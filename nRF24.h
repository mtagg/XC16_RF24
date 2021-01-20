/* 
 * File:   nRF24.h
 * Author: mmmta
 *
 * Created on January 12, 2021, 9:16 AM
 */

#ifndef NRF24_H
#define	NRF24_H



#include <xc.h>
#include "CONFIG.h"
#include "nRF24L01.h"
#include "SPI.h"
#include "delay.h"


/*TODO*/
//Dynamic Payload within payload width functionality
//Power Up
//dynamic address setting&checking
//multiple pipeline settings
//dynamic payload width settings
//flush RX and flush TX


//void setCE(bit);
///* sets Chip Enable register pin used to control slave*/
//void setCSn(byte
void WriteRegister(uint8_t reg, uint8_t set);
/*method used to write to a register within nRF module
 @param reg accepts an 8 bit address
 @param set accepts the bit array of desired settings within that register
 */
uint8_t ReadRegister(uint8_t reg);
/*method used to write to a register within nRF module
 @param reg accepts an 8 bit address
 @param set accepts the bit array of register settings to fetch
 RETURNS: 16bit word containing the settings of the desired register "reg"
 */

void nRF_Transmitter_Init();
/*Collection of register settings used at start-up
 * 
 */

void nRF_Receiver_Init();
/*Collection of register settings used at start-up
 * 
 */
    
uint8_t TransmitPayload (const uint8_t* buffer, uint8_t byte_length);
/* general method for transmitting data via SPI to slave nRF module over 2.4GHz
 * @param buffer will hold the payload as it is received byte by byte
 * @param byte_length is the number of bytes that is being requested from payload
 * 
 */
//void ReadPayload ( uint8_t* buff, uint8_t byte_len);
///* Method will take a buffer of specified length and make calls to GetPayload()
// * until it returns with status flag bits set, in which case, it will clear flags
// * and return.
// * @param buff will hold the payload as it is received byte by byte
// * @param byte_len is the number of bytes that is being requested from payload
// *
// */
uint8_t GetPayload(uint8_t* buffer, uint8_t byte_length);
/* Method to read one payload from  RX FIFO buffer when feedback is expected from slave
 * @param buffer will hold the payload as it is received byte by byte
 * @param byte_length is the number of bytes that is being requested from payload
 * RETURNS 8 bit status bits
 */


void nRF_PowerDown();
/* method will shut down nRF24L01 module until one of the two Init() functions is called again 
 * and the module wakes up again
 */



#endif	/* NRF24_H */

