
/*
 *  FaultProtect.c
 *  Created on: 2018-7-9
 *  Author: xiaogang
 *
 */

#include "FaultProtect.h"
#include "Const_Defines.h"
#include "Global_struct.h"
#include "NandFlash.h"
#include "master_can.h"

TIMER_DLEAY EmergencyFault = TIMER_DLEAY_DEFAULTS;

TIMER_DLEAY DCFuseFaultA = TIMER_DLEAY_DEFAULTS;
TIMER_DLEAY DCFuseFaultB = TIMER_DLEAY_DEFAULTS;
TIMER_DLEAY DCFuseFaultC = TIMER_DLEAY_DEFAULTS;

TIMER_DLEAY ACFuseFaultA = TIMER_DLEAY_DEFAULTS;
TIMER_DLEAY ACFuseFaultB = TIMER_DLEAY_DEFAULTS;
TIMER_DLEAY ACFuseFaultC = TIMER_DLEAY_DEFAULTS;

OVER_PROTECT over_igbt_ia = OVER_PROTECT_DEFAULTS;
OVER_PROTECT over_igbt_ib = OVER_PROTECT_DEFAULTS;
OVER_PROTECT over_igbt_ic = OVER_PROTECT_DEFAULTS;

OVER_PROTECT over_sysiapeak = OVER_PROTECT_DEFAULTS;
OVER_PROTECT over_sysibpeak = OVER_PROTECT_DEFAULTS;
OVER_PROTECT over_sysicpeak = OVER_PROTECT_DEFAULTS;

OVER_PROTECT over_Ucapa = OVER_PROTECT_DEFAULTS;

OVER_PROTECT over_Udca = OVER_PROTECT_DEFAULTS;

OVER_PROTECT over_Idca = OVER_PROTECT_DEFAULTS;
OVER_PROTECT over_Idcb = OVER_PROTECT_DEFAULTS;
OVER_PROTECT over_Idcc = OVER_PROTECT_DEFAULTS;

OVER_PROTECT over_UaRms = OVER_PROTECT_DEFAULTS;
OVER_PROTECT over_UbRms = OVER_PROTECT_DEFAULTS;
OVER_PROTECT over_UcRms = OVER_PROTECT_DEFAULTS;

OVER_PROTECT over_IaRms = OVER_PROTECT_DEFAULTS;
OVER_PROTECT over_IbRms = OVER_PROTECT_DEFAULTS;
OVER_PROTECT over_IcRms = OVER_PROTECT_DEFAULTS;

OVER_PROTECT over_IacapRms = OVER_PROTECT_DEFAULTS;
OVER_PROTECT over_IbcapRms = OVER_PROTECT_DEFAULTS;
OVER_PROTECT over_IccapRms = OVER_PROTECT_DEFAULTS;

OVER_PROTECT over_SysIaRms = OVER_PROTECT_DEFAULTS;
OVER_PROTECT over_SysIbRms = OVER_PROTECT_DEFAULTS;
OVER_PROTECT over_SysIcRms = OVER_PROTECT_DEFAULTS;

UNDER_PROTECT under_udca = UNDER_PROTECT_DEFAULTS;
UNDER_PROTECT under_udcb = UNDER_PROTECT_DEFAULTS;
UNDER_PROTECT under_udcc = UNDER_PROTECT_DEFAULTS;

UNDER_PROTECT under_ucapa = UNDER_PROTECT_DEFAULTS;
UNDER_PROTECT under_ucapb = UNDER_PROTECT_DEFAULTS;
UNDER_PROTECT under_ucapc = UNDER_PROTECT_DEFAULTS;

UNDER_PROTECT under_ucapa1 = UNDER_PROTECT_DEFAULTS;
UNDER_PROTECT under_ucapb1 = UNDER_PROTECT_DEFAULTS;
UNDER_PROTECT under_ucapc1 = UNDER_PROTECT_DEFAULTS;

UNDER_PROTECT under_loadarms = UNDER_PROTECT_DEFAULTS;
UNDER_PROTECT under_loadbrms = UNDER_PROTECT_DEFAULTS;
UNDER_PROTECT under_loadcrms = UNDER_PROTECT_DEFAULTS;

void FaultProtInit(void)
{

    EmergencyFault.ActDelay = ParaData.FaultProtect.EmergencyFaultDly;

    over_sysiapeak.ActDealy = ParaData.FaultProtect.OverIIgbtDly;
    over_sysiapeak.GreatValue = (float)ParaData.FaultProtect.OverIgbtIPeak;
    over_sysiapeak.flag.All = 0;

    over_sysibpeak.ActDealy = ParaData.FaultProtect.OverIIgbtDly;
    over_sysibpeak.GreatValue = (float)ParaData.FaultProtect.OverIgbtIPeak;
    over_sysibpeak.flag.All = 0;

    over_sysicpeak.ActDealy = ParaData.FaultProtect.OverIIgbtDly;
    over_sysicpeak.GreatValue = (float)ParaData.FaultProtect.OverIgbtIPeak;
    over_sysicpeak.flag.All = 0;

    over_igbt_ia.ActDealy = ParaData.FaultProtect.OverIIgbtDly;
    over_igbt_ia.GreatValue = (float)ParaData.FaultProtect.OverIgbtIPeak;
    over_igbt_ia.flag.All = 0;

    over_igbt_ib.ActDealy = over_igbt_ia.ActDealy;
    over_igbt_ib.GreatValue = over_igbt_ia.GreatValue;
    over_igbt_ib.flag.All = 0;

    over_igbt_ic.ActDealy = over_igbt_ia.ActDealy;
    over_igbt_ic.GreatValue = over_igbt_ia.GreatValue;
    over_igbt_ic.flag.All = 0;

    over_Udca.ActDealy = 2*ParaData.FaultProtect.OverUdcDly;
    over_Udca.GreatValue = 860;//1.10*((float)ParaData.FaultProtect.OverUdcPeak);
    over_Udca.flag.All = 0;

    over_Ucapa.ActDealy = 4*ParaData.FaultProtect.OverUdcDly;
    over_Ucapa.GreatValue = (float)ParaData.FaultProtect.OverUdcPeak;
    over_Ucapa.flag.All = 0;

    under_udca.ActDealy = ParaData.FaultProtect.UnderUdcDly;
    under_udca.UnderValue = 0.75*((float)ParaData.FaultProtect.UnderUdc);
    under_udca.flag.All = 0;

    under_ucapa.ActDealy = ParaData.FaultProtect.UnderUdcDly;
    under_ucapa.UnderValue = (float)ParaData.FaultProtect.UnderUdc;
    under_ucapa.flag.All = 0;

    under_ucapa1.ActDealy = 2*ParaData.FaultProtect.UnderUdcDly;
    under_ucapa1.UnderValue = 0.7*(float)ParaData.FaultProtect.UnderUdc;
    under_ucapa1.flag.All = 0;


    over_Idca.ActDealy = ParaData.FaultProtect.OverIdcDly;
    over_Idca.GreatValue = (float)ParaData.FaultProtect.OverIdc;
    over_Idca.flag.All = 0;

    over_Idcb.ActDealy = ParaData.FaultProtect.OverIdcDly;
    over_Idcb.GreatValue = (float)ParaData.FaultProtect.OverIdc;
    over_Idcb.flag.All = 0;

    over_Idcc.ActDealy = ParaData.FaultProtect.OverIdcDly;
    over_Idcc.GreatValue = (float)ParaData.FaultProtect.OverIdc;
    over_Idcc.flag.All = 0;

    over_SysIaRms.ActDealy = ParaData.FaultProtect.OverSysIRmsDly;
    over_SysIaRms.GreatValue = (float)ParaData.FaultProtect.OverSysIRms;
    over_SysIaRms.flag.All = 0;

    over_SysIbRms.ActDealy = ParaData.FaultProtect.OverSysIRmsDly;
    over_SysIbRms.GreatValue = (float)ParaData.FaultProtect.OverSysIRms;
    over_SysIbRms.flag.All = 0;

    over_SysIcRms.ActDealy = ParaData.FaultProtect.OverSysIRmsDly;
    over_SysIcRms.GreatValue = (float)ParaData.FaultProtect.OverSysIRms;
    over_SysIcRms.flag.All = 0;

    over_IacapRms.ActDealy = ParaData.FaultProtect.OverIcapRmsDly;
    over_IacapRms.GreatValue = (float)ParaData.FaultProtect.OverIcapRms;
    over_IacapRms.flag.All = 0;

    over_IbcapRms.ActDealy = ParaData.FaultProtect.OverIcapRmsDly;
    over_IbcapRms.GreatValue = (float)ParaData.FaultProtect.OverIcapRms;
    over_IbcapRms.flag.All = 0;

    over_IccapRms.ActDealy = ParaData.FaultProtect.OverIcapRmsDly;
    over_IccapRms.GreatValue = (float)ParaData.FaultProtect.OverIcapRms;
    over_IccapRms.flag.All = 0;

    over_UaRms.ActDealy = ParaData.FaultProtect.OverURmsDly;
    over_UaRms.GreatValue = (float)ParaData.FaultProtect.OverURms;
    over_UaRms.flag.All = 0;

    over_UbRms.ActDealy = ParaData.FaultProtect.OverURmsDly;
    over_UbRms.GreatValue = (float)ParaData.FaultProtect.OverURms;
    over_UbRms.flag.All = 0;

    over_UcRms.ActDealy = ParaData.FaultProtect.OverURmsDly;
    over_UcRms.GreatValue = (float)ParaData.FaultProtect.OverURms;
    over_UcRms.flag.All = 0;

    over_IaRms.ActDealy = ParaData.FaultProtect.OverIRmsDly;
    over_IaRms.GreatValue = (float)ParaData.FaultProtect.OverIRms;
    over_IaRms.flag.All = 0;

    over_IbRms.ActDealy = ParaData.FaultProtect.OverIRmsDly;
    over_IbRms.GreatValue = (float)ParaData.FaultProtect.OverIRms;
    over_IbRms.flag.All = 0;

    over_IcRms.ActDealy = ParaData.FaultProtect.OverIRmsDly;
    over_IcRms.GreatValue = (float)ParaData.FaultProtect.OverIRms;
    over_IcRms.flag.All = 0;

    under_loadarms.ActDealy = ParaData.FaultProtect.UnderUrmsDly;
    under_loadarms.UnderValue = (float)ParaData.FaultProtect.UnderURms;
    under_loadarms.flag.All = 0;

    under_loadbrms.ActDealy = ParaData.FaultProtect.UnderUrmsDly;
    under_loadbrms.UnderValue = (float)ParaData.FaultProtect.UnderURms;
    under_loadbrms.flag.All = 0;

    under_loadcrms.ActDealy =ParaData.FaultProtect.UnderUrmsDly;
    under_loadcrms.UnderValue = (float)ParaData.FaultProtect.UnderURms;
    under_loadcrms.flag.All = 0;

}

#pragma CODE_SECTION(FastFaultProtProc,"ramfuncs");

void FastFaultProtProc(void)
{

    static int16 dly_faulta = 0;
    static int16 dly_faultscr = 0;

    if(RunData.StateMachine.StateMachine != Running)
    {
        if((RunData.StateMachine.McwReg.bits.Reset==1) && (RunData.StateMachine.PreMcwReg.bits.Reset==0))
        {
            FaultProtInit();
            CanA_reset();
        }

    }
//急停故障

    EmergencyFault.flag.bits.TonEn = ((~RunData.STATUS_CPLD0)>>1)&0x0001;
    EmergencyFault.flag.bits.Reset = RunData.StateMachine.MswReg.bits.reset;
    EmergencyFault.calc(&EmergencyFault);
    if((RunData.StateMachine.FaultCode3Reg.bits.EmergentStop == 0)&&EmergencyFault.flag.bits.TOut)
    {
        RunData.StateMachine.FaultCode3Reg.bits.EmergentStop = 1;
    }

    over_Udca.input = fabs(RunData.FilteredData.Udc);
    over_Udca.flag.bits.Reset = RunData.StateMachine.MswReg.bits.reset;
    over_Udca.calc(&over_Udca);
    if((RunData.StateMachine.FaultCode0Reg.bits.OverUdca == 0)&&over_Udca.flag.bits.Status)
    {
        RunData.StateMachine.FaultCode0Reg.bits.OverUdca = 1;
    }

    over_Ucapa.input = fabs(RunData.GridData.Ucapa_vol);
    over_Ucapa.flag.bits.Reset = RunData.StateMachine.MswReg.bits.reset;
    over_Ucapa.calc(&over_Ucapa);
    if((RunData.StateMachine.FaultCode3Reg.bits.OverSpcUA  == 0)&&over_Ucapa.flag.bits.Status)
    {
        RunData.StateMachine.FaultCode3Reg.bits.OverSpcUA  = 1;
    }

    over_igbt_ia.input = fabs(RunData.FilteredData.IgbtIa0);
    over_igbt_ia.flag.bits.Reset = RunData.StateMachine.MswReg.bits.reset;
    over_igbt_ia.calc(&over_igbt_ia);
    if((RunData.StateMachine.FaultCode0Reg.bits.OverAMoudle1Ipeak == 0)&&over_igbt_ia.flag.bits.Status)
    {
        RunData.StateMachine.FaultCode0Reg.bits.OverAMoudle1Ipeak = 1;

    }

    over_igbt_ib.input = fabs(RunData.FilteredData.IgbtIb0);
    over_igbt_ib.flag.bits.Reset = RunData.StateMachine.MswReg.bits.reset;
    over_igbt_ib.calc(&over_igbt_ib);
    if((RunData.StateMachine.FaultCode0Reg.bits.OverBMoudle1Ipeak == 0)&&over_igbt_ib.flag.bits.Status)
    {
        RunData.StateMachine.FaultCode0Reg.bits.OverBMoudle1Ipeak = 1;
    }

    over_igbt_ic.input = fabs(RunData.FilteredData.IgbtIc0);
    over_igbt_ic.flag.bits.Reset = RunData.StateMachine.MswReg.bits.reset;
    over_igbt_ic.calc(&over_igbt_ic);
    if((RunData.StateMachine.FaultCode0Reg.bits.OverCMoudle1Ipeak == 0)&&over_igbt_ic.flag.bits.Status)
    {
        RunData.StateMachine.FaultCode0Reg.bits.OverCMoudle1Ipeak = 1;
    }

/*  over_sysiapeak.input = fabs(RunData.FilteredData.SysIa1);
    over_sysiapeak.flag.bits.Reset = RunData.StateMachine.MswReg.bits.reset;
    over_sysiapeak.calc(&over_sysiapeak);
    if((RunData.StateMachine.FaultCode1Reg.bits.OversysIapeak == 0)&&over_sysiapeak.flag.bits.Status)
    {
        RunData.StateMachine.FaultCode1Reg.bits.OversysIapeak = 1;
    }

    over_sysibpeak.input = fabs(RunData.FilteredData.SysIb1);
    over_sysibpeak.flag.bits.Reset = RunData.StateMachine.MswReg.bits.reset;
    over_sysibpeak.calc(&over_sysibpeak);
    if((RunData.StateMachine.FaultCode1Reg.bits.OversysIbpeak == 0)&&over_sysibpeak.flag.bits.Status)
    {
        RunData.StateMachine.FaultCode1Reg.bits.OversysIbpeak = 1;
    }

    over_sysicpeak.input = fabs(RunData.FilteredData.SysIc1);
    over_sysicpeak.flag.bits.Reset = RunData.StateMachine.MswReg.bits.reset;
    over_sysicpeak.calc(&over_sysicpeak);
    if((RunData.StateMachine.FaultCode1Reg.bits.OversysIcpeak == 0)&&over_sysicpeak.flag.bits.Status)
    {
        RunData.StateMachine.FaultCode1Reg.bits.OversysIcpeak = 1;
    }*/


    if(RunData.StateMachine.MswReg.bits.GridCompen==0)
    {
        dly_faultscr++;
        if(dly_faultscr>200)
        {
            dly_faultscr = 205;
        }
    }
    else
    {
        dly_faultscr = 0;
    }

/*  if((dly_faultscr>100)&&(RunData.StateMachine.MswReg.bits.GridCompen==0)&&(RunData.StateMachine.MswReg.bits.Charging||RunData.StateMachine.MswReg.bits.Running))
        {
            if((RunData.InvControlOutput.Invline_Vd < 0.85*RunData.InvControlOutput.Gridline_Ud)&&(RunData.GridData.GridUaRms>40))
            {
                 dly_faulta++;
            }
            else
            {
                 dly_faulta = 0;
            }
            if( dly_faulta >15)
            {
                RunData.StateMachine.FaultCode4Reg.bits.BreakScrA = 1;
                RunData.StateMachine.FaultCode4Reg.bits.BreakScrB = 1;
                RunData.StateMachine.FaultCode4Reg.bits.BreakScrC = 1;
                dly_faulta = 0;
            }

        }*/

    if((RunData.StateMachine.FaultCode0Reg.all) \
            ||(RunData.StateMachine.FaultCode1Reg.all) \
            ||(RunData.StateMachine.FaultCode2Reg.all) \
            ||(RunData.StateMachine.FaultCode3Reg.all) \
            ||(RunData.StateMachine.FaultCode4Reg.bits.op_slave) )
    {
        CLOSED_PWM();
        RunData.StateMachine.StateMachine = Fault;
        RunData.StateMachine.MswReg.bits.Fault = 1;

    }

    if(RunData.StateMachine.FaultCode4Reg.bits.BreakScrA \
            ||RunData.StateMachine.FaultCode4Reg.bits.BreakScrB \
            ||RunData.StateMachine.FaultCode4Reg.bits.BreakScrC  )
    {

        RunData.StateMachine.StateMachine = Fault;
    //  RunData.StateMachine.MswReg.bits.Fault = 1;
    }



}


#pragma CODE_SECTION(RmsProtect,"ramfuncs");

void RmsProtect(void)
{

    static int16 dly_fault_seq = 0;

    if((RunData.StateMachine.McwReg.bits.Enableseq)&&(RunData.GridData.GridUaRms > 160)&&(RunData.GridData.GridUbRms > 160)&&(RunData.GridData.GridUcRms > 160))
    {
        if(RunData.InvControlOutput.GridUd < 220)
        {
            dly_fault_seq ++;
            if(dly_fault_seq > 5)
            {
                RunData.StateMachine.FaultCode0Reg.bits.PhaSequFault = 1;
            }
        }
        else
        {
            dly_fault_seq = 0;
        }
    }
    else
    {
        dly_fault_seq = 0;
    }

    if(RunData.StateMachine.MswReg.bits.GridCompen)
    {
       under_ucapa.flag.bits.Reset = 0;
       under_ucapa.input = RunData.GridData.Ucapa_vol;
       under_ucapa.calc(&under_ucapa);
       if((RunData.StateMachine.FaultCode3Reg.bits.LowerSpcUA == 0)&&under_ucapa.flag.bits.Status)
       {
            RunData.StateMachine.FaultCode3Reg.bits.LowerSpcUA = 1;
       }

     }

    if(RunData.StateMachine.StateMachine == Running)
    {
        under_udca.flag.bits.Reset = 0;

        if(RunData.StateMachine.MswReg.bits.Gridabnomal ==0)
        {
            under_udca.input = RunData.GridData.Udca_vol;
            under_udca.calc(&under_udca);
            if((RunData.StateMachine.FaultCode0Reg.bits.UnderUdca == 0)&&under_udca.flag.bits.Status)
            {
                RunData.StateMachine.FaultCode0Reg.bits.UnderUdca = 1;
            }
        }
        under_ucapa1.flag.bits.Reset = 0;
        under_ucapa1.input = RunData.GridData.Ucapa_vol;
        under_ucapa1.calc(&under_ucapa1);
        if((RunData.StateMachine.FaultCode3Reg.bits.LowerSpcUA == 0)&&under_ucapa1.flag.bits.Status)
        {
            RunData.StateMachine.FaultCode3Reg.bits.LowerSpcUA = 1;
        }


    }

    if(RunData.StateMachine.MswReg.bits.reset)
    {
        under_udca.flag.bits.Reset = RunData.StateMachine.MswReg.bits.reset;
        under_udca.calc(&under_udca);

        under_ucapa.flag.bits.Reset = RunData.StateMachine.MswReg.bits.reset;
        under_ucapa.calc(&under_ucapa);

        under_ucapa1.flag.bits.Reset = RunData.StateMachine.MswReg.bits.reset;
        under_ucapa1.calc(&under_ucapa1);

        under_loadarms.flag.bits.Reset = RunData.StateMachine.MswReg.bits.reset;
        under_loadarms.calc(&under_loadarms);
        under_loadbrms.flag.bits.Reset = RunData.StateMachine.MswReg.bits.reset;
        under_loadbrms.calc(&under_loadbrms);
        under_loadcrms.flag.bits.Reset = RunData.StateMachine.MswReg.bits.reset;
        under_loadcrms.calc(&under_loadcrms);

        over_UaRms.flag.bits.Reset = RunData.StateMachine.MswReg.bits.reset;
        over_UaRms.calc(&over_UaRms);

        over_UbRms.flag.bits.Reset = RunData.StateMachine.MswReg.bits.reset;
        over_UbRms.calc(&over_UbRms);

        over_UcRms.flag.bits.Reset = RunData.StateMachine.MswReg.bits.reset;
        over_UcRms.calc(&over_UcRms);

    }

    if(RunData.StateMachine.MswReg.bits.GridCompen)
    {
        under_loadarms.flag.bits.Reset = 0;
        under_loadbrms.flag.bits.Reset = 0;
        under_loadcrms.flag.bits.Reset = 0;

        over_UaRms.flag.bits.Reset = 0;
        over_UbRms.flag.bits.Reset = 0;
        over_UcRms.flag.bits.Reset = 0;

        under_loadarms.input = RunData.GridData.LoadUaRms;
        under_loadarms.calc(&under_loadarms);
        if((RunData.StateMachine.FaultCode3Reg.bits.DVROutUnderFault==0)&&under_loadarms.flag.bits.Status)
        {
            RunData.StateMachine.FaultCode3Reg.bits.DVROutUnderFault = 1;
        }
        under_loadbrms.input = RunData.GridData.LoadUbRms;
        under_loadbrms.calc(&under_loadbrms);
        if((RunData.StateMachine.FaultCode3Reg.bits.DVROutUnderFault==0)&&under_loadbrms.flag.bits.Status)
        {
            RunData.StateMachine.FaultCode3Reg.bits.DVROutUnderFault = 1;
        }
        under_loadcrms.input = RunData.GridData.LoadUcRms;
        under_loadcrms.calc(&under_loadcrms);
        if((RunData.StateMachine.FaultCode3Reg.bits.DVROutUnderFault==0)&&under_loadcrms.flag.bits.Status)
        {
            RunData.StateMachine.FaultCode3Reg.bits.DVROutUnderFault = 1;
        }

         over_UaRms.input = RunData.GridData.LoadUaRms;
         over_UaRms.calc(&over_UaRms);
         if((RunData.StateMachine.FaultCode2Reg.bits.OverInvUA == 0)&&over_UaRms.flag.bits.Status)
         {
                RunData.StateMachine.FaultCode2Reg.bits.OverInvUA = 1;
         }
         over_UbRms.input = RunData.GridData.LoadUbRms;
         over_UbRms.calc(&over_UbRms);
         if((RunData.StateMachine.FaultCode2Reg.bits.OverInvUB == 0)&&over_UbRms.flag.bits.Status)
         {
                RunData.StateMachine.FaultCode2Reg.bits.OverInvUB = 1;
         }
         over_UcRms.input = RunData.GridData.LoadUcRms;
         over_UcRms.calc(&over_UcRms);
         if((RunData.StateMachine.FaultCode2Reg.bits.OverInvUC == 0)&&over_UcRms.flag.bits.Status)
         {
                RunData.StateMachine.FaultCode2Reg.bits.OverInvUC = 1;
         }



    }


/*  over_Idca.input = fabs(RunData.GridData.Udca_cur);
    over_Idca.flag.bits.Reset = RunData.StateMachine.MswReg.bits.reset;
    over_Idca.calc(&over_Idca);
    if((RunData.StateMachine.FaultCode2Reg.bits.OverUdcIA == 0)&&over_Idca.flag.bits.Status)
    {
        RunData.StateMachine.FaultCode2Reg.bits.OverUdcIA = 1;
    }

    over_Idcb.input = fabs(RunData.GridData.Udcb_cur);
    over_Idcb.flag.bits.Reset = RunData.StateMachine.MswReg.bits.reset;
    over_Idcb.calc(&over_Idcb);
    if((RunData.StateMachine.FaultCode2Reg.bits.OverUdcIB == 0)&&over_Idcb.flag.bits.Status)
    {
        RunData.StateMachine.FaultCode2Reg.bits.OverUdcIB = 1;
    }

    over_Idcc.input = fabs(RunData.GridData.Udcc_cur);
    over_Idcc.flag.bits.Reset = RunData.StateMachine.MswReg.bits.reset;
    over_Idcc.calc(&over_Idcc);
    if((RunData.StateMachine.FaultCode2Reg.bits.OverUdcIC == 0)&&over_Idcc.flag.bits.Status)
    {
        RunData.StateMachine.FaultCode2Reg.bits.OverUdcIC = 1;
    }
*/


     over_IaRms.input = RunData.GridData.GridIaRms;
     over_IaRms.flag.bits.Reset = RunData.StateMachine.MswReg.bits.reset;
     over_IaRms.calc(&over_IaRms);
     if((RunData.StateMachine.FaultCode0Reg.bits.OverOutIA == 0)&&over_IaRms.flag.bits.Status)
     {
            RunData.StateMachine.FaultCode0Reg.bits.OverOutIA = 1;
     }

     over_IbRms.input = RunData.GridData.GridIbRms;
     over_IbRms.flag.bits.Reset = RunData.StateMachine.MswReg.bits.reset;
     over_IbRms.calc(&over_IbRms);
     if((RunData.StateMachine.FaultCode0Reg.bits.OverOutIB == 0)&&over_IbRms.flag.bits.Status)
     {
            RunData.StateMachine.FaultCode0Reg.bits.OverOutIB = 1;
     }

     over_IcRms.input = RunData.GridData.GridIcRms;
     over_IcRms.flag.bits.Reset = RunData.StateMachine.MswReg.bits.reset;
     over_IcRms.calc(&over_IcRms);
     if((RunData.StateMachine.FaultCode0Reg.bits.OverOutIC == 0)&&over_IcRms.flag.bits.Status)
     {
            RunData.StateMachine.FaultCode0Reg.bits.OverOutIC = 1;
     }

     over_SysIaRms.input = RunData.GridData.SysIaRms;
     over_SysIaRms.flag.bits.Reset = RunData.StateMachine.MswReg.bits.reset;
     over_SysIaRms.calc(&over_SysIaRms);
     if((RunData.StateMachine.FaultCode0Reg.bits.OverSysIA == 0)&&over_SysIaRms.flag.bits.Status)
     {
            RunData.StateMachine.FaultCode0Reg.bits.OverSysIA = 1;
     }

     over_SysIbRms.input = RunData.GridData.SysIbRms;
     over_SysIbRms.flag.bits.Reset = RunData.StateMachine.MswReg.bits.reset;
     over_SysIaRms.calc(&over_SysIbRms);
     if((RunData.StateMachine.FaultCode0Reg.bits.OverSysIB == 0)&&over_SysIbRms.flag.bits.Status)
     {
            RunData.StateMachine.FaultCode0Reg.bits.OverSysIB = 1;
     }

     over_SysIcRms.input = RunData.GridData.SysIcRms;
     over_SysIcRms.flag.bits.Reset = RunData.StateMachine.MswReg.bits.reset;
     over_SysIcRms.calc(&over_SysIcRms);
     if((RunData.StateMachine.FaultCode0Reg.bits.OverSysIC == 0)&&over_SysIcRms.flag.bits.Status)
     {
            RunData.StateMachine.FaultCode0Reg.bits.OverSysIC = 1;
     }

     over_IacapRms.input = RunData.GridData.CapIaRms;
     over_IacapRms.flag.bits.Reset = RunData.StateMachine.MswReg.bits.reset;
     over_IacapRms.calc(&over_IacapRms);
     if((RunData.StateMachine.FaultCode1Reg.bits.OvercapIa == 0)&&over_IacapRms.flag.bits.Status)
     {
         RunData.StateMachine.FaultCode1Reg.bits.OvercapIa = 1;
     }

     over_IbcapRms.input = RunData.GridData.CapIbRms;
     over_IbcapRms.flag.bits.Reset = RunData.StateMachine.MswReg.bits.reset;
     over_IbcapRms.calc(&over_IbcapRms);
     if((RunData.StateMachine.FaultCode1Reg.bits.OvercapIb == 0)&&over_IbcapRms.flag.bits.Status)
     {
         RunData.StateMachine.FaultCode1Reg.bits.OvercapIb = 1;
     }

     over_IccapRms.input = RunData.GridData.CapIcRms;
     over_IccapRms.flag.bits.Reset = RunData.StateMachine.MswReg.bits.reset;
     over_IccapRms.calc(&over_IccapRms);
     if((RunData.StateMachine.FaultCode1Reg.bits.OvercapIc == 0)&&over_IccapRms.flag.bits.Status)
     {
         RunData.StateMachine.FaultCode1Reg.bits.OvercapIc = 1;
     }


     if((RunData.StateMachine.FaultCode0Reg.all) \
             ||(RunData.StateMachine.FaultCode1Reg.all) \
             ||(RunData.StateMachine.FaultCode2Reg.all) \
             ||(RunData.StateMachine.FaultCode3Reg.all) \
             ||(RunData.StateMachine.FaultCode4Reg.bits.op_slave) )
     {
         CLOSED_PWM();
        RunData.StateMachine.StateMachine = Fault;
        RunData.StateMachine.MswReg.bits.Fault = 1;
     }

    if(RunData.StateMachine.FaultCode4Reg.bits.BreakScrA||RunData.StateMachine.FaultCode4Reg.bits.BreakScrB||RunData.StateMachine.FaultCode4Reg.bits.BreakScrC)
    {

        RunData.StateMachine.StateMachine = Fault;
    //  RunData.StateMachine.MswReg.bits.Fault = 1;
    }

}

void over_protect_calc(OVER_PROTECT *v)
{
    float back;

    back = v->GreatValue*0.98;
    if(v->input >= v->GreatValue)
    {
        v->cnt++;
        if(v->cnt >= v->ActDealy)
        {
            v->flag.bits.Status = 1;
            v->cnt = v->ActDealy;
        }
    }
    else if(v->input < back)
    {
        v->cnt = 0;
    }
    if(v->flag.bits.Reset)
    {
        v->flag.bits.Status = 0;
        v->cnt = 0;
    }
}


void under_protect_calc(UNDER_PROTECT *v)
{
    float back;

    back = v->UnderValue*1.02;

    if(v->input <= v->UnderValue)
    {
        v->cnt++;
        if(v->cnt >= v->ActDealy)
        {
            v->flag.bits.Status = 1;
            v->cnt = v->ActDealy;
        }
    }
    else if(v->input > back)
    {
        v->cnt = 0;
    }
    if(v->flag.bits.Reset)
    {
        v->flag.bits.Status = 0;
        v->cnt = 0;
    }
}


void timer_delay_protect_calc(TIMER_DLEAY *v)
{
    if(v->flag.bits.TonEn)
    {
        v->cnt++;
        if(v->cnt > v->ActDelay)
        {
            v->cnt = v->ActDelay;
            v->flag.bits.TOut = 1;
        }
    }
    else
    {
        v->flag.bits.TOut = 0;
        v->cnt = 0;
    }

}

