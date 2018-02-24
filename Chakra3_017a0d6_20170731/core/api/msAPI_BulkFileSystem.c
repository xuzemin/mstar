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
#define MSAPI_BULK_FILE_SYSTEM_C

#include "debug.h"

#include "datatype.h"
#include "msAPI_FS_SysInfo.h"

#if (ENABLE_BULK_FILE_SYSTEM)
#include <string.h>
#include "IOUtil.h"
#include "FSUtil.h"
#include "msAPI_FSCommon.h"
#include "msAPI_FSEnv.h"
#include "msAPI_MSDCtrl.h"
#include "msAPI_FCtrl.h"
#include "msAPI_FAT.h"
#ifdef PVR_8051 //[8051]
#include "msAPI_NTFS.h"
#else
#include "msAPI_N51FS.h"
#endif
#include "msAPI_BulkFileSystem.h"
#ifdef PVR_8051
#include "drvMIU.h"
#else
//#include "drvdma_if.h" //Chakra1
#include "MsTypes.h" //Chakra2
#include "drvBDMA.h"
#include "msAPI_Timer.h"
#endif
#include "sysinfo.h"
#include "MApp_GlobalSettingSt.h"

//************************************************************************************************************/
//0x00010001: Initial version
//0x00010002: Add MST_BKFS.EPG creation function
//0x00010003: Add swapping function on head information of index file
//0x00010004: Add bulk folder creation data time to identify if the BKFS is formatted on this disk originally
//0x00010005: Add eServiceType, u32StartDT, u32Duration to BulkFileEntry
//0x00010006: Add BULK_RWBYTES_OF_SPEED to BulkFileEntry
//0x00010007: Extend the Max. permitted number of bulk from 9999 to 65535
//0x00020007: Adjust version number to identify 8051 or aeon/mips system
//************************************************************************************************************/
//Porting Related
#if 0//def PVR_8051 //[8051]
#define BKFSSwap32(a) Swap32(a)
#define BKFSSwap16(a) Swap16(a)
#else //[aron or mips]
#if defined(MIPS_CHAKRA) || defined(ARM_CHAKRA)
#define msAPI_FS_GetXData(a) _PA2VA(msAPI_FS_GetAddr((a)<<12))
#else
#ifndef _PA2VA
#define _PA2VA
#endif
#ifndef _VA2PA
#define _VA2PA
#endif
#define msAPI_FS_GetXData(a) msAPI_FS_GetAddr((a)<<12)
#endif
#define msAPI_FS_GetXDataVA(a) msAPI_FS_GetAddr((a)<<12)  //a: virtual address

#define FAT_ReturnXData()
#define msAPI_FS_ReturnXData()
#define FCtrl_ReturnFileInodeXdata()
#define FAT_File_GetHandleXData(a) FAT_File_GetHandleInfo(a)
#define FCtrl_GetFileSystemXData(a) FCtrl_GetFileSystemInfo(a)
#define FCtrl_GetFatTableCacheXData(a) FCtrl_GetFatTableCacheInfo(a)
#define FS_ByteSwapCopy(a, b, c) memcpy(a, b, c)
#define BKFSSwap32(a) ((U32)(a))
#define BKFSSwap16(a) ((U16)(a))
#endif

//Functionality Switch Related
#define ENABLE_TO_RECORD_AS_TS_FILE     1 //Enable To Record TS File, 0: record in bulk, 1:record in ts file
#define ENABLE_TO_AUTO_RESUME_ALL_BULKS 1 //Enable To Recyle All Bulks From Deleted TS, 0: disable, 1:enable this function.
#define ENABLE_TO_BULK_FAST_SEARCH      1 //Enable To Bulk Fast Search: Search file from current directory entry, not from head.
#if (!ENABLE_TO_BULK_FAST_SEARCH)
#define msAPI_FCtrl_ResetCurrentDirEntryIndex() do{}while(0)
#endif

//Debugging Related
#define ioassert(x)  if(!(x)){__ASSERT(0);return FALSE;}
#define SPLIT_DBG(x) do{}while(0)
U8 debugFlag = 0; //can be removed
#define BKFSDBG(x) //(x)

//Bulk Related
#define INVALID_ALLOC_TBL_INDEX 0xFFFFFFFF
#define INVALID_ST_SECTOR_TBL_INDEX 0xFFFFFFFF
#define INVALID_BULK_START_SECTOR 0xFFFFFFFF
#define LENGTH_OF_IDX_FILE_NAME  12
#define LENGTH_OF_BKFS_FOLDER     8
#define LENGTH_OF_BKFS_FILE      12
#define LENGTH_OF_BKFS_EPG_FILE  12
#define BKFS_MIN_BULKID           1 //tag of bulk starts from MINBULKID
#define PARAM_OFFSET(structName, paramName)  ((U32)(&(((structName *)0)->paramName)))
#define MAX_LN_FAT_FILE_CNT 32 //max size is (4G-64M)*32
#define MAX_FAT_SEG_FILENAME_BUF_SIZE (4096-PARAM_OFFSET(BulkFileEntry, fatSegNameTBL[0]))
#define FAT_SEGMENT_FILE_SIZE ((((U32)0xFFFFFFFF)/(U32)BULK_SIZE)*(U32)BULK_SIZE)   //  4G-64M
#define BKFS_DIRTY_ALLOC_TBL    0x00000001
#define BKFS_DIRTY_ST_SECT_TBL 0x00000002
#define MAX_PERMITTED_BULK_CNT 0xFFFF

//Device/Driver Related
static U8  BKFS_DiskDriveIndex=INVALID_DRIVE_INDEX;
static U8  BKFS_DeviceID=INVALID_DEVICE_INDEX;

//Bulk Folder/Name/Index Related
static U8 code IDX_FILE_NAME[]="MST_BKFS.IDX\0";
static U8 code BKFS_FOLDER[]="_MSTBKFS\0";
static U8 code BKFS_FILE[]="MST00000.BUK\0";
static U16 name8_3_epg[]={'M','S','T','_','B','K','F','S','.','E','P','G'};
static U16 g_segFilename[MAX_FAT_SEG_FILENAME_LEN];
static U32 PoolAddress=0xFFFFFFFF;
static U32 IDX_FILE_StartSector=0xFFFFFFFF;
static U32 BKFS_SectorsPerBulk;
static U32 BKFS_TotalBulkNumber;
static BOOLEAN BKFS_Initialized=FALSE;
static EN_CREATE_BULKS_STATE _enCreateBulksState = EN_CREATE_BULKS_INIT;   //timeshift_state_machine
static U32 g_u32TotalDiskSizeMBSetToUsed = 0;
static U16 g_u16BulksToCreate = 0;
static U16 g_u16CurrentCreateBulkNum = 0;
static U32 g_BKFS_AllocTBL_Node_Number = 0;
static U32 g_BKFS_STSecTBL_Node_Number = 0;
static U16 g_u16FreeBulkCnt = 0;
static U32 g_u32CurrentAllocTBLNodeIndex= INVALID_ALLOC_TBL_INDEX;
static U32 g_u32CurrentSTSecTBLNodeIndex=  INVALID_ST_SECTOR_TBL_INDEX;
static U16 g_u16TimeShiftReservedBulkCnt = 0;
static U32 g_u32BKFS_Dirty_Flag = 0;

//FAT Related
static U32 BytesPerSector;

#define BULK_FS_MAGIC_HEADER  0x5AA50000

#define MISC_BULK_VERSION_OFFSET 0x0000           //Bulk Version: BKFS version number.
#define MISC_BULK_VERSION_SIZE   0x0004
#define MISC_STARTSECTBL_NODECNT_OFFSET 0x0004    //Start Sector Table Count: how many 4K-table does index file have.
#define MISC_STARTSECTBL_NODECNT_SIZE   0x0004
#define MISC_ALLOCTBL_NODECNT_OFFSET 0x0008       //Allocation Table Count: how many 4K-table does index file have.
#define MISC_ALLOCTBL_NODECNT_SIZE   0x0004
#define MISC_TOTAL_SIZE_USED_OFFSET 0x000C        //Total Disk Size: how many disk size does BKFS use in current disk.
#define MISC_TOTAL_SIZE_USED_SIZE   0x0004
#define MISC_TOTAL_BULK_OFFSET 0x0010             //Total Bulk Count: how many bulk(*.buk) count does BKFS have.
#define MISC_TOTAL_BULK_SIZE   0x0004
#define MISC_BULK_SPEED_OFFSET 0x0014             //BKFS Speed: speed data of this storage.
#define MISC_BULK_SPEED_SIZE   0x0002
#define MISC_BULK_RWBYTES_OF_SPEED_OFFSET 0x0016  //BKFS Speed: KBytes of Read/Write for current speed data.
#define MISC_BULK_RWBYTES_OF_SPEED_SIZE   0x0002
#define MISC_RESERVED_BULKCNT_OFFSET 0x0018       //Reserved Bulk Count: reserved bulk count for timeshift function.
#define MISC_RESERVED_BULKCNT_SIZE   0x0002
#define MISC_RESERVED_SPACEMB_OFFSET 0x001A       //Reserved Disk Space: how many disk size(MB) does BKFS reserve for timeshift function.
#define MISC_RESERVED_SPACEMB_SIZE   0x0004
#define MISC_BULK_INDEXMAX_OFFSET 0x001E          //Max. Bulk File Index: the maximum index number of used bulk file entry, this is used to save the performance of "bulk file searching" in index file.
#define MISC_BULK_INDEXMAX_SIZE   0x0002
#define MISC_USED_BULKCNT_OFFSET 0x0020           //Used Bulk Count: how many bulk that are used to store data.
#define MISC_USED_BULKCNT_SIZE   0x0002
#define MISC_BULK_FOLDER_CREATED_DT_OFFSET 0x0022 //Created Time Of Bulk Folder: used to identify if the BKFS is formatted on this disk originally.
#define MISC_BULK_FOLDER_CREATED_DT_SIZE   0x0004

//This api will change return value!!!
#define SET_MISCINFO(pBase, misc_type, src)   \
    do{__ASSERT(sizeof(src) == MISC_##misc_type##_SIZE);     \
        if (MISC_##misc_type##_SIZE == 4) {src = BKFSSwap32(src);}     \
        else {src = BKFSSwap16(src);}     \
        memcpy(((U8*)pBase)+MISC_##misc_type##_OFFSET, &src, MISC_##misc_type##_SIZE);     \
      }while(0)

#define GET_MISCINFO(dst, misc_type, pBase)   \
    do{__ASSERT(sizeof(dst) == MISC_##misc_type##_SIZE);     \
        memcpy(&dst, ((U8*)pBase)+MISC_##misc_type##_OFFSET, MISC_##misc_type##_SIZE);     \
        if (MISC_##misc_type##_SIZE == 4) dst = BKFSSwap32(dst);     \
        else dst = BKFSSwap16(dst);     \
      }while(0)

//to keep API clear
extern U32 FAT_FATStructureGetNextCluster( U8 u8fsid, U32 u32DirEntryClusterNo );
static U32 BKFS_GetTotalBulkNumber(void);
BOOLEAN BKFS_GetBulkTBLSize(U32 *pTotalSTSectTBL_Cnt, U32 *pTotalAllocTBL_Cnt);

#if 0
void BKFS_PrintAllHandles(void);
#endif
typedef struct
{
    U16                BulkFileID;
    U16                StartBulkID;
    BOOLEAN            RingMode;
    U8                 uFatSegTsFileCnt; //splitted ts file count
    U16                fatSegTSFileNameOffset[MAX_LN_FAT_FILE_CNT];//offset int array fatSegNameTBL
    EN_BKF_OPEN_MODE   OpenMode;
    U32                RingStartPosition;
    LongLong           FileLength;
    LongLong           RingSize; //maximum 0x100000000
//////////////////////////
/*The following is for BulkFile Info*/
    MEMBER_SERVICETYPE eServiceType;
    U32                u32StartDT;
    U32                u32Duration;
    U16                ProgramName[PVR_MAX_PROGRAM_NAME_LEN];
    U16                ChannelName[PVR_MAX_CHANNEL_NAME_LEN];
    U16                ProgramDesc[PVR_MAX_PROGRAM_DESC_LEN];
//////////////////////////
    U16                FileName[256];
    U16                fatSegNameTBL[1];  //fatSegNameTBL must be put at tail of BulkFileEntry structure
}BulkFileEntry;

typedef struct
{
    U8 HandleID;
    U16 BulkFileID;
    LongLong FileLength;
    LongLong Position;
    EN_BKF_OPEN_MODE OpenMode;
    U16 CurrentBulkID;
    U32 CurrentBulkSectorNO;
    U32 CurrentSectorOffset;
    BOOLEAN RingMode;
    LongLong RingSize; //maximum 0x100000000
    U32 RingStartPosition;

}BulkFileHandle;

extern U32 FAT_FATGetSectorNo( U8 u8fsid, U32 u32ClusterNo );
extern BOOLEAN FAT_DirEntryUpdate(U8 u8Filehandle);
extern BOOLEAN FAT_EntryFillCluster(U8 u8FileHandle);
extern FAT_FileInode *FAT_File_GetInodeFromHandle(U8 u8FileHandleID);
#ifdef PVR_8051 //[8051]
extern void FCtrl_ReturnFileInodeXdata(void);
#endif

U8 msAPI_BKFS_GetDriveIndex(void)
{
    return BKFS_DiskDriveIndex;
}

U8 msAPI_BKFS_GetDeviceIndex(void)
{
    return BKFS_DeviceID;
}

BOOLEAN msAPI_BKFS_IsInitialized(void)
{
    BKFSDBG(printf("BKFS_Initialized [%bu], BKFS_DeviceID [%bu], BKFS_DiskDriveIndex [%bu]\n", BKFS_Initialized, BKFS_DeviceID, BKFS_DiskDriveIndex));
    if(BKFS_Initialized==TRUE && BKFS_DiskDriveIndex!=INVALID_DRIVE_INDEX
                                                         &&  BKFS_DeviceID!=INVALID_DEVICE_INDEX)
        return TRUE;

    return FALSE;
}


///////////////////////////////////////////////////////////////////////
//1. Trim the FAT32 Record File entry start cluster to zero
//with out release  cluster chain in FAT table
//because cluster of Record files is reused by Bulk File, here release cluster chain is forbidden.
//2.Trim FAT32 Record File length to zero
///////////////////////////////////////////////////////////////////////
static BOOLEAN BKFS_TrimFAT32RecordFile(U8 u8Handle)
{
    FAT_FileInode *pFileInode;
    if(u8Handle != INVALID_FILE_HANDLE)
        return FALSE;
    pFileInode = FAT_File_GetInodeFromHandle( u8Handle);
    pFileInode->u32FileStartClusterNo = 0;
    pFileInode->u32FileTotalSize = 0;
    FCtrl_ReturnFileInodeXdata();
    //Always need to call msAPI_FCtrl_FileClose() continually to update data on physical disk.

    return TRUE;
}


//It never return XDATA!!
static BulkFileHandle* BKFS_GetBulkFileHandleXDATA(void)
{
    return (BulkFileHandle xdata*)msAPI_FS_GetXData(BULK_FILE_HANDLE_ADDR>>12);
}

//It never return XDATA!!
static BulkFileEntry* BKFS_GetBulkFileEntryXDATA(U16 bulkFileID)
{
    BulkFileEntry* pBulkFile;
    U32 sector=0xFFFFFFFF;
    U8 u8DeviceID = msAPI_BKFS_GetDeviceIndex();

    if(bulkFileID==0)
    {
        __ASSERT(0);
        return NULL;
    }

    if(bulkFileID>MAX_BULK_FILE_ID)
    {
        __ASSERT(0);
        return NULL;
    }

    pBulkFile=(BulkFileEntry xdata*)msAPI_FS_GetXData(BULK_FILE_ENTRY_ADDR>>12);

    if(pBulkFile->BulkFileID!=bulkFileID)
    {
        sector= IDX_FILE_StartSector
               +(IDX_HEAD_SIZE/BytesPerSector)
               +(g_BKFS_AllocTBL_Node_Number*IDX_ALLOCATION_TABLE_NODE_SIZE/BytesPerSector)
               +(g_BKFS_STSecTBL_Node_Number*IDX_BULK_START_SECTOR_TABLE_NODE_SIZE/BytesPerSector)
               +(bulkFileID*BULK_FILE_ENTRY_SIZE/BytesPerSector);

        if(!msAPI_MSDCtrl_SectorRead(u8DeviceID, sector,(BULK_FILE_ENTRY_SIZE/BytesPerSector),_PA2VA(BULK_FILE_ENTRY_ADDR)))
        {
            __ASSERT(0);
            return NULL;
        }
    }

    return pBulkFile;
}

/*
//If wanna get continuous bulk numbers, open it.
// 0 ~ 1023
static U16 BKFS_GetContinuousFreeBulkCnt(void)
{
    U16* pu16=NULL;
    U16 i=1;
    U16 u16BulkCnt = 0;

    pu16=(U16 xdata*)msAPI_FS_GetXData(ALLOCATION_TABLE_ADDR>>12);
    for(i=1;i<(BKFS_TotalBulkNumber+1);i++)
    {
        if(pu16[i]==0x0)
            u16BulkCnt++;
        else if (u16BulkCnt == 0)
            continue;
        else
        {
            msAPI_FS_ReturnXData();
            return u16BulkCnt;
        }
    }

    msAPI_FS_ReturnXData();
    return u16BulkCnt;
}*/
static BOOLEAN BKFS_WriteAllocationTable(void)
{
    if(g_u32BKFS_Dirty_Flag & BKFS_DIRTY_ALLOC_TBL)
   {
      U8 u8DeviceID = msAPI_BKFS_GetDeviceIndex();
      U8 u8SectorCnt = (IDX_ALLOCATION_TABLE_NODE_SIZE/BytesPerSector);
      U32 sectorAddr= IDX_FILE_StartSector
                    +(IDX_HEAD_SIZE/BytesPerSector)
                    +(g_BKFS_STSecTBL_Node_Number*IDX_BULK_START_SECTOR_TABLE_NODE_SIZE/BytesPerSector);

        __ASSERT(g_u32CurrentAllocTBLNodeIndex!=INVALID_ALLOC_TBL_INDEX
              && g_u32CurrentAllocTBLNodeIndex<g_BKFS_AllocTBL_Node_Number);
        g_u32BKFS_Dirty_Flag &= ~BKFS_DIRTY_ALLOC_TBL;
        return msAPI_MSDCtrl_SectorWrite(u8DeviceID, sectorAddr+u8SectorCnt*g_u32CurrentAllocTBLNodeIndex,
                             (IDX_ALLOCATION_TABLE_NODE_SIZE/BytesPerSector), _PA2VA(ALLOCATION_TABLE_ADDR));
   }
    return TRUE;
}
// 0 ~ 1023

static U16 BKFS_GetFreeBulkID(U16 u16MinBulkID)
{
    U16* pu16=NULL;
    U16 i;
    pu16=(U16 xdata*)msAPI_FS_GetXData(ALLOCATION_TABLE_ADDR>>12);

    for(i=u16MinBulkID;i<=BKFS_TotalBulkNumber;i++)
    {
         U16 bulkID = i;
         if((bulkID/(IDX_ALLOCATION_TABLE_NODE_SIZE/2)) != g_u32CurrentAllocTBLNodeIndex)
         {
              U8 u8DeviceID = msAPI_BKFS_GetDeviceIndex();
              U8 u8SectorCnt = (IDX_ALLOCATION_TABLE_NODE_SIZE/BytesPerSector);
              U32 sectorAddr= IDX_FILE_StartSector
                        +(IDX_HEAD_SIZE/BytesPerSector)
                         +(g_BKFS_STSecTBL_Node_Number*IDX_BULK_START_SECTOR_TABLE_NODE_SIZE/BytesPerSector)+u8SectorCnt*g_u32CurrentAllocTBLNodeIndex;
              BKFS_WriteAllocationTable();
              g_u32CurrentAllocTBLNodeIndex = (bulkID/(IDX_ALLOCATION_TABLE_NODE_SIZE/2));
              sectorAddr = IDX_FILE_StartSector +(IDX_HEAD_SIZE/BytesPerSector)+(g_BKFS_STSecTBL_Node_Number*IDX_BULK_START_SECTOR_TABLE_NODE_SIZE/BytesPerSector)
                                      +u8SectorCnt*g_u32CurrentAllocTBLNodeIndex;
               if(FALSE == msAPI_MSDCtrl_SectorRead(u8DeviceID, sectorAddr, u8SectorCnt, _PA2VA(ALLOCATION_TABLE_ADDR)))
               {
                        g_u32CurrentAllocTBLNodeIndex = INVALID_ALLOC_TBL_INDEX;
                        __ASSERT(0);
                        msAPI_FS_ReturnXData();
                        return INVALID_BK_ID;
               }

          }
         bulkID %= (IDX_ALLOCATION_TABLE_NODE_SIZE/2);

         if(pu16[bulkID]==0x0)
         {
            msAPI_FS_ReturnXData();
            return i;
         }
    }

    msAPI_FS_ReturnXData();
    return INVALID_BK_ID;
}

static U16 BKFS_GetFreeBulkFileEntryID(void)
{
    BulkFileEntry* pBulkFile=NULL;
    U8 u8DeviceID = msAPI_BKFS_GetDeviceIndex();

    U16 i=1;
    U32 sector=IDX_FILE_StartSector
               +(IDX_HEAD_SIZE/BytesPerSector)
               +(g_BKFS_AllocTBL_Node_Number*IDX_ALLOCATION_TABLE_NODE_SIZE/BytesPerSector)
               +(g_BKFS_STSecTBL_Node_Number*IDX_BULK_START_SECTOR_TABLE_NODE_SIZE/BytesPerSector);

    for(i=1;i<(MAX_BULK_FILE_ID+1);i++)
    {
        ioassert(msAPI_MSDCtrl_SectorRead(u8DeviceID, sector+((U32)i*BULK_FILE_ENTRY_SIZE)/BytesPerSector,(BULK_FILE_ENTRY_SIZE/BytesPerSector),_PA2VA(IO_TEMP_ADDR)));
        pBulkFile=(BulkFileEntry xdata*)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);

        if(pBulkFile->BulkFileID==0)
        {
            U16 u16MaxUsedBulkFileEntryIndex = msAPI_BKFS_GetMaxUsedBulkFileEntryIndex();
            if (i > u16MaxUsedBulkFileEntryIndex)
            {
                if (!msAPI_BKFS_SetMaxUsedBulkFileEntryIndex(i))
                {
                    __ASSERT(0);
                }
            }
            msAPI_FS_ReturnXData();
            return i;
        }

        msAPI_FS_ReturnXData();

    }
    return INVALID_BULK_FILE_ID;
}


static U8 BKFS_GetFreeHandleID(void)
{
    U8 i=0;
    BulkFileHandle* pBKFHandle=(BulkFileHandle xdata*)msAPI_FS_GetXData(BULK_FILE_HANDLE_ADDR>>12);

    for(i=0;i<MAX_BULK_FILE_HANDLE_NUM;i++)
    {
        if(pBKFHandle[i].HandleID==INVALID_FILE_HANDLE)
        {
            msAPI_FS_ReturnXData();
            return i;
        }
    }
    msAPI_FS_ReturnXData();
    return INVALID_FILE_HANDLE;
}

static BOOLEAN BKFS_FetchBulkStartSectorTable(void)
{
      U8 u8DeviceID = msAPI_BKFS_GetDeviceIndex();
      U32 sectorAddr= IDX_FILE_StartSector
                    +(IDX_HEAD_SIZE/BytesPerSector);
      U8 u8SectorCnt = (IDX_BULK_START_SECTOR_TABLE_NODE_SIZE/BytesPerSector);


     if(FALSE == msAPI_MSDCtrl_SectorRead(u8DeviceID, sectorAddr, u8SectorCnt, _PA2VA(BULK_START_SECTOR_TABLE_ADDR)))
     {
               g_u32CurrentSTSecTBLNodeIndex = INVALID_ST_SECTOR_TBL_INDEX;
               return FALSE;
     }
     g_u32CurrentSTSecTBLNodeIndex = 0;
     return TRUE;
}

static U32 BKFS_GetBulkStartSector(U16 bulkID)
{
    U32* pu32=NULL;
    U32   sector;

    if((bulkID>BKFS_TotalBulkNumber) || bulkID == 0) //Bulk0 is never used
    {
        __ASSERT(0);
        return INVALID_BULK_START_SECTOR;
    }

    if(g_u32CurrentSTSecTBLNodeIndex != bulkID/(IDX_BULK_START_SECTOR_TABLE_NODE_SIZE/4))
    {
        U32 sectorAddr;
        U8 u8DeviceID = msAPI_BKFS_GetDeviceIndex();
        U8 u8SectorCnt = (IDX_BULK_START_SECTOR_TABLE_NODE_SIZE/BytesPerSector);
        g_u32CurrentSTSecTBLNodeIndex = bulkID/(IDX_BULK_START_SECTOR_TABLE_NODE_SIZE/4);
       sectorAddr= IDX_FILE_StartSector+(IDX_HEAD_SIZE/BytesPerSector)+g_u32CurrentSTSecTBLNodeIndex*u8SectorCnt;
       if(FALSE == msAPI_MSDCtrl_SectorRead(u8DeviceID, sectorAddr, u8SectorCnt, _PA2VA(BULK_START_SECTOR_TABLE_ADDR)))
       {
               g_u32CurrentSTSecTBLNodeIndex = INVALID_ST_SECTOR_TBL_INDEX;
              __ASSERT(0);
             return INVALID_BULK_START_SECTOR;
       }
    }
    bulkID %= (IDX_BULK_START_SECTOR_TABLE_NODE_SIZE/4);

    pu32=(U32 xdata*)msAPI_FS_GetXData(BULK_START_SECTOR_TABLE_ADDR>>12);
    sector=pu32[bulkID];
    msAPI_FS_ReturnXData();
    if (sector == 0) //sector of specific bulk should not be "0"
    {
        __ASSERT(0);
        return INVALID_BULK_START_SECTOR;
    }

    return sector;
}

static BOOLEAN BKFS_FetchAllocationTable(void)
{
     U16 i;
     U16 *pu16;
     U8 u8DeviceID = msAPI_BKFS_GetDeviceIndex();
     U8 u8SectorCnt = (IDX_ALLOCATION_TABLE_NODE_SIZE/BytesPerSector);
     U32 sectorAddr= IDX_FILE_StartSector
                    +(IDX_HEAD_SIZE/BytesPerSector)
                    +(g_BKFS_STSecTBL_Node_Number*IDX_BULK_START_SECTOR_TABLE_NODE_SIZE/BytesPerSector);

    g_u16FreeBulkCnt = (U16)BKFS_GetTotalBulkNumber();
    g_u16FreeBulkCnt -= g_u16TimeShiftReservedBulkCnt;

    g_u32CurrentAllocTBLNodeIndex = g_BKFS_AllocTBL_Node_Number;

    while(g_u32CurrentAllocTBLNodeIndex>0)
    {
        BKFSDBG(printf("g_u32CurrentAllocTBLNodeIndex=%ld, g_u16FreeBulkCnt=%d\n",  g_u32CurrentAllocTBLNodeIndex, g_u16FreeBulkCnt));
         g_u32CurrentAllocTBLNodeIndex--;

         if(FALSE == msAPI_MSDCtrl_SectorRead(u8DeviceID, sectorAddr+u8SectorCnt*g_u32CurrentAllocTBLNodeIndex,
                                                              u8SectorCnt,_PA2VA(ALLOCATION_TABLE_ADDR)) )
         {
               g_u32CurrentAllocTBLNodeIndex = INVALID_ALLOC_TBL_INDEX;
               return FALSE;
         }


         pu16=(U16 xdata*)msAPI_FS_GetXData(ALLOCATION_TABLE_ADDR>>12);

         for( i=0; i< IDX_ALLOCATION_TABLE_NODE_SIZE/2; i++)
             if(pu16[i] && (g_u32CurrentAllocTBLNodeIndex||i>g_u16TimeShiftReservedBulkCnt))
             {
                   __ASSERT(g_u16FreeBulkCnt);
                     g_u16FreeBulkCnt--;
             }
         msAPI_FS_ReturnXData();
    }
    //printf("Free Bulk cnt is %ld\n", g_u16FreeBulkCnt);
    return TRUE;

}

static void BKFS_SetBulkValue(U16 bulkID,U16 val)
{
     U16 *pu16;

    if(bulkID>g_BKFS_AllocTBL_Node_Number*(IDX_ALLOCATION_TABLE_NODE_SIZE/2))
    {
        __ASSERT(0);
        return;
    }

    if((bulkID/(IDX_ALLOCATION_TABLE_NODE_SIZE/2)) != g_u32CurrentAllocTBLNodeIndex)
    {
       U8 u8DeviceID = msAPI_BKFS_GetDeviceIndex();
       U8 u8SectorCnt = (IDX_ALLOCATION_TABLE_NODE_SIZE/BytesPerSector);
       U32 sectorAddr= IDX_FILE_StartSector
                    +(IDX_HEAD_SIZE/BytesPerSector)
                    +(g_BKFS_STSecTBL_Node_Number*IDX_BULK_START_SECTOR_TABLE_NODE_SIZE/BytesPerSector)+u8SectorCnt*g_u32CurrentAllocTBLNodeIndex;
        BKFS_WriteAllocationTable();
        g_u32CurrentAllocTBLNodeIndex = (bulkID/(IDX_ALLOCATION_TABLE_NODE_SIZE/2));
        sectorAddr= IDX_FILE_StartSector +(IDX_HEAD_SIZE/BytesPerSector)+(g_BKFS_STSecTBL_Node_Number*IDX_BULK_START_SECTOR_TABLE_NODE_SIZE/BytesPerSector)
                                      +u8SectorCnt*g_u32CurrentAllocTBLNodeIndex;
       if(FALSE == msAPI_MSDCtrl_SectorRead(u8DeviceID, sectorAddr, u8SectorCnt, _PA2VA(ALLOCATION_TABLE_ADDR)))
       {
               g_u32CurrentAllocTBLNodeIndex = INVALID_ALLOC_TBL_INDEX;
               __ASSERT(0);
               return;
       }

    }
    bulkID %= (IDX_ALLOCATION_TABLE_NODE_SIZE/2);

   pu16=(U16 xdata*)msAPI_FS_GetXData(ALLOCATION_TABLE_ADDR>>12);

    if(g_u32CurrentAllocTBLNodeIndex ||  bulkID>g_u16TimeShiftReservedBulkCnt)
    {
          //reserved bulks will not be calculated into drive free space
          if(pu16[bulkID]==0 && val)
          {
                 __ASSERT(g_u16FreeBulkCnt);
                 g_u16FreeBulkCnt--;
          }
          else if(pu16[bulkID] && val==0)
              g_u16FreeBulkCnt++;
     }

    pu16[bulkID]=val;
    g_u32BKFS_Dirty_Flag |= BKFS_DIRTY_ALLOC_TBL;

    msAPI_FS_ReturnXData();
}

static U16 BKFS_GetBulkValue(U16 bulkID)
{
    U16* pu16=NULL;
    U16 val;

    if(bulkID>g_BKFS_AllocTBL_Node_Number*(IDX_ALLOCATION_TABLE_NODE_SIZE/2))
    {
        __ASSERT(0);
        return 0xFFFF;
    }
    if((bulkID/(IDX_ALLOCATION_TABLE_NODE_SIZE/2)) != g_u32CurrentAllocTBLNodeIndex)
    {
       U8 u8DeviceID = msAPI_BKFS_GetDeviceIndex();
       U8 u8SectorCnt = (IDX_ALLOCATION_TABLE_NODE_SIZE/BytesPerSector);
       U32 sectorAddr= IDX_FILE_StartSector
                    +(IDX_HEAD_SIZE/BytesPerSector)
                    +(g_BKFS_STSecTBL_Node_Number*IDX_BULK_START_SECTOR_TABLE_NODE_SIZE/BytesPerSector)+u8SectorCnt*g_u32CurrentAllocTBLNodeIndex;
        BKFS_WriteAllocationTable();
        g_u32CurrentAllocTBLNodeIndex = (bulkID/(IDX_ALLOCATION_TABLE_NODE_SIZE/2));
        sectorAddr= IDX_FILE_StartSector +(IDX_HEAD_SIZE/BytesPerSector)+(g_BKFS_STSecTBL_Node_Number*IDX_BULK_START_SECTOR_TABLE_NODE_SIZE/BytesPerSector)
                                      +u8SectorCnt*g_u32CurrentAllocTBLNodeIndex;
       if(FALSE == msAPI_MSDCtrl_SectorRead(u8DeviceID, sectorAddr, u8SectorCnt, _PA2VA(ALLOCATION_TABLE_ADDR)))
       {
               g_u32CurrentAllocTBLNodeIndex = INVALID_ALLOC_TBL_INDEX;
               return FALSE;
       }

    }
    bulkID %= (IDX_ALLOCATION_TABLE_NODE_SIZE/2);

    pu16=(U16 xdata*)msAPI_FS_GetXData(ALLOCATION_TABLE_ADDR>>12);
    val=pu16[bulkID];
    msAPI_FS_ReturnXData();

    return val;
}

static BOOLEAN BKFS_WriteBulkFileEntry(U16 bulkFileID,U32 MIUAddr)
{
    U32 sector=0xFFFFFFFF;
    U8 u8DeviceID = msAPI_BKFS_GetDeviceIndex();
    sector= IDX_FILE_StartSector
               +(IDX_HEAD_SIZE/BytesPerSector)
               +(g_BKFS_STSecTBL_Node_Number*IDX_BULK_START_SECTOR_TABLE_NODE_SIZE/BytesPerSector)
               +(g_BKFS_AllocTBL_Node_Number*IDX_ALLOCATION_TABLE_NODE_SIZE/BytesPerSector)
               +(bulkFileID*BULK_FILE_ENTRY_SIZE/BytesPerSector);

    return msAPI_MSDCtrl_SectorWrite(u8DeviceID, sector,BULK_FILE_ENTRY_SIZE/BytesPerSector,MIUAddr);
}

static BOOLEAN BKFS_WriteCurrentCachedBulkFileEntry(void)
{
    BulkFileEntry *pBulkFile=NULL;
    //U32 sector=0xFFFFFFFF;
    U16 bulkFileID=0xFFFF;
    pBulkFile=(BulkFileEntry xdata*)msAPI_FS_GetXData(BULK_FILE_ENTRY_ADDR>>12);

    bulkFileID=pBulkFile->BulkFileID;


    if(bulkFileID>MAX_BULK_FILE_ID)
    {
        __ASSERT(0);
        msAPI_FS_ReturnXData();
        return FALSE;
    }

    msAPI_FS_ReturnXData();

    return BKFS_WriteBulkFileEntry(bulkFileID,_PA2VA(BULK_FILE_ENTRY_ADDR));
}

static U16 BKFS_SearchBulkFile(U16* pu16FileName)
{
    BulkFileEntry* pBulkFile=NULL;
    U8 u8DeviceID = msAPI_BKFS_GetDeviceIndex();
    U16 FileName[256];
    U16 i=1, k;
    U16 u16Step;
    U16 u16BulkFileID;
    U16 u16MaxUsedBulkFileEntryIndex = msAPI_BKFS_GetMaxUsedBulkFileEntryIndex();
    U32 sector= IDX_FILE_StartSector+(IDX_HEAD_SIZE/BytesPerSector)+
                   (g_BKFS_STSecTBL_Node_Number*IDX_BULK_START_SECTOR_TABLE_NODE_SIZE/BytesPerSector)+
                                   (g_BKFS_AllocTBL_Node_Number*IDX_ALLOCATION_TABLE_NODE_SIZE/BytesPerSector);

    memset(FileName,0,sizeof(FileName));
    memcpy(FileName,pu16FileName,FS_strlen_U(pu16FileName)*2);
    u16Step = PVR_IO_BUFFER_LEN/BULK_FILE_ENTRY_SIZE;
    for(i=1;i<=u16MaxUsedBulkFileEntryIndex;i+=u16Step)
    {
        if(u16MaxUsedBulkFileEntryIndex-i+1 < u16Step) //final loop
            u16Step = u16MaxUsedBulkFileEntryIndex-i+1;

        ioassert(msAPI_MSDCtrl_SectorRead(u8DeviceID, sector+((U32)i*BULK_FILE_ENTRY_SIZE)/BytesPerSector,((u16Step*BULK_FILE_ENTRY_SIZE)/BytesPerSector), _PA2VA((PVR_IO_BUFFER_MEMORY_TYPE&MIU1)?PVR_IO_BUFFER_ADR|MIU_INTERVAL:PVR_IO_BUFFER_ADR)));
        for( k=0; k<u16Step; k++)
        {
            pBulkFile=(BulkFileEntry xdata*)msAPI_FS_GetXData(((((PVR_IO_BUFFER_MEMORY_TYPE&MIU1)?PVR_IO_BUFFER_ADR|MIU_INTERVAL:PVR_IO_BUFFER_ADR))+k*BULK_FILE_ENTRY_SIZE)>>12);
            if(pBulkFile->BulkFileID==0)
            {
                  msAPI_FS_ReturnXData();
                  continue;
            }

            if(FS_strequal_U(pBulkFile->FileName,FileName))
            {
                  BKFSDBG(printf("i=%u, BulkFileID=%u, StartBulkID=%u\n",i,pBulkFile->BulkFileID,pBulkFile->StartBulkID));
                  u16BulkFileID = pBulkFile->BulkFileID;
                  msAPI_FS_ReturnXData();
                  return u16BulkFileID;
            }
            msAPI_FS_ReturnXData();
        }
    }
    return INVALID_BULK_FILE_ID;
}

/*static U16 BKFS_SearchBulkFileByIndex(U32 u32BulkFileIndex)
{
    BulkFileEntry* pBulkFile=NULL;
    U8 u8DeviceID = msAPI_BKFS_GetDeviceIndex();
    U16 i=1;
    U16 u16MaxUsedBulkFileEntryIndex = msAPI_BKFS_GetMaxUsedBulkFileEntryIndex();
    U32 sector= IDX_FILE_StartSector+(IDX_HEAD_SIZE/BytesPerSector)+
                   (g_BKFS_STSecTBL_Node_Number*IDX_BULK_START_SECTOR_TABLE_NODE_SIZE/BytesPerSector)+
                                   (g_BKFS_AllocTBL_Node_Number*IDX_ALLOCATION_TABLE_NODE_SIZE/BytesPerSector);


    if ((u32BulkFileIndex == 0) || (u32BulkFileIndex > u16MaxUsedBulkFileEntryIndex))
        return INVALID_BULK_FILE_ID;

    //1st time, using fixed address searching to enhancement performance.
    ioassert(msAPI_MSDCtrl_SectorRead(u8DeviceID, sector+((U32)u32BulkFileIndex*BULK_FILE_ENTRY_SIZE)/BytesPerSector,(BULK_FILE_ENTRY_SIZE/BytesPerSector),_PA2VA(IO_TEMP_ADDR)));
    pBulkFile=(BulkFileEntry xdata*)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);
    if (pBulkFile->BulkFileID == u32BulkFileIndex)
    {
        BKFSDBG(printf("i=%u, BulkFileID=%u, StartBulkID=%u\n",i,pBulkFile->BulkFileID,pBulkFile->StartBulkID));
        msAPI_FS_ReturnXData();
        return u32BulkFileIndex;
    }
    msAPI_FS_ReturnXData();

    //2nd, sequential search.
    for(i=1;i<=u16MaxUsedBulkFileEntryIndex;i++)
    {
        ioassert(msAPI_MSDCtrl_SectorRead(u8DeviceID, sector+((U32)i*BULK_FILE_ENTRY_SIZE)/BytesPerSector,(BULK_FILE_ENTRY_SIZE/BytesPerSector),_PA2VA(IO_TEMP_ADDR)));
        pBulkFile=(BulkFileEntry xdata*)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);

        if(pBulkFile->BulkFileID==0)
        {
             msAPI_FS_ReturnXData();
             continue;
        }

        //if(FS_strequal_U(pBulkFile->FileName,FileName))
        if (pBulkFile->BulkFileID == u32BulkFileIndex)
        {
            BKFSDBG(printf("i=%u, BulkFileID=%u, StartBulkID=%u\n",i,pBulkFile->BulkFileID,pBulkFile->StartBulkID));
            msAPI_FS_ReturnXData();
            return i;
        }

        msAPI_FS_ReturnXData();
    }
    return INVALID_BULK_FILE_ID;
}*/ //for performance improvement

BKFS_POSITION msAPI_BKFS_FindFirstPOS(void)
{
    U16 u16MaxUsedBulkFileEntryIndex = msAPI_BKFS_GetMaxUsedBulkFileEntryIndex();
    return MAKE_BKFS_POSITION(u16MaxUsedBulkFileEntryIndex, 1);
}


BKFS_POSITION msAPI_BKFS_FindNextBulkFile(BKFS_POSITION pos, U16 *pCurBulkFileName, U16 *pBufU16Len)
{
    BulkFileEntry* pBulkFile=NULL;
    U16 u16Index = BKFS_GET_POS_INDEX(pos);
    U16 maxIndex = BKFS_GET_POS_MAX_INDEX(pos);
    U8 u8DeviceID = msAPI_BKFS_GetDeviceIndex();
    U16 len;
    U32 sector= IDX_FILE_StartSector+(IDX_HEAD_SIZE/BytesPerSector)
               +(g_BKFS_STSecTBL_Node_Number*IDX_BULK_START_SECTOR_TABLE_NODE_SIZE/BytesPerSector)
               +(g_BKFS_AllocTBL_Node_Number*IDX_ALLOCATION_TABLE_NODE_SIZE/BytesPerSector);

    while(u16Index<=maxIndex)
    {
       if(FALSE == msAPI_MSDCtrl_SectorRead(u8DeviceID, sector+((U32)u16Index*BULK_FILE_ENTRY_SIZE)/BytesPerSector,(BULK_FILE_ENTRY_SIZE/BytesPerSector),_PA2VA(IO_TEMP_ADDR)))
        {
           MS_DEBUG_MSG(printf("msAPI_MSDCtrl_SectorRead() FALSE\n"));
           __ASSERT(0);
           return (BKFS_POSITION)0;
        }
        pBulkFile=(BulkFileEntry xdata*)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);

        if(pBulkFile->BulkFileID==0 || pBulkFile->OpenMode==BKF_OPEN_FOR_RING_WRITE)
        {
             msAPI_FS_ReturnXData();
             u16Index++;
             continue;
        }
        len = FS_strlen_U(pBulkFile->FileName);

        if(len  > *pBufU16Len)
             len = *pBufU16Len;
        memcpy(pCurBulkFileName, pBulkFile->FileName, sizeof(U16)*len);
        msAPI_FS_ReturnXData();
        *pBufU16Len = len;

        return MAKE_BKFS_POSITION(maxIndex, (u16Index+1));
    }
    return (BKFS_POSITION)0;
}

//[CPU bound solution only]
U8 BKFS_FAT_CreateFiles(U8 u8EnvironmentID, U16 *fileName, U8 fileLen, U32 u32FileTotalSize,
            FileEntry *pFileDirEntry)
{
    U8 u8Handle;
    U8 bResult;
    FAT_FileInode *pFileInode;
    U8 fsid;
    U8 *pu8FatTable;
    FAT_FileSysStruct * pFAT_FileSys;
    U8 u8DeviceIndex;
    U32 u32FatCount;
    U32 u32DirStartClusterNo;
    U32 u32FATStartSectorNo;
    U8 u8BPB_SecPerClus;
    U16 u16BPB_BytsPerSec;
    U32 u32BytesPerCluster;
    //[perfromance issue, using U16 can get better performance
    U32 u32FATClusterCnt;
    U16 u16FATClusterCnt;
    U16 u16FatTableIndex;
    U32  u32ClusterID;
    //]

    if(u32FileTotalSize == 0)
    {
        __ASSERT(0);
        return INVALID_FILE_HANDLE;
    }
    // create file
    if(pFileDirEntry == NULL)
          u8Handle = FAT_FileCreate(u8EnvironmentID, fileName, fileLen, CREATE_MODE_NEW);
    else
          u8Handle = msAPI_FCtrl_FileOpen(pFileDirEntry, OPEN_MODE_BINARY_FOR_READ_WRITE);

    if(INVALID_FILE_HANDLE == u8Handle)
    {
        __ASSERT(0);
        return INVALID_FILE_HANDLE;
    }
    pFileInode = FAT_File_GetInodeFromHandle( u8Handle);
    pFileInode->u32FileTotalSize = u32FileTotalSize;

    bResult = FAT_EntryFillCluster(u8Handle);
    if(ENTRY_CREATE_RESULT_ERROR == bResult)
    {
        __ASSERT(printf("BKFS_FAT_CreateFiles: Unknown error happens\n"));
        FCtrl_ReturnFileInodeXdata();
        return INVALID_FILE_HANDLE;
    }
    else if(ENTRY_CREATE_RESULT_FULL == bResult)
    {
        __ASSERT(printf("BKFS_FAT_CreateFiles: No Free Space\n"));
        FCtrl_ReturnFileInodeXdata();
        return INVALID_FILE_HANDLE;
    }


    u32DirStartClusterNo = pFileInode->u32FileStartClusterNo;
    FCtrl_ReturnFileInodeXdata();
    if(debugFlag)
    {
        HERE;
    }
    fsid = msAPI_FSEnv_GetEnvironment( u8EnvironmentID )->u8FileSystemID;
    u8DeviceIndex = msAPI_FSEnv_GetEnvironment( u8EnvironmentID )->u8DeviceIndex;

    pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemXData(fsid);
    u32FATStartSectorNo = pFAT_FileSys->stFAT.u32FATStartSectorNo;
    u8BPB_SecPerClus = pFAT_FileSys->stBootSector.BPB_SecPerClus;
    u16BPB_BytsPerSec = pFAT_FileSys->stBootSector.BPB_BytsPerSec;
    FAT_ReturnXData();
    u32BytesPerCluster = (U32)((U32)u8BPB_SecPerClus*(U32)u16BPB_BytsPerSec);
    u32FATClusterCnt = u32FileTotalSize/u32BytesPerCluster;
    u16FATClusterCnt = (U16)(u32FileTotalSize/u32BytesPerCluster);

    // update entry
    if(!FAT_DirEntryUpdate(u8Handle))
    {
        __ASSERT(0);
        return INVALID_FILE_HANDLE;
    }
    if(debugFlag)
    {
        HERE;
    }
    u32FatCount = (u32DirStartClusterNo/1024);

    if ( !msAPI_MSDCtrl_SectorRead(u8DeviceIndex, (U32)(u32FATStartSectorNo + (u32FatCount*8)), 8, (FILE_FAT_TABLE_CACHE + (U32)fsid * FAT_TABLE_CACHE_LEN)) )
    {
        __ASSERT(0);
        return INVALID_FILE_HANDLE;
    }

    pu8FatTable = (U8*)FCtrl_GetFatTableCacheXData(fsid);
    u16FatTableIndex = (U16)(u32DirStartClusterNo%1024);
    u32FATClusterCnt--;
    u16FATClusterCnt--;

    if (u32FATClusterCnt>0xFFFF) //need to use U32
    {
        while(1)
        {
            //FAT_ClearCluster(u8EnvironmentID, u32DirStartClusterNo, u8BPB_SecPerClus);
            //u32ClusterID =  BKFSSwap32(++u32DirStartClusterNo);
            u32DirStartClusterNo++;
            u32ClusterID =  BKFSSwap32(u32DirStartClusterNo);
            memcpy(pu8FatTable + (u16FatTableIndex*FAT32ENTRYSIZE), &u32ClusterID, FAT32ENTRYSIZE);
            u16FatTableIndex++;
            if(u16FatTableIndex == 1024)
            {
                u16FatTableIndex = 0;
                FAT_ReturnXData();
                if ( !msAPI_MSDCtrl_SectorWrite( u8DeviceIndex, (U32)(u32FATStartSectorNo + (u32FatCount*8)) , 8, FILE_FAT_TABLE_CACHE + (U32)fsid * FAT_TABLE_CACHE_LEN) )
                {
                    __ASSERT(0);
                    return INVALID_FILE_HANDLE;
                }
                u32FatCount ++;

                //if ( !msAPI_MSDCtrl_SectorRead(u8DeviceIndex, (U32)(u32FATStartSectorNo + (u32FatCount*8)), 8, FILE_FAT_TABLE_CACHE + (U32)fsid * FAT_TABLE_CACHE_LEN) )
                if ( !FAT_FATStructureFetch(fsid, (u32FatCount*8)))
                {
                    __ASSERT(0);
                    return INVALID_FILE_HANDLE;
                }
                pu8FatTable = (U8*)FCtrl_GetFatTableCacheXData(fsid);
            }

            u32FATClusterCnt--;
            if(u32FATClusterCnt == 0)
            {
                u32ClusterID =  BKFSSwap32(0xFFFFFFF);
                memcpy(pu8FatTable + (u16FatTableIndex*FAT32ENTRYSIZE), &u32ClusterID, FAT32ENTRYSIZE);
                pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemXData(fsid);
                pFAT_FileSys->u32CurrentFreeCluster = u32DirStartClusterNo;
                FAT_ReturnXData();
                break;
            }
        }
    }
    else //just need to use U16 to save performance
    {
        while(1)
        {
            //u32ClusterID =  BKFSSwap32(++u32DirStartClusterNo);
            u32DirStartClusterNo++;
            u32ClusterID =  BKFSSwap32(u32DirStartClusterNo);
            memcpy(pu8FatTable + (u16FatTableIndex*FAT32ENTRYSIZE), &u32ClusterID, FAT32ENTRYSIZE);
            u16FatTableIndex++;
            if(u16FatTableIndex == 1024)
            {
                u16FatTableIndex = 0;
                FAT_ReturnXData();
                if ( !msAPI_MSDCtrl_SectorWrite( u8DeviceIndex, (U32)(u32FATStartSectorNo + (u32FatCount*8)) , 8,  FILE_FAT_TABLE_CACHE + (U32)fsid * FAT_TABLE_CACHE_LEN))
                {
                    __ASSERT(0);
                    return INVALID_FILE_HANDLE;
                }
                u32FatCount ++;
                //if ( !msAPI_MSDCtrl_SectorRead(u8DeviceIndex, (U32)(u32FATStartSectorNo + (u32FatCount*8)), 8, FILE_FAT_TABLE_CACHE + (U32)fsid * FAT_TABLE_CACHE_LEN))
                if ( !FAT_FATStructureFetch(fsid, (u32FatCount*8)))
                {
                    __ASSERT(0);
                    return INVALID_FILE_HANDLE;
                }
                pu8FatTable = (U8*)FCtrl_GetFatTableCacheXData(fsid);
            }

            u16FATClusterCnt--;
            if(u16FATClusterCnt == 0)
            {
                u32ClusterID =  BKFSSwap32(0xFFFFFFF);
                memcpy(pu8FatTable + (u16FatTableIndex*FAT32ENTRYSIZE), &u32ClusterID, FAT32ENTRYSIZE);
                pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemXData(fsid);
                pFAT_FileSys->u32CurrentFreeCluster = u32DirStartClusterNo;
                FAT_ReturnXData();
                break;
            }
        }
    }
    FAT_ReturnXData();

    if ( !msAPI_MSDCtrl_SectorWrite( u8DeviceIndex, (U32)(u32FATStartSectorNo + (u32FatCount*8)), 8, FILE_FAT_TABLE_CACHE + (U32)fsid * FAT_TABLE_CACHE_LEN) )
    {
        __ASSERT(0);
        return INVALID_FILE_HANDLE;
    }
    return u8Handle;
}

EN_FILE_CLOSE_RESULT BKFS_FAT_CloseFiles(U8 u8Handle)
{
    return msAPI_FCtrl_FileClose(u8Handle);
}

static BOOLEAN BKFS_AllocateNextBulk(U16 bulkID,U16* nextBulkID)
{
    U16 bkID=BKFS_GetFreeBulkID(bulkID+1);
    *nextBulkID=INVALID_BK_ID;

    if(bkID==INVALID_BK_ID)
    {
        return FALSE;
    }

    *nextBulkID=bkID;
    BKFS_SetBulkValue(bulkID,bkID);
    BKFS_SetBulkValue(bkID,LAST_BULK_ID);

    ioassert(BKFS_WriteAllocationTable());
    return TRUE;
}

static BOOLEAN BKFS_CreateBulkFileEntry(U16* pu16FileName,U16 freeBulkFileID,U16 startBulkID,EN_BKF_OPEN_MODE mode,U8 *ringBulkCount)
{
    BulkFileEntry* pBulkFile=NULL;

    pBulkFile=BKFS_GetBulkFileEntryXDATA(freeBulkFileID);
    if(pBulkFile==NULL)
    {
        __ASSERT(0);
        msAPI_FS_ReturnXData();
        return FALSE;
    }
    pBulkFile->BulkFileID=freeBulkFileID;
    pBulkFile->StartBulkID=startBulkID;
    pBulkFile->OpenMode=mode;
    pBulkFile->uFatSegTsFileCnt = 0;
/*
    pBulkFile->RingMode=ringMode;
    pBulkFile->RingStartPosition=0;

    if(ringMode)
    {
        LongLong rsz;
        LL_assign(&rsz,0);
        if(ringBulkCount==MAX_RING_BULK_COUNT)
        {
            rsz.Hi=1;
        }
        else
        {
            rsz.Lo=ringBulkCount*BULK_SIZE;
        }
        pBulkFile->RingSize=rsz;
    }
*/
    memcpy(pBulkFile->FileName,pu16FileName,FS_strlen_U(pu16FileName)*2);
    LL_assign(&pBulkFile->FileLength,0);

    msAPI_FS_ReturnXData();

    BKFS_SetBulkValue(startBulkID,LAST_BULK_ID);

    //pre allocate bulk
    if(mode==BKF_OPEN_FOR_RING_WRITE)
    {
        U16 _bkid=startBulkID;
        U16 _nxtbkid;
        U8 i=1;

        while(i < *ringBulkCount)
        {
            if(BKFS_AllocateNextBulk(_bkid,&_nxtbkid))
            {
                _bkid = _nxtbkid;
                i+=1;
            }
            else
            {
                __ASSERT(0);
                return FALSE;
            }
        }
        *ringBulkCount = i;
    }

    ioassert(BKFS_WriteAllocationTable());
    ioassert(BKFS_WriteCurrentCachedBulkFileEntry());
    return TRUE;
}

//return next allocated bulk.
//will return start bulk if last is reached.
static U16 BKFS_GetBulkValue_RingMode(U16 bulkFileID,U16 bulkID)
{
    U16* pu16=NULL;
    //U16 i=1;
    U16 nextBulkID = INVALID_BK_ID;

    pu16=(U16 xdata*)msAPI_FS_GetXData(ALLOCATION_TABLE_ADDR>>12);
    nextBulkID = pu16[bulkID];
    msAPI_FS_ReturnXData();

    if(nextBulkID == LAST_BULK_ID)
    {
        BulkFileEntry* pBulkFile=NULL;
        pBulkFile=BKFS_GetBulkFileEntryXDATA(bulkFileID);
        if(pBulkFile==NULL)
        {
            __ASSERT(0);
            msAPI_FS_ReturnXData();
            return INVALID_BK_ID;
        }
        nextBulkID = pBulkFile->StartBulkID; //return to head
        msAPI_FS_ReturnXData();
    }
    return nextBulkID;
}

//TODO: need to implement
static BOOLEAN BKFS_SetupCheck(U8 fsid)
{
    UNUSED(fsid);
    if(!FS_IsPowerOf2(BULK_SIZE))
    {
        __ASSERT(0);
        return FALSE;
    }
    return TRUE;
}

static BOOLEAN BKFS_FileResetReadHandleToBegin(U8 handleID)
{
    BulkFileHandle* pHandle;
    U16 BulkFileID;
    U16 startBulk;
//    BOOLEAN ringMode;
//    U32 ringStartPosition;
//    LongLong ringSize;
    LongLong fileLength;
    EN_BKF_OPEN_MODE OpenMode;

    pHandle=BKFS_GetBulkFileHandleXDATA();
    BulkFileID=pHandle[handleID].BulkFileID;
    //ringSize=pHandle[handleID].RingSize;
    //ringMode=pHandle[handleID].RingMode;
    //ringStartPosition=pHandle[handleID].RingStartPosition;
    fileLength=pHandle[handleID].FileLength;
    OpenMode=pHandle[handleID].OpenMode;
    msAPI_FS_ReturnXData();

    startBulk=BKFS_GetBulkFileEntryXDATA(BulkFileID)->StartBulkID;
    msAPI_FS_ReturnXData();

    //if((!ringMode)||(LL_greater_or_equal(&ringSize,&fileLength)))
    {
        pHandle=BKFS_GetBulkFileHandleXDATA();
        pHandle[handleID].CurrentBulkSectorNO=BKFS_GetBulkStartSector(startBulk);
        pHandle[handleID].CurrentBulkID=startBulk;
        pHandle[handleID].CurrentSectorOffset=0;
        LL_assign(&pHandle[handleID].Position,0);
        msAPI_FS_ReturnXData();
    }
//    else
    {
/*
        LongLong _pos;
        U32 _nextBulkID=startBulk;
        U32 _tmp=ringStartPosition;

        //seach the BulkID to ring start
        while(_tmp>=BULK_SIZE)
        {
            _tmp-=BULK_SIZE;
            _nextBulkID=BKFS_GetBulkValue(_nextBulkID);

        }

        _pos=LL_subtractLong(&fileLength,&ringSize);

        pHandle=BKFS_GetBulkFileHandleXDATA();
        pHandle[handleID].CurrentBulkSectorNO=BKFS_GetBulkStartSector(_nextBulkID);
        pHandle[handleID].CurrentBulkID=_nextBulkID;
        pHandle[handleID].CurrentSectorOffset=(_tmp/BytesPerSector);
        memcpy(&pHandle[handleID].Position,&_pos,sizeof(LongLong));
        msAPI_FS_ReturnXData();
*/
    }
    return TRUE;
}

static BOOLEAN BKFS_FreeBulks(U16 startBulkID,BOOLEAN keepStart)
{
    U16 guard=0;
    U16 BulkID=startBulkID; BKFSDBG(printf("[BKFS] BKFS_FreeBulks: startBulkID=%u\n",startBulkID));
    while(TRUE)
    {
        U16 nextBulkID=BKFS_GetBulkValue(BulkID);
        if(keepStart&&(BulkID==startBulkID))
        {
            BKFS_SetBulkValue(BulkID,LAST_BULK_ID);
        }
        else
        {
            BKFSDBG(printf("[BKFS] Delete : Set bulk[%u] free\n",BulkID));
            BKFS_SetBulkValue(BulkID,0);
        }
        if(nextBulkID==0xFFFF||nextBulkID==LAST_BULK_ID)
        {
            break;
        }
        else
        {
            BulkID=nextBulkID;
        }

        guard++;
        if(guard==BKFS_TotalBulkNumber)
        {
            return TRUE;
        }
        if(guard>1024)
        {
            __ASSERT(0);
            return FALSE;
        }
    }
    ioassert(BKFS_WriteAllocationTable());
    return TRUE;
}

BOOLEAN msAPI_BKFS_SetMemory(U32 poolAddress,U32 len)
{
    UNUSED(len);

    if((poolAddress&0xFFF)>0)
    {
        __ASSERT(0);
        return FALSE;
    }

    if((BULK_MEM_CHECK-BKFS_MEM_ADDR)>BKFS_MEM_LEN)
    {
        __ASSERT(0);
        return FALSE;
    }

    PoolAddress=poolAddress;

    BKFSDBG(printf("Set BKFS Memory Address 0x%08lx, Length=0x%08lx\n",PoolAddress,len));

    return TRUE;
}


BOOLEAN msAPI_BKFS_SetDiskDriveIndex(U8 driveIndex)
{
    if (driveIndex > DISK_DRIVE_NUM)
    {
        return FALSE;
    }
    BKFS_DiskDriveIndex=driveIndex;

    return TRUE;
}

BOOLEAN msAPI_BKFS_SetDeviceIndex(U8 deviceIndex)
{
    if (deviceIndex == INVALID_DEVICE_INDEX)
    {
        __ASSERT(0);
        return FALSE;
    }

    BKFS_DeviceID=deviceIndex;
    BKFSDBG(printf("Set BKFS DeviceIndex=%bu\n",BKFS_DeviceID));
    return TRUE;
}

//IDX_FILE_StartSector: Byte 0x04~0x07
static U32 BKFS_GetTotalBulkNumber(void)
{
    U32* pu32=NULL;
    U32 PhysicalBulkNum;
    U32 sectorAddr= IDX_FILE_StartSector;
    U8 u8DeviceID = msAPI_BKFS_GetDeviceIndex();

    if(!msAPI_MSDCtrl_SectorRead(u8DeviceID, sectorAddr,1,_PA2VA(IO_TEMP_ADDR)))
    {
        __ASSERT(0);
        return 0;
    }
    pu32=(U32 xdata*)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);
    GET_MISCINFO(PhysicalBulkNum, TOTAL_BULK, pu32);
    msAPI_FS_ReturnXData();
    if((PhysicalBulkNum&0xFFFF0000)!=BULK_FS_MAGIC_HEADER)
    {
           __ASSERT(0);
            return 0;
    }
    PhysicalBulkNum &= 0x0000FFFF;
    return PhysicalBulkNum;
}

static U16 BKFS_GetFileStartBulkID(U16 bulkFileID)
{
    U16 StartBulkID = INVALID_BK_ID;
    BulkFileEntry* pBulkFile=NULL;
    pBulkFile=BKFS_GetBulkFileEntryXDATA(bulkFileID);
    if(pBulkFile==NULL)
    {
        __ASSERT(0);
        msAPI_FS_ReturnXData();
        return INVALID_BK_ID;
    }
    StartBulkID = pBulkFile->StartBulkID;
    msAPI_FS_ReturnXData();
    return StartBulkID;
}

static BOOLEAN BKFS_Initial(U8 environmentID)
{
    FS_EnvironmentStruct* pFS_Env;
    FAT_FileSysStruct *pFsStruct;
    FileEntry entry;
    U32 u32ClusterID;

    U8 fileName[13];
    U8 bkfsFolder[9];
    U16* pu16;
    //U32 ts =msAPI_Timer_GetTime0();


    pFS_Env=msAPI_FSEnv_GetEnvironment(environmentID);

    if(pFS_Env==NULL)
    {
        __ASSERT(0);
        return FALSE;
    }
    if(!BKFS_SetupCheck(pFS_Env->u8FileSystemID))
    {
        __ASSERT(0);
        return FALSE;
    }
    if(msAPI_BKFS_GetDeviceIndex()!=pFS_Env->u8DeviceIndex)
    {
        __ASSERT(0);
        return FALSE;
    }
    pFsStruct=(FAT_FileSysStruct*)FCtrl_GetFileSystemXData(BKFS_DiskDriveIndex);
    BytesPerSector=pFsStruct->stBootSector.BPB_BytsPerSec;
    FAT_ReturnXData();

    BKFS_SectorsPerBulk=BULK_SIZE/BytesPerSector;
    BKFSDBG(printf("BKFS_Initial(): BKFS_SectorsPerBulk = %lu\n",BKFS_SectorsPerBulk));
    if(!msAPI_FCtrl_DirectoryChangeToRoot(environmentID))
    {
        __ASSERT(0);
        return FALSE;
    }

    memset(bkfsFolder,0,sizeof(bkfsFolder));
    memcpy(bkfsFolder,BKFS_FOLDER,LENGTH_OF_BKFS_FOLDER);

    if(!msAPI_FCtrl_EntrySearchByShortName(environmentID,bkfsFolder,8,&entry))
    {
        BKFSDBG(printf("  BKFS Initiate FAIL : Can't find the folder of BKFS at DriveIndex=%bu of DeviceIndex=%bu!!\n",BKFS_DiskDriveIndex,BKFS_DeviceID));
        return FALSE;
    }

    if(!msAPI_FCtrl_DirectoryChange(environmentID,&entry))
    {
        BKFSDBG(printf("  BKFS Initiate FAIL : Can't change to the folder of BKFS at DriveIndex=%bu of DeviceIndex=%bu!!\n",BKFS_DiskDriveIndex,BKFS_DeviceID));
        return FALSE;
    }
    memset(fileName,0,sizeof(fileName));
    memcpy(fileName,IDX_FILE_NAME,LENGTH_OF_IDX_FILE_NAME);
    ioassert(msAPI_FCtrl_EntrySearchByShortName(environmentID,fileName,12,&entry));

    memcpy(&u32ClusterID ,&entry.EntryID[0], FAT32ENTRYSIZE);
    IDX_FILE_StartSector= FAT_FATGetSectorNo(BKFS_DiskDriveIndex, u32ClusterID);


    BKFSDBG(printf("BKFS_Initial(): IDX_FILE_StartSector = %lu\n",IDX_FILE_StartSector));

    if (msAPI_BKFS_GetBulkVersionNo() != BKFS_VERSION)
    {
        MS_DEBUG_MSG(printf("BKFS Initiate FAIL : Incorrect BKFS Version No. Please reformat the disk before you start to use any [PVR] function.\n"));
        return FALSE;
    }

    if(FALSE==BKFS_GetBulkTBLSize(&g_BKFS_STSecTBL_Node_Number, &g_BKFS_AllocTBL_Node_Number)
        ||g_BKFS_STSecTBL_Node_Number==0 || g_BKFS_AllocTBL_Node_Number==0)
    {
           BKFSDBG(printf("BKFS Initiate FAIL : Incorrect BKFS Allocation/(Start Sector) Table Size.\n"));
           return FALSE;
    }
    g_u16TimeShiftReservedBulkCnt = msAPI_BKFS_GetTimeShiftReservedBulkCnt();

    BKFS_FetchAllocationTable();
    BKFS_FetchBulkStartSectorTable();

    pu16=(U16 xdata*)msAPI_FS_GetXData(BULK_FILE_ENTRY_ADDR>>12);
    *pu16=0;
    msAPI_FS_ReturnXData();

    memset((U8*)BKFS_GetBulkFileHandleXDATA(),0xFF,0x1000);
    msAPI_FS_ReturnXData();

    BKFS_TotalBulkNumber=BKFS_GetTotalBulkNumber();
    BKFSDBG(printf("BKFS_Initial(): BKFS_TotalBulkNumber = %lu\n",BKFS_TotalBulkNumber));
    //printf("%lu ms spend in BULK FS initialization phase\n",msAPI_Timer_DiffTimeFromNow(ts));
    return TRUE;
}

static BOOLEAN BKFS_PrepareDrive(void)
{
    U8 i=0;
    if(!msAPI_FCtrl_IsDriveMounted(BKFS_DiskDriveIndex))
    {
        //msAPI_MSDCtrl_CheckDevices_Ex();
        msAPI_MSDCtrl_CheckDevices();


        if(msAPI_BKFS_GetDeviceIndex()==INVALID_DEVICE_INDEX)
        {
            for(i=0;i<STORAGE_DEVICE_NUM;i++)
            {
                if(msAPI_MSDCtrl_GetDeviceStatus(i)==MSD_STATUS_INSERTED)
                {
                    msAPI_BKFS_SetDeviceIndex(i);
                }
            }
        }

        if(msAPI_MSDCtrl_GetDeviceStatus(msAPI_BKFS_GetDeviceIndex())==MSD_STATUS_INSERTED)
        {
            if(!msAPI_FCtrl_ActiveDevice(msAPI_BKFS_GetDeviceIndex()))
            {
                __ASSERT(0);
                return FALSE;
            }
        }
        else
        {
            //__ASSERT(0);
            return FALSE;
        }

    }
    return TRUE;
}

static U8 BKFS_SearchBulkByIndex(U8 u8EnvironmentID, U16 u16BulkIndex)
{
    FileEntry bulkEntry;
    U8 u8BulkHandle;
    U8 fileName[LENGTH_OF_BKFS_FILE];
    U8 bkfsFolder[LENGTH_OF_BKFS_FOLDER];

    if ((u8EnvironmentID >= FS_ENVIRONMENT_NUM) || (u16BulkIndex > BKFS_TotalBulkNumber))
        return INVALID_FILE_HANDLE;

    //Search bulk file: change to root directory
    if(!msAPI_FCtrl_DirectoryChangeToRoot(u8EnvironmentID))
    {
        __ASSERT(0);
        return INVALID_FILE_HANDLE;
    }
    //Search bulk file: search bulk folder to change to bulk directory.
    memset(bkfsFolder, 0, sizeof(bkfsFolder));
    memcpy(bkfsFolder, BKFS_FOLDER, LENGTH_OF_BKFS_FOLDER);
    if(!msAPI_FCtrl_EntrySearchByShortName(u8EnvironmentID,bkfsFolder, LENGTH_OF_BKFS_FOLDER, &bulkEntry))
    {
        __ASSERT(0);
        return INVALID_FILE_HANDLE;
    }
    //Search bulk file: change to bulk folder to find bulk file entry.
    if(!msAPI_FCtrl_DirectoryChange(u8EnvironmentID,&bulkEntry))
    {
        __ASSERT(0);
        return INVALID_FILE_HANDLE;
    }
    //Search bulk file: find bulk file entry.
    memset(fileName, 0, sizeof(fileName));
    memcpy(fileName, BKFS_FILE, LENGTH_OF_BKFS_FILE);

    *(fileName + 7) = *(fileName + 7) + (u16BulkIndex%10); //assign index 'N' to MST0000N.BUK
    *(fileName + 6) = *(fileName + 6) + ((u16BulkIndex-((u16BulkIndex/100)*100))/10); //assign index 'N' to MST000N0.BUK
    *(fileName + 5) = *(fileName + 5) + ((u16BulkIndex-((u16BulkIndex/1000)*1000))/100); //assign index 'N' to MST00N00.BUK
    *(fileName + 4) = *(fileName + 4) + ((u16BulkIndex-((u16BulkIndex/10000)*10000))/1000); //assign index 'N' to MST0N000.BUK
    *(fileName + 3) = *(fileName + 3) + (u16BulkIndex/10000); //assign index 'N' to MSTN0000.BUK
#if (ENABLE_TO_BULK_FAST_SEARCH)
    if (msAPI_FCtrl_GetCurrentDirEntryIndex() == -1) //just need to setup at the 1st searching.
        msAPI_FCtrl_SetCurrentDirEntryIndex(u16BulkIndex*2+1); //set directory entry index to enhance performance
    if (!msAPI_FCtrl_EntrySearchByShortNameFromCurrentDirEntry(u8EnvironmentID, fileName, LENGTH_OF_BKFS_FILE, &bulkEntry))
    {
        //search again from head
        if (!msAPI_FCtrl_EntrySearchByShortName(u8EnvironmentID, fileName, LENGTH_OF_BKFS_FILE, &bulkEntry))
        {
            __ASSERT(0);
            return INVALID_FILE_HANDLE;
        }
    }
#else
    if (!msAPI_FCtrl_EntrySearchByShortName(u8EnvironmentID, fileName, LENGTH_OF_BKFS_FILE, &bulkEntry))
    {
        __ASSERT(0);
        return INVALID_FILE_HANDLE;
    }
#endif
    u8BulkHandle = msAPI_FCtrl_FileOpen(&bulkEntry, OPEN_MODE_FOR_READ_WRITE);
    if(u8BulkHandle == INVALID_FILE_HANDLE)
    {
        __ASSERT(0);
        return INVALID_FILE_HANDLE;
    }

    return u8BulkHandle;
}

BOOLEAN msAPI_BKFS_IsFormated(U8 u8DiskDriveIndex)
{
    U8 u8EnvironmentID;
    U16 BKFSDirName[9]={'_','M','S','T','B','K','F','S',0};
    U16 BKFSIndexFileName[13] = {'M','S','T','_','B','K','F','S','.','I','D','X',0};
    FileEntry entry;

    u8EnvironmentID = msAPI_FSEnv_Register(u8DiskDriveIndex);
    if(u8EnvironmentID==INVALID_FS_ENVIRONMENT_INDEX)
    {
        return FALSE;
    }

    if (msAPI_BKFS_GetBulkVersionNo() != BKFS_VERSION)
    {
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        return FALSE;
    }

    if(!msAPI_FCtrl_DirectoryChangeToRoot(u8EnvironmentID))
    {
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        return FALSE;
    }

    //check if the forlder _MSTBKFS existed or not
    if(!msAPI_FCtrl_EntrySearchByName(u8EnvironmentID,&BKFSDirName[0],8,&entry))
    {
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        return FALSE;
    }

    if(entry.EntryType!=ENTRY_TYPE_DIR)
    {
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        return FALSE;
    }

    if(!msAPI_FCtrl_DirectoryChange(u8EnvironmentID,&entry))
    {
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        return FALSE;
    }

    //check if the index file  MST_BKFS.IDX existed or not
    if(!msAPI_FCtrl_EntrySearchByName(u8EnvironmentID,&BKFSIndexFileName[0],12,&entry))
    {
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        return FALSE;
    }

    if(entry.EntryType!=ENTRY_TYPE_FILE)
    {
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        return FALSE;
    }

    /*if (!bFastCheck)
    {
        //check if the file size and start cluster of bulk are correct
        U8 u8BulkHandle = INVALID_FILE_HANDLE;
        U32 u32TotalBulkNumber = BKFS_GetTotalBulkNumber();
        U32 u32Index;
        FAT_FileHandle *pFileHandle;

        for (u32Index = 1; u32Index <= u32TotalBulkNumber; u32Index++)
        {
            u8BulkHandle = BKFS_SearchBulkByIndex(u8EnvironmentID, (U16)u32Index);
            if(u8BulkHandle == INVALID_FILE_HANDLE)
            {
                msAPI_FSEnv_UnRegister(u8EnvironmentID);
                return FALSE;
            }
            pFileHandle = FAT_File_GetHandleXData(u8BulkHandle);
            if (pFileHandle->u32FileTotalSize != BULK_SIZE)
            {
                msAPI_FSEnv_UnRegister(u8EnvironmentID);
                FAT_ReturnXData();
                BKFS_FAT_CloseFiles(u8BulkHandle); //close bulk file to update directory entry data
                return FALSE;
            }
            FAT_ReturnXData();
            BKFS_FAT_CloseFiles(u8BulkHandle); //close bulk file to update directory entry data
        }
    }*/

    msAPI_FSEnv_UnRegister(u8EnvironmentID);
    return TRUE;
}

BOOLEAN msAPI_BKFS_IsBulkFileReady(U8 u8DiskDriveIndex, U16* u16BulkIndex, BOOLEAN* bFinished)
{
    //check if the file size and start cluster of bulk are correct
    U8 u8EnvironmentID;
    U8 u8BulkHandle = INVALID_FILE_HANDLE;
    BOOLEAN bReady = FALSE;
    FAT_FileInode *pFileInode;

    u8EnvironmentID = msAPI_FSEnv_Register(u8DiskDriveIndex);
    if(u8EnvironmentID==INVALID_FS_ENVIRONMENT_INDEX)
    {
        __ASSERT(0);
        return FALSE;
    }

    u8BulkHandle = BKFS_SearchBulkByIndex(u8EnvironmentID, *u16BulkIndex);
    if(u8BulkHandle == INVALID_FILE_HANDLE)
    {
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        __ASSERT(0);
        return FALSE;
    }
    pFileInode = FAT_File_GetInodeFromHandle( u8BulkHandle);
    if (pFileInode->u32FileTotalSize == BULK_SIZE)
        bReady = TRUE;

    FCtrl_ReturnFileInodeXdata();


    BKFS_FAT_CloseFiles(u8BulkHandle); //close bulk file to update directory entry data
    msAPI_FSEnv_UnRegister(u8EnvironmentID);

    if (*u16BulkIndex < BKFS_GetTotalBulkNumber())
        *bFinished = FALSE;
    else *bFinished = TRUE;
    (*u16BulkIndex)++;

    return bReady;
}

BOOLEAN msAPI_BKFS_IsPartitionReady(U8 _diskDriveIndex,U8 _deviceIndex)
{
    if ((_diskDriveIndex==INVALID_DRIVE_INDEX) || (_deviceIndex==INVALID_DEVICE_INDEX))
    {
        __ASSERT(0);
        return FALSE;
    }
    else
    {
        if (!msAPI_FCtrl_IsDriveMounted(_diskDriveIndex))
        {
            msAPI_MSDCtrl_CheckDevices();
            if (msAPI_MSDCtrl_GetDeviceStatus(_deviceIndex)==MSD_STATUS_INSERTED)
            {
                if (msAPI_FCtrl_ActiveDevice(_deviceIndex))
                {
                    return TRUE;
                }
            }
        }
        else
        {
             return TRUE;
        }
    }

    return FALSE;
}

//Check disk's healthiness to verify if there has bad sectors
BOOLEAN BKFS_GetHealthinessSectorCount(U8 u8EnvironmentID, U32* u32HealthinessSectors)
{
    U32 u32BytesPerSec;
    U32 u32RootDirEndSectorNo;
    U32 u32SectorsPerBulk;
    U32 u32TotalSectors;
    U32* pu32=NULL;
    FAT_FileSysStruct* pFAT_FileSys;
    U8  u8DeviceID = msAPI_BKFS_GetDeviceIndex();
    U8  fsid;

    if (u8EnvironmentID >= FS_ENVIRONMENT_NUM)
        return FALSE;

    fsid = msAPI_FSEnv_GetEnvironment( u8EnvironmentID )->u8FileSystemID;
    pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemXData(fsid);
    u32TotalSectors = pFAT_FileSys->stBootSector.BPB_TotSec32;
    u32BytesPerSec = pFAT_FileSys->stBootSector.BPB_BytsPerSec;
    u32RootDirEndSectorNo = pFAT_FileSys->u32RootDirEndSectorNo;
    msAPI_FS_ReturnXData();
    u32SectorsPerBulk = (U32)(BULK_SIZE/u32BytesPerSec);
    *u32HealthinessSectors = u32TotalSectors;
    while (*u32HealthinessSectors > u32RootDirEndSectorNo)
    {
        //Set parity check data.
        if(!msAPI_MSDCtrl_SectorRead(u8DeviceID, *u32HealthinessSectors, 1, _PA2VA(IO_TEMP_ADDR)))
        {
            __ASSERT(0);
            return FALSE;
        }
        pu32=(U32 xdata*)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);
        pu32[0] = BULK_FS_MAGIC_HEADER;
        if(!msAPI_MSDCtrl_SectorWrite(u8DeviceID, *u32HealthinessSectors,1,_PA2VA(IO_TEMP_ADDR)))
        {
            __ASSERT(0);
            msAPI_FS_ReturnXData();
            return FALSE;
        }
        msAPI_FS_ReturnXData();

        //Get parity check data.
        if(!msAPI_MSDCtrl_SectorRead(u8DeviceID, *u32HealthinessSectors, 1, _PA2VA(IO_TEMP_ADDR)))
        {
            __ASSERT(0);
            msAPI_FS_ReturnXData();
            return FALSE;
        }
        pu32=(U32 xdata*)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);
        if (pu32[0] == BULK_FS_MAGIC_HEADER)
        {
            msAPI_FS_ReturnXData();
            break;
        }
        msAPI_FS_ReturnXData();

        //if remain disk is smaller than 1 BULK_SIZE, stop to check.
        if (*u32HealthinessSectors < (u32RootDirEndSectorNo+u32SectorsPerBulk))
        {
            *u32HealthinessSectors = u32RootDirEndSectorNo;
            break;
        }
        else
        {
            *u32HealthinessSectors -= u32SectorsPerBulk;
        }
    }

    return TRUE;
}

//Return cluster count
U32 BKFS_GetAvailableSectorCount(U8 u8EnvironmentID)
{
    FS_EnvironmentStruct* pFS_Env;
    FAT_FileSysStruct* pFAT_FileSys;
    U32 u32FileTotalSize = BULK_SIZE;
    U32 u32SectorsPerFile = 0;
    U32 u32TotalSectors = 0;
    U32 u32AvailableSectors = 0;
    U32 u32HealthinessSectors = 0;
    U32 u32FAT32Size = 0;
    U16 u16BytesPerSector = 0;
    U16 u16RsvdSecCnt = 0;
    U16 u16EstimatedBulkFileCnt = 0;
    U8  u8SectorPerCluster = 0;
    U8  u8NumFATs = 2;
    U16 u16BytesPerFileEntry = 0x1000;
    U32 u32SafeBoundSectors;
    U8  u8EstimatedSTTBLNodeCnt;
    U8  u8EstimatedAllocTBLNodeCnt;

    if (u8EnvironmentID >= FS_ENVIRONMENT_NUM) return 0;

    pFS_Env = msAPI_FSEnv_GetEnvironment(u8EnvironmentID);
    if (!pFS_Env) return 0;

    pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemXData(pFS_Env->u8FileSystemID);
    if (!pFAT_FileSys) return 0;

    u32TotalSectors = pFAT_FileSys->stBootSector.BPB_TotSec32;
    u8SectorPerCluster = pFAT_FileSys->stBootSector.BPB_SecPerClus;
    u16BytesPerSector = pFAT_FileSys->stBootSector.BPB_BytsPerSec;
    u16RsvdSecCnt = pFAT_FileSys->stBootSector.BPB_RsvdSecCnt;
    u8NumFATs = pFAT_FileSys->stBootSector.BPB_NumFATs;
    u32FAT32Size = pFAT_FileSys->stBootSector.BPB_FATSz32;
    FAT_ReturnXData();

    //[Check disk's healthiness to verify if there has bad sectors
    if (BKFS_GetHealthinessSectorCount(u8EnvironmentID, &u32HealthinessSectors))
        if (u32HealthinessSectors < u32TotalSectors)
            u32TotalSectors = u32HealthinessSectors;
    //]

    u32SectorsPerFile = (U32)(u32FileTotalSize / u16BytesPerSector); //(u32FileTotalSize/512)
    u16EstimatedBulkFileCnt = (U16)(u32TotalSectors / u32SectorsPerFile);

    u8EstimatedSTTBLNodeCnt = (u16EstimatedBulkFileCnt+IDX_BULK_START_SECTOR_TABLE_NODE_SIZE/4-1)/(IDX_BULK_START_SECTOR_TABLE_NODE_SIZE/4);
    u8EstimatedAllocTBLNodeCnt = (u16EstimatedBulkFileCnt+IDX_ALLOCATION_TABLE_NODE_SIZE/2-1)/(IDX_ALLOCATION_TABLE_NODE_SIZE/2);
    u8EstimatedSTTBLNodeCnt *= IDX_BULK_START_SECTOR_TABLE_NODE_SIZE/u16BytesPerSector;
    u8EstimatedAllocTBLNodeCnt *= IDX_ALLOCATION_TABLE_NODE_SIZE/u16BytesPerSector;
    /********************************************
    please reference FAT_Cache_SetFreeCluster()
    the gap for searching first free cluster is as following u32SafeBoundSize
    we should fixed it in FAT_Cache_SetFreeCluster(), but at this stage, I only patch at BULK FS here
    ********************************/
    u32SafeBoundSectors = (U32)((u16BytesPerSector*u8SectorPerCluster)/(4*0x100UL));

    // Total available sector = TotalSectors - BPBSize(512K) - 2*FATSize - RootDirectory(0) - ReservedSector -
    //                          BKFS folder directory sector(".", "..") - Cluster of (N-1) Bulk FileEntry
    u32AvailableSectors = u32TotalSectors -u8EstimatedSTTBLNodeCnt-u8EstimatedAllocTBLNodeCnt-
                    u32SafeBoundSectors- (u32FAT32Size*u8NumFATs) - u16RsvdSecCnt - ((u16EstimatedBulkFileCnt*u16BytesPerFileEntry)/u16BytesPerSector);

    return u32AvailableSectors;
}

//u16DiskSize is represent as MegaBytes
U16 BKFS_CalculateBulksNum(U8 u8EnvironmentID)
{
    FS_EnvironmentStruct* pFS_Env;
    FAT_FileSysStruct* pFAT_FileSys;
    U32 u32DiskAvailableSectors = 0;
    U32 u32SectorsOfDiskSize = 0;
    U32 u32FileTotalSize = BULK_SIZE;
    U32 u32EPGSectors;
    U32 u32SectorsOfBulk;
    U32 u32SectorsOfIndexFile;
    U16 u16BytesPerSector = 0;
    U16 u16BulksToCreate = 0;

    if (u8EnvironmentID >= FS_ENVIRONMENT_NUM) return 0;

    pFS_Env = msAPI_FSEnv_GetEnvironment(u8EnvironmentID);
    if (!pFS_Env) return 0;

    pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemXData(pFS_Env->u8FileSystemID);
    if (!pFAT_FileSys) return 0;

    u16BytesPerSector = pFAT_FileSys->stBootSector.BPB_BytsPerSec;
    FAT_ReturnXData();

    u32EPGSectors = (U32)((U32)EGP_FN_SIZE)/((U32)u16BytesPerSector);
    u32DiskAvailableSectors = BKFS_GetAvailableSectorCount(u8EnvironmentID)-u32EPGSectors;//reserve 4M EPG
    if (g_u32TotalDiskSizeMBSetToUsed != 0)
        u32SectorsOfDiskSize = g_u32TotalDiskSizeMBSetToUsed * ((U32)BYTES_PER_MEGA/((U32)u16BytesPerSector));
    else
        u32SectorsOfDiskSize = u32DiskAvailableSectors;
    if ((u32SectorsOfDiskSize == 0) || (u32SectorsOfDiskSize > u32DiskAvailableSectors)) //Request all disk size or Request over quota
        u16BulksToCreate = (U16)(u32DiskAvailableSectors/((U32)(u32FileTotalSize/u16BytesPerSector)));
    else u16BulksToCreate = (U16)(u32SectorsOfDiskSize/((U32)(u32FileTotalSize/u16BytesPerSector)));

    //if "disk total size" < "bulk size"+"index file size", need to reserver some disk size for index file.
    u32SectorsOfBulk = ((U32)u16BulksToCreate)*((U32)BULK_SIZE/(U32)u16BytesPerSector);
    u32SectorsOfIndexFile = ((U32)(u16BulksToCreate+4)*((U32)(0x1000/u16BytesPerSector)));
    if ((u32SectorsOfDiskSize - u32SectorsOfBulk) <= u32SectorsOfIndexFile) //index file size
        u16BulksToCreate -= (u32SectorsOfIndexFile/u32SectorsOfBulk)+1;

    g_u32TotalDiskSizeMBSetToUsed = ((U32)u16BulksToCreate)*(u32FileTotalSize/(U32)BYTES_PER_MEGA);
    return u16BulksToCreate;
}

void msAPI_BKFS_SetTotalDiskSizeUsedMB(U32 u32TotalDiskSizeSetToUsed)
{
    g_u32TotalDiskSizeMBSetToUsed = u32TotalDiskSizeSetToUsed;
    return;
}

U16 msAPI_BKFS_GetBulksNumToCreate(void)
{
    return g_u16BulksToCreate;
}

U32 msAPI_BKFS_GetDriveFreeSpaceMB(void)
{
    U32 u32DriveFreeSpaceMB = ((U32)g_u16FreeBulkCnt) * ((U32)(BULK_SIZE/BYTES_PER_MEGA));
    return u32DriveFreeSpaceMB;
}
LongLong msAPI_BKFS_FileTellAvailableWriteSpace(U8 handleID)
{
    LongLong len;
    U32  u32CurBULKRemainSize;
    BulkFileHandle* pHandle;
    len.Hi=0xFFFFFFFF;
    len.Lo=0xFFFFFFFF;

    if(msAPI_BKFS_IsInitialized() == FALSE)
    {
        __ASSERT(0);
        return len;
    }

    if(handleID>=MAX_BULK_FILE_HANDLE_NUM)
    {
        __ASSERT(0);
        return len;
    }

    pHandle=BKFS_GetBulkFileHandleXDATA();

    if(pHandle[handleID].HandleID==INVALID_FILE_HANDLE)
    {
        __ASSERT(0); //handle is closed
        msAPI_FS_ReturnXData();
        return len;
    }
    if(pHandle[handleID].OpenMode != BKF_OPEN_FOR_WRITE)
    {
        __ASSERT(0); //handle is closed
        msAPI_FS_ReturnXData();
        return len;
    }
    memcpy(&len,&pHandle[handleID].FileLength,sizeof(LongLong));
    msAPI_FS_ReturnXData();

    len.Hi = 0;
    u32CurBULKRemainSize = len.Lo%BULK_SIZE;
    if(u32CurBULKRemainSize)
        u32CurBULKRemainSize = BULK_SIZE-u32CurBULKRemainSize;
    len.Lo = msAPI_BKFS_GetDriveFreeSpaceMB();

    len = LL_multU32(len.Lo, 0x100000);
    len = LL_add(&len, u32CurBULKRemainSize);

    return len;
}
//For UI to redraw percentage of bulk creating process
void msAPI_BKFS_ResetCurrentCreateBulkNum(void)
{
    g_u16CurrentCreateBulkNum = 0;
    return;
}

U16 msAPI_BKFS_GetCurrentCreateBulkNum(void)
{
    return g_u16CurrentCreateBulkNum;
}

void msAPI_BKFS_SetCreateBulksState(EN_CREATE_BULKS_STATE enState)
{
    _enCreateBulksState = enState;
}

EN_CREATE_BULKS_STATE msAPI_BKFS_GetCreateBulksState(void)
{
    return _enCreateBulksState;
}

//[add for new FAT solution
static BOOLEAN BKFS_GetDirEntrySectorOffset(U8 u8Handle, U32* u32SectorNo, U32* u32DirEntryOffset)
{
    FAT_FileHandle *pFileHandle;
    FAT_FileInode *pFileInode;
    FAT_FileSysStruct* pFAT_FileSys;
    U32 u32DirEntryStartCluster;
    U32 u32DirEntryCountPerSector;
    U32 u32DirEntryCountPerCluster;
    U32 u32BytesPerSec;
    U32 u32SectorPerCluster;
    U8  u8FATType;
    U8  u8DeviceIndex;
    U8  u8Fsid;

    if(INVALID_FILE_HANDLE == u8Handle)
        return FALSE;

    pFileInode = FAT_File_GetInodeFromHandle( u8Handle);

    u32DirEntryStartCluster = pFileInode->u32DirStartCluster;
    *u32DirEntryOffset = pFileInode->u32DirEntryOffset;
    FCtrl_ReturnFileInodeXdata();


    pFileHandle = FAT_File_GetHandleXData(u8Handle);
    u8Fsid = pFileHandle->pub_fileheader.FileSystemID;

    pFAT_FileSys = (FAT_FileSysStruct*)FCtrl_GetFileSystemXData(u8Fsid);
    u8FATType = pFAT_FileSys->stFAT.u8FATType;
    u32BytesPerSec = pFAT_FileSys->stBootSector.BPB_BytsPerSec;
    u32SectorPerCluster = pFAT_FileSys->stBootSector.BPB_SecPerClus;
    u8DeviceIndex = pFAT_FileSys->DeviceIndex;
    msAPI_FS_ReturnXData();

    u32DirEntryCountPerSector = (u32BytesPerSec/sizeof(DirEntryStruct));
    u32DirEntryCountPerCluster = (u32DirEntryCountPerSector*u32SectorPerCluster);

    if((u8FATType == FAT_TYPE_FAT32) ||(u32DirEntryStartCluster!=0))
    {
        while(*u32DirEntryOffset >= u32DirEntryCountPerCluster)
        {
            u32DirEntryStartCluster = FAT_FATStructureGetNextCluster(u8Fsid, u32DirEntryStartCluster);
            if(u32DirEntryStartCluster == 0)
            {
                __ASSERT(0);
                return FALSE;
            }
            *u32DirEntryOffset -= u32DirEntryCountPerCluster;
        }
    }

    *u32SectorNo = FAT_FATGetSectorNo(u8Fsid, u32DirEntryStartCluster);
    *u32SectorNo += (*u32DirEntryOffset/u32DirEntryCountPerSector);
    *u32DirEntryOffset = (*u32DirEntryOffset % u32DirEntryCountPerSector);
    FCtrl_ReturnFileInodeXdata();

    return TRUE;
}

BOOLEAN msAPI_BKFS_Show_Hide_File(U8 u8Handle, BOOLEAN bShow)
{
    FAT_FileHandle *pFileHandle;
    FAT_FileSysStruct* pFAT_FileSys;
    U32 u32DirEntryOffset;
    U32 u32SectorNo;
    U16 u16AttrOffset;
    U8  u8DeviceIndex;
    U8  u8Fsid;
    U8* pu8 = NULL;

    if(INVALID_FILE_HANDLE == u8Handle)
        return FALSE;

    pFileHandle = FAT_File_GetHandleXData(u8Handle);
    u8Fsid = pFileHandle->pub_fileheader.FileSystemID;
    pFAT_FileSys = (FAT_FileSysStruct*)FCtrl_GetFileSystemXData(u8Fsid);
    u8DeviceIndex = pFAT_FileSys->DeviceIndex;
    msAPI_FS_ReturnXData();
    FAT_ReturnXData();
    if (!BKFS_GetDirEntrySectorOffset(u8Handle, &u32SectorNo, &u32DirEntryOffset))
    {
        __ASSERT(0);
        return FALSE;
    }

    if(!msAPI_MSDCtrl_SectorRead(u8DeviceIndex, u32SectorNo, 1, _PA2VA(IO_TEMP_ADDR)))
    {
        __ASSERT(0);
        return FALSE;
    }
    //[ Write DIR_Attr
    pu8=(U8 xdata*)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);
    u16AttrOffset = u32DirEntryOffset*0x20+0x0B; //0x20:FAT 32 Byte Directory Entry Structure, offset of attr is 0x0B.
    if (!bShow) pu8[u16AttrOffset] |= 0x2;
    else pu8[u16AttrOffset] |= 0x0;
    if(!msAPI_MSDCtrl_SectorWrite(u8DeviceIndex, u32SectorNo, 1, _PA2VA(IO_TEMP_ADDR)))
    {
        __ASSERT(0);
        msAPI_FS_ReturnXData();
        return FALSE;
    }
    msAPI_FS_ReturnXData();
    //]

    return TRUE;
}

static void BKFS_Show_Hide_Bulk_Folder(BOOLEAN bShow)
{
    U8 u8EnvironmentID;
    U8 u8Handle;
    FileEntry entry;
    U8 bkfsFolder[LENGTH_OF_BKFS_FOLDER];

    u8EnvironmentID = msAPI_FSEnv_Register(BKFS_DiskDriveIndex);
    if(u8EnvironmentID==INVALID_FS_ENVIRONMENT_INDEX)
    {
        return;
    }

    if(!msAPI_FCtrl_DirectoryChangeToRoot(u8EnvironmentID))
    {
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        return;
    }

    //check if the forlder _MSTBKFS existed or not
    memset(bkfsFolder, 0, sizeof(bkfsFolder));
    memcpy(bkfsFolder, BKFS_FOLDER, LENGTH_OF_BKFS_FOLDER);
    if(!msAPI_FCtrl_EntrySearchByShortName(u8EnvironmentID, bkfsFolder, LENGTH_OF_BKFS_FOLDER, &entry))
    {
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        return;
    }

    u8Handle = msAPI_FCtrl_DirectoryOpen(&entry, OPEN_MODE_FOR_READ_WRITE);
    if(u8Handle == INVALID_FILE_HANDLE)
    {
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        return;
    }
    msAPI_BKFS_Show_Hide_File(u8Handle, bShow);
    BKFS_FAT_CloseFiles(u8Handle);

    msAPI_FSEnv_UnRegister(u8EnvironmentID);
    return;
}
//#endif

///////////////////////////////////////////////////////////////////////
//1.Switch start cluster number in file entry
//2.Switch file total size in file entry
///////////////////////////////////////////////////////////////////////
static BOOLEAN BKFS_AssociateToBulk(U8 u8HandleS, U8 u8HandleT)
{
    FAT_FileInode *pFileInodeS, *pFileInodeT;
    U32 u32FileStartClusterNoT, u32FileTotalSizeT;
    //U32 u32FileTotalSizeS, u32FileStartClusterNoS;

    if((INVALID_FILE_HANDLE == u8HandleS) || (INVALID_FILE_HANDLE == u8HandleT))
        return FALSE;

    //Retrieve file start clusterNo and file total size from source file
    /*pFileHandleS = FAT_File_GetHandleXData(u8HandleS);
    u32FileStartClusterNoS = pFileHandleS->u32FileStartClusterNo;
    u32FileTotalSizeS = pFileHandleS->u32FileTotalSize;
    FAT_ReturnXData();*/ //dont need to update u32FileStartClusterNo

    //Retrieve and update file start clusterNo and file total size from target file
    pFileInodeT = FAT_File_GetInodeFromHandle(u8HandleT);
    u32FileStartClusterNoT = pFileInodeT->u32FileStartClusterNo;
    //pFileHandleT->u32FileStartClusterNo = u32FileStartClusterNoS; //dont need to update u32FileStartClusterNo
    u32FileTotalSizeT = pFileInodeT->u32FileTotalSize;
    pFileInodeT->u32FileTotalSize = 0;//u32FileTotalSizeS;
    FCtrl_ReturnFileInodeXdata();

    //Update file start clusterNo and file total size from source file
    pFileInodeS = FAT_File_GetInodeFromHandle(u8HandleS);
    pFileInodeS->u32FileStartClusterNo = u32FileStartClusterNoT;
    pFileInodeS->u32FileTotalSize = u32FileTotalSizeT;
    FCtrl_ReturnFileInodeXdata();
    //Always need to call msAPI_FCtrl_FileClose() continually to update data on physical disk.

    return TRUE;
}

///////////////////////////////////////////////////////////////////////
//Update file total size in file entry of specific bulk
///////////////////////////////////////////////////////////////////////
static BOOLEAN BKFS_UpdateFileSize(U8 u8Handle, U32 u32Size)
{
    FAT_FileInode *pFileInode;

    if(INVALID_FILE_HANDLE == u8Handle)
        return FALSE;

    //Update file total size
    pFileInode = FAT_File_GetInodeFromHandle(u8Handle);
    pFileInode->u32FileTotalSize = u32Size;
    /*if (u32Size  == 0)
        pFileHandle->u32FileStartClusterNo = 0x0;*/  //set DIR_FstClusHI and DIR_FstClusLO to 0x0.
    FCtrl_ReturnFileInodeXdata();
    //Always need to call msAPI_FCtrl_FileClose() continually to update data on physical disk.

    return TRUE;
}

///////////////////////////////////////////////////////////////////////
//Update file start cluster No in file entry of specific bulk
///////////////////////////////////////////////////////////////////////
#if 0
static BOOLEAN BKFS_UpdateFileStartClusterNo(U8 u8Handle, U32 u32FileStartClusterNo)
{
    FAT_FileHandle *pFileHandle;

    if(INVALID_FILE_HANDLE == u8Handle)
        return FALSE;

    //Update file total size
    pFileHandle = FAT_File_GetHandleXData(u8Handle);
    pFileHandle->u32FileStartClusterNo = u32FileStartClusterNo;
    FAT_ReturnXData();
    //Always need to call msAPI_FCtrl_FileClose() continually to update data on physical disk.

    return TRUE;
}
#endif

#if 0
static U16 BKFS_GetMaxRecordBulkCnt(void)
{
    if (BKFS_TotalBulkNumber > 0)
        return (((U16)BKFS_TotalBulkNumber) - msAPI_BKFS_GetTimeShiftReservedBulkCnt());
    return 0;
}
#endif
///////////////////////////////////////////////////////////////////////
//1.Connect two bulk files to one bulk file
//2.Update latest used cluster(0xFFFFFF0F) of one bulk to next cluster
///////////////////////////////////////////////////////////////////////
static BOOLEAN BKFS_ConnectBulks(U8 u8EnvironmentID, U16 u16CurrentBulkID, U16 u16NextBulk)
{
    FAT_FileSysStruct *pFAT_FileSys;
    U8 u8BulkHandle;
    U8 fsid;
    U8 u8SectorPerCluster;
    U32* pu32;
    U32 u32FATStartSectorNo;
    U32 u32FATFileEndClusterSectorNo;
    U16 u16OffsetIntoFATSector;
    U32 u32FATOffsetOfBulk; //cluster usage of 64MB file needs 0x80 sectors(BPB_SecPerClus = 4), (4->0x100, 8->0x80, 16->0x40)
    U32 u32CurrentEndCluster;//should equal 0x20+0x80*(u16CurrentBulkID); //end cluster address in FAT
    U32 u32NextStartCluster;
    U32 u32RootDirEndSectorNo;
    U8   uDeviceID = msAPI_BKFS_GetDeviceIndex();

    if ((u16CurrentBulkID > BKFS_TotalBulkNumber) || (u16NextBulk > BKFS_TotalBulkNumber) ||
        (u8EnvironmentID >= FS_ENVIRONMENT_NUM))
    {
        __ASSERT(0);
        return FALSE;
    }

    fsid = msAPI_FSEnv_GetEnvironment(u8EnvironmentID)->u8FileSystemID;
    pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemXData(fsid);
    u8SectorPerCluster = pFAT_FileSys->stBootSector.BPB_SecPerClus;
    u32FATStartSectorNo = pFAT_FileSys->stFAT.u32FATStartSectorNo;
    u32RootDirEndSectorNo = pFAT_FileSys->u32RootDirEndSectorNo;
    u32FATOffsetOfBulk = BULK_SIZE/pFAT_FileSys->stBootSector.BPB_BytsPerSec;
    FAT_ReturnXData();

    u32FATOffsetOfBulk = u32FATOffsetOfBulk/u8SectorPerCluster;
    u32CurrentEndCluster = (BKFS_GetBulkStartSector(u16CurrentBulkID)-u32RootDirEndSectorNo)/u8SectorPerCluster+2;
    u32CurrentEndCluster += u32FATOffsetOfBulk-1;
    u32NextStartCluster =  (BKFS_GetBulkStartSector(u16NextBulk)-u32RootDirEndSectorNo)/u8SectorPerCluster+2;

    u32FATFileEndClusterSectorNo = u32CurrentEndCluster/128+u32FATStartSectorNo;
    u16OffsetIntoFATSector = u32CurrentEndCluster&127;

    //read sector data from FAT
    if(!msAPI_MSDCtrl_SectorRead(uDeviceID, u32FATFileEndClusterSectorNo,1,_PA2VA(IO_TEMP_ADDR)))
    {
        __ASSERT(0);
        return FALSE;
    }
    pu32=(U32 xdata*)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);
    if(pu32[u16OffsetIntoFATSector] != (U32)BKFSSwap32(0x0FFFFFFF))
    {
        __ASSERT(0);
        return FALSE;
    }
    pu32[u16OffsetIntoFATSector] = BKFSSwap32(u32NextStartCluster);
    //u32NextCluster = BKFSSwap32(BKFSSwap32(pu32[2])+1); //assign to next clustor(cluster+1)
   // pu32[3] = nextStartSector/u8SectorPerCluster;
    msAPI_FS_ReturnXData();
    //write next clustor to specific address in FAT
    if(!msAPI_MSDCtrl_SectorWrite(uDeviceID, u32FATFileEndClusterSectorNo,1,_PA2VA(IO_TEMP_ADDR)))
    {
        __ASSERT(0);
        return FALSE;
    }

    //Update file size of next bulk to '0' KB
    u8BulkHandle = BKFS_SearchBulkByIndex(u8EnvironmentID, u16NextBulk);
    if(u8BulkHandle == INVALID_FILE_HANDLE)
    {
        __ASSERT(0);
        return FALSE;
    }
    if (!BKFS_UpdateFileSize(u8BulkHandle, 0))
    {
        BKFS_FAT_CloseFiles(u8BulkHandle); //close bulk file to update directory entry data
        __ASSERT(0);
        return FALSE;
    }

    //[Update start clusterNo to '0' of BulkN
    /*if (!BKFS_UpdateFileStartClusterNo(u8BulkHandle, 0))
    {
        BKFS_FAT_CloseFiles(u8BulkHandle); //close bulk file to update directory entry data
        __ASSERT(0);
        return FALSE;
    }*/
    //]

    BKFS_FAT_CloseFiles(u8BulkHandle); //close bulk file to update directory entry data
    return TRUE;
}

///////////////////////////////////////////////////////////////////////
//Refill FAT table of specific bulk, update it's cluster usage
///////////////////////////////////////////////////////////////////////
BOOLEAN BKFS_RefillBulkFATTable(U8 u8EnvironmentID, U16 u16BulkIndex)
{
    FAT_FileSysStruct *pFAT_FileSys;
    U8 fsid;
    U8 u8SectorPerCluster;
    U8 u8SectorsReadPerRun = 8;
    U16 u16BytesPerSector;
    U16 u16ClusterCntPerRun;
    U32* pu32;
    U32 u32FATStartSectorNo;
    U32 u32FATFileStartClusterSectorNo; //start cluster address in FAT
    U32 u32RootDirEndSectorNo;
    U32 u32CurrentStartCluster;
    U32 u32ClustersPerBulk;
    U32 u32CurrentStartClusterNo;
    U32 u32OffsetIntoFATSector;
    U32 u32Index=0, u32CurrentRun=1, u32TotalRun, u32Count = 0;
    U8   uDeviceID = msAPI_BKFS_GetDeviceIndex();

    if ((u8EnvironmentID >= FS_ENVIRONMENT_NUM)  || (u16BulkIndex > BKFS_TotalBulkNumber))
        return FALSE;

    fsid = msAPI_FSEnv_GetEnvironment(u8EnvironmentID)->u8FileSystemID;
    pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemXData(fsid);
    u16BytesPerSector = pFAT_FileSys->stBootSector.BPB_BytsPerSec;
    u8SectorPerCluster = pFAT_FileSys->stBootSector.BPB_SecPerClus;
    u32FATStartSectorNo = pFAT_FileSys->stFAT.u32FATStartSectorNo;
    u32RootDirEndSectorNo = pFAT_FileSys->u32RootDirEndSectorNo;
    FAT_ReturnXData();
    u32CurrentStartCluster = (BKFS_GetBulkStartSector(u16BulkIndex)-u32RootDirEndSectorNo)/u8SectorPerCluster+2;
    u32FATFileStartClusterSectorNo = u32CurrentStartCluster/128+u32FATStartSectorNo;
    u32OffsetIntoFATSector = u32CurrentStartCluster&127;
    u32ClustersPerBulk = (U32)(BULK_SIZE/(u8SectorPerCluster*u16BytesPerSector));
    u16ClusterCntPerRun = (U16)((u8SectorsReadPerRun*u16BytesPerSector)/4);
    u32TotalRun = (U32)((u32ClustersPerBulk/u16ClusterCntPerRun));
    if (u32OffsetIntoFATSector > 0) u32TotalRun++; //need to read extra one sector since there exists offset.
    u32CurrentStartClusterNo = (U32)(u32OffsetIntoFATSector+(u32ClustersPerBulk*(u16BulkIndex-1)));

    u32Index = u32OffsetIntoFATSector; //normally it starts from index=4
    while(u32CurrentRun <= u32TotalRun)
    {
        //read sector data from FAT
        if(!msAPI_MSDCtrl_SectorRead(uDeviceID, u32FATFileStartClusterSectorNo+(u8SectorsReadPerRun*(u32CurrentRun-1)),u8SectorsReadPerRun,_PA2VA(IO_TEMP_ADDR)))
        {
            __ASSERT(0);
            return FALSE;
        }
        pu32=(U32 xdata*)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);
        if (u32CurrentRun == u32TotalRun) //write tail for u32OffsetIntoFATSector.
        {
            while(u32Index < u32OffsetIntoFATSector) //read to the offset address
            {
                if (u32Index == (u32OffsetIntoFATSector-1))
                    pu32[u32Index] = BKFSSwap32(0x0FFFFFFF); //last run, write tail
                else
                  pu32[u32Index] = BKFSSwap32(u32CurrentStartClusterNo+1+u32Count); //last run, write next cluster
                u32Index++;
                u32Count++;
            }
        }
        else
        {
            while (u32Index < u16ClusterCntPerRun) //write normal allocation of cluster
            {
                pu32[u32Index] = BKFSSwap32(u32CurrentStartClusterNo+1+u32Count); //write next cluster
                u32Index++;
                u32Count++;
            }
        }
        //write next clustor to specific address in FAT
        if(!msAPI_MSDCtrl_SectorWrite(uDeviceID, u32FATFileStartClusterSectorNo+(u8SectorsReadPerRun*(u32CurrentRun-1)),u8SectorsReadPerRun, _PA2VA(IO_TEMP_ADDR)))
        {
            __ASSERT(0);
            msAPI_FS_ReturnXData();
            return FALSE;
        }
        u32Index = 0;
        u32CurrentRun++;
        msAPI_FS_ReturnXData();
    }

    return TRUE;
}

///////////////////////////////////////////////////////////////////////
//Renew bulkN, update it's end cluster and file size
///////////////////////////////////////////////////////////////////////
static BOOLEAN BKFS_RenewBulk(U8 u8EnvironmentID, U16 u16BulkIndex, BOOLEAN bFillFATTable)
{
    FAT_FileSysStruct *pFAT_FileSys;
    U8 u8BulkHandle;
    U8 fsid;
    U8 u8SectorPerCluster;
    //U8 u8DefaultSectorPerCluster = 4;
    //U8 u8BPB_SecPerClus;
    U32* pu32;
    U32 u32FATStartSectorNo;
    U16 u16OffsetIntoFATSector;
    U32 u32FATOffsetOfBulk; //cluster usage of 64MB file needs 0x80 sectors(BPB_SecPerClus = 4), (4->0x100, 8->0x80, 16->0x40)
    U32 u32FATFileEndClusterSectorNo; //end cluster address in FAT
    U32 u32RootDirEndSectorNo;
    U32 u32CurrentEndCluster;
    U8   uDeviceID = msAPI_BKFS_GetDeviceIndex();
    //U32 u32BulkStartSectorNo; //Start sector number of BulkN
    //U32 u32BulkStartClusterNo; //Start cluster number of BulkN, calculated from u32BulkStartSectorNo

    if ((u8EnvironmentID >= FS_ENVIRONMENT_NUM)  || (u16BulkIndex > BKFS_TotalBulkNumber))
        return FALSE;

    fsid = msAPI_FSEnv_GetEnvironment(u8EnvironmentID)->u8FileSystemID;
    pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemXData(fsid);
    u8SectorPerCluster = pFAT_FileSys->stBootSector.BPB_SecPerClus;
    u32FATStartSectorNo = pFAT_FileSys->stFAT.u32FATStartSectorNo;
    //u32RootDirEndSectorNo = pFAT_FileSys->u32RootDirEndSectorNo;
    //u8BPB_SecPerClus = pFAT_FileSys->stBootSector.BPB_SecPerClus;
    u32RootDirEndSectorNo = pFAT_FileSys->u32RootDirEndSectorNo;
    u32FATOffsetOfBulk = BULK_SIZE/pFAT_FileSys->stBootSector.BPB_BytsPerSec;
    FAT_ReturnXData();

    u32FATOffsetOfBulk = u32FATOffsetOfBulk/u8SectorPerCluster;
    u32CurrentEndCluster = (BKFS_GetBulkStartSector(u16BulkIndex)-u32RootDirEndSectorNo)/u8SectorPerCluster+2;
    u32CurrentEndCluster += u32FATOffsetOfBulk-1;

    u32FATFileEndClusterSectorNo = u32CurrentEndCluster/128+u32FATStartSectorNo;
    u16OffsetIntoFATSector = u32CurrentEndCluster&127;

    //read sector data from FAT
    if(!msAPI_MSDCtrl_SectorRead(uDeviceID, u32FATFileEndClusterSectorNo,1,_PA2VA(IO_TEMP_ADDR)))
    {
        __ASSERT(0);
        return FALSE;
    }
    pu32=(U32 xdata*)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);
    pu32[u16OffsetIntoFATSector] = BKFSSwap32(0x0FFFFFFF); //assign ending symbol "0xFFFFFF0F" of this file in FAT
    msAPI_FS_ReturnXData();

    //write next clustor to specific address in FAT
    if(!msAPI_MSDCtrl_SectorWrite(uDeviceID, u32FATFileEndClusterSectorNo,1, _PA2VA(IO_TEMP_ADDR)))
    {
        __ASSERT(0);
        return FALSE;
    }

    //Update file size of next bulk to 'BULK_SIZE' KB
    u8BulkHandle = BKFS_SearchBulkByIndex(u8EnvironmentID, u16BulkIndex);
    if(u8BulkHandle == INVALID_FILE_HANDLE)
    {
        __ASSERT(0);
        return FALSE;
    }
    if (!BKFS_UpdateFileSize(u8BulkHandle, BULK_SIZE))
    {
        BKFS_FAT_CloseFiles(u8BulkHandle); //close bulk file to update directory entry data
        __ASSERT(0);
        return FALSE;
    }

    //[Update start clusterNo of BulkN
    /*if (!BKFS_FetchBulkStartSectorTable())
    {
        BKFS_FAT_CloseFiles(u8BulkHandle); //close bulk file to update directory entry data
        __ASSERT(0);
        return FALSE;
    }
    pu32=(U32 xdata*)msAPI_FS_GetXData(BULK_START_SECTOR_TABLE_ADDR>>12);
    u32BulkStartSectorNo = pu32[u16BulkIndex];
    msAPI_FS_ReturnXData();
    u32BulkStartClusterNo = ((u32BulkStartSectorNo - u32RootDirEndSectorNo)/u8BPB_SecPerClus)+2;
    if (!BKFS_UpdateFileStartClusterNo(u8BulkHandle, u32BulkStartClusterNo))
    {
        BKFS_FAT_CloseFiles(u8BulkHandle); //close bulk file to update directory entry data
        __ASSERT(0);
        return FALSE;
    }*/
    //]

    BKFS_FAT_CloseFiles(u8BulkHandle);

    if (bFillFATTable)
    {
        if (!BKFS_RefillBulkFATTable(u8EnvironmentID, u16BulkIndex))
        {
            __ASSERT(0);
            return FALSE;
        }
    }

    return TRUE;
}

#if ENABLE_TO_AUTO_RESUME_ALL_BULKS
BOOLEAN BKFS_Remove_Invalid_BulkFileEntry(U8 u8EnvironmentID, BulkFileEntry* pBulkFile)
{
    U16 i, uNameLen;
    BOOLEAN bRemoved = FALSE;
    U8 u8Handle;
    FileEntry  entry;
    //printf("check bulk file %d\n", pBulkFile->BulkFileID);

    if(!msAPI_FCtrl_DirectoryChangeToRoot(u8EnvironmentID))
    {
            __ASSERT(0);
            return FALSE;
    }

    i = 0;
    while(i<pBulkFile->uFatSegTsFileCnt)
    {
        uNameLen = FS_strlen_U(pBulkFile->fatSegNameTBL+pBulkFile->fatSegTSFileNameOffset[i]);

        if(uNameLen==0 || uNameLen>=MAX_FAT_SEG_FILENAME_LEN)
        {
              if(bRemoved == FALSE)
              {
                  i=0;//reset i to remove all split files
                  bRemoved = TRUE;
              }
              else
              {
                 i++;
              }
              continue;
        }
        memcpy(g_segFilename, pBulkFile->fatSegNameTBL+pBulkFile->fatSegTSFileNameOffset[i],
                                                           (uNameLen+1)*sizeof(U16));
       if(!msAPI_FCtrl_EntrySearchByName(u8EnvironmentID, g_segFilename, uNameLen, &entry))
        {
              if(bRemoved == FALSE)
              {
                  i=0;//reset i to remove all split files
                  bRemoved = TRUE;
              }
              else
              {
                 i++;
              }
             continue;
        }

        i++;

       if(bRemoved == FALSE)
       {
           continue;
       }

        u8Handle = msAPI_FCtrl_FileOpen(&entry, OPEN_MODE_FOR_READ_WRITE);
        if(u8Handle == INVALID_FILE_HANDLE)
        {
               __ASSERT(0);
              return FALSE;
         }
        BKFS_TrimFAT32RecordFile(u8Handle);
        BKFS_FAT_CloseFiles(u8Handle);

         //Set lenght fo file entry to "0" to prevent from clearing FAT table.
        entry.FileLength.Lo = 0;
        entry.FileLength.Hi = 0;
       if (!msAPI_FCtrl_FileDelete(&entry))
       {
             __ASSERT(0);
             return FALSE;
        }
    }
    //printf("     result %s\n", bRemoved?"Deleted":"Pass");
    return bRemoved;
}
#endif

#if ENABLE_TO_AUTO_RESUME_ALL_BULKS
BOOLEAN BKFS_ResumeAllBulks(void)
{
    U16 u16MaxUsedBulkFileEntryIndex = msAPI_BKFS_GetMaxUsedBulkFileEntryIndex();
    U16 u16Index, u16StartIndex;
    U8 u8EnvironmentID = msAPI_FSEnv_Register(BKFS_DiskDriveIndex);
    BulkFileEntry* pBulkFile;
    FileEntry entry;

    if(u8EnvironmentID==INVALID_FS_ENVIRONMENT_INDEX)
        return FALSE;

    if (msAPI_BKFS_GetTimeShiftReservedBulkCnt() > 0)
        u16StartIndex = 2; //skip time shift bulk file entry.
    else u16StartIndex = 1;
    for (u16Index = u16StartIndex; u16Index <= u16MaxUsedBulkFileEntryIndex; u16Index++)
    {
        pBulkFile = BKFS_GetBulkFileEntryXDATA(u16Index);
        if(pBulkFile == NULL)
        {
            msAPI_FS_ReturnXData();
            continue;
        }
        if(pBulkFile->BulkFileID==0)
        {
            msAPI_FS_ReturnXData();
            continue;
        }

        //Change to root directory
        if(!msAPI_FCtrl_DirectoryChangeToRoot(u8EnvironmentID))
        {
            msAPI_FSEnv_UnRegister(u8EnvironmentID);
            msAPI_FS_ReturnXData();
            __ASSERT(0);
            return FALSE;
        }

        if(!msAPI_FCtrl_EntrySearchByName(u8EnvironmentID, pBulkFile->FileName, FS_strlen_U(pBulkFile->FileName), &entry))
        {
            U16 u16StartBulkID = pBulkFile->StartBulkID;
            U16 u16BulkID = pBulkFile->StartBulkID;
            U16 u16BulkfileID = pBulkFile->BulkFileID;

            if (!BKFS_Remove_Invalid_BulkFileEntry(u8EnvironmentID, pBulkFile))
            {
                BKFSDBG(printf("BKFS: Can't find invalid TS file entry\n"));
            }
            //Update file size of all used bulks to be 'BULK_SIZE' KB
            while(u16BulkID!=LAST_BULK_ID && u16BulkID<=BKFS_TotalBulkNumber)
            {
                if (!BKFS_RenewBulk(u8EnvironmentID, u16BulkID, TRUE)) //need to refill FAT table
                {
                    msAPI_FSEnv_UnRegister(u8EnvironmentID);
                    msAPI_FS_ReturnXData();
                    __ASSERT(0);
                    return FALSE;
                }
                u16BulkID = BKFS_GetBulkValue(u16BulkID);
            }

            memset(pBulkFile, 0, BULK_FILE_ENTRY_SIZE);
            msAPI_FS_ReturnXData();
            //write the BulkFileEntry cached in BULK_FILE_ENTRY_ADDR back
            ioassert(BKFS_WriteBulkFileEntry(u16BulkfileID, _PA2VA(BULK_FILE_ENTRY_ADDR)));
            ioassert(BKFS_FreeBulks(u16StartBulkID, FALSE));
        }
        else
        {
            msAPI_FS_ReturnXData();
        }
    }

    msAPI_FSEnv_UnRegister(u8EnvironmentID);
    return TRUE;
}
#endif

static BOOLEAN BKFS_GetBKFSFolderCreatedDT(U32 *u32BulkFolderCreatedDT)
{
    U8 u8EnvironmentID = msAPI_FSEnv_Register(BKFS_DiskDriveIndex);
    U8 u8Handle;
    U8 u8DeviceIndex;
    U8 u8Fsid;
    U8 bkfsFolder[LENGTH_OF_BKFS_FOLDER];
    U16* pu16 = NULL;
    U32 u32DirEntryOffset;
    U32 u32SectorNo;
    U32 u32OffsetAddr;
    FileEntry entry;
    FAT_FileHandle *pFileHandle;
    FAT_FileSysStruct* pFAT_FileSys;

    if(u8EnvironmentID==INVALID_FS_ENVIRONMENT_INDEX)
    {
        __ASSERT(0);
        return FALSE;
    }

    //Change to root directory
    if(!msAPI_FCtrl_DirectoryChangeToRoot(u8EnvironmentID))
    {
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        return FALSE;
    }

    //check if the forlder _MSTBKFS existed or not
    memset(bkfsFolder, 0, sizeof(bkfsFolder));
    memcpy(bkfsFolder, BKFS_FOLDER, LENGTH_OF_BKFS_FOLDER);
    if(!msAPI_FCtrl_EntrySearchByShortName(u8EnvironmentID,bkfsFolder, LENGTH_OF_BKFS_FOLDER, &entry))
    {
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        return FALSE;
    }

    if(entry.EntryType!=ENTRY_TYPE_DIR)
    {
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        return FALSE;
    }

    u8Handle = msAPI_FCtrl_DirectoryOpen(&entry, OPEN_MODE_FOR_READ_WRITE);
    if(u8Handle == INVALID_FILE_HANDLE)
    {
        __ASSERT(0);
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        return FALSE;
    }

    pFileHandle = FAT_File_GetHandleXData(u8Handle);
    u8Fsid = pFileHandle->pub_fileheader.FileSystemID;
    pFAT_FileSys = (FAT_FileSysStruct*)FCtrl_GetFileSystemXData(u8Fsid);
    u8DeviceIndex = pFAT_FileSys->DeviceIndex;
    msAPI_FS_ReturnXData();
    FAT_ReturnXData();
    if (!BKFS_GetDirEntrySectorOffset(u8Handle, &u32SectorNo, &u32DirEntryOffset))
    {
        __ASSERT(0);
        BKFS_FAT_CloseFiles(u8Handle);
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        return FALSE;
    }

    if(!msAPI_MSDCtrl_SectorRead(u8DeviceIndex, u32SectorNo, 1, _PA2VA(IO_TEMP_ADDR)))
    {
        __ASSERT(0);
        BKFS_FAT_CloseFiles(u8Handle);
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        return FALSE;
    }
    //[ Get DIR_entry data
    u32OffsetAddr = (u32DirEntryOffset*0x10); //if U8: *0x20, if U16: *0x10, if U32: *0x08.
    pu16=(U16 xdata*)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);
    *u32BulkFolderCreatedDT = BKFSSwap16(pu16[u32OffsetAddr+7]);
    *u32BulkFolderCreatedDT = *u32BulkFolderCreatedDT << 16;
    *u32BulkFolderCreatedDT ^= BKFSSwap16(pu16[u32OffsetAddr+8]);
    msAPI_FS_ReturnXData();

    BKFS_FAT_CloseFiles(u8Handle);
    msAPI_FSEnv_UnRegister(u8EnvironmentID);
    return TRUE;
}

static U32 BKFS_GetBulkFolderCreatedDateTime(void)
{
    U32* pu32=NULL;
    U32 u32BulkFolderCreatedDT;
    U32 sectorAddr= IDX_FILE_StartSector;
    U8   uDeviceID = msAPI_BKFS_GetDeviceIndex();

    if(msAPI_BKFS_IsInitialized() == FALSE)
    {
        __ASSERT(0);
        return 0;
    }

    if(!msAPI_MSDCtrl_SectorRead(uDeviceID, sectorAddr,1,_PA2VA(IO_TEMP_ADDR)))
    {
        __ASSERT(0);
        return 0;
    }

    pu32=(U32 xdata*)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);
    GET_MISCINFO(u32BulkFolderCreatedDT, BULK_FOLDER_CREATED_DT, pu32);
    msAPI_FS_ReturnXData();

    return u32BulkFolderCreatedDT;
}

static BOOLEAN BKFS_CheckBulkFolderCreatedDateTime(void)
{
    U32 u32BulkFolderCreatedDT;

    //check if the bulk folder is not modified.
    if (!BKFS_GetBKFSFolderCreatedDT(&u32BulkFolderCreatedDT))
    {
        BKFSDBG(printf("  BKFS Initiate FAIL : Can't get the creation date time of bulk folder at DriveIndex=%bu of DeviceIndex=%bu!!\n",BKFS_DiskDriveIndex,BKFS_DeviceID));
        __ASSERT(0);
        return FALSE;
    }

    if(u32BulkFolderCreatedDT != BKFS_GetBulkFolderCreatedDateTime())
    {
        BKFSDBG(printf("  BKFS Initiate FAIL : The bulk folder has been modified at DriveIndex=%bu of DeviceIndex=%bu!!\n",BKFS_DiskDriveIndex,BKFS_DeviceID));
        return FALSE;
    }
    return TRUE;
}

BOOLEAN msAPI_BKFS_Initial(BOOLEAN force)
{
    U8 envId=INVALID_FS_ENVIRONMENT_INDEX;

    if(BKFS_Initialized)
    {
        BKFSDBG(printf("BKFS already initialized at DriveIndex=%bu of DeviceIndex=%bu\n",BKFS_DiskDriveIndex,BKFS_DeviceID));
        if(force)
        {
            BKFSDBG(printf("  Force to initial BKFS again!!\n"));
            BKFS_Initialized=FALSE;
        }
        else
        {
                return TRUE;
        }
    }

    BKFSDBG(printf("  Start to initial BKFS!!\n"));

    if (!BKFS_PrepareDrive())
    {
        //__ASSERT(0);
    }
    else
    {
        if(BKFS_DiskDriveIndex==INVALID_DRIVE_INDEX)
        {
            U8 i;
            for(i=0;i<DISK_DRIVE_NUM;i++)
            {
                if(msAPI_FCtrl_IsDriveMounted(i))
                {
                    BKFS_DiskDriveIndex=i;
                }
            }
        }
        envId=msAPI_FSEnv_Register(BKFS_DiskDriveIndex);
        if(envId==INVALID_FS_ENVIRONMENT_INDEX)
        {
            __ASSERT(0);
        }
        else
        {
            if(!BKFS_Initial(envId))
            {
                msAPI_FSEnv_UnRegister(envId);
                BKFSDBG(printf("  BKFS Initialize FAIL !! at DriveIndex=%bu of DeviceIndex=%bu!!\n",BKFS_DiskDriveIndex,BKFS_DeviceID));
                return FALSE;
            }
            else
            {
                msAPI_FSEnv_UnRegister(envId);
                BKFS_Initialized=TRUE;
                if (!BKFS_CheckBulkFolderCreatedDateTime())
                {
                    BKFS_Initialized=FALSE;
                    return FALSE;
                }
                #if ENABLE_TO_AUTO_RESUME_ALL_BULKS
                BKFS_ResumeAllBulks(); //auto check if all TS file and bulk are matched
                #endif
                BKFSDBG(printf("  BKFS Initialize success at DriveIndex=%bu of DeviceIndex=%bu!!\n",BKFS_DiskDriveIndex,BKFS_DeviceID));
                return TRUE;
            }
        }

    }

    BKFSDBG(printf("  BKFS Initialize failed at DriveIndex=%bu of DeviceIndex=%bu!!\n",BKFS_DiskDriveIndex,BKFS_DeviceID));
    return FALSE;
}


///////////////////////////////////////////////////////////////////////////////
//1.Find the record path file and bulk file with
//2.Renew all used bulks
//  a.Switch start cluster between recorded file and bulk file
//  b.Switch file total size in file entry between recorded file and bulk file
//  c.Close record file and bulk file
///////////////////////////////////////////////////////////////////////////////
BOOLEAN BKFS_DeleteRecordPathFiles(BulkFileEntry *pBulkFile)
{
    U8 u8DiskDriveIndex = msAPI_BKFS_GetDriveIndex();
    //U8 u8DeviceIndex = msAPI_BKFS_GetDeviceIndex();
    U8 u8EnvironmentID = INVALID_FS_ENVIRONMENT_INDEX;
    U8 u8Handle;
    U8 u8Index;
    U16 u16StartBulkID;
    U16 uNameLen;
    BOOLEAN bFillFatTbl=FALSE;

   // BulkFileEntry* pBulkFile;
    FileEntry entry;
    LongLong llBulkFileLength;

    u16StartBulkID = pBulkFile->StartBulkID;
    llBulkFileLength = pBulkFile->FileLength;

    u8EnvironmentID = msAPI_FSEnv_Register(u8DiskDriveIndex);
    if (u8EnvironmentID >= FS_ENVIRONMENT_NUM)
    {
        __ASSERT(0);
        return FALSE;
    }

    //Change to root directory
    if(!msAPI_FCtrl_DirectoryChangeToRoot(u8EnvironmentID))
    {
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        __ASSERT(0);
        return FALSE;
    }
    for( u8Index=0; u8Index<pBulkFile->uFatSegTsFileCnt; u8Index++)
    {

       SPLIT_DBG(printf("Delete record file  %s\n",
                         Unicode2ASCII(pBulkFile->fatSegNameTBL+pBulkFile->fatSegTSFileNameOffset[u8Index])));

        uNameLen = FS_strlen_U(pBulkFile->fatSegNameTBL+pBulkFile->fatSegTSFileNameOffset[u8Index]);

        if(uNameLen==0 || uNameLen>=MAX_FAT_SEG_FILENAME_LEN)
        {
              msAPI_FSEnv_UnRegister(u8EnvironmentID);
              __ASSERT(0);
              return FALSE;
        }
        memcpy(g_segFilename, pBulkFile->fatSegNameTBL+pBulkFile->fatSegTSFileNameOffset[u8Index],
                                                           (uNameLen+1)*sizeof(U16));
       if(!msAPI_FCtrl_EntrySearchByName(u8EnvironmentID, g_segFilename, uNameLen, &entry))
        {
           SPLIT_DBG(printf("Find record file  %s in root directory failed\n",Unicode2ASCII(g_segFilename)));
           bFillFatTbl=TRUE;
           continue;
        }

        u8Handle = msAPI_FCtrl_FileOpen(&entry, OPEN_MODE_FOR_READ_WRITE);
        if(u8Handle == INVALID_FILE_HANDLE)
        {
               msAPI_FSEnv_UnRegister(u8EnvironmentID);
               __ASSERT(0);
              return FALSE;
         }
        BKFS_TrimFAT32RecordFile(u8Handle);
        BKFS_FAT_CloseFiles(u8Handle);

         //Set lenght fo file entry to "0" to prevent from clearing FAT table.
        entry.FileLength.Lo = 0;
        entry.FileLength.Hi = 0;
       if (!msAPI_FCtrl_FileDelete(&entry))
       {
             msAPI_FSEnv_UnRegister(u8EnvironmentID);
             __ASSERT(0);
             return FALSE;
        }

    }

    //Update file size of all used bulks to be 'BULK_SIZE' KB
    while(u16StartBulkID!=LAST_BULK_ID&& u16StartBulkID<=BKFS_TotalBulkNumber)
    {
        if (!BKFS_RenewBulk(u8EnvironmentID, u16StartBulkID, bFillFatTbl))
        {
            msAPI_FSEnv_UnRegister(u8EnvironmentID);
            __ASSERT(0);
            return FALSE;
        }
        u16StartBulkID = BKFS_GetBulkValue(u16StartBulkID);
    }
    msAPI_FSEnv_UnRegister(u8EnvironmentID);
    return TRUE;
}

U16 BKFS_FileGenerateFATSegmentFileName(U16* pu16FileName, U8 u8Index,
    U16 *pDstNameBuf, U16 dstNameBufLength)
{
    U16 filenameLength = 0;
    U16 lastPotIndex = 0xFFFF;
    U16 rmCharCnt = 0;

     while(pu16FileName[filenameLength])
     {
        if(pu16FileName[filenameLength] == '.')
            lastPotIndex = filenameLength;
        filenameLength++;
     }

     if(filenameLength == 0)
        return 0;

     if(lastPotIndex == 0xFFFF)
        lastPotIndex = filenameLength;


     if(filenameLength > dstNameBufLength-1-3)
     {
          if(lastPotIndex < 4)
             lastPotIndex = filenameLength;
          rmCharCnt = filenameLength-dstNameBufLength+1+3;
          memcpy(pDstNameBuf, pu16FileName, sizeof(U16)*(lastPotIndex-rmCharCnt));
          memcpy(pDstNameBuf+lastPotIndex+3-rmCharCnt, pu16FileName+lastPotIndex,
                                                                                  sizeof(U16)*(filenameLength-lastPotIndex+1));
          lastPotIndex -= rmCharCnt;
          //dstNameBufLength = dstNameBufLength;/*including the tail zero*/
     }
     else
     {
          memcpy(pDstNameBuf, pu16FileName, sizeof(U16)*lastPotIndex);
          memcpy(pDstNameBuf+lastPotIndex+3, pu16FileName+lastPotIndex,
                                                                              sizeof(U16)*(filenameLength-lastPotIndex+1));
          dstNameBufLength = filenameLength+3+1;/*including the tail zero*/
     }

     pDstNameBuf[lastPotIndex] = '~';
     pDstNameBuf[lastPotIndex+1] = '0'+u8Index/10;
     pDstNameBuf[lastPotIndex+2] = '0'+u8Index%10;

     return dstNameBufLength;/*including the tail zero*/
}

///////////////////////////////////////////////////////////////////////
//1.Create or find the record file
//2.Switch start cluster between recorded file and bulk file
//3.Switch file total size in file entry between recorded file and bulk file
//4.Close record file and bulk file
///////////////////////////////////////////////////////////////////////
BOOLEAN BKFS_CreateRecordPathFiles(U16 *u16RecordPathFileName)
{
    U8 u8DiskDriveIndex = msAPI_BKFS_GetDriveIndex();
    //U8 u8DeviceIndex = msAPI_BKFS_GetDeviceIndex();
    U8 u8EnvironmentID = INVALID_FS_ENVIRONMENT_INDEX;
    U8 u8Handle, u8BulkHandle;
    //U8 handle=INVALID_FILE_HANDLE;
    U8  uFATSegIndex;
    U8  uFatSegTsFileCnt;
    BOOLEAN bNeedSplit;
    BulkFileEntry* pBulkFile;
    U16 BulkFileID;
    U16 u16StartBulkID = 0, u16NextBulkID;
    U16 uCurPaddingBufOffset;
    U16 uLen;
    U32 tmpSize;
    //U16 u16TotalBulkNumInUsed;
   // U16 u16MaxRecordBulkCnt;
    //U32 BulkFileLengthKB = 0;
    LongLong llBulkFileLength;

    if (u16RecordPathFileName == NULL)
        return FALSE;

    u8EnvironmentID = msAPI_FSEnv_Register(u8DiskDriveIndex);
    if (u8EnvironmentID >= FS_ENVIRONMENT_NUM)
    {
        __ASSERT(0);
        return FALSE;
    }

    //find the bulk file by filename
    BulkFileID = BKFS_SearchBulkFile(u16RecordPathFileName);
    if(BulkFileID == INVALID_BULK_FILE_ID)
    {
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        __ASSERT(0);
        return FALSE;
    }
    //Create record path file: get bulk file entry
    pBulkFile = BKFS_GetBulkFileEntryXDATA(BulkFileID);
    if(pBulkFile == NULL)
    {
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        msAPI_FS_ReturnXData();
        __ASSERT(0);
        return FALSE;
    }
    u16StartBulkID = pBulkFile->StartBulkID;
    llBulkFileLength = pBulkFile->FileLength;
    uFatSegTsFileCnt = pBulkFile->uFatSegTsFileCnt;
    msAPI_FS_ReturnXData();

    __ASSERT(uFatSegTsFileCnt == 0);

    //Create record path file: check if the size of file is '0' byte
    if (LL_iszero(&llBulkFileLength))
    {
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        return FALSE;
    }
    //Create record path file: check if the size of file is over '4G'
    /*if (llBulkFileLength.Hi > 0)
    {
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        __ASSERT(0);
        return FALSE;
    }*/ //enable it when need to check if TS file is over 4G
    //u16MaxRecordBulkCnt = BKFS_GetMaxRecordBulkCnt();
   // u16TotalBulkNumInUsed = LL_LongDivU32(&llBulkFileLength, BULK_SIZE).Lo+1; //+1:at least uses one bulk
  //  u16TotalBulkNumInUsed = u16TotalBulkNumInUsed>u16MaxRecordBulkCnt?u16MaxRecordBulkCnt:u16TotalBulkNumInUsed;

    bNeedSplit = (llBulkFileLength.Hi!=0 || llBulkFileLength.Lo>FAT_SEGMENT_FILE_SIZE);
    uFATSegIndex = 0;
    uCurPaddingBufOffset = 0;

    uLen = FS_strlen_U(u16RecordPathFileName);
    uLen++;

    SPLIT_DBG(printf("Create record file for %s,NameSpace%d, need split=%bd\n",
                         Unicode2ASCII(u16RecordPathFileName), (U16)MAX_FAT_SEG_FILENAME_BUF_SIZE, (U8)bNeedSplit));
    while(!LL_iszero(&llBulkFileLength))
    {
         tmpSize = 0;
         //Create record path file: create recorded file in root directory
        if(!msAPI_FCtrl_DirectoryChangeToRoot(u8EnvironmentID))
        {
               msAPI_FSEnv_UnRegister(u8EnvironmentID);
                __ASSERT(0);
               return FALSE;
         }
         if(uFatSegTsFileCnt>=MAX_LN_FAT_FILE_CNT
            ||(MAX_FAT_SEG_FILENAME_BUF_SIZE-uCurPaddingBufOffset*sizeof(U16))<MAX_FAT_SEG_FILENAME_LEN*sizeof(U16))
         {
                SPLIT_DBG(printf("Not enough name space in BulkFileEntry, TS fileCnt = %d\n",
                    (U16)uFatSegTsFileCnt));
                msAPI_FSEnv_UnRegister(u8EnvironmentID);
                 __ASSERT(0);
                 return FALSE;
         }

        if((bNeedSplit&&uFATSegIndex>0) || (uLen>MAX_FAT_SEG_FILENAME_LEN))
        {
            //We will not change first name of the first split
            uLen = BKFS_FileGenerateFATSegmentFileName(u16RecordPathFileName, uFATSegIndex,
                                                                                   g_segFilename, MAX_FAT_SEG_FILENAME_LEN);
            SPLIT_DBG(printf("Create Split TS record file %s, beg at bulk%d\n",
                                Unicode2ASCII(g_segFilename), u16StartBulkID));
        }
        else
        {
             memcpy(g_segFilename, u16RecordPathFileName, sizeof(U16)*uLen);
             SPLIT_DBG(printf("Use original name %s as split filename\n", Unicode2ASCII(g_segFilename)));
        }

        if(bNeedSplit)
            uFATSegIndex++;

        u8Handle = FAT_FileCreate(u8EnvironmentID, g_segFilename, FS_strlen_U(g_segFilename), CREATE_MODE_NEW);
        if(INVALID_FILE_HANDLE == u8Handle)
        {
            msAPI_FSEnv_UnRegister(u8EnvironmentID);
           __ASSERT(0);
         return FALSE;
        }
        u8BulkHandle = BKFS_SearchBulkByIndex(u8EnvironmentID, u16StartBulkID);
        if(u8BulkHandle == INVALID_FILE_HANDLE)
        {
             BKFS_FAT_CloseFiles(u8Handle); //close record path file to update directory entry data
             msAPI_FSEnv_UnRegister(u8EnvironmentID);
             __ASSERT(0);
             return FALSE;
        }
        //Switch start cluster and file size of two files
        if (!BKFS_AssociateToBulk(u8Handle, u8BulkHandle))
        {
             BKFS_FAT_CloseFiles(u8BulkHandle); //close bulk file to update directory entry data
             BKFS_FAT_CloseFiles(u8Handle); //close record path file to update directory entry data
             msAPI_FSEnv_UnRegister(u8EnvironmentID);
             __ASSERT(0);
             return FALSE;
         }
         BKFS_FAT_CloseFiles(u8BulkHandle); //close bulk file to update directory entry data

         tmpSize += (llBulkFileLength.Hi || llBulkFileLength.Lo>=BULK_SIZE)?BULK_SIZE:llBulkFileLength.Lo;
         llBulkFileLength = LL_subtract(&llBulkFileLength,
                                 (llBulkFileLength.Hi || llBulkFileLength.Lo>=BULK_SIZE)?BULK_SIZE:llBulkFileLength.Lo);
         while(1)
         {
               u16NextBulkID = BKFS_GetBulkValue(u16StartBulkID);
               if(u16NextBulkID==LAST_BULK_ID || u16NextBulkID>BKFS_TotalBulkNumber)
               {
                    if(!LL_iszero(&llBulkFileLength))
                    {
                         msAPI_FSEnv_UnRegister(u8EnvironmentID);//bug found-->filelength is not inaccordance with BULK list
                         __ASSERT(0);
                         return FALSE;

                     }
                    break;
               }
               if (!BKFS_ConnectBulks(u8EnvironmentID, u16StartBulkID, u16NextBulkID))
               {
                     msAPI_FSEnv_UnRegister(u8EnvironmentID);
                     __ASSERT(0);
                    return FALSE;
               }
               tmpSize += (llBulkFileLength.Hi || llBulkFileLength.Lo>=BULK_SIZE)?BULK_SIZE:llBulkFileLength.Lo;
               llBulkFileLength = LL_subtract(&llBulkFileLength,
                                 (llBulkFileLength.Hi || llBulkFileLength.Lo>=BULK_SIZE)?BULK_SIZE:llBulkFileLength.Lo);

               u16StartBulkID = u16NextBulkID;
               if(tmpSize >= FAT_SEGMENT_FILE_SIZE)
               {
                  SPLIT_DBG(printf("      Terminate Split TS record file %s at bulk%d\n",
                                Unicode2ASCII(g_segFilename), u16StartBulkID));
                   //skip to next un-connected bulk.
                   u16StartBulkID = BKFS_GetBulkValue(u16StartBulkID);

                   break;
               }
         }
                   //Update record path file size
         if (!BKFS_UpdateFileSize(u8Handle, tmpSize)) //only 4G file can be created, it's FAT32's limitation
         {
             BKFS_FAT_CloseFiles(u8Handle); //close record path file to update directory entry data
             msAPI_FSEnv_UnRegister(u8EnvironmentID);
             __ASSERT(0);
             return FALSE;
         }
         BKFS_FAT_CloseFiles(u8Handle);

         pBulkFile = BKFS_GetBulkFileEntryXDATA(BulkFileID);
         if(pBulkFile == NULL)
         {
             msAPI_FSEnv_UnRegister(u8EnvironmentID);
             msAPI_FS_ReturnXData();
             __ASSERT(0);
             return FALSE;
          }
          pBulkFile->fatSegTSFileNameOffset[ pBulkFile->uFatSegTsFileCnt++] = uCurPaddingBufOffset;
          memcpy(pBulkFile->fatSegNameTBL+uCurPaddingBufOffset, g_segFilename, uLen*sizeof(U16));
          uCurPaddingBufOffset += uLen;
          uFatSegTsFileCnt = pBulkFile->uFatSegTsFileCnt;
          msAPI_FS_ReturnXData();
          if( !bNeedSplit && !LL_iszero(&llBulkFileLength))
          {
              //bug
              __ASSERT(0);
              return FALSE;
          }
    }

    msAPI_FSEnv_UnRegister(u8EnvironmentID);
    BKFS_WriteCurrentCachedBulkFileEntry();
    return TRUE;
}

U16 msAPI_BKFS_GetFreeBulkCnt(void)
{
    return g_u16FreeBulkCnt;
}
//]add for new FAT solution

BOOLEAN msAPI_BKFS_FileExist(U16* pu16FileName)
{
    if(msAPI_BKFS_IsInitialized() == FALSE)
    {
        __ASSERT(0);
        return FALSE;
    }

    if(BKFS_SearchBulkFile(pu16FileName)==INVALID_BULK_FILE_ID)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

BOOLEAN msAPI_BKFS_FileDelete(U16* pu16FileName)
{
    BulkFileEntry* pBulkFile=NULL;
    BulkFileHandle* pHandle;
    U16 bulkFileID=INVALID_BULK_FILE_ID;
    U16 BulkID=0x0;
    U8 i=0;

    BKFSDBG(printf("[BKFS] msAPI_BKFS_FileDelete:\n"));// BKFSDBG(BKFS_PrintAllHandles());

    if(msAPI_BKFS_IsInitialized() == FALSE)
    {
        __ASSERT(0);
        return FALSE;
    }

    bulkFileID=BKFS_SearchBulkFile(pu16FileName);
    if(bulkFileID==INVALID_BULK_FILE_ID)
    {
        return FALSE;
    }

    pHandle=BKFS_GetBulkFileHandleXDATA();
    for(i=0;i<MAX_BULK_FILE_HANDLE_NUM;i++)
    {
        if( pHandle[i].HandleID!=INVALID_FILE_HANDLE //opened
            &&pHandle[i].BulkFileID==bulkFileID //same Bulk File
            )
        {

             msAPI_FS_ReturnXData();
             __ASSERT(0);// opened file can not be deleted
             return FALSE;
        }
    }
    msAPI_FS_ReturnXData();

    pBulkFile=BKFS_GetBulkFileEntryXDATA(bulkFileID);
    if(pBulkFile==NULL)
    {
        __ASSERT(0);
        msAPI_FS_ReturnXData();
        return FALSE;
    }

    //[Delete record path file: check if file is existed
#if (ENABLE_TO_RECORD_AS_TS_FILE)
    if (pBulkFile->OpenMode == BKF_OPEN_FOR_WRITE)
    {
        msAPI_FCtrl_ResetCurrentDirEntryIndex(); //must reset DirEntryIndex before using this quick search.
        if(!BKFS_DeleteRecordPathFiles(pBulkFile))
        {
                msAPI_FS_ReturnXData();
                msAPI_FCtrl_ResetCurrentDirEntryIndex(); //must reset DirEntryIndex before using this quick search.
                __ASSERT(0);
                return FALSE;
        }
        msAPI_FCtrl_ResetCurrentDirEntryIndex(); //must reset DirEntryIndex before using this quick search.
    }
#endif //#if (ENABLE_TO_RECORD_AS_TS_FILE)
    //]

    BulkID=pBulkFile->StartBulkID;
    memset(pBulkFile,0,BULK_FILE_ENTRY_SIZE);
    msAPI_FS_ReturnXData();

    //write the BulkFileEntry cached in BULK_FILE_ENTRY_ADDR back
    ioassert(BKFS_WriteBulkFileEntry(bulkFileID, _PA2VA(BULK_FILE_ENTRY_ADDR)));

    ioassert(BKFS_FreeBulks(BulkID,FALSE));

    return TRUE;
}

extern U8 FAT_FileCreateDirEntry(U8 u8EnvironmentID, U16 *pu16LongName, U8 charLen, FileEntry *pEntryToSet, BOOLEAN bIsFile, EN_CREATE_MODE createMode);

BOOLEAN msAPI_BKFS_CreateBulks(EN_CREATE_BULKS_STATE enCreateBulksState, U8 u8EnvironmentID, U16* u16BulkNum)
{
    static U16 name[12]={'M','S','T','0','0','0','0','1','.','B','U','K'};
    static U16 name8_3[12];
    U16 name8_3_idx[]={'M','S','T','_','B','K','F','S','.','I','D','X'};

    U32 ts;
    U8 u8Handle;
    FAT_FileInode *pFileInode;
    static U32 u32TotalSectors = 0;
    static U32 u32TmpSectors = 0;
    static U8 sectorPerCluster = 0;
    static U16 _bytesPerSector = 0;
    static U8 u8DeviceIndex = 0xFF;
    static U8 fsid = 0xFF;
    static U32 u32BukCount = 0;
    static U32 u32FileTotalSize = BULK_SIZE;
    static FileEntry stIndexFileEntry;
    //U32 addr = (IO_TEMP_ADDR>>12);

    switch(enCreateBulksState)
    {
        case EN_CREATE_BULKS_INIT:
        {
            u8DeviceIndex = msAPI_FSEnv_GetEnvironment( u8EnvironmentID )->u8DeviceIndex;
            fsid = msAPI_FSEnv_GetEnvironment( u8EnvironmentID )->u8FileSystemID;
            memcpy(name8_3,name,sizeof(name));
            u32BukCount = 0;
            g_u16BulksToCreate = 0;
            g_u16CurrentCreateBulkNum = 0;
            _enCreateBulksState = EN_CREATE_BULKS_CREATEFOLDER;
            break;
        }
        case EN_CREATE_BULKS_CREATEFOLDER:
        {
            U16 name8[]={'_','M','S','T','B','K','F','S'};
            U32 u32DirStartClusterNo;
            //U32 u32FAT32Size;
            //U8 u8NumFATs;
            U32 *pBuk;
            U8 bResult;

            FS_EnvironmentStruct* pFS_Env;
            FAT_FileSysStruct * pFAT_FileSys;

            ts = msAPI_Timer_GetTime0();
            /*  create folder _MSTBKFS   */
            BKFSDBG(printf("\ncreate folder _MSTBKFS\n"));
            u8Handle = FAT_FolderCreate(u8EnvironmentID, name8, 8);
            if(INVALID_FILE_HANDLE == u8Handle)
            {
                __ASSERT(0);
                _enCreateBulksState = EN_CREATE_BULKS_INIT;
                return FALSE;
            }
            BKFSDBG(printf("create folder _MSTBKFS DONE !\n"));
            pFileInode= FAT_File_GetInodeFromHandle(u8Handle);
            u32DirStartClusterNo = pFileInode->u32FileStartClusterNo;
            FCtrl_ReturnFileInodeXdata();
            BKFS_FAT_CloseFiles(u8Handle);
            BKFSDBG(printf("time=%lu\n",msAPI_Timer_DiffTimeFromNow(ts))); //print the time message

            /* change  folder to _MSTBKFS   */
            ts = msAPI_Timer_GetTime0();
            BKFSDBG(printf("\nchange  folder to _MSTBKFS\n"));
            if(!FAT_DirectoryChange(u8EnvironmentID, u32DirStartClusterNo))
            {
                _enCreateBulksState = EN_CREATE_BULKS_INIT;
                __ASSERT(0);
                return FALSE;
            }

            BKFSDBG(printf("change  folder to _MSTBKFS DONE !\n"));
            BKFSDBG(printf("time=%lu\n",msAPI_Timer_DiffTimeFromNow(ts))); //print the time message

            pFS_Env = msAPI_FSEnv_GetEnvironment( u8EnvironmentID );
            pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemXData(pFS_Env->u8FileSystemID);
            u32TotalSectors = pFAT_FileSys->stBootSector.BPB_TotSec32;
            sectorPerCluster=pFAT_FileSys->stBootSector.BPB_SecPerClus;
            _bytesPerSector=pFAT_FileSys->stBootSector.BPB_BytsPerSec;
            //u8NumFATs = pFAT_FileSys->stBootSector.BPB_NumFATs;
            //u32FAT32Size = pFAT_FileSys->stBootSector.BPB_FATSz32;
            FAT_ReturnXData();

            /*// u32TotalSectors - (u32FAT32Size*u8NumFATs) - rootDiretory sector - BKFS folder directory sector )
            u32TotalSectors = u32TotalSectors-((u32FAT32Size*u8NumFATs)+sectorPerCluster*2);
            printf("u32TotalSectors = %lu\n",u32TotalSectors);

            u32TmpSectors = (u32FileTotalSize/_bytesPerSector);
            g_u16BulksToCreate = (U16)(u32TotalSectors/u32TmpSectors);*/
            u32TmpSectors = (u32FileTotalSize/_bytesPerSector);
            BKFSDBG(printf("total sectors = %lx\n", u32TotalSectors)); //print the time message
            g_u16BulksToCreate = BKFS_CalculateBulksNum(u8EnvironmentID);
            if (g_u16BulksToCreate >= MAX_PERMITTED_BULK_CNT) //Max. bulk count is 65535.
                g_u16BulksToCreate = MAX_PERMITTED_BULK_CNT;

            //clean once
            pBuk = (U32 xdata *)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);
            memset(pBuk, 0, 0x1000);
            msAPI_FS_ReturnXData();

            /*********************************************
            For performance isssue, reserve a directory slot in the header of directory clusters
            for index file.
            **********************************************/
            bResult = FAT_FileCreateDirEntry(u8EnvironmentID, name8_3_idx, 12, &stIndexFileEntry, TRUE, CREATE_MODE_NEW);

            if(bResult != ENTRY_CREATE_RESULT_SUCCESS)
            {
                  _enCreateBulksState = EN_CREATE_BULKS_INIT;
                  __ASSERT(0);
                  return FALSE;
            }
            _enCreateBulksState = EN_CREATE_BULKS_CREATEBULKS;

            break;
        }
        case EN_CREATE_BULKS_CREATEBULKS:
        {
           // U32 *pBuk;
            U32 u32StartCluster;
            ts = msAPI_Timer_GetTime0();
            BKFSDBG(printf("\ncreate file MST_000X.BUK\n"));
            //pBuk = (U32 xdata *)msAPI_FS_GetXData(addr);

            u8Handle = BKFS_FAT_CreateFiles(u8EnvironmentID, name8_3, 12, u32FileTotalSize, NULL);
            if(INVALID_FILE_HANDLE == u8Handle)
            {
                _enCreateBulksState = EN_CREATE_BULKS_INIT;
                __ASSERT(printf("CREATEBULKS: Create Bulk Fail\n"));
                return FALSE;
                /*if (u32BukCount < (MEGA_PER_GIGA/BULK_SIZE))
                {
                    _enCreateBulksState = EN_CREATE_BULKS_INIT;
                    __ASSERT(printf("CREATEBULKS: Available Disk size is smaller than 1G\n"));
                    return FALSE;
                }
                else {
                    *u16BulkNum = (U16)u32BukCount;
                    g_u16FreeBulkCnt = g_u16BulksToCreate;
                    _enCreateBulksState = EN_CREATE_BULKS_CREATEINDEX;
                    break;
                }*/
            }
            pFileInode = FAT_File_GetInodeFromHandle(u8Handle);
            u32StartCluster = pFileInode->u32FileStartClusterNo;
            FCtrl_ReturnFileInodeXdata();

            //*(pBuk + u32BukCount+1) = FAT_FATGetSectorNo(fsid, u32StartCluster);

            u32BukCount ++;
            g_u16CurrentCreateBulkNum++;

            *(name8_3 + 7) = *(name8_3 + 7) + 1;
            if(*(name8_3 + 7) == 0x3A)
            {
                *(name8_3 + 7) = *(name8_3 + 7) - 0xA;
                *(name8_3 + 6) = *(name8_3 + 6) + 1;
                if(*(name8_3 + 6) == 0x3A )
                {
                    *(name8_3 + 6) = *(name8_3 + 6) - 0xA;
                    *(name8_3 + 5) = *(name8_3 + 5) + 1;
                    if(*(name8_3 + 5) == 0x3A )
                    {
                        *(name8_3 + 5) = *(name8_3 + 5) - 0xA;
                        *(name8_3 + 4) = *(name8_3 + 4) + 1;
                        if(*(name8_3 + 4) == 0x3A )
                        {
                            *(name8_3 + 4) = *(name8_3 + 4) - 0xA;
                            *(name8_3 + 3) = *(name8_3 + 3) + 1;
                        }
                    }
                }
            }
            BKFSDBG(printf("    Bulk File count: u32StartCluster: 0x%08LX  [%lu][%lu]\n", u32StartCluster, u32TmpSectors, u32TotalSectors));

            u32TotalSectors -= u32TmpSectors;
            if((u32TmpSectors > u32TotalSectors) || g_u16CurrentCreateBulkNum>=g_u16BulksToCreate || ((*u16BulkNum!=0)&&(u32BukCount>= (U32)*u16BulkNum)))
            {
                //BKFSDBG(printf("\nu32TmpSectors:%LX,  u32TotalSectors: %LX", u32TmpSectors,  u32TotalSectors));
                BKFSDBG(printf("Create Over ~~ u32TotalSectors[%lu],u32TmpSectors[%lu]\n",u32TotalSectors,u32TmpSectors)); //print the time message
                *u16BulkNum = (U16)u32BukCount;
                g_u16FreeBulkCnt = g_u16BulksToCreate;
                _enCreateBulksState = EN_CREATE_BULKS_CREATEINDEX;
            }

            BKFS_FAT_CloseFiles(u8Handle);
            //msAPI_FS_ReturnXData();
            BKFSDBG(printf("create file MST_000X.BUK DONE !\n"));
            BKFSDBG(printf("file%lu, time=%lu\n",u32BukCount, msAPI_Timer_DiffTimeFromNow(ts))); //print the time message
            break;
        }
        case EN_CREATE_BULKS_CREATEINDEX:
        {
            /*  create file MST_BKFX.IDX    */
            U32 u32IndexFileTotalSize;
            U32 u32StartCluster;
            U32 u32SectorNo;
            U32 u32Tmp;
            U32 *pBuk;
            U32 u32BulkFolderCreatedDT;
            U16* pu16;
            U16* pu16FileName;
            U32 i=0;
            U32 u32ClusterID;
            U32 u32STTBLNodeCnt = (u32BukCount+IDX_BULK_START_SECTOR_TABLE_NODE_SIZE/4-1)/(IDX_BULK_START_SECTOR_TABLE_NODE_SIZE/4);
            U32 u32AllocTBLNodeCnt = (u32BukCount+IDX_ALLOCATION_TABLE_NODE_SIZE/2-1)/(IDX_ALLOCATION_TABLE_NODE_SIZE/2);
            FileEntry bulkEntry;

            fsid = msAPI_FSEnv_GetEnvironment( u8EnvironmentID )->u8FileSystemID;

            ts = msAPI_Timer_GetTime0();
            ///get bulk folder's created date time
            if (!BKFS_GetBKFSFolderCreatedDT(&u32BulkFolderCreatedDT))
            {
                _enCreateBulksState = EN_CREATE_BULKS_INIT;
                __ASSERT(0);
                return FALSE;
            }
            //]
            BKFSDBG(printf("\ncreate file MST_BKFX.IDX\n"));
            u32IndexFileTotalSize = (0x1000UL+u32STTBLNodeCnt*IDX_BULK_START_SECTOR_TABLE_NODE_SIZE+
                u32AllocTBLNodeCnt*IDX_ALLOCATION_TABLE_NODE_SIZE+ ((u32BukCount+1) * 0x1000));  //
            debugFlag = 0;
            u8Handle = BKFS_FAT_CreateFiles(u8EnvironmentID, name8_3_idx, 12, u32IndexFileTotalSize, &stIndexFileEntry);
            if(INVALID_FILE_HANDLE == u8Handle)
            {
                _enCreateBulksState = EN_CREATE_BULKS_INIT;
                __ASSERT(0);
                return FALSE;
            }
            pFileInode = FAT_File_GetInodeFromHandle(u8Handle);
            u32StartCluster = pFileInode->u32FileStartClusterNo;
            FCtrl_ReturnFileInodeXdata();;
            BKFSDBG(printf("create file MST_BKFX.IDX DONE !\n"));
            BKFSDBG(printf("time=%lu\n",msAPI_Timer_DiffTimeFromNow(ts))); //print the time message

            /* record first Buk Index */
            ts = msAPI_Timer_GetTime0();
            BKFSDBG(printf("\nrecord first Buk Index\n"));
            pBuk = (U32 xdata *)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);
            memset(pBuk, 0, 0x1000);

            __ASSERT(((u32STTBLNodeCnt|u32AllocTBLNodeCnt|u32BukCount)&0xFFFF0000)==0);
            u32BukCount ^=BULK_FS_MAGIC_HEADER;
            u32STTBLNodeCnt ^= BULK_FS_MAGIC_HEADER;
            u32AllocTBLNodeCnt ^= BULK_FS_MAGIC_HEADER;

            SET_MISCINFO(pBuk, STARTSECTBL_NODECNT, u32STTBLNodeCnt);
            SET_MISCINFO(pBuk, ALLOCTBL_NODECNT, u32AllocTBLNodeCnt);
            u32Tmp = BKFS_VERSION;
            SET_MISCINFO(pBuk, BULK_VERSION, u32Tmp);
            SET_MISCINFO(pBuk, TOTAL_SIZE_USED, g_u32TotalDiskSizeMBSetToUsed);
            SET_MISCINFO(pBuk, TOTAL_BULK, u32BukCount);
            SET_MISCINFO(pBuk, BULK_FOLDER_CREATED_DT, u32BulkFolderCreatedDT);

            msAPI_FS_ReturnXData();
            g_u32TotalDiskSizeMBSetToUsed = 0; //just to reset to initial value;

            u32STTBLNodeCnt ^= BKFSSwap32(BULK_FS_MAGIC_HEADER);
            u32STTBLNodeCnt = BKFSSwap32(u32STTBLNodeCnt);
            u32AllocTBLNodeCnt ^= BKFSSwap32(BULK_FS_MAGIC_HEADER);
            u32AllocTBLNodeCnt = BKFSSwap32(u32AllocTBLNodeCnt);
            u32BukCount ^= BKFSSwap32(BULK_FS_MAGIC_HEADER);
            u32BukCount = BKFSSwap32(u32BukCount);

            u32SectorNo =  FAT_FATGetSectorNo(fsid, u32StartCluster);
            BKFSDBG(printf("record first Buk Index : @sector[%lu]\n",u32SectorNo));

            if(!msAPI_MSDCtrl_SectorWrite(u8DeviceIndex, u32SectorNo, 8, _PA2VA(IO_TEMP_ADDR)))
            {
                _enCreateBulksState = EN_CREATE_BULKS_INIT;
                BKFS_FAT_CloseFiles(u8Handle);
                __ASSERT(0);
                return FALSE;
            }
            BKFSDBG(printf("record first Buk Index DONE !\n"));
            BKFSDBG(printf("time=%lu\n",msAPI_Timer_DiffTimeFromNow(ts))); //print the time message

            /* write Bulk start sector in IDX */
            BKFSDBG(printf("\nstart build start sector table, bulkcnt%ld, start sector table node cnt %ld\n", u32BukCount, u32STTBLNodeCnt));
            ts = msAPI_Timer_GetTime0();
            pBuk = (U32 xdata *)msAPI_FS_GetXData(BULK_START_SECTOR_TABLE_ADDR>>12);
            memset(pBuk, 0, 0x1000);
            u32SectorNo = FAT_FATGetSectorNo(fsid, u32StartCluster)+IDX_HEAD_SIZE/_bytesPerSector;
            memcpy(name8_3,name,sizeof(name));
            pu16FileName= (U16*)msAPI_FS_Memory_Allocate(256*2);
            if(pu16FileName == NULL)
            {
                  _enCreateBulksState = EN_CREATE_BULKS_INIT;
                  msAPI_FS_ReturnXData();//pBulk
                  BKFS_FAT_CloseFiles(u8Handle);
                  __ASSERT(0);
                   return FALSE;
             }
            msAPI_FCtrl_EntryFirst(u8EnvironmentID);
            for( i=0; i<=u32BukCount; i++)
            {
                BOOLEAN bFindBULKFN = FALSE;
                U16 tmp = (U16)i;
                if( i==0)
                    continue;
                name8_3[3] = '0'+tmp/10000UL;
                tmp = tmp%10000UL;
                name8_3[4] = '0'+tmp/1000UL;
                tmp = tmp%1000UL;
                name8_3[5] = '0'+tmp/100UL;
                tmp = tmp%100UL;
                name8_3[6] = '0'+tmp/10UL;
                tmp = tmp%10UL;
                name8_3[7] = '0'+tmp;
                while(msAPI_FCtrl_EntryNext(u8EnvironmentID, &bulkEntry)==ENTRY_NEXT_RESULT_SUCCESS)
                {
                    U8 len=0;
                    len = msAPI_FCtrl_EntryGetCurrentName(u8EnvironmentID, GET_DRAM_ADDR(pu16FileName), 255);
                    if(len != LENGTH_OF_BKFS_FILE)
                        continue;
                   if(memcmp(name8_3, pu16FileName, sizeof(U16)*LENGTH_OF_BKFS_FILE))
                       continue;
                   bFindBULKFN = TRUE;
                   break;
                }
                if( bFindBULKFN == FALSE)
                {
                       _enCreateBulksState = EN_CREATE_BULKS_INIT;
                        msAPI_FS_Memory_Free(pu16FileName);
                        msAPI_FS_ReturnXData();//pBulk
                       BKFS_FAT_CloseFiles(u8Handle);
                      __ASSERT(0);
                       return FALSE;
                }
               memcpy(&u32ClusterID ,&bulkEntry.EntryID[0], FAT32ENTRYSIZE);
               pBuk[i&1023UL] = FAT_FATGetSectorNo(fsid, u32ClusterID);
               //printf("bulk %ld start sector is %lx\n", i, pBuk[i&1023UL]);

               if( (i&1023UL)==1023UL  || i==u32BukCount)
               {
                    if(!msAPI_MSDCtrl_SectorWrite(u8DeviceIndex, u32SectorNo, 8, _PA2VA(BULK_START_SECTOR_TABLE_ADDR)))
                   {
                       _enCreateBulksState = EN_CREATE_BULKS_INIT;
                       msAPI_FS_Memory_Free(pu16FileName);
                       msAPI_FS_ReturnXData();//pBulk
                       BKFS_FAT_CloseFiles(u8Handle);
                      __ASSERT(0);
                       return FALSE;
                    }
                    u32SectorNo += 8;
                    memset(pBuk, 0, 0x1000);
                }
               FS_RESET_WDT();
            }
            msAPI_FS_ReturnXData();
            msAPI_FS_Memory_Free(pu16FileName);
            BKFSDBG(printf("finish building start sector table!!\n"));
            BKFSDBG(printf("time=%lu\n",msAPI_Timer_DiffTimeFromNow(ts))); //print the time message
            //pBuk = (U32 xdata *)msAPI_FS_GetXData(addr);

            /* reset allocation table*/
            ts = msAPI_Timer_GetTime0();
            BKFSDBG(printf("\nreset allocation table\n"));
            pu16 = (U16 xdata *)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);
            memset(pu16, 0, 0x1000);
            *pu16 = INVALID_BK_ID;
            msAPI_FS_ReturnXData();

            u32SectorNo =  FAT_FATGetSectorNo(fsid, u32StartCluster)+IDX_HEAD_SIZE/_bytesPerSector
                                                                        +u32STTBLNodeCnt*IDX_BULK_START_SECTOR_TABLE_NODE_SIZE/_bytesPerSector;
            BKFSDBG(printf("reset allocation table : @sector[%lu]\n ",u32SectorNo));
            for( i=0; i<u32AllocTBLNodeCnt; i++)
            {
                if(!msAPI_MSDCtrl_SectorWrite(u8DeviceIndex, u32SectorNo+i*8, 8, _PA2VA(IO_TEMP_ADDR)))
                {
                     _enCreateBulksState = EN_CREATE_BULKS_INIT;
                     BKFS_FAT_CloseFiles(u8Handle);
                     __ASSERT(0);
                     return FALSE;
                }

                if( i==0)
                {
                      pu16 = (U16 xdata *)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);
                     *pu16 = 0;
                      msAPI_FS_ReturnXData();
                }
           }
            BKFSDBG(printf("reset allocation table DONE !\n"));
            BKFSDBG(printf("time=%lu\n",msAPI_Timer_DiffTimeFromNow(ts))); //print the time message

             /* reset all FileEntry */
            ts = msAPI_Timer_GetTime0();
            BKFSDBG(printf("\nStart to reset all FileEntry\n "));
            for(i=0;i<(u32BukCount+1);i++)
            {
                pu16 = (U16 xdata *)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);

                if(i==0)
                {
                    memset(pu16, 0xEE, 0x1000);
                    *pu16 = INVALID_BULK_FILE_ID;
                }
                else
                {
                    memset(pu16, 0x0, 0x1000);
                }
                msAPI_FS_ReturnXData();

                u32SectorNo =  FAT_FATGetSectorNo(fsid, u32StartCluster) +IDX_HEAD_SIZE/_bytesPerSector+u32STTBLNodeCnt*IDX_BULK_START_SECTOR_TABLE_NODE_SIZE/_bytesPerSector
                                                   +u32AllocTBLNodeCnt*IDX_ALLOCATION_TABLE_NODE_SIZE/_bytesPerSector;

                if(!msAPI_MSDCtrl_SectorWrite(u8DeviceIndex, u32SectorNo+(U32)i*(BULK_FILE_ENTRY_SIZE/_bytesPerSector), 8, _PA2VA(IO_TEMP_ADDR)))
                {
                    _enCreateBulksState = EN_CREATE_BULKS_INIT;
                    BKFS_FAT_CloseFiles(u8Handle);
                    __ASSERT(0);
                    return FALSE;
                }
            }
            _enCreateBulksState = EN_CREATE_BULKS_CREATEEPG;
            BKFS_FAT_CloseFiles(u8Handle);
            msAPI_BKFS_SetDefaultDiskDriveIndex(BKFS_DiskDriveIndex); //set current drive as default drive
            BKFSDBG(printf("Start to reset all FileEntry DONE !\n "));
            BKFSDBG(printf("time=%lu\n",msAPI_Timer_DiffTimeFromNow(ts))); //print the time message
            debugFlag = 0;

            break;
        }
        case EN_CREATE_BULKS_CREATEEPG:
        {
            /*  create file MST_BKFX.EPG    */
            U32 u32EPGFileTotalSize;
            U32 u32StartCluster;
            //U32 u32SectorNo;
            //U16* pu16;

            ts = msAPI_Timer_GetTime0();
            BKFSDBG(printf("\ncreate file MST_BKFS.EPG\n")); //print the time message
            u32EPGFileTotalSize = EGP_FN_SIZE;  //
            debugFlag = 0;
            //u8Handle = BKFS_FAT_CreateFiles(u8EnvironmentID, name8_3_epg, LENGTH_OF_BKFS_EPG_FILE, u32EPGFileTotalSize, NULL);
            u8Handle = FAT_FileCreate(u8EnvironmentID, name8_3_epg, LENGTH_OF_BKFS_EPG_FILE, CREATE_MODE_NEW);
            if(INVALID_FILE_HANDLE == u8Handle)
            {
                _enCreateBulksState = EN_CREATE_BULKS_INIT;
                __ASSERT(0);
                return FALSE;
            }
            pFileInode = FAT_File_GetInodeFromHandle(u8Handle);
            u32StartCluster = pFileInode->u32FileStartClusterNo;
            FCtrl_ReturnFileInodeXdata();
            BKFSDBG(printf("create file MST_BKFX.EPG DONE !\n"));
            BKFSDBG(printf("time=%lu\n",msAPI_Timer_DiffTimeFromNow(ts))); //print the time message

            /* write Bulk start sector in IDX */
            BKFSDBG(printf("  Clear  Bulk EPG File, u32StartCluster: 0x%08LX, u32EPGFileTotalSize: 0x%08LX\n", u32StartCluster, u32EPGFileTotalSize));
            /* record first Buk Index */
            /*ts = msAPI_Timer_GetTime0();
            u32SectorNo =  FAT_FATGetSectorNo(fsid, u32StartCluster);
            BKFSDBG(printf("EPG first secotr[%lu]\n",u32SectorNo));
            pu16 = (U16 xdata *)msAPI_FS_GetXData(addr);
            memset(pu16, 0, 0x1000);
            msAPI_FS_ReturnXData();
            while(u32EPGFileTotalSize>=0x1000)
            {
                 if(!msAPI_MSDCtrl_SectorWrite(u8DeviceIndex, u32SectorNo, 8, IO_TEMP_ADDR))
                 {
                       _enCreateBulksState = EN_CREATE_BULKS_INIT;
                       BKFS_FAT_CloseFiles(u8Handle);
                       __ASSERT(0);
                       return FALSE;
                 }
                 u32EPGFileTotalSize -= 0x1000;
                 u32SectorNo += 8;
            }*/

            _enCreateBulksState = EN_CREATE_BULKS_DONE;
            BKFS_FAT_CloseFiles(u8Handle);
            BKFS_Show_Hide_Bulk_Folder(FALSE);

            BKFSDBG(printf("Clear EPG file DONE !\n"));
            BKFSDBG(printf("time=%lu\n",msAPI_Timer_DiffTimeFromNow(ts))); //print the time message
            break;
        }
        case EN_CREATE_BULKS_DONE:
        {
            break;
        }

        //return TRUE;
    }

    return TRUE;
}

#if 0
BOOLEAN msAPI_BKFS_FileResetWriteHandle(U8 handleID)
{
    BulkFileEntry* pBulkFile;
    BulkFileHandle* pHandle;
    U16 bulkFileID;
    U16 startBulk;
    U8 i=0;
    BOOLEAN ringMode;

    if(handleID>=MAX_BULK_FILE_HANDLE_NUM)
    {
        __ASSERT(0);
        return FALSE;
    }

    pHandle=BKFS_GetBulkFileHandleXDATA();
    if(pHandle[handleID].HandleID==INVALID_FILE_HANDLE)
    {
        __ASSERT(0); //handle is closed
        msAPI_FS_ReturnXData();
        return FALSE;
    }

    if(pHandle[handleID].OpenMode!=BKF_OPEN_FOR_WRITE||pHandle[handleID].OpenMode!=BKF_OPEN_FOR_RING_WRITE)
    {
        __ASSERT(0);
        msAPI_FS_ReturnXData();
        return FALSE;
    }

    ringMode=pHandle[handleID].RingMode;

    for(i=0;i<MAX_BULK_FILE_HANDLE_NUM;i++)
    {
        if( pHandle[i].HandleID!=INVALID_FILE_HANDLE //opened
            &&pHandle[i].BulkFileID==bulkFileID //same Bulk File
            &&i!=handleID //not self
            )
        {
             __ASSERT(0);// can not reset a handle of a file with read handle opened
            msAPI_FS_ReturnXData();
            return FALSE;
        }
    }

    bulkFileID=pHandle[handleID].BulkFileID;
    msAPI_FS_ReturnXData();

    pBulkFile=BKFS_GetBulkFileEntryXDATA(bulkFileID);
    startBulk=pBulkFile->StartBulkID;
    LL_assign(&pBulkFile->FileLength,0);
    msAPI_FS_ReturnXData();

     //write the BulkFileEntry cached in BULK_FILE_ENTRY_ADDR back
    ioassert(BKFS_WriteBulkFileEntry(bulkFileID,BULK_FILE_ENTRY_ADDR));

    if(!ringMode)
    {
        BKFS_FreeBulks(startBulk,TRUE);
    }

    //****setup handle
    pHandle=BKFS_GetBulkFileHandleXDATA();
    pHandle[handleID].CurrentBulkSectorNO=BKFS_GetBulkStartSector(startBulk);
    pHandle[handleID].CurrentBulkID=startBulk;
    pHandle[handleID].CurrentSectorOffset=0;
    pHandle[handleID].RingStartPosition=0;
    LL_assign(&pHandle[handleID].FileLength,0);
    LL_assign(&pHandle[handleID].Position,0);

    msAPI_FS_ReturnXData();

    return TRUE;
}
#endif //#if 0

#if 0 // unused
U8 BKFS_ValidteRingBulkCount(U8 count)
{
    if(count>BKFS_TotalBulkNumber||(!FS_IsPowerOf2(count)))
    {
        U8 i=0;
        for(i=0;i<8;i++) //for(i=0;i<0xFF;i++) for fix warning: avoid overflowed or truncated value to "count"
        {
            if((1<<i)>count)
            {
                break;
            }
        }
        count=(1<<(i-1));
    }
    return count;
}
#endif

U8 BKFS_FileCreateForWrite(U16* pu16FileName,EN_BKF_OPEN_MODE mode,U8* pRingBulkCount)
{
    U8 handle=INVALID_FILE_HANDLE;
    BulkFileEntry* pBulkFile;
    BulkFileHandle* pHandle;
    U16 freeBulkID;
    U16 freeBulkFileID;
    U8 handleId;

    U16 startBulk;
    LongLong len;
//    LongLong ringSize;
//    U32 ringStartPosition;

    if(msAPI_BKFS_IsInitialized() == FALSE)
    {
         __ASSERT(0);
         goto CREATE_END;
    }

    BKFSDBG(printf("[BKFS] BKFS_FileCreateForWrite:\n"));// BKFSDBG(BKFS_PrintAllHandles());

    if(msAPI_BKFS_FileExist(pu16FileName))
    {
         msAPI_BKFS_FileDelete(pu16FileName);
        //__ASSERT(0);
        //goto CREATE_END;
    }
    /*else
    {
        if (mode == BKF_OPEN_FOR_WRITE)
        {
            if (!msAPI_BKFS_SetTotalRecordedFileCnt(msAPI_BKFS_GetTotalRecordedFileCnt()+1))
            {
                __ASSERT(0);
                goto CREATE_END;
            }
        }
    }*/

    handleId=BKFS_GetFreeHandleID();
    if(handleId==INVALID_FILE_HANDLE)
    {
            __ASSERT(0);
        goto CREATE_END;
    }

    if (mode == BKF_OPEN_FOR_WRITE)
        freeBulkID=BKFS_GetFreeBulkID(msAPI_BKFS_GetTimeShiftReservedBulkCnt()+1);
    else
       freeBulkID=BKFS_GetFreeBulkID(BKFS_MIN_BULKID);
    freeBulkFileID=BKFS_GetFreeBulkFileEntryID();

    if(freeBulkFileID==INVALID_BULK_FILE_ID||freeBulkID==INVALID_BK_ID)
    {
        __ASSERT(0);
        goto CREATE_END;
    }
/*
    if(ringMode) //2008_0731_2140
    {
       *pRingBulkCount=BKFS_ValidteRingBulkCount(*pRingBulkCount);
       BKFSDBG(printf("  RingBulkCount=0x%bx\n",*pRingBulkCount));
    }
*/
    BKFSDBG(printf("New BulkFile Entry!! BulkFileID=%u,BulkID=%u\n",freeBulkFileID,freeBulkID));
/*
    printf("[BKFS] BKFS_FileCreateForWrite:\n");
    printf("       New BulkFile Entry!! BulkFileID=%u,BulkID=%u\n",freeBulkFileID,freeBulkID);
    printf("       createMode = 0x%bx\n",mode);
    printf("       BKFS_TotalBulkNumber=%lu  RingBulkCount=%bu\n", BKFS_TotalBulkNumber,*pRingBulkCount);
    printf("[BKFS] BKFS_FileCreateForWrite:\n");
*/
    if(!BKFS_CreateBulkFileEntry(pu16FileName,freeBulkFileID,freeBulkID,mode,pRingBulkCount))
    {
        __ASSERT(0);
        goto CREATE_END;
    }

    //****get bulk
    pBulkFile=BKFS_GetBulkFileEntryXDATA(freeBulkFileID);
    startBulk=pBulkFile->StartBulkID;
    len=pBulkFile->FileLength;
//    ringMode=pBulkFile->RingMode;
//    ringSize=pBulkFile->RingSize;
//    ringStartPosition=pBulkFile->RingStartPosition;
    msAPI_FS_ReturnXData();

    //****setup handle
    pHandle=BKFS_GetBulkFileHandleXDATA();
    pHandle[handleId].BulkFileID=freeBulkFileID;
    pHandle[handleId].OpenMode=mode;
    pHandle[handleId].CurrentBulkSectorNO=BKFS_GetBulkStartSector(startBulk);
    pHandle[handleId].CurrentBulkID=startBulk;
    pHandle[handleId].CurrentSectorOffset=0;
    pHandle[handleId].HandleID=handleId;
    LL_assign(&pHandle[handleId].FileLength,0);
    LL_assign(&pHandle[handleId].Position,0);

//    pHandle[handleId].RingMode=ringMode;
//    pHandle[handleId].RingSize=ringSize;
//    pHandle[handleId].RingStartPosition=ringStartPosition;
    msAPI_FS_ReturnXData();

    handle=handleId;

CREATE_END:

    BKFSDBG(printf("[BKFS] write handle %bu created for BulkFileID=%u\n",handle,freeBulkFileID));
    return handle;
}

U8 BKFS_FileOpenForRead(U16* pu16FileName,EN_BKF_OPEN_MODE mode)
{
    U8 handle=INVALID_FILE_HANDLE;
    BulkFileEntry* pBulkFile;
    BulkFileHandle* pHandle;

    U16 BulkFileID;
    U8 handleId;
    U16 startBulk;
    LongLong len;
    BOOLEAN ringMode;
    LongLong ringSize;
    U32 ringStartPosition;
    U8 i=0;
    U8 writingHandle=INVALID_FILE_HANDLE;

    if(msAPI_BKFS_IsInitialized() == FALSE)
    {
        __ASSERT(0);
        goto OPEN_END;
    }

    BulkFileID=BKFS_SearchBulkFile(pu16FileName);
    if(BulkFileID==INVALID_BULK_FILE_ID)
    {
        __ASSERT(0);
        goto OPEN_END;
    }

    handleId=BKFS_GetFreeHandleID();
    if(handleId==INVALID_FILE_HANDLE)
    {
        __ASSERT(0);
        goto OPEN_END;
    }

    //****get bulk
    pBulkFile=BKFS_GetBulkFileEntryXDATA(BulkFileID);
    startBulk=pBulkFile->StartBulkID;
    len=pBulkFile->FileLength;
    ringMode=pBulkFile->RingMode;
    ringSize=pBulkFile->RingSize;
    ringStartPosition=pBulkFile->RingStartPosition;
    msAPI_FS_ReturnXData();

    //****setup handle
    pHandle=BKFS_GetBulkFileHandleXDATA();
    pHandle[handleId].BulkFileID=BulkFileID;
    pHandle[handleId].OpenMode=mode;
    pHandle[handleId].CurrentBulkSectorNO=BKFS_GetBulkStartSector(startBulk);
    pHandle[handleId].CurrentBulkID=startBulk;
    pHandle[handleId].CurrentSectorOffset=0;
    pHandle[handleId].HandleID=handleId;
    pHandle[handleId].FileLength=len;

    pHandle[handleId].RingMode=ringMode;
    pHandle[handleId].RingSize=ringSize;
    pHandle[handleId].RingStartPosition=ringStartPosition;

    BKFSDBG(printf("[BKFS] opening handle=%bu for read of BulkFileID=%u\n",handleId,BulkFileID));

    //search writing handle
    for(i=0;i<MAX_BULK_FILE_HANDLE_NUM;i++)
    {
        if( pHandle[i].HandleID!=INVALID_FILE_HANDLE //opened
                &&pHandle[i].BulkFileID==BulkFileID //same Bulk File
                &&i!=handleId //not self
                &&(pHandle[i].OpenMode==BKF_OPEN_FOR_RING_WRITE||pHandle[i].OpenMode==BKF_OPEN_FOR_WRITE)//write
            )
        {

            BKFSDBG(printf("[BKFS] found exsited writing handle %bu\n",i));
            writingHandle=i;
            break;
        }
    }

    //found writing handle!!
    if(writingHandle!=INVALID_FILE_HANDLE)
    {
        pHandle[handleId].RingStartPosition=pHandle[writingHandle].RingStartPosition;
        pHandle[handleId].FileLength=pHandle[writingHandle].FileLength;
    }
    msAPI_FS_ReturnXData();

    if(ringMode)
    {

        BKFS_FileResetReadHandleToBegin(handleId);

    }
    else
    {
        pHandle=BKFS_GetBulkFileHandleXDATA();
        LL_assign(&pHandle[handleId].Position,0);
        msAPI_FS_ReturnXData();
    }

    handle=handleId;

OPEN_END:
    BKFSDBG(printf("[BKFS] read handle %bu opened for BulkFileID=%u\n",handle,BulkFileID));
    return handle;
}

U8 msAPI_BKFS_FileOpen(U16* pu16FileName,EN_BKF_OPEN_MODE mode)
{
    if(mode==BKF_OPEN_FOR_WRITE)
    {
        U8 count=0;
//        return BKFS_FileCreateForWrite(pu16FileName,mode,FALSE,&count);
        return BKFS_FileCreateForWrite(pu16FileName,mode,&count);
    }
    else if(mode==BKF_OPEN_FOR_READ)
    {
        return BKFS_FileOpenForRead(pu16FileName,mode);
    }
    else
    {
        __ASSERT(0);
        return INVALID_FILE_HANDLE;
    }
}

U8 msAPI_BKFS_FileCreate(U16* pu16FileName)
{
    U8 u8BulkCnt = msAPI_BKFS_GetTimeShiftReservedBulkCnt();
    /*if (u8BulkCnt > BKFS_GetContinuousFreeBulkCnt())
        return INVALID_FILE_HANDLE;*/

    return BKFS_FileCreateForWrite(pu16FileName,BKF_OPEN_FOR_RING_WRITE, &u8BulkCnt);
}

#if 0
U8 msAPI_BKFS_RingFileCreate(U16* pu16FileName,EN_BKF_OPEN_MODE mode,U8* pu8BulkCount)
{
    if(!FS_IsPowerOf2(*pu8BulkCount))
    {
        __ASSERT(0);// ring bulk count must be power of 2 and
        return INVALID_FILE_HANDLE;
    }

    if((*pu8BulkCount)>MAX_RING_BULK_COUNT)
    {
        __ASSERT(0);
        return INVALID_FILE_HANDLE;
    }

    if(mode==BKF_OPEN_FOR_RING_WRITE)
    {
        //return BKFS_FileCreateForWrite(pu16FileName,mode,TRUE,pu8BulkCount);
        return BKFS_FileCreateForWrite(pu16FileName,mode,pu8BulkCount);
    }
    else
    {
        __ASSERT(0);
        return INVALID_FILE_HANDLE;
    }
}
#endif

U32 msAPI_BKFS_FileWrite(U8 handleID,U32VA BuffAddr,U32 writeLength)
{
    LongLong currentLength;
    LongLong currentPosition;
    U16 bulkFileID;
    U16 currentBulkID;

    U32 processedBytes=0;
    U16 byteCount;
    U32 currentBulkSectorNO;
    U32 currentSectorOffset;
    BulkFileHandle* pHandle;
    U8 i=0;
    U8   uDeviceID = msAPI_BKFS_GetDeviceIndex();
    //LongLong ringSize;
    //U32 ringStartPosition;
    //BOOLEAN ringMode;
    //U32 ringStart=0;
    EN_BKF_OPEN_MODE OpenMode;

    if(msAPI_BKFS_IsInitialized() == FALSE)
    {
        __ASSERT(0);
        return processedBytes;
    }

    if(INVALID_FILE_HANDLE == handleID)
    {
        __ASSERT(0);
        return processedBytes;
    }

    pHandle=BKFS_GetBulkFileHandleXDATA();
    currentLength=pHandle[handleID].FileLength;
    currentPosition=pHandle[handleID].Position;

#if 0
printf("ICP[%lu] / ICL[%lu]\n",currentPosition.Lo,currentLength.Lo);
#endif

    currentBulkSectorNO=pHandle[handleID].CurrentBulkSectorNO;
    currentSectorOffset=pHandle[handleID].CurrentSectorOffset;
    currentBulkID=pHandle[handleID].CurrentBulkID;
    bulkFileID=pHandle[handleID].BulkFileID;
    OpenMode=pHandle[handleID].OpenMode;
    //ringSize=pHandle[handleID].RingSize;
    //ringMode=pHandle[handleID].RingMode;
    //ringStartPosition=pHandle[handleID].RingStartPosition;
    BKFSDBG(printf(">>> [BKFS_FileWrite] :@@ WLength[%lu], CLength[%lu],CBulkID[%u][StartSector %lu][Offset %lu], SPB[%lu]\n",writeLength,currentLength.Lo,currentBulkID,currentBulkSectorNO,currentSectorOffset,BKFS_SectorsPerBulk));
    msAPI_FS_ReturnXData();

    //byteCount=(currentLength.Lo%BytesPerSector);
    byteCount=(currentPosition.Lo%BytesPerSector);

    if(writeLength==0)
    {
        return 0;
    }

    //write non sector aligned bytes
    if(byteCount>0)
    {
        U16 _bytesToWrite;
        if(!msAPI_MSDCtrl_SectorRead(uDeviceID, (currentBulkSectorNO+currentSectorOffset),1,_PA2VA(IO_TEMP_ADDR)))
        {
            __ASSERT(0);
            return 0;
        }

        _bytesToWrite=(BytesPerSector-byteCount)>writeLength?writeLength:(BytesPerSector-byteCount);

        msAPI_FS_MIU_Copy(BuffAddr,(U32)_PA2VA(IO_TEMP_ADDR+ byteCount),_bytesToWrite);

        BKFSDBG(printf(">>> [BKFS_FileWrite] : NonAligned Write : Start[%lu], bytes[%u]\n",(currentBulkSectorNO+currentSectorOffset),_bytesToWrite));
        if(!msAPI_MSDCtrl_SectorWrite(uDeviceID, (currentBulkSectorNO+currentSectorOffset),1, _PA2VA(IO_TEMP_ADDR)))
        {
            __ASSERT(0);
            return 0;
        }

        writeLength-=_bytesToWrite;
        currentPosition=LL_add(&currentPosition,_bytesToWrite);
        if(LL_greater(&currentPosition,&currentLength))
        {
            currentLength=currentPosition;
        }


        BuffAddr+=_bytesToWrite;
        processedBytes+=_bytesToWrite;

        //full write , we need to progress to next sector
        if(_bytesToWrite==(BytesPerSector-byteCount))
        {
            currentSectorOffset++;

            pHandle=BKFS_GetBulkFileHandleXDATA();
            pHandle[handleID].CurrentSectorOffset=currentSectorOffset;
            msAPI_FS_ReturnXData();
        }
    }

    //write sector
    if(writeLength>0)
    {
        U32 _remainSectorCounts=writeLength /BytesPerSector;
        U32 _sectorsToWrite;
        U32 _len;

        while(_remainSectorCounts>0)
        {
            //check if we need to allocate new bulk
            if(currentSectorOffset==BKFS_SectorsPerBulk)
            {
                U16 nextBulk;
                BKFSDBG(printf(">>> [BKFS_FileWrite] BKFS_AllocateNextBulk \n"));
                if(OpenMode == BKF_OPEN_FOR_RING_WRITE)
                {
                    nextBulk=BKFS_GetBulkValue_RingMode(bulkFileID,currentBulkID);
                }
                else if(!BKFS_AllocateNextBulk(currentBulkID,&nextBulk))
                {
                    // allocated failed... then we should stop here
                    BKFSDBG(printf(">>> [BKFS_FileWrite] BKFS_AllocateNextBulk Fail<<<\n"));
                    goto FILE_WRITE_END;
                }

                currentBulkSectorNO=BKFS_GetBulkStartSector(nextBulk);
                if (currentBulkSectorNO == INVALID_BULK_START_SECTOR)
                {
                    BKFSDBG(printf(">>> [BKFS_FileWrite] currentBulkSectorNO = INVALID_BULK_START_SECTOR<<<\n"));
                    goto FILE_WRITE_END;
                }
                currentSectorOffset=0;
                currentBulkID=nextBulk;
                BKFSDBG(printf(">>> [BKFS_FileWrite] BKFS_AllocateNextBulk : nextBulk[%u] currentBulkSectorNO[%lu]\n",nextBulk,currentBulkSectorNO));

                if(OpenMode == BKF_OPEN_FOR_RING_WRITE)
                {
                    BKFSDBG(printf(">>> [BKFS_FileWrite] "));
                    if(BKFS_GetFileStartBulkID(bulkFileID)==nextBulk)
                    {
                        BKFSDBG(printf("Return to Start Bulk[%u], StartSector[%lu]  [A]\n",nextBulk,currentBulkSectorNO));
                    }
                    else
                    {
                        BKFSDBG(printf("Get Next Bulk[%u], StartSector[%lu]  [A]\n",nextBulk,currentBulkSectorNO));
                    }
                }
                else if(OpenMode == BKF_OPEN_FOR_WRITE)
                {
                    BKFSDBG(printf(">>> [BKFS_FileWrite] Allocate Next Bulk[%u], StartSector[%lu]  [A]\n",nextBulk,currentBulkSectorNO));
                }

                pHandle=BKFS_GetBulkFileHandleXDATA();
                pHandle[handleID].CurrentBulkSectorNO=currentBulkSectorNO;
                pHandle[handleID].CurrentSectorOffset=currentSectorOffset;
                pHandle[handleID].CurrentBulkID=currentBulkID;
                msAPI_FS_ReturnXData();
            }

            //try to write as much sectors as possible
            _sectorsToWrite=_remainSectorCounts > (BKFS_SectorsPerBulk-currentSectorOffset)?(BKFS_SectorsPerBulk-currentSectorOffset):_remainSectorCounts;

            //printf("BKFS_DeviceID=%bu,currentBulkSectorNO=0x%08lx,currentSectorOffset=0x%08lx, _sectorsToWrite=0x%08lx,BuffAddr=0x%08lx\n",BKFS_DeviceID,currentBulkSectorNO,currentSectorOffset,(U32)_sectorsToWrite,BuffAddr);
            BKFSDBG(printf(">>> [BKFS_FileWrite] : Full Sector Write: Start[%lu], Write[%lu]\n",(currentBulkSectorNO+currentSectorOffset),_sectorsToWrite));
            if(!msAPI_MSDCtrl_SectorWrite(uDeviceID, (currentBulkSectorNO+currentSectorOffset),_sectorsToWrite,BuffAddr))
            {
                BKFSDBG(printf(">>> [BKFS_FileWrite] Write Error : Full Sector Write: Start[%lu] (H[%bd] CBSS[%lu] CBSO[%lu]), Write[%lu]\n",(currentBulkSectorNO+currentSectorOffset),handleID,currentBulkSectorNO,currentSectorOffset,_sectorsToWrite));
                __ASSERT(0);
               goto FILE_WRITE_END;
            }
            else
            {
                _len=_sectorsToWrite*BytesPerSector;

                currentPosition=LL_add(&currentPosition,_len);
                if(LL_greater(&currentPosition,&currentLength))
                {
                    currentLength = currentPosition;
                }

                currentSectorOffset+=_sectorsToWrite;
                _remainSectorCounts-=_sectorsToWrite;

                processedBytes+=_len;
                writeLength-=_len;
                BuffAddr+=_len;

                pHandle=BKFS_GetBulkFileHandleXDATA();
                pHandle[handleID].CurrentSectorOffset=currentSectorOffset;
                msAPI_FS_ReturnXData();
            }
        }
    }

    //write tail
    if(writeLength>0)
    {
        //check if we need to allocate new bulk
        if(currentSectorOffset==BKFS_SectorsPerBulk)
        {
            U16 nextBulk;

            if(OpenMode == BKF_OPEN_FOR_RING_WRITE)
            {
                nextBulk=BKFS_GetBulkValue_RingMode(bulkFileID,currentBulkID);
            }
            else if(!BKFS_AllocateNextBulk(currentBulkID,&nextBulk))
            {
                // allocated failed... then we should stop here
                goto FILE_WRITE_END;
            }

            currentBulkSectorNO=BKFS_GetBulkStartSector(nextBulk);
            if (currentBulkSectorNO == INVALID_BULK_START_SECTOR)
            {
                BKFSDBG(printf(">>> [BKFS_FileWrite] currentBulkSectorNO = INVALID_BULK_START_SECTOR<<<\n"));
                goto FILE_WRITE_END;
            }
            currentSectorOffset=0;
            currentBulkID=nextBulk;

            if(OpenMode == BKF_OPEN_FOR_RING_WRITE)
            {
                //printf(">>> [BKFS_FileWrite] ");
                if(BKFS_GetFileStartBulkID(bulkFileID)==nextBulk)
                {
                    MS_DEBUG_MSG(printf("Return to Start Bulk[%u], StartSector[%lu]  [A]\n",nextBulk,currentBulkSectorNO));
                }
                else
                {
                    MS_DEBUG_MSG(printf("Get Next Bulk[%u], StartSector[%lu]  [A]\n",nextBulk,currentBulkSectorNO));
                }
            }
            else if(OpenMode == BKF_OPEN_FOR_WRITE)
            {
                MS_DEBUG_MSG(printf(">>> [BKFS_FileWrite] Allocate Next Bulk[%u], StartSector[%lu]  [A]\n",nextBulk,currentBulkSectorNO));
            }

            pHandle=BKFS_GetBulkFileHandleXDATA();
            pHandle[handleID].CurrentBulkSectorNO=currentBulkSectorNO;
            pHandle[handleID].CurrentSectorOffset=currentSectorOffset;
            pHandle[handleID].CurrentBulkID=currentBulkID;
            msAPI_FS_ReturnXData();
        }

        if(!msAPI_MSDCtrl_SectorRead(uDeviceID, (currentBulkSectorNO+currentSectorOffset),1,_PA2VA(IO_TEMP_ADDR)))
        {
            __ASSERT(0);
            goto FILE_WRITE_END;
        }

        msAPI_FS_MIU_Copy(BuffAddr, _PA2VA(IO_TEMP_ADDR), writeLength);
        BKFSDBG(printf(">>> [BKFS_FileWrite] : Tail Sector Write: Start[%lu], bytes[%lu]\n",(currentBulkSectorNO+currentSectorOffset),writeLength));
        if(!msAPI_MSDCtrl_SectorWrite(uDeviceID, (currentBulkSectorNO+currentSectorOffset),1, _PA2VA(IO_TEMP_ADDR)))
        {
            __ASSERT(0);
            goto FILE_WRITE_END;
        }
        else
        {
            currentPosition=LL_add(&currentPosition,writeLength);
            if(LL_greater(&currentPosition,&currentLength))
            {
                 currentLength = currentPosition;
            }

            processedBytes+=writeLength;
        }
    }

FILE_WRITE_END:

    pHandle=BKFS_GetBulkFileHandleXDATA();
    pHandle[handleID].FileLength=currentLength;
    pHandle[handleID].Position=currentPosition;

    #if 0
    printf("[BKFS] CP[%lu] / FL[%lu]\n",currentPosition.Lo,currentLength.Lo);
    #endif

    for(i=0;i<MAX_BULK_FILE_HANDLE_NUM;i++)
    {
        if( pHandle[i].HandleID!=INVALID_FILE_HANDLE //opened
            &&pHandle[i].BulkFileID==bulkFileID //same Bulk File
            &&i!=handleID //not self
            )
        {
            pHandle[i].FileLength=currentLength;
/*
            if(ringMode)
            {
                //update ReadPosition, the ReadPosition can not be less more than a RingSize than the FileLength

                LongLong _readPos;
                _readPos=pHandle[i].Position;
                _readPos=LL_addLong(&_readPos,&ringSize);

                while(!LL_greater(&_readPos,&currentLength))
                {
                    pHandle[i].Position=_readPos;
                    _readPos=LL_addLong(&_readPos,&ringSize);
                }

                //update RingStartPosition
                if(LL_greater(&currentLength,&ringSize))
                {
                    ringStart=(currentLength.Lo & (ringSize.Lo-1));
                    pHandle[handleID].RingStartPosition= ringStart;
                }
                pHandle[i].RingStartPosition= ringStart;
            }
*/
        }
    }
    msAPI_FS_ReturnXData();
    //check other read handle
    return processedBytes;
}

U32 msAPI_BKFS_FileRead(U8 handleID,U32VA BuffAddr,U32 readLength)
{
    LongLong currentPosition;
    LongLong fileLength;
    LongLong ll_tmp;
    U16 bulkFileID;
    U16 currentBulkID;

    U32 processedBytes=0;
    U16 byteCount;
    U32 currentBulkSectorNO;
    U32 currentSectorOffset;
    U8   uDeviceID = msAPI_BKFS_GetDeviceIndex();
//    LongLong ringSize;
//    BOOLEAN ringMode;
//    U32 ringStartPosition;
    EN_BKF_OPEN_MODE OpenMode;
    BulkFileHandle* pHandle;

    if(msAPI_BKFS_IsInitialized() == FALSE)
    {
        __ASSERT(0);
        return 0;
    }

    if(readLength==0)
    {
        return 0;
    }

    pHandle=BKFS_GetBulkFileHandleXDATA();
    currentPosition=pHandle[handleID].Position;
    fileLength=pHandle[handleID].FileLength;
    currentBulkSectorNO=pHandle[handleID].CurrentBulkSectorNO;
    currentSectorOffset=pHandle[handleID].CurrentSectorOffset;
    currentBulkID=pHandle[handleID].CurrentBulkID;
    bulkFileID=pHandle[handleID].BulkFileID;
    //ringSize=pHandle[handleID].RingSize;
    //ringStartPosition=pHandle[handleID].RingStartPosition;
    //ringMode=pHandle[handleID].RingMode;
    OpenMode = pHandle[handleID].OpenMode;
    msAPI_FS_ReturnXData();

    if(LL_equal(&currentPosition,&fileLength))
    {
        return 0;
    }

    ll_tmp=LL_add(&currentPosition,readLength);
    if(LL_greater(&ll_tmp,&fileLength))
    {
        LongLong result;
        result=LL_subtractLong(&fileLength,&currentPosition);
        if(result.Hi>0)
        {
            __ASSERT(0);
        }
        readLength=result.Lo;
    }

    byteCount=(currentPosition.Lo%BytesPerSector);

    //read non sector aligned bytes
    if(byteCount>0)
    {
        U16 _bytesToRead;

        _bytesToRead=(BytesPerSector-byteCount)>readLength?readLength:(BytesPerSector-byteCount);

        if(!msAPI_MSDCtrl_SectorRead(uDeviceID, currentBulkSectorNO+currentSectorOffset, 1, _PA2VA(IO_TEMP_ADDR)))
        {
            __ASSERT(0);
            return 0;
        }

        msAPI_FS_MIU_Copy((U32)_PA2VA(IO_TEMP_ADDR+byteCount), BuffAddr, _bytesToRead);

        BuffAddr+=_bytesToRead;
        processedBytes+=_bytesToRead;
        readLength-=_bytesToRead;

        currentPosition=LL_add(&currentPosition,_bytesToRead);

        if(_bytesToRead==(BytesPerSector-byteCount))
        {
            currentSectorOffset++;
            pHandle=BKFS_GetBulkFileHandleXDATA();
            pHandle[handleID].CurrentSectorOffset=currentSectorOffset;
            msAPI_FS_ReturnXData();
        }
    }

    //read sectors
    if(readLength>0)
    {
        U32 _remainSectorCounts=readLength /BytesPerSector;
        U32 _sectorsToRead;
        U32 _len;

        //read !!
        while(_remainSectorCounts>0)
        {
             //check if we need to move to next bulk
            if(currentSectorOffset==BKFS_SectorsPerBulk)
            {
                U16 nextBulkID;
                if(OpenMode == BKF_OPEN_FOR_RING_WRITE)
                {
                    nextBulkID=BKFS_GetBulkValue_RingMode(bulkFileID,currentBulkID);
                }
                else
                {
                    nextBulkID=BKFS_GetBulkValue(currentBulkID);
                }

                if(nextBulkID==LAST_BULK_ID)
                {
                    goto FILE_READ_END;
                }
                else
                {
                    currentSectorOffset=0;
                    currentBulkID=nextBulkID;
                    currentBulkSectorNO=BKFS_GetBulkStartSector(currentBulkID);
                    pHandle=BKFS_GetBulkFileHandleXDATA();
                    pHandle[handleID].CurrentBulkID=currentBulkID;
                    pHandle[handleID].CurrentSectorOffset=0;
                    pHandle[handleID].CurrentBulkSectorNO=currentBulkSectorNO;
                    msAPI_FS_ReturnXData();
                }
            }

            _sectorsToRead=_remainSectorCounts > (BKFS_SectorsPerBulk-currentSectorOffset)?(BKFS_SectorsPerBulk-currentSectorOffset):_remainSectorCounts;

            if(!msAPI_MSDCtrl_SectorRead(uDeviceID, (currentBulkSectorNO+currentSectorOffset),_sectorsToRead,BuffAddr))
            {
                __ASSERT(0);
               goto FILE_READ_END;
            }
            else
            {
                _len=_sectorsToRead*BytesPerSector;
                currentSectorOffset+=_sectorsToRead;
                _remainSectorCounts-=_sectorsToRead;

                processedBytes+=_len;
                readLength-=_len;
                BuffAddr+=_len;
                currentPosition=LL_add(&currentPosition,_len);

                pHandle=BKFS_GetBulkFileHandleXDATA();
                pHandle[handleID].CurrentSectorOffset=currentSectorOffset;
                msAPI_FS_ReturnXData();
            }
        }
    }

    //read tail
    if(readLength>0)
    {
        //check if we need to move to next bulk
        if(currentSectorOffset==BKFS_SectorsPerBulk)
        {
            U16 nextBulkID;
            if(OpenMode == BKF_OPEN_FOR_RING_WRITE)
            {
                nextBulkID=BKFS_GetBulkValue_RingMode(bulkFileID,currentBulkID);
            }
            else
            {
                nextBulkID=BKFS_GetBulkValue(currentBulkID);
            }

            if(nextBulkID==LAST_BULK_ID)
            {
                goto FILE_READ_END;
            }
            else
            {
                currentSectorOffset=0;
                currentBulkID=nextBulkID;
                currentBulkSectorNO=BKFS_GetBulkStartSector(currentBulkID);
                pHandle=BKFS_GetBulkFileHandleXDATA();
                pHandle[handleID].CurrentBulkID=currentBulkID;
                pHandle[handleID].CurrentSectorOffset=0;
                pHandle[handleID].CurrentBulkSectorNO=currentBulkSectorNO;
                msAPI_FS_ReturnXData();

            }
        }

        if(!msAPI_MSDCtrl_SectorRead(uDeviceID, currentBulkSectorNO+currentSectorOffset,1,_PA2VA(IO_TEMP_ADDR)))
        {
            __ASSERT(0);
            goto FILE_READ_END;

        }
        else
        {
            msAPI_FS_MIU_Copy(_PA2VA(IO_TEMP_ADDR), BuffAddr, readLength);
            currentPosition=LL_add(&currentPosition,readLength);
            processedBytes+=readLength;
        }
    }

FILE_READ_END:

    pHandle=BKFS_GetBulkFileHandleXDATA();
    pHandle[handleID].Position=currentPosition;
    msAPI_FS_ReturnXData();

    return processedBytes;
}

BOOLEAN msAPI_BKFS_FileClose(U8 handleID)
{
    BulkFileHandle* pHandle;
    BulkFileEntry* pEntry;
    U16 bulkFileID;
    EN_BKF_OPEN_MODE mode;
    LongLong fileLength;
    U32 ringStartPosision;
    U16 FileName[256];

    if(msAPI_BKFS_IsInitialized() == FALSE)
    {
        __ASSERT(0);
        return FALSE;
    }
    BKFSDBG(printf("[BKFS] msAPI_BKFS_FileClose:\n")); //BKFSDBG(BKFS_PrintAllHandles());
    pHandle=BKFS_GetBulkFileHandleXDATA();
    bulkFileID=pHandle[handleID].BulkFileID;
    mode=pHandle[handleID].OpenMode;
    fileLength=pHandle[handleID].FileLength;
    ringStartPosision = pHandle[handleID].RingStartPosition;
    msAPI_FS_ReturnXData();

    if(mode==BKF_OPEN_FOR_WRITE|| mode==BKF_OPEN_FOR_RING_WRITE)
    {
        pEntry=BKFS_GetBulkFileEntryXDATA(bulkFileID);
        pEntry->FileLength=fileLength;
        pEntry->RingStartPosition = ringStartPosision;
        memset(FileName,0,sizeof(FileName));
        memcpy(FileName,pEntry->FileName,FS_strlen_U(pEntry->FileName)*2);
        msAPI_FS_ReturnXData();
        BKFS_WriteCurrentCachedBulkFileEntry();
        #if (ENABLE_TO_RECORD_AS_TS_FILE)
        if (mode == BKF_OPEN_FOR_WRITE)
        {
            msAPI_FCtrl_ResetCurrentDirEntryIndex(); //must reset DirEntryIndex before using this quick search.
            if(!BKFS_CreateRecordPathFiles(FileName))
            {
                msAPI_FCtrl_ResetCurrentDirEntryIndex(); //must reset DirEntryIndex before using this quick search.
                __ASSERT(0);
                return FALSE;
            }
            msAPI_FCtrl_ResetCurrentDirEntryIndex(); //must reset DirEntryIndex before using this quick search.
        }
        #endif
    }

    pHandle=BKFS_GetBulkFileHandleXDATA();
    pHandle[handleID].HandleID=INVALID_FILE_HANDLE;
    pHandle[handleID].BulkFileID=INVALID_BULK_FILE_ID;
    msAPI_FS_ReturnXData();
    return TRUE;
}

LongLong msAPI_BKFS_FileLength(U8 handleID)
{
    LongLong len;
    BulkFileHandle* pHandle;
    len.Hi=0xFFFFFFFF;
    len.Lo=0xFFFFFFFF;

    if(msAPI_BKFS_IsInitialized() == FALSE)
    {
        __ASSERT(0);
        return len;
    }

    if(handleID>=MAX_BULK_FILE_HANDLE_NUM)
    {
        __ASSERT(0);
        return len;
    }

    pHandle=BKFS_GetBulkFileHandleXDATA();

    if(pHandle[handleID].HandleID==INVALID_FILE_HANDLE)
    {
        __ASSERT(0); //handle is closed
        msAPI_FS_ReturnXData();
        return len;
    }

    memcpy(&len,&pHandle[handleID].FileLength,sizeof(LongLong));
    msAPI_FS_ReturnXData();

    return len;
}

LongLong msAPI_BKFS_FileTell(U8 handleID)
{
    LongLong pos;
    BulkFileHandle* pHandle;
    pos.Hi=0xFFFFFFFF;
    pos.Lo=0xFFFFFFFF;

    if(msAPI_BKFS_IsInitialized() == FALSE)
    {
        __ASSERT(0);
        return pos;
    }

    if(handleID>=MAX_BULK_FILE_HANDLE_NUM)
    {
        __ASSERT(0);
        return pos;
    }

    pHandle=BKFS_GetBulkFileHandleXDATA();

    if(pHandle[handleID].HandleID==INVALID_FILE_HANDLE)
    {
        __ASSERT(0); //handle is closed
        msAPI_FS_ReturnXData();
        return pos;
    }

    memcpy(&pos,&pHandle[handleID].Position,sizeof(LongLong));

    msAPI_FS_ReturnXData();
    return pos;
}


static BOOLEAN BKFS_FileSeekFromCurrent(U8 handleID,LongLong length)
{
    LongLong currentPosition;
    LongLong fileLength;
    LongLong ll_tmp;
    LongLong ll_tmp2;
    U16 bulkFileID;
    U16 currentBulkID;

    U16 byteCount;
    U32 currentBulkSectorNO;
    U32 currentSectorOffset;
    BulkFileHandle* pHandle;
    //BOOLEAN ringMode;
    EN_BKF_OPEN_MODE OpenMode;

    //if(length==0)
    if(LL_iszero(&length))
    {
        return TRUE;
    }

    pHandle=BKFS_GetBulkFileHandleXDATA();
    currentPosition=pHandle[handleID].Position;
    fileLength=pHandle[handleID].FileLength;
    currentBulkSectorNO=pHandle[handleID].CurrentBulkSectorNO;
    currentSectorOffset=pHandle[handleID].CurrentSectorOffset;
    currentBulkID=pHandle[handleID].CurrentBulkID;
    bulkFileID=pHandle[handleID].BulkFileID;
    //ringMode=pHandle[handleID].RingMode;
    OpenMode=pHandle[handleID].OpenMode;
    msAPI_FS_ReturnXData();

    //ll_tmp=LL_add(&currentPosition,length);
    ll_tmp=LL_addLong(&currentPosition,&length);
    if(LL_greater(&ll_tmp,&fileLength))
    {
        LongLong result;
        result=LL_subtractLong(&fileLength,&currentPosition);
        if(result.Hi>0)
        {
            __ASSERT(0);
        }
        //length=result.Lo;
        length=result;
    }

    byteCount=(currentPosition.Lo%BytesPerSector);

    //read non sector aligned bytes
    if(byteCount>0)
    {
        //U16 _bytes;
        LongLong _bytes;
        LongLong ll_tmpBytes;

        ll_tmpBytes.Hi = 0;
        ll_tmpBytes.Lo = BytesPerSector-byteCount;
        //_bytes=(BytesPerSector-byteCount)>length?length:(BytesPerSector-byteCount);
        _bytes=LL_greater(&ll_tmpBytes, &length)?length:ll_tmpBytes;
        //length-=_bytes;
        length = LL_subtractLong(&length, &_bytes);

        //currentPosition=LL_add(&currentPosition,_bytes);
        currentPosition=LL_addLong(&currentPosition,&_bytes);

        //if(_bytes==(BytesPerSector-byteCount))
        if(LL_equal(&_bytes, &ll_tmpBytes))
        {
            currentSectorOffset++;
            pHandle=BKFS_GetBulkFileHandleXDATA();
            pHandle[handleID].CurrentSectorOffset=currentSectorOffset;
            msAPI_FS_ReturnXData();
        }
    }

    ll_tmp2.Hi = 0;
    ll_tmp2.Lo = 0;
    //read sectors
    //if(length>0)
    if(LL_greater(&length, &ll_tmp2))
    {
        //U32 _remainSectorCounts=length /BytesPerSector;
        //LongLong llTmpSectors = LL_LongDivU32(&length, BytesPerSector);
        LongLong llTmpSectors;
        U32 _remainSectorCounts;
        U32 _sectorsToRead;
        U32 _len;
        llTmpSectors = LL_LongDivU32(&length, BytesPerSector);
        _remainSectorCounts = llTmpSectors.Lo;

        //read !!
        while(_remainSectorCounts>0)
        {
              //check if we need to move to next bulk
            if(currentSectorOffset==BKFS_SectorsPerBulk)
            {
                U16 nextBulkID;
                if(OpenMode==BKF_OPEN_FOR_RING_WRITE)
                {
                    nextBulkID=BKFS_GetBulkValue_RingMode(bulkFileID,currentBulkID);
                }
                else
                {
                    nextBulkID=BKFS_GetBulkValue(currentBulkID);
                }

                if(nextBulkID==LAST_BULK_ID)
                {
                    goto FILE_SEEK_END;
                }
                else
                {
                    currentSectorOffset=0;
                    currentBulkID=nextBulkID;
                    currentBulkSectorNO=BKFS_GetBulkStartSector(currentBulkID);
                    pHandle=BKFS_GetBulkFileHandleXDATA();
                    pHandle[handleID].CurrentBulkID=currentBulkID;
                    pHandle[handleID].CurrentSectorOffset=0;
                    pHandle[handleID].CurrentBulkSectorNO=currentBulkSectorNO;
                    msAPI_FS_ReturnXData();
                }
            }

            _sectorsToRead=_remainSectorCounts > (BKFS_SectorsPerBulk-currentSectorOffset)?(BKFS_SectorsPerBulk-currentSectorOffset):_remainSectorCounts;
            _len=_sectorsToRead*BytesPerSector;
            currentSectorOffset+=_sectorsToRead;
            _remainSectorCounts-=_sectorsToRead;

            //length-=_len;
            length = LL_subtract(&length, _len);
            currentPosition=LL_add(&currentPosition,_len);

            pHandle=BKFS_GetBulkFileHandleXDATA();
            pHandle[handleID].CurrentSectorOffset=currentSectorOffset;
            msAPI_FS_ReturnXData();
        }
    }

    //read tail
    //if(length>0)
    if(LL_greater(&length, &ll_tmp2))
    {
        //check if we need to move to next bulk
        if(currentSectorOffset==BKFS_SectorsPerBulk)
        {
            U16 nextBulkID;
            if(OpenMode==BKF_OPEN_FOR_RING_WRITE)
            {
                nextBulkID=BKFS_GetBulkValue_RingMode(bulkFileID,currentBulkID);
            }
            else
            {
                nextBulkID=BKFS_GetBulkValue(currentBulkID);
            }

            if(nextBulkID==LAST_BULK_ID)
            {
                goto FILE_SEEK_END;
            }
            else
            {
                currentSectorOffset=0;
                currentBulkID=nextBulkID;
                currentBulkSectorNO=BKFS_GetBulkStartSector(currentBulkID);
                pHandle=BKFS_GetBulkFileHandleXDATA();
                pHandle[handleID].CurrentBulkID=currentBulkID;
                pHandle[handleID].CurrentSectorOffset=0;
                pHandle[handleID].CurrentBulkSectorNO=currentBulkSectorNO;
                msAPI_FS_ReturnXData();
            }
        }

        //currentPosition=LL_add(&currentPosition,length);
        currentPosition=LL_addLong(&currentPosition,&length);
    }

FILE_SEEK_END:

    pHandle=BKFS_GetBulkFileHandleXDATA();
    pHandle[handleID].Position=currentPosition;
    msAPI_FS_ReturnXData();

    return TRUE;
}

BOOLEAN msAPI_BKFS_FileSeek(U8 handleID,LongLong seekLength,EN_BKF_SEEK_OPTION option)
{
    BulkFileHandle* pHandle;
    LongLong currentPos;
    //BOOLEAN ringMode;
    //LongLong ringSize;
    //U32 ringStartPosition;
    LongLong fileLength;
    EN_BKF_OPEN_MODE OpenMode;

    if(msAPI_BKFS_IsInitialized() == FALSE)
    {
        __ASSERT(0);
        return FALSE;
    }

    if(handleID>=MAX_BULK_FILE_HANDLE_NUM)
    {
        __ASSERT(0);
        return FALSE;
    }

    pHandle=BKFS_GetBulkFileHandleXDATA();
    if(pHandle[handleID].HandleID==INVALID_FILE_HANDLE)
    {
        __ASSERT(0); //handle is closed
        msAPI_FS_ReturnXData();
        return FALSE;
    }
/*
    if(pHandle[handleID].OpenMode!=BKF_OPEN_FOR_READ)
    {
        __ASSERT(0); //handle is closed
        msAPI_FS_ReturnXData();
        return FALSE;

    }
*/
    currentPos=pHandle[handleID].Position;
    fileLength=pHandle[handleID].FileLength;
    //ringMode=pHandle[handleID].RingMode;
    //ringSize=pHandle[handleID].RingSize;
    //ringStartPosition=pHandle[handleID].RingStartPosition;
    OpenMode = pHandle[handleID].OpenMode;
    msAPI_FS_ReturnXData();

    switch(option)
    {
        case BKF_SEEK_OPTION_FROM_CURRENT_BACKWARD:
        //if((!ringMode)||LL_greater_or_equal(&ringSize,&fileLength))
        {
            //1. not RingMode
            //2. is RingMode but not exceed one ring size
            LongLong targetPos;

            //use targetPos trickly
            //LL_assign(&targetPos,seekLength);
            targetPos = seekLength;
            //seek to head
            if(!BKFS_FileResetReadHandleToBegin(handleID))
            {
                __ASSERT(0);
                return FALSE;
            }

            if(LL_greater_or_equal(&targetPos,&currentPos))
            {
                return TRUE;
            }

            //targetPos=LL_subtract(&currentPos,seekLength);
            targetPos=LL_subtractLong(&currentPos,&seekLength);

            return BKFS_FileSeekFromCurrent(handleID,targetPos);
        }
//        else
/*
        {
// For Ring Mode

            U32 _readPosInRing=0;
            U32 _bytesToSeekFromRingStart;

            //BKFSDBG(printf("currentPos.Lo=0x%08lx\n",currentPos.Lo));

            _readPosInRing=(ringSize.Lo-1)& currentPos.Lo;

            //BKFSDBG(printf("_readPosInRing=0x%08lx,ringStartPosition=0x%08lx\n",_readPosInRing,ringStartPosition));
            if(ringStartPosition<=_readPosInRing)
            {
                seekLength=(seekLength>(_readPosInRing-ringStartPosition))?(_readPosInRing-ringStartPosition):seekLength;
                _bytesToSeekFromRingStart=(_readPosInRing-ringStartPosition-seekLength);
                //BKFSDBG(printf("_bytesToSeekFromRingStart=0x%08lx\n",_bytesToSeekFromRingStart));
            }
            else
            {
                U32 len=LL_subtract(&ringSize,ringStartPosition).Lo+_readPosInRing;
                seekLength=(seekLength>len)?len:seekLength;
                _bytesToSeekFromRingStart=len-seekLength;

            }

            BKFS_FileResetReadHandleToBegin(handleID);
            return BKFS_FileSeekFromCurrent(handleID,_bytesToSeekFromRingStart);
        }
*/
        case BKF_SEEK_OPTION_FROM_BEGIN:
            BKFS_FileResetReadHandleToBegin(handleID);
            return BKFS_FileSeekFromCurrent(handleID,seekLength);
        case BKF_SEEK_OPTION_FROM_CURRENT_FORWARD:
            return BKFS_FileSeekFromCurrent(handleID,seekLength);

        default:
            __ASSERT(0);
            return FALSE;
    }
}

//Set the u32CurrentFreeCluster to the end cluster of index file to speed up
//the search speed of free cluster of FAT32
BOOLEAN msAPI_BKFS_ResetFreeCluster(void)
{

    U8 u8EnvironmentID = msAPI_FSEnv_Register(BKFS_DiskDriveIndex);
    U8 u8Handle;
    U8 u8SectorPerCluster;
    U16 u16BytesPerSector;
    U16 BKFSDirName[9]={'_','M','S','T','B','K','F','S',0};
    U16 BKFSIndexFileName[13] = {'M','S','T','_','B','K','F','S','.','I','D','X',0};
    U32 u32BulkIDXFileSize;
    U32 u32ClusterCntOfBulkIDXFile;
    U32 u32CurrentFreeCluster;
    FileEntry entry;
    FS_EnvironmentStruct* pFS_Env;
    FAT_FileSysStruct* pFAT_FileSys;
    FAT_FileInode *pFileInode;

    if(u8EnvironmentID==INVALID_FS_ENVIRONMENT_INDEX)
    {
        __ASSERT(0);
        return FALSE;
    }

    //Change to root directory
    if(!msAPI_FCtrl_DirectoryChangeToRoot(u8EnvironmentID))
    {
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        return FALSE;
    }

    //check if the forlder _MSTBKFS existed or not
    if(!msAPI_FCtrl_EntrySearchByName(u8EnvironmentID,&BKFSDirName[0],8,&entry))
    {
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        return FALSE;
    }

    if(entry.EntryType!=ENTRY_TYPE_DIR)
    {
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        return FALSE;
    }

    if(!msAPI_FCtrl_DirectoryChange(u8EnvironmentID,&entry))
    {
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        return FALSE;
    }

    //check if the index file  MST_BKFS.IDX existed or not
    if(!msAPI_FCtrl_EntrySearchByName(u8EnvironmentID,&BKFSIndexFileName[0],12,&entry))
    {
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        return FALSE;
    }

    if(entry.EntryType!=ENTRY_TYPE_FILE)
    {
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        return FALSE;
    }

    u8Handle = msAPI_FCtrl_FileOpen(&entry, OPEN_MODE_FOR_READ_WRITE);
    if(u8Handle == INVALID_FILE_HANDLE)
    {
        __ASSERT(0);
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        return FALSE;
    }

    pFS_Env = msAPI_FSEnv_GetEnvironment(u8EnvironmentID);
    if (!pFS_Env)
    {
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        return FALSE;
    }
    pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemXData(pFS_Env->u8FileSystemID);
    if (!pFAT_FileSys)
    {
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        return FALSE;
    }
    u8SectorPerCluster = pFAT_FileSys->stBootSector.BPB_SecPerClus;
    u16BytesPerSector = pFAT_FileSys->stBootSector.BPB_BytsPerSec;

    pFileInode = FAT_File_GetInodeFromHandle(u8Handle);
    u32BulkIDXFileSize = 0x4000+(((U32)msAPI_BKFS_GetTotalBulkCnt())*0x1000);
    u32ClusterCntOfBulkIDXFile = u32BulkIDXFileSize/((U32)u8SectorPerCluster*(U32)u16BytesPerSector);
    u32CurrentFreeCluster = pFileInode->u32FileStartClusterNo+u32ClusterCntOfBulkIDXFile;
    FCtrl_ReturnFileInodeXdata(); //FAT_File_GetHandleXData()
    BKFS_FAT_CloseFiles(u8Handle);
    pFAT_FileSys->u32CurrentFreeCluster = u32CurrentFreeCluster;
    FAT_ReturnXData(); //FCtrl_GetFileSystemXData()
    msAPI_FSEnv_UnRegister(u8EnvironmentID);

    return TRUE;
}

#if 0
U16 msAPI_BKFS_SpeedCheck(void)
{
    //U16 BKFSCheckFileName[23] = {'M','m','S','s','T','t','_','B','b','K','k','F','f','S','s','.','C','c','H','h','K','k',0};
    U16 BKFSCheckFileName[13] = {'T','I','M','E','S','H','I','F','T','.','T','S',0}; //must be, need this action to occupy 1st index in index file.
    U16 u16Speed = 0;
    U16 u16CurrentSpeed = 0;
    U32 u32WriteLength = (U32)0x00040000;
    U32 u32ReadLength = (U32)0x00040000;
    U32 u32BestRWLength = (U32)0x00040000;
    U32 u32PrefixWriteLength = (U32)0x00100000; //1MB
    U32 u32TotalWriteLength = 0;
    U32 u32TotalReadLength = 0;
    U8 u8handle_w, u8handle_r;
    U8 u8BulkCount = 1;
    U8 u8LoopCnt = 5;
    U8 u8Index;
    U32 ts;
    U32 u32testTime = 4000;
    U8 u8DeviceIndex;
    U8 u8DiskDriveIndex;

    if(msAPI_BKFS_IsInitialized() == FALSE)
    {
        __ASSERT(0);
        return 0;
    }

    u8DeviceIndex = msAPI_BKFS_GetDeviceIndex();
    u8DiskDriveIndex = msAPI_BKFS_GetDriveIndex();

    if(msAPI_BKFS_IsPartitionReady(u8DiskDriveIndex, u8DeviceIndex))
    {
        for (u8Index = 0; u8Index < u8LoopCnt; u8Index++)
        {
            if(msAPI_BKFS_FileExist(BKFSCheckFileName))
            {
                if(!msAPI_BKFS_FileDelete(BKFSCheckFileName))
                {
                    __ASSERT(0);
                    return 0;
                }
            }

            u8handle_w=BKFS_FileCreateForWrite(BKFSCheckFileName, BKF_OPEN_FOR_RING_WRITE, &u8BulkCount); //if use BKF_OPEN_FOR_WRITE, it will create TS file.
            u8handle_r=msAPI_BKFS_FileOpen(BKFSCheckFileName,BKF_OPEN_FOR_READ);

            if( (INVALID_FILE_HANDLE == u8handle_w) || (INVALID_FILE_HANDLE == u8handle_r))
            {
                __ASSERT(0);
                return 0;
            }
#if 1//def MIPS_CHAKRA
            msAPI_BKFS_FileWrite(u8handle_w,_PA2VA(PVR_WRITE_SDRAM_ADR),u32PrefixWriteLength); //Prepare 1M data to stagger R/W sectors.
#else
            msAPI_BKFS_FileWrite(u8handle_w,PVR_WRITE_SDRAM_ADR,u32PrefixWriteLength); //Prepare 1M data to stagger R/W sectors.
#endif
            //Start to write for 5 seconds
            BKFSDBG(printf("u32WriteLength[0x%lx]\n", u32WriteLength));
            u32TotalWriteLength = 0;
            u32TotalReadLength = 0;
            ts=msAPI_Timer_GetTime0();
            while(msAPI_Timer_DiffTimeFromNow(ts)<u32testTime)
            {
                U32 u32tempLength_w, u32tempLength_r;

                u32tempLength_w=msAPI_BKFS_FileWrite(u8handle_w,_PA2VA(PVR_WRITE_SDRAM_ADR),u32WriteLength);
                u32tempLength_r=msAPI_BKFS_FileRead(u8handle_r,_PA2VA(PVR_READ_SDRAM_ADR),u32ReadLength);

                u32TotalWriteLength += u32tempLength_w;
                u32TotalReadLength += u32tempLength_r;
            }
            printf(" WriteLength[%lu]\n",u32TotalWriteLength);
            BKFSDBG(printf(" ReadLength[%lu]\n",u32TotalReadLength));

            msAPI_BKFS_FileClose(u8handle_r);
            msAPI_BKFS_FileClose(u8handle_w);

            //do not delete created timeshift file to occupy 1st index in bulk index file,
            //unless there is no any timeshift bulk to be reserved.
            if (msAPI_BKFS_GetTimeShiftReservedBulkCnt() == 0)
            {
                if(msAPI_BKFS_FileExist(BKFSCheckFileName))
                {
                    if(!msAPI_BKFS_FileDelete(BKFSCheckFileName))
                    {
                        __ASSERT(0);
                    }
                }
            }

            u16CurrentSpeed = (U16)(((u32TotalWriteLength/(u32testTime/1000)))/1024);
            if (u16CurrentSpeed > u16Speed)
            {
                u16Speed = u16CurrentSpeed;
                u32BestRWLength = u32WriteLength;
            }
            //printf("u32WriteLength is %ld, u16CurrentSpeed is %d\n", u32WriteLength/1024, u16CurrentSpeed);
            u32WriteLength = u32WriteLength/2; //test 256KB->128KB->64KB->32KB->16KB
            u32ReadLength = u32ReadLength/2;
        }
        //u16Speed = (U16)(((u32TotalWriteLength/(u32testTime/1000)))/1024);
        //printf("u32BestRWLength is %ld, u16Speed is %d\n", u32BestRWLength/1024, u16Speed);
        msAPI_BKFS_SetBulkSpeed(u16Speed);
        msAPI_BKFS_SetBulkRWKByteOfSpeed((U16)(u32BestRWLength/1024));
        return u16Speed;
    }
    else
    {
        return 0;
    }
}
#endif

//IDX_FILE_StartSector: Byte 0x00~0x03
U32 msAPI_BKFS_GetBulkVersionNo(void)
{
    U32* pu32=NULL;
    U32 u32BulkVersionNo;
    U32 sectorAddr= IDX_FILE_StartSector;
    U8   uDeviceID = msAPI_BKFS_GetDeviceIndex();

    if(!msAPI_MSDCtrl_SectorRead(uDeviceID, sectorAddr,1,_PA2VA(IO_TEMP_ADDR)))
    {
        return 0;   // 0 as error on getting version
    }
    pu32=(U32 xdata*)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);
    GET_MISCINFO(u32BulkVersionNo, BULK_VERSION, pu32);
    msAPI_FS_ReturnXData();

    return u32BulkVersionNo;
}

BOOLEAN BKFS_GetBulkTBLSize(U32 *pTotalSTSectTBL_Cnt, U32 *pTotalAllocTBL_Cnt)
{
    U32* pu32=NULL;
    U32 sectorAddr= IDX_FILE_StartSector;
    U8   uDeviceID = msAPI_BKFS_GetDeviceIndex();

    /*if (!msAPI_BKFS_IsFormated(u8DiskDriveIndex))
    {
        __ASSERT(0);
        return 0;
    }*/

    if(!msAPI_MSDCtrl_SectorRead(uDeviceID, sectorAddr,1,_PA2VA(IO_TEMP_ADDR)))
    {
        __ASSERT(0);
        return FALSE;
    }
    pu32=(U32 xdata*)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);
    GET_MISCINFO((*pTotalSTSectTBL_Cnt), STARTSECTBL_NODECNT, pu32);
    GET_MISCINFO((*pTotalAllocTBL_Cnt), ALLOCTBL_NODECNT, pu32);
    msAPI_FS_ReturnXData();

    if(((*pTotalSTSectTBL_Cnt)&0xFFFF0000)!=BULK_FS_MAGIC_HEADER ||
        ((*pTotalAllocTBL_Cnt)&0xFFFF0000)!=BULK_FS_MAGIC_HEADER )
         return FALSE;
    *pTotalSTSectTBL_Cnt &= 0x0000FFFF;
    *pTotalAllocTBL_Cnt &= 0x0000FFFF;
    return TRUE;
}

U32 msAPI_BKFS_GetTotalDiskSizeSetToUsedMB(void)
{
    U32* pu32=NULL;
    U32 u32TotalDiskSizeSetToUsed;
    U32 sectorAddr= IDX_FILE_StartSector;
    U8   uDeviceID = msAPI_BKFS_GetDeviceIndex();

    /*if (!msAPI_BKFS_IsFormated(u8DiskDriveIndex))
    {
        __ASSERT(0);
        return 0;
    }*/
    if(msAPI_BKFS_IsInitialized() == FALSE)
    {
        __ASSERT(0);
        return 0;
    }

    if(!msAPI_MSDCtrl_SectorRead(uDeviceID, sectorAddr,1,_PA2VA(IO_TEMP_ADDR)))
    {
        __ASSERT(0);
        return 0;
    }
    pu32=(U32 xdata*)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);
    GET_MISCINFO(u32TotalDiskSizeSetToUsed, TOTAL_SIZE_USED, pu32);
    msAPI_FS_ReturnXData();
    return u32TotalDiskSizeSetToUsed;
}

U16 msAPI_BKFS_GetTotalBulkCnt(void)
{
    U8* pu8=NULL;
    U32 u32TotalBulkCnt;
    U32 sectorAddr= IDX_FILE_StartSector;
    U8   uDeviceID = msAPI_BKFS_GetDeviceIndex();

    if(msAPI_BKFS_IsInitialized() == FALSE)
    {
        __ASSERT(0);
        return 0;
    }
    /*if (!msAPI_BKFS_IsFormated(u8DiskDriveIndex))
    {
        __ASSERT(0);
        return 0;
    }*/

    if(!msAPI_MSDCtrl_SectorRead(uDeviceID, sectorAddr,1,_PA2VA(IO_TEMP_ADDR)))
    {
        __ASSERT(0);
        return 0;
    }
    pu8=(U8 xdata*)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);
    GET_MISCINFO(u32TotalBulkCnt, TOTAL_BULK, pu8);
    msAPI_FS_ReturnXData();
    return (U16)u32TotalBulkCnt; //the bulk cnt will be limited within U16
}

U16 msAPI_BKFS_GetBulkSpeed(void)
{
    U8* pu8=NULL;
    U16 u16Speed;
    U32 sectorAddr= IDX_FILE_StartSector;
    U8   uDeviceID = msAPI_BKFS_GetDeviceIndex();

    /*if (!msAPI_BKFS_IsFormated(u8DiskDriveIndex))
    {
        __ASSERT(0);
        return 0;
    }*/
    if(msAPI_BKFS_IsInitialized() == FALSE)
    {
        return 0;
    }
    if(!msAPI_MSDCtrl_SectorRead(uDeviceID, sectorAddr,1,_PA2VA(IO_TEMP_ADDR)))
    {
        __ASSERT(0);
        return 0;
    }
    pu8=(U8 xdata*)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);
    GET_MISCINFO(u16Speed, BULK_SPEED, pu8);
    msAPI_FS_ReturnXData();
    return u16Speed;
}

BOOLEAN msAPI_BKFS_SetBulkSpeed(U16 u16Speed)
{
    U8* pu8=NULL;
    U32 sectorAddr= IDX_FILE_StartSector;
    U8   uDeviceID = msAPI_BKFS_GetDeviceIndex();

    /*if (!msAPI_BKFS_IsFormated(u8DiskDriveIndex))
    {
        __ASSERT(0);
        return FALSE;
    }*/
    if(msAPI_BKFS_IsInitialized() == FALSE)
    {
        __ASSERT(0);
        return FALSE;
    }
    if(!msAPI_MSDCtrl_SectorRead(uDeviceID, sectorAddr,1,_PA2VA(IO_TEMP_ADDR)))
    {
        __ASSERT(0);
        return FALSE;
    }
    pu8=(U8 xdata*)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);

    SET_MISCINFO(pu8, BULK_SPEED, u16Speed);

    if(!msAPI_MSDCtrl_SectorWrite(uDeviceID, sectorAddr,1,_PA2VA(IO_TEMP_ADDR)))
    {
        __ASSERT(0);
        msAPI_FS_ReturnXData();
        return FALSE;
    }
    msAPI_FS_ReturnXData();
    return TRUE;
}

U16 msAPI_BKFS_GetBulkRWKByteOfSpeed(void)
{
    U8* pu8=NULL;
    U16 u16RWKByteOfSpeed;
    U32 sectorAddr= IDX_FILE_StartSector;
    U8  uDeviceID = msAPI_BKFS_GetDeviceIndex();

    /*if (!msAPI_BKFS_IsFormated(u8DiskDriveIndex))
    {
        __ASSERT(0);
        return 0;
    }*/
    if(msAPI_BKFS_IsInitialized() == FALSE)
    {
        return 0;
    }
    if(!msAPI_MSDCtrl_SectorRead(uDeviceID, sectorAddr,1,_PA2VA(IO_TEMP_ADDR)))
    {
        __ASSERT(0);
        return 0;
    }
    pu8=(U8 xdata*)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);
    GET_MISCINFO(u16RWKByteOfSpeed, BULK_RWBYTES_OF_SPEED, pu8);
    msAPI_FS_ReturnXData();
    return u16RWKByteOfSpeed;
}

BOOLEAN msAPI_BKFS_SetBulkRWKByteOfSpeed(U16 u16RWKByteOfSpeed)
{
    U8* pu8=NULL;
    U32 sectorAddr= IDX_FILE_StartSector;
    U8  uDeviceID = msAPI_BKFS_GetDeviceIndex();

    /*if (!msAPI_BKFS_IsFormated(u8DiskDriveIndex))
    {
        __ASSERT(0);
        return FALSE;
    }*/
    if(msAPI_BKFS_IsInitialized() == FALSE)
    {
        __ASSERT(0);
        return FALSE;
    }
    if(!msAPI_MSDCtrl_SectorRead(uDeviceID, sectorAddr,1,_PA2VA(IO_TEMP_ADDR)))
    {
        __ASSERT(0);
        return FALSE;
    }
    pu8=(U8 xdata*)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);

    SET_MISCINFO(pu8, BULK_RWBYTES_OF_SPEED, u16RWKByteOfSpeed);

    if(!msAPI_MSDCtrl_SectorWrite(uDeviceID, sectorAddr,1,_PA2VA(IO_TEMP_ADDR)))
    {
        __ASSERT(0);
        msAPI_FS_ReturnXData();
        return FALSE;
    }
    msAPI_FS_ReturnXData();
    return TRUE;
}

BOOLEAN msAPI_BKFS_SetTimeShiftReservedBulkCnt(U16 u16BulkCnt)
{
    U16* pu16=NULL;
    U32 sectorAddr= IDX_FILE_StartSector;
    U8   uDeviceID = msAPI_BKFS_GetDeviceIndex();

    /*if (!msAPI_BKFS_IsFormated(u8DiskDriveIndex))
    {
        __ASSERT(0);
        return FALSE;
    }*/

    if(msAPI_BKFS_IsInitialized() == FALSE)
    {
        __ASSERT(0);
        return FALSE;
    }
    if(!msAPI_MSDCtrl_SectorRead(uDeviceID, sectorAddr,1,_PA2VA(IO_TEMP_ADDR)))
    {
        __ASSERT(0);
        return FALSE;
    }
    pu16=(U16 xdata*)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);
    SET_MISCINFO(pu16, RESERVED_BULKCNT, u16BulkCnt);
    u16BulkCnt = BKFSSwap16(u16BulkCnt);
    if(!msAPI_MSDCtrl_SectorWrite(uDeviceID, sectorAddr,1,_PA2VA(IO_TEMP_ADDR)))
    {
        __ASSERT(0);
        msAPI_FS_ReturnXData();
        return FALSE;
    }
    msAPI_FS_ReturnXData();

    g_u16TimeShiftReservedBulkCnt = u16BulkCnt;

    return BKFS_FetchAllocationTable();//recalculate Free drive space

}

U16 msAPI_BKFS_GetTimeShiftReservedBulkCnt(void)
{
    U16* pu16=NULL;
    U16 u16BulkCnt;
    U32 sectorAddr= IDX_FILE_StartSector;
    U8   uDeviceID = msAPI_BKFS_GetDeviceIndex();

    /*if (!msAPI_BKFS_IsFormated(u8DiskDriveIndex))
    {
        __ASSERT(0);
        return 0;
    }*/

    if(!msAPI_MSDCtrl_SectorRead(uDeviceID, sectorAddr,1,_PA2VA(IO_TEMP_ADDR)))
    {
        __ASSERT(0);
        return 0;
    }
    pu16=(U16 xdata*)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);
    GET_MISCINFO(u16BulkCnt, RESERVED_BULKCNT, pu16);
    msAPI_FS_ReturnXData();
    return u16BulkCnt;
}

BOOLEAN msAPI_BKFS_SetTimeShiftRecordLengthMB(U32 u32TimeShiftRecordLengthMB)
{
    U32* pu32=NULL;
    U32 sectorAddr= IDX_FILE_StartSector;
    U16 u16BulkCnt = (U16)(u32TimeShiftRecordLengthMB/((U32)(BULK_SIZE/BYTES_PER_MEGA)));
    U8   uDeviceID = msAPI_BKFS_GetDeviceIndex();
    U16 u16TotalBulkCnt = msAPI_BKFS_GetTotalBulkCnt();

    if (u16BulkCnt > u16TotalBulkCnt)
    {
        u16BulkCnt = u16TotalBulkCnt;
        u32TimeShiftRecordLengthMB = (U32)(u16BulkCnt*((U32)(BULK_SIZE/BYTES_PER_MEGA)));
    }

    /*if (!msAPI_BKFS_IsFormated(u8DiskDriveIndex))
    {
        __ASSERT(0);
        return FALSE;
    }*/
    if(msAPI_BKFS_IsInitialized() == FALSE)
    {
        __ASSERT(0);
        return FALSE;
    }
    if(!msAPI_MSDCtrl_SectorRead(uDeviceID, sectorAddr,1,_PA2VA(IO_TEMP_ADDR)))
    {
        __ASSERT(0);
        return FALSE;
    }
    pu32=(U32 xdata*)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);
    SET_MISCINFO(pu32, RESERVED_SPACEMB, u32TimeShiftRecordLengthMB);
    if(!msAPI_MSDCtrl_SectorWrite(uDeviceID, sectorAddr,1,_PA2VA(IO_TEMP_ADDR)))
    {
        __ASSERT(0);
        msAPI_FS_ReturnXData();
        return FALSE;
    }
    msAPI_FS_ReturnXData();

    //Update reserved bulk count
    msAPI_BKFS_SetTimeShiftReservedBulkCnt(u16BulkCnt);

    return TRUE;
}

U32 msAPI_BKFS_GetTimeShiftRecordLengthMB(void)
{
    U32* pu32=NULL;
    U32 u32TimeShiftRecordLengthMB;
    U32 sectorAddr= IDX_FILE_StartSector;
    U8   uDeviceID = msAPI_BKFS_GetDeviceIndex();

    /*if (!msAPI_BKFS_IsFormated(u8DiskDriveIndex))
    {
        __ASSERT(0);
        return 0;
    }*/
    if(msAPI_BKFS_IsInitialized() == FALSE)
    {
        __ASSERT(0);
        return 0;
    }

    if(!msAPI_MSDCtrl_SectorRead(uDeviceID, sectorAddr,1,_PA2VA(IO_TEMP_ADDR)))
    {
        __ASSERT(0);
        return 0;
    }
    pu32=(U32 xdata*)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);
    GET_MISCINFO(u32TimeShiftRecordLengthMB, RESERVED_SPACEMB, pu32);
    msAPI_FS_ReturnXData();
    return u32TimeShiftRecordLengthMB;
}

//IDX_FILE_StartSector: Byte 0x10~0x11
//Used for storing the maximun number of bulk file entry that has been used in index file.
//This data can be used to check if all bulk file entry has relative TS file.
BOOLEAN msAPI_BKFS_SetMaxUsedBulkFileEntryIndex(U16 u16MaxUsedBulkFileEntryIndex)
{
    U16* pu16=NULL;
    U32 sectorAddr= IDX_FILE_StartSector;
    U8   uDeviceID = msAPI_BKFS_GetDeviceIndex();

    /*if (!msAPI_BKFS_IsFormated(u8DiskDriveIndex))
    {
        __ASSERT(0);
        return FALSE;
    }*/
    if(msAPI_BKFS_IsInitialized() == FALSE)
    {
        __ASSERT(0);
        return FALSE;
    }

    if(!msAPI_MSDCtrl_SectorRead(uDeviceID, sectorAddr,1,_PA2VA(IO_TEMP_ADDR)))
    {
        __ASSERT(0);
        return FALSE;
    }
    pu16=(U16 xdata*)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);
    SET_MISCINFO(pu16, BULK_INDEXMAX, u16MaxUsedBulkFileEntryIndex);
    if(!msAPI_MSDCtrl_SectorWrite(uDeviceID, sectorAddr,1,_PA2VA(IO_TEMP_ADDR)))
    {
        __ASSERT(0);
        msAPI_FS_ReturnXData();
        return FALSE;
    }
    msAPI_FS_ReturnXData();
    return TRUE;
}

U16 msAPI_BKFS_GetMaxUsedBulkFileEntryIndex(void)
{
    U16* pu16=NULL;
    U16 u16MaxUsedBulkFileEntryIndex;
    U32 sectorAddr= IDX_FILE_StartSector;
    U8   uDeviceID = msAPI_BKFS_GetDeviceIndex();
    /*if (!msAPI_BKFS_IsFormated(u8DiskDriveIndex))
    {
        __ASSERT(0);
        return 0;
    }*/
    if(msAPI_BKFS_IsInitialized() == FALSE)
    {
        __ASSERT(0);
        return 0;
    }

    if(!msAPI_MSDCtrl_SectorRead(uDeviceID,sectorAddr,1, _PA2VA(IO_TEMP_ADDR)))
    {
        __ASSERT(0);
        return 0;
    }
    pu16=(U16 xdata*)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);
    GET_MISCINFO(u16MaxUsedBulkFileEntryIndex, BULK_INDEXMAX, pu16);
    msAPI_FS_ReturnXData();
    return u16MaxUsedBulkFileEntryIndex;
}

BOOLEAN msAPI_BKFS_SetDefaultDiskDriveIndex(U8 u8DefaultDrive)
{
    U8* pu8=NULL;
    U32  sectorAddr= 0x0; //MBR
    U8   uDeviceID = msAPI_BKFS_GetDeviceIndex();

    if (u8DefaultDrive >= DISK_DRIVE_NUM)
    {
        return FALSE;
    }

    /*if (!msAPI_BKFS_IsFormated(u8DefaultDrive))
    {
        __ASSERT(0);
        return FALSE;
    }*/

    if(!msAPI_MSDCtrl_SectorRead(uDeviceID, sectorAddr,1, _PA2VA(IO_TEMP_ADDR)))
    {
        __ASSERT(0);
        return FALSE;
    }
    pu8=(U8 xdata*)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);
    pu8[48] = 'M'; pu8[49] = 'S'; pu8[50] = 'T'; pu8[51] = 'D'; pu8[52] = 'R'; pu8[53] = 'V'; //mstar magic number
    pu8[54] = u8DefaultDrive;
    if(!msAPI_MSDCtrl_SectorWrite(uDeviceID, sectorAddr, 1, _PA2VA(IO_TEMP_ADDR)))
    {
        __ASSERT(0);
        msAPI_FS_ReturnXData();
        return FALSE;
    }
    msAPI_FS_ReturnXData();
    return TRUE;
}

U8 msAPI_BKFS_GetDefaultDiskDriveIndex(void)
{
    U8* pu8=NULL;
    U8  u8DefaultDiskDriveIndex = 0;
    U32 sectorAddr= 0x0; //MBR
    U8  uDeviceID = msAPI_BKFS_GetDeviceIndex();

    if(!msAPI_MSDCtrl_SectorRead(uDeviceID,sectorAddr,1, _PA2VA(IO_TEMP_ADDR)))
    {
        __ASSERT(0);
        return 0;
    }

    pu8=(U8 xdata*)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);
    if (!((pu8[48] == 'M') && (pu8[49] == 'S') && (pu8[50] == 'T') &&
         (pu8[51] == 'D') && (pu8[52] == 'R') && (pu8[53] == 'V'))) //mstar magic number
    {
        msAPI_FS_ReturnXData();
        return 0;
    }

    u8DefaultDiskDriveIndex = pu8[54];
    msAPI_FS_ReturnXData();
    return u8DefaultDiskDriveIndex;
}


BFK_PARA_OPT_RES msAPI_BKFS_SetBulkFileInfo(U16* pu16BulkFileName, U16* u16BulkFileID, BFK_PROG_INFO info, void *pBuffer, U16 bufLen)
{
   U16 bulkFileID;
   BulkFileEntry *pHandle;
   BFK_PARA_OPT_RES ret;
   U16 uLen;
   U16 *pU16Addr;

    if(msAPI_BKFS_IsInitialized() == FALSE)
    {
        __ASSERT(0);
        return BKF_PARA_ERROR_STORAGE;
    }

   if(pBuffer == NULL || bufLen == 0)
       return BKF_PARA_INVALID_PARAM;

  if (*u16BulkFileID == INVALID_BULK_FILE_ID)
   {
       bulkFileID=BKFS_SearchBulkFile(pu16BulkFileName);
       if(bulkFileID == INVALID_BULK_FILE_ID)
       {
           return BKF_PARA_ERROR_NOFILE;
       }
       *u16BulkFileID = bulkFileID;
   }
   else bulkFileID = *u16BulkFileID;

   pHandle= BKFS_GetBulkFileEntryXDATA(bulkFileID);

   if(pHandle == NULL)
        return BKF_PARA_ERROR_STORAGE;

   switch(info)
   {
     case  BKF_PARA_SERVICE_TYPE:
       if(bufLen < sizeof(MEMBER_SERVICETYPE))
       {
           ret = BKF_PARA_INVALID_PARAM;
           break;
       }
       //Support DTV/RADIO only
       if ((*(MEMBER_SERVICETYPE*)pBuffer != E_SERVICETYPE_DTV) && (*(MEMBER_SERVICETYPE*)pBuffer != E_SERVICETYPE_RADIO))
       {
           ret = BKF_PARA_INVALID_PARAM;
           break;
       }
       pHandle->eServiceType = *(MEMBER_SERVICETYPE*)pBuffer;
       ret = BKF_PARA_SUCCESS;
       break;
     case  BKF_PARA_PROGRAM_NAME:
       pU16Addr = (U16 *)pBuffer;
       uLen = 0;//length will include string tail
       while(pU16Addr[uLen])
             uLen++;
       uLen++;//include tail zero
       if(uLen>PVR_MAX_PROGRAM_NAME_LEN)
       {
           ret = BKF_PARA_INVALID_PARAM;
           break;
       }
       memset(pHandle->ProgramName, 0, PVR_MAX_PROGRAM_NAME_LEN*sizeof(U16));
       memcpy(pHandle->ProgramName, pU16Addr, uLen*sizeof(U16));
       ret = BKF_PARA_SUCCESS;
       break;
     case  BKF_PARA_CHANNEL_NAME:
       pU16Addr = (U16 *)pBuffer;
       uLen = 0;//length will include string tail
       while(pU16Addr[uLen])
             uLen++;
       uLen++;//include tail zero
       if(uLen>PVR_MAX_CHANNEL_NAME_LEN)
       {
           ret = BKF_PARA_INVALID_PARAM;
           break;
       }
       memset(pHandle->ChannelName, 0, PVR_MAX_CHANNEL_NAME_LEN*sizeof(U16));
       memcpy(pHandle->ChannelName, pU16Addr, uLen*sizeof(U16));
       ret = BKF_PARA_SUCCESS;
       break;
     case BKF_PARA_PROGRAM_DESC:
       pU16Addr = (U16 *)pBuffer;
       uLen = 0;//length will include string tail
       while(pU16Addr[uLen])
             uLen++;
       uLen++;//include tail zero
       if(uLen>PVR_MAX_PROGRAM_DESC_LEN)
       {
           ret = BKF_PARA_INVALID_PARAM;
           break;
       }
       memset(pHandle->ProgramDesc, 0, PVR_MAX_PROGRAM_DESC_LEN);
       memcpy(pHandle->ProgramDesc, pU16Addr, uLen*sizeof(U16));
       ret = BKF_PARA_SUCCESS;
       break;
     case  BKF_PARA_STARTDT:
       if(bufLen < sizeof(U32))
       {
           ret = BKF_PARA_INVALID_PARAM;
           break;
       }
       pHandle->u32StartDT = *(U32*)pBuffer;
       ret = BKF_PARA_SUCCESS;
       break;
     case  BKF_PARA_DURATION:
       if(bufLen < sizeof(U32))
       {
           ret = BKF_PARA_INVALID_PARAM;
           break;
       }
       pHandle->u32Duration= *(U32*)pBuffer;
       ret = BKF_PARA_SUCCESS;
       break;
     case BKF_PARA_TELL_FILELENGTH:
       ret = BKF_PARA_INVALID_PARAM;
       break;
     default:
        ret = BKF_PARA_INVALID_PARAM;
        break;
    }
    msAPI_FS_ReturnXData();

    if(ret == BKF_PARA_SUCCESS)
    {
        if(BKFS_WriteBulkFileEntry(bulkFileID, _PA2VA(BULK_FILE_ENTRY_ADDR)) == FALSE)
        {
             ret = BKF_PARA_ERROR_STORAGE;
        }
    }
    return ret;

}

BFK_PARA_OPT_RES msAPI_BKFS_GetBulkFileInfo(U16* pu16BulkFileName, U16* u16BulkFileID,
                                                                      BFK_PROG_INFO info, void *pBuffer, U16 *pBufLen)
{
   U16 bulkFileID;
   BulkFileEntry *pHandle;
   BFK_PARA_OPT_RES ret;
   U16 uLen;
   LongLong *pLongLong;

    if(msAPI_BKFS_IsInitialized() == FALSE)
    {
        __ASSERT(0);
        return BKF_PARA_ERROR_STORAGE;
    }

   if(pBuffer == NULL || *pBufLen == 0)
       return BKF_PARA_INVALID_PARAM;

  if (*u16BulkFileID == INVALID_BULK_FILE_ID)
   {
       bulkFileID=BKFS_SearchBulkFile(pu16BulkFileName);
       if(bulkFileID == INVALID_BULK_FILE_ID)
       {
           return BKF_PARA_ERROR_NOFILE;
       }
       *u16BulkFileID = bulkFileID;
   }
   else bulkFileID = *u16BulkFileID;

   pHandle= BKFS_GetBulkFileEntryXDATA(bulkFileID);

   if(pHandle == NULL)
        return BKF_PARA_ERROR_STORAGE;

   switch(info)
   {
     case  BKF_PARA_SERVICE_TYPE:
       if(*pBufLen < sizeof(MEMBER_SERVICETYPE))
       {
          *pBufLen = sizeof(MEMBER_SERVICETYPE);
           ret = BKF_PARA_LEAK_OF_RET_BUFF;
           break;
       }
       *(MEMBER_SERVICETYPE*)pBuffer = pHandle->eServiceType;
       ret = BKF_PARA_SUCCESS;
       break;
     case  BKF_PARA_PROGRAM_NAME:
       uLen = 0;//length will include string tail
       while(pHandle->ProgramName[uLen])
             uLen++;
       uLen++;//include tail zero
       if(uLen > PVR_MAX_PROGRAM_NAME_LEN)
       {
            __ASSERT(0);
            ret = BKF_PARA_ERROR_BAD_SECTOR_DATA;
            break;
       }
       if(uLen*sizeof(U16) > *pBufLen)
       {
           *pBufLen = uLen*sizeof(U16);
           ret = BKF_PARA_LEAK_OF_RET_BUFF;
           break;
       }
       memcpy(pBuffer, pHandle->ProgramName,uLen*sizeof(U16));
       ret = BKF_PARA_SUCCESS;
       break;
     case  BKF_PARA_CHANNEL_NAME:
       uLen = 0;//length will include string tail
       while(pHandle->ChannelName[uLen])
             uLen++;
       uLen++;//include tail zero
       if(uLen > PVR_MAX_CHANNEL_NAME_LEN)
       {
            __ASSERT(0);
            ret = BKF_PARA_ERROR_BAD_SECTOR_DATA;
            break;
       }
       if(uLen*sizeof(U16) > *pBufLen)
       {
           *pBufLen = uLen*sizeof(U16);
           ret = BKF_PARA_LEAK_OF_RET_BUFF;
           break;
       }
       memcpy(pBuffer, pHandle->ChannelName,uLen*sizeof(U16));
       ret = BKF_PARA_SUCCESS;
       break;
     case  BKF_PARA_PROGRAM_DESC:
       uLen = 0;//length will include string tail
       while(pHandle->ProgramDesc[uLen])
             uLen++;
       uLen++;//include tail zero
       if(uLen > PVR_MAX_PROGRAM_DESC_LEN)
       {
            __ASSERT(0);
            ret = BKF_PARA_ERROR_BAD_SECTOR_DATA;
            break;
       }
       if(uLen*sizeof(U16) > *pBufLen)
       {
           *pBufLen = uLen*sizeof(U16);
           ret = BKF_PARA_LEAK_OF_RET_BUFF;
           break;
       }
       memcpy(pBuffer, pHandle->ProgramDesc,uLen*sizeof(U16));
       ret = BKF_PARA_SUCCESS;
       break;
     case  BKF_PARA_STARTDT:
       if(*pBufLen < sizeof(U32))
       {
          *pBufLen = sizeof(U32);
           ret = BKF_PARA_LEAK_OF_RET_BUFF;
           break;
       }
       *(U32*)pBuffer = pHandle->u32StartDT;
       ret = BKF_PARA_SUCCESS;
       break;
     case  BKF_PARA_DURATION:
       if(*pBufLen < sizeof(U32))
       {
          *pBufLen = sizeof(U32);
           ret = BKF_PARA_LEAK_OF_RET_BUFF;
           break;
       }
       *(U32*)pBuffer = pHandle->u32Duration;
       ret = BKF_PARA_SUCCESS;
       break;
     case BKF_PARA_TELL_FILELENGTH:
       if(*pBufLen < sizeof(LongLong))
       {
          *pBufLen = sizeof(LongLong);
           ret = BKF_PARA_LEAK_OF_RET_BUFF;
           break;
       }
       pLongLong = (LongLong*)pBuffer;
       pLongLong->Hi = pHandle->FileLength.Hi;
       pLongLong->Lo = pHandle->FileLength.Lo;
       ret = BKF_PARA_SUCCESS;
       break;
     default:
        ret = BKF_PARA_INVALID_PARAM;
        break;
    }
    msAPI_FS_ReturnXData();

    return ret;

}

#if 0
//IDX_FILE_StartSector: Byte 0x12~0x13
BOOLEAN msAPI_BKFS_SetTotalRecordedFileCnt(U16 u16RecordedFileCnt)
{
    U16* pu16=NULL;
    U32 sectorAddr= IDX_FILE_StartSector;

    /*if (!msAPI_BKFS_IsFormated(u8DiskDriveIndex))
    {
        __ASSERT(0);
        return FALSE;
    }*/

    if(!msAPI_MSDCtrl_SectorRead(BKFS_DeviceID,sectorAddr,1, _PA2VA(IO_TEMP_ADDR)))
    {
        __ASSERT(0);
        return FALSE;
    }
    pu16=(U16 xdata*)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);
    pu16[9] = u16RecordedFileCnt;
    if(!msAPI_MSDCtrl_SectorWrite(BKFS_DeviceID,sectorAddr,1,_PA2VA(IO_TEMP_ADDR)))
    {
        __ASSERT(0);
        msAPI_FS_ReturnXData();
        return FALSE;
    }
    msAPI_FS_ReturnXData();
    return TRUE;
}

//IDX_FILE_StartSector: Byte 0x12~0x13
U16 msAPI_BKFS_GetTotalRecordedFileCnt(void)
{
    U16* pu16=NULL;
    U16 u16RecordedFileCnt;
    U32 sectorAddr= IDX_FILE_StartSector;

    /*if (!msAPI_BKFS_IsFormated(u8DiskDriveIndex))
    {
        __ASSERT(0);
        return 0;
    }*/

    if(!msAPI_MSDCtrl_SectorRead(BKFS_DeviceID,sectorAddr,1, _PA2VA(IO_TEMP_ADDR)))
    {
        __ASSERT(0);
        return 0;
    }
    pu16=(U16 xdata*)msAPI_FS_GetXData(IO_TEMP_ADDR>>12);
    u16RecordedFileCnt=pu16[9];
    msAPI_FS_ReturnXData();
    return u16RecordedFileCnt;
}
#endif

#if 0 //only for BKFSDBG()
void BKFS_PrintAllHandles(void)
{
    BulkFileHandle* pHandle;
    U8 i;
    printf("[BKFS] HandleDump: >>>>>>\n");
    pHandle=BKFS_GetBulkFileHandleXDATA();
    for(i=0;i<MAX_BULK_FILE_HANDLE_NUM;i++)
    {
        if( pHandle[i].HandleID!=INVALID_FILE_HANDLE)
        {

            if( pHandle[i].OpenMode == BKF_OPEN_FOR_READ)
            {
                printf("       Handle %d is for READ\n", pHandle[i].HandleID );
            }
            else if( pHandle[i].OpenMode == BKF_OPEN_FOR_WRITE )
            {
                printf("       Handle %d is for WRITE\n", pHandle[i].HandleID );
            }
            else if( pHandle[i].OpenMode == BKF_OPEN_FOR_RING_WRITE )
            {
                printf("       Handle %d is for RING_WRITE\n", pHandle[i].HandleID);
            }
        }
    }
    printf(">>>>>>>>>>>>>>>>>>>>\n");
    msAPI_FS_ReturnXData();
}
#endif
#if 0
/***************************************************************************************/
static BOOLEAN msAPI_BKFS_CheckFS(U8 u8EnvironmentID, FileEntry *pfentry, U16 *pu16Filename)
{
    U8 bkfsFolder[8];

    memset(bkfsFolder, 0, sizeof(bkfsFolder));
    memcpy(bkfsFolder, BKFS_FOLDER, LENGTH_OF_BKFS_FOLDER);

    if (INVALID_FS_ENVIRONMENT_INDEX == u8EnvironmentID)
    {
        //printf("\nBKFS ERROR : Invalid FID!");
        return FALSE;
    }

    if(!msAPI_FCtrl_DirectoryChangeToRoot(u8EnvironmentID))
    {
        //printf("\nBKFS ERROR : Fail to Change director to root!");
        return FALSE;
    }

    /* search directory name */
    if(!msAPI_FCtrl_EntrySearchByShortName(u8EnvironmentID, bkfsFolder, LENGTH_OF_BKFS_FOLDER, pfentry))
    {
        //printf("\nBKFS ERROR : Directory not found!");
        return FALSE;
    }

    /* change working directory */
    if(!msAPI_FCtrl_DirectoryChange(u8EnvironmentID, pfentry))
    {
        //printf("\nBKFS ERROR : Fail to change directory!");
        return FALSE;
    }

    /* Search file */
    if(!msAPI_FCtrl_EntrySearchByName(u8EnvironmentID, pu16Filename, LENGTH_OF_BKFS_EPG_FILE, pfentry))
    {
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        __ASSERT(0);
        //printf("\nBKFS ERROR : File not found!");
        return FALSE;
    }
    return TRUE;
}

/***************************************************************************************/
BOOLEAN msAPI_BKFS_FlashCopy(EN_BFK_FLASHCOPY enCopyType, U32 u32Adr, U32 u32Len, U16 *pu16Filename, U8 u8FilenameLen)
{
    U8 u8EnvironmentID, hWriteFile, hReadFile;
    U32 u32RetLen = 0;
    U32 u32Timer;
    U32 u32FileTotalSize;
    FileEntry fentry;
    FAT_FileHandle *pFileHandleT;

    u8EnvironmentID = msAPI_FSEnv_Register(msAPI_BKFS_GetDriveIndex());
    u32RetLen       = 0;
    hWriteFile         = INVALID_FILE_HANDLE;
    hReadFile         = INVALID_FILE_HANDLE;

    if (INVALID_FS_ENVIRONMENT_INDEX == u8EnvironmentID)
    {
        //printf("\nBKFS ERROR : Fail to register!");
        return FALSE;
    }

    if(!msAPI_BKFS_CheckFS(u8EnvironmentID, &fentry, pu16Filename))
    {
        //printf("\nBKFS ERROR : File not found!");
        return FALSE;
    }

    switch (enCopyType)
    {
        case BKF_FLASHCOPY_DRAM2FLASH:

            /* delete MST_BKFS.EPG */
            if (!msAPI_FCtrl_FileDelete(&fentry))
            {
                //printf("\nBKFS ERROR : Fail to delete file!");
                return FALSE;
            }

            /* create MST_BKFS.EPG */
            hWriteFile =  msAPI_FCtrl_FileCreate(u8EnvironmentID, pu16Filename, u8FilenameLen, CREATE_MODE_NEW);
            if (INVALID_FILE_HANDLE == hWriteFile)
            {
                //printf("\nBKFS ERROR : Fail to create file!");
                return FALSE;
            }

            if (!msAPI_BKFS_ResetFreeCluster())
            {
                //printf("\nBKFS ERROR : Fail to reset free cluster!");
                return FALSE;
            }


            //printf("\nDRAM ==> FLASH...");
            u32Timer = msAPI_Timer_GetTime0();

            u32RetLen = msAPI_FCtrl_FileWrite(hWriteFile, u32Adr, u32Len);

            //printf("Done! (%lu ms)\n", msAPI_Timer_DiffTimeFromNow(u32Timer));

            pFileHandleT = FAT_File_GetHandleXData(hWriteFile);
            pFileHandleT->u32FileTotalSize = u32Len;
            //printf("\n%08lx bytes left", u32RetLen);

            msAPI_FCtrl_FileClose(hWriteFile);
            hWriteFile = NULL;
            msAPI_FSEnv_UnRegister(u8EnvironmentID);
            FAT_ReturnXData();

            break;

        case BKF_FLASHCOPY_FLASH2DRAM:

            hReadFile = msAPI_FCtrl_FileOpen(&fentry, OPEN_MODE_FOR_READ_WRITE);

            if(hReadFile == INVALID_FILE_HANDLE)
            {
                //printf("\nBKFS ERROR : Fail to open file!");
                return FALSE;
            }
            //printf("\nFLASH ==> DRAM...");
            pFileHandleT = FAT_File_GetHandleXData(hReadFile);
            u32FileTotalSize = pFileHandleT->u32FileTotalSize;
            FAT_ReturnXData();

            u32Timer = msAPI_Timer_GetTime0();

            if (u32FileTotalSize != 0)
            {
                msAPI_FCtrl_FileSeek(hReadFile, 0, FILE_SEEK_SET);
                u32RetLen = msAPI_FCtrl_FileRead(hReadFile, u32Adr, u32Len);
            }

            //printf("Done! (%lu ms)\n", msAPI_Timer_DiffTimeFromNow(u32Timer));
            //printf("%08lx bytes left\n", u32RetLen);
            msAPI_FCtrl_FileClose(hReadFile);
            hReadFile = NULL;
            msAPI_FSEnv_UnRegister(u8EnvironmentID);

            break;
    }
    return TRUE;
}


U16* msAPI_BKFS_GetEPGFileName()
{
    return name8_3_epg;
}

U8 msAPI_BKFS_GetEPGFileLength()
{
    return LENGTH_OF_BKFS_EPG_FILE;
}

#endif

EN_BFK_VERSION_CHECK msAPI_BKFS_isBulkVersionChanged(void)
{
    switch(msAPI_BKFS_GetBulkVersionNo())
    {
        case 0:
            return BKF_VERCHK_ERROR_GET_VERSION;

        case BKFS_VERSION:
            return BKF_VERCHK_OK;

        default:
            return BKF_VERCHK_DIFFERENT_VERSION;
    }
}

#else
    code U8 _DUMMY;
#endif


#undef MSAPI_BULK_FILE_SYSTEM_C

