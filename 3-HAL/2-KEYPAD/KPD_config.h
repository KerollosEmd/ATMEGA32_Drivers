/****************************************/
/*				Name: kerollos Emad 	*/
/* 				Date: 18-9-2021			*/
/*				SWC	: KEYPAD			*/
/*				Version: 1.0			*/
/****************************************/

#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_

#define KPD_PORT			DIO_u8_PORTB

#define KPD_COL0_PIN		DIO_u8_PIN4
#define KPD_COL1_PIN		DIO_u8_PIN5
#define KPD_COL2_PIN		DIO_u8_PIN6
#define KPD_COL3_PIN		DIO_u8_PIN7

#define KPD_ROW0_PIN		DIO_u8_PIN3
#define KPD_ROW1_PIN		DIO_u8_PIN2
#define KPD_ROW2_PIN		DIO_u8_PIN1
#define KPD_ROW3_PIN		DIO_u8_PIN0

#define KPD_No_PRESSED_KEY  0xff

#define KPD_ARR_VAL			{{0,2,0,0},{5,0,7,0},{0,10,0,0},{0,0,0,0}}

#endif
