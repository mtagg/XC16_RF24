/* 
 * File:   delay.h
 * Author: mmmta
 *
 * Created on January 5, 2021, 10:06 AM
 */

#ifndef DELAY_H
#define	DELAY_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <xc.h>
void T2Init();
void delay_ms(unsigned int ms);
void __attribute__ ((interrupt, no_auto_psv)) _T2Interrupt();

#ifdef	__cplusplus
}
#endif

#endif	/* DELAY_H */

