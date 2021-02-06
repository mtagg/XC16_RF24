//#include <xc.h>
//#include <p24F16KA101.h>
#include "delay.h"

void T2Init(){
    
    T2CONbits.T32 = 0;          //t2 is a 16 bit timer
    T2CONbits.TON = 0;          //timer off initially
    T2CONbits.TCKPS = 0b01;     //1:8 prescalar for timer (@8MHz clock)
    T2CONbits.TCS = 0;          //use system clock for timer
    T2CONbits.TSIDL = 0;        //timer used in idle
    IEC0bits.T2IE = 0;          //disable t2 interrupts initially
    IPC1bits.T2IP = 0b111;      //t2 interrupt priority 7
    
    
    return;
}
void delay_ms(unsigned int ms){
    
    PR2 = 16 * 2 * ms;
    TMR2 = 0;           //restart counter buffer
    IFS0bits.T2IF = 0;  //reset IF 
    IEC0bits.T2IE = 1;  //enable t2 interrupts
    T2CONbits.TON = 1;  //turn timer on
    Idle();
    
    return;
}

void __attribute__ ((interrupt, no_auto_psv)) _T2Interrupt(){
    if (IFS0bits.T2IF == 1){
        T2CONbits.TON = 0; //stop timer
        IEC0bits.T2IE = 0; //disable t2 interrupts
    }
    return;
}
