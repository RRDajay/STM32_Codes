#include "flash.h"
#include "gpio.h"
#include "rcc.h"
#include "stm32f1xx.h"
#include "usart.h"

#if defined(__RTOS__)
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"
#else
#include "systick.h"
#endif

#if defined(__RTOS__) && defined(__MUTEX_DEMO__)

volatile static uint32_t ulIdleCycleCount;
void myTask1(void *param);
void Task2(void *param);
void Task3(void *param);
void vApplicationIdleHook(void);
SemaphoreHandle_t xMutex;

#endif

// Function Prototypes
extern void clkInit(void);
extern void resetCtrl(void);
extern void (*usart1_handler)(void);

int main_mutex(void) {
  // Initializes RCC and FLASH prebuffer
  clkInit();

  // Enable apb2 clock for portc and usart1
  rcc_iopc_clock_enable();
  rcc_usart1_clock_enable();
  rcc_iopa_clock_enable();

  gpio_config_output_pin(GPIOC, 13, OUTPUT_OD,
                         S50); // Configure PC13 as output
  gpio_config_output_pin(GPIOC, 15, OUTPUT_OD,
                         S50); // Configure PC15 as output

  // Configure TX/RX Pins
  gpio_config_output_pin(GPIOA, 9, OUTPUT_AF_PP, S50);
  gpio_config_input_pin(GPIOA, 10, INPUT_PU_PD);

  // Enable USART
  usart_setup(USART1, 115200);
  usart1_handler = resetCtrl;
  usart_enable_irq(USART1);
  // usart_enable_tcie(USART1);
  usart_enable_rxneie(USART1);
  usart_enable(USART1);

#if defined(__RTOS__) && defined(__MUTEX_DEMO__)

  xMutex = xSemaphoreCreateMutex();
  if (xMutex == NULL) {
    for (;;)
      ;
  }

  xTaskCreate(myTask1, "task1", 128, NULL, tskIDLE_PRIORITY + 1, NULL);
  xTaskCreate(Task2, "task2", 128, NULL, tskIDLE_PRIORITY + 1, NULL);
  xTaskCreate(Task3, "task3", 128, NULL, tskIDLE_PRIORITY + 1, NULL);

  vTaskStartScheduler();

#endif

  /* Loop forever */
#if !(defined(__RTOS__))
  while (1) {
    gpio_pin_toggle(GPIOC, 13);
    delay_ms(1000);
  }
#endif
}

#if defined(__RTOS__) && defined(__MUTEX_DEMO__)
void myTask1(void *param) {
  for (;;) {
    gpio_pin_toggle(GPIOC, 13);
    vTaskDelay(250);
  }
}

void Task2(void *param) {
  for (;;) {
    if (xSemaphoreTake(xMutex, 10)) {
      usart_send_string(USART1, "Hello from Task2\r\n");
      xSemaphoreGive(xMutex);
    }

    vTaskDelay(10);
  }
}

void Task3(void *param) {
  for (;;) {
    if (xSemaphoreTake(xMutex, 10)) {
      xSemaphoreGive(xMutex);
      usart_send_string(USART1, "Hello from Task3\r\n");
    }
    vTaskDelay(10);
  }
}

void vApplicationIdleHook(void) { ulIdleCycleCount++; }

#endif
