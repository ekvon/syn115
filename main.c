#include "stm32f103.h"

#include <stdio.h>

#define CHAR_BUF_SIZE 0x400

char usart_tx_buf[CHAR_BUF_SIZE];
char usart_rx_buf[CHAR_BUF_SIZE];

void  dummy_loop(uint32_t count){
	while(--count);
}

int main()
{
	int count;
	size_t size,i;
	char * p;
	
	/*	ToDo: nulling USART buffers	*/
	count=0x8;
  
  stm32f103_rcc_init();
  SystemCoreClockUpdate();
  
  /*	disable unaligned access fault	*/
  /*	SCB->CCR = SCB->CCR & ~(1<<3);	*/
  
  stm32f103_gpio_init();
  stm32f103_usart1_init();
  
	/*	prepare tx buffer (not in use)	*/
	sprintf(usart_tx_buf,"syn115 is configured. SystemCoreClock is %ld\n", SystemCoreClock);
	/*	transmitter enable	*/
	USART1->CR1|=USART_CR1_TE;
	/*	send test string	*/
	for(p=usart_tx_buf;*p;p++){
		USART1->DR=*p;
		while(!(USART1->SR&USART_SR_TC)){
		}
	}
	/*	blink with initial clock	*/
	for(i=0;i<count;i++){
    GPIOC->BSRR=GPIO_BSRR_BS13;
    dummy_loop(0xffff);
    GPIOC->BRR=GPIO_BRR_BR13;
    dummy_loop(0xffff);
  }
}
