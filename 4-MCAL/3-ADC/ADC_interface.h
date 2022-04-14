/********************************************************************************************************/
/*	        ********************			Name: Kerollos Emad                 ******************   	*/
/* 	        ********************			Date: 9-10-2021		                ******************   	*/
/*	        ********************			SWC	: ADC			                ******************   	*/
/*	        ********************			Version: 1.0		                ******************   	*/
/********************************************************************************************************/

#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H


/*MACROS*/


/*********************************TABLE1****************************************************************
**********************************Voltage Reference Selections for ADC**********************************
********************************They are the values that puts in the ADMUX Register*********************
********************************in Bits 7 and 6*********************************************************/
//Reference Selection
#define ADC_u8_AREF                         0b00
#define ADC_u8_AVCC                         0b01
#define ADC_u8_2_56V_IVREF                  0b11
/*******************************************************************************************************/

/*Bit 5 – ADLAR: ADC Left Adjust Result
The ADLAR bit affects the presentation of the ADC conversion result in the ADC Data
Register. Write one to ADLAR to left adjust the result. Otherwise, the result is right
adjusted. Changing the ADLAR bit will affect the ADC Data Register immediately,
regardless of any ongoing conversions.*/

#define ADC_u8_LIFT_ADJUST_RES              1
#define ADC_u8_RIGHT_ADJUST_RES             0

/*********************************TABLE2****************************************************************
**********************************Input Channels and Gain for ADC***************************************
********************************They are the values that puts in the ADMUX Register*********************
********************************in Bits 4 to 0*********************************************************/
//Analog Channel and Gain Selection Bits  
#define ADC_u8_SINGLE_ADC0                  0b00000                    //Single Ended Input
#define ADC_u8_SINGLE_ADC1                  0b00001                    //Single Ended Input
#define ADC_u8_SINGLE_ADC2                  0b00010                    //Single Ended Input
#define ADC_u8_SINGLE_ADC3                  0b00011                    //Single Ended Input
#define ADC_u8_SINGLE_ADC4                  0b00100                    //Single Ended Input
#define ADC_u8_SINGLE_ADC5                  0b00101                    //Single Ended Input
#define ADC_u8_SINGLE_ADC6                  0b00110                    //Single Ended Input
#define ADC_u8_SINGLE_ADC7                  0b00111                    //Single Ended Input

#define ADC_u8_DIFF_pADC0_nADC0_X10         0b01000                    //Differential input with negative ADC0 10X
#define ADC_u8_DIFF_pADC1_nADC0_X10         0b01001                    //Differential input with negative ADC0 10X
#define ADC_u8_DIFF_pADC0_nADC0_X200        0b01010                    //Differential input with negative ADC0 200X
#define ADC_u8_DIFF_pADC1_nADC0_X200        0b01011                    //Differential input with negative ADC0 200X
 
#define ADC_u8_DIFF_pADC2_nADC2_X10         0b01100                    //Differential input witH negative ADC2 10X
#define ADC_u8_DIFF_pADC3_nADC2_X10         0b01101                    //Differential input witH negative ADC2 10X
#define ADC_u8_DIFF_pADC2_nADC2_X200        0b01110                    //Differential input witH negative ADC2 200X
#define ADC_u8_DIFF_pADC3_nADC2_X200        0b01111                    //Differential input witH negative ADC2 200X
 
#define ADC_u8_DIFF_pADC0_nADC1_X1          0b10000                    //Differential input whit negative ADC1 1X
#define ADC_u8_DIFF_pADC1_nADC1_X1          0b10001                    //Differential input whit negative ADC1 1X
#define ADC_u8_DIFF_pADC2_nADC1_X1          0b10010                    //Differential input whit negative ADC1 1X
#define ADC_u8_DIFF_pADC3_nADC1_X1          0b10011                    //Differential input whit negative ADC1 1X
#define ADC_u8_DIFF_pADC4_nADC1_X1          0b10100                    //Differential input whit negative ADC1 1X
#define ADC_u8_DIFF_pADC5_nADC1_X1          0b10101                    //Differential input whit negative ADC1 1X
#define ADC_u8_DIFF_pADC6_nADC1_X1          0b10110                    //Differential input whit negative ADC1 1X
#define ADC_u8_DIFF_pADC7_nADC1_X1          0b10111                    //Differential input whit negative ADC1 1X
 
#define ADC_u8_DIFF_pADC0_nADC2_X1          0b11000                    //Differential input with negative ADC2 1X
#define ADC_u8_DIFF_pADC1_nADC2_X1          0b11001                    //Differential input with negative ADC2 1X
#define ADC_u8_DIFF_pADC2_nADC2_X1          0b11010                    //Differential input with negative ADC2 1X
#define ADC_u8_DIFF_pADC3_nADC2_X1          0b11011                    //Differential input with negative ADC2 1X
#define ADC_u8_DIFF_pADC4_nADC2_X1          0b11100                    //Differential input with negative ADC2 1X
#define ADC_u8_DIFF_pADC5_nADC2_X1          0b11101                    //Differential input with negative ADC2 1X
 
#define ADC_u8_TEST_1_22V_Vbg               0b11110                    //Test the ADC port Pins
#define ADC_u8_TEST_0V_GND                  0b11111                    //Test the ADC port Pins
/*******************************************************************************************************/



//Enable ADC
/*Bit 7 – ADEN: ADC Enable
Writing this bit to one enables the ADC. By writing it to zero, the ADC is turned off. 
Turning the ADC off while a conversion is in progress, will terminate this conversion.*/
#define ADC_u8_ADC_ENABLE                   1
#define ADC_u8_ADC_DISABLE                  0

//Start Conversion
/*Bit 6 – ADSC: ADC Start Conversion
In Single Conversion mode, write this bit to one to start each conversion. In Free Run-
ning Mode, write this bit to one to start the first conversion. The first conversion after
ADSC has been written after the ADC has been enabled, or if ADSC is written at the
same time as the ADC is enabled, will take 25 ADC clock cycles instead of the normal
13. This first conversion performs initialization of the ADC.

ADSC will read as one as long as a conversion is in progress. When the conversion is
complete, it returns to zero. Writing zero to this bit has no effect.*/
#define ADC_u8_START_CONVERSION             1
#define ADC_u8_TERMINATE_CONVERSION         0

//Auto Trigger Enable
/*Bit 5 – ADATE: ADC Auto Trigger Enable
When this bit is written to one, Auto Triggering of the ADC is enabled. The ADC will start
a conversion on a positive edge of the selected trigger signal. The trigger source is
selected by setting the ADC Trigger Select bits, ADTS in SFIOR.*/
#define ADC_u8_AUTO_TRIGGER_ENABLE          1
#define ADC_u8_AUTO_TRIGGER_DISABLE         0

/*Bit 4 – ADIF: ADC Interrupt Flag
This bit is set when an ADC conversion completes and the Data Registers are updated.
The ADC Conversion Complete Interrupt is executed if the ADIE bit and the I-bit in
SREG are set. 
ADIF is cleared by hardware when executing the corresponding interrupt handling vector. 
Alternatively, ADIF is cleared by writing a logical one to the flag.
Beware that if doing a Read-Modify-Write on ADCSRA, a pending interrupt can be dis-
abled. This also applies if the SBI and CBI instructions are used.*/
#define ADC_u8_CLEAR_INTERRUPT             1

/*Bit 3 – ADIE: ADC Interrupt Enable
When this bit is written to one and the I-bit in SREG is set, the ADC Conversion Com-
plete Interrupt is activated.*/

/*********************************TABLE3****************************************************************
**********************************Prescalar for ADC*****************************************************
********************************They are the values that puts in the ADCSRA Register********************
********************************in Bits 2 to 0*********************************************************/
//ADC Prescaler SELECTIONS      
#define ADC_u8_PS_CLK_BY_2                  0                    //CLK DIV BY 2
#define ADC_u8_PS_CLK_BY_2                  1                    //CLK DIV BY 2
#define ADC_u8_PS_CLK_BY_4                  2                    //CLK DIV BY 4
#define ADC_u8_PS_CLK_BY_8                  3                    //CLK DIV BY 8
#define ADC_u8_PS_CLK_BY_16                 4                    //CLK DIV BY 16
#define ADC_u8_PS_CLK_BY_32                 5                    //CLK DIV BY 32
#define ADC_u8_PS_CLK_BY_64                 6                    //CLK DIV BY 64
#define ADC_u8_PS_CLK_BY_128                7                    //CLK DIV BY 128

/*******************************************************************************************************/

/*********************************TABLE4****************************************************************
**********************************ADC Auto Trigger Source Selections************************************
********************************They are the values that puts in the SFIOR Register*********************
********************************in Bits 7 to 5*********************************************************/
//Special Function IO Register SOURCES for Auto Trigger 
//6 Sources for Auto Trigger
#define ADC_u8_SFIOR_FREE_RUN                   0x00             //Free Running 
#define ADC_u8_SFIOR_ANALOG_COMP                0x20             //Analog Comparator
#define ADC_u8_SFIOR_EXTI0_REQ                  0x40             //External Interrupt 0 Request
#define ADC_u8_SFIOR_TC0_COMP_MATCH             0x60             //Timer/Counter0 Compare Match
#define ADC_u8_SFIOR_TC0_OVER_FLOW              0x80             //Timer/Counter0 Overflow
#define ADC_u8_SFIOR_TC_COMP_MATCH_B            0xA0             //Timer/Counter  Compare Match B
#define ADC_u8_SFIOR_TC1_OVER_FLOW              0xC0             //Timer/Counter1 Over Flow
#define ADC_u8_SFIOR_TC1_CAPT_EVENT             0xE0             //Timer/Counter1 Capture Event

/*******************************************************************************************************/


void ADC_voidInit(void);

u8   ADC_u8GetDigitalValueSync(u8 Copy_u8ChannelNum, u16* Copy_u16ReturnedDigitalValue);

u8   ADC_u8GetDigitalValue8bitsSync(u8 Copy_u8ChannelNum, u8* Copy_u8ReturnedDigitalValue);

u8 	 ADC_u8GetDigitalValueAsync(u8 Copy_u8ChannelNum, /*u16* Copy_u16ReturnedDigitalValue,*/ void(*Copy_PtrToFun)(/*void*/u16));

u8   ADC_u8SetChannelandGain(u8 Copy_u8ChannelGain);

u8   ADC_u8SetREF(u8 Copy_u8REF);

u8   ADC_u8SetPrescaler(u8 Copy_u8Prescaler);

u8   ADC_u8AutoTriggerSource(u8 Copy_u8ATS);
void ADC_voidAutoTriggerDisable(void);

u8   ADC_u8ResultAdjustment(u8 Copy_u8ADLAR);

#endif
