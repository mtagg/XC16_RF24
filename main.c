/* C - Standard Headers*/
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





#ifdef MASTER_TRANSMITTER
int main(void) {
    //IOinit(); //not really necessary unless interrupts are required, this might be able to be done in nRF24.c
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