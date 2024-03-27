#include "F2837xD_Device.h"
#include "ModbusSlave.h"
#include "Driver_Sci.h"
#include "CrcCheck.h"

SciCom MdbsSciComb;
SciCom MdbsSciComc;

int16 Func03(MODBUS_COM_SEVER_OBJ *v)	//读保持寄存器连续块的内容（1至125个寄存器0x7D）
{
	int16 start,len;
	int16 i;
	int16 tmp;
	start = v->ReceBuf[2]<<8;
	start |=v->ReceBuf[3];
	len = v->ReceBuf[4]<<8;
	len |= v->ReceBuf[5];
	v->SendBuf[0] = v->ReceBuf[0];
	v->SendBuf[1] = v->ReceBuf[1];
	v->SendBuf[2] = len*2;
	for(i = 0;i<len;i++)
	{
		tmp = *(v->ReadDataPtr+start+i);
		v->SendBuf[3+i*2] = tmp>>8;
		v->SendBuf[4+i*2] = tmp&0xff;
	}
	tmp = CrcCalc(v->SendBuf,len*2+3);
	v->SendBuf[4+len*2] = tmp>>8;
	v->SendBuf[3+len*2] = tmp&0xff;
	return len*2+5;


}
int16 Func04(MODBUS_COM_SEVER_OBJ *v)
{
	int16 start,len;
	int16 i;
	int16 tmp;
	start = v->ReceBuf[2]<<8;
	start |=v->ReceBuf[3];
	len = v->ReceBuf[4]<<8;
	len |= v->ReceBuf[5];
	v->SendBuf[0] = v->ReceBuf[0];
	v->SendBuf[1] = v->ReceBuf[1];
	v->SendBuf[2] = len*2;
	for(i = 0;i<len;i++)
	{
		tmp = *(v->ParDataPtr+start+i);
		v->SendBuf[3+i*2] = tmp>>8;
		v->SendBuf[4+i*2] = tmp&0xff;
	}
	tmp = CrcCalc(v->SendBuf,len*2+3);
	v->SendBuf[4+len*2] = tmp>>8;
	v->SendBuf[3+len*2] = tmp&0xff;
	return len*2+5;

}

int16 Func06(MODBUS_COM_SEVER_OBJ *v)	//写单个保持寄存器
{
	int16 start;
	int16 val;
	int16 tmp;
	start = v->ReceBuf[2]<<8;
	start |=v->ReceBuf[3];
	val = v->ReceBuf[4]<<8;
	val |= v->ReceBuf[5];
	*(v->WriteDataPtr+start) = val;

	v->SendBuf[0] = v->ReceBuf[0];
	v->SendBuf[1] = v->ReceBuf[1];
	v->SendBuf[2] = v->ReceBuf[2];
	v->SendBuf[3] = v->ReceBuf[3];
	*(v->WriteDataPtr+start) = val;
	v->SendBuf[4] = val>>8;
	v->SendBuf[5] = val&0x00ff;

	tmp = CrcCalc(v->SendBuf,6);
	v->SendBuf[7] = tmp>>8;
	v->SendBuf[6] = tmp&0xff;
	return 8;
}

int16 Func16(MODBUS_COM_SEVER_OBJ *v)	//写连续寄存器块（1至123个寄存器0x7B）
{
	int16 start,len;
	int16 i;
	int16 tmp;
	start = v->ReceBuf[2]<<8;
	start |=v->ReceBuf[3];
	len = v->ReceBuf[4]<<8;
	len |= v->ReceBuf[5];
	if(2*len==v->ReceBuf[6])
	{
		for(i=0;i<len;i++)
		{
			tmp = v->ReceBuf[7+i*2]<<8;
			tmp |= v->ReceBuf[8+i*2];
			*(v->ParDataPtr+i+start)=tmp;
		}
		v->SendBuf[0] = v->ReceBuf[0];
		v->SendBuf[1] = v->ReceBuf[1];
		v->SendBuf[2] = v->ReceBuf[2];
		v->SendBuf[3] = v->ReceBuf[3];
		v->SendBuf[4] = v->ReceBuf[4];
		v->SendBuf[5] = v->ReceBuf[5];
		tmp = CrcCalc(v->SendBuf,6);
		v->SendBuf[7] = tmp>>8;
		v->SendBuf[6] = tmp&0xff;
		return 8;
	}
	else
	{
		return -1;
	}

}
int16 FuncUnSupport(MODBUS_COM_SEVER_OBJ *v)
{
	int16 crc;
	v->SendBuf[0] = v->ReceBuf[0];
	v->SendBuf[1] = 0x81;
	v->SendBuf[2] = 1;
	crc = CrcCalc(v->SendBuf,3);
	v->SendBuf[3] = crc>>8;
	v->SendBuf[4] = crc&0xff;
	return 5;

}

int16 ModbusFrameOperation(MODBUS_COM_SEVER_OBJ *v,int16 num)
{
	int16  crc,crc1;
	int16 total_num;
	if(v->ReceBuf[0]!=v->MonitorPar.MyAddr)
	{
		return -1;
	}
	else
	{
		if((num < 8)||(num > 255))
		{
			v->ComStatus->bits.FrameLenErr = 1;
			return -2;
		}
		crc = CrcCalc(v->ReceBuf,num-2);
		crc1 = (*(v->ReceBuf+num-1))<<8 | (*(v->ReceBuf+num-2));
		if(crc != crc1)
		{
			v->ComStatus->bits.CrcErr = 1;
			return -3;
		}

		switch(v->ReceBuf[1])
		{
		case 3:
			total_num = Func03(v);
			break;
		case 4:
			total_num = Func04(v);
			break;
		case 6:
			total_num = Func06(v);
			break;
		case 16:
			total_num = Func16(v);
			break;
		default:
			total_num = FuncUnSupport(v);
			break;
		}

		return total_num;
	}

}

void ModbusCommInit(MODBUS_COM_SEVER_OBJ *v)
{
//	MdbsSciComb.Init(v->MonitorPar.BaudRate,SciPariNone,SciData8,SciStop1);
	Re485_Rece();
	MdbsSciComb.ClearRxFifo = ClearRxFifoCom2;
	MdbsSciComb.ClearTxFifo = ClearTxFifoCom2;
	MdbsSciComb.GetRxFifoStatus = GetRxFifoStatus2;
	MdbsSciComb.GetTxFifoStatus = GetTxFifoStatus2;
	MdbsSciComb.ReadRxFifo = ReadRxFifoCom2;
	MdbsSciComb.WriteTxFifo = WriteTxFifoCom2;
	MdbsSciComb.WriteTxFifoBlock = WriteTxFifoBlockCom2;
	MdbsSciComb.CheckSendComplete = CheckSendCompleteCom2;
	Re485c_Rece();
    MdbsSciComc.ClearRxFifo = ClearRxFifoCom3;
    MdbsSciComc.ClearTxFifo = ClearTxFifoCom3;
    MdbsSciComc.GetRxFifoStatus = GetRxFifoStatus3;
    MdbsSciComc.GetTxFifoStatus = GetTxFifoStatus3;
    MdbsSciComc.ReadRxFifo = ReadRxFifoCom3;
    MdbsSciComc.WriteTxFifo = WriteTxFifoCom3;
    MdbsSciComc.WriteTxFifoBlock = WriteTxFifoBlockCom3;
    MdbsSciComc.CheckSendComplete = CheckSendCompleteCom3;
}


void ModbusCommOpt(MODBUS_COM_SEVER_OBJ *v)
{
	static int16 rece_ptr = 0;
	static int32 frame_cnt = 0;
	static int16 flag =0;
	int16 rece_num,send_num,i=0;

	rece_num = MdbsSciComb.ReadRxFifo(v->ReceBuf+rece_ptr,16);
//	reee = rece_num ;
	if((rece_num == 0)&&flag)
	{
		frame_cnt++;
	}
	if(rece_num>0)
	{
		rece_ptr += rece_num;
	//	if(rece_ptr > MODBUS_MAX_FRAME_LEN)
	//	{
	//		rece_ptr -= rece_num;
	//	}
		flag =1;
		frame_cnt = 0;
	}

	if((frame_cnt>500)&&(rece_ptr>7))
	{
       if(v->ReceBuf[0]==v->MonitorPar.MyAddr)
       {
		   send_num = ModbusFrameOperation(v,rece_ptr);
		   Re485_Send();
		   if(send_num>0)
		   {
			   v->ComStatus->bits.ReceFrameOK = 1;
			   MdbsSciComb.WriteTxFifoBlock(v->SendBuf,send_num);
		    }
		    rece_ptr = 0;
		    frame_cnt = 0;
		    Re485_Rece();
		    flag = 0;
       }
        else
        {

  		    rece_ptr = 0;
  		    frame_cnt = 0;
  		    flag = 0;
  		    Re485_Send();
  		    for(i=0;i<200;i++)
  		    {
  			    ;
  		    }
  	    	Re485_Rece();
       }

	}

}

void ModbusCommOptc(MODBUS_COM_SEVER_OBJ *v)
{
    static int16 rece_ptr = 0;
    static int32 frame_cnt = 0;
    static int16 flag =0;
    int16 rece_num,send_num,i=0;

    rece_num = MdbsSciComc.ReadRxFifo(v->ReceBuf+rece_ptr,16);
//  reee = rece_num ;
    if((rece_num == 0)&&flag)
    {
        frame_cnt++;
    }
    if(rece_num>0)
    {
        rece_ptr += rece_num;
    //  if(rece_ptr > MODBUS_MAX_FRAME_LEN)
    //  {
    //      rece_ptr -= rece_num;
    //  }
        flag =1;
        frame_cnt = 0;
    }

    if((frame_cnt>500)&&(rece_ptr>7))
    {
       if(v->ReceBuf[0]==v->MonitorPar.MyAddr)
       {
           send_num = ModbusFrameOperation(v,rece_ptr);
           Re485c_Send();
           if(send_num>0)
           {
               v->ComStatus->bits.ReceFrameOK = 1;
               MdbsSciComc.WriteTxFifoBlock(v->SendBuf,send_num);
            }
            rece_ptr = 0;
            frame_cnt = 0;
            Re485c_Rece();
            flag = 0;
       }
        else
        {

            rece_ptr = 0;
            frame_cnt = 0;
            flag = 0;
            Re485c_Send();
            for(i=0;i<200;i++)
            {
                ;
            }
            Re485c_Rece();
       }

    }

}


