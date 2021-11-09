#include "systick.h"

#ifndef __RTOS__
volatile uint32_t tickCount = 0;

void systick_init(void) {
  SystemCoreClockUpdate();

  // Configure 1ms interrupt
  SysTick_Config(SystemCoreClock / 1000);
}

void SysTick_Handler(void) { tickCount++; }

void delay_ms(uint32_t desiredTick) {
  volatile uint32_t start = tickCount;

  while ((tickCount - start) < desiredTick)
    ;

  tickCount = 0;
}

#endif
