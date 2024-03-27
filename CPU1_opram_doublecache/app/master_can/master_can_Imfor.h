#ifndef     MASTER_CAN_IMFOR_H_
#define     MASTER_CAN_IMFOR_H_
//*****************************************************************************
// include
//*****************************************************************************
#include "driverlib.h"
#include "device.h"
#include "master_can.h"


//*****************************************************************************
// extern
//*****************************************************************************
extern void   can_Tx_Buff_refresh(uint8_t quantity);
extern void   can_Rx_Buff_refresh(uint8_t quantity);

#endif /* MASTER_CAN_IMFOR_H_ */
