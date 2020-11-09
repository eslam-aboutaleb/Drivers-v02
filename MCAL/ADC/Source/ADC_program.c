#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"

/* ***************************************************************************** */
/* ADC current adjust state */
/* ***************************************************************************** */
static ADC_Adjust_t ADC_xCurrentAdjustState;
#define ADC_GET_CURRENT_ADJUST_STATE()						ADC_xCurrentAdjustState
/* ***************************************************************************** */


/* ***************************************************************************** */
/* ADC callback pointer to function */
/* ***************************************************************************** */
static void (*ADC_vCallBack)(uint16);

/* ***************************************************************************** */
Error_Status ADC_xInit(const ADC_Typedef *ADCx)
{
	Error_Status Local_xErrorState	=	E_NOK;

	/* Configure reference voltage */
	Local_xErrorState	=	ADC_xRefVoltage(ADCx->ADC_xVoltRef);
	/* Configure adjusting result state */
	Local_xErrorState	=	ADC_xAdjustResult(ADCx->ADC_xAdjustState);
	if(ADCx->ADC_xAdjustState == ADC_RIGHT_ADJUST)
	{
		ADC_xCurrentAdjustState = ADC_RIGHT_ADJUST;
	}
	else
	{
		ADC_xCurrentAdjustState = ADC_LEFT_ADJUST;
	}
	/* Set ADC interrupt state */
	Local_xErrorState	=	ADC_xSetIntState(ADCx->ADC_xInterruptState);
	/* Set auto trigger state */
	Local_xErrorState	=	ADC_xSetAutoTrigger(ADCx->ADC_xTriggerState);
	/* Set PreScaler */
	Local_xErrorState	=	ADC_xSetPrescaler(ADCx->ADC_xPrescaler);
	/* Set ADC auto trigger source */
	Local_xErrorState	=	ADC_xSetTriggerSrc(ADCx->ADC_xTriggerSource);
	/* Set initial ADC state */
	Local_xErrorState	=	ADC_xSetState(ADCx->ADC_xState);

	return Local_xErrorState;
}

/* ***************************************************************************** */

static Error_Status ADC_xRefVoltage(ADC_VoltageRef_t Copy_xVoltRef)
{
	switch(Copy_xVoltRef)
	{
	case ADC_VREF_TURNED_OFF:
		CLEAR_BIT(ADMUX,REFS1);
		CLEAR_BIT(ADMUX,REFS0);
		break;
	case ADC_AVCC_EX_CAP:
		CLEAR_BIT(ADMUX,REFS1);
		SET_BIT(ADMUX,REFS0);
		break;
	case ADC_INTERNAL_VOLTAGE_2_56:
		SET_BIT(ADMUX,REFS1);
		SET_BIT(ADMUX,REFS0);
		break;
	default:
		return E_NOK;
		break;
	}
	return E_OK;
}

/* ***************************************************************************** */

static Error_Status ADC_xAdjustResult(ADC_Adjust_t Copy_xAdjustState)
{
	switch(Copy_xAdjustState)
	{
	case ADC_LEFT_ADJUST:
		CLEAR_BIT(ADMUX,ADLAR);
		break;
	case ADC_RIGHT_ADJUST:
		SET_BIT(ADMUX,ADLAR);
		break;
	default:
		return E_NOK;
		break;
	}
	return E_OK;
}

/* ***************************************************************************** */

Error_Status ADC_xSelectChannel(ADC_Ch_t Copy_xChannel)
{
	/* Check validity of the channel */
	if(E_NOK == ADC_IS_VALID_CH(Copy_xChannel))
	{
		return E_NOK;
	}

	/* Clear selection bits */
	ADMUX &= 0xE0;
	/* Set channel bits */
	ADMUX |= Copy_xChannel;
	return E_OK;
}

/* ***************************************************************************** */

Error_Status ADC_xSetState(ADC_State_t Copy_xState)
{
	switch(Copy_xState)
	{
	case ADC_DISABLE:
		CLEAR_BIT(ADCSRA,ADEN);
		break;
	case ADC_ENABLE:
		SET_BIT(ADCSRA,ADEN);
		break;
	default:
		return E_NOK;
		break;
	}
	return E_OK;
}

/* ***************************************************************************** */

Error_Status ADC_xSetIntState(ADC_Int_t Copy_xState)
{
	switch (Copy_xState) {
	case ADC_DISABLE_INTERRUPT:
		CLEAR_BIT(ADCSRA,ADIE);
		break;
	case ADC_ENABLE_INTERRUPT:
		SET_BIT(ADCSRA,ADIE);
		break;
	default:
		return E_NOK;
		break;
	}
	return E_OK;
}

/* ***************************************************************************** */

static Error_Status ADC_xSetAutoTrigger(ADC_AutoTrigger_t Copy_xTrigger)
{
	switch (Copy_xTrigger) {
	case ADC_DISABLE_AUTO_TRIGGER:
		CLEAR_BIT(ADCSRA,ADATE);
		break;
	case ADC_ENABLE_AUTO_TRIGGER:
		SET_BIT(ADCSRA,ADATE);
		break;
	default:
		return E_NOK;
		break;
	}
	return E_OK;
}

/* ***************************************************************************** */

static Error_Status ADC_xSetPrescaler(ADC_Prescaler_t Copy_xPrescaler)
{
	if(E_NOK == ADC_IS_VALID_PRESCALER(Copy_xPrescaler))
	{
		return E_NOK;
	}
	/* Clear PreScaler bits */
	ADCSRA &= 0xF8;
	/* Set PreScaler */
	ADCSRA |= Copy_xPrescaler;

	return E_OK;
}

/* ***************************************************************************** */

static Error_Status ADC_xSetTriggerSrc(ADC_TriggerSrc_t Copy_xSrc)
{
	if(E_NOK == ADC_IS_VALID_TRGSRC(Copy_xSrc))
	{
		return E_NOK;
	}
	/* Clear special function IO bits */
	SFIOR &= 0x0F;
	/* Set special function IO bits */
	SFIOR |= (4<<Copy_xSrc);

	return E_OK;
}

/* ***************************************************************************** */
Error_Status ADC_xReadUpperRegSynch(ADC_Ch_t Copy_xADC_Chx,uint8 *u8RecvData)
{
	Error_Status Local_xErrorStatus	=	E_NOK;
	/* Select ADC channel */
	Local_xErrorStatus	=	ADC_xSelectChannel(Copy_xADC_Chx);
	/* Enable ADC */
	ADC_xSetState(ADC_ENABLE);
	/* Start ADC conversion */
	ADC_START_CONVERSION();
	/* Check ADC flag */
	ADC_CHECK_FLAG();
	/* Clear ADC flag */
	ADC_CLEAR_FALG();
	/* Assign ADC data */
	*u8RecvData = ADCH;
	/* Disable ADC */
	ADC_xSetState(ADC_DISABLE);

	return Local_xErrorStatus;

}
/* ***************************************************************************** */
Error_Status ADC_xReadSynch(ADC_Ch_t Copy_xADC_Chx,uint16 *u16RecvData)
{
	uint32 Local_u32TimeOutCounter	=	0;
	Error_Status Local_xErrorStatus	=	E_NOK;
	/* Select ADC channel */
	Local_xErrorStatus	=	ADC_xSelectChannel(Copy_xADC_Chx);
	/* Enable ADC */
	ADC_xSetState(ADC_ENABLE);
	/* Start ADC conversion */
	ADC_START_CONVERSION();
	/* Check ADC flag */
	while(GET_BIT(ADCSRA,ADIF) == E_NOK)
	{
		Local_u32TimeOutCounter++;
		if(ADC_TIME_OUT	==	Local_u32TimeOutCounter)
		{
			break;
		}
	}
	/* Clear ADC flag */
	ADC_CLEAR_FALG();
	/* Assign ADC data */
	if(ADC_GET_CURRENT_ADJUST_STATE() == ADC_RIGHT_ADJUST)
	{
		*u16RecvData =	ADCBUF_REG;
	}
	else if(ADC_GET_CURRENT_ADJUST_STATE() == ADC_LEFT_ADJUST)
	{
		*u16RecvData =	(ADCL >> 6);
		*u16RecvData =	(ADCH << 2);
	}
	else
	{
		Local_xErrorStatus	=	E_NOK;
	}

	/* Disable ADC */
	ADC_xSetState(ADC_DISABLE);

	return Local_xErrorStatus;
}

/* ***************************************************************************** */

Error_Status ADC_xReadASynch(ADC_Ch_t Copy_xADC_Chx,void (*pvCallBack)(uint16))
{
	Error_Status Local_xErrorStaus	=	E_NOK;
	/* Assign callback function */
	ADC_vCallBack		=	pvCallBack;
	/* Select ADC channel */
	Local_xErrorStaus	=	ADC_xSelectChannel(Copy_xADC_Chx);
	/* Enable ADC interrupt */
	Local_xErrorStaus	=	ADC_xSetIntState(ADC_ENABLE_INTERRUPT);
	/* Enable ADC */
	Local_xErrorStaus	=	ADC_xSetState(ADC_ENABLE);
	/* Start ADC conversion */
	ADC_START_CONVERSION();

	return Local_xErrorStaus;
}

/* ***************************************************************************** */
void ADC_IRQ(void)
{
	if(ADC_GET_CURRENT_ADJUST_STATE() == ADC_RIGHT_ADJUST)
	{
		ADC_vCallBack(ADCBUF_REG);
	}
	else if(ADC_GET_CURRENT_ADJUST_STATE() == ADC_LEFT_ADJUST)
	{
		uint16 Local_u16RecvData	=	0;

		Local_u16RecvData =	(ADCL >> 6);
		Local_u16RecvData =	(ADCH << 2);

		ADC_vCallBack(Local_u16RecvData);
	}

	/* Start ADC conversion */
	ADC_START_CONVERSION();

	/* Clear ADC flag */
	ADC_CLEAR_FALG();
}
