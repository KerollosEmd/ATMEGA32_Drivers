/********************************************************************************************************/
/*	        ********************			Name: Kerollos Emad                 ******************   	*/
/* 	        ********************			Date: 9-10-2021		                ******************   	*/
/*	        ********************			SWC	: ADC			                ******************   	*/
/*	        ********************			Version: 1.0		                ******************   	*/
/********************************************************************************************************/
#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

#define ADC_u8_NOT_BUSY 0
#define ADC_u8_BUSY 	1

#define ADC_u8_SFIOR_REG               *((volatile u8*)0x50)
#define ADC_u8_ADMUX_REG               *((volatile u8*)0x27)
#define ADC_u8_ADCSRA_REG              *((volatile u8*)0x26)

#define ADC_u8_ADCH_REG                *((volatile u8*)0x25)
#define ADC_u8_ADCL_REG                *((volatile u8*)0x24)

#define ADC_u16_ADCDATA_REG           *((volatile u16*)0x24)

/*******************************************************************************************************/
//ADC Multiplexer selection register BITs Names
//|  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |   BITS
//|REFS1|REGS0| LAR |MUX4 |MUX3 |MUX2 |MUX1 |MUX0 |   NAME
#define ADC_u8_MUXREG_MUX0                  0                   //Analog Channel and Gain Selection Bit0                      
#define ADC_u8_MUXREG_MUX1                  1                   //Analog Channel and Gain Selection Bit1           
#define ADC_u8_MUXREG_MUX2                  2                   //Analog Channel and Gain Selection Bit2
#define ADC_u8_MUXREG_MUX3                  3                   //Analog Channel and Gain Selection Bit3
#define ADC_u8_MUXREG_MUX4                  4                   //Analog Channel and Gain Selection Bit4

#define ADC_u8_MUXREG_LAR                   5                   //ADC Left Adjusted Results
#define ADC_u8_MUXREG_REFS0                 6                   //Reference Selection Bits
#define ADC_u8_MUXREG_REFS1                 7                   //Reference Selection Bits

#define ADC_u8_REF_SHIFT                    6
#define ADC_u8_VREF_NUM                     4
#define ADC_u8_VREF_RESERVED_BIT            2
#define ADC_u8_CLR_REFS                     0x3F
/*******************************************************************************************************/


/*******************************************************************************************************/
//ADC Control and status Register A
//|  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |   BITS
//|ADEN |ADSC |ADATE|ADIF |ADIE |ADPS2|ADPS1|ADPS0|   NAME
#define ADC_u8_CSRA_ADPS0                   0                    //ADC Prescaler Select Bits
#define ADC_u8_CSRA_ADPS1                   1                    //ADC Prescaler Select Bits
#define ADC_u8_CSRA_ADPS2                   2                    //ADC Prescaler Select Bits

#define ADC_u8_CSRA_ADIE                    3                    //ADC Interrupt Enable
#define ADC_u8_CSRA_ADIF                    4                    //ADC Interrupt Flag
#define ADC_u8_CSRA_ADATE                   5                    //ADC Auto Trigger Enable
#define ADC_u8_CSRA_ADSC                    6                    //ADC Start Conversion
#define ADC_u8_CSRA_ADEN                    7                    //ADC Enable

#define ADC_u8_PS_NUM                       8
#define ADC_u8_CLR_PS_BITS                  0xFC                 //Clear Prescaler Bits in ADCSR by anding 
/*******************************************************************************************************/

/*******************************************************************************************************/
#define ADC_u8_SFIOR_RESERVED_BIT               4
#define ADC_u8_CLR_ADTS_BITS                    0x0F             //Clear Auto Trigger Selection Bits in SFIOR 
/*******************************************************************************************************/

/*******************************************************************************************************/
#define ADC_u8_CHANNEL_NUM                  32                   //Channel number and Gain
#define ADC_u8_CLR_MUX_BITS                 0xE0                 //Clear Mux Bits in the ADMUX Register by Anding this macro
/*******************************************************************************************************/

/*********************************TABLE2****************************************************************
**********************************Input Channels and Gain for ADC***************************************
********************************They are the values that puts in the ADMUX Register*********************
********************************in Bits 4 to 0*********************************************************/
//Analog Channel and Gain Selection Bits  
#define ADC_u8_SINGLE_ADC0_BINARY                  00000                    //Single Ended Input
#define ADC_u8_SINGLE_ADC1_BINARY                  00001                    //Single Ended Input
#define ADC_u8_SINGLE_ADC2_BINARY                  00010                    //Single Ended Input
#define ADC_u8_SINGLE_ADC3_BINARY                  00011                    //Single Ended Input
#define ADC_u8_SINGLE_ADC4_BINARY                  00100                    //Single Ended Input
#define ADC_u8_SINGLE_ADC5_BINARY                  00101                    //Single Ended Input
#define ADC_u8_SINGLE_ADC6_BINARY                  00110                    //Single Ended Input
#define ADC_u8_SINGLE_ADC7_BINARY                  00111                    //Single Ended Input

#define ADC_u8_DIFF_pADC0_nADC0_X10_BINARY         01000                    //Differential input with negative ADC0 10X
#define ADC_u8_DIFF_pADC1_nADC0_X10_BINARY         01001                    //Differential input with negative ADC0 10X
#define ADC_u8_DIFF_pADC0_nADC0_X200_BINARY        01010                    //Differential input with negative ADC0 200X
#define ADC_u8_DIFF_pADC1_nADC0_X200_BINARY        01011                    //Differential input with negative ADC0 200X
 
#define ADC_u8_DIFF_pADC2_nADC2_X10_BINARY         01100                    //Differential input witH negative ADC2 10X
#define ADC_u8_DIFF_pADC3_nADC2_X10_BINARY         01101                    //Differential input witH negative ADC2 10X
#define ADC_u8_DIFF_pADC2_nADC2_X200_BINARY        01110                    //Differential input witH negative ADC2 200X
#define ADC_u8_DIFF_pADC3_nADC2_X200_BINARY        01111                    //Differential input witH negative ADC2 200X
 
#define ADC_u8_DIFF_pADC0_nADC1_X1_BINARY          10000                    //Differential input whit negative ADC1 1X
#define ADC_u8_DIFF_pADC1_nADC1_X1_BINARY          10001                    //Differential input whit negative ADC1 1X
#define ADC_u8_DIFF_pADC2_nADC1_X1_BINARY          10010                    //Differential input whit negative ADC1 1X
#define ADC_u8_DIFF_pADC3_nADC1_X1_BINARY          10011                    //Differential input whit negative ADC1 1X
#define ADC_u8_DIFF_pADC4_nADC1_X1_BINARY          10100                    //Differential input whit negative ADC1 1X
#define ADC_u8_DIFF_pADC5_nADC1_X1_BINARY          10101                    //Differential input whit negative ADC1 1X
#define ADC_u8_DIFF_pADC6_nADC1_X1_BINARY          10110                    //Differential input whit negative ADC1 1X
#define ADC_u8_DIFF_pADC7_nADC1_X1_BINARY          10111                    //Differential input whit negative ADC1 1X
 
#define ADC_u8_DIFF_pADC0_nADC2_X1_BINARY          11000                    //Differential input with negative ADC2 1X
#define ADC_u8_DIFF_pADC1_nADC2_X1_BINARY          11001                    //Differential input with negative ADC2 1X
#define ADC_u8_DIFF_pADC2_nADC2_X1_BINARY          11010                    //Differential input with negative ADC2 1X
#define ADC_u8_DIFF_pADC3_nADC2_X1_BINARY          11011                    //Differential input with negative ADC2 1X
#define ADC_u8_DIFF_pADC4_nADC2_X1_BINARY          11100                    //Differential input with negative ADC2 1X
#define ADC_u8_DIFF_pADC5_nADC2_X1_BINARY          11101                    //Differential input with negative ADC2 1X
 
#define ADC_u8_TEST_1_22V_Vbg_BINARY               11110                    //Test the ADC port Pins
#define ADC_u8_TEST_0V_GND_BINARY                  11111                    //Test the ADC port Pins
/*******************************************************************************************************/

/*********************************TABLE1****************************************************************
**********************************Voltage Reference Selections for ADC**********************************
********************************They are the values that puts in the ADMUX Register*********************
********************************in Bits 7 and 6*********************************************************/
//Reference Selection
#define ADC_u8_AREF_BINARY                         00
#define ADC_u8_AVCC_BINARY                         01
#define ADC_u8_2_56V_IVREF_BINARY                  11
/*******************************************************************************************************/


/*******************************************************************************************************/
#define PRIVATE_u8_CONC(B7,B6,B5,B4,B3,B2,B1,B0)		PRIVATE_u8_CONC_HELP(B7,B6,B5,B4,B3,B2,B1,B0)
#define PRIVATE_u8_CONC_HELP(B7,B6,B5,B4,B3,B2,B1,B0)	0b##B7##B6##B5##B4##B3##B2##B1##B0
/*******************************************************************************************************/

/*******************************************************************************************************/
#define PRIVATE_u8_CONC_ADMUX(B2,B1,B0)		PRIVATE_u8_CONC_ADMUX_HELP(B2,B1,B0)
#define PRIVATE_u8_CONC_ADMUX_HELP(B2,B1,B0)	0b##B2##B1##B0
/*******************************************************************************************************/

#endif  
