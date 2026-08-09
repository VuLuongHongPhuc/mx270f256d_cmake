
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
/*** Macros for LED_blue pin.12 ***/
#define LED_blue_Set()               (LATASET = (1<<10))
#define LED_blue_Clear()             (LATACLR = (1<<10))
#define LED_blue_Toggle()            (LATAINV = (1<<10))
#define LED_blue_OutputEnable()      (TRISACLR = (1<<10))
#define LED_blue_InputEnable()       (TRISASET = (1<<10))
#define LED_blue_Get()               ((PORTA >> 10) & 0x1)
#define LED_blue_PIN                  GPIO_PIN_RA10

/*** Macros for LED_green pin.13 ***/
#define LED_green_Set()               (LATASET = (1<<7))
#define LED_green_Clear()             (LATACLR = (1<<7))
#define LED_green_Toggle()            (LATAINV = (1<<7))
#define LED_green_OutputEnable()      (TRISACLR = (1<<7))
#define LED_green_InputEnable()       (TRISASET = (1<<7))
#define LED_green_Get()               ((PORTA >> 7) & 0x1)
#define LED_green_PIN                  GPIO_PIN_RA7

/*** Macros for LED_ambre pin.32 ***/
#define LED_ambre_Set()               (LATASET = (1<<8))
#define LED_ambre_Clear()             (LATACLR = (1<<8))
#define LED_ambre_Toggle()            (LATAINV = (1<<8))
#define LED_ambre_OutputEnable()      (TRISACLR = (1<<8))
#define LED_ambre_InputEnable()       (TRISASET = (1<<8))
#define LED_ambre_Get()               ((PORTA >> 8) & 0x1)
#define LED_ambre_PIN                  GPIO_PIN_RA8


// *** SWITCH BOUTON ***********************************************************
#define BTN_IGNORE_FACTOR 10

//pin.33 RB4
#define SW1_tris()          (TRISBbits.TRISB4=INPUT_PIN)
#define SW1_Set_pullup()    (CNPUBbits.CNPUB4=PULL_UP)
#define SW1_port()          (PORTBbits.RB4)

#define SW1_Set()               (LATBSET = (1<<4))
#define SW1_Clear()             (LATBCLR = (1<<4))
#define SW1_Toggle()            (LATBINV = (1<<4))
#define SW1_OutputEnable()      (TRISBCLR = (1<<4))
#define SW1_InputEnable()       (TRISBSET = (1<<4))
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
