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

#define _MAPP_KEYTOSPEECH_C_

////////////////////////////////////////////////////////////////////////////////
/// @file MApp_TTSControlHandler.c
/// @author MStar Semiconductor Inc.
/// @brief Idle mode handler for APP layer
////////////////////////////////////////////////////////////////////////////////

/******************************************************************************/
/*                            Header Files                                    */
/******************************************************************************/
#include "Board.h"

#if ENABLE_KEY_TO_SPEECH
#include <string.h>
#include "drvSOUND.h"
#include "drvAUDIO_if.h"
#include "msAPI_Timer.h"
#include "msAPI_audio.h"
#include "msAPI_Memory.h"
#include "msAPI_MIU.h"
#include "MApp_KeyToSpeech.h"

#define KTS_MUTE_BGM ENABLE
#define KTS_AUDIO_BUFFER_MAXIMUM_SIZE 0x20000

//==========================================================================
U8* g_pu8KTS_Start_Addr = NULL;
U32 g_u32KTS_Len = 0;

typedef enum
{
    EN_KTS_ISRUNNING,
    EN_KTS_DONE
} EN_KTS_STATUS;
EN_KTS_STATUS KTS_Status;

BOOLEAN MApp_KTS_IsEnable(void)
{
    return stGenSetting.g_SysSetting.bKTSOn;
}

void MApp_KTS_Setup_Audio(BOOLEAN bMuteBGM)
{
    if(bMuteBGM)
    {
        // for aviod pop noise
        MApi_AUDIO_SetMixModeMute(E_AUDIO_INFO_GAME_IN, PCM_VOL, TRUE);//TTS path mute
        msAPI_Timer_Delayms(1);
        MApi_AUDIO_SetMixModeMute(E_AUDIO_INFO_GAME_IN, PCM_VOL, FALSE);//TTS path unmute
    #if KTS_MUTE_BGM
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_TTS_Background_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
        //MApi_AUDIO_SetMixModeMute(E_AUDIO_INFO_GAME_IN, GAME1_VOL, TRUE);
    #else
        //MApi_AUDIO_SetMixModeVolume(E_AUDIO_INFO_GAME_IN, GAME1_VOL, 0x20, 0);
    #endif
    }
    else
    {
    #if KTS_MUTE_BGM
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_TTS_Background_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
        //MApi_AUDIO_SetMixModeMute(E_AUDIO_INFO_GAME_IN, GAME1_VOL, FALSE);
    #else
        //MApi_AUDIO_SetMixModeVolume(E_AUDIO_INFO_GAME_IN, GAME1_VOL, u8DBVal, 0);
    #endif
    }
}
BOOLEAN MApp_KTS_IsAudioFinished(void)
{
    if(MDrv_SND_GetParam(Sound_GET_PARAM_SIMPLE_TTS_Status, 0) == 0)
        return TRUE;
    else
        return FALSE;
}

void MApp_KTS_FreeMemory(void)
{
    if( g_pu8KTS_Start_Addr )
    {
        msAPI_Memory_Free( g_pu8KTS_Start_Addr, BUF_ID_KTS);
        MApp_KTS_Setup_Audio(FALSE);
        KTS_Status = EN_KTS_DONE;
        g_pu8KTS_Start_Addr = NULL;
    }
}
U16 MApp_KTS_Resource_Mapping(EN_KTS_ITEMS enItem)
{
    U16 u16BinID;
    switch(enItem)
    {
        case EN_KTS_POWER_ON:
            u16BinID = BIN_ID_KTS_POWER_ON;
        break;
        case EN_KTS_POWER_OFF:
            u16BinID = BIN_ID_KTS_POWER_OFF;
        break;
        case EN_KTS_CHANNEL_UP:
            u16BinID = BIN_ID_KTS_CHANNEL_UP;
        break;
        case EN_KTS_CHANNEL_DOWN:
            u16BinID = BIN_ID_KTS_CHANNEL_DOWN;
        break;
        case EN_KTS_VOLUME_UP:
            u16BinID = BIN_ID_KTS_VOLUME_UP;
        break;
        case EN_KTS_VOLUME_DOWN:
            u16BinID = BIN_ID_KTS_VOLUME_DOWN;
        break;
        case EN_KTS_MUTE_ON:
            u16BinID = BIN_ID_KTS_MUTE_ON;
        break;
        case EN_KTS_MUTE_OFF:
            u16BinID = BIN_ID_KTS_MUTE_OFF;
        break;
        case EN_KTS_MENU:
            u16BinID = BIN_ID_KTS_MENU;
        break;
        case EN_KTS_SOURCE:
            u16BinID = BIN_ID_KTS_SOURCE;
        break;
        default:
            u16BinID = BIN_ID_KTS_POWER_ON;
        break;
    }
    return u16BinID;
}
void MApp_KTS_Stop(void)
{
    if( g_pu8KTS_Start_Addr)
    {
        MDrv_SND_DMA_SetPara((MS_U32)g_pu8KTS_Start_Addr, 0);
    }
}

void MApp_KTS_Say(EN_KTS_ITEMS enItem)
{
    BOOLEAN bResult;
    BININFO BinInfo;
    U32 u32AudioDataLength = 0;
    if(!MApp_KTS_IsEnable())
        return;
    MApp_KTS_Stop();

    MApp_KTS_FreeMemory();

    BinInfo.B_ID = MApp_KTS_Resource_Mapping(enItem);

    msAPI_MIU_Get_BinInfo(&BinInfo, &bResult) ;
    if (bResult != PASS)
    {
        printf("Error: Can't find PCM file on flash.\n");
        return ;
    }

    if(BinInfo.B_Len < KTS_AUDIO_BUFFER_MAXIMUM_SIZE)
        u32AudioDataLength = BinInfo.B_Len;
    else
        u32AudioDataLength = KTS_AUDIO_BUFFER_MAXIMUM_SIZE;

    g_pu8KTS_Start_Addr = msAPI_Memory_Allocate(u32AudioDataLength, BUF_ID_KTS);

    if( g_pu8KTS_Start_Addr == NULL )
    {
        printf("\nError:g_pu8KTS_Start_Addr malloc failed!\n");
        return ;
    }
    memset( g_pu8KTS_Start_Addr, 0, u32AudioDataLength);

    msAPI_MIU_Copy(BinInfo.B_FAddr, (U32)g_pu8KTS_Start_Addr, u32AudioDataLength, MIU_FLASH2SDRAM);
    //MDrv_DMA_LoadBin(&BinInfo,(U32)g_pu8KTS_Start_Addr, BinInfo.B_FAddr, (OADSEC_BUFFER_ADR+OADSEC_BUFFER_LEN));

    MApp_KTS_Setup_Audio(TRUE);

    MDrv_SND_DMA_SetPara((MS_U32)g_pu8KTS_Start_Addr, u32AudioDataLength);

    KTS_Status = EN_KTS_ISRUNNING;

}

void MApp_KTS_Task(void)
{
    if(!MApp_KTS_IsEnable())
        return;
    if((KTS_Status == EN_KTS_ISRUNNING) && MApp_KTS_IsAudioFinished())
    {
        MApp_KTS_FreeMemory();
    }
}

#endif

