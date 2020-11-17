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
#include "LCD_interface.h"
#include "Keypad_interface.h"

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

	LCD_xGotoPosition(LCD_FIRST_LINE,0);
	LCD_vSendString("Enter user name");
	for(Local_u8LoginTries = 0;Local_u8LoginTries < HOME_LOGIN_TRIES;Local_u8LoginTries++)
	{
		if(Local_u8LoginTries > 0)
		{
			Display_vPrint("Try again",LCD_FIRST_LINE);
		}
		Display_vRecieveString(&Name);

		if(Login_CheckUserName(&Name) == E_OK)
		{
			Local_EntryFlag	=	E_OK;
			Alarm_xSetState(ALARM_1,ALARM_OFF);
			break;
		}
		else
		{
			LCD_vClear();
			LCD_xGotoPosition(0,0);
			Display_vPrint("Wrong user",LCD_FIRST_LINE);
			LCD_xGotoPosition(0,1);
		}
	}

	LCD_vClear();
	if(Local_EntryFlag == E_OK)
	{
		LCD_vSendString("Enter pass");
		for(Local_u8LoginTries = 0;Local_u8LoginTries < HOME_LOGIN_TRIES;Local_u8LoginTries++)
		{
			if(Local_u8LoginTries > 0)
			{
				Display_vPrint("Try again",LCD_FIRST_LINE);
			}
			Display_vRecieveString(Pass);
			if(Login_CheckPass(Pass) == E_OK)
			{
				Local_xRightPwFlag	=	E_OK;
				break;
			}
			else
			{
				LCD_vClear();
				Display_vPrint("Wrong password",LCD_FIRST_LINE);
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
	LCD_vClear();
	float32 Local_f32CurrentTemp	=	0;
	uint8 u8TempBuf[TEMP_BUF_SIZE]	=	{0};
	/* Update temperature reading */
	TempS_vUpdate();

	/* Read the current temperature */
	Local_f32CurrentTemp	=	TempS_f32GetTemp();
	Util_String_vFloatToStr(Local_f32CurrentTemp,u8TempBuf,TEMP_MAX_FLOAT_NUM);
	LCD_xGotoPosition(0,0);
	LCD_vSendString("Temperature is");
	LCD_xGotoPosition(1,0);
	LCD_vSendString(u8TempBuf);
	HOME_DELAY_MS(1000);
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
	LCD_xGotoPosition(0,0);
	LCD_vSendString("Welcome, Choose option");
	HOME_DELAY_MS(700);
	LCD_xGotoPosition(0,0);
	LCD_vSendString("1- control door");
	LCD_xGotoPosition(1,0);
	LCD_vSendString("2- toggle light");
	LCD_xGotoPosition(2,0);
	LCD_vSendString("3- Get temp ");
	LCD_xGotoPosition(3,0);
	LCD_vSendString("0- Exit menu ");
	HOME_DELAY_MS(1000);
	LCD_vClear();
}

/* ***************************************************************************** */

Flag_Status Home_xOptionHandle(void)
{
	static HomeLighState_t Local_xLedState	=	HOME_LIGHT_OFF;
	static HomeDoorState_t Local_xDoorState	=	HOME_DOOR_CLOSED;
	Flag_Status Local_xFlag					=	E_OK;

	uint8 Local_xRecvData	=	E_NOK;

	LCD_vClear();
	Home_vWelcomMsg();

	Display_vRecvChar(&Local_xRecvData);


	Home_vUpdate();

	LCD_vClear();
	switch(Local_xRecvData)
	{
	case HOME_DOOR_OP:
		if(HOME_DOOR_CLOSED	==	Local_xDoorState)
		{
			LCD_vSendString("Opening door");
			Home_vOpenDoor();
		}
		else
		{
			LCD_vSendString("Closing door");
			Home_vCloseDoor();
		}
		Local_xDoorState = (HOME_DOOR_CLOSED == Local_xDoorState)?HOME_DOOR_OPENED:HOME_DOOR_CLOSED;
		break;

	case HOME_LED_OP:
		Local_xLedState = (HOME_LIGHT_OFF == Local_xLedState)?HOME_LIGHT_ON:HOME_LIGHT_OFF;
		Home_vSetLight(Local_xLedState);
		LCD_vSendString("Toggling light");
		break;

	case HOME_TEMP_OP:
		Home_vPrintTemp();
		break;
	case HOME_EXIT_MENU_OP:
		Local_xFlag = E_NOK;
		break;
	default:
		LCD_vSendString("Wrong choice");
		break;
	}
	Local_xRecvData = 0;
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
