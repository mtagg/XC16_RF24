
 
#ifndef SPI_H
#define	SPI_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "CONFIG.h"
#include "nRF24L01.h"
#include "nRF24.h"
#include "delay.h"





///* sets Chip Select (n) register pin used to start data transfer to nRF module*/
void MasterInit(); 
//used in MCU master-mode & transceiver slave - mode
void SlaveInit(); 
// unused for MCU master-mode
uint8_t SPI_Comm(uint8_t word); 
/*Master communications via SPI
 * @param word accepts 1 byte word to transmit
 * RETURNS: 1 byte received from SPI1BUF after byte transfer
 */


void __attribute__ ((interrupt, no_auto_psv)) _SPI1Interrupt(); 


#endif	/* SPI_H */

