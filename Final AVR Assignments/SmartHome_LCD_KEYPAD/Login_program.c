#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Util_String_interface.h"

#include "Login_interface.h"
#include "Login_config.h"

static uint8 UserNames[LOGIN_N_USERS][LOGIN_USERS_NAME_LEN] ={"12345","13579","24680"};
static uint8 UsersPass[LOGIN_N_USERS][LOGIN_USERS_PASS_LEN]	={"12345","00000","55555"};

static uint8 u8CurrentIndex	=	0;

Flag_Status Login_CheckUserName(uint8 *String)
{
	Flag_Status Local_xFlag = E_NOK;
	uint8 Local_u8Index = 0;
	for(Local_u8Index = 0; Local_u8Index < LOGIN_N_USERS;Local_u8Index++)
	{
		if(Util_String_xComp(String,UserNames[Local_u8Index]) == 0)
		{
			u8CurrentIndex	= Local_u8Index;
			Local_xFlag = E_OK;
			break;
		}
	}

	return Local_xFlag;
}

Flag_Status Login_CheckPass(uint8 *String)
{
	Flag_Status Local_xFlag = E_NOK;

	if(Util_String_xComp(String,UsersPass[u8CurrentIndex]) ==0)
	{
		Local_xFlag = E_OK;
	}

	return Local_xFlag;
}
