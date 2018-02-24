//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
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
#include "MApp_GlobalVar.h"
#include "MApp_XC_PQ.h"


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
BOOLEAN g_bIsSoftStartValid = FALSE ;

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

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void Mst_PwmPortInit( void )
{
    PWM_DbgLv   PWMDbLv = E_PWM_DBGLV_ALL;
    PWM_Result  PWMRet  = E_PWM_FAIL;
    PWM_ChNum   PWMPort;

    if(PWMRet == MDrv_PWM_Init(PWMDbLv))
        printf("PWM initial FAIL!!!\n");

#if defined(PWM_UNIT_DIV)
    MDrv_PWM_UnitDiv(PWM_UNIT_DIV);
#else
    MDrv_PWM_UnitDiv(0);
#endif

#if defined(PWM0_PERIOD) && defined(INIT_PWM0_DUTY)
    if ( !PAD_PWM0_IS_GPIO )
    {
        PWMPort = E_PWM_CH0;
        MDrv_PWM_Oen(PWMPort, 0);   /* Set 0 for output enable */
        MDrv_PWM_Period(PWMPort, PWM0_PERIOD);
        MDrv_PWM_DutyCycle(PWMPort, INIT_PWM0_DUTY);
        MDrv_PWM_Div(PWMPort, 0);
        MDrv_PWM_Polarity(PWMPort, NON_INVERSE);
        MDrv_PWM_Vdben(PWMPort, NO);
        MDrv_PWM_Dben(PWMPort, NO);
    }
#endif

#if defined(PWM1_PERIOD) && defined(INIT_PWM1_DUTY)
    if ( !PAD_PWM1_IS_GPIO )
    {
        PWMPort = E_PWM_CH1;
        MDrv_PWM_Oen(PWMPort, 0);    /* Set 0 for output enable */
        MDrv_PWM_Period(PWMPort, PWM1_PERIOD);
        MDrv_PWM_DutyCycle(PWMPort, INIT_PWM1_DUTY);
        MDrv_PWM_Div(PWMPort, 0);
        MDrv_PWM_Polarity(PWMPort, NON_INVERSE);
        MDrv_PWM_Vdben(PWMPort, NO);
        MDrv_PWM_Dben(PWMPort, NO);
    }
#endif

#if defined(PWM2_PERIOD) && defined(INIT_PWM2_DUTY)
    if ( PIN_PWM2 == PAD_PWM2 ? !PAD_PWM2_IS_GPIO : !PAD_GPIO14_IS_GPIO )
    {
        PWMPort = E_PWM_CH2;
        MDrv_PWM_Oen(PWMPort, 0);    /* Set 0 for output enable */
        MDrv_PWM_Period(PWMPort, PWM2_PERIOD);
        MDrv_PWM_DutyCycle(PWMPort, INIT_PWM2_DUTY);
        MDrv_PWM_Div(PWMPort, 0);
        MDrv_PWM_Polarity(PWMPort, NON_INVERSE);
        MDrv_PWM_Vdben(PWMPort, NO);
        MDrv_PWM_Dben(PWMPort, NO);
    }
#endif

#if defined(PWM3_PERIOD) && defined(INIT_PWM3_DUTY)
    if ( PIN_PWM3 == PAD_PWM3 ? !PAD_PWM3_IS_GPIO : !PAD_GPIO15_IS_GPIO )
    {
        PWMPort = E_PWM_CH3;
        MDrv_PWM_Oen(PWMPort, 0);    /* Set 0 for output enable */
        MDrv_PWM_Period(PWMPort, PWM03_PERIOD);
        MDrv_PWM_DutyCycle(PWMPort, INIT_PWM3_DUTY);
        MDrv_PWM_Div(PWMPort, 0);
        MDrv_PWM_Polarity(PWMPort, NON_INVERSE);
        MDrv_PWM_Vdben(PWMPort, NO);
        MDrv_PWM_Dben(PWMPort, NO);
    }
#endif
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void msGPIO_Init()
{

//     Audio_Amplifier_ON();// // TO Be Decide for de Pop

    Power_On();
    SCART_OUT_ON();

    Mst_PwmPortInit();

    //msPWM_OutputEnable( (PWM0_ENABLE | PWM1_ENABLE | PWM2_ENABLE | PWM3_ENABLE) );
//    MApi_PNL_SetBackLight(BACKLITE_INIT_SETTING);
    //MApi_PNL_SetBackLight(DISABLE);
    //CUS03 No Use
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
  #if(MS_BOARD_TYPE_SEL == BD_MST214D_D01A_S_MILAN)
    MDrv_SAR_Kpd_MMIO_Init();
    MDrv_SAR_Adc_SetHSyncCh(E_SAR_ADC_HSYNC_CH1);
    MDrv_SAR_Adc_SetHSyncChEn(ENABLE);
  #endif

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
