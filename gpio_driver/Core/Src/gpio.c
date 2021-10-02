#include "gpio.h"

uint32_t PINPOS[16] = {
    // For CRL
    (0x00),(0x04),(0x08),(0x0C),(0x10),(0x14),(0x18),(0x1C),
    // For CRH
    (0x00),(0x04),(0x08),(0x0C),(0x10),(0x14),(0x18),(0x1C)
};

void config_output_pin(GPIO_TypeDef *port, uint32_t pinNumber, OUTPUT_MODE_TYPES outputModeTypes, PIN_SPEED pinSpeed)
{
    if (pinNumber >= 8) 
    {
            switch (outputModeTypes)
            {
                case OUTPUT_PP:
                    port->CRH &= ~((1 << (PINPOS[pinNumber]+2)) | (1 << PINPOS[pinNumber]));
                    port->CRH |= ((OUTPUT_PP << (PINPOS[pinNumber]+2)) | (pinSpeed << PINPOS[pinNumber]));
                    break;
                
                case OUTPUT_OD:
                    port->CRH &= ~((1 << (PINPOS[pinNumber]+2)) | (1 << PINPOS[pinNumber]));
                    port->CRH |= ((OUTPUT_OD << (PINPOS[pinNumber]+2)) | (pinSpeed << PINPOS[pinNumber]));
                    break;

                case OUTPUT_AF_PP:
                    port->CRH &= ~((1 << (PINPOS[pinNumber]+2)) | (1 << PINPOS[pinNumber]));
                    port->CRH |= ((OUTPUT_AF_PP << (PINPOS[pinNumber]+2)) | (pinSpeed << PINPOS[pinNumber]));
                    break;

                case OUTPUT_AF_OD:
                    port->CRH &= ~((1 << (PINPOS[pinNumber]+2)) | (1 << PINPOS[pinNumber]));
                    port->CRH |= ((OUTPUT_AF_OD << (PINPOS[pinNumber]+2)) | (pinSpeed << PINPOS[pinNumber]));
                    break;
                
                default:
                    break;
            }
    }

    else 
    {
            switch (outputModeTypes)
            {
                case OUTPUT_PP:
                    port->CRH &= ~((1 << (PINPOS[pinNumber]+2)) | (1 << PINPOS[pinNumber]));
                    port->CRH |= ((OUTPUT_PP << (PINPOS[pinNumber]+2)) | (pinSpeed << PINPOS[pinNumber]));
                    break;
                
                case OUTPUT_OD:
                    port->CRH &= ~((1 << (PINPOS[pinNumber]+2)) | (1 << PINPOS[pinNumber]));
                    port->CRH |= ((OUTPUT_OD << (PINPOS[pinNumber]+2)) | (pinSpeed << PINPOS[pinNumber]));
                    break;

                case OUTPUT_AF_PP:
                    port->CRH &= ~((1 << (PINPOS[pinNumber]+2)) | (1 << PINPOS[pinNumber]));
                    port->CRH |= ((OUTPUT_AF_PP << (PINPOS[pinNumber]+2)) | (pinSpeed << PINPOS[pinNumber]));
                    break;

                case OUTPUT_AF_OD:
                    port->CRH &= ~((1 << (PINPOS[pinNumber]+2)) | (1 << PINPOS[pinNumber]));
                    port->CRH |= ((OUTPUT_AF_OD << (PINPOS[pinNumber]+2)) | (pinSpeed << PINPOS[pinNumber]));
                    break;
                
                default:
                    break;
            }
    }
}

void config_input_pin(GPIO_TypeDef *port, uint32_t pinNumber, INPUT_MODE_TYPES inputModeTypes)
{
    
}
