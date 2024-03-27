

#ifndef CONST_DEFINES_H
#define CONST_DEFINES_H



#define FullPWMCounterOfInverter   20000
#define T_sample                   0.0001
#define DeathArea                  800
#define GRID_FRQ      			   50.0
#define PI 			  			   3.1415926535898


#define CS2_CONVST            ((Uint16 *)0x100004)
#define CS2_AD3               ((Uint16 *)0x10000A)
#define CS2_AD2               ((Uint16 *)0x100008)
#define CS2_AD1               ((Uint16 *)0x100006)
#define CS2_RESET_AD1         ((Uint16 *)0x100002)
#define CS2_RESET_AD2         ((Uint16 *)0x100002)


#define CS2_STATUS0           ((Uint16 *)0x10000C) //Y6_reg
#define CS2_STATUS1           ((Uint16 *)0x10000E) //Y7_reg
#define CS2_DSP_FPGA1         ((Uint16 *)0x100010) //Y8_reg

#define CS2_FPGA_DSP1         ((Uint16 *)0x100012) //Y9_reg

/*
UART_A  EMIF    ADC     PCB     FPGA
RX:     Y10     T16     OPI17   FPGA_OPI[0]
TX:     Y11     U18     OPO17   FPGA_PWM[16]
*/
#define CS2_FPGA_DSP2         ((Uint16 *)0x100014) //Y10_reg
#define CS2_DSP_FPGA2         ((Uint16 *)0x100016) //Y11_reg
/*
UART_B  EMIF    ADC     PCB     FPGA
RX:     Y12     T8      OPI16   OPI16
TX:     Y13     V1      OPO16   FPGA_PWM[15]
*/
#define CS2_FPGA_DO1_L         ((Uint16 *)0x100018)  //Y12_reg
#define CS2_FPGA_DO1_H         ((Uint16 *)0x10001A)  //Y13_reg
/*
UART_C  EMIF    ADC     PCB     FPGA
RX:     Y14     T9      OPI15   OPI15
TX:     Y15     U1      OPO15   FPGA_PWM[14]
*/
#define CS2_FPGA_DSP3           ((Uint16 *)0x10001C)  //Y14_reg
#define CS2_DSP_FPGA3           ((Uint16 *)0x10001E)  //Y15_reg
/*
UART_D  EMIF    ADC     PCB     FPGA
RX:     Y16     T10     OPI14   OPI14
TX:     Y17     V2      OPO14   FPGA_PWM[13]
*/
#define CS2_FPGA_DSP4           ((Uint16 *)0x100020)  //Y16_reg
#define CS2_DSP_FPGA4           ((Uint16 *)0x100022)  //Y17_reg



#define WAVE0        ((Uint16 *)0x300000)
#define WAVE1        ((Uint16 *)0x300001)
/*#define CS2_CONVST            ((Uint16 *)0x100004)
#define CS2_AD2               ((Uint16 *)0x10000C)
#define CS2_AD1               ((Uint16 *)0x100008)
#define CS2_RESET_AD1         ((Uint16 *)0x100002)
#define CS2_RESET_AD2         ((Uint16 *)0x100002)

#define CS2_STATUS0           ((Uint16 *)0x1000A0)
#define CS2_STATUS1           ((Uint16 *)0x1000B2)
#define CS2_STATUS2           ((Uint16 *)0x1000C4)*/

#define FLASH                 ((Uint16 *)0x300002)

#define CONST1DIV3    			   0.3333333333333
#define SQRT3         			   1.7320508075689
#define ISQRT3                     0.5773672055427


#define SAMPLE_POINT 40            //用于计算有效值
#define SAMPLE_POINT_1 0.025




#define PRODUCT_ID       630
#define SOFT_VERSION     80

#define AC_BREAKER_BYPASS_TRIP_ON                        GpioDataRegs.GPBCLEAR.bit.GPIO58 = 1;
#define AC_BREAKER_BYPASS_TRIP_OFF                       GpioDataRegs.GPBSET.bit.GPIO58 = 1;

#define AC_BREAKER_BYPASS_DOWN_ON                        GpioDataRegs.GPBCLEAR.bit.GPIO59 = 1;
#define AC_BREAKER_BYPASS_DOWN_OFF                       GpioDataRegs.GPBSET.bit.GPIO59 = 1;

#define AC_KM2_ON                                        GpioDataRegs.GPBCLEAR.bit.GPIO60 = 1;
#define AC_KM2_OFF                                       GpioDataRegs.GPBSET.bit.GPIO60 = 1;

#define AC_CHARGE_ON                                     GpioDataRegs.GPACLEAR.bit.GPIO24 = 1;
#define AC_CHARGE_OFF                                    GpioDataRegs.GPASET.bit.GPIO24 = 1;

#define CAP_KM11_ON                                      GpioDataRegs.GPACLEAR.bit.GPIO25 = 1;
#define CAP_KM11_OFF                                     GpioDataRegs.GPASET.bit.GPIO25 = 1;

#define BUSCAP_DISCHARGE_ON                              GpioDataRegs.GPACLEAR.bit.GPIO26 = 1;
#define BUSCAP_DISCHARGE_OFF                             GpioDataRegs.GPASET.bit.GPIO26 = 1;

#define ERR                                              GpioDataRegs.GPACLEAR.bit.GPIO27 = 1;
#define ERR_OFF                                          GpioDataRegs.GPASET.bit.GPIO27 = 1;

#define FAULT_ON                                         GpioDataRegs.GPACLEAR.bit.GPIO22 = 1;
#define FAULT_OFF                                        GpioDataRegs.GPASET.bit.GPIO22 = 1;

#define MODULE1_ON                                       GpioDataRegs.GPCCLEAR.bit.GPIO67 = 1;
#define MODULE1_OFF                                      GpioDataRegs.GPCSET.bit.GPIO67 = 1;

#define MODULE2_ON                                       GpioDataRegs.GPBCLEAR.bit.GPIO53 = 1;
#define MODULE2_OFF                                      GpioDataRegs.GPBSET.bit.GPIO53 = 1;

#define MODULE3_ON                                       GpioDataRegs.GPACLEAR.bit.GPIO15 = 1;
#define MODULE3_OFF                                      GpioDataRegs.GPASET.bit.GPIO15 = 1;

#define MODULE4_ON                                       GpioDataRegs.GPACLEAR.bit.GPIO9 = 1;
#define MODULE4_OFF                                      GpioDataRegs.GPASET.bit.GPIO9 = 1;

#define SCR_FAN_ON                                       GpioDataRegs.GPACLEAR.bit.GPIO10 = 1;
#define SCR_FAN_OFF                                      GpioDataRegs.GPASET.bit.GPIO10 = 1;

#define REAC_FAN_ON                                      GpioDataRegs.GPACLEAR.bit.GPIO11 = 1;
#define REAC_FAN_OFF                                     GpioDataRegs.GPASET.bit.GPIO11 = 1;

#define SCR_ON                                           GpioDataRegs.GPASET.bit.GPIO12 = 1;
#define SCR_OFF                                          GpioDataRegs.GPACLEAR.bit.GPIO12 = 1;



#define RUN_ON
#define RUN_OFF









#define MAX(A,B) (A>B)?(A):(B)
#define MIN(A,B) (A<B)?(A):(B)
#define LIMIT(A,H,L) if((A) > (H))\
	{A=H;}\
	else if((A)<(L))\
	{A=L;}



#endif
