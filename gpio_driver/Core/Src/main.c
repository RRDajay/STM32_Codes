#include "gpio.h"
#include "stm32f1xx.h"

void delay(void) {
	for(uint64_t i = 0; i <= 100000; i++) {
		asm("nop");
	}
}

void RCC_config(void) {

	// Enable Prefetch buffer
	FLASH->ACR |= (0x1UL << FLASH_ACR_PRFTBE_Pos) | FLASH_ACR_LATENCY_1;

	RCC->CR |= RCC_CR_HSEON_Msk;          // Enable HSE
	while(!(RCC->CR & RCC_CR_HSERDY_Msk));   // Wait till HSE ready
	
	RCC->CFGR |= RCC_CFGR_SW_HSE;                 // Swich to HSE temporarly
	RCC->CR   ^= RCC_CR_HSION_Msk;			 // Disable HSI
	
	RCC->CFGR |= RCC_CFGR_PLLMULL9_Msk;      // Set PLL multiplication to 9
	RCC->CFGR |= RCC_CFGR_PLLSRC_Msk;          // HSE as PLL->SRC

	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1 | RCC_CFGR_PPRE1_DIV2 | RCC_CFGR_HPRE_DIV1;

	RCC->CR |= RCC_CR_PLLON_Msk;            // Enable PLL
	while(!(RCC->CR & RCC_CR_PLLRDY_Msk));   // Wait till PLL ready
	
	RCC->CFGR &= 0xfffffff0; 
	RCC->CFGR = (RCC->CFGR | RCC_CFGR_SW_PLL); // Set PLL as Clock source
	while(!(RCC->CFGR & RCC_CFGR_SWS_PLL));  // Wait till PLL is CLK SRC

}

int main(void)
{

	// RCC Configuration
	// RCC_config();

	// Enable APB2 Clocks for PORTA, PORTB, and PORTC
	RCC->CFGR  |= (0b111 << RCC_CFGR_MCO_Pos);	
	
	GPIO_CLOCK_ENABLE_PORTA;
	GPIO_CLOCK_ENABLE_PORTB;
	GPIO_CLOCK_ENABLE_PORTC;

	// Configure PA1, PB1, PC13, and PC15 as output
	config_input_pin(GPIOA, 1, INPUT_PU_PD);
	config_output_pin(GPIOA, 8, OUTPUT_AF_PP, S50);
	config_output_pin(GPIOB, 1, OUTPUT_PP, S50);
	config_output_pin(GPIOC, 13, OUTPUT_PP, S50);
	config_output_pin(GPIOC, 15, OUTPUT_PP, S50);

    /* Loop forever */
	while(1) {

		// simple delay
		delay();

		// Toggle output for PA1, PB1, PC13, and PC15
		if (pin_read(GPIOA, 1)) {
			pin_toggle(GPIOC, 13);
		}

		pin_toggle(GPIOB, 1);
		pin_toggle(GPIOC, 15);
		
	}
}
