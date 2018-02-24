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
#define MAPP_CHANNEL_CHANGE_C

//------------------------------------------------------------------------------
//                    Header Files
//------------------------------------------------------------------------------
#include <string.h>
#include <stdio.h>


#include "MsCommon.h"

#include "Board.h"
#include "debug.h"
#include "msAPI_Global.h"

#include "datatype.h"
#include "msAPI_Timer.h"
#include "msAPI_Video.h"
#include "msAPI_audio.h"
#include "apiAUDIO.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "apiXC_Sys.h"
#include "apiXC_PCMonitor.h"
#include "msAPI_MIU.h"
#include "msAPI_Tuner.h"
#include "msAPI_Memory.h"        //PAT/PMT Parsing when ch change
#include "msAPI_IR.h"
#include "msAPI_ATVSystem.h"
#include "msAPI_VD.h"
#include "msAPI_Tuning.h"
#if(ENABLE_CI)
#include "msAPI_CI.h"
#endif
#include "MApp_Init.h"

#if ENABLE_OAD
#include "MApp_OAD.h"
#endif

#include "MApp_VDMode.h"
//#include "MApp_UiMenuVChip.h"
#include "MApp_PCMode.h"
#include "MApp_Exit.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalVar.h"
#include "MApp_Key.h"
#include "MApp_GlobalFunction.h"
#include "MApp_Audio.h"
#include "MApp_SignalMonitor.h"
#include "MApp_InputSource.h"
#include "MApp_MVDMode.h"
#include "MApp_DataBase.h"
#include "MApp_Scaler.h"
#if(ENABLE_DVB)
#include "MApp_Dvb_SI.h" // "mapp_si.h"
#endif

#if (ENABLE_OAD)
#include "MApp_OAD.h"
#endif  //ENABLE_OAD
#include "MApp_Scan.h"
#include "MApp_ChannelChange.h"
#include "MApp_ChannelList.h"
#include "MApp_TV.h"
#include "MApp_IR.h"
#include "MApp_Font.h"
#include "MApp_BlockSys.h"
#include "MApp_Main.h"
#include "MApp_AnalogInputs.h"
#include "MApp_MultiTasks.h"
#if ENABLE_DVB_T2
#include "demodulator_T2.h"
#endif

#if (ENABLE_SUBTITLE)
#include "MApp_Subtitle.h"
#endif

#include "msAPI_ChProc.h"
#include "MApp_ATVProc.h"
#include "msAPI_FreqTableDTV.h"
#include "msAPI_DTVSystem.h"
#include "MApp_TopStateMachine.h"
#if ENABLE_TTX
#include "msAPI_TTX.h"
#include "mapp_ttx.h"
#endif

#if (ENABLE_DTV_EPG)
#include "mapp_eit.h"
#endif

#include "drvCPU.h"

#if MHEG5_ENABLE
#include "msAPI_MHEG5.h"
#endif

#if ENABLE_ATSC_TTS
#include "MApp_TTSControlHandler.h"
#endif

#if ((BRAZIL_CC)||(ATSC_CC == ATV_CC))
#include "mapp_closedcaption.h"
#include "MApp_VChip.h"
#endif

#if ENABLE_PVR
#include "MApp_Playback.h"
#include "MApp_Record.h"
#endif
//#include "MApp_ZUI_Main.h"

#if MHEG5_ENABLE
#include "MApp_MHEG5_Main.h"
#include "mapp_eit.h"
static U16 g_u16Current_ServicePosition;
#endif


#if(ENABLE_S2)
#include "apiDTVSatTable.h"
#include "apiDigiTuner.h"
#endif

#if ENABLE_CI
#include "msAPI_CI.h"
#include "MApp_CIMMI.h"
#endif

#if (ENABLE_PIP)
#include "MApp_PIP.h"
#endif

#if ENABLE_ATSC
#include "MApp_ZUI_ACTchannelinfo_ATSC.h"
#endif

#if (AV_SYNC_ADJUST)
#include "MApp_AVSync.h"
#endif

#include "MApp_SDT_Monitor.h"
#include "MApp_ParentalRating.h"
//---------------------------------
// TODO:  Remove these...
#include "MApp_ZUI_Main.h"
#include "ZUI_tables_h.inl"
#include "ZUI_exefunc.h"
//---------------------------------

#if ENABLE_KEY_TO_SPEECH
#include "MApp_KeyToSpeech.h"
#endif

//
//******************************************************************************
//

extern BOOLEAN bCheckBlockPW;
extern BOOLEAN bCheckParentalPW;
//extern U8 g_ParentalRating_u8PreParental_Control;
extern BOOLEAN bStopMonitorBlock;
extern BOOLEAN g_PIDfromMHEG5;
extern U16 g_u16MHEG5_VideoPID;
extern U16 g_u16MHEG5_AudioPID;

#if ENABLE_AUTOTEST
extern BOOLEAN g_bAutobuildDebug;
#endif

#if (CHANNEL_SCAN_AUTO_TEST)
extern MS_TP_SETTING stTpSettingPC;
#endif

BOOLEAN bParentalPWPassCheck = FALSE;

#if(ENABLE_S2)
extern DTVPROGRAMID_M _astS2ProgramIDTable[MAX_DTV_S2_MUX_NUMBER];
extern BOOLEAN _GetSatInforByID(MS_U8 u8SATId,MS_SAT_PARAM *pSATParam);
DTVPROGRAMID_M g_stCurS2ProggramId; //TP;
#endif

/******************************************************************************/
/*                     Macro                    */
/******************************************************************************/

#define CHANNELCHANGE_DBINFO(y)     //y

#define ENABLE_CH_CHANGE_TIMER_DEBUG    0

#define DEBUG_ENABLE_CHANNEL(x)     //x
#define DEBUG_ENABLE_AV(x)          //x


#if (ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP)
#define DELAY_FOR_STABLE_CHANNELCHANGE  800
#else
#define DELAY_FOR_STABLE_CHANNELCHANGE  300
#endif


/******************************************************************************/
//                     Local
/******************************************************************************/
static BOOLEAN g_ChChg_bInFunc_EnableChannel = 0;

static EN_CHANNELCHANGE_STATE enChannelChangeState = STATE_CHANNELCHANGE_INIT;
static EN_RET enChannelChangeRetVal;

static U32 u32ChannelChangeTimer;
static BOOLEAN fWaitforMSGBoxFading;
#if MHEG5_ENABLE
static BOOLEAN _bBackDataProgram=FALSE;
#endif

#if (ENABLE_CH_CHANGE_TIMER_DEBUG == 1)
U32 g_u32ChannelChangeTimer1,
    g_u32ChannelChangeTimer2,
    g_u32ChannelChangeTimer3,
    g_u32ChannelChangeTimer4,
    g_u32ChannelChangeTimer5;

void Debug_ChannelChangeTimer(void)
{
    g_u32ChannelChangeTimer5 = msAPI_Timer_GetTime0();

    //pstVirtualCh = MApp_ChanProc_GetCurChannelPointer();


    CHANNELCHANGE_DBINFO(printf("\n"));
    //printf("CH change to %u-%u\n", pstVirtualCh->stCHAttribute.major_num, pstVirtualCh->stCHAttribute.minor_num);
    CHANNELCHANGE_DBINFO(printf("disable ch S~E = %lu\n", (g_u32ChannelChangeTimer2 - g_u32ChannelChangeTimer1)));
    CHANNELCHANGE_DBINFO(printf("disable ch E ~ enable ch S = %lu\n", (g_u32ChannelChangeTimer3 - g_u32ChannelChangeTimer2)));
    CHANNELCHANGE_DBINFO(printf("enable ch S~E = %lu\n", (g_u32ChannelChangeTimer4 - g_u32ChannelChangeTimer3)));
    CHANNELCHANGE_DBINFO(printf("enable ch E ~ enable scaler = %lu\n", (g_u32ChannelChangeTimer5 - g_u32ChannelChangeTimer4)));
    CHANNELCHANGE_DBINFO(printf("total time =  %lu\n", (g_u32ChannelChangeTimer5 - g_u32ChannelChangeTimer1)));
}
#endif

/*********************************************************************************/
/*                  Functions                        */
/*********************************************************************************/

void MApp_ChannelChange_VariableInit ( void )
{
    enChannelChangeState = STATE_CHANNELCHANGE_INIT;

    g_eCurrentUserServiceType=E_SERVICETYPE_INVALID;
}



static BOOLEAN MApp_ChannelChange_KeyRepeatDelay( void )
{
    if(MApp_KeyIsReapeatStatus())
    {
        if(msAPI_Timer_DiffTimeFromNow(u32ChannelChangeTimer)<=CHANNEL_CHANGE_KEY_REPEAT_DELAY)
        {
            #if ENABLE_KEY_TO_SPEECH
            if(MApp_KTS_IsAudioFinished())
                MApp_KTS_Stop();
            #endif
            u8KeyCode = KEY_NULL;
            return TRUE;
        }
    }
    return FALSE;
}

extern void MApp_ZUI_ACT_ResetInfoTimer(void);

static void MApp_ChannelChange_ProcessUserInput( void )
{
#if ENABLE_SBTVD_DTV_SYSTEM
    U16 u16CurOridinal,u16NextOridinal,u16NextPosition = INVALID_PROGRAM_POSITION;
    U16 u16NetProNum,u16CurOridinal2;
    MEMBER_SERVICETYPE bNextServiceType = E_SERVICETYPE_INVALID;
    E_UI_INPUT_SOURCE ePreInput_Source_Type;
#endif

    if(u8KeyCode == KEY_CHANNEL_PLUS || u8KeyCode == KEY_CHANNEL_MINUS)
    {
        MApp_ZUI_ACT_ResetInfoTimer();

    #if ENABLE_SBTVD_DTV_SYSTEM
        if(msAPI_SRC_IS_SBTVD_InUse())
        {
            dmSetLastWatchedOrdinal();

            if (ANT_AIR == msAPI_ATV_GetCurrentAntenna())
            {
                u16CurOridinal = msAPI_CHPROC_CM_GetCurrentOrdinal(E_SERVICETYPE_UNITED_TV,E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                u16CurOridinal2 = u16CurOridinal;

                if(u8KeyCode == KEY_CHANNEL_PLUS)
                {
                    do
                    {
                        u16NextOridinal = msAPI_CHPROC_CM_GetNextOrdinal(E_SERVICETYPE_UNITED_TV,u16CurOridinal,FALSE);
                        if(u16NextOridinal == INVALID_ORDINAL)
                            break;

                        u16CurOridinal=u16NextOridinal;
                        msAPI_CHPROC_CM_GetOrdinal_SerType_Position_Brazil(u16NextOridinal,&bNextServiceType,&u16NextPosition);
                        if(bNextServiceType == E_SERVICETYPE_ATV)
                        {
                            u16NetProNum = (u16NextPosition>>8);
                            if (FALSE == msAPI_ATV_IsProgramSkipped(u16NetProNum))
                            {
                                break;
                            }
                        }
                        else if(bNextServiceType == E_SERVICETYPE_DTV)
                        {
                             if(FALSE == msAPI_CM_GetProgramAttribute(E_SERVICETYPE_DTV,u16NextPosition,E_ATTRIBUTE_IS_SKIPPED))
                             {
                                break;
                             }
                        }
                        else
                        {
                            if(bNextServiceType == E_SERVICETYPE_RADIO)
                            {
                                if(FALSE == msAPI_CM_GetProgramAttribute(E_SERVICETYPE_RADIO,u16NextPosition,E_ATTRIBUTE_IS_SKIPPED))
                                    break;
                            }
                        }
                     }while(u16NextOridinal != u16CurOridinal2);
                }
                else //if(u8KeyCode == KEY_CHANNEL_MINUS)
                {
                    do
                    {
                        u16NextOridinal = msAPI_CHPROC_CM_GetPrevOrdinal(E_SERVICETYPE_UNITED_TV,u16CurOridinal,FALSE);
                        if(u16NextOridinal == INVALID_ORDINAL)
                            break;
                        u16CurOridinal=u16NextOridinal;
                        msAPI_CHPROC_CM_GetOrdinal_SerType_Position_Brazil(u16NextOridinal,&bNextServiceType,&u16NextPosition);
                        if(bNextServiceType==E_SERVICETYPE_ATV)
                        {
                            u16NetProNum = (u16NextPosition>>8);
                            if (FALSE == msAPI_ATV_IsProgramSkipped(u16NetProNum))
                            {
                                break;
                            }
                        }
                        else if(bNextServiceType == E_SERVICETYPE_DTV)
                        {
                            if(FALSE == msAPI_CM_GetProgramAttribute(E_SERVICETYPE_DTV,u16NextPosition,E_ATTRIBUTE_IS_SKIPPED))
                            {
                                break;
                            }
                        }
                        else
                        {
                            if(bNextServiceType == E_SERVICETYPE_RADIO)
                            {
                                if(FALSE == msAPI_CM_GetProgramAttribute(E_SERVICETYPE_RADIO,u16NextPosition,E_ATTRIBUTE_IS_SKIPPED))
                                    break;
                            }
                        }
                    }while(u16NextOridinal != u16CurOridinal2);
                }

                if(u16NextOridinal != INVALID_ORDINAL)
                {
                    msAPI_CHPROC_CM_GetOrdinal_SerType_Position_Brazil(u16NextOridinal,&bNextServiceType,&u16NextPosition);

                    ePreInput_Source_Type = UI_INPUT_SOURCE_TYPE;

                    if(bNextServiceType == E_SERVICETYPE_ATV)
                        UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ATV;
                    else
                        UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ISDBT;

                    if(ePreInput_Source_Type != UI_INPUT_SOURCE_TYPE)
                    {

                        MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);
                        MApp_InputSource_SwitchSource( UI_INPUT_SOURCE_TYPE, MAIN_WINDOW );
                        enChannelChangeState = STATE_CHANNELCHANGE_INIT;//resolve Mantis 0355646
                    }
                 }
            }
        }
    #endif

    #if (ENABLE_CI && MEDIASET_PREMIUM_SMART_CAM)
        if ( IsDTVInUse() )
        {
            msAPI_CI_HSS_Active(TRUE);
        }
    #endif
    }

    switch ( u8KeyCode )
    {
        case KEY_CHANNEL_PLUS:

            if ( MApp_ChannelChange_KeyRepeatDelay() || enChannelChangeState == STATE_CHANNELCHANGE_SHOWINFO)
            {
                u8KeyCode = KEY_NULL;
                break;
            }

            CHANNELCHANGE_DBINFO( printf( "KEY_CHANNEL_PLUS \n" ) );
            CHANNELCHANGE_DBINFO( printf( "IsSrcTypeDTV=%bx \n", IsSrcTypeDTV( SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW) ) ) );
        #if ENABLE_DVB
            if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
                #if (ENABLE_PIP)
                || ((MApp_Get_PIPMode() != EN_PIP_MODE_OFF) && IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
                #endif
                )
            {
                MEMBER_SERVICETYPE bServiceType,bNewServiceType;
                WORD wNextProgramPosition;

              #if ENABLE_SBTVD_DTV_SYSTEM
                if(msAPI_SRC_IS_SBTVD_InUse())
                {
                    bNewServiceType = bNextServiceType;
                    bServiceType = E_SERVICETYPE_INVALID;
                    wNextProgramPosition = u16NextPosition;
                }
                else
              #endif
                {
                    bNewServiceType = bServiceType = msAPI_CM_GetCurrentServiceType();
                    wNextProgramPosition = msAPI_CM_GetNextProgramPosition(bServiceType, msAPI_CM_GetCurrentPosition(bServiceType), FALSE, E_ALL_LIST,&bNewServiceType);
                }
                if( wNextProgramPosition != INVALID_PROGRAM_POSITION )
                {

                    #if(ENABLE_SBTVD_DTV_SYSTEM)
                      if(!msAPI_SRC_IS_SBTVD_InUse())
                    #endif
                    {
                        dmSetLastWatchedOrdinal();
                    }

                    //Cancel Freeze
                    if(g_bIsImageFrozen)
                    {
                        g_bIsImageFrozen = FALSE;
                        MApi_XC_FreezeImg(g_bIsImageFrozen, MAIN_WINDOW);
                    }

                    if(bNewServiceType != bServiceType)
                    {
                        bServiceType = bNewServiceType;
                        msAPI_CM_SetCurrentServiceType(bNewServiceType);
                    }

                    msAPI_CM_SetCurrentPosition(bServiceType, wNextProgramPosition);
                #if ENABLE_CI_PLUS
                    if(TRUE == MApp_CI_IsOpMode())
                    {
                        DB_CI_PLUS_SETTING.u16OpChannelIdex = wNextProgramPosition;
                    }
                #endif

                    if ( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) )
                    {
                        MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);
                    }

                  #if (ENABLE_PIP)
                    if(IsPIPSupported())
                    {
                        if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) )
                            MApp_ChannelChange_DisableChannel(TRUE,SUB_WINDOW);
                    }
                  #endif

                    stGenSetting.stScanMenuSetting.u8RFChannelNumber= msAPI_CM_GetPhysicalChannelNumber(bServiceType, wNextProgramPosition);

                    enChannelChangeState = STATE_CHANNELCHANGE_DISPLAY;
                }
            }
            else
        #endif // #if ENABLE_DVB
            {
                if( msAPI_ATV_GetCurrentProgramNumber() == msAPI_ATV_GetNextProgramNumber(msAPI_ATV_GetCurrentProgramNumber(), FALSE) )
                {
                    u8KeyCode = KEY_NULL;
                    return;
                }

              #if ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_ATV_SYSTEM || (TV_SYSTEM == TV_NTSC) )
                    msAPI_ATV_SetDirectTuneFlag(TRUE);
              #endif

                #if(ENABLE_SBTVD_DTV_SYSTEM)
                if(!msAPI_SRC_IS_SBTVD_InUse())
                #endif
                {
                    dmSetLastWatchedOrdinal();
                }


              #if ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_ATV_SYSTEM || (TV_SYSTEM == TV_NTSC) )
                  msAPI_ATV_SetDirectTuneFlag(FALSE);
              #endif

                if( IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) )
                    MApp_ChannelChange_DisableAV(MAIN_WINDOW);

              #if (ENABLE_PIP)
                if(IsPIPSupported())
                {
                    if( IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) )
                        MApp_ChannelChange_DisableAV(SUB_WINDOW);
                }
              #endif

                //Cancel Freeze
                if(g_bIsImageFrozen)
                {
                    g_bIsImageFrozen = FALSE;
                    MApi_XC_FreezeImg(g_bIsImageFrozen, MAIN_WINDOW);
                }


                #if(ENABLE_SBTVD_ATV_SYSTEM)
                    if((msAPI_SRC_IS_SBTVD_InUse())&&(ANT_AIR == msAPI_ATV_GetCurrentAntenna()))
                    {
                        msAPI_ATV_SetCurrentProgramNumber(u16NextPosition >> 8);
                    }
                    else
                #endif
                    msAPI_ATV_SetCurrentProgramNumber(msAPI_ATV_GetNextProgramNumber(msAPI_ATV_GetCurrentProgramNumber(), FALSE));

                //BY 20090406 msAPI_VD_AdjustVideoFactor(E_ADJUST_VIDEOMUTE_DURING_LIMITED_TIME, DELAY_FOR_STABLE_TUNER);

                msAPI_AVD_TurnOffAutoAV();
                msAPI_Tuner_ChangeProgram();
                //msAPI_VD_ClearSyncCheckCounter();
                msAPI_AVD_ClearAspectRatio();

                MApp_CheckBlockProgramme();        // 070711_SK_1 block programme
                enChannelChangeState = STATE_CHANNELCHANGE_DISPLAY;
#if ENABLE_KEY_TO_SPEECH
            if(!MApp_KeyIsReapeatStatus())
                MApp_KTS_Say(EN_KTS_CHANNEL_UP);
#endif
            }
            u8KeyCode = KEY_NULL;
            break;


        case KEY_CHANNEL_MINUS:
            if ( MApp_ChannelChange_KeyRepeatDelay() || enChannelChangeState == STATE_CHANNELCHANGE_SHOWINFO)
            {
                u8KeyCode = KEY_NULL;
                break;
            }

            CHANNELCHANGE_DBINFO(printf("KEY_CHANNEL_MINUS \n"));
            CHANNELCHANGE_DBINFO( printf( "IsSrcTypeDTV=%bx \n", IsSrcTypeDTV( SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW) ) ) );
        #if ENABLE_DVB
            if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
              #if (ENABLE_PIP)
                || ((MApp_Get_PIPMode() != EN_PIP_MODE_OFF) && IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
              #endif
              )
            {
                MEMBER_SERVICETYPE bServiceType,bNewServiceType;
                WORD wPrevProgramPosition;


#if ENABLE_SBTVD_DTV_SYSTEM
                  if(msAPI_SRC_IS_SBTVD_InUse())
                  {
                      bNewServiceType = bNextServiceType;
                      bServiceType = E_SERVICETYPE_INVALID;
                      wPrevProgramPosition = u16NextPosition;
                  }
                  else
#endif
                  {
                      bNewServiceType = bServiceType = msAPI_CM_GetCurrentServiceType();
                      wPrevProgramPosition = msAPI_CM_GetPrevProgramPosition(bServiceType, msAPI_CM_GetCurrentPosition(bServiceType), FALSE, E_ALL_LIST,&bNewServiceType);
                  }

                if( wPrevProgramPosition != INVALID_PROGRAM_POSITION )
                {

#if(ENABLE_SBTVD_DTV_SYSTEM)
                  if(!msAPI_SRC_IS_SBTVD_InUse())
#endif
                    {
                        dmSetLastWatchedOrdinal();
                    }

                    //Cancel Freeze
                    if(g_bIsImageFrozen)
                    {
                        g_bIsImageFrozen = FALSE;
                        MApi_XC_FreezeImg(g_bIsImageFrozen, MAIN_WINDOW);
                    }

                    if(bNewServiceType != bServiceType)
                    {
                        msAPI_CM_SetCurrentServiceType(bNewServiceType);
                        bServiceType = bNewServiceType;
                    }

                    msAPI_CM_SetCurrentPosition(bServiceType, wPrevProgramPosition);
                #if ENABLE_CI_PLUS
                    if(TRUE == MApp_CI_IsOpMode())
                    {
                        DB_CI_PLUS_SETTING.u16OpChannelIdex = wPrevProgramPosition;
                    }
                #endif
                    if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) )
                        MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);
                    #if (ENABLE_PIP)
                    if(IsPIPSupported())
                    {
                        if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) )
                            MApp_ChannelChange_DisableChannel(TRUE,SUB_WINDOW);
                    }
                    #endif
                    stGenSetting.stScanMenuSetting.u8RFChannelNumber= msAPI_CM_GetPhysicalChannelNumber(bServiceType, wPrevProgramPosition);

                    enChannelChangeState = STATE_CHANNELCHANGE_DISPLAY;
                }
            }
            else
        #endif
            {
                if( msAPI_ATV_GetCurrentProgramNumber() == msAPI_ATV_GetPrevProgramNumber(msAPI_ATV_GetCurrentProgramNumber(), FALSE) )
                {
                    u8KeyCode = KEY_NULL;
                    return;
                }

                #if ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_ATV_SYSTEM || (TV_SYSTEM == TV_NTSC) )
                    msAPI_ATV_SetDirectTuneFlag(TRUE);
                #endif
                    #if(ENABLE_SBTVD_DTV_SYSTEM)
                    if(!msAPI_SRC_IS_SBTVD_InUse())
                    #endif
                    {
                        dmSetLastWatchedOrdinal();
                    }

                #if ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_ATV_SYSTEM || (TV_SYSTEM == TV_NTSC) )
                    msAPI_ATV_SetDirectTuneFlag(TRUE);
                #endif

                if( IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) )
                    MApp_ChannelChange_DisableAV(MAIN_WINDOW);
                  #if (ENABLE_PIP)
                if(IsPIPSupported())
                {
                    if( IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) )
                        MApp_ChannelChange_DisableAV(SUB_WINDOW);
                }
                  #endif

                //Cancel Freeze
                if(g_bIsImageFrozen)
                {
                    g_bIsImageFrozen = FALSE;
                    MApi_XC_FreezeImg(g_bIsImageFrozen, MAIN_WINDOW);
                }



#if(ENABLE_SBTVD_ATV_SYSTEM)
                  if((msAPI_SRC_IS_SBTVD_InUse())&&(ANT_AIR == msAPI_ATV_GetCurrentAntenna()))
                  {
                      msAPI_ATV_SetCurrentProgramNumber(u16NextPosition >> 8);
                  }
                  else
#endif
                    msAPI_ATV_SetCurrentProgramNumber(msAPI_ATV_GetPrevProgramNumber(msAPI_ATV_GetCurrentProgramNumber(), FALSE));

                //BY 20090406 msAPI_VD_AdjustVideoFactor(E_ADJUST_VIDEOMUTE_DURING_LIMITED_TIME, DELAY_FOR_STABLE_TUNER);
                msAPI_AVD_TurnOffAutoAV();
                msAPI_Tuner_ChangeProgram();
                //msAPI_VD_ClearSyncCheckCounter();
                msAPI_AVD_ClearAspectRatio();

                MApp_CheckBlockProgramme();        // 070711_SK_1 block programme
                enChannelChangeState = STATE_CHANNELCHANGE_DISPLAY;
#if ENABLE_KEY_TO_SPEECH
                if(!MApp_KeyIsReapeatStatus())
                    MApp_KTS_Say(EN_KTS_CHANNEL_DOWN);
#endif
            }
            u8KeyCode = KEY_NULL;
            break;


        case KEY_SELECT:
            fWaitforMSGBoxFading = FALSE;
            u8KeyCode = KEY_NULL;
            break;

        case KEY_NULL:
            break;

        default:
            fWaitforMSGBoxFading = FALSE;
            //** For CUS03L
            //u8KeyCode = KEY_NULL;
            break;
    }
}

/*********************************************************************************/
#define DISABLE_AV_TRACE()  //printf("DisableAV-%u at %u\n", __LINE__, MsOS_GetSystemTime() )

void MApp_ChannelChange_DisableAV( SCALER_WIN eWindow )
{
    DEBUG_ENABLE_AV( printf("MApp_ChannelChange_DisableAV(win=%u)\n", eWindow); );

    DISABLE_AV_TRACE();

#if ENABLE_TTX
  #if(0 == ENABLE_TTX_SHOW_OFF_SIGNAL)//Don't refresh TTX when AV mute
    MApp_TTX_Reflesh();
  #endif
#endif

    DISABLE_AV_TRACE();

    /* mute audio */
    // Amp_Mute_enable Flag turn on depend on Customer Amp Mute/unMute speed
#if (ENABLE_PIP)
    if ( ( (MApp_Get_PIPMode() == EN_PIP_MODE_OFF) && eWindow == MAIN_WINDOW )
       || UI_IS_AUDIO_SOURCE_IN(eWindow) )
#endif
    {
        if (IsATVInUse())
        {
            //msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE_DURING_LIMITED_TIME, DELAY_FOR_STABLE_SIF/*DELAY_FOR_CHANNELCHANGE*/, E_AUDIOMUTESOURCE_ATV);
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYSYNC_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
        }
        else
        {
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
        }

        DISABLE_AV_TRACE();
    }

    /* enable scaler free run */
#if ENABLE_DTV
    if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(eWindow)))
    {
        DISABLE_AV_TRACE();

        msAPI_Scaler_SetCVBSMute(ENABLE, E_VE_MUTE_GEN,SYS_INPUT_SOURCE_TYPE(eWindow),OUTPUT_CVBS1);
      #if (ENABLE_CVBSOUT_2)
        msAPI_Scaler_SetCVBSMute(ENABLE, E_VE_MUTE_GEN,SYS_INPUT_SOURCE_TYPE(eWindow),OUTPUT_CVBS2);
      #endif

        DISABLE_AV_TRACE();

        msAPI_Scaler_SetBlueScreen( ENABLE, E_XC_FREE_RUN_COLOR_BLACK, NULL, eWindow);
    }
    else
#endif
    {
        DISABLE_AV_TRACE();

      #if (ENABLE_SW_CH_FREEZE_SCREEN)
        if(IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(eWindow)) && stGenSetting.stTvSetting.u8SwitchMode == ATV_SWITCH_CH_FREEZE_SCREEN)
        {
            msAPI_Scaler_SetFreezeScreen(ENABLE, DEFAULT_SCREEN_FREEZE_TIME, eWindow);
        }
        else
      #endif
        {
            msAPI_Scaler_SetBlueScreen( ENABLE, E_XC_FREE_RUN_COLOR_BLACK, NULL, eWindow);
        }

        DISABLE_AV_TRACE();

    #if(PATCH_FOR_V_RANGE)
       if(IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(eWindow)))
           MApp_VD_RangeReset();
    #endif
    }

    DISABLE_AV_TRACE();
}

/*********************************************************************************/

void MApp_ChannelChange_EnableAV( void )
{
    DEBUG_ENABLE_AV( printf("MApp_ChannelChange_EnableAV()\n"); );

#if ENABLE_DTV
  #if (ENABLE_PIP)
    if ( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
        ||(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) && (MApp_Get_PIPMode() != EN_PIP_MODE_OFF)))
  #else

    if ( IsDTVInUse()
      #if(ENABLE_S2)
      || IsS2InUse()
      #endif
       )
  #endif
    {
        MApp_VID_VariableInit();
    }
#endif // #if ENABLE_DTV

#if ENABLE_ATSC // fix mantis 0905460
    if(IsATVInUse() || IsAVInUse())
    {
        // if switch to analog source, caption must bet set to 608
        if ( stGenSetting.g_CaptionSetting.u8CCMode == CAPTIONMENU_MODE_ON )
        {
            if ( IsDTVInUse() )
            {
                if (stGenSetting.g_CaptionSetting.u8CaptionServiceModeDTV!=CAPTIONMENU_SERVICE_OFF)
                {
                    stGenSetting.g_CaptionSetting.u8CaptionServiceMode = stGenSetting.g_CaptionSetting.u8CaptionServiceModeDTV;
                }
                else
                {
                    stGenSetting.g_CaptionSetting.u8CaptionServiceMode = stGenSetting.g_CaptionSetting.u8CaptionServiceModeATV;
                }
            }
            else
            {
                stGenSetting.g_CaptionSetting.u8CaptionServiceMode = stGenSetting.g_CaptionSetting.u8CaptionServiceModeATV;
            }
        }
    #if (PARSING_CC_WHENMUTE)
        else if (stGenSetting.g_CaptionSetting.u8CCMode == CAPTIONMENU_MODE_CC_WHEN_MUTE)
        {
            fEnableCCWhenMuteFunc = FALSE;
            stGenSetting.g_CaptionSetting.u8CaptionServiceMode = CS_OFF;
            MApp_ClosedCaption_GetUserCmd();
            if (MApp_Aud_GetMuteStatus())
            {
                fEnableCCWhenMuteFunc = TRUE;
                fEnableClosedCaptionFunc = TRUE;
            }
       }
    #endif
        MApp_ClosedCaption_GetUserCmd();
    }
#endif

}

void MApp_ChannelChange_Set_Audio_Decoder_System(WORD wAudType )
{
    /* set decoder system and reload firmware code */
    //MsOS_DelayTask(500);

    DEBUG_AU_LOAD_CODE( printf("wAudType=%u\n", wAudType); );

    switch(wAudType)
    {
        case  E_AUDIOSTREAM_MPEG:
            MApi_AUDIO_SetSystem(MSAPI_AUD_DVB_MPEG);
            break;

        case E_AUDIOSTREAM_AC3:
            MApi_AUDIO_SetSystem(MSAPI_AUD_DVB_AC3);
            break;

        case E_AUDIOSTREAM_AC3P:
            MApi_AUDIO_SetSystem(MSAPI_AUD_DVB_AC3P);
            break;

        case E_AUDIOSTREAM_MPEG4:
        case E_AUDIOSTREAM_AAC:
            MApi_AUDIO_SetSystem(MSAPI_AUD_DVB_AAC);
            break;

        case E_AUDIOSTREAM_MPEG_AD:
            MApi_AUDIO_SetSystem(MSAPI_AUD_DVB2_MPEG);
            break;

        case E_AUDIOSTREAM_AC3_AD:
            MApi_AUDIO_SetSystem(MSAPI_AUD_DVB2_AC3);
            break;

        case E_AUDIOSTREAM_AC3P_AD:
            MApi_AUDIO_SetSystem(MSAPI_AUD_DVB2_AC3P);
            break;

        case E_AUDIOSTREAM_AACP_AD:
            MApi_AUDIO_SetSystem(MSAPI_AUD_DVB2_AAC);
            break;

        case E_AUDIOSTREAM_DRA:
            MApi_AUDIO_SetSystem(MSAPI_AUD_DVB_DRA);
            break;

        default:
            break;
    }

    if( wAudType == E_AUDIOSTREAM_AC3
     || wAudType == E_AUDIOSTREAM_AC3P
     || wAudType == E_AUDIOSTREAM_AAC
     || wAudType == E_AUDIOSTREAM_MPEG4
      )
    {
        if(stGenSetting.g_SysSetting.fSPDIFMODE == 0)
        {
            MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
        }
        else
        {
            MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_NONPCM);
        }
    }
    else
    {
        MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
    }

    MApi_AUDIO_SetAC3Info(Audio_AC3_infoType_DrcMode, RF_MODE, 0);      //RF Mod
    MApi_AUDIO_SetAC3Info(Audio_AC3_infoType_DownmixMode, DOLBY_DOWNMIX_MODE_LTRT, 0);    //LtRt


    MApi_AUDIO_DTV_HDMI_CFG(FALSE);  // DTV mod set False
}

/*********************************************************************************/
void MApp_ChannelChange_DisableChannel (BOOLEAN u8IfStopDsmcc, SCALER_WIN eWindow /*U8 u8ChanBufIdx*/ ) //for change channel
{
    DEBUG_ENABLE_CHANNEL(printf("MApp_ChannelChange_DisableChannel(win=%u)\n", eWindow););
    BOOL bCloseMHEG5;
    bCloseMHEG5 = TRUE;

#if (!MHEG5_ENABLE)
    u8IfStopDsmcc = u8IfStopDsmcc; //for fixing compile warning
#endif

    MApp_Set_Audio_Mute_Timer(FALSE);


#if ENABLE_ATSC
    if(IsAtscInUse() || IsATVInUse())
    {
        MApp_ChannelChange_DisableChannel_ATSC();
        return;
    }
#endif

    if ( FALSE==fEnableSignalMonitor )
    {
        return;
    }

#if (ENABLE_CHCHANGETIME)
    printf("[ch change time]DisableChannel start = %ld\n", msAPI_Timer_DiffTimeFromNow(gU32ChChangeTime));
#endif

    //printf("MApp_ChannelChange_DisableChannel\n");
#if ENABLE_DVB //ENABLE_DTV
    if ( IsDTVInUse() )
    {
    #if ENABLE_PVR
        if (MApp_PVR_IsPlaybacking())
        {
            MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_CLOSE, 0);
        }

        if (!((E_PVR_STATE_RECORD == MApp_PVR_StateMachineGet() || E_PVR_STATE_RECORDnPLAYBACK == MApp_PVR_StateMachineGet()) &&
            (E_RECORD_STATE_RECORDING == MApp_Record_StateMachineGet())))
        {
            MApp_PVR_StateMachineInput(E_PVR_INPUT_RECORD_CLOSE,   0);
        }
    #endif

    #if ENABLE_CI_PLUS_V1_4
        if (TRUE == MApp_CI_IsHcKeepAppRunning())
        {
            bCloseMHEG5 = FALSE;
            printf("[CI+][HC][MHEG] Keep App Running \n");
        }
        else
        {
            bCloseMHEG5 = TRUE;
            printf("[CI+][MHEG] Close MHEG5 \n");
        }
    #endif

    #if ENABLE_CI
        if ( u8IfStopDsmcc && bCloseMHEG5 )
        {
            // Fix Ziggo HC V2 tune_request
            const U8 u8AbortReqCode[1] = {EN_APPMMI_ABORT_CODES_SYSTEM_CANCEL};
            msAPI_CI_AppMmi_AbortReq(u8AbortReqCode, 1);
         }
    #endif

    #if MHEG5_ENABLE
        if ( u8IfStopDsmcc && bCloseMHEG5 )
        {
             MApi_MHEG5_Disable(EN_MHEG5_DM_DISABLE_AND_STOPDSMCC);
        }
    #endif

    #if ENABLE_TTX
        if ( u8IfStopDsmcc && bCloseMHEG5)
        {
            if ( *MApp_Dmx_GetFid(EN_TTX_FID) != MSAPI_DMX_INVALID_FLT_ID )
            {
                // when change channel, close previous TTX pid filter
                msAPI_TTX_VBIAcquireEnable(FALSE);
                msAPI_TTX_SetTTXFid(MSAPI_DMX_INVALID_FLT_ID);
                msAPI_DMX_CloseFilter( *MApp_Dmx_GetFid(EN_TTX_FID));
                MApp_Dmx_SetFid(MSAPI_DMX_INVALID_FLT_ID, EN_TTX_FID);
                MApp_TTX_Reflesh();
            }
        }

        MApp_TTX_SetDefaultTTX_PID(MSAPI_DMX_INVALID_PID);
        MApp_TTX_TeletextCommand(TTX_TV);
    #endif // #if ENABLE_TTX

      #if ENABLE_SUBTITLE
        if ( u8IfStopDsmcc && bCloseMHEG5 )
        {
            MApp_Subtitle_Force_Exit();
        }
      #endif
    }
#endif // #if ENABLE_DVB

#if (BRAZIL_CC)
    #if(ENABLE_SBTVD_DTV_SYSTEM)
    if(msAPI_SRC_IS_SBTVD_InUse())
    #endif
    {
        if( ( (IsDTVInUse()||IsS2InUse() )
             && DB_CC_SETTING.enDTVCaptionType != DTV_CAPTION_OFF
             )
           ||(IsATVInUse() && DB_CC_SETTING.enATVCaptionType != ATV_CAPTION_TYPE_OFF))
        {
            if(MApp_CC_GetInfo(CC_SELECTOR_STATUS_CODE) == STATE_CAPTION_PARSER)
            {
                MApp_CC_StopParser();
                MApp_Dmx_PES_Stop();
            }
        }
    }
#elif (ATSC_CC == ATV_CC)
    if ((IsATVInUse() && DB_CC_SETTING.enATVCaptionType != ATV_CAPTION_TYPE_OFF))
    {
        if(MApp_CC_GetInfo(CC_SELECTOR_STATUS_CODE) == STATE_CAPTION_PARSER)
        {
            MApp_CC_StopParser();
            //MApp_Dmx_PES_Stop();
        }
    }
#endif

#if ENABLE_PVR
    if (!(E_PVR_STATE_PLAYBACK == MApp_PVR_StateMachineGet() &&  E_PLAYBACK_STATE_PLAYBACKING== MApp_Playback_StateMachineGet()))
#endif
    {
      #if (MHEG5_ENABLE && MHEG5_NDT_UNINTERRUPT_AV)
        if (msAPI_MHEG5_GetNDTChannelChange()==false)
      #endif
        {
            MApp_ChannelChange_DisableAV(eWindow);
        }
    }

#if (ENABLE_CH_CHANGE_TIMER_DEBUG == 1)
    g_u32ChannelChangeTimer1 = msAPI_Timer_GetTime0();
#endif

    //MApp_ChannelChange_DisableAV();
#if  ENABLE_DVB //ENABLE_DTV
  #if (ENABLE_PIP)
    if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
        ||(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) && (MApp_Get_PIPMode() != EN_PIP_MODE_OFF)))
  #else
    if ( IsDTVInUse() )
  #endif
    {
    #if 1//ENABLE_ZIGGO
        MApp_ParentalRating_DisableChannel();
    #endif

    #if (MHEG5_ENABLE && MHEG5_NDT_UNINTERRUPT_AV)
        if (msAPI_MHEG5_GetNDTChannelChange()==false)
    #endif
        {
            /* stop audio decoder */
            MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_STOP);
            /* stop audio filter */
            MApi_AUDIO_SetADOutputMode(AD_OUT_NONE);
            //msAPI_DMX_Stop( *MApp_Dmx_GetFid(EN_AUDIO_FID) );
            MApp_Demux_Stop_Filter_Audio();

            /* stop ad audio decoder */
            MApi_AUDIO_SetCommand(MSAPI_AUD_DVB2_DECCMD_STOP);
            /* stop ad audio filter */
            //msAPI_DMX_Stop(*MApp_Dmx_GetFid(EN_AD_FID));
            MApp_Demux_Stop_Filter_AudioDesc();
        }

        //if(pstVirtualCh->u16VideoPid /*< MSAPI_DMX_INVALID_PID*/)
    #if (MHEG5_ENABLE && MHEG5_NDT_UNINTERRUPT_AV)
        if (msAPI_MHEG5_GetNDTChannelChange() == FALSE)
    #endif
        {
            // stop video filter
            msAPI_DMX_Stop( *MApp_Dmx_GetFid(EN_VIDEO_FID) );

            #if ENABLE_PVR
            if (!(E_PVR_STATE_PLAYBACK == MApp_PVR_StateMachineGet() &&  E_PLAYBACK_STATE_PLAYBACKING== MApp_Playback_StateMachineGet()))
            #endif
            {
                // stop video decoder
                msAPI_VID_Command( MSAPI_VID_STOP );
            }

            #if ENABLE_PVR
            if (!(E_PVR_STATE_PLAYBACK == MApp_PVR_StateMachineGet() &&  E_PLAYBACK_STATE_PLAYBACKING== MApp_Playback_StateMachineGet()))
            #endif
            {
                // stop VOP
                MDrv_MVOP_Enable(FALSE);
            }
#if (MHEG5_ENABLE)
            g_MHEG5Video.bHaveVideo = FALSE;
#endif
        }

        //if(pstVirtualCh->u16PcrPid /*< MSAPI_DMX_INVALID_PID*/)
    #if (MHEG5_ENABLE && MHEG5_NDT_UNINTERRUPT_AV)
        if (msAPI_MHEG5_GetNDTChannelChange() == FALSE)
    #endif
        {
            /* stop pcr filter */
            msAPI_DMX_Stop( *MApp_Dmx_GetFid(EN_PCR_FID) );
        }

    #if 0
        MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_CLOSE, 0);
        MApp_PVR_StateMachineInput(E_PVR_INPUT_RECORD_CLOSE, 0);
    #endif

    #if MHEG5_ENABLE
        g_u16Current_VideoPID = g_u16Current_AudioPID=INVALID_PID;
        g_u16Current_ServicePosition=0xFFFF;
        if(!g_PIDfromMHEG5 && !_bBackDataProgram)
            MApp_Dmx_DisableTableMonitor();
    #else
        MApp_Dmx_DisableTableMonitor();
    #endif
        u32ChkTry2ChgMpeg2Time = 0;
    }
    else
#endif
    {
        /* stop audio decoder */
        if(IsATVInUse()) //ATV source need not to stop audio decoder, It will cause ATV no sound until reset
        {
            ;
        }
        else
        {
            MApi_AUDIO_SIF_SendCmd(MSAPI_AUD_SIF_CMD_SET_STOP,0, 0);
        }
    }

    enFrotEndLockStatus = FRONTEND_UNKNOWN;
    enMVDVideoStatus = MVD_UNKNOWN_VIDEO;

    fEnableSignalMonitor = FALSE;

  #if (ENABLE_CH_CHANGE_TIMER_DEBUG == 1)
    g_u32ChannelChangeTimer2 = msAPI_Timer_GetTime0();
  #endif

//#if ENABLE_CI_PLUS
//    msAPI_CI_HSS_Notify_CurrentServiceInfo(0, 0);
//#endif
#if ENABLE_CI
    msAPI_CI_NotifyServiceExit();
#endif

#if (ENABLE_CHCHANGETIME)
    printf("[ch change time]DisableChannel end = %ld\n", msAPI_Timer_DiffTimeFromNow(gU32ChChangeTime));
#endif
}


// For Nordig 9.45
#if ENABLE_DTV// NTV_FUNCTION_ENABLE
void MApp_ChannelChange_SearchAudioLangPriorityType3(U8* u8AudLangSelected, U8* u8LRAudioMode, U8 bServiceType, WORD wCurrentPosition, EN_SI_LANGUAGE enSoundAudioLan, U8 u8Nocheck_AudType, BOOLEAN bCheckBroadcastMix )
{
    AUD_INFO aAudioStreamInfo;
    U8 i,AudioLangNum;
    U8 u8AudLangCodeIdx_;
    BOOLEAN bFindAudio = FALSE;
    U8 u8AudLangSel=0xFF,u8LRAudMode=0xFF;
	U8 AudioMode;

    AudioLangNum = msAPI_CM_GetAudioStreamCount((MEMBER_SERVICETYPE)bServiceType, wCurrentPosition);
	for(AudioMode=0; AudioMode<2; AudioMode++) //follow Nordig spec 6.5 audio prioritising:normal and supplementary audio
	{

    if(stGenSetting.g_SysSetting.fSPDIFMODE == 0)
    {
        for(i=0; i<AudioLangNum; i++)
        {
            msAPI_CM_GetAudioStreamInfo((MEMBER_SERVICETYPE)bServiceType, wCurrentPosition, &aAudioStreamInfo, i);
			if(!stGenSetting.g_SoundSetting.bEnableAD)
			{
				if((AudioMode==0)&&(aAudioStreamInfo.aISOLangInfo[0].bBroadcastMixedAD == TRUE))
            	{
                	continue;
           	 	}
			}
			else
			{
				if((AudioMode==0)&&(aAudioStreamInfo.aISOLangInfo[0].bBroadcastMixedAD == FALSE))
            	{
                	continue;
            	}
			}
            if(bCheckBroadcastMix && aAudioStreamInfo.aISOLangInfo[0].bBroadcastMixedAD == FALSE)
            {
                continue;
            }

            if(!bCheckBroadcastMix)
            {
                //if(aAudioStreamInfo.wAudType != E_AUDIOSTREAM_MPEG4)
                if( msAPI_CM_Get_SIAudStreamType_By_AudInfo( &(aAudioStreamInfo) ) != E_SI_AUDIOSTREAM_MPEG4)
                {
                    continue;
                }
                if(aAudioStreamInfo.aISOLangInfo[0].bAudType != 0x00 && u8Nocheck_AudType != 1)
                {
                    continue;
                }
            }

            u8AudLangCodeIdx_ = aAudioStreamInfo.aISOLangInfo[0].bISOLangIndex;
            if(u8AudLangCodeIdx_ == enSoundAudioLan || enSoundAudioLan == SI_LANGUAGE_NONE)
            {
            #if 1//NTV_FUNCTION_ENABLE
                //if(aAudioStreamInfo.u8ProfileAndLevel == HE_AAC_LEVEL2)
                if( aAudioStreamInfo.eProfileAndLevel == E_CM_PROFILE_HE_AAC_LEVEL2 )
                {
                    *u8AudLangSelected = i;
                    *u8LRAudioMode = aAudioStreamInfo.aISOLangInfo[0].bISOLanguageInfo;
                    bFindAudio = TRUE;
                    break;
                }
                else
            #endif
                {
                    if(u8AudLangSel == 0xFF && u8LRAudMode == 0xFF)
                    {
                        u8AudLangSel = i;
                        u8LRAudMode = aAudioStreamInfo.aISOLangInfo[0].bISOLanguageInfo;
                    }
                }

            }
        }
        //[5]MPEG
        if(bFindAudio == FALSE)
        {
            for(i=0; i<AudioLangNum; i++)
            {
                msAPI_CM_GetAudioStreamInfo((MEMBER_SERVICETYPE)bServiceType, wCurrentPosition, &aAudioStreamInfo, i);
				if(!stGenSetting.g_SoundSetting.bEnableAD)
				{
					if((AudioMode==0)&&(aAudioStreamInfo.aISOLangInfo[0].bBroadcastMixedAD == TRUE))
					{
						continue;
					}
				}
				else
				{
					if((AudioMode==0)&&(aAudioStreamInfo.aISOLangInfo[0].bBroadcastMixedAD == FALSE))
					{
						continue;
					}
				}
                if(bCheckBroadcastMix && aAudioStreamInfo.aISOLangInfo[0].bBroadcastMixedAD == FALSE)
                {
                    continue;
                }

                if(!bCheckBroadcastMix)
                {
                    //if(aAudioStreamInfo.wAudType != E_AUDIOSTREAM_MPEG)
                    if( msAPI_CM_Get_SIAudStreamType_By_AudInfo( &(aAudioStreamInfo) ) != E_SI_AUDIOSTREAM_MPEG )
                    {
                        continue;
                    }

                    if(aAudioStreamInfo.aISOLangInfo[0].bAudType != 0x00 && u8Nocheck_AudType != 1)
                    {
                        continue;
                    }
                }

                u8AudLangCodeIdx_ = aAudioStreamInfo.aISOLangInfo[0].bISOLangIndex;
                if(u8AudLangCodeIdx_ == enSoundAudioLan || enSoundAudioLan == SI_LANGUAGE_NONE)
                {
                    *u8AudLangSelected = i;
                    *u8LRAudioMode = aAudioStreamInfo.aISOLangInfo[0].bISOLanguageInfo;
                    bFindAudio = TRUE;
                    break;
                }

            }
        }

    //[2]AAC
        if(bFindAudio == FALSE)
        {
            for(i=0; i<AudioLangNum; i++)
            {
                msAPI_CM_GetAudioStreamInfo((MEMBER_SERVICETYPE)bServiceType, wCurrentPosition, &aAudioStreamInfo, i);
				if(!stGenSetting.g_SoundSetting.bEnableAD)
				{
					if((AudioMode==0)&&(aAudioStreamInfo.aISOLangInfo[0].bBroadcastMixedAD == TRUE))
					{
						continue;
					}
				}
				else
				{
					if((AudioMode==0)&&(aAudioStreamInfo.aISOLangInfo[0].bBroadcastMixedAD == FALSE))
					{
						continue;
					}
				}

                if(bCheckBroadcastMix && aAudioStreamInfo.aISOLangInfo[0].bBroadcastMixedAD == FALSE)
                {
                    continue;
                }

                if(!bCheckBroadcastMix)
                {
                    //if(aAudioStreamInfo.wAudType != E_AUDIOSTREAM_AAC)
                    if( msAPI_CM_Get_SIAudStreamType_By_AudInfo( &(aAudioStreamInfo) ) != E_SI_AUDIOSTREAM_AAC)
                    {
                        continue;
                    }
                    if(aAudioStreamInfo.aISOLangInfo[0].bAudType != 0x00 && u8Nocheck_AudType != 1)
                    {
                        continue;
                    }
                }

                u8AudLangCodeIdx_ = aAudioStreamInfo.aISOLangInfo[0].bISOLangIndex;
                if(u8AudLangCodeIdx_ == enSoundAudioLan || enSoundAudioLan == SI_LANGUAGE_NONE)
                {
#if 1//NTV_FUNCTION_ENABLE
                    /*if( aAudioStreamInfo.u8ProfileAndLevel==0x58
                      ||aAudioStreamInfo.u8ProfileAndLevel==0x51
                      ||( (aAudioStreamInfo.u8ProfileAndLevel==0x00)&&(OSD_COUNTRY_SETTING == OSD_COUNTRY_THAILAND) )
                      ) */
                    if( aAudioStreamInfo.eProfileAndLevel == E_CM_PROFILE_HE_AAC_LEVEL2
                      ||aAudioStreamInfo.eProfileAndLevel == E_CM_PROFILE_AAC_LEVEL2
                      ||( (aAudioStreamInfo.eProfileAndLevel ==E_CM_PROFILE_NONE)&&(OSD_COUNTRY_SETTING == OSD_COUNTRY_THAILAND) )
                      )
                    {
                        *u8AudLangSelected = i;
                        *u8LRAudioMode = aAudioStreamInfo.aISOLangInfo[0].bISOLanguageInfo;
                        bFindAudio = TRUE;
                        break;
                    }
                    else
#endif
                    {
                        if(u8AudLangSel == 0xFF && u8LRAudMode == 0xFF)
                        {
                            u8AudLangSel = i;
                            u8LRAudMode = aAudioStreamInfo.aISOLangInfo[0].bISOLanguageInfo;
                        }
                    }
                }
            }
        }
        //[3]AC3P
        if(bFindAudio == FALSE)
        {
            for(i=0; i<AudioLangNum; i++)
            {
                msAPI_CM_GetAudioStreamInfo((MEMBER_SERVICETYPE)bServiceType, wCurrentPosition, &aAudioStreamInfo, i);
				if(!stGenSetting.g_SoundSetting.bEnableAD)
				{
					if((AudioMode==0)&&(aAudioStreamInfo.aISOLangInfo[0].bBroadcastMixedAD == TRUE))
					{
						continue;
					}
				}
				else
				{
					if((AudioMode==0)&&(aAudioStreamInfo.aISOLangInfo[0].bBroadcastMixedAD == FALSE))
					{
						continue;
					}
				}

                if(bCheckBroadcastMix && aAudioStreamInfo.aISOLangInfo[0].bBroadcastMixedAD == FALSE)
                {
                    continue;
                }

                if(!bCheckBroadcastMix)
                {
                    //if(aAudioStreamInfo.wAudType != E_AUDIOSTREAM_AC3P)
                    if( msAPI_CM_Get_SIAudStreamType_By_AudInfo( &(aAudioStreamInfo) ) != E_SI_AUDIOSTREAM_AC3P)
                    {
                        continue;
                    }
                    if(aAudioStreamInfo.aISOLangInfo[0].bAudType != 0x00 && u8Nocheck_AudType != 1)
                    {
                        continue;
                    }
                }

                u8AudLangCodeIdx_ = aAudioStreamInfo.aISOLangInfo[0].bISOLangIndex;
                if(u8AudLangCodeIdx_ == enSoundAudioLan || enSoundAudioLan == SI_LANGUAGE_NONE)
                {
                    *u8AudLangSelected = i;
                    *u8LRAudioMode = aAudioStreamInfo.aISOLangInfo[0].bISOLanguageInfo;
                    bFindAudio = TRUE;
                    break;
                }
            }
        }

        //[4]AC3
        if(bFindAudio == FALSE)
        {
            for(i=0; i<AudioLangNum; i++)
            {
                msAPI_CM_GetAudioStreamInfo((MEMBER_SERVICETYPE)bServiceType, wCurrentPosition, &aAudioStreamInfo, i);
                if(!stGenSetting.g_SoundSetting.bEnableAD)
                {
                    if((AudioMode==0)&&(aAudioStreamInfo.aISOLangInfo[0].bBroadcastMixedAD == TRUE))
                    {
                        continue;
                    }
                }
                else
                {
                    if((AudioMode==0)&&(aAudioStreamInfo.aISOLangInfo[0].bBroadcastMixedAD == FALSE))
                    {
                        continue;
                    }
                }

                //if(aAudioStreamInfo.wAudType != E_AUDIOSTREAM_AC3)
                if( msAPI_CM_Get_SIAudStreamType_By_AudInfo( &(aAudioStreamInfo) ) != E_SI_AUDIOSTREAM_AC3)
                {
                    continue;
                }

                if(aAudioStreamInfo.aISOLangInfo[0].bAudType != 0x00 && u8Nocheck_AudType != 1)
                {
                    continue;
                }
                u8AudLangCodeIdx_ = aAudioStreamInfo.aISOLangInfo[0].bISOLangIndex;
                if(u8AudLangCodeIdx_ == enSoundAudioLan || enSoundAudioLan == SI_LANGUAGE_NONE)
                {
                    *u8AudLangSelected = i;
                    *u8LRAudioMode = aAudioStreamInfo.aISOLangInfo[0].bISOLanguageInfo;
                    bFindAudio = TRUE;
                    break;
                }
            }
        }
    }
    else
    {
        //[1]MPEG4
        if(bFindAudio == FALSE)
        {
            for(i=0; i<AudioLangNum; i++)
            {
                msAPI_CM_GetAudioStreamInfo((MEMBER_SERVICETYPE)bServiceType, wCurrentPosition, &aAudioStreamInfo, i);
				if(!stGenSetting.g_SoundSetting.bEnableAD)
				{
					if((AudioMode==0)&&(aAudioStreamInfo.aISOLangInfo[0].bBroadcastMixedAD == TRUE))
					{
						continue;
					}
				}
				else
				{
					if((AudioMode==0)&&(aAudioStreamInfo.aISOLangInfo[0].bBroadcastMixedAD == FALSE))
					{
						continue;
					}
				}

                if(bCheckBroadcastMix && aAudioStreamInfo.aISOLangInfo[0].bBroadcastMixedAD == FALSE)
                {
                    continue;
                }

                if(!bCheckBroadcastMix)
                {
                    //if(aAudioStreamInfo.wAudType != E_AUDIOSTREAM_MPEG4)
                    if( msAPI_CM_Get_SIAudStreamType_By_AudInfo( &(aAudioStreamInfo) ) != E_SI_AUDIOSTREAM_MPEG4)
                    {
                        continue;
                    }
                    if(aAudioStreamInfo.aISOLangInfo[0].bAudType != 0x00 && u8Nocheck_AudType != 1)
                    {
                        continue;
                    }
                }

                u8AudLangCodeIdx_ = aAudioStreamInfo.aISOLangInfo[0].bISOLangIndex;
                if(u8AudLangCodeIdx_ == enSoundAudioLan || enSoundAudioLan == SI_LANGUAGE_NONE)
                {
                #if 1//NTV_FUNCTION_ENABLE
                    //if(aAudioStreamInfo.u8ProfileAndLevel==HE_AAC_LEVEL4 || aAudioStreamInfo.u8ProfileAndLevel==AAC_LEVEL4)
                    if(aAudioStreamInfo.eProfileAndLevel==E_CM_PROFILE_HE_AAC_LEVEL4 || aAudioStreamInfo.eProfileAndLevel==E_CM_PROFILE_AAC_LEVEL4)
                    {
                        *u8AudLangSelected = i;
                        *u8LRAudioMode = aAudioStreamInfo.aISOLangInfo[0].bISOLanguageInfo;
                        bFindAudio = TRUE;
                        break;
                    }
                    else
                #endif
                    {
                        if(u8AudLangSel == 0xFF && u8LRAudMode == 0xFF)
                        {
                            u8AudLangSel = i;
                            u8LRAudMode = aAudioStreamInfo.aISOLangInfo[0].bISOLanguageInfo;
                        }
                    }
                }
            }
        }

    //[2]AAC
        if(bFindAudio == FALSE)
        {
            for(i=0; i<AudioLangNum; i++)
            {
                msAPI_CM_GetAudioStreamInfo((MEMBER_SERVICETYPE)bServiceType, wCurrentPosition, &aAudioStreamInfo, i);
				if(!stGenSetting.g_SoundSetting.bEnableAD)
				{
					if((AudioMode==0)&&(aAudioStreamInfo.aISOLangInfo[0].bBroadcastMixedAD == TRUE))
					{
						continue;
					}
				}
				else
				{
					if((AudioMode==0)&&(aAudioStreamInfo.aISOLangInfo[0].bBroadcastMixedAD == FALSE))
					{
						continue;
					}
				}

                if(bCheckBroadcastMix && aAudioStreamInfo.aISOLangInfo[0].bBroadcastMixedAD == FALSE)
                {
                    continue;
                }

                if(!bCheckBroadcastMix)
                {
                    //if(aAudioStreamInfo.wAudType != E_AUDIOSTREAM_AAC)
                    if( msAPI_CM_Get_SIAudStreamType_By_AudInfo( &(aAudioStreamInfo) ) != E_SI_AUDIOSTREAM_AAC)
                    {
                        continue;
                    }
                    if(aAudioStreamInfo.aISOLangInfo[0].bAudType != 0x00 && u8Nocheck_AudType != 1)
                    {
                        continue;
                    }
                }

                u8AudLangCodeIdx_ = aAudioStreamInfo.aISOLangInfo[0].bISOLangIndex;
                if(u8AudLangCodeIdx_ == enSoundAudioLan || enSoundAudioLan == SI_LANGUAGE_NONE)
                {
                #if 1//NTV_FUNCTION_ENABLE
                    //if(aAudioStreamInfo.u8ProfileAndLevel==HE_AAC_LEVEL4 || aAudioStreamInfo.u8ProfileAndLevel==AAC_LEVEL4)
                    if(aAudioStreamInfo.eProfileAndLevel==E_CM_PROFILE_HE_AAC_LEVEL4 || aAudioStreamInfo.eProfileAndLevel==E_CM_PROFILE_AAC_LEVEL4)
                    {
                        *u8AudLangSelected = i;
                        *u8LRAudioMode = aAudioStreamInfo.aISOLangInfo[0].bISOLanguageInfo;
                        bFindAudio = TRUE;
                        break;
                    }
                    else
                #endif
                    {
                        if(u8AudLangSel == 0xFF && u8LRAudMode == 0xFF)
                        {
                            u8AudLangSel = i;
                            u8LRAudMode = aAudioStreamInfo.aISOLangInfo[0].bISOLanguageInfo;
                        }
                    }
                }
            }
        }

        //[3]AC3P
        if(bFindAudio == FALSE)
        {
            for(i=0; i<AudioLangNum; i++)
            {
                msAPI_CM_GetAudioStreamInfo((MEMBER_SERVICETYPE)bServiceType, wCurrentPosition, &aAudioStreamInfo, i);
				if(!stGenSetting.g_SoundSetting.bEnableAD)
				{
					if((AudioMode==0)&&(aAudioStreamInfo.aISOLangInfo[0].bBroadcastMixedAD == TRUE))
					{
						continue;
					}
				}
				else
				{
					if((AudioMode==0)&&(aAudioStreamInfo.aISOLangInfo[0].bBroadcastMixedAD == FALSE))
					{
						continue;
					}
				}

                if(bCheckBroadcastMix && aAudioStreamInfo.aISOLangInfo[0].bBroadcastMixedAD == FALSE)
                {
                    continue;
                }

                if(!bCheckBroadcastMix)
                {
                    //if(aAudioStreamInfo.wAudType != E_AUDIOSTREAM_AC3P)
                    if(msAPI_CM_Get_SIAudStreamType_By_AudInfo( &(aAudioStreamInfo) ) != E_SI_AUDIOSTREAM_AC3P)
                    {
                        continue;
                    }
                    if(aAudioStreamInfo.aISOLangInfo[0].bAudType != 0x00 && u8Nocheck_AudType != 1)
                    {
                        continue;
                    }
                }

                u8AudLangCodeIdx_ = aAudioStreamInfo.aISOLangInfo[0].bISOLangIndex;
                if(u8AudLangCodeIdx_ == enSoundAudioLan || enSoundAudioLan == SI_LANGUAGE_NONE)
                {
                    *u8AudLangSelected = i;
                    *u8LRAudioMode = aAudioStreamInfo.aISOLangInfo[0].bISOLanguageInfo;
                    bFindAudio = TRUE;
                    break;
                }
             }
        }

        //[4]AC3
        if(bFindAudio == FALSE)
        {
            for(i=0; i<AudioLangNum; i++)
            {
                msAPI_CM_GetAudioStreamInfo((MEMBER_SERVICETYPE)bServiceType, wCurrentPosition, &aAudioStreamInfo, i);
				if(!stGenSetting.g_SoundSetting.bEnableAD)
				{
					if((AudioMode==0)&&(aAudioStreamInfo.aISOLangInfo[0].bBroadcastMixedAD == TRUE))
					{
						continue;
					}
				}
				else
				{
					if((AudioMode==0)&&(aAudioStreamInfo.aISOLangInfo[0].bBroadcastMixedAD == FALSE))
					{
						continue;
					}
				}

                if(bCheckBroadcastMix && aAudioStreamInfo.aISOLangInfo[0].bBroadcastMixedAD == FALSE)
                {
                    continue;
                }

                if(!bCheckBroadcastMix)
                {
                    //if(aAudioStreamInfo.wAudType != E_AUDIOSTREAM_AC3)
                    if( msAPI_CM_Get_SIAudStreamType_By_AudInfo( &(aAudioStreamInfo) ) != E_SI_AUDIOSTREAM_AC3)
                    {
                        continue;
                    }
                    if(aAudioStreamInfo.aISOLangInfo[0].bAudType != 0x00 && u8Nocheck_AudType != 1)
                    {
                        continue;
                    }
                }

                u8AudLangCodeIdx_ = aAudioStreamInfo.aISOLangInfo[0].bISOLangIndex;
                if(u8AudLangCodeIdx_ == enSoundAudioLan || enSoundAudioLan == SI_LANGUAGE_NONE)
                {
                    *u8AudLangSelected = i;
                    *u8LRAudioMode = aAudioStreamInfo.aISOLangInfo[0].bISOLanguageInfo;
                    bFindAudio = TRUE;
                    break;
                }
            }
        }

    //[5]MPEG
        if(bFindAudio == FALSE)
        {
            for(i=0; i<AudioLangNum; i++)
            {
                msAPI_CM_GetAudioStreamInfo((MEMBER_SERVICETYPE)bServiceType, wCurrentPosition, &aAudioStreamInfo, i);
				if(!stGenSetting.g_SoundSetting.bEnableAD)
				{
					if((AudioMode==0)&&(aAudioStreamInfo.aISOLangInfo[0].bBroadcastMixedAD == TRUE))
					{
						continue;
					}
				}
				else
				{
					if((AudioMode==0)&&(aAudioStreamInfo.aISOLangInfo[0].bBroadcastMixedAD == FALSE))
					{
						continue;
					}
				}

                if(bCheckBroadcastMix && aAudioStreamInfo.aISOLangInfo[0].bBroadcastMixedAD == FALSE)
                {
                    continue;
                }

                if(!bCheckBroadcastMix)
                {
                    //if(aAudioStreamInfo.wAudType != E_AUDIOSTREAM_MPEG)
                    if(msAPI_CM_Get_SIAudStreamType_By_AudInfo( &(aAudioStreamInfo) ) != E_SI_AUDIOSTREAM_MPEG)
                    {
                        continue;
                    }
                    if(aAudioStreamInfo.aISOLangInfo[0].bAudType != 0x00 && u8Nocheck_AudType != 1)
                    {
                        continue;
                    }
                }

                u8AudLangCodeIdx_ = aAudioStreamInfo.aISOLangInfo[0].bISOLangIndex;
                if(u8AudLangCodeIdx_ == enSoundAudioLan || enSoundAudioLan == SI_LANGUAGE_NONE)
                {
                    if(u8AudLangSel == 0xFF && u8LRAudMode == 0xFF)
                    {
                        u8AudLangSel = i;
                        u8LRAudMode = aAudioStreamInfo.aISOLangInfo[0].bISOLanguageInfo;
                    }
                }
            }
        }
    }
    if((AudioMode==0)&&(bFindAudio == TRUE))
		break;

    if(bFindAudio == FALSE)
    {
        if(u8AudLangSel != 0xFF && u8LRAudMode != 0xFF)
        {
            *u8AudLangSelected = u8AudLangSel;
            *u8LRAudioMode = u8LRAudMode;
            break;
        }
        else
        {
            *u8AudLangSelected = 0;
            *u8LRAudioMode = 0;
        }
    }
	}
}
#endif // #if ENABLE_DTV

/************************************************************************************/

#if ENABLE_DTV//NORDIG_FUNC //for Nordig Spec v2.0
void MApp_ChannelChange_SearchAudioLangPriorityType(U8* u8AudLangSelected, U8* u8LRAudioMode, U8 bServiceType, WORD wCurrentPosition, EN_SI_LANGUAGE enSoundAudioLan, U8 u8Nocheck_AudType, BOOLEAN bCheckBroadcastMix )
{
    AUD_INFO aAudioStreamInfo;
    U8 i,j,k,AudioLangNum;
    U8 u8AudLangCodeIdx;

    AudioLangNum = msAPI_CM_GetAudioStreamCount((MEMBER_SERVICETYPE)bServiceType, wCurrentPosition);

    for (k=0 ; k<5 ; k++)
    {
        for(i=0; i<AudioLangNum; i++)
        {
            msAPI_CM_GetAudioStreamInfo((MEMBER_SERVICETYPE)bServiceType, wCurrentPosition, &aAudioStreamInfo, i);

            if(bCheckBroadcastMix && aAudioStreamInfo.aISOLangInfo[0].bBroadcastMixedAD == FALSE)
            {
                continue;
            }

            SI_AUDIOSTREAM_TYPE eSIAudStreamType = msAPI_CM_Get_SIAudStreamType_By_AudInfo(&aAudioStreamInfo);


            for(j=0; j<MAX_AUD_ISOLANG_NUM; j++)
            {
                //if(aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex == LANGUAGE_NONE)
                //    break;
                u8AudLangCodeIdx = aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex;
                if ( (aAudioStreamInfo.aISOLangInfo[j].bAudType == 0x00)
                   ||(u8Nocheck_AudType == 1) )
                {
                    if ( u8AudLangCodeIdx == enSoundAudioLan
                       ||enSoundAudioLan == SI_LANGUAGE_NONE )
                    {
                        switch(k)
                        {
                            case 0:
                                //if(aAudioStreamInfo.wAudType == E_AUDIOSTREAM_MPEG4)
                                if(eSIAudStreamType == E_SI_AUDIOSTREAM_MPEG4)
                                {
                                    *u8AudLangSelected = i;
                                    *u8LRAudioMode = aAudioStreamInfo.aISOLangInfo[j].bISOLanguageInfo;
                                    return;
                                }
                                break;

                            case 1:
                                //if(aAudioStreamInfo.wAudType == E_AUDIOSTREAM_AAC)
                                if(eSIAudStreamType == E_SI_AUDIOSTREAM_AAC)
                                {
                                    *u8AudLangSelected = i;
                                    *u8LRAudioMode = aAudioStreamInfo.aISOLangInfo[j].bISOLanguageInfo;
                                    return;
                                }
                                break;

                            case 2:
                                //if(aAudioStreamInfo.wAudType == E_AUDIOSTREAM_AC3P)
                                if(eSIAudStreamType == E_SI_AUDIOSTREAM_AC3P)
                                {
                                    *u8AudLangSelected = i;
                                    *u8LRAudioMode = aAudioStreamInfo.aISOLangInfo[j].bISOLanguageInfo;
                                    return;
                                }
                                break;

                            case 3:
                                //if(aAudioStreamInfo.wAudType == E_AUDIOSTREAM_AC3)
                                if(eSIAudStreamType == E_SI_AUDIOSTREAM_AC3)
                                {
                                    *u8AudLangSelected = i;
                                    *u8LRAudioMode = aAudioStreamInfo.aISOLangInfo[j].bISOLanguageInfo;
                                    return;
                                }
                                break;

                            case 4:
                                //if(aAudioStreamInfo.wAudType == E_AUDIOSTREAM_MPEG)
                                if(eSIAudStreamType == E_SI_AUDIOSTREAM_MPEG)
                                {
                                    *u8AudLangSelected = i;
                                    *u8LRAudioMode = aAudioStreamInfo.aISOLangInfo[j].bISOLanguageInfo;
                                    return;
                                }
                                break;
                        } // switch
                    }
                }
            } // for(j=0; j<MAX_AUD_ISOLANG_NUM; j++)
        } // for(i=0; i<AudioLangNum; i++)
    } // for (k=0 ; k<5 ; k++)
}
#endif // #if ENABLE_DTV

/************************************************************************************/

#if ENABLE_DTV

void MApp_ChannelChange_SearchAudioLangPriorityType2(U8* u8AudLangSelected, U8* u8LRAudioMode, U8 bServiceType, WORD wCurrentPosition, EN_SI_LANGUAGE enSoundAudioLan, U8 u8Nocheck_AudType, BOOLEAN bCheckBroadcastMix )
{
    AUD_INFO aAudioStreamInfo;
    U8 i,j,k,AudioLangNum;
    U8 u8AudLangCodeIdxL;

    AudioLangNum = msAPI_CM_GetAudioStreamCount((MEMBER_SERVICETYPE)bServiceType, wCurrentPosition);

    for(k=0 ; k<5 ; k++)
    {
        for(i=0; i<AudioLangNum; i++)
        {
            msAPI_CM_GetAudioStreamInfo((MEMBER_SERVICETYPE)bServiceType, wCurrentPosition, &aAudioStreamInfo, i);
            if(bCheckBroadcastMix && aAudioStreamInfo.aISOLangInfo[0].bBroadcastMixedAD == FALSE)
            {
                continue;
            }

            SI_AUDIOSTREAM_TYPE eSIAudStreamType = msAPI_CM_Get_SIAudStreamType_By_AudInfo(&aAudioStreamInfo);

            for(j=0; j<MAX_AUD_ISOLANG_NUM; j++)
            {
                //if(aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex == LANGUAGE_NONE)
                //    break;
                u8AudLangCodeIdxL = aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex;
                if( aAudioStreamInfo.aISOLangInfo[j].bAudType == 0x00
                  || u8Nocheck_AudType == 1
                  || (bCheckBroadcastMix && aAudioStreamInfo.aISOLangInfo[0].bBroadcastMixedAD)
                  )
                {
                    if((u8AudLangCodeIdxL == enSoundAudioLan || enSoundAudioLan == SI_LANGUAGE_NONE) &&
                    (TRUE == aAudioStreamInfo.aISOLangInfo[j].bIsValid))
                    {
                        switch(k)
                        {
                            case 0:
                                //if(aAudioStreamInfo.wAudType == E_AUDIOSTREAM_AC3)
                                if(eSIAudStreamType == E_SI_AUDIOSTREAM_AC3)
                                {
                                    *u8AudLangSelected = i;
                                    *u8LRAudioMode = aAudioStreamInfo.aISOLangInfo[j].bISOLanguageInfo;
                                    return;
                                 }break;
                            case 1:
                                //if(aAudioStreamInfo.wAudType == E_AUDIOSTREAM_AC3P)
                                if(eSIAudStreamType == E_SI_AUDIOSTREAM_AC3P)
                                {
                                    *u8AudLangSelected = i;
                                    *u8LRAudioMode = aAudioStreamInfo.aISOLangInfo[j].bISOLanguageInfo;
                                    return;
                                 }break;
                            case 2:
                                //if(aAudioStreamInfo.wAudType == E_AUDIOSTREAM_MPEG4)
                                if(eSIAudStreamType == E_SI_AUDIOSTREAM_MPEG4)
                                {
                                    *u8AudLangSelected = i;
                                    *u8LRAudioMode = aAudioStreamInfo.aISOLangInfo[j].bISOLanguageInfo;
                                    return;
                                 }break;
                            case 3:
                                //if(aAudioStreamInfo.wAudType == E_AUDIOSTREAM_AAC)
                                if(eSIAudStreamType == E_SI_AUDIOSTREAM_AAC)
                                {
                                    *u8AudLangSelected = i;
                                    *u8LRAudioMode = aAudioStreamInfo.aISOLangInfo[j].bISOLanguageInfo;
                                    return;
                                 }break;

                            case 4:
                                //if(aAudioStreamInfo.wAudType == E_AUDIOSTREAM_MPEG)
                                if(eSIAudStreamType == E_SI_AUDIOSTREAM_MPEG)
                                {
                                    *u8AudLangSelected = i;
                                    *u8LRAudioMode = aAudioStreamInfo.aISOLangInfo[j].bISOLanguageInfo;
                                    return;
                                 }break;
                        }
                    }
                }
            }
        }
    }

}

/*********************************************************************************/
//ZUI: moved from UiMenu
#if (ENABLE_CI_PLUS)
void MApp_ChannelChange_SearchDefaultOPAudioLang(void)
{
    AUD_INFO aAudioStreamInfo;
    MEMBER_SERVICETYPE bServiceType;
    WORD wCurrentPosition;
    U8 u8AudLangCodeIdxL;
    U8 i,j,AudioLangNum;
    U8 u8GetPreferredLang = 0xFF; // Other primary audio
    U8 u8GetPreferredLang2= 0xFF; // Preferred but not primary audio
    //U8 u82ndPreferredLang = 0xFF;
    //U8 u8Get2ndPreferredLang2= 0xFF; // Preferred but not primary audio
    U8 u8PreferredLangAudMode= 0xFF,u8PreferredLang2AudMode= 0xFF;
       //u82ndPreferredLangAudMode= 0xFF,u82ndPreferredLang2AudMode= 0xFF;
    U8 u8GetPreferredLang_eng = 0xFF;
    U8 u8GetPreferredLang_und = 0xFF;
    U8 u8GetPreferredLang_qaa = 0xFF;
    U8 u8GetPreferredLang_qab = 0xFF;
    U8 u8GetPreferredLang_qac = 0xFF;
    U8 u8PreferredLangAudMode_eng = 0xFF;
    U8 u8PreferredLangAudMode_und = 0xFF;
    U8 u8PreferredLangAudMode_qaa = 0xFF;
    U8 u8PreferredLangAudMode_qab = 0xFF;
    U8 u8PreferredLangAudMode_qac = 0xFF;
    U8 au8IsoLang[3];
    EN_SI_LANGUAGE eLangcode = SI_LANGUAGE_UND;

    if(TRUE == MApp_CI_GetOpIso639LangCodeByCicamId(MApp_CI_GetCurrentOpCicamId(), au8IsoLang))
    {
        eLangcode = msAPI_SI_GetLanguageByISO639LangCode(au8IsoLang);
    }

    //search default audio lang
    g_u8AudLangSelected = 0;
    bServiceType = msAPI_CM_GetCurrentServiceType();
    wCurrentPosition = msAPI_CM_GetCurrentPosition(bServiceType);
    AudioLangNum = msAPI_CM_GetAudioStreamCount(bServiceType, wCurrentPosition);

    if(AudioLangNum != 0)
    {
        for(i = 0; i < AudioLangNum; i++)
        {
            /* Get all audio information */
            msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &aAudioStreamInfo, i);
            for(j = 0; j < MAX_AUD_ISOLANG_NUM; j++)
            {
                if(aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex == SI_LANGUAGE_NONE)
                    break;
                if (aAudioStreamInfo.aISOLangInfo[j].bBroadcastMixedAD)
                            {
                                break;
                            }

                u8AudLangCodeIdxL = aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex;
                /* Choose primary audio type only. */
                if(aAudioStreamInfo.aISOLangInfo[j].bAudType == 0x00)
                {
                    if(u8AudLangCodeIdxL == eLangcode)
                    {
                        if(IS_DTG_COUNTRY(OSD_COUNTRY_SETTING))
                        {
                            MApp_ChannelChange_SearchAudioLangPriorityType2(&g_u8AudLangSelected, &g_u8LRAudioMode, bServiceType, wCurrentPosition, eLangcode, 0, FALSE);
                        }
                        else
                        {
                            MApp_ChannelChange_SearchAudioLangPriorityType3(&g_u8AudLangSelected, &g_u8LRAudioMode, bServiceType, wCurrentPosition, eLangcode, 0, FALSE);
                        }
                        return;
                    }
                    else if((u8GetPreferredLang_eng == 0xFF && u8AudLangCodeIdxL == SI_LANGUAGE_ENGLISH)
                           || (u8GetPreferredLang_und == 0xFF && u8AudLangCodeIdxL == SI_LANGUAGE_UND)
                           || (u8GetPreferredLang_qaa == 0xFF && u8AudLangCodeIdxL == SI_LANGUAGE_QAA)
                           || (u8GetPreferredLang_qab == 0xFF && u8AudLangCodeIdxL == SI_LANGUAGE_QAB)
                           || (u8GetPreferredLang_qac == 0xFF && u8AudLangCodeIdxL == SI_LANGUAGE_QAC))
                    {
                        if(u8GetPreferredLang_und == 0xFF && u8AudLangCodeIdxL == SI_LANGUAGE_UND)
                        {
                              u8GetPreferredLang_und = i;
                             u8PreferredLangAudMode_und = aAudioStreamInfo.aISOLangInfo[j].bISOLanguageInfo;
                        }
                        else if(u8GetPreferredLang_qaa == 0xFF && u8AudLangCodeIdxL == SI_LANGUAGE_QAA)
                        {
                            u8GetPreferredLang_qaa = i;
                            u8PreferredLangAudMode_qaa = aAudioStreamInfo.aISOLangInfo[j].bISOLanguageInfo;
                        }
                        else if(u8GetPreferredLang_qab == 0xFF && u8AudLangCodeIdxL == SI_LANGUAGE_QAB)
                        {
                            u8GetPreferredLang_qab = i;
                            u8PreferredLangAudMode_qab = aAudioStreamInfo.aISOLangInfo[j].bISOLanguageInfo;
                        }
                        else if(u8GetPreferredLang_qac == 0xFF && u8AudLangCodeIdxL == SI_LANGUAGE_QAC)
                        {
                            u8GetPreferredLang_qac = i;
                            u8PreferredLangAudMode_qac = aAudioStreamInfo.aISOLangInfo[j].bISOLanguageInfo;
                        }
                        else if(u8GetPreferredLang_eng == 0xFF && u8AudLangCodeIdxL == SI_LANGUAGE_ENGLISH)
                        {
                             u8GetPreferredLang_eng = i;
                             u8PreferredLangAudMode_eng = aAudioStreamInfo.aISOLangInfo[j].bISOLanguageInfo;
                        }
                    }
                    else if(u8GetPreferredLang == 0xFF && u8GetPreferredLang_eng == 0xFF && u8GetPreferredLang_und == 0xFF)
                    {
                        u8GetPreferredLang = i;
                        u8PreferredLangAudMode = aAudioStreamInfo.aISOLangInfo[j].bISOLanguageInfo;
                    }
                }
                else
                {
                    if(u8GetPreferredLang2 == 0xFF && u8AudLangCodeIdxL == eLangcode)
                    {
                        u8GetPreferredLang2 = i;
                        u8PreferredLang2AudMode = aAudioStreamInfo.aISOLangInfo[j].bISOLanguageInfo;
                    }
                }
            }

        }

        if((u8GetPreferredLang_eng != 0xFF) || (u8GetPreferredLang_und != 0xFF) || (u8GetPreferredLang_qaa != 0xFF)
        || (u8GetPreferredLang_qab != 0xFF) || (u8GetPreferredLang_qac != 0xFF))
        {
            if(u8GetPreferredLang_und != 0xFF)
            {
                g_u8AudLangSelected = u8GetPreferredLang_und;
                g_u8LRAudioMode     = u8PreferredLangAudMode_und;
            }
            else if(u8GetPreferredLang_eng != 0xFF)
            {
                g_u8AudLangSelected = u8GetPreferredLang_eng;
                g_u8LRAudioMode     = u8PreferredLangAudMode_eng;
            }
            else if(u8GetPreferredLang_qaa != 0xFF)
            {
                g_u8AudLangSelected = u8GetPreferredLang_qaa;
                g_u8LRAudioMode     = u8PreferredLangAudMode_qaa;
            }
            else if(u8GetPreferredLang_qab != 0xFF)
            {
                g_u8AudLangSelected = u8GetPreferredLang_qab;
                g_u8LRAudioMode     = u8PreferredLangAudMode_qab;
            }
            else if(u8GetPreferredLang_qac != 0xFF)
            {
                g_u8AudLangSelected = u8GetPreferredLang_qac;
                g_u8LRAudioMode     = u8PreferredLangAudMode_qac;
            }
        }
        else if (u8GetPreferredLang != 0xFF)
        {
            if(IS_DTG_COUNTRY(OSD_COUNTRY_SETTING))
            {
                MApp_ChannelChange_SearchAudioLangPriorityType2(&g_u8AudLangSelected, &g_u8LRAudioMode, bServiceType, wCurrentPosition, SI_LANGUAGE_NONE, 0, FALSE);
            }
            else
            {
                MApp_ChannelChange_SearchAudioLangPriorityType3(&g_u8AudLangSelected, &g_u8LRAudioMode, bServiceType, wCurrentPosition, SI_LANGUAGE_NONE, 0, FALSE);
            }
        }
        else if (u8GetPreferredLang2 != 0xFF)
        {
            g_u8AudLangSelected = u8GetPreferredLang2;
            g_u8LRAudioMode     = u8PreferredLang2AudMode;
        }
    #if NORDIG_FUNC //for Nordig Spec v2.0
        else
        {
            if(IS_DTG_COUNTRY(OSD_COUNTRY_SETTING))
            {
                MApp_ChannelChange_SearchAudioLangPriorityType2(&g_u8AudLangSelected, &g_u8LRAudioMode, bServiceType, wCurrentPosition, SI_LANGUAGE_NONE, 1, FALSE);
            }
            else
            {
                MApp_ChannelChange_SearchAudioLangPriorityType3(&g_u8AudLangSelected, &g_u8LRAudioMode, bServiceType, wCurrentPosition, SI_LANGUAGE_NONE, 1, FALSE);
            }
            //MApp_ChannelChange_SearchAudioLangPriorityType(&g_u8AudLangSelected, &g_u8LRAudioMode, bServiceType, wCurrentPosition, SI_LANGUAGE_NONE, 1);
        }
    #endif
    }
}
#endif

void MApp_ChannelChange_SearchDefaultAudioLang(void)
{
#if(ENABLE_DVB)
    AUD_INFO aAudioStreamInfo;
    MEMBER_SERVICETYPE bServiceType;
    WORD wCurrentPosition;
    U8 u8AudLangCodeIdxL;
    U8 i,j,AudioLangNum;
    U8 u8GetPreferredLang = 0xFF; // Other primary audio
    U8 u8GetPreferredLang2= 0xFF; // Preferred but not primary audio
    U8 u82ndPreferredLang = 0xFF;
    U8 u8Get2ndPreferredLang2= 0xFF; // Preferred but not primary audio
    U8 u8PreferredLangAudMode= 0xFF,u8PreferredLang2AudMode= 0xFF,
       u82ndPreferredLangAudMode= 0xFF,u82ndPreferredLang2AudMode= 0xFF;
    U8 u8GetPreferredLang_eng = 0xFF;
    U8 u8GetPreferredLang_und = 0xFF;
    U8 u8GetPreferredLang_qaa = 0xFF;
    U8 u8GetPreferredLang_qab = 0xFF;
    U8 u8GetPreferredLang_qac = 0xFF;
    U8 u8PreferredLangAudMode_eng = 0xFF;
    U8 u8PreferredLangAudMode_und = 0xFF;
    U8 u8PreferredLangAudMode_qaa = 0xFF;
    U8 u8PreferredLangAudMode_qab = 0xFF;
    U8 u8PreferredLangAudMode_qac = 0xFF;

    //search default audio lang
    g_u8AudLangSelected = 0;
    bServiceType = msAPI_CM_GetCurrentServiceType();
    wCurrentPosition = msAPI_CM_GetCurrentPosition(bServiceType);
    AudioLangNum = msAPI_CM_GetAudioStreamCount(bServiceType, wCurrentPosition);
    if(AudioLangNum != 0)
    {
        for(i = 0; i < AudioLangNum; i++)
        {
            /* Get all audio information */
            msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &aAudioStreamInfo, i);
            for(j = 0; j < MAX_AUD_ISOLANG_NUM; j++)
            {
                if(aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex == SI_LANGUAGE_NONE)
                    break;
                if (aAudioStreamInfo.aISOLangInfo[j].bBroadcastMixedAD)
                {
                    break;
                }
                if (FALSE == aAudioStreamInfo.aISOLangInfo[j].bIsValid)break;
                u8AudLangCodeIdxL = aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex;
                /* Choose primary audio type only. */
                if(aAudioStreamInfo.aISOLangInfo[j].bAudType == 0x00)
                {
                    if(u8AudLangCodeIdxL == MApp_GetSILanguage((EN_LANGUAGE)stGenSetting.g_SoundSetting.enSoundAudioLan1))
                    {
                        if(IS_DTG_COUNTRY(OSD_COUNTRY_SETTING))
                        {
                            MApp_ChannelChange_SearchAudioLangPriorityType2(&g_u8AudLangSelected, &g_u8LRAudioMode, bServiceType, wCurrentPosition, MApp_GetSILanguage((EN_LANGUAGE)stGenSetting.g_SoundSetting.enSoundAudioLan1), 0, FALSE);
                        }
                        else
                        {
                            MApp_ChannelChange_SearchAudioLangPriorityType3(&g_u8AudLangSelected, &g_u8LRAudioMode, bServiceType, wCurrentPosition, MApp_GetSILanguage((EN_LANGUAGE)stGenSetting.g_SoundSetting.enSoundAudioLan1), 0, FALSE);
                        }
                        return;
                    }
                    else if(u82ndPreferredLang == 0xFF && u8AudLangCodeIdxL == MApp_GetSILanguage((EN_LANGUAGE)stGenSetting.g_SoundSetting.enSoundAudioLan2))
                    {

                        if(IS_DTG_COUNTRY(OSD_COUNTRY_SETTING))
                        {
                            MApp_ChannelChange_SearchAudioLangPriorityType2(&u82ndPreferredLang, &u82ndPreferredLangAudMode, bServiceType, wCurrentPosition, MApp_GetSILanguage((EN_LANGUAGE)stGenSetting.g_SoundSetting.enSoundAudioLan2), 0, FALSE);
                        }
                        else
                        {
                            MApp_ChannelChange_SearchAudioLangPriorityType3(&u82ndPreferredLang, &u82ndPreferredLangAudMode, bServiceType, wCurrentPosition, MApp_GetSILanguage((EN_LANGUAGE)stGenSetting.g_SoundSetting.enSoundAudioLan2), 0 , FALSE);
                        }
                    }
                    else if(u82ndPreferredLang == 0xFF &&u8AudLangCodeIdxL == MApp_GetSILanguage( SUBTITLE_DEFAULT_LANGUAGE_1))
                    {
                        if(IS_DTG_COUNTRY(OSD_COUNTRY_SETTING))
                        {
                            MApp_ChannelChange_SearchAudioLangPriorityType2(&u82ndPreferredLang, &u82ndPreferredLangAudMode, bServiceType, wCurrentPosition, MApp_GetSILanguage(SUBTITLE_DEFAULT_LANGUAGE_1), 0, FALSE);
                        }
                        else
                        {
                            MApp_ChannelChange_SearchAudioLangPriorityType3(&g_u8AudLangSelected, &g_u8LRAudioMode, bServiceType, wCurrentPosition, MApp_GetSILanguage(SUBTITLE_DEFAULT_LANGUAGE_1), 0, FALSE);
                        }
                        //break;
                    }
                    else if(u82ndPreferredLang == 0xFF &&u8AudLangCodeIdxL == MApp_GetSILanguage( SUBTITLE_DEFAULT_LANGUAGE_2))
                    {
                        if(IS_DTG_COUNTRY(OSD_COUNTRY_SETTING))
                        {
                            MApp_ChannelChange_SearchAudioLangPriorityType2(&u82ndPreferredLang, &u82ndPreferredLangAudMode, bServiceType, wCurrentPosition,  MApp_GetSILanguage(SUBTITLE_DEFAULT_LANGUAGE_2), 0, FALSE);
                        }
                        else
                        {
                            MApp_ChannelChange_SearchAudioLangPriorityType3(&g_u8AudLangSelected, &g_u8LRAudioMode, bServiceType, wCurrentPosition, MApp_GetSILanguage(SUBTITLE_DEFAULT_LANGUAGE_2), 0, FALSE);
                        }
                        //break;
                    }
                    #if (ENABLE_DVB_NOISDB)
                    else if(IS_DTG_COUNTRY(OSD_COUNTRY_SETTING) &&
                        #if(ENABLE_SBTVD_DTV_SYSTEM)
                            (!msAPI_SRC_IS_SBTVD_InUse())&&
                        #endif
                        ((u8GetPreferredLang_eng == 0xFF && u8AudLangCodeIdxL == SI_LANGUAGE_ENGLISH)
                           || (u8GetPreferredLang_und == 0xFF && u8AudLangCodeIdxL == SI_LANGUAGE_UND)
                           || (u8GetPreferredLang_qaa == 0xFF && u8AudLangCodeIdxL == SI_LANGUAGE_QAA)
                           || (u8GetPreferredLang_qab == 0xFF && u8AudLangCodeIdxL == SI_LANGUAGE_QAB)
                           || (u8GetPreferredLang_qac == 0xFF && u8AudLangCodeIdxL == SI_LANGUAGE_QAC)))
                    {
                        if(OSD_COUNTRY_SETTING == OSD_COUNTRY_NEWZEALAND)
                        {
                            if(u8GetPreferredLang_eng == 0xFF && u8AudLangCodeIdxL == SI_LANGUAGE_ENGLISH)
                            {
                                u8GetPreferredLang_eng = i;
                                u8PreferredLangAudMode_eng = aAudioStreamInfo.aISOLangInfo[j].bISOLanguageInfo;
                            }
                            else if(u8GetPreferredLang_und == 0xFF && u8AudLangCodeIdxL == SI_LANGUAGE_UND)
                            {
                                u8GetPreferredLang_und = i;
                                u8PreferredLangAudMode_und = aAudioStreamInfo.aISOLangInfo[j].bISOLanguageInfo;
                            }
                            else if(u8GetPreferredLang_qaa == 0xFF && u8AudLangCodeIdxL == SI_LANGUAGE_QAA)
                            {
                                u8GetPreferredLang_qaa = i;
                                u8PreferredLangAudMode_qaa = aAudioStreamInfo.aISOLangInfo[j].bISOLanguageInfo;
                            }
                            else if(u8GetPreferredLang_qab == 0xFF && u8AudLangCodeIdxL == SI_LANGUAGE_QAB)
                            {
                                u8GetPreferredLang_qab = i;
                                u8PreferredLangAudMode_qab = aAudioStreamInfo.aISOLangInfo[j].bISOLanguageInfo;
                            }
                            else if(u8GetPreferredLang_qac == 0xFF && u8AudLangCodeIdxL == SI_LANGUAGE_QAC)
                            {
                                u8GetPreferredLang_qac = i;
                                u8PreferredLangAudMode_qac = aAudioStreamInfo.aISOLangInfo[j].bISOLanguageInfo;
                            }
                        }
                        else
                        {
                            if(u8GetPreferredLang_und == 0xFF && u8AudLangCodeIdxL == SI_LANGUAGE_UND)
                            {
                                u8GetPreferredLang_und = i;
                                u8PreferredLangAudMode_und = aAudioStreamInfo.aISOLangInfo[j].bISOLanguageInfo;
                            }
                            else if(u8GetPreferredLang_eng == 0xFF && u8AudLangCodeIdxL == SI_LANGUAGE_ENGLISH)
                            {
                                u8GetPreferredLang_eng = i;
                                u8PreferredLangAudMode_eng = aAudioStreamInfo.aISOLangInfo[j].bISOLanguageInfo;
                            }
                            else if(u8GetPreferredLang_qaa == 0xFF && u8AudLangCodeIdxL == SI_LANGUAGE_QAA)
                            {
                                u8GetPreferredLang_qaa = i;
                                u8PreferredLangAudMode_qaa = aAudioStreamInfo.aISOLangInfo[j].bISOLanguageInfo;
                            }
                            else if(u8GetPreferredLang_qab == 0xFF && u8AudLangCodeIdxL == SI_LANGUAGE_QAB)
                            {
                                u8GetPreferredLang_qab = i;
                                u8PreferredLangAudMode_qab = aAudioStreamInfo.aISOLangInfo[j].bISOLanguageInfo;
                            }
                            else if(u8GetPreferredLang_qac == 0xFF && u8AudLangCodeIdxL == SI_LANGUAGE_QAC)
                            {
                                u8GetPreferredLang_qac = i;
                                u8PreferredLangAudMode_qac = aAudioStreamInfo.aISOLangInfo[j].bISOLanguageInfo;
                            }
                        }
                    }
                    #endif
                    else if(u8GetPreferredLang == 0xFF && u8GetPreferredLang_eng == 0xFF && u8GetPreferredLang_und == 0xFF)
                    {
                        u8GetPreferredLang = i;
                        u8PreferredLangAudMode = aAudioStreamInfo.aISOLangInfo[j].bISOLanguageInfo;
                    }
                }
                else
                {
                    if(u8GetPreferredLang2 == 0xFF && u8AudLangCodeIdxL == MApp_GetSILanguage((EN_LANGUAGE)stGenSetting.g_SoundSetting.enSoundAudioLan1))
                    {
                        u8GetPreferredLang2 = i;
                        u8PreferredLang2AudMode = aAudioStreamInfo.aISOLangInfo[j].bISOLanguageInfo;
                    }
                    else if(u8Get2ndPreferredLang2 == 0xFF && u8AudLangCodeIdxL == MApp_GetSILanguage((EN_LANGUAGE)stGenSetting.g_SoundSetting.enSoundAudioLan2))
                    {
                        u8Get2ndPreferredLang2 = i;
                        u82ndPreferredLang2AudMode = aAudioStreamInfo.aISOLangInfo[j].bISOLanguageInfo;
                    }
                }
            }

        }
        // If we don't got primary preferred audio, we choose other primary audio first.
        // If no primary audio exists, we choose prefferred audio. No matter what type it is.
        if (u82ndPreferredLang != 0xFF)
        {
            g_u8AudLangSelected = u82ndPreferredLang;
            g_u8LRAudioMode     = u82ndPreferredLangAudMode;
        }
        else if((u8GetPreferredLang_eng != 0xFF) || (u8GetPreferredLang_und != 0xFF) || (u8GetPreferredLang_qaa != 0xFF)
             || (u8GetPreferredLang_qab != 0xFF) || (u8GetPreferredLang_qac != 0xFF))
        {
            if(OSD_COUNTRY_SETTING == OSD_COUNTRY_NEWZEALAND)
            {
                if(u8GetPreferredLang_eng != 0xFF)
                {
                    g_u8AudLangSelected = u8GetPreferredLang_eng;
                    g_u8LRAudioMode     = u8PreferredLangAudMode_eng;
                }
                else if(u8GetPreferredLang_und != 0xFF)
                {
                    g_u8AudLangSelected = u8GetPreferredLang_und;
                    g_u8LRAudioMode     = u8PreferredLangAudMode_und;
                }
                else if(u8GetPreferredLang_qaa != 0xFF)
                {
                    g_u8AudLangSelected = u8GetPreferredLang_qaa;
                    g_u8LRAudioMode     = u8PreferredLangAudMode_qaa;
                }
                else if(u8GetPreferredLang_qab != 0xFF)
                {
                    g_u8AudLangSelected = u8GetPreferredLang_qab;
                    g_u8LRAudioMode     = u8PreferredLangAudMode_qab;
                }
                else if(u8GetPreferredLang_qac != 0xFF)
                {
                    g_u8AudLangSelected = u8GetPreferredLang_qac;
                    g_u8LRAudioMode     = u8PreferredLangAudMode_qac;
                }
            }
            else
            {
                if(u8GetPreferredLang_und != 0xFF)
                {
                    g_u8AudLangSelected = u8GetPreferredLang_und;
                    g_u8LRAudioMode     = u8PreferredLangAudMode_und;
                }
                else if(u8GetPreferredLang_eng != 0xFF)
                {
                    g_u8AudLangSelected = u8GetPreferredLang_eng;
                    g_u8LRAudioMode     = u8PreferredLangAudMode_eng;
                }
                else if(u8GetPreferredLang_qaa != 0xFF)
                {
                    g_u8AudLangSelected = u8GetPreferredLang_qaa;
                    g_u8LRAudioMode     = u8PreferredLangAudMode_qaa;
                }
                else if(u8GetPreferredLang_qab != 0xFF)
                {
                    g_u8AudLangSelected = u8GetPreferredLang_qab;
                    g_u8LRAudioMode     = u8PreferredLangAudMode_qab;
                }
                else if(u8GetPreferredLang_qac != 0xFF)
                {
                    g_u8AudLangSelected = u8GetPreferredLang_qac;
                    g_u8LRAudioMode     = u8PreferredLangAudMode_qac;
                }
            }
        }
        else if (u8GetPreferredLang != 0xFF)
        {
            if(IS_DTG_COUNTRY(OSD_COUNTRY_SETTING))
            {
                MApp_ChannelChange_SearchAudioLangPriorityType2(&g_u8AudLangSelected, &g_u8LRAudioMode, bServiceType, wCurrentPosition, SI_LANGUAGE_NONE, 0, FALSE);
            }
            else
            {
                MApp_ChannelChange_SearchAudioLangPriorityType3(&g_u8AudLangSelected, &g_u8LRAudioMode, bServiceType, wCurrentPosition, SI_LANGUAGE_NONE, 0, FALSE);
            }
        }
        else if (u8GetPreferredLang2 != 0xFF)
        {
            g_u8AudLangSelected = u8GetPreferredLang2;
            g_u8LRAudioMode     = u8PreferredLang2AudMode;
        }
        else if (u8Get2ndPreferredLang2 != 0xFF)
        {
            g_u8AudLangSelected = u8Get2ndPreferredLang2;
            g_u8LRAudioMode     = u82ndPreferredLang2AudMode;
        }
    #if NORDIG_FUNC //for Nordig Spec v2.0
        else
        {
            if(IS_DTG_COUNTRY(OSD_COUNTRY_SETTING))
            {
                MApp_ChannelChange_SearchAudioLangPriorityType2(&g_u8AudLangSelected, &g_u8LRAudioMode, bServiceType, wCurrentPosition, SI_LANGUAGE_NONE, 1, FALSE);
            }
            else
            {
                //1281231 TC14061300399: audio language focus error
                MApp_ChannelChange_SearchAudioLangPriorityType3(&g_u8AudLangSelected, &g_u8LRAudioMode, bServiceType, wCurrentPosition, SI_LANGUAGE_NONE, 0, FALSE);
            }
            //MApp_ChannelChange_SearchAudioLangPriorityType(&g_u8AudLangSelected, &g_u8LRAudioMode, bServiceType, wCurrentPosition, SI_LANGUAGE_NONE, 1);
        }
    #endif
    }
#endif
}

#if(ENABLE_DVB_AUDIO_DESC)
void MApp_ChannelChange_SearchBroadcastMixAudio(void)
{
    if (!stGenSetting.g_SoundSetting.bEnableAD)
    {
        //printf("MApp_UiMenu_SearchAdAudio : AD is disabled\n");
        return;
    }


    MEMBER_SERVICETYPE bServiceType;
    AUD_INFO aAudioStreamInfo;
    AUD_INFO aPriAudioStreamInfo;
    WORD wCurrentPosition;
    U8 AudioLangNum;
    U8 i, j, k;
    U8 u8BroadcastMixAudSelected=0xFF;

#if ENABLE_CI_PLUS
    U8 au8IsoLang[3];
    EN_SI_LANGUAGE eLangcode = SI_LANGUAGE_UND;

    if(TRUE == MApp_CI_GetOpIso639LangCodeByCicamId(MApp_CI_GetCurrentOpCicamId(), au8IsoLang))
    {
        eLangcode = msAPI_SI_GetLanguageByISO639LangCode(au8IsoLang);
    }
#endif

    memset(&aAudioStreamInfo, 0, sizeof(AUD_INFO));
    memset(&aPriAudioStreamInfo, 0, sizeof(AUD_INFO));


    bServiceType = msAPI_CM_GetCurrentServiceType();
    wCurrentPosition = msAPI_CM_GetCurrentPosition(bServiceType);
    AudioLangNum = msAPI_CM_GetAudioStreamCount(bServiceType, wCurrentPosition);

#if ENABLE_PVR
    if (MApp_PVR_IsPlaybacking())
    {
        MApp_PVR_PlaybackAudioGetStreamInfo(&aPriAudioStreamInfo, g_u8AudLangSelected);
    }
    else
#endif
    {
        // Get current main audio language
        msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &aPriAudioStreamInfo, g_u8AudLangSelected);
    }

    if (AudioLangNum != 0)
    {
        for (i = 0; i < AudioLangNum; i++)
        {

#if ENABLE_PVR
            if (MApp_PVR_IsPlaybacking())
            {
                MApp_PVR_PlaybackAudioGetStreamInfo(&aAudioStreamInfo, i);
            }
            else
#endif
            {
                /* Get all audio information */
                msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &aAudioStreamInfo, i);
            }

            //printf("bAudType = 0x%02bx\n", aAudioStreamInfo.aISOLangInfo[0].bAudType);

            for (j = 0; j < MAX_AUD_ISOLANG_NUM; j++)
            {
                if (aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex == SI_LANGUAGE_NONE)
                {
                    break;
                }

                /* find visual impaired audio stream */
                if (aAudioStreamInfo.aISOLangInfo[j].bBroadcastMixedAD)
                {
                    for (k = 0; k < MAX_AUD_ISOLANG_NUM; k++)
                    {
                    #if (ENABLE_CI_PLUS)
                        if(TRUE == MApp_CI_IsOpMode())
                        {
                            if ((aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex == eLangcode))
                            {
                                MApp_ChannelChange_SearchAudioLangPriorityType3(&g_u8AudLangSelected, &g_u8LRAudioMode, bServiceType, wCurrentPosition, (EN_SI_LANGUAGE)aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex , 0, TRUE);
                                return;
                            }
                        }
                        if(FALSE == MApp_CI_IsOpMode())
                        {
                            if ((aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex != aPriAudioStreamInfo.aISOLangInfo[k].bISOLangIndex)
                                    ||((aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex == aPriAudioStreamInfo.aISOLangInfo[k].bISOLangIndex)&&(!aPriAudioStreamInfo.aISOLangInfo[k].bBroadcastMixedAD)))
                            {
                                if(IS_DTG_COUNTRY(OSD_COUNTRY_SETTING))
                                {
                                    MApp_ChannelChange_SearchAudioLangPriorityType2(&g_u8AudLangSelected, &g_u8LRAudioMode, bServiceType, wCurrentPosition, (EN_SI_LANGUAGE)aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex , 0, TRUE);
                                }
                                else
                                {
                                    MApp_ChannelChange_SearchAudioLangPriorityType3(&g_u8AudLangSelected, &g_u8LRAudioMode, bServiceType, wCurrentPosition, (EN_SI_LANGUAGE)aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex , 0, TRUE);
                                }

                                return;
                            }
                        }
                    #else
                    if ((aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex != aPriAudioStreamInfo.aISOLangInfo[k].bISOLangIndex)
                            ||((aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex == aPriAudioStreamInfo.aISOLangInfo[k].bISOLangIndex)&&(!aPriAudioStreamInfo.aISOLangInfo[k].bBroadcastMixedAD)))
                        {
                            if(IS_DTG_COUNTRY(OSD_COUNTRY_SETTING))
                            {
                                MApp_ChannelChange_SearchAudioLangPriorityType2(&g_u8AudLangSelected, &g_u8LRAudioMode, bServiceType, wCurrentPosition, (EN_SI_LANGUAGE)aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex , 0, TRUE);
                            }
                            else
                            {
                                MApp_ChannelChange_SearchAudioLangPriorityType3(&g_u8AudLangSelected, &g_u8LRAudioMode, bServiceType, wCurrentPosition, (EN_SI_LANGUAGE)aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex , 0, TRUE);
                            }

                            return;
                        }
                    #endif
                        else if((u8BroadcastMixAudSelected == 0xFF) &&
                            (aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex == SI_LANGUAGE_BROADCAST_MIX))//no language case
                        {

                            if(IS_DTG_COUNTRY(OSD_COUNTRY_SETTING))
                            {
                                MApp_ChannelChange_SearchAudioLangPriorityType2(&g_u8AudLangSelected, &g_u8LRAudioMode, bServiceType, wCurrentPosition, SI_LANGUAGE_BROADCAST_MIX, 0, TRUE);
                            }
                            else
                            {
                                MApp_ChannelChange_SearchAudioLangPriorityType3(&g_u8AudLangSelected, &g_u8LRAudioMode, bServiceType, wCurrentPosition, SI_LANGUAGE_BROADCAST_MIX, 0, TRUE);
                            }

                            u8BroadcastMixAudSelected=g_u8AudLangSelected;
                        }
                        else if(IS_DTG_COUNTRY(OSD_COUNTRY_SETTING) && (aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex==SI_LANGUAGE_ENGLISH))
                        {
                            MApp_ChannelChange_SearchAudioLangPriorityType2(&g_u8AudLangSelected, &g_u8LRAudioMode, bServiceType, wCurrentPosition, SI_LANGUAGE_ENGLISH, 0, TRUE);
                            u8BroadcastMixAudSelected=g_u8AudLangSelected;
                        }
                    }
                }
            }
        }
    }
}
#endif
#endif // #if ENABLE_DTV


#if ENABLE_AD_DISABLE_MAINAUDIO
void MApp_Audio_SwitchtoADAudio(BOOL ADEnable)
{
    AUD_INFO stAudioStreamInfo;
    AUD_INFO stAdAudioStreamInfo;
    MEMBER_SERVICETYPE bServiceType;
    WORD wCurrentPosition;
    DMX_FILTER_STATUS eDMXFLTSTA;
    bServiceType = msAPI_CM_GetCurrentServiceType();
    wCurrentPosition = msAPI_CM_GetCurrentPosition(bServiceType);

    msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &stAudioStreamInfo, g_u8AudLangSelected);
    msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &stAdAudioStreamInfo, g_u8AdAudSelected);

    if ((ADEnable)&&(stGenSetting.g_SoundSetting.bEnableAD)&&( INVALID_PID != stAdAudioStreamInfo.wAudPID ))
    {
        /* set audio PID & start filter */
        //printf("Channel change, audio pid 0x%x, u8AudFid %bu\n",stAudioStreamInfo.wAudPID,MApp_Dmx_GetAudioFid());
        //eDMXFLTSTA = msAPI_DMX_StartFilter( stAudioStreamInfo.wAudPID, MSAPI_DMX_FILTER_TYPE_AUDIO, MApp_Dmx_GetFid(EN_AUDIO_FID) );
        eDMXFLTSTA = msAPI_DMX_StartFilter( stAdAudioStreamInfo.wAudPID, MSAPI_DMX_FILTER_TYPE_AUDIO, MApp_Dmx_GetFid(EN_AUDIO_FID) );
        //printf("a Channel change, eDMXFLTSTA %bu, audio pid 0x%x, u8AudFid %bu\n",eDMXFLTSTA,msAPI_DMX_GetFilterPID(MApp_Dmx_GetAudioFid()),MApp_Dmx_GetAudioFid());

        /* set decoder system and reload firmware code */
        {
            MApp_ChannelChange_Set_Audio_Decoder_System(stAdAudioStreamInfo.wAudType);
        }


        /* re-sync audio decoder */

        /* start audio decoder */
      #if (ENABLE_AUTOTEST || ENABLE_BOOTTIME)
       #if (ENABLE_BOOTTIME==DISABLE)
        if (g_bAutobuildDebug == TRUE)
       #endif
        {
            if (gbBootTimeFinish == FALSE)
            {
                gU32TmpTime = msAPI_Timer_DiffTimeFromNow(gU32BootTime);
                printf("[TIME] start audio decoder = %ld\n", gU32TmpTime);
            }
        }
      #endif

        {
            MApi_DMX_AVFifo_Reset(DMX_FILTER_TYPE_AUDIO, TRUE);
            MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_PLAY);
            MApi_DMX_AVFifo_Reset(DMX_FILTER_TYPE_AUDIO, FALSE);


          #if MHEG5_ENABLE
            if ((msAPI_MHEG5_IsRunning() == TRUE) ||
                (bServiceType == E_SERVICETYPE_RADIO))
            {
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            }
          #endif

            if (g_u8LRAudioMode == 0)
            {
                MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_SoundMode, MSAPI_AUD_MODE_STEREO, 0);
            }
            else if (g_u8LRAudioMode == 1)
            {
                MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_SoundMode, MSAPI_AUD_MODE_RR, 0);
                MApi_AUDIO_SetMpegInfo(Audio_MPEG_infoType_SoundMode, MSAPI_AUD_MPEG_SOUNDMODE_RR, 0);
            }
            else if (g_u8LRAudioMode == 2)
            {
                MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_SoundMode, MSAPI_AUD_MODE_LL, 0);
                MApi_AUDIO_SetMpegInfo(Audio_MPEG_infoType_SoundMode, MSAPI_AUD_MPEG_SOUNDMODE_LL, 0);
            }

            /* if radio channel, since channel change time is small, need additional mute delay
               to wait DTV audio dac out stable after play command */
            if ( bServiceType == E_SERVICETYPE_RADIO) {
                msAPI_Timer_Delayms(250);
            }
            else
            {
                MApp_Set_Audio_Mute_Timer(TRUE);
            }

            // solved scramble->ATV no audio bug.
            if(E_AUDIOSTREAM_AC3==stAdAudioStreamInfo.wAudType||E_AUDIOSTREAM_AC3P==stAdAudioStreamInfo.wAudType)
            {
                MApi_AUDIO_SetAC3Info(Audio_AC3_infoType_DrcMode, RF_MODE, 0);    //RF Mod
                MApi_AUDIO_SetAC3Info(Audio_AC3_infoType_DownmixMode, DOLBY_DOWNMIX_MODE_LTRT, 0);  // LtRt
                u32AC3CheckTimer = msAPI_Timer_GetTime0();
                bEnableAC3Check  = TRUE;
                u8AC3CheckTimes  = 10;
                //printf("set SPDIF_non-PCM\r\n");
            }
            else if(E_AUDIOSTREAM_AAC==stAdAudioStreamInfo.wAudType||E_AUDIOSTREAM_MPEG4==stAdAudioStreamInfo.wAudType)
            {
                MApi_AUDIO_SetAACInfo(Audio_AAC_infoType_DrcMode, RF_MODE, 0);      //RF Mod
                MApi_AUDIO_SetAACInfo(Audio_AAC_infoType_DownmixMode, DOLBY_DOWNMIX_MODE_LTRT, 0);
            }


            if(stGenSetting.g_SysSetting.fSPDIFMODE == 0)
            {
                MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
            }
            else
            {
                MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_NONPCM);
            }
        }
        // solved scramble->ATV no audio bug.
    }
    else if ( INVALID_PID != stAudioStreamInfo.wAudPID )
    {
        /* set audio PID & start filter */
        //printf("Channel change, audio pid 0x%x, u8AudFid %bu\n",stAudioStreamInfo.wAudPID,MApp_Dmx_GetAudioFid());
        //eDMXFLTSTA = msAPI_DMX_StartFilter( stAudioStreamInfo.wAudPID, MSAPI_DMX_FILTER_TYPE_AUDIO, MApp_Dmx_GetFid(EN_AUDIO_FID) );
        eDMXFLTSTA = msAPI_DMX_StartFilter( stAudioStreamInfo.wAudPID, MSAPI_DMX_FILTER_TYPE_AUDIO, MApp_Dmx_GetFid(EN_AUDIO_FID) );
        //printf("a Channel change, eDMXFLTSTA %bu, audio pid 0x%x, u8AudFid %bu\n",eDMXFLTSTA,msAPI_DMX_GetFilterPID(MApp_Dmx_GetAudioFid()),MApp_Dmx_GetAudioFid());

        /* set decoder system and reload firmware code */
        {
            MApp_ChannelChange_Set_Audio_Decoder_System(stAudioStreamInfo.wAudType);
        }


        /* re-sync audio decoder */

        /* start audio decoder */
      #if (ENABLE_AUTOTEST || ENABLE_BOOTTIME)
       #if (ENABLE_BOOTTIME==DISABLE)
        if (g_bAutobuildDebug == TRUE)
       #endif
        {
            if (gbBootTimeFinish == FALSE)
            {
                gU32TmpTime = msAPI_Timer_DiffTimeFromNow(gU32BootTime);
                printf("[TIME] start audio decoder = %ld\n", gU32TmpTime);
            }
        }
      #endif

        {
            MApi_DMX_AVFifo_Reset(DMX_FILTER_TYPE_AUDIO, TRUE);
            MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_PLAY);
            MApi_DMX_AVFifo_Reset(DMX_FILTER_TYPE_AUDIO, FALSE);


          #if MHEG5_ENABLE
            if ((msAPI_MHEG5_IsRunning() == TRUE) ||
                (bServiceType == E_SERVICETYPE_RADIO))
            {
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            }
          #endif

            if (g_u8LRAudioMode == 0)
            {
                MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_SoundMode, MSAPI_AUD_MODE_STEREO, 0);
            }
            else if (g_u8LRAudioMode == 1)
            {
                MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_SoundMode, MSAPI_AUD_MODE_RR, 0);
                MApi_AUDIO_SetMpegInfo(Audio_MPEG_infoType_SoundMode, MSAPI_AUD_MPEG_SOUNDMODE_RR, 0);
            }
            else if (g_u8LRAudioMode == 2)
            {
                MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_SoundMode, MSAPI_AUD_MODE_LL, 0);
                MApi_AUDIO_SetMpegInfo(Audio_MPEG_infoType_SoundMode, MSAPI_AUD_MPEG_SOUNDMODE_LL, 0);
            }

            /* if radio channel, since channel change time is small, need additional mute delay
               to wait DTV audio dac out stable after play command */
            if ( bServiceType == E_SERVICETYPE_RADIO) {
                msAPI_Timer_Delayms(250);
            }
            else
            {
                MApp_Set_Audio_Mute_Timer(TRUE);
            }

            // solved scramble->ATV no audio bug.
            if(E_AUDIOSTREAM_AC3==stAudioStreamInfo.wAudType||E_AUDIOSTREAM_AC3P==stAudioStreamInfo.wAudType)
            {
                MApi_AUDIO_SetAC3Info(Audio_AC3_infoType_DrcMode, RF_MODE, 0);    //RF Mod
                MApi_AUDIO_SetAC3Info(Audio_AC3_infoType_DownmixMode, DOLBY_DOWNMIX_MODE_LTRT, 0);  // LtRt
                u32AC3CheckTimer = msAPI_Timer_GetTime0();
                bEnableAC3Check  = TRUE;
                u8AC3CheckTimes  = 10;
                //printf("set SPDIF_non-PCM\r\n");
            }
            else if(E_AUDIOSTREAM_AAC==stAudioStreamInfo.wAudType||E_AUDIOSTREAM_MPEG4==stAudioStreamInfo.wAudType)
            {
                MApi_AUDIO_SetAACInfo(Audio_AAC_infoType_DrcMode, RF_MODE, 0);      //RF Mod
                MApi_AUDIO_SetAACInfo(Audio_AAC_infoType_DownmixMode, DOLBY_DOWNMIX_MODE_LTRT, 0);
            }


            if(stGenSetting.g_SysSetting.fSPDIFMODE == 0)
            {
                MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
            }
            else
            {
                MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_NONPCM);
            }
        }
        // solved scramble->ATV no audio bug.
    }
}
#endif
/************************************************************************************/

#if 0
//ZUI: moved from UiMenu2.c
void _MApp_ChannelChange_SearchAdAudio(void)
{
    MEMBER_SERVICETYPE bServiceType;
    AUD_INFO aAudioStreamInfo;
    AUD_INFO aPriAudioStreamInfo;
    WORD wCurrentPosition;
    U8 AudioLangNum;
    U8 i,j,k;
    U8 u8ADIndex=0xFF,u8ADNum=0;;
    //printf("-> MApp_UiMenu_SearchAdAudio\n");

    bServiceType = msAPI_CM_GetCurrentServiceType();
    wCurrentPosition = msAPI_CM_GetCurrentPosition(bServiceType);
    AudioLangNum = msAPI_CM_GetAudioStreamCount(bServiceType, wCurrentPosition);
    g_u8AdAudSelected = 0xFF;
    if (!stGenSetting.g_SoundSetting.bEnableAD)
    {
        //printf("MApp_UiMenu_SearchAdAudio : AD is disabled\n");
        return;
    }
    //printf("AudioLangNum = 0x%02bx\n", AudioLangNum);
    // Get current main audio language
    msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &aPriAudioStreamInfo, g_u8AudLangSelected);

    if (AudioLangNum != 0)
    {
        for (i = 0; i < AudioLangNum; i++)
        {
            /* Get all audio information */
            msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &aAudioStreamInfo, i);

            //printf("bAudType = 0x%02bx\n", aAudioStreamInfo.aISOLangInfo[0].bAudType);

            for (j = 0; j < MAX_AUD_ISOLANG_NUM; j++)
            {
                if (aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex == SI_LANGUAGE_NONE)
                {
                    break;
                }

                    /* find visual impaired audio stream */
                    if (aAudioStreamInfo.aISOLangInfo[j].bAudType == 0x03)
                    {
                        // find ad's language
                        for (k = 0; k < MAX_AUD_ISOLANG_NUM; k++)
                        {
                            //if (aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex == LANGUAGE_NONE)
                            //    continue;

                            // ad's language is the same as primary audio's
                            if ((aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex == aPriAudioStreamInfo.aISOLangInfo[k].bISOLangIndex)
                                || ((SI_LANGUAGE_ENGLISH == aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex) &&(SI_LANGUAGE_UND== aPriAudioStreamInfo.aISOLangInfo[k].bISOLangIndex))
                                || ((SI_LANGUAGE_UND == aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex) &&(SI_LANGUAGE_ENGLISH== aPriAudioStreamInfo.aISOLangInfo[k].bISOLangIndex)))
                            {
                                if (g_u8AudLangSelected == i)
                                {
                                    //printf("primary audio playing current found ad, find another\n");
                                    continue;
                                }

                                //printf("####found ad audio 0x%02bx####\n", i);
                                g_u8AdAudSelected = i;
                                if ((aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex == aPriAudioStreamInfo.aISOLangInfo[k].bISOLangIndex))
                                {
                                    return;
                                }
                            }
                            else
                            {
                                u8ADIndex=i;
                                u8ADNum++;
                            }
                        }
                    }
                }
        }
    }
    if((AudioLangNum==2) &&  (u8ADNum==1))
    {
        g_u8AdAudSelected = u8ADIndex;
    }
        //printf("MApp_UiMenu_SearchAdAudio : No AD found\n");
}
#endif

/************************************************************************************/

#if ENABLE_DVB
// Refine source : reset tuner&demod
void MApp_ChannelChange_EnableChannel_ResetTunerAndDemod(
    BYTE cRFChannelNumber, MEMBER_SERVICETYPE bServiceType, WORD wCurrentPosition )
{
    MS_TP_SETTING stTempTP;

    memset(&stTempTP, 0x00, sizeof(MS_TP_SETTING));

#if(ENABLE_S2)
    if( IsS2InUse() )
    {
        U16 u16CurrentS2IDIdx = msAPI_CM_GetPhysicalidx(bServiceType,wCurrentPosition);
        if( u16CurrentS2IDIdx >= MAX_DTV_S2_MUX_NUMBER )
        { // DVBS ID Table index invalid
            return;
        }

        g_stCurS2ProggramId = _astS2ProgramIDTable[u16CurrentS2IDIdx];
        //printf("\r\nCurrentS2idx=%d [%d]",CurrentS2idx,TP.SatelliteId);

        MS_SAT_PARAM sat;
        memset(&sat, 0x00, sizeof(MS_SAT_PARAM)); // fix coverity 207476

        if( FALSE == _GetSatInforByID(g_stCurS2ProggramId.SatelliteId, &sat) )
        {
            return;
        }

        MApi_DigiTuner_Tune2RfCh(sat, &g_stCurS2ProggramId, eAutoTune);
    }
    else
#endif
#if( ENABLE_DVBC )
    if( IsDVBCInUse() ) // DVB-C
    {
        U8 u8PhNum = 0;
        u8PhNum = msAPI_CM_Get_RFChannelIndex(cRFChannelNumber);
        //printf("u8PhNum=%u\n", u8PhNum);

    #if 1 // Use new API
        if( msAPI_CM_Get_MS_TPSetting_By_IdTabIdx(u8PhNum, &stTempTP) )
        {
        #if ENABLE_ZIGGO
            stTempTP.bAutoQamFlag = FALSE;
        #endif

            msAPI_Tuner_Tune2RfCh(&stTempTP);
        }
    #else

        DTVPROGRAMID_M stDPI;
        memset(&stDPI, 0, sizeof(stDPI));

        if(msAPI_CM_GetIDTable(u8PhNum,(BYTE *)&stDPI,E_DATA_ID_TABLE))
        {
            //stTempTP.u32Symbol_rate = stDPI.u32SymbRate;
            stTempTP.u32Symbol_rate = msAPI_CM_Get_IDTab_SymbolRate(&stDPI);

            stTempTP.u8Modulation = stDPI.QamMode;
            stTempTP.u32Frequency = stDPI.u32Frequency;
        #if ENABLE_ZIGGO
            stTempTP.bAutoQamFlag = FALSE;
        #endif
            msAPI_Tuner_Tune2RfCh(&stTempTP);
        }
    #endif
    }
    else
#endif
    {
        U8 u8PhNum=0;
        DTVPROGRAMID_M stDPI;
        memset(&stDPI, 0x00, sizeof(DTVPROGRAMID_M)); // fix coverity 218311

        u8PhNum = msAPI_CM_Get_RFChannelIndex(cRFChannelNumber);
        msAPI_CM_GetIDTable(u8PhNum,(BYTE *)&stDPI,E_DATA_ID_TABLE);

        if( msAPI_DFT_GetTSSetting(cRFChannelNumber, &stTempTP) == TRUE )
        {
            CHANNELCHANGE_DBINFO(printf("Current chn freq 0x%lx\n",stTempTP.u32Frequency));
            stTempTP.u8PLPID = msAPI_CM_GetPLP_ID(bServiceType,wCurrentPosition);
            stTempTP.u8HpLp = msAPI_CM_GetHpLp(bServiceType,wCurrentPosition);
            stTempTP.enBandWidth = stDPI.enBandWidth;

             // [step4/4]
        #if PATCH_FOR_HW_LIMIT_EXT_SYNC
            printf("loda Ext_Sync = %d\n",stDPI.Ext_Sync);
            if(stDPI.Ext_Sync == 0)
            {
                MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_DEMOD, FALSE, TRUE, TRUE);
            }
            else
            {
                MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_DEMOD, FALSE, FALSE, TRUE);
            }
        #endif

        #if ENABLE_DVB_T2
            if(IsDVBTInUse())
            {
                if(stTempTP.u8PLPID != 0xFF)
                {
                    MApp_DTV_Scan_T2_SetForceMonitorT2Signal(TRUE);
                    MAPP_DTV_Scan_T2_DoScan(DVB_T2_DEMOD,FALSE);
                    MAPP_DTV_Scan_T2_SetServiceType(DVBT2_SERVICE);
                    mdev_CofdmSetPlpGroupID(stTempTP.u8PLPID,0);
                }
                else
                {
                    MApp_DTV_Scan_T2_SetForceMonitorT2Signal(FALSE);
                    MAPP_DTV_Scan_T2_DoScan(DVB_T_DEMOD,FALSE);
                    MAPP_DTV_Scan_T2_SetServiceType(DVBT_SERVICE);
                }
            }
            else
        #endif
            {
                msAPI_Demod_Init( E_INIT_DEMOD_FOR_CHANGE_CHANNEL, msAPI_DTV_Comm_Get_CurSrcUseDemodType());
            }


        #if( CHANNEL_SCAN_AUTO_TEST )
            if(stTpSettingPC.u32Frequency)
            {
                msAPI_Tuner_Tune2RfCh( &stTpSettingPC );
                stTpSettingPC.u32Frequency = 0;
            }
            else
        #endif
            {
                msAPI_Tuner_Tune2RfCh(&stTempTP);
            }
        }
        else
        {
            printf("\nError: Get TSSetting failed!\n");
        }

    }

}
#endif // #if ENABLE_DVB

/************************************************************************************/
#if ENABLE_DVB
void MApp_ChannelChange_SetVideoAndAudioPid(MEMBER_SERVICETYPE bServiceType, WORD wPosition)
{
#if ENABLE_DTV
    MS_TP_SETTING stTempTP;
    memset(&stTempTP, 0x00, sizeof(MS_TP_SETTING)); // fix coverity 207477
#endif
    BYTE cRFChannelNumber;
    WORD wVideo_PID;
//        WORD wAudPID;
    WORD wPCR_PID;
    WORD wService_ID;
    WORD wTransportStream_ID;
    WORD wOriginalNetwork_ID;
    AUD_INFO stAudioStreamInfo;
    AUD_INFO stAdAudioStreamInfo;
    WORD wCurrentPosition = wPosition;
    DMX_FILTER_STATUS eDMXFLTSTA;
    SCALER_WIN eWindow = MAIN_WINDOW;

    g_ChChg_bInFunc_EnableChannel = TRUE;

    bCheckBlockPW = FALSE;
    bCheckParentalPW = FALSE;
    bParentalPWPassCheck = FALSE;
    //g_ParentalRating_u8PreParental_Control = 0xFF;
    //MApp_Set_MonitorParental(TRUE);

    //ZUI_TODO: if( g_u8MenuPageIndex != MENU_CHANNEL_DTV_ManualScan)
    {
      #if (ENABLE_DTV && MHEG5_ENABLE)//for change AV(different channel) in MHEG5
        if (!g_PIDfromMHEG5)
        {
            bStopMonitorBlock=FALSE;
        }
      #else
        bStopMonitorBlock=FALSE;
      #endif
    }


    if( fEnableSignalMonitor == TRUE )
    {
      #if (!ENABLE_S2)
        printf("Enable_channel: fEnableSignalMonitor already=1\n");
        g_ChChg_bInFunc_EnableChannel = FALSE;
        return;
      #else
        if( !IsS2InUse() )
        {
            printf("Enable_channel: fEnableSignalMonitor already=1\n");
            g_ChChg_bInFunc_EnableChannel = FALSE;
            return;
        }
      #endif
    }

  #if ENABLE_SDT_OTHER_MONITOR
    MApp_Update_User_Service();
  #endif

    gCurValidSubtitleIndex=0xFFFFFFFF;
    msAPI_CM_Reset_AudioValidIndex();

    //BYTE bSelectedAudStream;

  #if ENABLE_OAD
    //MApp_OAD_SetMonitorState( EN_OAD_MONITOR_STATE_STOP ); //reset MApp_OAD_Monitor()
    //MApp_OAD_SetDownloadState(EN_OAD_DOWNLOAD_STATE_STOP);
  #endif

    //init enCurScreenSaver[] to EN_SCREENSAVER_NULL when channel change
    if (SYS_SCREEN_SAVER_TYPE(MAIN_WINDOW) != EN_SCREENSAVER_NULL)
    {
        SYS_SCREEN_SAVER_TYPE(MAIN_WINDOW) = EN_SCREENSAVER_NULL;
    }
    else if (SYS_SCREEN_SAVER_TYPE(SUB_WINDOW) != EN_SCREENSAVER_NULL)
    {
        SYS_SCREEN_SAVER_TYPE(SUB_WINDOW) = EN_SCREENSAVER_NULL;
    }

#if (ENABLE_CI_PLUS)
    if( TRUE == MApp_CI_IsOpMode() )
    {
        MApp_ChannelChange_SearchDefaultOPAudioLang();
    }
    else
#endif
    {
        MApp_ChannelChange_SearchDefaultAudioLang();   //Fied test UI bug N0.24 rock.tsai//
    }


  #if (ENABLE_CI_PLUS)
    if(TRUE == MApp_CI_IsOpMode())
    {
        MApp_Audio_OpSearchAdAudio();
    }
    else
  #endif
    {
        MApp_Audio_SearchAdAudio(); //_MApp_ChannelChange_SearchAdAudio();            //Search for Ad audio
    }

#if(ENABLE_DVB_AUDIO_DESC)
    if (g_u8AdAudSelected == 0xFF)
    {
        MApp_ChannelChange_SearchBroadcastMixAudio();
    }
#endif
    //else
    //{
    //    MApp_Audio_SetAudioLanguage(g_u8AdAudSelected);
    //}

    MApp_SDT_ResetRunningStatus();

    cRFChannelNumber = msAPI_CM_GetPhysicalChannelNumber(bServiceType,wCurrentPosition);
    wService_ID = msAPI_CM_GetService_ID(bServiceType, wCurrentPosition);
    wTransportStream_ID = msAPI_CM_GetTS_ID(bServiceType, wCurrentPosition);
    wOriginalNetwork_ID = msAPI_CM_GetON_ID(bServiceType,wCurrentPosition);

  #if MHEG5_ENABLE
    g_u16Current_ServicePosition=wCurrentPosition;
  #endif

  #if ENABLE_CI_PLUS
    msAPI_CI_NotifyCurrentServiceInfo(wTransportStream_ID, wService_ID);
    if (msAPI_CI_CardDetect())
    {
        msAPI_CI_HSS_Check();
        msAPI_CI_CC_Reset_URI();
    }
  #endif

    // Set tuner and demod
    MApp_ChannelChange_EnableChannel_ResetTunerAndDemod(cRFChannelNumber, bServiceType, wCurrentPosition);

    if(FALSE == MApp_Dmx_GetMonitorStatus(EN_MONITOR_TABLE_ALL))    //Dummy Case table monitor start
    {
        MApp_Dmx_EnableTableMonitor();
    }

#if MHEG5_ENABLE
    if ( !g_PIDfromMHEG5 && !_bBackDataProgram)
    {
        g_bMHEG5Service=FALSE;
        MApp_SI_Reset(SI_RESET_CHNCHANGE);
    #if ENABLE_TTX
        MApp_TTX_Reset_TTX_Info();
    #endif
    }
#else
    // Reset SI tables
  #if  (ENABLE_TTX)
    MApp_TTX_Reset_TTX_Info();
  #endif
    MApp_SI_Reset(SI_RESET_CHNCHANGE);
#endif // #if MHEG5_ENABLE


#if MHEG5_ENABLE
    MApp_MHEG5_Enable_LiveMHEG5(TRUE);
#endif

//#if ENABLE_T_C_COMBO
if( IsDVBCInUse()
#if (ENABLE_S2 && ASTRA_HD_ENABLE)
    || IsS2InUse()
#endif
    )
{
    MApp_Dmx_Enable_NIT_Other(TRUE);
}
else
{
    MApp_Dmx_Enable_NIT_Other(FALSE);
}

    {
        VIDEO_TYPE u8VideoType=msAPI_CM_GetProgramVideoType(bServiceType, wCurrentPosition);
        VDEC_CodecType eCodecType=E_VDEC_CODEC_TYPE_MPEG2;

        if(u8VideoType == E_VIDEOTYPE_MPEG)
        {
            eCodecType=E_VDEC_CODEC_TYPE_MPEG2;
        }
        else if(u8VideoType == E_VIDEOTYPE_H264)
        {
            eCodecType=E_VDEC_CODEC_TYPE_H264;
        }
        else if(u8VideoType == E_VIDEOTYPE_AVS)
        {
            eCodecType=E_VDEC_CODEC_TYPE_AVS;
        }
        else if(u8VideoType == E_VIDEOTYPE_VC1)
        {
            eCodecType=E_VDEC_CODEC_TYPE_VC1_ADV;
        }
      #if ( CHIP_SUPPORT_HEVC ) //IMPLEMENT_DTV_H265
        else if(u8VideoType == E_VIDEOTYPE_H265)
        {
            eCodecType = E_VDEC_CODEC_TYPE_HEVC;
        }
      #endif
        msAPI_VID_SetMappingAVCParameter(eCodecType);
    }

    // If cur source is not DTV, Change to last DTV source
    if ( SYS_INPUT_SOURCE_TYPE(eWindow) != INPUT_SOURCE_DTV )
    {
        if(eWindow == MAIN_WINDOW)
        {
        #if 1 // 20150908
            MApp_InputSrc_ChangeToLastUiDtvSrc();
        #else
            #if ENABLE_S2
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_S2;
            #elif ENABLE_DVBT
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBT;
            #elif ENABLE_DVBC
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBC;
            #elif ENABLE_DTMB
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DTMB;
            #elif ENABLE_ISDBT
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ISDBT;
            #else
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBT;
            #endif

            MApp_InputSource_SwitchSource( UI_INPUT_SOURCE_TYPE, MAIN_WINDOW );
        #endif
        }
      #if (ENABLE_PIP)
        else if(IsPIPSupported())
        {
          #if ENABLE_S2
            UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_S2;
          #elif ENABLE_DVBT
            UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBT;
          #elif ENABLE_DVBC
            UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBC;
          #elif ENABLE_DTMB
            UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DTMB;
          #elif ENABLE_ISDBT
            UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ISDBT;
          #else
            UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBT;
          #endif

            MApp_InputSource_SwitchSource( UI_SUB_INPUT_SOURCE_TYPE, SUB_WINDOW );
        }
      #endif
    }

    wPCR_PID = msAPI_CM_GetPCR_PID(bServiceType,wCurrentPosition);
    if ( INVALID_PID != wPCR_PID )
    {
        /* set pcr PID & start filter */
        eDMXFLTSTA = msAPI_DMX_StartFilter( wPCR_PID, MSAPI_DMX_FILTER_TYPE_PCR, MApp_Dmx_GetFid(EN_PCR_FID) );
        //printf("a Channel change, eDMXFLTSTA %bu,PCR Pid 0x%x, u8PcrFid %bu\n", eDMXFLTSTA, msAPI_DMX_GetFilterPID(u8PcrFid),u8PcrFid);
    }
  #if MHEG5_ENABLE
    if ( g_PIDfromMHEG5 )
    {
        wVideo_PID = g_u16MHEG5_VideoPID;
    }
    else
  #endif
    {
        wVideo_PID = msAPI_CM_GetVideoPID(bServiceType,wCurrentPosition);
    }

    //printf("wPCR_PID=%d\n",wPCR_PID);
    //printf("wVideo_PID=%d\n",wVideo_PID);

#if MHEG5_ENABLE
  #if MHEG5_NDT_UNINTERRUPT_AV
    if (msAPI_MHEG5_GetNDTChannelChange()==false)
  #endif
    {
        g_u16Current_VideoPID = wVideo_PID;
        g_eCurrent_VideoType = g_eCodecType;
    }
#endif

    if (INVALID_PID != wVideo_PID)
    {
        /* set video PID & start filter */
        //printf("Channel change, Video Pid 0x%x, u8VidFid %bu\n",wVideo_PID,u8VidFid);
        eDMXFLTSTA = msAPI_DMX_StartFilter( wVideo_PID, MSAPI_DMX_FILTER_TYPE_VIDEO, MApp_Dmx_GetFid(EN_VIDEO_FID)  );
        //printf("a Channel change, eDMXFLTSTA %bu,Video Pid 0x%x, u8VidFid %bu\n", eDMXFLTSTA, msAPI_DMX_GetFilterPID(u8VidFid),u8VidFid);

    #if ENABLE_PVR
        if (!(E_PVR_STATE_PLAYBACK == MApp_PVR_StateMachineGet() &&  E_PLAYBACK_STATE_PLAYBACKING== MApp_Playback_StateMachineGet()))
    #endif
        {
        #if (MHEG5_ENABLE && MHEG5_NDT_UNINTERRUPT_AV)
            if (msAPI_MHEG5_GetNDTChannelChange()==false)
        #endif
            {
                msAPI_VID_Init(FALSE, E_VDEC_SRC_MODE_DTV);
            }
        }

    #if ENABLE_PVR
        if (!(E_PVR_STATE_PLAYBACK == MApp_PVR_StateMachineGet() &&  E_PLAYBACK_STATE_PLAYBACKING== MApp_Playback_StateMachineGet()))
    #endif
        {
        #if (MHEG5_ENABLE && MHEG5_NDT_UNINTERRUPT_AV)
            if (msAPI_MHEG5_GetNDTChannelChange()==false)
        #endif
            {
                /* start video decoder */
                msAPI_VID_Command( MSAPI_VID_PLAY );
                MDrv_MVOP_Enable( TRUE );
            }
        }

      #if (MHEG5_ENABLE)
        g_MHEG5Video.bHaveVideo = TRUE;
        msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_MHEG5, DISABLE, 0, MAIN_WINDOW);
      #endif
    }
    else
    {
      #if (MHEG5_ENABLE)
        g_MHEG5Video.bHaveVideo = FALSE;
      #endif
    }

    msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &stAudioStreamInfo, g_u8AudLangSelected);
    msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &stAdAudioStreamInfo, g_u8AdAudSelected);

    if ( wVideo_PID != INVALID_PID &&
        (( stAudioStreamInfo.wAudPID == INVALID_PID ) ||
        ( stAudioStreamInfo.wAudPID == 0))  )
    {
    #if ENABLE_PVR
        if (!(E_PVR_STATE_PLAYBACK == MApp_PVR_StateMachineGet() &&  E_PLAYBACK_STATE_PLAYBACKING== MApp_Playback_StateMachineGet()))
    #endif
        {
        #if (MHEG5_ENABLE && MHEG5_NDT_UNINTERRUPT_AV)
            if (msAPI_MHEG5_GetNDTChannelChange()==false)
        #endif
            {
                // set mvd to freerun in video only program
                //msAPI_VID_MVDCommand( MSAPI_VID_FREERUN );
                msAPI_VID_Command( MSAPI_VID_FREERUN );
            }
        }
    }

    if(wVideo_PID != INVALID_PID && msAPI_CM_GetProgramAttribute(bServiceType,wCurrentPosition, E_ATTRIBUTE_IS_STILL_PICTURE)==FALSE)
    {
        fEnableMvdTimingMonitor = TRUE;
        if( INVALID_PID != stAudioStreamInfo.wAudPID )
        {
        #if ENABLE_PVR
            if (!(E_PVR_STATE_PLAYBACK == MApp_PVR_StateMachineGet() &&  E_PLAYBACK_STATE_PLAYBACKING== MApp_Playback_StateMachineGet()))
        #endif
            {
              #if (ENABLE_PIP)
                if( (MApp_Get_PIPMode() == EN_PIP_MODE_OFF) || UI_IS_AUDIO_SOURCE_IN(eWindow) )
              #endif
                {
                #if (MHEG5_ENABLE && MHEG5_NDT_UNINTERRUPT_AV)
                    if (msAPI_MHEG5_GetNDTChannelChange()==false)
                #endif
                    {
                        MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_AVSYNC);
                    }
                }
            }
        }
    }
    else
    {
        if(wVideo_PID != INVALID_PID && msAPI_CM_GetProgramAttribute(bServiceType,wCurrentPosition, E_ATTRIBUTE_IS_STILL_PICTURE)==TRUE)
            fEnableMvdTimingMonitor = TRUE;
        else
            fEnableMvdTimingMonitor = FALSE;

      #if (ENABLE_PIP)
        if( (MApp_Get_PIPMode() == EN_PIP_MODE_OFF) || UI_IS_AUDIO_SOURCE_IN(eWindow) )
      #endif
        {
          #if MHEG5_ENABLE
            if ( g_PIDfromMHEG5 )
            {
                if( INVALID_PID != (g_u16MHEG5_AudioPID&~0xE000) )
                {
                   MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_FREE_RUN);
                }
            }
            else
          #endif
            {
                if( INVALID_PID != stAudioStreamInfo.wAudPID )
                {
                    MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_FREE_RUN);
                }
            }
        }
    }

    {
        //bSelectedAudStream = msAPI_CM_GetSelectedAudioStream(bServiceType,wCurrentPosition);
        //msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &stAudioStreamInfo, g_u8AudLangSelected/*bSelectedAudStream*/);
      #if MHEG5_ENABLE
        g_u16Current_AudioPID = stAudioStreamInfo.wAudPID;
        //g_u16Current_AudioType = stAudioStreamInfo.wAudType;
        g_u16Current_AudioType = msAPI_CM_Get_AudStreamType_By_AudInfo( (&stAudioStreamInfo) );
      #endif

      #if ENABLE_PVR
        if (!(E_PVR_STATE_PLAYBACK == MApp_PVR_StateMachineGet() &&  E_PLAYBACK_STATE_PLAYBACKING== MApp_Playback_StateMachineGet()))
      #endif
        {
          #if (MHEG5_ENABLE && MHEG5_NDT_UNINTERRUPT_AV)
            if (msAPI_MHEG5_GetNDTChannelChange()== false)
          #endif
            {
            #if ENABLE_AD_DISABLE_MAINAUDIO
                 MApp_Audio_SwitchtoADAudio(TRUE);
            #else
                if ( INVALID_PID != stAudioStreamInfo.wAudPID )
                {
                    /* set audio PID & start filter */
                    //printf("Channel change, audio pid 0x%x, u8AudFid %bu\n",stAudioStreamInfo.wAudPID,MApp_Dmx_GetAudioFid());
                    //eDMXFLTSTA = msAPI_DMX_StartFilter( stAudioStreamInfo.wAudPID, MSAPI_DMX_FILTER_TYPE_AUDIO, MApp_Dmx_GetFid(EN_AUDIO_FID) );
                    eDMXFLTSTA = MApp_Demux_Start_Filter_Audio( stAudioStreamInfo.wAudPID );
                    //printf("a Channel change, eDMXFLTSTA %bu, audio pid 0x%x, u8AudFid %bu\n",eDMXFLTSTA,msAPI_DMX_GetFilterPID(MApp_Dmx_GetAudioFid()),MApp_Dmx_GetAudioFid());

                    /* set decoder system and reload firmware code */
                  #if (ENABLE_PIP)
                    if( (MApp_Get_PIPMode() == EN_PIP_MODE_OFF) || UI_IS_AUDIO_SOURCE_IN(eWindow) )
                  #endif
                    {
                        //MApp_ChannelChange_Set_Audio_Decoder_System(stAudioStreamInfo.wAudType);
                        MApp_ChannelChange_Set_Audio_Decoder_System( msAPI_CM_Get_AudStreamType_By_AudInfo( &stAudioStreamInfo ) );
                    }
                    /* re-sync audio decoder */

                    /* start audio decoder */
                  #if (ENABLE_AUTOTEST || ENABLE_BOOTTIME)
                   #if (ENABLE_BOOTTIME==DISABLE)
                    if (g_bAutobuildDebug == TRUE)
                   #endif
                    {
                        if (gbBootTimeFinish == FALSE)
                        {
                            gU32TmpTime = msAPI_Timer_DiffTimeFromNow(gU32BootTime);
                            printf("[TIME] start audio decoder = %ld\n", gU32TmpTime);
                        }
                    }
                  #endif

                  #if (ENABLE_PIP)
                    if( (MApp_Get_PIPMode() == EN_PIP_MODE_OFF) || UI_IS_AUDIO_SOURCE_IN(eWindow) )
                  #endif
                    {
                        MApi_DMX_AVFifo_Reset(DMX_FILTER_TYPE_AUDIO, TRUE);
                        MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_PLAY);
                        MApi_DMX_AVFifo_Reset(DMX_FILTER_TYPE_AUDIO, FALSE);


                      #if MHEG5_ENABLE
                        if ((msAPI_MHEG5_IsRunning() == TRUE) ||
                            (bServiceType == E_SERVICETYPE_RADIO))
                        {
                            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                        }
                      #endif

                        if (g_u8LRAudioMode == 0)
                        {
                            MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_SoundMode, MSAPI_AUD_MODE_STEREO, 0);
                        }
                        else if (g_u8LRAudioMode == 1)
                        {
                            MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_SoundMode, MSAPI_AUD_MODE_RR, 0);
                            MApi_AUDIO_SetMpegInfo(Audio_MPEG_infoType_SoundMode, MSAPI_AUD_MPEG_SOUNDMODE_RR, 0);
                        }
                        else if (g_u8LRAudioMode == 2)
                        {
                            MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_SoundMode, MSAPI_AUD_MODE_LL, 0);
                            MApi_AUDIO_SetMpegInfo(Audio_MPEG_infoType_SoundMode, MSAPI_AUD_MPEG_SOUNDMODE_LL, 0);
                        }

                        /* if radio channel, since channel change time is small, need additional mute delay
                           to wait DTV audio dac out stable after play command */
                        if ( bServiceType == E_SERVICETYPE_RADIO) {
                            msAPI_Timer_Delayms(250);
                        }
                        else
                        {
                            MApp_Set_Audio_Mute_Timer(TRUE);
                        }

                        // solved scramble->ATV no audio bug.
                        SI_AUDIOSTREAM_TYPE eSIAudStreamType = msAPI_CM_Get_SIAudStreamType_By_AudInfo(&stAudioStreamInfo);

                        //if(E_AUDIOSTREAM_AC3==stAudioStreamInfo.wAudType||E_AUDIOSTREAM_AC3P==stAudioStreamInfo.wAudType)
                        if( E_SI_AUDIOSTREAM_AC3==eSIAudStreamType||E_SI_AUDIOSTREAM_AC3P==eSIAudStreamType)
                        {
                            MApi_AUDIO_SetAC3Info(Audio_AC3_infoType_DrcMode, RF_MODE, 0);    //RF Mod
                            MApi_AUDIO_SetAC3Info(Audio_AC3_infoType_DownmixMode, DOLBY_DOWNMIX_MODE_LTRT, 0);  // LtRt
                            u32AC3CheckTimer = msAPI_Timer_GetTime0();
                            bEnableAC3Check  = TRUE;
                            u8AC3CheckTimes  = 10;
                            //printf("set SPDIF_non-PCM\r\n");
                        }
                        //else if(E_AUDIOSTREAM_AAC==stAudioStreamInfo.wAudType||E_AUDIOSTREAM_MPEG4==stAudioStreamInfo.wAudType)
                        else if(E_SI_AUDIOSTREAM_AAC==eSIAudStreamType||E_SI_AUDIOSTREAM_MPEG4==eSIAudStreamType)
                        {
                            MApi_AUDIO_SetAACInfo(Audio_AAC_infoType_DrcMode, RF_MODE, 0);      //RF Mod
                            MApi_AUDIO_SetAACInfo(Audio_AAC_infoType_DownmixMode, DOLBY_DOWNMIX_MODE_LTRT, 0);
                        }
                        else
                        {
                            //printf("\nWarning: AudType=%u is invalid!\n", stAudioStreamInfo.wAudType);
                            printf("\nWarning: eSIAudStreamType=%u is invalid!\n", eSIAudStreamType);
                        }


                        if(stGenSetting.g_SysSetting.fSPDIFMODE == 0)
                        {
                            MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
                        }
                        else
                        {
                            MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_NONPCM);
                        }
                    }
                    // solved scramble->ATV no audio bug.
                }
            #endif

                // if ad audio exist
                if (INVALID_PID != stAdAudioStreamInfo.wAudPID)
                {
                    //printf("Ad pid found\n");
                    /* Eris ad can not co-exist with AC3 */
                  #if 0
                    if ((stAudioStreamInfo.wAudType == E_AUDIOSTREAM_MPEG) &&
                        (stAdAudioStreamInfo.wAudType == E_AUDIOSTREAM_MPEG))
                  #endif
                    {
                    #if(ENABLE_DVB_AUDIO_DESC)
                        if (stGenSetting.g_SoundSetting.bEnableAD)
                        {
                            //printf("Ad enabled\n");

                          #if (ENABLE_PIP)
                            if( (MApp_Get_PIPMode() == EN_PIP_MODE_OFF) || UI_IS_AUDIO_SOURCE_IN(eWindow) )
                          #endif
                            {
                                if (g_u8AdAudSelected != 0xFF)
                                {
                                    MApp_Audio_SetAdAudio(g_u8AdAudSelected);
                                    MApi_AUDIO_SetADOutputMode(AD_OUT_BOTH);
                                    //MApi_AUDIO_SetCommand(MSAPI_AUD_DVB2_DECCMD_PLAY);
                                }

                                //printf("ADVolume = 0x%02bx\n", msAPI_AUD_ConvertVolumeUnit(stGenSetting.g_SoundSetting.ADVolume));
                                MApp_Audio_AdjustADVolume(stGenSetting.g_SoundSetting.ADVolume);
                            }
                          #if 0
                            MApi_AUDIO_SetADOutputMode(stGenSetting.g_SoundSetting.ADOutput);
                          #endif
                        } // if (stGenSetting.g_SoundSetting.bEnableAD)
                    #endif
                    }
                } // if (INVALID_PID != stAdAudioStreamInfo.wAudPID)
            } // if (msAPI_MHEG5_GetNDTChannelChange() == false)
        }

      #if ENABLE_PVR
        g_u16Current_PCRPID = wPCR_PID;
        g_u16Current_PVR_VideoPID = wVideo_PID;
        g_u16Current_PVR_AudioPID = stAudioStreamInfo.wAudPID;
        //g_wCurrent_AudioType = stAudioStreamInfo.wAudType;
        g_wCurrent_AudioType = msAPI_CM_Get_AudStreamType_By_AudInfo(&stAudioStreamInfo);
        g_eCurrent_PVR_VideoType = g_eCodecType;
        g_u16Current_AudioDescriptorPID = stAdAudioStreamInfo.wAudPID;
      #endif
    }

    //For display AV simultaneously.
  #if ENABLE_PVR
    if (!(E_PVR_STATE_PLAYBACK == MApp_PVR_StateMachineGet() &&  E_PLAYBACK_STATE_PLAYBACKING== MApp_Playback_StateMachineGet()))
  #endif
    {
      #if (MHEG5_ENABLE && MHEG5_NDT_UNINTERRUPT_AV)
        if (msAPI_MHEG5_GetNDTChannelChange()==false)
      #endif
        {
            MApp_VID_VariableInit();
        }
    }
    bH264FirstTimeCheck = TRUE;

    //For display AV simultaneously.
  #if(ENABLE_S2)
    if ( IsDTVInUse() || IsS2InUse())
  #else
    if ( IsDTVInUse() )
  #endif
    {
        UI_Hotkey_Subtitle = FALSE;
    }

  #if 0
    {
        WORD wLCN = msAPI_CM_GetLogicalChannelNumber(bServiceType, wCurrentPosition);

        printf("\nEnable CH>>RF_CH %bu TS_ID %u ON_ID %u S_ID %u LCN %u\n",
            cRFChannelNumber, wTransportStream_ID, wOriginalNetwork_ID, wService_ID, wLCN);
        printf("           V 0x%04x A 0x%04x PCR 0x%04x\n",
            g_u16Current_VideoPID,  g_u16Current_AudioPID, wPCR_PID);
    }
  #endif

  #if MHEG5_ENABLE
    if ( !g_PIDfromMHEG5 )
        MApp_MHEG5_Update_Program(g_u16Current_VideoPID,g_u16Current_AudioPID,g_u16Current_AudioType,g_eCurrent_VideoType);
  #endif

  #if (AV_SYNC_ADJUST)
    MApp_AVSync_ResetAvSyncStatus();
  #endif

    MApp_ParentalRating_EnableChannel();

    MApp_SignalMonitor_Init();

    fEnableSignalMonitor = TRUE;

    //For display AV simultaneously.
    //MApp_ChannelChange_EnableAV();
#if (ENABLE_3D_PROCESS)
    if(DB_3D_SETTING.en3DType != EN_3D_BYPASS || DB_3D_SETTING.en3DTo2DType != EN_3D_TO_2D_OFF )
    {
        msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
    #if (ENABLE_MFC_6M20 || ENABLE_MFC_6M30)
        MApp_ZUI_Set_UI_3D_Mode(E_UI_3D_OUTPUT_MODE_NONE);
        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_ALL);
        MDrv_Ursa_6M30_3D_MODE (PANEL_3D_MODE_NONE);
    #elif(ENABLE_6M40_4KX2K_PROCESS || ENABLE_6M50_4KX2K_PROCESS)
        MApp_ZUI_Set_UI_3D_Mode(E_UI_3D_OUTPUT_MODE_NONE);
        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_ALL);
        MDrv_Ursa_6M40_3D_MODE (PANEL_3D_MODE_NONE);
    #else
        if(DB_3D_SETTING.en3DType != EN_3D_BYPASS)
        {
            DB_3D_SETTING.en3DType = EN_3D_BYPASS;
        #if(ENABLE_NEW_3D_FLOW)
            MApp_Scaler_SetVideo3DMode(DB_3D_SETTING.en3DType);
        #else
            MApp_Scaler_SetVideo3DMode(MAPP_Scaler_Map3DFormatTo3DUserMode(E_XC_3D_INPUT_MODE_NONE));
        #endif
        }

        if (DB_3D_SETTING.en3DTo2DType != EN_3D_TO_2D_OFF)
        {
            DB_3D_SETTING.en3DTo2DType = EN_3D_TO_2D_OFF;
            MApi_Scaler_Set3DInfo(E_XC_3D_INPUT_MODE_NONE, E_XC_3D_OUTPUT_FRAME_L);
        #if(ENABLE_NEW_3D_FLOW)
            MApp_Scaler_SetVideo3DMode(EN_3D_BYPASS);
        #else
            MApp_Scaler_SetVideo3DMode(E_USER_3D_MODE_OFF);
        #endif
        }
    #endif

        msAPI_Scaler_SetBlueScreen(DISABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
    }
#endif


    g_ChChg_bInFunc_EnableChannel = FALSE;

  #if (ENABLE_CH_CHANGE_TIMER_DEBUG == 1)
    g_u32ChannelChangeTimer4 = msAPI_Timer_GetTime0();
  #endif

#if (ENABLE_CHCHANGETIME)
    printf("[ch change time]EnableChannel end = %ld\n", msAPI_Timer_DiffTimeFromNow(gU32ChChangeTime));
#endif
#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("EnableChannel - End");
#endif
}
#endif

void MApp_ChannelChange_EnableChannel_2(SCALER_WIN eWindow)
{
    INPUT_SOURCE_TYPE_t eInputSrcType = SYS_INPUT_SOURCE_TYPE(eWindow);

#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("EnableChannel - Start");
#endif

#if ENABLE_DTV
    MS_TP_SETTING stTempTP;
    memset(&stTempTP, 0x00, sizeof(MS_TP_SETTING)); // fix coverity 207477
#endif

    g_ChChg_bInFunc_EnableChannel = TRUE;


#if( ENABLE_SCRIPT_EXECUTE)
    msUS_UseScript(EN_SCRIPT_EVENT_CHANNELCHANGE);
#endif

    DEBUG_ENABLE_CHANNEL(printf("MApp_ChannelChange_EnableChannel(win=%u)\n", eWindow););

//    SHOW_VIDEO_INFO(("MApp_ChannelChange_EnableChannel eWindow=%d",eWindow));

    bCheckBlockPW = FALSE;
    bCheckParentalPW = FALSE;
    bParentalPWPassCheck = FALSE;
    //g_ParentalRating_u8PreParental_Control = 0xFF;
    //MApp_Set_MonitorParental(TRUE);

    //ZUI_TODO: if( g_u8MenuPageIndex != MENU_CHANNEL_DTV_ManualScan)
    {
      #if (ENABLE_DTV && MHEG5_ENABLE)//for change AV(different channel) in MHEG5
        if (!g_PIDfromMHEG5)
        {
            bStopMonitorBlock=FALSE;
        }
      #else
        bStopMonitorBlock=FALSE;
      #endif
    }


#if ENABLE_ATSC
    if (IsAtscInUse() || IsATVInUse())
    {
        MApp_ChannelChange_EnableChannel_ATSC();
        g_ChChg_bInFunc_EnableChannel = FALSE;
        return;
    }
#endif

    if( IsSrcTypeATV(eInputSrcType))
    {
          // Setup up VD...
        // DVBneed this!!
        msAPI_AVD_SetChannelChange();
    }

    if( fEnableSignalMonitor == TRUE )
    {
      #if (!ENABLE_S2)
        printf("Enable_channel: fEnableSignalMonitor already=1\n");
        g_ChChg_bInFunc_EnableChannel = FALSE;
        return;
      #else
        if( !IsS2InUse() )
        {
            printf("Enable_channel: fEnableSignalMonitor already=1\n");
            g_ChChg_bInFunc_EnableChannel = FALSE;
            return;
        }
      #endif
    }

#if ENABLE_DVB //ENABLE_DTV
  #if ENABLE_SDT_OTHER_MONITOR
    MApp_Update_User_Service();
  #endif

    gCurValidSubtitleIndex=0xFFFFFFFF;
    msAPI_CM_Reset_AudioValidIndex();
#endif

#if (ENABLE_CH_CHANGE_TIMER_DEBUG == 1)
    g_u32ChannelChangeTimer3 = msAPI_Timer_GetTime0();
#endif

#if (ENABLE_CHCHANGETIME)
    printf("[ch change time]EnableChannel start = %ld\n", msAPI_Timer_DiffTimeFromNow(gU32ChChangeTime));
#endif

#if (ENABLE_SBTVD_DTV_SYSTEM)
    if(msAPI_SRC_IS_SBTVD_InUse())
    {
        MApi_DMX_RemoveDupAVPkt(TRUE);
    }
#endif

    MApp_CheckBlockProgramme();

    if( IsSrcTypeATV(eInputSrcType) )
    {
        if ( eInputSrcType != INPUT_SOURCE_TV )
        {
            if(eWindow == MAIN_WINDOW)
            {
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ATV;
                MApp_InputSource_SwitchSource( UI_INPUT_SOURCE_TYPE, MAIN_WINDOW );
            }
          #if (ENABLE_PIP)
            else if(IsPIPSupported())
            {
                MApp_InputSource_SwitchSource( UI_INPUT_SOURCE_ATV, SUB_WINDOW );
            }
          #endif
        }

        CHANNELCHANGE_DBINFO(printf("Enable ATV channel, need to be added\n"));

        //msAPI_VD_3DCombSpeedup();
        //msAPI_AVD_SetChannelChange();

      #if (ENABLE_PIP)
        if( (MApp_Get_PIPMode() == EN_PIP_MODE_OFF) || UI_IS_AUDIO_SOURCE_IN(eWindow) )
      #endif
        {
            MApi_AUDIO_SIF_SendCmd(MSAPI_AUD_SIF_CMD_SET_PLAY,0,0);
            MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
        }
    }
#if ENABLE_DVB//ENABLE_DTV
    else
    {
        BYTE cRFChannelNumber;
        WORD wVideo_PID;
//        WORD wAudPID;
        WORD wPCR_PID;
        WORD wService_ID;
        WORD wTransportStream_ID;
        WORD wOriginalNetwork_ID;
        AUD_INFO stAudioStreamInfo;
        AUD_INFO stAdAudioStreamInfo;
        MEMBER_SERVICETYPE bServiceType;
        WORD wCurrentPosition;
        DMX_FILTER_STATUS eDMXFLTSTA;
        //BYTE bSelectedAudStream;

      #if ENABLE_OAD
        //MApp_OAD_SetMonitorState( EN_OAD_MONITOR_STATE_STOP ); //reset MApp_OAD_Monitor()
        //MApp_OAD_SetDownloadState(EN_OAD_DOWNLOAD_STATE_STOP);
      #endif

        //init enCurScreenSaver[] to EN_SCREENSAVER_NULL when channel change
        if (SYS_SCREEN_SAVER_TYPE(MAIN_WINDOW) != EN_SCREENSAVER_NULL)
        {
            SYS_SCREEN_SAVER_TYPE(MAIN_WINDOW) = EN_SCREENSAVER_NULL;
        }
        else if (SYS_SCREEN_SAVER_TYPE(SUB_WINDOW) != EN_SCREENSAVER_NULL)
        {
            SYS_SCREEN_SAVER_TYPE(SUB_WINDOW) = EN_SCREENSAVER_NULL;
        }

    #if (ENABLE_CI_PLUS)
        if( TRUE == MApp_CI_IsOpMode() )
        {
            MApp_ChannelChange_SearchDefaultOPAudioLang();
        }
        else
    #endif
        {
            MApp_ChannelChange_SearchDefaultAudioLang();   //Fied test UI bug N0.24 rock.tsai//
        }


      #if (ENABLE_CI_PLUS)
        if(TRUE == MApp_CI_IsOpMode())
        {
            MApp_Audio_OpSearchAdAudio();
        }
        else
      #endif
        {
            MApp_Audio_SearchAdAudio(); //_MApp_ChannelChange_SearchAdAudio();            //Search for Ad audio
        }

    #if(ENABLE_DVB_AUDIO_DESC)
        if (g_u8AdAudSelected == 0xFF)
        {
            MApp_ChannelChange_SearchBroadcastMixAudio();
        }
    #endif
        //else
        //{
        //    MApp_Audio_SetAudioLanguage(g_u8AdAudSelected);
        //}

        MApp_SDT_ResetRunningStatus();

        bServiceType = msAPI_CM_GetCurrentServiceType();
        wCurrentPosition = msAPI_CM_GetCurrentPosition(bServiceType);

        DEBUG_ENABLE_CHANNEL(printf("1bServiceType =%u\n", bServiceType););
        DEBUG_ENABLE_CHANNEL(printf("1wCurrentPosition =%u\n", wCurrentPosition););


#if(ENABLE_S2_FAST_SCAN)
        if(IsS2InUse())
        {
            if(msAPI_CM_GetScanType(bServiceType, wCurrentPosition))
            {
                MApp_SI_Set_M7DVBS_OpenMonitor(TRUE);
                printf("\n\n\n M7 Monitor TRUE\n\n\n");
            }
            else
            {
                MApp_SI_Set_M7DVBS_OpenMonitor(FALSE);
                printf("\n\n\n M7 Monitor FALSE\n\n\n");
            }
        }
        else
        {
            printf("\n\n\n M7 Monitor do nothing\n\n\n");
        }
#endif
        if ( (msAPI_CM_CountProgram( E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO) == 0)
           &&(msAPI_CM_CountProgram( E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO) == 0)
          #if NORDIG_FUNC //for Nordig Spec v2.0
           &&(msAPI_CM_CountProgram( E_SERVICETYPE_DATA, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO) == 0)
          #endif
            )
        {
            g_ChChg_bInFunc_EnableChannel = FALSE;
            return;
        }

    #if 0//ENABLE_T_C_COMBO
      #if ENABLE_T_C_CHANNEL_MIX
        //switch demod type
        if( msAPI_CM_GetProgramAttribute(bServiceType,wCurrentPosition, E_ATTRIBUTE_IS_TERRESTRIAL) == IsDVBCInUse() )
        {
            stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType ^= 1;
            msAPI_Tuner_SwitchSource((EN_DVB_TYPE)stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType, TRUE);
        }
      #endif
    #endif

        if(msAPI_CM_GetProgramAttribute(bServiceType,wCurrentPosition, E_ATTRIBUTE_IS_DELETED)==TRUE
        || msAPI_CM_GetProgramAttribute(bServiceType,wCurrentPosition, E_ATTRIBUTE_IS_VISIBLE)==FALSE
        )
        {
            enChannelChangeRetVal =EXIT_NULL;
            u8KeyCode = KEY_CHANNEL_MINUS;
            MApp_ChannelChange_ProcessUserInput();
        }

        cRFChannelNumber = msAPI_CM_GetPhysicalChannelNumber(bServiceType,wCurrentPosition);
        wService_ID = msAPI_CM_GetService_ID(bServiceType, wCurrentPosition);
        wTransportStream_ID = msAPI_CM_GetTS_ID(bServiceType, wCurrentPosition);
        wOriginalNetwork_ID = msAPI_CM_GetON_ID(bServiceType,wCurrentPosition);

    #if MHEG5_ENABLE
        MApp_BlockSysSetCurrentService(bServiceType,wCurrentPosition);
        g_eCurrentRealServiceType=g_eCurrentUserServiceType = bServiceType;

        if(bServiceType == E_SERVICETYPE_RADIO)
            g_wCurrentRadioRealServicePosition=g_wCurrentRadioUserServicePosition = wCurrentPosition;
      #if NORDIG_FUNC //for Nordig Spec v2.0
        else if(bServiceType == E_SERVICETYPE_DATA)
            g_wCurrentDataRealServicePosition=g_wCurrentDataUserServicePosition = wCurrentPosition;
      #endif
        else
            g_wCurrentTVRealServicePosition=g_wCurrentTVUserServicePosition = wCurrentPosition;

        g_u16CurrentServiceID=wService_ID;
        g_wCurrentTS_ID=wTransportStream_ID;
        g_wCurrent_ONID=wOriginalNetwork_ID;
    #endif

        if(msAPI_CM_GetProgramAttribute(bServiceType,wCurrentPosition, E_ATTRIBUTE_IS_DELETED)==TRUE)
        {
            g_ChChg_bInFunc_EnableChannel = FALSE;
            return;
        }

      #if MHEG5_ENABLE
        g_u16Current_ServicePosition=wCurrentPosition;
      #endif

      #if ENABLE_CI_PLUS
        msAPI_CI_NotifyCurrentServiceInfo(wTransportStream_ID, wService_ID);
        #if ENABLE_CI_PLUS_V1_4
            DTV_CHANNEL_INFO ChannelInfo;
            if(msAPI_CM_GetProgramInfo(bServiceType, wCurrentPosition, &ChannelInfo) == TRUE)
            {
                if(ChannelInfo.stCHAttribute.bIsVirtualSevice)
                    msAPI_CI_AppInfo_EnterCicamVirtualChannel();
            }

        #endif
        if (msAPI_CI_CardDetect())
        {
            msAPI_CI_HSS_Check();
            msAPI_CI_CC_Reset_URI();
        }
      #endif

      #if (ENABLE_BOOTTIME)
        if (gbBootTimeFinish == FALSE)
            gU32BootStepTime = msAPI_Timer_GetTime0();
      #endif

        PRINT_AUTOTEST_CHECKPT_TIME("start FE init");

        // Set tuner and demod
        MApp_ChannelChange_EnableChannel_ResetTunerAndDemod(cRFChannelNumber, bServiceType, wCurrentPosition);

      #if(ENABLE_BOOTTIME)
        if (gbBootTimeFinish == FALSE)
        {
            BOOLEAN bResult = 0;

            while(1)
            {
                static MS_U8 counter=0;
                msAPI_Tuner_CheckLock( &bResult,TRUE);

                if(bResult)
                {
                    gU32TmpTime = msAPI_Timer_DiffTimeFromNow(gU32BootStepTime);
                    printf("[TIME] FE Lock Time = %ld\n", gU32TmpTime);
                    break;
                }
                else
                {
                    msAPI_Timer_Delayms(100);
                    if(counter++ >20)
                        break;
                }
            }
        }
      #endif // #if(ENABLE_BOOTTIME)

        if(FALSE == MApp_Dmx_GetMonitorStatus(EN_MONITOR_TABLE_ALL))    //Dummy Case table monitor start
        {
            MApp_Dmx_EnableTableMonitor();
        }

    #if MHEG5_ENABLE
        if ( !g_PIDfromMHEG5 && !_bBackDataProgram)
        {
            g_bMHEG5Service=FALSE;
            MApp_SI_Reset(SI_RESET_CHNCHANGE);
        #if ENABLE_TTX
            MApp_TTX_Reset_TTX_Info();
        #endif
        }
    #else
        // Reset SI tables
      #if  (ENABLE_TTX)
        MApp_TTX_Reset_TTX_Info();
      #endif
        MApp_SI_Reset(SI_RESET_CHNCHANGE);
    #endif // #if MHEG5_ENABLE


    #if MHEG5_ENABLE
        MApp_MHEG5_Enable_LiveMHEG5(TRUE);
    #endif

    //#if ENABLE_T_C_COMBO
    if( IsDVBCInUse()
#if (ENABLE_S2 && ASTRA_HD_ENABLE)
        || IsS2InUse()
#endif
        )
    {
        MApp_Dmx_Enable_NIT_Other(TRUE);
    }
    else
    {
        MApp_Dmx_Enable_NIT_Other(FALSE);
    }

    //#elif ENABLE_DVBC
    //    MApp_Dmx_Enable_NIT_Other(TRUE);
    //#else
    //    MApp_Dmx_Enable_NIT_Other(FALSE);
    //#endif

        {
            VIDEO_TYPE u8VideoType=msAPI_CM_GetProgramVideoType(bServiceType, wCurrentPosition);
            VDEC_CodecType eCodecType=E_VDEC_CODEC_TYPE_MPEG2;

            if(u8VideoType == E_VIDEOTYPE_MPEG)
            {
                eCodecType=E_VDEC_CODEC_TYPE_MPEG2;
            }
            else if(u8VideoType == E_VIDEOTYPE_H264)
            {
                eCodecType=E_VDEC_CODEC_TYPE_H264;
            }
            else if(u8VideoType == E_VIDEOTYPE_AVS)
            {
                eCodecType=E_VDEC_CODEC_TYPE_AVS;
            }
            else if(u8VideoType == E_VIDEOTYPE_VC1)
            {
                eCodecType=E_VDEC_CODEC_TYPE_VC1_ADV;
            }
          #if ( CHIP_SUPPORT_HEVC ) //IMPLEMENT_DTV_H265
            else if(u8VideoType == E_VIDEOTYPE_H265)
            {
                eCodecType = E_VDEC_CODEC_TYPE_HEVC;
            }
          #endif
            msAPI_VID_SetMappingAVCParameter(eCodecType);
        }

        // If cur source is not DTV, Change to last DTV source
        if ( SYS_INPUT_SOURCE_TYPE(eWindow) != INPUT_SOURCE_DTV )
        {
            if(eWindow == MAIN_WINDOW)
            {
            #if 1 // 20150908
                MApp_InputSrc_ChangeToLastUiDtvSrc();
            #else
                #if ENABLE_S2
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_S2;
                #elif ENABLE_DVBT
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBT;
                #elif ENABLE_DVBC
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBC;
                #elif ENABLE_DTMB
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DTMB;
                #elif ENABLE_ISDBT
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ISDBT;
                #else
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBT;
                #endif

                MApp_InputSource_SwitchSource( UI_INPUT_SOURCE_TYPE, MAIN_WINDOW );
            #endif
            }
          #if (ENABLE_PIP)
            else if(IsPIPSupported())
            {
              #if ENABLE_S2
                UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_S2;
              #elif ENABLE_DVBT
                UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBT;
              #elif ENABLE_DVBC
                UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBC;
              #elif ENABLE_DTMB
                UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DTMB;
              #elif ENABLE_ISDBT
                UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ISDBT;
              #else
                UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBT;
              #endif

                MApp_InputSource_SwitchSource( UI_SUB_INPUT_SOURCE_TYPE, SUB_WINDOW );
            }
          #endif
        }

        wPCR_PID = msAPI_CM_GetPCR_PID(bServiceType,wCurrentPosition);
        if ( INVALID_PID != wPCR_PID )
        {
            /* set pcr PID & start filter */
            eDMXFLTSTA = msAPI_DMX_StartFilter( wPCR_PID, MSAPI_DMX_FILTER_TYPE_PCR, MApp_Dmx_GetFid(EN_PCR_FID) );
            //printf("a Channel change, eDMXFLTSTA %bu,PCR Pid 0x%x, u8PcrFid %bu\n", eDMXFLTSTA, msAPI_DMX_GetFilterPID(u8PcrFid),u8PcrFid);
        }
      #if MHEG5_ENABLE
        if ( g_PIDfromMHEG5 )
        {
            wVideo_PID = g_u16MHEG5_VideoPID;
        }
        else
      #endif
        {
            wVideo_PID = msAPI_CM_GetVideoPID(bServiceType,wCurrentPosition);
        }

        //printf("wPCR_PID=%d\n",wPCR_PID);
        //printf("wVideo_PID=%d\n",wVideo_PID);

    #if MHEG5_ENABLE
      #if MHEG5_NDT_UNINTERRUPT_AV
        if (msAPI_MHEG5_GetNDTChannelChange()==false)
      #endif
        {
            g_u16Current_VideoPID = wVideo_PID;
            g_eCurrent_VideoType = g_eCodecType;
        }
    #endif

        if (INVALID_PID != wVideo_PID)
        {
            /* set video PID & start filter */
            //printf("Channel change, Video Pid 0x%x, u8VidFid %bu\n",wVideo_PID,u8VidFid);
            eDMXFLTSTA = msAPI_DMX_StartFilter( wVideo_PID, MSAPI_DMX_FILTER_TYPE_VIDEO, MApp_Dmx_GetFid(EN_VIDEO_FID)  );
            //printf("a Channel change, eDMXFLTSTA %bu,Video Pid 0x%x, u8VidFid %bu\n", eDMXFLTSTA, msAPI_DMX_GetFilterPID(u8VidFid),u8VidFid);

        #if ENABLE_PVR
            if (!(E_PVR_STATE_PLAYBACK == MApp_PVR_StateMachineGet() &&  E_PLAYBACK_STATE_PLAYBACKING== MApp_Playback_StateMachineGet()))
        #endif
            {
            #if (MHEG5_ENABLE && MHEG5_NDT_UNINTERRUPT_AV)
                if (msAPI_MHEG5_GetNDTChannelChange()==false)
            #endif
                {
                    msAPI_VID_Init(FALSE, E_VDEC_SRC_MODE_DTV);
                }
            }

        #if ENABLE_PVR
            if (!(E_PVR_STATE_PLAYBACK == MApp_PVR_StateMachineGet() &&  E_PLAYBACK_STATE_PLAYBACKING== MApp_Playback_StateMachineGet()))
        #endif
            {
            #if (MHEG5_ENABLE && MHEG5_NDT_UNINTERRUPT_AV)
                if (msAPI_MHEG5_GetNDTChannelChange()==false)
            #endif
                {
                    /* start video decoder */
                #if (ENABLE_AUTOTEST || ENABLE_BOOTTIME)
                  #if (ENABLE_BOOTTIME==DISABLE)
                    if (g_bAutobuildDebug == TRUE)
                  #endif
                    {
                        if (gbBootTimeFinish == FALSE)
                        {
                            gU32TmpTime = msAPI_Timer_DiffTimeFromNow(gU32BootTime);
                            printf("[TIME] start video decoder = %ld\n", gU32TmpTime);
                        }
                    }
                #endif
                    msAPI_VID_Command( MSAPI_VID_PLAY );

                    MDrv_MVOP_Enable( TRUE );
                }
            }

          #if (MHEG5_ENABLE)
            g_MHEG5Video.bHaveVideo = TRUE;
            msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_MHEG5, DISABLE, 0, MAIN_WINDOW);
          #endif
        }
        else
        {
          #if (MHEG5_ENABLE)
            g_MHEG5Video.bHaveVideo = FALSE;
          #endif
        }

        msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &stAudioStreamInfo, g_u8AudLangSelected);
        msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &stAdAudioStreamInfo, g_u8AdAudSelected);

        if ( wVideo_PID != INVALID_PID &&
            (( stAudioStreamInfo.wAudPID == INVALID_PID ) ||
            ( stAudioStreamInfo.wAudPID == 0))  )
        {
        #if ENABLE_PVR
            if (!(E_PVR_STATE_PLAYBACK == MApp_PVR_StateMachineGet() &&  E_PLAYBACK_STATE_PLAYBACKING== MApp_Playback_StateMachineGet()))
        #endif
            {
            #if (MHEG5_ENABLE && MHEG5_NDT_UNINTERRUPT_AV)
                if (msAPI_MHEG5_GetNDTChannelChange()==false)
            #endif
                {
                    // set mvd to freerun in video only program
                    //msAPI_VID_MVDCommand( MSAPI_VID_FREERUN );
                    msAPI_VID_Command( MSAPI_VID_FREERUN );
                }
            }
        }

        if(wVideo_PID != INVALID_PID && msAPI_CM_GetProgramAttribute(bServiceType,wCurrentPosition, E_ATTRIBUTE_IS_STILL_PICTURE)==FALSE)
        {
            fEnableMvdTimingMonitor = TRUE;
            if( INVALID_PID != stAudioStreamInfo.wAudPID )
            {
            #if ENABLE_PVR
                if (!(E_PVR_STATE_PLAYBACK == MApp_PVR_StateMachineGet() &&  E_PLAYBACK_STATE_PLAYBACKING== MApp_Playback_StateMachineGet()))
            #endif
                {
                  #if (ENABLE_PIP)
                    if( (MApp_Get_PIPMode() == EN_PIP_MODE_OFF) || UI_IS_AUDIO_SOURCE_IN(eWindow) )
                  #endif
                    {
                    #if (MHEG5_ENABLE && MHEG5_NDT_UNINTERRUPT_AV)
                        if (msAPI_MHEG5_GetNDTChannelChange()==false)
                    #endif
                        {
                            MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_AVSYNC);
                        }
                    }
                }
            }
        }
        else
        {
            if(wVideo_PID != INVALID_PID && msAPI_CM_GetProgramAttribute(bServiceType,wCurrentPosition, E_ATTRIBUTE_IS_STILL_PICTURE)==TRUE)
                fEnableMvdTimingMonitor = TRUE;
            else
                fEnableMvdTimingMonitor = FALSE;

          #if (ENABLE_PIP)
            if( (MApp_Get_PIPMode() == EN_PIP_MODE_OFF) || UI_IS_AUDIO_SOURCE_IN(eWindow) )
          #endif
            {
              #if MHEG5_ENABLE
                if ( g_PIDfromMHEG5 )
                {
                    if( INVALID_PID != (g_u16MHEG5_AudioPID&~0xE000) )
                    {
                       MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_FREE_RUN);
                    }
                }
                else
              #endif
                {
                    if( INVALID_PID != stAudioStreamInfo.wAudPID )
                    {
                        MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_FREE_RUN);
                    }
                }
            }
        }

    #if MHEG5_ENABLE
        if ( g_PIDfromMHEG5 )
        {
            AUDIOSTREAM_TYPE wAudType;
            if((g_u16MHEG5_AudioPID&0xE000) == 0x8000)
            {
                wAudType=E_AUDIOSTREAM_AC3;
            }
            else if((g_u16MHEG5_AudioPID&0xE000) == 0x2000)
            {
                wAudType=E_AUDIOSTREAM_MPEG4;
            }
            else if((g_u16MHEG5_AudioPID&0xE000) == 0x4000)
            {
                wAudType=E_AUDIOSTREAM_AAC;
            }
            else if((g_u16MHEG5_AudioPID&0xE000) == 0x6000)
            {
                wAudType=E_AUDIOSTREAM_AC3P;
            }
            else
            {
                wAudType=E_AUDIOSTREAM_MPEG;
            }

            msAPI_DMX_StartFilter( g_u16MHEG5_AudioPID&~0xE000, MSAPI_DMX_FILTER_TYPE_AUDIO,MApp_Dmx_GetFid(EN_AUDIO_FID) );

          #if (ENABLE_PIP)
            if( (MApp_Get_PIPMode() == EN_PIP_MODE_OFF) || UI_IS_AUDIO_SOURCE_IN(eWindow) )
          #endif
            {
                MApp_ChannelChange_Set_Audio_Decoder_System(wAudType);
                MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_PLAY);
            }

        #if (MHEG5_ENABLE && MHEG5_NDT_UNINTERRUPT_AV)
            if (msAPI_MHEG5_GetNDTChannelChange()==false)
        #endif
            {
                g_u16Current_AudioPID = g_u16MHEG5_AudioPID&~0xE000;
                g_u16Current_AudioType = wAudType;
            }
        }
        else
    #endif // #if MHEG5_ENABLE
        {
            //bSelectedAudStream = msAPI_CM_GetSelectedAudioStream(bServiceType,wCurrentPosition);
            //msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &stAudioStreamInfo, g_u8AudLangSelected/*bSelectedAudStream*/);
          #if MHEG5_ENABLE
            g_u16Current_AudioPID = stAudioStreamInfo.wAudPID;
            //g_u16Current_AudioType = stAudioStreamInfo.wAudType;
            g_u16Current_AudioType = msAPI_CM_Get_AudStreamType_By_AudInfo( (&stAudioStreamInfo) );
          #endif

          #if ENABLE_PVR
            if (!(E_PVR_STATE_PLAYBACK == MApp_PVR_StateMachineGet() &&  E_PLAYBACK_STATE_PLAYBACKING== MApp_Playback_StateMachineGet()))
          #endif
            {
              #if (MHEG5_ENABLE && MHEG5_NDT_UNINTERRUPT_AV)
                if (msAPI_MHEG5_GetNDTChannelChange()== false)
              #endif
                {
                #if ENABLE_AD_DISABLE_MAINAUDIO
                     MApp_Audio_SwitchtoADAudio(TRUE);
                #else
                    if ( INVALID_PID != stAudioStreamInfo.wAudPID )
                    {
                        /* set audio PID & start filter */
                        //printf("Channel change, audio pid 0x%x, u8AudFid %bu\n",stAudioStreamInfo.wAudPID,MApp_Dmx_GetAudioFid());
                        //eDMXFLTSTA = msAPI_DMX_StartFilter( stAudioStreamInfo.wAudPID, MSAPI_DMX_FILTER_TYPE_AUDIO, MApp_Dmx_GetFid(EN_AUDIO_FID) );
                        eDMXFLTSTA = MApp_Demux_Start_Filter_Audio( stAudioStreamInfo.wAudPID );
                        //printf("a Channel change, eDMXFLTSTA %bu, audio pid 0x%x, u8AudFid %bu\n",eDMXFLTSTA,msAPI_DMX_GetFilterPID(MApp_Dmx_GetAudioFid()),MApp_Dmx_GetAudioFid());

                        /* set decoder system and reload firmware code */
                      #if (ENABLE_PIP)
                        if( (MApp_Get_PIPMode() == EN_PIP_MODE_OFF) || UI_IS_AUDIO_SOURCE_IN(eWindow) )
                      #endif
                        {
                            //MApp_ChannelChange_Set_Audio_Decoder_System(stAudioStreamInfo.wAudType);
                            MApp_ChannelChange_Set_Audio_Decoder_System( msAPI_CM_Get_AudStreamType_By_AudInfo( &stAudioStreamInfo ) );
                        }


                        /* re-sync audio decoder */

                        /* start audio decoder */
                      #if (ENABLE_AUTOTEST || ENABLE_BOOTTIME)
                       #if (ENABLE_BOOTTIME==DISABLE)
                        if (g_bAutobuildDebug == TRUE)
                       #endif
                        {
                            if (gbBootTimeFinish == FALSE)
                            {
                                gU32TmpTime = msAPI_Timer_DiffTimeFromNow(gU32BootTime);
                                printf("[TIME] start audio decoder = %ld\n", gU32TmpTime);
                            }
                        }
                      #endif

                      #if (ENABLE_PIP)
                        if( (MApp_Get_PIPMode() == EN_PIP_MODE_OFF) || UI_IS_AUDIO_SOURCE_IN(eWindow) )
                      #endif
                        {
                            MApi_DMX_AVFifo_Reset(DMX_FILTER_TYPE_AUDIO, TRUE);
                            MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_PLAY);
                            MApi_DMX_AVFifo_Reset(DMX_FILTER_TYPE_AUDIO, FALSE);


                          #if MHEG5_ENABLE
                            if ((msAPI_MHEG5_IsRunning() == TRUE) ||
                                (bServiceType == E_SERVICETYPE_RADIO))
                            {
                                msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                            }
                          #endif

                            if (g_u8LRAudioMode == 0)
                            {
                                MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_SoundMode, MSAPI_AUD_MODE_STEREO, 0);
                            }
                            else if (g_u8LRAudioMode == 1)
                            {
                                MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_SoundMode, MSAPI_AUD_MODE_RR, 0);
                                MApi_AUDIO_SetMpegInfo(Audio_MPEG_infoType_SoundMode, MSAPI_AUD_MPEG_SOUNDMODE_RR, 0);
                            }
                            else if (g_u8LRAudioMode == 2)
                            {
                                MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_SoundMode, MSAPI_AUD_MODE_LL, 0);
                                MApi_AUDIO_SetMpegInfo(Audio_MPEG_infoType_SoundMode, MSAPI_AUD_MPEG_SOUNDMODE_LL, 0);
                            }

                            /* if radio channel, since channel change time is small, need additional mute delay
                               to wait DTV audio dac out stable after play command */
                            if ( bServiceType == E_SERVICETYPE_RADIO) {
                                msAPI_Timer_Delayms(250);
                            }
                            else
                            {
                                MApp_Set_Audio_Mute_Timer(TRUE);
                            }

                            // solved scramble->ATV no audio bug.
                            SI_AUDIOSTREAM_TYPE eSIAudStreamType = msAPI_CM_Get_SIAudStreamType_By_AudInfo(&stAudioStreamInfo);
                        #if 1
                            switch( eSIAudStreamType )
                            {
                                case E_SI_AUDIOSTREAM_AC3:
                                case E_SI_AUDIOSTREAM_AC3P:
                                {
                                    MApi_AUDIO_SetAC3Info(Audio_AC3_infoType_DrcMode, RF_MODE, 0);    //RF Mod
                                    MApi_AUDIO_SetAC3Info(Audio_AC3_infoType_DownmixMode, DOLBY_DOWNMIX_MODE_LTRT, 0);  // LtRt
                                    u32AC3CheckTimer = msAPI_Timer_GetTime0();
                                    bEnableAC3Check  = TRUE;
                                    u8AC3CheckTimes  = 10;
                                    //printf("set SPDIF_non-PCM\r\n");
                                }
                                    break;

                                case E_SI_AUDIOSTREAM_AAC:
                                case E_SI_AUDIOSTREAM_MPEG4:
                                    MApi_AUDIO_SetAACInfo(Audio_AAC_infoType_DrcMode, RF_MODE, 0);      //RF Mod
                                    MApi_AUDIO_SetAACInfo(Audio_AAC_infoType_DownmixMode, DOLBY_DOWNMIX_MODE_LTRT, 0);
                                    break;

                                case E_SI_AUDIOSTREAM_MPEG:
                                    // Do nothing
                                    break;

                                default:
                                    printf("\nWarning: eSIAudStreamType=%u is invalid!\n", eSIAudStreamType);
                                    break;
                            }
                        #else
                            //if(E_AUDIOSTREAM_AC3==stAudioStreamInfo.wAudType||E_AUDIOSTREAM_AC3P==stAudioStreamInfo.wAudType)
                            if( E_SI_AUDIOSTREAM_AC3==eSIAudStreamType||E_SI_AUDIOSTREAM_AC3P==eSIAudStreamType)
                            {
                                MApi_AUDIO_SetAC3Info(Audio_AC3_infoType_DrcMode, RF_MODE, 0);    //RF Mod
                                MApi_AUDIO_SetAC3Info(Audio_AC3_infoType_DownmixMode, DOLBY_DOWNMIX_MODE_LTRT, 0);  // LtRt
                                u32AC3CheckTimer = msAPI_Timer_GetTime0();
                                bEnableAC3Check  = TRUE;
                                u8AC3CheckTimes  = 10;
                                //printf("set SPDIF_non-PCM\r\n");
                            }
                            //else if(E_AUDIOSTREAM_AAC==stAudioStreamInfo.wAudType||E_AUDIOSTREAM_MPEG4==stAudioStreamInfo.wAudType)
                            else if(E_SI_AUDIOSTREAM_AAC==eSIAudStreamType||E_SI_AUDIOSTREAM_MPEG4==eSIAudStreamType)
                            {
                                MApi_AUDIO_SetAACInfo(Audio_AAC_infoType_DrcMode, RF_MODE, 0);      //RF Mod
                                MApi_AUDIO_SetAACInfo(Audio_AAC_infoType_DownmixMode, DOLBY_DOWNMIX_MODE_LTRT, 0);
                            }
                            else if( E_SI_AUDIOSTREAM_MPEG == eSIAudStreamType)
                            {
                                // Do nothing
                            }
                            else
                            {
                                //printf("\nWarning: AudType=%u is invalid!\n", stAudioStreamInfo.wAudType);
                                printf("\nWarning: eSIAudStreamType=%u is invalid!\n", eSIAudStreamType);
                            }
                        #endif

                            if(stGenSetting.g_SysSetting.fSPDIFMODE == 0)
                            {
                                MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
                            }
                            else
                            {
                                MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_NONPCM);
                            }
                        }
                        // solved scramble->ATV no audio bug.
                    }
                #endif

                    // if ad audio exist
                    if (INVALID_PID != stAdAudioStreamInfo.wAudPID)
                    {
                        //printf("Ad pid found\n");
                        /* Eris ad can not co-exist with AC3 */
                      #if 0
                        if ((stAudioStreamInfo.wAudType == E_AUDIOSTREAM_MPEG) &&
                            (stAdAudioStreamInfo.wAudType == E_AUDIOSTREAM_MPEG))
                      #endif
                        {
                        #if(ENABLE_DVB_AUDIO_DESC)
                            if (stGenSetting.g_SoundSetting.bEnableAD)
                            {
                                //printf("Ad enabled\n");

                              #if (ENABLE_PIP)
                                if( (MApp_Get_PIPMode() == EN_PIP_MODE_OFF) || UI_IS_AUDIO_SOURCE_IN(eWindow) )
                              #endif
                                {
                                    if (g_u8AdAudSelected != 0xFF)
                                    {
                                        MApp_Audio_SetAdAudio(g_u8AdAudSelected);
                                        MApi_AUDIO_SetADOutputMode(AD_OUT_BOTH);
                                        //MApi_AUDIO_SetCommand(MSAPI_AUD_DVB2_DECCMD_PLAY);
                                    }

                                    //printf("ADVolume = 0x%02bx\n", msAPI_AUD_ConvertVolumeUnit(stGenSetting.g_SoundSetting.ADVolume));
                                    MApp_Audio_AdjustADVolume(stGenSetting.g_SoundSetting.ADVolume);
                                }
                              #if 0
                                MApi_AUDIO_SetADOutputMode(stGenSetting.g_SoundSetting.ADOutput);
                              #endif
                            } // if (stGenSetting.g_SoundSetting.bEnableAD)
                        #endif
                        }
                    } // if (INVALID_PID != stAdAudioStreamInfo.wAudPID)
                } // if (msAPI_MHEG5_GetNDTChannelChange() == false)
            }

          #if ENABLE_PVR
            g_u16Current_PCRPID = wPCR_PID;
            g_u16Current_PVR_VideoPID = wVideo_PID;
            g_u16Current_PVR_AudioPID = stAudioStreamInfo.wAudPID;
            //g_wCurrent_AudioType = stAudioStreamInfo.wAudType;
            g_wCurrent_AudioType = msAPI_CM_Get_AudStreamType_By_AudInfo(&stAudioStreamInfo);
            g_eCurrent_PVR_VideoType = g_eCodecType;
            g_u16Current_AudioDescriptorPID = stAdAudioStreamInfo.wAudPID;
          #endif
        }

        //For display AV simultaneously.
      #if ENABLE_PVR
        if (!(E_PVR_STATE_PLAYBACK == MApp_PVR_StateMachineGet() &&  E_PLAYBACK_STATE_PLAYBACKING== MApp_Playback_StateMachineGet()))
      #endif
        {
          #if (MHEG5_ENABLE && MHEG5_NDT_UNINTERRUPT_AV)
            if (msAPI_MHEG5_GetNDTChannelChange()==false)
          #endif
            {
                MApp_VID_VariableInit();
            }
        }
        bH264FirstTimeCheck = TRUE;

        //For display AV simultaneously.
      #if(ENABLE_S2)
        if ( IsDTVInUse() || IsS2InUse())
      #else
        if ( IsDTVInUse() )
      #endif
        {
            UI_Hotkey_Subtitle = FALSE;
        }

      #if 0
        {
            WORD wLCN = msAPI_CM_GetLogicalChannelNumber(bServiceType, wCurrentPosition);

            printf("\nEnable CH>>RF_CH %bu TS_ID %u ON_ID %u S_ID %u LCN %u\n",
                cRFChannelNumber, wTransportStream_ID, wOriginalNetwork_ID, wService_ID, wLCN);
            printf("           V 0x%04x A 0x%04x PCR 0x%04x\n",
                g_u16Current_VideoPID,  g_u16Current_AudioPID, wPCR_PID);
        }
      #endif

      #if MHEG5_ENABLE
        if ( !g_PIDfromMHEG5 )
            MApp_MHEG5_Update_Program(g_u16Current_VideoPID,g_u16Current_AudioPID,g_u16Current_AudioType,g_eCurrent_VideoType);
      #endif

      #if (AV_SYNC_ADJUST)
        MApp_AVSync_ResetAvSyncStatus();
      #endif

        MApp_ParentalRating_EnableChannel();

    }
#endif // #if ENABLE_DVB//ENABLE_DTV

    MApp_SignalMonitor_Init();

    fEnableSignalMonitor = TRUE;

    DEBUG_ENABLE_CHANNEL( printf("Enable_channel: fEnableSignalMonitor=1\n"); );

    //For display AV simultaneously.
    //MApp_ChannelChange_EnableAV();
#if (ENABLE_3D_PROCESS)
    if(DB_3D_SETTING.en3DType != EN_3D_BYPASS || DB_3D_SETTING.en3DTo2DType != EN_3D_TO_2D_OFF )
    {
        msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);

    #if (ENABLE_MFC_6M20 || ENABLE_MFC_6M30)
        MApp_ZUI_Set_UI_3D_Mode(E_UI_3D_OUTPUT_MODE_NONE);
        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_ALL);
        MDrv_Ursa_6M30_3D_MODE (PANEL_3D_MODE_NONE);
    #elif(ENABLE_6M40_4KX2K_PROCESS || ENABLE_6M50_4KX2K_PROCESS)
        MApp_ZUI_Set_UI_3D_Mode(E_UI_3D_OUTPUT_MODE_NONE);
        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_ALL);
        MDrv_Ursa_6M40_3D_MODE (PANEL_3D_MODE_NONE);
    #else
        if(DB_3D_SETTING.en3DType != EN_3D_BYPASS)
        {
            DB_3D_SETTING.en3DType = EN_3D_BYPASS;
        #if(ENABLE_NEW_3D_FLOW)
            MApp_Scaler_SetVideo3DMode(DB_3D_SETTING.en3DType);
        #else
            MApp_Scaler_SetVideo3DMode(MAPP_Scaler_Map3DFormatTo3DUserMode(E_XC_3D_INPUT_MODE_NONE));
        #endif
        }

        if (DB_3D_SETTING.en3DTo2DType != EN_3D_TO_2D_OFF)
        {
            DB_3D_SETTING.en3DTo2DType = EN_3D_TO_2D_OFF;
            MApi_Scaler_Set3DInfo(E_XC_3D_INPUT_MODE_NONE, E_XC_3D_OUTPUT_FRAME_L);
        #if(ENABLE_NEW_3D_FLOW)
            MApp_Scaler_SetVideo3DMode(EN_3D_BYPASS);
        #else
            MApp_Scaler_SetVideo3DMode(E_USER_3D_MODE_OFF);
        #endif
        }
    #endif

        msAPI_Scaler_SetBlueScreen(DISABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
    }
#endif


    g_ChChg_bInFunc_EnableChannel = FALSE;

  #if (ENABLE_CH_CHANGE_TIMER_DEBUG == 1)
    g_u32ChannelChangeTimer4 = msAPI_Timer_GetTime0();
  #endif

#if (ENABLE_CHCHANGETIME)
    printf("[ch change time]EnableChannel end = %ld\n", msAPI_Timer_DiffTimeFromNow(gU32ChChangeTime));
#endif
#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("EnableChannel - End");
#endif
}

BOOLEAN MApp_ChChg_IsInEnableChannel(void)
{
    return g_ChChg_bInFunc_EnableChannel;
}


#if ENABLE_PIP
void MApp_ChannelChange_PIP_ChangeAudioSource2TV (SCALER_WIN eWindow)
{
    if(IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(eWindow)))
    {
        MApi_AUDIO_SIF_SendCmd(MSAPI_AUD_SIF_CMD_SET_PLAY, 0,0);
        MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
    }
#if ENABLE_DTV
    else
    {
        BYTE cRFChannelNumber;
        WORD wVideo_PID;
//        WORD wAudPID;
        WORD wService_ID;
        WORD wTransportStream_ID;
        WORD wOriginalNetwork_ID;
        AUD_INFO stAudioStreamInfo;
        AUD_INFO stAdAudioStreamInfo;
        MEMBER_SERVICETYPE bServiceType;
        WORD wCurrentPosition;
        //BYTE bSelectedAudStream;

    #if (ENABLE_CI_PLUS)
        if(TRUE == MApp_CI_IsOpMode())
        {
            MApp_ChannelChange_SearchDefaultOPAudioLang();
        }
        else
        {
            MApp_ChannelChange_SearchDefaultAudioLang();   //Fied test UI bug N0.24 rock.tsai//
        }
    #else
        MApp_ChannelChange_SearchDefaultAudioLang();   //Fied test UI bug N0.24 rock.tsai//
    #endif

    #if (ENABLE_CI_PLUS)
        if(TRUE == MApp_CI_IsOpMode())
        {
            MApp_Audio_OpSearchAdAudio();
        }
        else
    #endif
        MApp_Audio_SearchAdAudio(); //_MApp_ChannelChange_SearchAdAudio();            //Search for Ad audio

        if(g_u8AdAudSelected == 0xFF)
        {
            MApp_ChannelChange_SearchBroadcastMixAudio();
        }
        //else
        //{
         //   MApp_Audio_SetAudioLanguage(g_u8AdAudSelected);
        //}

        MApp_SDT_ResetRunningStatus();
        bServiceType = msAPI_CM_GetCurrentServiceType();
        wCurrentPosition = msAPI_CM_GetCurrentPosition(bServiceType);
        cRFChannelNumber = msAPI_CM_GetPhysicalChannelNumber(bServiceType,wCurrentPosition);
        wService_ID = msAPI_CM_GetService_ID(bServiceType, wCurrentPosition);
        wTransportStream_ID = msAPI_CM_GetTS_ID(bServiceType, wCurrentPosition);
        wOriginalNetwork_ID = msAPI_CM_GetON_ID(bServiceType,wCurrentPosition);


    #if MHEG5_ENABLE
        g_eCurrentRealServiceType=g_eCurrentUserServiceType = bServiceType;

        if(bServiceType == E_SERVICETYPE_RADIO)
            g_wCurrentRadioRealServicePosition=g_wCurrentRadioUserServicePosition = wCurrentPosition;
      #if NORDIG_FUNC //for Nordig Spec v2.0
        else if(bServiceType == E_SERVICETYPE_DATA)
            g_wCurrentDataRealServicePosition=g_wCurrentDataUserServicePosition = wCurrentPosition;
      #endif
        else
            g_wCurrentTVRealServicePosition=g_wCurrentTVUserServicePosition = wCurrentPosition;

        g_u16CurrentServiceID=wService_ID;
        g_wCurrentTS_ID=wTransportStream_ID;
        g_wCurrent_ONID=wOriginalNetwork_ID;
    #endif

        if(msAPI_CM_GetProgramAttribute(bServiceType,wCurrentPosition, E_ATTRIBUTE_IS_DELETED)==TRUE)
        {
            return;
        }

    #if MHEG5_ENABLE
        g_u16Current_ServicePosition=wCurrentPosition;
    #endif

    #if MHEG5_ENABLE
        if ( g_PIDfromMHEG5 )
        {
            wVideo_PID = g_u16MHEG5_VideoPID;
        }
        else
    #endif
        {
            wVideo_PID = msAPI_CM_GetVideoPID(bServiceType,wCurrentPosition);
        }

        //printf("wPCR_PID=%d\n",wPCR_PID);
        //printf("wVideo_PID=%d\n",wVideo_PID);

        msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &stAudioStreamInfo, g_u8AudLangSelected);
        msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &stAdAudioStreamInfo, g_u8AdAudSelected);

        if(wVideo_PID != INVALID_PID && msAPI_CM_GetProgramAttribute(bServiceType,wCurrentPosition, E_ATTRIBUTE_IS_STILL_PICTURE)==FALSE)
        {
            if( INVALID_PID != stAudioStreamInfo.wAudPID )
            {
              #if ENABLE_PVR
                if (!(E_PVR_STATE_PLAYBACK == MApp_PVR_StateMachineGet() &&  E_PLAYBACK_STATE_PLAYBACKING== MApp_Playback_StateMachineGet()))
              #endif
                {
                    MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_AVSYNC);
                }
            }
        }
        else
        {
          #if MHEG5_ENABLE
            if ( g_PIDfromMHEG5 )
            {
                if( INVALID_PID != (g_u16MHEG5_AudioPID&~0xE000) )
                {
                   MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_FREE_RUN);
                }
            }
            else
          #endif
            {
                if( INVALID_PID != stAudioStreamInfo.wAudPID )
                {
                    MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_FREE_RUN);
                }
            }
        }


        AUDIOSTREAM_TYPE eAudStreamType = msAPI_CM_Get_AudStreamType_By_AudInfo(&stAudioStreamInfo);


    #if MHEG5_ENABLE
        if ( g_PIDfromMHEG5 )
        {
            WORD wAudType;
            if((g_u16MHEG5_AudioPID&0xE000) == 0x8000)
            {
                wAudType=E_AUDIOSTREAM_AC3;
            }
            else if((g_u16MHEG5_AudioPID&0xE000) == 0x2000)
            {
                wAudType=E_AUDIOSTREAM_MPEG4;
            }
            else if((g_u16MHEG5_AudioPID&0xE000) == 0x4000)
            {
                wAudType=E_AUDIOSTREAM_AAC;
            }
            else if((g_u16MHEG5_AudioPID&0xE000) == 0x6000)
            {
                wAudType=E_AUDIOSTREAM_AC3P;
            }
            else
            {
                wAudType=E_AUDIOSTREAM_MPEG;
            }

            MApp_ChannelChange_Set_Audio_Decoder_System(wAudType);
            MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_PLAY);
        }
        else
    #endif
        {
            //bSelectedAudStream = msAPI_CM_GetSelectedAudioStream(bServiceType,wCurrentPosition);
            //msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &stAudioStreamInfo, g_u8AudLangSelected/*bSelectedAudStream*/);
        #if MHEG5_ENABLE
            g_u16Current_AudioPID = stAudioStreamInfo.wAudPID;
            //g_u16Current_AudioType = stAudioStreamInfo.wAudType;
            g_u16Current_AudioType = eAudStreamType;
        #endif

        #if ENABLE_PVR
            if (!(E_PVR_STATE_PLAYBACK == MApp_PVR_StateMachineGet() &&  E_PLAYBACK_STATE_PLAYBACKING== MApp_Playback_StateMachineGet()))
        #endif
            {
                if ( INVALID_PID != stAudioStreamInfo.wAudPID )
                {
                    /* set decoder system and reload firmware code */
                    //MApp_ChannelChange_Set_Audio_Decoder_System(stAudioStreamInfo.wAudType);
                    MApp_ChannelChange_Set_Audio_Decoder_System(eAudStreamType);

                    MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_PLAY);

                #if MHEG5_ENABLE
                    if ((msAPI_MHEG5_IsRunning() == TRUE) ||
                        (bServiceType == E_SERVICETYPE_RADIO))
                    {
                        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                    }
                #endif
                    if (g_u8LRAudioMode == 0)
                    {
                        MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_SoundMode, MSAPI_AUD_MODE_STEREO, 0);
                    }
                    else if (g_u8LRAudioMode == 1)
                    {
                        MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_SoundMode, MSAPI_AUD_MODE_RR, 0);
                        MApi_AUDIO_SetMpegInfo(Audio_MPEG_infoType_SoundMode, MSAPI_AUD_MPEG_SOUNDMODE_RR, 0);
                    }
                    else if (g_u8LRAudioMode == 2)
                    {
                        MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_SoundMode, MSAPI_AUD_MODE_LL, 0);
                        MApi_AUDIO_SetMpegInfo(Audio_MPEG_infoType_SoundMode, MSAPI_AUD_MPEG_SOUNDMODE_LL, 0);
                    }
                    /* if radio channel, since channel change time is small, need additional mute delay
                       to wait DTV audio dac out stable after play command */
                    if ( bServiceType == E_SERVICETYPE_RADIO) {
                        msAPI_Timer_Delayms(250);
                    }
                    else
                    {
                        MApp_Set_Audio_Mute_Timer(TRUE);
                    }
                    // solved scramble->ATV no audio bug.
                    if(E_AUDIOSTREAM_AC3==eAudStreamType||E_AUDIOSTREAM_AC3P==eAudStreamType)
                    {
                        MApi_AUDIO_SetAC3Info(Audio_AC3_infoType_DrcMode, RF_MODE, 0);    //RF Mod
                        MApi_AUDIO_SetAC3Info(Audio_AC3_infoType_DownmixMode, DOLBY_DOWNMIX_MODE_LTRT, 0);  // LtRt
                        u32AC3CheckTimer = msAPI_Timer_GetTime0();
                        bEnableAC3Check  = TRUE;
                        u8AC3CheckTimes  = 10;
                        //printf("set SPDIF_non-PCM\r\n");
                        if(stGenSetting.g_SysSetting.fSPDIFMODE == 0)
                        {
                            MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
                        }
                        else
                        {
                            MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_NONPCM);
                        }
                    }
                    else if(E_AUDIOSTREAM_AAC==eAudStreamType||E_AUDIOSTREAM_MPEG4==eAudStreamType)
                    {
                        MApi_AUDIO_SetAACInfo(Audio_AAC_infoType_DrcMode, RF_MODE, 0);    //RF Mod
                        MApi_AUDIO_SetAACInfo(Audio_AAC_infoType_DownmixMode, DOLBY_DOWNMIX_MODE_LTRT, 0);
                        if(stGenSetting.g_SysSetting.fSPDIFMODE == 0)
                        {
                            MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
                        }
                        else
                        {
                            MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_NONPCM);
                        }
                    }
                // solved scramble->ATV no audio bug.
                }

                // if ad audio exist
                if (INVALID_PID != stAdAudioStreamInfo.wAudPID)
                {
                    //printf("Ad pid found\n");
                    /* Eris ad can not co-exist with AC3 */
                    #if 0
                    if ((stAudioStreamInfo.wAudType == E_AUDIOSTREAM_MPEG) &&
                        (stAdAudioStreamInfo.wAudType == E_AUDIOSTREAM_MPEG))
                    #endif
                    {
                        if (stGenSetting.g_SoundSetting.bEnableAD)
                        {
                            //printf("Ad enabled\n");
                            if (g_u8AdAudSelected != 0xFF)
                            {
                                MApp_Audio_SetAdAudio(g_u8AdAudSelected);
                                MApi_AUDIO_SetADOutputMode(AD_OUT_BOTH);
                                //MApi_AUDIO_SetCommand(MSAPI_AUD_DVB2_DECCMD_PLAY);
                            }

                            //printf("ADVolume = 0x%02bx\n", msAPI_AUD_ConvertVolumeUnit(stGenSetting.g_SoundSetting.ADVolume));
                            MApp_Audio_AdjustADVolume(stGenSetting.g_SoundSetting.ADVolume);
                            #if 0
                            MApi_AUDIO_SetADOutputMode(stGenSetting.g_SoundSetting.ADOutput);
                            #endif
                        }
                        //printf("set SPDIF_PCM\r\n");
                        //MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
                    }
                }
            }
        }
    }
#endif
}
#endif

/* // No used
EN_DETECT_SIGNAL_STATE MApp_ChannelChange_DetectSignalStatus(E_UI_INPUT_SOURCE input_type)
{
    EN_DETECT_SIGNAL_STATE ret = STATE_DETECT_SIGNAL_ERROR;

    switch(input_type)
    {
    #if ENABLE_DVB //( ENABLE_DTV )
      #if ENABLE_S2
        case UI_INPUT_SOURCE_S2:
      #endif
      #if ENABLE_DVBT
        case UI_INPUT_SOURCE_DVBT:
      #endif
      #if ENABLE_DVBC
        case UI_INPUT_SOURCE_DVBC:
      #endif
      #if ENABLE_DTMB
        case UI_INPUT_SOURCE_DTMB:
      #endif
      #if ENABLE_ISDBT
        case UI_INPUT_SOURCE_ISDBT:
      #endif
        {
            // For TV mode
            if(MApp_GetSignalStatus()==SIGNAL_UNLOCK)
                ret = STATE_DETECT_SIGNAL_NOSIGNAL;
            else
                ret = STATE_DETECT_SIGNAL_OK;

            break;
        }
    #endif // #if ENABLE_DVB


        case UI_INPUT_SOURCE_ATV:
        {
            if(IsVDHasSignal()==FALSE)
            {
                // no sync
                ret = STATE_DETECT_SIGNAL_NOSIGNAL;
            }
            else
            {
                ret = STATE_DETECT_SIGNAL_OK;
            }

            break;
        }


    #if (INPUT_YPBPR_VIDEO_COUNT >= 1)
        case UI_INPUT_SOURCE_COMPONENT:  // VIDEO - YPbPr    2
    #endif
        case UI_INPUT_SOURCE_RGB:    // PC - VGA         3
        {
            if(MApi_XC_PCMonitor_SyncLoss(MAIN_WINDOW) && g_bPCSignalMonitor==TRUE)
            {
                // it's for delay until it detects the signal or reach the max re-try counts
                if(g_u8PCSignalMonitorCounter<10)
                {
                    g_bPCSignalMonitor = FALSE;
                    g_u8PCSignalMonitorCounter++;
                    return STATE_DETECT_SIGNAL_INPROGRESS_NOSIGNAL;
                }
                else
                {
                    ret = STATE_DETECT_SIGNAL_NOSIGNAL;
                }
            }
            else if ((MApp_PCMode_GetCurrentState(MAIN_WINDOW) == E_PCMODE_STABLE_UN_SUPPORT_MODE)&&g_bPCSignalMonitor==TRUE)
            {
                ret = STATE_DETECT_SIGNAL_PC_UNSUPPORT_MODE;
            }
            else if (MApi_XC_PCMonitor_SyncLoss(MAIN_WINDOW) && g_bPCSignalMonitor==FALSE)
            {
                return STATE_DETECT_SIGNAL_INPROGRESS_NOSIGNAL;
            }

            g_bPCSignalMonitor = FALSE;
            g_u8PCSignalMonitorCounter = 0;

            if ( (ret != STATE_DETECT_SIGNAL_NOSIGNAL)
               &&(ret != STATE_DETECT_SIGNAL_PC_UNSUPPORT_MODE) )
            {
                ret = STATE_DETECT_SIGNAL_OK;
            }

            break;
        }


    #if (INPUT_AV_VIDEO_COUNT >= 1)
        case UI_INPUT_SOURCE_AV:   // VIDEO - CVBS       1
        {
            CHANNELCHANGE_DBINFO(printf("AYAY_MMM,%u\n",(U16)SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)));
            if(IsVDHasSignal()==FALSE)
            {
                // no sync
                ret = STATE_DETECT_SIGNAL_NOSIGNAL;
            }
            else
            {
                ret = STATE_DETECT_SIGNAL_OK;
            }

            break;
        }
    #endif

        default:
            break;
    }

    return ret;
}
*/

/************************************************************************************/
EN_RET MApp_ChannelChange_ShowAnalogBanner ( void )
{
    enChannelChangeRetVal =EXIT_NULL;

    switch (enChannelChangeState)
    {
        case STATE_CHANNELCHANGE_INIT:
        {
            if (MApp_ZUI_GetActive_ChannelInfo_OSD())
            {
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_CH_BANNER);
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_CH_INFO);
            }
            else
            {
                MApp_ZUI_ACT_Startup_ChannelInfo_OSD();//ZUI: MApp_UiMenu_ExecuteKeyEvent( MIA_PROGRAM_INFO_MSG_BOX );
                if(IsAnyTVSourceInUse())
                {
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_BRIEF_CH_INFO);
                }
                else
                {
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_SOURCE_BANNER);
                }
            }
            enChannelChangeState = STATE_CHANNELCHANGE_DISPLAY;//STATE_CHANNELCHANGE_WAITKEY;
            u32ChannelChangeTimer = msAPI_Timer_GetTime0();
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();

            break;
        }


        case STATE_CHANNELCHANGE_DISPLAY:
        {
            if ((msAPI_Timer_DiffTimeFromNow(u32ChannelChangeTimer ) > u32InfoOSD_Duration)
                ||u8KeyCode!=KEY_NULL)
            {
                //ZUI: enCurTVWin=DISP_WIN_NONEOSD;
                enChannelChangeRetVal =EXIT_CLOSE;
                enChannelChangeState = STATE_CHANNELCHANGE_INIT;
                g_bRealTimeMonitorOnly = FALSE;
            }

            break;
        }


        default:
            break;
    }

    return enChannelChangeRetVal;
}

/************************************************************************************/

void MApp_ChannelChange_CheckBlockChannelPW(void)
{
    /*/ZUI_TODO:
    MApp_UiMenu_ExecuteKeyEvent(MIA_EXIT);
    MApp_TopStateMachine_SetTopState(STATE_TOP_MENU);
    enUiMainMenuState = STATE_UIMENU_WAIT;
    enMenuFlowState = FS_MAIN_MENU;
    MApp_UiMenu_ExecuteKeyEvent(MIA_ENTER_BLOCK_CH_PASSWORD);
    */
    MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_PASSWORD_INPUT_MSGBOX);
}


#if(ENABLE_S2_CHCHANGE_NOT_SAVE_DTAR)
extern U32 u32Enable_Change_Timer;
#endif

EN_RET MApp_ChannelChange ( void )
{
#if ((BRAZIL_CC)||(ATSC_CC == ATV_CC))
#if BRAZIL_CC
    if(IS_SBTVD_APP)
#endif
    {
        //MApp_CC_ResetExistInfo();
        msAPI_CC_Reset(); // jany edit

#if ENABLE_ISDB_ATV_VCHIP
        MApp_VChip_Init();
        MApp_CC_Initialize();
        fVChipPassWordEntered= FALSE;
#endif
    }
#endif

#if ENABLE_PVR
    if(MApp_PVR_IsRecording())
        MApp_PVR_StateMachineRunning();
#endif

//static Bool bFontLoadF=1;
#if MHEG5_ENABLE
    if (enChannelChangeState == STATE_CHANNELCHANGE_INIT)
    {
        MApp_ChannelPosition_Restore();
    }
#endif

    enChannelChangeRetVal =EXIT_NULL;

    MApp_ChannelChange_ProcessUserInput();

#if STATE_PRINT
    if ( u8KeyCode != KEY_NULL )
    {
        //printf( "CC:%bx ", enChannelChangeState );
    }
#endif

#if 0
    #if ENABLE_CI
    if ( msAPI_CI_MMICheckEvent() )
    {
        //MApp_ChannelChange_Exit();
        //if(fWaitforMSGBoxFading)
        //{
        //    MApp_DM_DeleteOsd(FS_WAIT_MENU, IDLE_CHANNELINO_WIN);
        //}
        // need to do more

        enChannelChangeRetVal =EXIT_CLOSE;
        enChannelChangeState = STATE_CHANNELCHANGE_INIT;
        g_bRealTimeMonitorOnly = FALSE;
        return enChannelChangeRetVal;
    }
    #endif
#endif

    switch ( enChannelChangeState )
    {
        case STATE_CHANNELCHANGE_INIT:
        {
            CHANNELCHANGE_DBINFO( printf( "STATE_CHANNELCHANGE_INIT\n" ) );
            // TV<-> Radio switch is enable when there is not searched Radio pr. And when show installation guide the banner can't display.
            enChannelChangeState = STATE_CHANNELCHANGE_DISPLAY;
            g_bRealTimeMonitorOnly = TRUE;

            g_u8LRAudioMode = 0; //Init for Audio language
        }
        break;

        case STATE_CHANNELCHANGE_SHOWINFO:
        {
            CHANNELCHANGE_DBINFO(printf("\r\n STATE_CHANNELCHANGE_SHOWINFO"));

          #if ENABLE_PVR
            if (!(E_PVR_STATE_PLAYBACK == MApp_PVR_StateMachineGet() &&  E_PLAYBACK_STATE_PLAYBACKING== MApp_Playback_StateMachineGet()))
          #endif
            {
                if (MApp_ZUI_GetActive_ChannelInfo_OSD())
                {
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_CH_BANNER);
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_CH_INFO);
                }
                else
                {
                    MApp_ZUI_ACT_Startup_ChannelInfo_OSD();//ZUI: MApp_UiMenu_ExecuteKeyEvent( MIA_PROGRAM_INFO_MSG_BOX );
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_BRIEF_CH_INFO);
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_TV_BANNER);
                }
            }

            fWaitforMSGBoxFading = TRUE;
            enChannelChangeState = STATE_CHANNELCHANGE_MSGBOX_FADING;//STATE_CHANNELCHANGE_WAITKEY;

            u32ChannelChangeTimer = msAPI_Timer_GetTime0();
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
        }
        break;


        case STATE_CHANNELCHANGE_DISPLAY:
        {
            CHANNELCHANGE_DBINFO( printf( "\r\n STATE_CHANNELCHANGE_DISPLAY" ) );

            g_bRealTimeMonitorOnly = TRUE;
            g_u8LRAudioMode = 0; //Init for Audio language

            //ZUI_TODO: g_showParentalRatingDrawed =FALSE;
        #if (ENABLE_PIP)
            if(IsPIPSupported())
            {
                if ( (MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
                   &&( IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))
                     ||IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) )
                    )
                {
                    // TV src is on sub window
                  #if ENABLE_CI_PLUS
                    if(DB_CI_PLUS_SETTING.bInOpMenu && bPowerOnEnterOPMode)
                    {
                        //Fix 1250523: [Marlon_120B][CI+1.3] Test 7.2.8.1 enter op channel , press CH+ key , invalid service message display
                        MApp_CI_EnterCiOperatorProfile(DB_CI_PLUS_SETTING.u8OpIndex);
                        //bPowerOnEnterOPMode = FALSE;
                        MApp_ChannelChange_EnableChannel(SUB_WINDOW);

                    }
                    else
                  #endif
                    {
                        #if ENABLE_CI_PLUS
                        bPowerOnEnterOPMode = FALSE;
                        #endif
                        MApp_ChannelChange_EnableChannel(SUB_WINDOW);
                    }
                    stGenSetting.stScanMenuSetting.u8ChType = MApp_InputSource_GetUIInputSourceType(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW));
                }
                else
                {
                  #if ENABLE_CI_PLUS
                    if(DB_CI_PLUS_SETTING.bInOpMenu && bPowerOnEnterOPMode)
                    {
                        //Fix 1250523: [Marlon_120B][CI+1.3] Test 7.2.8.1 enter op channel , press CH+ key , invalid service message display
                        MApp_CI_EnterCiOperatorProfile(DB_CI_PLUS_SETTING.u8OpIndex);
                        //bPowerOnEnterOPMode = FALSE;
                        MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
                    }
                    else
                  #endif
                    {
                        #if ENABLE_CI_PLUS
                        bPowerOnEnterOPMode = FALSE;
                        #endif
                        MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
                    }
                    stGenSetting.stScanMenuSetting.u8ChType = UI_INPUT_SOURCE_TYPE;
                }
            }
            else
        #endif // #if (ENABLE_PIP)
            {
            #if ENABLE_CI_PLUS
                if(DB_CI_PLUS_SETTING.bInOpMenu && bPowerOnEnterOPMode)
                {
                    //Fix 1250523: [Marlon_120B][CI+1.3] Test 7.2.8.1 enter op channel , press CH+ key , invalid service message display
                    MApp_CI_EnterCiOperatorProfile(DB_CI_PLUS_SETTING.u8OpIndex);
                    //bPowerOnEnterOPMode = FALSE;
                    MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
                }
                else
            #endif
                {
                    #if ENABLE_CI_PLUS
                    bPowerOnEnterOPMode = FALSE;
                    #endif
                    MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
                }
                stGenSetting.stScanMenuSetting.u8ChType = UI_INPUT_SOURCE_TYPE;
            }

            //enChannelChangeState = STATE_CHANNELCHANGE_SHOWINFO;

            bNextEvent = FALSE;

        #if (MHEG5_ENABLE)
          #if(ENABLE_S2)
            if ( IsDTVInUse() || IsS2InUse()
          #else
            if ( IsDTVInUse()
          #endif
          #if (ENABLE_PIP)
               &&(MApp_Get_PIPMode() == EN_PIP_MODE_OFF)
          #endif
               )
            {
                enCheckMHEGLoadingStatus = EN_MHEG5_MONITOR;
                msAPI_MHEG5_SetGoBackMHEG5(false);

                MApp_TV_DSMCC_Trigger_Monitor();
            }
        #endif

            {
            #if ENABLE_PVR
                if( !(E_PVR_STATE_PLAYBACK == MApp_PVR_StateMachineGet() &&  E_PLAYBACK_STATE_PLAYBACKING == MApp_Playback_StateMachineGet()) )
            #endif  //#if ENABLE_PVR
                {
                #if ( ENABLE_OAD )
                    if( !( EN_OAD_MONITOR_STATE_STOP == MApp_OAD_GetMonitorState() ) )
                #endif  //ENABLE_OAD
                    {
                    #if ENABLE_ATSC
                        if (MApp_ZUI_ACT_IsChInfoMode(TYPE_CHANNEL_BANNER))
                        {
                        #if (ENABLE_MESSAGE_BOX_DISPLAY_TIMING)
                            //MApp_ZUI_ACT_ExecuteChannelInfoAction(EN_EXE_CHINFO_BANNER_PROG_TIMIMG_RESET);
                            MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CHINFO_BANNER_PROG_TIMIMG_RESET);
                        #else
                            MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CHINFO_BANNER_RESET);
                        #endif
                        }

                        if (u8KeyCode != KEY_INFO)
                        {
                            enChannelInfoPageType = TYPE_CHANNEL_BANNER;
                        }
                    #endif // #if ENABLE_ATSC

                        if (MApp_ZUI_GetActive_ChannelInfo_OSD())
                        {
                            MApp_ZUI_ACT_ShutdownOSD();
                            MApp_ZUI_ACT_Startup_ChannelInfo_OSD();
                        }
                        else
                        {
                            MApp_ZUI_ACT_Startup_ChannelInfo_OSD();
                        }

                        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_BRIEF_CH_INFO);
                        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_TV_BANNER);
                    }
                }

                fWaitforMSGBoxFading = TRUE;
                enChannelChangeState = STATE_CHANNELCHANGE_MSGBOX_FADING;//STATE_CHANNELCHANGE_WAITKEY;
                u32ChannelChangeTimer = msAPI_Timer_GetTime0();
                u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            }
        }
        break;

        case STATE_CHANNELCHANGE_MSGBOX_FADING:
        {
            //CHANNELCHANGE_DBINFO(printf("STATE_CHANNELCHANGE_MSGBOX_FADING\n"));
        #if (MHEG5_ENABLE)
          #if(ENABLE_S2)
            if ( IsDTVInUse() || IsS2InUse()
          #else
            if ( IsDTVInUse()
          #endif
          #if (ENABLE_PIP)
               &&(MApp_Get_PIPMode() == EN_PIP_MODE_OFF)
          #endif
               )
            {
                MApp_TV_DSMCC_Trigger_Monitor();
            }
        #endif // #if (MHEG5_ENABLE)

            if ( (FALSE == fWaitforMSGBoxFading)
               ||(msAPI_Timer_DiffTimeFromNow(u32ChannelChangeTimer ) > (u32InfoOSD_Duration-3500L)) //unit = ms
               )
            {
            #if MHEG5_ENABLE
                if (msAPI_MHEG5_GetBinStatus() == FALSE
                    //#if (ENABLE_PIP)
                    //&& (MApp_Get_PIPMode() == EN_PIP_MODE_OFF)
                    //#endif
                    )
                {
                    if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
                    {
                        // Initial Beon for DTV
                        msAPI_MHEG5_Bean_Init();
                    }
                }
            #endif
                enChannelChangeRetVal =EXIT_CLOSE;
                enChannelChangeState = STATE_CHANNELCHANGE_INIT;
                g_bRealTimeMonitorOnly = FALSE;
            }

        #if ENABLE_CI
           #if (ENABLE_PIP)
            else if ( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
                    ||(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) && (MApp_Get_PIPMode() != EN_PIP_MODE_OFF)))
           #else
            else if ( IsDTVInUse()
                  #if ENABLE_S2
                    ||IsS2InUse()
                  #endif
                    )
           #endif
            {
                // Speed up CI.
                if (msAPI_CI_CardDetect() == FALSE)
                {
                    if (msAPI_CI_Polling()) { }
                }
                else
                {
                    msAPI_CI_MAINLOOP();
                }
            }
        #endif // #if ENABLE_CI
        }
        break;


        default:
            break;
    }


#if ENABLE_PVR
    if(MApp_PVR_IsRecording())
        MApp_PVR_StateMachineRunning();
#endif

#if(ENABLE_S2_CHCHANGE_NOT_SAVE_DTAR)
     u32Enable_Change_Timer = msAPI_Timer_GetTime0();
#endif

    return enChannelChangeRetVal;
}

//
//******************************************************************************
//

#if ENABLE_DVB
BOOLEAN MApp_ChannelChange_ChangeSpeciChannel( U16 u16InputValue, U16 wOriginalNetwork_ID, U16 wTransportStream_ID, EN_MHEG_5_TUNE_TYPE bType, BOOLEAN bCheckTsID, BOOLEAN bShowDisplayInfo )
{
  #if MHEG5_ENABLE
    MEMBER_SERVICETYPE eCurrentUserServiceType;
    WORD wCurrentUserServicePosition;
  #endif
    MEMBER_SERVICETYPE bServiceType,eGotServiceType;
    BOOLEAN bResult=FALSE;
    U16 u16CurPosition,u16GotPosition,u16Loop,u16LCN,U16LoopEnd;
    U8 u8PhyNum = INVALID_PHYSICAL_CHANNEL_NUMBER;

    if (( MApp_TopStateMachine_GetTopState() != STATE_TOP_CHANNELCHANGE)&&
        ( MApp_TopStateMachine_GetTopState() != STATE_TOP_MENU)&&
        ( MApp_TopStateMachine_GetTopState() != STATE_TOP_OSDPAGE)&&
         ( MApp_TopStateMachine_GetTopState() != STATE_TOP_TTX ) &&
         ( MApp_TopStateMachine_GetTopState() != STATE_TOP_DIGITALINPUTS)
         #if(ENABLE_SUBTITLE)
         && ( MApp_TopStateMachine_GetTopState() != STATE_TOP_SUBTITLE)
         #endif
         #if (ENABLE_OAD)
         && (MApp_TopStateMachine_GetTopState() != STATE_TOP_OAD)
         #endif
         #if (ENABLE_CI)
         && (MApp_TopStateMachine_GetTopState() != STATE_TOP_MMI)
         #endif
       ) // ONLY change channel at IDLE state
    {
        //printf("\n MApp_TopStateMachine_GetTopState() = %bu \n",MApp_TopStateMachine_GetTopState());
        return FALSE;
    }


    bServiceType = msAPI_CM_GetCurrentServiceType();
    u16CurPosition = msAPI_CM_GetCurrentPosition( bServiceType );
    u8PhyNum = msAPI_CM_GetPhysicalChannelNumber( bServiceType, u16CurPosition );


#if MHEG5_ENABLE
    eCurrentUserServiceType=g_eCurrentUserServiceType;
    if(g_eCurrentUserServiceType == E_SERVICETYPE_RADIO)
        wCurrentUserServicePosition=g_wCurrentRadioUserServicePosition;
  #if NORDIG_FUNC //for Nordig Spec v2.0
    else if(g_eCurrentUserServiceType == E_SERVICETYPE_DATA)
        wCurrentUserServicePosition=g_wCurrentDataUserServicePosition;
  #endif
    else
        wCurrentUserServicePosition=g_wCurrentTVUserServicePosition;


    if ( g_PIDfromMHEG5 )
    {
        if (g_u16MHEG5_VideoPID == g_u16Current_VideoPID )
        {
            msAPI_Scaler_SetScreenMute( E_SCREEN_MUTE_MHEG5, DISABLE, 0 , MAIN_WINDOW);
        }

        if (g_u16MHEG5_VideoPID == g_u16Current_VideoPID && ( g_u16MHEG5_AudioPID & ~0xE000 ) == g_u16Current_AudioPID )
        {

            g_MHEG5Video.u8VideoFlag &= ~(EVER_SET_VIDEO_STREAM|EVER_SET_VIDEO_BOX_SIZE);

            msAPI_MHEG5_VID_Send_CHANGESTREAM();
            return FALSE;
        }
    }


    // if only the video pid is the same as before, do change audio pid only.
    if ( g_PIDfromMHEG5 && g_u16MHEG5_VideoPID == g_u16Current_VideoPID && ( ( g_u16MHEG5_AudioPID & ~0xE000 ) != g_u16Current_AudioPID ) )
    {
        AUDIOSTREAM_TYPE wAudType = E_AUDIOSTREAM_INVALID;

        g_MHEG5Video.u8VideoFlag &= ~(EVER_SET_VIDEO_STREAM|EVER_SET_VIDEO_BOX_SIZE);
        if ( INVALID_PID != g_u16MHEG5_AudioPID )
        {
            if((g_u16MHEG5_AudioPID&0xE000) == 0x8000)
            {
                wAudType=E_AUDIOSTREAM_AC3;
            }
            else if((g_u16MHEG5_AudioPID&0xE000) == 0x2000)
            {
                wAudType=E_AUDIOSTREAM_MPEG4;
            }
            else if((g_u16MHEG5_AudioPID&0xE000) == 0x4000)
            {
                wAudType=E_AUDIOSTREAM_AAC;
            }
            else if((g_u16MHEG5_AudioPID&0xE000) == 0x6000)
            {
                wAudType=E_AUDIOSTREAM_AC3P;
            }
            else
            {
                wAudType=E_AUDIOSTREAM_MPEG;
            }
            msAPI_MHEG_AUD_ChangeAudPid( g_u16MHEG5_AudioPID & ~0xE000, wAudType );
        }
        else
        {
            msAPI_MHEG_AUD_Stop();
        }
        g_u16Current_AudioPID = g_u16MHEG5_AudioPID & ~0xE000;
        g_u16Current_AudioType = wAudType;
        msAPI_MHEG5_VID_Send_CHANGESTREAM();
        return FALSE;
    }

    if ( g_PIDfromMHEG5 && g_u16MHEG5_VideoPID != INVALID_PID)
    {
      #if (MHEG5_NDT_UNINTERRUPT_AV)
        if (msAPI_MHEG5_GetNDTChannelChange()==false)
      #endif
        {
            msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, ENABLE, 300, MAIN_WINDOW);
        }
    }

    if ( g_PIDfromMHEG5 )
    {
        msAPI_Scaler_SetScreenMute( E_SCREEN_MUTE_MHEG5, DISABLE, 0 , MAIN_WINDOW);
    }

#endif // #if MHEG5_ENABLE


    // channel change - stop dsmcc in "DisableChannel"
    if( bType != TYPE_TUNE_STREAM_SER_ID && bType != TYPE_TUNE_STREAM_LCN
     #if MHEG5_ENABLE
      #if MHEG5_NDT   // ndt - do not stop dsmcc
        && bType != TYPE_CHANNEL_CHANGE_SER_ID_NDT
        && bType != TYPE_CHANNEL_CHANGE_SER_ID_QUIETLY_NDT
        && bType != TYPE_CHANNEL_CHANGE_LCN_NDT
        && bType != TYPE_CHANNEL_CHANGE_LCN_QUIETLY_NDT
      #endif
     #endif
        )
    {
        if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) )
            MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);

      #if (ENABLE_PIP)
        if((MApp_Get_PIPMode() != EN_PIP_MODE_OFF))
        {
            if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) )
                MApp_ChannelChange_DisableChannel(TRUE,SUB_WINDOW);
        }
      #endif
    }
    else    // otherwise - change stream only, no need to stop dsmcc in "DisableChannel"
    {
        if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) )
            MApp_ChannelChange_DisableChannel(FALSE,MAIN_WINDOW);

      #if (ENABLE_PIP)
        if((MApp_Get_PIPMode() != EN_PIP_MODE_OFF))
        {
            if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) )
                MApp_ChannelChange_DisableChannel(FALSE,SUB_WINDOW);
        }
      #endif
    }

    // lcn process
    if ( ( bType == TYPE_TUNE_STREAM_LCN )
       ||( bType == TYPE_CHANNEL_CHANGE_LCN )
       ||( bType == TYPE_CHANNEL_CHANGE_LCN_QUIETLY )
     #if MHEG5_ENABLE
      #if MHEG5_NDT
        || (bType == TYPE_CHANNEL_CHANGE_LCN_QUIETLY_NDT) || (bType == TYPE_CHANNEL_CHANGE_LCN_NDT)
      #endif
     #endif
        )
    {
        //printf("\n  LCN LCN LCN \n");

        U16LoopEnd = msAPI_CM_CountProgram( E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO);

        for ( u16Loop = 0; u16Loop < U16LoopEnd; u16Loop++ )
        {
            u16LCN = msAPI_CM_GetLogicalChannelNumber( E_SERVICETYPE_DTV, u16Loop );
            if ( u16InputValue == u16LCN )
            {
                eGotServiceType = E_SERVICETYPE_DTV;
                u16GotPosition = u16Loop;
                bResult = TRUE;
                break;
            }
        }

        if ( u16Loop >= U16LoopEnd )
        {
            U16LoopEnd = msAPI_CM_CountProgram( E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO);
            for ( u16Loop = 0; u16Loop < U16LoopEnd; u16Loop++ )
            {
                u16LCN = msAPI_CM_GetLogicalChannelNumber( E_SERVICETYPE_RADIO, u16Loop );
                if ( u16InputValue == u16LCN )
                {
                    eGotServiceType = E_SERVICETYPE_RADIO;
                    u16GotPosition = u16Loop;
                    bResult = TRUE;
                    break;
                }
            }
#if NORDIG_FUNC //for Nordig Spec v2.0
            if ( u16Loop >= U16LoopEnd )
            {
                U16LoopEnd = msAPI_CM_CountProgram( E_SERVICETYPE_DATA, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO);
                for ( u16Loop = 0; u16Loop < U16LoopEnd; u16Loop++ )
                {
                    u16LCN = msAPI_CM_GetLogicalChannelNumber( E_SERVICETYPE_DATA, u16Loop );
                    if ( u16InputValue == u16LCN )
                    {
                        eGotServiceType = E_SERVICETYPE_DATA;
                        u16GotPosition = u16Loop;
                        bResult = TRUE;
                        break;
                    }
                }
            }
#endif
        }
    }
    else    // service process
    {
        bResult = msAPI_CM_GetServiceTypeAndPositionWithIDs( wTransportStream_ID, wOriginalNetwork_ID, u16InputValue, 1,&eGotServiceType, &u16GotPosition, bCheckTsID );
    }

    if ( bResult )
    {
        if(bShowDisplayInfo)
        {
            msAPI_CM_SetCurrentServiceType( eGotServiceType );
            msAPI_CM_SetCurrentPosition( eGotServiceType, u16GotPosition);
        }
        else
        {
            MApp_ChannelChange_SetVideoAndAudioPid(eGotServiceType, u16GotPosition);
            return TRUE;
        }
    }
    else
    {
        U16LoopEnd = msAPI_CM_CountProgram( E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO);

        for ( u16Loop = 0; u16Loop < U16LoopEnd; u16Loop++ )
        {
            if ( u8PhyNum == msAPI_CM_GetPhysicalChannelNumber( E_SERVICETYPE_DTV, u16Loop ) )
            {
                break;
            }
        }

        if( u16Loop >= U16LoopEnd )
        {
            printf("\nWarning: No channel!\n");
            return FALSE;
        }

        msAPI_CM_SetCurrentServiceType( E_SERVICETYPE_DTV );
        msAPI_CM_SetCurrentPosition( E_SERVICETYPE_DTV, u16Loop);
    }


#if (MHEG5_ENABLE)//for change AV(different channel) in MHEG5
    if (g_PIDfromMHEG5)
    {
        MEMBER_SERVICETYPE eTmpServiceTyp;
        U16 u16TmpPosition;
        eTmpServiceTyp = msAPI_CM_GetCurrentServiceType();
        u16TmpPosition = msAPI_CM_GetCurrentPosition( eTmpServiceTyp );
        if(u16CurPosition != u16TmpPosition)
        {
            bStopMonitorBlock=FALSE;
        }
    }
#endif

  #if (ENABLE_PIP)
    if((MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
        && (IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) || IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))))
    {
        MApp_ChannelChange_EnableChannel(SUB_WINDOW);
    }
    else
  #endif
    {
        MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
    }

    if ( bType == TYPE_TUNE_STREAM_SER_ID || bType == TYPE_TUNE_STREAM_LCN )//current service should not be updated
    {
        msAPI_CM_SetCurrentServiceType( bServiceType );
        msAPI_CM_SetCurrentPosition( bServiceType, u16CurPosition);
    }
    //printf("HK: %s:%d bServiceType:%x, u16CurPosition:%d, u8PhyNum:%d\n",__FUNCTION__,__LINE__,msAPI_CM_GetCurrentServiceType(),msAPI_CM_GetCurrentPosition( bServiceType ),msAPI_CM_GetPhysicalChannelNumber( bServiceType, u16CurPosition ));

#if MHEG5_ENABLE
    if(bType == TYPE_CHANNEL_CHANGE_SER_ID_QUIETLY || bType == TYPE_CHANNEL_CHANGE_LCN_QUIETLY
        || bType == TYPE_TUNE_STREAM_SER_ID || bType == TYPE_TUNE_STREAM_LCN || bType == TYPE_CHANNEL_CHANGE_LCN_NDT
      #if MHEG5_NDT
        || bType == TYPE_CHANNEL_CHANGE_SER_ID_QUIETLY_NDT || bType == TYPE_CHANNEL_CHANGE_LCN_QUIETLY_NDT
      #endif
        )
    {
        g_eCurrentUserServiceType=eCurrentUserServiceType;
        if(eCurrentUserServiceType == E_SERVICETYPE_RADIO)
            g_wCurrentRadioUserServicePosition=wCurrentUserServicePosition;
    #if NORDIG_FUNC //for Nordig Spec v2.0
        else if(eCurrentUserServiceType == E_SERVICETYPE_DATA)
            g_wCurrentDataUserServicePosition=wCurrentUserServicePosition;
        #endif
        else
            g_wCurrentTVUserServicePosition=wCurrentUserServicePosition;
    }
#endif

    // any ndt - do not show UI banner
    if (TRUE == bShowDisplayInfo)
    {
    if ( ( bType == TYPE_CHANNEL_CHANGE_SER_ID ) || ( bType == TYPE_CHANNEL_CHANGE_LCN ) )
    {
        //        printf("\n  TYPE_CHANNEL_CHANGE  Position= %u \n",u16Loop);
        enChannelChangeRetVal =EXIT_CLOSE;
        enChannelChangeState = STATE_CHANNELCHANGE_INIT;    // show UI of channel change
        g_bRealTimeMonitorOnly = FALSE;
        MApp_TopStateMachine_SetTopState( STATE_TOP_CHANNELCHANGE );
    }
    }
    return TRUE;
}

#endif // #if ENABLE_DTV

//
//******************************************************************************
//

#if MHEG5_ENABLE

EN_RET MApp_ChannelChange_GoBackDataMode(void)
{
    if(g_u16Current_VideoPID != INVALID_PID)
    {
        _bBackDataProgram=TRUE;
        MApp_ChannelChange_DisableChannel(FALSE, MAIN_WINDOW);
        MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
        _bBackDataProgram=FALSE;
        return (EN_RET)TRUE;
    }
    return (EN_RET)FALSE;
}

void MApp_ChannelPosition_Restore(void)
{
    #if(ENABLE_S2)
    if(IsDTVInUse() || IsS2InUse())
    #else
    if (IsDTVInUse())
    #endif
    {
        if(g_eCurrentUserServiceType == E_SERVICETYPE_INVALID)
        {
            g_eCurrentRealServiceType=g_eCurrentUserServiceType = msAPI_CM_GetCurrentServiceType();
            g_wCurrentTVRealServicePosition=g_wCurrentTVUserServicePosition = msAPI_CM_GetCurrentPosition(E_SERVICETYPE_DTV);
            g_wCurrentRadioRealServicePosition=g_wCurrentRadioUserServicePosition = msAPI_CM_GetCurrentPosition(E_SERVICETYPE_RADIO);
            #if NORDIG_FUNC //for Nordig Spec v2.0
            g_wCurrentDataRealServicePosition=g_wCurrentDataUserServicePosition = msAPI_CM_GetCurrentPosition(E_SERVICETYPE_DATA);
            #endif
        }
        else if(g_eCurrentUserServiceType != g_eCurrentRealServiceType || g_wCurrentTVUserServicePosition != g_wCurrentTVRealServicePosition
       #if NORDIG_FUNC //for Nordig Spec v2.0
           || g_wCurrentDataUserServicePosition != g_wCurrentDataRealServicePosition
       #endif
             || g_wCurrentRadioUserServicePosition != g_wCurrentRadioRealServicePosition)
        {
            #if NORDIG_FUNC //for Nordig Spec v2.0
        if(g_eCurrentUserServiceType == E_SERVICETYPE_RADIO)
                msAPI_CM_SetCurrentPosition(E_SERVICETYPE_DATA,g_wCurrentDataUserServicePosition);
            else if(g_eCurrentUserServiceType == E_SERVICETYPE_DATA)
                msAPI_CM_SetCurrentPosition(E_SERVICETYPE_DTV,g_wCurrentTVUserServicePosition);
        else
                msAPI_CM_SetCurrentPosition(E_SERVICETYPE_RADIO,g_wCurrentRadioUserServicePosition);
            #else
            if(g_eCurrentUserServiceType == E_SERVICETYPE_RADIO)
                msAPI_CM_SetCurrentPosition(E_SERVICETYPE_DTV,g_wCurrentTVUserServicePosition);
            else
                msAPI_CM_SetCurrentPosition(E_SERVICETYPE_RADIO,g_wCurrentRadioUserServicePosition);
            #endif
            msAPI_CM_SetCurrentServiceType(g_eCurrentUserServiceType);
            if(g_eCurrentUserServiceType == E_SERVICETYPE_RADIO)
                msAPI_CM_SetCurrentPosition(g_eCurrentUserServiceType,g_wCurrentRadioUserServicePosition);
            #if NORDIG_FUNC //for Nordig Spec v2.0
            else if(g_eCurrentUserServiceType == E_SERVICETYPE_DATA)
                msAPI_CM_SetCurrentPosition(g_eCurrentUserServiceType,g_wCurrentDataUserServicePosition);
            #endif
            else
                msAPI_CM_SetCurrentPosition(g_eCurrentUserServiceType,g_wCurrentTVUserServicePosition);
            MApp_SI_Disable_Auto_Update(TRUE);
        }

    }
}

#endif // #if MHEG5_ENABLE

//
//******************************************************************************
//

#if (ENABLE_DVB_TAIWAN_APP)

void MApp_ATV_ChangeAntennaType(EN_ANT_TYPE enAntennaType)
{
    if(enAntennaType==msAPI_ATV_GetCurrentAntenna() || !IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
    {
        return;
    }
    else
    {
        // 1. Disable channel
        MApp_ChannelChange_DisableChannel(FALSE, MAIN_WINDOW);
        if(g_bIsImageFrozen)
        {
            g_bIsImageFrozen = FALSE;
            MApi_XC_FreezeImg(g_bIsImageFrozen, MAIN_WINDOW);
        }

        // 2. Save last watched channel for current antenna type
        msAPI_ATV_SetCurrentProgramNumber(msAPI_ATV_GetCurrentProgramNumber());

        // 3. Switch antenna type
        stGenSetting.stScanMenuSetting.u8Antenna = enAntennaType;
        msAPI_ATV_SetCurrentAntenna(enAntennaType);

        // 4. Load current channel for new antenna type, reset prev. channel
        msAPI_ATV_SetCurrentProgramNumber(msAPI_ATV_LoadCurrentProgramNumber());
        dmSetLastWatchedOrdinal();

        // Reference to channel up/down
        msAPI_AVD_TurnOffAutoAV();
        msAPI_Tuner_ChangeProgram();
        msAPI_AVD_ClearAspectRatio();
        MApp_CheckBlockProgramme();

        // 5. Enable channel
        MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
    }
}

#endif // #if (ENABLE_DVB_TAIWAN_APP)

//
//******************************************************************************
//

#define DEBUG_CC_VD_FORCEMODE(x)    //x

void MApp_ChannelChange_SetupVdForceMode(void)
{
    U8 u8ForceVDMode;
    AVD_VideoStandardType eCurChVdStd;
    AVD_VideoStandardType eUserChVdStd;

  #if (ENABLE_ATSC)
    if ( IsAtscInUse() )
    {
        eCurChVdStd  = E_VIDEOSTANDARD_NTSC_M;
        eUserChVdStd = E_VIDEOSTANDARD_NTSC_M;
    }
    else
  #endif
    {
        U8 u8CurrentProgramNumber = msAPI_ATV_GetCurrentProgramNumber();
        eCurChVdStd  = msAPI_ATV_GetVideoStandardOfProgram(u8CurrentProgramNumber);
        eUserChVdStd = msAPI_ATV_GetUserVideoStandardOfProgram(u8CurrentProgramNumber);
    }

    DEBUG_CC_VD_FORCEMODE(printf("eCurChVdStd=%u, eUserChVdStd=%u\n", eCurChVdStd, eUserChVdStd););

    //printf(">> %s eCurChVdStd:%u eUserChVdStd:%u\n", __FUNCTION__, eCurChVdStd, eUserChVdStd);

    if (eUserChVdStd == E_VIDEOSTANDARD_AUTO)
    {
      #if(ENABLE_ATV_CHANGE_CHANNEL_USE_VD_FORCE_MODE)
        u8ForceVDMode = E_FORCE_VD_MODE_ON_FOR_A_WHILE;
      #else
        u8ForceVDMode = E_FORCE_VD_MODE_OFF;
      #endif
    }
    else
    {
        u8ForceVDMode = E_FORCE_VD_MODE_ON_FOREVER;
        eCurChVdStd = eUserChVdStd;
    }

    if( IsATVInUse()
      &&(u8ForceVDMode != E_FORCE_VD_MODE_OFF)
      &&(eCurChVdStd != E_VIDEOSTANDARD_AUTO)
      &&(eCurChVdStd != E_VIDEOSTANDARD_NOTSTANDARD)
      )
    {
        //printf("\n>>>>EnableForceMode\n");
        msAPI_AVD_ForceVideoStandard(eCurChVdStd);

        //msAPI_AVD_SetVideoStandard(eCurChVdStd);

        //printf("#### eCurChVdStd =%d ####\n",eCurChVdStd);
        if( u8ForceVDMode == E_FORCE_VD_MODE_ON_FOR_A_WHILE )
        {
            msAPI_AVD_Set_ForceVideoStd_CountDownTime(1000);
        }
    }
    else
    {
        //printf("\n>>>>DisableForceMode0\n");
        msAPI_AVD_StartAutoStandardDetection();

        // Why use this function
        //msAPI_AVD_DetectVideoStandard(OPERATIONMETHOD_MANUALLY);

        /*if( (eCurChVdStd != E_VIDEOSTANDARD_AUTO)
          &&(eCurChVdStd != E_VIDEOSTANDARD_NOTSTANDARD)
          )
        {
            msAPI_AVD_SetVideoStandard(eCurChVdStd);
        }*/
    }
}



//------------------------------------------------------------------------------

#undef  MAPP_CHANNEL_CHANGE_C

