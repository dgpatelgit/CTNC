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

#ifdef ENABLE_SENSOR

LOCAL CTNC_RES ICACHE_FLASH_ATTR	fResource[CTNC_MAX_NUMBER_OF_RESOURCE];

LOCAL void ICACHE_FLASH_ATTR buttonTask(void *pvParameters)
{
	static uint32_t messageId = 0;
	uint8_t 	loopIndex;
	uint8_t 	currentValue;
	uint8_t 	remoteRequest[50] = {0};
	uint32_t 	remoteRequestLength;

	DBGINF(("Button task initiated"));
	vTaskDelay(100);
	DBGINF(("Button task running"));

	for (loopIndex = 0; loopIndex < CTNC_MAX_NUMBER_OF_RESOURCE; loopIndex++) {
		if (CTNC_RES_TYPE_BINARY_INPUT == fResource[loopIndex].type) {
			PIN_FUNC_SELECT(fResource[loopIndex].gpioName, fResource[loopIndex].gpioFunc);
			PIN_PULLUP_EN(fResource[loopIndex].gpioName);

			//GPIO_DIS_OUTPUT(GPIO_ID_PIN(fResource[loopIndex].gpioNumber));
			gpio_output_set(0, BIT(GPIO_ID_PIN(fResource[loopIndex].gpioNumber)), 0,0);
		}
	}
	DBGINF(("All resource output set to current values."));

	while (1) {
		for (loopIndex = 0; loopIndex < CTNC_MAX_NUMBER_OF_RESOURCE; loopIndex++) {
			fResource[loopIndex].lacheValue++;
			currentValue = GPIO_READ(fResource[loopIndex].gpioNumber);
			if ( (currentValue != fResource[loopIndex].value) ||
				 (fResource[loopIndex].lacheValue >= 5000) ) {
				fResource[loopIndex].value = currentValue;
				fResource[loopIndex].lacheValue = 0;

				messageId++;
				remoteRequestLength = snprintf(
										&remoteRequest[0], 50, "/%d/%s/%s/uresval/%d/%d",
										messageId,
										MESH_getNodeID(),
										MESH_getNodeID(),
										fResource[loopIndex].id, fResource[loopIndex].value);

				for (loopIndex = 0; loopIndex < 4; loopIndex++) {
					sendUDPData(remoteRequest, remoteRequestLength);
					vTaskDelay(50);
				}

				break;
			}
		}

		vTaskDelay(CTNC_BTN_TASK_SLEEP);
	}

    DBGERR(("QUITING BUTTON TASK, This is never expected"));
    vTaskDelete(NULL);
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
	fResource[1].gpioNumber = 2;
	fResource[1].gpioFunc = FUNC_GPIO2;
	fResource[1].gpioName = PERIPHS_IO_MUX_GPIO2_U;
	fResource[1].gpioIndicator = 2;

	DBGINF(("Default values set for resources"));

	xTaskCreate(buttonTask, "btn", CTNC_BTN_TASK_STACK_SIZE, NULL, 2, NULL);

	status = 0;
	return status;
}

#endif /* ENABLE_SENSOR */
