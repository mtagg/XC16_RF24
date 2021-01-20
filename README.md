
# XC16_RF24
\n
#/* README IS A WORK IN PROGRESS */\n


#/* How to use this library */ \n
*
   no idea right now :p
*
#/*Files used for testing purposes*/\n
*   main.c
*   IO.c
*   IO.h
*
*
#/*Files to be used for general library/firmware*/\n
*    SPI.h
*    SPI.c
*    nRF24.h
*    nRF24.c   - using 
*    CONFIG.h  -  contains comments that will define desired modes from the PIC24 device, ie: master-recieve, master-transmit, or slave configurations(only used for SPI) 
*    delay.c   -  used within nRF24.c to allow wait times after packets are sent/received, or after adjusting register settings 
*    delay.h   
*    nRF24L01.h - container for all macros(for register addresses or instruction set) found on the nRF24L0(1) data sheet (also found within this repository for reference)
#
