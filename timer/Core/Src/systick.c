#include "systick.h"

void systick_init(void) {

	SystemCoreClockUpdate();

	// SysTick_Config(SystemCoreClock / 1000);
	SysTick_Config(SystemCoreClock / 1000);
	// SysTick_Config(9000000UL);


}

void SysTick_Handler(void) {
	pin_toggle(GPIOC, 13);
}
