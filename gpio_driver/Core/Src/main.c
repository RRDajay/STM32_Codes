#include <stdint.h>
#include "gpio.h"
#include "stm32f1xx.h"

void delay(void) {
	for(uint64_t i = 0; i <= 100000; i++) {
		asm("nop");
	}
}



int main(void)
{
	// Enable APB2 Clock
	RCC->APB2ENR |= (1 << RCC_APB2ENR_IOPCEN_Pos);

	// PC13 as output
	// GPIOC->CRH |= GPIO_CRH_CNF13_0 | GPIO_CRH_MODE13; 
	config_output_pin(GPIOC, 13, OUTPUT_PP, S50);

    /* Loop forever */
	while(1) {

		delay();
		
		// Reset LED
		GPIOC->ODR ^= (1 << GPIO_ODR_ODR13_Pos);

	}
}
