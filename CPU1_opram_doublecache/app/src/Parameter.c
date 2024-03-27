

#include "Global_struct.h"
#include "Const_Defines.h"
#include "FilterAdData.h"
#include "NandFlash.h"
#include "RecordCtrl.h"
#include "RtcDS1302.h"
#include "master_can.h"
#include "master_can_app.h"
#include "ExRAM.h"

void Parameter_init ()
{

	    ParaData.SoftVersion = SOFT_VERSION;
	    ParaData.ModbusPar.MyAddr = 1;

	    ParaData.InvCtr.CurKp = 30.0;    //1.0
	    ParaData.InvCtr.CurKi = 2.0;     //2.0
	    ParaData.InvCtr.CurMax = 300.0;
	    ParaData.InvCtr.CurMin = -300.0;

	    ParaData.InvCtr.PllKp = 1;
	    ParaData.InvCtr.PllKi = 1;
	    ParaData.InvCtr.PllMax = 30.0;
	    ParaData.InvCtr.PllMin = -30.0;

	    ParaData.InvCtr.UdcKp = 40.0;
	    ParaData.InvCtr.UdcKi = 4.0;
	    ParaData.InvCtr.UdcMax = 800.0;
	    ParaData.InvCtr.UdcMin = -800.0;

        ParaData.InvCtr.UcapKp = 10.0;
        ParaData.InvCtr.UcapKi = 4.0;
        ParaData.InvCtr.UcapMax = 100.0;
        ParaData.InvCtr.UcapMin = -100.0;

	    ParaData.InvCtr.Idckp = 1.0;
	    ParaData.InvCtr.Idcki = 1.0;
	    ParaData.InvCtr.Idcmax = 140.0;
	    ParaData.InvCtr.Idcmin = -140.0;

	    ParaData.InvCtr.t_Inv = 30000;
	    ParaData.InvCtr.V_diff = 16;
	    ParaData.InvCtr.t_syon = 40;
	    ParaData.InvCtr.vdhvrt = 360;
	    ParaData.InvCtr.vdlvrt = 275;
	    ParaData.InvCtr.Ucap_charge = 440;
	    ParaData.InvCtr.Ucap_stop = 450;
	    ParaData.InvCtr.Ucap_Dvr_quit = 350;
	    ParaData.InvCtr.vdref = 233;
	    RunData.InvControlInput.VolRef = 1.414*ParaData.InvCtr.vdref;
	    ParaData.InvCtr.Igrid_filter_k = 5;
	    ParaData.InvCtr.Iinv_filter_k = 5;
	    ParaData.InvCtr.Ugrid_filter_k = 100;
	    ParaData.InvCtr.Uinv_filter_k = 100;


	    Temper_ambient_obj.Par.FanLev = 300;
	    Temper_ambient_obj.Par.ParHighLev2 = 620;
        Temper_ambient1_obj.Par.FanLev = 300;
        Temper_ambient1_obj.Par.ParHighLev2 = 620;
	    Temper_SCR_obj.Par.FanLev = 300;
	    Temper_SCR_obj.Par.ParHighLev2 = 750;

	    Temper_muduleA_obj.Par.FanLev = 300;
	    Temper_muduleA_obj.Par.ParHighLev2 = 900;
	    Temper_muduleB_obj.Par.FanLev = 300;
	    Temper_muduleB_obj.Par.ParHighLev2 = 900;
	    Temper_muduleC_obj.Par.FanLev = 300;
	    Temper_muduleC_obj.Par.ParHighLev2 = 900;

	    ParaData.FaultProtect.OverIIgbtDly = 10;
	    ParaData.FaultProtect.OverIgbtIPeak = 1100;

	    ParaData.FaultProtect.EmergencyFaultDly = 10;
	    ParaData.FaultProtect.FuseFaultDly = 10;
	    ParaData.FaultProtect.IgbtFaultDly = 10;

	    ParaData.FaultProtect.OverIdc = 450;
	    ParaData.FaultProtect.OverIdcDly = 10;

	    ParaData.FaultProtect.OverUdcDly = 4;
	    ParaData.FaultProtect.OverUdcPeak = 500;

	    ParaData.FaultProtect.UnderUdc = 330;
	    ParaData.FaultProtect.UnderUdcDly = 5;

	    ParaData.FaultProtect.OverIcapRmsDly = 30;
	    ParaData.FaultProtect.OverIcapRms = 25;

	    ParaData.FaultProtect.OverIRmsDly = 20;
	    ParaData.FaultProtect.OverIRms = 600;

	    ParaData.FaultProtect.OverSysIRmsDly = 20;
	    ParaData.FaultProtect.OverSysIRms = 650;

	    ParaData.FaultProtect.OverURmsDly = 30;
	    ParaData.FaultProtect.OverURms = 260;

	    ParaData.FaultProtect.UnderUrmsDly = 30;
	    ParaData.FaultProtect.UnderURms = 185;

	    ParaData.FaultProtect.UnderFreqAC =4700;
	    ParaData.FaultProtect.OverFreqAC =5300;
	    ParaData.FaultProtect.FreqFaultDly = 20;
	    ParaData.FaultProtect.TempFaultDly = 20;

	    ParaData.InvCtr.Scrcur = 10;
	    ParaData.InvCtr.Idref = 20;
	    ParaData.InvCtr.Udc_ref = 620;

	    ParaData.Rate_val.Power = 250;
	    ParaData.Rate_val.GridUrms = 380;
	    ParaData.SoftVersion = 1;
	    ParaData.ProductIdH = 20197;
	    ParaData.ProductIdL = 1;
	    ParaData.Sys_Cur_gain = 500;
	    ParaData.Load_Cur_gain = 1500;

	    ParaData.Module1_ID = 1;
	    ParaData.Module2_ID = 2;
	    ParaData.Module3_ID = 3;
	    ParaData.Module4_ID = 4;
	    ParaData.Module_NUM = 2;
	    ParaData.Module_Cur_gain = 200;

	    ParaData.FaultProtect.Module_Ipeak = 600;
	    ParaData.FaultProtect.Module_Ipeak_Dly = 15;
        ParaData.FaultProtect.Module_Irms = 300;
        ParaData.FaultProtect.Module_Irms_Dly = 20;

        ParaData.InvCtr.Transformer_k = 116;
        ParaData.InvCtr.Salve = 0;
        ParaData.InvCtr.Salve_NUM = 1;

        ParaData.CMS_NUM = 4;


}

#pragma CODE_SECTION(Comproc, "ramfuncs");
void Comproc(void)
{

	float temp_min;
	int16 g_j = 0,g_h = 0;


/*	RunData.ModbusData[0]  = (int16)(RunData.ExAdresult.Ad1ChA1);//RunData.StateMachine.StatusReg0.all;
	RunData.ModbusData[1]  = (int16)(RunData.ExAdresult.Ad1ChA2);//RunData.StateMachine.StatusReg1.all;
	RunData.ModbusData[2]  = (int16)(RunData.ExAdresult.Ad1ChA3);//RunData.StateMachine.StatusReg2.all;
	RunData.ModbusData[3]  = (int16)(RunData.ExAdresult.Ad1ChA4);//RunData.StateMachine.FaultCode0Reg.all;
	RunData.ModbusData[4]  = (int16)(RunData.ExAdresult.Ad1ChA5);//RunData.StateMachine.FaultCode1Reg.all;
	RunData.ModbusData[5]  = (int16)(RunData.ExAdresult.Ad1ChA6);//RunData.StateMachine.FaultCode2Reg.all;
	RunData.ModbusData[6]  = (int16)(RunData.ExAdresult.Ad1ChA7);//RunData.StateMachine.FaultCode3Reg.all;
	RunData.ModbusData[7]  = (int16)(RunData.ExAdresult.Ad1ChA8);//RunData.StateMachine.FaultCode4Reg.all;
	RunData.ModbusData[8]  = (int16)(RunData.ExAdresult.Ad2ChA1);//(int16)(10*RunData.GridData.GridUaRms);
	RunData.ModbusData[9] =  (int16)(RunData.ExAdresult.Ad2ChA2);//(int16)(10*RunData.GridData.GridUbRms);
	RunData.ModbusData[10] = (int16)(RunData.ExAdresult.Ad2ChA3);//(int16)(10*RunData.GridData.GridUcRms);
	RunData.ModbusData[11] = (int16)(RunData.ExAdresult.Ad2ChA4);//(int16)(10*RunData.GridData.SysIaRms);
	RunData.ModbusData[12] = (int16)(RunData.ExAdresult.Ad2ChA5);//(int16)(10*RunData.GridData.SysIbRms);
	RunData.ModbusData[13] = (int16)(RunData.ExAdresult.Ad2ChA6);//(int16)(10*RunData.GridData.SysIcRms);
	RunData.ModbusData[14] = (int16)(RunData.ExAdresult.Ad2ChA7);//(int16)(10*RunData.GridData.GridIaRms);
	RunData.ModbusData[15] = (int16)(RunData.ExAdresult.Ad2ChA8);//(int16)(10*RunData.GridData.GridIbRms);
	RunData.ModbusData[16] = (int16)(RunData.ExAdresult.Ad3ChA1);//(int16)(10*RunData.GridData.GridIcRms);
	RunData.ModbusData[17] = (int16)(RunData.ExAdresult.Ad3ChA2);//(int16)(10*RunData.GridData.Udca_cur);
	RunData.ModbusData[18] = (int16)(RunData.ExAdresult.Ad3ChA3);//(int16)(10*RunData.GridData.Udcb_cur);
	RunData.ModbusData[19] = (int16)(RunData.ExAdresult.Ad3ChA4);//(int16)(10*RunData.GridData.Udcc_cur);
	RunData.ModbusData[20] = (int16)(RunData.ExAdresult.Ad3ChA5);//(int16)(10*RunData.GridData.LoadUaRms);
	RunData.ModbusData[21] = (int16)(RunData.ExAdresult.Ad3ChA6);//(int16)(10*RunData.GridData.LoadUbRms);
	RunData.ModbusData[22] = (int16)(RunData.ExAdresult.Ad3ChA7);//(int16)(10*RunData.GridData.LoadUcRms);
	RunData.ModbusData[23] = (int16)(RunData.ExAdresult.Ad3ChA8);//(int16)(10*RunData.GridData.Udca_vol);*/
	RunData.ModbusData[0]  = RunData.StateMachine.StatusReg0.all;
	    RunData.ModbusData[1]  = RunData.StateMachine.StatusReg1.all;
	    RunData.ModbusData[2]  = RunData.StateMachine.StatusReg2.all;
	    RunData.ModbusData[3]  = RunData.StateMachine.FaultCode0Reg.all;
	    RunData.ModbusData[4]  = RunData.StateMachine.FaultCode1Reg.all;
	    RunData.ModbusData[5]  = RunData.StateMachine.FaultCode2Reg.all;
	    RunData.ModbusData[6]  = RunData.StateMachine.FaultCode3Reg.all;
	    RunData.ModbusData[7]  = RunData.StateMachine.FaultCode4Reg.all;
	    RunData.ModbusData[8]  = (int16)(10*RunData.GridData.GridUaRms);
	    RunData.ModbusData[9] =  (int16)(10*RunData.GridData.GridUbRms);
	    RunData.ModbusData[10] = (int16)(10*RunData.GridData.GridUcRms);
	    RunData.ModbusData[11] = (int16)(10*RunData.GridData.SysIaRms);
	    RunData.ModbusData[12] = (int16)(10*RunData.GridData.SysIbRms);
	    RunData.ModbusData[13] = (int16)(10*RunData.GridData.SysIcRms);
	    RunData.ModbusData[14] = (int16)(10*RunData.GridData.GridIaRms);
	    RunData.ModbusData[15] = (int16)(10*RunData.GridData.GridIbRms);
	    RunData.ModbusData[16] = (int16)(10*RunData.GridData.GridIcRms);
	    RunData.ModbusData[17] = (int16)(10*RunData.InvControlOutput.LoadIdp);//LoadIdp
	    RunData.ModbusData[18] = (int16)(10*RunData.InvControlOutput.LoadIqp);//LoadIqp
	    RunData.ModbusData[19] = (int16)(10*RunData.InvControlOutput.GridUd);
	    RunData.ModbusData[20] = (int16)(10*RunData.GridData.LoadUaRms);
	    RunData.ModbusData[21] = (int16)(10*RunData.GridData.LoadUbRms);
	    RunData.ModbusData[22] = (int16)(10*RunData.GridData.LoadUcRms);
	    RunData.ModbusData[23] = (int16)(10*RunData.GridData.Udca_vol);
	    RunData.ModbusData[24] = (int16)(10*RunData.InvControlOutput.InvVqp);//InvVqp
	    RunData.ModbusData[25] = (int16)(10*RunData.InvControlOutput.InvVdp);//InvVdp
	    RunData.ModbusData[26] = (int16)(10*RunData.GridData.Ucapa_vol);
	    RunData.ModbusData[27] = (int16)(10*RunData.GridData.Ucapb_vol);
	    RunData.ModbusData[28]=  (int16)(10*RunData.GridData.Ucapc_vol);
	    RunData.ModbusData[29] = (int16)(10*RunData.GridData.CapIaRms);
	    RunData.ModbusData[30] = (int16)(10*RunData.GridData.CapIbRms);
	    RunData.ModbusData[31] = (int16)(10*RunData.GridData.CapIcRms);
	    RunData.ModbusData[32] = SCR_ntc.temperature;//CAP_ntc.temperature;       // SCR2温度
	    RunData.ModbusData[33] = ambient_ntc1.temperature;  //电容柜温度
	    RunData.ModbusData[34] = 10*RunData.StateMachine.StateMachine;
	    RunData.ModbusData[35] = SCR_ntc.temperature;
	    RunData.ModbusData[36] = ambient_ntc.temperature;  //功率柜温度
	    RunData.ModbusData[37] = NF_Data.Para[1][0];//RunData.Gridnormalcnt;
//	    RunData.ModbusData[37] = (*(volatile uint16_t *)((STATUS1_TYPE0_START)+(NF_DataParaNum)));//RunData.Gridnormalcnt; change
	    RunData.ModbusData[38] = SOFT_VERSION;//Inv_controlobj.CtlINVMode;
	    RunData.ModbusData[39] = Rtc_Data.CurTime[6];//(int16)(10*RunData.InvControlOutput.LoadIda);
	    RunData.ModbusData[40] = Rtc_Data.CurTime[4];//(int16)(10*RunData.InvControlOutput.LoadIqa);
	    RunData.ModbusData[41] = Rtc_Data.CurTime[3];//(int16)(10*RunData.InvControlOutput.LoadIdb);
	    RunData.ModbusData[42] = Rtc_Data.CurTime[2];//(int16)(10*RunData.InvControlOutput.GridVda);
	    RunData.ModbusData[43] = Rtc_Data.CurTime[1];//(int16)(10*RunData.InvControlOutput.GridVdb);
	    RunData.ModbusData[44] = Rtc_Data.CurTime[0];//(int16)(10*RunData.InvControlOutput.GridVdc);
	    RunData.ModbusData[45] = (int16)(0.01*RunData.GridData.ActivePower);
	    RunData.ModbusData[46] = (int16)(0.01*RunData.GridData.ReactivePower);
	    RunData.ModbusData[47] = (int16)(1000*RunData.GridData.PowerFactor);
	//    RunData.ModbusData[48] = (int16)(10*RunData.GridData.LoadUaRms);
	    RunData.ModbusData[49] = (int16)(10*RunData.GridData.LoadUbRms);
	    RunData.ModbusData[50] = (int16)(10*RunData.GridData.LoadUcRms);
	    RunData.ModbusData[51] =  RunData.t_gridabnormal*0.2;
	    RunData.ModbusData[52] =  RunData.Compenok;
	    RunData.ModbusData[53] = (int16)(100*RunData.GridData.FrequencyA);
	    RunData.ModbusData[54] = (int16)(100*RunData.GridData.FrequencyB);
	    RunData.ModbusData[55] = (int16)(100*RunData.GridData.FrequencyC);
	    RunData.ModbusData[56] = NF_Data.Para[0][0];//故障次数 delete
//	    RunData.ModbusData[56] = (*(volatile uint16_t *)(STATUS1_TYPE0_START));//故障次数 change
	    RunData.ModbusData[57] = (int16)(RunData.InvControlOutput.Invline_Vd);
	    RunData.ModbusData[58] = (int16)(RunData.InvControlOutput.InvVdp);
	    RunData.ModbusData[59] = (int16)(RunData.InvControlOutput.InvVdc);
	    RunData.ModbusData[60] = (int16)(RunData.InvControlOutput.GridUd);
	    RunData.ModbusData[61] = (int16)(RunData.InvControlOutput.GridVdb);
	    RunData.ModbusData[62] = (int16)(RunData.InvControlOutput.GridVdc);

	    temp_min = MIN(RunData.InvControlOutput.GridVdap,RunData.InvControlOutput.GridVdbp);
	    temp_min = MIN(temp_min,RunData.InvControlOutput.GridVdcp);
	    RunData.ModbusData[69] = (int16)(temp_min*0.707);
	    RunData.ModbusData[70] = RunData.t_gridabnormal*0.2;

	    RunData.ModbusData[71] = RunData.STATUS_CPLD0;
	//    RunData.ModbusData[73] = Inv_controlobj.PllMode;
	    RunData.ModbusData[72] = (RunData.STATUS_CPLD1)&0x000f;

	    RunData.StateMachine.McwReg.all = RunData.ModbusData[75];
	    if((((RunData.STATUS_CPLD0)&0x0001))&&(RunData.StateMachine.McwReg.bits.InvRun)&&(RunData.StateMachine.MswReg.bits.Fault == 0))
	    {
	        RunData.StateMachine.MswReg.bits.Start = 1;
	    }
	    if((((RunData.STATUS_CPLD0)&0x0001)==0)&&(RunData.StateMachine.McwReg.bits.InvRun==0))
	    {
	        RunData.StateMachine.MswReg.bits.Start = 0;
	    }
	    RunData.IOtext = RunData.ModbusData[76];
	//  RunData.InvControlInput.VolRef = 1.414*((float)RunData.ModbusData[77]);

	    Rtc_Data.SetTime[0] = RunData.ModbusData[118];
	    Rtc_Data.SetTime[1] = RunData.ModbusData[117];
	    Rtc_Data.SetTime[2] = RunData.ModbusData[116];
	    Rtc_Data.SetTime[3] = RunData.ModbusData[115];
	    Rtc_Data.SetTime[4] = RunData.ModbusData[114];
	    Rtc_Data.SetTime[6] = RunData.ModbusData[113];

	    RunData.ModbusData[179] = RunData.ModbusData2[6];
	    RunData.ModbusData[180] = RunData.ModbusData2[0];
	    RunData.ModbusData[181] = RunData.ModbusData2[1];
	    RunData.ModbusData[182] = RunData.ModbusData2[2];
	    RunData.ModbusData[183] = RunData.ModbusData2[3];
	    RunData.ModbusData[184] = RunData.ModbusData2[4];
	    RunData.ModbusData[185] = RunData.ModbusData2[5];

        RunData.ModbusData[186] = RunData.ModbusData2[18];
        RunData.ModbusData[187] = RunData.ModbusData2[12];
        RunData.ModbusData[188] = RunData.ModbusData2[13];
        RunData.ModbusData[189] = RunData.ModbusData2[14];
        RunData.ModbusData[190] = RunData.ModbusData2[15];
        RunData.ModbusData[191] = RunData.ModbusData2[16];
        RunData.ModbusData[192] = RunData.ModbusData2[17];

        RunData.ModbusData[193] = RunData.ModbusData2[30];
        RunData.ModbusData[194] = RunData.ModbusData2[24];
        RunData.ModbusData[195] = RunData.ModbusData2[25];
        RunData.ModbusData[196] = RunData.ModbusData2[26];
        RunData.ModbusData[197] = RunData.ModbusData2[27];
        RunData.ModbusData[198] = RunData.ModbusData2[28];
        RunData.ModbusData[199] = RunData.ModbusData2[29];

        RunData.ModbusData[200] = RunData.ModbusData2[42];
        RunData.ModbusData[201] = RunData.ModbusData2[36];
        RunData.ModbusData[202] = RunData.ModbusData2[37];
        RunData.ModbusData[203] = RunData.ModbusData2[38];
        RunData.ModbusData[204] = RunData.ModbusData2[39];
        RunData.ModbusData[205] = RunData.ModbusData2[40];
        RunData.ModbusData[206] = RunData.ModbusData2[41];

        RunData.ModbusData2[51] = RunData.StateMachine.McwReg.all;
        RunData.ModbusData2[63] = RunData.StateMachine.McwReg.all;
        RunData.ModbusData2[75] = RunData.StateMachine.McwReg.all;
        RunData.ModbusData2[87] = RunData.StateMachine.McwReg.all;

	    RunData.index = RunData.ModbusData[e_abnormal_vol+15];
	    RunData.ModbusData[e_abnormal_vol+16] = RunData.Gridabnormalcnt;
	    if((RunData.index < 6)&&(RunData.index > 0))
	    {
	        for(g_j=0;g_j<15;g_j++)
	        {
	            RunData.ModbusData[e_abnormal_vol+g_j] = RunData.Gridabnormal[RunData.index-1][g_j];
	        }
	        RunData.ModbusData[e_abnormal_vol+17] = RunData.index;
	    }

	    if(RunData.index==6)
	    {
	        for(g_h=0;g_h<5;g_h++)
	        {
	            for(g_j=0;g_j<15;g_j++)
	            {
	                RunData.Gridabnormal[g_h][g_j]=0;
	            }
	        }
	        RunData.Gridabnormalcnt = 0;
	    }





    ModbusComServer.run(&ModbusComServer);//执行函数
    ModbusComServerc.run(&ModbusComServerc);//执行函数

}



static void ModbusDataPro_Float(int16 *pSrc,float *pDst,int16 low,int16 top)
{
    if((*pSrc >= low)&&(*pSrc <= top))
        *pDst = *pSrc;
    else
        *pSrc = *pDst;
}

static void ModbusDataPro_Int16(int16 *pSrc,int16 *pDst,int16 low,int16 top)
{
    if((*pSrc >= low)&&(*pSrc <= top))
        *pDst = *pSrc;
    else
        *pSrc = *pDst;
}

static void ModbusDataPro_Uint16(int16 *pSrc,Uint16 *pDst,int16 low,int16 top)
{
    if((*pSrc >= low)&&(*pSrc <= top))
        *pDst = *pSrc;
    else
        *pSrc = *pDst;
}

#pragma CODE_SECTION(Paracom, "ramfuncs");

void Paracom(void)
{

	ModbusDataPro_Float(&RunData.ModbusData[77],&ParaData.InvCtr.vdref,0,1001);
	RunData.InvControlInput.VolRef = 1.414*ParaData.InvCtr.vdref;
	ModbusDataPro_Uint16(&RunData.ModbusData[78],&ParaData.Rate_val.Power,0,20000);
    ModbusDataPro_Float(&RunData.ModbusData[79],&ParaData.InvCtr.vdlvrt,20,1005);
    ModbusDataPro_Float(&RunData.ModbusData[80],&ParaData.InvCtr.vdhvrt,30,2006);
    ModbusDataPro_Uint16(&RunData.ModbusData[81],&ParaData.InvCtr.t_Inv,0,0x7FFF);
    ModbusDataPro_Float(&RunData.ModbusData[82],&ParaData.InvCtr.Ucap_charge,68,881);
    ModbusDataPro_Float(&RunData.ModbusData[83],&ParaData.InvCtr.Ucap_stop,82,896);
    ModbusDataPro_Float(&RunData.ModbusData[84],&ParaData.InvCtr.Ucap_Dvr_quit,30,710);
    ModbusDataPro_Uint16(&RunData.ModbusData[85],&ParaData.FaultProtect.OverUdcPeak,70,1021);
    ModbusDataPro_Uint16(&RunData.ModbusData[86],&ParaData.FaultProtect.OverUdcDly,4,101);
    ModbusDataPro_Uint16(&RunData.ModbusData[87],&ParaData.FaultProtect.UnderUdc,99,861);
    ModbusDataPro_Uint16(&RunData.ModbusData[88],&ParaData.FaultProtect.UnderUdcDly,4,300);
    ModbusDataPro_Uint16(&RunData.ModbusData[89],&ParaData.FaultProtect.OverIRms,50,5025);
    ModbusDataPro_Uint16(&RunData.ModbusData[90],&ParaData.FaultProtect.OverIRmsDly,10,500);
    ModbusDataPro_Uint16(&RunData.ModbusData[91],&ParaData.FaultProtect.OverURms,25,300);
    ModbusDataPro_Uint16(&RunData.ModbusData[92],&ParaData.FaultProtect.OverURmsDly,15,40);

    ModbusDataPro_Int16(&RunData.ModbusData[93],&Temper_muduleA_obj.Par.FanLev,10,501);
    Temper_muduleB_obj.Par.FanLev = Temper_muduleA_obj.Par.FanLev;
    Temper_muduleC_obj.Par.FanLev = Temper_muduleA_obj.Par.FanLev;

    ModbusDataPro_Int16(&RunData.ModbusData[94],&Temper_muduleA_obj.Par.ParHighLev2,10,1101);
    Temper_muduleB_obj.Par.ParHighLev2 = Temper_muduleA_obj.Par.ParHighLev2;
    Temper_muduleC_obj.Par.ParHighLev2 = Temper_muduleA_obj.Par.ParHighLev2;

    ModbusDataPro_Int16(&RunData.ModbusData[95],&Temper_SCR_obj.Par.FanLev,10,400);
    ModbusDataPro_Int16(&RunData.ModbusData[96],&Temper_SCR_obj.Par.ParHighLev2,70,900);
    ModbusDataPro_Int16(&RunData.ModbusData[97],&Temper_ambient_obj.Par.FanLev,10,400);
    ModbusDataPro_Int16(&RunData.ModbusData[98],&Temper_ambient_obj.Par.ParHighLev2,60,800);
    Temper_ambient1_obj.Par.FanLev = Temper_ambient_obj.Par.FanLev;
    Temper_ambient1_obj.Par.ParHighLev2 =Temper_ambient_obj.Par.ParHighLev2;
    ModbusDataPro_Uint16(&RunData.ModbusData[99],&ParaData.FaultProtect.OverSysIRms,30,5060);
    ModbusDataPro_Uint16(&RunData.ModbusData[100],&ParaData.FaultProtect.OverSysIRmsDly,10,100);
    ModbusDataPro_Uint16(&RunData.ModbusData[101],&ParaData.FaultProtect.OverIgbtIPeak,1,5001);
    ModbusDataPro_Uint16(&RunData.ModbusData[102],&ParaData.FaultProtect.OverIIgbtDly,2,100);
    ModbusDataPro_Uint16(&RunData.ModbusData[103],&ParaData.FaultProtect.IgbtFaultDly,2,100);
    ModbusDataPro_Uint16(&RunData.ModbusData[104],&ParaData.FaultProtect.UdcFaultDly,4,200);
    ModbusDataPro_Uint16(&RunData.ModbusData[105],&ParaData.FaultProtect.OverIcapRms,16,401);
    ModbusDataPro_Uint16(&RunData.ModbusData[106],&ParaData.FaultProtect.OverIcapRmsDly,19,401);
    ModbusDataPro_Uint16(&RunData.ModbusData[107],&ParaData.FaultProtect.OverFreqAC,5200,5600);
    ModbusDataPro_Uint16(&RunData.ModbusData[108],&ParaData.FaultProtect.UnderFreqAC,4000,5500);
    ModbusDataPro_Uint16(&RunData.ModbusData[109],&ParaData.FaultProtect.OverIdc,40,500);
    ModbusDataPro_Uint16(&RunData.ModbusData[110],&ParaData.FaultProtect.OverIdcDly,4,66);
    ModbusDataPro_Uint16(&RunData.ModbusData[111],&ParaData.ProductIdH,0,0x7FFF);
    ModbusDataPro_Uint16(&RunData.ModbusData[112],&ParaData.ProductIdL,0,999);
    ModbusDataPro_Uint16(&RunData.ModbusData[113],&ParaData.Year,0,0x7FFF);
    ModbusDataPro_Uint16(&RunData.ModbusData[114],&ParaData.Month,0,13);
    ModbusDataPro_Uint16(&RunData.ModbusData[115],&ParaData.Data,0,32);
    ModbusDataPro_Uint16(&RunData.ModbusData[116],&ParaData.Hour,0,25);
    ModbusDataPro_Uint16(&RunData.ModbusData[117],&ParaData.Minute,0,60);
    ModbusDataPro_Uint16(&RunData.ModbusData[118],&ParaData.Second,0,60);
    ModbusDataPro_Uint16(&RunData.ModbusData[119],&ParaData.Flash,0,0x7FFF);

    ModbusDataPro_Float(&RunData.ModbusData[120],&ParaData.InvCtr.CurKp,4,500);
    ModbusDataPro_Float(&RunData.ModbusData[121],&ParaData.InvCtr.CurKi,0,101);
    ModbusDataPro_Float(&RunData.ModbusData[122],&ParaData.InvCtr.CurMax,9,500);
    ParaData.InvCtr.CurMin = -ParaData.InvCtr.CurMax;

    ModbusDataPro_Float(&RunData.ModbusData[123],&ParaData.InvCtr.UdcKp,1,801);
    ModbusDataPro_Float(&RunData.ModbusData[124],&ParaData.InvCtr.UdcKi,2,101);
    ModbusDataPro_Float(&RunData.ModbusData[125],&ParaData.InvCtr.UdcMax,5,5001);
    ParaData.InvCtr.UdcMin = -ParaData.InvCtr.UdcMax;

    ModbusDataPro_Float(&RunData.ModbusData[126],&ParaData.InvCtr.PllKp,0,4);
    ModbusDataPro_Float(&RunData.ModbusData[127],&ParaData.InvCtr.PllKi,0,5);
    ModbusDataPro_Float(&RunData.ModbusData[128],&ParaData.InvCtr.PllMax,0,150);
    ParaData.InvCtr.PllMin = -ParaData.InvCtr.PllMax;

    ModbusDataPro_Float(&RunData.ModbusData[129],&ParaData.InvCtr.Ugrid_filter_k,80,200);
    ModbusDataPro_Float(&RunData.ModbusData[130],&ParaData.InvCtr.Uinv_filter_k,80,200);
    ModbusDataPro_Float(&RunData.ModbusData[131],&ParaData.InvCtr.Igrid_filter_k,0,10);
    ModbusDataPro_Float(&RunData.ModbusData[132],&ParaData.InvCtr.Iinv_filter_k,0,10);
    ModbusDataPro_Uint16(&RunData.ModbusData[133],&ParaData.InvCtr.t_syon,0,101);
    ModbusDataPro_Float(&RunData.ModbusData[134],&ParaData.InvCtr.V_diff,0,206);
    ModbusDataPro_Float(&RunData.ModbusData[135],&ParaData.InvCtr.Idref,0,1001);
    RunData.InvControlInput.Idref = ParaData.InvCtr.Idref;
    ModbusDataPro_Float(&RunData.ModbusData[136],&ParaData.InvCtr.Scrcur,0,106);
    ModbusDataPro_Uint16(&RunData.ModbusData[137],&ParaData.Module1_ID,0,20);
    ModbusDataPro_Uint16(&RunData.ModbusData[138],&ParaData.Module2_ID,0,20);
    ModbusDataPro_Uint16(&RunData.ModbusData[139],&ParaData.Module3_ID,0,20);
    ModbusDataPro_Uint16(&RunData.ModbusData[140],&ParaData.Module4_ID,0,20);
    ModbusDataPro_Uint16(&RunData.ModbusData[141],&ParaData.FaultProtect.Module_Ipeak,0,5000);
    ModbusDataPro_Uint16(&RunData.ModbusData[142],&ParaData.FaultProtect.Module_Ipeak_Dly,0,1001);
    ModbusDataPro_Uint16(&RunData.ModbusData[143],&ParaData.FaultProtect.Module_Irms,0,5000);
    ModbusDataPro_Uint16(&RunData.ModbusData[144],&ParaData.FaultProtect.Module_Irms_Dly,0,1001);
    ModbusDataPro_Uint16(&RunData.ModbusData[145],&ParaData.Module_NUM,0,20);
    ModbusDataPro_Uint16(&RunData.ModbusData[146],&ParaData.Module_Cur_gain,0,5001);
    ModbusDataPro_Uint16(&RunData.ModbusData[147],&ParaData.Sys_Cur_gain,0,2000);
    ModbusDataPro_Float(&RunData.ModbusData[148],&ParaData.InvCtr.Udc_ref,0,1000);
    ModbusDataPro_Float(&RunData.ModbusData[149],&ParaData.InvCtr.UcapKp,0,801);
    ModbusDataPro_Float(&RunData.ModbusData[150],&ParaData.InvCtr.UcapKi,0,101);
    ModbusDataPro_Float(&RunData.ModbusData[151],&ParaData.InvCtr.UcapMax,0,1000);
    ParaData.InvCtr.UcapMin = -ParaData.InvCtr.UcapMax;
    ModbusDataPro_Float(&RunData.ModbusData[152],&ParaData.InvCtr.Transformer_k,0,3001);
    ModbusDataPro_Uint16(&RunData.ModbusData[153],&ParaData.FaultProtect.UnderURms,0,1001);
    ModbusDataPro_Uint16(&RunData.ModbusData[154],&ParaData.CMS_NUM,0,10);
    ModbusDataPro_Uint16(&RunData.ModbusData[155],&ParaData.Load_Cur_gain,0,30001);
    ModbusDataPro_Float(&RunData.ModbusData[156],&ParaData.InvCtr.Salve,0,10);
    ModbusDataPro_Float(&RunData.ModbusData[157],&ParaData.InvCtr.Salve_NUM,0,10);

    RunData.ModbusData2[52] = ParaData.FaultProtect.OverUdcPeak;
    RunData.ModbusData2[53] = ParaData.FaultProtect.OverUdcDly;
    RunData.ModbusData2[54] = ParaData.FaultProtect.Module_Ipeak;
    RunData.ModbusData2[55] = ParaData.FaultProtect.Module_Ipeak_Dly;
    RunData.ModbusData2[56] = ParaData.FaultProtect.Module_Irms;
    RunData.ModbusData2[57] = ParaData.FaultProtect.Module_Irms_Dly;
    RunData.ModbusData2[58] = Temper_muduleA_obj.Par.FanLev;
    RunData.ModbusData2[59] = Temper_muduleA_obj.Par.ParHighLev2;
    RunData.ModbusData2[60] = ParaData.Module1_ID;
    RunData.ModbusData2[61] = ParaData.Module_Cur_gain;

    RunData.ModbusData2[64] = ParaData.FaultProtect.OverUdcPeak;
    RunData.ModbusData2[65] = ParaData.FaultProtect.OverUdcDly;
    RunData.ModbusData2[66] = ParaData.FaultProtect.Module_Ipeak;
    RunData.ModbusData2[67] = ParaData.FaultProtect.Module_Ipeak_Dly;
    RunData.ModbusData2[68] = ParaData.FaultProtect.Module_Irms;
    RunData.ModbusData2[69] = ParaData.FaultProtect.Module_Irms_Dly;
    RunData.ModbusData2[70] = Temper_muduleA_obj.Par.FanLev;
    RunData.ModbusData2[71] = Temper_muduleA_obj.Par.ParHighLev2;
    RunData.ModbusData2[72] = ParaData.Module2_ID;
    RunData.ModbusData2[73] = ParaData.Module_Cur_gain;

    RunData.ModbusData2[76] = ParaData.FaultProtect.OverUdcPeak;
    RunData.ModbusData2[77] = ParaData.FaultProtect.OverUdcDly;
    RunData.ModbusData2[78] = ParaData.FaultProtect.Module_Ipeak;
    RunData.ModbusData2[79] = ParaData.FaultProtect.Module_Ipeak_Dly;
    RunData.ModbusData2[80] = ParaData.FaultProtect.Module_Irms;
    RunData.ModbusData2[81] = ParaData.FaultProtect.Module_Irms_Dly;
    RunData.ModbusData2[82] = Temper_muduleA_obj.Par.FanLev;
    RunData.ModbusData2[83] = Temper_muduleA_obj.Par.ParHighLev2;
    RunData.ModbusData2[84] = ParaData.Module3_ID;
    RunData.ModbusData2[85] = ParaData.Module_Cur_gain;

    RunData.ModbusData2[88] = ParaData.FaultProtect.OverUdcPeak;
    RunData.ModbusData2[89] = ParaData.FaultProtect.OverUdcDly;
    RunData.ModbusData2[90] = ParaData.FaultProtect.Module_Ipeak;
    RunData.ModbusData2[91] = ParaData.FaultProtect.Module_Ipeak_Dly;
    RunData.ModbusData2[92] = ParaData.FaultProtect.Module_Irms;
    RunData.ModbusData2[93] = ParaData.FaultProtect.Module_Irms_Dly;
    RunData.ModbusData2[94] = Temper_muduleA_obj.Par.FanLev;
    RunData.ModbusData2[95] = Temper_muduleA_obj.Par.ParHighLev2;
    RunData.ModbusData2[96] = ParaData.Module4_ID;
    RunData.ModbusData2[97] = ParaData.Module_Cur_gain;



}
