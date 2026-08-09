
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR mips)

# XC32 installation
set(XC32_ROOT "D:/Program/Microchip/xc32/v4.35")

# Compiler
set(CMAKE_C_COMPILER   "${XC32_ROOT}/bin/xc32-gcc.exe")
set(CMAKE_CXX_COMPILER "${XC32_ROOT}/bin/xc32-g++.exe")
set(CMAKE_ASM_COMPILER "${XC32_ROOT}/bin/xc32-gcc.exe")

# Memory usage
set(XC32_SIZE "${XC32_ROOT}/bin/xc32-size.exe")


set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

