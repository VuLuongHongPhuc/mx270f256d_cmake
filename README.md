# PIC32MX270F256D
- Base on Microchip USB CDC simple demo

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

## 

## Note
- Local .ld or startup.S can't force selection yet

## Debug
- with MPLAB X IDE 6.20 : can't break in freertos thread code!
- with MDB - OK