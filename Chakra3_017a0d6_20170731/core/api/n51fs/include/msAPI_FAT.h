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
#ifndef MSAPI_FAT_H
#define  MSAPI_FAT_H
#include "datatype.h"

#define FAT_ENVIRONMENT_ADR         0x0000              //4
#define FAT_ENVIRONMENT_LEN         0x1000              // 4
#define FAT_DIR_ENTRY_CACHE_ADR     (FAT_ENVIRONMENT_ADR+FAT_ENVIRONMENT_LEN)
#define FAT_DIR_ENTRY_CACHE_LEN     0x1000               // 4K
#define FAT_FSINFO_SECTOR_ADR       (FAT_DIR_ENTRY_CACHE_ADR+FAT_DIR_ENTRY_CACHE_LEN)
#define FAT_FSINFO_SECTOR_LEN       0x1000     // 4K
#define FAT_CURRENT_INFO_ADR        (FAT_FSINFO_SECTOR_ADR+FAT_FSINFO_SECTOR_LEN)
#define FAT_CURRENT_INFO_LEN        0x1000

#define FAT_CURRENT_INFO_ENTRY_offset       0x0
#define FAT_CURRENT_INFO_ENTRY_NAME_offset  0x100
#define FAT_CURRENT_INFO_ENTRY_NAME_SHORT_ONLY_offset  0x300




#define FAT_SECTOR_SIZE_512BYTE             512
//#define FAT_FAT_TABLE_CACHE_SECTOR_SIZE     8        //8*512=4K

#define FAT_FSINFO_SECTOR_SIZE              1

#define FAT_DIE_ENTRY_CACHE_BYTES          0x1000



//#define FAT_DIR_ENTRY_CACHE_SECTOR_SIZE     8        // 8*512=4K
//#define FAT_SECTOR_MAX_DIR_ENTRY_NO         16
//#define FAT_DIR_ENTRY_CACHE_LAST_ENTRY      (FAT_DIR_ENTRY_CACHE_SECTOR_SIZE*FAT_SECTOR_MAX_DIR_ENTRY_NO-1)

//fat cluster status ============================================================================//
#define FAT_CLUSTER_NOT_USED                    0x000
#define FAT_CLUSTER_ALLOCATED                    0x002
#define FAT_CLUSTER_RESERVED                    0xFF6
#define FAT_CLUSTER_DEFECTIVE                    0xFF7
#define FAT_CLUSTER_FINAL                        0xFF8

#define FAT_MAX_DIRECTORY_PATH_SIZE                                         256
#define FAT_MAX_NOT_FULL_PATH_DIRECTORY_PATH_SIZE              128
#define FAT_MAX_LONG_FILE_NAME_SIZE                                         256
#define FAT_MAX_CLUSTER_NO_CACHE_SIZE                                     128

#define FAT_MAX_DIRECTORY_CLUSTER_COUNT                              32

#define FAT_PARTITION_TABLE_SECTOR_OFFSET                        0
#define FAT_BOOT_SECTOR_OFFSET                                    0

#define DIR_ENTRY_CACHE_IS_LAST             0x2
#define DIR_ENTRY_CACHE_IS_FIRST            0x3

#define CLUSTER_CHAIN_SIZE 0x200

//*DirEntry type=======================================//
#define DIR_ENTRY_IS_LAST                         0x0
#define DIR_ENTRY_NAME_ACTUALLY_E5     0x05
#define DIR_ENTRY_IS_DOT                          0x2e
#define DIR_ENTRY_IS_FREE                 0xe5

#define DIR_ENTRY_NAME_LEN                8
#define DIR_ENTRY_EXT_NAME_LEN      3

//*FAT table entry type=================================//
//#define FAT12ENTRYSIZE
#define FAT16ENTRYSIZE                    2
#define FAT32ENTRYSIZE                    4


#define FIRST_BYTE_OF_ENTRY_MAX_LONGNAME    0x54
#define FIRST_BYTE_OF_ENTRY_END_LONGNAME    0x40


typedef enum
{
    FAT_TYPE_FAT12                            =0,
    FAT_TYPE_FAT16                            =1,
    FAT_TYPE_FAT32                            =2,
    FAT_TYPE_NOT_SUPPORT                    =3,
}EN_FAT_TYPE;

typedef enum
{
    FAT_ATTRIB_READ_ONLY                        =0x01,    //indicates that writes to the file should fail.
    FAT_ATTRIB_HIDDEN                            =0x02,    //indicates that normal directory listings should not show this file.
    FAT_ATTRIB_SYSTEM                            =0x04,    //indicates that this is an operating system file.
    FAT_ATTRIB_VOLUME_ID                        =0x08,    //there should only be one "file" on the volume that has this attribute set, and that file must be in the root directory.
    FAT_ATTRIB_DIRECTORY                        =0x10,    //indicates that this file is actually a container for other files.
    FAT_ATTRIB_ARCHIVE                            =0x20,    //this attribute supports backup utilities.
    FAT_ATTRIB_LONG_NAME                        =0x0F,    //= ATTRIB_READ_ONLY |
}EN_FAT_ATTRIB;

typedef enum
{
   FAT_XDATA_OPTION_ENVIRONMENT,
   FAT_XDATA_OPTION_DIR_ENTRY_CACHE,
   FAT_XDATA_OPTION_FSINFO_SECTOR,
   FAT_XDATA_OPTION_FAT_CURRENT_INFO,
}EN_FAT_XDATA_OPTION;

/*
typedef enum
{
    GET_DIR_ENTRY_CLUSTER_NO,
    FLUSH_DIR_ENTRY_CLUSTER_NO,
}EN_FAT_STRUCTURE_OPTION;
*/
typedef enum
{
    GET_FSI_FREE_COUNT,
    GET_FSI_NXT_FREE,
}EN_FAT_FSINFO_OPTION;

#if 0
typedef enum
{
    DIR_ENTRY_CACHE_TO_FIRST,
    DIR_ENTRY_CACHE_TO_PREV,
    DIR_ENTRY_CACHE_TO_NEXT,
}EN_DIR_ENTRY_CACHE_FETCH_OPTION;
#endif

typedef enum
{
    FILE_SEEK_FORWARD_FROM_END,
    FILE_SEEK_FORWARD_FROM_CURRENT,
}EN_FAT_FILE_SEEK_FORWARD_OPTION;

typedef enum
{
    FILE_SEEK_BACKWARD_FROM_START,
    FILE_SEEK_BACKWARD_FROM_CURRENT,
}EN_FAT_FILE_SEEK_BACKWARD_OPTION;


//<<FAT STRUCTURE>>=======================================//
typedef struct
{
    EN_FAT_TYPE   u8FATType;                                //FAT Type (FAT12/FAT16/FAT32)
    U32 u32FATStartSectorNo;                    //FAT Table is located at sector#
    U32 u32FATTotalClusterNo;                    //FAT Table total cluster#
}FATStruct;

//<<DIRENTRY STRUCTURE>>===================================//
typedef struct
{
    U8 pu8DirEntryName[DIR_ENTRY_NAME_LEN];
    U8 ps8DirEntryExtName[DIR_ENTRY_EXT_NAME_LEN];
    U8 u8DirEntryAttrib;
    U8 pu8DirEntryReserved[8];
    U16 u16DirEntryStartClusterHI;
    U16 u16DirEntryTime;
    U16 u16DirEntryDate;
    U16 u16DirEntryStartClusterLO;
    U32 u32DirEntryFileLength;
}DirEntryStruct;


//<<DIRECTORY STRUCTURE>>========================================================================//
typedef struct
{
    //<========for directory===========================//
    U32 u32CurrentDirStartClusterNo;                    //Directory is located at cluster#
    U32 u32ParentDirStartClusterNo;

    //<========for DirEntryCache=======================//
    //U32 u32ClusterChain[FAT_MAX_DIRECTORY_CLUSTER_COUNT];      //store all cluster# of current directory
    //U16 u16ClusterChainIndex;                                                  //index use for u32ClusterChain[FAT_MAX_DIRECTORY_CLUSTER_COUNT]
    U32 u32CurrentCluster;
    U32 u32CurrentDirEntryCacheClusterNo;
    U16 u16DirEntryCacheOffsetSectorNo;
    S16 s16DirEntryCacheCurrentIndex;                                       //index for 1K DirEntry cache
    S32 s32CurrentDirEntryIndex;
    S32 s32LastDirEntryIndex;

}DirectoryStruct;


//<<BOOT SECTOR STRUCTURE>>======================================================================//
typedef struct
{
    //common part =======================================//
    U8  BS_jmpBoot[3];
    U8  BS_OEMName[8];
    U16 BPB_BytsPerSec;
    U8  BPB_SecPerClus;
    U16 BPB_RsvdSecCnt;
    U8  BPB_NumFATs;
    U16 BPB_RootEntCnt;
    U16 BPB_TotSec16;
    U8  BPB_Media;
    U16 BPB_FATSz16;
    U16 BPB_SecPerTrk;
    U16 BPB_NumHeads;
    U32 BPB_HiddSec;
    U32 BPB_TotSec32;

    //FAT32 only ========================================//
    U32 BPB_FATSz32;
    U16 BPB_ExtFlags;
    U16 BPB_FSVer;
    U32 BPB_RootClus;
    U16 BPB_FSInfo;
    U16 BPB_BkBootSec;

    //common part =======================================//
    U8  BS_DrvNum;
    U8  BS_Reserved1;
    U8  BS_BootSig;
    U32 BS_VolID;
    U8  BS_VolLab[11];
    U8  BS_FilSysType[8];
    U16 BS_SignWord;
}BootSectorStruct;



//<<FAT_FILESYS STRUCTURE>>=========================================//
typedef struct
{
    /*first block must be the same between all file sys struct*/
    U8 FileSystemID;//<musb not be moved!!
    U8 FileSystemType;
    U8 FileSystemSupport;
    S8 DeviceIndex;

    /*system table ================================================*/
    #if 0
    PartitionTableStruct stPartitionTable;        //Partition Table structure
    #endif
    U32 u32RelativeSector;                    //relativeSector of partition table structure
    BootSectorStruct     stBootSector;            //Boot Sector structure
    FATStruct             stFAT;                    //FAT Table structure

    /*FSInfo structure ==============================================*/
    U32 u32FSI_Free_Count;
    U32 u32FSI_Nxt_Free;

    /*root directory ==============================================*/
    U32 u32RootDirStartClusterNo;                //root directory start cluster#
    U32 u32RootDirStartSectorNo;                //root directory start sector#
    U32 u32RootDirEndSectorNo;                    //root directory end   sector#
    U32 u32RootDirTotalSectorCount;                //root directory total sector

    /*flag ========================================================*/
    BOOLEAN bInit;                                //initial flag

    //<=======fat table use==========//
    U8 u8FAT12LastEntryByte;  //used only for FAT12
    U32 u32FATTableOffsetSectorNo;
    U32 u32CurrentFreeCluster;
    BOOLEAN bIsFATCacheDirty;
    U16 u16DirEntryCacheCount;
}FAT_FileSysStruct;

//<<FAT_ENVIRONMENT STRUCTURE>>==========================================//
typedef struct
{
    //<=======common part=========//
    S8 s8DeviceIndex;
    U8 u8FileSystemID;
    U8  u8EnvironmentID;

    //<======current direcotry========//
    DirectoryStruct stCurrentDirectory;            //current directory structure

}FAT_Environment;

typedef struct
{
    U32 u32ClusterChainStart;
    U32 u32ClusterChainLength;
}File_ClusterChain;

//<<FILE HANDLE STRUCTURE>>======================================================================//
typedef struct
{
   FileHandleStruct  pub_fileheader;

    U32 u32FilePosition;

    U32 u32FileCurrentClusterNo;
    U32 u32FileCurrentSectorNo;
    U16 u16ClusterChainIndex;

    // Open Mode
    U8 u8OpenMode;
}FAT_FileHandle;

//<<FILE HANDLE STRUCTURE>>======================================================================//
typedef struct
{
    FileInodeStruct  pub_inodeheader;

    // file attributes
    U8  u8FileAttrib;
    U32 u32FileTotalSize;

    // file cluster
    U32 u32FileStartClusterNo;


    // dir cluster
    U32 u32DirStartCluster;
    U32 u32DirEntryOffset;


    // file cluster chain
    BOOLEAN bIsClusterChainActive;
}FAT_FileInode;

#ifdef MSAPI_FAT_C
#define INTERFACE
#else
#define    INTERFACE extern
#endif

INTERFACE U32* FAT_GetAddr(U8 u8EnvironmentId, EN_FAT_XDATA_OPTION option);
INTERFACE FAT_FileHandle* FAT_File_GetHandleInfo(U8 u8FileHandleID);
INTERFACE FAT_FileInode *FAT_File_GetInodeFromHandle(U8 u8FileHandleID);
INTERFACE U32 FAT_GetMIUAddress(U8 u8EnvironmentId, EN_FAT_XDATA_OPTION option);
INTERFACE File_ClusterChain* FAT_File_GetHandleClusterChainInfo(U8 u8FileInodeID);
INTERFACE DirEntryStruct* DirEntryIterator_GetInfo(void);

INTERFACE BOOLEAN FAT_InitialFileSystem(S8 deviceIndex,U32 bootStartSector ,U8* partitionBytes,FAT_FileSysStruct *pstFileSys);
INTERFACE BOOLEAN FAT_SaveEnvironment(U8 u8EnvironmentID);
INTERFACE BOOLEAN FAT_FATStructureFetch( U8 fsid, U32 u32FATOffsetSectorNo);


//*file handle========================================================================================//
INTERFACE void FAT_HandlePostCreate( U8 u8FileHandleNo, FileEntry *pFileEntry, U8 u8OpenMode );

//*directroy==========================================================================================//
INTERFACE BOOLEAN FAT_DirectoryChange(U8 u8EnvironmentId, U32 u32DirStartClusterNo);
INTERFACE U32 FAT_DirectoryGetParentClusterNo(U8 u8EnvironmentID);
INTERFACE BOOLEAN FAT_DirectroyDirEntryToFirst(U8 u8EnvironmentID);

//*file===============================================================================================//
INTERFACE BOOLEAN FAT_FileOpen(U8 u8FileHandleNo, void * pFileEntry,BOOLEAN fastOpen);
INTERFACE BOOLEAN FAT_FileClose(U8 u8FileHandleNo);
INTERFACE BOOLEAN FAT_FileDelete(FileEntry* pFileEntry);
INTERFACE U32 FAT_FileRead(U8 u8FileHandleNo, U32 u32DesBufAdr, U32 u32ReadByteLength);
INTERFACE U8 FAT_FileSeekBackward(U8 u8FileHandleNo, U32 u32Position, EN_FILE_SEEK_OPTION Option);

INTERFACE BOOLEAN FAT_FileSeek(U8 u8FileHandleNo, U32 u32Length, EN_FILE_SEEK_OPTION eOption);

//INTERFACE U8 FAT_FileSeekForward(U8 u8FileHandleNo, U32 u32Position, EN_FAT_FILE_SEEK_FORWARD_OPTION Option);   //Not check
INTERFACE void FAT_GetCurrentFileEntry(U8 enid, FileEntry *entry);
INTERFACE U8 FAT_GetNameByFileEntry(U8 enid, FileEntry *entry, U32 destMIUAddr, U8 charLen, BOOLEAN *bIsLongName);

INTERFACE U8 FAT_FileCreate(U8 u8enid,U16 *pu16LongName,U8 charLen, EN_CREATE_MODE createMode);
INTERFACE U8 FAT_FolderCreate(U8 u8enid, U16 *pu16LongName, U8 charLen);
INTERFACE U32 FAT_FileWrite(U8 u8FileHandle, U32 u32SrcBufAddr, U32 u32BufferLen);

//*disk space==========================================================//
INTERFACE U32 FAT_GetTotalSizeInKB(U8 u8fsid);
INTERFACE U32 FAT_GetUnusedSizeInKB(U8 u8fsid);
INTERFACE U32 FAT_GetUnusedSizeInKB_New(U8 u8fsid);

#if FILE_SYSTEM_FORMAT_ENABLE
INTERFACE BOOLEAN FAT_FastFormatByDriveIndex(MSDCtrl_Drive target_drive);
INTERFACE BOOLEAN FAT_FastFormatByDriveIndex_enhance(MSDCtrl_Drive target_drive);
#endif

INTERFACE BOOLEAN FAT_FAT32ClusterChainScan(U8 u8EnvironmentID, U32 u32StartClusterNo, U32 *u32LenToSet, U32 *NextClusterToSet);
INTERFACE U32 FAT_FileTell(U8 handleId);

INTERFACE U8 FAT_DirEntryFindVolumeLabel(U8 u8DriveIndex, U16 *VolLabName, U8 VolLabNameLen);

#if ENABLE_PVR
// update new cluster to FAT table
INTERFACE U32 FAT_FAT32_GetUnusedSizeInKB(U8 u8fsid);
#endif
#undef INTERFACE
#endif
