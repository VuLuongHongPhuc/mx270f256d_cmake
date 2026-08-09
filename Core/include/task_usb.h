/**
 * @file task_usb.h
 * @brief Task Usb.
 * 
 * @author Phuc VU
 * @date 2026-08-09
 */

#ifndef _TASK_USB_H_
#define _TASK_USB_H_

/********************************* Includes ***************************************/
#include <stdint.h>
#include <FreeRTOS.h>
#include <task.h>

#ifdef __cplusplus
extern "C" {
#endif

/********************************* Constants definition ***************************/
/********************************* Macros definition ******************************/
/********************************* Types definition *******************************/

typedef struct
{
    uint8_t      task_id;
} TaskUsbParam_t;

/********************************* Global variable ********************************/
/********************************* API functions prototype ************************/

void UsbTask(void *parameters);


#ifdef __cplusplus
}
#endif

#endif /* _TASK_USB_H_ */