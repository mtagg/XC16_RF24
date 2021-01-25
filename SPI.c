#include "SPI.h"

void MasterInit(){ //8-bit, framed off
//    TRISBbits.TRISB15 = 0;       // SS1 digital out
//    TRISBbits.TRISB12 = 0;       //SCLK digital out     

//setup SPI interrupts
    IEC0bits.SPI1IE = 1;       //  enable interrupts
    IFS0bits.SPI1IF = 0;       //  clear SPI interrupt flag
    IPC2bits.SPI1IP = 0b101;   //  SPI interrupt priority 5
    
//SPI status init
    SPI1STATbits.SPIROV = 0;   //  clear buff register overflow flag  
    SPI1STATbits.SPISIDL = 0;  //  continue SPI op in idle
    SPI1STATbits.SISEL = 0b101;//  101: interrupt when last bit is shifted out of SPISR - transmit is complete

//SPI1CON1 - SPI Config
    
    SPI1CON1bits.DISSCK = 0;   //  internal SPI clock enabled (SCK1)
    SPI1CON1bits.DISSDO = 0;   //  Digi out used => 0, unused => 1
    SPI1CON1bits.MODE16 = 0;   //  16 bit words, 8-bit => 0
    SPI1CON1bits.SMP = 1;      //  data sampled end of data output time
    SPI1CON1bits.CKE = 1;      //  1: serial out data changes on active->idle clock (see CKP)
    SPI1CON1bits.SSEN = 1;     //  master mode: pin controlled by port function
    SPI1CON1bits.CKP = 0;      //  idle state = 0, clock active = 1    
    
    SPI1CON1bits.MSTEN = 1;    //  master mode enabled (For Rx AND Tx)
    
    SPI1CON1bits.SPRE = 0b000; //  secondary clock prescale 8:1
    SPI1CON1bits.PPRE = 0b00;  //  primary clock prescale   64:1
    
//SPI1CON2 - framed support
    SPI1CON2bits.FRMEN = 0;    //  framed SPI1 support ENABLED 
//    SPI1CON2bits.SPIFPOL = 1;  //  0: frame sync pulse active low
//    SPI1CON2bits.SPIFE = 1;    //  frame sync pulse signals first bit clock
//    SPI1CON2bits.SPIFSD = 0;   //  frame sync pulse output (master)
//    
//SPI1CON2 - Enhanced buffer mode    
    SPI1CON2bits.SPIBEN = 1;   //  enable enhanced buffer mode
    SPI1STATbits.SPIEN = 1;    //  set for SPI enable
            
    //
//initialize nRF24L01 registers for Rx/Tx
    //
    return;
}

void SlaveInit(){//8-bit, framed off
//       TRISBbits.TRISB15 = 1;       // SS1 digital in
//       TRISBbits.TRISB12 = 1;       //SCLK digital in
//setup SPI interrupts
    IEC0bits.SPI1IE = 1;       //  enable interrupts
    IFS0bits.SPI1IF = 0;       //  clear SPI interrupt flag
    IPC2bits.SPI1IP = 0b111;   //  SPI interrupt priority 7
    
//SPI status init
    SPI1STATbits.SPIROV = 0;   //  clear buff register overflow flag  
    SPI1STATbits.SPISIDL = 0;  //  continue SPI op in idle
    SPI1STATbits.SPIEN = 1;    //  enable SPI
    SPI1STATbits.SISEL = 0b001;//  001: interrupt when data available in receive buffer

//SPI1CON1 - SPI Config   
    SPI1CON1bits.DISSCK = 0;   //  internal SPI clock enabled (SCK1)
    SPI1CON1bits.DISSDO = 0;   //  SDO1: used => 0, unused => 1
    SPI1CON1bits.MODE16 = 0;   //  16 bit words, 8-bit => 0
    SPI1CON1bits.SMP = 0;      //  cleared for slave mode 
    SPI1CON1bits.CKE = 0;      //  0: serial out data changes on active->idle clock (see CKP)
    SPI1CON1bits.SSEN = 0;     //  SS1 pin controlled by port function
    SPI1CON1bits.CKP = 1;      //  idle state = 1, clock active = 0    
    
    SPI1CON1bits.MSTEN = 0;    //  master mode disabled (For Rx AND Tx)
    
    SPI1CON1bits.SPRE = 0b000; //  secondary clock prescale 8:1
    SPI1CON1bits.PPRE = 0b00;  //  primary clock prescale   64:1
    
//SPI1CON2 - framed support OFF
    SPI1CON2bits.FRMEN = 0;    //  framed SPI1 support ENABLED 
//    SPI1CON2bits.SPIFSD = 1;   //  frame sync pulse input (slave)
//    SPI1CON2bits.SPIFPOL = 1;  //  0: frame sync pulse active low
//    SPI1CON2bits.SPIFE = 1;    //  frame sync pulse signals first bit clock
//    
    
//SPI1CON2 - Enhanced buffer mode    
    SPI1CON2bits.SPIBEN = 1;   //  enable enhanced buffer mode
            
    //
//initialize nRF24L01 registers for Rx/Tx
    //
    return;
}

uint8_t SPI_Comm(uint8_t word){ //used for master transmit mode
//clear flags   
    IFS0bits.SPI1IF = 0;                //  clear SPI interrupt flag
    SPI1STATbits.SPIROV = 0;            //  clear buff register overflow flag
    SPI1BUF;                            // dummy read to ensure buffer is cleared
    
//write to buffer  & transmit  
    if (SPI1STATbits.SPITBF == 0){      //  room in buffer is available to write
        SPI1BUF = word;                 //  write data to be transmitted    
        while (SPI1STATbits.SPITBF == 1); //move buffer data into shift register                                      
    }
    
    delay_ms(1);
    return SPI1BUF;
}

#ifdef MASTER_TRANSMITTER
void __attribute__ ((interrupt, no_auto_psv)) _SPI1Interrupt(){
    if (IFS0bits.SPI1IF == 1) {
        IFS0bits.SPF1IF = 0;  //reset IF & return
    }
    return;
}
#endif

#ifdef SLAVE_RECEIVER //made for LED blink 
void __attribute__ ((interrupt, no_auto_psv)) _SPI1Interrupt(){
    if (IFS0bits.SPI1IF == 1) {
        unsigned int temp;
        while(!SPI1STATbits.SRXMPT){ 
            temp = SPI1BUF;        //clears recieved buffer value
            
            if (temp == 0xFF){             //performs a read on the spi buffer
                LATBbits.LATB4 = 1;             //set LED if recievced buffer is high
            }else if(temp == 0x00){
              LATBbits.LATB4 = 0;           //else turn LED off
            }
        }
        IFS0bits.SPF1IF = 0;                //reset IF
    }
    return; //back to idle following the slave read
}

#endif
