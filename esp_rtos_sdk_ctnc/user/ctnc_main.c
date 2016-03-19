/******************************************************************************
00 * Copyright 2013-2014 Espressif Systems (Wuxi)
 *
 * FileName: user_main.c
 *
 * Description: entry file of user application
 *
 * Modification history:
 *     2014/12/1, v1.0 create this file.
*******************************************************************************/
#include "ctnc_common.h"

#ifndef ENABLE_SENSOR

LOCAL CTNC_RES ICACHE_FLASH_ATTR	fResource[CTNC_MAX_NUMBER_OF_RESOURCE];
LOCAL CTNC_VW ICACHE_FLASH_ATTR  	fVirtualWire[CTNC_MAX_NUMBER_OF_VIRTUAL_WIRE];
LOCAL CTNC_TMR ICACHE_FLASH_ATTR 	fTimer[CTNC_MAX_NUMBER_OF_TIMER];

LOCAL void ICACHE_FLASH_ATTR buttonTask(void *pvParameters)
{
	uint8_t 	loopIndex;
	uint8_t 	currentValue;

	DBGINF(("Button task initiated"));
	vTaskDelay(100);
	DBGINF(("Button task running"));

	for (loopIndex = 0; loopIndex < CTNC_MAX_NUMBER_OF_RESOURCE; loopIndex++) {
		if (CTNC_RES_TYPE_BINARY_INPUT == fResource[loopIndex].type) {
			PIN_FUNC_SELECT(fResource[loopIndex].gpioName, fResource[loopIndex].gpioFunc);
			PIN_PULLUP_EN(fResource[loopIndex].gpioName);

			//GPIO_DIS_OUTPUT(GPIO_ID_PIN(fResource[loopIndex].gpioNumber));
			gpio_output_set(0, BIT(GPIO_ID_PIN(fResource[loopIndex].gpioNumber)), 0,0);

			RES_setResourceValue(fResource[loopIndex].id, fResource[loopIndex].value);
		}
	}
	DBGINF(("All resource output set to current values."));

	while (1) {
		for (loopIndex = 0; loopIndex < CTNC_MAX_NUMBER_OF_RESOURCE; loopIndex++) {
			if (CTNC_RES_TYPE_BINARY_INPUT == fResource[loopIndex].type) {
				currentValue = GPIO_READ(fResource[loopIndex].gpioNumber);
				if (1 == fResource[loopIndex].lacheValue && 0 == currentValue) {
					DBGINF(("Button at %d GPIO pressed", fResource[loopIndex].gpioNumber));
					RES_setResourceValue(
							fResource[loopIndex].id,
							((fResource[loopIndex].value == 1) ? 0 : 1));
					fResource[loopIndex].lacheValue = currentValue;
				} else if (0 == fResource[loopIndex].lacheValue && 1 == currentValue) {
					DBGINF(("Button at %d GPIO release", fResource[loopIndex].gpioNumber));
					fResource[loopIndex].lacheValue = currentValue;
				} else {
					//DBGINF(("No change in %d GPIO", fResource[loopIndex].gpioNumber));
				}
			}
		}

		for (loopIndex = 0; loopIndex < CTNC_MAX_NUMBER_OF_TIMER; loopIndex++) {
			if (RES_INVALID_ID != fTimer[loopIndex].resId) {
				if (fTimer[loopIndex].timeLeft <= CTNC_BTN_TASK_SLEEP) {
					CTNC_RES * res = RES_getResource(fTimer[loopIndex].resId);

					if (NULL == res) {
						DBGERR(("Invalid resource Id set for timer"));
					} else {
						if (res->value != fTimer[loopIndex].value) {
							RES_setResourceValue(fTimer[loopIndex].resId, fTimer[loopIndex].value);
						}
					}

					fTimer[loopIndex].timeLeft = fTimer[loopIndex].timeout;

				} else {
					fTimer[loopIndex].timeLeft -= CTNC_BTN_TASK_SLEEP;
				}
			}
		}

		vTaskDelay(CTNC_BTN_TASK_SLEEP);
	}

    DBGERR(("QUITING BUTTON TASK, This is never expected"));
    vTaskDelete(NULL);
}

CTNC_RES * ICACHE_FLASH_ATTR RES_getResource(uint32_t resId)
{
	CTNC_RES * res = NULL;
	
	if (RES_INVALID_ID == resId) {
		res = &fResource[0];
	} else if (resId >= 1 && resId <= CTNC_MAX_NUMBER_OF_RESOURCE) {
		res = &fResource[resId - 1];
	}
			
	return res;
}

int32_t ICACHE_FLASH_ATTR handleInput(uint8_t * srcNodeId, uint32_t srcId, uint16_t srcValue)
{
	int32_t 	status = 0;
	uint8_t		loopIndex;
	CTNC_VW * 	ctncVw;
	
	for (loopIndex = 0; loopIndex < CTNC_MAX_NUMBER_OF_VIRTUAL_WIRE; loopIndex++) {
		ctncVw = &fVirtualWire[loopIndex];

		if ( (0 == strcmp(ctncVw->srcNodeId, srcNodeId)) &&
		     (ctncVw->srcResId == srcId) ) {
			if (0 == strcmp(ctncVw->destNodeId, MESH_getNodeID())) {
				if (ctncVw->destResId == srcId) {
					DBGERR(("Wrong virtual wiring"));
					status = -2;
				} else {
					DBGINF(("Setting actual output [%d]", ctncVw->type));
					if (CTNC_VW_TYPE_FOLLOW == ctncVw->type)
						status = RES_setResourceValue(ctncVw->destResId, srcValue);
					else if (CTNC_VW_TYPE_REVERSE == ctncVw->type)
						status = RES_setResourceValue(ctncVw->destResId, !(srcValue));
					else
						status = -4;
				}
			} else {
				uint8_t 	remoteRequest[50] = {0};
				uint32_t 	remoteRequestLength;

				remoteRequestLength = snprintf(
										&remoteRequest[0], 50, "/506/%s/%s/sresval/%d/%d",
										MESH_getNodeID(),
										ctncVw->destNodeId,
										ctncVw->destResId,
										(CTNC_VW_TYPE_REVERSE == ctncVw->type) ? !(srcValue) : srcValue);
				status = sendUDPData(remoteRequest, remoteRequestLength);
			}
		}
	}

	return (status);
}

int32_t ICACHE_FLASH_ATTR RES_setResourceValue(uint32_t resId, uint16_t newValue)
{
	int32_t status = -1;
	uint8_t loopIndex= 0;

	if (RES_INVALID_ID != resId) {
		CTNC_RES * res = RES_getResource(resId);
		
		if (NULL != res) {
			if ((CTNC_RES_TYPE_BINARY_OUTPUT == res->type) &&
				(0 == newValue || 1 == newValue) ) {
				res->value = newValue;
				status = 0;
				
				DBGINF(("Output resource %d set to new value %d", res->id, res->value));
				printf("\n&&SIO%1d%1d?\n", res->gpioIndicator, res->value);

			} else if ((CTNC_RES_TYPE_BINARY_INPUT == res->type) &&
					   (0 == newValue || 1 == newValue) ) {
				res->value = newValue;

				// Reset the timer value
				for (loopIndex = 0; loopIndex < CTNC_MAX_NUMBER_OF_TIMER; loopIndex++) {
					if (res->id == fTimer[loopIndex].resId) {
						fTimer[loopIndex].timeLeft = fTimer[loopIndex].timeout;
					}
				}

				if (0 == (status = handleInput(MESH_getNodeID(), res->id, res->value))) {
					// Switch LED
					printf("\n&&SIO%1d%1d?\n", res->gpioIndicator, res->value);
					DBGINF(("Input resource %d set to new value %d", res->id, res->value));
				} else {
					DBGERR(("Could not served the input request"));
				}
				
			} else {
				DBGERR(("Resource type does not match"));
				status = -2;
			}
		} else {
			DBGERR(("Invalid resource ID"));
			status = -3;
		}
	} else {
		DBGERR(("Resource ID is passed as INVALID"));
		status = -4;
	}

	return status;
}

int32_t ICACHE_FLASH_ATTR RES_setResourceName(uint32_t resId, uint8_t * newName)
{
	int32_t 	status = -1;
	CTNC_RES * 	res = RES_getResource(resId);
	
	if (NULL != res) {
		bzero(res->name, CTNC_MAX_RESOURCE_NAME + 1);
		strncpy(res->name, newName, CTNC_MAX_RESOURCE_NAME);

		status = 0;
		
		DBGINF(("Resource %d given new name %s", res->id, res->name));
	} else {
		DBGERR(("Invalid resource ID"));
		status = -2;
	}

	return status;
}

int32_t ICACHE_FLASH_ATTR RES_Init(void)
{
	int32_t		status = -1;
	uint8_t 	loopIndex;

	bzero(fResource, sizeof(fResource));

	for (loopIndex = 0; loopIndex < CTNC_MAX_NUMBER_OF_RESOURCE; loopIndex++) {
		fResource[loopIndex].id = loopIndex + 1;

		fResource[loopIndex].gpioNumber = loopIndex;
		fResource[loopIndex].gpioFunc = 0;
		fResource[loopIndex].gpioName = 0;
		fResource[loopIndex].gpioIndicator = 0;

		fResource[loopIndex].type = CTNC_RES_TYPE_INVALID;
		fResource[loopIndex].lacheValue = 1;
		fResource[loopIndex].value = 0;
		snprintf(&fResource[loopIndex].name[0], CTNC_MAX_RESOURCE_NAME, "RES-%02d", loopIndex + 1);
	}

	fResource[0].type = CTNC_RES_TYPE_BINARY_INPUT;
	fResource[0].gpioNumber = 0;
	fResource[0].gpioFunc = FUNC_GPIO0;
	fResource[0].gpioName = PERIPHS_IO_MUX_GPIO0_U;
	fResource[0].gpioIndicator = 1;

	fResource[1].type = CTNC_RES_TYPE_BINARY_INPUT;
	fResource[1].gpioNumber = 4;
	fResource[1].gpioFunc = FUNC_GPIO4;
	fResource[1].gpioName = PERIPHS_IO_MUX_GPIO4_U;
	fResource[1].gpioIndicator = 2;

	fResource[2].type = CTNC_RES_TYPE_BINARY_INPUT;
	fResource[2].gpioNumber = 5;
	fResource[2].gpioFunc = FUNC_GPIO5;
	fResource[2].gpioName = PERIPHS_IO_MUX_GPIO5_U;
	fResource[2].gpioIndicator = 3;

	fResource[3].type = CTNC_RES_TYPE_BINARY_OUTPUT;
	fResource[3].gpioNumber = 6;
	fResource[3].gpioIndicator = 6;

	fResource[4].type = CTNC_RES_TYPE_BINARY_OUTPUT;
	fResource[4].gpioNumber = 7;
	fResource[4].gpioIndicator = 7;

	fResource[5].type = CTNC_RES_TYPE_BINARY_OUTPUT;
	fResource[5].gpioNumber = 8;
	fResource[5].gpioIndicator = 8;

	DBGINF(("Default values set for resources"));

	bzero(fVirtualWire, sizeof(fVirtualWire));

	for (loopIndex = 0; loopIndex < CTNC_MAX_NUMBER_OF_VIRTUAL_WIRE; loopIndex++) {
		fVirtualWire[loopIndex].id = loopIndex + 1;
	}

	VW_addVirtualWire(CTNC_VW_TYPE_FOLLOW, MESH_getNodeID(), 1, MESH_getNodeID(), 5);
	VW_addVirtualWire(CTNC_VW_TYPE_FOLLOW, MESH_getNodeID(), 2, MESH_getNodeID(), 4);
	VW_addVirtualWire(CTNC_VW_TYPE_FOLLOW, MESH_getNodeID(), 3, MESH_getNodeID(), 6);

	DBGINF(("All virtual wire ids set."));

	bzero(fTimer, sizeof(fTimer));

	for (loopIndex = 0; loopIndex < CTNC_MAX_NUMBER_OF_TIMER; loopIndex++) {
		fTimer[loopIndex].id = loopIndex + 1;
	}

	TMR_addTimer(2, 10000, 0);

	DBGINF(("All timer ids set."));

	xTaskCreate(buttonTask, "btn", CTNC_BTN_TASK_STACK_SIZE, NULL, 2, NULL);

	status = 0;
	return status;
}

CTNC_VW * ICACHE_FLASH_ATTR VW_getVirtualWire(uint32_t vwId)
{
	uint8_t 	loopIndex;
	CTNC_VW * 	vw = NULL;
	
	if (RES_INVALID_ID == vwId) {
		vw = &fVirtualWire[0];
	} else {
		for (loopIndex = 0; loopIndex < CTNC_MAX_NUMBER_OF_VIRTUAL_WIRE; loopIndex++) {
			if (fVirtualWire[loopIndex].id == vwId) {
				vw = &fVirtualWire[loopIndex];
				break;
			}
		}
	}

	return vw;	
}

CTNC_VW * ICACHE_FLASH_ATTR VW_addVirtualWire(CTNC_VW_TYPE type, uint8_t * srcNodeId, uint32_t srcResId, uint8_t * destNodeId, uint32_t destResId)
{
	uint8_t 	loopIndex;
	CTNC_VW * 	vwFree = NULL;
	CTNC_VW * 	vw = NULL;

	for (loopIndex = 0; loopIndex < CTNC_MAX_NUMBER_OF_VIRTUAL_WIRE; loopIndex++) {
		if ( (fVirtualWire[loopIndex].srcResId == srcResId) &&
			 (fVirtualWire[loopIndex].destResId == destResId) &&
			 (0 == strncmp(fVirtualWire[loopIndex].srcNodeId, srcNodeId, CTNC_MAX_NODE_ID_LENGTH)) &&
			 (0 == strncmp(fVirtualWire[loopIndex].destNodeId, destNodeId, CTNC_MAX_NODE_ID_LENGTH)) ) {

			vw = &fVirtualWire[loopIndex];
			break;
		} else if ( (NULL == vwFree) &&
				 	(RES_INVALID_ID == fVirtualWire[loopIndex].srcResId) ) {
			vwFree = &fVirtualWire[loopIndex];
		}
	}
	
	if (NULL == vw) {
		if (NULL != vwFree) {
			vw = vwFree;

			vw->type = type;
			vw->srcResId = srcResId;
			bzero(vw->destNodeId, sizeof(vw->destNodeId));
			strncpy(vw->srcNodeId, srcNodeId, CTNC_MAX_NODE_ID_LENGTH);
			strncpy(vw->destNodeId, destNodeId, CTNC_MAX_NODE_ID_LENGTH);
			vw->destResId = destResId;
		} else {
			DBGERR(("Out of free slots to store virtual wire"));
		}
	}

	return vw;
}

int32_t ICACHE_FLASH_ATTR VW_removeVirtualWire(uint32_t vwId)
{
	int32_t 	status = -1;
	uint8_t 	loopIndex;

	if (RES_INVALID_ID == vwId) {
		// Remove all VW
		status = 0;
		for (loopIndex = 0; loopIndex < CTNC_MAX_NUMBER_OF_VIRTUAL_WIRE; loopIndex++) {
			fVirtualWire[loopIndex].srcResId = RES_INVALID_ID;
		}
	} else {
		status = -2;
		for (loopIndex = 0; loopIndex < CTNC_MAX_NUMBER_OF_VIRTUAL_WIRE; loopIndex++) {
			if (fVirtualWire[loopIndex].id == vwId) {
				fVirtualWire[loopIndex].srcResId = RES_INVALID_ID;

				status = 0;
				break;
			}
		}
	}

	return status;
}

CTNC_TMR * ICACHE_FLASH_ATTR TMR_getTimer(uint32_t tmrId)
{
	uint8_t 		loopIndex;
	CTNC_TMR * 		tmr = NULL;

	if (RES_INVALID_ID == tmrId) {
		tmr = &fTimer[0];
	} else {
		for (loopIndex = 0; loopIndex < CTNC_MAX_NUMBER_OF_TIMER; loopIndex++) {
			if (fTimer[loopIndex].id == tmrId) {
				tmr = &fTimer[loopIndex];
				break;
			}
		}
	}

	return tmr;
}

CTNC_TMR * ICACHE_FLASH_ATTR TMR_addTimer(uint8_t resId, uint32_t timeout, uint8_t value)
{
	uint8_t 		loopIndex;
	CTNC_TMR * 		tmrFree = NULL;
	CTNC_TMR * 		tmr = NULL;

	// TODO :: Time needs to divided by 4 in order to get proper trigger
	if (timeout > 40) timeout = timeout / 4;

	for (loopIndex = 0; loopIndex < CTNC_MAX_NUMBER_OF_TIMER; loopIndex++) {
		if ((fTimer[loopIndex].resId == resId) &&
			(fTimer[loopIndex].timeout == timeout)) {

			tmr = &fTimer[loopIndex];
			break;
		} else if ( (NULL == tmrFree) &&
				 	(RES_INVALID_ID == fTimer[loopIndex].resId) ) {
			tmrFree = &fTimer[loopIndex];
		}
	}

	if (NULL == tmr) {
		if (NULL != tmrFree) {
			tmr = tmrFree;

			tmr->resId = resId;
			tmr->value = value;
			tmr->timeout = timeout;
			tmr->timeLeft = timeout;
		} else {
			DBGERR(("Out of free slots to store timer"));
		}
	}

	return tmr;
}

int32_t ICACHE_FLASH_ATTR TMR_removeTimer(uint32_t tmrId)
{
	int32_t 	status = -1;
	uint8_t 	loopIndex;

	if (RES_INVALID_ID == tmrId) {
		// Remove all Timers
		status = 0;
		for (loopIndex = 0; loopIndex < CTNC_MAX_NUMBER_OF_TIMER; loopIndex++) {
			fTimer[loopIndex].resId = RES_INVALID_ID;
		}
	} else {
		status = -2;
		for (loopIndex = 0; loopIndex < CTNC_MAX_NUMBER_OF_TIMER; loopIndex++) {
			if (fTimer[loopIndex].id == tmrId) {
				fTimer[loopIndex].resId = RES_INVALID_ID;

				status = 0;
				break;
			}
		}
	}

	return status;
}

#endif /* !ENABLE_SENSOR */
