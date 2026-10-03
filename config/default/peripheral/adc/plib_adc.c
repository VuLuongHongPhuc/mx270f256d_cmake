/*******************************************************************************
  ADC Peripheral Library Interface Source File

  Company
    Microchip Technology Inc.

  File Name
    plib_adc.c

  Summary
    ADC peripheral library source.

  Description
    This file implements the ADC peripheral library.

*******************************************************************************/

// DOM-IGNORE-BEGIN
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
// DOM-IGNORE-END

#include "device.h"
#include "plib_adc.h"


// *****************************************************************************
// *****************************************************************************
// Section: ADC Implementation
// *****************************************************************************
// *****************************************************************************


void ADC_Initialize(void)
{
    /* GPIO configuration */
    ANSELBbits.ANSB0 = 1; /* RB0 as analog pin.21*/
    TRISBbits.TRISB0 = 1; /* RB0 as input */

    //AD1CON1CLR = _AD1CON1_ON_MASK;
    AD1CON1 = 0; /* Default:
                  * ADC module OFF
                  * Continue operation in IDLE
                  * Unsigned integer format
                  * Manual conversion trigger
                  * */
    AD1CON1bits.SIDL = 1;/* No operation in IDLE mode. */
    AD1CON1bits.SSRC = 0b111; /* Auto conversion trigger */

    /* Configure ADC voltage reference and buffer fill modes. */
    AD1CON2 = 0; /* Default: VREF from AVDD and AVSS,
                            Inputs are not scanned,
                            Interrupt every sample */
    
    /* Configure ADC conversion clock */
    AD1CON3 = 0;
    //AD1CON3bits.ADCS = 19; /* conversion duration (=>AD1CON3bits.ADRC=1)*/
    AD1CON3bits.SAMC = 0b11111; /* sampling = 31 TAD (=> AD1CON1bits.SSRC=0b111) */

    /* Configure input channels */
    AD1CHS = 0; /* Default: 
                 * CH0+ input is AN0.
                 * CHO- input is VREFL (AVss) 
                 * */
    AD1CHSbits.CH0SA = 0b0010; /* CH0+ input is AN2. */
    
    AD1CSSL = 0x0000; /* No inputs are scanned.
                        Note: Contents of AD1CSSL are ignored when CSCNA = 0 */

    IFS0bits.AD1IF = 0; /* Clear ADC conversion interrupt*/
    //IPC5bits.AD1IP = 4; /* Interrupt priority [1..7] */
    //IPC5bits.AD1IS = 0; /* Interrupt sub priority [0..3] */
    //IEC0bits.AD1IE = 1;/* Enable ADC conversion interrupt*/

    /* Turn ON ADC */
    AD1CON1SET = _AD1CON1_ON_MASK;
}

void ADC_Enable(void)
{
    AD1CON1SET = _AD1CON1_ON_MASK;
}

void ADC_Disable(void)
{
    AD1CON1CLR = _AD1CON1_ON_MASK;
}

void ADC_SamplingStart(void)
{
    AD1CON1CLR = _AD1CON1_DONE_MASK;
    AD1CON1SET = _AD1CON1_SAMP_MASK;
}

void ADC_ConversionStart(void)
{
    AD1CON1CLR = _AD1CON1_SAMP_MASK;
}

void ADC_InputSelect(ADC_MUX muxType, ADC_INPUT_POSITIVE positiveInput, ADC_INPUT_NEGATIVE negativeInput)
{
    if (muxType == ADC_MUX_B)
    {
        AD1CHSbits.CH0SB = (uint8_t)positiveInput;
        AD1CHSbits.CH0NB = (uint8_t)negativeInput;
    }
    else
    {
        AD1CHSbits.CH0SA = (uint8_t)positiveInput;
        AD1CHSbits.CH0NA = (uint8_t)negativeInput;
    }
}

void ADC_InputScanSelect(ADC_INPUTS_SCAN scanInputs)
{
    AD1CSSL = (uint32_t)scanInputs;
}

/* Check if conversion result is available */
bool ADC_ResultIsReady(void)
{
    return (AD1CON1bits.DONE != 0U);
}

/**
 * @brief Read the conversion result
 * @param bufferNumber The buffer number to read from
 * @return The conversion result
 * @example
 * <code>
 *  ADC_SamplingStart();
 *  while(ADC_ResultIsReady() == false) {};
 *  uint32_t result = ADC_ResultGet(ADC_RESULT_BUFFER_0);
 * </code>
 */
uint32_t ADC_ResultGet(ADC_RESULT_BUFFER bufferNumber)
{
    return (*((&ADC1BUF0) + ((uint32_t)bufferNumber << 2)));
}

