/*
 * ADC_DRIVER_TEST.c
 *
 *  Created on: Oct 12, 2021
 *      Author: KeroEmad
 */

/*Libraries*/
#include "STD_Types.h"
#include "BIT_MATH.h"
#define	 F_CPU 8000000UL
#include <util/delay.h>

/*MCAL*/
#include "DIO_interface.h"
#include "ADC_interface.h"
#include "GIE_interface.h"

/*HAL*/
#include "LCD_interface.h"

#define LED_u8_PORT    DIO_u8_PORTB

#define LED_u8_RED	   DIO_u8_PIN0
#define LED_u8_YELLOW  DIO_u8_PIN1
#define LED_u8_GREEN   DIO_u8_PIN2

u8 App_u8Flag = 0;

u16 App_u16DigitalValue=0xffff;

void App_voidNotificationFunc(/*void*/u16);

void main(void) {

	DIO_voidInit();

	LCD_voidInit();

	/*ADC_voidConfig();*/

	ADC_voidInit();

	ADC_u8SetREF(ADC_u8_AVCC);

	GIE_voidEnable();

	//ADC_u8ResultAdjustment(ADC_u8_LIFT_ADJUST_RES);

	u16 Local_u8ADCValue;

	while (1) {
		LCD_voidWriteCommand(LCD_Clear);
		/*ADC_u8GetDigitalValueSync(ADC_u8_SINGLE_ADC6,&Local_u8ADCValue)*/
		if (ADC_u8GetDigitalValueAsync(ADC_u8_SINGLE_ADC6, /*&App_u16DigitalValue*//*&Local_u8ADCValue,*/
				&App_voidNotificationFunc)) {
			if (/*!App_u8Flag*/App_u16DigitalValue!=0xffff) {
				/*Local_u8ADCValue*/Local_u8ADCValue = (/*Local_u8ADCValue*/App_u16DigitalValue* 5000UL) / 1024;
				LCD_voidWritNumber(/*Local_u8ADCValue*/Local_u8ADCValue);
				LCD_voidWriteString(" mV");
				//check if v>=0, v<1500
				if (/*Local_u8ADCValue*/Local_u8ADCValue < 2000) {
					DIO_u8SetPinValue(LED_u8_PORT, LED_u8_RED, DIO_u8_LOW);
					DIO_u8SetPinValue(LED_u8_PORT, LED_u8_YELLOW, DIO_u8_LOW);
					DIO_u8SetPinValue(LED_u8_PORT, LED_u8_GREEN, DIO_u8_HIGH);
				} else if ((/*Local_u8ADCValue*/Local_u8ADCValue >= 2000)
						&& (/*Local_u8ADCValue*/Local_u8ADCValue < 3000)) {
					DIO_u8SetPinValue(LED_u8_PORT, LED_u8_RED, DIO_u8_LOW);
					DIO_u8SetPinValue(LED_u8_PORT, LED_u8_YELLOW, DIO_u8_HIGH);
					DIO_u8SetPinValue(LED_u8_PORT, LED_u8_GREEN, DIO_u8_LOW);
				} else if (/*Local_u8ADCValue*/Local_u8ADCValue >= 3000) {
					DIO_u8SetPinValue(LED_u8_PORT, LED_u8_RED, DIO_u8_HIGH);
					DIO_u8SetPinValue(LED_u8_PORT, LED_u8_YELLOW, DIO_u8_LOW);
					DIO_u8SetPinValue(LED_u8_PORT, LED_u8_GREEN, DIO_u8_LOW);
				}
				/*App_u8Flag=1;*/
				App_u16DigitalValue=0xffff;
				/*_delay_ms(500);*/
			}else {
				LCD_voidWriteString("DV not Updated");
				/*_delay_ms(500);*/
			}

		} else {
			LCD_voidWriteString("Error in async func");
		}
		_delay_ms(200);
	}
}

void App_voidNotificationFunc(u16 Copy_u16DigitalValue) {
	/*App_u8Flag = 0;*/
	App_u16DigitalValue=Copy_u16DigitalValue;
}
