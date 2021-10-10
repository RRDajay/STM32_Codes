#include "gpio.h"
#include "rcc.h"
#include "systick.h"
#include "usart.h"
#include "stm32f1xx.h"

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

void initialize(void) {
	// RCC Configuration
	RCC_config();

	// Configure SysTick Timer (1ms tick)
	systick_init();
}

int main(void)
{
	
	initialize();

	// Enable APB2 Clock PORTC
	gpio_clock_enable_portc();

	// Configure PC13 as output
	gpio_config_output_pin(GPIOC, 13, OUTPUT_PP, S50);


    /* Loop forever */
	while(1) {
		
		gpio_pin_toggle(GPIOC, 13);

		uint32_t temp1 = rcc_get_ppre2_prescaler();
		uint32_t temp2 = rcc_get_ahb_prescaler();
		uint32_t temp3 = rcc_get_ppre1_prescaler();
		uint32_t temp4 = rcc_get_apb1_clk();
		uint32_t temp5 = rcc_get_apb2_clk();
		uint32_t temp6 = rcc_get_sysclk();
		
		__NOP();

		delay_ms(500);
	}
}
