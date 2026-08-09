cmake_minimum_required(VERSION 3.24.2)

# set(MCU 32MX270F256D)

add_library(FreeRTOS STATIC
        MemMang/heap_4.c
        portable/port.c
        portable/port_asm.S
        source/croutine.c
        source/event_groups.c
        source/list.c
        source/queue.c
        source/stream_buffer.c
        source/timers.c
        source/tasks.c
#        source/FreeRTOS_tasks.c
)

target_include_directories(FreeRTOS PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/portable
)

target_compile_options(FreeRTOS PRIVATE
    -mprocessor=${MCU}
    -O1
    -ffunction-sections
    -fdata-sections
    -Wl,--gc-sections
    -Wall
    -fstack-usage
)