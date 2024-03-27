//###########################################################################
//
// FILE:   Sys_Init.h
//
// TITLE:
//
//###########################################################################
// $TI Release:
// $Release Date: March  8, 2016 $
// $Copyright:
//
//###########################################################################

#ifndef TASK_1MS_H
#define TASK_1MS_H


#include "Dev_Init.h"

extern void InitTimer1(void);
extern void Task1ms(void);
interrupt void CpuTimer1Isr(void);

extern void MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr);

#endif  // end of TASK_1MS_H definition


//===========================================================================
