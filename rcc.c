#include "stm32f103.h"

void stm32f103_rcc_init(){
	/*	enable GPIO	*/
  RCC->APB2ENR|=RCC_APB2ENR_IOPBEN;
  RCC->APB2ENR|=RCC_APB2ENR_IOPCEN;
  RCC->APB2ENR|=RCC_APB2ENR_AFIOEN;
	/* enable USART1	*/
  RCC->APB2ENR|=RCC_APB2ENR_USART1EN;
  /*	don't use any prescalers for APB2	*/
  RCC->CFGR&=~(0x1<<13);
  
  /*	turn on HSE (8MHz) for high stability	*/
  RCC->CR|=RCC_CR_HSEON;
  while(!(RCC->CR&RCC_CR_HSERDY)){
  }
  
	/*	turn on PLLCLK (HSE is used as source;output frequency is 72MHz)	*/
	/*	RCC->CFGR|=(0x1<<16);	*/
	RCC->CFGR|=RCC_CFGR_PLLMULL9;
	RCC->CR|=RCC_CR_PLLON;
	while((RCC->CR&RCC_CR_PLLRDY)==0){
	}
	
	/*	switch to PLLCLK	*/
	RCC->CFGR&=~RCC_CFGR_SW;
	RCC->CFGR|=RCC_CFGR_SW_PLL;
  while ((RCC->CFGR&RCC_CFGR_SWS)!=0x08){
  }
  
  /*	turn off HSI	*/
}
