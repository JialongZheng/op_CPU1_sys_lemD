/*
 * NandFlash.c
 *
 *  Created on: 2019-3-10
 *      Author: JCH
 */
#include <string.h>
#include "F2837xD_Device.h"
#include "F2837xD_Examples.h"    // DSP2833x Examples Include File
#include "Global_struct.h"
//#include "Temperature.h"
#include "NandFlash.h"
#include "RtcDS1302.h"

//==========================//
//函数名:NF_ReadID()
//描述:读ID号
//输入:
//输出:
//==========================//
Uint32 NF_ReadID(void)
{
    Uint32 id=0;

    NF_CMD(0x9090);    //发送读ID命令
    NF_ADDR(0x0000);   //指定地址

    DELAY_US(12L);

    id = NF_RDDATA();     //厂商ID, 20H
    id <<= 16;
    id |= NF_RDDATA();    //设备ID, 76H

    return id;
}

//==========================//
//函数名:NF_ReadStatus()
//描述:读状态
//输入:
//输出:
//==========================//
Uint16 NF_ReadStatus(void)
{
    Uint16 i,status=0;

    NF_CMD(0x70); //发送读状态命令

    do
    {
        i++;


        if(status)
            break;
    }
    while(i<10000);

    return status;
}

//==========================//
//函数名:NF_IsBadBlock()
//描述:是否坏块
//输入:
//输出:
//==========================//
Uint16 NF_IsBadBlock(Uint16 block)
{
    Uint16 i,rtn=1;
 /*   Uint16 addr1,addr2,addr3,buff[NF_SPARE_NUM];
    Uint32 blkPage = block*NF_PAGE_NUM;

    addr1 = blkPage&0xff;
    addr1 |= addr1<<8;

    addr2 = (blkPage>>8)&0xff;
    addr2 |= addr2<<8;

    addr3 = (blkPage>>16)&0x01;
    addr3 |= addr3<<8;

    NF_CMD(0x5050);                //区域C
    NF_ADDR(0x0000);               //A0~A7 位(Column Address)
    NF_ADDR(addr1);                //A9-A16, (Page Address)
    NF_ADDR(addr2);                //A17-A24, (Page Address)
    NF_ADDR(addr3);                //A25, (Page Address)

    DELAY_US(12L);

    for(i=0;i<NF_SPARE_NUM;i++)
    {
        buff[i] = NF_RDDATA();    //读16个 字节
    }

    if(buff[5]==0xffff)           //非坏块
    {*/
        rtn = 0;
//    }

    return rtn;
}

//==========================//
//函数名:NF_MarkBadBlock()
//描述:标记坏块
//输入:
//输出:
//==========================//
Uint16 NF_MarkBadBlock(Uint16 block)
{
//    Uint16 i;
    Uint16 rtn=1;
    /*   Uint16 addr1,addr2,addr3,buff[NF_SPARE_NUM];
    Uint32 blkPage = block*NF_PAGE_NUM;

    addr1 = blkPage&0xff;
    addr1 |= addr1<<8;

    addr2 = (blkPage>>8)&0xff;
    addr2 |= addr2<<8;

    addr3 = (blkPage>>16)&0x01;
    addr3 |= addr3<<8;

    NF_CMD(0x5050);                //区域C
    NF_CMD(0x8080);                //写开始命令
    NF_ADDR(0x0000);               //A0~A7 位(Column Address)
    NF_ADDR(addr1);                //A9-A16, (Page Address)
    NF_ADDR(addr2);                //A17-A24, (Page Address)
    NF_ADDR(addr3);                //A25, (Page Address)

    buff[5] = 0x4444;              //第6个字节标记坏块

    for(i=0;i<NF_SPARE_NUM;i++)
    {
        NF_WRDATA(buff[i]);        //写16 字节到Spare area
    }

    NF_CMD(0x1010);      */          //写结束命令



    return rtn;
}

//==========================//
//函数名:NF_EraseBlock()
//描述:擦除块
//输入:
//输出:
//==========================//
Uint16 NF_EraseBlock(Uint16 block)
{
    Uint16 rtn=1;
    Uint16 addr1,addr2,addr3;
    Uint32 blkPage = block*NF_PAGE_NUM;

  //  if(NF_IsBadBlock(block))
  //      return rtn;

    addr1 = blkPage&0xff;
  //  addr1 |= addr1<<8;

    addr2 = (blkPage>>8)&0xff;
  //  addr2 |= addr2<<8;

    addr3 = (blkPage>>16)&0x01;
  //  addr3 |= addr3<<8;

    NF_CMD(0x60);                //设置擦除模式
    NF_ADDR(addr1);                //A9-A16, (Page Address), 基于块擦除
    NF_ADDR(addr2);                //A17-A24, (Page Address)
    NF_ADDR(addr3);                //A25, (Page Address)
    NF_CMD(0xd0);                //发送擦写命令, 开始擦写

    DELAY_US(3500);      //max 3ms
    rtn = 0;
    return rtn;
}

//==========================//
//函数名:NF_ReadPage()
//描述:读一页数据
//输入:
//输出:
//==========================//
Uint16 NF_ReadPage(Uint16 block,Uint16 page,Uint16 *buffer)
{
    Uint16 i,rtn=1,temp1,temp2;
    Uint16 *bufP = buffer;
    Uint16 addr1,addr2,addr3;
    Uint32 blkPage = (block*NF_PAGE_NUM)+page;

    addr1 = blkPage&0xff;
  //  addr1 |= addr1<<8;

    addr2 = (blkPage>>8)&0xff;
 //   addr2 |= addr2<<8;

    addr3 = (blkPage>>16)&0x01;
 //   addr3 |= addr3<<8;

    NF_CMD(0x00);                //读区域A
    NF_ADDR(0x00);               //A0~A7 位(Column Address)
    NF_ADDR(0x00);
    NF_ADDR(addr1);                //A9-A16, (Page Address)
    NF_ADDR(addr2);                //A17-A24, (Page Address)
    NF_ADDR(addr3);                //A25, (Page Address)
    NF_CMD(0x30);
    DELAY_US(26);        //max 25us

    for(i=0;i<NF_BYTE_NUM;i++)
    {
      temp1 =  NF_RDDATA();
      temp2 =  NF_RDDATA();
      *bufP++ = ((temp2&0xff)<<8)|(temp1&0xff);
    }

    rtn = 0;

    return rtn;
}

//==========================//
//函数名:NF_WritePage()
//描述:写一页数据
//输入:
//输出:
//==========================//
Uint16 NF_WritePage(Uint16 block,Uint16 page,Uint16 *buffer)
{
    Uint16 i,rtn=1;
    Uint16 addr1,addr2,addr3;
    Uint32 blkPage = (block*NF_PAGE_NUM)+page;

    addr1 = blkPage&0xff;
 //   addr1 |= addr1<<8;

    addr2 = (blkPage>>8)&0xff;
 //   addr2 |= addr2<<8;

    addr3 = (blkPage>>16)&0x01;
  //  addr3 |= addr3<<8;


    NF_CMD(0x80);                //写开始命令
    NF_ADDR(0x00);               //A0~A7 位(Column Address)
    NF_ADDR(0x00);
    NF_ADDR(addr1);                //A9-A16, (Page Address)
    NF_ADDR(addr2);                //A17-A24, (Page Address)
    NF_ADDR(addr3);                //A25, (Page Address)
    DELAY_US(2);
    for(i=0;i<NF_BYTE_NUM;i++)
    {
        NF_WRDATA(buffer[i]&0xff);
        NF_WRDATA((buffer[i]&0xff00)>>8);
    }
    NF_CMD(0x10);                //写结束命令

    DELAY_US(620);     //MAX 600us

    rtn = 0;
    return rtn;
}

//===========================================================================
// No more.
//===========================================================================

