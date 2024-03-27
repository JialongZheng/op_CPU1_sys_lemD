


#include "F2837xD_device.h"
#include "EEprom.h"
#include "Const_Defines.h"
#include "Global_struct.h"
#include "Temperature.h"
#include "F2837xD_i2c.h"



int16 MsgBuffer_Send[64] = {0};
int16 MsgBuffer_Receive[64] = {0};


void RD_EEPROM(Uint16 Byte_Sum,Uint16 Offet_Addr,Uint16 Page_Addr)
{
	Uint16 i=0;
	Uint16 I2C_com=0;

	I2caRegs.I2CSAR.all = 0x50;// EEPROMĳһҳ��ַ��������豸��1010A2��ҳ��ַP1P0��ɣ�
		//����������ĳһ����֡�Ĳ�����ַ
		I2caRegs.I2CCNT = 2;

		I2caRegs.I2CDXR.all = Page_Addr; //EEPROM I2C_EEPROM_HIGH_ADDR  0x00

		I2caRegs.I2CDXR.all = Offet_Addr;//EEPROMĳһСҳ���׵�ַ
		I2caRegs.I2CMDR.all = 0x6E20;
		//���������ͺ�һ��Ҫ��һ����ʱ
		//����ʱ������0.6us(2.7~5V2us����,��AT24C08��5����
		//������������һ��ǳ���Ҫ
		I2C_com=0;
		while(I2caRegs.I2CMDR.bit.STP == 1)     //��������֮��Ĵ���
		{
			I2C_com++;
			for(i=0;i<10;i++){;}
			if(I2C_com>10000)
			{
				I2C_com=0;
		//		goto loop1;
				break;
		     }
		}
		I2caRegs.I2CMDR.bit.STP = 1; //������æ״̬
		I2caRegs.I2CCNT = Byte_Sum;

		I2caRegs.I2CMDR.all = 0x6C20;
		I2C_com=0;
		while(I2caRegs.I2CMDR.bit.STP == 1)
		{
		 	I2C_com++;
			for(i=0;i<10;i++){;}
			if(I2C_com>10000)
			{
				I2C_com=0;
			//	goto loop1;
				break;
			}
		}
		I2caRegs.I2CMDR.bit.STP = 1; //������æ״̬

		for(i=0; i<Byte_Sum; i++)
		{
			MsgBuffer_Receive[i] = I2caRegs.I2CDRR.all;
		}

}

void WR_EEPROM(Uint16 Byte_Sum,Uint16 Offet_Addr,Uint16 Page_Addr)
{

	Uint16  i=0;
	Uint16  I2C_com=0;

	I2caRegs.I2CSAR.all = 0x50;  // EEPROMĳһҳ��ַ��������豸��1010A2��ҳ��ַP1P0��ɣ�

	I2caRegs.I2CCNT = Byte_Sum+2;         // ���͵��ֽ���Byte_Sum + 2���ֽڵ�ַ��ʵ����Ч�ֽ�ÿ����෢��14���ֽڣ�

	I2caRegs.I2CDXR.all = Page_Addr;

	I2caRegs.I2CDXR.all = Offet_Addr;
	//������I2CDXR��д��Ҫ���͵��ֽ�����FIFO��
	for(i=0; i<Byte_Sum; i++)
	{
	  I2caRegs.I2CDXR.all = MsgBuffer_Send[i];
	}
	//��������(���ɷ�ʽ���ܶϵ�Ӱ�죻�ÿ�ʼģʽ����ֹͣģʽ������ģʽ�����ͣ�I2Cģ�ʹ�?

	I2caRegs.I2CMDR.all = 0x6E20;
	for(i=0;i<150;i++){;}
	I2C_com=0;
	while(I2caRegs.I2CMDR.bit.STP == 1)//��������֮��Ĵ������
	{
		I2C_com++;
		for(i=0;i<10;i++){;}
		if(I2C_com>10000)
		{
			I2C_com=0;
			//goto loop2;
			break;

		}
	}
	I2caRegs.I2CMDR.bit.STP = 1; //������æ״̬
//	I2caRegs.I2CMDR.bit.IRS = 0;//��λ
	for(i=0;i<30000;i++){;}
}



void RD_DATA_PROCESS(Uint16 Byte_Sum)
{
	Uint16  i = 0;
	Uint16  j = 0;
	Uint16  High_byte;
	Uint16  Low_byte;
	Uint16  Data_Buffer[32] = {0};

	for(i=0; i<(Byte_Sum*2); i++)
	{
		j++;
		Low_byte = MsgBuffer_Receive[i]&0x00ff;
		High_byte = MsgBuffer_Receive[++i]&0x00ff;
		High_byte = High_byte<<8;
		Data_Buffer[i-j] =  High_byte | Low_byte;
	}

	for( i=0; i<(Byte_Sum*0.5); i++ )
	{
		MsgBuffer_Receive[i] = Data_Buffer[i];
	}
}


void WR_DATA_PROCESS(Uint16 Word_Sum)
{
	Uint16  HIGH_RESVD = 0xFF00;
	Uint16  LOW_RESVD  = 0x00FF;
	Uint16  High_byte;
	Uint16  Low_byte;
	Uint16  i = 0;
	Uint16  j = 0;
	Uint16  Data_Process_Buffer = 0;
	Uint16 Dada_Buffer[32] = {0};
	for(i=0; i< Word_Sum; i++)
	{
		Dada_Buffer[i] = MsgBuffer_Send[i];
	}
	                                                      //һ���ֲ��2���ֽ�����װ��MsgBuffer_Send[]
	for(i=0; i< (Word_Sum*2); i++)
	{
		Data_Process_Buffer = Dada_Buffer[i-j];
		Low_byte = (Data_Process_Buffer & LOW_RESVD);
		MsgBuffer_Send[i] = Low_byte;
		High_byte = (Data_Process_Buffer & HIGH_RESVD);
		High_byte = High_byte>>8;
		MsgBuffer_Send[++i] = High_byte;
		j++;                                               //ע��j��ʹ�ã�Ϊ�����ڴ���Data_Buffer[]ʱ������©����
	}
}

void  RDAdcZero_EEprom()
{
   RD_EEPROM(6,0x10,0x0);
   RD_DATA_PROCESS(6);

   ExAdcObj.ex_adChZero->Ad1A7ZERO  = MsgBuffer_Receive[0];
   ExAdcObj.ex_adChZero->Ad3A4ZERO  = MsgBuffer_Receive[1];
   ExAdcObj.ex_adChZero->Ad3A5ZERO  = MsgBuffer_Receive[2];

   RD_EEPROM(12,0x20,0x0);
   RD_DATA_PROCESS(6);

   ExAdcObj.ex_adChZero->Ad1A1ZERO  = MsgBuffer_Receive[0];
   ExAdcObj.ex_adChZero->Ad1A2ZERO  = MsgBuffer_Receive[1];
   ExAdcObj.ex_adChZero->Ad1A3ZERO  = MsgBuffer_Receive[2];

   ExAdcObj.ex_adChZero->Ad1A4ZERO  = MsgBuffer_Receive[3];
   ExAdcObj.ex_adChZero->Ad1A5ZERO  = MsgBuffer_Receive[4];
   ExAdcObj.ex_adChZero->Ad1A6ZERO  = MsgBuffer_Receive[5];


}


void  WRAdcZero_EEprom()
{
//   Uint16 i=0;

//   i=0;
   MsgBuffer_Send[0] =  ExAdcObj.ex_adChZero->Ad1A7ZERO;
   MsgBuffer_Send[1] =  ExAdcObj.ex_adChZero->Ad3A4ZERO;
   MsgBuffer_Send[2] =  ExAdcObj.ex_adChZero->Ad3A5ZERO;

   WR_DATA_PROCESS(3);
   WR_EEPROM(6,0x10,0x0);

   MsgBuffer_Send[0] =  ExAdcObj.ex_adChZero->Ad1A1ZERO;
   MsgBuffer_Send[1] =  ExAdcObj.ex_adChZero->Ad1A2ZERO;
   MsgBuffer_Send[2] =  ExAdcObj.ex_adChZero->Ad1A3ZERO;

   MsgBuffer_Send[3] =  ExAdcObj.ex_adChZero->Ad1A4ZERO;
   MsgBuffer_Send[4] =  ExAdcObj.ex_adChZero->Ad1A5ZERO;
   MsgBuffer_Send[5] =  ExAdcObj.ex_adChZero->Ad1A6ZERO;

   WR_DATA_PROCESS(6);
   WR_EEPROM(12,0x20,0x0);

}

void  RDParam_EEprom()
{
	Uint16 i=0;

   RD_EEPROM(14,0x30,0x1);
   RD_DATA_PROCESS(14);

   for(i=0;i<7;i++)
   {
	   RunData.ModbusData[e_ParaFirst+i] = MsgBuffer_Receive[i];
   }

   RD_EEPROM(14,0x00,0x4);
   RD_DATA_PROCESS(14);

   for(i=0;i<7;i++)
   {
	   RunData.ModbusData[e_ParaFirst+7+i] = MsgBuffer_Receive[i];
   }

   RD_EEPROM(14,0x20,0x4);
   RD_DATA_PROCESS(14);

   for(i=0;i<7;i++)
   {
	   RunData.ModbusData[e_ParaFirst+14+i] = MsgBuffer_Receive[i];
   }

   RD_EEPROM(14,0x10,0x2);
   RD_DATA_PROCESS(14);

   for(i=0;i<7;i++)
   {
	   RunData.ModbusData[e_ParaFirst+21+i] = MsgBuffer_Receive[i];
   }

   RD_EEPROM(14,0x20,0x2);
   RD_DATA_PROCESS(14);

   for(i=0;i<7;i++)
   {
	   RunData.ModbusData[e_ParaFirst+28+i] = MsgBuffer_Receive[i];
   }

   RD_EEPROM(14,0x30,0x2);
   RD_DATA_PROCESS(14);

   for(i=0;i<7;i++)
   {
	   RunData.ModbusData[e_ParaFirst+35+i] = MsgBuffer_Receive[i];
   }

   RD_EEPROM(14,0x40,0x2);
   RD_DATA_PROCESS(14);

   for(i=0;i<7;i++)
   {
	   RunData.ModbusData[e_ParaFirst+42+i] = MsgBuffer_Receive[i];
   }

   RD_EEPROM(14,0x30,0x4);
   RD_DATA_PROCESS(14);

   for(i=0;i<7;i++)
   {
	   RunData.ModbusData[e_ParaFirst+49+i] = MsgBuffer_Receive[i];
   }

   RD_EEPROM(14,0x40,0x4);
   RD_DATA_PROCESS(14);

   for(i=0;i<7;i++)
   {
	   RunData.ModbusData[e_ParaFirst+56+i] = MsgBuffer_Receive[i];
   }

   RD_EEPROM(14,0x50,0x4);
   RD_DATA_PROCESS(14);

   for(i=0;i<7;i++)
   {
       RunData.ModbusData[e_ParaFirst+63+i] = MsgBuffer_Receive[i];
   }

   RD_EEPROM(14,0x50,0x2);
   RD_DATA_PROCESS(14);

   for(i=0;i<7;i++)
   {
       RunData.ModbusData[e_ParaFirst+70+i] = MsgBuffer_Receive[i];
   }

   RD_EEPROM(14,0x10,0x1);
   RD_DATA_PROCESS(14);

   for(i=0;i<7;i++)
   {
       RunData.ModbusData[e_ParaFirst+77+i] = MsgBuffer_Receive[i];
   }


}

void  WRParam_EEprom()
{
   Uint16 i=0;



   for(i=0;i<7;i++)
   {
	   MsgBuffer_Send[i] = RunData.ModbusData[e_ParaFirst+i];
   }
   WR_DATA_PROCESS(7);
   WR_EEPROM(14,0x30,0x1);

   for(i=0;i<7;i++)
   {
	   MsgBuffer_Send[i] = RunData.ModbusData[e_ParaFirst+7+i];
   }
   WR_DATA_PROCESS(7);
   WR_EEPROM(14,0x00,0x4);

   for(i=0;i<7;i++)
   {
	   MsgBuffer_Send[i] = RunData.ModbusData[e_ParaFirst+14+i];
   }
   WR_DATA_PROCESS(7);
   WR_EEPROM(14,0x20,0x4);

   for(i=0;i<7;i++)
   {
	   MsgBuffer_Send[i] = RunData.ModbusData[e_ParaFirst+21+i];
   }
   WR_DATA_PROCESS(7);
   WR_EEPROM(14,0x10,0x2);

   for(i=0;i<7;i++)
   {
	   MsgBuffer_Send[i] = RunData.ModbusData[e_ParaFirst+28+i];
   }
   WR_DATA_PROCESS(7);
   WR_EEPROM(14,0x20,0x2);

   for(i=0;i<7;i++)
   {
	   MsgBuffer_Send[i] = RunData.ModbusData[e_ParaFirst+35+i];
   }
   WR_DATA_PROCESS(7);
   WR_EEPROM(14,0x30,0x2);

   for(i=0;i<7;i++)
   {
	   MsgBuffer_Send[i] = RunData.ModbusData[e_ParaFirst+42+i];
   }
   WR_DATA_PROCESS(7);
   WR_EEPROM(14,0x40,0x2);

   for(i=0;i<7;i++)
   {
	   MsgBuffer_Send[i] = RunData.ModbusData[e_ParaFirst+49+i];
   }
   WR_DATA_PROCESS(7);
   WR_EEPROM(14,0x30,0x4);

   for(i=0;i<7;i++)
   {
	   MsgBuffer_Send[i] = RunData.ModbusData[e_ParaFirst+56+i];
   }
   WR_DATA_PROCESS(7);
   WR_EEPROM(14,0x40,0x4);

   for(i=0;i<7;i++)
   {
       MsgBuffer_Send[i] = RunData.ModbusData[e_ParaFirst+63+i];
   }
   WR_DATA_PROCESS(7);
   WR_EEPROM(14,0x50,0x4);

   for(i=0;i<7;i++)
   {
       MsgBuffer_Send[i] = RunData.ModbusData[e_ParaFirst+70+i];
   }
   WR_DATA_PROCESS(7);
   WR_EEPROM(14,0x50,0x2);

   for(i=0;i<7;i++)
   {
       MsgBuffer_Send[i] = RunData.ModbusData[e_ParaFirst+77+i];
   }
   WR_DATA_PROCESS(7);
   WR_EEPROM(14,0x10,0x1);

}



