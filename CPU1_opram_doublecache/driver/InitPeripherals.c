/*
 * Initper.c
 *
 *  Created on: 2015年12月9日
 *      Author: new
 */
#include "database.h"
#include "Dev_Init.h"
#include "Const_Defines.h"

void InitPeripheral(void)
{
    int16 i=0;
//---------------------------------------------------------------------
    EALLOW;
    ClkCfgRegs.PERCLKDIVSEL.bit.EMIF1CLKDIV = 0x1; ///1/2 of PLLSYSCLK is selected EMIF1CLK = 200M/2
    ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV = 0x0;
    EDIS;

    EALLOW;
    Emif1ConfigRegs.EMIF1MSEL.all = 0x93A5CE71;//cpu1
    EDIS;
#if 1
    //
    //ad by zz
    Emif1Regs.ASYNC_CS2_CR.all =  (         EMIF_ASYNC_ASIZE_16    | // 16Bit Memory Interface
                                            EMIF_ASYNC_TA_1        | // Turn Around time of 2 Emif Clock
                                            EMIF_ASYNC_RHOLD_8     | // Read Hold time of 1 Emif Clock
                                            EMIF_ASYNC_RSTROBE_16  | // Read Strobe time of 4 Emif Clock  //ensure 45ns
                                            EMIF_ASYNC_RSETUP_8    | // Read Setup time of 1 Emif Clock
                                            EMIF_ASYNC_WHOLD_8     | // Write Hold time of 1 Emif Clock
                                            EMIF_ASYNC_WSTROBE_16  | // Write Strobe time of 1 Emif Clock
                                            EMIF_ASYNC_WSETUP_8    | // Write Setup time of 1 Emif Clock
                                            EMIF_ASYNC_EW_DISABLE  | // Extended Wait Disable.
                                            EMIF_ASYNC_SS_DISABLE    // Strobe Select Mode Disable.
                                           );
#else
    Emif1Regs.ASYNC_CS2_CR.all =  (EMIF_ASYNC_ASIZE_16     | // 16Bit Memory Interface
                                            EMIF_ASYNC_TA_1        | // Turn Around time of 2 Emif Clock
                                            EMIF_ASYNC_RHOLD_1     | // Read Hold time of 1 Emif Clock
                                            EMIF_ASYNC_RSTROBE_16   | // Read Strobe time of 4 Emif Clock  //ensure 45ns
                                            EMIF_ASYNC_RSETUP_1    | // Read Setup time of 1 Emif Clock
                                            EMIF_ASYNC_WHOLD_1     | // Write Hold time of 1 Emif Clock
                                            EMIF_ASYNC_WSTROBE_8   | // Write Strobe time of 1 Emif Clock
                                            EMIF_ASYNC_WSETUP_1    | // Write Setup time of 1 Emif Clock
                                            EMIF_ASYNC_EW_DISABLE  | // Extended Wait Disable.
                                            EMIF_ASYNC_SS_DISABLE    // Strobe Select Mode Disable.
                                           );
#endif
    Emif1Regs.ASYNC_CS3_CR.all =  (         EMIF_ASYNC_ASIZE_16  | // 16Bit Memory Interface
                                            EMIF_ASYNC_TA_1        | // Turn Around time of 2 Emif Clock
                                            EMIF_ASYNC_RHOLD_1     | // Read Hold time of 1 Emif Clock
                                            EMIF_ASYNC_RSTROBE_16  | // Read Strobe time of 4 Emif Clock  ensure 45ns
                                            EMIF_ASYNC_RSETUP_1    | // Read Setup time of 1 Emif Clock
                                            EMIF_ASYNC_WHOLD_1     | // Write Hold time of 1 Emif Clock
                                            EMIF_ASYNC_WSTROBE_5   | // Write Strobe time of 1 Emif Clock  ensure 30ns
                                            EMIF_ASYNC_WSETUP_1    | // Write Setup time of 1 Emif Clock
                                            EMIF_ASYNC_EW_DISABLE  | // Extended Wait Disable.
                                            EMIF_ASYNC_SS_DISABLE    // Strobe Select Mode Disable.
                                           );

//------------------------------------------------------------------
    EALLOW;
//-----------------------------------
    CpuTimer1Regs.PRD.all = 200000;//100us
    CpuTimer1Regs.TPR.all  = 0;
    CpuTimer1Regs.TPRH.all = 0;
    CpuTimer1Regs.TCR.all = 0x4030;


 //--------------------------------------
	ScibRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback
									   // No parity,8 char bits,
									   // async mode, idle-line protocol
	ScibRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
	ScibRegs.SCIFFTX.bit.SCIRST = 0;
	for(i=0;i<10;i++){;}

	ScibRegs.SCICTL2.all =0x0000;
    ScibRegs.SCIHBAUD.all =0x0001;
    ScibRegs.SCILBAUD.all =0x0045; //19200
//	ScibRegs.SCIHBAUD.all =0x0000;
//	ScibRegs.SCILBAUD.all =0x0035;  //115200
	ScibRegs.SCIFFTX.all=0xE040;
	ScibRegs.SCIFFRX.all=0x2040;
	ScibRegs.SCIFFCT.all=0x0;
	ScibRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset


    //--------------------------------------
       ScicRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback
                                          // No parity,8 char bits,
                                          // async mode, idle-line protocol
       ScicRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
       ScicRegs.SCIFFTX.bit.SCIRST = 0;
       for(i=0;i<10;i++){;}

       ScicRegs.SCICTL2.all =0x0000;
  //     ScicRegs.SCIHBAUD.all =0x0001;
   //    ScicRegs.SCILBAUD.all =0x0045; //19200
       ScicRegs.SCIHBAUD.all =0x0000;
       ScicRegs.SCILBAUD.all =0x0035;  //115200
       ScicRegs.SCIFFTX.all=0xE040;
       ScicRegs.SCIFFRX.all=0x2040;
       ScicRegs.SCIFFCT.all=0x0;
       ScicRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset
 //--------------------------------------
//--------------------------------------------
  //  I2caRegs.I2CMDR.bit.IRS =0;
    I2caRegs.I2CSAR.all = 0x0050;        // Slave address - EEPROM control code

    I2caRegs.I2CPSC.all = 19;            // Prescaler - need 7-12 Mhz on module clk
    I2caRegs.I2CCLKL = 8;           // NOTE: must be non zero
    I2caRegs.I2CCLKH = 7;           // NOTE: must be non zero
    I2caRegs.I2CIER.all = 0x00;
    I2caRegs.I2CMDR.all = 0x0020;    // Take I2C out of reset
                                     // Stop I2C when suspended

    I2caRegs.I2CFFTX.all = 0x6040;   // Enable FIFO mode and TXFIFO
    I2caRegs.I2CFFRX.all = 0x2040;   // Enable RXFIFO, clear RXFFINT,

    EDIS;
//---------------------------------------------------

    EPwm1Regs.ETSEL.bit.SOCAEN    = 1;    // Disable SOC on A group
    EPwm1Regs.ETSEL.bit.SOCASEL    = 3;   // Select SOC on up-count
    EPwm1Regs.ETPS.bit.SOCAPRD = 1;       // Generate pulse on 1st event

    EPwm1Regs.TBPRD = FullPWMCounterOfInverter;             // Set timer period 801 TBCLKs
    EPwm1Regs.TBPHS.bit.TBPHS = 0x0000;  // Phase is 0
    EPwm1Regs.TBCTR = 0x0000;             // Clear counter
       // Set Compare values
    EPwm1Regs.CMPA.bit.CMPA = 2000;    // Set compare A value

    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up and down
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;
    EPwm1Regs.TBCTL.bit.SYNCOSEL = 1;              // PWM同步信号
          //
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO; // Load on Zero
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
          //
    EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;            // Set PWM1A on Zero
    EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;

    EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_LOC;
    EPwm1Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm1Regs.DBRED.bit.DBRED = 800;
    EPwm1Regs.DBFED.bit.DBFED = 800;



 /*     EALLOW;
      SyncSocRegs.SYNCSELECT.bit.EPWM4SYNCIN=0;
      SyncSocRegs.SYNCSELECT.bit.EPWM10SYNCIN=2;
      EDIS;*/

}


void ConfigureADC(void)
{
    EALLOW;

    //write configurations
    //
    AdcaRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
    AdcbRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
    AdccRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
    AdcdRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
    AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    AdcSetMode(ADC_ADCB, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    AdcSetMode(ADC_ADCC, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    AdcSetMode(ADC_ADCD, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    //Set pulse positions to late
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdcbRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdccRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdcdRegs.ADCCTL1.bit.INTPULSEPOS = 1;

    //power up the ADC
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    AdcbRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    AdccRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    AdcdRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    //delay for 1ms to allow ADC time to power up
    DELAY_US(1000);

    EDIS;
}

void SetupADCEpwm(Uint16 channel)
{
    Uint16 acqps;

    //
    //determine minimum acquisition window (in SYSCLKS) based on resolution
    //
    if(ADC_RESOLUTION_12BIT == AdcaRegs.ADCCTL2.bit.RESOLUTION)
    {
        acqps = 150; //75ns
    }
    else //resolution is 16-bit
    {
        acqps = 63; //320ns
    }

    //
    //Select the channels to convert and end of conversion flag
    //
    EALLOW;
    AdcaRegs.ADCSOC0CTL.bit.CHSEL = channel;  //SOC0 will convert pin A0
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 5; //trigger on ePWM1 SOCA/C
    AdcaRegs.ADCSOC1CTL.bit.CHSEL = 1;  //SOC0 will convert pin A0
    AdcaRegs.ADCSOC1CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = 5; //trigger on ePWM1 SOCA/C
    AdcaRegs.ADCSOC2CTL.bit.CHSEL = 2;  //SOC0 will convert pin A0
    AdcaRegs.ADCSOC2CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC2CTL.bit.TRIGSEL = 5; //trigger on ePWM1 SOCA/C
    AdcaRegs.ADCSOC3CTL.bit.CHSEL = 3;  //SOC0 will convert pin A0
    AdcaRegs.ADCSOC3CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC3CTL.bit.TRIGSEL = 5; //trigger on ePWM1 SOCA/C
    AdcaRegs.ADCSOC4CTL.bit.CHSEL = 4;  //SOC0 will convert pin A0
    AdcaRegs.ADCSOC4CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC4CTL.bit.TRIGSEL = 5; //trigger on ePWM1 SOCA/C
    AdcaRegs.ADCSOC5CTL.bit.CHSEL = 5;  //SOC0 will convert pin A0
    AdcaRegs.ADCSOC5CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC5CTL.bit.TRIGSEL = 5; //trigger on ePWM1 SOCA/C

    AdcaRegs.ADCSOC14CTL.bit.CHSEL = 14;  //SOC0 will convert pin A0
    AdcaRegs.ADCSOC14CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC14CTL.bit.TRIGSEL = 5; //trigger on ePWM1 SOCA/C

    AdcaRegs.ADCSOC15CTL.bit.CHSEL = 15;  //SOC0 will convert pin A0
    AdcaRegs.ADCSOC15CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC15CTL.bit.TRIGSEL = 5; //trigger on ePWM1 SOCA/C

    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 0; //end of SOC0 will set INT1 flag
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;   //enable INT1 flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //make sure INT1 flag is cleared

    AdcbRegs.ADCSOC6CTL.bit.CHSEL = channel;  //SOC0 will convert pin A0
    AdcbRegs.ADCSOC6CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcbRegs.ADCSOC6CTL.bit.TRIGSEL = 5; //trigger on ePWM1 SOCA/C
    AdcbRegs.ADCSOC7CTL.bit.CHSEL = 1;  //SOC0 will convert pin A0
    AdcbRegs.ADCSOC7CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcbRegs.ADCSOC7CTL.bit.TRIGSEL = 5; //trigger on ePWM1 SOCA/C
    AdcbRegs.ADCSOC8CTL.bit.CHSEL = 2;  //SOC0 will convert pin A0
    AdcbRegs.ADCSOC8CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcbRegs.ADCSOC8CTL.bit.TRIGSEL = 5; //trigger on ePWM1 SOCA/C
    AdcbRegs.ADCSOC9CTL.bit.CHSEL = 3;  //SOC0 will convert pin A0
    AdcbRegs.ADCSOC9CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcbRegs.ADCSOC9CTL.bit.TRIGSEL = 5; //trigger on ePWM1 SOCA/C

    AdccRegs.ADCSOC10CTL.bit.CHSEL = 2;  //SOC0 will convert pin A0
    AdccRegs.ADCSOC10CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdccRegs.ADCSOC10CTL.bit.TRIGSEL = 5; //trigger on ePWM1 SOCA/C
    AdccRegs.ADCSOC11CTL.bit.CHSEL = 3;  //SOC0 will convert pin A0
    AdccRegs.ADCSOC11CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdccRegs.ADCSOC11CTL.bit.TRIGSEL = 5; //trigger on ePWM1 SOCA/C
    AdccRegs.ADCSOC12CTL.bit.CHSEL = 4;  //SOC0 will convert pin A0
    AdccRegs.ADCSOC12CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdccRegs.ADCSOC12CTL.bit.TRIGSEL = 5; //trigger on ePWM1 SOCA/C

    AdcdRegs.ADCSOC13CTL.bit.CHSEL = 3;  //SOC0 will convert pin A0
    AdcdRegs.ADCSOC13CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcdRegs.ADCSOC13CTL.bit.TRIGSEL = 5; //trigger on ePWM1 SOCA/C
    AdcdRegs.ADCSOC14CTL.bit.CHSEL = 4;  //SOC0 will convert pin A0
    AdcdRegs.ADCSOC14CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcdRegs.ADCSOC14CTL.bit.TRIGSEL = 5; //trigger on ePWM1 SOCA/C
    AdcdRegs.ADCSOC15CTL.bit.CHSEL = 2;  //SOC0 will convert pin A0
    AdcdRegs.ADCSOC15CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcdRegs.ADCSOC15CTL.bit.TRIGSEL = 5; //trigger on ePWM1 SOCA/C


    EDIS;
}

#pragma CODE_SECTION(GetAdResult,"ramfuncs");
void GetAdResult(ADC_OBJ *v)
{
/*  int16 i = 0;
    int16 ad[16];

    for(i=0;i<16;i++)
    {
        ad[i] =(int16)( *(&AdcMirror.ADCRESULT0 + i)-(*(&v->adChZero->A0ZERO+i)));
    }
    for(i=0;i<16;i++)
    {
     *(&v->adresult->AdChA0+i) = *(&v->adc_gain->AdChA0Gain+i) * ad[i];
    }*/
    v->adresult->AdChA0 = v->adc_gain->AdChA0Gain*((int16)(AdcaResultRegs.ADCRESULT14) -(int16) (v->adChZero->A0ZERO));
    v->adresult->AdChB0 = v->adc_gain->AdChB0Gain*((int16)(AdcaResultRegs.ADCRESULT15) - (int16)(v->adChZero->B0ZERO));
    v->adresult->AdChA1 = v->adc_gain->AdChA1Gain*((int16)(AdcaResultRegs.ADCRESULT2) - (int16)(v->adChZero->A1ZERO));
    v->adresult->AdChB1 = v->adc_gain->AdChB1Gain*((int16)(AdcbResultRegs.ADCRESULT6) - (int16)(v->adChZero->B1ZERO));
    v->adresult->AdChA2 = v->adc_gain->AdChA2Gain*((int16)(AdcaResultRegs.ADCRESULT3) - (int16)(v->adChZero->A2ZERO));
    v->adresult->AdChB2 = v->adc_gain->AdChB2Gain*((int16)(AdcbResultRegs.ADCRESULT7) - (int16)(v->adChZero->B2ZERO));
    v->adresult->AdChA3 = v->adc_gain->AdChA3Gain*((int16)(AdcaResultRegs.ADCRESULT4) - (int16)(v->adChZero->A3ZERO));
    v->adresult->AdChB3 = v->adc_gain->AdChB3Gain*((int16)(AdcbResultRegs.ADCRESULT8) - (int16)(v->adChZero->B3ZERO));
    v->adresult->AdChA4 = v->adc_gain->AdChA4Gain*((int16)(AdcaResultRegs.ADCRESULT5) - (int16)(v->adChZero->A4ZERO));
    v->adresult->AdChB4 = v->adc_gain->AdChB4Gain*((int16)(AdcbResultRegs.ADCRESULT9) - (int16)(v->adChZero->B4ZERO));
    v->adresult->AdChA5 = v->adc_gain->AdChA5Gain*((int16)(AdccResultRegs.ADCRESULT10) - (int16)(v->adChZero->A5ZERO));
    v->adresult->AdChB5 = v->adc_gain->AdChB5Gain*((int16)(AdcdResultRegs.ADCRESULT13) - (int16)(v->adChZero->B5ZERO));
    v->adresult->AdChA6 = v->adc_gain->AdChA6Gain*((int16)(AdccResultRegs.ADCRESULT11) - (int16)(v->adChZero->A6ZERO));
    v->adresult->AdChB6 = v->adc_gain->AdChB6Gain*((int16)(AdcdResultRegs.ADCRESULT14) - (int16)(v->adChZero->B6ZERO));
    v->adresult->AdChA7 = v->adc_gain->AdChA7Gain*((int16)(AdccResultRegs.ADCRESULT12) - (int16)(v->adChZero->A7ZERO));
    v->adresult->AdChB7 = v->adc_gain->AdChB7Gain*((int16)(AdcdResultRegs.ADCRESULT15) - (int16)(v->adChZero->B7ZERO));
}

#pragma CODE_SECTION(GetExAdResult,"ramfuncs");
void GetExAdResult(EX_ADC_OBJ *v)

{
     int16 ad[24];
     int16 i=0;

     ad[0]= *CS2_AD1;
     if(ad[0]&0x8000)
     {
         ad[0] = -((~ad[0])&0x7fff);
     }
     i++;
     ad[1]= *CS2_AD1;
     if(ad[1]&0x8000)
     {
         ad[1] = -((~ad[1])&0x7fff);
     }
     i++;
     ad[2]= *CS2_AD1;
     if(ad[2]&0x8000)
     {
         ad[2] = -((~ad[2])&0x7fff);
     }
     i++;
     ad[3]= *CS2_AD1;
     if(ad[3]&0x8000)
     {
         ad[3] = -((~ad[3])&0x7fff);
     }
     i++;
     ad[4]= *CS2_AD1;
     if(ad[4]&0x8000)
     {
         ad[4] = -((~ad[4])&0x7fff);
     }
     i++;
     ad[5]= *CS2_AD1;
     if(ad[5]&0x8000)
     {
         ad[5] = -((~ad[5])&0x7fff);
     }
     i++;
     ad[6]= *CS2_AD1;
     if(ad[6]&0x8000)
     {
         ad[6] = -((~ad[6])&0x7fff);
     }
     i++;
     ad[7]= *CS2_AD1;

     if(ad[7]&0x8000)
     {
         ad[7] = -((~ad[7])&0x7fff);
     }

     i++;
     ad[8]= *CS2_AD2;
     if(ad[8]&0x8000)
     {
         ad[8] = -((~ad[8])&0x7fff);
     }

     i++;
     ad[9]= *CS2_AD2;
     if(ad[9]&0x8000)
     {
         ad[9] = -((~ad[9])&0x7fff);
     }

     i++;
     ad[10]= *CS2_AD2;
     if(ad[10]&0x8000)
     {
         ad[10] = -((~ad[10])&0x7fff);
     }
     i++;
     ad[11]= *CS2_AD2;
     if(ad[11]&0x8000)
     {
         ad[11] = -((~ad[11])&0x7fff);
     }
     i++;
     ad[12]= *CS2_AD2;
     if(ad[12]&0x8000)
     {
         ad[12] = -((~ad[12])&0x7fff);
     }
     i++;
     ad[13]= *CS2_AD2;
     if(ad[13]&0x8000)
     {
         ad[13] = -((~ad[13])&0x7fff);
     }
     i++;
     ad[14]= *CS2_AD2;
     if(ad[14]&0x8000)
     {
         ad[14] = -((~ad[14])&0x7fff);
     }
     i++;
     ad[15]= *CS2_AD2;
     if(ad[15]&0x8000)
     {
         ad[15] = -((~ad[15])&0x7fff);
     }

     i++;
     ad[16]= *CS2_AD3;
     if(ad[16]&0x8000)
     {
         ad[16] = -((~ad[16])&0x7fff);
     }

     i++;
     ad[17]= *CS2_AD3;
     if(ad[17]&0x8000)
     {
         ad[17] = -((~ad[17])&0x7fff);
     }

     i++;
     ad[18]= *CS2_AD3;
     if(ad[18]&0x8000)
     {
         ad[18] = -((~ad[18])&0x7fff);
     }
     i++;
     ad[19]= *CS2_AD3;
     if(ad[19]&0x8000)
     {
         ad[19] = -((~ad[19])&0x7fff);
     }
     i++;
     ad[20]= *CS2_AD3;
     if(ad[20]&0x8000)
     {
         ad[20] = -((~ad[20])&0x7fff);
     }
     i++;
     ad[21]= *CS2_AD3;
     if(ad[21]&0x8000)
     {
         ad[21] = -((~ad[21])&0x7fff);
     }
     i++;
     ad[22]= *CS2_AD3;
     if(ad[22]&0x8000)
     {
         ad[22] = -((~ad[22])&0x7fff);
     }
     i++;
     ad[23]= *CS2_AD3;
     if(ad[23]&0x8000)
     {
         ad[23] = -((~ad[23])&0x7fff);
     }
     v->ex_adresult->Ad1ChA1 = v->ex_adc_gain->Ad1A1Gain*(ad[0]-v->ex_adChZero->Ad1A1ZERO);
     v->ex_adresult->Ad1ChA2 = v->ex_adc_gain->Ad1A2Gain*(ad[1]-v->ex_adChZero->Ad1A2ZERO);
     v->ex_adresult->Ad1ChA3 = v->ex_adc_gain->Ad1A3Gain*(ad[2]-v->ex_adChZero->Ad1A3ZERO);
     v->ex_adresult->Ad1ChA4 = v->ex_adc_gain->Ad1A4Gain*(ad[3]-v->ex_adChZero->Ad1A4ZERO);
     v->ex_adresult->Ad1ChA5 = v->ex_adc_gain->Ad1A5Gain*(ad[4]-v->ex_adChZero->Ad1A5ZERO);
     v->ex_adresult->Ad1ChA6 = v->ex_adc_gain->Ad1A6Gain*(ad[5]-v->ex_adChZero->Ad1A6ZERO);
     v->ex_adresult->Ad1ChA7 = v->ex_adc_gain->Ad1A7Gain*(ad[6]-v->ex_adChZero->Ad1A7ZERO);
     v->ex_adresult->Ad1ChA8 = v->ex_adc_gain->Ad1A8Gain*(ad[7]-v->ex_adChZero->Ad1A8ZERO);
     v->ex_adresult->Ad2ChA1 = v->ex_adc_gain->Ad2A1Gain*(ad[8]-v->ex_adChZero->Ad2A1ZERO);
     v->ex_adresult->Ad2ChA2 = v->ex_adc_gain->Ad2A2Gain*(ad[9]-v->ex_adChZero->Ad2A2ZERO);
     v->ex_adresult->Ad2ChA3 = v->ex_adc_gain->Ad2A3Gain*(ad[10]-v->ex_adChZero->Ad2A3ZERO);
     v->ex_adresult->Ad2ChA4 = v->ex_adc_gain->Ad2A4Gain*(ad[11]-v->ex_adChZero->Ad2A4ZERO);
     v->ex_adresult->Ad2ChA5 = v->ex_adc_gain->Ad2A5Gain*(ad[12]-v->ex_adChZero->Ad2A5ZERO);
     v->ex_adresult->Ad2ChA6 = v->ex_adc_gain->Ad2A6Gain*(ad[13]-v->ex_adChZero->Ad2A6ZERO);
     v->ex_adresult->Ad2ChA7 = v->ex_adc_gain->Ad2A7Gain*(ad[14]-v->ex_adChZero->Ad2A7ZERO);
     v->ex_adresult->Ad2ChA8 = v->ex_adc_gain->Ad2A8Gain*(ad[15]-v->ex_adChZero->Ad2A8ZERO);
     v->ex_adresult->Ad3ChA1 = v->ex_adc_gain->Ad3A1Gain*(ad[16]-v->ex_adChZero->Ad3A1ZERO);
     v->ex_adresult->Ad3ChA2 = v->ex_adc_gain->Ad3A2Gain*(ad[17]-v->ex_adChZero->Ad3A2ZERO);
     v->ex_adresult->Ad3ChA3 = v->ex_adc_gain->Ad3A3Gain*(ad[18]-v->ex_adChZero->Ad3A3ZERO);
     v->ex_adresult->Ad3ChA4 = v->ex_adc_gain->Ad3A4Gain*(ad[19]-v->ex_adChZero->Ad3A4ZERO);
     v->ex_adresult->Ad3ChA5 = v->ex_adc_gain->Ad3A5Gain*(ad[20]-v->ex_adChZero->Ad3A5ZERO);
     v->ex_adresult->Ad3ChA6 = v->ex_adc_gain->Ad3A6Gain*(ad[21]-v->ex_adChZero->Ad3A6ZERO);
     v->ex_adresult->Ad3ChA7 = v->ex_adc_gain->Ad3A7Gain*(ad[22]-v->ex_adChZero->Ad3A7ZERO);
     v->ex_adresult->Ad3ChA8 = v->ex_adc_gain->Ad3A8Gain*(ad[23]-v->ex_adChZero->Ad3A8ZERO);
}

void ExAdcZeroCal(struct EX_ADC_CH_ZERO *v)
{

    int16 ad[24];
    int16 i=0;

    ad[0]= *CS2_AD1;
    if(ad[0]&0x8000)
    {
        ad[0] = -((~ad[0])&0x7fff);
    }
    i++;
    ad[1]= *CS2_AD1;
    if(ad[1]&0x8000)
    {
        ad[1] = -((~ad[1])&0x7fff);
    }
    i++;
    ad[2]= *CS2_AD1;
    if(ad[2]&0x8000)
    {
        ad[2] = -((~ad[2])&0x7fff);
    }
    i++;
    ad[3]= *CS2_AD1;
    if(ad[3]&0x8000)
    {
        ad[3] = -((~ad[3])&0x7fff);
    }
    i++;
    ad[4]= *CS2_AD1;
    if(ad[4]&0x8000)
    {
        ad[4] = -((~ad[4])&0x7fff);
    }
    i++;
    ad[5]= *CS2_AD1;
    if(ad[5]&0x8000)
    {
        ad[5] = -((~ad[5])&0x7fff);
    }
    i++;
    ad[6]= *CS2_AD1;
    if(ad[6]&0x8000)
    {
        ad[6] = -((~ad[6])&0x7fff);
    }
    i++;
    ad[7]= *CS2_AD1;

    if(ad[7]&0x8000)
    {
        ad[7] = -((~ad[7])&0x7fff);
    }

    i++;
    ad[8]= *CS2_AD2;
    if(ad[8]&0x8000)
    {
        ad[8] = -((~ad[8])&0x7fff);
    }

    i++;
    ad[9]= *CS2_AD2;
    if(ad[9]&0x8000)
    {
        ad[9] = -((~ad[9])&0x7fff);
    }

    i++;
    ad[10]= *CS2_AD2;
    if(ad[10]&0x8000)
    {
        ad[10] = -((~ad[10])&0x7fff);
    }
    i++;
    ad[11]= *CS2_AD2;
    if(ad[11]&0x8000)
    {
        ad[11] = -((~ad[11])&0x7fff);
    }
    i++;
    ad[12]= *CS2_AD2;
    if(ad[12]&0x8000)
    {
        ad[12] = -((~ad[12])&0x7fff);
    }
    i++;
    ad[13]= *CS2_AD2;
    if(ad[13]&0x8000)
    {
        ad[13] = -((~ad[13])&0x7fff);
    }
    i++;
    ad[14]= *CS2_AD2;
    if(ad[14]&0x8000)
    {
        ad[14] = -((~ad[14])&0x7fff);
    }
    i++;
    ad[15]= *CS2_AD2;
    if(ad[15]&0x8000)
    {
        ad[15] = -((~ad[15])&0x7fff);
    }
    i++;
    ad[16]= *CS2_AD3;
    if(ad[16]&0x8000)
    {
        ad[16] = -((~ad[16])&0x7fff);
    }

    i++;
    ad[17]= *CS2_AD3;
    if(ad[17]&0x8000)
    {
        ad[17] = -((~ad[17])&0x7fff);
    }

    i++;
    ad[18]= *CS2_AD3;
    if(ad[18]&0x8000)
    {
        ad[18] = -((~ad[18])&0x7fff);
    }
    i++;
    ad[19]= *CS2_AD3;
    if(ad[19]&0x8000)
    {
        ad[19] = -((~ad[19])&0x7fff);
    }
    i++;
    ad[20]= *CS2_AD3;
    if(ad[20]&0x8000)
    {
        ad[20] = -((~ad[20])&0x7fff);
    }
    i++;
    ad[21]= *CS2_AD3;
    if(ad[21]&0x8000)
    {
        ad[21] = -((~ad[21])&0x7fff);
    }
    i++;
    ad[22]= *CS2_AD3;
    if(ad[22]&0x8000)
    {
        ad[22] = -((~ad[22])&0x7fff);
    }
    i++;
    ad[23]= *CS2_AD3;
    if(ad[23]&0x8000)
    {
        ad[23] = -((~ad[23])&0x7fff);
    }
    v->Ad1A7ZERO = v->Ad1A7ZERO + ad[6];
    v->Ad3A4ZERO = v->Ad3A4ZERO + ad[19];
    v->Ad3A5ZERO = v->Ad3A5ZERO + ad[20];

    v->Ad1A1ZERO = v->Ad1A1ZERO + ad[0];
    v->Ad1A2ZERO = v->Ad1A2ZERO + ad[1];
    v->Ad1A3ZERO = v->Ad1A3ZERO + ad[2];

    v->Ad1A4ZERO = v->Ad1A4ZERO + ad[3];
    v->Ad1A5ZERO = v->Ad1A5ZERO + ad[4];
    v->Ad1A6ZERO = v->Ad1A6ZERO + ad[5];

}
