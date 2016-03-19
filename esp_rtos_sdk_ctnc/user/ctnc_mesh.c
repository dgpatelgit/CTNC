#include "ctnc_common.h"

LOCAL ICACHE_FLASH_ATTR uint8_t nodeId[CTNC_MAX_NODE_ID_LENGTH] = {0};

uint8_t * ICACHE_FLASH_ATTR MESH_getNodeID(void)
{
	if (0 == nodeId[0] && 0 == nodeId[1] && 0 == nodeId[2])
	{
		uint8_t loopIndex = 0;
		uint8_t	readIndex = 0;
		uint8_t nibbleIndex = 0;
		uint8_t apMac[6] = {0};

		if ( wifi_get_macaddr(SOFTAP_IF, &apMac[0])) {
			for (loopIndex = 0; loopIndex < CTNC_MAX_NODE_ID_LENGTH - 1; loopIndex++)
			{
				if (0 == nibbleIndex) {
					nodeId[loopIndex] = 'K' + (apMac[readIndex] >> 4);
					nibbleIndex++;
				} else {
					nodeId[loopIndex] = 'K' + (apMac[readIndex] & 0x0F);
					readIndex++;
					nibbleIndex = 0;
				}

				if (6 == readIndex) readIndex = 0;
			}
		}
	}

	DBGINF(("Unique Node ID: %s", nodeId));

	return &nodeId[0];
}


