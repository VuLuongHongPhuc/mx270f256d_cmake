cmake_minimum_required(VERSION 3.24.2)

set(MCU 32MX270F256D)

add_library(FreeRTOS STATIC
        portable/MemMang/heap_4.c
        portable/PIC32MX/port.c
        portable/PIC32MX/port_asm.S
        source/croutine.c
        source/event_groups.c
        source/list.c
        source/queue.c
        source/stream_buffer.c
        source/timers.c
        source/tasks.c
)

target_include_directories(FreeRTOS PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/portable/PIC32MX
)

target_compile_options(FreeRTOS PRIVATE
    -mprocessor=${MCU}
    -O1
    -g
    -Wall
    -ffunction-sections
    -fdata-sections
#    -fstack-usage          ---> message compiler: not supported for this target
#    -Wstack-usage=2048
)