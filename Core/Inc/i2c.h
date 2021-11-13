#ifndef _I2C_H_
#define _I2C_H_

#include "stdbool.h"
#include "stddef.h"
#include "stm32f1xx.h"

/* From datasheet:

    STANDARD MODE:                                 |    FAST MODE:
    SDA and SCL rise time, T_r = 1000ns            |    SDA and SCL rise time,
   T_r = 300ns SCL clock high time, T_w(sclh) = 4000ns        |    SCL clock
   high time, T_w(sclh) = 600ns SDA and SCL fall time, T_f = 300ns             |
   SDA and SCL fall time, T_f = 300ns SCL clock low time, T_w(scll) = 4700ns |
   SCL clock low time, T_w(scll) = 1300ns

    T_high = T_r + T_w(sclh)
    T_low = T_f + T_w(scll)

    where:
                                                   |    If DUTY = 0;
        T_high = CCR * T_pclk1                     |    T_high = CCR * T_pclk1
        T_low = CCR * T_pclk1                      |    T_low = 2 * CCR *
   T_pclk1
                                                   |
                                                   |    If DUTY = 1
                                                   |    T_high = 9 * CCR *
   T_pclk1 |    T_low = 16 * CCR * T_pclk1

*/

#define I2C_SM_MODE 0U
#define I2C_FM_MODE 1U

#define I2C_T_R_SM_MODE 1000E-9
#define I2C_T_W_SCLH_SM_MODE 4000E-9
#define I2C_T_F_SM_MODE 300E-9
#define I2C_T_W_SCLL_SM_MODE 4700E-9

#define I2C_SCL_FREQ_400KHZ 0x801EU
#define I2C_SCL_FREQ_300KHZ 0x8028U
#define I2C_SCL_FREQ_200KHZ 0x803CU
#define I2C_SCL_FREQ_100KHZ 0x00B4U
#define I2C_SCL_FREQ_50KHZ 0x0168U
#define I2C_SCL_FREQ_20KHZ 0x0384U

#define BUFFER_SIZE 128

void i2c_set_transmit_data(uint8_t* _data);
uint8_t i2c_get_receive_buffer();

// I2C Control Registers
void i2c_init(I2C_TypeDef* i2cx, uint8_t i2c_mode, uint32_t _apb1_clk);
void i2c_enable(I2C_TypeDef* i2cx);
void i2c_disable(I2C_TypeDef* i2cx);
void i2c_sw_reset(I2C_TypeDef* i2cx);
void i2c_enable_pec(I2C_TypeDef* i2cx);
void i2c_disable_pec(I2C_TypeDef* i2cx);
void i2c_enable_clkstretch(I2C_TypeDef* i2cx);
void i2c_disable_clkstretch(I2C_TypeDef* i2cx);
void i2c_dma_last_transfer(I2C_TypeDef* i2cx); // next DMA eot is the last transfer
void i2c_dma_not_last_transfer(I2C_TypeDef* i2cx); // next DMA eot is not the last transfer

// I2C Communication Flow Helper Functions

void i2c_master_write_data(I2C_TypeDef* i2cx, uint8_t* _data, uint8_t size, uint8_t address);
void i2c_master_read_data(I2C_TypeDef* i2cx, uint8_t size, uint8_t _address);
void i2c_master_write_data_it(I2C_TypeDef* i2cx, uint8_t* _data, uint8_t _address);
void i2c_master_read_data_it(I2C_TypeDef* i2cx, uint8_t size, uint8_t _address);

// void i2c_master_write_data_it(I2C_TypeDef* i2cx);
// void i2c_master_write_it(I2C_TypeDef* i2cx);
// void i2c_master_send_data_it(I2C_TypeDef* i2cx);
// void i2c_master_stop_it(I2C_TypeDef* i2cx);

// I2C Interrupts
void i2c_dma_enable(I2C_TypeDef* i2cx); // enable DMA requests
void i2c_itbuf_enable(I2C_TypeDef* i2cx); // enable buffer interrupt
void i2c_itevt_enable(I2C_TypeDef* i2cx); // enable event interrupt
void i2c_iterr_enable(I2C_TypeDef* i2cx); // enable error interrupt

void i2c_dma_disable(I2C_TypeDef* i2cx); // disable DMA requests
void i2c_itbuf_disable(I2C_TypeDef* i2cx); // disable buffer interrupt
void i2c_itevt_disable(I2C_TypeDef* i2cx); // disable event interrupt
void i2c_iterr_disable(I2C_TypeDef* i2cx); // disable error interrupt

// I2C Check Flags
bool i2c_start_bit_flag(I2C_TypeDef* i2cx);
bool i2c_address_flag(I2C_TypeDef* i2cx);
bool i2c_byte_transfer_flag(I2C_TypeDef* i2cx);
bool i2c_receiver_not_empty_flag(I2C_TypeDef* i2cx);
bool i2c_trasmitter_empty_flag(I2C_TypeDef* i2cx);
bool i2c_acknowledge_flag(I2C_TypeDef* i2cx);

#endif