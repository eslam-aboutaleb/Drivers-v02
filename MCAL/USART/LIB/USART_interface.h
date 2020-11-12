 /* ******************************************************  */
 /*  USART_program.h									    */
 /*  Version: 1.0											*/
 /*  Author : Eslam Ehab Aboutaleb							*/
 /* ******************************************************  */

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

#ifndef F_CPU
#define F_CPU 8000000
#endif

typedef unsigned char									USART_TypeDef;

#define USART1											0


typedef enum
{
	USART_INTERRUPT_OFF,
	USART_INTERRUPT_ON,
	USART_INTERRUPT_RX_ON,
	USART_INTERRUPT_RX_OFF,
	USART_INTERRUPT_TX_ON,
	USART_INTERRUPT_TX_OFF
}USART_IntState_t;

typedef enum
{
	USART_FIVE_BITS,
	USART_SIX_BITS,
	USART_SEVEN_BITS,
	USART_EIGHT_BITS,
	USART_NINE_BITS
}USART_DataSize_t;

typedef enum
{
	USART_PARITY_OFF,
	USART_ODD_PARITY,
	USART_EVEN_PARITY
}USART_Parity_t;

typedef enum
{
	USART_ONE_STOP_BIT,
	USART_TWO_STOP_BITS
}USART_StopBit_t;

typedef enum
{
	USART_NORMAL_SPEED,
	USART_HIGH_SPEED
}USART_TransmissionSpeed_t;

typedef enum
{
	USART_TRANSMITER,
	USART_RECIEVER,
	USART_TRANSMITER_RECIEVER
}USART_TransmissionState_T;

typedef enum
{
	USART_DISABLE,
	USART_ENABLE
}USART_State_t;

typedef struct
{
	uint16 BaudRate;
	USART_IntState_t Interrupt;
	USART_DataSize_t DataSize;
	USART_Parity_t Parity;
	USART_StopBit_t StopBit;
	USART_State_t State;
	USART_TransmissionSpeed_t Speed;
	USART_TransmissionState_T	TransState;
}USART_ConfigType;

Error_Status USART_xInit(USART_TypeDef USARTx,USART_ConfigType * configType_PTr);
Error_Status USART_xSetState(USART_TypeDef USARTx,USART_State_t Copy_xState);
Error_Status USART_xSetStopBits(USART_TypeDef USARTx,USART_StopBit_t Copy_xStopBits);
Error_Status USART_xSetParityBit(USART_TypeDef USARTx,USART_Parity_t Copy_xParity);
Error_Status USART_xSetDataSize(USART_TypeDef USARTx,USART_DataSize_t Copy_xDataSize);
Error_Status USART_xSetBaudRate(USART_TypeDef USARTx,USART_TransmissionSpeed_t Copy_xSpeed, uint16 Copy_u16BaudRate);
Error_Status USART_xSetInterrupt(USART_TypeDef USARTx,uint8 interrupt );
Error_Status USART_xSetTransState(USART_TypeDef USARTx,uint8 Copy_xstate);
Error_Status USART_xSendByte(USART_TypeDef USARTx,uint8 data);
Error_Status USART_xSendString(USART_TypeDef USARTx,uint8 * string);
Error_Status USART_xRecieveByte(USART_TypeDef USARTx,uint8 *RecvData);
Error_Status USART_xRecieveString(USART_TypeDef USARTx,uint8 * string);

#endif /* USART_INTERFACE_H_ */
