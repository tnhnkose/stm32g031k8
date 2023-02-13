/*
 * main.c
 *
 * author: Tunahan Köseoğlu
 *
 * description: Blinks 1 s on-board LED at roughly 1 second intervals using "SysTick"
 *    			exception with 1 millisecond interrupt intervals. The systemm frequency is 16 Mhz,
 *
 *
 */

#include "stm32g0xx.h"


volatile int counter=0;

void delay(volatile uint32_t);

void SysTick_Handler();
void delay_ms();

int main(void) {

	//Enable SysTick timer

	SysTick->CTRL = 0; // Disable SysTick
	SysTick->LOAD = SystemCoreClock/1000; // Count down from 999 to 0
	SysTick->VAL = 0; // Clear current value
	SysTick->CTRL = 0x7; // Enable Systick, exception,
	 // and use processor clock




    /* Enable GPIOC clock */
    RCC->IOPENR |= (1U << 2);

    /* Setup PC6 as output */
    GPIOC->MODER &= ~(3U << 2*6);
    GPIOC->MODER |= (1U << 2*6);

    while(1){
    /* Turn on LED */
    GPIOC->ODR |= (1U << 6);
    delay_ms(1000);
    GPIOC->ODR &= ~(1U << 6);
    delay_ms(1000); //delay for 1 s
    }
    return 0;
}


void delay(volatile uint32_t s) {
    for(; s>0; s--);
}
//SysTick handler function
void SysTick_Handler(){
	counter++;
}
//delay for time value
void delay_ms(int time){

	while(counter!=time);
	counter=0;

}
