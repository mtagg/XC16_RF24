#include <xc.h>
#include <p24Fxxxx.h>
#include <p24F16KA101.h>
#include "RF_CONFIG.h"


#ifdef MASTER_TRANSMITTER
int main(void) {
    T2Init();
    MasterInit();
    nRF_Transmitter_Init();

    CSn_Init('a', 4);
    CE_Init('b', 4);

    while (1){    
        delay_ms(1000);
        WriteCE(1);
        WriteCSn(1);
        delay_ms(1000);
        WriteCE(0);
        WriteCSn(0);
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