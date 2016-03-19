#ifndef __CTNC_COMMON_H__
#define __CTNC_COMMON_H__

// Include all required header files here
#include "esp_common.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "ctnc_config.h"
#include "ctnc_main.h"
#include "ctnc_wifi.h"
#include "ctnc_mesh.h"
#include "ctnc_server.h"

#define GET_STRING(val) #val

#define DBGERR(msg) printf("ERR: "); printf msg; printf("\n")
#define DBGWRN(msg) printf("WRN: "); printf msg; printf("\n")
#define DBGINF(msg) //printf("INF: "); printf msg; printf("\n")

#endif /* __CTNC_COMMON_H__ */
