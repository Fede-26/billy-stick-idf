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

void on_button_long(button_t *btn, button_state_t event)
{
    if (event == BUTTON_RELEASED)
    {
        ESP_LOGI(TAG, "Button pressed");
        // button_unregister_all();


        //TODO HACK SOMETHING: We need to start a new task, because the current task is the one that is running the plugin and the callback, so the callback never returns...
        led_plugin_entry(&lcd);
    }
}

extern "C" void app_main(void)
{

    ESP_LOGI(TAG, "Initializing LED");
    led_init();

    ESP_LOGI(TAG, "Initializing button");
    // Push button connected to GPIO0:
    button_t btn = *button_get_button();
    button_register_cb(on_button_long);

    ESP_LOGI(TAG, "Initializing LCD");
    // Display, ST7735s on SPI bus
    if (!lcd.init())
    {
        ESP_LOGW(TAG, "lcd.init() failed");
        return;
    }
    lcd.setBrightness(255);



    // Stuff
    drawPage(lcd, 1, 2, "Billy Stick", "Hello, World!");

    while (1)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
