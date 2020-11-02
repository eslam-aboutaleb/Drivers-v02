/* *******************************************************	*/
/*  keypad_program.c									    */
/*  Version: 2.0											*/
/* 	Date: 30/10/2020										*/
/*  Author : Eslam Ehab Aboutaleb							*/
/* *******************************************************  */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "Queue_interface.h"
#include "Keypad_interface.h"
#include "Keypad_config.h"


/* Keypad layout*/
/* ***************************************************************************** */
static uint8 Keypad_keys2D[KEYPAD_MATRX_ROWS_N][KEYPAD_MATRX_COLS_N] = KEYPAD_KEYS_2D;
/* ***************************************************************************** */

void Keypad_vInit(void)
{
	uint8 Local_u8ColIndex		= 0;
	uint8 Local_u8RowIndex		= 0;
	uint8 Local_u8StateIndex 	= 0;
	uint8 Local_MulIndex 		= 0;

	/* Initialize the row pins as output */
	for(Local_u8ColIndex=0;Local_u8ColIndex<KEYPAD_MATRX_COLS_N;Local_u8ColIndex++)
	{
		GPIO_vInitPortPin(KeypadCols_Map[Local_u8ColIndex].Keypad_xPort,KeypadCols_Map[Local_u8ColIndex].Keypad_xPin,GPIO_OUT);
	}

	/* Initialize the row pins as input */
	for(Local_u8RowIndex=0;Local_u8RowIndex<KEYPAD_MATRX_ROWS_N;Local_u8RowIndex++)
	{
		GPIO_vInitPortPin(KeypadRows_Map[Local_u8RowIndex].Keypad_xPort,KeypadRows_Map[Local_u8RowIndex].Keypad_xPin,GPIO_IN);
		GPIO_vWritePortPin(KeypadRows_Map[Local_u8RowIndex].Keypad_xPort,KeypadRows_Map[Local_u8RowIndex].Keypad_xPin,GPIO_HIGH);

		for(Local_MulIndex=0;Local_MulIndex < KEYPAD_MATRX_COLS_N;Local_MulIndex++)
		{
			/* Initialize the keypad samples */
			KeypadRows_Map[Local_u8RowIndex].KeypadSampels[Local_u8StateIndex][0]	=	KEYPAD_RELEASED_LEVEL;
			KeypadRows_Map[Local_u8RowIndex].KeypadSampels[Local_u8StateIndex][1]	=	KEYPAD_RELEASED_LEVEL;
			/* Initialize the keypad state */
			KeypadRows_Map[Local_u8RowIndex].KeypadState[Local_u8StateIndex]		=	KEYPAD_RELEASED;

			Local_u8StateIndex++;
		}
	}
}

/* ***************************************************************************** */

Flag_Status Keypad_xScan(KeypadState_t Copy_xPressingState)
{
	uint8 Local_u8ColIndex = 0;
	uint8 Local_u8RowIndex = 0;
	uint8 Local_u8StateIndex = 0;

	for(Local_u8ColIndex=0;Local_u8ColIndex < KEYPAD_MATRX_COLS_N;Local_u8ColIndex++)
	{
		/* Enable column */
		GPIO_vWritePortPin(
				KeypadCols_Map[Local_u8ColIndex].Keypad_xPort,
				KeypadCols_Map[Local_u8ColIndex].Keypad_xPin,
				GPIO_LOW);

		/* Checking rows */
		for(Local_u8RowIndex=0;Local_u8RowIndex<KEYPAD_MATRX_ROWS_N;Local_u8RowIndex++)
		{
			/* Update switch samples => Old sample = last new sample */
			KeypadRows_Map[Local_u8RowIndex].KeypadSampels[Local_u8StateIndex][0]	=
					KeypadRows_Map[Local_u8RowIndex].KeypadSampels[Local_u8StateIndex][1];

			/* The new sample will be equal to the switch state */
			KeypadRows_Map[Local_u8RowIndex].KeypadSampels[Local_u8StateIndex][1]	=
					GPIO_xReadPortPin(
							KeypadRows_Map[Local_u8RowIndex].Keypad_xPort
							,KeypadRows_Map[Local_u8RowIndex].Keypad_xPin);


			/* The keypad switches have four states */
			switch(KeypadRows_Map[Local_u8RowIndex].KeypadState[Local_u8StateIndex])
			{
			case KEYPAD_RELEASED:
				if((KEYPAD_PRESSED_LEVEL == KeypadRows_Map[Local_u8RowIndex].KeypadSampels[Local_u8StateIndex][0]) &&
						(KEYPAD_PRESSED_LEVEL == KeypadRows_Map[Local_u8RowIndex].KeypadSampels[Local_u8StateIndex][1]))
				{
					KeypadRows_Map[Local_u8RowIndex].KeypadState[Local_u8StateIndex] = KEYPAD_PRE_PRESSED;
				}
				break;

			case KEYPAD_PRE_PRESSED:
				if(KEYPAD_PRESSED_LEVEL == KeypadRows_Map[Local_u8RowIndex].KeypadSampels[Local_u8StateIndex][1])
				{
					KeypadRows_Map[Local_u8RowIndex].KeypadState[Local_u8StateIndex] = KEYPAD_PRESSED;
				}
				break;

			case KEYPAD_PRESSED:
				if((KEYPAD_RELEASED_LEVEL == KeypadRows_Map[Local_u8RowIndex].KeypadSampels[Local_u8StateIndex][0])&&
						(KEYPAD_RELEASED_LEVEL == KeypadRows_Map[Local_u8RowIndex].KeypadSampels[Local_u8StateIndex][1]))
				{
					KeypadRows_Map[Local_u8RowIndex].KeypadState[Local_u8StateIndex] = KEYPAD_PRE_RELEASED;
				}
				break;

			case KEYPAD_PRE_RELEASED:
				if(KEYPAD_RELEASED_LEVEL == KeypadRows_Map[Local_u8RowIndex].KeypadSampels[Local_u8StateIndex][1])
				{
					KeypadRows_Map[Local_u8RowIndex].KeypadState[Local_u8StateIndex] = KEYPAD_RELEASED;
				}
				break;

			default:

				break;
			}

			if(KeypadRows_Map[Local_u8RowIndex].KeypadState [Local_u8StateIndex]	== Copy_xPressingState)
			{
				Queue_EnQueu(Keypad_keys2D[Local_u8ColIndex][Local_u8RowIndex]);
				return E_OK;
			}
			Local_u8StateIndex++;
		}

		/* Disable column */
		GPIO_vWritePortPin(
				KeypadCols_Map[Local_u8ColIndex].Keypad_xPort,
				KeypadCols_Map[Local_u8ColIndex].Keypad_xPin,
				GPIO_HIGH);
	}
	return E_NOK;
}

/* ***************************************************************************** */

Flag_Status Keypad_xReadPressedBuf(uint8* u8Recv_Data)
{
	uint8 Local_u8Data = 0;
	if(Queue_DeQueue(&Local_u8Data) == E_NOK)
	{
		return E_NOK;
	}
	*u8Recv_Data = Local_u8Data;
	return E_OK;
}

/* ***************************************************************************** */
