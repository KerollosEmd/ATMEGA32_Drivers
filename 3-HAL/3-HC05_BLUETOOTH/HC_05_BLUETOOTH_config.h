/*
 * HC_05_BLUETOOTH_config.h
 *
 *  Created on: Feb 10, 2022
 *      Author: KeroEmad
 */

#ifndef HC_05_BLUETOOTH_CONFIG_H_
#define HC_05_BLUETOOTH_CONFIG_H_

#define HC05BL_EN_KEY_PIN			DIO_u8_PIN3
#define HC05BL_EN_KEY_PORT			DIO_u8_PORTD

#define HC05BL_VCC_PIN				DIO_u8_PIN2
#define HC05BL_VCC_PORT				DIO_u8_PORTD

/*
 * HC05BL Sittings Configuration for Initializing Module
 */

//	If you to reconfigure Sittings of Module Please Change the
//	macro below to : HC05BL_RECONFIG
#define HC05BL_IS_DEFAULT				HC05BL_DEFAULT
#define HC05BL_PASSWORD					1234					//Default 1234

#define HC05BL_DATAMODE_BAUD_RATE		HC05BL_9600				//Default HC05BL_9600
#define HC05BL_STOP_BITS				HC05BL_1_SB				//Default HC05BL_1_SB
#define HC05BL_PARITY_BITS				HC05BL_DISABLE_PARITY	//Default HC05BL_DISABLE_PARITY

#endif /* HC_05_BLUETOOTH_CONFIG_H_ */
