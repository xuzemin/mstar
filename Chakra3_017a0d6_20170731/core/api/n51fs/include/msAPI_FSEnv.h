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
#ifndef _MSAPI_FSENV_H
#define _MSAPI_FSENV_H

#if OBA2
#include "N51FS_Wrapper.h"
#else

#include "datatype.h"
#include "debug.h"

#ifdef _MSAPI_FSENV_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

typedef struct
{
    U8 u8CurrentDirectoryIndex;
    U8 u8FileSystemID;
    U8 u8FileSystemType;
    U8 u8DeviceIndex;
    BOOLEAN bIsInit;
}  FS_EnvironmentStruct;

#define FS_DEFAULT_YEAR                           1980
#define FS_DEFAULT_MONTH                       1
#define FS_DEFAULT_DAY                             1
#define FS_DEFAULT_HOUR                          0
#define FS_DEFAULT_MIN                              0
#define FS_DEFAULT_SEC                             0

#define SECONDS_PER_MIN         60L
#define SECONDS_PER_HOUR        3600L
#define SECONDS_PER_HALF_HOUR    1800L
#define SECONDS_PER_DAY            86400L
#define MINS_PER_HOUR            60
#define HOURS_PER_DAY            24

typedef struct
{
    U16 u16Year;
    U8 u8Month;
    U8 u8Day;
    U8 u8Hour;
    U8 u8Min;
    U8 u8Sec;
} FS_TIME;

//msAPI_FSEnv  => n51fs
INTERFACE U8    FS_u8var0;
INTERFACE U8    FS_u8var1;
INTERFACE U8    FS_u8var2;
INTERFACE U8    FS_u8var3;
INTERFACE U8    FS_u8var4;

INTERFACE U16   FS_u16var0;
INTERFACE U16   FS_u16var1;
INTERFACE U16   FS_u16var2;
INTERFACE U16   FS_u16var3;

INTERFACE U32   FS_u32var0;
INTERFACE U32   FS_u32var1;
INTERFACE U32   FS_u32var2;
INTERFACE U32   FS_u32var3;
INTERFACE U32   FS_u32var4;
INTERFACE U32   FS_u32var5;
INTERFACE U32   FS_u32var6;
INTERFACE U32   FS_u32var7;

INTERFACE U16*  FS_pu16var0;
INTERFACE U32*  FS_pu32var0;

//used in FAT_FATXXClusterScan
#define s_u8ReadSectorCount      FS_u8var0
#define s_u16FATEntryCacheCount  FS_u16var0
#define s_u16FATEntryCacheOffset FS_u16var1
#define s_u16Count               FS_u16var2
#define s_u32ClusterNo           FS_u32var0
#define s_u32SectorNo            FS_u32var1
#define s_pu16FAT16EntryCache      FS_pu16var0
#define s_pu32FAT32EntryCache      FS_pu32var0

//used in FAT_Cache for DirEntryIterator
#define itrFSID                               FS_u8var0
#define itrDeviceIndex                        FS_u8var1
#define itrSectorsPerCluster                  FS_u8var2
#define itrFATType                            FS_u8var3
#define itrDirEntryCacheSectorCount           FS_u8var4

#define itrBytesPerSector                    FS_u16var0
#define itrCurrentCacheOffsetSector          FS_u16var1
#define itrCurrentCacheDirEntryIndex         FS_u16var2
#define itrDirEntryCacheCount                FS_u16var3

#define itrDirectoryStartCluster             FS_u32var0
#define itrBufferAddress                     FS_u32var1
#define itrRootEntryCount                    FS_u32var2
#define itrTotalClusters                     FS_u32var3
#define itrRootDirectoryStartCluster         FS_u32var4
#define itrRootDirectoryTotalSectorCount     FS_u32var5
#define itrCurrentCacheCluster               FS_u32var6
#define itrCurrentDirEntryIndex              FS_u32var7

#define FILE_ENVIRONMENT_MEMORY_SIZE 0x4000UL//0x6000UL
#define FILE_HANDLE_MEMORY_SIZE 0x1400UL//0x2000UL
#define FILE_INODE_MEMORY_SIZE 0x1400UL//0x2000UL
#define FILE_SYSTEM_SECTOR_BYTES 0x200
#define FILE_SYSTEM_SECTOR_REMAIN_MASK  0x1FF//
#define FAT_TABLE_CACHE_LEN         0x1000UL              // 4K
#define FILE_SYS_STRUCT_SIZE 256//512
#define FAT_SECTOR_SIZE_512BYTE 512


#if (ENABLE_N51FS)
#define MIN_FS_MEMORY 0x1B000
#else
#define MIN_FS_MEMORY 0x14000
#endif

#ifndef MemAlign
#define MemAlign(n, unit)   ( (((n)+(unit)-1)/(unit)) * (unit) )
#endif

INTERFACE U32 _FILE_SYSTEM_POOL_ADR;
INTERFACE U32 _FILE_SYSTEM_POOL_LEN;
INTERFACE U8 FS_FILE_HANDLE_NUM;
INTERFACE U8 FS_ENVIRONMENT_NUM;
INTERFACE U8 DISK_DRIVE_NUM;

#if (MEMORY_MAP <= MMAP_32MB)
#define MAX_FS_FILE_HANDLE_NUM  4
#define MAX_FS_ENVIRONMENT_NUM  3
#define MAX_DISK_DRIVE_NUM      8
#else
#define MAX_FS_FILE_HANDLE_NUM  6
#define MAX_FS_ENVIRONMENT_NUM  4
#define MAX_DISK_DRIVE_NUM      16
#endif

// ######## FS MEMORY
INTERFACE U32 USB_IO_TEMP_ADDR;
INTERFACE U32 USB_IO_TEMP_ADDR_CACHE;
#define USB_IO_TEMP_LEN                 0x1000UL

INTERFACE U32 USB_IO_TEMP_ADDR2;
#if (MEMORY_MAP <= MMAP_32MB)
#define USB_IO_TEMP_LEN2                USB_IO_TEMP_LEN
#else
#define USB_IO_TEMP_LEN2         0x10000UL
#endif

INTERFACE U32 DEVICE_IO_BUFFER_ADDR;
#define DEVICE_IO_BUFFER_LEN           0x1000UL

//following define should be used only in msAPI_MSDCtrl for W/R
INTERFACE U32 STORAGE_DEVICE_MEMORY_ADDR;
#define STORAGE_DEVICE_MEMORY_LEN       0x400UL//0x800UL    // 2K  5 * 2 (sizeof(StorageDevice))

INTERFACE U32 DRIVE_MEMORY_ADDR;
#define DRIVE_MEMORY_LEN                0x400UL//0x800UL   // 2K  0x800>16 * 13 ( sizeof(MSDCtrl_Drive))

INTERFACE U32 FILE_SYSTEM_MOUNTED_ADDR;
#define FILE_SYSTEM_MOUNTED_LEN         0x1000UL  //4K  16 * 256(FAT_FileSysStruct or N51FS_FileSysStruct)


INTERFACE U32 FILE_ENVIRONMENT_POOL;
INTERFACE U32 FILE_ENVIRONMENT_POOL_LEN;

INTERFACE U32 FILE_FAT_TABLE_CACHE;
INTERFACE U32 FILE_FAT_TABLE_CACHE_LEN;


INTERFACE U32 FILE_INODE_POOL;
INTERFACE U32 FILE_INODE_POOL_LEN;

INTERFACE U32 FILE_HANDLE_POOL;
INTERFACE U32 FILE_HANDLE_POOL_LEN;


#if (ENABLE_N51FS)
INTERFACE U32 N51FS_TEMP_4K_BACKUP_BUFFER_0;
#define N51FS_TEMP_4K_BACKUP_BUFFER_0_LEN       0x1000UL

INTERFACE U32 N51FS_TEMP_4K_BACKUP_BUFFER_1;
#define N51FS_TEMP_4K_BACKUP_BUFFER_1_LEN       0x1000UL

INTERFACE U32 N51FS_TEMP_4K_BACKUP_BUFFER_2;
#define N51FS_TEMP_4K_BACKUP_BUFFER_2_LEN       0x1000UL

INTERFACE U32 N51FS_TEMP_4K_BUFFER_0;
#define N51FS_TEMP_4K_BUFFER_0_LEN       0x1000UL

INTERFACE U32 N51FS_TEMP_4K_BUFFER_1;
#define N51FS_TEMP_4K_BUFFER_1_LEN       0x1000UL

INTERFACE U32 N51FS_INDEX_BUFFER_ADDR;
#define N51FS_INDEX_BUFFER_LEN          0x1000UL

INTERFACE U32 N51FS_TEMP_4K_FIXUP;
#define N51FS_TEMP_4K_FIXUP_LEN       0x1000UL

INTERFACE U32 FS_MEMORY_MAP_END;

//~!~
INTERFACE U32   N51FS_CB_SRC_BUFFER_ADDR;
#define N51FS_CB_SRC_LEN 0x10000
INTERFACE U32   N51FS_CB_DST_BUFFER_ADDR;
#define N51FS_CB_DST_LEN 0x10000

#ifdef NTFS_DECOMPRESS_BUF_ADR
    #if ((N51FS_CB_SRC_LEN + N51FS_CB_DST_LEN) <= NTFS_DECOMPRESS_BUF_LEN)
        #define SUPPORT_COMPRESS    1
    #else
        #define SUPPORT_COMPRESS    0
    #endif
#else
    #define SUPPORT_COMPRESS    0
#endif

#else

INTERFACE U32 FS_MEMORY_MAP_END;
#endif
//######## FS MEMORY

INTERFACE U32 XDataAddr[4][4];

INTERFACE  BOOLEAN msAPI_FSEnv_Init(U32 u32FS_adr,U32 u32FS_len);
INTERFACE  U8 msAPI_FSEnv_Register(U8 u8DriveNo);
INTERFACE  void msAPI_FSEnv_UnRegister(U8 u8HandleNo);
INTERFACE  FS_EnvironmentStruct* msAPI_FSEnv_GetEnvironment(U8 u8HandleNo);
INTERFACE U32 msAPI_FS_GetAddr(U32 addr);

INTERFACE FS_TIME msAPI_FS_GetLocalTime(void);
INTERFACE void msAPI_FS_ConvertSeconds2StTime ( U32 u32SystemTime, FS_TIME *pstTime );
INTERFACE U32 msAPI_FS_ConvertStTime2Seconds ( FS_TIME *pstTime );

#undef INTERFACE
#endif
#endif
