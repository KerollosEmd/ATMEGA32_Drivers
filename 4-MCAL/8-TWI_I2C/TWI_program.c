#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "TWI_interface.h"
#include "TWI_private.h"
#include "TWI_config.h"

void TWI_voidTWIInit(u8 Copy_u8SlaveAddress){


	/* Enable TWI and Enable ACK */
	SET_BIT(TWI_u8_TWCR_REG,6);
	SET_BIT(TWI_u8_TWCR_REG,2);
	/* Set Clk 100KHZ with no Prescaler */
	/* TWPS = 0 */
	CLR_BIT(TWI_u8_TWSR_REG,1);
	CLR_BIT(TWI_u8_TWSR_REG,0);

	TWI_u8_TWBR_REG = 32;
	/* Assign my Own Add => TWAR */
	TWI_u8_TWAR_REG = Copy_u8SlaveAddress<<1;


}

//u8   TWI_u8SlaveInit(u8 Copy_u8SlaveAddress);

TWI_ERR_STATE TWI_EnuSendStartCondition(void){
	TWI_ERR_STATE Local_EnuErrorState = TWI_OK;
	/* Send Start Condition */
	SET_BIT(TWI_u8_TWCR_REG,5);
	/* Clear Flag to Start the new Job */
	SET_BIT(TWI_u8_TWCR_REG,7);
	/* Wait for The Flag */
	while(!GET_BIT(TWI_u8_TWCR_REG,7));
	/* Check Status Code (ACK) */
	if((TWI_u8_TWSR_REG & 0xF8) != 0x08){

		Local_EnuErrorState = TWI_SC_ERROR;
	}
	else{
		/* Clear Start Condition Bit */
//		CLR_BIT(TWI_u8_TWCR_REG,5);
	}
	return Local_EnuErrorState;
}

TWI_ERR_STATE TWI_EnuSendRepStartCondition(void){
	TWI_ERR_STATE Local_EnuErrorState = TWI_OK;
	/* Send Start Condition */
	SET_BIT(TWI_u8_TWCR_REG,5);
	/* Clear Flag to Start the new Job */
	SET_BIT(TWI_u8_TWCR_REG,7);
	/* Wait for The Flag */
	while(!GET_BIT(TWI_u8_TWCR_REG,7));
	/* Check Status Code (ACK) */
	if((TWI_u8_TWSR_REG & 0xF8) != 0x10){
		Local_EnuErrorState = TWI_RSC_ERROR;
	}
	else{
		/* Clear Start Condition Bit */
//		CLR_BIT(TWI_u8_TWCR_REG,5);
	}
	return Local_EnuErrorState;
}

TWI_ERR_STATE TWI_EnuSendSlaveAddWithWrite(u8 Copy_u8SlaveAddress){
	TWI_ERR_STATE Local_EnuErrorState = TWI_OK;

	/* Write Slave Address into TWDR Reg + 0(Write) */
	TWI_u8_TWDR_REG = Copy_u8SlaveAddress<<1;
	/* Select Write Operation */
	CLR_BIT(TWI_u8_TWDR_REG,0);
	/* Clear Start Condition Bit */
	CLR_BIT(TWI_u8_TWCR_REG,5);
	/* Clear Flag to Start New Job */
	SET_BIT(TWI_u8_TWCR_REG,7);
	/* Wait for The Flag */
	while(!GET_BIT(TWI_u8_TWCR_REG,7));
	/* Check Status Code (ACK) */
	if((TWI_u8_TWSR_REG & 0xF8) != 0x18){
//		DIO_u8SetPinValue(DIO_u8_PORTB,DIO_u8_PIN0,DIO_u8_HIGH);
		Local_EnuErrorState = TWI_SLA_W_ERROR;
	}
	return Local_EnuErrorState;
}

TWI_ERR_STATE TWI_EnuSendSlaveAddWithRead (u8 Copy_u8SlaveAddress){
	TWI_ERR_STATE Local_EnuErrorState = TWI_OK;

	/* Write Slave Address into TWDR Reg + 1(Read) */
	TWI_u8_TWDR_REG = Copy_u8SlaveAddress<<1;

	/* Select Read Operation */
	SET_BIT(TWI_u8_TWDR_REG,0);
	/* Clear Start Condition Bit */
	CLR_BIT(TWI_u8_TWCR_REG,5);
	/* Clear Flag to Start New Job */
	SET_BIT(TWI_u8_TWCR_REG,7);
	/* Wait for The Flag */
	while(!GET_BIT(TWI_u8_TWCR_REG,7));
	/* Check Status Code (ACK) */
	if((TWI_u8_TWSR_REG & 0xF8) != 0x40){
		Local_EnuErrorState = TWI_SLA_R_ERROR;
	}
	return Local_EnuErrorState;
}

TWI_ERR_STATE TWI_EnuSendDataByte(u8 Copy_u8Byte){
	TWI_ERR_STATE Local_EnuErrorState = TWI_OK;
	/* Write Byte into TWDR Reg */
	TWI_u8_TWDR_REG = Copy_u8Byte;
	/* Clear Flag to Start New Job */
	SET_BIT(TWI_u8_TWCR_REG,7);
	/* Wait for The Flag */
	while(!GET_BIT(TWI_u8_TWCR_REG,7));
	/* Check Status Code (ACK) */
	if((TWI_u8_TWSR_REG & 0xF8) != 0x28){
		Local_EnuErrorState = TWI_DATA_T_ERROR;
	}
	return Local_EnuErrorState;
}

TWI_ERR_STATE TWI_EnuReadDataByte(u8 * Copy_pu8RecByte){
	TWI_ERR_STATE Local_EnuErrorState = TWI_OK;
	if(Copy_pu8RecByte != NULL){
		/* Start Job of Reading */
		SET_BIT(TWI_u8_TWCR_REG,7);
		/* Wait for The Flag */
		while(!GET_BIT(TWI_u8_TWCR_REG,7));
		/* Check Status Code (ACK) */
		if((TWI_u8_TWSR_REG & 0xF8) != 0x50){
			Local_EnuErrorState = TWI_DATA_R_ERROR;
		}
		else{/* Valid Data */
			*Copy_pu8RecByte = TWI_u8_TWDR_REG;
		}
	}
	else{
		Local_EnuErrorState = TWI_NULL_POINTER;
	}
	return Local_EnuErrorState;
}

TWI_ERR_STATE TWI_EnuSendStopCondition(void){
	TWI_ERR_STATE Local_EnuErrorState = TWI_OK;
	/* Send Stop Condition */
	SET_BIT(TWI_u8_TWCR_REG,4);
	/* Clear Flag to Start new job */
	SET_BIT(TWI_u8_TWCR_REG,7);
	return Local_EnuErrorState;
}
