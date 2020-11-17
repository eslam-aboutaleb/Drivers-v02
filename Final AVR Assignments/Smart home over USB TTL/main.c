/* **************************************************************************** */
/* Author	: Eslam Ehab Aboutaleb												*/
/* Date		: 10/11/2020														*/
/* version	: V01																*/
/* **************************************************************************** */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "USART_interface.h"
#include "USART_private.h"
#include "Home_interface.h"
#include "ADC_interface.h"
#include "TempS_interface.h"
#include "PWM_interface.h"
#include "Alarm_interface.h"
#include "LDR_interface.h"
#include "Display_interface.h"
#include "Util_String_interface.h"


int main(void)
{
	/* Initialize USART */
	USART_ConfigType USART_DATA;
	USART_DATA.BaudRate	=	9600;
	USART_DATA.DataSize	=	USART_EIGHT_BITS;
	USART_DATA.Parity	=	USART_PARITY_OFF;
	USART_DATA.StopBit	=	USART_ONE_STOP_BIT;
	USART_DATA.State	=	USART_TRANSMITER_RECIEVER;

	USART_xInit(USART1,&USART_DATA);

	ADC_Typedef ADC_DATA;

	/* Initialize ADC */
	GPIO_vInitPortPin(GPIOA,GPIO_PIN_0,GPIO_IN);

	ADC_DATA.ADC_xAdjustState 	= ADC_LEFT_ADJUST;
	ADC_DATA.ADC_xState 		= ADC_ENABLE;
	ADC_DATA.ADC_xPrescaler 	= ADC_PRESCALER_128;
	ADC_DATA.ADC_xVoltRef 		= ADC_AVCC_EX_CAP;
	ADC_DATA.ADC_xInterruptState= ADC_DISABLE_INTERRUPT;
	ADC_DATA.ADC_xTriggerState	= ADC_ENABLE_AUTO_TRIGGER;
	ADC_DATA.ADC_xTriggerSource = ADC_TRSRC_FREE_RUNNING_MODE;

	ADC_xInit(&ADC_DATA);

	/*Initialize PWM*/
	PWM_Typedef PWM_DATA;
	PWM_DATA.Mode		=	TIMER1_WGM_FPWM_ICR;
	PWM_DATA.COM_Mode	=	Clr_OC1A_OC1B_CompMatchNonInvert;
	PWM_DATA.Channel	=	PWM_CH_1;
	PWM_DATA.Prescaler	=	PWM_Prescaler_256;
	PWM_vInit(&PWM_DATA);
	PWM_vSetFPWM_Freq(50);

	/* Initialize temperature sensor */
	TempS_vInit();
	/* Initialize LDR */
	LDR_vInit();

	/* Initialize Alarm */
	Alarm_xInit(ALARM_1,ALARM_OFF);

	/* Initialize Home settings */
	Home_vInit();

	while(1)
	{
		if(Home_xEnter() == E_OK)
		{
			while(Home_xOptionHandle() == E_OK);
		}
	}

	return 0;
}
