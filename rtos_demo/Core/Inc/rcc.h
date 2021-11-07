#ifndef RCC_H
#define RCC_H 

#include "stm32f1xx.h"
#include "stdbool.h"
#include "stdint.h"

// Microcontroller Clock Output (MCO)

#define MCO_SYSCLK              (4U)              
#define MCO_HSICLK              (5U)
#define MCO_HSECLK              (6U)
#define MCO_PLLCLK              (7U)

// ADC Prescaler
#define PCLK2_DIV_2             (0U << 14U)
#define PCLK2_DIV_4             (1U << 14U)
#define PCLK2_DIV_6             (2U << 14U)
#define PCLK2_DIV_8             (3U << 14U)

// APB1 Prescaler
#define PPRE1_DIV_2             (4U << 8U)
#define PPRE1_DIV_4             (5U << 8U)
#define PPRE1_DIV_8             (6U << 8U)
#define PPRE1_DIV_16            (7U << 8U)

// APB2 Prescaler
#define PPRE2_DIV_2             (4U << 11U)
#define PPRE2_DIV_4             (5U << 11U)
#define PPRE2_DIV_8             (6U << 11U)
#define PPRE2_DIV_16            (7U << 11U)

// AHB Prescaler
#define HPRE_DIV_2              (8U << 4U)
#define HPRE_DIV_4              (9U << 4U)
#define HPRE_DIV_8              (10U << 4U)
#define HPRE_DIV_16             (11U << 4U)
#define HPRE_DIV_64             (12U << 4U)
#define HPRE_DIV_128            (13U << 4U)
#define HPRE_DIV_256            (14U << 4U)
#define HPRE_DIV_512            (15U << 4U)

// Divider Options
#define DIV_1                   (1U)
#define DIV_2                   (2U)
#define DIV_4                   (4U)
#define DIV_6                   (6U)
#define DIV_8                   (8U)
#define DIV_16                  (16U)
#define DIV_64                  (64U)
#define DIV_128                 (128U)
#define DIV_256                 (256U)
#define DIV_512                 (512U)

// PLL Multiplication factor
#define PLLMUL_2                    (0U)
#define PLLMUL_3                    (1U)
#define PLLMUL_4                    (2U)
#define PLLMUL_5                    (3U)
#define PLLMUL_6                    (4U)
#define PLLMUL_7                    (5U)
#define PLLMUL_8                    (6U)
#define PLLMUL_9                    (7U)
#define PLLMUL_10                   (8U)
#define PLLMUL_11                   (9U)
#define PLLMUL_12                   (10U)
#define PLLMUL_13                   (11U)
#define PLLMUL_14                   (12U)
#define PLLMUL_15                   (13U)
#define PLLMUL_16_1                 (14U)
#define PLLMUL_16_2                 (15U)

// USB Prescaler
#define USB_PLL_0                   (0U)
#define USB_PLL_1                   (1U)

// PLLXTPRE HSE divider for PLL entry
#define HSE_CLK_NO_DIV                  (0U)
#define HSE_CLK_DIV_2                   (1U)

// PLLSRC: PLL entry clock source
#define HSI_CLK_DIV_2                   (0U)
#define HSE_CLK                         (1U)

// SW: System Clock Switch
#define HSI_CLK                         (0U)
#define PLL_CLK                         (2U)

// Clock Getter Helper Functions
uint32_t rcc_get_apb1_clk(void);
uint32_t rcc_get_apb2_clk(void);
uint32_t rcc_get_sysclk(void);
uint32_t rcc_get_ppre1_prescaler(void);
uint32_t rcc_get_ppre2_prescaler(void);
uint32_t rcc_get_ahb_prescaler(void);

// PLL
void rcc_pll_enable(void);
void rcc_pll_disable(void);

// CSS
void rcc_csson_enable(void);
void rcc_csson_disable(void);

// HSEBYP
void rcc_hsebyp_enable(void);
void rcc_hsebyp_disable(void);

// HSE
void rcc_hse_enable(void);
void rcc_hse_disable(void);

// HSICAL
uint8_t rcc_get_hsical(void);

// HSITRIM
uint8_t rcc_get_hsitrim(void);
void rcc_set_hsitrim(uint8_t val);

// HSI
void rcc_hsi_enable(void);
void rcc_hsi_disable(void);

// RCC CFGR Reg Helper Functions
void rcc_set_mco(uint32_t val);
void rcc_set_adc_prescaler(uint32_t val);
void rcc_set_ppre2_prescaler(uint32_t val);
void rcc_set_ppre1_prescaler(uint32_t val);
void rcc_set_ahb_prescaler(uint32_t val);
void rcc_set_pllmul(uint32_t val);
void rcc_set_usb_prescaler(uint32_t val);
void rcc_set_pllxtpre(uint32_t val);
void rcc_set_pllsrc(uint32_t val);
uint32_t rcc_get_sws(void);
void rcc_set_sysclk();

// AHB Clock Helper Functions
void rcc_sdio_clock_enable(void);
void rcc_fsmc_clock_enable(void);
void rcc_crc_clock_enable(void);
void rcc_flitf_clock_enable(void);
void rcc_sram_clock_enable(void);
void rcc_dma2_clock_enable(void);
void rcc_dma1_clock_enable(void);

void rcc_sdio_clock_disable(void);
void rcc_fsmc_clock_disable(void);
void rcc_crc_clock_disable(void);
void rcc_flitf_clock_disable(void);
void rcc_sram_clock_disable(void);
void rcc_dma2_clock_disable(void);
void rcc_dma1_clock_disable(void);

// APB1 Clock Helper Functions
void rcc_dac_clock_enable(void);
void rcc_pwr_clock_enable(void);
void rcc_bkp_clock_enable(void);
void rcc_can_clock_enable(void);
void rcc_usb_clock_enable(void);
void rcc_i2c2_clock_enable(void);
void rcc_i2c1_clock_enable(void);
void rcc_uart5_clock_enable(void);
void rcc_uart4_clock_enable(void);
void rcc_usart3_clock_enable(void);
void rcc_usart2_clock_enable(void);
void rcc_spi3_clock_enable(void);
void rcc_spi2_clock_enable(void);
void rcc_wwdg_clock_enable(void);
void rcc_tim14_clock_enable(void);
void rcc_tim13_clock_enable(void);
void rcc_tim12_clock_enable(void);
void rcc_tim7_clock_enable(void);
void rcc_tim6_clock_enable(void);
void rcc_tim5_clock_enable(void);
void rcc_tim4_clock_enable(void);
void rcc_tim3_clock_enable(void);
void rcc_tim2_clock_enable(void);

void rcc_dac_clock_disable(void);
void rcc_pwr_clock_disable(void);
void rcc_bkp_clock_disable(void);
void rcc_can_clock_disable(void);
void rcc_usb_clock_disable(void);
void rcc_i2c2_clock_disable(void);
void rcc_i2c1_clock_disable(void);
void rcc_uart5_clock_disable(void);
void rcc_uart4_clock_disable(void);
void rcc_usart3_clock_disable(void);
void rcc_usart2_clock_disable(void);
void rcc_spi3_clock_disable(void);
void rcc_spi2_clock_disable(void);
void rcc_wwdg_clock_disable(void);
void rcc_tim14_clock_disable(void);
void rcc_tim13_clock_disable(void);
void rcc_tim12_clock_disable(void);
void rcc_tim7_clock_disable(void);
void rcc_tim6_clock_disable(void);
void rcc_tim5_clock_disable(void);
void rcc_tim4_clock_disable(void);
void rcc_tim3_clock_disable(void);
void rcc_tim2_clock_disable(void);

// APB2 Clock Helper Functions
void rcc_tim11_clock_enable(void);
void rcc_tim10_clock_enable(void);
void rcc_tim9_clock_enable(void);
void rcc_adc3_clock_enable(void);
void rcc_usart1_clock_enable(void);
void rcc_tim8_clock_enable(void);
void rcc_spi1_clock_enable(void);
void rcc_tim1_clock_enable(void);
void rcc_adc2_clock_enable(void);
void rcc_adc1_clock_enable(void);
void rcc_iopg_clock_enable(void);
void rcc_iopf_clock_enable(void);
void rcc_iope_clock_enable(void);
void rcc_iopd_clock_enable(void);
void rcc_iopc_clock_enable(void);
void rcc_iopb_clock_enable(void);
void rcc_iopa_clock_enable(void);
void rcc_afio_clock_enable(void);

void rcc_tim11_clock_enable(void);
void rcc_tim10_clock_enable(void);
void rcc_tim9_clock_enable(void);
void rcc_adc3_clock_enable(void);
void rcc_usart1_clock_enable(void);
void rcc_tim8_clock_enable(void);
void rcc_spi1_clock_enable(void);
void rcc_tim1_clock_enable(void);
void rcc_adc2_clock_enable(void);
void rcc_adc1_clock_enable(void);
void rcc_iopg_clock_enable(void);
void rcc_iopf_clock_enable(void);
void rcc_iope_clock_enable(void);
void rcc_iopd_clock_enable(void);
void rcc_iopc_clock_enable(void);
void rcc_iopb_clock_enable(void);
void rcc_iopa_clock_enable(void);
void rcc_afio_clock_enable(void);

#endif