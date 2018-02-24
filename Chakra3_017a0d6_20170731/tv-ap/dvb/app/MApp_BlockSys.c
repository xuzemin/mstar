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

#define MAPP_BLOCKSYS_C

#include <string.h>
#include "Board.h"
#include "datatype.h"

// Common Definition
#include "MsCommon.h"

#include "apiXC.h"
#include "apiXC_Adc.h"
#include "apiXC_Sys.h"
#include "msAPI_DTVSystem.h"
#include "msAPI_ATVSystem.h"
#include "msAPI_audio.h"

#include "MApp_Key.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalVar.h"
#include "MApp_Audio.h"
#include "MApp_UiMenuDef.h"
#include "MApp_TV.h"// For parental block
#include "MApp_ChannelChange.h"// For parental block
#include "MApp_BlockSys.h"
#include "MApp_ATVProc.h"

#define BLOCKSYSDBG(x)  //x
/********************************************************************************/
/*                    Local                                                     */
/********************************************************************************/
#define BLOCKSYS_MONITOR_PERIOD 100 //ms
static BOOLEAN fParentalControlStatus;
extern BOOLEAN bStopMonitorBlock;
//ZUI: unused...#if BLOCK_SYSTEM
#if MHEG5_ENABLE
MEMBER_SERVICETYPE _eCurServiceType=E_SERVICETYPE_INVALID;
WORD _wCurPosition=0;
#endif
void MApp_BlockSys_SetBlockStatus(BOOLEAN bBlockSysBlockStatus)
{
#if (!ENABLE_DTV)
    UNUSED(bBlockSysBlockStatus);
#else
    if(bBlockSysBlockStatus)
    { //block
        BLOCKSYSDBG(printf("BLOCKSY>> Blcok!\n"));
        if( IsSrcTypeDTV( SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW) )
		#if ENBALE_PARENTALRATING_MM
		||IsSrcTypeStorage(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
		#endif
		)
        {
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYVCHIP_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_RATING, ENABLE, NULL, MAIN_WINDOW);
        }
        else
        {
            //TO DO : sub window
        }

    }
    else
    {
        //unblock
        BLOCKSYSDBG(printf("BLOCKSY>> UnBlcok!\n"));
        if( IsSrcTypeDTV( SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW) )
        #if ENBALE_PARENTALRATING_MM
		||IsSrcTypeStorage(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
		#endif
		)
        {
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYVCHIP_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_RATING, DISABLE, NULL, MAIN_WINDOW);
        }
        else
        {
            //TO DO : sub window
        }
    }
#endif
}

void MApp_ParentalControl_SetBlockStatus(BOOLEAN bBlockSysBlockStatus)
{
#if (!ENABLE_DTV)
    UNUSED(bBlockSysBlockStatus);
#else
    fParentalControlStatus=bBlockSysBlockStatus;
    MApp_BlockSys_SetBlockStatus(bBlockSysBlockStatus);
#endif
}
BOOLEAN MApp_ParentalControl_GetBlockStatus(void)
{
    return fParentalControlStatus;
}

void MApp_CheckBlockProgramme(void)
{
#if ENABLE_DVB
    MEMBER_SERVICETYPE bServiceType;
    WORD wCurPosition;
#endif
    BYTE cCurrentProgramNumber;

    if(!stGenSetting.g_BlockSysSetting.u8BlockSysLockMode)
        return;

#if ENABLE_DVB
    if( IsDTVInUse() )
    {
    #if MHEG5_ENABLE
        if(_eCurServiceType != E_SERVICETYPE_INVALID)
        {
            bServiceType=_eCurServiceType;
            wCurPosition=_wCurPosition;
        }
        else
    #endif
        {
            bServiceType = msAPI_CM_GetCurrentServiceType();
            wCurPosition = msAPI_CM_GetCurrentPosition(bServiceType);
        }

        bIsBlocked = msAPI_CM_GetProgramAttribute(bServiceType, wCurPosition, E_ATTRIBUTE_IS_LOCKED);
    }
    else
#endif
    if( IsATVInUse() )
    {
        cCurrentProgramNumber = msAPI_ATV_GetCurrentProgramNumber();
        bIsBlocked = msAPI_ATV_IsProgramLocked((BYTE)cCurrentProgramNumber);
    }
    else
    {
        msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BLOCK, DISABLE, NULL, MAIN_WINDOW);
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYBLOCK_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
        bIsBlocked = FALSE;
    }

    if (FALSE ==bStopMonitorBlock)
        MApp_EnableBlockProgramme(bIsBlocked);
}

void MApp_EnableBlockProgramme(BOOLEAN bEnableBlock)
{
#if (!ENABLE_DTV)
    UNUSED(bEnableBlock);
#else
    if(bEnableBlock == TRUE)
    {
        if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) || IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
        {
            msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BLOCK, ENABLE, NULL, MAIN_WINDOW);
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYBLOCK_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            msAPI_Scaler_SetCVBSMute(ENABLE, E_VE_MUTE_GEN,SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),OUTPUT_CVBS1);
        }
        else
        {
            //TO DO : for sub window
        }
    }
    else
    {
        if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) || IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
        {
            msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BLOCK, DISABLE, NULL, MAIN_WINDOW);
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYBLOCK_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            msAPI_Scaler_SetCVBSMute(DISABLE, E_VE_MUTE_GEN,SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),OUTPUT_CVBS1);
        }
        else
        {
            //TO DO : for sub window
        }
    }
#endif
}

#if MHEG5_ENABLE
void MApp_BlockSysSetCurrentService(MEMBER_SERVICETYPE eServiceType, WORD wPosition)
{
     _eCurServiceType=eServiceType;
    _wCurPosition=wPosition;
}
#endif
//ZUI: unused...#endif

