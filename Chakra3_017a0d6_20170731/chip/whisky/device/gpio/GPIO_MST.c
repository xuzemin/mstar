////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#include "GPIO.h"
#include "Board.h"
#include "hwreg.h"
#include "SysInit.h"
#include "drvGlobal.h"
#include "apiXC.h"

#include "Panel.h"
#include "apiPNL.h"
#include "drvPWM.h"

#include "apiXC_Sys.h"
#include "msAPI_Timer.h"

#include "drvGPIO.h"
#if (!BLOADER)
#include "MApp_GlobalVar.h"
#include "MApp_XC_PQ.h"
#endif

#if (I2C_IO_EXPANDER_TYPE != I2C_IO_EXPANDER_NONE)
#include "EXT_GPIO.C"
#endif

#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"
#include "drvSAR.h"
//****************************************************************************
// Private attributes of this file.
//****************************************************************************

//#define IO_EXPANDER_ADDR                0xFFFF
//#define IO_EXPANDER_SETTING_DATA        0xFF

#define MAX_BACKLIGHT                   100
#define SAR_ADC_CHANNEL_DATA_MASK       0x3F

/******************************************************************************/
/*                                 Global                                     */
/******************************************************************************/
//BOOLEAN g_bIsSoftStartValid = FALSE ;

#if (INPUT_SCART_VIDEO_COUNT >0)//CANAL+
U8 gCANAL_PLUS_SCART_Plug_In;
#endif

/******************************************************************************/
/*                                 Local                                      */
/******************************************************************************/
static  BOOLEAN _bScartChanged=FALSE;


//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------


#define PWM0_SYNC_WITH_VSYNC 0
#define PWM1_SYNC_WITH_VSYNC 0
#define PWM2_SYNC_WITH_VSYNC 0
#define PWM3_SYNC_WITH_VSYNC 0





//-----------------------------------------------------------------------------
void Mst_PwmPortInit( void )
{
    PWM_DbgLv   PWMDbLv = E_PWM_DBGLV_NONE;
    PWM_Result  PWMRet  = E_PWM_FAIL;
    PWM_ChNum   PWMPort;

    if(PWMRet == MDrv_PWM_Init(PWMDbLv))
        printf("PWM initial FAIL  !!!\n");

#if defined(PWM_UNIT_DIV)
    MDrv_PWM_UnitDiv(PWM_UNIT_DIV);
#else
    MDrv_PWM_UnitDiv(0);
#endif

#if defined(PWM0_PERIOD) && defined(INIT_PWM0_DUTY)
    if ( PADS_PWM0_MODE != Unknown_pad_mux )
    {
        PWMPort = E_PWM_CH0;
        MDrv_PWM_Period(PWMPort, PWM0_PERIOD);
        MDrv_PWM_DutyCycle(PWMPort, INIT_PWM0_DUTY);
        MDrv_PWM_Div(PWMPort, 0); //PWM0_DIV //compiling error free -- check later
        MDrv_PWM_Polarity(PWMPort, NON_INVERSE);
#if PWM0_SYNC_WITH_VSYNC
        MDrv_PWM_Vdben(PWMPort, YES);
        MDrv_PWM_ResetEn(PWMPort, YES);
#else
        MDrv_PWM_Dben(PWMPort, YES);
#endif
        MDrv_PWM_Oen(PWMPort, 0);   /* Set 0 for output enable */
    }
#endif

#if defined(PWM1_PERIOD) && defined(INIT_PWM1_DUTY)
    if ( PADS_PWM1_MODE != Unknown_pad_mux )
    {
        PWMPort = E_PWM_CH1;
        MDrv_PWM_Period(PWMPort, PWM1_PERIOD);
        MDrv_PWM_DutyCycle(PWMPort, INIT_PWM1_DUTY);
        MDrv_PWM_Div(PWMPort, 0);
        MDrv_PWM_Polarity(PWMPort, NON_INVERSE);
#if PWM1_SYNC_WITH_VSYNC
        MDrv_PWM_Vdben(PWMPort, YES);
        MDrv_PWM_ResetEn(PWMPort, YES);

#else
        MDrv_PWM_Dben(PWMPort, YES);
#endif
        MDrv_PWM_Oen(PWMPort, 0);    /* Set 0 for output enable */
    }
#endif

#if defined(PWM2_PERIOD) && defined(INIT_PWM2_DUTY)
    if ( PADS_PWM2_MODE != Unknown_pad_mux )
    {
        PWMPort = E_PWM_CH2;
        MDrv_PWM_Period(PWMPort, PWM2_PERIOD);
        MDrv_PWM_DutyCycle(PWMPort, INIT_PWM2_DUTY);
        MDrv_PWM_Div(PWMPort, 0);
        MDrv_PWM_Polarity(PWMPort, NON_INVERSE);
#if PWM2_SYNC_WITH_VSYNC
        MDrv_PWM_Vdben(PWMPort, YES);
        MDrv_PWM_ResetEn(PWMPort, YES);
#else
        MDrv_PWM_Dben(PWMPort, YES);
#endif
        MDrv_PWM_Oen(PWMPort, 0);    /* Set 0 for output enable */
    }
#endif

#if defined(PWM3_PERIOD) && defined(INIT_PWM3_DUTY)
    if ( PADS_PWM3_MODE != Unknown_pad_mux )
    {
        PWMPort = E_PWM_CH3;
        MDrv_PWM_Period(PWMPort, PWM3_PERIOD);
        MDrv_PWM_DutyCycle(PWMPort, INIT_PWM3_DUTY);
        MDrv_PWM_Div(PWMPort, 0);
        MDrv_PWM_Polarity(PWMPort, NON_INVERSE);
#if PWM3_SYNC_WITH_VSYNC
        MDrv_PWM_Vdben(PWMPort, YES);
        MDrv_PWM_ResetEn(PWMPort, YES);
#else
        MDrv_PWM_Dben(PWMPort, YES);
#endif
        MDrv_PWM_Oen(PWMPort, 0);    /* Set 0 for output enable */
    }
#endif
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void msGPIO_Init(void)
{
//     Audio_Amplifier_ON();// // TO Be Decide for de Pop

    Power_On();
    SCART_OUT_ON();

    Mst_PwmPortInit();

    //msPWM_OutputEnable( (PWM0_ENABLE | PWM1_ENABLE | PWM2_ENABLE | PWM3_ENABLE) );

  #if (!BLOADER)
//    MApi_PNL_SetBackLight(BACKLITE_INIT_SETTING);
    //MApi_PNL_SetBackLight(DISABLE);
  #endif


    //===============================
    Panel_VG_HL_CTL_ON();
    Tuner_ON();
    Demodulator_ON();
    LAN_ON();
    //===============================

}

void InitIOExpander(void)
{
#if (I2C_IO_EXPANDER_TYPE != I2C_IO_EXPANDER_NONE)
    MDrv_ExGPIO_Init();
#endif
    msGPIO_Init();
    _bScartChanged=FALSE;

}

BYTE GetSarAdcLevel(U8 u8Channel)
{
    U8 u8SarValue=0;

    #if (KEYPAD_TYPE_SEL != KEYPAD_TYPE_NONE)
    if(msKeypad_Get_ADC_Channel(u8Channel,&u8SarValue)==0)
    {
        return u8SarValue;
    }
    #endif
    return 0;
 }

BYTE GetScart1IDLevel(void)
{
    MDrv_SAR_Adc_SetHSyncCh((SAR_AdcHSyncCh) 1);
    MDrv_SAR_Adc_SetHSyncChEn(ENABLE);
    return GetSarAdcLevel(SCART_ID1_SAR_CHAN);
}

BYTE GetScart2IDLevel(void)
{
    return GetSarAdcLevel(SCART_ID2_SAR_CHAN);
}

// ToDo:
BOOLEAN IsScartRGB(void)
{
    //RGB: 1-3V, CVBS: 0-0.4V
    if((MDrv_ReadByte(H_BK_ADC_ATOP(0x45)) & 0x0F) > 3)//bit[11:8]
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOLEAN IsScart1Connected( void )
{
    return ( GetScart1IDLevel() > SCART_ID_LEVEL_4V );
}
BOOLEAN IsScart2Connected( void )
{
    return ( GetScart2IDLevel() > SCART_ID_LEVEL_4V );
}

#define SCART1_CONNECT   0x01
#define SCART2_CONNECT   0x02

#if (INPUT_SCART_VIDEO_COUNT > 0)
static unsigned char PreScartConnectStatus = 0;
static unsigned char PreScartDisConnectStatus = 0;
#endif

BOOLEAN msAPI_GPIO_IsSourceJustConnected( INPUT_SOURCE_TYPE_t type )
{
#if(INPUT_SCART_VIDEO_COUNT == 0)
    type = type;
#endif

#if (INPUT_SCART_VIDEO_COUNT >= 1)
    if (type == INPUT_SOURCE_SCART)
    {
        if (IsScart1Connected() == TRUE)
        {
            gCANAL_PLUS_SCART_Plug_In=1;//CANAL+
            if (!(PreScartConnectStatus & SCART1_CONNECT))
            {
                PreScartConnectStatus |= SCART1_CONNECT;
                if(_bScartChanged == FALSE)
                    _bScartChanged = TRUE;
                //return TRUE;
            }
                return TRUE;
        }
        else
        {
            PreScartConnectStatus &= ~SCART1_CONNECT;
        }
    }
#endif
#if (INPUT_SCART_VIDEO_COUNT >= 2)
    else if (type == INPUT_SOURCE_SCART2)
    {
        if (IsScart2Connected() == TRUE)
        {
            if (!(PreScartConnectStatus & SCART2_CONNECT))
            {
                PreScartConnectStatus |= SCART2_CONNECT;
                if(_bScartChanged == FALSE)
                    _bScartChanged = TRUE;
                //return TRUE;
            }
            return TRUE;
        }
        else
        {
            PreScartConnectStatus &= ~SCART2_CONNECT;
        }

    }
#endif
    return FALSE;

}

BOOLEAN msAPI_GPIO_IsSourceJustDisConnected( INPUT_SOURCE_TYPE_t type )
{
#if(INPUT_SCART_VIDEO_COUNT == 0)
    type = type;
#endif

#if (INPUT_SCART_VIDEO_COUNT >= 1)
    if (type == INPUT_SOURCE_SCART)
    {
        static U8 _u8Tmp1 = 0;
        U8 _u8Tmp2;

        while(1)
        {
            _u8Tmp2 = IsScart1Connected();
            if (_u8Tmp1 != _u8Tmp2)
            {
                _u8Tmp1 = _u8Tmp2;
                MsOS_DelayTask(200);
            }
            else
                break;
        }

        if (IsScart1Connected() == FALSE)
        {
//            printf("GPIO: disconnect, status=0x%bx \n",PreScartDisConnectStatus);
            if (PreScartDisConnectStatus & SCART1_CONNECT)
            {
                PreScartDisConnectStatus &= ~SCART1_CONNECT;

                if(_bScartChanged == FALSE)
                {
                    _bScartChanged = TRUE;
                }
                //return TRUE;
            }
                gCANAL_PLUS_SCART_Plug_In=0;//CANAL+

                return TRUE;
            }
        else
        {
//            printf("GPIO: connect \n");
            PreScartDisConnectStatus |= SCART1_CONNECT;
        }
    }
#endif
#if (INPUT_SCART_VIDEO_COUNT >= 2)
    else if (type == INPUT_SOURCE_SCART2)
    {
        if (IsScart2Connected() == FALSE)
        {
            if (PreScartDisConnectStatus & SCART2_CONNECT)
            {
                PreScartDisConnectStatus &= ~SCART2_CONNECT;
                if(_bScartChanged == FALSE)
                    _bScartChanged = TRUE;
                //return TRUE;
            }
            return TRUE;
        }
        else
        {
            PreScartDisConnectStatus |= SCART2_CONNECT;
        }

    }
#endif
    return FALSE;

}

void InitGPIO(void)
{
    /* dummy */
}

BOOLEAN IsScartChange(void)
{
    return _bScartChanged;
}

void ResetScartChange(void)
{
    _bScartChanged=FALSE;
}
