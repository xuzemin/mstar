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
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// @file
// @brief
// @author MStarSemi Inc.
//
//-
//-
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _MSAPI_FSCOMMON_H
#define    _MSAPI_FSCOMMON_H

#if OBA2
#include "Wrapper_Common.h"
#else

#include "datatype.h"
#include "debug.h"
#include "msAPI_FS_SysInfo.h"

#ifdef FS_UTIL_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

//device compile flag setting
#ifndef ENABLE_USB
#define ENABLE_USB 1
#endif

#ifndef ENABLE_USB_2
#define ENABLE_USB_2 0
#endif

#ifndef ENABLE_NAND
#define ENABLE_NAND 0
#endif

#ifndef ENABLE_CF
#define ENABLE_CF 0
#endif

//NTFS support
#ifndef ENABLE_N51FS
#define ENABLE_N51FS 1
#endif

#ifndef FILE_SYSTEM_SMALL
#define FILE_SYSTEM_SMALL 0
#endif

#ifndef FILE_SYSTEM_WRITE_ENABLE
#define FILE_SYSTEM_WRITE_ENABLE   1
#endif

#ifndef FAT_CACHE_PREV_ENABLE
#define FAT_CACHE_PREV_ENABLE 0
#endif

#ifndef ENABLE_DREC
#define ENABLE_DREC 0
#endif

#ifndef FILE_SYSTEM_GET_VOLUME_LABEL_ENABLE
#define FILE_SYSTEM_GET_VOLUME_LABEL_ENABLE 1
#endif

#ifndef FILE_SYSTEM_GET_FREE_SPACE_ENABLE
#define FILE_SYSTEM_GET_FREE_SPACE_ENABLE 1
#endif

#ifndef FILE_SYSTEM_GET_TOTAL_SIZE_ENABLE
#define FILE_SYSTEM_GET_TOTAL_SIZE_ENABLE 1
#endif

#ifndef FILE_SYSTEM_SEARCH_BY_SHORT_NAME_ENABLE
#define FILE_SYSTEM_SEARCH_BY_SHORT_NAME_ENABLE 1
#endif

#ifndef FILE_SYSTEM_FOLDER_CREATE_ENABLE
#define FILE_SYSTEM_FOLDER_CREATE_ENABLE 0
#endif

#ifndef FILE_SYSTEM_GET_FILENAME_BY_FILEENTRY_ENABLE
#define FILE_SYSTEM_GET_FILENAME_BY_FILEENTRY_ENABLE 1
#endif

#ifndef FILE_SYSTEM_FILE_TELL_ENABLE
#define FILE_SYSTEM_FILE_TELL_ENABLE 1
#endif

#ifndef FILE_SYSTEM_LONGLONG_API_ENABLE
#define FILE_SYSTEM_LONGLONG_API_ENABLE 1
#endif

#ifndef FILE_SYSTEM_FORMAT_ENABLE
#define FILE_SYSTEM_FORMAT_ENABLE   1//0
#endif

#ifndef FILE_SYSTEM_LIMIT_IO_SECTORS
#define FILE_SYSTEM_LIMIT_IO_SECTORS 1
#endif


#ifndef FILE_SYSTEM_ENABLE_START_DEVICE
#define FILE_SYSTEM_ENABLE_START_DEVICE 1
#endif


#ifndef FILE_SYSTEM_ENABLE_IS_CURRENT_NAME_SHORT_ONLY
#define FILE_SYSTEM_ENABLE_IS_CURRENT_NAME_SHORT_ONLY 1
#endif


#ifndef FILE_SYSTEM_ENABLE_TELL_LONG_LONG
#define FILE_SYSTEM_ENABLE_TELL_LONG_LONG 1
#endif


#ifndef FILE_SYSTEM_ENABLE_GET_SUPPORT_MODE
#define FILE_SYSTEM_ENABLE_GET_SUPPORT_MODE 1
#endif


#ifndef FILE_SYSTEM_ENABLE_SET_SUPPORT_MODE
#define FILE_SYSTEM_ENABLE_SET_SUPPORT_MODE 1
#endif


#ifndef FILE_SYSTEM_ENABLE_ENTRY_GET_BY_HANDLE
#define FILE_SYSTEM_ENABLE_ENTRY_GET_BY_HANDLE 1
#endif

#ifndef FILE_SYSTEM_ENABLE_GET_MAX_DEVICE_COUNT
#define FILE_SYSTEM_ENABLE_GET_MAX_DEVICE_COUNT 1
#endif

#ifndef FILE_SYSTEM_ENABLE_MSD_IS_PORT_CHANGED
#define FILE_SYSTEM_ENABLE_MSD_IS_PORT_CHANGED  1
#endif

#ifndef FILE_SYSTEM_ENABLE_MSD_RESET_PORTS
#define FILE_SYSTEM_ENABLE_MSD_RESET_PORTS 1
#endif

#ifndef FILE_SYSTEM_ENABLE_MSD_CHECK_DEVICES_ON_PORTS
#define FILE_SYSTEM_ENABLE_MSD_CHECK_DEVICES_ON_PORTS 1
#endif

#ifndef FILE_SYSTEM_ENABLE_MSD_GET_BLOCK_SIZE
#define FILE_SYSTEM_ENABLE_MSD_GET_BLOCK_SIZE 1
#endif

#ifndef FILE_SYSTEM_ENABLE_MSD_DEVICES_CHANGE_STATUS_CHECK
#define FILE_SYSTEM_ENABLE_MSD_DEVICES_CHANGE_STATUS_CHECK 1
#endif

#ifndef FILE_SYSTEM_ENABLE_FCTRL_DIRECTORY_CHANGE_TO_CONTAINED
#define FILE_SYSTEM_ENABLE_FCTRL_DIRECTORY_CHANGE_TO_CONTAINED 1
#endif

#ifndef FILE_SYSTEM_ENABLE_FCTRL_GET_DIRECTORY_DOT
#define FILE_SYSTEM_ENABLE_FCTRL_GET_DIRECTORY_DOT 1
#endif

#ifndef FILE_SYSTEM_ENABLE_FCTRL_RESET_DEVICES
#define FILE_SYSTEM_ENABLE_FCTRL_RESET_DEVICES 1
#endif

#ifndef FILE_SYSTEM_ENABLE_FCTRL_GET_DRIVE_COUNT_BY_PORT
#define FILE_SYSTEM_ENABLE_FCTRL_GET_DRIVE_COUNT_BY_PORT 1
#endif

#ifndef FILE_SYSTEM_ENABLE_FCTRL_ENTRY_SEARCH_BY_NAME
#define FILE_SYSTEM_ENABLE_FCTRL_ENTRY_SEARCH_BY_NAME 1
#endif

/*definition ====================================================================================*/
#define INVALID_DRIVE_INDEX                        0xff
#define INVALID_DEVICE_INDEX                    0xFF
#define INVALID_FS_ENVIRONMENT_INDEX            0xFF
#define INVALID_FILE_HANDLE                     0xff
#define INVALID_FILE_INODEID                    0xff
#define INVALID_MBR_INDEX                       0xFF
#define INVALID_MBR_ADDRESS                     0xFFFFFFFF

#define FCTRL_INVALID_FILE_HANDLE                0xff
#define FCTRL_RW_DATA_CACHE_SIZE                2

#define MSD_USB_INDEX_START  0
#if ENABLE_USB
#define MSD_USB_NUM          5 // 4
#else
#define MSD_USB_NUM          0
#endif
#define MSD_USB_INDEX_END    (MSD_USB_INDEX_START+MSD_USB_NUM)

#define MSD_USB_2_INDEX_START         MSD_USB_INDEX_END
#if ENABLE_USB_2
#define MSD_USB_2_NUM         5 // 4
#else
#define MSD_USB_2_NUM         0
#endif
#define MSD_USB_2_INDEX_END   (MSD_USB_2_INDEX_START+MSD_USB_2_NUM)


#define MSD_USB_3_INDEX_START         MSD_USB_2_INDEX_END
#if ENABLE_USB_3
#define MSD_USB_3_NUM         5 // 4
#else
#define MSD_USB_3_NUM         0
#endif
#define MSD_USB_3_INDEX_END   (MSD_USB_3_INDEX_START+MSD_USB_3_NUM)

#define MSD_USB_4_INDEX_START         MSD_USB_3_INDEX_END
#if ENABLE_USB_4
#define MSD_USB_4_NUM         5 // 4
#else
#define MSD_USB_4_NUM         0
#endif
#define MSD_USB_4_INDEX_END   (MSD_USB_4_INDEX_START+MSD_USB_4_NUM)



#define MSD_CREADER_INDEX_START  MSD_USB_2_INDEX_END
#if ENABLE_CARDREADER
#define MSD_CREADER_NUM          1
#else
#define MSD_CREADER_NUM          0
#endif
#define MSD_CREADER_INDEX_END (MSD_CREADER_INDEX_START+MSD_CREADER_NUM)


#define MSD_CF_INDEX_START  MSD_CREADER_INDEX_END
#if defined(ENABLE_CF) && (ENABLE_CF == 1)
#define MSD_CF_NUM           (1)
#else
#define MSD_CF_NUM           (0)
#endif
#define MSD_CF_INDEX_END     (MSD_CF_INDEX_START + MSD_CF_NUM)

#define MSD_NAND_INDEX_START  MSD_CF_INDEX_END
#if (ENABLE_NAND)
#define MSD_NAND_NUM           (1)
#else
#define MSD_NAND_NUM           (0)
#endif
#define MSD_NAND_INDEX_END     (MSD_NAND_INDEX_START + MSD_NAND_NUM)

#define STORAGE_DEVICE_NUM   (MSD_USB_NUM + MSD_USB_2_NUM + MSD_USB_3_NUM + MSD_USB_4_NUM + MSD_CREADER_NUM + MSD_CF_NUM + MSD_NAND_NUM)

#define FS_SETBIT(REG, BIT)   ((REG) |= (1UL << (BIT)))
#define FS_GETBIT(REG, BIT)   (((REG) >> (BIT)) & 0x01UL)

//CHAR
#define FS_CHAR_SPACE           0x0020
#define FS_CHAR_DOT             0x002E
#define FS_CHAR_STAR            0x002A
#define FS_CHAR_SLASH           0x002F
#define FS_CHAR_GT              0x003E
#define FS_CHAR_COLON           0x003A
#define FS_CHAR_QM              0x003F

/*enum ================================================================================*/
typedef enum
{
    FILE_SYSTEM_TYPE_NONE=0,
    FILE_SYSTEM_TYPE_FAT,
    FILE_SYSTEM_TYPE_NTFS,
    FILE_SYSTEM_TYPE_N51FS = FILE_SYSTEM_TYPE_NTFS,
}EN_FILE_SYSTEM_TYPE;

typedef enum
{
    DRIVE_INITIAL_STATUS_ERROR,
    DRIVE_INITIAL_STATUS_SUCCESS,
    DRIVE_INITIAL_STATUS_NO_SLOT,
    DRIVE_INITIAL_STATUS_MOUNTED_ALREADY,

}EN_DRIVE_INITIAL_STATUS;

typedef enum
{
    MSD_DEVICE_TYPE_NONE = 0,
    MSD_DEVICE_TYPE_USBDISK,    //usb disk
    MSD_DEVICE_TYPE_CREADER     //card reader
}EN_MSD_DEVICE_TYPE;


typedef enum
{
    ENTRY_TYPE_FILE,
    ENTRY_TYPE_DIR,
    ENTRY_TYPE_DIR_DOT,      // Current directory
    ENTRY_TYPE_DIR_DOTDOT,   // Parent directory
    ENTRY_TYPE_LAST,
    ENTRY_TYPE_NULL=0xFF,
} EN_ENTRY_TYPE;

typedef enum
{
    DEVICE_START_STATUS_ERROR,  // must be 0 due to capability.do not change this value.
    DEVICE_START_STATUS_SUCCESS,// must be 1 due to capability.do not change this value.
    DEVICE_START_STATUS_STARTED_ALREADY,
}EN_DEVICE_START_STATUS;

typedef enum
{
    ENTRY_NEXT_RESULT_ERROR,
    ENTRY_NEXT_RESULT_SUCCESS,
    ENTRY_NEXT_RESULT_LAST
}EN_ENTRY_NEXT_RESULT;

typedef enum
{
    ENTRY_CREATE_RESULT_ERROR,
    ENTRY_CREATE_RESULT_SUCCESS,
    ENTRY_CREATE_RESULT_LAST,
    ENTRY_CREATE_RESULT_FREE,
    ENTRY_CREATE_RESULT_FULL
}EN_ENTRY_CREATE_RESULT;

typedef enum
{
    FILE_SYSTEM_SUPPORT_NONE        =0x0,
    FILE_SYSTEM_SUPPORT_READ        =0x1,
    FILE_SYSTEM_SUPPORT_WRITE       =0x2,
    FILE_SYSTEM_SUPPORT_DELETE      =0x4
}EN_FILE_SYSTEM_SUPPORT;

/*===============================================================================================*/



/*data structure ================================================================================*/
typedef struct
{
    U32 Hi;
    U32 Lo;
}LongLong;

//<< MSDCtrl_Drive STRUCTURE>>======================================================================//
typedef struct
{
    U8 DriveIndex;
    U8 DeviceIndex;
    EN_FILE_SYSTEM_TYPE FileSystemType;
    U8 PartitionNo;
    U32 LBA;
    U32 u32MBRLogicBlockAddress;
    U8 u8IndexInMBR;
}MSDCtrl_Drive;


//<< FileEntry STRUCTURE>>======================================================================//
//40 bytes
typedef struct
{
    EN_ENTRY_TYPE  EntryType;
    LongLong FileLength;
    U32 EntryFileLength;
    U32 EntrySeconds;//since 1980/01/01/0/0/0
    U8 EntryID[8];
    U8 EntryID_Ext[8];
    U8 EnvironmentID;
    U8 FileSystemID;
    U8 EntryAttrib;
} FileEntry;


//<< FileHandleStruct STRUCTURE>>======================================================================//
typedef struct
{
    U8 HandleID;
    U8 InodeID;
    U8 FileSystemID;
    //Open Mode
    U8 OpenMode;

}FileHandleStruct;

//<< FileHandleStruct STRUCTURE>>======================================================================//
typedef struct
{
    U8 InodeID;
    U8 FileSystemID;
    U8 refCnt;
    FileEntry stFileEntry;

}FileInodeStruct;


INTERFACE LongLong LL_add(LongLong* pLongLong,U32 val);
INTERFACE LongLong LL_add_signed(LongLong* pLongLong,S32 val);
INTERFACE LongLong LL_addLong(LongLong* pX,LongLong* pY);
INTERFACE LongLong LL_subtract(LongLong* pLongLong,U32 val);
INTERFACE LongLong LL_subtractLong(LongLong *pX, LongLong *pY);
INTERFACE BOOLEAN LL_equal(LongLong* pX,LongLong* pY);

INTERFACE BOOLEAN LL_greater(LongLong* pX,LongLong* pY);
INTERFACE BOOLEAN LL_greater_or_equal(LongLong* pX,LongLong* pY);
INTERFACE BOOLEAN LL_iszero(LongLong *pX);
INTERFACE void LL_assign(LongLong* pX,U32 val);
INTERFACE LongLong LL_multU32(U32 x, U32 y);
INTERFACE LongLong LL_LongMultU32(LongLong *pLongLong, U32 y);
INTERFACE LongLong LL_rshift(LongLong *pX, U8 bitCount);
//INTERFACE LongLong LL_mult(LongLong *pX, U32 val);
INTERFACE LongLong LL_LongDivU32(LongLong* x, U32 y);

#undef INTERFACE
#endif /*OBAMA*/
#endif    /*_MSAPI_FSCOMMON_H END */
