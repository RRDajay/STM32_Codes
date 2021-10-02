#include <stdint.h>
#include "stm32f1xx.h"

#define flash_prefetch_buffer_enable()    (FLASH->ACR |= FLASH_ACR_PRFTBE)

void delay(void) {
	for(uint64_t i = 0; i <= 100000; i++) {
		asm("nop");
	}
}

void init(void) {

	// Configure the Flash prefetch.
	flash_prefetch_buffer_enable();
}

int main(void)
{

	// System Init
	init();

	// Enable APB2 Clock
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

	// PC13 as output
	GPIOC->CRH |= GPIO_CRH_CNF13_0 | GPIO_CRH_MODE13; 
	
	// Initializes PC13 output to LOW
	GPIOC->ODR &= (0 << GPIO_ODR_ODR13_Pos); 

    /* Loop forever */
	while(1) {

		delay();
		
		// Reset LED
		GPIOC->ODR ^= (1 << GPIO_ODR_ODR13_Pos);

	}
}
