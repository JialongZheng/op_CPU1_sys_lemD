/*
 * FilterAdData.h
 *
 * Created on: 2018-7-9
 * Author: xiaogang
 */

#ifndef FILTERADDATA_H_
#define FILTERADDATA_H_

#include "Dev_Init.h"

//母线电压
#define UDCA            RunData.ExAdresult.Ad1ChA7
#define UDCB            RunData.ExAdresult.Ad3ChA4
#define UDCC            RunData.ExAdresult.Ad3ChA5

//电网电压
#define UGAN            RunData.ExAdresult.Ad1ChA1
#define UGBN            RunData.ExAdresult.Ad1ChA2
#define UGCN            RunData.ExAdresult.Ad1ChA3

//逆变电压
#define ULAN            RunData.ExAdresult.Ad1ChA4
#define ULBN            RunData.ExAdresult.Ad1ChA5
#define ULCN            RunData.ExAdresult.Ad1ChA6

//模块电流
#define IGBT_IA         RunData.ExAdresult.Ad1ChA8
#define IGBT_IB         RunData.ExAdresult.Ad2ChA1
#define IGBT_IC         RunData.ExAdresult.Ad2ChA2

//系统电流
#define SYSTEM_IA       RunData.ExAdresult.Ad2ChA3
#define SYSTEM_IB       RunData.ExAdresult.Ad2ChA4
#define SYSTEM_IC       RunData.ExAdresult.Ad2ChA5

//滤波电容电流
#define CAP_IA          RunData.ExAdresult.Ad3ChA6
#define CAP_IB          RunData.ExAdresult.Ad3ChA7
#define CAP_IC          RunData.ExAdresult.Ad3ChA8



//温度

#define SCR_HEATSINK_TEMP    RunData.Adresult.AdChB5;         //   1
#define AMBIENT_TEMP         RunData.Adresult.AdChB6;         //  2


#define AMBIENT_TEMP1         RunData.Adresult.AdChA0;    //     ETH1  14
//#define AMBIENT_TEMP1         RunData.Adresult.AdChB0;    //     ETH1  15


/*#define SCR_HEATSINK_TEMP    RunData.Adresult.AdChB5;         //   1
#define REACTOR_TEMP         RunData.Adresult.AdChB6;         //  2


#define AMBIENT_TEMP         RunData.Adresult.AdChA0;    //     ETH1  14
#define AMBIENT_TEMP1         RunData.Adresult.AdChB0; */   //     ETH1  15


struct FILTERED_AD_DATA
{
	float LoadUa0;
	float LoadUb0;
	float LoadUc0;
	float LoadUa1;
	float LoadUb1;
	float LoadUc1;
	float GridUa0;
	float GridUb0;
	float GridUc0;
	float GridUa1;
	float GridUb1;
	float GridUc1;
	float IgbtIa0;
	float IgbtIb0;
	float IgbtIc0;
	float IgbtIa1;
	float IgbtIb1;
	float IgbtIc1;
	float SysIa0;     //A相系统电流采样值
	float SysIb0;     //B相系统电流采样值
	float SysIc0;     //C相系统电流采样值
	float SysIa1;     //A相系统电流滤波值
	float SysIb1;     //B相系统电流滤波值
	float SysIc1;     //C相系统电流滤波值
	float Udc;
	float Ucap;
	float CapIa0;
	float CapIb0;
	float CapIc0;
	float CapIa1;
	float CapIb1;
	float CapIc1;
	float moduleA_temper;
	float moduleB_temper;
	float moduleC_temper;
	float ambient_temper;
	float Scr_temper;

};

struct GRID_DATA
{
	float Udca_vol;
	float Udcb_vol;
	float Udcc_vol;
	float Ucapa_vol;
	float Ucapb_vol;
	float Ucapc_vol;
	float Ucapma_vol;
	float Ucapmb_vol;
	float Ucapmc_vol;
	float Ucapa_s;
	float Ucapb_s;
	float Ucapc_s;
	float Udca_cur;
	float Udcb_cur;
	float Udcc_cur;
	float LoadUaRms;
	float LoadUbRms;
	float LoadUcRms;
	float GridUaRms;
	float GridUbRms;
	float GridUcRms;
	float GridUa1Rms;
	float GridUb1Rms;
	float GridUc1Rms;
	float GridIaRms;
	float GridIbRms;
	float GridIcRms;
	float SysIaRms;
	float SysIbRms;
	float SysIcRms;
	float CapIaRms;
	float CapIbRms;
	float CapIcRms;
	float ActivePower;
	float ReactivePower;
	float PowerFactor;
	float FrequencyA;
	float FrequencyB;
	float FrequencyC;

};

extern struct EX_ADC_GAIN ExAdcGain;
extern struct EX_ADC_CH_ZERO ExAdcChZero;

extern EX_ADC_OBJ ExAdcObj;

extern struct ADC_GAIN AdcGain;
extern struct ADC_CH_ZERO AdcChZero;

extern ADC_OBJ AdcObj ;

extern void CaltGridInit(void);
extern void CaltGrid(void);


extern void FilterAdinit(void);
extern void FilterAdData(void);

#endif /* FILTERADDATA_H_ */
