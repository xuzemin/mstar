#include "Board.h"

#if ( LD_ENABLE )

#include "debug.h"

#include "drvGlobal.h"
#include "drvPWM.h"

#include "apiXC.h"

#include "msAPI_LD_PWM.h"

//======================================================================

//#define DEBUG_PWM(x)    x
#define DEBUG_LD_PWM(x) x


#if( MS_BOARD_TYPE_SEL == BD_MST084B_10AHB_15043 )
    #define LD_HSYNC_USE_PWM_CH E_PWM_CH0
    #define LD_VSYNC_USE_PWM_CH E_PWM_CH1
    #define LD_CS_USE_PWM_CH    E_PWM_CH3

    //#define LD_INT_USE_PWM_CH   E_PWM_CH2

#elif(( MS_BOARD_TYPE_SEL == BD_MST222F_D01A_S )||( MS_BOARD_TYPE_SEL == BD_SOLUM_XL1U ))
/*
PAD_PWM0        PWM : HSync
PAD_PWM1        PWM : VSync
PAD_PWM3        PWM : CS
PAD_TCON2       SPI: MSPI1_SCK
PAD_TCON3       SPI: MSPI1_SDI   ( 這個才是 output)
*/

    #define LD_HSYNC_USE_PWM_CH E_PWM_CH0
    #define LD_VSYNC_USE_PWM_CH E_PWM_CH1
    #define LD_CS_USE_PWM_CH    E_PWM_CH3

    //#define LD_INT_USE_PWM_CH   E_PWM_CH2

#endif

#define LD_VSYNC_PLUSE_WIDTH_US 1000 // us


#define PWM_EXT_CLK     12000000// 24000000(Crystall_Clk)/2

#define PWM_HSYNC_HTOTAL    4096


#define PWM_REG_BASE    0x13F400



// reg_force_shift_set_en0	0	0	1	h0	rw	PWM0 enable to avoid pwm_sig trigger fail after Vsync with reg_shift = 0 & bad reg_div set
void MHal_PWM_Set_ForceShift0(PWM_ChNum ePWM_Ch, BOOL bEnable)
{
    U16 u16Mask = (BIT6)<<ePWM_Ch;

    //printf("MHal_PWM_Set_ForceShift0(%u,%u)\n", ePWM_Ch, bEnable);
    //printf(" u16Mask=0x%X\n", u16Mask);

    MDrv_Write2ByteMask(PWM_REG_BASE+0x6A, (bEnable?u16Mask:0), u16Mask);
}

// PWM-Int
// 2D use R
typedef enum
{
    PWM_INT_RP_L,
    PWM_INT_FP_L,
    PWM_INT_RP_R,
    PWM_INT_FP_R,
} EnuPwmIntType;
void MHal_PWM_Set_Int(PWM_ChNum ePWM_Ch, EnuPwmIntType ePwmIntType, BOOLEAN bEnable)
{
    U8 u8Reg = 0xCC;
    U16 u16Mask = 0;


    if( (ePwmIntType == PWM_INT_RP_L) || (ePwmIntType == PWM_INT_FP_L) )
        u8Reg = 0xCC;
    else
        u8Reg = 0xCE;

    if( (ePwmIntType == PWM_INT_RP_L) || (ePwmIntType == PWM_INT_RP_R) )
        u16Mask = 0x01;
    else
        u16Mask = 0x02;

    u16Mask = u16Mask << (ePWM_Ch*2);

    printf("MHal_PWM_Set_Int(%u,%u, %u)\n", ePWM_Ch, ePwmIntType, bEnable);

    printf(" u8Reg=0x%X, u16Mask=0x%X\n", u8Reg, u16Mask);

    MDrv_Write2ByteMask(PWM_REG_BASE+u8Reg, (bEnable?u16Mask:0), u16Mask);
}


typedef enum
{
    SET_PWM_FOR_INIT,
    SET_PWM_FOR_VFREQ_CHANGE,
}EunPwmSetupCase;

void MApi_LD_PWM_Setup_VSync(U32 u32VFreqx1000, EunPwmSetupCase eSetPwmCase)
{
    DEBUG_LD_PWM( printf("MApi_LD_PWM_Setup_VSync(u32VFreqx1000=%u, case=%u)\n", u32VFreqx1000, eSetPwmCase); );

    DEBUG_LD_PWM( printf("Force V Freq 30\n"); );
    u32VFreqx1000 = 30000;

    PWM_ChNum ePWM_Ch = LD_VSYNC_USE_PWM_CH;

    U8 u8Divider = 12; // For PWM Clk = 1M

    //period*div = xtal/frequency       //, 100000*2 = 12000000/60
    // period = xtal/div/freq

    U32 u32PWMClk = PWM_EXT_CLK / u8Divider;
    U32 u32Period = (u32PWMClk * 1000) / u32VFreqx1000 + 1;

    U32 u32Shift = 0x00;

    U32 u32VSyncPulseWidth = LD_VSYNC_PLUSE_WIDTH_US; // 1000us

    U32 u32Duty = u32PWMClk / (1000000/u32VSyncPulseWidth);

    DEBUG_LD_PWM( printf("ePWM_Ch=%u\n", ePWM_Ch); );

    DEBUG_LD_PWM( printf("u8Divider=%u\n", u8Divider); );
    DEBUG_LD_PWM( printf("u32PWMClk=%u\n", u32PWMClk); );

    DEBUG_LD_PWM( printf("u32Period=%u(0x%X)\n", u32Period, u32Period); );

    DEBUG_LD_PWM( printf("u32VSyncPulseWidth=%u\n", u32VSyncPulseWidth); );
    DEBUG_LD_PWM( printf("u32Duty=%u(0x%X)\n", u32Duty, u32Duty); );

    MDrv_PWM_Period(ePWM_Ch, u32Period-1);//200000-1);
    MDrv_PWM_DutyCycle(ePWM_Ch, u32Duty);//200);

    if( eSetPwmCase == SET_PWM_FOR_INIT )
    {
        MDrv_PWM_Div(ePWM_Ch, u8Divider - 1);
        MDrv_PWM_Shift(ePWM_Ch, u32Shift );

        if( ((u8Divider - 1)!=0)&& (u32Shift==0))
        {
            MHal_PWM_Set_ForceShift0(ePWM_Ch, TRUE);
        }
        else
        {
            MHal_PWM_Set_ForceShift0(ePWM_Ch, FALSE);
        }

        MDrv_PWM_Polarity(ePWM_Ch, NON_INVERSE);

        MDrv_PWM_Vdben(ePWM_Ch, YES);
        MDrv_PWM_ResetEn(ePWM_Ch, TRUE);

        MDrv_PWM_Oen(ePWM_Ch, 0);
    }
}

void MApi_LD_PWM_Setup_HSync(U32 u32VFreqx1000, EunPwmSetupCase eSetPwmCase)
{
    DEBUG_LD_PWM( printf("MApi_LD_PWM_Setup_HSync(u32VFreqx1000=%u, case=%u)\n", u32VFreqx1000, eSetPwmCase); );

    PWM_ChNum ePWM_Ch = LD_HSYNC_USE_PWM_CH;

    U8 u8Divider = 1;

    U32 u32PWMClk = PWM_EXT_CLK / u8Divider;
    U32 u32HFreq = u32VFreqx1000 * PWM_HSYNC_HTOTAL / 1000;

    U32 u32Period = u32PWMClk / u32HFreq  + 1;
    U32 u32Duty = u32Period / 2;

    U32 u32Shift = 0x00;

    DEBUG_LD_PWM( printf("ePWM_Ch=%u\n", ePWM_Ch); );

    DEBUG_LD_PWM( printf("u8Divider=%u\n", u8Divider); );
    DEBUG_LD_PWM( printf("u32PWMClk=%u\n", u32PWMClk); );

    DEBUG_LD_PWM( printf("u32HFreq=%u\n", u32HFreq); );
    DEBUG_LD_PWM( printf("u32Period=%u(0x%X)\n", u32Period, u32Period); );
    DEBUG_LD_PWM( printf("u32Duty=%u(0x%X)\n", u32Duty, u32Duty); );


    MDrv_PWM_Period(ePWM_Ch, u32Period-1);//49-1);
    MDrv_PWM_DutyCycle(ePWM_Ch, u32Duty);//23);

    if( eSetPwmCase == SET_PWM_FOR_INIT )
    {
        MDrv_PWM_Div(ePWM_Ch, u8Divider - 1);
        MDrv_PWM_Shift(ePWM_Ch, u32Shift );

        if( ((u8Divider - 1)!=0)&& (u32Shift==0))
        {
            MHal_PWM_Set_ForceShift0(ePWM_Ch, TRUE);
        }
        else
        {
            MHal_PWM_Set_ForceShift0(ePWM_Ch, FALSE);
        }


        MDrv_PWM_Polarity(ePWM_Ch, NON_INVERSE);

        MDrv_PWM_Vdben(ePWM_Ch, YES);
        MDrv_PWM_ResetEn(ePWM_Ch, TRUE);

        MDrv_PWM_Oen(ePWM_Ch, 0);
    }
}

void MApi_LD_PWM_Setup_CS(BOOL bEnable, EunPwmSetupCase eSetPwmCase)
{
    DEBUG_LD_PWM( printf("MApi_LD_PWM_Setup_CS(bEnable=%u, case=%u)\n", bEnable, eSetPwmCase); );

    U32 u32VFreqx1000 = 30000;

    PWM_ChNum ePWM_Ch = LD_CS_USE_PWM_CH;

    U8 u8Divider = 12;

    //period*div = xtal/frequency       //, 100000*2 = 12000000/60
    // period = xtal/div/freq

    U32 u32PWMClk = PWM_EXT_CLK / u8Divider;
    U32 u32PWM_UnitNS = 1000000000 / u32PWMClk;

    U32 u32Period = (u32PWMClk * 1000) / u32VFreqx1000 + 1;

    U32 u32PulseWidth = 100*1000; // 100us

    U32 u32Shift = 0x0D;
    U32 u32Duty = u32PulseWidth / u32PWM_UnitNS;

    DEBUG_LD_PWM( printf("ePWM_Ch=%u\n", ePWM_Ch); );

    DEBUG_LD_PWM( printf("u8Divider=%u\n", u8Divider); );
    DEBUG_LD_PWM( printf("u32PWMClk=%u\n", u32PWMClk); );
    DEBUG_LD_PWM( printf("u32PWM_UnitNS=%u\n", u32PWM_UnitNS); );

    DEBUG_LD_PWM( printf("u32Period=%u(0x%X)\n", u32Period, u32Period); );

    DEBUG_LD_PWM( printf("u32Shift=%u(0x%X)\n", u32Shift, u32Shift); );
    DEBUG_LD_PWM( printf("u32PulseWidth=%u\n", u32PulseWidth); );
    DEBUG_LD_PWM( printf("u32Duty=%u(0x%X)\n", u32Duty, u32Duty); );

    MDrv_PWM_Period(ePWM_Ch, u32Period-1);//200000-1);

    MDrv_PWM_DutyCycle(ePWM_Ch, u32Duty + u32Shift);//200);

    if( eSetPwmCase == SET_PWM_FOR_INIT )
    {
        MDrv_PWM_Div(ePWM_Ch, u8Divider - 1);
        MDrv_PWM_Shift(ePWM_Ch, u32Shift ); // todo

        if( ((u8Divider - 1)!=0)&& (u32Shift==0))
        {
            MHal_PWM_Set_ForceShift0(ePWM_Ch, TRUE);
        }
        else
        {
            MHal_PWM_Set_ForceShift0(ePWM_Ch, FALSE);
        }

        MDrv_PWM_Polarity(ePWM_Ch, INVERSE);

        MDrv_PWM_Vdben(ePWM_Ch, YES);
        MDrv_PWM_ResetEn(ePWM_Ch, TRUE);

        MDrv_PWM_Oen(ePWM_Ch, 0);
    }
}

void MApi_LD_PWM_Setup_Int(BOOL bEnable, EunPwmSetupCase eSetPwmCase)
{
    DEBUG_LD_PWM( printf("MApi_LD_PWM_Setup_Int(bEnable=%u, case=%u)\n", bEnable, eSetPwmCase); );

    U32 u32VFreqx1000 = 30000;

    PWM_ChNum ePWM_Ch = LD_CS_USE_PWM_CH;

    U8 u8Divider = 12;

    //period*div = xtal/frequency       //, 100000*2 = 12000000/60
    // period = xtal/div/freq

    U32 u32PWMClk = PWM_EXT_CLK / u8Divider;
    U32 u32PWM_UnitNS = 1000000000 / u32PWMClk;

    U32 u32Period = (u32PWMClk * 1000) / u32VFreqx1000 + 1;

    U32 u32PulseWidth = 15*1000*1000; // 15ms

    U32 u32Shift = 0x0;
    U32 u32Duty = u32PulseWidth / u32PWM_UnitNS;

    DEBUG_LD_PWM( printf("ePWM_Ch=%u\n", ePWM_Ch); );

    DEBUG_LD_PWM( printf("u8Divider=%u\n", u8Divider); );
    DEBUG_LD_PWM( printf("u32PWMClk=%u\n", u32PWMClk); );
    DEBUG_LD_PWM( printf("u32PWM_UnitNS=%u\n", u32PWM_UnitNS); );

    DEBUG_LD_PWM( printf("u32Period=%u(0x%X)\n", u32Period, u32Period); );

    //DEBUG_LD_PWM( printf("u32Shift=%u(0x%X)\n", u32Shift, u32Shift); );
    DEBUG_LD_PWM( printf("u32PulseWidth=%u\n", u32PulseWidth); );
    DEBUG_LD_PWM( printf("u32Duty=%u(0x%X)\n", u32Duty, u32Duty); );

    MDrv_PWM_Period(ePWM_Ch, u32Period-1);//200000-1);

    MDrv_PWM_DutyCycle(ePWM_Ch, u32Duty + u32Shift);//200);

    if( eSetPwmCase == SET_PWM_FOR_INIT )
    {
        MDrv_PWM_Div(ePWM_Ch, u8Divider - 1);
        MDrv_PWM_Shift(ePWM_Ch, u32Shift ); // todo

        if( ((u8Divider - 1)!=0)&& (u32Shift==0))
        {
            MHal_PWM_Set_ForceShift0(ePWM_Ch, TRUE);
        }
        else
        {
            MHal_PWM_Set_ForceShift0(ePWM_Ch, FALSE);
        }

        MDrv_PWM_Polarity(ePWM_Ch, NON_INVERSE);

        MDrv_PWM_Vdben(ePWM_Ch, YES);
        MDrv_PWM_ResetEn(ePWM_Ch, TRUE);

        MDrv_PWM_Oen(ePWM_Ch, 0);

        MHal_PWM_Set_Int( ePWM_Ch, PWM_INT_FP_R, bEnable);
    }
}

void MApi_LD_PWM_Init(void)
{
    PRINT_CURRENT_LINE();

    DEBUG_LD_PWM( printf("MApi_LD_PWM_Init()\n"); );

    MS_U32 u32OutputVFreqX1000 = MApi_XC_GetOutputVFreqX100()*10;

    MApi_LD_PWM_Setup_VSync(u32OutputVFreqX1000, SET_PWM_FOR_INIT);

    MApi_LD_PWM_Setup_HSync(u32OutputVFreqX1000, SET_PWM_FOR_INIT);

    MApi_LD_PWM_Setup_CS(u32OutputVFreqX1000, SET_PWM_FOR_INIT);

    //MApi_LD_PWM_Setup_Int(u32OutputVFreqX1000, SET_PWM_FOR_INIT);
}

void MApi_LD_PWM_Update(void)
{
    PRINT_CURRENT_LINE();

    MS_U32 u32OutputVFreqX1000 = MApi_XC_GetOutputVFreqX100()*10;

    // Because PWM-VSync reset by V Sync, nothing change
    MApi_LD_PWM_Setup_VSync(u32OutputVFreqX1000, SET_PWM_FOR_VFREQ_CHANGE);

    MApi_LD_PWM_Setup_HSync(u32OutputVFreqX1000, SET_PWM_FOR_VFREQ_CHANGE);

#if 0
    MS_U32 u32PWM_PERIOD;

    u32PWM_PERIOD = (long)(12000000 * 100 + (OutputVFreqX100/2))/(OutputVFreqX100);
    DEBUG_LD_PWM( printf("u32PWM_PERIOD=%u", u32PWM_PERIOD); );
    MDrv_PWM_Period(LD_VSYNC_USE_PWM_CH, u32PWM_PERIOD-1);    //Vsync

    u32PWM_PERIOD = (long)(12000000 * 100 + (OutputVFreqX100*4096/2))/(OutputVFreqX100*4096);
    DEBUG_LD_PWM( printf("u32PWM_PERIOD=%u", u32PWM_PERIOD); );
    MDrv_PWM_Period(LD_HSYNC_USE_PWM_CH, u32PWM_PERIOD-1);    //Hsync
#endif
}

#if 0 // Ursa-PWM

#define PWM_DUTYX100_MAX_NUM            (100*100)
#define PWM_SHIFT_DEGREEX100_MAX_NUM    (360*100)


U16 AlignTo2expo(U16 u16Input)
{
    U16 u16Checkbit = _BIT0;
    //U32 u32breaktime = msAPI_Timer_GetTime0();

    while(u16Input > u16Checkbit)   //Increase return value until >= input
    {
        u16Checkbit<<=1;
        //INFINITE_LOOP_TIME_OUT(u32breaktime,500);       //infinite loop, so break and printf message
    }

    return u16Checkbit;
}

//==========================================================
//Description:
//u8PWMNum(PWM0 ~PWM5)      : 0~5
//ucFrequency     : PWM frequency
//bVsyncEn         : PWM synchronize with Vsync
//Period             : 18bit
//ucDuty             : Duty=  0~100
//shift              : 0~360
//==========================================================
void MDrv_MFC_PWM_waveform_maker(DRV_PWM_CH u8PWMNum, U16 u16FrequencyX10, U16 u16DutyInPercentX100,
                                 U16 u16ShiftIn360DegreeX100, U16 u16Div, U8 SyncRstCnt,
                                 U8 u8DoubleBufferSelect, EnuPwmRstCtrl ePwmRstCtrl, BOOL bPolarity
                                 )
{
    U32 u32Duty, u32Shift, u32PWM_LocalClk;
    U32 u32temp;
    U32 u32Period0,u32Period1;
    BOOL bReg_RESET_EN = 0;
    BOOL bReg_RST_MUX = 0;
    BOOL bReg_NVS_RST_EN = 0;
    //BOOL bReg_NVS_align_en = 0;
    BOOL bReg_LR_flag_rising_pulse = 0;
    U8 u8HSyncResetCount = 0;

    DEBUG_PWM( printf("MDrv_MFC_PWM_waveform_maker(u8PWMNum=%u)\n", u8PWMNum); );
    DEBUG_PWM( printf(" (u16FrequencyX10=%u)\n", u16FrequencyX10););
    DEBUG_PWM( printf(" (SyncRstCnt=%u)\n", SyncRstCnt); );

    if(u16DutyInPercentX100 >= PWM_DUTYX100_MAX_NUM)
    {
        u16DutyInPercentX100 = PWM_DUTYX100_MAX_NUM;
        MDrv_PWM_Set_ForceLevel(u8PWMNum,ENABLE,ENABLE);
    }
    else if(u16DutyInPercentX100 == 0)
    {
        MDrv_PWM_Set_ForceLevel(u8PWMNum,ENABLE,DISABLE);
    }
    else
    {
        MDrv_PWM_Set_ForceLevel(u8PWMNum,DISABLE,DISABLE);
    }

    if(u16ShiftIn360DegreeX100 >= PWM_SHIFT_DEGREEX100_MAX_NUM)
    {
       u16ShiftIn360DegreeX100 %= PWM_SHIFT_DEGREEX100_MAX_NUM;
    }
    //PWM waveform could be reset by display VSYNC or HSYNC to keep the synchronous relation.
    //(1) When RESET_EN = 1 and RST_MUX = 0,
    //      PWM waveform will be reset by incoming VSYNC. As the diagram1 shown below.
    //      => Reset every Vsync
    //(2) When RESET_EN = 1 and RST_MUX = 1 and NVS_RST_EN = 0,
    //      PWM waveform will be reset by incoming HSYNC.  If you need reset every 2 HSYNC, set HS_RST_CNT = 1(start from 0). As the diagram2 shown below.
    //(3) When RESET_EN = 1 and RST_MUX = 1 and NVS_RST_EN = 1,
    //      PWM waveform will be reset by incoming VSYNC. If you need reset every 2 VSYNC, set HS_RST_CNT = 1

    if( ePwmRstCtrl == PWM_RST_CTRL__LRFLAG )
    {
        bReg_RESET_EN = TRUE;
        bReg_RST_MUX = 1; // for NVS
        bReg_NVS_RST_EN = 1;
        bReg_LR_flag_rising_pulse = 1;
    }
    else if( ePwmRstCtrl == PWM_RST_CTRL__VSYNC )
    {
        bReg_RESET_EN = TRUE;


        //bReg_RST_MUX=0 : each Vsync reset
        //bReg_RST_MUX=1 : multiple Vsync reset

        if (SyncRstCnt>0)
        {
            bReg_NVS_RST_EN = 1;
            bReg_RST_MUX = 1; // for NVS
        }
        else
        {
            bReg_RST_MUX = 0; // for V
        }

        u8HSyncResetCount = SyncRstCnt;
    }
    else if( ePwmRstCtrl == PWM_RST_CTRL__HSYNC )// HSync_Rst
    {
        bReg_RESET_EN = TRUE;
        bReg_RST_MUX = 1; // for H sync
        u8HSyncResetCount = SyncRstCnt;
    }
    else // PWM_RST_NONE
    {
        bReg_RESET_EN = FALSE;
        bReg_RST_MUX = 0;
        bReg_LR_flag_rising_pulse = 0;
    }


    u32PWM_LocalClk = (CRYSTAL_CLOCK + u16Div/2)/ u16Div;
    u32Period0 =( u32PWM_LocalClk *10 + (U32)(u16FrequencyX10)/2) / (U32)(u16FrequencyX10);

#if 0//( PANEL_TYPE_SEL == PNL_LTA750HQ01_VX1_FHD_240HZ )
    if( ePwmRstCtrl == PWM_RST_CTRL__NONE )
    {
        u32Period1 = u32Period0;
    }
    else if( (u8PWMNum == LD_SEC75_VSYNC_PWM_CH_SEL) &&  (u16FrequencyX10<1300) )
    {
        u32Period1 = u32Period0 + 0x40;
    }
    else
    {
        u32Period1 = u32Period0*5/4 ;//add 1/4 period for timing change (240->200Hz)
    }
#else
    if(( ePwmRstCtrl != PWM_RST_CTRL__NONE ) /*&&(MDrv_PNL_Get_CurOutputVFreqX10()<u16FrequencyX10) */)
    {
        u32Period1 = u32Period0*5/4 ;//add 1/4 period for timing change (240->200Hz)
    }
    else
    {
        u32Period1 = u32Period0;
    }
#endif

    if (u32Period1 > 0x3FFFF)    //Period overflow protection
    {
        printf("%sWarning: Period is over 0x3FFFF%s\n",KRED,KNRM);
        u32temp = u32Period1 / 0x3FFFF;
        u32temp = AlignTo2expo(u32temp+1);        //Divider should be exponential of 2
        u32Period1 = u32Period1 / (u32temp);    //Period = 1.x * 0x3FFFF => Period/2, Divider*2
        u32Period0 = u32Period0 / (u32temp);    //Period = 1.x * 0x3FFFF => Period/2, Divider*2
        u16Div = u16Div * (u32temp);
    }
    DEBUG_PWM( printf(" u32Period=0x%X\n", u32Period1); );

    u32Shift = (u32Period0 * (U32)u16ShiftIn360DegreeX100 + 36000/2) / 36000;
    u32Duty  = (u32Period0 * (U32)u16DutyInPercentX100 + 10000/2) / 10000 + u32Shift;

    DEBUG_PWM( printf(" u32Shift=0x%X\n", u32Shift); );
    DEBUG_PWM( printf(" u32Duty=0x%X\n", u32Duty); );

#if 1 // Daniel
    u8DoubleBufferSelect=u8DoubleBufferSelect;
    bPolarity=bPolarity;

#else

    MHal_PWM_SWVdbEn(u8PWMNum, 0);

    MHal_PWM_HWDoubleBuffer(u8PWMNum, u8DoubleBufferSelect);

    MHal_PWM_ResetMuxSel(u8PWMNum, bReg_RST_MUX);
    MHal_PWM_NVS_RST_EN(u8PWMNum, bReg_NVS_RST_EN);
    MHal_PWM_NVS_align_en(u8PWMNum, bReg_NVS_align_en);
    MHal_PWM_Set_LR_flag_rising_pulse(u8PWMNum,bReg_LR_flag_rising_pulse); // reg_pwm0_lr_sync_rp

    MHal_PWM_HsyncResetCnt(u8PWMNum, u8HSyncResetCount);
    MHal_PWM_SetPeriod(u8PWMNum, u32Period1-1); //"+4" for longer than one frame no Vsyn rst issue
    //MHal_PWM_SetPeriod(u8PWMNum, u32Period-1 + 0x40); //"+4" for longer than one frame no Vsyn rst issue
    MHal_PWM_SetDuty(u8PWMNum, u32Duty-1);
    MHal_PWM_SetShift(u8PWMNum, u32Shift);
    MHal_PWM_SetDivider(u8PWMNum, u16Div-1);
    MHal_PWM_SetPolarity(u8PWMNum, bPolarity);

    MHal_PWM_SWVdbEn(u8PWMNum, 1);

#endif

}
#endif // Ursa-PWM

#endif // LD_ENABLE

