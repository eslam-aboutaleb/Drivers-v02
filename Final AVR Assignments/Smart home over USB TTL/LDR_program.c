/* **************************************************************************** */
/* Author	: Eslam Ehab Aboutaleb												*/
/* Date		: 15/11/2020														*/
/* version	: V01																*/
/* **************************************************************************** */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ADC_interface.h"

#include "LDR_interface.h"
#include "LDR_config.h"
/* **************************************************************************** */
static uint16 LDR_Value;
/* **************************************************************************** */

void LDR_vInit(void)
{
	/* Initial value for light intensity */
	LDR_Value	=	0;
}

/* **************************************************************************** */

uint16 LDR_u16GetVal(void)
{
	return LDR_Value;
}

/* ***************************************************************************** */
/*Light intensity sensor update*/
/* ***************************************************************************** */
void LDR_vUpdate(void)
{
	uint16 Local_u16RecvData	=	0;

	/*Measure the current light intensity*/
	 ADC_xReadSynch(LDR_ADC_CHANNEL, &Local_u16RecvData);

	 LDR_Value = Local_u16RecvData;
}
