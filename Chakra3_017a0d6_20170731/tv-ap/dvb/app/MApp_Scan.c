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

#define MAPP_SCAN_C

//------------------------------------------------------------------------------
//                    Header Files
//------------------------------------------------------------------------------
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include "apiXC.h"
#include "apiXC_Adc.h"

#include "debug.h"

#include "msAPI_Global.h"

#include "apiGOP.h"

#include "msAPI_Memory.h"
#include "msAPI_MIU.h"
#include "msAPI_Timer.h"
#include "msAPI_OSD.h"
#include "msAPI_Tuner.h"

#include "msAPI_IR.h"
#include "msAPI_Ram.h"
#include "msAPI_audio.h"
#include "msAPI_VD.h"
#include "msAPI_Tuning.h"
#include "msAPI_ChProc.h"
#include "msAPI_DrvInit.h"

#include "MApp_GlobalVar.h"
#include "MApp_Exit.h"
#include "MApp_Key.h"

#if (ENABLE_DTV)
#include "mapp_demux.h"
#include "mapp_si.h"
#include "mapp_si_util.h"
#if ENABLE_OAD
#include "MApp_OAD.h"
#endif
#endif

#include "MApp_DataBase.h"
#include "MApp_Scan.h"
#include "MApp_SignalMonitor.h"
#include "MApp_VDMode.h"
#include "MApp_ChannelChange.h"
#include "MApp_InputSource.h"
#include "MApp_TV.h"
#include "MApp_UiMenuDef.h"
#include "MApp_GlobalFunction.h"

#include "msAPI_Demod.h"

#if(ENABLE_S2)
#include "MApp_MenuChannel.h"
#include "apiDigiTuner.h"
#include "Utl.h"
#include "MApp_ZUI_Main.h"
#endif

#if (ENABLE_DTV_EPG)
#include "MApp_EpgTimer.h"
#include "mapp_eit.h"
#endif

#include "MApp_SaveData.h"
#include "MApp_PlayCard.h"
#include "ZUI_exefunc.h"
#include "MApp_ZUI_Main.h"
#include "ZUI_tables_h.inl"

#if ENABLE_DVBC
#include "MApp_CADTV_Proc.h"
#include "msAPI_FreqTableCADTV.h"
#include "MApp_IR.h"
#endif

#if (CHANNEL_SCAN_AUTO_TEST)
#include "drvUartDebug.h"
#include "MApp_Main.h"
extern ScanAutoTestData g_ScanAutoTestData;
extern MS_TP_SETTING stTpSettingPC;
#endif

#include "msAPI_DTVSystem.h"
#include "MApp_ATVProc.h"
#include "msAPI_ATVSystem.h"
#include "msAPI_FreqTableDTV.h"
#if ENABLE_CI
#include "MApp_MultiTasks.h"
#endif
#if ENABLE_DVB_T2
#include "demodulator_T2.h"
#include "drvSYS.h"
#endif

#if ENABLE_PVR
#include "MApp_PVR.h"
#endif

#if (ENABLE_PIP)
#include "MApp_PIP.h"
#endif

#if(ENABLE_CI)
#include "MApp_CIMMI.h"
#endif

//============================================================================

#ifndef TUNER_PLL_STABLE_TIME
    #define TUNER_PLL_STABLE_TIME  50   //ms
#endif

//============================================================================

#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
BOOLEAN bIsCellIDRemoveMsgBox = FALSE;
#endif

#if ENABLE_TARGET_REGION
BOOLEAN bSetTargetRegion = FALSE;
MW_DVB_TARGET_REGION_INFO* pInfo;
#endif

BOOLEAN bisSetChannelListId = FALSE;
BOOLEAN bisSetLCNConfict = FALSE;

#if (ENABLE_LCN_CONFLICT)
WORD     wLcnConflictNumber = 1;
WORD    wLCNConflictChCounter = 0;
BOOLEAN bManualDoWithLcn = 1;
BOOLEAN bAlreadyShowConflictMsg = 0;
WORD     wStartChannelNum=1;
#if(ASTRA_HD_ENABLE)
#define MAX_LCNCONFLICT_NUM     50
extern WORD wLCNConflictList[MAX_LCNCONFLICT_NUM];
#endif
#endif
extern BOOLEAN MApp_ZUI_ACT_ExecuteAutoTuningAction(U16 act);
#if ENABLE_AUTOTEST
extern BOOLEAN g_bAutobuildDebug;
#endif

#if ENABLE_DVBC
    #if ENABLE_ZIGGO
    #define ENABLE_NIT_QUICK_SCAN 1
    #define ENABLE_GET_SDT_WITHOUT_ORDER 1
    #else
    #define ENABLE_NIT_QUICK_SCAN 0
    #define ENABLE_GET_SDT_WITHOUT_ORDER 0
    #endif
#else
#define ENABLE_NIT_QUICK_SCAN 0
#define ENABLE_GET_SDT_WITHOUT_ORDER 0
#endif


#if ENABLE_GET_SDT_WITHOUT_ORDER
static U32 u32WaitSDTTime;
#define WAIT_SDT_TIMEOUT 10000
#endif

#if ENABLE_FAVORITE_NETWORK
U32    u32PrevDVB_Frequency=0;
#endif

#if (ENABLE_HIERARCHY)
#error "Use Hierarchy will need to pay the money, please make sure you want to enable it"
#endif

//===================================================================================================

#if (BLOADER)
//U8   u8ScanPercentageNum;            // add for Auto Tune menu
//U16  u16ScanDtvChNum;                 // add for Auto Tune menu
BOOLEAN MApp_ZUI_ACT_ExecuteWndAction(U16 val)
{
    UNUSED(val);
    return TRUE;
}
void MApp_ChannelChange_DisableChannel (BOOLEAN u8IfStopDsmcc, SCALER_WIN eWindow /*U8 u8ChanBufIdx*/ ) //for change channel
{
    UNUSED(u8IfStopDsmcc);UNUSED(eWindow);
}
//EN_OSD_COUNTRY_SETTING MApp_GetOSDCountrySetting(void){}
#endif
//------------------------------------------------------------------------------
//                     Macro
//------------------------------------------------------------------------------
#if ENABLE_SCAN_ONELINE_MSG
#define SCAN_ONE_LINE_DBINFO(y)         y
#else
#define SCAN_ONE_LINE_DBINFO(y)         //y
#endif
#define SCAN_DBINFO(y)                  //y
#define DVBC_SCAN_DBINFO(y)             //y

//------------------------------------------------------------------------------

#define SCAN_DEBUG_CH           0x01
#define SCAN_DEBUG_PAL          0x02
#define SCAN_DEBUG_DVB          0x04

#define SCAN_DEBUG              0x00
#define SCAN_DBG(flag,s)        if (SCAN_DEBUG & flag) { MS_DEBUG_MSG(s); }

#define DEFAULT_MINOR_NUM       1
#define LOSS_SIGNAL_TIMEOUT     30000

//------------------------------------------------------------------------------
//                     Local
//------------------------------------------------------------------------------
#if(ENABLE_S2)
EN_SCAN_STATE enScanState = STATE_SCAN_INIT;
#else
static EN_SCAN_STATE enScanState = STATE_SCAN_INIT;
#endif
static EN_SCAN_STATE enPreScanState = STATE_SCAN_INIT;
static BOOLEAN fReturnToPrevious = FALSE;
static BOOLEAN fEndHalt = FALSE;


static EN_DVB_SCAN_STATE enDVBScanState = STATE_DVB_SCAN_INIT;

#if 1//ENABLE_T_C_COMBO
static EN_DVB_TYPE enDVBPreSelectType = EN_DVB_T_TYPE;
#endif

#if ENABLE_DVB
static EN_RET enDVBScanRetVal;
MS_TP_SETTING stTPSetting;
static SCAN_TABLE_CONFIG _stScanConfig;
#endif

static U16 u8RFCh;

U8 u8NumOfVchFound;
#if(ENABLE_S2_FAST_SCAN)
U8 uFastScanLoop;
#endif
U16 u16NumOfSrvAdd = 0;

U8 u8MuxTotal=0;

#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
typedef struct NetworkChange
{
    U8 bMuxRemove :1;
    U8 bMuxAdd :1;
    U8 bCellRemove :1;
    U8 bFreqChange :1;
    U8 bLossOfSignal :1;
    U8 reserve :3;
} NetworkChange;
static NetworkChange _stNetworkChangInfo={0,0,0,0,0,0};
static U32 _u32CheckMuxUpdateTimer=0;
static U32 _u32MessageDisplayTimer = 0;
static U32 _u32MessageLossSignalTimer = 0;
static U8   _u8FirstRF=0;
BOOLEAN bLossSignalRetune = TRUE;
EN_LOSS_SIGNAL_STATE enLossSignalState = LOSS_SIGNAL_INIT;
static BYTE _cOriginal_ChRF = INVALID_PHYSICAL_CHANNEL_NUMBER;
static BOOLEAN _bFrequency_change = FALSE;
static U8 _u32MessageDisplayImmediateEnd = 0;
#endif
#if(ENABLE_UPDATE_MULTIPLEX_NIT_UAE)
BOOLEAN g_NITUpdateAutoScan=FALSE;
BOOLEAN g_NITUpdateScanCanel=FALSE;
BOOLEAN g_NITVersionChange=FALSE;
#endif


#if ENABLE_DVBC

static _DVBC_SCAN_FLAG _stDVBCScanFlags;
static BOOL _bQuickInstallProcessed = FALSE;
U16 u16PorcessedFreqCnt=0,u16RemainFreqCnt=0;
U32 u32ProcessingCentreFreq;
#endif // #if ENABLE_DVBC


#if NTV_FUNCTION_ENABLE
static BOOLEAN bScanGoRegion= FALSE;
#endif

#if ENABLE_DVB_T2
static EN_SCAN_SWITCH_DEMOD _bScanT2 = DEMO_NUM;
static EN_T2_SERVICE_DEMOD  _bT2ServiceType = SERVICE_NUM;
static BOOLEAN _bForceMonitorT2Signal = 0;
static BOOLEAN _bInMonitorT2Status = FALSE;
static U8 _CurrentPlpID = 0xFF;
U8 _TotalPlpIDNum;
extern MS_U8 u8PlpIDList[32];
#endif

//********************************************************************************
//                     local prototype
//********************************************************************************
#if ENABLE_DVB
static void _MApp_DTV_Scan_TableConfig(SCAN_TABLE_CONFIG *pstScanConfig);
#endif

#if ENABLE_DVBC
static void _MApp_DTV_Scan_InitSymbolRate(void);

/*static*/ BOOLEAN _MApp_DTV_Scan_IncreaseModulationMode(void);

static void _MApp_DTV_Scan_InitDVBCScanFlags(void);
static void _MApp_DTV_Scan_InitModulationMode(void);
static void _MApp_DTV_Scan_AddNITFreqIntoScanTbl(void);
static BOOLEAN _MApp_DTV_Scan_GetTPSettingFromNITParams(MS_TP_SETTING *pstTPSetting);
//static BOOLEAN _MApp_DTV_Scan_SetCableTPSetting(_DVBC_SCAN_FLAG *stScanFlag, MS_TP_SETTING *pstTPSetting);
static void _MApp_DTV_Scan_SetNITAvailableFlag(BOOLEAN bNITFlag);
static BOOLEAN _MApp_DTV_Scan_GetNITAvailableFlag(void);
static BOOLEAN _MApp_Scan_DVBC_QuickInstall_ProcessKey(void);
static BOOLEAN _MApp_Scan_DVBC_QuickInstall_Init(void);
static BOOLEAN _MApp_Scan_DVBC_QuickInstall_AddOneDTVPchVchs(void);
static void _MApp_Scan_DVBC_QuickInstall_RemoveMismatchedTS(void);
static void _MApp_Scan_DVBC_QuickInstall_End(void);
#endif

//********************************************************************************
//                     Functions
//********************************************************************************

/********************************************************************************************************************************************************/
#if ENABLE_DTV
//#if ENABLE_SBTVD_SCAN
//EN_OSD_TUNE_TYPE_SETTING eTuneType = OSD_TUNE_TYPE_AIR_PLUS_CABLE;
//#else
EN_OSD_TUNE_TYPE_SETTING eTuneType = OSD_TUNE_TYPE_DTV_PLUS_ATV;
//#endif
#if ENABLE_DVBC_PLUS_DTMB_CHINA_APP
BOOLEAN _bNITScan = FALSE;
#endif
#else
EN_OSD_TUNE_TYPE_SETTING eTuneType = OSD_TUNE_TYPE_ATV_ONLY;
#endif


#if(ENABLE_S2)
static BOOLEAN _iss2bscancomplete=1;
MS_SAT_PARAM sat_info;
static MS_U32 _u32LockTimeMax;
static MS_U32 _u32WateTime;
MS_U8 _u8IsAstraLCNScan = 0;
DTVPROGRAMID_M TPSInfo;
EN_SAT_ROLL_OFF_TYPE eRollOff;
BLINDSCAN_STATUS _enBlindScanStatus = BLINDSCAN_READY;
extern BOOLEAN _GetSatInforByID(MS_U8 u8SATId,MS_SAT_PARAM *pSATParam);
extern DTVPROGRAMID_M _afe_param[MAX_TPSOFSAT_NUM];
extern WORD MApi_DB_DFT_PositionBySatID2PCHIndex(BYTE bSatID,WORD wPosition);
#endif

#if CHAKRA3_AUTO_TEST
extern U16 MApp_AT_Get_QamSetting(void);
extern U16 MApp_AT_Get_SymbolSetting(void);
#endif

//========================================================================

#define IS_NETWORK_UPDARE_COUNTRY(c)    MApp_Scan_Is_NETWORK_UPDARE_COUNTRY( (c) )
#define IS_DONOT_REMOVE_COUNTRY(c)      MApp_Scan_Is_DONOT_REMOVE_COUNTRY( (c) )

BOOLEAN MApp_Scan_Is_NETWORK_UPDARE_COUNTRY(EN_OSD_COUNTRY_SETTING eOSD_COUNTRY_SETTING)
{
    switch(eOSD_COUNTRY_SETTING)
    {
        case OSD_COUNTRY_MALAYSIA:
        case OSD_COUNTRY_KUWAIT:
        case OSD_COUNTRY_OMAN:
        case OSD_COUNTRY_QATAR:
        case OSD_COUNTRY_SAUDI_ARABIA:
        case OSD_COUNTRY_BAHRAIN:
//1281446: [SQC][Marlon_120B][1st_DVBT][Antenna Ready HD (Finland)] Standby channel update ->
        case OSD_COUNTRY_FINLAND:
    #if (ENABLE_COUNTRY_SINGAPORE)
        case OSD_COUNTRY_SINGAPORE:
    #endif

    #if (ENABLE_COUNTRY_GHANA)
        case OSD_COUNTRY_GHANA:
    #endif
        case OSD_COUNTRY_UNITED_ARAB_EMIRATES:
            return TRUE;
            break;;

        default:
            break;
    }

    return FALSE;
}

BOOLEAN MApp_Scan_Is_DONOT_REMOVE_COUNTRY(EN_OSD_COUNTRY_SETTING eOSD_COUNTRY_SETTING)
{

    switch(eOSD_COUNTRY_SETTING)
    {
        case OSD_COUNTRY_MALAYSIA:
        case OSD_COUNTRY_KUWAIT:
        case OSD_COUNTRY_OMAN:
        case OSD_COUNTRY_QATAR:
        case OSD_COUNTRY_SAUDI_ARABIA:
        case OSD_COUNTRY_BAHRAIN:
    #if (ENABLE_COUNTRY_SINGAPORE)
        case OSD_COUNTRY_SINGAPORE:
    #endif

    #if (ENABLE_COUNTRY_GHANA)
        case OSD_COUNTRY_GHANA:
    #endif
        case OSD_COUNTRY_UNITED_ARAB_EMIRATES:
            return TRUE;
            break;;

        default:
            break;
    }

    return FALSE;
}


#if ENABLE_DVB
static void MApp_Scan_ProcessUserInput( void )
{
    switch ( u8KeyCode )
    {
        case KEY_POWER:
        case DSC_KEY_PWROFF:
#if(ENABLE_UPDATE_MULTIPLEX_NIT_UAE)
            if(g_NITUpdateAutoScan)
            {
                g_NITUpdateScanCanel = TRUE;
                MApi_PNL_En(TRUE);
                MApi_PNL_SetBackLight(ENABLE);
                MUTE_Off();
                u8KeyCode = NULL;
            }
            else
#endif
            {
                enScanState = STATE_SCAN_GOTO_STANDBY;
                MApp_ZUI_ProcessKey(u8KeyCode);
            }
            break;


        case KEY_EXIT:
        case KEY_MENU:
            if (  stGenSetting.stScanMenuSetting.u8ScanType == SCAN_TYPE_AUTO
              #if ENABLE_DVBC
               || stGenSetting.stScanMenuSetting.u8ScanType == SCAN_TYPE_NETWORK
              #endif
              #if(ENABLE_S2)
               || stGenSetting.stScanMenuSetting.u8ScanType == S2_SCAN_TYPE_AUTO
               || stGenSetting.stScanMenuSetting.u8ScanType == S2_SCAN_TYPE_BLIND
               || stGenSetting.stScanMenuSetting.u8ScanType == S2_SCAN_TYPE_MANUAL
               || stGenSetting.stScanMenuSetting.u8ScanType == S2_SCAN_TYPE_NETWORK
              #if(ENABLE_S2_FAST_SCAN)
               || stGenSetting.stScanMenuSetting.u8ScanType == S2_SCAN_TYPE_FAST
              #endif
              #endif
               )
            {
                if(enScanState ==STATE_SCAN_PAUSE || enScanState ==STATE_SCAN_INIT)
                {
                  #if ENABLE_FAVORITE_NETWORK
                     if (g_bSetFavoriteNetwork)
                     {
                         MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_FAVORITE_NETWORK_EXIT_SCAN_PAUSE);
                     }
                  #endif

                    u8KeyCode = NULL;
                }
                else
                {
                #if(ENABLE_S2)
                    if(IsS2InUse())
                    {
                        u8KeyCode = KEY_EXIT;
                    }
                #endif

                    if(eTuneType == OSD_TUNE_TYPE_DTV_ONLY)
                    {
                        u8KeyCode = KEY_EXIT;
                    }

                    fEndHalt = FALSE;
                    fReturnToPrevious=FALSE;
                    enPreScanState = enScanState;
                    enScanState = STATE_SCAN_PAUSE;
                    MApp_ZUI_ProcessKey(u8KeyCode);
                }
            }
            break;


        case KEY_SELECT:
            if (  stGenSetting.stScanMenuSetting.u8ScanType == SCAN_TYPE_AUTO
              #if ENABLE_DVBC
               || stGenSetting.stScanMenuSetting.u8ScanType == SCAN_TYPE_NETWORK
              #endif
              #if(ENABLE_S2)
               || stGenSetting.stScanMenuSetting.u8ScanType == S2_SCAN_TYPE_AUTO
               || stGenSetting.stScanMenuSetting.u8ScanType == S2_SCAN_TYPE_BLIND
               || stGenSetting.stScanMenuSetting.u8ScanType == S2_SCAN_TYPE_MANUAL
               || stGenSetting.stScanMenuSetting.u8ScanType == S2_SCAN_TYPE_NETWORK
              #if(ENABLE_S2_FAST_SCAN)
               || stGenSetting.stScanMenuSetting.u8ScanType == S2_SCAN_TYPE_FAST
              #endif
              #endif
               )
            {
              #if ENABLE_FAVORITE_NETWORK
                if (g_bSetFavoriteNetwork)
                {
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SET_FAVORITE_NETWORK_SELECT);
                }
                else
              #endif
                {
                    MApp_ZUI_ProcessKey(u8KeyCode);
            }
            }
            break;


        case KEY_LEFT:
          #if ENABLE_FAVORITE_NETWORK
             if (g_bSetFavoriteNetwork)
             {
                 MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SET_FAVORITE_NETWORK_LEFT);
                 break;
             }
          #endif


        case KEY_RIGHT:
          #if ENABLE_FAVORITE_NETWORK
             if (g_bSetFavoriteNetwork)
             {
                 MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SET_FAVORITE_NETWORK_RIGHT);
                 break;
             }
          #endif


    #if(ENABLE_LCN_CONFLICT)
        case KEY_UP:
        case KEY_DOWN:
    #endif
        {
            if (  stGenSetting.stScanMenuSetting.u8ScanType == SCAN_TYPE_AUTO
              #if ENABLE_DVBC
               || stGenSetting.stScanMenuSetting.u8ScanType == SCAN_TYPE_NETWORK
              #endif
              #if (ENABLE_S2)
               || stGenSetting.stScanMenuSetting.u8ScanType == S2_SCAN_TYPE_AUTO
               || stGenSetting.stScanMenuSetting.u8ScanType == S2_SCAN_TYPE_BLIND
               || stGenSetting.stScanMenuSetting.u8ScanType == S2_SCAN_TYPE_MANUAL
               || stGenSetting.stScanMenuSetting.u8ScanType == S2_SCAN_TYPE_NETWORK
              #if(ENABLE_S2_FAST_SCAN)
               || stGenSetting.stScanMenuSetting.u8ScanType == S2_SCAN_TYPE_FAST
              #endif
              #endif
               )
            {
                MApp_ZUI_ProcessKey(u8KeyCode);
            }

            break;
        }

        default:
            break;
    }
    u8KeyCode = KEY_NULL;
}

/********************************************************************************************************************************************************/
BOOLEAN MApp_DTV_Scan_Init( void )
{
    /* initial variables ==============================================*/
#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
    if(g_enScanType !=SCAN_TYPE_NUM)
#endif
    {
        g_enScanType = (EN_SCAN_TYPE) stGenSetting.stScanMenuSetting.u8ScanType;
    }

    u8MuxTotal = 0;
    SCAN_DBINFO( printf( "\r\n MApp_DTV_Scan_Init: g_enScanType=%x ", g_enScanType ) );
    u8NumOfVchFound = 0;

#if ENABLE_FAVORITE_NETWORK
    g_bSetFavoriteNetwork  = FALSE;
#endif

#if ENABLE_TARGET_REGION
    bSetTargetRegion = FALSE;
#endif

    bisSetChannelListId = FALSE;
    bisSetLCNConfict = FALSE;

#if ENABLE_LCN_CONFLICT
    bManualDoWithLcn = TRUE;
    bAlreadyShowConflictMsg = FALSE;
    wStartChannelNum = 1;
#if(ASTRA_HD_ENABLE)
    if(GetASTRA_HD_ENABLE())
    {
        msAPI_CM_SetLCNConflictListNum(0);
    }
#endif
    wLCNConflictChCounter = 0;
#endif

#if ENABLE_DVBC_PLUS_DTMB_CHINA_APP
    if(IsDVBCInUse() && (g_enScanType==SCAN_TYPE_AUTO))
    {
        if(_bNITScan)
        {
            g_enScanType=SCAN_TYPE_NETWORK;
            DVBCNetworkIdScanType = 1;   // auto mode
        #if (!BLOADER)
            DVBCFreqScanType = 0;   //manual mode
            DVBCSymbolRateScanType = 1;
        #endif
        }
        else
        {
        #if (!BLOADER)
            DVBCSymbolRateScanType = 1;
        #endif
        }
    }
#endif

#if (!BLOADER)
#if(ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
    if(GetASTRA_HD_ENABLE())
    {
        MApp_SI_SetChannelTuningMode(E_CHSAVE_BY_PAT);
        msAPI_CM_ResetServiceListInfoData(TRUE);
        msAPI_CM_SetServiceListFocusIndex(0xFF);
        _u8IsAstraLCNScan = 0;
    }
#endif //#if(ASTRA_HD_ENABLE)


    MApp_SI_Scan_Init();
    u16NumOfSrvAdd = 0;
#endif

#if ENABLE_DVBC
//#if ENABLE_T_C_COMBO
    if(IsDVBCInUse())
//#endif
    {
        _MApp_DTV_Scan_InitDVBCScanFlags();
    }
#endif

    if (  SCAN_TYPE_AUTO == g_enScanType
      #if ENABLE_DVBC
       || SCAN_TYPE_NETWORK== g_enScanType
      #endif
      #if(ENABLE_S2)
       || S2_SCAN_TYPE_AUTO == g_enScanType
       || S2_SCAN_TYPE_BLIND== g_enScanType
       || S2_SCAN_TYPE_MANUAL== g_enScanType
       || S2_SCAN_TYPE_NETWORK== g_enScanType
      #if(ENABLE_S2_FAST_SCAN)
       || S2_SCAN_TYPE_FAST == g_enScanType
      #endif
      #endif
       )
    {
#if (!BLOADER)
        //reset DTV channel
        //msAPI_CM_ResetAllProgram();
      #if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
        MApp_SI_ResetNetwork();
      #endif

        if(msAPI_CM_GetCountry() == E_NORWAY || msAPI_CM_GetCountry() == E_SWEDEN)
        {
            //stGenSetting.stScanMenuSetting.u8BandWidth = E_RF_CH_BAND_7MHz;
          #if 1
            msAPI_DFT_SetBandwidth(stGenSetting.stScanMenuSetting.u8BandWidth);
          #else
            msAPI_DFT_SetBandwidth(E_RF_CH_BAND_7MHz);
            msAPI_SetCrossBandwidth(TRUE);
          #endif
        }
#endif

#if ENABLE_DVBC
    if(IsDVBCInUse())
    {
        _MApp_DTV_Scan_InitSymbolRate();
        _MApp_DTV_Scan_InitModulationMode();
        msAPI_DCFT_SelectBuiltInFreqTableforCountry(MApp_GetOSDCountrySetting());
        msAPI_DCFT_ResetNITNewFreqTbl();
        u8RFCh = INVALID_IDINDEX;     //dummy
    }
    else
#endif
    #if(ENABLE_S2)
    {
        if(IsS2InUse())
        {
            u8RFCh = 0;
        }
        else
        {
            u8RFCh = msAPI_DFT_GetFirstPhysicalChannelNumber();
        }
    }
    #else
        u8RFCh = msAPI_DFT_GetFirstPhysicalChannelNumber();
    #endif

    #if (ENABLE_DTV)
      #if ENABLE_OAD
        MApp_OAD_Init();
      #endif
    #endif

    #if ENABLE_SCAN_CM_DEBUG
        //u8ScanDtvChNum = 0;//msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY);;
        //u8ScanRadioChNum = 0;//msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY);;
    #endif
    }
    else
    {
    #if ENABLE_DVBC
        if(IsDVBCInUse())
        {
            u8RFCh = stGenSetting.stScanMenuSetting.u8RFChannelNumber = INVALID_RF_CHANNEL_NUMBER;   //dummy
            U16 u16IDIndex;
            if( msAPI_CM_GetIDIndexWithFreq(MApp_CadtvManualTuning_GetFrequency(), &u16IDIndex) )
            {
                u8RFCh = u16IDIndex;
            }
        }
        else
    #endif
        {
        #if(ENABLE_S2)
            if(IsS2InUse())
            {
                u8RFCh = 0;
            }
            else
        #endif
            {
                u8RFCh = stGenSetting.stScanMenuSetting.u8RFChannelNumber;
            }
        }
    }

#if (!BLOADER)
    MApp_ChannelChange_DisableChannel(TRUE, MAIN_WINDOW);
    MApp_Dmx_CloseAllFilters();
#endif

    u8ScanPercentageNum = 0;
#if ENABLE_DVBC
    u16PorcessedFreqCnt = 0;
    u16RemainFreqCnt = 0;
    u32ProcessingCentreFreq =0;
#endif

    return TRUE;
}

/********************************************************************************************************************************************************/
void MApp_DTV_Scan_End( BOOLEAN bSkipDupSrvRemove )
{
    WORD wPosition;

    SCAN_DBINFO( printf("\n MApp_DTV_Scan_End(%d) ", bSkipDupSrvRemove) );

#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
    if(msAPI_SI_IsSpecificCountry(MApp_GetSICountry(OSD_COUNTRY_SETTING),SI_SUPPORT_NETWORK_UPDATE_SPECIFIC_COUNTRY))
    {
        MApp_SI_Free_NetworkChangeInfo();
    }
#endif

#if (ENABLE_LCN_CONFLICT)
    if (((SCAN_TYPE_AUTO== g_enScanType) && (OSD_COUNTRY_SETTING == OSD_COUNTRY_ITALY))
#if(ASTRA_HD_ENABLE)
        ||(S2_SCAN_TYPE_NETWORK == g_enScanType && GetASTRA_HD_ENABLE())
#endif
    )
    {
        DTV_SIMPLE_SERVICE_INFO *pInfoLncConflict;
        MEMBER_SERVICETYPE bServiceType = msAPI_CM_GetCurrentServiceType();
        BOOL bComplete = 1;
        wLCNConflictChCounter = 0;
        while(((pInfoLncConflict=msAPI_CM_GetDuplicateService(bServiceType,wStartChannelNum))!=NULL)&&bManualDoWithLcn)
        {
            bComplete = 0;
            enPreScanState = enScanState;
            fEndHalt = FALSE;
            fReturnToPrevious=FALSE;
            enScanState = STATE_SCAN_PAUSE;
            if(!bAlreadyShowConflictMsg)
            {
                bAlreadyShowConflictMsg = TRUE;
                MApp_ZUI_ACT_ExecuteAutoTuningAction(EN_EXE_SET_LCN_CONFLICT);
            }
            wStartChannelNum=pInfoLncConflict->wNumber+1;
            while(pInfoLncConflict)
            {
                printf("\n bServiceToSelect %d lcn %d position %d name %.*s ",pInfoLncConflict->bServiceToSelect,pInfoLncConflict->wNumber,pInfoLncConflict->dwPosition,MAX_SERVICE_NAME,pInfoLncConflict->bChannelName);
                if(pInfoLncConflict->bServiceToSelect && wLCNConflictChCounter<MAX_SUPPORT_LCN_CONFLICT_NUM)
                {
                    wLcnConflictNumber = pInfoLncConflict->wNumber;
                    memcpy(g_ucLcnConflict[wLCNConflictChCounter].bLcnConflictChannelName, pInfoLncConflict->bChannelName, MAX_SERVICE_NAME);
                    g_ucLcnConflict[wLCNConflictChCounter].dwLcnConflictPosition = pInfoLncConflict->dwPosition;
#if(ASTRA_HD_ENABLE)
                    if(GetASTRA_HD_ENABLE())
                    {
                        MS_U8 u8TempConflictNum = msAPI_CM_GetLCNConflictListNum();
                        if(u8TempConflictNum < MAX_LCNCONFLICT_NUM && wLCNConflictList[u8TempConflictNum-1] != pInfoLncConflict->wNumber)
                        {
                            wLCNConflictList[u8TempConflictNum] = pInfoLncConflict->wNumber;
                            printf("wLCNConflictList[%d]=%d\n",u8TempConflictNum,wLCNConflictList[u8TempConflictNum]);
                            u8TempConflictNum++;
                            msAPI_CM_SetLCNConflictListNum(u8TempConflictNum);
                        }
                    }
#endif
                    wLCNConflictChCounter++;
                }
                pInfoLncConflict=pInfoLncConflict->next;
            }

            if(wLcnConflictNumber != wStartChannelNum)
                break;
        }

        if(bManualDoWithLcn && !bComplete)
        {
            MApp_ZUI_ACT_ExecuteAutoTuningAction(EN_EXE_LCN_REFREASH_LCN_CONFILCT_MENU);
            return;
        }

        msAPI_CM_ResetLCNConflictParams();
    }
#endif

#if ENABLE_AUTOTEST
    if(g_bAutobuildDebug)
    {
        printf("\n 31_DTV_Tuning_End_%d \n", u16ScanDtvChNum);
    }
#endif

#if (!ENABLE_DVB_T2 && !ENABLE_HIERARCHY)
    if (SCAN_TYPE_MANUAL == g_enScanType)
    {
        SI_SHORT_DTV_CHANNEL_INFO *pastVirtualCh = MApp_SI_Get_PastVirtualCh();
        WORD *au16ServiceIDs=NULL;//[MAX_VC_PER_PHYSICAL];
        MEMBER_SERVICETYPE *aeServiceType=NULL;//[MAX_VC_PER_PHYSICAL];
        U8   i,u8RemovedChnNum,u8PLP_ID;
        U8 u8ServiceCount=MApp_SI_GetScanNumOfPatItem();

        au16ServiceIDs=(WORD*)msAPI_Memory_Allocate(sizeof(WORD)*MAX_VC_PER_PHYSICAL, BUF_ID_DVB_SCAN_END_1);
        aeServiceType=(MEMBER_SERVICETYPE*)msAPI_Memory_Allocate(sizeof(MEMBER_SERVICETYPE)*MAX_VC_PER_PHYSICAL, BUF_ID_DVB_SCAN_END_2);

        if(au16ServiceIDs && aeServiceType)
        {
            for( i = 0; i < u8ServiceCount; i++)
            {
                au16ServiceIDs[i] = pastVirtualCh[i].wService_ID;
                switch(pastVirtualCh[i].stCHAttribute.bServiceType)
                {
                    case E_TYPE_RADIO:
                        aeServiceType[i] =E_SERVICETYPE_RADIO;
                        break;

                    case E_TYPE_DATA:
                        aeServiceType[i] =E_SERVICETYPE_DATA;
                        break;

                    default:
                    case E_TYPE_DTV:
                        aeServiceType[i] =E_SERVICETYPE_DTV;
                        break;
                }
                //aeServiceType[i] = (MEMBER_SERVICETYPE) pastVirtualCh[i].stCHAttribute.bServiceType;
            }
            msAPI_Tuner_Get_PLP_ID(&u8PLP_ID);
            u8RemovedChnNum = msAPI_CM_RemoveMismatchedProgram(u8RFCh,pastVirtualCh[0].wTransportStream_ID, u8PLP_ID,msAPI_Tuner_Get_HpLp(), au16ServiceIDs, aeServiceType, u8NumOfVchFound,0xff,0xffff);
        }
        else
        {
            ASSERT(0);
        }

        if(au16ServiceIDs)msAPI_Memory_Free(au16ServiceIDs, BUF_ID_DVB_SCAN_END_1);
        if(aeServiceType)msAPI_Memory_Free(aeServiceType, BUF_ID_DVB_SCAN_END_2);
        //printf("SCAN_TYPE_MANUAL>> u8RemovedChnNum = %bu\n", u8RemovedChnNum);
    }
#endif

#if ENABLE_OAD
    if(MApp_Dmx_GetOADScanMode()==FALSE && MApp_OAD_IsOadScanCheck() == FALSE)
#endif
    {
    #if ENABLE_TARGET_REGION
        if (SCAN_TYPE_AUTO== g_enScanType
        && bSetTargetRegion == FALSE
        && (OSD_COUNTRY_SETTING == OSD_COUNTRY_UK
        || OSD_COUNTRY_SETTING == OSD_COUNTRY_MALAYSIA
#if(ENABLE_COUNTRY_SINGAPORE)
        || OSD_COUNTRY_SETTING == OSD_COUNTRY_SINGAPORE
#endif
#if(ENABLE_COUNTRY_MYANMAR)
        || OSD_COUNTRY_SETTING == OSD_COUNTRY_MYANMAR
#endif
#if (ENABLE_COUNTRY_GHANA)
        || OSD_COUNTRY_SETTING == OSD_COUNTRY_GHANA
#endif
        ))
        {
            bSetTargetRegion = TRUE;
            pInfo=MApp_SI_GetTargetRegionNameInfo();
            if(pInfo != NULL)
            {
            #if 0
                int i,j,k,l;
                for( i=0;i<pInfo->u8CountryNum;i++)
                {
                    printf("country %.*s\n",3,pInfo->pCountryInfo[i].au8CountryCode);
                    for( j=0;j<pInfo->pCountryInfo[i].u16PrimaryRegionNum;j++)
                    {
                        printf("__primary %x %s\n",pInfo->pCountryInfo[i].pPrimaryRegionInfo[j].u8Code
                        ,pInfo->pCountryInfo[i].pPrimaryRegionInfo[j].name);
                        for( k=0;k<pInfo->pCountryInfo[i].pPrimaryRegionInfo[j].u16SecondaryRegionNum;k++)
                        {
                            printf("____secondary %x %s\n",pInfo->pCountryInfo[i].pPrimaryRegionInfo[j].pSecondaryRegionInfo[k].u8Code
                            ,pInfo->pCountryInfo[i].pPrimaryRegionInfo[j].pSecondaryRegionInfo[k].name);
                            for( l=0;l<pInfo->pCountryInfo[i].pPrimaryRegionInfo[j].pSecondaryRegionInfo[k].u16TertiaryRegionNum;l++)
                            {
                                printf("______teritary %x %s\n",pInfo->pCountryInfo[i].pPrimaryRegionInfo[j].pSecondaryRegionInfo[k].pTertiaryRegionInfo[l].u16Code
                                    ,pInfo->pCountryInfo[i].pPrimaryRegionInfo[j].pSecondaryRegionInfo[k].pTertiaryRegionInfo[l].name);
                            }
                        }
                    }
                }
            #endif
                enPreScanState = enScanState;
                fEndHalt = FALSE;
                fReturnToPrevious=FALSE;
                enScanState = STATE_SCAN_PAUSE;
                MApp_ZUI_ACT_ExecuteAutoTuningAction(EN_EXE_SET_TARGET_REGION);
                return;
            }
        }
    #endif
    }

#if (ASTRA_LCN_ENABLE)
    if (msAPI_CM_GetServiceListIdCount() && (!bisSetChannelListId) && _u8IsAstraLCNScan)
    {
        bisSetChannelListId = TRUE;
        enPreScanState = enScanState;
        fEndHalt = FALSE;
        fReturnToPrevious=FALSE;
        enScanState = STATE_SCAN_PAUSE;
        MApp_ZUI_ACT_ExecuteAutoTuningAction(EN_EXE_SET_ASTRA_CHANNEL_ID);
        return;
    }
#endif // (ASTRA_LCN_ENABLE)

#if (ENABLE_FAVORITE_NETWORK)
    if (SCAN_TYPE_AUTO== g_enScanType && g_bSetFavoriteNetwork == FALSE && OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY)
    {
        if (g_u8NetworkTotal > 1)
        {
           g_bSetFavoriteNetwork = 1;
//           g_u8NetworkIndex  = 0;
           enPreScanState     = enScanState;
           fEndHalt          = FALSE;
           fReturnToPrevious = FALSE;
           enScanState         = STATE_SCAN_PAUSE;
           MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SET_FAVORITE_NETWORK);
           printf("\n 123 <MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SET_FAVORITE_NETWORK)>");
           return;
        }
    }
#endif

    MApp_SI_Scan_End();

    if(TRUE != msAPI_CM_ArrangeDataManager(TRUE,bSkipDupSrvRemove))
    {
        SCAN_DBINFO( printf("\n MApp_DTV_Scan_End: msAPI_CM_ArrangeDataManager FAIL !! "));
    }

#if ENABLE_DVBC
//#if ENABLE_T_C_COMBO
    if(IsDVBCInUse())
//#endif
    {
        _MApp_DTV_Scan_SetNITAvailableFlag(FALSE);
    }
#endif

#if 0//ENABLE_SCAN_CM_DEBUG
    msAPI_CM_PrintAllProgram();
#endif

#if ENABLE_OAD
    if(MApp_Dmx_GetOADScanMode()==FALSE && MApp_OAD_IsOadScanCheck() == FALSE)
#endif
    {
        switch( g_enScanType )
        {
        #if ENABLE_DVBC
            case SCAN_TYPE_NETWORK:
        #endif
        #if(ENABLE_S2)
            case S2_SCAN_TYPE_AUTO:
            case S2_SCAN_TYPE_BLIND:
            case S2_SCAN_TYPE_MANUAL:
            case S2_SCAN_TYPE_NETWORK:
        #if(ENABLE_S2_FAST_SCAN)
        case S2_SCAN_TYPE_FAST:
        #endif
        #endif
            case SCAN_TYPE_AUTO:

            #if (ENABLE_S2&&ENABLE_S2_CH_CHANGE_TO_SEARCHPOSITION)
                if( g_u16SearchPosition != 0xffff )
                {
                    msAPI_CM_S2SetsearchPosition(g_u16SearchPosition);
                }
                else
            #endif

                if(msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO) > 0)
                {

                    msAPI_CM_SetCurrentServiceType(E_SERVICETYPE_DTV);
                }
                else if(msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO) > 0)
                {

                    msAPI_CM_SetCurrentServiceType(E_SERVICETYPE_RADIO);
                }
                else if(msAPI_CM_CountProgram(E_SERVICETYPE_DATA, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO) > 0)
                {

                    msAPI_CM_SetCurrentServiceType(E_SERVICETYPE_DATA);
                }
                else
                {
                    msAPI_CM_SetCurrentServiceType(E_SERVICETYPE_DTV);
                }

                msAPI_CM_SetCurrentPosition(E_SERVICETYPE_DTV,0);
                msAPI_CM_SetCurrentPosition(E_SERVICETYPE_RADIO,0);
            #if NORDIG_FUNC //for Nordig Spec v.20
                msAPI_CM_SetCurrentPosition(E_SERVICETYPE_DATA,0);
            #endif

                if(msAPI_CM_GetCountry() == E_NORWAY || msAPI_CM_GetCountry() == E_SWEDEN)
                {
                    msAPI_SetCrossBandwidth(FALSE);
                    msAPI_DFT_SetBandwidth(stGenSetting.stScanMenuSetting.u8BandWidth);
                }

                break;


        #if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
            case SCAN_TYPE_UPDATE_MUX:
                MApp_SI_ResetNetworkNewService();
                if( TRUE == msAPI_CM_GetFirstPositionInPCN(E_SERVICETYPE_DTV, _u8FirstRF, &wPosition) )
                {
                    msAPI_CM_SetCurrentServiceType(E_SERVICETYPE_DTV);
                    msAPI_CM_SetCurrentPosition(E_SERVICETYPE_DTV, wPosition);
                }
                else if( TRUE == msAPI_CM_GetFirstPositionInPCN(E_SERVICETYPE_RADIO, _u8FirstRF, &wPosition) )
                {
                    msAPI_CM_SetCurrentServiceType(E_SERVICETYPE_RADIO);
                    msAPI_CM_SetCurrentPosition(E_SERVICETYPE_RADIO, wPosition);
                }
            #if (NORDIG_FUNC) //for Nordig Spec v2.0
                else if( TRUE == msAPI_CM_GetFirstPositionInPCN(E_SERVICETYPE_DATA, _u8FirstRF, &wPosition) )
                {
                    msAPI_CM_SetCurrentServiceType(E_SERVICETYPE_DATA);
                    msAPI_CM_SetCurrentPosition(E_SERVICETYPE_DATA, wPosition);
                }
            #endif
                else
                {
                    msAPI_CM_SetCurrentServiceType(E_SERVICETYPE_DTV);
                    msAPI_CM_SetCurrentPosition(E_SERVICETYPE_DTV,0);
                    msAPI_CM_SetCurrentPosition(E_SERVICETYPE_RADIO,0);
                #if (NORDIG_FUNC) //for Nordig Spec v.20
                    msAPI_CM_SetCurrentPosition(E_SERVICETYPE_DATA,0);
                #endif
                }
                break;
        #endif // #if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)


            case SCAN_TYPE_MANUAL:
                /* After manual scan , search the first position(DTV or Radio) in current PCN */
                if( TRUE == msAPI_CM_GetFirstPositionInPCN(E_SERVICETYPE_DTV, u8RFCh, &wPosition) )
                {
                    msAPI_CM_SetCurrentServiceType(E_SERVICETYPE_DTV);
                    msAPI_CM_SetCurrentPosition(E_SERVICETYPE_DTV, wPosition);
                }
                else if( TRUE == msAPI_CM_GetFirstPositionInPCN(E_SERVICETYPE_RADIO, u8RFCh, &wPosition) )
                {
                    msAPI_CM_SetCurrentServiceType(E_SERVICETYPE_RADIO);
                    msAPI_CM_SetCurrentPosition(E_SERVICETYPE_RADIO, wPosition);
                }
              #if NORDIG_FUNC //for Nordig Spec v2.0
                else if( TRUE == msAPI_CM_GetFirstPositionInPCN(E_SERVICETYPE_DATA, u8RFCh, &wPosition) )
                {
                    msAPI_CM_SetCurrentServiceType(E_SERVICETYPE_DATA);
                    msAPI_CM_SetCurrentPosition(E_SERVICETYPE_DATA, wPosition);
                }
              #endif

                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_DTV_MANUAL_SCAN_END);
              #if ENABLE_DVBC
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CADTV_MANUAL_SCAN_END);
              #endif
                break;


            default:
                break;
        }
    }

    //MApp_Dmx_EnableTableMonitor();

#if (ENABLE_DTV_EPG)
    /* init epg database */
    MApp_EIT_All_Sche_ResetFilter();
  #if (!BLOADER)
    MApp_Epg_Init();
  #endif

    if (  stGenSetting.stScanMenuSetting.u8ScanType == SCAN_TYPE_AUTO
      #if ENABLE_DVBC
       || stGenSetting.stScanMenuSetting.u8ScanType == SCAN_TYPE_NETWORK
      #endif
      #if(ENABLE_S2)
       || stGenSetting.stScanMenuSetting.u8ScanType == S2_SCAN_TYPE_AUTO
       || stGenSetting.stScanMenuSetting.u8ScanType == S2_SCAN_TYPE_BLIND
       || stGenSetting.stScanMenuSetting.u8ScanType == S2_SCAN_TYPE_MANUAL
       || stGenSetting.stScanMenuSetting.u8ScanType == S2_SCAN_TYPE_NETWORK
      #if(ENABLE_S2_FAST_SCAN)
       || stGenSetting.stScanMenuSetting.u8ScanType == S2_SCAN_TYPE_FAST
      #endif
      #endif
        )
    {
        MApp_EpgTimer_InitTimerSettings(TRUE);
    }
#endif  //#if (ENABLE_DTV_EPG)

#if (!BLOADER)
    msAPI_ClearIRFIFO();
#endif

#if ENABLE_SBTVD_CM_APP
    if(msAPI_SRC_IS_SBTVD_InUse())
    {
        if(msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO)||msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO))
        {
            msAPI_CHPROC_CM_InitOridial();
        }
    }
#endif
}
/*****************************************************************************/


/********************************************************************************************************************************************************/

/*****************************************************************************/
//static void MApp_Scan_SetLCNAssignmentFlag( U16 u16LCN, U8 eService )
//{
//    if(eService == E_SERVICETYPE_DTV)
//    {
//        stGenSetting.g_SysSetting.au8TVLCNAssignment[u16LCN / 8] |= ( 0x01 << ( u16LCN % 8 ) );
//    }
//    else
//    {
//        stGenSetting.g_SysSetting.au8RadioLCNAssignment[u16LCN / 8] |= ( 0x01 << ( u16LCN % 8 ) );
//    }
//}
/*****************************************************************************/
//static void MApp_Scan_UnsetLCNAssignmentFlag( U16 u16LCN,  U8 eService )
//{
//    if(eService == E_SERVICETYPE_DTV)
//    {
//        stGenSetting.g_SysSetting.au8TVLCNAssignment[u16LCN / 8] &= ~( 0x01 << ( u16LCN % 8 ) );
//    }
//    else
//    {
//        stGenSetting.g_SysSetting.au8RadioLCNAssignment[u16LCN / 8] &= ~( 0x01 << ( u16LCN % 8 ) );
//    }
//}
/*****************************************************************************/
//static BOOLEAN MApp_Scan_LCNAssignmentCheck( U16 u16LCN,  U8 eService )
//{
//    BOOLEAN bReturn = FALSE;
//
//    if(eService == E_SERVICETYPE_DTV)
//    {
//        if( ( stGenSetting.g_SysSetting.au8TVLCNAssignment[u16LCN / 8] & ( 0x01 << ( u16LCN % 8 ) ) ) == ( 0x01 << ( u16LCN % 8 ) ) )
//        {
//            bReturn = true;
//        }
//    }
//    else
//    {
//        if( ( stGenSetting.g_SysSetting.au8RadioLCNAssignment[u16LCN / 8] & ( 0x01 << ( u16LCN % 8 ) ) ) == ( 0x01 << ( u16LCN % 8 ) ) )
//        {
//            bReturn = true;
//        }
//    }
//    return bReturn;
//}
/*****************************************************************************/
//static void MApp_Scan_ReAllocateLCN( _DTVPROGRAMDATA *pstService )
//{
//    #if (SI_SCAN_NEW_STRUCT)
//    U8 eService = E_SERVICETYPE_RADIO;
//
//    if(pstService->u16VideoPID != INVALID_PID)
//    {
//        eService = E_SERVICETYPE_DTV;
//    }
//    while( MApp_Scan_LCNAssignmentCheck( stGenSetting.g_SysSetting.u16OverflowLCN, eService) == true )
//    {
//        stGenSetting.g_SysSetting.u16OverflowLCN += 1;
//    }
//    #else
//    while( MApp_Scan_LCNAssignmentCheck( stGenSetting.g_SysSetting.u16OverflowLCN, pstService->stCHAttribute.bServiceType) == true )
//    {
//        stGenSetting.g_SysSetting.u16OverflowLCN += 1;
//    }
//    #endif
//    pstService->u16LogicalChannelNumber = stGenSetting.g_SysSetting.u16OverflowLCN;
//    stGenSetting.g_SysSetting.u16OverflowLCN += 1;
//
//    if( stGenSetting.g_SysSetting.u16OverflowLCN > MAX_NUM_OF_LCN_VALUE )
//    {
//        stGenSetting.g_SysSetting.u16OverflowLCN = MAIN_OVERFLOW_AREA_START_INDEX;
//    }
//}



/********************************************************************************************************************************************************/
/********************************************************************************************************************************************************/
static U8 MApp_Scan_AddOneDTVPchVchs( U16 u16PhysicalChIdx,SI_SHORT_DTV_CHANNEL_INFO *pastVirtualCh,U8 u8NumOfVch,BOOLEAN bCheckServiceInfo ,BOOLEAN *bDBfull)
{
    U8 u8Loop_1;
    U8 u8NumOfActiveCh = 0;
    U8 u8TotalCh = 0;
    BOOLEAN fIsDummyCh;
    BOOLEAN bBackupUsingBuffer;
    BOOLEAN eResult;
    MEMBER_SERVICETYPE bServiceType = E_SERVICETYPE_INVALID;
    WORD wPosition,wLCN;
    SI_DTV_CHANNEL_INFO stDtvPgmData;
    SI_DTVPROGRAMID stDtvIDTable;
    #if 1//ENABLE_DVBC
    MS_TP_SETTING pstCurTPsetting;
    #endif
    U8 au8NetWorkName[MAX_NETWORK_NAME];
    U8 len;

    BOOLEAN bFull=FALSE;
    fIsDummyCh = FALSE;
    bBackupUsingBuffer = FALSE;

#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
    MEMBER_SERVICETYPE eCurServiceType;
    WORD wCurPosition;
    BYTE cLossSignalRF;

    eCurServiceType = msAPI_CM_GetCurrentServiceType();
    wCurPosition = msAPI_CM_GetCurrentPosition(eCurServiceType);
    cLossSignalRF = msAPI_CM_GetOriginalRFnumber(eCurServiceType, wCurPosition);
    //printf("cLossSignalRF   %bu\n",cLossSignalRF);
#endif

#if ENABLE_DVBC
    // check NID is match or not when Network ID scan was enabled
    if (_stScanConfig.bNetworkIDFilterEn)
    {
        if (pastVirtualCh[0].wNetwork_ID != _stScanConfig.bNetworkID)
        {
            return 0;
        }
    }
#endif

    //#if ENABLE_DVBC
    memset(&stDtvIDTable, 0, sizeof(stDtvIDTable));
#if ENABLE_DVB_T2
    stDtvIDTable.u8PLP_ID = INVALID_PLPID;
#endif

    //#endif
    //MApp_SI_GetDtvPmgData(&pastVirtualCh[0], 0, &stDtvPgmData);

    stDtvIDTable.wNetwork_ID = pastVirtualCh[0].wNetwork_ID;
    stDtvIDTable.wTransportStream_ID = pastVirtualCh[0].wTransportStream_ID;
    stDtvIDTable.wOriginalNetwork_ID = pastVirtualCh[0].wOriginalNetwork_ID;

    for (u8Loop_1=0;u8Loop_1<u8NumOfVch;u8Loop_1++)
    {
        if (pastVirtualCh[u8Loop_1].wNetwork_ID != INVALID_NID && \
            pastVirtualCh[u8Loop_1].wOriginalNetwork_ID!=INVALID_ON_ID &&\
            pastVirtualCh[u8Loop_1].wService_ID!=INVALID_SERVICE_ID)
        {
            stDtvIDTable.wNetwork_ID = pastVirtualCh[u8Loop_1].wNetwork_ID;
            stDtvIDTable.wTransportStream_ID = pastVirtualCh[u8Loop_1].wTransportStream_ID;
            stDtvIDTable.wOriginalNetwork_ID = pastVirtualCh[u8Loop_1].wOriginalNetwork_ID;
#if (ENABLE_SAVE_SQI)
            stDtvIDTable.wStrengthQuality = pastVirtualCh[u8Loop_1].stCHAttribute.wSignalStrength;
#endif
            break;
        }
    }

    //if(pastVirtualCh[0].wTransportStream_ID != INVALID_TS_ID )//&& pastVirtualCh[0].wOriginalNetwork_ID != INVALID_ON_ID)
//    if (u8Loop_1<u8NumOfVch)
    {
        stDtvIDTable.cRFChannelNumber = u16PhysicalChIdx;
    #if ENABLE_TARGET_REGION
        stDtvIDTable.u8Region=DEFAULT_REGION;
    #endif

    #if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
        if((OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY) && (MApp_DTV_Scan_GetLossSignalState() == LOSS_SIGNAL_RETUNE))
        {
            for(u8Loop_1=0; u8Loop_1<u8NumOfVch; u8Loop_1++)
            {
                if(pastVirtualCh[u8Loop_1].wService_ID == msAPI_CM_GetService_ID(eCurServiceType, wCurPosition)
                    &&(pastVirtualCh[u8Loop_1].wOriginalNetwork_ID == msAPI_CM_GetON_ID(eCurServiceType, wCurPosition))
                    &&(cLossSignalRF == INVALID_PHYSICAL_CHANNEL_NUMBER || cLossSignalRF != _cOriginal_ChRF))
                {
                    stDtvIDTable.cOriginal_RF = _cOriginal_ChRF;
                    stDtvIDTable.dwAlternativeTime = 0;
                    if((MApp_SI_IS_GotTDTOrTOT()==TRUE))
                    {
                    stDtvIDTable.dwAlternativeTime = msAPI_Timer_GetSystemTime();
                    }
                    //printf("%s cOriginal_RF %bu, dwAlternativeTime %u\n",__FUNCTION__,stDtvIDTable.cOriginal_RF,stDtvIDTable.dwAlternativeTime);
                    break;
                }
            }
            if(u8Loop_1 == u8NumOfVch)
            {
                stDtvIDTable.cOriginal_RF = INVALID_PHYSICAL_CHANNEL_NUMBER;
                stDtvIDTable.dwAlternativeTime = INVALID_ALTERNATIVETIME;
            }
        }
        else
        {
            stDtvIDTable.cOriginal_RF = INVALID_PHYSICAL_CHANNEL_NUMBER;
            stDtvIDTable.dwAlternativeTime = INVALID_ALTERNATIVETIME;
        }
    #endif

        msAPI_Tuner_Get_CELL_ID(&stDtvIDTable.wCellID);

    #if 1//ENABLE_DVBC
        memset(&pstCurTPsetting, 0, sizeof(MS_TP_SETTING));
        msAPI_Tuner_GetCurTPSetting(&pstCurTPsetting);
        stDtvIDTable.u32Frequency = pstCurTPsetting.u32Frequency ;
        stDtvIDTable.u32SymbRate = pstCurTPsetting.u32Symbol_rate ;
        stDtvIDTable.QamMode = pstCurTPsetting.u8Modulation ;
        stDtvIDTable.enBandWidth = pstCurTPsetting.enBandWidth;
    #endif

    #if (ENABLE_DVB_T2)
        msAPI_Tuner_Get_PLP_ID(&stDtvIDTable.u8PLP_ID);
    #endif

    #if (ENABLE_HIERARCHY)
        stDtvIDTable.u8HpLp=msAPI_Tuner_Get_HpLp();
    #endif
    }
    if ((TRUE == MApp_SI_Get_NetWorkName(au8NetWorkName,&len,MAX_NETWORK_NAME)) /*&& (0!=au8NetWorkName[0])*/)
    {
        msAPI_CM_SetCurrentNetworkName(au8NetWorkName, len);
    }

    for(u8Loop_1=0; u8Loop_1<u8NumOfVch; u8Loop_1++)
    {
        MApp_SI_GetDtvPmgData(&pastVirtualCh[u8Loop_1], u8Loop_1, &stDtvPgmData);
    #if(ENABLE_S2_FAST_SCAN)
        stDtvPgmData.stCHAttribute.bIsFastScan = FALSE;
    #endif
        #if ENABLE_SBTVD_SCAN
        if(IsISDBTInUse())
        {
            if(stDtvPgmData.stLCN.bPhysicalChannel > MAX_UHF_PHYSICAL_CHANNEL_NUMBER_ISDBT)
            {
                stDtvPgmData.stLCN.bPhysicalChannel = u16PhysicalChIdx;
            }
            if(stDtvPgmData.stLCN.bPhysicalChannel == 0xFF)
            {
                continue ;
            }
        }
        #endif

        if( bCheckServiceInfo == TRUE )
        {
            if( MApp_SI_Action_CheckServiceInfo( &stDtvPgmData ) == FALSE )
            {
                #if ENABLE_SCAN_CM_DEBUG
                printf( "MApp_Scan_CheckServiceInfo %u fail (Null Service)!\n", u8Loop_1 );
                #else
                SCAN_DBINFO( printf( "MApp_Scan_CheckServiceInfo %u fail (Null Service)!\n", u8Loop_1 ) );
                #endif
                continue;
            }

            if(u8NumOfActiveCh != u8Loop_1)
            {
                memcpy(&pastVirtualCh[u8NumOfActiveCh], &pastVirtualCh[u8Loop_1], sizeof(SI_SHORT_DTV_CHANNEL_INFO));
            }
            pastVirtualCh[u8NumOfActiveCh].stCHAttribute.bServiceType = stDtvPgmData.stCHAttribute.bServiceType;
        }

        if (  (g_enScanType == SCAN_TYPE_AUTO)
          #if ENABLE_DVBC
           || (g_enScanType == SCAN_TYPE_NETWORK)
          #endif
           )
        {
            eResult = msAPI_SI_AddProgram(&stDtvIDTable, &stDtvPgmData,&bFull, FALSE);
            if(TRUE == eResult)
            {
                if(stDtvPgmData.stCHAttribute.bServiceType == E_TYPE_DTV)
                    u16ScanDtvChNum++;
              #if NORDIG_FUNC //for Nordig Spec v2.0
                else if(stDtvPgmData.stCHAttribute.bServiceType == E_TYPE_DATA)
                    u16ScanDataChNum++;
              #endif
                else if (stDtvPgmData.stCHAttribute.bServiceType == E_TYPE_RADIO)
                    u16ScanRadioChNum++;
            }
        }
        else
        {
            BOOLEAN bServiceExist;
        #if (ENABLE_DVB_T2)
            WORD plp;
        #endif
            //eResult = msAPI_SI_AddProgram(&stDtvIDTable, &stDtvPgmData,&bFull, FALSE);
        #if ENABLE_DVBC
//#if ENABLE_T_C_COMBO
            if(IsDVBCInUse())
//#endif
            {
                if(FALSE == msAPI_SI_AddProgramIDTable(&stDtvIDTable,&stDtvPgmData.bIDIdex))
                {
                    continue ;
                }
                u8RFCh = u16PhysicalChIdx = stDtvPgmData.bIDIdex;
            }
        #endif
            bServiceExist=msAPI_CM_GetServiceTypeAndPositionWithPCN(u16PhysicalChIdx, stDtvPgmData.wService_ID, &bServiceType, &wPosition);
            printf("%s...sid %x exist %d type %d %d\n",__FUNCTION__,
                stDtvPgmData.wService_ID,bServiceExist,bServiceType,stDtvPgmData.stCHAttribute.bServiceType);
        #if (ENABLE_DVB_T2)
            plp = msAPI_CM_GetPLP_ID(bServiceType, wPosition);
        #endif
            if((bServiceExist == FALSE)
                || (msAPI_SI_ToSI_Service_Type(bServiceType) != stDtvPgmData.stCHAttribute.bServiceType)
            #if (ENABLE_DVB_T2)
                || plp != stDtvIDTable.u8PLP_ID
            #endif
                )
            {
            #if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
                if(g_enScanType == SCAN_TYPE_UPDATE_MUX && msAPI_SI_IsSpecificCountry(MApp_GetSICountry(OSD_COUNTRY_SETTING),SI_SUPPORT_NETWORK_UPDATE_SPECIFIC_COUNTRY))
                {
                    stDtvPgmData.stPSI_SI_Version.bNITVer=INVALID_VERSION_NUM;
                    if(_bFrequency_change)
                    {
                        stDtvPgmData.stCHAttribute.wSignalStrength = 0x7FFF;
                    }
                    eResult = msAPI_SI_AddProgram(&stDtvIDTable, &stDtvPgmData,&bFull, FALSE);
                }
                else
                {
                    eResult = msAPI_SI_AddProgram(&stDtvIDTable, &stDtvPgmData,&bFull, FALSE);
                }
            #else
                eResult = msAPI_SI_AddProgram(&stDtvIDTable, &stDtvPgmData,&bFull, FALSE);
            #endif
            }
            else
            {
                //if deleted program, then reset all attribute
                if((stDtvPgmData.wLCN == 0) || (stDtvPgmData.wLCN == SI_INVALID_LOGICAL_CHANNEL_NUMBER))
                {
                    stDtvPgmData.stCHAttribute.bValidLCN=FALSE;
                }
                if(msAPI_CM_GetProgramAttribute(bServiceType, wPosition, E_ATTRIBUTE_IS_DELETED) == TRUE)
                {
                    msAPI_CM_ResetAttribute(bServiceType, wPosition);
                }//if moved program, then keep its LCN
                else if(msAPI_CM_GetProgramAttribute(bServiceType, wPosition, E_ATTRIBUTE_IS_MOVED) == TRUE)
                {
                    wLCN = msAPI_CM_GetLogicalChannelNumber(bServiceType, wPosition);//restore back LCN
                    if(wLCN > 0 && wLCN != INVALID_LOGICAL_CHANNEL_NUMBER)
                    {
                        stDtvPgmData.wLCN = wLCN;
                    }
                }
                else
                {
                    wLCN = msAPI_CM_GetLogicalChannelNumber(bServiceType, wPosition);
                    if( stDtvPgmData.wLCN != wLCN)
                    {
                        WORD position=0;//fix coverity 83832
                        if(msAPI_SI_GetServiceByLogicalChannelNumber(msAPI_SI_ToSI_Service_Type(bServiceType),stDtvPgmData.wLCN,&position))
                        {
                            if(msAPI_CM_GetProgramVideoType(bServiceType,position) != msAPI_SI_ToCM_Video_Type(stDtvPgmData.stCHAttribute.eVideoType))
                            {
                                stDtvPgmData.wLCN=wLCN;
                            }
                        }
                    }
                }

                {
                    MEMBER_SI_SERVICETYPE bType;
                    bType=msAPI_SI_ToSI_Service_Type(bServiceType);
                    eResult = msAPI_SI_UpdateProgram(bType, wPosition, (BYTE *)&stDtvPgmData, E_SI_DATA_ALL);
                }
            }

            if(TRUE == eResult)
            {
                if(stDtvPgmData.stCHAttribute.bServiceType == E_TYPE_DTV)
                    u16ScanDtvChNum++;
#if NORDIG_FUNC //for Nordig Spec v2.0
                else if(stDtvPgmData.stCHAttribute.bServiceType == E_TYPE_DATA)
                    u16ScanDataChNum++;
#endif
                else if (stDtvPgmData.stCHAttribute.bServiceType == E_TYPE_RADIO)
                    u16ScanRadioChNum++;
            }
        }
        u8NumOfActiveCh++;
        if(TRUE != eResult)
        {
            #if ENABLE_SCAN_CM_DEBUG
            printf("store channel to DB fail. Result %u, type %u\n",eResult,stDtvPgmData.stCHAttribute.bServiceType);
            #else
            SCAN_DBINFO( printf("store channel to DB fail. Result %u, type %u\n",eResult,stDtvPgmData.stCHAttribute.bServiceType) );
            #endif

            if( bFull)// == E_RESULT_OUTOF_EEPROM )
            {
                *bDBfull = TRUE;
                break;
            }
            continue;
        }
        u8TotalCh++;
    }

    #if ENABLE_SCAN_CM_DEBUG
    printf("RF %u add %u chs!\n\n", u16PhysicalChIdx, u8NumOfActiveCh);
    #endif

    return u8TotalCh;
}
#endif

#if ENABLE_DVBC
void _MApp_DTV_Scan_GetCableScanFlags(_DVBC_SCAN_FLAG * _pOadDVBCScanFlags)
{
    _pOadDVBCScanFlags->bNITScanAvailable = _stDVBCScanFlags.bNITScanAvailable;
    _pOadDVBCScanFlags->bCheckNewFreqfromNIT = _stDVBCScanFlags.bCheckNewFreqfromNIT;
    _pOadDVBCScanFlags->bFrontEndLock = _stDVBCScanFlags.bFrontEndLock;
    _pOadDVBCScanFlags->bInitScanState = _stDVBCScanFlags.bInitScanState;
    _pOadDVBCScanFlags->reserved = _stDVBCScanFlags.reserved;
}
#endif
/*****************************************************************************/

void MApp_Scan_State_Init( void )
{
    enScanState = STATE_SCAN_INIT;
    enDVBScanState = STATE_DVB_SCAN_INIT;
#if ENABLE_DVB
    MApp_Dmx_GetScanTableStateInit();
#endif
}

#if ENABLE_DVB
static void _MApp_DTV_Scan_TableConfig(SCAN_TABLE_CONFIG *pstScanConfig)
{
    if (NULL == pstScanConfig)
        return;
    memset(pstScanConfig, 0, sizeof(SCAN_TABLE_CONFIG));
#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
    if(msAPI_SI_IsSpecificCountry(MApp_GetSICountry(OSD_COUNTRY_SETTING),SI_SUPPORT_NETWORK_UPDATE_SPECIFIC_COUNTRY))
    {
        pstScanConfig->bUpdateMuxOnly = (SCAN_TYPE_UPDATE_MUX == g_enScanType)? TRUE: FALSE;
    }
    else
    {
        pstScanConfig->bUpdateMuxOnly = FALSE;
    }
#else
    pstScanConfig->bUpdateMuxOnly = FALSE;
#endif

#if ENABLE_DVBC
    if (SCAN_TYPE_NETWORK == g_enScanType)
    {
        if (DVBCNetworkIdScanType)
        {
            pstScanConfig->bParseNITOther = FALSE;
            pstScanConfig->bNetworkIDFilterEn = FALSE;
            pstScanConfig->bNetworkID = INVALID_NID ;
            _bQuickInstallProcessed = FALSE;
        }
        else
        {
            pstScanConfig->bParseNITOther = TRUE;
            pstScanConfig->bNetworkIDFilterEn = TRUE;
            pstScanConfig->bNetworkID = MApp_CadtvManualTuning_GetNID();
            // don't execute quick install processing, just check NID match or not in saving program stage
            //_bQuickInstallProcessed = TRUE;
            _bQuickInstallProcessed = FALSE;
        }
    }
    else
    {
        pstScanConfig->bParseNITOther = FALSE;
        pstScanConfig->bNetworkIDFilterEn = FALSE;
        pstScanConfig->bNetworkID = INVALID_NID;
        _bQuickInstallProcessed = FALSE;
    }
#else
        pstScanConfig->bParseNITOther = FALSE;
        pstScanConfig->bNetworkIDFilterEn = FALSE;
        pstScanConfig->bNetworkID = INVALID_NID;
#endif

#if (ENABLE_DVBC && ENABLE_NIT_QUICK_SCAN)
    if(IsDVBCInUse() && ((g_enScanType == SCAN_TYPE_NETWORK) || (g_enScanType == SCAN_TYPE_AUTO)))// && OSD_COUNTRY_SETTING == E_NETHERLANDS)
    {
        _stScanConfig.bEnableNITQuickScan=TRUE;
    }
#endif
#if (ENABLE_S2 && ENABLE_S2_NIT_QUICK_SCAN)
    if(IsS2InUse() && (g_enScanType == S2_SCAN_TYPE_NETWORK)
#if(ASTRA_HD_ENABLE)
    && (GetASTRA_HD_ENABLE() && MApp_Get_IsNITQuickScan())
#endif
    )// && OSD_COUNTRY_SETTING == E_NETHERLANDS)
    {
        pstScanConfig->bParseNITOther = TRUE;
        _stScanConfig.bEnableNITQuickScan=TRUE;
    }
#endif

}
#if(ENABLE_S2)
MS_BOOL _TurnMotor(MS_SAT_PARAM stSatParam,MS_BOOL bForceTune)
{
    MS_BOOL bRet = FALSE;

    _GetSatInforByID(_lnb_satelliteID[_u8CurScanSATPos],&stSatParam);
    if((stSatParam.u8Position&DISEQC12_USALS_POSITION_MASK) > 0)
    {
        if((stSatParam.u8Position&DISEQC12_USALS_POSITION_MASK) != _u8MotorPosition)
        {
            if(bForceTune)
            {
                MApi_DigiTuner_DiSEqC_GoSatPos(stSatParam.u8Position&DISEQC12_USALS_POSITION_MASK);
            }
            bRet = TRUE;
        }
    }
    _u8MotorPosition = stSatParam.u8Position&DISEQC12_USALS_POSITION_MASK;
    return bRet;
}

static MS_BOOL _ChScan_InitFreqTableBySATPos(MS_U8 u8SATPos)
{
    if(g_enScanType != S2_SCAN_TYPE_BLIND)
    {
        MS_U16 wTPPos, wTPIdx,i;
        DTVPROGRAMID_M carrierParam;
        if(_lnb_satelliteID[u8SATPos] < INVALID_SAT_ID)
        {
            u32TPSCount = MApi_DB_DFT_PhysicalChannelBySatID(_lnb_satelliteID[u8SATPos]);
            for(i=0;i<MAX_TPSOFSAT_NUM;i++)
            {
                memset(&_afe_param[i],0x00,sizeof(DTVPROGRAMID_M));
            }
            for(wTPPos=0;wTPPos<u32TPSCount;wTPPos++)
            {
                wTPIdx = MApi_DB_DFT_PositionBySatID2PCHIndex(_lnb_satelliteID[u8SATPos], wTPPos);
                GetIDTable(wTPIdx, (BYTE *)&carrierParam,E_DATA_ID_TABLE);
                _afe_param[wTPPos] = carrierParam;
            }
            _u16AddTPSNum = u32TPSCount;
        }
        else
        {
            return FALSE;
        }
    }
    return TRUE;
}

#if (ENABLE_S2_FAST_SCAN)
typedef struct
{
    U16 Orbital_pos;
    TYPE_SATELLITE SatID;
} ST_SATID_POS;

U8 MApp_GetSatIDForOrbitalPostion(U16 Orbital_pos)
{
    ST_SATID_POS satid[4] =
    {
        {304, KU_130_HOTBIRD_6_7A_8},
        {402, KU_192_ASTRA_1H_1KR_1L_1M},
        {565, KU_235_ASTRA_1E_1G_3A},
        {642, KU_282_ASTRA_2A_2B_2D},
    };

    if(Orbital_pos == satid[0].Orbital_pos)
        return satid[0].SatID;
    else if(Orbital_pos == satid[1].Orbital_pos)
        return satid[1].SatID;
    else if(Orbital_pos == satid[2].Orbital_pos)
        return satid[2].SatID;
    else if(Orbital_pos == satid[3].Orbital_pos)
        return satid[3].SatID;

    return KU_130_HOTBIRD_6_7A_8;
}
#endif

static U8 MApp_S2_Scan_AddOneDTVPchVchs( U16 u16PhysicalChIdx,SI_SHORT_DTV_CHANNEL_INFO *pastVirtualCh,U8 u8NumOfVch,BOOLEAN bCheckServiceInfo ,BOOLEAN *bDBfull)
{
    U8 u8Loop_1;
    U8 u8NumOfActiveCh = 0;
    //      U16 u16VirChInfoIdx = 0;
    BOOLEAN fIsDummyCh;
    BOOLEAN bBackupUsingBuffer;
    BOOLEAN eResult;
    MEMBER_SERVICETYPE bServiceType;
    WORD wPosition,wLCN;
    SI_DTV_CHANNEL_INFO stDtvPgmData;
    SI_DTVPROGRAMID stDtvIDTable;
    U8 au8NetWorkName[MAX_NETWORK_NAME];
    U8 len;

    BOOLEAN bFull=FALSE;
    fIsDummyCh = FALSE;
    bBackupUsingBuffer = FALSE;

    memset(&stDtvIDTable, 0, sizeof(stDtvIDTable));

    MApp_SI_GetDtvPmgData(&pastVirtualCh[0], 0, &stDtvPgmData);
    //if(pastVirtualCh[0].wTransportStream_ID != INVALID_TS_ID )//&& pastVirtualCh[0].wOriginalNetwork_ID != INVALID_ON_ID)
    {
        stDtvIDTable.wNetwork_ID = pastVirtualCh[0].wNetwork_ID;
        stDtvIDTable.wTransportStream_ID = pastVirtualCh[0].wTransportStream_ID;
        stDtvIDTable.wOriginalNetwork_ID = pastVirtualCh[0].wOriginalNetwork_ID;
    #if(ENABLE_S2)
        if(IsS2InUse())
        {
            stDtvIDTable.cRFChannelNumber = 0x88;
        }
        else
    #endif
        {
            stDtvIDTable.cRFChannelNumber = u16PhysicalChIdx;
        }
        msAPI_Tuner_Get_CELL_ID(&stDtvIDTable.wCellID);
    }

#if (ENABLE_S2_FAST_SCAN)
    if(g_enScanType == S2_SCAN_TYPE_FAST)
    {
       if ((TRUE == MApp_SI_Get_M7DVBS_NetWorkName(au8NetWorkName,&len,MAX_NETWORK_NAME)) && (0!=au8NetWorkName[0]))
       {
            msAPI_CM_SetCurrentNetworkName(au8NetWorkName, len);
       }
    }
    else
#endif //#if (ENABLE_S2_FAST_SCAN)
    {
    if ((TRUE == MApp_SI_Get_NetWorkName(au8NetWorkName,&len,MAX_NETWORK_NAME)) && (0!=au8NetWorkName[0]))
    {
        msAPI_CM_SetCurrentNetworkName(au8NetWorkName, len);
    }
    }

    for(u8Loop_1=0; u8Loop_1<u8NumOfVch; u8Loop_1++)
    {
        MApp_SI_GetDtvPmgData(&pastVirtualCh[u8Loop_1], u8Loop_1, &stDtvPgmData);

        if( bCheckServiceInfo == TRUE )
        {
            if( MApp_SI_Action_CheckServiceInfo( &stDtvPgmData ) == FALSE )
            {
                continue;
            }

            if(u8NumOfActiveCh != u8Loop_1)
            {
                memcpy(&pastVirtualCh[u8NumOfActiveCh], &pastVirtualCh[u8Loop_1], sizeof(SI_SHORT_DTV_CHANNEL_INFO));
            }
            pastVirtualCh[u8NumOfActiveCh].stCHAttribute.bServiceType = stDtvPgmData.stCHAttribute.bServiceType;
        }

        if(IsS2InUse())
        {
        #if (ENABLE_S2_FAST_SCAN)
            if(g_enScanType == S2_SCAN_TYPE_FAST)
            {
                stDtvPgmData.satid=MApp_GetSatIDForOrbitalPostion(pastVirtualCh[u8Loop_1].stSatDelSys.u16Orbital_pos);
                stDtvIDTable.SatelliteId =stDtvPgmData.satid;
                stDtvIDTable.u32S2Frequency = pastVirtualCh[u8Loop_1].stSatDelSys.u32CentreFreq/100;
                stDtvIDTable.u16SymbolRate = (U16)(pastVirtualCh[u8Loop_1].stSatDelSys.u32Symbol_rate/10);
                stDtvIDTable.u8Polarity = pastVirtualCh[u8Loop_1].stSatDelSys.u8Polarization;
                stDtvIDTable.wTransportStream_ID = pastVirtualCh[u8Loop_1].wTransportStream_ID;
                stDtvIDTable.wOriginalNetwork_ID = pastVirtualCh[u8Loop_1].wOriginalNetwork_ID;
                stDtvPgmData.stCHAttribute.bIsFastScan = TRUE;
            }
            else
        #endif
            {
                stDtvPgmData.satid=_lnb_satelliteID[_u8CurScanSATPos];
                stDtvIDTable.SatelliteId =_lnb_satelliteID[_u8CurScanSATPos];
                stDtvIDTable.u32S2Frequency = TPSInfo.u32S2Frequency;
                stDtvIDTable.u16SymbolRate = TPSInfo.u16SymbolRate;
                stDtvIDTable.u8Polarity = TPSInfo.u8Polarity;
            #if (ENABLE_S2_FAST_SCAN)
                stDtvPgmData.stCHAttribute.bIsFastScan = FALSE;
            #endif
            }
            printf("\r\n S2 Scan SatelliteId[%d] Freq[%d]",stDtvIDTable.SatelliteId,stDtvIDTable.u32S2Frequency );
        }
        else
        {
            stDtvPgmData.satid=0xff;
            stDtvIDTable.SatelliteId =0xff;
        }
        if( g_enScanType == S2_SCAN_TYPE_AUTO || g_enScanType == S2_SCAN_TYPE_BLIND|| g_enScanType == S2_SCAN_TYPE_NETWORK
        #if(ENABLE_S2_FAST_SCAN)
        || S2_SCAN_TYPE_FAST == g_enScanType
        #endif
        ||S2_SCAN_TYPE_MANUAL== g_enScanType)
        {
            eResult = msAPI_SI_AddProgram(&stDtvIDTable, &stDtvPgmData,&bFull, FALSE);
            if(TRUE == eResult)
            {
                if(stDtvPgmData.stCHAttribute.bServiceType == E_TYPE_DTV)
                {
                    u16ScanDtvChNum++;
                }
            #if NORDIG_FUNC
                else if(stDtvPgmData.stCHAttribute.bServiceType == E_TYPE_DATA)
                {
                    u16ScanDataChNum++;
                }
            #endif
                else if (stDtvPgmData.stCHAttribute.bServiceType == E_TYPE_RADIO)
                {
                    u16ScanRadioChNum++;
                }
            }
        }
        else
        {
            if( TRUE != msAPI_CM_GetServiceTypeAndPositionWithPCN(u16PhysicalChIdx, stDtvPgmData.wService_ID, &bServiceType, &wPosition) )
            {
            #if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
                if(g_enScanType == SCAN_TYPE_UPDATE_MUX)
                {
                    stDtvPgmData.stPSI_SI_Version.bNITVer=INVALID_VERSION_NUM;
                    eResult = msAPI_SI_AddProgram(&stDtvIDTable, &stDtvPgmData,&bFull, FALSE);
                }
                else
                {
                    eResult = msAPI_SI_AddProgram(&stDtvIDTable, &stDtvPgmData,&bFull, FALSE);
                }
            #else
                eResult = msAPI_SI_AddProgram(&stDtvIDTable, &stDtvPgmData,&bFull, FALSE);
            #endif
            }
            else
            {
                //if deleted program, then reset all attribute
                if(msAPI_CM_GetProgramAttribute(bServiceType, wPosition, E_ATTRIBUTE_IS_DELETED) == TRUE)
                {
                    msAPI_CM_ResetAttribute(bServiceType, wPosition);
                }//if moved program, then keep its LCN
                else if(msAPI_CM_GetProgramAttribute(bServiceType, wPosition, E_ATTRIBUTE_IS_MOVED) == TRUE)
                {
                    wLCN = msAPI_CM_GetLogicalChannelNumber(bServiceType, wPosition);//restore back LCN
                    if(wLCN > 0 && wLCN != INVALID_LOGICAL_CHANNEL_NUMBER)
                    {
                        stDtvPgmData.wLCN = wLCN;
                    }
                }

                {
                    MEMBER_SI_SERVICETYPE bType;
                    bType=msAPI_SI_ToSI_Service_Type(bServiceType);
                    eResult = msAPI_SI_UpdateProgram(bType, wPosition, (BYTE *)&stDtvPgmData, E_SI_DATA_ALL);
                }
            }

            if(TRUE == eResult)
            {
                if(stDtvPgmData.stCHAttribute.bServiceType == E_TYPE_DTV)
                {
                    u16ScanDtvChNum++;
                }
            #if NORDIG_FUNC //for Nordig Spec v2.0
                else if(stDtvPgmData.stCHAttribute.bServiceType == E_TYPE_DATA)
                {
                    u16ScanDataChNum++;
                }
            #endif
                else if (stDtvPgmData.stCHAttribute.bServiceType == E_TYPE_RADIO)
                {
                    u16ScanRadioChNum++;
                }
            }
        }

        if(TRUE != eResult)
        {
        #if 1// ENABLE_SCAN_CM_DEBUG
            printf("store channel to DB fail. Result %u, type %u\n",eResult,stDtvPgmData.stCHAttribute.bServiceType);
        #else
            SCAN_DBINFO( printf("store channel to DB fail. Result %u, type %u\n",eResult,stDtvPgmData.stCHAttribute.bServiceType) );
        #endif
            if( bFull)// == E_RESULT_OUTOF_EEPROM )
            {
                *bDBfull = TRUE;
                break;
            }
            continue;
        }
        u8NumOfActiveCh++;
    }
    printf("\n\nRF %u add %u chs!\n\n", u16PhysicalChIdx, u8NumOfActiveCh);
    return u8NumOfActiveCh;
}

static MS_BOOL _ChScan_2TpsIsTheSame(DTVPROGRAMID_M TPInList,DTVPROGRAMID_M NewTP)
{
    MS_U16 u16BandWidth = 0;

    if(TPInList.u8Polarity == NewTP.u8Polarity && TPInList.SatelliteId == NewTP.SatelliteId )
    {
        if(abs(TPInList.u32S2Frequency - NewTP.u32S2Frequency) < 5)
        {
            if(eRollOff == SAT_RO_35)
            {
                u16BandWidth = (MS_U32)TPInList.u16SymbolRate*135/100;
            }
            else if(eRollOff  == SAT_RO_25)
            {
                u16BandWidth = (MS_U32)TPInList.u16SymbolRate*125/100;
            }
            else
            {
                u16BandWidth = (MS_U32)TPInList.u16SymbolRate*120/100;
            }

            if(abs(TPInList.u32S2Frequency - NewTP.u32S2Frequency) <= (u16BandWidth/2))
            {
                return TRUE;
            }
        }
    }
    return FALSE;
}

static MS_BOOL _BlindScan_AddTP2List(DTVPROGRAMID_M TP)
{
    MS_U16 u16Idx= 0 ;

    for(u16Idx = 0;u16Idx<_u16AddTPSNum;u16Idx ++)
    {
        if(_ChScan_2TpsIsTheSame(_afe_param[u16Idx],TP))
        {
            break;
        }
    }
    if(TP.u16SymbolRate >800&&TP.u32S2Frequency>1000)
    {
        if(u16Idx >= _u16AddTPSNum)
        {
            memcpy(&(_afe_param[_u16AddTPSNum]),&TP,sizeof(DTVPROGRAMID_M));
            _u16AddTPSNum ++;
            return TRUE;
        }
        else
        {
            memcpy(&(_afe_param[u16Idx]),&TP,sizeof(DTVPROGRAMID_M));
        }
    }
    return FALSE;
}

BYTE S2_DFT_GetPercentWithPhysicalChannelNumber(MS_U32 value,MS_U32 total)
{
    if(total!=0)
    {
        return (BYTE)(((WORD)value*100)/total);
    }
    else
    {
        return 0;
    }
}

MS_BOOL MApi_ChanScan_NitScan_IsSameNITTP(DTVPROGRAMID_M TP)
{
    return _ChScan_2TpsIsTheSame(_afe_param[0],TP);
}

void MApi_ChanScan_NitScan_ResetTPList(void)
{
    memset(&_afe_param[1],0,sizeof(DTVPROGRAMID_M)*(MAX_TPSOFSAT_NUM-1));
    u32TPSCount = 1;
    _u16AddTPSNum = 1;
}

MS_BOOL MApi_ChanScan_NitScan_AddTP2List(DTVPROGRAMID_M TP)
{
    MS_BOOL bRet = TRUE;
    RemoveProgram_by_TP(TP);
    bRet =  _BlindScan_AddTP2List(TP);
    u32TPSCount = _u16AddTPSNum;
    return bRet;
}
#endif

#if(ENABLE_S2)
#include "mapp_si_util.h"
#include "MApp_TopStateMachine.h"

BOOLEAN msAPI_CM_Test_SetOneProgram(void)
{
    eAutoTune = FE_TUNE_AUTO;
    u32TPSCount = 1;
    _u32Frequency  = 10700;
    _u32NumOfChanScan = 0;
    _u16GetTPSNum = 0;
    _u8SATTotalNum = 1;//MApi_DB_SAT_GetSATCount();
    _u8CurScanSATPos = 0;
    _u16AddTPSNum = u32TPSCount;
    _u8TPBlindScanProgress = 0;
    _u8MotorPosition = 0;
    _lnb_satelliteID[1]=0xFF;
    _u16RFCh  = 0;
#if(ENABLE_S2_CH_CHANGE_TO_SEARCHPOSITION)
    g_u16SearchPosition=0xffff;
#endif
    stGenSetting.stScanMenuSetting.u8ScanType=S2_SCAN_TYPE_MANUAL;
    MApp_TopStateMachine_SetTopState(STATE_TOP_DTV_SCAN);
    g_enScanType = S2_SCAN_TYPE_MANUAL;
    return TRUE;
}
extern BOOLEAN CreatS2ProgramIndexTableAndProgramIDTable(void);
static U8 Blind_Start_Persent=0;
#endif


//[step 0/4]
#if(PATCH_FOR_HW_LIMIT_EXT_SYNC == 1 )
BOOLEAN g_Ext_Sync = TRUE;
U8  u8Change_ExtSync_Count = 0 ;
#endif

#if (ENABLE_S2_FAST_SCAN)
static void _MApp_SetFastScanPercentageNum(void)
{
    if(g_enScanType == S2_SCAN_TYPE_FAST)
    {
        if(u8NumOfVchFound == 0)
        {
            u8ScanPercentageNum = 0;
        }
        else
        {
            u8ScanPercentageNum = uFastScanLoop * 100 / u8NumOfVchFound;
        }
    }
}
#endif

BOOL MApp_CheckChangeBand(void)
{
    if((((msAPI_CM_GetCountry() == E_NORWAY) && ((u8RFCh >= 5 && u8RFCh < 21) || (u8RFCh >69 && u8RFCh <= 120)))||((msAPI_CM_GetCountry() == E_SWEDEN) && (u8RFCh >= 5 && u8RFCh <= 120)))
    && (msAPI_DFT_VHF_CrossBWFreq_GetFinishScanStatus() == FALSE))
    {
        if(msAPI_DFT_GetBandwidth() == E_RF_CH_BAND_7MHz)
        {
            msAPI_DFT_SetBandwidth(E_RF_CH_BAND_8MHz);
            stTPSetting.enBandWidth = E_RF_CH_BAND_8MHz;
        }
        else if(msAPI_DFT_GetBandwidth() == E_RF_CH_BAND_8MHz)
        {
            msAPI_DFT_SetBandwidth(E_RF_CH_BAND_7MHz);
            stTPSetting.enBandWidth = E_RF_CH_BAND_7MHz;
        }
        msAPI_DFT_VHF_CrossBWFreq_SetFinishScanStatus(TRUE);
        return TRUE;
    }
    return FALSE;
}

EN_RET MApp_DTV_Scan( void )
{
    BOOLEAN ScanResult = FE_NOT_LOCK;;
    BOOLEAN fDBFull, bAddService;
    U16 i;
    static U16 u16GetProgramsCnt = 0;
    static U8 u8PhysicalChannelCnt = 0;
    WORD wSignalQualityStrength = 0;
#if (ENABLE_DVBC && ENABLE_NIT_QUICK_SCAN)
    static U16 _u16TSID;
#endif
#if 1//NTV_FUNCTION_ENABLE
    U8 u8NetworkTotal = 0xFF;
#endif
    enDVBScanRetVal =EXIT_NULL;

#if (CHANNEL_SCAN_AUTO_TEST)
    if( ( g_ScanAutoTestData.u2State == 1 ) && ( g_ScanAutoTestData.fCommand == 0 ) )
    {
        enScanState = STATE_SCAN_END;
    }
#endif

    MApp_Scan_ProcessUserInput();

    /*
    //OAD scan test
    {
        #include "MApp_OAD.h"
        extern EN_OAD_SCAN_STATE MApp_OAD_Scan( U8* percentage );
        EN_OAD_SCAN_STATE bstate;
        U8 dummy;
        bstate=MApp_OAD_Scan(&dummy);
        if(bstate == STATE_OAD_SCAN_END)
        {
            return EXIT_GOTO_CHANNELCHANGE;
        }
        return EXIT_NULL;
    }
    */

    switch( enScanState )
    {
        case STATE_SCAN_INIT:
            SCAN_DBINFO( printf("\n ********************* ") );
            SCAN_DBINFO( printf("\n <<<STATE_SCAN_INIT>>> ") );
            SCAN_DBINFO( printf("\n ********************* \n") );

            u8PhysicalChannelCnt=0;
           #if PATCH_FOR_HW_LIMIT_EXT_SYNC
              g_Ext_Sync = TRUE;
           #endif

            msAPI_DFT_VHF_CrossBWFreq_SetFinishScanStatus(FALSE);


        #if ENABLE_SBTVD_DTV_SYSTEM
            if( IS_COUNTRY_USE_SBTVD() )
            {
                msAPI_ATV_SetCurrentAntenna(ANT_AIR);
            }
        #endif

        #if ENABLE_DVB_T2
            MApp_DTV_Scan_T2_InitVariables();
            MApp_DTV_Scan_T2_SetForceMonitorT2Signal(FALSE);
        #endif

            // Init demod/tsp path
        #if ENABLE_DVB_T2
            if( IsDVBTInUse() )
            {
                MAPP_DTV_Scan_T2_DoScan(DVB_T_DEMOD, TRUE);
            }
            else
        #endif
            {
                msAPI_Demod_SetupTSPath(E_DEMOD_TSP_PATH_CASE_NORMAL);
            }

        #if(ENABLE_S2_FAST_SCAN)
        uFastScanLoop = 0;
        #endif

        #if ENABLE_CI //scan needn't pass CI Card
            //msAPI_Tuner_Serial_Control(FALSE,FALSE);
            MApp_CI_Enable_Process(FALSE);
        #endif

            enDVBScanState = STATE_DVB_SCAN_INIT;
          #if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
            if(msAPI_SI_IsSpecificCountry(MApp_GetSICountry(OSD_COUNTRY_SETTING),SI_SUPPORT_NETWORK_UPDATE_SPECIFIC_COUNTRY))
            {
                MApp_SI_Free_NetworkChangeInfo();
                MApp_SI_SetCheckFreqChange(FALSE);
            }
          #endif
            MApp_Dmx_GetScanTableStateInit();

          #if ENABLE_OFFLINE_SIGNAL_DETECTION
            MApp_OffLineInit();
          #endif

          #if ENABLE_FAVORITE_NETWORK
            u32PrevDVB_Frequency = 0;
          #endif
        #if (ENABLE_DTV)
            #if ENABLE_OAD
            if (g_enScanType == SCAN_TYPE_AUTO)
                MApp_OAD_ScanSignalRest();
            #endif
        #endif
            if( MApp_DTV_Scan_Init() == TRUE )
            {
                _MApp_DTV_Scan_TableConfig(&_stScanConfig);

              #if(!DVB_T_C_DIFF_DB)
                DB_PROGRAM_SOURCE_TYPE = UI_INPUT_SOURCE_TYPE;
              #endif

                if (  g_enScanType == SCAN_TYPE_AUTO
                  #if ENABLE_DVBC
                   || g_enScanType == SCAN_TYPE_NETWORK
                  #endif
                  #if(ENABLE_S2)
                    ||S2_SCAN_TYPE_AUTO == g_enScanType
                    ||S2_SCAN_TYPE_BLIND== g_enScanType
                    ||S2_SCAN_TYPE_MANUAL== g_enScanType
                    ||S2_SCAN_TYPE_NETWORK== g_enScanType
                  #if(ENABLE_S2_FAST_SCAN)
                    || S2_SCAN_TYPE_FAST == g_enScanType
                  #endif
                  #endif
                    )
                {
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_AUTOTUNING_PROGRESS);//ZUI: MApp_UiMenu_ExecuteKeyEvent( MIA_ATV_PERCENT ); //draw progress bar
                }
            #if(ENABLE_S2)
                if(S2_SCAN_TYPE_BLIND== g_enScanType )
                {
                    enScanState = STATE_BLIND_START_SET_FIRST_SAT;
                    break;
                }
                else if(S2_SCAN_TYPE_AUTO== g_enScanType||S2_SCAN_TYPE_MANUAL== g_enScanType
            #if(ENABLE_S2_FAST_SCAN)
                || S2_SCAN_TYPE_FAST == g_enScanType
            #endif
                ||S2_SCAN_TYPE_NETWORK== g_enScanType )
                {
                    enScanState = STATE_START;
                    break;
                }
                else
            #endif

                enScanState = STATE_SCAN_SEARCH_RF_CHANNEL;

            #if ENABLE_DVBC
                if(IsDVBCInUse())
                {
                    if (FALSE == _MApp_DTV_Scan_SetCableTPSetting(&_stDVBCScanFlags, &stTPSetting))
                    {
                        enScanState = STATE_SCAN_END;
                    }
                    else
                    {
                        SCAN_DBINFO(printf("\n @@@Freq: %lu ",stTPSetting.u32Frequency));
                        SCAN_DBINFO(printf("\n @@@Symbol rate: %lu ",stTPSetting.u32Symbol_rate));
                        SCAN_DBINFO(printf("\n @@@Modulation: %u ",stTPSetting.u8Modulation));
                        SCAN_DBINFO(printf("\n @@@Bandwidth: %u ",stTPSetting.enBandWidth));
                    }
                }
                else
            #endif
                {
                    SCAN_DBINFO(printf("\n ***u8RFCh = %u", u8RFCh));
                    msAPI_DFT_GetTSSetting( u8RFCh, &stTPSetting );
                }
            }
            else
            {
                enScanState = STATE_SCAN_END;
            }
            break;


        case STATE_SCAN_NEXT_CHANNEL:
            msAPI_DFT_VHF_CrossBWFreq_SetFinishScanStatus(FALSE);
            SCAN_DBINFO( printf( "\n <<<STATE_SCAN_NEXT_CHANNEL>>> " ) );
            u8KeyCode = KEY_NULL;
             // [step 2/4]
          #if PATCH_FOR_HW_LIMIT_EXT_SYNC
            u8Change_ExtSync_Count = 0 ;
            g_Ext_Sync = TRUE;
            MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_DEMOD, FALSE, TRUE, TRUE);
          #endif
            // end
          #if ENABLE_DVB_T2
            MApp_DTV_Scan_T2_InitVariables();
            if( IsDVBTInUse() )
            {
                MAPP_DTV_Scan_T2_DoScan(DVB_T_DEMOD, TRUE);
            }
          #endif

        //#if ENABLE_T_C_COMBO
        #if ENABLE_DVBC
            if (IsDVBCInUse())
            {
                if( g_enScanType == SCAN_TYPE_AUTO || g_enScanType == SCAN_TYPE_NETWORK)
                {
                    if (FALSE == _MApp_DTV_Scan_SetCableTPSetting(&_stDVBCScanFlags, &stTPSetting))
                    {
                        enScanState = STATE_SCAN_END;
                    }
                    else
                    {
                        enScanState = STATE_SCAN_SEARCH_RF_CHANNEL;
                        //1TODO: update progress bar
                        u8RFCh = msAPI_DFT_GetNextPhysicalChannelNumber(u8RFCh);
                        u8ScanPercentageNum = msAPI_DCFT_CalculatePercentTbl();
                        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_AUTOTUNING_PROGRESS);

                        SCAN_DBINFO(printf("\n @u8RFCh: %u ", u8RFCh));
                        SCAN_DBINFO(printf("\n @Freq: %lu ", stTPSetting.u32Frequency));
                        SCAN_DBINFO(printf("\n @Symbol rate: %lu ", stTPSetting.u32Symbol_rate));
                        SCAN_DBINFO(printf("\n @Modulation: %u ", stTPSetting.u8Modulation));
                        SCAN_DBINFO(printf("\n @Bandwidth: %u ", stTPSetting.enBandWidth));
                    }
                }
                else
                {
                    enScanState = STATE_SCAN_END;
                }
            }
            else
        #endif
            {
                u8RFCh = msAPI_DFT_GetNextPhysicalChannelNumber(u8RFCh);
                if( u8RFCh == INVALID_PHYSICAL_CHANNEL_NUMBER/*u8MaxRFCh*/ )
                {
                #if ENABLE_FAVORITE_NETWORK
                    To_Invalid_Physical:
                #endif
                    enScanState = STATE_SCAN_END;
                    break;
                }

                enScanState = STATE_SCAN_SEARCH_RF_CHANNEL;
                msAPI_DFT_GetTSSetting( u8RFCh, &stTPSetting );
                // this case for avoid the overlap channels especial in Norway DVB-T 7MHz alt 8MHz.
            #if ENABLE_FAVORITE_NETWORK
                while((stTPSetting.u32Frequency - u32PrevDVB_Frequency) < 7000L)
                {
                    u8RFCh = msAPI_DFT_GetNextPhysicalChannelNumber(u8RFCh);

                    if( u8RFCh == INVALID_PHYSICAL_CHANNEL_NUMBER/*u8MaxRFCh*/ )
                    {
                        goto To_Invalid_Physical;
                    }

                    msAPI_DFT_GetTSSetting( u8RFCh, &stTPSetting );
                }
            #endif
                if( g_enScanType == SCAN_TYPE_AUTO )
                {
                    u8ScanPercentageNum = msAPI_DFT_GetPercentWithPhysicalChannelNumber(u8RFCh);
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_AUTOTUNING_PROGRESS);
                }
            }
/*
        #elif ENABLE_DVBC
            if( g_enScanType == SCAN_TYPE_AUTO || g_enScanType == SCAN_TYPE_NETWORK)
            {
                if (FALSE == _MApp_DTV_Scan_SetCableTPSetting(&_stDVBCScanFlags, &stTPSetting))
                {
                    enScanState = STATE_SCAN_END;
                }
                else
                {
                    SCAN_DBINFO(printf("@@@@Freq: %lu\n",stTPSetting.u32Frequency));
                    SCAN_DBINFO(printf("@@@@Symbol rate: %lu\n",stTPSetting.u32Symbol_rate));
                    SCAN_DBINFO(printf("@@@@Modulation: %u\n",stTPSetting.u8Modulation));
                    SCAN_DBINFO(printf("@@@@Bandwidth: %u\n",stTPSetting.enBandWidth));
                    enScanState = STATE_SCAN_SEARCH_RF_CHANNEL;
                    //1TODO: update progress bar
                    u8RFCh = msAPI_DFT_GetNextPhysicalChannelNumber(u8RFCh);
                    u8ScanPercentageNum = msAPI_DCFT_CalculatePercentTbl();
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_AUTOTUNING_PROGRESS);
                }
            }
            else
            {
                enScanState = STATE_SCAN_END;
            }
        #else
            u8RFCh = msAPI_DFT_GetNextPhysicalChannelNumber(u8RFCh);
            if( u8RFCh == INVALID_PHYSICAL_CHANNEL_NUMBER )
            {
                enScanState = STATE_SCAN_END;
                break;
            }
            //}

            enScanState = STATE_SCAN_SEARCH_RF_CHANNEL;
            msAPI_DFT_GetTSSetting( u8RFCh, &stTPSetting );
            if( g_enScanType == SCAN_TYPE_AUTO )
            {
                u8ScanPercentageNum = msAPI_DFT_GetPercentWithPhysicalChannelNumber(u8RFCh);
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_AUTOTUNING_PROGRESS);
            }
          #endif
*/
            break;


        case STATE_SCAN_SEARCH_RF_CHANNEL:
            SCAN_DBINFO( printf( "\n [%d]<<<STATE_SCAN_SEARCH_RF_CHANNEL>>> ", __LINE__) );
            //SCAN_ONE_LINE_DBINFO( printf( "+"));
            u8KeyCode = KEY_NULL;
            //wNetworkID = INVALID_ON_ID;

        #if ENABLE_DVBC
            if(IsDVBCInUse())
            {
                DVBC_SCAN_DBINFO( printf( "\n stTPSetting -- F=%d SR= %d  Q= %d ",stTPSetting.u32Frequency,stTPSetting.u32Symbol_rate,stTPSetting.u8Modulation ) );
            }
            else
          #endif
            {
                DVBC_SCAN_DBINFO( printf( "\n u8RFCh is %d ", u8RFCh ) );
                DVBC_SCAN_DBINFO( printf( "\n stTPSetting.u32Frequency: %d ", stTPSetting.u32Frequency ) );
                DVBC_SCAN_DBINFO( printf( "\n stTPSetting.enBandWidth:  %d ", stTPSetting.enBandWidth ) );
            }

            if ( MApp_DVB_Scan( &stTPSetting, &ScanResult ) == FALSE )
            {
                break;
            }

            if( ScanResult == FE_LOCK )
            {
            #if ENABLE_DVB_T2
                if( IsDVBTInUse()//mdev_Cofdm_MSB123X_Ready()
                  &&(DVB_T2_DEMOD == MApp_DTV_Scan_T2_ScanCheckSignal()))
                {
                    _TotalPlpIDNum = mdev_CofdmGetPlpIDList();
                    mdev_CofdmGetCurrentPlpID(&_CurrentPlpID);
                    msAPI_Tuner_SetCurrentTPSetting(_CurrentPlpID);
                }
                else
                {
                    _CurrentPlpID = INVALID_PLPID;
                    memset(u8PlpIDList, INVALID_PLPID, sizeof(u8PlpIDList)/*32*/);
                    msAPI_Tuner_SetCurrentTPSetting(INVALID_PLPID);
                }
            #endif
                enScanState = STATE_SCAN_GET_PROGRAMS;

            #if (CHANNEL_SCAN_AUTO_TEST)
                if( g_ScanAutoTestData.u2State == 1 && u8NumOfVchFound > 0 )
                    g_ScanAutoTestData.u12ChFoundNum++;
            #endif

            #if ENABLE_DVBC
                msAPI_Tuner_UpdateTPSetting();
                if (g_enScanType == SCAN_TYPE_AUTO || g_enScanType == SCAN_TYPE_NETWORK)
                   _stDVBCScanFlags.bFrontEndLock = 1;
            #endif
            }
            else // Not Lock
            {
            #if ENABLE_DVBC
                if (g_enScanType == SCAN_TYPE_AUTO || g_enScanType == SCAN_TYPE_NETWORK)
            #else
                if( g_enScanType == SCAN_TYPE_AUTO )
            #endif
                {
                    if(MApp_CheckChangeBand())
                    {
                        enScanState = STATE_SCAN_SEARCH_RF_CHANNEL;
                    }
                    else
                #if ENABLE_DVB_T2
                    //if(DVB_T2_DEMOD == MApp_DTV_Scan_T2_ScanCheckSignal())
                    if( (DVB_T_DEMOD == MApp_DTV_Scan_T2_ScanCheckSignal())
                      && IsDVBTInUse()
                      )
                    {
                        MAPP_DTV_Scan_T2_DoScan(DVB_T2_DEMOD,TRUE);
                        enScanState = STATE_SCAN_SEARCH_RF_CHANNEL; // Stay in this state
                        msAPI_DFT_VHF_CrossBWFreq_SetFinishScanStatus(FALSE);
                    }
                    else
                #endif
                    {
                        enScanState = STATE_SCAN_NEXT_CHANNEL;
                    }
                }
                else
                {
                    if(g_enScanType == SCAN_TYPE_MANUAL && MApp_CheckChangeBand())
                    {
                        enScanState = STATE_SCAN_SEARCH_RF_CHANNEL;
                    }
                    else
                #if ENABLE_DVB_T2
                    //if( DVB_T2_DEMOD == MApp_DTV_Scan_T2_ScanCheckSignal() )
                    if( (DVB_T_DEMOD == MApp_DTV_Scan_T2_ScanCheckSignal())
                      && IsDVBTInUse()
                      )
                    {
                        MAPP_DTV_Scan_T2_DoScan(DVB_T2_DEMOD,TRUE);
                        enScanState = STATE_SCAN_SEARCH_RF_CHANNEL; // Stay in this state
                        msAPI_DFT_VHF_CrossBWFreq_SetFinishScanStatus(FALSE);
                    }
                    else
                #endif
                    {
                        enScanState = STATE_SCAN_END;
                    }
                }
            }

          #if ENABLE_SCAN_CM_DEBUG
            printf("\n g_enScanType = %u u8RFCh = %u ScanResult = %u ",
                                (U8)g_enScanType, u8RFCh, (U8)ScanResult );
          #endif

          #if 0
            SCAN_DBG( SCAN_DEBUG_CH, printf( "g_enScanType = %bu u8RFCh = %bu ScanResult = %bu\n", ( U8 ) g_enScanType, u8RFCh, ( U8 ) ScanResult ) );
          #else // Modifiedby coverity_0457
            SCAN_DBG( SCAN_DEBUG_CH, printf("\n g_enScanType = %u u8RFCh = %u ScanResult = %u ",
                            (U8)g_enScanType, u8RFCh, (U8)ScanResult ) );
          #endif
            break;

    #if (ENABLE_S2)
        case STATE_BLIND_START_SET_FIRST_SAT:
        {
          #if (SUPPORT_UNICABLE)
            if(_GetSatInforByID( _lnb_satelliteID[_u8CurScanSATPos],&sat_info))
            {
          #else
                _GetSatInforByID( _lnb_satelliteID[_u8CurScanSATPos],&sat_info);
          #endif
              #if (ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
                if(GetASTRA_HD_ENABLE() && (strncmp((char*)sat_info.aSatName,"Ku_ASTRA",8) == 0 || strncmp((char*)sat_info.aSatName,"ASTRA",5) == 0))
                {
                    _u8IsAstraLCNScan = 1;
                }
              #endif
                _enBlindScanStatus = BLINDSCAN_READY;
                enScanState = STATE_BLIND_START;
                _iss2bscancomplete=0;
          #if (SUPPORT_UNICABLE)
            }
          #endif
          }
            break;


        case STATE_BLIND_START:
        {
            MS_U8 u8Status;
            MS_U8 u8Polarity = 0;
            MS_BOOL bHiLoF = FALSE;
            u8Status = _enBlindScanStatus;
            u8Status ++;
            u8Status %= BLINDSCAN_STATUS_NUM;
        #if ( WATCH_DOG == ENABLE )
            MDrv_Sys_DisableWatchDog();
        #endif
            if (sat_info.u16LoLOF == sat_info.u16HiLOF)
            {
                if (u8Status >= BLINDSCAN_H_HiLOF)
                {
                    u8Status = BLINDSCAN_GETTP_FINISH;
                }
            }
            else if(sat_info.u16LoLOF < MAX_C_LOF_FREQ) //c band     L-LOF for H  H-LOF for V
            {
                if ( u8Status == BLINDSCAN_V_LoLOF
                   ||u8Status == BLINDSCAN_H_HiLOF)
                {
                    u8Status = BLINDSCAN_V_HiLOF;
                }
            }
            _enBlindScanStatus = (BLINDSCAN_STATUS)u8Status;

            switch(_enBlindScanStatus)
            {
                case BLINDSCAN_H_LoLOF:
                    u8Polarity = 0;
                    bHiLoF = FALSE;
                    Blind_Start_Persent = 0;
                    break;

                case BLINDSCAN_V_LoLOF:
                    Blind_Start_Persent = 25;
                    u8Polarity = 1;
                    bHiLoF = FALSE;
                    break;

                case BLINDSCAN_H_HiLOF:
                    Blind_Start_Persent = 50;
                    u8Polarity = 0;
                    bHiLoF = TRUE;
                    break;

                case BLINDSCAN_V_HiLOF:
                    Blind_Start_Persent = 75;
                    u8Polarity = 1;
                    bHiLoF = TRUE;
                    break;

                case BLINDSCAN_GETTP_FINISH:
                    Blind_Start_Persent = 100;
                    enScanState =    STATE_BLIND_END;
                    return EXIT_CLOSE;

                default:
                    break;
            }

            if(MApi_DigiTuner_BlindScan_Start(sat_info,u8Polarity,bHiLoF))
            {
                _u16GetTPSNum = 0;
                if(_TurnMotor(sat_info,TRUE))
                {
                    _u32WateTime = MsOS_GetSystemTime();
                    enScanState =  STATE_BLIND_TURNMOTOR;
                }
                else
                {
                    enScanState =  STATE_BLIND_NEXTFREQ;
                }
            }
            else
            {
                enScanState =  STATE_SCAN_END;
            }
        }
        MApp_ZUI_API_ShowWindow(HWND_SAT_SCAN_PROGRESS_INFO_ITEM, SW_SHOW);
        break;


        case STATE_BLIND_TURNMOTOR:
          #if ( WATCH_DOG == ENABLE )
            msAPI_Timer_ResetWDT();
          #endif

            if ((MsOS_GetSystemTime() - _u32WateTime) > (SAT_MOVE_TIME*1000))
            {
                enScanState = STATE_BLIND_NEXTFREQ;
            }
            else
            {
                enScanState = STATE_BLIND_TURNMOTOR;
            }
            break;


        case STATE_BLIND_NEXTFREQ:
        {
            MS_BOOL bBlindScanEnd = 0; // fix coverity 207481
            MS_U8  u8Progress = 0; // fix coverity 207483
            _u8TPBlindScanProgress = 0;

        #if(SUPPORT_UNICABLE)
            if (sat_info.eLNBType == EN_LNBTYPE_UNICABLE)
            {
                MApi_DigiTuner_Uni_SetFreq();
            }
        #endif
            if(MApi_DigiTuner_BlindScan_NextFreq(&bBlindScanEnd,&u8Progress))
            {
                if(bBlindScanEnd)
                {
                    enScanState = STATE_BLIND_START;
                }
                else
                {
                    enScanState = STATE_BLIND_WAITFINISH;
                }
                u8ScanPercentageNum = u8Progress;
                if((u8ScanPercentageNum%3)==0)
                {
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_AUTOTUNING_PROGRESS);
                }
            }
            else
            {
                enScanState = STATE_SCAN_END;
            }
        }
        break;


        case STATE_BLIND_WAITFINISH:
        {
            MS_U8 u8Find = 0;
        #if(SUPPORT_UNICABLE)
            MS_U32 m_u32Frequency;
            if (sat_info.eLNBType== EN_LNBTYPE_UNICABLE)
            {
                MDrv_CofdmDmd_BlindScan_GetCurrentFreq(&m_u32Frequency);
                if ( m_u32Frequency > 2150/*bs_stop_freq*/*10)
                {
                    enScanState = STATE_BLIND_START;
                    break;
                }
            }
        #endif
            if(MApi_DigiTuner_BlindScan_WaitCurFeqFinished(&_u8TPBlindScanProgress,&u8Find))
            {
                if(_u8TPBlindScanProgress == 100)
                {
                    if((u8Find -_u16GetTPSNum)> 0)
                        enScanState = STATE_BLIND_GETTPLIST;
                    else
                        enScanState = STATE_BLIND_NEXTFREQ;
                }
            }
            else
            {
                enScanState = STATE_SCAN_END;
            }
        }
            break;


        case STATE_BLIND_GETTPLIST:
        {
            MS_U16 u16TPNum = MAX_TPSOFSAT,idx=0;
            DTVPROGRAMID_M carrierTPList[MAX_TPSOFSAT];
            printf("\r\nSTATE_BLIND_GETTPLIST");
            memset(carrierTPList, 0, sizeof(carrierTPList));
            if(MApi_DigiTuner_BlindScan_GetChannel(_u16GetTPSNum,&u16TPNum, carrierTPList))
            {
                if(u16TPNum > 0)
                {
                    MS_U8 u8Polarity = 0;
                    MS_U16 u16LOFFreq;
                    MS_SAT_PARAM SATParam;

                                      memset(&SATParam, 0x00, sizeof(MS_SAT_PARAM)); // fix coverity 207482
                    _GetSatInforByID(_lnb_satelliteID[_u8CurScanSATPos],&SATParam);
                    if(_enBlindScanStatus == BLINDSCAN_V_LoLOF || _enBlindScanStatus == BLINDSCAN_V_HiLOF)
                    {
                        u8Polarity = 1;
                    }
                    if(_enBlindScanStatus == BLINDSCAN_V_HiLOF || _enBlindScanStatus == BLINDSCAN_H_HiLOF)
                    {
                        u16LOFFreq = SATParam.u16HiLOF;
                    }
                    else
                    {
                        u16LOFFreq = SATParam.u16LoLOF;
                    }

                    for(idx = 0;idx < u16TPNum;idx ++)
                    {
                        if(u16LOFFreq <MAX_C_LOF_FREQ) //C band
                        {
                            carrierTPList[idx].u32S2Frequency = u16LOFFreq -carrierTPList[idx].u32S2Frequency ;
                        }
                        else
                        {
                            carrierTPList[idx].u32S2Frequency += u16LOFFreq;
                        }
                        carrierTPList[idx].u8Polarity = u8Polarity;
                        carrierTPList[idx].SatelliteId = _lnb_satelliteID[_u8CurScanSATPos];
                        eRollOff = SAT_RO_20;
                        _BlindScan_AddTP2List(carrierTPList[idx]);
                    }
                    _u16GetTPSNum += u16TPNum;
                    u32TPSCount = _u16AddTPSNum;
                    printf("\n u32TPSCount = %d ",u32TPSCount);
                }
                enScanState = STATE_BLIND_NEXTFREQ;
            }
            else
            {
                enScanState = STATE_SCAN_END;
            }
        }
            break;


        case STATE_BLIND_END:
            MApi_DigiTuner_BlindScan_Cancel();
            if(MApi_DigiTuner_BlindScan_End())
            {
                enScanState = STATE_START;
            }
            else
            {
                enScanState = STATE_SCAN_END;
            }
            _iss2bscancomplete=1;
        #if ( WATCH_DOG == ENABLE )
            MDrv_Sys_EnableWatchDog();
        #endif
            break;
        case STATE_START:
        #if ( WATCH_DOG == ENABLE )
            MDrv_Sys_DisableWatchDog();
        #endif
            if(u32TPSCount >0)
            {
                _u32NumOfChanScan = 0;
                u8RFCh=_u32NumOfChanScan;
            #if ENABLE_S2
                if (Test_Dvbs2)
                {
                    Test_Dvbs2 = FALSE;
                    _afe_param[0].SatelliteId = 3;
                    _afe_param[0].u32S2Frequency = 10700;
                    _afe_param[0].u16SymbolRate = 27509;
                    _afe_param[0].u8Polarity = 0;
                    _lnb_satelliteID[_u8CurScanSATPos] = 3;
                }
            #endif
                memcpy((MS_U8*)&TPSInfo,(MS_U8*)&_afe_param[0],sizeof(DTVPROGRAMID_M));
            }
            else if(_lnb_satelliteID[_u8CurScanSATPos]!=INVALID_SAT_ID )
            {
                enScanState = STATE_SETTPS;
                break;
            }
            else
            {
                enScanState = STATE_SCAN_END;
                break;
            }
            _GetSatInforByID(_lnb_satelliteID[_u8CurScanSATPos],&sat_info);
#if (ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
            if(GetASTRA_HD_ENABLE() && (strncmp((char*)sat_info.aSatName,"Ku_ASTRA",8) == 0 || strncmp((char*)sat_info.aSatName,"ASTRA",5) == 0))
            {
                _u8IsAstraLCNScan = 1;
            }
#endif
            MApp_ZUI_API_InvalidateWindow(HWND_SAT_SCAN_PROGRESS_SEARCH_NUM);
            MApp_ZUI_API_InvalidateWindow(HWND_SAT_SCAN_PROGRESS_SAT_NAME);
            if(_TurnMotor(sat_info,TRUE))
            {
                _u32WateTime= MsOS_GetSystemTime();
                enScanState = STATE_TURNMOTOR;
            }
            else
            {
                enScanState = STATE_TUNE2RF;
            }
            break;


        case STATE_TURNMOTOR:
          #if ( WATCH_DOG == ENABLE )
            msAPI_Timer_ResetWDT();
          #endif

            if ((MsOS_GetSystemTime() - _u32WateTime) > (SAT_MOVE_TIME*1000))
            {
                enScanState = STATE_TUNE2RF;
            }
            else
            {
                enScanState = STATE_TURNMOTOR;
            }
            break;


        case STATE_TUNE2RF:
            if (eAutoTune != FE_TUNE_MANUAL &&
            MApi_DigiTuner_Tune2RfCh(sat_info,&TPSInfo,eAutoTune) == FALSE)
            {
                enScanState = STATE_SCAN_END;
                break;
            }
            MApi_DigiTuner_GetMaxLockTime(eAutoTune, &_u32LockTimeMax);
            _u32WateTime= MsOS_GetSystemTime();
            enScanState = STATE_WAITLOCK;
            break;


        case STATE_WAITLOCK:
            if (MApi_DigiTuner_TPSGetLock() == TRUE)
            {
                MS_S16 s16RFOffset = 0;

                //MApi_DigiTuner_GetRFOffset(&s16RFOffset);
                msAPI_Demod_S_Get_RFOffset(&s16RFOffset);
                DEBUG_DEMOD_S( printf("s16RFOffset=%d\n", s16RFOffset); );

                DEBUG_DEMOD_S( printf("1. TPSInfo.u32S2Frequency=%u\n", TPSInfo.u32S2Frequency); );
                // TPSInfo.u32S2Frequency-= s16RFOffset;
                if(sat_info.u16LoLOF < MAX_C_LOF_FREQ) //c band
                {
                    TPSInfo.u32S2Frequency -= s16RFOffset;
                }
                else
                {
                    TPSInfo.u32S2Frequency += s16RFOffset;
                }
                DEBUG_DEMOD_S( printf("2. TPSInfo.u32S2Frequency=%u\n", TPSInfo.u32S2Frequency); );

                if (0 != s16RFOffset)
                {
                    if (FALSE == msAPI_CM_EditS2ProgramIDTableOffset(&TPSInfo, s16RFOffset))
                    {
                        printf("msAPI_CM_EditS2ProgramIDTableOffset is fail\n");
                    }
                }
                enScanState = STATE_SCAN_GET_PROGRAMS;
                //printf("\r\n_________lock");
                break;
            }

            if ((MsOS_GetSystemTime() - _u32WateTime) > _u32LockTimeMax)
            {
                enScanState = STATE_SETTPS;
                break;
            }
            enScanState = STATE_WAITLOCK;
            break;


        case STATE_SETTPS:
            _u32NumOfChanScan++;
            u8RFCh=_u32NumOfChanScan;
            if (_u32NumOfChanScan < u32TPSCount)
            {
                memcpy((MS_U8*)&TPSInfo,(MS_U8*)&_afe_param[_u32NumOfChanScan],sizeof(DTVPROGRAMID_M));
            }
            else
            {
                _u32NumOfChanScan --; // avoid to get invalid number
                _u8CurScanSATPos++;
                if(_lnb_satelliteID[_u8CurScanSATPos] == INVALID_SAT_ID)
                {
                    u8ScanPercentageNum = 100;
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_AUTOTUNING_PROGRESS);
                    MsOS_DelayTask(300);
                    enScanState = STATE_SCAN_END;
                    break;
                }
                if(g_enScanType == S2_SCAN_TYPE_BLIND)
                {
                    _GetSatInforByID(_lnb_satelliteID[_u8CurScanSATPos],&sat_info);
                    for(i=0;i<MAX_TPSOFSAT_NUM;i++)
                    memset(&_afe_param[i],0x00,sizeof(DTVPROGRAMID_M));
                    _u16AddTPSNum = 0;
                    u32TPSCount = 0;
                    enScanState = STATE_BLIND_START;
                    break;
                }
                else if(_ChScan_InitFreqTableBySATPos(_u8CurScanSATPos))
                {
                    _u32NumOfChanScan = 0;
                    enScanState = STATE_START;
                    break;
                }
                else
                {
                    u8ScanPercentageNum =100;
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_AUTOTUNING_PROGRESS);
                    MsOS_DelayTask(300);
                    enScanState = STATE_SCAN_END;
                    break;
                }
            }
            u8ScanPercentageNum = S2_DFT_GetPercentWithPhysicalChannelNumber(_u32NumOfChanScan,u32TPSCount);
            MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_AUTOTUNING_PROGRESS);
            enScanState = STATE_TUNE2RF;
            break;


        case STATE_FIND_NIT_FREQ:
        {
            MS_U16                   u16FreqCnt;
            MS_SAT_PARAMETER           siCDSInfo;
            DTVPROGRAMID_M           carrierParam;
            MS_BOOL _NeedResetTPList = FALSE;
            u16FreqCnt = 1;

                        memset(&carrierParam, 0x00, sizeof(DTVPROGRAMID_M)); // fix coverity 207484
            if(_u16MultiTPNum==0&&_u32NumOfChanScan== 0)
            {
            _NeedResetTPList = TRUE;
            }
            while (u16FreqCnt)
            {
                if(MApp_SI_GetNextSatParameter(&siCDSInfo, &u16FreqCnt, TRUE))
                {
                    carrierParam.u32S2Frequency  = (siCDSInfo.u32CentreFreq)/100;  // 111.11111GHZ --->111111MHZ
                    carrierParam.u16SymbolRate = ((siCDSInfo.u32Symbol_rate&0xfffffff))/10;// 111.1111M --->111111K
                    carrierParam.u8Polarity = siCDSInfo.u8Polarization;
                    carrierParam.SatelliteId = _lnb_satelliteID[_u8CurScanSATPos];
                    printf("--------u16FreqCnt = %d-------",u16FreqCnt);
                    printf("\nFrequecy = %d",carrierParam.u32S2Frequency);
                    printf("\nSymbolRate = %d",carrierParam.u16SymbolRate);
                    printf("\nPolarity = %d",carrierParam.u8Polarity);
                    eRollOff = SAT_RO_20;//(EN_SAT_ROLL_OFF_TYPE)(siCDSInfo.u8RollOff%4);//warn
                    if(_NeedResetTPList &&!MApi_ChanScan_NitScan_IsSameNITTP(carrierParam))
                    {
                        printf("\n -----------TP List Reset-------");
                        _NeedResetTPList = FALSE;
                        MApi_ChanScan_NitScan_ResetTPList();
                    }
                    //MApi_ChanScan_NitScan_AddTP2List(carrierParam);
                }
                else
                {
                    break;
                }
            }
        }
            enScanState = STATE_SETTPS;
            break;
    #endif


        case STATE_SCAN_GET_PROGRAMS:   //Truman for digital only, analog scan shouldn't go into this state
            SCAN_DBINFO( printf( "\n [%d]<<<STATE_SCAN_GET_PROGRAMS>>> ", __LINE__) );
            u8KeyCode = KEY_NULL;
            u8NumOfVchFound = 0;
          #if 0//network test code
            {
                extern BOOLEAN MApp_Dmx_GetAllNetwork(U32 u32TimeOut);
                if(MApp_Dmx_GetAllNetwork(30000)==FALSE)
                {
                    break;
                }
                printf("finish\n");
            }
            {
                MS_NETWORK_NAME_INFO info;
                MS_CABLE_PARAMETER info2;
                U16 dumy;
                while(MApp_SI_GetNextNetoworkInfo(&info))
                {
                    printf("network ID %x name %s\n",info.u16NetworkID,info.au8NetworkName);
                }
                _stScanConfig.bNetworkIDFilterEn=TRUE;
                _stScanConfig.bParseNITOther=TRUE;
                _stScanConfig.bNetworkID=0xa03f;
                MApp_SI_SetNetworkID(_stScanConfig.bNetworkID);

                while(MApp_SI_GetNextCableParameter(&info2,&dumy ))
                {
                    printf("frequency %d\n",info2.u32CentreFreq);
                }
            }
          #endif

        #if(ASTRA_HD_ENABLE)
                  if((!_u8IsAstraLCNScan) || (_u8IsAstraLCNScan && (!MApp_Get_IsNITQuickScan())))
                  {
                        if( MApp_Dmx_GetScanTables(&_stScanConfig, &u8NumOfVchFound ) == FALSE )
                        {
                            u16GetProgramsCnt++;
                            SCAN_DBINFO( printf( "MApp_Dmx_GetScanTables\n" ) );
                            break;
                        }
                  }
                  else if(MApp_Dmx_IsWaitChannelListID())
                  {
                      if(msAPI_CM_GetServiceListIdCount() && (!bisSetChannelListId)&& _u8IsAstraLCNScan)
                      {
                          bisSetChannelListId = TRUE;
                          enPreScanState = enScanState;
                          fEndHalt = FALSE;
                          fReturnToPrevious=FALSE;
                          enScanState = STATE_SCAN_PAUSE;
                          MApp_ZUI_ACT_ExecuteAutoTuningAction(EN_EXE_SET_ASTRA_CHANNEL_ID);
                          break;
                      }
                      MApp_Dmx_WaitChannelListID(FALSE);
                      break;
                  }
                  else if( MApp_Dmx_AstraHD_GetScanTables(&_stScanConfig, &u8NumOfVchFound ) == FALSE )
                  {
                      u16GetProgramsCnt++;
                      SCAN_DBINFO( printf( "MApp_Dmx_AstraHD_GetScanTables\n" ) );
                      break;
                  }
          #elif(ASTRA_LCN_ENABLE)
            if(!_u8IsAstraLCNScan)
            {
                    if( MApp_Dmx_GetScanTables(&_stScanConfig, &u8NumOfVchFound ) == FALSE )
                    {
                        u16GetProgramsCnt++;
                        SCAN_DBINFO( printf( "MApp_Dmx_GetScanTables\n" ) );
                        break;
                    }
             }
            else if( MApp_Dmx_AstraHD_GetScanTables(&_stScanConfig, &u8NumOfVchFound ) == FALSE )
            {
                u16GetProgramsCnt++;
                SCAN_DBINFO( printf( "MApp_Dmx_AstraHD_GetScanTables\n" ) );
                break;
            }
        #elif(ENABLE_S2_FAST_SCAN)
            if(g_enScanType == S2_SCAN_TYPE_FAST)
            {
                MApp_SI_Set_M7DVBS_OpenMonitor(TRUE);
                if(MApp_Dmx_M7_DVBS_FASTSCAN_FST_GetScanTables(&_stScanConfig, &u8NumOfVchFound ) == FALSE)
                {
                    u16GetProgramsCnt++;
                    SCAN_DBINFO( printf( "MApp_Dmx_M7_DVBS_FASTSCAN_FST_GetScanTables\n" ) );
                    break;
                }
            }
            else
            {
                 MApp_SI_Set_M7DVBS_OpenMonitor(FALSE);
                 if(MApp_Dmx_GetScanTables(&_stScanConfig, &u8NumOfVchFound ) == FALSE)
                 {
                      u16GetProgramsCnt++;
                      SCAN_DBINFO( printf( "MApp_Dmx_GetScanTables\n" ) );
                      break;
                 }
            }
        #else
            if( MApp_Dmx_GetScanTables(&_stScanConfig, &u8NumOfVchFound ) == FALSE )
            {
                u16GetProgramsCnt++;
                SCAN_DBINFO( printf( "MApp_Dmx_GetScanTables\n" ) );
                break;
            }
        #endif

            SCAN_ONE_LINE_DBINFO( printf(" u8NumOfVchFound = %u waitcnt=%u ", u8NumOfVchFound, u16GetProgramsCnt);)

            msAPI_Tuner_CheckSignalStrength(&wSignalQualityStrength);
            wSignalQualityStrength = (wSignalQualityStrength&0xFF)<<8;
            wSignalQualityStrength |= (msAPI_Tuner_GetSignalQualityPercentage()&0xFF);
            SCAN_ONE_LINE_DBINFO( printf( " sq= 0x%x \n", wSignalQualityStrength ) );

            u16GetProgramsCnt=0;  // reset for next round
          #if (ENABLE_SCAN_CM_DEBUG | ENABLE_SCAN_ONELINE_MSG)
            {
                U8 j;
                SI_SHORT_DTV_CHANNEL_INFO *pastVirtualCh=(SI_SHORT_DTV_CHANNEL_INFO *)MApp_SI_Get_PastVirtualCh();

                SCAN_DBINFO(printf("\n MApp_DTV_Scan>> u8NumOfPatItem = %u ", u8NumOfVchFound));
                for(j=0; j<u8NumOfVchFound; j++)
                {
                    printf("\n [%02u] Lcn %05u Sid %05u Vpid %05u Apid %05u Vis %u Sel %u data %u stype %u ",\
                        j,pastVirtualCh[j].wLCN,pastVirtualCh[j].wService_ID,\
                        pastVirtualCh[j].wVideo_PID,pastVirtualCh[j].stAudInfo[0].wAudPID,\
                        (U8)pastVirtualCh[j].stCHAttribute.bVisibleServiceFlag,(U8)pastVirtualCh[j].stCHAttribute.bNumericSelectionFlag,\
                        (U8)pastVirtualCh[j].stCHAttribute.bIsDataServiceAvailable,
                        (U8)pastVirtualCh[j].stCHAttribute.bServiceType);
                }

            }
          #endif

            MApp_Dmx_GetScanTableStateInit();

        #if (ENABLE_S2)
            if (IsS2InUse())
            {
                printf("\n u8NumOfVchFound = %d ", u8NumOfVchFound);
                if( u8NumOfVchFound > 0 )
                {

                #if(ENABLE_S2_FAST_SCAN)
                    if(g_enScanType == S2_SCAN_TYPE_FAST)
                    {
                        enScanState = STATE_SCAN_FNT_GET_PROGRAMS;
                    }
                    #elif(ENABLE_S2_NIT_QUICK_SCAN)
                   if(_stScanConfig.bEnableNITQuickScan && _u8IsAstraLCNScan)
                    {
                        enScanState=STATE_S2_SCAN_NIT_QUICK_SCAN_GET_NIT;
                    }
                    else
                #endif //#if(ENABLE_S2_FAST_SCAN)
                    {
                    enScanState = STATE_SCAN_SAVE_PROGRAMS;
                }
                }
                else
                {
                    enScanState = STATE_SETTPS;
                }
            }
            else
        #endif
            {
                if( u8NumOfVchFound > 0 )
                {
                  #if ENABLE_DVBC
                    if(IsDVBCInUse())
                    {
                      #if ENABLE_NIT_QUICK_SCAN
                        if(_stScanConfig.bEnableNITQuickScan)
                        {
                            enScanState=STATE_SCAN_NIT_QUICK_SCAN_GET_NIT;
                            #if ENABLE_GET_SDT_WITHOUT_ORDER
                            u32WaitSDTTime = 0;
                            #endif
                            break;
                        }
                      #endif

                        _MApp_DTV_Scan_SetNITAvailableFlag(TRUE);

                        if (  (g_enScanType == SCAN_TYPE_AUTO)
                           && (!_stDVBCScanFlags.bCheckNewFreqfromNIT) )
                        {
                            _MApp_DTV_Scan_AddNITFreqIntoScanTbl();
                            _stDVBCScanFlags.bCheckNewFreqfromNIT = 1;
                        }
                    }
                  #endif

                    enScanState = STATE_SCAN_SAVE_PROGRAMS;
                }
                else
                {
                    if (  g_enScanType == SCAN_TYPE_AUTO
                      #if ENABLE_DVBC
                       || g_enScanType == SCAN_TYPE_NETWORK
                      #endif
                       )
                    {
                        SCAN_DBG( SCAN_DEBUG_CH, printf("\n Can't get channel infomation ") );
                        //  [step 1/4]
                      #if PATCH_FOR_HW_LIMIT_EXT_SYNC
                        g_Ext_Sync = FALSE ;
                        MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_DEMOD, FALSE, FALSE, TRUE);
                        enScanState = STATE_SCAN_SEARCH_RF_CHANNEL; // repeat search
                        u8Change_ExtSync_Count+=1;
                        if(u8Change_ExtSync_Count >= 2 ) //  repeat 2 times ,go to next
                        {
                            printf("skip current RF search !\n");
                            u8Change_ExtSync_Count = 0 ;
                            enScanState = STATE_SCAN_NEXT_CHANNEL;
                        }
                      #else
                          enScanState = STATE_SCAN_NEXT_CHANNEL;
                      #endif
                        // end
                    }
                    else
                    {
                      #if PATCH_FOR_HW_LIMIT_EXT_SYNC
                        g_Ext_Sync = FALSE ;
                        MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_DEMOD, FALSE, FALSE, TRUE);
                        enScanState = STATE_SCAN_SEARCH_RF_CHANNEL; // repeat search
                        u8Change_ExtSync_Count+=1;
                        if(u8Change_ExtSync_Count >= 2 ) //  repeat 2 times ,go to end
                        {
                            printf("\n skip current RF search ! ");
                            u8Change_ExtSync_Count = 0 ;
                            enScanState = STATE_SCAN_END;
                        }
                      #else
                        enScanState = STATE_SCAN_END;
                      #endif
                    }

                #if (ENABLE_HIERARCHY)
                    if(msAPI_Tuner_Is_HierarchyOn()&&(msAPI_Tuner_Get_HpLp()==0))
                    {
                        stTPSetting.u8HpLp=1;
                        enScanState=STATE_SCAN_SEARCH_RF_CHANNEL;
                        break;

                    }
                #endif

                #if ENABLE_DVB_T2
                    {
                        U8 u8PLP_ID;
                        if(MApp_SI_GetNextT2Parameter(&u8PLP_ID)&& (_TotalPlpIDNum > 1))
                        {
                            stTPSetting.u8PLPID=u8PLP_ID;
                            mdev_CofdmSetPlpGroupID(u8PLP_ID,0);
                            enScanState=STATE_SCAN_SEARCH_RF_CHANNEL;
                        }
                    }
                #endif
                }
            }
            break;


        #if (ENABLE_DVBC && ENABLE_NIT_QUICK_SCAN)
            case STATE_SCAN_NIT_QUICK_SCAN_GET_NIT:
            {
                MS_CABLE_PARAMETER desc;
                if(MApp_SI_GetNextCableParameter(&desc, NULL,NULL,NULL,NULL, FALSE))
                {
                    _u16TSID=desc.u16TSID;
                    enScanState = STATE_SCAN_NIT_QUICK_SCAN_WAIT_SDT;
                    break;
                }
            }
            enScanState = STATE_SCAN_END;
            break;

            case STATE_SCAN_NIT_QUICK_SCAN_WAIT_SDT:
            {
                MS_CABLE_PARAMETER desc;
                U16 u16RemainFreq;
                U16 u16ServiceNumber=0;
                MS_SERVICE_LIST_INFO* pServiceListInfo=NULL;
                MS_SERVICE_LCN_INFO* pLcnInfo=NULL;
                BOOL bGetSDT,bScanByLCNtag= FALSE;

                #if ENABLE_GET_SDT_WITHOUT_ORDER
                BOOL bWaitSDTTimeout =FALSE;
                if(u32WaitSDTTime == 0) u32WaitSDTTime = msAPI_SI_Timer_GetTime();
                if(u32WaitSDTTime + WAIT_SDT_TIMEOUT < msAPI_SI_Timer_GetTime())
                {
                    //printf("ENABLE_GET_SDT_WITHOUT_ORDER  timeout!!!!! \n");
                    bWaitSDTTimeout =TRUE; //hard to wait unused tsid, goto ENABLE_GET_SDT_WITHOUT_ORDER Disable
                    if(_u16TSID == SI_INVALID_TS_ID)
                        enScanState = STATE_SCAN_NIT_QUICK_SCAN_GET_NIT;
                }
                else
                {
                    _u16TSID = GetSDTParsingTSID();
                }
                #endif

                #if ENABLE_ZIGGO
                    bScanByLCNtag = TRUE;
                #endif

                if(MApp_Dmx_GetSDTScanTables(_u16TSID,&bGetSDT, 6000) == FALSE)
                {
                    break;
                }

                if(MApp_SI_GetNextCableParameter(&desc, &pServiceListInfo,&pLcnInfo,&u16ServiceNumber,&u16RemainFreq, TRUE))
                {
                    SI_DTVPROGRAMID stDtvIDTable;
                    SI_DTV_CHANNEL_INFO stDtvPgmData;
                    BOOLEAN bFull=FALSE;
                    memset(&stDtvIDTable, 0, sizeof(stDtvIDTable));
                    stDtvIDTable.wNetwork_ID = desc.u16NetworkID;
                    stDtvIDTable.wTransportStream_ID = desc.u16TSID;
                    stDtvIDTable.wOriginalNetwork_ID = desc.u16ONID;
                    stDtvIDTable.u32Frequency = desc.u32CentreFreq/10;
                    stDtvIDTable.u32SymbRate = desc.u32Symbol_rate/10 ;
                    stDtvIDTable.QamMode = desc.u8Modulation-1;

                    for(i=0;i<u16ServiceNumber;i++)
                    {
                        if(!bScanByLCNtag)
                        {
                            if (pServiceListInfo[i].u16ProgramNumber)
                            {
                                msAPI_SI_FillProgramDataWithDefault(&stDtvPgmData);
                                stDtvPgmData.wService_ID=pServiceListInfo[i].u16ProgramNumber;
                                stDtvPgmData.wTS_LCN=stDtvPgmData.wLCN=pLcnInfo[i].u16LCNNumber;
                                stDtvPgmData.wSimu_LCN=pLcnInfo[i].u16SimuLCNNumber;
                                stDtvPgmData.stCHAttribute.bVisibleServiceFlag=pLcnInfo[i].u8fVisable;
                                stDtvPgmData.stCHAttribute.bNumericSelectionFlag=pLcnInfo[i].u8fSelectable;
                                stDtvPgmData.stCHAttribute.bIsSpecialService=pLcnInfo[i].u8IsSpecialService;
                                stDtvPgmData.stCHAttribute.bServiceTypePrio=msAPI_SI_ToCM_Service_Priority(pServiceListInfo[i].u8ServicePriority);
                                if(pServiceListInfo[i].u8ServiceType == E_TYPE_DTV
                                    || pServiceListInfo[i].u8ServiceType == E_TYPE_RADIO
                                    || pServiceListInfo[i].u8ServiceType == E_TYPE_DATA)
                                {
                                    stDtvPgmData.stCHAttribute.bServiceType=pServiceListInfo[i].u8ServiceType;
                                }
                                else
                                {
                                    stDtvPgmData.stCHAttribute.bServiceType=E_TYPE_DTV;
                                    stDtvPgmData.stCHAttribute.bVisibleServiceFlag=FALSE;
                                    stDtvPgmData.stCHAttribute.bNumericSelectionFlag=FALSE;
                                    stDtvPgmData.stCHAttribute.bInvalidService=TRUE;
                                    stDtvPgmData.stCHAttribute.bIsServiceIdOnly=TRUE;
                                }

                                if(!(bGetSDT && MApp_SI_GetSeviceNameByIndex(stDtvPgmData.bChannelName,SI_MAX_SERVICE_NAME,i)))
                                {
                                    if(pServiceListInfo[i].u8ServiceType == E_TYPE_DATA)snprintf((char*)stDtvPgmData.bChannelName,SI_MAX_SERVICE_NAME,"DATA\0");
                                    else if(pServiceListInfo[i].u8ServiceType == E_TYPE_RADIO)snprintf((char*)stDtvPgmData.bChannelName,SI_MAX_SERVICE_NAME,"RADIO\0");
                                    else snprintf((char*)stDtvPgmData.bChannelName,SI_MAX_SERVICE_NAME,"TV\0");
                                }

                                msAPI_SI_Action_CheckServiceInfo_DVB(&stDtvPgmData);
                                //printf("add service id %x name %s\n",stDtvPgmData.wService_ID, stDtvPgmData.bChannelName);

                                if(msAPI_SI_AddProgram(&stDtvIDTable, &stDtvPgmData,&bFull, TRUE))
                                {
                                    if(!stDtvPgmData.stCHAttribute.bInvalidService)
                                    {
                                        if(pServiceListInfo[i].u8ServiceType == E_TYPE_DTV)u16ScanDtvChNum++;
                                        else if(pServiceListInfo[i].u8ServiceType == E_TYPE_RADIO)u16ScanRadioChNum++;
                                        else u16ScanDataChNum++;
                                    }

                                }
                                else if (bFull)
                                {
                                    break;
                                }
                            }
                        }
                        else
                        {
                            if (pLcnInfo[i].u16ServiceID)
                            {
                                msAPI_SI_FillProgramDataWithDefault(&stDtvPgmData);
                                stDtvPgmData.wService_ID=pLcnInfo[i].u16ServiceID;
                                stDtvPgmData.wTS_LCN=stDtvPgmData.wLCN=pLcnInfo[i].u16LCNNumber;
                                stDtvPgmData.wSimu_LCN=pLcnInfo[i].u16SimuLCNNumber;
                                stDtvPgmData.stCHAttribute.bVisibleServiceFlag=pLcnInfo[i].u8fVisable;
                                stDtvPgmData.stCHAttribute.bNumericSelectionFlag=pLcnInfo[i].u8fSelectable;
                                stDtvPgmData.stCHAttribute.bIsSpecialService=pLcnInfo[i].u8IsSpecialService;
                                stDtvPgmData.stCHAttribute.bServiceTypePrio=msAPI_SI_ToCM_Service_Priority(pServiceListInfo[i].u8ServicePriority);

                                if(pServiceListInfo[i].u8ServiceType == E_TYPE_DTV
                                    || pServiceListInfo[i].u8ServiceType == E_TYPE_RADIO
                                    || pServiceListInfo[i].u8ServiceType == E_TYPE_DATA)
                                {
                                    stDtvPgmData.stCHAttribute.bServiceType=pServiceListInfo[i].u8ServiceType;
                                }

                                if(pServiceListInfo[i].u8ServiceType == E_TYPE_SKIP_SERVICE)
                                {
                                    printf("donot add id %d service type %d \n",pLcnInfo[i].u16LCNNumber,pServiceListInfo[i].u8ServiceType);
                                    continue;
                                }

                                if(!(bGetSDT && MApp_SI_GetSeviceNameByIndex(stDtvPgmData.bChannelName,SI_MAX_SERVICE_NAME,i)))
                                {
                                    if(pServiceListInfo[i].u8ServiceType == E_TYPE_DATA)snprintf((char*)stDtvPgmData.bChannelName,SI_MAX_SERVICE_NAME,"DATA\0");
                                    else if(pServiceListInfo[i].u8ServiceType == E_TYPE_RADIO)snprintf((char*)stDtvPgmData.bChannelName,SI_MAX_SERVICE_NAME,"RADIO\0");
                                    else snprintf((char*)stDtvPgmData.bChannelName,SI_MAX_SERVICE_NAME,"TV\0");
                                    stDtvPgmData.stCHAttribute.bServiceType=E_TYPE_DTV;
                                    stDtvPgmData.stCHAttribute.bVisibleServiceFlag=FALSE;
                                    stDtvPgmData.stCHAttribute.bNumericSelectionFlag=FALSE;
                                    stDtvPgmData.stCHAttribute.bInvalidService=TRUE;
                                    stDtvPgmData.stCHAttribute.bIsServiceIdOnly=TRUE;
                                }
                                else
                                {
                                    if(bGetSDT)
                                    {
                                        if(MApp_SI_GetSeviceNameByIndex(stDtvPgmData.bChannelName, SI_MAX_SERVICE_NAME,i))
                                        {
                                            BYTE bChannelNameTemp[SI_MAX_SERVICE_NAME]={0};
                                            if((memcmp(stDtvPgmData.bChannelName, bChannelNameTemp, SI_MAX_SERVICE_NAME) == 0)&&bGetSDT)
                                            {
                                                continue;
                                            }
                                        }

                                    }
                                }

                                msAPI_SI_Action_CheckServiceInfo_DVB(&stDtvPgmData);
                                //printf("add service id %x name %s\n",stDtvPgmData.wService_ID, stDtvPgmData.bChannelName);

                                if(msAPI_SI_AddProgram(&stDtvIDTable, &stDtvPgmData,&bFull, TRUE))
                                {
                                    if(!stDtvPgmData.stCHAttribute.bInvalidService)
                                    {
                                        if(pServiceListInfo[i].u8ServiceType == E_TYPE_DTV)u16ScanDtvChNum++;
                                        else if(pServiceListInfo[i].u8ServiceType == E_TYPE_RADIO)u16ScanRadioChNum++;
                                        else u16ScanDataChNum++;
                                    }

                                }
                                else if (bFull)
                                {
                                    break;
                                }
                            }
                        }
                    }

                    if(bFull)
                        break;

    /*
                    printf("cable =>freq %d sym %d mod %d ONID %x  NID %x TSID %x\n",desc.u32CentreFreq,desc.u32Symbol_rate,desc.u8Modulation,
                    desc.u16ONID,desc.u16NetworkID,desc.u16TSID);
                    for(i=0;i<u16ServiceNumber;i++)
                    if(pServiceListInfo[i].u16ProgramNumber)
                    printf("service => ID %x type %d lcn %d simu %d visible %d selectable %d special %d\n",
                    pServiceListInfo[i].u16ProgramNumber,
                    pServiceListInfo[i].u8ServiceType,
                    pLcnInfo[i].u16LCNNumber,
                    pLcnInfo[i].u16SimuLCNNumber,
                    pLcnInfo[i].u8fVisable,
                    pLcnInfo[i].u8fSelectable,
                    pLcnInfo[i].u8IsSpecialService
                    );
    */

                    pServiceListInfo=NULL;
                    pLcnInfo=NULL;
                    u16ServiceNumber=0;

                    #if ENABLE_GET_SDT_WITHOUT_ORDER
                    if(!bWaitSDTTimeout)
                    {
                        u32WaitSDTTime = msAPI_SI_Timer_GetTime();
                        ResetSDTParsingParameter(); //The tsid parsed end and change to next.
                    }
                    #endif
                }
                #if ENABLE_GET_SDT_WITHOUT_ORDER
                if((!bWaitSDTTimeout)&&(!u16RemainFreq))
                    enScanState = STATE_SCAN_END;
                else
                #endif
                    enScanState = STATE_SCAN_NIT_QUICK_SCAN_GET_NIT;
            }
            break;
        #endif

    #if(ENABLE_S2_FAST_SCAN)
        case STATE_SCAN_FNT_GET_PROGRAMS:
           if(g_enScanType == S2_SCAN_TYPE_FAST)
           {
                u8NumOfVchFound = 0;
                if(MApp_Dmx_M7_DVBS_FASTSCAN_FNT_GetScanTables(&_stScanConfig, &u8NumOfVchFound) == FALSE)
                {
                    u16GetProgramsCnt++;
                    SCAN_DBINFO(printf("MApp_Dmx_M7_DVBS_FASTSCAN_FNT_GetScanTables\n" ));
                    break;
                }
           }
           enScanState = STATE_SCAN_SAVE_PROGRAMS;
           break;
    #elif(ENABLE_S2_NIT_QUICK_SCAN)
        case STATE_S2_SCAN_NIT_QUICK_SCAN_GET_NIT:
        {
            MS_U16 u16FreqCnt;
            MS_SAT_PARAMETER           siCDSInfo;
            DTVPROGRAMID_M           carrierParam;
            MS_BOOL _NeedResetTPList = FALSE;
            MS_BOOL bRet = TRUE;

            memset(&carrierParam, 0x00, sizeof(DTVPROGRAMID_M)); // fix coverity 207484
            if(_u16MultiTPNum==0&&_u32NumOfChanScan== 0)
            {
                _NeedResetTPList = TRUE;
            }
            if(MApp_SI_GetNextSatParameter(&siCDSInfo, &u16FreqCnt,FALSE))
            {
                carrierParam.u32S2Frequency  = (siCDSInfo.u32CentreFreq)/100;  // 111.11111GHZ --->111111MHZ
                carrierParam.u16SymbolRate = ((siCDSInfo.u32Symbol_rate&0xfffffff))/10;// 111.1111M --->111111K
                carrierParam.u8Polarity = siCDSInfo.u8Polarization;
                carrierParam.SatelliteId = _lnb_satelliteID[_u8CurScanSATPos];
                printf("--------u16FreqCnt = %d-------",u16FreqCnt);
                printf("\nFrequecy = %d",carrierParam.u32S2Frequency);
                printf("\nSymbolRate = %d",carrierParam.u16SymbolRate);
                printf("\nPolarity = %d",carrierParam.u8Polarity);
                eRollOff = SAT_RO_20;//(EN_SAT_ROLL_OFF_TYPE)(siCDSInfo.u8RollOff%4);//warn
                             if(_NeedResetTPList &&!MApi_ChanScan_NitScan_IsSameNITTP(carrierParam))
                {
                    printf("\n -----------TP List Reset-------");
                    _NeedResetTPList = FALSE;
                    MApi_ChanScan_NitScan_ResetTPList();
                }
                //MApi_ChanScan_NitScan_AddTP2List(carrierParam);
                bRet =  _BlindScan_AddTP2List(carrierParam);
                _u32NumOfChanScan++;
                u8RFCh=_u32NumOfChanScan;
                if (_u32NumOfChanScan < u32TPSCount)
                {
                    memcpy((MS_U8*)&TPSInfo,(MS_U8*)&_afe_param[_u32NumOfChanScan],sizeof(DTVPROGRAMID_M));
                }
                enScanState = STATE_S2_SCAN_NIT_QUICK_SCAN_WAIT_SGT;
            }
            else
            {
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_AUTOTUNING_PROGRESS);
                enScanState = STATE_SCAN_END;
                break;
            }
        }
       case STATE_S2_SCAN_NIT_QUICK_SCAN_WAIT_SGT:
       {
            MS_U16 u16ServiceIndex;
            BOOLEAN bFull=FALSE;
            MS_SAT_PARAMETER siCDSInfo;
            MS_SI_SGT_SERVICE_INFO ServiceInfo;
            MS_U16 u16AllSGTServiceNum = msAPI_CM_GetAstraServiceCount();
            SI_DTVPROGRAMID stDtvIDTable;
            SI_DTV_CHANNEL_INFO stDtvPgmData;

            if(MApp_SI_GetNextSatParameter(&siCDSInfo, NULL,TRUE))
            {
                for(u16ServiceIndex = 0;u16ServiceIndex<u16AllSGTServiceNum;u16ServiceIndex++)
                {
                    ServiceInfo = msAPI_CM_GetAstraServiceInfo(u16ServiceIndex);
                    if(siCDSInfo.u16Tsid == ServiceInfo.stTripleIds.u16TsId)
                    {
                        memset(&stDtvIDTable, 0, sizeof(stDtvIDTable));
                        stDtvIDTable.wNetwork_ID = siCDSInfo.u16Nid;
                        stDtvIDTable.wTransportStream_ID = siCDSInfo.u16Tsid;
                        stDtvIDTable.wOriginalNetwork_ID = siCDSInfo.u16Onid;
                        stDtvIDTable.SatelliteId =_lnb_satelliteID[_u8CurScanSATPos];
                        stDtvIDTable.u32S2Frequency = (siCDSInfo.u32CentreFreq)/100;
                        stDtvIDTable.u16SymbolRate = ((siCDSInfo.u32Symbol_rate&0xfffffff))/10;
                        stDtvIDTable.cRFChannelNumber = 0x88;

                        msAPI_SI_FillProgramDataWithDefault(&stDtvPgmData);

                        stDtvPgmData.wService_ID=ServiceInfo.stTripleIds.u16SrvId;
                        stDtvPgmData.wTS_LCN=stDtvPgmData.wLCN=ServiceInfo.u16LCN;
                        stDtvPgmData.stCHAttribute.bVisibleServiceFlag=ServiceInfo.bIsVisble;
                        stDtvPgmData.stCHAttribute.bIsScramble=ServiceInfo.bIsServiceScrambled;
                        stDtvPgmData.wSgt_PID = ServiceInfo.wSgt_PID;
                        stDtvPgmData.stCHAttribute.bServiceTypePrio=ServiceInfo.u8ServiceTypePrio;
                        stDtvPgmData.satid = _lnb_satelliteID[_u8CurScanSATPos];
                        stDtvPgmData.stCHAttribute.bIsFastScan = FALSE;
                        if(ServiceInfo.u8ServiceType == E_TYPE_DTV
                            || ServiceInfo.u8ServiceType == E_TYPE_RADIO
                            || ServiceInfo.u8ServiceType == E_TYPE_DATA)
                        {
                            stDtvPgmData.stCHAttribute.bServiceType=ServiceInfo.u8ServiceType;
                        }
                        else
                        {
                            stDtvPgmData.stCHAttribute.bServiceType=E_TYPE_DTV;
                            stDtvPgmData.stCHAttribute.bVisibleServiceFlag=FALSE;
                            stDtvPgmData.stCHAttribute.bInvalidService=TRUE;
                            stDtvPgmData.stCHAttribute.bIsServiceIdOnly=TRUE;
                        }
                        memcpy(stDtvPgmData.bChannelName,ServiceInfo.au8ServiceName,MAPI_SI_MAX_SERVICE_NAME*sizeof(U8));
                        msAPI_SI_Action_CheckServiceInfo_DVB(&stDtvPgmData);
                        if(msAPI_SI_AddProgram(&stDtvIDTable, &stDtvPgmData,&bFull, TRUE))
                        {
                            if(!stDtvPgmData.stCHAttribute.bInvalidService)
                            {
                                if(ServiceInfo.u8ServiceType == E_TYPE_DTV)u16ScanDtvChNum++;
                                else if(ServiceInfo.u8ServiceType == E_TYPE_RADIO)u16ScanRadioChNum++;
                                else u16ScanDataChNum++;
                            }

                        }
                        else if(bFull)
                        {
                            break;
                        }

                    }
                }
                if(bFull)break;

                    enScanState = STATE_S2_SCAN_NIT_QUICK_SCAN_GET_NIT;
                    break;
                }

            enScanState = STATE_SCAN_END;
            break;
       }
    #endif //#if(ENABLE_S2_FAST_SCAN)
        case STATE_SCAN_SAVE_PROGRAMS:
            SCAN_DBINFO( printf( "\n <<<STATE_SCAN_SAVE_PROGRAMS>>> " ) );
          #if ENABLE_FAVORITE_NETWORK
            u32PrevDVB_Frequency = stTPSetting.u32Frequency;
          #endif
            u8KeyCode = KEY_NULL;
            u8PhysicalChannelCnt++;

            SCAN_DBINFO(printf("\n u8NumOfVchFound = %d ", u8NumOfVchFound));

            bAddService = TRUE;
            msAPI_Tuner_CheckSignalStrength(&wSignalQualityStrength);
            wSignalQualityStrength = (wSignalQualityStrength&0x7F)<<8;
            wSignalQualityStrength |= (msAPI_Tuner_GetSignalQualityPercentage()&0xFF);
            printf( "\n (DTV Scan)wSignalQualityStrength <%X> ", wSignalQualityStrength );

            fDBFull = FALSE;
            if(bAddService)
            {

    #if(ENABLE_S2_FAST_SCAN)
                if(g_enScanType == S2_SCAN_TYPE_FAST)
                {
                    U8 u8NumVch = 0;

                    if(uFastScanLoop < u8NumOfVchFound)
                    {
                        u8NumVch = (U8) MApp_Dmx_M7_DVBS_FASTSCAN_FNT_Parse_Table(uFastScanLoop);
                        SI_SHORT_DTV_CHANNEL_INFO *pastVirtualCh=MApp_SI_Get_PastVirtualCh();

                        if ( IS_BESTMUX_COUNTRY(OSD_COUNTRY_SETTING) && g_enScanType == SCAN_TYPE_MANUAL)//don't care quality, must replace the same service
                        {
                            wSignalQualityStrength = 0x7FFF;
                        }

                        for(i = 0; i < u8NumVch; i++)
                        {
                            pastVirtualCh[i].stCHAttribute.wSignalStrength = wSignalQualityStrength;
                        }

                      u16NumOfSrvAdd += MApp_S2_Scan_AddOneDTVPchVchs(u8RFCh, pastVirtualCh, u8NumVch, TRUE, &fDBFull);
                      uFastScanLoop++;
                    }
                }
               else
    #endif  //#if(ENABLE_S2_FAST_SCAN)
               {
                SI_SHORT_DTV_CHANNEL_INFO *pastVirtualCh=MApp_SI_Get_PastVirtualCh();
                if ( IS_BESTMUX_COUNTRY(OSD_COUNTRY_SETTING) && g_enScanType == SCAN_TYPE_MANUAL)//don't care quality, must replace the same service
                {
                    wSignalQualityStrength = 0x7FFF;
                }

                for(i = 0;i < u8NumOfVchFound ;i++)
                {
                    pastVirtualCh[i].stCHAttribute.wSignalStrength = wSignalQualityStrength;
                }

            #if(ENABLE_S2)
                if(IsS2InUse())
                {
                    u16NumOfSrvAdd += MApp_S2_Scan_AddOneDTVPchVchs(u8RFCh, pastVirtualCh, u8NumOfVchFound, TRUE, &fDBFull);
                }
                else
            #endif
                {
                    u16NumOfSrvAdd += MApp_Scan_AddOneDTVPchVchs(u8RFCh, pastVirtualCh, u8NumOfVchFound, TRUE, &fDBFull);
                }
                //it will cause remove normal service: ex: 1~5 invalid,6~0 valid service
                //if (SCAN_TYPE_MANUAL == g_enScanType)
                  //  u8NumOfVchFound = (U8)u16NumOfSrvAdd;
                }
            #if ENABLE_SKIP_ATV_PROGRAMS_SAME_TO_DTV_LCN
                U16 u16Ordinal;
                U16 u16Number;
                for (u16Ordinal = 0; u16Ordinal <= msAPI_ATV_GetActiveProgramCount(); u16Ordinal++)
                {
                    msAPI_CHPROC_CM_GetAttributeOfOrdinal(E_SERVICETYPE_ATV, u16Ordinal, (BYTE*)&u16Number, E_SERVICE_ATTR_NUMBER, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                    if ((u16Number + 1) == pastVirtualCh->stLCN.bPhysicalChannel)
                    {
                        msAPI_ATV_SkipProgram(u16Number, TRUE);
                        break;
                    }
                }
            #endif

            #if ENABLE_SCAN_CM_DEBUG
                SCAN_DBINFO(printf("\n Total u16NumOfSrvAdd: %u ", u16NumOfSrvAdd));
                SCAN_DBINFO(printf("\n u16ScanDtvChNum:      %u ", u16ScanDtvChNum));
                SCAN_DBINFO(printf("\n u16ScanRadioChNum:    %u ", u16ScanRadioChNum));
              #if NORDIG_FUNC //for Nordig Spec v2.0
                SCAN_DBINFO(printf("\n u16ScanDataChNum:     %u ", u16ScanDataChNum));
              #endif
            #endif
            }

        #if(ENABLE_S2)
            if(IsS2InUse())
            {
                if( g_enScanType == S2_SCAN_TYPE_NETWORK )
                {
                    enScanState = STATE_FIND_NIT_FREQ;
                }
                else
                {
            #if(ENABLE_S2_FAST_SCAN)
                   if(g_enScanType == S2_SCAN_TYPE_FAST)
                   {
                       if(uFastScanLoop < u8NumOfVchFound)
                       {
                            enScanState = STATE_SCAN_SAVE_PROGRAMS;
                            _MApp_SetFastScanPercentageNum();
                            MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_AUTOTUNING_PROGRESS);
                       }
                       else
                       {
                           MApp_Dmx_GetScanTableStateInit();
                           uFastScanLoop = 0;
                           enScanState = STATE_SCAN_PAT_PMT_GET_PROGRAMS;
                       }
                   }
                   else
                   {
                    enScanState = STATE_SETTPS;
                }
            #else
                   enScanState = STATE_SETTPS;
            #endif
                }
            }
            else
        #endif
            {
        #if PLAYCARD_DISABLE // if you want use play card turn off this

              #if ENABLE_DVBC
                if( (g_enScanType == SCAN_TYPE_AUTO || g_enScanType == SCAN_TYPE_NETWORK) && !fDBFull)
              #else
                if( g_enScanType == SCAN_TYPE_AUTO && !fDBFull)
              #endif
                {
                  #if ENABLE_DVB_T2
                    U8 u8PLP_ID;
                    if(MApp_SI_GetNextT2Parameter(&u8PLP_ID)&& (_TotalPlpIDNum > 1))
                    {
                        stTPSetting.u8PLPID=u8PLP_ID;
                        mdev_CofdmSetPlpGroupID(u8PLP_ID,0);
                        enScanState=STATE_SCAN_SEARCH_RF_CHANNEL;
                    }
                    else
                  #endif
                    {
                        enScanState = STATE_SCAN_NEXT_CHANNEL;
                    }
                }
                else
                {
                    //u8ScanDtvChNum = msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY);;
                    //u8ScanRadioChNum = msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY);;
                #if ENABLE_DVB_T2
                    U8 u8PLP_ID;
                    if(MApp_SI_GetNextT2Parameter(&u8PLP_ID)&& (_TotalPlpIDNum > 1))
                    {
                        stTPSetting.u8PLPID=u8PLP_ID;
                        mdev_CofdmSetPlpGroupID(u8PLP_ID,0);
                        enScanState=STATE_SCAN_SEARCH_RF_CHANNEL;
                    }
                    else
                #endif
                    {
                        enScanState = STATE_SCAN_END;
                    }
                }

        #else // PLAYCARD_DISABLE

                u16ScanDtvChNum = msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                u16ScanRadioChNum = msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
            #if NORDIG_FUNC //for Nordig Spec v2.0
                u16ScanDataChNum = msAPI_CM_CountProgram(E_SERVICETYPE_DATA, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
            #endif
                enScanState = STATE_SCAN_END;

        #endif // PLAYCARD_DISABLE

            }

        #if ENABLE_DVB_T2
            if(SCAN_TYPE_MANUAL == g_enScanType)
            {
                msAPI_CM_DVBT2_RemoveMux(u8RFCh,u8PlpIDList,_TotalPlpIDNum);
            }
        #endif

        #if 0//(ENABLE_DVB_T2||ENABLE_HIERARCHY)
            if (SCAN_TYPE_MANUAL == g_enScanType)
            {
                SI_SHORT_DTV_CHANNEL_INFO *pastVirtualCh = MApp_SI_Get_PastVirtualCh();
                WORD *au16ServiceIDs=NULL;//[MAX_VC_PER_PHYSICAL];
                MEMBER_SERVICETYPE *aeServiceType=NULL;//[MAX_VC_PER_PHYSICAL];
                U8   j,u8RemovedChnNum,u8PLP_ID;
                U8 u8ServiceCount=MApp_SI_GetScanNumOfPatItem();
                au16ServiceIDs=(WORD*)msAPI_Memory_Allocate(sizeof(WORD)*MAX_VC_PER_PHYSICAL,(EN_BUFFER_ID)0);
                aeServiceType=(MEMBER_SERVICETYPE*)msAPI_Memory_Allocate(sizeof(MEMBER_SERVICETYPE)*MAX_VC_PER_PHYSICAL,(EN_BUFFER_ID)0);
                if(au16ServiceIDs && aeServiceType)
                {
                    for( j = 0; j< u8ServiceCount; j++)
                    {
                        au16ServiceIDs[j] = pastVirtualCh[j].wService_ID;
                        switch(pastVirtualCh[j].stCHAttribute.bServiceType)
                        {
                            case E_TYPE_RADIO:
                                aeServiceType[j] =E_SERVICETYPE_RADIO;
                                break;
                            case E_TYPE_DATA:
                                aeServiceType[j] =E_SERVICETYPE_DATA;
                                break;
                            default:
                            case E_TYPE_DTV:
                                aeServiceType[j] =E_SERVICETYPE_DTV;
                                break;
                        }
                        //aeServiceType[i] = (MEMBER_SERVICETYPE) pastVirtualCh[i].stCHAttribute.bServiceType;
                    }
                    msAPI_Tuner_Get_PLP_ID(&u8PLP_ID);

                    u8RemovedChnNum = msAPI_CM_RemoveMismatchedProgram(u8RFCh,  pastVirtualCh[0].wTransportStream_ID ,u8PLP_ID ,msAPI_Tuner_Get_HpLp(), au16ServiceIDs, aeServiceType, u8ServiceCount,0xff,0xffff);

                }
                else
                {
                    ASSERT(0);
                }
                if(au16ServiceIDs)msAPI_Memory_Free(au16ServiceIDs,(EN_BUFFER_ID)0);
                if(aeServiceType)msAPI_Memory_Free(aeServiceType,(EN_BUFFER_ID)0);
                //printf("SCAN_TYPE_MANUAL>> u8RemovedChnNum = %bu\n", u8RemovedChnNum);
            }

          #if (ENABLE_HIERARCHY)
            if(msAPI_Tuner_Is_HierarchyOn()&&(msAPI_Tuner_Get_HpLp()==0))
            {

                stTPSetting.u8HpLp=1;
                enScanState=STATE_SCAN_SEARCH_RF_CHANNEL;
                break;
            }
          #endif
            {
                U8 u8PLP_ID;
                if(MApp_SI_GetNextT2Parameter(&u8PLP_ID)&& (_TotalPlpIDNum > 1))
                {
                    stTPSetting.u8PLPID=u8PLP_ID;
                    mdev_CofdmSetPlpGroupID(u8PLP_ID,0);
                    enScanState=STATE_SCAN_SEARCH_RF_CHANNEL;
                }
            }
        #endif
            break;


#if(ENABLE_S2_FAST_SCAN)
        case STATE_SCAN_PAT_PMT_GET_PROGRAMS:
        {
            u8NumOfVchFound = 0;

            if(g_enScanType == S2_SCAN_TYPE_FAST)
            {
                if(MApp_Dmx_M7_DVBS_FASTSCAN_PAT_PMT_GetScanTables(&_stScanConfig, &u8NumOfVchFound) == FALSE)
                {
                    u16GetProgramsCnt++;
                    SCAN_DBINFO( printf( "MApp_Dmx_M7_DVBS_FASTSCAN_FST_GetScanTables\n" ) );
                    break;
                }
            }

            if(u8NumOfVchFound > 0)
            {
                 enScanState = STATE_SETTPS;
            }
            else
            {
                printf("**[%s,%s,%d]****MApp_Dmx_M7_DVBS_FASTSCAN_FST_GetScanTables Error*****u8NumOfVchFound = %d****PAT or PMT  Servic ID Not Match FNT and FST**********\n",__FILE__,__FUNCTION__,__LINE__,u8NumOfVchFound);
            }
        }
        break;
 #endif // #if(ENABLE_S2_FAST_SCAN)
        case STATE_SCAN_PAUSE:
            SCAN_DBINFO( printf("\n <<<STATE_SCAN_PAUSE>>> ") );
            if(fEndHalt)
            {
                SCAN_DBINFO( printf("\n End Halt>>") );
                if(fReturnToPrevious)
                {
                    SCAN_DBINFO( printf("\n Return to previous state>> ") );
                    SCAN_DBINFO( printf("\n Previous state=0x%x ", enPreScanState) );
                    enScanState=enPreScanState;
                }
                else
                {
                    SCAN_DBINFO( printf("\n Go to end>>") );
                    enScanState=STATE_SCAN_END;
                }
                fEndHalt=FALSE;
            }
            else
            {
                SCAN_DBINFO( printf("\n Start halt>> ") );
            }
            break;


        case STATE_SCAN_END:
        case STATE_SCAN_EXIT_MAIN_MENU:
            SCAN_DBINFO( printf("\n <<<%s>>> ", ((enScanState == STATE_SCAN_END)?("STATE_SCAN_END"):("STATE_SCAN_EXIT_MAIN_MENU"))) );
          #if PATCH_FOR_HW_LIMIT_EXT_SYNC
            g_Ext_Sync = TRUE;
            MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_DEMOD, FALSE, TRUE, TRUE);
          #endif

          #if(ENABLE_S2)   // MTC_AD_FIX
            if(stGenSetting.stScanMenuSetting.u8ScanType == S2_SCAN_TYPE_BLIND)
            {
                if(_iss2bscancomplete==0)
                {
                    MApi_DigiTuner_BlindScan_Cancel();
                    MApi_DigiTuner_BlindScan_End();
                }
            }
          #endif

            SCAN_DBINFO(printf("\n ## u16ScanDtvChNum:      %u",u16ScanDtvChNum));
            SCAN_DBINFO(printf("\n ## u16ScanRadioChNum:    %u",u16ScanRadioChNum));
            SCAN_DBINFO(printf("\n ## u8PhysicalChannelCnt: %d ", u8PhysicalChannelCnt));
          #if NORDIG_FUNC //for Nordig Spec v2.0
            SCAN_DBINFO(printf("\n ## u16ScanDataChNum:     %u",u16ScanDataChNum));
          #endif

          #if ENABLE_DVB_T2
            MApp_DTV_Scan_T2_InitVariables();
            MApp_DTV_Scan_T2_EnterSignalMonitorStatus(FALSE);
          #endif

          #if ENABLE_CI
            MApp_CI_Enable_Process(TRUE);
          #endif

        #if NTV_FUNCTION_ENABLE
            if (  (msAPI_CM_GetCountry() == E_NORWAY)
              #if ENABLE_FAVORITE_NETWORK
               && !g_bSetFavoriteNetwork
              #endif
               && ((g_enScanType == SCAN_TYPE_AUTO)||(g_enScanType == SCAN_TYPE_MANUAL))
               )
            {
                U8 k,u8NetworkNorwegianCount;

                u8NetworkNorwegianCount = 0;
              #if ENABLE_FAVORITE_NETWORK
                g_u8NetworkIndex = 0xFF;
              #endif

                for(k=0;k<MAX_NETWOEK_NUMBER;k++)
                {
                    if(msAPI_CM_IS_NorwegianNetwork(k))
                    {
                        u8NetworkTotal = k+1;
                        u8NetworkNorwegianCount++;
                      #if ENABLE_FAVORITE_NETWORK
                        if (g_u8NetworkIndex == 0xFF)
                            g_u8NetworkIndex = k;
                      #endif
                    }
                }

                if (u8NetworkNorwegianCount!=0)
                {
                    u8NetworkTotal = u8NetworkNorwegianCount;
                }

                if (u8NetworkTotal == 1)
                {
                    msAPI_CM_Set_FavoriteNetwork(0);
                }

            #if ENABLE_FAVORITE_NETWORK
                g_u8NetworkTotal = 0;

                if (u8NetworkTotal != 0xFF)
                   g_u8NetworkTotal = u8NetworkTotal;
            #endif
            }
        #endif // #if NTV_FUNCTION_ENABLE

            MApp_DTV_Scan_End((g_enScanType == SCAN_TYPE_AUTO && u8NetworkTotal!=0xFF && u8NetworkTotal > 1) ? TRUE : FALSE);

            SCAN_DBINFO( printf( "MENU_CHANNEL_DTV_ManualScan>>\n" ) );

            if (  g_enScanType == SCAN_TYPE_AUTO
              #if ENABLE_DVBC
               || g_enScanType == SCAN_TYPE_NETWORK
              #endif
              #if ENABLE_S2
               || g_enScanType == S2_SCAN_TYPE_AUTO
               || g_enScanType == S2_SCAN_TYPE_BLIND
               || g_enScanType == S2_SCAN_TYPE_MANUAL
               || g_enScanType == S2_SCAN_TYPE_NETWORK
               #if(ENABLE_S2_FAST_SCAN)
               || S2_SCAN_TYPE_FAST == g_enScanType
               #endif
              #endif
               )
            {
            #if ENABLE_SBTVD_SCAN
                if(IsISDBTInUse())
                {
                    if ( enScanState == STATE_SCAN_END )
                    {
                        enDVBScanRetVal = EXIT_GOTO_ATVSCAN;
                    }
                    else if(enScanState == STATE_SCAN_EXIT_MAIN_MENU)  //20100608EL
                    {
                        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_AUTO_SCAN_FINISH);

                        if(u16ScanDtvChNum==0)
                        {
                            if ( u8ScanAtvChNum > 0)
                            {
                                if ( UI_INPUT_SOURCE_TYPE != UI_INPUT_SOURCE_ATV)
                                {
                                    //PIP behavior: If PIP is enabled, close sub window and turn on ATV in the main window.
                                #if (ENABLE_PIP)
                                    if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
                                    {
                                        BOOLEAN bResetSrc = FALSE;

                                        if (  IsSrcTypeScart(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))
                                           || IsSrcTypeAV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))
                                           || IsSrcTypeSV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) )
                                        {
                                            bResetSrc = TRUE;
                                        }

                                        if(stGenSetting.g_stPipSetting.enPipSoundSrc==EN_PIP_SOUND_SRC_SUB)
                                        {
                                            stGenSetting.g_stPipSetting.enPipSoundSrc=EN_PIP_SOUND_SRC_MAIN;
                                            MApp_InputSource_PIP_ChangeAudioSource(MAIN_WINDOW);
                                        }

                                        E_UI_INPUT_SOURCE ePreSrc = UI_SUB_INPUT_SOURCE_TYPE;
                                        UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_NONE;
                                        MApp_InputSource_ChangeInputSource(SUB_WINDOW);
                                        UI_SUB_INPUT_SOURCE_TYPE = ePreSrc;
                                        stGenSetting.g_stPipSetting.enPipMode = EN_PIP_MODE_OFF;
                                        if(bResetSrc)
                                        {//Set sub window source type to 1st compatible src with the main window.
                                            UI_SUB_INPUT_SOURCE_TYPE = MApp_InputSource_GetUIInputSourceType(MApp_InputSource_PIP_Get1stCompatibleSrc(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)));
                                        }
                                    }
                                #endif // #if (ENABLE_PIP)

                                    UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ATV;
                                    MApp_InputSource_SwitchSource( UI_INPUT_SOURCE_TYPE, MAIN_WINDOW );

                                    msAPI_ATV_SetCurrentProgramNumber(msAPI_ATV_GetFirstProgramNumber(FALSE));
                                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE_DURING_LIMITED_TIME, DELAY_FOR_STABLE_SIF, E_AUDIOMUTESOURCE_ATV);

                                    //BY 20090406 msAPI_VD_AdjustVideoFactor(E_ADJUST_VIDEOMUTE_DURING_LIMITED_TIME, DELAY_FOR_STABLE_TUNER);
                                    msAPI_AVD_TurnOffAutoAV();
                                    msAPI_Tuner_ChangeProgram();
                                    //msAPI_VD_ClearSyncCheckCounter();
                                    msAPI_AVD_ClearAspectRatio();
                                    enDVBScanRetVal = EXIT_GOTO_TV;
                                }
                            }
                            else
                            {
                                enDVBScanRetVal = EXIT_GOTO_PREVIOUS;
                            }
                            enScanState = STATE_SCAN_INIT;
                        }
                        else
                        {
                            enScanState = STATE_SCAN_INIT;
                            enDVBScanRetVal = EXIT_GOTO_TV;
                        }
                        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_INTERNAL_2_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                    }
                }
                else
            #endif  //ENABLE_SBTVD_SCAN
                {
                  #if (ENABLE_TARGET_REGION || ENABLE_LCN_CONFLICT)
                    if (enScanState == STATE_SCAN_PAUSE /*&& bSetTargetRegion == TRUE*/)
                    {
                        return enDVBScanRetVal;
                    }
                  #endif

                #if ENABLE_S2
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_AUTOTUNING_PROGRESS);
                    MApp_ZUI_MainTask();
                    msAPI_Timer_Delayms(1500);
                #endif

                    if( enScanState == STATE_SCAN_END)
                    {
                    #if(ENABLE_S2)
                        Dvbs2_Default_Scan = 1;
                    #endif

                        SCAN_DBINFO( printf( "MIA_FINISH_SCAN>>\n" ) );
                        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_AUTO_SCAN_FINISH);
                        SCAN_DBINFO( printf( "u16NumOfSrvAdd = %u\n", u16NumOfSrvAdd ) );
                    }

                #if(ENABLE_S2)
                    if(IsS2InUse())
                    {
                        enScanState = STATE_SCAN_INIT;
                        enDVBScanRetVal = EXIT_GOTO_TV;
                        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_INTERNAL_2_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                    #if ( WATCH_DOG == ENABLE )
                        MDrv_Sys_EnableWatchDog();
                    #endif
                    }
                    else
                #endif
                    {
                        if(u16ScanDtvChNum==0)
                        {
                            if ( u8ScanAtvChNum > 0)
                            {
                                if ( UI_INPUT_SOURCE_TYPE != UI_INPUT_SOURCE_ATV)
                                {
                                    //PIP behavior: If PIP is enabled, close sub window and turn on ATV in the main window.
                                #if (ENABLE_PIP)
                                    if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
                                    {
                                        BOOLEAN bResetSrc = FALSE;

                                        if (  IsSrcTypeScart(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))
                                           || IsSrcTypeAV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))
                                           || IsSrcTypeSV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
                                        {
                                            bResetSrc = TRUE;
                                        }

                                        if(stGenSetting.g_stPipSetting.enPipSoundSrc==EN_PIP_SOUND_SRC_SUB)
                                        {
                                            stGenSetting.g_stPipSetting.enPipSoundSrc=EN_PIP_SOUND_SRC_MAIN;
                                            MApp_InputSource_PIP_ChangeAudioSource(MAIN_WINDOW);
                                        }
                                        E_UI_INPUT_SOURCE ePreSrc = UI_SUB_INPUT_SOURCE_TYPE;
                                        UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_NONE;
                                        MApp_InputSource_ChangeInputSource(SUB_WINDOW);
                                        UI_SUB_INPUT_SOURCE_TYPE = ePreSrc;
                                        stGenSetting.g_stPipSetting.enPipMode = EN_PIP_MODE_OFF;
                                        if(bResetSrc)
                                        {//Set sub window source type to 1st compatible src with the main window.
                                            UI_SUB_INPUT_SOURCE_TYPE = MApp_InputSource_GetUIInputSourceType(MApp_InputSource_PIP_Get1stCompatibleSrc(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)));
                                        }
                                    }
                                #endif // #if (ENABLE_PIP)

                                    UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ATV;
                                    MApp_InputSource_SwitchSource( UI_INPUT_SOURCE_TYPE, MAIN_WINDOW );

                                    msAPI_ATV_SetCurrentProgramNumber(msAPI_ATV_GetFirstProgramNumber(FALSE));
                                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE_DURING_LIMITED_TIME, DELAY_FOR_STABLE_SIF, E_AUDIOMUTESOURCE_ATV);
                                    //BY 20090406 msAPI_VD_AdjustVideoFactor(E_ADJUST_VIDEOMUTE_DURING_LIMITED_TIME, DELAY_FOR_STABLE_TUNER);
                                    msAPI_AVD_TurnOffAutoAV();
                                    msAPI_Tuner_ChangeProgram();
                                    //msAPI_VD_ClearSyncCheckCounter();
                                    msAPI_AVD_ClearAspectRatio();
                                    enDVBScanRetVal = EXIT_GOTO_TV;
                                }
                            }
                            else
                            {
                            #if ( ENABLE_UNITY_MEDIA_SETTING )
                                if(OSD_COUNTRY_SETTING == OSD_COUNTRY_GERMANY)
                                {
                                    MApp_ZUI_ACT_ShutdownOSD();
                                    MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_WELCOME_MSGBOX);
                                    enDVBScanRetVal = EXIT_GOTO_TV;
                                }
                                else
                            #endif  //ENABLE_UNITY_MEDIA_SETTING
                                {
                                    enDVBScanRetVal = EXIT_GOTO_PREVIOUS;
                                }
                            }
                            enScanState = STATE_SCAN_INIT;
                        }
                        else
                        {
                        #if ( ENABLE_UNITY_MEDIA_SETTING )
                            if( OSD_COUNTRY_SETTING == OSD_COUNTRY_GERMANY )
                            {
                                MApp_ZUI_ACT_ShutdownOSD();
                                MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_WELCOME_MSGBOX);
                            }
                        #endif  //ENABLE_UNITY_MEDIA_SETTING

                            enScanState = STATE_SCAN_INIT;
                            enDVBScanRetVal = EXIT_GOTO_TV;
                        }

                        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_INTERNAL_2_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                    }
                }
            }
            else
            {
                if( enScanState == STATE_SCAN_EXIT_MAIN_MENU )
                {
                    enDVBScanRetVal =EXIT_GOTO_TV;
                }
                else
                {
                    enDVBScanRetVal =EXIT_GOTO_PREVIOUS;
                }

                enScanState = STATE_SCAN_INIT;
            }

            if ( (g_enScanType == SCAN_TYPE_MANUAL && u8NumOfVchFound > 0)
               || g_enScanType == SCAN_TYPE_AUTO
              #if ENABLE_DVBC
               || g_enScanType == SCAN_TYPE_NETWORK
              #endif
              #if ENABLE_S2
               || g_enScanType == S2_SCAN_TYPE_AUTO
               || g_enScanType == S2_SCAN_TYPE_BLIND
               || g_enScanType == S2_SCAN_TYPE_NETWORK
              #if(ENABLE_S2_FAST_SCAN)
               || S2_SCAN_TYPE_FAST == g_enScanType
              #endif
              #endif
               )
            {
                if(msAPI_CM_CountProgram(msAPI_CM_GetCurrentServiceType(), E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO) > 0)
                {
                #if NTV_FUNCTION_ENABLE
                    if(OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY)
                    {
                        if(u8NetworkTotal != 0xFF && u8NetworkTotal > 1)
                        {
                            MApp_Set_ScanGoRegion_Status(TRUE);
                        }
                        else
                        {
                            MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
                        }
                    }
                    else
                    {
                        MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
                    }
                #else
                    MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
                #endif
                }
            }

        #if (CHANNEL_SCAN_AUTO_TEST)
            if(g_ScanAutoTestData.u2State == 1)
            {
                g_ScanAutoTestData.u16SrvFoundNum = u16NumOfSrvAdd;
                g_ScanAutoTestData.fCommand = 0;
                g_ScanAutoTestData.u2State = 2;
            }
        #endif
            break;


        case STATE_SCAN_GOTO_STANDBY:
            SCAN_DBINFO( printf("\n <<<STATE_SCAN_GOTO_STANDBY>>> ") );

          #if PATCH_FOR_HW_LIMIT_EXT_SYNC
            g_Ext_Sync = TRUE;
            MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_DEMOD, FALSE, TRUE, TRUE);
          #endif

            MApp_DTV_Scan_End(FALSE);

            if (  (g_enScanType == SCAN_TYPE_AUTO)
              #if ENABLE_DVBC
               || (g_enScanType == SCAN_TYPE_NETWORK)
              #endif
              #if ENABLE_S2
               || (g_enScanType == S2_SCAN_TYPE_AUTO)
               || (g_enScanType == S2_SCAN_TYPE_MANUAL)
               || (g_enScanType == S2_SCAN_TYPE_BLIND)
               || (g_enScanType == S2_SCAN_TYPE_NETWORK)
              #if(ENABLE_S2_FAST_SCAN)
               || S2_SCAN_TYPE_FAST == g_enScanType
              #endif
              #endif
               )
            {
                MApp_ZUI_ACT_ShutdownOSD();
            }

            enDVBScanRetVal =EXIT_GOTO_STANDBY;
            enScanState = STATE_SCAN_INIT;
            break;

        default:
            break;
    }

    return enDVBScanRetVal;
}
#endif // #if ENABLE_DTV


#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
void MApp_DTV_Scan_Retune_Confirm_Yes(void)
{
    MEMBER_SERVICETYPE eServiceType;
    WORD wCurPosition,wNID,wONID,wTSID;
    if (_u32MessageLossSignalTimer )
    {
        eServiceType = msAPI_CM_GetCurrentServiceType();
        wCurPosition = msAPI_CM_GetCurrentPosition(eServiceType);
        wNID = msAPI_CM_GetNetwork_ID(eServiceType,wCurPosition);
        wONID = msAPI_CM_GetON_ID(eServiceType,wCurPosition);
        wTSID = msAPI_CM_GetTS_ID(eServiceType,wCurPosition);

        MApp_SI_Recollect_TSRFList2Scan(wNID, wONID, wTSID);
        MApp_DTV_Scan_SetLossSignalState(LOSS_SIGNAL_RETUNE);
        _cOriginal_ChRF = msAPI_CM_GetPhysicalChannelNumber(eServiceType, wCurPosition);
        //printf("_cOriginal_ChRF  %bu\n",_cOriginal_ChRF);
        _u32MessageLossSignalTimer = 0;
        _stNetworkChangInfo.bLossOfSignal = FALSE;
        enScanState = STATE_SCAN_INIT;
    }
}

void MApp_DTV_Scan_Retune_Confirm_No(void)
{
    if (_u32MessageLossSignalTimer )
    {
        if(_u32MessageLossSignalTimer)
        {
            g_enScanType=SCAN_TYPE_NUM;
        }

        MApp_DTV_Scan_SetLossSignalState(LOSS_SIGNAL_NO_RETUNE);
        _u32MessageLossSignalTimer = 0;
        _stNetworkChangInfo.bLossOfSignal = FALSE;
        enScanState = STATE_SCAN_END;
    }
}

void MApp_DTV_Scan_NetworkChange_Cornfim_OK(void)
{
    if(_u32CheckMuxUpdateTimer )  //norway spec. says scan start without confirmation
    {
        if(_stNetworkChangInfo.bMuxAdd)
        {
            enScanState = STATE_SCAN_INIT;
        }
        else
        {
            enScanState = STATE_SCAN_END;
            return;
        }

        if(_stNetworkChangInfo.bMuxRemove)
        {
            MApp_SI_RemoveMismatchedMux();
        }

        if(_stNetworkChangInfo.bCellRemove)
        {
            BOOLEAN bCurCHIsRemoved;
            msAPI_CM_RemoveInvalidService(&bCurCHIsRemoved);
        }

        _u32CheckMuxUpdateTimer=0;
        _u32MessageDisplayTimer = 0;
        _stNetworkChangInfo.bCellRemove=_stNetworkChangInfo.bMuxAdd=_stNetworkChangInfo.bMuxRemove=FALSE;
    }
}

void MApp_DTV_Scan_NetworkChange_Cornfim_NO(void)
{
    if(_u32CheckMuxUpdateTimer == 0)
    {
        return;
    }
    enScanState=STATE_SCAN_END;
    _u32CheckMuxUpdateTimer=0;
    _u32MessageDisplayTimer = 0;
}

EN_LOSS_SIGNAL_STATE MApp_DTV_Scan_GetLossSignalState(void)
{
    return enLossSignalState;
}

void MApp_DTV_Scan_SetLossSignalState(EN_LOSS_SIGNAL_STATE enState)
{
    enLossSignalState = enState;
}

static void MApp_DTV_Scan_NewMux_ProcessUserInput( void )
{
    switch( u8KeyCode )
    {
        case KEY_POWER:
        case DSC_KEY_PWROFF:
            if(_u32CheckMuxUpdateTimer)
            {
                g_enScanType=SCAN_TYPE_NUM;
            }
            _u32CheckMuxUpdateTimer=0;
            if(_stNetworkChangInfo.bMuxRemove)
            {
                MApp_SI_RemoveMismatchedMux();
            }
            if(_stNetworkChangInfo.bCellRemove)
            {
                BOOLEAN bCurCHIsRemoved;
                msAPI_CM_RemoveInvalidService(&bCurCHIsRemoved);
            }
            if(_stNetworkChangInfo.bMuxAdd)
            {
                MApp_SI_AddNewTSService();
            }
            _stNetworkChangInfo.bCellRemove=_stNetworkChangInfo.bMuxAdd=_stNetworkChangInfo.bMuxRemove=FALSE;
            enScanState = STATE_SCAN_GOTO_STANDBY;
            break;


        case KEY_SELECT:
        case KEY_LEFT:
        case KEY_RIGHT:
        #if 1
          #if 0 //ENABLE_RIKS_TV
            if(_stNetworkChangInfo.bFreqChange||_stNetworkChangInfo.bMuxAdd)
            {
                if(0 != _u32MessageDisplayTimer)
                {
                    _u32MessageDisplayImmediateEnd=1;
                    break;
                }
            }
          #endif

            if (((_stNetworkChangInfo.bFreqChange) || (_stNetworkChangInfo.bMuxAdd))
              && (MApp_ZUI_GetActiveOSD() == E_OSD_MESSAGE_BOX)
              && (0 != _u32MessageDisplayTimer))
            {
                MApp_ZUI_ProcessKey(u8KeyCode);
            }
        #else
            if(_u32CheckMuxUpdateTimer)
            {
                if(_stNetworkChangInfo.bMuxAdd)
                {

                    enScanState=STATE_SCAN_INIT;
                }
                else
                {
                    enScanState=STATE_SCAN_END;
                    break;
                }
                if(_stNetworkChangInfo.bMuxRemove)
                {
                    MApp_SI_RemoveMismatchedMux();
                    //printf("MApp_SI_RemoveMismatchedMux\n");
                }
                if(_stNetworkChangInfo.bCellRemove)
                {
                    BOOLEAN bCurCHIsRemoved;
                    msAPI_CM_RemoveInvalidService(&bCurCHIsRemoved);
                }
                _u32CheckMuxUpdateTimer=0;
                _stNetworkChangInfo.bCellRemove=_stNetworkChangInfo.bMuxAdd=_stNetworkChangInfo.bMuxRemove=FALSE;

            }
        #endif
            break;


        case KEY_EXIT:
        #if ENABLE_RIKS_TV
        //case KEY_RIGHT:
        #endif
//            if (OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY)      //norway spec says it shall not be possible to cancel the scan
//                break;
            //marked for Riks Test 11.02 Verify it is able to cancel the scanning
            if(OSD_COUNTRY_SETTING == OSD_COUNTRY_FINLAND)//cable ready not allow cancel
                break;
            if(_u32CheckMuxUpdateTimer)
            {
                g_enScanType=SCAN_TYPE_NUM;
            }
            //_u32CheckMuxUpdateTimer=0;
            //_stNetworkChangInfo.bMuxAdd=_stNetworkChangInfo.bMuxRemove=FALSE;
            enScanState=STATE_SCAN_END;
            if(_stNetworkChangInfo.bMuxAdd)
            {
                MApp_SI_AddNewTSService();
            }
            //printf("cancel ....\n");
            break;


        default:
            break;
    }

    u8KeyCode = KEY_NULL;
}


void MApp_DTV_Scan_Set_UpdateMethod(BOOLEAN bAddMux, BOOLEAN bRemoveMux ,BOOLEAN bCellRemove, BOOLEAN bFreqChange)
{
    _stNetworkChangInfo.bMuxAdd=bAddMux;
    _stNetworkChangInfo.bMuxRemove=bRemoveMux;
    _stNetworkChangInfo.bCellRemove=bCellRemove;
    _stNetworkChangInfo.bFreqChange = bFreqChange;
    SCAN_DBINFO(printf("MApp_DTV_Scan_Set_UpdateMethod add %u remove %u cell remove %u  freqChange  %u\n",_stNetworkChangInfo.bMuxAdd,_stNetworkChangInfo.bMuxRemove,bCellRemove,_stNetworkChangInfo.bFreqChange));
}


void MApp_DTV_Scan_Set_LossSignalFlag(BOOLEAN bLossSignal)
{
    _stNetworkChangInfo.bLossOfSignal = bLossSignal;
}

void MApp_DTV_Scan_Update_Mux_State_Init( void )
{
    enScanState = STATE_SCAN_WAIT;
    enDVBScanState = STATE_DVB_SCAN_INIT;
    MApp_Dmx_GetScanTableStateInit();
}
EN_RET MApp_DTV_Scan_Update_Mux( void )
{
    BOOLEAN ScanResult=0;
    BOOLEAN fDBFull=FALSE;
    U16 i=0;
    WORD wSignalQuality=0;
    SI_SHORT_DTV_CHANNEL_INFO *pastVirtualCh = NULL;
    enDVBScanRetVal =EXIT_NULL;
    BOOLEAN bFindCurServiceInALTFreq = FALSE;

    MApp_DTV_Scan_NewMux_ProcessUserInput();

    switch( enScanState )
    {
        case STATE_SCAN_INIT:
            //Earse all osd message
            //Display "Scanning..."
            printf("Scanning...\n");

            _u8FirstRF=0;
            _u32CheckMuxUpdateTimer=0;
            enDVBScanState = STATE_DVB_SCAN_INIT;

            if( IS_NETWORK_UPDARE_COUNTRY(OSD_COUNTRY_SETTING) )
            {   //Direct to auto tuning flow
                _stNetworkChangInfo.bCellRemove=_stNetworkChangInfo.bMuxAdd=_stNetworkChangInfo.bMuxRemove=_stNetworkChangInfo.bFreqChange = FALSE;
                enDVBScanState = STATE_DVB_SCAN_INIT;

                stGenSetting.stScanMenuSetting.u8ScanType = SCAN_TYPE_AUTO;
                g_enScanType=SCAN_TYPE_AUTO;
                enDVBScanRetVal = EXIT_GOTO_DTVSCAN;
                eTuneType = OSD_TUNE_TYPE_DTV_ONLY;
                u16ScanDtvChNum = 0;
                u16ScanRadioChNum = 0;
            #if ( NORDIG_FUNC )
                u16ScanDataChNum = 0;
            #endif //NORDIG_FUNC
                MApp_ZUI_ACT_StartupOSD(E_OSD_AUTO_TUNING);
                break;
            }
        #if ( NORDIG_FUNC )
            // Modified for "additional task 1_NorDig Task 14:16"  [TC16032502044] when Mux changed case behavior.
            else if( ( OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY )
                  || ( OSD_COUNTRY_SETTING == OSD_COUNTRY_SWEDEN )
                   )
            {   //Direct to auto tuning flow, and reset CM to clear before network program.
                msAPI_CM_ResetAllProgram();

                _stNetworkChangInfo.bCellRemove=_stNetworkChangInfo.bMuxAdd=_stNetworkChangInfo.bMuxRemove=_stNetworkChangInfo.bFreqChange = FALSE;
                enDVBScanState = STATE_DVB_SCAN_INIT;

                stGenSetting.stScanMenuSetting.u8ScanType = SCAN_TYPE_AUTO;
                g_enScanType = SCAN_TYPE_AUTO;
                enDVBScanRetVal = EXIT_GOTO_DTVSCAN;
                eTuneType = OSD_TUNE_TYPE_DTV_ONLY;
                u16ScanDtvChNum = 0;
                u16ScanRadioChNum = 0;
                u16ScanDataChNum = 0;
                MApp_ZUI_ACT_StartupOSD( E_OSD_AUTO_TUNING );
                break;
            }
        #endif  //NORDIG_FUNC

            if(MApp_ZUI_GetActiveOSD() == E_OSD_MESSAGE_BOX)
            {
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CLOSE_CURRENT_OSD);
            }
        #if 1   //TODO
            MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
            MApp_ZUI_ACT_ExecuteWndAction( EN_EXE_SHOW_SCANNING_MSGBOX );
        #else
            uniSys_Funs_MessageBox_Show( EN_EXE_SHOW_SCANNING_MSGBOX );
        #endif

            MApp_Dmx_GetScanTableStateInit();
            _MApp_DTV_Scan_TableConfig(&_stScanConfig);

            if( MApp_DTV_Scan_Init() == TRUE )
            {
                g_enScanType=SCAN_TYPE_UPDATE_MUX;
                enScanState = STATE_SCAN_SEARCH_RF_CHANNEL;
            #if ENABLE_DVBC
                if(IsDVBCInUse())
                {
                    BYTE cRFChannelNumber;
                    MEMBER_SERVICETYPE bServiceType;
                    WORD wCurrentPosition;
                    U8 u8PhNum=0;
                    DTVPROGRAMID_M stDPI;

                    memset(&stDPI, 0, sizeof(stDPI));

                    bServiceType = msAPI_CM_GetCurrentServiceType();
                    wCurrentPosition = msAPI_CM_GetCurrentPosition(bServiceType);
                    cRFChannelNumber = msAPI_CM_GetPhysicalChannelNumber(bServiceType,wCurrentPosition);
                    if(INVALID_PHYSICAL_CHANNEL_NUMBER == cRFChannelNumber)
                    {
                        enScanState = STATE_SCAN_END;
                        break;
                    }
                    u8PhNum = msAPI_CM_Get_RFChannelIndex(cRFChannelNumber);
                    if(msAPI_CM_GetIDTable(u8PhNum,(BYTE *)&stDPI,E_DATA_ID_TABLE))
                    {
                        //stTPSetting.u32Symbol_rate = stDPI.u32SymbRate;
                        stTPSetting.u32Symbol_rate = msAPI_CM_Get_IDTab_SymbolRate(&stDPI);

                        stTPSetting.u8Modulation = stDPI.QamMode;
                        stTPSetting.u32Frequency = stDPI.u32Frequency;
                        stTPSetting.enBandWidth = stDPI.enBandWidth;
                        stTPSetting.bAutoSRFlag = 0;
                        stTPSetting.bAutoQamFlag = 0;

                    }
                    else
                    {
                        enScanState = STATE_SCAN_END;
                        break;
                    }
                    _stScanConfig.bEnableNITQuickScan=TRUE;
                }
                else
            #endif
                {
                    if((MApp_DTV_Scan_GetLossSignalState() == LOSS_SIGNAL_RETURN_ORIGINAL_RF) && (OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY))
                    {
                        u8RFCh = msAPI_CM_GetOriginalRFnumber(msAPI_CM_GetCurrentServiceType(),msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()));
                        //printf("u8RFCh  %bu\n",u8RFCh);
                    }
                    else
                    {
                        if(IS_NETWORK_UPDARE_COUNTRY(OSD_COUNTRY_SETTING))
                        //if ((OSD_COUNTRY_SETTING == OSD_COUNTRY_MALAYSIA) || (OSD_COUNTRY_SETTING == OSD_COUNTRY_UNITED_ARAB_EMIRATES))
                        {   //Singapore tune all RF because SGP SIPSI test stream doens't content frequency_list_descriptor and terrestrial_delivery_system_descriptor
                            u8RFCh = msAPI_DFT_GetFirstPhysicalChannelNumber();
                        }
                        else
                        {
                            u8RFCh=MApp_SI_Get_New_RF_Index();
                        }
                        //printf("...u8RFCh  %bu\n",u8RFCh);
                    }
                    if(u8RFCh != SI_INVALID_PHYSICAL_CHANNEL_NUMBER && u8RFCh !=0)
                    {
                        msAPI_DFT_GetTSSetting( u8RFCh, &stTPSetting );
                        //msAPI_Aeon_Disable();
                    }
                    else
                    {
                        enScanState = STATE_SCAN_END;
                    }
                }
            }
            else
            {
                enScanState = STATE_SCAN_END;
            }
            break;
        case STATE_SCAN_NEXT_CHANNEL:

#if ENABLE_DVBC
            if(IsDVBCInUse())
            {
                MS_CABLE_PARAMETER desc;
                BYTE dummy;
                enScanState = STATE_SCAN_END;
                if(!_MApp_DTV_Scan_GetNITAvailableFlag())break;
                while(MApp_SI_GetNextCableParameter(&desc, NULL,NULL,NULL,NULL, TRUE))
                {
                    if(msAPI_CM_Is_TSExist(desc.u16ONID, desc.u16TSID, &dummy) == FALSE)
                    {

                        stTPSetting.u32Symbol_rate = desc.u32Symbol_rate/10;
                        stTPSetting.u8Modulation = desc.u8Modulation-1;
                        stTPSetting.u32Frequency = desc.u32CentreFreq/10;
                        stTPSetting.enBandWidth = E_RF_CH_BAND_8MHz;
                        stTPSetting.bAutoSRFlag = 0;
                        stTPSetting.bAutoQamFlag = 0;
                        enScanState = STATE_SCAN_SEARCH_RF_CHANNEL;
                        //printf("new mux...%d\n",stTPSetting.u32Frequency);
                        break;
                    }

                    ResetSDTParsingParameter(); //reset Params for next GetNextCableParameter
                }

            }
            else
#endif
            {
                if(IS_NETWORK_UPDARE_COUNTRY(OSD_COUNTRY_SETTING))
                //if ((OSD_COUNTRY_SETTING == OSD_COUNTRY_MALAYSIA) || (OSD_COUNTRY_SETTING == OSD_COUNTRY_UNITED_ARAB_EMIRATES))
                {   //Singapore tune all RF because SGP SIPSI test stream doens't content frequency_list_descriptor and terrestrial_delivery_system_descriptor
                    u8RFCh=msAPI_DFT_GetNextPhysicalChannelNumber(u8RFCh);
                }
                else
                {
                    u8RFCh=MApp_SI_Get_New_RF_Index();
                }

                if( u8RFCh == SI_INVALID_PHYSICAL_CHANNEL_NUMBER || u8RFCh == 0/*u8MaxRFCh*/ )
                {
                    enScanState = STATE_SCAN_END;
                    break;
                }
                enScanState = STATE_SCAN_SEARCH_RF_CHANNEL;
                msAPI_DFT_GetTSSetting( u8RFCh, &stTPSetting );
            }
            break;
        case STATE_SCAN_SEARCH_RF_CHANNEL:
            if( MApp_DVB_Scan( &stTPSetting, &ScanResult ) == FALSE )
            {
                break;
            }
            if( ScanResult == FE_LOCK )
            {
                enScanState = STATE_SCAN_GET_PROGRAMS;
            }
            else
            {
                if((MApp_DTV_Scan_GetLossSignalState() == LOSS_SIGNAL_RETURN_ORIGINAL_RF) && (OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY))
                {
                    enScanState = STATE_SCAN_END;
                }
                else
                {
                    enScanState = STATE_SCAN_NEXT_CHANNEL;
                }
            }
            break;
        case STATE_SCAN_GET_PROGRAMS:   //Truman for digital only, analog scan shouldn't go into this state
            u8NumOfVchFound = 0;
            if( MApp_Dmx_GetScanTables(&_stScanConfig, &u8NumOfVchFound ) == FALSE )
            {
                break;
            }
            MApp_Dmx_GetScanTableStateInit();
#if ENABLE_DVBC
            if(_stScanConfig.bEnableNITQuickScan)
            {
                if(!_MApp_DTV_Scan_GetNITAvailableFlag())
                {
                    _MApp_DTV_Scan_SetNITAvailableFlag(TRUE);
                    _stScanConfig.bEnableNITQuickScan=FALSE;
                    enScanState=STATE_SCAN_NEXT_CHANNEL;
                    break;
                }
            }
#endif
            if( u8NumOfVchFound > 0 )
                enScanState = STATE_SCAN_SAVE_PROGRAMS;
            else
            {
                enScanState = STATE_SCAN_NEXT_CHANNEL;

              #if (ENABLE_HIERARCHY)
                if(msAPI_Tuner_Is_HierarchyOn()&&(msAPI_Tuner_Get_HpLp()==0))
                {
                    stTPSetting.u8HpLp=1;
                    enScanState=STATE_SCAN_SEARCH_RF_CHANNEL;
                    break;
                }
              #endif

              #if ENABLE_DVB_T2
                {
                    U8 u8PLP_ID;
                    if(MApp_SI_GetNextT2Parameter(&u8PLP_ID)&& (_TotalPlpIDNum > 1))
                    {
                        stTPSetting.u8PLPID=u8PLP_ID;
                        mdev_CofdmSetPlpGroupID(u8PLP_ID,0);
                        enScanState=STATE_SCAN_SEARCH_RF_CHANNEL;
                    }
                }
              #endif
            }
            break;

        case STATE_SCAN_SAVE_PROGRAMS:
            if(_u8FirstRF == 0)
            {
                _u8FirstRF=u8RFCh;
            }
            if(u8NumOfVchFound && (MApp_DTV_Scan_GetLossSignalState() == LOSS_SIGNAL_RETURN_ORIGINAL_RF) && (OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY))
            {
                msAPI_CM_ResetOriginalRFnumber(msAPI_CM_GetCurrentServiceType(),msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()));
            }
            MApp_SI_Reset_New_RF_Index(u8RFCh);
            //wSignalQuality = msAPI_Tuner_GetSingalSNRPercentage();
            msAPI_Tuner_CheckSignalStrength(&wSignalQuality);
            wSignalQuality = (wSignalQuality&0x7F)<<8;
            //wSignalQuality |= (msAPI_Tuner_GetSingalSNRPercentage()&0xFF);
            wSignalQuality |= (msAPI_Tuner_GetSignalQualityPercentage()&0xFF);
            printf("\r\n (UpdateMux)wSignalQualityStrength <# %x #>\n",wSignalQuality);
            fDBFull = FALSE;
            pastVirtualCh = MApp_SI_Get_PastVirtualCh();
            for(i = 0;i < u8NumOfVchFound ;i++)
            {
                if((MApp_DTV_Scan_GetLossSignalState() == LOSS_SIGNAL_RETURN_ORIGINAL_RF || MApp_DTV_Scan_GetLossSignalState() == LOSS_SIGNAL_RETUNE)
                    && ((OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY) || (OSD_COUNTRY_SETTING == OSD_COUNTRY_NEWZEALAND)))
                {
                    pastVirtualCh[i].stCHAttribute.wSignalStrength = 0x7FFF;
                }
                else
                {
                    pastVirtualCh[i].stCHAttribute.wSignalStrength = wSignalQuality;
                }
                if((MApp_DTV_Scan_GetLossSignalState() == LOSS_SIGNAL_RETUNE)
                    &&((pastVirtualCh[i].wService_ID == msAPI_CM_GetService_ID(msAPI_CM_GetCurrentServiceType(), msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType())))
                    &&(pastVirtualCh[i].wOriginalNetwork_ID == msAPI_CM_GetON_ID(msAPI_CM_GetCurrentServiceType(), msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType())))))
                {
                    bFindCurServiceInALTFreq = TRUE;
                }
            }

            if((MApp_DTV_Scan_GetLossSignalState() != LOSS_SIGNAL_RETUNE) || bFindCurServiceInALTFreq == TRUE)
            {
                u16NumOfSrvAdd += MApp_Scan_AddOneDTVPchVchs(u8RFCh, pastVirtualCh, u8NumOfVchFound, TRUE, &fDBFull);

                {
                    U16  *au16ServiceIDs=NULL;//[MAX_VC_PER_PHYSICAL];
                    MEMBER_SERVICETYPE *aeServiceType=NULL;//[MAX_VC_PER_PHYSICAL];
                    MS_PAT_ITEM *pastPATItem = MApp_SI_Get_PastPATItem();
                    U8 u8PLP_ID=0;
                    U8 u8ServiceCount=MApp_SI_GetScanNumOfPatItem();

                    au16ServiceIDs=(U16*)msAPI_Memory_Allocate(sizeof(U16)*MAX_VC_PER_PHYSICAL, BUF_ID_DVB_SCAN_UPDATE_MUX);
                    aeServiceType=(MEMBER_SERVICETYPE*)msAPI_Memory_Allocate(sizeof(MEMBER_SERVICETYPE)*MAX_VC_PER_PHYSICAL, BUF_ID_DVB_SCAN_UPDATE_MUX);

                    if(au16ServiceIDs && aeServiceType)
                    {
                        for( i = 0; i < u8ServiceCount; i++)
                        {
                            au16ServiceIDs[i] = pastPATItem[i].u16ProgramNumber;
                            aeServiceType[i]  = msAPI_SI_ToCM_Service_Type((MEMBER_SI_SERVICETYPE)pastVirtualCh[i].stCHAttribute.bServiceType);
                            //aeServiceType[i] = (MEMBER_SERVICETYPE) pastVirtualCh[i].stCHAttribute.bServiceType;
                        }
                        msAPI_Tuner_Get_PLP_ID(&u8PLP_ID);
                        msAPI_CM_RemoveMismatchedProgram(u8RFCh, pastVirtualCh[0].wTransportStream_ID, u8PLP_ID, msAPI_Tuner_Get_HpLp(), au16ServiceIDs, aeServiceType, u8ServiceCount,0,0);
                    }
                    else
                    {
                        ASSERT(0);
                    }
                    if(au16ServiceIDs)  msAPI_Memory_Free(au16ServiceIDs, BUF_ID_DVB_SCAN_UPDATE_MUX);
                    if(aeServiceType)   msAPI_Memory_Free(aeServiceType, BUF_ID_DVB_SCAN_UPDATE_MUX);
                }
            }

            if( !fDBFull)
            {
                enScanState = STATE_SCAN_NEXT_CHANNEL;

            #if (ENABLE_HIERARCHY)
                if(msAPI_Tuner_Is_HierarchyOn()&&(msAPI_Tuner_Get_HpLp()==0))
                {
                    stTPSetting.u8HpLp=1;
                    enScanState=STATE_SCAN_SEARCH_RF_CHANNEL;
                    break;

                }
            #endif

            #if ENABLE_DVB_T2
                {
                    U8 u8PLP_ID;
                    if(MApp_SI_GetNextT2Parameter(&u8PLP_ID)&& (_TotalPlpIDNum > 1))
                    {
                        stTPSetting.u8PLPID=u8PLP_ID;
                        mdev_CofdmSetPlpGroupID(u8PLP_ID,0);
                        enScanState=STATE_SCAN_SEARCH_RF_CHANNEL;
                    }
                }
            #endif
            }
            else
            {
                enScanState = STATE_SCAN_END;
            }
            break;

        case STATE_SCAN_END:
            //erase message
          #if 1   //TODO
            if(MApp_ZUI_GetActiveOSD() == E_OSD_MESSAGE_BOX)
            {
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CLOSE_CURRENT_OSD);
            }
          #endif

            if(_u32CheckMuxUpdateTimer)//cancel
            {
                if(!IS_DONOT_REMOVE_COUNTRY(OSD_COUNTRY_SETTING))
                //if((OSD_COUNTRY_SETTING != OSD_COUNTRY_UNITED_ARAB_EMIRATES) && (OSD_COUNTRY_SETTING != OSD_COUNTRY_MALAYSIA))
                {
                    if(_stNetworkChangInfo.bMuxRemove)
                    {
                        MApp_SI_RemoveMismatchedMux();
                    }
                    if(_stNetworkChangInfo.bCellRemove)
                    {
                        BOOLEAN bCurCHIsRemoved;
                        msAPI_CM_RemoveInvalidService(&bCurCHIsRemoved);
                        if(bCurCHIsRemoved)
                        {
                            MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);
                            MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
                        }
                    }
                }
                MApp_SI_ResetNetworkNewService();
                if (OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY)
                    MApp_DTV_Scan_SetLossSignalState(LOSS_SIGNAL_INIT);
                _u32CheckMuxUpdateTimer=0;
                enDVBScanRetVal =EXIT_GOTO_PREVIOUS;
                enScanState = STATE_SCAN_INIT;
                g_enScanType = (EN_SCAN_TYPE) stGenSetting.stScanMenuSetting.u8ScanType;
                MApp_SI_EnableNetworkCheck(TRUE);
                break;
            }
            _stNetworkChangInfo.bCellRemove=_stNetworkChangInfo.bMuxAdd=_stNetworkChangInfo.bMuxRemove=_stNetworkChangInfo.bFreqChange = FALSE;
            _bFrequency_change = FALSE;
            MApp_DTV_Scan_End(FALSE);
          #if (MHEG5_ENABLE)
            if ( IsDTVInUse()
        #if ENABLE_S2
            ||IsS2InUse()
        #endif
            )
            {
                msAPI_MHEG5_Bean_Init();

                enCheckMHEGLoadingStatus = EN_MHEG5_MONITOR;
                msAPI_MHEG5_SetGoBackMHEG5(false);
            }
          #endif

          #if 0
            enUiMainMenuState = STATE_UIMENU_WAIT;
          #endif

            // to prevent sound when analog tuning is finished
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_INTERNAL_2_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);

            if(msAPI_CM_CountProgram(msAPI_CM_GetCurrentServiceType(), E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO) != 0)
            {
                MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
            }

            enDVBScanRetVal =EXIT_GOTO_PREVIOUS;
            enScanState = STATE_SCAN_INIT;
            g_enScanType = (EN_SCAN_TYPE) stGenSetting.stScanMenuSetting.u8ScanType;
            MApp_SI_EnableNetworkCheck(TRUE);
            break;


        case STATE_SCAN_GOTO_STANDBY:
            //erase message
          #if 1 //TODO
            if(MApp_ZUI_GetActiveOSD() == E_OSD_MESSAGE_BOX)
            {
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CLOSE_CURRENT_OSD);
            }
          #endif
            _stNetworkChangInfo.bCellRemove=_stNetworkChangInfo.bMuxAdd=_stNetworkChangInfo.bMuxRemove=_stNetworkChangInfo.bFreqChange= FALSE;
            _bFrequency_change = FALSE;
            MApp_DTV_Scan_End(FALSE);
          #if 0 //TODO
            enUiMainMenuState = STATE_UIMENU_WAIT;
          #endif
            enDVBScanRetVal =EXIT_GOTO_STANDBY;
            enScanState = STATE_SCAN_INIT;
            MApp_SI_EnableNetworkCheck(TRUE);
            break;


        case STATE_SCAN_WAIT:
            if (((_u32MessageDisplayTimer && msAPI_Timer_DiffTimeFromNow(_u32MessageDisplayTimer) > 3000)
                ||_u32MessageDisplayImmediateEnd == 1)&&
                ((OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY)||(OSD_COUNTRY_SETTING == OSD_COUNTRY_SWEDEN)||(OSD_COUNTRY_SETTING == OSD_COUNTRY_FINLAND)))
            {
//1281446: [SQC][Marlon_120B][1st_DVBT][Antenna Ready HD (Finland)] Standby channel update ->
                if(_u32MessageDisplayImmediateEnd == 1)
                    _u32MessageDisplayImmediateEnd = 0;
                if((_stNetworkChangInfo.bMuxAdd || _stNetworkChangInfo.bFreqChange))
                    //&& (OSD_COUNTRY_SETTING != OSD_COUNTRY_FINLAND))   // FINLAN is not scan
                {

                    enScanState=STATE_SCAN_INIT;
                    if(_stNetworkChangInfo.bFreqChange)
                        _bFrequency_change = TRUE;
                }
                else
                {
                    _u32CheckMuxUpdateTimer=0;
                    _u32MessageDisplayTimer = 0;
                    enScanState=STATE_SCAN_END;
                    break;
                }
                if(_stNetworkChangInfo.bMuxRemove)
                {
                    MApp_SI_RemoveMismatchedMux();
                    //printf("MApp_SI_RemoveMismatchedMux\n");
                }
                _u32CheckMuxUpdateTimer=0;
                _u32MessageDisplayTimer = 0;
                _stNetworkChangInfo.bFreqChange=_stNetworkChangInfo.bMuxAdd=_stNetworkChangInfo.bMuxRemove=FALSE;
                break;
            }
            else if ((_u32MessageLossSignalTimer && msAPI_Timer_DiffTimeFromNow(_u32MessageLossSignalTimer) > LOSS_SIGNAL_TIMEOUT) &&
                ((OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY)||(OSD_COUNTRY_SETTING == OSD_COUNTRY_SWEDEN)))
            {
                if (LOSS_SIGNAL_CONFIRM_MSG == MApp_DTV_Scan_GetLossSignalState())
                {
                #if 1 //TODO
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CLOSE_CURRENT_OSD);
                    MApp_DTV_Scan_SetLossSignalState(LOSS_SIGNAL_NO_RETUNE);
                #endif
                }
                _u32MessageLossSignalTimer = 0;
                _stNetworkChangInfo.bLossOfSignal = FALSE;
                enDVBScanRetVal =EXIT_GOTO_PREVIOUS;
                enScanState = STATE_SCAN_INIT;
                break;
            }
            else if(_u32CheckMuxUpdateTimer && msAPI_Timer_DiffTimeFromNow(_u32CheckMuxUpdateTimer) > 10000)
            {
                //printf("wait time out\n");
                enScanState=STATE_SCAN_END;
                break;
            }
            if((MApp_DTV_Scan_GetLossSignalState() == LOSS_SIGNAL_RETURN_ORIGINAL_RF) && ((OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY)||(OSD_COUNTRY_SETTING == OSD_COUNTRY_SWEDEN)))
            {
                MApp_SI_EnableNetworkCheck(FALSE);
                g_enScanType=SCAN_TYPE_NUM;
                //printf("LOSS_SIGNAL_RETURN_ORIGINAL_RF\n");
                enScanState = STATE_SCAN_INIT;
            }
            else if (0==_u32MessageLossSignalTimer && _stNetworkChangInfo.bLossOfSignal)
            {
                MApp_SI_EnableNetworkCheck(FALSE);
                 g_enScanType=SCAN_TYPE_NUM;
                //printf("display LOSS_OF_SIGNAL_MSGBOX\n");
            #if 0 //TODO
                MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                MApp_ZUI_ACT_ExecuteWndAction( EN_EXE_SHOW_LOSS_OF_SIGNAL_MSGBOX );
            #else
                MApp_ZUI_ACT_ShutdownOSD();
                MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_LOSS_OF_SIGNAL_MSGBOX);
            #endif
                _u32MessageLossSignalTimer = msAPI_Timer_GetTime0();
                if(0 == _u32MessageLossSignalTimer)
                {
                    _u32MessageLossSignalTimer=1;
                }
            }
            else if (  (0 == _u32CheckMuxUpdateTimer)
                    && ( _stNetworkChangInfo.bFreqChange
                       ||_stNetworkChangInfo.bMuxRemove
                       ||_stNetworkChangInfo.bMuxAdd
                       ||_stNetworkChangInfo.bCellRemove )
                    )
            {
                MApp_SI_EnableNetworkCheck(FALSE);
                g_enScanType = SCAN_TYPE_NUM;

              #if ENABLE_OAD
                if (MApp_OAD_IsPowerOnCheck() || MApp_OAD_IsScheduleOnCheck())
                {
                    // do nothing
                    printf("\r\n OAD Check do not pop up msgbox\n");
                }
                else
              #endif
                if(_stNetworkChangInfo.bFreqChange)
                {
                    printf("\r\n bFreqChange!!\n");
                #if 0 //TODO
                    MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                    MApp_ZUI_ACT_ExecuteWndAction( EN_EXE_SHOW_FREQUENCY_CHANGE_MSGBOX );
                #else
                    MApp_ZUI_ACT_ShutdownOSD();
                    MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_FREQUENCY_CHANGE_MSGBOX);
                #endif
                }
                else if(_stNetworkChangInfo.bMuxAdd)
                {
                    printf("\r\n New Multiplex Add\n");
                    if (OSD_COUNTRY_SETTING == OSD_COUNTRY_FINLAND)
                    {
//1281446: [SQC][Marlon_120B][1st_DVBT][Antenna Ready HD (Finland)] Standby channel update ->
                    #if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT) //TODO, wait UI
                        MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                        MApp_ZUI_ACT_ExecuteWndAction( EN_EXE_SHOW_NETWORK_CHANGE_MSGBOX );
                    #endif
                    }
                    else if (OSD_COUNTRY_SETTING == OSD_COUNTRY_NEWZEALAND)
                    {
                    #if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT) //TODO
                        MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                        MApp_ZUI_ACT_ExecuteWndAction( EN_EXE_SHOW_NETWORK_CHANGE_MSGBOX );
                    #endif
                    }
                    else if(IS_NETWORK_UPDARE_COUNTRY(OSD_COUNTRY_SETTING))
                    {
                        //display "New Multiplex might be available! Re-scan is required."
                    #if 0 //TODO
                        MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                        MApp_ZUI_ACT_ExecuteWndAction( EN_EXE_SHOW_NEW_MULTIPLEX_MIGHT_AVAILABLE_MSGBOX );
                    #else
                        MApp_ZUI_ACT_ShutdownOSD();
                        MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_NETWORK_CHANGE_MSGBOX);
                    #endif
                    }
                    else if((OSD_COUNTRY_SETTING == OSD_COUNTRY_SWEDEN))
                    {
                        //display "New Multiplex might be available! Re-scan is required."
                    #if 0 //TODO
                        MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                        MApp_ZUI_ACT_ExecuteWndAction( EN_EXE_SHOW_NEW_MULTIPLEX_MIGHT_AVAILABLE_MSGBOX );
                    #else
                        MApp_ZUI_ACT_ShutdownOSD();
                        MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_NETWORK_CHANGE_MSGBOX);
                    #endif
                    }
                #if ( NORDIG_FUNC )
                    // Modified for "additional task 1_NorDig Task 14:16"  [TC16032502044] when Mux changed case behavior.
                    else if( ( OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY )
                          || ( OSD_COUNTRY_SETTING == OSD_COUNTRY_SWEDEN )
                           )
                    {
                        MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_MULTIPLEX_IS_REMOVED_MSGBOX);
                    }
                #endif  //NORDIG_FUNC
                }
                else if(_stNetworkChangInfo.bMuxRemove)
                {
                    printf("Multiplex is removed. Update now?\n");
                    if (OSD_COUNTRY_SETTING == OSD_COUNTRY_NEWZEALAND)
                    {
                    #if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT) //TODO
                        MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                        MApp_ZUI_ACT_ExecuteWndAction( EN_EXE_SHOW_NETWORK_CHANGE_MSGBOX );
                    #endif
                    }
                    else if(IS_NETWORK_UPDARE_COUNTRY(OSD_COUNTRY_SETTING))
                    //else if ((OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY)||(OSD_COUNTRY_SETTING ==OSD_COUNTRY_MALAYSIA))
                    {
                    #if 0 //TODO
                         MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                         MApp_ZUI_ACT_ExecuteWndAction( EN_EXE_SHOW_MULTIPLEX_IS_REMOVED_MSGBOX );
                    #else
                         MApp_ZUI_ACT_ShutdownOSD();
                         MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                         MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_MULTIPLEX_IS_REMOVED_MSGBOX);
                    #endif
                    }
                    else if((OSD_COUNTRY_SETTING == OSD_COUNTRY_SWEDEN))
                    {
                         MApp_ZUI_ACT_ShutdownOSD();
                         MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                         MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_NETWORK_CHANGE_MSGBOX);
                    }
                }
                else if(_stNetworkChangInfo.bCellRemove)
                {
                #if 1 //TODO
                    printf("Transmitter is removed. Update now?\n");
                    bIsCellIDRemoveMsgBox = TRUE;
                    MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                    MApp_ZUI_ACT_ExecuteWndAction( EN_EXE_SHOW_NETWORK_CHANGE_MSGBOX );
                #endif
                }
                _u32CheckMuxUpdateTimer =  msAPI_Timer_GetTime0();
                _u32MessageDisplayTimer = msAPI_Timer_GetTime0();
                if(0 == _u32CheckMuxUpdateTimer)
                {
                    _u32CheckMuxUpdateTimer=1;
                }
                if(0 == _u32MessageDisplayTimer)
                {
                    _u32MessageDisplayTimer=1;
                }
                //MApp_Dmx_DisableTableMonitor();
            }
            break;
        default:
            break;
    }
    return enDVBScanRetVal;
}
#endif

/*****************************************************************************/
#define NEW_SCAN_APP_DBG(y)     //y


#if 1//ENABLE_T_C_COMBO
void MApp_DVBType_SetCurrentType(U8 SelectDVBType)
{
/*
    UI_PREV_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_TYPE;

    if (SelectDVBType == EN_DVB_T_TYPE)
        UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBT;
    else
        UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBC;
*/
    stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType = (EN_DVB_TYPE)SelectDVBType;
}

EN_DVB_TYPE MApp_DVBType_GetPrevType(void)
{
    return enDVBPreSelectType;
}

void MApp_DVBType_SetPrevType(EN_DVB_TYPE SelectDVBType)
{
    printf("\n[-enDVBPreSelectType-]: %d\n",SelectDVBType);
    enDVBPreSelectType = (EN_DVB_TYPE)SelectDVBType;
}
#endif

#if(ENABLE_DTV)

EN_DVB_TYPE MApp_DVBType_GetCurrentType(void)
{
    if( stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType )
        return EN_DVB_C_TYPE;

    return EN_DVB_T_TYPE;
}

BOOLEAN MApp_DVB_Scan( MS_TP_SETTING *pstTPSetting,BOOLEAN *ScanResult )
{
    BOOLEAN Result = FE_NOT_LOCK;

    *ScanResult = FE_NOT_LOCK;

    //printf("\n MApp_DVB_Scan (%d) \n", enDVBScanState);

    switch( enDVBScanState )
    {
        case STATE_DVB_SCAN_INIT:
            enDVBScanState = STATE_DVB_SCAN_INIT_DEMODE;
            break;

        case STATE_DVB_SCAN_INIT_DEMODE:
            //Set Tuner
          #if CHANNEL_SCAN_AUTO_TEST
            if(stTpSettingPC.u32Frequency)
            {
                printf("\r\nMApp_Scan: msAPI_Tuner_Tune2RfCh\r\n");
                msAPI_Tuner_Tune2RfCh( &stTpSettingPC );
            }
            else
            {
                msAPI_Tuner_Tune2RfCh( pstTPSetting );
            }
          #else

//            printf("%s,%d\r\n",__FUNCTION__,__LINE__);
            msAPI_Tuner_Tune2RfCh( pstTPSetting );
          #endif

            msAPI_Timer_Delayms( TUNER_PLL_STABLE_TIME );
            enDVBScanState = STATE_DVB_SCAN_CHECK_LOCK;
            break;


        case STATE_DVB_SCAN_CHECK_LOCK:
            //Check Lock Loop
          #if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
            if(g_enScanType==SCAN_TYPE_UPDATE_MUX && msAPI_SI_IsSpecificCountry(MApp_GetSICountry(OSD_COUNTRY_SETTING),SI_SUPPORT_NETWORK_UPDATE_SPECIFIC_COUNTRY))//todo check offset case
            {
                U8 i;
                for(i=0;i<100;i++)
                {
                    msAPI_Timer_Delayms(10);
                    msAPI_Tuner_CheckLock( &Result,FALSE);
                    if( Result == FE_LOCK )
                    {
                        break;
                    }
                }
                if(i>=100)
                {
                    *ScanResult = FE_NOT_LOCK;
                    enDVBScanState = STATE_DVB_SCAN_INIT;
                    return TRUE;
                }
            }
          #endif


            if( msAPI_Tuner_CheckLock(&Result, TRUE) == FALSE )
            {
                NEW_SCAN_APP_DBG( printf( "\n FE IIC fail " ); );
              #if PLAYCARD_DISABLE // if you want use play card turn off this
                *ScanResult = FE_NOT_LOCK;
              #else
                *ScanResult = FE_LOCK;
              #endif
                enDVBScanState = STATE_DVB_SCAN_INIT;
                return TRUE;
                break;
            }

            NEW_SCAN_APP_DBG( printf( "\n MApp_DVB_Scan Demod Check Lock=%bd ", ( U8 ) Result ); );
            if( Result == FE_LOCK )
            {
                *ScanResult = FE_LOCK;
                NEW_SCAN_APP_DBG( printf( "\n FE Locked " ); );
              #if ENABLE_AUTOTEST
                if(g_bAutobuildDebug)
                {
                    printf("\n 31_DTV_FE_Locked ");
                }
              #endif
            }
            else
            {
              #if PLAYCARD_DISABLE // if you want use play card turn off this
                *ScanResult = FE_NOT_LOCK;
              #else
                *ScanResult = FE_LOCK;
              #endif
                NEW_SCAN_APP_DBG( printf( "\n FE Not Locked " ); );
            }
            enDVBScanState = STATE_DVB_SCAN_INIT;
            return TRUE;
            break;
    }

    return FALSE;
}
#endif

void MApp_Scan_SetScanState(EN_SCAN_STATE state)
{
    enScanState = state;
}

void MApp_DTV_ExitScanPauseState(void)
{
    fEndHalt = TRUE;
    enScanState = enPreScanState;
    fReturnToPrevious = TRUE;
}

void MApp_DTV_ExitScanPause2End(void)
{
    fEndHalt = TRUE;
    enPreScanState = enScanState;
    enScanState = STATE_SCAN_END;
}

void MApp_DTV_ExitScanPause2Menu(void)
{
    fEndHalt = TRUE;
    enPreScanState = enScanState;
    enScanState = STATE_SCAN_EXIT_MAIN_MENU;
}

#if ENABLE_DVBC
static void _MApp_DTV_Scan_InitSymbolRate(void)
{
    U16 u16Sym;
    if (g_enScanType == SCAN_TYPE_AUTO || g_enScanType == SCAN_TYPE_NETWORK)
    {
    #if (!BLOADER)
        if (DVBCSymbolRateScanType) //auto mode
    #else
        if (1)
    #endif
        {
        #if CHAKRA3_AUTO_TEST
            U16 u16AT_Symbol = MApp_AT_Get_SymbolSetting();
            if(u16AT_Symbol!= 0xFFFF)
            {
                if((u16AT_Symbol>9999)||(u16AT_Symbol<1))
                    u16Sym = 6875;
                else
                    u16Sym = u16AT_Symbol;
                u16AT_Symbol = 0xFFFF;
            }
            else
        #endif
            {
            if (IS_NORDIC_COUNTRY(OSD_COUNTRY_SETTING))
                u16Sym = DEFAULT_DVBC_NORDIG_SYMBOL_RATE;
            else if(OSD_COUNTRY_SETTING == E_CHINA)
                u16Sym = DEFAULT_DVBC_CHINA_SYMBOL_RATE;
            else
                u16Sym = DEFAULT_DVBC_SYMBOL_RATE;
            }
            MApp_CadtvManualTuning_SetSymbol(u16Sym);
        }
    }
}

/*static*/ BOOLEAN _MApp_DTV_Scan_IncreaseModulationMode(void)
{
    EN_CAB_CONSTEL_TYPE eQam = MApp_CadtvManualTuning_GetQamType();
    return MApp_CadtvManualTuning_SetQamType(++eQam);
}

static void _MApp_DTV_Scan_InitDVBCScanFlags(void)
{
    memset(&_stDVBCScanFlags, 0, sizeof(_DVBC_SCAN_FLAG));
    _stDVBCScanFlags.bInitScanState = 1;
}


static void _MApp_DTV_Scan_InitModulationMode(void)
{
    if (g_enScanType == SCAN_TYPE_AUTO || g_enScanType == SCAN_TYPE_NETWORK)
    {
        #if CHAKRA3_AUTO_TEST
        U16 u16AT_Qam = MApp_AT_Get_QamSetting();
        if(u16AT_Qam != 0xFFFF)
        {
            if(u16AT_Qam > CAB_QAM256)
                u16AT_Qam = CAB_QAM256;
            MApp_CadtvManualTuning_SetQamType((EN_CAB_CONSTEL_TYPE)u16AT_Qam);
            u16AT_Qam = 0xFFFF;
        }
        else
        #endif
        {
            MApp_CadtvManualTuning_SetQamType(CAB_QAM16);
        }
    }
}

static void _MApp_DTV_Scan_AddNITFreqIntoScanTbl(void)
{
    MS_CABLE_PARAMETER desc;
    U16 u16RemainFreq;

    while(MApp_SI_GetNextCableParameter(&desc, NULL,NULL,NULL,&u16RemainFreq, TRUE) && u16RemainFreq>0)
    {
        if (FALSE == msAPI_DCFT_IsThisFreqInBuiltinFreqTbl(desc.u32CentreFreq))
        {
            SCAN_DBINFO(printf("@@@%s=>Freq: %lu\n",__FUNCTION__, desc.u32CentreFreq));
            msAPI_DCFT_SetFreqToNITNewFreqTbl(desc.u32CentreFreq);
        }
        ResetSDTParsingParameter(); //reset Params for next GetNextCableParameter
    }
}

static BOOLEAN _MApp_DTV_Scan_GetTPSettingFromNITParams(MS_TP_SETTING *pstTPSetting)
{
    MS_CABLE_PARAMETER desc;
    U16 u16RemainFreq;
    if (NULL == pstTPSetting)
        return FALSE;

    U32 u32InitFreq = MApp_CadtvManualTuning_GetFrequency();

    ResetSDTParsingParameter(); //reset Params for next GetNextCableParameter

    while(MApp_SI_GetNextCableParameter(&desc, NULL,NULL,NULL,&u16RemainFreq, TRUE))
    {
        pstTPSetting->u32Frequency = desc.u32CentreFreq/10;
        pstTPSetting->u8Modulation = desc.u8Modulation - 1;
        pstTPSetting->u32Symbol_rate = desc.u32Symbol_rate/10;
        pstTPSetting->enBandWidth = E_RF_CH_BAND_8MHz;

        if(u32InitFreq != pstTPSetting->u32Frequency)
            return TRUE;  // Find the new freq different from init...return TRUE. otherwise find next
    }
    return FALSE;

#if 0
    if (MApp_SI_GetNextCableParameter(&desc, NULL, NULL, NULL, &u16RemainFreq, TRUE))
    {
        pstTPSetting->u32Frequency = desc.u32CentreFreq/10;
        pstTPSetting->u8Modulation = desc.u8Modulation - 1;
        pstTPSetting->u32Symbol_rate = desc.u32Symbol_rate/10;
        pstTPSetting->enBandWidth = E_RF_CH_BAND_8MHz;
        ResetSDTParsingParameter(); //reset Params for next GetNextCableParameter
        return TRUE;
    }
    else
    {
        return FALSE;
    }
#endif
}


BOOLEAN _MApp_DTV_Scan_SetCableTPSetting(_DVBC_SCAN_FLAG *stScanFlag, MS_TP_SETTING *pstTPSetting)
{
    BOOL bTuenOtherQamMode = FALSE;
    if (NULL == pstTPSetting || NULL == stScanFlag)
        return FALSE;

    if (g_enScanType == SCAN_TYPE_MANUAL)
    {
        pstTPSetting->u32Frequency = MApp_CadtvManualTuning_GetFrequency();
        pstTPSetting->enBandWidth = E_RF_CH_BAND_8MHz;
        pstTPSetting->u32Symbol_rate = MApp_CadtvManualTuning_GetSymbol();
        pstTPSetting->u8Modulation = (U8)MApp_CadtvManualTuning_GetQamType();
        pstTPSetting->bAutoSRFlag = 0;
        pstTPSetting->bAutoQamFlag = 0;
        return TRUE;
    }
    else if (g_enScanType == SCAN_TYPE_AUTO)
    {
        printf("%s,%d,g_enScanType == SCAN_TYPE_AUTO\r\n",__FUNCTION__,__LINE__);
        if (stScanFlag->bInitScanState)
        {
            stScanFlag->bInitScanState = 0;
            bTuenOtherQamMode = FALSE;
        }
        else if (!stScanFlag->bFrontEndLock && !stScanFlag->bInitScanState)
        {   //tune the other qam mode when fornt-end unlock
        #if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)    \
           ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA)     \
           ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON)   \
           ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA)   \
           ) // T4 support auto qam     //verity 0115
            bTuenOtherQamMode = FALSE;
        #else
            bTuenOtherQamMode = _MApp_DTV_Scan_IncreaseModulationMode();
        #endif
        }
        else
        {
            // tune next frequency
            bTuenOtherQamMode = FALSE;
            stScanFlag->bFrontEndLock = 0;
            MApp_CadtvManualTuning_SetQamType(CAB_QAM16);
        }
        if (FALSE == bTuenOtherQamMode)
        {
            _MApp_DTV_Scan_InitModulationMode();
            if (NULL == (pstTPSetting->u32Frequency = msAPI_DCFT_GetBuiltInNextFreq(0)))
            {
#if 0   //auto(blind) scan don't consider the NIT frequencies
                //Built-in frequencies have been scanned over, change to NIT frequency table
                if (NULL == (pstTPSetting->u32Frequency = msAPI_DCFT_GetNITNextFreq()))
#endif
                    return FALSE;
            }
        }
        pstTPSetting->enBandWidth = E_RF_CH_BAND_8MHz;
        pstTPSetting->u32Symbol_rate = MApp_CadtvManualTuning_GetSymbol();
        pstTPSetting->u8Modulation = (U8)MApp_CadtvManualTuning_GetQamType();
        pstTPSetting->bAutoQamFlag = 1;
    #if (!BLOADER)
        if (DVBCSymbolRateScanType)
            pstTPSetting->bAutoSRFlag = 1;
        else
            pstTPSetting->bAutoSRFlag = 0;
    #else
        pstTPSetting->bAutoSRFlag = 1;
    #endif
        return TRUE;
    }
    else if (g_enScanType == SCAN_TYPE_NETWORK)
    {
        printf("%s,%d,g_enScanType == SCAN_TYPE_NETWORK\r\n",__FUNCTION__,__LINE__);
        if (stScanFlag->bInitScanState)
        {
            stScanFlag->bInitScanState = 0;
            bTuenOtherQamMode = FALSE;
        #if (!BLOADER)
            if (!DVBCFreqScanType)  //manual frequency
            {
#if 1   //home channel frequency is independent with built-in frequency
                pstTPSetting->u32Frequency = MApp_CadtvManualTuning_GetFrequency();
                pstTPSetting->enBandWidth = E_RF_CH_BAND_8MHz;
                pstTPSetting->u32Symbol_rate = MApp_CadtvManualTuning_GetSymbol();
                pstTPSetting->u8Modulation = (U8)MApp_CadtvManualTuning_GetQamType();
                pstTPSetting->bAutoQamFlag = 1;
            #if (!BLOADER)
                if (DVBCSymbolRateScanType)
                    pstTPSetting->bAutoSRFlag = 1;
                else
                    pstTPSetting->bAutoSRFlag = 0;
            #else
                pstTPSetting->bAutoSRFlag = 1;
            #endif
                //init built-in frequency next starting frequency index
                msAPI_DCFT_GetBuiltInNextFreq(MApp_CadtvManualTuning_GetFrequency());
                return TRUE;
#else
                if (NULL == (pstTPSetting->u32Frequency = msAPI_DCFT_GetBuiltInNextFreq(MApp_CadtvManualTuning_GetFrequency())))
                {
                    return FALSE;
                }
                else
                {
                    pstTPSetting->enBandWidth = E_RF_CH_BAND_8MHz;
                    pstTPSetting->u32Symbol_rate = MApp_CadtvManualTuning_GetSymbol();
                    pstTPSetting->u8Modulation = (U8)MApp_CadtvManualTuning_GetQamType();
                    return TRUE;
                }
#endif
            }
        #endif
        }
        else if (!stScanFlag->bNITScanAvailable && !stScanFlag->bFrontEndLock && !stScanFlag->bInitScanState)
        {   //tune the other qam mode when fornt-end unlock
        #if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)    \
           ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA)     \
           ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON)   \
           ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA)   \
           ) // T4 support auto qam     //verity 0115
            bTuenOtherQamMode = FALSE;
        #else
            bTuenOtherQamMode = _MApp_DTV_Scan_IncreaseModulationMode();
        #endif
        }
        else
        {
            // tune next frequency
            bTuenOtherQamMode = FALSE;
            stScanFlag->bFrontEndLock = 0;
            if (!stScanFlag->bNITScanAvailable)
                MApp_CadtvManualTuning_SetQamType(CAB_QAM16);
        }
        if (FALSE == bTuenOtherQamMode)
        {
            if (TRUE == _MApp_DTV_Scan_GetNITAvailableFlag())
            {
                //NIT available, get tp setting by NIT parameters
                return _MApp_DTV_Scan_GetTPSettingFromNITParams(pstTPSetting);
            }
            else
            {
                //find built-in frequencies first, and then nit new frequencies again
                _MApp_DTV_Scan_InitModulationMode();
                if (NULL == (pstTPSetting->u32Frequency = msAPI_DCFT_GetBuiltInNextFreq(0)))
                {   //Built-in frequencies have been scanned over, change to NIT frequency table
                   if (NULL == (pstTPSetting->u32Frequency = msAPI_DCFT_GetNITNextFreq()))
                        return FALSE;
                }
            }
        }
        pstTPSetting->enBandWidth = E_RF_CH_BAND_8MHz;
        pstTPSetting->u32Symbol_rate = MApp_CadtvManualTuning_GetSymbol();
        pstTPSetting->u8Modulation = (U8)MApp_CadtvManualTuning_GetQamType();
        pstTPSetting->bAutoQamFlag = 1;
    #if (!BLOADER)
        if (DVBCSymbolRateScanType)
            pstTPSetting->bAutoSRFlag = 1;
        else
            pstTPSetting->bAutoSRFlag = 0;
    #else
        pstTPSetting->bAutoSRFlag = 1;
    #endif
        return TRUE;
    }
    else
        return FALSE;
}


static void _MApp_DTV_Scan_SetNITAvailableFlag(BOOLEAN bNITFlag)
{
    _stDVBCScanFlags.bNITScanAvailable = bNITFlag;
}

static BOOLEAN _MApp_DTV_Scan_GetNITAvailableFlag(void)
{
    return (_stDVBCScanFlags.bNITScanAvailable) ? TRUE : FALSE;
}


static BOOLEAN _MApp_Scan_DVBC_QuickInstall_ProcessKey(void) // kk 0815-1
{
    MApp_ProcessUserInput();

    switch (u8KeyCode)
    {
            case KEY_POWER:
            case KEY_1:
            case KEY_2:
            case KEY_3:
            case KEY_4:
            case KEY_5:
            case KEY_6:
            case KEY_7:
            case KEY_8:
            case KEY_9:
            case KEY_0:
            case KEY_UP:
            case KEY_DOWN:
            case KEY_CHANNEL_MINUS:
            case KEY_CHANNEL_PLUS:
            case KEY_INPUT_SOURCE:
            case KEY_TV_INPUT:
            case KEY_POWERONLY:
            case KEY_AV:
                u8KeyCode = KEY_NULL;
                return FALSE;
            break;
            default:
                break;
    }
    u8KeyCode = KEY_NULL;
    return TRUE ;
}

static BOOLEAN _MApp_Scan_DVBC_QuickInstall_Init(void)
{
    u8NumOfVchFound = 0;

    if (FALSE == MApp_SI_Scan_Init())
        return FALSE;

    u16NumOfSrvAdd = 0;

    return TRUE;

}

static BOOLEAN _MApp_Scan_DVBC_QuickInstall_AddOneDTVPchVchs(void)
{
    SI_SHORT_DTV_CHANNEL_INFO *pastVirtualCh;
    SI_DTV_CHANNEL_INFO stDtvPgmData;
    SI_DTVPROGRAMID stDtvIDTable;
    MS_CABLE_PARAMETER desc;
    U16 u16RemainFreq;
    U8 u8NumOfVch;
    U8 u8Loop_1;
    U8 u8NumOfActiveCh = 0;
    MEMBER_SERVICETYPE eServiceType;
    WORD wPosition;
    BOOLEAN bFull, bResult = FALSE;
    U8 au8NetWorkName[MAX_NETWORK_NAME];
    U8 len;

    u8NumOfVch = MApp_SI_GetScanNumOfPatItem();
    pastVirtualCh = MApp_SI_Get_PastVirtualCh();

    memset(&stDtvIDTable, 0, sizeof(stDtvIDTable));
    if (u8NumOfVch>0)
    {

        stDtvIDTable.wNetwork_ID = pastVirtualCh[0].wNetwork_ID;
        stDtvIDTable.wTransportStream_ID = pastVirtualCh[0].wTransportStream_ID;
        stDtvIDTable.wOriginalNetwork_ID = pastVirtualCh[0].wOriginalNetwork_ID;
        stDtvIDTable.cRFChannelNumber = INVALID_IDINDEX;
        msAPI_Tuner_Get_CELL_ID(&stDtvIDTable.wCellID);

        if (MApp_SI_GetNextCableParameter(&desc,NULL,NULL,NULL, &u16RemainFreq, TRUE))
        {
            stDtvIDTable.u32Frequency = desc.u32CentreFreq;
            stDtvIDTable.u32SymbRate = desc.u32Symbol_rate;
            stDtvIDTable.QamMode = desc.u8Modulation;
            ResetSDTParsingParameter(); //reset Params for next GetNextCableParameter
        }

        if ((TRUE == MApp_SI_Get_NetWorkName(au8NetWorkName,&len,MAX_NETWORK_NAME)) /*&& (0!=au8NetWorkName[0])*/)
        {
            msAPI_CM_SetCurrentNetworkName(au8NetWorkName, len);
        }

        SCAN_DBINFO(printf("@@@NID:%d, TSID:%d, ONID:%d, Freq:%lu, sym:%lu, qam:%d, NetworkName:%s\n",stDtvIDTable.wNetwork_ID,stDtvIDTable.wTransportStream_ID,
        stDtvIDTable.wOriginalNetwork_ID,stDtvIDTable.u32Frequency,stDtvIDTable.u32SymbRate,stDtvIDTable.QamMode,au8NetWorkName));

        if(msAPI_SI_AddProgramIDTable(&stDtvIDTable,&stDtvPgmData.bIDIdex))
        {
            return FALSE;
        }
        for(u8Loop_1=0; u8Loop_1<u8NumOfVch; u8Loop_1++)
        {
            MApp_SI_GetDtvPmgData(&pastVirtualCh[u8Loop_1], u8Loop_1, &stDtvPgmData);
            if( MApp_SI_Action_CheckServiceInfo( &stDtvPgmData ) == FALSE )
            {
                continue;
            }
            if(u8NumOfActiveCh != u8Loop_1)
            {
                memcpy(&pastVirtualCh[u8NumOfActiveCh], &pastVirtualCh[u8Loop_1], sizeof(SI_SHORT_DTV_CHANNEL_INFO));
            }

            pastVirtualCh[u8NumOfActiveCh].stCHAttribute.bServiceType = stDtvPgmData.stCHAttribute.bServiceType;

            if( TRUE != msAPI_CM_GetServiceTypeAndPositionWithPCN(stDtvPgmData.bIDIdex, stDtvPgmData.wService_ID, &eServiceType, &wPosition) )
            {
                stDtvPgmData.stCHAttribute.bIsServiceIdOnly = FALSE;////Inancb 02102009: do not show "INVALID SERVICE" popup when tuning the channel first time
                bResult = msAPI_SI_AddProgram(&stDtvIDTable, &stDtvPgmData,&bFull, FALSE);
            }
            else
            {
                MEMBER_SI_SERVICETYPE bType;
                bType=msAPI_SI_ToSI_Service_Type(eServiceType);
                bResult = msAPI_SI_UpdateQuickInstallProgram(bType, wPosition, &stDtvPgmData);
            }
            u8NumOfActiveCh++;
        }

        msAPI_SI_RemoveQuickInstallMismatchedProgram(pastVirtualCh, u8NumOfVch, stDtvPgmData.bIDIdex, msAPI_SI_ToSI_Service_Type(E_SERVICETYPE_DTV));
        msAPI_SI_RemoveQuickInstallMismatchedProgram(pastVirtualCh, u8NumOfVch, stDtvPgmData.bIDIdex, msAPI_SI_ToSI_Service_Type(E_SERVICETYPE_RADIO));
#if (NORDIG_FUNC)
        msAPI_SI_RemoveQuickInstallMismatchedProgram(pastVirtualCh, u8NumOfVch, stDtvPgmData.bIDIdex, msAPI_SI_ToSI_Service_Type(E_SERVICETYPE_DATA));
#endif
    }
    return bResult;
}

static void _MApp_Scan_DVBC_QuickInstall_RemoveMismatchedTS(void)
{
    U16 au16TsId[MAX_MUX_NUMBER_NORMAL];
    U8 u8TsIdNum;
    MApp_Dmx_DVBC_QuickInstallGetTsIDs(au16TsId, &u8TsIdNum, MAX_MUX_NUMBER_NORMAL);
    msAPI_CM_RemoveQuickInstallMismatchedTS(au16TsId, u8TsIdNum);
}

static void _MApp_Scan_DVBC_QuickInstall_End(void)
{
    MApp_SI_Scan_End();

#if (ENABLE_DTV_EPG)
    MApp_Epg_Init();
    MApp_EpgTimer_InitTimerSettings(TRUE);
#endif

    if(TRUE != msAPI_CM_ArrangeDataManager(TRUE, FALSE))
    {
        SCAN_DBINFO( printf( "msAPI_CM_ArrangeDataManager FAIL !! \n" ));
    }

#if 0//ENABLE_SCAN_CM_DEBUG
    msAPI_CM_PrintAllProgram();
#endif
}

BOOLEAN MApp_Scan_DVBC_QuickInstall_GetProcessedFlag(void)
{
    return (_bQuickInstallProcessed)? TRUE : FALSE;
}

BOOLEAN MApp_Scan_DVBC_QuickInstall_ChList(void)
{
    DVBC_QUICK_INSTALL_CHLIST_STATE enQuickInstallState;
    DMX_DVBC_QUICK_INSTALL_RET_STATE enDmxScanTblRetState;
    BOOLEAN bContinue = TRUE;
    BOOLEAN retVal = FALSE;

    enQuickInstallState = QUICK_INSTALL_STATE_INIT;
    u8KeyCode = KEY_NULL;

    SCAN_DBINFO(printf("!!!!!!DVBC_QuickInstall Started!!!!!!\n"));

    while (bContinue)
    {
        if(_MApp_Scan_DVBC_QuickInstall_ProcessKey() == FALSE)
        {
            enQuickInstallState = QUICK_INSTALL_STATE_END;
            retVal = TRUE;
        }
        switch (enQuickInstallState)
        {
            case QUICK_INSTALL_STATE_INIT:
            {
                if (TRUE == _MApp_Scan_DVBC_QuickInstall_Init())
                {
                    MApp_Dmx_DVBC_QuickInstallStateInit();
                    enQuickInstallState = QUICK_INSTALL_STATE_SCAN_TABLE;
                }
                break;
            }
            case QUICK_INSTALL_STATE_SCAN_TABLE:
            {
                enDmxScanTblRetState = MApp_Dmx_DVBC_QuickInstallScanTables();
                switch (enDmxScanTblRetState)
                {
                    case DMX_QUICK_INSTALL_RET_STATE_UPDATE_CHLIST:
                    {
                        enQuickInstallState = QUICK_INSTALL_STATE_UPDATE_CHLIST;
                        break;
                    }
                    case DMX_QUICK_INSTALL_RET_STATE_REMOVE_MISSING_MUX:
                    {
                        enQuickInstallState = QUICK_INSTALL_STATE_REMOVE_MISSING_MUX;
                        break;
                    }
                    case DMX_QUICK_INSTALL_RET_STATE_END:
                    {
                        enQuickInstallState = QUICK_INSTALL_STATE_END;
                        break;
                    }
                    case DMX_QUICK_INSTALL_RET_STATE_NONE:
                    {
                        enQuickInstallState = QUICK_INSTALL_STATE_SCAN_TABLE;
                        break;
                    }
                    default:
                    {
                        enQuickInstallState = QUICK_INSTALL_STATE_END;
                        break;
                    }
                }
                break;
            }
            case QUICK_INSTALL_STATE_UPDATE_CHLIST:
            {
                _MApp_Scan_DVBC_QuickInstall_AddOneDTVPchVchs();
                enQuickInstallState = QUICK_INSTALL_STATE_SCAN_TABLE;
                break;
            }
            case QUICK_INSTALL_STATE_REMOVE_MISSING_MUX:
            {
                _MApp_Scan_DVBC_QuickInstall_RemoveMismatchedTS();
                enQuickInstallState = QUICK_INSTALL_STATE_END;
                break;
            }
            case QUICK_INSTALL_STATE_END:
            {
                _MApp_Scan_DVBC_QuickInstall_End();
                bContinue = FALSE;
                break;
            }
            default:
                break;
        }
    }
    SCAN_DBINFO(printf("!!!!!!DVBC_QuickInstall Finished!!!!!!\n"));
    return retVal;
}

#endif // #if ENABLE_DVBC


#if NTV_FUNCTION_ENABLE

static U8 _bSelectFavoriteNetwork=INVALID_NETWORKINDEX;

void MApp_DTV_Scan_SetSelectFavoriteNetwork(U8 cNetworkIndex)
{
    _bSelectFavoriteNetwork=cNetworkIndex;
}

U8 MApp_DTV_Scan_GetSelectFavoriteNetwork(void)
{
    return _bSelectFavoriteNetwork;
}

void MApp_Set_ScanGoRegion_Status(BOOLEAN bStatus)
{
    bScanGoRegion = bStatus;
}

BOOLEAN MApp_Get_ScanGoRegion_Status(void)
{
    return bScanGoRegion;
}

#endif // #if NTV_FUNCTION_ENABLE




#if ENABLE_DVB_T2

void MApp_DTV_Scan_T2_InitVariables(void)
{
    //_bScanT2 = DEMO_NUM;
    _bScanT2 = SCAN_DEMOD_NOT_DVBT_AND_T2;
    _bInMonitorT2Status = TRUE;
    MApp_SI_FreeT2DelSysDesc();
}

BOOLEAN MApp_DTV_Scan_T2_InSignalMonitorStatus(void)
{
    return _bInMonitorT2Status;
}

void MApp_DTV_Scan_T2_EnterSignalMonitorStatus(BOOLEAN bTrue) //Target: update freq(for monitor and scan)
{
    _bInMonitorT2Status = bTrue;
}

EN_T2_SERVICE_DEMOD MApp_DTV_Scan_T2_GetServiceType(void)
{
    return _bT2ServiceType;
}

void MAPP_DTV_Scan_T2_SetServiceType(EN_T2_SERVICE_DEMOD enSercieType)
{
    _bT2ServiceType = enSercieType;
}

BOOLEAN MApp_DTV_Scan_T2_ForceMonitorT2Signal(void)
{
    return _bForceMonitorT2Signal;
}

void MApp_DTV_Scan_T2_SetForceMonitorT2Signal(BOOLEAN bTrue)
{
    _bForceMonitorT2Signal = bTrue;
}

EN_SCAN_SWITCH_DEMOD MApp_DTV_Scan_T2_ScanCheckSignal(void)
{
    return _bScanT2;
}

#define DEBUG_DTV_SCAN_T2(x)    //x
void MAPP_DTV_Scan_T2_DoScan_2(EN_SCAN_SWITCH_DEMOD bT2Demo,BOOLEAN bIsScanStatus)//bIsScanStatus :0(isn't scan status,ts pass through ci card) 1:(scan status,ts bypass ci card)
{
    //DMX_FILTER_STATUS dmx_status;
    //MS_BOOL bExtSync,bParallel,pbClkInv;
    //DMX_FLOW_INPUT dmx_flow_input;
    //DMX_FLOW endmxflow = DMX_FLOW_PLAYBACK;

    bIsScanStatus=bIsScanStatus;

    //PRINT_CURRENT_LINE();
    DEBUG_DTV_SCAN_T2(printf("MAPP_DTV_Scan_T2_DoScan(bT2Demo=%u, Scan=%u)\n", bT2Demo, bIsScanStatus););

    _bScanT2 = bT2Demo;

    if( IsS2InUse() || IsDVBCInUse() || IsISDBTInUse())
    {
        printf("DVBS,DVBC no need T2!\n");
        _bScanT2 = SCAN_DEMOD_NOT_DVBT_AND_T2;
        return;
    }

    if( !mdev_Cofdm_MSB123X_Ready() )
    {
        //_bScanT2 = DVB_T_DEMOD;
        printf("\nError: MSB123X not Ready!\n");
        //printf("_bScanT2 = DVB_T_DEMOD;\n");
        //return;
    }

#if 0//(ENABLE_OAD && !BLOADER)
    if(bShowOadScanPage)
    {
        printf("bShowOadScanPage!\n");
        //_bScanT2 = DVB_T_DEMOD;
        return;
    }
#endif

#if( ENABLE_PVR )
    if (MApp_PVR_IsRecording())
    {
        //endmxflow = DMX_FLOW_PVR;
        printf("\nWarning: When PVR working, should not chnage tsp path!\n");
        return;
    }
#endif


    SCAN_DBINFO(printf("MAPP_DTV_Scan_T2_DoScan ScanDemodType = %d\n",_bScanT2));
    SCAN_DBINFO(printf("MAPP_DTV_Scan_T2_DoScan bIsScanStatus = %d\n",bIsScanStatus));

    if(_bScanT2 == DVB_T2_DEMOD)
    {
        DEBUG_DTV_SCAN_T2(printf("_bScanT2 == DVB_T2_DEMOD\n"););

        mdev_ControlTSOutput(ENABLE);

        msAPI_Demod_Init(E_INIT_DEMOD_FOR_SCAN, E_DEMODULATOR_TYPE_DVBT2);

        if(bIsScanStatus)
        {
            mdev_CofdmSetPlpGroupID(0,0);
        }
    #if(FRONTEND_DEMOD_T2_TYPE == MSTAR_MSB123X_DVBT2 || FRONTEND_DEMOD_T2_TYPE == MSTAR_MSB101A_DVBT2)
        mdev_Set_Current_DEMOD_TYPE(E_COFDM_EXTERNAL_DVBT2);
        MDrv_SYS_SetPadMux(E_TS1_PAD_SET, E_PARALLEL_IN);
    #endif

#if 0
    #if (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD)
        MApi_DMX_FlowSet(endmxflow, DMX_FLOW_INPUT_EXT_INPUT1, FALSE, TRUE, TRUE);
    #elif (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER)
        MApi_DMX_FlowSet(endmxflow, DMX_FLOW_INPUT_EXT_INPUT0, FALSE, TRUE, FALSE);
    #elif (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)
        MApi_DMX_FlowSet(endmxflow, DMX_FLOW_INPUT_DEMOD, FALSE, TRUE, TRUE);
    #else
      #if (FRONTEND_DEMOD_T2_TYPE == EMBEDDED_DVBT2_DEMOD)
        MApi_DMX_FlowSet(endmxflow, DMX_FLOW_INPUT_DEMOD, FALSE, TRUE, TRUE);
      #else
        MApi_DMX_FlowSet(endmxflow, DMX_FLOW_INPUT_EXT_INPUT0, FALSE, TRUE, FALSE);
      #endif
    #endif
#endif

        MDrv_SYS_SetAGCPadMux(E_SYS_DTV_AGC_PAD_SET_ALL_OFF);

        // What's the rule?
        mdev_ControlAGCOutput(ENABLE);
    }
    else//if(_bScanT2 == DVB_T_DEMOD)
    {
        DEBUG_DTV_SCAN_T2(printf("_bScanT2 == DVB_T_DEMOD\n"););

    #if 0//(FRONTEND_DEMOD_DVBT_TYPE!=MSTAR_MSB124X_DVBT)
        mdev_ControlTSOutput(DISABLE);
        mdev_ControlAGCOutput(DISABLE);
    #endif

        msAPI_Demod_Init(E_INIT_DEMOD_FOR_SCAN, E_DEMODULATOR_TYPE_DVBT);

    #if(FRONTEND_DEMOD_T2_TYPE == MSTAR_MSB123X_DVBT2 || FRONTEND_DEMOD_T2_TYPE == MSTAR_MSB101A_DVBT2)
        mdev_Set_Current_DEMOD_TYPE(E_COFDM_INVALID);
        MDrv_SYS_SetPadMux(E_TS1_PAD_SET, E_PARALLEL_OUT);
        MDrv_SYS_SetPadMux(E_TS0_PAD_SET, E_PARALLEL_IN);
    #endif

        // What's the rule?
        MDrv_SYS_SetAGCPadMux(E_SYS_DTV_AGC_PAD_SET);
    }

    // Setup demod&Tsp path...
#if( ENABLE_PVR )
    if ( MApp_PVR_IsRecording() && (!bIsScanStatus) )
    {
        //endmxflow = DMX_FLOW_PVR;
        msAPI_Demod_SetupTSPath(E_DEMOD_TSP_PATH_CASE_PVR_REC);
    }
    else
#endif
#if ENABLE_CI // For CI case
    if( msAPI_CI_CardDetect()
      &&(!bIsScanStatus)
      )
    {
    #if( ENABLE_CI_PLUS )
        //if(msAPI_Tuner_IsByPassMode())
        if( MApp_CI_Is_CIByPassMode() )
        {
        #if 1
            msAPI_Demod_SetupTSPath(E_DEMOD_TSP_PATH_CASE_CI_BY_PASS);
        #else
            dmx_status = MApi_DMX_Get_FlowInput_Status(endmxflow, &dmx_flow_input, &pbClkInv, &bExtSync, &bParallel);
            if(dmx_flow_input != DMX_FLOW_INPUT_DEMOD)
            {
                MApi_DMX_FlowSet(endmxflow, DMX_FLOW_INPUT_DEMOD, FALSE, TRUE, TRUE);
            }
        #endif
        }
        else
    #endif
        {
        #if 1
            msAPI_Demod_SetupTSPath(E_DEMOD_TSP_PATH_CASE_CI_IN_USE);
        #else
            MDrv_SYS_SetPadMux(E_TS1_PAD_SET, E_PARALLEL_OUT);
            dmx_status = MApi_DMX_Get_FlowInput_Status(DMX_FLOW_PLAYBACK, &dmx_flow_input, &pbClkInv, &bExtSync, &bParallel);
            if(dmx_flow_input != DMX_FLOW_INPUT_EXT_INPUT0)
            {
                MApi_DMX_FlowSet(endmxflow, DMX_FLOW_INPUT_EXT_INPUT0, FALSE, TRUE, TRUE);
            }
        #endif
        }
    }
    else // Normal case
#endif
    {
    #if 1
        msAPI_Demod_SetupTSPath(E_DEMOD_TSP_PATH_CASE_NORMAL);
    #else
        dmx_status = MApi_DMX_Get_FlowInput_Status(endmxflow, &dmx_flow_input, &pbClkInv, &bExtSync, &bParallel);
        if(dmx_flow_input != DMX_FLOW_INPUT_DEMOD)
        {
            #if (FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB124X_DVBT)
                MApi_DMX_FlowSet(endmxflow, DMX_FLOW_INPUT_EXT_INPUT0, FALSE, TRUE, FALSE);
            #else
                MApi_DMX_FlowSet(endmxflow, DMX_FLOW_INPUT_DEMOD, FALSE, TRUE, TRUE);
            #endif
        }
    #endif
    }

}

#endif // #if ENABLE_DVB_T2

#if(ENABLE_S2)
EN_SCAN_STATE MApp_Get_enScanState(void)
{
    return enScanState;
}
#endif

#if(ASTRA_HD_ENABLE)
void MApp_Set_S2ScanParamWithCurProg(void)
{
    U8 u8Polarity = 0;

    msAPI_CM_GetCurrentSatParam(&_afe_param[0].SatelliteId,&_afe_param[0].u32S2Frequency,&_afe_param[0].u16SymbolRate, &u8Polarity);

    _afe_param[0].u8Polarity = u8Polarity;

    _lnb_satelliteID[_u8CurScanSATPos] = _afe_param[0].SatelliteId;
}
#endif


U16 MApp_Scan_Get_CurRFChannel(void)
{
    return u8RFCh;
}

void MApp_Scan_Set_CurRFChannel(U16 u16RFChannel)
{
    u8RFCh = u16RFChannel;
}


/***************************************************************************************/

#undef MAPP_SCAN_A_C

