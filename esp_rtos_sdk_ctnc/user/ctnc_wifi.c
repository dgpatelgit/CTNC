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

#define WIFI_MONITORING_INTERVAL_IN_MS 	20000

LOCAL os_timer_t ICACHE_FLASH_ATTR  fWiFiTimer;

LOCAL void ICACHE_FLASH_ATTR fWiFiTimerCallback(void *arg)
{
	DBGINF(("fWiFiTimerCallback() kicked"));

    if (STATION_GOT_IP == wifi_station_get_connect_status())
    {
    	struct ip_info info = {0};

    	wifi_get_ip_info(STATION_IF, &info);
    	DBGINF(("Station details ::\nIP: %d.%d.%d.%d NM: %d.%d.%d.%d GW: %d.%d.%d.%d\n",
    			GET_READABLE_IP_ADDR(info.ip), GET_READABLE_IP_ADDR(info.netmask), GET_READABLE_IP_ADDR(info.gw)));

    	if (STATION_MODE != wifi_get_opmode())
    	{
    		DBGINF(("Setting up STATION MODE"));
    		wifi_set_opmode(STATION_MODE);
    	}
    }
    else if (STATIONAP_MODE != wifi_get_opmode())
    {
    	DBGINF(("Setting up BOTH MODE"));
    	wifi_set_opmode(STATIONAP_MODE);
    }
    else
    {
    	struct ip_info info = {0};

    	wifi_get_ip_info(SOFTAP_IF, &info);
    	DBGINF(("AP details ::\nIP: %d.%d.%d.%d NM: %d.%d.%d.%d GW: %d.%d.%d.%d\n",
    			GET_READABLE_IP_ADDR(info.ip), GET_READABLE_IP_ADDR(info.netmask), GET_READABLE_IP_ADDR(info.gw)));
    }
}

int32_t ICACHE_FLASH_ATTR WIFI_Init(void)
{
	// Set up wifi mode to station and try to connect to previous AP
    wifi_station_set_auto_connect(true);
    wifi_station_set_reconnect_policy(true);
    wifi_set_opmode(STATION_MODE);

	os_timer_disarm(&fWiFiTimer);
	os_timer_setfn(&fWiFiTimer, (os_timer_func_t *)fWiFiTimerCallback, (void *)0);
	os_timer_arm(&fWiFiTimer, WIFI_MONITORING_INTERVAL_IN_MS, 1);
	
	return (0);
}
