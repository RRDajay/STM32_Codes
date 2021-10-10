#include "rcc.h"

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