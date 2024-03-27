/*
 * RtcDS1302.c
 *
 *  Created on: 2019-5-26
 *      Author: JCH
 */
#include "F2837xD_Device.h"
#include "F2837xD_Examples.h"
#include "Global_struct.h"
#include "RtcDS1302.h"
#include "NandFlash.h"

//#pragma CODE_SECTION(RtcProcess, "ramfuncs");
//#pragma CODE_SECTION(DS1302_GetTime, "ramfuncs");
//#pragma CODE_SECTION(DS1302_SetTime, "ramfuncs");
//#pragma CODE_SECTION(DS1302_Read, "ramfuncs");
//#pragma CODE_SECTION(DS1302_Write, "ramfuncs");
//#pragma CODE_SECTION(DS1302_ReadByte, "ramfuncs");
//#pragma CODE_SECTION(DS1302_WriteByte, "ramfuncs");

RTC_DATA Rtc_Data;


//==========================//
//������:RtcInit()
//����:
//����:
//���:
//==========================//
void RtcInit(void)
{
    Uint16 i;

    for(i=0;i<Rtc_DataNum;i++)
    {
        Rtc_Data.Buf[i] = 0;
        Rtc_Data.CurTime[i] = 0;
        Rtc_Data.SetTime[i] = 0;
    }

    StartClock();

    Rtc_Data.SetEn = 0;
}

//==========================//
//������:RtcProcess()
//����:
//����:
//���:
//==========================//
void RtcProcess(void)
{
    if((RunData.ModbusData[e_NF_Cmd]==1))
    {
        Rtc_Data.Buf[Rtc_Second] = Rtc_Data.SetTime[Rtc_Second]/10*16 + Rtc_Data.SetTime[Rtc_Second]%10;
        Rtc_Data.Buf[Rtc_Minute] = Rtc_Data.SetTime[Rtc_Minute]/10*16 + Rtc_Data.SetTime[Rtc_Minute]%10;
        Rtc_Data.Buf[Rtc_Hour]   = Rtc_Data.SetTime[Rtc_Hour]/10*16 + Rtc_Data.SetTime[Rtc_Hour]%10;
        Rtc_Data.Buf[Rtc_Day]    = Rtc_Data.SetTime[Rtc_Day]/10*16 + Rtc_Data.SetTime[Rtc_Day]%10;
        Rtc_Data.Buf[Rtc_Month]  = Rtc_Data.SetTime[Rtc_Month]/10*16 + Rtc_Data.SetTime[Rtc_Month]%10;
        Rtc_Data.Buf[Rtc_Week]   = Rtc_Data.SetTime[Rtc_Week]/10*16 + Rtc_Data.SetTime[Rtc_Week]%10;
        Rtc_Data.Buf[Rtc_Year]   = (Rtc_Data.SetTime[Rtc_Year]-2000)/10*16 + (Rtc_Data.SetTime[Rtc_Year]-2000)%10;
        Rtc_Data.Buf[Rtc_WtEn]   = 0x80; //��д����

        DS1302_SetTime(Rtc_Data.Buf);
        RunData.ModbusData[e_NF_Cmd] = 0;
    }
    else
    {
        DS1302_GetTime(Rtc_Data.Buf);

        Rtc_Data.CurTime[Rtc_Second] = (((Rtc_Data.Buf[Rtc_Second]&0x7F)>>4) & 0x0F)*10 + (Rtc_Data.Buf[Rtc_Second] & 0x0F);
        Rtc_Data.CurTime[Rtc_Minute] = (((Rtc_Data.Buf[Rtc_Minute]&0x7F)>>4) & 0x0F)*10 + (Rtc_Data.Buf[Rtc_Minute] & 0x0F);
        Rtc_Data.CurTime[Rtc_Hour]   = (((Rtc_Data.Buf[Rtc_Hour]&0x3F)>>4) & 0x0F)*10 + (Rtc_Data.Buf[Rtc_Hour] & 0x0F);
        Rtc_Data.CurTime[Rtc_Day]    = (((Rtc_Data.Buf[Rtc_Day]&0x3F)>>4) & 0x0F)*10 + (Rtc_Data.Buf[Rtc_Day] & 0x0F);
        Rtc_Data.CurTime[Rtc_Month]  = (((Rtc_Data.Buf[Rtc_Month]&0x1F)>>4) & 0x0F)*10 + (Rtc_Data.Buf[Rtc_Month] & 0x0F);
        Rtc_Data.CurTime[Rtc_Week]   = Rtc_Data.Buf[Rtc_Week] & 0x07;
        Rtc_Data.CurTime[Rtc_Year]   = 2000 + ((Rtc_Data.Buf[Rtc_Year]>>4) & 0x0F)*10 + (Rtc_Data.Buf[Rtc_Year] & 0x0F);
    }

  //  Rtc_Data.SetEn = RecordData.Type;
}

//==========================//
//������:StartClock()
//����:
//����:
//���:
//==========================//
static void StartClock(void)
{
    Uint8 val;

    val = DS1302_Read(0x81);  //��������
    val =(val&0x7F);
    DS1302_Write(0x8E,0x00);  //�ر�д����
    DS1302_Write(0x80,val);   //�򿪾���
    DS1302_Write(0x90,0xA5);  //�򿪳�������
    DS1302_Write(0x8E,0x80);  //��д����
}

//==========================//
//������:DS1302_GetTime()
//����:
//����:
//���:
//==========================//
static void DS1302_GetTime(Uint8 *pTM)
{
    Uint8 i;

    DS1302_CE = 0;
    DELAY_US(1);
    DS1302_CK = 0;
    DELAY_US(1);
    DS1302_CE = 1;
    DELAY_US(5);

    DS1302_WriteByte(0xBF);        //�����ֽ�
    for(i=0;i<8;i++)
    {
        *pTM = DS1302_ReadByte();  //����8Byte����
        pTM++;
    }

    DS1302_CK = 1;
    DELAY_US(1);
    DS1302_CE =0;
    DELAY_US(1);
}

//==========================//
//������:DS1302_SetTime()
//����:
//����:
//���:
//==========================//
static void DS1302_SetTime(Uint8 *pTM)
{
    Uint8 i;

    DS1302_Write(0x8E,0x00);     //�ر�д����

    DS1302_CE = 0;
    DELAY_US(1);
    DS1302_CK = 0;
    DELAY_US(1);
    DS1302_CE = 1;
    DELAY_US(5);

    DS1302_WriteByte(0xBE);      //д���ֽ�
    for(i=0;i<8;i++)
    {
        DS1302_WriteByte(*pTM);  //д��8Byte����
        pTM++;
    }

    DS1302_CK =1;
    DELAY_US(1);
    DS1302_CE =0 ;
    DELAY_US(1);

    DS1302_Write(0x8e,0x80);     //��д����
}

//==========================//
//������:DS1302_Read()
//����:
//����:
//���:
//==========================//
static Uint8 DS1302_Read(Uint8 cmd)
{
    Uint8 data;

    DS1302_CE = 0;
    DELAY_US(1);
    DS1302_CK = 0;
    DELAY_US(1);
    DS1302_CE = 1;
    DELAY_US(5);

    DS1302_WriteByte(cmd);
    data = DS1302_ReadByte();
    DELAY_US(1);
    DS1302_CE = 0;

    return data;
}

//==========================//
//������:DS1302_Write()
//����:
//����:
//���:
//==========================//
static void DS1302_Write(Uint8 cmd,Uint8 data)
{
    DS1302_CE = 0;
    DELAY_US(1);
    DS1302_CK = 0;
    DELAY_US(1);
    DS1302_CE = 1;
    DELAY_US(5);

    DS1302_WriteByte(cmd);
    DS1302_WriteByte(data);
    DS1302_CK = 1;
    DELAY_US(1);
    DS1302_CE =0;
    DELAY_US(5);
}

//==========================//
//������:DS1302_ReadByte()
//����:
//����:
//���:
//==========================//
static Uint8 DS1302_ReadByte(void)
{
    Uint8 i,rxBuf=0,data=0;

    DS1302_READ;

    for(i=0;i<8;i++)
    {
        data = DS1302_IO;
        DELAY_US(1);
        DS1302_CK = 1;
        DELAY_US(2);
        DS1302_CK = 0;
        DELAY_US(2);
        rxBuf += data<<i;
    }

    return rxBuf;
}

//==========================//
//������:DS1302_WriteByte()
//����:
//����:
//���:
//==========================//
static void DS1302_WriteByte(Uint8 data)
{
    Uint8 i;

    DS1302_WRITE;

    for(i=0;i<8;i++)
    {
        DS1302_IO = data&0x01;
        DELAY_US(1);
        DS1302_CK  = 1;
        DELAY_US(2);
        DS1302_CK  = 0;
        DELAY_US(2);
        data = data>>1;
    }
}

//===========================================================================
// No more.
//===========================================================================
