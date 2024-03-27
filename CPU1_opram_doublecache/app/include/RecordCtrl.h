/*
 * RecordCtrl.h
 *
 *  Created on: 2024��3��5��
 *      Author: Admin
 */

#ifndef APP_INCLUDE_RECORDCTRL_H_
#define APP_INCLUDE_RECORDCTRL_H_
#include"NandFlash.h"

#define NF_ParaBlkID   0      //Һ����������Χ0~9 block
#define NF_RecdBlkID   10    //¼��������Χ10~299 block
#define NF_WaveBlkID   300   //�������ݷ�Χ300~2048 block


#define NF_GroupNum    20     //��ౣ�����������
//#define NF_PreSampNum  300    //�¼�����ǰҪ����Ĳ����� delete
#define NF_PreSampNum  150    //�¼�����ǰҪ����Ĳ����� change
#define NF_SampTypeNum 20     //����������
#define NF_SampOffset  0 //

#define NF_TypeBlkNumR 300   //��¼ÿ��¼������Ԥ����block��
#define NF_TypeBlkNumP 30    //����ÿ��¼������Ԥ����block��
//����
#define NF_TypeParaNum 17     //ÿ�����ݵĲ�������,6��ʱ��+11��״̬��
#define NF_DataTypeNum 2      //NF_DATA������������:����,����
#define NF_DataParaNum 341    //NF_DATA���ܲ���������20*(6+11)+1
//�������ݿ�
//#define SAMP_NUM_FLT   2000   //���ϲ����㻺������ delete
#define SAMP_NUM_FLT   1000   //���ϲ����㻺������ change
#define NF_SampNum_Flt 50     //ÿ�α���Ĳ�����������ÿҳ�ܹ����������������=1024/20
//#define NF_SectNum_Flt 40     //ÿ�α�������ݶ�������ҳ��=2000/50 delete
#define NF_SectNum_Flt 20     //ÿ�α��������ҳ��=1000/50
#define NF_BlkNum_Flt  1      //ÿ��block��=20/64
//��ֵ���ݿ�
//#define SAMP_NUM       15000L  //��ѹ�쳣��ֵ�����㻺������ delete
#define SAMP_NUM       7500L  //��ѹ�쳣��ֵ�����㻺������ change
#define NF_SampNum_Abn 50     //ÿ�α���Ĳ�����������ÿҳ�ܹ����������������=1024/20
//#define NF_SectNum_Abn 300    //ÿ�α�������ݶ�������ҳ��=15000/50 delete
#define NF_SectNum_Abn 150    //ÿ�α�������ݶ�������ҳ��=7500/50
//#define NF_BlkNum_Abn  5     //ÿ��block��=300/64
#define NF_BlkNum_Abn  3     //ÿ��block��=150/64
//��Чֵ���ݿ�
#define NF_DataNum_Rms 600
#define NF_SampNum_Rms 50     //ÿ�α���Ĳ�����������ÿҳ�ܹ����������������=1024/6
#define NF_SectNum_Rms 12     //ÿ�α�������ݶ�������ҳ��=600/50
#define NF_BlkNum_Rms  1      //ÿ��block��=6/64

#define CYCLE_NUM      200    //�ܲ�����������5kHz/50Hz
#define SampTypeNum    14     //����������

#define NF_PreNum_Rms  50     //
#define NF_TpyeNum_Rms 6      //

#define ALL_FLAG_LEN   11     //���з��Ÿ���


enum NF_OPNUM  //NF������
{
    NF_Write_Wave = 1,      //д¼����������
    NF_Write_Recd = 2,      //д¼����������
    NF_Write_AbnRms = 3,    //
    NF_Read_Wave = 4,       //��¼����������
    NF_Write_Para = 5,      //дҺ�������ò���
    NF_Read_Para = 6,       //��Һ�������ú�¼������
    NF_Init_Recd = 7
};

enum RecordData_Type
{
    RD_Idle,
    RD_Fault, //��������
    RD_Abnor,     //��ѹ�쳣��ֵ����
    RD_AbnRms,    //��ѹ�쳣��Чֵ����
    RD_InitNF,    //��ʼ��NF
    RD_SetRtc     //
};

typedef struct
{
    //34��
    Uint16 OpNum;                                  //������
    Uint16 Fault;                                  //���ϱ�־
    Uint16 SampIndex;                              //
    Uint16 SampFltIndex;                              //���ϱ������
    Uint16 SampRmsIdx;                             //
    int16 Index;
    int16 FltIndex;                                //���ϻ���Ŀ��ֵ
    int16 RmsIdx;                                  //
    Uint16 Count;                                  //���ݼ���
    Uint16 BlkID;                                  //���ݱ�����
    Uint16 BlkLmt;                                 //
    Uint16 SampNum;                                //
    Uint16 SectNum;                                //
    Uint16 BlkNum;                                 //
    Uint16 BlkCnt;                                 //
    Uint16 Type;                                   //��������
    Uint16 Step;                                   //��������
    Uint16 InitStep;                               //
    Uint16 FltRdEn;                                //�������ݲɼ�ʹ��
    Uint16 FltRdEn2;                                //����2�������ݲɼ�ʹ�� add
    bool_t WriteFltcache;                           //д���ϻ����־λ add
    bool_t ReadFltcache;                           //�����ϻ����־λ add
    Uint16 FltTrip;
    Uint16 RmsRdEn;                                //��Чֵ���ݲɼ�ʹ��
    Uint16 NowRdEn;
    Uint16 NowRdEn2;                               //��ֵ���ݻ���ʹ�� add
    bool_t WriteNowcache;                          //д��ֵ�����־λ add
    bool_t ReadNowcache;                           //����ֵ�����־λ add
    Uint16 RmsCmpEn;                               //
    Uint16 CmpEn;
    Uint16 FltEn;
    Uint16 WEn;
    Uint16 FltWEn;                                 //�������ݻ���дflash��־λ
    Uint16 ParaWtEn;                               //
//682
    Uint16 Para[NF_DataTypeNum][NF_DataParaNum];   //3������:����,����,ÿ�����ݰ���:1���������� +ÿ��6��ʱ��+11��״̬��
//11
    Uint16 Flag[ALL_FLAG_LEN];
    //����ʱ״̬����
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
    Uint16 OpNum;             //������
    Uint16 BlkID;             //���ݱ�����
    Uint16 BlkLmt;            //
    Uint16 SampNum;           //
    Uint16 SectNum;           //
    Uint16 BlkNum;            //
    Uint16 BlkCnt;            //
    Uint16 TxEn;              //���ݴ���ʹ��
    Uint16 Type;              //��������ѡ��
    Uint16 Numb;              //���ݼ�¼��
    Uint16 Step;              //���ݵ�������
    Uint16 Count;             //�μ�����15�����ݷ�5�Σ�һ��3������
    Uint16 Index;             //���ݻ��浱ǰ����
    Uint16 OpDelay;
    Uint16 OldIdx;            //���ݻ��浱ǰ����
    int16 Buff[NF_BYTE_NUM];  //����ͨ�����ݻ���
}RECORD_DATA;

extern NF_DATA NF_Data;
extern RECORD_DATA RecordData;
//extern RAM_DATA RAM_Data1;//add
//extern RAM_DATA RAM_Data1;//add

#endif /* APP_INCLUDE_RECORDCTRL_H_ */
