/**
 * @file task_main.c
 * @brief Task main.
 * 
 * @author Phuc VU
 * @date Jun 18, 2026
 */

/********************************* Includes ***************************************/
#include <xc.h>
#include "task_main.h"
#include "hardware.h"
#include "ssd1306.h"
#include "ssd1306_test.h"
#include "spi2.h"

/********************************* Constants definition ***************************/

#define SSD1306_SPI_SW    0

#define SSD1306_MISO      6U
#define SSD1306_MOSI      8U
#define SSD1306_SCK      15U
#define SSD1306_RESET     0U
#define SSD1306_DC        1U
#define SSD1306_CS        2U

/********************************* Macros definition ******************************/

/********************************* Types definition *******************************/

/********************************* Local variable *********************************/

/********************************* Local functions prototype **********************/

/********************************* API functions **********************************/

static inline void RESETsignal(uint8_t state)
{
    LATBbits.LATB0 = state;
}

static inline void DCsignal(uint8_t state)
{
    LATBbits.LATB1 = state;
}

static inline void CSsignal(uint8_t state)
{
    LATBbits.LATB2 = state;
}

#if (SSD1306_SPI_SW == 1)
static inline void SpiWriteByte(uint8_t value)
{
    for(int n=0; n<8; n++)
    {       
        LATBCLR = 1 << SSD1306_SCK; /* SCK set low */

        if (value & (0x80>>n))
        {
            LATCSET = 1 << SSD1306_MOSI;    /* MOSI pin set high */
        }
        else
        {
            LATCCLR = 1 << SSD1306_MOSI;    /* MOSI pin set low */
        }
        
        LATBINV = 1 << SSD1306_SCK;         /* SCK set high */

        Nop();
        Nop();
        Nop();
        Nop();
    }

    LATBCLR = 1 << SSD1306_SCK; /* SCK set low */
}

static bool SpiWrite(uint8_t const * const data, size_t size)
{
    for(int i=0; i<size; i++)
    {
        SpiWriteByte(((uint8_t*)data)[i]);
    }

    return true;
}
#endif

void MainTask(void *parameters)
{
    TaskMainParam_t * pTaskParam = (TaskMainParam_t*) parameters;
    (void)pTaskParam;

    /* SPI SSD1306
    SDI  RC6    2 --> MISO
    SDO  RC8    4 --> MOSI
    SCK1 RB15  15
    RST  RB0   21
    DC   RB1   22
    CS   RB2   23
    */
   
   InterfaceSpi_t interface;
   interface.Delay = &vTaskDelay;
   interface.CS    = &CSsignal;
   interface.DC    = &DCsignal;
   interface.RES   = &RESETsignal;
   
#if (SSD1306_SPI_SW == 1)
    TRISBCLR  = 0x8007;    /* RB0, RB1, RB2, RB15 as output */ 
    ANSELBCLR = 0x8007;    /* Digital Mode Enable */
    TRISCCLR = 1 << 8;     /* RC8 as output */

    interface.Write = &SpiWrite;
#else
    interface.Write = &SPI2_WriteBytesIT;
#endif
   
    SSD1306_SPI_Initialize(&interface);

    ssd1306_initialize_test(vTaskDelay);

    // display logo prebuild
	SSD1306_Display();

    int index = 0;

    while(1)
    {
        //LED_D2_Toggle();       
        vTaskDelay(1000U / portTICK_PERIOD_MS);
        
        if (index)
        {
            index = 0;

            SSD1306_Clear();
            ssd1306_testdrawchar();
            SSD1306_Display();
        }
        else
        {
            index ++;

            SSD1306_Clear();
            ssd1306_testdrawtriangle();
            SSD1306_Display();
        }
    }
}


/*EOF*/
