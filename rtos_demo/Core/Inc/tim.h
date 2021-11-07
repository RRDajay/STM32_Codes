#ifndef _TIM_H_ 
#define _TIM_H_

#include "stm32f1xx.h"
#include "stdbool.h"

typedef enum {
    UPCOUNTER = 0U,
    DOWNCOUNTER = 1U
} TIM_COUNTMODE;

void tim_counter_setup(TIM_TypeDef* timx,  TIM_COUNTMODE timCountMode, uint16_t prescalerValue, uint16_t autoReloadValue, bool autoReload);
void tim_counter_enable(TIM_TypeDef* timx);
void tim_counter_disable(TIM_TypeDef* timx);

#endif //_TIM_H_