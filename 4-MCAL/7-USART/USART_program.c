/*
 * USART_program.c
 *
 *  Created on: Feb 7, 2022
 *      Author: KeroEmad
 */

/*Library*/
#include "STD_Types.h"
#include "BIT_MATH.h"

/*MCAL header*/
#include "USART_config.h"
#include "USART_interface.h"
#include "USART_private.h"

/*
 * Static Global Variables and Pointers
 */
static void(*USART_PtrToFunRXC)(u8)=NULL;
static void(*USART_PtrToFunTXC)(u8)=NULL;
static void(*USART_PtrToFunUDRE)(u8*)=NULL;
/*Initialization of USART*/
/*Initialize USART by Asynchronous UART
 *Select Baud Rate by putting the suitable value as input argument i.e.:9600
 *8-Bit Character Size */
void USART_voidInit(u32 Copy_u32BaudRate){

	/*Enable TxD and RxD*/
	USART_u8UCSRB |=(1<<USART_UCSRB_RXEN)|(1<<USART_UCSRB_TXEN);

	/*Select 8bit Character Size*/
	USART_u8UCSRC |= (1<<USART_UCSRC_URSEL)|(1<<USART_UCSRC_UCSZ1)|(1<<USART_UCSRC_UCSZ0);

	/*Baud Rate Select i.e.:9600*/
	u32 Local_u32BaudPrescaler=USART_BAUD_RATE(Copy_u32BaudRate);

	USART_u8UBRRL=(u8)Local_u32BaudPrescaler;							//update Lower  UBRRL
	USART_u8UBRRH=(0<<USART_UCSRC_URSEL)|(Local_u32BaudPrescaler>>8);	//update Higher UBRRH

}

/*Some feature APIs*/
/*
 * Ongoing transmissions by the transmitter and receiver will be cor-
rupted if the baud rate is changed. Writing UBRRL will trigger an immediate update of
the baud rate prescaler.
 */
void	 USART_voidBaudRate(u32 Copy_u32BaudRate){
	u32 Local_u32BaudPrescaler=USART_BAUD_RATE(Copy_u32BaudRate);
//	while(!(GET_BIT(USART_u8UCSRA,USART_UCSRA_TXC)));					//wait tell TxC Complete
	USART_u8UBRRL=(u8)Local_u32BaudPrescaler;							//update Lower  UBRRL
	USART_u8UBRRH=(0<<USART_UCSRC_URSEL)|(Local_u32BaudPrescaler>>8);	//update Higher UBRRH

}
/*******************
 * Select mode of USART
 * 1----> Synchronous
 * 0----> Asynchronous
 * *********************/
void 	 USART_voidModeSel(u8 Copy_u8UMSEL){
	USART_u8UCSRC = (1<<USART_UCSRC_URSEL)|(Copy_u8UMSEL<<USART_UCSRC_UMSEL);
}

/*********************
 * Parity MOde Select
 * 00---->Disable Parity bits
 * 10---->Even Parity Mode
 * 11---->Odd Parity Mode
 * *******************/
void     USART_voidParityMode(u8 Copy_u8UPM_1_0);

/*
 * Stop Bit Select
 * 0---->1bit (default)
 * 1---->2bit
 */
void     USART_voidStopBitSel(u8 Copy_u8USBS);

/*
 * Character Size
 * it is separated into 3 bits in 2 registers
 * UCSZ2 in UCSRB and UCSZ1:0 in UCSRB
 * 000---->5-bits Char
 * 001---->6-bits Char
 * 010---->7-bits Char
 * 011---->8-bits Char
 * 111---->9-bits Char
 */
void     USART_voidCharSize(u8 Copy_u8UCSZ_2_1_0);

/*
 * Clock Polarity
 * 0---->Rising TxD & Falling RxD
 * 1---->Falling TxD & Rising RxD
 */
void     USART_voidClockPol(u8 Copy_u8UCPOL);

/*
 * Multi-Processor Communication Mode
 * 0---->Disable
 * 1---->Activate
 */
void     USART_voidMultiProcessorMode(u8 Copy_u8MPCM);

/*
 * Interrupt Enable of
 * ---->Rx Complete Interrupt
 * ---->Tx Complete Interrupt
 * ---->Data Register Empty Interrupt
 */
void     USART_voidInterruptEn(void){
	USART_u8UCSRB|=(1<<USART_UCSRB_RXCIE);//|(1<<USART_UCSRB_TXCIE);//|(1<<USART_UCSRB_UDRIE);
}

/*Whole register assignment*/
u8	 _USART_u8UCSRC(u8 Copy_u8UMSEL, u8 Copy_u8UPM, u8 Copy_u8USBS, u8 Copy_u8UCSZ, u8 Copy_u8UCPOL);
u8	 _USART_u8UCSRB(u8 Copy_u8RXCIE, u8 Copy_u8TXCIE, u8 Copy_u8UDRIE, u8 Copy_u8RXEN, u8 Copy_u8TXEN);
u8	 _USART_u8UCSRA(u8 Copy_u8U2X, u8 Copy_u8MPCM);

/*Main USART APIs*/
u8	 USART_u8SendChar(u8 Copy_u8TxChar){
	/*Wait until UDRE Data Register Empty Flag is set to 1*/
	while(!(GET_BIT(USART_u8UCSRA,USART_UCSRA_UDRE)));
	/*Update UDR TX Buffer with Char.*/
	USART_u8UDR=Copy_u8TxChar;
	return 0;
}

u8	 USART_u8SendString(u8 *Copy_ptru8ArTxString){
	u8 Local_u8Index;

	for(Local_u8Index=0; Copy_ptru8ArTxString[Local_u8Index]!='\0'; Local_u8Index++){
		USART_u8SendChar(Copy_ptru8ArTxString[Local_u8Index]);
	}

	return 0;
}
u8	 USART_u8ReceiveChar(u8 *Copy_ptru8RxChar){
	/*wait until data is received*/
	while(!(GET_BIT(USART_u8UCSRA,USART_UCSRA_RXC)));
	/*return value*/
	*Copy_ptru8RxChar=USART_u8UDR;
	return (*Copy_ptru8RxChar);
}
u8	 USART_u8ReceiveString(u8 *Copy_ptru8ArRxString){
	u8 Local_u8Index;

	for(Local_u8Index=0; USART_u8ReceiveChar(&Copy_ptru8ArRxString[Local_u8Index])!='\n'; Local_u8Index++);

	return 1;
}

/*
 * CALLBACK FUNCTIONs
 */
u8		USART_u8RXCSetCallBack(void(* Copy_PtrToFun)(u8)){
	u8 Local_u8ErrorState=STD_TYPES_OK;
	if(Copy_PtrToFun!=NULL){
		//update Global pointer to function of ISR of RXC
		USART_PtrToFunRXC=Copy_PtrToFun;
	}else{
		Local_u8ErrorState=STD_TYPES_NOTOK;
	}

	return Local_u8ErrorState;
}
u8		USART_u8TXCSetCallBack(void(* Copy_PtrToFun)(u8)){
	u8 Local_u8ErrorState=STD_TYPES_OK;
	if(Copy_PtrToFun!=NULL){
		//update Global pointer to function of ISR of TXC
		USART_PtrToFunTXC=Copy_PtrToFun;
	}else{
		Local_u8ErrorState=STD_TYPES_NOTOK;
	}

	return Local_u8ErrorState;
}
u8		USART_u8UDRESetCallBack(void(* Copy_PtrToFun)(u8*)){
	u8 Local_u8ErrorState=STD_TYPES_OK;
	if(Copy_PtrToFun!=NULL){
		//update Global pointer to function of ISR of UDRE
		USART_PtrToFunUDRE=Copy_PtrToFun;
	}else{
		Local_u8ErrorState=STD_TYPES_NOTOK;
	}

	return Local_u8ErrorState;
}

void __vector_13(void) __attribute__((signal));
void __vector_13(void){
//	static u8 Local_u8Char;
	if(USART_PtrToFunRXC!=NULL){
		USART_PtrToFunRXC(USART_u8UDR);
	}
}
void __vector_14(void) __attribute__((signal));
void __vector_14(void){
	if(USART_PtrToFunUDRE!=NULL){
			USART_PtrToFunUDRE(&USART_u8UDR);
		}
}
void __vector_15(void) __attribute__((signal));
void __vector_15(void){

}
