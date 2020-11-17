 /* ******************************************************  */
 /*  USART_program.h									    */
 /*  Version: 1.0											*/
 /*  Author : Eslam Ehab Aboutaleb							*/
 /* ******************************************************  */

#ifndef USART_PRIVATE_H_
#define USART_PRIVATE_H_

#define USART_IS_VALID_CH(Channel)							(Channel == USART1)


#define UBRRL   (*(volatile uint8*)0x0029)

#define UCSRB   (*(volatile uint8*)0x002A)
#define TXB8    0
#define RXB8    1
#define UCSZ2   2
#define TXEN    3
#define RXEN    4
#define UDRIE   5
#define TXCIE   6
#define RXCIE   7

#define UCSRA   (*(volatile uint8*)0x002B)
#define MPCM    0
#define U2X     1
#define PE      2
#define DOR     3
#define FE      4
#define UDRE    5
#define TXC     6
#define RXC     7

#define UDR     (*(volatile uint8*)0x002C)


#define UCSRC   (*(volatile uint8*)0x0040)
#define UCPOL   0
#define UCSZ0   1
#define UCSZ1   2
#define USBS    3
#define UPM0    4
#define UPM1    5
#define UMSEL   6
#define URSEL   7

#define UBRRH   (*(volatile uint8*)0x0040)
#define URSEL   7

#endif /* USART_PRIVATE_H_ */
