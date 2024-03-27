/*
 * RecordCtrl.c
 *
 *  Created on: 2024年3月5日
 *      Author: Admin
 */
#include <string.h>
#include <stddef.h>
#include "F2837xD_Device.h"
#include "F2837xD_Examples.h"    // DSP2833x Examples Include File
#include "Global_struct.h"
#include "RtcDS1302.h"
#include "RecordCtrl.h"
#include "ExRAM.h"
//test
int16 testk;
//14000
int16 SampBuf[SampTypeNum][SAMP_NUM_FLT];
//14000
int16 SampBuf2[SampTypeNum][SAMP_NUM_FLT];//add
//105,000
int16 SampBuf_Start[SampTypeNum][SAMP_NUM];
//105,000
int16 SampBuf2_Start[SampTypeNum][SAMP_NUM];//add
//3600
int16 AbnRms[NF_TpyeNum_Rms][NF_DataNum_Rms];
NF_DATA NF_Data;
RECORD_DATA RecordData;
//RAM_DATA RAM_Data1;//add
//RAM_DATA RAM_Data2;
Uint16 buff[NF_BYTE_NUM];
Uint16 buf_i = 0;

#pragma DATA_SECTION(buff,"WAVEDATA1");
#pragma DATA_SECTION(RecordData,"WAVEDATA2");
#pragma DATA_SECTION(NF_Data,"WAVEDATA3");
#pragma DATA_SECTION(SampBuf,"WAVEDATA4");
#pragma DATA_SECTION(SampBuf2,"WAVEDATA5");
#pragma DATA_SECTION(SampBuf_Start,"WAVEDATA6");
#pragma DATA_SECTION(SampBuf2_Start,"WAVEDATA7");
#pragma DATA_SECTION(AbnRms,"WAVEDATA8");



//==========================//
//函数名:NandFlashInit()
//描述:Nand Flash初始化
//输入:
//输出:
//==========================//
void NandFlashInit(void)
{
    Uint32 i;
    int16 *pTmp = 0;

    NF_Data.OpNum = NF_Read_Para;
    NF_Data.Fault = 0;
    NF_Data.SampIndex = 0;
    NF_Data.SampRmsIdx = 0;
    NF_Data.SampFltIndex = 0;
    NF_Data.Index = 0;
    NF_Data.RmsIdx = 0;
    NF_Data.Count = 0;
    NF_Data.BlkID = 0;
    NF_Data.BlkLmt = 0;
    NF_Data.SampNum = 0;
    NF_Data.SectNum = 0;
    NF_Data.BlkNum = 0;
    NF_Data.BlkCnt = 0;
    NF_Data.Type = 0;
    NF_Data.Step = 0;
    NF_Data.InitStep = 0;
    NF_Data.FltRdEn = 1;
    NF_Data.FltRdEn2 = 1;//add
    NF_Data.ReadFltcache = 0;
    NF_Data.FltTrip = 1;
    NF_Data.FltWEn = 0;
    NF_Data.FltEn = 0;
    NF_Data.RmsRdEn = 1;
    NF_Data.NowRdEn = 1;
    NF_Data.NowRdEn2 = 1;
    NF_Data.RmsCmpEn = 0;
    NF_Data.CmpEn = 0;
    NF_Data.WEn = 0;
    NF_Data.ParaWtEn = 0;

    for(i=0; i<NF_DataParaNum; i++)
    {
        NF_Data.Para[0][i] = 0;
        NF_Data.Para[1][i] = 0;
    }

    for(i=0; i<ALL_FLAG_LEN; i++)
        NF_Data.Flag[i] = 0;

    pTmp = &SampBuf[0][0];//FLT CACHE1
    for(i=0; i<SampTypeNum*SAMP_NUM_FLT; i++)
    {
        *pTmp++ = 0;//delete
    }
//#ifdef EXRAM_512K
    pTmp = &SampBuf2[0][0];//FLT CACHE2
    for(i=0; i<SampTypeNum*SAMP_NUM_FLT; i++)
    {
        *pTmp++ = 0;//delete
    }
//#endif
    pTmp = &SampBuf_Start[0][0];//PEAK CACHE1
     for(i=0; i<SampTypeNum*SAMP_NUM; i++)
     {
         *pTmp++ = 0;
     }
//#ifdef EXRAM_512K
     pTmp = &SampBuf2_Start[0][0];//PEAK CACHE2
      for(i=0; i<SampTypeNum*SAMP_NUM; i++)
      {
          *pTmp++ = 0;
      }
//#endif
    pTmp = &AbnRms[0][0];//RMS CACHE1
    for(i=0; i<NF_TpyeNum_Rms*NF_DataNum_Rms; i++)
    {
        *pTmp++ = 0;
    }
#ifdef EXRAM_512K
    pTmp = &NF_Data.AbnRms2[0][0];//RMS CACHE2
    for(i=0; i<NF_TpyeNum_Rms*NF_DataNum_Rms; i++)
    {
        *pTmp++ = 0;
    }
#endif
    pTmp = 0;
    RecordData.Flag_Rd = 0;
    RecordData.OpNum = 0;
    RecordData.BlkID = 0;
    RecordData.BlkLmt = 0;
    RecordData.SampNum = 0;
    RecordData.SectNum = 0;
    RecordData.BlkNum = 0;
    RecordData.BlkCnt = 0;
    RecordData.TxEn = 0;
    RecordData.Type = 0;
    RecordData.Numb = 0;
    RecordData.Step = 0;
    RecordData.Count = 0;
    RecordData.Index = 0;
    RecordData.OldIdx = 0;

    for(i=0;i<NF_BYTE_NUM;i++)
        RecordData.Buff[i] = 0;
}

//==========================//
//函数名:NF_Operate()
//描述:NF读写录波数据操作
//输入:
//输出:
//==========================//
void NF_Operate(void)
{
    Uint16 i,k,*p;
    int16 index;

    switch(NF_Data.OpNum)
    {
        //1写录波波形
        case NF_Write_Wave:
        {
            if(NF_Data.Step==0) //参数初始化
            {
                //获取缓存索引号
                //计算组号，block号
                if(NF_Data.Type==RD_Fault)
                {
                    NF_Data.SampNum = NF_SampNum_Flt;
                    NF_Data.SectNum = NF_SectNum_Flt;
                    NF_Data.BlkNum = NF_BlkNum_Flt;
                }
                else if(NF_Data.Type==RD_Abnor)
                {
                    NF_Data.Index = NF_Data.SampIndex-1-NF_PreSampNum;
                    if(NF_Data.Index < 0)
                    NF_Data.Index += SAMP_NUM;
                    NF_Data.RmsIdx = NF_Data.SampRmsIdx-1-NF_PreNum_Rms;
                    if(NF_Data.RmsIdx < 0)
                    NF_Data.RmsIdx += NF_DataNum_Rms;
                    NF_Data.RmsCmpEn = 1;
                //    NF_Data.NowRdEn = 1;
                    NF_Data.CmpEn = 1;
                    NF_Data.SampNum = NF_SampNum_Abn;
                    NF_Data.SectNum = NF_SectNum_Abn;
                    NF_Data.BlkNum = NF_BlkNum_Abn;
                }

                k = NF_Data.Type - 1;//故障数据：k=0；电压异常数据：k=1；RD_AbnRms,有效值数据：k=2
                i = NF_Data.Para[k][0]%NF_GroupNum;//明天试一下减1 0-20Group
                NF_Data.BlkID = NF_WaveBlkID+k*NF_TypeBlkNumR+i*NF_Data.BlkNum;//根据类型计算块号
                NF_Data.BlkLmt = NF_WaveBlkID+(k+1)*NF_TypeBlkNumR;
                i *= NF_TypeParaNum;

                //更新录波参数
                NF_Data.Para[k][0]++;              //总发生次数
                NF_Data.Para[k][i+1] = Rtc_Data.CurTime[Rtc_Year];
                NF_Data.Para[k][i+2] = Rtc_Data.CurTime[Rtc_Month];
                NF_Data.Para[k][i+3] = Rtc_Data.CurTime[Rtc_Day];
                NF_Data.Para[k][i+4] = Rtc_Data.CurTime[Rtc_Hour];
                NF_Data.Para[k][i+5] = Rtc_Data.CurTime[Rtc_Minute];
                NF_Data.Para[k][i+6] = Rtc_Data.CurTime[Rtc_Second];
                //write ram cache add
                if(NF_Data.Type==RD_Fault)
                {
                    //写flash前缓存
                    NF_Data.Para[k][i+7]  = NF_Data.Flag[0];  //状态0
                    NF_Data.Para[k][i+8]  = NF_Data.Flag[1];  //状态1
                    NF_Data.Para[k][i+9]  = NF_Data.Flag[2];  //状态2
                    NF_Data.Para[k][i+10] = NF_Data.Flag[3];  //状态3
                    NF_Data.Para[k][i+11] = NF_Data.Flag[4];  //状态4
                    NF_Data.Para[k][i+12] = NF_Data.Flag[5];  //状态5
                    NF_Data.Para[k][i+13] = NF_Data.Flag[6];  //状态6
                    NF_Data.Para[k][i+14] = NF_Data.Flag[7];  //状态7
                    NF_Data.Para[k][i+15] = NF_Data.Flag[8];  //状态8
                    NF_Data.Para[k][i+16] = NF_Data.Flag[9];  //状态9
                    NF_Data.Para[k][i+17] = NF_Data.Flag[10]; //状态10
                }

                NF_Data.BlkCnt = 0;
                NF_Data.Count = 0;
                NF_Data.Step = 1;
            }
            if((NF_Data.Step==1)&&(RunData.StateMachine.MswReg.bits.Gridabnomal==0)) //擦除新块
            {
                NF_WP_EN = 1;//写使能引脚
                k = NF_Data.BlkID;
                //在NF_WaveBlkID~NF_BLOCK_NUM block间写波形数据
                for(i=k; i<NF_Data.BlkID+NF_Data.BlkNum; i++)
                {
                    NF_EraseBlock(i);
                }

               NF_Data.Step = 2;
            }
            else if((NF_Data.Step==2)&&(RunData.StateMachine.MswReg.bits.Gridabnomal==0)) //存储数据
            {

                if((NF_Data.WEn==1)&&(NF_Data.Type==RD_Abnor))
                {
                    for(i=0; i<NF_Data.SampNum; i++)//缓存一页
                    {
                       //保存前缓存峰值数据
                       index = NF_Data.Index;
                       k = i*NF_SampTypeNum;
#ifdef EXRAM_512K
                       if(NF_Data.ReadNowcache)//如果异常次数是1的倍数从故障缓存1读数据
#endif
                       //read ram cache add
                       {
                           buff[k] =   SampBuf_Start[0][index]+NF_SampOffset;//电网电压A
                           buff[k+1] = SampBuf_Start[1][index]+NF_SampOffset;//电网电压B
                           buff[k+2] = SampBuf_Start[2][index]+NF_SampOffset;//电网电压C
                           buff[k+3] = SampBuf_Start[3][index]+NF_SampOffset;//逆变电压A
                           buff[k+4] = SampBuf_Start[4][index]+NF_SampOffset;//逆变电压B
                           buff[k+5] = SampBuf_Start[5][index]+NF_SampOffset;//逆变电压C
                           buff[k+6] = SampBuf_Start[6][index]+NF_SampOffset;//模块电流A
                           buff[k+7] = SampBuf_Start[7][index]+NF_SampOffset;//模块电流B
                           buff[k+8] = SampBuf_Start[8][index]+NF_SampOffset;//模块电流C
                           buff[k+9] = SampBuf_Start[9][index]+NF_SampOffset;//系统电流A
                           buff[k+10] = SampBuf_Start[10][index]+NF_SampOffset;//系统电流B
                           buff[k+11] = SampBuf_Start[11][index]+NF_SampOffset;//系统电流C
                           buff[k+12] = SampBuf_Start[12][index]+NF_SampOffset;//母线电压
                       }
#ifdef EXRAM_512K
                       else//从故障缓存2读数据
                       {
//                           buff[k] =   SampBuf2_Start[0][index]+NF_SampOffset;//电网电压A
//                           buff[k+1] = SampBuf2_Start[1][index]+NF_SampOffset;//电网电压B
//                           buff[k+2] = SampBuf2_Start[2][index]+NF_SampOffset;//电网电压C
//                           buff[k+3] = SampBuf2_Start[3][index]+NF_SampOffset;//逆变电压A
//                           buff[k+4] = SampBuf2_Start[4][index]+NF_SampOffset;//逆变电压B
//                           buff[k+5] = SampBuf2_Start[5][index]+NF_SampOffset;//逆变电压C
//                           buff[k+6] = SampBuf2_Start[6][index]+NF_SampOffset;//模块电流A
//                           buff[k+7] = SampBuf2_Start[7][index]+NF_SampOffset;//模块电流B
//                           buff[k+8] = SampBuf2_Start[8][index]+NF_SampOffset;//模块电流C
//                           buff[k+9] = SampBuf2_Start[9][index]+NF_SampOffset;//系统电流A
//                           buff[k+10] = SampBuf2_Start[10][index]+NF_SampOffset;//系统电流B
//                           buff[k+11] = SampBuf2_Start[11][index]+NF_SampOffset;//系统电流C
//                           buff[k+12] = SampBuf2_Start[12][index]+NF_SampOffset;//母线电压
                       }
#endif

                       if(++index >= SAMP_NUM)
                          index = 0;
                       NF_Data.Index = index;
                    }

                     //保存数据
                     k = NF_Data.BlkID;//块号
                     i = NF_Data.Count;
                     NF_WritePage(k,i,buff);

                     //录波波形保存完后，再保存录波参数
                     if(++NF_Data.Count >= NF_PAGE_NUM)
                     {
                         NF_Data.Count = 0;
                         NF_Data.BlkCnt++;
                         NF_Data.BlkID++;
         //                NF_Data.Step = 1;
                     }

                     if((NF_Data.BlkCnt*NF_PAGE_NUM+NF_Data.Count) >= NF_Data.SectNum)
                     {
                         NF_WP_DIS = 1;
                         NF_Data.Step = 0;
                         NF_Data.OpNum = NF_Write_Recd;
//                         NF_Data.NowRdEn = 1;//写RAM开始位
                         //add
#ifdef EXRAM_512K
                         if(NF_Data.ReadNowcache)
#endif
                         {
                             NF_Data.NowRdEn = 1;//写完后使能RAM1存数据
                         }
#ifdef EXRAM_512K
                         else
                         {
                             NF_Data.NowRdEn2 = 1;//写完后使能RAM2存数据
                         }//add end
#endif
                         NF_Data.WEn = 0;
                     }
                }

                if((NF_Data.FltWEn==1)&&(NF_Data.Type==RD_Fault))
                {
                    for(i=0; i<NF_Data.SampNum; i++)//缓存一页
                    {
                       //故障保存缓存数据
                       index = NF_Data.FltIndex;
                       k = i*NF_SampTypeNum;
//#ifdef EXRAM_512K
                       if(NF_Data.ReadFltcache)//如果故障次数是1的倍数从故障缓存1读数据
//#endif
                       //read ram cache add
                       {
                           buff[k] = SampBuf[0][index]+NF_SampOffset;
                           buff[k+1] = SampBuf[1][index]+NF_SampOffset;//NF_Data.BlkID;//
                           buff[k+2] = SampBuf[2][index]+NF_SampOffset;//NF_Data.Count;//
                           buff[k+3] = SampBuf[3][index]+NF_SampOffset;
                           buff[k+4] = SampBuf[4][index]+NF_SampOffset;
                           buff[k+5] = SampBuf[5][index]+NF_SampOffset;
                           buff[k+6] = SampBuf[6][index]+NF_SampOffset;
                           buff[k+7] = SampBuf[7][index]+NF_SampOffset;
                           buff[k+8] = SampBuf[8][index]+NF_SampOffset;
                           buff[k+9] = SampBuf[9][index]+NF_SampOffset;
                           buff[k+10] = SampBuf[10][index]+NF_SampOffset;
                           buff[k+11] = SampBuf[11][index]+NF_SampOffset;
                           buff[k+12] = SampBuf[12][index]+NF_SampOffset;
                           buff[k+13] = SampBuf[13][index]+NF_SampOffset;
                           testk = k;
                       }
//#ifdef EXRAM_512Kb
                       else//如果故障次数是2的倍数从故障缓存2读数据
                       {
                           buff[k] = SampBuf2[0][index]+NF_SampOffset;
                           buff[k+1] = SampBuf2[1][index]+NF_SampOffset;//NF_Data.BlkID;//
                           buff[k+2] = SampBuf2[2][index]+NF_SampOffset;//NF_Data.Count;//
                           buff[k+3] = SampBuf2[3][index]+NF_SampOffset;
                           buff[k+4] = SampBuf2[4][index]+NF_SampOffset;
                           buff[k+5] = SampBuf2[5][index]+NF_SampOffset;
                           buff[k+6] = SampBuf2[6][index]+NF_SampOffset;
                           buff[k+7] = SampBuf2[7][index]+NF_SampOffset;
                           buff[k+8] = SampBuf2[8][index]+NF_SampOffset;
                           buff[k+9] = SampBuf2[9][index]+NF_SampOffset;
                           buff[k+10] = SampBuf2[10][index]+NF_SampOffset;
                           buff[k+11] = SampBuf2[11][index]+NF_SampOffset;
                           buff[k+12] = SampBuf2[12][index]+NF_SampOffset;
                           buff[k+13] = SampBuf2[13][index]+NF_SampOffset;
                           testk = k;
                       }
//#endif


                       if(++index >= SAMP_NUM_FLT)
//                       if(++index >=  NF_Data.FltIndex)
                          index = 0;
                       NF_Data.FltIndex = index;
                    }

                     k = NF_Data.BlkID;
                     i = NF_Data.Count;
                     NF_WritePage(k,i,buff);

                     //录波波形保存完后，再保存录波参数
                     if(++NF_Data.Count >= NF_PAGE_NUM)
                     {
                         NF_Data.Count = 0;
                         NF_Data.BlkCnt++;
                         NF_Data.BlkID++;
         //                NF_Data.Step = 1;
                     }

                     if((NF_Data.BlkCnt*NF_PAGE_NUM+NF_Data.Count) >= NF_Data.SectNum)
                     {
                         NF_WP_DIS = 1;
                         NF_Data.Step = 0;
                         NF_Data.OpNum = NF_Write_Recd;
//                         NF_Data.FltRdEn = 1;//写完后使能RAM1存数据 delete
                         //add
                         if(NF_Data.ReadFltcache)
                         {
                             NF_Data.FltRdEn = 1;//写完后使能RAM1存数据
                         }
                         else
                         {
                             NF_Data.FltRdEn2 = 1;//写完后使能RAM2存数据
                         }//add end
                         NF_Data.FltWEn = 0;//写完清空写flash位
                     }
                }
            }
        }

        break;
        //写录波参数数据
        case NF_Write_Recd:
        {
     /*       if(RunData.StateMachine.MswReg.bits.Compenflag_flash>0)   //跌落标志位让程序0
            {
                k = RD_Abnor - 1;
                i = (NF_Data.Para[k][0]-1)%NF_GroupNum*NF_TypeParaNum;

                NF_Data.Para[k][i+7] = RunData.StateMachine.MswReg.bits.Compenflag_flash; //跌落类型
                NF_Data.Para[k][i+8] = RunData.t_gridabnormal*0.2; //单位：0.01s
                NF_Data.Step = 0;
                RunData.StateMachine.MswReg.bits.Compenflag_flash=0;
            }*/

            if(NF_Data.Step==0)
            {
                k = NF_Data.Type-1;
                NF_Data.BlkID = NF_RecdBlkID+k*NF_TypeBlkNumP;
                NF_Data.BlkLmt = NF_RecdBlkID+(k+1)*NF_TypeBlkNumP;
                NF_Data.Step = 1;
            }
            else if(NF_Data.Step==1)
            {
                NF_WP_EN = 1;
                k = NF_Data.BlkID;
                //在NF_RecdBlkID~NF_WaveBlkID block间写录波参数数据
                NF_EraseBlock(NF_Data.BlkID);

                 NF_Data.Step = 2;

            }
            else if(NF_Data.Step==2)
            {
                k = NF_Data.Type-1;
                p = &NF_Data.Para[k][0];
                //保存前缓存参数
                for(i=0; i<NF_DataParaNum; i++)//循环341次
                {
                    buff[i] = *p++;
                }

                //在NF_RecdBlkID~NF_WaveBlkID block间写录波参数数据
                if(NF_WritePage(NF_Data.BlkID,0,buff))
                {
                    NF_Data.BlkID++;
                    NF_Data.Step = 1;
                }
                else
                    NF_Data.Step = 3;
            }
            else
            {
                NF_WP_DIS = 1;
                NF_Data.OpNum = 0;
            }
        }

        break;
        //3
        case NF_Write_AbnRms:
        {
            if(NF_Data.Step==0)
            {
                NF_Data.SampNum = NF_SampNum_Rms;
                NF_Data.SectNum = NF_SectNum_Rms;
                NF_Data.BlkNum = NF_BlkNum_Rms;

                k = RD_AbnRms - 1;
                i = (NF_Data.Para[RD_Abnor-1][0]-1)%NF_GroupNum;//扰动次数
                NF_Data.BlkID = NF_WaveBlkID+k*NF_TypeBlkNumR+i*NF_Data.BlkNum;
                NF_Data.BlkLmt = NF_WaveBlkID+(k+1)*NF_TypeBlkNumR;

                NF_Data.BlkCnt = 0;
                NF_Data.Count = 0;
                NF_Data.Step = 1;
            }
            else if(NF_Data.Step==1)
            {
                NF_WP_EN = 1;
                k = NF_Data.BlkID;
                //在NF_ParaBlkID~NF_RecdBlkID block间写液晶屏参数数据
                NF_EraseBlock(NF_Data.BlkID);
                NF_Data.Step = 2;

            }
            else if(NF_Data.Step==2)
            {
                for(i=0; i<NF_Data.SampNum; i++)
                {
                    //保存亲缓存有效值数据
                    index = NF_Data.RmsIdx;
                    k = i*NF_SampTypeNum;
                    //read ram cache add
                    {
                        buff[k]   = AbnRms[0][index]+NF_SampOffset;
                        buff[k+1] = AbnRms[1][index]+NF_SampOffset;
                        buff[k+2] = AbnRms[2][index]+NF_SampOffset;
                        buff[k+3] = AbnRms[3][index]+NF_SampOffset;
                        buff[k+4] = AbnRms[4][index]+NF_SampOffset;
                        buff[k+5] = AbnRms[5][index]+NF_SampOffset;
                    }
//                    else
//                    {
//                        buff[k]   = NF_Data.AbnRms2[0][index]+NF_SampOffset;
//                        buff[k+1] = NF_Data.AbnRms2[1][index]+NF_SampOffset;
//                        buff[k+2] = NF_Data.AbnRms2[2][index]+NF_SampOffset;
//                        buff[k+3] = NF_Data.AbnRms2[3][index]+NF_SampOffset;
//                        buff[k+4] = NF_Data.AbnRms2[4][index]+NF_SampOffset;
//                        buff[k+5] = NF_Data.AbnRms2[5][index]+NF_SampOffset;
//                    }


                    if(++index >= NF_DataNum_Rms)
                        index = 0;
                    NF_Data.RmsIdx = index;
                }

                k = NF_Data.BlkID;
                i = NF_Data.Count;
                NF_WritePage(k,i,buff);
                NF_Data.Count++;

         /*       if(++NF_Data.Count >= NF_PAGE_NUM)
                {
                    NF_Data.Count = 0;
                    NF_Data.BlkCnt++;
            //        NF_Data.BlkID++;
                    NF_Data.Step = 1;
                }*/
                if (NF_Data.Count >= NF_Data.SectNum)
           //     if((NF_Data.BlkCnt*NF_PAGE_NUM+NF_Data.Count) >= NF_Data.SectNum)
                {
                    NF_WP_DIS = 1;
                    NF_Data.Count = 0;
                    NF_Data.RmsRdEn = 1;
                    NF_Data.OpNum = 0;
                    RecordData.Flag_Rd =1;
                }
            }
        }

        break;
        //5写液晶屏设置参数
        case NF_Write_Para:
        {
            if(NF_Data.Step==0)
            {
                NF_Data.BlkID = NF_ParaBlkID;
                NF_Data.BlkLmt = NF_RecdBlkID;
                NF_Data.Step = 1;
            }
            NF_WP_EN =1;

            NF_EraseBlock(1);
            NF_EraseBlock(2);
   //         DELAY_US(10000L);
            buf_i ++;
            if(buf_i==20)
            {
                buf_i = 1;
            }
               for(i=0; i<NF_BYTE_NUM; i++)
                {
                    buff[i] = buf_i*(i+1);
                }

                NF_WritePage(1,2,buff);
                NF_WritePage(2,0,buff);
         //     NF_WritePage(1,4,buff);
                NF_WP_DIS = 1;
                NF_Data.OpNum = NF_Read_Para;
        }

        break;
        //读液晶屏设置和录波参数
        case NF_Read_Para:
        {
     //       NF_ReadPage(1,2,buff);
      //      NF_ReadPage(2,0,buff);
            NF_ReadPage(NF_RecdBlkID,0,buff);
            if(buff[0]!=0xFFFF)//已经初始化，则覆盖DSP录波参数数据
            {
                p = &NF_Data.Para[0][0];

                for(i=0; i<NF_DataParaNum; i++)
                {
                    *p++ = buff[i];
                }
            }

            //在NF_RecdBlkID~NF_WaveBlkID block间读NF录波参数

            NF_ReadPage(NF_RecdBlkID+NF_TypeBlkNumP,0,buff);

            if(buff[0]!=0xFFFF)//已经初始化，则覆盖DSP录波参数数据
            {
                p = &NF_Data.Para[1][0];

                for(i=0; i<NF_DataParaNum; i++)
                {
                    *p++ = buff[i];
                }
            }

            NF_Data.OpNum = 0;
        }


        break;
        //7
        case NF_Init_Recd:
        {
            if(NF_Data.Step==0)
            {
                if(NF_Data.InitStep==0)
                    NF_Data.Type = RD_Fault;
                else if(NF_Data.InitStep==1)
                    NF_Data.Type = RD_Abnor;

                k = NF_Data.Type-1;
                NF_Data.BlkID = NF_RecdBlkID+k*NF_TypeBlkNumP;
                NF_Data.BlkLmt = NF_RecdBlkID+(k+1)*NF_TypeBlkNumP;
                NF_Data.Step = 1;
            }
            else if(NF_Data.Step==1)
            {
                NF_WP_EN = 1;
                k = NF_Data.BlkID;
                //在NF_RecdBlkID~NF_WaveBlkID block间写录波参数数据
                for(i=k; i<NF_Data.BlkLmt; i++)
                {
                    if(NF_EraseBlock(i))
                        continue;
                    else
                        break;
                }

                //超范围，则报故障
                if(i>=NF_Data.BlkLmt)
                {
                    NF_WP_DIS = 1;
                    NF_Data.Fault = 1;
                    NF_Data.OpNum = 0;
                }
                else
                {
                    NF_Data.BlkID = i;
                    NF_Data.Step = 2;
                }
            }
            else if(NF_Data.Step==2)
            {
                k = NF_Data.Type-1;
                p = &NF_Data.Para[k][0];

                for(i=0; i<NF_DataParaNum; i++)
                {
                    buff[i] = *p++;
                }

                //在NF_RecdBlkID~NF_WaveBlkID block间写录波参数数据
                if(NF_WritePage(NF_Data.BlkID,0,buff))
                {
                    NF_Data.BlkID++;
                    NF_Data.Step = 1;
                }
                else if(NF_Data.InitStep==0)
                {
                    NF_Data.InitStep = 1;
                    NF_Data.Step = 0;
                }
                else
                    NF_Data.Step = 3;
            }
            else
            {
                NF_WP_DIS = 1;
                NF_Data.InitStep = 0;
                NF_Data.Step = 0;
                RunData.ModbusData[e_NF_Cmd] = 0;
                NF_Data.OpNum = 0;
            }
        }

        break;
    }
}


//==========================//
//函数名:RecordCtrl()
//描述:录波控制，发送给modbus
//输入:
//输出:
//==========================//
void RecordCtrl(void)
{
    Uint16 i,k;
    RecordData.Type = RunData.ModbusData1[0];    //波形操作类型  跌落还是故障
    RecordData.Numb = RunData.ModbusData1[1]; //每条类型有20条,读第几条

    if(RecordData.Type==RD_InitNF)
    {
        NF_Data.Para[0][0] = 0;
        NF_Data.Para[1][0] = 0;
        NF_Data.OpNum = NF_Init_Recd;//NF操作码初始化flash
    }
    else if((RecordData.Type>0)
          &&(RecordData.Type<RD_InitNF)
          &&(RecordData.Numb>0)
          &&(RunData.ModbusData1[2]>0)
          &&((RecordData.Flag_Rd)||(RecordData.Type==RD_Fault)||(RunData.StateMachine.MswReg.bits.Wave_RdOn)))//RX读取的点位大于零
    {
        if(RecordData.TxEn==1)
        {
            if(RecordData.Type==RD_Fault)//如果是读故障类型
            {
                for(i=0;i<50;i++)
                {
                    //发送波形数据
                    k = (RecordData.Index%RecordData.SampNum+i)*NF_SampTypeNum;
                    RunData.ModbusData1[20+14*i] = RecordData.Buff[k];
                    RunData.ModbusData1[20+14*i+1] = RecordData.Buff[k+1];
                    RunData.ModbusData1[20+14*i+2] = RecordData.Buff[k+2];
                    RunData.ModbusData1[20+14*i+3] = RecordData.Buff[k+3];
                    RunData.ModbusData1[20+14*i+4] = RecordData.Buff[k+4];
                    RunData.ModbusData1[20+14*i+5] = RecordData.Buff[k+5];
                    RunData.ModbusData1[20+14*i+6] = RecordData.Buff[k+6];
                    RunData.ModbusData1[20+14*i+7] = RecordData.Buff[k+7];
                    RunData.ModbusData1[20+14*i+8] = RecordData.Buff[k+8];
                    RunData.ModbusData1[20+14*i+9] = RecordData.Buff[k+9];
                    RunData.ModbusData1[20+14*i+10] = RecordData.Buff[k+10];
                    RunData.ModbusData1[20+14*i+11] = RecordData.Buff[k+11];
                    RunData.ModbusData1[20+14*i+12] = RecordData.Buff[k+12];
                    RunData.ModbusData1[20+14*i+13] = RecordData.Buff[k+13];
                    //add
                    if(RecordData.Type == RD_Abnor)
                    {
                        break;//如果此时读扰动退出读故障
                    }//add end
                }

                k = RD_Fault-1;
            }
            else if(RecordData.Type==RD_Abnor)
            {
                for(i=0;i<50;i++)
                {
                    k = (RecordData.Index%RecordData.SampNum+i)*NF_SampTypeNum;
                    RunData.ModbusData1[20+14*i]   = RecordData.Buff[k];
                    RunData.ModbusData1[20+14*i+1] = RecordData.Buff[k+1];
                    RunData.ModbusData1[20+14*i+2] = RecordData.Buff[k+2];
                    RunData.ModbusData1[20+14*i+3] = RecordData.Buff[k+3];
                    RunData.ModbusData1[20+14*i+4] = RecordData.Buff[k+4];
                    RunData.ModbusData1[20+14*i+5] = RecordData.Buff[k+5];
                    RunData.ModbusData1[20+14*i+6] = RecordData.Buff[k+6];
                    RunData.ModbusData1[20+14*i+7] = RecordData.Buff[k+7];
                    RunData.ModbusData1[20+14*i+8] = RecordData.Buff[k+8];
                    RunData.ModbusData1[20+14*i+9] = RecordData.Buff[k+9];
                    RunData.ModbusData1[20+14*i+10] = RecordData.Buff[k+10];
                    RunData.ModbusData1[20+14*i+11] = RecordData.Buff[k+11];
                    RunData.ModbusData1[20+14*i+12] = RecordData.Buff[k+12];
                    RunData.ModbusData1[20+14*i+13] = RecordData.Buff[k+13];
                }

                k = RD_Abnor-1;
            }
            else if(RecordData.Type==RD_AbnRms)
            {
                for(i=0;i<50;i++)
                {
                    k = (RecordData.Index%RecordData.SampNum+i)*NF_SampTypeNum;
                    RunData.ModbusData1[20+6*i] = RecordData.Buff[k];
                    RunData.ModbusData1[20+6*i+1] = RecordData.Buff[k+1];
                    RunData.ModbusData1[20+6*i+2] = RecordData.Buff[k+2];
                    RunData.ModbusData1[20+6*i+3] = RecordData.Buff[k+3];
                    RunData.ModbusData1[20+6*i+4] = RecordData.Buff[k+4];
                    RunData.ModbusData1[20+6*i+5] = RecordData.Buff[k+5];
                }

                k = RD_Abnor-1;
            }
//            RunData.ModbusData[3] = RecordData.OldIdx+1;//扰动波形记录标志位+1
            RunData.ModbusData1[3] = RecordData.Index+1;//TX扰动波形记录波形读取标志位

            i = ((RecordData.Numb-1)%NF_GroupNum)*NF_TypeParaNum;//去掉减1试试
            RunData.ModbusData1[e_Year_R] = NF_Data.Para[k][i+1];
            RunData.ModbusData1[e_Month_R] = NF_Data.Para[k][i+2];
            RunData.ModbusData1[e_Day_R] = NF_Data.Para[k][i+3];
            RunData.ModbusData1[e_Hour_R] = NF_Data.Para[k][i+4];
            RunData.ModbusData1[e_Minute_R] = NF_Data.Para[k][i+5];
            RunData.ModbusData1[e_Second_R] = NF_Data.Para[k][i+6];

           if(RecordData.Type==RD_Fault)
            {
                RunData.ModbusData1[e_McwReg_R] = NF_Data.Para[k][i+7];
                RunData.ModbusData1[e_MswReg_R] = NF_Data.Para[k][i+9];
                RunData.ModbusData1[e_Status0_R] = NF_Data.Para[k][i+10];
                RunData.ModbusData1[e_Status1_R] = NF_Data.Para[k][i+11];
                RunData.ModbusData1[e_Status2_R] = NF_Data.Para[k][i+12];
                RunData.ModbusData1[e_Fault0_R] = NF_Data.Para[k][i+13];
                RunData.ModbusData1[e_Fault1_R] = NF_Data.Para[k][i+14];
                RunData.ModbusData1[e_Fault2_R] = NF_Data.Para[k][i+15];
                RunData.ModbusData1[e_Fault3_R] = NF_Data.Para[k][i+16];
                RunData.ModbusData1[e_Fault4_R] = NF_Data.Para[k][i+17];
            }

            RecordData.Index =  RunData.ModbusData1[2]-1;  //RX波形读取点
            if((RecordData.Index>RecordData.OldIdx)
            && (RecordData.OpDelay >= 1000))// &&((RecordData.Index%RecordData.SampNum)==0))
            {
                RecordData.OpDelay = 0;
                RecordData.OldIdx = RecordData.Index;
                if((RecordData.Index%RecordData.SampNum)==0)
                    RecordData.TxEn = 0;
            }
        }
        if(NF_Data.OpNum==0)
            RecordData.OpDelay++;
        else
            RecordData.OpDelay = 0;

        if((RecordData.OpNum==0)&&(RecordData.OpDelay>=1500))//1000 change 1500
        {
            RecordData.OpDelay = 0;
            RecordData.OpNum = NF_Read_Wave;
        }
    }
    else if(RunData.ModbusData1[2]==0)//波形读取点为0
    {
        RecordData.OpDelay = 0;
        RecordData.TxEn = 0;
        RecordData.Step = 0;
        RecordData.Index = 0;
        RecordData.OldIdx = 0;
        RecordData.OpNum = 0;
    }

    //读Flash波形
    if((RecordData.OpNum==NF_Read_Wave) && (NF_Data.OpNum==0))//RunData.ModbusData1[2]
    {
        if(RecordData.Step==0)
        {
            //add
//            RecordData.Numb = RunData.ModbusData1[1]; //每条类型有20条,读第几条
            //获取所读数据block号
            if(RecordData.Type==RD_Fault)
            {
                RecordData.SampNum = NF_SampNum_Flt;//每页能够保存的最多采样个数
                RecordData.SectNum = NF_SectNum_Flt;//每段保存的数据页数
                RecordData.BlkNum = NF_BlkNum_Flt;//块数
            }
            else if(RecordData.Type==RD_Abnor)
            {
                RecordData.SampNum = NF_SampNum_Abn;
                RecordData.SectNum = NF_SectNum_Abn;
                RecordData.BlkNum = NF_BlkNum_Abn;
            }
            else if(RecordData.Type==RD_AbnRms)
            {
                RecordData.SampNum = NF_SampNum_Rms;
                RecordData.SectNum = NF_SectNum_Rms;
                RecordData.BlkNum = NF_BlkNum_Rms;
            }

            k = RecordData.Type-1;//计算读取类型
            i = (RecordData.Numb-1)%NF_GroupNum;//i = (RecordData.Numb-1)%NF_GroupNum;组数
            RecordData.BlkID = NF_WaveBlkID+k*NF_TypeBlkNumR+i*RecordData.BlkNum;
            RecordData.BlkLmt = NF_WaveBlkID+(k+1)*NF_TypeBlkNumR;

            RecordData.BlkCnt = 0;
            RecordData.OldIdx = 0;
            RecordData.Step = 1;
        }
        else if(RecordData.Step==1)
        {
//            //在NF_WaveBlkID~NF_BLOCK_NUM block间读NF液晶屏参数数据
//
//            RecordData.Count = 0;
//            RecordData.Step = 2;
            //在NF_WaveBlkID~NF_BLOCK_NUM block间读NF液晶屏参数数据
            k = RecordData.BlkID;
            for(i=k; i<RecordData.BlkLmt; i++)
            {
                if(NF_IsBadBlock(i))
                    continue;
                else
                    break;
            }

            if(i>=RecordData.BlkLmt) //超范围，则报故障，并终止读取
            {
                NF_Data.Fault = 1;
                RecordData.OpNum = 0;
                RunData.ModbusData[0] = 0;
            }
            else //正常，进入下一步
            {
                RecordData.BlkID = i;
                RecordData.Count = 0;
                RecordData.Step = 2;
            }
        }
        else if(RecordData.Step==2)
        {
            //缓存数据没有传输完成，则返回
            if(RecordData.TxEn!=0)
                return;//detele

            //获取所读数据block号
            k = RecordData.BlkID;
            i = RecordData.Count;
            NF_ReadPage(k,i,buff);

            //更新相应缓存数据，并使能传输
            for(i=0; i<NF_BYTE_NUM; i++)
                RecordData.Buff[i] = buff[i]-NF_SampOffset;

            RecordData.TxEn = 1;//缓存完可以发送

            //一组录波读完
            if(++RecordData.Count >= NF_PAGE_NUM)
            {
                RecordData.Count = 0;
                RecordData.BlkCnt++;
                RecordData.BlkID++;
                RecordData.Step = 1;
            }
            //块数计数*64+页计数>=20
            if((RecordData.BlkCnt*NF_PAGE_NUM+RecordData.Count) >= (RecordData.SectNum))//change
            {
                RecordData.Step = 0;
                RecordData.Index = 0;
                RecordData.OldIdx = 0;
                RecordData.OpNum = 0;//detele
//                RecordData.TxEn = 0;//detele
//                RecordData.Count = 0;//detele
       //         RecordData.Flag_Rd =0;

            }
        }
    }
//    }//add
}

