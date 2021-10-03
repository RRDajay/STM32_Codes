#include "stm32f1xx.h"
#include "config.h"
#include "systick_init.h"

void init(void) {

	// Configure the Flash prefetch.
	// FLASH_PREFETCH_BUFFER_ENABLE();
	FLASH->ACR |= FLASH_ACR_PRFTBE_Msk | FLASH_ACR_LATENCY_1;

	// Set Interrupt Group Priority
	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	// Initialize Systick
	systick_init();
}


void RCC_config(void) {

	RCC->CR |= RCC_CR_HSEON_Msk;          // Enable HSE
	while(!(RCC->CR & RCC_CR_HSERDY_Msk));   // Wait till HSE ready
	
	RCC->CFGR |= RCC_CFGR_SW_HSE;                 // Swich to HSE temporarly
	RCC->CR   ^= RCC_CR_HSION_Msk;			 // Disable HSI
	
	RCC->CFGR |= RCC_CFGR_PLLMULL9_Msk;      // Set PLL multiplication to 9
	RCC->CFGR |= RCC_CFGR_PLLSRC_Msk;          // HSE as PLL->SRC

	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1 | RCC_CFGR_PPRE1_DIV2 | RCC_CFGR_HPRE_DIV1;

	RCC->CR |= RCC_CR_PLLON_Msk;            // Enable PLL
	while(!(RCC->CR & RCC_CR_PLLRDY_Msk));   // Wait till PLL ready
	
	RCC->CFGR &= 0xfffffff0; 
	RCC->CFGR = (RCC->CFGR | RCC_CFGR_SW_PLL); // Set PLL as Clock source
	while(!(RCC->CFGR & RCC_CFGR_SWS_PLL));  // Wait till PLL is CLK SRC

	RCC->CFGR  |= (0b111 << RCC_CFGR_MCO_Pos);	
	
	RCC->APB2ENR |= (1 << RCC_APB2ENR_IOPAEN_Pos); 
	RCC->APB2ENR |= (1 << RCC_APB2ENR_IOPCEN_Pos); 

}

int main(void)
{

	init();
	
	RCC_config();

	// PC13 as output
	GPIOC->CRH |= GPIO_CRH_CNF13_0 | GPIO_CRH_MODE13; 

	// Initializes PC13 output to LOW
	GPIOC->ODR &= (0 << GPIO_ODR_ODR13_Pos);

    /* Loop forever */
	while(1) {
		
	}
}
