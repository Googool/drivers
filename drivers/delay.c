/*
 * File: delay.c
 * Author: Ask Marius Lysgaard
 * Created on May 5, 2023, 10:02 PM
 */

#include <xc.h>

void delay_init(void) {
    T2CONbits.T2CKPS = 0b10; // Set prescaler to 1:16
    T2CONbits.T2OUTPS = 0b0000; // Set postscaler to 1:1
    PR2 = 249; // Set period register for 1 microsecond
    T2CONbits.TMR2ON = 1; // Enable Timer 2
}

void delay_us(unsigned int us) {
    unsigned int i;
    TMR2 = 0; // Reset Timer 2
    while (us--) {
        while (!PIR1bits.TMR2IF); // Wait for Timer 2 overflow
        PIR1bits.TMR2IF = 0; // Reset Timer 2 overflow flag
    }
}

void delay_ms(unsigned int ms) {
    unsigned int i;
    TMR2 = 0; // Reset Timer 2
    while (ms--) {
        for (i = 0; i < 1000; i++) {
            while (!PIR1bits.TMR2IF); // Wait for Timer 2 overflow
            PIR1bits.TMR2IF = 0; // Reset Timer 2 overflow flag
        }
    }
}