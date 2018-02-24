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
/*
++++++++++++++++++++++++++++++++++???????????????++++++++++++++++++++++++++++++++++++++++++??????????????????????++++++++++++++++++++++++++++++++++++++++=++????
++++++++++++++++++++++++++++++++++IIIIIIIIIIIIII????????????????????????????????????????????IIIIIIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++++++++++++++++++++++++++++++++IIIIIIIIIIII????????????????????????????????????????????????IIIIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++++=+IIIIIIIIIII+++++++++++++++?$$$$$$$$$77II??????????I???????????????????????????????????IIIIIIIIIIIIIII?III??????????????????????????????????????????IIIII
+++++++DMMMMMMMMMMMZI++++++++++++=NMMMMMMMMMMMZ$?I77$$$$$$I?????????????????????????????????????IIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++++=8MMMMMMMMMMMMD7=+++++++++IMMMMMMMMMMMMM8OZZ$7I???????????????????????????????????????????IIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++++=8MMMMMMMMMMMMM8++++++++++DMMMMMMMMMMMMMD8$I?????????????????III???????????????????????????IIIIIIIIIIII?III??????????????????????????????????????????IIIII
+++=+?=8MMMMMMMMMMMMMMZZ++++++?DMMMMMMMMMMMMMMZZ???????????????IIIIIIIIIII????????????????????????IIIIIIIIIII?III??????????????????????????????????????????IIIII
+++++I=DMMMMMMMMMMMMMMMN?=++++8MMMMMMMMMMMMMMMZ$??????????????IIIIIIIIIIIIII??????????????????????IIIIIIIIIII?III??????????????????????????????????????????IIIII
+++++I+8MMMMMMMMMMMMMMMMD?=+IDMMMMMMMMMMMMMMMM$$?????????????IIIIIIIIIIIIIIII????????????????????IIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++?I+8MMMMMMMMMMMMMMMMMOI~OMMMMMMMMMMMMMMMMM$$?????????????IIIIIIIIIIIIIIIII????????????IIIIIIIIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++II+8MMMMMMMMMMMNNMMNMND8MMNNMMNNMMMMMMMMMMZ$????????????IZZ8888OZ7IIIIIIIIIIIIIIIIIIIIIIZD7IIIIIIIIIIIIII?IIIIIIIIIII???????????????????????IIIIIIIIIIIIIIII
++++II+8MMMMMMMMMMII????????OOOOOOZ8MMMMMMMMMMZ$??????????ZDMMMMMDDDNND87IIIIIIIIIIIIIII?Z8MMDIIIIIIIIIIIIIII?IIIIIIIIIII???????????????????????IIIIIIIIIIIIIIII
+++III+8MMMMMMMMMMI++++++7$ZZZZZZZOOMMMMMMMMMMZ$??????IINMMMMMMD+IIII7I7DMMIIIIIIII?I8NMMMMMMD?IIIIIIIIIIIIII?IIIIIIIIIII???????????????????????IIIIIIIIIIIIIIII
+++III+8MMMMMMMMMMI+++++I$ZZZZZZZZ$ZMMMMMMMMMMZ$??????IMMMMMMMMMI??????IIO87IIIIII?DMMMMMMMMMD?IIIIIIIIIIIIII?IIIIIIIIIII???????????????????????IIIIIIIIIIIIIIII
++?III+8MMMMMMMMMMI++=$$ZZZZZZZZZIIZMMMMMMMMMMZ$??????MMMMMMMMMMMZ??????????????IIIMMMMMMMMMMD$ZZZZIIIIIIIIII+Z8DDNMMMDDDOO$I?????????????IIIII$ZZZ7IIII7O8887II
+?IIII+8MMMMMMMMMMI++7ZZZZZZZZZZI+IZMMMMMMMMMMZ$????7ZMMMMMMMMMMMM$????????????OMMMMMMMMMMMMMMMMMMNIIIIIIIII8MMMD888DMMMMMMMND$?????????8MMMMMMMMMMOII78MMMMM8?I
+?IIII+8MMMMMMMMMMI?7ZZZZZZZZZZ?++IZMMMMMMMMMMZ$????7ZMMMMMMMMMMMMMM8??????????+++?MMMMMMMMMM8IIIIIIIIIIIZMMM77IIIIIII8MMMMMMMMND?II????8MMMMMMMMMMOODNZII7Z8I7I
?IIIII+8MMMMMMMMMMZZZZZZZZZZZZI+++IZMMMMMMMMMMZ$??????NMMMMMMMMMMMMMMDII??????????IMMMMMMMMMM8IIIIIIIIIIIO8ZI?IIIIIIIIZDMMMMMMMMMD??????8MMMMMMMMMMN8D7IIIIIIIII
?IIIII+8MMMMMMMMMNZZZZZZZZZZZZ++++?ZMMMMMMMMMMZ$??????ZMMMMMMMMMMMMMMMMN7?????????IMMMMMMMMMM8IIIIIIIIIIIIIII?IIIIIIIIZDMMMMMMMMMMI?????8MMMMMMMMMM8IIIIIIIIIIII
?IIIII+8MMMMMMMMN8ZZZZZZZZZZZ?++++?ZMMMMMMMMMMZ$??????I8MMMMMMMMMMMMMMMM8?????????IMMMMMMMMMMO?IIIIIIIIIIIII7I7777777IODMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMMNZZZZZZZZZZZZ7+++++?ZMMMMMMMMMMZ$????????8MMMMMMMMMMMMMMMMDD???????IMMMMMMMMMMO??IIIIIIIII7DMMMMMMMDDMDDNMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMNZZZZZZZZZZZZ$++++++?ZMMMMMMMMMMZ$I????????7NMMMMMMMMMMMMMMMMDI?????IMMMMMMMMMMO????IIIIIZ8MMMMMMMM7III7ONMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMNOZZZZZZZZZZZ7++++++?ZMMMMMMMMMMZ$III??????+IMMMMMMMMMMMMMMMMN$+????IMMMMMMMMMMO????IIII?NMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMMMMNOZZZZZZZZ?++++++?ZMMMMMMMMMMZ$IIII????????ZMMMMMMMMMMMMMMMO?????IMMMMMMMMMMZ?????III$MMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMMMMM?$ZZZZZZ$+++++++?ZMMMMMMMMMMZ$IIIIIIIIII???ZMMMMMMMMMMMMMMDZ????IMMMMMMMMMMZ?????IIIZMMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII=DMMMMMMMMMM?++7ZZZ7?+++++++IZMMMMMMMMMMZ$IIIIIIIIIIIIII7OMMMMMMMMMMMM8?????IMMMMMMMMMMZ????IIIIZMMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?II?II+8MMMMMMMMMMI++?ZOZ7?+++++++?ZMMMMMMMMMMZ$IIII7OZIIIIIIIII8MMMMMMMMMMMZ?????IMMMMMMMMMM$???OOD7IIMMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIMMMMMMMMMMMMMMNNNN8O$I++++?NMNNMMMMMMMMMMMMMMD8I77NM8IIIIIIIIOMMMMMMMMMO??????+8MMMMMMMMMZ??$MM$?IIZMMMMMMMMM?IIIZNMMMMMMMMMMMZ?????8MMMMMMMMMMOIIIIIIIIIIII
?II?MMMMMMMMMMMMMMMMMM88??++++?MMMMMMMMMMMMMMMMMMD8II7IDMMOIIIIIIOMMMMMMMDOIIII??I??NMMMMMMMMMO8MZ$?IIIIZMMMMMMMMZIZ8MDMMMMMMMMMMMO?????8MMMMMMMMMMOIIIIIIIIIIII
?II?DDDDDDDDDDDDDDD8DDZ$++++++?D8D8DDDDDDDDDDDDDDOZIIIIII?7ODMMMMMMMNDZ7?IIIIIII??????ZDMMMMN8Z7??I?IIIIIIIZ8MMMMN8Z??7$ZZZZZZZZZZZ+????IZZZZZZZZZZ7IIIIIIIIIIII
?IIIII++++++++++++++++=+++++++++++IIIIIIIIIIIIIIIIII???I?????I77ZZ77IIIIIIIIIIIII????I???II??????????IIIIIIII?777IIIIIIII???????????????????????IIIIIIIIIIIIIIII
*/
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
//#define PVR_UI_T2_PORTING_DONE FALSE
#ifndef MAPP_UIPVR_H
#define MAPP_UIPVR_H

#include "Board.h"

#if ENABLE_PVR

//#include "datatype.h"
#include "MApp_Record.h"
#include "MApp_PVR_Browser.h"
#include "msAPI_PVRFileSystem.h"
#include "msAPI_FS_SysInfo.h"


#ifndef PVR_8051
#include "MApp_ZUI_ACTglobal.h"
#endif

#ifdef MAPP_UIPVR_C
    #define INTERFACE
#else
    #define INTERFACE extern
#endif



//*****************************************************************************
//              Enums
//*****************************************************************************
typedef enum
{
    EN_PVR_CHKSTS_INITIAL,
    EN_PVR_CHKSTS_CHECK_USB,
    EN_PVR_CHKSTS_USB_NOT_CONNECT,
    EN_PVR_CHKSTS_CHECK_DISK,
    EN_PVR_CHKSTS_NO_PARTITION,
    EN_PVR_CHKSTS_CHECK_SIZE_FAIL,
    EN_PVR_CHKSTS_CHECK_FORMAT,
    EN_PVR_CHKSTS_CHECK_BULK,
    EN_PVR_CHKSTS_CHECK_BULK_FAIL,
    EN_PVR_CHKSTS_CHECK_FORMAT_PASS,
    EN_PVR_CHKSTS_FORMAT_PROGRESS,
    EN_PVR_CHKSTS_FORMAT_ERROR,
#if (ENABLE_BULK_FILE_SYSTEM)
    EN_PVR_CHKSTS_CREATE_FILE_SYSTEM_PROGRESS,
#endif
    EN_PVR_CHKSTS_CREATE_FOLDER_ERROR,
    EN_PVR_CHKSTS_CREATE_INDEX_ERROR,
    EN_PVR_CHKSTS_CREATE_FILE_SYSTEM_PASS,
    EN_PVR_CHKSTS_CHECK_TMSHFT_SIZE,
    EN_PVR_CHKSTS_CHECK_SPEED_START,
    EN_PVR_CHKSTS_CHECK_SPEED_PASS,
    EN_PVR_CHKSTS_OK,
} EN_PVR_CHECK_FILE_SYSTEM_STATUS;

typedef enum
{
    EN_PVR_CHKMOD_NONE,
    EN_PVR_CHKMOD_CHECK_ALL,
    EN_PVR_CHKMOD_FORCE_FORMAT,
} EN_PVR_CHECK_FILE_SYSTEM_MODE;

typedef enum
{
    EN_PVR_PAGE_NONE,
    EN_PVR_PAGE_BRIEF,
    EN_PVR_PAGE_NORMAL,
} EN_PVR_PAGE_MODE;

typedef enum
{
    E_PVR_RECORDER_IDLE,
    E_PVR_RECORDER_TIMEUP,
    E_PVR_RECORDER_TIMEUP_TO_REC,
    E_PVR_RECORDER_TIMEUP_RECORDING,
    E_PVR_RECORDER_ONECLICK_RECORD,
} EN_PVR_RECORDER_STATUS;

typedef enum
{
    E_PVR_WARNING_NONE,
    E_PVR_WARNING_USB_NOT_READY,
    E_PVR_WARNING_DISK_FORMAT_ERROR,
    E_PVR_WARNING_DISK_FORMAT_VERSION_CHANGED,
    E_PVR_WARNING_CLOCK_NOT_SET,
    E_PVR_WARNING_PLAY_NO_DEVICE,
    E_PVR_WARNING_PLAY_LOW_DISK_SPEED,
    E_PVR_WARNING_REC_NO_DEVICE,
    E_PVR_WARNING_REC_URI_BLOCK,
    E_PVR_WARNING_REC_NO_SIGNAL,
    E_PVR_WARNING_REC_NO_DISK_SPACE,
    E_PVR_WARNING_TIMESHIFT_NO_DISK_SPACE,
    E_PVR_WARNING_REC_LOW_DISK_SPEED,
    E_PVR_WARNING_REC_SCRAMBLE,
    E_PVR_WARNING_REC_PROCESSING,
    E_PVR_WARNING_EPG_RECORDER_REC_PREPARING,
    E_PVR_WARNING_PVR_SYSTEM_ERROR,
    E_PVR_WARNING_PVR_FILE_READ_ERROR,
    E_PVR_WARNING_PVR_PLAYBACK_CANTSUPPORT,
    E_PVR_WARNING_PVR_RECORD_CANTSUPPORT,
    E_PVR_WARNING_PVR_TIMESHIFT_CANTSUPPORT,
} EN_PVR_POP_UP_WARNING;

typedef enum
{
    EN_PVR_KEYRTN_NONE,
    EN_PVR_KEYRTN_PROCESSED,
    #ifdef PVR_8051
    EN_PVR_KEYRTN_TO_MENU_STATE,
    #else
    EN_PVR_KEYRTN_TO_FILE_BROWSWER,
    #endif
} EN_PVR_KEY_INPUT_RETURN;

#ifndef PVR_8051
typedef enum
{
    MENU_PVR_NONE,
    MENU_PVR_INITIAL,
    MENU_PVR_RECORD,
    MENU_PVR_RECORDING_BRIEF,
    MENU_PVR_RECORD_CHANNEL_CHANGE_CHECK,
    MENU_PVR_TIME_SHIFT,
    MENU_PVR_TIME_SHIFT_BRIEF,
    MENU_PVR_PLAYBACK_BRIEF,
    MENU_PVR_PLAYBACK,
    MENU_PVR_PAUSE_BRIEF,
    MENU_PVR_SOURCE_CHANGE_CHECK,
  //MENU_PVR_POP_UP_WARNING_MSG,
    MENU_PVR_CHECKFS_MAIN,
    MENU_PVR_CHECKFS_CREATE_PARTITION_MSG,
    MENU_PVR_CHECKFS_FORMAT_DISK_CHECK_MSG,
    MENU_PVR_CHECKFS_SELECT_DISK_MSG,
    MENU_PVR_CHECKFS_FORMAT_SETTING_MSG,
    MENU_PVR_CHECKFS_FORMAT_PROGRESS_MSG,
    MENU_PVR_CHECKFS_SET_TMSHFT_SIZE_MSG,
  //MENU_PVR_FILE_BROWSER,
  //MENU_PVR_FILE_BROWSER_FILEINFO,
}PvrMenuPageType;
#endif

typedef enum
{
    E_ABLOOP_NONE,
    E_ABLOOP_A_set,
    E_ABLOOP_B_set, //AB loop starting
} enPvrABLoopState;

//*****************************************************************************
//              Defines
//*****************************************************************************
#define UI_PVR_BLOCK_SCRAMBLE_CHANNEL_RECORD        FALSE

#define UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC           (3)
#define TIME_SHIFT_SIZE_TO_TIME_RATIO_SD            (28)    //estimate GB -> Minutes
#define TIME_SHIFT_SIZE_TO_TIME_RATIO_HD            (8)
#define TIME_SHIFT_MAX_DISK_SIZE_GB                 (4)
#define PVR_TIMESHIFT_SIZE_512M_NUM                 (255)

#define PVR_CHECKFS_MAX_SPEED                       (6000)
#define PVR_CHECKFS_SD_SPEED                        (600)
#define PVR_CHECKFS_HD_SPEED                        (1500)
#define PVR_CHECKFS_FULLHD_SPEED                    (4500)
#define PVR_CHECKFS_MAX_RECORD_TIME                 (6*SECONDS_PER_HOUR)

#define EPG_RECORDER_PVR_LEADING_TIME_s             5       //for waiting stream info/subtitle after channel change
#define UI_PVR_CHANNEL_NAME_MAX_UNICODE_LEN         (16)
#define UI_PVR_PROGRAM_NAME_MAX_UNICODE_LEN         (50)

#if((ENABLE_USB_2 && ENABLE_USB) ||(ENABLE_USB_3 && ENABLE_USB_4))
#define PVR_USB_COUNT   (2)
#elif (ENABLE_USB||ENABLE_USB_3||ENABLE_USB_4)
#define PVR_USB_COUNT   (1)
#else
#define PVR_USB_COUNT   (0)
#endif

//*****************************************************************************
//              Global variables
//*****************************************************************************
//recording info for ui
INTERFACE U32     g_u32TimeShiftClockStartTime;
INTERFACE U32     g_u32TimeShiftStartRecordingTime_Sec;

//ui trigger start/stop
INTERFACE U16     g_pu16TempFileName[RECORD_NAME_LENGTH];

//disk formatting
INTERFACE U8      g_u8PVRActiveDevice;                  // MSD_USB_INDEX_START:USB_0, MSD_USB_2_INDEX_START:USB_1
INTERFACE U8      g_u8PVRActiveDisk;                    // 0:DiskC,  1:DiskD...
INTERFACE U16     g_u16TimeShiftDiskSize_GB;            // PVR_TIMESHIFT_SIZE_512M_NUM: 512MB, 1: 1GB, 2:2GB ~ TIME_SHIFT_MAX_DISK_SIZE_GB
INTERFACE U16     g_u16FileSystemDiskSize_GB;           //0:All, 1 ~ max disk available size
INTERFACE U8 g_u8PvrFormatFsType;   //for Disk format
INTERFACE EN_PVR_CHECK_FILE_SYSTEM_STATUS g_PVRCheckFSStatus;
INTERFACE EN_PVR_CHECK_FILE_SYSTEM_MODE   g_PVRCheckFSMode;

//confirm source change when recording
INTERFACE U8 g_u8PvrCheckSourceIdx;

//program browser
#if(ENABLE_PVR_BROWSER)
INTERFACE SORT_TYPE g_PVRBrowerSort;
#ifdef PVR_8051
INTERFACE U16     g_PvrBrowser_CurrentDrawingItem;      //for drawing item in page, absolute index
#endif
INTERFACE U16     g_PvrBrowser_TotalItem;
INTERFACE U16     g_PvrBrowser_PageStartItem;
INTERFACE U8      g_PvrBrowser_FocusItem;
#endif

//EPG
INTERFACE EN_PVR_RECORDER_STATUS    g_PVR_RecordStatus; //For EPG Recorder wake up
INTERFACE EN_PVR_POP_UP_WARNING     g_PVR_PopUpWarning; //For sharing general warning message.
INTERFACE U32     g_u32RecorderPvrLeadingTime;          //For EPG Recorder leading time up

//MENU PAGE
#ifndef PVR_8051
INTERFACE PvrMenuPageType  g_PvrMenuPageType;
#endif

//*****************************************************************************
//              Function prototypes
//*****************************************************************************
INTERFACE U8      MApp_UiPvr_TimeShiftGetPlaybackPercentage(void);
INTERFACE U8      MApp_UiPvr_TimeShiftGetRecordPercentage(void);
INTERFACE U8      MApp_UiPvr_PlaybackGetPlaybackPercentage(void);

INTERFACE enPvrABLoopState MApp_UiPvr_GetABLoop_Status(void);

INTERFACE void    MApp_UiPvr_TimeshiftRecordStart(U16 u16CiPinCode);
INTERFACE void    MApp_UiPvr_RecordStart(U16 u16CiPinCode);
INTERFACE void    MApp_UiPvr_RecordStop(void);
INTERFACE void    MApp_UiPvr_PlaybackStart(void);
INTERFACE void    MApp_UiPvr_PlaybackStop(void);

INTERFACE void    MApp_UiPvr_Init(void);
INTERFACE BOOLEAN MApp_UiPvr_IsRecordingExceedMaxTime(U8 RecorPath);
INTERFACE void    MApp_UiPvr_UIMonitor(void);
INTERFACE EN_PVR_KEY_INPUT_RETURN MApp_UiPvr_KeyProcessor(void);
INTERFACE MEMBER_SERVICETYPE MApp_UiPvr_Browser_GetPlayingServiceType(void);
INTERFACE void    MApp_UiPvr_CheckFS_FlowControl(void);
INTERFACE void    MApp_UiPvr_CheckFS_SelectActiveDisk(void);
INTERFACE void    MApp_UiPvr_CheckFS_StartCheckAll(void);
INTERFACE void    MApp_UiPvr_CheckFS_Confirm_CreatePartition(void);
INTERFACE void    MApp_UiPvr_CheckFS_StartFormat(void);
INTERFACE void    MApp_UiPvr_CheckFS_Cancel(void);
INTERFACE void    MApp_UiPvr_CheckFS_Confirm_Formating(void);
INTERFACE void    MApp_UiPvr_CheckFS_Initial(void);
INTERFACE U8      MApp_UiPvr_CheckFS_GetCheckBulkPercent(void);


INTERFACE void MApp_UiPvr_VirtualKeyProcessor(HWND current);


#if(ENABLE_PVR_BROWSER)
INTERFACE void    MApp_UiPvr_Browser_Init(void);
INTERFACE void    MApp_UiPvr_Browser_DeInit(void);
INTERFACE void    MApp_UiPvr_Browser_Reset(void);

#ifdef PVR_8051
INTERFACE void    MApp_UiPvr_Browser_RedrawPage(void);
INTERFACE BOOLEAN MApp_UiPvr_Browser_KeyProcessor(void);
#else
INTERFACE BOOLEAN MApp_UiPvr_Browser_KeyProcessor(U8 KeyCode);
#endif

INTERFACE void    MApp_UiPvr_Browser_UpdateRecordingAttr(void);

#endif

/***************************************************************************************/

#endif  //#if ENABLE_PVR

#undef INTERFACE
#endif

