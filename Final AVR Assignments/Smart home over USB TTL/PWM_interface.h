/* ***********************************************************  */
/*  PWM_interface.h											    */
/*  Version		: 1.0											*/
/*  Author 		: Eslam Ehab Aboutaleb							*/
/* 	Description	: GPIO driver 									*/
/* ***********************************************************  */

#ifndef PWM_INTERFACE_H_
#define PWM_INTERFACE_H_

#ifndef TIMER1_ENABLED
#define TIMER1_PWM_ENABLED
#endif

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#define PWM_OCR1A_PORT    'D'
#define PWM_OCR1B_PORT    'D'

#define PWM_OCR1A_PIN      5
#define PWM_OCR1B_PIN      4

typedef enum
{
	Normal_Port_Operation,
	Tog_OC1A_CompMatch_OC1B_Disconnected,
	Clr_OC1A_OC1B_CompMatchNonInvert,
	Set_OC1A_OC1B_CompMatchInvert
}PWM_Com_OutputMode;

typedef enum
{
	PWM_CH_1,
	PWM_CH_2
}PWM_Channels;

typedef enum
{
TIMER1_WGM_PWM_8      ,
TIMER1_WGM_PWM_9      ,
TIMER1_WGM_PWM_10     ,
TIMER1_WGM_FPWM_8     ,
TIMER1_WGM_FPWM_9     ,
TIMER1_WGM_FPWM_10    ,
TIMER1_WGM_PWM_PF_ICR ,
TIMER1_WGM_PWM_PF_OCR ,
TIMER1_WGM_PWM_P_ICR  ,
TIMER1_WGM_PWM_P_OCR  ,
TIMER1_WGM_FPWM_ICR   ,
TIMER1_WGM_FPWM_OCR

}PWM_Mode;


typedef enum
{
	PWM_NO_Clock_Source,
	PWM_Prescaler_1,
	PWM_Prescaler_8,
	PWM_Prescaler_64,
	PWM_Prescaler_256,
	PWM_Prescaler_1024,
	PWM_Preascaler_ExClockT1_Falling,
	PWM_Preascaler_ExClockT1_Rising
}PWM_ClockPrescaler;

typedef struct
{
	PWM_Com_OutputMode COM_Mode;
	PWM_Mode Mode;
	PWM_Channels Channel;
	PWM_ClockPrescaler	Prescaler;
}PWM_Typedef;


Error_Status PWM_vInit(PWM_Typedef *PWM_ConfigPtr);
void PWM_vStop(void);
Error_Status PWM_xSetPrescaler(PWM_ClockPrescaler Copy_xPrescaler);
Error_Status PWM_xSetChannels(PWM_Channels Copy_xChannel,PWM_Com_OutputMode Copy_xOutputMode);
void PWM_vSetFPWM_Freq(uint16 Copy_u16Freq);
void PWM_vSetPWM_Freq(uint16 Copy_u16Freq);
Error_Status PWM_xSetDutyCycle(PWM_Channels Copy_xChannel,float32 Copy_f32DutyCycle);
Error_Status PWM_xSet_TONus(uint16 Copy_u16Time,PWM_Channels Copy_xChannel);
Error_Status PWM_xSetValReg(PWM_Channels Copy_xChannel,uint16 Copy_u16Val);

#endif /* PWM_INTERFACE_H_ */
