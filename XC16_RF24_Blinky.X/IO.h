
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef IO_H
#define	IO_H

#include <xc.h>
#include <p24F16KA101.h>

void IOinit();
void __attribute__ ((interrupt, no_auto_psv))_CNInterrupt();


#endif	/* SPI_H */

