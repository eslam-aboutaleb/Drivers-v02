/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 19-8-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */


#ifndef LED_CONFIG_H
#define LED_CONFIG_H

/* ***********************************************************  */

typedef unsigned char										LedPort_t;
typedef unsigned char										LedPin_t;

/* ***********************************************************  */

#define LEDS_N												2

typedef struct{
	LedPort_t	Led_Port;
	LedPin_t	Led_Pin;
}LedMap_st;

LedMap_st Leds[LEDS_N] ={
		{GPIOA,GPIO_PIN_3},
		{GPIOA,GPIO_PIN_7}
};


#endif /* LED_CONFIG_H */
