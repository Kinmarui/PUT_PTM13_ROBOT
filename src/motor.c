/*
 * motor.c
 *
 *  Created on: May 2, 2011
 *      Author: Michal Fularz
 */

#include "motor.h"
//#include <stddef.h>
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x.h"

void MOTOR_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	// sterowniki silnika
	// INA_L
	GPIO_InitStructure.GPIO_Pin = ML_INA;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ML_INA_PORT, &GPIO_InitStructure);
	// INB_L
	GPIO_InitStructure.GPIO_Pin = ML_INB;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ML_PORT, &GPIO_InitStructure);

	// INA_R & INB_R
	GPIO_InitStructure.GPIO_Pin = MR_INA | MR_INB;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MR_PORT, &GPIO_InitStructure);
	
	// PWM_R & PWM_L
	GPIO_InitStructure.GPIO_Pin = MR_PWM | ML_PWM;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(M_PWM_PORT, &GPIO_InitStructure);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	// Timer3 clock enable
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	// Konfiguracja Timera 3
	TIM_TimeBaseStructure.TIM_Period = 2000;	// 4,5 kHz
	TIM_TimeBaseStructure.TIM_Prescaler = 8;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	// Konfiguracja kanalu 3
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 1000;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	// Konfiguracja kanalu 4
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 1000;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM3, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
}

 void MOTOR_setPower(int ML_power, int MR_power)
 {
 	// argument wejœciowy z zakresu 0-100, a PWM 0-2000, wiêc mno¿enie razy 20
	TIM3->CCR3 = MR_power*20;
 	TIM3->CCR4 = ML_power*20;
 }

 void MOTOR_setDirection(state direction)
 {
 	switch(direction)
 	{
 		case BACKWARD:
 		// ustawienie obu silników na obrót zgodnie z ruchem wskazówek zegara
 			GPIO_ResetBits(MR_INA_PORT, MR_INA);
 			GPIO_SetBits(MR_INB_PORT, MR_INB);
			GPIO_SetBits(ML_INA_PORT, ML_INA);
 			GPIO_ResetBits(ML_INB_PORT, ML_INB);
 		break;
		
 		case FORWARD:
 		// ustawienie obu silników na obrót przeciwnie do ruchu wskazówek zegara
			GPIO_SetBits(MR_INA_PORT, MR_INA);
 			GPIO_ResetBits(MR_INB_PORT, MR_INB);
 			GPIO_ResetBits(ML_INA_PORT, ML_INA);
 			GPIO_SetBits(ML_INB_PORT, ML_INB);
 		break;
		
 		case RIGHT:
			GPIO_SetBits(MR_INA_PORT, MR_INA);
 			GPIO_ResetBits(MR_INB_PORT, MR_INB);
 			GPIO_SetBits(ML_INA_PORT, ML_INA);
 			GPIO_ResetBits(ML_INB_PORT, ML_INB);
 		break;
		
 		case LEFT:
 			GPIO_ResetBits(MR_INA_PORT, MR_INA);
 			GPIO_SetBits(MR_INB_PORT, MR_INB);
 			GPIO_ResetBits(ML_INA_PORT, ML_INA);
 			GPIO_SetBits(ML_INB_PORT, ML_INB);
 		break;
		
 		case RIGHT_F:
 			GPIO_SetBits(MR_INA_PORT, MR_INA);
			GPIO_ResetBits(MR_INB_PORT, MR_INB);
 			GPIO_ResetBits(ML_INA_PORT, ML_INA);
 			GPIO_ResetBits(ML_INB_PORT, ML_INB);
 		break;
		
 		case LEFT_F:
 			GPIO_ResetBits(MR_INA_PORT, MR_INA);
 			GPIO_ResetBits(MR_INB_PORT, MR_INB);
			GPIO_SetBits(ML_INA_PORT, ML_INA);
 			GPIO_ResetBits(ML_INB_PORT, ML_INB);
 		break;
		
 		case RIGHT_B:
 			GPIO_ResetBits(MR_INA_PORT, MR_INA);
			GPIO_SetBits(MR_INB_PORT, MR_INB);
 			GPIO_ResetBits(ML_INA_PORT, ML_INA);
 			GPIO_ResetBits(ML_INB_PORT, ML_INB);
 		break;
		
 		case LEFT_B:
 			GPIO_ResetBits(MR_INA_PORT, MR_INA);
 			GPIO_ResetBits(MR_INB_PORT, MR_INB);
			GPIO_ResetBits(ML_INA_PORT, ML_INA);
 			GPIO_SetBits(ML_INB_PORT, ML_INB);
 		break;
		
 		case STOP:
 		break;
			
 		case BRAKE:
 			// hamowanie - wszystko wyzerowane(albo stan wysoki)
 			GPIO_ResetBits(MR_INA_PORT, MR_INA);
			GPIO_ResetBits(MR_INB_PORT, MR_INB);
			GPIO_ResetBits(ML_INA_PORT, ML_INA);
 			GPIO_ResetBits(ML_INB_PORT, ML_INB);
		break;
			
 		default:
 		break;
 	}
 }
