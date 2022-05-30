# TIMER/COUNTER

/*tiks_num = 1023;  //--->timer 10 bits
F_CPU=8000000UL;
prescale_time=1000000;
OVF_time=1024;//----->1024 uS

//50000000 us desired time
desired_tiks=4882.8125;
preloadValue=1024-832=192;
//counter--->4883

//initialize timer counter
preloadValue=832;

ISR(ovf){
    static u16 counter=0;
    if(counter=4883){
        timer_counter=preloadValue
        //code{

        //}
        counter=0;
    }
}

/*rules*/
/*
timerFreq=F_CPU/prescale
time of one tike= 1/timeFreq =1 uS
time of OVF= time of one tike*2^(Res)=1024 uS

number of OvF= desired time /time of OVF =48882.8125

number of tikes of (0.8125)= 0.8125 *1024=832

preload_value=time of OVF - number of tikes of (o.8125)=1024-832=192
*/
/*
timer_res=16 bits       timer_freq=10 MHz       desired_time=10 sec

time of one tik= 1/10000000=0.1 uS

time of OVF= 0.1 *2^(16)=6553.6 uS

number of OVF= 10000000/6553.6=1525.87890625;

number of tikes of (0.87890625)=0.87890625*65536=57600;

preload_value = 65536-57600=7936

ISR(ovf){
    static u16 counter=0;
    if(counter==1526){
        timer_counter=7936;
        //code{

        //}
        counter=0;
    }
}

*/
