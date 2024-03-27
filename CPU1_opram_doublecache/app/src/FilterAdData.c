/*
 * FilterAdData.c
 * Created on: 2018-7-10
 * Author: xiaogang
 */


#include "FilterAdData.h"
#include "Dev_Init.h"
#include "Const_Defines.h"
#include "Global_struct.h"
#include "Temperature.h"
#include "Inv_CalFun.h"
#include "math.h"

NTC_K ntc_k= {-28.609,20.4,-2.074,0.1137,-0.0029,0.00003};//300R //{-26.8,8.1176,-0.2618,0.0035};680R
NTC_Module ntc_module={-8.5337,9.8072,-0.4264,0.0104,-0.00009};     //  {-10.228,9.1576,-0.3739,0.0086,-0.00007}  340濠电偛鏌岄崘鍓э拷锟�

THREE_PHASE_RMS_CAL GridLineVolRms = THREE_PHASE_RMS_CAL_DEFAULTS;
THREE_PHASE_RMS_CAL GridPhaseVolRms = THREE_PHASE_RMS_CAL_DEFAULTS;
THREE_PHASE_RMS_CAL GridCurRms = THREE_PHASE_RMS_CAL_DEFAULTS;
THREE_PHASE_RMS_CAL CapCurRms = THREE_PHASE_RMS_CAL_DEFAULTS;

SINGAL_PHASE_RMS_CAL GridUaRms = SINGAL_PHASE_RMS_CAL_DEFAULTS;
SINGAL_PHASE_RMS_CAL GridUbRms = SINGAL_PHASE_RMS_CAL_DEFAULTS;
SINGAL_PHASE_RMS_CAL GridUcRms = SINGAL_PHASE_RMS_CAL_DEFAULTS;

SINGAL_PHASE_RMS_CAL LoadUaRms = SINGAL_PHASE_RMS_CAL_DEFAULTS;
SINGAL_PHASE_RMS_CAL LoadUbRms = SINGAL_PHASE_RMS_CAL_DEFAULTS;
SINGAL_PHASE_RMS_CAL LoadUcRms = SINGAL_PHASE_RMS_CAL_DEFAULTS;

SINGAL_PHASE_RMS_CAL GridIaRms = SINGAL_PHASE_RMS_CAL_DEFAULTS;
SINGAL_PHASE_RMS_CAL GridIbRms = SINGAL_PHASE_RMS_CAL_DEFAULTS;
SINGAL_PHASE_RMS_CAL GridIcRms = SINGAL_PHASE_RMS_CAL_DEFAULTS;

SINGAL_PHASE_RMS_CAL SysIaRms = SINGAL_PHASE_RMS_CAL_DEFAULTS;
SINGAL_PHASE_RMS_CAL SysIbRms = SINGAL_PHASE_RMS_CAL_DEFAULTS;
SINGAL_PHASE_RMS_CAL SysIcRms = SINGAL_PHASE_RMS_CAL_DEFAULTS;

SINGAL_PHASE_RMS_CAL CapIaRms = SINGAL_PHASE_RMS_CAL_DEFAULTS;
SINGAL_PHASE_RMS_CAL CapIbRms = SINGAL_PHASE_RMS_CAL_DEFAULTS;
SINGAL_PHASE_RMS_CAL CapIcRms = SINGAL_PHASE_RMS_CAL_DEFAULTS;

LOW_PASS_FILTER ia_lpf = LOW_PASS_FILTER_DEFAULTS;
LOW_PASS_FILTER ib_lpf = LOW_PASS_FILTER_DEFAULTS;
LOW_PASS_FILTER ic_lpf = LOW_PASS_FILTER_DEFAULTS;

LOW_PASS_FILTER sys_ia_lpf = LOW_PASS_FILTER_DEFAULTS;
LOW_PASS_FILTER sys_ib_lpf = LOW_PASS_FILTER_DEFAULTS;
LOW_PASS_FILTER sys_ic_lpf = LOW_PASS_FILTER_DEFAULTS;

LOW_PASS_FILTER uab_lpf = LOW_PASS_FILTER_DEFAULTS;
LOW_PASS_FILTER ubc_lpf = LOW_PASS_FILTER_DEFAULTS;
LOW_PASS_FILTER uca_lpf = LOW_PASS_FILTER_DEFAULTS;

LOW_PASS_FILTER iacap_lpf = LOW_PASS_FILTER_DEFAULTS;
LOW_PASS_FILTER ibcap_lpf = LOW_PASS_FILTER_DEFAULTS;
LOW_PASS_FILTER iccap_lpf = LOW_PASS_FILTER_DEFAULTS;

LOW_PASS_FILTER ucapa_lpf = LOW_PASS_FILTER_DEFAULTS;

MEAN_PASS_FILTER ucapa_mpf = MEAN_PASS_FILTER_DEFAULTS;

LOW_PASS_FILTER udca_lpf = LOW_PASS_FILTER_DEFAULTS;

MEAN_PASS_FILTER vda_mpf = MEAN_PASS_FILTER_DEFAULTS;
MEAN_PASS_FILTER vdb_mpf = MEAN_PASS_FILTER_DEFAULTS;
MEAN_PASS_FILTER vdc_mpf = MEAN_PASS_FILTER_DEFAULTS;

INSTANTANEOUS_POWER_CAL GridPQ = INSTANTANEOUS_POWER_CAL_DEFAULTS;

LOW_PASS_FILTER GridPQ_P_lpf = LOW_PASS_FILTER_DEFAULTS;
LOW_PASS_FILTER GridPQ_Q_lpf = LOW_PASS_FILTER_DEFAULTS;


void FilterAdinit()
{

    ExAdcGain.Ad1A1Gain = 0.019531245;//-0.0244140625*1.04;//0.019531245;//GridAN//-0.0244140625
    ExAdcGain.Ad1A2Gain = ExAdcGain.Ad1A1Gain;//GridBN
    ExAdcGain.Ad1A3Gain = ExAdcGain.Ad1A1Gain;

    ExAdcGain.Ad1A4Gain = ExAdcGain.Ad1A1Gain; //LoadAN
    ExAdcGain.Ad1A5Gain = ExAdcGain.Ad1A1Gain;
    ExAdcGain.Ad1A6Gain = ExAdcGain.Ad1A1Gain;
#if 0
    ExAdcGain.Ad1A7Gain = -0.05425347222*1.08*(ParaData.InvCtr.Ugrid_filter_k/100);
    ExAdcGain.Ad3A4Gain = -0.05425347222*1.08*(ParaData.InvCtr.Uinv_filter_k/100);//
    ExAdcGain.Ad3A5Gain = -0.05425347222*1.08*(ParaData.InvCtr.Uinv_filter_k/100);//
#else
    ExAdcGain.Ad1A7Gain = 0.019531245*2.35*(ParaData.InvCtr.Ugrid_filter_k/100);//UDC1
    ExAdcGain.Ad3A4Gain = 0.019531245*2.35*(ParaData.InvCtr.Uinv_filter_k/100);
    ExAdcGain.Ad3A5Gain =  0.019531245*2.35*(ParaData.InvCtr.Uinv_filter_k/100);
#endif
  /*     ExAdcGain.Ad1A7Gain = 0.019531245*2.35*(ParaData.InvCtr.Ugrid_filter_k/100);//UDC1
       ExAdcGain.Ad3A4Gain = 0.019531245*2.35*(ParaData.InvCtr.Uinv_filter_k/100);
       ExAdcGain.Ad3A5Gain = 0.019531245*2.35*(ParaData.InvCtr.Uinv_filter_k/100);*/
#ifdef BYPASS_NO_FAULT
    ExAdcGain.Ad1A8Gain = 0.009155273*(float)(ParaData.Sys_Cur_gain/100);//IGBTA1  500/4
    ExAdcGain.Ad2A1Gain = 0.009155273*(float)(ParaData.Sys_Cur_gain/100);//
    ExAdcGain.Ad2A2Gain = 0.009155273*(float)(ParaData.Sys_Cur_gain/100);//
#else
       ExAdcGain.Ad1A8Gain = 0.009155273*(float)(400/100);//IGBTA1  500/4
       ExAdcGain.Ad2A1Gain = 0.009155273*(float)(400/100);//
       ExAdcGain.Ad2A2Gain = 0.009155273*(float)(400/100);//
#endif
       ExAdcGain.Ad2A3Gain = 0.009155273*(float)(ParaData.Sys_Cur_gain/100);//systemIa  500/4
       ExAdcGain.Ad2A4Gain = 0.009155273*(float)(ParaData.Sys_Cur_gain/100);//
       ExAdcGain.Ad2A5Gain = 0.009155273*(float)(ParaData.Sys_Cur_gain/100);//

       ExAdcGain.Ad2A6Gain = 0.009155273*(float)(ParaData.Sys_Cur_gain/100);//IGBTA2  500/4
       ExAdcGain.Ad2A7Gain = 0.009155273*(float)(ParaData.Sys_Cur_gain/100);//
       ExAdcGain.Ad2A8Gain = 0.009155273*(float)(ParaData.Sys_Cur_gain/100);//
       ExAdcGain.Ad3A6Gain = 0.009155273/2;//  cap
       ExAdcGain.Ad3A7Gain = 0.009155273/2;//
       ExAdcGain.Ad3A8Gain = 0.009155273/2;//

       ExAdcGain.Ad3A1Gain = 0.019531245;//AB
       ExAdcGain.Ad3A2Gain = 0.019531245;//
       ExAdcGain.Ad3A3Gain = 0.019531245;


    AdcGain.AdChA0Gain = 0.01;     //
    AdcGain.AdChB0Gain = 0.01;        //
    AdcGain.AdChA1Gain = 0.48828125;
    AdcGain.AdChB1Gain = 0.01;       //
    AdcGain.AdChA2Gain = 0.48828125;
    AdcGain.AdChB2Gain = 0.01;
    AdcGain.AdChA3Gain = 0.030517578125;
    AdcGain.AdChB3Gain = 0.01;
    AdcGain.AdChA4Gain = 0.030517578125;
    AdcGain.AdChB4Gain = 0.01;
    AdcGain.AdChA5Gain = 0.030517578125;
    AdcGain.AdChB5Gain = 0.01;
    AdcGain.AdChA6Gain = 0.426136*1.2;
    AdcGain.AdChB6Gain = 0.01;
    AdcGain.AdChA7Gain = 0.426136*1.2;
    AdcGain.AdChB7Gain = 1;

    AdcObj.adChZero->A0ZERO = 10;
    AdcObj.adChZero->B0ZERO = 10;
    AdcObj.adChZero->A1ZERO = 2040;
    AdcObj.adChZero->B1ZERO = 10;
    AdcObj.adChZero->A2ZERO = 2040;
    AdcObj.adChZero->B2ZERO = 10;
    AdcObj.adChZero->A3ZERO = 2040;
    AdcObj.adChZero->B3ZERO = 10;
    AdcObj.adChZero->A4ZERO = 2040;
    AdcObj.adChZero->B4ZERO = 10;
    AdcObj.adChZero->A5ZERO = 2040;
    AdcObj.adChZero->B5ZERO = 10;
    AdcObj.adChZero->A6ZERO = 2040;
    AdcObj.adChZero->B6ZERO = 10;
    AdcObj.adChZero->A7ZERO = 2040;
    AdcObj.adChZero->B7ZERO = 10;

//	AdcObj.adChZero = &AdcChZero;
	AdcObj.adc_gain = &AdcGain;
	AdcObj.adresult = &RunData.Adresult;

//	ExAdcObj.ex_adChZero = &ExAdcChZero;
	ExAdcObj.ex_adc_gain = &ExAdcGain;
	ExAdcObj.ex_adresult = &RunData.ExAdresult;
	ExAdcObj.run = (void (*)(Uint32))GetExAdResult;

	moduleA_TEMP.ntcmodule = &ntc_module;
	moduleB_TEMP.ntcmodule = &ntc_module;
	moduleC_TEMP.ntcmodule = &ntc_module;
	ambient_ntc.ntck = &ntc_k;
	ambient_ntc1.ntck = &ntc_k;
	SCR_ntc.ntck = &ntc_k;
	CAP_ntc.ntck = &ntc_k;

//	OutputXbarRegs.OUTPUT7MUX0TO15CFG.bit.MUX14 = 3;
	OutputXbarRegs.OUTPUT7MUXENABLE.bit.MUX14 = 1;
	InputXbarRegs.INPUT5SELECT = 29;

}


//#pragma CODE_SECTION(FilterAdData,"ramfuncs");

void FilterAdData()
{
	RunData.FilteredData.IgbtIa0 = IGBT_IA;
	RunData.FilteredData.IgbtIb0 = IGBT_IB;
	RunData.FilteredData.IgbtIc0 = IGBT_IC;

	RunData.FilteredData.CapIa0 = CAP_IA;
    RunData.FilteredData.CapIb0 = -CAP_IA-CAP_IC;
    RunData.FilteredData.CapIc0 = CAP_IC;

	RunData.FilteredData.GridUa0 = UGAN;
	RunData.FilteredData.GridUb0 = UGBN;
	RunData.FilteredData.GridUc0 = UGCN;

	RunData.FilteredData.LoadUa0 = ULAN;
	RunData.FilteredData.LoadUb0 = ULBN;
	RunData.FilteredData.LoadUc0 = ULCN;

	RunData.FilteredData.SysIa0 = SYSTEM_IA;
	RunData.FilteredData.SysIb0 = SYSTEM_IB;
	RunData.FilteredData.SysIc0 = SYSTEM_IC;

	RunData.FilteredData.Udc = UDCA;
    RunData.FilteredData.Ucap = UDCB;

    ia_lpf.x = RunData.FilteredData.IgbtIa0;
    ia_lpf.calc(&ia_lpf);
    ib_lpf.x = RunData.FilteredData.IgbtIb0;
    ib_lpf.calc(&ib_lpf);
    ic_lpf.x = RunData.FilteredData.IgbtIc0;
    ic_lpf.calc(&ic_lpf);
    RunData.FilteredData.IgbtIa1 = ia_lpf.y;
    RunData.FilteredData.IgbtIb1 = ib_lpf.y;
    RunData.FilteredData.IgbtIc1 = ic_lpf.y;

    sys_ia_lpf.x = RunData.FilteredData.SysIa0;
    sys_ia_lpf.calc(&sys_ia_lpf);
    sys_ib_lpf.x = RunData.FilteredData.SysIb0;
    sys_ib_lpf.calc(&sys_ib_lpf);
    sys_ic_lpf.x = RunData.FilteredData.SysIc0;
    sys_ic_lpf.calc(&sys_ic_lpf);
    RunData.FilteredData.SysIa1 = sys_ia_lpf.y;
    RunData.FilteredData.SysIb1 = sys_ib_lpf.y;
    RunData.FilteredData.SysIc1 = sys_ic_lpf.y;
}

void CaltGridInit()
{
    udca_lpf.fc = 100;
    udca_lpf.ts = 0.001;

    ia_lpf.fc = 1500;
    ib_lpf.fc = 1500;
    ic_lpf.fc = 1500;

    ia_lpf.ts = 0.0001;
    ib_lpf.ts = 0.0001;
    ic_lpf.ts = 0.0001;

    uab_lpf.fc = 1500;
    ubc_lpf.fc = 1500;
    uca_lpf.fc = 1500;

    iacap_lpf.fc = 1500;
    ibcap_lpf.fc = 1500;
    iccap_lpf.fc = 1500;

    sys_ia_lpf.fc = 2000;
    sys_ib_lpf.fc = 2000;
    sys_ic_lpf.fc = 2000;
    sys_ia_lpf.ts = 0.0001;
    sys_ib_lpf.ts = 0.0001;
    sys_ic_lpf.ts = 0.0001;

    ucapa_mpf.k = 0.04;

    vda_mpf.k = 0.02;
    vdb_mpf.k = 0.02;
    vdc_mpf.k = 0.02;

    uab_lpf.ts = 0.001;
    ubc_lpf.ts = 0.001;
    uca_lpf.ts = 0.001;

    iacap_lpf.ts = 0.001;
    ibcap_lpf.ts = 0.001;
    iccap_lpf.ts = 0.001;

    ucapa_lpf.fc = 100;
    ucapa_lpf.ts = 0.001;

    GridPQ_P_lpf.fc = 30;
    GridPQ_P_lpf.ts = 0.001;
    GridPQ_Q_lpf.fc = 30;
    GridPQ_Q_lpf.ts = 0.001;
    GridPQ.filter = 0.01;

}


//#pragma CODE_SECTION(CaltGrid,"ramfuncs");
float sss=0;
float s_power=0;
void CaltGrid()
{



      udca_lpf.x = RunData.FilteredData.Udc;
      udca_lpf.calc(&udca_lpf);
      RunData.GridData.Udca_vol = udca_lpf.y;

      ucapa_lpf.x = RunData.FilteredData.Ucap;
      ucapa_lpf.calc(&ucapa_lpf);
      RunData.GridData.Ucapa_vol= ucapa_lpf.y;

      ucapa_mpf.x = RunData.GridData.Ucapa_vol;
      ucapa_mpf.calc(&ucapa_mpf);
      RunData.GridData.Ucapma_vol = ucapa_mpf.y;
      RunData.GridData.Ucapa_s = 1/RunData.GridData.Ucapma_vol;

      vda_mpf.x = RunData.InvControlOutput.GridVda;
      vda_mpf.calc(&vda_mpf);
      RunData.GridData.GridUa1Rms = vda_mpf.y;

      vdb_mpf.x = RunData.InvControlOutput.GridVdb;
      vdb_mpf.calc(&vdb_mpf);
      RunData.GridData.GridUb1Rms = vdb_mpf.y;

      vdc_mpf.x = RunData.InvControlOutput.GridVdc;
      vdc_mpf.calc(&vdc_mpf);
      RunData.GridData.GridUc1Rms = vdc_mpf.y;


      iacap_lpf.x = RunData.FilteredData.CapIa0;
      iacap_lpf.calc(&iacap_lpf);
      ibcap_lpf.x = RunData.FilteredData.CapIb0;
      ibcap_lpf.calc(&ibcap_lpf);
      iccap_lpf.x = RunData.FilteredData.CapIc0;
      iccap_lpf.calc(&iccap_lpf);
      RunData.FilteredData.CapIa1 = iacap_lpf.y;
      RunData.FilteredData.CapIb1 = ibcap_lpf.y;
      RunData.FilteredData.CapIc1 = iccap_lpf.y;


      uab_lpf.x = RunData.FilteredData.GridUa0;
      uab_lpf.calc(&uab_lpf);
      ubc_lpf.x = RunData.FilteredData.GridUb0;
      ubc_lpf.calc(&ubc_lpf);
      uca_lpf.x = RunData.FilteredData.GridUc0;
      uca_lpf.calc(&uca_lpf);
      RunData.FilteredData.GridUa1 = uab_lpf.y;
      RunData.FilteredData.GridUb1 = ubc_lpf.y;
      RunData.FilteredData.GridUc1 = uca_lpf.y;

      CapIaRms.s = RunData.FilteredData.CapIa1;
      CapIaRms.calc(&CapIaRms);
      RunData.GridData.CapIaRms = CapIaRms.rms;

      CapIbRms.s = RunData.FilteredData.CapIb1;
      CapIbRms.calc(&CapIbRms);
      RunData.GridData.CapIbRms = CapIbRms.rms;

      CapIcRms.s = RunData.FilteredData.CapIc1;
      CapIcRms.calc(&CapIcRms);
      RunData.GridData.CapIcRms = CapIcRms.rms;

      GridUaRms.s = RunData.FilteredData.GridUa0;
      GridUaRms.calc(&GridUaRms);
      RunData.GridData.GridUaRms = GridUaRms.rms;

      GridUbRms.s = RunData.FilteredData.GridUb0;
      GridUbRms.calc(&GridUbRms);
      RunData.GridData.GridUbRms = GridUbRms.rms;

      GridUcRms.s = RunData.FilteredData.GridUc0;
      GridUcRms.calc(&GridUcRms);
      RunData.GridData.GridUcRms = GridUcRms.rms;

      LoadUaRms.s = RunData.FilteredData.LoadUa0;
      LoadUaRms.calc(&LoadUaRms);
      RunData.GridData.LoadUaRms = LoadUaRms.rms;

      LoadUbRms.s = RunData.FilteredData.LoadUb0;
      LoadUbRms.calc(&LoadUbRms);
      RunData.GridData.LoadUbRms = LoadUbRms.rms;

      LoadUcRms.s = RunData.FilteredData.LoadUc0;
      LoadUcRms.calc(&LoadUcRms);
      RunData.GridData.LoadUcRms = LoadUcRms.rms;

      GridIaRms.s = RunData.FilteredData.IgbtIa1;
      GridIaRms.calc(&GridIaRms);
      RunData.GridData.GridIaRms = GridIaRms.rms;

      GridIbRms.s = RunData.FilteredData.IgbtIb1;
      GridIbRms.calc(&GridIbRms);
      RunData.GridData.GridIbRms = GridIbRms.rms;

      GridIcRms.s = RunData.FilteredData.IgbtIc1;
      GridIcRms.calc(&GridIcRms);
      RunData.GridData.GridIcRms = GridIcRms.rms;

      SysIaRms.s = RunData.FilteredData.SysIa1;
      SysIaRms.calc(&SysIaRms);
      RunData.GridData.SysIaRms = SysIaRms.rms;

      SysIbRms.s = RunData.FilteredData.SysIb1;
      SysIbRms.calc(&SysIbRms);
      RunData.GridData.SysIbRms = SysIbRms.rms;

      SysIcRms.s = RunData.FilteredData.SysIc1;
      SysIcRms.calc(&SysIcRms);
      RunData.GridData.SysIcRms = SysIcRms.rms;

      if(RunData.InvControlOutput.GridVda > 220)
          {
              RunData.GridData.FrequencyA = 0.1591549407*RunData.InvControlOutput.GridAFrequency;
          }
          else
          {
              RunData.GridData.FrequencyA = 50.0;
          }

          if(RunData.InvControlOutput.GridVdb > 220)
          {
              RunData.GridData.FrequencyB = 0.1591549407*RunData.InvControlOutput.GridBFrequency;
          }
          else
          {
              RunData.GridData.FrequencyB = 50.0;
          }

          if(RunData.InvControlOutput.GridVdc > 220)
          {
              RunData.GridData.FrequencyC = 0.1591549407*RunData.InvControlOutput.GridCFrequency;
          }
          else
          {
              RunData.GridData.FrequencyC = 50.0;
          }
          GridPQ.ua = RunData.FilteredData.GridUa0;
          GridPQ.ub = RunData.FilteredData.GridUb0;
          GridPQ.uc = RunData.FilteredData.GridUc0;
          GridPQ.ia  = RunData.FilteredData.SysIa0;
          GridPQ.ib  = RunData.FilteredData.SysIb0;
          GridPQ.ic  = RunData.FilteredData.SysIc0;
          GridPQ.calc(&GridPQ);

          GridPQ_P_lpf.x = GridPQ.ActivePower;
          GridPQ_P_lpf.calc(&GridPQ_P_lpf);
          GridPQ_Q_lpf.x = GridPQ.ReactivePower;
          GridPQ_Q_lpf.calc(&GridPQ_Q_lpf);

          RunData.GridData.ActivePower = GridPQ_P_lpf.y;
          RunData.GridData.ReactivePower = GridPQ_Q_lpf.y;

          s_power = (RunData.GridData.ActivePower*0.001)*(RunData.GridData.ActivePower*0.001) +
                    RunData.GridData.ReactivePower*0.001*RunData.GridData.ReactivePower*0.001;

          sss = sqrt(s_power);
         // sss = s_power ;
          if(sss> 2)
          {
             RunData.GridData.PowerFactor = 0.001*RunData.GridData.ActivePower/sss;
          }
          else
          {
             RunData.GridData.PowerFactor = 0;
          }

}



