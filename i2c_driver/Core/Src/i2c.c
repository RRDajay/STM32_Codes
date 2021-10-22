#include "i2c.h"

void i2c_enable(I2C_TypeDef *i2cx){i2cx->CR1 |= (1U << 0U);}
void i2c_disable(I2C_TypeDef *i2cx){i2cx->CR1 &= ~(1U << 0U);}

// I2C Clock Control Setup
void i2c_init(I2C_TypeDef *i2cx, uint8_t i2c_mode, uint32_t _apb1_clk) {

    // I2C Reset
    i2cx->CR1 |= (1U << 15U);
    i2cx->CR1 &= ~(1U << 15U);

    // Gets the APB1 clock value used by the I2C registers
    uint32_t apb1_clk = _apb1_clk;

    // Divide the APB1 clock to get the whole number since CR2 only accepts between 2 - 50
    while(!(apb1_clk % 10)) {
        apb1_clk /= 10;
    }

    i2cx->CR2 |= (apb1_clk << 0U); 

    if (i2c_mode == I2C_SM_MODE) {
        
        /* From datasheet:

            STANDARD MODE:                                           
            SDA and SCL rise time, T_r = 1000ns                      
            SCL clock high time, T_w(sclh) = 4.0us                   

            CCR = T_r + T_w / T_pclk1

        */

        // Set I2C to standard mode
        i2cx->CCR &= ~(1U << 15U);

        // Calculate value for Clock Control Register
        float ccr_value = (I2C_T_R_SM_MODE + I2C_T_W_SM_MODE) * _apb1_clk;
        i2cx->CCR |= (uint16_t) ccr_value;

        uint8_t trise_value = (I2C_T_R_SM_MODE * _apb1_clk) + 1;
        i2cx->TRISE = (uint8_t) trise_value;

        __NOP();
   
    }

    // // Set I2C to fast mode
    // if (mode == I2C_FM_MODE) {

        /* From datasheet:
            FAST MODE:
            SDA and SCL rise _ime, T_r = 300ns       
            SCL clock high time, T_w(sclh) = 0.6us  
        */

        //     i2cx->CCR |= (1U << 15U);
        
    // }




}


// I2C Control
void i2c_dma_last_transfer(I2C_TypeDef *i2cx) {i2cx->CR2 |= 1U << 12U; }// next dma eot is the last transfer
void i2c_dma_not_last_transfer(I2C_TypeDef *i2cx) {i2cx->CR2 &= (1U << 12U); } // next DMA eot is not the last transfer

// I2C Interrupts
void i2c_dmaen_enable(I2C_TypeDef *i2cx) {i2cx->CR2 |= 1U << 11U; } // enable DMA requests
void i2c_itbufen_enable(I2C_TypeDef *i2cx) {i2cx->CR2 |= 1U << 10U; } // enable buffer interrupts
void i2c_itevten_enable(I2C_TypeDef *i2cx) {i2cx->CR2 |= 1U << 9U; } // enable event interrupts
void i2c_iterren_enable(I2C_TypeDef *i2cx) {i2cx->CR2 |= 1U << 8U; } // enable error interrupts

void i2c_dmaen_disable(I2C_TypeDef *i2cx) {i2cx->CR2 &= ~(1U << 11U); } // disable DMA requests
void i2c_itbufen_disable(I2C_TypeDef *i2cx) {i2cx->CR2 &= ~(1U << 10U); } // disable buffer interrupts
void i2c_itevten_disable(I2C_TypeDef *i2cx) {i2cx->CR2 &= ~(1U << 9U); } // disable event interrupts
void i2c_iterren_disable(I2C_TypeDef *i2cx) {i2cx->CR2 &= ~(1U << 8U); } // disable error interrupts
