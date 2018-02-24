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

#define  MSAPI_FAT_C

#include "datatype.h"
#include "debug.h"



#include "FSUtil.h"
#include "msAPI_FSCommon.h"
#include "msAPI_FCtrl.h"
#include "msAPI_FAT.h"
#include "msAPI_FSEnv.h"
#include "msAPI_MSDCtrl.h"
#include "FAT_Cache.h"
#include "SysInit.h"

#define COMPUTE_REAL_FREE_CLUSTER_COUNT 1
#if COMPUTE_REAL_FREE_CLUSTER_COUNT
#define ENABLE_CALC_FREE_CLUSTER_THRESHOLD 0x800000
#endif
#define MEM_OFFSET_CLUSTER_CHAIN    0x400//0x1000

#define FATDBG(x) //x
#define NAME_SIZE 255
#define ioassert(x)  if(!(x)){__ASSERT(0);return FALSE;}

#if(FILE_SYSTEM_SMALL == 1)
    #if(FILE_SYSTEM_WRITE_ENABLE == 1)
    #error "FILE_SYSTEM_WRITE_ENABLE should be disable if FILE_SYSTEM_SMALL is enable"
    #endif
#endif


#if 0
#define FAT_ASSERT(expr)  do { \
    if( !(expr) )        \
    { \
        PRINT_CURRENT_LINE();\
        printf("FAT_ASSERT!\n");\
    } \
} while(0)
#else
    #define FAT_ASSERT(expr)
#endif



//extern functions to keep API clean
extern void msAPI_FCtrl_FileHandleFree(U8 u8FileHandleNo);
extern BOOLEAN FAT_DirEntryUpdate(U8 u8Filehandle);
extern void FAT_EntrySetCurrentNameShortOnly(U8 enid,BOOLEAN val);

//*common API========================================================//
//static U32 FAT_File_GetHandleXDataMIUAddress(U8 u8FileHandleID);
static EN_FAT_TYPE FAT_FATGetType( U8 *pu8FileType );
static U32 FAT_FATGetMaxClusterNo( U32 u32FATSize, EN_FAT_TYPE FATType );
U32 FAT_FATGetSectorNo( U8 u8fsid, U32 u32ClusterNo );


//*initial FAT file system================================================================//
static BOOLEAN FAT_PartitionTableRead( FAT_FileSysStruct *pstFileSys, U32 bootStartSector,U8 *u8partitionBytes );
static BOOLEAN FAT_BootSectorRead( FAT_FileSysStruct *pstFileSys );
static BOOLEAN FAT_FATStructureReadRoot( FAT_FileSysStruct *pstFAT_FileSys, U32 logicalBlockAddress);
static BOOLEAN FAT_RootDirectroyInfo( FAT_FileSysStruct *pstFileSys );


//*FAT table=========================================================================//
BOOLEAN FAT_FATStructureFetch( U8 u8Fsid, U32 u32FATOffsetSectorNo);
static U32  FAT_FATStructureRead( U8 u8fsid, U32 u32DirEntryClusterNo);
static BOOLEAN FAT_FATStructureWrite( U8 u8fsid );

#if (!FILE_SYSTEM_SMALL)
static BOOLEAN FAT_FATStructureFreeClusterNo( FileEntry *pTempFileEntry);
static BOOLEAN FAT_SetClusterNo(U8 u8fsid , U32 u32ClusterNo, U32 u32ValueToSet);
static BOOLEAN FAT_ComputedFreeClusterTotalCnt(FAT_FileSysStruct *pFAT_FileSys, U32 *pu32FreeClusterCnt);
#endif

//*FSInfo Sector=======================================================================//
//static BOOLEAN FAT_FATFsinfoFetch( U8 u8EnvironmentID);
#if 0
static U32 FAT_FATFsinfoRead(U8 u8EnvironmentID, EN_FAT_FSINFO_OPTION Option);
#endif
//static BOOLEAN FAT_FATFsinfoUpdate(FileEntry *pTempFileEntry, U32 u32deletedClusterCount);

static BOOLEAN FAT_FATFsinfoFetch(FAT_FileSysStruct *pstFileSys);
#if (!FILE_SYSTEM_SMALL)
  #if FILE_SYSTEM_WRITE_ENABLE
     static BOOLEAN FAT_FATFsinfoUpdate(U8 fsid);
  #endif
    static BOOLEAN FAT_FATFsinfoUpdate_Increase(FileEntry *pTempFileEntry, U32 u32deletedClusterCount);
#endif
//*directory=========================================================================//
//static void FAT_DirectoryEntryGetName( DirEntryStruct *pstTempDirEntry, U16 *pu16FileName );
//static void FAT_DirectoryEntryGetLongName( DirEntryStruct *pstTempDirEntry, U16 *pu16LongFileName );
static void FAT_DirectoryEntrySave(U8 fsid, U8 u8EnvironmentID, DirEntryStruct * pstTempDirEntry, FileEntry * pFileToSet,U32 currentClusterNo,U32 currentDirEntryOffset );
//static BOOLEAN FAT_DirectoryClusterChainFetch(U8 u8EnvironmentId);
//static BOOLEAN FAT_DirectoryEntryWrite(U8 u8EnvironmentID);
#if (!FILE_SYSTEM_SMALL)
static BOOLEAN FAT_DirectoryFreeDirEntry(FileEntry *pDeleteFileEntry);
#endif
//*file=======================================================================//
static BOOLEAN FAT_FileClusterChainFetch(U8 u8FileHandleID);

//static U32 FAT_FileGetPrevCluster(U8 u8FileHandleID);       //Not check
//static U32 FAT_FileGetLastCluster(U8 u8FileHandleID);       //Not check


//[Rewrote]==================================================================================
#define LONG_NAME_BYTE_POS_IN_DIRENTRY_NUM 13
static U8 code LONG_NAME_BYTE_POS_IN_DIRENTRY[LONG_NAME_BYTE_POS_IN_DIRENTRY_NUM]={1,3,5,7,9,14,16,18,20,22,24,28,30};

/* customized strncmp for reserving code memory */
#if 0
static char __strncmp (
  char *string1,   /* first string */
  char *string2,   /* second string */
  int len)        /* max characters to compare */
{
    if (!string1 || !string2) return string1 - string2;    // null pointer Ã³¸®
    if (len <= 0) return 0;
    while (*string1 && *string2 && --len > 0)
    {
        if (*string1 != *string2) break;
        string1++;
        string2++;
    }
    return *string1 - *string2;
}
#endif

//Eric added for Aeon FS
U32* FAT_GetAddr(U8 u8EnvironmentId, EN_FAT_XDATA_OPTION option)
{
    if(u8EnvironmentId<FS_ENVIRONMENT_NUM) //WBT Comparing unsigned greater than or equal zero is always true. "u8EnvironmentId >= 0"
    {
        return (U32 xdata*)msAPI_FS_GetAddr(XDataAddr[u8EnvironmentId][option]);
    }
    else
    {
        __ASSERT(0);
        MDrv_Sys_StopCpu(1);
        return NULL;
    }
}

FAT_FileHandle* FAT_File_GetHandleInfo(U8 u8FileHandleID)
{
    return (FAT_FileHandle xdata*)msAPI_FS_GetAddr(FILE_HANDLE_POOL + FILE_HANDLE_MEMORY_SIZE * u8FileHandleID);
}

FAT_FileInode *FAT_File_GetInodeFromHandle(U8 u8FileHandleID)
{
    FAT_FileHandle * pstFAT_FileHandle;
    U8   u8InodeID;

    pstFAT_FileHandle = FAT_File_GetHandleInfo(u8FileHandleID);
    u8InodeID = pstFAT_FileHandle->pub_fileheader.InodeID;
    if(u8InodeID ==INVALID_FILE_INODEID)
    {
         __ASSERT(0);
         return NULL;
    }
    return  (FAT_FileInode*)FCtrl_GetFileInodeInfo(u8InodeID);
}


U32 FAT_GetMIUAddress(U8 u8EnvironmentId, EN_FAT_XDATA_OPTION option)
{
    if( u8EnvironmentId<FS_ENVIRONMENT_NUM) //WBT Comparing unsigned greater than or equal zero is always true. "u8EnvironmentId >= 0"
        return XDataAddr[u8EnvironmentId][option];
     else
    {
        __ASSERT(0);
        MDrv_Sys_StopCpu(1);
        return 0;
    }
}

DirEntryStruct* DirEntryIterator_GetInfo(void)
{
    DirEntryStruct* pDirEntry;
    pDirEntry = (DirEntryStruct xdata*)msAPI_FS_GetAddr(itrBufferAddress);

    pDirEntry+=itrCurrentCacheDirEntryIndex;

    return pDirEntry;
}

File_ClusterChain* FAT_File_GetHandleClusterChainInfo(U8 u8FileInodeID)
{
    return (File_ClusterChain xdata*)msAPI_FS_GetAddr((FILE_INODE_POOL + FILE_INODE_MEMORY_SIZE * u8FileInodeID)+(U32)MEM_OFFSET_CLUSTER_CHAIN);
}

static U32 FAT_FATGetMaxClusterNo( U32 u32FATSize, EN_FAT_TYPE FATType )
{
    U32 u32MaxClusterNo;

    switch(FATType)
    {
        case FAT_TYPE_FAT12:
            u32MaxClusterNo = u32FATSize * 2 / 3;
            if(u32MaxClusterNo > 0xFF7)
                u32MaxClusterNo = 0xFF7;
            break;
        case FAT_TYPE_FAT16:
            u32MaxClusterNo = u32FATSize / 2;
            if(u32MaxClusterNo > 0xFFF7)
                u32MaxClusterNo = 0xFFF7;
            break;
        case FAT_TYPE_FAT32:
            u32MaxClusterNo = u32FATSize  / 4;
            if(u32MaxClusterNo > 0xFFFFFF7)
                u32MaxClusterNo = 0xFFFFFF7;
            break;
        default:
            u32MaxClusterNo = 0;
            break;
    }
    return u32MaxClusterNo;
}

U32 FAT_FATGetClusterStatus( U8 u8FatType, U32 u32FatTotalClusterNo, U32 u32ClusterNo )
{
    switch ( u8FatType )
    {
        case FAT_TYPE_FAT12:
            {
                if ( u32ClusterNo == 0x000 )
                {
                    return FAT_CLUSTER_NOT_USED;
                }
                else if ( ( u32ClusterNo >= 0x002 ) && ( u32ClusterNo <= u32FatTotalClusterNo ) )
                {
                    return FAT_CLUSTER_ALLOCATED;
                }
                else if ( u32ClusterNo == 0xff7 )
                {
                    return FAT_CLUSTER_DEFECTIVE;
                }
                else if ( u32ClusterNo >= 0xff8  )              //8 cluster
                {
                    return FAT_CLUSTER_FINAL;
                }
                break;
            }
        case FAT_TYPE_FAT16:
            {
                if ( u32ClusterNo == 0x0000 )
                {
                    return FAT_CLUSTER_NOT_USED;
                }
                else if ( ( u32ClusterNo >= 0x0002 ) && ( u32ClusterNo <= u32FatTotalClusterNo ) )
                {
                    return FAT_CLUSTER_ALLOCATED;
                }
                else if ( u32ClusterNo == 0xfff7 )
                {
                    return FAT_CLUSTER_DEFECTIVE;
                }
                else if ( u32ClusterNo >= 0xfff8 )            //8 cluster
                {
                    return FAT_CLUSTER_FINAL;
                }
                break;
            }
        case FAT_TYPE_FAT32:
            {
                if ( u32ClusterNo == 0x00000000 )
                {
                    return FAT_CLUSTER_NOT_USED;
                }
                else if ( ( u32ClusterNo >= 0x00000002 ) && ( u32ClusterNo <= u32FatTotalClusterNo ) )
                {
                    return FAT_CLUSTER_ALLOCATED;
                }
                else if ( u32ClusterNo == 0xfffffff7 )
                {
                    return FAT_CLUSTER_DEFECTIVE;
                }
                else if (  u32ClusterNo >= 0x0ffffff8 )    //8 cluster
                {
                    return FAT_CLUSTER_FINAL;
                }
                break;
            }
        default:
            break;
    }

    return FAT_CLUSTER_RESERVED;
}


static EN_FAT_TYPE FAT_FATGetType( U8 *pu8FileType )
{
    if ( !strncmp( ( const char* )pu8FileType, "FAT12", 5 ) )
        return FAT_TYPE_FAT12;

    if ( !strncmp( ( const char* )pu8FileType, "FAT16", 5 ) )
        return FAT_TYPE_FAT16;

    if ( !strncmp( ( const char* )pu8FileType, "FAT32", 5 ) )
        return FAT_TYPE_FAT32;

    return FAT_TYPE_NOT_SUPPORT;
}

BOOLEAN FAT_FATStructureFetch( U8 fsid, U32 u32FATOffsetSectorNo)
{
    FAT_FileSysStruct *pFAT_FileSys;
    U8 u8DeviceIndex;
    U32 u32FATStartSectorNo;
    U16 u16BytePerSec;
    U8 u8SectorSize;
    U8 u8FatType;
    U8 u8Fat12LastByte = 0;
    pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemInfo(fsid);

    u8DeviceIndex = (U8)pFAT_FileSys->DeviceIndex;
    u32FATStartSectorNo = pFAT_FileSys->stFAT.u32FATStartSectorNo;
    u16BytePerSec=pFAT_FileSys->stBootSector.BPB_BytsPerSec;
    u8FatType=pFAT_FileSys->stFAT.u8FATType;

    u8SectorSize = (U8)(FAT_TABLE_CACHE_LEN / u16BytePerSec);
    //printf("fsid: %bu\n", fsid);
    //printf("secterno: %lu\n", u32FATStartSectorNo + u32FATOffsetSectorNo);
    //printf("secter size: %bu\n", u8SectorSize);
    if ( !msAPI_MSDCtrl_SectorRead(u8DeviceIndex, u32FATStartSectorNo + u32FATOffsetSectorNo, (U32)u8SectorSize, (FILE_FAT_TABLE_CACHE + (U32)fsid * FAT_TABLE_CACHE_LEN) ) )
    {
        __ASSERT(0);
        return FALSE;
    }
    pFAT_FileSys->u32FATTableOffsetSectorNo = u32FATOffsetSectorNo;
    if(u8FatType == FAT_TYPE_FAT12)
    {
        if ( !msAPI_MSDCtrl_SectorRead(u8DeviceIndex, u32FATStartSectorNo + u32FATOffsetSectorNo + u8SectorSize, 1, USB_IO_TEMP_ADDR ) )
        {
            __ASSERT(0);
            return FALSE;
        }
        msAPI_FS_MIU_Copy(USB_IO_TEMP_ADDR, GET_DRAM_ADDR(&u8Fat12LastByte), 1);
        pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemInfo(fsid);

        pFAT_FileSys->u8FAT12LastEntryByte = u8Fat12LastByte;
    }
    return TRUE;
}

static BOOLEAN FAT_FATStructureReadRoot( FAT_FileSysStruct *pstFAT_FileSys , U32 logicalBlockAddress)
{
        U32  u32FATSize, u32BPB_FATSz16;

    /*[01]check FAT type ==============================================================*/
    pstFAT_FileSys->stFAT.u8FATType = FAT_FATGetType(pstFAT_FileSys->stBootSector.BS_FilSysType);
    if(pstFAT_FileSys->stFAT.u8FATType == FAT_TYPE_NOT_SUPPORT)
    {
        return FALSE;
    }

    /*[02]read FAT start sector#==========================================================*/
    pstFAT_FileSys->stFAT.u32FATStartSectorNo    =  pstFAT_FileSys->u32RelativeSector + pstFAT_FileSys->stBootSector.BPB_RsvdSecCnt;    //(2)

    /*[04]calculate max cluster number ================================================*/                                                //(4)
    if(pstFAT_FileSys->stFAT.u8FATType == FAT_TYPE_FAT32)    //<<======for FAT32
    {
    #if 1
        U32 u32RootLogicalSectorNo;
        u32RootLogicalSectorNo = pstFAT_FileSys->stFAT.u32FATStartSectorNo + (pstFAT_FileSys->stBootSector.BPB_NumFATs * pstFAT_FileSys->stBootSector.BPB_FATSz32) - logicalBlockAddress;
        pstFAT_FileSys->stFAT.u32FATTotalClusterNo = (pstFAT_FileSys->stBootSector.BPB_TotSec32-u32RootLogicalSectorNo)/pstFAT_FileSys->stBootSector.BPB_SecPerClus;
        if(pstFAT_FileSys->stFAT.u32FATTotalClusterNo > 0xFFFFFF7)
        {
            pstFAT_FileSys->stFAT.u32FATTotalClusterNo = 0xFFFFFF7;
        }
    #else
        pstFAT_FileSys->stFAT.u32FATTotalClusterNo = FAT_FATGetMaxClusterNo(pstFAT_FileSys->stBootSector.BPB_FATSz32 * pstFAT_FileSys->stBootSector.BPB_BytsPerSec, (EN_FAT_TYPE)pstFAT_FileSys->stFAT.u8FATType);
    #endif
    }
    else        //<<=====for FAT12/16
    {
        u32BPB_FATSz16 = pstFAT_FileSys->stBootSector.BPB_FATSz16;
        u32FATSize = u32BPB_FATSz16 * pstFAT_FileSys->stBootSector.BPB_BytsPerSec;
        pstFAT_FileSys->stFAT.u32FATTotalClusterNo = FAT_FATGetMaxClusterNo(u32FATSize, (EN_FAT_TYPE)pstFAT_FileSys->stFAT.u8FATType);
    }

    return TRUE;
}


static U32  FAT_FATStructureRead(U8 u8fsid, U32 u32DirEntryClusterNo)
{
   U32 u32TempFatTableOffsetSectorNo, u32FatTableEntryOffset;
   U32 u32ReturnClusterNo;
   U8 *pu8FatTable;
   U16 u16BytePerSec;
   U8 u8SectorSize;
   U8 u8FatType;
   FAT_FileSysStruct *pFATFileSys;
   U32 u32Low;
   U32 u32High;
   U16 u16TempEntry,u16Temp;

   pFATFileSys = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);

   u16BytePerSec=pFATFileSys->stBootSector.BPB_BytsPerSec;
   u32TempFatTableOffsetSectorNo  = pFATFileSys->u32FATTableOffsetSectorNo;
   u8FatType = pFATFileSys->stFAT.u8FATType;

   u8SectorSize = (U8)(FAT_TABLE_CACHE_LEN / u16BytePerSec);

    if(u8FatType == FAT_TYPE_FAT32)
    {
        u32FatTableEntryOffset = u32DirEntryClusterNo * FAT32ENTRYSIZE;
    }
    else if(u8FatType == FAT_TYPE_FAT16)
    {
        u32FatTableEntryOffset = u32DirEntryClusterNo * FAT16ENTRYSIZE;
    }
    else
    {
        u32FatTableEntryOffset = u32DirEntryClusterNo * 3lu /2lu;
    }

    u32Low = u32TempFatTableOffsetSectorNo * u16BytePerSec;
    u32High = (u32TempFatTableOffsetSectorNo + u8SectorSize) * u16BytePerSec;
    //*FAT table entry offset miss in FAT table*=================================================//
    if ( u32FatTableEntryOffset < u32Low ||
        u32FatTableEntryOffset >= u32High )
    {
        BOOLEAN bIsDirty;
        pFATFileSys = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);

        u32TempFatTableOffsetSectorNo = u32FatTableEntryOffset / u16BytePerSec;
        bIsDirty = pFATFileSys->bIsFATCacheDirty;

        if (bIsDirty)                    //<<===flush FAT table entry cross cache
        {
            FAT_FATStructureWrite(u8fsid);                          //Entry Cluster# of deleted file cross FAT table cache
        }

        //pFATFileSys = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);

        if ( !FAT_FATStructureFetch(u8fsid, u32TempFatTableOffsetSectorNo) )
        {
             __ASSERT(0);
             return 0;
        }
        u32Low = u32TempFatTableOffsetSectorNo * u16BytePerSec;
        u32High = (u32TempFatTableOffsetSectorNo + u8SectorSize) * u16BytePerSec;
    }

    //*FAT table entry offset fit in FAT table*==================================================//
    pu8FatTable = (U8*)FCtrl_GetFatTableCacheInfo(u8fsid);

    if(pu8FatTable == NULL)
    {
        __ASSERT(0);
        return 0;
    }

    if ( u8FatType == FAT_TYPE_FAT16)
    {
        //u32ReturnClusterNo = (U32)((*(U16*)(pu8FatTable + (u32FatTableEntryOffset - u32Low))));
        memcpy(&u16Temp,(pu8FatTable + (u32FatTableEntryOffset - u32Low)),2);
        u32ReturnClusterNo = (U32)u16Temp;
    }
    else if ( u8FatType == FAT_TYPE_FAT32 )
    {
         //u32ReturnClusterNo = (*(U32*)(pu8FatTable + (u32FatTableEntryOffset - u32Low)));
         memcpy(&u32ReturnClusterNo,(pu8FatTable + (u32FatTableEntryOffset - u32Low)),4);
    }
    else
    {
        if(u32FatTableEntryOffset == u32High - 1)
        {
            pFATFileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemInfo(u8fsid);

            u16TempEntry = (U16)(pFATFileSys->u8FAT12LastEntryByte) << 8;
            u16TempEntry |= *(pu8FatTable + (u32FatTableEntryOffset - u32Low));
        }
        else
        {
            //u16TempEntry = (*(U16*)(pu8FatTable + (u32FatTableEntryOffset - u32Low)));
            memcpy(&u16TempEntry,(pu8FatTable + (u32FatTableEntryOffset - u32Low)),2);
        }

        if((u32DirEntryClusterNo & 1) == 0)
        {
            u32ReturnClusterNo = (U32)(u16TempEntry & 0x0FFF);
        }
        else
        {
            u32ReturnClusterNo = (U32)(u16TempEntry >> 4);
        }
    }
    return u32ReturnClusterNo;
}

static BOOLEAN FAT_FATStructureWrite( U8 fsid )
{
    FAT_FileSysStruct *pFsStruct;
    U32 u32TempFatTableOffsetSectorNo;
    U16 u16BytePerSec;
    U16 u16SectorSize;
    S8  s8DeviceIndex;
    U32 u32FATStartSectorNo;
    U8 u8FatType;
    U32 u32TotalSecterNo;
    U8 u8Fat12LastByte;

    pFsStruct=(FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(fsid);

    u32TempFatTableOffsetSectorNo  = pFsStruct->u32FATTableOffsetSectorNo;
    pFsStruct->bIsFATCacheDirty = FALSE;
    u16BytePerSec = pFsStruct->stBootSector.BPB_BytsPerSec;
    s8DeviceIndex = pFsStruct->DeviceIndex;
    u8FatType = pFsStruct->stFAT.u8FATType;
    u32FATStartSectorNo = pFsStruct->stFAT.u32FATStartSectorNo;
    u8Fat12LastByte = pFsStruct->u8FAT12LastEntryByte;
    if(u8FatType == FAT_TYPE_FAT32)
    {
        u32TotalSecterNo = pFsStruct->stBootSector.BPB_FATSz32;
    }
    else
    {
        u32TotalSecterNo = (U32)pFsStruct->stBootSector.BPB_FATSz16;
    }

    u16SectorSize = (U16)FAT_TABLE_CACHE_LEN / u16BytePerSec;

    if(u32TotalSecterNo - u32TempFatTableOffsetSectorNo < u16SectorSize)
    {
        u16SectorSize = u32TotalSecterNo - u32TempFatTableOffsetSectorNo;
    }

    if ( !msAPI_MSDCtrl_SectorWrite( s8DeviceIndex, u32FATStartSectorNo + u32TempFatTableOffsetSectorNo, (U32)u16SectorSize,  FILE_FAT_TABLE_CACHE + fsid * FAT_TABLE_CACHE_LEN ) )
    {
        __ASSERT(0);
        return FALSE;
    }

    if(u8FatType == FAT_TYPE_FAT12 && u32TempFatTableOffsetSectorNo + u16SectorSize < u32TotalSecterNo)
    {
        if ( !msAPI_MSDCtrl_SectorRead( s8DeviceIndex, u32FATStartSectorNo + u32TempFatTableOffsetSectorNo + u16SectorSize, 1, USB_IO_TEMP_ADDR  ) )
        {
            __ASSERT(0);
            return FALSE;
        }
        msAPI_FS_MIU_Copy(GET_DRAM_ADDR(&u8Fat12LastByte), USB_IO_TEMP_ADDR, 1);
        if ( !msAPI_MSDCtrl_SectorWrite( s8DeviceIndex, u32FATStartSectorNo + u32TempFatTableOffsetSectorNo + u16SectorSize, 1,  USB_IO_TEMP_ADDR ) )
        {
            __ASSERT(0);
            return FALSE;
        }
    }

    return TRUE;
}

U32 FAT_FATStructureGetNextCluster( U8 u8fsid, U32 u32DirEntryClusterNo )
{
    FAT_FileSysStruct *pFsStruct;//stFAT_FileSys;
    U32 u32DirEntryNextClusterNo;
    U8 u8FatType;

    //*get file system=======================================================*//
    pFsStruct=(FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);

    u8FatType=pFsStruct->stFAT.u8FATType;

    if (u8FatType == FAT_TYPE_NOT_SUPPORT)
    {
        __ASSERT(0);
        return (U32)NULL;
    }
     u32DirEntryNextClusterNo = FAT_FATStructureRead(u8fsid, u32DirEntryClusterNo);
     return u32DirEntryNextClusterNo;
}

static BOOLEAN FAT_PartitionTableRead( FAT_FileSysStruct *pstFileSys, U32 logicalBlockAddress,U8 *u8partitionBytes )
{
    //*Single partition, no MBR====================================================/
    if ( u8partitionBytes == NULL )
    {
        pstFileSys->u32RelativeSector = FAT_BOOT_SECTOR_OFFSET;
        return TRUE;
    }

    //*standard MBR===============================================================/
    else
    {
        //memcpy(( U8 * )&pstFileSys->u32RelativeSector, u8partitionBytes+8, 4);
        pstFileSys->u32RelativeSector=logicalBlockAddress;
        //printf("pstFileSys->u32RelativeSector=0x%08lx\n",pstFileSys->u32RelativeSector);
        return TRUE;
    }
}

static BOOLEAN FAT_BootSectorRead( FAT_FileSysStruct *pstFileSys )
{
    BootSectorStruct *pstBootSector;
    U32 u32SectorNo;
    U8  *u8RwDataCache;


    /*[01]read boot sector structure ==================================================*/
    u32SectorNo = pstFileSys->u32RelativeSector;

    if ( !msAPI_MSDCtrl_SectorRead( pstFileSys->DeviceIndex, u32SectorNo, 1, USB_IO_TEMP_ADDR ) )
    {
        __ASSERT(0);
        return FALSE;
    }
    u8RwDataCache = (U8 xdata*)msAPI_FS_GetAddr(USB_IO_TEMP_ADDR);

    if(u8RwDataCache==NULL)
    {
        __ASSERT(0);
        return FALSE;
    }


    /*[02]check boot sector structure =================================================*/
    /*[02-1]check if real boot sector by jump instruction =============================*/
    pstBootSector = &( pstFileSys->stBootSector );
    memcpy( pstBootSector->BS_jmpBoot, u8RwDataCache + 0, 3 );

    if ( ( pstBootSector->BS_jmpBoot[0] != 0xE9 ) && ( ( pstBootSector->BS_jmpBoot[0] != 0xEB ) && ( pstBootSector->BS_jmpBoot[2] != 0x90 ) ) )
    {
        FATDBG(printf("No Boot Sector\n"););
        __ASSERT(0);
        return FALSE;
    }

    /*[02-2]check if real boot sector by signature word ===============================*/
    memcpy( ( U8 * )&pstBootSector->BS_SignWord, u8RwDataCache + 510, 2 );

    if ( pstBootSector->BS_SignWord != 0xaa55 )
    {
        FATDBG(printf("Warnning Boot Sector SignWord != 0xaa55\n"););
    }

    /*[03]copy boot sector ============================================================*/
    /*[03-1]common part ===============================================================*/
    memcpy( pstBootSector->BS_OEMName, u8RwDataCache + 3, 8 );
    memcpy( ( U8 * )&pstBootSector->BPB_BytsPerSec, u8RwDataCache + 11, 2 );
    pstBootSector->BPB_SecPerClus = u8RwDataCache[13];
    memcpy( ( U8 * )&pstBootSector->BPB_RsvdSecCnt, u8RwDataCache + 14, 2 );
    pstBootSector->BPB_NumFATs = u8RwDataCache[16];
    memcpy( ( U8 * )&pstBootSector->BPB_RootEntCnt, u8RwDataCache + 17, 2 );
    memcpy( ( U8 * )&pstBootSector->BPB_TotSec16, u8RwDataCache + 19, 2 );
    pstBootSector->BPB_Media = u8RwDataCache[21];
    memcpy( ( U8 * )&pstBootSector->BPB_FATSz16, u8RwDataCache + 22, 2 );
    memcpy( ( U8 * )&pstBootSector->BPB_SecPerTrk, u8RwDataCache + 24, 2 );
    memcpy( ( U8 * )&pstBootSector->BPB_NumHeads, u8RwDataCache + 26, 2 );
    memcpy( ( U8 * )&pstBootSector->BPB_HiddSec, u8RwDataCache + 28, 4 );
    memcpy( ( U8 * )&pstBootSector->BPB_TotSec32, u8RwDataCache + 32, 4 );


    /*[03-2]check FAT12/16/32 =========================================================*/
    /*[03-2a]FAT12/FAT16 ==============================================================*/
    memcpy( pstBootSector->BS_FilSysType, u8RwDataCache + 54, 8 );

    if ( ( FAT_FATGetType( pstBootSector->BS_FilSysType ) == FAT_TYPE_FAT12 ) || ( FAT_FATGetType( pstBootSector->BS_FilSysType ) == FAT_TYPE_FAT16 ) )
    {
        pstBootSector->BS_DrvNum = u8RwDataCache[36];
        pstBootSector->BS_Reserved1 = u8RwDataCache[37];
        pstBootSector->BS_BootSig = u8RwDataCache[38];
        memcpy( ( U8 * )&pstBootSector->BS_VolID, u8RwDataCache + 39, 4 );
        memcpy( pstBootSector->BS_VolLab, u8RwDataCache + 43, 11 );
    }

    /*[03-2b]FAT32 ====================================================================*/
    else
    {
        memcpy( pstBootSector->BS_FilSysType, u8RwDataCache + 82, 8 );

        if ( FAT_FATGetType( pstBootSector->BS_FilSysType ) == FAT_TYPE_FAT32 )
        {
            memcpy( ( U8 * )&pstBootSector->BPB_FATSz32, u8RwDataCache + 36, 4 );
            memcpy( ( U8 * )&pstBootSector->BPB_ExtFlags, u8RwDataCache + 40, 2 );
            memcpy( ( U8 * )&pstBootSector->BPB_FSVer, u8RwDataCache + 42, 2 );
            memcpy( ( U8 * )&pstBootSector->BPB_RootClus, u8RwDataCache + 44, 4 );
            memcpy( ( U8 * )&pstBootSector->BPB_FSInfo, u8RwDataCache + 48, 2 );
            memcpy( ( U8 * )&pstBootSector->BPB_BkBootSec, u8RwDataCache + 50, 2 );

            pstBootSector->BS_DrvNum = u8RwDataCache[64];
            pstBootSector->BS_Reserved1 = u8RwDataCache[65];
            pstBootSector->BS_BootSig = u8RwDataCache[66];
            memcpy( ( U8 * )&pstBootSector->BS_VolID, u8RwDataCache + 67, 4 );

            memcpy( pstBootSector->BS_VolLab, u8RwDataCache + 71, 11 );
        }

        /*[03-2c]other type ===========================================================*/
        else
        {
            FATDBG(printf("File System Type is not supported! \n"););
            __ASSERT(0);
            return FALSE;
        }
    }

    pstFileSys->u16DirEntryCacheCount = (((U32)pstBootSector->BPB_BytsPerSec*pstBootSector->BPB_SecPerClus)/sizeof(DirEntryStruct))>128?128:(((U32)pstBootSector->BPB_BytsPerSec*pstBootSector->BPB_SecPerClus)/sizeof(DirEntryStruct));
    return TRUE;
}

#if 0
static BOOLEAN FAT_FATFsinfoFetch( U8 u8EnvironmentID)
{
    FS_EnvironmentStruct *pFS_Env;
    U32 u32FsinfoStartSectorNo;
    U16 u16BytePerSec;
    FAT_FileSysStruct *pFsStruct;
    U32 u32BufferAddress;
    //U32 u32FSI_LeadSig, u32FSI_StrucSig, u32FSI_TrailSig;
    //U8  *pu8RwDataCache;
    //U16 addr;

    //*get FAT file sys================================================//
    pFS_Env = msAPI_FSEnv_GetEnvironment(u8EnvironmentID);

    // get FAT file system
    pFsStruct=(FAT_FileSysStruct*)FCtrl_GetFileSystemXData(pFS_Env->u8FileSystemID);
    u16BytePerSec = pFsStruct->stBootSector.BPB_BytsPerSec;
    u32FsinfoStartSectorNo = pFsStruct->stBootSector.BPB_FSInfo + pFsStruct->u32RelativeSector;
    FAT_ReturnXData();

    u32BufferAddress = FAT_GetXDataMIUAddress(u8EnvironmentID, FAT_XDATA_OPTION_FSINFO_SECTOR);
    if ( !msAPI_MSDCtrl_SectorRead( pFS_Env->u8DeviceIndex, u32FsinfoStartSectorNo, 1, u32BufferAddress))
    {
        __ASSERT(0);
        FAT_ReturnXData();
        return FALSE;
    }

    // mark FSI code, request by Ken
    #if 0
    addr = (u32BufferAddress >> 12);
    pu8RwDataCache = (U8 xdata*)msAPI_FS_GetXData(addr);

    if(pu8RwDataCache==NULL)
    {
        __ASSERT(0);
        return FALSE;
    }


    /*check FSI_LeadSig =============================*/
    memcpy( (U8*)&u32FSI_LeadSig, pu8RwDataCache + 0, 4 );
    if ( u32FSI_LeadSig != 0x41615252 )
    {
        __ASSERT(0);
        FAT_ReturnXData();
        return FALSE;
    }

    /*check FSI_StrucSig ========================*/
    memcpy( (U8*)&u32FSI_StrucSig, pu8RwDataCache + 484, 4 );
    if ( u32FSI_StrucSig != 0x61417272 )
    {
        __ASSERT(0);
        FAT_ReturnXData();
        return FALSE;
    }

    /*check FSI_TrailSig ============================*/
    memcpy( (U8*)&u32FSI_TrailSig, pu8RwDataCache + 508, 4 );
    if ( u32FSI_TrailSig != 0xaa550000 )
    {
        __ASSERT(0);
        FAT_ReturnXData();
        return FALSE;
    }

    /*check FSInfo OK!save~~=============================*/
    //msAPI_FS_MIU_Copy(USB_IO_TEMP_ADDR, ( U32 )FAT_GetXDataMIUAddress(u8EnvironmentID, FAT_XDATA_OPTION_FSINFO_SECTOR), (U32)FAT_FSINFO_SECTOR_SIZE * u16BytePerSec );

    FAT_ReturnXData();
    #endif

    return TRUE;
}
#endif

static BOOLEAN FAT_FATFsinfoFetch(FAT_FileSysStruct *pstFileSys)
{
    U32 u32FsinfoStartSectorNo;
    U16 u16BytePerSec;
    //FAT_FileSysStruct *pFsStruct;
    U32 u32FSI_Free_Count, u32FSI_Nxt_Free;
    U8  *pu8RwDataCache;

    FATDBG(printf("Enter FAT_FATFsinfoFetch()\n"););
    if(pstFileSys->FileSystemID ==INVALID_DRIVE_INDEX)
    {
        __ASSERT(0);
        return FALSE;
    }

    // get FAT file system
    u16BytePerSec = pstFileSys->stBootSector.BPB_BytsPerSec;
    u32FsinfoStartSectorNo = pstFileSys->stBootSector.BPB_FSInfo + pstFileSys->u32RelativeSector;

    if ( !msAPI_MSDCtrl_SectorRead( pstFileSys->DeviceIndex, u32FsinfoStartSectorNo, 1, USB_IO_TEMP_ADDR))
    {
        __ASSERT(0);
        return FALSE;
    }

    pu8RwDataCache = (U8 xdata*)msAPI_FS_GetAddr(USB_IO_TEMP_ADDR);

    if(pu8RwDataCache==NULL)
    {
        __ASSERT(0);
        return FALSE;
    }

    memcpy( (U8*)&u32FSI_Free_Count, pu8RwDataCache + 488, 4 );

#if (!FILE_SYSTEM_SMALL)
#if COMPUTE_REAL_FREE_CLUSTER_COUNT
    U32 u32TotalFatTableSize = pstFileSys->stBootSector.BPB_FATSz32*pstFileSys->stBootSector.BPB_BytsPerSec;
    if(u32TotalFatTableSize < ENABLE_CALC_FREE_CLUSTER_THRESHOLD
    || u32FSI_Free_Count == 0xFFFFFFFF)
#else
    //If the value is 0xffffffff ,it means invalid. then the free cluster count
    // is unknown and must be computed
    if(u32FSI_Free_Count == 0xFFFFFFFF)
#endif
    {
        if(FAT_ComputedFreeClusterTotalCnt(pstFileSys, &u32FSI_Free_Count)==FALSE)
        {
            printf("!!! FAT_ComputedFreeClusterTotalCnt ERROR\n");
            u32FSI_Free_Count = pstFileSys->stFAT.u32FATTotalClusterNo;
        }
    }
#endif

    pstFileSys->u32FSI_Free_Count=u32FSI_Free_Count;

    memcpy( (U8*)&u32FSI_Nxt_Free, pu8RwDataCache + 492, 4 );

    pstFileSys->u32FSI_Nxt_Free=u32FSI_Nxt_Free;

    FATDBG(printf("Initial u32FSI_Free_Count = %lu\n",u32FSI_Free_Count););
    FATDBG(printf("Initial u32FSI_Nxt_Free = %lu\n",u32FSI_Nxt_Free););

    return TRUE;
}
#if 0//FILE_SYSTEM_GET_FREE_SPACE_ENABLE
static U32 FAT_FATFsinfoRead(U8 u8EnvironmentID, EN_FAT_FSINFO_OPTION Option)
{
    U32 u32FSI_Free_Count, u32FSI_Nxt_Free;
    U8 *pu8FSInfo;

    pu8FSInfo = (U8*)FAT_GetAddr(u8EnvironmentID, FAT_XDATA_OPTION_FSINFO_SECTOR);

    memcpy( (U8*)&u32FSI_Free_Count, pu8FSInfo + 488, 4 );
    memcpy( (U8*)&u32FSI_Nxt_Free, pu8FSInfo + 492, 4 );

    switch (Option)
    {
        case GET_FSI_FREE_COUNT:
                    return u32FSI_Free_Count;
        case GET_FSI_NXT_FREE:
                    return u32FSI_Nxt_Free;
    }
}
#endif


static BOOLEAN FAT_RootDirectroyInfo( FAT_FileSysStruct *pstFileSys )
{
    /*[01]FT32 =======================================================================*/
    if ( pstFileSys->stFAT.u8FATType == FAT_TYPE_FAT32 )
    {
        pstFileSys->u32RootDirStartClusterNo = pstFileSys->stBootSector.BPB_RootClus;
        pstFileSys->u32RootDirStartSectorNo = pstFileSys->stFAT.u32FATStartSectorNo + pstFileSys->stBootSector.BPB_NumFATs * pstFileSys->stBootSector.BPB_FATSz32;
        pstFileSys->u32RootDirTotalSectorCount = 0; //Not used for FAT32
    }

    /*[02]FAT12/16 ====================================================================*/
    else
    {
        pstFileSys->u32RootDirStartClusterNo = 0;
        pstFileSys->u32RootDirStartSectorNo = pstFileSys->stFAT.u32FATStartSectorNo + pstFileSys->stBootSector.BPB_NumFATs * pstFileSys->stBootSector.BPB_FATSz16;
        pstFileSys->u32RootDirTotalSectorCount = pstFileSys->stBootSector.BPB_RootEntCnt * sizeof( DirEntryStruct ) / pstFileSys->stBootSector.BPB_BytsPerSec;
    }

    /*[03]both FAT12/16/32 ============================================================*/
    pstFileSys->u32RootDirEndSectorNo = pstFileSys->u32RootDirStartSectorNo + pstFileSys->u32RootDirTotalSectorCount;

    return TRUE;
}



BOOLEAN FAT_InitialFileSystem(S8 deviceIndex, U32 logicalBlockAddress,U8* partitionBytes,FAT_FileSysStruct *pstFileSys)
{
    //*Note: save fix values of FAT and store in FILE_SYSTEM_MOUNTED_ADDR*//

    /*initial*/
    if(sizeof(FAT_FileSysStruct)>FILE_SYS_STRUCT_SIZE)
    {
        __ASSERT(0);
        return FALSE;
    }

    memset((void*)pstFileSys, 0, sizeof(FAT_FileSysStruct));

    pstFileSys->FileSystemType =FILE_SYSTEM_TYPE_FAT;
    pstFileSys->DeviceIndex    =deviceIndex;
    pstFileSys->u32FATTableOffsetSectorNo = 0;
    pstFileSys->u32CurrentFreeCluster = 2;
    pstFileSys->bIsFATCacheDirty = FALSE;
    pstFileSys->FileSystemSupport = FILE_SYSTEM_SUPPORT_READ;


    /*[01]read partition talbe ====================================================*/
    if(!FAT_PartitionTableRead(pstFileSys,logicalBlockAddress,partitionBytes))
    {
        __ASSERT(0);
        return FALSE;
    }

    /*[02]read boot sector structure ==============================================*/
    if(!FAT_BootSectorRead(pstFileSys))
    {
        __ASSERT(0);
        return FALSE;
    }

    /*[03]read FAT structure ======================================================*/
    if(!FAT_FATStructureReadRoot(pstFileSys,logicalBlockAddress))
    {
        __ASSERT(0);
        return FALSE;
    }

    /*[04]read root directory info ============================================*/
    if (!FAT_RootDirectroyInfo(pstFileSys))
    {
        __ASSERT(0);
        return FALSE;
    }

    /*[05]read FSInfo sector structure ========================================*/
    if(pstFileSys->stFAT.u8FATType == FAT_TYPE_FAT32)
    {
        FATDBG(printf("FAT_InitialFileSystem() : Fetch FSInfo\n"));
        if (!FAT_FATFsinfoFetch(pstFileSys))
        {
            __ASSERT(0);
            return FALSE;
        }
    }

    /*[06]flags ==================================================================*/
    pstFileSys->bInit = TRUE;


    return TRUE;
}



BOOLEAN FAT_SaveEnvironment(U8 u8EnvironmentID)
{
    FAT_FileSysStruct *pFsStruct;
    FS_EnvironmentStruct * pFS_Env;
    FAT_Environment * pFAT_Env;
    U32 u32RootDirStartClusterNo;
    U8 u8FATType;

    /*[01]get file system=======================================================*/
    pFS_Env = msAPI_FSEnv_GetEnvironment(u8EnvironmentID);
    if(pFS_Env == NULL)
    {
		__ASSERT(0);
        return FALSE;
    }

    // get FAT file system
    pFsStruct=(FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(pFS_Env->u8FileSystemID);

    u32RootDirStartClusterNo = pFsStruct->u32RootDirStartClusterNo;
    u8FATType = pFsStruct->stFAT.u8FATType;

    /*[02]get FAT_Environment=======================================================*/
    pFAT_Env = (FAT_Environment*)FAT_GetAddr(u8EnvironmentID,FAT_XDATA_OPTION_ENVIRONMENT);

    /*[03]save common part=======================================================*/
    pFAT_Env->s8DeviceIndex   = pFS_Env->u8DeviceIndex;
    pFAT_Env->u8FileSystemID  = pFS_Env->u8FileSystemID;
    pFAT_Env->u8EnvironmentID = u8EnvironmentID;

    /*[04]save current direcotry==================================================*/
    pFAT_Env->stCurrentDirectory.u32CurrentDirStartClusterNo = u32RootDirStartClusterNo;  //Root
    pFAT_Env->stCurrentDirectory.u32ParentDirStartClusterNo  = u32RootDirStartClusterNo;  //Root
    pFAT_Env->stCurrentDirectory.u32CurrentCluster = u32RootDirStartClusterNo;  //Root
    pFAT_Env->stCurrentDirectory.u32CurrentDirEntryCacheClusterNo = 0xFFFFFFFF;
    pFAT_Env->stCurrentDirectory.s16DirEntryCacheCurrentIndex = -1;
    pFAT_Env->stCurrentDirectory.s32CurrentDirEntryIndex = -1;
    pFAT_Env->stCurrentDirectory.s32LastDirEntryIndex=-1;

    /*[05]save FSInfo sector for FAT32=================================================*/
/*
    if ( u8FATType == FAT_TYPE_FAT32)
    {
         if ( !FAT_FATFsinfoFetch(u8EnvironmentID) )
        {
            __ASSERT(0);
            FAT_ReturnXData();
            return FALSE;
        }
    }
*/
    //==========================*//
    return TRUE;

    //printf("FAT_Environment Saved!! EnvironmentID=%bu, DeviceIndex=%bu\n",pFAT_Env->u8EnvironmentID, pFAT_Env->s8DeviceIndex);

}

#if 0
/*TRICKY FUNCTION!!*/
static void  FAT_DirectoryEntryGetName( DirEntryStruct *pstTempDirEntry, U16 *pu16FileName )
{
    U8 u8Loop;
    U8 ch;

    BOOLEAN nameIsLowerCase=(*((U8*)pstTempDirEntry+12))&(1<<3);
    BOOLEAN extIsLowerCase=(*((U8*)pstTempDirEntry+12))&(1<<4);



    /*[02]get file name ===============================================================*/
    /*[02-1]get 8-byte file name ======================================================*/
    for ( u8Loop = 0; u8Loop < 8; u8Loop++ )
    {

        if ( pstTempDirEntry->pu8DirEntryName[u8Loop] == ' ' )
        {
            break;
        }
        ch=pstTempDirEntry->pu8DirEntryName[u8Loop];

        if(nameIsLowerCase&& (ch>='A'&&ch<='Z'))
            ch=ch-'A'+'a';

        *pu16FileName = (U16)ch;
        pu16FileName++;
    }

    /*[02-2]get 3-byte file name extension ============================================*/
    for ( u8Loop = 0; u8Loop < 3; u8Loop++ )
    {
        if ( pstTempDirEntry->ps8DirEntryExtName[u8Loop] == ' ' )
        {
            break;
        }
        if ( u8Loop == 0 )
        {
            *pu16FileName = '.';
            pu16FileName++;
        }

        ch=pstTempDirEntry->ps8DirEntryExtName[u8Loop];
        if(extIsLowerCase && (ch>='A'&&ch<='Z'))
            ch=ch-'A'+'a';

        *pu16FileName = (U16)ch;
        pu16FileName++;
    }
    *pu16FileName = '\0';
}
#endif


#define FS_SECONDS_PER_YEAR 0x1E13380 //60*60*24*365
code U16 DaysPerMonth[12] =
{
    0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334,
};
void FAT_DirectoryEntrySave( U8 u8fsid, U8 u8EnvironmentID, DirEntryStruct * pstTempDirEntry, FileEntry * pFileToSet,U32 currentClusterNo,U32 currentDirEntryOffset )
{
    U16 tTime;
    U16 tDate;
    FS_TIME fsTime;

    //printf("%lu,%lu\n",currentClusterNo,currentDirEntryOffset);
    pFileToSet->EnvironmentID = u8EnvironmentID;
    pFileToSet->FileSystemID = u8fsid;
    pFileToSet->EntryAttrib = pstTempDirEntry->u8DirEntryAttrib;

    tTime = (pstTempDirEntry->u16DirEntryTime);
    tDate = (pstTempDirEntry->u16DirEntryDate);

    fsTime.u16Year = ((tDate>>9)&0x7F) + FS_DEFAULT_YEAR;
    fsTime.u8Month = (tDate>>5)&0x0F;
    fsTime.u8Day = tDate&0x1F;
    fsTime.u8Hour = (tTime>>11)&0x1F;
    fsTime.u8Min = (tTime>>5)&0x3F;
    fsTime.u8Sec = (tTime&0x1F)*2;
    //printf("0x%08Lx Year:%d Month:%bu Day:%bu Hour:%bu Min:%bu Sec:%bu\n",
    //        (U16)fsTime.u16Year, (U8)fsTime.u8Month, (U8)fsTime.u8Day, (U8)fsTime.u8Hour, (U8)fsTime.u8Min, (U8)fsTime.u8Sec);
    pFileToSet->EntrySeconds = msAPI_FS_ConvertStTime2Seconds(&fsTime);


    pFileToSet->EntryFileLength = (pstTempDirEntry->u32DirEntryFileLength);
    LL_assign(&pFileToSet->FileLength, pFileToSet->EntryFileLength);

    if(pstTempDirEntry->u8DirEntryAttrib&FAT_ATTRIB_DIRECTORY)
    {
        if ( pstTempDirEntry->pu8DirEntryName[0] == DIR_ENTRY_IS_DOT && pstTempDirEntry->pu8DirEntryName[1] != DIR_ENTRY_IS_DOT )
        {
          pFileToSet->EntryType = ENTRY_TYPE_DIR_DOT;

        }

        else if ( pstTempDirEntry->pu8DirEntryName[0] == DIR_ENTRY_IS_DOT && pstTempDirEntry->pu8DirEntryName[1] == DIR_ENTRY_IS_DOT )
        {
          pFileToSet->EntryType = ENTRY_TYPE_DIR_DOTDOT;

        }

        else
        {
          pFileToSet->EntryType = ENTRY_TYPE_DIR;

        }
    }
    else
    {
         pFileToSet->EntryType = ENTRY_TYPE_FILE;

    }

    //Eric For little endian
    //*((U16*)&pFileToSet->EntryID[0])=(pstTempDirEntry->u16DirEntryStartClusterHI);
    //*((U16*)&pFileToSet->EntryID[2])=(pstTempDirEntry->u16DirEntryStartClusterLO);

    //*((U16*)&pFileToSet->EntryID[0])=(pstTempDirEntry->u16DirEntryStartClusterLO);
    memcpy(&pFileToSet->EntryID[0],&(pstTempDirEntry->u16DirEntryStartClusterLO),2);
    //*((U16*)&pFileToSet->EntryID[2])=(pstTempDirEntry->u16DirEntryStartClusterHI);
    memcpy(&pFileToSet->EntryID[2],&(pstTempDirEntry->u16DirEntryStartClusterHI),2);

    memcpy(&pFileToSet->EntryID_Ext[0],&currentClusterNo,sizeof(currentClusterNo));
    memcpy(&pFileToSet->EntryID_Ext[4],&currentDirEntryOffset,sizeof(currentDirEntryOffset));
    //printf("\nDirEntry start clusterNo:0x%08lx",*(U32*)pFileToSet->EntryID);HERE;

    //File Entry update

    /* //Eric won't use
    if(((U16)pFileToSet)>=0xF000)
    {
        FileEntry tmpEntry;
        U8* pTmp;
        memcpy(&tmpEntry,pFileToSet,sizeof(FileEntry));
        //addr = (FAT_GetXDataMIUAddress(u8EnvironmentID, FAT_XDATA_OPTION_FAT_CURRENT_INFO)>>12); //Eric won't use
        //pTmp=(U8 xdata*)(msAPI_FS_GetXData(addr)+FAT_CURRENT_INFO_ENTRY_offset); //Eric won't use
        pTmp=(U8 xdata*)(FAT_GetAddr(u8EnvironmentID, FAT_XDATA_OPTION_FAT_CURRENT_INFO)+FAT_CURRENT_INFO_ENTRY_offset);

        memcpy(pTmp,&tmpEntry,sizeof(FileEntry));
        //msAPI_FS_ReturnXData(); //Eric won't use
    }
    else */
    {
        U8* pTmp;
        //addr = (FAT_GetXDataMIUAddress(u8EnvironmentID, FAT_XDATA_OPTION_FAT_CURRENT_INFO)>>12); //Eric won't use
        //pTmp=(U8 xdata*)(msAPI_FS_GetXData(addr)+FAT_CURRENT_INFO_ENTRY_offset); //Eric won't use
        pTmp=((U8 *)FAT_GetAddr(u8EnvironmentID, FAT_XDATA_OPTION_FAT_CURRENT_INFO)+(U32)FAT_CURRENT_INFO_ENTRY_offset);

        memcpy(pTmp,pFileToSet,sizeof(FileEntry));
    }
   // msAPI_FS_MIU_Copy(GET_DRAM_ADDR(), +FAT_CURRENT_INFO_ENTRY_offset, sizeof(FileEntry));

}

U32 FAT_FATGetSectorNo( U8 u8fsid, U32 u32ClusterNo )
{
    FAT_FileSysStruct* pFAT_FileSys;
    U32 u32RootDirEndSectorNo,u32RootDirStartSectorNo;
    U8 BPB_SecPerClus;
    U8 u8FATType;

    pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemInfo(u8fsid);

    u8FATType = pFAT_FileSys->stFAT.u8FATType;
    u32RootDirEndSectorNo=pFAT_FileSys->u32RootDirEndSectorNo;
    u32RootDirStartSectorNo = pFAT_FileSys->u32RootDirStartSectorNo;
    BPB_SecPerClus=pFAT_FileSys->stBootSector.BPB_SecPerClus;

    if(u32ClusterNo==0)
    {
        if(u8FATType == FAT_TYPE_FAT16||u8FATType == FAT_TYPE_FAT12)
        {
            return u32RootDirStartSectorNo;
        }
        else
        {
            __ASSERT(0);
            return 0;
        }
    }
    else
    {
        if(u32ClusterNo<2)
        {
            __ASSERT(0);
            return 0;
        }

        return u32RootDirEndSectorNo+ ( u32ClusterNo - 2) * BPB_SecPerClus ;

    }
}





U8 code strDOT[8]={'.',' ',' ',' ',' ',' ',' ',' '};
U8 code strDOTDOT[8]={'.','.',' ',' ',' ',' ',' ',' '};

static BOOLEAN _byteCompare(U8* b1,U8* b2,U8 len)
{
    U8 i=0;
    for(i=0;i<len;i++)
    {
        if(b1[i]!=b2[i])
            return FALSE;
    }
    return TRUE;
}

/*TRICKY FUNCTION!!*/
static void  FAT_DirectoryEntryGetName( DirEntryStruct *pstTempDirEntry, U16 *pu16FileName )
{
    U8 u8Loop;
    U8 ch;

    BOOLEAN nameIsLowerCase=(*((U8*)pstTempDirEntry+12))&(1<<3);
    BOOLEAN extIsLowerCase=(*((U8*)pstTempDirEntry+12))&(1<<4);



    /*[02]get file name ===============================================================*/
    /*[02-1]get 8-byte file name ======================================================*/
    for ( u8Loop = 0; u8Loop < 8; u8Loop++ )
    {

        if ( pstTempDirEntry->pu8DirEntryName[u8Loop] == ' ' )
        {
            break;
        }
        ch=pstTempDirEntry->pu8DirEntryName[u8Loop];

        if(nameIsLowerCase&& (ch>='A'&&ch<='Z'))
            ch=ch-'A'+'a';

        *pu16FileName = (U16)ch;
        pu16FileName++;
    }

    /*[02-2]get 3-byte file name extension ============================================*/
    for ( u8Loop = 0; u8Loop < 3; u8Loop++ )
    {
        if ( pstTempDirEntry->ps8DirEntryExtName[u8Loop] == ' ' )
        {
            break;
        }
        if ( u8Loop == 0 )
        {
            *pu16FileName = '.';
            pu16FileName++;
        }

        ch=pstTempDirEntry->ps8DirEntryExtName[u8Loop];
        if(extIsLowerCase && (ch>='A'&&ch<='Z'))
            ch=ch-'A'+'a';

        *pu16FileName = (U16)ch;
        pu16FileName++;
    }
    *pu16FileName = '\0';
}


EN_ENTRY_NEXT_RESULT FAT_DirEntryNext( U8 u8EnvironmentID, FileEntry* pFileToSet )
{
    DirEntryStruct * pstDirEntry;
    FAT_Environment* pFAT_Env;
    FAT_FileSysStruct* pstFAT_FileSys;

    U32 u32CurrentDirStartClusterNo;
    S16 s16CurrentDirEntryIndex;
    U8 longNameLen=0;
    U8 firstByteOfEntry;
    S32 currentDirEntryIndex=-1;
    U8 u8fsid;
    U16 dirEntryCacheCount;//=FAT_DIE_ENTRY_CACHE_BYTES
    BOOLEAN hasLongName=FALSE;

    U8 u8FATType;
    U16 u16RootEntryCount;
    U32 u32EntryCountPerSector;
    U32 u32RootStartClusterNo;
    U8* pu8Tmp;
    FS_EnvironmentStruct * pFS_Env;
    longNameLen=0;
    hasLongName=FALSE;
    currentDirEntryIndex=-1;

    pFS_Env = msAPI_FSEnv_GetEnvironment(u8EnvironmentID);
    if(pFS_Env == NULL)
    {
		__ASSERT(0);
        return ENTRY_NEXT_RESULT_ERROR;
    }
    else
    {
        u8fsid = pFS_Env->u8FileSystemID;
    }

    //clean up the FAT_CURRENT_INFO_ADR
    //pu8Tmp=(U8 xdata *)msAPI_FS_GetXData((FAT_GetXDataMIUAddress(u8EnvironmentID, FAT_XDATA_OPTION_FAT_CURRENT_INFO)>>12))+FAT_CURRENT_INFO_ENTRY_NAME_offset; //Eric won't use
    pu8Tmp=(U8 xdata *)msAPI_FS_GetAddr(FAT_GetMIUAddress(u8EnvironmentID, FAT_XDATA_OPTION_FAT_CURRENT_INFO))+FAT_CURRENT_INFO_ENTRY_NAME_offset;

    memset(pu8Tmp,0x00,256);

    pstFAT_FileSys=(FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);

    u8FATType=pstFAT_FileSys->stFAT.u8FATType;
    dirEntryCacheCount=pstFAT_FileSys->u16DirEntryCacheCount;
    u16RootEntryCount=pstFAT_FileSys->stBootSector.BPB_RootEntCnt;
    u32EntryCountPerSector=pstFAT_FileSys->stBootSector.BPB_BytsPerSec/sizeof(DirEntryStruct);
    u32RootStartClusterNo=pstFAT_FileSys->u32RootDirStartClusterNo;

    pFAT_Env=(FAT_Environment*)FAT_GetAddr(u8EnvironmentID, FAT_XDATA_OPTION_ENVIRONMENT);

    s16CurrentDirEntryIndex=pFAT_Env->stCurrentDirectory.s16DirEntryCacheCurrentIndex;
    u32CurrentDirStartClusterNo=pFAT_Env->stCurrentDirectory.u32CurrentDirStartClusterNo;
    currentDirEntryIndex=pFAT_Env->stCurrentDirectory.s32CurrentDirEntryIndex;

    while(TRUE)
    {

        s16CurrentDirEntryIndex++;
        currentDirEntryIndex++;
        FS_RESET_WDT();

        //@NOTE[TRIKY CODE]:FAT16 root directory special handle
        if((u8FATType!=FAT_TYPE_FAT32)&&(u32CurrentDirStartClusterNo==u32RootStartClusterNo))
        {

            U32 entryCount;
            pFAT_Env=(FAT_Environment*)FAT_GetAddr(u8EnvironmentID, FAT_XDATA_OPTION_ENVIRONMENT);

            entryCount=u32EntryCountPerSector*pFAT_Env->stCurrentDirectory.u16DirEntryCacheOffsetSectorNo;

            if((entryCount+s16CurrentDirEntryIndex)==u16RootEntryCount)
            {
                pFAT_Env=(FAT_Environment*)FAT_GetAddr(u8EnvironmentID, FAT_XDATA_OPTION_ENVIRONMENT);

                pFAT_Env->stCurrentDirectory.s32LastDirEntryIndex=currentDirEntryIndex;

                currentDirEntryIndex--;
                s16CurrentDirEntryIndex--;

                pFAT_Env->stCurrentDirectory.s16DirEntryCacheCurrentIndex=s16CurrentDirEntryIndex;
                pFAT_Env->stCurrentDirectory.s32CurrentDirEntryIndex=currentDirEntryIndex;

                return ENTRY_NEXT_RESULT_LAST;
            }
            else if((entryCount+s16CurrentDirEntryIndex)>u16RootEntryCount)
            {
                __ASSERT(0);
                return ENTRY_NEXT_RESULT_ERROR;
            }

        }
        //printf("\n s16CurrentDirEntryIndex: %u", s16CurrentDirEntryIndex);

        /*cache missed*/
        if ( s16CurrentDirEntryIndex >= dirEntryCacheCount)
        {

            U8 result=FAT_Cache_DirecotryDirEntryCacheNext( u8EnvironmentID);

            if(result==DIR_ENTRY_CACHE_IS_LAST)
            {
                pFAT_Env=(FAT_Environment*)FAT_GetAddr(u8EnvironmentID, FAT_XDATA_OPTION_ENVIRONMENT);

                pFAT_Env->stCurrentDirectory.s32LastDirEntryIndex=currentDirEntryIndex;
                currentDirEntryIndex--;
                s16CurrentDirEntryIndex--;
                pFAT_Env->stCurrentDirectory.s16DirEntryCacheCurrentIndex=s16CurrentDirEntryIndex;
                pFAT_Env->stCurrentDirectory.s32CurrentDirEntryIndex=currentDirEntryIndex;

                return ENTRY_NEXT_RESULT_LAST;
            }
            if (result==FALSE)
            {
                __ASSERT(0);

                return ENTRY_NEXT_RESULT_ERROR;
            }
            s16CurrentDirEntryIndex=0;
        }

        /*get DirEntry*/
        pstDirEntry = (DirEntryStruct*)FAT_GetAddr( u8EnvironmentID, FAT_XDATA_OPTION_DIR_ENTRY_CACHE );

        pstDirEntry += s16CurrentDirEntryIndex;

        firstByteOfEntry=pstDirEntry->pu8DirEntryName[0];

        if(pstDirEntry->u8DirEntryAttrib == FAT_ATTRIB_LONG_NAME)
        {
            U16 _LongNameOffset;
            //U8* pu8Tmp;
            U8 m=0;
            U16 au16Buffer[13];//sizeof(LONG_NAME_BYTE_POS_IN_DIRENTRY)*2

            if(!hasLongName)
            {
                if(firstByteOfEntry==DIR_ENTRY_IS_FREE)
                {
                    continue;
                }
                else if((firstByteOfEntry==0 ||firstByteOfEntry > FIRST_BYTE_OF_ENTRY_MAX_LONGNAME))//illegal
                {
                    __ASSERT(0);

                    //*update DirEntryCache index of FAT_Environment==============================================//
                    currentDirEntryIndex--;
                    s16CurrentDirEntryIndex--;
                    pFAT_Env=(FAT_Environment*)FAT_GetAddr(u8EnvironmentID, FAT_XDATA_OPTION_ENVIRONMENT);

                    pFAT_Env->stCurrentDirectory.s16DirEntryCacheCurrentIndex=s16CurrentDirEntryIndex;
                    pFAT_Env->stCurrentDirectory.s32CurrentDirEntryIndex=currentDirEntryIndex;

                    return ENTRY_NEXT_RESULT_ERROR;
                }
            }
            else
            {
                if(firstByteOfEntry==DIR_ENTRY_IS_FREE)
                {
                    __ASSERT(0);

                    longNameLen=0;
                    hasLongName=FALSE;

                    continue;
                }
            }


            memset(au16Buffer,0,sizeof(au16Buffer));
            //for(m=0;m<sizeof(LONG_NAME_BYTE_POS_IN_DIRENTRY);m++)
            for(m=0;m<LONG_NAME_BYTE_POS_IN_DIRENTRY_NUM;m++)
            {
                //au16Buffer[m]=*((U16*)( ((U8*)pstDirEntry) + LONG_NAME_BYTE_POS_IN_DIRENTRY[m])); //Eric won't use
                memcpy(&au16Buffer[m],(U8 *)pstDirEntry+LONG_NAME_BYTE_POS_IN_DIRENTRY[m],2);
                if(au16Buffer[m]==0)
                    break;

                longNameLen++;
            }

           _LongNameOffset=((U16)26)*((firstByteOfEntry&(~0x40))-1);

            //pu8Tmp=(U8 xdata *)msAPI_FS_GetXData((FAT_GetXDataMIUAddress(u8EnvironmentID, FAT_XDATA_OPTION_FAT_CURRENT_INFO)>>12))+FAT_CURRENT_INFO_ENTRY_NAME_offset; //Eric won't use
            pu8Tmp=(U8 xdata *)msAPI_FS_GetAddr(FAT_GetMIUAddress(u8EnvironmentID, FAT_XDATA_OPTION_FAT_CURRENT_INFO))+FAT_CURRENT_INFO_ENTRY_NAME_offset;
            memcpy(pu8Tmp + _LongNameOffset ,au16Buffer,sizeof(au16Buffer));

            hasLongName=TRUE;

            continue;

        }
        else if(pstDirEntry->u8DirEntryAttrib == FAT_ATTRIB_VOLUME_ID)
        {
            continue;
        }
        else
        {
            if(firstByteOfEntry==DIR_ENTRY_IS_LAST)
            {
                U8* pTmp;
                U16 charEnd=0;

                pstDirEntry--;                           //<====move to last Direcotry entry

                //*update DirEntryCache index of FAT_Environment==============================================//

                pFAT_Env=(FAT_Environment*)FAT_GetAddr(u8EnvironmentID, FAT_XDATA_OPTION_ENVIRONMENT);

                pFAT_Env->stCurrentDirectory.s32LastDirEntryIndex=currentDirEntryIndex;

                currentDirEntryIndex--;
                s16CurrentDirEntryIndex--;
                pFAT_Env->stCurrentDirectory.s16DirEntryCacheCurrentIndex=s16CurrentDirEntryIndex;
                pFAT_Env->stCurrentDirectory.s32CurrentDirEntryIndex=currentDirEntryIndex;

                //name update
                pTmp=((U8 *)FAT_GetAddr(u8EnvironmentID, FAT_XDATA_OPTION_FAT_CURRENT_INFO)+(U32)FAT_CURRENT_INFO_ENTRY_NAME_offset);

                memcpy(pTmp ,&charEnd,sizeof(charEnd));

              #if (!FILE_SYSTEM_SMALL)
                FAT_EntrySetCurrentNameShortOnly(u8EnvironmentID,FALSE);
              #endif

                //File Entry update
                pFileToSet->EntryType = ENTRY_TYPE_LAST;
                /* //Eric won't use
                if(((U16)pFileToSet)>=0xF000)
                {
                    FileEntry tmpEntry;

                    memcpy(&tmpEntry,pFileToSet,sizeof(FileEntry));
                    //addr = (FAT_GetXDataMIUAddress(u8EnvironmentID, FAT_XDATA_OPTION_FAT_CURRENT_INFO)>>12); //Eric won't use
                    //pTmp=(U8 xdata*)(msAPI_FS_GetXData(addr)+FAT_CURRENT_INFO_ENTRY_offset); //Eric won't use
                    pTmp=(U8 xdata*)(FAT_GetAddr(u8EnvironmentID, FAT_XDATA_OPTION_FAT_CURRENT_INFO)+FAT_CURRENT_INFO_ENTRY_offset);

                    memcpy(pTmp,&tmpEntry,sizeof(FileEntry));
                    //msAPI_FS_ReturnXData(); //Eric won't use
                }
                else */
                {
                    pTmp=((U8 *)FAT_GetAddr(u8EnvironmentID, FAT_XDATA_OPTION_FAT_CURRENT_INFO)+(U32)FAT_CURRENT_INFO_ENTRY_offset);

                    memcpy(pTmp,pFileToSet,sizeof(FileEntry));
                }

                return ENTRY_NEXT_RESULT_LAST;
            }
            else if(firstByteOfEntry == DIR_ENTRY_IS_DOT)
            {

                if((pstDirEntry->u8DirEntryAttrib & FAT_ATTRIB_DIRECTORY)==0
                    ||(!(_byteCompare(&strDOT[0],pstDirEntry->pu8DirEntryName,8)||_byteCompare(&strDOTDOT[0],pstDirEntry->pu8DirEntryName,8))))
                {
                    __ASSERT(0);

                    //printf("%bu\n",(U8)(pstDirEntry->u8DirEntryAttrib & FAT_ATTRIB_DIRECTORY));
                    //printf("%bu\n",(U8)_byteCompare(&strDOT[0],pstDirEntry->pu8DirEntryName,8));
                    //printf("%bu\n",(U8)_byteCompare(&strDOTDOT[0],pstDirEntry->pu8DirEntryName,8));

                    //*update DirEntryCache index of FAT_Environment==============================================//
                    currentDirEntryIndex--;
                    s16CurrentDirEntryIndex--;
                    pFAT_Env=(FAT_Environment*)FAT_GetAddr(u8EnvironmentID, FAT_XDATA_OPTION_ENVIRONMENT);

                    pFAT_Env->stCurrentDirectory.s16DirEntryCacheCurrentIndex=s16CurrentDirEntryIndex;
                    pFAT_Env->stCurrentDirectory.s32CurrentDirEntryIndex=currentDirEntryIndex;

                    return ENTRY_NEXT_RESULT_ERROR;
                }
                else
                {
                    continue;

                }

            }
            else if(firstByteOfEntry==DIR_ENTRY_IS_FREE)
            {
                continue;
            }
            else if((firstByteOfEntry<0x20&&firstByteOfEntry!=0x05)
                ||(firstByteOfEntry==0x22)
                ||(0x29<firstByteOfEntry&&firstByteOfEntry<0x30&&firstByteOfEntry!=0x2D)
                ||(0x39<firstByteOfEntry&&firstByteOfEntry<0x40)
                ||(0x5A<firstByteOfEntry&&firstByteOfEntry<0x5E)
                ||firstByteOfEntry==0x7C)
            {
                //The following characters are not legal in any bytes of DIR_Name:
                //Values less than 0x20 except for the special case of 0x05 in DIR_Name[0] described above.
                //0x22, 0x2A, 0x2B, 0x2C, 0x2E, 0x2F, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x5B, 0x5C, 0x5D, and 0x7C.
                __ASSERT(0);
                FATDBG(printf("firstByteOfEntry=0x%02bx,pstDirEntry->u8DirEntryAttrib=0x%02bx\n",firstByteOfEntry,pstDirEntry->u8DirEntryAttrib));
                continue;
            }
            else
            {
                if(pstDirEntry->u16DirEntryStartClusterHI == 0xFFFF && pstDirEntry->u16DirEntryStartClusterLO == 0xFFFF)
                {
                    continue;
                }

                FAT_DirectoryEntrySave( u8fsid, u8EnvironmentID, pstDirEntry, pFileToSet, u32CurrentDirStartClusterNo, currentDirEntryIndex);

                if(hasLongName)
                {

                    //U8 *pu8Tmp;
                    U16 charEnd=0;
                    //pu8Tmp=(U8 xdata *)msAPI_FS_GetXData((FAT_GetXDataMIUAddress(u8EnvironmentID, FAT_XDATA_OPTION_FAT_CURRENT_INFO)>>12))+FAT_CURRENT_INFO_ENTRY_NAME_offset; //Eric won't use
                    pu8Tmp=(U8 xdata *)msAPI_FS_GetAddr(FAT_GetMIUAddress(u8EnvironmentID, FAT_XDATA_OPTION_FAT_CURRENT_INFO))+FAT_CURRENT_INFO_ENTRY_NAME_offset;
                    memcpy(pu8Tmp + longNameLen*2, &charEnd,sizeof(charEnd));

                  #if (!FILE_SYSTEM_SMALL)
                    FAT_EntrySetCurrentNameShortOnly(u8EnvironmentID,FALSE);
                  #endif

                }
                else
                {
                    U16 au16Buffer[13];
                    //U8* pu8Tmp;
                    memset(au16Buffer,0,sizeof(au16Buffer));
                    FAT_DirectoryEntryGetName(pstDirEntry,au16Buffer);

                    pu8Tmp=((U8 *)FAT_GetAddr(u8EnvironmentID, FAT_XDATA_OPTION_FAT_CURRENT_INFO)+(U32)FAT_CURRENT_INFO_ENTRY_NAME_offset);

                    memcpy(pu8Tmp,au16Buffer,sizeof(au16Buffer));

                  #if (!FILE_SYSTEM_SMALL)
                    FAT_EntrySetCurrentNameShortOnly(u8EnvironmentID,TRUE);
                  #endif
                }

                //*update DirEntryCache index of FAT_Environment==============================================//
                pFAT_Env=(FAT_Environment*)FAT_GetAddr(u8EnvironmentID, FAT_XDATA_OPTION_ENVIRONMENT);

                pFAT_Env->stCurrentDirectory.s16DirEntryCacheCurrentIndex=s16CurrentDirEntryIndex;
                pFAT_Env->stCurrentDirectory.s32CurrentDirEntryIndex=currentDirEntryIndex;

                return ENTRY_NEXT_RESULT_SUCCESS;
            }
        }
    }
}



BOOLEAN FAT_DirectroyDirEntryToFirst(U8 u8EnvironmentID)
{
    FAT_Environment *pFAT_Env;
    U32 u32CurrentDirClusterNo;

    pFAT_Env = (FAT_Environment*)FAT_GetAddr(u8EnvironmentID, FAT_XDATA_OPTION_ENVIRONMENT);

    u32CurrentDirClusterNo = pFAT_Env->stCurrentDirectory.u32CurrentDirStartClusterNo;
    pFAT_Env->stCurrentDirectory.s32CurrentDirEntryIndex=-1;
    pFAT_Env->stCurrentDirectory.s32LastDirEntryIndex=-1;

    if ( !FAT_Cache_DirectoryClusterFetch(u8EnvironmentID))
    {
        __ASSERT(0);
         return FALSE;
    }

    if (!FAT_Cache_DirectoryDirEntryCacheFetchFromStart(u8EnvironmentID, u32CurrentDirClusterNo))
    {
         __ASSERT(0);
         return FALSE;
    }

     return TRUE; // WBT


}




//can only be chaned to child or directly to root
BOOLEAN FAT_DirectoryChange(U8 u8EnvironmentId, U32 u32DirStartClusterNo)
{
    FAT_FileSysStruct *pstFAT_fileSys;
    FS_EnvironmentStruct * pFS_Env;
    FAT_Environment * pFAT_Env;
    DirEntryStruct* pDirEntry;
    U8 u8TempParentDirClusterNo[4];
    U32 u32RootDirStartClusterNo;
    U32 u32TotalClusterCount;
    U32 directoryClusterNoBackup;
    U32 u32Temp=0;

    //*[01]get file system========================================================*//
    pFS_Env = msAPI_FSEnv_GetEnvironment(u8EnvironmentId);
    if(pFS_Env == NULL)
    {
		__ASSERT(0);
        return FALSE;
    }

    pstFAT_fileSys=(FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(pFS_Env->u8FileSystemID);

    u32RootDirStartClusterNo=pstFAT_fileSys->u32RootDirStartClusterNo;
    u32TotalClusterCount=pstFAT_fileSys->stFAT.u32FATTotalClusterNo;

    pFAT_Env = (FAT_Environment*)FAT_GetAddr(u8EnvironmentId, FAT_XDATA_OPTION_ENVIRONMENT);

    directoryClusterNoBackup=pFAT_Env->stCurrentDirectory.u32CurrentDirStartClusterNo;
    pFAT_Env->stCurrentDirectory.u32CurrentDirStartClusterNo = u32DirStartClusterNo;
    pFAT_Env->stCurrentDirectory.u32CurrentCluster = u32DirStartClusterNo;

    if(u32DirStartClusterNo>=u32TotalClusterCount)
    {
        __ASSERT(0);
        pFAT_Env = (FAT_Environment*)FAT_GetAddr(u8EnvironmentId, FAT_XDATA_OPTION_ENVIRONMENT);

        pFAT_Env->stCurrentDirectory.u32CurrentDirStartClusterNo=directoryClusterNoBackup;
        pFAT_Env->stCurrentDirectory.u32CurrentCluster = directoryClusterNoBackup;
        return FALSE;
    }


    //*[02]fetch all cluster# of current directory for FAT12/16/32================*//
    if(!FAT_Cache_DirectoryClusterFetch(u8EnvironmentId))
    {
        __ASSERT(0);
        pFAT_Env = (FAT_Environment*)FAT_GetAddr(u8EnvironmentId, FAT_XDATA_OPTION_ENVIRONMENT);

        pFAT_Env->stCurrentDirectory.u32CurrentDirStartClusterNo=directoryClusterNoBackup;
        pFAT_Env->stCurrentDirectory.u32CurrentCluster = directoryClusterNoBackup;
        return FALSE;
    }

    //*fetch to environment pool==============================================*//
    if ( !FAT_Cache_DirectoryDirEntryCacheFetchFromStart(u8EnvironmentId, u32DirStartClusterNo) )
    {
        __ASSERT(0);
        pFAT_Env = (FAT_Environment*)FAT_GetAddr(u8EnvironmentId, FAT_XDATA_OPTION_ENVIRONMENT);

        pFAT_Env->stCurrentDirectory.u32CurrentDirStartClusterNo=directoryClusterNoBackup;
        pFAT_Env->stCurrentDirectory.u32CurrentCluster = directoryClusterNoBackup;
        return FALSE;
    }


    if ( u32DirStartClusterNo == u32RootDirStartClusterNo )
    {
        /*update FAT_Environment info ==============================================*/
        pFAT_Env = (FAT_Environment*)FAT_GetAddr(u8EnvironmentId, FAT_XDATA_OPTION_ENVIRONMENT);

        pFAT_Env->stCurrentDirectory.u32ParentDirStartClusterNo  = u32RootDirStartClusterNo;    //root
        pFAT_Env->stCurrentDirectory.u32CurrentDirStartClusterNo = u32RootDirStartClusterNo;    //root
        pFAT_Env->stCurrentDirectory.u32CurrentCluster = u32RootDirStartClusterNo;
        pFAT_Env->stCurrentDirectory.s32CurrentDirEntryIndex= -1;
        pFAT_Env->stCurrentDirectory.s32LastDirEntryIndex=-1;
    }
    else
    {
        FileEntry pFileToSet;
        memset(&pFileToSet,0,sizeof(pFileToSet));

        pDirEntry = (DirEntryStruct*)FAT_GetAddr( u8EnvironmentId, FAT_XDATA_OPTION_DIR_ENTRY_CACHE );

        if ( pDirEntry->pu8DirEntryName[0] != DIR_ENTRY_IS_DOT )
        {
            __ASSERT(0);
            #if 0 //remove following check due to customer spec
            FAT_ReturnXData();
            pFAT_Env = (FAT_Environment*)FAT_GetXData(u8EnvironmentId, FAT_XDATA_OPTION_ENVIRONMENT);
            pFAT_Env->stCurrentDirectory.u32CurrentDirStartClusterNo=directoryClusterNoBackup;
            FAT_ReturnXData();
            return FALSE;
            #endif
        }

        pDirEntry++;
        if ( pDirEntry->pu8DirEntryName[0] != DIR_ENTRY_IS_DOT || pDirEntry->pu8DirEntryName[1] != DIR_ENTRY_IS_DOT )
        {
            __ASSERT(0);
            pFAT_Env = (FAT_Environment*)FAT_GetAddr(u8EnvironmentId, FAT_XDATA_OPTION_ENVIRONMENT);

            pFAT_Env->stCurrentDirectory.u32CurrentDirStartClusterNo=directoryClusterNoBackup;
            pFAT_Env->stCurrentDirectory.u32CurrentCluster = directoryClusterNoBackup;
            return FALSE;
        }

        //Eric for little-endian
        //memcpy( (U8*)&u8TempParentDirClusterNo[0], (U8*)&pDirEntry->u16DirEntryStartClusterHI, 2 );
        //memcpy( (U8*)&u8TempParentDirClusterNo[2], (U8*)&pDirEntry->u16DirEntryStartClusterLO, 2 );
        memcpy( (U8*)&u8TempParentDirClusterNo[0], (U8*)&pDirEntry->u16DirEntryStartClusterLO, 2 );
        memcpy( (U8*)&u8TempParentDirClusterNo[2], (U8*)&pDirEntry->u16DirEntryStartClusterHI, 2 );


        FAT_DirectoryEntrySave(pFS_Env->u8FileSystemID, u8EnvironmentId, pDirEntry, &pFileToSet, u32DirStartClusterNo, 0);

        //*update FAT_Envrionment info==========================================*//
        pFAT_Env = (FAT_Environment*)FAT_GetAddr(u8EnvironmentId, FAT_XDATA_OPTION_ENVIRONMENT);

        memcpy(&u32Temp,u8TempParentDirClusterNo,4);
        //if ( *((U32*)u8TempParentDirClusterNo) == 0 )    //means parent direcotry is root
        if ( u32Temp == 0 )    //means parent direcotry is root
        {
            pFAT_Env->stCurrentDirectory.u32ParentDirStartClusterNo =u32RootDirStartClusterNo;
        }
        else
        {
            //pFAT_Env->stCurrentDirectory.u32ParentDirStartClusterNo  = *((U32*)u8TempParentDirClusterNo);
            memcpy(&(pFAT_Env->stCurrentDirectory.u32ParentDirStartClusterNo),u8TempParentDirClusterNo,4);
        }

        pFAT_Env->stCurrentDirectory.u32CurrentDirStartClusterNo = u32DirStartClusterNo;
        pFAT_Env->stCurrentDirectory.u32CurrentCluster = u32DirStartClusterNo;
        pFAT_Env->stCurrentDirectory.s32CurrentDirEntryIndex= -1;
        pFAT_Env->stCurrentDirectory.s32LastDirEntryIndex=-1;
    }

    return TRUE;

}




void FAT_HandlePostCreate( U8 u8FileHandleNo, FileEntry *pFileEntry, U8 u8OpenMode )
{
    FAT_FileHandle * pstFAT_FileHandle;
    FAT_FileInode  *pFATInode;
    U8 i;

    for(i=0; i < FS_FILE_HANDLE_NUM; i++)
    {
        pFATInode = (FAT_FileInode*)FCtrl_GetFileInodeInfo(i);
        if(pFATInode->pub_inodeheader.InodeID!=INVALID_FILE_INODEID && pFATInode->pub_inodeheader.FileSystemID == pFileEntry->FileSystemID)
        {
            if(memcmp(pFileEntry->EntryID_Ext, pFATInode->pub_inodeheader.stFileEntry.EntryID_Ext,8)==0)
            {
                  if(pFATInode->pub_inodeheader.stFileEntry.EntryID[0]==0 && pFATInode->pub_inodeheader.stFileEntry.EntryID[1]==0 &&
                        pFATInode->pub_inodeheader.stFileEntry.EntryID[2]==0 && pFATInode->pub_inodeheader.stFileEntry.EntryID[3]==0)
                  {
                         memcpy(&pFATInode->pub_inodeheader.stFileEntry.EntryID[0], &pFileEntry->EntryID[0], 4);
                  }
                 else
                 {
                         __ASSERT(memcmp(pFileEntry->EntryID,  pFATInode->pub_inodeheader.stFileEntry.EntryID, 4) == 0);
                 }
                 __ASSERT( pFATInode->pub_inodeheader.refCnt != 0);
                 pFATInode->pub_inodeheader.refCnt++;
                 break;
            }
        }
    }
    if( i==FS_FILE_HANDLE_NUM)
    {
        for(i=0; i < FS_FILE_HANDLE_NUM; i++)
        {
             pFATInode = (FAT_FileInode*)FCtrl_GetFileInodeInfo(i);
             if(pFATInode->pub_inodeheader.InodeID ==INVALID_FILE_INODEID)
             {
                    pFATInode->pub_inodeheader.InodeID = i;
                    pFATInode->pub_inodeheader.FileSystemID = pFileEntry->FileSystemID;
                    pFATInode->pub_inodeheader.refCnt = 1;
//                    memcpy( (U8*)&pInode->u32FileStartClusterNo, (U8*)&pFileEntry->EntryID, 4);
//                    memcpy( (U8*)&pInode->u32DirStartCluster, (U8*)&pFileEntry->EntryID_Ext, 4);
//                    memcpy( (U8*)&pInode->u32DirEntryOffset, (U8*)&pFileEntry->EntryID_Ext[4], 4);
                    //pInode->u8FileAttrib = 0;
                    pFATInode->pub_inodeheader.stFileEntry = *pFileEntry;
                    pFATInode->u8FileAttrib = 0;
                    pFATInode->u32FileTotalSize = pFileEntry->FileLength.Lo;
                    pFATInode->u32FileStartClusterNo   = 0;
                    pFATInode->u32DirStartCluster = 0;
                    pFATInode->u32DirEntryOffset = 0;
                    //printf("allocate-->inode %02b of %02b\n", i, u8FileHandleNo);
                    break;
             }
         }
    }
    __ASSERT( i<FS_FILE_HANDLE_NUM);

    pstFAT_FileHandle = FAT_File_GetHandleInfo(u8FileHandleNo);
    pstFAT_FileHandle->pub_fileheader.InodeID = i;

    pstFAT_FileHandle->pub_fileheader.HandleID = u8FileHandleNo;
    pstFAT_FileHandle->pub_fileheader.FileSystemID = pFileEntry->FileSystemID;

    /*file attributes =========================*/
    pstFAT_FileHandle->u32FilePosition = 0;

    /*file cluster ============================*/
    pstFAT_FileHandle->u32FileCurrentClusterNo = 0;
    pstFAT_FileHandle->u32FileCurrentSectorNo  = 0;


    //Open Mode
    pstFAT_FileHandle->u8OpenMode = u8OpenMode;


}



void FAT_GetCurrentFileEntry(U8 enid, FileEntry *entry)
{
    U8* pData;

    pData=((U8 *)FAT_GetAddr(enid, FAT_XDATA_OPTION_FAT_CURRENT_INFO)+(U32)FAT_CURRENT_INFO_ENTRY_offset);

    memcpy(entry, pData, sizeof(FileEntry));
}



extern BOOLEAN DirEntryIterator_Reset(U8 fsid,U32 directoryStartCluster,U32 dirEntryIndex,U32 bufferAddress4KAligned);
extern BOOLEAN DirEntryIterator_Previous(void);
extern BOOLEAN FAT_FAT32ClusterChainScan(U8 u8fsid, U32 u32StartClusterNo, U32 *u32LenToSet, U32 *NextClusterToSet);
extern BOOLEAN FAT_FAT16ClusterChainScan(U8 u8fsid, U32 u32StartClusterNo, U32 *u32LenToSet, U32 *NextClusterToSet);
extern BOOLEAN FAT_FAT12ClusterChainScan(U8 u8fsid, U32 u32StartClusterNo, U32 *u32LenToSet, U32 *NextClusterToSet);

static BOOLEAN  FAT_FILE_AppendClusterChain(   U8 fsid, U8 u8FileHandleID, U32 u32ChainStartCluster, U16 curIndex, U8 u8FatType, U8*merge2Previous)
{
    BOOLEAN bResult = FALSE;
    U32 u32ChainLength;
    File_ClusterChain* pClusterChain;
    FAT_FileInode *pFATInode;
    U32 u32NextClusterNo;
    U8 firstMerge = 1;
    FAT_FileHandle *pFileHandle = FAT_File_GetHandleInfo(u8FileHandleID);

    *merge2Previous = 0;
    pClusterChain=FAT_File_GetHandleClusterChainInfo(pFileHandle->pub_fileheader.InodeID);

    while(curIndex < (U16)CLUSTER_CHAIN_SIZE - 1)
    {
        bResult = FALSE;
        if(u8FatType==FAT_TYPE_FAT32)
        {
            bResult=FAT_FAT32ClusterChainScan(fsid, u32ChainStartCluster, &u32ChainLength, &u32NextClusterNo);
        }
        else if(u8FatType==FAT_TYPE_FAT16)
        {
            bResult=FAT_FAT16ClusterChainScan(fsid, u32ChainStartCluster, &u32ChainLength, &u32NextClusterNo);
        }
        else
        {
            bResult=FAT_FAT12ClusterChainScan(fsid, u32ChainStartCluster, &u32ChainLength, &u32NextClusterNo);
        }


        if(!bResult)
        {
            __ASSERT(0);
            break;
        }

        if(curIndex > 0 && pClusterChain[curIndex-1].u32ClusterChainStart+
                                        pClusterChain[curIndex-1].u32ClusterChainLength == u32ChainStartCluster)
        {
             pClusterChain[curIndex-1].u32ClusterChainLength += u32ChainLength;
             if(firstMerge)
                 *merge2Previous = 1;
        }
        else
        {
             pClusterChain[curIndex].u32ClusterChainStart = u32ChainStartCluster;
             pClusterChain[curIndex].u32ClusterChainLength = u32ChainLength;
             curIndex++;
        }
        firstMerge = 0;
        pClusterChain[curIndex].u32ClusterChainStart = u32ChainStartCluster;
        pClusterChain[curIndex].u32ClusterChainLength = u32ChainLength;


        //printf("[%u]: u32ChainStartCluster: %lu, u32ChainLength: %lu, u32NextClusterNo: %lu\n",
        //u16Index, u32ChainStartCluster, u32ChainLength, u32NextClusterNo);

        if(u32NextClusterNo >= 0x0FFFFFF8)
        {
            pClusterChain[curIndex].u32ClusterChainStart = u32NextClusterNo;
            pClusterChain[curIndex].u32ClusterChainLength = 0;

            //printf("  ~~~0x%08lx 0x%08lx 0x%08lx 0x%08lx\n",pClusterChain[0].u32ClusterChainStart,pClusterChain[0].u32ClusterChainLength,pClusterChain[1].u32ClusterChainStart,pClusterChain[1].u32ClusterChainLength);

            pFATInode = FAT_File_GetInodeFromHandle(u8FileHandleID);
            if(pFATInode == NULL)
            {
                     __ASSERT(0);
                     return FALSE;
            }
             pFATInode->bIsClusterChainActive = TRUE;
             bResult = TRUE;

            break;
        }
        u32ChainStartCluster = u32NextClusterNo;
    }
    return bResult;
}

static BOOLEAN FAT_FileClusterChainFetch(U8 u8FileHandleID)
{
    FAT_FileHandle *pstFAT_FileHandle;
    FAT_FileInode   *pFATInode;
    U8 u8FatType;
    U32 u32ChainStartCluster;
    U8 fsid;
    File_ClusterChain* pClusterChain;
    FAT_FileSysStruct *pFsStruct;

    pstFAT_FileHandle = FAT_File_GetHandleInfo(u8FileHandleID);
    fsid = pstFAT_FileHandle->pub_fileheader.FileSystemID;

    pFsStruct=(FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(fsid);
    u8FatType=pFsStruct->stFAT.u8FATType;

    pFATInode = FAT_File_GetInodeFromHandle(u8FileHandleID);
    if(pFATInode == NULL)
    {
          __ASSERT(0);
          return FALSE;
    }
    u32ChainStartCluster = pFATInode->u32FileStartClusterNo;


    pClusterChain=FAT_File_GetHandleClusterChainInfo(pstFAT_FileHandle->pub_fileheader.InodeID);
    memset(pClusterChain, 0x0, 0x1000);

    return FAT_FILE_AppendClusterChain(fsid, u8FileHandleID, u32ChainStartCluster, 0,  u8FatType, &u8FatType);

}

BOOLEAN FAT_FileOpen(U8 u8FileHandleNo, void * pFileEntry,BOOLEAN fastOpen)
{
    FAT_FileHandle * pstFAT_FileHandle;
    FileEntry * pTempFileEntry;
    BOOLEAN bIsDirty;
    U8 u8fsid;
    FAT_FileInode *pFATInode;
    BOOLEAN bIsClusterChainActive;
    U32 u32StartClusterNo;

    pstFAT_FileHandle = FAT_File_GetHandleInfo(u8FileHandleNo);

    pTempFileEntry = (FileEntry *)pFileEntry;

    //*update FAT_FileHandle info============================================*//

    pstFAT_FileHandle->u32FilePosition = 0;

    pstFAT_FileHandle->u32FileCurrentSectorNo = 0;
    pstFAT_FileHandle->u16ClusterChainIndex = 0;
    u8fsid=pstFAT_FileHandle->pub_fileheader.FileSystemID;
    memcpy( (U8*)&pstFAT_FileHandle->u32FileCurrentClusterNo, (U8*)&pTempFileEntry->EntryID, 4 );

   pFATInode = FAT_File_GetInodeFromHandle(u8FileHandleNo);
   if(pFATInode == NULL)
   {
           __ASSERT(0);
           return FALSE;
   }
   if(pFATInode->pub_inodeheader.refCnt == 1)
   {
          pFATInode->u8FileAttrib = pTempFileEntry->EntryAttrib;
          pFATInode->u32FileTotalSize = pTempFileEntry->FileLength.Lo;
          memcpy( (U8*)&pFATInode->u32FileStartClusterNo, (U8*)&pTempFileEntry->EntryID, 4 );

          memcpy( (U8*)&pFATInode->u32DirStartCluster, (U8*)&pTempFileEntry->EntryID_Ext, 4 );
          memcpy( (U8*)&pFATInode->u32DirEntryOffset, (U8*)&pTempFileEntry->EntryID_Ext[4], 4 );
          bIsClusterChainActive = pFATInode->bIsClusterChainActive = FALSE;
   }
   else
         bIsClusterChainActive = pFATInode->bIsClusterChainActive;

   u32StartClusterNo = pFATInode->u32FileStartClusterNo;

   pstFAT_FileHandle->u32FileCurrentClusterNo = u32StartClusterNo;
   pstFAT_FileHandle->u16ClusterChainIndex = 0;
   pstFAT_FileHandle->u32FileCurrentSectorNo = 0;


    bIsDirty=((FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid))->bIsFATCacheDirty;


    if (bIsDirty)
    {
        FAT_FATStructureWrite(u8fsid);
    }

    if(fastOpen)
    {

        pFATInode->bIsClusterChainActive = FALSE;
    }
    else
    {
        if(pTempFileEntry->FileLength.Lo)
        {
            if(!FAT_FileClusterChainFetch(u8FileHandleNo))
            {
                __ASSERT(0);
            }
        }
    }
    return TRUE;
}

BOOLEAN FAT_FileClose(U8 u8FileHandleNo)
{
#if FILE_SYSTEM_WRITE_ENABLE
    FAT_FileSysStruct *pFsStruct;
    U8 u8FATType;
#endif
    FAT_FileHandle *pFileHandle;
    U8 u8OpenMode;
    U8 u8fsid;
    pFileHandle = FAT_File_GetHandleInfo(u8FileHandleNo);

    u8OpenMode = pFileHandle->u8OpenMode;
    u8fsid = pFileHandle->pub_fileheader.FileSystemID;

#if FILE_SYSTEM_WRITE_ENABLE

    pFsStruct = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);

    u8FATType = pFsStruct->stFAT.u8FATType;

    if( (u8OpenMode!=OPEN_MODE_FOR_READ) &&
        (u8OpenMode!=OPEN_MODE_BINARY_FOR_READ) &&
        (u8OpenMode!=OPEN_MODE_FAST_FOR_READ) )
    {
        if(!FAT_DirEntryUpdate(u8FileHandleNo))
        {
            __ASSERT(0);

        }
    }

    if(u8FATType == FAT_TYPE_FAT32)
    {
        FATDBG(printf("FAT_FileClose() : FAT_FATFsinfoUpdate() \n"););
        if( (u8OpenMode!=OPEN_MODE_FOR_READ) &&
            (u8OpenMode!=OPEN_MODE_BINARY_FOR_READ) &&
            (u8OpenMode!=OPEN_MODE_FAST_FOR_READ) )
        {
            if(!FAT_FATFsinfoUpdate(u8fsid))
            {
                __ASSERT(0);
                return FALSE;
            }
        }
    }
#endif
    msAPI_FCtrl_FileHandleFree(u8FileHandleNo);

    return TRUE;
}

U32 FAT_FATTableUpdate(U8 u8fsid, U32 clusterNo, U32 u32ClusterNeeded);

static U32 FAT_GetNextCluster(FAT_FileHandle * pstFAT_FileHandle, U8 u8BPB_SecPerClus,
                                                                  U16 u16BytePerSec,  U8 u8FATType, U32 u32FATTotalClusterNo, U32 u32AppendLength)
{
    FAT_FileInode  *pFATInode = NULL;
    U32 u32FileTotalSize = 0;
    U32 u32StartClusterNO = 0;
    BOOLEAN bIsClusterChainActive = FALSE;
    U32 u32ClusterNeeded = 0;
    U8 merge2Previous = 0;
    U32 u32BytePerClus = (U32)u16BytePerSec*u8BPB_SecPerClus;
    File_ClusterChain *pClusterChain = NULL;

    pFATInode = (FAT_FileInode*)FCtrl_GetFileInodeInfo(pstFAT_FileHandle->pub_fileheader.InodeID);
    if(pFATInode == NULL)
    {
           __ASSERT(0);
           return FAT_CLUSTER_FINAL;
    }
   u32FileTotalSize = pFATInode->u32FileTotalSize;
   bIsClusterChainActive = pFATInode->bIsClusterChainActive;
   u32StartClusterNO = pFATInode->u32FileStartClusterNo;
    pClusterChain=FAT_File_GetHandleClusterChainInfo(pstFAT_FileHandle->pub_fileheader.InodeID);

    if(u32StartClusterNO == 0)
    {
         __ASSERT(pstFAT_FileHandle->u32FileCurrentClusterNo == 0);
         goto ALLOCATE_NEW;
    }
    __ASSERT(pstFAT_FileHandle->u32FileCurrentSectorNo == u8BPB_SecPerClus);

    if(bIsClusterChainActive)
    {
          U16 currentClusterChainIndex=pstFAT_FileHandle->u16ClusterChainIndex;
          U32 u32ClusterLength;



          u32StartClusterNO = pClusterChain[currentClusterChainIndex].u32ClusterChainStart;
          u32ClusterLength = pClusterChain[currentClusterChainIndex].u32ClusterChainLength;

          __ASSERT(pstFAT_FileHandle->u32FileCurrentClusterNo>=u32StartClusterNO
             && pstFAT_FileHandle->u32FileCurrentClusterNo<u32StartClusterNO+u32ClusterLength);

           if(pstFAT_FileHandle->u32FileCurrentClusterNo + 1 == u32StartClusterNO +  u32ClusterLength)
           {
                 U32 clusterStartNo;

                 currentClusterChainIndex++;
                 clusterStartNo=pClusterChain[currentClusterChainIndex].u32ClusterChainStart;

                 if(FAT_FATGetClusterStatus( u8FATType, u32FATTotalClusterNo, clusterStartNo) != FAT_CLUSTER_ALLOCATED)
                            goto ALLOCATE_NEW;

                 pstFAT_FileHandle->u32FileCurrentClusterNo = clusterStartNo;
                 pstFAT_FileHandle->u16ClusterChainIndex=currentClusterChainIndex;
                 pstFAT_FileHandle->u32FileCurrentSectorNo = 0;

                 return FAT_CLUSTER_ALLOCATED;
             }
             else
             {
                        pstFAT_FileHandle->u32FileCurrentClusterNo++;
                        pstFAT_FileHandle->u32FileCurrentSectorNo = 0;
                        return FAT_CLUSTER_ALLOCATED;
              }
    }
    else
    {
         u32StartClusterNO = FAT_FATStructureGetNextCluster( pstFAT_FileHandle->pub_fileheader.FileSystemID, pstFAT_FileHandle->u32FileCurrentClusterNo);
         if(FAT_FATGetClusterStatus( u8FATType, u32FATTotalClusterNo, u32StartClusterNO ) != FAT_CLUSTER_ALLOCATED)
              goto ALLOCATE_NEW;
         pstFAT_FileHandle->u32FileCurrentClusterNo = u32StartClusterNO;
         pstFAT_FileHandle->u32FileCurrentSectorNo = 0;
         return FAT_CLUSTER_ALLOCATED;
    }

 ALLOCATE_NEW:
    //for file read
    if(u32AppendLength == 0)
    {
          return FAT_CLUSTER_FINAL;
    }

#if (FILE_SYSTEM_WRITE_ENABLE)
    u32ClusterNeeded = (u32AppendLength+u32BytePerClus-1)/u32BytePerClus;
   // printf(" pstFAT_FileHandle->u32FileCurrentClusterNo = %ld\n",  lstClusterNo);
   //printf("FAT_FATTableUpdate in nextcluster %08x\n", pstFAT_FileHandle->u32FileCurrentClusterNo);
    if((u32StartClusterNO=FAT_FATTableUpdate(pstFAT_FileHandle->pub_fileheader.FileSystemID, pstFAT_FileHandle->u32FileCurrentClusterNo, u32ClusterNeeded)) == 0)
    {
             __ASSERT(0);
            return FAT_CLUSTER_FINAL;
    }
   pFATInode =  (FAT_FileInode*)FCtrl_GetFileInodeInfo(pstFAT_FileHandle->pub_fileheader.InodeID);
   if(pFATInode == NULL)
   {
           __ASSERT(0);
          return FAT_CLUSTER_FINAL;
   }
   if(pFATInode->u32FileStartClusterNo == 0)
   {
      pFATInode->u32FileStartClusterNo = u32StartClusterNO;
      memcpy( (U8*)&(pFATInode->pub_inodeheader.stFileEntry.EntryID), (U8*)&u32StartClusterNO, 4 );
   }

   if(FAT_FILE_AppendClusterChain( pstFAT_FileHandle->pub_fileheader.FileSystemID, pstFAT_FileHandle->pub_fileheader.HandleID, u32StartClusterNO,
                                            pstFAT_FileHandle->u32FileCurrentClusterNo?(pstFAT_FileHandle->u16ClusterChainIndex+1):0, u8FATType, &merge2Previous)==FALSE)
   {
             __ASSERT(0);
             return FAT_CLUSTER_FINAL;
   }
   if(pstFAT_FileHandle->u32FileCurrentClusterNo == 0)
   {
       pstFAT_FileHandle->u16ClusterChainIndex = 0;
   }
   else if(!merge2Previous)
   {
        pstFAT_FileHandle->u16ClusterChainIndex++;
   }
   pstFAT_FileHandle->u32FileCurrentClusterNo = u32StartClusterNO;
   pstFAT_FileHandle->u32FileCurrentSectorNo = 0;
#else
    UNUSED(u32BytePerClus);
    UNUSED(merge2Previous);
    UNUSED(u32ClusterNeeded);
#endif
   return FAT_CLUSTER_ALLOCATED;

}
static U32 FAT_GetRemainSectors(FAT_FileHandle * pstFAT_FileHandle, U8 u8BPB_SecPerClus)
{
    FAT_FileInode  *pFATInode;
    BOOLEAN bIsClusterChainActive;
    U32 u32RemainSectors;

    pFATInode = (FAT_FileInode*)FCtrl_GetFileInodeInfo(pstFAT_FileHandle->pub_fileheader.InodeID);
    if(pFATInode == NULL)
    {
           __ASSERT(0);
           return FAT_CLUSTER_FINAL;
    }
   bIsClusterChainActive = pFATInode->bIsClusterChainActive;

    __ASSERT(pstFAT_FileHandle->u32FileCurrentClusterNo != 0);
    __ASSERT(pstFAT_FileHandle->u32FileCurrentSectorNo < u8BPB_SecPerClus);

    if(bIsClusterChainActive)
    {
          U16 currentClusterChainIndex=pstFAT_FileHandle->u16ClusterChainIndex;
          File_ClusterChain *pClusterChain;
          U32 u32ClusterLength;
          U32 u32StartClusterNO;


          pClusterChain=FAT_File_GetHandleClusterChainInfo(pstFAT_FileHandle->pub_fileheader.InodeID);
          u32StartClusterNO = pClusterChain[currentClusterChainIndex].u32ClusterChainStart;
          u32ClusterLength = pClusterChain[currentClusterChainIndex].u32ClusterChainLength;

          __ASSERT(pstFAT_FileHandle->u32FileCurrentClusterNo>=u32StartClusterNO
             && pstFAT_FileHandle->u32FileCurrentClusterNo<u32StartClusterNO+u32ClusterLength);

          u32RemainSectors = u8BPB_SecPerClus-pstFAT_FileHandle->u32FileCurrentSectorNo+
             (u32StartClusterNO +  u32ClusterLength-1-pstFAT_FileHandle->u32FileCurrentClusterNo)*u8BPB_SecPerClus;

          return u32RemainSectors;
    }
    else
    {
             u32RemainSectors = u8BPB_SecPerClus-pstFAT_FileHandle->u32FileCurrentSectorNo;
             return u32RemainSectors;
    }
}

static void FAT_StepSectors( FAT_FileHandle * pstFAT_FileHandle, U32 stepSectors, U8 u8BPB_SecPerClus)
{
    FAT_FileInode  *pFATInode;
    BOOLEAN bIsClusterChainActive;

    pFATInode = (FAT_FileInode*)FCtrl_GetFileInodeInfo(pstFAT_FileHandle->pub_fileheader.InodeID);
    //if(!pFATInode)
    //{
    //       __ASSERT(0);
    //}
   bIsClusterChainActive = pFATInode->bIsClusterChainActive;

    __ASSERT(pstFAT_FileHandle->u32FileCurrentClusterNo != 0);
    __ASSERT(pstFAT_FileHandle->u32FileCurrentSectorNo < u8BPB_SecPerClus);

    if(bIsClusterChainActive)
    {
          U16 currentClusterChainIndex=pstFAT_FileHandle->u16ClusterChainIndex;
          File_ClusterChain *pClusterChain;
          U32 u32ClusterLength;
          U32 u32StartClusterNO;


          pClusterChain=FAT_File_GetHandleClusterChainInfo(pstFAT_FileHandle->pub_fileheader.InodeID);
          u32StartClusterNO = pClusterChain[currentClusterChainIndex].u32ClusterChainStart;
          u32ClusterLength = pClusterChain[currentClusterChainIndex].u32ClusterChainLength;
          __ASSERT(pstFAT_FileHandle->u32FileCurrentClusterNo>=u32StartClusterNO
             && pstFAT_FileHandle->u32FileCurrentClusterNo<u32StartClusterNO+u32ClusterLength);

          pstFAT_FileHandle->u32FileCurrentClusterNo += (pstFAT_FileHandle->u32FileCurrentSectorNo+stepSectors)/u8BPB_SecPerClus;
          pstFAT_FileHandle->u32FileCurrentSectorNo = (pstFAT_FileHandle->u32FileCurrentSectorNo+stepSectors)%u8BPB_SecPerClus;
          __ASSERT(pstFAT_FileHandle->u32FileCurrentClusterNo <= u32StartClusterNO+u32ClusterLength);
          if(pstFAT_FileHandle->u32FileCurrentClusterNo == u32StartClusterNO+u32ClusterLength)
          {
               pstFAT_FileHandle->u32FileCurrentClusterNo--;
               pstFAT_FileHandle->u32FileCurrentSectorNo = u8BPB_SecPerClus;
          }
    }
    else
    {
           pstFAT_FileHandle->u32FileCurrentSectorNo += stepSectors;
           __ASSERT( pstFAT_FileHandle->u32FileCurrentSectorNo <= u8BPB_SecPerClus);
    }

}

U32 FAT_FileRead(U8 u8FileHandleNo, U32 u32DesBufAdr, U32 u32ReadByteLength)
{

    //*Note: file read unit=> sector*//
    FAT_FileHandle * pstFAT_FileHandle;
    FAT_FileSysStruct *pFsStruct;
    U32 u32ProcessByteLength;
    U32 u32ReadSectorCnt, u32ReadByteCnt;
    U32 u32StartSector;
    U32 u32OriginalReadByte = u32ReadByteLength;
    U16 u16BytePerSec;
    U32 u32RemainSectorNum;
    U8 u8FATType;
    U32 u32FATTotalClusterNo;
    U32 u32FileTotalSize;
    U8 u8BPB_SecPerClus;
    U8 u8DeviceIndex;
    FAT_FileInode *pFATInode;
    BOOLEAN bIsClusterChainActive;
    U32 u32StartClusterNo;

    pstFAT_FileHandle = FAT_File_GetHandleInfo(u8FileHandleNo);

    // get FAT file system
    pFsStruct = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(pstFAT_FileHandle->pub_fileheader.FileSystemID);
    u16BytePerSec = pFsStruct->stBootSector.BPB_BytsPerSec;
    u8FATType = pFsStruct->stFAT.u8FATType;
    u32FATTotalClusterNo = pFsStruct->stFAT.u32FATTotalClusterNo;
    u8BPB_SecPerClus = pFsStruct->stBootSector.BPB_SecPerClus;
    u8DeviceIndex = pFsStruct->DeviceIndex;

   pFATInode = FAT_File_GetInodeFromHandle(u8FileHandleNo);
   if(pFATInode == NULL)
   {
           __ASSERT(0);
           return u32OriginalReadByte;
   }
   u32FileTotalSize = pFATInode->u32FileTotalSize;
   bIsClusterChainActive = pFATInode->bIsClusterChainActive;
   u32StartClusterNo = pFATInode->u32FileStartClusterNo;

   if(pstFAT_FileHandle->u32FileCurrentClusterNo == 0)
    {
        pstFAT_FileHandle->u32FileCurrentClusterNo = u32StartClusterNo;
        pstFAT_FileHandle->u16ClusterChainIndex = 0;
    }

    // check file position
    if ( ( pstFAT_FileHandle->u32FilePosition ) >= u32FileTotalSize )
    {
        return u32OriginalReadByte;
    }

   if((pstFAT_FileHandle->u32FileCurrentClusterNo==0 ||pstFAT_FileHandle->u32FileCurrentSectorNo==u8BPB_SecPerClus)  &&
           FAT_CLUSTER_ALLOCATED != FAT_GetNextCluster(pstFAT_FileHandle, u8BPB_SecPerClus,
                                                                  u16BytePerSec,  u8FATType, u32FATTotalClusterNo, 0))
   {
           __ASSERT(0);
           return u32OriginalReadByte;
   }

    if(u32ReadByteLength + pstFAT_FileHandle->u32FilePosition > u32FileTotalSize)
    {
        u32ReadByteLength = u32FileTotalSize - pstFAT_FileHandle->u32FilePosition;
    }

    // read current sector of current cluster
    u32ProcessByteLength = 0;

    //read head sector
    u32ReadByteCnt = pstFAT_FileHandle->u32FilePosition % u16BytePerSec;
    if(u32ReadByteCnt)
    {
        u32ReadByteCnt = u16BytePerSec - u32ReadByteCnt;
        if(u32ReadByteCnt > u32ReadByteLength)
        {
            u32ReadByteCnt = u32ReadByteLength;
        }
        u32StartSector = FAT_FATGetSectorNo( pstFAT_FileHandle->pub_fileheader.FileSystemID, pstFAT_FileHandle->u32FileCurrentClusterNo ) + pstFAT_FileHandle->u32FileCurrentSectorNo;
        //sector read
        if ( !msAPI_MSDCtrl_SectorRead( u8DeviceIndex,
            u32StartSector, 1, USB_IO_TEMP_ADDR))
        {
            __ASSERT(0);
            return (u32OriginalReadByte - u32ProcessByteLength);
        }
        msAPI_FS_MIU_Copy (USB_IO_TEMP_ADDR + pstFAT_FileHandle->u32FilePosition % u16BytePerSec, u32DesBufAdr, u32ReadByteCnt);
        u32ProcessByteLength = u32ReadByteCnt;
        pstFAT_FileHandle->u32FilePosition += u32ReadByteCnt;

        if(pstFAT_FileHandle->u32FilePosition % u16BytePerSec == 0)
             pstFAT_FileHandle->u32FileCurrentSectorNo++;
        //get next sector
        if(u32ProcessByteLength < u32ReadByteLength ||
           (pstFAT_FileHandle->u32FilePosition % u16BytePerSec == 0 &&
           pstFAT_FileHandle->u32FilePosition < u32FileTotalSize)
           )
        {
            if ( pstFAT_FileHandle->u32FileCurrentSectorNo == u8BPB_SecPerClus )
            {
                if(FAT_CLUSTER_ALLOCATED != FAT_GetNextCluster(pstFAT_FileHandle, u8BPB_SecPerClus,
                                                                  u16BytePerSec,  u8FATType, u32FATTotalClusterNo, 0))
               {
                      __ASSERT(0);
                      return (u32OriginalReadByte - u32ProcessByteLength);
               }
            }
        }
    }

    //read remain data
    while(u32ProcessByteLength  + u16BytePerSec <= u32ReadByteLength )
    {
        u32StartSector = FAT_FATGetSectorNo( pstFAT_FileHandle->pub_fileheader.FileSystemID, pstFAT_FileHandle->u32FileCurrentClusterNo ) + pstFAT_FileHandle->u32FileCurrentSectorNo;
         u32RemainSectorNum = FAT_GetRemainSectors(pstFAT_FileHandle, u8BPB_SecPerClus);
        __ASSERT(u32RemainSectorNum);

        u32ReadByteCnt = u32ReadByteLength - u32ProcessByteLength;
        if((unsigned long long)u32ReadByteCnt < (unsigned long long)u32RemainSectorNum * u16BytePerSec)
        {
            u32ReadSectorCnt = u32ReadByteCnt/u16BytePerSec;
            u32ReadByteCnt = u32ReadSectorCnt * u16BytePerSec;
        }
        else
        {
            u32ReadByteCnt = u32RemainSectorNum * u16BytePerSec;
            u32ReadSectorCnt = u32RemainSectorNum;
        }

        //sector read
        if ( !msAPI_MSDCtrl_SectorRead( u8DeviceIndex,
            u32StartSector, u32ReadSectorCnt, u32DesBufAdr + u32ProcessByteLength))
        {
            __ASSERT(0);
            pstFAT_FileHandle->u32FilePosition += u32ReadByteCnt;
            return (u32OriginalReadByte - u32ProcessByteLength);
        }

        u32ProcessByteLength += u32ReadByteCnt;
        pstFAT_FileHandle->u32FilePosition += u32ReadByteCnt;
        //printf("step %ld , %ld\n", u32ReadSectorCnt,  pstFAT_FileHandle->u32FileCurrentSectorNo);
        FAT_StepSectors(pstFAT_FileHandle, u32ReadSectorCnt, u8BPB_SecPerClus);

       if ( pstFAT_FileHandle->u32FileCurrentSectorNo==u8BPB_SecPerClus&&u32ReadByteLength-u32ProcessByteLength)
        {

                if(FAT_CLUSTER_ALLOCATED != FAT_GetNextCluster(pstFAT_FileHandle, u8BPB_SecPerClus,
                                                                  u16BytePerSec,  u8FATType, u32FATTotalClusterNo, 0))
               {
                      __ASSERT(0);
                      return (u32OriginalReadByte - u32ProcessByteLength);
               }
        }
    }

    //read tail sector
    if(u32ProcessByteLength < u32ReadByteLength)
    {
        u32StartSector = FAT_FATGetSectorNo( pstFAT_FileHandle->pub_fileheader.FileSystemID, pstFAT_FileHandle->u32FileCurrentClusterNo ) + pstFAT_FileHandle->u32FileCurrentSectorNo;
        u32ReadByteCnt = u32ReadByteLength - u32ProcessByteLength;

        //sector read
        if ( !msAPI_MSDCtrl_SectorRead( u8DeviceIndex,
            u32StartSector, 1, USB_IO_TEMP_ADDR))
        {
            __ASSERT(0);
            return (u32OriginalReadByte - u32ProcessByteLength);
        }
        msAPI_FS_MIU_Copy (USB_IO_TEMP_ADDR, u32DesBufAdr + u32ProcessByteLength, u32ReadByteCnt);
        u32ProcessByteLength += u32ReadByteCnt;
        pstFAT_FileHandle->u32FilePosition += u32ReadByteCnt;
    }

    return u32OriginalReadByte - u32ProcessByteLength;
}


BOOLEAN FAT_FileSeekWithoutClusterChain(U8 u8FileHandleNo, U32 u32Position, EN_FILE_SEEK_OPTION eOption)
{
    FAT_FileHandle * pstFAT_FileHandle;
    FAT_FileSysStruct *pFAT_FileSys;
    U32 u32SecPerClusByteLen;
    U8 u8fsid;
    U8 u8BPB_SecPerClus, u8FATType;
    U32 u32FATTotalClusterNo;
    U16 u16BytePerSec;
    FAT_FileInode *pFATInode;
    U32 u32FileStartClusterNo;

    pstFAT_FileHandle = FAT_File_GetHandleInfo(u8FileHandleNo);
    u8fsid = pstFAT_FileHandle->pub_fileheader.FileSystemID;

    //Triky!! It is OK due to the FileHandle XdataWindow is different from FileSystem XDataWindow
    pFAT_FileSys = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);
    u8BPB_SecPerClus = pFAT_FileSys->stBootSector.BPB_SecPerClus;
    u8FATType = pFAT_FileSys->stFAT.u8FATType;
    u32FATTotalClusterNo = pFAT_FileSys->stFAT.u32FATTotalClusterNo;
    u16BytePerSec = pFAT_FileSys->stBootSector.BPB_BytsPerSec;

   pFATInode = FAT_File_GetInodeFromHandle(u8FileHandleNo);
   if(pFATInode == NULL)
   {
           __ASSERT(0);
           return FALSE;
   }
   u32FileStartClusterNo = pFATInode->u32FileStartClusterNo;

    u32SecPerClusByteLen = (U32)u8BPB_SecPerClus * u16BytePerSec;

    if ( eOption == FILE_SEEK_SET || pstFAT_FileHandle->u32FileCurrentClusterNo==0)
    {
        pstFAT_FileHandle->u32FileCurrentClusterNo = u32FileStartClusterNo;
        pstFAT_FileHandle->u32FileCurrentSectorNo =0;
        pstFAT_FileHandle->u32FilePosition = 0;
    }
    if(pstFAT_FileHandle->u32FileCurrentClusterNo == 0)
    {
        if(FILE_SEEK_SET==eOption  && u32Position==0)
            return TRUE;
        return FALSE;
    }

    // seek until meet position
    while ( TRUE )
    {
        U32 remainByteInClus = u32SecPerClusByteLen-(pstFAT_FileHandle->u32FilePosition%u32SecPerClusByteLen);
        U32 nextCluster;

        __ASSERT(FAT_FATGetClusterStatus( u8FATType, u32FATTotalClusterNo, pstFAT_FileHandle->u32FileCurrentClusterNo ) == FAT_CLUSTER_ALLOCATED);

        if(u32Position < remainByteInClus)
              remainByteInClus = u32Position;
        u32Position -= remainByteInClus;
        pstFAT_FileHandle->u32FilePosition += remainByteInClus;

        if(u32Position)
        {
              __ASSERT((pstFAT_FileHandle->u32FilePosition%u32SecPerClusByteLen) == 0);
              nextCluster = FAT_FATStructureGetNextCluster(u8fsid ,pstFAT_FileHandle->u32FileCurrentClusterNo );
              if (FAT_FATGetClusterStatus( u8FATType, u32FATTotalClusterNo, nextCluster) != FAT_CLUSTER_ALLOCATED )
              {
                   __ASSERT(0);
		    pstFAT_FileHandle->u32FileCurrentSectorNo = u8BPB_SecPerClus;
                  return FALSE;
              }
              pstFAT_FileHandle->u32FileCurrentClusterNo = nextCluster;
              pstFAT_FileHandle->u32FileCurrentSectorNo = 0;
        }
        else
        {
              pstFAT_FileHandle->u32FileCurrentSectorNo = (pstFAT_FileHandle->u32FilePosition%u32SecPerClusByteLen)/u16BytePerSec;
              return TRUE;
        }
    }
}

BOOLEAN FAT_FileSeek(U8 u8FileHandleNo, U32 u32Length, EN_FILE_SEEK_OPTION eOption)
{
    FAT_FileHandle * pFileHandle;
    FAT_FileSysStruct *pFAT_FileSys;
    File_ClusterChain* pClusterChain;
    U32 u32BytePerClus;
    U32 u32CurrPosition;
    U16 u16Index;
    U32 u32ClusterCount = 0;
    BOOLEAN bResult = FALSE;
    U16 u16BytePerSec;
    U32 u32TempLength;
    U32 u32TempStart;
    BOOLEAN bIsClusterChainActive;
    FAT_FileInode *pFATInode;
    U32 u32FileTotalSize;
    U8 BPB_SecPerClus;

    pFileHandle = FAT_File_GetHandleInfo(u8FileHandleNo);
    u32CurrPosition = pFileHandle->u32FilePosition;

    //triky!! It is OK due to the FileSystem XataWindow is different from  FileHandle XDataWindow
    pFAT_FileSys = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(pFileHandle->pub_fileheader.FileSystemID);
    u16BytePerSec = pFAT_FileSys->stBootSector.BPB_BytsPerSec;
    u32BytePerClus = (U32)pFAT_FileSys->stBootSector.BPB_SecPerClus * u16BytePerSec;
    BPB_SecPerClus = pFAT_FileSys->stBootSector.BPB_SecPerClus;

   pFATInode = FAT_File_GetInodeFromHandle(u8FileHandleNo);
   if(pFATInode == NULL)
   {
           __ASSERT(0);
           return FALSE;
   }
   bIsClusterChainActive = pFATInode->bIsClusterChainActive;
   u32FileTotalSize = pFATInode->u32FileTotalSize;


    if(bIsClusterChainActive)
    {

        //calculate set position
        if(eOption == FILE_SEEK_SET)
        {
            u32CurrPosition = 0;
        }

        if(u32Length > (u32FileTotalSize-u32CurrPosition))
        {
           u32Length = (u32FileTotalSize-u32CurrPosition);
        }

        u32CurrPosition+=u32Length;

        pClusterChain=FAT_File_GetHandleClusterChainInfo(pFileHandle->pub_fileheader.InodeID);

        for(u16Index = 0; u16Index < CLUSTER_CHAIN_SIZE; u16Index++)
        {
            u32TempLength=pClusterChain[u16Index].u32ClusterChainLength;
            u32TempStart=pClusterChain[u16Index].u32ClusterChainStart;

            if(u32TempLength== 0)
            {
               if(u16Index && (unsigned long long)u32CurrPosition == (unsigned long long)u32ClusterCount * u32BytePerClus)
               {
                           u32TempLength=pClusterChain[u16Index-1].u32ClusterChainLength;
                           u32TempStart=pClusterChain[u16Index-1].u32ClusterChainStart;

                            pFileHandle->u32FileCurrentClusterNo = u32TempStart+u32TempLength-1;
                            pFileHandle->u32FileCurrentSectorNo = BPB_SecPerClus;
                            pFileHandle->u32FilePosition = u32CurrPosition;
                            pFileHandle->u16ClusterChainIndex = u16Index-1;
                            bResult = TRUE;
               }
                else
                {
                    __ASSERT(0);
                }

                //can't find !!??
                break;
            }
            u32ClusterCount += u32TempLength;
            if((unsigned long long)u32CurrPosition < (unsigned long long)u32ClusterCount * u32BytePerClus)
            {
                //found!
                pFileHandle->u32FilePosition = u32CurrPosition;
                u32ClusterCount = u32ClusterCount - u32TempLength;
                u32CurrPosition = u32CurrPosition - u32ClusterCount * u32BytePerClus;
                pFileHandle->u32FileCurrentClusterNo = u32CurrPosition / u32BytePerClus + u32TempStart;
                pFileHandle->u32FileCurrentSectorNo = (u32CurrPosition % u32BytePerClus) / u16BytePerSec;
                pFileHandle->u16ClusterChainIndex = u16Index;
                bResult = TRUE;
                break;
            }
        }

    }
    else
    {

        bResult = FAT_FileSeekWithoutClusterChain(u8FileHandleNo, u32Length, eOption);
    }
    return bResult;
}

#if FILE_SYSTEM_FILE_TELL_ENABLE
U32 FAT_FileTell(U8 handleId)
{
    U32 val=0;

    FAT_FileHandle* pHandle;

    if(handleId==INVALID_FILE_HANDLE)
        return 0xFFFFFFFF;

    pHandle = FAT_File_GetHandleInfo(handleId);
    val=pHandle->u32FilePosition;

    return val;

}
#endif



U8 FAT_EntryGetCurrentNameToMIU(U8 enid,U32 destMIUAddr,U8 charLen)
{
    U8 fileNameLen=0;
    U16* pu16String;
    U8 i;

    if(charLen==0)
        return 0;

    pu16String=(U16*)(void *)((U8*)FAT_GetAddr(enid, FAT_XDATA_OPTION_FAT_CURRENT_INFO)+(U32)FAT_CURRENT_INFO_ENTRY_NAME_offset);

     for(i=0;i<255;i++)
    {
        if( *(pu16String++)==0)
            break;
    }
    fileNameLen=(i>charLen)?charLen:i;

    msAPI_FS_MIU_Copy( FAT_GetMIUAddress(enid, FAT_XDATA_OPTION_FAT_CURRENT_INFO)+FAT_CURRENT_INFO_ENTRY_NAME_offset, destMIUAddr,(U32)charLen*2UL);

    return fileNameLen;

}


#if (!FILE_SYSTEM_SMALL)

void FAT_EntrySetCurrentNameShortOnly(U8 enid,BOOLEAN shortOnly)
{
    *((BOOLEAN*)FAT_GetAddr(enid, FAT_XDATA_OPTION_FAT_CURRENT_INFO)+(U32)FAT_CURRENT_INFO_ENTRY_NAME_SHORT_ONLY_offset)=shortOnly;
}

BOOLEAN FAT_EntryIsCurrentNameShortOnly(U8 enid)
{
    BOOLEAN result;

    result=*((BOOLEAN*)FAT_GetAddr(enid, FAT_XDATA_OPTION_FAT_CURRENT_INFO)+(U32)FAT_CURRENT_INFO_ENTRY_NAME_SHORT_ONLY_offset);

    return result;
}

U32 FAT_DirectoryGetParentClusterNo(U8 u8EnvironmentID)
{
     FAT_Environment * pstFAT_Env;
     U32 u32ReturnParentClusterNo;

     pstFAT_Env = (FAT_Environment *)FAT_GetAddr(u8EnvironmentID, FAT_XDATA_OPTION_ENVIRONMENT);

     u32ReturnParentClusterNo = pstFAT_Env->stCurrentDirectory.u32ParentDirStartClusterNo;

     return u32ReturnParentClusterNo;
}

#if 0
static BOOLEAN FAT_FATFsinfoUpdate(FileEntry *pTempFileEntry, U32 u32deletedClusterCount)
{
    FS_EnvironmentStruct *pFS_Env;
    FAT_FileSysStruct *pFsStruct;
    U32 u32FSI_Free_Count, u32FSI_Nxt_Free;
    U8 *pu8FSInfo;
    U16 u16BytePerSec;
    U8 u8DeviceIndex;
    U32 u32StartSector;

    //*get FAT_Env info================================================//
    pFS_Env = msAPI_FSEnv_GetEnvironment(pTempFileEntry->EnvironmentID);

    //*get FAT file sys================================================//
    pFsStruct = (FAT_FileSysStruct*)FCtrl_GetFileSystemXData(pFS_Env->u8FileSystemID);
    u16BytePerSec=pFsStruct->stBootSector.BPB_BytsPerSec;
    u8DeviceIndex = pFsStruct ->DeviceIndex;
    u32StartSector = pFsStruct->stBootSector.BPB_FSInfo + pFsStruct->u32RelativeSector;
    FAT_ReturnXData();



    //*update FSINFO_SECTOR of FILE_ENVIRONMENT_POOL========================//
    pu8FSInfo = (U8*)FAT_GetXData(pTempFileEntry->EnvironmentID, FAT_XDATA_OPTION_FSINFO_SECTOR);

    memcpy( (U8*)&u32FSI_Free_Count, pu8FSInfo + 488, 4 );
    u32FSI_Free_Count += u32deletedClusterCount;
    memcpy(pu8FSInfo + 488, (U8*)&u32FSI_Free_Count, 4);

    memcpy( (U8*)&u32FSI_Free_Count, pu8FSInfo + 492, 4 );
    u32FSI_Nxt_Free = *(U32*)pTempFileEntry->EntryID;
    memcpy(pu8FSInfo + 492, (U8*)&u32FSI_Nxt_Free, 4);
    FAT_ReturnXData();

    //*update disk==================================================//
    msAPI_FS_MIU_Copy( (U32)FAT_GetXDataMIUAddress(pTempFileEntry->EnvironmentID, FAT_XDATA_OPTION_FSINFO_SECTOR), USB_IO_TEMP_ADDR, (U32)FAT_FSINFO_SECTOR_SIZE * u16BytePerSec );

    if ( !msAPI_MSDCtrl_SectorWrite( u8DeviceIndex, u32StartSector, FAT_FSINFO_SECTOR_SIZE, USB_IO_TEMP_ADDR ) )
    {
        __ASSERT(0);
        return FALSE;
    }
    else
    {
        return TRUE;
    }

}
#endif

static BOOLEAN FAT_FATFsinfoUpdate_Increase(FileEntry *pTempFileEntry, U32 u32deletedClusterCount)
{
    FAT_FileSysStruct *pFsStruct;
    U16 u16BytePerSec;
    U8 u8DeviceIndex;
    U32 u32StartSector;
    U8 *pu8RwDataCache;
    U32 u32FSI_Free_Count;
    U32 u32FSI_Nxt_Free;

    // get FAT file system
    pFsStruct=(FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(pTempFileEntry->FileSystemID);

    u16BytePerSec=pFsStruct->stBootSector.BPB_BytsPerSec;
    u8DeviceIndex=pFsStruct ->DeviceIndex;
    u32StartSector=pFsStruct->stBootSector.BPB_FSInfo + pFsStruct->u32RelativeSector;
    pFsStruct->u32FSI_Free_Count += u32deletedClusterCount;
    //pFsStruct->u32FSI_Nxt_Free = *(U32*)pTempFileEntry->EntryID;
    memcpy(&(pFsStruct->u32FSI_Nxt_Free),pTempFileEntry->EntryID,4);
    u32FSI_Free_Count = pFsStruct->u32FSI_Free_Count;
    u32FSI_Nxt_Free = pFsStruct->u32FSI_Nxt_Free;

    if ( !msAPI_MSDCtrl_SectorRead( u8DeviceIndex, u32StartSector, 1, USB_IO_TEMP_ADDR))
    {
        __ASSERT(0);
        return FALSE;
    }

    pu8RwDataCache = (U8 xdata*)msAPI_FS_GetAddr(USB_IO_TEMP_ADDR);

    FATDBG(printf("FAT_FATFsinfoUpdate_Increase() : Free Count = %lx\n",u32FSI_Free_Count););
    memcpy((pu8RwDataCache+488), (U8 *)&(u32FSI_Free_Count), 4);
    memcpy((pu8RwDataCache+492), (U8 *)&(u32FSI_Nxt_Free), 4);

    //*update disk==================================================//
    if ( !msAPI_MSDCtrl_SectorWrite( u8DeviceIndex, u32StartSector, FAT_FSINFO_SECTOR_SIZE, USB_IO_TEMP_ADDR ) )
    {
        __ASSERT(0);
        return FALSE;
    }
    else
    {
        return TRUE;
    }

}

#if FILE_SYSTEM_WRITE_ENABLE
static BOOLEAN FAT_FATFsinfoUpdate(U8 fsid)
{
    FAT_FileSysStruct *pFsStruct;
    U16 u16BytePerSec;
    U8 u8DeviceIndex;
    U32 u32StartSector;
    U8 *pu8RwDataCache;
    U32 u32FSI_Free_Count;
    U32 u32FSI_Nxt_Free;

    // get FAT file system
    pFsStruct=(FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(fsid);

    u16BytePerSec=pFsStruct->stBootSector.BPB_BytsPerSec;
    u8DeviceIndex=pFsStruct ->DeviceIndex;
    u32StartSector=pFsStruct->stBootSector.BPB_FSInfo + pFsStruct->u32RelativeSector;
    u32FSI_Free_Count = pFsStruct->u32FSI_Free_Count;
    pFsStruct->u32FSI_Nxt_Free = pFsStruct->u32CurrentFreeCluster;
    u32FSI_Nxt_Free = pFsStruct->u32FSI_Nxt_Free;

    if ( !msAPI_MSDCtrl_SectorRead( u8DeviceIndex, u32StartSector, 1, USB_IO_TEMP_ADDR))
    {
        __ASSERT(0);
        return FALSE;
    }

    pu8RwDataCache = (U8 xdata*)msAPI_FS_GetAddr(USB_IO_TEMP_ADDR);

    FATDBG(printf("FAT_FATFsinfoUpdate() : Free Count = %lx\n",u32FSI_Free_Count););
    memcpy((pu8RwDataCache+488), (U8 *)&(u32FSI_Free_Count), 4);
    memcpy((pu8RwDataCache+492), (U8 *)&(u32FSI_Nxt_Free), 4);

    //*update disk==================================================//
    if ( !msAPI_MSDCtrl_SectorWrite( u8DeviceIndex, u32StartSector, FAT_FSINFO_SECTOR_SIZE, USB_IO_TEMP_ADDR ) )
    {
        __ASSERT(0);
        return FALSE;
    }
    else
    {
        return TRUE;
    }

}
#endif


//  2008/08/04
//  Orignally we only erase the exact sector of the FileEntry. However, we
//  got a strange USB disk that would have problem. As we
//  need to consider some USB disk with cluster size more
//  than 4K, we seperate the case into less equal than 4K( RW the whole
//  cluster ) and the bigger one ( RW only the sector)
//
static BOOLEAN FAT_DirectoryFreeDirEntry(FileEntry *pDeleteFileEntry)
{

    DirEntryStruct* pDirEntryStruct;
    FAT_FileSysStruct* pstFAT_FileSys;
    U32 sectorNo;
    S32 indexOffset;//offset in current cluster of current sector
    U32 dirEntryCountPerSector;
    U32 dirEntryCountPerCluster;
    U8 deviceIndex;
    U8 guard;
    //FAT_Environment *pFAT_Env;
    U8 u8FAT_Type;
    U32 sectorsPerCluster;
    U32 _cluster;
    U32 _prevCluster;//use to memory previous cluster
    S32 _indexOffsetInDirectory;
    U32 clusterSize;
    FS_EnvironmentStruct * pFS_Env;

    pstFAT_FileSys=(FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(pDeleteFileEntry->FileSystemID);

    u8FAT_Type=pstFAT_FileSys->stFAT.u8FATType;
    sectorsPerCluster=pstFAT_FileSys->stBootSector.BPB_SecPerClus;
    dirEntryCountPerSector=( pstFAT_FileSys->stBootSector.BPB_BytsPerSec)/sizeof(DirEntryStruct);
    dirEntryCountPerCluster=dirEntryCountPerSector*sectorsPerCluster;
    clusterSize=(U32)sectorsPerCluster*pstFAT_FileSys->stBootSector.BPB_BytsPerSec;


    //FAT_Environment *pFAT_Env;
    //U32 currentDirectoryClusterNo;
    //S32 currentEntryIndex;

    pFS_Env = msAPI_FSEnv_GetEnvironment(pDeleteFileEntry->EnvironmentID);
    if(pFS_Env == NULL)
    {
		__ASSERT(0);
        return FALSE;
    }
    else
    {
        deviceIndex = pFS_Env->u8DeviceIndex;
    }

    memcpy(&_cluster,&pDeleteFileEntry->EntryID_Ext[0],sizeof(U32));
    memcpy(&_indexOffsetInDirectory,&pDeleteFileEntry->EntryID_Ext[4],sizeof(U32));

    _prevCluster=_cluster;
    indexOffset=_indexOffsetInDirectory;


    if((u8FAT_Type==FAT_TYPE_FAT32)||(_cluster!=0))
    {
        //shift to cluster
        while(indexOffset>=(S32)dirEntryCountPerCluster)
        {
            _prevCluster=_cluster;
            _cluster=FAT_FATStructureGetNextCluster(pDeleteFileEntry->FileSystemID,_cluster);
            if(_cluster == 0)
            {
                __ASSERT(0);
                return FALSE;
            }
            indexOffset -= dirEntryCountPerCluster;
        }
    }


    //shfit to sector
    sectorNo=FAT_FATGetSectorNo(pDeleteFileEntry->FileSystemID, _cluster);

    //  2008/08/04
    //  Ridiculous Patch!!
    if(((u8FAT_Type==FAT_TYPE_FAT32)||(_cluster!=0))&& clusterSize<=0x1000)
    {

        ioassert(msAPI_MSDCtrl_SectorRead(deviceIndex,sectorNo,sectorsPerCluster,USB_IO_TEMP_ADDR));

        //erase the last short entry
        pDirEntryStruct = (DirEntryStruct xdata* )msAPI_FS_GetAddr(USB_IO_TEMP_ADDR);

        if( (pDirEntryStruct[indexOffset].pu8DirEntryName[0] ==DIR_ENTRY_IS_FREE)
            ||(pDirEntryStruct[indexOffset].pu8DirEntryName[0] ==DIR_ENTRY_IS_LAST))
        {
            __ASSERT(0);
            return FALSE;
        }
        else if((pDirEntryStruct[indexOffset].u8DirEntryAttrib == FAT_ATTRIB_LONG_NAME)
            ||(pDirEntryStruct[indexOffset].u8DirEntryAttrib == FAT_ATTRIB_VOLUME_ID))
            //||(pDirEntryStruct[indexOffset].u8DirEntryAttrib & FAT_ATTRIB_DIRECTORY)==1)
        {
            __ASSERT(0);

            return FALSE;
        }

        pDirEntryStruct[indexOffset].pu8DirEntryName[0] = DIR_ENTRY_IS_FREE;

        indexOffset--;
        _indexOffsetInDirectory--;
        guard=0;//guard

        while(TRUE)
        {
            if(indexOffset<0)
            {

                //FLUSH
                ioassert(msAPI_MSDCtrl_SectorWrite(deviceIndex,sectorNo,sectorsPerCluster,USB_IO_TEMP_ADDR));

                if(_indexOffsetInDirectory<0)
                {
                    break;//reach head
                }

                sectorNo=FAT_FATGetSectorNo(pDeleteFileEntry->FileSystemID,_prevCluster); //+ (sectorsPerCluster-1);

                ioassert(msAPI_MSDCtrl_SectorRead(deviceIndex,sectorNo,sectorsPerCluster,USB_IO_TEMP_ADDR));
                indexOffset=dirEntryCountPerCluster-1;

            }
            FS_RESET_WDT();

            pDirEntryStruct = (DirEntryStruct xdata*)msAPI_FS_GetAddr(USB_IO_TEMP_ADDR);

            if(pDirEntryStruct[indexOffset].u8DirEntryAttrib==FAT_ATTRIB_LONG_NAME)
            {

                U8 firstByte=pDirEntryStruct[indexOffset].pu8DirEntryName[0];
                pDirEntryStruct[indexOffset].pu8DirEntryName[0] = DIR_ENTRY_IS_FREE;

                if((firstByte & FIRST_BYTE_OF_ENTRY_END_LONGNAME) == FIRST_BYTE_OF_ENTRY_END_LONGNAME)
                {
                    break;
                }


            }
            else
            {
                break;
            }

            indexOffset--;
            _indexOffsetInDirectory--;
            guard++;

            ioassert(guard<255);

        }

        //FLUSH one more time
        ioassert(msAPI_MSDCtrl_SectorWrite(deviceIndex,sectorNo,sectorsPerCluster,USB_IO_TEMP_ADDR));
        return TRUE;

    }
    else
    {
        S32 sectorIndexInCluster;

        sectorIndexInCluster=indexOffset/dirEntryCountPerSector;
        sectorNo+=sectorIndexInCluster;
        indexOffset=indexOffset%dirEntryCountPerSector;

        ioassert(msAPI_MSDCtrl_SectorRead(deviceIndex,sectorNo,1,USB_IO_TEMP_ADDR));



        //erase the last short entry
        pDirEntryStruct = (DirEntryStruct xdata* )msAPI_FS_GetAddr(USB_IO_TEMP_ADDR);

        if( (pDirEntryStruct[indexOffset].pu8DirEntryName[0] ==DIR_ENTRY_IS_FREE)
            ||(pDirEntryStruct[indexOffset].pu8DirEntryName[0] ==DIR_ENTRY_IS_LAST))
        {
            __ASSERT(0);
            return FALSE;
        }
        else if((pDirEntryStruct[indexOffset].u8DirEntryAttrib == FAT_ATTRIB_LONG_NAME)
            ||(pDirEntryStruct[indexOffset].u8DirEntryAttrib == FAT_ATTRIB_VOLUME_ID))
//            ||(pDirEntryStruct[indexOffset].u8DirEntryAttrib & FAT_ATTRIB_DIRECTORY)==1)
        {
            __ASSERT(0);

            return FALSE;
        }

        pDirEntryStruct[indexOffset].pu8DirEntryName[0] = DIR_ENTRY_IS_FREE;

        indexOffset--;
        _indexOffsetInDirectory--;
        guard=0;//guard

        while(TRUE)
        {
            if(indexOffset<0)
            {


                //FLUSH
                ioassert(msAPI_MSDCtrl_SectorWrite(deviceIndex,sectorNo,1,USB_IO_TEMP_ADDR));

                if(_indexOffsetInDirectory<0)
                {
                    break;//reach head
                }

                sectorNo--;
                sectorIndexInCluster--;

                //jump to previous cluster
                if(sectorIndexInCluster<0)
                {
                    sectorIndexInCluster=sectorsPerCluster-1;
                    sectorNo=FAT_FATGetSectorNo(pDeleteFileEntry->FileSystemID,_prevCluster) + sectorIndexInCluster;
                }

                ioassert(msAPI_MSDCtrl_SectorRead(deviceIndex,sectorNo,1,USB_IO_TEMP_ADDR));
                indexOffset=dirEntryCountPerSector-1;

            }
            FS_RESET_WDT();

            pDirEntryStruct = (DirEntryStruct xdata*)msAPI_FS_GetAddr(USB_IO_TEMP_ADDR);

            if(pDirEntryStruct[indexOffset].u8DirEntryAttrib==FAT_ATTRIB_LONG_NAME)
            {

                U8 firstByte=pDirEntryStruct[indexOffset].pu8DirEntryName[0];
                pDirEntryStruct[indexOffset].pu8DirEntryName[0] = DIR_ENTRY_IS_FREE;

                if((firstByte & FIRST_BYTE_OF_ENTRY_END_LONGNAME) == FIRST_BYTE_OF_ENTRY_END_LONGNAME)
                {
                    break;
                }


            }
            else
            {
                break;
            }

            indexOffset--;
            _indexOffsetInDirectory--;
            guard++;

            ioassert(guard<255);

        }

        //FLUSH one more time
        ioassert(msAPI_MSDCtrl_SectorWrite(deviceIndex,sectorNo,1,USB_IO_TEMP_ADDR));
        return TRUE;
    }



}




static BOOLEAN FAT_FATStructureFreeClusterNo( FileEntry *pTempFileEntry)
{
    FAT_FileSysStruct  *pFAT_fileSys;
    U32 u32CurrentClusterNo, u32NextClusterNo, u32NextClusterStatus, u32deletedClusterCount;
    //U8 u8FatTableEntrySize;
    U8 u8FATType;
    U32 u32FATTotalClusterNo;

    if(0 == pTempFileEntry->FileLength.Lo)
        return TRUE;

    pFAT_fileSys = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(pTempFileEntry->FileSystemID);

    u8FATType = pFAT_fileSys->stFAT.u8FATType;
    u32FATTotalClusterNo = pFAT_fileSys->stFAT.u32FATTotalClusterNo;

    //u32CurrentClusterNo = *(U32*)pTempFileEntry->EntryID;
    memcpy(&u32CurrentClusterNo,pTempFileEntry->EntryID,4);

    u32deletedClusterCount = 0;

    //*free cluster chain of deleted file ===================================================//
    while ( TRUE )
    {
            u32NextClusterNo = FAT_FATStructureGetNextCluster( pTempFileEntry->FileSystemID, u32CurrentClusterNo );
            u32NextClusterStatus = FAT_FATGetClusterStatus(u8FATType, u32FATTotalClusterNo, u32NextClusterNo );

            if(u32NextClusterNo==u32CurrentClusterNo)
            {
                __ASSERT(0);
                return FALSE;
            }

            switch ( u32NextClusterStatus )
            {
                    case FAT_CLUSTER_NOT_USED:
                    {
                        __ASSERT(0);
                        return FALSE;
                    }
                    case FAT_CLUSTER_ALLOCATED:
                    {
                        if(!FAT_SetClusterNo(pTempFileEntry->FileSystemID, u32CurrentClusterNo, 0))
                        {
                            __ASSERT(0);
                            return FALSE;
                        }
                        else
                        {
                            u32deletedClusterCount++;
                            break;
                        }

                     }
                    case FAT_CLUSTER_FINAL:                                  //<=======means oxFFFFFFFF
                    {
                        if(!FAT_SetClusterNo(pTempFileEntry->FileSystemID, u32CurrentClusterNo, 0))
                        {
                            __ASSERT(0);
                            return FALSE;
                        }

                        // update FAT table
                        if ( !FAT_FATStructureWrite( pTempFileEntry->FileSystemID ) )
                        {
                            __ASSERT(0);
                            return FALSE;
                        }
                        else
                        {
                             u32deletedClusterCount++;

                             if ( u8FATType == FAT_TYPE_FAT32)
                             {
                                //printf("FAT_FATStructureFreeClusterNo() : FAT_FATFsinfoUpdate_Increase()\n");
                                FAT_FATFsinfoUpdate_Increase(pTempFileEntry, u32deletedClusterCount);
                             }

                             return TRUE;                      //last cluster# of cluster chain
                        }

                     }
                case FAT_CLUSTER_RESERVED:
                case FAT_CLUSTER_DEFECTIVE:
                default:
                    break;
            }

            u32CurrentClusterNo = u32NextClusterNo;
    }
}




#if FILE_SYSTEM_GET_TOTAL_SIZE_ENABLE
U32 FAT_GetTotalSizeInKB(U8 u8fsid)
{
    //FS_EnvironmentStruct *pFS_Env;
    FAT_FileSysStruct *pFAT_FileSys;
    U32 u32FATDiskTotalSize;
    U32 u32BPB_FATSize;
    U32 u32OffsetOfFAT;
    U16 temp;

    //pFS_Env = msAPI_FSEnv_GetEnvironment(u8EnvironmentID);
    pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemInfo(u8fsid);

    #if 0
    u32FATDiskTotalSize = ((pFAT_FileSys->stFAT.u32FATTotalClusterNo * pFAT_FileSys->stBootSector.BPB_SecPerClus)*pFAT_FileSys->stBootSector.BPB_BytsPerSec)/1024;
    #else

    if(FAT_TYPE_FAT32 == pFAT_FileSys->stFAT.u8FATType)
        u32BPB_FATSize = pFAT_FileSys->stBootSector.BPB_FATSz32;
    else
        u32BPB_FATSize = pFAT_FileSys->stBootSector.BPB_FATSz16;


    if(pFAT_FileSys->stBootSector.BPB_TotSec16)
        u32FATDiskTotalSize = pFAT_FileSys->stBootSector.BPB_TotSec16;
    else
        u32FATDiskTotalSize = pFAT_FileSys->stBootSector.BPB_TotSec32;

    u32FATDiskTotalSize = (u32FATDiskTotalSize/pFAT_FileSys->stBootSector.BPB_SecPerClus)*pFAT_FileSys->stBootSector.BPB_SecPerClus;

    u32OffsetOfFAT = (pFAT_FileSys->stBootSector.BPB_NumFATs * u32BPB_FATSize) + pFAT_FileSys->stBootSector.BPB_RsvdSecCnt;
    if(u32OffsetOfFAT % pFAT_FileSys->stBootSector.BPB_SecPerClus)
        u32OffsetOfFAT = (u32OffsetOfFAT/pFAT_FileSys->stBootSector.BPB_SecPerClus + 1)*pFAT_FileSys->stBootSector.BPB_SecPerClus;

    u32FATDiskTotalSize -= u32OffsetOfFAT;
    if(FAT_TYPE_FAT12 == pFAT_FileSys->stFAT.u8FATType)
        u32FATDiskTotalSize -= u32OffsetOfFAT;


    if(pFAT_FileSys->stBootSector.BPB_BytsPerSec < 1024)
    {
        temp = (1024/pFAT_FileSys->stBootSector.BPB_BytsPerSec);
        u32FATDiskTotalSize /= temp;
    }
    else
    {
        temp = (pFAT_FileSys->stBootSector.BPB_BytsPerSec/1024);
        u32FATDiskTotalSize *= temp;
    }
    #endif

    return u32FATDiskTotalSize;
}
#endif

#if FILE_SYSTEM_GET_FREE_SPACE_ENABLE
#if ENABLE_PVR
// update new cluster to FAT table
U32 FAT_FAT32_GetUnusedSizeInKB(U8 u8fsid)
{
    U32 u32MaxCluster;
    FAT_FileSysStruct *pFsStruct;
    U16 u16BytePerSec;
    U32 *pu32FatTable;
    U16 u16SectorSize;

    U32  u32CurrentWindowStart;
    U16 i;
    U32 u32TotalFreeClusters = 0;
    U8 deviceIndex;
    U32 u32FATStartSectorNo;
    U32 u32CurCluster = 0;
    U32 u32TempFatTableOffsetSectorNo;
    U32 u32BytePerClus;

    pFsStruct = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);
    __ASSERT(pFsStruct->stFAT.u8FATType == FAT_TYPE_FAT32);

    u16BytePerSec=pFsStruct->stBootSector.BPB_BytsPerSec;
    u32MaxCluster = pFsStruct->stFAT.u32FATTotalClusterNo;
    deviceIndex=pFsStruct->DeviceIndex;
    u32FATStartSectorNo = pFsStruct->stFAT.u32FATStartSectorNo;
    u32BytePerClus  = (U32)u16BytePerSec*pFsStruct->stBootSector.BPB_SecPerClus;

    u32TempFatTableOffsetSectorNo = 0;
    while(u32CurCluster<u32MaxCluster)
    {

        if(BULK_FILE_SYSTEM_LEN>(u32MaxCluster-u32CurCluster)*4)
            u16SectorSize = (U16)(((u32MaxCluster-u32CurCluster)*4+u16BytePerSec-1)/u16BytePerSec);
        else
            u16SectorSize = (U16)(BULK_FILE_SYSTEM_LEN / u16BytePerSec);

        if( !msAPI_MSDCtrl_SectorRead(deviceIndex, u32FATStartSectorNo + u32TempFatTableOffsetSectorNo, (U32)u16SectorSize, _PA2VA(((BULK_FILE_SYSTEM_MEMORY_TYPE&MIU1)?BULK_FILE_SYSTEM_ADR|MIU_INTERVAL:BULK_FILE_SYSTEM_ADR))) )
        {
             __ASSERT(0);
             return 0;
        }
        u32TempFatTableOffsetSectorNo += u16SectorSize;
        u32CurrentWindowStart = 0;
        while(u32CurrentWindowStart < BULK_FILE_SYSTEM_LEN)
        {
            U32 u32Clus2Check;
          #if 0//ndef MIPS_CHAKRA //[8051+Aeon]
            pu32FatTable = (U32 xdata* )_PA2VA(msAPI_FS_GetAddr(((BULK_FILE_SYSTEM_MEMORY_TYPE&MIU1)?BULK_FILE_SYSTEM_ADR|MIU_INTERVAL:BULK_FILE_SYSTEM_ADR)+u32CurrentWindowStart));
          #else
            pu32FatTable = (U32 xdata* )_PA2VA(msAPI_FS_GetAddr(((BULK_FILE_SYSTEM_MEMORY_TYPE&MIU1)?BULK_FILE_SYSTEM_ADR|MIU_INTERVAL:BULK_FILE_SYSTEM_ADR)+u32CurrentWindowStart));
          #endif
            u32Clus2Check = 0x1000/4;
            if(u32Clus2Check > u32MaxCluster-u32CurCluster)
                  u32Clus2Check = u32MaxCluster-u32CurCluster;
            for( i=0; i<u32Clus2Check; i++)
            {
                if(pu32FatTable[i] == 0)
                    u32TotalFreeClusters++;
                u32CurCluster++;
            }
            u32CurrentWindowStart += 0x1000;
            if(u32CurCluster >= u32MaxCluster)
                break;
        }
    }

    if(u32BytePerClus >= 1024)
        return u32TotalFreeClusters*(u32BytePerClus/1024);
    else
        return u32TotalFreeClusters*u32BytePerClus/1024;
}
#endif
U32 FAT_GetUnusedSizeInKB(U8 u8fsid)
{
    //FS_EnvironmentStruct *pFS_Env;
    FAT_FileSysStruct *pFAT_FileSys;
    U32 u32FATDiskUnusedSpaceSize, u32CurrentClusterNo, u32UnusedClusterCount;
    U8 u8FATType;
    U32 u32FATTotalClusterNo;
    U8 u8BPB_SecPerClus;
    U32 u32TempFatTableOffsetSectorNo, u32FatTableEntryOffset;
    U16 u16BytePerSec;
    U8 u8SectorSize;
    U8 *pu8FatTable;
    U16 u16TempEntry;
    U32 u32Low;
    U32 u32High;
    U16 temp;
    U16 u16Temp;

    // get FAT file sys
    //pFS_Env = msAPI_FSEnv_GetEnvironment(u8EnvironmentID);
    pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemInfo(u8fsid);

    #if 0
    u32FATTotalClusterNo = pFAT_FileSys->stFAT.u32FATTotalClusterNo;
    #else
    u32FATTotalClusterNo = FAT_GetTotalSizeInKB(u8fsid);
    //u32FATTotalClusterNo = ((u32FATTotalClusterNo*1024)/pFAT_FileSys->stBootSector.BPB_BytsPerSec)/pFAT_FileSys->stBootSector.BPB_SecPerClus;
    if(pFAT_FileSys->stBootSector.BPB_BytsPerSec < 1024)
    {
        temp = (1024/pFAT_FileSys->stBootSector.BPB_BytsPerSec);
        u32FATTotalClusterNo = ((u32FATTotalClusterNo*temp)/pFAT_FileSys->stBootSector.BPB_SecPerClus);
    }
    else
    {
        temp = (pFAT_FileSys->stBootSector.BPB_BytsPerSec/1024);
        u32FATTotalClusterNo = ((u32FATTotalClusterNo/temp)/pFAT_FileSys->stBootSector.BPB_SecPerClus);
    }
    #endif
    u8FATType = pFAT_FileSys->stFAT.u8FATType;
    u8BPB_SecPerClus = pFAT_FileSys->stBootSector.BPB_SecPerClus;
    u16BytePerSec=pFAT_FileSys->stBootSector.BPB_BytsPerSec;
    u32TempFatTableOffsetSectorNo  = pFAT_FileSys->u32FATTableOffsetSectorNo;
    u8SectorSize = (U8)(FAT_TABLE_CACHE_LEN / u16BytePerSec);

    if(u8FATType == FAT_TYPE_FAT32)
    {
//        U16 temp;
        U32 freeCount;
        // [2008/01/26 CheKuei] Fix the empty FAT32 disk free space issue -- begin
        #if 0
        u32FATDiskUnusedSpaceSize = FAT_FATFsinfoRead(u8EnvironmentID,GET_FSI_FREE_COUNT) * u8BPB_SecPerClus/2;
        return u32FATDiskUnusedSpaceSize;
        #endif

        // Update by Ken
        //U32 freeCount=FAT_FATFsinfoRead(u8EnvironmentID,GET_FSI_FREE_COUNT);
        pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemInfo(u8fsid);

        freeCount=pFAT_FileSys->u32FSI_Free_Count;

        //FAT32 spec allow incorrect freeCount > totalCount, so it needs to be fixed
        if(freeCount>=u32FATTotalClusterNo)
        {
            freeCount=u32FATTotalClusterNo;
        }

        u32FATDiskUnusedSpaceSize = (freeCount* u8BPB_SecPerClus);
        if(u16BytePerSec < 1024)
        {
            temp = (1024/u16BytePerSec);
            u32FATDiskUnusedSpaceSize /= temp;
        }
        else
        {
            temp = (u16BytePerSec/1024);
            u32FATDiskUnusedSpaceSize *= temp;
        }

        return u32FATDiskUnusedSpaceSize;
        // [2008/01/26 CheKuei] Fix the empty FAT32 disk free space issue -- end

    }
    else
    {
//        U16 temp;
        u32CurrentClusterNo = 2;
        u32UnusedClusterCount = 0;
        u32Low = u32TempFatTableOffsetSectorNo * u16BytePerSec;
        u32High = (u32TempFatTableOffsetSectorNo + u8SectorSize) * u16BytePerSec;
        while ( u32CurrentClusterNo < (u32FATTotalClusterNo + 4) )
        {

            if(u8FATType == FAT_TYPE_FAT16)
            {
                u32FatTableEntryOffset = u32CurrentClusterNo * FAT16ENTRYSIZE;
            }
            else
            {
                u32FatTableEntryOffset = u32CurrentClusterNo * 3lu /2lu;
            }

            //*FAT table entry offset miss in FAT table*=================================================//
            if ( u32FatTableEntryOffset < u32Low ||
                 u32FatTableEntryOffset >= u32High )
            {
                BOOLEAN bIsDirty;
                pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemInfo(u8fsid);

                u32TempFatTableOffsetSectorNo = u32FatTableEntryOffset / u16BytePerSec;
                bIsDirty = pFAT_FileSys->bIsFATCacheDirty;

                if (bIsDirty)                    //<<===flush FAT table entry cross cache
                {
                    FAT_FATStructureWrite(u8fsid);                          //Entry Cluster# of deleted file cross FAT table cache
                }

                //pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemInfo(u8fsid);

                if ( !FAT_FATStructureFetch(u8fsid, u32TempFatTableOffsetSectorNo) )
                {
                     __ASSERT(0);
                     return FALSE;
                }
                u32Low = u32TempFatTableOffsetSectorNo * u16BytePerSec;
                u32High = (u32TempFatTableOffsetSectorNo + u8SectorSize) * u16BytePerSec;

            }

            pu8FatTable = (U8*)FCtrl_GetFatTableCacheInfo(u8fsid);

            if(pu8FatTable == NULL)
            {
                 __ASSERT(0);
                 return FALSE;
            }

            u32TempFatTableOffsetSectorNo = u8SectorSize * u16BytePerSec;
            u32FatTableEntryOffset = 0;
            while(u32CurrentClusterNo < (u32FATTotalClusterNo + 4) && u32FatTableEntryOffset < u32TempFatTableOffsetSectorNo)
            {
                if(u8FATType == FAT_TYPE_FAT16)
                {
                    memcpy(&u16Temp,(pu8FatTable + u32FatTableEntryOffset),2);
                    //if(*((U16 *)(pu8FatTable + u32FatTableEntryOffset)) == 0x0)
                    if(u16Temp==0x0)
                    {
                        u32UnusedClusterCount++;
                    }
                    u32FatTableEntryOffset += FAT16ENTRYSIZE;
                }
                else
                {
                    if(u32FatTableEntryOffset == u32High - 1)
                    {
                        pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemInfo(u8fsid);

                        u16TempEntry = (U16)(pFAT_FileSys->u8FAT12LastEntryByte) << 8;
                        u16TempEntry |= *(pu8FatTable + u32FatTableEntryOffset);
                    }
                    else
                    {
                        //u16TempEntry = (*(U16*)(pu8FatTable + u32FatTableEntryOffset));
                        memcpy(&u16TempEntry,(pu8FatTable + u32FatTableEntryOffset),2);
                    }

                    if((u32CurrentClusterNo & 1) == 0)
                    {
                        if((u16TempEntry & 0x0FFF) == 0x0)
                        {
                            u32UnusedClusterCount++;
                        }
                        u32FatTableEntryOffset += 2;
                    }
                    else
                    {
                        if((u16TempEntry >> 4) == 0x0)
                        {
                            u32UnusedClusterCount++;
                        }
                        u32FatTableEntryOffset++;
                    }
                }
                u32CurrentClusterNo++;
            }
        }

        u32FATDiskUnusedSpaceSize = (u32UnusedClusterCount * u8BPB_SecPerClus);
        if(u16BytePerSec < 1024)
        {
            temp = (1024/u16BytePerSec);
            u32FATDiskUnusedSpaceSize /= temp;
        }
        else
        {
            temp = (u16BytePerSec/1024);
            u32FATDiskUnusedSpaceSize *= temp;
        }
        return u32FATDiskUnusedSpaceSize;
    }
}

static BOOLEAN FAT_ComputedFreeClusterTotalCnt(FAT_FileSysStruct *pFAT_FileSys, U32 *pu32FreeClusterCnt)
{
    if(pFAT_FileSys ==NULL)
    {
        return FALSE;
    }

    if(pFAT_FileSys->stFAT.u8FATType == FAT_TYPE_FAT32)
    {
        U32 u32FreeClusterTotalCnt = 0, u32RecordNumClusterInOneSecter;
        U32 u32FATTotalClusterNo;
        U32 *u32pFAT= NULL;
        U32 u32Cnt, k, u32ClusterCnt = 0, u32ReadSectorNum;

        u32ReadSectorNum = USB_IO_TEMP_LEN2/pFAT_FileSys->stBootSector.BPB_BytsPerSec;
        u32RecordNumClusterInOneSecter = pFAT_FileSys->stBootSector.BPB_BytsPerSec/4;
        u32FATTotalClusterNo = pFAT_FileSys->stFAT.u32FATTotalClusterNo;

        //Check free cluster numbers in each FAT table secter
        for(u32Cnt = 0;u32Cnt<pFAT_FileSys->stBootSector.BPB_FATSz32;u32Cnt+=u32ReadSectorNum)
        {
            if ( !msAPI_MSDCtrl_SectorRead((U8)pFAT_FileSys->DeviceIndex, pFAT_FileSys->stFAT.u32FATStartSectorNo + u32Cnt,u32ReadSectorNum, USB_IO_TEMP_ADDR2 ) )
            {
                __ASSERT(0);
                return FALSE;
            }
            else
            {
                u32pFAT = (U32 *)msAPI_FS_GetAddr(USB_IO_TEMP_ADDR2);

                //Check number free cluster number
                for(k=0;k<u32RecordNumClusterInOneSecter*u32ReadSectorNum;k++)
                {
                    if(*u32pFAT == 0x0)
                    {
                        u32FreeClusterTotalCnt++;
                    }
                    u32pFAT++;
                    u32ClusterCnt++;
                    if(u32ClusterCnt >= u32FATTotalClusterNo)
                    {
                        break;
                    }
                }
            }
        }

        //defaut 2 cluster not use , so add 2
        *pu32FreeClusterCnt = u32FreeClusterTotalCnt + 2;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

U32 FAT_GetUnusedSizeInKB_New(U8 u8fsid)
{
    //FS_EnvironmentStruct *pFS_Env;
    FAT_FileSysStruct *pFAT_FileSys;
    U32 u32FATDiskUnusedSpaceSize, u32CurrentClusterNo, u32UnusedClusterCount;
    U8 u8FATType;
    U32 u32FATTotalClusterNo;
    U8 u8BPB_SecPerClus;
    U32 u32TempFatTableOffsetSectorNo, u32FatTableEntryOffset;
    U16 u16BytePerSec;
    U8 u8SectorSize;
    U8 *pu8FatTable;
    U16 u16TempEntry;
    U32 u32Low;
    U32 u32High;
    U16 temp;
    U16 u16Temp;

    // get FAT file sys
    //pFS_Env = msAPI_FSEnv_GetEnvironment(u8EnvironmentID);
    pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemInfo(u8fsid);

    #if 0
    u32FATTotalClusterNo = pFAT_FileSys->stFAT.u32FATTotalClusterNo;
    #else
    u32FATTotalClusterNo = FAT_GetTotalSizeInKB(u8fsid);
    //u32FATTotalClusterNo = ((u32FATTotalClusterNo*1024)/pFAT_FileSys->stBootSector.BPB_BytsPerSec)/pFAT_FileSys->stBootSector.BPB_SecPerClus;
    if(pFAT_FileSys->stBootSector.BPB_BytsPerSec < 1024)
    {
        temp = (1024/pFAT_FileSys->stBootSector.BPB_BytsPerSec);
        u32FATTotalClusterNo = ((u32FATTotalClusterNo*temp)/pFAT_FileSys->stBootSector.BPB_SecPerClus);
    }
    else
    {
        temp = (pFAT_FileSys->stBootSector.BPB_BytsPerSec/1024);
        u32FATTotalClusterNo = ((u32FATTotalClusterNo/temp)/pFAT_FileSys->stBootSector.BPB_SecPerClus);
    }
    #endif
    u8FATType = pFAT_FileSys->stFAT.u8FATType;
    u8BPB_SecPerClus = pFAT_FileSys->stBootSector.BPB_SecPerClus;
    u16BytePerSec=pFAT_FileSys->stBootSector.BPB_BytsPerSec;
    u32TempFatTableOffsetSectorNo  = pFAT_FileSys->u32FATTableOffsetSectorNo;
    u8SectorSize = (U8)(FAT_TABLE_CACHE_LEN / u16BytePerSec);

    if(u8FATType == FAT_TYPE_FAT32)
    {
//        U16 temp;
        U32 freeCount;
        // [2008/01/26 CheKuei] Fix the empty FAT32 disk free space issue -- begin
        #if 0
        u32FATDiskUnusedSpaceSize = FAT_FATFsinfoRead(u8EnvironmentID,GET_FSI_FREE_COUNT) * u8BPB_SecPerClus/2;
        return u32FATDiskUnusedSpaceSize;
        #endif

        // Update by Ken
        //U32 freeCount=FAT_FATFsinfoRead(u8EnvironmentID,GET_FSI_FREE_COUNT);

        freeCount=pFAT_FileSys->u32FSI_Free_Count;

        //FAT32 spec allow incorrect freeCount > totalCount, so it needs to be fixed
        if(freeCount>=u32FATTotalClusterNo)
        {
            //If the value is 0xffffffff ,it means invalid. then the free cluster count
            // is unknown and must be computed
            if(freeCount == 0xFFFFFFFF)
            {
                if(FAT_ComputedFreeClusterTotalCnt(pFAT_FileSys, &freeCount)==FALSE)
                {
                    freeCount=u32FATTotalClusterNo;
                }
            }
            else
            {
                freeCount=u32FATTotalClusterNo;
            }
            pFAT_FileSys->u32FSI_Free_Count = freeCount;
        }

        //printf("\nfreeClusterCount=%ld ,u32FATTotalClusterNo=%ld\n",freeCount,u32FATTotalClusterNo);

        u32FATDiskUnusedSpaceSize = (freeCount* u8BPB_SecPerClus);
        if(u16BytePerSec < 1024)
        {
            temp = (1024/u16BytePerSec);
            u32FATDiskUnusedSpaceSize /= temp;
        }
        else
        {
            temp = (u16BytePerSec/1024);
            u32FATDiskUnusedSpaceSize *= temp;
        }

        return u32FATDiskUnusedSpaceSize;
        // [2008/01/26 CheKuei] Fix the empty FAT32 disk free space issue -- end

    }
    else
    {
//        U16 temp;
        u32CurrentClusterNo = 2;
        u32UnusedClusterCount = 0;
        u32Low = u32TempFatTableOffsetSectorNo * u16BytePerSec;
        u32High = (u32TempFatTableOffsetSectorNo + u8SectorSize) * u16BytePerSec;
        while ( u32CurrentClusterNo < (u32FATTotalClusterNo + 4) )
        {

            if(u8FATType == FAT_TYPE_FAT16)
            {
                u32FatTableEntryOffset = u32CurrentClusterNo * FAT16ENTRYSIZE;
            }
            else
            {
                u32FatTableEntryOffset = u32CurrentClusterNo * 3lu /2lu;
            }

            //*FAT table entry offset miss in FAT table*=================================================//
            if ( u32FatTableEntryOffset < u32Low ||
                 u32FatTableEntryOffset >= u32High )
            {
                BOOLEAN bIsDirty;
                pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemInfo(u8fsid);

                u32TempFatTableOffsetSectorNo = u32FatTableEntryOffset / u16BytePerSec;
                bIsDirty = pFAT_FileSys->bIsFATCacheDirty;

                if (bIsDirty)                    //<<===flush FAT table entry cross cache
                {
                    FAT_FATStructureWrite(u8fsid);                          //Entry Cluster# of deleted file cross FAT table cache
                }

                //pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemInfo(u8fsid);

                if ( !FAT_FATStructureFetch(u8fsid, u32TempFatTableOffsetSectorNo) )
                {
                     __ASSERT(0);
                     return FALSE;
                }
                u32Low = u32TempFatTableOffsetSectorNo * u16BytePerSec;
                u32High = (u32TempFatTableOffsetSectorNo + u8SectorSize) * u16BytePerSec;

            }

            pu8FatTable = (U8*)FCtrl_GetFatTableCacheInfo(u8fsid);

            if(pu8FatTable == NULL)
            {
                 __ASSERT(0);
                 return FALSE;
            }

            u32TempFatTableOffsetSectorNo = u8SectorSize * u16BytePerSec;
            u32FatTableEntryOffset = 0;
            while(u32CurrentClusterNo < (u32FATTotalClusterNo + 4) && u32FatTableEntryOffset < u32TempFatTableOffsetSectorNo)
            {
                if(u8FATType == FAT_TYPE_FAT16)
                {
                    memcpy(&u16Temp,(pu8FatTable + u32FatTableEntryOffset),2);
                    //if(*((U16 *)(pu8FatTable + u32FatTableEntryOffset)) == 0x0)
                    if(u16Temp==0x0)
                    {
                        u32UnusedClusterCount++;
                    }
                    u32FatTableEntryOffset += FAT16ENTRYSIZE;
                }
                else
                {
                    if(u32FatTableEntryOffset == u32High - 1)
                    {
                        pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemInfo(u8fsid);

                        u16TempEntry = (U16)(pFAT_FileSys->u8FAT12LastEntryByte) << 8;
                        u16TempEntry |= *(pu8FatTable + u32FatTableEntryOffset);
                    }
                    else
                    {
                        //u16TempEntry = (*(U16*)(pu8FatTable + u32FatTableEntryOffset));
                        memcpy(&u16TempEntry,(pu8FatTable + u32FatTableEntryOffset),2);
                    }

                    if((u32CurrentClusterNo & 1) == 0)
                    {
                        if((u16TempEntry & 0x0FFF) == 0x0)
                        {
                            u32UnusedClusterCount++;
                        }
                        u32FatTableEntryOffset += 2;
                    }
                    else
                    {
                        if((u16TempEntry >> 4) == 0x0)
                        {
                            u32UnusedClusterCount++;
                        }
                        u32FatTableEntryOffset++;
                    }
                }
                u32CurrentClusterNo++;
            }
        }

        u32FATDiskUnusedSpaceSize = (u32UnusedClusterCount * u8BPB_SecPerClus);
        if(u16BytePerSec < 1024)
        {
            temp = (1024/u16BytePerSec);
            u32FATDiskUnusedSpaceSize /= temp;
        }
        else
        {
            temp = (u16BytePerSec/1024);
            u32FATDiskUnusedSpaceSize *= temp;
        }
        return u32FATDiskUnusedSpaceSize;
    }
}
#endif

#if FILE_SYSTEM_FORMAT_ENABLE
BOOLEAN FAT_FastFormatByDriveIndex(MSDCtrl_Drive target_drive)
{
    FAT_FileSysStruct *pFAT_FileSys;
    U32 u32FATStartSectorNo;
    U32 u32FATTotalSector;
    U32 u32RootDirStartSectorNo;
    U8 u8NumFATs;
    U16 u16BytesPerSec;
    U8 u8SecPerClus;
    U8 u8FatType;
    U8 u8MaxSector;
    U32 u32FATDate[3];
    U32 u32TotalCleanSectors;
    U32 u32SectorCount=0;
    U32 u32FsinfoStartSectorNo;
    U32 u32FSI_Free_Count, u32FSI_Nxt_Free;
    BOOLEAN bRet;

    pFAT_FileSys = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(target_drive.DriveIndex);
    u8FatType=pFAT_FileSys->stFAT.u8FATType;

    /*[01]get file system=======================================================*/
    if(u8FatType == FAT_TYPE_FAT32)
    {
        U32 totalClusters;
        u32FATStartSectorNo = pFAT_FileSys->stFAT.u32FATStartSectorNo;
        u32FATTotalSector = pFAT_FileSys->stBootSector.BPB_FATSz32;
        u32RootDirStartSectorNo = pFAT_FileSys->u32RootDirStartSectorNo;
        //u32TotalSec = pFAT_FileSys->stBootSector.BPB_TotSec32;
        u8NumFATs = pFAT_FileSys->stBootSector.BPB_NumFATs;
        u16BytesPerSec = pFAT_FileSys->stBootSector.BPB_BytsPerSec;
        u8SecPerClus = pFAT_FileSys->stBootSector.BPB_SecPerClus;
        u8MaxSector = (USB_IO_TEMP_LEN/u16BytesPerSec);

        //printf("u32FATStartSectorNo=0x%lx u32FATTotalSector:0x%lx\n",u32FATStartSectorNo,u32FATTotalSector);
        //printf("u32RootDirStartSectorNo=0x%lx\n",u32RootDirStartSectorNo);
        //printf("u16BytesPerSec=0x%x\n",u16BytesPerSec);
        //printf("u8SecPerClus=0x%bx\n",u8SecPerClus);
        //printf("u8MaxSector=0x%bx\n",u8MaxSector);

    #if 0
	totalClusters = (pFAT_FileSys->stBootSector.BPB_TotSec32-u32FATStartSectorNo-u32FATTotalSector*u8NumFATs)/u8SecPerClus;
	if(totalClusters > u32FATTotalSector*u16BytesPerSec/4)
		totalClusters = u32FATTotalSector*u16BytesPerSec/4;
    #else
        totalClusters = pFAT_FileSys->stFAT.u32FATTotalClusterNo;
    #endif

        //I. Clean FAT Table. -------------------------------------//
        if ( !msAPI_MSDCtrl_SectorRead(target_drive.DeviceIndex, u32FATStartSectorNo, 1, USB_IO_TEMP_ADDR))
        {
            __ASSERT(0);
            return FALSE;
        }
        memcpy((U8 *)u32FATDate,(U8 *)USB_IO_TEMP_ADDR,4);  //Set u32FATDate[0]

        u32FATDate[1] = 0xFFFFFFFF;  //Set u32FATDate[1]
        u32FATDate[2] = 0x0FFFFFFF;  //Set u32FATDate[2]
        //printf("u32FATDate[0]=0x%lx, u32FATDate[1]=0x%lx u32FATDate[2]=0x%lx\n",u32FATDate[0],u32FATDate[1],u32FATDate[2]);

        u32TotalCleanSectors = u32FATTotalSector;

        //-----Clean FAT1
        memset((U8 *)USB_IO_TEMP_ADDR,0,USB_IO_TEMP_LEN);
        if(u8NumFATs > 0)
        {
            u32SectorCount = 0;
            while(u32TotalCleanSectors>0)
            {
                if(u32TotalCleanSectors >= u8MaxSector)
                {
                    if ( !msAPI_MSDCtrl_SectorWrite(target_drive.DeviceIndex, u32FATStartSectorNo+u32SectorCount, u8MaxSector, USB_IO_TEMP_ADDR))
                    {
                        __ASSERT(0);
                        return FALSE;
                    }
                    u32SectorCount += u8MaxSector;
                    u32TotalCleanSectors -= u8MaxSector;

                }
                else
                {
                    if ( !msAPI_MSDCtrl_SectorWrite(target_drive.DeviceIndex, u32FATStartSectorNo+u32SectorCount, u32TotalCleanSectors, USB_IO_TEMP_ADDR))
                    {
                        __ASSERT(0);
                        return FALSE;
                    }
                    u32SectorCount += u32TotalCleanSectors;
                    u32TotalCleanSectors = 0;
                }
            }

            //Set FAT1 First Sector.
            memcpy((U8 *)(USB_IO_TEMP_ADDR),(U8 *)(u32FATDate), 4);         //Set u32FATDate[0]
            memcpy((U8 *)(USB_IO_TEMP_ADDR+4),(U8 *)(u32FATDate+1), 4);   //Set u32FATDate[1]
            memcpy((U8 *)(USB_IO_TEMP_ADDR+8),(U8 *)(u32FATDate+2), 4);   //Set u32FATDate[1]
            if ( !msAPI_MSDCtrl_SectorWrite(target_drive.DeviceIndex, u32FATStartSectorNo, 1, USB_IO_TEMP_ADDR))
            {
                __ASSERT(0);
                return FALSE;
            }
        }

        //-----Clean FAT2
        memset((U8 *)USB_IO_TEMP_ADDR,0,USB_IO_TEMP_LEN);
        if(u8NumFATs == 2)
        {
            u32SectorCount = u32FATTotalSector;
            while(u32TotalCleanSectors>0)
            {
                if(u32TotalCleanSectors >= u8MaxSector)
                {
                    if ( !msAPI_MSDCtrl_SectorWrite(target_drive.DeviceIndex, u32FATStartSectorNo+u32SectorCount, u8MaxSector, USB_IO_TEMP_ADDR))
                    {
                        __ASSERT(0);
                        return FALSE;
                    }
                    u32SectorCount += u8MaxSector;
                    u32TotalCleanSectors -= u8MaxSector;
                }
                else
                {
                    if ( !msAPI_MSDCtrl_SectorWrite(target_drive.DeviceIndex, u32FATStartSectorNo+u32SectorCount, u32TotalCleanSectors, USB_IO_TEMP_ADDR))
                    {
                        __ASSERT(0);
                        return FALSE;
                    }
                    u32SectorCount += u32TotalCleanSectors;
                    u32TotalCleanSectors = 0;
                }
            }

            //Set FAT1 First Sector.
            memcpy((U8 *)(USB_IO_TEMP_ADDR),(U8 *)(u32FATDate), 4);         //Set u32FATDate[0]
            memcpy((U8 *)(USB_IO_TEMP_ADDR+4),(U8 *)(u32FATDate+1), 4);   //Set u32FATDate[1]
            memcpy((U8 *)(USB_IO_TEMP_ADDR+8),(U8 *)(u32FATDate+2), 4);   //Set u32FATDate[1]
            if ( !msAPI_MSDCtrl_SectorWrite(target_drive.DeviceIndex, u32FATStartSectorNo+u32FATTotalSector, 1, USB_IO_TEMP_ADDR))
            {
                __ASSERT(0);
                return FALSE;
            }
        }
        //----------------------------------------------------//


        //II. Clean Root Directory.----------------------------------//
        memset((U8 *)USB_IO_TEMP_ADDR,0,USB_IO_TEMP_LEN);
        u32TotalCleanSectors = u8SecPerClus;

        u32SectorCount = 0;
        while(u32TotalCleanSectors>0)
        {
            if(u32TotalCleanSectors >= u8MaxSector)
            {
                if ( !msAPI_MSDCtrl_SectorWrite(target_drive.DeviceIndex, u32RootDirStartSectorNo+u32SectorCount, u8MaxSector, USB_IO_TEMP_ADDR))
                {
                    __ASSERT(0);
                    return FALSE;
                }
                u32SectorCount += u8MaxSector;
                u32TotalCleanSectors -= u8MaxSector;
            }
            else
            {
                if ( !msAPI_MSDCtrl_SectorWrite(target_drive.DeviceIndex, u32RootDirStartSectorNo+u32SectorCount, u32TotalCleanSectors, USB_IO_TEMP_ADDR))
                {
                    __ASSERT(0);
                    return FALSE;
                }
                u32SectorCount += u32TotalCleanSectors;
                u32TotalCleanSectors = 0;
            }
        }
        //----------------------------------------------------//


        //III. Update Free Space.----------------------------------//
        // get FAT file system
        u32FsinfoStartSectorNo = pFAT_FileSys->stBootSector.BPB_FSInfo + pFAT_FileSys->u32RelativeSector;
        if ( !msAPI_MSDCtrl_SectorRead(pFAT_FileSys->DeviceIndex, u32FsinfoStartSectorNo, 1, USB_IO_TEMP_ADDR))
        {
            __ASSERT(0);
            return FALSE;
        }

        u32FSI_Free_Count = totalClusters;
        u32FSI_Nxt_Free = 2;
        memcpy((U8 *)(USB_IO_TEMP_ADDR+488),(U8 *)(&u32FSI_Free_Count), 4);   //Set u32FATDate[1]
        memcpy((U8 *)(USB_IO_TEMP_ADDR+492),(U8 *)(&u32FSI_Nxt_Free), 4);

        if (msAPI_MSDCtrl_SectorWrite(pFAT_FileSys->DeviceIndex, u32FsinfoStartSectorNo, 1, USB_IO_TEMP_ADDR))
        {
            pFAT_FileSys->u32FSI_Free_Count = u32FSI_Free_Count;
        }
        else
        {
            __ASSERT(0);
            return FALSE;
        }

        pFAT_FileSys->u32CurrentFreeCluster = u32FSI_Nxt_Free;
        //----------------------------------------------------//

        MS_DEBUG_MSG(printf("Format Done!\n"));
        bRet = TRUE;
    }
    else
    {
        bRet = FALSE;
    }

    return bRet;
}

static BOOLEAN FAT_FAT32_Format_BPB(U8 u8DeviceIndex, U32 u32RelativeSector, U32 u32TotalSec, U8* u8SecPerCluster, U32 *u32FATSize)
{
    U8 * pBPB;
    U16 u16BytesPerSec;
    U32 temp;
    U8 u8Offset0_31[] = {0xEB, 0x58, 0x90,  // BPB_jmpBoot
                                'M', 'S', 'D', 'O', 'S', '5', '.', '0',     // BS_OEMName
                                0, 2,       // BPB_BytsPerSec
                                0x08,       // BPB_SecPerClus
                                0x20, 0,    // BPB_RsvdSecCnt
                                2,          // BPB_NumFATs
                                0, 0, 0, 0, // unused
                                0xF8,       // BPB_Media
                                0, 0,       // unused, must be zero
                                0x3F, 0,    // BPB_SecPerTrk
                                0xFF, 0,    // BPB_NumHeads
                                0, 0, 0, 0};// BPB_HiddSec

    U8 u8Offset40_89[] = {0, 0,         // BPB_ExtFlags
                          0, 0,         // BPB_FSVer
                          2, 0, 0, 0,   // BPB_RootClus
                          1, 0,         // BPB_FSInfo
                          6, 0,         // BPB_BkBootSec
                          0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  // BPB_Reserved
                          0x80,         // BS_DrvNum
                          0,            // BS_Reserved1
                          0x29,         // BS_BootSig
                          0x30, 0xC9, 0xC0, 0x10,   // BS_VolID
                          'N', 'O', ' ', 'N', 'A', 'M', 'E', ' ', ' ', ' ', ' ',    // BS_VolLab
                          'F', 'A', 'T', '3', '2', ' ', ' ', ' '};  // BS_FilSysType


    // get total size
    if(u32TotalSec == 0)
    {
        u32TotalSec = msAPI_MSDCtrl_GetBlockNum(u8DeviceIndex);
        FATDBG(printf("\n    Format TotalSec: 0x%08LX", u32TotalSec));
    }
    u16BytesPerSec = msAPI_MSDCtrl_GetBlockSize(u8DeviceIndex);
    if(u16BytesPerSec == 0)
    {
        u16BytesPerSec = 0x200;
    }
    u8Offset0_31[11] = (u16BytesPerSec&0xFF);
    u8Offset0_31[12] = (u16BytesPerSec >> 8);

    FATDBG(printf("MSD block number = 0x%x\n", msAPI_MSDCtrl_GetBlockNum(u8DeviceIndex)));
    FATDBG(printf("MSD block size = 0x%x\n", msAPI_MSDCtrl_GetBlockSize(u8DeviceIndex)));
    FATDBG(printf("\n    Format TotalSec: 0x%08LX [%lu]", u32TotalSec,u32TotalSec));

    // set BPB_SecPerClus
    if(*u8SecPerCluster==0)
    {
        if(u32TotalSec<16777216)
        {
            //Cluster size 4K
            *u8SecPerCluster = 0x1000/u16BytesPerSec;
            u8Offset0_31[13] = *u8SecPerCluster;
        }
        else if((u32TotalSec>=16777216) && (u32TotalSec<33554432))
        {
            //Cluster size 8K
            *u8SecPerCluster = 0x2000/u16BytesPerSec;
            u8Offset0_31[13] = *u8SecPerCluster;
        }
        else if((u32TotalSec>=33554432) && (u32TotalSec<67108864))
        {
            //Cluster size 16K
            *u8SecPerCluster = 0x4000/u16BytesPerSec;
            u8Offset0_31[13] = *u8SecPerCluster;
        }
        else
        {
            //Cluster size 32K
            *u8SecPerCluster = 0x8000/u16BytesPerSec;
            u8Offset0_31[13] = *u8SecPerCluster;
        }
    }
    else
    {
         u8Offset0_31[13] = *u8SecPerCluster;
    }

    // get FAT size
    *u32FATSize = (u32TotalSec)/(*u8SecPerCluster)*4/u16BytesPerSec +1;
    FATDBG(printf("PVRFS_FAT_Format_BPB : u8SecPerCluster[%bd], u32FATSize[%lu]",*u8SecPerCluster, u32FATSize));

    pBPB = (U8 xdata *)msAPI_FS_GetAddr(USB_IO_TEMP_ADDR);
    {
        memset((pBPB + 0), 0, 0x400);
        memcpy((pBPB + 0), u8Offset0_31, 32);
        memcpy((pBPB + 0xD), u8SecPerCluster, 1);       //BPB_SecPerClu
        memcpy((pBPB + 0x20), (U8 *)&u32TotalSec, 4);   //BPB_TotSec32
        memcpy((pBPB + 0x24), (U8 *)u32FATSize, 4);     //BPB_FATSz32
        memcpy((pBPB + 0x28), u8Offset40_89, 50);
        temp = 0xaa550000;
        memcpy((pBPB + 0x1FC), (U8 *)&temp, 4);         //signature occupies the last 2 bytes of the boot sector

        //FSInfo Sector Structure and Backup Boot Sector.
        temp = 0x41615252;
        memcpy((pBPB + 0x200), (U8 *)&temp, 4); //FSI_LeadSig
        temp = 0x61417272;
        memcpy((pBPB + 0x3E4), (U8 *)&temp, 4); //FSI_StrucSig
        temp = 0xFFFFFFFF;
        memcpy((pBPB + 0x3E8), (U8 *)&temp, 4); //FSI_Free_Count
        temp = 0x2;
        memcpy((pBPB + 0x3EC), (U8 *)&temp, 4); //FSI_Nxt_Free
        temp = 0xaa550000;
        memcpy((pBPB + 0x3FC), (U8 *)&temp, 4); //FSI_TrailSig
    }

    if(!msAPI_MSDCtrl_SectorWrite(u8DeviceIndex, u32RelativeSector, 2, USB_IO_TEMP_ADDR))
    {
        __ASSERT(0);
        return FALSE;
    }

    return TRUE;
}

static BOOLEAN FAT_FAT32_Probe_BPB(U8 u8DeviceIndex, U32 u32RelativeSector,
               U16*pu16ReservedSectors, U8 *pu8NumFATs,  U8* pu8SecPerCluster, U32 *pu32TotalSec, U32 *pu32FATSize)
{
    U8 *pBPB;

    if(!msAPI_MSDCtrl_SectorRead(u8DeviceIndex, u32RelativeSector, 1, USB_IO_TEMP_ADDR))
    {
        __ASSERT(0);
        return FALSE;
    }
    pBPB = (U8 xdata *)msAPI_FS_GetAddr(USB_IO_TEMP_ADDR);

    ///check if this is an valid FAT32 BPB
    if(pBPB[0]!=0xEB || pBPB[2]!=0x90 ||
       pBPB[82]!='F' || pBPB[84]!='T'|| pBPB[86]!='2')
    {
         __ASSERT(0);
         return FALSE;
    }
    if(pu8NumFATs)
        *pu8NumFATs = *(pBPB + 0x10);
    if(pu8SecPerCluster)
        *pu8SecPerCluster= *(pBPB + 0xD);
    if(pu16ReservedSectors)
        memcpy((U8 *)pu16ReservedSectors, (pBPB + 0x0E),  2);
    if(pu32TotalSec)
        memcpy((U8 *)pu32TotalSec, (pBPB + 0x20),  4);
    if(pu32FATSize)
        memcpy((U8 *)pu32FATSize, (pBPB + 0x24), 4);

    return TRUE;
}


BOOLEAN FAT_FastFormatByDriveIndex_enhance(MSDCtrl_Drive target_drive)
{
    #define MAX_PARTITION_COUNT 4

    U8 u8DeviceID = target_drive.DeviceIndex;
    U8 u8IndexInMBR = target_drive.u8IndexInMBR;
    U16 u16IndexInMBR = u8IndexInMBR;
    U32 u32MBRLogicBlockAddress = target_drive.u32MBRLogicBlockAddress;
    U8 *pu8Cache;

    if(u8IndexInMBR >= MAX_PARTITION_COUNT && u8IndexInMBR!=INVALID_MBR_INDEX)
    {
        __ASSERT(0);
        return FALSE;
    }

    // step1: get u32RelativeSector & format BPB
    U32 u32RelativeSector;
    U32 u32TotalSec;
    U8 u8NumFATs;
    U8 u8SecPerCluster = 0; // 0->dynamic detect
    U32 u32FATSize, u32TotalFATTableSec;
    U16 u16ReservedSectors;

    if(u32MBRLogicBlockAddress != INVALID_MBR_ADDRESS)
    {
        if(!msAPI_MSDCtrl_SectorRead(u8DeviceID, u32MBRLogicBlockAddress, 1, USB_IO_TEMP_ADDR))
        {
            __ASSERT(0);
            return FALSE;
        }

        pu8Cache = (U8 xdata* )msAPI_FS_GetAddr(USB_IO_TEMP_ADDR);
        if(u8IndexInMBR>=MAX_PARTITION_COUNT)
        {
            u32RelativeSector = 0;
            u32TotalSec = 0;
        }
        else
        {
            u16IndexInMBR *= 0x10;
            if(*(pu8Cache + 0x1C2 + u16IndexInMBR)==0x01||*(pu8Cache + 0x1C2 + u16IndexInMBR)==0x04||*(pu8Cache + 0x1C2 + u16IndexInMBR)==0x06
             ||*(pu8Cache + 0x1C2 + u16IndexInMBR)==0x07
             ||*(pu8Cache + 0x1C2 + u16IndexInMBR)==0x0B||*(pu8Cache + 0x1C2 + u16IndexInMBR)==0x0C||*(pu8Cache + 0x1C2 + u16IndexInMBR)==0x0E
             ||*(pu8Cache + 0x1C2 + u16IndexInMBR)==0x1C)
            {
                memcpy((U8 *)&u32RelativeSector, (pu8Cache + 0x1C6 + u16IndexInMBR), 4);
                memcpy((U8 *)&u32TotalSec, (pu8Cache + 0x1CA + u16IndexInMBR), 4);

                if(u32TotalSec == 0)
                {
                    u32RelativeSector = 0;
                }
                else
                {
                    u32RelativeSector += u32MBRLogicBlockAddress;
                    *(pu8Cache + 0x1C2 + u16IndexInMBR) = 0x0B;
                    if(!msAPI_MSDCtrl_SectorWrite(u8DeviceID, u32MBRLogicBlockAddress, 1, USB_IO_TEMP_ADDR))
                    {
                        __ASSERT(0);
                        return FALSE;
                    }
                }
            }
            else
            {
                u32RelativeSector = 0;
                u32TotalSec = 0;
            }
        }

        if(u32MBRLogicBlockAddress>0||u8IndexInMBR>0)
        {
            if((0 == u32RelativeSector) || (0 == u32TotalSec))
            {
                __ASSERT(0);
                return FALSE;
            }
        }

        u8NumFATs = 2;
        u8SecPerCluster = 0;
        FAT_FAT32_Format_BPB(u8DeviceID, u32RelativeSector, u32TotalSec, &u8SecPerCluster, &u32FATSize);
        u32TotalFATTableSec = (U32)u8NumFATs * u32FATSize;

        FATDBG(printf("\nu32RelativeSector: 0x%08LX, u16FatStartSec: %X, u8NumFATs: %02bx, u32FATSize: %LX",u32RelativeSector, (U16)0x20, u8NumFATs, u32FATSize));
    }
    else
    {
        //FAT16
        FATDBG(printf("    No Partition Table was Found, Create BPB Directly...\n"));
        u32RelativeSector = 0;
        u32TotalSec = 0;
        u8NumFATs = 2;
        FAT_FAT32_Format_BPB(u8DeviceID, u32RelativeSector, u32TotalSec, &u8SecPerCluster, &u32FATSize); //no partition table found, force to create BPB
        u32TotalFATTableSec = (U32)u8NumFATs * u32FATSize;
    }

    if(FAT_FAT32_Probe_BPB(u8DeviceID, u32RelativeSector, &u16ReservedSectors, &u8NumFATs,
        &u8SecPerCluster, &u32TotalSec, &u32FATSize) == FALSE)
    {
        __ASSERT(0);
        return FALSE;
    }
    u32TotalFATTableSec = (U32)u8NumFATs * u32FATSize;

    U32 u32FATStartSectorNo = u32RelativeSector + u16ReservedSectors; //0x20:FatStartSec
    U16 u16BytesPerSec = 512;
    U8 u8MaxSector = (USB_IO_TEMP_LEN/u16BytesPerSec);
    U32 u32WriteCount, u32RemainderSectorCnt;
    U8 u8WriteSectorNum;

    //I. Clean all FAT table(FAT1 + FAT2).----------------------------------//
    u32WriteCount = 0;
    u32RemainderSectorCnt = u32TotalFATTableSec;
    memset((U8 *)USB_IO_TEMP_ADDR,0,USB_IO_TEMP_LEN);

    while(u32RemainderSectorCnt > 0)
    {
        u8WriteSectorNum = MIN(u32RemainderSectorCnt, u8MaxSector);
        if(!msAPI_MSDCtrl_SectorWrite(u8DeviceID, (U32)(u32FATStartSectorNo+u32WriteCount), u8WriteSectorNum, USB_IO_TEMP_ADDR))
        {
            __ASSERT(0);
            return FALSE;
        }
        u32RemainderSectorCnt -=u8WriteSectorNum;
        u32WriteCount +=u8WriteSectorNum;
    }

    FATDBG(printf("    Initial ROOT Dorectory...\n"));
    //II. Clean Root Directory.----------------------------------//
    u32WriteCount = 0;
    u32RemainderSectorCnt = u8SecPerCluster;

    while(u32RemainderSectorCnt > 0)
    {
        u8WriteSectorNum = MIN(u32RemainderSectorCnt, u8MaxSector);
        if(!msAPI_MSDCtrl_SectorWrite(u8DeviceID, (U32)(u32FATStartSectorNo+u32TotalFATTableSec + u32WriteCount), u8WriteSectorNum, USB_IO_TEMP_ADDR))
        {
            __ASSERT(0);
            return FALSE;
        }
        u32RemainderSectorCnt -=u8WriteSectorNum;
        u32WriteCount += u8WriteSectorNum;
    }

    //III. Init FAT table.----------------------------------//
    U32 u32ClusterID;
    u32ClusterID = 0x0FFFFFF8;
    memcpy((U8 *)(USB_IO_TEMP_ADDR),  (U8 *)(&u32ClusterID), 4);
    u32ClusterID = 0xFFFFFFFF;
    memcpy((U8 *)(USB_IO_TEMP_ADDR+4),(U8 *)(&u32ClusterID), 4);
    memcpy((U8 *)(USB_IO_TEMP_ADDR+8),(U8 *)(&u32ClusterID), 4);

    //Set FAT1 First Sector.
    if(!msAPI_MSDCtrl_SectorWrite(u8DeviceID, (U32)u32FATStartSectorNo, 1, USB_IO_TEMP_ADDR))
    {
        __ASSERT(0);
        return FALSE;
    }

    //Set FAT2 First Sector.
    if(!msAPI_MSDCtrl_SectorWrite(u8DeviceID, (U32)(u32FATStartSectorNo+u32FATSize), 1, USB_IO_TEMP_ADDR))
    {
        __ASSERT(0);
        return FALSE;
    }

    FATDBG(printf("Format Done!\n"));

    //IV. Re-Active Device.----------------------------------//
    msAPI_MSDCtrl_ResetDevice(u8DeviceID);
    msAPI_MSDCtrl_CheckDevices();
    if(!msAPI_FCtrl_ActiveDevice(u8DeviceID))
    {
        FATDBG(printf("Active device fail\n"));
        return FALSE;
    }

    return TRUE;
}
#endif

static BOOLEAN FAT_SetClusterNo(U8 u8fsid , U32 u32ClusterNo, U32 u32ValueToSet)
{
    FAT_FileSysStruct *pFATFileSys;
    U32 u32TempFatTableOffsetSectorNo, u32FatTableEntryOffset;
    U8 *pu8FatTable;
    U8 u8FATType;
    U16 u16BytePerSec;
    U8 u8SectorSize;
    U16 u16EntryData;
    U32 u32Low;
    U32 u32High;
    U16 u16Temp;

    pFATFileSys = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);

    u8FATType = pFATFileSys->stFAT.u8FATType;
    u16BytePerSec=pFATFileSys->stBootSector.BPB_BytsPerSec;
    u32TempFatTableOffsetSectorNo  = pFATFileSys->u32FATTableOffsetSectorNo;

    if(u8FATType == FAT_TYPE_FAT32)
    {
        u32FatTableEntryOffset = u32ClusterNo * FAT32ENTRYSIZE;
    }
    else if(u8FATType == FAT_TYPE_FAT16)
    {
        u32FatTableEntryOffset = u32ClusterNo * FAT16ENTRYSIZE;
    }
    else
    {
        u32FatTableEntryOffset = u32ClusterNo * 3lu /2lu;
    }

    u8SectorSize = (U8)(FAT_TABLE_CACHE_LEN / u16BytePerSec);
    u32Low = u32TempFatTableOffsetSectorNo * u16BytePerSec;
    u32High = (u32TempFatTableOffsetSectorNo + u8SectorSize) * u16BytePerSec;
    // FAT table entry offset miss in FAT table
    if ( u32FatTableEntryOffset < u32Low ||
         u32FatTableEntryOffset >= u32High)
    {
         u32TempFatTableOffsetSectorNo = u32FatTableEntryOffset / u16BytePerSec;

         //printf("FAT write 2 \n");

         if (pFATFileSys->bIsFATCacheDirty)                    //<<===flush FAT table entry cross cache
         {
             FAT_FATStructureWrite(u8fsid);                          //Entry Cluster# of deleted file cross FAT table cache
         }

         //pFATFileSys = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);

         if ( !FAT_FATStructureFetch(u8fsid, u32TempFatTableOffsetSectorNo) )
         {
              __ASSERT(0);
              return FALSE;
         }
        u32Low = u32TempFatTableOffsetSectorNo * u16BytePerSec;
        u32High = (u32TempFatTableOffsetSectorNo + u8SectorSize) * u16BytePerSec;
    }

    pu8FatTable = (U8*)FCtrl_GetFatTableCacheInfo(u8fsid);

    if(pu8FatTable == NULL)
    {
        __ASSERT(0);
        return FALSE;
    }

    if(u8FATType == FAT_TYPE_FAT32)
    {
        //*(U32*)(pu8FatTable + (u32FatTableEntryOffset - u32Low)) = (u32ValueToSet);
        memcpy((pu8FatTable + (u32FatTableEntryOffset - u32Low)),&u32ValueToSet,4);
    }
    else if(u8FATType == FAT_TYPE_FAT16)
    {
        //*(U16*)(pu8FatTable + (u32FatTableEntryOffset - u32Low)) = ((U16)u32ValueToSet);
        u16Temp=(U16)u32ValueToSet;
        memcpy((pu8FatTable + (u32FatTableEntryOffset - u32Low)),&u16Temp,2);
    }
    else
    {
        if(u32FatTableEntryOffset == u32High - 1)
        {
            if((u32ClusterNo & 1) == 0)
            {
                *(pu8FatTable + (u32FatTableEntryOffset - u32Low)) = (U8)((U16)u32ValueToSet & 0x00FF);
                pFATFileSys = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);

                pFATFileSys->u8FAT12LastEntryByte &= 0xF0;
                pFATFileSys->u8FAT12LastEntryByte |= (U8)((U16)u32ValueToSet >> 8);
            }
            else
            {
                *(pu8FatTable + (u32FatTableEntryOffset - u32Low)) &= 0x0F;
                *(pu8FatTable + (u32FatTableEntryOffset - u32Low)) |= (U8)((u32ValueToSet << 4) & 0x000000FF);
                pFATFileSys = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);

                pFATFileSys->u8FAT12LastEntryByte = (U8)((U16)u32ValueToSet >> 4);
            }
        }
        else
        {
            if((u32ClusterNo & 1) == 0)
            {
                //u16EntryData = (*(U16*)(pu8FatTable + (u32FatTableEntryOffset - u32Low))) & 0xF000;
                memcpy(&u16Temp,(pu8FatTable + (u32FatTableEntryOffset - u32Low)),2);
                u16EntryData = (u16Temp & 0xF000);
                u16EntryData |= ((U16)u32ValueToSet & 0x0FFF);
            }
            else
            {
                //u16EntryData = (*(U16*)(pu8FatTable + (u32FatTableEntryOffset - u32Low))) & 0x000F;
                memcpy(&u16Temp,(pu8FatTable + (u32FatTableEntryOffset - u32Low)),2);
                u16EntryData = (u16Temp & 0x000F);
                u16EntryData |= ((U16)u32ValueToSet << 4);

            }
            //*(U16*)(pu8FatTable + (u32FatTableEntryOffset - u32Low)) = (u16EntryData);
            memcpy((pu8FatTable + (u32FatTableEntryOffset - u32Low)),&u16EntryData,2);

        }
    }

    pFATFileSys = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);

    pFATFileSys->bIsFATCacheDirty = TRUE;

    //FAT_FATStructureWrite(u8fsid);
    //printf("write value = %lx ,in cluster = %lu \n", u32ValueToSet, u32ClusterNo);
    return TRUE;
}




BOOLEAN FAT_FileDelete(FileEntry* pFileEntry)
{

    U8 u8FAT_TYPE;
    U32 cluster;

    u8FAT_TYPE = ((FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(pFileEntry->EnvironmentID))->stFAT.u8FATType;

    memcpy(&cluster,&pFileEntry->EntryID_Ext[0],sizeof(U32));

    if (!FAT_DirectoryFreeDirEntry(pFileEntry) )
    {
       __ASSERT(0);
       return FALSE;
    }

    if((u8FAT_TYPE==FAT_TYPE_FAT32)|| (cluster!=0))
    {
        FAT_FileSysStruct *pFAT_FileSys;

        if (! FAT_FATStructureFreeClusterNo(pFileEntry) )
        {
            __ASSERT(0);
            return FALSE;
        }

        pFAT_FileSys = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(pFileEntry->FileSystemID);

        //pFAT_FileSys->u32CurrentFreeCluster = *(U32*)pFileEntry->EntryID;
        memcpy(&(pFAT_FileSys->u32CurrentFreeCluster),pFileEntry->EntryID,4);
    }

    return TRUE;



}

#if FILE_SYSTEM_GET_FILENAME_BY_FILEENTRY_ENABLE
static U8 _charlow(U8 ch)
{

    if(ch >= 'A' && ch<= 'Z')
    {
        return ch+ 'a' - 'A';
    }
    else
    {
        return ch;
    }
}

U8 FAT_GetNameByFileEntry(U8 enid, FileEntry *entry, U32 destMIUAddr,U8 charLen, BOOLEAN *bIsLongName)
{
    U8 fileNameLen=0;
    U32 currentClusterNo, currentDirEntryOffset;
    FS_EnvironmentStruct *pFS_Env;
    DirEntryStruct* pDirEntry;
    U8* startEntry;
    BOOLEAN hasLongName=FALSE;
    U8 u8Loop;
    U8 u8FirstByteOfEntry;


    if(charLen==0)
    {
        *bIsLongName=FALSE; //for HasShortNameOnly
        return 0;
    }

    memcpy(&currentClusterNo, &entry->EntryID_Ext[0], sizeof(currentClusterNo));
    memcpy(&currentDirEntryOffset, &entry->EntryID_Ext[4], sizeof(currentDirEntryOffset));

    pFS_Env = msAPI_FSEnv_GetEnvironment(enid);

    if(!DirEntryIterator_Reset(pFS_Env->u8FileSystemID,currentClusterNo,currentDirEntryOffset,USB_IO_TEMP_ADDR))
    {
        __ASSERT(0);
        return 0;
    }
    pDirEntry=DirEntryIterator_GetInfo();

    startEntry =(U8*)pDirEntry;

    u8FirstByteOfEntry = *startEntry;

    if( u8FirstByteOfEntry == DIR_ENTRY_IS_FREE || u8FirstByteOfEntry == DIR_ENTRY_IS_LAST
        || (u8FirstByteOfEntry < 0x20 && u8FirstByteOfEntry != 0x05)
        || (u8FirstByteOfEntry == 0x22)
        || (0x29 < u8FirstByteOfEntry && u8FirstByteOfEntry < 0x30 && u8FirstByteOfEntry != 0x2D)
        || (0x39 < u8FirstByteOfEntry && u8FirstByteOfEntry < 0x40)
        || (0x5A < u8FirstByteOfEntry && u8FirstByteOfEntry < 0x5E)
        || (u8FirstByteOfEntry==0x7C))
    {
        FATDBG(printf("Illegal in the first bytes of DIR_Name"));
        return 0;
    }

    if(DirEntryIterator_Previous())
    {
        pDirEntry=DirEntryIterator_GetInfo();

        if(FAT_ATTRIB_LONG_NAME == *((U8*)pDirEntry+ 0xB) && (*((U8*)pDirEntry)==0x01||*((U8*)pDirEntry)==0x41))
        {
            hasLongName=TRUE;
        }
    }

    if(FALSE == *bIsLongName)
    {
        U8 fileName[12];
        U8* pData;
        BOOLEAN lowerCase=FALSE;

        pData = startEntry;
        fileNameLen = 0;

        //pDirEntry=DirEntryIterator_GetInfo(); //unused value

        memset(fileName,0,sizeof(fileName));

        lowerCase=((*(pData+0x0C)&0x8)>0);
        for(u8Loop=0;u8Loop<11;u8Loop++)
        {

            if(*(pData + u8Loop) != FS_CHAR_SPACE)
            {
                if(u8Loop==8)
                {
                    fileName[fileNameLen]=FS_CHAR_DOT;
                    fileNameLen++;

                    lowerCase=((*(pData+0x0C)&0x10) >0);
                }


                if(lowerCase)
                {
                    fileName[fileNameLen]=_charlow(*(pData + u8Loop));
                }
                else
                {
                fileName[fileNameLen] = *(pData + u8Loop);
                }

                fileNameLen++;

            }

        }

        fileNameLen=fileNameLen>charLen?charLen:fileNameLen;
        msAPI_FS_MIU_Copy( (U32)fileName, destMIUAddr,  (U32)fileNameLen);

    }
    else
    {
        U16 fileName[255];

        memset(fileName,0,sizeof(fileName));
        if(!hasLongName)
        {

            U8* pData;
            BOOLEAN lowerCase=FALSE;

            fileNameLen = 0;


            pData=startEntry;


            lowerCase=((*(pData+0x0C)&0x8 )>0);
            for(u8Loop=0;u8Loop<11;u8Loop++)
            {

                if(*(pData + u8Loop) != FS_CHAR_SPACE)
                {
                    if(u8Loop==8)
                    {
                        fileName[fileNameLen]=FS_CHAR_DOT;
                        fileNameLen++;

                        lowerCase=((*(pData+0x0C)&0x10) >0);
                    }



                    if(lowerCase)
                    {
                         fileName[fileNameLen]=_charlow(*(pData + u8Loop));
                    }
                    else
                    {
                    fileName[fileNameLen] = *(pData + u8Loop);
                    }

                    fileNameLen++;

                }

            }

            *bIsLongName = TRUE; //this flag is for HasShortNameOnly!!
        }
        else
        {
            U8 guard=0;

            pDirEntry=DirEntryIterator_GetInfo();

            while(FAT_ATTRIB_LONG_NAME == *( ((U8*)pDirEntry) + 0xB) )
            {
                //for(u8Loop=0; u8Loop<sizeof(LONG_NAME_BYTE_POS_IN_DIRENTRY); u8Loop++)
                for(u8Loop=0; u8Loop<LONG_NAME_BYTE_POS_IN_DIRENTRY_NUM; u8Loop++)
                {
                    //fileName[fileNameLen++] = ( *(U16*)((U8*)pDirEntry+LONG_NAME_BYTE_POS_IN_DIRENTRY[u8Loop])); //Eric won't use
                    memcpy(&fileName[fileNameLen],(U8 *)pDirEntry+LONG_NAME_BYTE_POS_IN_DIRENTRY[u8Loop],2);
                    if(fileName[fileNameLen] == 0)
                    {
                        break;
                    }
                    fileNameLen++;
                }



                if( ( *((U8*)pDirEntry) & FIRST_BYTE_OF_ENTRY_END_LONGNAME ) == FIRST_BYTE_OF_ENTRY_END_LONGNAME)
                {
                    break;
                }

                if(!DirEntryIterator_Previous())
                {
                    goto IS_FIRST;
                }

                //TRICKY!!
                pDirEntry=DirEntryIterator_GetInfo();

                guard++;
                if(guard==0xFF)
                {
                    __ASSERT(0);
                    break;
                }

            }

        }


IS_FIRST:

        fileNameLen=fileNameLen>charLen?charLen:fileNameLen;
        if(fileNameLen == 255)
        {
            fileName[fileNameLen-1] = 0;
        }
        else
        {
            fileName[fileNameLen] = 0;
            fileNameLen++;
        }
        msAPI_FS_MIU_Copy(  (U32)fileName, destMIUAddr,  (U32)fileNameLen*2UL);
    }
// printf("XDataExtStackCount = %bu ",msAPI_FCtrl_GetXDataExtStackCount());HERE;


    return fileNameLen;

}
#endif



#endif

#if (FILE_SYSTEM_WRITE_ENABLE)

//----fat create/write file function
// the following is fat create/write file related function......
// currently we only support fat32/fat16
extern BOOLEAN FAT_DirEntryNew_Short(U8 u8fsid, U8* shortName,U8* extName, U32 u32ClusterNo, S32 s32Offset, BOOLEAN isFile, EN_CREATE_MODE createMode);
extern U8 FAT_DirEntryNew_Long(U8 u8fsid, U16 *pu16LongName, U8 charLen, U8 u8CheckSum, U8 u8TotalEntryNum, U32 u32ClusterNo, S32 s32Offset);
extern BOOLEAN FAT_DirEntryNew_Directory(U8 u8fsid, FileEntry *pFileToSet, U32 u32ClusterNo);
extern U8 FAT_FileCreateCheckName(U16 *pu16LongName, U8 charLen);
extern U8 FAT_ClearCluster(U8 u8fsid, U32 u32ClusterNo);
extern S32 FAT_Cache_FileWriteBegin(U8 handle,U32 u32SrcBufAddr, U32 buffLen);
extern BOOLEAN ConvertLongFileNameToShort(U8* shortName,U16* longName,U8 longNameLength);
extern BOOLEAN ConvertLongFileNameToShort_Short(U8* shortName,U16* longName,U8 longNameLength);
extern BOOLEAN FAT_IsLongName(U16 *pu16LongName, U8 charLen);


U32 FAT_FATStructureGetFreeCluster(U8 u8fsid)
{
    FAT_FileSysStruct *pFAT_FileSys;
    U32 u32FreeClusterNo, u32CurrentClusterNo, u32NextClusterNo;
    //U32 u32CurrentFreeClusterNo;
    U32 u32FATTotalClusterNo;
    U32 i;
    BOOLEAN bIsFound = FALSE;
    U32 u32RootDirStartClusterNo;
    // get FAT file system

    /*[01]get file system=======================================================*/
    pFAT_FileSys = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);

    u32FATTotalClusterNo = pFAT_FileSys->stFAT.u32FATTotalClusterNo;
    u32CurrentClusterNo = pFAT_FileSys->u32CurrentFreeCluster;
    //printf("u32CurrentClusterNo: %LX\n", u32CurrentClusterNo);
    u32RootDirStartClusterNo = pFAT_FileSys->u32RootDirStartClusterNo;

    //scan FAT table until meet free cluster
    //while ( u32CurrentClusterNo < u32FATTotalClusterNo)
    for(i = 0; i < u32FATTotalClusterNo ; i++)
    {
        if(u32CurrentClusterNo >= (u32FATTotalClusterNo+2))  //Cluster index:  2 ~ (u32FATTotalClusterNo+2-1)
        {
            u32CurrentClusterNo = 2;
            MS_DEBUG_MSG(printf("Storage is almost full, search free cluster from beginning...\n"));
        }
        FS_RESET_WDT();

        u32NextClusterNo = FAT_FATStructureGetNextCluster(u8fsid, u32CurrentClusterNo);

        if ( u32NextClusterNo == 0x0 )
        {
            bIsFound = TRUE;
            break;
        }
        u32CurrentClusterNo++;
    }

    if(bIsFound)
    {
        u32FreeClusterNo = u32CurrentClusterNo;

        pFAT_FileSys = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);

        pFAT_FileSys->u32CurrentFreeCluster = u32FreeClusterNo;

    }
    else
    {
        u32FreeClusterNo = 0;
        MS_DEBUG_MSG(printf("Storage is full.\n"));
    }


    //printf("Get Free Cluster = %lu \n", u32FreeClusterNo);
    return u32FreeClusterNo;

}
// update new cluster to FAT table
static U32 FAT_FAT32_FATTable_Fast_Update_Block(U8 u8fsid, U32 u32StartClusterNo, U32 u32ClusterNeeded, U32 *u32FirstAllocatedCluster, U32 *u32LastAllocatedCluster)
{
    U32 u32ClusterUpdated = 0;
    U32 u32ClusterChecked = 0;
    U32 u32MaxCluster;
    FAT_FileSysStruct *pFsStruct;
    U16 u16BytePerSec;
    U32 *pu32FatTable;
    U32 u32Low;
    U32 u32High;
    U32 u32TempFatTableOffsetSectorNo;
    U8 u8SectorSize;
    BOOLEAN bIsDirty;
    U32 u32PreEntry = 0;

    pFsStruct = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);
    __ASSERT(pFsStruct->stFAT.u8FATType == FAT_TYPE_FAT32);

    u16BytePerSec=pFsStruct->stBootSector.BPB_BytsPerSec;
    bIsDirty = pFsStruct->bIsFATCacheDirty;
    u32TempFatTableOffsetSectorNo  = pFsStruct->u32FATTableOffsetSectorNo;
#if 0
    u32MaxCluster = pFsStruct->stBootSector.BPB_TotSec32/pFsStruct->stBootSector.BPB_SecPerClus;
#else
    u32MaxCluster = pFsStruct->stFAT.u32FATTotalClusterNo;
#endif



    u8SectorSize = (U8)(FAT_TABLE_CACHE_LEN / u16BytePerSec);

    u32Low = (u32TempFatTableOffsetSectorNo * u16BytePerSec)>>2;
    u32High = ((u32TempFatTableOffsetSectorNo + u8SectorSize) * u16BytePerSec)>>2;

    pu32FatTable = FCtrl_GetFatTableCacheInfo(u8fsid);

    while(1)
    {
         if(u32StartClusterNo >= u32MaxCluster)  //Cluster index:  2 ~ (u32FATTotalClusterNo+2-1)
        {
            u32StartClusterNo = 2;
        }

            //*FAT table entry offset miss in FAT table*=================================================//
           if ( u32StartClusterNo < u32Low ||
                            u32StartClusterNo >= u32High )
          {


                        if (bIsDirty)                    //<<===flush FAT table entry cross cache
                        {
                                       if(FAT_FATStructureWrite(u8fsid))                        //Entry Cluster# of deleted file cross FAT table cache
                                            bIsDirty = FALSE;
                                       else
                                       {
                                           __ASSERT(0);
                                       }
                         }
                       u32TempFatTableOffsetSectorNo = u32StartClusterNo*FAT32ENTRYSIZE / u16BytePerSec;

                        if ( !FAT_FATStructureFetch(u8fsid, u32TempFatTableOffsetSectorNo) )
                        {
                                       __ASSERT(0);
                                       break;
                         }
                        pFsStruct = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);
                        pFsStruct->u32FATTableOffsetSectorNo = u32TempFatTableOffsetSectorNo;
                        u32Low = (u32TempFatTableOffsetSectorNo * u16BytePerSec)>>2;
                        u32High = ((u32TempFatTableOffsetSectorNo + u8SectorSize) * u16BytePerSec)>>2;
             }

              //*FAT table entry offset fit in FAT table*==================================================//

              do
              {
                   if(*(pu32FatTable + u32StartClusterNo - u32Low) == 0)
                    {
                        if(u32PreEntry)
                        {
                            *(pu32FatTable + u32PreEntry - u32Low) = u32StartClusterNo;
                        }
                        else
                        {
                             *u32FirstAllocatedCluster = u32StartClusterNo;
                        }
                        *(pu32FatTable + u32StartClusterNo - u32Low) =  0x0FFFFFFF;
                        u32PreEntry = u32StartClusterNo;
                        *u32LastAllocatedCluster = u32StartClusterNo;
                        bIsDirty = TRUE;
                        u32ClusterUpdated++;
                    }
                    u32StartClusterNo = u32StartClusterNo+1;
                    if(u32StartClusterNo >= u32MaxCluster)
                           break;
                   u32ClusterChecked++;
              }while(u32StartClusterNo<u32High && u32ClusterUpdated<u32ClusterNeeded);
              if(u32ClusterUpdated)
                  break;
              if(u32ClusterChecked > u32MaxCluster)
                   break;

      }
       if (bIsDirty)                    //<<===flush FAT table entry cross cache
       {
                if(!FAT_FATStructureWrite(u8fsid))
                {
                      pFsStruct = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);

                      pFsStruct->bIsFATCacheDirty = TRUE;
                       __ASSERT(0);
                 }
       }

    return u32ClusterUpdated;


}

static U32  FAT_FAT32_FATTable_Fast_Update(U8 u8fsid, U32 clusterNo, U32 u32ClusterNeeded)
{
      U32 u32CurrentClusterNo;
      U32 u32ClusterUpdated = 0;
      U32 u32FirstAllocatedCluster=0;
      U32 u32PreCluster = clusterNo;
      FAT_FileSysStruct *pFsStruct;

      if(u32PreCluster)
          u32CurrentClusterNo = u32PreCluster+1;
      else
      {
           pFsStruct = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);
           u32CurrentClusterNo = pFsStruct->u32CurrentFreeCluster;
      }

      while(u32ClusterUpdated < u32ClusterNeeded)
      {
         U32 u32Tmp, Tmp1=0;

         u32Tmp = FAT_FAT32_FATTable_Fast_Update_Block(u8fsid, u32CurrentClusterNo,
                                          u32ClusterNeeded-u32ClusterUpdated, &Tmp1, &u32CurrentClusterNo);
         if(u32Tmp == 0)
              break;
         if(u32ClusterNeeded == 1)
        {
               FAT_ClearCluster(u8fsid, Tmp1);
        }
         if(u32FirstAllocatedCluster == 0)
              u32FirstAllocatedCluster = Tmp1;

         u32ClusterUpdated += u32Tmp;
         if(u32PreCluster)
            {
               BOOLEAN _btmp = TRUE;
               _btmp = FAT_SetClusterNo(u8fsid, u32PreCluster, Tmp1);
            }
         u32PreCluster = u32CurrentClusterNo;
         u32CurrentClusterNo++;
      }
      if( u32ClusterUpdated)
      {
           pFsStruct = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);
           pFsStruct->u32CurrentFreeCluster = u32CurrentClusterNo+1;
           pFsStruct->u32FSI_Free_Count -= u32ClusterUpdated;
           FAT_FATFsinfoUpdate(u8fsid);
      }
      return u32FirstAllocatedCluster;
}

// update new cluster to FAT table
U32 FAT_FATTableUpdate(U8 u8fsid, U32 clusterNo, U32 u32ClusterNeeded)
{
    U32 u32TmpCluster, i;
    FAT_FileSysStruct *pFsStruct;
    U32 u32MaxCluster;
    U32 u32FreeCluster=0, u32Return=0;
    EN_FAT_TYPE u8FATType;

    pFsStruct = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);
    u8FATType = pFsStruct->stFAT.u8FATType;

    if(pFsStruct->stBootSector.BPB_TotSec16)
    {
        u32MaxCluster = pFsStruct->stBootSector.BPB_TotSec16/pFsStruct->stBootSector.BPB_SecPerClus;
    }
    else
    {
        u32MaxCluster = pFsStruct->stBootSector.BPB_TotSec32/pFsStruct->stBootSector.BPB_SecPerClus;
    }


    if(u8FATType == FAT_TYPE_FAT32)
    {
         return FAT_FAT32_FATTable_Fast_Update(u8fsid, clusterNo, u32ClusterNeeded);
    }

    u32FreeCluster =clusterNo;
    for(i = 0; i < u32ClusterNeeded; i++)
    {
        u32TmpCluster = u32FreeCluster;
        u32FreeCluster = FAT_FATStructureGetFreeCluster(u8fsid);
        if(u32FreeCluster == 0)
        {
            return 0;
        }


        if(i == 0)
        {
            u32Return = u32FreeCluster;
        }

        // boundary check
        if(u32FreeCluster >= u32MaxCluster)
        {
            return 0;
        }


        if(u32ClusterNeeded == 1)
        {
            FAT_ClearCluster(u8fsid, u32FreeCluster);
        }

        if(u32TmpCluster!=0)
        {
            if(!FAT_SetClusterNo(u8fsid, u32TmpCluster, u32FreeCluster))
            {
                __ASSERT(0);
                return FALSE;
            }
        }

        if(!FAT_SetClusterNo(u8fsid, u32FreeCluster, 0xFFFFFFF))
        {
            __ASSERT(0);
            return FALSE;
        }
    }


    if(!FAT_FATStructureWrite(u8fsid))
    {
         __ASSERT(0);

        return FALSE;
    }
#if 0
    if(u8FATType == FAT_TYPE_FAT32)
    {
        //update FSInfo here
        U32 u32FSI_Nxt_Free = FAT_FATStructureGetFreeCluster(u8fsid);

        if(u32FSI_Nxt_Free==0)
        {
            u32FSI_Nxt_Free=0xFFFFFFFF;
        }

        FATDBG(printf("FAT_FATTableUpdate() : Update FSInfo\n",u32ClusterNeeded););


        if((pFsStruct->u32FSI_Free_Count-u32ClusterNeeded)>0)
        {
               pFsStruct->u32FSI_Free_Count -= u32ClusterNeeded;
        }
        else
        {
               pFsStruct->u32FSI_Free_Count = 0;
        }

        pFsStruct->u32FSI_Nxt_Free=u32FSI_Nxt_Free;
        FATDBG(printf("FAT_FATTableUpdate() : u32ClusterNeeded  = %lu\n",u32ClusterNeeded););
        FATDBG(printf("FAT_FATTableUpdate() : u32FSI_Free_Count = %lx\n",pFsStruct->u32FSI_Free_Count););
        FATDBG(printf("FAT_FATTableUpdate() : u32FSI_Nxt_Free   = %lx\n\n",pFsStruct->u32FSI_Nxt_Free););

    }
#endif
    return u32Return;
}
static EN_ENTRY_CREATE_RESULT FAT_DirEntryFindEmpty( U8 u8EnvironmentID, U8 u8EntryCount )
{
    DirEntryStruct * pstDirEntry;
    FAT_Environment* pFAT_Env;
    FAT_FileSysStruct *pFsStruct;
    U32 u32CurrentDirStartClusterNo, u32CurrentCluster;
    U8 firstByteOfEntry;
    U8 u8fsid;
    U16 dirEntryCacheCount, sectorPerCache;
    U8 u8FreeEntryCount = 0;
    U32 sectorNo;
    S16 dirEntryIndexInCache = 0;
    S32 dirEntryIndexInCluster = 0;
    S32 currentDirEntryIndex = 0;
    U8 u8DeviceIndex;
    U8 u8FATType;
    U32 u32RootDirStartClusterNo;
    U16 u16BPB_RootEntCnt;
    U32 dirEntryPerCluster;
    U32 u32FATTotalClusterNo;
    U8 u8CacheSectorOffset = 0;

    u8fsid = msAPI_FSEnv_GetEnvironment(u8EnvironmentID)->u8FileSystemID;

    // get FAT file system
    pFsStruct = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);

    dirEntryCacheCount = pFsStruct->u16DirEntryCacheCount;
    dirEntryPerCluster = ((U32)pFsStruct->stBootSector.BPB_BytsPerSec * pFsStruct->stBootSector.BPB_SecPerClus)/sizeof(DirEntryStruct);
    sectorPerCache = (USB_IO_TEMP_LEN/pFsStruct->stBootSector.BPB_BytsPerSec);
    u8DeviceIndex = pFsStruct->DeviceIndex;
    u8FATType = pFsStruct->stFAT.u8FATType;
    u32RootDirStartClusterNo = pFsStruct->u32RootDirStartClusterNo;
    u16BPB_RootEntCnt = pFsStruct->stBootSector.BPB_RootEntCnt;
    u32FATTotalClusterNo = pFsStruct->stFAT.u32FATTotalClusterNo;

    pFAT_Env=(FAT_Environment*)FAT_GetAddr(u8EnvironmentID, FAT_XDATA_OPTION_ENVIRONMENT);

    u32CurrentDirStartClusterNo = pFAT_Env->stCurrentDirectory.u32CurrentDirStartClusterNo;
    //For speed up, Start to search from current-cluster, not start-cluster
    u32CurrentCluster = pFAT_Env->stCurrentDirectory.u32CurrentCluster;

    if(dirEntryCacheCount == 0)
    {
        __ASSERT(0);
        FATDBG(printf("DirEntryCacheCount is Zero!\n"));
        return ENTRY_CREATE_RESULT_ERROR;
    }

    if(pFAT_Env->stCurrentDirectory.s32CurrentDirEntryIndex > 0)
    {
        currentDirEntryIndex = pFAT_Env->stCurrentDirectory.s32CurrentDirEntryIndex;
        dirEntryIndexInCluster = (pFAT_Env->stCurrentDirectory.s32CurrentDirEntryIndex%dirEntryPerCluster);
        if(dirEntryIndexInCluster >= dirEntryCacheCount)
        {
            dirEntryIndexInCache = dirEntryIndexInCluster%dirEntryCacheCount;
            u8CacheSectorOffset = (dirEntryIndexInCluster/dirEntryCacheCount)*sectorPerCache;
        }
        else
        {
            dirEntryIndexInCache = dirEntryIndexInCluster;
        }
    }

    sectorNo = FAT_FATGetSectorNo(u8fsid, u32CurrentCluster);
    sectorNo += u8CacheSectorOffset;
    if ( !msAPI_MSDCtrl_SectorRead( u8DeviceIndex, sectorNo, sectorPerCache, USB_IO_TEMP_ADDR) )
    {
        __ASSERT(0);
        return ENTRY_CREATE_RESULT_ERROR;
    }

    while(TRUE)
    {

        FS_RESET_WDT();

        //@NOTE[TRIKY CODE]:FAT16 root directory special handle
        if((u8FATType == FAT_TYPE_FAT16 || u8FATType == FAT_TYPE_FAT12) && (u32CurrentDirStartClusterNo == u32RootDirStartClusterNo))
        {

            if(dirEntryIndexInCluster >= u16BPB_RootEntCnt)
            {
                pFAT_Env=(FAT_Environment*)FAT_GetAddr(u8EnvironmentID, FAT_XDATA_OPTION_ENVIRONMENT);

                pFAT_Env->stCurrentDirectory.s32LastDirEntryIndex = currentDirEntryIndex;

                pFAT_Env->stCurrentDirectory.s16DirEntryCacheCurrentIndex = dirEntryIndexInCache;
                pFAT_Env->stCurrentDirectory.u32CurrentCluster = u32CurrentDirStartClusterNo;
                pFAT_Env->stCurrentDirectory.s32CurrentDirEntryIndex = currentDirEntryIndex;
                return ENTRY_CREATE_RESULT_FULL;
            }

        }

        /* get next cluster */
        if ( dirEntryIndexInCache >= dirEntryCacheCount)
        {
            if((dirEntryIndexInCluster >= (S32)dirEntryPerCluster) && (u32CurrentCluster != 0))
            {
                U32 u32ClusterStatus;
                U32 tmpCluster;

                tmpCluster = FAT_FATStructureGetNextCluster(u8fsid, u32CurrentCluster);
                u32ClusterStatus = FAT_FATGetClusterStatus( u8FATType, u32FATTotalClusterNo,  tmpCluster);

                if(u32ClusterStatus == FAT_CLUSTER_FINAL)
                {
                    tmpCluster = FAT_FATTableUpdate(u8fsid, u32CurrentCluster, 1);
                    if(0 == tmpCluster)
                    {
                        return ENTRY_CREATE_RESULT_FULL;
                    }
                    FATDBG(printf("Update new Cluster: %LX\n", tmpCluster););
                }
                u32CurrentCluster = tmpCluster;
                dirEntryIndexInCluster = 0;
            }

            sectorNo = FAT_FATGetSectorNo(u8fsid, u32CurrentCluster);
            sectorNo += (dirEntryIndexInCluster/dirEntryCacheCount)*sectorPerCache;
            if ( !msAPI_MSDCtrl_SectorRead( u8DeviceIndex, sectorNo, sectorPerCache, USB_IO_TEMP_ADDR) )
            {
                __ASSERT(0);
                return ENTRY_CREATE_RESULT_ERROR;
            }

            dirEntryIndexInCache=0;
        }

        /* get DirEntry */
        pstDirEntry = (DirEntryStruct xdata* )msAPI_FS_GetAddr(USB_IO_TEMP_ADDR);

        pstDirEntry += dirEntryIndexInCache;
        firstByteOfEntry = pstDirEntry->pu8DirEntryName[0];

        if(firstByteOfEntry == DIR_ENTRY_IS_FREE)
        {
            if(u8FreeEntryCount == 0)
            {
                //*update DirEntryCache index of FAT_Environment==============================================//
                pFAT_Env = (FAT_Environment*)FAT_GetAddr(u8EnvironmentID, FAT_XDATA_OPTION_ENVIRONMENT);

                pFAT_Env->stCurrentDirectory.s32LastDirEntryIndex = currentDirEntryIndex;
                pFAT_Env->stCurrentDirectory.s16DirEntryCacheCurrentIndex = dirEntryIndexInCache;
                pFAT_Env->stCurrentDirectory.u32CurrentCluster = u32CurrentCluster;
                pFAT_Env->stCurrentDirectory.s32CurrentDirEntryIndex = currentDirEntryIndex;
            }

            u8FreeEntryCount ++;
        }
        else if(firstByteOfEntry == DIR_ENTRY_IS_LAST)
        {
            //*update DirEntryCache index of FAT_Environment==============================================//
            pFAT_Env = (FAT_Environment*)FAT_GetAddr(u8EnvironmentID, FAT_XDATA_OPTION_ENVIRONMENT);

            pFAT_Env->stCurrentDirectory.s32LastDirEntryIndex = currentDirEntryIndex;
            pFAT_Env->stCurrentDirectory.s16DirEntryCacheCurrentIndex = dirEntryIndexInCache;
            pFAT_Env->stCurrentDirectory.u32CurrentCluster = u32CurrentCluster;
            pFAT_Env->stCurrentDirectory.s32CurrentDirEntryIndex = currentDirEntryIndex;

            return ENTRY_CREATE_RESULT_LAST;
        }
        else
        {
            u8FreeEntryCount = 0;
        }

        if(u8EntryCount == u8FreeEntryCount)
        {
            return ENTRY_CREATE_RESULT_FREE;
        }

        dirEntryIndexInCache ++;
        dirEntryIndexInCluster ++;
        currentDirEntryIndex ++;
    }

}


BOOLEAN FAT_DirEntryWriteDirect(U8 u8fsid,U32 startCluster,U32 u32Index,DirEntryStruct* pDirEntry)
{
    U32 sectorNo;
    S8 deviceIndex;
    U32 dirEntryCountPerSector;
    U32 dirEntryCountPerCluster;
    FAT_FileSysStruct* pFAT_FileSys;
    U32 u32BytesPerSec;
    U32 u32SectorPerCluster;
    U8 u8FATType;

    pFAT_FileSys = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);

    u8FATType = pFAT_FileSys->stFAT.u8FATType;
    u32BytesPerSec = pFAT_FileSys->stBootSector.BPB_BytsPerSec;
    u32SectorPerCluster = pFAT_FileSys->stBootSector.BPB_SecPerClus;
    deviceIndex = pFAT_FileSys->DeviceIndex;

    dirEntryCountPerSector = (u32BytesPerSec/sizeof(DirEntryStruct));
    dirEntryCountPerCluster = (dirEntryCountPerSector*u32SectorPerCluster);

    if((u8FATType == FAT_TYPE_FAT32) ||(startCluster!=0))
    {
        while(u32Index >= dirEntryCountPerCluster)
        {
            startCluster = FAT_FATStructureGetNextCluster(u8fsid,startCluster);
            if(startCluster == 0)
            {
                __ASSERT(0);
                return FALSE;
            }
            u32Index -= dirEntryCountPerCluster;
        }
    }

    //shift to sector
    sectorNo = FAT_FATGetSectorNo(u8fsid, startCluster);
    sectorNo += (u32Index/dirEntryCountPerSector);
    u32Index = (u32Index % dirEntryCountPerSector);


    if(!msAPI_MSDCtrl_SectorRead(deviceIndex,sectorNo, 1, USB_IO_TEMP_ADDR))
    {
        __ASSERT(0);
        return FALSE;
    }

    msAPI_FS_MIU_Copy(GET_DRAM_ADDR(pDirEntry), ((U32)USB_IO_TEMP_ADDR + (u32Index*sizeof(DirEntryStruct))), sizeof(DirEntryStruct));

    if(!msAPI_MSDCtrl_SectorWrite(deviceIndex,sectorNo, 1, USB_IO_TEMP_ADDR))
    {
        __ASSERT(0);
        return FALSE;
    }

    return TRUE;
}


U8 FAT_FileCreateDirEntry(U8 u8EnvironmentID, U16 *pu16LongName, U8 charLen, FileEntry *pEntryToSet, BOOLEAN bIsFile, EN_CREATE_MODE createMode)
{
    FAT_Environment* pFAT_Env;
    FAT_FileSysStruct * pFAT_FileSys;
    FS_EnvironmentStruct * pFS_Env;

    S16 s16CurrentDirEntryIndexInCache;
    U8 shortName[11];
    U32 u32CurrentDirStartClusterNo, u32RootDirStartClusterNo, u32CurrentClusterNo;
    S32 lastEntryIndexInCurrentDirectory=-1, s32DirEntryIndexInCurCluster;
    U8 u8FillEntryNum;
    U16 u16BPB_RootEntCnt;
    U8 u8FATType;
    BOOLEAN bIsLongName;
    U8 bResult;
    U32 u32dirEntryPerCluster;

    pFS_Env = msAPI_FSEnv_GetEnvironment( u8EnvironmentID );

    pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemInfo(pFS_Env->u8FileSystemID);

    u16BPB_RootEntCnt = pFAT_FileSys->stBootSector.BPB_RootEntCnt;
    u8FATType = pFAT_FileSys->stFAT.u8FATType;
    u32RootDirStartClusterNo = pFAT_FileSys->u32RootDirStartClusterNo;

    bIsLongName = FAT_IsLongName(pu16LongName, charLen);
    //Always allow long file name.
    if(1)//(bIsLongName)
    {
        u8FillEntryNum = (charLen/sizeof(LONG_NAME_BYTE_POS_IN_DIRENTRY)) + 1;
        if((charLen%sizeof(LONG_NAME_BYTE_POS_IN_DIRENTRY)) != 0)
        {
            u8FillEntryNum++;
        }
    }
    else
    {
        u8FillEntryNum = 1;
    }

    bResult = FAT_DirEntryFindEmpty(u8EnvironmentID, u8FillEntryNum);
    if(ENTRY_CREATE_RESULT_ERROR == bResult)
    {
        __ASSERT(0);
        return ENTRY_CREATE_RESULT_ERROR;
    }
    else if(ENTRY_CREATE_RESULT_FULL == bResult)
    {
        return ENTRY_CREATE_RESULT_FULL;
    }

    pFAT_Env=(FAT_Environment*)FAT_GetAddr(u8EnvironmentID, FAT_XDATA_OPTION_ENVIRONMENT);

    s16CurrentDirEntryIndexInCache = pFAT_Env->stCurrentDirectory.s16DirEntryCacheCurrentIndex;
    u32CurrentDirStartClusterNo = pFAT_Env->stCurrentDirectory.u32CurrentDirStartClusterNo;
    lastEntryIndexInCurrentDirectory = pFAT_Env->stCurrentDirectory.s32CurrentDirEntryIndex;

    u32dirEntryPerCluster = ((U32)pFAT_FileSys->stBootSector.BPB_BytsPerSec * pFAT_FileSys->stBootSector.BPB_SecPerClus)/sizeof(DirEntryStruct);
    u32CurrentClusterNo = pFAT_Env->stCurrentDirectory.u32CurrentCluster;
    s32DirEntryIndexInCurCluster = lastEntryIndexInCurrentDirectory%u32dirEntryPerCluster;
    FATDBG(printf("\n(C: %LX, P: %LX)", u32CurrentDirStartClusterNo, lastEntryIndexInCurrentDirectory););

    if((FAT_TYPE_FAT16 == u8FATType || FAT_TYPE_FAT12 == u8FATType) && (u32CurrentDirStartClusterNo == u32RootDirStartClusterNo))
    {
        if( (lastEntryIndexInCurrentDirectory >= u16BPB_RootEntCnt) ||
            ((lastEntryIndexInCurrentDirectory+u8FillEntryNum) > u16BPB_RootEntCnt))
        {
            return ENTRY_CREATE_RESULT_FULL;
        }
    }

    U8 u8Loop;
    U8 u8CheckSum = 0;

    if(bIsLongName)
    {
        if(!ConvertLongFileNameToShort_Short(shortName,pu16LongName,charLen))
        {
            __ASSERT(0);
            return ENTRY_CREATE_RESULT_ERROR;
        }
    }
    else
    {
        if(!ConvertLongFileNameToShort(shortName,pu16LongName,charLen))
        {
            __ASSERT(0);
            return ENTRY_CREATE_RESULT_ERROR;
        }
    }
    // get check sum
    for(u8Loop = 0; u8Loop < 11; u8Loop++)
    {
        if(u8CheckSum & 1)
        {
            u8CheckSum = 0x80 + (u8CheckSum >> 1) + shortName[u8Loop];
        }
        else
        {
            u8CheckSum = 0x00 + (u8CheckSum >> 1) + shortName[u8Loop];
        }
    }

    // long-name setting
    //For speed up, Start to search from current-cluster, not start-cluster
    FAT_DirEntryNew_Long(pFS_Env->u8FileSystemID, pu16LongName, charLen, u8CheckSum, (u8FillEntryNum-1), u32CurrentClusterNo, s32DirEntryIndexInCurCluster);
    lastEntryIndexInCurrentDirectory+=(u8FillEntryNum-1);
    s32DirEntryIndexInCurCluster+=(u8FillEntryNum-1);

    // short-name setting
    //For speed up, Start to search from current-cluster, not start-cluster
    FAT_DirEntryNew_Short(pFS_Env->u8FileSystemID, &shortName[0],&shortName[8], u32CurrentClusterNo, s32DirEntryIndexInCurCluster, bIsFile, createMode);

    //can long & short create should shatr this common part...
    //update index in current
    pFAT_Env=(FAT_Environment*)FAT_GetAddr(u8EnvironmentID, FAT_XDATA_OPTION_ENVIRONMENT);

    pFAT_Env->stCurrentDirectory.s32CurrentDirEntryIndex = lastEntryIndexInCurrentDirectory;
    pFAT_Env->stCurrentDirectory.s32LastDirEntryIndex = lastEntryIndexInCurrentDirectory + 1;

    //update index in cache
    s16CurrentDirEntryIndexInCache++;
    pFAT_Env->stCurrentDirectory.s16DirEntryCacheCurrentIndex = s16CurrentDirEntryIndexInCache;

    //save to FileEntry
    memset(pEntryToSet, 0, sizeof(FileEntry));
    pEntryToSet->EnvironmentID = u8EnvironmentID;
    pEntryToSet->FileSystemID = pFS_Env->u8FileSystemID;
    pEntryToSet->EntryAttrib = FAT_ATTRIB_ARCHIVE|(createMode==CREATE_MODE_NEW_ATTR_HIDDEN?FAT_ATTRIB_HIDDEN:0x00);
    pEntryToSet->EntryFileLength = 0;
    LL_assign(&pEntryToSet->FileLength, 0);
    pEntryToSet->EntryType = ENTRY_TYPE_FILE;

    memcpy(&pEntryToSet->EntryID_Ext[0], &u32CurrentDirStartClusterNo, 4);
    memcpy(&pEntryToSet->EntryID_Ext[4], &lastEntryIndexInCurrentDirectory, 4);

    return ENTRY_CREATE_RESULT_SUCCESS;

}

// create file
// return handle.
// only support 8.3 file name
// aaa.txt => aaa     txt
U8 FAT_FileCreate(U8 u8enid, U16 *pu16LongName, U8 charLen, EN_CREATE_MODE createMode)
{
    BOOLEAN bResult;
    FileEntry stFileEntry;

    if(!FAT_FileCreateCheckName(pu16LongName, charLen))
    {
        __ASSERT(0);
        return INVALID_FILE_HANDLE;
    }

    bResult = FAT_FileCreateDirEntry(u8enid, pu16LongName, charLen, &stFileEntry, TRUE, createMode);
    if(ENTRY_CREATE_RESULT_ERROR == bResult)
    {
        __ASSERT(0);
        return INVALID_FILE_HANDLE;
    }
    else if(ENTRY_CREATE_RESULT_FULL == bResult)
    {
        __ASSERT(printf("    XXXX@ FAT_FileCreate: No Free Space XXXX"));
        return INVALID_FILE_HANDLE;
    }

    return msAPI_FCtrl_FileOpen(&stFileEntry, OPEN_MODE_BINARY_FOR_READ_WRITE);
}

U8 FAT_EntryFillCluster(U8 u8FileHandle)
{
    FAT_FileHandle *pFileHandle;
    FAT_FileInode   *pFileInode;
    U8 fsid;

    pFileHandle = FAT_File_GetHandleInfo(u8FileHandle);
    pFileInode = FAT_File_GetInodeFromHandle(u8FileHandle);

    fsid=pFileHandle->pub_fileheader.FileSystemID;
    if(pFileHandle->u32FileCurrentClusterNo == 0)
    {
        pFileInode->u32FileStartClusterNo = FAT_FATTableUpdate(pFileHandle->pub_fileheader.FileSystemID, 0, 1);
        if(0 == pFileInode->u32FileStartClusterNo)
        {
            return ENTRY_CREATE_RESULT_FULL;
        }
        pFileHandle->u32FileCurrentClusterNo = pFileInode->u32FileStartClusterNo;

        // update Dir Entry
        if(!FAT_DirEntryUpdate(u8FileHandle))
        {
            __ASSERT(0);
            return ENTRY_CREATE_RESULT_ERROR;
        }
    }

    return ENTRY_CREATE_RESULT_SUCCESS;
}


#if FILE_SYSTEM_FOLDER_CREATE_ENABLE
U8 FAT_FolderCreate(U8 u8enid, U16 *pu16LongName, U8 charLen)
{
    U8 bResult;
    U32 u32CurrentClusterNo;
    FS_EnvironmentStruct * pFS_Env;
    FAT_FileInode *pFileInode;
    FileEntry stFileEntry;
    U8 handle;

    pFS_Env = msAPI_FSEnv_GetEnvironment( u8enid );

    if(!FAT_FileCreateCheckName(pu16LongName, charLen))
    {
        __ASSERT(0);
        return INVALID_FILE_HANDLE;
    }

    bResult = FAT_FileCreateDirEntry(u8enid, pu16LongName, charLen, &stFileEntry, FALSE, CREATE_MODE_NEW);
    if(ENTRY_CREATE_RESULT_ERROR == bResult)
    {
        __ASSERT(0);
        return INVALID_FILE_HANDLE;
    }
    else if(ENTRY_CREATE_RESULT_FULL == bResult)
    {
        __ASSERT(printf("    XXXX@ FAT_FolderCreate: No Free Space XXXX"));
        return INVALID_FILE_HANDLE;
    }

    // short-name setting
    handle = msAPI_FCtrl_FileOpen(&stFileEntry, OPEN_MODE_BINARY_FOR_READ_WRITE);
    bResult = FAT_EntryFillCluster(handle);
    if(ENTRY_CREATE_RESULT_ERROR == bResult)
    {
        //__ASSERT(0);
        __ASSERT(printf("    XXXX@ FAT_FolderCreate: Unknown Error Occurs XXXX"));
        return INVALID_FILE_HANDLE;
    }
    else if(ENTRY_CREATE_RESULT_FULL == bResult)
    {
        //__ASSERT(0);
        __ASSERT(printf("    XXXX@ FAT_FolderCreate: No Free Space XXXX"));
        return INVALID_FILE_HANDLE;
    }

    pFileInode = FAT_File_GetInodeFromHandle(handle);
    u32CurrentClusterNo = pFileInode->u32FileStartClusterNo;
    //printf("\nu32CurrentClusterNo: %LX", u32CurrentClusterNo);
    memcpy(&stFileEntry.EntryID, &u32CurrentClusterNo, OPEN_MODE_EMPTY_FOR_WRITE);
    //FAT_ReturnXData();
    memcpy(&(pFileInode->pub_inodeheader.stFileEntry), &stFileEntry, sizeof(FileEntry));


    FAT_ClearCluster(pFS_Env->u8FileSystemID, u32CurrentClusterNo);
    FAT_DirEntryNew_Directory(pFS_Env->u8FileSystemID, &stFileEntry, u32CurrentClusterNo);


    return handle;
}
#endif


U32 FAT_FileWrite(U8 u8FileHandle, U32 u32SrcBufAddr, U32 u32BufferLen)
{

    //*Note: file read unit=> sector*//
    FAT_FileHandle * pstFAT_FileHandle;
    FAT_FileSysStruct *pFsStruct;
    U32 u32ProcessByteLength = 0;
    U32 u32WriteSectorCnt, u32WriteByteCnt;
    U16 u16BytePerSec;
    U32 u32RemainSectorNum;
    U8 u8FATType;
    U32 u32FATTotalClusterNo;
    U32 u32FileTotalSize;
    U8 u8BPB_SecPerClus;
    U8 u8DeviceIndex;
    FAT_FileInode *pFATInode;
    BOOLEAN bIsClusterChainActive;
    U8 u8FatType;
    U32 u32StartSector;
    U32 u32StartClusterNO;
    U8 file_extended = 0;

    //printf("FAT_FileWrite(u8FileHandle=%u, u32SrcBufAddr=0x%X, u32BufferLen=0x%X)\n", u8FileHandle, u32SrcBufAddr, u32BufferLen);

    pstFAT_FileHandle = FAT_File_GetHandleInfo(u8FileHandle);
    pFATInode = (FAT_FileInode*)FCtrl_GetFileInodeInfo(pstFAT_FileHandle->pub_fileheader.InodeID);
   if(pFATInode == NULL)
   {
       FAT_ASSERT(0);
       return u32BufferLen;
   }

    // get FAT file system
    pFsStruct = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(pstFAT_FileHandle->pub_fileheader.FileSystemID);
    u16BytePerSec = pFsStruct->stBootSector.BPB_BytsPerSec;
    u8FATType = pFsStruct->stFAT.u8FATType;
    u32FATTotalClusterNo = pFsStruct->stFAT.u32FATTotalClusterNo;
    u8BPB_SecPerClus = pFsStruct->stBootSector.BPB_SecPerClus;
    u8DeviceIndex = pFsStruct->DeviceIndex;
     u8FatType=pFsStruct->stFAT.u8FATType;

   u32FileTotalSize = pFATInode->u32FileTotalSize;
   bIsClusterChainActive = pFATInode->bIsClusterChainActive;
   u32StartClusterNO = pFATInode->u32FileStartClusterNo;
   if(pstFAT_FileHandle->u32FileCurrentClusterNo == 0)
   {
        pstFAT_FileHandle->u32FileCurrentClusterNo = u32StartClusterNO;
        pstFAT_FileHandle->u16ClusterChainIndex = 0;
   }
   if((u32StartClusterNO==0 ||pstFAT_FileHandle->u32FileCurrentSectorNo==u8BPB_SecPerClus)  &&
           FAT_CLUSTER_ALLOCATED != FAT_GetNextCluster(pstFAT_FileHandle, u8BPB_SecPerClus,
                                                                  u16BytePerSec,  u8FATType, u32FATTotalClusterNo, u32BufferLen))
   {
           FAT_ASSERT(0);
           return u32BufferLen;
   }

    FAT_ASSERT(FAT_CLUSTER_ALLOCATED == FAT_FATGetClusterStatus( u8FATType, u32FATTotalClusterNo, pstFAT_FileHandle->u32FileCurrentClusterNo));
    FAT_ASSERT(u8BPB_SecPerClus >= pstFAT_FileHandle->u32FileCurrentSectorNo);

    //read head sector
    u32WriteByteCnt = pstFAT_FileHandle->u32FilePosition % u16BytePerSec;
    if(u32WriteByteCnt)
    {
        u32WriteByteCnt = u16BytePerSec - u32WriteByteCnt;
        if(u32BufferLen < u32WriteByteCnt)
        {
            u32WriteByteCnt = u32BufferLen;
        }
        u32StartSector = FAT_FATGetSectorNo( pstFAT_FileHandle->pub_fileheader.FileSystemID, pstFAT_FileHandle->u32FileCurrentClusterNo ) + pstFAT_FileHandle->u32FileCurrentSectorNo;
        //sector read
        if ( !msAPI_MSDCtrl_SectorRead( u8DeviceIndex,
            u32StartSector, 1, USB_IO_TEMP_ADDR))
        {
            FAT_ASSERT(0);
            goto FAT_WRITE_BYEBYE;
        }
        msAPI_FS_MIU_Copy (u32SrcBufAddr, USB_IO_TEMP_ADDR + pstFAT_FileHandle->u32FilePosition % u16BytePerSec, u32WriteByteCnt);
        if ( !msAPI_MSDCtrl_SectorWrite( u8DeviceIndex,
            u32StartSector, 1, USB_IO_TEMP_ADDR))
        {
            FAT_ASSERT(0);
            goto FAT_WRITE_BYEBYE;
        }

        u32ProcessByteLength = u32WriteByteCnt;
        pstFAT_FileHandle->u32FilePosition += u32WriteByteCnt;
        if(pstFAT_FileHandle->u32FilePosition > u32FileTotalSize)
        {
               u32FileTotalSize = pstFAT_FileHandle->u32FilePosition;
               pFATInode = FAT_File_GetInodeFromHandle(u8FileHandle);
               pFATInode->u32FileTotalSize = u32FileTotalSize;
               pFATInode->pub_inodeheader.stFileEntry.EntryFileLength = u32FileTotalSize;
               pFATInode->pub_inodeheader.stFileEntry.FileLength.Lo = u32FileTotalSize;
               file_extended = 1;
        }

        //get next sector
        if(pstFAT_FileHandle->u32FilePosition % u16BytePerSec == 0)
                       pstFAT_FileHandle->u32FileCurrentSectorNo++;
        if(u32ProcessByteLength < u32BufferLen)
        {
            if ( pstFAT_FileHandle->u32FileCurrentSectorNo == u8BPB_SecPerClus )
            {

                if(FAT_CLUSTER_ALLOCATED != FAT_GetNextCluster(pstFAT_FileHandle, u8BPB_SecPerClus,
                                                                  u16BytePerSec,  u8FATType, u32FATTotalClusterNo, u32BufferLen-u32ProcessByteLength))
               {
                      FAT_ASSERT(0);
                      goto FAT_WRITE_BYEBYE;
               }
            }
        }
    }

    //read remain data
    //printf("write %ld, %d, %ld\n", u32ProcessByteLength, u16BytePerSec, u32BufferLen);
    while(u32ProcessByteLength  + u16BytePerSec <= u32BufferLen )
    {
        FAT_ASSERT(FAT_CLUSTER_ALLOCATED == FAT_FATGetClusterStatus( u8FATType, u32FATTotalClusterNo, pstFAT_FileHandle->u32FileCurrentClusterNo));
        FAT_ASSERT(u8BPB_SecPerClus >= pstFAT_FileHandle->u32FileCurrentSectorNo);
        u32StartSector = FAT_FATGetSectorNo( pstFAT_FileHandle->pub_fileheader.FileSystemID, pstFAT_FileHandle->u32FileCurrentClusterNo ) + pstFAT_FileHandle->u32FileCurrentSectorNo;
        u32RemainSectorNum = FAT_GetRemainSectors(pstFAT_FileHandle, u8BPB_SecPerClus);
        FAT_ASSERT(u32RemainSectorNum);

        u32WriteByteCnt = u32BufferLen - u32ProcessByteLength;
        if(u32WriteByteCnt < u32RemainSectorNum * u16BytePerSec)
        {
            u32WriteSectorCnt = u32WriteByteCnt/u16BytePerSec;
            u32WriteByteCnt = u32WriteSectorCnt * u16BytePerSec;
        }
        else
        {
            u32WriteByteCnt = u32RemainSectorNum * u16BytePerSec;
            u32WriteSectorCnt = u32RemainSectorNum;
        }

        //sector write
        //printf("write %ld %ldsectors\n", u32StartSector, u32WriteSectorCnt);
        if ( !msAPI_MSDCtrl_SectorWrite( u8DeviceIndex,
            u32StartSector, u32WriteSectorCnt, u32SrcBufAddr + u32ProcessByteLength))
        {
            FAT_ASSERT(0);

            goto FAT_WRITE_BYEBYE;
        }

        u32ProcessByteLength += u32WriteByteCnt;
        //printf("u32ProcessByteLength=%u\n", u32ProcessByteLength);

        pstFAT_FileHandle->u32FilePosition += u32WriteByteCnt;

        if(pstFAT_FileHandle->u32FilePosition > u32FileTotalSize)
        {
               u32FileTotalSize = pstFAT_FileHandle->u32FilePosition;
               pFATInode->u32FileTotalSize = u32FileTotalSize;
               pFATInode->pub_inodeheader.stFileEntry.EntryFileLength = u32FileTotalSize;
               pFATInode->pub_inodeheader.stFileEntry.FileLength.Lo = u32FileTotalSize;
               file_extended = 1;
        }

        FAT_StepSectors(pstFAT_FileHandle, u32WriteSectorCnt, u8BPB_SecPerClus);

        if ( pstFAT_FileHandle->u32FileCurrentSectorNo==u8BPB_SecPerClus&&u32BufferLen-u32ProcessByteLength)
        {
            if(FAT_CLUSTER_ALLOCATED != FAT_GetNextCluster(pstFAT_FileHandle, u8BPB_SecPerClus,
                                                              u16BytePerSec,  u8FATType, u32FATTotalClusterNo, u32BufferLen-u32ProcessByteLength))
            {
                FAT_ASSERT(0);
                goto FAT_WRITE_BYEBYE;
            }
        }

    }


    //read tail sector
    if(u32ProcessByteLength < u32BufferLen)
    {
        u32StartSector = FAT_FATGetSectorNo( pstFAT_FileHandle->pub_fileheader.FileSystemID, pstFAT_FileHandle->u32FileCurrentClusterNo ) + pstFAT_FileHandle->u32FileCurrentSectorNo;
        u32WriteByteCnt = u32BufferLen - u32ProcessByteLength;
        //sector read
        if ( !msAPI_MSDCtrl_SectorRead( u8DeviceIndex,
            u32StartSector, 1, USB_IO_TEMP_ADDR))
        {
            FAT_ASSERT(0);
            goto FAT_WRITE_BYEBYE;
        }

        msAPI_FS_MIU_Copy (u32SrcBufAddr + u32ProcessByteLength, USB_IO_TEMP_ADDR,  u32WriteByteCnt);

        if ( !msAPI_MSDCtrl_SectorWrite( u8DeviceIndex,
            u32StartSector, 1, USB_IO_TEMP_ADDR))
        {
            FAT_ASSERT(0);
            goto FAT_WRITE_BYEBYE;
        }

        u32ProcessByteLength += u32WriteByteCnt;
        pstFAT_FileHandle->u32FilePosition += u32WriteByteCnt;
        if(pstFAT_FileHandle->u32FilePosition > u32FileTotalSize)
        {
               u32FileTotalSize = pstFAT_FileHandle->u32FilePosition;
               pFATInode->u32FileTotalSize = u32FileTotalSize;
               pFATInode->pub_inodeheader.stFileEntry.EntryFileLength = u32FileTotalSize;
               pFATInode->pub_inodeheader.stFileEntry.FileLength.Lo = u32FileTotalSize;
               file_extended = 1;
        }
    }

 FAT_WRITE_BYEBYE:
    if(file_extended && !FAT_DirEntryUpdate(u8FileHandle))
    {
        FAT_ASSERT(0);
    }

    return u32BufferLen - u32ProcessByteLength;

}
#endif

#if FILE_SYSTEM_GET_VOLUME_LABEL_ENABLE
// return the length of volume label
U8 FAT_DirEntryFindVolumeLabel(U8 u8DriveIndex, U16 *VolLabName, U8 VolLabNameLen)
{
    DirEntryStruct * pstDirEntry;
    FAT_FileSysStruct *pFsStruct;
    U32 u32CurrentDirStartClusterNo, u32CurrentCluster;
    U8 pu8DirEntryVolumeLabel[DIR_ENTRY_NAME_LEN+DIR_ENTRY_EXT_NAME_LEN+1];   //Add 1 byte to protect over-range reading!
    U8 firstByteOfEntry;
    U8 u8DIR_Attr;
    U8 u8fsid;
    U16 dirEntryCacheCount, sectorPer4K;
    U32 sectorNo;
    S16 dirEntryIndexInCache = 0;
    S32 dirEntryIndexInCluster = 0;
    S32 currentDirEntryIndex = 0;
    U8 u8DeviceIndex;
    U8 u8FATType;
    U32 u32RootDirStartClusterNo;
    U16 u16BPB_RootEntCnt;
    U32 dirEntryPerCluster;
    U32 u32FATTotalClusterNo;
    u8fsid = u8DriveIndex;

    // get FAT file system
    pFsStruct = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);

    dirEntryCacheCount = pFsStruct->u16DirEntryCacheCount;
    dirEntryPerCluster = ((U32)pFsStruct->stBootSector.BPB_BytsPerSec * pFsStruct->stBootSector.BPB_SecPerClus)/sizeof(DirEntryStruct);
    sectorPer4K = (0x1000/pFsStruct->stBootSector.BPB_BytsPerSec);
    u8DeviceIndex = pFsStruct->DeviceIndex;
    u8FATType = pFsStruct->stFAT.u8FATType;
    u32RootDirStartClusterNo = pFsStruct->u32RootDirStartClusterNo;
    u16BPB_RootEntCnt = pFsStruct->stBootSector.BPB_RootEntCnt;
    u32FATTotalClusterNo = pFsStruct->stFAT.u32FATTotalClusterNo;

    u32CurrentDirStartClusterNo=u32RootDirStartClusterNo;
    u32CurrentCluster=u32RootDirStartClusterNo;

    sectorNo = FAT_FATGetSectorNo(u8fsid, u32CurrentCluster);

    if(dirEntryCacheCount == 0)
    {
        __ASSERT(0);
        FATDBG(printf("DirEntryCacheCount is Zero!\n"));
        return ENTRY_CREATE_RESULT_ERROR;
    }

    if ( !msAPI_MSDCtrl_SectorRead( u8DeviceIndex, sectorNo, sectorPer4K, USB_IO_TEMP_ADDR) )
    {
        __ASSERT(0);
        return ENTRY_CREATE_RESULT_ERROR;
    }

    while(TRUE)
    {
        FS_RESET_WDT();

        //@NOTE[TRIKY CODE]:FAT16 root directory special handle
        if((u8FATType == FAT_TYPE_FAT16 || u8FATType == FAT_TYPE_FAT12) && (u32CurrentDirStartClusterNo == u32RootDirStartClusterNo))
        {
            if(dirEntryIndexInCluster >= u16BPB_RootEntCnt)
            {
                //could not find volume label entry
                return 0;
            }
        }

        /* get next cluster */
        if ( dirEntryIndexInCache >= dirEntryCacheCount)
        {
            if((dirEntryIndexInCluster >= (S32)dirEntryPerCluster) && (u32CurrentCluster != 0))
            {
                U32 u32ClusterStatus;
                U32 tmpCluster;

                tmpCluster = FAT_FATStructureGetNextCluster(u8fsid, u32CurrentCluster);
                u32ClusterStatus = FAT_FATGetClusterStatus( u8FATType, u32FATTotalClusterNo,  tmpCluster);

                if(u32ClusterStatus == FAT_CLUSTER_FINAL)
                {
                    //at the end of RootDirectory and could find volume label entry
                    return 0;
                }
                u32CurrentCluster = tmpCluster;
                dirEntryIndexInCluster = 0;
            }

            sectorNo = FAT_FATGetSectorNo(u8fsid, u32CurrentCluster);
            sectorNo += (dirEntryIndexInCluster/dirEntryCacheCount)*sectorPer4K;
            if ( !msAPI_MSDCtrl_SectorRead( u8DeviceIndex, sectorNo, sectorPer4K, USB_IO_TEMP_ADDR) )
            {
                __ASSERT(0);
                return ENTRY_CREATE_RESULT_ERROR;
            }

            dirEntryIndexInCache=0;
        }

        /* get DirEntry */
        pstDirEntry = (DirEntryStruct xdata* )msAPI_FS_GetAddr(USB_IO_TEMP_ADDR);

        pstDirEntry += dirEntryIndexInCache;
        firstByteOfEntry = pstDirEntry->pu8DirEntryName[0];
        u8DIR_Attr = pstDirEntry->u8DirEntryAttrib;

        if( (firstByteOfEntry!=DIR_ENTRY_IS_FREE)&&
            (firstByteOfEntry!=DIR_ENTRY_NAME_ACTUALLY_E5)&&
            (firstByteOfEntry!=DIR_ENTRY_IS_LAST)&&
            (u8DIR_Attr==FAT_ATTRIB_VOLUME_ID))
        {
            U8 i=10,j=0;
            U8 u8VolLabNameLenTemp=0;
            VolLabNameLen=VolLabNameLen>11?11:VolLabNameLen;

            FATDBG(printf("Got it ! Find Volume Label Entry\n"));
            pstDirEntry = (DirEntryStruct xdata* )msAPI_FS_GetAddr(USB_IO_TEMP_ADDR);

            pstDirEntry += dirEntryIndexInCache;
            memset(pu8DirEntryVolumeLabel,0,(DIR_ENTRY_NAME_LEN+DIR_ENTRY_EXT_NAME_LEN+1));  //Add 1 byte to protect over-range reading!
            memcpy(&pu8DirEntryVolumeLabel[0],pstDirEntry->pu8DirEntryName,DIR_ENTRY_NAME_LEN);
            memcpy(&pu8DirEntryVolumeLabel[DIR_ENTRY_NAME_LEN],pstDirEntry->ps8DirEntryExtName,DIR_ENTRY_EXT_NAME_LEN);

            //truncate spaces at the end.
            while(i>0)
            {
                if(pu8DirEntryVolumeLabel[i]!=0x20)
                {
                    break;
                }
                i--;
            }

            //All 0x20 == empty
            if((i==0)&&(pu8DirEntryVolumeLabel[0]==0x20))
            {
                return 0;
            }

            for(j=0;j<(i+1);j++)
            {
                if(pu8DirEntryVolumeLabel[j]<0x80)
                {
                    VolLabName[u8VolLabNameLenTemp] = pu8DirEntryVolumeLabel[j];
                }
                else
                {
                    VolLabName[u8VolLabNameLenTemp] = ( ((U16)pu8DirEntryVolumeLabel[j] << 8) | pu8DirEntryVolumeLabel[j+1]);
                    j++;
                }
                u8VolLabNameLenTemp++;
                if(u8VolLabNameLenTemp>=VolLabNameLen)
                {
                    break;
                }
            }

            VolLabNameLen=VolLabNameLen>u8VolLabNameLenTemp?u8VolLabNameLenTemp:VolLabNameLen;
            VolLabName[VolLabNameLen] = 0x0000;

            return VolLabNameLen;
        }

        dirEntryIndexInCache ++;
        dirEntryIndexInCluster ++;
        currentDirEntryIndex ++;
    }

    // Nothing found
    return 0;
}
#endif

#undef MSAPI_FAT_C
