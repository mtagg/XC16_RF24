/* Standard & Hardware Library Files */

#include "xc.h"
#include "p24Fxxxx.h"
#include "p24F16KA101.h"
#include "stdio.h"

//#include "stdlib.h"
//#include "string.h"
//#include "math.h"
//#include "errno.h"

/* SPI & nRF Firmware Files */

#include "CONFIG.h"
#include "delay.h"
#include "IO.h"
#include "nRF24L01.h"
#include "SPI.h"
#include "nRF24.h"

/* User Files */


/* Pre-programming - xc16 compiler*/
/*
#pragma config IESO = OFF    // 2 Speed Startup disabled 
#pragma config FNOSC = LPFRC  // CLK = 500 kHz 
#pragma config FCKSM = CSECMD // Clock switching is enabled, clock monitor off  
#pragma config SOSCSEL = SOSCLP // Secondary oscillator for Low Power Operation 
#pragma config POSCFREQ = MS  //Primary Oscillator/External clk freq betwn  100khz - 8mhz
#pragma config OSCIOFNC = ON  //CLKO output disabled on pin 8, use as IO.  
#pragma config POSCMOD = NONE  // Primary oscillator mode is disabled
#pragma config POSCMOD = HS //HS oscillator mode enabled
*/
#pragma config FNOSC = LPFRC  // CLK = 500 kHz 

/* These are already automatically defined in the p24f16 hardware library*/
/*
#define Nop() {__asm__ volatile ("nop");}
//#define ClrWdt() {__asm__ volatile ("clrwdt");}
#define Sleep() {__asm__ volatile ("pwrsav #0");}   //Sleep() - put MCU in sleep mode - CPU and some peripherals off
#define Idle() {__asm__ volatile ("pwrsav #1");}    //Idle() - put MCU in idle mode - only CPU off
//#define dsen() {__asm__ volatile ("BSET DSCON, #15");} //
*/


#ifdef MASTER_TRANSMITTER
int main(void) {
    IOinit();
    T2Init();
    MasterInit();
    nRF_Transmitter_Init();

    delay_ms(5000);
    
    while (1){        
    }
    return 0;
}
#endif

#ifdef MASTER_RECEIVER
#endif
#ifdef SLAVE_TRANSMITTER
#endif
#ifdef SLAVE_RECEIVER
int main(void) {
    IOinit();
    T2Init();
    SlaveInit();

    while (1){    
        Idle(); //will be interrupted when data is available to be read        
    }
    return 0;
}
#endif