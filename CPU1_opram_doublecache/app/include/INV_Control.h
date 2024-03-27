

#ifndef INV_CONTROL_H
#define INV_CONTROL_H


#include "F2837xD_Device.h"
#include "F2837xD_Examples.h"    // DSP2833x Examples Include File


struct INV_CONTROL_PAR
{
    float UdcKp;
    float UdcKi;
    float UdcMax;
    float UdcMin;

    float UcapKp;
    float UcapKi;
    float UcapMax;
    float UcapMin;

    float CurKp;
    float CurKi;
    float CurMax;
    float CurMin;

    float PllKp;
    float PllKi;
    float PllMax;
    float PllMin;

    float Idckp;
    float Idcki;
    float Idcmax;
    float Idcmin;

    float vdlvrt;
    float vdhvrt;

    Uint16 t_Inv;
    float Ucap_charge;
    float Ucap_stop;
    float Ucap_Dvr_quit;
    float Ugrid_filter_k;
    float Uinv_filter_k;
    float Igrid_filter_k;
    float Iinv_filter_k;
    Uint16 t_syon;
    float V_diff;
    float vdref;
    float Idref;
    float Scrcur;
    float Udc_ref;
    float Transformer_k;
    float Salve;
    float Salve_NUM;

};




struct INV_CONTROL_INPUT
{
    float UdcRef;
    float VolRef;           //V/F模式下电压设定
    float FreqRef;          //V/F模式频率设定
    float Iqref;
    float Udc;
    float Udc_pn;
    float Udc_nn;
    float Idc;
    float IgbtIa0;
    float IgbtIb0;
    float IgbtIc0;
    float GridUa0;
    float GridUb0;
    float GridUc0;
    float GridUan0;
    float GridUbn0;
    float GridUcn0;
    float LoadUa0;
    float LoadUb0;
    float LoadUc0;
    float LoadUan0;
    float LoadUbn0;
    float LoadUcn0;
    float LoadIa0;
    float LoadIb0;
    float LoadIc0;
    float cap;
    float Vdref;
    float Idref;
    float Idcref;
    float spwmafactor;
};
struct INV_CONTROL_OUTPUT
{
        float Load_trs_Theta;
        float Load_trs_SinTheta;
        float Load_trs_CosTheta;

        float LoadATheta;
        float GridATheta;
        float GridAFrequency;
        float SinThetaA;
        float CosThetaA;

        float LoadBTheta;
        float GridBTheta;
        float GridBFrequency;
        float SinThetaB;
        float CosThetaB;

        float LoadCTheta;
        float GridCTheta;
        float GridCFrequency;
        float SinThetaC;
        float CosThetaC;

        float SysTheta;
        float SysFrequency;
        float SysSinTheta;
        float SysCosTheta;

        float SysATheta;
        float SysAFrequency;
        float SysASinTheta;
        float SysACosTheta;

        float SysBTheta;
        float SysBFrequency;
        float SysBSinTheta;
        float SysBCosTheta;

        float SysCTheta;
        float SysCFrequency;
        float SysCSinTheta;
        float SysCCosTheta;

        float vdref;
        float Invline_Vd;
        float InvVdb;
        float InvVdc;
        float InvVdp;
        float InvVdn;

        float Vqref;
        float Invline_Vq;
        float InvVqb;
        float InvVqc;
        float InvVqp;
        float InvVqn;

        float Idpref;
        float Idnref;
        float IgbtIdp;
        float IgbtIdn;

        float Iqpref;
        float Iqnref;
        float IgbtIqp;
        float IgbtIqn;

        float IdpPi_Out;
        float IdnPi_Out;
        float IqpPi_Out;
        float IqnPi_Out;
        float IdcPi_Out;

        float GridVda;
        float GridVdb;
        float GridVdc;
        float GridVqa;
        float GridVqb;
        float GridVqc;
        float LoadIdp;
        float LoadIdn;
        float LoadIqp;
        float LoadIqn;

        float GridVdap;
        float GridVdbp;
        float GridVdcp;
        float GridUd;
        float GridUq;
        float Gridline_Ud;
        float Gridline_Uq;

        float SpwmVd;
        float SpwmVq;
        float PwmT1;
        float PwmT2;
        float PwmT3;
        float PwmT4;
        float Idc_ford;
};

struct CTL_MCW_BITS
{
    Uint16 Run:1;           // 0 启停
    Uint16 synon:1;         // 1 同步标志位
    Uint16 OvertimeEn:1;    // 2
    Uint16 TestInv:1;       // 3 逆变测试
    Uint16 Reset:1;         // 4复位
    Uint16 GridSwitch:1;    // 外部给的并网开关状态，1:并网运行，0:vf孤网运行
    Uint16 IdcMode:1;       // 1=Idc，0=udc
    Uint16 Testpwm:1;       // 1=PQ, 0=Idc or udc 优先级高于udc和idc
    Uint16 QMode:1;         // 无功模式
    Uint16 Fault:1;         // 故障位
    Uint16 UnderEnergy:1;   //
    Uint16 Gridrecovery:1;
    Uint16 GridLvrt:1;        // 12 低穿标志位
    Uint16 GridHvrt:1;        // 13 高穿标志位
    Uint16 Compenflag_flash:1;// 14 flash 标志位
    Uint16 Gridabnomal:1;     // 15 扰动标志位
};

enum enumCtlMode
{
    Standby     = 1,
    Idc_Q       = 2,
    Udc_Q       = 4,
    VF_ISLAND   = 8
};

enum enumPllMode
{
    Island     = 1,
    Gridsys     = 2
};

union CTL_MCW_REG
{
    Uint16 all;
    struct CTL_MCW_BITS bits;
};

typedef struct
{
    enum enumPllMode PllMode;
    enum enumCtlMode CtlINVMode;
    struct INV_CONTROL_INPUT *input;
    struct INV_CONTROL_OUTPUT *output;
    struct INV_CONTROL_PAR *par;
    union CTL_MCW_REG CtlMcwReg;
    union CTL_MCW_REG CtlMcwRegPre;
    void (*init)();
    void  (*run)();
}INV_CONTROL_OBJ;

#define INV_CONTROL_DATA_OBJ_DEFAULTS {\
    Gridsys,\
    Standby,\
    0,\
    0,\
    0,\
    0,\
    0,\
    (void (*)(Uint32))InvControlInit,\
    (void (*)(Uint32))InvControl}

extern union WORD_REG ConfigCopy;


extern INV_CONTROL_OBJ Inv_controlobj;


void InvControl(INV_CONTROL_OBJ *v);
void InvControlInit(INV_CONTROL_OBJ *v);

void CaltIdcMode(INV_CONTROL_OBJ *v);
void CaltUdcIqMode(INV_CONTROL_OBJ *v);
void CaltIdqRef(INV_CONTROL_OBJ *v);
void CaltIslandMode(INV_CONTROL_OBJ *v);
void CalGridAPll(INV_CONTROL_OBJ *v);
void CalGridBPll(INV_CONTROL_OBJ *v);
void CalGridCPll(INV_CONTROL_OBJ *v);
void PwmOut(INV_CONTROL_OBJ *v);
void CalCurrentPI(INV_CONTROL_OBJ *v);
void CalParkTrans(INV_CONTROL_OBJ *v);
void CalSysParkTrans(INV_CONTROL_OBJ *v);
void CaltIdcRef (INV_CONTROL_OBJ *v);















#endif
