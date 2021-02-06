/* 
 * File:   CONFIG.h
 * Author: mmmta
 *
 * Created on January 16, 2021, 6:31 PM
 */

#ifndef RF_CONFIG_H
#define	RF_CONFIG_H

///* Standard & Hardware Library Files */
//
#include <xc.h>
#include <p24Fxxxx.h>
#include <p24F16KA101.h>
//
///* C - Standard Headers*/
#include "stdio.h"
////#include "stdlib.h"
////#include "string.h"
////#include "math.h"
////#include "errno.h"

///*Library required headers*/
#include "delay.h"
#include "IO.h"
#include "nRF24L01.h"
#include "SPI.h"
#include "nRF24.h"

/* Pre-programming options - xc16 compiler*/

//#pragma config IESO = OFF    // 2 Speed Startup disabled 
//#pragma config FNOSC = LPFRC  // CLK = 500 kHz 
//#pragma config FCKSM = CSECMD // Clock switching is enabled, clock monitor off  
//#pragma config SOSCSEL = SOSCLP // Secondary oscillator for Low Power Operation 
//#pragma config POSCFREQ = MS  //Primary Oscillator/External clk freq betwn  100khz - 8mhz
//#pragma config OSCIOFNC = ON  //CLKO output disabled on pin 8, use as IO.  
//#pragma config POSCMOD = NONE  // Primary oscillator mode is disabled
//#pragma config POSCMOD = HS //HS oscillator mode enabled

#pragma config FNOSC = LPFRC // internal CLK : 500 kHz


/*Uncomment the mode which applies to your hardware*/
#define MASTER_TRANSMITTER
//#define MASTER_RECEIVER
//#define SLAVE_TRANSMITTER
//#define SLAVE_RECEIVER


#endif	/* RF_CONFIG_H */

