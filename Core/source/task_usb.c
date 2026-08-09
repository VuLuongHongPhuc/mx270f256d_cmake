/**
 * @file task_usb.c
 * @brief Task Usb.
 * 
 * @author Phuc VU
 * @date 2026-08-09
 */

/********************************* Includes ***************************************/
#include <xc.h>
#include "task_usb.h"
#include "drv_usbfs.h"
#include "usb_device.h"
#include "app.h"
#include "definitions.h"

/********************************* Constants definition ***************************/

/********************************* Macros definition ******************************/

/********************************* Types definition *******************************/

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


/********************************* Local variable *********************************/

SYSTEM_OBJECTS sysObj;

/********************************* Local functions prototype **********************/

/********************************* API functions **********************************/

void UsbTask(void *parameters)
{
    (void)parameters;

    int count = 0;

    /* Initialize the USB device layer */
    sysObj.usbDevObject0 = USB_DEVICE_Initialize (USB_DEVICE_INDEX_0 , ( SYS_MODULE_INIT* ) & usbDevInitData);

    /* Initialize USB Driver */ 
    sysObj.drvUSBFSObject = DRV_USBFS_Initialize(DRV_USBFS_INDEX_0, (SYS_MODULE_INIT *) &drvUSBFSInit);    


    while(1)
    {
        vTaskDelay(1U / portTICK_PERIOD_MS);
        
        if (count == 0)
        {
            USB_DEVICE_Tasks(sysObj.usbDevObject0);
            count = 4;
        }
        else
        {
            count --;
        }

        APP_Tasks();
    }
}

/*EOF*/
