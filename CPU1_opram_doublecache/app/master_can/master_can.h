#ifndef MASTER_CAN_H
#define MASTER_CAN_H


//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif
//*****************************************************************************
// include
//*****************************************************************************
#include "driverlib.h"
#include "device.h"
#define     TX_MBOX_BASE        0   //��ʼ���ĵ�һ����������
#define     TX_MBOX_NUMS        12   //��ʼ���������������
#define     TX_MBOX_MAX         TX_MBOX_BASE+TX_MBOX_NUMS-1    //���һ����������
#define     TX_BUFF_MAXNUM      TX_MBOX_NUMS*4

#define     RX_MBOX_BASE        16   //��ʼ���ĵ�һ����������
#define     RX_MBOX_NUMS        12   //��ʼ���������������
#define     RX_MBOX_MAX         RX_MBOX_BASE+RX_MBOX_NUMS-1    //���һ����������
#define     RX_BUFF_MAXNUM      RX_MBOX_NUMS*4

#define     HEART_OUTTIME       5000
/*ö��1-32��Ӧ��Ϣ����0~31*/
typedef enum
{
   MBOX0 = 1,
   MBOX1,
   MBOX2,
   MBOX3,
   MBOX4,
   MBOX5,
   MBOX6,
   MBOX7,
   MBOX8,
   MBOX9,
   MBOX10,
   MBOX11,
   MBOX12,
   MBOX13,
   MBOX14,
   MBOX15,
   MBOX16,
   MBOX17,
   MBOX18,
   MBOX19,
   MBOX20,
   MBOX21,
   MBOX22,
   MBOX23,
   MBOX24,
   MBOX25,
   MBOX26,
   MBOX27,
   MBOX28,
   MBOX29,
   MBOX30,
   MBOX31
} CAN_MBOX;
/*ö��1-8������can��Ϣ�ֽڳ���1-8�ֽ�*/
typedef enum
{
   Byte_0 = 0,
   Byte_1 = 1,
   Byte_2,
   Byte_3,
   Byte_4,
   Byte_5,
   Byte_6,
   Byte_7,
   Byte_8

} DATA_LENGTH;
/*ö��0-7,������������ֵ��0��ȷ��������ʾ����*/
typedef enum
{
    Success = 0,
    Error_1 = 1,
    Error_2,
    Error_3,
    Error_4,
    Error_5,
    Error_6,
    Error_7,
    Error_8
} ERR_TYPE;
typedef struct CAN_SCAN{
    uint16_t  Tx_Buff[TX_BUFF_MAXNUM];//�洢��������
    uint16_t  Rx_Buff[RX_BUFF_MAXNUM];//�洢��������

    uint32_t  run_timer;//canɨ���ʱ
    uint32_t  run_count;//���дӻ���ѯһ��+1
    uint16_t run_flag;
    uint16_t dly_com1;
    uint16_t dly_com1_1;
    uint16_t dly_com2;
    uint16_t dly_com2_1;
    uint16_t dly_com3;
    uint16_t dly_com3_1;
    uint16_t dly_com4;
    uint16_t dly_com4_1;
    uint16_t  err_derive;
    uint16_t  err_box_id; //����ʧ�ܵ�����
    uint32_t  err_timer1;   //�豸1ʧ�ܼ�ʱ
    uint32_t  err_timer2;   //�豸2ʧ�ܼ�ʱ
    uint32_t  err_timer3;   //�豸3ʧ�ܼ�ʱ
    uint32_t  err_timer4;   //�豸4ʧ�ܼ�ʱ
    uint32_t  err_timer5;   //�豸5ʧ�ܼ�ʱ
}CAN_SCAN;
extern CAN_SCAN CanScan;

struct BOX_BITS {                   // bits description
    uint32_t rsvd:16;                    // 31:16 Reserved
    uint32_t M0:1;                  // 0 Master Select for GS0 RAM
    uint32_t M1:1;                  // 1 Master Select for GS1 RAM
    uint32_t M2:1;                  // 2 Master Select for GS2 RAM
    uint32_t M3:1;                  // 3 Master Select for GS3 RAM
    uint32_t M4:1;                  // 4 Master Select for GS4 RAM
    uint32_t M5:1;                  // 5 Master Select for GS5 RAM
    uint32_t M6:1;                  // 6 Master Select for GS6 RAM
    uint32_t M7:1;                  // 7 Master Select for GS7 RAM
    uint32_t M8:1;                  // 8 Master Select for GS8 RAM
    uint32_t M9:1;                  // 9 Master Select for GS9 RAM
    uint32_t M10:1;                 // 10 Master Select for GS10 RAM
    uint32_t M11:1;                 // 11 Master Select for GS11 RAM
    uint32_t M12:1;                 // 12 Master Select for GS12 RAM
    uint32_t M13:1;                 // 13 Master Select for GS13 RAM
    uint32_t M14:1;                 // 14 Master Select for GS14 RAM
    uint32_t M15:1;                 // 15 Master Select for GS15 RAM
};

union BOX_REG {
    uint32_t  all;
    struct  BOX_BITS  bit;
};

typedef struct CANB_SCAN{
    uint32_t  BmsgID;
    uint16_t  RxB_Buff[16][16];
    union  BOX_REG box;
    uint16_t  dev_nums;
    uint16_t run_count;
    uint16_t run_flag;
    uint16_t run_timer;

}CANB_SCAN;
extern CANB_SCAN CanBScan;



//*****************************************************************************
// Defines
//*****************************************************************************
#define TXCOUNT  100000


//*****************************************************************************
extern void init_can_a(void);
extern void init_can_b(void);
extern void write_to_box(const uint16_t *msgData,uint32_t base,uint16_t box_n);
extern void CanABasic_init(void);
extern void CanBBasic_init(void);
extern void CanA_reset(void);
extern uint8_t CanB_receive(uint8_t nums, uint16_t *pbuff);
extern uint8_t CanB_send(uint8_t id);
extern uint8_t can_send_OneFrameData(uint8_t id, const uint16_t *pdata);
extern uint8_t can_receive_OneFrameData(uint8_t id,uint16_t *pbuff);

extern uint16_t   DataBit_Set  (uint16_t data,uint16_t bit);
extern uint16_t   DataBit_Reset(uint16_t data,uint16_t bit);
extern uint16_t   DataBit_Reead(uint16_t data,uint16_t bit);
extern void       can_err_timer(uint8_t quantity);
#ifdef __cplusplus
}
#endif

#endif //  CAN_H
