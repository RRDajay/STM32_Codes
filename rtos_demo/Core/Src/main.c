#include "stm32f1xx.h"
#include "gpio.h"
#include "rcc.h"
#include "usart.h"
#include "flash.h"

#ifdef __RTOS__
#include "FreeRTOS.h"
#include "task.h"
#else
#include "systick.h"
#endif

#ifdef __RTOS__

static const char *pcTextForTask4 = "Hello from task4!\r\n";
static const char *pcTextForTask3 = "Hello from task3!\r\n";
static const char *pcTextForTask2 = "Hello from task2!\r\n";



void myTask1 (void *pvParameters) {
	for(;;){
		gpio_pin_toggle(GPIOC, 13);
		vTaskDelay(1000);
	}
}

void myTask3(void *pvParameters) {
	for(;;) {
		// gpio_pin_toggle(GPIOC, 15);
		usart_send_string(USART1, (char*)pvParameters);
		vTaskDelay(1000);
	}
}

void myTask2(void *pvParameters) {
	for(;;) {
		// gpio_pin_toggle(GPIOC, 15);
		usart_send_string(USART1, (char*)pvParameters);
		vTaskDelay(1000);
	}
}

void myTask4(void *pvParameters) {
	for(;;) {
		volatile uint8_t x = usart_read(USART1);
		usart_write(USART1, x);
		vTaskDelay(50);
	}
}

#endif

void init(void);
void ledBlink(void);
extern void (*usart1_handler)(void);

int main(void)
{

	init();

	// Enable apb2 clock for portc and usart1
	rcc_iopc_clock_enable();
	rcc_usart1_clock_enable();
	rcc_iopa_clock_enable();
	
	gpio_config_output_pin(GPIOC, 13, OUTPUT_OD, S50); // Configure PC13 as output
	gpio_config_output_pin(GPIOC, 15, OUTPUT_OD, S50); // Configure PC15 as output

	// Configure TX/RX Pins
	gpio_config_output_pin(GPIOA, 9, OUTPUT_AF_PP, S50);
	gpio_config_input_pin(GPIOA, 10, INPUT_PU_PD);

	// Enable USART
	usart_setup(USART1, 115200);
	usart1_handler = ledBlink;
	usart_enable_irq(USART1);
	// usart_enable_tcie(USART1);
	usart_enable_rxneie(USART1);
	usart_enable(USART1);
	
	// Create Tasks
#ifdef __RTOS__

	xTaskCreate(myTask1, "task1", 128, NULL, tskIDLE_PRIORITY+1, NULL);
	xTaskCreate(myTask2, "task2", 128, (void*)pcTextForTask2, tskIDLE_PRIORITY+3, NULL);
	xTaskCreate(myTask3, "task3", 128, (void*)pcTextForTask3, tskIDLE_PRIORITY+2, NULL);

	// Start Scheduler
	vTaskStartScheduler();
	
#endif

    /* Loop forever */
	while(1) {

#ifndef __RTOS__
		// usart_send_string(USART1, "Hello World\n");

		// delay_ms(1000);
		// usart_read(USART1);
		// usart_write(USART1, 'a');
		// usart_send_string(USART1, "Hello World\n");
		// gpio_pin_toggle(GPIOC, 13);
		// delay_ms(1000);
#endif

	}

}

void init(void) {

	//	**********	RCC Configuration	**********	//

	// Enable Prefetch buffer
	flash_enable_prefetch_buffer();

	// Enable HSE and wait till HSE ready
	rcc_hse_enable();
	
	// Swich to HSE temporarily
	rcc_set_sysclk(HSE_CLK);

	// Disable HSI
	rcc_hsi_disable();
	
	// Set PLL multiplication to 9
	rcc_set_pllmul(PLLMUL_9);
	
	// Set HSE as PLL source
	rcc_set_pllsrc(HSE_CLK);

	// Set APB1, APB2, and AHB Prescalers
	rcc_set_ppre1_prescaler(DIV_2);
	rcc_set_ppre2_prescaler(DIV_1);
	rcc_set_ahb_prescaler(DIV_1);

	// Enable PLL and wait until PLL is ready
	rcc_pll_enable();

	// Set PLL as Clock source and wait till PLL is CLK source
	rcc_set_sysclk(PLL_CLK);

#ifndef __RTOS__
	systick_init();
#endif
}

void ledBlink(void) {
	volatile uint8_t x = usart_read_IT(USART1);
	usart_send_string(USART1, "Hello World\n");
}