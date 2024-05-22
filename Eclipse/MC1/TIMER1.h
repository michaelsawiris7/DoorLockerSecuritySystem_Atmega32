/*
 * TIMER1.h
 *
 *  Created on: Mar 27, 2024
 *      Author: Admin
 */

#ifndef TIMER1_H_
#define TIMER1_H_

#include "STANDS.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "MACROS.h"

typedef enum
{
	Normal_mode=0,CTC_mode=4,FAST_PWM_mode=15
}Timer1_Mode;
typedef enum
{
	StopCounter,NoPrescaler,Fcpu_8,Fcpu_64,Fcpu_256,Fcpu_1024
}Timer1_Prescaler;
typedef struct
{
	volatile uint16 Initial_value;
	volatile uint16 Compare_value; // it will be used in compare mode only.
	Timer1_Prescaler prescaler;
	Timer1_Mode mode;
} Timer1_ConfigType;

void TIMER1_INIT(const Timer1_ConfigType * Config_Ptr);
void TIMER1_DeINIT(void);
void Timer1_setCallBack(void(*a_ptr)(void));

#endif /* TIMER1_H_ */
