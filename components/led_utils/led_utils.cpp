#include <stdio.h>
#include "led_utils.hpp"
#include "led_strip_spi.h"
#include "esp_log.h"

#define TAG "led_utils"

static led_strip_spi_t strip;
static spi_device_handle_t device_handle;

void led_init()
{
    led_strip_spi_install();
    strip = LED_STRIP_SPI_DEFAULT();

    strip.mosi_io_num = RGBLED_DI;
    strip.sclk_io_num = RGBLED_CI;
    strip.length = LEDSTRIP_LEN;
    strip.device_handle = device_handle;
    strip.max_transfer_sz = LED_STRIP_SPI_BUFFER_SIZE(LEDSTRIP_LEN);
    strip.clock_speed_hz = 1000000 * 10; // 10Mhz

    ESP_ERROR_CHECK(led_strip_spi_init(&strip));
    ESP_ERROR_CHECK(led_strip_spi_flush(&strip));
    return;
}

rgb_t uintToRgb(unsigned int color)
{
    return rgb_from_code(color);
}

void led(rgb_t color)
{
    led_strip_spi_t *strip_ptr = &strip;

    esp_err_t err = led_strip_spi_fill(strip_ptr, 0, LEDSTRIP_LEN, color);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "led_strip_spi_fill(): %s", esp_err_to_name(err));
    }
    ESP_ERROR_CHECK(led_strip_spi_flush(strip_ptr));
    return;
}
