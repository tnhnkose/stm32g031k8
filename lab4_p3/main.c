/*
 * main.c
 *
 * author: Tunahan Köseoğlu
 *
 * Description:  At this problem, I used a KeyPad to setup the duty cycle of the PWM signal.
 * 				The current duty cycle should be printed to the screen via UART.  .
 */
#include "stm32g0xx.h"



void system_init();
void keypad_init();
void pwm_init();
void UART_init(uint32_t baud_rate);
void printChar(uint8_t c);
void _print( char *buf, int len);



void EXTI4_15_IRQHandler(void);
void SysTick_Handler(void);
void delay_ms(int);



volatile int millis = 1600;
volatile int control = 0;
volatile int number = 0;
volatile int sayi = 0;
volatile int pwm_pulse_variable = 0;



#define PWM_PERIOD    100
#define PWM_PULSE    0



int main(void)
{
    UART_init(9600);
    system_init();
    keypad_init();
    pwm_init();



    while(1)
    {
        GPIOA->ODR |= (0xF0);
        TIM2->CCR2 = (uint32_t)pwm_pulse_variable;
    }
    return 0;
}
void system_init()
{
    RCC->IOPENR |= (7U);// Enable GPIOA-B-C clock



    /* Set SysTick */
    SysTick->CTRL = 0;//Disable SysTick
    SysTick->LOAD = (SystemCoreClock/1000);//for 1 ms 1600 cpu clock
    SysTick->VAL = 0;//Clear current value to 0
    SysTick->CTRL = 0x7;//Enable SysTick
}
void keypad_init()
{
    /* Set pin PC6 as output */
    GPIOC->MODER &= ~(3U << 2 * 6);
    GPIOC->MODER |= (1U << 2 * 6);



    /* Set pin PA4 as output */
    GPIOA->MODER &= ~(3U << 2 * 4);
    GPIOA->MODER |= (1U << 2 * 4);
    /* Set pin PA5 as output */
    GPIOA->MODER &= ~(3U << 2 * 5);
    GPIOA->MODER |= (1U << 2 * 5);
    /* Set pin PA6 as output */
    GPIOA->MODER &= ~(3U << 2 * 6);
    GPIOA->MODER |= (1U << 2 * 6);
    /* Set pin PA7 as output */
    GPIOA->MODER &= ~(3U << 2 * 7);
    GPIOA->MODER |= (1U << 2 * 7);
    GPIOA->ODR |= (0xF0);



    /* Set pin PB4 as input */
    GPIOB->MODER &= ~(3U << 2 * 4);
    /* Set pin PB5 as input */
    GPIOB->MODER &= ~(3U << 2 * 5);
    /* Set pin PB6 as input */
    GPIOB->MODER &= ~(3U << 2 * 6);
    /* Set pin PB7 as input */
    GPIOB->MODER &= ~(3U << 2 * 7);



    /* Setup PB4 as external interrupt */
    EXTI->EXTICR[1] |= (1U << 8 * 0);//external interrupt selection
    EXTI->RTSR1 |= (1U << 4);//rising trigger selection(when button pressed)
    EXTI->IMR1 |= (1U << 4);//CPU wakeup with interrupt mask
    /* Setup PB5 as external interrupt */
    EXTI->EXTICR[1] |= (1U << 8 * 1);//external interrupt selection
    EXTI->RTSR1 |= (1U << 5);//rising trigger selection(when button pressed)
    EXTI->IMR1 |= (1U << 5);//CPU wakeup with interrupt mask
    /* Setup PB6 as external interrupt */
    EXTI->EXTICR[1] |= (1U << 8 * 2);//external interrupt selection
    EXTI->RTSR1 |= (1U << 6);//rising trigger selection(when button pressed)
    EXTI->IMR1 |= (1U << 6);//CPU wakeup with interrupt mask
    /* Setup PB7 as external interrupt */
    EXTI->EXTICR[1] |= (1U << 8 * 3);//external interrupt selection
    EXTI->RTSR1 |= (1U << 7);//rising trigger selection(when button pressed)
    EXTI->IMR1 |= (1U << 7);//CPU wakeup with interrupt mask
       NVIC_EnableIRQ(EXTI4_15_IRQn);//set up NVIC for interrupt request
}
void pwm_init()
{
    /* Set pin PB3 as output */
    GPIOB->MODER &= ~(3U << 2 * 3);
    GPIOB->MODER |= (1U << 2 * 3);
    RCC->APBENR1 |= RCC_APBENR1_TIM2EN;// Enable TIM2 clock
    GPIOB->AFR[0] |= (2 << (3 * 4));// set alternate function to TIM2 for PB3
    GPIOB->MODER &= ~(3U << 2*3);// set pin as alternate function
    GPIOB->MODER |= (2U << 2*3);// set pin as alternate function
    TIM2->CCMR1 |= (6U << 12);// set PWM mode
    TIM2->CCER |= TIM_CCER_CC2E;// enable output
    TIM2->ARR = PWM_PERIOD;// set period
    TIM2->CCR2 = PWM_PULSE;// set pulse width
    TIM2->CR1 |= TIM_CR1_CEN; // start timer
}
void UART_init(uint32_t baud_rate)
{
    /* Enable GPIOA and USART2 clocks */
    RCC->IOPENR  |= (1U  << 0);
    RCC->APBENR1 |= (1U << 17);



    /* Set pin PA2 alternate function */
    GPIOA->MODER &= ~(3U << 2 * 2);
    GPIOA->MODER |= (2U  << 2 * 2);



    /* AF1 for PA2 0001 */
    GPIOA->AFR[0] &= (0xFFFF0FF);
    GPIOA->AFR[0] |= (1U   << 4 * 2);



    /* Set pin PA3 as an alternate function */
    GPIOA->MODER &= ~(3U << 2 * 3);
    GPIOA->MODER |= (2U  << 2 * 3);



    /* AF1 for PA3 0001 */
    GPIOA->AFR[0] &= (0xFFFF0FFF);
    GPIOA->AFR[0] |= (1U   << 4 * 3);



    /* Setup USART2 */
    USART2-> CR1  = 0; // reset all values at the register
    USART2-> CR1 |= (1 << 3); // enable Receiver PA3
    USART2-> CR1 |= (1 << 2); // enable Transmitter PA2
    USART2->CR1 |= (1 << 0); // enable USART
    USART2->BRR = (SystemCoreClock / baud_rate); //baud rate
}
void printChar(uint8_t c)
{
    USART2->TDR = c;
    while(!( USART2->ISR & (1<<6)));
}
void _print( char *ptr, int length)
{
    for(int i=0; i < length ; i++)
        printChar(ptr[i]);
}
void EXTI4_15_IRQHandler(void)
{
    if((EXTI->RPR1 >> 4) & 1)//Is external interrupt from PB4
    {
        GPIOA->BRR |= (0xF0);//Low logic all columns
        GPIOA->ODR |= (1U << 4);//1. column high
        if((GPIOB->IDR >> 4) & 1)
            number = 1;



        GPIOA->BRR |= (0xF0);
        GPIOA->ODR |= (1U << 5);//2. column high
        if((GPIOB->IDR >> 4) & 1)
            number = 2;



        GPIOA->BRR |= (0xF0);
        GPIOA->ODR |= (1U << 6);//3. column high
        if((GPIOB->IDR >> 4) & 1)
            number = 3;



        GPIOA->BRR |= (0xF0);
        GPIOA->ODR |= (1U << 7);//4. column high
        if((GPIOB->IDR >> 4) & 1)
            number = 101;
    }
    else if((EXTI->RPR1 >> 5) & 1)//Is external interrupt from PB5
    {
        GPIOA->BRR |= (0xF0);//Low logic all columns
        GPIOA->ODR |= (1U << 4);//1. column high
        if((GPIOB->IDR >> 5) & 1)
            number = 4;



        GPIOA->BRR |= (0xF0);
        GPIOA->ODR |= (1U << 5);//2. column high
        if((GPIOB->IDR >> 5) & 1)
            number = 5;



        GPIOA->BRR |= (0xF0);
        GPIOA->ODR |= (1U << 6);//3. column high
        if((GPIOB->IDR >> 5) & 1)
            number = 6;



        GPIOA->BRR |= (0xF0);
        GPIOA->ODR |= (1U << 7);//4. column high
        if((GPIOB->IDR >> 5) & 1)
            number = 101;
    }
    else if((EXTI->RPR1 >> 6) & 1)//Is external interrupt from PB6
    {
        GPIOA->BRR |= (0xF0);//Low logic all columns
        GPIOA->ODR |= (1U << 4);//1. column high
        if((GPIOB->IDR >> 6) & 1)
            number = 7;



        GPIOA->BRR |= (0xF0);
        GPIOA->ODR |= (1U << 5);//2. column high
        if((GPIOB->IDR >> 6) & 1)
            number = 8;



        GPIOA->BRR |= (0xF0);
        GPIOA->ODR |= (1U << 6);//3. column high
        if((GPIOB->IDR >> 6) & 1)
            number = 9;



        GPIOA->BRR |= (0xF0);
        GPIOA->ODR |= (1U << 7);//4. column high
        if((GPIOB->IDR >> 6) & 1)
            number = 101;
    }
    else if((EXTI->RPR1 >> 7) & 1)//Is external interrupt from PB7
    {
        GPIOA->BRR |= (0xF0);
        GPIOA->ODR |= (1U << 4);//4. column high
        if((GPIOB->IDR >> 7) & 1)
            number = 101;



        GPIOA->BRR |= (0xF0);
        GPIOA->ODR |= (1U << 5);//2. column high
        if((GPIOB->IDR >> 7) & 1)
            number = 0;



        GPIOA->BRR |= (0xF0);
        GPIOA->ODR |= (1U << 6);//3. column high
        if((GPIOB->IDR >> 7) & 1)
            number = 66;



        GPIOA->BRR |= (0xF0);
        GPIOA->ODR |= (1U << 7);//4. column high
        if((GPIOB->IDR >> 7) & 1)
            number = 101;
    }
    if(number == 66)
    {
        if(sayi <= 100)
        {
            pwm_pulse_variable = sayi;
        }
        sayi = 0;
    }
    else
        sayi = ((sayi * 10) + number);



    for(int a=millis*250; a>0; a--);
    EXTI->RPR1 |= (1U << 4);//rising edge pending
    EXTI->RPR1 |= (1U << 5);//rising edge pending
    EXTI->RPR1 |= (1U << 6);//rising edge pending
    EXTI->RPR1 |= (1U << 7);//rising edge pending
}
void SysTick_Handler(void)
{
    control++;
    if(control == 2000)
    {
        int digit1 = pwm_pulse_variable / 100;
        int digit2 = (pwm_pulse_variable % 100)/10;
        int digit3 = pwm_pulse_variable % 10;
        printChar((uint8_t)digit1 + 48);
        printChar((uint8_t)digit2 + 48);
        printChar((uint8_t)digit3 + 48);
        printChar(9);//Tab
        control = 0;
    }
}
