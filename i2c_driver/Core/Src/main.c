#include "gpio.h"
#include "rcc.h"
#include "flash.h"
#include "systick.h"
#include "stm32f1xx.h"

void rcc_config(void) {

	// Enable Prefetch buffer
	FLASH->ACR |= (0x1UL << FLASH_ACR_PRFTBE_Pos) | FLASH_ACR_LATENCY_1;
	// FLASH->

	// Enable HSE and wait till HSE ready
	rcc_hse_enable();
	
	// Swich to HSE temporarily
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
	
	uint32_t address = 0x08002000;
	uint32_t address2 = 0x08002000;
	uint8_t* data = "Hello World";

    /* Loop forever */
	while(1) {

		gpio_pin_toggle(GPIOC, 13);

		
		if(*data)
		{
			flash_write(address, *((uint16_t*)data));
			address = address+2;
			data+=2;
		}

		else {
			uint32_t* temp = flash_read(address2);
			flash_erase(address2);
			
			address = 0x8002000;
			data = "Hello World";
		}

	}
}
