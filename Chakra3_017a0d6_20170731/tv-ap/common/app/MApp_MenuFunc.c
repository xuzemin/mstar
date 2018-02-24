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
// (MStar Confidential Information) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define MAPP_MENUFUNC_COMMON_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Board.h"

#include "drvAVD.h"

#include "msAPI_CPU.h"
#include "msAPI_DrvInit.h"

#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalFunction.h"
#include "MApp_MultiTasks.h"
#include "MApp_Sleep.h"

#include "mapp_videoplayer.h"
#if MHEG5_ENABLE
#include "MApp_MHEG5_Main.h"
#endif

U8 MApp_MenuFunc_Setup_TimezoneIndex_Get(void)
{
    return GET_TIMEZONE_MENU_LANGUAGE_DTG();
}

void MApp_MenuFunc_Setup_TimezoneIndex_Adjust(U8 u8Index)
{
    SET_TIME_MENU_ZONE((EN_MENU_TIMEZONE)u8Index);
#if ENABLE_DVB
    MApp_SI_SetTimeZone(MApp_GetSITimeZone(stGenSetting.g_Time.enTimeZone));
    MApp_SI_SetClockTimeZone(MApp_GetSIClockTimeZone(stGenSetting.g_Time.en_Clock_TimeZone));
    MApp_SI_Update_Time(MApp_GetAutoSystemTimeFlag());
#endif
    MApp_Time_SetOnTime();
}

U8 MApp_MenuFunc_Setup_BlockSysLockMode_Get(void)
{
    return stGenSetting.g_BlockSysSetting.u8BlockSysLockMode;
}

void MApp_MenuFunc_Setup_BlockSysLockMode_Set(U8 u8BlockSysLockMode)
{
    stGenSetting.g_BlockSysSetting.u8BlockSysLockMode = u8BlockSysLockMode;
}

U16 MApp_MenuFunc_Setup_BlockSysPassWord_Get(void)
{
    return stGenSetting.g_BlockSysSetting.u16BlockSysPassword;
}

void MApp_MenuFunc_Setup_BlockSysPassWord_Set(U16 u16Password)
{
    stGenSetting.g_BlockSysSetting.u16BlockSysPassword = u16Password;
}


U8 MApp_MenuFunc_Setup_BlockSysEnterLockPage_Get(void)
{
    return stGenSetting.g_BlockSysSetting.u8EnterLockPage;
}

void MApp_MenuFunc_Setup_BlockSysEnterLockPage_Set(U8 bEnterLockPage)
{
    stGenSetting.g_BlockSysSetting.u8EnterLockPage = bEnterLockPage;
}



void MApp_MenuFunc_Setup_SubLanguage_Toggle(void)
{
    stGenSetting.g_SysSetting.fSUBLANG_FLAG = !stGenSetting.g_SysSetting.fSUBLANG_FLAG;

}

U8 MApp_MenuFunc_Setup_SubLanguage_Get(void)
{
    return stGenSetting.g_SysSetting.fSUBLANG_FLAG;
}

#if ENABLE_DRM

U8 MApp_MenuFunc_Setup_IsDRMActivatedStatus_Get(void)
{
    return stGenSetting.g_VDplayerDRMInfo.bIsActivated;
}

U8 MApp_MenuFunc_Setup_IsDRMDeActivatedStatus_Get(void)
{
    return stGenSetting.g_VDplayerDRMInfo.bIsDeactivated;
}
#endif

void MApp_MenuFunc_Setup_DRMDeactive(void)
{
#if MHEG5_ENABLE
    if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
    {
        MApi_MHEG5_Disable(EN_MHEG5_DM_DISABLE_WITH_AUTOBOOT_LATER);
    }
#endif

  #if ENABLE_DRM
    MApp_VDPlayer_Deactivate();
  #endif

#if MHEG5_ENABLE
    if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
    {
        msAPI_COPRO_Disable();

        // Initial Beon for DTV
        msAPI_MHEG5_Bean_Init();
    }
#endif
}

void MApp_MenuFunc_Setup_DIVXConfirm(void)
{
#if MHEG5_ENABLE
    if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
    {
        MApi_MHEG5_Disable(EN_MHEG5_DM_DISABLE_WITH_AUTOBOOT_LATER);
    }
#endif

#if ENABLE_DRM
    MDrv_AVD_Set3dComb(DISABLE);
    MApp_VDPlayer_CheckAndGenDRMData();
    if (IsATVInUse()||IsAVInUse())
    {
        MDrv_AVD_Set3dComb(ENABLE);
    }
#endif

#if MHEG5_ENABLE
    if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
    {
        msAPI_COPRO_Disable();

        // Initial Beon for DTV
        msAPI_MHEG5_Bean_Init();
    }
#endif
}

#if (ENABLE_3D_PROCESS)
EN_3D_TYPE MApp_MenuFunc_Setup_3DType_Get(void)
{
    return DB_3D_SETTING.en3DType;
}
#endif

EN_MS_NR MApp_MenuFunc_Video_NOISE_REDUCTION_Get(void)
{
    return ST_VIDEO.eNRMode.eNR;
}

EN_MS_MPEG_NR MApp_MenuFunc_Get_MPEG_NOISE_REDUCTION_Setting(void)
{
    return ST_VIDEO.eNRMode.eMPEG_NR;
}


#if(ENABLE_SCART_SVIDEO)
#if 0
void MApp_MenuFunc_Setup_AdjustScartSource(EN_SCART_SELECT u8ScartInputSource)
{
    printf("\r\n Scart Source Select =%d", u8ScartInputSource);
    stGenSetting.g_SysSetting.fSCARTInputSel = u8ScartInputSource;
    MApp_InputSource_SwitchSource( UI_INPUT_SOURCE_SCART, MAIN_WINDOW );

}
#endif
#endif

//******************************************************************************



