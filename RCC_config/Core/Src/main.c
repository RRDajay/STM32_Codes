#include "stm32f1xx.h"
#include "config.h"
#include "systick_init.h"

void init(void) {

	// Configure the Flash prefetch.
	FLASH_PREFETCH_BUFFER_ENABLE();

	// Set Interrupt Group Priority
	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	// Initialize Systick
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
