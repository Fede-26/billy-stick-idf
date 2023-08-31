#ifndef LED_UTILS_HPP
#define LED_UTILS_HPP

#include "led_strip_spi.h"

// RGB led hardware configuration:
#define RGBLED_CI       39
#define RGBLED_DI       40
#define LEDSTRIP_LEN     1

void led_init();
rgb_t uintToRgb(unsigned int color);
void led(rgb_t color);
#endif // LED_UTILS_HPP