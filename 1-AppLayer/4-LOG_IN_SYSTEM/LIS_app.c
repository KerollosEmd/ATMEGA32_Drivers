/********************************************************************************************************/
/*	        ********************			Name: Kerollos Emad                 ******************   	*/
/* 	        ********************			Date: 9-10-2021		                ******************   	*/
/*	        ********************			SWC	: LOG_IN_SYSTEM	                ******************   	*/
/*	        ********************			Version: 1.2		                ******************   	*/
/********************************************************************************************************/


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

/*APPLayer*/
#include "LIS_header.h"

/*Macros*/

#define LIS_HOME_POS			4

u32 LIS_u32ConcatenateNum(u32 Copy_u32Operand, u32 Copy_NewInput);

u8 LogInSystem(void) {



	u8 Local_u8ErrorState=STD_TYPES_OK;
	u8 Local_u8Key, Local_u8Xpos = LIS_HOME_POS;
	u8 Local_u8WrongTrials = 0;

	u32 Local_u32EnteredValue = 0;

	//Print order to the user to Enter his password
	LCD_voidWriteCommand(LCD_Clear);
	LCD_voidWriteString("Enter Password :");
	LCD_voidGoToXY(Local_u8Xpos, LCD_u8_LINE_2);


	// loop
	while (1) {
		//take from the user the entered Numbers
		do {
			Local_u8Key = KPD_u8GetPressedKey();
		} while (Local_u8Key == 0xff);

		if (Local_u8Key <= 9) {
			Local_u32EnteredValue = LIS_u32ConcatenateNum(Local_u32EnteredValue,
					Local_u8Key);

			//print the entered value to lcd
			LCD_voidGoToXY(Local_u8Xpos, LCD_u8_LINE_2);
			LCD_voidWritNumber(Local_u8Key);

			//replace the number entered by '*'
			_delay_ms(400);
			LCD_voidGoToXY(Local_u8Xpos, LCD_u8_LINE_2);
			LCD_voidWriteChar('*');

			Local_u8Xpos++;

		} else if (Local_u8Key == '=') {

			if (Local_u8WrongTrials < NUMBER_OF_TRIALS) {

				if (Local_u32EnteredValue == LOG_IN_PASSWORD) {
					/*Break Supper Loop of Log in System*/
					break;
				} else {
					Local_u8Xpos = LIS_HOME_POS;
					Local_u8WrongTrials++;
					LCD_voidWriteCommand(LCD_Clear);

					LCD_voidGoToXY(0, LCD_u8_LINE_1);
					LCD_voidWriteString("Wrong Password");

					LCD_voidGoToXY(0, LCD_u8_LINE_2);
					LCD_voidWriteString("Try Again:");

					Local_u32EnteredValue = 0;

					_delay_ms(2000);
					LCD_voidWriteCommand(LCD_Clear);
					LCD_voidWriteString("Enter Password :");
					LCD_voidGoToXY(Local_u8Xpos, LCD_u8_LINE_2);
				}
			} else {


				//return error state
				Local_u8ErrorState=STD_TYPES_NOTOK;
				DIO_u8SetPinValue(LIS_BUZZER_PORT,LIS_BUZZER_PIN,DIO_u8_HIGH);
				LCD_voidWriteCommand(LCD_Clear);
				LCD_voidWriteString("System Failure");
				while(1);
				break;
			}
		}
	}
	return Local_u8ErrorState;
}

u32 LIS_u32ConcatenateNum(u32 Copy_u32Operand, u32 Copy_NewInput) {
	Copy_u32Operand *= 10;
	Copy_u32Operand += Copy_NewInput;

	return Copy_u32Operand;
}
