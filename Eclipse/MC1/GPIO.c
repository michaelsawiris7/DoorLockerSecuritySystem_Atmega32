/*
 * GPIO.c
 *
 *  Created on: Apr 12, 2024
 *      Author: Eng. Michael Samir Sawiris Naguib
 */


#include "GPIO.h"
#include <avr/io.h>
//**************************************************************************************************************************************
//**************************************************************************************************************************************
void  DDR(uint8 Port,uint8 Pin,uint8 State)
{
	switch(Port)
	{
			case PA:
				if (Pin==total)
				{
					if(State==OUTPUT)
					{
						DDRA=0xFF;
					}
					else
					{
						DDRA=0x00;

					}
				}
				else
				{
					if(State == OUTPUT)
					{
						SET_BIT(DDRA,Pin);
					}
					else
					{
						CLEAR_BIT(DDRA,Pin);
					}
				}
				break;
		//###############################################################################################################################
			case PB:
				if (Pin==total)
				{
					if(State==OUTPUT)
					{
						DDRB=0xFF;
					}
					else
					{
						DDRB=0x00;

					}
				}
				else
				{
					if(State == OUTPUT)
					{
						SET_BIT(DDRB,Pin);
					}
					else
					{
						CLEAR_BIT(DDRB,Pin);
					}
				}
				break;
		//###############################################################################################################################

			case PC:
				if (Pin==total)
				{
					if(State==OUTPUT)
					{
						DDRC=0xFF;
					}
					else
					{
						DDRC=0x00;

					}
				}
				else
				{
					if(State == OUTPUT)
					{
						SET_BIT(DDRC,Pin);
					}
					else
					{
						CLEAR_BIT(DDRC,Pin);
					}
				}
				break;
		//###############################################################################################################################
			case PD:
				if (Pin==total)
				{
					if(State==OUTPUT)
					{
						DDRD=0xFF;
					}
					else
					{
						DDRD=0x00;

					}				}
				else
				{
					if(State == OUTPUT)
					{
						SET_BIT(DDRD,Pin);
					}
					else
					{
						CLEAR_BIT(DDRD,Pin);
					}
				}
				break;
	}
}
//**************************************************************************************************************************************
//**************************************************************************************************************************************
void  PORT (uint8 Port,uint8 Pin,uint8 data)
{
	switch(Port)
	{
			case PA:
				if (Pin==total)
				{

					if(data==ON)
					{
						PORTA=0xFF;
					}
					else
					{
						PORTA=0x00;

					}
				}
				else
				{
					if(data == LOGIC_HIGH)
					{
						SET_BIT(PORTA,Pin);
					}
					else
					{
						CLEAR_BIT(PORTA,Pin);
					}
				}
				break;
//###############################################################################################################################
			case PB:
				if (Pin==total)
				{

					if(data==ON)
							{
								PORTB=0xFF;
							}
							else
							{
								PORTB=0x00;

							}
				}
				else
				{
					if(data == LOGIC_HIGH)
					{
						SET_BIT(PORTB,Pin);
					}
					else
					{
						CLEAR_BIT(PORTB,Pin);
					}
				}
				break;
//###############################################################################################################################
			case PC:
				if (Pin==total)
				{

					if(data==ON)
							{
								PORTC=0xFF;
							}
							else
							{
								PORTC=0x00;

							}
				}
				else
				{
					if(data == LOGIC_HIGH)
					{
						SET_BIT(PORTC,Pin);
					}
					else
					{
						CLEAR_BIT(PORTC,Pin);
					}
				}
				break;
//###############################################################################################################################
			case PD:
				if (Pin==total)
				{

					if(data==ON)
							{
								PORTD=0xFF;
							}
							else
							{
								PORTD=0x00;

							}
				}
				else
				{
					if(data == LOGIC_HIGH)
					{
						SET_BIT(PORTD,Pin);
					}
					else
					{
						CLEAR_BIT(PORTD,Pin);
					}
				}
				break;
	}
}
//**************************************************************************************************************************************
//**************************************************************************************************************************************
uint8 PIN  (uint8 Port,uint8 Pin)
{
	volatile uint8 RET;
	switch(Port)
	{
	case PA:
		if(Pin==total)
		{
			RET=PINA;
		}
		else
		{
			RET=GET_BIT(PINA,Pin);
		}
		break;
	case PB:
		if(Pin==total)
		{
			RET=PINB;
		}
		else
		{
			RET=GET_BIT(PINB,Pin);  //PINB&(1<<pi);
		}
		break;
	case PC:
		if(Pin==total)
		{
			RET=PINC;
		}
		else
		{
			RET=GET_BIT(PINC,Pin);
		}
		break;
	case PD:
		if(Pin==total)
		{
			RET=PIND;
		}
		else
		{
			RET=GET_BIT(PIND,Pin);
		}
		break;
	}
	return RET;
}


