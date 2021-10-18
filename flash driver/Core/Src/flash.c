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

void flash_write(uint32_t address, uint16_t data) {

    if (FLASH->SR & (1U << 0U))
        return;
    
    // Unlocks FLASH PEC
    flash_unlock();
    
    // Write FLASH_CR_PG to 1
    FLASH->CR |= (1U << 0U);

    // Perform Half Word write
    *((volatile uint16_t*) address) = data;

    // Checks if FLASH is busy
    while(FLASH->SR & (1U << 0U));

    // Reset EOP
    FLASH->SR |= (1U << 5U);

    // Reset FLASH_CR_PG
    FLASH->CR &= ~(1U << 0U);

    // Locks FLASH PEC
    flash_lock();
    
}

uint32_t flash_read(uint32_t* address) {
    return *address;
}

void flash_erase(uint32_t address) {

    // Check that no FLASH memory operation is ongoing by checking the BSY bit in the FLASH_CR register
    if (FLASH->SR & (1U << 0U))
        return;
    
    // Unlock FLASH PEC

    flash_unlock();

    // Set the PER bit in the FLASH_CR register
    FLASH->CR |= (1U << 1U);

    // Program the FLASH_AR register to select a page to erase
    FLASH->AR = address;

    // Set the STRT bit in the FLASH_CR register
    FLASH->CR |= (1U << 6U);

    // Wait for the BSY bit to be reset
    while(FLASH->SR & (1U << 0U));

    // Reset PER bit in the FLASH_CR Register
    FLASH->CR &= ~(1U << 1U);

    // Reset EOP
    FLASH->SR |= (1U << 5U);

    // Lock FLASH PEC
    flash_lock();
    // Read the erased page and verify
}