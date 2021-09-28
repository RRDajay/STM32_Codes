#include "stm32f1xx.h"
#include "config.h"
#include "systick_init.h"

void init(void) {

	// Configure the Flash prefetch.
	FLASH_PREFETCH_BUFFER_ENABLE();

	// Set Interrupt Group Priority
	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	// Initialize Systick
	systick_init();
}

// HSE 8MHz
void RCC_config(void) {

	// // Configure HSE as MCO, PLL Multiplier (!Must be set before PLL is enabled), PLL entry divider and PLL entry clock source,
	// // AHB, APB1, APB2 Prescalers and SYSCLK
	// RCC->CFGR |= RCC_CFGR_MCO_HSE | RCC_CFGR_PLLMULL9_Msk | RCC_CFGR_PLLXTPRE_HSE | 
	// 			RCC_CFGR_PLLSRC_Msk | RCC_CFGR_PPRE2_DIV1 | RCC_CFGR_PPRE1_DIV2 | RCC_CFGR_HPRE_DIV1 |
	// 			RCC_CFGR_SWS_PLL | RCC_CFGR_SW_HSI;

	// // Turn on HSE and PLL
	// RCC->CR |= RCC_CR_HSEON_Msk | RCC_CR_PLLON_Msk;

	// // Configure APB2 Clock
	// RCC->CR |= (1 << 16);            // Enable HSE
	// while(!(RCC->CR & (1 << 17)));   // Wait till HSE ready
	
	// RCC->CFGR |= 1;                  // Swich to HSE temporarly
	// RCC->CR   &= ~1;				 // Disable HSI
	
	// RCC->CFGR |= (0b111 << 18);      // Set PLL multiplication to 9
	// RCC->CFGR |= (1 << 16);          // HSE as PLL->SRC
	
	// RCC->CR |= (1 << 24);            // Enable PLL
	// while(!(RCC->CR & (1 << 25)));   // Wait till PLL ready
	
	// RCC->CFGR = (RCC->CFGR | 0b10) & ~1; // Set PLL as Clock source
	// while(!(RCC->CFGR & (1 << 3)));  // Wait till PLL is CLK SRC

}

int main(void)
{

	init();
	
	RCC_config();

	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; 
	// PC13 as output
	GPIOC->CRH |= GPIO_CRH_CNF13_0 | GPIO_CRH_MODE13; 

	// Initializes PC13 output to LOW
	GPIOC->ODR &= (0 << GPIO_ODR_ODR13_Pos);

    /* Loop forever */
	while(1) {
		
	}
}
