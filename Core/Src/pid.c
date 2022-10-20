/*
 * @Description:
 * @Author: cy
 * @Date: 2022-10-20 14:47:12
 * @LastEditors: cy
 * @LastEditTime: 2022-10-20 15:12:22
 */

#include "pid.h"

#include "IQmathLib.h"
#include "focMath.h"
#include "retarget.h"

void pid_calculate(Pid_t *pid) {
    pid->error = pid->target - pid->current;
    pid->integral += pid->error;
    LIMIT_MAX(pid->max_int, pid->integral);
    LIMIT_MIN(pid->min_int, pid->integral);
    pid->out = _IQmpy(pid->kp, pid->error) + _IQmpy(pid->ki, pid->integral) + _IQmpy(pid->ki, pid->error - pid->pre_error);
    LIMIT_MAX(pid->max_out, pid->out);
    LIMIT_MIN(pid->min_out, pid->out);
}
