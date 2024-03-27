/*
 *  Temperature.h
 *  Created on: 2018-8-6
 *  Author: xiaogang
 */

#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_



struct TEMPER_CS_REG_BIT
{
	Uint16 LowLevAct:1;
	Uint16 FanAct:1;
	Uint16 HighLev1Act:1;
	Uint16 HighLev2Act:1;
	Uint16 Alarm:1;
	Uint16 Fault:1;
	Uint16 res6_7:2;
};

union TEMPER_CS_REG
{
	Uint16 all;
	struct TEMPER_CS_REG_BIT bits;
};


struct TEMPERATURE_CH_PAR
{
	int16 ParLowLev;		//µÍÎÂ±¨¾¯
	int16 FanLev;			//¿ª·çÉÈ
	int16 ParHighLev1;		//±¨¾¯
	int16 ParHighLev2;		//¹ÊÕÏ
};


typedef struct
{
	float k0;
	float k1;
	float k2;
	float k3;
	float k4;
//	float k5;
}NTC_K;

typedef struct
{
    float k0;
    float k1;
    float k2;
    float k3;
    float k4;
}NTC_Module;


typedef struct {
	              float  ad;
				  float  sum;
				  int16  sumcnt;
				  int16  temperature;
				  NTC_K *ntck;
		 	 	  void  (*calc)();	                 // Pointer to calculation function
			    }TEMPERATURE_CALC;

typedef struct {
                  float  ad;
			      float  sum;
			      int16  sumcnt;
			      int16  temperature;
			      NTC_Module *ntcmodule;
			      void  (*calc)();                   // Pointer to calculation function
			    }MODULE_TEMP_CALC;


#define NTC_TEMPERATURE_CALC	{0,0,0,0,0,(void (*)(Uint32))NtcTempCalc}
#define MODULE_TEMP_DEFAULTS    {0,0,0,0,0,(void (*)(Uint32))ModuleTempCalc}

typedef struct {
			   	int16 *Data;
			   	union TEMPER_CS_REG TemperCSReg;
			   	struct TEMPERATURE_CH_PAR Par;
			   	void  (*init)();
			   	void  (*run)();		// Pointer to calculation function
			   }TEMPERATURE_OBJ;

#define TEMPERATURE_OBJ_DEFAULTS \
{\
    0,\
	0,\
	{0},\
	(void (*)(Uint32))TemperatureObjInit,\
	(void (*)(Uint32))TemperatureObjProc\
}

extern TEMPERATURE_OBJ Temper_muduleA_obj;
extern TEMPERATURE_OBJ Temper_muduleB_obj;
extern TEMPERATURE_OBJ Temper_muduleC_obj;
extern TEMPERATURE_OBJ Temper_ambient_obj;
extern TEMPERATURE_OBJ Temper_ambient1_obj;
extern TEMPERATURE_OBJ Temper_SCR_obj;

extern TEMPERATURE_CALC  SCR_ntc;
extern TEMPERATURE_CALC  ambient_ntc;
extern TEMPERATURE_CALC  ambient_ntc1;
extern TEMPERATURE_CALC CAP_ntc;
extern MODULE_TEMP_CALC  moduleA_TEMP;
extern MODULE_TEMP_CALC  moduleB_TEMP;
extern MODULE_TEMP_CALC  moduleC_TEMP;


void NtcTempCalc(TEMPERATURE_CALC *v);
void ModuleTempCalc(MODULE_TEMP_CALC *v);
void TemperatureObjInit(TEMPERATURE_OBJ *v);
void TemperatureObjProc(TEMPERATURE_OBJ *v);



#endif /* TEMPERATURER_H_ */
