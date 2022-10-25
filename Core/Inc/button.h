/*
 * @Description:
 * @Author: cy
 * @Date: 2022-10-20 18:33:52
 * @LastEditors: cy
 * @LastEditTime: 2022-10-20 19:01:34
 */

#ifndef __BUTTON_H
#define __BUTTON_H

#include "main.h"
#include "stm32f103x6.h"

typedef struct {
    void (*on_touch)();
    void (*on_press)();
    void (*on_click)();
    void (*on_longPress)();
    void (*on_cancel)();
    uint16_t pin;
    GPIO_TypeDef* gpio;
} Button_t;

#endif  // __BUTTON_H