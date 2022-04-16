/*
 * HC_05_BLUETOOTH_prog.c
 *
 *  Created on: Feb 10, 2022
 *      Author: KeroEmad
 */

#include "STD_Types.h"
#include "BIT_MATH.h"
#define F_CPU 		8000000UL
#include <util/delay.h>
#include "LCD_interface.h"

/*
 * MCAL LIBRARIES
 */
#include "DIO_interface.h"
#include "USART_interface.h"
#include "GIE_interface.h"

/*
 * HAL LIBRARIES
 */
#include "HC_05_BLUETOOTH_config.h"
#include "HC_05_BLUETOOTH_interface.h"
#include "HC_05_BLUETOOTH_private.h"
/*
 * Array of Flags
 */

static HC05BL_FLAG_ENUMTYPE 	HC05BL_Au8Flags[HC05BL_TOTAL_NUM_OF_FLAGS]={0};

u8	 HC05BL_voidInitCommandMode(void){
	//	*update flag for Entering Command Mode Function
	HC05BL_Au8Flags[HC05BL_COMMAND_MODE]=HC05BL_OK;
	//	*Local Variables
	u8 Local_u8ErrorState=STD_TYPES_OK;
	u8 Local_u8RxString[10]="AT\r\n";
	//	u8 Local_u8Index=0;
	//	*Reset VCC pin of Module
	DIO_u8SetPinValue(HC05BL_VCC_PORT,HC05BL_VCC_PIN,DIO_u8_LOW);
	//	*Set EN key pin to enter command mode
	DIO_u8SetPinValue(HC05BL_EN_KEY_PORT,HC05BL_EN_KEY_PIN,DIO_u8_HIGH);
	//	*Set USART BAUD RATE TO ATCOMMAND MODE BAUD RATE
	USART_voidBaudRate(HC05BL_ATCOMMAND_BAUD_RATE);
	//	*Delay for Debounce
	_delay_ms(50);
	//	*Power Up Module
	DIO_u8SetPinValue(HC05BL_VCC_PORT,HC05BL_VCC_PIN,DIO_u8_HIGH);
	// 	*delay for wake up circuit
	_delay_ms(1000);
	//	*Check Connection of AT Command Mode
	USART_u8SendString(Local_u8RxString);
	USART_u8ReceiveString(Local_u8RxString);
	/*	LCD_voidWritNumber(Local_u8RxString[0]);
	for(Local_u8Index=1;Local_u8RxString[Local_u8Index]!='\r';Local_u8Index++){
		LCD_voidWriteChar(Local_u8RxString[Local_u8Index]);
	}*/
	if(Local_u8RxString[0]==0){
		DIO_u8SetPinValue(DIO_u8_PORTD,DIO_u8_PIN7,DIO_u8_HIGH);
		//	*Update Flags
		HC05BL_Au8Flags[HC05BL_NORMAL_MODE]=HC05BL_NOTOK;
		HC05BL_Au8Flags[HC05BL_COMMAND_MODE_CONNECTED]=HC05BL_OK;
	}else{
		HC05BL_Au8Flags[HC05BL_COMMAND_MODE_CONNECTED]=HC05BL_NOTOK;
		Local_u8ErrorState=STD_TYPES_NOTOK;
	}
	return Local_u8ErrorState;
}

void HC05BL_voidEndCommandMode(void){
	//	*Reset VCC pin of Module
	DIO_u8SetPinValue(HC05BL_VCC_PORT,HC05BL_VCC_PIN,DIO_u8_LOW);
	//	*Reset EN key pin to enter NORMAL mode
	DIO_u8SetPinValue(HC05BL_EN_KEY_PORT,HC05BL_EN_KEY_PIN,DIO_u8_LOW);
	//	*Set USART BAUD RATE TO NORML MODE BAUD RATE
	USART_voidBaudRate(HC05BL_DATAMODE_BAUD_RATE);
	_delay_ms(50);
	//	*Power Up Module
	DIO_u8SetPinValue(HC05BL_VCC_PORT,HC05BL_VCC_PIN,DIO_u8_HIGH);
	//	*	Update Flags
	HC05BL_Au8Flags[HC05BL_COMMAND_MODE]=HC05BL_NOTOK;
	HC05BL_Au8Flags[HC05BL_COMMAND_MODE_CONNECTED]=HC05BL_NOTOK;
	HC05BL_Au8Flags[HC05BL_NORMAL_MODE]=HC05BL_OK;
}


u8 HC05BL_u8SendCommand(u8 *Copy_u8CommandString){
	u8 Local_u8ErrorState=STD_TYPES_OK;
	//	*Check Command Mode is initialized Correctly
	if((HC05BL_Au8Flags[HC05BL_COMMAND_MODE_CONNECTED]==HC05BL_OK)&&(HC05BL_Au8Flags[HC05BL_COMMAND_MODE]==HC05BL_OK)){
		DIO_u8SetPinValue(DIO_u8_PORTD,DIO_u8_PIN7,DIO_u8_HIGH);
		//		*Send Command
		USART_u8SendString(Copy_u8CommandString);
		//		*Receive response on The Same String pointer
		USART_u8ReceiveString(Copy_u8CommandString);

	}else{
		Local_u8ErrorState=STD_TYPES_NOTOK;
	}

	return Local_u8ErrorState;
}


void HC05BL_voidInitModule(void){

	//	 * initialize USART with Normal Mode Baud Rate
	USART_voidInit(HC05BL_DATAMODE_BAUD_RATE);
	/*
	//	 * Enable RxC&TxC Interrupt
	USART_voidInterruptEn();
	//	* Enable Global Interrupt
	GIE_voidEnable();
	 */
	//	* Turn on power to Module In Normal Mode
	DIO_u8SetPinValue(HC05BL_VCC_PORT,HC05BL_VCC_PIN,DIO_u8_HIGH);

	/*
	 * Check if Default sittings Changed or not
	 */
#if (HC05BL_IS_DEFAULT==HC05BL_RECONFIG)
	//	reconfigure module
	HC05BL_voidInitCommandMode();
	HC05BL_u8UARTconfig(HC05BL_DATAMODE_BAUD_RATE,HC05BL_STOP_BITS,HC05BL_PARITY_BITS);


#endif
}


/*
 * AT Command Mode
 */
u8 HC05BL_u8SetPassword(u32 Copy_u32Password){
	u8 Local_u8ErrorState=STD_TYPES_OK;
	u8 Local_u8CommandString[15]="AT+PSWD=";
	u8 Local_u8Index=0;
	//	*Check Command Mode is initialized Correctly
	if((HC05BL_Au8Flags[HC05BL_COMMAND_MODE_CONNECTED]==HC05BL_OK)&&(HC05BL_Au8Flags[HC05BL_COMMAND_MODE]==HC05BL_OK)){
		//		*Convert Numbers to String
		HC05BL_Private_voidNUMtoStringConv(Copy_u32Password,&Local_u8CommandString[8]);
		//		*Set end of Command \r\n
		for(Local_u8Index=0;Local_u8CommandString[Local_u8Index]!='\0';Local_u8Index++);
		Local_u8CommandString[Local_u8Index]='\r';
		Local_u8CommandString[++Local_u8Index]='\n';
		Local_u8CommandString[++Local_u8Index]='\0';
		//		*Send Command
		HC05BL_u8SendCommand(Local_u8CommandString);

	}else{
		Local_u8ErrorState=STD_TYPES_NOTOK;
	}

	return Local_u8ErrorState;

}

u8 HC05BL_u8SetName(u8 *Copy_pu8Name){
	u8 Local_u8ErrorState=STD_TYPES_OK;
	u8 Local_u8CommandString[15]="AT+NAME=";
	u8 Local_u8Index=0;
	//	*Check Command Mode is initialized Correctly
	if((HC05BL_Au8Flags[HC05BL_COMMAND_MODE_CONNECTED]==HC05BL_OK)&&(HC05BL_Au8Flags[HC05BL_COMMAND_MODE]==HC05BL_OK)){
//		*Assign New Name with Command Name
		for(;Copy_pu8Name[Local_u8Index]!='\0';Local_u8Index++){
			Local_u8CommandString[Local_u8Index+8]=Copy_pu8Name[Local_u8Index];
		}
		//		*Set end of Command \r\n
		for(Local_u8Index=0;Local_u8CommandString[Local_u8Index]!='\0';Local_u8Index++);
		Local_u8CommandString[Local_u8Index]='\r';
		Local_u8CommandString[++Local_u8Index]='\n';
		Local_u8CommandString[++Local_u8Index]='\0';
		//		*Send Command
		HC05BL_u8SendCommand(Local_u8CommandString);

	}else{
		Local_u8ErrorState=STD_TYPES_NOTOK;
	}

	return Local_u8ErrorState;
}


u8 HC05BL_u8UARTconfig(u32 Copy_u32BaudRate, u8 Copy_u8StopBit, u8 Copy_u8ParityBit){
	u8 Local_u8ErrorState=STD_TYPES_OK;
	u8 Local_u8Index=0;
	u8 Local_u8CommandStart[]="AT+UART=";
	u8 Local_u8CommandString[25];
	for(;Local_u8CommandStart[Local_u8Index]!='\0';Local_u8Index++){
		Local_u8CommandString[Local_u8Index]=Local_u8CommandStart[Local_u8Index];
	}
	HC05BL_Private_voidNUMtoStringConv(Copy_u32BaudRate,&Local_u8CommandString[Local_u8Index]);
	for(;Local_u8CommandString[Local_u8Index]!='\0';Local_u8Index++);
	Local_u8CommandString[Local_u8Index]=',';
	Local_u8Index++;
	HC05BL_Private_voidNUMtoStringConv(Copy_u8StopBit,&Local_u8CommandString[Local_u8Index]);
	for(;Local_u8CommandString[Local_u8Index]!='\0';Local_u8Index++);
	Local_u8CommandString[Local_u8Index]=',';
	Local_u8Index++;
	HC05BL_Private_voidNUMtoStringConv(Copy_u8ParityBit,&Local_u8CommandString[Local_u8Index]);
	for(;Local_u8CommandString[Local_u8Index]!='\0';Local_u8Index++);
	Local_u8CommandString[Local_u8Index]='\r';
	Local_u8CommandString[++Local_u8Index]='\n';
	Local_u8CommandString[++Local_u8Index]='\0';

	Local_u8ErrorState=HC05BL_u8SendCommand(Local_u8CommandString);

	return Local_u8ErrorState;
}
u8 HC05BL_u8GetState(void);
/*
 * Data Mode
 */
u8 HC05BL_u8SendMessage(u8 *Copy_pAu8Message){
	u8 Local_u8ErrorState=STD_TYPES_OK;

	USART_u8SendString(Copy_pAu8Message);

	return Local_u8ErrorState;
}

u8 HC05BL_u8ReceiveMessage(u8 *Copy_pAu8Message){
	u8 Local_u8ErrorState=STD_TYPES_OK;
	USART_u8ReceiveString(Copy_pAu8Message);
	return Local_u8ErrorState;
}

/*
 * Private Functions
 */
void HC05BL_Private_voidNUMtoStringConv(u32 Copy_u32NUM, u8* Copy_pu8Array){
	//local variables
	u8 local_u8Length = 0;

	u32 local_u32num = Copy_u32NUM;
	u32 Local_u32Index;

	while (local_u32num != 0) {
		local_u8Length++;
		local_u32num /= 10;
	}

	//Split the whole number to units , tens , hundreds ,.... etc.
	for (Local_u32Index = 0; Copy_u32NUM != 0; Local_u32Index++) {
		Copy_pu8Array[local_u8Length - (Local_u32Index + 1)] = '0'
				+ (u8) (Copy_u32NUM % 10); //convert integer to ASCII
		Copy_u32NUM /= 10;
	}

	Copy_pu8Array[local_u8Length] = '\0';

	if(local_u8Length==0)
	{
		Copy_pu8Array[local_u8Length]='0';
		Copy_pu8Array[local_u8Length+1] = '\0';
	}
	else
	{
		Copy_pu8Array[local_u8Length] = '\0';
	}
}

