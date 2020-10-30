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
							/* LCD characteristics */
/* ***************************************************************************** */
#define LCD_N_LINES										2
#define LCD_N_COLS										16

/* ***************************************************************************** */
#endif /*LCD_CONFIG_H_*/
