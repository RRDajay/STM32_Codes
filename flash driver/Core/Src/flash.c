#include "flash.h"

void flash_unlock() {

    // Check if flash is locked
    if ((FLASH->CR & (1U << 7U))) 
    {
        // Write first flash key
        FLASH->KEYR = FLASH_KEY_1;

        // Write second flash key
        FLASH->KEYR = FLASH_KEY_2;

        // Check if flash is unlocked
        while((FLASH->CR & (1U << 7U)));
    }


}

void flash_lock() {

    // Check if flash is unlocked
    if (!(FLASH->CR & (1U << 7U))) {
        FLASH->CR |= (1U << 7U);
        while(!((FLASH->CR & (1U << 7U))));
    }
}

void flash_write(uint32_t* address, uint8_t data) {

}

uint32_t flash_read(uint32_t* address) {
    return *address;
}
