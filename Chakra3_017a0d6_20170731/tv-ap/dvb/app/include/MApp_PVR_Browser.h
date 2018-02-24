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

#ifndef MAPP_PVR_BROWSER_H
#define MAPP_PVR_BROWSER_H

#include "Board.h"


#if ( ENABLE_PVR_BROWSER )

#include "datatype.h"
#include "msAPI_PVRFileSystem.h"   // For PVR_MAX_CHANNEL_NAME_LEN
#include "MApp_GlobalSettingSt.h"   //For ST_TIME struct



#define PVR_BROWSER_ITEM_PER_PAGE    10
#define PVR_BROWSER_SIZE_OF_FILE_NAME   25

/// Return value for PVR API interface.
typedef enum
{
    E_PVR_RET_OK,                   /// Function execution successfully
    E_PVR_RET_FAIL,                 /// Function failed
    E_PVR_RET_POOL_TOO_SMALL,
    E_PVR_RET_POOL_IS_FULL,
    E_PVR_RET_DRV_NOT_READY,
    E_PVR_RET_FS_REGISTER_FAIL,
    E_PVR_RET_FS_INTERNAL_FAIL,
    E_PVR_RET_BUK_FILES_NOT_FOUND,
    E_PVR_RET_EMPTY_SLOT_NOT_FOUND,
    E_PVR_RET_LIST_ADD_FAIL,
    E_PVR_RET_LIST_DEL_FAIL,
    E_PVR_RET_LIST_BROKEN,
    E_PVR_RET_LIST_IS_EMPTY,
    E_PVR_RET_SLOTMAP_ERR,
    E_PVR_RET_ARG_INVALID,
    E_PVR_RET_BUF_SIZE_NOT_ENOUGH,
    E_PVR_RET_BROWSER_NOT_ACTIVE,
    E_PVR_RET_BROWSER_NO_FILE_IN_PLAYING,
    E_PVR_RET_BROWSER_NO_FILE_IN_RECORDING,

    E_PVR_RET_NUM,

} E_PVR_RET;

typedef enum
{
    E_PVR_BROWSER_INACTIVE,
    E_PVR_BROWSER_ACTIVE,
    E_PVR_BROWSER_STATUS_NUM,

}   E_PVR_BROWSER_STATUS;

typedef enum
{
    LIST_DIRECTION_UP,
    LIST_DIRECTION_DOWN,
    LIST_DIRECTION_NUM,

} SEARCH_DIRECTION;

typedef enum
{
    SORT_NONE,
    SORT_PROG_NAME,
    SORT_CHANNEL_NAME,
    SORT_PROG_TIME,
    SORT_FILE_NAME,
    SORT_FILE_LENGTH,
    SORT_TYPE_NUM,

} SORT_TYPE;

#define MAX_PVR_BROWSER_ENTRY_NUM   (PVR_BROWSER_BUFFER_LEN/sizeof(PVR_BROWSER_ENTRY))
#define PVR_BROWSER_RESERVED_ENTRY_INDEX 0

#define PVR_BROWSER_MAX_FILE_NAME_LEN       (MAX_FAT_SEG_FILENAME_LEN)   ///Unicode length,including srting tail zero char
#define PVR_BROWSER_MAX_CHANNEL_NAME_LEN    (PVR_MAX_CHANNEL_NAME_LEN/2) //Unicode length,///LCN 5 digit+1 extra space char+1 string tail zero char
#define PVR_BROWSER_MAX_PROGRAM_NAME_LEN    (PVR_MAX_PROGRAM_NAME_LEN/2) //Unicode length, ///plus 1 string tail zero char
#define PVR_BROWSER_MAX_PROGRAM_DESC_LEN    (PVR_MAX_PROGRAM_DESC_LEN/2) //Unicode length,we only store the fist 255 char of program desc

#define PVR_NULL_FILE_INDEX         0xFFFF

typedef struct
{
    U16 u16FileName[PVR_BROWSER_MAX_FILE_NAME_LEN];
    U16 u16ProgramName[PVR_BROWSER_MAX_PROGRAM_NAME_LEN];
    U16 u16ChannelName[PVR_BROWSER_MAX_CHANNEL_NAME_LEN];
    U16 u16ProgDesc[PVR_BROWSER_MAX_PROGRAM_DESC_LEN];
    U32 u32StartTime;
    U32 u32Duration;
    MEMBER_SERVICETYPE enServiceType;
    LongLong u64FileLength;
    BOOLEAN isPlaying;
    BOOLEAN isRecording;
} PVR_UI_BROWSER_ENTRY;

typedef enum
{
    E_PVR_ATTR_FILE_NAME,
    E_PVR_ATTR_PROGRAM_NAME,
    E_PVR_ATTR_CHANNEL_NAME,
    E_PVR_ATTR_PROGRAM_DESC,
    E_PVR_ATTR_PROGRAM_START_TIME,
    E_PVR_ATTR_PROGRAM_DURATION,
    E_PVR_ATTR_SERVICE_TYPE,
    E_PVR_ATTR_IS_PLAYING,
    E_PVR_ATTR_IS_RECORDING,
    PVR_PARA_NUM,
} PVR_FILE_ATTRIBUTE_MEMBER;

#ifdef MAPP_PVR_FILEBROWSER_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

////////////////////////////////////////////////////////////
///[Browser Create/Destroy]
////////////////////////////////////////////////////////////

INTERFACE   E_PVR_RET   MApp_PvrBrowser_Create(U8 u8DriveID);
INTERFACE   E_PVR_RET   MApp_PvrBrowser_Destroy(void);

////////////////////////////////////////////////////////////
///[Browser Basic Operation]
////////////////////////////////////////////////////////////
INTERFACE E_PVR_RET MApp_PvrBrowser_GetFileAttribute(PVR_FILE_ATTRIBUTE_MEMBER AttribType, SORT_TYPE sortType, U16 LogicalIndex, BYTE *pBuffer, const U16 BufLen);
INTERFACE E_PVR_RET MApp_PvrBrowser_GetFileAttributes(SORT_TYPE sortType, U16 LogicalIndex, PVR_UI_BROWSER_ENTRY *E);
INTERFACE E_PVR_RET MApp_PvrBrowser_GetRecordingAttributes(PVR_UI_BROWSER_ENTRY *E);
INTERFACE U16 MApp_PvrBrowser_GetTotalFileNum(void);
INTERFACE U16 MApp_PvrBrowser_ConvertIndex(SORT_TYPE OldSortType, U16 OldLogicalIndex, SORT_TYPE NewSortType);
INTERFACE U16 MApp_PvrBrowser_IsFileExist(U16 *FileName);
INTERFACE U16 MApp_PvrBrowser_SetAttributeByFileName(PVR_FILE_ATTRIBUTE_MEMBER AttribType, U16 *FileName, void *para);
INTERFACE E_PVR_RET MApp_PvrBrowser_DeleteFileEntry(SORT_TYPE sortType, U16 LogicalIndex);
INTERFACE E_PVR_RET MApp_PvrBrowser_GetPlayingAttribute(PVR_FILE_ATTRIBUTE_MEMBER AttribType, BYTE *pBuffer, const U16 BufLen);
INTERFACE E_PVR_RET MApp_PvrBrowser_GetRecordingAttribute(PVR_FILE_ATTRIBUTE_MEMBER AttribType, BYTE *pBuffer, const U16 BufLen);
INTERFACE U32 MApp_PvrBrowser_GetPlayingIndex(SORT_TYPE sortType);
INTERFACE U32 MApp_PvrBrowser_GetRecordingIndex(SORT_TYPE sortType);
INTERFACE E_PVR_RET MApp_PvrBrowser_AddNewEntry(PVR_UI_BROWSER_ENTRY *pNewEntry);
INTERFACE BOOLEAN MApp_PvrBrowser_IsAnyFilePlaying(void);
INTERFACE BOOLEAN MApp_PvrBrowser_IsAnyFileRecording(void);
INTERFACE U16 MApp_PvrBrowser_GetLogicalIndexByFileName(SORT_TYPE SortType, U16 *FileName);
INTERFACE BOOLEAN MApp_PvrBrowser_IsEmptyBuffer(void);
#undef INTERFACE
#endif
#endif


