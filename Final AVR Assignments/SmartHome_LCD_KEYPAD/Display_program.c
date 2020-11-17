#include <stdarg.h>
#include <string.h>
#include <stdio.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "LCD_interface.h"
#include "Keypad_interface.h"
#include "GPIO_interface.h"
#include "Display_interface.h"
#define DISPLAY_MSG_MAX									80
static 	LCD_configType LCD_DATA;

void Display_vPrint(uint8 *Copy_u8String,uint8 Copy_u8line)
{
	uint16 Length = 0;
	uint16 Local_u16Index = 0;


	Length = strlen(Copy_u8String);

	LCDAnimation_vMoveLine(Copy_u8String,Copy_u8line);
}


void Display_vRecieveString(uint8 *Copy_u8String)
{
	uint8 u8RecvData;
	uint8 Local_u8Index = 0;
	memset(Copy_u8String,'\0',sizeof(Copy_u8String));
	while(1)
	{
		u8RecvData = Keypad_xScan();
		if(u8RecvData != E_NOK)
		{
			if(DISPLAY_ENTER_KEY==u8RecvData)
			{
				break;
			}
			else
			{

				Copy_u8String[Local_u8Index] =  u8RecvData;

				Local_u8Index++;
				Copy_u8String[Local_u8Index] = '\0';
				LCD_xGotoPosition(LCD_SECOND_LINE,0);
				LCD_vSendString(Copy_u8String);
			}
		}

	}

}

void Display_vRecvChar(uint8 *Copy_u8Char)
{
	uint8 u8RecvData;
	u8RecvData = Keypad_xScan();

	while(u8RecvData == E_NOK)
	{
		u8RecvData	=	Keypad_xScan();
	}

	*Copy_u8Char =  u8RecvData;
	LCD_xGotoPosition(LCD_SECOND_LINE,0);
	LCD_xSendByte(u8RecvData);
}
