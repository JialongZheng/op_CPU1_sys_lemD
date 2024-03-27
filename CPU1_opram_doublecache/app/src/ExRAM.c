/*
 * ExRAM.c
 *
 *  Created on: 2024Äê3ÔÂ6ÈÕ
 *      Author: Admin
 */
#include <string.h>
#include "F2837xD_Device.h"
#include "F2837xD_Examples.h"    // DSP2833x Examples Include File
#include "Global_struct.h"
#include "ExRAM.h"


//Uint16 WriteMem(uint32_t startAddr,Uint16 WriteData,Uint16 memSize)
//{
//    uint32_t *memPrt;
//    uint32_t i;
//
//    //Write data to memory
//    memPrt = (uint32_t *)startAddr;
//    for(i=0;i<memSize;i++)
//    {
//        *memPrt++ = WriteData;
//    }
//
//    return 0;
//}
//Uint16 ReadMem(uint32_t startAddr,Uint16 memSize)
//{
//    uint32_t *memPrt;
//    uint32_t i;
//    Uint16 ReadData;
//
//    //Read data for memory
//    memPrt = (uint32_t *)startAddr;
//    for(i=0;i<memSize;i++)
//    {
//
//        ReadData = *memPrt++;
//    }
//    return ReadData;
//}
//void WriteMem1word(uint32_t startAddr,Uint16 WriteData)
//{
//   (*(volatile uint32_t *)startAddr) = WriteData;
//}
//Uint16 ReadMem1word(uint32_t startAddr)
//{
//    Uint16 ReadData = (*(volatile uint32_t *)startAddr);
//    return ReadData;
//}
