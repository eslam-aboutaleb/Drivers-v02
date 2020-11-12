/* ******************************************************  */
/*  USART_program.c									    */
/*  Version: 1.0											*/
/*  Author : Eslam Ehab Aboutaleb							*/
/* ******************************************************  */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "USART_interface.h"
#include "USART_private.h"

Error_Status USART_xInit(USART_TypeDef USARTx,USART_ConfigType * configType_PTr)
{
	Error_Status Local_xErrorState;

	/* Clear URSSEL bit to write on UBRRH register */
	CLEAR_BIT(UCSRC,URSEL);

	/* Set baud rate */
	Local_xErrorState	=	USART_xSetBaudRate(USARTx,configType_PTr->Speed,configType_PTr->BaudRate);

	/*set URSEL bit to write on UCSRC register*/
	SET_BIT(UCSRC,URSEL);

	/* Set stop bits */
	Local_xErrorState	=	USART_xSetStopBits(USARTx,configType_PTr->StopBit);

	/* Set parity bit */
	Local_xErrorState	=	USART_xSetParityBit(USARTx,configType_PTr->Parity);

	/* Set data size */
	Local_xErrorState	=	USART_xSetDataSize(USARTx,configType_PTr->DataSize);

	/* Set USART Interrupt state */
	Local_xErrorState	=	USART_xSetInterrupt(USARTx,configType_PTr->Interrupt);

	/* Set Transmission state -> Enable USART */
	Local_xErrorState	=	USART_xSetTransState(USARTx,configType_PTr->TransState);

	return Local_xErrorState;
}



Error_Status USART_xSetStopBits(USART_TypeDef USARTx,USART_StopBit_t Copy_xStopBits)
{
	if(USART1	==	USARTx)
	{
		/*set URSEL bit to write on UCSRC register*/
		SET_BIT(UCSRC,URSEL);
		switch(Copy_xStopBits)
		{
		case USART_ONE_STOP_BIT:
			CLEAR_BIT(UCSRC,USBS);
			break;
		case USART_TWO_STOP_BITS:
			SET_BIT(UCSRC,USBS);
			break;
		default:
			/* Default is one stop bit */
			CLEAR_BIT(UCSRC,USBS);
			break;

		}
	}
	else
	{
		return E_NOK;
	}
	return E_OK;
}

Error_Status USART_xSetParityBit(USART_TypeDef USARTx,USART_Parity_t Copy_xParity)
{
	if(USART1	==	USARTx)
	{
		switch(Copy_xParity)
		{
		case USART_PARITY_OFF:
			UCSRC = (1<<URSEL)&~(1<<UPM0)&~(1<<UPM1);
			break;
		case USART_ODD_PARITY:
			UCSRC = (1<<URSEL)|(1<<UPM0);
			break;
		case USART_EVEN_PARITY:
			UCSRC = (1<<URSEL)|(1<<UPM0)|(1<<UPM1);
			break;
		default:
			UCSRC = (1<<URSEL)&~(1<<UPM0)&~(1<<UPM1);
			break;
		}
	}
	else
	{
		return E_NOK;
	}
	return E_OK;
}

Error_Status USART_xSetDataSize(USART_TypeDef USARTx,USART_DataSize_t Copy_xDataSize)
{
	if(USART1	==	USARTx)
	{
		/*set URSEL bit to write on UCSRC register*/
		SET_BIT(UCSRC,URSEL);

		switch(Copy_xDataSize)
		{
		case USART_FIVE_BITS:
			UCSRC = (1<<URSEL)&~(1<<UCSZ0)&~(1<<UCSZ1)&(~(1<<UCSZ2));
			break;
		case USART_SIX_BITS:
			UCSRC = (1<<URSEL)|(1<<UCSZ0);
			CLEAR_BIT(UCSRB,UCSZ2);
			break;
		case USART_SEVEN_BITS:
			UCSRC = (1<<URSEL)|(1<<UCSZ1);
			CLEAR_BIT(UCSRB,UCSZ2);
			break;
		case USART_EIGHT_BITS:
			UCSRC = (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
			CLEAR_BIT(UCSRB,UCSZ2);
			break;
		case USART_NINE_BITS:
			UCSRC = (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
			SET_BIT(UCSRB,UCSZ2);
			break;
		default:
			/* Default is 8 bit mode */
			UCSRC = (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
			CLEAR_BIT(UCSRB,UCSZ2);
			break;
		}
	}
	else
	{
		return E_NOK;
	}
	return E_OK;
}

Error_Status USART_xSetBaudRate(USART_TypeDef USARTx,USART_TransmissionSpeed_t Copy_xSpeed, uint16 Copy_u16BaudRate)
{
	uint16 BaudRate_equ=0;
	if(USART1	==	USARTx)
	{
		switch(Copy_xSpeed)
		{
		case USART_NORMAL_SPEED:
			BaudRate_equ=(F_CPU)/((Copy_u16BaudRate * 16UL)-1);
			UBRRL=BaudRate_equ;
			UBRRH=(uint8)(BaudRate_equ>>8);
			break;

		case USART_HIGH_SPEED:
			SET_BIT(UCSRA,U2X);
			BaudRate_equ=(F_CPU)/((Copy_u16BaudRate * 8UL)-1);
			UBRRL=BaudRate_equ;
			UBRRH=(uint8)(BaudRate_equ>>8);
			break;

		default:
			BaudRate_equ=(F_CPU)/((Copy_u16BaudRate * 16UL)-1);
			UBRRL=BaudRate_equ;
			UBRRH=(uint8)(BaudRate_equ>>8);
			break;
		}
	}
	else
	{
		return E_NOK;
	}
	return E_OK;

}

Error_Status USART_xSetInterrupt(USART_TypeDef USARTx,uint8 interrupt )
{
	if(USART1	==	USARTx)
	{
		switch(interrupt)
		{
		case USART_INTERRUPT_OFF:
			CLEAR_BIT(UCSRB,RXCIE);
			CLEAR_BIT(UCSRB,TXCIE);
			break;

		case USART_INTERRUPT_ON:
			SET_BIT(UCSRB,RXCIE);
			SET_BIT(UCSRB,TXCIE);
			break;

		case USART_INTERRUPT_RX_ON:
			SET_BIT(UCSRB,RXCIE);
			break;

		case USART_INTERRUPT_RX_OFF:
			CLEAR_BIT(UCSRB,RXCIE);
			break;

		case USART_INTERRUPT_TX_ON:
			SET_BIT(UCSRB,TXCIE);
			break;

		case  USART_INTERRUPT_TX_OFF:
			CLEAR_BIT(UCSRB,TXCIE);
			break;

		default:
			return E_NOK;
			break;

		}
	}
	else
	{
		return E_NOK;
	}
	return E_OK;
}

Error_Status USART_xSetTransState(USART_TypeDef USARTx,USART_TransmissionState_T Copy_xstate)
{
	if(USART1	==	USARTx)
	{
		switch(Copy_xstate)
		{
		case USART_TRANSMITER:
			SET_BIT(UCSRB,TXEN);
			CLEAR_BIT(UCSRB,RXEN);
			break;
		case USART_RECIEVER:
			SET_BIT(UCSRB,RXEN);
			CLEAR_BIT(UCSRB,TXEN);
			break;
		case USART_TRANSMITER_RECIEVER:
			SET_BIT(UCSRB,RXEN);
			SET_BIT(UCSRB,TXEN);
			break;
		default:
			SET_BIT(UCSRB,RXEN);
			SET_BIT(UCSRB,TXEN);
			break;
		}
	}
	else
	{
		return E_OK;
	}
	return E_OK;
}



Error_Status USART_xSendByte(USART_TypeDef USARTx,uint8 data)
{
	if(USART1	==	USARTx)
	{
		/*wait until Date buffer is empty and ready to Write*/
		while((UCSRA&(1<<UDRE))==0);
		UDR=data;
	}
	else
	{
		return E_NOK;
	}
	return E_OK;
}

Error_Status USART_xSendString(USART_TypeDef USARTx,uint8 * string)
{
	if(USART_IS_VALID_CH(USARTx)	==	E_OK)
	{
		while(*string!='\0')
		{
			USART_xSendByte(USARTx,*string);
			string++;
		}
		USART_xSendByte(USARTx,'\0');
	}
	else
	{
		return E_NOK;
	}
	return E_OK;
}

Error_Status USART_xRecieveByte(USART_TypeDef USARTx,uint8 *RecvData)
{
	if(USART1	==	USARTx)
	{
		/*Wait until there is unread data in Date Buffer*/
		while (GET_BIT(UCSRA , RXC)	==	0);
		*RecvData	=	 UDR;
	}
	else
	{
		*RecvData	=	E_NOK;
		return E_NOK;
	}
	return E_OK;
}



Error_Status USART_xRecieveString(USART_TypeDef USARTx,uint8 * string)
{
	uint8 Local_u8Data	=	0;
	if(USART_IS_VALID_CH(USARTx)	==	E_OK)
	{
		/*temporary variable as a buffer*/
		uint8 data;
		do
		{
			USART_xRecieveByte(USARTx,&Local_u8Data);
			/*assign data to the string*/
			*string=data;
			/*move to next address*/
			string++;
		} while (data!='\0');

	}
	else
	{
		return E_NOK;
	}

	return E_OK;
}
