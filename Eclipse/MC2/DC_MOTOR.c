/*
 * DC_MOTOR.c
 *
 *  Created on: Mar 22, 2024
 *      Author: Admin
 */



#include "DC_MOTOR.h"
#include <avr/io.h>
void PWM_Timer0_Start(uint8 duty_cycle)
{
	DDR(PB,DC_M_PIN_speed,OUTPUT);
	TCNT0=0;
	OCR0=(uint8)(2.55*duty_cycle);
	TCCR0=(1<<WGM01)|(1<<WGM00)|(1<<COM01)|(1<<CS01);

}

void DC_MOTOR_INIT()
{
	DDR(DC_M_PORT,DC_M_PIN1,OUTPUT);
	PORT(DC_M_PORT,DC_M_PIN1,OFF);

	DDR(DC_M_PORT,DC_M_PIN2,OUTPUT);
	PORT(DC_M_PORT,DC_M_PIN2,OFF);
}

void DC_MOTOR(MOTOR_STATE state,uint8 speed)
{
	switch(state)
	{
	case m_off:
		PORT(DC_M_PORT,DC_M_PIN1,OFF);
		PORT(DC_M_PORT,DC_M_PIN2,OFF);
		break;
	case m_on_cw:
		PORT(DC_M_PORT,DC_M_PIN1,ON);
		PORT(DC_M_PORT,DC_M_PIN2,OFF);
		PWM_Timer0_Start(speed);
		break;

	case m_on_acw:
		PORT(DC_M_PORT,DC_M_PIN1,OFF);
		PORT(DC_M_PORT,DC_M_PIN2,ON);
		PWM_Timer0_Start(speed);
		break;
	default:
		PORT(DC_M_PORT,DC_M_PIN1,OFF);
		PORT(DC_M_PORT,DC_M_PIN2,OFF);
		break;
	}
}

void DC_MOTOR_ON(void)
{
	PORT(DC_M_PORT,DC_M_PIN1,ON);
	PORT(DC_M_PORT,DC_M_PIN2,OFF);
}
void DC_MOTOR_ON_CCW(void)
{
	PORT(DC_M_PORT,DC_M_PIN1,OFF);
	PORT(DC_M_PORT,DC_M_PIN2,ON);
}
void DC_MOTOR_OFF(void)
{
	PORT(DC_M_PORT,DC_M_PIN1,OFF);
	PORT(DC_M_PORT,DC_M_PIN2,OFF);
}
