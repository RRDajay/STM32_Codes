#include "stm32f1xx.h"
#include "config.h"

#define SystemCoreClock 8000000UL;

void SysTick_Handler(void) {
	// Toggle led 
	GPIOC->ODR ^= (1 << GPIO_ODR_ODR13_Pos);
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

	// Configure APB2 Clock
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; 

	// PC13 as output
	GPIOC->CRH |= GPIO_CRH_CNF13_0 | GPIO_CRH_MODE13; 

	// Initializes PC13 output to LOW
	GPIOC->ODR &= (0 << GPIO_ODR_ODR13_Pos);

    /* Loop forever */
	while(1) {
		
	}
}
