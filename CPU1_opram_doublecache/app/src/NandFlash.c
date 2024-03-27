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
//������:NF_ReadID()
//����:��ID��
//����:
//���:
//==========================//
Uint32 NF_ReadID(void)
{
    Uint32 id=0;

    NF_CMD(0x9090);    //���Ͷ�ID����
    NF_ADDR(0x0000);   //ָ����ַ

    DELAY_US(12L);

    id = NF_RDDATA();     //����ID, 20H
    id <<= 16;
    id |= NF_RDDATA();    //�豸ID, 76H

    return id;
}

//==========================//
//������:NF_ReadStatus()
//����:��״̬
//����:
//���:
//==========================//
Uint16 NF_ReadStatus(void)
{
    Uint16 i,status=0;

    NF_CMD(0x70); //���Ͷ�״̬����

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
//������:NF_IsBadBlock()
//����:�Ƿ񻵿�
//����:
//���:
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

    NF_CMD(0x5050);                //����C
    NF_ADDR(0x0000);               //A0~A7 λ(Column Address)
    NF_ADDR(addr1);                //A9-A16, (Page Address)
    NF_ADDR(addr2);                //A17-A24, (Page Address)
    NF_ADDR(addr3);                //A25, (Page Address)

    DELAY_US(12L);

    for(i=0;i<NF_SPARE_NUM;i++)
    {
        buff[i] = NF_RDDATA();    //��16�� �ֽ�
    }

    if(buff[5]==0xffff)           //�ǻ���
    {*/
        rtn = 0;
//    }

    return rtn;
}

//==========================//
//������:NF_MarkBadBlock()
//����:��ǻ���
//����:
//���:
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

    NF_CMD(0x5050);                //����C
    NF_CMD(0x8080);                //д��ʼ����
    NF_ADDR(0x0000);               //A0~A7 λ(Column Address)
    NF_ADDR(addr1);                //A9-A16, (Page Address)
    NF_ADDR(addr2);                //A17-A24, (Page Address)
    NF_ADDR(addr3);                //A25, (Page Address)

    buff[5] = 0x4444;              //��6���ֽڱ�ǻ���

    for(i=0;i<NF_SPARE_NUM;i++)
    {
        NF_WRDATA(buff[i]);        //д16 �ֽڵ�Spare area
    }

    NF_CMD(0x1010);      */          //д��������



    return rtn;
}

//==========================//
//������:NF_EraseBlock()
//����:������
//����:
//���:
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

    NF_CMD(0x60);                //���ò���ģʽ
    NF_ADDR(addr1);                //A9-A16, (Page Address), ���ڿ����
    NF_ADDR(addr2);                //A17-A24, (Page Address)
    NF_ADDR(addr3);                //A25, (Page Address)
    NF_CMD(0xd0);                //���Ͳ�д����, ��ʼ��д

    DELAY_US(3500);      //max 3ms
    rtn = 0;
    return rtn;
}

//==========================//
//������:NF_ReadPage()
//����:��һҳ����
//����:
//���:
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

    NF_CMD(0x00);                //������A
    NF_ADDR(0x00);               //A0~A7 λ(Column Address)
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
//������:NF_WritePage()
//����:дһҳ����
//����:
//���:
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


    NF_CMD(0x80);                //д��ʼ����
    NF_ADDR(0x00);               //A0~A7 λ(Column Address)
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
    NF_CMD(0x10);                //д��������

    DELAY_US(620);     //MAX 600us

    rtn = 0;
    return rtn;
}

//===========================================================================
// No more.
//===========================================================================

