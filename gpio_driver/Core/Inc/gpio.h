#ifndef GPIO_H
#define GPIO_H

#include "stm32f1xx.h"

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
#define GPIO_CLOCK_ENABLE_ALT_FUNCT         (RCC->APB2ENR |= 1 << RCC_APB2ENR_AFIOEN_Pos)     
#define GPIO_CLOCK_ENABLE_PORTA             (RCC->APB2ENR |= 1 << RCC_APB2ENR_IOPAEN_Pos)
#define GPIO_CLOCK_ENABLE_PORTB             (RCC->APB2ENR |= 1 << RCC_APB2ENR_IOPBEN_Pos)
#define GPIO_CLOCK_ENABLE_PORTC             (RCC->APB2ENR |= 1 << RCC_APB2ENR_IOPCEN_Pos)
#define GPIO_CLOCK_ENABLE_PORTD             (RCC->APB2ENR |= 1 << RCC_APB2ENR_IOPDEN_Pos)
#define GPIO_CLOCK_ENABLE_PORTE             (RCC->APB2ENR |= 1 << RCC_APB2ENR_IOPEEN_Pos)

void config_output_pin(GPIO_TypeDef *port, uint32_t pinNumber, OUTPUT_MODE_TYPES outputModeTypes, PIN_SPEED pinSpeed);
void config_input_pin(GPIO_TypeDef *port, uint32_t pinNumber, INPUT_MODE_TYPES inputModeTypes);

#endif