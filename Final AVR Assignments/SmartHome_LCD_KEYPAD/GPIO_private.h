 /* ******************************************************  */
 /*  GPIO_privat.h										    */
 /*  Version: 1.0											*/
 /*  Author : Eslam Ehab Aboutaleb							*/
 /* ******************************************************  */

#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_


/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for GPIO Init Channel */
#define GPIO_INIT_CHANNEL_SID           (uint8)0x05

/* Service ID for GPIO read Channel */
#define GPIO_READ_CHANNEL_SID           (uint8)0x00

/* Service ID for GPIO write Channel */
#define GPIO_WRITE_CHANNEL_SID          (uint8)0x01

/* Service ID for GPIO read Port */
#define GPIO_READ_PORT_SID              (uint8)0x02

/* Service ID for GPIO write Port */
#define GPIO_WRITE_PORT_SID             (uint8)0x03

/* Service ID for GPIO init Port */
#define GPIO_INIT_PORT_SID              (uint8)0x04

/* Service ID for GPIO Init Channel */
#define GPIO_INIT_SID                   (uint8)0x10

/* Service ID for GPIO flip Channel */
#define GPIO_FLIP_CHANNEL_SID           (uint8)0x11

/*******************************************************************************
 *                      GPIO Error Codes                                        *
 *******************************************************************************/
/* Error Invalid Channel */
#define GPIO_E_PARAM_INVALID_CHANNEL_ID (uint8)0x0A

/* Error API service called with NULL pointer parameter */
#define GPIO_E_PARAM_STATE              (uint8)0x10

/* Error Invalid Port */
#define GPIO_E_PARAM_INVALID_PORT_ID    (uint8)0x14

/* Error initialize GPIO with null pointer */
#define GPIO_E_PARAM_POINTER            (uint8)0x20

/* ***************************************************************************** */
/*						 GPIO validation Functions like macros					 */
/* ***************************************************************************** */
/* GPIO Port validation */
#define GPIO_IS_VALID_PORT(PORTx)					(GPIOA == PORTx || GPIOB == PORTx ||\
		GPIOC == PORTx	|| GPIOD == PORTx ||\
		GPIOD == PORTx)

/* GPIO Pin validation */
#define GPIO_IS_VALID_PIN(PINx)						(PINx  <  GPIO_NPINS_PER_PORT)

/* Mode pin validation */
#define GPIO_IS_VALID_MODE(MODEx)					(GPIO_OUT  == MODEx   || GPIO_IN == MODEx)

/* GPIO pin Value validation */
#define GPIO_IS_VALID_VALUE(STATEx)					(GPIO_HIGH == STATEx || GPIO_LOW == STATEx)

/* GPIO port mode and value validation */
#define GPIO_IS_PORT_VAL_MODE(STATEx)				(STATEx < 0x00FF)



/* ***************************************************************************** */
/* Definition for PORTA Registers */
/* ***************************************************************************** */
#define PORTA 	(*(volatile uint8 *)0x003B)
#define DDRA 	(*(volatile uint8 *)0x003A)
#define PINA  	(*(volatile uint8 *)0x0039)

/* ***************************************************************************** */
/* Definition for PORTB Registers */
/* ***************************************************************************** */
#define PORTB 	(*(volatile uint8 *)0x0038)
#define DDRB 	(*(volatile uint8 *)0x0037)
#define PINB  	(*(volatile uint8 *)0x0036)

/* ***************************************************************************** */
/* Definition for PORTC Registers */
/* ***************************************************************************** */
#define PORTC 	(*(volatile uint8 *)0x0035)
#define DDRC 	(*(volatile uint8 *)0x0034)
#define PINC  	(*(volatile uint8 *)0x0033)

/* ***************************************************************************** */
/* Definition for PORTD Registers */
/* ***************************************************************************** */
#define PORTD 	(*(volatile uint8 *)0x0032)
#define DDRD 	(*(volatile uint8 *)0x0031)
#define PIND  	(*(volatile uint8 *)0x0030)

#endif /* GPIO_PRIVATE_H_ */
