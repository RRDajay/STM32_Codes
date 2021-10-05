#include "systick.h"
#include "gpio.h"

volatile uint32_t tickCount = 0;

void systick_init(void) {

	SystemCoreClockUpdate();

	// Configure 1ms interrupt
	SysTick_Config(SystemCoreClock / 1000);
}

void SysTick_Handler(void) {
	pin_toggle(GPIOC, 13);
}

void delay_ms(uint32_t desiredTick){
	
	volatile uint32_t start = tickCount;

	while((tickCount - start) < desiredTick);

	tickCount = 0;
}
