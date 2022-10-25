/*
 * @Description:
 * @Author: cy
 * @Date: 2022-10-19 20:17:06
 * @LastEditors: cy
 * @LastEditTime: 2022-10-20 15:52:37
 */

#include "focMath.h"

#include "focControl.h"

void get_motor_current(Foc_t* foc) {
    foc->ia = _IQmpy(_IQ19toIQ(_IQ19mpy(GetMotor1ADC1PhaseXValue(1), AD_TO_CURRENT)), _IQ(1.5));
    foc->ib = _IQmpy(_IQ19toIQ(_IQ19mpy(GetMotor1ADC1PhaseXValue(3), AD_TO_CURRENT)), _IQ(1.5));
    foc->ic = _IQmpy(_IQ19toIQ(_IQ19mpy(GetMotor1ADC1PhaseXValue(2), AD_TO_CURRENT)), _IQ(1.5));
}

void ipark_calc(Foc_t* foc) {
    GetMotor1PreCurrent(foc);
    if (foc->iNum < 3) {
        return;
    }
    switch (foc->svpwm.sector) {
        case 1:
            foc->ia =_IQ(0.0f) - foc->ib - foc->ic;
            break;
        case 2:
            foc->ib =_IQ(0.0f) - foc->ia - foc->ic;
            break;
        case 3:
            foc->ib =_IQ(0.0f) - foc->ia - foc->ic;
            break;
        case 4:
            foc->ic =_IQ(0.0f) - foc->ia - foc->ib;
            break;
        case 5:
            foc->ic =_IQ(0.0f) - foc->ia - foc->ib;
            break;
        case 6:
            foc->ia =_IQ(0.0f) - foc->ib - foc->ic;
            break;
        default:
            break;
    }
}

void park_calc(Foc_t* foc){

}
