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

#ifndef MAPP_SCAN_H
#define MAPP_SCAN_H

#include "datatype.h"
#include "msAPI_Global.h"

#include "msAPI_Tuner.h"
#include "msAPI_DTVSystem.h"

#include "MApp_Exit.h"


//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
#if(ASTRA_HD_ENABLE)
#if ( ENABLE_S2)
#define ENABLE_S2_NIT_QUICK_SCAN 1
#else
#define ENABLE_S2_NIT_QUICK_SCAN 0
#endif
#endif
#ifndef ENABLE_S2_NIT_QUICK_SCAN
#define ENABLE_S2_NIT_QUICK_SCAN 0
#endif

// debug for scan
#define ENABLE_SCAN_CM_DEBUG            0 //for CM debugging

//------------------------------------------------------------------------------
// Enums
//------------------------------------------------------------------------------
#if(ENABLE_S2)
typedef enum
{
     BLINDSCAN_READY,
     BLINDSCAN_H_LoLOF,
     BLINDSCAN_V_LoLOF,
     BLINDSCAN_H_HiLOF,
     BLINDSCAN_V_HiLOF,
     BLINDSCAN_GETTP_FINISH,

     BLINDSCAN_STATUS_NUM
}BLINDSCAN_STATUS;
#endif


typedef enum
{
    STATE_SCAN_INIT,
    STATE_SCAN_NEXT_CHANNEL,
    STATE_SCAN_SEARCH_RF_CHANNEL,
    STATE_SCAN_GET_PROGRAMS,
    STATE_SCAN_NIT_QUICK_SCAN_GET_NIT,
    STATE_SCAN_NIT_QUICK_SCAN_WAIT_SDT,
    STATE_SCAN_NIT_QUICK_SCAN_SAVE_PROGRAMS,
    STATE_SCAN_SAVE_PROGRAMS,
    STATE_SCAN_PAUSE,
    STATE_SCAN_END,
    STATE_SCAN_GOTO_STANDBY,
    STATE_SCAN_EXIT_MAIN_MENU,
    STATE_SCAN_INTERRUPT,
#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
    STATE_SCAN_WAIT,
#endif

#if(ENABLE_S2)
    STATE_BLIND_START_SET_FIRST_SAT,
    STATE_BLIND_START,
    STATE_BLIND_TURNMOTOR,
    STATE_BLIND_NEXTFREQ,
    STATE_BLIND_WAITFINISH,
    STATE_BLIND_GETTPLIST,
    STATE_BLIND_END,
    STATE_START,
    STATE_TURNMOTOR,
    STATE_TUNE2RF,
    STATE_WAITLOCK,
    STATE_SETTPS,
    STATE_FIND_NIT_FREQ,
    STATE_IDLE,
    STATE_S2_SCAN_WAIT,
#if(ENABLE_S2_FAST_SCAN)	
	STATE_SCAN_FNT_GET_PROGRAMS,
	STATE_SCAN_PAT_PMT_GET_PROGRAMS,
#endif //#if(ENABLE_S2_FAST_SCAN)	
#if(ENABLE_S2_NIT_QUICK_SCAN)
    STATE_S2_SCAN_NIT_QUICK_SCAN_GET_NIT,
    STATE_S2_SCAN_NIT_QUICK_SCAN_WAIT_SGT,
#endif
#endif

#if(ENABLE_ATSC)
  #if (CHANNEL_ADD_AND_MERGE_FUNC==ENABLE)
    STATE_SCAN_RELEASE_BUF,
    STATE_SCAN_DB_PREPROCESS,
  #endif
    STATE_SCAN_GET_TPSETTINGS,
    STATE_SCAN_TUNE_TO_RF_CH,
    STATE_SCAN_ZIG_ZAG,
    STATE_SCAN_CHANGE_QAM_MODE,
    STATE_SCAN_CHECK_FE_LOCK_STATUS,
    STATE_SCAN_CHECK_VD_LOCK_STATUS,
    STATE_SCAN_GET_TABLE,
    STATE_SCAN_SAVE_SETTING,
    STATE_SCAN_SCAN_END,
    STATE_SCAN_CHANGE_SPECTRUM_MODE,
#endif

} EN_SCAN_STATE;

#if ENABLE_ATSC_SCAN_NEW_MODE
typedef enum
{
    ATSC_SCAN_TYPE_AIR_DTV,
    ATSC_SCAN_TYPE_AIR_ATV,
    ATSC_SCAN_TYPE_CABLE_DTV,
    ATSC_SCAN_TYPE_CABLE_ATV,
    ATSC_SCAN_TYPE_NUM,
} EN_ATSC_SCAN_TYPE;
#endif

#if ENABLE_DVBC
typedef enum
{
    QUICK_INSTALL_STATE_INIT = 0,
    QUICK_INSTALL_STATE_SCAN_TABLE,
    QUICK_INSTALL_STATE_UPDATE_CHLIST,
    QUICK_INSTALL_STATE_REMOVE_MISSING_MUX,
    QUICK_INSTALL_STATE_END,
}DVBC_QUICK_INSTALL_CHLIST_STATE;
#endif



typedef enum
{
    STATE_DVB_SCAN_INIT,
    STATE_DVB_SCAN_INIT_DEMODE,
    STATE_DVB_SCAN_CHECK_LOCK,
} EN_DVB_SCAN_STATE;

typedef enum
{
    FTA,
    ALL,
    SCAN_SRV_TYPE_NUM
} EN_SCAN_SRV_TYPE;

#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
typedef enum
{
    LOSS_SIGNAL_INIT,
    LOSS_SIGNAL_CONFIRM_MSG,
    LOSS_SIGNAL_RETUNE,
    LOSS_SIGNAL_NO_RETUNE,
    LOSS_SIGNAL_RETURN_TO_NOSIGNAL,
    LOSS_SIGNAL_RETURN_ORIGINAL_RF
}EN_LOSS_SIGNAL_STATE;
#endif

#if ENABLE_DVB_T2
typedef struct _T2_DESC_DEL_SYS_DATA
{
    BOOLEAN bUsed;
    U8 u8PLP_ID;
    struct _T2_DESC_DEL_SYS_DATA *next;
} T2_DESC_DEL_SYS_DATA; // Cable delivery system descript

typedef enum
{
    DVB_T_DEMOD,
    DVB_T2_DEMOD,
    SCAN_DEMOD_NOT_DVBT_AND_T2,
    DEMO_NUM
}EN_SCAN_SWITCH_DEMOD;

typedef enum
{
    DVBT_SERVICE,
    DVBT2_SERVICE,
    SERVICE_NUM
}EN_T2_SERVICE_DEMOD;
#endif // #if ENABLE_DVB_T2

#if ENABLE_DVBC
typedef struct
{
    U32 bNITScanAvailable           :1;
    U32 bCheckNewFreqfromNIT    :1;
    U32 bFrontEndLock                   :1;
    U32 bInitScanState                  :1;
    U32 reserved                            :28;
}_DVBC_SCAN_FLAG;
#endif

//------------------------------------------------------------------------------
// Function prototypes
//------------------------------------------------------------------------------
#ifdef MAPP_SCAN_A_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

INTERFACE void MApp_Scan_State_Init(void);
INTERFACE EN_RET MApp_DTV_Scan( void );
#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
INTERFACE void MApp_DTV_Scan_Retune_Confirm_Yes(void);
INTERFACE void MApp_DTV_Scan_Retune_Confirm_No(void);
INTERFACE void MApp_DTV_Scan_NetworkChange_Cornfim_OK(void);
INTERFACE void MApp_DTV_Scan_NetworkChange_Cornfim_NO(void);
INTERFACE EN_LOSS_SIGNAL_STATE MApp_DTV_Scan_GetLossSignalState(void);
INTERFACE void MApp_DTV_Scan_SetLossSignalState(EN_LOSS_SIGNAL_STATE enState);
INTERFACE void MApp_DTV_Scan_Set_LossSignalFlag(BOOLEAN bLossSignal);
INTERFACE EN_RET MApp_DTV_Scan_Update_Mux( void );
INTERFACE void MApp_DTV_Scan_Set_UpdateMethod(BOOLEAN bAddMux, BOOLEAN bRemoveMux ,BOOLEAN bCellRemove, BOOLEAN bFreqChange);
INTERFACE void MApp_DTV_Scan_Update_Mux_State_Init( void );
#endif
INTERFACE BOOLEAN MApp_DTV_Scan_Init(void);
INTERFACE void MApp_DTV_Scan_End(BOOLEAN bSkipDupSrvRemove);

#if(ENABLE_DTV)
INTERFACE BOOLEAN MApp_DVB_Scan( MS_TP_SETTING *pstTPSetting, BOOLEAN *ScanResult);
#endif

INTERFACE EN_DVB_TYPE MApp_DVBType_GetCurrentType(void);
#if 1//ENABLE_DVBC
INTERFACE void MApp_DVBType_SetCurrentType(U8 SelectDVBType);

INTERFACE EN_DVB_TYPE MApp_DVBType_GetPrevType(void);
INTERFACE void MApp_DVBType_SetPrevType(EN_DVB_TYPE SelectDVBType);
#endif

//ZUI:
INTERFACE void MApp_Scan_SetScanState(EN_SCAN_STATE state);
INTERFACE void MApp_DTV_ExitScanPauseState(void);
INTERFACE void MApp_DTV_ExitScanPause2End(void);
INTERFACE void MApp_DTV_ExitScanPause2Menu(void);

#if ENABLE_DVBC
INTERFACE BOOLEAN MApp_Scan_DVBC_QuickInstall_GetProcessedFlag(void);
INTERFACE BOOLEAN MApp_Scan_DVBC_QuickInstall_ChList(void);
INTERFACE void _MApp_DTV_Scan_GetCableScanFlags(_DVBC_SCAN_FLAG * _pOadDVBCScanFlags);
INTERFACE BOOLEAN _MApp_DTV_Scan_SetCableTPSetting(_DVBC_SCAN_FLAG *stScanFlag, MS_TP_SETTING *pstTPSetting);
#endif

#if NTV_FUNCTION_ENABLE
INTERFACE void MApp_DTV_Scan_SetSelectFavoriteNetwork(U8 cNetworkIndex);
INTERFACE U8 MApp_DTV_Scan_GetSelectFavoriteNetwork(void);
INTERFACE void MApp_Set_ScanGoRegion_Status(BOOLEAN bStatus);
INTERFACE BOOLEAN MApp_Get_ScanGoRegion_Status(void);
#endif

#if ENABLE_DVB_T2
INTERFACE void MApp_DTV_Scan_T2_InitVariables(void);
INTERFACE EN_T2_SERVICE_DEMOD MApp_DTV_Scan_T2_GetServiceType(void);
INTERFACE void MAPP_DTV_Scan_T2_SetServiceType(EN_T2_SERVICE_DEMOD enSercieType);
INTERFACE void MApp_DTV_Scan_T2_EnterSignalMonitorStatus(BOOLEAN bTrue);
INTERFACE BOOLEAN MApp_DTV_Scan_T2_InSignalMonitorStatus(void);
INTERFACE EN_SCAN_SWITCH_DEMOD MApp_DTV_Scan_T2_ScanCheckSignal(void);

#if 0
    #define MAPP_DTV_Scan_T2_DoScan( bT2Demo, bIsScanStatu) do {    \
            msDebug_ANSI_SetColorText(E_FONT_COLOR_BLACK);              \
            msDebug_ANSI_SetColorText(E_FONT_BACKGROUND_COLOR_YELLOW);   \
            printf("%u : %s : call MAPP_DTV_Scan_T2_DoScan()\n", __LINE__, __FILE__ ); \
            msDebug_ANSI_AllAttrOffText();                      \
            MAPP_DTV_Scan_T2_DoScan_2( bT2Demo, bIsScanStatu);  \
        } while(0)
#else
    #define MAPP_DTV_Scan_T2_DoScan( bT2Demo, bIsScanStatu) MAPP_DTV_Scan_T2_DoScan_2( bT2Demo, bIsScanStatu)
#endif

INTERFACE void MAPP_DTV_Scan_T2_DoScan_2(EN_SCAN_SWITCH_DEMOD bT2Demo,BOOLEAN bIsScanStatu);

INTERFACE BOOLEAN MApp_DTV_Scan_T2_ForceMonitorT2Signal(void);
INTERFACE void MApp_DTV_Scan_T2_SetForceMonitorT2Signal(BOOLEAN bTrue);
#endif


#if(ENABLE_S2)
INTERFACE EN_SCAN_STATE MApp_Get_enScanState(void);
INTERFACE BOOLEAN msAPI_CM_Test_SetOneProgram(void);
#if(ASTRA_HD_ENABLE)
INTERFACE void MApp_Set_S2ScanParamWithCurProg(void);
#endif

#endif

U16 MApp_Scan_Get_CurRFChannel(void);
void MApp_Scan_Set_CurRFChannel(U16 u16RFChannel);

#if(ENABLE_ATSC)
#include "MApp_Scan_ATSC.h"
#endif

/***************************************************************************************/

#undef INTERFACE

/***************************************************************************************/

#endif // #ifndef MAPP_SCAN_H


