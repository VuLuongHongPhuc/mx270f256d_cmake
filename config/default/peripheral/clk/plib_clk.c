/*******************************************************************************
  SYS CLK Static Functions for Clock System Service

  Company:
    Microchip Technology Inc.

  File Name:
    plib_clk.c

  Summary:
    SYS CLK static function implementations for the Clock System Service.

  Description:
    The Clock System Service provides a simple interface to manage the
    oscillators on Microchip microcontrollers. This file defines the static
    implementation for the Clock System Service.

  Remarks:
    Static functions incorporate all system clock configuration settings as
    determined by the user via the Microchip Harmony Configurator GUI.
    It provides static version of the routines, eliminating the need for an
    object ID or object handle.

    Static single-open interfaces also eliminate the need for the open handle.

*******************************************************************************/

/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Include Files
// *****************************************************************************
// *****************************************************************************

#include "device.h"
#include "plib_clk.h"

// *****************************************************************************
// *****************************************************************************
// Section: File Scope Functions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    void CLK_Initialize( void )

  Summary:
    Initializes hardware and internal data structure of the System Clock.

  Description:
    This function initializes the hardware and internal data structure of System
    Clock Service.

  Remarks:
    This is configuration values for the static version of the Clock System
    Service module is determined by the user via the MHC GUI.

    The objective is to eliminate the user's need to be knowledgeable in the
    function of the 'configuration bits' to configure the system oscillators.
*/

void CLK_Initialize( void )
{

    /* Code for fuse settings can be found in "initialization.c" */


    /* Wait for PLL to be locked */
    while(OSCCONbits.SLOCK == 0U)
    {
        /* Nothing to do */
    }

    /* Peripheral Module Disable Configuration */

    //value |= 0x0001U; /* AD1MD */
    //value |= 0x0100U; /* CTMUMD */
    //value |= 0x1000U; /* CVRMD */
    PMD1     = 0x1101U;

    //value |= 0x0001U; /* CMP1MD */
    //value |= 0x0002U; /* CMP2MD */
    //value |= 0x0004U; /* CMP3MD */
    PMD2     = 0x0007U;

    //value |= 0x000001U; /* IC1MD */
    //value |= 0x000002U; /* IC2MD */
    //value |= 0x000004U; /* IC3MD */
    //value |= 0x000008U; /* IC4MD */
    //value |= 0x000010U; /* IC5MD */
    //value |= 0x010000U; /* OC1MD */
    //value |= 0x020000U; /* OC2MD */
    //value |= 0x040000U; /* OC3MD */
    //value |= 0x080000U; /* OC4MD */
    //value |= 0x100000U; /* OC5MD */
    PMD3     = 0x1f001fU;

    //value |= 0x0001U; /* T1MD */
    //value |= 0x0002U; /* T2MD */
    //value |= 0x0004U; /* T3MD */
    //value |= 0x0008U; /* T4MD */
    //value |= 0x0010U; /* T5MD */
    PMD4     = 0x001eU;

    //value |= 0x0000001U; /* U1MD - UART1 */
    //value |= 0x0000002U; /* U2MD - UART2 */
    //value |= 0x0000100U; /* SPI1MD */
    //value |= 0x0000200U; /* SPI2MD - use */
    //value |= 0x0010000U; /* I2C1MD */
    //value |= 0x0020000U; /* I2C2MD */
    //value |= 0x1000000U; /* USB - use */
    PMD5     = 0x0030103U;

    //value |= 0x00001U; /* RTCCMD */
    //value |= 0x00002U; /* REFOMD */
    //value |= 0x10000U; /* PMPMD */
    PMD6     = 0x10001U;
}
