/* 
 * File:   i2c.h
 * Author: Ask Marius Lysgaard
 * Created on May 2, 2023, 12:26 PM
 */

#ifndef I2C_H
#define	I2C_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdint.h>
    
    void i2c_init(void);
    void i2c_start(void);
    void i2c_stop(void);
    void i2c_write(uint8_t data);
    uint8_t i2c_read_ack(void);
    uint8_t i2c_read_nack(void);
    void i2c_write_byte(uint8_t address, uint8_t data);
    uint8_t i2c_read_byte(uint8_t address);

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */