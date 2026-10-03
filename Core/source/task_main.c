/**
 * @file task_main.c
 * @brief Task main.
 * 
 * @author Phuc VU
 * @date Jun 18, 2026
 */

/********************************* Includes ***************************************/

#include "task_main.h"
#include <xc.h>
#include "plib_gpio.h"
#include "ssd1306_i2c.h"
#include "plib_i2c1_master.h"
#include "plib_i2c_master_common.h"
#include "convert_to_string.h"
#include "plib_adc.h"
#include "led_ws2812b.h"

/********************************* Constants definition ***************************/

#define ADC_ZERO_DIV_LIMITATION         1023

/********************************* Macros definition ******************************/

/********************************* Types definition *******************************/

/********************************* Local variable *********************************/

/********************************* Local functions ********************************/

static void WS2812B_SwitchPixel(int index)
{
    (void)__builtin_disable_interrupts();

    int shiftColor;
    uint32_t color;
    shiftColor = index % 3;
    color = 0x80 << (8 * shiftColor);
    WS2812B_SendPixel((uint8_t)color, (uint8_t)(color >> 8), (uint8_t)(color >> 16));
    
    (void)__builtin_enable_interrupts();
}

/********************************* API functions **********************************/

void MainTask(void *parameters)
{
    TaskMainParam_t * pTaskParam = (TaskMainParam_t*) parameters;
    (void)pTaskParam;

    

    SSD1306_Initialize();
    SSD1306_Display();


    uint32_t adc_result;
    char str[16];
    const float R1 = 10000.0f;   // Valeur de la résistance connue en Ohms (ex: 10 k +/- 10%)
    const float Vcc = 3.25f;     // Tension d'alimentation
    
    int iColor = 0;
    

    while(1)
    {
        LED_D4_Toggle();

        //LATBbits.LATB15 ^= 1;

        WS2812B_SwitchPixel(iColor);
        iColor++;
        
        vTaskDelay(1000U / portTICK_PERIOD_MS);

        
        ADC_SamplingStart();

        vTaskDelay(1); /* Give time for sampling and conversion */

        /* Wait end conversion */
        while(ADC_ResultIsReady() == false)
        {
            /* Do nothing */
        }

        adc_result = ADC_ResultGet(ADC_RESULT_BUFFER_0);
        
        SSD1306_Clear();

        if (adc_result < ADC_ZERO_DIV_LIMITATION)
        {
            float Vout = (adc_result * Vcc) / 1024.0f;
            float Rx = R1 * Vout / (Vcc - Vout); // Calcul de la résistance inconnue
         
            u32toa (adc_result, str);
            SSD1306_SetCursor(0, 8);
            SSD1306_OutputText(str);

            fixed3_to_str(Rx, str);
            SSD1306_SetCursor(0, 16);
            SSD1306_OutputText(str);
        }
        else
        {
            SSD1306_SetCursor(0, 8);
            SSD1306_OutputText("Erreur / Hors limite");
        }

        SSD1306_Display();
    }

}


/*EOF*/
