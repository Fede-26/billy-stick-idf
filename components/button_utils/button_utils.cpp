#include <stdio.h>
#include "esp_log.h"
#include "button_utils.hpp"
#include "button.h"

#define TAG "button_utils"

static button_t gpio_btn;
bool isButtonInit = false;
static button_event_cb_t callback;

void button_event_cb(button_t *btn, button_state_t event)
{
    ESP_LOGI(TAG, "Callback called");
    if (NULL != callback)
    {
        callback(&gpio_btn, event);
    }
}

button_t *button_get_button(void)
{
    if (!isButtonInit)
    {
        //
        // Push button connected to GPIO0:
        //
        gpio_btn.gpio = (gpio_num_t)0;
        gpio_btn.pressed_level = 0;
        gpio_btn.internal_pull = true;
        gpio_btn.autorepeat = false;
        gpio_btn.callback = button_event_cb;
        ESP_ERROR_CHECK(button_init(&gpio_btn));
        isButtonInit = true;
        // ESP_LOGE(TAG, "Button create failed");
    }
    return &gpio_btn;
}

// void button_destroy(button_handle_t btn_handle)
// {
//     if (NULL != btn_handle)
//     {
//         iot_button_delete(btn_handle);
//     }
//     else
//     {
//         ESP_LOGE(TAG, "button_delete() failed: Button handle is NULL");
//     }
// }

// cb type: static void button_single_click_cb(void *arg,void *usr_data)
void button_register_cb(button_event_cb_t cb)
{
    callback = cb;
}

// void button_unregister_cb(button_event_t event)
// {
//     if (NULL != gpio_btn && iot_button_count_event(gpio_btn, event) > 0)
//     {
//         iot_button_unregister_cb(gpio_btn, event);
//     }
//     else
//     {
//         ESP_LOGE(TAG, "button_unregister_cb() failed: Button handle is NULL or event not registered");
//     }
// }

void button_unregister_all(void)
{
    callback = NULL;
    // button_unregister_cb(&gpio_btn, SHORT_TIME);
    // button_unregister_cb(&gpio_btn, MEDIUM_TIME);
    // button_unregister_cb(&gpio_btn, LONG_TIME);
}

void reinit_button(void)
{
    ESP_ERROR_CHECK(button_done(&gpio_btn));
    ESP_ERROR_CHECK(button_init(&gpio_btn));
}

// button_event_t button_get_event(void)
// {
//     if (NULL != gpio_btn)
//     {
//         return iot_button_get_event(gpio_btn);
//     }
//     return BUTTON_NONE_PRESS;
// }