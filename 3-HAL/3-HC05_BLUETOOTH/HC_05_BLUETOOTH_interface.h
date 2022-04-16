/*
 * HC_05_BLUETOOTH_interface.h
 *
 *  Created on: Feb 10, 2022
 *      Author: KeroEmad
 */

#ifndef HC_05_BLUETOOTH_INTERFACE_H_
#define HC_05_BLUETOOTH_INTERFACE_H_
u8	 HC05BL_voidInitCommandMode(void);
void HC05BL_voidEndCommandMode(void);
void HC05BL_voidInitModule(void);
/*
 * AT Command Mode
 */
u8 HC05BL_u8SendCommand(u8 *Copy_u8CommandString);
u8 HC05BL_u8SetPassword(u32 Copy_u32Password);
u8 HC05BL_u8SetName(u8 *Copy_pu8Name);
u8 HC05BL_u8UARTconfig(u32 Copy_u32BaudRate, u8 Copy_u8StopBit, u8 Copy_u8ParityBit);
u8 HC05BL_u8GetState(void);
/*
 * Data Mode
 */
u8 HC05BL_u8SendMessage(u8 *Copy_pAu8Message);
u8 HC05BL_u8ReceiveMessage(u8 *Copy_pAu8Message);
#endif /* HC_05_BLUETOOTH_INTERFACE_H_ */
