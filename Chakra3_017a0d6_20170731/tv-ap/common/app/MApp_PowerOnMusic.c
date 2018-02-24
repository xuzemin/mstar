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

//-------------------------------------------------------------------------------------------------
#include "Board.h"

#if( ENABLE_POWERON_MUSIC || ENABLE_SOUNDTEST_MUSIC_LOOP)

#define MAPP_POWER_ON_MUSIC_C

#include "BinInfo.h"

#include "msAPI_MIU.h"
#include "msAPI_Timer.h"

#include "MApp_GlobalSettingSt.h"

#include "mapp_music.h"

#include "MApp_Audio.h"

#include "MApp_PowerOnMusic.h"

//-------------------------------------------------------------------------------------------------
#ifndef POWERON_MUSIC_MIN_HOLD_ON_TIME
#define POWERON_MUSIC_MIN_HOLD_ON_TIME  3000
#endif

#define POWER_ON_MUSIC_VOLUME   (stGenSetting.g_SoundSetting.Volume)


static U32 g_u32PowerOnMusicStartTime = 0;
static BOOL g_bPowerOnMusicExist = FALSE;

static U16 m_u16BinID;

static EN_MUSIC_STATE g_PowerOnMusic_eState = STATE_MUSIC_NONE;

#define MANDY_REFINE_1  0

#if(MANDY_REFINE_1)
static U32 u32AudioStatus;
#endif

#define DEBUG_POWER_ON_MUSIC(x) //x

//******************************************************************************
/// Initialize of playback melody from flash.
/// @param  u16BinID \b IN Specify melody bin ID.
/// @return NA
//******************************************************************************
void MApp_Music_StateInit(U16 u16BinID)
{
    g_PowerOnMusic_eState = STATE_MUSIC_INIT;
    m_u16BinID = u16BinID;
    g_u32PowerOnMusicStartTime = 0;
    g_bPowerOnMusicExist = FALSE;

#if(MANDY_REFINE_1)
    u32AudioStatus = 0;
    msAPI_AUD_StoreRestoreAudioMuteStatus(TRUE, &u32AudioStatus);
    msAPI_AUD_SetAllAudioUnmute();
#endif
}

BOOLEAN MApp_Music_PowerON_Melody_Decode_OneTime(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    DEBUG_POWER_ON_MUSIC( printf("MApp_Music_PowerON_Melody_Decode_OneTime() at %u\n", MsOS_GetSystemTime()); );

    U32 u32FlashStart, u32FlashEnd;
    BININFO BinInfo;

#if (ENABLE_MPLAYER_CAPTURE_MUSIC)
    if (stGenSetting.g_SysSetting.UsrPowerOnMusic == POWERON_MUSIC_USER)
    {
        u32FlashStart = (U32)USER_MP3_FLASH_START_ADDR;
        u32FlashEnd = (U32)USER_MP3_FLASH_END;
    }
    else
#endif // #if (ENABLE_MPLAYER_CAPTURE_MUSIC)
    {
        BOOLEAN bResult;

        BinInfo.B_ID = m_u16BinID;
        msAPI_MIU_Get_BinInfo(&BinInfo, &bResult) ;

        if (bResult != PASS)
        {
            printf("Error: Can't find MP3 file on flash.\n");
            return FALSE;
        }

        u32FlashStart = BinInfo.B_FAddr;
        u32FlashEnd = BinInfo.B_FAddr + BinInfo.B_Len;
    }

    msAPI_Music_Init(MSAPI_AUD_DVB_MP3, POWER_ON_MUSIC_VOLUME);

    MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_FREE_RUN);
    //PRINT_CURRENT_LINE();
    //msAPI_AUD_PrintMuteClient();

//==============================================================
#if( POWER_ON_MUSIC_LOAD_DATA_ONE_TIME ) // Use R2 decoder (MM new mode)

    AES_INFO es_info;
    U32 MADBuffAddr;
    U32 u32FileSize = BinInfo.B_Len;
    U32 es_size, es_total_size = 0;
    MADBuffAddr = (msAPI_AUD_GetDspMadBaseAddr(DSP_DEC));
    MApi_AUDIO_MM2_initAesInfo(AU_DEC_ID1);

    DEBUG_POWER_ON_MUSIC( printf("MP3 u32FileSize=0x%X\n", u32FileSize); );

    while(u32FileSize > 0)
    {
        MApi_AUDIO_MM2_checkAesInfo(AU_DEC_ID1, &es_info);
        if(es_info.aes_freeSpace > 0)
        {
            es_total_size += es_info.aes_freeSpace;
            es_size = MIN(es_info.aes_freeSpace, u32FileSize);

            msAPI_MIU_Copy(u32FlashStart, es_info.aes_write_addr + MADBuffAddr, es_size, MIU_FLASH2SDRAM);

            u32FlashStart += es_size;
            u32FileSize -= es_size;
            DEBUG_POWER_ON_MUSIC( printf("u32FileSize=0x%X\n", u32FileSize); );

            MApi_AUDIO_MM2_inputAesFinished(AU_DEC_ID1, es_size, FALSE, 0); //Inform R2 how much ES data is sent
        }
        else
        {
            printf("\x1b[31m""Power On music file (%u) is larger than ES buffer(%u)!!!!""\x1b[0m""\n",BinInfo.B_Len, es_total_size);
            break;
        }
    }

    msAPI_Timer_Delayms(4);
    MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_PLAYMM_FILE2);

    g_u32PowerOnMusicStartTime = msAPI_Timer_GetTime0();
    //printf("g_u32PowerOnMusicStartTime=%u\n", g_u32PowerOnMusicStartTime);

#if(ENABLE_LOG_FILE_IN_MEM)
    DEBUG_BOOT_TIME( Debug_Log_MemPrintf( LOG_MEM_GROUP_BOOT, "g_u32PowerOnMusicStartTime=%u\n",  g_u32PowerOnMusicStartTime ); );
#endif

    msAPI_Timer_Delayms(4);
    g_bPowerOnMusicExist = TRUE;
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
    return TRUE;

#else // Use DSP decoder (MM old mode)

    U32 u32ReqAddr, u32ReqBytes = 0;
    U32 u32AlreadyCopySize = 0;


    MApi_AUDIO_SetMpegInfo(Audio_MPEG_infoType_MMFileSize, FILE_SIZE_64KB, 0);

    msAPI_Music_StartDecode();

    msAPI_Timer_Delayms(30);

    g_u32PowerOnMusicStartTime = msAPI_Timer_GetTime0();

    while(1)
    {
        u32FlashStart += u32ReqBytes;
        if( (msAPI_Music_CheckInputRequest(&u32ReqAddr, &u32ReqBytes) == TRUE) )
        {
            //printf("Request: 0x%x 0x%X\n", u32ReqAddr, u32ReqBytes);

            if ( u32FlashStart + u32ReqBytes >= u32FlashEnd )
            {
                msAPI_Music_CleanFileEndData(u32ReqAddr, u32ReqBytes, 0x0UL);
                u32ReqBytes = u32FlashEnd - u32FlashStart;
            }

            msAPI_MIU_Copy(u32FlashStart, u32ReqAddr, u32ReqBytes, MIU_FLASH2SDRAM);

            msAPI_Music_SetInput();

            g_bPowerOnMusicExist = TRUE;

            u32AlreadyCopySize += u32ReqBytes;

            if( u32AlreadyCopySize >= BinInfo.B_Len )
            {
                //return TRUE;   //Normal exit path
                break;
            }
        }
        else
        {
            printf("\x1b[31m Power On music file (%u) is larger than ES buffer(%u)!!!! \x1b[0m\n",BinInfo.B_Len, MApi_AUDIO_GetCommAudioInfo(Audio_Comm_infoType_DEC1_ESBufferSize));
            g_bPowerOnMusicExist = TRUE;
            break;
        }
    }

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
    return TRUE;
#endif
}

#if( ENABLE_POWERON_MUSIC )

BOOLEAN MApp_Music_Decode(void)
{
    //static BOOLEAN bDataOnFlash;
    static U32 u32FlashStart, u32FlashEnd;

    U32 u32ReqAddr, u32ReqBytes;
    BININFO BinInfo;

    switch (g_PowerOnMusic_eState)
    {
        case STATE_MUSIC_INIT:
            //bDataOnFlash = FALSE;

#if (ENABLE_MPLAYER_CAPTURE_MUSIC)
            if (stGenSetting.g_SysSetting.UsrPowerOnMusic == POWERON_MUSIC_USER)
            {
                //msAPI_Flash_ChipSelect(E_FLASH_CHIP_SELECT_1);
               //MDrv_SERFLASH_Init();

                u32FlashStart = (U32)USER_MP3_FLASH_START_ADDR;
                u32FlashEnd = (U32)USER_MP3_FLASH_END;

                //bDataOnFlash = TRUE;
            }
            else
#endif // #if (ENABLE_MPLAYER_CAPTURE_MUSIC)
            {
                BOOLEAN bResult;

                BinInfo.B_ID = m_u16BinID;
                msAPI_MIU_Get_BinInfo(&BinInfo, &bResult) ;

                if (bResult != PASS)
                {
                    printf("Error: Can't find MP3 file on flash.\n");
                    return TRUE;
                }

                u32FlashStart = BinInfo.B_FAddr;
                u32FlashEnd = BinInfo.B_FAddr + BinInfo.B_Len;
            }

            msAPI_Music_Init(MSAPI_AUD_DVB_MP3, POWER_ON_MUSIC_VOLUME);
            msAPI_Music_StartDecode();
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_DURING_LIMITED_TIME_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);

            msAPI_Timer_Delayms(30);

            g_PowerOnMusic_eState = STATE_MUSIC_INPUT;
            break;

        case STATE_MUSIC_INPUT:
            if ((msAPI_Music_CheckInputRequest(&u32ReqAddr, &u32ReqBytes) == TRUE))
            {
                {
                    int org_size = u32ReqBytes;

                    if ( u32FlashStart + u32ReqBytes >= u32FlashEnd )
                    {
                        msAPI_Music_CleanFileEndData(u32ReqAddr, u32ReqBytes, 0x0UL);
                        u32ReqBytes = u32FlashEnd - u32FlashStart;
                    }

                    /*if (bDataOnFlash)
                    {
                        msAPI_Flash_Read(u32FlashStart, u32ReqBytes, (U8 *)_PA2VA(u32ReqAddr));
                    }
                    else */
                    {
                        msAPI_MIU_Copy(u32FlashStart, u32ReqAddr, u32ReqBytes, MIU_FLASH2SDRAM);
                    }
                    u32ReqBytes = org_size;
                }

                u32FlashStart +=u32ReqBytes;
                msAPI_Music_SetInput();
            }

            if (u32FlashStart >= u32FlashEnd)
            {
                g_PowerOnMusic_eState = STATE_MUSIC_WAIT_DECODE_DONE;
            }

            if (g_PowerOnMusic_eState == STATE_MUSIC_WAIT_DECODE_DONE)
            {
#if (ENABLE_MPLAYER_CAPTURE_MUSIC)
                if(stGenSetting.g_SysSetting.UsrPowerOnMusic == POWERON_MUSIC_USER)
                {
                    //msAPI_Flash_ChipSelect(E_FLASH_CHIP_SELECT_0);
                    //MDrv_SERFLASH_Init();
                }
#endif // #if (ENABLE_MPLAYER_CAPTURE_MUSIC)
            }
            break;

        case STATE_MUSIC_WAIT_DECODE_DONE:
            if (msAPI_Music_CheckPlayDone())
            {
                return TRUE;
            }
            break;

        case STATE_MUSIC_NONE:
        default:
            // Do nothing
            break;
    }

    return FALSE;
}

void MApp_Music_StopDecode(void)
{
    msAPI_Music_StopDecode();

    g_PowerOnMusic_eState = STATE_MUSIC_NONE;
}

U32 MApp_PowerOnMusic_Get_AlreadyPlayTime(void)
{
    if( g_u32PowerOnMusicStartTime == 0 )
    {
        return 0;
    }

    return msAPI_Timer_DiffTimeFromNow(g_u32PowerOnMusicStartTime);
}

void MApp_PowerOnMusic_Stop(void)
{
    //PRINT_CURRENT_LINE();
    DEBUG_POWER_ON_MUSIC( printf("MApp_PowerOnMusic_Stop() at %u\n", MsOS_GetSystemTime() ); );


    // Set audio mute
    //printf("MUTE_On()\n");
    //MApp_Audio_Set_AmpMute(AUDIO_AMP_MUTE_ON);

#if(MANDY_REFINE_1)
    msAPI_AUD_StoreRestoreAudioMuteStatus(FALSE, &u32AudioStatus);
#else
    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYSYNC_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
#endif

    // Stop decode
    MApp_Music_StopDecode();


    //Recover to default audio request size setting
    //Because some APP seems doesn't send correct request size by itself
    MApi_AUDIO_SetMpegInfo(Audio_MPEG_infoType_MMFileSize, FILE_SIZE_2KB, 0);
}

void MApp_PowerOnMusic_WaitPlayFinish(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());
    DEBUG_POWER_ON_MUSIC( printf("MApp_PowerOnMusic_WaitPlayFinish() at %u\n", MsOS_GetSystemTime() ); );

    if( g_bPowerOnMusicExist == FALSE )
        return;


    U32 u32FunctionEnteredTime = msAPI_Timer_GetTime0();
    //printf("\nMusic played %d ms, still %d ms remaining\n", MApp_PowerOnMusic_Get_AlreadyPlayTime(), POWERON_MUSIC_MIN_HOLD_ON_TIME - MApp_PowerOnMusic_Get_AlreadyPlayTime());


    while(g_bPowerOnMusicExist)
    {
        MApp_PowerOnMusic_Task();

        if( msAPI_Timer_DiffTimeFromNow(u32FunctionEnteredTime) > 20000 )
        {
            //Time out
            break;
        }

        printf(".");
        msAPI_Timer_Delayms_2(2, E_DELAY_ID_WAIT_POWER_ON_MUSIC_DONE);
    }

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PowerOnMusic_Task(void)
{
    if( g_bPowerOnMusicExist == FALSE )
        return;

    //PRINT_CURRENT_LINE();
    DEBUG_POWER_ON_MUSIC( printf("MApp_PowerOnMusic_Task() at %u\n", MsOS_GetSystemTime()); );

    // Check if need stop music
    BOOLEAN bNeedToStop = FALSE;

    //printf("POWERON_MUSIC_MIN_HOLD_ON_TIME=%u\n", POWERON_MUSIC_MIN_HOLD_ON_TIME);
    //printf("g_u32PowerOnMusicStartTime=%u\n", g_u32PowerOnMusicStartTime);
    //printf("MApp_PowerOnMusic_Get_AlreadyPlayTime()=%u\n", MApp_PowerOnMusic_Get_AlreadyPlayTime());

    if( MApi_AUDIO_CheckPlayDone() )
    {
        DEBUG_POWER_ON_MUSIC( printf("Already play finish\n"); );
        bNeedToStop = TRUE;
    }
    else if( (MApp_PowerOnMusic_Get_AlreadyPlayTime() >= POWERON_MUSIC_MIN_HOLD_ON_TIME)
            ||(MApp_PowerOnMusic_Get_AlreadyPlayTime() >= 15000)
            )
    {
        DEBUG_POWER_ON_MUSIC( printf("Play time(%u) > %u\n", MApp_PowerOnMusic_Get_AlreadyPlayTime(), POWERON_MUSIC_MIN_HOLD_ON_TIME); );
        bNeedToStop = TRUE;
    }

    if( bNeedToStop )
    {
        MApp_PowerOnMusic_Stop();

        //PRINT_CURRENT_LINE();
        printf("Power on music stop at %u\n",  MsOS_GetSystemTime());

        g_bPowerOnMusicExist = FALSE;
    }

}

#endif //ENABLE_POWERON_MUSIC

#if ENABLE_SOUNDTEST_MUSIC_LOOP
#include "MApp_InputSource.h"
#include "MApp_EWS.h"

BOOLEAN m_bSoundTestMusicLoop = FALSE;
BOOLEAN m_bSoundTestMusicLoopFirstEnter = FALSE;
BOOLEAN m_bSoundTestMusicLoopFinish = FALSE;
BOOLEAN bInMP3_Play = FALSE;
static U32 g_u32SoundFinishTime;

BOOLEAN MApp_SoundTest_ON(BOOLEAN bSoundOn)
{
    m_bSoundTestMusicLoop = bSoundOn;
    m_bSoundTestMusicLoopFirstEnter = TRUE;
    return TRUE;
}

BOOLEAN MApp_SoundTest_Exit(void)
{

    if(bInMP3_Play)
    {
        //msAPI_AUD_FanetTestResumeMuteAudio();
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
        msAPI_Timer_Delayms(100);
        msAPI_Music_StopDecode();
        MApp_SoundTest_ON(FALSE);
        bInMP3_Play = FALSE;
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
        return TRUE;

    }
    else
    {
        return FALSE;

    }

}

void MApp_SoundTest_Task(U16 u16BinId)
{
      if(m_bSoundTestMusicLoop==TRUE)
      {
          if(m_bSoundTestMusicLoopFirstEnter==TRUE)
          {
              //MApp_Aud_EnableMute(TRUE);
              msAPI_Timer_Delayms(100);//SB
              MApp_InputSource_ChangeAudioSource(INPUT_SOURCE_STORAGE,UI_INPUT_SOURCE_NONE);
              msAPI_Timer_Delayms(100);//SB
              //MApp_Aud_EnableMute(FALSE);
              //msAPI_AUD_FanetTestUnMuteAudio();

              MApp_Music_StateInit(u16BinId);
              MApp_Music_PowerON_Melody_Decode_OneTime();
              //After music start decode , we needs to wait DSP decode first frame , so we set threshold 100ms.
              msAPI_Timer_Delayms(100);
              m_bSoundTestMusicLoopFirstEnter = FALSE;
              m_bSoundTestMusicLoopFinish = FALSE;
              bInMP3_Play = TRUE;
          }
          else if (MApi_AUDIO_CheckPlayDone())
          {

            if(m_bSoundTestMusicLoopFinish==FALSE)
            {
#if ENABLE_EWS
                MApp_EWS_SetAudioFlag(FALSE);
#endif
                m_bSoundTestMusicLoopFinish =TRUE;
                g_u32SoundFinishTime =  msAPI_Timer_GetTime0();
            }
            if(msAPI_Timer_DiffTimeFromNow(g_u32SoundFinishTime) > 200  && m_bSoundTestMusicLoopFinish ==TRUE)
            {
                MApp_Music_PowerON_Melody_Decode_OneTime();
                m_bSoundTestMusicLoopFinish = FALSE;
                //After music start decode , we needs to wait DSP decode first frame , so we set threshold 100ms.
                msAPI_Timer_Delayms(100);

            }
            else
            {
                //if(g_u32SoundFinishTime)
               // printf("@@@    g_u32SoundFinishTime=%d\n ",msAPI_Timer_DiffTimeFromNow(g_u32SoundFinishTime));
            }

          }
      }
}

#endif // ENABLE_SOUNDTEST_MUSIC_LOOP

#undef MAPP_POWER_ON_MUSIC_C

#endif // ( ENABLE_POWERON_MUSIC || ENABLE_SOUNDTEST_MUSIC_LOOP)

