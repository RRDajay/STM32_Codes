#include "flash.h"
#include "gpio.h"
#include "i2c.h"
#include "rcc.h"
#include "stm32f1xx.h"
#include "systick.h"
#include "usart.h"

void clkInit(void);
void resetCtrl(void);

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
    i2c_set_transmit_data("Hello World");
    uint8_t address = 0x27;
    i2c_set_slave_address(address);
    NVIC_EnableIRQ(I2C1_EV_IRQn);
    NVIC_EnableIRQ(I2C1_ER_IRQn);
    i2c_enable(I2C1);
    i2c_master_start_it(I2C1);

    // ****************************************************** //

    /* Loop forever */
    while (1) {

        gpio_pin_toggle(GPIOC, 13);

        delay_ms(250);

        // ****** I2C write to device polling method ***** //

        // i2c_start(I2C1);
        // i2c_write(I2C1);
        // i2c_send_data(I2C1);
        // i2c_send_data(I2C1);
        // i2c_send_data(I2C1);
        // i2c_send_data(I2C1);
        // i2c_send_data(I2C1);
        // i2c_send_data(I2C1);
        // i2c_send_data(I2C1);
        // i2c_send_data(I2C1);
        // i2c_send_data(I2C1);
        // i2c_send_data(I2C1);
        // i2c_send_data(I2C1);
        // i2c_stop(I2C1);
        // i2c_set_data("Hello World");

        // *********************************** //
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
