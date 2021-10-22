#ifndef _I2C_H_ 
#define _I2C_H_

#include "stm32f1xx.h"

/* From datasheet:

    STANDARD MODE:                                 |    FAST MODE:            
    SDA and SCL rise time, T_r = 1000ns            |    SDA and SCL rise time, T_r = 300ns 
    SCL clock high time, T_w(sclh) = 4000ns        |    SCL clock high time, T_w(sclh) = 600ns  
    SDA and SCL fall time, T_f = 300ns             |    SDA and SCL fall time, T_f = 300ns
    SCL clock low time, T_w(scll) = 4700ns         |    SCL clock low time, T_w(scll) = 1300ns 

    T_high = T_r + T_w(sclh)
    T_low = T_f + T_w(scll) 
    
    where:
                                                   |    If DUTY = 0;
        T_high = CCR * T_pclk1                     |    T_high = CCR * T_pclk1
        T_low = CCR * T_pclk1                      |    T_low = 2 * CCR * T_pclk1
                                                   |    
                                                   |    If DUTY = 1
                                                   |    T_high = 9 * CCR * T_pclk1
                                                   |    T_low = 16 * CCR * T_pclk1

*/

#define I2C_SM_MODE     0U
#define I2C_FM_MODE     1U

#define I2C_T_R_SM_MODE         1000E-9
#define I2C_T_W_SM_MODE         4000E-9


#define I2C_SCL_FREQ_400KHZ     0x801EU    
#define I2C_SCL_FREQ_300KHZ     0x8028U
#define I2C_SCL_FREQ_200KHZ     0x803CU
#define I2C_SCL_FREQ_100KHZ     0x00B4U
#define I2C_SCL_FREQ_50KHZ      0x0168U
#define I2C_SCL_FREQ_20KHZ      0x0384U

// I2C Control Registers
void i2c_init(I2C_TypeDef *i2cx, uint8_t i2c_mode, uint32_t _apb1_clk);
void i2c_enable(I2C_TypeDef *i2cx);

// I2C Control
void i2c_dma_last_transfer(I2C_TypeDef *i2cx); // next dma eot is the last transfer
void i2c_dma_not_last_transfer(I2C_TypeDef *i2cx); // next DMA eot is not the last transfer

// I2C Interrupts
void i2c_dmaen_enable(I2C_TypeDef *i2cx); // enable DMA requests
void i2c_itbufen_enable(I2C_TypeDef *i2cx); // enable buffer interrupt
void i2c_itevten_enable(I2C_TypeDef *i2cx); // enable event interrupt
void i2c_iterren_enable(I2C_TypeDef *i2cx); // enable error interrupt

void i2c_dmaen_disable(I2C_TypeDef *i2cx); // disable DMA requests
void i2c_itbufen_disable(I2C_TypeDef *i2cx); // disable buffer interrupt
void i2c_itevten_disable(I2C_TypeDef *i2cx); // disable event interrupt
void i2c_iterren_disable(I2C_TypeDef *i2cx); // disable error interrupt



#endif