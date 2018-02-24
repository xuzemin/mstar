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

#ifndef MSAPI_BULK_FILE_SYSTEM_H
#define MSAPI_BULK_FILE_SYSTEM_H

#include "datatype.h"
#include "Board.h"
#include "msAPI_FSCommon.h"
#include "msAPI_DTVSystem.h"

#ifdef PVR_8051 //[8051]
#define BKFS_VERSION  0x00010007UL
#else //[aron or mips]
#define BKFS_VERSION  0x00020007UL //for non-8051
#endif

#define BULK_SIZE 0x4000000UL
#define EGP_FN_SIZE EVENTDB_SDRAM_LEN+EPGEXTDB_SDRAM_LEN
#define IDX_HEAD_SIZE 0x1000UL
#define IDX_BULK_START_SECTOR_TABLE_NODE_SIZE 0x1000UL
#define IDX_ALLOCATION_TABLE_NODE_SIZE 0x1000UL

#define BULK_FILE_ENTRY_SIZE 0x1000UL
#define MAX_FAT_SEG_FILENAME_LEN 128

#define BULK_START_SECTOR_TABLE_ADDR  BKFS_MEM_ADDR
#define ALLOCATION_TABLE_ADDR   (BULK_START_SECTOR_TABLE_ADDR+0x1000)
#define BULK_FILE_ENTRY_ADDR    (ALLOCATION_TABLE_ADDR+0x1000)
#define BULK_FILE_HANDLE_ADDR          (BULK_FILE_ENTRY_ADDR+0x1000)
#define IO_TEMP_ADDR          (BULK_FILE_HANDLE_ADDR+0x1000)
#ifdef S3PLUS //[S3P]
#define PVR_IO_BUFFER_LEN     0x10000
#define PVR_IO_BUFFER_ADR     (IO_TEMP_ADDR+0x1000)
#define BULK_MEM_CHECK        (PVR_IO_BUFFER_ADR+PVR_IO_BUFFER_LEN)
#else
#define BULK_MEM_CHECK        (IO_TEMP_ADDR+0x1000)
#endif

#define MAX_DISK_SIZE_PER_PARTITION 31 //31G
#define MAX_BULK_FILE_ID 1023
#define INVALID_BK_ID 0xFFFF
#define LAST_BULK_ID 0xF000

#define MAX_BULK_FILE_HANDLE_NUM 16

#define INVALID_BULK_FILE_ID 0xFFFF

#define MAX_RING_BULK_COUNT ((0xFFFFFFFF/BULK_SIZE)+1)

#define SECTOR_PER_CLUSTER 0x20 //16K

#define BYTES_PER_KBYTE  1024
#define BYTES_PER_MEGA   1048576//1024*1024
#define MEGA_PER_GIGA    1024//1G = 1024MB

typedef enum
{
    BKF_OPEN_FOR_READ,
    BKF_OPEN_FOR_WRITE,
    BKF_OPEN_FOR_RING_WRITE,
}EN_BKF_OPEN_MODE;

typedef enum
{
    BKF_SEEK_OPTION_FROM_BEGIN,
    BKF_SEEK_OPTION_FROM_CURRENT_FORWARD,
    BKF_SEEK_OPTION_FROM_CURRENT_BACKWARD,
}EN_BKF_SEEK_OPTION;

typedef enum
{
    EN_CREATE_BULKS_INIT,
    EN_CREATE_BULKS_CREATEFOLDER,
    EN_CREATE_BULKS_CREATEBULKS,
    EN_CREATE_BULKS_CREATEINDEX,
    EN_CREATE_BULKS_CREATEEPG,
    EN_CREATE_BULKS_DONE
} EN_CREATE_BULKS_STATE;

typedef enum
{
    BKF_PARA_SERVICE_TYPE,
    BKF_PARA_PROGRAM_NAME,
    BKF_PARA_CHANNEL_NAME,
    BKF_PARA_PROGRAM_DESC,
    BKF_PARA_STARTDT,
    BKF_PARA_DURATION,
    BKF_PARA_TELL_FILELENGTH
 }BFK_PROG_INFO;

typedef enum
{
     BKF_PARA_SUCCESS,
     BKF_PARA_ERROR_NOFILE,
     BKF_PARA_LEAK_OF_RET_BUFF,
     BKF_PARA_INVALID_PARAM,
     BKF_PARA_ERROR_STORAGE,
     BKF_PARA_ERROR_BAD_SECTOR_DATA
}BFK_PARA_OPT_RES;

#if 0
typedef enum
{
     BKF_FLASHCOPY_DRAM2FLASH,
     BKF_FLASHCOPY_FLASH2DRAM
}EN_BFK_FLASHCOPY;
#endif

typedef enum
{
    BKF_VERCHK_OK,
    BKF_VERCHK_DIFFERENT_VERSION,
    BKF_VERCHK_ERROR_GET_VERSION,
}EN_BFK_VERSION_CHECK;

#ifdef MSAPI_BULK_FILE_SYSTEM_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

#define U32VA  U32  //U32 of vitual address
#define U32PA  U32  //U32 of physical address

#define BKFS_MEM_ADDR  ((BULK_FILE_SYSTEM_MEMORY_TYPE&MIU1)?BULK_FILE_SYSTEM_ADR|MIU_INTERVAL:BULK_FILE_SYSTEM_ADR)
#define BKFS_MEM_LEN   BULK_FILE_SYSTEM_LEN

INTERFACE BOOLEAN msAPI_BKFS_FileExist(U16* pu16FileName);
INTERFACE U8 msAPI_BKFS_FileOpen(U16* pu16FileName,EN_BKF_OPEN_MODE mode);
INTERFACE U8 msAPI_BKFS_FileCreate(U16* pu16FileName);

//The last parameter is used to specify the bulk count that would be occupied by this ring file.
//Under current 51MB bulk, the maximum count should be 8.
//The bulk count can only be 1, 2, 4, 8 and if there is only fewer empty bulk available, the fewer value would be returned.
#if 0
INTERFACE U8 msAPI_BKFS_RingFileCreate(U16* pu16FileName,EN_BKF_OPEN_MODE mode,U8* pu8BulkCount);
#endif
INTERFACE BOOLEAN msAPI_BKFS_FileDelete(U16* pu16FileName);

INTERFACE U32 msAPI_BKFS_FileRead(U8 handleID,U32VA MIUAddr,U32 readLength);
INTERFACE U32 msAPI_BKFS_FileWrite(U8 handleID,U32VA MIUAddr,U32 writeLength);
INTERFACE BOOLEAN msAPI_BKFS_FileSeek(U8 handleID,LongLong seekLength,EN_BKF_SEEK_OPTION option);

INTERFACE LongLong msAPI_BKFS_FileLength(U8 handleID);
INTERFACE LongLong msAPI_BKFS_FileTell(U8 handleID);
INTERFACE BOOLEAN msAPI_BKFS_FileClose(U8 handleID);

INTERFACE BOOLEAN msAPI_BKFS_SetMemory(U32 poolAddress,U32 len);
INTERFACE BOOLEAN msAPI_BKFS_SetDiskDriveIndex(U8 driveIndex);
INTERFACE BOOLEAN msAPI_BKFS_SetDeviceIndex(U8 deviceIndex);

INTERFACE BOOLEAN msAPI_BKFS_IsInitialized(void);
INTERFACE BOOLEAN msAPI_BKFS_Initial(BOOLEAN force);
INTERFACE U8 msAPI_BKFS_GetDriveIndex(void);
INTERFACE U8 msAPI_BKFS_GetDeviceIndex(void);

INTERFACE BOOLEAN msAPI_BKFS_Format(U32 u32MBRLogicBlockAddress, U8 u8IndexInMBR, U32* u32WriteCount, BOOLEAN* bFinished);
INTERFACE BOOLEAN msAPI_BKFS_IsFormated(U8 u8DiskDriveIndex);
INTERFACE BOOLEAN msAPI_BKFS_IsBulkFileReady(U8 u8DiskDriveIndex, U16* u16BulkIndex, BOOLEAN* bFinished);
INTERFACE BOOLEAN msAPI_BKFS_IsPartitionReady(U8 _diskDriveIndex,U8 _deviceIndex);

INTERFACE U16 msAPI_BKFS_GetBulksNumToCreate(void);
INTERFACE void msAPI_BKFS_ResetCurrentCreateBulkNum(void);
INTERFACE U16 msAPI_BKFS_GetCurrentCreateBulkNum(void);
INTERFACE BOOLEAN msAPI_BKFS_CreateBulks(EN_CREATE_BULKS_STATE enCreateBulksState, U8 u8EnvironmentID, U16* u16BulkNum);
INTERFACE void msAPI_BKFS_SetCreateBulksState(EN_CREATE_BULKS_STATE enState);
INTERFACE EN_CREATE_BULKS_STATE msAPI_BKFS_GetCreateBulksState(void);
INTERFACE void msAPI_BKFS_SetTotalDiskSizeUsedMB(U32 u32TotalDiskSizeSetToUsed);
INTERFACE U32 msAPI_BKFS_GetTotalDiskSizeSetToUsedMB(void);
INTERFACE U16 msAPI_BKFS_GetFreeBulkCnt(void);
INTERFACE U16 msAPI_BKFS_GetTotalBulkCnt(void);
INTERFACE BOOLEAN msAPI_BKFS_ResetFreeCluster(void);
//INTERFACE U16 msAPI_BKFS_SpeedCheck(void);
INTERFACE BOOLEAN msAPI_BKFS_SetBulkSpeed(U16 u16Speed);
INTERFACE U16 msAPI_BKFS_GetBulkSpeed(void);
INTERFACE BOOLEAN msAPI_BKFS_SetBulkRWKByteOfSpeed(U16 u16RWKByteOfSpeed);
INTERFACE U16 msAPI_BKFS_GetBulkRWKByteOfSpeed(void);
INTERFACE BOOLEAN msAPI_BKFS_SetTimeShiftReservedBulkCnt(U16 u16BulkCnt);
INTERFACE U16 msAPI_BKFS_GetTimeShiftReservedBulkCnt(void);
INTERFACE BOOLEAN msAPI_BKFS_SetTimeShiftRecordLengthMB(U32 u32TimeShiftRecordLengthMB);
INTERFACE U32 msAPI_BKFS_GetTimeShiftRecordLengthMB(void);
INTERFACE U32 msAPI_BKFS_GetDriveFreeSpaceMB(void);
INTERFACE BOOLEAN msAPI_BKFS_SetMaxUsedBulkFileEntryIndex(U16 u16MaxUsedBulkFileEntryIndex);
INTERFACE U16 msAPI_BKFS_GetMaxUsedBulkFileEntryIndex(void);
INTERFACE BOOLEAN msAPI_BKFS_SetDefaultDiskDriveIndex(U8 u8DefaultDrive);
INTERFACE U8 msAPI_BKFS_GetDefaultDiskDriveIndex(void);
INTERFACE U32 msAPI_BKFS_GetBulkVersionNo(void);

INTERFACE BFK_PARA_OPT_RES msAPI_BKFS_SetBulkFileInfo(U16* pu16BulkFileName, U16* u16BulkFileID,
                                                                      BFK_PROG_INFO info, void *pBuffer, U16 bufLen);
INTERFACE BFK_PARA_OPT_RES msAPI_BKFS_GetBulkFileInfo(U16* pu16BulkFileName, U16* u16BulkFileID,
                                                                     BFK_PROG_INFO info, void *pBuffer, U16 *pBufLen);
INTERFACE BOOLEAN msAPI_BKFS_Show_Hide_File(U8 u8Handle, BOOLEAN bShow);

/*here for bulk browser*/
//[Program Information
#define PVR_MAX_CHANNEL_NAME_LEN    (MAX_SERVICE_NAME +5+1+1) ///LCN 5 digit+1 extra space char+1 tailing zero char
#define PVR_MAX_PROGRAM_NAME_LEN    (256)   //(MAX_SHORT_EVENT_DESCRIPTOR_LEN+1) ///including 1 tailing zero char
#define PVR_MAX_PROGRAM_DESC_LEN    (256)   ///including 1 tailing zero char, we only store 255 char of program desc
//]

#define BKFS_MAGIC 0x56a3de37
#define MAKE_BKFS_POSITION(maxIndex, curIndex)   \
   ((((U32)maxIndex)<<16 |curIndex)^BKFS_MAGIC)
#define BKFS_GET_POS_INDEX(pos) ((U16)((pos)^BKFS_MAGIC))
#define BKFS_GET_POS_MAX_INDEX(pos) ((U16)(((pos)^BKFS_MAGIC)>>16))

typedef U32 BKFS_POSITION;

INTERFACE BKFS_POSITION msAPI_BKFS_FindFirstPOS(void);
INTERFACE BKFS_POSITION msAPI_BKFS_FindNextBulkFile(BKFS_POSITION pos, U16 *pCurBulkFileName,  U16 *pBufU16Len);
#if 0
INTERFACE BOOLEAN msAPI_BKFS_FlashCopy( EN_BFK_FLASHCOPY enCopyType,
                                        U32 u32Adr,
                                        U32 u32Len,
                                        U16 *pu16Filename,
                                        U8 u8FilenameLen);
INTERFACE U16* msAPI_BKFS_GetEPGFileName(void);
INTERFACE U8 msAPI_BKFS_GetEPGFileLength(void);
#endif


INTERFACE EN_BFK_VERSION_CHECK msAPI_BKFS_isBulkVersionChanged(void);

#undef INTERFACE
#endif
