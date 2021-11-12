#include "i2c.h"
#include "systick.h"

void lcd_init(void)
{
    delay_ms(100);
    i2c_start(I2C1);
    i2c_send_address(I2C1, 0x27);

    i2c_send_data(I2C1, 0x30);
    delay_ms(5);

    i2c_send_data(I2C1, 0x30);
    delay_ms(1);

    i2c_send_data(I2C1, 0x30);
    delay_ms(1);

    i2c_send_data(I2C1, 0x38);
    delay_ms(1);

    i2c_send_data(I2C1, 0x08);
    delay_ms(1);

    i2c_send_data(I2C1, 0x01);
    delay_ms(1);

    i2c_send_data(I2C1, 0x06);
    delay_ms(1);

    i2c_send_data(I2C1, 0x0E);
    delay_ms(1);

    i2c_stop(I2C1);
}