/*
 * @Description:
 * @Author: cy
 * @Date: 2022-10-20 18:33:42
 * @LastEditors: cy
 * @LastEditTime: 2022-10-20 19:02:12
 */
#include "button.h"

#include "FreeRTOS.h"
#include "stm32f1xx_hal_gpio.h"
#include "task.h"

static uint8_t count;

void button_task(void *arg) {
    Button_t *button = (Button_t *)arg;
    while (1) {
        if (HAL_GPIO_ReadPin(button->gpio, button->pin)) {
            button->on_touch();
            if (count == 0) {
                button->on_press();
            } else if (count > 20) {
                button->on_longPress();
                count = 0;
            }
            count++;
        } else {
            if (count > 0) {
                button->on_cancel();
            }
            count = 0;
        }
    }
    vTaskDelay(pdMS_TO_TICKS(10));
}