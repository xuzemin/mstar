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
#define MAPP_EWS_C

#include "Board.h"

#if ENABLE_EWS

#include <string.h>

#include "MApp_EWS.h"

#include "msAPI_Timer.h"
#include "apiXC_Sys.h"

#include "ZUI_tables_h.inl"

#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_ACTglobal.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_Menu_Main.h"
#include "MApp_Audio.h"
#include "msAPI_DTVSystem.h"
#include "mapp_si.h"

#include "MApp_GlobalVar.h"
#include "MApp_ChannelChange.h"
#include "MApp_SignalMonitor.h"
#include "MApp_TopStateMachine.h"
#include "MApp_InputSource.h"
#include "MApp_TopStateMachine.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_PowerOnMusic.h"

//=============================================================================

#define EWS_DEBUG(x)        //x
#define EWS_PERIOD          1000//ms
#define EWS_MSG_DELAY       1000//90000//ms (Time of Message disappearence when EWS status was changed)

BOOL bEwsAudioMuteControl = FALSE;
static U32 u32EwsPeriodTime = 0;    //Monitor period
static U32 u32EwsMsgDelayTime = 0;  //Msg delay time; Sharp only
static BOOL bMsgCancelFlag = FALSE; // for User cancel display in WASPADA
static BOOL bEwsAudioFlag = FALSE;
static U8 u8EwsPrevStatus = EN_EWS_DEFAULT;
extern EN_MENU_STATE enMainMenuState;
MS_EWSSETTING stEwsSettingData;

extern U8 u8Scroll_BaseLine;
extern U8 u8Scroll_TotalCount;

extern U16 u16NextLineStartInx;
extern bit bStopScrollDown;

U8         u8EwsScrollLineCount = 0;
U8         u8EwsScrollLineCount_Pre = 0;

#define EWS_TEXT_SCROLL_LINE_BUF_SIZE   98
static U16 au16EwsTextScrollLineInx[EWS_TEXT_SCROLL_LINE_BUF_SIZE] = {0};

#define EWS_DESC_BUF_SIZE   4096
static U8 u8EwsDescriptionBuf[EWS_DESC_BUF_SIZE]={0};

#if ENABLE_SOUNDTEST_MUSIC_LOOP
BOOLEAN MApp_EWS_SoundTest_Exit(void)
{
    if(MApp_SoundTest_Exit())
    {
        //MApp_EWS_SetMsgCancelFlag(FALSE);
        MApp_EWS_SetAudioFlag(FALSE);
        //unmute all
        MApp_EWS_AudioMuteFlag(FALSE);
        MApp_EWS_SetAudioFlag(FALSE);
        /* unmute the sound */
        MApp_InputSource_ChangeAudioSource( SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),UI_INPUT_SOURCE_NONE);
        MApp_Audio_SetAudioLanguage(g_u8AudLangSelected);

        return TRUE;
    }
    return FALSE;
}
#endif

void MApp_EWS_Exit(void)
{
    if((MApp_ZUI_GetActiveOSD() == E_OSD_MESSAGE_BOX) && (MApp_ZUI_API_IsWindowVisible(HWND_EWS_FRAME) == TRUE  || MApp_ZUI_API_IsWindowVisible(HWND_EWS_FRAME_WASPADA) == TRUE))
    {
        MApp_ZUI_ACT_ShutdownOSD();
    }

#if ENABLE_SOUNDTEST_MUSIC_LOOP
   if( MApp_EWS_SoundTest_Exit())
   {
        // msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_EWS, DISABLE, NULL, MAIN_WINDOW);
        MApp_EWS_ScreenDisplay_Handler();
   }
   else
#endif
   {
       MApp_EWS_ScreenDisplay_Handler();

      // msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_EWS, DISABLE, NULL, MAIN_WINDOW);
       MApp_ChannelChange_SearchDefaultAudioLang();
       MApp_Audio_SetAudioLanguage(g_u8AudLangSelected);
       MApp_EWS_AudioMuteFlag(FALSE);
       EWS_DEBUG(printf("\r\n[EWS]EWS Exit"););

       //reset Flag status
       //MApp_EWS_SetMsgCancelFlag(FALSE);
       MApp_EWS_SetAudioFlag(FALSE);
   }
}

U8 MApp_EWS_GetDisasterSymbol(void)
{
    return stEwsSettingData.u8_EwsDisasterSymbol;
}

U8 MApp_EWS_GetAuthor(void)
{
    return stEwsSettingData.u8_EwsAuthor;
}

BOOLEAN MApp_EWS_NeedResetEWS(void)
{
    if(!IsDTVInUse())
    {
        return TRUE;
    }

    if( MApp_TopStateMachine_GetTopState() == STATE_TOP_CHANNELCHANGE
        || MApp_TopStateMachine_GetTopState() == STATE_TOP_DTV_SCAN
        || MApp_TopStateMachine_GetTopState() == STATE_TOP_ATV_SCAN
        || MApp_TopStateMachine_GetTopState() == STATE_TOP_DTV_MANUAL_TUNING )
    {
        return TRUE;
    }

    if (MApp_TopStateMachine_GetTopState()== STATE_TOP_STANDBY)
    {
        return TRUE;
    }

    if(MApp_ZUI_GetActiveOSD() == E_OSD_INSTALL_GUIDE)
    {
        return TRUE;
    }

    if(MApp_GetSignalStatus()!=SIGNAL_LOCK)
    {
        return TRUE;
    }

    return FALSE;

}

U8 MApp_EWS_GetStatus(void)
{

    if(!IsDVBTInUse())
    {
        //enMainMenuState = STATE_MENU_CLEAN_UP;
        return 0xFF;
    }

    if( (MApp_TopStateMachine_GetTopState()==STATE_TOP_CHANNELCHANGE)
        || (MApp_TopStateMachine_GetTopState()==STATE_TOP_DTV_SCAN)
        || (MApp_TopStateMachine_GetTopState()==STATE_TOP_ATV_SCAN)
        || (MApp_TopStateMachine_GetTopState() == STATE_TOP_DTV_MANUAL_TUNING))
    {
        return 0xFF;

    }

    if (MApp_TopStateMachine_GetTopState()== STATE_TOP_STANDBY)
    {
        return 0xFF;
    }

    if(MApp_ZUI_GetActiveOSD() == E_OSD_INSTALL_GUIDE)
    {
        return 0xFF;
    }

    if(MApp_GetSignalStatus()!=SIGNAL_LOCK)
        return 0xFF;

    MApp_SI_GetEWSSetting(&stEwsSettingData);
    if(stEwsSettingData.bisValid == TRUE)
        return stEwsSettingData.u8_EwsDisasterLoctionStatus;
    else
        return 0xFF;
}

BOOL MApp_EWS_GetMsgCancelFlag(void)
{
    return bMsgCancelFlag;
}

void MApp_EWS_SetMsgCancelFlag(BOOL Cancelflag)
{
    bMsgCancelFlag = Cancelflag;
}

void MApp_EWS_AudioMuteFlag(BOOL muteflag)
{
    bEwsAudioMuteControl = muteflag;
}

void MApp_EWS_SetAudioFlag(BOOL flag)
{
    bEwsAudioFlag = flag;
}

BOOLEAN MApp_EWS_Reset_Description(void)
{
    u8EwsScrollLineCount = 0;
    u8EwsScrollLineCount_Pre = 0;
    memset(au16EwsTextScrollLineInx, 0, sizeof(au16EwsTextScrollLineInx));
    memset(u8EwsDescriptionBuf, 0, sizeof(u8EwsDescriptionBuf));
	return TRUE;
}

BOOLEAN MApp_EWS_Set_Description(void)
{
     U16 strcount = 0;

     memset(u8EwsDescriptionBuf, 0, sizeof(u8EwsDescriptionBuf));
     strcount = strlen((char *)stEwsSettingData.u8_EwsDisasterType);
     strncpy((char*)u8EwsDescriptionBuf, (char*)stEwsSettingData.u8_EwsDisasterType, strcount);
     strcount = strlen((char*)u8EwsDescriptionBuf);
     u8EwsDescriptionBuf[strcount++]=',';
     u8EwsDescriptionBuf[strcount++]=' ';

     strncpy((char*)&u8EwsDescriptionBuf[strcount], (char*)stEwsSettingData.u8_EwsDisasterRemark, strlen((char *)stEwsSettingData.u8_EwsDisasterRemark));

     //Daerah Anda :

     strcount = strlen((char*)u8EwsDescriptionBuf);
#if  0
     //U16 i;
     printf("\n===start===len:%d, len2:%d\n", strlen((char *)stEwsSettingData.u8_EwsDisasterRemark), strcount);
     for(i = 0; i < 4096; i++)
     {
         printf("%c", u8EwsDescriptionBuf[i]);
     }
     printf("===end===\n");
#endif
     u8EwsDescriptionBuf[strcount++]=',';
     u8EwsDescriptionBuf[strcount++]=' ';
     u8EwsDescriptionBuf[strcount++]='D';
     u8EwsDescriptionBuf[strcount++]='a';
     u8EwsDescriptionBuf[strcount++]='e';
     u8EwsDescriptionBuf[strcount++]='r';
     u8EwsDescriptionBuf[strcount++]='a';
     u8EwsDescriptionBuf[strcount++]='h';
     u8EwsDescriptionBuf[strcount++]=' ';
     u8EwsDescriptionBuf[strcount++]='A';
     u8EwsDescriptionBuf[strcount++]='n';
     u8EwsDescriptionBuf[strcount++]='d';
     u8EwsDescriptionBuf[strcount++]='a';
     u8EwsDescriptionBuf[strcount++]=' ';
     u8EwsDescriptionBuf[strcount++]=':';
     u8EwsDescriptionBuf[strcount++]=' ';

     switch(MApp_EWS_GetStatus())
     {
         case EN_EWS_AWAS:
             strcpy((char*)&u8EwsDescriptionBuf[strcount], "Status Awas");
             break;

         case EN_EWS_SIAGA:
             strcpy((char*)&u8EwsDescriptionBuf[strcount], "Status Siaga");
             break;

         case EN_EWS_WASPADA:
             strcpy((char*)&u8EwsDescriptionBuf[strcount], "Status Waspada");

         break;

         default:
             u8EwsDescriptionBuf[strcount++]=0;
             break;
     }

     return TRUE;

}

BOOLEAN MApp_EWS_Get_Description(U16* pStrDest, U16 u32DestBufSize )
{
    //MApp_ZUI_API_StringBuffU8toU16(pStrDest,stEwsSettingData.u8_EwsDisasterType,strcount);

    // Clear dest buf
    pStrDest[0] = 0;

    U16 u16CopySize = EWS_DESC_BUF_SIZE;

    U16 u16BufOffset = 0;

    if( u8EwsScrollLineCount < EWS_TEXT_SCROLL_LINE_BUF_SIZE )
    {
        u16BufOffset = au16EwsTextScrollLineInx[u8EwsScrollLineCount];
        if( u16BufOffset >= EWS_DESC_BUF_SIZE )
        {
            return FALSE;
        }

        // u16BufOffset range is 0 ~ 4095
        // u16CopySize range is 4096 ~ 1
        u16CopySize = EWS_DESC_BUF_SIZE - u16BufOffset;
    }

    if( u16CopySize > u32DestBufSize )
    {
        u16CopySize = u32DestBufSize;
    }

    MApp_ZUI_API_StringBuffU8toU16(pStrDest, (u8EwsDescriptionBuf + u16BufOffset), /*4096*/u16CopySize );

    //printf("[%s][%d] addr:%d, line:%d \n", __FUNCTION__, __LINE__, au16EwsTextScrollLineInx[u8EwsScrollLineCount], u8EwsScrollLineCount);
    return TRUE;
}

BOOLEAN MApp_EWS_Scroll(void)
{
    if((MApp_ZUI_GetActiveOSD() != E_OSD_MESSAGE_BOX) ||
        (MApp_ZUI_API_IsWindowVisible(HWND_EWS_FRAME) == FALSE))
    {
        return FALSE;
    }

    if (u8KeyCode == KEY_DOWN && bStopScrollDown)
    {
        return FALSE;
    }

    if ( u8KeyCode == KEY_DOWN && !bStopScrollDown )
    {
        u8EwsScrollLineCount ++;
    }

    if ( u8KeyCode == KEY_UP && u8EwsScrollLineCount > 0 )
    {
        u8EwsScrollLineCount--;
    }

    if ( u8EwsScrollLineCount == 0 )
    {
        au16EwsTextScrollLineInx[0] = 0;
    }
    else
    {
        if ( u8EwsScrollLineCount > u8EwsScrollLineCount_Pre )
        {
            au16EwsTextScrollLineInx[u8EwsScrollLineCount] = au16EwsTextScrollLineInx[u8EwsScrollLineCount - 1] + u16NextLineStartInx;
            u8EwsScrollLineCount_Pre = u8EwsScrollLineCount_Pre;
        }
    }

    // TODO
    //MApp_ZUI_API_ShowWindow(HWND_CHINFO_EXT_CONTENT_TEXT, SW_SHOW);

    MApp_ZUI_API_InvalidateWindow(HWND_EWS_FRAME);

    return TRUE;
}


void MApp_EWS_Scroll_Text(EWS_TEXT_SCROLL uTextScroll)
{

    //bEwsAudioFlag = flag;
    switch(uTextScroll)
    {
        case EN_EWS_SCROLL_RESET:
            u8Scroll_BaseLine =0;
            u8Scroll_TotalCount = 0;
          break;

        case EN_EWS_SCROLL_DOWN:
            //printf(" EN_EWS_SCROLL_DOWN  u8Scroll_TotalCount=%d  u8Scroll_BaseLine=%d\n",u8Scroll_TotalCount,u8Scroll_BaseLine);
            if(u8Scroll_TotalCount>0 &&( u8Scroll_BaseLine < (u8Scroll_TotalCount-1)))
            {
                u8Scroll_BaseLine ++;

			if((MApp_ZUI_GetActiveOSD() == E_OSD_MESSAGE_BOX) && (MApp_ZUI_API_IsWindowVisible(HWND_EWS_FRAME) == TRUE))
                {
                    MApp_ZUI_API_InvalidateWindow(HWND_EWS_FRAME);

                }
            if((MApp_ZUI_GetActiveOSD() == E_OSD_MESSAGE_BOX) && (MApp_ZUI_API_IsWindowVisible(HWND_EWS_FRAME) == TRUE  || MApp_ZUI_API_IsWindowVisible(HWND_EWS_FRAME_WASPADA) == TRUE))
                {
                    MApp_ZUI_API_InvalidateWindow(HWND_EWS_FRAME_WASPADA);
                }
            }
          break;

        case EN_EWS_SCROLL_UP:
        {

            //printf(" EN_EWS_SCROLL_UP  u8Scroll_TotalCount=%d  u8Scroll_BaseLine=%d\n",u8Scroll_TotalCount,u8Scroll_BaseLine);
            if(u8Scroll_BaseLine>0)
            {
                u8Scroll_BaseLine --;
                if((MApp_ZUI_GetActiveOSD() == E_OSD_MESSAGE_BOX) && (MApp_ZUI_API_IsWindowVisible(HWND_EWS_FRAME) == TRUE  || MApp_ZUI_API_IsWindowVisible(HWND_EWS_FRAME_WASPADA) == TRUE))
                {
                    MApp_ZUI_API_InvalidateWindow(HWND_EWS_FRAME_WASPADA);
                }
            }
        }
      break;


    }
}


BOOL MApp_EWS_Audio_Monitor(void)
{
   // if(MApp_EWS_GetStatus()== EN_EWS_WASPADA)
      //  return TRUE;
    if((bEwsAudioFlag == FALSE))
    {

#if ENABLE_SOUNDTEST_MUSIC_LOOP
       // printf(" Make EWS Mp3\n");
        if(MApp_EWS_GetStatus()== EN_EWS_WASPADA )
        {
            if((MApp_ZUI_GetActiveOSD() == E_OSD_MESSAGE_BOX) && (MApp_ZUI_API_IsWindowVisible(HWND_EWS_FRAME_WASPADA) == TRUE))
            {
                MApp_SoundTest_ON(TRUE);
                MApp_EWS_SetAudioFlag(TRUE);
            }
        }
        else
        {
            MApp_SoundTest_ON(TRUE);
            MApp_EWS_SetAudioFlag(TRUE);
        }
#else

        MS_EWSAUDIOINFO stAudioInfo;

        MApp_SI_GetEWSAudioInfo(&stAudioInfo);
    	EWS_DEBUG(printf("audio PID =%x,audio type=%x\n",stAudioInfo.u16EWSAudioPID,stAudioInfo.u16EWSAudioType);)
        if(stAudioInfo.u16EWSAudioPID == 0)
        {

            return FALSE;
        }
        MApp_Audio_SetEWSAudio(stAudioInfo);
        MApp_EWS_SetAudioFlag(TRUE);

#endif


    }
    return TRUE;
}
void MApp_EWS_ScreenDisplay_Handler(void)
{
    switch(MApp_EWS_GetStatus())
    {
        case EN_EWS_AWAS://0x01 AWAS
            msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_EWS, ENABLE, NULL, MAIN_WINDOW);
            break;

        case EN_EWS_SIAGA://0x02 SIAGA
        case EN_EWS_WASPADA://0x03 WASPADA
        default:
            msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_EWS, DISABLE, NULL, MAIN_WINDOW);
            break;
    }
}

void MApp_EWS_MsgDisplay_Monitor(void)
{
    switch(MApp_EWS_GetStatus())
    {
        case EN_EWS_AWAS://0x01 AWAS
        case EN_EWS_SIAGA://0x02 SIAGA
        {

            MApp_EWS_SetMsgCancelFlag(FALSE);
            if(MApp_ZUI_GetActiveOSD() == E_OSD_MAIN_MENU)
            {
                enMainMenuState = STATE_MENU_CLEAN_UP;
                return;
            }
            else if((MApp_ZUI_GetActiveOSD() == E_OSD_MESSAGE_BOX) && (MApp_ZUI_API_IsWindowVisible(HWND_EWS_FRAME) == TRUE))
            {
                MApp_ZUI_API_InvalidateWindow(HWND_EWS_FRAME);
            }
            else
            {
                if(MApp_ZUI_GetActiveOSD() != E_OSD_EMPTY)
                {

                    MApp_ZUI_ACT_ShutdownOSD();
                }
                else
                {

                    MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                    MApp_TopStateMachine_SetTopState(STATE_TOP_DIGITALINPUTS);
                }
            }
        }
            break;
        case EN_EWS_WASPADA://0x03 WASPADA
        {

            if(bMsgCancelFlag ==  TRUE)
            {
                if((MApp_ZUI_GetActiveOSD() == E_OSD_MESSAGE_BOX) && (MApp_ZUI_API_IsWindowVisible(HWND_EWS_FRAME_WASPADA) == TRUE))
                {
                    MApp_ZUI_ACT_ShutdownOSD();
#if ENABLE_SOUNDTEST_MUSIC_LOOP
                    MApp_EWS_SoundTest_Exit();
#endif
                }
                else
                {

                }
            }
            else
            {
                if((MApp_ZUI_GetActiveOSD() == E_OSD_MESSAGE_BOX) && (MApp_ZUI_API_IsWindowVisible(HWND_EWS_FRAME_WASPADA) == FALSE))
                {
                    MApp_ZUI_API_InvalidateWindow(HWND_EWS_FRAME_WASPADA);
                }
                else
                {
                    if(MApp_ZUI_GetActiveOSD() == E_OSD_MAIN_MENU) //mainmenu exit
                    {
                        enMainMenuState = STATE_MENU_CLEAN_UP;
                        return;
                    }
                    else
                    {

                        if(MApp_ZUI_GetActiveOSD() != E_OSD_EMPTY)
                        {
                            //1244410 when ESW WASPADA, do not flicking osd
                            //MApp_ZUI_ACT_ShutdownOSD();
                        }
                        else
                        {

                            MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                            MApp_TopStateMachine_SetTopState(STATE_TOP_DIGITALINPUTS);

                        }
                    }

                }
            }

        }
            break;
        default:
            //MApp_ZUI_ACT_ShutdownOSD();
            break;
    }

}

BOOL MApp_EWS_DisasterStatusCheck(void)
{
    switch(MApp_EWS_GetStatus())
    {
        case EN_EWS_AWAS:
        case EN_EWS_SIAGA:
            bMsgCancelFlag = FALSE;
        case EN_EWS_WASPADA:
            EWS_DEBUG(printf("\r\n[EWS]EWS STATUS %x",MApp_EWS_GetStatus());)

            return TRUE;
        default:
            EWS_DEBUG(printf("\r\n[EWS]EWS STATUS %x",MApp_EWS_GetStatus());)
            bMsgCancelFlag = FALSE;
            return FALSE;
    }
}

void MApp_EWS_Handler(void)
{
    U8 u8EwsCurrentStatus = MApp_EWS_GetStatus();

    if(IsDTVInUse())
    {
        if(MApp_ZUI_GetActiveOSD() == E_OSD_INSTALL_GUIDE || MApp_ZUI_GetActiveOSD() == E_OSD_DTV_MANUAL_TUNING || MApp_ZUI_GetActiveOSD() == E_OSD_AUTO_TUNING)
        {
             //no need to check EWS, because now is scan
             if(  MApp_TopStateMachine_GetTopState()==STATE_TOP_DTV_SCAN )
             {
                 MApp_EWS_SetMsgCancelFlag(FALSE);

             }

        }
        else if((MApp_ZUI_GetActiveOSD() == E_OSD_MAIN_MENU) && (MApp_ZUI_API_IsWindowVisible(HWND_MENU_DLG_INPUT_EWS_LOCATION_COMMON) == TRUE))
        {
            //bypass: cancel WASPASA msg status
            MApp_EWS_SetMsgCancelFlag(FALSE);
        }
        else
        {

            if((MApp_ZUI_GetActiveOSD() == E_OSD_MAIN_MENU) && (MApp_ZUI_API_IsWindowVisible(HWND_MENU_DLG_INPUT_EWS_LOCATION_COMMON) == TRUE))
                return;

            if(msAPI_Timer_DiffTimeFromNow(u32EwsPeriodTime) < EWS_PERIOD)
                return;
            u32EwsPeriodTime = msAPI_Timer_GetTime0();

            if(MApp_EWS_NeedResetEWS())
            {
                MApp_SI_ExitEWS();
                MApp_EWS_SetMsgCancelFlag(FALSE);
            }


            if((u8EwsCurrentStatus == EN_EWS_AWAS)
                ||(u8EwsCurrentStatus == EN_EWS_SIAGA)
                ||(u8EwsCurrentStatus == EN_EWS_WASPADA))
            {
                MApp_EWS_MsgDisplay_Monitor();
                MApp_EWS_Audio_Monitor();

#if ENABLE_SOUNDTEST_MUSIC_LOOP
                MApp_SoundTest_Task(BIN_ID_EWS_MP3);
#endif

                if(u8EwsPrevStatus != u8EwsCurrentStatus)
                {
                    EWS_DEBUG(printf("\r\n[EWS]Screen Mute");)
                    MApp_EWS_Exit();
                }
                u32EwsMsgDelayTime = msAPI_Timer_GetTime0();
                u8EwsPrevStatus = u8EwsCurrentStatus;
            }
            else
            {


                if(u8EwsPrevStatus != u8EwsCurrentStatus)
                {
                        MApp_EWS_Exit();
                        u8EwsPrevStatus = u8EwsCurrentStatus;
                }

            }
        }

    }
}
#endif
#undef MAPP_EWS_C
