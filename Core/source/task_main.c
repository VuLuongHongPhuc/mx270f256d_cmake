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
    TaskMainParam_t * pTaskParam = (TaskMainParam_t*) parameters;
    (void)pTaskParam;


    while(1)
    {
        vTaskDelay(1000U / portTICK_PERIOD_MS);
    }
}

/*EOF*/
