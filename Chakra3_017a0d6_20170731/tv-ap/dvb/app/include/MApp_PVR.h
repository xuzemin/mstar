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

#ifndef MAPP_PVR_H
#define MAPP_PVR_H

//system
#include "Board.h"     //For pvr select


#if ENABLE_PVR
#include "datatype.h"
#include "msAPI_PVR.h"
#include "msAPI_FSCommon.h"
#include "MApp_Subtitle.h"
#include "msAPI_PVRFileSystem.h"

/*definition ====================================================================================*/
#define PVR_RECORD_IN_ALL_INPUT_SOURCE  FALSE

/*enumeration ===================================================================================*/
//<<pvr state machine>>==========================================================================//
typedef enum
{
    E_PVR_STATE_IDLE,
    E_PVR_STATE_INIT,
    E_PVR_STATE_WAITFORMAT,
    E_PVR_STATE_WAIT,
    E_PVR_STATE_TIMESHIFT,
    E_PVR_STATE_RECORD,
    E_PVR_STATE_RECORDnPLAYBACK,
    E_PVR_STATE_PLAYBACK
} enPVRState;

//<<pvr state machine input>>====================================================================//
typedef enum
{
    E_PVR_INPUT_NONE,

    E_PVR_INPUT_RECORD_OPEN,
    E_PVR_INPUT_RECORD_START,
    E_PVR_INPUT_RECORD_STOP,
    E_PVR_INPUT_RECORD_CLOSE,

    E_PVR_INPUT_PLAYBACK_OPEN,
    E_PVR_INPUT_PLAYBACK_START,
    E_PVR_INPUT_PLAYBACK_PAUSE,
    E_PVR_INPUT_PLAYBACK_RESUME,
    E_PVR_INPUT_PLAYBACK_STEP_IN,
    E_PVR_INPUT_PLAYBACK_JUMP_TO_TIME,
    E_PVR_INPUT_PLAYBACK_JUMP_FORWARD,
    E_PVR_INPUT_PLAYBACK_JUMP_BACKWARD,
    E_PVR_INPUT_PLAYBACK_SLOW_FORWARD,
    E_PVR_INPUT_PLAYBACK_FAST_FORWARD,
    E_PVR_INPUT_PLAYBACK_FAST_BACKWARD,
    E_PVR_INPUT_PLAYBACK_STOP,
    E_PVR_INPUT_PLAYBACK_CLOSE,
} enPVRInput;

/*function ======================================================================================*/
#ifdef MAPP_PVR_C
    #define INTERFACE
#else
    #define INTERFACE extern
#endif

INTERFACE BOOLEAN        MApp_PVR_SetDiskDriveIndex(U8 u8DriveIndex, BOOLEAN bForceInit);
INTERFACE U8             MApp_PVR_GetDefaultDiskDriveIndex(void);
INTERFACE BOOLEAN        MApp_PVR_DiskFormat(EN_PVRFS_FSTYPE ePVRFSFileSystemType);
INTERFACE BOOLEAN        MApp_PVR_DiskFormatCreateFolder(void);
INTERFACE BOOLEAN        MApp_PVR_DiskFormatCreateBulks(BOOLEAN *bFinished);
INTERFACE BOOLEAN        MApp_PVR_DiskFormatCreateIndexFile(void);
INTERFACE U8             MApp_PVR_DiskFormatGetPercentage(void);

#if (ENABLE_BULK_FILE_SYSTEM)
INTERFACE U8             MApp_PVR_DiskFormatGetCreateFilePercentage(void);
#endif

INTERFACE U32            MApp_PVR_DiskGetAvailableSizeMB(void);

INTERFACE U16            MApp_PVR_DiskCheckSpeed(void);
INTERFACE U16            MApp_PVR_DiskGetSpeed(void);
INTERFACE BOOLEAN        MApp_PVR_DiskSetSpeed(U16 newSpeed);

INTERFACE BOOLEAN        MApp_PVR_TimeShiftSetRecordLengthMB(U32 u32TimeShiftRecordLengthMB);
INTERFACE U32            MApp_PVR_TimeShiftGetRecordLengthMB(void);

INTERFACE BOOLEAN        MApp_PVR_IsVideoFrameCountStillIncrease(void);
INTERFACE BOOLEAN        MApp_PVR_IsSystemReady(void);
INTERFACE BOOLEAN        MApp_PVR_IsFileFormatCheckFail(void);
INTERFACE BOOLEAN        MApp_PVR_IsFileFormatVersionChanged(void);
INTERFACE BOOLEAN        MApp_PVR_IsPlaybacking(void);
INTERFACE BOOLEAN        MApp_PVR_IsRecording(void);
INTERFACE BOOLEAN        MApp_PVR_IsFastPlaybacking(void);
INTERFACE BOOLEAN        MApp_PVR_IsPVRStatePlaybacking(void);
INTERFACE void MApp_PVR_GetPlaybackFileName(U16 * u16NameBuffer);
INTERFACE void MApp_PVR_GetRecordFileName(U16 * u16NameBuffer);
INTERFACE U32 MApp_PVR_GetRecordStartSysTime(void);
INTERFACE U32 MApp_PVR_GetCurRecordTimeInSec(void);
INTERFACE U32 MApp_PVR_GetDurationTime(void);
INTERFACE U32 MApp_PVR_GetPlaybackTimeSec(void);
INTERFACE BOOLEAN MApp_PVR_IsFastBackwardPlaybacking(void);
INTERFACE enPvrEncryptType MApp_PVR_GetEncryptionType(void);
INTERFACE BOOL MApp_PVR_SetCicamCheckLevel(const U8 u8CicamCheckLevel);
INTERFACE BOOL MApp_PVR_GetRecordCAPVR(void);

INTERFACE void           MApp_PVR_RecordAudioAddServices(U8 u8PathNum, U8 u8Idx, U8 u8Num);
INTERFACE U8             MApp_PVR_PlaybackAudioGetLanguageSelection(void);
INTERFACE U8             MApp_PVR_PlaybackAudioGetLanguageTotal(void);
INTERFACE BYTE           MApp_PVR_PlaybackAudioGetLanguageInfo(void);
INTERFACE BOOLEAN        MApp_PVR_PlaybackAudioGetStreamInfo(AUD_INFO* pstAudioStreamInfo, U8 u8Idx);
INTERFACE void           MApp_PVR_PlaybackAudioSelectLanguage(U8 u8AudSelectedIndex);
INTERFACE void           MApp_PVR_PlaybackAudioStopLanguage(U8 u8AudSelectedIndex);

#ifndef S3PLUS
INTERFACE void           MApp_PVR_PlaybackAdAudioSelectLanguage(U8 u8AudSelectedIndex);
INTERFACE void           MApp_PVR_PlaybackAdAudioStopLanguage(U8 u8AudSelectedIndex);
#endif

INTERFACE void           MApp_PVR_RecordSubtitleAddServices(U8 u8PathNum, U8 u8Idx, U8 u8Num, DVB_SUBTITLE_SERVICE* pSubtitleServices);
INTERFACE void           MApp_PVR_PlaybackSubtitleLoadServices(U8* pu8SelIdx, U8* pu8Num, DVB_SUBTITLE_SERVICE* pSubtitleServices);
INTERFACE void           MApp_PVR_PlaybackSubtitleLoadMenu(U8* pu8SelIdx, U8* pu8Num, SUBTITLE_MENU* pSubtitleServices, U8* pu8fEnableSubtitle, U8* pu8fEnableTTXSubtitle);
INTERFACE void           MApp_PVR_PlaybackGetTTXSubtitleNum(U8* pu8Num);

INTERFACE void           MApp_PVR_StateMachineRunning(void);
INTERFACE void           MApp_PVR_StateMachineInput(enPVRInput enSMInput, U32 u32ExtParameter);
INTERFACE enPVRState     MApp_PVR_StateMachineGet(void);
INTERFACE enPvrApiStatus MApp_PVR_StatusGet(void);

BOOLEAN MApp_PVR_Is_InRecording(void);

#if BRAZIL_PVR_CC
INTERFACE U16 MApp_PVR_Playback_GetCCPID(void);
INTERFACE void MApp_PVR_Playback_SetCCPID(U16 u16PID);
#endif

#undef INTERFACE
#endif//ENABLE_PVR
#endif

