#include "stm32f103.h"

void stm32f103_gpio_init(){
	/*	PA8 (AF-MCO;push-pull;max speed 50MHz)	*/
	GPIOA->CRH&=~(0xf);
	GPIOA->CRH|=0xb;
	/*	PB13 (general purpose output; max speed 50MHz)	*/
	GPIOB->CRH&=~(0xf<<20);
	GPIOB->CRH|=(0x3<<20);
	/*	PC13 (general purpose output; max speed 50MHz)	*/
  GPIOC->CRH&=~(0xf<<20);
  GPIOC->CRH|=(0x3<<20);
}
