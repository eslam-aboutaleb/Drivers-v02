/* ******************************************************   */
/*  ErrorM_program.c									    */
/*  Version: 1.0											*/
/*  Author : Eslam Ehab Aboutaleb							*/
/* ******************************************************   */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrorM_config.h"
#include "ErrorM_interface.h"

/* ***************************************************************************** */

void ErrorM_vReport( uint16 u16ModuleId,uint8 u8InstanceId,uint8 u8ApiId,uint8 u8ErrorId)
{
#if ERROR_CHECK == E_OK

	while(1)
	{
		/* Halt the program */
		/* Print Error message */
	}

#endif
}
