#include "i2c.h"

static uint8_t* data;
static uint8_t receiveBuffer[128];
static uint8_t address;


void i2c_set_data(uint8_t* _data) { data = _data; }
void i2c_set_slave_address(uint8_t _address) {address = _address; }

// I2C Clock Control Setup
void i2c_init(I2C_TypeDef *i2cx, uint8_t i2c_mode, uint32_t _apb1_clk) {

    // I2C Reset
    i2c_sw_reset(i2cx);

    // Gets the APB1 clock value used by the I2C registers
    uint32_t apb1_clk = _apb1_clk;

    // Divide the APB1 clock to get the whole number since CR2 only accepts between 2 - 50
    while(!(apb1_clk % 10)) {
        apb1_clk /= 10;
    }

    i2cx->CR2 |= (apb1_clk << 0U); 

    if (i2c_mode == I2C_SM_MODE) {
        
        // Set I2C to standard mode
        i2cx->CCR &= ~(1U << 15U);

        // Calculate value for Clock Control Register
        float ccr_value = (I2C_T_R_SM_MODE + I2C_T_W_SCLH_SM_MODE) * _apb1_clk;
        i2cx->CCR |= (uint16_t) ccr_value;

        uint8_t trise_value = (I2C_T_R_SM_MODE * _apb1_clk) + 1;
        i2cx->TRISE = (uint8_t) trise_value;

    }

}
void i2c_enable(I2C_TypeDef *i2cx){i2cx->CR1 |= (1U << 0U); }
void i2c_disable(I2C_TypeDef *i2cx){i2cx->CR1 &= ~(1U << 0U); }
void i2c_sw_reset(I2C_TypeDef *i2cx) {
        i2cx->CR1 |= (1U << 15U);
        i2cx->CR1 &= ~(1U << 15U);
}
void i2c_dma_last_transfer(I2C_TypeDef *i2cx) {i2cx->CR2 |= 1U << 12U; }// next dma eot is the last transfer
void i2c_dma_not_last_transfer(I2C_TypeDef *i2cx) {i2cx->CR2 &= (1U << 12U); } // next DMA eot is not the last transfer

// I2C Communication Flow Helper Functions
void i2c_start(I2C_TypeDef *i2cx) {
    // Acknowledge enable
    i2cx->CR1 |= (1U << 10U);

    // Generate Start
    i2cx->CR1 |= (1U << 8U);
}
void i2c_write(I2C_TypeDef *i2cx) {

    // // Check is SB bit is set
    while(!i2c_sb(i2cx));

    // Write address to data register
    i2cx->DR = address<<1;

    // // Check if address is sent
    while(!(i2c_addr(i2cx)));

    // Clear ADDR flag by reading SR1 and SR2
    uint16_t temp = i2cx->SR1 | i2cx->SR2;
}
void i2c_read(I2C_TypeDef *i2cx) {
    
    // // Check is SB bit is set
    while(!i2c_sb(i2cx));

    // Write address to data register
    i2cx->DR = (address << 1 ) | 1;

    // // Check if address is sent
    while(!(i2c_addr(i2cx) || i2c_af(i2cx)));

    // Clear ADDR flag by reading SR1 and SR2
    uint16_t temp = i2cx->SR1 | i2cx->SR2;
}
void i2c_read_data(I2C_TypeDef *i2cx) {
    
    // Check if receive data register is not empty
    while(!(i2c_rxne(i2cx)));

    // Read data from register
    uint8_t temp = i2cx->DR;
}

void i2c_send_data(I2C_TypeDef *i2cx) {
    // Check if data register is empty
    while(!(i2cx->SR1 & (1U << 7U)));

    // Write data to register
    i2cx->DR = *data;

    // Check if BTF is set
    while(!((i2cx->SR1 & (1U << 2U))));
}
void i2c_stop(I2C_TypeDef *i2cx) {
    i2cx->CR1 |= (1U << 9U);
}

void i2c_start_it(I2C_TypeDef *i2cx) {
    // Acknowledge enable
    i2cx->CR1 |= (1U << 10U);

    // Generate Start
    i2cx->CR1 |= (1U << 8U);
}
void i2c_write_it(I2C_TypeDef *i2cx) { i2cx->DR = address<<1; }
void i2c_read_it(I2C_TypeDef *i2cx) { i2cx->DR = (address << 1 ) | 1; }
void i2c_read_data_it(I2C_TypeDef *i2cx) { uint8_t temp = i2cx->DR; }
void i2c_send_data_it(I2C_TypeDef *i2cx) { i2cx->DR = *data; }
void i2c_stop_it(I2C_TypeDef *i2cx) { i2cx->CR1 |= (1U << 9U); }

// I2C Interrupts
void i2c_dmaen_enable(I2C_TypeDef *i2cx) {i2cx->CR2 |= 1U << 11U; } // enable DMA requests
void i2c_itbufen_enable(I2C_TypeDef *i2cx) {i2cx->CR2 |= 1U << 10U; } // enable buffer interrupts
void i2c_itevten_enable(I2C_TypeDef *i2cx) {i2cx->CR2 |= 1U << 9U; } // enable event interrupts
void i2c_iterren_enable(I2C_TypeDef *i2cx) {i2cx->CR2 |= 1U << 8U; } // enable error interrupts

void i2c_dmaen_disable(I2C_TypeDef *i2cx) {i2cx->CR2 &= ~(1U << 11U); } // disable DMA requests
void i2c_itbufen_disable(I2C_TypeDef *i2cx) {i2cx->CR2 &= ~(1U << 10U); } // disable buffer interrupts
void i2c_itevten_disable(I2C_TypeDef *i2cx) {i2cx->CR2 &= ~(1U << 9U); } // disable event interrupts
void i2c_iterren_disable(I2C_TypeDef *i2cx) {i2cx->CR2 &= ~(1U << 8U); } // disable error interrupts

// I2C Check Flags
bool i2c_sb(I2C_TypeDef *i2cx) { return i2cx->SR1 & (1U << 0U) ? 1 : 0 ; }          // check if sb is set
bool i2c_addr(I2C_TypeDef *i2cx) { return i2cx->SR1 & (1U << 1U) ? 1 : 0 ; }        // check if addr is set
bool i2c_btf(I2C_TypeDef *i2cx) { return i2cx->SR1 & (1U << 2U) ? 1 : 0 ; }         // check if btf is set
bool i2c_rxne(I2C_TypeDef *i2cx) { return i2cx->SR1 & (1U << 6U) ? 1 : 0; }         // check if rxne is set
bool i2c_txe(I2C_TypeDef *i2cx) { return i2cx->SR1 & (1U << 7U) ? 1 : 0 ; }         // check if txe is set
bool i2c_af(I2C_TypeDef *i2cx) { return i2cx->SR1 & (1U << 10U) ? 1 : 0 ; }         // check if af is set


// I2C Interrupt Handler

void I2C1_EV_IRQHandler(void) {

    // Check if btf bit is set
    // if(i2c_btf(I2C1)) {

    //     if(i2c_txe(I2C1)) {
    //         i2c_stop_it(I2C1);
    //     } 

    //     if(i2c_rxne(I2C1)) {
    //         I2C1->CR1 &= ~(1U << 10U);
    //         uint8_t temp5 = I2C1->DR;
    //         i2c_stop_it(I2C1);
    //         uint8_t temp6 = I2C1->DR;
    //     }
    // }
    
    // Check if start bit is set
    if(i2c_sb(I2C1)) {
        // i2c_write_it(I2C1);
        i2c_read_it(I2C1);
    }

    // Check if addr bit is set
    if (i2c_addr(I2C1)) {
        uint16_t temp = I2C1->SR1 | I2C1->SR2;
    }

    // Check if txe bit is set
    if(i2c_txe(I2C1)) {
        if(*data) {
            i2c_send_data_it(I2C1);
            data++;
        }

        if(i2c_btf(I2C1)) {
            i2c_stop_it(I2C1);
        }
    }

    // Check if rxne is set 
    if(i2c_rxne(I2C1)) {
        
        i2c_read_data_it(I2C1);

        if(i2c_btf(I2C1)) {
            I2C1->CR1 &= ~(1U << 10U);
            i2c_stop_it(I2C1);
            uint8_t temp5 = I2C1->DR;
            uint8_t temp6 = I2C1->DR;
        }
    }
}

void I2C1_ER_IRQHandler(void) {

    // Check if acknowledge failure
    if(i2c_af(I2C1)) {
        i2c_stop_it(I2C1);
        i2c_start_it(I2C1);
    }
}
