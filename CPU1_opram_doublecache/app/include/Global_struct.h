

#include "Inv_Control.h"
#include "Dev_Init.h"
#include "FilterAdData.h"
#include "FaultProtect.h"
#include "State_Machine.h"
#include "ModbusSlave.h"
#include "Temperature.h"

#ifndef GLOBAL_STRUCT_H
#define GLOBAL_STRUCT_H



struct WORD_BITS
{
	Uint16 Bit0:1;
	Uint16 Bit1:1;
	Uint16 Bit2:1;
	Uint16 Bit3:1;
	Uint16 Bit4:1;
	Uint16 Bit5:1;
	Uint16 Bit6:1;
	Uint16 Bit7:1;
	Uint16 Bit8:1;
	Uint16 Bit9:1;
	Uint16 Bit10:1;
	Uint16 Bit11:1;
	Uint16 Bit12:1;
	Uint16 Bit13:1;
	Uint16 Bit14:1;
	Uint16 Bit15:1;

};
union WORD_REG
{
	Uint16 all;
	struct WORD_BITS bits;
};

struct MODUBS_WRITER_AREA
{

	int16 PD0;
   Uint16 PD1;
   Uint16 PD2;
	int16 PD3;
	int16 PD4;
	int16 PD5;
	int16 PD6;
	int16 PD7;
	int16 PD8;
	int16 PD9;
	int16 PD10;
	int16 PD11;
	int16 PD12;
	int16 PD13;
	int16 PD14;
	int16 PD15;
	int16 PD16;
	int16 PD17;
	int16 PD18;
	int16 PD19;
	int16 PD20;
    int16 PD21;
	int16 PD22;
	int16 PD23;
	int16 PD24;
	int16 PD25;
	int16 PD26;
	int16 PD27;
	int16 PD28;
	int16 PD29;
	int16 PD30;
	int16 PD31;
	int16 PD32;
	int16 PD33;
	int16 PD34;
	int16 PD35;
	int16 PD36;
	int16 PD37;
	int16 PD38;
	int16 PD39;
	int16 PD40;
	int16 PD41;
    int16 PD42;
	int16 PD43;
	int16 PD44;
	int16 PD45;
	int16 PD46;
	int16 PD47;
	int16 PD48;
	int16 PD49;
	int16 PD50;
	int16 PD51;
	int16 PD52;
	int16 PD53;
	int16 PD54;
	int16 PD55;
	int16 PD56;
	int16 PD57;


};

struct MODUBS_READ_AREA
{
	Uint16 PD0;
	Uint16 PD1;
	Uint16 PD2;
	Uint16 PD3;
	Uint16 PD4;
	Uint16 PD5;
	int16 PD6;
	int16 PD7;
	int16 PD8;
	int16 PD9;
	int16 PD10;
	Uint16 PD11;
	Uint16 PD12;
	Uint16 PD13;
	Uint16 PD14;
	Uint16 PD15;
	Uint16 PD16;
	Uint16 PD17;
	Uint16 PD18;
	int16 PD19;
	Uint16 PD20;
	int16 PD21;
	int16 PD22;
	int16 PD23;
	int16 PD24;
	int16 PD25;
	Uint16 PD26;
	Uint16 PD27;
	int16 PD28;
};

struct MODUBS_DATA
{
	struct MODUBS_READ_AREA ReadData;
	struct MODUBS_WRITER_AREA WriteData;
};

struct PARA_DATA
{
    Uint16 ProductIdH;                      //1  设备标识
    Uint16 ProductIdL;                      //1  设备标识
    Uint16 SoftVersion;                     //2  软件版本
    Uint16 Year;
    Uint16 Month;
    Uint16 Data;
    Uint16 Hour;
    Uint16 Minute;
    Uint16 Second;
    Uint16 Flash;
    Uint16 Module1_ID;
    Uint16 Module2_ID;
    Uint16 Module3_ID;
    Uint16 Module4_ID;
    Uint16 Module_NUM;
    Uint16 Module_Cur_gain;
    Uint16 Sys_Cur_gain;
    Uint16 Load_Cur_gain;
    Uint16 CMS_NUM;
	struct RATE_VAL Rate_val;			    //4  额定参数
	struct MODBUS_PAR ModbusPar;			//5 modbus rtc 参数
	struct FAULT_PROT_PAR FaultProtect;     //7  故障参数
	struct INV_CONTROL_PAR InvCtr;          //8  控制参数
};

//全局数据结构体
struct RUN_DATA
{
    int16 Adczeroint;
    Uint16 InterruptCount;
    Uint16 STATUS_CPLD0;
    Uint16 STATUS_CPLD1;
    Uint16 STATUS_CPLD2;
    Uint16 ERR_CPLD;
    Uint16 START_AD;
    Uint16 IOtext;
    Uint16 t_gridabnormal;
    Uint16 Compenok;
	union  WORD_REG controlbit;
	union  WORD_REG flagbit;
	struct AD_RESULT Adresult;
	struct EX_AD_RESULT ExAdresult;                                              //1
//	struct CAN_DATA CanData;					   //2
	struct STATE_MACHINE_DATA StateMachine;		   //3
	struct FILTERED_AD_DATA FilteredData;		   //6
	struct GRID_DATA GridData;					   //8
	struct INV_CONTROL_INPUT InvControlInput;	   //9
	struct INV_CONTROL_OUTPUT InvControlOutput;    //10
	int16 ModbusData[510];
	int16 ModbusData1[750];
	Uint16 ModbusData2[100];
	int16 Gridabnormal[5][15];
    int16 index;
    Uint16 Gridabnormalcnt;
};



extern struct RUN_DATA RunData;
extern struct PARA_DATA ParaData;

void Parameter_init(void);
void Comproc(void);
void Paracom(void);

void Paratocpu2(void);
interrupt void adca1_isr(void);

#endif
