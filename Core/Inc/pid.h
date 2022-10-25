/*
 * @Description: 
 * @Author: cy
 * @Date: 2022-10-20 14:47:19
 * @LastEditors: cy
 * @LastEditTime: 2022-10-20 14:56:42
 */

#ifndef __PID_H
#define __PID_H

#include "main.h"
#include "IQmathLib.h"

typedef struct{
    _iq target;
    _iq kp;
    _iq ki;
    _iq kd;
    _iq out;
    _iq error;
    _iq current;
    _iq pre_error;
    _iq integral;
    _iq max_int;
    _iq min_int;
    _iq max_out;
    _iq min_out;
}Pid_t;

#endif // __PID_H