/*
 * Timer_prog.c
 *
 *  Created on: Oct 22, 2021
 *      Author: KeroEmad
 */

#include "STD_Types.h"
#include "BIT_MATH.h"

#include "Timer_config.h"
#include "Timer_interface.h"
#include "Timer_private.h"

#include "GIE_interface.h"
/*********************************************************/
/*********************************************************/
/****************** Timer/Counter0************************/
/*********************************************************/
/*********************************************************/

/*Global Pointers to Function Interrupt*/
static void(*TMR0_ArrPtrToFunInt[2])(void)={NULL,NULL};
/*Global Variables*/
static u16	TMR0_u16CTCcounter=0;
static u8 TMR0_u8CS0=0;
static u8 TMR0_u8CTC_ISR_flag=0;
static u8 TMR0_u8TOV_ISR_flag=0;

void TMR0_voidCTCMode_init(u8 Copy_u8CompareValue, u8 Copy_u8ClkSource){

//	 * Set WGM0[1:0]=2 To select CTC Mode for TMR0
	SET_BIT(TMR0_u8_TCCR0_REG,TMR0_TCCR0_WGM01);
	CLR_BIT(TMR0_u8_TCCR0_REG,TMR0_TCCR0_WGM00);
//	* update OCR0 Register by Copy_u8CompareValue
	TMR0_u8_OCR0_REG=Copy_u8CompareValue;
//	* Update pre_scaler
	TMR0_u8_TCCR0_REG|=Copy_u8ClkSource;
	TMR0_u8CS0=Copy_u8ClkSource;
//	* Enable Global Interrupt
	GIE_voidEnable();
//	* Enable output compare match interrupt
	SET_BIT(TMR_u8_TIMSK_REG,TMR0_OCIE0);
}
void TMR0_voidExecuteEvery_ms_init(void){
//	* Initialize CTC mode of timer0 with 64 pre_scaler and 125 Compare match value
	TMR0_voidCTCMode_init(125,TMR_PRESCALER_64);// this value is pre_calculated for F_CPU 8MHz Clock

}
void TMR0_voidExcuteEvery_ms(void(*Copy_PtrToFun)(void),u16 Copy_u16RequiredTime_ms){
//	* Update Global Pointer to Function of CTC ISR
	if(Copy_PtrToFun!=NULL){
			TMR0_ArrPtrToFunInt[TMR0_CTC_INT]=Copy_PtrToFun;
	}
//	* Update Global variable
	TMR0_u16CTCcounter=Copy_u16RequiredTime_ms;
}



u8 	 TMR0_u8SetCallBack(u8 Copy_u8TMRInt,void(*Copy_PtrToFun)(void)){
	u8 Local_u8ErrorState=STD_TYPES_OK;

	if(Copy_PtrToFun!=NULL){
		TMR0_ArrPtrToFunInt[Copy_u8TMRInt]=Copy_PtrToFun;
	}else{
		Local_u8ErrorState=STD_TYPES_NOTOK;
	}

	return Local_u8ErrorState;
}
/*********************************************************/

void TMR0_voidEnable(void){
	if(TMR0_u8CS0!=0)
		TMR0_u8_TCCR0_REG|=TMR0_u8CS0;
}
void TMR0_voidDisable(void){
	while(TMR0_u8CTC_ISR_flag);
	TMR0_u8_TCCR0_REG &= ~0b111;
}
/*********************************************************/
/*********************************************************/
/***********Interrupt Service Routine for Timer 0*********/
/*********************************************************/
/*********************************************************/
/*******************OVF TIMER0 ISR************************/
void __vector_11(void) __attribute__((signal));
void __vector_11(void){

/*
	static u16  Local_u16Counter=0;
	Local_u16Counter++;
	if(Local_u16Counter==3907){
		update timer counter with preload value
		TMR_u8_TMR0_TCNT0_REG=192;
		if(TMR0_ArrPtrToFunInt[TMR_u8_TMR0_OVF_INT]!=NULL){
			TMR0_ArrPtrToFunInt[TMR_u8_TMR0_OVF_INT]();
		}
		Local_u16Counter=0;
	}
*/
}

/*******************CTC TIMER0 ISR************************/
void __vector_10(void) __attribute__((signal));
void __vector_10(void){
	static u16  Local_u16Counter=0;
	Local_u16Counter++;
	TMR0_u8CTC_ISR_flag=1;
	if(Local_u16Counter==TMR0_u16CTCcounter){
		if(TMR0_ArrPtrToFunInt[TMR0_CTC_INT]!=NULL){
			TMR0_ArrPtrToFunInt[TMR0_CTC_INT]();
		}
		Local_u16Counter=0;
		TMR0_u8CTC_ISR_flag=0;
	}
}
/*********************************************************/
/*********************************************************/

