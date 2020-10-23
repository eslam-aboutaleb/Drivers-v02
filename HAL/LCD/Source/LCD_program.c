/* *******************************************************	*/
/*  LCD_program.c										    */
/*  Version: 1.0											*/
/* 	Date: 20/10/2020										*/
/*  Author : Eslam Ehab Aboutaleb							*/
/* *******************************************************  */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "Util_String_interface.h"
#include "LCD_interface.h"
#include "LCD_config.h"
#include "LCD_Private.h"

/* ***************************************************************************** */
static uint8 u8LCD_WordLength;
/* ***************************************************************************** */
#define LCD_SET_CURRENT_WORD_LENGTH(u8WordLength)			u8LCD_WordLength = u8WordLength
#define LCD_U8GET_CURRENT_WORD_LENGTH()						u8LCD_WordLength
/* ***************************************************************************** */

void LCD_vInit(LCD_configType * ConfigTypePtr)
{
	/* Initialize control pins */
	GPIO_vInitPortPin(LCD_E_PIN_CR,LCD_E_PIN,GPIO_OUT);
	GPIO_vInitPortPin(LCD_RS_PIN_CR,LCD_RS_PIN,GPIO_OUT);
	GPIO_vInitPortPin(LCD_RW_PIN_CR,LCD_RW_PIN,GPIO_OUT);

	/* Set LCD RW pin high as reading mode to read the busy flag */
	GPIO_vWritePortPin(LCD_RW_PIN_DR,LCD_RW_PIN,GPIO_HIGH);
	/* Clear LCD enable pin */
	GPIO_vWritePortPin(LCD_E_PIN_DR,LCD_E_PIN,GPIO_LOW);

	/* Check LCD operates at which word length mode */
	if(LCD_8_pins == ConfigTypePtr->WordLength)
	{
		/* Set current word length flag as 8 pins mode */
		LCD_SET_CURRENT_WORD_LENGTH(LCD_8_pins);
		/* Initialize Data pins */
		GPIO_vInitPortPin(LCD_DATA_PIN0_DR,LCD_DATA_PIN0,GPIO_OUT);
		GPIO_vInitPortPin(LCD_DATA_PIN1_DR,LCD_DATA_PIN1,GPIO_OUT);
		GPIO_vInitPortPin(LCD_DATA_PIN2_DR,LCD_DATA_PIN2,GPIO_OUT);
		GPIO_vInitPortPin(LCD_DATA_PIN3_DR,LCD_DATA_PIN3,GPIO_OUT);

		GPIO_vInitPortPin(LCD_DATA_PIN4_DR,LCD_DATA_PIN4,GPIO_OUT);
		GPIO_vInitPortPin(LCD_DATA_PIN5_DR,LCD_DATA_PIN5,GPIO_OUT);
		GPIO_vInitPortPin(LCD_DATA_PIN6_DR,LCD_DATA_PIN6,GPIO_OUT);
		GPIO_vInitPortPin(LCD_DATA_PIN7_DR,LCD_DATA_PIN7,GPIO_OUT);
	}
	else if (LCD_4_pins == ConfigTypePtr->WordLength)
	{
		/* Set current word length flag as 4 pins mode */
		LCD_SET_CURRENT_WORD_LENGTH(LCD_4_pins);
		/* Initialize Data pins */
		GPIO_vInitPortPin(LCD_DATA_PIN4_DR,LCD_DATA_PIN4,GPIO_OUT);
		GPIO_vInitPortPin(LCD_DATA_PIN5_DR,LCD_DATA_PIN5,GPIO_OUT);
		GPIO_vInitPortPin(LCD_DATA_PIN6_DR,LCD_DATA_PIN6,GPIO_OUT);
		GPIO_vInitPortPin(LCD_DATA_PIN7_DR,LCD_DATA_PIN7,GPIO_OUT);
	}
	else
	{
		/* No Action */
	}

	/* Initialization sequence */
	/* Check if there is any operation is still running and wait until VDD rises */
	LCD_CHECK_BUSY_FLAG();

	/* Function set configurations */
	LCD_vSendComand(
			LCD_FUNCTION_SET|
			/* Configure word length */
			LCD_PINS  (ConfigTypePtr->WordLength)|
			/* Configure number of lines */
			LCD_LINES (ConfigTypePtr->linesNumber)|
			/* Configure font size */
			LCD_FONT  (ConfigTypePtr->FontSize)
	);

	/* Check if there is any operation is still running */
	LCD_CHECK_BUSY_FLAG();

	/* Cursor and display control */
	LCD_vSendComand(
			LCD_CURSOR_DISPLAY_CONTROL|
			/*Configure display state*/
			DISPLAYSET  (ConfigTypePtr->DisplayState)|
			/*Configure Cursor state*/
			CURSOR_SET  (ConfigTypePtr->CursorState)|
			/*Configure Cursor blinking state*/
			CURSOR_BLINK(ConfigTypePtr->CursorBlinkState)
	);

	/* Check if there is any operation is still running */
	LCD_CHECK_BUSY_FLAG();

	/* Clear the screen */
	LCD_vSendComand(LCD_CLR);

	/* Check if there is any operation is still running */
	LCD_CHECK_BUSY_FLAG();
	/* Entry mode */
	LCD_vSendComand(
			LCD_SET_ENTRY_MODE
			/* Configure cursor shifting state */
			|CURSOR_SHIFT  (ConfigTypePtr->CursorShift)
			/* Configure display shifting state */
			|LCD_DISPLAY_SHIFT (ConfigTypePtr->DisplayShift)
	);

	/* Clear LCD RW pin to return to write mode */
	GPIO_vWritePortPin(LCD_RW_PIN_DR,LCD_RW_PIN,GPIO_LOW);
}

/* ***************************************************************************** */

static void LCD_vSendComand(uint8 Copy_u8Command)
{
	/* Turn LCD to send data mode */
	GPIO_vWritePortPin(LCD_RS_PIN_DR,LCD_RS_PIN,GPIO_LOW);
	GPIO_vWritePortPin(LCD_RW_PIN_DR,LCD_RW_PIN,GPIO_LOW);
	/* Send data to LCD port */
	if(LCD_8_pins == LCD_U8GET_CURRENT_WORD_LENGTH())
	{
		LCD_vLatch(Copy_u8Command,LCD_SEND_COMMAND,LCD_8_pins);
	}
	else if(LCD_4_pins == LCD_U8GET_CURRENT_WORD_LENGTH())
	{
		LCD_vLatch(Copy_u8Command,LCD_SEND_COMMAND,LCD_4_pins);
	}
	else
	{
		/* No Action */
	}
}

/* ***************************************************************************** */
void LCD_vSendByte(uint8 Copy_u8Byte)
{
	/* Turn LCD to send data mode */
	GPIO_vWritePortPin(LCD_RS_PIN_CR,LCD_RS_PIN,GPIO_HIGH);
	GPIO_vWritePortPin(LCD_RW_PIN_CR,LCD_RW_PIN,GPIO_LOW);
	if(LCD_8_pins == LCD_U8GET_CURRENT_WORD_LENGTH())
	{
		LCD_vLatch(Copy_u8Byte,LCD_SEND_DATA,LCD_8_pins);
	}
	else if(LCD_4_pins == LCD_U8GET_CURRENT_WORD_LENGTH())
	{
		LCD_vLatch(Copy_u8Byte,LCD_SEND_DATA,LCD_4_pins);
	}
	else
	{
		/* No Action */
	}


}

/* ***************************************************************************** */
static void LCD_vLatch(uint8 Copy_u8Data,uint8 Copy_u8DataType,uint8 Copy_u8Mode )
{
	if(LCD_8_pins==Copy_u8Mode)
	{
		/* Send data to LCD port */
		GPIO_vWritePortPin(LCD_DATA_PIN0_CR,LCD_DATA_PIN0,GET_BIT(Copy_u8Data,0));
		GPIO_vWritePortPin(LCD_DATA_PIN1_CR,LCD_DATA_PIN1,GET_BIT(Copy_u8Data,1));
		GPIO_vWritePortPin(LCD_DATA_PIN2_CR,LCD_DATA_PIN2,GET_BIT(Copy_u8Data,2));
		GPIO_vWritePortPin(LCD_DATA_PIN3_CR,LCD_DATA_PIN3,GET_BIT(Copy_u8Data,3));
		GPIO_vWritePortPin(LCD_DATA_PIN4_CR,LCD_DATA_PIN4,GET_BIT(Copy_u8Data,4));
		GPIO_vWritePortPin(LCD_DATA_PIN5_CR,LCD_DATA_PIN5,GET_BIT(Copy_u8Data,5));
		GPIO_vWritePortPin(LCD_DATA_PIN6_CR,LCD_DATA_PIN6,GET_BIT(Copy_u8Data,6));
		GPIO_vWritePortPin(LCD_DATA_PIN7_CR,LCD_DATA_PIN7,GET_BIT(Copy_u8Data,7));

		/* Enable LCD */
		LCD_vSendPulse();
	}
	else if(LCD_4_pins==Copy_u8Mode)
	{
		/*Send upper nibble*/
		GPIO_vWritePortPin(LCD_DATA_PIN4_CR,LCD_DATA_PIN4,GET_BIT(Copy_u8Data,4));
		GPIO_vWritePortPin(LCD_DATA_PIN5_CR,LCD_DATA_PIN5,GET_BIT(Copy_u8Data,5));
		GPIO_vWritePortPin(LCD_DATA_PIN6_CR,LCD_DATA_PIN6,GET_BIT(Copy_u8Data,6));
		GPIO_vWritePortPin(LCD_DATA_PIN7_CR,LCD_DATA_PIN7,GET_BIT(Copy_u8Data,7));
		/* Enable LCD */
		LCD_vSendPulse();

		if(GET_BIT(Copy_u8Data,5) == 1 && GET_BIT(Copy_u8Data,6) == 0 && GET_BIT(Copy_u8Data,7) == 0 && LCD_SEND_COMMAND == Copy_u8DataType)
		{
			/*Send upper nibble*/
			GPIO_vWritePortPin(LCD_DATA_PIN4_CR,LCD_DATA_PIN4,GET_BIT(Copy_u8Data,4));
			GPIO_vWritePortPin(LCD_DATA_PIN5_CR,LCD_DATA_PIN5,GET_BIT(Copy_u8Data,5));
			GPIO_vWritePortPin(LCD_DATA_PIN6_CR,LCD_DATA_PIN6,GET_BIT(Copy_u8Data,6));
			GPIO_vWritePortPin(LCD_DATA_PIN7_CR,LCD_DATA_PIN7,GET_BIT(Copy_u8Data,7));
			/* Enable LCD */
			LCD_vSendPulse();

			/*send lower nibble*/
			GPIO_vWritePortPin(LCD_DATA_PIN4_CR,LCD_DATA_PIN4,GET_BIT(Copy_u8Data,0));
			GPIO_vWritePortPin(LCD_DATA_PIN5_CR,LCD_DATA_PIN5,GET_BIT(Copy_u8Data,1));
			GPIO_vWritePortPin(LCD_DATA_PIN6_CR,LCD_DATA_PIN6,GET_BIT(Copy_u8Data,2));
			GPIO_vWritePortPin(LCD_DATA_PIN7_CR,LCD_DATA_PIN7,GET_BIT(Copy_u8Data,3));
			/* Enable LCD */
			LCD_vSendPulse();

		}
		else
		{
			/*send lower nibble*/
			GPIO_vWritePortPin(LCD_DATA_PIN4_CR,LCD_DATA_PIN4,GET_BIT(Copy_u8Data,0));
			GPIO_vWritePortPin(LCD_DATA_PIN5_CR,LCD_DATA_PIN5,GET_BIT(Copy_u8Data,1));
			GPIO_vWritePortPin(LCD_DATA_PIN6_CR,LCD_DATA_PIN6,GET_BIT(Copy_u8Data,2));
			GPIO_vWritePortPin(LCD_DATA_PIN7_CR,LCD_DATA_PIN7,GET_BIT(Copy_u8Data,3));
			/* Enable LCD */
			LCD_vSendPulse();
		}
	}
}

/* ***************************************************************************** */

static void LCD_vSendPulse(void)
{
	GPIO_vWritePortPin(LCD_E_PIN_CR,LCD_E_PIN,GPIO_HIGH);
	LCD_DELAY_MS(1);
	GPIO_vWritePortPin(LCD_E_PIN_CR,LCD_E_PIN,GPIO_LOW);
	LCD_DELAY_MS(1);
}

/* ***************************************************************************** */

void LCD_vSendString(uint8 *Copy_u8String)
{
	while (*Copy_u8String != '\0')
	{
		LCD_vSendByte(*Copy_u8String);
		Copy_u8String++;
	}
}

/* ***************************************************************************** */

Error_Status LCD_xGotoPosition(uint8 Copy_u8X_Position,uint8 Copy_u8Y_Position)
{
	if(LCD_IS_FIRST_LINE(Copy_u8Y_Position) == E_OK)
	{
		LCD_vSendComand((LCD_SET_DDRAM_ADDRESS | LCD_FIRST_LINE) + Copy_u8X_Position);
	}
	else if(LCD_IS_SECOND_LINE(Copy_u8Y_Position) == E_OK)
	{
		LCD_vSendComand((LCD_SET_DDRAM_ADDRESS | LCD_SECOND_LINE) + Copy_u8X_Position);
	}
	else
	{
		return E_NOK;
	}

	return E_OK;
}
/* ***************************************************************************** */
void LCD_vSendInt(sint32 Copy_s32Num)
{
	uint8 Local_u8NumBufferp[16] = {0};
	Util_String_vNumtoStr(Copy_s32Num,Local_u8NumBufferp);
	LCD_vSendString(Local_u8NumBufferp);
}

/* ***************************************************************************** */
void LCD_vAddChar(uint8 *u8Character)
{
}
