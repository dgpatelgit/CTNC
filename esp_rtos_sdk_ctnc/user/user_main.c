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

LOCAL void ICACHE_FLASH_ATTR UART_SetBaudrate(uint8 uart_no, uint32 baud_rate)
{
	uart_div_modify(uart_no, UART_CLK_FREQ / baud_rate);
}

/******************************************************************************
 * FunctionName : user_init
 * Description  : entry of user application, init user function here
 * Parameters   : none
 * Returns      : none
*******************************************************************************/
void ICACHE_FLASH_ATTR user_init(void)
{
	UART_SetBaudrate(0,9600);

    DBGINF(("SDK version:%s\n", system_get_sdk_version()));

    RES_Init();

	WIFI_Init();
	
    SERVER_Init();
}

