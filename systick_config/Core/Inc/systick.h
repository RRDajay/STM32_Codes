#ifndef SYSTICK_H
#define SYSTICK_H

#include "stm32f1xx.h"

void systick_init(void);
void SysTick_Handler(void);
void delay_ms(uint32_t ticks);

#endif
