## LED WS2812B protocol
- 24 bits data frame

### Color order
| Color | G    | R    | B    |
| ----- | ---- | ---- | ---- |
| Red   | 0x00 | 0xFF | 0x00 |
| Green | 0xFF | 0x00 | 0x00 |
| Blue  | 0x00 | 0x00 | 0xFF |
| White | 0xFF | 0xFF | 0xFF |


### Timing Requirements
| Bit | High Time | Low Time |
| --- | --------- | -------- |
| 0   | 0.35 µs   | 0.8 µs   |
| 1   | 0.7 µs    | 0.6 µs   |

### Delay latch
- Pull the line low for at least 50 µs


### Tricks
- Use SPI with specific baud to send data.
####
| WS2812 Bit | SPI Encoding |
| ---------- | ------------ |
| 0          | 100          |
| 1          | 110          |
