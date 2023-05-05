/*
 * File: delay.h
 * Author: Ask Marius Lysgaard
 * Created on May 5, 2023, 10:02 PM
 */

#ifndef I2C_H
#define	I2C_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
    
void delay_init(void);
void delay_us(unsigned int us);
void delay_ms(unsigned int ms);

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */