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
// #define BYPASS 0//1-�޽����ߣ���·


struct MCW_BITS
{
    Uint16 Charge:1;         // 0 ����
    Uint16 Reset:1;          // 1 ��λ
    Uint16 AutoManual:1;     // 2  �Զ�/�ֶ� ¼��
    Uint16 Stop:1;           // 3
    Uint16 EnableA:1;        // 4
    Uint16 EnableB:1;        // 5
    Uint16 EnableC:1;        // 6
    Uint16 Enableseq :1;     // 7   ����ʹ��
    Uint16 Charge_Mode :1;   // 8   ���ģʽ0���� 1��ѹ
    Uint16 BypassMcboff :1;  // 9
    Uint16 InvRun:1;         // 10  ����
    Uint16 EnterTestMode:1;  // 11  ͬ������
    Uint16 Calibartion:1;    // 12    ��0
    Uint16 IOtext:1;         // 13    �̵�������
    Uint16 ParamEn:1;        // 14     ����ʹ��
    Uint16 Param:1;          // 15     ����Ĭ��

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
    Uint16 Charging:1;          //4 ����״̬
    Uint16 GridCompen:1;        //5 ����״̬
    Uint16 reset:1;             //6 ��λ״̬
    Uint16 TestMode:1;          //7 ����״̬
    Uint16 ParamEn:1;           //8
    Uint16 Calibartion:1;       //9
    Uint16 Togglebit:1;         //10 ����λ
    Uint16 Compenflag_flash:1;  //11
    Uint16 GridCompenpre:1;     //12 �Ŷ�
    Uint16 Gridabnomal:1;       //13 �����쳣
    Uint16 Start:1;             //14 ����
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
    Uint16 CompenStatus:1;   //2     ����״̬
    Uint16 InvStatusA  :1;   //3  A�������״̬
    Uint16 ComStatus1  :1;   //4  ģ��1ͨѶ״̬
    Uint16 ComStatus2  :1;   //5  ģ��2ͨѶ״̬
    Uint16 ChgStatusA  :1;   //6  A����״̬
    Uint16 ComStatus3  :1;   //7  ģ��3ͨѶ״̬
    Uint16 ComStatus4  :1;   //8  ģ��4ͨѶ״̬
    Uint16 ScrStatusA  :1;   //9  A��SCR״̬
    Uint16 ScrStatusB  :1;   //10 B��SCR״̬
    Uint16 ScrStatusC  :1;   //11 C��SCR״̬
    Uint16 InputSwitch :1;   //12 ���߿���״̬
    Uint16 OutputSwitch:1;   //13 ���߿���״̬
    Uint16 BypassMcb   :1;   //14 ��·����״̬
    Uint16 MainContact :1;   //15 ���Ӵ���״̬
};

union STATUS_REG0
{
    Uint16 all;
    struct STATUS_BITS0 bits;
};


struct STATUS_BITS1
{
    Uint16 SoftContact    :1;   //16  �����Ӵ���״̬
    Uint16 TRSoftCon      :1;   //17
    Uint16 FilteCapCon    :1;   //18
    Uint16 res            :1;   //19
    Uint16 BreakerDC      :1;   //20
    Uint16 Module3BreakDC :1;   //21 B��ֱ����·��״̬
    Uint16 Module4BreakDC  :1;   //22 C��ֱ����·��״̬
    Uint16 SectionSwitch  :1;   //23   ��ť����״̬
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
    Uint16 PhaSequFault     :1;   //0   ϵͳ��ѹ�������
    Uint16 OverSysIA        :1;   //1   ϵͳA�����
    Uint16 OverSysIB        :1;   //2   ϵͳB�����
    Uint16 OverSysIC        :1;   //3   ϵͳC�����
    Uint16 OverOutIA        :1;   //4   �����A�����
    Uint16 OverOutIB        :1;   //5        �����B�����
    Uint16 OverOutIC        :1;   //6        �����C�����
    Uint16 OverUdca         :1;   //7       ֱ��ĸ��A���ѹ
    Uint16 OverModule1Iarms :1;   //8       ֱ��ĸ��B���ѹ
    Uint16 OverModule1Ibrms :1;   //9       ֱ��ĸ��C���ѹ
    Uint16 UnderUdca        :1;   //10    ֱ��ĸ��A��Ƿѹ
    Uint16 OverModule1Icrms :1;   //11    ֱ��ĸ��B��Ƿѹ
    Uint16 OverModule2Iarms :1;   //12    ֱ��ĸ��C��Ƿѹ
    Uint16 OverAMoudle1Ipeak:1;   //13  ģ��A������ֵ����
    Uint16 OverBMoudle1Ipeak:1;   //14  ģ��B������ֵ����
    Uint16 OverCMoudle1Ipeak:1;   //15  ģ��C������ֵ����
};

union FAULT_CODE0_REG
{
    Uint16 all;
    struct FAULT_CODE0_BITS bits;
};


struct FAULT_CODE1_BITS
{
    Uint16 OversysIapeak   :1;   //16 A��ϵͳ������ֵ����
    Uint16 OversysIbpeak   :1;   //17 B��ϵͳ������ֵ����
    Uint16 OversysIcpeak   :1;   //18 C��ϵͳ������ֵ����
    Uint16 M1_DCBrkFUFlt   :1;   //19 A��ֱ����˿����
    Uint16 M2_DCBrkFUFlt   :1;   //20 B��ֱ����˿����
    Uint16 SB1overtime     :1;   //21 C��ֱ����˿����
    Uint16 M3_DCBrkFUFlt   :1;   //22 A�ཻ����˿����
    Uint16 M4_DCBrkFUFlt   :1;   //23 B�ཻ����˿����
    Uint16 ALL_ACBrkFUFlt  :1;   //24 C�ཻ����˿����
    Uint16 InputSwitchFlt  :1;   //25 ���߿��ع���
    Uint16 BypassSwitchFlt :1;   //26 ��·���ع���
    Uint16 OutputSwitchFlt :1;   //27 ���߿��ع���
    Uint16 OvercapIa       :1;   //28 A���˲����ݹ���
    Uint16 OvercapIb       :1;   //29 B���˲����ݹ���
    Uint16 OvercapIc       :1;   //30 C���˲����ݹ���
    Uint16 SoftContFault   :1;   //31   �����������

};

union FAULT_CODE1_REG
{
    Uint16 all;
    struct FAULT_CODE1_BITS bits;
};

struct FAULT_CODE2_BITS
{
    Uint16 MainContFault  :1;   //32  ���Ӵ�������
    Uint16 SCRFanConFlt   :1;   //33  ���Ӵ�������
    Uint16 TRSoftConFlt   :1;   //34
    Uint16 FilterCapConFlt:1;   //35
    Uint16 BreakerDcFlt   :1;   //36 ֱ����·������
    Uint16 DISBrkDcFlt    :1;   //37 �ŵ�΢�Ϲ���
    Uint16 ALL_ModuleFlt  :1;   //38 ��ģ��ȫ������
    Uint16 OverInvUA      :1;   //39 A���������ѹ����
    Uint16 OverInvUB      :1;   //40 B���������ѹ����
    Uint16 OverInvUC      :1;   //41 C���������ѹ����
    Uint16 OverUdcA_HW    :1;   //42 A��ֱ��Ӳ����ѹ����
    Uint16 OverUdcB_HW    :1;   //43 B��ֱ��Ӳ����ѹ����
    Uint16 OverUdcC_HW    :1;   //44 C��ֱ��Ӳ����ѹ����
    Uint16 OverAMoudle2Ipeak  :1;   //45 A��ֱ����������
    Uint16 OverBMoudle2Ipeak  :1;   //46 B��ֱ����������
    Uint16 OverCMoudle2Ipeak  :1;   //47 C��ֱ����������

};


union FAULT_CODE2_REG
{
    Uint16 all;
    struct FAULT_CODE2_BITS bits;
};

struct FAULT_CODE3_BITS
{
    Uint16 OverSpcUA        :1;    //48 A�೬�����ݹ�ѹ����
    Uint16 OverModule2Ibrms :1;    //49 B�೬�����ݹ�ѹ����
    Uint16 OverModule2Icrms :1;    //50 C�೬�����ݹ�ѹ����
    Uint16 LowerSpcUA       :1;    //51 A�೬������Ƿѹ����
    Uint16 OverTempScr      :1;    //52 B�೬������Ƿѹ����
    Uint16 OverTimeStart    :1;    //53 C�೬������Ƿѹ����
    Uint16 DVROutUnderFault :1;    //54  ���Ƿѹ����
    Uint16 M1_ACNC_DCNO_Flt :1;    //55 A������ʱ����
    Uint16 M2_ACNC_DCNO_Flt :1;    //56 B������ʱ����
    Uint16 M3_ACNC_DCNO_Flt :1;    //57 C������ʱ����
    Uint16 M4_ACNC_DCNO_Flt :1;    //57 C������ʱ����
    Uint16 OverTimeInvOut   :1;    //58 DVR�����ʱ����
    Uint16 HighAmbientTemp:1;      //76  �������±���
    Uint16 HighInductanceTemp:1;   //77 �翹�����±���
    Uint16 EmergentStop:1;         //78 ��ͣ
    Uint16 ScrFanFlt      :1;      //79 SCR�������
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
    Uint16 Moudle3Fault  :1;     //66 A��IGBT���¹���
    Uint16 Moudle4Fault  :1;     //67 B��IGBT���¹���
    Uint16 BreakScrA      :1;     //73 A��SCR��·����
    Uint16 BreakScrB      :1;     //74 B��SCR��·����
    Uint16 BreakScrC      :1;     //75 C��SCR��·����
    Uint16 ShortScrA      :1;     //70 A��SCR��·����
    Uint16 ShortScrB      :1;     //71 B��SCR��·����
    Uint16 ShortScrC      :1;     //72 C��SCR��·����
    Uint16 op_slave      :1;     //72 C��SCR��·����
};


union FAULT_CODE4_REG
{
    Uint16 all;
    struct FAULT_CODE4_BITS bits;
};

//״̬��ת�����趨ֵ�������ϱ�־λ����
enum enum_RunState
{
    Stop_State      = 4,        // ͣ��
    ReadyRun        = 2,        // ����
    Dccharge        = 3,        // ֱ�����
    ReadyStart      = 1,        // ����Ԥ��磬������
    Running         = 8,        // ������
    Fault           = 16,       // ����
    TestState       = 64        // ͬ����λ�������
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
