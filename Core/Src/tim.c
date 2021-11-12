#include "tim.h"

void tim_counter_setup(TIM_TypeDef* timx,
    TIM_COUNTMODE timCountMode,
    uint16_t prescalerValue,
    uint16_t autoReloadValue,
    bool autoReload)
{
    // Set Counter Direction
    if (timCountMode == UPCOUNTER)
        timx->CR1 |= (0U << 0U);
    if (timCountMode == DOWNCOUNTER)
        timx->CR1 |= (1U << 0U);

    // Enable Auto-reload preload
    if (autoReload == true)
        timx->CCR1 |= (1U << 7U);
    if (autoReload == false)
        timx->CCR1 &= (1U << 7U);

    // Set Prescaler
    timx->PSC = prescalerValue;

    // Set Reload Value
    timx->ARR = autoReloadValue;
}

void tim_counter_enable(TIM_TypeDef* timx)
{
    timx->CR1 |= (1U << 0U);
}
void tim_counter_disable(TIM_TypeDef* timx)
{
    timx->CR1 &= (1U << 0U);
}
