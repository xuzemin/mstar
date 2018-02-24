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

#ifndef MAPP_CIPVR_ADAPTION_H
#define MAPP_CIPVR_ADAPTION_H

#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))

#include "datatype.h"
#include "msAPI_PVR.h"
#include "msAPI_PVRFileSystem.h"    //For file system part

#define FILE_NAME_LENGTH        128     //Unicode
#define CI_OPERATORING_MAX_TIME                     6000 //3s
#define PVR_INVISIBLE_SKIP_CAP 3
#define CI_PINCODESTATUS_MAX_TIME                   6000 //3s
#define MAX_EVENTINFO_NUM                   16
#define MAX_LICENSE_SIZE                   1024
#define U32_MAX             (0xFFFFFFFFUL)

/// Define PVR Path
typedef enum
{
    PVR_PATH_RECORD   = 0,
    PVR_PATH_PLAYBACK = 1
} EN_PVR_PATH_TYPE;

typedef struct
{
    /// program_number:
    ///     the program number of the associated Record Start protocol for this recording.
    U16 u16program_number;
    /// PINcode_status_field:
    ///     this byte returns the status of the PIN code CICAM management, see Table 11.30.
    U8 u8PINcode_status_field;
    /// rating:
    ///     This 8-bit field is coded as DVB rating (3+years). Rating is defined in EN 300 468 [10] parental rating descriptor.
    ///     It represents the rating of the broadcasted content item that triggered the cc_PIN_event() APDU.
    U8 u8rating;
    /// pin_event_time_utc:
    ///     This field returns the time when the parental rating changed requiring the entry of a PIN.
    ///     This is a 40-bit field which specifies the date and time in MJD and UTC when the parental rating changed (See start_time field of the EIT in EN 300 468 [10]).
    ///     This 40-bit field is coded as 16-bits giving the 16 LSBs of MJD followed by 24 bits coded as 6 digits in 4-bit BCD.
    U8 au8pin_event_time_utc[CI_UTC_TIME_LEN];
    /// pin_event_time_centiseconds:
    ///     This field contains the fractional part (seconds/100) of the time of the change in parental rating requiring the entry of a PIN.
    U8 u8pin_event_time_centiseconds;
    /// private_data:
    ///     These private data bytes provide the CICAM with the option to include additional CAS specific information stored with the maturity rating in the recording.
    ///     The private_data is returned to the CICAM on playback using the cc_PIN_playback() APDU.
    U8 au8private_data[CI_CC_PIN_EVENT_PRIVATE_DATA_LEN];
    BOOL bValid;
    BOOL bVideoBlanking;
} PvrPinEvent;

typedef struct
{
    U32 u32BlockBeginTime;
    PvrPinEvent pvrPinEvent;
}PinEventInfo;

typedef struct
{
    U8 u8PinEventCount;
    PinEventInfo m_PinEventInfo[MAX_EVENTINFO_NUM];
    U8  m_hPineventFile;
    U32 m_u32ActiveID;
    BOOL m_bActive;
}PinEventHander;

typedef struct
{
    // CICAM License
    U16 m_u16program_number;
    EN_CC_PVR_LICENSE_STATUS m_u8license_status;
    BOOL    m_bUriValid;
    CI_CC_URI_MESSAGE   m_unUriMessage;
    U16 m_u16CicamLicenseLength;
    U8  m_stl_license[MAX_LICENSE_SIZE];
    BOOL    m_bLicenseAvailable;

    // HOST License
    BOOL    m_bLicenseValid;
    U8  m_u8play_count;

    U32 m_u32ExpiredTime;
    U32 m_u32ReceivedTime;
} PvrUriLicense;

typedef struct
{
    U32 u32BlockBeginTime;
    PvrUriLicense pvrUriLicense;
}UriLicenseInfo;

typedef struct
{
    U8 u8UrilicenseCount;
    U8 m_u8CICAMID[CC_AUTH_ID_SIZE];
    UriLicenseInfo m_UrilicenseInfo[MAX_EVENTINFO_NUM];
    U8  m_hUrilicenseFile;
    U32 m_u32ActiveID;
    BOOL m_bActive;
}UriLicenseHander;

/// Retention Limit Display Block for UI
typedef struct
{
    /// retention limit block begin time
    U32 u32Begin;
    /// retention limit block end time
    U32 u32End;
    /// retention limit block current mask region
    U32 u32Cur;
    /// rest license count
    U8 u8Count;
}RetentionLimitDisplayBlock;

#ifdef MAPP_CIPVR_ADAPTION_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

////////////////////////////////////////////////////////////////////////////////////////
INTERFACE BOOL MAPP_CIPVR_IsCopyFreely(BOOL bIsScramble);
INTERFACE BOOL MAPP_CIPVR_CICheckCCPinCapabilities(BOOL bPVRprocess, BOOL bScrambleServiceCheck, BOOL bSendCCPin);
INTERFACE BOOL MAPP_CIPVR_PVRCIPlusOperatingMode(EN_CC_PVR_DATATYPE_ID eOperatingType, EN_CC_PVR_OPERATING_MODE eOperatingMode, U8* pu8PinCode, U16 u16PinCodeLen);
INTERFACE BOOL MAPP_CIPVR_CISendCCPin(BOOL bMmiReq, U16 PinCode);
INTERFACE BOOL MAPP_CIPVR_CICheckPinEventStatus(BOOL *bPinCodeCorrect, U16 *u16CachedPinCode);
INTERFACE void MAPP_CIPVR_PVRReTriggerURICopyProtect(void);
INTERFACE enPvrApiStatus MAPP_CIPVR_CIPlusPVRHandling(EN_PVR_PATH_TYPE enPVRPath, BOOL bIsTimeshift,U16 u16CiPinCode);
INTERFACE BOOL MAPP_CIPVR_CIPVRActionMonitor(void);
INTERFACE BOOL MAPP_CIPVR_RetentionLimitMonitor(U32 u32CurrentTime, U32* u32JumpTime);
INTERFACE BOOL MAPP_CIPVR_CIPVRFS_RecordFileCreate(U16* pu16FileName);
INTERFACE BOOL MAPP_CIPVR_CIPVRFS_PlaybackFileOpen(U16* pu16FileName, EN_PVRFS_OPEN_MODE mode);
INTERFACE BOOL MAPP_CIPVR_CIPVRFS_PlaybackFileRead(void);
INTERFACE BOOL MAPP_CIPVR_CIPVRFS_RecordFileClose(void);
INTERFACE BOOL MAPP_CIPVR_CIPVRFS_PlaybackFileClose(void);
INTERFACE BOOL MAPP_CIPVR_SetMuteFlag(BOOL bMute, E_SCREEN_MUTE_STATUS enFlag);
INTERFACE BOOL MAPP_CIPVR_PinEventPlaybackingRunning(void);
INTERFACE BOOL MAPP_CIPVR_UriLicensePlaybackingRunning(void);
INTERFACE BOOL MAPP_CIPVR_PlaybackCiSecuredPatternCheck(U8* u8aCICAMID);
INTERFACE BOOL MAPP_CIPVR_RecordStartEventUpdate(CI_CC_URI_LICENSE stUriLicense, U8* u8aCICAMID);
#undef INTERFACE
#endif//((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
#endif
