/*
 * main.c
 *
 * author: Tunahan Köseoğlu
 * Description: Connection between the board and the PC with UART protocol.
 *
 */

#include "stm32g0xx.h"

void UART_tx(uint8_t c);
uint8_t UART_rx(void);
void UART_init(uint32_t baud);
void printChar(uint8_t c);
void _print( char *buf, int len);
void print(char *buf);
void delay_ms(int);

int main(void) {

	 UART_init(9600); // UART initilization

    while(1) {
    	delay_ms(1000);
    	_print("Hello World\n",12);
    }

    return 0;
}

void UART_init(uint32_t baud){

	RCC->IOPENR  |= (1U  << 0);  //enable GPIOA clock
	RCC->APBENR1 |= (1U << 17); // enabLE USART clock

	GPIOA->MODER &= ~(3U << 2*2); // PA2 alternate function
	GPIOA->MODER |= (2U  << 2*2);

	GPIOA->AFR[0] &= ~(0xFU << 4*2); // AF1 from mux
	GPIOA->AFR[0] |= (1U   << 4*2);


	GPIOA->MODER &= ~(3U << 2*3); // PA3 as an alternate function
	GPIOA->MODER |= (2U  << 2*3);

	GPIOA->AFR[0] &= ~(0xFU << 4*3); // AF1 from mux
	GPIOA->AFR[0] |= (1U   << 4*3);

	// setup UART2
	USART2-> CR1  = 0; // reset all values at the register
	USART2-> CR1 |= (1 << 3); // enable Receiver

	USART2-> CR1 |= (1 << 2); // enable Transmitter

	USART2->CR1 |= (1 << 0); // enable USART

	USART2->BRR = (SystemCoreClock / baud); //baud rate


}

void UART_tx(uint8_t c){

		printChar(c);
}

uint8_t UART_rx(void){

	uint8_t message = USART2->RDR;
	return message;
}


void printChar(uint8_t c){
USART2->TDR =(uint16_t)c;
while(!( USART2->ISR & (1<<6)));
}

void _print( char *ptr, int len){

for(int i=0; i<len ; ++i){
printChar(ptr[i]);
}

}
void delay_ms(int time ){

	time=time*1600;
	while(time!=0){
		time=time-1;
}
}







