/*
/*
 * CALC_main.c
 *
 *  Created on: Sep 25, 2021
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

void CALC_voidExit(void);
void CALC_voidError(u8 Copy_u8ErrNum);

u32  CALC_u32ConcatenateNum(u32 Copy_u32Operand,  u32 Copy_NewInput);

void main(void) {
	/*initialize the dio */

	DIO_voidInit();
	/*initialize the LCD in 8 bit mode */
	LCD_voidInit();

	u8 Local_u8Key;
//	u8 Local_u8counterNewLine = 0;
	u32 Local_u32Operand1 = 0, Local_u32Operand2 = 0, Local_u32Result = 0;
	u8		Local_u8Operator;
	u8 /*Local_u8FlagNum = 0,*/ Local_u8FlagOperator=0;
	while (1) {

		/*//check if we get the last character in LCD display region
		 if (Local_u8counterNewLine == 16) {
		 LCD_voidGoToXY(0, LCD_u8_LINE_2);
		 } else if (Local_u8counterNewLine == 31) {
		 LCD_voidGoToXY(0, LCD_u8_LINE_1);
		 Local_u8counterNewLine = 0;
		 }*/
		//get pressed key
		do {
			Local_u8Key = KPD_u8GetPressedKey();
		} while (Local_u8Key == 0xff);

		if (Local_u8Key <= 9) {

//			Local_u8counterNewLine++;
//			Local_u8FlagNum++;
			switch (Local_u8FlagOperator) {
			case 0:
				Local_u32Operand1 =CALC_u32ConcatenateNum(Local_u32Operand1,Local_u8Key) ;
				LCD_voidWritNumber(Local_u8Key);
				break;
			case 1:
				Local_u32Operand2 = CALC_u32ConcatenateNum(Local_u32Operand2,Local_u8Key) ;
				LCD_voidWritNumber(Local_u8Key);
				break;
			default:
				CALC_voidError(1);
				break;
			}

		} else {
			/*
			 switch (Local_u8Key)
			 {
			 case '+': LCD_voidWriteChar('+');break;
			 case '-': LCD_voidWriteChar('-');break;
			 case '*': LCD_voidWriteChar('*');break;
			 case '=': LCD_voidWriteChar('=');break;

			 case '/': LCD_voidWriteChar('/');break;
			 case '%': LCD_voidWriteChar('%');break;
			 }*/

//			Local_u8FlagNum++;
			Local_u8FlagOperator++;
			if (Local_u8FlagOperator == 1) {
				Local_u8Operator = Local_u8Key;
				LCD_voidWriteChar(Local_u8Operator);
			}

//			Local_u8counterNewLine++;

			if ((Local_u8FlagOperator >= 2) && (Local_u8Key == '=')) {
				switch (Local_u8Operator) {
				case '+':
					Local_u32Result = Local_u32Operand1 + Local_u32Operand2;
					LCD_voidWriteChar('=');
					LCD_voidWritNumber(Local_u32Result);
					CALC_voidExit();
					break;
				case '-': {
					if (Local_u32Operand1 > Local_u32Operand2) {
						Local_u32Result = Local_u32Operand1 - Local_u32Operand2;
						LCD_voidWriteChar('=');
						LCD_voidWritNumber(Local_u32Result);
					} else {
						Local_u32Result = Local_u32Operand2 - Local_u32Operand1;
						LCD_voidWriteString("=-");
						LCD_voidWritNumber(Local_u32Result);
					}
				}
					CALC_voidExit();
					break;
				case '*':
					Local_u32Result = Local_u32Operand1 * Local_u32Operand2;
					LCD_voidWriteChar('=');
					LCD_voidWritNumber(Local_u32Result);
					CALC_voidExit();

					break;
				case '/': {
					if (Local_u32Operand2 == 0) {
						LCD_voidWriteCommand(LCD_Clear);
						LCD_voidWriteString("Math Error");
					} else {
						Local_u32Result = Local_u32Operand1 / Local_u32Operand2;
						LCD_voidWriteChar('=');
						LCD_voidWritNumber(Local_u32Result);
						if ((Local_u32Operand1 % Local_u32Operand2) != 0) {
							LCD_voidWriteChar('.');
							Local_u32Result = ((Local_u32Operand1
									% Local_u32Operand2) * 10)
									/ Local_u32Operand2;
							LCD_voidWritNumber(Local_u32Result);
							Local_u32Result = ((((Local_u32Operand1
									% Local_u32Operand2) * 10)
									- (Local_u32Result * Local_u32Operand2)) * 10)
									/ Local_u32Operand2;
							if (Local_u32Result != 0)
								LCD_voidWritNumber(Local_u32Result);
						}
					}
				}
					CALC_voidExit();
					break;
				case '%':
					Local_u32Result = Local_u32Operand1 % Local_u32Operand2;
					LCD_voidWriteChar('=');
					LCD_voidWritNumber(Local_u32Result);
					CALC_voidExit();

					break;
				default:
					CALC_voidError(2);

					break;
				}
			} else if ((Local_u8FlagOperator >= 3) && (Local_u8Key == '+')) {
			Local_u8FlagOperator=0; Local_u32Operand1=0;Local_u32Operand2=0;
				LCD_voidWriteCommand(LCD_Clear);
			}

		}

	}
}

void CALC_voidExit(void) {
	LCD_voidGoToXY(0, LCD_u8_LINE_2);
	LCD_voidWriteString("Press+to Cancel");
}
void CALC_voidError(u8 Copy_u8ErrNum) {
	LCD_voidWriteCommand(LCD_Clear);
	LCD_voidWriteString("Error ");
	LCD_voidWritNumber(Copy_u8ErrNum);
	CALC_voidExit();
}
u32  CALC_u32ConcatenateNum(u32 Copy_u32Operand, u32 Copy_NewInput){

	Copy_u32Operand*=10;
	Copy_u32Operand+=Copy_NewInput;

	return Copy_u32Operand;

}


