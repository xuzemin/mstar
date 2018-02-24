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
#ifndef __MBFS__COMMON__
#define __MBFS__COMMON__
#include "Board.h"
#include "datatype.h"


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

#ifndef FILE_SYSTEM_SMALL
#define FILE_SYSTEM_SMALL 0
#endif

#ifndef FS_FILE_HANDLE_NUM
#define FS_FILE_HANDLE_NUM    4        //for read / write
#endif

#ifndef FS_ENVIRONMENT_NUM
#define FS_ENVIRONMENT_NUM     4
#endif

#ifndef DISK_DRIVE_NUM
#define DISK_DRIVE_NUM            16
#endif


#ifndef ENABLE_NAND
#define ENABLE_NAND 0
#endif

#ifndef ENABLE_CF
#define ENABLE_CF 0
#endif


#ifndef FILE_SYSTEM_WRITE_ENABLE
#define FILE_SYSTEM_WRITE_ENABLE   1
#endif


#if 0//ndef ENABLE_DREC
#define ENABLE_DREC 0
#endif

#ifndef FILE_SYSTEM_GET_VOLUME_LABEL_ENABLE
#define FILE_SYSTEM_GET_VOLUME_LABEL_ENABLE 0
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


#define AEON_NONCACHE_MASK  0x80000000



#if (FS_FILE_HANDLE_NUM>4)
#error "Can not have more than 4 File Handle!!!"
#endif


#if (FS_ENVIRONMENT_NUM>4)
#error "Can not have more than 4 File System Environemnt!!!"
#endif

//######## FS MEMORY


/*definition ====================================================================================*/
#define INVALID_DRIVE_INDEX                        0xff
#define INVALID_DEVICE_INDEX                    0xFF
#define INVALID_FS_ENVIRONMENT_INDEX            0xFF
#define INVALID_FILE_HANDLE                        0xff




#define FCTRL_INVALID_FILE_HANDLE                0xff
#define FCTRL_RW_DATA_CACHE_SIZE                2


#define MSD_USB_INDEX_START  0
#if ENABLE_USB
#define MSD_USB_NUM          4
#else
#define MSD_USB_NUM          0
#endif
#define MSD_USB_INDEX_END    (MSD_USB_INDEX_START+MSD_USB_NUM)

#define MSD_USB_2_INDEX_START         MSD_USB_INDEX_END
#if ENABLE_USB_2
#define MSD_USB_2_NUM         4
#else
#define MSD_USB_2_NUM         0
#endif
#define MSD_USB_2_INDEX_END   (MSD_USB_2_INDEX_START+MSD_USB_2_NUM)


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

#define STORAGE_DEVICE_NUM   (MSD_USB_NUM + MSD_USB_2_NUM + MSD_CREADER_NUM + MSD_CF_NUM + MSD_NAND_NUM)

#define STORAGE_DRIVE_NUM DISK_DRIVE_NUM

#define FILE_SYS_STRUCT_SIZE 512

#define FAT_SECTOR_SIZE_512BYTE 512

#define MAX_PATH_NAME_LEN 256


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


typedef enum
{
    MSD_PORT_0,//Card Reader
    MSD_PORT_1,//USB 1
    MSD_PORT_2,//USB 2
    MSD_PORT_3, // CF
    MSD_PORT_4, // NAND
    MSD_PORT_NUM,
    INVALID_MSD_PORT=0xFF,
}EN_MSD_PORT;

#define MAX_DEVICE_CNT 16

#define     NO_DEVICE               0
#define     USB11_DEVICE            1
#define     USB20_DEVICE            2
#define        BAD_DEVICE              3

typedef struct
{
    U32 port_connect_status;
    U8 driveNumber[MSD_PORT_NUM];
    U8 deviceStatus[MAX_DEVICE_CNT];
    U8 devicePort[MAX_DEVICE_CNT];
    U8 deviceDrvCnt[MAX_DEVICE_CNT];
    U8 usbPortStatus[MSD_PORT_NUM];
}USB_PORT_STATUS;


typedef struct
{
    U32 Hi;
    U32 Lo;
}LongLong;
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
    ENTRY_NEXT_RESULT_ERROR,
    ENTRY_NEXT_RESULT_SUCCESS,
    ENTRY_NEXT_RESULT_LAST
}EN_ENTRY_NEXT_RESULT;

typedef enum
{
    FILE_CLOSE_RESULT_ERROR,
    FILE_CLOSE_RESULT_SUCCESS,
    FILE_CLOSE_RESULT_CLOSED_ALREADY,
}EN_FILE_CLOSE_RESULT;

typedef enum
{
    FILE_SEEK_SET   = 0,
    FILE_SEEK_CUR   = 1
}EN_FILE_SEEK_OPTION;

typedef enum
{
    FILE_SYSTEM_TYPE_NONE=0,
    FILE_SYSTEM_TYPE_FAT,
    FILE_SYSTEM_TYPE_NTFS,
    FILE_SYSTEM_TYPE_EXT3,
    FILE_SYSTEM_TYPE_N51FS,
    FILE_SYSTEM_TYPE_UDF,
    FILE_SYSTEM_TYPE_ISO9660,
    FILE_SYSTEM_TYPE_ERROR=0xFF,
}EN_FILE_SYSTEM_TYPE;

typedef enum
{
    CREATE_MODE_NEW,
    CREATE_MODE_NEW_FORCE,
    CREATE_MODE_APPEND,
    CREATE_MODE_NEW_ATTR_HIDDEN
}EN_CREATE_MODE;


//284 bytes
typedef struct
{
    EN_ENTRY_TYPE  EntryType;
    LongLong FileLength;
    U32 EntryFileLength;
    U32 EntrySeconds;//since 1980/01/01/0/0/0
    U32 st_mode;
    char fullname[MAX_PATH_NAME_LEN];
    U8 EnvironmentID;
    U8 FileSystemID;//drvID
    U8 EntryAttrib;
    //char dumpfortest[140];//no used, save this memory for FILE_INFO_LONG_FILENAME_SIZE
} FileEntry;


typedef struct
{
   U8 u8EnvID;
   U32 createmode;
   U32 fileNameLength;
   char filename[256];
}FILE_CREATE_PARAM;



typedef enum
{
    FILE_SYSTEM_MOUNT_RO=0,
    FILE_SYSTEM_MOUNT_RW,
}EN_FILE_SYSTEM_MNT_MODE;

typedef struct
{
     EN_FILE_SYSTEM_TYPE fsType;
     EN_FILE_SYSTEM_MNT_MODE mountMode;
     U8 portNO;
     U8 deviceID;
     U32 totalSpaceInKB;
     U32 freeSpaceInKB;
     char devName[MAX_PATH_NAME_LEN];
     char mountpoint[MAX_PATH_NAME_LEN];
}DRIVE_INFO;

typedef struct
{
    U8 BusNO;
    U8 DriveIndex;
    U8 DeviceIndex;
    EN_FILE_SYSTEM_TYPE FileSystemType;
    U8 PartitionNo;
    U32 LBA;
}MSDCtrl_Drive;

typedef enum
{
    MSD_STATUS_EMPTY,
    MSD_STATUS_BUSY,
    MSD_STATUS_IDLE,
    MSD_STATUS_INSERTED,
    MSD_STATUS_UNPLUGGED,
    MSD_STATUS_EJECTED,
    MSD_STATUS_ERROR,
}EN_MSD_STATUS;//EMPTY->INSERTED->IDLE->BUSY->IDLE->UNPLUGGED->EMPTY


typedef enum
{
    OPEN_MODE_FOR_READ                          = 0,
    OPEN_MODE_BINARY_FOR_READ                   = 1,
    OPEN_MODE_FOR_READ_WRITE                    = 2,
    OPEN_MODE_BINARY_FOR_READ_WRITE             = 3,
    OPEN_MODE_EMPTY_FOR_WRITE                   = 4,
    OPEN_MODE_BINARY_EMPTY_FOR_WRITE            = 5,
    OPEN_MODE_EMPTY_FOR_READ_WRITE              = 6,
    OPEN_MODE_BINARY_EMPTY_FOR_READ_WRITE       = 7,
    OPEN_MODE_FOR_APPEND                        = 8,
    OPEN_MODE_BINARY_FOR_APPEND                 = 9,
    OPEN_MODE_FOR_READ_APPEND                   = 10,
    OPEN_MODE_BINARY_FOR_READ_APPEND            = 11,
    OPEN_MODE_FAST_FOR_READ                     = 0x80,
    OPEN_MODE_NONE                              =0xFF,
}EN_OPEN_MODE;

 LongLong LL_add(LongLong* pLongLong,U32 val);
 LongLong LL_add_signed(LongLong* pLongLong,S32 val);
 LongLong LL_addLong(LongLong* pX,LongLong* pY);
 LongLong LL_subtract(LongLong* pLongLong,U32 val);
 LongLong LL_subtractLong(LongLong *pX, LongLong *pY);
 BOOLEAN LL_equal(LongLong* pX,LongLong* pY);

 BOOLEAN LL_greater(LongLong* pX,LongLong* pY);
 BOOLEAN LL_greater_or_equal(LongLong* pX,LongLong* pY);
 BOOLEAN LL_iszero(LongLong *pX);
 void LL_assign(LongLong* pX,U32 val);
 LongLong LL_multU32(U32 x, U32 y);
 LongLong LL_LongMultU32(LongLong *pLongLong, U32 y);
 LongLong LL_rshift(LongLong *pX, U8 bitCount);


#define IS_DOT_OR_DOTDOT(s) ((s)[0] == '.' && (!(s)[1] || ((s)[1] == '.' && !(s)[2])))
#define IS_DIR_DOT(s) ((s)[0] == '.' && (s)[1]==0)
#define IS_DIR_DOTDOT(s) ((s)[0] == '.' && (s)[1] == '.' && (s)[2]==0)

#endif
