#include "gpio.h"
#include "rcc.h"
#include "systick.h"
#include "stm32f1xx.h"

void rcc_config(void) {

	// Enable Prefetch buffer
	FLASH->ACR |= (0x1UL << FLASH_ACR_PRFTBE_Pos) | FLASH_ACR_LATENCY_1;

	// Enable HSE and wait till HSE ready
	rcc_hse_enable();
	
	// Swich to HSE temporarly
	rcc_set_sysclk(HSE_CLK);

	// Disable HSI
	rcc_hsi_disable();
	
	// Set PLL multiplication to 9
	rcc_set_pllmul(PLLMUL_9);
	
	// Set HSE as PLL source
	rcc_set_pllsrc(HSE_CLK);

	// Set APB1, APB2, and AHB Prescalers
	rcc_set_ppre1_prescaler(DIV_2);
	rcc_set_ppre2_prescaler(DIV_1);
	rcc_set_ahb_prescaler(DIV_1);

	// Enable PLL and wait until PLL is ready
	rcc_pll_enable();

	// Set PLL as Clock source and wait till PLL is CLK source
	rcc_set_sysclk(PLL_CLK);	
}

void initialize(void) {

	// RCC Configuration
	rcc_config();

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

		delay_ms(1000);
	}
}
