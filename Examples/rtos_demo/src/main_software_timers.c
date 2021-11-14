#include "flash.h"
#include "gpio.h"
#include "rcc.h"
#include "stm32f1xx.h"
#include "usart.h"

#if defined(__RTOS__)
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "timers.h"
#else
#include "systick.h"
#endif

#if defined(__RTOS__) && defined(__SOFTWARE_TIMER_DEMO__)

void Task1(void *params);
void vApplicationdIdleHook(void);

#endif

// Function Prototypes
extern void clkInit(void);
extern void resetCtrl(void);
extern void (*usart1_handler)(void);

int main_software_timers(void) {
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

  usart_send_string(USART1, "Hello from STM32\r\n");

#if defined(__RTOS__) && defined(__SOFTWARE_TIMER_DEMO__)

  xTaskCreate(Task1, "task1", 128, NULL, tskIDLE_PRIORITY + 1, NULL);

  vTaskStartScheduler();
#endif

  /* Loop forever */
#if !(defined(__RTOS__))
  while (1) {
    gpio_pin_toggle(GPIOC, 13);
    delay_ms(100);
  }
#endif
}

#if defined(__RTOS__) && defined(__SOFTWARE_TIMER_DEMO__)

void Task1(void *params) {
  for (;;) {
    gpio_pin_toggle(GPIOC, 13);
    vTaskDelay(500);
  }
}

void vApplicationIdleHook(void) {}

#endif
