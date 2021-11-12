#ifndef USART_H
#define USART_H

#include "math.h"
#include "stdbool.h"
#include "stdint.h"
#include "stm32f1xx.h"

// USART Configuration Register Helper Functions
void usart_setup(USART_TypeDef* usart, int baudRate);
void usart_enable(USART_TypeDef* usart);
uint16_t
fractional_baud_rate_generator(uint32_t baudRate);

// USART status register helper functions
bool check_status_register(USART_TypeDef* usart, unsigned int pos);
bool usart_transmit_register_empty_flag(USART_TypeDef* usart);
bool usart_transmission_complete_flag(USART_TypeDef* usart);
bool usart_read_data_register_not_empty_flag(USART_TypeDef* usart);
bool usart_idle_line_flag(USART_TypeDef* usart);
bool usart_overrun_error_flag(USART_TypeDef* usart);
bool usart_noise_error_flag(USART_TypeDef* usart);
bool usart_framing_error_flag(USART_TypeDef* usart);
bool usart_parity_error_flag(USART_TypeDef* usart);

// USART Data Register Helper Functions
void usart_send_string(USART_TypeDef* usart, uint8_t* data);
void usart_write(USART_TypeDef* usart, uint8_t data);
void usart_write_IT(USART_TypeDef* usart, uint8_t data);
uint8_t
usart_read(USART_TypeDef* usart);
uint8_t
usart_read_IT(USART_TypeDef* usart);

// USART Interrupts
void usart_enable_irq(USART_TypeDef* usart);
void usart_disable_irq(USART_TypeDef* usart);

// USART1 CR1 Helper Functions
void usart_enable_peie(USART_TypeDef* usart);
void usart_enable_txeie(USART_TypeDef* usart);
void usart_enable_tcie(USART_TypeDef* usart);
void usart_enable_rxneie(USART_TypeDef* usart);
void usart_enable_idleie(USART_TypeDef* usart);
void usart_enable_te(USART_TypeDef* usart);
void usart_enable_re(USART_TypeDef* usart);
void usart_enable_rwe(USART_TypeDef* usart);
void usart_enable_sbk(USART_TypeDef* usart);

void usart_disable_peie(USART_TypeDef* usart);
void usart_disable_txeie(USART_TypeDef* usart);
void usart_disable_tcie(USART_TypeDef* usart);
void usart_disable_rxneie(USART_TypeDef* usart);
void usart_disable_idleie(USART_TypeDef* usart);
void usart_disable_te(USART_TypeDef* usart);
void usart_disable_re(USART_TypeDef* usart);
void usart_disable_rwe(USART_TypeDef* usart);
void usart_disable_sbk(USART_TypeDef* usart);

// USART CR3 Helper Functions
void usart_enable_ctsie(USART_TypeDef* usart);
void usart_enable_ctse(USART_TypeDef* usart);
void usart_enable_rtse_(USART_TypeDef* usart);
void usart_enable_dma_trasmitter(USART_TypeDef* usart);
void usart_enable_dma_receiver(USART_TypeDef* usart);
void usart_enable_scen(USART_TypeDef* usart);
void usart_enable_nack(USART_TypeDef* usart);
void usart_enable_hdsel(USART_TypeDef* usart);
void usart_enable_irlp(USART_TypeDef* usart);
void usart_enable_iren(USART_TypeDef* usart);
void usart_enable_eie(USART_TypeDef* usart);

void usart_disable_ctsie(USART_TypeDef* usart);
void usart_disable_ctse(USART_TypeDef* usart);
void usart_disable_rtse_(USART_TypeDef* usart);
void usart_disable_dma_trasmitter(USART_TypeDef* usart);
void usart_disable_dma_receiver(USART_TypeDef* usart);
void usart_disable_scen(USART_TypeDef* usart);
void usart_disable_nack(USART_TypeDef* usart);
void usart_disable_hdsel(USART_TypeDef* usart);
void usart_disable_irlp(USART_TypeDef* usart);
void usart_disable_iren(USART_TypeDef* usart);
void usart_disable_eie(USART_TypeDef* usart);

#endif
