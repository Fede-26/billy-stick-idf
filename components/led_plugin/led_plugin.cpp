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

// button_t btn;
LGFX_LiLyGo_TDongleS3* lcd_ptr;
// static button_t btn;
// static LGFX_LiLyGo_TDongleS3 lcd;


void led_plugin_press_down(button_t *btn, button_state_t event)
{
   
    // LGFX_LiLyGo_TDongleS3 lcd = *(LGFX_LiLyGo_TDongleS3 *)usr_data;
    ESP_LOGI(TAG, "Button pressed");
    led(uintToRgb(0xffffffu));
}

void led_plugin_entry(LGFX_LiLyGo_TDongleS3 *lcd_ptr1)
{
    // while (button_get_event() == BUTTON_PRESS_DOWN)
    // {
    //     ESP_LOGI(TAG, "Button pressed too long");
    // }
    // Wait for gpio 0 to be high
    button_t btn = *button_get_button();
    while (gpio_get_level(GPIO_NUM_0) == 0){
        ESP_LOGI(TAG, "Waiting for button to be released");
        // ESP_LOGI(TAG, "Button get status: %d", );
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    // button_unregister_all();
    ESP_LOGI(TAG, "Entered led_plugin_entry()");
    lcd_ptr = lcd_ptr1;
    LGFX_LiLyGo_TDongleS3 lcd = *lcd_ptr;
    // clear the lcd
    //  lcd.init();
    drawPage(lcd, 1, 2, "LED", "Uhuu!");
    // lcd.clear(0x000000u);       // ERROR: I don't know why this doesn't work
    ESP_LOGI(TAG, "lcd.clear()");
    button_register_cb(led_plugin_press_down);
    // reinit_button();
    // button_unregister_all();
    // button_register_cb(BUTTON_PRESS_DOWN, led_plugin_press_down, NULL);
    ESP_LOGI(TAG, "btn.callback = led_plugin_on_button");

    led(uintToRgb(0x0000ffu));
    while (1)
    {
        vTaskDelay(500 / portTICK_PERIOD_MS);
        // led(uintToRgb(0x00ff00u));
        // vTaskDelay(500 / portTICK_PERIOD_MS);
    }
    return;
}
