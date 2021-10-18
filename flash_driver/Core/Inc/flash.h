#ifndef _FLASH_H_
#define _FLASH_H_

#include "stm32f1xx.h"
#include "stdbool.h"

#define RDPRT_KEY               (0x00A5UL)
#define FLASH_KEY_1             (0x45670123UL)
#define FLASH_KEY_2             (0xCDEF89ABUL)
#define FLASH_PAGES             (128UL)


void flash_enable_prefetch_buffer(void);

// PEC
void flash_unlock();
void flash_lock();
void flash_write(uint32_t address, uint16_t data);
void flash_erase(uint32_t address);
uint32_t flash_read(uint32_t* address);



#endif // _FLASH_H_
