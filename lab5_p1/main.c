/*
 * main.c
 *
 * author: Tunahan Köseoğlu
 *
 * Description:  At this problem, I control the brightnesses of two LEDs with a Potantiometer.
 * 				 When  the potantiometer value changes,  the brightnesses are should be changed
 * 				 in opposite ways which means one LED brighntess increaes and the other decreases.
 * 				 I used ADC at the problem.
 */

#include "stm32g0xx.h"

#define LEDDELAY    1600000

void delay(volatile uint32_t);

int main(void) {


	init_output_timer();


    while(1) {

    }

    return 0;
}

void init_output_timer(){

		RCC->IOPENR |= ( 1U << 1); //GPIOB clock enable
		RCC->APBENR1 |= RCC_APBENR1_TIM3EN; // Enable TIM3 clock

		GPIOB->MODER &= ~( 3U << 2*4); // PB4 as an alternate function
		GPIOB->MODER |= ( 2U << 2*4);

		GPIOB->MODER &= ~( 3U << 2*5); // PB5 as an alternate function
		GPIOB->MODER |= ( 2U << 2*5);


		GPIOB->AFR[0] |= ( 1 << 4*4); // AF1 FOR TIM3 CH1
		GPIOB->AFR[0] |= ( 1 << 4*5); // AF1 FOR TIM3 CH1

		TIM3->CCMR1 |= (3U<<5);
		TIM3->CCMR1 |= (6U<<12);
		TIM3->CCER |=TIM_CCER_CC1E;// TIM3 output enable
		TIM3->CCER |=TIM_CCER_CC2E;// TIM3 output enable
		TIM3->ARR=100; // period of PWM

		TIM3->CCR1 =100;// duty cycle
		TIM3->CCR2 =100;// duty cycle

		TIM3->CR1 |= TIM_CR1_CEN; // TIM3 enable

}
