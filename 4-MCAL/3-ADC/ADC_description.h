/*****************************************************************************************************
************************************Analog to digital convirter *************************************


analoge value =digital value * step size 

Quantization_error: 
            difference between actual value and the calculated value.

10 mV --> 1 C 
0.5 V --> 50 C 


Uref we can control on it 


conversion time for the Succiseve Approximate register 
conversion time = TC * Number of bits (resolution)


registers of ADC:
    ADMUX: ADC multiplexer --> 010- ---  (address 0x27)
    SFIOR: Special Function I/O --> ---------- not used 
    ADCSRA: ADC Control and Status --> (ADEN|ADSC|ADATE|ADIF|ADIE|1|1|0 ) ---> 110 for prescaler select bits (CLK/64 Mode)

*/


/* assignments make adc driver*/