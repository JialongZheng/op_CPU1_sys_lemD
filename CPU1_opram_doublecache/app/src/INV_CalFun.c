
/*
 *  INV_CalFun.c
 *  Created on: 2018-7-7
 *  Author: xiaogang
 */


#include "math.h"

#include "F2837xD_device.h"
#include "INV_CalFun.h"
//#include "Global_Defines.h"
#include "Const_Defines.h"


#pragma CODE_SECTION(Rmp_cntl_calc,"ramfuncs");

void Rmp_cntl_calc(RMPCNTL *v)
{
	if (v->TargetValue >= v->SetpointValue)
	{
		v->SetpointValue += v->Step;        // 0.0000305 is resolution of Q15
		if (v->SetpointValue > v->TargetValue)
		{
		  v->SetpointValue = v->TargetValue;
		}
	}
	else
	{
		v->SetpointValue -= v->Step;        // 0.0000305 is resolution of Q15
		if (v->SetpointValue < v->TargetValue)
		{
		  v->SetpointValue = v->TargetValue;
		}
	}
}



#pragma CODE_SECTION(low_pass_filter_cal,"ramfuncs");

void low_pass_filter_cal(LOW_PASS_FILTER *v)
{
	v->y = (v->y0 + 2.0*PI*v->ts*v->fc*v->x)/(1 + 2.0*PI*v->ts*v->fc);

	v->y0 = v->y;
}

#pragma CODE_SECTION(mean_pass_filter_cal,"ramfuncs");
void mean_pass_filter_cal(MEAN_PASS_FILTER *v)
{
	v->y = (v->x)*(v->k)+(v->y)*(1-(v->k));
}

#pragma CODE_SECTION(single_phase_rms_calc,"ramfuncs");

void single_phase_rms_calc(SINGAL_PHASE_RMS_CAL *v)
{
	float temp;
	v->sumx2 += v->s*v->s;
	v->cnt++;
	if((v->cnt) >= SAMPLE_POINT)
	{
		temp = v->sumx2*SAMPLE_POINT_1;
		temp = sqrt(temp);
		v->cnt = 0;
		v->sumx2 = 0;
		temp = temp*v->filter;
		temp += v->rms_1*(1.0 - v->filter);
		v->rms = temp;
		v->rms_1 = v->rms;
	}

}

#pragma CODE_SECTION(freq_single_phase_rms_calc,"ramfuncs");

void freq_single_phase_rms_calc(FREQ_SINGLE_PHASE_RMS_CAL *v)
{
	float temp;

	if(fabs(v->theta - v->theta_1) > 0.5)
	{
		v->sumx2 += v->val*v->val;
		v->cnt++;
		temp = v->sumx2 / v->cnt;
		temp = sqrt(temp);
		v->sumx2 = 0;
		v->cnt = 0;
		temp = temp*v->filter;
		temp += v->rms*(1.0-v->filter);
		v->rms = temp;
	}
	else
	{
		v->sumx2 += v->val*v->val;
		v->cnt++;
		if(v->cnt >= 100)	//10HZ及以下不计算有效值
		{
			v->sumx2 = 0;
			v->cnt = 0;
			v->rms = 0;
		}
	}
	v->theta_1 = v->theta;
}

#pragma CODE_SECTION(three_phase_rms_calc,"ramfuncs");

void three_phase_rms_calc(THREE_PHASE_RMS_CAL *v)
{
	float temp;
	temp = v->a*v->a + v->b*v->b + v->c*v->c;
	temp = sqrt(temp);
	temp = temp*0.5774;
	v->rms = temp;
	v->rms = temp*v->filter + v->rms_1*(1.0-v->filter);
	v->rms_1 = v->rms;
}

#pragma CODE_SECTION(instantaneous_power_calc,"ramfuncs");

void instantaneous_power_calc(INSTANTANEOUS_POWER_CAL *v)
{
	float temp;
	temp = (v->ua-v->ub)*v->ic + (v->ub-v->uc)*v->ia + (v->uc-v->ua)*v->ib;
	temp = temp*0.57735;
	v->ReactivePower = temp*v->filter + v->reactiveP_1*(1.0-v->filter);
	v->reactiveP_1 = v->ReactivePower;
	v->ReactivePower = temp;

	temp = v->ua*v->ia + v->ub*v->ib + v->uc*v->ic;
	v->ActivePower = temp*v->filter + v->activeP_1*(1.0- v->filter);
	v->activeP_1 = v->ActivePower;
	v->ActivePower = temp;

}



void OPEN_PWM(void)
{
    GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;
}


void CLOSED_PWM(void)
{
    GpioDataRegs.GPASET.bit.GPIO0 = 1;
}







