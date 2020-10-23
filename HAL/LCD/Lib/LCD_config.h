/* *******************************************************	*/
/*  LCD_Config.c										    */
/*  Version: 1.0											*/
/* 	Date: 20/10/2020										*/
/*  Author : Eslam Ehab Aboutaleb							*/
/* *******************************************************  */

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

/* ***************************************************************************** */
/* Check if the clock is defined */
#ifndef F_CPU
#define F_CPU 8000000UL
#endif

/* ***************************************************************************** */
						/* MCU timing libraries */
/* ***************************************************************************** */
#define AVR_MCU						0

#define LCD_MASTER_MCU				AVR_MCU

#if LCD_MASTER_MCU	==	AVR_MCU
#include <util/delay.h>
#endif

/* ***************************************************************************** */
							/*Portable macros*/
/* ***************************************************************************** */
#define LCD_DELAY_MS 	_delay_ms
#define LCD_DELAY_US	_delay_us

/* ***************************************************************************** */
							/*LCD initialization timing macros*/
/* ***************************************************************************** */
#define LCD_VDD_RISE_WAIT_MS							50
#define LCD_FUNCTION_SET_WAIT_US						1000
#define LCD_CURSOR_DISP_CNTRL_WAIT_US					1000
#define LCD_END_INIT_WAIT_MS							2

/* ***************************************************************************** */
								/*Data pins*/
/* ***************************************************************************** */
#define LCD_DATA_PIN0_DR							GPIOC
#define LCD_DATA_PIN0_CR							GPIOC
#define LCD_DATA_PIN0   							GPIO_PIN_0

#define LCD_DATA_PIN1_DR							GPIOC
#define LCD_DATA_PIN1_CR							GPIOC
#define LCD_DATA_PIN1   							GPIO_PIN_1

#define LCD_DATA_PIN2_DR							GPIOC
#define LCD_DATA_PIN2_CR							GPIOC
#define LCD_DATA_PIN2   							GPIO_PIN_2

#define LCD_DATA_PIN3_DR							GPIOC
#define LCD_DATA_PIN3_CR							GPIOC
#define LCD_DATA_PIN3   							GPIO_PIN_3

#define LCD_DATA_PIN4_DR							GPIOC
#define LCD_DATA_PIN4_CR							GPIOC
#define LCD_DATA_PIN4   							GPIO_PIN_4

#define LCD_DATA_PIN5_DR							GPIOC
#define LCD_DATA_PIN5_CR							GPIOC
#define LCD_DATA_PIN5   							GPIO_PIN_5

#define LCD_DATA_PIN6_DR							GPIOC
#define LCD_DATA_PIN6_CR							GPIOC
#define LCD_DATA_PIN6   							GPIO_PIN_6

#define LCD_DATA_PIN7_DR							GPIOC
#define LCD_DATA_PIN7_CR							GPIOC
#define LCD_DATA_PIN7   							GPIO_PIN_7

/* ***************************************************************************** */
							/*Control pins*/
/* ***************************************************************************** */
#define LCD_E_PIN_DR      							GPIOD
#define LCD_E_PIN_CR      							GPIOD
#define LCD_E_PIN        							GPIO_PIN_0

#define LCD_RS_PIN_DR     							GPIOD
#define LCD_RS_PIN_CR     							GPIOD
#define LCD_RS_PIN        							GPIO_PIN_2

#define LCD_RW_PIN_DR     							GPIOD
#define LCD_RW_PIN_CR     							GPIOD
#define LCD_RW_PIN        							GPIO_PIN_1

/* ***************************************************************************** */
#endif /*LCD_CONFIG_H_*/
