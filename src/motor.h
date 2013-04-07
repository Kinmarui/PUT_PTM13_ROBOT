/*
 * motor.h
 *
 *  Created on: May 2, 2011
 *      Author: Michal Fularz
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#define MR_PORT GPIOA
#define MR_INA_PORT MR_PORT
#define MR_INB_PORT MR_PORT
#define MR_INB GPIO_Pin_6
#define MR_INA GPIO_Pin_4
#define MR_DIAGA GPIO_Pin_5
#define MR_DIAGB GPIO_Pin_7

#define ML_INA_PORT GPIOD
#define ML_INA GPIO_Pin_2
#define ML_PORT GPIOB
#define ML_INB_PORT ML_PORT
#define ML_INB GPIO_Pin_6
#define ML_DIAGA GPIO_Pin_5
#define ML_DIAGB GPIO_Pin_7

#define M_PWM_PORT GPIOB
#define MR_PWM GPIO_Pin_0
#define ML_PWM GPIO_Pin_1

typedef enum { FORWARD, BACKWARD, RIGHT, LEFT, RIGHT_F, LEFT_F, RIGHT_B, LEFT_B, STOP, BRAKE } state;

void MOTOR_init(void);
void MOTOR_setPower(int ML_power, int MR_power);
void MOTOR_setDirection(state direction);

#endif /* MOTOR_H_ */
