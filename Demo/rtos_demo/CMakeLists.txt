set(EXECUTABLE rtos_demo)

# Executable Files
add_executable(${EXECUTABLE}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main_queue_demo.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main_tasks_demo.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main_software_timers.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main_mutex.c
    ${PROJECT_SOURCES}
    ${STARTUP_CODE}
    ${RTOS_SOURCES}
)

# Embedded Macros
target_compile_definitions(${EXECUTABLE} PRIVATE 
    STM32F103xB
    __RTOS__
    # __TASKS_DEMO__
    # __QUEUE_DEMO__
    # __SEMIHOSTING__
    # __SOFTWARE_TIMER_DEMO__
    __MUTEX_DEMO__
    )

# Add header directories to target
target_include_directories(${EXECUTABLE} PRIVATE
    ${PROJECT_INCLUDE_DIRECTORIES}
    ${RTOS_INCLUDE_DIRECTORIES}
    )

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