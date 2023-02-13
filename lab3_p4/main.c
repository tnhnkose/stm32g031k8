/*
 * main.c
 *
 * author: Tunahan  Köseoğlu
 *
 * Description: The project is about WatchDog timers in a simple blinky sample.
 */
#include "stm32g0xx.h"

void SysTick_Handler(void);
void delay_ms(int);

volatile int control = 0;

int main(void)
{
	/* Set SysTick */
	SysTick->CTRL = 0;//Disable SysTick
	SysTick->LOAD = (SystemCoreClock/1000);//for 1 ms 16000 cpu clock
	SysTick->VAL = 0;//Clear current value to 0
	SysTick->CTRL = 0x7;//Enable SysTick

	/* Set Independent Watchdog */
	IWDG->KR = (0xCCCC);//Enable IWDG
	IWDG->KR = (0x5555);//Register access to prescaler and reload
	IWDG->PR = (0x1);//Prescaler register
	IWDG->RLR = (0xFFF);//Reload value
	IWDG->SR = 0;//Status register

    /* Enable GPIOC clock */
    RCC->IOPENR |= (1U << 2);

    /* Setup PC6 as output */
    GPIOC->MODER &= ~(3U << 2*6);
    GPIOC->MODER |= (1U << 2*6);

    while(1)
    {
    	delay_ms(1000);
    	GPIOC->ODR |= (1U << 6);
    	IWDG->KR = (0xAAAA);//Feed the dog
    }
    return 0;
}
void SysTick_Handler(void)
{
    control++;
}
void delay_ms(int msecond)
{
    control = 0;
    while(control<msecond);
}
