/* 
 * File:   CONFIG.h
 * Author: mmmta
 *
 * Created on January 16, 2021, 6:31 PM
 */

#ifndef CONFIG_H
#define	CONFIG_H

/* Standard & Hardware Library Files */

#include "xc.h"
#include "p24Fxxxx.h"
#include "p24F16KA101.h"

//default - to be REMOVED in final library configuration

// TRISBbits.TRISB4 = 0;
// TRISAbits.TRISA4 = 0;
// #define CE  LATBbits.LATB4
// #define CSn  LATAbits.LATA4

/*Uncomment the mode which applies to your hardware*/
#define MASTER_TRANSMITTER
//#define MASTER_RECEIVER
//#define SLAVE_TRANSMITTER
//#define SLAVE_RECEIVER

/* Pre-programming options - xc16 compiler*/
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
#pragma config FNOSC = LPFRC // internal CLK : 500 kHz

#endif	/* CONFIG_H */

