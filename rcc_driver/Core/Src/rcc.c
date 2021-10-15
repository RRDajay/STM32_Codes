#include "rcc.h"

// Clock Getter Helper Functions

uint32_t rcc_get_ppre1_prescaler(void) {

    uint32_t temp = RCC->CFGR & (7U << 8U);

    if (temp == PPRE1_DIV_2)    
        return DIV_2;
    if (temp == PPRE1_DIV_4)    
        return DIV_4;
    if (temp == PPRE1_DIV_8)    
        return DIV_8;
    if (temp == PPRE1_DIV_16)   
        return DIV_16;

    else
        return DIV_1;

}

uint32_t rcc_get_ppre2_prescaler(void) {

    uint32_t temp = RCC->CFGR & (7U << 11U);

    if (temp == PPRE2_DIV_2)    
        return DIV_2;
    if (temp == PPRE2_DIV_4)    
        return DIV_4;
    if (temp == PPRE2_DIV_8)    
        return DIV_8;
    if (temp == PPRE2_DIV_16)   
        return DIV_16;

    else
        return DIV_1;

}

uint32_t rcc_get_ahb_prescaler(void) {
    uint32_t temp = RCC->CFGR & (15U << 4U);

    if (temp == HPRE_DIV_2)    
        return DIV_2;
    if (temp == HPRE_DIV_4)    
        return DIV_4;
    if (temp == HPRE_DIV_8)    
        return DIV_8;
    if (temp == HPRE_DIV_16)   
        return DIV_16;
    if (temp == HPRE_DIV_64)   
        return DIV_64;
    if (temp == HPRE_DIV_128)   
        return DIV_128;
    if (temp == HPRE_DIV_256)   
        return DIV_256;
    if (temp == HPRE_DIV_512)   
        return DIV_512;

    else
        return DIV_1;
}

uint32_t rcc_get_sysclk(void) {

    SystemCoreClockUpdate();

    return SystemCoreClock;
}

uint32_t rcc_get_apb2_clk(void) {

    uint32_t sys_clk = rcc_get_sysclk();

    // Get AHB Prescaler
    uint32_t ahb_clk = rcc_get_ahb_prescaler();

    // Get APB2 Prescaler
    uint32_t apb2_clk = rcc_get_ppre2_prescaler();

    return (sys_clk / ahb_clk) / apb2_clk;
}

uint32_t rcc_get_apb1_clk(void) {

    uint32_t sys_clk = rcc_get_sysclk();

    // Get AHB Prescaler
    uint32_t ahb_clk = rcc_get_ahb_prescaler();
    
    // Get APB1 Prescaler
    uint32_t apb1_clk = rcc_get_ppre1_prescaler();

    return (sys_clk / ahb_clk) / apb1_clk;
}


// AHB Clock Helper Functions
void rcc_sdio_clock_enable(void){RCC->AHBENR |= 1 << 10;}
void rcc_fsmc_clock_enable(void){RCC->AHBENR |= 1 << 8;}
void rcc_crc_clock_enable(void){RCC->AHBENR |= 1 << 6;}
void rcc_flitf_clock_enable(void){RCC->AHBENR |= 1 << 4;}
void rcc_sram_clock_enable(void){RCC->AHBENR |= 1 << 2;}
void rcc_dma2_clock_enable(void){RCC->AHBENR |= 1 << 1;}
void rcc_dma1_clock_enable(void){RCC->AHBENR |= 1 << 0;}

void rcc_sdio_clock_disable(void){RCC->AHBENR &= ~(1 << 10);}
void rcc_fsmc_clock_disable(void){RCC->AHBENR &= ~(1 << 8);}
void rcc_crc_clock_disable(void){RCC->AHBENR &= ~(1 << 6);}
void rcc_flitf_clock_disable(void){RCC->AHBENR &= ~(1 << 4);}
void rcc_sram_clock_disable(void){RCC->AHBENR &= ~(1 << 2);}
void rcc_dma2_clock_disable(void){RCC->AHBENR &= ~(1 << 1);}
void rcc_dma1_clock_disable(void){RCC->AHBENR &= ~(1 << 0);}

// APB1 Clock Helper Functions
void rcc_dac_clock_enable(void){RCC->APB1ENR |= 1 << 29;}
void rcc_pwr_clock_enable(void){RCC->APB1ENR |= 1 << 28;}
void rcc_bkp_clock_enable(void){RCC->APB1ENR |= 1 << 27;}
void rcc_can_clock_enable(void){RCC->APB1ENR |= 1 << 25;}
void rcc_usb_clock_enable(void){RCC->APB1ENR |= 1 << 23;}
void rcc_i2c2_clock_enable(void){RCC->APB1ENR |= 1 << 22;}
void rcc_i2c1_clock_enable(void){RCC->APB1ENR |= 1 << 21;}
void rcc_uart5_clock_enable(void){RCC->APB1ENR |= 1 << 20;}
void rcc_uart4_clock_enable(void){RCC->APB1ENR |= 1 << 19;}
void rcc_usart3_clock_enable(void){RCC->APB1ENR |= 1 << 18;}
void rcc_usart2_clock_enable(void){RCC->APB1ENR |= 1 << 17;}
void rcc_spi3_clock_enable(void){RCC->APB1ENR |= 1 << 15;}
void rcc_spi2_clock_enable(void){RCC->APB1ENR |= 1 << 14;}
void rcc_wwdg_clock_enable(void){RCC->APB1ENR |= 1 << 11;}
void rcc_tim14_clock_enable(void){RCC->APB1ENR |= 1 << 8;}
void rcc_tim13_clock_enable(void){RCC->APB1ENR |= 1 << 7;}
void rcc_tim12_clock_enable(void){RCC->APB1ENR |= 1 << 6;}
void rcc_tim7_clock_enable(void){RCC->APB1ENR |= 1 << 5;}
void rcc_tim6_clock_enable(void){RCC->APB1ENR |= 1 << 4;}
void rcc_tim5_clock_enable(void){RCC->APB1ENR |= 1 << 3;}
void rcc_tim4_clock_enable(void){RCC->APB1ENR |= 1 << 2;}
void rcc_tim3_clock_enable(void){RCC->APB1ENR |= 1 << 1;}
void rcc_tim2_clock_enable(void){RCC->APB1ENR |= 1 << 0;}

void rcc_dac_clock_disable(void){RCC->APB1ENR &= ~(1 << 29);}
void rcc_pwr_clock_disable(void){RCC->APB1ENR &= ~(1 << 28);}
void rcc_bkp_clock_disable(void){RCC->APB1ENR &= ~(1 << 27);}
void rcc_can_clock_disable(void){RCC->APB1ENR &= ~(1 << 25);}
void rcc_usb_clock_disable(void){RCC->APB1ENR &= ~(1 << 23);}
void rcc_i2c2_clock_disable(void){RCC->APB1ENR &= ~(1 << 22);}
void rcc_i2c1_clock_disable(void){RCC->APB1ENR &= ~(1 << 21);}
void rcc_uart5_clock_disable(void){RCC->APB1ENR &= ~(1 << 20);}
void rcc_uart4_clock_disable(void){RCC->APB1ENR &= ~(1 << 19);}
void rcc_usart3_clock_disable(void){RCC->APB1ENR &= ~(1 << 18);}
void rcc_usart2_clock_disable(void){RCC->APB1ENR &= ~(1 << 17);}
void rcc_spi3_clock_disable(void){RCC->APB1ENR &= ~(1 << 15);}
void rcc_spi2_clock_disable(void){RCC->APB1ENR &= ~(1 << 14);}
void rcc_wwdg_clock_disable(void){RCC->APB1ENR &= ~(1 << 11);}
void rcc_tim14_clock_disable(void){RCC->APB1ENR &= ~(1 << 8);}
void rcc_tim13_clock_disable(void){RCC->APB1ENR &= ~(1 << 7);}
void rcc_tim12_clock_disable(void){RCC->APB1ENR &= ~(1 << 6);}
void rcc_tim7_clock_disable(void){RCC->APB1ENR &= ~(1 << 5);}
void rcc_tim6_clock_disable(void){RCC->APB1ENR &= ~(1 << 4);}
void rcc_tim5_clock_disable(void){RCC->APB1ENR &= ~(1 << 3);}
void rcc_tim4_clock_disable(void){RCC->APB1ENR &= ~(1 << 2);}
void rcc_tim3_clock_disable(void){RCC->APB1ENR &= ~(1 << 1);}
void rcc_tim2_clock_disable(void){RCC->APB1ENR &= ~(1 << 0);}

// APB2 Clock Helper Functions
void rcc_tim11_clock_enable(void){RCC->APB2ENR |= 1 << 21;}
void rcc_tim10_clock_enable(void){RCC->APB2ENR |= 1 << 20;}
void rcc_tim9_clock_enable(void){RCC->APB2ENR |= 1 << 19;}
void rcc_adc3_clock_enable(void){RCC->APB2ENR |= 1 << 15;}
void rcc_usart1_clock_enable(void){RCC->APB2ENR |= 1 << 14;}
void rcc_tim8_clock_enable(void){RCC->APB2ENR |= 1 << 13;}
void rcc_spi1_clock_enable(void){RCC->APB2ENR |= 1 << 12;}
void rcc_tim1_clock_enable(void){RCC->APB2ENR |= 1 << 11;}
void rcc_adc2_clock_enable(void){RCC->APB2ENR |= 1 << 10;}
void rcc_adc1_clock_enable(void){RCC->APB2ENR |= 1 << 9;}
void rcc_iopg_clock_enable(void){RCC->APB2ENR |= 1 << 8;}
void rcc_iopf_clock_enable(void){RCC->APB2ENR |= 1 << 7;}
void rcc_iope_clock_enable(void){RCC->APB2ENR |= 1 << 6;}
void rcc_iopd_clock_enable(void){RCC->APB2ENR |= 1 << 5;}
void rcc_iopc_clock_enable(void){RCC->APB2ENR |= 1 << 4;}
void rcc_iopb_clock_enable(void){RCC->APB2ENR |= 1 << 3;}
void rcc_iopa_clock_enable(void){RCC->APB2ENR |= 1 << 2;}
void rcc_afio_clock_enable(void){RCC->APB2ENR |= 1 << 0;}

void rcc_tim11_clock_disable(void){RCC->APB2ENR &=~(1 << 21);}
void rcc_tim10_clock_disable(void){RCC->APB2ENR &=~(1 << 20);}
void rcc_tim9_clock_disable(void){RCC->APB2ENR &=~(1 << 19);}
void rcc_adc3_clock_disable(void){RCC->APB2ENR &=~(1 << 15);}
void rcc_usart1_clock_disable(void){RCC->APB2ENR &=~(1 << 14);}
void rcc_tim8_clock_disable(void){RCC->APB2ENR &=~(1 << 13);}
void rcc_spi1_clock_disable(void){RCC->APB2ENR &=~(1 << 12);}
void rcc_tim1_clock_disable(void){RCC->APB2ENR &=~(1 << 11);}
void rcc_adc2_clock_disable(void){RCC->APB2ENR &=~(1 << 10);}
void rcc_adc1_clock_disable(void){RCC->APB2ENR &=~(1 << 9);}
void rcc_iopg_clock_disable(void){RCC->APB2ENR &=~(1 << 8);}
void rcc_iopf_clock_disable(void){RCC->APB2ENR &=~(1 << 7);}
void rcc_iope_clock_disable(void){RCC->APB2ENR &=~(1 << 6);}
void rcc_iopd_clock_disable(void){RCC->APB2ENR &=~(1 << 5);}
void rcc_iopc_clock_disable(void){RCC->APB2ENR &=~(1 << 4);}
void rcc_iopb_clock_disable(void){RCC->APB2ENR &=~(1 << 3);}
void rcc_iopa_clock_disable(void){RCC->APB2ENR &=~(1 << 2);}
void rcc_afio_clock_disable(void){RCC->APB2ENR &=~(1 << 0);}

