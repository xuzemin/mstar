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
#ifndef _MAPP_OAD_H_
#define _MAPP_OAD_H_

#include "datatype.h"
#include "msAPI_demux.h"
#include "MApp_Exit.h"
#include "msAPI_MW_GlobalSt.h"

#if  1
#include "MApp_ZUI_ACTglobal.h"
#endif


#ifdef _MAPP_OAD_C_
#define INTERFACE
#else
#define INTERFACE extern
#endif

#define OAD_TEST 0

typedef enum
{
    EN_OAD_UNT_CHECK_NONE,
    EN_OAD_UNT_CHECK_IN_BG,
    EN_OAD_UNT_CHECK_NEW_SW,
    EN_OAD_UNT_CHECK_SCHEDULE,
} EN_OAD_UNT_CHECK_STATE;

typedef enum
{
    STATE_OAD_SIGALPROCESS_INIT,
    STATE_OAD_SIGALPROCESS_RUN,
    STATE_OAD_SIGALPROCESS_EXIT,
} EN_OAD_SIGALPROCESS_STATE;

typedef enum
{
    EN_OAD_MONITOR_STATE_DSI_INIT,                  //  0
    EN_OAD_MONITOR_STATE_DSI_RECEIVING,             //  1
    EN_OAD_MONITOR_STATE_DSI_SIGNAL,                //  2
    EN_OAD_MONITOR_STATE_DII_INIT,                  //  3
    EN_OAD_MONITOR_STATE_DII_RECEIVING,             //  4
    EN_OAD_MONITOR_STATE_DII_READY,                 //  5
    EN_OAD_MONITOR_STATE_NIT_DSI_SIGNAL,            //  6
    EN_OAD_MONITOR_STATE_UNT_INIT,                  //  7
    EN_OAD_MONITOR_STATE_UNT_RECEIVING,             //  8
    EN_OAD_MONITOR_STATE_UNT_SIGNAL,                //  9
    EN_OAD_MONITOR_STATE_UNT_CHECK_SCHEDULE,        // 10
    EN_OAD_MONITOR_STATE_UNT_SCHEDULE_NOT,          // 11
    EN_OAD_MONITOR_STATE_UNT_WAIT_SCHEDULE,         // 12
    EN_OAD_MONITOR_STATE_UNT_LINKAGE_SSU_FOUND,     // 13
    EN_OAD_MONITOR_STATE_NIT_SIGNAL,                // 14
    EN_OAD_MONITOR_STATE_PMT_DBID_RECEINING_BY_NIT, // 15
    EN_OAD_MONITOR_STATE_PMT_DBID_RECEINING,        // 16
    EN_OAD_MONITOR_STATE_WAIT_PMT_RECEINING,        // 17
    EN_OAD_MONITOR_STATE_PMT_SID_RECEINING,         // 18
    EN_OAD_MONITOR_STATE_STOP,                      // 19
    EN_OAD_MONITOR_STATE_RECEIVING_TIMEOUT,         // 20
    EN_OAD_MONITOR_STATE_NONE,                      // 21
    EN_OAD_MONITOR_STATE_EXIT,                      // 22
} EN_OAD_MONITOR_STATE;

typedef enum
{
    EN_OAD_DOWNLOAD_STATE_FLASH_ERASEINIT,          //    0
    EN_OAD_DOWNLOAD_STATE_FLASH_ERASING,            //    1
    EN_OAD_DOWNLOAD_STATE_DDB_INIT,                 //    2
    EN_OAD_DOWNLOAD_STATE_DDB_RECEIVING,            //    3
    EN_OAD_DOWNLOAD_STATE_DDB_COMPLETED,            //    4
    EN_OAD_DOWNLOAD_STATE_WAIT,                     //    5
    EN_OAD_DOWNLOAD_STATE_STOP,                     //    6
    EN_OAD_DOWNLOAD_STATE_NONE,                     //    7
} EN_OAD_DOWNLOAD_STATE;

typedef enum
{
    EN_OAD_APP_STATE_INIT,                          //  0
    EN_OAD_APP_STATE_WAIT_USER,                     //  1
    EN_OAD_APP_STATE_YES,                           //  2
    EN_OAD_APP_STATE_NO,                            //  3
    EN_OAD_APP_STATE_DOWNLOADING,                   //  4
    EN_OAD_APP_STATE_SCAN,                          //  5
    EN_OAD_APP_STATE_STOP,                          //  6
    EN_OAD_APP_STATE_UPGRADING,                     //  7
    EN_OAD_APP_STATE_EXIT,                          //  8
    EN_OAD_APP_STATE_NONE                           //  9
} EN_OAD_APP_STATE;

typedef enum
{
    STATE_OAD_SCAN_INIT,                            //  0
    STATE_OAD_SCAN_NEXT_CHANNEL,                    //  1
    STATE_OAD_SCAN_SEARCH_RF_CHANNEL,               //  2
    STATE_OAD_SCAN_PATPMT_MONITOR,                  //  3
    STATE_OAD_SCAN_WAIT_PATPMT_MONITOR,             //  4
    STATE_OAD_SCAN_WAIT_OAD_MONITOR,                //  5
    STATE_OAD_SCAN_SSU_FOUND_OR_SCHEDULE,           //  6
    STATE_OAD_SCAN_EXIT,                            //  7
    STATE_OAD_SCAN_END,                             //  8
} EN_OAD_SCAN_STATE;

#define DMX_BUF_SIZE_MONITOR    0x4000
#define DMX_BUF_SIZE_DOWNLOAD   0x4000*4

typedef enum
{
    EN_OAD_EEPROM_MONITOR,
    EN_OAD_EEPROM_OTHER,
} EN_OAD_EEPROM_STATE;

INTERFACE void MApp_OAD_Init( void ) ;
INTERFACE void MApp_OAD_SetInfo(void) ;
INTERFACE void MApp_OAD_GetInfo(EN_OAD_EEPROM_STATE state) ;
INTERFACE BOOLEAN MApp_OAD_VersonCheck(U16 type,U8 *pPrivateData) ;
INTERFACE void MApp_OAD_SetPmtSignal( WORD wPid, WORD wBDid, BYTE *pSelector, U8 selectorType, U16 wService_ID);
INTERFACE void MApp_OAD_SetNitSignal( WORD wTSId, WORD wONId, WORD wServiceId, BYTE *pSelector);
INTERFACE void MApp_OAD_Monitor( void );
INTERFACE void MApp_OAD_Download( void );
#if OAD_TEST
INTERFACE void MApp_OAD_AppTest( void );
#endif
INTERFACE EN_RET MApp_OAD_AppMain( void );
INTERFACE  EN_OAD_MONITOR_STATE MApp_OAD_GetMonitorState( void );
INTERFACE  void MApp_OAD_SetMonitorState( EN_OAD_MONITOR_STATE state );
INTERFACE  EN_OAD_DOWNLOAD_STATE MApp_OAD_GetDownloadState( void );
INTERFACE  void MApp_OAD_SetDownloadState( EN_OAD_DOWNLOAD_STATE state );
INTERFACE  EN_OAD_APP_STATE MApp_OAD_GetAppState( void );
INTERFACE  void MApp_OAD_SetAppState( EN_OAD_APP_STATE state );
INTERFACE BOOLEAN MApp_OAD_IsDownloadAvailable(void) ;
INTERFACE EN_OAD_SCAN_STATE MApp_OAD_GetScanState( void );
INTERFACE void MApp_OAD_SetScanState( EN_OAD_SCAN_STATE state );
INTERFACE BOOLEAN MApp_OAD_IsDownloadCompleted(void) ;
INTERFACE BOOLEAN MApp_OAD_IsDownloading(void) ;
INTERFACE BOOLEAN MApp_OAD_IsUntSchedule(void) ;
INTERFACE BOOLEAN MApp_OAD_IsUserSelectOn(void);
INTERFACE void MApp_OAD_StartDownload(void) ;
INTERFACE void MApp_OAD_StopDownload(void) ;
INTERFACE void MApp_OAD_GetVersion(U32 *tvVER,U32 *tsVER);
INTERFACE void MApp_OAD_GetService(U16 *netID,U16 *tsID,U16 *serviceID,MEMBER_SERVICETYPE *type,WORD *position) ;
INTERFACE U8 MApp_OAD_GetProgress(void) ;
INTERFACE U32 MApp_OAD_GetScheduleStart(void) ;
INTERFACE U32 MApp_OAD_GetScheduleEnd(void) ;
INTERFACE WORD MApp_OAD_GetServiceLcn(void) ;
INTERFACE LPTSTR MApp_OAD_GetOadRfChannel(void);


#if (BLOADER)
#if ENABLE_ATSC
INTERFACE EN_OAD_SCAN_STATE MApp_OAD_Scan_BL_ATSC( U8* percentage );
#else
INTERFACE EN_OAD_SCAN_STATE MApp_OAD_Scan( U8* percentage );
#endif
#else
#if ENABLE_ATSC
INTERFACE EN_RET MApp_OAD_Scan_ATSC(void);
INTERFACE EN_RET MApp_OAD_Scan_ATSC2( U8* percentage );
#else
INTERFACE EN_RET MApp_OAD_Scan( U8* percentage );
#endif
#endif

INTERFACE void MApp_OAD_ScanSignalRest(void);
INTERFACE void MApp_OAD_GetInfo_BL(U16* u16PID, U32* u32Freq, U8* u8BandWidth, U8* u8Country, U16* DTVSource);
INTERFACE EN_OAD_UNT_CHECK_STATE MApp_OAD_GetCheckUNTState(void);
INTERFACE BOOLEAN MApp_OAD_IsPowerOnScreen(void);
INTERFACE void MApp_OAD_SetPowerOnScreen(void);
INTERFACE BOOLEAN MApp_OAD_GetPowerOnScreen(void);
INTERFACE void MApp_OAD_Set_StandbyOffCheck(BOOLEAN bEnable);
INTERFACE BOOLEAN MApp_OAD_IsStandbyOffCheck(void);
INTERFACE void MApp_OAD_Set_PowerOnCheck(BOOLEAN bEnable);
INTERFACE BOOLEAN MApp_OAD_IsPowerOnCheck(void);
INTERFACE void MApp_OAD_Set_ScheduleOnCheck(void);
INTERFACE BOOLEAN MApp_OAD_IsScheduleOnCheck(void);
INTERFACE void MApp_OAD_Set_OadScanCheck(void);
INTERFACE BOOLEAN MApp_OAD_IsOadScanCheck(void);
INTERFACE void MApp_OAD_Set_ShowScheduleMsg(BOOLEAN bStatus);
INTERFACE void MApp_OAD_PowerOnScreen(void);
INTERFACE void MApp_OAD_Set_PMT_Ready(BOOLEAN bReady);
INTERFACE void MApp_OAD_Set_NIT_Ready(BOOLEAN bReady);
INTERFACE BOOLEAN MApp_OAD_GetSignalForStandby(void);
INTERFACE void MApp_OAD_StandbyUpdate(void);
INTERFACE void MApp_OAD_StandbyReceivePowerKey(void);
INTERFACE void MApp_OAD_ResetInfo(void);

INTERFACE BOOLEAN MApp_OAD_GetSignalForStandby(void);
INTERFACE void MApp_OAD_StandbyUpdate(void);
INTERFACE void MApp_OAD_StandbyReceivePowerKey(void);

#undef INTERFACE
#endif //_MAPP_OAD_H_
