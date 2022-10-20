/*
 * @Description: foc相关的数学计算
 * @Author: cy
 * @Date: 2022-10-19 20:17:17
 * @LastEditors: cy
 * @LastEditTime: 2022-10-20 15:00:10
 */

#ifndef __FOCMATH_H
#define __FOCMATH_H

#include "IQmathLib.h"

#define SQRT_3_3 _IQ(0.577350269)         // 三分之根号三
#define SQRT_3 _IQ(1.732050808)           // 根号三
#define SQRT_3_2 _IQ(0.866025404)         // 二分之根号三
#define AD_TO_CURRENT _IQ19(0.001611328)  // 电流采样比例系数

#define LIMIT_MAX(limit, val) (val) = (val) > (limit) ? (limit) : (val)
#define LIMIT_MIN(limit, val) (val) = (val) < (limit) ? (limit) : (val)

#endif  // __FOCMATH_H