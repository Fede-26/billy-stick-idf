/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_log.h"
#include "lcd_utils.hpp"

const char *TAG = "main";

static LGFX_LiLyGo_TDongleS3 lcd;

extern "C" void app_main(void)
{
  printf("Hello world!\n");

  //
  // Display, ST7735s on SPI bus
  //
  if (!lcd.init())
  {
    ESP_LOGW(TAG, "lcd.init() failed");
    return;
  }

  lcd.setBrightness(128);

  lcd.clear(0xff0000u);
  lcd.setColor(0xffffffu);
  lcd.drawRect(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);
  lcd.setCursor(2, 2);
  lcd.setTextColor(0xffffffu, 0xff0000u);
  lcd.println("Loaded LovyanGFX");
  lcd.setCursor(10, 10);
  lcd.setTextColor(0x00ff00u, 0xff0000u);
  lcd.println("Green");

  /* Print chip information */
  esp_chip_info_t chip_info;
  uint32_t flash_size;
  esp_chip_info(&chip_info);
  printf("This is %s chip with %d CPU core(s), %s%s%s%s, ",
         CONFIG_IDF_TARGET,
         chip_info.cores,
         (chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "WiFi/" : "",
         (chip_info.features & CHIP_FEATURE_BT) ? "BT" : "",
         (chip_info.features & CHIP_FEATURE_BLE) ? "BLE" : "",
         (chip_info.features & CHIP_FEATURE_IEEE802154) ? ", 802.15.4 (Zigbee/Thread)" : "");

  unsigned major_rev = chip_info.revision / 100;
  unsigned minor_rev = chip_info.revision % 100;
  printf("silicon revision v%d.%d, ", major_rev, minor_rev);
  if (esp_flash_get_size(NULL, &flash_size) != ESP_OK)
  {
    printf("Get flash size failed");
    return;
  }

  printf("%" PRIu32 "MB %s flash\n", flash_size / (uint32_t)(1024 * 1024),
         (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

  printf("Minimum free heap size: %" PRIu32 " bytes\n", esp_get_minimum_free_heap_size());

  for (int i = 10; i >= 0; i--)
  {
    printf("Restarting in %d seconds...\n", i);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  printf("Restarting now.\n");
  fflush(stdout);
  // esp_restart();
}
