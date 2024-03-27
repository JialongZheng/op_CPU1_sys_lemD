#ifndef DATABASE_H_
#define DATABASE_H_
#include "F28x_Project.h"
#include "F2837xD_Ipc_drivers.h"
#include "macro.h"
#include "math.h"
#include "inital.h"


struct MAIN_LOOP {
	unsigned long LED_CNT;
	unsigned long CLK_CNT;
	unsigned long COM_CNT;
	unsigned long n_adclk;
	unsigned long nms;
	unsigned long SEND_CNT;
	unsigned long RECEIVE_CNT;
	Uint16 POWER_ON;
};

extern struct MAIN_LOOP m_loop;





void InitPeripheral(void);


#endif /* extern "C" */
