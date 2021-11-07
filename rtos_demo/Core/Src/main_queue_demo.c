#include "stm32f1xx.h"
#include "gpio.h"
#include "rcc.h"
#include "usart.h"
#include "flash.h"

#if defined(__RTOS__)
#include "FreeRTOS.h"
#include "task.h"
#else
#include "systick.h"
#endif

#if defined(__RTOS__) && defined(__QUEUE_DEMO__)

// Variable Declaration
static volatile uint32_t ulIdleCycleCount;

// RTOS Function Prototypes
void vApplicationIdleHook(void);
void myTask1 (void *pvParameters);
void myTask2 (void *pvParameters);


#endif

#if __SEMIHOSTING__
#include <stdio.h>
extern void initialise_monitor_handles();
#endif

// Function Prototypes
extern void clkInit(void);
extern void ledBlink(void);
extern void (*usart1_handler)(void);

int main_queue(void)
{

	// Initializes RCC and FLASH prebuffer
	clkInit();

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

#if __SEMIHOSTING__
	initialise_monitor_handles();
#endif

#if defined(__RTOS__) && defined(__QUEUE_DEMO__)

	// Create Tasks
	xTaskCreate(myTask1, "task1", 128, NULL, tskIDLE_PRIORITY+1, NULL);
	xTaskCreate(myTask2, "task2", 128, NULL, tskIDLE_PRIORITY+2, NULL);
	// Start Scheduler
	vTaskStartScheduler();
	
#endif

    /* Loop forever */
	while(1) {
#if !(defined(__RTOS__))

#if __SEMIHOSTING__
		printf("Hello World\n");
#endif

		gpio_pin_toggle(GPIOC, 13);
		delay_ms(1000);

#endif
	}

}

#if defined(__RTOS__) && defined(__QUEUE_DEMO__) 

// Blink led every 500ms
void myTask1 (void *pvParameters) {
	for(;;) { 
		gpio_pin_toggle(GPIOC, 13);
		vTaskDelay(500);
		usart_send_string(USART1, "Hello from task 1!\n");
	}
}

void myTask2 (void *pvParameters) {
	for(;;) {
		usart_send_string(USART1, "Hello from task 2!\n");
		vTaskDelay(150);
	}
}
// Increment ulIdleCycleCount during idle time 
void vApplicationIdleHook(void) {

	ulIdleCycleCount++;
}

#endif
