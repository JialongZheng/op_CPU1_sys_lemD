/*
 * RtcDS1302.h
 *
 *  Created on: 2019-5-26
 *      Author: JCH
 */

#ifndef HEADER_RTCDS1302_H_
#define HEADER_RTCDS1302_H_


#define DS1302_IO      GpioDataRegs.GPADAT.bit.GPIO30   //数据输入输出脚
#define DS1302_CK      GpioDataRegs.GPADAT.bit.GPIO29   //时钟引脚
#define DS1302_CE      GpioDataRegs.GPADAT.bit.GPIO23   //使能管脚
#define DS1302_READ    EALLOW; GpioCtrlRegs.GPADIR.bit.GPIO30=0; EDIS
#define DS1302_WRITE   EALLOW; GpioCtrlRegs.GPADIR.bit.GPIO30=1; EDIS

typedef enum
{
    Rtc_Second,
    Rtc_Minute,
    Rtc_Hour,
    Rtc_Day,
    Rtc_Month,
    Rtc_Week,
    Rtc_Year,
    Rtc_WtEn,

    Rtc_DataNum

}RTCData_Tab;

typedef struct
{
    Uint16 SetEn;
    Uint16 CurTime[Rtc_DataNum];
    Uint16 SetTime[Rtc_DataNum];
    Uint8 Buf[Rtc_DataNum];
}RTC_DATA;

extern void RtcInit(void);
extern void RtcProcess(void);
static void StartClock(void);
static void DS1302_GetTime(Uint8 *pTM);
static void DS1302_SetTime(Uint8 *pTM);
static Uint8 DS1302_Read(Uint8 cmd);
static void DS1302_Write(Uint8 cmd,Uint8 data);
static Uint8 DS1302_ReadByte(void);
static void DS1302_WriteByte(Uint8 data);

extern RTC_DATA Rtc_Data;

#endif /* HEADER_RTCDS1302_H_ */
