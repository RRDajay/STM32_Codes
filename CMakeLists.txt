cmake_minimum_required(VERSION 3.10.0)
project(driver-codes-stm32f1xx)

enable_language(C CXX ASM)

set(MCU_FLAGS 
    -mcpu=cortex-m3
    -mthumb)
    
# MCU Startup Code 
set(STARTUP_CODE  ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/startup_stm32f103xb.s)

# MCU Linker Script
set(LINKER_SCRIPT  ${CMAKE_CURRENT_SOURCE_DIR}/Core/Script/STM32F103C8Tx_FLASH.ld)

# Header Directories
set(PROJECT_INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F1xx/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Core/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Inc
    )

set(RTOS_INCLUDE_DIRECTORIES    
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/FreeRTOS/ARM_CM3
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/FreeRTOS/Include
)

# Source Directories
file(GLOB_RECURSE PROJECT_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F1xx/Source/*.c
    )

file(GLOB_RECURSE RTOS_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/FreeRTOS/Src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/FreeRTOS/ARM_CM3/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/FreeRTOS/MemMang/heap_4.c
    )

add_subdirectory(Demo/blink_led)
add_subdirectory(Demo/usart_demo)
add_subdirectory(Demo/dma_usart_demo)
add_subdirectory(Demo/i2c_master_demo)
add_subdirectory(Demo/rtos_demo)
add_subdirectory(Demo/lcd_demo)
