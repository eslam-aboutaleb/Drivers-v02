/* ***************************************************************************** */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 5-10-2020                                                               */
/* ***************************************************************************** */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "SSD_config.h"
#include "SSD_interface.h"

/* ***************************************************************************** */
/*Functions definitions*/
/* ***************************************************************************** */

void SSD_vInit(tSSD Copy_xSSD,tSSD_Type Copy_xSSD_type)
{
#if SSD_MULTIPLEXING_STATE== SSD_MULTIPLEXING_ON

	switch(Copy_xSSD)
	{
	case SSD_One:
		GPIO_vInitPortPin(SSD_CONTROL_ONE_PORT_CR,SSD_CONTROL_ONE_PORT_PIN,GPIO_OUT);
		break;
	case SSD_Two:
		GPIO_vInitPortPin(SSD_CONTROL_TWO_PORT_CR,SSD_CONTROL_TWO_PORT_PIN,GPIO_OUT);
		break;
	default:
		break;

	}
#endif

	/* Initialize SSD data pins */
	switch(Copy_xSSD)
	{
	case SSD_One:
		GPIO_vInitPortPin(SSD_DATA_PIN_1_PORT_CR,SSD_PIN_1,GPIO_OUT);
		GPIO_vInitPortPin(SSD_DATA_PIN_2_PORT_CR,SSD_PIN_2,GPIO_OUT);
		GPIO_vInitPortPin(SSD_DATA_PIN_3_PORT_CR,SSD_PIN_3,GPIO_OUT);
		GPIO_vInitPortPin(SSD_DATA_PIN_4_PORT_CR,SSD_PIN_4,GPIO_OUT);
		GPIO_vInitPortPin(SSD_DATA_PIN_5_PORT_CR,SSD_PIN_5,GPIO_OUT);
		GPIO_vInitPortPin(SSD_DATA_PIN_6_PORT_CR,SSD_PIN_6,GPIO_OUT);
		GPIO_vInitPortPin(SSD_DATA_PIN_7_PORT_CR,SSD_PIN_7,GPIO_OUT);
		GPIO_vInitPortPin(SSD_DATA_PIN_8_PORT_CR,SSD_PIN_8,GPIO_OUT);
		break;

	case SSD_Two:
		GPIO_vInitPortPin(SSD2_DATA_PIN_1_PORT_CR,SSD2_PIN_1,GPIO_OUT);
		GPIO_vInitPortPin(SSD2_DATA_PIN_2_PORT_CR,SSD2_PIN_2,GPIO_OUT);
		GPIO_vInitPortPin(SSD2_DATA_PIN_3_PORT_CR,SSD2_PIN_3,GPIO_OUT);
		GPIO_vInitPortPin(SSD2_DATA_PIN_4_PORT_CR,SSD2_PIN_4,GPIO_OUT);
		GPIO_vInitPortPin(SSD2_DATA_PIN_5_PORT_CR,SSD2_PIN_5,GPIO_OUT);
		GPIO_vInitPortPin(SSD2_DATA_PIN_6_PORT_CR,SSD2_PIN_6,GPIO_OUT);
		GPIO_vInitPortPin(SSD2_DATA_PIN_7_PORT_CR,SSD2_PIN_7,GPIO_OUT);
		GPIO_vInitPortPin(SSD2_DATA_PIN_8_PORT_CR,SSD2_PIN_8,GPIO_OUT);
		break;

	default:
		break;
	}


	SSD_vOut(Copy_xSSD,Copy_xSSD_type, SSD_NULL);

}


/* ***************************************************************************** */


void SSD_vOut(tSSD Copy_xSSD,tSSD_Type Copy_xSSD_type, tSSD_Symbol Copy_SSD_xSymbol)
{
	/* Output ssd_symbol on selected ssd */
	switch(Copy_xSSD)
	{
	case SSD_One:

		if(Copy_xSSD_type == SSD_Cathode)
		{
			GPIO_vWritePortPin(SSD_DATA_PIN_1_PORT_DR,SSD_PIN_1,GET_BIT(SSD_Data[Copy_SSD_xSymbol],0));
			GPIO_vWritePortPin(SSD_DATA_PIN_2_PORT_DR,SSD_PIN_2,GET_BIT(SSD_Data[Copy_SSD_xSymbol],1));
			GPIO_vWritePortPin(SSD_DATA_PIN_3_PORT_DR,SSD_PIN_3,GET_BIT(SSD_Data[Copy_SSD_xSymbol],2));
			GPIO_vWritePortPin(SSD_DATA_PIN_4_PORT_DR,SSD_PIN_4,GET_BIT(SSD_Data[Copy_SSD_xSymbol],3));
			GPIO_vWritePortPin(SSD_DATA_PIN_5_PORT_DR,SSD_PIN_5,GET_BIT(SSD_Data[Copy_SSD_xSymbol],4));
			GPIO_vWritePortPin(SSD_DATA_PIN_6_PORT_DR,SSD_PIN_6,GET_BIT(SSD_Data[Copy_SSD_xSymbol],5));
			GPIO_vWritePortPin(SSD_DATA_PIN_7_PORT_DR,SSD_PIN_7,GET_BIT(SSD_Data[Copy_SSD_xSymbol],6));
			GPIO_vWritePortPin(SSD_DATA_PIN_8_PORT_DR,SSD_PIN_8,GET_BIT(SSD_Data[Copy_SSD_xSymbol],7));
		}
		else
		{
			GPIO_vWritePortPin(SSD_DATA_PIN_1_PORT_DR,SSD_PIN_1,(GET_BIT(SSD_Data[Copy_SSD_xSymbol],0)==1?0:1));
			GPIO_vWritePortPin(SSD_DATA_PIN_2_PORT_DR,SSD_PIN_2,(GET_BIT(SSD_Data[Copy_SSD_xSymbol],1)==1?0:1));
			GPIO_vWritePortPin(SSD_DATA_PIN_3_PORT_DR,SSD_PIN_3,(GET_BIT(SSD_Data[Copy_SSD_xSymbol],2)==1?0:1));
			GPIO_vWritePortPin(SSD_DATA_PIN_4_PORT_DR,SSD_PIN_4,(GET_BIT(SSD_Data[Copy_SSD_xSymbol],3)==1?0:1));
			GPIO_vWritePortPin(SSD_DATA_PIN_5_PORT_DR,SSD_PIN_5,(GET_BIT(SSD_Data[Copy_SSD_xSymbol],4)==1?0:1));
			GPIO_vWritePortPin(SSD_DATA_PIN_6_PORT_DR,SSD_PIN_6,(GET_BIT(SSD_Data[Copy_SSD_xSymbol],5)==1?0:1));
			GPIO_vWritePortPin(SSD_DATA_PIN_7_PORT_DR,SSD_PIN_7,(GET_BIT(SSD_Data[Copy_SSD_xSymbol],6)==1?0:1));
			GPIO_vWritePortPin(SSD_DATA_PIN_8_PORT_DR,SSD_PIN_8,(GET_BIT(SSD_Data[Copy_SSD_xSymbol],7)==1?0:1));
		}
		break;
	case SSD_Two:
		if(Copy_xSSD_type == SSD_Cathode)
		{
			GPIO_vWritePortPin(SSD2_DATA_PIN_1_PORT_DR,SSD2_PIN_1,GET_BIT(SSD_Data[Copy_SSD_xSymbol],0));
			GPIO_vWritePortPin(SSD2_DATA_PIN_2_PORT_DR,SSD2_PIN_2,GET_BIT(SSD_Data[Copy_SSD_xSymbol],1));
			GPIO_vWritePortPin(SSD2_DATA_PIN_3_PORT_DR,SSD2_PIN_3,GET_BIT(SSD_Data[Copy_SSD_xSymbol],2));
			GPIO_vWritePortPin(SSD2_DATA_PIN_4_PORT_DR,SSD2_PIN_4,GET_BIT(SSD_Data[Copy_SSD_xSymbol],3));
			GPIO_vWritePortPin(SSD2_DATA_PIN_5_PORT_DR,SSD2_PIN_5,GET_BIT(SSD_Data[Copy_SSD_xSymbol],4));
			GPIO_vWritePortPin(SSD2_DATA_PIN_6_PORT_DR,SSD2_PIN_6,GET_BIT(SSD_Data[Copy_SSD_xSymbol],5));
			GPIO_vWritePortPin(SSD2_DATA_PIN_7_PORT_DR,SSD2_PIN_7,GET_BIT(SSD_Data[Copy_SSD_xSymbol],6));
			GPIO_vWritePortPin(SSD2_DATA_PIN_8_PORT_DR,SSD2_PIN_8,GET_BIT(SSD_Data[Copy_SSD_xSymbol],7));
		}
		else
		{
			GPIO_vWritePortPin(SSD2_DATA_PIN_1_PORT_DR,SSD2_PIN_1,(GET_BIT(SSD_Data[Copy_SSD_xSymbol],0))==1?0:1);
			GPIO_vWritePortPin(SSD2_DATA_PIN_2_PORT_DR,SSD2_PIN_2,(GET_BIT(SSD_Data[Copy_SSD_xSymbol],1))==1?0:1);
			GPIO_vWritePortPin(SSD2_DATA_PIN_3_PORT_DR,SSD2_PIN_3,(GET_BIT(SSD_Data[Copy_SSD_xSymbol],2))==1?0:1);
			GPIO_vWritePortPin(SSD2_DATA_PIN_4_PORT_DR,SSD2_PIN_4,(GET_BIT(SSD_Data[Copy_SSD_xSymbol],3))==1?0:1);
			GPIO_vWritePortPin(SSD2_DATA_PIN_5_PORT_DR,SSD2_PIN_5,(GET_BIT(SSD_Data[Copy_SSD_xSymbol],4))==1?0:1);
			GPIO_vWritePortPin(SSD2_DATA_PIN_6_PORT_DR,SSD2_PIN_6,(GET_BIT(SSD_Data[Copy_SSD_xSymbol],5))==1?0:1);
			GPIO_vWritePortPin(SSD2_DATA_PIN_7_PORT_DR,SSD2_PIN_7,(GET_BIT(SSD_Data[Copy_SSD_xSymbol],6))==1?0:1);
			GPIO_vWritePortPin(SSD2_DATA_PIN_8_PORT_DR,SSD2_PIN_8,(GET_BIT(SSD_Data[Copy_SSD_xSymbol],7))==1?0:1);
		}
		break;
	default:
		break;
	}
}


/* ***************************************************************************** */

tSSD_State SSD_xGetState(tSSD Copy_xSSD)
{
/*If the user uses multiplexing these functions will be defined*/
#if(SSD_MULTIPLEXING_STATE == SSD_MULTIPLEXING_ON)

	tSSD_State ret = SSD_OFF;
	switch (Copy_xSSD)
	{
	case SSD_One:
		ret = GPIO_xReadPortPin(SSD_CONTROL_ONE_PORT_DR, SSD_CONTROL_ONE_PORT_PIN);
		break;
	case SSD_Two:
		ret = GPIO_xReadPortPin(SSD_CONTROL_TWO_PORT_DR, SSD_CONTROL_TWO_PORT_PIN);
		break;
	default:
		break;
	}

	return ret;
#endif
}




void SSD_vSetState(tSSD Copy_xSSD,tSSD_Type Copy_SSD_xtype ,tSSD_State Copy_SSD_xState){
#if(SSD_MULTIPLEXING_STATE == SSD_MULTIPLEXING_ON)
	switch (Copy_xSSD)
	{
	case SSD_One:
		if(Copy_SSD_xtype==SSD_Cathode)
		{
			GPIO_vWritePortPin(SSD_CONTROL_ONE_PORT_DR, SSD_CONTROL_ONE_PORT_PIN, 0);
		}
		else
		{
			GPIO_vWritePortPin(SSD_CONTROL_ONE_PORT_DR, SSD_CONTROL_ONE_PORT_PIN, 1);
		}
		break;
	case SSD_Two:
		if(Copy_SSD_xtype==SSD_Cathode)
		{
			GPIO_vWritePortPin(SSD_CONTROL_TWO_PORT_DR, SSD_CONTROL_TWO_PORT_PIN, 0);
		}
		else
		{
			GPIO_vWritePortPin(SSD_CONTROL_TWO_PORT_DR, SSD_CONTROL_TWO_PORT_PIN, 1);
		}
		break;

		/* Should not be here */
	default:
		break;
	}
#endif
}

/* ***************************************************************************** */

void SSD_vUpdate(void)
{
	static Flag_Status x_100Flag = E_NOK;
	static uint8 u8TensIndex = SSD_0;
	static uint8 u8OnesIndex = SSD_0;

	SSD_vOut(SSD_Two,SSD_Cathode,u8TensIndex);

	if(E_OK == x_100Flag)
	{
		/* The SSDs print 99 */
		return;
	}

	SSD_vOut(SSD_One,SSD_Cathode,u8OnesIndex);
	u8OnesIndex++;

	/* If ones SSD is more than 9 increase one in tens index */
	if(u8OnesIndex > SSD_9)
	{
		u8TensIndex++;
		u8OnesIndex = SSD_0;
	}

	/* Check if tens SSD reached 9 =>SSDs print 99*/
	if(u8TensIndex >= SSD_9)
	{
		u8TensIndex = SSD_9;
		x_100Flag = E_OK;
	}
}

/* ***************************************************************************** */
void SSD_vUpdateMul(void)
{
#if(SSD_MULTIPLEXING_STATE == SSD_MULTIPLEXING_ON)

	static uint8 flag = 0;
	if (flag ==0)
	{
		GPIO_vWritePortPin(GPIOB,GPIO_PIN_7,GPIO_LOW);
		SSD_vOut(SSD_One,SSD_Cathode,3);
		flag =1;
	}
	else
	{
		GPIO_vWritePortPin(GPIOB,GPIO_PIN_7,GPIO_HIGH);
		SSD_vOut(SSD_Two,SSD_Anode,5);
		flag = 0;
	}
	SSD_Delay_MS(20);
#endif
}
