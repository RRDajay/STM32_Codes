#ifndef _DMA_H_
#define _DMA_H_

#include "stdbool.h"
#include "stdint.h"
#include "stm32f1xx.h"

typedef enum DMA_CHANNELx {

    CH1 = 0u,
    CH2 = 1u,
    CH3 = 2u,
    CH4 = 3u,
    CH5 = 4u,
    CH6 = 5u,
    CH7 = 6u,

} DMA_CHANNELx;

typedef enum DATA_TRANSFER_DIR {

    READ_FROM_PERIPHERAL = 0u,
    READ_FROM_MEM = 1u,

} DATA_TRANSFER_DIR;

typedef enum DMA_PRIORITY_LEVEL {
    LOW = 0u,
    MEDIUM = 1u,
    HIGH = 2u,
    VERY_HIGH = 3u,
} DMA_PRIORITY_LEVEL;

typedef enum DMA_MEMORY_SIZE {
    BIT8 = 0u,
    BIT16 = 1u,
    BIT32 = 2u
} DMA_MEMORY_SIZE;

// DMA Interrupt Status Register
bool dma_transfer_error_flag(DMA_TypeDef* dmax, DMA_CHANNELx dma_channelx);
bool dma_half_transfer_complete_flag(DMA_TypeDef* dmax, DMA_CHANNELx dma_channelx);
bool dma_transfer_complete_flag(DMA_TypeDef* dmax, DMA_CHANNELx dma_channelx);
bool dma_global_interrupt_flag(DMA_TypeDef* dmax, DMA_CHANNELx dma_channelx);

// DMA Interrupt Flag Clear Register
void dma_clear_transfer_error_flag(DMA_TypeDef* dmax, DMA_CHANNELx dma_channelx);
void dma_clear_half_transfer_complete_flag(DMA_TypeDef* dmax,
    DMA_CHANNELx dma_channelx);
void dma_clear_transfer_complete_flag(DMA_TypeDef* dmax, DMA_CHANNELx dma_channelx);
void dma_clear_global_interrupt_flag(DMA_TypeDef* dmax, DMA_CHANNELx dma_channelx);

// DMA Channel X Configuration Register
void dma_enable_mem2mem(DMA_Channel_TypeDef* dmaChannelX);
void dma_disable_mem2mem(DMA_Channel_TypeDef* dmaChannelX);

void dma_set_channel_priority_level(DMA_Channel_TypeDef* dmaChannelX,
    DMA_PRIORITY_LEVEL priorityLevel);

void dma_set_memory_size(DMA_Channel_TypeDef* dmaChannelX, uint8_t memSize);
void dma_set_peripheral_size(DMA_Channel_TypeDef* dmaChannelX,
    uint8_t peripheralSize);

void dma_enable_minc(DMA_Channel_TypeDef* dmaChannelX);
void dma_disable_minc(DMA_Channel_TypeDef* dmaChannelX);

void dma_enable_pinc(DMA_Channel_TypeDef* dmaChannelX);
void dma_disable_pinc(DMA_Channel_TypeDef* dmaChannelX);

void dma_enable_circ(DMA_Channel_TypeDef* dmaChannelX);
void dma_disable_circ(DMA_Channel_TypeDef* dmaChannelX);

void dma_set_dir(DMA_Channel_TypeDef* dmaChannelX, DATA_TRANSFER_DIR dataDirection);

void dma_enable_teie(DMA_Channel_TypeDef* dmaChannelX);
void dma_disable_teie(DMA_Channel_TypeDef* dmaChannelX);
void dma_enable_htie(DMA_Channel_TypeDef* dmaChannelX);
void dma_disable_htie(DMA_Channel_TypeDef* dmaChannelX);
void dma_enable_tcie(DMA_Channel_TypeDef* dmaChannelX);
void dma_disable_tcie(DMA_Channel_TypeDef* dmaChannelX);
void dma_enable_channel(DMA_Channel_TypeDef* dmaChannelX);
void dma_disable_channel(DMA_Channel_TypeDef* dmaChannelX);

// DMA CNTDR
void dma_set_cntdr(DMA_Channel_TypeDef* dmaChannelX, uint16_t cntdrSize);

// DMA CPAR
void dma_set_cpar(DMA_Channel_TypeDef* dmaChannelX, uint32_t periphAdd);

// DMA CMAR
void dma_set_cmar(DMA_Channel_TypeDef* dmaChannelX, uint32_t memAdd);

#endif // _DMA_H_
