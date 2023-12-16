#include "stm32f103.h"

#include <stdio.h>
#include <stdlib.h>

#define CHAR_BUF_SIZE 0x400

char usart_tx_buf[CHAR_BUF_SIZE];
char usart_rx_buf[CHAR_BUF_SIZE];

char syn115_tx_buf[CHAR_BUF_SIZE];
int count;

void  dummy_loop(uint32_t count){
	while(--count);
}

void SysTick_Handler(){
	sprintf(usart_tx_buf,"SysTickHandler: count=%d\n", count);
	stm32f103_usart1_tx(usart_tx_buf,0);
	if(!count--){
		/*	disable SysTickTimer	*/
		SysTick->CTRL&=~0x1;
		/*	exit	*/
		exit(EXIT_SUCCESS);
	}
}

int main()
{
	/*	frequency of transmission	*/
	uint32_t f;
	size_t size,i;
	char * p;
	
	/*	ToDo: nulling USART buffers	*/
	count=0x8;
  
  stm32f103_rcc_init();
  SystemCoreClockUpdate();
  
  stm32f103_gpio_init();
  stm32f103_usart1_init();
  
	/*	prepare tx buffer (not in use)	*/
	sprintf(usart_tx_buf,"syn115 is configured. SystemCoreClock is %ld\n", SystemCoreClock);
	stm32f103_usart1_tx(usart_tx_buf,0);
	
	/*	
	* Initialize and enable SysTickTimer.
	* AHB/8 (4MHz) is used as source clock.
	*/
  SysTick->LOAD|=0x3d0900;
  SysTick->CTRL|=0x1;
  
  dummy_loop(0xffff);
}
