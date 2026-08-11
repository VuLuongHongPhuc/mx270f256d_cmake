# PIC32MX270F256D
- Base on Microchip USB CDC simple demo
- Use with MPLAB X IDE 6.20 for debug

## Configuration:
- external EC 8MHz
- FreeRTOS v11.1.0
- DFP 1.5.259
- XC32 V4.35

## System configuration:
- SYSCLK = 40MHz
- PBCLK1 = 40MHz
- USB Clock = 48MHz

## LED configuration:
| Name | Port | Pin | Label |
|------|------|-----|-------|
| LED1 | RA10 | 12  | D2    |
| LED2 | RA7  | 13  | D3    |
| LED3 | RA8  | 32  | D4    |


## Note
- Local .ld or startup.S can't force selection yet

## Debug
### MPLAB X IDE 6.20
- Enter exception loop if option "Halt at main" active
- Enter exception loop after a break
### MDB
- OK

## Debug project with MDB
- go to build folder: cd build
## Launch the debugger
- D:/Program/Microchip/MPLABX/v6.20/mplab_platform/bin/mdb.bat
## Set the target device
- device PIC32MX270F256D
## Set the debugger device
- set AutoSelectMemRanges auto         --> default
### Select debugger tool:
- hwtool PICkit3
- hwtool ICD3
- hwtool SNAP
## Load the executable
- program mx270f256d_cmake.elf
## Breakpoints
- break main     --> function
- break [filename.c]:[line]
## Run
- run            --> start apps
- halt
- continue       --> resume apps
- reset
- step
- stepi          --> + one instruction
## Exit mdb
- quit