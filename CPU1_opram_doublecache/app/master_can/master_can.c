//#############################################################################
#include "master_can.h"
#include "Global_struct.h"
#include "State_Machine.h"
CAN_SCAN CanScan;
CANB_SCAN CanBScan;
static void canA_init(uint8_t BitRate);
static uint8_t can_mbox_set(uint16_t tx_ID,uint16_t rx_ID);
static void CanB_init(uint8_t BitRate);
static uint8_t CanB_mbox_set(void);

void CanA_reset(void)
{
    if(RunData.StateMachine.StatusReg0.bits.ComStatus4||RunData.StateMachine.StatusReg0.bits.ComStatus3||RunData.StateMachine.StatusReg0.bits.ComStatus2||RunData.StateMachine.StatusReg0.bits.ComStatus1)
    {
        CAN_disableAllMessageObjects(CANA_BASE);
        canA_init(500);
        can_mbox_set(0x20,0x10);
    }

}

void CanABasic_init(void)
{
    canA_init(500);
    can_mbox_set(0x20,0x10);
    CanScan.run_flag = 0;
    CanScan.run_timer = 0;
}
static void canA_init(uint8_t BitRate)
{
    //
    // Initialize GPIO and configure GPIO pins for CANTX/CANRX
    // on module A
    //
    GPIO_setPinConfig(GPIO_18_CANRXA);
    GPIO_setPinConfig(GPIO_19_CANTXA);
    //
    // Initialize the CAN controllers
    //
    CAN_initModule(CANA_BASE);
    //
    // Set up the CAN bus bit rate to 500kHz for each module
    // Refer to the Driver Library User Guide for information on how to set
    // tighter timing control. Additionally, consult the device data sheet
    // for more information about the CAN module clocking.
    if(BitRate == 500)
    {
        // 500k
        CAN_setBitRate(CANA_BASE, DEVICE_SYSCLK_FREQ, 500000, 16);
    }
    else if (BitRate == 1000)
    {
        // 1M
        CAN_setBitRate(CANA_BASE, DEVICE_SYSCLK_FREQ, 1000000, 8);
    }
    else if (BitRate == 250)
    {
        // 250
        CAN_setBitRate(CANA_BASE, DEVICE_SYSCLK_FREQ, 250000, 32);
    }

}
static uint8_t can_mbox_set(uint16_t tx_ID,uint16_t rx_ID)
{
    if( (tx_ID+TX_MBOX_MAX > 0x7FF) || (rx_ID+RX_MBOX_MAX > 0x7FF) )
    {
        return Error_1;//邮箱ID超范围
    }
    //邮箱0-4 初始化为普通发送邮箱
    CAN_setupMessageObject(CANA_BASE, MBOX0, tx_ID,
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_TX, 0,
                           CAN_MSG_OBJ_NO_FLAGS, Byte_8);
    CAN_setupMessageObject(CANA_BASE, MBOX1, tx_ID+1,
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_TX, 0,
                           CAN_MSG_OBJ_NO_FLAGS, Byte_8);
    CAN_setupMessageObject(CANA_BASE, MBOX2, tx_ID+2,
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_TX, 0,
                           CAN_MSG_OBJ_NO_FLAGS, Byte_8);
    /*--设备2-----------------------------------------------------------------*/
    CAN_setupMessageObject(CANA_BASE, MBOX3, tx_ID+3,
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_TX, 0,
                           CAN_MSG_OBJ_NO_FLAGS, Byte_8);
    CAN_setupMessageObject(CANA_BASE, MBOX4, tx_ID+4,
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_TX, 0,
                           CAN_MSG_OBJ_NO_FLAGS, Byte_8);
    CAN_setupMessageObject(CANA_BASE, MBOX5, tx_ID+5,
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_TX, 0,
                           CAN_MSG_OBJ_NO_FLAGS, Byte_8);
    /*--设备3-----------------------------------------------------------------*/
    CAN_setupMessageObject(CANA_BASE, MBOX6, tx_ID+6,
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_TX, 0,
                           CAN_MSG_OBJ_NO_FLAGS, Byte_8);
    CAN_setupMessageObject(CANA_BASE, MBOX7, tx_ID+7,
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_TX, 0,
                           CAN_MSG_OBJ_NO_FLAGS, Byte_8);
    CAN_setupMessageObject(CANA_BASE, MBOX8, tx_ID+8,
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_TX, 0,
                           CAN_MSG_OBJ_NO_FLAGS, Byte_8);
    /*--设备4-----------------------------------------------------------------*/
    CAN_setupMessageObject(CANA_BASE, MBOX9, tx_ID+9,
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_TX, 0,
                           CAN_MSG_OBJ_NO_FLAGS, Byte_8);
    CAN_setupMessageObject(CANA_BASE, MBOX10, tx_ID+10,
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_TX, 0,
                           CAN_MSG_OBJ_NO_FLAGS, Byte_8);
    CAN_setupMessageObject(CANA_BASE, MBOX11, tx_ID+11,
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_TX, 0,
                           CAN_MSG_OBJ_NO_FLAGS, Byte_8);

    // 邮箱8 邮箱9 初始化为普通接收邮箱
    // Initialize the receive message object used for receiving CAN messages.
    // Message Object Parameters:
    //      CAN Module: A
    //      Message Object ID Number: 1
    //      Message Identifier: 0x1
    //      Message Frame: Standard
    //      Message Type: Receive
    //      Message ID Mask: 0x0
    //      Message Object Flags: None
    //      Message Data Length: "Don't care" for a Receive mailbox
    //
//    CAN_setupMessageObject(CANA_BASE, MBOX8, 0x08,
//                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RX, 0,
//                           CAN_MSG_OBJ_NO_FLAGS, Byte_0);
//    CAN_setupMessageObject(CANA_BASE, MBOX9, 0x09,
//                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RX, 0,
//                           CAN_MSG_OBJ_NO_FLAGS, Byte_0);
    // 初始化远程帧邮箱
    // Initialize the mailbox used for sending the remote frame
    // - and receiving the corresponding data frame
    // Message Object Parameters:
    //      CAN Module: A
    //      Message Object ID Number: 1
    //      Message Identifier: 0x111
    //      Message Frame: Standard
    //      Message Type: Receive (but transmits a Remote frame first)
    //      Message ID Mask: 0x0
    //      Message Object Flags: None
    //      Message Data Length: 8 Bytes
    //
    CAN_setupMessageObject(CANA_BASE, MBOX16, rx_ID,
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RX, 0,
                           CAN_MSG_OBJ_NO_FLAGS, Byte_8);
    CAN_setupMessageObject(CANA_BASE, MBOX17, rx_ID+1,
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RX, 0,
                           CAN_MSG_OBJ_NO_FLAGS, Byte_8);
    CAN_setupMessageObject(CANA_BASE, MBOX18, rx_ID+2,
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RX, 0,
                           CAN_MSG_OBJ_NO_FLAGS, Byte_8);
    /*--设备2-----------------------------------------------------------------*/
    CAN_setupMessageObject(CANA_BASE, MBOX19, rx_ID+3,
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RX, 0,
                           CAN_MSG_OBJ_NO_FLAGS, Byte_8);
    CAN_setupMessageObject(CANA_BASE, MBOX20, rx_ID+4,
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RX, 0,
                           CAN_MSG_OBJ_NO_FLAGS, Byte_8);
    CAN_setupMessageObject(CANA_BASE, MBOX21, rx_ID+5,
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RX, 0,
                           CAN_MSG_OBJ_NO_FLAGS, Byte_8);
    /*--设备3-----------------------------------------------------------------*/
    CAN_setupMessageObject(CANA_BASE, MBOX22, rx_ID+6,
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RX, 0,
                           CAN_MSG_OBJ_NO_FLAGS, Byte_8);
    CAN_setupMessageObject(CANA_BASE, MBOX23, rx_ID+7,
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RX, 0,
                           CAN_MSG_OBJ_NO_FLAGS, Byte_8);
    CAN_setupMessageObject(CANA_BASE, MBOX24, rx_ID+8,
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RX, 0,
                           CAN_MSG_OBJ_NO_FLAGS, Byte_8);
    /*--设备4-----------------------------------------------------------------*/
    CAN_setupMessageObject(CANA_BASE, MBOX25, rx_ID+9,
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RX, 0,
                           CAN_MSG_OBJ_NO_FLAGS, Byte_8);
    CAN_setupMessageObject(CANA_BASE, MBOX26, rx_ID+10,
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RX, 0,
                           CAN_MSG_OBJ_NO_FLAGS, Byte_8);
    CAN_setupMessageObject(CANA_BASE, MBOX27, rx_ID+11,
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RX, 0,
                           CAN_MSG_OBJ_NO_FLAGS, Byte_8);

    //
    // Start CAN module A operations
    //
    CAN_startModule(CANA_BASE);
    return Success;
}


/*  can_send_OneFrameData   发送一帧数据
 *  id:     选择写入邮箱 id对应 MBOX
 *  pdata:  要写入的数据
 *  return:
 * */
uint8_t can_send_OneFrameData(uint8_t id, const uint16_t *pdata)
{
    uint16_t msgData[8];
    uint16_t count = 0;
    uint8_t j;
    if( id>TX_MBOX_MAX )
        return Error_1;
    if(DataBit_Reead(CanScan.err_box_id,id-TX_MBOX_BASE)==1)
    {
        //return Error_2;
    }
    //把4个16位数拆分为8个8位数
    for( j = 0 ; j < 8 ; j++ )
    {
        if( (j%2) == 0 )
        {
            msgData[j] = pdata[j/2] >> 8;
        }
        else
        {
            msgData[j] = pdata[j/2] & 0xff;
        }
    }
    /* CAN 发送数据,035邮箱从0开始，377从1开始，所有邮箱+1 */
    CAN_sendMessage(CANA_BASE, id+1, Byte_8, msgData);
    /* 等待发送完成 */
    while(((HWREGH(CANA_BASE + CAN_O_ES) & CAN_ES_TXOK)) !=  CAN_ES_TXOK)
    {
        /*8字节标准帧为108bit,1M速率发送需要108us,500K速率发送需要216us
         * 200M主频，T=1/200M=0.005us 计数到216us需要86400
         * */
        if(count++ > 0xE000)
        {
            //发送超时
            CanScan.err_box_id |= DataBit_Set(CanScan.err_box_id,id-TX_MBOX_BASE);
            count = 0;
            return Error_3;
            break;
        }
    }
    /* 帧间隔3bit 主频200M 速率1M
     * ---------------------------------------------------------------- */
//    for(count = 0;count<600;count++)
//    {}


    return Success;
}
uint8_t can_receive_OneFrameData(uint8_t id,uint16_t *pbuff)
{

    uint16_t msgData[8];
    uint32_t count = 0;
    uint32_t msgid = 0;
    uint32_t box_msk = 0;
    /* 检查邮箱合法性
     * MBOX16-MBOX21  17-22
     * ---------------------------------------------------------------- */
 /*   if( id > RX_MBOX_MAX || id < RX_MBOX_BASE )
    {
        return Error_1;
    }
    if(DataBit_Reead(CanScan.err_box_id,id-RX_MBOX_BASE)==1)
    {
        return Error_2;
    }*/
    // /* 发送远程帧
    //  * ---------------------------------------------------------------- */
    // CAN_sendMessage(CANA_BASE, id+1, Byte_8, msgData);
    // /* 发送远程帧是否成功
    //  * ---------------------------------------------------------------- */
    // while(((HWREG_BP(CANA_BASE + CAN_O_ES) & CAN_ES_TXOK)) != CAN_ES_TXOK)
    // {
    //     if(count++ > 0xE000)
    //     {
    //         //发送远程帧超时
    //         CanScan.err_box_id |= DataBit_Set(CanScan.err_box_id,id-RX_MBOX_BASE);
    //         count = 0;
    //         return Error_3;
    //         break;
    //     }
    // }
    /* 帧间隔3bit 主频200M 速率1M
     * ---------------------------------------------------------------- */
//    for(count = 0;count<600;count++)
//    {}
    /* 检查接收是否成功
     * Poll RxOk bit in CAN_ES register to check completion of reception
     * ---------------------------------------------------------------- */
    // while(((HWREG_BP(CANA_BASE + CAN_O_ES) & CAN_ES_RXOK)) != CAN_ES_RXOK)
    // {
    //     if(count++ > 0xE000)
    //     {
    //         //接收数据超时
    //         CanScan.err_box_id |= DataBit_Set(CanScan.err_box_id,id-RX_MBOX_BASE);
    //         count = 0;
    //         return Error_4;
    //         break;
    //     }
    // }
    /* 标志位满足后接收数据
     * ---------------------------------------------------------------- */
    msgid = (HWREG_BP(CANA_BASE + CAN_O_NDAT_21));
    box_msk = (uint32_t)1 << id;
    if((msgid&box_msk) > 0)
    {
        CAN_readMessage(CANA_BASE, id+1, msgData);//接收数据
        pbuff[0] = ( msgData[0]<<8 ) + msgData[1];
        pbuff[1] = ( msgData[2]<<8 ) + msgData[3];
        pbuff[2] = ( msgData[4]<<8 ) + msgData[5];
        pbuff[3] = ( msgData[6]<<8 ) + msgData[7];
    }

    return Success;
}
/* ---------------------------------------------------------------------------------------------------------- */
uint16_t  DataBit_Set(uint16_t data,uint16_t bit)
{
    if(bit>15)
        return data;
    else
        data |= (uint16_t) ( 1<<bit ) ;
    return data;
}
uint16_t  DataBit_Reset(uint16_t data,uint16_t bit)
{
    if(bit>15)
        return data;
    else
        data &= (uint16_t) ( ~(1<<bit) ) ;
    return data;
}
uint16_t   DataBit_Reead(uint16_t data,uint16_t bit)
{
    if(bit>31)
        return data;
    else
    {
        data &= (uint16_t) ( 1 << bit );
        data = data >> bit ;
        return data;
    }
}
static void can_err_timer1(void)
{
    if(DataBit_Reead(CanScan.err_box_id,0)&
            DataBit_Reead(CanScan.err_box_id,1)&
            DataBit_Reead(CanScan.err_box_id,2) ==1  )
    {
        CanScan.err_timer1++;
        DataBit_Set(CanScan.err_derive,0);
        if( CanScan.err_timer1%2000 == 0)
        {
            //累计2000ms尝试重连
            CanScan.err_box_id = DataBit_Reset(CanScan.err_box_id,TX_MBOX_BASE+0);
            CanScan.err_box_id = DataBit_Reset(CanScan.err_box_id,TX_MBOX_BASE+1);
            CanScan.err_box_id = DataBit_Reset(CanScan.err_box_id,TX_MBOX_BASE+2);
            DataBit_Reset(CanScan.err_derive,0);
        }
    }
    else
    {
        CanScan.err_timer1 = 0;
        DataBit_Reset(CanScan.err_derive,0);
    }
}
static void can_err_timer2(void)
{
    if(DataBit_Reead(CanScan.err_box_id,3)&
            DataBit_Reead(CanScan.err_box_id,4)&
            DataBit_Reead(CanScan.err_box_id,5) ==1  )
    {
        CanScan.err_timer2++;
        DataBit_Set(CanScan.err_derive,1);
        if( CanScan.err_timer2%2000 == 0)
        {
            //累计2000ms尝试重连
            CanScan.err_box_id = DataBit_Reset(CanScan.err_box_id,TX_MBOX_BASE+3);
            CanScan.err_box_id = DataBit_Reset(CanScan.err_box_id,TX_MBOX_BASE+4);
            CanScan.err_box_id = DataBit_Reset(CanScan.err_box_id,TX_MBOX_BASE+5);
            DataBit_Reset(CanScan.err_derive,1);
        }
    }
    else{
        CanScan.err_timer2 = 0;
    DataBit_Reset(CanScan.err_derive,1);
    }
}
static void can_err_timer3(void)
{
    if(DataBit_Reead(CanScan.err_box_id,6)&
            DataBit_Reead(CanScan.err_box_id,7)&
            DataBit_Reead(CanScan.err_box_id,8) ==1  )
    {
        CanScan.err_timer3++;
        DataBit_Set(CanScan.err_derive,2);
       if( CanScan.err_timer3%2000 == 0)
        {
            //累计2000ms尝试重连
            CanScan.err_box_id = DataBit_Reset(CanScan.err_box_id,TX_MBOX_BASE+6);
            CanScan.err_box_id = DataBit_Reset(CanScan.err_box_id,TX_MBOX_BASE+7);
            CanScan.err_box_id = DataBit_Reset(CanScan.err_box_id,TX_MBOX_BASE+8);
            DataBit_Reset(CanScan.err_derive,2);
        }
    }
    else
    {
        CanScan.err_timer3 = 0;
        DataBit_Reset(CanScan.err_derive,2);
    }
}
static void can_err_timer4(void)
{
    if(DataBit_Reead(CanScan.err_box_id,9)&
            DataBit_Reead(CanScan.err_box_id,10)&
            DataBit_Reead(CanScan.err_box_id,11) ==1  )
    {
        CanScan.err_timer4++;
        DataBit_Set(CanScan.err_derive,3);
        if( CanScan.err_timer4%2000 == 0)
        {
            //累计2000ms尝试重连
            CanScan.err_box_id = DataBit_Reset(CanScan.err_box_id,TX_MBOX_BASE+9);
            CanScan.err_box_id = DataBit_Reset(CanScan.err_box_id,TX_MBOX_BASE+10);
            CanScan.err_box_id = DataBit_Reset(CanScan.err_box_id,TX_MBOX_BASE+11);
            DataBit_Reset(CanScan.err_derive,3);
        }
    }
    else
    {
        CanScan.err_timer4 = 0;
        DataBit_Reset(CanScan.err_derive,3);
    }
}
static void can_err_timer5(void)
{
    if(DataBit_Reead(CanScan.err_box_id,12)&
            DataBit_Reead(CanScan.err_box_id,13)&
            DataBit_Reead(CanScan.err_box_id,14) ==1  )
    {
        CanScan.err_timer5++;
        DataBit_Set(CanScan.err_derive,4);
        if( CanScan.err_timer5%2000 == 0)
        {
            //累计2000ms尝试重连
            CanScan.err_box_id = DataBit_Reset(CanScan.err_box_id,TX_MBOX_BASE+12);
            CanScan.err_box_id = DataBit_Reset(CanScan.err_box_id,TX_MBOX_BASE+13);
            CanScan.err_box_id = DataBit_Reset(CanScan.err_box_id,TX_MBOX_BASE+14);
            DataBit_Reset(CanScan.err_derive,4);
        }
    }
    else
    {
        CanScan.err_timer5 = 0;
        DataBit_Reset(CanScan.err_derive,4);
    }
}
void can_err_timer(uint8_t quantity)
{
    switch(quantity)
    {
        case 5:
            can_err_timer5();
            //break;
        case 4:
            can_err_timer4();
            //break;
        case 3:
            can_err_timer3();
            //break;
        case 2:
            can_err_timer2();
            //break;
        case 1:
            can_err_timer1();
            //break;
        default:
            break;
    }

}
/*-------------------------------------------*/
/*  向对应邮箱ram写入数据
 *  msgData     写入的数据
 *  base        CANB_BASE/CANA_BASE
 *  box_n       MBOX1~32
 * */
void write_to_box(const uint16_t *msgData,uint32_t base,uint16_t box_n)
{
    uint16_t cnt;
    uint32_t data_lsb = 0U ,data_msb = 0U;

    ASSERT(CAN_isBaseValid(base));
    ASSERT((box_n <= 32U) && (box_n > 0U));

    for(cnt = 0;cnt < 4; cnt++)
    {
        data_msb |= ( (uint32_t)(msgData[cnt]) ) << (cnt*8);
    }
    for(cnt = 4;cnt < 8; cnt++)
    {
        data_lsb |= ( (uint32_t)(msgData[cnt]) ) << ( (cnt-4)*8 );
    }
    // Transmit messages from CAN-A
    //  读写邮箱ram必须借助IF1 IF2 IF3
    HWREG_BP(base + CAN_O_IF1DATA)  = data_msb;// 0x4433 2211UL;
    HWREG_BP(base + CAN_O_IF1DATB)  = data_lsb;// 0x88776655UL;
    //
    // Transfer to MBX RAM
    //                                  CAN_IF1CMD_DIR|CAN_IF1CMD_DATA_B|CAN_IF1CMD_DATA_A
    HWREG_BP(base + CAN_O_IF1CMD)  =  CAN_IF1CMD_DIR|CAN_IF1CMD_DATA_B|CAN_IF1CMD_DATA_A|box_n;//0x00830002UL;
}

void CanBBasic_init(void)
{
    CanBScan.dev_nums = 3;   //采样板数量
    CanB_init(500);
    CanB_mbox_set();
    CanBScan.run_flag = 0;
    CanBScan.run_timer = 0;
}

static void CanB_init(uint8_t BitRate)
{
    //
    // Initialize GPIO and configure GPIO pins for CANTX/CANRX
    // on module A
    //
    GPIO_setPinConfig(GPIO_20_CANTXB);
    GPIO_setPinConfig(GPIO_21_CANRXB);
    //
    // Initialize the CAN controllers
    //
    CAN_initModule(CANB_BASE);
    //
    // Set up the CAN bus bit rate to 500kHz for each module
    // Refer to the Driver Library User Guide for information on how to set
    // tighter timing control. Additionally, consult the device data sheet
    // for more information about the CAN module clocking.
    if (BitRate == 500)
    {
        // 500k
        CAN_setBitRate(CANB_BASE, DEVICE_SYSCLK_FREQ, 500000, 16);
    }
    else if (BitRate == 1000)
    {
        // 1M
        CAN_setBitRate(CANB_BASE, DEVICE_SYSCLK_FREQ, 1000000, 8);
    }
    else if (BitRate == 250)
    {
        // 250
        CAN_setBitRate(CANB_BASE, DEVICE_SYSCLK_FREQ, 250000, 32);
    }
}
static uint8_t CanB_mbox_set(void)
{
    uint16_t i;
    uint32_t msgid;
    for (i = 0; i < 10; i++)
    {
        //发送
        CAN_setupMessageObject(CANB_BASE, MBOX0 + i, 0x3e1 + i,
                               CAN_MSG_FRAME_EXT, CAN_MSG_OBJ_TYPE_TX, 0,
                               CAN_MSG_OBJ_NO_FLAGS, Byte_8);
        //接收
        msgid = 0x00000213 + (i << 4);
        CAN_setupMessageObject(CANB_BASE, MBOX16 + i, msgid,
                               CAN_MSG_FRAME_EXT, CAN_MSG_OBJ_TYPE_RX, 0xFFFFFFFC,
                               CAN_MSG_OBJ_USE_ID_FILTER | CAN_MSG_OBJ_NO_FLAGS, Byte_8);
    }
    // // //邮箱0 邮箱1 初始化为普通发送邮箱
    // CAN_setupMessageObject(CANB_BASE, MBOX0, 0x3e1,
    //                        CAN_MSG_FRAME_EXT, CAN_MSG_OBJ_TYPE_TX, 0,
    //                        CAN_MSG_OBJ_NO_FLAGS, Byte_8);
    // CAN_setupMessageObject(CANB_BASE, MBOX1, 0x3e2,
    //                        CAN_MSG_FRAME_EXT, CAN_MSG_OBJ_TYPE_TX, 0,
    //                        CAN_MSG_OBJ_NO_FLAGS, Byte_8);

    // // 邮箱16 邮箱17设置为接收邮箱
    // CAN_setupMessageObject(CANB_BASE, MBOX16, 0x00000213,
    //                        CAN_MSG_FRAME_EXT, CAN_MSG_OBJ_TYPE_RX, 0xFFFFFFFC,
    //                        CAN_MSG_OBJ_USE_ID_FILTER | CAN_MSG_OBJ_NO_FLAGS, Byte_8);
    // CAN_setupMessageObject(CANB_BASE, MBOX17, 0x00000223,
    //                        CAN_MSG_FRAME_EXT, CAN_MSG_OBJ_TYPE_RX, 0xFFFFFFFC,
    //                        CAN_MSG_OBJ_USE_ID_FILTER | CAN_MSG_OBJ_NO_FLAGS, Byte_8);

    // Start CAN module A operations
    //
    CAN_startModule(CANA_BASE);
    return Success;
}


uint8_t CanB_send(uint8_t id)
{
    uint16_t msgData[8];
    uint16_t count = 0;
    if (id > 15)
        return Error_1;
    msgData[0] = 0x01;
    msgData[1] = 0x00;
    msgData[2] = 0x00;
    msgData[3] = 0x00;
    msgData[4] = 0x00;
    msgData[5] = 0x00;
    msgData[6] = 0x00;
    msgData[7] = 0x00;
    /* CAN 发送数据,035邮箱从0开始，377从1开始，所有邮箱+1 */
    CAN_sendMessage(CANB_BASE, id + 1, Byte_8, msgData);
    /* 等待发送完成 */
    while (((HWREGH(CANB_BASE + CAN_O_ES) & CAN_ES_TXOK)) != CAN_ES_TXOK)
    {
        /*8字节标准帧为108bit,1M速率发送需要108us,500K速率发送需要216us
         * 200M主频，T=1/200M=0.005us 计数到216us需要86400
         * */
        if (count++ > 0xE000)
        {
            //发送超时
            count = 0;
            return Error_3;
            break;
        }
    }
    /* 帧间隔3bit 主频200M 速率1M
     * ---------------------------------------------------------------- */
    //    for(count = 0;count<600;count++)
    //    {}

    return Success;
}

uint8_t CanB_receive(uint8_t nums, uint16_t *pbuff)
{

    uint16_t msgData[8];
    uint8_t add, i;
    uint32_t box_msk;
    /* 检查邮箱合法性
     * MBOX16-MBOX21  17-22
     * ---------------------------------------------------------------- */
    if (nums > 10)
    {
        return Error_1;
    }
    box_msk = (1 << nums) - 1;
    box_msk = box_msk << 16;
    /* 检查接收是否成功
     * Poll RxOk bit in CAN_ES register to check completion of reception
     * ---------------------------------------------------------------- */
    CanBScan.box.all = (HWREG_BP(CANB_BASE + CAN_O_NDAT_21));
    CanBScan.box.all &= box_msk;
    // if ((HWREG_BP(CANB_BASE + CAN_O_NDAT_21)) == ndat)
    if (CanBScan.box.all > 0)
    {
        /* 标志位满足后接收数据
         * ---------------------------------------------------------------- */

        // CAN_readMessage(CANB_BASE, id+1, msgData);//接收数据
        if (CanBScan.box.bit.M0)
        {
            asm("  NOP");
            i = 0;
            CAN_readMessageWithID(CANB_BASE, 17 + i, CAN_MSG_FRAME_STD, &CanBScan.BmsgID, msgData);
            add = (uint8_t)(CanBScan.BmsgID & 0x00000003);
            if (add > 3)
            {
                return Error_2;
            }
            pbuff[(i * 16) + (add * 4) + 0] = (msgData[0] << 8) + msgData[1];
            pbuff[(i * 16) + (add * 4) + 1] = (msgData[2] << 8) + msgData[3];
            pbuff[(i * 16) + (add * 4) + 2] = (msgData[4] << 8) + msgData[5];
            pbuff[(i * 16) + (add * 4) + 3] = (msgData[6] << 8) + msgData[7];
        }
        if (CanBScan.box.bit.M1)
        {
            asm("  NOP");
            i = 1;
            CAN_readMessageWithID(CANB_BASE, 17 + i, CAN_MSG_FRAME_STD, &CanBScan.BmsgID, msgData);
            add = (uint8_t)(CanBScan.BmsgID & 0x00000003);
            if (add > 3)
            {
                return Error_2;
            }
            pbuff[(i * 16) + (add * 4) + 0] = (msgData[0] << 8) + msgData[1];
            pbuff[(i * 16) + (add * 4) + 1] = (msgData[2] << 8) + msgData[3];
            pbuff[(i * 16) + (add * 4) + 2] = (msgData[4] << 8) + msgData[5];
            pbuff[(i * 16) + (add * 4) + 3] = (msgData[6] << 8) + msgData[7];
        }
        if (CanBScan.box.bit.M2)
        {
            asm("  NOP");
            i = 2;
            CAN_readMessageWithID(CANB_BASE, 17 + i, CAN_MSG_FRAME_STD, &CanBScan.BmsgID, msgData);
            add = (uint8_t)(CanBScan.BmsgID & 0x00000003);
            if (add > 3)
            {
                return Error_2;
            }
            pbuff[(i * 16) + (add * 4) + 0] = (msgData[0] << 8) + msgData[1];
            pbuff[(i * 16) + (add * 4) + 1] = (msgData[2] << 8) + msgData[3];
            pbuff[(i * 16) + (add * 4) + 2] = (msgData[4] << 8) + msgData[5];
            pbuff[(i * 16) + (add * 4) + 3] = (msgData[6] << 8) + msgData[7];
        }
        if (CanBScan.box.bit.M3)
        {
            asm("  NOP");
            i = 3;
            CAN_readMessageWithID(CANB_BASE, 17 + i, CAN_MSG_FRAME_STD, &CanBScan.BmsgID, msgData);
            add = (uint8_t)(CanBScan.BmsgID & 0x00000003);
            if (add > 3)
            {
                return Error_2;
            }
            pbuff[(i * 16) + (add * 4) + 0] = (msgData[0] << 8) + msgData[1];
            pbuff[(i * 16) + (add * 4) + 1] = (msgData[2] << 8) + msgData[3];
            pbuff[(i * 16) + (add * 4) + 2] = (msgData[4] << 8) + msgData[5];
            pbuff[(i * 16) + (add * 4) + 3] = (msgData[6] << 8) + msgData[7];
        }
        if (CanBScan.box.bit.M4)
        {
            asm("  NOP");
            i = 4;
            CAN_readMessageWithID(CANB_BASE, 17 + i, CAN_MSG_FRAME_STD, &CanBScan.BmsgID, msgData);
            add = (uint8_t)(CanBScan.BmsgID & 0x00000003);
            if (add > 3)
            {
                return Error_2;
            }
            pbuff[(i * 16) + (add * 4) + 0] = (msgData[0] << 8) + msgData[1];
            pbuff[(i * 16) + (add * 4) + 1] = (msgData[2] << 8) + msgData[3];
            pbuff[(i * 16) + (add * 4) + 2] = (msgData[4] << 8) + msgData[5];
            pbuff[(i * 16) + (add * 4) + 3] = (msgData[6] << 8) + msgData[7];
        }
        if (CanBScan.box.bit.M5)
        {
            asm("  NOP");
            i = 5;
            CAN_readMessageWithID(CANB_BASE, 17 + i, CAN_MSG_FRAME_STD, &CanBScan.BmsgID, msgData);
            add = (uint8_t)(CanBScan.BmsgID & 0x00000003);
            if (add > 3)
            {
                return Error_2;
            }
            pbuff[(i * 16) + (add * 4) + 0] = (msgData[0] << 8) + msgData[1];
            pbuff[(i * 16) + (add * 4) + 1] = (msgData[2] << 8) + msgData[3];
            pbuff[(i * 16) + (add * 4) + 2] = (msgData[4] << 8) + msgData[5];
            pbuff[(i * 16) + (add * 4) + 3] = (msgData[6] << 8) + msgData[7];
        }
        if (CanBScan.box.bit.M6)
        {
            asm("  NOP");
            i = 6;
            CAN_readMessageWithID(CANB_BASE, 17 + i, CAN_MSG_FRAME_STD, &CanBScan.BmsgID, msgData);
            add = (uint8_t)(CanBScan.BmsgID & 0x00000003);
            if (add > 3)
            {
                return Error_2;
            }
            pbuff[(i * 16) + (add * 4) + 0] = (msgData[0] << 8) + msgData[1];
            pbuff[(i * 16) + (add * 4) + 1] = (msgData[2] << 8) + msgData[3];
            pbuff[(i * 16) + (add * 4) + 2] = (msgData[4] << 8) + msgData[5];
            pbuff[(i * 16) + (add * 4) + 3] = (msgData[6] << 8) + msgData[7];
        }
        if (CanBScan.box.bit.M7)
        {
            asm("  NOP");
            i = 7;
            CAN_readMessageWithID(CANB_BASE, 17 + i, CAN_MSG_FRAME_STD, &CanBScan.BmsgID, msgData);
            add = (uint8_t)(CanBScan.BmsgID & 0x00000003);
            if (add > 3)
            {
                return Error_2;
            }
            pbuff[(i * 16) + (add * 4) + 0] = (msgData[0] << 8) + msgData[1];
            pbuff[(i * 16) + (add * 4) + 1] = (msgData[2] << 8) + msgData[3];
            pbuff[(i * 16) + (add * 4) + 2] = (msgData[4] << 8) + msgData[5];
            pbuff[(i * 16) + (add * 4) + 3] = (msgData[6] << 8) + msgData[7];
        }
        if (CanBScan.box.bit.M8)
        {
            asm("  NOP");
            i = 8;
            CAN_readMessageWithID(CANB_BASE, 17 + i, CAN_MSG_FRAME_STD, &CanBScan.BmsgID, msgData);
            add = (uint8_t)(CanBScan.BmsgID & 0x00000003);
            if (add > 3)
            {
                return Error_2;
            }
            pbuff[(i * 16) + (add * 4) + 0] = (msgData[0] << 8) + msgData[1];
            pbuff[(i * 16) + (add * 4) + 1] = (msgData[2] << 8) + msgData[3];
            pbuff[(i * 16) + (add * 4) + 2] = (msgData[4] << 8) + msgData[5];
            pbuff[(i * 16) + (add * 4) + 3] = (msgData[6] << 8) + msgData[7];
        }
        if (CanBScan.box.bit.M9)
        {
            asm("  NOP");
            i = 9;
            CAN_readMessageWithID(CANB_BASE, 17 + i, CAN_MSG_FRAME_STD, &CanBScan.BmsgID, msgData);
            add = (uint8_t)(CanBScan.BmsgID & 0x00000003);
            if (add > 3)
            {
                return Error_2;
            }
            pbuff[(i * 16) + (add * 4) + 0] = (msgData[0] << 8) + msgData[1];
            pbuff[(i * 16) + (add * 4) + 1] = (msgData[2] << 8) + msgData[3];
            pbuff[(i * 16) + (add * 4) + 2] = (msgData[4] << 8) + msgData[5];
            pbuff[(i * 16) + (add * 4) + 3] = (msgData[6] << 8) + msgData[7];
        }
    }

    /* 帧间隔3bit 主频200M 速率1M
     * ---------------------------------------------------------------- */
    // for (count = 0; count < 600; count++)
    // {
    // }
    return Success;
}

