/**
 * @file task_monitor.c
 * @brief Debug task monitor.
 * 
 * @author Phuc VU
 * @date Jun 18, 2026
 */

/********************************* Includes ***************************************/

#include <stdio.h>
#include <stddef.h>
#include "task_config.h"
#include "task_monitor.h"
#include "hardware.h"



/********************************* Constants definition ***************************/

/********************************* Macros definition ******************************/

/********************************* Types definition *******************************/

/********************************* Local variable *********************************/

/********************************* Local functions prototype **********************/

/********************************* API functions **********************************/

void MonitorTask(void* parameters)
{    
    TaskMonitorParam_t* pTaskParam = NULL;
    pTaskParam = (TaskMonitorParam_t*) parameters;
    (void)pTaskParam;
  
    while(1)
    {
        LED_D3_Toggle();
        vTaskDelay(1000U / portTICK_PERIOD_MS);
    }
}

/*EOF*/
