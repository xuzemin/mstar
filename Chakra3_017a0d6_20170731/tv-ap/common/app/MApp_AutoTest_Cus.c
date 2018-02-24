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

#include "Board.h"

#if( CHAKRA3_AUTO_TEST )

#if 0//def ATSC_SYSTEM
    #define CHAKRA2_ATSC    1
#else
    #define CHAKRA2_ATSC    0
#endif

//#define MAPP_AUTOTEST_C
#include "MApp_AutoTest.h"

#include "drvUSB.h"
#include "msAPI_Global.h"
#include "msAPI_Tuning.h"
#include "msAPI_FreqTableATV.h"

#include "msAPI_ATVSystem.h"
#if( ENABLE_DTV )
#include "msAPI_DTVSystem.h"
#include "MApp_SignalMonitor.h"
#endif

#include "MApp_TopStateMachine.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_USBDownload.h"
#include "MApp_Menu_Main.h"

#include "ZUI_exefunc.h"

#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIwindow.h"

#if( CHAKRA2_ATSC )
#include "MApp_ZUI_APItables.h"
#include "MApp_UiMenuFunc.h"
#include "OSDTbl_h.inl"
#include "mapp_closedcaption.h"
#include "MApp_UiMenu.h"
#endif

#include "MApp_ZUI_ACTmainpage.h"

#include "MApp_UiMenuDef.h"
#include "MApp_DataBase.h"
#include "MApp_ChannelChange.h"
#if (ENABLE_ATSC)
#include "MApp_ChannelProc_ATSC.h"
#include "MApp_MVDMode.h"
#endif



#if( CHAKRA2_ATSC )
extern BOOLEAN MApp_UiMenuFunc_InputSourceSwitch(E_UI_INPUT_SOURCE SelectUIInputSource);
extern void MApp_ZUI_ACT_ForceUpdate_SoftWareUpgradeStatus(U8 percent);
extern void MApp_ChannelChange_DisableChannel(void);
#else

extern EN_OSD_TUNE_TYPE_SETTING eTuneType;
extern COMMON_DLG_MODE _eCommonDlgMode;
extern EN_MENU_STATE enMainMenuState;

extern EN_OSD_COUNTRY_SETTING MApp_ZUI_ACT_GetTuningCountry(void);
extern void MApp_ZUI_ACT_SetTuningCountry(EN_OSD_COUNTRY_SETTING TuningCountry);
extern BOOLEAN MApp_ZUI_ACT_ExecuteMainMenuAction(U16 act);
extern BOOLEAN MApp_ZUI_ACT_ExecuteMenuCommonDialogAction(U16 act);
extern void MApp_ZUI_ACT_InputSourceSwitch( E_UI_INPUT_SOURCE source_type );
extern void MApp_ZUI_SwUpdate_ProgressBar(U8 percent);
extern void MApp_ChannelChange_DisableChannel (BOOLEAN u8IfStopDsmcc, SCALER_WIN eWindow /*U8 u8ChanBufIdx*/ ); //for change channel
extern void MApp_SetOSDCountrySetting(EN_OSD_COUNTRY_SETTING eOSDCountrySetting, BOOLEAN bSave);
#endif

extern E_UI_INPUT_SOURCE MApp_InputSource_GetUIInputSourceType(INPUT_SOURCE_TYPE_t stInputSrc);
extern BOOLEAN MApp_IsSrcHasSignal(SCALER_WIN eWindow);
extern void MDrv_Sys_WholeChipReset( void );
extern U32 msAPI_Timer_DiffTimeFromNow(U32 u32TaskTimer);


//======================================================================================


#define DEBUG_AUTOTEST_CUS(x)   //x

#define DEBUG_AT_SET_SRC(x)     //x

//======================================================================================

BOOL MApp_AT_Cmd_SetInputSource(EN_AT_INPUT_SOURCE_TYPE enAutoTestInputSrc)
{
    DEBUG_AT_SET_SRC( printf("enAutoTestInputSrc=%d\n", enAutoTestInputSrc) );

    if( enAutoTestInputSrc >= INPUT_SOURCE_NUM )
    {
        printf("enAutoTestInputSrc=%d, INPUT_SOURCE_NUM=%d\n", enAutoTestInputSrc, INPUT_SOURCE_NUM);
        return FALSE;
    }

    E_UI_INPUT_SOURCE eTargetUIInputSource = MApp_InputSource_GetUIInputSourceType( (INPUT_SOURCE_TYPE_t)enAutoTestInputSrc );
    DEBUG_AT_SET_SRC( printf("eTargetUIInputSource=%d\n",eTargetUIInputSource) );

    if( (eTargetUIInputSource >= UI_INPUT_SOURCE_NUM)
      ||(eTargetUIInputSource == UI_INPUT_SOURCE_NONE))
    {
        printf("eTargetUIInputSource=%d, UI_INPUT_SOURCE_NUM=%d\n", eTargetUIInputSource, UI_INPUT_SOURCE_NUM);
        return FALSE;
    }

#if 0//( CHAKRA2_ATSC )

    if( (eTargetUIInputSource == UI_INPUT_SOURCE_TV) )
        eTargetUIInputSource = UI_INPUT_SOURCE_DTV;

    MApp_ZUI_ACT_ShutdownOSD();

    MApp_UiMenuFunc_InputSourceSwitch(eTargetUIInputSource);

    MApp_TopStateMachine_SetTopState(STATE_TOP_INPUTSOURCE);
    enInputSourceState = STATE_INPUTSOURCE_CLEAN_UP;

#else


  #if(ENABLE_ATSC)// Patch ATSC: Because ATSC has only TV source, no seperate DTV/ATV
    if( (enAutoTestInputSrc==EN_AT_INPUT_SOURCE_ATV)||(enAutoTestInputSrc==EN_AT_INPUT_SOURCE_DTV) )
    {
        //U16 u16CurListProgIdx = MApp_ChanProc_GetCurProgIndex();
        //printf("u16CurListProgIdx=%u\n", u16CurListProgIdx ); );

        U16 u16MainListProgIdx = MApp_ChanProc_GetCurMainListProgIndex();
        DEBUG_AT_SET_SRC( printf("u16MainListProgIdx=%u\n", u16MainListProgIdx ); );

        if( u16MainListProgIdx != INVALID_SERVICE_IDX )
        {
        #if 0
            U16 u16VirChIdx = VIR_CH_IDX(u16MainListProgIdx);
            printf(" u16VirChIdx=%u\n", u16VirChIdx );

            MS_VIRTUAL_CHANNEL stVirCh_Tmp;
            MApp_ChanProc_GetSingleChannel( (&stVirCh_Tmp) , u16VirChIdx);

            MApp_ChanProc_Is_ChannelAtv();
        #endif

            if( MApp_ChanProc_Is_CurChannelAtv() )
            {
                // Current channel is ATV
                if( enAutoTestInputSrc==EN_AT_INPUT_SOURCE_DTV ) // If Auto test want to change source to DTV
                {
                    printf("Cur Ch is ATV, but AT want src to DTV!\n");

                    // Set prog index to first DTV
                    if( FALSE == MApp_ChanProc_ResetProgIdx_ToFirstAtvDtv(FALSE) )
                    {
                        printf("\nNo DTV ch exist!\n");
                    }
                }
            }
            else
            {
                // Current channel is DTV
                if( enAutoTestInputSrc==EN_AT_INPUT_SOURCE_ATV ) // If Auto test want to change source to ATV
                {
                    printf("Cur Ch is DTV, but AT want src to ATV!\n");

                    // Set prog index to first ATV
                    if( FALSE == MApp_ChanProc_ResetProgIdx_ToFirstAtvDtv(TRUE) )
                    {
                        printf("\nNo ATV ch exist!\n");
                    }
                }
            }
        }
    }
  #endif

    MApp_ZUI_ACT_InputSourceSwitch(eTargetUIInputSource);

    MApp_TopStateMachine_SetTopState(STATE_TOP_ANALOG_SHOW_BANNER);
#endif

    return TRUE;
}

BOOL MApp_AT_IsSrcHasSignal(SCALER_WIN eWin)
{
#if(ENABLE_ATSC)
    if( IsAtscInUse() )
    {
        if( (MApp_GetSignalLockStatus() == FE_LOCK)
          &&(MApp_VID_Is_VdecStatusGood())
          )
        {
            return TRUE;
        }
        else
        {
        #if(ENABLE_AT_DEBUG_INPUT_SIGNAL)
            if( g_AT_bDebugInputSignal )
            {
                printf("MApp_GetSignalLockStatus()=%u\n", MApp_GetSignalLockStatus() );
                printf("MApp_VID_Is_VdecStatusGood()=%u\n", MApp_VID_Is_VdecStatusGood() );
            }
        #endif

            return FALSE;
        }
    }
    else
#endif
#if(ENABLE_DVB)
    if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(eWin)) )
    {
        EN_SIGNAL_LOCK_STATUS eSIGNAL_LOCK_STATUS = MApp_GetSignalStatus();

        if( eSIGNAL_LOCK_STATUS != SIGNAL_LOCK )
        {
        #if(ENABLE_AT_DEBUG_INPUT_SIGNAL)
            printf("eSIGNAL_LOCK_STATUS=%u\n", eSIGNAL_LOCK_STATUS);
        #endif
            return FALSE;
        }
        else
        {
            return TRUE;
        }
    }
    else
#endif
    {
        return MApp_IsSrcHasSignal(eWin);
    }
}

BOOL MApp_AT_Cmd_GetInputSignal(void)
{
#if(ENABLE_AT_DEBUG_INPUT_SIGNAL)
    g_AT_bDebugInputSignal = 1;
#endif

    BOOLEAN bHasSignalMain = MApp_AT_IsSrcHasSignal(MAIN_WINDOW);
    BOOLEAN bHasSignal = bHasSignalMain;

#if (ENABLE_PIP)
    if(IsPIPSupported())
    {
        BOOLEAN bHasSignalSub = MApp_AT_IsSrcHasSignal(SUB_WINDOW);
        bHasSignal = bHasSignalMain || bHasSignalSub;
    }
#endif

#if(ENABLE_AT_DEBUG_INPUT_SIGNAL)
    g_AT_bDebugInputSignal = 0;
#endif

    return bHasSignal;
}

#if(ENABLE_DTV)
#if(ENABLE_ATSC)
void MApp_ZUI_ACT_ExecAtscAutoScan(void);
#endif
BOOL MApp_AT_Cmd_DtvAutoScan(EN_AT_MEMBER_COUNTRY enCountry)
{
    EN_OSD_COUNTRY_SETTING enOsdCountry = (EN_OSD_COUNTRY_SETTING)enCountry;
    printf("enOsdCountry=%d\n", enOsdCountry);

    //printf("MApp_TopStateMachine_GetTopState()=%d\n", MApp_TopStateMachine_GetTopState());
    if( MApp_TopStateMachine_GetTopState() != STATE_TOP_DIGITALINPUTS )
    {
        return FALSE;
    }


    eTuneType = OSD_TUNE_TYPE_DTV_ONLY;

#if( ENABLE_ATSC )
    if( IsAtscInUse()||IsATVInUse() )
    {
        MApp_ZUI_ACT_ShutdownOSD();
        MApp_ZUI_ACT_StartupOSD(1/*E_OSD_MAIN_MENU*/);
        MApp_ZUI_ACT_ExecAtscAutoScan();
    }
    else
#endif
    {
        MApp_ZUI_ACT_SetTuningCountry(enOsdCountry);
        MApp_SetOSDCountrySetting( MApp_ZUI_ACT_GetTuningCountry(), TRUE);

        MApp_ZUI_ACT_ExecuteMainMenuAction(EN_EXE_GOTO_AUTO_TUNING);
    }

    enMainMenuState = STATE_MENU_GOTO_SCAN;
    MApp_TopStateMachine_SetTopState(STATE_TOP_MENU);

    PRINT_AUTOTEST_CHECKPT_TIME("dtv auto tuning UI");

    return TRUE;
}

BOOL MApp_AT_Cmd_DtvManualScan(U16 u16ChannelNumber)
{
    u16ChannelNumber=u16ChannelNumber;

#if( CHAKRA2_ATSC )
    if( MApp_TopStateMachine_GetTopState() != STATE_TOP_TV )
    {
        return FALSE;
    }
#else
    if( MApp_TopStateMachine_GetTopState() != STATE_TOP_DIGITALINPUTS )
    {
        return FALSE;
    }

    MApp_ZUI_ACT_ExecuteMainMenuAction(EN_EXE_GOTO_DTV_TUNING);
    enMainMenuState = STATE_MENU_GOTO_DTV_MANUALTUNING;
    MApp_TopStateMachine_SetTopState(STATE_TOP_MENU);
#endif

    return TRUE;
}

BOOL MApp_AT_Cmd_GetDtvChannelList(void)
{
#if( CHAKRA2_ATSC )
    U16 u16TotalServiceNum = MApp_ChanProc_GetNumOfServices(MAIN_LIST);
    printf("u16TotalServiceNum=%u\n", u16TotalServiceNum);

    return FALSE;
#else
    //MS_U16 u16DTVChannelCnt = msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_ALL);
    //MS_U16 u16RADIOChannelCnt = msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_ALL);
    //MS_U16 u16DATAChannelCnt = msAPI_CM_CountProgram(E_SERVICETYPE_DATA, E_PROGACESS_INCLUDE_ALL);
    MS_U16 u16DTVChannelCnt = msAPI_DTV_GetProgramCount(E_SERVICETYPE_DTV, INCLUDE_ALL);
    MS_U16 u16RADIOChannelCnt = msAPI_DTV_GetProgramCount(E_SERVICETYPE_RADIO, INCLUDE_ALL);
    MS_U16 u16DATAChannelCnt = msAPI_DTV_GetProgramCount(E_SERVICETYPE_DATA, INCLUDE_ALL);

    if( u16DTVChannelCnt!=0 || u16RADIOChannelCnt!=0 || u16DATAChannelCnt!=0 )
    {
        U8 au8ChannelNameBuf[MAX_SERVICE_NAME]={0};

        MS_U16 u16DTVChannelIdx = 0;

        for(u16DTVChannelIdx=0; u16DTVChannelIdx<u16DTVChannelCnt; ++u16DTVChannelIdx)
        {
            msAPI_CM_GetServiceName(E_SERVICETYPE_DTV, u16DTVChannelIdx, au8ChannelNameBuf);
            MApp_AT_Msg_Add__AndAppendNewLine( au8ChannelNameBuf );
        }

        MS_U16 u16RADIOChannelIdx = 0;

        for(u16RADIOChannelIdx=0; u16RADIOChannelIdx<u16RADIOChannelCnt; ++u16RADIOChannelIdx)
        {
            msAPI_CM_GetServiceName(E_SERVICETYPE_RADIO,u16RADIOChannelIdx, au8ChannelNameBuf);
            MApp_AT_Msg_Add__AndAppendNewLine( au8ChannelNameBuf );
        }

        MS_U16 u16DATAChannelIdx = 0;

        for(u16DATAChannelIdx=0; u16DATAChannelIdx<u16DATAChannelCnt; ++u16DATAChannelIdx)
        {
            msAPI_CM_GetServiceName(E_SERVICETYPE_DATA,u16DATAChannelIdx, au8ChannelNameBuf);
            MApp_AT_Msg_Add__AndAppendNewLine( au8ChannelNameBuf );
        }

        return TRUE;
    }

    return FALSE;
#endif
}

BOOL MApp_AT_Cmd_GetDtvSignal(void)
{
#if( ENABLE_ATSC)
    U8 u8Loop;
    MS_RF_CHANNEL_new stRf_Ch;
    MS_VIRTUAL_CHANNEL *ptmpstVirtualCh = NULL;

    for(u8Loop = 0; u8Loop <stChSetting.u16MainListSrvNum; u8Loop++)
    {
        ptmpstVirtualCh = MApp_ChanProc_GetChannelPointer(VIR_CH_IDX(u8Loop ));

        MApp_ChanProc_GetRfChannelPointer(ptmpstVirtualCh, &stRf_Ch);

        if( stRf_Ch.stTPSetting.fModulation != DEMOD_ATSC_MODE_NTSC )
        {
            MApp_ChannelChange_DisableChannel(TRUE, MAIN_WINDOW);
            MApp_ChanProc_SetMainListProgIndex(u8Loop);
            MApp_ChanProc_RefreshChannelBuffer(MAIN_LIST);
            MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
            MApp_SetChChangeState(TRUE);
            return TRUE;
        }
    }

    printf("---none DTV channel.\n");
    return FALSE;
#else
    //MS_U16 u16DTVChannelCnt = msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_ALL);
    //MS_U16 u16RADIOChannelCnt = msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_ALL);
    //MS_U16 u16DATAChannelCnt = msAPI_CM_CountProgram(E_SERVICETYPE_DATA, E_PROGACESS_INCLUDE_ALL);
    MS_U16 u16DTVChannelCnt = msAPI_DTV_GetProgramCount(E_SERVICETYPE_DTV, INCLUDE_ALL);
    MS_U16 u16RADIOChannelCnt = msAPI_DTV_GetProgramCount(E_SERVICETYPE_RADIO, INCLUDE_ALL);
    MS_U16 u16DATAChannelCnt = msAPI_DTV_GetProgramCount(E_SERVICETYPE_DATA, INCLUDE_ALL);

    if( (u16DTVChannelCnt!=0 || u16RADIOChannelCnt!=0 || u16DATAChannelCnt!=0)
//      &&(UI_INPUT_SOURCE_TYPE==UI_INPUT_SOURCE_DTV)
      &&(IsDTVInUse())
      )
    {
        BYTE cRFChannelNumber;
        U8 buffer[16]={ASCII_NULL}, u8PhNum=0, name[MAX_SERVICE_NAME];
        WORD u16CurPosIdx = msAPI_CM_GetCurrentPosition(E_SERVICETYPE_DTV);
        DTVPROGRAMID_M stDPI;

        snprintf((char *)buffer, 9, "%d",u16DTVChannelCnt);
        MApp_AT_Msg_Add__AndAppendNewLine(buffer);

        snprintf((char *)buffer, 9, "%d",u16RADIOChannelCnt);
        MApp_AT_Msg_Add__AndAppendNewLine(buffer);

        snprintf((char *)buffer, 9, "%d",u16DATAChannelCnt);
        MApp_AT_Msg_Add__AndAppendNewLine(buffer);


        msAPI_CM_GetServiceName(E_SERVICETYPE_DTV, u16CurPosIdx, name);
        printf("DTV serviceNum=%u\n",  u16DTVChannelCnt);
        printf("[DTV channel change][%u] Zapping  start\n", gU32ATCkPtTime);
        printf("[DTV channel change][%u]: Unmute\n", g_AT_u32UnmuteVideo);

        cRFChannelNumber = msAPI_CM_GetPhysicalChannelNumber(E_SERVICETYPE_DTV, u16CurPosIdx);
        u8PhNum = msAPI_CM_Get_RFChannelIndex(cRFChannelNumber);
        msAPI_CM_GetIDTable(u8PhNum,(BYTE *)&stDPI,E_DATA_ID_TABLE);
        printf("<CI><Current Program Info><Name>[%u]:%s\n", (u16CurPosIdx+1), name);
        printf("<CI><Current Program Info><Frequency>[%u]:%u\n", (u16CurPosIdx+1), stDPI.u32Frequency);

        return TRUE;
    }

    return FALSE;
#endif
}
#endif

BOOL MApp_AT_Cmd_AtvAutoScan(EN_AT_MEMBER_COUNTRY enCountry)
{
    EN_OSD_COUNTRY_SETTING enOsdCountry = (EN_OSD_COUNTRY_SETTING)enCountry;
    printf("enOsdCountry=%d\n", enOsdCountry);

    if( MApp_TopStateMachine_GetTopState() != STATE_TOP_DIGITALINPUTS )
    {
        return FALSE;
    }

    eTuneType = OSD_TUNE_TYPE_ATV_ONLY;

#if( ENABLE_ATSC )
    if( IsAtscInUse()||IsATVInUse() )
    {
        MApp_ZUI_ACT_ShutdownOSD();
        MApp_ZUI_ACT_StartupOSD(1/*E_OSD_MAIN_MENU*/);
        MApp_ZUI_ACT_ExecAtscAutoScan();
    }
    else
#endif
    {
        MApp_ZUI_ACT_SetTuningCountry(enOsdCountry);
        MApp_SetOSDCountrySetting(MApp_ZUI_ACT_GetTuningCountry(), TRUE);

        MApp_ZUI_ACT_ExecuteMainMenuAction(EN_EXE_GOTO_AUTO_TUNING);
    }

    enMainMenuState = STATE_MENU_GOTO_SCAN;
    MApp_TopStateMachine_SetTopState(STATE_TOP_MENU);

    PRINT_AUTOTEST_CHECKPT_TIME("atv auto tuning UI");

    return TRUE;
}

BOOL MApp_AT_Cmd_AtvManualScan(U16 u16Freq)
{
    u16Freq = u16Freq;

#if( CHAKRA2_ATSC )

    if( MApp_TopStateMachine_GetTopState() != STATE_TOP_TV )
    {
        return FALSE;
    }

    return FALSE;
#else

    if( MApp_TopStateMachine_GetTopState() != STATE_TOP_DIGITALINPUTS )
    {
        return FALSE;
    }

    MApp_ZUI_ACT_ExecuteMainMenuAction(EN_EXE_GOTO_ATV_TUNING);
    enMainMenuState = STATE_MENU_GOTO_ATV_MANUALTUNING;
    MApp_TopStateMachine_SetTopState(STATE_TOP_MENU);

    return TRUE;
#endif
}

BOOL MApp_AT_Cmd_GetAtvChannelList(void)
{
#if( CHAKRA2_ATSC )

    return FALSE;
#else
    MS_U8 u8ATVChannelCnt = msAPI_ATV_GetActiveProgramCount();

    if( u8ATVChannelCnt == 0 )
        return FALSE;

    MS_U8 u8ATVChannelIdx = 0;
    U8 au8ATVChannelName[MAX_STATION_NAME]={0};
    for(u8ATVChannelIdx=0; u8ATVChannelIdx<u8ATVChannelCnt; ++u8ATVChannelIdx)
    {
        msAPI_ATV_GetStationName((BYTE)u8ATVChannelIdx, au8ATVChannelName);
        //printf("%s\n",GetATVChannelName);
        MApp_AT_Msg_Add__AndAppendNewLine(au8ATVChannelName);
    }

    return TRUE;
#endif
}

BOOL MApp_AT_Cmd_GetAtvSignal(void)
{
#if( CHAKRA2_ATSC )

    return FALSE;
#else
    MS_U8 u8ATVChannelCnt = msAPI_ATV_GetActiveProgramCount();

    if( (u8ATVChannelCnt!=0) && (UI_INPUT_SOURCE_TYPE==UI_INPUT_SOURCE_ATV) )
    {
        BYTE buffer[12]={ASCII_NULL}, u8CurProgNum = msAPI_ATV_GetCurrentProgramNumber();;
        U8 name[MAX_STATION_NAME];
        WORD wTunerPLL,wTunerPLLI,wTunerPLLF;

        snprintf((char *)buffer, 11, "%d", u8ATVChannelCnt);
        MApp_AT_Msg_Add__AndAppendNewLine(buffer);
        msAPI_ATV_GetStationName(u8CurProgNum, name);
        printf("ATV serviceNum=%u\n",  u8ATVChannelCnt);
        printf("[ATV channel change][%u] Zapping  start\n", gU32ATCkPtTime);
        printf("[ATV channel change][%u]: Unmute\n", g_AT_u32UnmuteVideo);
        printf("<CI><Current Program Info><Name>[%u]:%s\n", (u8CurProgNum+1), name);
        wTunerPLL = msAPI_Tuner_GetCurrentChannelPLL2UiStr();
        wTunerPLLI = msAPI_CFT_ConvertPLLtoIntegerOfFrequency(wTunerPLL);
        wTunerPLLF = msAPI_CFT_ConvertPLLtoFractionOfFrequency(wTunerPLL);
        printf("<CI><Current Program Info><Frequency>[%u]:%u.%u\n", (u8CurProgNum+1), wTunerPLLI, wTunerPLLF);
        return TRUE;
    }
    return FALSE;
#endif
}

BOOL MApp_AT_Cmd_GetVideoState(void)
{
#if( CHAKRA2_ATSC )

    return FALSE;
#else

    BOOL bResult = TRUE;
    char* pcReportStr = "NONE";

//    if( UI_INPUT_SOURCE_TYPE==UI_INPUT_SOURCE_DTV )
    if (IsDTVInUse())
    {
        DEBUG_AUTOTEST_CUS( printf("SYS_SCREEN_SAVER_TYPE=%d\n", SYS_SCREEN_SAVER_TYPE(MAIN_WINDOW)) );
        switch( SYS_SCREEN_SAVER_TYPE(MAIN_WINDOW) )
        {
            case EN_SCREENSAVER_NULL:
                pcReportStr = "COMMON_VIDEO";
                break;
            case EN_SCREENSAVER_NOT_RUNNING1:
            case EN_SCREENSAVER_NOT_RUNNING2:
                pcReportStr = "NOT_RUNNING";
                break;
            case EN_SCREENSAVER_SCRAMBLE: //note: please reference "MIA_SCRAMBLE_CHANNEL_MSG_BOX"
                pcReportStr = "NO_CI_MODULE";
                break;
            case EN_SCREENSAVER_SCRAMBLED_PROGRAM:
                pcReportStr = "NO_CI_MODULE";
                break;
            case EN_SCREENSAVER_LOCKED_PROGRAM:
                pcReportStr = "CH_BLOCK";
                break;
            case EN_SCREENSAVER_BLOCKRATING:
                pcReportStr = "PARENTAL_BLOCK";
                break;
            case EN_SCREENSAVER_AUDIOONLY:
                pcReportStr = "AUDIO_ONLY";
                break;
            case EN_SCREENSAVER_MHEGONLY:
                pcReportStr = "MHEG5_ONLY";
                break;
            case EN_SCREENSAVER_UNSUPPORT_MODE:
                pcReportStr = "INVALID_SERVICE";
                break;
            default:
            case EN_SCREENSAVER_NO_SHOW_PROGRAM:
            case EN_SCREENSAVER_NOSIGNAL:
                pcReportStr = "NO_SIGNAL";
                bResult = FALSE;
                break;
        }
    }
    else if(UI_INPUT_SOURCE_TYPE==UI_INPUT_SOURCE_ATV)
    {
        pcReportStr = "ATV mode";
    }
    else
    {
        pcReportStr = "OtherInputsource";
    }

    MApp_AT_Msg_Add__AndAppendNewLine((U8*)pcReportStr);

    return bResult;
#endif
}

BOOL MApp_AT_Cmd_FactoryReset(void)
{
#if( CHAKRA2_ATSC )

    return FALSE;
#else

    _eCommonDlgMode = EN_COMMON_DLG_MODE_FACTORY_RESET;
    MApp_ZUI_ACT_ExecuteMenuCommonDialogAction(EN_EXE_FACTORY_RESET);

    return TRUE;
#endif
}

BOOL MApp_AT_Cmd_ClearProgram(void)
{
#if( CHAKRA2_ATSC )

    MApp_ChannelChange_DisableChannel();

    return FALSE;

#else

    MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);

 #if ENABLE_DTV
    msAPI_CM_ResetAllProgram();
 #endif

    msAPI_ATV_ResetChannelData();

    return TRUE;

#endif
}

BOOL MApp_AT_Cmd_SwUpgrade_Init(void)
{
    U8 u8PortNo=0;

    u8PortNo = MApp_UsbDownloadCheckPort();

    if(u8PortNo== INVALID_USB_PORT)
        return FALSE;

#if( CHAKRA2_ATSC )
    MApp_UsbDownload_Init(u8PortNo, MApp_ZUI_ACT_ForceUpdate_SoftWareUpgradeStatus);
#else
    MApp_UsbDownload_Init(u8PortNo, MApp_ZUI_SwUpdate_ProgressBar);
#endif

    if( !MW_UsbDownload_Search() )
    {
            return FALSE;
    }

    return TRUE;
}

void MApp_AT_Cmd_SwUpgrade_Start(void)
{
    if (MW_UsbDownload_Start())
    {
        printf("Reboot~");
        //msAPI_BLoader_Reboot();
        MDrv_Sys_WholeChipReset();
    }
}

#endif

