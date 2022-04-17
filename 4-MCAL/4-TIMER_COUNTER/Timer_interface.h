/*
 * Timer_interface.h
 *
 *  Created on: Oct 22, 2021
 *      Author: KeroEmad
 */
/*
 * https://maxembedded.com/2011/06/introduction-to-avr-timers/
 * https://maxembedded.com/2011/06/avr-timers-timer0/
 * https://maxembedded.com/2011/06/avr-timers-timer1/
 *
 * Timers Basic equations and calculations :
 * Time_period_per_Tick= 1/F_CPU;		//Thus, for 8MHz F_CPU time period for each tick is 0.125 us
 * Timer_Num_ofTicks=(Required_delay/Time_period_per_Tick)-1; //So, it will requires 7999 Tick to make 1 ms delay
 * Pre_scaler:
 * 		For 8Mhz F_CPU:-
 * 		so for making 1 ms delay function it will requires
 * 		a 64 prescaler selection
 * 		and a 125 tickes only for reaching 1 ms
 *
 */

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_
/*General Macros for all Timer/Counters Peripherals */
#define TMR_PRESCALER_0			      0b001
#define TMR_PRESCALER_8			      0b010
#define TMR_PRESCALER_64		      0b011
#define TMR_PRESCALER_256		      0b100
#define TMR_PRESCALER_1024		      0b101
#define TMR_EXT_CLK_FALLING_EDG	      0b110
#define TMR_EXT_CLK_RISING_EDG	      0b111
/*********************************************************/
/*********************************************************/
/*******************Timer/Counter0************************/
/*********************************************************/
/*********************************************************/

/*********************************************************/
/************************Macros****************************/
/*********************************************************/
#define TMR0_OVF_INT			      0
#define TMR0_CTC_INT			      1
/*********************************************************/
/************************API's****************************/
/*********************************************************/
void TMR0_voidNormalMode_init(u32 Copy_u32prescalerValue);
void TMR0_voidCTCMode_init(u8 Copy_u8CompareValue, u8 Copy_u8ClkSource);
void TMR0_voidCTCoutputMode_init(u8 Copy_u8CompareValue, u32 Copy_u32prescalerValue);
void TMR0_voidPWM(u32 Copy_u32Frequency);
void TMR0_voidEnable(void);
void TMR0_voidDisable(void);
void TMR0_voidExecuteEvery_ms_init(void);
void TMR0_voidExcuteEvery_ms(void(*Copy_PtrToFun)(void),u16 Copy_u16RequiredTime_ms);
u8 	 TMR0_u8SetDelay_ms(u32 Copy_u32DelayTime);
u8 	 TMR0_u8SetCallBack(u8 Copy_u8TMRInt,void(*Copy_PtrToFun)(void));

/*********************************************************/
/*********************************************************/
/*******************Timer/Counter1************************/
/*********************************************************/
/*********************************************************/


#endif /* TIMER_INTERFACE_H_ */


