/*
 *  Driver_sci.h
 *  Created on: 2018.7.16
 *  Author: xiaogang
 */


#ifndef DRIVER_SCI_H_
#define DRIVER_SCI_H_





enum baud_sci
{
	SciBaud1200  = 1,
	SciBaud2400  = 2,
	SciBaud4800  = 3,
	SciBaud9600  = 4,
	SciBaud19200 = 5,
	SciBaud38400 = 6,
	SciBaud56000 = 7,
	SciBaud1M	 = 8,
	SciBaduMax   = 10
};

enum pari_sci
{
	SciPariNone = 1,
	SciPariOdd  = 2,
	SciPariEven = 3,
	SciPariMark = 4,
	SciPariSpace = 5
};

enum data_sci
{
	SciData5 = 1,
	SciData6 = 2,
	SciData7 = 3,
	SciData8 = 4
};

enum stop_sci
{
	SciStop1   = 1,
	SciStop1_5 = 2,
	SciStop2   = 3
};

typedef struct
{
	void (*Init)(enum baud_sci,enum pari_sci,enum data_sci,enum stop_sci);
	void (*ClearRxFifo)();
	void (*ClearTxFifo)();
	int16 (*GetRxFifoStatus)();
	int16 (*GetTxFifoStatus)();
	int16 (*ReadRxFifo)(char *,int16);
	bool (*WriteTxFifo)(char *,int16);
	bool (*WriteTxFifoBlock)(char *,int16);
	bool (*CheckSendComplete)();
	void (*SciReset)();
} SciCom;


#define	Re485_Send()	   GpioDataRegs.GPCSET.bit.GPIO68 = 1;
#define	Re485_Rece()	   GpioDataRegs.GPCCLEAR.bit.GPIO68 = 1;

#define Re485c_Send()       GpioDataRegs.GPBSET.bit.GPIO36 = 1;
#define Re485c_Rece()       GpioDataRegs.GPBCLEAR.bit.GPIO36 = 1;

int16 GetRxFifoStatus3(void);
void ClearRxFifoCom3(void);
int16 ReadRxFifoCom3(char *recebuf,int16 num);
int16 GetTxFifoStatus3(void);
void ClearTxFifoCom3(void);
bool WriteTxFifoCom3(char *sendbuf,int16 num);
bool CheckSendCompleteCom3(void);
bool WriteTxFifoBlockCom3(char *sendbuf,int16 num);
void InitCom3(enum baud_sci baudrate,enum pari_sci parity,enum data_sci charlen,enum stop_sci stopbit);
void ResetCom3(void);

int16 GetRxFifoStatus2(void);
void ClearRxFifoCom2(void);
int16 ReadRxFifoCom2(char *recebuf,int16 num);
int16 GetTxFifoStatus2(void);
void ClearTxFifoCom2(void);
bool WriteTxFifoCom2(char *sendbuf,int16 num);
bool CheckSendCompleteCom2(void);
bool WriteTxFifoBlockCom2(char *sendbuf,int16 num);
void InitCom2(enum baud_sci baudrate,enum pari_sci parity,enum data_sci charlen,enum stop_sci stopbit);
void ResetCom2(void);

#define SciCom3Default {InitCom3,\
						ClearRxFifoCom3,\
						ClearTxFifoCom3,\
						GetRxFifoStatus3,\
						GetTxFifoStatus3,\
						ReadRxFifoCom3,\
						WriteTxFifoCom3,\
						WriteTxFifoBlockCom3,\
						CheckSendCompleteCom3,\
						ResetCom3}

#define SciCombDefault {InitCom2,\
						ClearRxFifoCom2,\
						ClearTxFifoCom2,\
						GetRxFifoStatus2,\
						GetTxFifoStatus2,\
						ReadRxFifoCom2,\
						WriteTxFifoCom2,\
						WriteTxFifoBlockCom2,\
						CheckSendCompleteCom2,\
						ResetCom2}

#endif /* DRIVER_SCI_H_ */
