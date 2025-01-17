/*
 * KEYPAD.c
 *
 *  Created on: Apr 13, 2024
 *      Author: Eng. Michael Samir Sawiris Naguib
 */



#include "KEYPAD.h"
#include <util/delay.h>
static uint8 K_P_4X4(uint8 button_number);


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

uint8 KEYPAD(void)
{
	uint8 col,row;
	DDR(KEYPAD_ROW_PORT, KEYPAD_FIRST_ROW_PIN, INPUT);
	DDR(KEYPAD_ROW_PORT, KEYPAD_FIRST_ROW_PIN+1, INPUT);
	DDR(KEYPAD_ROW_PORT, KEYPAD_FIRST_ROW_PIN+2, INPUT);
	DDR(KEYPAD_ROW_PORT, KEYPAD_FIRST_ROW_PIN+3, INPUT);

	DDR(KEYPAD_COL_PORT, KEYPAD_FIRST_COL_PIN, INPUT);
	DDR(KEYPAD_COL_PORT, KEYPAD_FIRST_COL_PIN+1, INPUT);
	DDR(KEYPAD_COL_PORT, KEYPAD_FIRST_COL_PIN+2, INPUT);
	DDR(KEYPAD_COL_PORT, KEYPAD_FIRST_COL_PIN+3, INPUT);

	while(1)
	{
		for(row=0 ; row<KEYPAD_NUM_ROWS ; row++) /* loop for rows */
		{
			/*
			 * Each time setup the direction for all keypad port as input pins,
			 * except this row will be output pin
			 */
			DDR(KEYPAD_ROW_PORT,KEYPAD_FIRST_ROW_PIN+row,OUTPUT);

			/* Set/Clear the row output pin */
			PORT(KEYPAD_ROW_PORT, KEYPAD_FIRST_ROW_PIN+row, KEYPAD_BUTTON_PRESSED);

			for(col=0 ; col<KEYPAD_NUM_COLS ; col++) /* loop for columns */
			{
				/* Check if the switch is pressed in this column */
				if(PIN(KEYPAD_COL_PORT,KEYPAD_FIRST_COL_PIN+col) == KEYPAD_BUTTON_PRESSED)
				{

							  return  K_P_4X4((row*KEYPAD_NUM_COLS)+col+1);
				}
			}
			DDR(KEYPAD_ROW_PORT,(KEYPAD_FIRST_ROW_PIN)+row,INPUT);
			_delay_ms(5); /* Add small delay to fix CPU load issue in proteus */
		}
	}
}

static uint8 K_P_4X4(uint8 button_number)
{
	uint8 keypad_button = 0;
	switch(button_number)
	{
		case 1: keypad_button = 7;
				break;
		case 2: keypad_button = 8;
				break;
		case 3: keypad_button = 9;
				break;
		case 4: keypad_button = '%'; // ASCII Code of %
				break;
		case 5: keypad_button = 4;
				break;
		case 6: keypad_button = 5;
				break;
		case 7: keypad_button = 6;
				break;
		case 8: keypad_button = '*'; /* ASCII Code of '*' */
				break;
		case 9: keypad_button = 1;
				break;
		case 10: keypad_button = 2;
				break;
		case 11: keypad_button = 3;
				break;
		case 12: keypad_button = '-'; /* ASCII Code of '-' */
				break;
		case 13: keypad_button = 13;  /* ASCII of Enter */
				break;
		case 14: keypad_button = 0;
				break;
		case 15: keypad_button = '='; /* ASCII Code of '=' */
				break;
		case 16: keypad_button = '+'; /* ASCII Code of '+' */
				break;
		default: keypad_button = button_number;
				break;
	}
	return keypad_button;
}
