# PIC32MX270F256D
- Base on Microchip USB CDC simple demo

## Configuration:
- CPU 40MHz
- Peripheral 40MHz
- USB 48MHz
- external EC 8MHz
- FreeRTOS v11.1.0
- DFP 1.5.259
- XC32 V4.35

## System configuration:
- SYSCLK = 40MHz
- PBCLK1 = 40MHz
- USB Clock = 48MHz

## LED configuration:
| Name | Port | Pin |
|------|------|-----|
| LED1 | RA10 | 12  |
| LED2 | RA7  | 13  |
| LED3 | RA8  | 32  |

## Note
- Local .ld or startup.S can't force selection yet