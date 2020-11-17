#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "util/delay.h"

#include "Display_interface.h"
#include "Login_interface.h"
#include "TempS_interface.h"
#include "Util_String_interface.h"
#include "PWM_interface.h"
#include "Led_interface.h"
#include "Alarm_interface.h"
#include "LDR_interface.h"

#include "Home_interface.h"
#include "Home_config.h"

/* ***************************************************************************** */
void Home_vInit(void)
{
	LED_xInit(HOME_LIGHT_LED,HOME_LIGHT_OFF);
	LED_xInit(HOME_LIGHT_LDR_SENSOR_LED,HOME_LIGHT_OFF);
}

/* ***************************************************************************** */

Flag_Status Home_xEnter(void)
{
	uint8 Local_u8LoginTries 		=	0;
	uint8 Name[NAME_LENGTH]			=	{[0 ... 49]='\0'};
	uint8 Pass[PASS_LENGTH]			=	{0};
	Flag_Status Local_EntryFlag		=	E_NOK;
	Flag_Status Local_xRightPwFlag	=	E_NOK;

	Display_vPrint("Enter user name \r\n");
	for(Local_u8LoginTries = 0;Local_u8LoginTries < HOME_LOGIN_TRIES;Local_u8LoginTries++)
	{
		Display_vRecieveString(Name);
		if(Login_CheckUserName(Name) == E_OK)
		{
			Local_EntryFlag	=	E_OK;
			Alarm_xSetState(ALARM_1,ALARM_OFF);
			break;
		}
		else
		{
			Display_vPrint("Wrong user name\r\n");
			Display_vPrint("Try again\r\n");
		}
	}

	if(Local_EntryFlag == E_OK)
	{
		Display_vPrint("Enter user password\r\n");

		for(Local_u8LoginTries = 0;Local_u8LoginTries < HOME_LOGIN_TRIES;Local_u8LoginTries++)
		{
			Display_vRecieveString(Pass);
			if(Login_CheckPass(Pass) == E_OK)
			{
				Local_xRightPwFlag	=	E_OK;
				break;
			}
			else
			{
				Display_vPrint("Wrong password\r\n");
				Display_vPrint("Try again\r\n");
			}
		}
	}
	else
	{
		Alarm_xSetState(ALARM_1,ALARM_ON);
	}
	if(Local_xRightPwFlag == E_NOK)
	{
		Alarm_xSetState(ALARM_1,ALARM_ON);
	}

	return Local_xRightPwFlag;
}

/* ***************************************************************************** */

void Home_vPrintTemp(void)
{
	float32 Local_f32CurrentTemp	=	0;
	uint8 u8TempBuf[TEMP_BUF_SIZE]	=	{0};
	/* Update temperature reading */
	TempS_vUpdate();

	/* Read the current temperature */
	Local_f32CurrentTemp	=	TempS_f32GetTemp();
	Util_String_vFloatToStr(Local_f32CurrentTemp,u8TempBuf,TEMP_MAX_FLOAT_NUM);
	Display_vPrint("Temperature is %s \r\n",u8TempBuf);
}

/* ***************************************************************************** */

void Home_vOpenDoor(void)
{
	uint16 Local_u16Index = 0;
	for(Local_u16Index=0;Local_u16Index<HOME_DOOR_SERVO_MAX_MS;Local_u16Index+=100)
	{
		PWM_xSet_TONus(Local_u16Index,HOME_DOOR_SERVO_CH);
		_delay_ms(50);
	}
}

/* ***************************************************************************** */

void Home_vCloseDoor(void)
{
	uint16 Local_u16Index = 0;
	for(Local_u16Index=HOME_DOOR_SERVO_MAX_MS;Local_u16Index>=1;Local_u16Index-=100)
	{
		PWM_xSet_TONus(Local_u16Index,HOME_DOOR_SERVO_CH);
		_delay_ms(50);
	}
}

/* ***************************************************************************** */

void Home_vSetLight(HomeLighState_t Copy_xLightState)
{
	LED_xSetState(HOME_LIGHT_LED,Copy_xLightState);
}

/* ***************************************************************************** */

static void Home_vWelcomMsg(void)
{
	Display_vPrint("Welcome, Choose option \r\n");
	Display_vPrint("1- Open & Close door \r\n");
	Display_vPrint("2- Open & Close light \r\n");
	Display_vPrint("3- Get the current temp \r\n");
	Display_vPrint("0- Exit menu \r\n");
}

/* ***************************************************************************** */

Flag_Status Home_xOptionHandle(void)
{
	static HomeLighState_t Local_xLedState	=	HOME_LIGHT_OFF;
	static HomeDoorState_t Local_xDoorState	=	HOME_DOOR_CLOSED;
	Flag_Status Local_xFlag					=	E_OK;

	uint8 Local_xRecvData	=	0;

	Home_vWelcomMsg();

	Display_vRecvChar(&Local_xRecvData);

	Home_vUpdate();

	switch(Local_xRecvData)
	{
	case HOME_DOOR_OP:
		if(HOME_DOOR_CLOSED	==	Local_xDoorState)
		{
			Display_vPrint("Opening door \r\n");
			Home_vOpenDoor();
		}
		else
		{
			Display_vPrint("Closing door \r\n");
			Home_vCloseDoor();
		}
		Local_xDoorState = (HOME_DOOR_CLOSED == Local_xDoorState)?HOME_DOOR_OPENED:HOME_DOOR_CLOSED;
		break;

	case HOME_LED_OP:
		Local_xLedState = (HOME_LIGHT_OFF == Local_xLedState)?HOME_LIGHT_ON:HOME_LIGHT_OFF;
		Home_vSetLight(Local_xLedState);
		Display_vPrint("Toggling light \r\n");
		break;

	case HOME_TEMP_OP:
		Home_vPrintTemp();
		break;
	case HOME_EXIT_MENU_OP:
		Local_xFlag = E_NOK;
		break;
	default:
		Display_vPrint("Wrong choice \r\n");
		break;
	}
	return Local_xFlag;
}

/* ***************************************************************************** */

void Home_vUpdate(void)
{
	LDR_vUpdate();

	if(LDR_u16GetVal() < HOME_LIGHT_MIN_INTENSITY)
	{
		LED_xSetState(HOME_LIGHT_LDR_SENSOR_LED,LED_ON);
	}
	else
	{
		LED_xSetState(HOME_LIGHT_LDR_SENSOR_LED,LED_OFF);
	}
}
