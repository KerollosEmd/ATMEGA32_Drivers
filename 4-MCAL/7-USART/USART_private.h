/*
 * USART_private.h
 *
 *  Created on: Feb 7, 2022
 *      Author: KeroEmad
 */

#ifndef USART_PRIVATE_H_
#define USART_PRIVATE_H_

#define USART_BAUD_RATE(USART_BAUDRATE)		(((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

/*USART Registers*/
/*DATA REGISTER*/
#define USART_u8UDR                *((volatile u8*)0x2C)

/*Control and Status Registers*/
#define USART_u8UCSRA              *((volatile u8*)0x2B)
#define USART_u8UCSRB              *((volatile u8*)0x2A)
#define USART_u8UCSRC              *((volatile u8*)0x40)

/*Baud Rate Registers*/
#define USART_u8UBRRL              *((volatile u8*)0x29)
#define USART_u8UBRRH              *((volatile u8*)0x40)


/*UCSRA Bits define*/
#define USART_UCSRA_MPCM		0
#define USART_UCSRA_U2X			1
#define USART_UCSRA_PE			2
#define USART_UCSRA_DOR			3
#define USART_UCSRA_FE			4
#define USART_UCSRA_UDRE		5
#define USART_UCSRA_TXC			6
#define USART_UCSRA_RXC			7

/*UCSRB Bits define*/
#define USART_UCSRB_TXB8		0
#define USART_UCSRB_RXB8		1
#define USART_UCSRB_UCSZ2		2
#define USART_UCSRB_TXEN		3
#define USART_UCSRB_RXEN		4
#define USART_UCSRB_UDRIE		5
#define USART_UCSRB_TXCIE		6
#define USART_UCSRB_RXCIE		7

/*UCSRC Bits define*/
#define USART_UCSRC_UCPOL		0
#define USART_UCSRC_UCSZ0		1
#define USART_UCSRC_UCSZ1		2
#define USART_UCSRC_USBS		3
#define USART_UCSRC_UPM0		4
#define USART_UCSRC_UPM1		5
#define USART_UCSRC_UMSEL		6
#define USART_UCSRC_URSEL		7

#define USART_UBRRH_URSEL		7

#endif /* USART_PRIVATE_H_ */
