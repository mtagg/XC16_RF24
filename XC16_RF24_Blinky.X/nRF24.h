/* 
 * File:   nRF24.h
 * Author: mmmta
 *
 * Created on January 12, 2021, 9:16 AM
 */

#ifndef NRF24_H
#define	NRF24_H
#include <xc.h>
#include <p24F16KA101.h>

#include "nRF24L01.h"
#include "SPI.h"
#include "delay.h"


/****************************************************************/
/****************************************************************/
/*TODO
1.
  //Power Up
  //flush RX and flush TX
2.
  //dynamic address setting&checking
  //dynamic payload width settings
3. 
  //Dynamic Payload within payload width functionality
  //multiple pipeline settings

 END TODO */
/****************************************************************/
/****************************************************************/

/* sets Chip Enable register pin used to control slave
 * @param Register_x : either 'a' or 'b' ('A' or 'B') for TRISA or TRISB
 * @param bit_index : takes bit-index (as int) from said register ie: 0:15 
 * 
 */
void CE_Init(char Register_x, uint8_t bit_index);

/* sets Chip Select (n) register pin used to start data transfer to nRF module
 * @param Register_x : either 'a' or 'b' ('A' or 'B') for TRISA or TRISB
 * @param bit_index : takes bit-index (as int) from said register ie: 0:15 
 */
void CSn_Init(char Register_x, uint8_t bit_index);

/* writes to CSn
*  @param setting : bit to set the CSn pin to 
*/
void WriteCSn(uint8_t setting);

/* writes to CE
*  @param setting : bit to set the CE pin to
*/
void WriteCE(uint8_t setting);

/*method used to write to a register within nRF module
 @param reg accepts an 8 bit address
 @param set accepts the bit array of desired settings within that register
 */
void WriteRegister(uint8_t reg, uint8_t set);

/*method used to read to a register within nRF module
 @param reg accepts an 8 bit address
 @param set accepts the bit array of register settings to fetch
 RETURNS: 16bit word containing the settings of the desired register "reg"
 */
uint8_t ReadRegister(uint8_t reg);

/*Collection of register settings used at start-up
 * 
 */
void nRF_Transmitter_Init();

/*Collection of register settings used at start-up
 * 
 */
void nRF_Receiver_Init();

  /* general method for transmitting data via SPI to slave nRF module over 2.4GHz
 * @param buffer will hold the payload as it is received byte by byte
 * @param byte_length is the number of bytes that is being requested from payload
 * 
 */  
uint8_t TransmitPayload (const uint8_t* buffer, uint8_t byte_length);


/* Method to read one payload from  RX FIFO buffer when feedback is expected from slave
 * @param buffer will hold the payload as it is received byte by byte
 * @param byte_length is the number of bytes that is being requested from payload
 * RETURNS 8 bit status bits
 */
uint8_t GetPayload(uint8_t* buffer, uint8_t byte_length);


/* method will shut down nRF24L01 module until one of the two Init() functions is called again 
 * and the module wakes up again
 */
void nRF_PowerDown();




#endif	/* NRF24_H */

