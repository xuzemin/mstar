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

#ifndef MSAPI_PVR_FILE_SYSTEM_H
#define MSAPI_PVR_FILE_SYSTEM_H

#include "datatype.h"
#include "Board.h"
#include "msAPI_FSCommon.h"
#include "msAPI_FS_SysInfo.h"
#include "msAPI_BulkFileSystem.h"

#ifdef OBAMA
#define __PVRFS_SUPPORT_PARTITION__ 0
#else
#define __PVRFS_SUPPORT_PARTITION__ 1
#endif

#define FAT_MAX_FILE_LENGTH         0xFFFFFFFF //2^32-1

#ifdef MSAPI_PVR_FILE_SYSTEM_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

#define PVR_FOLDER           {'_','M','S','T','P','V','R',0}
#define PVR_SECURE_CONTENT_FOLDER           {'S','e','c','u','r','e',0}
#define PVR_PIN_EVENT_MAP_FILENAME          {'P','V','R','P','i','n','E','v','e','n','t','.','b','i','n',0}
#define PVR_URI_LICENSE_MAP_FILENAME        {'P','V','R','U','r','i','L','i','c','e','n','s','e','.','b','i','n',0}

typedef enum
{
    PVR_FS_BULKFS = 0,
    PVR_FS_N51FAT32,
    PVR_FS_LINUX_FAT,
    PVR_FS_LINUX_NTFS,
    PVR_FS_LINUX_EXT2,
    PVR_FS_LINUX_EXT3,
    PVR_FS_LINUX_UNSUPPORTED,
    PVR_FS_MAX,
}EN_PVRFS_FSTYPE;

typedef enum
{
    PVRFS_OPEN_FOR_READ, //file read: playback
    PVRFS_OPEN_FOR_WRITE, //file write: record
    PVRFS_OPEN_FOR_RING_WRITE, //file read/write: timeshifting
}EN_PVRFS_OPEN_MODE;

typedef enum
{
    PVRFS_SEEK_OPTION_FROM_BEGIN,
    PVRFS_SEEK_OPTION_FROM_CURRENT_FORWARD,
    PVRFS_SEEK_OPTION_FROM_CURRENT_BACKWARD, //Support for BKFS only
}EN_PVRFS_SEEK_OPTION;

/*******************************************************/
/****************** Global Variables *******************/
/*******************************************************/

extern U16 g_u16DiskSpeed;


INTERFACE void msAPI_PVRFS_FAT32Test(void);
/***************** Environment Handle ******************/
INTERFACE BOOLEAN msAPI_PVRFS_SetFileSystemType(EN_PVRFS_FSTYPE type);
INTERFACE EN_PVRFS_FSTYPE msAPI_PVRFS_GetFileSystemType(void);
INTERFACE BOOLEAN msAPI_PVRFS_IsLinuxFileSystemType(EN_PVRFS_FSTYPE enPVRFSFileSystemType);
INTERFACE BOOLEAN msAPI_PVRFS_SetDeviceIndex(U8 u8DeviceIndex);
INTERFACE BOOLEAN msAPI_PVRFS_SetDiskDriveIndex(U8 u8DriveIndex);
INTERFACE U8 msAPI_PVRFS_GetDriveIndex(void);
INTERFACE U8 msAPI_PVRFS_GetDeviceIndex(void);
INTERFACE BOOLEAN msAPI_PVRFS_IsInitialized(void);
INTERFACE BOOLEAN msAPI_PVRFS_Initial(BOOLEAN force);
INTERFACE void msAPI_PVRFS_Reset(void);
INTERFACE BOOLEAN msAPI_PVRFS_SetMemory(U32 poolAddress,U32 len);
/************************ Disk *************************/
INTERFACE U32 msAPI_PVRFS_GetDriveFreeSpaceMB(void);
INTERFACE U32 msAPI_PVRFS_GetAvailableDiskSizeMB(U8 u8EnvironmentID);
INTERFACE BOOLEAN msAPI_PVRFS_IsDeviceRAWDisk(U8 u8DeviceIndex);
INTERFACE U16 msAPI_PVRFS_SpeedCheck(void);
/********************** FAT Table **********************/
#ifdef OBAMA
INTERFACE BOOLEAN msAPI_PVRFS_Format(EN_PVRFS_FSTYPE ePVRFSFileSystemType, U8 u8DiskDriveIndex);
INTERFACE U8 msAPI_PVRFS_GetFormatPercentage(void);
#else
INTERFACE BOOLEAN msAPI_PVRFS_Format(U32 u32MBRLogicBlockAddress, U8 u8IndexInMBR, U32* u32WriteCount, BOOLEAN* bFinished);
INTERFACE U32 msAPI_PVRFS_GetFATFormatWriteCnt(U8 u8DriveNo);
#endif
INTERFACE BOOLEAN msAPI_PVRFS_IsFormated(U8 u8DiskDriveIndex);
/******************* Partition Table *******************/
INTERFACE BOOLEAN msAPI_PVRFS_IsPartitionReady(U8 u8DiskDriveIndex,U8 u8DeviceIndex);
#if __PVRFS_SUPPORT_PARTITION__
/*Interface for disk partition support*/
//INTERFACE BOOLEAN msAPI_PVRFS_FDISK_Format_TEST(void);
INTERFACE BOOLEAN msAPI_PVRFS_ClearMBR(U8 u8DeviceIndex, U32 lba);
INTERFACE BOOLEAN msAPI_PVRFS_AddMainPartition( U8 u8DeviceIndex, U8 partitionID, BOOLEAN isMainPartition, U32 startLBA, U32 LBACnt);
INTERFACE BOOLEAN msAPI_PVRFS_AddLogicPartition(U8 u8DeviceIndex,  U8 expandPartitionID, U8 logicPartitionID, U32 startLBA, U32 LBACnt);
#endif //__PVRFS_SUPPORT_PARTITION__
/********************* File Handle *********************/
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
INTERFACE BOOL msAPI_CIPVRFS_FileCreate(U16* pu16FileName, U8 *pineventhander, U8 *urilicensehander);
INTERFACE BOOL msAPI_CIPVRFS_FileOpen(U16* pu16FileName, EN_PVRFS_OPEN_MODE mode, U8 *pineventhander, U8 *urilicensehander);
INTERFACE U32 msAPI_CIPVRFS_FileWrite(U8 u8HandleID,U32 u32Buffer,U32 u32WriteLength);
INTERFACE BOOL msAPI_CIPVRFS_FileClose(U8 pineventHandleID, U8 urilicenseHandleID);
INTERFACE BOOL msAPI_CIPVRFS_FileDelete(U16* pu16FileName);
#endif
INTERFACE U8 msAPI_PVRFS_FileCreate(U16* pu16FileName);
INTERFACE U8 msAPI_PVRFS_FileOpen(U16* pu16FileName,EN_PVRFS_OPEN_MODE mode);
INTERFACE BOOLEAN msAPI_PVRFS_FileClose(U8 u8HandleID);
INTERFACE BOOLEAN msAPI_PVRFS_FileDelete(U16* pu16FileName);
//INTERFACE BOOLEAN msAPI_PVRFS_FileExist_InPVRDirectory(U8 u8EnvironmentID, U16* pu16FileName);
INTERFACE BOOLEAN msAPI_PVRFS_FileExist(U16* pu16FileName);
INTERFACE LongLong msAPI_PVRFS_FileLength(U8 u8HandleID);
INTERFACE U32 msAPI_PVRFS_FileRead(U8 u8HandleID, U32 u32Buffer, U32 u32ReadLength);
INTERFACE U32 msAPI_PVRFS_FileWrite(U8 u8HandleID,U32 u32Buffer,U32 u32WriteLength);
INTERFACE BOOLEAN msAPI_PVRFS_FileSeek(U8 u8HandleID,LongLong seekLength,EN_PVRFS_SEEK_OPTION option);
INTERFACE LongLong msAPI_PVRFS_FileTell(U8 u8HandleID);
INTERFACE BOOLEAN msAPI_PVRFS_GetFirstPVRFile(U8 u8EnvironmentID, FileEntry* fileEntry);
INTERFACE BOOLEAN msAPI_PVRFS_GetNextPVRFile(U8 u8EnvironmentID, FileEntry* fileEntry);
INTERFACE U8 msAPI_PVRFS_GetFileNameByFileEntry(U8 u8EnvironmentID, FileEntry* pEntry, U32 address, U8 charLen);

//Bulk only
#if (ENABLE_BULK_FILE_SYSTEM)
INTERFACE BOOLEAN msAPI_PVRFS_CreateBulks(EN_CREATE_BULKS_STATE enCreateBulksState, U8 u8EnvironmentID, U16* u16BulkNum);
INTERFACE BKFS_POSITION msAPI_PVRFS_FindFirstPOS(void);
INTERFACE BKFS_POSITION msAPI_PVRFS_FindNextBulkFile(BKFS_POSITION pos, U16 *pCurBulkFileName,  U16 *pBufU16Len);
INTERFACE BFK_PARA_OPT_RES msAPI_PVRFS_SetBulkFileInfo(U16* pu16BulkFileName, U16* u16BulkFileID, BFK_PROG_INFO info, void *pBuffer, U16 bufLen);
INTERFACE BFK_PARA_OPT_RES msAPI_PVRFS_GetBulkFileInfo(U16* pu16BulkFileName, U16* u16BulkFileID, BFK_PROG_INFO info, void *pBuffer, U16 *pBufLen);
INTERFACE U32 msAPI_PVRFS_GetBulkVersionNo(void);
INTERFACE U32 msAPI_PVRFS_GetTotalDiskSizeSetToUsedMB(void);
INTERFACE U16 msAPI_PVRFS_GetTotalBulkCnt(void);
INTERFACE U16 msAPI_PVRFS_GetBulkRWKByteOfSpeed(void);
INTERFACE U16 msAPI_PVRFS_GetBulksNumToCreate(void);
INTERFACE BOOLEAN msAPI_PVRFS_SetBulkSpeed(U16 u16Speed);
INTERFACE U16 msAPI_PVRFS_GetBulkSpeed(void);
INTERFACE BOOLEAN msAPI_PVRFS_SetBulkRWKByteOfSpeed(U16 u16RWKByteOfSpeed);
INTERFACE U16 msAPI_PVRFS_GetBulkRWKByteOfSpeed(void);
INTERFACE BOOLEAN msAPI_PVRFS_SetTimeShiftReservedBulkCnt(U16 u16BulkCnt);
INTERFACE U16 msAPI_PVRFS_GetTimeShiftReservedBulkCnt(void);
INTERFACE BOOLEAN msAPI_PVRFS_SetTimeShiftRecordLengthMB(U32 u32TimeShiftRecordLengthMB);
INTERFACE U32 msAPI_PVRFS_GetTimeShiftRecordLengthMB(void);
INTERFACE BOOLEAN msAPI_PVRFS_SetMaxUsedBulkFileEntryIndex(U16 u16MaxUsedBulkFileEntryIndex);
INTERFACE U16 msAPI_PVRFS_GetMaxUsedBulkFileEntryIndex(void);
INTERFACE BOOLEAN msAPI_PVRFS_SetDefaultDiskDriveIndex(U8 u8DefaultDrive);
INTERFACE U8 msAPI_PVRFS_GetDefaultDiskDriveIndex(void);
INTERFACE void msAPI_PVRFS_SetCreateBulksState(EN_CREATE_BULKS_STATE enState);
INTERFACE EN_CREATE_BULKS_STATE msAPI_PVRFS_GetCreateBulksState(void);
INTERFACE U16 msAPI_PVRFS_GetCurrentCreateBulkNum(void);
INTERFACE U32 msAPI_PVRFS_GetDriveFreeSpaceMB(void);
INTERFACE BOOLEAN msAPI_PVRFS_IsBulkFileReady(U8 u8DiskDriveIndex, U16* u16BulkIndex, BOOLEAN* bFinished);
INTERFACE EN_BFK_VERSION_CHECK msAPI_PVRFS_isBulkVersionChanged(void);
INTERFACE void msAPI_PVRFS_ResetCurrentCreateBulkNum(void);
INTERFACE void msAPI_PVRFS_SetTotalDiskSizeUsedMB(U32 u32TotalDiskSizeSetToUsed);
INTERFACE BOOLEAN msAPI_PVRFS_ResetFreeCluster(void);
#endif //#if (ENABLE_BULK_FILE_SYSTEM)
#undef INTERFACE
#endif
