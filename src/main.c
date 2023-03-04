#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_system.h"

#define LED_BUILTIN 2
#define LED_GREEN   4
#define LED_YELLOW  5
#define LED_RED    18

void taskBlinkRed(void *pvParameter) {
   while (true)
   {
      gpio_set_level(LED_RED, 1);
      vTaskDelay(200 / portTICK_PERIOD_MS);
      gpio_set_level(LED_RED, 0);
      vTaskDelay(200 / portTICK_PERIOD_MS);
   }
}

void taskBlinkYellow(void *pvParameter) {
   while (true)
   {
      gpio_set_level(LED_YELLOW, 1);
      vTaskDelay(500 / portTICK_PERIOD_MS);
      gpio_set_level(LED_YELLOW, 0);
      vTaskDelay(500 / portTICK_PERIOD_MS);
   }
}

void taskBlinkGreen(void *pvParameter) {
   while (true)
   {
      gpio_set_level(LED_GREEN, 1);
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      gpio_set_level(LED_GREEN, 0);
      vTaskDelay(1000 / portTICK_PERIOD_MS);
   }
}

void app_main() {
   gpio_set_direction(LED_BUILTIN, GPIO_MODE_OUTPUT);
   gpio_set_direction(LED_GREEN, GPIO_MODE_OUTPUT);
   gpio_set_direction(LED_YELLOW, GPIO_MODE_OUTPUT);
   gpio_set_direction(LED_RED, GPIO_MODE_OUTPUT);
   xTaskCreatePinnedToCore(taskBlinkRed, "taskBlinkRed", 2048, NULL, 1, NULL, 0);
   xTaskCreatePinnedToCore(taskBlinkYellow, "taskBlinkYellow", 2048, NULL, 1, NULL, 0);
   xTaskCreatePinnedToCore(taskBlinkGreen, "taskBlinkGreen", 2048, NULL, 1, NULL, 0);
   printf("System ready");

   while (true)
   {
      gpio_set_level(LED_BUILTIN, 1);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      gpio_set_level(LED_BUILTIN, 0);
      vTaskDelay(1000 / portTICK_PERIOD_MS);
   }
}