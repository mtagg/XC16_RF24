/* 
 * File:   CONFIG.h
 * Author: mmmta
 *
 * Created on January 16, 2021, 6:31 PM
 */

#ifndef CONFIG_H
#define	CONFIG_H


#define CE  LATBbits.LATB4
#define CSN LATAbits.LATA4    
    

/*Uncomment the mode which applies to your hardware*/
#define MASTER_TRANSMITTER
//#define MASTER_RECEIVER
//#define SLAVE_TRANSMITTER
//#define SLAVE_RECEIVER


#endif	/* CONFIG_H */

