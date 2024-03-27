//###########################################################################
//
// FILE:	State_Machine.c
//
// TITLE:
//
//###########################################################################
// $TI Release:
// $Release Date: Aug  04, 2018 $
// $Copyright:
//
//###########################################################################

#include "F28x_Project.h"
#include "State_Machine.h"
#include "Const_Defines.h"
#include "Global_struct.h"
#include "Temperature.h"
#include "NandFlash.h"
#include "RecordCtrl.h"
#include "INV_CalFun.h"

//#define TEST
#define EXRAM_512K
/*********************************************************
 * author:xiaogang
 * function:void StateMachineInit()
 * description: 状态机初始化函数
 * data: 2018.8.4
 ********************************************************/
void StateMachineInit()
{
	 RunData.StateMachine.StateMachine = Stop_State;
	 RunData.StateMachine.StateMachinepre = Stop_State;
	 RunData.StateMachine.FaultCode0Reg.all = 0;
	 RunData.StateMachine.FaultCode1Reg.all = 0;
	 RunData.StateMachine.FaultCode2Reg.all = 0;
	 RunData.StateMachine.FaultCode3Reg.all = 0;
	 RunData.StateMachine.FaultCode4Reg.all = 0;
}

/*********************************************************
 * author:xiaogang
 * function: void StateMachineProc()
 * description: 状态机调用函数
 * data: 2018.8.6
 ********************************************************/
void StateMachineProc()
{
	static Uint32 dly = 0;
	static int16 dlyfault = 0;
	static int16 dlyfault1 = 0;
	static int16 dlyrun = 0;
	static int16 dlyLED = 0;
	static int16 dlyKM5 = 0;
	static int16 dly_mcb_on = 0;
	static int16 dly_mcb_off = 0;
	static int16 restart = 0;
	int16 ch;
	Uint16 *pStatus;

	if((RunData.StateMachine.McwReg.bits.Calibartion==1)&&(RunData.StateMachine.PreMcwReg.bits.Calibartion==0))
	{
		RunData.StateMachine.MswReg.bits.Calibartion = 1;
     	for(ch =0;ch<16;ch++)
        {
   // 	    *(&(AdcObj.adChZero->A0ZERO)+ch) = 0;
        }

	    RunData.StateMachine.MswReg.bits.RdyRun = 0;
	    RunData.StateMachine.MswReg.bits.Running = 0;
	    RunData.StateMachine.MswReg.bits.TestMode = 0;
	    RunData.StateMachine.MswReg.bits.Charging = 0;
	    RunData.StateMachine.MswReg.bits.ParamEn = 0;
	}

	if((RunData.StateMachine.McwReg.bits.AutoManual!=RunData.StateMachine.PreMcwReg.bits.AutoManual))
	{
	    RunData.StateMachine.MswReg.bits.Wave_RdOn = 1;
	}

	if((RunData.StateMachine.McwReg.bits.ParamEn==1)&&(RunData.StateMachine.PreMcwReg.bits.ParamEn==0))
	{
		 RunData.StateMachine.MswReg.bits.ParamEn = 1;

		 RunData.StateMachine.MswReg.bits.RdyRun = 0;
		 RunData.StateMachine.MswReg.bits.Running = 0;
		 RunData.StateMachine.MswReg.bits.TestMode = 0;
		 RunData.StateMachine.MswReg.bits.Charging = 0;
		 RunData.StateMachine.MswReg.bits.Calibartion = 0;
	}

    if((RunData.StateMachine.FaultCode0Reg.all) \
            ||(RunData.StateMachine.FaultCode1Reg.all) \
            ||(RunData.StateMachine.FaultCode2Reg.all) \
            ||(RunData.StateMachine.FaultCode3Reg.all) \
            ||(RunData.StateMachine.FaultCode4Reg.bits.op_slave))
    {
     	RunData.StateMachine.StateMachine = Fault;
     	RunData.StateMachine.MswReg.bits.Fault = 1;
	    RunData.StateMachine.MswReg.bits.RdyRun = 0;
	    RunData.StateMachine.MswReg.bits.Running = 0;
	    RunData.StateMachine.MswReg.bits.TestMode = 0;
	    RunData.StateMachine.MswReg.bits.Charging = 0;
    }

	if(RunData.StateMachine.FaultCode4Reg.bits.BreakScrA||RunData.StateMachine.FaultCode4Reg.bits.BreakScrB||RunData.StateMachine.FaultCode4Reg.bits.BreakScrC)
	{

		RunData.StateMachine.StateMachine = Fault;
	//	RunData.StateMachine.MswReg.bits.Fault = 1;
	}


	switch(RunData.StateMachine.StateMachine)
	    {
	        case Stop_State:

	            CLOSED_PWM();
	            MODULE1_OFF
	            MODULE2_OFF
	            MODULE3_OFF
	            MODULE4_OFF

	            if((RunData.StateMachine.StateMachinepre == Fault)&&(RunData.StateMachine.StateMachine == Stop_State))
	            {
	                restart++;
	            }
	            if(RunData.StateMachine.McwReg.bits.Reset)
	            {
	                restart = 0;
	            }
	            RunData.StateMachine.StateMachinepre = RunData.StateMachine.StateMachine;

	           if(RunData.StateMachine.McwReg.bits.EnterTestMode)
	            {
	                RunData.StateMachine.StateMachine = TestState;

	                dly = 0;
	            }

	            dlyLED++;
	            if(dlyLED>10)
	            {
	                ERR_OFF
	                FAULT_OFF
	                RUN_OFF
	                AC_KM2_OFF
	                AC_CHARGE_OFF
	                CAP_KM11_OFF
	                dlyLED = 0;
	            }

	            dlyfault = 0;
	     if(RunData.StateMachine.MswReg.bits.Start == 0)
	     {
	         AC_BREAKER_BYPASS_DOWN_OFF
	         dly_mcb_off = 0;
	         dly_mcb_on++;
	         if(dly_mcb_on<3000)
	         {
	             AC_BREAKER_BYPASS_TRIP_ON
	         }
	         else
	         {
	             AC_BREAKER_BYPASS_TRIP_OFF
	             dly_mcb_on = 3002;
	             MonitorACBypassMcbStatus();
	          }
	     }

	     if((RunData.InvControlOutput.GridVda > 100)&&(RunData.InvControlOutput.GridVdb > 100)&&(RunData.InvControlOutput.GridVdc > 100))
	     {
	          if((((RunData.STATUS_CPLD0>>7)&0x0001)==0)&&(RunData.StateMachine.MswReg.bits.Start == 1)&&(restart<2))
	          {
#ifdef BYPASS_NO_FAULT
#else
	                if((((RunData.STATUS_CPLD0>>3)&0x0001)==1)&&(((RunData.STATUS_CPLD0>>4)&0x0001)==1))
	                    {
	                        dly_mcb_on = 0;
	                        AC_BREAKER_BYPASS_TRIP_OFF
	                        dly_mcb_off++;
	                        if(dly_mcb_off<350)
	                        {
	                            AC_BREAKER_BYPASS_DOWN_ON
	                        }
	                        else
	                        {
	                            AC_BREAKER_BYPASS_DOWN_OFF
	                            dly_mcb_off = 352;
	                            if(((RunData.STATUS_CPLD0>>2)&0x0001)==1)
	                            {
	                               RunData.StateMachine.FaultCode1Reg.bits.BypassSwitchFlt = 1;
	                            }
	                        }
	                    }
	                    else if(((RunData.STATUS_CPLD0>>3)&0x0001)==0)
	                    {
	                        RunData.StateMachine.FaultCode1Reg.bits.InputSwitchFlt = 1;
	                    }
	                    else
	                    {
	                        RunData.StateMachine.FaultCode1Reg.bits.OutputSwitchFlt = 1;
	                    }
#endif
	             if(((RunData.STATUS_CPLD0>>2)&0x0001)==0) // 旁路开关不合
	             {
	                 if(RunData.FilteredData.Udc>460)
	                 {
	                //   AC_KM2_ON
	                     AC_BREAKER_BYPASS_DOWN_OFF
	                     RunData.StateMachine.MswReg.bits.Charging = 1;
	                     RunData.StateMachine.StateMachine = ReadyStart;
	                     dly = 0;
	                  }
	                  else
	                  {
	                     AC_CHARGE_ON
	                     AC_BREAKER_BYPASS_DOWN_OFF
	                     RunData.StateMachine.MswReg.bits.Charging = 1;
	                     RunData.StateMachine.StateMachine = ReadyStart;
	                     dly = 0;
	                  }
	             }

	        }
	     }

	             MonitorACMcbStatus();
	             RunData.StateMachine.McwReg.bits.Reset = 0;
	             RunData.StateMachine.MswReg.bits.reset = 0;
	             RunData.StateMachine.McwReg.bits.Stop = 0;
	        //   RunData.StateMachine.McwReg.bits.InvRun = 0;
	             RunData.StateMachine.MswReg.bits.RdyRun = 0;
	             RunData.StateMachine.MswReg.bits.Running = 0;
	             RunData.StateMachine.MswReg.bits.Fault = 0;
	             RunData.StateMachine.MswReg.bits.TestMode = 0;
	             RunData.StateMachine.MswReg.bits.Charging = 0;
	             RunData.StateMachine.MswReg.bits.GridCompen = 0;
	             RunData.StateMachine.MswReg.bits.Gridabnomal = 0;
	             break;
	        case ReadyStart:
	            CLOSED_PWM();
	            ERR_OFF
	            FAULT_OFF
	            CAP_KM11_ON
	             dly++;
	            if((dly>1000)&&(RunData.FilteredData.Udc>100*(1.414*1.732*ParaData.InvCtr.vdref/ParaData.InvCtr.Transformer_k))&&(RunData.FilteredData.Ucap>100*(1.414*1.732*ParaData.InvCtr.vdref/ParaData.InvCtr.Transformer_k)))
	            {
	                AC_KM2_ON
	            }
                if((dly>1000)&&(RunData.FilteredData.Udc>100*(2.3*ParaData.InvCtr.vdref/ParaData.InvCtr.Transformer_k))&&(RunData.FilteredData.Ucap>100*(2.3*ParaData.InvCtr.vdref/ParaData.InvCtr.Transformer_k))&&(RunData.FilteredData.IgbtIa1<1.2)&&(RunData.FilteredData.IgbtIb1<1.2)&&(RunData.FilteredData.IgbtIc1<1.2))
                {
                    AC_KM2_ON
                }

	            if((dly>8000)&&(RunData.FilteredData.Udc>235*RunData.GridData.LoadUaRms/ParaData.InvCtr.Transformer_k)&&(RunData.FilteredData.Ucap>235*RunData.GridData.LoadUaRms/ParaData.InvCtr.Transformer_k))
	             {
	                 AC_KM2_ON
	             }
	            else
	            {
	                if((dly>10000)&&(RunData.FilteredData.Ucap <30 ))
	                {
	                    RunData.StateMachine.FaultCode1Reg.bits.SoftContFault = 1;
	                }
	            }
	             if(RunData.StateMachine.McwReg.bits.Stop ==1)
	             {
	                RunData.StateMachine.StateMachine = Stop_State;
	                dly = 0;
	             }
	             if(RunData.StateMachine.MswReg.bits.Start ==0)
	             {
	                 RunData.StateMachine.StateMachine = Stop_State;
	                 dly = 0;
	             }
                 if((((RunData.STATUS_CPLD0>>7)&0x0001)==1))
                 {
                     AC_CHARGE_OFF
                 }
	             if((((RunData.STATUS_CPLD0>>6)&0x0001)==0)&&(((RunData.STATUS_CPLD0>>7)&0x0001)==1))
	             {
	                RunData.StateMachine.StateMachine = Dccharge;
	           //     AC_CHARGE_OFF

	                dly = 0;
	             }

	             if(dly > 65000)
	             {
	                if(RunData.FilteredData.Udc < RunData.GridData.LoadUaRms)
	                {
	                    RunData.StateMachine.FaultCode3Reg.bits.OverTimeStart = 1;
	                }

	                dly = 0;
	       //         RunData.StateMachine.FaultCode2Reg.bits.MainContFault = 1;
	             }
	             RunData.StateMachine.McwReg.bits.Charge = 0;
	             RunData.StateMachine.MswReg.bits.RdyRun = 0;
	             RunData.StateMachine.MswReg.bits.Running = 0;
	             RunData.StateMachine.MswReg.bits.Fault = 0;
	             RunData.StateMachine.MswReg.bits.TestMode = 0;
	             RunData.StateMachine.MswReg.bits.Charging = 1;
	             RunData.StateMachine.MswReg.bits.GridCompen = 0;
	             MonitorACMcbStatus();
	             MonitorACInMcbStatus();
	             MonitorACOutMcbStatus();
	             MonitorDCMcbStatus();
	             MonitorFilterCapConStatus();
	        //     MonitorSB1Status();
	             MonitorDCBrkStatus();
	             MonitorModule1BrkStatus();
	             MonitorModule2BrkStatus();
	             MonitorModule3BrkStatus();
	             MonitorModule4BrkStatus();
	             MonitorALLModuleStatus();
	             MonitorModule_Flt();
	             break;
	        case Dccharge:
	             ERR_OFF
	             CLOSED_PWM();
	             if(((RunData.STATUS_CPLD0>>2)&0x0001)==1)
	             {
	                 RunData.StateMachine.FaultCode1Reg.bits.BypassSwitchFlt = 1;
	             }

	             if((RunData.FilteredData.Ucap > 0.9*RunData.FilteredData.Udc))
	             {
	                 dly = 0;
	                 RunData.StateMachine.StateMachine = ReadyRun;
	              }

	              if((RunData.StateMachine.MswReg.bits.GridCompen ==0)&&(RunData.StateMachine.MswReg.bits.Gridabnomal))
	              {
	                  if((RunData.GridData.Ucapa_vol<100))
	                  {
	                     RunData.StateMachine.StateMachine = Stop_State;
	                  }
	                  Inv_controlobj.CtlINVMode = Standby;
	               }

	             if(RunData.StateMachine.McwReg.bits.Stop ==1)
	             {
	                 RunData.StateMachine.StateMachine = Stop_State;
	                 dly = 0;
	             }
	             if(RunData.StateMachine.MswReg.bits.Start ==0)
	             {
	                 RunData.StateMachine.StateMachine = Stop_State;
	                 dly = 0;
	             }

	             RunData.StateMachine.McwReg.bits.Charge = 0;
	             RunData.StateMachine.MswReg.bits.RdyRun = 0;
	             RunData.StateMachine.MswReg.bits.Running = 0;
	             RunData.StateMachine.MswReg.bits.Fault = 0;
	             RunData.StateMachine.MswReg.bits.TestMode = 0;
	             RunData.StateMachine.MswReg.bits.Charging = 1;
	             MonitorACMcbStatus();
	             MonitorACInMcbStatus();
	             MonitorACOutMcbStatus();
	             MonitorDCMcbStatus();
	             MonitorFilterCapConStatus();
	        //     MonitorSB1Status();
	             MonitorDCBrkStatus();
	             MonitorModule1BrkStatus();
	             MonitorModule2BrkStatus();
	             MonitorModule3BrkStatus();
	             MonitorModule4BrkStatus();
	             MonitorALLModuleStatus();
	             MonitorModule_Flt();
	        break;
	        case ReadyRun:
	            CLOSED_PWM();
	             dly++;
	             if(dly>500)
	             {
	                 dly = 502;
	             }
	             if(((RunData.STATUS_CPLD0>>2)&0x0001)==1)
	             {
	                 RunData.StateMachine.FaultCode1Reg.bits.BypassSwitchFlt = 1;
	             }

	             if((RunData.StateMachine.MswReg.bits.Start == 1)&&(dly>500))
	             {
	                 RunData.StateMachine.StateMachine = Running;
	                 dly = 202;

	             }
	            if((RunData.StateMachine.MswReg.bits.GridCompen ==0)&&(RunData.StateMachine.MswReg.bits.Gridabnomal))
	            {
	                 if(RunData.GridData.Ucapa_vol<170)
	                 {
	                        RunData.StateMachine.StateMachine = Stop_State;
	                 }
	                    Inv_controlobj.CtlINVMode = Standby;
	            }
	             if((RunData.StateMachine.McwReg.bits.Stop ==1)&&(dly>200))
	             {
	                 RunData.StateMachine.StateMachine = Stop_State;
	                 dly = 0;
	             }
	             if((RunData.StateMachine.MswReg.bits.Start ==0)&&(dly>200))
	             {
	                 RunData.StateMachine.StateMachine = Stop_State;
	                 dly = 0;
	             }

	             if(dly>100)
	             {
	                 MonitorACConStatus();
	             }

	             RunData.StateMachine.MswReg.bits.RdyRun = 1;
	             RunData.StateMachine.MswReg.bits.Running = 0;
	             RunData.StateMachine.MswReg.bits.Fault = 0;
	             RunData.StateMachine.MswReg.bits.TestMode = 0;
	             RunData.StateMachine.MswReg.bits.Charging = 1;
	             MonitorACMcbStatus();
	             MonitorACInMcbStatus();
	             MonitorACOutMcbStatus();
	             MonitorDCMcbStatus();
	             MonitorFilterCapConStatus();
	        //     MonitorSB1Status();
	             MonitorDCBrkStatus();
	             MonitorModule1BrkStatus();
	             MonitorModule2BrkStatus();
	             MonitorModule3BrkStatus();
	             MonitorModule4BrkStatus();
	             MonitorALLModuleStatus();
	             MonitorModule_Flt();
	             break;
	        case Running:
	            OPEN_PWM();

	             dly++;
	             if(dly>30000)
	             {
	                 restart = 0;
	                 dly = 0;
	             }
	             RUN_ON
	             if(((RunData.STATUS_CPLD0>>2)&0x0001)==1)
	             {
	                 RunData.StateMachine.FaultCode1Reg.bits.BypassSwitchFlt = 1;
	             }

	             if(RunData.StateMachine.MswReg.bits.Start == 0)
	             {
	                 dlyrun++;
	                 if(dlyrun > 50)
	                 {
	                     RunData.StateMachine.StateMachine = ReadyRun;
	                     dlyrun = 0;
	                 }
	             }

	            if((RunData.GridData.Ucapa_vol < Inv_controlobj.par->Ucap_charge))
	            {
	                if((RunData.InvControlOutput.GridVda > 100)&&(RunData.InvControlOutput.GridVdb > 100)&&(RunData.InvControlOutput.GridVdc > 100))
	                {
	                    dlyKM5++;
	                }
	                else
	                {
	                    dlyKM5 = 0;
	                }
	            }

	            if((RunData.GridData.Ucapa_vol < Inv_controlobj.par->Ucap_charge)&&(dlyKM5>20)&&(RunData.StateMachine.MswReg.bits.GridCompen ==0)&&(RunData.StateMachine.MswReg.bits.Gridabnomal ==0)&&(Inv_controlobj.CtlMcwReg.bits.GridSwitch==0))
	            {
	               if(RunData.StateMachine.McwReg.bits.Charge_Mode)
	                {
	                    Inv_controlobj.CtlINVMode = Udc_Q;
	                }
	                else
	                {
	                    Inv_controlobj.CtlINVMode = Idc_Q;
	                }

	                dlyKM5 = 22;
	            }

	            if((RunData.StateMachine.MswReg.bits.GridCompen ==0)&&(RunData.StateMachine.MswReg.bits.Gridabnomal))
	            {
	                if((RunData.GridData.Ucapa_vol<100))
	                {
	                    RunData.StateMachine.StateMachine = Stop_State;
	                }
	                Inv_controlobj.CtlINVMode = Standby;
	            }
	            if((RunData.GridData.Ucapa_vol > Inv_controlobj.par->Ucap_stop))
	            {
	                Inv_controlobj.CtlINVMode = Standby;
	                dlyKM5 = 0;
	            }
	             MonitorACMcbStatus();
	             MonitorACConStatus();
	             MonitorACInMcbStatus();
	             MonitorACOutMcbStatus();
	             MonitorDCMcbStatus();
	             MonitorFilterCapConStatus();
	        //     MonitorSB1Status();
	             MonitorDCBrkStatus();
	             MonitorModule1BrkStatus();
	             MonitorModule2BrkStatus();
	             MonitorModule3BrkStatus();
	             MonitorModule4BrkStatus();
	             MonitorALLModuleStatus();
	             MonitorModule_Flt();
	             RunData.StateMachine.MswReg.bits.Running = 1;
	             RunData.StateMachine.MswReg.bits.RdyRun = 0;
	             RunData.StateMachine.MswReg.bits.Fault = 0;
	             RunData.StateMachine.MswReg.bits.TestMode = 0;
	             RunData.StateMachine.MswReg.bits.Charging = 0;
	             break;
	        case Fault:

	        if(RunData.StateMachine.MswReg.bits.GridCompen)
	        {
	            RunData.Compenok = 0;
	        }
#ifdef BYPASS_NO_FAULT
#else
	        if(((RunData.STATUS_CPLD0>>2)&0x0001)==0)
	        {
	          RunData.StateMachine.MswReg.bits.Fault = 1;
	          RunData.StateMachine.MswReg.bits.Running = 0;
	        }
#endif
            MODULE1_OFF
            MODULE2_OFF
            MODULE3_OFF
            MODULE4_OFF

	       if(RunData.StateMachine.MswReg.bits.Fault)
	        {
	            CLOSED_PWM();
	            Inv_controlobj.CtlINVMode = Standby;
	            RunData.StateMachine.MswReg.bits.Running = 0;
	            AC_KM2_OFF
	        }
	        else
	        {
	            Inv_controlobj.CtlINVMode = VF_ISLAND;
	        }
#ifdef TEST
            if(NF_Data.FltTrip==1)//启动状态位&&NF_Data.FltTrip==1（初始化和复位为1）
#else
	        if((RunData.StateMachine.MswReg.bits.Start) && (NF_Data.FltTrip==1))//启动状态位&&NF_Data.FltTrip==1（初始化和复位为1）
#endif
	        {
	            NF_Data.FltTrip = 0;
//	            NF_Data.Step = 0;//change
//	            NF_Data.Type = RD_Fault;//change
//	            NF_Data.OpNum = NF_Write_Wave;//change
	            NF_Data.FltEn = 1;//故障使能
	            //故障索引=缓存计数-1-前移波形
	            NF_Data.FltIndex = NF_Data.SampFltIndex-1-NF_PreSampNum;
	                if(NF_Data.FltIndex < 0)
	                    NF_Data.FltIndex += SAMP_NUM_FLT;//如果前移数不够就等于缓存前的个数继续存
	                pStatus = &RunData.StateMachine.McwReg.all;
	                for(ch=0; ch<ALL_FLAG_LEN; ch++)
	                {
	                    NF_Data.Flag[ch] = pStatus[ch];
	                }

	                RunData.StateMachine.MswReg.bits.FltTrip = 1;
            }
#ifdef SOURCE
	        if((NF_Data.FltRdEn==0)&&(NF_Data.OpNum==0)&&(RunData.StateMachine.MswReg.bits.FltTrip==1))//delete
#endif
	        if(((NF_Data.FltRdEn==0)||(NF_Data.FltRdEn2==0))&&(NF_Data.OpNum==0)&&(RunData.StateMachine.MswReg.bits.FltTrip==1))//add
	        {
	           NF_Data.Step = 0;
	           NF_Data.Type = RD_Fault;//故障类型
	           NF_Data.OpNum = NF_Write_Wave;//1//写录波波形数据 delete end
	           if(NF_Data.FltRdEn==0)
	           {
	               NF_Data.ReadFltcache = 1;
	           }
	           else if(NF_Data.FltRdEn2==0)
	           {
	               NF_Data.ReadFltcache = 0;
	           }
	           RunData.StateMachine.MswReg.bits.FltTrip = 0;
            }

	        dlyLED = 0;
	        ERR
	        FAULT_ON
	        RUN_OFF
	        AC_CHARGE_OFF
	        CAP_KM11_OFF
	        dlyfault++;
            if((dlyfault>10000)&&(restart<1))
	        {
//                RunData.StateMachine.MswReg.bits.reset = 1;//delete 自复位功能
                RunData.StateMachine.MswReg.bits.reset = 0;

            }

            if(RunData.StateMachine.MswReg.bits.reset == 1)
            {
                RunData.StateMachine.FaultCode0Reg.all = 0;
	            RunData.StateMachine.FaultCode1Reg.all = 0;
	            RunData.StateMachine.FaultCode2Reg.all = 0;
	            RunData.StateMachine.FaultCode3Reg.all = 0;
	            RunData.StateMachine.FaultCode4Reg.all = 0;
	            Temper_ambient_obj.TemperCSReg.bits.Fault = 0;
	            Temper_ambient1_obj.TemperCSReg.bits.Fault = 0;
	            Temper_SCR_obj.TemperCSReg.bits.Fault = 0;
	            Inv_controlobj.CtlMcwReg.bits.OvertimeEn = 0;
	            NF_Data.Fault = 0;
	            NF_Data.FltTrip = 1;
	            dlyfault = 0;
//	            dly_mcb_on = 0;
            }

	             if(RunData.StateMachine.McwReg.bits.Reset == 1)
	             {
	                 RunData.StateMachine.MswReg.bits.reset = 1;
	                 RunData.StateMachine.FaultCode0Reg.all = 0;
	                 RunData.StateMachine.FaultCode1Reg.all = 0;
	                 RunData.StateMachine.FaultCode2Reg.all = 0;
	                 RunData.StateMachine.FaultCode3Reg.all = 0;
	                 RunData.StateMachine.FaultCode4Reg.all = 0;
	                 Temper_ambient_obj.TemperCSReg.bits.Fault = 0;
	                 Temper_ambient1_obj.TemperCSReg.bits.Fault = 0;
	                 Temper_SCR_obj.TemperCSReg.bits.Fault = 0;
	                 Inv_controlobj.CtlMcwReg.bits.OvertimeEn = 0;
	                 NF_Data.FltTrip = 1;
	                 NF_Data.Fault = 0;
	                 dlyfault = 0;
	                 dly_mcb_on = 0;
	                 restart = 0;
	             }

	            RunData.StateMachine.StateMachinepre = RunData.StateMachine.StateMachine;
	            if((RunData.StateMachine.FaultCode0Reg.all==0)&&(RunData.StateMachine.FaultCode1Reg.all==0)&&(RunData.StateMachine.FaultCode2Reg.all==0)&&(RunData.StateMachine.FaultCode3Reg.all==0)&&(RunData.StateMachine.FaultCode4Reg.all==0))
	            {
	             dlyfault1++;
	             if(dlyfault1>5)
	             {
	                 RunData.StateMachine.StateMachine = Stop_State;
	                 dlyfault1 = 0;
	             }
	            }

	             AC_BREAKER_BYPASS_DOWN_OFF
	             dly_mcb_off = 0;
	             dly_mcb_on++;
	             if(dly_mcb_on<3000)
	             {
	                 AC_BREAKER_BYPASS_TRIP_ON
	             }
	             else
	             {
	                 AC_BREAKER_BYPASS_TRIP_OFF
	                 dly_mcb_on = 3002;
	                 MonitorACBypassMcbStatus();
	             }
	    //         MonitorModule_Flt();
	             RunData.StateMachine.McwReg.bits.Stop = 0;
	             RunData.StateMachine.McwReg.bits.Charge = 0;
	    //       RunData.StateMachine.McwReg.bits.InvRun = 0;
	    //       RunData.StateMachine.MswReg.bits.Running = 0;
	             RunData.StateMachine.MswReg.bits.RdyRun = 0;
	    //       RunData.StateMachine.MswReg.bits.Fault = 1;
	    //         RunData.StateMachine.MswReg.bits.TestMode = 0;
	             RunData.StateMachine.MswReg.bits.Charging = 0;
	    //       RunData.StateMachine.MswReg.bits.GridCompen = 0;
	    //       RunData.StateMachine.MswReg.bits.Gridabnomal = 0;
	             RunData.StateMachine.MswReg.bits.Start = 0;

	             break;
	        case TestState:
	            OPEN_PWM();
	             if((RunData.StateMachine.McwReg.bits.Stop)||(RunData.StateMachine.McwReg.bits.EnterTestMode ==0))
	             {
	                RunData.StateMachine.StateMachine = Stop_State;
	                dly = 0;
	             }
	             if(dly<=100)
	             {
	                 AC_CHARGE_ON
	             }
	             if(dly>100)
	             {
	                 AC_CHARGE_OFF
	             }

	             dly++;

	             if(dly>300)
	             {
	                 RunData.StateMachine.MswReg.bits.TestMode = 1;
	                 Inv_controlobj.CtlINVMode = VF_ISLAND;
	                 dly =302;
	             }

	             RunData.StateMachine.MswReg.bits.RdyRun = 0;
	             RunData.StateMachine.MswReg.bits.Running = 0;
	             RunData.StateMachine.MswReg.bits.Fault = 0;
	             RunData.StateMachine.MswReg.bits.Charging = 0;
	             break;
	        default:
	             RunData.StateMachine.StateMachine = Stop_State;
	             break;
	    }

	    RunData.StateMachine.PreMcwReg.all = RunData.StateMachine.McwReg.all;

	}


	void MonitorDCMcbStatus()
	{
	    static int16 dlytempa = 0;
	    if((((RunData.STATUS_CPLD0>>10)&0x0001)||((RunData.STATUS_CPLD0>>11)&0x0001)||((RunData.STATUS_CPLD0>>12)&0x0001)||((RunData.STATUS_CPLD0>>13)&0x0001))==0)
	    {
	        dlytempa++;
	        if(dlytempa>100)
	        {
	            dlytempa = 0;
	            RunData.StateMachine.FaultCode2Reg.bits.BreakerDcFlt = 1;
	        }
	    }
	    else
	    {
	        dlytempa = 0;
	    }
	}

    void MonitorACMcbStatus()
    {
        static int16 dlytempa = 0;
        if((((RunData.STATUS_CPLD0>>14)&0x0001)||((RunData.STATUS_CPLD0>>15)&0x0001)||((RunData.STATUS_CPLD1)&0x0001)||((RunData.STATUS_CPLD1>>1)&0x0001))==0)
        {
            dlytempa++;
            if(dlytempa>100)
            {
                dlytempa = 0;
                RunData.StateMachine.FaultCode1Reg.bits.ALL_ACBrkFUFlt = 1;
            }
        }
        else
        {
            dlytempa = 0;
        }
    }

    void MonitorModule1BrkStatus()
    {
        static int16 dlytempa = 0;
        if(((RunData.STATUS_CPLD0>>14)&0x0001)&&(((RunData.STATUS_CPLD0>>10)&0x0001)==0))
        {
            dlytempa++;
            if(dlytempa>100)
            {
                dlytempa = 0;
                RunData.StateMachine.FaultCode3Reg.bits.M1_ACNC_DCNO_Flt = 1;
            }
        }
        else
        {
            dlytempa = 0;
        }
    }

    void MonitorModule2BrkStatus()
    {
        static int16 dlytempa = 0;
        if(((RunData.STATUS_CPLD0>>15)&0x0001)&&(((RunData.STATUS_CPLD0>>11)&0x0001)==0))
        {
            dlytempa++;
            if(dlytempa>100)
            {
                dlytempa = 0;
                RunData.StateMachine.FaultCode3Reg.bits.M2_ACNC_DCNO_Flt = 1;
            }
        }
        else
        {
            dlytempa = 0;
        }
    }

    void MonitorModule3BrkStatus()
    {
        static int16 dlytempa = 0;
        if(((RunData.STATUS_CPLD1)&0x0001)&&(((RunData.STATUS_CPLD0>>12)&0x0001)==0))
        {
            dlytempa++;
            if(dlytempa>100)
            {
                dlytempa = 0;
                RunData.StateMachine.FaultCode3Reg.bits.M3_ACNC_DCNO_Flt = 1;
            }
        }
        else
        {
            dlytempa = 0;
        }
    }

    void MonitorModule4BrkStatus()
    {
        static int16 dlytempa = 0;
        if(((RunData.STATUS_CPLD1>>1)&0x0001)&&(((RunData.STATUS_CPLD0>>13)&0x0001)==0))
        {
            dlytempa++;
            if(dlytempa>100)
            {
                dlytempa = 0;
                RunData.StateMachine.FaultCode3Reg.bits.M4_ACNC_DCNO_Flt = 1;
            }
        }
        else
        {
            dlytempa = 0;
        }
    }

    void MonitorALLModuleStatus()
    {
        static int16 dly_module1 = 0;
        static int16 dly_module2 = 0;
        static int16 dly_module3 = 0;
        static int16 dly_module4 = 0;

        switch (ParaData.Module_NUM)
        {
            case 4:
                if(((RunData.ModbusData2[5]>>1)&0x0001)&&((RunData.ModbusData2[17]>>1)&0x0001)&&((RunData.ModbusData2[29]>>1)&0x0001)&&(((RunData.ModbusData2[41]>>1)&0x0001)))
                {
                    dly_module1++;
                    if(dly_module1>100)
                    {
                        dly_module1 = 0;
                        RunData.StateMachine.FaultCode2Reg.bits.ALL_ModuleFlt = 1;
                    }
                }
                else
                {
                    dly_module1 = 0;
                }
            break;
            case 3:
                if(((RunData.ModbusData2[5]>>1)&0x0001)&&((RunData.ModbusData2[17]>>1)&0x0001)&&((RunData.ModbusData2[29]>>1)&0x0001))
                {
                    dly_module2++;
                    if(dly_module2>100)
                    {
                        dly_module2 = 0;
                        RunData.StateMachine.FaultCode2Reg.bits.ALL_ModuleFlt = 1;
                    }
                }
                else
                {
                    dly_module2 = 0;
                }
            break;
            case 2:
                if(((RunData.ModbusData2[5]>>1)&0x0001)&&((RunData.ModbusData2[17]>>1)&0x0001))
                {
                    dly_module3++;
                    if(dly_module3>100)
                    {
                        dly_module3 = 0;
                        RunData.StateMachine.FaultCode2Reg.bits.ALL_ModuleFlt = 1;
                    }
                }
                else
                {
                    dly_module3 = 0;
                }
            break;
            case 1:
                if(((RunData.ModbusData2[5]>>1)&0x0001))
                {   dly_module4++;
                    if(dly_module4>100)
                    {
                        dly_module4 = 0;
                        RunData.StateMachine.FaultCode2Reg.bits.ALL_ModuleFlt = 1;
                    }
                }
                else
                {
                    dly_module4 = 0;
                }
            break;
        default:
                if(((RunData.ModbusData2[5]>>1)&0x0001)&&((RunData.ModbusData2[17]>>1)&0x0001)&&((RunData.ModbusData2[29]>>1)&0x0001)&&(((RunData.ModbusData2[41]>>1)&0x0001)))
                {
                    dly_module1++;
                    if(dly_module1>100)
                    {
                        dly_module1 = 0;
                        RunData.StateMachine.FaultCode2Reg.bits.ALL_ModuleFlt = 1;
                    }
                }
                else
                {
                    dly_module1 = 0;
                }
            break;

        }

    }


	void MonitorDCBrkStatus()
	{
	    static int16 dlytempb = 0;
	    if(((RunData.STATUS_CPLD1>>2)&0x0001))
	    {
	        dlytempb++;
	        if(dlytempb>200)
	        {
	            dlytempb = 0;
	            RunData.StateMachine.FaultCode2Reg.bits.DISBrkDcFlt = 1;
	        }
	    }
	    else
	    {
	        dlytempb = 0;
	    }
	}


	void MonitorTRSoftConStatus()
	{
	    static int16 dlytemp = 0;
	    if(((RunData.STATUS_CPLD0>>6)&0x0001)==0)
	    {
	        dlytemp++;
	        if(dlytemp>20)
	        {
	            dlytemp = 0;
	            RunData.StateMachine.FaultCode2Reg.bits.TRSoftConFlt = 1;
	        }
	    }
	    else
	    {
	        dlytemp = 0;
	    }
	}

	void MonitorFilterCapConStatus()
	{
	    static int16 dlytemp = 0;
	    if(((RunData.STATUS_CPLD0>>8)&0x0001)==0)
	    {
	        dlytemp++;
	        if(dlytemp>100)
	        {
	            dlytemp = 0;
	            RunData.StateMachine.FaultCode2Reg.bits.FilterCapConFlt = 1;
	        }
	    }
	    else
	    {
	        dlytemp = 0;
	    }
	}

	void MonitorACConStatus()
	{
	    static int16 dlytemp = 0;
	    if(((RunData.STATUS_CPLD0>>7)&0x0001)==0)
	    {
	        dlytemp++;
	        if(dlytemp>100)
	        {
	            dlytemp = 0;
	            RunData.StateMachine.FaultCode2Reg.bits.MainContFault = 1;
	        }
	    }
	    else
	    {
	        dlytemp = 0;
	    }

	}

	void MonitorACInMcbStatus()
	{
	    static int16 dlytemp = 0;
	    if(((RunData.STATUS_CPLD0>>3)&0x0001)==0)
	    {
	        dlytemp++;
	        if(dlytemp>1000)
	        {
	            dlytemp = 0;
	            RunData.StateMachine.FaultCode1Reg.bits.InputSwitchFlt = 1;
	        }
	    }
	    else
	    {
	        dlytemp = 0;
	    }
	}

	void MonitorACOutMcbStatus()
	{
	    static int16 dlytemp = 0;
	    if(((RunData.STATUS_CPLD0>>4)&0x0001)==0)
	    {
	        dlytemp++;
	        if(dlytemp>100)
	        {
	            dlytemp = 0;
	            RunData.StateMachine.FaultCode1Reg.bits.OutputSwitchFlt = 1;
	        }
	    }
	    else
	    {
	        dlytemp = 0;
	    }
	}

	void MonitorACBypassMcbStatus()
	{
	    static int16 dlytemp = 0;
	    if(((RunData.STATUS_CPLD0>>2)&0x0001)==0)
	    {
#ifdef BYPASS_NO_FAULT
#else
	        dlytemp++;
	        if(dlytemp>350)
	        {
	            dlytemp = 0;
	            RunData.StateMachine.FaultCode1Reg.bits.BypassSwitchFlt = 1;
	        }
#endif
	    }
	    else
	    {
	        dlytemp = 0;
	    }
	}

	void MonitorSB1Status()
	{
	    static int16 dlytemp = 0;
	    if(((RunData.STATUS_CPLD0>>9)&0x0001))
	    {
	        dlytemp++;
	        if(dlytemp>100)
	        {
	            dlytemp = 0;
	            RunData.StateMachine.FaultCode1Reg.bits.SB1overtime = 1;
	        }
	    }
	    else
	    {
	        dlytemp = 0;
	    }
	}
	void MonitorModule_Flt()
	{
	    static int16 dly_module1 = 0;
	    static int16 dly_module2 = 0;
	    static int16 dly_module3 = 0;
	    static int16 dly_module4 = 0;

	    if((((RunData.ModbusData2[5]>>1)&0x0001)==1)&&(RunData.StateMachine.StatusReg0.bits.ComStatus1==0))
	    {
	        dly_module1++;
	        if(dly_module1>2000)
	        {
	            MODULE1_ON
	            dly_module1 =0;
	        }

	    }
	    else
	    {
	        dly_module1 = 0;
	    }
        if((((RunData.ModbusData2[17]>>1)&0x0001)==1)&&(RunData.StateMachine.StatusReg0.bits.ComStatus2==0))
        {
            dly_module2++;
               if(dly_module2>2000)
               {
                   MODULE2_ON
                   dly_module2 =0;
               }
        }
        else
        {
            dly_module2 =0;
        }
        if((((RunData.ModbusData2[29]>>1)&0x0001)==1)&&(RunData.StateMachine.StatusReg0.bits.ComStatus3==0))
        {
            dly_module3++;
            if(dly_module3>2000)
            {
                MODULE3_ON
                dly_module3 =0;
            }

        }
        else
        {
            dly_module3 =0;
        }
        if((((RunData.ModbusData2[41]>>1)&0x0001)==1)&&(RunData.StateMachine.StatusReg0.bits.ComStatus4==0))
        {
            dly_module4++;
            if(dly_module4>2000)
            {
                MODULE4_ON
                dly_module4 =0;
            }
        }
        else
        {
            dly_module4 =0;
        }

	}

	void IOtext()
	{
	   if(RunData.IOtext==0x0001)
	   {
	       AC_BREAKER_BYPASS_TRIP_ON
	   }
	   else
	   {
	       AC_BREAKER_BYPASS_TRIP_OFF
	   }
	   if(RunData.IOtext==0x0002)
	   {
	       AC_BREAKER_BYPASS_DOWN_ON
	   }
	   else
	   {
	       AC_BREAKER_BYPASS_DOWN_OFF
	   }
	   if(RunData.IOtext==0x0004)
	   {
	       AC_KM2_ON
	   }
	   else
	   {
	       AC_KM2_OFF
	   }
	   if(RunData.IOtext==0x0008)
	   {
	       AC_CHARGE_ON
	   }
	   else
	   {
	       AC_CHARGE_OFF
	   }
	   if(RunData.IOtext==0x0010)
	   {
	       CAP_KM11_ON
	   }
	   else
	   {
	       CAP_KM11_OFF
	   }
	   if(RunData.IOtext==0x0020)
	   {
	       BUSCAP_DISCHARGE_ON
	   }
	   else
	   {
	       BUSCAP_DISCHARGE_OFF
	   }
	   if(RunData.IOtext==0x0040)
	   {
	       ERR
	   }
	   else
	   {
	       ERR_OFF
	   }
	   if(RunData.IOtext==0x0080)
	   {
	       FAULT_ON
	   }
	   else
	   {
	       FAULT_OFF
	   }
	   if(RunData.IOtext==0x0100)
	   {
	       MODULE1_ON
	   }
	   else
	   {
	       MODULE1_OFF
	   }
	   if(RunData.IOtext==0x0200)
	   {
	       MODULE2_ON
	   }
	   else
	   {
	       MODULE2_OFF
	   }
	   if(RunData.IOtext==0x0400)
	   {
	       MODULE3_ON
	   }
	   else
	   {
	       MODULE3_OFF
	   }

	  if(RunData.IOtext==0x0800)
	  {
	       MODULE4_ON
	  }
	  else
	 {
	       MODULE4_OFF
	  }
	 if(RunData.IOtext==0x1000)
	  {
         SCR_FAN_ON
	  }
	 if(RunData.IOtext==0x2000)
	 {
	     REAC_FAN_ON
	 }
	 if(RunData.IOtext==0x4000)
	 {
	   //KM12
	 }

	 if(RunData.IOtext==0x8000)
	 {
        SCR_OFF
	 }
	 else
	 {
	     SCR_ON
	 }



	}

	void MonitorStatus()
	{
	    static Uint16 dly1 = 50,dly2 = 50,dly3 = 50,dly4 = 50;

	    if(RunData.StateMachine.MswReg.bits.Running||RunData.StateMachine.MswReg.bits.Charging)
	    {
	        RunData.StateMachine.StatusReg0.bits.RunStatus = 1;
	    }
	    else
	    {
	        RunData.StateMachine.StatusReg0.bits.RunStatus = 0;
	    }

	    if(RunData.StateMachine.MswReg.bits.Fault)
	    {
	        RunData.StateMachine.StatusReg0.bits.FaultStatus = 1;
	    }
	    else
	    {
	        RunData.StateMachine.StatusReg0.bits.FaultStatus = 0;
	    }
	    if(RunData.StateMachine.MswReg.bits.GridCompen)
	    {
	        RunData.StateMachine.StatusReg0.bits.CompenStatus = 1;
	    }
	    else
	    {
	        RunData.StateMachine.StatusReg0.bits.CompenStatus = 0;
	    }
	    if(RunData.StateMachine.MswReg.bits.Charging||((RunData.StateMachine.MswReg.bits.Running)&&(Inv_controlobj.CtlINVMode!=Standby)))
	    {
	        RunData.StateMachine.StatusReg0.bits.InvStatusA = 1;
	    }
	    else
	    {
	        RunData.StateMachine.StatusReg0.bits.InvStatusA = 0;
	    }

	    if((RunData.StateMachine.MswReg.bits.Running)&&((Inv_controlobj.CtlINVMode==Udc_Q)||(Inv_controlobj.CtlINVMode==Idc_Q)))
	    {
	        RunData.StateMachine.StatusReg0.bits.ChgStatusA = 1;
	    }
	    else
	    {
	        RunData.StateMachine.StatusReg0.bits.ChgStatusA = 0;
	    }

	    if((RunData.STATUS_CPLD0>>3)&0x0001)
	    {
	        RunData.StateMachine.StatusReg0.bits.InputSwitch = 1;
	    }
	    else
	    {
	        RunData.StateMachine.StatusReg0.bits.InputSwitch = 0;
	    }
	    if((RunData.STATUS_CPLD0>>4)&0x0001)
	    {
	        RunData.StateMachine.StatusReg0.bits.OutputSwitch = 1;
	    }
	    else
	    {
	        RunData.StateMachine.StatusReg0.bits.OutputSwitch = 0;
	    }
	    if((RunData.STATUS_CPLD0>>2)&0x0001)
	    {
	        RunData.StateMachine.StatusReg0.bits.BypassMcb = 1;
	    }
	    else
	    {
	        RunData.StateMachine.StatusReg0.bits.BypassMcb = 0;
	    }
	    if((RunData.STATUS_CPLD0>>7)&0x0001)
	    {
	        RunData.StateMachine.StatusReg0.bits.MainContact = 1;
	    }
	    else
	    {
	        RunData.StateMachine.StatusReg0.bits.MainContact = 0;
	    }
	    if((RunData.STATUS_CPLD0>>6)&0x0001)
	    {
	        RunData.StateMachine.StatusReg1.bits.SoftContact = 1;
	    }
	    else
	    {
	        RunData.StateMachine.StatusReg1.bits.SoftContact = 0;
	    }

	    if((RunData.STATUS_CPLD1>>3)&0x0001)
	    {
	        RunData.StateMachine.StatusReg1.bits.TRSoftCon = 1;
	    }
	    else
	    {
	        RunData.StateMachine.StatusReg1.bits.TRSoftCon = 0;
	    }
	    if((RunData.STATUS_CPLD0>>8)&0x0001)
	    {
	        RunData.StateMachine.StatusReg1.bits.FilteCapCon = 1;
	    }
	    else
	    {
	        RunData.StateMachine.StatusReg1.bits.FilteCapCon = 0;
	    }
	    if((RunData.STATUS_CPLD0>>10)&0x0001)
	    {
	        RunData.StateMachine.StatusReg1.bits.Module1BreakDC = 1;
	    }
	    else
	    {
	        RunData.StateMachine.StatusReg1.bits.Module1BreakDC = 0;
	    }

	    if((RunData.STATUS_CPLD0>>11)&0x0001)
	    {
	        RunData.StateMachine.StatusReg1.bits.Module2BreakDC = 1;
	    }
	    else
	    {
	        RunData.StateMachine.StatusReg1.bits.Module2BreakDC = 0;
	    }

        if((RunData.STATUS_CPLD0>>12)&0x0001)
        {
            RunData.StateMachine.StatusReg1.bits.Module3BreakDC = 1;
        }
        else
        {
            RunData.StateMachine.StatusReg1.bits.Module3BreakDC = 0;
        }
        if((RunData.STATUS_CPLD0>>13)&0x0001)
        {
            RunData.StateMachine.StatusReg1.bits.Module4BreakDC = 1;
        }
        else
        {
            RunData.StateMachine.StatusReg1.bits.Module4BreakDC = 0;
        }

	    if((RunData.STATUS_CPLD0>>1)&0x0001)
	    {
	        RunData.StateMachine.StatusReg1.bits.EmergentStop = 0;
	    }
	    else
	    {
	        RunData.StateMachine.StatusReg1.bits.EmergentStop = 1;
	    }

        if((RunData.STATUS_CPLD0)&0x0001)
        {
            RunData.StateMachine.StatusReg1.bits.SectionSwitch = 1;
        }
        else
        {
            RunData.StateMachine.StatusReg1.bits.SectionSwitch = 0;
        }
        if((RunData.STATUS_CPLD0>>14)&0x0001)
        {
            dly1++;
            if(dly1>100)
            {
                dly1 =105;

                RunData.StateMachine.StatusReg1.bits.Module1BreakAC = 1;
            }
        }
        else
        {
            dly1--;
            if(dly1<10)
           {
                dly1=8;
                RunData.StateMachine.StatusReg1.bits.Module1BreakAC = 0;
           }
        }

        if((RunData.STATUS_CPLD0>>15)&0x0001)
        {
            dly2++;
            if(dly2>100)
            {
                dly2 =105;

                RunData.StateMachine.StatusReg1.bits.Module2BreakAC = 1;
            }

        }
        else
        {
            dly2--;
            if(dly2<10)
           {
                dly2=8;
                RunData.StateMachine.StatusReg1.bits.Module2BreakAC = 0;
           }


        }

        if((RunData.STATUS_CPLD1)&0x0001)
        {
            dly3++;
            if(dly3>100)
            {
                dly3 =105;

                RunData.StateMachine.StatusReg1.bits.Module3BreakAC = 1;
            }
        }
        else
        {
            dly3--;
            if(dly3<10)
           {
                dly3=8;
                RunData.StateMachine.StatusReg1.bits.Module3BreakAC = 0;
           }
        }
        if((RunData.STATUS_CPLD1>>1)&0x0001)
        {
            dly4++;
            if(dly4>100)
            {
                dly4 =105;

                RunData.StateMachine.StatusReg1.bits.Module4BreakAC = 1;
            }
        }
        else
        {
            dly4--;
            if(dly4<10)
           {
                dly4=8;
                RunData.StateMachine.StatusReg1.bits.Module4BreakAC = 0;
           }
        }


	    RunData.StateMachine.StatusReg2.bits.SelfCheck = 1;

	}
//===========================================================================
// End of file.
//===========================================================================
