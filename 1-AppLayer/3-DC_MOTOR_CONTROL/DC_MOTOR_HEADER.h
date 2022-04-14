/*
 * DC_MOTOR_HEADER.h
 *
 *  Created on: Oct 18, 2021
 *      Author: KeroEmad
 */

#ifndef DC_MOTOR_HEADER_H_
#define DC_MOTOR_HEADER_H_

/*macros*/
#define MOTOR_CW_PORT	DIO_u8_PORTA
#define MOTOR_CW_PIN	DIO_u8_PIN0

#define MOTOR_CCW_PORT	DIO_u8_PORTA
#define MOTOR_CCW_PIN	DIO_u8_PIN1


#define DC_MOTOR_CONTROL	1

#define DC_CW				1
#define DC_CCW				2
#define DC_STOP				3
#define DC_RETURN			4

void DC_Motor_app(void);

#endif /* DC_MOTOR_HEADER_H_ */
