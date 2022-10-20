/*
 * @Description: 
 * @Author: cy
 * @Date: 2022-10-20 14:45:46
 * @LastEditors: cy
 * @LastEditTime: 2022-10-20 14:46:06
 */


#ifndef __FOCCONTROL_H
#define __FOCCONTROL_H

#include "main.h"
#include "IQmathLib.h"

// FOC结构体创建
typedef struct
{
    uint8_t isEnable; //电机使能标志
    _iq polePairs;    //极对数

    _iq tariq;        //目标q电流
    _iq tarid;        //目标i电流
    _iq19 mAngle_Offect;//偏移角度
	_iq19 mAngle;       //机械角度
    _iq19 eAngle;       //电角度
    _iq eRadian;      //电角度弧度
    _iq eAngleSine;   //电角度正弦值（非弧度）
    _iq eAngleCosine; //电角度余弦值（非弧度）

    uint8_t iNum;     //a 电流采样个数
    _iq ia;           //a 相实际电流
    _iq ib;           //b 相实际电流
	_iq ic;           //c 相实际电流

    _iq I_Alpha;      //clarke变换后 * 2/3后 I_Alpha
    _iq I_Beta;       //clarke变换后 * 2/3后 I_Beta

    _iq I_Alpha_Svpwm;//park反变换后 I_Alpha_Svpwm
    _iq I_Beta_Svpwm; //park反变换后 I_Beta_Svpwm
    
    _iq Iq;           //park变换后 Iq
    _iq Id;           //park变换后 Id
    
    _iq19 tarSpeed;     //目标转速 机械角度
    _iq19 preSpeed;     //当前转速 机械角度
		_iq19 tarPos;       //目标位置 机械角度
		_iq19 prePos;       //当前位置 机械角度
    struct PI_Struct idPID;    //id pid
    struct PI_Struct iqPID;    //iq pid
    struct PID_Struct sPID;    //speed pid
	struct PID_Struct pPID;    //position pid
 
}FOC_Struct;

#endif // __FOCCONTROL_H