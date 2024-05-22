/*
 * LCD.c
 *
 *  Created on: Apr 13, 2024
 *      Author: Eng. Michael Samir Sawiris Naguib
 */



#include "LCD.h"
//===================================================================
// LCD INITIALIZATION
void LCD_INIT(void)
{
			DDR(RS_PORT,RS_PIN,OUTPUT);            //RS PIN     ---> OUTPUT
			DDR(EN_PORT,EN_PIN,OUTPUT);            //ENABLE PIN ---> OUTPUT
			_delay_ms(20);
#if (LCD_TYPE==FOUR_BITS_MODE)

			DDR(D4_PORT,D4_PIN,OUTPUT);
			DDR(D5_PORT,D5_PIN,OUTPUT);
			DDR(D6_PORT,D6_PIN,OUTPUT);
			DDR(D7_PORT,D7_PIN,OUTPUT);

			LCD_COMMAND(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
			LCD_COMMAND(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);
			LCD_COMMAND(LCD_TWO_LINES_FOUR_BITS_MODE);


#elif (LCD_TYPE ==EIGHT_BITS_MODE)

			DDR(LCD_PORT,total,OUTPUT);
			LCD_COMMAND(LCD_TWO_LINES_EIGHT_BITS_MODE);
#endif
			LCD_COMMAND(LCD_CURSOR_OFF);
			LCD_COMMAND(LCD_CLEAR_COMMAND);
}
// SEND COMMAND
void LCD_COMMAND(uint8 command)
{
			PORT(RS_PORT,RS_PIN,OFF);
			_delay_ms(1);
			PORT(EN_PORT,EN_PIN,ON);
			_delay_ms(1);

#if (LCD_TYPE==FOUR_BITS_MODE)

			PORT(D4_PORT,D4_PIN,GET_BIT(command,4) );
			PORT(D5_PORT,D5_PIN,GET_BIT(command,5) );
			PORT(D6_PORT,D6_PIN,GET_BIT(command,6) );
			PORT(D7_PORT,D7_PIN,GET_BIT(command,7) );

			_delay_ms(1);
			PORT(EN_PORT,EN_PIN,OFF);
			_delay_ms(1);
			PORT(EN_PORT,EN_PIN,ON);

			_delay_ms(1);

			PORT(D4_PORT,D4_PIN,GET_BIT(command,0) );
			PORT(D5_PORT,D5_PIN,GET_BIT(command,1) );
			PORT(D6_PORT,D6_PIN,GET_BIT(command,2) );
			PORT(D7_PORT,D7_PIN,GET_BIT(command,3) );

			_delay_ms(1);
			PORT(EN_PORT,EN_PIN,OFF);
			_delay_ms(1);

#elif (LCD_TYPE==EIGHT_BITS_MODE)


			PORT(LCD_PORT,total,command);
			_delay_ms(1);
			PORT(EN_PORT,EN_PIN,OFF);
			_delay_ms(1);
#endif
}
//===================================================================
// SEND CHARACHTER
void LCD_CHAR(uint8 charachter)
{

		PORT(RS_PORT,RS_PIN,ON);
		_delay_ms(1);
		PORT(EN_PORT,EN_PIN,ON);
		_delay_ms(1);

#if (LCD_TYPE==FOUR_BITS_MODE)
		PORT(D4_PORT,D4_PIN,GET_BIT(charachter,4) );
		PORT(D5_PORT,D5_PIN,GET_BIT(charachter,5) );
		PORT(D6_PORT,D6_PIN,GET_BIT(charachter,6) );
		PORT(D7_PORT,D7_PIN,GET_BIT(charachter,7) );

		_delay_ms(1);
		PORT(EN_PORT,EN_PIN,OFF);
		_delay_ms(1);
		PORT(EN_PORT,EN_PIN,ON);

		_delay_ms(1);


		PORT(D4_PORT,D4_PIN,GET_BIT(charachter,0) );
		PORT(D5_PORT,D5_PIN,GET_BIT(charachter,1) );
		PORT(D6_PORT,D6_PIN,GET_BIT(charachter,2) );
		PORT(D7_PORT,D7_PIN,GET_BIT(charachter,3) );

		_delay_ms(1);
		PORT(EN_PORT,EN_PIN,OFF);
		_delay_ms(1);

#elif (LCD_TYPE==EIGHT_BITS_MODE)

			PORT(LCD_PORT,total,charachter);
			_delay_ms(1);
			PORT(EN_PORT,EN_PIN,OFF);
			_delay_ms(1);

#endif
}

//===================================================================
// SEND STRING
void LCD_STR(const char *ptr)
{
	while((*ptr) != '\0')
	{
		LCD_CHAR(*ptr);
		ptr++;
	}
}

//===================================================================
// CLEAR LCD
void LCD_CLEAR(void)
{
	LCD_COMMAND(LCD_CLEAR_COMMAND);
}

void LCD_INT(int data)
{
   char buff[16]; /* String to hold the ascii result */
   itoa(data,buff,10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
   LCD_STR(buff); /* Display the string */
}

void LCD_moveCursor(uint8 row,uint8 col)
{
	volatile uint8 lcd_memory_address;

	switch(row)
	{
		case 0:
			lcd_memory_address=col;
				break;
		case 1:
			lcd_memory_address=col+0x40;
				break;
		case 2:
			lcd_memory_address=col+0x10;
				break;
		case 3:
			lcd_memory_address=col+0x50;
				break;
	}
	/* Move the LCD cursor to this specific address */
	LCD_COMMAND(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}

void LCD_STR_R_C(uint8 row,uint8 col,const char *txt)
{
	LCD_moveCursor(row,col); /* go to to the required LCD position */
	LCD_STR(txt); /* display the string */
}
