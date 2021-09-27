#include <stdint.h>
#include "stm32f1xx.h"

#define FLASH_PREFETCH_BUFFER_ENABLE()    (FLASH->ACR |= FLASH_ACR_PRFTBE)

void delay(void) {
	for(uint64_t i = 0; i <= 100000; i++) {
		asm("nop");
	}
}

void init(void) {

	// Configure the Flash prefetch.
	FLASH_PREFETCH_BUFFER_ENABLE();

	// Set Interrupt Group Priority
	NVIC_SetPriorityGrouping(0x00000003U);
}

int main(void)
{

	init();

	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH |= GPIO_CRH_CNF13_0 | GPIO_CRH_MODE13; // PC13 as output
	GPIOC->ODR &= (0 << GPIO_ODR_ODR13_Pos); // Initializes PC13 output to LOW

    /* Loop forever */
	while(1) {

		delay();
		GPIOC->ODR ^= (1 << GPIO_ODR_ODR13_Pos);
	}
}
