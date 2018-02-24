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
#include "debug.h"
#include "datatype.h"
#include "drvAUDIO.h"
#include "apiXC.h"
#include "apiXC_Adc.h"

#include "msAPI_Global.h"
#include "msAPI_Tuning.h"
#include "msAPI_ATVSystem.h"
#include "msAPI_FreqTableATV.h"
#include "msAPI_DTVSystem.h"
#include "msAPI_audio.h"
#include "msAPI_Timer.h"
#include "msAPI_VD.h"
#include "msAPI_MIU.h"

#include "Panel.h"
#include "apiPNL.h"
#include "apiXC_PCMonitor.h"

#if ENABLE_TTX
#include "msAPI_TTX.h"
#include "mapp_ttx.h"
#endif
#include "MApp_ATVProc.h"
#include "MApp_VDMode.h"
#include "MApp_GlobalVar.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_PCMode.h"
#include "MApp_TopStateMachine.h"
#include "MApp_Scaler.h"
#include "MApp_UiMenuDef.h" //ZUI:
#include "MApp_ATV_Scan.h"
#include "MApp_ZUI_Main.h"
#include "ZUI_tables_h.inl"
#include "ZUI_exefunc.h"
#include "GPIO.h"
#include "drvUartDebug.h" //For OTHER_TUNER_DEBUG
#include "drvIPAUTH.h"
#if(CHAKRA3_AUTO_TEST)
#include "MApp_AutoTest.h"
#endif
#include "MApp_GlobalFunction.h"


#define DEBUG_TVAVHANDLER        0xFF

#ifdef DEBUG_TVAVHANDLER
    #define debugTVAVHandlerPrint(a,b)    debugPrint(a,b)
#else
    #define debugTVAVHandlerPrint(a,b)
#endif

#if (ENABLE_PIP)
#include "MApp_PIP.h"
#endif

extern unsigned char Customer_info[];
extern unsigned char Customer_hash[];
//extern THR_TBL_TYPE code AuSifInitThreshold[];
//****************************************************************************
// Private attributes of this file.
//****************************************************************************

//static VIDEOSOURCE_TYPE     m_eInitVideoSource;

//------------------------------------------------------------------------------
// Local Function Prototype
//------------------------------------------------------------------------------
static BOOLEAN _MApp_ATVProc_IsVideoSourceActive( SCALER_WIN eWindow );
//static void _MApp_ATVProc_ClearBuffer(BYTE *pcBuffer, BYTE cSize);
static void _MApp_ATVProc_NotifyToMainSystem( SCALER_WIN eWindow );

//
//------------------------------------------------------------------------------
//
static void _MApp_ATVProc_UpdateScanState( SCALER_WIN eWindow)
{
    static U8 LimitHandle=0;
  #if (ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP)
    EN_ATV_SYSTEM_TYPE u8AudioSystem = EN_ATV_SystemType_DK;
  #else
    EN_ATV_SYSTEM_TYPE u8AudioSystem = EN_ATV_SystemType_DK;//EN_ATV_SystemType_BG;
  #endif
    AUDIOSTANDARD_TYPE eAudioStandard;

  #if ( ENABLE_DVB_TAIWAN_APP || (TV_SYSTEM == TV_NTSC) )
    return;
  #elif ENABLE_SBTVD_ATV_SYSTEM
    if(IS_SBTVD_APP)
        return;
  #endif


    if ( !(IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(eWindow))) )
        return;

    LimitHandle++;
    if(LimitHandle < 90) //900mSEC
        return;
    LimitHandle = 0;

    //Update System
    eAudioStandard = msAPI_AUD_GetAudioStandard();
    u8AudioSystem=MApp_ATVProc_GetAudioSystem(eAudioStandard);

    if (u8AudioSystem != stGenSetting.stScanMenuSetting.u8SoundSystem)
    {
        stGenSetting.stScanMenuSetting.u8SoundSystem = u8AudioSystem;
      #if ((FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)||(FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)||(FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF) )// GEM_SYNC_0815
        msAPI_Tuner_SetIF();
      #endif
    }
}


//------------------------------------------------------------------------------
/// What options is enabled for this ATV.
/// @param eOption \b IN:
//      E_ENABLE_SYSTEM_L: To enable BG/I/DK/L. If not, BG/I/DK/M.
//      E_ENABLE_RF_TABLE: To use RF frequency table of china & australia.
//      E_ENABLE_RT_AFT: To enable realtime AFT.
//      E_ENABLE_CH_NAME: To enable Channel Name for ATV.
//      E_ENABLE_TTX: To enable teletext function.
//      E_ENABLE_CARRIER_MUTE:
//      E_ENABLE_SAVING_DUAL: To save dual mode. It will be saved.
//      E_ENABLE_HI_DEVIATION: To enable HI-Deviation.
//      E_ENABLE_VOLUME_CURVE_SEL: To select the kind of volume curve.
//      E_ENABLE_MONO_ONLY: To use only mono.
//      E_ENABLE_SCART: To include SCART input.
//      E_ENABLE_WSS: To use WSS and SCART-ID for detecting aspect ratio of input signal.
/// @return TRUE/FALSE
//------------------------------------------------------------------------------
BOOLEAN MApp_ATVProc_IsThisATVOptionEnabled(THISATV_OPTION eOption)
{
    BOOLEAN bEnabled;

    bEnabled = FALSE;

    switch ( eOption )
    {
    case E_ENABLE_SYSTEM_L:
    #if ( ENABLE_DTMB_CHINA_APP || ENABLE_DVB_TAIWAN_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP)
        bEnabled = FALSE;
    #else
        #if ENABLE_SBTVD_ATV_SYSTEM
        if(IS_SBTVD_APP)
        {
            bEnabled = FALSE;
        }
        else
        #endif
        {
            bEnabled = TRUE;
        }
    #endif
        break;

    case E_ENABLE_RF_TABLE:
        bEnabled = FALSE;
        break;

    case E_ENABLE_RT_AFT:
#if (OTHER_TUNER_DEBUG==1)
        bEnabled = FALSE;
#else
        bEnabled = TRUE;
#endif
        break;

    case E_ENABLE_CH_NAME:
        bEnabled = TRUE;
        break;

    case E_ENABLE_TTX:
        bEnabled = TRUE;
        break;

    case E_ENABLE_CARRIER_MUTE:
        bEnabled = TRUE;
        break;

    case E_ENABLE_SAVING_DUAL:
        bEnabled = TRUE;
        break;

    case E_ENABLE_HI_DEVIATION:
        bEnabled = FALSE;
        break;

    case E_ENABLE_VOLUME_CURVE_SEL:
        bEnabled = FALSE;
        break;

    case E_ENABLE_MONO_ONLY:
        bEnabled = FALSE;
        break;

    case E_ENABLE_SCART:
        #if(ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP)
            bEnabled = FALSE;
        #elif(INPUT_SCART_VIDEO_COUNT>0)
            bEnabled = TRUE;
        #endif
        break;

    case E_ENABLE_WSS:
        bEnabled = TRUE;
        break;

    default:
        bEnabled = FALSE;
        break;
    }

    return bEnabled;
}

void MApp_ATVProc_Initialize_Audio(void)
{
    MApi_AUTH_Process(Customer_info,Customer_hash);

#if(FIXED_POWER_ON_EARPHONE_POP==ENABLE)

  #if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)  \
     ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) \
     )
    MS_U32 u32Param = 0x00000800; // only for milan setting
  #else
    MS_U32 u32Param = 0x00000080;
  #endif

#else
    MS_U32 u32Param = 0x00000800;
#endif

    msAPI_AUD_InitAudioSystem(NULL);

    MApi_AUDIO_SOUND_SetParam(Sound_SET_Type_SetDCOffet, &u32Param);
}
/**
 FUNCTION    : void MApp_ATVProc_Exit(void)

 USAGE    : To exit TV/AV module.

 INPUT    : None

 OUTPUT    : None

 GLOBALS: None

*/
void MApp_ATVProc_Exit(void)
{
    debugTVAVHandlerPrint("exit atvav",0);

    if ( msAPI_Tuner_IsTuningProcessorBusy() == TRUE )
    {
        msAPI_Tuner_TuningProcessor(AFT_EXT_STEP_SEARCHSTOP);
    }

    MApi_AUDIO_ExitAudioSystem();
}

void MApp_ATVProc_AspectRatio_Task(void)
{
    BOOLEAN bIsTuningProcessorBusy = msAPI_Tuner_IsTuningProcessorBusy();

    // Detect WSS (widescreen signalling) singal. Change ARC if WSS changed.
    if( FALSE == bIsTuningProcessorBusy
     && TRUE == msAPI_AVD_IsAspectRatioChanged()
     && EN_AspectRatio_Original == ST_VIDEO.eAspectRatio
     && IsSrcTypeDigitalVD( SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW) )
     ) //Support WSS only in original ARC of picture mode
    {
        EN_ASPECT_RATIO_TYPE eVideoARCType; //ARC type on "SCREEN" ( Result ARC )
        ASPECT_RATIO_TYPE     eWSSARCType;  //ARC type come from input source
        // Retrieve WSS type from Video decoder.
        eWSSARCType = msAPI_AVD_GetAspectRatioCode();

        //In channel edit screen, need to use FULL screen mode
      #if 0 //ZUI:
        if( g_u8MenuPageIndex == MENU_CHANNEL_EDIT
/*       || g_u8MenuPageIndex ==   MENU_CHANNEL_EDIT_LIST
         || g_u8MenuPageIndex ==   MENU_CHANNEL_EDIT_LIST_DELETING
         || g_u8MenuPageIndex ==   MENU_CHANNEL_EDIT_LIST_MOVING*/
         || g_u8MenuPageIndex ==   MENU_BLOCK_EDIT
/*       || g_u8MenuPageIndex ==   MENU_BLOCK_EDIT_LIST*/ )
      #else
        if (MApp_ZUI_GetActiveOSD()==E_OSD_PROGRAM_EDIT)
      #endif
        {
            eVideoARCType = VIDEOSCREEN_FULL;
        }
        else if ((g_IPanel.AspectRatio()!=E_PNL_ASPECT_RATIO_WIDE) )
        {   //WSS only for wide panel
            eVideoARCType = VIDEOSCREEN_NORMAL;
        }
        else
        {
            switch(eWSSARCType)
            {
                case ARC4x3_FULL:
                    eVideoARCType  =   VIDEOSCREEN_NORMAL;
                    break;

                case ARC14x9_LETTERBOX_CENTER:
                case ARC14x9_FULL_CENTER:
                        eVideoARCType = VIDEOSCREEN_WSS_14by9_LETTERBOX_CENTER;
                        break;
                    case ARC14x9_LETTERBOX_TOP:
                        eVideoARCType = VIDEOSCREEN_WSS_14by9_LETTERBOX_TOP;
                    break;
                case ARC16x9_LETTERBOX_CENTER:
                case ARC_ABOVE16x9_LETTERBOX_CENTER:
                        eVideoARCType = VIDEOSCREEN_WSS_16by9_LETTERBOX_CENTER;
                        break;
                    case ARC16x9_LETTERBOX_TOP:
                        eVideoARCType = VIDEOSCREEN_WSS_16by9_LETTERBOX_TOP;
                    break;

                case ARC16x9_ANAMORPHIC:
                    eVideoARCType = VIDEOSCREEN_FULL;
                    break;

                case ARC_INVALID:
                default:
                    eVideoARCType = VIDEOSCREEN_NORMAL;
                    break;
            }
        }

        //if(IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
        {
            stSystemInfo[MAIN_WINDOW].enAspectRatio = eVideoARCType;
            printf("Set stSystemInfo[MAIN_WINDOW].enAspectRatio=%u\n", stSystemInfo[MAIN_WINDOW].enAspectRatio);
            MApp_Scaler_SetWindow(NULL, NULL, NULL,
                                  stSystemInfo[MAIN_WINDOW].enAspectRatio,
                                  SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
        }
    }

}

void MApp_ATVProc_Scart_Task(void)
{
    static U32 s_u32ScartFB_Task_LastTime = 0;


    if( msAPI_Timer_DiffTime_2(s_u32ScartFB_Task_LastTime, MsOS_GetSystemTime()) < 5 )
        return;

    s_u32ScartFB_Task_LastTime = MsOS_GetSystemTime();



    msAPI_AVD_Scart_Monitor();

    // If scart src type change, set window again
    if( msAPI_AVD_GetScart1SrcType() != E_SCART_SRC_TYPE_UNKNOWN )
    {
        if(TRUE == msAPI_AVD_IsScart1SourceTypeChanged())
        {
            MApp_Scaler_SetWindow(
                NULL,
                NULL,
                NULL,
                stSystemInfo[MAIN_WINDOW].enAspectRatio,
                SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),
                MAIN_WINDOW);
        }
    }
}

#if ENABLE_TTX
void MApp_ATVProc_TTX_Task(void)
{
    BOOLEAN bIsTuningProcessorBusy = msAPI_Tuner_IsTuningProcessorBusy();

    // Teletext is turned off suddenly.
    if( FALSE == bIsTuningProcessorBusy && TRUE == MApp_TTX_IsTeletextOffSuddenly() )
    {
        MApp_TTX_TeletextCommand(TTX_TV);
    }

#if( 0 == ENABLE_TTX_SHOW_OFF_SIGNAL)//Don't exit TTX mode when signal off
    if(msAPI_AVD_GetStandardDetection()==E_VIDEOSTANDARD_NOTSTANDARD)
    {
        if(MApp_TTX_IsTeletextOn())
            MApp_TTX_TeletextCommand(TTX_TV);
    }
#endif

    MApp_TTX_VBIDataProcessor();
}
#endif


/**
 FUNCTION    : void void MApp_ATVProc_Handler(void)

 USAGE    : To make TV/AV module breathing. This function should be called under 10ms continuously.

 INPUT    : None

 OUTPUT    : None

 GLOBALS: None
*/

#define DEBUG_ATV_PROC_TIME(x)   //x

void MApp_ATVProc_Handler( SCALER_WIN eWindow )
{
    static DWORD m_dwATVAVHandlerTimer = 0;
    //DEBUG_ATV_PROC_TIME(U32 u32Time1 = MsOS_GetSystemTime();)

    // Every 10ms do one time, why 10ms?
    if( (msAPI_Timer_DiffTimeFromNow(m_dwATVAVHandlerTimer) < 10) )
    {
        return;
    }

    m_dwATVAVHandlerTimer = msAPI_Timer_GetTime0();

#if 0//( DEBUG_CHG_SRC_TIME)
    printf(" ATVP-1 %u\n", g_Debug_u32Time_ChangeSrc);
#endif

    DEBUG_ATV_PROC_TIME(printf("ATV_Proc-1 %u\n", MsOS_GetSystemTime()););

    msAPI_AVD_VideoProcessor();

    DEBUG_ATV_PROC_TIME(printf("ATV_Proc-2 %u\n", MsOS_GetSystemTime()););

#if(ENABLE_ATSC)
    // If in ATSC auto scan, return
    if( MApp_Is_InAutoScan_ATSC() )
    {
        return;
    }
#endif

    DEBUG_ATV_PROC_TIME(printf("ATV_Proc-3 %u\n", MsOS_GetSystemTime()););

    if( TRUE == msAPI_AVD_IsVideoFormatChanged()&&(msAPI_AVD_Is_VDStable()) )
    {
        msAPI_AVD_SetIsVideoFormatChangedAsFalse();

        _MApp_ATVProc_NotifyToMainSystem(eWindow);
    }

    DEBUG_ATV_PROC_TIME(printf("ATV_Proc-4 %u\n", MsOS_GetSystemTime()););

#if ENABLE_TTX_ACI
    if (enTTXACIState!=STATE_TTX_ACI_FINALIZE_EXIT) // if !processAci, we can change frequency!
#endif
    {
        if (MApp_ATV_Scan_ScanState() != STATE_ATV_SCAN_PAUSE)
        {
        #if (ENABLE_FM_RADIO)
            if ( UI_INPUT_SOURCE_TYPE != UI_INPUT_SOURCE_FMRADIO)
        #endif
            {
                msAPI_Tuner_TuningProcessor(AFT_EXT_STEP_PERIODIC);
            }
        }
    }

    DEBUG_ATV_PROC_TIME(printf("ATV_Proc-5 %u\n", MsOS_GetSystemTime()););

    if ( msAPI_Tuner_IsTuningProcessorBusy() == FALSE )
    {
        _MApp_ATVProc_UpdateScanState(eWindow);
    }

    DEBUG_ATV_PROC_TIME(printf("ATV_Proc-6 %u\n", MsOS_GetSystemTime()););


  #if (ENABLE_PIP)
    if( (MApp_Get_PIPMode() == EN_PIP_MODE_OFF) || UI_IS_AUDIO_SOURCE_IN(eWindow) )
  #endif
    {
        MW_AUD_AudioProcessor();
    }

    DEBUG_ATV_PROC_TIME(printf("ATV_Proc-7 %u\n", MsOS_GetSystemTime()););

#if ENABLE_TTX
    MApp_ATVProc_TTX_Task();
#endif

#if ENABLE_IP_AUTO_COAST
    msAPI_Scaler_IPAutoCoastHandler();
#endif

#if(PATCH_FOR_V_RANGE)
    MApp_VD_SyncRangeHandler();
#endif

    MApp_ATVProc_AspectRatio_Task();

    // Monitor Scart fast blanking
    if( (msAPI_Tuner_IsTuningProcessorBusy() == FALSE)
      &&(IsScartInUse())
      )
    {
        MApp_ATVProc_Scart_Task();
    }

    DEBUG_ATV_PROC_TIME(printf("ATV_Proc-8 %u\n", MsOS_GetSystemTime()););
}

//------------------------------------------------------------------------------
// Local Functions
//------------------------------------------------------------------------------
static BOOLEAN _MApp_ATVProc_IsVideoSourceActive(SCALER_WIN eWindow)
{
    if( IsSrcTypeDigitalVD(SYS_INPUT_SOURCE_TYPE(eWindow)))
    {
        return TRUE;
    }

    return FALSE;
}
/*
static void _MApp_ATVProc_ClearBuffer(BYTE *pcBuffer, BYTE cSize)
{
    BYTE i;

    for(i=0; i < cSize; i++)
    {
        pcBuffer[i] = 0x00;
    }
}
*/

#if ENABLE_NO_AUDIO_INPUT_AUTO_MUTE
void _MApp_ATVProc_NO_AUDIO_INPUT_AUTO_MUTE(BOOL bHasSignal)
{
    if( bHasSignal )
    {
        if( IsAVInUse()||IsSVInUse() )
        {
           BYTE NR_status;
           static BYTE PreNR_status=0;

            NR_status = MApi_AUDIO_GetCommAudioInfo(Audio_Comm_infoType_getNR_Status);

            if(PreNR_status!=NR_status)
            {
                if(!NR_status)
                {
                    PreNR_status=NR_status;
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_INTERNAL_1_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                    printf("NRenable=%d\n",(MS_U32)(MApi_AUDIO_GetCommAudioInfo(Audio_Comm_infoType_getNR_Status) ));
                }
                else
                {
                    PreNR_status=NR_status;
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_INTERNAL_1_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                    printf("NRenable=%d\n",(MS_U32)(MApi_AUDIO_GetCommAudioInfo(Audio_Comm_infoType_getNR_Status) ));
                }
            }
        }
    }
    else
    {
        // nothing
    }
}
#endif

// This function should only called once for VD std change
static void _MApp_ATVProc_NotifyToMainSystem(SCALER_WIN eWindow)
{
    BOOLEAN bIsTuningProcessorBusy;
  #if (TV_FREQ_SHIFT_CLOCK)
    //static U8 u8VDNoSyncCount =0 ;//fixed has garbage strongly when power on in ATV source when has signal
  #endif
    BOOL bVDHasSignal = IsVDHasSignal();


#if ( DEBUG_CHG_SRC_TIME)
    //printf("  Noti-1 %u\n", g_Debug_u32Time_ChangeSrc);
    msDebug_PrintChgSrcTime("Noti-1");
#endif

    if( _MApp_ATVProc_IsVideoSourceActive(eWindow) == FALSE )
    {
        return;
    }

    bIsTuningProcessorBusy = msAPI_Tuner_IsTuningProcessorBusy();


    // Send Signal Information.
    if( bVDHasSignal == TRUE )
    {
        debugTVAVHandlerPrint("Send Message - Change Signal Info - Sync OK",0);

      #if (TV_FREQ_SHIFT_CLOCK)
        if (IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(eWindow)))
        {
            //u8VDNoSyncCount =0;
            msAPI_Tuner_Patch_TVShiftClk(ENABLE);
        }
      #endif
    }
    else
    {
        debugTVAVHandlerPrint("Send Message - Change Signal Info - No Sync",0);
#if 0//( CHAKRA3_AUTO_TEST )
        if (g_AT_bChangeSource)	//for no signal
        {
            MApp_AT_SendEvent( E_AT_EVENT_CHANGE_SOURCE_NO_SIGNAL, (void*)msAPI_Timer_GetTime0());
        }
#endif

    #if (TV_FREQ_SHIFT_CLOCK)
        if (IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(eWindow)))
        {
            //if (!MDrv_AVD_IsSyncLocked())//fixed Blink alway when search one program
            {
                //u8VDNoSyncCount ++;
                //if(u8VDNoSyncCount>8)
                {
                    //u8VDNoSyncCount = 0;
                    msAPI_Tuner_Patch_TVShiftClk(DISABLE);
                }
            }
        }
        else
        {
            msAPI_Tuner_Patch_ResetTVShiftClk();
        }
    #endif

    #if (ENABLE_PIP)
        if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
        {
            if( SYS_SCREEN_SAVER_TYPE(SUB_WINDOW) == EN_SCREENSAVER_NOSIGNAL || SYS_SCREEN_SAVER_TYPE(SUB_WINDOW) == EN_SCREENSAVER_NOSYNC || SYS_SCREEN_SAVER_TYPE(SUB_WINDOW) == EN_SCREENSAVER_NOSYNC_VD)
            {
                //power saving TO DO : wait for API from ken.chang
            }
        }
    #endif

    #if 0//ENABLE_ATV_MODE_SHOW_NO_SIGNAL
        if(IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(eWindow)))
        {
            SYS_SCREEN_SAVER_TYPE(eWindow) = EN_SCREENSAVER_NOSYNC_VD;
        }
        if (MApp_ZUI_GetActiveOSD() == E_OSD_SCREEN_SAVER)
        {
            MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_ALL);
        }
        else if (MApp_ZUI_GetActiveOSD() == E_OSD_EMPTY)
        {
            MApp_ZUI_ACT_StartupOSD(E_OSD_SCREEN_SAVER);
        }
    #endif
    }

#if ENABLE_NO_AUDIO_INPUT_AUTO_MUTE
    _MApp_ATVProc_NO_AUDIO_INPUT_AUTO_MUTE(bVDHasSignal);
#endif

    // Video frequency is changed. So mode handler will change mode.
    //if( TRUE == msAPI_AVD_IsVideoFormatChanged()&&(msAPI_AVD_Is_VDStable()) )
    {
        AVD_VideoStandardType eVideoStandard;

        //msAPI_AVD_SetIsVideoFormatChangedAsFalse();//20100330EL

        eVideoStandard = msAPI_AVD_GetVideoStandard();
        if (MApp_ZUI_GetActiveOSD() == E_OSD_ATV_MANUAL_TUNING)
        {
            MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_UPDATE_SIGNAL_INFORMAT);
        }

      #if 1
        switch( eVideoStandard )
        {
            case E_VIDEOSTANDARD_PAL_BGHI:  mvideo_vd_set_videosystem(SIG_PAL);       break;
            case E_VIDEOSTANDARD_NTSC_M:    mvideo_vd_set_videosystem(SIG_NTSC);      break;
            case E_VIDEOSTANDARD_SECAM:     mvideo_vd_set_videosystem(SIG_SECAM);     break;
            case E_VIDEOSTANDARD_NTSC_44:   mvideo_vd_set_videosystem(SIG_NTSC_443);  break;
            case E_VIDEOSTANDARD_PAL_M:     mvideo_vd_set_videosystem(SIG_PAL_M);     break;
            case E_VIDEOSTANDARD_PAL_N:     mvideo_vd_set_videosystem(SIG_PAL_NC);    break;
            case E_VIDEOSTANDARD_PAL_60:    mvideo_vd_set_videosystem(SIG_NTSC_443);  break;
            default:                        mvideo_vd_set_videosystem(SIG_PAL);       break;
        }
      #endif

      #if (TV_FREQ_SHIFT_CLOCK)
        msAPI_AVD_ShiftClk((AVD_ATV_CLK_TYPE)g_u8_ShiftClk_LastMode);
      #endif

#if SPEEDUP_BRAZIL_ATV_SCAN
        if(bIsTuningProcessorBusy == FALSE)
#endif
        {
            MApp_VD_SetMode(eWindow);
        }

    #if( ENABLE_TTX && ENABLE_TTX_ANALOG )
        msAPI_TTX_SetVideoStandard(eVideoStandard);
    #endif

    #if (ENABLE_PIP)
        if( (MApp_Get_PIPMode() == EN_PIP_MODE_OFF) || UI_IS_AUDIO_SOURCE_IN(eWindow) )
    #endif
        {
            if ( MApi_XC_IsBlackVideoEnable(MAIN_WINDOW) )
            {
                ;
            }
            else
            {
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            }
        }

    #if ENABLE_IP_AUTO_COAST
        MApi_XC_EnableIPCoastDebounce();
    #endif
    }

#if 0//(PATCH_FOR_V_RANGE)
    if(IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(eWindow)))
        MApp_VD_StartRangeHandle();
#endif

}

EN_ATV_SYSTEM_TYPE MApp_ATVProc_GetAudioSystem(AUDIOSTANDARD_TYPE eAudioStandard)
{
#if ( ENABLE_DVB_TAIWAN_APP || (TV_SYSTEM == TV_NTSC) )
    EN_ATV_SYSTEM_TYPE u8AudioSystem=EN_ATV_SystemType_M;
#elif (ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP)
    EN_ATV_SYSTEM_TYPE u8AudioSystem=EN_ATV_SystemType_DK;
#else
    EN_ATV_SYSTEM_TYPE u8AudioSystem;

    #if ENABLE_SBTVD_ATV_SYSTEM
    if(IS_SBTVD_APP)
    {
        u8AudioSystem = EN_ATV_SystemType_M;
    }
    else
    #endif
    {
        u8AudioSystem = EN_ATV_SystemType_DK;//EN_ATV_SystemType_BG;
    }
#endif

    switch (eAudioStandard)
    {
        case E_AUDIOSTANDARD_BG:
        case E_AUDIOSTANDARD_BG_A2:
        case E_AUDIOSTANDARD_BG_NICAM:
            u8AudioSystem = EN_ATV_SystemType_BG;
            break;

        case E_AUDIOSTANDARD_I:
            u8AudioSystem = EN_ATV_SystemType_I;
            break;

        case E_AUDIOSTANDARD_DK:
        case E_AUDIOSTANDARD_DK1_A2:
        case E_AUDIOSTANDARD_DK2_A2:
        case E_AUDIOSTANDARD_DK3_A2:
        case E_AUDIOSTANDARD_DK_NICAM:
            u8AudioSystem = EN_ATV_SystemType_DK;
            break;

    #if ( ENABLE_DTMB_CHINA_APP || ENABLE_DVB_TAIWAN_APP || ENABLE_ATV_CHINA_APP || ENABLE_SBTVD_ATV_SYSTEM || ENABLE_DVBC_PLUS_DTMB_CHINA_APP || (TV_SYSTEM == TV_NTSC) )
        case E_AUDIOSTANDARD_M:
        case E_AUDIOSTANDARD_M_BTSC:
        case E_AUDIOSTANDARD_M_A2:
        case E_AUDIOSTANDARD_M_EIA_J:
            u8AudioSystem = EN_ATV_SystemType_M;
            break;
    #endif

        case E_AUDIOSTANDARD_L:
            u8AudioSystem = EN_ATV_SystemType_L;
            break;

        default:
            break;
    }

    return  u8AudioSystem;
}


