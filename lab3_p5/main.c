//lab3_q5
#include "stm32g0xx.h"

void EXTI4_15_IRQHandler(void);
void SysTick_Handler(void);

int millis = 1600;
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
	IWDG->PR = (0x5);//Prescaler register
	IWDG->RLR = (0xFFF);//Reload value
	IWDG->SR = 0;//Status register

	/* Enable GPIOA-B-C clock */
    RCC->IOPENR |= (7U);

    /* Set PA0-1-4-5 as output*/
    GPIOA->MODER &= (0xFFFFF0F0);
    GPIOA->MODER |= (0x505);

    /* Set PB0-2-4-5-6-7-8-9 as output*/
    GPIOB->MODER &= (0xFFF000CF);
    GPIOB->MODER |= (0x55510);

    /* Set PC6 as output*/
    GPIOC->MODER &= ~(3U << 2*6);
    GPIOC->MODER |= (1U << 2*6);

    /* Setup PA7 as input */
    GPIOA->MODER &= ~(3U << 2*7);

    /* Setup PA7 as external interrupt */
    EXTI->EXTICR[1] |= (0U << 8*3);//external interrupt selection
    EXTI->RTSR1 |= (1U << 7);//rising trigger selection(when button pressed)
    EXTI->IMR1 |= (1U << 7);//CPU wakeup with interrupt mask
   	NVIC_EnableIRQ(EXTI4_15_IRQn);//set up NVIC for interrupt request

   	while(1)
    return 0;
}

void EXTI4_15_IRQHandler(void)
{
	GPIOC->BRR |= (1U << 6);
	for(int x=0; x<10; x++)
	{
		for(int y=0; y<10; y++)
		{
			for(int z=0; z<10; z++)
			{
				for(int t=0; t<10; t+=5)
				{
					/* Digit 1 */
					GPIOA->BRR |= (0x33);
					GPIOA->ODR |= (0x32);
					switch(x)
					{
						case(0):
						GPIOB->ODR = (0x1F4);
						break;
						case(1):
						GPIOB->ODR = (0x30);
						break;
						case(2):
						GPIOB->ODR = (0x2D4);
						break;
						case(3):
						GPIOB->ODR = (0x274);
						break;
						case(4):
						GPIOB->ODR = (0x330);
						break;
						case(5):
						GPIOB->ODR = (0x364);
						break;
						case(6):
						GPIOB->ODR = (0x3E4);
						break;
						case(7):
						GPIOB->ODR = (0x34);
						break;
						case(8):
						GPIOB->ODR = (0x3F4);
						break;
						case(9):
						GPIOB->ODR = (0x374);
						break;
					}
					for(int a=millis; a>0; a--);
					/* Digit 2 */
					GPIOA->BRR |= (0x33);
					GPIOA->ODR |= (0x31);
					switch(y)
					{
						case(0):
						GPIOB->ODR = (0x1F4);
						break;
						case(1):
						GPIOB->ODR = (0x30);
						break;
						case(2):
						GPIOB->ODR = (0x2D4);
						break;
						case(3):
						GPIOB->ODR = (0x274);
						break;
						case(4):
						GPIOB->ODR = (0x330);
						break;
						case(5):
						GPIOB->ODR = (0x364);
						break;
						case(6):
						GPIOB->ODR = (0x3E4);
						break;
						case(7):
						GPIOB->ODR = (0x34);
						break;
						case(8):
						GPIOB->ODR = (0x3F4);
						break;
						case(9):
						GPIOB->ODR = (0x374);
						break;
					}
					for(int a=millis; a>0; a--);
					/* Digit3 */
					GPIOA->BRR |= (0x33);
					GPIOA->ODR |= (0x23);
					switch(z)
					{
						case(0):
						GPIOB->ODR = (0x1F4);
						break;
						case(1):
						GPIOB->ODR = (0x30);
						break;
						case(2):
						GPIOB->ODR = (0x2D4);
						break;
						case(3):
						GPIOB->ODR = (0x274);
						break;
						case(4):
						GPIOB->ODR = (0x330);
						break;
						case(5):
						GPIOB->ODR = (0x364);
						break;
						case(6):
						GPIOB->ODR = (0x3E4);
						break;
						case(7):
						GPIOB->ODR = (0x34);
						break;
						case(8):
						GPIOB->ODR = (0x3F4);
						break;
						case(9):
						GPIOB->ODR = (0x374);
						break;
					}
					for(int a=millis; a>0; a--);
					/* Digit 4 */
					GPIOA->BRR |= (0x33);
					GPIOA->ODR |= (0x13);
					switch(t)
					{
						case(0):
						GPIOB->ODR = (0x1F4);
						break;
						case(1):
						GPIOB->ODR = (0x30);
						break;
						case(2):
						GPIOB->ODR = (0x2D4);
						break;
						case(3):
						GPIOB->ODR = (0x274);
						break;
						case(4):
						GPIOB->ODR = (0x330);
						break;
						case(5):
						GPIOB->ODR = (0x364);
						break;
						case(6):
						GPIOB->ODR = (0x3E4);
						break;
						case(7):
						GPIOB->ODR = (0x34);
						break;
						case(8):
						GPIOB->ODR = (0x3F4);
						break;
						case(9):
						GPIOB->ODR = (0x374);
						break;
					}
					for(int a=millis*2; a>0; a--);
				}
			}
		}
	}
	/* PC6 led on */
	GPIOC->ODR |= (1U << 6);

	/* All digits write zero */
	GPIOA->BRR |= (0x33);
	GPIOA->ODR &= (0xFFFFFFCC);
	GPIOB->ODR = (0x1F4);

	IWDG->KR = (0xAAAA);//Feed the dog
	EXTI->RPR1 |= (1U << 7);//rising edge pending
}
void SysTick_Handler(void)
{

}
