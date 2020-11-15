/* **************************************************************************** */
/* Author	: Eslam Ehab Aboutaleb												*/
/* Date		: 10/11/2020														*/
/* version	: V01																*/
/* **************************************************************************** */

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

/* ***************************************************************************** */

/* ADC registers */
#define ADMUX										(*(volatile uint8	*) 0x0027)
#define ADCSRA										(*(volatile uint8	*) 0x0026)
#define ADCH										(*(volatile uint8	*) 0x0025)
#define ADCL										(*(volatile uint8	*) 0x0024)

#define ADCBUF_REG									(*(volatile uint16	*) 0x0024)

#define	SFIOR										(*(volatile uint8	*) 0x0050)

/* ***************************************************************************** */

/* ADC pins */
#define REFS1											7
#define REFS0											6
#define ADEN											7
#define ADIE											3
#define ADIF											4
#define ADATE											5
#define ADSC											6
#define ADLAR											5

/* ***************************************************************************** */
/* ADC errors checking */
#define ADC_IS_VALID_CH(ChNum)						(ChNum < ADC_N_CH_OPTIONS)
#define ADC_IS_VALID_PRESCALER(PreScaler)			(PreScaler <= ADC_PRESCALER_128)
#define ADC_IS_VALID_TRGSRC(Src)					(Src <= ADC_TRSRC_TIMER_CAPTURE_EVENT)

/* ***************************************************************************** */

/* ADC Flag macros */
#define ADC_CHECK_FLAG()							while(GET_BIT(ADCSRA,ADIF) == E_NOK);
#define ADC_CLEAR_FALG()							SET_BIT(ADCSRA,ADIF)

/* ***************************************************************************** */

/* ADC start conversion */
#define ADC_START_CONVERSION();						SET_BIT(ADCSRA,ADSC)

/* ***************************************************************************** */
							/* ADC IRQ prototype */
/* ***************************************************************************** */
#define ADC_IRQ										__vector16

void ADC_IRQ(void) __attribute__ ((signal));


/* ***************************************************************************** */
							/* ADC private prototypes */
/* ***************************************************************************** */
static Error_Status ADC_xRefVoltage(ADC_VoltageRef_t Copy_xVoltRef);

/* ***************************************************************************** */
static Error_Status ADC_xAdjustResult(ADC_Adjust_t Copy_xAdjustState);
/* ***************************************************************************** */

static Error_Status ADC_xSetAutoTrigger(ADC_AutoTrigger_t Copy_xTrigger);
/* ***************************************************************************** */

static Error_Status ADC_xSetPrescaler(ADC_Prescaler_t Copy_xPrescaler);
/* ***************************************************************************** */

static Error_Status ADC_xSetTriggerSrc(ADC_TriggerSrc_t Copy_xSrc);
/* ***************************************************************************** */


#endif /* ADC_PRIVATE_H_ */
