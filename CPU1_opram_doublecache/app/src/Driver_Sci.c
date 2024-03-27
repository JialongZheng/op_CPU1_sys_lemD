#include "F2837xD_Device.h"
#include "Types.h"
#include "Driver_Sci.h"
 char temp1[9];
int16 GetRxFifoStatus3(void)
{
	return ScicRegs.SCIFFRX.bit.RXFFST;
}

void ClearRxFifoCom3(void)
{
	ScicRegs.SCIFFRX.bit.RXFIFORESET = 0;
	ScicRegs.SCIFFRX.bit.RXFFOVRCLR  = 1;
	ScicRegs.SCIFFRX.bit.RXFIFORESET = 1;
}

int16 ReadRxFifoCom3(char *recebuf,int16 num)
{
	int16 actual_num,temp_num,i;
	if(	ScicRegs.SCIRXST.bit.RXERROR==1)
	{
		ScicRegs.SCICTL1.bit.SWRESET = 0;
		for(i=0;i<10;i++){;};
		ScicRegs.SCICTL1.bit.SWRESET = 1;

	}
		actual_num = GetRxFifoStatus3();
		if(actual_num <= 0)
		{
			return 0;
		}
		if(num == 0)
		{
			num = actual_num;
		}
		if(actual_num > num)
		{
			actual_num = num;
		}
		temp_num = actual_num;
		while(temp_num > 0)
		{
			*recebuf = ScicRegs.SCIRXBUF.bit.SAR;
			recebuf ++;
			temp_num--;
		}
		return actual_num;

}

int16 GetTxFifoStatus3(void)
{
	return ScicRegs.SCIFFTX.bit.TXFFST;
}

void ClearTxFifoCom3(void)
{
	ScicRegs.SCIFFTX.bit.TXFIFORESET = 0;
	ScicRegs.SCIFFTX.bit.SCIRST = 0;
	ScicRegs.SCIFFTX.bit.TXFIFORESET = 1;
	ScicRegs.SCIFFTX.bit.SCIRST = 1;
}

bool WriteTxFifoCom3(char *sendbuf,int16 num)
{
	int16 empty_num;
	empty_num = 16 - GetTxFifoStatus3();
	if((empty_num <= 0) || (empty_num < num))
	{
		return FALSE;
	}
	else
	{
		while(num > 0)
		{
			ScicRegs.SCITXBUF.bit.TXDT = *sendbuf;
			sendbuf ++;
			num--;
		}
	}
	return TRUE;
}

bool CheckSendCompleteCom3(void)
{
	if(GetTxFifoStatus3()==0)
	{
		return (ScicRegs.SCICTL2.bit.TXEMPTY);
	}
	else
	{
		return FALSE;
	}
}

bool WriteTxFifoBlockCom3(char *sendbuf,int16 num)
{
	int16 empty_num;
	while(num>0)
	{
		empty_num = 16 - GetTxFifoStatus3();
		while( (empty_num>0) && (num>0) )
		{
			ScicRegs.SCITXBUF.bit.TXDT = *sendbuf;
			sendbuf++;
			empty_num--;
			num--;
		}
	}
	while(GetTxFifoStatus3()>0);
	while(ScicRegs.SCICTL2.bit.TXEMPTY == 0);
	return TRUE;	
}

int16 GetRxFifoStatus2(void)
{
	return ScibRegs.SCIFFRX.bit.RXFFST;
}

void ClearRxFifoCom2(void)
{
	ScibRegs.SCIFFRX.bit.RXFIFORESET = 0;
	ScibRegs.SCIFFRX.bit.RXFFOVRCLR  = 1;
	ScibRegs.SCIFFRX.bit.RXFIFORESET = 1;
}

int16 ReadRxFifoCom2(char *recebuf,int16 num)
{
	int16 actual_num,temp_num,i;

    if( ScibRegs.SCIRXST.bit.RXERROR==1)
    {
        ScibRegs.SCICTL1.bit.SWRESET = 0;
        for(i=0;i<10;i++){;};
        ScibRegs.SCICTL1.bit.SWRESET = 1;

    }
        actual_num = GetRxFifoStatus2();
        if(actual_num <= 0)
        {
            return 0;
        }
        if(num == 0)
        {
            num = actual_num;
        }
        if(actual_num > num)
        {
            actual_num = num;
        }
        temp_num = actual_num;
        while(temp_num > 0)
        {
            *recebuf = ScibRegs.SCIRXBUF.bit.SAR;
            recebuf ++;
            temp_num--;
        }
        return actual_num;
}

int16 GetTxFifoStatus2(void)
{
	return ScibRegs.SCIFFTX.bit.TXFFST;
}

void ClearTxFifoCom2(void)
{
	ScibRegs.SCIFFTX.bit.TXFIFORESET = 0;
	ScibRegs.SCIFFTX.bit.SCIRST = 0;
	ScibRegs.SCIFFTX.bit.TXFIFORESET = 1;
	ScibRegs.SCIFFTX.bit.SCIRST = 1;
}

bool WriteTxFifoCom2(char *sendbuf,int16 num)
{
	int16 empty_num;
	empty_num = 16 - GetTxFifoStatus2();
	if((empty_num <= 0) || (empty_num < num))
	{
		return FALSE;
	}
	else
	{
		while(num > 0)
		{
			ScibRegs.SCITXBUF.bit.TXDT = *sendbuf;
			sendbuf ++;
			num--;
		}
	}
	return TRUE;
}

bool CheckSendCompleteCom2(void)
{
	if(GetTxFifoStatus2()==0)
	{
		return (ScibRegs.SCICTL2.bit.TXEMPTY);
	}
	else
	{
		return FALSE;
	}
}

bool WriteTxFifoBlockCom2(char *sendbuf,int16 num)
{
	int16 empty_num;
	while(num>0)
	{
		empty_num = 16 - GetTxFifoStatus2();
		while( (empty_num>0) && (num>0) )
		{
			ScibRegs.SCITXBUF.bit.TXDT = *sendbuf;
			sendbuf++;
			empty_num--;
			num--;
		}
	}
	while(GetTxFifoStatus2()>0);
	while(ScibRegs.SCICTL2.bit.TXEMPTY == 0);
	return TRUE;
}
/*
// 初始化串口1 Scic,主从guangxian
void InitCom3(enum baud_sci baudrate,enum pari_sci parity,enum data_sci charlen,enum stop_sci stopbit)
{
	int i;


// 设置通讯波特率
	switch(baudrate)
	{
	case SciBaud1200:
		ScicRegs.SCIHBAUD.bit.BAUD = 0x0F;
		ScicRegs.SCILBAUD = 0x41;
		break;
	case SciBaud2400:
		ScicRegs.SCIHBAUD = 0x07;
		ScicRegs.SCILBAUD = 0xA0;
		break;
	case SciBaud4800:
		ScicRegs.SCIHBAUD = 0x03;
		ScicRegs.SCILBAUD = 0xD0;
		break;
	case SciBaud9600:
		ScicRegs.SCIHBAUD = 0x01;
		ScicRegs.SCILBAUD = 0xE7;
		break;
	case SciBaud19200:
		ScicRegs.SCIHBAUD = 0x00;
		ScicRegs.SCILBAUD = 0xF3;
		break;
	case SciBaud38400:
		ScicRegs.SCIHBAUD = 0x00;
		ScicRegs.SCILBAUD = 0x79;
		break;
	case SciBaud56000:
		ScicRegs.SCIHBAUD = 0x00;
		ScicRegs.SCILBAUD = 0x53;
		break;
	case SciBaud1M:
		ScicRegs.SCIHBAUD = 0x00;
		ScicRegs.SCILBAUD = 0x04;
		break;
	case SciBaduMax:
		ScicRegs.SCIHBAUD = 0x00;
		ScicRegs.SCILBAUD = 0x00;
		break;
	default:
		ScicRegs.SCIHBAUD = 0x00;
		ScicRegs.SCILBAUD = 0x79;
		break;
	}
// 设置校验方式
	switch(parity)
	{
	case SciPariNone:
		ScicRegs.SCICCR.bit.PARITYENA = 0;
		break;
	case SciPariOdd:
		ScicRegs.SCICCR.bit.PARITYENA = 1;
		ScicRegs.SCICCR.bit.PARITY    = 0;
		break;
	case SciPariEven:
		ScicRegs.SCICCR.bit.PARITYENA = 1;
		ScicRegs.SCICCR.bit.PARITY    = 1;
		break;
	case SciPariMark:
		ScicRegs.SCICCR.bit.PARITYENA = 0;		//2812不支持，直接禁止校验
		break;
	case SciPariSpace:
		ScicRegs.SCICCR.bit.PARITYENA = 0;		//2812不支持，直接禁止校验
		break;
	default:
		ScicRegs.SCICCR.bit.PARITYENA = 0;
		break;
	}
// 设置数据长度
	switch(charlen)
	{
	case SciData5:
		ScicRegs.SCICCR.bit.SCICHAR = 4;
		break;
	case SciData6:
		ScicRegs.SCICCR.bit.SCICHAR = 5;
		break;
	case SciData7:
		ScicRegs.SCICCR.bit.SCICHAR = 6;
		break;
	case SciData8:
		ScicRegs.SCICCR.bit.SCICHAR = 7;
		break;
	default:
		ScicRegs.SCICCR.bit.SCICHAR = 7;
		break;
	}
// 设置停止位长度
	switch(stopbit)
	{
	case SciStop1:
		ScicRegs.SCICCR.bit.STOPBITS = 0;
		break;
	case SciStop1_5:
		ScicRegs.SCICCR.bit.STOPBITS = 0;		//2812不支持1.5个停止位使用1个停止位
		break;
	case SciStop2:
		ScicRegs.SCICCR.bit.STOPBITS = 1;
		break;
	default:
		ScicRegs.SCICCR.bit.STOPBITS = 0;
		break;
	}
	ScicRegs.SCICTL1.all =0x0003;  //new cc
	ScicRegs.SCIFFTX.bit.SCIRST = 0;		//复位 SCI 收发器
	for(i=0;i<10;i++){;}
	ScicRegs.SCIFFTX.all = 0xE04F; //0xC000;			//清除复位位，使能SCI FIFO,FIFO为空，禁止发送中断
	ScicRegs.SCIFFRX.all = 0x204F;  //0x401F;			//禁止接收中断
	ScicRegs.SCIFFCT.all = 0x0000;  //0x0001;			//延时1个位
	ScicRegs.SCICTL1.all = 0x23;	//清除复位位，使能发送，使能接收
}

// 初始化串口2 SCIB 485
void InitCom2(enum baud_sci baudrate,enum pari_sci parity,enum data_sci charlen,enum stop_sci stopbit)
{
	int i;


// 设置通讯波特率
	switch(baudrate)
	{
	case SciBaud1200:
		ScibRegs.SCIHBAUD = 0x0F;
		ScibRegs.SCILBAUD = 0x41;
		break;
	case SciBaud2400:
		ScibRegs.SCIHBAUD = 0x07;
		ScibRegs.SCILBAUD = 0xA0;
		break;
	case SciBaud4800:
		ScibRegs.SCIHBAUD = 0x03;
		ScibRegs.SCILBAUD = 0xD0;
		break;
	case SciBaud9600:
		ScibRegs.SCIHBAUD = 0x01;
		ScibRegs.SCILBAUD = 0xE7;
		break;
	case SciBaud19200:
		ScibRegs.SCIHBAUD = 0x00;
		ScibRegs.SCILBAUD = 0xF3;
		break;
	case SciBaud38400:
		ScibRegs.SCIHBAUD = 0x00;
		ScibRegs.SCILBAUD = 0x79;
		break;
	case SciBaud56000:
		ScibRegs.SCIHBAUD = 0x00;
		ScibRegs.SCILBAUD = 0x53;
		break;
	case SciBaud1M:
		ScibRegs.SCIHBAUD = 0x00;
		ScibRegs.SCILBAUD = 0x04;
		break;
	case SciBaduMax:
		ScibRegs.SCIHBAUD = 0x00;
		ScibRegs.SCILBAUD = 0x00;
		break;
	default:
		ScibRegs.SCIHBAUD = 0x00;
		ScibRegs.SCILBAUD = 0x79;
		break;
	}
// 设置校验方式
	switch(parity)
	{
	case SciPariNone:
		ScibRegs.SCICCR.bit.PARITYENA = 0;
		break;
	case SciPariOdd:
		ScibRegs.SCICCR.bit.PARITYENA = 1;
		ScibRegs.SCICCR.bit.PARITY    = 0;
		break;
	case SciPariEven:
		ScibRegs.SCICCR.bit.PARITYENA = 1;
		ScibRegs.SCICCR.bit.PARITY    = 1;
		break;
	case SciPariMark:
		ScibRegs.SCICCR.bit.PARITYENA = 0;		//2812不支持，直接禁止校验
		break;
	case SciPariSpace:
		ScibRegs.SCICCR.bit.PARITYENA = 0;		//2812不支持，直接禁止校验
		break;
	default:
		ScibRegs.SCICCR.bit.PARITYENA = 0;
		break;
	}
// 设置数据长度
	switch(charlen)
	{
	case SciData5:
		ScibRegs.SCICCR.bit.SCICHAR = 4;
		break;
	case SciData6:
		ScibRegs.SCICCR.bit.SCICHAR = 5;
		break;
	case SciData7:
		ScibRegs.SCICCR.bit.SCICHAR = 6;
		break;
	case SciData8:
		ScibRegs.SCICCR.bit.SCICHAR = 7;
		break;
	default:
		ScibRegs.SCICCR.bit.SCICHAR = 7;
		break;
	}
// 设置停止位长度
	switch(stopbit)
	{
	case SciStop1:
		ScibRegs.SCICCR.bit.STOPBITS = 0;
		break;
	case SciStop1_5:
		ScibRegs.SCICCR.bit.STOPBITS = 0;		//2812不支持1.5个停止位使用1个停止位
		break;
	case SciStop2:
		ScibRegs.SCICCR.bit.STOPBITS = 1;
		break;
	default:
		ScibRegs.SCICCR.bit.STOPBITS = 0;
		break;
	}
	ScibRegs.SCICTL1.all =0x0003;  //new cc
	ScibRegs.SCIFFTX.bit.SCIRST = 0;		//复位 SCI 收发器
	for(i=0;i<10;i++){;}
	ScibRegs.SCIFFTX.all = 0xE04F; //0xC000;			//清除复位位，使能SCI FIFO,FIFO为空，禁止发送中断
	ScibRegs.SCIFFRX.all = 0x204F;  //0x401F;			//禁止接收中断
	ScibRegs.SCIFFCT.all = 0x0000;  //0x0001;			//延时1个位
	ScibRegs.SCICTL1.all = 0x23;	//清除复位位，使能发送，使能接收
//	ScibRegs.SCIFFTX.bit.TXFIFOXRESET=1;	//重新使能发送FIFO的操作
//	ScibRegs.SCIFFRX.bit.RXFIFORESET=1;	   	//重新使能接收FIFO的操作

}*/
void ResetCom3(void)
{
	int16 i;

	if(ScicRegs.SCIRXST.bit.RXERROR)
	{
		ScicRegs.SCICTL1.bit.SWRESET = 0;
		ScicRegs.SCIFFTX.bit.SCIRST = 0;		//复位 SCI 收发器
		for(i=0;i<10;i++){;};
		ScicRegs.SCICTL1.bit.SWRESET = 1;
		ScicRegs.SCIFFTX.bit.SCIRST = 1;		//enable SCI 收发器
		ScicRegs.SCIFFTX.bit.TXFIFORESET=1;	//重新使能发送FIFO的操作
		ScicRegs.SCIFFRX.bit.RXFIFORESET=1;	   	//重新使能接收FIFO的操作

	}
}
void ResetCom2(void)
{
	int16 i;
	if(ScibRegs.SCIRXST.bit.RXERROR)
	{
		ScibRegs.SCICTL1.bit.SWRESET = 0;
		ScibRegs.SCIFFTX.bit.SCIRST = 0;		//复位 SCI 收发器
		for(i=0;i<10;i++){;};
		ScibRegs.SCICTL1.bit.SWRESET = 1;
		ScibRegs.SCIFFTX.bit.SCIRST = 1;		//enable SCI 收发器
		ScibRegs.SCIFFTX.bit.TXFIFORESET=1;	//重新使能发送FIFO的操作
		ScibRegs.SCIFFRX.bit.RXFIFORESET=1;	   	//重新使能接收FIFO的操作

	}
}
