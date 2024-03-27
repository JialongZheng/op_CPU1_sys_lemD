/*
 *
 *  Dev_Init.h
 *  Created on: 2018-7-9
 *  Author: xiaogang
 */

#ifndef DEV_INIT_H
#define DEV_INIT_H

#include "F28x_Project.h"



extern void ADC_config(void);
extern void ConfigureADC(void);

extern void SetupADCEpwm(Uint16 channel);

struct ADC_GAIN
{
	float AdChA0Gain;
	float AdChB0Gain;
	float AdChA1Gain;
	float AdChB1Gain;
	float AdChA2Gain;
	float AdChB2Gain;
	float AdChA3Gain;
	float AdChB3Gain;
	float AdChA4Gain;
	float AdChB4Gain;
	float AdChA5Gain;
	float AdChB5Gain;
	float AdChA6Gain;
	float AdChB6Gain;
	float AdChA7Gain;
	float AdChB7Gain;
};

struct EX_ADC_GAIN
{
	float Ad1A1Gain;
	float Ad1A2Gain;
	float Ad1A3Gain;
	float Ad1A4Gain;
	float Ad1A5Gain;
	float Ad1A6Gain;
	float Ad1A7Gain;
	float Ad1A8Gain;
	float Ad2A1Gain;
	float Ad2A2Gain;
	float Ad2A3Gain;
	float Ad2A4Gain;
	float Ad2A5Gain;
	float Ad2A6Gain;
	float Ad2A7Gain;
	float Ad2A8Gain;
    float Ad3A1Gain;
    float Ad3A2Gain;
    float Ad3A3Gain;
    float Ad3A4Gain;
    float Ad3A5Gain;
    float Ad3A6Gain;
    float Ad3A7Gain;
    float Ad3A8Gain;
};


struct EX_ADC_CH_ZERO
{
	float Ad1A1ZERO;
	float Ad1A2ZERO;
	float Ad1A3ZERO;
	float Ad1A4ZERO;
	float Ad1A5ZERO;
	float Ad1A6ZERO;
	float Ad1A7ZERO;
	float Ad1A8ZERO;
	float Ad2A1ZERO;
	float Ad2A2ZERO;
	float Ad2A3ZERO;
	float Ad2A4ZERO;
	float Ad2A5ZERO;
	float Ad2A6ZERO;
	float Ad2A7ZERO;
	float Ad2A8ZERO;
	float Ad3A1ZERO;
	float Ad3A2ZERO;
	float Ad3A3ZERO;
	float Ad3A4ZERO;
	float Ad3A5ZERO;
	float Ad3A6ZERO;
	float Ad3A7ZERO;
	float Ad3A8ZERO;
};

struct ADC_CH_ZERO
{
	Uint32 A0ZERO;
	Uint32 B0ZERO;
	Uint32 A1ZERO;
	Uint32 B1ZERO;
	Uint32 A2ZERO;
	Uint32 B2ZERO;
	Uint32 A3ZERO;
	Uint32 B3ZERO;
	Uint32 A4ZERO;
	Uint32 B4ZERO;
	Uint32 A5ZERO;
	Uint32 B5ZERO;
	Uint32 A6ZERO;
	Uint32 B6ZERO;
	Uint32 A7ZERO;
	Uint32 B7ZERO;
};
//ad ×ª»»½á¹û
struct AD_RESULT
{
	float AdChA0;
	float AdChB0;
	float AdChA1;
	float AdChB1;
	float AdChA2;
	float AdChB2;
	float AdChA3;
	float AdChB3;
	float AdChA4;
	float AdChB4;
	float AdChA5;
	float AdChB5;
	float AdChA6;
	float AdChB6;
	float AdChA7;
	float AdChB7;
};

struct EX_AD_RESULT
{
	float Ad1ChA1;
	float Ad1ChA2;
	float Ad1ChA3;
	float Ad1ChA4;
	float Ad1ChA5;
	float Ad1ChA6;
	float Ad1ChA7;
	float Ad1ChA8;
	float Ad2ChA1;
	float Ad2ChA2;
	float Ad2ChA3;
	float Ad2ChA4;
	float Ad2ChA5;
	float Ad2ChA6;
	float Ad2ChA7;
	float Ad2ChA8;
    float Ad3ChA1;
    float Ad3ChA2;
    float Ad3ChA3;
    float Ad3ChA4;
    float Ad3ChA5;
    float Ad3ChA6;
    float Ad3ChA7;
    float Ad3ChA8;
};

typedef struct{
	struct AD_RESULT *adresult;
	struct ADC_GAIN *adc_gain;
	struct ADC_CH_ZERO *adChZero;
	void (*run)();
}ADC_OBJ;

typedef struct{
	struct EX_AD_RESULT *ex_adresult;
	struct EX_ADC_GAIN *ex_adc_gain;
	struct EX_ADC_CH_ZERO *ex_adChZero;
	void (*run)();
}EX_ADC_OBJ;


#define ADC_OBJ_DEFAULTS {0,0,0,\
	(void (*)(Uint32))GetAdResult}

void GetAdResult(ADC_OBJ *v);

void AdcZeroCal(struct ADC_CH_ZERO *v);

#define AdChZeroDefaults {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
#define ADC_GAINDEFAULTS {1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f}

#define EX_ADC_OBJ_DEFAULTS {0,0,0,\
	(void (*)(Uint32))GetExAdResult}

void GetExAdResult(EX_ADC_OBJ *v);

void ExAdcZeroCal(struct EX_ADC_CH_ZERO *v);

#define ExAdChZeroDefaults {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
#define EX_ADC_GAINDEFAULTS {1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f}




#endif  // end of INV_DEVINIT_H definition


//===========================================================================
