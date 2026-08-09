cmake_minimum_required(VERSION 3.24.2)

# set(CMAKE_VERBOSE_MAKEFILE True)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/toolchain-pic32mz.cmake)

#Device Family Pack
set(DFP "D:/Program/Microchip/MPLABX/v6.20/packs/Microchip/PIC32MX_DFP/1.5.259")
set(MCU 32MX270F256D)

project(mx270f256d_cmake C ASM)
# set(LINKER_FILE ${CMAKE_SOURCE_DIR}/linker/p32MX270F256D.ld)


# Add subdirectories - order matters
add_subdirectory(FreeRTOS)
add_subdirectory(Utils)
add_subdirectory(config)


set(CORE_SOURCE_FILES
    Core/source/main.c
    Core/source/task_monitor.c
    Core/source/task_main.c
    Core/source/task_usb.c
    Core/source/app.c
)

add_executable(${PROJECT_NAME}.elf
    ${UTILS_SOURCE_FILES}
    ${CORE_SOURCE_FILES}
    ${CONFIG_SOURCE_FILES}
)

# Link libraries to project
target_link_libraries(${PROJECT_NAME}.elf PRIVATE 
    FreeRTOS
)

# List of include directories
target_include_directories(${PROJECT_NAME}.elf PRIVATE
    ${CMAKE_SOURCE_DIR}/Core/include
    ${CMAKE_SOURCE_DIR}/Utils/include
    ${CMAKE_SOURCE_DIR}/config/default
    ${CMAKE_SOURCE_DIR}/config/default/usb
    ${CMAKE_SOURCE_DIR}/config/default/usb/src
    ${CMAKE_SOURCE_DIR}/config/default/system
    ${CMAKE_SOURCE_DIR}/config/default/system/debug
    ${CMAKE_SOURCE_DIR}/config/default/system/int
    ${CMAKE_SOURCE_DIR}/config/default/peripheral/clk
    ${CMAKE_SOURCE_DIR}/config/default/peripheral/evic
    ${CMAKE_SOURCE_DIR}/config/default/peripheral/gpio
    ${CMAKE_SOURCE_DIR}/config/default/osal
    ${CMAKE_SOURCE_DIR}/config/default/driver
    ${CMAKE_SOURCE_DIR}/config/default/driver/usb
    ${CMAKE_SOURCE_DIR}/config/default/driver/usb/usbfs
    ${CMAKE_SOURCE_DIR}/config/default/driver/usb/usbfs/src
    ${CMAKE_SOURCE_DIR}/config/default/driver/usb/usbfs/src/templates
)

target_compile_options(${PROJECT_NAME}.elf PRIVATE
    -mprocessor=${MCU}
    -O0
    -g
    -Wall
    -ffunction-sections
    -fdata-sections
    -mdfp=${DFP}
)

target_link_options(${PROJECT_NAME}.elf PRIVATE
    -mprocessor=${MCU}
    -O0
    -g
    -Wl,--gc-sections
    -Wl,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map
    -Wl,--memorysummary,${PROJECT_BINARY_DIR}/${PROJECT_NAME}_memory.xml
#    -Wl,--print-memory-usage
    -mdfp=${DFP}
)

# Generate HEX file
add_custom_command(TARGET ${PROJECT_NAME}.elf
    POST_BUILD
    COMMAND ${XC32_ROOT}/bin/xc32-bin2hex ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf
)

# Generate Memory Usage Report
add_custom_command(TARGET ${PROJECT_NAME}.elf
    POST_BUILD
    COMMAND ${XC32_SIZE}
            --format=berkeley
            $<TARGET_FILE:${PROJECT_NAME}.elf>
    COMMENT "PIC32 Memory Usage:"
)

# Generate Memory Usage Report in XML format
add_custom_command(TARGET ${PROJECT_NAME}.elf
    POST_BUILD
    COMMAND ${CMAKE_SOURCE_DIR}/tools/memory_report.exe ${PROJECT_BINARY_DIR}/${PROJECT_NAME}_memory.xml
)
