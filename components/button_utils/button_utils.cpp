#include <stdio.h>
#include "esp_log.h"
#include "button_utils.hpp"
#include "button.h"

#define TAG "button_utils"

button_t gpio_btn;
bool isButtonInit = false;

button_t* button_get_button(void)
{
    if (!isButtonInit)
    {
        ESP_ERROR_CHECK(button_init(&gpio_btn, GPIO_NUM_0, tskIDLE_PRIORITY+10, configMINIMAL_STACK_SIZE*4));
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

// // cb type: static void button_single_click_cb(void *arg,void *usr_data)
// void button_register_cb(button_event_t event, button_cb_t cb, void *arg)
// {
//     if (NULL != gpio_btn)
//     {
//         ESP_ERROR_CHECK(iot_button_register_cb(gpio_btn, event, cb, arg));
//     }
//     else
//     {
//         ESP_LOGE(TAG, "button_register_cb() failed: Button handle is NULL");
//     }
// }


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

    button_unregister_cb(&gpio_btn, SHORT_TIME);
    button_unregister_cb(&gpio_btn, MEDIUM_TIME);
    button_unregister_cb(&gpio_btn, LONG_TIME);
}

// button_event_t button_get_event(void)
// {
//     if (NULL != gpio_btn)
//     {
//         return iot_button_get_event(gpio_btn);
//     }
//     return BUTTON_NONE_PRESS;
// }