#include <stdint.h>
#include <xc.h>


/*
 * Core Tick = 50ns
*/


#define POS_BIT_0       0x0001U
#define POS_BIT_1       0x0002U
#define POS_BIT_2       0x0004U
#define POS_BIT_3       0x0008U
#define POS_BIT_4       0x0010U
#define POS_BIT_5       0x0020U
#define POS_BIT_6       0x0040U
#define POS_BIT_7       0x0080U
#define POS_BIT_8       0x0100U
#define POS_BIT_9       0x0200U
#define POS_BIT_10      0x0400U
#define POS_BIT_11      0x0800U
#define POS_BIT_12      0x1000U
#define POS_BIT_13      0x2000U
#define POS_BIT_14      0x4000U
#define POS_BIT_15      0x8000U

#define DATA_HIGH() (LATBSET = POS_BIT_14)
#define DATA_LOW()  (LATBCLR = POS_BIT_14)

static void WS2812B_SendByte(uint8_t byte)
{

    for(int i = 7; i >= 0; i--)
    {
        if(byte & (1 << i))
        {
            /* 800 ns +/- 150 */
            DATA_HIGH();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();

            /* 400 ns +/- 150 */
            DATA_LOW();
        }
        else
        {
            /* 450 ns +/- 150 */
            DATA_HIGH();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();

            /* 800 ns +/- 150 */
            DATA_LOW();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
        }
    }
}

void WS2812B_SendPixel(uint8_t r, uint8_t g, uint8_t b)
{
    /* Note: Call function take to much time interval */

    WS2812B_SendByte(g);  // Green first
    WS2812B_SendByte(r);
    WS2812B_SendByte(b);
}