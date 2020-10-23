/* *******************************************************	*/
/*  Util_String_interface.h									*/
/*  Version: 1.0											*/
/* 	Date: 23/10/2020										*/
/*  Author : Eslam Ehab Aboutaleb							*/
/* *******************************************************  */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Util_String_interface.h"

void Util_String_vNumtoStr(sint32 Copy_s32Num,uint8 *pu8Buffer)
{
	sint32 		 Local_s32Index		= 	0;
	sint32 		 Local_s32Copy 		= 	0;
	Flag_Status  Local_xSignFlag	=	E_NOK;
	uint8		 Local_xSignBorder	=	0;

	/* Checks if the number is negative */
	if(Copy_s32Num < 0)
	{
		/* Turn it to positive */
		Copy_s32Num 	= -1 * Copy_s32Num;
		/* Raise sign flag*/
		Local_xSignFlag = E_OK;
	}

	/* Buffer to count number of digits in the number */
	Local_s32Copy = Copy_s32Num;

	while(Local_s32Copy > 0)
	{
		Local_s32Copy /=10;
		Local_s32Index++;
	}
	/* If the number is negative */
	if(Local_xSignFlag == E_OK)
	{
		/* Increase the index to be able to store sign in the buffer */
		Local_s32Index++;
		/* Assign the sign in the first index */
		pu8Buffer[0] = '-';
		/* Leave the first index empty for the sign */
		Local_xSignBorder = 1;
	}
	pu8Buffer[Local_s32Index--] = '\0';
	while(Local_s32Index >= Local_xSignBorder)
	{
		/* Convert the numbers to characters and store them in the buffer */
		pu8Buffer[Local_s32Index--] = ((Copy_s32Num % 10) + '0');
		Copy_s32Num /= 10;
	}
}


void Util_String_vFloatToStr(float32 Copy_f32NUM, uint8 *pu8Buffer)
{
	sint32 		Local_s32Index 			= 0;
	sint32 		Local_s32DecSize		= 0;
	float32 	Local_f32SubBuffer 		= 0;
	sint32 		Local_s32NumToSub		= 0;
	sint32 		Local_s32IntBuff		= 0;
	Flag_Status Local_xSignFlag			= E_NOK;
	uint8		Local_xSignBorder		= 0;

	if(Copy_f32NUM < 0)
	{
		/* Turn it to positive */
		Copy_f32NUM = -1 * Copy_f32NUM;
		/* Raise sign flag*/
		Local_xSignFlag = E_OK;
	}
	Local_s32NumToSub 		= (sint32)Copy_f32NUM;
	Local_s32IntBuff		= (sint32)Copy_f32NUM;


	if(Local_s32IntBuff == 0)
	{
		Local_s32Index =1;
	}
	else{
		while (Local_s32IntBuff > 0)
		{
			Local_s32IntBuff /= 10;
			Local_s32Index++;
		}
	}
	if(Local_xSignFlag == E_OK)
	{
		/* Increase the index to be able to store sign in the buffer */
		Local_s32Index++;
		/* Assign the sign in the first index */
		pu8Buffer[0] = '-';
		/* Leave the first index empty for the sign */
		Local_xSignBorder = 1;
	}
	Local_s32IntBuff = (sint32)Copy_f32NUM;
	Local_s32DecSize = Local_s32Index+1;
	pu8Buffer[Local_s32Index--] = '.';
	while(Local_s32Index >= Local_xSignBorder)
	{
		pu8Buffer[Local_s32Index--] = ((Local_s32IntBuff % 10) + '0');
		Local_s32IntBuff /= 10;
	}

	Local_f32SubBuffer = Copy_f32NUM - (float32) Local_s32NumToSub;
	if(Local_f32SubBuffer > 0.0)
	{
		while(Local_f32SubBuffer > 0.0)
		{
			Local_f32SubBuffer *= 10;
			pu8Buffer[Local_s32DecSize] = Local_f32SubBuffer+'0';
			Local_s32NumToSub = Local_f32SubBuffer;
			Local_f32SubBuffer = Local_f32SubBuffer - Local_s32NumToSub;
			Local_s32DecSize++;
		}
		pu8Buffer[Local_s32DecSize] = '\0';
	}
	else
	{
		pu8Buffer[Local_s32DecSize - 1] = '\0';
	}

}
