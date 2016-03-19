	.file	"ctnc_wifi.c"
	.text
.Ltext0:
	.literal_position
	.align	4
	.type	fWiFiTimerCallback, @function
fWiFiTimerCallback:
.LFB0:
	.file 1 "user/ctnc_wifi.c"
	.loc 1 18 0
.LVL0:
	addi	sp, sp, -32
.LCFI0:
	s32i.n	a0, sp, 28
.LCFI1:
	.loc 1 21 0
	call0	wifi_station_get_connect_status
.LVL1:
	bnei	a2, 5, .L2
.LBB9:
	.loc 1 23 0
	movi.n	a4, 0xc
	movi.n	a3, 0
	mov.n	a2, sp
	call0	memset
.LVL2:
	.loc 1 25 0
	mov.n	a3, sp
	movi.n	a2, 0
	call0	wifi_get_ip_info
.LVL3:
	.loc 1 29 0
	call0	wifi_get_opmode
.LVL4:
	beqi	a2, 1, .L1
	.loc 1 32 0
	movi.n	a2, 1
	j	.L9
.L2:
.LBE9:
	.loc 1 35 0
	call0	wifi_get_opmode
.LVL5:
	beqi	a2, 3, .L5
	.loc 1 38 0
	movi.n	a2, 3
.L9:
	call0	wifi_set_opmode
.LVL6:
	j	.L1
.L5:
.LVL7:
.LBB10:
.LBB11:
	.loc 1 42 0
	movi.n	a3, 0
	movi.n	a4, 0xc
	mov.n	a2, sp
	call0	memset
.LVL8:
	.loc 1 44 0
	mov.n	a3, sp
	movi.n	a2, 1
	call0	wifi_get_ip_info
.LVL9:
.L1:
.LBE11:
.LBE10:
	.loc 1 48 0
	l32i.n	a0, sp, 28
	addi	sp, sp, 32
	ret.n
.LFE0:
	.size	fWiFiTimerCallback, .-fWiFiTimerCallback
	.literal_position
	.literal .LC0, fWiFiTimer
	.literal .LC1, fWiFiTimerCallback
	.literal .LC2, 20000
	.align	4
	.global	WIFI_Init
	.type	WIFI_Init, @function
WIFI_Init:
.LFB1:
	.loc 1 51 0
	addi	sp, sp, -16
.LCFI2:
	.loc 1 53 0
	movi.n	a2, 1
	.loc 1 51 0
	s32i.n	a0, sp, 12
	s32i.n	a12, sp, 8
.LCFI3:
	.loc 1 53 0
	call0	wifi_station_set_auto_connect
.LVL10:
	.loc 1 54 0
	movi.n	a2, 1
	call0	wifi_station_set_reconnect_policy
.LVL11:
	.loc 1 55 0
	movi.n	a2, 1
	call0	wifi_set_opmode
.LVL12:
	.loc 1 57 0
	l32r	a12, .LC0
	mov.n	a2, a12
	call0	os_timer_disarm
.LVL13:
	.loc 1 58 0
	l32r	a3, .LC1
	mov.n	a2, a12
	movi.n	a4, 0
	call0	os_timer_setfn
.LVL14:
	.loc 1 59 0
	l32r	a3, .LC2
	mov.n	a2, a12
	movi.n	a4, 1
	call0	os_timer_arm
.LVL15:
	.loc 1 62 0
	l32i.n	a0, sp, 12
	movi.n	a2, 0
	l32i.n	a12, sp, 8
	addi	sp, sp, 16
	ret.n
.LFE1:
	.size	WIFI_Init, .-WIFI_Init
	.local	fWiFiTimer
	.comm	fWiFiTimer,28,4
	.section	.debug_frame,"",@progbits
.Lframe0:
	.4byte	.LECIE0-.LSCIE0
.LSCIE0:
	.4byte	0xffffffff
	.byte	0x3
	.string	""
	.uleb128 0x1
	.sleb128 -4
	.uleb128 0
	.byte	0xc
	.uleb128 0x1
	.uleb128 0
	.align	4
.LECIE0:
.LSFDE0:
	.4byte	.LEFDE0-.LASFDE0
.LASFDE0:
	.4byte	.Lframe0
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
	.byte	0x4
	.4byte	.LCFI0-.LFB0
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.4byte	.LCFI1-.LCFI0
	.byte	0x80
	.uleb128 0x1
	.align	4
.LEFDE0:
.LSFDE2:
	.4byte	.LEFDE2-.LASFDE2
.LASFDE2:
	.4byte	.Lframe0
	.4byte	.LFB1
	.4byte	.LFE1-.LFB1
	.byte	0x4
	.4byte	.LCFI2-.LFB1
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.4byte	.LCFI3-.LCFI2
	.byte	0x80
	.uleb128 0x1
	.byte	0x8c
	.uleb128 0x2
	.align	4
.LEFDE2:
	.text
.Letext0:
	.file 2 "c:\\espressif\\xtensa-lx106-elf\\xtensa-lx106-elf\\include\\stdint.h"
	.file 3 "c:/Espressif/ESP8266_RTOS_SDK/include/espressif/c_types.h"
	.file 4 "c:/Espressif/ESP8266_RTOS_SDK/include/espressif/esp_wifi.h"
	.file 5 "c:/Espressif/ESP8266_RTOS_SDK/include/lwip/ipv4/lwip/ip4_addr.h"
	.file 6 "c:/Espressif/ESP8266_RTOS_SDK/include/espressif/esp_sta.h"
	.file 7 "c:/Espressif/ESP8266_RTOS_SDK/include/espressif/esp_timer.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x4dd
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF59
	.byte	0x1
	.4byte	.LASF60
	.4byte	.LASF61
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF0
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF1
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.4byte	.LASF2
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0x3
	.4byte	.LASF4
	.byte	0x2
	.byte	0x50
	.4byte	0x4c
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x3
	.4byte	.LASF5
	.byte	0x2
	.byte	0x51
	.4byte	0x5e
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF6
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF7
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF8
	.uleb128 0x3
	.4byte	.LASF9
	.byte	0x3
	.byte	0x28
	.4byte	0x53
	.uleb128 0x3
	.4byte	.LASF10
	.byte	0x3
	.byte	0x34
	.4byte	0x53
	.uleb128 0x2
	.byte	0x4
	.byte	0x4
	.4byte	.LASF11
	.uleb128 0x2
	.byte	0x8
	.byte	0x4
	.4byte	.LASF12
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF13
	.uleb128 0x5
	.byte	0x4
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.4byte	.LASF14
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF15
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF16
	.uleb128 0x6
	.4byte	.LASF28
	.byte	0x4
	.byte	0x5
	.byte	0x2c
	.4byte	0xce
	.uleb128 0x7
	.4byte	.LASF30
	.byte	0x5
	.byte	0x2d
	.4byte	0x73
	.byte	0
	.byte	0
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.4byte	.LASF17
	.uleb128 0x8
	.byte	0x4
	.4byte	0x5e
	.byte	0x4
	.byte	0x33
	.4byte	0x100
	.uleb128 0x9
	.4byte	.LASF18
	.byte	0
	.uleb128 0x9
	.4byte	.LASF19
	.byte	0x1
	.uleb128 0x9
	.4byte	.LASF20
	.byte	0x2
	.uleb128 0x9
	.4byte	.LASF21
	.byte	0x3
	.uleb128 0x9
	.4byte	.LASF22
	.byte	0x4
	.byte	0
	.uleb128 0x3
	.4byte	.LASF23
	.byte	0x4
	.byte	0x39
	.4byte	0xd5
	.uleb128 0x8
	.byte	0x4
	.4byte	0x5e
	.byte	0x4
	.byte	0x7e
	.4byte	0x12a
	.uleb128 0x9
	.4byte	.LASF24
	.byte	0
	.uleb128 0x9
	.4byte	.LASF25
	.byte	0x1
	.uleb128 0x9
	.4byte	.LASF26
	.byte	0x2
	.byte	0
	.uleb128 0x3
	.4byte	.LASF27
	.byte	0x4
	.byte	0x82
	.4byte	0x10b
	.uleb128 0x6
	.4byte	.LASF29
	.byte	0xc
	.byte	0x4
	.byte	0x84
	.4byte	0x164
	.uleb128 0xa
	.string	"ip"
	.byte	0x4
	.byte	0x85
	.4byte	0xb5
	.byte	0
	.uleb128 0x7
	.4byte	.LASF31
	.byte	0x4
	.byte	0x86
	.4byte	0xb5
	.byte	0x4
	.uleb128 0xa
	.string	"gw"
	.byte	0x4
	.byte	0x87
	.4byte	0xb5
	.byte	0x8
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.4byte	0x5e
	.byte	0x6
	.byte	0xf5
	.4byte	0x195
	.uleb128 0x9
	.4byte	.LASF32
	.byte	0
	.uleb128 0x9
	.4byte	.LASF33
	.byte	0x1
	.uleb128 0x9
	.4byte	.LASF34
	.byte	0x2
	.uleb128 0x9
	.4byte	.LASF35
	.byte	0x3
	.uleb128 0x9
	.4byte	.LASF36
	.byte	0x4
	.uleb128 0x9
	.4byte	.LASF37
	.byte	0x5
	.byte	0
	.uleb128 0x3
	.4byte	.LASF38
	.byte	0x6
	.byte	0xfc
	.4byte	0x164
	.uleb128 0x3
	.4byte	.LASF39
	.byte	0x7
	.byte	0x21
	.4byte	0x1ab
	.uleb128 0xb
	.4byte	0x1b6
	.uleb128 0xc
	.4byte	0x9e
	.byte	0
	.uleb128 0x6
	.4byte	.LASF40
	.byte	0x1c
	.byte	0x7
	.byte	0x23
	.4byte	0x217
	.uleb128 0x7
	.4byte	.LASF41
	.byte	0x7
	.byte	0x24
	.4byte	0x217
	.byte	0
	.uleb128 0x7
	.4byte	.LASF42
	.byte	0x7
	.byte	0x25
	.4byte	0x9e
	.byte	0x4
	.uleb128 0x7
	.4byte	.LASF43
	.byte	0x7
	.byte	0x26
	.4byte	0x7e
	.byte	0x8
	.uleb128 0x7
	.4byte	.LASF44
	.byte	0x7
	.byte	0x27
	.4byte	0x7e
	.byte	0xc
	.uleb128 0x7
	.4byte	.LASF45
	.byte	0x7
	.byte	0x28
	.4byte	0x21d
	.byte	0x10
	.uleb128 0x7
	.4byte	.LASF46
	.byte	0x7
	.byte	0x29
	.4byte	0xce
	.byte	0x14
	.uleb128 0x7
	.4byte	.LASF47
	.byte	0x7
	.byte	0x2a
	.4byte	0x9e
	.byte	0x18
	.byte	0
	.uleb128 0xd
	.byte	0x4
	.4byte	0x1b6
	.uleb128 0xd
	.byte	0x4
	.4byte	0x1a0
	.uleb128 0x3
	.4byte	.LASF48
	.byte	0x7
	.byte	0x2b
	.4byte	0x1b6
	.uleb128 0xe
	.4byte	.LASF62
	.byte	0x1
	.byte	0x11
	.byte	0x1
	.4byte	0x264
	.uleb128 0xf
	.string	"arg"
	.byte	0x1
	.byte	0x11
	.4byte	0x9e
	.uleb128 0x10
	.4byte	0x256
	.uleb128 0x11
	.4byte	.LASF49
	.byte	0x1
	.byte	0x17
	.4byte	0x135
	.byte	0
	.uleb128 0x12
	.uleb128 0x11
	.4byte	.LASF49
	.byte	0x1
	.byte	0x2a
	.4byte	0x135
	.byte	0
	.byte	0
	.uleb128 0x13
	.4byte	0x22e
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x34e
	.uleb128 0x14
	.4byte	0x23a
	.4byte	.LLST0
	.uleb128 0x15
	.4byte	.LBB9
	.4byte	.LBE9-.LBB9
	.4byte	0x2d6
	.uleb128 0x16
	.4byte	0x24a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x17
	.4byte	.LVL2
	.4byte	0x404
	.4byte	0x2b3
	.uleb128 0x18
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x71
	.sleb128 0
	.uleb128 0x18
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x18
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x1
	.byte	0x3c
	.byte	0
	.uleb128 0x17
	.4byte	.LVL3
	.4byte	0x421
	.4byte	0x2cc
	.uleb128 0x18
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x18
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x2
	.byte	0x71
	.sleb128 0
	.byte	0
	.uleb128 0x19
	.4byte	.LVL4
	.4byte	0x441
	.byte	0
	.uleb128 0x15
	.4byte	.LBB10
	.4byte	.LBE10-.LBB10
	.4byte	0x332
	.uleb128 0x14
	.4byte	0x23a
	.4byte	.LLST1
	.uleb128 0x1a
	.4byte	.LBB11
	.4byte	.LBE11-.LBB11
	.uleb128 0x16
	.4byte	0x257
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x17
	.4byte	.LVL8
	.4byte	0x404
	.4byte	0x31b
	.uleb128 0x18
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x71
	.sleb128 0
	.uleb128 0x18
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x18
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x1
	.byte	0x3c
	.byte	0
	.uleb128 0x1b
	.4byte	.LVL9
	.4byte	0x421
	.uleb128 0x18
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x18
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x2
	.byte	0x71
	.sleb128 0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x19
	.4byte	.LVL1
	.4byte	0x44c
	.uleb128 0x19
	.4byte	.LVL5
	.4byte	0x441
	.uleb128 0x19
	.4byte	.LVL6
	.4byte	0x458
	.byte	0
	.uleb128 0x1c
	.4byte	.LASF63
	.byte	0x1
	.byte	0x32
	.4byte	0x41
	.4byte	.LFB1
	.4byte	.LFE1-.LFB1
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x3f3
	.uleb128 0x17
	.4byte	.LVL10
	.4byte	0x46d
	.4byte	0x37a
	.uleb128 0x18
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.uleb128 0x17
	.4byte	.LVL11
	.4byte	0x482
	.4byte	0x38d
	.uleb128 0x18
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.uleb128 0x17
	.4byte	.LVL12
	.4byte	0x458
	.4byte	0x3a0
	.uleb128 0x18
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.uleb128 0x17
	.4byte	.LVL13
	.4byte	0x497
	.4byte	0x3b4
	.uleb128 0x18
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7c
	.sleb128 0
	.byte	0
	.uleb128 0x17
	.4byte	.LVL14
	.4byte	0x4ae
	.4byte	0x3d6
	.uleb128 0x18
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7c
	.sleb128 0
	.uleb128 0x18
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x5
	.byte	0x3
	.4byte	fWiFiTimerCallback
	.uleb128 0x18
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.uleb128 0x1b
	.4byte	.LVL15
	.4byte	0x4c9
	.uleb128 0x18
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7c
	.sleb128 0
	.uleb128 0x18
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x3
	.byte	0xa
	.2byte	0x4e20
	.uleb128 0x18
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.byte	0
	.uleb128 0x1d
	.4byte	.LASF64
	.byte	0x1
	.byte	0xf
	.4byte	0x223
	.uleb128 0x5
	.byte	0x3
	.4byte	fWiFiTimer
	.uleb128 0x1e
	.4byte	.LASF56
	.4byte	0x9e
	.4byte	0x421
	.uleb128 0xc
	.4byte	0x9e
	.uleb128 0xc
	.4byte	0x4c
	.uleb128 0xc
	.4byte	0xa7
	.byte	0
	.uleb128 0x1f
	.4byte	.LASF52
	.byte	0x4
	.byte	0x96
	.4byte	0xce
	.4byte	0x43b
	.uleb128 0xc
	.4byte	0x12a
	.uleb128 0xc
	.4byte	0x43b
	.byte	0
	.uleb128 0xd
	.byte	0x4
	.4byte	0x135
	.uleb128 0x20
	.4byte	.LASF50
	.byte	0x4
	.byte	0x4e
	.4byte	0x100
	.uleb128 0x21
	.4byte	.LASF51
	.byte	0x6
	.2byte	0x105
	.4byte	0x195
	.uleb128 0x1f
	.4byte	.LASF53
	.byte	0x4
	.byte	0x6c
	.4byte	0xce
	.4byte	0x46d
	.uleb128 0xc
	.4byte	0x100
	.byte	0
	.uleb128 0x1f
	.4byte	.LASF54
	.byte	0x6
	.byte	0xdb
	.4byte	0xce
	.4byte	0x482
	.uleb128 0xc
	.4byte	0xce
	.byte	0
	.uleb128 0x1f
	.4byte	.LASF55
	.byte	0x6
	.byte	0xf3
	.4byte	0xce
	.4byte	0x497
	.uleb128 0xc
	.4byte	0xce
	.byte	0
	.uleb128 0x22
	.4byte	.LASF57
	.byte	0x7
	.byte	0x5b
	.4byte	0x4a8
	.uleb128 0xc
	.4byte	0x4a8
	.byte	0
	.uleb128 0xd
	.byte	0x4
	.4byte	0x223
	.uleb128 0x22
	.4byte	.LASF58
	.byte	0x7
	.byte	0x47
	.4byte	0x4c9
	.uleb128 0xc
	.4byte	0x4a8
	.uleb128 0xc
	.4byte	0x21d
	.uleb128 0xc
	.4byte	0x9e
	.byte	0
	.uleb128 0x23
	.4byte	.LASF65
	.byte	0x7
	.byte	0x52
	.uleb128 0xc
	.4byte	0x4a8
	.uleb128 0xc
	.4byte	0x7e
	.uleb128 0xc
	.4byte	0xce
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x4
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0xb
	.byte	0x1
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x2111
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x4109
	.byte	0
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.4byte	.LVL0-.Ltext0
	.4byte	.LVL1-1-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL1-1-.Ltext0
	.4byte	.LFE0-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST1:
	.4byte	.LVL7-.Ltext0
	.4byte	.LVL9-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
	.section	.debug_aranges,"",@progbits
	.4byte	0x1c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	0
	.4byte	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF36:
	.string	"STATION_CONNECT_FAIL"
.LASF45:
	.string	"timer_func"
.LASF65:
	.string	"os_timer_arm"
.LASF40:
	.string	"_os_timer_t"
.LASF2:
	.string	"short int"
.LASF52:
	.string	"wifi_get_ip_info"
.LASF15:
	.string	"sizetype"
.LASF46:
	.string	"timer_repeat_flag"
.LASF26:
	.string	"MAX_IF"
.LASF32:
	.string	"STATION_IDLE"
.LASF24:
	.string	"STATION_IF"
.LASF53:
	.string	"wifi_set_opmode"
.LASF42:
	.string	"timer_handle"
.LASF57:
	.string	"os_timer_disarm"
.LASF9:
	.string	"u32_t"
.LASF59:
	.string	"GNU C89 5.1.0 -mlongcalls -mtext-section-literals -mno-serialize-volatile -g -Os -std=gnu90 -fno-inline-functions"
.LASF28:
	.string	"ip_addr"
.LASF21:
	.string	"STATIONAP_MODE"
.LASF61:
	.string	"C:\\\\Espressif\\\\examples\\\\esp_rtos_sdk_ctnc"
.LASF60:
	.string	"user/ctnc_wifi.c"
.LASF11:
	.string	"float"
.LASF7:
	.string	"long long int"
.LASF56:
	.string	"memset"
.LASF39:
	.string	"os_timer_func_t"
.LASF35:
	.string	"STATION_NO_AP_FOUND"
.LASF22:
	.string	"MAX_MODE"
.LASF14:
	.string	"long int"
.LASF54:
	.string	"wifi_station_set_auto_connect"
.LASF37:
	.string	"STATION_GOT_IP"
.LASF30:
	.string	"addr"
.LASF29:
	.string	"ip_info"
.LASF34:
	.string	"STATION_WRONG_PASSWORD"
.LASF62:
	.string	"fWiFiTimerCallback"
.LASF1:
	.string	"unsigned char"
.LASF20:
	.string	"SOFTAP_MODE"
.LASF0:
	.string	"signed char"
.LASF8:
	.string	"long long unsigned int"
.LASF47:
	.string	"timer_arg"
.LASF5:
	.string	"uint32_t"
.LASF6:
	.string	"unsigned int"
.LASF38:
	.string	"STATION_STATUS"
.LASF3:
	.string	"short unsigned int"
.LASF19:
	.string	"STATION_MODE"
.LASF16:
	.string	"char"
.LASF64:
	.string	"fWiFiTimer"
.LASF4:
	.string	"int32_t"
.LASF51:
	.string	"wifi_station_get_connect_status"
.LASF17:
	.string	"_Bool"
.LASF41:
	.string	"timer_next"
.LASF10:
	.string	"uint32"
.LASF13:
	.string	"long unsigned int"
.LASF63:
	.string	"WIFI_Init"
.LASF12:
	.string	"double"
.LASF44:
	.string	"timer_period"
.LASF49:
	.string	"info"
.LASF31:
	.string	"netmask"
.LASF43:
	.string	"timer_expire"
.LASF48:
	.string	"os_timer_t"
.LASF23:
	.string	"WIFI_MODE"
.LASF55:
	.string	"wifi_station_set_reconnect_policy"
.LASF33:
	.string	"STATION_CONNECTING"
.LASF50:
	.string	"wifi_get_opmode"
.LASF18:
	.string	"NULL_MODE"
.LASF58:
	.string	"os_timer_setfn"
.LASF25:
	.string	"SOFTAP_IF"
.LASF27:
	.string	"WIFI_INTERFACE"
	.ident	"GCC: (GNU) 5.1.0"
