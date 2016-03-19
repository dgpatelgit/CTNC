#ifndef __CTNC_RES_H__
#define __CTNC_RES_H__

// This was defined in the old SDK.
#ifndef GPIO_OUTPUT_SET
#define GPIO_OUTPUT_SET(gpio_no, bit_value) \
	gpio_output_set(bit_value<<gpio_no, ((~bit_value)&0x01)<<gpio_no, 1<<gpio_no,0)
#endif

#define GPIO_WRITE(gpioNumber, newValue) \
			DBGINF(("Before DIR Register: 0x08X", GPIO_REG_READ(GPIO_ENABLE_ADDRESS))); \
			GPIO_REG_WRITE(GPIO_ENABLE_ADDRESS, ((GPIO_REG_READ(GPIO_ENABLE_ADDRESS) | (0x01 << GPIO_ID_PIN(gpioNumber))))); \
			DBGINF(("After DIR Register: 0x08X", GPIO_REG_READ(GPIO_ENABLE_ADDRESS))); \
			DBGINF(("Before Value Register: 0x08X", GPIO_REG_READ(GPIO_IN_ADDRESS))); \
			GPIO_REG_WRITE(GPIO_OUT_ADDRESS, (((GPIO_REG_READ(GPIO_IN_ADDRESS) & !(0x01 << GPIO_ID_PIN(gpioNumber))) | ((newValue & 0x01) << (GPIO_ID_PIN(gpioNumber)))))); \
			DBGINF(("After Value Register: 0x08X", GPIO_REG_READ(GPIO_IN_ADDRESS)))

#define GPIO_SET_OUT_MODE(gpioNumber) \
			(GPIO_SET_REG_MASK(GPIO_ENABLE_ADDRESS, (0x01 << GPIO_ID_PIN(gpioNumber))))

#define GPIO_READ(gpioNumber) \
			((GPIO_REG_READ(GPIO_IN_ADDRESS)  >> (GPIO_ID_PIN(gpioNumber))) & 0x01)

#define GPIO_WRITE_LOW(gpioNumber) \
			(GPIO_CLEAR_REG_MASK(GPIO_OUT_ADDRESS, (0x01 << GPIO_ID_PIN(gpioNumber))))

#define GPIO_WRITE_HIGH(gpioNumber) \
			(GPIO_SET_REG_MASK(GPIO_OUT_ADDRESS, (0x01 << GPIO_ID_PIN(gpioNumber))))

#define RES_INVALID_ID 	0

typedef enum _CTNC_RES_TYPE_ {
	CTNC_RES_TYPE_INVALID = 0,

	CTNC_RES_TYPE_INTERNAL,
	CTNC_RES_TYPE_NOT_CONNECTED,
	CTNC_RES_TYPE_BINARY_INPUT,
	CTNC_RES_TYPE_BINARY_OUTPUT,

	CTNC_RES_TYPE_LAST
} CTNC_RES_TYPE;

typedef struct _CTNC_RES_ {
	uint32_t		id;

	uint8_t			gpioNumber;
	uint8_t			gpioFunc;
	uint8_t			gpioIndicator;
	uint32_t		gpioName;

	CTNC_RES_TYPE 	type;
	uint16_t		lacheValue;
	uint16_t 		value;
	uint8_t 		name[CTNC_MAX_RESOURCE_NAME + 1];
} CTNC_RES;

extern int32_t ICACHE_FLASH_ATTR RES_Init(void);

#endif /* __CTNC_RES_H__ */
