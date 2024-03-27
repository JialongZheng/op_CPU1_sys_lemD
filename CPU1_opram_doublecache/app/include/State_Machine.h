//###########################################################################
//
// FILE:   State_Machine.h
//
// TITLE:  DSP2833x Device Definitions.
//
//###########################################################################
// $TI Release:
// $Release Date: July  8, 2018 $
// $Copyright:
//
//###########################################################################

#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H
#include "F2837xD_Device.h"
#include "F2837xD_Examples.h"
//#include "Global_Defines.h"
// #define BYPASS 0//1-无进出线，旁路


struct MCW_BITS
{
    Uint16 Charge:1;         // 0 启动
    Uint16 Reset:1;          // 1 复位
    Uint16 AutoManual:1;     // 2  自动/手动 录波
    Uint16 Stop:1;           // 3
    Uint16 EnableA:1;        // 4
    Uint16 EnableB:1;        // 5
    Uint16 EnableC:1;        // 6
    Uint16 Enableseq :1;     // 7   相序使能
    Uint16 Charge_Mode :1;   // 8   充电模式0恒流 1恒压
    Uint16 BypassMcboff :1;  // 9
    Uint16 InvRun:1;         // 10  运行
    Uint16 EnterTestMode:1;  // 11  同步测试
    Uint16 Calibartion:1;    // 12    较0
    Uint16 IOtext:1;         // 13    继电器测试
    Uint16 ParamEn:1;        // 14     参数使能
    Uint16 Param:1;          // 15     参数默认

};

union MCW_REG
{
    Uint16 all;
    struct MCW_BITS bits;
};

struct MSW_BITS
{
    Uint16 Running:1;           //0
    Uint16 Fault:1;             //1
    Uint16 Wave_RdOn:1;             //2
    Uint16 RdyRun:1;            //3
    Uint16 Charging:1;          //4 软起状态
    Uint16 GridCompen:1;        //5 低落状态
    Uint16 reset:1;             //6 复位状态
    Uint16 TestMode:1;          //7 测试状态
    Uint16 ParamEn:1;           //8
    Uint16 Calibartion:1;       //9
    Uint16 Togglebit:1;         //10 心跳位
    Uint16 Compenflag_flash:1;  //11
    Uint16 GridCompenpre:1;     //12 扰动
    Uint16 Gridabnomal:1;       //13 电网异常
    Uint16 Start:1;             //14 启动
    Uint16 FltTrip:1;           //15
};

union MSW_REG
{
    Uint16 all;
    struct MSW_BITS bits;
};

struct STATUS_BITS0
{
    Uint16 RunStatus   :1;   //0
    Uint16 FaultStatus :1;   //1
    Uint16 CompenStatus:1;   //2     补偿状态
    Uint16 InvStatusA  :1;   //3  A相逆变器状态
    Uint16 ComStatus1  :1;   //4  模块1通讯状态
    Uint16 ComStatus2  :1;   //5  模块2通讯状态
    Uint16 ChgStatusA  :1;   //6  A相充电状态
    Uint16 ComStatus3  :1;   //7  模块3通讯状态
    Uint16 ComStatus4  :1;   //8  模块4通讯状态
    Uint16 ScrStatusA  :1;   //9  A相SCR状态
    Uint16 ScrStatusB  :1;   //10 B相SCR状态
    Uint16 ScrStatusC  :1;   //11 C相SCR状态
    Uint16 InputSwitch :1;   //12 进线开关状态
    Uint16 OutputSwitch:1;   //13 出线开关状态
    Uint16 BypassMcb   :1;   //14 旁路开关状态
    Uint16 MainContact :1;   //15 主接触器状态
};

union STATUS_REG0
{
    Uint16 all;
    struct STATUS_BITS0 bits;
};


struct STATUS_BITS1
{
    Uint16 SoftContact    :1;   //16  软启接触器状态
    Uint16 TRSoftCon      :1;   //17
    Uint16 FilteCapCon    :1;   //18
    Uint16 res            :1;   //19
    Uint16 BreakerDC      :1;   //20
    Uint16 Module3BreakDC :1;   //21 B相直流断路器状态
    Uint16 Module4BreakDC  :1;   //22 C相直流断路器状态
    Uint16 SectionSwitch  :1;   //23   旋钮开关状态
    Uint16 EmergentStop   :1;   //24
    Uint16 ScrFanContact  :1;   //25
    Uint16 Module1BreakAC :1;   //26
    Uint16 Module2BreakAC :1;   //27
    Uint16 Module3BreakAC :1;   //28
    Uint16 Module4BreakAC :1;
    Uint16 Module1BreakDC :1;
    Uint16 Module2BreakDC :1;
};

union STATUS_REG1
{
    Uint16 all;
    struct STATUS_BITS1 bits;
};

struct STATUS_BITS2
{
    Uint16 SelfCheck     :1;
    Uint16 GridAbnormal  :1;
    Uint16 MessageSend   :1;
    Uint16 GridAbtype    :1;
    Uint16 Running       :1;
    Uint16 GridLvrt      :1;
    Uint16 GridHvrt      :1;
    Uint16 Bypass        :1;
    Uint16 Quit          :1;
    Uint16 Protectok     :1;
    Uint16 NoProtect     :1;

};

union STATUS_REG2
{
    Uint16 all;
    struct STATUS_BITS2 bits;
};

struct FAULT_CODE0_BITS
{
    Uint16 PhaSequFault     :1;   //0   系统电压相序故障
    Uint16 OverSysIA        :1;   //1   系统A相过流
    Uint16 OverSysIB        :1;   //2   系统B相过流
    Uint16 OverSysIC        :1;   //3   系统C相过流
    Uint16 OverOutIA        :1;   //4   逆变器A相过流
    Uint16 OverOutIB        :1;   //5        逆变器B相过流
    Uint16 OverOutIC        :1;   //6        逆变器C相过流
    Uint16 OverUdca         :1;   //7       直流母线A相过压
    Uint16 OverModule1Iarms :1;   //8       直流母线B相过压
    Uint16 OverModule1Ibrms :1;   //9       直流母线C相过压
    Uint16 UnderUdca        :1;   //10    直流母线A相欠压
    Uint16 OverModule1Icrms :1;   //11    直流母线B相欠压
    Uint16 OverModule2Iarms :1;   //12    直流母线C相欠压
    Uint16 OverAMoudle1Ipeak:1;   //13  模块A电流峰值过流
    Uint16 OverBMoudle1Ipeak:1;   //14  模块B电流峰值过流
    Uint16 OverCMoudle1Ipeak:1;   //15  模块C电流峰值过流
};

union FAULT_CODE0_REG
{
    Uint16 all;
    struct FAULT_CODE0_BITS bits;
};


struct FAULT_CODE1_BITS
{
    Uint16 OversysIapeak   :1;   //16 A相系统电流峰值过流
    Uint16 OversysIbpeak   :1;   //17 B相系统电流峰值过流
    Uint16 OversysIcpeak   :1;   //18 C相系统电流峰值过流
    Uint16 M1_DCBrkFUFlt   :1;   //19 A相直流熔丝故障
    Uint16 M2_DCBrkFUFlt   :1;   //20 B相直流熔丝故障
    Uint16 SB1overtime     :1;   //21 C相直流熔丝故障
    Uint16 M3_DCBrkFUFlt   :1;   //22 A相交流熔丝故障
    Uint16 M4_DCBrkFUFlt   :1;   //23 B相交流熔丝故障
    Uint16 ALL_ACBrkFUFlt  :1;   //24 C相交流熔丝故障
    Uint16 InputSwitchFlt  :1;   //25 进线开关故障
    Uint16 BypassSwitchFlt :1;   //26 旁路开关故障
    Uint16 OutputSwitchFlt :1;   //27 出线开关故障
    Uint16 OvercapIa       :1;   //28 A相滤波电容过流
    Uint16 OvercapIb       :1;   //29 B相滤波电容过流
    Uint16 OvercapIc       :1;   //30 C相滤波电容过流
    Uint16 SoftContFault   :1;   //31   交流软起故障

};

union FAULT_CODE1_REG
{
    Uint16 all;
    struct FAULT_CODE1_BITS bits;
};

struct FAULT_CODE2_BITS
{
    Uint16 MainContFault  :1;   //32  主接触器故障
    Uint16 SCRFanConFlt   :1;   //33  充电接触器故障
    Uint16 TRSoftConFlt   :1;   //34
    Uint16 FilterCapConFlt:1;   //35
    Uint16 BreakerDcFlt   :1;   //36 直流断路器故障
    Uint16 DISBrkDcFlt    :1;   //37 放电微断故障
    Uint16 ALL_ModuleFlt  :1;   //38 子模块全部故障
    Uint16 OverInvUA      :1;   //39 A相逆变器过压故障
    Uint16 OverInvUB      :1;   //40 B相逆变器过压故障
    Uint16 OverInvUC      :1;   //41 C相逆变器过压故障
    Uint16 OverUdcA_HW    :1;   //42 A相直流硬件过压故障
    Uint16 OverUdcB_HW    :1;   //43 B相直流硬件过压故障
    Uint16 OverUdcC_HW    :1;   //44 C相直流硬件过压故障
    Uint16 OverAMoudle2Ipeak  :1;   //45 A相直流过流故障
    Uint16 OverBMoudle2Ipeak  :1;   //46 B相直流过流故障
    Uint16 OverCMoudle2Ipeak  :1;   //47 C相直流过流故障

};


union FAULT_CODE2_REG
{
    Uint16 all;
    struct FAULT_CODE2_BITS bits;
};

struct FAULT_CODE3_BITS
{
    Uint16 OverSpcUA        :1;    //48 A相超级电容过压故障
    Uint16 OverModule2Ibrms :1;    //49 B相超级电容过压故障
    Uint16 OverModule2Icrms :1;    //50 C相超级电容过压故障
    Uint16 LowerSpcUA       :1;    //51 A相超级电容欠压故障
    Uint16 OverTempScr      :1;    //52 B相超级电容欠压故障
    Uint16 OverTimeStart    :1;    //53 C相超级电容欠压故障
    Uint16 DVROutUnderFault :1;    //54  输出欠压故障
    Uint16 M1_ACNC_DCNO_Flt :1;    //55 A相软起超时故障
    Uint16 M2_ACNC_DCNO_Flt :1;    //56 B相软起超时故障
    Uint16 M3_ACNC_DCNO_Flt :1;    //57 C相软起超时故障
    Uint16 M4_ACNC_DCNO_Flt :1;    //57 C相软起超时故障
    Uint16 OverTimeInvOut   :1;    //58 DVR输出超时故障
    Uint16 HighAmbientTemp:1;      //76  环境过温保护
    Uint16 HighInductanceTemp:1;   //77 电抗器过温保护
    Uint16 EmergentStop:1;         //78 急停
    Uint16 ScrFanFlt      :1;      //79 SCR风机故障
};


union FAULT_CODE3_REG
{
    Uint16 all;
    struct FAULT_CODE3_BITS bits;
};

struct FAULT_CODE4_BITS
{
    Uint16 Moudle1Fault  :1;     //64
    Uint16 Moudle2Fault  :1;     //65
    Uint16 Moudle3Fault  :1;     //66 A相IGBT过温故障
    Uint16 Moudle4Fault  :1;     //67 B相IGBT过温故障
    Uint16 BreakScrA      :1;     //73 A相SCR断路故障
    Uint16 BreakScrB      :1;     //74 B相SCR断路故障
    Uint16 BreakScrC      :1;     //75 C相SCR断路故障
    Uint16 ShortScrA      :1;     //70 A相SCR短路故障
    Uint16 ShortScrB      :1;     //71 B相SCR短路故障
    Uint16 ShortScrC      :1;     //72 C相SCR短路故障
    Uint16 op_slave      :1;     //72 C相SCR短路故障
};


union FAULT_CODE4_REG
{
    Uint16 all;
    struct FAULT_CODE4_BITS bits;
};

//状态机转换，设定值处理，故障标志位处理
enum enum_RunState
{
    Stop_State      = 4,        // 停机
    ReadyRun        = 2,        // 待机
    Dccharge        = 3,        // 直流充电
    ReadyStart      = 1,        // 交流预充电，启动中
    Running         = 8,        // 运行中
    Fault           = 16,       // 故障
    TestState       = 64        // 同步相位脉冲测试
};


struct STATE_MACHINE_DATA
{
    enum enum_RunState StateMachine;
    enum enum_RunState StateMachinepre;
    union MCW_REG McwReg;
    union MCW_REG PreMcwReg;
    union MSW_REG MswReg;
    union STATUS_REG0 StatusReg0;
    union STATUS_REG1 StatusReg1;
    union STATUS_REG2 StatusReg2;
    union FAULT_CODE0_REG FaultCode0Reg;
    union FAULT_CODE1_REG FaultCode1Reg;
    union FAULT_CODE2_REG FaultCode2Reg;
    union FAULT_CODE3_REG FaultCode3Reg;
    union FAULT_CODE4_REG FaultCode4Reg;
};


extern void StateMachineInit(void);
extern void StateMachineProc(void);

extern void MonitorDCMcbStatus(void);
extern void MonitorDCBrkStatus(void);

extern void MonitorALLModuleStatus(void);
extern void MonitorModule4BrkStatus(void);
extern void MonitorModule3BrkStatus(void);
extern void MonitorModule2BrkStatus(void);
extern void MonitorModule1BrkStatus(void);

extern void MonitorACOutMcbStatus(void);
extern void MonitorACBypassMcbStatus(void);
extern void MonitorACMcbStatus(void);
extern void MonitorACInMcbStatus(void);
extern void MonitorACConStatus(void);

extern void MonitorStatus(void);
extern void IOtext(void);
extern void MonitorModule_Flt(void);

extern void MonitorTRSoftConStatus(void);
extern void MonitorFilterCapConStatus(void);
extern void MonitorSB1Status(void);

#endif  // end of STATE_MACHINE_H definition


//===========================================================================
// End of file.
//===========================================================================
