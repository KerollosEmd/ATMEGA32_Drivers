/*
 * Timer_private.h
 *
 *  Created on: Oct 22, 2021
 *      Author: KeroEmad
 */

#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

#define TMR_u8_TIMSK_REG	        *((volatile u8*)0x59)
#define TMR_u8_TIFR_REG	         	*((volatile u8*)0x58)

/*********************************************************/
/*********************************************************/
/*******************Timer/Counter0************************/
/*********************************************************/
/*********************************************************/

#define TMR0_u8_OCR0_REG			*((volatile u8*)0x5C)
#define TMR0_u8_TCCR0_REG			*((volatile u8*)0x53)
#define TMR0_u8_TCNT0_REG			*((volatile u8*)0x52)


/*
 * TCCR0 Bits Configuration
 */
/*Clock Select Mode Bits*/
#define TMR0_TCCR0_CS00				0
#define TMR0_TCCR0_CS01				1
#define TMR0_TCCR0_CS02				2
/*Compare Match Output Mode Bits */
#define TMR0_TCCR0_COM00			4
#define TMR0_TCCR0_COM01			5
/*Wave Generation Mode Bits*/
#define TMR0_TCCR0_WGM01			3
#define TMR0_TCCR0_WGM00			6
/*Force Output Compare Bit*/
#define TMR0_TCCR0_FOC0				7

/*
 * TIMSK Bits Configuration
 */
/*Timer0 Interrupt Enable Bits*/
#define TMR0_OCIE0					1
#define TMR0_TOIE0					0

#define Timer0						0
#define Timer1						1
#define Timer2						2

/*********************************************************/
/*********************************************************/
/*******************Timer/Counter1************************/
/*********************************************************/
/*********************************************************/

#endif /* TIMER_PRIVATE_H_ */
