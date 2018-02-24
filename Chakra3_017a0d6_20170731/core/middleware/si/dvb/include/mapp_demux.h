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

#ifndef MAPP_DEMUX_H
#define MAPP_DEMUX_H

#if(ENABLE_DTV)
#include "msAPI_demux.h"

/******************************************************************************/
/*                                 Macro                                      */
/******************************************************************************/

#define INVALID_VERSION_NUM         0xFF
#define PARENTAL_RATE_SHIFT 3

#define DMX_MAX_MUX_NUMBER          40
/*****************************************************************************/
/*                         Functions                                         */
/*****************************************************************************/
// demux helper functions
#define TSGetBitFromU8(ptr, bitn)           (((*(U8 *)ptr) >> bitn) & 0x01)
#define TSGetBitsFromU8(ptr, lsb, mask)     (((*(U8 *)ptr) >> lsb) & mask)
//#define TSGetU16(ptr)                       (*((U16 *)ptr))
#define TSGetU16(ptr)                       ((((U8 *)ptr)[0] << 8) + ((U8 *)ptr)[1])
#define TSGetBitsFromU16(ptr, lsb, mask)    ((TSGetU16(ptr) >> lsb) & mask)
//#define TSGetU24(ptr)                       (*((U24 *)ptr))
#define TSGetU24(ptr)                       ((((U8 *)ptr)[0] << 16)+(((U8 *)ptr)[1] << 8) + ((U8 *)ptr)[2])
//#define TSGetU32(ptr)                       (*((U32 *)ptr))
#define TSGetU32(ptr)                       ((((U8 *)ptr)[0] << 24) + (((U8 *)ptr)[1] << 16) + (((U8 *)ptr)[2] << 8) + (((U8 *)ptr)[3] << 0))
#define TSGetBitsFromU32(ptr, lsb, mask)    ((TSGetU32(ptr) >> lsb) & mask)

/******************************************************************************/
/*                                 Enum                                       */
/******************************************************************************/

/* PID definition */
typedef enum
{
    // MPEG-2 PID
    PID_PAT         = 0x0000,
    PID_CAT         = 0x0001,
    PID_TSDT        = 0x0002,
  //PID_reserved    = 0x0003 ~ 0x000F

    // PSIP PID [ATSC only]
    PID_BASE        = 0x1FFB,           // todo: remove?

    // DVB-T SI PID
    PID_NIT         = 0x0010,           // NIT / ST
    PID_SDT_BAT     = 0x0011,           // SDT / BAT / ST
    PID_EIT_CIT     = 0x0012,           // EIT / SE / CIT (TS 102 323 [36])
    PID_RST         = 0x0013,           // RST / ST
    PID_TDT_TOT     = 0x0014,           // TDT / TOT / ST
  //PID_NSYNC       = 0x0015,
  //PID_RNT         = 0x0016,           // RNT (TS 102 323 [36] TV Anytime over DVB)
  //PID_INBAND_SGNL = 0x001c,           // inband signaling
  //PID_MEASUREMENT = 0x001d,           // measurement
    PID_DIT         = 0x001e,
    PID_SIT         = 0x001f,
    PID_EWS         = 0x0080,

} EN_PSIP_PID;


/* PSIP Table */
typedef enum
{
    EN_MONITOR_TABLE_ALL,
    EN_MONITOR_PAT,
    EN_MONITOR_PMT,
    EN_MONITOR_PMT_OTHER,
    EN_MONITOR_SDT,
    EN_MONITOR_SDT_OTHER,
    EN_MONITOR_NIT,
    EN_MONITOR_PF_EIT,
    EN_MONITOR_PF_EIT_ALL,
    EN_MONITOR_TDT,
    EN_MONITOR_TOT,
    EN_MONITOR_CI_TUNE,
    EN_MONITOR_EWS_TRDW,
    EN_MONITOR_EWS_TCDW,
    EN_MONITOR_EWS_TMDW,

#if (ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
    EN_MONITOR_SGT,
#endif  //#if (ASTRA_HD_ENABLE)
#if(M7_DVBS_FAST_SCAN_ENABLE)
    EN_MONITOR_FNT,
    EN_MONITOR_FST,
#endif   // #if (M7_DVBS_FAST_SCAN_ENABLE)


} EN_MONITOR_TABLE;

/* A/V/PCR/TTX/SUBT */
typedef enum
{
    EN_AUDIO_FID,
    EN_VIDEO_FID,
    EN_PCR_FID,
    EN_AD_FID,
    EN_TTX_FID,
    EN_PES_FID,
    EN_OAD_MONITOR_FID,
    EN_OAD_DOWNLOAD_FID
} EN_FID;


typedef enum
{
    DMX_QUICK_INSTALL_RET_STATE_NONE,
    DMX_QUICK_INSTALL_RET_STATE_UPDATE_CHLIST,
    DMX_QUICK_INSTALL_RET_STATE_REMOVE_MISSING_MUX,
    DMX_QUICK_INSTALL_RET_STATE_END
}DMX_DVBC_QUICK_INSTALL_RET_STATE;
/*****************************************************************************/
/*                              Structures                                   */
/*****************************************************************************/
typedef struct
{
    U32 bUpdateMuxOnly:             1;
    U32 bParseNITOther:             1;
    U32 bNetworkIDFilterEn:           1;
    U32 bNetworkID:                     16;
    U32 bEnableNITQuickScan:            11;
    U32 reserved:                       12;
}SCAN_TABLE_CONFIG;

typedef struct
{
    void (*pfNotify_OAD_Init)(void);
}MS_DMX_NOTIFY;
/******************************************************************************/
/*                       Global Variable Declarations                         */
/******************************************************************************/
#ifdef MAPP_DEMUX_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

//INTERFACE U16       u8TTXFid;
/******************************************************************************/
/*                       Global Function Prototypes                           */
/******************************************************************************/
//(1) system interface
INTERFACE void MApp_Dmx_EnableTableMonitor(void);
INTERFACE void MApp_Dmx_DisableTableMonitor(void);
INTERFACE void MApp_Dmx_DisableTableMonitor_FileIn(void);
INTERFACE void MApp_Dmx_EnableFileInMonitor(void);
INTERFACE void MApp_Dmx_DisableFileInMonitor(void);
INTERFACE void MApp_Dmx_CloseAllFilters(void);


INTERFACE BOOLEAN MApp_Dmx_GetMonitorStatus(EN_MONITOR_TABLE eTable);
INTERFACE void MApp_Dmx_SetMonitorStatus(BOOLEAN bStatus, EN_MONITOR_TABLE eTable);
//(4) EPG functions
INTERFACE U8 MApp_Dmx_EIT_Get_CurPfVer(void);
INTERFACE void MApp_Dmx_EIT_Set_CurPfVer(U8 u8EitCurPfVer);
INTERFACE void MApp_Dmx_EIT_Set_PfMonitor_Status(BOOLEAN bEitPfMonitor);
INTERFACE void MApp_Dmx_EIT_Init_ChangeLanguage(void);
INTERFACE void MApp_Dmx_EIT_Proc(U32 u32PollingMs);


//(5) SUBTITLE functions
INTERFACE void MApp_Dmx_PES_Monitor(U16 u16PID, void *pfNotify, BOOLEAN bFileIn);
INTERFACE void MApp_Dmx_PES_Stop(void);
INTERFACE void MApp_Dmx_PES_Restart(void);

//(6) Fid function
INTERFACE U8 *MApp_Dmx_GetFid(EN_FID eFid);
INTERFACE void MApp_Dmx_SetFid(U8 u8Fid, EN_FID eFid);

//(7) Misc
#if ENABLE_SDT_OTHER_MONITOR
INTERFACE void MApp_Dmx_Disable_Reset_Filter(void);
#endif
INTERFACE void MApp_Dmx_SetReset_EventInfo_status(BOOLEAN bStatus);
INTERFACE BOOLEAN MApp_Dmx_GetScanTables(SCAN_TABLE_CONFIG *stScanConfig, U8 *u8FoundNum);
#if(ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
INTERFACE BOOLEAN MApp_Dmx_AstraHD_GetScanTables(SCAN_TABLE_CONFIG *stScanConfig, U8 *u8FoundNum);
INTERFACE void MApp_Dmx_WaitChannelListID(bool bwait);
INTERFACE BOOLEAN MApp_Dmx_IsWaitChannelListID(void);
#endif  // #if (ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)

#if(M7_DVBS_FAST_SCAN_ENABLE)
INTERFACE BOOLEAN MApp_Dmx_M7_DVBS_FASTSCAN_FNT_GetScanTables(SCAN_TABLE_CONFIG *stScanConfig, U8 *u8FoundNum);
INTERFACE U16 MApp_Dmx_M7_DVBS_FASTSCAN_FNT_Parse_Table( U8 u8SecCount);
INTERFACE BOOLEAN MApp_Dmx_M7_DVBS_FASTSCAN_FST_GetScanTables(SCAN_TABLE_CONFIG *pstScanConfig, U8 *u8FoundNum);
INTERFACE BOOLEAN MApp_Dmx_M7_DVBS_FASTSCAN_PAT_PMT_GetScanTables(SCAN_TABLE_CONFIG *pstScanConfig, U8 *u8FoundNum);
#endif // #if (M7_DVBS_FAST_SCAN_ENABLE)

INTERFACE BOOLEAN MApp_Dmx_GetSDTScanTables(U16 u16TSID, BOOLEAN* bGotSDT, U32 u32WaitTime);
#if 1//def DVB_C_ENABLE
INTERFACE BOOLEAN MApp_Dmx_GetAllNetwork(U32 u32TimeOut);
INTERFACE void MApp_Dmx_Enable_NIT_Other(BOOLEAN bEnable);
#endif
INTERFACE void MApp_Dmx_GetScanTableStateInit(void);
INTERFACE void MApp_Dmx_DVBC_QuickInstallStateInit(void);
INTERFACE void MApp_Dmx_DVBC_QuickInstallGetTsIDs(U16 *pu16TsIDs, U8 *pu8TsIdCount, U8 u8MaxPoolLen);
INTERFACE DMX_DVBC_QUICK_INSTALL_RET_STATE MApp_Dmx_DVBC_QuickInstallScanTables(void);
INTERFACE U8 * MApp_Dmx_GetSI4KSectionBuffer(void);
INTERFACE void MApp_Dmx_Init_OAD(MS_DMX_NOTIFY* psNotify);
#if ENABLE_OAD
INTERFACE BOOLEAN MApp_Dmx_Get_IsAllPmtReady(void);
INTERFACE void MApp_Dmx_ResetAllPmtReady(void);
INTERFACE void MApp_Dmx_SetCITuneServiceId(U16 u16ServiceId);
INTERFACE U16 MApp_Dmx_GetCITuneServiceId(void);
#endif
#undef INTERFACE
#endif//#if(ENABLE_DTV)
#endif
