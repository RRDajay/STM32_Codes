#include "dma.h"

// DMA Interrupt Status Register
bool dma_transfer_error_flag(DMA_TypeDef* dmax, DMA_CHANNELx dma_channelx)
{
    volatile uint32_t transferStatus = (dmax->ISR & (1u << (0x03 + 4 * dma_channelx))) >> (0x03 + 4 * dma_channelx);

    if (transferStatus == 1u)
        return true;

    return false;
}

bool dma_half_transfer_complete_flag(DMA_TypeDef* dmax, DMA_CHANNELx dma_channelx)
{
    volatile uint32_t transferStatus = (dmax->ISR & (1u << (0x02 + 4 * dma_channelx))) >> (0x02 + 4 * dma_channelx);

    if (transferStatus == 1u)
        return true;

    return false;
}

bool dma_transfer_complete_flag(DMA_TypeDef* dmax, DMA_CHANNELx dma_channelx)
{
    volatile uint32_t transferStatus = (dmax->ISR & (1u << (0x01 + 4 * dma_channelx))) >> (0x01 + 4 * dma_channelx);

    if (transferStatus == 1u)
        return true;

    return false;
}

bool dma_global_interrupt_flag(DMA_TypeDef* dmax, DMA_CHANNELx dma_channelx)
{
    volatile uint32_t transferStatus = (dmax->ISR & (1u << (0x00 + 4 * dma_channelx))) >> (0x00 + 4 * dma_channelx);

    if (transferStatus == 1u)
        return true;

    return false;
}

// DMA Interrupt Flag Clear Register
void dma_clear_transfer_error_flag(DMA_TypeDef* dmax, DMA_CHANNELx dma_channelx)
{
    dmax->IFCR |= (1u << (0x03 + 4 * dma_channelx));
}

void dma_clear_half_transfer_complete_flag(DMA_TypeDef* dmax,
    DMA_CHANNELx dma_channelx)
{
    dmax->IFCR |= (1u << (0x02 + 4 * dma_channelx));
}

void dma_clear_transfer_complete_flag(DMA_TypeDef* dmax, DMA_CHANNELx dma_channelx)
{
    dmax->IFCR |= (1u << (0x01 + 4 * dma_channelx));
}

void dma_clear_global_interrupt_flag(DMA_TypeDef* dmax, DMA_CHANNELx dma_channelx)
{
    dmax->IFCR |= (1u << (0x00 + 4 * dma_channelx));
}

// DMA Channel X Configuration Register
void dma_enable_mem2mem(DMA_Channel_TypeDef* dmaChannelX)
{
    dmaChannelX->CCR &= ~(1u << 14u);
    dmaChannelX->CCR |= (1u << 14u);
}
void dma_disable_mem2mem(DMA_Channel_TypeDef* dmaChannelX)
{
    dmaChannelX->CCR &= ~(1u << 14u);
}

void dma_set_channel_priority_level(DMA_Channel_TypeDef* dmaChannelX,
    DMA_PRIORITY_LEVEL priorityLevel)
{
    dmaChannelX->CCR &= ~(3u << 12u);
    if (priorityLevel == LOW)
        dmaChannelX->CCR |= (LOW << 12u);
    if (priorityLevel == MEDIUM)
        dmaChannelX->CCR |= (MEDIUM << 12u);
    if (priorityLevel == HIGH)
        dmaChannelX->CCR |= (HIGH << 12u);
    if (priorityLevel == VERY_HIGH)
        dmaChannelX->CCR |= (VERY_HIGH << 12u);
}

void dma_set_memory_size(DMA_Channel_TypeDef* dmaChannelX, DMA_MEMORY_SIZE memSize)
{
    dmaChannelX->CCR &= ~(3u << 10u);
    if (memSize == BIT8)
        dmaChannelX->CCR |= BIT8 << 10u;
    if (memSize == BIT16)
        dmaChannelX->CCR |= BIT16 << 10u;
    if (memSize == BIT32)
        dmaChannelX->CCR |= BIT32 << 10u;
}

void dma_set_peripheral_size(DMA_Channel_TypeDef* dmaChannelX,
    DMA_MEMORY_SIZE peripheralSize)
{
    dmaChannelX->CCR &= ~(3u << 8u);
    if (peripheralSize == BIT8)
        dmaChannelX->CCR |= BIT8 << 8u;
    if (peripheralSize == BIT16)
        dmaChannelX->CCR |= BIT16 << 8u;
    if (peripheralSize == BIT32)
        dmaChannelX->CCR |= BIT32 << 8u;
}

void dma_enable_minc(DMA_Channel_TypeDef* dmaChannelX)
{
    dmaChannelX->CCR |= (1u << 7u);
}
void dma_disable_minc(DMA_Channel_TypeDef* dmaChannelX)
{
    dmaChannelX->CCR &= ~(1u << 7u);
}

void dma_enable_pinc(DMA_Channel_TypeDef* dmaChannelX)
{
    dmaChannelX->CCR |= (1u << 6u);
}
void dma_disable_pinc(DMA_Channel_TypeDef* dmaChannelX)
{
    dmaChannelX->CCR &= ~(1u << 6u);
}

void dma_enable_circ(DMA_Channel_TypeDef* dmaChannelX)
{
    dmaChannelX->CCR |= (1u << 5u);
}
void dma_disable_circ(DMA_Channel_TypeDef* dmaChannelX)
{
    dmaChannelX->CCR &= ~(1u << 5u);
}

void dma_set_dir(DMA_Channel_TypeDef* dmaChannelX, DATA_TRANSFER_DIR dataDirection)
{
    dmaChannelX->CCR &= ~(3u << 4u);

    if (dataDirection == READ_FROM_PERIPHERAL)
        dmaChannelX->CCR |= READ_FROM_PERIPHERAL << 4u;

    if (dataDirection == READ_FROM_MEM)
        dmaChannelX->CCR |= READ_FROM_MEM << 4u;
}

void dma_enable_teie(DMA_Channel_TypeDef* dmaChannelX)
{
    dmaChannelX->CCR |= (1u << 3u);
}

void dma_disable_teie(DMA_Channel_TypeDef* dmaChannelX)
{
    dmaChannelX->CCR &= ~(1u << 3u);
}

void dma_enable_htie(DMA_Channel_TypeDef* dmaChannelX)
{
    dmaChannelX->CCR |= (1u << 2u);
}

void dma_disable_htie(DMA_Channel_TypeDef* dmaChannelX)
{
    dmaChannelX->CCR &= ~(1u << 2u);
}

void dma_enable_tcie(DMA_Channel_TypeDef* dmaChannelX)
{
    dmaChannelX->CCR |= (1u << 1u);
}

void dma_disable_tcie(DMA_Channel_TypeDef* dmaChannelX)
{
    dmaChannelX->CCR &= ~(1u << 1u);
}

void dma_enable_channel(DMA_Channel_TypeDef* dmaChannelX)
{
    dmaChannelX->CCR |= (1u << 0u);
}

void dma_disable_channel(DMA_Channel_TypeDef* dmaChannelX)
{
    dmaChannelX->CCR &= ~(1u << 0u);
}

// DMA CNTDR
void dma_set_cntdr(DMA_Channel_TypeDef* dmaChannelX, uint16_t cntdrSize)
{
    dmaChannelX->CNDTR = cntdrSize;
}

// DMA CPAR
void dma_set_cpar(DMA_Channel_TypeDef* dmaChannelX, uint32_t periphAdd)
{
    dmaChannelX->CPAR = periphAdd;
}

// DMA CMAR
void dma_set_cmar(DMA_Channel_TypeDef* dmaChannelX, uint32_t memAdd)
{
    dmaChannelX->CMAR = memAdd;
}
