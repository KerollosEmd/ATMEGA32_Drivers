/********************************************************************************************************/
/*	        ********************			Name: Kerollos Emad                 ******************   	*/
/* 	        ********************			Date: 9-10-2021		                ******************   	*/
/*	        ********************			SWC	: ADC			                ******************   	*/
/*	        ********************			Version: 1.0		                ******************   	*/
/********************************************************************************************************/

#include "C:\Users\KeroEmad\Desktop\imt_july\COTS\4-LibLayer\STD_Types.h"
#include "C:\Users\KeroEmad\Desktop\imt_july\COTS\4-LibLayer\BIT_MATH.h"

#include "ADC_config.h"
#include "ADC_private.h"
#include "ADC_interface.h"

/* static u16 * ADC_Ptru16DigitalValue=NULL; */

static u8 ADC_u8BusyFlag= ADC_u8_NOT_BUSY;

static void(*ADC_PtrToFun)(/*void*/u16)=NULL;

void ADC_voidInit(void){
    /*select vref= AVCC*/
    ADC_u8SetREF(ADC_u8_AVCC);

    /*select right adjustment*/
    ADC_u8ResultAdjustment(ADC_u8_RIGHT_ADJUST_RES);

    /*single conversion mode*/
    ADC_voidAutoTriggerDisable();

    /*adc enable */
    SET_BIT(ADC_u8_ADCSRA_REG,ADC_u8_CSRA_ADEN);

    /*Select Prescaler*/
    ADC_u8SetPrescaler(ADC_u8_PS_CLK_BY_64);
}

void ADC_voidConfig(void){
    ADC_u8_ADMUX_REG = PRIVATE_u8_CONC_ADMUX(ADC_u8_MUXREG_REFS_BITS,ADC_u8_MUXREG_LAR_BITS,ADC_u8_MUXREG_MUX_BITS);


}


u8   ADC_u8GetDigitalValueSync(u8 Copy_u8ChannelNum, u16* Copy_u16ReturnedDigitalValue){
    u8 Local_u8ErrorState =STD_TYPES_OK;

    u32 Local_u32TimeOutCounter=0;

    if(ADC_u8SetChannelandGain(Copy_u8ChannelNum)&&(Copy_u16ReturnedDigitalValue!=NULL)){
        //start conversion 
        SET_BIT(ADC_u8_ADCSRA_REG,ADC_u8_CSRA_ADSC);

        //wait for the flag 
        while ((!GET_BIT(ADC_u8_ADCSRA_REG,ADC_u8_CSRA_ADIF))&&(Local_u32TimeOutCounter<1000000UL))
        	Local_u32TimeOutCounter++;

        //Check flag
        if(GET_BIT(ADC_u8_ADCSRA_REG,ADC_u8_CSRA_ADIF))
        {

        //clear flag 
        SET_BIT(ADC_u8_ADCSRA_REG,ADC_u8_CSRA_ADIF);

        //read digital value 
        *Copy_u16ReturnedDigitalValue=ADC_u16_ADCDATA_REG;
        }else{
            Local_u8ErrorState=STD_TYPES_NOTOK;
        }
    }else{
        Local_u8ErrorState=STD_TYPES_NOTOK;
    }

    return Local_u8ErrorState;
}

u8   ADC_u8GetDigitalValue8bitsSync(u8 Copy_u8ChannelNum, u8* Copy_u8ReturnedDigitalValue){
    u8 Local_u8ErrorState =STD_TYPES_OK;

    if(ADC_u8SetChannelandGain(Copy_u8ChannelNum)&&(Copy_u8ReturnedDigitalValue!=NULL)){
        //start conversion
        SET_BIT(ADC_u8_ADCSRA_REG,ADC_u8_CSRA_ADSC);

        //wait for the flag
        while (!GET_BIT(ADC_u8_ADCSRA_REG,ADC_u8_CSRA_ADIF));

        //clear flag
        SET_BIT(ADC_u8_ADCSRA_REG,ADC_u8_CSRA_ADIF);

        //read digital value
        *Copy_u8ReturnedDigitalValue=ADC_u8_ADCH_REG;

    }else{
        Local_u8ErrorState=STD_TYPES_NOTOK;
    }

    return Local_u8ErrorState;
}

u8 	 ADC_u8GetDigitalValueAsync(u8 Copy_u8ChannelNum, /*u16* Copy_u16ReturnedDigitalValue,*/ void(*Copy_PtrToFun)(/*void*/u16)){
	u8 Local_u8ErrorState= STD_TYPES_OK;

	//Check Channel Number , Check Pointers
	if((ADC_u8BusyFlag==ADC_u8_NOT_BUSY)&&ADC_u8SetChannelandGain(Copy_u8ChannelNum)/*&&(Copy_u16ReturnedDigitalValue!=NULL)*/){
	//Change  Busy flag into Busy state
		ADC_u8BusyFlag=ADC_u8_BUSY;
	//update Global pointers with the input addresses
		/*ADC_Ptru16DigitalValue = Copy_u16ReturnedDigitalValue;*/
		ADC_PtrToFun		   = Copy_PtrToFun;
	//Select ADC Channel
		/*done it in the if condition*/
	//ADC Interrupt enable
		SET_BIT(ADC_u8_ADCSRA_REG, ADC_u8_CSRA_ADIE);
	//ADC Start Conversion
		SET_BIT(ADC_u8_ADCSRA_REG,ADC_u8_CSRA_ADSC);

	}else{
		Local_u8ErrorState=STD_TYPES_NOTOK;
	}

	return Local_u8ErrorState;
}

/*ISR of ADC*/
void __vector_16(void) __attribute__((signal));
void __vector_16(void){
	if((ADC_PtrToFun!=NULL)/*&&(ADC_Ptru16DigitalValue!=NULL)*/){
		//Update digital value
		/**ADC_Ptru16DigitalValue=ADC_u16_ADCDATA_REG;*/
		//Call Notification Function
		ADC_PtrToFun(ADC_u16_ADCDATA_REG);
		//Disable Interrupt
		CLR_BIT(ADC_u8_ADCSRA_REG, ADC_u8_CSRA_ADIE);
		//Set Busy flag into Not Busy state
		ADC_u8BusyFlag=ADC_u8_NOT_BUSY;
	}
}

u8   ADC_u8SetChannelandGain(u8 Copy_u8ChannelGain){
    u8 Local_u8ErrorState = STD_TYPES_OK;

    if(Copy_u8ChannelGain<ADC_u8_CHANNEL_NUM){
        //Clear Channel and Gain in the ADMUX Register
        ADC_u8_ADMUX_REG &=ADC_u8_CLR_MUX_BITS;
        
        //Set Channel and Gain in the ADMUX Register
        ADC_u8_ADMUX_REG |=Copy_u8ChannelGain;

    }else{
        Local_u8ErrorState=STD_TYPES_NOTOK;
    }

    return Local_u8ErrorState;
}

/*This function Takes the required Voltage Reference Source 
Options:
-->For applying external reference voltage :         (ADC_u8_AREF)
-->For applying the AVCC reference with
   External Capcitor on AREF Pin:                    (ADC_u8_AVCC)
-->For applying the Internal 2.56V Voltage
Reference with extarnal Capacitor on AREF Pin:       (ADC_u8_2_56V_IVREF)
                        <<<<<Hint>>>>>
The internal voltage reference options may not be
used if an external reference voltage is being applied to the AREF pin.*/
u8   ADC_u8SetREF(u8 Copy_u8REF){
    u8 Local_u8ErrorState=STD_TYPES_OK;

    if((Copy_u8REF<ADC_u8_VREF_NUM)&&(Copy_u8REF!=ADC_u8_VREF_RESERVED_BIT)){
        //Clear Voltage Reference Selection Bits in ADMUX Register
        ADC_u8_ADMUX_REG &= ADC_u8_CLR_REFS;

        //Set Reference selection bits 
        ADC_u8_ADMUX_REG |= (Copy_u8REF<<ADC_u8_REF_SHIFT);

    }else{
        Local_u8ErrorState=STD_TYPES_NOTOK;
    }

    return Local_u8ErrorState;
}

u8   ADC_u8SetPrescaler(u8 Copy_u8Prescaler){
    u8 Local_u8ErrorState = STD_TYPES_OK;

    if(Copy_u8Prescaler<ADC_u8_PS_NUM){
        //Clear Prescaler Selection Bits in
        ADC_u8_ADCSRA_REG &=ADC_u8_CLR_PS_BITS;

        //Set Prescaler Selection Bits
        ADC_u8_ADCSRA_REG |=Copy_u8Prescaler;

    }else{
        Local_u8ErrorState=STD_TYPES_NOTOK;
    }

    return Local_u8ErrorState;
}


u8   ADC_u8AutoTriggerSource(u8 Copy_u8ATS){
    u8 Local_u8ErrorState = STD_TYPES_OK;

    if(!GET_BIT(Copy_u8ATS,ADC_u8_SFIOR_RESERVED_BIT)){
        //Enable Auto Trigger Sources in ADCSRA
        SET_BIT(ADC_u8_ADCSRA_REG,ADC_u8_CSRA_ADATE);

        //Clear Auto Trigger Source Selection Bits in SFIOR
        ADC_u8_SFIOR_REG &= ADC_u8_CLR_ADTS_BITS;

        //Set  Auto  Trigger Source Selection Bits in SFIOR
        ADC_u8_SFIOR_REG |= Copy_u8ATS;

        //Start Conversion
        SET_BIT(ADC_u8_ADCSRA_REG,ADC_u8_CSRA_ADSC);

    }else{
        Local_u8ErrorState=STD_TYPES_NOTOK;
    }

    return Local_u8ErrorState;
}

/*This function has no arguments as it just Disable the 
Auto Trigger Sources by clearing the ADATE bit in ADCSRA register*/
void ADC_voidAutoTriggerDisable(void){
    //Enable Auto Trigger Sources in ADCSRA
    CLR_BIT(ADC_u8_ADCSRA_REG,ADC_u8_CSRA_ADATE);
}

/*This function takes 0 or 1 to adjust the result.
Where for left adjust result put            "ADC_u8_RIGHT_ADJUST_RES",
Alternativily, for right adjust result put  "ADC_u8_LIFT_ADJUST_RES".
Otherwise the function will return error state.*/
u8   ADC_u8ResultAdjustment(u8 Copy_u8ADLAR){
    u8 Local_u8ErrorState=STD_TYPES_OK;
    
    switch (Copy_u8ADLAR)
    {
    case ADC_u8_LIFT_ADJUST_RES:
        SET_BIT(ADC_u8_ADMUX_REG,ADC_u8_MUXREG_LAR);
        break;
    case ADC_u8_RIGHT_ADJUST_RES:
        CLR_BIT(ADC_u8_ADMUX_REG,ADC_u8_MUXREG_LAR);
        break;
    default: Local_u8ErrorState=STD_TYPES_NOTOK;
        break;
    }

    return Local_u8ErrorState;
}
