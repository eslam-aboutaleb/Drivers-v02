/* ***********************************************************  */
/*  GPIO_program.c											    */
/*  Version		: 1.0											*/
/*  Author 		: Eslam Ehab Aboutaleb							*/
/* 	Description	: GPIO driver 									*/
/* ***********************************************************  */

/* Dependencies */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrorM_interface.h"
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

/* Mode pin validation */
#define GPIO_IS_VALID_MODE(MODEx)					(GPIO_OUT  == MODEx   || GPIO_IN == MODEx)

/* GPIO pin Value validation */
#define GPIO_IS_VALID_VALUE(STATEx)					(GPIO_HIGH == STATEx || GPIO_LOW == STATEx)

/* GPIO port mode and value validation */
#define GPIO_IS_PORT_VAL_MODE(STATEx)				(STATEx < 0x00FF)


/* ***************************************************************************** */

void GPIO_vInit(GPIO_ConfigType *xpGIPO_Config)
{
	uint8 Local_u8PinsIndex	=	0;

	for(Local_u8PinsIndex = 0;NULL != xpGIPO_Config; Local_u8PinsIndex++)
	{
		/* Error checking sequence */
#if ERROR_CHECK	==	E_OK
		/* Check port validation */
		if(E_NOK == GPIO_IS_VALID_PORT((xpGIPO_Config->Pins[Local_u8PinsIndex].xPort)))
		{
			ErrorM_vReport(GPIO_MODULE_ID,GPIO_INSTANCE_ID,GPIO_INIT_CHANNEL_SID,GPIO_E_PARAM_INVALID_PORT_ID);
		}
		/* Check pin validation */
		if(E_NOK == GPIO_IS_VALID_PIN((xpGIPO_Config->Pins[Local_u8PinsIndex].xPin_Num)))
		{
			ErrorM_vReport(GPIO_MODULE_ID,GPIO_INSTANCE_ID,GPIO_INIT_CHANNEL_SID,GPIO_E_PARAM_INVALID_CHANNEL_ID);
		}
		/* Check mode validation */
		if(E_NOK == GPIO_IS_VALID_MODE((xpGIPO_Config->Pins[Local_u8PinsIndex].xPin_Mode)))
		{
			ErrorM_vReport(GPIO_MODULE_ID,GPIO_INSTANCE_ID,GPIO_INIT_CHANNEL_SID,GPIO_E_PARAM_STATE);
		}
#endif

		/*
		 * Check which port is needed and set the pin if the mode is GPIO_OUT
		 * and clear the pin if the mode is GPIO_IN
		 *                                                                     */
		switch(xpGIPO_Config->Pins[Local_u8PinsIndex].xPort)
		{
		case GPIOA:
			if (GPIO_OUT == (xpGIPO_Config->Pins[Local_u8PinsIndex].xPin_Mode)) {
				SET_BIT(DDRA,(xpGIPO_Config->Pins[Local_u8PinsIndex].xPin_Num));
			}
			else {
				CLEAR_BIT(DDRA,(xpGIPO_Config->Pins[Local_u8PinsIndex].xPin_Num));
			}
			break;
		case GPIOB:
			if (GPIO_OUT == (xpGIPO_Config->Pins[Local_u8PinsIndex].xPin_Mode)) {
				SET_BIT(DDRB,(xpGIPO_Config->Pins[Local_u8PinsIndex].xPin_Num));
			}
			else {
				CLEAR_BIT(DDRB,(xpGIPO_Config->Pins[Local_u8PinsIndex].xPin_Num));
			}
			break;
		case GPIOC:
			if (GPIO_OUT == (xpGIPO_Config->Pins[Local_u8PinsIndex].xPin_Mode)) {
				SET_BIT(DDRC,(xpGIPO_Config->Pins[Local_u8PinsIndex].xPin_Num));
			}
			else {
				CLEAR_BIT(DDRC,(xpGIPO_Config->Pins[Local_u8PinsIndex].xPin_Num));
			}
			break;
		case GPIOD:
			if (GPIO_OUT == (xpGIPO_Config->Pins[Local_u8PinsIndex].xPin_Mode)) {
				SET_BIT(DDRD,(xpGIPO_Config->Pins[Local_u8PinsIndex].xPin_Num));
			}
			else {
				CLEAR_BIT(DDRD,(xpGIPO_Config->Pins[Local_u8PinsIndex].xPin_Num));
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
	if(E_NOK == GPIO_IS_VALID_PORT(Copy_xGPIOx))
	{
		ErrorM_vReport(GPIO_MODULE_ID,GPIO_INSTANCE_ID,GPIO_INIT_CHANNEL_SID,GPIO_E_PARAM_INVALID_PORT_ID);
	}
	/* Check pin validation */
	if(E_NOK == GPIO_IS_VALID_PIN(Copy_xPinx))
	{
		ErrorM_vReport(GPIO_MODULE_ID,GPIO_INSTANCE_ID,GPIO_INIT_CHANNEL_SID,GPIO_E_PARAM_INVALID_CHANNEL_ID);
	}
	/* Check mode validation */
	if(E_NOK == GPIO_IS_VALID_MODE(Copy_xMode))
	{
		ErrorM_vReport(GPIO_MODULE_ID,GPIO_INSTANCE_ID,GPIO_INIT_CHANNEL_SID,GPIO_E_PARAM_STATE);
	}
#endif
	/*
	 * Check which port is needed and set the pin if the mode is GPIO_OUT
	 * and clear the pin if the mode is GPIO_IN
	 *                                                                     */
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
	if(E_NOK == GPIO_IS_VALID_PORT(Copy_xGPIOx))
	{
		ErrorM_vReport(GPIO_MODULE_ID,GPIO_INSTANCE_ID,GPIO_WRITE_CHANNEL_SID,GPIO_E_PARAM_INVALID_PORT_ID);
	}
	/* Check pin validation */
	if(E_NOK == GPIO_IS_VALID_PIN(Copy_xPinx))
	{
		ErrorM_vReport(GPIO_MODULE_ID,GPIO_INSTANCE_ID,GPIO_WRITE_CHANNEL_SID,GPIO_E_PARAM_INVALID_CHANNEL_ID);
	}
	/* Check value validation */
	if(E_NOK == GPIO_IS_VALID_VALUE(Copy_xVal))
	{
		ErrorM_vReport(GPIO_MODULE_ID,GPIO_INSTANCE_ID,GPIO_WRITE_CHANNEL_SID,GPIO_E_PARAM_STATE);
	}
#endif

	/*
	 * Check which port is needed and set the pin if the mode is GPIO_HIGH
	 * and clear the pin if the mode is GPIO_LOW
	 *                                                                     */
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
	if(E_NOK == GPIO_IS_VALID_PORT(Copy_xGPIOx))
	{
		ErrorM_vReport(GPIO_MODULE_ID,GPIO_INSTANCE_ID,GPIO_READ_CHANNEL_SID,GPIO_E_PARAM_INVALID_PORT_ID);
	}
	/* Check pin validation */
	if(E_NOK == GPIO_IS_VALID_PIN(Copy_xPinx))
	{
		ErrorM_vReport(GPIO_MODULE_ID,GPIO_INSTANCE_ID,GPIO_READ_CHANNEL_SID,GPIO_E_PARAM_INVALID_CHANNEL_ID);
	}
#endif


	/* Get the state of the pin based on specific port and pin */
	GPIO_PinState_t Local_GPIO_xState = 0;
	switch(Copy_xGPIOx) {
	case GPIOA:
		Local_GPIO_xState = GET_BIT(PINA,Copy_xPinx);
		break;
	case GPIOB:
		Local_GPIO_xState = GET_BIT(PINB,Copy_xPinx);
		break;
	case GPIOC:
		Local_GPIO_xState = GET_BIT(PINC, Copy_xPinx);
		break;
	case GPIOD:
		Local_GPIO_xState = GET_BIT(PIND,Copy_xPinx);
		break;
	default:
		break;
	}
	/* Return the state */
	return Local_GPIO_xState;
}

GPIO_PinState_t GPIO_xFlipPortPin(GPIO_Port_t Copy_xGPIOx ,GPIO_Pin_t Copy_xPinx)
{
#if ERROR_CHECK	==	E_OK
	/* Check port validation */
	if(E_NOK == GPIO_IS_VALID_PORT(Copy_xGPIOx))
	{
		ErrorM_vReport(GPIO_MODULE_ID,GPIO_INSTANCE_ID,GPIO_FLIP_CHANNEL_SID,GPIO_E_PARAM_INVALID_PORT_ID);
	}
	/* Check pin validation */
	if(E_NOK == GPIO_IS_VALID_PIN(Copy_xPinx))
	{
		ErrorM_vReport(GPIO_MODULE_ID,GPIO_INSTANCE_ID,GPIO_FLIP_CHANNEL_SID,GPIO_E_PARAM_INVALID_CHANNEL_ID);
	}
#endif

	/* Toggle the pin if it is high turn it to low and vice versa */
	GPIO_PinState_t Local_xState = GPIO_xReadPortPin(Copy_xGPIOx,Copy_xPinx);
	switch(Local_xState)
	{
	case GPIO_HIGH:
		GPIO_vWritePortPin(Copy_xGPIOx,Copy_xPinx,GPIO_LOW);
		break;
	case GPIO_LOW:
		GPIO_vWritePortPin(Copy_xGPIOx,Copy_xPinx,GPIO_HIGH);
		break;
	default:
		break;
	}
	/* Return the current state */
	Local_xState = ~ Local_xState;

	return Local_xState;
}
void GPIO_vInitPort(GPIO_Port_t Copy_xGPIOx ,GPIO_PortMode_t Copy_xMode)
{
#if ERROR_CHECK	==	E_OK
	/* Check if it is valid port */
	if(E_NOK == GPIO_IS_PORT_VAL_MODE(Copy_xGPIOx))
	{
		ErrorM_vReport(GPIO_MODULE_ID,GPIO_INSTANCE_ID,GPIO_INIT_PORT_SID,GPIO_E_PARAM_INVALID_PORT_ID);
	}
	/* Check if it is valid mode */
	if(E_NOK == GPIO_IS_PORT_VAL_MODE(Copy_xMode))
	{
		ErrorM_vReport(GPIO_MODULE_ID,GPIO_INSTANCE_ID,GPIO_INIT_PORT_SID,GPIO_E_PARAM_STATE);
	}
#endif
	/* Assign the mode to the port */
	switch(Copy_xGPIOx) {
	case GPIOA:
		DDRA = Copy_xMode;
		break;
	case GPIOB:
		DDRB = Copy_xMode;
		break;
	case GPIOC:
		DDRC = Copy_xMode;
		break;
	case GPIOD:
		DDRD = Copy_xMode;
		break;
	default:
		break;
	}
}

void GPIO_vWritePort(GPIO_Port_t Copy_xGPIOx ,GPIO_PortState_t Copy_xVal)
{
#if ERROR_CHECK	==	E_OK
	/* Check if it is valid port */
	if(E_NOK == GPIO_IS_PORT_VAL_MODE(Copy_xGPIOx))
	{
		ErrorM_vReport(GPIO_MODULE_ID,GPIO_INSTANCE_ID,GPIO_WRITE_PORT_SID,GPIO_E_PARAM_INVALID_PORT_ID);
	}
	/* Check if it is valid value */
	if(E_NOK == GPIO_IS_PORT_VAL_MODE(Copy_xVal))
	{
		ErrorM_vReport(GPIO_MODULE_ID,GPIO_INSTANCE_ID,GPIO_WRITE_PORT_SID,GPIO_E_PARAM_STATE);
	}
#endif

	/* Assign the value to the port */
	switch(Copy_xGPIOx) {
	case GPIOA:
		DDRA = Copy_xVal;
		break;
	case GPIOB:
		DDRB = Copy_xVal;
		break;
	case GPIOC:
		DDRC = Copy_xVal;
		break;
	case GPIOD:
		DDRD = Copy_xVal;
		break;
	default:
		break;
	}

}
