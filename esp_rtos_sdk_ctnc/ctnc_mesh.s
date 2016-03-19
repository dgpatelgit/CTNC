	.file	"ctnc_mesh.c"
	.text
.Ltext0:
	.literal_position
	.literal .LC0, nodeId
	.align	4
	.global	MESH_getNodeID
	.type	MESH_getNodeID, @function
MESH_getNodeID:
.LFB0:
	.file 1 "user/ctnc_mesh.c"
	.loc 1 6 0
	addi	sp, sp, -32
.LCFI0:
	s32i.n	a13, sp, 20
.LCFI1:
	.loc 1 7 0
	l32r	a13, .LC0
	.loc 1 6 0
	s32i.n	a0, sp, 28
	s32i.n	a12, sp, 24
.LCFI2:
	.loc 1 7 0
	l8ui	a2, a13, 0
	bnez.n	a2, .L2
	.loc 1 7 0 is_stmt 0 discriminator 1
	l8ui	a2, a13, 1
	bnez.n	a2, .L2
	.loc 1 7 0 discriminator 2
	l8ui	a12, a13, 2
	bnez.n	a12, .L2
.LVL0:
.LBB2:
	.loc 1 14 0 is_stmt 1
	mov.n	a3, sp
	movi.n	a2, 1
	.loc 1 12 0
	s32i.n	a12, sp, 0
	s16i	a12, sp, 4
	.loc 1 14 0
	call0	wifi_get_macaddr
.LVL1:
	beqz.n	a2, .L2
	mov.n	a6, a13
	movi.n	a4, 9
	mov.n	a2, a12
	mov.n	a3, a12
	.loc 1 23 0
	mov.n	a7, a12
.LVL2:
.L7:
	add.n	a5, sp, a3
	.loc 1 17 0
	bnez.n	a2, .L4
.LVL3:
	.loc 1 18 0
	l8ui	a2, a5, 0
	srli	a2, a2, 4
	addi	a2, a2, 75
	s8i	a2, a6, 0
.LVL4:
	.loc 1 19 0
	movi.n	a2, 1
	j	.L5
.LVL5:
.L4:
	.loc 1 21 0
	l8ui	a2, a5, 0
.LVL6:
	.loc 1 22 0
	addi.n	a3, a3, 1
.LVL7:
	.loc 1 21 0
	extui	a2, a2, 0, 4
	addi	a2, a2, 75
	s8i	a2, a6, 0
	.loc 1 22 0
	extui	a3, a3, 0, 8
.LVL8:
	.loc 1 23 0
	movi.n	a2, 0
.LVL9:
.L5:
	addi.n	a4, a4, -1
	.loc 1 26 0
	addi	a5, a3, -6
	extui	a4, a4, 0, 8
	moveqz	a3, a7, a5
.LVL10:
	addi.n	a6, a6, 1
.LVL11:
	.loc 1 15 0
	bnez.n	a4, .L7
.LVL12:
.L2:
.LBE2:
	.loc 1 34 0
	l32i.n	a0, sp, 28
	mov.n	a2, a13
	l32i.n	a12, sp, 24
	l32i.n	a13, sp, 20
	addi	sp, sp, 32
	ret.n
.LFE0:
	.size	MESH_getNodeID, .-MESH_getNodeID
	.local	nodeId
	.comm	nodeId,10,1
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
	.byte	0x8d
	.uleb128 0x3
	.byte	0x4
	.4byte	.LCFI2-.LCFI1
	.byte	0x80
	.uleb128 0x1
	.byte	0x8c
	.uleb128 0x2
	.align	4
.LEFDE0:
	.text
.Letext0:
	.file 2 "c:\\espressif\\xtensa-lx106-elf\\xtensa-lx106-elf\\include\\stdint.h"
	.file 3 "c:/Espressif/ESP8266_RTOS_SDK/include/espressif/c_types.h"
	.file 4 "c:/Espressif/ESP8266_RTOS_SDK/include/espressif/esp_wifi.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x192
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF25
	.byte	0x1
	.4byte	.LASF26
	.4byte	.LASF27
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF0
	.uleb128 0x3
	.4byte	.LASF7
	.byte	0x2
	.byte	0x2a
	.4byte	0x37
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
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF4
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF5
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF6
	.uleb128 0x3
	.4byte	.LASF8
	.byte	0x3
	.byte	0x2b
	.4byte	0x2c
	.uleb128 0x2
	.byte	0x4
	.byte	0x4
	.4byte	.LASF9
	.uleb128 0x2
	.byte	0x8
	.byte	0x4
	.4byte	.LASF10
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF11
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.4byte	.LASF12
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF13
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF14
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.4byte	.LASF15
	.uleb128 0x5
	.byte	0x4
	.4byte	0x53
	.byte	0x4
	.byte	0x7e
	.4byte	0xc3
	.uleb128 0x6
	.4byte	.LASF16
	.byte	0
	.uleb128 0x6
	.4byte	.LASF17
	.byte	0x1
	.uleb128 0x6
	.4byte	.LASF18
	.byte	0x2
	.byte	0
	.uleb128 0x3
	.4byte	.LASF19
	.byte	0x4
	.byte	0x82
	.4byte	0xa4
	.uleb128 0x7
	.byte	0x4
	.4byte	0x68
	.uleb128 0x8
	.4byte	.LASF28
	.byte	0x1
	.byte	0x5
	.4byte	0x148
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x148
	.uleb128 0x9
	.4byte	.LBB2
	.4byte	.LBE2-.LBB2
	.uleb128 0xa
	.4byte	.LASF20
	.byte	0x1
	.byte	0x9
	.4byte	0x2c
	.4byte	.LLST0
	.uleb128 0xa
	.4byte	.LASF21
	.byte	0x1
	.byte	0xa
	.4byte	0x2c
	.4byte	.LLST1
	.uleb128 0xa
	.4byte	.LASF22
	.byte	0x1
	.byte	0xb
	.4byte	0x2c
	.4byte	.LLST2
	.uleb128 0xb
	.4byte	.LASF23
	.byte	0x1
	.byte	0xc
	.4byte	0x14e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0xc
	.4byte	.LVL1
	.4byte	0x17f
	.uleb128 0xd
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x1
	.byte	0x31
	.uleb128 0xd
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x2
	.byte	0x71
	.sleb128 0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.4byte	0x2c
	.uleb128 0xe
	.4byte	0x2c
	.4byte	0x15e
	.uleb128 0xf
	.4byte	0x8f
	.byte	0x5
	.byte	0
	.uleb128 0xe
	.4byte	0x2c
	.4byte	0x16e
	.uleb128 0xf
	.4byte	0x8f
	.byte	0x9
	.byte	0
	.uleb128 0xb
	.4byte	.LASF24
	.byte	0x1
	.byte	0x3
	.4byte	0x15e
	.uleb128 0x5
	.byte	0x3
	.4byte	nodeId
	.uleb128 0x10
	.4byte	.LASF29
	.byte	0x4
	.byte	0xb5
	.4byte	0x9d
	.uleb128 0x11
	.4byte	0xc3
	.uleb128 0x11
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
	.uleb128 0x6
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
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
	.uleb128 0x9
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0xa
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
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0xb
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
	.uleb128 0xc
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x2111
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x10
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
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.4byte	.LVL0-.Ltext0
	.4byte	.LVL2-.Ltext0
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL2-.Ltext0
	.4byte	.LVL10-.Ltext0
	.2byte	0x9
	.byte	0x76
	.sleb128 0
	.byte	0x3
	.4byte	nodeId
	.byte	0x1c
	.byte	0x9f
	.4byte	.LVL10-.Ltext0
	.4byte	.LVL11-.Ltext0
	.2byte	0xb
	.byte	0x76
	.sleb128 0
	.byte	0x3
	.4byte	nodeId
	.byte	0x1c
	.byte	0x23
	.uleb128 0x1
	.byte	0x9f
	.4byte	.LVL11-.Ltext0
	.4byte	.LVL12-.Ltext0
	.2byte	0xb
	.byte	0x76
	.sleb128 -1
	.byte	0x3
	.4byte	nodeId
	.byte	0x1c
	.byte	0x23
	.uleb128 0x1
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST1:
	.4byte	.LVL0-.Ltext0
	.4byte	.LVL2-.Ltext0
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL2-.Ltext0
	.4byte	.LVL7-.Ltext0
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL7-.Ltext0
	.4byte	.LVL8-.Ltext0
	.2byte	0x3
	.byte	0x73
	.sleb128 -1
	.byte	0x9f
	.4byte	.LVL8-.Ltext0
	.4byte	.LVL12-.Ltext0
	.2byte	0x1
	.byte	0x53
	.4byte	0
	.4byte	0
.LLST2:
	.4byte	.LVL0-.Ltext0
	.4byte	.LVL2-.Ltext0
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL2-.Ltext0
	.4byte	.LVL3-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL3-.Ltext0
	.4byte	.LVL4-.Ltext0
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL4-.Ltext0
	.4byte	.LVL5-.Ltext0
	.2byte	0x2
	.byte	0x31
	.byte	0x9f
	.4byte	.LVL5-.Ltext0
	.4byte	.LVL6-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL8-.Ltext0
	.4byte	.LVL9-.Ltext0
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL9-.Ltext0
	.4byte	.LVL12-.Ltext0
	.2byte	0x1
	.byte	0x52
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
.LASF21:
	.string	"readIndex"
.LASF27:
	.string	"C:\\\\Espressif\\\\examples\\\\esp_rtos_sdk_ctnc"
.LASF3:
	.string	"short unsigned int"
.LASF9:
	.string	"float"
.LASF6:
	.string	"long long unsigned int"
.LASF25:
	.string	"GNU C89 5.1.0 -mlongcalls -mtext-section-literals -mno-serialize-volatile -g -Os -std=gnu90 -fno-inline-functions"
.LASF1:
	.string	"unsigned char"
.LASF11:
	.string	"long unsigned int"
.LASF28:
	.string	"MESH_getNodeID"
.LASF8:
	.string	"uint8"
.LASF18:
	.string	"MAX_IF"
.LASF26:
	.string	"user/ctnc_mesh.c"
.LASF24:
	.string	"nodeId"
.LASF10:
	.string	"double"
.LASF19:
	.string	"WIFI_INTERFACE"
.LASF16:
	.string	"STATION_IF"
.LASF4:
	.string	"unsigned int"
.LASF14:
	.string	"char"
.LASF7:
	.string	"uint8_t"
.LASF13:
	.string	"sizetype"
.LASF17:
	.string	"SOFTAP_IF"
.LASF5:
	.string	"long long int"
.LASF22:
	.string	"nibbleIndex"
.LASF2:
	.string	"short int"
.LASF20:
	.string	"loopIndex"
.LASF12:
	.string	"long int"
.LASF29:
	.string	"wifi_get_macaddr"
.LASF0:
	.string	"signed char"
.LASF15:
	.string	"_Bool"
.LASF23:
	.string	"apMac"
	.ident	"GCC: (GNU) 5.1.0"
