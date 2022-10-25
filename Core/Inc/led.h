/*
 * @Description: 
 * @Author: cy
 * @Date: 2022-10-20 18:36:27
 * @LastEditors: cy
 * @LastEditTime: 2022-10-20 18:39:47
 */

#include "main.h"
#include "stm32f1xx_hal_gpio.h"

#define LED_ON() HAL_GPIO_WritePin(GPIOB, uint16_t GPIO_PIN_11, GPIO_PIN_RESET)

#define LED_OFF() HAL_GPIO_WritePin(GPIOB, uint16_t GPIO_PIN_11, GPIO_PIN_SET)