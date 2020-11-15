#include <stdarg.h>
#include <string.h>
#include <stdio.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "USART_interface.h"

#include "Display_interface.h"

#define DISPLAY_MSG_MAX									80
void Display_vPrint(uint8 *Copy_u8String, ...)
{
	uint8 ActDataMsg[DISPLAY_MSG_MAX]	=	{0};
	uint16 Length = 0;
	uint16 Local_u16Index = 0;
	va_list args;
	va_start(args,Copy_u8String);
	vsprintf(ActDataMsg,Copy_u8String,args);

	Length = strlen(ActDataMsg);

	for(Local_u16Index = 0; Local_u16Index < Length;Local_u16Index++)
	{
		USART_xSendByte(USART1,ActDataMsg[Local_u16Index]);
	}

	va_end(args);
}


void Display_vRecieveString(uint8 *Copy_u8String)
{
	USART_xRecieveString(USART1,Copy_u8String);
}

void Display_vRecvChar(uint8 *Copy_u8Char)
{
	USART_xRecieveByte(USART1,Copy_u8Char);
}
