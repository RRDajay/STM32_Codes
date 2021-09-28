#include <stdint.h>
#include "stm32f1xx.h"
#include "config.h"

#define SystemCoreClock 8000000UL;

void delay(void) {
	for(uint64_t i = 0; i <= 100000; i++) {
		asm("nop");
	}
}

void SysTick_Handler(void) {
	GPIOC->ODR ^= (1 << GPIO_ODR_ODR13_Pos);
}

void systick_init(void) {
	SysTick->LOAD |= SystemCoreClock;
	NVIC_SetPriority(SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL);
	SysTick->VAL = 0UL;
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk;
}

void init(void) {

	// Configure the Flash prefetch.
	FLASH_PREFETCH_BUFFER_ENABLE();

	// Set Interrupt Group Priority
	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	systick_init();
}

int main(void)
{

	init();

	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH |= GPIO_CRH_CNF13_0 | GPIO_CRH_MODE13; // PC13 as output
	GPIOC->ODR &= (0 << GPIO_ODR_ODR13_Pos); // Initializes PC13 output to LOW

    /* Loop forever */
	while(1) {

		// delay();
		
	}
}
