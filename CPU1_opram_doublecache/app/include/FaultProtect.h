/*
 *  Faultprotect.h
 *  Created on: 2018-7-9
 *  Author: xiaogang
 */

#ifndef FAULT_PROTECT_H_
#define FAULT_PROTECT_H_

#include "State_Machine.h"


struct RATE_VAL
{
	Uint16 GridUrms;
	Uint16 GridFreq;
	Uint16 Ubattery;
	Uint16 Power;
};


struct FAULT_PROT_PAR
{
	Uint16 OverIgbtIPeak;
	Uint16 OverUdcPeak;
	Uint16 OverIdc;
	Uint16 UnderUdc;
	Uint16 EmergencyFaultDly;
	Uint16 FuseFaultDly;
	Uint16 OverIdcDly;
	Uint16 IgbtFaultDly;
	Uint16 UdcFaultDly;
	Uint16 OverIIgbtDly;
	Uint16 OverUdcDly;
	Uint16 UnderUdcDly;
	Uint16 UnderUrmsDly;
	Uint16 UnderURms;
	Uint16 OverURms;
	Uint16 OverIRms;
	Uint16 OverSysIRms;
	Uint16 OverIcapRms;
	Uint16 OverURmsDly;
	Uint16 OverSysIRmsDly;
	Uint16 OverIcapRmsDly;
	Uint16 OverIRmsDly;
	Uint16 OverFreqAC;
	Uint16 UnderFreqAC;
	Uint16 FreqFaultDly;
	Uint16 TempFaultDly;
	Uint16 Module_Ipeak;
	Uint16 Module_Ipeak_Dly;
	Uint16 Module_Irms;
	Uint16 Module_Irms_Dly;
};



struct FLAG_REG_BIT
{
	Uint16 Status:1;	//����/���ڱ������
	Uint16 Reset:1;		//��λ����
	Uint16 NeedInit:1;
	Uint16 TonEn:1;		//IO��ʱ��λ����
	Uint16 TOut:1;		//IO��ʱ�����
};

union FLAG_REG
{
	Uint16 All;
	struct FLAG_REG_BIT bits;
};

typedef struct
{
	float  input;		    // Input: ������
	float  GreatValue; 		// Input: ����ֵ����ֵ
	Uint16 ActDealy;		// Input: ������ʱ
	Uint16 cnt;			    // INput: ��ʱ����������cnt=ActDealyʱ����
	union FLAG_REG flag;	// outpu: ������
	void  (*calc)();		// Pointer to calculation function
} OVER_PROTECT;


#define OVER_PROTECT_DEFAULTS { 0, \
                          0, \
                          0, \
                          0, \
                          0, \
              			  (void (*)(Uint32))over_protect_calc }


typedef struct
{
	float  input;		    // Input: ������
	float  UnderValue; 		// Input: ����ֵ,����ֵ
	Uint16  ActDealy;		// Input: ������ʱ
	Uint16 cnt;			    // INput: ��ʱ����������cnt=ActDealyʱ����
	union FLAG_REG flag;	// outpu: ������
	void  (*calc)();		// Pointer to calculation function
} UNDER_PROTECT;

#define UNDER_PROTECT_DEFAULTS { 0, \
                          		 0, \
                          		 0, \
                          		 1, \
                          		 0, \
                          		 (void (*)(Uint32))under_protect_calc }


typedef struct
{
	float input1;			//������1
	float input2;			//������2
	float input3;			//������3
	float UnbalanceVal;	    //��ƽ���
	Uint16 ActDelay;	    //��ʱ
	Uint16 cnt;
	union FLAG_REG flag;
	void (*calc)();
} UNBALANCE_PROTECT;

#define UNBALANCE_PROTECT_DEFAULTS {0,\
									0,\
									0,\
									0,\
									0,\
									0,\
									0,\
									(void (*)(Uint32))unbalance_protect_calc\
									}

typedef struct
{
	Uint16 ActDelay;
	Uint16 cnt;			    // input: ��ʱ����������cnt=ActDealyʱ����
	union FLAG_REG flag;	// outpu: ������
	void  (*calc)();		// Pointer to calculation function
} TIMER_DLEAY;


#define TIMER_DLEAY_DEFAULTS {0, \
                              0, \
                              0, \
              			      (void (*)(Uint32))timer_delay_protect_calc }


extern void over_protect_calc(OVER_PROTECT *v);

extern void under_protect_calc(UNDER_PROTECT *v);

extern void unbalance_protect_calc(UNBALANCE_PROTECT *v);

extern void timer_delay_protect_calc(TIMER_DLEAY *v);

extern void FastFaultProtProc(void);
extern void FaultProtInit(void);
extern void RmsProtect(void);

#endif
