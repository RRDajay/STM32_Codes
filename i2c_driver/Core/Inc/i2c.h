#ifndef _I2C_H_ 
#define _I2C_H_

#include "stm32f1xx.h"

// I2C Mode
void i2c_master_mode_enable(I2C_TypeDef i2cx);
void i2c_slave_mode_enable(I2C_TypeDef i2cx);
void i2c_dma_request_enable(I2C_TypeDef i2cx);// DMA request enable




void i2c_itbufen_enable(I2C_TypeDef i2cx); // enable buffer interrupt
void i2c_itevten_enable(I2C_TypeDef i2cx); // enable event interrupt
void i2c_iterren_enable(I2C_TypeDef i2cx); // enable error interrupt

void i2c_itbufen_disable(I2C_TypeDef i2cx); // disable buffer interrupt
void i2c_itevten_disable(I2C_TypeDef i2cx); // disable event interrupt
void i2c_iterren_disable(I2C_TypeDef i2cx); // disable error interrupt



#endif