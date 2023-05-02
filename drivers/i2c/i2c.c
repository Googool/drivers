/*
 * File: i2c.c
 * Author: Ask Marius Lysgaard
 * Created on May 2, 2023, 9:32 AM
 */

#include <xc.h>
#include <stdint.h>

// Defining I2C communication parameters
#define I2C_SPEED 100000
#define I2C_SLAVE_ADDRESS 0x50

// Function to initialize the I2C module
void i2c_init() {
  SSPCON1 = 0b00101000;
  SSPCON2 = 0x00;
  SSPADD = (_XTAL_FREQ/(4*I2C_SPEED))-1;
  SSPSTAT = 0x80;
}

// Function to generate an I2C start condition
void i2c_start() {
  SSPCON2bits.SEN = 1;
  while(SSPCON2bits.PEN);
}

// Function to generate an I2C restart condition
void i2c_restart() {
  SSPCON2bits.RSEN = 1;
  while(SSPCON2bits.RSEN);
}

// Function to write data to the I2C bus
void i2c_write(uint8_t data) {
  SSPBUF = data;
  while(SSPSTATbits.BF);
  while(SSPCON2bits.ACKSTAT);
}

// Function to read data from the I2C bus
uint8_t i2c_read(uint8_t ack) {
  uint8_t data;
  SSPCON2bits.RCEN = 1;
  while(!SSPSTATbits.BF);
  data = SSPBUF;
  SSPCON2bits.ACKDT = ack;
  SSPCON2bits.ACKEN = 1;
  while(SSPCON2bits.ACKEN);
  return data;
}

// Function to write data to a specific register on the I2C slave device
