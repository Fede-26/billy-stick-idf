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


#define TAG "main"
static LGFX_LiLyGo_TDongleS3 lcd;

button_t btn;

unsigned int white = 0xffffffu;
unsigned int black = 0x000000u;
unsigned int red = 0xff0000u;
unsigned int green = 0x00ff00u;
unsigned int blue = 0x0000ffu;

void on_button(button_t *btn, button_state_t state)
{
  if (state == BUTTON_PRESSED)
  {
    led(uintToRgb(white));
    ESP_LOGI(TAG, "Button pressed");
  }
  else if (state == BUTTON_RELEASED)
  {
    led(uintToRgb(black));
    ESP_LOGI(TAG, "Button released");
  }
  else if (state == BUTTON_CLICKED)
  {
    ESP_LOGI(TAG, "Button clicked");
  }
  else if (state == BUTTON_PRESSED_LONG)
  {
    led(uintToRgb(blue));
    ESP_LOGI(TAG, "Button pressed long");
  }
}

extern "C" void app_main(void)
{

  ESP_LOGI(TAG, "Initializing LED");
  led_init();

  ESP_LOGI(TAG, "Initializing button");
  //
  // Push button connected to GPIO0:
  //
  btn.gpio = (gpio_num_t)0;
  btn.pressed_level = 0;
  btn.internal_pull = true;
  btn.autorepeat    = false;
  btn.callback      = on_button;

  ESP_ERROR_CHECK(button_init(&btn));

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



  // /* Print chip information */
  // esp_chip_info_t chip_info;
  // uint32_t flash_size;
  // esp_chip_info(&chip_info);
  // printf("This is %s chip with %d CPU core(s), %s%s%s%s, ",
  //        CONFIG_IDF_TARGET,
  //        chip_info.cores,
  //        (chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "WiFi/" : "",
  //        (chip_info.features & CHIP_FEATURE_BT) ? "BT" : "",
  //        (chip_info.features & CHIP_FEATURE_BLE) ? "BLE" : "",
  //        (chip_info.features & CHIP_FEATURE_IEEE802154) ? ", 802.15.4 (Zigbee/Thread)" : "");

  // unsigned major_rev = chip_info.revision / 100;
  // unsigned minor_rev = chip_info.revision % 100;
  // printf("silicon revision v%d.%d, ", major_rev, minor_rev);
  // if (esp_flash_get_size(NULL, &flash_size) != ESP_OK)
  // {
  //   printf("Get flash size failed");
  //   return;
  // }

  // printf("%" PRIu32 "MB %s flash\n", flash_size / (uint32_t)(1024 * 1024),
  //        (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

  // printf("Minimum free heap size: %" PRIu32 " bytes\n", esp_get_minimum_free_heap_size());

  // for (int i = 10; i >= 0; i--)
  // {
  //   printf("Restarting in %d seconds...\n", i);
  //   vTaskDelay(1000 / portTICK_PERIOD_MS);
  // }
  // printf("Restarting now.\n");
  // fflush(stdout);
  // // esp_restart();

  while(1){
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
