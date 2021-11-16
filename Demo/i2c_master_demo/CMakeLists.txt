
set(EXECUTABLE i2c_master_demo)

# Executable Files
add_executable(${EXECUTABLE} 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
    ${PROJECT_SOURCES}
    ${STARTUP_CODE})

# Embedded Macros
target_compile_definitions(${EXECUTABLE} PRIVATE 
    STM32F103xB
    # MASTER_WRITE_DEMO
    # MASTER_READ_DEMO
    MASTER_WRITE_INTERRUPT_DEMO
    # MASTER_READ_INTERRUPT_DEMO
)

# Add header directories to target
target_include_directories(${EXECUTABLE} PRIVATE
    ${PROJECT_INCLUDE_DIRECTORIES})

# Compiler and linker options
target_compile_options(${EXECUTABLE} PRIVATE
    ${MCU_FLAGS}
    -fdata-sections 
    -ffunction-sections
    # -Wall
    # -Wextra
    # -Wpedantic
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
    -Wl,-Map=$<TARGET_FILE:${EXECUTABLE}>.map,--cref
    -Wl,--gc-sections
    -Wl,--print-memory-usage)

add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${EXECUTABLE}>)

add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${EXECUTABLE}>
    ${EXECUTABLE}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary -S $<TARGET_FILE:${EXECUTABLE}>
    ${EXECUTABLE}.bin)