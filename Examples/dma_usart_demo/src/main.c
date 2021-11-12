#include "dma.h"
#include "flash.h"
#include "gpio.h"
#include "rcc.h"
#include "stm32f1xx.h"
#include "systick.h"
#include "usart.h"

void clkInit(void);

static volatile uint8_t receiveBuffer[11];

int main(void)
{
    clkInit();

    // Enable usart clock and gpio clock
    rcc_usart1_clock_enable();
    gpio_clock_enable_porta();
    gpio_clock_enable_portc();

    // Configure PC13 as output
    gpio_config_output_pin(GPIOC, 13, OUTPUT_PP, S50);

    // Configure TX/RX Pins
    gpio_config_output_pin(GPIOA, 9, OUTPUT_AF_PP, S50);
    gpio_config_input_pin(GPIOA, 10, INPUT_PU_PD);

    // Configure DMA
    rcc_dma1_clock_enable();
    usart_enable_dma_receiver(USART1);

    dma_enable_minc(DMA1_Channel5);
    dma_enable_tcie(DMA1_Channel5);
    dma_set_dir(DMA1_Channel5, READ_FROM_PERIPHERAL);
    dma_enable_circ(DMA1_Channel5);

    // Set size of buffer
    dma_set_cntdr(DMA1_Channel5, sizeof(receiveBuffer));

    // Write USART_DR address to DMA
    dma_set_cpar(DMA1_Channel5, (uint32_t)&USART1->DR);

    // Write memory address to DMA
    dma_set_cmar(DMA1_Channel5, (uint32_t)receiveBuffer);

    // Enable usart (default settings)
    usart_setup(USART1, 115200);
    usart_enable(USART1);

    // Enable DMA
    dma_enable_channel(DMA1_Channel5);

    NVIC_EnableIRQ(DMA1_Channel5_IRQn);

    /* Loop forever */
    while (1) {
    }
}

void DMA1_Channel5_IRQHandler(void)
{
    if (dma_transfer_complete_flag(DMA1, CH5)) {
        gpio_pin_toggle(GPIOC, 13);
        dma_clear_transfer_complete_flag(DMA1, CH5);
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
