/****************************************/
/*				Name: kerollos Emad 	*/
/* 				Date: 18-9-2021			*/
/*				SWC	: KEYPAD			*/
/*				Version: 1.0			*/
/****************************************/

//library
#include "STD_Types.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "KPD_config.h"
#include "KPD_privat.h"
#include "KPD_interface.h"


u8 KPD_u8GetPressedKey(void)
{
	u8 Local_u8PressedKey=KPD_No_PRESSED_KEY, Local_u8PinState;

	static u8 Local_u8KPDArr[ROW_NUM][COLUMN_NUM]= KPD_ARR_VAL;

	static u8 Local_u8KPDColArr[COLUMN_NUM]={
			KPD_COL0_PIN,
			KPD_COL1_PIN,
			KPD_COL2_PIN,
			KPD_COL3_PIN
	};

	static u8 Local_u8KPDRowArr[ROW_NUM]={
				KPD_ROW0_PIN,
				KPD_ROW1_PIN,
				KPD_ROW2_PIN,
				KPD_ROW3_PIN
		};

	u8 Local_u8ColIndex, Local_u8RowIndex;

	for(Local_u8ColIndex=0;Local_u8ColIndex<COLUMN_NUM;Local_u8ColIndex++)
	{
		//activate current column
		DIO_u8SetPinValue(KPD_PORT,Local_u8KPDColArr[Local_u8ColIndex],DIO_u8_LOW);

		for(Local_u8RowIndex=0;Local_u8RowIndex<ROW_NUM;Local_u8RowIndex++)
		{
			//read current row
			DIO_u8GetPinValue(KPD_PORT,Local_u8KPDRowArr[Local_u8RowIndex],&Local_u8PinState);
			//check the switch
			if(Local_u8PinState==DIO_u8_LOW)
			{
				Local_u8PressedKey=Local_u8KPDArr[Local_u8RowIndex][Local_u8ColIndex];

				while(Local_u8PinState==DIO_u8_LOW)
				{
					DIO_u8GetPinValue(KPD_PORT,Local_u8KPDRowArr[Local_u8RowIndex],&Local_u8PinState);
				}

				return Local_u8PressedKey;
			}
		}

		//deactivate current column
		DIO_u8SetPinValue(KPD_PORT,Local_u8KPDColArr[Local_u8ColIndex],DIO_u8_HIGH);
	}


	return Local_u8PressedKey;
}
