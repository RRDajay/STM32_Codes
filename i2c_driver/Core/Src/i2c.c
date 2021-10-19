#include "i2c.h"



// enable buffer interrupts
void i2c_itbufen_enable(I2C_TypeDef i2cx) {i2cx.CR2 |= 1U << 10U; } 
// enable event interrupts
void i2c_itevten_enable(I2C_TypeDef i2cx) {i2cx.CR2 |= 1U << 9U; } 
// enable error interrupts
void i2c_iterren_enable(I2C_TypeDef i2cx) {i2cx.CR2 |= 1U << 8U; } 

// disable buffer interrupts
void i2c_itbufen_disable(I2C_TypeDef i2cx) {i2cx.CR2 &= ~(1U << 10U); } 
// disable event interrupts
void i2c_itevten_disable(I2C_TypeDef i2cx) {i2cx.CR2 &= ~(1U << 9U); } 
// disable error interrupts
void i2c_iterren_disable(I2C_TypeDef i2cx) {i2cx.CR2 &= ~(1U << 8U); } 
