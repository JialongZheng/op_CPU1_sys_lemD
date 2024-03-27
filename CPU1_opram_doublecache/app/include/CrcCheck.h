/*
 *  Crc16.h
 *  Created on: 2018.7.16
 *  Author: xiaogang
 */

#ifndef CRC_CHECK_H_
#define CRC_CHECK_H_

#include "Const_Defines.h"
#include "Global_struct.h"
struct OPDAT_BITS {          // bits   description
    Uint16 fun:2;
    int16 data1:7;
    int16 data2:7;
};


union OPDAT_REG {
   Uint16              all;
   struct OPDAT_BITS  bit;
};
typedef struct
{
    Uint16 *tx_reg;
    Uint16 *rx_reg;
    union OPDAT_REG tx;
    union OPDAT_REG rx;
    Uint16 fault;
//    Uint16 tx_data[3];
//    Uint16 rx_buff[5];
//    Uint16 rx_data[3];
//    Uint16 header;
//    Uint16 crc;
}OP_COM;
#define EMIF_TO_UART_A \
{\
    CS2_DSP_FPGA2,\
    CS2_FPGA_DSP2,\
    0,\
    0\
}
extern OP_COM op_A;
void op_tx(OP_COM *op);
Uint16 op_rx(OP_COM *op);
Uint16 get_posedge(Uint16 Value );
Uint16 get_negedge(Uint16 Value );
Uint16 get_16posedge(Uint16 Value ,Uint16 chchres);

extern const int16 CrcTable[];
extern const char CrcTableHi[];
extern const char CrcTableLo[];
int16 CrcCalc8_8(char *, int16);
int16 CrcCalc(char *,int16);
int16 CrcCalcWord(int16 *p,int16 len);

#endif /* CRC16_H_ */
