/* ***********************************************************  */
/*  PWM_program.c											    */
/*  Version		: 1.0											*/
/*  Author 		: Eslam Ehab Aboutaleb							*/
/* 	Description	: GPIO driver 									*/
/* ***********************************************************  */

#include <avr//io.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "PWM_interface.h"
#include "PWM_private.h"


static uint16 Global_Prescaler	=	PWM_NO_Clock_Source;
static uint16 u16Current_Freq;

Error_Status PWM_vInit(PWM_Typedef *PWM_ConfigPtr)
{
	Error_Status Local_xErrorState	=	0;
	/* Choose channel and compare match mode */
	Local_xErrorState	=	PWM_xSetChannels(PWM_ConfigPtr->Channel,PWM_ConfigPtr->COM_Mode);

	/* Initialize PWM pins as output */
	switch(PWM_ConfigPtr->Channel)
	{
	case PWM_CH_1:
		GPIO_vInitPortPin(PWM_OCR1A_PORT,PWM_OCR1A_PIN,GPIO_OUT);
		break;
	case PWM_CH_2:
		GPIO_vInitPortPin(PWM_OCR1B_PORT,PWM_OCR1B_PIN,GPIO_OUT);
		break;
	default:
		return E_NOK;
		break;
	}
	/* Set PWM mode */
	Local_xErrorState	=	PWM_xSetMode(PWM_ConfigPtr->Mode);
	/* Enable Timer */
	Local_xErrorState	=	PWM_xSetPrescaler(PWM_ConfigPtr->Prescaler);

	return Local_xErrorState;
}

Error_Status PWM_xSetPrescaler(PWM_ClockPrescaler Copy_xPrescaler)
{
	switch(Copy_xPrescaler)
	{
	case PWM_NO_Clock_Source:
		CLEAR_BIT(TCCR1B,CS10);
		CLEAR_BIT(TCCR1B,CS11);
		CLEAR_BIT(TCCR1B,CS12);
		Global_Prescaler=0;
		break;
	case PWM_Prescaler_1:
		SET_BIT(TCCR1B,CS10);
		CLEAR_BIT(TCCR1B,CS11);
		CLEAR_BIT(TCCR1B,CS12);

		Global_Prescaler=1;
		break;

	case PWM_Prescaler_8:
		CLEAR_BIT(TCCR1B,CS10);
		SET_BIT(TCCR1B,CS11);
		CLEAR_BIT(TCCR1B,CS12);

		Global_Prescaler=8;
		break;

	case PWM_Prescaler_64:
		SET_BIT(TCCR1B,CS10);
		SET_BIT(TCCR1B,CS11);
		CLEAR_BIT(TCCR1B,CS12);

		Global_Prescaler=64;
		break;

	case PWM_Prescaler_256:
		CLEAR_BIT(TCCR1B,CS10);
		CLEAR_BIT(TCCR1B,CS11);
		SET_BIT(TCCR1B,CS12);

		Global_Prescaler=256;
		break;

	case PWM_Prescaler_1024:
		SET_BIT(TCCR1B,CS10);
		CLEAR_BIT(TCCR1B,CS11);
		SET_BIT(TCCR1B,CS12);

		Global_Prescaler=1024;
		break;

	case PWM_Preascaler_ExClockT1_Falling:
		CLEAR_BIT(TCCR1B,CS10);
		SET_BIT(TCCR1B,CS11);
		SET_BIT(TCCR1B,CS12);
		break;
	case PWM_Preascaler_ExClockT1_Rising:
		SET_BIT(TCCR1B,CS10);
		SET_BIT(TCCR1B,CS11);
		SET_BIT(TCCR1B,CS12);
		break;
	default:
		return E_NOK;
		break;
	}
	return E_OK;
}

void PWM_vStop(void)
{
	CLEAR_BIT(TCCR1B,CS10);
	CLEAR_BIT(TCCR1B,CS11);
	CLEAR_BIT(TCCR1B,CS12);
}

Error_Status PWM_xSetChannels(PWM_Channels Copy_xChannel,PWM_Com_OutputMode Copy_xOutputMode)
{
	switch(Copy_xOutputMode)
	{
	case Normal_Port_Operation:
		if (Copy_xChannel==PWM_CH_1)
		{
			CLEAR_BIT(TCCR1A,COM1A1);
			CLEAR_BIT(TCCR1A,COM1A0);
		}
		else if (Copy_xChannel==PWM_CH_2)
		{
			CLEAR_BIT(TCCR1A,COM1B1);
			CLEAR_BIT(TCCR1A,COM1B0);
		}
		break;

	case Tog_OC1A_CompMatch_OC1B_Disconnected:
		if (Copy_xChannel==PWM_CH_1)
		{
			CLEAR_BIT(TCCR1A,COM1A1);
			SET_BIT(TCCR1A,COM1A0);
		}
		else if (Copy_xChannel==PWM_CH_2)
		{
			CLEAR_BIT(TCCR1A,COM1B1);
			SET_BIT(TCCR1A,COM1B0);
		}
		break;

	case Clr_OC1A_OC1B_CompMatchNonInvert:
		if (Copy_xChannel==PWM_CH_1)
		{
			SET_BIT(TCCR1A,COM1A1);
			CLEAR_BIT(TCCR1A,COM1A0);
		}
		else if (Copy_xChannel==PWM_CH_2)
		{
			SET_BIT(TCCR1A,COM1B1);
			CLEAR_BIT(TCCR1A,COM1B0);
		}
		break;

	case Set_OC1A_OC1B_CompMatchInvert:
		if (Copy_xChannel==PWM_CH_1)
		{
			SET_BIT(TCCR1A,COM1A1);
			SET_BIT(TCCR1A,COM1A0);
		}
		if (Copy_xChannel==PWM_CH_2)
		{
			SET_BIT(TCCR1A,COM1B1);
			SET_BIT(TCCR1A,COM1B0);
		}
		break;

	default:
		return E_NOK;
		break;
	}
	return E_OK;
}

static Error_Status PWM_xSetMode(PWM_Mode Copy_xMode)
{
	switch(Copy_xMode)
	{
	case TIMER1_WGM_PWM_8     :
		SET_BIT(TCCR1A,WGM10);
		CLEAR_BIT(TCCR1A,WGM11);
		CLEAR_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1B,WGM13);
		break;
	case TIMER1_WGM_PWM_9     :
		CLEAR_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		CLEAR_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1B,WGM13);
		break;
	case TIMER1_WGM_PWM_10	  :
		SET_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		CLEAR_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1B,WGM13);
		break;
	case TIMER1_WGM_FPWM_8	  :
		SET_BIT(TCCR1A,WGM10);
		CLEAR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1B,WGM13);
		break;
	case TIMER1_WGM_FPWM_9	  :
		CLEAR_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1B,WGM13);
		break;
	case TIMER1_WGM_FPWM_10	  :
		SET_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1B,WGM13);
		break;
	case TIMER1_WGM_PWM_PF_ICR:
		CLEAR_BIT(TCCR1A,WGM10);
		CLEAR_BIT(TCCR1A,WGM11);
		CLEAR_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
	case TIMER1_WGM_PWM_PF_OCR:
		SET_BIT(TCCR1A,WGM10);
		CLEAR_BIT(TCCR1A,WGM11);
		CLEAR_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
	case TIMER1_WGM_PWM_P_ICR :
		CLEAR_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		CLEAR_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
	case TIMER1_WGM_PWM_P_OCR :
		SET_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		CLEAR_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
	case TIMER1_WGM_FPWM_ICR  :
		CLEAR_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
	case TIMER1_WGM_FPWM_OCR  :
		SET_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1A,WGM12);
		SET_BIT(TCCR1A,WGM13);
		break;
	default:
		return E_NOK;
		break;
	}
	return E_OK;

}

Error_Status PWM_xSetDutyCycle(PWM_Channels Copy_xChannel,float32 Copy_f32DutyCycle)
{
	Copy_f32DutyCycle		=	Copy_f32DutyCycle/100;
	uint16 u16PWM_RegVal	=	(uint16)(ICR1 * Copy_f32DutyCycle);
	switch(Copy_xChannel)
	{
	case PWM_CH_1:
		OCR1A	=	u16PWM_RegVal;
		break;
	case PWM_CH_2:
		OCR1B	=	u16PWM_RegVal;
		break;
	default:
		return E_NOK;
		break;
	}
	return E_OK;
}

void PWM_vSetFPWM_Freq(uint16 Copy_u16Freq)
{
	/*The PWM resolution for fast PWM can be fixed to 8-bit, 9-bit, or 10-bit, or defined by either ICR1
	or OCR1A*/
	ICR1=(uint16)(F_CPU/(Copy_u16Freq*Global_Prescaler))-1;
	u16Current_Freq	=	Copy_u16Freq;
}

void PWM_vSetPWM_Freq(uint16 Copy_u16Freq)
{
	/*The PWM resolution for Phase correct PWM can be fixed to 8-bit, 9-bit, or 10-bit, or defined by either ICR1
	or OCR1A*/
	ICR1=(uint16)(F_CPU/(Copy_u16Freq*Global_Prescaler*2));
	u16Current_Freq	=	Copy_u16Freq;
}


Error_Status PWM_xSet_TONus(uint16 Copy_u16Time,PWM_Channels Copy_xChannel)
{
	uint16 Local_u16Val;
	Local_u16Val =(uint16)(Copy_u16Time/((Global_Prescaler*1000000)/F_CPU));

	switch(Copy_xChannel)
	{
	case PWM_CH_1:
		OCR1A	=	Local_u16Val;
		break;
	case PWM_CH_2:
		OCR1B	=	Local_u16Val;
		break;
	default:
		return E_NOK;
		break;
	}
	return E_OK;
}

Error_Status PWM_xSetValReg(PWM_Channels Copy_xChannel,uint16 Copy_u16Val)
{
	switch(Copy_xChannel)
		{
		case PWM_CH_1:
			OCR1A	=	Copy_u16Val;
			break;
		case PWM_CH_2:
			OCR1B	=	Copy_u16Val;
			break;
		default:
			return E_NOK;
			break;
		}
		return E_OK;
}
