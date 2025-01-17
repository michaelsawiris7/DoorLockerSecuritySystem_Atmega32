/*
 * LCD.h
 *
 *  Created on: Mar 22, 2024
 *      Author: Eng. Michael Samir Sawiris Naguib
 */

#ifndef LCD_H_
#define LCD_H_


#include "GPIO.h"
#include <stdlib.h>
#include <util/delay.h>


#define FOUR_BITS_MODE  4
#define EIGHT_BITS_MODE 8
/*
 * CONFIGURATIONG OF LCD
 *********************************************************/
#define LCD_TYPE  FOUR_BITS_MODE
//********************************************************
#define LCD_PORT  PA
//********************************************************
#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define LCD_SET_CURSOR_LOCATION              0x80

/*********************************************/
#define RS_PORT  PC
#define RS_PIN   P6
#define EN_PORT  PC
#define EN_PIN   P7
/*********************************************/
#define	D4_PORT   PA
#define D4_PIN    P4

#define	D5_PORT   PA
#define D5_PIN    P5


#define	D6_PORT   PA
#define D6_PIN    P6

#define	D7_PORT   PA
#define D7_PIN    P7
/***********************************************/

void LCD_INIT(void);

void LCD_COMMAND(uint8 command);


void LCD_CHAR(uint8 charachter);

void LCD_STR(const char *ptr);

void LCD_CLEAR(void);
void LCD_INT(int data);

void LCD_moveCursor(uint8 row,uint8 col);
void LCD_STR_R_C(uint8 row,uint8 col,const char *txt);


#endif /* LCD_H_ */
