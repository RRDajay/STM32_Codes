#include "stm32f1xx.h"
#include "config.h"

#define SystemCoreClock 8000000UL;

void SysTick_Handler(void) {
	// Toggle led 
	// GPIOC->ODR ^= (1 << GPIO_ODR_ODR13_Pos);
	GPIOC->ODR ^= GPIO_ODR_ODR13_Msk;
}

void systick_init(void) {
	// Configure Systick Reload Value Register
	SysTick->LOAD |= SystemCoreClock;
	// Configure Systick Exception in NVIC
	NVIC_SetPriority(SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL);
	// Configure Systick Current Value Register 
	SysTick->VAL = 0UL;
	// Configure Systick Control and Status Register
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk;
}
