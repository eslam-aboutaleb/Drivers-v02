/* *******************************************************	*/
/* 	Date: 30/10/2020										*/
/*  Author : Eslam Ehab Aboutaleb							*/
/* *******************************************************  */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "LCD_interface.h"

void main(void){
	LCD_configType LCD_DATA;
	LCD_DATA.LCD_Map.LCD_DATA_PORT[0] 					= GPIOC;
	LCD_DATA.LCD_Map.LCD_DATA_PIN[0]					= GPIO_PIN_4;
	LCD_DATA.LCD_Map.LCD_DATA_PORT[1] 					= GPIOC;
	LCD_DATA.LCD_Map.LCD_DATA_PIN[1]					= GPIO_PIN_5;
	LCD_DATA.LCD_Map.LCD_DATA_PORT[2] 					= GPIOC;
	LCD_DATA.LCD_Map.LCD_DATA_PIN[2]					= GPIO_PIN_6;
	LCD_DATA.LCD_Map.LCD_DATA_PORT[3] 					= GPIOC;
	LCD_DATA.LCD_Map.LCD_DATA_PIN[3]					= GPIO_PIN_7;

	LCD_DATA.LCD_Map.LCD_CNTRL_PORT[LCD_E_PIN_INDEX]	= GPIOD;
	LCD_DATA.LCD_Map.LCD_CNTRL_PIN[LCD_E_PIN_INDEX]		= GPIO_PIN_0;

	LCD_DATA.LCD_Map.LCD_CNTRL_PORT[LCD_RW_PIN_INDEX]	= GPIOD;
	LCD_DATA.LCD_Map.LCD_CNTRL_PIN[LCD_RW_PIN_INDEX]	= GPIO_PIN_1;

	LCD_DATA.LCD_Map.LCD_CNTRL_PORT[LCD_RS_PIN_INDEX]	= GPIOD;
	LCD_DATA.LCD_Map.LCD_CNTRL_PIN[LCD_RS_PIN_INDEX]	= GPIO_PIN_2;

	LCD_DATA.WordLength									= LCD_4_pins;
	LCD_DATA.FontSize 									= LCD_Format_5x8;
	LCD_DATA.linesNumber								= LCD_Two_lines;
	LCD_DATA.CursorBlinkState 							= LCD_CursorBlinkOFF;
	LCD_DATA.CursorState 								= LCD_CursorOFF;
	LCD_DATA.DisplayState 								= LCD_DisplayON;
	LCD_xInit(&LCD_DATA);
	LCD_vClear(&LCD_DATA);
	while(1)
	{
		/* Action */
	}
}