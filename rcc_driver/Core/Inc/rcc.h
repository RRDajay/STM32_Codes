#ifndef RCC_H
#define RCC_H 

#include "stm32f1xx.h"
#include "stdbool.h"
#include "stdint.h"

#define PPRE1_DIV_2             (4U << 8U)
#define PPRE1_DIV_4             (5U << 8U)
#define PPRE1_DIV_8             (6U << 8U)
#define PPRE1_DIV_16            (7U << 8U)

#define PPRE2_DIV_2             (4U << 11U)
#define PPRE2_DIV_4             (5U << 11U)
#define PPRE2_DIV_8             (6U << 11U)
#define PPRE2_DIV_16            (7U << 11U)

#define HPRE_DIV_2              (8U << 4U)
#define HPRE_DIV_4              (9U << 4U)
#define HPRE_DIV_8              (10U << 4U)
#define HPRE_DIV_16             (11U << 4U)
#define HPRE_DIV_64             (12U << 4U)
#define HPRE_DIV_128            (13U << 4U)
#define HPRE_DIV_256            (14U << 4U)
#define HPRE_DIV_512            (15U << 4U)

#define DIV_1                   (1U)
#define DIV_2                   (2U)
#define DIV_4                   (4U)
#define DIV_8                   (8U)
#define DIV_16                  (16U)
#define DIV_64                  (64U)
#define DIV_128                 (128U)
#define DIV_256                 (256U)
#define DIV_512                 (512U)

// typedef enum {

// } PPRE2_Div;

// Clock Getter Helper Functions
uint32_t rcc_get_apb1_clk(void);
uint32_t rcc_get_apb2_clk(void);
uint32_t rcc_get_sysclk(void);
uint32_t rcc_get_ppre1_prescaler(void);
uint32_t rcc_get_ppre2_prescaler(void);
uint32_t rcc_get_ahb_prescaler(void);

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
void rcc_spi1_clock_enable(void);
void rcc_tim1_clock_enable(void);
void rcc_adc2_clock_enable(void);
void rcc_adc1_clock_enable(void);
void rcc_iope_clock_enable(void);
void rcc_iopd_clock_enable(void);
void rcc_iopc_clock_enable(void);
void rcc_iopb_clock_enable(void);
void rcc_iopa_clock_enable(void);
void rcc_afio_clock_enable(void);

void rcc_tim11_clock_disable(void);
void rcc_tim10_clock_disable(void);
void rcc_tim9_clock_disable(void);
void rcc_adc3_clock_disable(void);
void rcc_usart1_clock_disable(void);
void rcc_spi1_clock_disable(void);
void rcc_tim1_clock_disable(void);
void rcc_adc2_clock_disable(void);
void rcc_adc1_clock_disable(void);
void rcc_iope_clock_disable(void);
void rcc_iopd_clock_disable(void);
void rcc_iopc_clock_disable(void);
void rcc_iopb_clock_disable(void);
void rcc_iopa_clock_disable(void);
void rcc_afio_clock_disable(void);


#endif