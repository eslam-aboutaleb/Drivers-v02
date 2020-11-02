/* *******************************************************	*/
/*  keypad_program.c									    */
/*  Version: 1.0											*/
/* 	Date: 22/10/2020										*/
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
	uint8 Local_u8ColIndex = 0;
	uint8 Local_u8RowIndex = 0;

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
	}

}

/* ***************************************************************************** */

Error_Status Keypad_xScan(void)
{
	uint8 Local_u8ColIndex = 0;
	uint8 Local_u8RowIndex = 0;

	for(Local_u8ColIndex=0;Local_u8ColIndex<KEYPAD_MATRX_COLS_N;Local_u8ColIndex++)
	{
		GPIO_vWritePortPin(KeypadCols_Map[Local_u8ColIndex].Keypad_xPort,KeypadCols_Map[Local_u8ColIndex].Keypad_xPin,GPIO_LOW);
		for(Local_u8RowIndex=0;Local_u8RowIndex<KEYPAD_MATRX_ROWS_N;Local_u8RowIndex++)
		{

			if(GPIO_xReadPortPin(KeypadRows_Map[Local_u8RowIndex].Keypad_xPort,KeypadRows_Map[Local_u8RowIndex].Keypad_xPin) == GPIO_LOW)
			{
				while(GPIO_xReadPortPin(KeypadRows_Map[Local_u8RowIndex].Keypad_xPort,KeypadRows_Map[Local_u8RowIndex].Keypad_xPin) == GPIO_LOW);
				Queue_EnQueu(Keypad_keys2D[Local_u8ColIndex][Local_u8RowIndex]);
				return E_OK;
			}
		}
		GPIO_vWritePortPin(KeypadCols_Map[Local_u8ColIndex].Keypad_xPort,KeypadCols_Map[Local_u8ColIndex].Keypad_xPin,GPIO_HIGH);
	}
	return E_NOK;
}

/* ***************************************************************************** */

Error_Status Keypad_xReadPressedBuf(uint8* u8Recv_Data)
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

void Keypad_Update(void)
{
	/* Application */
}
