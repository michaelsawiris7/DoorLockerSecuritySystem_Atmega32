/*
 * DC_MOTOR.h
 *
 *  Created on: Mar 22, 2024
 *      Author: Admin
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "STANDS.h"
#include "GPIO.h"
#include "MACROS.h"
#include <util/delay.h>

#define DC_M_PORT PA
#define DC_M_PIN1 P1
#define DC_M_PIN2 P2
#define DC_M_PIN_speed P3
//DC MOTOR STATE [ OFF_M=0 , ON_CLOCKWISE_M =1 , ON_ANTI-CLOCKWISE_M =2 ]
typedef enum
{
	m_off,m_on_cw,m_on_acw
}MOTOR_STATE;

void PWM_Timer0_Start(uint8 duty_cycle);
void DC_MOTOR(MOTOR_STATE state,uint8 speed);
void DC_MOTOR_INIT();
void DC_MOTOR_ON(void);

void DC_MOTOR_ON_CCW(void);

void DC_MOTOR_OFF(void);





#endif /* DC_MOTOR_H_ */
