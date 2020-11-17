/* **************************************************************************** */
/* Author	: Eslam Ehab Aboutaleb												*/
/* Date		: 15/11/2020														*/
/* version	: V01																*/
/* **************************************************************************** */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ADC_interface.h"

#include "TempS_interface.h"
#include "TempS_config.h"
/* **************************************************************************** */
static float32 TempValue;
/* **************************************************************************** */

void TempS_vInit(void)
{
	/* Initial value for temperature */
	TempValue	=	0;
}

/* **************************************************************************** */

float32 TempS_f32GetTemp(void)
{
	return TempValue;
}

/* ***************************************************************************** */
/*Temperature sensor update*/
/* ***************************************************************************** */
void TempS_vUpdate(void)
{
	uint16 Local_u16RecvData	=	0;
	float32 Local_f32Voltage	=	0;
	/*Measure the current temperature*/
	 ADC_xReadSynch(TEMPSENSE_ADC_CHANNEL, &Local_u16RecvData);
	 /* Convert the reading into milli voltage */
	 Local_f32Voltage = (float32)Local_u16RecvData*(TEMPSENSE_VCC_MV/TEMPSENSE_ADC_RESOLUTION);

	/* Divide voltage by 10mv the 2 to get accurate temperature degree */
	TempValue= (Local_f32Voltage/100)/2;
}
