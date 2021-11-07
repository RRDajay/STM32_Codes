#include "usart.h"


void usart_clock_enable(void) {
    // Enable USART clock
    RCC->APB2ENR |= (1 << RCC_APB2ENR_USART1EN_Pos);
}

void usart_clock_disable(void) {
    // Disable USART Clock
    RCC->APB2ENR &= ~(1 << RCC_APB2ENR_USART1EN_Pos);
}

void usart_enable(USART_TypeDef *usart) {
    // Enable USART
    usart->CR1 |= (1 << USART_CR1_UE_Pos);
}

void usart_setup(USART_TypeDef *usart, int baudRate) {

    // default configurations
    // 1 start bit, 8 data bits, 1 stop bit
    
    // configure baud rate
    usart->BRR = fractional_baud_rate_generator(baudRate);

    // Enable Transmitter
    usart->CR1 |= (1 << USART_CR1_TE_Pos);

    // Enable Receiver
    usart->CR1 |= (1 << USART_CR1_RE_Pos);



}

uint16_t fractional_baud_rate_generator(uint32_t baudRate) {
    
    SystemCoreClockUpdate();

    double integer, fractional;
    double temp = SystemCoreClock / (16U * (double)baudRate);

    fractional = modf(temp, &integer);
    
    return ((uint16_t) integer << 4) | (uint16_t) (16*fractional);

}

// USART status register helper functions
bool check_status_register(USART_TypeDef *usart, unsigned int pos) {

    if (((usart->SR & (1U << pos)) >> pos) == 1) {
        return true;
    }

    return false;
}

bool usart_transmit_register_empty_flag(USART_TypeDef *usart){return check_status_register(usart, 7U);}
bool usart_transmission_complete_flag(USART_TypeDef *usart){return check_status_register(usart, 6U);}
bool usart_read_data_register_not_empty_flag(USART_TypeDef *usart){return check_status_register(usart, 5U);}
bool usart_idle_line_flag(USART_TypeDef *usart){return check_status_register(usart, 4U);}
bool usart_overrun_error_flag(USART_TypeDef *usart){return check_status_register(usart, 3U);}
bool usart_noise_error_flag(USART_TypeDef *usart){return check_status_register(usart, 2U);}
bool usart_framing_error_flag(USART_TypeDef *usart){return check_status_register(usart, 1U);}
bool usart_parity_error_flag(USART_TypeDef *usart){return check_status_register(usart, 0U);}

// USART Data Register Helper Functions
void usart_write(USART_TypeDef *usart, uint8_t data) {

    // Check if USART data register is empty
    while(!(usart_transmit_register_empty_flag(usart)));

    // Write data to data register
    usart->DR = data;   

    // Check if USART transmission complete
    while(!(usart_transmission_complete_flag(usart)));

}

void usart_write_IT(USART_TypeDef *usart, uint8_t data) {

    // Check if USART data register is empty
    // while(!(usart_transmit_register_empty_flag(usart)));

    // Write data to data register
    usart->DR = data;   

    // Check if USART transmission complete
    // while(!(usart_transmission_complete_flag(usart)));

}


void usart_send_string(USART_TypeDef *usart, uint8_t* data) {

    // Check if dereferenced data is not null pointer
    while(*data) {

        // Characters in the array are written to the data register one by one
        usart_write(usart, *data);
        
        //Increment pointer
        data++;
    }

}

uint8_t usart_read(USART_TypeDef *usart) {

    while(!(usart_read_data_register_not_empty_flag(usart)));

    volatile uint8_t temp = usart->DR;

    return temp;
}

uint8_t usart_read_IT(USART_TypeDef *usart) {

    // while(!(usart_read_data_register_not_empty_flag(usart)));

    volatile uint8_t temp = usart->DR;

    return temp;
}

// USART Interrupts Helper Functions
void usart_enable_irq(USART_TypeDef *usart){
    
    if(usart == USART1) NVIC_EnableIRQ(USART1_IRQn);
    if(usart == USART2) NVIC_EnableIRQ(USART2_IRQn);
    if(usart == USART3) NVIC_EnableIRQ(USART3_IRQn);

}

void usart_enable_peie(USART_TypeDef *usart){usart->CR1 |= (1U << 8U);}
void usart_enable_txeie(USART_TypeDef *usart){usart->CR1 |= (1U << 7U);}
void usart_enable_tcie(USART_TypeDef *usart){usart->CR1 |= (1U << 6U);}
void usart_enable_rxneie(USART_TypeDef *usart){usart->CR1 |= (1U << 5U);}
void usart_enable_idleie(USART_TypeDef *usart){usart->CR1 |= (1U << 4U);}

void usart_disable_irq(USART_TypeDef *usart){
    
    if(usart == USART1) NVIC_DisableIRQ(USART1_IRQn);
    if(usart == USART2) NVIC_DisableIRQ(USART2_IRQn);
    if(usart == USART3) NVIC_DisableIRQ(USART3_IRQn);
        
}

void usart_disable_peie(USART_TypeDef *usart){usart->CR1 &= ~(1U << 8U);}
void usart_disable_txeie(USART_TypeDef *usart){usart->CR1 &= ~(1U << 7U);}
void usart_disable_tcie(USART_TypeDef *usart){usart->CR1 &= ~(1U << 6U);}
void usart_disable_rxneie(USART_TypeDef *usart){usart->CR1 &= ~(1U << 5U);}
void usart_disable_idleie(USART_TypeDef *usart){usart->CR1 &= ~(1U << 4U);}

void (*usart1_handler)(void);
void (*usart2_handler)(void);
void (*usart3_handler)(void);
// Interrupt Handlers
void USART1_IRQHandler(void){
    
    if(usart1_handler) {
        usart1_handler();
    }
}

void USART2_IRQHandler(void){
    
}

void USART3_IRQHandler(void){
    
}