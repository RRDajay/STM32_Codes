#include "flash.h"
#include "gpio.h"
#include "rcc.h"
#include "stm32f1xx.h"
#include "usart.h"

#if defined(__RTOS__)
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#else
#include "systick.h"
#endif

#if defined(__RTOS__) && defined(__QUEUE_DEMO__)

typedef enum {
    eSender1,
    eSender2
} DataSource_t;

typedef struct {
    uint8_t* ucValue;
    DataSource_t eDataSource;
} Data_t;

// Dummy Data
static Data_t xStructsToSend[2] = {
    { "Received from sender1", eSender1 },
    { "Received from sender2", eSender2 }
};

// Cycle count during applicationIdle
static uint32_t ulIdleCycleCount;

// Queue declaration
QueueHandle_t xQueue;

// Tasks Function prototype
static void vLedBlink(void* param);
static void vSenderTask(void* param);
static void vReceiverTask(void* param);
void vApplicationIdleHook(void);

#endif

#if __SEMIHOSTING__
#include <stdio.h>
extern void initialise_monitor_handles();
#endif

// Function Prototypes
extern void clkInit(void);
extern void resetCtrl(void);
extern void (*usart1_handler)(void);

int main_queue(void)
{
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

#if __SEMIHOSTING__
    initialise_monitor_handles();
#endif

#if defined(__RTOS__) && defined(__QUEUE_DEMO__)

    xQueue = xQueueCreate(3, sizeof(Data_t));

    if (xQueue != NULL) {

        xTaskCreate(vLedBlink, "LedBlink", 128, NULL, tskIDLE_PRIORITY + 2, NULL);
        xTaskCreate(vSenderTask, "Sender1", 512, &(xStructsToSend[0]), tskIDLE_PRIORITY + 2,
            NULL);
        xTaskCreate(vSenderTask, "Sender2", 512, &(xStructsToSend[1]), tskIDLE_PRIORITY + 2,
            NULL);
        xTaskCreate(vReceiverTask, "Receiver", 512, NULL, tskIDLE_PRIORITY + 1,
            NULL);

        vTaskStartScheduler();
    } else {
    }

#endif

    /* Loop forever */
#if !(defined(__RTOS__))
    while (1) {
#if __SEMIHOSTING__
        printf("Hello World\n");
#endif

        gpio_pin_toggle(GPIOC, 13);
        delay_ms(1000);
    }
#endif
}

#if defined(__RTOS__) && defined(__QUEUE_DEMO__)

static void vLedBlink(void* param)
{
    for (;;) {
        gpio_pin_toggle(GPIOC, 13);
        vTaskDelay(1000);
    }
}

static void vSenderTask(void* param)
{
    BaseType_t xStatus;
    const TickType_t xTicksToWait = pdMS_TO_TICKS(100);

    for (;;) {
        xStatus = xQueueSendToBack(xQueue, param, xTicksToWait);
        if (xStatus != pdPASS) {
            usart_send_string(USART1, "Could not send to the queue.\r\n");
        }
    }

    vTaskDelay(100);
}

static void vReceiverTask(void* param)
{
    Data_t xReceivedStructure;
    BaseType_t xStatus;
    const TickType_t xTickToWait = pdMS_TO_TICKS(50);

    for (;;) {
        if (uxQueueMessagesWaiting(xQueue) != 3) {
            usart_send_string(USART1, "Queue is full!\r\n");
        }

        xStatus = xQueueReceive(xQueue, &xReceivedStructure, xTickToWait);

        if (xStatus == pdPASS) {
            if (xReceivedStructure.eDataSource == eSender1) {
                usart_send_string(USART1, "From sender 1 = ");
                usart_send_string(USART1, xReceivedStructure.ucValue);
                usart_send_string(USART1, "\r\n");

            } else {
                usart_send_string(USART1, "From sender 2 = ");
                usart_send_string(USART1, xReceivedStructure.ucValue);
                usart_send_string(USART1, "\r\n");
            }
        } else {
            usart_send_string(USART1, "Could not receive from the queue.\r\n");
        }
    }
}

void vApplicationIdleHook(void) { ulIdleCycleCount++; }

#endif
