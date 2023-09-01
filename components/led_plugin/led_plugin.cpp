#include <stdio.h>
#include "led_plugin.hpp"

#include "button.h"
#include "esp_log.h"
#include "esp_err.h"
#include "driver/gpio.h"

#include "lcd_utils.hpp"
#include "led_utils.hpp"
#include "button_utils.hpp"

#define TAG "led_plugin"

LGFX_LiLyGo_TDongleS3 *lcd_ptr;

void led_plugin_press_down(button_t *btn, button_state_t event)
{
    const char *states[] =
        {
            [BUTTON_PRESSED] = "pressed",
            [BUTTON_RELEASED] = "released",
            [BUTTON_CLICKED] = "clicked",
            [BUTTON_PRESSED_LONG] = "pressed long",
        };
    ESP_LOGI(TAG, "Button %s", states[event]);
    ESP_LOGI(TAG, "Button pressed");
    led(uintToRgb(0xffffffu));
}

void led_plugin_entry(LGFX_LiLyGo_TDongleS3 *lcd_ptr1)
{

    // button_t btn = *button_get_button();
    while (gpio_get_level(GPIO_NUM_0) == 0)
    {
        ESP_LOGI(TAG, "Waiting for button to be released");
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }

    ESP_LOGI(TAG, "Entered led_plugin_entry()");

    lcd_ptr = lcd_ptr1;
    LGFX_LiLyGo_TDongleS3 lcd = *lcd_ptr;

    drawPage(lcd, 1, 2, "LED", "Uhuu!");
    ESP_LOGI(TAG, "lcd.clear()");

    button_register_cb(led_plugin_press_down);
    ESP_LOGI(TAG, "btn.callback = led_plugin_on_button");

    led(uintToRgb(0x0000ffu));
    while (1)
    {
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
    return;
}
