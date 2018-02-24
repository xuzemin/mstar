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

#define MAPP_KTV_MAIN_C

/******************************************************************************/
/*                 Header Files                                               */
/* ****************************************************************************/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "datatype.h"
#include "debug.h"

#ifdef ENABLE_KTV
#include "MApp_Exit.h"
#include "MApp_Key.h"
#include "MApp_UiMenuDef.h"
#include "MApp_ZUI_Main.h"
#include "MApp_KTV_Main.h"
#include "MApp_KTV.h"
#include "MApp_KTV_Lyric.h"
#include "MApp_APEngine.h"
#include "msAPI_APEngine.h"
#include "IOUtil.h"
#include "BinInfo.h"
#include "drvCPU.h"
#include "apiAUDIO.h"

///////////////////////////////////////////////////////////
#define UI_DBG(x)   x

static enumKTVFlags _eKTVFlag=E_KTV_FLAG_NONE;
static U8           _u8CurrentDriveIdx = 0;

//////////////////////////////////////////////////////////
static void _MApp_KTV_Main_Init(void)
{
    if(!(_eKTVFlag&E_KTV_FLAG_INITED))
    {
        if(MApp_KTV_InitializeUsbDevice() == E_KTV_RET_OK)
        {
            if(MApp_KTV_ConnectDrive(_u8CurrentDriveIdx) == E_KTV_RET_OK)
            {
                _eKTVFlag |= E_KTV_FLAG_DRIVE_CONNECT_OK;
                UI_DBG(printf("connect drive %bu OK ^_^\n", _u8CurrentDriveIdx));
            }
        }
        //MApp_APEngine_Start();
        MApp_APEngine_RegisterByID(BIN_ID_CODE_AEON_KTV, NONE_HANDLE, ((BEON_MEM_MEMORY_TYPE & MIU1) ? (BEON_MEM_ADR | MIU_INTERVAL) : ( BEON_MEM_ADR)), BEON_MEM_LEN);
        //msAPI_APEngine_AppRunByBinID(BIN_ID_CODE_AEON_KTV, ((BEON_MEM_MEMORY_TYPE & MIU1) ? (BEON_MEM_ADR | MIU_INTERVAL) : ( BEON_MEM_ADR)), BEON_MEM_LEN);
        MApi_AUDIO_SetKTVSoundCode(TRUE);
        MDrv_WriteByteMask(0x2CE6,0x06,0x07);//set mic mix gain to +12db , need control by drv lately
        _eKTVFlag |= E_KTV_FLAG_INITED;
    }
    enKTVLyricState = STATE_KTV_LYRIC_INIT;
    eKTVLoadFileAttribute = (enumKTVLoadFileAttribute)0;
    bServerError = FALSE;
    bShowErrorInfo = FALSE;
}

static void _MApp_KTV_Switch2KTV(void)
{
    //add switch KTV AP code in here
    if(_eKTVFlag & E_KTV_FLAG_INITED)
    {
        UI_DBG(printf("\n\n\n*******************KTV has inited\n"));
        _eKTVFlag = E_KTV_FLAG_INITED;
        if(MApp_KTV_ConnectDrive(_u8CurrentDriveIdx) == E_KTV_RET_OK)
        {
            _eKTVFlag |= E_KTV_FLAG_DRIVE_CONNECT_OK;
            UI_DBG(printf("connect drive %bu OK ^_^\n", _u8CurrentDriveIdx));
        }
    }
    else
    {
        UI_DBG(printf("\n\n\n*******************KTV_Init\n"));
        _MApp_KTV_Main_Init();
    }
    enKTVState=STATE_KTV_INIT;
}

EN_RET MApp_KTV_Main(void)
{
    EN_RET enRetVal =EXIT_NULL;

    //if (enKTVState != STATE_KTV_WAIT)
    //    printf("\nMS:%bx ", enKTVState);

    switch(enKTVState)
    {
        case STATE_KTV_INIT:
            MApp_ZUI_ACT_StartupOSD(E_OSD_KTV);
            _MApp_KTV_Switch2KTV();
            enKTVState = STATE_KTV_WAIT;
            break;

        case STATE_KTV_WAIT:
            MApp_ZUI_ProcessKey(u8KeyCode);
            u8KeyCode = KEY_NULL;
            break;

        case STATE_KTV_CLEAN_UP:
            MApp_ZUI_ACT_ShutdownOSD();
            enKTVState = STATE_KTV_INIT;
            enRetVal =EXIT_CLOSE;
            break;

        case STATE_KTV_GOTO_STANDBY:
            MApp_ZUI_ACT_ShutdownOSD();
            u8KeyCode = KEY_POWER;
            enRetVal =EXIT_GOTO_STANDBY;
            break;

        case STATE_KTV_GOTO_MENU:
            MApp_ZUI_ACT_ShutdownOSD();
            enKTVState = STATE_KTV_RETURN_FROM_MENU;
            enRetVal = EXIT_KTV_TRAN_MENU;
            break;
        case STATE_KTV_GOTO_INPUTSOURCE:
            MApp_ZUI_ACT_ShutdownOSD();
            enKTVState = STATE_KTV_RETURN_FROM_MENU;
            enRetVal = EXIT_GOTO_INPUTSOURCE;
            break;
        case STATE_KTV_RETURN_FROM_MENU:
            enKTVState = STATE_KTV_WAIT;
            MApp_ZUI_ACT_StartupOSD(E_OSD_KTV);
            break;
        default:
            enKTVState = STATE_KTV_WAIT;
            break;
    }
    return enRetVal;
}

void MApp_KTV_Main_Exit(void)
{
#if defined(MIPS_CHAKRA) || defined(__AEONR2__)
    MDrv_COPRO_Disable();
#else
    MDrv_COPRO_Disable();
#endif
    MApi_AUDIO_SetKTVSoundCode(FALSE);
    _eKTVFlag = E_KTV_FLAG_NONE;
    enKTVState = STATE_KTV_INIT;
}

#endif
#undef MAPP_KTV_MAIN_C

