
/*
 * main.c
 *
 * author: Tunahan Köseoğlu
 *
 * Description: At this problem I implemented a PWM signal to control an LED brightness with duty cycles.
 * 				The brightness will be increase and decrease linearly.
 */
#include "stm32g0xx.h"

void init_timer();
void SysTick_Handler(void);
void delay_ms(int);



volatile int control = 0;



int main(void) {
	 /* Set SysTick */
	    SysTick->CTRL = 0;//Disable SysTick
	    SysTick->LOAD = (SystemCoreClock/1000);//for 1 ms 16000 cpu clock
	    SysTick->VAL = 0;//Clear current value to 0
	    SysTick->CTRL = 0x7;//Enable SysTick
	init_timer();


	 while(1) {

	    	for(uint32_t i=0; i<100 ;i++){
	    		TIM2->CCR2 = i;
	    		 delay_ms(5);
	    	}
	    	for(uint32_t i=100 ; i>0 ; i--){
	    	    		TIM2->CCR2 = i;
	    	    		 delay_ms(5);
	    	    	}

	    }


    return 0;
}



void init_timer(){

	RCC->IOPENR |= ( 1U << 0); //GPIOA clock enable
	RCC->APBENR1 |= RCC_APBENR1_TIM2EN; // Enable TIM2 clock

	GPIOA->MODER &= ~( 3U << 2*1); //alternate function
	GPIOA->MODER |= ( 2U << 2*1);

	GPIOA->AFR[0] |= ( 2 << 1*4); // AF2 FOR TIM2 CH2

	TIM2->CCMR1 |= (6U<<12);
	TIM2->CCER |=TIM_CCER_CC2E;// TIM2 output enable
	TIM2->ARR=100; // period of PWM

	TIM2->CCR2 =0;// duty cycle

	TIM2->CR1 |= TIM_CR1_CEN; // TIM2 enable


}



void SysTick_Handler(void)
{
    control++;
}



void delay_ms(int ms)
{
    control = 0;
    while(control < ms);
}










