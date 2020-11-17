#ifndef ALARM_INTERFACE_H_
#define ALARM_INTERFACE_H_

typedef enum
{
	ALARM_1
}Alarm_t;

typedef enum
{
	ALARM_OFF = 0,
	ALARM_ON  = 1
}Alarm_State_t;


Error_Status Alarm_xInit(Alarm_t Alarm, Alarm_State_t state);
Error_Status Alarm_xSetState(Alarm_t Alarm, Alarm_State_t state);
Alarm_State_t Alarm_xGetState(Alarm_t Alarm);

#endif /* ALARM_INTERFACE_H_ */
