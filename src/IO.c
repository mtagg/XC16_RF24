//#include <xc.h>
//#include <p24F16KA101.h>

#include "IO.h"


void IOinit(){
    
    //Initialize pins: 
    AD1PCFG = 0xFFFF;             // all IOs set digital
//    TRISBbits.TRISB4 = 0;        // pin9  - RB4 digital output for CE
//    TRISAbits.TRISA4 = 1;        // pin10 - RA4 digital input for IRQ
//    TRISBbits.TRISB13 = 0;       // SD01 digital out   
//    TRISBbits.TRISB14 = 1;       // SDI1 digital in
            
    //setup IRQ interrupt
    IEC1bits.CNIE = 1;        // enable CN interrupts
    IPC4bits.CNIP = 0b110;    // CN interrupt priotrity 6
    IFS1bits.CNIF = 0;        // clear flag
   // CNEN1bits.CN0IE = 1;      // setup RA4 as a CN interrupt
    
    
}


void __attribute__ ((interrupt, no_auto_psv)) _CNInterrupt(){
    if (IFS1bits.CNIF == 1) {
        IFS1bits.CNIF = 0;      //reset IF
    }

}
