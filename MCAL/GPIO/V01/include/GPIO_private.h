 /* ******************************************************  */
 /*  GPIO_privat.h										    */
 /*  Version: 1.0											*/
 /*  Author : Eslam Ehab Aboutaleb							*/
 /* ******************************************************  */

#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_

/* Definition for PORTA Registers */
#define PORTA 	(*(volatile uint8 *)0x003B)
#define DDRA 	(*(volatile uint8 *)0x003A)
#define PINA  	(*(volatile uint8 *)0x0039)

/* Definition for PORTB Registers */
#define PORTB 	(*(volatile uint8 *)0x0038)
#define DDRB 	(*(volatile uint8 *)0x0037)
#define PINB  	(*(volatile uint8 *)0x0036)

/* Definition for PORTC Registers */
#define PORTC 	(*(volatile uint8 *)0x0035)
#define DDRC 	(*(volatile uint8 *)0x0034)
#define PINC  	(*(volatile uint8 *)0x0033)

/* Definition for PORTD Registers */
#define PORTD 	(*(volatile uint8 *)0x0032)
#define DDRD 	(*(volatile uint8 *)0x0031)
#define PIND  	(*(volatile uint8 *)0x0030)

#endif /* GPIO_PRIVATE_H_ */
