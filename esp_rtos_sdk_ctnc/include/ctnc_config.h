#ifndef __CTNC_CONFIG_H__
#define __CTNC_CONFIG_H__

// Length of Node ID including NULL character
#define CTNC_MAX_NODE_ID_LENGTH	(10)

// Max. number of resources
#define CTNC_MAX_NUMBER_OF_RESOURCE (6)

// Length of resource name including NULL character
#define CTNC_MAX_RESOURCE_NAME (20)

// Max. number of timers
#define CTNC_MAX_NUMBER_OF_TIMER (3)

// Max. number of virtual wire
#define CTNC_MAX_NUMBER_OF_VIRTUAL_WIRE (5)

// Button task details
#define CTNC_BTN_TASK_STACK_SIZE	(512)
#define CTNC_BTN_TASK_SLEEP 		(10)

// UDP task details
#define CTNC_UDP_SERVER_PORT 				(uint16_t)5656
#define CTNC_UDP_TASK_STACK_SIZE			(512)
#define CTNC_MAX_UDP_REQUEST_BUFFER_SIZE 	(512)
#define CTNC_MAX_UDP_RESPONSE_BUFFER_SIZE 	(512)

#undef ENABLE_SENSOR

#endif /* __CTNC_CONFIG_H__ */

