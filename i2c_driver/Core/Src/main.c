#include "gpio.h"
#include "rcc.h"
#include "flash.h"
#include "systick.h"
#include "i2c.h"

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

void lcd_init(void) {

	delay_ms(100);
	i2c_start(I2C1);
	i2c_send_address(I2C1, 0x27);

	i2c_send_data(I2C1, 0x30);
	delay_ms(5);

	i2c_send_data(I2C1, 0x30);
	delay_ms(1);

	i2c_send_data(I2C1, 0x30);
	delay_ms(1);

	i2c_send_data(I2C1, 0x38);
	delay_ms(1);

	i2c_send_data(I2C1, 0x08);
	delay_ms(1);

	i2c_send_data(I2C1, 0x01);
	delay_ms(1);

	i2c_send_data(I2C1, 0x06);
	delay_ms(1);

	i2c_send_data(I2C1, 0x0E);
	delay_ms(1);

	i2c_stop(I2C1);
}

int main(void)
{

	initialize();

	// Enable APB2 Clock PORTC
	rcc_iopb_clock_enable();
	rcc_iopc_clock_enable();
	rcc_i2c1_clock_enable();

	// Configure PC13 as output
	gpio_config_output_pin(GPIOC, 13, OUTPUT_OD, S50);
	
	// I2C1 SCL pin
	gpio_config_output_pin(GPIOB, 6, OUTPUT_AF_OD, S50); 
	
	// I2C1 SDA pin
	gpio_config_output_pin(GPIOB, 7, OUTPUT_AF_OD, S50); 

	uint32_t _apb1_clk = rcc_get_apb1_clk();

	i2c_init(I2C1, I2C_SM_MODE, _apb1_clk);
	i2c_enable(I2C1);

	__NOP();

	lcd_init();
	

    /* Loop forever */
	while(1) {

		__NOP();

	}
}
