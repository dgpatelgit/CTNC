#ifndef __CTNC_MESH_H__
#define __CTNC_MESH_H__

#include "esp_common.h"

#include "ctnc_main.h"

#define GET_IP_UINT32(p1, p2, p3, p4) ( ((p4 & 0xFF) << 24) | ((p3 & 0xFF) << 16) | ((p2 & 0xFF) << 8) | (p2 & 0xFF) )
#define GET_READABLE_IP(addr) (addr & 0xFF), ((addr >> 8) & 0xFF), ((addr >> 16) & 0xFF), ((addr >> 24) & 0xFF)
#define GET_READABLE_IP_ADDR(ip) GET_READABLE_IP(ip.addr)

uint8_t * ICACHE_FLASH_ATTR MESH_getNodeID(void);

#endif /* __CTNC_MESH_H__ */
