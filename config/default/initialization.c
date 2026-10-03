
/********************************* Includes ***************************************/

#include "initialization.h"
#include "plib_clk.h"
#include "plib_gpio.h"
#include "plib_evic.h"
#include "app.h"
#include "hardware.h"
#include "spi2.h"
#include "plib_i2c_master_common.h"
#include "plib_i2c1_master.h"
#include "plib_coretimer.h"
#include "plib_adc.h"

/********************************* Section: Configuration Bits ********************/

/*** DEVCFG0 ***/
#pragma config DEBUG =      OFF
#pragma config JTAGEN =     OFF
#pragma config ICESEL =     ICS_PGx3
#pragma config PWP =        OFF
#pragma config BWP =        OFF
#pragma config CP =         OFF


/*** DEVCFG1 ***/
#pragma config FNOSC =      PRIPLL
#pragma config FPBDIV =     DIV_1
#pragma config FSOSCEN =    OFF
#pragma config IESO =       OFF
#pragma config POSCMOD =    EC
#pragma config OSCIOFNC =   OFF
#pragma config FCKSM =      CSDCMD
#pragma config WDTPS =      PS1048576
#pragma config FWDTEN =     OFF
#pragma config WINDIS =     OFF
#pragma config FWDTWINSZ =  WINSZ_50


/*** DEVCFG2 ***/
#pragma config FPLLIDIV =   DIV_2
#pragma config FPLLMUL =    MUL_20
#pragma config FPLLODIV =   DIV_2
#pragma config UPLLEN =     ON
#pragma config UPLLIDIV =   DIV_2

/*** DEVCFG3 ***/
#pragma config FVBUSONIO =  OFF     /* Control by USB : OFF - use to control external power switch */
#pragma config USERID =     0xffff
#pragma config PMDL1WAY =   ON
#pragma config IOL1WAY =    OFF
#pragma config FUSBIDIO =   OFF     /* Control by USB : OFF -> IO is free to use */





void SYS_Initialize ( void* data )
{
    /* Start out with interrupts disabled before configuring any modules */
    (void)__builtin_disable_interrupts();

    CLK_Initialize();

    /* Configure KSEG0 as cacheable memory. This is needed for Prefetch Buffer */
    __builtin_mtc0(16, 0,(__builtin_mfc0(16, 0) | 0x3U));

    /* Set the SRAM wait states to One */
    BMXCONbits.BMXWSDRM = 1;


    GPIO_Initialize();
    CORETIMER_Initialize();
    
    //SPI2_Initialize();
    I2C1_Initialize();
    ADC_Initialize();


    APP_Initialize();


    EVIC_Initialize();

    /* Enable global interrupts */
    (void)__builtin_enable_interrupts();
}

/*******************************************************************************
 End of File
*/
