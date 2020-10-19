/* ******************************************************   */
/*  GPIO_program.c										    */
/*  Version: 1.0											*/
/*  Author : Eslam Ehab Aboutaleb							*/
/* ******************************************************   */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_config.h"
#include "GPIO_private.h"
#include "GPIO_interface.h"

/* ***************************************************************************** */
/* GPIO validation */
/* GPIO Port validation */
#define GPIO_IS_VALID_PORT(PORTx)					(GPIOA == PORTx || GPIOB == PORTx ||\
		GPIOC == PORTx	|| GPIOD == PORTx ||\
		GPIOD == PORTx)

/* GPIO Pin validation */
#define GPIO_IS_VALID_PIN(PINx)						(PINx  <  GPIO_NPINS_PER_PORT)

/* Mode validation */
#define GPIO_IS_VALID_MODE(MODEx)					(GPIO_OUT  == MODEx   || GPIO_IN == MODEx)

/* GPIO Value validation */
#define GPIO_IS_VALID_VALUE(STATEx)					(GPIO_HIGH == STATEx || GPIO_LOW == STATEx)

/* ***************************************************************************** */

void GPIO_vInit(GPIO_ConfigType *xpGIPO_Config)
{
	uint8 u8PinsIndex	=	0;

	for(u8PinsIndex = 0;NULL != xpGIPO_Config; u8PinsIndex++)
	{
/* Error checking sequence */
#if ERROR_CHECK	==	E_OK
		/* Check port validation */
		if(!GPIO_IS_VALID_PORT((xpGIPO_Config->Pins[u8PinsIndex].xPort)))
		{
			ErrorM_vReport(GPIO_MODULE_ID,GPIO_INSTANCE_ID,GPIO_INIT_CHANNEL_SID,GPIO_E_PARAM_INVALID_PORT_ID);
		}
		/* Check pin validation */
		if(!GPIO_IS_VALID_PIN((xpGIPO_Config->Pins[u8PinsIndex].xPin_Num)))
		{
			ErrorM_vReport(GPIO_MODULE_ID,GPIO_INSTANCE_ID,GPIO_INIT_CHANNEL_SID,GPIO_E_PARAM_INVALID_CHANNEL_ID);
		}
		/* Check mode validation */
		if(!GPIO_IS_VALID_MODE((xpGIPO_Config->Pins[u8PinsIndex].xPin_Mode)))
		{
			ErrorM_vReport(GPIO_MODULE_ID,GPIO_INSTANCE_ID,GPIO_INIT_CHANNEL_SID,GPIO_E_PARAM_STATE);
		}
#endif

		/*
		 * Check which port is needed and set the pin if the mode is GPIO_OUT
		 * and clear the pin if the mode is GPIO_IN
		 *                                                                     */
		switch(xpGIPO_Config->Pins[u8PinsIndex].xPort)
		{
		case GPIOA:
			if (GPIO_OUT == (xpGIPO_Config->Pins[u8PinsIndex].xPin_Mode)) {
				SET_BIT(DDRA,(xpGIPO_Config->Pins[u8PinsIndex].xPin_Num));
			}
			else {
				CLEAR_BIT(DDRA,(xpGIPO_Config->Pins[u8PinsIndex].xPin_Num));
			}
			break;
		case GPIOB:
			if (GPIO_OUT == (xpGIPO_Config->Pins[u8PinsIndex].xPin_Mode)) {
				SET_BIT(DDRB,(xpGIPO_Config->Pins[u8PinsIndex].xPin_Num));
			}
			else {
				CLEAR_BIT(DDRB,(xpGIPO_Config->Pins[u8PinsIndex].xPin_Num));
			}
			break;
		case GPIOC:
			if (GPIO_OUT == (xpGIPO_Config->Pins[u8PinsIndex].xPin_Mode)) {
				SET_BIT(DDRC,(xpGIPO_Config->Pins[u8PinsIndex].xPin_Num));
			}
			else {
				CLEAR_BIT(DDRC,(xpGIPO_Config->Pins[u8PinsIndex].xPin_Num));
			}
			break;
		case GPIOD:
			if (GPIO_OUT == (xpGIPO_Config->Pins[u8PinsIndex].xPin_Mode)) {
				SET_BIT(DDRD,(xpGIPO_Config->Pins[u8PinsIndex].xPin_Num));
			}
			else {
				CLEAR_BIT(DDRD,(xpGIPO_Config->Pins[u8PinsIndex].xPin_Num));
			}
			break;
		default:
			break;

		}

	}
}

/* ***************************************************************************** */

void GPIO_vInitPortPin(GPIO_Port_t Copy_xGPIOx,GPIO_Pin_t Copy_xPinx ,GPIO_PinMode_t Copy_xMode)
{
#if ERROR_CHECK	==	E_OK
		/* Check port validation */
		if(!GPIO_IS_VALID_PORT(Copy_xGPIOx))
		{
			ErrorM_vReport(GPIO_MODULE_ID,GPIO_INSTANCE_ID,GPIO_INIT_CHANNEL_SID,GPIO_E_PARAM_INVALID_PORT_ID);
		}
		/* Check pin validation */
		if(!GPIO_IS_VALID_PIN(Copy_xPinx))
		{
			ErrorM_vReport(GPIO_MODULE_ID,GPIO_INSTANCE_ID,GPIO_INIT_CHANNEL_SID,GPIO_E_PARAM_INVALID_CHANNEL_ID);
		}
		/* Check mode validation */
		if(!GPIO_IS_VALID_MODE(Copy_xMode))
		{
			ErrorM_vReport(GPIO_MODULE_ID,GPIO_INSTANCE_ID,GPIO_INIT_CHANNEL_SID,GPIO_E_PARAM_STATE);
		}
#endif
	switch(Copy_xGPIOx) {
	case GPIOA:
		if (Copy_xMode == GPIO_OUT) {
			SET_BIT(DDRA,Copy_xPinx);
		}
		else {
			CLEAR_BIT(DDRA,Copy_xPinx);
		}
		break;
	case GPIOB:
		if (Copy_xMode == GPIO_OUT) {
			SET_BIT(DDRB,Copy_xPinx);
		}
		else {
			CLEAR_BIT(DDRB,Copy_xPinx);
		}
		break;
	case GPIOC:
		if (Copy_xMode == GPIO_OUT) {
			SET_BIT(DDRC,Copy_xPinx);
		}
		else {
			CLEAR_BIT(DDRC,Copy_xPinx);
		}
		break;
	case GPIOD:
		if (Copy_xMode == GPIO_OUT) {
			SET_BIT(DDRD,Copy_xPinx);
		}
		else {
			CLEAR_BIT(DDRD,Copy_xPinx);
		}
		break;
	default:
		break;
	}
}

/* ***************************************************************************** */

void GPIO_vWritePortPin(GPIO_Port_t Copy_xGPIOx ,GPIO_Pin_t Copy_xPinx ,GPIO_PinState_t Copy_xVal)
{
#if ERROR_CHECK	==	E_OK
	/* Check port validation */
		if(!GPIO_IS_VALID_PORT(Copy_xGPIOx))
		{
			ErrorM_vReport(GPIO_MODULE_ID,GPIO_INSTANCE_ID,GPIO_WRITE_CHANNEL_SID,GPIO_E_PARAM_INVALID_PORT_ID);
		}
		/* Check pin validation */
		if(!GPIO_IS_VALID_PIN(Copy_xPinx))
		{
			ErrorM_vReport(GPIO_MODULE_ID,GPIO_INSTANCE_ID,GPIO_WRITE_CHANNEL_SID,GPIO_E_PARAM_INVALID_CHANNEL_ID);
		}
		/* Check value validation */
		if(!GPIO_IS_VALID_VALUE(Copy_xVal))
		{
			ErrorM_vReport(GPIO_MODULE_ID,GPIO_INSTANCE_ID,GPIO_WRITE_CHANNEL_SID,GPIO_E_PARAM_STATE);
		}
#endif
	switch(Copy_xGPIOx) {
	case GPIOA:
		if (Copy_xVal == GPIO_HIGH) {
			SET_BIT(PORTA,Copy_xPinx);
		}
		else {
			CLEAR_BIT(PORTA,Copy_xPinx);
		}
		break;
	case GPIOB:
		if (Copy_xVal == GPIO_HIGH) {
			SET_BIT(PORTB,Copy_xPinx);
		}
		else {
			CLEAR_BIT(PORTB,Copy_xPinx);
		}
		break;
	case GPIOC:
		if (Copy_xVal == GPIO_HIGH) {
			SET_BIT(PORTC,Copy_xPinx);
		}
		else {
			CLEAR_BIT(PORTC,Copy_xPinx);
		}
		break;
	case GPIOD:
		if (Copy_xVal == GPIO_HIGH) {
			SET_BIT(PORTD,Copy_xPinx);
		}
		else {
			CLEAR_BIT(PORTD,Copy_xPinx);
		}
		break;
	default:
		break;
	}


}

/* ***************************************************************************** */

GPIO_PinState_t GPIO_xReadPortPin(GPIO_Port_t Copy_xGPIOx ,GPIO_Pin_t Copy_xPinx)
{
#if ERROR_CHECK	==	E_OK
	/* Check port validation */
		if(!GPIO_IS_VALID_PORT(Copy_xGPIOx))
		{
			ErrorM_vReport(GPIO_MODULE_ID,GPIO_INSTANCE_ID,GPIO_READ_CHANNEL_SID,GPIO_E_PARAM_INVALID_PORT_ID);
		}
		/* Check pin validation */
		if(!GPIO_IS_VALID_PIN(Copy_xPinx))
		{
			ErrorM_vReport(GPIO_MODULE_ID,GPIO_INSTANCE_ID,GPIO_READ_CHANNEL_SID,GPIO_E_PARAM_INVALID_CHANNEL_ID);
		}
#endif

	GPIO_PinState_t GPIO_xState = 0;
	switch(Copy_xGPIOx) {
	case GPIOA:
		GPIO_xState = GET_BIT(PINA,Copy_xPinx);
		break;
	case GPIOB:
		GPIO_xState = GET_BIT(PINB,Copy_xPinx);
		break;
	case GPIOC:
		GPIO_xState = GET_BIT(PINC, Copy_xPinx);
		break;
	case GPIOD:
		GPIO_xState = GET_BIT(PIND,Copy_xPinx);
		break;
	default:
		break;
	}
	return GPIO_xState;
}

