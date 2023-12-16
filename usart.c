#include "stm32f103.h"

#include <math.h>
#include <string.h>

void stm32f103_usart1_init(){
	/*	PA9 (transmitter)	*/
  GPIOA->CRH&=~(uint32_t)(0xf<<4);
  /*	alternate function (output push-pull; max speed 50MHz)	*/ 
  GPIOA->CRH|=(uint32_t)(0xb<<4);
  /*	PA10 (receiver)	*/
  /*	not in use	*/
  /*	directly used SystemCoreClock as no prescalers are used	for APB2	*/
	USART1->BRR=(uint16_t)stm32f103_usart_brr_value(SystemCoreClock,STM32_USART_BR_9600);
	/*	usart enable; settings: M=8 (default), parity control disable	*/
	USART1->CR1|=USART_CR1_UE;
}

/*	value of USART BRR register	*/
uint32_t stm32f103_usart_brr_value(uint32_t APBxCLK, uint32_t br){
	float divisor;
	float mantissa,fraction;
	/*	integer values	*/
	uint32_t brr_mantissa,brr_fraction;
	/*	return value	*/
	uint32_t rv;
	if(br!=STM32_USART_BR_9600&&br!=STM32_USART_BR_19200&&br!=STM32_USART_BR_57600&&br!=STM32_USART_BR_115200){
		/*	unsupported baudrate value	*/
		return 0;
	}
	/*	ToDo: floating point operations with GNU as	*/
	divisor=(1.0*APBxCLK)/br/16;
	mantissa=floorf(divisor);
	fraction=divisor-mantissa;
	fraction*=0x10;
	fraction=ceilf(fraction);
	/*	just in case	*/	
	brr_mantissa=(uint32_t)mantissa;
	brr_fraction=(uint32_t)fraction;
	rv=(brr_mantissa<<4)|brr_fraction;
	return rv;
}

void stm32f103_usart1_tx(char buf[], uint16_t size){
	size_t i;
	
	if(!size)
		size=strlen(buf);
	/*	transmitter enable	*/
	USART1->CR1|=USART_CR1_TE;
	/*	send test string	*/
	for(i=0;i<size;i++){
		USART1->DR=buf[i];
		while(!(USART1->SR&USART_SR_TC)){
		}
	}
	/*	disable trasmitter	*/
	USART1->CR1&=~USART_CR1_TE;
}
