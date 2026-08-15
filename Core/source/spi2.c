

/********************************* Includes ***************************************/

#include <stdbool.h>

#include <FreeRTOS.h>
#include <semphr.h>

#include <xc.h>
#include <sys/attribs.h>  // IPLxAUTO, IPLxSRS, __ISR

#include "spi2.h"

/********************************* Constants definition ***************************/

#define DEF_DUMMY_DATA  0xffffffff

#define DEF_FIFO_BUFFER_SIZE    4

/********************************* Macros definition ******************************/

/********************************* Types definition *******************************/

typedef struct
{
    uint8_t * txBuf;
    size_t size;
    size_t index;
}SpiBuffer_t;

static SpiBuffer_t _status = { NULL, 0, 0 };

/********************************* Local variable *********************************/

SemaphoreHandle_t _xSemaphore = NULL;
 StaticSemaphore_t _xSemaphoreBuffer;

/********************************* Local prototypes *******************************/

static void InitializeGPIO(void);
static void fillTxBufferFifo(void);

/********************************* API functions prototype ************************/


void SPI2_Initialize(void)
{
    _xSemaphore = xSemaphoreCreateBinaryStatic( &_xSemaphoreBuffer );
    if (_xSemaphore == NULL)
    {
        /* Create failed */
    }

    InitializeGPIO();

    /*
     * SPI2CON
     * SPI2STAT
     * SPI2BUF
     * SPI2BRG
     * SPI2CON2
     */
    
    uint32_t dummyData = 0U;

    /* Disable SPI2 Interrupts */
    IEC1CLR = 0x40000;
    IEC1CLR = 0x80000;
    IEC1CLR = 0x100000;

    /* STOP and Reset the SPI */
    SPI2CON = 0;

    /* Clear the Receiver buffer */
    dummyData = SPI2BUF;
    (void)dummyData;

    /* Clear SPI2 Interrupt flags */
    IFS1CLR = 0x40000;
    IFS1CLR = 0x80000;
    IFS1CLR = 0x100000;

    /* BAUD Rate register Setup */
    SPI2BRG = 19; /* 1.000.000 Hz */
    //SPI2BRG = 39; /* 500.000 Hz */

    /* CLear RX flag Overflow */
    SPI2STATCLR = _SPI2STAT_SPIROV_MASK;

    /*
    MSTEN = 1
    CKP = 0
    CKE = 1
    MODE<32,16> = 0
    ENHBUF = 1
    MSSEN = 0
    MCLKSEL = 0
    */
    /* SPI CONTROL REGISTER p.173 */
    SPI2CONbits.MSTEN   = 1;  /*!< Master Mode Enable bit */
    SPI2CONbits.CKP     = 0;  /*!< Clock Polarity Select bit. 0 = Idle state for clock is a low level; active state is a high level */
    SPI2CONbits.CKE     = 1;  /*!< SPI Clock Edge Select bit. 1 = Serial output data changes on transition from active clock state to Idle clock state (see CKP bit) */
    SPI2CONbits.ENHBUF  = 1;  /*!< Enhanced Buffer Enable bit */
    SPI2CONbits.MODE16  = 0;  /*!< 32/16-Bit Communication Select bits. 00 = 8-bit communication */
    SPI2CONbits.MODE32  = 0;
    SPI2CONbits.MSSEN   = 0;  /*!< Slave Select Enable (CS). 0 = SSx pin not used for Slave mode, pin controlled by port function. */
    SPI2CONbits.MCLKSEL = 0;  /*!< Master Clock Enable bit. 0 = PBCLK2 is used by the Baud Rate Generator */
    SPI2CONbits.STXISEL = 0;  /*!< SPI Transmit Buffer Empty Interrupt Mode bits. 00 = Shift and FIFO empty*/
    SPI2CONbits.SRXISEL = 1;  /*!< SPI Receive Buffer Full Interrupt Mode bits. 01 = Interrupt is generated when the buffer is not empty */

    
    /* Initialize Transfer Done interrupt p.69 */
    IPC9bits.SPI2IP = 1;    /*!< Error, RX, TX priority 0-7 */
    IPC9bits.SPI2IS = 0;    /*!< Error, RX, TX sub priority 0-3 */
    
    /* Enable Transfer Done Interrupt */
    //IEC1SET |= _IEC1_SPI2EIE_MASK;    /*!< Enable Error interrupt -> IFS1<18> */
    //IEC1SET |= _IEC1_SPI2RXIE_MASK;   /*!< Enable RX interrupt    -> IFS1<19> */
    //IEC1SET |= _IEC1_SPI2TXIE_MASK;   /*!< Enable TX interrupt    -> IFS1<20> */

    /* OVERFLOW */    
    SPI2CON2bits.IGNROV = 1;// ignore overflow RX
    SPI2CON2bits.IGNTUR = 1;// ignore overflow TX
    
    dummyData = SPI2BUF;          /*!< Read rx buffer to reset flag FIFO */
    (void)dummyData;              /*!< dummy -> prevent warning at build */
    
    /* Enable SPI2 */
    SPI2CONSET = _SPI2CON_ON_MASK;
}

static void InitializeGPIO()
{
    /* SPI SSD1306
    - SDI  RC6    2 --> MISO
    - SDO  RC8    4 --> MOSI
    - SCK1 RB15  15
    - RST  RB0   21
    - DC   RB1   22
    - CS   RB2   23
    */

    LATBbits.LATB2 = 1;    /* CS */
    
    TRISBCLR  = 0x8007;    /* RB0, RB1, RB2, RB15 as output */ 
    ANSELBCLR = 0x8007;    /* Digital Mode Enable */
    TRISCCLR = 1 << 8;     /* RC8 as output */

    /* PPS Input Remapping RC6 -> MISO */
    //SDI2R = 5;

    /* PPS Output Remapping RC8 -> MOSI */
    RPC8R = 4;
}

bool SPI2_WriteBytes(uint8_t const * const pBuf, size_t size)
{
    if ((NULL == pBuf) || (0 == size))
    {
        return false;
    }
    
    /* Clear the receive overflow error if any */
    SPI2STATCLR = _SPI2STAT_SPIROV_MASK;

    while((SPI2STAT & _SPI2STAT_SPITBE_MASK) == 0U)
    {
        /* Wait for transmit buffer to be empty */
    }

    for(int i=0; i<size; i++)
    {
        SPI2BUF = ((uint8_t*)pBuf)[i];

        while((SPI2STAT & _SPI2STAT_SPITBE_MASK) == 0U)
        {
            /* Wait for transmit buffer to be empty */
        }
    }
    
    /* Make sure no data is pending in the shift register */
    while((SPI2STAT & _SPI2STAT_SRMT_MASK) == 0U)
    {
        /* Data pending in shift register */
    }

    return true;
}

bool SPI2_WriteBytesIT(uint8_t * pBuf, size_t size)
{
    if ((NULL == pBuf) || (0 == size))
    {
        return false;
    }
    
    /* Clear the receive overflow error if any */
    SPI2STATCLR = _SPI2STAT_SPIROV_MASK;
    
    while((SPI2STAT & _SPI2STAT_SPITBE_MASK) == 0U)
    {
        /* Wait for transmit buffer to be empty */
    }

    _status.index = 0;
    _status.size = size;
    _status.txBuf = pBuf;

    fillTxBufferFifo();

    /* Clear interrupt flag */
    IFS1CLR = _IFS1_SPI2TXIF_MASK; /* Clear interrupt flag */
    IFS1CLR = _IFS1_SPI2RXIF_MASK; /* Clear interrupt flag */
    IFS1CLR = _IFS1_SPI2EIF_MASK; /* Clear interrupt flag */

    /* Enable transmit interrupt to complete the transfer in ISR context */
    IEC1SET = _IEC1_SPI2TXIE_MASK;

    if (xSemaphoreTake(_xSemaphore, 1000) == pdPASS)
    {
        return true;
    }

    return false;
}

bool SPI2_Busy()
{
    if ((SPI2STAT & _SPI2STAT_SRMT_MASK) != 0U)
    {
        /* Clear receiver overflow error if any */
        SPI2STATCLR = _SPI2STAT_SPIROV_MASK;

        /* Disable transmit interrupt */
        IEC1CLR = _IEC1_SPI2TXIE_MASK;

        return true;
    }
    
    return false;
}

static void fillTxBufferFifo(void)
{
    if ((_status.size == 0) || (_status.index == _status.size))
    {
        return;
    }

    int count = DEF_FIFO_BUFFER_SIZE;
            
    do
    {
        SPI2BUF = ((uint8_t*)_status.txBuf)[_status.index++];

        if (_status.index == _status.size)
        {
            break;
        }

        count --;
    } while (count == 0);
}

void __ISR(_SPI_2_VECTOR, IPL1AUTO) _InterruptSpi2Handler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if((SPI2STAT & _SPI2STAT_SPITBE_MASK) == _SPI2STAT_SPITBE_MASK)
    {
        SPI2STATCLR = _SPI2STAT_SPIROV_MASK; /* Clear receiver overflow error if any */

        /* Send remaining buffer */
        if (_status.index != _status.size)
        {
            fillTxBufferFifo();
        }
        else
        {
            xSemaphoreGiveFromISR(_xSemaphore, &xHigherPriorityTaskWoken);
                
            IEC1CLR = _IEC1_SPI2TXIE_MASK; /* Disable transmit interrupt */
        }
    }

    
    IFS1CLR = _IFS1_SPI2TXIF_MASK; /* Clear interrupt flag */
    //IFS1CLR = _IFS1_SPI2RXIF_MASK; /* Clear interrupt flag */
    //IFS1CLR = _IFS1_SPI2EIF_MASK; /* Clear interrupt flag */

    if (xHigherPriorityTaskWoken != pdFALSE)
    {
        portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
    }
}

/*EOF*/
