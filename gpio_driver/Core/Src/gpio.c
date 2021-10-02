#include "gpio.h"

void config_output_pin(GPIO_TypeDef *port, uint32_t pinNumber, OUTPUT_MODE_TYPES outputModeTypes, PIN_SPEED pinSpeed)
{
    switch (outputModeTypes)
    {
    case OUTPUT_PP:
        break;
    
    case OUTPUT_OD:
        break;

    case OUTPUT_AF_PP:
        break;
        
    case OUTPUT_AF_OD:
        break;
    
    default:
        break;
    }
}

void config_input_pin(GPIO_TypeDef *port, uint32_t pinNumber, INPUT_MODE_TYPES inputModeTypes)
{
    
}
