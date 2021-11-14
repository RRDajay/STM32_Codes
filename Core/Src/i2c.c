#include "i2c.h"

uint8_t receiveBuffer[BUFFER_SIZE];
static uint8_t receiveSize;
static uint8_t* data;
static uint8_t receiveBufferIndex;
static uint8_t address;
// static uint8_t

static void receiveBufferPut(uint8_t data)
{
    if (receiveBufferIndex == BUFFER_SIZE) {
        receiveBufferIndex = 0;
        ;
    }

    receiveBuffer[receiveBufferIndex] = data;

    receiveBufferIndex++;
}

void i2c_set_transmit_data(uint8_t* _data) { data = _data; }

// I2C Clock Control Setup
void i2c_init(I2C_TypeDef* i2cx, uint8_t i2c_mode, uint32_t _apb1_clk)
{
    // I2C Reset
    i2c_sw_reset(i2cx);

    // Gets the APB1 clock value used by the I2C registers
    uint32_t apb1_clk = _apb1_clk;

    // Divide the APB1 clock to get the whole number since CR2 only accepts
    // between 2 - 50
    while (!(apb1_clk % 10)) {
        apb1_clk /= 10;
    }

    i2cx->CR2 |= (apb1_clk << 0U);

    if (i2c_mode == I2C_SM_MODE) {
        // Set I2C to standard mode
        i2cx->CCR &= ~(1U << 15U);

        // Calculate value for Clock Control Register
        float ccr_value = (I2C_T_R_SM_MODE + I2C_T_W_SCLH_SM_MODE) * _apb1_clk;
        i2cx->CCR |= (uint16_t)ccr_value;

        uint8_t trise_value = (I2C_T_R_SM_MODE * _apb1_clk) + 1;
        i2cx->TRISE = (uint8_t)trise_value;
    }
}
void i2c_enable(I2C_TypeDef* i2cx) { i2cx->CR1 |= (1U << 0U); }
void i2c_disable(I2C_TypeDef* i2cx) { i2cx->CR1 &= ~(1U << 0U); }
void i2c_sw_reset(I2C_TypeDef* i2cx)
{
    i2cx->CR1 |= (1U << 15U);
    i2cx->CR1 &= ~(1U << 15U);
}
void i2c_dma_last_transfer(I2C_TypeDef* i2cx)
{
    i2cx->CR2 |= 1U << 12U;
} // next dma eot is the last transfer
void i2c_dma_not_last_transfer(I2C_TypeDef* i2cx)
{
    i2cx->CR2 &= (1U << 12U);
} // next DMA eot is not the last transfer

// I2C Communication Flow Helper Functions
void i2c_master_write_data(I2C_TypeDef* i2cx, uint8_t* _data, uint8_t size, uint8_t address)
{
    data = _data;

    i2cx->CR1 |= (1U << 10U); // Acknowledge enable
    i2cx->CR1 |= (1U << 8U); // Generate Start

    while (!i2c_start_bit_flag(i2cx)) { }; // Check if SB bit is set

    i2cx->DR = address << 1; // Write address to data register

    while (!(i2c_address_flag(i2cx))) { }; // Check if address is sent

    uint16_t temp = i2cx->SR1 | i2cx->SR2; // Clear ADDR flag by reading SR1 and SR2

    for (int i = 0; i < size; i++) {
        while (!(i2cx->SR1 & (1U << 7U))) { }; // Check if data register is empty
        i2cx->DR = *data; // Write data to register
        data++;
    }

    while (!((i2cx->SR1 & (1U << 2U)))) { }; // Check if BTF is set

    i2cx->CR1 |= (1U << 9U); // Generate Stop Condition
}

void i2c_master_read_data(I2C_TypeDef* i2cx, uint8_t size, uint8_t _address)
{
    i2cx->CR1 |= (1U << 10U); // Acknowledge enable
    i2cx->CR1 |= (1U << 8U); // Generate Start

    while (!i2c_start_bit_flag(i2cx)) { }; // Check if SB bit is set

    i2cx->DR = _address << 1 | 1; // Write address to data register

    while (!(i2c_address_flag(i2cx))) { }; // Check if address is sent

    uint16_t dummyRead = i2cx->SR1 | i2cx->SR2; // Clear ADDR flag by reading SR1 and SR2

    if (size >= 2) {

        for (size_t i = 0; i < size - 2; i++) {

            while (!i2c_receiver_not_empty_flag(I2C1)) { } // Check if data register is not empty
            volatile uint8_t temp = i2cx->DR;
            receiveBufferPut(temp);
        }
    }

    i2cx->CR1 &= ~(1U << 10U); // Acknowledge disable
    i2cx->CR1 |= (1U << 9U); // Generate Stop Condition

    while (!i2c_receiver_not_empty_flag(I2C1))
        ;

    receiveBufferPut(i2cx->DR);
}
void i2c_master_write_data_it(I2C_TypeDef* i2cx, uint8_t* _data, uint8_t _address)
{

    data = _data;
    address = _address << 1;

    // Acknowledge enable
    i2cx->CR1 |= (1U << 10U);

    // Generate Start
    i2cx->CR1 |= (1U << 8U);
}

void i2c_master_read_data_it(I2C_TypeDef* i2cx, uint8_t size, uint8_t _address)
{
    receiveSize = size;
    address = _address << 1 | 1;

    // Acknowledge enable
    i2cx->CR1 |= (1U << 10U);

    // Generate Start
    i2cx->CR1 |= (1U << 8U);
}

// void i2c_master_write_it(I2C_TypeDef* i2cx) { i2cx->DR = address << 1; }
// void i2c_master_read_it(I2C_TypeDef* i2cx) { i2cx->DR = (address << 1) | 1; }
// void i2c_master_read_data_it(I2C_TypeDef* i2cx) { uint8_t temp = i2cx->DR; }
// void i2c_master_send_data_it(I2C_TypeDef* i2cx) { i2cx->DR = *data; }
// void i2c_master_stop_it(I2C_TypeDef* i2cx) { i2cx->CR1 |= (1U << 9U); }

// I2C Interrupts
void i2c_dma_enable(I2C_TypeDef* i2cx)
{
    i2cx->CR2 |= 1U << 11U;
} // enable DMA requests
void i2c_itbuf_enable(I2C_TypeDef* i2cx)
{
    i2cx->CR2 |= 1U << 10U;
} // enable buffer interrupts
void i2c_itevt_enable(I2C_TypeDef* i2cx)
{
    i2cx->CR2 |= 1U << 9U;
} // enable event interrupts
void i2c_iterr_enable(I2C_TypeDef* i2cx)
{
    i2cx->CR2 |= 1U << 8U;
} // enable error interrupts

void i2c_dma_disable(I2C_TypeDef* i2cx)
{
    i2cx->CR2 &= ~(1U << 11U);
} // disable DMA requests
void i2c_itbuf_disable(I2C_TypeDef* i2cx)
{
    i2cx->CR2 &= ~(1U << 10U);
} // disable buffer interrupts
void i2c_itevt_disable(I2C_TypeDef* i2cx)
{
    i2cx->CR2 &= ~(1U << 9U);
} // disable event interrupts
void i2c_iterr_disable(I2C_TypeDef* i2cx)
{
    i2cx->CR2 &= ~(1U << 8U);
} // disable error interrupts

// I2C Check Flags
bool i2c_start_bit_flag(I2C_TypeDef* i2cx)
{
    return i2cx->SR1 & (1U << 0U) ? 1 : 0;
} // check if sb is set
bool i2c_address_flag(I2C_TypeDef* i2cx)
{
    return i2cx->SR1 & (1U << 1U) ? 1 : 0;
} // check if addr is set
bool i2c_byte_transfer_flag(I2C_TypeDef* i2cx)
{
    return i2cx->SR1 & (1U << 2U) ? 1 : 0;
} // check if btf is set
bool i2c_receiver_not_empty_flag(I2C_TypeDef* i2cx)
{
    return i2cx->SR1 & (1U << 6U) ? 1 : 0;
} // check if rxne is set
bool i2c_trasmitter_empty_flag(I2C_TypeDef* i2cx)
{
    return i2cx->SR1 & (1U << 7U) ? 1 : 0;
} // check if txe is set
bool i2c_acknowledge_flag(I2C_TypeDef* i2cx)
{
    return i2cx->SR1 & (1U << 10U) ? 1 : 0;
} // check if af is set

// I2C Interrupt Handler

void I2C1_EV_IRQHandler(void)
{
    if (i2c_start_bit_flag(I2C1)) {
        I2C1->DR = address;
    }

    if (i2c_address_flag(I2C1)) {
        // I2C1->CR1 &= ~(1u << 10u);
        uint16_t dummyRead = I2C1->SR1 | I2C1->SR2;
        // I2C1->CR1 |= 1u << 9u;
    }

    if (i2c_trasmitter_empty_flag(I2C1)) {
        if (*data) {
            I2C1->DR = *data;
            data++;
        } else {
            I2C1->CR1 |= (1U << 9U); // Generate Stop Condition
        }
    }

    if (i2c_receiver_not_empty_flag(I2C1)) {
        if (receiveSize > 3) {
            volatile uint8_t temp = I2C1->DR;
            receiveBufferPut(I2C1->DR);
            receiveSize--;
        } else {
            I2C1->CR1 &= ~(1U << 10U); // Acknowledge disable
            I2C1->CR1 |= (1U << 9U); // Generate Stop Condition
            receiveBufferPut(I2C1->DR);
        }
    }
}

void I2C1_ER_IRQHandler(void)
{
    // Check if acknowledge failure
    if (i2c_acknowledge_flag(I2C1)) {
        // i2c_master_stop_it(I2C1);
    }
}
