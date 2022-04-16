/*
 * HC_05_BLUETOOTH_private.h
 *
 *  Created on: Feb 10, 2022
 *      Author: KeroEmad
 */

#ifndef HC_05_BLUETOOTH_PRIVATE_H_
#define HC_05_BLUETOOTH_PRIVATE_H_
#define HC05BL_OK						1
#define HC05BL_NOTOK					0

#define HC05BL_DEFAULT					0
#define HC05BL_RECONFIG					1

#define HC05BL_ATCOMMAND_BAUD_RATE		38400UL
#define HC05BL_9600          			9600UL
#define HC05BL_1_SB          			1
#define HC05BL_2_SB          			2
#define HC05BL_DISABLE_PARITY			0
#define HC05BL_ODD_PARITY				1
#define HC05BL_EVEN_PARITY				2

/*
 * Private ENUM
 */
typedef enum{
	HC05BL_NORMAL_MODE,
	HC05BL_COMMAND_MODE,
	HC05BL_COMMAND_MODE_CONNECTED,
	HC05BL_IS_CONNECTED,
	HC05BL_TOTAL_NUM_OF_FLAGS
}HC05BL_FLAG_ENUMTYPE;
void HC05BL_Private_voidNUMtoStringConv(u32 Copy_u32NUM,u8* Copy_pu8Array);


#endif /* HC_05_BLUETOOTH_PRIVATE_H_ */
