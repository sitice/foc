/*
 * @Description: 
 * @Author: cy
 * @Date: 2022-10-19 12:50:25
 * @LastEditors: cy
 * @LastEditTime: 2022-10-19 18:46:50
 */


#ifndef __SVPWM_H
#define __SVPWM_H

#include "main.h"
#include "IQmathLib.h"


typedef struct{
    _iq uAlpha; //阿尔法轴目标电压 	(最大值为母线电压 * sqrt(3) / 3)
    _iq uBeta;  //贝塔轴目标电压   	(最大值为母线电压 * sqrt(3) / 3)
    _iq u1;		//用于扇区判断
    _iq u2;		//用于扇区判断
    _iq u3;		//用于扇区判断
    _iq t0;		//0矢量作用时长
    _iq t1;		//1矢量作用时长
    _iq t2;		//2矢量作用时长
    _iq t3;		//3矢量作用时长
    _iq t4;		//4矢量作用时长
    _iq t5;		//5矢量作用时长
    _iq t6;		//6矢量作用时长
    _iq t7;		//7矢量作用时长
    _iq ta;		//a相作用时长
    _iq tb;		//b相作用时长
    _iq tc;		//c相作用时长
    _iq ts;		//SVPWM周期
    _iq K;		//SVPWM 系数K =  sqrt(3) * Ts / Udc
    _iq udc;       //母线电压
    uint8_t sector;//扇区索引
}Svpwm_t;

void select_svpwm_sector(Svpwm_t* svpwm);

void calculate_vertor_time(Svpwm_t* svpwm);

void svpwm_generate(Svpwm_t* svpwm);

#endif // __SVPWM_H