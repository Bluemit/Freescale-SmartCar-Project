/*
 * Drv.h
 *
 *  Created on: Jul 7, 2014
 *      Author: ZZH
 */

#ifndef DRV_H_
#define DRV_H_

#define MOTOR0_DEAD_ZONE_GO 4000//left motor go dead output
#define MOTOR1_DEAD_ZONE_GO 4000 //right motor go dead output
#define MOTOR0_DEAD_ZONE_BACK 4000 //left motor back dead output
#define MOTOR1_DEAD_ZONE_BACK 4000 //right motor back dead output

#include "Type.h"

void DRV_PWM_SetRatio16(u8 channel, s16 ratio);//0 is left, 1 is right
void DRV_PWM_Init(void);

#endif /* DRV_H_ */
