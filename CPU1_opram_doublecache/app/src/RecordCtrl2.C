/*
 * RecordCtrl2.C
 *
 *  Created on: 2024Äê3ÔÂ15ÈÕ
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

void NandFlashInit(void)
{

}

void SaveWave(void)
{
    switch(NF_Data.OpNum)
    {

        case WriteWave:
        {
            if()
            NF_Data.SampNum = NF_SampNum_Flt;
            NF_Data.SectNum = NF_SectNum_Flt;
            NF_Data.BlkNum = NF_BlkNum_Flt;
        }
        case WriteAboWave:
        {
            NF_Data.Index = NF_Data.SampIndex-1-NF_PreSampNum;
            if(NF_Data.Index < 0)
            NF_Data.Index += SAMP_NUM;
            NF_Data.RmsIdx = NF_Data.SampRmsIdx-1-NF_PreNum_Rms;
            if(NF_Data.RmsIdx < 0)
            NF_Data.RmsIdx += NF_DataNum_Rms;
            NF_Data.RmsCmpEn = 1;
            NF_Data.CmpEn = 1;
            NF_Data.SampNum = NF_SampNum_Abn;
            NF_Data.SectNum = NF_SectNum_Abn;
            NF_Data.BlkNum = NF_BlkNum_Abn;
        }


    }







}
