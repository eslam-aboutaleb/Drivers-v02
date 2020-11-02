/* *******************************************************	*/
/*  keypad_program.c									    */
/*  Version: 3.0											*/
/* 	Date: 2/11/2020											*/
/*  Author : Eslam Ehab Aboutaleb							*/
/* *******************************************************  */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "Keypad_interface.h"
#include "Keypad_config.h"

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
			/* Initialize the keypad callback functions */
			KeypadRows_Map[Local_u8RowIndex].Keypad_CallBack[Local_u8StateIndex]	=	NULL;
			Local_u8StateIndex++;
		}
	}
}

/* ***************************************************************************** */
Error_Status Keypad_xSetKeyFunc(uint8 Copy_u8KeyNum,void(*CallBackPtr)(void))
{
	/* Check if the number of pin is bigger than number of Rows * Cols */
	/* Check if the CallBackPtr is Null or not */
	if((NULL == CallBackPtr) || (Copy_u8KeyNum > ((KEYPAD_MATRX_COLS_N*KEYPAD_MATRX_ROWS_N)-1)))
	{
		return E_NOK;
	}

	KeypadRows_Map[Copy_u8KeyNum % KEYPAD_MATRX_ROWS_N].Keypad_CallBack[Copy_u8KeyNum] = CallBackPtr;

	return E_OK;
}
/* ***************************************************************************** */
Error_Status Keypad_xScan(KeypadState_t Copy_xPressingState)
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
				/* Check if the keypad callback function is null or not */
				if(KeypadRows_Map[Local_u8RowIndex].Keypad_CallBack[Local_u8StateIndex] == NULL)
				{
					return E_NOK;
				}
				KeypadRows_Map[Local_u8RowIndex].Keypad_CallBack[Local_u8StateIndex]();
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
