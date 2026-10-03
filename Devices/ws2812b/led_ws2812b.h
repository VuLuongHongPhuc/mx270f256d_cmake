#ifndef _WS2812_HEADER_H_
#define _WS2812_HEADER_H_

/********************************* Includes ***************************************/
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

/********************************* Constants definition ***************************/

/********************************* Macros definition ******************************/

/********************************* Types definition *******************************/

/********************************* Global variable ********************************/

/********************************* API functions prototype ************************/

/**
 * @brief Send a pixel to WS2812B LED strip.
 * @param r Red component (0-255)
 * @param g Green component (0-255)
 * @param b Blue component (0-255)
 * @note This function should be called with interrupts disabled to ensure precise timing.
 * @example
 * <code>
 *  (void)__builtin_disable_interrupts();
 *  WS2812B_SendPixel(255, 0, 0); // Send red pixel on first position
 *  WS2812B_SendPixel(0, 255, 0); // Send green pixel on second position
 *  WS2812B_SendPixel(0, 0, 255); // Send blue pixel on third position
 *  (void)__builtin_enable_interrupts();
 * </code>
 */
void WS2812B_SendPixel(uint8_t r, uint8_t g, uint8_t b);


#ifdef __cplusplus
}
#endif

#endif /* _WS2812_HEADER_H_ */