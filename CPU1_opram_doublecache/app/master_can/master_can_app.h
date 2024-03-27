#ifndef MASTER_CAN__APP_H
#define MASTER_CAN__APP_H


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
#include "master_can.h"
#define  led_30_tog()    GPIO_togglePin(94)
#define  led_31_tog()    GPIO_togglePin(99)

struct can_run_err {
    uint8_t     send_out_time_count;
    uint8_t     send_out_time_flag;
    uint8_t     read_out_time_count;
    uint8_t     read_out_time_flag;
};

extern struct MAIN_LOOP m_loop;
//
// Function Prototypes (External)
//
/*extern */



extern bool   can_run_flag;
extern bool   can_get_flag;

extern void CanApp_MainFunction(uint8_t quantity);
extern void CanApp_RX_MainFunction(uint8_t quantity);
extern void Can_Heart(uint8_t quantity);

extern void led_init(void);
extern void led_30_ctrl(uint8_t led);
extern void led_31_ctrl(uint8_t led);



/*
extern uint8_t  test_remote_rec(uint8_t box);
extern uint8_t  test_simple_send(uint8_t box , uint8_t device_n);
extern uint8_t  refresh_can_set_data(uint8_t device_n);
extern void test_simple_rec(void);
*/


#ifdef __cplusplus
}
#endif

#endif //  CAN_H
