#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "src/motor.h"


int i;
int main(void)
{
	SystemInit();

	/* GPIOD Periph clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA
			| RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD, ENABLE);

	// Alternate Functions I/O clock enable
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);




	GPIO_InitTypeDef GPIO_InitStructure;
	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);


	MOTOR_init();
	MOTOR_setDirection(STOP);
	MOTOR_setPower(0, 0);

    while(1)
    {
    	/*
        for(i=0; i < 99999; i++) ;
       GPIO_SetBits(GPIOC, GPIO_Pin_10);
   	MOTOR_setPower(10, 10);

    for(i=0; i < 99999; i++) ;
   GPIO_ResetBits(GPIOC, GPIO_Pin_10);
	MOTOR_setPower(20, 20);

    for(i=0; i < 99999; i++) ;
   GPIO_ResetBits(GPIOC, GPIO_Pin_10);
	MOTOR_setPower(50, 50);*/
    }
}
