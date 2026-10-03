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
| Name | Port | Pin | Label  |
|------|------|-----|--------|
| LED2 | RA10 | 12  | LED_D2 |
| LED3 | RA7  | 13  | LED_D3 |
| LED4 | RA8  | 32  | LED_D4 |

## Flasher/Debugger
- RA0: PGED3
- RA1: PGEC3

## Issue
- Can't debug with MPLAB X IDE from .elf

## Note
- default startup file used.

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
- D:/Program/Microchip/MPLABX/v6.20/mplab_platform/bin/mdb.bat ../Debug/MDB_CommandFile.txt    --> running MDB with command file method
## Set the target device
- device PIC32MX270F256D
## Set the debugger device
- set AutoSelectMemRanges auto         --> default
- set freezeperiphs true               --> freeze peripheral on debug
- set hwtoolclock.frcindebug false     --> don't switch to FRC in debug halt
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