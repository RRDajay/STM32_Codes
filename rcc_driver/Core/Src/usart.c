#include "usart.h"

void usart_clock_enable(void) {
    // Enable USART clock
    RCC->APB2ENR |= (1 << RCC_APB2ENR_USART1EN_Pos);
}

void usart_clock_disable(void) {
    // Disable USART Clock
    RCC->APB2ENR &= ~(1 << RCC_APB2ENR_USART1EN_Pos);
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

    // Enable USART
    usart->CR1 |= (1 << USART_CR1_UE_Pos);

}

uint16_t fractional_baud_rate_generator(uint32_t baudRate) {
    
    double integer, fractional;
    double temp = SystemCoreClock / (16U * (double)baudRate);

    fractional = modf(temp, &integer);
    
    return ((uint16_t) integer << 4) | (uint16_t) (16*fractional);

}

// USART status register helper functions
bool check_status_register(USART_TypeDef *usart, unsigned int pos) {

    if ((usart->SR & (1 << pos)) == 0) {
        return false;
    }

    return true;
}
bool usart_transmit_register_empty_flag(USART_TypeDef *usart){return check_status_register(usart, USART_SR_TXE_Pos);}
bool usart_transmission_complete_flag(USART_TypeDef *usart){return check_status_register(usart, USART_SR_TC_Pos);}
bool usart_read_data_register_not_empty_flag(USART_TypeDef *usart){return check_status_register(usart, USART_SR_RXNE_Pos);}
bool usart_idle_line_flag(USART_TypeDef *usart){return check_status_register(usart, USART_SR_IDLE_Pos);}
bool usart_overrun_error_flag(USART_TypeDef *usart){return check_status_register(usart, USART_SR_ORE_Pos);}
bool usart_noise_error_flag(USART_TypeDef *usart){return check_status_register(usart, USART_SR_NE_Pos);}
bool usart_framing_error_flag(USART_TypeDef *usart){return check_status_register(usart, USART_SR_FE_Pos);}
bool usart_parity_error_flag(USART_TypeDef *usart){return check_status_register(usart, USART_SR_PE_Pos);}

// USART Data Register Helper Functions
void usart_write(USART_TypeDef *usart, uint8_t data) {

    // Check if USART data register is empty
    while(!(usart_transmit_register_empty_flag(usart)));

    // Write data to data register
    usart->DR = data;   

    // Check if USART transmission complete
    while(!(usart_transmission_complete_flag(usart)));

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

    uint8_t temp;

    while(!(usart_read_data_register_not_empty_flag(usart)));

    temp = usart->DR;

    return temp;
}

// USART Interrupts Helper Functions
void usart_enable_irq(USART_TypeDef *usart){
    
    if(usart == USART1) 
        NVIC_EnableIRQ(USART1_IRQn);
    
    if(usart == USART2) 
        NVIC_EnableIRQ(USART2_IRQn);
    
    if(usart == USART3) 
        NVIC_EnableIRQ(USART3_IRQn);

}

void usart_enable_peie(USART_TypeDef *usart){usart->CR1 |= (1 << 8);}
void usart_enable_txeie(USART_TypeDef *usart){usart->CR1 |= (1 << 7);}
void usart_enable_tcie(USART_TypeDef *usart){usart->CR1 |= (1 << 6);}
void usart_enable_rxneie(USART_TypeDef *usart){usart->CR1 |= (1 << 5);}
void usart_enable_idleie(USART_TypeDef *usart){usart->CR1 |= (1 << 4);}

void usart_disable_irq(USART_TypeDef *usart){
    if(usart == USART1) {NVIC_DisableIRQ(USART1_IRQn);}
    if(usart == USART2) {NVIC_DisableIRQ(USART2_IRQn);}
    if(usart == USART3) {NVIC_DisableIRQ(USART3_IRQn);}
}

void usart_disable_peie(USART_TypeDef *usart){usart->CR1 &= ~(1 << 8);}
void usart_disable_txeie(USART_TypeDef *usart){usart->CR1 &= ~(1 << 7);}
void usart_disable_tcie(USART_TypeDef *usart){usart->CR1 &= ~(1 << 6);}
void usart_disable_rxneie(USART_TypeDef *usart){usart->CR1 &= ~(1 << 5);}
void usart_disable_idleie(USART_TypeDef *usart){usart->CR1 &= ~(1 << 4);}

// Interrupt Handlers
void USART1_IRQHandler(void){

}

void USART2_IRQHandler(void){
    
}

void USART3_IRQHandler(void){
    
}