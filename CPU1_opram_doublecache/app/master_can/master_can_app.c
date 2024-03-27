/*
 * can_get_function.c
 *
//    //1-初始化can
//    CAN_initModule(uint32_t base);
//    //2-设置波特率
//    CAN_initModule(uint32_t base);
//    //3-手动设置波特率
//    CAN_setBitTiming(uint32_t base, uint16_t prescaler,
//                     uint16_t prescalerExtension, uint16_t tSeg1, uint16_t tSeg2,
//                     uint16_t sjw);
//    //4-清除中断
//    CAN_clearInterruptStatus(uint32_t base, uint32_t intClr);
//    //5-设置邮箱
//    CAN_setupMessageObject(uint32_t base, uint32_t objID, uint32_t msgID,
//                           CAN_MsgFrameType frame, CAN_MsgObjType msgType,
//                           uint32_t msgIDMask, uint32_t flags, uint16_t msgLen);
//    //6-发送消息
//    CAN_sendMessage(uint32_t base, uint32_t objID, uint16_t msgLen,
//                    const uint16_t *msgData);
//
//    //7-发送远程帧
//    CAN_sendRemoteRequestMessage(uint32_t base, uint32_t objID);
//    //8-读写邮箱RAM
//    CAN_transferMessage(uint32_t base, uint16_t interface, uint32_t objID,
//                        bool direction);
//    //9-关闭邮箱
//    CAN_clearMessage(uint32_t base, uint32_t objID);
//    //10-关闭所有邮箱
//    CAN_disableAllMessageObjects(uint32_t base);
 */

#include "master_can.h"
#include "master_can_app.h"
#include "master_can_imfor.h"
#include "Global_struct.h"

bool can_run_flag; //运行任务标志位
bool can_get_flag;

static void CanApp_Tx(uint8_t quantity, uint8_t id);
static void CanApp_Tx_RTR(uint8_t quantity, uint8_t id);
static void CanApp_Rx(uint8_t quantity);

/* 发送邮箱 发送数据
 * quantity 要发送的从机数目 1-5
 * */
static void CanApp_Tx(uint8_t quantity, uint8_t id)
{
    // uint8_t  i;
    uint16_t pdata[4];

    if (id < quantity * 3)
    {
        pdata[0] = CanScan.Tx_Buff[(id - TX_MBOX_BASE) * 4 + 0]; // CanScan.run_count;//
        pdata[1] = CanScan.Tx_Buff[(id - TX_MBOX_BASE) * 4 + 1]; // CanScan.run_timer;//
        pdata[2] = CanScan.Tx_Buff[(id - TX_MBOX_BASE) * 4 + 2];
        pdata[3] = CanScan.Tx_Buff[(id - TX_MBOX_BASE) * 4 + 3];
        // if (DataBit_Reead(CanScan.err_derive, id / 3) == 0)
        {
            can_send_OneFrameData(id, pdata);
        }
    }
}
/*发送远程帧*/
static void CanApp_Tx_RTR(uint8_t quantity, uint8_t id)
{
    uint16_t pdata[4];
    uint32_t count;
    if (id < quantity * 3)
    {
        id = RX_MBOX_BASE + id;
        /* 发送远程帧
         * ---------------------------------------------------------------- */
        // CAN_sendRemoteRequestMessage(CANA_BASE,MBOX8);
        CAN_sendMessage(CANA_BASE, id + 1, Byte_8, pdata);
        while (((HWREG_BP(CANA_BASE + CAN_O_ES) & CAN_ES_TXOK)) != CAN_ES_TXOK)
        {
            if (count++ > 0xE000)
            {
                //发送远程帧超时
                CanScan.err_box_id |= DataBit_Set(CanScan.err_box_id, id - RX_MBOX_BASE);
                count = 0;
                break;
            }
        }
    }
}
/* 所有接收邮箱 发送一次远程帧，并接收对应数据*/
static void CanApp_Rx(uint8_t quantity)
{
    uint8_t i;
    //    uint16_t pdata[4];
    /*  一个设备三个邮箱 quantity*3得到邮箱数量
     * 发送邮箱的起始地址为RX_MBOX_BASE
     * */
    quantity = quantity * 3 + RX_MBOX_BASE;
    for (i = RX_MBOX_BASE; i < quantity; i++)
    {
        can_receive_OneFrameData(i, &CanScan.Rx_Buff[(i - RX_MBOX_BASE) * 4 + 0]);
        //        CanScan.Rx_Buff[(i - RX_MBOX_BASE) * 4 + 0] = pdata[0]; // CanScan.run_count;//pdata[0];
        //        CanScan.Rx_Buff[(i - RX_MBOX_BASE) * 4 + 1] = pdata[1]; // CanScan.run_timer;//pdata[1];
        //        CanScan.Rx_Buff[(i - RX_MBOX_BASE) * 4 + 2] = pdata[2]; // 1000*CanScan.run_timer/CanScan.run_count;//pdata[2];
        //        CanScan.Rx_Buff[(i - RX_MBOX_BASE) * 4 + 3] = pdata[3];
    }
}

void CanApp_MainFunction(uint8_t quantity)
{
    /* step1: 刷新运行数据 */
    can_Tx_Buff_refresh(quantity);
    /* step2: 发送数据 */
    CanApp_Tx(quantity, CanScan.run_count);
}

void CanApp_RX_MainFunction(uint8_t quantity)
{
    CanApp_Rx(quantity);
    /* step4: 处理接收数据 */
    can_Rx_Buff_refresh(quantity);
}
void Can_Heart(uint8_t quantity)
{
    switch (quantity)
    {
    case 4:
    {
        if ((((RunData.ModbusData2[41] >> 15) & 0x0001) == 1))
        {
            CanScan.dly_com4++;
            CanScan.dly_com4_1 = 0;
            if (CanScan.dly_com4 > HEART_OUTTIME)
            {
                CanScan.dly_com4 = HEART_OUTTIME + 1;
                RunData.StateMachine.StatusReg0.bits.ComStatus4 = 1;
            }
            else
            {
                RunData.StateMachine.StatusReg0.bits.ComStatus4 = 0;
            }
        }
        else
        {
            CanScan.dly_com4_1++;
            CanScan.dly_com4 = 0;
            if (CanScan.dly_com4_1 > HEART_OUTTIME)
            {
                CanScan.dly_com4_1 = HEART_OUTTIME + 1;
                RunData.StateMachine.StatusReg0.bits.ComStatus4 = 1;
            }
            else
            {
                RunData.StateMachine.StatusReg0.bits.ComStatus4 = 0;
            }
        }
    }
    case 3:
    {
        if ((((RunData.ModbusData2[29] >> 15) & 0x0001) == 1))
        {
            CanScan.dly_com3++;
            CanScan.dly_com3_1 = 0;
            if (CanScan.dly_com3 > HEART_OUTTIME)
            {
                CanScan.dly_com3 = HEART_OUTTIME + 1;
                RunData.StateMachine.StatusReg0.bits.ComStatus3 = 1;
            }
            else
            {
                RunData.StateMachine.StatusReg0.bits.ComStatus3 = 0;
            }
        }
        else
        {
            CanScan.dly_com3_1++;
            CanScan.dly_com3 = 0;
            if (CanScan.dly_com3_1 > HEART_OUTTIME)
            {
                CanScan.dly_com3_1 = HEART_OUTTIME + 1;
                RunData.StateMachine.StatusReg0.bits.ComStatus3 = 1;
            }
            else
            {
                RunData.StateMachine.StatusReg0.bits.ComStatus3 = 0;
            }
        }
    }
    case 2:
    {
        if ((((RunData.ModbusData2[17] >> 15) & 0x0001) == 1))
        {
            CanScan.dly_com2++;
            CanScan.dly_com2_1 = 0;
            if (CanScan.dly_com2 > HEART_OUTTIME)
            {
                CanScan.dly_com2 = HEART_OUTTIME + 1;
                RunData.StateMachine.StatusReg0.bits.ComStatus2 = 1;
            }
            else
            {
                RunData.StateMachine.StatusReg0.bits.ComStatus2 = 0;
            }
        }
        else
        {
            CanScan.dly_com2_1++;
            CanScan.dly_com2 = 0;
            if (CanScan.dly_com2_1 > HEART_OUTTIME)
            {
                CanScan.dly_com2_1 = HEART_OUTTIME + 1;
                RunData.StateMachine.StatusReg0.bits.ComStatus2 = 1;
            }
            else
            {
                RunData.StateMachine.StatusReg0.bits.ComStatus2 = 0;
            }
        }
    }
    case 1:
    {
        if ((((RunData.ModbusData2[5] >> 15) & 0x0001) == 1))
        {
            CanScan.dly_com1++;
            CanScan.dly_com1_1 = 0;
            if (CanScan.dly_com1 > HEART_OUTTIME)
            {
                CanScan.dly_com1 = HEART_OUTTIME + 1;
                RunData.StateMachine.StatusReg0.bits.ComStatus1 = 1;
            }
            else
            {
                RunData.StateMachine.StatusReg0.bits.ComStatus1 = 0;
            }
        }
        else
        {
            CanScan.dly_com1_1++;
            CanScan.dly_com1 = 0;
            if (CanScan.dly_com1_1 > HEART_OUTTIME)
            {
                CanScan.dly_com1_1 = HEART_OUTTIME + 1;
                RunData.StateMachine.StatusReg0.bits.ComStatus1 = 1;
            }
            else
            {
                RunData.StateMachine.StatusReg0.bits.ComStatus1 = 0;
            }
        }
    }
    default:
        break;
    }
}

/*  led初始化
 *  led30-gpio94
 *  led31-gpio99
 * */
void led_init(void)
{
    GPIO_setPinConfig(GPIO_94_GPIO94);
    GPIO_setDirectionMode(94, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(94, GPIO_PIN_TYPE_STD);
    GPIO_setMasterCore(94, GPIO_CORE_CPU1);
    GPIO_setQualificationMode(94, GPIO_QUAL_SYNC);

    GPIO_setPinConfig(GPIO_99_GPIO99);
    GPIO_setDirectionMode(99, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(99, GPIO_PIN_TYPE_STD);
    GPIO_setMasterCore(99, GPIO_CORE_CPU1);
    GPIO_setQualificationMode(99, GPIO_QUAL_SYNC);
}
void led_30_ctrl(uint8_t led)
{
    GPIO_writePin(94, led);
}
void led_31_ctrl(uint8_t led)
{
    GPIO_writePin(99, led);
}
/*  下面是刚开始测试用的*/
#if 0
uint16_t txMsgData[8];
uint16_t rxMsgData[8];
uint16_t can_send_data[4];


uint16_t can_run_data[20];
uint16_t can_set_data[20];


/*  主机查询从机数据测试
 *  发送一个远程帧
 *  对应id接收数据
 *  将接收数据使用其他邮箱发送出去
 *
*/
uint8_t test_remote_rec(uint8_t box)
{
    uint16_t count = 0 ;
    if( box > 22 || box < 16 )
    {
        return 1;
    }

    CAN_sendMessage(CANA_BASE, MBOX0 + box, Byte_8, rxMsgData);//发送远程帧
    while(((HWREG_BP(CANA_BASE + CAN_O_ES) & CAN_ES_TXOK)) != CAN_ES_TXOK)
    {}
    // Poll RxOk bit in CAN_ES register to check completion of reception
    //
    while(((HWREG_BP(CANA_BASE + CAN_O_ES) & CAN_ES_RXOK)) != CAN_ES_RXOK)
    {
        count++;
        if(count>0xffff)
            break;
    }

    CAN_readMessage(CANA_BASE, MBOX0 + box, rxMsgData);//接收数据
    can_run_data[(box-10)*4+0] = ( rxMsgData[0]<<8 ) + rxMsgData[1];
    can_run_data[(box-10)*4+1] = ( rxMsgData[2]<<8 ) + rxMsgData[3];
    can_run_data[(box-10)*4+2] = ( rxMsgData[4]<<8 ) + rxMsgData[5];
    can_run_data[(box-10)*4+3] = ( rxMsgData[6]<<8 ) + rxMsgData[7];
    return 0;
    //CAN_sendMessage(CANA_BASE, MBOX0 + box_n - 10, Byte_8, rxMsgData);//将接收的数据使用其他邮箱发送
}
/*普通方式接收测试*/
void test_simple_rec(void)
{
    if(((HWREGH(CANA_BASE + CAN_O_ES) & CAN_ES_RXOK)) == CAN_ES_RXOK)
    {
        //
        // Get the received message
        //
        CAN_readMessage(CANA_BASE, MBOX8, rxMsgData);

        if(rxMsgData[0] == 0XAA)
        {
            GPIO_togglePin(99);
        }
        rxMsgData[0]=0;
        rxMsgData[1]=0;
        CAN_readMessage(CANA_BASE, MBOX9, rxMsgData);
        if(rxMsgData[1] == 0XBB)
        {
            GPIO_togglePin(94);
        }
        rxMsgData[0]=0;
        rxMsgData[1]=0;
        //CAN_sendMessage(CANB_BASE, MBOX7, Byte_8, rxMsgData);
    }
}
/*  test_simple_send    can普通发送模式
 *  box                 要发送的邮箱 MBOX0~MBOX4
 *  device_n            设备ID 0~4
 * */
uint8_t  test_simple_send(uint8_t box , uint8_t device_n)
{
    uint8_t j;
    uint16_t msgData[8];

    /* 邮箱0~4 为普通发送邮箱*/
    if( box < MBOX0 || box > MBOX5)
    return 0;
    refresh_can_set_data(1 );
    /*  将485接收数据(16位) 写入发送缓存(8位)*/
    for( j = 0 ; j < 8 ; j++ )
    {
        if( (j%2) == 0 )
        {
            msgData[j] = can_set_data[ (j/2) + (device_n*4) ] >> 8;
        }
        else
        {
            msgData[j] = can_set_data[ (j/2) + (device_n*4) ] & 0xff;
        }
    }
    /* CAN 发送数据 */
    CAN_sendMessage(CANA_BASE, box, 8, msgData);
    /* 等待发送完成 */
    while(((HWREGH(CANA_BASE + CAN_O_ES) & CAN_ES_TXOK)) !=  CAN_ES_TXOK)
    {
    }
    return 1;
}
uint8_t refresh_can_set_data(uint8_t device_n)
{
    uint8_t j;
    if(device_n > 5)
        return 0;
    for( j = 0 ; j < 8 ; j++ )
    {
        if( (j%2) == 0 )
        {
            txMsgData[j] = can_set_data[ (j/2) + (device_n*4) ] >> 8;
        }
        else
        {
            txMsgData[j] = can_set_data[ (j/2) + (device_n*4) ] & 0xff;
        }
    }
    return 1;
}

#endif // 0
