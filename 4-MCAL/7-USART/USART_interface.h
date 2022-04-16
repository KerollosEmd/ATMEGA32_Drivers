/*
 * USART_interface.h
 *
 *  Created on: Feb 7, 2022
 *      Author: KeroEmad
 */

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

#include "STD_Types.h"
#include "BIT_MATH.h"


/*Initialization of USART*/
void	 USART_voidInit(u32 Copy_u32BaudRate);

/*Some feature APIs*/
void	 USART_voidBaudRate(u32 Copy_u32BaudRate);
void 	 USART_voidModeSel(u8 Copy_u8UMSEL);
void     USART_voidParityMode(u8 Copy_u8UPM_1_0);
void     USART_voidStopBitSel(u8 Copy_u8USBS);
void     USART_voidCharSize(u8 Copy_u8UCSZ_2_1_0);
void     USART_voidClockPol(u8 Copy_u8UCPOL);
void     USART_voidMultiProcessorMode(u8 Copy_u8MPCM);
void     USART_voidInterruptEn(void);

/*Whole register assignment*/
u8		 _USART_u8UCSRC(u8 Copy_u8UMSEL, u8 Copy_u8UPM, u8 Copy_u8USBS, u8 Copy_u8UCSZ, u8 Copy_u8UCPOL);
u8		 _USART_u8UCSRB(u8 Copy_u8RXCIE, u8 Copy_u8TXCIE, u8 Copy_u8UDRIE, u8 Copy_u8RXEN, u8 Copy_u8TXEN);
u8		 _USART_u8UCSRA(u8 Copy_u8U2X, u8 Copy_u8MPCM);

/*Main USART APIs*/
u8	 	USART_u8SendChar(u8 Copy_u8TxChar);
u8	 	USART_u8SendString(u8 *Copy_ptru8ArTxString);
u8	 	USART_u8ReceiveChar(u8 *Copy_ptru8RxChar);
u8		USART_u8ReceiveString(u8 *Copy_ptru8ArRxString);

/*
 * CALLBACK FUNCTIONs
 */
u8		USART_u8RXCSetCallBack(void(* Copy_PtrToFun)(u8));
u8		USART_u8TXCSetCallBack(void(* Copy_PtrToFun)(u8));
u8		USART_u8UDRESetCallBack(void(* Copy_PtrToFun)(u8*));
#endif /* USART_INTERFACE_H_ */
