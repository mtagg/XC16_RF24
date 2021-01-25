#include "nRF24.h"


char CE_REGISTER;
char CSN_REGISTER;
uint8_t CE_REGISTER_BIT;
uint8_t CSN_REGISTER_BIT;

void CE_Init(char Register_x, uint8_t bit_index){
    CE_REGISTER_BIT = bit_index;
    if (Register_x == 'a' || Register_x == 'A'){
        CE_REGISTER = 'A';

        switch (bit_index){
        case 0:
            TRISA = TRISA & 0xFFFE; //RA0 set to output (0)
            break;
        
        default:
            TRISA = TRISA & ~(0x0001 << (bit_index - 1));
            break;
        }

    }else if (Register_x == 'b' || Register_x == 'B'){
        CE_REGISTER = 'B';

        switch (bit_index){
        case 0:
            TRISB = TRISB & 0xFFFE; //RB0 set to output (0)
            break;

        default:
            TRISB = TRISB & ~(0x0001 << (bit_index-1));
            break;
        }
    }
}
void CSn_Init(char Register_x, uint8_t bit_index){
    CSN_REGISTER_BIT = bit_index;
    if (Register_x == 'a' || Register_x == 'A'){
        CSN_REGISTER = 'A';

        switch (bit_index)
        {
        case 0:
            TRISA = TRISA & 0xFFFE; //RA0 set to output (0)
            break;

        default:
            TRISA = TRISA & ~(0x0001 << (bit_index - 1));
            break;
        }
    }
    else if (Register_x == 'b' || Register_x == 'B'){
        CSN_REGISTER = 'B';

        switch (bit_index)
        {
        case 0:
            TRISB = TRISB & 0xFFFE; //RB0 set to output (0)
            break;

        default:
            TRISB = TRISB & ~(0x0001 << (bit_index - 1));
            break;
        }
    }
}
void WriteCSn(uint8_t setting){
    return;
}
void WriteCE(uint8_t setting){
    return;
}








void WriteRegister(uint8_t reg, uint8_t set){
    //to be adjusted to read more than 1 byte at a time using pointer to buffer and length variable
    WriteCSn(0);
    SPI_Comm(W_REGISTER | reg);
    SPI_Comm(set);
    WriteCSn(1);
    delay_ms(1);
    return;
}
uint8_t ReadRegister(uint8_t reg){
//to be adjusted to read more than 1 byte at a time using pointer to buffer and length variable
    uint8_t data;
    WriteCSn(0);
    SPI_Comm(R_REGISTER | reg);//starts transfer
    data = SPI_Comm(0xFF);
    WriteCSn(1);
    delay_ms(1);
    return data; // returns 8 bit settings recieved from desired register
}


void nRF_Transmitter_Init(){
    WriteCE(1); //chip enable
    delay_ms(1); // 1 ms delay      
// SET CONFIG REGISTER
    WriteRegister(CONFIG, 0b01111110); //transmit mode config
// SET SETUP_AW
    WriteRegister(SETUP_AW, 0b00000011); //receive address size - 5 bytes      
// SET AUTO RETRANSMISSION    
    WriteRegister(SETUP_RETR, 0b00000001);//enable re-transmit count up to 1 time  
// SET RF CHANNEL
    WriteRegister(RF_CH, 0b00000010);//set channel for nRF24L01
// SET RF_SETUP
    WriteRegister(RF_SETUP, 0b00000000);   
// SET STATUS
    WriteRegister(STATUS, 0b01110000); //reset status interrupt bits  
   /*------------------------------------------------------*/   
//default RX_ADDR_P0  : 0xE7E7E7E7E7
//default TX_ADDR     : 0xE7E7E7E7E7
   
//// SET RX_ADDR_P0 - only need one receive address for this project
//    WriteRegister(RX_ADDR_P0, 0xF1F1F1F1F1);

//// SET TX_ADDRESS
//    WriteRegister(TX_ADDR, 0x0123012301); 
//    transmit address only used for PTX devices
   /*------------------------------------------------------*/
  
// SET PAYLOAD WIDTH
   WriteRegister(RX_PW_P0, 2); // set P0 receive size to 2 bytes for PIC24 use
// FLUSH_TX FIFO BUFFER
    SPI_Comm(FLUSH_TX); // 16bit word will be read from LSBYTE -> MSBYTE, instruction will be first
// FLUSH_RX FIFO BUFFER
    SPI_Comm(FLUSH_RX); // 
    
    //finished initialization
    WriteCE(0);
    delay_ms(1);
    return;
}

void nRF_Receiver_Init(){
    WriteCE(1);     //chip enable
    delay_ms(1);     // 1 ms delay       
// SET CONFIG REGISTER
    WriteRegister(CONFIG, 0b01111111); // receiver mode config
// SET SETUP_AW
    WriteRegister(SETUP_AW, 0b00000011); //receive address size - 5 bytes      
// SET AUTO RETRANSMISSION    
    WriteRegister(SETUP_RETR, 0b00000001);//enable re-transmit count up to 1 time  
// SET RF CHANNEL
    WriteRegister(RF_CH, 0b00000010);//set channel for nRF24L01
// SET RF_SETUP
    WriteRegister(RF_SETUP, 0b00000000);    
// SET STATUS
   WriteRegister(STATUS, 0b01110000); //reset status interrupt bits
   
   /*------------------------------------------------------*/   
//default RX_ADDR_P0  : 0xE7E7E7E7E7
//default TX_ADDR     : 0xE7E7E7E7E7
   
//// SET RX_ADDR_P0 - only need one receive address for this project
//    WriteRegister(RX_ADDR_P0, 0xF1F1F1F1F1);

//// SET TX_ADDRESS
//    WriteRegister(TX_ADDR, 0x0123012301); 
//    transmit address only used for PTX devices
   /*------------------------------------------------------*/
    
// SET PAYLOAD WIDTH
   WriteRegister(RX_PW_P0, 2); // set P0 receive size to 2 bytes for PIC24 use
 
// FLUSH_TX FIFO BUFFER
    SPI_Comm(FLUSH_TX); // 16bit word will be read from LSBYTE -> MSBYTE, instruction will be first
// FLUSH_RX FIFO BUFFER
    SPI_Comm(FLUSH_RX); // 
 
    
    
    //finished initialization
    WriteCE(0);
    delay_ms(1);
    return;

}


uint8_t TransmitPayload (const uint8_t* buffer, uint8_t byte_length){ // used in Tx Mode
    //1. power up
    //2. config
    //3. delay for settling
    //4. write the payload
    
    uint8_t data_len = byte_length; //overflow protection ????
    //uint8_t unused_len ; //later to be used when considering dynamic payloads as to clear the buffer either way

//Flush Tx FIFO to avoid overflow problems
    WriteCSn(0);
    SPI_Comm(FLUSH_TX);
    WriteCSn(1);
    delay_ms(1);

    //Begin payload write if FIFO is empty as expected    
    uint8_t status = 0x00; // initialized to 0 for error checks
    if ((ReadRegister(STATUS) & 0x01) == 0x00){
        WriteCSn(0);
        status = SPI_Comm (W_TX_PAYLOAD);
        while (data_len--){SPI_Comm(*buffer);} //replace buffer with whatever comes in after transmit
        //clear FIFO buffer if dynamic payloads are enabled with a while loop to read blanks
//CE high for transmit signal
        WriteCSn(1);
        WriteCE(1); //start transmit
        delay_ms(1);
        WriteCE(0);
//buffer code and interrupt checks/resets for transmit
        delay_ms(500); //time buffer for transmit
        while((ReadRegister(STATUS) & 0x20) == 0x00 ); //loop until packet sent
        WriteRegister(STATUS,0b00111100); //clear transmit interrupts
    }
    return status; //returns the final status of the nRF module
}

uint8_t GetPayload(uint8_t* buffer, uint8_t byte_length){ // used in Rx Mode

    uint8_t data_len = byte_length; //overflow protection ????
    //uint8_t unused_len ; //later to be used when considering dynamic payloads as to clear the buffer either way
    
    WriteCSn(0);
    uint8_t status = SPI_Comm( R_RX_PAYLOAD);
    while (data_len--){ *buffer++ = SPI_Comm(0xFF);}
    //clear FIFO buffer if dynamic payloads are enabled with a while loop to read blanks
    WriteCSn(1);
    
    
    return status; 
    //returns whatever status bits were sent back after the instruction
}

void nRF_PowerDown(){

    SPI_Comm(CONFIG<<4 & 0b0000); //set PWR_UP bit low
}

