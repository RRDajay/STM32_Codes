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

#if defined(__RTOS__) && defined(__TASKS_DEMO__)

static const char *pcTextForTask2 = "\r\nS,255,255,255,255,255,255,E\r\n\n";
static const char *pcTextForTask3 = "Hello from task3!\r\n";
static const char *pcTextForTask4 = "Hello from task4!\r\n";
static volatile uint32_t ulIdleCycleCount;
void vApplicationIdleHook(void);
void myTask1 (void *pvParameters);
void myTask2 (void *pvParameters);
void myTask3 (void *pvParameters);

#endif

#if __SEMIHOSTING__
#include <stdio.h>
extern void initialise_monitor_handles();
#endif

extern void clkInit(void);
extern void ledBlink(void);
extern void (*usart1_handler)(void);

int main_tasks(void)
{

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
	// Create Tasks
#if defined(__RTOS__) && defined(__TASKS_DEMO__)

	xTaskCreate(myTask1, "task1", 128, NULL, tskIDLE_PRIORITY+1, NULL);
	xTaskCreate(myTask2, "task2", 128, (void*)pcTextForTask2, tskIDLE_PRIORITY+3, NULL);
	xTaskCreate(myTask3, "task3", 128, (void*)pcTextForTask3, tskIDLE_PRIORITY+2, NULL);
	// xTaskCreate(myTask4, "task4", 1024, NULL, tskIDLE_PRIORITY+4, NULL);

	// Start Scheduler
	vTaskStartScheduler();
	
#endif

    /* Loop forever */

	while(1);

}

#if defined(__RTOS__) && defined(__TASKS_DEMO__) 

void myTask1 (void *pvParameters) {
	for(;;){
		gpio_pin_toggle(GPIOC, 13);
		volatile UBaseType_t uxPriority1 = uxTaskPriorityGet(NULL);
		vTaskDelay(500);
	}
}

void myTask2(void *pvParameters) {
	for(;;) {
		// gpio_pin_toggle(GPIOC, 15);
		usart_send_string(USART1, (char*)pvParameters);
		volatile UBaseType_t uxPriority2 = uxTaskPriorityGet(NULL);
		vTaskDelay(1000);
	}
}

void myTask3(void *pvParameters) {
	for(;;) {
		// gpio_pin_toggle(GPIOC, 15);
		usart_send_string(USART1, (char*)pvParameters);
		volatile UBaseType_t uxPriority3 = uxTaskPriorityGet(NULL);
		vTaskDelay(pdMS_TO_TICKS(100));
	}
}

void myTask4(void *pvParameters) {
	for(;;) {

		vTaskDelay(100);
	}
}

void vApplicationIdleHook(void) {
	ulIdleCycleCount++;
}

#endif
