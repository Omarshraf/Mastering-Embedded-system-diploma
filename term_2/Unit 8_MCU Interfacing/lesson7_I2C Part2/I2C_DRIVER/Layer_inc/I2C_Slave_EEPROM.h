/*
 * I2C_Slave_EEPROM.h
 *
 *  Created on: Aug 11, 2023
 *      Author: Omar
 */

#ifndef I2C_SLAVE_EEPROM_H_
#define I2C_SLAVE_EEPROM_H_

#include "Stm32_F103C6_I2C_drivers.h"

//E2PROM is an i2c slave
//idle mode : device is in high-impedance state and waits for data
//Master Transmitter mode: the device transmits data to a slave receiver
//master Receiver mode: the divice receives data from a slave transmitter

#define EEPROM_Slave_address			0x2A

void eeprom_init(void);
unsigned char eeprom_write_Nbytes(unsigned int Memory_address , unsigned char* bytes, uint8_t Data_Length);
unsigned char eeprom_read_byte(unsigned int address ,uint8_t dataOut , uint8_t dataLen);




#endif /* I2C_SLAVE_EEPROM_H_ */
