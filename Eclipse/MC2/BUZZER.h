/*
 * BUZZER.h
 *
 *  Created on: Mar 23, 2024
 *      Author: Admin
 */

#ifndef BUZZER_H_
#define BUZZER_H_


#include "GPIO.h"
#include "STANDS.h"
#include "MACROS.h"

#define  ON_BUZZER  (1u)
#define  OFF_BUZZER (0u)

void BUZZER_INIT(uint8 port,uint8 pin);
void BUZZER_ON(void);
void BUZZER_OFF(void);


#endif /* BUZZER_H_ */
