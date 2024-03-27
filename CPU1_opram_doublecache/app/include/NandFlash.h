/*
 * NandFlash.h
 *
 *  Created on: 2019-3-10
 *      Author: JCH
 */

#ifndef NANDFLASH_H_
#define NANDFLASH_H_

#define rNFDATA (*(volatile unsigned int *)0x380000)
#define rNFCMD  (*(volatile unsigned int *)0x380040)
#define rNFADDR (*(volatile unsigned int *)0x380020)

#define NF_WP_EN  GpioDataRegs.GPBSET.bit.GPIO32
#define NF_WP_DIS GpioDataRegs.GPBCLEAR.bit.GPIO32

#define NF_CMD(cmd)     {rNFCMD=cmd;}   //发送命令
#define NF_ADDR(addr)   {rNFADDR=addr;} //写入地址
#define NF_RDDATA()     (rNFDATA)       //读数据
#define NF_WRDATA(data) {rNFDATA=data;} //写数据

#define NF_BYTE_NUM    1024    //字节数2048  16位数 1024
#define NF_SPARE_NUM   64
#define NF_PAGE_NUM    64
#define NF_BLOCK_NUM   2048



extern void NandFlashInit(void);
extern void NF_Operate(void);
extern void RecordCtrl(void);
extern Uint32 NF_ReadID(void);
extern Uint16 NF_ReadStatus(void);
Uint16 NF_IsBadBlock(Uint16 block);
Uint16 NF_MarkBadBlock(Uint16 block);
Uint16 NF_EraseBlock(Uint16 block);
Uint16 NF_ReadPage(Uint16 block,Uint16 page,Uint16 *buffer);
Uint16 NF_WritePage(Uint16 block,Uint16 page,Uint16 *buffer);


#endif /* NANDFLASH_H_ */
