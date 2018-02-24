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

#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include "drvPQ.h"
#include "MApp_InputSource.h"
#include "MApp_SaveData.h"
#include "MApp_Func_Inputsource.h"
#include "MApp_PVR.h"
#include "MApp_UiPvr.h"
#include "MApp_ZUI_EventNotify.h"

#if ENABLE_DMP
#include "MApp_DMP_Main.h"
#endif
#if ENABLE_PIP
#include "MApp_PIP.h"
#endif
#include "msAPI_Tuner.h"

void MApp_Function_InputSourceSwitch( E_UI_INPUT_SOURCE source_type )
{
#if (ENABLE_PIP)
    //If sub window is opened, close SUB_WINDOW.
    if(IsPIPSupported() && UI_INPUT_SOURCE_TYPE != source_type )
    {
        //INPUT_SOURCE_TYPE_t enSrc = MApp_InputSource_GetInputSourceType(source_type);
        //E_UI_INPUT_SOURCE enUISrc = MApp_InputSource_GetUIInputSourceType(MApp_InputSource_PIP_Get1stCompatibleSrc(enSrc));
        stGenSetting.g_stPipSetting.enPipMode = EN_PIP_MODE_OFF;
        if(stGenSetting.g_stPipSetting.enPipSoundSrc!=EN_PIP_SOUND_SRC_MAIN)
        {
            stGenSetting.g_stPipSetting.enPipSoundSrc=EN_PIP_SOUND_SRC_MAIN;
        }
        //stGenSetting.g_stPipSetting.enSubInputSourceType = enUISrc;
        if(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW) != INPUT_SOURCE_NONE)
        {
            UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_NONE;
            MApp_InputSource_ChangeInputSource(SUB_WINDOW);
        }
        UI_SUB_INPUT_SOURCE_TYPE = MApp_InputSource_GetUIInputSourceType(MApp_InputSource_PIP_Get1stCompatibleSrc(MApp_InputSource_GetInputSourceType(source_type)));
    }
#endif

#if ENABLE_PVR
    if( (UI_INPUT_SOURCE_TYPE != source_type)
//       &&( (UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_DTV)
       &&( MApp_InputSrc_Is_UiInputSrcTypeDtv(UI_INPUT_SOURCE_TYPE) )
      )
    {
        if( MApp_PVR_IsRecording() )
        {
            MApp_InputSource_RecordSource(source_type);
            MApp_Ui_InputSourcePage_Notify(EN_INPUT_SOURCE_PAGE_NOTIFY_PVR_SOURCE_CHANGE_CHECK_PAGE , 0, 0);
            return;
        }
    }
#endif

#if 0//ENABLE_DVBC
    #if DVB_T_C_DIFF_DB
    #else
        if((UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_CADTV)&&
           (source_type == UI_INPUT_SOURCE_DTV))
        {
            return;
        }
    #endif
#endif

        //switch input source from TV/DTV to non-TV/DTV
        MApp_InputSource_RecordSource(UI_INPUT_SOURCE_TYPE);

        //UI_INPUT_SOURCE_TYPE = source_type;
        MApp_InputSrc_Set_UiInputSrcType(source_type);

        MApp_InputSource_ChangeInputSource(MAIN_WINDOW);
}

FUNC_INPUT_SOURCE_PAGE_STATUS MApp_FuncExec_InputSourcePage(FUNC_INPUT_SOURCE_PAGE_TYPE func, U8 para1, U8 * p_para2)
{
    p_para2 = p_para2;
    FUNC_INPUT_SOURCE_PAGE_STATUS enResult = EN_FUNC_INPUTSOURCE_STATUS_FAIL;

    switch(func)
    {
        case EN_FUNC_INPUTSOURCE_SOURCE:
            MApp_Function_InputSourceSwitch((E_UI_INPUT_SOURCE)para1);
            enResult = EN_FUNC_INPUTSOURCE_STATUS_OK;
            break;

        case EN_FUNC_INPUTSOURCE_STORE_PQ:
            MDrv_PQ_StoreCurrentValue();
            enResult = EN_FUNC_INPUTSOURCE_STATUS_OK;
            break;

        case EN_FUNC_INPUTSOURCE_SAVE_SYS_SETTING:
            MApp_SaveSysSetting();
            enResult = EN_FUNC_INPUTSOURCE_STATUS_OK;
            break;

#if ENABLE_SBTVD_ATV_SYSTEM
        case EN_FUNC_INPUTSOURCE_CHECK_ANTENNA:
            if(IS_SBTVD_APP && UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_ATV)
            {
                if(msAPI_ATV_GetCurrentAntenna() == ANT_AIR)
                    enResult = EN_FUNC_INPUTSOURCE_STATUS_OK;
            }
            break;
#endif

#if ENABLE_PVR
        case EN_FUNC_INPUTSOURCE_CHECK_PVR_RECORDING:
            if(MApp_PVR_IsRecording())
                enResult = EN_FUNC_INPUTSOURCE_STATUS_OK;
            break;

        case EN_FUNC_INPUTSOURCE_STOP_PVR:
            if( MApp_PVR_IsPlaybacking())
                MApp_UiPvr_PlaybackStop();

            if( MApp_PVR_IsRecording() )
                MApp_UiPvr_RecordStop();
            break;
#endif

#if ENABLE_DVBC
        case EN_FUNC_INPUTSOURCE_CHECK_DVBC:
            if ((EN_DVB_TYPE)stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType == EN_DVB_C_TYPE)
                enResult = EN_FUNC_INPUTSOURCE_STATUS_OK;
            break;
#endif

        default:
            break;
    }

    return enResult;

}

