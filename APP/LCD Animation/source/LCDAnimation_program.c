#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <string.h>
#include "LCD_interface.h"
#include "LCD_config.h"
#include "LCDAnimation_interface.h"
#include "LCDAnimation_config.h"

void LCDAnimation_VUpDown(uint8 *Copy_u8String)
{
	uint8 Local_u8LinePosition		=	0;
	static sint8 Local_s8Index		=	0;
	uint8 Local_u8BufIndex			=	0;
	static Flag_Status Local_xReverseFlag	=	E_NOK;
	uint8 u8Buffer[20];

	strcpy((char*)u8Buffer,(char*)Copy_u8String);
	uint8 Local_u8StrLength			= strlen((char*)u8Buffer);
	if(E_OK == Local_xReverseFlag)
	{
		Local_s8Index = LCD_N_COLS-1;
	}
	else
	{
		Local_s8Index = 0;
	}
	LCD_vClear();
	if(E_NOK == Local_xReverseFlag)
	{
		while(Local_s8Index < LCD_N_COLS)
		{
			LCD_xGotoPosition(Local_s8Index,Local_u8LinePosition);
			LCD_xSendByte(u8Buffer[Local_u8BufIndex]);
			Local_u8BufIndex++;
			if(Local_u8BufIndex > Local_u8StrLength)
			{
				Local_u8BufIndex = 0;
				LCD_vClear();
			}

			Local_s8Index++;
			LCD_DELAY_MS(LCDANIMATION_UPDOWN_T_MS);
			TOG_BIT(Local_u8LinePosition,0);
		}
	}
	else
	{
		Local_s8Index--;

		while(Local_s8Index >= 0)
		{
			LCD_xGotoPosition(Local_s8Index,Local_u8LinePosition);
			LCD_xSendByte(u8Buffer[Local_u8BufIndex]);
			Local_u8BufIndex++;
			if(Local_u8BufIndex > Local_u8StrLength)
			{
				Local_u8BufIndex = 0;
				LCD_vClear();
			}

			Local_s8Index--;
			LCD_DELAY_MS(LCDANIMATION_UPDOWN_T_MS);
			TOG_BIT(Local_u8LinePosition,0);
		}
	}
	TOG_BIT(Local_xReverseFlag,0) ;
}

void LCDAnimation_vMove(uint8 *Copy_pu8String)
{
	uint8 Local_u8LinePosition		=	0;
	static sint8 Local_s8Index		=	0;
	static Flag_Status Local_xReverseFlag	=	E_NOK;

	if(E_OK == Local_xReverseFlag)
	{
		Local_s8Index = LCD_N_COLS-1;
	}
	else
	{
		Local_s8Index = 0;
	}
	LCD_vClear();
	if(E_NOK == Local_xReverseFlag)
	{
		while(Local_s8Index < LCD_N_COLS)
		{
			LCD_vClear();
			LCD_xGotoPosition(Local_s8Index,Local_u8LinePosition);
			LCD_vSendString(Copy_pu8String);
			Local_s8Index++;
			LCD_DELAY_MS(LCDANIMATION_MOVE_T_MS);
			TOG_BIT(Local_u8LinePosition,0);
		}
	}
	else
	{
		Local_s8Index--;

		while(Local_s8Index >= 1)
		{
			LCD_vClear();
			LCD_xGotoPosition(Local_s8Index,Local_u8LinePosition);
			LCD_vSendString(Copy_pu8String);

			Local_s8Index--;
			LCD_DELAY_MS(LCDANIMATION_MOVE_T_MS);
			TOG_BIT(Local_u8LinePosition,0);
		}
	}
	TOG_BIT(Local_xReverseFlag,0) ;
}



