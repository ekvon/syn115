#ifndef __STM32F103xx__CONFIG__H
#define __STM32F103xx__CONFIG__H

#include <stm32f1xx.h>

#define STM32_USART_BR_9600 9600
#define STM32_USART_BR_19200 19200
#define STM32_USART_BR_57600 57600
#define STM32_USART_BR_115200 115200


void stm32f103_rcc_init();
void stm32f103_gpio_init();

void stm32f103_usart1_init();
uint32_t stm32f103_usart_brr_value(uint32_t APBxCLK, uint32_t br);

#endif
