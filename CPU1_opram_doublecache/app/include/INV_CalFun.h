
/************************************************************************************/
//  INV_CalFun.h
//  Created on: 2018-7-9
//  Author: xiaogang
/***********************************************************************************/



#ifndef INV_CALFUN_H
#define INV_CALFUN_H


typedef struct { float  TargetValue; 	   // Input: Target input
				 float  SetpointValue;	   // Output: Target output
				 float	Step;
		  	  	 void (*calc)();	  	   // Pointer to calculation function
				 } RMPCNTL;


/*-----------------------------------------------------------------------------
Default initalizer for the RMPCNTL object.
-----------------------------------------------------------------------------*/
#define RMPCNTL_DEFAULTS { 0,0,0,(void (*)(Uint32))Rmp_cntl_calc}
/*------------------------------------------------------------------------------
Prototypes for the functions in RMP_CNTL.C
------------------------------------------------------------------------------*/
void Rmp_cntl_calc(RMPCNTL *v);


typedef struct { float x;
                 float y0;
                 float y;
                 float fc;
                 float ts;
                 void  (*calc)();
				 }LOW_PASS_FILTER;

#define LOW_PASS_FILTER_DEFAULTS { 0, \
                          0, \
                          0, \
                          0, \
                          0, \
                         (void (*)(Uint32))low_pass_filter_cal}

void low_pass_filter_cal(LOW_PASS_FILTER *v);

typedef struct { float x;
                 float y;
                 float k;
                 void  (*calc)();
				 }MEAN_PASS_FILTER;

#define MEAN_PASS_FILTER_DEFAULTS { 0, \
                          0, \
                          0.01, \
                         (void (*)(Uint32))mean_pass_filter_cal}

void mean_pass_filter_cal(MEAN_PASS_FILTER *v);


typedef struct
{
	float val;
	float theta;
	float theta_1;
	float filter;
	float rms;
	float sumx2;
	int32 cnt;
	void (*calc)();
} FREQ_SINGLE_PHASE_RMS_CAL;

#define FREQ_SINGLE_PHASE_RMS_CAL_DEFAULTS \
{\
	0,\
	0,\
	0,\
	0.1,\
	0,\
	0,\
	0,\
	(void (*)(Uint32))freq_single_phase_rms_calc\
}

//50hz有效值计算，1ms一个点
typedef struct
{
	float  s;			// Input: 单相输入 (pu)
	float  rms;		    // Output: 有效值输出
	float  filter;  	// 平滑时间
	float  rms_1;		//平滑滤波
	float  sumx2;		//平方和
	Uint32 cnt;
	void  (*calc)();

}SINGAL_PHASE_RMS_CAL;



#define SINGAL_PHASE_RMS_CAL_DEFAULTS \
{\
	0,\
	0,\
	0.1,\
	0,\
	0,\
	0,\
	(void (*)(Uint32))single_phase_rms_calc\
}\
//三相有效值计算，a，b，c
//40ms平方和累加开根号
typedef struct
{
	float  a;			// Input: a
	float  b;			// Input: b
	float  c;			// Input: c
	float  rms;		    // Output: 有效值输出
	float  filter;  	// 平滑时间
	float  rms_1;		//平滑滤波
	void  (*calc)();		// Pointer to calculation function
}THREE_PHASE_RMS_CAL;



#define THREE_PHASE_RMS_CAL_DEFAULTS \
{\
	0,\
	0,\
	0,\
	0,\
	0.1,\
	0,\
	(void (*)(Uint32))three_phase_rms_calc\
}\
//三相有功功率无功功率计算,瞬时值算法
//
typedef struct
{
	float  ua;			           // Input: ua
	float  ub;			           // Input: ub
	float  uc;			           // Input: uc
	float  ia;			           // input: ia
	float  ib;			           // input: ib
	float  ic;			           // input: ic
	float  ReactivePower;		   // Output: 有效值输出
	float  ActivePower;
	float  filter;                 // 平滑时间
	float  reactiveP_1;	           //平滑滤波
	float  activeP_1;
	void  (*calc)();		       // Pointer to calculation function
}INSTANTANEOUS_POWER_CAL;



#define INSTANTANEOUS_POWER_CAL_DEFAULTS \
{\
	0,\
	0, \
	0, \
	0, \
	0, \
	0, \
	0, \
	0, \
	0.1, \
	0, \
	0,\
	(void (*)(Uint32))instantaneous_power_calc\
}\


void single_phase_rms_calc(SINGAL_PHASE_RMS_CAL *v);
void three_phase_rms_calc(THREE_PHASE_RMS_CAL *v);
void instantaneous_power_calc(INSTANTANEOUS_POWER_CAL *v);
void freq_single_phase_rms_calc(FREQ_SINGLE_PHASE_RMS_CAL *v);

typedef struct {
                 Uint16 Period;
                 Uint16 Periodhalf;
                 float MfuncC1;
                 float MfuncC2;
                 float MfuncC3;
                 float MfuncC4;
                 float MfuncC5;
                 float MfuncC6;
                 void (*run)();
               } PWMGEN ;


#define PWMGEN_DEFAULTS     { 12500,\
                              6250,  \
                              0,0,0,\
                              0,0,0,\
                              (void (*)(Uint32))PWM_Update \
                             }

void PWM_Update(PWMGEN *v);


extern void OPEN_PWM(void);

extern void CLOSED_PWM(void);

#endif
