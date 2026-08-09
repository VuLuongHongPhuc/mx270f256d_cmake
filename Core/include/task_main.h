#ifndef __TASK_MAIN_H_
#define __TASK_MAIN_H_

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
} TaskMainParam_t;

/********************************* Global variable ********************************/
/********************************* API functions prototype ************************/

void MainTask(void *parameters);


#ifdef __cplusplus
}
#endif

#endif /* __TASK_MAIN_H_ */