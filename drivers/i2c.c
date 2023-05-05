/*
 * File: i2c.c
 * Author: Ask Marius Lysgaard
 * Created on May 3, 2023, 15:01 PM
 */

#include "i2c.h"

#define I2C_SLAVE_ADDRESS 0x55
#define I2C_SLAVE_MASK 0x7F

typedef enum {
    SLAVE_NORMAL_DATA,
    SLAVE_DATA_ADDRESS
} SLAVE_WRITE_DATA_TYPE;