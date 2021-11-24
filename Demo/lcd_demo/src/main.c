#include "flash.h"
#include "gpio.h"
#include "i2c.h"
#include "rcc.h"
#include "stm32f1xx.h"
#include "systick.h"
#include "usart.h"

void clkInit(void);
void lcd_init(void);

int main(void)
{
        
    clkInit();

    // Enable APB2 Clock PORTC
    rcc_iopb_clock_enable();
    rcc_iopc_clock_enable();

    // Configure PC13 as output
    gpio_config_output_pin(GPIOC, 13, OUTPUT_OD, S50);

    // **************** I2C CONFIGURATION ******************** //
    rcc_i2c1_clock_enable(); // enable i2c1 clock
    gpio_config_output_pin(GPIOB, 6, OUTPUT_AF_OD, S50); // I2C1 SCL pin
    gpio_config_output_pin(GPIOB, 7, OUTPUT_AF_OD, S50); // I2C1 SDA pin
    volatile uint32_t _apb1_clk = rcc_get_apb1_clk();
    i2c_init(I2C1, I2C_SM_MODE, _apb1_clk);
    i2c_itbuf_enable(I2C1);
    i2c_itevt_enable(I2C1);
    i2c_iterr_enable(I2C1);

#if defined(MASTER_WRITE_INTERRUPT_DEMO) || defined(MASTER_READ_INTERRUPT_DEMO)
    NVIC_EnableIRQ(I2C1_EV_IRQn);
    NVIC_EnableIRQ(I2C1_ER_IRQn);
#endif // MACRO

    i2c_enable(I2C1);

    lcd_init();

    // ****************************************************** //

    /* Loop forever */
    while (1) {

        gpio_pin_toggle(GPIOC, 13);
        delay_ms(1000);

#ifdef MASTER_READ_DEMO
        i2c_master_read_data(I2C1, 6, 0x08);
        // i2c_master_read_data(I2C1, 1);
#endif

#ifdef MASTER_WRITE_DEMO
        i2c_master_write_data(I2C1, "Hello World", 11, 0x27);
#endif

#ifdef MASTER_WRITE_INTERRUPT_DEMO
        i2c_master_write_data_it(I2C1, "Hello World with Interrupt", 0x27);
#endif

#ifdef MASTER_READ_INTERRUPT_DEMO
        i2c_master_read_data_it(I2C1, 7, 0x08);
#endif
    }
}

void clkInit(void)
{
    //	**********	RCC Configuration	**********	//

    // Enable Prefetch buffer
    flash_enable_prefetch_buffer();

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

    // Update System Core Clock
    SystemCoreClockUpdate();
    systick_init();
}

void lcd_init(void) {
    delay_ms(15);
    i2c_master_write_data(I2C1, "0", 1, 0x27);
    delay_ms(5);
    i2c_master_write_data(I2C1, "0", 1, 0x27);
    delay_ms(1);
    i2c_master_write_data(I2C1, "0", 1, 0x27);
    
    // i2c_master_write_data(I2C1, " ", 1, 0x27);
    // i2c_master_write_data(I2C1, "0", 1, 0x27);
    // i2c_master_write_data(I2C1, "0", 1, 0x27);
    // i2c_master_write_data(I2C1, "0", 1, 0x27);
    


}