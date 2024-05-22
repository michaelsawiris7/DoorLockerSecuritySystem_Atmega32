/*
 * EEPROM.h
 *
 *  Created on: Mar 22, 2024
 *      Author: Admin
 */

#ifndef EEPROM_H_
#define EEPROM_H_

#include "STANDS.h"
#include "I2C.h"
#include <util/delay.h>
#define EEPROM_ADDRESS			  0x0311

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define ERROR 0
#define SUCCESS 1

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data);
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data);



#endif /* EEPROM_H_ */
