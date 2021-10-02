#include "gpio.h"
#include "stm32f1xx.h"

void delay(void) {
	for(uint64_t i = 0; i <= 100000; i++) {
		asm("nop");
	}
}

int main(void)
{
	// Enable APB2 Clocks for PORTA, PORTB, and PORTC
	GPIO_CLOCK_ENABLE_PORTA;
	GPIO_CLOCK_ENABLE_PORTB;
	GPIO_CLOCK_ENABLE_PORTC;

	// Configure PA1, PB1, PC13, and PC15 as output
	config_output_pin(GPIOA, 1, OUTPUT_PP, S50);
	config_output_pin(GPIOB, 1, OUTPUT_PP, S50);
	config_output_pin(GPIOC, 13, OUTPUT_PP, S50);
	config_output_pin(GPIOC, 15, OUTPUT_PP, S50);

    /* Loop forever */
	while(1) {

		// simple delay
		delay();

		// Toggle output for PA1, PB1, PC13, and PC15
		pin_toggle(GPIOA, 1);
		pin_toggle(GPIOB, 1);
		pin_toggle(GPIOC, 13);
		pin_toggle(GPIOC, 15);
		
	}
}
