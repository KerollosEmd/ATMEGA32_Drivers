#ifndef TWI_INTERFACE_H
#define TWI_INTERFACE_H

typedef enum{
	TWI_OK,
	TWI_SC_ERROR,
	TWI_RSC_ERROR,
	TWI_SLA_W_ERROR,
	TWI_SLA_R_ERROR,
	TWI_DATA_T_ERROR,
	TWI_NULL_POINTER,
	TWI_DATA_R_ERROR
}TWI_ERR_STATE;


void TWI_voidTWIInit(u8 Copy_u8SlaveAddress);

//u8   TWI_u8SlaveInit(u8 Copy_u8SlaveAddress);

TWI_ERR_STATE TWI_EnuSendStartCondition(void);

TWI_ERR_STATE TWI_EnuSendRepStartCondition(void);

TWI_ERR_STATE TWI_EnuSendSlaveAddWithWrite(u8 Copy_u8SlaveAddress);

TWI_ERR_STATE TWI_EnuSendSlaveAddWithRead (u8 Copy_u8SlaveAddress);

TWI_ERR_STATE TWI_EnuSendDataByte(u8 Copy_u8Byte);

TWI_ERR_STATE TWI_EnuReadDataByte(u8 * Copy_pu8RecByte);

TWI_ERR_STATE TWI_EnuSendStopCondition(void);

#endif
