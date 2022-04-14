/*
 * Kit_main.c
 *
 *  Created on: Oct 2, 2021
 *      Author: KeroEmad
 */

/*Libraries*/
#include "STD_Types.h"
#include "BIT_MATH.h"
#define	 F_CPU 8000000UL
#include <util/delay.h>

/*MCAL*/
#include "DIO_interface.h"

/*HAL*/
#include "LCD_interface.h"
#include "KPD_interface.h"

/*APP LAYER*/
#include "DC_MOTOR_HEADER.h"


void DC_Motor_app(void){
	u8 	Local_u8KeyValue;

	/*Entering the System*/
	LCD_voidWriteCommand(LCD_Clear);
	LCD_voidWriteString("Welcome To");
	LCD_voidGoToXY(0,LCD_u8_LINE_2);
	LCD_voidWriteString("Motor Dash Board");
	_delay_ms(3000);

	LCD_voidWriteCommand(LCD_Clear);
	LCD_voidWriteString("1-CW    3-STOP");
	LCD_voidGoToXY(0,LCD_u8_LINE_2);
	LCD_voidWriteString("2-CCW   4-RETURN");
	while(1){
		do {
			Local_u8KeyValue = KPD_u8GetPressedKey();
		} while (Local_u8KeyValue == 0xff);

		if(DC_CW==Local_u8KeyValue){

			DIO_u8SetPinValue(MOTOR_CW_PORT,MOTOR_CW_PIN,DIO_u8_HIGH);
			DIO_u8SetPinValue(MOTOR_CCW_PORT,MOTOR_CCW_PIN,DIO_u8_LOW);
		}
		else if(DC_CCW==Local_u8KeyValue){
			DIO_u8SetPinValue(MOTOR_CCW_PORT,MOTOR_CCW_PIN,DIO_u8_HIGH);
			DIO_u8SetPinValue(MOTOR_CW_PORT,MOTOR_CW_PIN,DIO_u8_LOW);
		}else if(DC_STOP==Local_u8KeyValue){
			DIO_u8SetPinValue(MOTOR_CCW_PORT,MOTOR_CCW_PIN,DIO_u8_LOW);
			DIO_u8SetPinValue(MOTOR_CW_PORT,MOTOR_CW_PIN,DIO_u8_LOW);
		}else if(DC_RETURN==Local_u8KeyValue){
			break;
		}
	}

}

