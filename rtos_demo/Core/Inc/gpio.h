#ifndef GPIO_H
#define GPIO_H

#include "stm32f1xx.h"
#include "stdbool.h"

// Pin Mode
typedef enum {
    OUTPUT,
    INPUT
} PIN_MODES;

// Input Mode Types
typedef enum  {
    ANALOG_MODE,
    FLOATING_INPUT,
    INPUT_PU_PD,
    RESERVED
} INPUT_MODE_TYPES;

// Output Mode Types
typedef enum  {
    OUTPUT_PP, 
    OUTPUT_OD, 
    OUTPUT_AF_PP, 
    OUTPUT_AF_OD
} OUTPUT_MODE_TYPES;

// Pin Speeds
typedef enum  {
    INPUT_MODE,
    S10,
    S2,
    S50
} PIN_SPEED;

// Clock Enabling
void gpio_clock_enable_af(void);     
void gpio_clock_enable_porta(void);
void gpio_clock_enable_portb(void);
void gpio_clock_enable_portc(void);
void gpio_clock_enable_portd(void);
void gpio_clock_enable_porte(void);

// Functions for pin configuration
void gpio_config_output_pin(GPIO_TypeDef *port, uint8_t pinNumber, OUTPUT_MODE_TYPES outputModeTypes, PIN_SPEED pinSpeed);
void gpio_config_input_pin(GPIO_TypeDef *port, uint8_t pinNumber, INPUT_MODE_TYPES inputModeTypes);

// Functions for pin output
void gpio_pin_reset(GPIO_TypeDef *port, uint8_t pinNumber);
void gpio_pin_set(GPIO_TypeDef *port, uint8_t pinNumber);
void gpio_pin_toggle(GPIO_TypeDef *port, uint8_t pinNumner);

// Functions for pin input
_Bool gpio_pin_read(GPIO_TypeDef *port, uint8_t pinNumber);

#endif