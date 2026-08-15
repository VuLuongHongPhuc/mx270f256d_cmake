#ifndef _SPI_HEADER_H_
#define _SPI_HEADER_H_

/********************************* Includes ***************************************/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>


#ifdef __cplusplus
extern "C" {
#endif

/********************************* Constants definition ***************************/

/********************************* Macros definition ******************************/

/********************************* Types definition *******************************/

/********************************* Global variable ********************************/

/********************************* API functions prototype ************************/

void SPI2_Initialize(void);
bool SPI2_WriteBytes(uint8_t const * const pBuf, size_t size);
bool SPI2_WriteBytesIT(uint8_t * pBuf, size_t size);


#ifdef __cplusplus
}
#endif

#endif /* _SPI_HEADER_H_ */