#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "sdkconfig.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_log.h"

#include "button.h"

#include "lcd_utils.hpp"
#include "led_utils.hpp"
#include "button_utils.hpp"
#include "led_plugin.hpp"

#define TAG "main"

LGFX_LiLyGo_TDongleS3 lcd;

void on_button_long(void *arg)
{

    unsigned int white = 0xffffffu;
    unsigned int black = 0x000000u;
    unsigned int red = 0xff0000u;
    unsigned int green = 0x00ff00u;
    unsigned int blue = 0x0000ffu;
    // led(uintToRgb(blue));
    ESP_LOGI(TAG, "Button pressed long");
    button_unregister_all();
    led_plugin_entry(&lcd);
}

extern "C" void app_main(void)
{

    ESP_LOGI(TAG, "Initializing LED");
    led_init();

    ESP_LOGI(TAG, "Initializing button");
    //
    // Push button connected to GPIO0:
    //
    // button_t btn;
    button_t btn = *button_get_button();
    ESP_ERROR_CHECK(button_register_cb(&btn, SHORT_TIME, on_button_long, NULL));

    // ESP_ERROR_CHECK(button_init(&btn));

    ESP_LOGI(TAG, "Initializing LCD");
    //
    // Display, ST7735s on SPI bus
    //
    if (!lcd.init())
    {
        ESP_LOGW(TAG, "lcd.init() failed");
        return;
    }
    lcd.setBrightness(255);

    drawPage(lcd, 1, 2, "Billy Stick", "Hello, World!");

    while (1)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
