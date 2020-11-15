#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"

#include "Alarm_interface.h"
#include "Alarm_config.h"

Error_Status Alarm_xInit(Alarm_t Alarm, Alarm_State_t state)
{
	/* Configure Alarm pins as output */
	switch (Alarm)
	{
	case ALARM_1:
		GPIO_vInitPortPin(ALARM_1_PORT_DR, ALARM_1_PIN, GPIO_OUT);
		break;

	default:
		/* No Thing */
		return E_NOK;
		break;
	}
	return E_OK;
}

void Alarm_vToggle(Alarm_t Alarm)
{
	/* Toggle Alarm */
	if (Alarm_xGetState(Alarm) == ALARM_ON)
	{
		Alarm_xSetState(Alarm, ALARM_OFF);
	} else
	{
		Alarm_xSetState(Alarm, ALARM_ON);
	}
}

Error_Status Alarm_xSetState(Alarm_t Alarm, Alarm_State_t state)
{
	/* Set led state */
	switch (Alarm)
	{
	case ALARM_1:
		GPIO_vWritePortPin(ALARM_1_PORT_CR, ALARM_1_PIN, state);
		break;
	default:
		/* No Thing */
		return E_NOK;
		break;
	}
	return E_OK;
}

Alarm_State_t Alarm_xGetState(Alarm_t Alarm)
{
	Alarm_State_t ret = ALARM_OFF;

	/* Set Alarm state */
	switch (Alarm)
	{
	case ALARM_1:
		ret = GPIO_xReadPortPin(ALARM_1_PORT_CR, ALARM_1_PIN);
		break;
	default:
		/* No Thing */
		break;
	}
	return ret;
}
