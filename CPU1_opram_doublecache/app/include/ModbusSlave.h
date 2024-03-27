/*
 *  ModusSlave.h
 *  Created on: 2018.7.16
 *  Author: xiaogang
 */
#ifndef MODBUS_SLAVE_H_
#define MODBUS_SLAVE_H_

#include "Driver_Sci.h"


#define MODBUS_MAX_FRAME_LEN 255

#define MODBUS_PAR_DEFAULTS {1,SciBaud9600}

struct MODBUS_COM_STATUS_BIT
{
	int16 ReceFrameOK:1;
	int16 SendFrameOK:1;
	int16 FrameLenErr:1;
	int16 CrcErr:1;
};

union MODBUS_COM_STATUS_REG
{
	struct MODBUS_COM_STATUS_BIT bits;
	Uint16 all;
};


struct MODBUS_PAR
{
	int16 MyAddr;
	enum baud_sci BaudRate;
};

typedef struct
{
	union MODBUS_COM_STATUS_REG *ComStatus;
	struct MODBUS_PAR MonitorPar;
	int16 *ReadDataPtr;
	int16 *WriteDataPtr;
	int16 *ParDataPtr;
	char SendBuf[MODBUS_MAX_FRAME_LEN];		//∑¢ÀÕª∫¥Ê
	char ReceBuf[MODBUS_MAX_FRAME_LEN];		//Ω” ’ª∫¥Ê
	void (*init)();
	void  (*run)();
} MODBUS_COM_SEVER_OBJ;

typedef enum
{

    e_NF_Cmd = 74,
    e_ParaFirst=77,
    e_ParaLast=134,

    e_abnormal_vol = 290,
    e_cms_vol = 401
}ModbusData_Tab;


typedef enum
{
    e_TxIdx_R=0,
    e_RxIdx_R,
    e_RecdIdx_R,
    e_TxData_R,
    e_McwReg_R=10,
    e_MswReg_R,
    e_Status0_R,
    e_Status1_R,
    e_Status2_R,
    e_Fault0_R,
    e_Fault1_R,
    e_Fault2_R,
    e_Fault3_R,
    e_Fault4_R


}ModbusData_Tab2;


typedef enum
{
    e_Year_R=4,
    e_Month_R,
    e_Day_R,
    e_Hour_R,
    e_Minute_R,
    e_Second_R

}ModbusData1_Tab;


extern void ModbusCommOpt(MODBUS_COM_SEVER_OBJ *v);
extern void ModbusCommOptc(MODBUS_COM_SEVER_OBJ *v);
extern void ModbusCommInit(MODBUS_COM_SEVER_OBJ *v);

#define MODBUS_COM_SEVER_DEFAULTS {\
	0,\
	MODBUS_PAR_DEFAULTS,\
	0,0,0,\
	{0},{0},\
	ModbusCommInit,\
	ModbusCommOpt\
}

extern  MODBUS_COM_SEVER_OBJ ModbusComServer;
extern  MODBUS_COM_SEVER_OBJ ModbusComServerc;

#endif
