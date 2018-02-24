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
#ifndef _MSAPI_FCTRL_H
#define    _MSAPI_FCTRL_H

#if OBA2
#include "N51FS_Wrapper.h"
#else

#include "datatype.h"
#include "debug.h"

#include "msAPI_FSCommon.h"
#include "msAPI_FSEnv.h"




//partition table content =======================================================================//
#define PARTITION_TABLE0_BYTE_OFFSET            446//16 BYTES
#define PARTITION_TABLE1_BYTE_OFFSET            462//16 BYTES
#define PARTITION_TABLE2_BYTE_OFFSET            478//16 BYTES
#define PARTITION_TABLE3_BYTE_OFFSET            494//16 BYTES
#define PARTITION_TABLE_SIGNATURE_BYTE_OFFSET   510//2  BYTES



#define N51FS_ROOT_MFR 5
#define N51FS_BITMAP_MFR 6

/*enumeration ===================================================================================*/
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


typedef enum
{
    CREATE_MODE_NEW,
    CREATE_MODE_NEW_FORCE,
    CREATE_MODE_APPEND,
    CREATE_MODE_NEW_ATTR_HIDDEN
}EN_CREATE_MODE;

typedef enum
{
    FILE_SEEK_SET   = 0,
    FILE_SEEK_CUR   = 1
}EN_FILE_SEEK_OPTION;


typedef enum
{
    FILE_CLOSE_RESULT_ERROR,
    FILE_CLOSE_RESULT_SUCCESS,
    FILE_CLOSE_RESULT_CLOSED_ALREADY,
}EN_FILE_CLOSE_RESULT;

#if (FILE_SYSTEM_FORMAT_ENABLE)
typedef enum
{
    FORMAT_FAST,
    FORMAT_COMPLETED,
}EN_FORMAT_MODE;
#endif

typedef enum
{
    //directory entry attribute =====================================================================//
    ENTRY_ATTRIB_READ_ONLY                      =0x01,  //indicates that writes to the file should fail.
    ENTRY_ATTRIB_HIDDEN                         =0x02,  //indicates that normal directory listings should not show this file.
    ENTRY_ATTRIB_SYSTEM                         =0x04,  //indicates that this is an operating system file.
    ENTRY_ATTRIB_VOLUME_ID                      =0x08,  //there should only be one "file" on the volume that has this attribute set, and that file must be in the root directory.
    ENTRY_ATTRIB_DIRECTORY                      =0x10,  //indicates that this file is actually a container for other files.
    ENTRY_ATTRIB_ARCHIVE                        =0x20,  //this attribute supports backup utilities.
    ENTRY_ATTRIB_LONG_NAME                      =0x0F,  //= ATTRIB_READ_ONLY |
}EN_ENTRY_ATTRIB;

typedef enum
{
    FILE_SYSTEM_FORMAT_UNKNOW=0,
    FILE_SYSTEM_FORMAT_FAT12,
    FILE_SYSTEM_FORMAT_FAT16,
    FILE_SYSTEM_FORMAT_FAT32,
    FILE_SYSTEM_FORMAT_NTFS,
}EN_FILE_SYSTEM_FORMAT;

typedef U16 DirEntryTimeStruct;

#define FS_GET_SEC(x)      ((x & 0x1F) * 2 )
#define FS_GET_MIN(x)      ((x >> 5) & 0x3F)
#define FS_GET_HOUR(x)     ((x >> 11) & 0x1F)

typedef U16 DirEntryDateStruct;

#define FS_GET_DAY(x)      (x & 0x1F)
#define FS_GET_MONTH(x)    ((x >> 5) & 0x0F)
#define FS_GET_YEAR(x)     ((x >> 9) & 0x7F) + FS_DEFAULT_YEAR

#define MSDOS_MBR_SIGNATURE 0xAA55
#define EFI_PMBR_OSTYPE_EFI 0xEF
#define EFI_PMBR_OSTYPE_EFI_GPT 0xEE

#define GPT_BLOCK_SIZE 512
#define GPT_HEADER_SIGNATURE 0x5452415020494645ULL
#define GPT_HEADER_REVISION_V1 0x00010000
#define GPT_PRIMARY_PARTITION_TABLE_LBA 1ULL
#define GPT_ENTRY_NAME "gpt"

typedef unsigned short efi_char16_t;

typedef struct {
	unsigned char b[16];
} efi_guid_t;

struct partition {
	unsigned char boot_ind;		/* 0x80 - active */
	unsigned char head;		/* starting head */
	unsigned char sector;		/* starting sector */
	unsigned char cyl;		/* starting cylinder */
	unsigned char sys_ind;		/* What partition type */
	unsigned char end_head;		/* end head */
	unsigned char end_sector;	/* end sector */
	unsigned char end_cyl;		/* end cylinder */
	unsigned char start_sect[4];	/* starting sector counting from 0 */
	unsigned char nr_sects[4];	/* nr of sectors in partition */
} __attribute__ ((packed));

/* based on linux/fs/partitions/efi.h */
typedef struct _gpt_header {
	unsigned char signature[8];
	unsigned char revision[4];
	unsigned char header_size[4];
	unsigned char header_crc32[4];
	unsigned char reserved1[4];
	unsigned char my_lba[8];
	unsigned char alternate_lba[8];
	unsigned char first_usable_lba[8];
	unsigned char last_usable_lba[8];
	efi_guid_t disk_guid;
	unsigned char partition_entry_lba[8];
	unsigned char num_partition_entries[4];
	unsigned char sizeof_partition_entry[4];
	unsigned char partition_entry_array_crc32[4];
	unsigned char reserved2[GPT_BLOCK_SIZE - 92];
} __attribute__ ((packed)) gpt_header;

typedef struct _gpt_entry_attributes {
	unsigned long long required_to_function:1;
	unsigned long long reserved:47;
	unsigned long long type_guid_specific:16;
} __attribute__ ((packed)) gpt_entry_attributes;

typedef struct _gpt_entry {
	efi_guid_t partition_type_guid;
	efi_guid_t unique_partition_guid;
	unsigned char starting_lba[8];
	unsigned char ending_lba[8];
	gpt_entry_attributes attributes;
	efi_char16_t partition_name[72 / sizeof(efi_char16_t)];
}
__attribute__ ((packed)) gpt_entry;

typedef struct _legacy_mbr {
	unsigned char boot_code[440];
	unsigned char unique_mbr_signature[4];
	unsigned char unknown[2];
	struct partition partition_record[4];
	unsigned char signature[2];
} __attribute__ ((packed)) legacy_mbr;

/*function ======================================================================================*/
#ifdef MSAPI_FCTRL_C
#define INTERFACE
#else
#define    INTERFACE extern
#endif

INTERFACE U32* FCtrl_GetFileSystemInfo(U8 fsid);
INTERFACE FileHandleStruct *FCtrl_GetFileHandleInfo(U8 HandleNo);
INTERFACE FileInodeStruct *FCtrl_GetFileInodeInfo(U8 u8InodeID);
INTERFACE U32* FCtrl_GetFatTableCacheInfo(U8 fsid);
INTERFACE void FCtrl_CopyFileHandleInfo(FileHandleStruct *handle, U8 HandleNo);


INTERFACE void msAPI_FCtrl_Init(void);
INTERFACE void msAPI_FCtrl_FileHandleResetAll(void);





//directory =====================================================================================//
INTERFACE BOOLEAN msAPI_FCtrl_DirectoryChangeToRoot(U8 environmentID);
INTERFACE BOOLEAN msAPI_FCtrl_DirectoryChange(U8 environmentId,FileEntry* pFileEntry);
#if FILE_SYSTEM_ENABLE_FCTRL_DIRECTORY_CHANGE_TO_CONTAINED
INTERFACE BOOLEAN msAPI_FCtrl_DirectoryChangeToContained(U8 environmentId,FileEntry* pFileEntry);
#endif
INTERFACE BOOLEAN msAPI_FCtrl_DirectoryGetDOTDOT(U8 environmentId,FileEntry* pFileToSet);
#if FILE_SYSTEM_ENABLE_FCTRL_GET_DIRECTORY_DOT
INTERFACE BOOLEAN msAPI_FCtrl_DirectoryGetDOT(U8 environmentId,FileEntry* pFileToSet);
#endif
INTERFACE BOOLEAN msAPI_FCtrl_DirectoryIsCurrentRoot(U8 environmentId);
INTERFACE U8 msAPI_FCtrl_DirectoryOpen(FileEntry* pFileEntry, U8 u8OpenMode);

//entry=====================================================================================//
INTERFACE EN_ENTRY_NEXT_RESULT msAPI_FCtrl_EntryNext(U8 enId,FileEntry* pFileToSet);
INTERFACE BOOLEAN msAPI_FCtrl_EntryFirst(U8 enId);
INTERFACE U8 msAPI_FCtrl_EntryGetCurrentName(U8 enId,U32 MIUAddr,U8 charLen);
INTERFACE U8 msAPI_FCtrl_EntryGetLongNameByFileEntry(U8 enId, FileEntry *entry, U32 MIUAddr, U8 charLen, BOOLEAN* pbShortNameOnly);
INTERFACE U8 msAPI_FCtrl_EntryGetShortNameByFileEntry(U8 enId, FileEntry *entry, U32 MIUAddr, U8 charLen);
INTERFACE BOOLEAN msAPI_FCtrl_EntrySearchByName(U8 enId,U16* pFileName,U8 charLen,FileEntry* pFileToSet);
#if FILE_SYSTEM_SEARCH_BY_SHORT_NAME_ENABLE
INTERFACE BOOLEAN msAPI_FCtrl_EntrySearchByShortName(U8 u8EnId,U8 *pu8FileNameToFind,U8 u8FileNameToFindLen ,FileEntry *pEntryToSet);
INTERFACE BOOLEAN msAPI_FCtrl_EntrySearchByShortNameFromCurrentDirEntry(U8 u8EnId,U8 *pu8FileNameToFind,U8 u8FileNameToFindLen ,FileEntry *pEntryToSet);
INTERFACE void msAPI_FCtrl_SetCurrentDirEntryIndex(S32 s32CurrentDirEntryIndex);
INTERFACE S32  msAPI_FCtrl_GetCurrentDirEntryIndex(void);
INTERFACE void msAPI_FCtrl_ResetCurrentDirEntryIndex(void);
#endif



//file ==========================================================================================//
INTERFACE BOOLEAN msAPI_FCtrl_FileSeek(U8 u8HandleNo, U32 u32Length, EN_FILE_SEEK_OPTION option);
INTERFACE U32 msAPI_FCtrl_FileTell(U8 u8HandleNo);
INTERFACE U32 msAPI_FCtrl_FileLength(U8 u8HandleNo);
INTERFACE U8 msAPI_FCtrl_FileOpen(const FileEntry* pFileEntry, U8 u8OpenMode);
INTERFACE EN_FILE_CLOSE_RESULT msAPI_FCtrl_FileClose(U8 u8HandleNo);
INTERFACE U32 msAPI_FCtrl_FileRead(U8 u8HandleNo, U32 u32Buffer, U32 u32Length);
INTERFACE U32 msAPI_FCtrl_FileRead2(U8 u8HandleNo, U32 u32VABuffer, U32 u32Length);
INTERFACE U32 msAPI_FCtrl_FileWrite(U8 u8HandleNo, U32 u32Buffer, U32 u32Length);

INTERFACE U8 msAPI_FCtrl_FileCreate(U8 u8enid,U16 *pu16LongName,U8 charLen,EN_CREATE_MODE createMode);
INTERFACE U8 msAPI_FCtrl_FileDelete(FileEntry* pFileEntry);

INTERFACE U8 msAPI_FCtrl_FileCreate_WithoutNameChecking(U8 u8enid, U16 *pu16LongName, U8 charLen, EN_CREATE_MODE createMode);
INTERFACE BOOLEAN msAPI_FCtrl_DirectoryCreate(U8 u8enid, U16 *pu16LongName, U8 charLen);
INTERFACE BOOLEAN msAPI_FCtrl_DirectoryCreate_And_GetFileEntry(U8 u8enid, U16 *pu16LongName, U8 charLen, FileEntry *pstFileEntry);

//disk size
INTERFACE U32 msAPI_FCtrl_GetUnusedSizeInKB_ByDriveIndex(U8 u8DriveIndex);
INTERFACE U32 msAPI_FCtrl_GetUnusedSizeInKB_ByDriveIndex_New(U8 u8DriveIndex);
INTERFACE U32 msAPI_FCtrl_GetTotalSizeInKB_ByDriveIndex(U8 u8DriveIndex);

INTERFACE U32 msAPI_FCtrl_GetTotalSectors(U8 driveNo);
INTERFACE BOOLEAN msAPI_FCtrl_CreateDRECFile(U8 driveNo,U8 fileNumber,U32* startCluster,U32* physicalSector);
INTERFACE void msAPI_FCtrl_FinishDRECFile(U8 driveNo,U8 fileNumber,U32 startCluster,U32 len);


//device
#if FILE_SYSTEM_ENABLE_START_DEVICE
INTERFACE U32 msAPI_FCtrl_StartDevice(U8 deviceIndex);
#endif
INTERFACE BOOLEAN msAPI_FCtrl_ActiveDevice(U8 deviceIndex);
#ifdef ENABLE_PTP
INTERFACE BOOLEAN msAPI_FCtrl_ActivePTPDevice(U8 deviceIndex);
#endif
//drive
INTERFACE BOOLEAN msAPI_FCtrl_GetDriveByIndex(U8 driveLetter,MSDCtrl_Drive* pDrive);
INTERFACE U8 msAPI_FCtrl_GetDriveCount(void);

#if FILE_SYSTEM_ENABLE_FCTRL_GET_DRIVE_COUNT_BY_PORT
INTERFACE U8 msAPI_FCtrl_GetDriveCountByPort(U8 port);
#endif

INTERFACE void msAPI_FCtrl_UnmountDrivesOnDevice(U8 deviceIndex);

INTERFACE void msAPI_FCtrl_RemoveDrivesOnDevice(U8 deviceIndex);
INTERFACE BOOLEAN msAPI_FCtrl_IsDriveMounted(U8 u8DriveId);

#if FILE_SYSTEM_GET_VOLUME_LABEL_ENABLE
INTERFACE U8 msAPI_FCtrl_VolumeLabelGetByDriveIndex(U8 u8DriveIndex, U16 *VolLabName, U8 VolLabNameLen, BOOLEAN *pbIsUnicode);
#endif

//The highest 8 bits mean of the return means how many paritions are founded on this device.
//The remain 24 bits mean whether the parition is loaded succesfully. Start from the lowest bit.
//ex: 0x04000002 means there are 4 paritions found on this device but only the 2nd (index=1) is loaded successfully.
INTERFACE U32 msAPI_FCtrl_LoadPartitionsOnDevice(U8 deviceIndex);
#if FILE_SYSTEM_ENABLE_IS_CURRENT_NAME_SHORT_ONLY
INTERFACE BOOLEAN msAPI_FCtrl_EntryIsCurrentNameShortNameOnly(U8 enId);
#endif

#if(FILE_SYSTEM_FORMAT_ENABLE)
INTERFACE BOOLEAN msAPI_FCtrl_FormatPartitionByDriveIndex(EN_FORMAT_MODE formatMode,U8 u8DriveIndex);
INTERFACE BOOLEAN msAPI_FCtrl_FAT16_Format(U8 driveNo);
#endif

INTERFACE LongLong msAPI_FCtrl_FileLength_LongLong(U8 u8HandleNo);
INTERFACE LongLong msAPI_FCtrl_FileTell_LongLong(U8 u8HandleNo);
INTERFACE BOOLEAN msAPI_FCtrl_FileSeek_LongLong(U8 u8HandleNo, LongLong u32Length, EN_FILE_SEEK_OPTION option);
INTERFACE BOOLEAN msAPI_FCtrl_EntryGetByHandle(U8 u8HandleNo,FileEntry* pEntryToSet);
INTERFACE EN_FILE_SYSTEM_FORMAT msAPI_FCtrl_GetFileSystemFormatByDriveIndex(U8 u8DriveIndex);

#undef INTERFACE
#endif /* OBAMA */
#endif    /*_MSAPI_FCTRL_H END */

