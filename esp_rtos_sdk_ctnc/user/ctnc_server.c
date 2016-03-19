/******************************************************************************
 * Copyright 2013-2014 Espressif Systems (Wuxi)
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

// Server error codes
typedef enum _SERVER_ERROR_CODE_ {
	SEC_OK = 0,
	SEC_RESPONSE = 1,
	SEC_UNKNOWN = 100,

	SEC_REQUEST_READ_FAILED,
	SEC_INVALID_REQUEST,
	SEC_SYSTEM_CALL_FAILURE,
	SEC_MISSING_INPUT,
	SEC_INVALID_INPUT,
	SEC_OUT_OF_MEMORY

} SEC;

LOCAL SEC ICACHE_FLASH_ATTR processRequest(
								uint8_t * 	requestUrl,
								uint8_t *	responseBuffer,
								uint16_t *	responseBufferLength)
{
	SEC 		errorCode = SEC_UNKNOWN;
	uint8_t * 	restUrl = requestUrl;
	uint8_t * 	messageId = NULL;
	uint8_t * 	fromNodeId = NULL;
	uint8_t * 	toNodeId = NULL;
	uint8_t * 	command = NULL;
	uint8_t * 	tmpStrPtr1 = NULL;
	uint8_t * 	tmpStrPtr2 = NULL;
	uint8_t * 	tmpStrPtr3 = NULL;
	uint8_t		loopIndex;
	uint16_t	requestUrlLength = strlen(requestUrl);
	uint16_t	requestUrlReadIndex;
	uint32_t	tmpId;
	uint32_t	tmpVal;
	uint32_t	writeIndex;
	CTNC_RES * 	res;
	CTNC_VW * 	vw;
	CTNC_TMR *  tmr;

	// Loop breaks if control reaches end
	while (1) {
		DBGINF(("URL : [%s]", requestUrl));

		if (0 == strncmp("errorCode", &requestUrl[0], 9)) {
			DBGINF(("Received response [%s]", requestUrl));
			errorCode = SEC_RESPONSE;
			break;
		} else if ('G' == requestUrl[0]) {
			DBGINF(("Looks like we found TCP request"));

			tmpStrPtr1 = strtok(requestUrl, " ");
			restUrl = strtok(NULL, " ");

			if (NULL == restUrl) {
				DBGERR(("Invalid TCP request"));
				errorCode = SEC_INVALID_REQUEST;
				break;
			}
		} else {
			restUrl = requestUrl;
		}

		if ('/' != restUrl[0]) {
			DBGERR(("URL does not start as expected"));
			errorCode = SEC_INVALID_REQUEST;
			break;
		}

		messageId = &restUrl[1];
		requestUrlReadIndex = 1;
		for (loopIndex = requestUrlReadIndex; loopIndex < requestUrlLength; loopIndex++) {
			if ('/' == restUrl[loopIndex]) {
				restUrl[loopIndex] = 0;
				fromNodeId = &restUrl[loopIndex + 1];
				requestUrlReadIndex = loopIndex + 2;
				break;
			}
		}
		if (NULL == messageId) {
			DBGERR(("NULL message Id"));
			errorCode = SEC_INVALID_REQUEST;
			break;
		}
		DBGINF(("Message ID: [%s]", messageId));

		for (loopIndex = requestUrlReadIndex; loopIndex < requestUrlLength; loopIndex++) {
			if ('/' == restUrl[loopIndex]) {
				restUrl[loopIndex] = 0;
				toNodeId = &restUrl[loopIndex + 1];
				requestUrlReadIndex = loopIndex + 2;
				break;
			}
		}
		if (NULL == fromNodeId) {
			DBGERR(("NULL from node id"));
			errorCode = SEC_INVALID_REQUEST;
			break;
		}
		DBGINF(("From Node ID: [%s]", fromNodeId));

		for (loopIndex = requestUrlReadIndex; loopIndex < requestUrlLength; loopIndex++) {
			if ('/' == restUrl[loopIndex]) {
				restUrl[loopIndex] = 0;
				command = &restUrl[loopIndex + 1];
				requestUrlReadIndex = loopIndex + 2;
				break;
			}
		}
		if (NULL == toNodeId) {
			DBGERR(("NULL to node id"));
			errorCode = SEC_INVALID_REQUEST;
			break;
		}
		DBGINF(("To Node ID: [%s]", toNodeId));

		for (loopIndex = requestUrlReadIndex; loopIndex < requestUrlLength; loopIndex++) {
			if ('/' == restUrl[loopIndex]) {
				restUrl[loopIndex] = 0;
				tmpStrPtr1 = &restUrl[loopIndex + 1];
				requestUrlReadIndex = loopIndex + 2;
				break;
			}
		}
		if (NULL == command) {
			DBGERR(("NULL command"));
			errorCode = SEC_INVALID_REQUEST;
			break;
		}
		DBGINF(("command: [%s]", command));

		if (0 == strcmp(command, "gnid")) {
			// Name 	:: Get Node ID
			// Format	:: /gnid

			*responseBufferLength = snprintf(
										responseBuffer,
										*responseBufferLength,
										"errorCode:%d|messageId:%s|request:%s" \
										"#nodeId:%s",
										SEC_OK, messageId, command,
										MESH_getNodeID());
			errorCode = SEC_OK;

			DBGINF(("/gnid ==> [%s]", responseBuffer));

		} else if (0 == strcmp(command, "sssidpass")) {
			// Name 	:: Set SSID and Pass
			// Format	:: sssidpass/<SSID>/<Password>

			struct station_config config;

			for (loopIndex = requestUrlReadIndex; loopIndex < requestUrlLength; loopIndex++) {
				if ('/' == restUrl[loopIndex]) {
					restUrl[loopIndex] = 0;
					tmpStrPtr2 = &restUrl[loopIndex + 1];
					requestUrlReadIndex = loopIndex + 2;
					break;
				}
			}
			if (NULL == tmpStrPtr1) {
				DBGERR(("SSID not received"));

				errorCode = SEC_MISSING_INPUT;
				break;
			}

			if (NULL == tmpStrPtr2) {
				DBGERR(("Pass not received"));

				errorCode = SEC_MISSING_INPUT;
				break;
			}

			DBGINF(("SSID: [%s] Pass: [%s]", tmpStrPtr1, tmpStrPtr2));

			bzero(&config, sizeof(config));
			if (!wifi_station_get_config(&config)) {
				DBGERR(("Failed to get current STA config"));

				errorCode = SEC_SYSTEM_CALL_FAILURE;
				break;
			}

			strncpy(config.ssid, tmpStrPtr1, 32);
			strncpy(config.password, tmpStrPtr2, 64);
			if (!wifi_station_set_config(&config)) {
				DBGERR(("Failed to set new STA config"));

				errorCode = SEC_SYSTEM_CALL_FAILURE;
				break;
			} else if (!wifi_set_opmode(STATION_MODE)) {
				DBGERR(("Failed to set STATION MODE"));

				errorCode = SEC_SYSTEM_CALL_FAILURE;
				break;
			} else {
				*responseBufferLength = snprintf(
											responseBuffer,
											*responseBufferLength,
											"errorCode:%d|messageId:%s|request:%s",
											SEC_OK, messageId, command);
				errorCode = SEC_OK;
			}

		} else if (0 == strcmp(command, "gres")) {
			// Name		:: Get resource details, '0' will fetch all resource details
			// Format	:: gres/<Resource ID>

			if (NULL == tmpStrPtr1) {
				DBGERR(("Failed to get resource ID"));

				errorCode = SEC_MISSING_INPUT;
				break;
			}

			tmpId = atoi(tmpStrPtr1);
			DBGINF(("Resouce ID: %d", tmpId));

			// If resource ID is '0' then return all resource details
			res = RES_getResource(tmpId);
			writeIndex = 0;
			for (loopIndex = 0; loopIndex < CTNC_MAX_NUMBER_OF_RESOURCE; loopIndex++, res++) {
				if (0 == writeIndex) {
					writeIndex = snprintf(
									responseBuffer,
									*responseBufferLength,
									"errorCode:%d|messageId:%s|request:%s",
									SEC_OK, messageId, command);
				}
				
				if ((*responseBufferLength - writeIndex) > 0) {
					writeIndex += snprintf(
									&responseBuffer[writeIndex],
									*responseBufferLength - writeIndex,
									"#resourceId:%d|name:%s|type:%d|value:%d",
									res->id,
									res->name,
									res->type,
									res->value);
				} else {
					DBGERR(("Running out of buffer to give response"));

					errorCode = SEC_OUT_OF_MEMORY;
					break;
				}
				
				if (RES_INVALID_ID != tmpId) break;
			}
			
			*responseBufferLength = writeIndex;
			errorCode = SEC_OK;

		} else if (0 == strcmp(command, "sresval")) {
			// Name		:: Set resource value
			// Format	:: sresval/<Resource ID>/<New Value>

			for (loopIndex = requestUrlReadIndex; loopIndex < requestUrlLength; loopIndex++) {
				if ('/' == restUrl[loopIndex]) {
					restUrl[loopIndex] = 0;
					tmpStrPtr2 = &restUrl[loopIndex + 1];
					requestUrlReadIndex = loopIndex + 2;
					break;
				}
			}
			if (NULL == tmpStrPtr1) {
				DBGERR(("Failed to get resource ID"));

				errorCode = SEC_MISSING_INPUT;
				break;
			}

			tmpId = atoi(tmpStrPtr1);

			if (NULL == tmpStrPtr2) {
				DBGERR(("Failed to get new value"));

				errorCode = SEC_MISSING_INPUT;
				break;
			}

			tmpVal = atoi(tmpStrPtr2);
			DBGINF(("Resource ID: %d New value: %d", tmpId, tmpVal));

			if (0 != RES_setResourceValue(tmpId, tmpVal)) {
				DBGERR(("Failed to set new value to the resource"));

				errorCode = SEC_INVALID_INPUT;
				break;
			}

			if (NULL != (res = RES_getResource(tmpId))) {
				*responseBufferLength = snprintf(
											responseBuffer,
											*responseBufferLength,
											"errorCode:%d|messageId:%s|request:%s" \
											"#resourceId:%d|name:%s|type:%d|value:%d",
											SEC_OK, messageId, command,
											res->id,
											res->name,
											res->type,
											res->value);
				errorCode = SEC_OK;
			} else {
				DBGERR(("Failed to get resource after setting new value"));

				errorCode = SEC_INVALID_INPUT;
			}

		} else if (0 == strcmp(command, "sresnm")) {
			// Name		:: Set the new name to resource
			// Format	:: sresnm/<Resource ID>/<New Name>

			for (loopIndex = requestUrlReadIndex; loopIndex < requestUrlLength; loopIndex++) {
				if ('/' == restUrl[loopIndex]) {
					restUrl[loopIndex] = 0;
					tmpStrPtr2 = &restUrl[loopIndex + 1];
					requestUrlReadIndex = loopIndex + 2;
					break;
				}
			}
			if (NULL == tmpStrPtr1) {
				DBGERR(("Failed to get resource ID"));

				errorCode = SEC_MISSING_INPUT;
				break;
			}

			tmpId = atoi(tmpStrPtr1);

			if (NULL == tmpStrPtr2) {
				DBGERR(("Failed to get new name"));

				errorCode = SEC_MISSING_INPUT;
				break;
			}

			DBGINF(("Resource ID: %d New name: %s", tmpId, tmpStrPtr2));

			if (0 != RES_setResourceName(tmpId, tmpStrPtr2)) {
				DBGERR(("Failed to set new name to the resource"));

				errorCode = SEC_INVALID_INPUT;
				break;
			}

			if (NULL != (res = RES_getResource(tmpId))) {
				*responseBufferLength = snprintf(
											responseBuffer,
											*responseBufferLength,
											"errorCode:%d|messageId:%s|request:%s" \
											"#resourceId:%d|name:%s|type:%d|value:%d",
											SEC_OK, messageId, command,
											res->id,
											res->name,
											res->type,
											res->value);
				errorCode = SEC_OK;
			} else {
				DBGERR(("Failed to get resource after setting new name"));

				errorCode = SEC_INVALID_INPUT;
			}

		} else if (0 == strcmp(command, "uresval")) {
			// Name		:: Update resource value notification from other devices
			// Format	:: uresval/<Source Resource ID>/<New Value>

			for (loopIndex = requestUrlReadIndex; loopIndex < requestUrlLength; loopIndex++) {
				if ('/' == restUrl[loopIndex]) {
					restUrl[loopIndex] = 0;
					tmpStrPtr2 = &restUrl[loopIndex + 1];
					requestUrlReadIndex = loopIndex + 2;
					break;
				}
			}
			if (NULL == tmpStrPtr1) {
				DBGERR(("Failed to get resource ID"));

				errorCode = SEC_MISSING_INPUT;
				break;
			}

			tmpId = atoi(tmpStrPtr1);

			if (NULL == tmpStrPtr2) {
				DBGERR(("Failed to get new value"));

				errorCode = SEC_MISSING_INPUT;
				break;
			}

			tmpVal = atoi(tmpStrPtr2);
			DBGINF(("Resource ID: %d New value: %d", tmpId, tmpVal));

			if (0 != handleInput(fromNodeId, tmpId, tmpVal)) {
				DBGERR(("Failed to serve the update resource trigger"));

				errorCode = SEC_INVALID_INPUT;
				break;
			} else {
				*responseBufferLength = snprintf(
											responseBuffer,
											*responseBufferLength,
											"errorCode:%d|messageId:%s|request:%s",
											SEC_OK, messageId, command);
				errorCode = SEC_OK;
			}

		} else if (0 == strcmp(command, "gvw")) {
			// Name		:: Get virtual wire entries, '0' will fetch all enteries
			// Format	:: gvw/<Virtual wire ID>

			if (NULL == tmpStrPtr1) {
				DBGERR(("Failed to get virtual wire ID"));

				errorCode = SEC_MISSING_INPUT;
				break;
			}

			tmpId = atoi(tmpStrPtr1);
			DBGINF(("Virtual wire ID: %d", tmpId));

			// If virtual wire ID is '0' then return all VW details
			vw = VW_getVirtualWire(tmpId);
			writeIndex = 0;
			for (loopIndex = 0; loopIndex < CTNC_MAX_NUMBER_OF_VIRTUAL_WIRE; loopIndex++, vw++) {
				if (0 == writeIndex) {
					writeIndex = snprintf(
									responseBuffer,
									*responseBufferLength,
									"errorCode:%d|messageId:%s|request:%s",
									SEC_OK, messageId, command);
				}

				if ((*responseBufferLength - writeIndex) > 0) {
					writeIndex += snprintf(
									&responseBuffer[writeIndex],
									*responseBufferLength - writeIndex,
									"#vwId:%d|type:%d|srcNodeId:%s|srcResId:%d|destNodeId:%s|destResId:%d",
									vw->id,
									vw->type,
									vw->srcNodeId,
									vw->srcResId,
									vw->destNodeId,
									vw->destResId);
				} else {
					DBGERR(("Running out of buffer to give response"));

					errorCode = SEC_OUT_OF_MEMORY;
					break;
				}
				
				if (RES_INVALID_ID != tmpId) break;
			}

			*responseBufferLength = writeIndex;
			errorCode = SEC_OK;

		} else if (0 == strcmp(command, "avw")) {
			// Name		:: Add new virtual wire
			// Format	:: avw/<Type>/<Source Node ID>/<Source Resource ID>/<Destination Node ID>/<Destination Resource ID>/

			tmpStrPtr2 = NULL;
			for (loopIndex = requestUrlReadIndex; loopIndex < requestUrlLength; loopIndex++) {
				if ('/' == restUrl[loopIndex]) {
					restUrl[loopIndex] = 0;
					tmpStrPtr2 = &restUrl[loopIndex + 1];
					requestUrlReadIndex = loopIndex + 2;
					break;
				}
			}
			if (NULL == tmpStrPtr1) {
				DBGERR(("Failed to get type"));

				errorCode = SEC_MISSING_INPUT;
				break;
			}
			writeIndex = atoi(tmpStrPtr1);
			if (writeIndex <= CTNC_VW_TYPE_INVALID || writeIndex > CTNC_VW_TYPE_LAST) {
				DBGERR(("Invalid type"));

				errorCode = SEC_INVALID_INPUT;
				break;
			}

			tmpStrPtr3 = NULL;
			for (loopIndex = requestUrlReadIndex; loopIndex < requestUrlLength; loopIndex++) {
				if ('/' == restUrl[loopIndex]) {
					restUrl[loopIndex] = 0;
					tmpStrPtr3 = &restUrl[loopIndex + 1];
					requestUrlReadIndex = loopIndex + 2;
					break;
				}
			}
			if (NULL == tmpStrPtr2) {
				DBGERR(("Failed to get source node ID"));

				errorCode = SEC_MISSING_INPUT;
				break;
			}

			tmpStrPtr1 = NULL;
			for (loopIndex = requestUrlReadIndex; loopIndex < requestUrlLength; loopIndex++) {
				if ('/' == restUrl[loopIndex]) {
					restUrl[loopIndex] = 0;
					tmpStrPtr1 = &restUrl[loopIndex + 1];
					requestUrlReadIndex = loopIndex + 2;
					break;
				}
			}
			if (NULL == tmpStrPtr3) {
				DBGERR(("Failed to get source resource ID"));

				errorCode = SEC_MISSING_INPUT;
				break;
			}
			tmpId = atoi(tmpStrPtr3);
			if (tmpId < 1 || tmpId > CTNC_MAX_NUMBER_OF_RESOURCE) {
				DBGERR(("Invalid source resource ID"));

				errorCode = SEC_INVALID_INPUT;
				break;
			}

			tmpStrPtr3 = NULL;
			for (loopIndex = requestUrlReadIndex; loopIndex < requestUrlLength; loopIndex++) {
				if ('/' == restUrl[loopIndex]) {
					restUrl[loopIndex] = 0;
					tmpStrPtr3 = &restUrl[loopIndex + 1];
					requestUrlReadIndex = loopIndex + 2;
					break;
				}
			}
			if (NULL == tmpStrPtr1) {
				DBGERR(("Failed to get destination node ID"));

				errorCode = SEC_MISSING_INPUT;
				break;
			}

			if (NULL == tmpStrPtr3) {
				DBGERR(("Failed to get destination resource ID"));

				errorCode = SEC_MISSING_INPUT;
				break;
			}
			tmpVal = atoi(tmpStrPtr3);
			if (tmpVal < 1 || tmpVal > CTNC_MAX_NUMBER_OF_RESOURCE) {
				DBGERR(("Invalid destination resource ID"));

				errorCode = SEC_INVALID_INPUT;
				break;
			}

			if (NULL != (vw = VW_addVirtualWire(writeIndex, tmpStrPtr2, tmpId, tmpStrPtr1, tmpVal))) {
				*responseBufferLength = snprintf(
											responseBuffer,
											*responseBufferLength,
											"errorCode:%d|messageId:%s|request:%s" \
											"#vwId:%d|type:%d|destNodeId:%s|srcResId:%d|destNodeId:%s|destResId:%d",
											SEC_OK, messageId, command,
											vw->id,
											vw->type,
											vw->srcNodeId,
											vw->srcResId,
											vw->destNodeId,
											vw->destResId);
				errorCode = SEC_OK;
			} else {
				DBGERR(("Could not add virtual wire"));

				errorCode = SEC_SYSTEM_CALL_FAILURE;
			}

		} else if (0 == strcmp(command, "rvw")) {
			// Name		:: Remove virtual wire entry
			// Format:: rvw/<Virtual Wire ID>

			if (NULL == tmpStrPtr1) {
				DBGERR(("Failed to get virtual wire ID"));

				errorCode = SEC_MISSING_INPUT;
				break;
			}

			tmpId = atoi(tmpStrPtr1);

			if (0 == VW_removeVirtualWire(tmpId)) {
				*responseBufferLength = snprintf(
											responseBuffer,
											*responseBufferLength,
											"errorCode:%d|messageId:%s|request:%s",
											SEC_OK, messageId, command);
				errorCode = SEC_OK;
			} else {
				DBGERR(("Could not remove virtual wire"));

				errorCode = SEC_SYSTEM_CALL_FAILURE;
			}

		} else if (0 == strcmp(command, "gtmr")) {
			// Name		:: Get registered timer, '0' will fetch all enteries
			// Format:: gtmr/<Timer ID>

			if (NULL == tmpStrPtr1) {
				DBGERR(("Failed to get callback ID"));

				errorCode = SEC_MISSING_INPUT;
				break;
			}

			tmpId = atoi(tmpStrPtr1);
			DBGINF(("Timer ID: %d", tmpId));

			// If callback ID is '0' then return all timer details
			tmr = TMR_getTimer(tmpId);
			writeIndex = 0;
			for (loopIndex = 0; loopIndex < CTNC_MAX_NUMBER_OF_TIMER; loopIndex++, tmr++) {
				if (0 == writeIndex) {
					writeIndex = snprintf(
									responseBuffer,
									*responseBufferLength,
									"errorCode:%d|messageId:%s|request:%s",
									SEC_OK, messageId, command);
				}

				if ((*responseBufferLength - writeIndex) > 0) {
					writeIndex += snprintf(
									&responseBuffer[writeIndex],
									*responseBufferLength - writeIndex,
									"#tmrId:%d|resId:%d|timeout:%d|value:%d",
									tmr->id,
									tmr->resId,
									tmr->timeout,
									tmr->value);
				} else {
					DBGERR(("Running out of buffer to give response"));

					errorCode = SEC_OUT_OF_MEMORY;
					break;
				}

				if (RES_INVALID_ID != tmpId) break;
			}

			*responseBufferLength = writeIndex;
			errorCode = SEC_OK;

		} else if (0 == strcmp(command, "atmr")) {
			// Name		:: Add new timer
			// Format	:: atmr/<Resource ID>/<Timeout in Milliseconds>/<Value to be set after timeout>

			tmpStrPtr2 = NULL;
			for (loopIndex = requestUrlReadIndex; loopIndex < requestUrlLength; loopIndex++) {
				if ('/' == restUrl[loopIndex]) {
					restUrl[loopIndex] = 0;
					tmpStrPtr2 = &restUrl[loopIndex + 1];
					requestUrlReadIndex = loopIndex + 2;
					break;
				}
			}
			if (NULL == tmpStrPtr1) {
				DBGERR(("Failed to get resource Id"));

				errorCode = SEC_MISSING_INPUT;
				break;
			}

			tmpId = atoi(tmpStrPtr1);
			if (tmpId <= 0 || tmpId > CTNC_MAX_NUMBER_OF_RESOURCE) {
				DBGERR(("Invalid resource Id"));

				errorCode = SEC_INVALID_INPUT;
				break;
			}

			tmpStrPtr1 = NULL;
			for (loopIndex = requestUrlReadIndex; loopIndex < requestUrlLength; loopIndex++) {
				if ('/' == restUrl[loopIndex]) {
					restUrl[loopIndex] = 0;
					tmpStrPtr1 = &restUrl[loopIndex + 1];
					requestUrlReadIndex = loopIndex + 2;
					break;
				}
			}
			if (NULL == tmpStrPtr2) {
				DBGERR(("Failed to get timeout"));

				errorCode = SEC_MISSING_INPUT;
				break;
			}
			tmpVal = atoi(tmpStrPtr2);

			if (NULL == tmpStrPtr1) {
				DBGERR(("Failed to get value"));

				errorCode = SEC_MISSING_INPUT;
				break;
			}
			writeIndex = atoi(tmpStrPtr1);

			if (NULL != (tmr = TMR_addTimer(tmpId, tmpVal, writeIndex))) {
				*responseBufferLength = snprintf(
											responseBuffer,
											*responseBufferLength,
											"errorCode:%d|messageId:%s|request:%s" \
											"#tmrId:%d|resId:%d|timeout:%d|value:%d",
											SEC_OK, messageId, command,
											tmr->id,
											tmr->resId,
											tmr->timeout,
											tmr->value);
				errorCode = SEC_OK;
			} else {
				DBGERR(("Could not add timer"));

				errorCode = SEC_SYSTEM_CALL_FAILURE;
			}

		} else if (0 == strcmp(command, "rtmr")) {
			// Name		:: Remove timer entry
			// Format:: rtmr/<Timer ID>

			if (NULL == tmpStrPtr1) {
				DBGERR(("Failed to get callback ID"));

				errorCode = SEC_MISSING_INPUT;
				break;
			}

			tmpId = atoi(tmpStrPtr1);

			if (RES_INVALID_ID == tmpId) {
				DBGERR(("Invalid timer ID"));

				errorCode = SEC_INVALID_INPUT;
				break;
			}

			if (0 == TMR_removeTimer(tmpId)) {
				*responseBufferLength = snprintf(
											responseBuffer,
											*responseBufferLength,
											"errorCode:%d|messageId:%s|request:%s",
											SEC_OK, messageId, command);
				errorCode = SEC_OK;
			} else {
				DBGERR(("Could not remove callback"));

				errorCode = SEC_SYSTEM_CALL_FAILURE;
			}
		} else {
			DBGERR(("Invalid command type"));
			errorCode = SEC_INVALID_INPUT;
			break;
		}

		break;
	}

	if (SEC_OK != errorCode && SEC_RESPONSE != errorCode) {
		*responseBufferLength = snprintf(
									responseBuffer,
									*responseBufferLength,
									"errorCode:%d|messageId:%s|request:%s",
									errorCode, messageId, command);

	}

	return errorCode;
}

LOCAL uint8_t ICACHE_FLASH_ATTR udpRequestBuffer[CTNC_MAX_UDP_REQUEST_BUFFER_SIZE];
LOCAL uint8_t ICACHE_FLASH_ATTR udpResponseBuffer[CTNC_MAX_UDP_RESPONSE_BUFFER_SIZE];

int32_t ICACHE_FLASH_ATTR sendUDPData(
							uint8_t * 		message,
							int32_t 		messageLength)
{
	int32_t 	status = -1;
    int32_t 	sinSize;
    int32_t 	remoteSocket;
    struct sockaddr_in remoteSocketAddress;


    DBGINF(("Sending broadcast message %d ==> [%s]",
    	messageLength, message));

	do {
		if (-1 == (remoteSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP))) {
			DBGERR(("Remote socket open call failed, status: %d", remoteSocket));
			break;
		}
		DBGINF(("Created remote socket: %d", remoteSocket));

		bzero(&remoteSocketAddress, sizeof(struct sockaddr_in));
		remoteSocketAddress.sin_family = AF_INET;
		remoteSocketAddress.sin_addr.s_addr = htonl(INADDR_BROADCAST);
		remoteSocketAddress.sin_port = htons(CTNC_UDP_SERVER_PORT);

		sinSize = sizeof(remoteSocketAddress);
		if (0 > (status = sendto(
							remoteSocket,
							message,
							messageLength, 0,
							(struct sockaddr *) &remoteSocketAddress,
							sinSize))) {
			DBGERR(("Socket sendto failed, status: %d", status));
		} else {
			DBGINF(("Socket sendto %d bytes", status));
			status = 0;
		}
	} while (0);

    if (remoteSocket) {
    	close(remoteSocket);
    }

    return status;
}

LOCAL void ICACHE_FLASH_ATTR udpReceiveTask(void *pvParameters)
{
    struct sockaddr_in 	serverSocketAddress;
    struct sockaddr_in 	clientSocketAddress;
    int32_t 			serverSocket;
    int32_t 			clientSocket;
    int32_t 			numberOfBytes;
    int32_t				optionValue;
    int32_t				status;
    socklen_t 			sinSize;
    uint8_t * 			ptrSendBuffer;
    uint16_t			responseBufferLength;

	DBGINF(("UDP Server started"));
	vTaskDelay(10);
	DBGINF(("UDP Server entering main loop"));

    while (1) {
        do {
        	if (-1 == (serverSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP))) {
                DBGERR(("Socket open call failed, status: %d", serverSocket));
                break;
            }
            DBGINF(("Created socket: %d", serverSocket));

            bzero(&serverSocketAddress, sizeof(struct sockaddr_in));
            serverSocketAddress.sin_family = AF_INET;
            serverSocketAddress.sin_addr.s_addr = htonl(INADDR_ANY);
            serverSocketAddress.sin_port = htons(CTNC_UDP_SERVER_PORT);

            if (-1 == bind(serverSocket, (struct sockaddr *)(&serverSocketAddress), sizeof(struct sockaddr))) {
                DBGERR(("Socket bind fail"));
                break;
            }
            DBGINF(("Socket bind port: %d", ntohs(serverSocketAddress.sin_port)));

            while(1) {
            	sinSize = sizeof(clientSocketAddress);
            	bzero(&udpRequestBuffer[0], CTNC_MAX_UDP_REQUEST_BUFFER_SIZE);
            	ptrSendBuffer = NULL;

            	DBGINF(("Waiting for UDP data..."));

            	if (0 > (numberOfBytes = recvfrom(
											serverSocket,
											udpRequestBuffer,
											CTNC_MAX_UDP_REQUEST_BUFFER_SIZE - 1, 0,
											(struct sockaddr *) &clientSocketAddress,
											&sinSize))) {
            		DBGERR(("UDP receive data failed, status: %d", numberOfBytes));
            		continue;
            	}
                DBGINF(("UDP request from %s %d", inet_ntoa(clientSocketAddress.sin_addr), htons(clientSocketAddress.sin_port)));
                DBGINF(("Read data success %d >> [%s]", numberOfBytes, udpRequestBuffer));

                sinSize = sizeof(clientSocketAddress);
				bzero(udpResponseBuffer, CTNC_MAX_UDP_RESPONSE_BUFFER_SIZE);
				responseBufferLength = CTNC_MAX_UDP_RESPONSE_BUFFER_SIZE - 1;
				status = processRequest(
							udpRequestBuffer,
							udpResponseBuffer,
							&responseBufferLength);

				if (SEC_RESPONSE != status) {
					DBGINF(("UDP sending response %d >> [%s]", responseBufferLength, udpResponseBuffer));
					if (0 > (status = sendto(
										serverSocket,
										udpResponseBuffer,
										responseBufferLength, 0,
										(struct sockaddr *) &clientSocketAddress,
										sinSize))) {
						DBGERR(("Socket sendto failed, status: %d", status));
					} else {
						vTaskDelay(10);
					}
				}
            }
        } while (0);

        close(serverSocket);

        DBGERR(("UDP server looping, This is not normal behavior"));
        vTaskDelay(5000);
    }

    DBGERR(("QUITING UDP SERVER, This is never expected"));
    vTaskDelete(NULL);
}

int32_t ICACHE_FLASH_ATTR SERVER_Init(void)
{
	int32_t status = 0;
	
	status = xTaskCreate(
				udpReceiveTask,
				"udp",
				CTNC_UDP_TASK_STACK_SIZE,
				NULL, 2, NULL);
	
	return status;
}

#endif /* !ENABLE_SENSOR */

