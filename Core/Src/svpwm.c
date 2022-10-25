/*
 * @Description:
 * @Author: cy
 * @Date: 2022-10-19 12:50:09
 * @LastEditors: cy
 * @LastEditTime: 2022-10-20 15:39:56
 */

#include "svpwm.h"
#include "focMath.h"

Svpwm_t svpwm = {
    _IQ(0),           //阿尔法轴目标电压 	(最大值为母线电压 * sqrt(3) / 3)
    _IQ(0),           //贝塔轴目标电压   	(最大值为母线电压 * sqrt(3) / 3)
    _IQ(0),           //用于扇区判断
    _IQ(0),           //用于扇区判断
    _IQ(0),           //用于扇区判断
    _IQ(0),           // 0矢量作用时长
    _IQ(0),           // 1矢量作用时长
    _IQ(0),           // 2矢量作用时长
    _IQ(0),           // 3矢量作用时长
    _IQ(0),           // 4矢量作用时长
    _IQ(0),           // 5矢量作用时长
    _IQ(0),           // 6矢量作用时长
    _IQ(0),           // 7矢量作用时长
    _IQ(0),           // a相作用时长
    _IQ(0),           // b相作用时长
    _IQ(0),           // c相作用时长
    _IQ(100),         // SVPWM 周期(us)
    _IQ(14.43375673), // SVPWM 系数K =  sqrt(3) * Ts / Udc = 14.433756729740644112728
    _IQ(12),          //母线电压
    0,                //扇区索引
};
/**
 * @description: 根据当前Alpha和βeta值判断扇区并写入参数中
 * @param {Svpwm_t *} svpwm
 * @return null
 */
void select_svpwm_sector(Svpwm_t* svpwm) {

    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t sector;

    //将旋转的坐标系变换到三个轴
    svpwm->u1 = svpwm->uBeta;
    svpwm->u2 = _IQmpy(svpwm->uAlpha, SQRT_3_2) - _IQdiv2(svpwm->uBeta);
    svpwm->u3 = -_IQmpy(svpwm->uAlpha, SQRT_3_2) - _IQdiv2(svpwm->uBeta);

    if (svpwm->u1 > _IQ(0)) {
        a = 1;
    } else {
        a = 0;
    }
    if (svpwm->u2 > _IQ(0)) {
        b = 1;
    } else {
        b = 0;
    }
    if (svpwm->u3 > _IQ(0)) {
        c = 1;
    } else {
        c = 0;
    }

    sector = 4 * c + 2 * b + a;
    switch (sector) {
        case 3:
            svpwm->sector = 1;
            break;
        case 1:
            svpwm->sector = 2;
            break;
        case 5:
            svpwm->sector = 3;
            break;
        case 4:
            svpwm->sector = 4;
            break;
        case 6:
            svpwm->sector = 5;
            break;
        case 2:
            svpwm->sector = 6;
            break;
    }
}
/**
 * @description: 计算扇区时间
 * @param {Svpwm_t*} svpwm
 * @return null
 */
void calculate_vertor_time(Svpwm_t* svpwm) {
    switch (svpwm->sector) {
        case 1:
            svpwm->t4 = _IQmpy(svpwm->K, svpwm->u2);
            svpwm->t6 = _IQmpy(svpwm->K, svpwm->u1);
            svpwm->t0 = svpwm->t7 = _IQdiv2(svpwm->ts - svpwm->t4 - svpwm->t6);
            break;
        case 2:
            svpwm->t2 = -_IQmpy(svpwm->K, svpwm->u2);
            svpwm->t6 = -_IQmpy(svpwm->K, svpwm->u3);
            svpwm->t0 = svpwm->t7 = _IQdiv2(svpwm->ts - svpwm->t2 - svpwm->t6);
            break;
        case 3:
            svpwm->t2 = _IQmpy(svpwm->K, svpwm->u1);
            svpwm->t3 = _IQmpy(svpwm->K, svpwm->u3);
            svpwm->t0 = svpwm->t7 = _IQdiv2(svpwm->ts - svpwm->t2 - svpwm->t3);
            break;
        case 4:
            svpwm->t1 = -_IQmpy(svpwm->K, svpwm->u1);
            svpwm->t3 = -_IQmpy(svpwm->K, svpwm->u2);
            svpwm->t0 = svpwm->t7 = _IQdiv2(svpwm->ts - svpwm->t1 - svpwm->t3);
            break;
        case 5:
            svpwm->t1 = _IQmpy(svpwm->K, svpwm->u3);
            svpwm->t5 = _IQmpy(svpwm->K, svpwm->u2);
            svpwm->t0 = svpwm->t7 = _IQdiv2(svpwm->ts - svpwm->t1 - svpwm->t5);
            break;
        case 6:
            svpwm->t4 = -_IQmpy(svpwm->K, svpwm->u3);
            svpwm->t5 = -_IQmpy(svpwm->K, svpwm->u1);
            svpwm->t0 = svpwm->t7 = _IQdiv2(svpwm->ts - svpwm->t4 - svpwm->t5);
            break;
    }
}
/**
 * @description: 生成svpwm
 * @param {Svpwm_t*} svpwm
 * @return none
 */
void svpwm_generate(Svpwm_t* svpwm) {
    switch (svpwm->sector) {
        case 1:
            svpwm->ta = svpwm->t4 + svpwm->t6 + svpwm->t7;
            svpwm->tb = svpwm->t6 + svpwm->t7;
            svpwm->tc = svpwm->t7;
            break;
        case 2:
            svpwm->ta = svpwm->t6 + svpwm->t7;
            svpwm->tb = svpwm->t2 + svpwm->t6 + svpwm->t7;
            svpwm->tc = svpwm->t7;
            break;
        case 3:
            svpwm->ta = svpwm->t7;
            svpwm->tb = svpwm->t2 + svpwm->t3 + svpwm->t7;
            svpwm->tc = svpwm->t3 + svpwm->t7;
            break;
        case 4:
            svpwm->ta = svpwm->t7;
            svpwm->tb = svpwm->t3 + svpwm->t7;
            svpwm->tc = svpwm->t1 + svpwm->t3 + svpwm->t7;
            break;
        case 5:
            svpwm->ta = svpwm->t5 + svpwm->t7;
            svpwm->tb = svpwm->t7;
            svpwm->tc = svpwm->t1 + svpwm->t5 + svpwm->t7;
            break;
        case 6:
            svpwm->ta = svpwm->t4 + svpwm->t5 + svpwm->t7;
            svpwm->tb = svpwm->t7;
            svpwm->tc = svpwm->t5 + svpwm->t7;
            break;
    }
}