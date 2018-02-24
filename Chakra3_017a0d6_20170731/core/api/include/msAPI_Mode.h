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
// (MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef MSAPI_MODE_H
#define MSAPI_MODE_H


#include "datatype.h"
#include "Board.h"
#include "msAPI_Global.h"
#include "apiXC_PCMonitor.h"

/********************************************************************************/
/*       Macro                                                                  */
/* ******************************************************************************/


/********************************************************************************/
/*       Enums                                                                  */
/* ******************************************************************************/

#ifdef MSAPI_MODE_C
    #define INTERFACE
#else
    #define INTERFACE extern
#endif


typedef struct
{
    BYTE ucX;
    BYTE ucY;
}T_MS_NONLINEAR_POINT;

typedef struct
{
    U16 ucX;
    U16 ucY;
}T_MS_NONLINEAR_POINT_16;//fix me

typedef struct
{
    T_MS_NONLINEAR_POINT stPoint0;
    T_MS_NONLINEAR_POINT stPoint1;
    T_MS_NONLINEAR_POINT stPoint2;
    T_MS_NONLINEAR_POINT stPoint3;
    //T_MS_NONLINEAR_POINT stPoint4;
}T_MS_NONLINEAR_CURVE;

typedef enum{
    BRIGHTNESS_R,
    BRIGHTNESS_G,
    BRIGHTNESS_B
}EN_BRIGHTNESS_TYPE;

/********************************************************************************/
/*                   Function Prototypes                     */
/********************************************************************************/
INTERFACE U8 GetScale100Value(U16 wValue, U16 wMinValue, U16 wMaxValue);
INTERFACE U16 N100toReallyValue ( U16 wValue, U16 wMinValue, U16 wMaxValue );

INTERFACE U8 msAPI_Mode_GetPcClockValue ( SCALER_WIN eWindow,U16 u16Value );
INTERFACE U8 msAPI_Mode_GetPcPhaseValue ( U16 u16value );

INTERFACE U8 GetColorTemperatureScale100Value(U16 wValueFrom, U16 wValueTo, U16 wMinValue, U16 wMaxValue, U8 wOrgScaleValue, BOOLEAN *bIsNeed2ResetValue);


INTERFACE U8 msAPI_CalNonLinearCurve(BYTE AdjustValue, T_MS_NONLINEAR_CURVE* stNonLinearCurve );


INTERFACE U8 GetScale100Value(U16 wValue, U16 wMinValue, U16 wMaxValue);
INTERFACE U8 GetScale60Value(U16 wValue, U16 wMinValue, U16 wMaxValue);
INTERFACE U8 GetScale64Value(U16 wValue, U16 wMinValue, U16 wMaxValue);

#define StandardModeHTotal(eWindow)      ((U16)g_PcadcModeSetting[eWindow].u16DefaultHTotal)
#define HTOTAL_ADJUST_DELTA(eWindow)     (((U32)g_PcadcModeSetting[eWindow].u16DefaultHTotal-MApp_PCMode_Get_HResolution(eWindow,TRUE))*95/100)
#define MIN_PC_CLOCK(eWindow)            (StandardModeHTotal(eWindow) - MIN(30, (HTOTAL_ADJUST_DELTA(eWindow)/2) ) )
#define MAX_PC_CLOCK(eWindow)            (StandardModeHTotal(eWindow) + MIN(30, (HTOTAL_ADJUST_DELTA(eWindow)/2) ) )

#define MIN_PC_PHASE            (0)
#define MAX_PC_PHASE            (MApi_XC_ADC_GetPhaseRange() - 1)

#define MIN_PC_H_START(eWindow)          (g_PcadcModeSetting[eWindow].u16DefaultHStart-(g_PcadcModeSetting[eWindow].u16DefaultHStart/2))
#define MAX_PC_H_START(eWindow)          (g_PcadcModeSetting[eWindow].u16DefaultHStart+(g_PcadcModeSetting[eWindow].u16DefaultHStart/2))

#define MIN_PC_V_START          (1)
#define MAX_PC_V_START(eWindow)          (g_PcadcModeSetting[eWindow].u16DefaultVStart*2 - MIN_PC_V_START)

#define DEFAULT_USER_RGB        128
#define MAX_USER_RGB            (DEFAULT_USER_RGB + 20)
#define MIN_USER_RGB            (DEFAULT_USER_RGB - 20)

#define SUB_BRIGHTNESS_MIN      (SUB_BRIGHTNESS_BYPASS - 50)
#define SUB_BRIGHTNESS_BYPASS   128
#define SUB_BRIGHTNESS_MAX      (SUB_BRIGHTNESS_BYPASS + 50)

#define SUB_CONTRAST_MIN        (SUB_CONTRAST_BYPASS - 50)
#define SUB_CONTRAST_BYPASS     128
#define SUB_CONTRAST_MAX        (SUB_CONTRAST_BYPASS + 50)

#define BRIGHTNESS_BYPASS       128
// SATURN end
#undef INTERFACE

#endif /* MSAPI_MODE_H */


