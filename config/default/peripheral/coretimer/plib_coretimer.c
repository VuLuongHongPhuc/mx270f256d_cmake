/*******************************************************************************
  Core Timer Peripheral Library

  Company:
    Microchip Technology Inc.

  File Name:
    plib_coretimer.c

  Summary:
    Core timer Source File

  Description:
    None

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

#include "device.h"
#include "plib_coretimer.h"


volatile static uint32_t _compare;
volatile static CORETIMER_OBJECT coreTmr;

void CORETIMER_Initialize(void)
{
    CORETIMER_Stop();

    /* stop timer in debug mode */
    _CP0_SET_DEBUG(_CP0_GET_DEBUG() & ~_CP0_DEBUG_COUNTDM_MASK);

    /* Set period for 1 ms */
    CORETIMER_PeriodSet(1);

    CORETIMER_Reset();

    /* Set interrupt priority */
    IPC0bits.CTIP = 1; /* Interrupt priority [1..7] */
    IPC0bits.CTIS = 0; /* Interrupt sub priority [0..3] */

    coreTmr.callback = NULL;
}

void CORETIMER_CallbackSet ( CORETIMER_CALLBACK callback, uintptr_t context )
{
    coreTmr.callback = callback;
    coreTmr.context = context;
}

uint32_t CORETIMER_GetTickCount(void)
{
    return coreTmr.tickCounter;
}

void CORETIMER_Reset(void)
{
    _compare = coreTmr.period;
    coreTmr.tickCounter = 0;

    /* Clear Core Timer */
    _CP0_SET_COUNT(0);
    _CP0_SET_COMPARE(_compare);
}

void CORETIMER_PeriodSet ( uint32_t period )
{
    coreTmr.period = period * N_TICKS_PER_MS;
}

void CORETIMER_Start(void)
{
    /* Disable Interrupt */
    IEC0CLR=0x1;

    /* Clear flag */
    IFS0CLR = 0x1;
    
    /* Enable Timer by clearing Disable Count (DC) bit */
    _CP0_SET_CAUSE(_CP0_GET_CAUSE() & (~_CP0_CAUSE_DC_MASK));
    
    /* Enable Interrupt */
    IEC0SET=0x1;
}

void CORETIMER_Stop( void )
{
    /* Disable Timer by setting Disable Count (DC) bit */
    _CP0_SET_CAUSE(_CP0_GET_CAUSE() | _CP0_CAUSE_DC_MASK);

    /* Disable Interrupt */
    IEC0CLR=0x1;
}

uint32_t CORETIMER_FrequencyGet ( void )
{
    return (CORE_TIMER_FREQUENCY);
}

void __ISR(_CORE_TIMER_VECTOR, IPL1AUTO) _CORETIMER_InterruptHandler(void)
{
    uint32_t status = IFS0bits.CTIF;
    coreTmr.tickCounter++;
    if(coreTmr.callback != NULL)
    {
        uintptr_t context = coreTmr.context;
        coreTmr.callback(status, context);
    }

    /* NOTE: 50 minimum for next compare */
    _compare += coreTmr.period;
    _CP0_SET_COMPARE(_compare);

    /* Clear flag */
    IFS0CLR = 0x1;
}

void CORETIMER_DelayMs ( uint32_t delay_ms)
{
    uint32_t startCount, endCount;

    /* Calculate the end count for the given delay */
    endCount=(CORE_TIMER_FREQUENCY / 1000U) * delay_ms;

    startCount=_CP0_GET_COUNT();
    while((_CP0_GET_COUNT() - startCount) < endCount)
    {
        /* Wait for compare match */
    }
}

void CORETIMER_DelayUs ( uint32_t delay_us)
{
    uint32_t startCount, endCount;

    /* Calculate the end count for the given delay */
    endCount=(CORE_TIMER_FREQUENCY / 1000000U) * delay_us;

    startCount=_CP0_GET_COUNT();
    while((_CP0_GET_COUNT() - startCount) < endCount)
    {
        /* Wait for compare match */
    }
}

