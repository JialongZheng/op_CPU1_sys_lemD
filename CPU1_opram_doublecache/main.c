#include "database.h"
#include "F28x_Project.h"
#include "Global_struct.h"
#include "INV_Control.h"
#include "Const_Defines.h"
#include "ModbusSlave.h"
#include "NandFlash.h"
#include "RecordCtrl.h"
#include "RtcDS1302.h"
#include "Dev_Init.h"
#include "Task_1ms.h"
#include "EEprom.h"
#include "master_can.h"
#include "master_can_app.h"
#include "ExRAM.h"

#include "CrcCheck.h"
//============================================================================
//#define ExRAM
//#define NANDFLAS
#define EXRAM_512K
uint16_t savecount;
#ifdef NANDFLAS
Uint16 buffflash[10];
#endif
#define RAM
#ifdef ExRAM
Uint16 wtest;//ASRAM_CS3_SIZE
Uint16 rtest;//ASRAM_CS3_SIZE
uint32_t testcount;
Uint16 testcount1;
#endif
//interrupt void adca1_isr(void)
//  BYPASS_NO_FAULT
float c1_r_array[50];
float c1_r_w_array[100];
Uint16 c1_r_w_array1[30];

#pragma DATA_SECTION(c1_r_array,"SHARERAMGS0");
#pragma DATA_SECTION(c1_r_w_array,"SHARERAMGS1");
#pragma DATA_SECTION(c1_r_w_array1,"SHARERAMGS2");


#define _FLASH  1
//-----------------------------------------------------------
void main(void)
 {
//-----------------------------------------------------
    InitSysCtrl();
//-----------------------------------------------------
    InitIpc();

    EALLOW;
//    MemCfgRegs.GSxMSEL.bit.MSEL_GS0 = 1;      // CPU2 is master for this memory
    MemCfgRegs.GSxMSEL.bit.MSEL_GS12 = 1;     // CPU2 is master for this memory
    EDIS;

    IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_FLASH);

    InitGpio();
    GpioDataRegs.GPASET.bit.GPIO12 = 1;

    DINT;

    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;

    InitPieVectTable();

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.GTBCLKSYNC = 0;
    EDIS;

    InitPeripheral();

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.GTBCLKSYNC = 1;

    EDIS;

//--------------------------------闁告劖顮�LASH缂佸顑呯花锟�-----------------------------------
    MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);

    InitFlash();

    ConfigureADC();

    SetupADCEpwm(0);

    EALLOW;
    PieVectTable.TIMER1_INT= &CpuTimer1Isr;
    PieVectTable.ADCA1_INT = &adca1_isr;
    EDIS;
    memset(&RunData, 0, sizeof(RunData));

    ModbusComServer.init = ModbusCommInit;
    ModbusComServer.run =  ModbusCommOpt;
    ModbusComServer.MonitorPar.MyAddr = 1;
    ModbusComServer.ComStatus->all = 0;

    ModbusComServer.ParDataPtr =(int16*)(&RunData.ModbusData[0]);
    ModbusComServer.ReadDataPtr = (int16*)(&RunData.ModbusData[0]);
    ModbusComServer.WriteDataPtr = (int16*)(&RunData.ModbusData[0]);
    ModbusComServer.init(&ModbusComServer);

    ModbusComServerc.run =  ModbusCommOptc;
    ModbusComServerc.MonitorPar.MyAddr = 1;
    ModbusComServerc.ComStatus->all = 0;

    ModbusComServerc.ParDataPtr =(int16*)(&RunData.ModbusData1[0]);
    ModbusComServerc.ReadDataPtr = (int16*)(&RunData.ModbusData1[0]);
    ModbusComServerc.WriteDataPtr = (int16*)(&RunData.ModbusData1[0]);
    GpioDataRegs.GPASET.bit.GPIO12 = 1;
    MODULE1_OFF
    MODULE2_OFF
    MODULE3_OFF
    MODULE4_OFF
    DELAY_US(1500*1000L);

    RtcInit();
    NandFlashInit();
    Parameter_init();
    CaltGridInit();

    CanABasic_init();
    CanBBasic_init();
    CanScan.err_box_id = 0;

    Inv_controlobj.par = &ParaData.InvCtr;
 //   NF_Data.OpNum = NF_Write_Para;
 //  NF_Operate();

    StateMachineInit();
    DELAY_US(10000L);
    DELAY_US(10000L);
    DELAY_US(10000L);
    DELAY_US(10000L);
    DELAY_US(10000L);
    NF_Operate();
    NandFlashInit();
    NF_Operate();
    RDParam_EEprom();

    Paracom();
    Paratocpu2();
    FaultProtInit();
    FilterAdinit();
    CanBScan.dev_nums = ParaData.CMS_NUM;
    ExAdcObj.ex_adChZero = &ExAdcChZero;
    RDAdcZero_EEprom();
  //  PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1; //濞达綀鍎婚崗妤禝E
    IER |=(M_INT1);
    IER |=(M_INT13);
    IpcRegs.IPCSET.bit.IPC10 = 1;

    EINT;
    ERTM;
//=========================================================
    CpuTimer1Regs.TCR.all = 0x4001;
 //   IpcRegs.IPCSET.bit.IPC10 = 1;
#ifdef NANDFLAS
    EALLOW;
    GpioCtrlRegs.GPCPUD.bit.GPIO94 = 0;   // Enable pull-up
    GpioDataRegs.GPCSET.bit.GPIO94 = 1; // Load output lower
    GpioCtrlRegs.GPCMUX2.bit.GPIO94 = 0;  //
    GpioCtrlRegs.GPCDIR.bit.GPIO94 = 1;   //
    EDIS;
    while(1)
    {
//        GpioDataRegs.GPCTOGGLE.bit.GPIO94 = 1;
//        GpioDataRegs.GPCSET.bit.GPIO94 =1;
//        DELAY_US(500000L);
//        GpioDataRegs.GPCTOGGLE.bit.GPIO94 = 1;
//        GpioDataRegs.GPCCLEAR.bit.GPIO94 =1;
//        DELAY_US(500000L);
//        ID = NF_ReadID();
//        memset(&test_data[0],0x0000,sizeof(test_data));
    //    test_data[0]= MT_ReadID(0X2020);
    //    test_data[1]=MT_ReadID(0X0000);
        //擦除后读取一次
//         GpioDataRegs.GPBDAT.bit.GPIO35 = 1;
//         NF_EraseBlock(1024);
//         GpioDataRegs.GPBDAT.bit.GPIO35 = 0;
//         Status = NF_ReadStatus();
//         DELAY_US(200);
         NF_ReadPage(303,0,&buffflash[0]);
////         Status = NF_ReadStatus();
         DELAY_US(200);
////         test_data[3] = 0;
////         for(nfi=0;nfi<512;nfi++)
////         {
////             if(ram_256k[nfi] != 0xffff)
////             {
////                 test_data[3]++;
////             }
////         }
//         //写入5678 再读取一次
//         memset(&buffflash[0],0x1,sizeof(buffflash));  //buff set 0x5678
////         DELAY_US(5000L);
//         GpioDataRegs.GPCCLEAR.bit.GPIO94 =1;
//         DELAY_US(500000L);
//         NF_WP_EN = 1;
////         GpioDataRegs.GPCSET.bit.GPIO94 =1;
////         DELAY_US(500000L);
//         NF_WritePage(1076,0,&buffflash[0]);                //write flash 5678
//         NF_WP_DIS = 1;
//         GpioDataRegs.GPCCLEAR.bit.GPIO94 =1;
//         DELAY_US(500000L);
//         GpioDataRegs.GPCCLEAR.bit.GPIO94 =1;
////         GPIO_writePin(94, 0);
////         Status = NF_ReadStatus();
////         DELAY_US(200);
//         memset(&buffflash[0],0x0000,sizeof(buffflash));  //buff set 0x0000
////         DELAY_US(200);
//         NF_ReadPage(1076,0,&buffflash[0]);                 //read buff
//         Status = NF_ReadStatus();
//         DELAY_US(200);
//         for(nfi=0;nfi<512;nfi++)
//         {
//             if(ram_256k[nfi] != 0x5555)
//             {
//                 test_data[4]++;
//             }
//         }
//         memset(&buffflash[0],0x0000,sizeof(buffflash));  //buff set 0x0000
//         NF_ReadPage(1076,0,&buffflash[0]);
//         DELAY_US(200);
//         for(nfi=0;nfi<512;nfi++)
//         {
//             if(ram_256k[nfi] != 0x5555)
//             {
//                 test_data[4]++;
//             }
//         }
    }
#endif

#ifdef ExRAM
    while(1)
    {
//        WriteMem(ASRAM_CS3_START_ADDR,wtest,1);
//        (*(volatile uint16_t *)(0x32191C+wtest)) = wtest;
        (*(volatile uint16_t *)((FAULT1_TYPE10_START)+wtest)) = wtest;
//        DELAY_US(200);
//        rtest=(*(volatile uint16_t *)(0x32191C+wtest));
        rtest=(*(volatile uint16_t *)((FAULT1_TYPE10_START)+wtest));
        wtest++;
//        testcount++;
        testcount = (volatile uint16_t *)((FAULT1_TYPE10_START)+wtest);
//        DELAY_US(200);
//        if(testcount == 0x3ffff)
//        {
////            testcount1++;
//        }
    }
#endif
    for(;;)
    {
           Comproc();
           if((RunData.StateMachine.MswReg.bits.Calibartion)&&(RunData.controlbit.bits.Bit3))
           {
               WRAdcZero_EEprom();

               RunData.StateMachine.MswReg.bits.Calibartion = 0;
               RunData.controlbit.bits.Bit3 = 0;

           }
           if((RunData.StateMachine.MswReg.bits.ParamEn == 1))
           {
//                NF_Data.Step = 0;
//                NF_Data.OpNum = NF_Write_Para;
                Paracom();
                Paratocpu2();
                WRParam_EEprom();
                FaultProtInit();
                FilterAdinit();

                RunData.ModbusData2[50] = RunData.ModbusData2[50]|0x0002;
                RunData.ModbusData2[62] = RunData.ModbusData2[62]|0x0002;
                RunData.ModbusData2[74] = RunData.ModbusData2[74]|0x0002;
                RunData.ModbusData2[86] = RunData.ModbusData2[86]|0x0002;
                RunData.StateMachine.MswReg.bits.ParamEn = 0;
            }
           CanB_receive(CanBScan.dev_nums,&CanBScan.RxB_Buff[0][0]);

            if(RunData.flagbit.bits.Bit0)
            {
//#ifdef RAM
//                NF_Data.OpNum = NF_Write_Wave;
//                NF_Data.Type = RD_Fault;
//#endif
                NF_Operate();
//#ifdef RAM
//                RunData.ModbusData1[0] = 1;//故障数据
//                RunData.ModbusData1[1] = 1;//读第一组
//                RunData.ModbusData1[2] = 2;
//                RecordData.OpNum = NF_Read_Wave;
//#endif
                    RecordCtrl();
                RunData.flagbit.bits.Bit0 = 0;
             }
            if(RunData.flagbit.bits.Bit1)
            {
               RtcProcess();
               RunData.flagbit.bits.Bit1 = 0;
           }

            if(CanScan.run_flag == 1)
            {
                CanScan.run_count++;

                if(CanScan.run_count >= ParaData.Module_NUM*3)
                {
                    CanScan.run_count = 0;
                }
                CanApp_MainFunction(ParaData.Module_NUM);
                CanScan.run_flag = 0;
//                CanApp_RX_MainFunction(ParaData.Module_NUM);
        /*        if((RunData.ModbusData2[5]&0x4000)==1)
                {
                    RunData.ModbusData2[50] = RunData.ModbusData2[50]&0xfffd;
                }
                if((RunData.ModbusData2[17]&0x4000)==1)
                {
                    RunData.ModbusData2[62] = RunData.ModbusData2[62]&0xfffd;
                }
                if((RunData.ModbusData2[29]&0x4000)==1)
                {
                    RunData.ModbusData2[74] = RunData.ModbusData2[74]&0xfffd;
                }
                if((RunData.ModbusData2[41]&0x4000)==1)
                {
                    RunData.ModbusData2[86] = RunData.ModbusData2[86]&0xfffd;
                }*/
                //
            }
            CanApp_RX_MainFunction(ParaData.Module_NUM);
            if(CanBScan.run_flag== 1)
            {
                CanBScan.run_count++;
                CanB_send(CanBScan.run_count%CanBScan.dev_nums);
                CanBScan.run_flag = 0;
            }




    }
//--------------------------------------------------------------
}


// adca1_isr - Read ADC Buffer in ISR


//#pragma CODE_SECTION(adca1_isr,"ramfuncs");

int16 aa[20]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
int16 bb[20];
int16 cc[20];
int16 jjj=0;
interrupt void adca1_isr(void)
{
    int16 h=0,i=0,hh=0;
#ifdef TEST_OP_SPEED
    static int16 vol_recovery = 0;
#endif
//    static int16 vol_hvrt = 0;
    static int16 abnor_flash_flag = 0;
    static Uint16 overtime = 0;
#ifdef TEST_ADCISR_SPEED
    led_31_ctrl(1);
#endif
    RunData.InterruptCount++;
    RunData.STATUS_CPLD0 = *CS2_STATUS0;
    RunData.STATUS_CPLD0 = *CS2_STATUS0;
#ifdef BYPASS_NO_FAULT
    RunData.STATUS_CPLD0 = DataBit_Reset(RunData.STATUS_CPLD0,2);
    RunData.STATUS_CPLD0 = DataBit_Set(RunData.STATUS_CPLD0,3);
    RunData.STATUS_CPLD0 = DataBit_Set(RunData.STATUS_CPLD0,4);
#endif
    RunData.STATUS_CPLD1 = *CS2_STATUS1;         //  0 1 neg
    RunData.STATUS_CPLD1 = *CS2_STATUS1;
    i++;
    i++;
    RunData.START_AD = *CS2_RESET_AD1;
    i++;
    RunData.START_AD = *CS2_CONVST;
    *CS2_DSP_FPGA1 = 201;
    *CS2_DSP_FPGA1 = 201;
    RunData.STATUS_CPLD2  = *CS2_FPGA_DSP1;
    RunData.STATUS_CPLD2  = *CS2_FPGA_DSP1;

    AdcObj.run(&AdcObj);

    for(h=0;h<50;h++)
    {
    }
    if(RunData.StateMachine.MswReg.bits.Calibartion == 0)
    {
        ExAdcObj.run(&ExAdcObj);
    }
 //   ExAdcObj.run(&ExAdcObj);

    FilterAdData();
#ifdef TEST_OP_SPEED
    vol_recovery= !vol_recovery;
    op_A.tx.bit.fun = RunData.ModbusData[350] ;
    op_A.tx.bit.data1 = RunData.ModbusData[351] ;
    op_A.tx.bit.data2 = RunData.ModbusData[352] ;
//    led_30_ctrl(op_A.tx.bit.fun);
#else

    if(       (RunData.StateMachine.FaultCode0Reg.all) \
            ||(RunData.StateMachine.FaultCode1Reg.all) \
            ||(RunData.StateMachine.FaultCode2Reg.all) \
            ||(RunData.StateMachine.FaultCode3Reg.all)  )
        op_A.tx.bit.fun = 2;
    else
        op_A.tx.bit.fun = RunData.StateMachine.MswReg.bits.Gridabnomal;
#ifdef OPDATA_TEST
    op_A.tx.bit.fun = RunData.ModbusData[350];
    op_A.tx.bit.data1 = RunData.ModbusData[351];
    op_A.tx.bit.data2 = RunData.ModbusData[352];
#else
    op_A.tx.bit.data1 = (Uint16)(0.05*c1_r_array[17]);
    op_A.tx.bit.data2 = (Uint16)(0.05*c1_r_array[18]);
    RunData.ModbusData[350] = op_A.tx.bit.fun;
    RunData.ModbusData[351] = op_A.tx.bit.data1;
    RunData.ModbusData[352] = op_A.tx.bit.data2;
//    RunData.ModbusData[357] = get_16posedge(RunData.ModbusData[353],RunData.ModbusData[357]);
//    RunData.ModbusData[359] = get_16posedge(RunData.ModbusData[358],RunData.ModbusData[359]);
#endif
//    op_A.tx.bit.fun = RunData.ModbusData[350] ;
//    op_A.tx.bit.data1 = RunData.ModbusData[351] ;
//    op_A.tx.bit.data2 = RunData.ModbusData[352] ;
#endif
        op_tx(&op_A);
        op_rx(&op_A);
    //if( op_rx(&op_A) ==1 )
    {

#ifdef TEST_OP_SPEED
//        led_31_ctrl(op_A.rx.bit.fun);
#endif
        RunData.ModbusData[354] = op_A.rx.bit.fun;
        RunData.ModbusData[355] = op_A.rx.bit.data1;
        RunData.ModbusData[356] = op_A.rx.bit.data2;
        c1_r_w_array1[2] = op_A.rx.bit.fun;//璺岃惤鏍囧織浣�   1闇�瑕佽ˉ鍋�
        c1_r_w_array1[3] = op_A.rx.bit.data1;
        c1_r_w_array1[4] = op_A.rx.bit.data2;
        if(op_A.rx.bit.fun == 2)
            RunData.StateMachine.FaultCode4Reg.bits.op_slave = 1;
        if(get_posedge(RunData.StateMachine.FaultCode4Reg.bits.op_slave) == 1)
            RunData.ModbusData[358] += 1;
#ifdef OPDATA_TEST
        if(op_A.rx.bit.fun != op_A.tx.bit.fun \
           || op_A.rx.bit.data1 != op_A.tx.bit.data1 \
           || op_A.rx.bit.data2 != op_A.tx.bit.data2 )
            RunData.ModbusData[359] += 1;
#endif
        // else
        //     RunData.StateMachine.FaultCode4Reg.bits.op_slave = 0;

    }
//    RunData.ModbusData[358] = op_A.crc;
//    RunData.ModbusData[359] = op_A.header;
    c1_r_w_array[0] = RunData.FilteredData.GridUa0;
    c1_r_w_array[1] = RunData.FilteredData.GridUb0;
    c1_r_w_array[2] = RunData.FilteredData.GridUc0;
    c1_r_w_array[3] = RunData.FilteredData.LoadUa0;
    c1_r_w_array[4] = RunData.FilteredData.LoadUb0;
    c1_r_w_array[5] = RunData.FilteredData.LoadUc0;
    c1_r_w_array[6] = RunData.FilteredData.IgbtIa0;
    c1_r_w_array[7] = RunData.FilteredData.IgbtIb0;
    c1_r_w_array[8] = RunData.FilteredData.IgbtIc0;
    c1_r_w_array[9] = RunData.FilteredData.SysIa0;
    c1_r_w_array[10] = RunData.FilteredData.SysIb0;
    c1_r_w_array[11] = RunData.FilteredData.SysIc0;
    c1_r_w_array[12] = RunData.GridData.Ucapa_vol;//RunData.FilteredData.Udc;
    c1_r_w_array[13] = RunData.FilteredData.Ucap;
    c1_r_w_array[14] = RunData.InvControlInput.Idref;
    c1_r_w_array[15] = 1.732*RunData.GridData.Ucapa_s;
    if(RunData.StateMachine.MswReg.bits.TestMode)
    {
        c1_r_w_array[15] = 0.0025;
    }
    c1_r_w_array1[0] = RunData.StateMachine.MswReg.all;
    c1_r_w_array1[1] = Inv_controlobj.CtlINVMode;
  //  c1_r_w_array1[2] =   璺岃惤鏍囧織浣�   1闇�瑕佽ˉ鍋�
  //  c1_r_w_array1[3] =    (Uint16)(0.05*c1_r_array[17]);  鎻掑叆鍏夌氦鍊�
   //  c1_r_w_array1[4] =   (Uint16)(0.05*c1_r_array[18]);
//    c1_r_w_array1[2] = op_A.rx_data[0];//璺岃惤鏍囧織浣�   1闇�瑕佽ˉ鍋�
//    c1_r_w_array1[3] = op_A.rx_data[1];
//    c1_r_w_array1[4] = op_A.rx_data[2];
    IPCLtoRFlagSet(IPC_FLAG10);

    FastFaultProtProc();

    if((RunData.StateMachine.MswReg.bits.GridCompen)&&(RunData.InterruptCount%10==0))
    {
        overtime++;
#ifdef BYPASS_NO_FAULT
#else
        if(overtime>10000)
        {
            RunData.StateMachine.FaultCode3Reg.bits.OverTimeInvOut =1;
        }
#endif
    }
    if(RunData.StateMachine.MswReg.bits.GridCompen==0)
    {
        overtime = 0;
    }


    RunData.InvControlOutput.GridVda = c1_r_array[0];
    RunData.InvControlOutput.GridVdb = c1_r_array[1];
    RunData.InvControlOutput.GridVdc = c1_r_array[2];
    RunData.InvControlOutput.GridUd = c1_r_array[3];
    RunData.InvControlOutput.GridUq = c1_r_array[4];
    RunData.InvControlOutput.InvVdp = c1_r_array[5];
    RunData.InvControlOutput.InvVqp = c1_r_array[6];
    RunData.InvControlOutput.LoadIdp = c1_r_array[7];
    RunData.InvControlOutput.LoadIqp = c1_r_array[8];
    RunData.InvControlOutput.GridAFrequency = c1_r_array[9];
    RunData.InvControlOutput.GridBFrequency = c1_r_array[10];
    RunData.InvControlOutput.GridCFrequency = c1_r_array[11];


    Inv_controlobj.CtlMcwReg.all = (Uint16)c1_r_array[12];

  //  c1_r_array[17];
  //  c1_r_array[18]

    RunData.StateMachine.MswReg.bits.GridCompenpre = RunData.StateMachine.MswReg.bits.Gridabnomal;

    RunData.StateMachine.MswReg.bits.Gridabnomal = Inv_controlobj.CtlMcwReg.bits.Gridabnomal;
 //   if(((Inv_controlobj.CtlMcwReg.bits.GridSwitch==0))&&(RunData.StateMachine.MswReg.bits.Gridabnomal)&&(RunData.GridData.Ucapa_vol>Inv_controlobj.par->Ucap_Dvr_quit))
    if((RunData.StateMachine.MswReg.bits.Gridabnomal)&&(RunData.GridData.Ucapa_vol>Inv_controlobj.par->Ucap_Dvr_quit))
    {
        RunData.StateMachine.MswReg.bits.GridCompen = 1;
    }
    else
    {
        RunData.StateMachine.MswReg.bits.GridCompen = 0;
    }

    if(RunData.StateMachine.MswReg.bits.GridCompenpre)
    {
        RunData.StateMachine.StatusReg2.bits.GridAbtype = RunData.StateMachine.StatusReg2.bits.GridHvrt;
    }

    RunData.StateMachine.StatusReg2.bits.GridAbnormal = RunData.StateMachine.MswReg.bits.Gridabnomal;
    RunData.StateMachine.StatusReg2.bits.GridLvrt = Inv_controlobj.CtlMcwReg.bits.GridLvrt;
    RunData.StateMachine.StatusReg2.bits.GridHvrt = Inv_controlobj.CtlMcwReg.bits.GridHvrt;

//     if(RunData.InterruptCount%2==0)//delete
     if(RunData.InterruptCount%4==0)//change
     {
         h = NF_Data.SampIndex;
         hh = NF_Data.SampFltIndex;//故障保存计数
         if(NF_Data.FltRdEn == 1)//只有在RAM缓存1写入flash时不进行写RAM
         {
             //故障缓存
             //write ram cache add
             //故障数据缓存
#ifdef RAM
             SampBuf[0][hh] = (int16)savecount;
             SampBuf[1][hh] = (int16)0x0001;
             SampBuf[2][hh] = (int16)0x0001;
             SampBuf[3][hh] = (int16)0x0001;
             SampBuf[4][hh] = (int16)0x0001;
             SampBuf[5][hh] = (int16)0x0001;
             SampBuf[6][hh] = (int16)0x0001;
             SampBuf[7][hh] = (int16)0x0001;
             SampBuf[8][hh] = (int16)0x0001;
             SampBuf[9][hh] =  (int16)0x0001;
             SampBuf[10][hh] = (int16)0x0001;
             SampBuf[11][hh] = (int16)0x0001;
             SampBuf[12][hh] = (int16)0x0001;
             SampBuf[13][hh] = (int16)0x0001;
#else
             NF_Data.SampBuf[0][hh] = (int16)RunData.FilteredData.GridUa0;
             NF_Data.SampBuf[1][hh] = (int16)RunData.FilteredData.GridUb0;
             NF_Data.SampBuf[2][hh] = (int16)RunData.FilteredData.GridUc0;
             NF_Data.SampBuf[3][hh] = (int16)RunData.FilteredData.LoadUa0;
             NF_Data.SampBuf[4][hh] = (int16)RunData.FilteredData.LoadUb0;
             NF_Data.SampBuf[5][hh] = (int16)RunData.FilteredData.LoadUc0;
             NF_Data.SampBuf[6][hh] = (int16)RunData.FilteredData.IgbtIa0;
             NF_Data.SampBuf[7][hh] = (int16)RunData.FilteredData.IgbtIb0;
             NF_Data.SampBuf[8][hh] = (int16)RunData.FilteredData.IgbtIc0;
             NF_Data.SampBuf[9][hh] =  (int16)RunData.FilteredData.SysIa0;
             NF_Data.SampBuf[10][hh] = (int16)RunData.FilteredData.SysIb0;
             NF_Data.SampBuf[11][hh] = (int16)RunData.FilteredData.SysIc0;
             NF_Data.SampBuf[12][hh] = (int16)RunData.FilteredData.Udc;
             NF_Data.SampBuf[13][hh] = (int16)RunData.FilteredData.Ucap;
#endif
         }
         if(NF_Data.FltRdEn2 == 1)//只有在RAM缓存2写入flash时不写RAM add
         {
             //write ram cache add
             //第二组故障数据缓存
#ifdef RAM
             SampBuf2[0][hh] = (int16)savecount;
             SampBuf2[1][hh] = (int16)0x0002;
             SampBuf2[2][hh] = (int16)0x0002;
             SampBuf2[3][hh] = (int16)0x0002;
             SampBuf2[4][hh] = (int16)0x0002;
             SampBuf2[5][hh] = (int16)0x0002;
             SampBuf2[6][hh] = (int16)0x0002;
             SampBuf2[7][hh] = (int16)0x0002;
             SampBuf2[8][hh] = (int16)0x0002;
             SampBuf2[9][hh] =  (int16)0x0002;
             SampBuf2[10][hh] = (int16)0x0002;
             SampBuf2[11][hh] = (int16)0x0002;
             SampBuf2[12][hh] = (int16)0x0002;
             SampBuf2[13][hh] = (int16)0x0002;
#else
             SampBuf2[0][hh] = (int16)RunData.FilteredData.GridUa0;
             SampBuf2[1][hh] = (int16)RunData.FilteredData.GridUb0;
             SampBuf2[2][hh] = (int16)RunData.FilteredData.GridUc0;
             SampBuf2[3][hh] = (int16)RunData.FilteredData.LoadUa0;
             SampBuf2[4][hh] = (int16)RunData.FilteredData.LoadUb0;
             SampBuf2[5][hh] = (int16)RunData.FilteredData.LoadUc0;
             SampBuf2[6][hh] = (int16)RunData.FilteredData.IgbtIa0;
             SampBuf2[7][hh] = (int16)RunData.FilteredData.IgbtIb0;
             SampBuf2[8][hh] = (int16)RunData.FilteredData.IgbtIc0;
             SampBuf2[9][hh] =  (int16)RunData.FilteredData.SysIa0;
             SampBuf2[10][hh] = (int16)RunData.FilteredData.SysIb0;
             SampBuf2[11][hh] = (int16)RunData.FilteredData.SysIc0;
             SampBuf2[12][hh] = (int16)RunData.FilteredData.Udc;
             SampBuf2[13][hh] = (int16)RunData.FilteredData.Ucap;
#endif
         }
         //故障采样点索引=hh(最大1000) 故障读flash标志位
          if((NF_Data.SampFltIndex==NF_Data.FltIndex)&&(NF_Data.FltEn == 1))////故障保存计数——需要的波形数&&发生故障
         {
//			 if((NF_Data.FltRdEn==1)||(NF_Data.FltRdEn2==1))
//			 {
			     NF_Data.WriteFltcache = !NF_Data.WriteFltcache;
			     savecount++;
                 if(NF_Data.WriteFltcache)//故障缓存切换
                 {
                     NF_Data.FltRdEn = 0;//RAM1写flash的时候不可以继续写RAM1
                 }
#ifdef RAM
                 else
                 {
                     NF_Data.FltRdEn2 = 0;//RAM2写flash的时候不可以继续写RAM2
                 }
//			 }
#endif
             NF_Data.FltWEn = 1;//数据缓存够了可以写故障参数到flash
             NF_Data.FltEn = 0;//故障读flash标志位失能
         }

         if(NF_Data.NowRdEn == 1)
         {
             //电压异常峰值数据采样缓存开始，除了写的时候都在缓存

             //write ram cache add
             //峰值数据缓存
             SampBuf_Start[0][h] = (int16)RunData.FilteredData.GridUa0;//电网电压A
             SampBuf_Start[1][h] = (int16)RunData.FilteredData.GridUb0;//电网电压B
             SampBuf_Start[2][h] = (int16)RunData.FilteredData.GridUc0;//电网电压C
             SampBuf_Start[3][h] = (int16)RunData.FilteredData.LoadUa0;//逆变电压A
             SampBuf_Start[4][h] = (int16)RunData.FilteredData.LoadUb0;//逆变电压B
             SampBuf_Start[5][h] = (int16)RunData.FilteredData.LoadUc0;//逆变电压B
             SampBuf_Start[6][h] = (int16)RunData.FilteredData.IgbtIa0;//模块电流A
             SampBuf_Start[7][h] = (int16)RunData.FilteredData.IgbtIb0;//模块电流B
             SampBuf_Start[8][h] = (int16)RunData.FilteredData.IgbtIc0;//模块电流C
             SampBuf_Start[9][h] =  (int16)RunData.FilteredData.SysIa0;//系统电流A
             SampBuf_Start[10][h] = (int16)RunData.FilteredData.SysIb0;//系统电流B
             SampBuf_Start[11][h] = (int16)RunData.FilteredData.SysIc0;//系统电流C
             SampBuf_Start[12][h] = (int16)RunData.FilteredData.Udc;//母线电压
             SampBuf_Start[13][h] = (int16)RunData.FilteredData.Ucap;//超容电压
         }
#ifdef EXRAM_512K
         if(NF_Data.NowRdEn2 == 1)
         {
             //write ram cache add
             //峰值数据缓存
             SampBuf2_Start[0][h] = (int16)RunData.FilteredData.GridUa0;//电网电压A
             SampBuf2_Start[1][h] = (int16)RunData.FilteredData.GridUb0;//电网电压B
             SampBuf2_Start[2][h] = (int16)RunData.FilteredData.GridUc0;//电网电压C
             SampBuf2_Start[3][h] = (int16)RunData.FilteredData.LoadUa0;//逆变电压A
             SampBuf2_Start[4][h] = (int16)RunData.FilteredData.LoadUb0;//逆变电压B
             SampBuf2_Start[5][h] = (int16)RunData.FilteredData.LoadUc0;//逆变电压B
             SampBuf2_Start[6][h] = (int16)RunData.FilteredData.IgbtIa0;//模块电流A
             SampBuf2_Start[7][h] = (int16)RunData.FilteredData.IgbtIb0;//模块电流B
             SampBuf2_Start[8][h] = (int16)RunData.FilteredData.IgbtIc0;//模块电流C
             SampBuf2_Start[9][h] =  (int16)RunData.FilteredData.SysIa0;//系统电流A
             SampBuf2_Start[10][h] = (int16)RunData.FilteredData.SysIb0;//系统电流B
             SampBuf2_Start[11][h] = (int16)RunData.FilteredData.SysIc0;//系统电流C
             SampBuf2_Start[12][h] = (int16)RunData.FilteredData.Udc;//母线电压
             SampBuf2_Start[13][h] = (int16)RunData.FilteredData.Ucap;//超容电压
         }
#endif
         //扰动索引(7500)
         if((NF_Data.SampIndex==NF_Data.Index)&&(NF_Data.CmpEn == 1))//缓存采样完毕&&发生扰动
         {
#ifdef EXRAM_512K
             NF_Data.WriteNowcache = !NF_Data.WriteNowcache;//切缓存
             if(NF_Data.WriteNowcache)//故障次数
#endif
             {
                 NF_Data.NowRdEn = 0;//RAM1写flash的时候不可以继续写RAM1
             }
#ifdef EXRAM_512K
             else
             {
                 NF_Data.NowRdEn2 = 0;;//RAM2写flash的时候不可以继续写RAM2
             }
#endif
             NF_Data.CmpEn = 0;//扰动标志位复位
             NF_Data.WEn = 1;
         }

         if(++h>=SAMP_NUM)//如果超过电压异常缓存点
         {
                  h = 0;
         }
//         if((NF_Data.FltRdEn==1)||(NF_Data.FltRdEn2==1))
//         {
         if(++hh>=SAMP_NUM_FLT)//如果超过故障缓存点
         {
             hh = 0;
         }
//         }
          NF_Data.SampIndex = h;//峰值&有效值采样点缓存数量
          NF_Data.SampFltIndex = hh;//故障采样点

          if((RunData.InterruptCount%CYCLE_NUM==0)&&(NF_Data.RmsRdEn==1))
          {
             h = NF_Data.SampRmsIdx;
             //write ram cache1
             //有效值数据缓存
             AbnRms[0][h] = (int16)(RunData.GridData.GridUa1Rms*0.707);
             AbnRms[1][h] = (int16)(RunData.GridData.GridUb1Rms*0.707);
             AbnRms[2][h] = (int16)(RunData.GridData.GridUc1Rms*0.707);
             AbnRms[3][h] = (int16)RunData.GridData.LoadUaRms;
             AbnRms[4][h] = (int16)RunData.GridData.LoadUbRms;
             AbnRms[5][h] = (int16)RunData.GridData.LoadUcRms;

//             NF_Data.AbnRms2[0][h] = (int16)(RunData.GridData.GridUa1Rms*0.707);
//             NF_Data.AbnRms2[1][h] = (int16)(RunData.GridData.GridUb1Rms*0.707);
//             NF_Data.AbnRms2[2][h] = (int16)(RunData.GridData.GridUc1Rms*0.707);
//             NF_Data.AbnRms2[3][h] = (int16)RunData.GridData.LoadUaRms;
//             NF_Data.AbnRms2[4][h] = (int16)RunData.GridData.LoadUbRms;
//             NF_Data.AbnRms2[5][h] = (int16)RunData.GridData.LoadUcRms;


             if(++h>=NF_DataNum_Rms)
             {
                 h = 0;
             }

              NF_Data.SampRmsIdx = h;

              if((NF_Data.SampRmsIdx==NF_Data.RmsIdx)&&(NF_Data.RmsCmpEn==1))
              {
                 NF_Data.RmsCmpEn = 0;
                 NF_Data.RmsRdEn = 0;
              }
           }
           else if((NF_Data.RmsRdEn==0)&&(NF_Data.OpNum==0))
           {
                   NF_Data.Step = 0;
                   NF_Data.OpNum = NF_Write_AbnRms;
                   RecordData.Flag_Rd =0;
           }
          if(RunData.StateMachine.MswReg.bits.Gridabnomal)
          {
              RunData.t_gridabnormal++;
          }
     }

/*     if(RunData.StateMachine.MswReg.bits.Running)
     {
        if((RunData.InvControlOutput.GridVda < Inv_controlobj.par->vdlvrt)||(RunData.InvControlOutput.GridVdb < Inv_controlobj.par->vdlvrt)||(RunData.InvControlOutput.GridVdc < Inv_controlobj.par->vdlvrt))
        {
            RunData.StateMachine.MswReg.bits.Gridabnomal = 1;
            Inv_controlobj.CtlMcwReg.bits.Gridrecovery = 0;
            RunData.StateMachine.StatusReg2.bits.GridLvrt = 1;
            vol_recovery = 0;
            vol_hvrt = 0;
            RunData.StateMachine.MswReg.bits.Compenflag_flash =1;
        }
        if((RunData.InvControlOutput.GridVda > Inv_controlobj.par->vdhvrt)||(RunData.InvControlOutput.GridVdb > Inv_controlobj.par->vdhvrt)||(RunData.InvControlOutput.GridVdc > Inv_controlobj.par->vdhvrt))
        {
            RunData.StateMachine.MswReg.bits.Gridabnomal = 1;
            Inv_controlobj.CtlMcwReg.bits.Gridrecovery = 0;
            vol_hvrt++;
            if(vol_hvrt>50)
            {
                RunData.StateMachine.StatusReg2.bits.GridHvrt = 1;
                RunData.StateMachine.StatusReg2.bits.GridAbtype = 1;
                vol_hvrt = 0;
            }
            vol_recovery = 0;
            RunData.StateMachine.MswReg.bits.Compenflag_flash = 1;
        }

     }*/



        if((RunData.StateMachine.StatusReg2.bits.GridLvrt||RunData.StateMachine.MswReg.bits.Gridabnomal)&&(RunData.StateMachine.StatusReg2.bits.GridHvrt==0))
        {
            RunData.InvControlOutput.GridVdap = MIN(fabs(RunData.InvControlOutput.GridVdap),fabs(RunData.InvControlOutput.GridVda));
            RunData.InvControlOutput.GridVdbp = MIN(fabs(RunData.InvControlOutput.GridVdbp),fabs(RunData.InvControlOutput.GridVdb));
            RunData.InvControlOutput.GridVdcp = MIN(fabs(RunData.InvControlOutput.GridVdcp),fabs(RunData.InvControlOutput.GridVdc));
        }

        if(RunData.StateMachine.StatusReg2.bits.GridHvrt)
        {
            RunData.InvControlOutput.GridVdap = MAX(RunData.InvControlOutput.GridVdap,RunData.InvControlOutput.GridVda);
            RunData.InvControlOutput.GridVdbp = MAX(RunData.InvControlOutput.GridVdbp,RunData.InvControlOutput.GridVdb);
            RunData.InvControlOutput.GridVdcp = MAX(RunData.InvControlOutput.GridVdcp,RunData.InvControlOutput.GridVdc);
        }

      if(RunData.StateMachine.McwReg.bits.IOtext==0)
      {
          if(((RunData.StateMachine.MswReg.bits.GridCompen)&&(RunData.StateMachine.MswReg.bits.Fault == 0)))
          {
              SCR_OFF
               RunData.StateMachine.StatusReg0.bits.ScrStatusA = 0;
               RunData.StateMachine.StatusReg0.bits.ScrStatusB = 0;
               RunData.StateMachine.StatusReg0.bits.ScrStatusC = 0;
          }
          else
          {
              SCR_ON
              RunData.Compenok = 1;
              RunData.StateMachine.StatusReg0.bits.ScrStatusA = 1;
              RunData.StateMachine.StatusReg0.bits.ScrStatusB = 1;
              RunData.StateMachine.StatusReg0.bits.ScrStatusC = 1;
              RunData.StateMachine.StatusReg2.bits.GridLvrt = 0;
              RunData.StateMachine.StatusReg2.bits.GridHvrt = 0;
          }
      }


       if(RunData.StateMachine.MswReg.bits.Fault)
        {
            RunData.Compenok = 0;
        }
        RunData.Gridabnormal[RunData.Gridabnormalcnt%5][13] = RunData.Compenok;
        if((RunData.StateMachine.MswReg.bits.GridCompenpre)&&(RunData.StateMachine.MswReg.bits.Gridabnomal==0))
        {
            RunData.Gridabnormal[RunData.Gridabnormalcnt%5][6] = (int16)(RunData.InvControlOutput.GridVdap*7.07);
            RunData.Gridabnormal[RunData.Gridabnormalcnt%5][7] = (int16)(RunData.InvControlOutput.GridVdbp*7.07);
            RunData.Gridabnormal[RunData.Gridabnormalcnt%5][8] = (int16)(RunData.InvControlOutput.GridVdcp*7.07);
            RunData.Gridabnormal[RunData.Gridabnormalcnt%5][9] = (int16)(10*RunData.GridData.LoadUaRms);
            RunData.Gridabnormal[RunData.Gridabnormalcnt%5][10] = (int16)(10*RunData.GridData.LoadUbRms);
            RunData.Gridabnormal[RunData.Gridabnormalcnt%5][11] = (int16)(10*RunData.GridData.LoadUcRms);
            RunData.Gridabnormal[RunData.Gridabnormalcnt%5][12] = RunData.t_gridabnormal*0.2;
            RunData.Gridabnormal[RunData.Gridabnormalcnt%5][13] = RunData.Compenok;
            RunData.Gridabnormal[RunData.Gridabnormalcnt%5][14] = RunData.StateMachine.StatusReg2.bits.GridAbtype;
            RunData.Gridabnormalcnt++;  //电压扰动事件数值+1
        }

           if((RunData.StateMachine.MswReg.bits.GridCompenpre==0)&&RunData.StateMachine.MswReg.bits.Gridabnomal)//闁哄嫷鍨粩瀛樼▔椤忓啰鐟愰柛妤�娲﹂柈锟�
           {
//               if(NF_Data.NowRdEn==1)//detele
               if((NF_Data.NowRdEn==0)&&(NF_Data.NowRdEn2==0))//add
               {
                   NF_Data.Step = 0;
                   NF_Data.Type = RD_Abnor;//电网异常
                   NF_Data.OpNum = NF_Write_Wave;//NF操作写录波
                   if(NF_Data.NowRdEn==0)
                   {
                       NF_Data.ReadNowcache = 1;
                   }
                   else if(NF_Data.NowRdEn2==0)
                   {
                       NF_Data.ReadNowcache = 0;
                   }

                   RecordData.Flag_Rd =0;//改动判断条件会不会影响这个标志位
                   RunData.StateMachine.MswReg.bits.Wave_RdOn = 0;
               }
               abnor_flash_flag = 1;
               RunData.t_gridabnormal = 0;
               RunData.Compenok = 0;
               RunData.StateMachine.StatusReg2.bits.GridAbtype = 0;
               RunData.InvControlOutput.GridVdap = RunData.InvControlOutput.GridVda;
               RunData.InvControlOutput.GridVdbp = RunData.InvControlOutput.GridVdb;
               RunData.InvControlOutput.GridVdcp = RunData.InvControlOutput.GridVdc;
               RunData.Gridabnormal[RunData.Gridabnormalcnt%5][0] = Rtc_Data.CurTime[Rtc_Year];
               RunData.Gridabnormal[RunData.Gridabnormalcnt%5][1] = Rtc_Data.CurTime[Rtc_Month];
               RunData.Gridabnormal[RunData.Gridabnormalcnt%5][2] = Rtc_Data.CurTime[Rtc_Day];
               RunData.Gridabnormal[RunData.Gridabnormalcnt%5][3] = Rtc_Data.CurTime[Rtc_Hour];
               RunData.Gridabnormal[RunData.Gridabnormalcnt%5][4] = Rtc_Data.CurTime[Rtc_Minute];
               RunData.Gridabnormal[RunData.Gridabnormalcnt%5][5] = Rtc_Data.CurTime[Rtc_Second];
           }
    /*       else if(abnor_flash_flag&&(RunData.StateMachine.MswReg.bits.Gridabnomal==0)&&(NF_Data.OpNum==0))//閻炴稏鍎辨导鈺冿拷鐟板缁狅綁宕ラ敓锟�
           {
                NF_Data.Step = 0;
                NF_Data.OpNum = NF_Write_Recd;
                abnor_flash_flag = 0;
           }*/

     //      RunData.StateMachine.MswReg.bits.GridCompenpre = RunData.StateMachine.MswReg.bits.Gridabnomal;

#if 1
 /*          op_A.tx_data[0] = RunData.ModbusData[350];
           op_A.tx_data[1] = RunData.ModbusData[351];
           op_A.tx_data[2] = RunData.ModbusData[352];
           op_tx(&op_A);
           if( op_rx(&op_A) ==1 )
           {
               RunData.ModbusData[354] = op_A.rx_data[0];
               RunData.ModbusData[355] = op_A.rx_data[1];
               RunData.ModbusData[356] = op_A.rx_data[2];
           }
           RunData.ModbusData[358] = op_A.crc;
           RunData.ModbusData[359] = op_A.header;
           */
#else
           if((RunData.InterruptCount%2)==0)
            {
          //    RunData.STATUS_CPLD1=*CS2_FPGA_DO1_L;

         //      *CS2_DSP_FPGA2 = aa[jjj];

        //      *CS2_FPGA_DO1_H = aa[jjj]+1;
              bb[jjj]  = ((*CS2_FPGA_DSP2))&0x00ff;

              jjj++;
              cc[jjj]  = ((*CS2_FPGA_DO1_L))&0x00ff;
              if(jjj==20)
              {
                  jjj=0;
              }
              aa[jjj] = 10*(jjj+1);

           //    RunData.STATUS_CPLD1=*CS2_FPGA_DO1_L;
            }
            else
            {
          //     RunData.STATUS_CPLD1=*CS2_FPGA_DO1_H;
          //      RunData.STATUS_CPLD1=*CS2_FPGA_DO1_H;
                *CS2_DSP_FPGA2 = aa[jjj];

                *CS2_FPGA_DO1_H = aa[jjj]+1;
            }
#endif
  //         bb[jjj]  = (*CS2_FPGA_DSP2)&0x00ff;
           if((RunData.controlbit.bits.Bit3 == 0)&&(RunData.Adczeroint<128)&&(RunData.StateMachine.MswReg.bits.Calibartion == 1))
           {
               RunData.Adczeroint++;
               ExAdcZeroCal(ExAdcObj.ex_adChZero);
               if(RunData.Adczeroint ==100)
               {
                   RunData.Adczeroint = 0;
                   ExAdcObj.ex_adChZero->Ad1A7ZERO = 0.01*ExAdcObj.ex_adChZero->Ad1A7ZERO;
                   ExAdcObj.ex_adChZero->Ad3A4ZERO = 0.01*ExAdcObj.ex_adChZero->Ad3A4ZERO;
                   ExAdcObj.ex_adChZero->Ad3A5ZERO = 0.01*ExAdcObj.ex_adChZero->Ad3A5ZERO;

                   ExAdcObj.ex_adChZero->Ad1A1ZERO = 0.01*ExAdcObj.ex_adChZero->Ad1A1ZERO;
                   ExAdcObj.ex_adChZero->Ad1A2ZERO = 0.01*ExAdcObj.ex_adChZero->Ad1A2ZERO;
                   ExAdcObj.ex_adChZero->Ad1A3ZERO = 0.01*ExAdcObj.ex_adChZero->Ad1A3ZERO;

                   ExAdcObj.ex_adChZero->Ad1A4ZERO = 0.01*ExAdcObj.ex_adChZero->Ad1A4ZERO;
                   ExAdcObj.ex_adChZero->Ad1A5ZERO = 0.01*ExAdcObj.ex_adChZero->Ad1A5ZERO;
                   ExAdcObj.ex_adChZero->Ad1A6ZERO = 0.01*ExAdcObj.ex_adChZero->Ad1A6ZERO;
                   RunData.controlbit.bits.Bit3 = 1;
               }
           }
#ifdef TEST_ADCISR_SPEED
    led_31_ctrl(0);
#endif

    IPCLtoRFlagClear(IPC_FLAG10);
//    led_30_ctrl(0);
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

void Paratocpu2(void)
{
    c1_r_w_array[40] = ParaData.InvCtr.CurKp;
    c1_r_w_array[41] = ParaData.InvCtr.CurKi;
    c1_r_w_array[42] = ParaData.InvCtr.CurMax;

    c1_r_w_array[43] = ParaData.InvCtr.UdcKp;
    c1_r_w_array[44] = ParaData.InvCtr.UdcKi;
    c1_r_w_array[45] = ParaData.InvCtr.UdcMax;

    c1_r_w_array[46] = ParaData.InvCtr.PllKp;
    c1_r_w_array[47] = ParaData.InvCtr.PllKi;
    c1_r_w_array[48] = ParaData.InvCtr.PllMax;

    c1_r_w_array[49] = ParaData.InvCtr.Igrid_filter_k;
    c1_r_w_array[50] = ParaData.InvCtr.vdref;
    c1_r_w_array[51] = ParaData.InvCtr.Idref;
    c1_r_w_array[52] = ParaData.InvCtr.Scrcur;
    c1_r_w_array[53] = (float)ParaData.InvCtr.t_syon;
    c1_r_w_array[54] = ParaData.InvCtr.V_diff;
    c1_r_w_array[55] = ParaData.InvCtr.vdlvrt;
    c1_r_w_array[56] = ParaData.InvCtr.vdhvrt;
    c1_r_w_array[57] = ParaData.InvCtr.Ucap_Dvr_quit;
    c1_r_w_array[58] = ParaData.InvCtr.Udc_ref;

    c1_r_w_array[59] = ParaData.InvCtr.UcapKp;
    c1_r_w_array[60] = ParaData.InvCtr.UcapKi;
    c1_r_w_array[61] = ParaData.InvCtr.UcapMax;
    c1_r_w_array[62] = ParaData.InvCtr.Transformer_k;
    c1_r_w_array[63] = ParaData.InvCtr.Salve;

    IPCLtoRFlagSet(IPC_FLAG9);
}

