cmake_minimum_required(VERSION 3.10.0)
project(rtos-demo-stm32-bluepill)

set(MCU_FLAGS 
    -mcpu=cortex-m3
    -mthumb)

set(EXECUTABLE ${CMAKE_PROJECT_NAME})

enable_language(C CXX ASM)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# MCU Startup Code Directories
set(STARTUP_CODE  ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/startup_stm32f103xb.s)

# MCU Linker Script Directories
set(LINKER_SCRIPT  ${CMAKE_CURRENT_SOURCE_DIR}/Core/Script/STM32F103C8Tx_FLASH.ld)

# Header Directories
set(PROJECT_INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F1xx/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Core/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/FreeRTOS/ARM_CM3
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/FreeRTOS/Include
    )

# Source Directories
file(GLOB_RECURSE PROJECT_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F1xx/Source/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/FreeRTOS/Src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/FreeRTOS/ARM_CM3/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/FreeRTOS/MemMang/heap_4.c
    )

# Executable Files
add_executable(${EXECUTABLE} 
    ${PROJECT_SOURCES}
    ${STARTUP_CODE})

# Embedded Macros
target_compile_definitions(${EXECUTABLE} PRIVATE 
    STM32F103xB
    __RTOS__
    # __TASKS_DEMO__
    __QUEUE_DEMO__
    # __SEMIHOSTING__
    )

# Add header directories to target
target_include_directories(${EXECUTABLE} PRIVATE
    ${PROJECT_INCLUDE_DIRECTORIES})

# Compiler and linker options
target_compile_options(${EXECUTABLE} PRIVATE
    ${MCU_FLAGS}
    -fdata-sections 
    -ffunction-sections
    -Wall
    -Wextra
    -Wpedantic
    # -Wno-unused-parameter
    # -MMD
    # -MP
    # -MF"$(@:%.o=%.d)"
    $<$<CONFIG:Debug>:-Og -g3 -ggdb -gdwarf-2>
    $<$<CONFIG:Release>:-Og -g0>)

target_link_options(${EXECUTABLE} PRIVATE
    ${MCU_FLAGS}
    --specs=nano.specs 
    -T${LINKER_SCRIPT}
    -lc
    -lm
    -lnosys
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map,--cref
    -Wl,--gc-sections
    -Wl,--print-memory-usage)

add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${EXECUTABLE}>)

add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${EXECUTABLE}>
    ${EXECUTABLE}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary -S $<TARGET_FILE:${EXECUTABLE}>
    ${EXECUTABLE}.bin)