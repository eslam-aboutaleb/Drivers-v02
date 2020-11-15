/*
 * ADC_interface.h
 *
 *  Created on: Nov 3, 2020
 *      Author: Dell
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

/* ***************************************************************************** */
typedef enum{
	ADC_VREF_TURNED_OFF,
	ADC_AVCC_EX_CAP,
	ADC_INTERNAL_VOLTAGE_2_56
}ADC_VoltageRef_t;

/* ***************************************************************************** */
typedef enum{
	ADC_LEFT_ADJUST,
	ADC_RIGHT_ADJUST
}ADC_Adjust_t;

/* ***************************************************************************** */
typedef enum{
	ADC_CH_0,
	ADC_CH_1,
	ADC_CH_2,
	ADC_CH_3,
	ADC_CH_4,
	ADC_CH_5,
	ADC_CH_6,
	ADC_CH_7,
	ADC_DIFFRENTIAL_CH0_CH0_G10x,
	ADC_DIFFRENTIAL_CH1_CH0_G10x,
	ADC_DIFFRENTIAL_CH0_CH0_G200x,
	ADC_DIFFRENTIAL_CH1_CH0_G200x,
	ADC_DIFFRENTIAL_CH2_CH2_G10x,
	ADC_DIFFRENTIAL_CH3_CH2_G10x,
	ADC_DIFFRENTIAL_CH2_CH2_G200x,
	ADC_DIFFRENTIAL_CH3_CH2_G200x,
	ADC_DIFFRENTIAL_CH0_CH1_G1x,
	ADC_DIFFRENTIAL_CH1_CH1_G1x,
	ADC_DIFFRENTIAL_CH2_CH1_G1x,
	ADC_DIFFRENTIAL_CH3_CH1_G1x,
	ADC_DIFFRENTIAL_CH4_CH1_G1x,
	ADC_DIFFRENTIAL_CH5_CH1_G1x,
	ADC_DIFFRENTIAL_CH6_CH1_G1x,
	ADC_DIFFRENTIAL_CH7_CH1_G1x,
	ADC_DIFFRENTIAL_CH0_CH2_G1x,
	ADC_DIFFRENTIAL_CH1_CH2_G1x,
	ADC_DIFFRENTIAL_CH2_CH2_G1x,
	ADC_DIFFRENTIAL_CH3_CH2_G1x,
	ADC_DIFFRENTIAL_CH4_CH2_G1x,
	ADC_DIFFRENTIAL_CH5_CH2_G1x,
}ADC_Ch_t;

/* ***************************************************************************** */
typedef enum{
	ADC_DISABLE,
	ADC_ENABLE
}ADC_State_t;

/* ***************************************************************************** */
typedef enum{
	ADC_DISABLE_INTERRUPT,
	ADC_ENABLE_INTERRUPT
}ADC_Int_t;

/* ***************************************************************************** */
typedef enum{
	ADC_DISABLE_AUTO_TRIGGER,
	ADC_ENABLE_AUTO_TRIGGER
}ADC_AutoTrigger_t;

/* ***************************************************************************** */
typedef enum{
	ADC_PRESCALER_2,
	ADC_PRESCALER_2C,
	ADC_PRESCALER_4,
	ADC_PRESCALER_8,
	ADC_PRESCALER_16,
	ADC_PRESCALER_32,
	ADC_PRESCALER_64,
	ADC_PRESCALER_128,
}ADC_Prescaler_t;
/* ***************************************************************************** */
typedef enum{
	ADC_TRSRC_FREE_RUNNING_MODE,
	ADC_TRSRC_ANALOG_COMPARATOR,
	ADC_TRSRC_EX_INT_REQ,
	ADC_TRSRC_TIMER0_COMPARE_MATCH,
	ADC_TRSRC_TIMER0OVERFLOW,
	ADC_TRSRC_TIMER1_COMPARE_MATCH,
	ADC_TRSRC_TIMER_OVERFLOW,
	ADC_TRSRC_TIMER_CAPTURE_EVENT
}ADC_TriggerSrc_t;

/* ***************************************************************************** */
typedef struct{
	ADC_Ch_t 			ADC_xChannel;
	ADC_Prescaler_t		ADC_xPrescaler;
	ADC_VoltageRef_t	ADC_xVoltRef;
	ADC_Adjust_t		ADC_xAdjustState;
	ADC_Int_t			ADC_xInterruptState;
	ADC_AutoTrigger_t	ADC_xTriggerState;
	ADC_TriggerSrc_t	ADC_xTriggerSource;
	ADC_State_t			ADC_xState;
}ADC_Typedef;

/* ***************************************************************************** */
							/* Functions prototypes */
/* ***************************************************************************** */

/* ***************************************************************************** */
/* Function		: 	ADC_xInit
 * Return  		: 	Error_Status		, Type	:	User defined
 * Parameters	:	ADCx				, Type	:	struct ADC_Typedef
 * Description	: 	- Function to initialize the ADC structure
 */
/* ***************************************************************************** */
Error_Status ADC_xInit(const ADC_Typedef *ADCx);

/* ***************************************************************************** */
/* Function		: 	ADC_xSelectChannel
 * Return  		: 	Error_Status		, Type	:	User defined
 * Parameters	:	Copy_xChannel		, Type	:	User defined
 * Description	: 	- Function to select ADC channel
 */
/* ***************************************************************************** */
Error_Status ADC_xSelectChannel(ADC_Ch_t Copy_xChannel);

/* ***************************************************************************** */
/* Function		: 	ADC_xSetState
 * Return  		: 	Error_Status		, Type	:	User defined
 * Parameters	:	Copy_xState			, Type	:	User defined
 * Description	: 	- Function to enable and disable ADC
 */
/* ***************************************************************************** */
Error_Status ADC_xSetState(ADC_State_t Copy_xState);

/* ***************************************************************************** */
/* Function		: 	ADC_xSetIntState
 * Return  		: 	Error_Status		, Type	:	User defined
 * Parameters	:	Copy_xState			, Type	:	User defined
 * Description	: 	- Function to enable and disable ADC interrupt
 */
/* ***************************************************************************** */
Error_Status ADC_xSetIntState(ADC_Int_t Copy_xState);

/* ***************************************************************************** */
/* Function		: 	ADC_xReadSynch
 * Return  		: 	Error_Status		, Type	:	User defined
 * Parameters	:	Copy_xADC_Chx		, Type	:	User defined
 * 					u16RecvData			, Type	:	Pointer to uint16
 * Description	: 	- Function to read synchronous ADC data
 */
/* ***************************************************************************** */
Error_Status ADC_xReadSynch(ADC_Ch_t Copy_xADC_Chx,uint16 *u16RecvData);

/* ***************************************************************************** */
/* Function		: 	ADC_xReadUpperRegSynch
 * Return  		: 	Error_Status		, Type	:	User defined
 * Parameters	:	Copy_xADC_Chx		, Type	:	User defined
 * 					u8RecvData			, Type	:	Pointer to uint8
 * Description	: 	- Function to read synchronous ADC higher register data
 */
/* ***************************************************************************** */
Error_Status ADC_xReadUpperRegSynch(ADC_Ch_t Copy_xADC_Chx,uint8 *u8RecvData);

/* ***************************************************************************** */
/* Function		: 	ADC_xReadASynch
 * Return  		: 	Error_Status		, Type	:	User defined
 * Parameters	:	Copy_xADC_Chx		, Type	:	User defined
 * 					pvCallBack			, Type	:	Pointer to function returns
 * 													void and takes uint16
 * Description	: 	- Function to read synchronous ADC data
 */
/* ***************************************************************************** */
Error_Status ADC_xReadASynch(ADC_Ch_t Copy_xADC_Chx,void (*pvCallBack)(uint16));

/* ***************************************************************************** */
#endif /* ADC_INTERFACE_H_ */

