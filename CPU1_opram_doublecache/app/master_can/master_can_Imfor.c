#include "master_can_imfor.h"
#include "master_can_app.h"
#include "master_can.h"
#include "Global_struct.h"




/*--------------------------------------------------------------------*/
static uint8_t  can_Tx_Buff_write(uint8_t ID, uint16_t value);
/*--------------------------------------------------------------------
 *  向can_Tx_Buff数组中写入数据
 *  ID    数组下标
 *  value 写入的16bit数据
 *  return 1 下标超范围
 *  return 0 正常写入
 * */
/*--------------------------------------------------------------------*/
static uint8_t  can_Tx_Buff_write(uint8_t ID, uint16_t value)
{
    if(ID >= TX_BUFF_MAXNUM)
    {
        //如果写入的状态量ID超范围，直接返回
        return 1;
    }
    CanScan.Tx_Buff[ID] = value;
    return 0;
}
/*--------------------------------------------------------------------
 *  更新发给从机所有设备的数据CanScan.Tx_Buff,需要在 CanApp_MainFunction 中使用
 *  quantity 从机数量 1~5
 * */
void   can_Tx_Buff_refresh(uint8_t quantity)
{
    switch(quantity)
    {
//        case 5:
        case 4:{
            /*设备4-----------------------------------------------*/
//            //MSGID 0x29
//            can_Tx_Buff_write(36,0x2933);//Word3
//            can_Tx_Buff_write(37,0x2922);//Word2
//            can_Tx_Buff_write(38,0x2911);//Word1
//            can_Tx_Buff_write(39,0x2900);//Word0
//            //MSGID 0x2A
//            can_Tx_Buff_write(40,0x2A33);//Word3
//            can_Tx_Buff_write(41,0x2A22);//Word2
//            can_Tx_Buff_write(42,can_run_flag);//Word1
//            can_Tx_Buff_write(43,can_run_flag);//Word0
//            //MSGID 0x2B
//            can_Tx_Buff_write(44,0x2B33);//Word3
//            can_Tx_Buff_write(45,0x2B22);//Word2
//            can_Tx_Buff_write(46,0x2B33);//Word1
//            can_Tx_Buff_write(47,0x2B44);//Word0
            /*设备1-----------------------------------------------*/
                //MSGID 0x20
              can_Tx_Buff_write(36,RunData.ModbusData2[86]);//CanScan.Tx_Buff[0]);//Word3
              can_Tx_Buff_write(37,RunData.ModbusData2[87]);//CanScan.Tx_Buff[1]);//Word2
              can_Tx_Buff_write(38,RunData.ModbusData2[88]);//CanScan.Tx_Buff[2]);//Word1
              can_Tx_Buff_write(39,RunData.ModbusData2[89]);//CanScan.Tx_Buff[3]);//Word0
              //MSGID 0x21
              can_Tx_Buff_write(40,RunData.ModbusData2[90]);//CanScan.Tx_Buff[4]);//Word3
              can_Tx_Buff_write(41,RunData.ModbusData2[91]);//CanScan.Tx_Buff[5]);//Word2
              can_Tx_Buff_write(42,RunData.ModbusData2[92]);//CanScan.Tx_Buff[6]);//Word1
              can_Tx_Buff_write(43,RunData.ModbusData2[93]);//CanScan.Tx_Buff[7]);//Word0
              //MSGID 0x22
              can_Tx_Buff_write(44,RunData.ModbusData2[94]);//CanScan.Tx_Buff[8]);//Word3
              can_Tx_Buff_write(45,RunData.ModbusData2[95]);//CanScan.Tx_Buff[9]);//Word2
              can_Tx_Buff_write(46,RunData.ModbusData2[96]);//CanScan.Tx_Buff[10]);//Word1
              can_Tx_Buff_write(47,RunData.ModbusData2[97]);//CanScan.Tx_Buff[11]);//Word0
        }
        case 3:{
            /*设备3-----------------------------------------------*/
//            //MSGID 0x26
//            can_Tx_Buff_write(24,0x2633);//Word3
//            can_Tx_Buff_write(25,0x2622);//Word2
//            can_Tx_Buff_write(26,0x2611);//Word1
//            can_Tx_Buff_write(27,0x2600);//Word0
//            //MSGID 0x27
//            can_Tx_Buff_write(28,0x2733);//Word3
//            can_Tx_Buff_write(29,0x2722);//Word2
//            can_Tx_Buff_write(30,can_run_flag);//Word1
//            can_Tx_Buff_write(31,can_run_flag);//Word0
//            //MSGID 0x28
//            can_Tx_Buff_write(32,0x2833);//Word3
//            can_Tx_Buff_write(33,0x2822);//Word2
//            can_Tx_Buff_write(34,0x2833);//Word1
//            can_Tx_Buff_write(35,0x2844);//Word0
            /*设备1-----------------------------------------------*/
                //MSGID 0x20
              can_Tx_Buff_write(24,RunData.ModbusData2[74]);//CanScan.Tx_Buff[0]);//Word3
              can_Tx_Buff_write(25,RunData.ModbusData2[75]);//CanScan.Tx_Buff[1]);//Word2
              can_Tx_Buff_write(26,RunData.ModbusData2[76]);//CanScan.Tx_Buff[2]);//Word1
              can_Tx_Buff_write(27,RunData.ModbusData2[77]);//CanScan.Tx_Buff[3]);//Word0
              //MSGID 0x21
              can_Tx_Buff_write(28,RunData.ModbusData2[78]);//CanScan.Tx_Buff[4]);//Word3
              can_Tx_Buff_write(29,RunData.ModbusData2[79]);//CanScan.Tx_Buff[5]);//Word2
              can_Tx_Buff_write(30,RunData.ModbusData2[80]);//CanScan.Tx_Buff[6]);//Word1
              can_Tx_Buff_write(31,RunData.ModbusData2[81]);//CanScan.Tx_Buff[7]);//Word0
              //MSGID 0x22
              can_Tx_Buff_write(32,RunData.ModbusData2[82]);//CanScan.Tx_Buff[8]);//Word3
              can_Tx_Buff_write(33,RunData.ModbusData2[83]);//CanScan.Tx_Buff[9]);//Word2
              can_Tx_Buff_write(34,RunData.ModbusData2[84]);//CanScan.Tx_Buff[10]);//Word1
              can_Tx_Buff_write(35,RunData.ModbusData2[85]);//CanScan.Tx_Buff[11]);//Word0
        }
        case 2:{
#if 0
            /*设备2-----------------------------------------------*/
            //MSGID 0x23
            can_Tx_Buff_write(12,RunData.ModbusData[23]);//CanScan.Tx_Buff[12]);//Word3
            can_Tx_Buff_write(13,RunData.ModbusData[28]);//CanScan.Tx_Buff[13]);//Word2
            can_Tx_Buff_write(14,RunData.ModbusData[33]);//CanScan.Tx_Buff[14]);//Word1
            can_Tx_Buff_write(15,RunData.ModbusData[38]);//CanScan.Tx_Buff[15]);//Word0
            //MSGID 0x24
            can_Tx_Buff_write(16,RunData.ModbusData[24]);//CanScan.Tx_Buff[16]);//Word3
            can_Tx_Buff_write(17,RunData.ModbusData[29]);//CanScan.Tx_Buff[17]);//Word2
            can_Tx_Buff_write(18,RunData.ModbusData[34]);//CanScan.Tx_Buff[18]);//Word1
            can_Tx_Buff_write(19,RunData.ModbusData[39]);//CanScan.Tx_Buff[19]);//Word0
            //MSGID 0x25
            can_Tx_Buff_write(20,0x2511);//Word3
            can_Tx_Buff_write(21,0x2522);//Word2
            can_Tx_Buff_write(22,0x2533);//Word1
            can_Tx_Buff_write(23,0x2544);//Word0
#else
            /*设备1-----------------------------------------------*/
                //MSGID 0x20
              can_Tx_Buff_write(12,RunData.ModbusData2[62]);//CanScan.Tx_Buff[0]);//Word3
              can_Tx_Buff_write(13,RunData.ModbusData2[63]);//CanScan.Tx_Buff[1]);//Word2
              can_Tx_Buff_write(14,RunData.ModbusData2[64]);//CanScan.Tx_Buff[2]);//Word1
              can_Tx_Buff_write(15,RunData.ModbusData2[65]);//CanScan.Tx_Buff[3]);//Word0
              //MSGID 0x21
              can_Tx_Buff_write(16,RunData.ModbusData2[66]);//CanScan.Tx_Buff[4]);//Word3
              can_Tx_Buff_write(17,RunData.ModbusData2[67]);//CanScan.Tx_Buff[5]);//Word2
              can_Tx_Buff_write(18,RunData.ModbusData2[68]);//CanScan.Tx_Buff[6]);//Word1
              can_Tx_Buff_write(19,RunData.ModbusData2[69]);//CanScan.Tx_Buff[7]);//Word0
              //MSGID 0x22
              can_Tx_Buff_write(20,RunData.ModbusData2[70]);//CanScan.Tx_Buff[8]);//Word3
              can_Tx_Buff_write(21,RunData.ModbusData2[71]);//CanScan.Tx_Buff[9]);//Word2
              can_Tx_Buff_write(22,RunData.ModbusData2[72]);//CanScan.Tx_Buff[10]);//Word1
              can_Tx_Buff_write(23,RunData.ModbusData2[73]);//CanScan.Tx_Buff[11]);//Word0
#endif
        }
        case 1:{
#if 0
          /*设备1-----------------------------------------------*/
              //MSGID 0x20
            can_Tx_Buff_write(0,RunData.ModbusData[20]);//CanScan.Tx_Buff[0]);//Word3
            can_Tx_Buff_write(1,RunData.ModbusData[25]);//CanScan.Tx_Buff[1]);//Word2
            can_Tx_Buff_write(2,RunData.ModbusData[30]);//CanScan.Tx_Buff[2]);//Word1
            can_Tx_Buff_write(3,RunData.ModbusData[35]);//CanScan.Tx_Buff[3]);//Word0
            //MSGID 0x21
            can_Tx_Buff_write(4,RunData.ModbusData[21]);//CanScan.Tx_Buff[4]);//Word3
            can_Tx_Buff_write(5,RunData.ModbusData[26]);//CanScan.Tx_Buff[5]);//Word2
            can_Tx_Buff_write(6,RunData.ModbusData[31]);//CanScan.Tx_Buff[6]);//Word1
            can_Tx_Buff_write(7,RunData.ModbusData[36]);//CanScan.Tx_Buff[7]);//Word0
            //MSGID 0x22
            can_Tx_Buff_write(8,RunData.ModbusData[22]);//CanScan.Tx_Buff[8]);//Word3
            can_Tx_Buff_write(9,RunData.ModbusData[27]);//CanScan.Tx_Buff[9]);//Word2
            can_Tx_Buff_write(10,RunData.ModbusData[32]);//CanScan.Tx_Buff[10]);//Word1
            can_Tx_Buff_write(11,RunData.ModbusData[37]);//CanScan.Tx_Buff[11]);//Word0
#else
            /*设备1-----------------------------------------------*/
                //MSGID 0x20
            //  RunData.ModbusData2[50] = 1;
              can_Tx_Buff_write(0,RunData.ModbusData2[50]);//CanScan.Tx_Buff[0]);//Word3
              can_Tx_Buff_write(1,RunData.ModbusData2[51]);//CanScan.Tx_Buff[1]);//Word2
              can_Tx_Buff_write(2,RunData.ModbusData2[52]);//CanScan.Tx_Buff[2]);//Word1
              can_Tx_Buff_write(3,RunData.ModbusData2[53]);//CanScan.Tx_Buff[3]);//Word0
              //MSGID 0x21
              can_Tx_Buff_write(4,RunData.ModbusData2[54]);//CanScan.Tx_Buff[4]);//Word3
              can_Tx_Buff_write(5,RunData.ModbusData2[55]);//CanScan.Tx_Buff[5]);//Word2
              can_Tx_Buff_write(6,RunData.ModbusData2[56]);//CanScan.Tx_Buff[6]);//Word1
              can_Tx_Buff_write(7,RunData.ModbusData2[57]);//CanScan.Tx_Buff[7]);//Word0
              //MSGID 0x22
              can_Tx_Buff_write(8,RunData.ModbusData2[58]);//CanScan.Tx_Buff[5]);//Word3
              can_Tx_Buff_write(9,RunData.ModbusData2[59]);//CanScan.Tx_Buff[9]);//Word2
              can_Tx_Buff_write(10,RunData.ModbusData2[60]);//CanScan.Tx_Buff[10]);//Word1
              can_Tx_Buff_write(11,RunData.ModbusData2[61]);//CanScan.Tx_Buff[11]);//Word0
#endif
        }
        default:
            break;
    }

}


/*--------------------------------------------------------------------
 * 读取Tx_Buff数组中的数据
 * ID:数组下标
 * return 0 数组下标超范围
 * */
static uint16_t  can_Rx_Buff_read(uint8_t ID )
{
    if(ID >= RX_BUFF_MAXNUM)
    {
        //如果写入的状态量ID超范围，直接返回
        return 0;
    }
    return CanScan.Rx_Buff[ID];
}
/*--------------------------------------------------------------------
 *  更新接收到的从机数据CanScan.Rx_Buff,需要在 CanApp_MainFunction 中使用
 *  quantity 从机数量 1~5
 * */
void   can_Rx_Buff_refresh(uint8_t quantity)
{
    switch(quantity)
    {
//        case 5:
        case 4:
        {
            //MSGID 0x13
             RunData.ModbusData2[36] = can_Rx_Buff_read(36);//Word3
             RunData.ModbusData2[37] = can_Rx_Buff_read(37);//Word2
             RunData.ModbusData2[38] = can_Rx_Buff_read(38);//CanScan.Tx_Buff[14]);//Word1
             RunData.ModbusData2[39] = can_Rx_Buff_read(39);//CanScan.Tx_Buff[15]);//Word0
             //MSGID 0x14
             RunData.ModbusData2[40] = can_Rx_Buff_read(40);//CanScan.Tx_Buff[16]);//Word3
             RunData.ModbusData2[41] = can_Rx_Buff_read(41);//CanScan.Tx_Buff[17]);//Word2
             RunData.ModbusData2[42] = can_Rx_Buff_read(42);//CanScan.Tx_Buff[18]);//Word1
             RunData.ModbusData2[43] = can_Rx_Buff_read(43);//CanScan.Tx_Buff[19]);//Word0
             //MSGID 0x15
             RunData.ModbusData2[44] = can_Rx_Buff_read(44);//Word3
             RunData.ModbusData2[45] = can_Rx_Buff_read(45);//Word2
             RunData.ModbusData2[46] = can_Rx_Buff_read(46);//Word1
             RunData.ModbusData2[47] = can_Rx_Buff_read(47);//Word0
        }
        case 3:{
            //MSGID 0x13
            RunData.ModbusData2[24] = can_Rx_Buff_read(24);//Word3
            RunData.ModbusData2[25] = can_Rx_Buff_read(25);//Word2
            RunData.ModbusData2[26] = can_Rx_Buff_read(26);//CanScan.Tx_Buff[14]);//Word1
            RunData.ModbusData2[27] = can_Rx_Buff_read(27);//CanScan.Tx_Buff[15]);//Word0
            //MSGID 0x14
            RunData.ModbusData2[28] = can_Rx_Buff_read(28);//CanScan.Tx_Buff[16]);//Word3
            RunData.ModbusData2[29] = can_Rx_Buff_read(29);//CanScan.Tx_Buff[17]);//Word2
            RunData.ModbusData2[30] = can_Rx_Buff_read(30);//CanScan.Tx_Buff[18]);//Word1
            RunData.ModbusData2[31] = can_Rx_Buff_read(31);//CanScan.Tx_Buff[19]);//Word0
            //MSGID 0x15
            RunData.ModbusData2[32] = can_Rx_Buff_read(32);//Word3
            RunData.ModbusData2[33] = can_Rx_Buff_read(33);//Word2
            RunData.ModbusData2[34] = can_Rx_Buff_read(34);//Word1
            RunData.ModbusData2[35] = can_Rx_Buff_read(35);//Word0
        }
        case 2:{

            //MSGID 0x13
            RunData.ModbusData2[12] = can_Rx_Buff_read(12);//Word3
            RunData.ModbusData2[13] = can_Rx_Buff_read(13);//Word2
            RunData.ModbusData2[14] = can_Rx_Buff_read(14);//CanScan.Tx_Buff[14]);//Word1
            RunData.ModbusData2[15] = can_Rx_Buff_read(15);//CanScan.Tx_Buff[15]);//Word0
            //MSGID 0x14
            RunData.ModbusData2[16] = can_Rx_Buff_read(16);//CanScan.Tx_Buff[16]);//Word3
            RunData.ModbusData2[17] = can_Rx_Buff_read(17);//CanScan.Tx_Buff[17]);//Word2
            RunData.ModbusData2[18] = can_Rx_Buff_read(18);//CanScan.Tx_Buff[18]);//Word1
            RunData.ModbusData2[19] = can_Rx_Buff_read(19);//CanScan.Tx_Buff[19]);//Word0
            //MSGID 0x15
            RunData.ModbusData2[20] = can_Rx_Buff_read(20);//Word3
            RunData.ModbusData2[21] = can_Rx_Buff_read(21);//Word2
            RunData.ModbusData2[22] = can_Rx_Buff_read(22);//Word1
            RunData.ModbusData2[23] = can_Rx_Buff_read(23);//Word0

        }
        case 1:{

            //MSGID 0x10
            RunData.ModbusData2[0] = can_Rx_Buff_read(0);//Word3   Iarms
            RunData.ModbusData2[1] = can_Rx_Buff_read(1);//Word2 Ibrms
            RunData.ModbusData2[2] = can_Rx_Buff_read(2);//Word1  Icrms
            RunData.ModbusData2[3] = can_Rx_Buff_read(3);//Word0  Udc
            //MSGID 0x11
            RunData.ModbusData2[4] = can_Rx_Buff_read(4);//Word3  TEMP
            RunData.ModbusData2[5] = can_Rx_Buff_read(5);//Word2
            RunData.ModbusData2[6] = can_Rx_Buff_read(6);//Word1
            RunData.ModbusData2[7] = can_Rx_Buff_read(7);////Word0
            //MSGID 0x12
            RunData.ModbusData2[8] = can_Rx_Buff_read(8);//Word3
            RunData.ModbusData2[9] = can_Rx_Buff_read(9);//Word2
            RunData.ModbusData2[10] = can_Rx_Buff_read(10);//Word1
            RunData.ModbusData2[11] = can_Rx_Buff_read(11);//Word0

        }
        default:
            break;
    }

}

