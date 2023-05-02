/*
 * File:   i2c.c
 * Author: Ask Marius Lysgaard
 * Created on May 2, 2023, 12:26 PM
 */

#include "i2c.h"

#define SCL_PIN TRISC3 // SCL pin (RC3)
#define SDA_PIN TRISC4 // SDA pin (RC4)

#define I2C_FREQUENCY 100000UL

void i2c_init(void) {
    SSPCON1 = 0b00101000; // Enable
    SSPCON2 = 0;
    SSPADD = (_XTAL_FREQ / (4 * I2C_FREQUENCY)) - 1;
    SCL_PIN = 1;
    SDA_PIN = 1;
}

void i2c_start(void) {
    SSPCON2bits.SEN = 1;
    while (SSPCON2bits.SEN);
}

void i2c_stop(void) {
    SSPCON2bits.PEN = 1;
    while (SSPCON2bits.PEN);
}

void i2c_write(uint8_t data) {
    SSPBUF = data;
    while (SSPSTATbits.BF);
}

uint8_t i2c_read_ack(void) {
    SSPCON2bits.RCEN = 1;
    while (!SSPSTATbits.BF);
    uint8_t data = SSPBUF;
    SSPCON2bits.ACKDT = 0;
    SSPCON2bits.ACKEN = 1;
    while (SSPCON2bits.ACKEN);
    return data;
}

uint8_t i2c_read_nack(void) {
    SSPCON2bits.RCEN = 1;
    while (!SSPSTATbits.BF);
    uint8_t data = SSPBUF;
    SSPCON2bits.ACKDT = 1;
    SSPCON2bits.ACKEN = 1;
    while (SSPCON2bits.ACKEN);
    return data;
}

void i2c_write_byte(uint8_t address, uint8_t data) {
    i2c_start();
    i2c_write((address << 1) | 0);
    i2c_write(data);
    i2c_stop();
}

uint8_t i2c_read_byte(uint8_t address) {
    i2c_start();
    i2c_write((address << 1) | 1);
    uint8_t data = i2c_read_nack();
    i2c_stop();
    return data;
}