/********************************************************************************************************/
/*	        ********************			Name: Kerollos Emad                 ******************   	*/
/* 	        ********************			Date: 9-10-2021		                ******************   	*/
/*	        ********************			SWC	: ADC			                ******************   	*/
/*	        ********************			Version: 1.0		                ******************   	*/
/********************************************************************************************************/


/********************************************************************************************************/
//ADC Multiplexer selection register BITs Names
//|  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |   BITS
//|REFS1|REGS0| LAR |MUX4 |MUX3 |MUX2 |MUX1 |MUX0 |   NAME


/********************************************************************************************************/
/*Channels Options:*/

/* <<single ended input>>
1 -ADC_u8_SINGLE_ADC0_BINARY
2 -ADC_u8_SINGLE_ADC1_BINARY
3 -ADC_u8_SINGLE_ADC2_BINARY
4 -ADC_u8_SINGLE_ADC3_BINARY
5 -ADC_u8_SINGLE_ADC4_BINARY
6 -ADC_u8_SINGLE_ADC5_BINARY
7 -ADC_u8_SINGLE_ADC6_BINARY
8 -ADC_u8_SINGLE_ADC7_BINARY */

/* <<Differential input with negative ADC0>>
9 -ADC_u8_DIFF_pADC0_nADC0_X10_BINARY 
10-ADC_u8_DIFF_pADC1_nADC0_X10_BINARY 
11-ADC_u8_DIFF_pADC0_nADC0_X200_BINARY
12-ADC_u8_DIFF_pADC1_nADC0_X200_BINARY */

/* <<Differential input witH negative ADC2>>
13-ADC_u8_DIFF_pADC2_nADC2_X10_BINARY 
14-ADC_u8_DIFF_pADC3_nADC2_X10_BINARY 
15-ADC_u8_DIFF_pADC2_nADC2_X200_BINARY
16-ADC_u8_DIFF_pADC3_nADC2_X200_BINARY */

/* <<Differential input whit negative ADC1 1X>>
17-ADC_u8_DIFF_pADC0_nADC1_X1_BINARY
18-ADC_u8_DIFF_pADC1_nADC1_X1_BINARY
19-ADC_u8_DIFF_pADC2_nADC1_X1_BINARY
20-ADC_u8_DIFF_pADC3_nADC1_X1_BINARY
21-ADC_u8_DIFF_pADC4_nADC1_X1_BINARY
22-ADC_u8_DIFF_pADC5_nADC1_X1_BINARY
23-ADC_u8_DIFF_pADC6_nADC1_X1_BINARY
24-ADC_u8_DIFF_pADC7_nADC1_X1_BINARY */

/* <<Differential input with negative ADC2 1X>>
25-ADC_u8_DIFF_pADC0_nADC2_X1_BINARY
26-ADC_u8_DIFF_pADC1_nADC2_X1_BINARY
27-ADC_u8_DIFF_pADC2_nADC2_X1_BINARY
28-ADC_u8_DIFF_pADC3_nADC2_X1_BINARY
29-ADC_u8_DIFF_pADC4_nADC2_X1_BINARY
30-ADC_u8_DIFF_pADC5_nADC2_X1_BINARY */

/*<<Test the ADC port Pins>>
31-ADC_u8_TEST_1_22V_Vbg_BINARY
32-ADC_u8_TEST_0V_GND_BINARY
*/

#define ADC_u8_MUXREG_MUX_BITS              ADC_u8_SINGLE_ADC6_BINARY
/********************************************************************************************************/

/********************************************************************************************************/
/*Options:
1-ADC_u8_LIFT_ADJUST_RES
2-ADC_u8_RIGHT_ADJUST_RES
*/
#define ADC_u8_MUXREG_LAR_BITS                   ADC_u8_RIGHT_ADJUST_RES                   
/********************************************************************************************************/

/********************************************************************************************************/
/*Options:
1-ADC_u8_AREF_BINARY
2-ADC_u8_AVCC_BINARY
3-ADC_u8_2_56V_IVREF_BINARY
*/
#define ADC_u8_MUXREG_REFS_BITS                ADC_u8_AVCC_BINARY                   
/********************************************************************************************************/

