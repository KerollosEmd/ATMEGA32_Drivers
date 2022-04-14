/********************************************************************************************************/
/*	        ********************			Name: Kerollos Emad                 ******************   	*/
/* 	        ********************			Date: 9-10-2021		                ******************   	*/
/*	        ********************			SWC	: LOG_IN_SYSTEM	                ******************   	*/
/*	        ********************			Version: 1.2		                ******************   	*/
/********************************************************************************************************/

#ifndef LIS_HEADER_H_
#define LIS_HEADER_H_

u8 LogInSystem(void);

//set the password
#define LOG_IN_PASSWORD			1234
#define SYSTEM_ERROR			0xEE
#define NUMBER_OF_TRIALS		3

//CONFIGURATIONS
#define LIS_BUZZER_PORT			DIO_u8_PORTA
#define LIS_BUZZER_PIN			DIO_u8_PIN2

#endif /* LIS_HEADER_H_ */
