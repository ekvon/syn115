#include "stm32f103.h"

void stm32f103_gpio_init(){
	/*	PB13 (general purpose output; max speed 50MHz)	*/
	GPIOB->CRH&=~(0xf<<20);
	GPIOB->CRH|=(0x3<<20);
	/*	PC13 (general purpose output; max speed 50MHz)	*/
  GPIOC->CRH&=~(0xf<<20);
  GPIOC->CRH|=(0x3<<20);
}
