/*
 * main.c
 *
 * author: Tunahan Köseoğlu
 *
 * Description:  The problem is about  general purpose timers. The timer is responsible for toggling an LED
 *              at 1 second intervals. When the button pressed, the blinking speed will be increased by 1 up to 10.
 *
 */

#include "stm32g0xx.h"
#define LEDDELAY 16000000

int volatile mode=1;
void init_timer(unsigned long int value);
void init_interrupt();
void TIM3_IRQHandler();
void EXTI4_15_IRQHandler(void);

int main(void) {

	RCC->APBENR1 |= (1U << 1); // Enable TIM3 clock
	init_timer(1);
	init_interrupt();

    /* Enable GPIOC and GPIOA clock */
    RCC->IOPENR |= (5U << 0);

    /* Setup PC6 as output */
    GPIOC->MODER &= ~(3U << 2*6);
    GPIOC->MODER |= (1U << 2*6);

    /* Setup PA5 as İNPUT */
     GPIOA->MODER &= ~(3U << 2*5);




    while(1) {
    }

    return 0;
}

void init_timer(unsigned long int value){


	TIM3->CR1 = 0; //clear the control register
//	TIM3->CR1  |=(1<<7); //ARPE
	TIM3->CNT = 0; //counter

	// changing time interrupt
	TIM3->PSC = 1000*value;
	TIM3->ARR = 16000;

	TIM3->DIER |= ( 1<<0 );
	TIM3->CR1  |= (1 << 0);
	TIM3->CR1 |= (1U << 7);//ARPE


	 NVIC_EnableIRQ(TIM3_IRQn);//Set up NVIC for interrupt request
     NVIC_SetPriority(TIM3_IRQn, 3);//Set up priority of timer low


}
void init_interrupt(){
	/* Initializing interrupt for PA5 button */
	     EXTI->EXTICR[1] |= (0U << 8*1); // Choose PortA
	    // MUX. 0 has 0-3, 1 has 4-7, 2 has 8-11, 3 has 12-15
	        EXTI->RTSR1 |= (1U << 5); // Rising edge on Px5
	        EXTI->IMR1 |= (1U << 5); // Mask Px5
	        NVIC_EnableIRQ(EXTI4_15_IRQn);//Set up NVIC for interrupt request
	        NVIC_SetPriority(EXTI4_15_IRQn, 1);//Set up priority of button high

}

void EXTI4_15_IRQHandler(){


	mode++;
	if(mode==11){
		mode=1;
	}

	 EXTI->RPR1 |= (1U << 7);//rising edge pending
	 init_timer(mode);

}

void TIM3_IRQHandler(){

	GPIOC->ODR ^= (1U << 6); // turn on led
	TIM3->SR &= ~(1U << 0);//Update interrupt flag

}


