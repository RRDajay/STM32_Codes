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

// PLL
void rcc_pll_enable(void) {
  RCC->CR |= (1U << 24U);
  while (!(RCC->CR & (1U << 25U)))
    ;
}

void rcc_pll_disable(void) { RCC->CR &= ~(1U << 24U); }

// CSS
void rcc_csson_enable(void) { RCC->CR |= (1U << 19U); }
void rcc_csson_disable(void) { RCC->CR &= ~(1U << 19U); }

// HSEBYP
void rcc_hsebyp_enable(void) { RCC->CR |= (1U << 18U); }
void rcc_hsebyp_disable(void) { RCC->CR &= ~(1U << 18U); }

// HSE
void rcc_hse_enable(void) {
  RCC->CR |= (1U << 16U);
  while (!(RCC->CR & (1U << 17U)))
    ;
}

void rcc_hse_disable(void) { RCC->CR &= ~(1U << 16U); }

// HSICAL
uint8_t rcc_get_hsical(void) { return RCC->CR & (0xFF << 8U); }

// HSITRIM
uint8_t rcc_get_hsitrim(void) { return RCC->CR & (0x1F << 3U); }
void rcc_set_hsitrim(uint8_t val) {
  if (val > 31)
    RCC->CR = 31;
  else
    RCC->CR = val;
}

// HSI
void rcc_hsi_enable(void) {
  RCC->CR |= (1U << 0U);
  while (!(RCC->CR & (1U << 1U)))
    ;
}

void rcc_hsi_disable(void) { RCC->CR &= ~(1U << 0U); }

// RCC CFGR Reg Helper Functions
void rcc_set_mco(uint32_t val) {
  RCC->CFGR &= ~(7U << 24U); // Reset Register, No Clock selected

  if (val == MCO_SYSCLK)
    RCC->CFGR |= MCO_SYSCLK << 24U;
  if (val == MCO_HSICLK)
    RCC->CFGR |= MCO_HSICLK << 24U;
  if (val == MCO_HSECLK)
    RCC->CFGR |= MCO_HSECLK << 24U;
  if (val == MCO_PLLCLK)
    RCC->CFGR |= MCO_PLLCLK << 24U;
}

void rcc_set_ppre2_prescaler(uint32_t val) {
  RCC->CFGR &= ~(7U << 11U); // Reset Register. HCLK not divided

  if (val == DIV_2)
    RCC->CFGR |= (PPRE2_DIV_2);
  if (val == DIV_4)
    RCC->CFGR |= (PPRE2_DIV_4);
  if (val == DIV_8)
    RCC->CFGR |= (PPRE2_DIV_8);
  if (val == DIV_16)
    RCC->CFGR |= (PPRE2_DIV_16);
}

void rcc_set_ppre1_prescaler(uint32_t val) {
  RCC->CFGR &= ~(7U << 8U); // Reset Register, HCLK not divided

  if (val == DIV_2)
    RCC->CFGR |= (PPRE1_DIV_2);
  if (val == DIV_4)
    RCC->CFGR |= (PPRE1_DIV_4);
  if (val == DIV_8)
    RCC->CFGR |= (PPRE1_DIV_8);
  if (val == DIV_16)
    RCC->CFGR |= (PPRE1_DIV_16);
}

void rcc_set_ahb_prescaler(uint32_t val) {
  RCC->CFGR &= ~(15U << 4U); // Reset Register, Sysclock not divided

  if (val == DIV_2)
    RCC->CFGR |= (HPRE_DIV_2);
  if (val == DIV_4)
    RCC->CFGR |= (HPRE_DIV_4);
  if (val == DIV_8)
    RCC->CFGR |= (HPRE_DIV_8);
  if (val == DIV_16)
    RCC->CFGR |= (HPRE_DIV_16);
  if (val == DIV_64)
    RCC->CFGR |= (HPRE_DIV_64);
  if (val == DIV_128)
    RCC->CFGR |= (HPRE_DIV_128);
  if (val == DIV_256)
    RCC->CFGR |= (HPRE_DIV_256);
  if (val == DIV_512)
    RCC->CFGR |= (HPRE_DIV_512);
}

void rcc_set_adc_prescaler(uint32_t val) {
  RCC->CFGR &= ~(3U << 14U); // Reset Register, defaults to PCLK divided by 2

  if (val == DIV_2)
    RCC->CFGR |= PCLK2_DIV_2;
  if (val == DIV_4)
    RCC->CFGR |= PCLK2_DIV_4;
  if (val == DIV_6)
    RCC->CFGR |= PCLK2_DIV_6;
  if (val == DIV_8)
    RCC->CFGR |= PCLK2_DIV_8;
}

void rcc_set_pllmul(uint32_t val) {
  RCC->CFGR &= ~(15U << 18U);

  if (val == PLLMUL_2)
    RCC->CFGR |= PLLMUL_2 << 18U;
  if (val == PLLMUL_3)
    RCC->CFGR |= PLLMUL_3 << 18U;
  if (val == PLLMUL_4)
    RCC->CFGR |= PLLMUL_4 << 18U;
  if (val == PLLMUL_5)
    RCC->CFGR |= PLLMUL_5 << 18U;
  if (val == PLLMUL_6)
    RCC->CFGR |= PLLMUL_6 << 18U;
  if (val == PLLMUL_7)
    RCC->CFGR |= PLLMUL_7 << 18U;
  if (val == PLLMUL_8)
    RCC->CFGR |= PLLMUL_8 << 18U;
  if (val == PLLMUL_9)
    RCC->CFGR |= PLLMUL_9 << 18U;
  if (val == PLLMUL_10)
    RCC->CFGR |= PLLMUL_10 << 18U;
  if (val == PLLMUL_11)
    RCC->CFGR |= PLLMUL_11 << 18U;
  if (val == PLLMUL_12)
    RCC->CFGR |= PLLMUL_12 << 18U;
  if (val == PLLMUL_13)
    RCC->CFGR |= PLLMUL_13 << 18U;
  if (val == PLLMUL_14)
    RCC->CFGR |= PLLMUL_14 << 18U;
  if (val == PLLMUL_15)
    RCC->CFGR |= PLLMUL_15 << 18U;
  if (val == PLLMUL_16_1)
    RCC->CFGR |= PLLMUL_16_1 << 18U;
  if (val == PLLMUL_16_2)
    RCC->CFGR |= PLLMUL_16_2 << 18U;
}

void rcc_set_usb_prescaler(uint32_t val) {
  RCC->CFGR &= ~(1U << 22U);

  if (val == USB_PLL_0)
    RCC->CFGR |= USB_PLL_0 << 22U;
  if (val == USB_PLL_1)
    RCC->CFGR |= USB_PLL_1 << 22U;
}

void rcc_set_pllxtpre(uint32_t val) {
  RCC->CFGR &= (1U << 17U);

  if (val == HSE_CLK_NO_DIV)
    RCC->CFGR |= HSE_CLK_NO_DIV << 17U;
  if (val == HSE_CLK_DIV_2)
    RCC->CFGR |= HSE_CLK_DIV_2 << 17U;
}

void rcc_set_pllsrc(uint32_t val) {
  RCC->CFGR &= ~(1U << 16U); // Reset CFGR Register

  if (val == HSI_CLK_DIV_2)
    RCC->CFGR |= HSI_CLK_DIV_2 << 16U;
  if (val == HSE_CLK)
    RCC->CFGR |= HSE_CLK << 16U;
}

uint32_t rcc_get_sws(void) { return RCC->CFGR & (3U << 2U); }

void rcc_set_sysclk(uint32_t val) {
  RCC->CFGR &= ~(3U); // Reset SW Register

  if (val == HSI_CLK) {
    RCC->CFGR |= HSI_CLK;
    while (!(RCC->CFGR & (HSI_CLK << 2U)))
      ;
  }

  if (val == HSE_CLK) {
    RCC->CFGR |= HSE_CLK;
    while (!(RCC->CFGR & (HSE_CLK << 2U)))
      ;
  }

  if (val == PLL_CLK) {
    RCC->CFGR |= PLL_CLK;
    while (!(RCC->CFGR & (PLL_CLK << 2U)))
      ;
  }
}

// AHB Clock Helper Functions
void rcc_sdio_clock_enable(void) { RCC->AHBENR |= 1U << 10U; }
void rcc_fsmc_clock_enable(void) { RCC->AHBENR |= 1U << 8U; }
void rcc_crc_clock_enable(void) { RCC->AHBENR |= 1U << 6U; }
void rcc_flitf_clock_enable(void) { RCC->AHBENR |= 1U << 4U; }
void rcc_sram_clock_enable(void) { RCC->AHBENR |= 1U << 2U; }
void rcc_dma2_clock_enable(void) { RCC->AHBENR |= 1U << 1U; }
void rcc_dma1_clock_enable(void) { RCC->AHBENR |= 1U << 0U; }

void rcc_sdio_clock_disable(void) { RCC->AHBENR &= ~(1U << 10U); }
void rcc_fsmc_clock_disable(void) { RCC->AHBENR &= ~(1U << 8U); }
void rcc_crc_clock_disable(void) { RCC->AHBENR &= ~(1U << 6U); }
void rcc_flitf_clock_disable(void) { RCC->AHBENR &= ~(1U << 4U); }
void rcc_sram_clock_disable(void) { RCC->AHBENR &= ~(1U << 2U); }
void rcc_dma2_clock_disable(void) { RCC->AHBENR &= ~(1U << 1U); }
void rcc_dma1_clock_disable(void) { RCC->AHBENR &= ~(1U << 0U); }

// APB1 Clock Helper Functions
void rcc_dac_clock_enable(void) { RCC->APB1ENR |= 1U << 29U; }
void rcc_pwr_clock_enable(void) { RCC->APB1ENR |= 1U << 28U; }
void rcc_bkp_clock_enable(void) { RCC->APB1ENR |= 1U << 27U; }
void rcc_can_clock_enable(void) { RCC->APB1ENR |= 1U << 25U; }
void rcc_usb_clock_enable(void) { RCC->APB1ENR |= 1U << 23U; }
void rcc_i2c2_clock_enable(void) { RCC->APB1ENR |= 1U << 22U; }
void rcc_i2c1_clock_enable(void) { RCC->APB1ENR |= 1U << 21U; }
void rcc_uart5_clock_enable(void) { RCC->APB1ENR |= 1U << 20U; }
void rcc_uart4_clock_enable(void) { RCC->APB1ENR |= 1U << 19U; }
void rcc_usart3_clock_enable(void) { RCC->APB1ENR |= 1U << 18U; }
void rcc_usart2_clock_enable(void) { RCC->APB1ENR |= 1U << 17U; }
void rcc_spi3_clock_enable(void) { RCC->APB1ENR |= 1U << 15U; }
void rcc_spi2_clock_enable(void) { RCC->APB1ENR |= 1U << 14U; }
void rcc_wwdg_clock_enable(void) { RCC->APB1ENR |= 1U << 11U; }
void rcc_tim14_clock_enable(void) { RCC->APB1ENR |= 1U << 8U; }
void rcc_tim13_clock_enable(void) { RCC->APB1ENR |= 1U << 7U; }
void rcc_tim12_clock_enable(void) { RCC->APB1ENR |= 1U << 6U; }
void rcc_tim7_clock_enable(void) { RCC->APB1ENR |= 1U << 5U; }
void rcc_tim6_clock_enable(void) { RCC->APB1ENR |= 1U << 4U; }
void rcc_tim5_clock_enable(void) { RCC->APB1ENR |= 1U << 3U; }
void rcc_tim4_clock_enable(void) { RCC->APB1ENR |= 1U << 2U; }
void rcc_tim3_clock_enable(void) { RCC->APB1ENR |= 1U << 1U; }
void rcc_tim2_clock_enable(void) { RCC->APB1ENR |= 1U << 0U; }

void rcc_dac_clock_disable(void) { RCC->APB1ENR &= ~(1U << 29U); }
void rcc_pwr_clock_disable(void) { RCC->APB1ENR &= ~(1U << 28U); }
void rcc_bkp_clock_disable(void) { RCC->APB1ENR &= ~(1U << 27U); }
void rcc_can_clock_disable(void) { RCC->APB1ENR &= ~(1U << 25U); }
void rcc_usb_clock_disable(void) { RCC->APB1ENR &= ~(1U << 23U); }
void rcc_i2c2_clock_disable(void) { RCC->APB1ENR &= ~(1U << 22U); }
void rcc_i2c1_clock_disable(void) { RCC->APB1ENR &= ~(1U << 21U); }
void rcc_uart5_clock_disable(void) { RCC->APB1ENR &= ~(1U << 20U); }
void rcc_uart4_clock_disable(void) { RCC->APB1ENR &= ~(1U << 19U); }
void rcc_usart3_clock_disable(void) { RCC->APB1ENR &= ~(1U << 18U); }
void rcc_usart2_clock_disable(void) { RCC->APB1ENR &= ~(1U << 17U); }
void rcc_spi3_clock_disable(void) { RCC->APB1ENR &= ~(1U << 15U); }
void rcc_spi2_clock_disable(void) { RCC->APB1ENR &= ~(1U << 14U); }
void rcc_wwdg_clock_disable(void) { RCC->APB1ENR &= ~(1U << 11U); }
void rcc_tim14_clock_disable(void) { RCC->APB1ENR &= ~(1U << 8U); }
void rcc_tim13_clock_disable(void) { RCC->APB1ENR &= ~(1U << 7U); }
void rcc_tim12_clock_disable(void) { RCC->APB1ENR &= ~(1U << 6U); }
void rcc_tim7_clock_disable(void) { RCC->APB1ENR &= ~(1U << 5U); }
void rcc_tim6_clock_disable(void) { RCC->APB1ENR &= ~(1U << 4U); }
void rcc_tim5_clock_disable(void) { RCC->APB1ENR &= ~(1U << 3U); }
void rcc_tim4_clock_disable(void) { RCC->APB1ENR &= ~(1U << 2U); }
void rcc_tim3_clock_disable(void) { RCC->APB1ENR &= ~(1U << 1U); }
void rcc_tim2_clock_disable(void) { RCC->APB1ENR &= ~(1U << 0U); }

// APB2 Clock Helper Functions
void rcc_tim11_clock_enable(void) { RCC->APB2ENR |= 1U << 21U; }
void rcc_tim10_clock_enable(void) { RCC->APB2ENR |= 1U << 20U; }
void rcc_tim9_clock_enable(void) { RCC->APB2ENR |= 1U << 19U; }
void rcc_adc3_clock_enable(void) { RCC->APB2ENR |= 1U << 15U; }
void rcc_usart1_clock_enable(void) { RCC->APB2ENR |= 1U << 14U; }
void rcc_tim8_clock_enable(void) { RCC->APB2ENR |= 1U << 13U; }
void rcc_spi1_clock_enable(void) { RCC->APB2ENR |= 1U << 12U; }
void rcc_tim1_clock_enable(void) { RCC->APB2ENR |= 1U << 11U; }
void rcc_adc2_clock_enable(void) { RCC->APB2ENR |= 1U << 10U; }
void rcc_adc1_clock_enable(void) { RCC->APB2ENR |= 1U << 9U; }
void rcc_iopg_clock_enable(void) { RCC->APB2ENR |= 1U << 8U; }
void rcc_iopf_clock_enable(void) { RCC->APB2ENR |= 1U << 7U; }
void rcc_iope_clock_enable(void) { RCC->APB2ENR |= 1U << 6U; }
void rcc_iopd_clock_enable(void) { RCC->APB2ENR |= 1U << 5U; }
void rcc_iopc_clock_enable(void) { RCC->APB2ENR |= 1U << 4U; }
void rcc_iopb_clock_enable(void) { RCC->APB2ENR |= 1U << 3U; }
void rcc_iopa_clock_enable(void) { RCC->APB2ENR |= 1U << 2U; }
void rcc_afio_clock_enable(void) { RCC->APB2ENR |= 1U << 0U; }

void rcc_tim11_clock_disable(void) { RCC->APB2ENR &= ~(1U << 21U); }
void rcc_tim10_clock_disable(void) { RCC->APB2ENR &= ~(1U << 20U); }
void rcc_tim9_clock_disable(void) { RCC->APB2ENR &= ~(1U << 19U); }
void rcc_adc3_clock_disable(void) { RCC->APB2ENR &= ~(1U << 15U); }
void rcc_usart1_clock_disable(void) { RCC->APB2ENR &= ~(1U << 14U); }
void rcc_tim8_clock_disable(void) { RCC->APB2ENR &= ~(1U << 13U); }
void rcc_spi1_clock_disable(void) { RCC->APB2ENR &= ~(1U << 12U); }
void rcc_tim1_clock_disable(void) { RCC->APB2ENR &= ~(1U << 11U); }
void rcc_adc2_clock_disable(void) { RCC->APB2ENR &= ~(1U << 10U); }
void rcc_adc1_clock_disable(void) { RCC->APB2ENR &= ~(1U << 9U); }
void rcc_iopg_clock_disable(void) { RCC->APB2ENR &= ~(1U << 8U); }
void rcc_iopf_clock_disable(void) { RCC->APB2ENR &= ~(1U << 7U); }
void rcc_iope_clock_disable(void) { RCC->APB2ENR &= ~(1U << 6U); }
void rcc_iopd_clock_disable(void) { RCC->APB2ENR &= ~(1U << 5U); }
void rcc_iopc_clock_disable(void) { RCC->APB2ENR &= ~(1U << 4U); }
void rcc_iopb_clock_disable(void) { RCC->APB2ENR &= ~(1U << 3U); }
void rcc_iopa_clock_disable(void) { RCC->APB2ENR &= ~(1U << 2U); }
void rcc_afio_clock_disable(void) { RCC->APB2ENR &= ~(1U << 0U); }
