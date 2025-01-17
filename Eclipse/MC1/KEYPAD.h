/*
 * KEYPAD.h
 *
 *  Created on: Mar 22, 2024
 *      Author: Eng. Michael Samir Sawiris Naguib
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "GPIO.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Keypad configurations for number of rows and columns */
#define KEYPAD_NUM_COLS                   4
#define KEYPAD_NUM_ROWS                   4

/* Keypad Port Configurations */
#define KEYPAD_ROW_PORT                   PB
#define KEYPAD_FIRST_ROW_PIN              P0

#define KEYPAD_COL_PORT                   PB
#define KEYPAD_FIRST_COL_PIN              P4

/* Keypad button logic configurations */
#define KEYPAD_BUTTON_PRESSED            LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED           LOGIC_HIGH


uint8 KEYPAD(void);



#endif /* KEYPAD_H_ */
