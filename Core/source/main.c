

#include <FreeRTOS.h>
#include <task.h>
#include "task_config.h"
#include "task_monitor.h"
#include "task_main.h"
#include "task_usb.h"
#include "initialization.h"
#include "app.h"
/********************************* Types definition *******************************/

/********************************* Local variable *********************************/

static TaskMainParam_t _param_task_main = {0};

static TaskMonitorParam_t _param_task_monitor = {0};
static TaskUsbParam_t _param_task_usb = {0};

static TaskHandle_t _task_handle[TSK_ID_MAX] = {0};

/********************************* Local functions prototype **********************/

void Error_Handler(void);
static void CreateTasks(void);

/********************************* Main *******************************************/

int main(void)
{
    SYS_Initialize ( NULL );

    CreateTasks();
    
    vTaskStartScheduler();

    while(1)
    {
    }

    return 0;
}

void Error_Handler(void)
{
    __builtin_disable_interrupts();
    while(1)
    {
        /* Stay here */
    }
}

static void CreateTasks(void)
{
    /* Create task main */
    static StaticTask_t xMainTaskBuffer;
    static StackType_t xMainTaskStack[TSK_STACKSIZE_MAIN];
    /* Prepare parameters */
    _param_task_main.task_id = TSK_ID_MAIN;
	
	_task_handle[TSK_ID_MAIN] = xTaskCreateStatic( MainTask,        /* Function that implements the task. */
                                (const char * const) TSK_NAME_MAIN, /* Text name for the task. */
                                TSK_STACKSIZE_MAIN,                 /* Number of indexes in the xStack array. */
                                (void * const) &_param_task_main,   /* Parameter passed into the task. */
                                TSK_PRIORITY_MAIN,                  /* Priority at which the task is created. */
                                xMainTaskStack,                     /* Array to use as the task's stack. */
                                &xMainTaskBuffer);                  /* Variable to hold the task's data structure. */
	if (_task_handle[TSK_ID_MAIN] == NULL)
    {
		/* Failed to create task */
        Error_Handler();
	}

    /* Create task USB */
    static StaticTask_t xUsbTaskBuffer ;
    static StackType_t xUsbTaskStack[TSK_STACKSIZE_USB];
    /* Prepare parameters */
    _param_task_usb.task_id = TSK_ID_USB;

    _task_handle[TSK_ID_USB] = xTaskCreateStatic( UsbTask,        /* Function that implements the task. */
                                (const char * const) TSK_NAME_USB, /* Text name for the task. */
                                TSK_STACKSIZE_USB,                 /* Number of indexes in the xStack array. */
                                (void * const) &_param_task_usb,   /* Parameter passed into the task. */
                                TSK_PRIORITY_USB,                  /* Priority at which the task is created. */
                                xUsbTaskStack,                     /* Array to use as the task's stack. */
                                &xUsbTaskBuffer);                  /* Variable to hold the task's data structure. */
    if (_task_handle[TSK_ID_USB] == NULL)
    {
        Error_Handler();
    }

    /* Create task monitor - last create ! */
    static StaticTask_t xMonitorTaskBuffer ;
    static StackType_t xMonitorTaskStack[TSK_STACKSIZE_MONITOR];
    /* Prepare parameters */
    _param_task_monitor.task_id = TSK_ID_MONITOR;
	_param_task_monitor.p_task_handle = _task_handle;

	_task_handle[TSK_ID_MONITOR] = xTaskCreateStatic( MonitorTask,     /* Function that implements the task. */
                                (const char * const) TSK_NAME_MONITOR, /* Text name for the task. */
                                TSK_STACKSIZE_MONITOR,                 /* Number of indexes in the xStack array. */
                                (void * const) &_param_task_monitor,   /* Parameter passed into the task. */
                                TSK_PRIORITY_MONITOR,                  /* Priority at which the task is created. */
                                xMonitorTaskStack,                     /* Array to use as the task's stack. */
                                &xMonitorTaskBuffer);                  /* Variable to hold the task's data structure. */
	if (_task_handle[TSK_ID_MONITOR] == NULL)
    {
        Error_Handler();
    }
}
/*EOF*/
