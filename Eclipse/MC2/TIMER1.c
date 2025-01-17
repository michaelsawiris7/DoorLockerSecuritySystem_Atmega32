/*
 * TIMER1.c
 *
 *  Created on: Mar 27, 2024
 *      Author: Admin
 */




#include "TIMER1.h"
#include<avr/io.h>
#include<avr/interrupt.h>
static    void (*g_callBackPtr)(void) = NULL_PTR;    //Pointer to [ void function (void) ]
//################ INTERRUPTS SERVICES #######################################
ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}

}
//################  START TIMER1 ####################################################
void TIMER1_INIT(const Timer1_ConfigType * Config_Ptr)
{
/*	TCNT1=Config_Ptr->Initial_value;
	if((Config_Ptr->mode)==CTC_mode)
		{
			TIMSK|=(1<<OCIE1A);
		    OCR1A=Config_Ptr->Compare_value;
		}
	else
	{
			TIMSK|=(1<<TOIE1);
	}
	TCCR1A = (1<<FOC1A);
	TCCR1A=(TCCR1A&0xFC)|(Config_Ptr->mode &0x03);
	TCCR1B=(TCCR1B&0xE7)|(Config_Ptr->mode &0x18);
	TCCR1B=(TCCR1B&0xF8)|(Config_Ptr->prescaler &0x07);*/

	TCCR1A=(1<<FOC1A)|(GET_BIT(Config_Ptr->mode,0)<<WGM10)|(GET_BIT(Config_Ptr->mode,1)<<WGM11);
	TCCR1B=(GET_BIT(Config_Ptr->mode,2)<<WGM12)|(GET_BIT(Config_Ptr->mode,3)<<WGM13)|(Config_Ptr->prescaler);
	TCNT1=(Config_Ptr->Initial_value);
	if((Config_Ptr->mode)==CTC_mode){
		OCR1A=(Config_Ptr->Compare_value);
		TIMSK|=(1<<OCIE1A);
	}
	else{
		TIMSK|=(1<<TOIE1);
	}

}
//################  CLOSE THE TIMER1 ############################################
void TIMER1_DeINIT(void)
{
	TCCR1B|=StopCounter;
	TCNT1=0;
	TIMSK&=~(1<<OCIE1A)&~(1<<TOIE1);
}
//################################################################################
void Timer1_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;
}
