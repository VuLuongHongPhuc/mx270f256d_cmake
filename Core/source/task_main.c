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

/********************************* Constants definition ***************************/

/********************************* Macros definition ******************************/

/********************************* Types definition *******************************/

/********************************* Local variable *********************************/

/********************************* Local functions prototype **********************/

/********************************* API functions **********************************/

void MainTask(void *parameters)
{
    (void)parameters;

    while(1)
    {
        LED_blue_Toggle();
        vTaskDelay(10U / portTICK_PERIOD_MS);
        LATBINV = 1 << 9; /* toggle */
    }
}

/*EOF*/
