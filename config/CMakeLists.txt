cmake_minimum_required(VERSION 3.23.1)

# file(GLOB_RECURSE CONFIG_SF "${CMAKE_CURRENT_SOURCE_DIR}/source/*.c")

set(CONFIG_SOURCE_FILES
#        ${CONFIG_SF}
    config/default/exceptions.c
    config/default/freertos_hooks.c
    config/default/initialization.c
    config/default/interrupts_a.S
    config/default/interrupts.c
    config/default/usb_device_init_data.c
    config/default/usb/src/usb_device_cdc_acm.c
    config/default/usb/src/usb_device_cdc.c
    config/default/usb/src/usb_device.c
    config/default/system/int//src/sys_int.c
    config/default/stdio/xc32_monitor.c
    config/default/peripheral/clk/plib_clk.c
    config/default/peripheral/evic/plib_evic.c
    config/default/peripheral/gpio/plib_gpio.c
    config/default/osal/osal_freertos.c
    config/default/driver/usb/usbfs/src/drv_usbfs_device.c
    config/default/driver/usb/usbfs/src/drv_usbfs.c
    PARENT_SCOPE
)

set(CONFIG_INLUDE_PATH
    default/usb
    default/usb/src
    default/system
    default/system/debug
    default/system/int
    default/peripheral/clk
    default/peripheral/evic
    default/peripheral/gpio
    default/osal
    default/driver
    default/driver/usb
    default/driver/usb/usbfs
    default/driver/usb/usbfs/src
    default/driver/usb/usbfs/src/templates
)
