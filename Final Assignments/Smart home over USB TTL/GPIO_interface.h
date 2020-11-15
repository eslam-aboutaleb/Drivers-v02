 /* ******************************************************  */
 /*  GPIO_interface.h									    */
 /*  Version: 1.0											*/
 /*  Author : Eslam Ehab Aboutaleb							*/
 /* ******************************************************  */

#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

/* ***************************************************************************** */
/* Configurations that are essential to interface file */
/* Number of ports */
#define GPIO_NPORTS							(4)
/* Number of pins */
#define GPIO_NO_PINS						(32)
/* Number of pins per port */
#define GPIO_NPINS_PER_PORT					(8)
/* ***************************************************************************** */
								/* GPIO keywords */
/* ***************************************************************************** */
typedef unsigned char				GPIO_Port_t;
typedef unsigned char				GPIO_PortMode_t;
typedef unsigned char				GPIO_PortState_t;
typedef unsigned char				GPIO_Pin_t;
typedef unsigned char				GPIO_PinMode_t;
typedef unsigned char				GPIO_PinState_t;

/* ***************************************************************************** */
								/* GPIO Ports */
/* ***************************************************************************** */
#define GPIOA                       'A'
#define GPIOB                       'B'
#define GPIOC                       'C'
#define GPIOD                       'D'
#define GPIOE                       'E'
/* ***************************************************************************** */
								/* GPIO Pins */
/* ***************************************************************************** */
#define GPIO_PIN_0                  (0)
#define GPIO_PIN_1                  (1)
#define GPIO_PIN_2                  (2)
#define GPIO_PIN_3                  (3)
#define GPIO_PIN_4                  (4)
#define GPIO_PIN_5                  (5)
#define GPIO_PIN_6                  (6)
#define GPIO_PIN_7                  (7)

/* ***************************************************************************** */
							/* GPIO Direction values */
/* ***************************************************************************** */
#define GPIO_IN                     (0)
#define GPIO_OUT                    (1)
/* ***************************************************************************** */
							/* GPIO Level values */
/* ***************************************************************************** */
#define GPIO_LOW                    (0)
#define GPIO_HIGH                   (1)


/* ***************************************************************************** */
							/* GPIO pins group Data structures */
/* ***************************************************************************** */
typedef struct
{
	/* Member contains the ID of the Port that this channel belongs to */
	GPIO_Port_t xPort;
	/* Member contains the ID of the Channel*/
	GPIO_Pin_t xPin_Num;
	/* Member contains the mode of the channel */
	GPIO_PinMode_t xPin_Mode;
}GPIO_ConfigPin;

/* Data Structure required for initializing the GPIO Driver */
typedef struct
{
	GPIO_ConfigPin Pins[GPIO_NO_PINS];
} GPIO_ConfigType;


/* ***************************************************************************** */
							/*Functions prototype*/
/* ***************************************************************************** */

/* ***************************************************************************** */
/* Function		: 	GPIO_vInit
 * Return  		: 	void
 * Parameters	: 	xpGIPO_Config, type: GPIO_ConfigType (struct)
 * Description	: 	Function to initialize group of pins based on structure and pre-
 * -compiled number of bins
 */
/* ***************************************************************************** */
void GPIO_vInit(GPIO_ConfigType *xpGIPO_Config);

/* ***************************************************************************** */
/* Function		: 	GPIO_vInitPortPin
 * Return  		: 	void
 * Parameters	:	Copy_xGPIOx			, Type	:	GPIO_Port_t
 * 				  	Copy_xPinx			, Type	:	GPIO_Pin_t
 * 				  	Copy_xMode			, Type	:	GPIO_PinMode_t
 * Description	: 	Function to initialize port pins based on specific port and pin
 */
/* ***************************************************************************** */
void GPIO_vInitPortPin(GPIO_Port_t Copy_xGPIOx,GPIO_Pin_t Copy_xPinx ,GPIO_PinMode_t Copy_xMode);

/* ***************************************************************************** */
/* Function		: 	GPIO_vWritePortPin
 * Return  		: 	void
 * Parameters	:	Copy_xGPIOx			, Type	:	GPIO_Port_t
 * 				  	Copy_xPinx			, Type	:	GPIO_Pin_t
 * 				  	Copy_xVal			, Type	:	GPIO_PinState_t
 * Description	: 	Function to initialize port pins based on specific port and pin
 */
/* ***************************************************************************** */
void GPIO_vWritePortPin(GPIO_Port_t Copy_xGPIOx ,GPIO_Pin_t Copy_xPinx ,GPIO_PinState_t Copy_xVal);

/* ***************************************************************************** */
/* Function		: 	GPIO_xReadPortPin
 * Return  		: 	void
 * Parameters	:	Copy_xGPIOx		, Type	:	GPIO_Port_t
 * 				  	Copy_xPinx		, Type	:	GPIO_Pin_t
 * Description	: 	Function to read port pins based on specific port and pin
 */
/* ***************************************************************************** */
GPIO_PinState_t GPIO_xReadPortPin(GPIO_Port_t Copy_xGPIOx ,GPIO_Pin_t Copy_xPinx);

/* ***************************************************************************** */
/* Function		: 	GPIO_xFlipPortPin
 * Return  		: 	void
 * Parameters	:	Copy_xGPIOx		, Type	:	GPIO_Port_t
 * 				  	Copy_xPinx		, Type	:	GPIO_Pin_t
 * Description	: 	Function to read port pins based on specific port and pin
 */
/* ***************************************************************************** */
GPIO_PinState_t GPIO_xFlipPortPin(GPIO_Port_t Copy_xGPIOx ,GPIO_Pin_t Copy_xPinx);

/* ***************************************************************************** */
/* Function		: 	GPIO_vWritePort
 * Return  		: 	void
 * Parameters	:	Copy_xGPIOx		, Type	:	GPIO_Port_t
 * 					Copy_xMode		, Type	:	GPIO_PortMode_t
 * Description	: 	Function to write value to the whole port
 */
/* ***************************************************************************** */
void GPIO_vInitPort(GPIO_Port_t Copy_xGPIOx ,GPIO_PortMode_t Copy_xMode);

/* ***************************************************************************** */
/* Function		: 	GPIO_vWritePort
 * Return  		: 	void
 * Parameters	:	Copy_xGPIOx		, Type	:	GPIO_Port_t
 * 					Copy_xVal		, Type	:	GPIO_PortState_t
 * Description	: 	Function to write value to the whole port
 */
/* ***************************************************************************** */
void GPIO_vWritePort(GPIO_Port_t Copy_xGPIOx ,GPIO_PortState_t Copy_xVal);

#endif /* GPIO_INTERFACE_H_ */
