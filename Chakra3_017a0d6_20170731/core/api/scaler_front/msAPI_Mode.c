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

////////////////////////////////////////////////////////////////////////////////
//
/// @file msAPI_Mode.h
/// This file includes MStar application interface for display mode.
/// @brief API for different modes
/// @author MStar Semiconductor, Inc.
//
////////////////////////////////////////////////////////////////////////////////

#define MSAPI_MODE_C

/******************************************************************************/
/*                    Header Files                                            */
/* ****************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include "Board.h"

// Common Definition
#include "MsCommon.h"


#include "apiXC.h"
#include "apiXC_Sys.h"


#include "drvGlobal.h"
#include "apiPNL.h"
#include "Panel.h"
#include "apiXC_Adc.h"
#include "MApp_PCMode.h"

#include "msAPI_Mode.h"
#include "QualityEx_Default.h"

/********************************************************************************/
/*                     Local                                                  */
/* ******************************************************************************/


/********************************************************************************/
/*                   Local Function Prototypes                  */
/********************************************************************************/

/********************************************************************************/
/*                   Local Type Definitions                  */
/********************************************************************************/

typedef struct
{
    T_MS_NONLINEAR_POINT_16     stPoint0;
    T_MS_NONLINEAR_POINT_16     stPoint1;
    T_MS_NONLINEAR_POINT_16     stPoint2;
    T_MS_NONLINEAR_POINT_16     stPoint3;
}T_MS_NONLINEAR_CURVE_16;  //fix me

/********************************************************************************/
/*                   Functions                      */
/********************************************************************************/

/******************************************************************************/
///-This function will calculate the current scale value
///@param wValue: the current scale value
///@param wMinValue: the min scale value
///@param wMaxValue: the max scale value
///@return :the current scale value in the range 0-100
/******************************************************************************/
U8 GetScale100Value(U16 wValue, U16 wMinValue, U16 wMaxValue)
{
    wMaxValue = wMaxValue - wMinValue;
    wValue = wValue - wMinValue;

    wValue = ((U32) wValue * 100 + (wMaxValue+2) / 2) / wMaxValue;
    if(wValue > 100)
        wValue = 100;

    return wValue;
}

U8 GetScale60Value(U16 wValue, U16 wMinValue, U16 wMaxValue)
{
    wMaxValue = wMaxValue - wMinValue;
    wValue = wValue - wMinValue;

    wValue = ((U32) wValue * 60 + (wMaxValue+2) / 2) / wMaxValue;
    if(wValue > 60)
        wValue = 60;

    return wValue;
}

U8 GetScale64Value(U16 wValue, U16 wMinValue, U16 wMaxValue)
{
    wMaxValue = wMaxValue - wMinValue;
    wValue = wValue - wMinValue;

    wValue = ((U32) wValue * 64 + (wMaxValue+2) / 2) / wMaxValue;
    if(wValue > 64)
        wValue = 64;

    return wValue;
}

/******************************************************************************/
///-This function will calculate the current scale value
//////@param wValue: the current scale value in the range 0-100
///@param wMinValue: the min scale value
///@param wMaxValue: the max scale value
///@return :the current scale value
/******************************************************************************/
U16 N100toReallyValue ( U16 wValue, U16 wMinValue, U16 wMaxValue )
{
    double dfTemp;
    wMaxValue = wMaxValue - wMinValue;
    if(!wValue)
        wValue=wMinValue;
    else
    {
        dfTemp=(double)(((wValue)*wMaxValue)/100.0+wMinValue);
        wValue=((wValue)*wMaxValue)/100+wMinValue;

        if((double)(dfTemp-wValue)>0.4)
            wValue=wValue+1;
    }
    return(U16) wValue;
}

/******************************************************************************/
///-This function will get the scaled value of clock for PC mode
/// @param *pModeSetting: the current mode setting
///-@see MS_PCADC_MODESETTING_TYPE
/// @return U8: scaled value of clock
//*************************************************************************
U8 msAPI_Mode_GetPcClockValue ( SCALER_WIN eWindow, U16 u16Value )
{
        return GetScale100Value( u16Value, MIN_PC_CLOCK(eWindow), MAX_PC_CLOCK(eWindow) );
}

/******************************************************************************/
///-This function will get  value of phase for PC mode
///@param u8value: the scaled value
///@return value of phase for PC mode
//*************************************************************************
U8 msAPI_Mode_GetPcPhaseValue ( U16 u16value )
{
    return GetScale100Value (u16value , MIN_PC_PHASE, MAX_PC_PHASE );
}



//fix me
U16 msAPI_CalNonLinearCurve_BackLight(BYTE AdjustValue, T_MS_NONLINEAR_CURVE_16* stNonLinearCurve )
{
    WORD rValue,ucY0,ucY1,ucX0,ucX1,ucIntercept;
    WORD wDistanceOfY, wDistanceOfX;

    if (AdjustValue < stNonLinearCurve->stPoint1.ucX)
    {
          ucY0 = stNonLinearCurve->stPoint0.ucY;
          ucY1 = stNonLinearCurve->stPoint1.ucY;
          ucX0 = stNonLinearCurve->stPoint0.ucX;
          ucX1 = stNonLinearCurve->stPoint1.ucX;
    }
    else if (AdjustValue < stNonLinearCurve->stPoint2.ucX)
    {
          ucY0 = stNonLinearCurve->stPoint1.ucY;
          ucY1 = stNonLinearCurve->stPoint2.ucY;
          ucX0 = stNonLinearCurve->stPoint1.ucX;
          ucX1 = stNonLinearCurve->stPoint2.ucX;
    }
    else //if (AdjustValue < stNonLinearCurve->stPoint3.ucX)
    {
          ucY0 = stNonLinearCurve->stPoint2.ucY;
          ucY1 = stNonLinearCurve->stPoint3.ucY;
          ucX0 = stNonLinearCurve->stPoint2.ucX;
          ucX1 = stNonLinearCurve->stPoint3.ucX;
    }
//    else
//    {
//          ucY0 = stNonLinearCurve->stPoint3.ucY;
//          ucY1 = stNonLinearCurve->stPoint4.ucY;
//          ucX0 = stNonLinearCurve->stPoint3.ucX;
//          ucX1 = stNonLinearCurve->stPoint4.ucX;
//    }

    if (ucY1 > ucY0)
    {
        wDistanceOfY = ucY1 - ucY0;
        wDistanceOfX = ucX1 - ucX0;
        ucIntercept  = ucY0;
        AdjustValue  = AdjustValue - ucX0;
    }
    else
    {
        wDistanceOfY = ucY0 - ucY1;
        wDistanceOfX = ucX1 - ucX0;
        ucIntercept  = ucY1;
        AdjustValue  = ucX1 - AdjustValue;
    }

  //printf("wDistanceOfY %u\n", wDistanceOfY);
  //printf("wDistanceOfX %u\n", wDistanceOfX);
  //printf("ucIntercept %bu\n", ucIntercept);
  //printf("AdjustValue %bu\n", AdjustValue);

    rValue = ((WORD)wDistanceOfY*AdjustValue/(wDistanceOfX)) + ucIntercept;
    return rValue;
}


//T_MS_NONLINEAR_CURVE code stBacklightCurveTbl =
#if(ENABLE_BACKLIGHT_ADJUST)
static T_MS_NONLINEAR_CURVE_16 code stBacklightCurveTbl =  //fix me
{
    {0,     0x10 },
    {30,    0x48 },
    {60,    0x90 },
    {100,   0xFF },
};
#else
static T_MS_NONLINEAR_CURVE_16 code stBacklightCurveTbl =  //fix me
{
    {0,     0 },
    {0,    0 },
    {0,    0 },
    {0,   0 },
};
#endif
// Move the function here from Panel.c, because it can not use  stBacklightCurveTbl over bank.
U16 msAPI_Mode_PictureBackLightN100toReallyValue ( U8 u8value )
{
#if(!ENABLE_BACKLIGHT_ADJUST)
    stBacklightCurveTbl.stPoint0.ucX = 0;
    stBacklightCurveTbl.stPoint0.ucY = (g_IPanel.DimCtrl(E_APIPNL_DIMMING_MIN));

    stBacklightCurveTbl.stPoint1.ucX = 30;
    stBacklightCurveTbl.stPoint1.ucY = ( ( (U16)( g_IPanel.DimCtrl(E_APIPNL_DIMMING_MAX) - g_IPanel.DimCtrl(E_APIPNL_DIMMING_MIN) ) * 20/100) + g_IPanel.DimCtrl(E_APIPNL_DIMMING_MIN) );

    stBacklightCurveTbl.stPoint2.ucX = 60;
    stBacklightCurveTbl.stPoint2.ucY = ( ( (U16)( g_IPanel.DimCtrl(E_APIPNL_DIMMING_MAX) - g_IPanel.DimCtrl(E_APIPNL_DIMMING_MIN) ) * 60/100) + g_IPanel.DimCtrl(E_APIPNL_DIMMING_MIN) );

    stBacklightCurveTbl.stPoint3.ucX = 100;
    stBacklightCurveTbl.stPoint3.ucY = (g_IPanel.DimCtrl(E_APIPNL_DIMMING_MAX)    );
#endif

    //return msAPI_CalNonLinearCurve(u8value, &stBacklightCurveTbl );
    return msAPI_CalNonLinearCurve_BackLight(u8value, &stBacklightCurveTbl );  //fix me
}

U8 msAPI_CalNonLinearCurve(BYTE AdjustValue, T_MS_NONLINEAR_CURVE* stNonLinearCurve )
{
    //dual direction
    BYTE rValue,ucY0,ucY1,ucX0,ucX1,ucIntercept;
    WORD wDistanceOfY, wDistanceOfX;

    if (AdjustValue < stNonLinearCurve->stPoint1.ucX)
    {
          ucY0 = stNonLinearCurve->stPoint0.ucY;
          ucY1 = stNonLinearCurve->stPoint1.ucY;
          ucX0 = stNonLinearCurve->stPoint0.ucX;
          ucX1 = stNonLinearCurve->stPoint1.ucX;
    }
    else if (AdjustValue < stNonLinearCurve->stPoint2.ucX)
    {
          ucY0 = stNonLinearCurve->stPoint1.ucY;
          ucY1 = stNonLinearCurve->stPoint2.ucY;
          ucX0 = stNonLinearCurve->stPoint1.ucX;
          ucX1 = stNonLinearCurve->stPoint2.ucX;
    }
    else //if (AdjustValue < stNonLinearCurve->stPoint3.ucX)
    {
          ucY0 = stNonLinearCurve->stPoint2.ucY;
          ucY1 = stNonLinearCurve->stPoint3.ucY;
          ucX0 = stNonLinearCurve->stPoint2.ucX;
          ucX1 = stNonLinearCurve->stPoint3.ucX;
    }
//    else
//    {
//          ucY0 = stNonLinearCurve->stPoint3.ucY;
//          ucY1 = stNonLinearCurve->stPoint4.ucY;
//          ucX0 = stNonLinearCurve->stPoint3.ucX;
//          ucX1 = stNonLinearCurve->stPoint4.ucX;
//    }

    if (ucY1 > ucY0)
    {
        wDistanceOfY = ucY1 - ucY0;
        wDistanceOfX = ucX1 - ucX0;
        ucIntercept  = ucY0;
        AdjustValue  = AdjustValue - ucX0;
    }
    else
    {
        wDistanceOfY = ucY0 - ucY1;
        wDistanceOfX = ucX1 - ucX0;
        ucIntercept  = ucY1;
        AdjustValue  = ucX1 - AdjustValue;
    }

 // printf("wDistanceOfY %u\n", wDistanceOfY);
 // printf("wDistanceOfX %u\n", wDistanceOfX);
 // printf("ucIntercept %bu\n", ucIntercept);
 // printf("AdjustValue %bu\n", AdjustValue);

    rValue = ((WORD)wDistanceOfY*AdjustValue/(wDistanceOfX)) + ucIntercept;
    return rValue;
}

U8 GetColorTemperatureScale100Value(U16 wValueFrom, U16 wValueTo, U16 wMinValue, U16 wMaxValue, U8 wOrgScaleValue, BOOLEAN *bIsNeed2ResetValue)
{
    U8 u8ScaleValueFrom = GetScale100Value(wValueFrom,wMinValue, wMaxValue);
    U8 u8ScaleValueTo   = GetScale100Value(wValueTo,wMinValue, wMaxValue);
    *bIsNeed2ResetValue = FALSE;

    if (wValueTo > wValueFrom) //increase
    {
        if ((u8ScaleValueTo - wOrgScaleValue) > 1)
            *bIsNeed2ResetValue = TRUE;
        if (wOrgScaleValue > 99) wOrgScaleValue = 100;
        else wOrgScaleValue++;
    }
    else if (wValueTo < wValueFrom) //decrease
    {
        if ((wOrgScaleValue - u8ScaleValueTo) > 1)
            *bIsNeed2ResetValue = TRUE;
        if (wOrgScaleValue < 1) wOrgScaleValue = 0;
        else wOrgScaleValue--;
    }
    else if (wValueFrom == wValueTo) //boundary coindication
    {
        if ((u8ScaleValueFrom == 0) && (wOrgScaleValue > 0))
        {
            *bIsNeed2ResetValue = TRUE;
            wOrgScaleValue--;
        }
        else if ((u8ScaleValueFrom == 100) && (wOrgScaleValue <100))
        {
            *bIsNeed2ResetValue = TRUE;
            wOrgScaleValue++;
        }
    }
    return wOrgScaleValue;
}
#undef MSAPI_MODE_C
