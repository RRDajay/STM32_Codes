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

// Clock Enable Helper Functions
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