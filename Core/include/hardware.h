
#ifndef _HARDWARE_H
#define _HARDWARE_H



/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif



//#define _XTAL_FREQ 8000000 pour la macro __delay_ms()
    
#define HIGH    1
#define LOW     0
    
#define OUTPUT_PIN  0
#define INPUT_PIN   1
#define PULL_UP     1


// *** LED ***********************************************************
/*** Macros for LED D2 RA10 pin.12 ***/
#define LED_D2_Set()               (LATASET  = 1<<10)
#define LED_D2_Clear()             (LATACLR  = 1<<10)
#define LED_D2_Toggle()            (LATAINV  = 1<<10)
#define LED_D2_OutputEnable()      (TRISACLR = 1<<10)
#define LED_D2_InputEnable()       (TRISASET = 1<<10)
#define LED_D2_Get()               ((PORTA >> 10) & 0x1)
#define LED_D2_PIN                  GPIO_PIN_RA10

/*** Macros for LED D3 RA7 pin.13 ***/
#define LED_D3_Set()               (LATASET  = 1<<7)
#define LED_D3_Clear()             (LATACLR  = 1<<7)
#define LED_D3_Toggle()            (LATAINV  = 1<<7)
#define LED_D3_OutputEnable()      (TRISACLR = 1<<7)
#define LED_D3_InputEnable()       (TRISASET = 1<<7)
#define LED_D3_Get()               ((PORTA >> 7) & 0x1)
#define LED_D3_PIN                  GPIO_PIN_RA7

/*** Macros for LED D4 RA8 pin.32 ***/
#define LED_D4_Set()               (LATASET  = 1<<8)
#define LED_D4_Clear()             (LATACLR  = 1<<8)
#define LED_D4_Toggle()            (LATAINV  = 1<<8)
#define LED_D4_OutputEnable()      (TRISACLR = 1<<8)
#define LED_D4_InputEnable()       (TRISASET = 1<<8)
#define LED_D4_Get()               ((PORTA >> 8) & 0x1)
#define LED_D4_PIN                  GPIO_PIN_RA8


// *** SWITCH BOUTON ***********************************************************
#define BTN_IGNORE_FACTOR 10

//pin.33 RB4
#define SW1_tris()          (TRISBbits.TRISB4=INPUT_PIN)
#define SW1_Set_pullup()    (CNPUBbits.CNPUB4=PULL_UP)
#define SW1_port()          (PORTBbits.RB4)

#define SW1_Set()               (LATBSET  = 1<<4)
#define SW1_Clear()             (LATBCLR  = 1<<4)
#define SW1_Toggle()            (LATBINV  = 1<<4)
#define SW1_OutputEnable()      (TRISBCLR = 1<<4)
#define SW1_InputEnable()       (TRISBSET = 1<<4)
#define SW1_Get()               ((PORTB>>4) & 0x1)
#define SW1_PIN                  GPIO_PIN_RB4


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
