/*=====================================================================================
 File name:        filter.C  (IQ version)
                    
 Originator:	Digital Control Systems Group
			Texas Instruments

 Description:  The Voltage Reconstruction based on switching functions and DC-Bus voltage                    

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20
-------------------------------------------------------------------------------------*/
#include "F2837xD_device.h"
#include "Temperature.h"

// ntc 温度输出，用曲线拟合
// 0-100度 对应  电压 0-3v
// AD值缩小100倍，温度值扩大10倍
// 代入 NTC 曲线公式，即可得到温度
#pragma CODE_SECTION(NtcTempCalc,"ramfuncs");

void NtcTempCalc(TEMPERATURE_CALC *v)
{
	//y = k6*x6 + k5*x5 + k4*x4 + k3*x3 + k2*x2 - k1*x + k0
	float x1,x2,x3,x4,x5;
	float temp;

	temp = 0;
	x1 = v->ad;
	x2 = (x1*x1);
	x3 = (x2*x1);
	x4 = (x3*x1);
//	x5 = (x4*x1);
//	temp += (v->ntck->k5)*x5;
	temp += (v->ntck->k4)*x4;
	temp += (v->ntck->k3)*x3;
	temp += (v->ntck->k2)*x2;
	temp += (v->ntck->k1)*x1;
	temp += (v->ntck->k0);
	v->sum += temp;
	v->sumcnt++;
	if(v->sumcnt >= 100)
	{
		v->sum = (v->sum)*0.1;
		v->temperature = (int16)(v->sum);
		v->sum = 0;
		v->sumcnt = 0;
	}
}

#pragma CODE_SECTION(ModuleTempCalc,"ramfuncs");

void ModuleTempCalc(MODULE_TEMP_CALC *v)
{
    //y = k6*x6 + k5*x5 + k4*x4 + k3*x3 + k2*x2 - k1*x + k0
    float x1,x2,x3,x4;
    float temp;

    temp = 0;
    x1 = v->ad;
    x2 = (x1*x1);
    x3 = (x2*x1);
    x4 = (x2*x2);
    temp += (v->ntcmodule->k4)*x4;
    temp += (v->ntcmodule->k3)*x3;
    temp += (v->ntcmodule->k2)*x2;
    temp += (v->ntcmodule->k1)*x1;
    temp += (v->ntcmodule->k0);
    v->sum += temp;
    v->sumcnt++;
    if(v->sumcnt >= 100)
    {
        v->sum = (v->sum)*0.1;
        v->temperature = (int16)(v->sum);
        v->sum = 0;
        v->sumcnt = 0;
    }
}


void TemperatureObjInit(TEMPERATURE_OBJ *v)
{

}
//计算温度，产生温度标志，包括报警，故障等，不做处理，在状态机中处理
void TemperatureObjProc(TEMPERATURE_OBJ *v)
{
	int16 level,temp;

	temp = *v->Data;

	level = v->Par.ParLowLev;
	if(temp < level)
	{
		v->TemperCSReg.bits.LowLevAct = 1;
	}
	else if(temp > (level+30))
	{
		v->TemperCSReg.bits.LowLevAct = 0;
	}

	level = v->Par.FanLev;
	if(temp > level)
	{
		v->TemperCSReg.bits.FanAct = 1;
	}
	else if(temp < (level-60))
	{
		v->TemperCSReg.bits.FanAct = 0;
	}

	level = v->Par.ParHighLev1;
	if(temp > level)
	{
		v->TemperCSReg.bits.HighLev1Act = 1;
	}
	else if(temp < (level-60))
	{
		v->TemperCSReg.bits.HighLev1Act = 0;
	}

	level = v->Par.ParHighLev2;
	if(temp > level)
	{
		v->TemperCSReg.bits.HighLev2Act = 1;
	}
	else if(temp < (level-60))
	{
		v->TemperCSReg.bits.HighLev2Act = 0;
	}

	v->TemperCSReg.bits.Alarm = v->TemperCSReg.bits.HighLev1Act;
	v->TemperCSReg.bits.Fault = v->TemperCSReg.bits.HighLev2Act;
}




