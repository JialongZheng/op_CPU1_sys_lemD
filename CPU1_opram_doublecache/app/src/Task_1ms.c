//###########################################################################
//
// FILE:	Task_1ms.c




#include "Task_1ms.h"
#include "Modbusslave.h"
#include "Const_Defines.h"
#include "Global_struct.h"
#include "State_Machine.h"
#include "Temperature.h"
//#include "FaultProtect.h"
#include "NandFlash.h"
#include "database.h"
#include "master_can.h"
#include "master_can_app.h"
#include "CrcCheck.h"


/*********************************************************************************************************
** 函数名称: CpuTimer0Isr()
** 功能描述： T0中断
** 输　入:
** 输出:
** 注  释:
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:

***********************************************************************************************/


interrupt void CpuTimer1Isr(void)
{
    IER |= M_INT13;                          // Set "global" priority
    EINT;
    CpuTimer1Regs.TCR.bit.TIF=1; // 定时到了指定时间，标志位置位，清除标志
    CpuTimer1Regs.TCR.bit.TRB=1;  // 重载Timer1的定时数据
//    GpioDataRegs.GPASET.bit.GPIO24 = 1;

    Task1ms();

  //  GpioDataRegs.GPACLEAR.bit.GPIO24 = 1;



//------------------每次都采样---------------------------------------
  //  PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
Uint16 status_dly = 0;
void Task1ms(void)
{
    Uint16 cms_j = 0,cms_h = 0;
    Uint32 cms_vol_t = 0;

    status_dly++;
    if(status_dly>120)
    {
        status_dly = 1205;
        RunData.flagbit.bits.Bit15 = 1;
    }


    m_loop.LED_CNT++;
    CanScan.run_timer++;
    CanBScan.run_timer++;
    if(CanScan.run_timer > 100)
    {
        CanScan.run_timer = 0;
        CanScan.run_flag = 1;
    }

    if(CanBScan.run_timer > 200)
    {
        CanBScan.run_timer = 0;
        CanBScan.run_flag = 1;
    }

    can_err_timer(4);
    Can_Heart(ParaData.Module_NUM);

    if(m_loop.LED_CNT%500==0)
    {
  //     GpioDataRegs.GPCTOGGLE.bit.GPIO68 = 1;
#ifdef TEST_OP_SPEED
        led_30_ctrl(LED);
        led_30_ctrl(!LED);
#else
        GpioDataRegs.GPDTOGGLE.bit.GPIO99 = 1;
#endif
    }

    if(m_loop.LED_CNT%5 == 0)
    {
       StateMachineProc();
       if(RunData.flagbit.bits.Bit15){
        MonitorStatus();
       }
            
       if(RunData.StateMachine.McwReg.bits.IOtext)
       {
           IOtext();
       }
    }

    if(m_loop.LED_CNT%10 == 0)
    {
        ambient_ntc.ad = AMBIENT_TEMP;
        ambient_ntc.calc(&ambient_ntc);

        ambient_ntc1.ad = AMBIENT_TEMP1;
        ambient_ntc1.calc(&ambient_ntc1);

    /*    CAP_ntc.ad = REACTOR_TEMP;
        CAP_ntc.calc(&CAP_ntc);*/

        SCR_ntc.ad = SCR_HEATSINK_TEMP;
        SCR_ntc.calc(&SCR_ntc);

        Temper_ambient_obj.Data = &ambient_ntc.temperature;
        Temper_ambient_obj.run(&Temper_ambient_obj);

        Temper_ambient1_obj.Data = &ambient_ntc1.temperature;
        Temper_ambient1_obj.run(&Temper_ambient1_obj);

        Temper_SCR_obj.Data = &SCR_ntc.temperature;
        Temper_SCR_obj.run(&Temper_SCR_obj);

        RunData.StateMachine.FaultCode3Reg.bits.HighAmbientTemp = Temper_ambient_obj.TemperCSReg.bits.Fault|Temper_ambient1_obj.TemperCSReg.bits.Fault;
        RunData.StateMachine.FaultCode3Reg.bits.OverTempScr = Temper_SCR_obj.TemperCSReg.bits.Fault;

          if(Temper_SCR_obj.TemperCSReg.bits.FanAct)
          {
                SCR_FAN_ON
          }
          else
          {
                SCR_FAN_OFF
          }
          if((Temper_ambient1_obj.TemperCSReg.bits.FanAct)||(Temper_ambient_obj.TemperCSReg.bits.FanAct)||(RunData.StateMachine.StateMachine == ReadyStart))
          {
                REAC_FAN_ON
          }
          else
          {
                REAC_FAN_OFF
          }



        }
        CaltGrid();



    if(m_loop.LED_CNT%2 == 0)
    {
        RunData.flagbit.bits.Bit0 = 1;
        RunData.flagbit.bits.Bit1 = 1;
        RmsProtect();

        for(cms_j=0;cms_j<ParaData.CMS_NUM;cms_j++)
        {
            cms_vol_t = 0;
            for(cms_h=0;cms_h<16;cms_h++)
            {
               RunData.ModbusData[e_cms_vol+cms_j*17+cms_h] = CanBScan.RxB_Buff[cms_j][cms_h];
               cms_vol_t = cms_vol_t + (CanBScan.RxB_Buff[cms_j][cms_h]);
               if(cms_h==15)
               {
                   RunData.ModbusData[e_cms_vol+cms_j*17+16] = (Uint32)(100*RunData.GridData.Ucapa_vol)-cms_vol_t ;
               }

            }
        }
    }

    if(m_loop.LED_CNT%1000 == 0)
    {

 //       GpioDataRegs.GPBTOGGLE.bit.GPIO60 = 1;
    }
    if(m_loop.LED_CNT>=60000)
    {
    //    NF_Data.ParaWtEn = 1;
    }

}

void MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr)
{
    while(SourceAddr < SourceEndAddr)
    {
       *DestAddr++ = *SourceAddr++;
    }
    return;
}

//==========================================================================
// End of file.
//===========================================================================
