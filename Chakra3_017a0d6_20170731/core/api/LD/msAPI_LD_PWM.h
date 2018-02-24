#ifndef _MSAPI_LD_PWM_H_
#define _MSAPI_LD_PWM_H_

#include "Board.h"

#if ( LD_ENABLE )

#define No_DoubleBF     0
#define DoubleBF        1
#define Vsync_DoubleBF  2

typedef enum DRV_PWM_CH_e
{
    PWM_CH0 = 0,
    PWM_CH1,
    PWM_CH2,
    PWM_CH3,
    PWM_CH4,
    PWM_CH5,
    PWM_NUMS,
    PWM_MAX = 0xFF
}DRV_PWM_CH;

typedef enum
{
    PWM_RST_CTRL__NONE,
    PWM_RST_CTRL__VSYNC,
    PWM_RST_CTRL__LRFLAG,
    PWM_RST_CTRL__HSYNC,
} EnuPwmRstCtrl;


#if 1
#define MDrv_MFC_PWM_waveform_maker( u8PWMNum,  u16FrequencyX10,  u16DutyInPercentX100, \
                                  u16ShiftIn360DegreeX100,  u16Div,  SyncRstCnt, \
                                  u8DoubleBufferSelect,  ePwmRstCtrl,  bPolarity     )

#else
void MDrv_MFC_PWM_waveform_maker(DRV_PWM_CH u8PWMNum, U16 u16FrequencyX10, U16 u16DutyInPercentX100,
    U16 u16ShiftIn360DegreeX100, U16 u16Div, U8 SyncRstCnt,
    U8 u8DoubleBufferSelect, EnuPwmRstCtrl ePwmRstCtrl, BOOL bPolarity );

#endif

void MApi_LD_PWM_Init(void);
void MApi_LD_PWM_Update(void);

#endif // LD_ENABLE

#endif // _URSA_PWM_H_

