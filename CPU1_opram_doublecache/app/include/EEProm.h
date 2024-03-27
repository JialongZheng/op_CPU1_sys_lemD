

#ifndef EEPROM_H
#define EEPROM_H

#include "F2837xD_i2c.h"

extern void RD_EEPROM(Uint16 Byte_Sum,Uint16 Offet_Addr,Uint16 Page_Addr);
extern void WR_EEPROM(Uint16 Byte_Sum,Uint16 Offet_Addr,Uint16 Page_Addr);

extern void Restore_Factory_Set(void);
extern void WRAdcZero_EEprom(void);
extern void RDAdcZero_EEprom(void);
extern void WRParam_EEprom(void);
extern void RDParam_EEprom(void);

extern void RD_DATA_PROCESS(Uint16 Byte_Sum);
extern void WR_DATA_PROCESS(Uint16 Word_Sum);

#endif
