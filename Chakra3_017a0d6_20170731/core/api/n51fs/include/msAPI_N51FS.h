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
#ifndef MSAPI_N51FS_H
#define MSAPI_N51FS_H

//Attribute length byte define in bytes
#define N51FS_STANDARD_INFORMATION_BYTES 72
#define N51FS_SYSTEM_RESERVE_FILE   24
#define INDEX_ENTRY_STACK_COUNT 2  //number of index entry
#define INDEX_ENTRY_STACK_DEEP 4

#define memoffset_N51FS_IndexVars   0x1000
#define memoffset_N51FS_INDEX_ROOT    0x2000
#define memoffset_N51FS_IndexRecord 0x3000
//#define memoffset_N51FS_CurrentFileEntry 0x4000

//#define memoffset_N51FS_IndexUpdateSequence 0x3000;

//no matter ntfs partition secor size is 512 bytes or others(such as 1024/2048/4096 bytes),
//some code should must alwanys use NTFS_BLOCK_SIZE,not sector size.
#define NTFS_BLOCK_SIZE         512

#define ReadU32(p,x)  (*((U32*)(p+x)))
#define ReadU16(p,x)  (*((U16*)(p+x)))


typedef enum
{
    INDEX_ENTRY_FLAG_BIT_NODE=0x1,
    INDEX_ENTRY_FLAG_BIT_END=0x2,
}EN_INDEX_FLAG_BIT;

typedef enum
{
    ATTR_TYPE_STANDARD_INFORMATION=0x10,
    ATTR_TYPE_ATTRIBUTE_LIST=0x20,
    ATTR_TYPE_FILE_NAME=0x30,
    ATTR_TYPE_VOLUMN_VERSION=0x40,
    ATTR_TYPE_OBJECT_ID=0x40,
    ATTR_TYPE_SECURITY_DESCRIPTOR=0x50,
    ATTR_TYPE_VOLUMN_NAME=0x60,
    ATTR_TYPE_VOLUME_INFORMATION=0x70,
    ATTR_TYPE_DATA=0x80,
    ATTR_TYPE_INDEX_ROOT=0x90,
    ATTR_TYPE_INDEX_ALLOCATION=0xA0,
    ATTR_TYPE_BITMAP=0xB0,
    ATTR_TYPE_SYMBOLIC_LINK=0xC0,
    ATTR_TYPE_REPARSE_POINT=0xC0,
    ATTR_TYPE_EA_INFORMATION=0xD0,
    ATTR_TYPE_EA=0xE0,
    ATTR_TYPE_PROPERTY_SET=0xF0,
    ATTR_TYPE_LOGGED_UTILITY_STREAM=0x100,

}EN_ATTRIBUTE_TYPE;

typedef enum
{
    FILENAMESPACE_POSIX,
    FILENAMESPACE_WIN32,
    FILENAMESPACE_DOS,
    FILENAMESPACE_WIN32DOS,
}EN_FILENAMESPACE_TYPE;


/*
typedef enum
{
    SEEK_OPTION_FROM_ZERO,
    SEEK_OPTION_FROM_CURRENT,
}EN_SEEK_OPTION;
*/
typedef struct
{
    /*first block  must be the same between all file sys struct*/
    U8 FileSystemID;//must not be moved
    U8 FileSystemType;
    U8 FileSystemSupport;
    S8 DeviceIndex;

    U8  BootIndicator;
    U8  SystemID;                //System ID. This byte defines the volume type.
    U32 RelativeSector;         //represents the offset from the beginning of the partition to the beginning of the volume.

    U32 MFTCluster;
    U32 MFTMirrorCluster;

    U16 BytesPerSector;
    U8 SectorsPerCluster;

    //U8 ClustersPerMFTRecord; <= this two member is removed due to it may be negative
    //U8 ClustersPerIndexRecord;
    U8 SectorsPerMFTRecord;
    U8 SectorsPerIndexRecord;
    U8 ClustersPerFileInputBuffer;

    U32 TotalSectors;            //Total Sectors.
    U8 BitCountPerSector;
    U16 BitCountPerCluster; //~!~

    //U32 PhysicalStartSector;    //represents the offset from the beginning of the disk to the beginning of the volume.


    /*N51FS*/
    /*
    U32 RootDirectory_MFTLCN;
    U32 CurrentFile_MFTLCN;
    U32 CurrentDirectory_MFTLCN;
    */
    /**/
}N51FS_FileSysStruct;

typedef struct
{
    U32 Type;
    U32 Size;
    BOOLEAN Residented;
    U8 NameLength;
    U16 ValueOffset;
}N51FS_AttributeInfo;

typedef struct
{
    U32 Type;
    U32 Length;
    U8  NonResidentFlag;
    U8  NameLength;
    U16 OffsetToName;
    U16 Flags;
    U16 AttrId;
    U32 LengthOfAttr;
    U16 OffsetToAttr;
    U8  IndexedFlag;
}N51FS_ResidentAttrHead;


typedef struct
{
    U32 Type;
    U32 Length;
    U8  NonResidentFlag;
    U8  NameLength;
    U16 OffsetToName;
    U16 Flags;
    U16 AttrId;
    U32 StartVCN;
    U32 StartVCN_H;
    U32 LastVCN;
    U32 LastVCN_H;
    U16 OffsetToDataRuns;
    U16 CompressUnitSize;
    U32 Padding;
    U32 AllocatedSize;
    U32 AllocatedSize_H;
    U32 RealSize;
    U32 RealSize_H;
    U32 InitialDataSize;
    U32 InitialDataSize_H;
}N51FS_NonResidentAttrHead;

typedef struct
{
    S8 DeviceIndex;
    U8 FileSystemID;
    U8  EnvironmentID;
    U32 CurrentDirectoryMFR;
    U32 ParentDirectoryMFR;
}N51FS_Environment;

typedef struct
{
    U32 u32LCN;
    U32 u32Len;
}
N51FS_MftDataRun;

#ifdef MSAPI_N51FS_C
#define INTERFACE
#else
#define    INTERFACE extern
#endif

INTERFACE N51FS_Environment* N51FS_GetEnvironmentInfo(U8 enid);


INTERFACE U32 N51FS_GetEnvironmentMIUAddressa(U8 enid);
INTERFACE U32 N51FS_GetTemp0XDataMIUAddr(void);
//INTERFACE U32 N51FS_GetCurrentFileEntryMIUAddress(U8 enid);


/*FILE system*/
INTERFACE BOOLEAN N51FS_InitialFileSystem(S8 deviceIndex,U32 partitionStartSector ,U8* partitionBytes,N51FS_FileSysStruct* pFileSysToInitial);
INTERFACE BOOLEAN N51FS_SaveEnvironment(U8 enid);

INTERFACE U32 N51FS_GetFreeSpaceInKB(U8 fsid);
INTERFACE U32 N51FS_GetTotalSizeInKB(U8 fsid);
INTERFACE U8 N51FS_FileRecordFindVolumeLabel(U8 u8DriveIndex, U16 *VolLabName, U8 VolLabNameLen);

/*N51FS common*/
INTERFACE U32 N51FS_ReadMFT_LSN(U8 fileSystemID, U32 MFR);
INTERFACE U32 N51FS_ReadMFTRecord(U8 enid,U32 recordNo,U32 destMIUAddr);
INTERFACE BOOLEAN N51FS_WriteMFTRecord(U8 fileSystemID,U32 MFR,U32 SrcMIUaddr);
INTERFACE N51FS_AttributeInfo N51FS_Attribute_Find(U8 fsid,U32 startMIUAddr,U32 destMIUAddr,EN_ATTRIBUTE_TYPE attrType, U16* pu16Offset, U32 lowestVCN);
INTERFACE void N51FS_Attribute_SwapAttrHead(void* pAttrHead);
INTERFACE U32 N51FS_Attribute_GetMIUAddr(U32 startMIUAddr, EN_ATTRIBUTE_TYPE attrType);
INTERFACE BOOLEAN N51FS_GetFileEntryByMFR(U8 u8enid, U32 u32mfr, FileEntry *pFileToSet);
INTERFACE BOOLEAN N51FS_WriteMFTRecord(U8 fileSystemID,U32 MFR,U32 SrcMIUaddr);

//file handle
INTERFACE void N51FS_HandlePostCreate(U8 fhid,U8 fileSytemID,U32 fileLengthHI,U32 fileLengthLO,U8 openMode );

//file
INTERFACE BOOLEAN N51FS_FileOpen(U8 handleId,U32 mfr);
INTERFACE BOOLEAN N51FS_FileClose(U8 handleId);
INTERFACE U32 N51FS_FileRead(U8 handleId,U32 MIUAddr,U32 len);
//NTERFACE U32 N51FS_FileSeek(U8 handleId,U32 seekLength,EN_SEEK_OPTION seekOption);
INTERFACE BOOLEAN N51FS_FileSeek(U8 handleId, U32 u32Length, EN_FILE_SEEK_OPTION seekOption);
INTERFACE LongLong N51FS_FileTell(U8 handleId);
INTERFACE LongLong N51FS_FileLength(U8 handleId);

INTERFACE BOOLEAN N51FS_FileDelete(FileEntry *pFileEntry);


//entry
INTERFACE void N51FS_EntryGetCurrentFileEntry(U8 enid, FileEntry *entry);
INTERFACE U8 N51FS_EntryGetCurrentNameToMIU(U8 enid,U32 destMIUAddr,U8 charLen);
INTERFACE U8 N51FS_EntryGetFileNameByFileEntry(U8 enid, FileEntry *entry, U32 destMIUAddr, U8 charLen, BOOLEAN *bIsLongName);
INTERFACE BOOLEAN N51FS_EntryFirst(U8 enId);

//directory
BOOLEAN N51FS_DirectoryChange(U8 enid,U32 mfr);
INTERFACE U32 N51FS_DirectoryGetCurrentMFR(U8 environmentId);
INTERFACE U32 N51FS_DirectoryGetParentMFR(U8 environmentId);


#undef INTERFACE
#endif

