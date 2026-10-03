/**
 * @file task_usb.c
 * @brief Task Usb.
 * 
 * @author Phuc VU
 * @date 2026-08-09
 */

/********************************* Includes ***************************************/
#include <xc.h>
#include <sys/attribs.h>
#include "task_usb.h"
#include "drv_usbfs.h"
#include "usb_device.h"
#include "app.h"
#include "definitions.h"
#include "plib_coretimer.h"

/********************************* Constants definition ***************************/

/********************************* Macros definition ******************************/

/********************************* Types definition *******************************/

/********************************* Local variable *********************************/

SYSTEM_OBJECTS sysObj;      /* ref by drv_usbfs.c */
static uint8_t __attribute__((aligned(512))) endPointTable1[DRV_USBFS_ENDPOINTS_NUMBER * 32];

static const DRV_USBFS_INIT drvUSBFSInit =
{
     /* Assign the endpoint table */
    .endpointTable= endPointTable1,


    /* Interrupt Source for USB module */
    .interruptSource = INT_SOURCE_USB,


    
    /* USB Controller to operate as USB Device */
    .operationMode = DRV_USBFS_OPMODE_DEVICE,
    
    .operationSpeed = USB_SPEED_FULL,
 
    /* Stop in idle */
    .stopInIdle = false,
    
        /* Suspend in sleep */
    .suspendInSleep = false,
 
    /* Identifies peripheral (PLIB-level) ID */
    .usbID = USB_ID_1,
    

};


/********************************* Local functions ********************************/

/********************************* API functions **********************************/

void UsbTask(void *parameters)
{
    TaskUsbParam_t * pTaskParam = (TaskUsbParam_t*) parameters;
    (void)pTaskParam;

    // uint32_t last_transmit;
    uint32_t last;
    uint32_t elapse;
    uint32_t tickCounter;

    
    /* Initialize the USB device layer */
    sysObj.usbDevObject0 = USB_DEVICE_Initialize (USB_DEVICE_INDEX_0 , ( SYS_MODULE_INIT* ) & usbDevInitData);
    
    /* Initialize USB Driver */ 
    sysObj.drvUSBFSObject = DRV_USBFS_Initialize(DRV_USBFS_INDEX_0, (SYS_MODULE_INIT *) &drvUSBFSInit);
    
    
    CORETIMER_Start();
    tickCounter = CORETIMER_GetTickCount();
    last = tickCounter;
    // last_transmit = tickCounter;

    while(1)
    {
        //vTaskDelay(1);
        tickCounter = CORETIMER_GetTickCount();
        elapse = tickCounter - last;
        if (elapse >= 5)
        {
            last = tickCounter;
            USB_DEVICE_Tasks(sysObj.usbDevObject0);
        }

        APP_Tasks();

        // elapse = tickCounter - last_transmit;
        // if (elapse >= 1000)
        // {
        //     last_transmit = tickCounter;
        //     USB_Transmit();
        // }

    }
}

/*EOF*/
