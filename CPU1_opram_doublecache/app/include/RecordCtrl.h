/*
 * RecordCtrl.h
 *
 *  Created on: 2024年3月5日
 *      Author: Admin
 */

#ifndef APP_INCLUDE_RECORDCTRL_H_
#define APP_INCLUDE_RECORDCTRL_H_
#include"NandFlash.h"

#define NF_ParaBlkID   0      //液晶屏参数范围0~9 block
#define NF_RecdBlkID   10    //录波参数范围10~299 block
#define NF_WaveBlkID   300   //波形数据范围300~2048 block


#define NF_GroupNum    20     //最多保存的数据组数
//#define NF_PreSampNum  300    //事件发生前要保存的采样数 delete
#define NF_PreSampNum  150    //事件发生前要保存的采样数 change
#define NF_SampTypeNum 20     //采样类型数
#define NF_SampOffset  0 //

#define NF_TypeBlkNumR 300   //记录每种录波类型预留的block数
#define NF_TypeBlkNumP 30    //参数每种录波类型预留的block数
//参数
#define NF_TypeParaNum 17     //每组数据的参数个数,6个时间+11个状态量
#define NF_DataTypeNum 2      //NF_DATA的数据类型数:跌落,故障
#define NF_DataParaNum 341    //NF_DATA的总参数个数，20*(6+11)+1
//故障数据块
//#define SAMP_NUM_FLT   2000   //故障采样点缓存数量 delete
#define SAMP_NUM_FLT   1000   //故障采样点缓存数量 change
#define NF_SampNum_Flt 50     //每段保存的采样个数，即每页能够保存的最多采样个数=1024/20
//#define NF_SectNum_Flt 40     //每次保存的数据段数，即页数=2000/50 delete
#define NF_SectNum_Flt 20     //每次保存的数据页数=1000/50
#define NF_BlkNum_Flt  1      //每组block数=20/64
//峰值数据块
//#define SAMP_NUM       15000L  //电压异常峰值采样点缓存数量 delete
#define SAMP_NUM       7500L  //电压异常峰值采样点缓存数量 change
#define NF_SampNum_Abn 50     //每段保存的采样个数，即每页能够保存的最多采样个数=1024/20
//#define NF_SectNum_Abn 300    //每次保存的数据段数，即页数=15000/50 delete
#define NF_SectNum_Abn 150    //每次保存的数据段数，即页数=7500/50
//#define NF_BlkNum_Abn  5     //每组block数=300/64
#define NF_BlkNum_Abn  3     //每组block数=150/64
//有效值数据块
#define NF_DataNum_Rms 600
#define NF_SampNum_Rms 50     //每段保存的采样个数，即每页能够保存的最多采样个数=1024/6
#define NF_SectNum_Rms 12     //每次保存的数据段数，即页数=600/50
#define NF_BlkNum_Rms  1      //每组block数=6/64

#define CYCLE_NUM      200    //周波采样点数量5kHz/50Hz
#define SampTypeNum    14     //采样类型数

#define NF_PreNum_Rms  50     //
#define NF_TpyeNum_Rms 6      //

#define ALL_FLAG_LEN   11     //所有符号个数


enum NF_OPNUM  //NF操作码
{
    NF_Write_Wave = 1,      //写录波波形数据
    NF_Write_Recd = 2,      //写录波参数数据
    NF_Write_AbnRms = 3,    //
    NF_Read_Wave = 4,       //读录波波形数据
    NF_Write_Para = 5,      //写液晶屏设置参数
    NF_Read_Para = 6,       //读液晶屏设置和录波参数
    NF_Init_Recd = 7
};

enum RecordData_Type
{
    RD_Idle,
    RD_Fault, //故障数据
    RD_Abnor,     //电压异常峰值数据
    RD_AbnRms,    //电压异常有效值数据
    RD_InitNF,    //初始化NF
    RD_SetRtc     //
};

typedef struct
{
    //34个
    Uint16 OpNum;                                  //操作码
    Uint16 Fault;                                  //故障标志
    Uint16 SampIndex;                              //
    Uint16 SampFltIndex;                              //故障保存计数
    Uint16 SampRmsIdx;                             //
    int16 Index;
    int16 FltIndex;                                //故障缓存目标值
    int16 RmsIdx;                                  //
    Uint16 Count;                                  //数据计数
    Uint16 BlkID;                                  //数据保存块号
    Uint16 BlkLmt;                                 //
    Uint16 SampNum;                                //
    Uint16 SectNum;                                //
    Uint16 BlkNum;                                 //
    Uint16 BlkCnt;                                 //
    Uint16 Type;                                   //数据类型
    Uint16 Step;                                   //操作步骤
    Uint16 InitStep;                               //
    Uint16 FltRdEn;                                //故障数据采集使能
    Uint16 FltRdEn2;                                //缓存2故障数据采集使能 add
    bool_t WriteFltcache;                           //写故障缓存标志位 add
    bool_t ReadFltcache;                           //读故障缓存标志位 add
    Uint16 FltTrip;
    Uint16 RmsRdEn;                                //有效值数据采集使能
    Uint16 NowRdEn;
    Uint16 NowRdEn2;                               //峰值数据缓存使能 add
    bool_t WriteNowcache;                          //写峰值缓存标志位 add
    bool_t ReadNowcache;                           //读峰值缓存标志位 add
    Uint16 RmsCmpEn;                               //
    Uint16 CmpEn;
    Uint16 FltEn;
    Uint16 WEn;
    Uint16 FltWEn;                                 //故障数据缓存写flash标志位
    Uint16 ParaWtEn;                               //
//682
    Uint16 Para[NF_DataTypeNum][NF_DataParaNum];   //3中数据:跌落,故障,每种数据包括:1个发生次数 +每组6个时间+11个状态量
//11
    Uint16 Flag[ALL_FLAG_LEN];
    //故障时状态缓存
//#ifdef EXRAM_512K
//14000
//    int16 SampBuf2[SampTypeNum][SAMP_NUM_FLT];//add
//#endif
//#ifdef EXRAM_512K
////105,000
//    int16 SampBuf_Start2[SampTypeNum][SAMP_NUM];//add
//#endif
//
//#ifdef EXRAM_512K
////3600
//    int16 AbnRms2[NF_TpyeNum_Rms][NF_DataNum_Rms];//add
//#endif
}NF_DATA;
//typedef struct
//{
//14000
extern int16 SampBuf[SampTypeNum][SAMP_NUM_FLT];
//14000
extern int16 SampBuf2[SampTypeNum][SAMP_NUM_FLT];//add
//105,000
extern int16 SampBuf_Start[SampTypeNum][SAMP_NUM];
//105,000
extern int16 SampBuf2_Start[SampTypeNum][SAMP_NUM];//add
//3600
extern int16 AbnRms[NF_TpyeNum_Rms][NF_DataNum_Rms];
//}RAM_DATA;

typedef struct
{
    Uint16 Flag_Rd;
    Uint16 OpNum;             //操作码
    Uint16 BlkID;             //数据保存块号
    Uint16 BlkLmt;            //
    Uint16 SampNum;           //
    Uint16 SectNum;           //
    Uint16 BlkNum;            //
    Uint16 BlkCnt;            //
    Uint16 TxEn;              //数据传输使能
    Uint16 Type;              //数据类型选择
    Uint16 Numb;              //数据记录号
    Uint16 Step;              //数据导出步骤
    Uint16 Count;             //段计数，15组数据分5段，一段3组数据
    Uint16 Index;             //数据缓存当前索引
    Uint16 OpDelay;
    Uint16 OldIdx;            //数据缓存当前索引
    int16 Buff[NF_BYTE_NUM];  //三个通道数据缓存
}RECORD_DATA;

extern NF_DATA NF_Data;
extern RECORD_DATA RecordData;
//extern RAM_DATA RAM_Data1;//add
//extern RAM_DATA RAM_Data1;//add

#endif /* APP_INCLUDE_RECORDCTRL_H_ */
