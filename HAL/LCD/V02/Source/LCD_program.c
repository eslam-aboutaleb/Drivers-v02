/* *******************************************************	*/
/*  LCD_program.c										    */
/*  Version: 2.0											*/
/* 	Date: 30/10/2020										*/
/*  Author : Eslam Ehab Aboutaleb							*/
/* *******************************************************  */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "Util_String_interface.h"
#include "LCD_config.h"
#include "LCD_interface.h"
#include "LCD_Private.h"

/* ***************************************************************************** */
static uint8 u8LCD_WordLength;
/* ***************************************************************************** */
#define LCD_SET_CURRENT_WORD_LENGTH(u8WordLength)			u8LCD_WordLength = u8WordLength
#define LCD_U8GET_CURRENT_WORD_LENGTH()						u8LCD_WordLength
/* ***************************************************************************** */

Error_Status LCD_xInit(LCD_configType * ConfigTypePtr)
{
	/* Initialize control pins */
	GPIO_vInitPortPin(ConfigTypePtr->LCD_Map.LCD_CNTRL_PORT[LCD_E_PIN_INDEX],ConfigTypePtr->LCD_Map.LCD_CNTRL_PIN[LCD_E_PIN_INDEX],GPIO_OUT);
	GPIO_vInitPortPin(ConfigTypePtr->LCD_Map.LCD_CNTRL_PORT[LCD_RS_PIN_INDEX],ConfigTypePtr->LCD_Map.LCD_CNTRL_PIN[LCD_RS_PIN_INDEX],GPIO_OUT);
	GPIO_vInitPortPin(ConfigTypePtr->LCD_Map.LCD_CNTRL_PORT[LCD_RW_PIN_INDEX],ConfigTypePtr->LCD_Map.LCD_CNTRL_PIN[LCD_RW_PIN_INDEX],GPIO_OUT);

	/* Set LCD RW pin high as reading mode to read the busy flag */
	GPIO_vWritePortPin(ConfigTypePtr->LCD_Map.LCD_CNTRL_PORT[LCD_RW_PIN_INDEX],ConfigTypePtr->LCD_Map.LCD_CNTRL_PIN[LCD_RW_PIN_INDEX],GPIO_HIGH);
	/* Clear LCD enable pin */
	GPIO_vWritePortPin(ConfigTypePtr->LCD_Map.LCD_CNTRL_PORT[LCD_E_PIN_INDEX],ConfigTypePtr->LCD_Map.LCD_CNTRL_PIN[LCD_E_PIN_INDEX],GPIO_LOW);

	uint8 Local_u8Index = 0;
	/* Check LCD operates at which word length mode */
	if(LCD_8_pins == ConfigTypePtr->WordLength)
	{
		/* Set current word length flag as 8 pins mode */
		LCD_SET_CURRENT_WORD_LENGTH(LCD_8_pins);

		/* Initialize Data pins */
		for(Local_u8Index = 0; Local_u8Index < LCD_8_pins;Local_u8Index++)
		{
			/* If there is no initialized port or pin return error */
			if(ConfigTypePtr == NULL || ConfigTypePtr== NULL)
			{
				return E_NOK;
			}
			GPIO_vInitPortPin(ConfigTypePtr->LCD_Map.LCD_DATA_PORT[Local_u8Index],ConfigTypePtr->LCD_Map.LCD_DATA_PIN[Local_u8Index],GPIO_OUT);
		}
	}
	else if (LCD_4_pins == ConfigTypePtr->WordLength)
	{
		/* Set current word length flag as 4 pins mode */
		LCD_SET_CURRENT_WORD_LENGTH(LCD_4_pins);
		/* Initialize Data pins */
		for(Local_u8Index = 0; Local_u8Index < LCD_4_pins;Local_u8Index++)
		{
			/* If there is no initialized port or pin return error */
			if(ConfigTypePtr == NULL || ConfigTypePtr== NULL)
			{
				return E_NOK;
			}
			GPIO_vInitPortPin(ConfigTypePtr->LCD_Map.LCD_DATA_PORT[Local_u8Index],ConfigTypePtr->LCD_Map.LCD_DATA_PIN[Local_u8Index],GPIO_OUT);
		}
	}
	else
	{
		return E_NOK;
	}

	/* Initialization sequence */
	/* Check if there is any operation is still running and wait until VDD rises */
	LCD_CHECK_BUSY_FLAG();

	/* Function set configurations */
	LCD_xSendComand(ConfigTypePtr,
			(LCD_FUNCTION_SET|
					/* Configure word length */
					LCD_PINS  (ConfigTypePtr->WordLength)|
					/* Configure number of lines */
					LCD_LINES (ConfigTypePtr->linesNumber)|
					/* Configure font size */
					LCD_FONT  (ConfigTypePtr->FontSize))
	);

	/* Check if there is any operation is still running */
	LCD_CHECK_BUSY_FLAG();

	/* Cursor and display control */
	LCD_xSendComand(ConfigTypePtr,
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
	LCD_xSendComand(ConfigTypePtr,LCD_CLR);

	/* Check if there is any operation is still running */
	LCD_CHECK_BUSY_FLAG();
	/* Entry mode */
	LCD_xSendComand(ConfigTypePtr,
			LCD_SET_ENTRY_MODE
			/* Configure cursor shifting state */
			|CURSOR_SHIFT  (ConfigTypePtr->CursorShift)
			/* Configure display shifting state */
			|LCD_DISPLAY_SHIFT (ConfigTypePtr->DisplayShift)
	);

	/* Clear LCD RW pin to return to write mode */
	GPIO_vWritePortPin(LCD_RW_PIN_PORT,LCD_RW_PIN,GPIO_LOW);

	return E_OK;
}

/* ***************************************************************************** */

static Error_Status LCD_xSendComand(LCD_configType *LCDx,uint8 Copy_u8Command)
{
	/* Turn LCD to send data mode */
	GPIO_vWritePortPin(LCDx->LCD_Map.LCD_CNTRL_PORT[LCD_RW_PIN_INDEX],LCDx->LCD_Map.LCD_CNTRL_PIN[LCD_RW_PIN_INDEX],GPIO_LOW);
	GPIO_vWritePortPin(LCDx->LCD_Map.LCD_CNTRL_PORT[LCD_RS_PIN_INDEX],LCDx->LCD_Map.LCD_CNTRL_PIN[LCD_RS_PIN_INDEX],GPIO_LOW);

	/* Send data to LCD port */
	if(LCD_8_pins == LCD_U8GET_CURRENT_WORD_LENGTH())
	{
		LCD_vLatch(LCDx,Copy_u8Command,LCD_SEND_COMMAND,LCD_8_pins);
	}
	else if(LCD_4_pins == LCD_U8GET_CURRENT_WORD_LENGTH())
	{
		LCD_vLatch(LCDx,Copy_u8Command,LCD_SEND_COMMAND,LCD_4_pins);
	}
	else
	{
		return E_NOK;
	}
	return E_OK;
}

/* ***************************************************************************** */
Error_Status LCD_xSendByte(LCD_configType *LCDx, uint8 Copy_u8Byte)
{
	/* Turn LCD to send data mode */
	GPIO_vWritePortPin(LCDx->LCD_Map.LCD_CNTRL_PORT[LCD_RW_PIN_INDEX],LCDx->LCD_Map.LCD_CNTRL_PIN[LCD_RW_PIN_INDEX],GPIO_LOW);
	GPIO_vWritePortPin(LCDx->LCD_Map.LCD_CNTRL_PORT[LCD_RS_PIN_INDEX],LCDx->LCD_Map.LCD_CNTRL_PIN[LCD_RS_PIN_INDEX],GPIO_HIGH);

	if(LCD_8_pins == LCD_U8GET_CURRENT_WORD_LENGTH())
	{
		LCD_vLatch(LCDx,Copy_u8Byte,LCD_SEND_DATA,LCD_8_pins);
	}
	else if(LCD_4_pins == LCD_U8GET_CURRENT_WORD_LENGTH())
	{
		LCD_vLatch(LCDx,Copy_u8Byte,LCD_SEND_DATA,LCD_4_pins);
	}
	else
	{
		return E_NOK;
	}

	return E_OK;
}
/* ***************************************************************************** */
Error_Status LCD_xRecvByte(uint8 Copy_u8Byte, uint8* pu8RecvData)
{
	uint8 Local_u8Data	=	0;
	uint8 Local_u8DataArr[8];
	uint8 Local_u8Index	=	0;
	/* Turn LCD to read data mode */
	GPIO_vWritePortPin(LCD_RS_PIN_PORT,LCD_RS_PIN,GPIO_HIGH);
	GPIO_vWritePortPin(LCD_RW_PIN_PORT,LCD_RW_PIN,GPIO_HIGH);
	/* Check what is the current word length */
	if(LCD_8_pins == LCD_U8GET_CURRENT_WORD_LENGTH())
	{
		Local_u8DataArr[0] = GPIO_xReadPortPin(LCD_DATA_PIN0_PORT,LCD_DATA_PIN0);
		Local_u8DataArr[1] = GPIO_xReadPortPin(LCD_DATA_PIN1_PORT,LCD_DATA_PIN1);
		Local_u8DataArr[2] = GPIO_xReadPortPin(LCD_DATA_PIN2_PORT,LCD_DATA_PIN2);
		Local_u8DataArr[3] = GPIO_xReadPortPin(LCD_DATA_PIN3_PORT,LCD_DATA_PIN3);
		Local_u8DataArr[4] = GPIO_xReadPortPin(LCD_DATA_PIN4_PORT,LCD_DATA_PIN4);
		Local_u8DataArr[5] = GPIO_xReadPortPin(LCD_DATA_PIN5_PORT,LCD_DATA_PIN5);
		Local_u8DataArr[6] = GPIO_xReadPortPin(LCD_DATA_PIN6_PORT,LCD_DATA_PIN6);
		Local_u8DataArr[7] = GPIO_xReadPortPin(LCD_DATA_PIN7_PORT,LCD_DATA_PIN7);
		for(Local_u8Index = 0;Local_u8Index < CHARSIZE;Local_u8Index++)
		{
			if(Local_u8DataArr[Local_u8Index] == 0)
			{
				CLEAR_BIT(Local_u8Data,Local_u8Index);
			}
			else if (Local_u8DataArr[Local_u8Index] == 1)
			{
				SET_BIT(Local_u8Data,Local_u8Index);
			}
			else
			{
				/* No Action */
			}
		}
	}
	else if(LCD_4_pins == LCD_U8GET_CURRENT_WORD_LENGTH())
	{
		/* Receive the upper nibble */
		Local_u8DataArr[0] = GPIO_xReadPortPin(LCD_DATA_PIN0_PORT,LCD_DATA_PIN4);
		Local_u8DataArr[1] = GPIO_xReadPortPin(LCD_DATA_PIN1_PORT,LCD_DATA_PIN5);
		Local_u8DataArr[2] = GPIO_xReadPortPin(LCD_DATA_PIN2_PORT,LCD_DATA_PIN6);
		Local_u8DataArr[3] = GPIO_xReadPortPin(LCD_DATA_PIN3_PORT,LCD_DATA_PIN7);

		/* Wait until LCD does the operations */
		LCD_CHECK_BUSY_FLAG();

		/* Receive the lower nibble */
		Local_u8DataArr[4] = GPIO_xReadPortPin(LCD_DATA_PIN4_PORT,LCD_DATA_PIN4);
		Local_u8DataArr[5] = GPIO_xReadPortPin(LCD_DATA_PIN5_PORT,LCD_DATA_PIN5);
		Local_u8DataArr[6] = GPIO_xReadPortPin(LCD_DATA_PIN6_PORT,LCD_DATA_PIN6);
		Local_u8DataArr[7] = GPIO_xReadPortPin(LCD_DATA_PIN7_PORT,LCD_DATA_PIN7);
		for(Local_u8Index = 0;Local_u8Index < CHARSIZE;Local_u8Index++)
		{
			if(Local_u8DataArr[Local_u8Index] == 0)
			{
				CLEAR_BIT(Local_u8Data,Local_u8Index);
			}
			else if (Local_u8DataArr[Local_u8Index] == 1)
			{
				SET_BIT(Local_u8Data,Local_u8Index);
			}
			else
			{
				/* No Action */
			}
		}
	}
	else
	{
		return E_NOK;
	}

	*pu8RecvData = Local_u8Data;
	return E_OK;

}
/* ***************************************************************************** */
static Error_Status LCD_vLatch(LCD_configType *LCDx,uint8 Copy_u8Data,uint8 Copy_u8DataType,uint8 Copy_u8Mode )
{
	uint8 Local_u8Index = 0;
	if(LCD_8_pins==Copy_u8Mode)
	{
		/* Send data to LCD port */
		for(Local_u8Index = 0; Local_u8Index < LCD_8_pins;Local_u8Index++)
		{
			/* If there is no initialized port or pin return error */
			if(LCDx == NULL || LCDx== NULL)
			{
				return E_NOK;
			}
			GPIO_vWritePortPin(LCDx->LCD_Map.LCD_DATA_PORT[Local_u8Index],LCDx->LCD_Map.LCD_DATA_PIN[Local_u8Index],GET_BIT(Copy_u8Data,Local_u8Index));
		}
		/* Enable LCD */
		LCD_vSendPulse(LCDx);
	}
	else if(LCD_4_pins==Copy_u8Mode)
	{
		uint8 Local_u8DataIndex = 0;
		/*Send upper nibble*/
		for(Local_u8DataIndex = 4,Local_u8Index = 0; Local_u8Index < 8;Local_u8Index++,Local_u8DataIndex++)
		{
			/* If there is no initialized port or pin return error */
			if(LCDx == NULL || LCDx== NULL)
			{
				return E_NOK;
			}
			GPIO_vWritePortPin(LCDx->LCD_Map.LCD_DATA_PORT[Local_u8Index],LCDx->LCD_Map.LCD_DATA_PIN[Local_u8Index],GET_BIT(Copy_u8Data,Local_u8DataIndex));
		}
		/* Enable LCD */
		LCD_vSendPulse(LCDx);

		if(GET_BIT(Copy_u8Data,5) == 1 && GET_BIT(Copy_u8Data,6) == 0 && GET_BIT(Copy_u8Data,7) == 0 && LCD_SEND_COMMAND == Copy_u8DataType)
		{
			/*Send upper nibble*/
			for(Local_u8DataIndex = 4,Local_u8Index = 0; Local_u8Index < 8;Local_u8Index++,Local_u8DataIndex++)
			{
				/* If there is no initialized port or pin return error */
				if(LCDx == NULL || LCDx== NULL)
				{
					return E_NOK;
				}
				GPIO_vWritePortPin(LCDx->LCD_Map.LCD_DATA_PORT[Local_u8Index],LCDx->LCD_Map.LCD_DATA_PIN[Local_u8Index],GET_BIT(Copy_u8Data,Local_u8DataIndex));
			}
			/* Enable LCD */
			LCD_vSendPulse(LCDx);

			/*send lower nibble*/
			for(Local_u8Index = 0; Local_u8Index < 4;Local_u8Index++)
			{
				/* If there is no initialized port or pin return error */
				if(LCDx == NULL || LCDx== NULL)
				{
					return E_NOK;
				}
				GPIO_vWritePortPin(LCDx->LCD_Map.LCD_DATA_PORT[Local_u8Index],LCDx->LCD_Map.LCD_DATA_PIN[Local_u8Index],GET_BIT(Copy_u8Data,Local_u8Index));
			}

			/* Enable LCD */
			LCD_vSendPulse(LCDx);

		}
		else
		{
			/*send lower nibble*/
			for(Local_u8Index = 0; Local_u8Index < 4;Local_u8Index++)
			{
				/* If there is no initialized port or pin return error */
				if(LCDx == NULL || LCDx== NULL)
				{
					return E_NOK;
				}
				GPIO_vWritePortPin(LCDx->LCD_Map.LCD_DATA_PORT[Local_u8Index],LCDx->LCD_Map.LCD_DATA_PIN[Local_u8Index],GET_BIT(Copy_u8Data,Local_u8Index));
			}

			/* Enable LCD */
			LCD_vSendPulse(LCDx);
		}
	}
	else
	{
		return E_NOK;
	}

	return E_OK;
}

/* ***************************************************************************** */

static void LCD_vSendPulse(LCD_configType *LCDx)
{
	GPIO_vWritePortPin(LCDx->LCD_Map.LCD_CNTRL_PORT[LCD_E_PIN_INDEX],LCDx->LCD_Map.LCD_CNTRL_PIN[LCD_E_PIN_INDEX],GPIO_HIGH);
	LCD_DELAY_MS(1);
	GPIO_vWritePortPin(LCDx->LCD_Map.LCD_CNTRL_PORT[LCD_E_PIN_INDEX],LCDx->LCD_Map.LCD_CNTRL_PIN[LCD_E_PIN_INDEX],GPIO_LOW);
	LCD_DELAY_MS(1);
}

/* ***************************************************************************** */

void LCD_vSendString(LCD_configType *LCDx,uint8 *Copy_u8String)
{
	while (*Copy_u8String != '\0')
	{
		LCD_xSendByte(LCDx,*Copy_u8String);
		Copy_u8String++;
	}
}

/* ***************************************************************************** */

Error_Status LCD_xGotoPosition(LCD_configType *LCDx,uint8 Copy_u8Line_Position, uint8 Copy_u8Col_Position)
{
	if(LCD_IS_FIRST_LINE(Copy_u8Line_Position) == E_OK)
	{
		LCD_xSendComand(LCDx,(LCD_SET_DDRAM_ADDRESS | LCD_FIRST_LINE) + Copy_u8Col_Position);
	}
	else if(LCD_IS_SECOND_LINE(Copy_u8Line_Position) == E_OK)
	{
		LCD_xSendComand(LCDx,(LCD_SET_DDRAM_ADDRESS | LCD_SECOND_LINE) + Copy_u8Col_Position);
	}
	else
	{
		return E_NOK;
	}

	return E_OK;
}
/* ***************************************************************************** */
void LCD_vSendInt(LCD_configType *LCDx,sint32 Copy_s32Num)
{
	uint8 Local_u8NumBufferp[LCD_N_COLS] = {0};
	Util_String_vNumtoStr(Copy_s32Num,Local_u8NumBufferp);
	LCD_vSendString(LCDx,Local_u8NumBufferp);
}

/* ***************************************************************************** */

void LCD_vSendFloat(LCD_configType *LCDx,float32 Copy_f32Num, uint8 Copy_u8N_NumbersAfterFPonit)
{
	uint8 Local_u8NumBufferp[LCD_N_COLS] = {0};
	Util_String_vFloatToStr(Copy_f32Num,Local_u8NumBufferp,Copy_u8N_NumbersAfterFPonit);
	LCD_vSendString(LCDx,Local_u8NumBufferp);
}
/* ***************************************************************************** */
void LCD_vClear(LCD_configType *LCDx)
{
	LCD_xSendComand(LCDx,LCD_CLR);
}

/* ***************************************************************************** */

void LCD_vReturnHome(LCD_configType *LCDx)
{
	LCD_xSendComand(LCDx,LCD_CURSOR_HOME);
}

/* ***************************************************************************** */
Error_Status LCD_vCustomChar(LCD_configType *LCDx,uint8 *Copy_pu8CharacteArr,CGRAM_CharPos_t Copy_xPosition)
{
	if(LCD_IS_VALID_CGRAM_POS(Copy_xPosition) == E_NOK)
	{
		return E_NOK;
	}

	uint8 Local_u8Index = 0;
	LCD_xSendComand(LCDx,LCD_SET_CGRAM_ADDRESS +(Copy_xPosition * 8));

	for(Local_u8Index = 0;Local_u8Index < LCD_CGRAM_PATTERN_BUFF_COUNT;Local_u8Index++)
	{
		LCD_xSendByte(LCDx,Copy_pu8CharacteArr[Local_u8Index]);
	}

	return E_OK;
}

