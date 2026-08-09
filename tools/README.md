# DEBUG memory_report

## Compile
g++.exe -g -O0 memory_report.cpp -o memory_report 

## Debug with gdb
gdb .\memory_report.exe

## Debug command
### Run
- Run: r
### Breakpoints
- Set breakpoint: (gdb) break main (or) (gdb) b main
- On file, line format: break filename:line
- file, line: (gdb) break src/uart.c:120
- list near breakpoints: (gdb) list
- Get all breakpoints: (gdb) info breakpoints
### Step execution
- One instruction: (gdb) stepi
- One source line: (gdb) step
- Continue       : (gdb) continue
### Inspect registers
- (gdb) info registers
### Read memory
- format : x / count format address
- Read 16 words    : (gdb) x/16wx 0x1D000000
- Read 32 Hex bytes: (gdb) x/32xb 0xA0000000

### Common stepping commands
| Command          | Meaning                                             |
| ---------------- | --------------------------------------------------- |
| `n` / `next`     | Execute next source line, don't enter functions     |
| `s` / `step`     | Execute next source line, enter functions           |
| `ni` / `nexti`   | Execute next machine instruction, don't enter calls |
| `si` / `stepi`   | Execute next machine instruction, enter calls       |
| `c` / `continue` | Run until next breakpoint                           |
| `finish`         | Run until current function returns                  |
| `until`          | Run until a later line in the current function      |


### temp command
b memory_report.cpp:46


# Debug project
## Debug with mdb
### Launch the debugger
- D:/Program/Microchip/MPLABX/v6.20/mplab_platform/bin/mdb.bat
### Set the target device
- device PIC32MX270F256D
### Set the debugger device
- set AutoSelectMemRanges auto         --> default
- hwtool PICkit3
- hwtool ICD3
### Load the executable
- program mx270f256d_cmake.elf
### Breakpoints
- break main     --> function
- break [filename.c]:[line]
### Run
- run            --> start apps
- halt
- continue       --> resume apps
- reset
- step
- stepi          --> + one instruction
### Exit mdb
- quit