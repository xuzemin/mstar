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
#define  MSAPI_FCTRL_C
#define  FCTRL_DBG(flag,x)          //{if(flag){x;}}

#include "datatype.h"
#include "debug.h"

#include "MsTypes.h"
#include "drvBDMA.h"

#include "msAPI_FCtrl.h"

#include "msAPI_N51FS.h"
#include "msAPI_FAT.h"
#include "msAPI_MSDCtrl.h"
#include "msAPI_FSEnv.h"
#include "msAPI_Timer.h"
#include "FSUtil.h"

#define BuildNum0   '0'
#define BuildNum1   '0'
#define BuildNum2   '1'
#define BuildNum3   '0'
#define BuildNum4   '0'
#define BuildNum5   '1'

#define FFLOW_CHECK(x) //x

U8 code FS_VBuf[32] = {'M', 'S', 'V', 'C', '0', '0',
                       'F', '1',
                       BuildNum0,
                       BuildNum1,
                       BuildNum2,
                       BuildNum3,
                       BuildNum4,
                       BuildNum5,
                       '0', '0', '0', '6', '0', '9', '7', '5',
                       'A', '4', '0', '0', '0', '0', '0', '0', '0',
                       'T'};

//static U8 fsCount;
static U8 drvCount;
static U8 drvCountPerPort[MSD_PORT_NUM];

//[used to keep latest DirEntryIndex to enhance the performance of searching directory entry.
#if(!FILE_SYSTEM_SMALL)
#if(FILE_SYSTEM_SEARCH_BY_SHORT_NAME_ENABLE)
static S32 g_s32CurrentDirEntryIndex = -1;
#endif
#endif
//]

                        //global file handle structure
//FAT_FileSysStruct      xdata * _pstFileSys[FCTRL_MAX_FILE_SYS_NO];            //global file sys structure pointer

U8 _u8CurrentDrive;                                                        //global current drive

//**extern function to keep API clean
extern EN_ENTRY_NEXT_RESULT N51FS_EntryNext(U8 enId,FileEntry* pFileToSet);
extern EN_ENTRY_NEXT_RESULT FAT_DirEntryNext(U8 enId,FileEntry* pFileToSet);
#if(FILE_SYSTEM_WRITE_ENABLE)
extern BOOLEAN FAT_Cache_SetFreeCluster(U8 u8fsid);
#endif

static U8 msAPI_FCtrl_FileHandleCreate(void* pFileSys,FileEntry* pFileEntry, U8 u8OpenMode);
void msAPI_FCtrl_FileHandleFree(U8 u8HandleNo);

//following variables is used to replace local varibles.
//TRIKY!! Use them with carefull!!
static MSDCtrl_Drive g_LocalDrive;
static U8 g_LocalLoopIndex;

//Eric added for aeon FS
U32* FCtrl_GetFileSystemInfo(U8 fsid)
{

    if(fsid==INVALID_DRIVE_INDEX)
    {
        __ASSERT(0);
        return NULL;
    }

    return ((U32 xdata*)(msAPI_FS_GetAddr(FILE_SYSTEM_MOUNTED_ADDR)+(U16)fsid*FILE_SYS_STRUCT_SIZE));
}


FileHandleStruct *FCtrl_GetFileHandleInfo(U8 u8FileHandleID)
{
    return (FileHandleStruct xdata*)msAPI_FS_GetAddr(FILE_HANDLE_POOL+FILE_HANDLE_MEMORY_SIZE*u8FileHandleID);
}

FileInodeStruct *FCtrl_GetFileInodeInfo(U8 u8InodeID)
{
    return (FileInodeStruct xdata*)msAPI_FS_GetAddr(FILE_INODE_POOL+FILE_INODE_MEMORY_SIZE*u8InodeID);
}


U32* FCtrl_GetFatTableCacheInfo(U8 fsid)
{
    if(fsid==INVALID_DRIVE_INDEX)
    {
        __ASSERT(0);
        return NULL;
    }

    return (U32 xdata*)msAPI_FS_GetAddr(FILE_FAT_TABLE_CACHE + fsid * FAT_TABLE_CACHE_LEN);
}

void FCtrl_CopyFileHandleInfo(FileHandleStruct *handle, U8 HandleNo)
{
    FileHandleStruct xdata * _pstFileHandle;
    _pstFileHandle = FCtrl_GetFileHandleInfo(HandleNo);
    memcpy(handle, _pstFileHandle, sizeof(FileHandleStruct));
}


BOOLEAN msAPI_FCtrl_EntryFirst(U8 enId)
{
    FS_EnvironmentStruct* pFSEnv;
    BOOLEAN result=FALSE;

    if(enId==INVALID_FILE_HANDLE)
    {
        __ASSERT(0);
        return FALSE;
    }

    pFSEnv=msAPI_FSEnv_GetEnvironment(enId);

    if(pFSEnv==NULL)
    {
        __ASSERT(0);
        return FALSE;
    }


    if(pFSEnv->u8FileSystemType==FILE_SYSTEM_TYPE_FAT)
    {
        result = FAT_DirectroyDirEntryToFirst(enId);

    }
    else if(pFSEnv->u8FileSystemType==FILE_SYSTEM_TYPE_N51FS)
    {
#if ENABLE_N51FS
        result = N51FS_EntryFirst(enId);
#else
        __ASSERT(0);
#endif
    }
    else
    {
        //printf("UnSupport File Type!!\n");
    }


    return result;
}



EN_ENTRY_NEXT_RESULT msAPI_FCtrl_EntryNext(U8 enId, FileEntry* pFileToSet)
{
    FS_EnvironmentStruct* pFSEnv;
    FileEntry tmpEntry;
    EN_ENTRY_NEXT_RESULT result=ENTRY_NEXT_RESULT_ERROR;
    //BOOLEAN result=FALSE;
    pFSEnv=msAPI_FSEnv_GetEnvironment(enId);
    if(pFSEnv == NULL)
    {
        __ASSERT(0);
        return ENTRY_NEXT_RESULT_ERROR;
    }



    if(pFSEnv->u8FileSystemType==FILE_SYSTEM_TYPE_FAT)
    {
        result=FAT_DirEntryNext(enId,&tmpEntry);

    }
    else if(pFSEnv->u8FileSystemType==FILE_SYSTEM_TYPE_N51FS)
    {

#if ENABLE_N51FS

        result= N51FS_EntryNext(enId,&tmpEntry);
#else
        __ASSERT(0);
        return ENTRY_NEXT_RESULT_ERROR;
#endif

    }
    else
    {
        //printf("UnSupport File Type!!\n");
        return ENTRY_NEXT_RESULT_ERROR;
    }

    if(result!=ENTRY_NEXT_RESULT_ERROR)
    {
        memcpy(pFileToSet,&tmpEntry,sizeof(FileEntry));
    }

    return result;


}

#if 0
BOOLEAN msAPI_FCtrl_EntryFirstNext(U8 enId, FileEntry* pFileToSet)
{
     return msAPI_FCtrl_EntryNext(enId,pFileToSet);
}
#endif

static U8 msAPI_FCtrl_GetAvailableDriveIndex(void)
{

    MSDCtrl_Drive* pDrv;
    U8 i;

    pDrv=(MSDCtrl_Drive xdata*)msAPI_FS_GetAddr(DRIVE_MEMORY_ADDR);

    for(i=0;i<DISK_DRIVE_NUM;i++)
    {
        //msAPI_FS_MIU_Copy(DRIVE_MEMORY_ADDR+i*sizeof(MSDCtrl_Drive),GET_DRAM_ADDR(&drv),sizeof(MSDCtrl_Drive));
        if(pDrv[i].DriveIndex==INVALID_DRIVE_INDEX)
        {
            FCTRL_DBG(1,printf("Found available DriveLetter: %d\n",(U16)(i)););
            return i;
        }

    }
    //Not Found
    return INVALID_DRIVE_INDEX;
}

static BOOLEAN msAPI_FCtrl_FileSystemInitial(S8 deviceIndex,U8 fsid,EN_FILE_SYSTEM_TYPE fsType,U8* partitionBytes,U32 logicalBlockAddress)
{
    BOOLEAN bResult = FALSE;
    U32 *pFileSys =NULL;
    pFileSys=msAPI_FS_Memory_Allocate(FILE_SYS_STRUCT_SIZE);

    if(pFileSys==NULL)
    {
        __ASSERT(0);
        return FALSE;
    }

    ((FAT_FileSysStruct*)pFileSys)->FileSystemType=FILE_SYSTEM_TYPE_NONE;

    if(fsType==FILE_SYSTEM_TYPE_FAT)
    {


        FAT_FileSysStruct* pFAT_FileSys=(FAT_FileSysStruct*)pFileSys;
        bResult = FAT_InitialFileSystem(deviceIndex, logicalBlockAddress,partitionBytes, pFAT_FileSys);
        if(bResult)
        {
            pFAT_FileSys->FileSystemType=fsType;
            pFAT_FileSys->FileSystemID=fsid;
        }

    }
    else if(fsType==FILE_SYSTEM_TYPE_N51FS)
    {
#if ENABLE_N51FS
        N51FS_FileSysStruct* pN51FS_FileSys=(N51FS_FileSysStruct*)pFileSys;
        pN51FS_FileSys->FileSystemID=fsid;
        bResult = N51FS_InitialFileSystem(deviceIndex,logicalBlockAddress,partitionBytes,pN51FS_FileSys);
        if(bResult)
        {
            pN51FS_FileSys->FileSystemType=fsType;
        }
#else
        __ASSERT(0);
#endif

    }
    else
    {

            __ASSERT(0);//got a problem here!!
    }

    msAPI_FS_MIU_Copy(GET_DRAM_ADDR(pFileSys),FILE_SYSTEM_MOUNTED_ADDR+(U32)fsid*FILE_SYS_STRUCT_SIZE,FILE_SYS_STRUCT_SIZE);

    //
    if(fsType==FILE_SYSTEM_TYPE_FAT&&bResult)
    {
        U32 offsetSector=0;

        FAT_FileSysStruct* pstFileSys=(FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(fsid);

        offsetSector=pstFileSys->u32FATTableOffsetSectorNo = 0;

        if(!FAT_FATStructureFetch(fsid,offsetSector) )
        {
            __ASSERT(0);

        }

    }

    msAPI_FS_Memory_Free(pFileSys);
    return bResult;

}


//this will always mount drive into system
static EN_DRIVE_INITIAL_STATUS msAPI_FCtrl_MountDrive(U8 deviceIndex,EN_FILE_SYSTEM_TYPE fsType,U8* partitionBytes,U32 logicalBlockAddress,U8 partitionNo, U32 u32MBRLogicBlockAddress, U8 u8IndexInMBR)
{
    U8 i=0;
    MSDCtrl_Drive drv;
    BOOLEAN _btmp = TRUE;

    memset(&drv,0,sizeof(drv));
    for(i=0;i<drvCount;i++)
    {
        _btmp = msAPI_FCtrl_GetDriveByIndex(i,&drv);
        if(drv.DeviceIndex!=INVALID_DEVICE_INDEX)
        {
            if(drv.DeviceIndex==deviceIndex&&drv.PartitionNo==partitionNo)
            {
                FCTRL_DBG(0,printf("  DeviceIndex=%bu, PartitionNo=%bu is already mounted at driveIndex=%bu\n",drv.DeviceIndex,partitionNo,drv.DriveIndex););
                return DRIVE_INITIAL_STATUS_MOUNTED_ALREADY;
            }
        }
    }

    if(drvCount<DISK_DRIVE_NUM)
    {
        BOOLEAN initialStatus=FALSE;

        drv.DeviceIndex=deviceIndex;
        drv.PartitionNo=partitionNo;
        drv.u32MBRLogicBlockAddress = u32MBRLogicBlockAddress;
        drv.u8IndexInMBR = u8IndexInMBR;
        drv.FileSystemType=FILE_SYSTEM_TYPE_NONE;
        drv.DriveIndex=msAPI_FCtrl_GetAvailableDriveIndex();
        drv.LBA=logicalBlockAddress;

        if(drv.DriveIndex==INVALID_DRIVE_INDEX)
        {
            //printf("no slot for new drive!!\n");
            return DRIVE_INITIAL_STATUS_NO_SLOT;
        }

        if(fsType!=FILE_SYSTEM_TYPE_NONE)
        {
            initialStatus=msAPI_FCtrl_FileSystemInitial(deviceIndex,drv.DriveIndex,fsType,partitionBytes,logicalBlockAddress);

            if(initialStatus)
            {
                drv.FileSystemType=fsType;
            }
            else
            {
                return DRIVE_INITIAL_STATUS_ERROR;
            }
        }




        if(msAPI_MSDCtrl_GetDevicePort(deviceIndex)>=MSD_PORT_NUM)
        {
            __ASSERT(0);
            return DRIVE_INITIAL_STATUS_ERROR;
        }

        /*set drive count*/
        drvCount+=1;

        drvCountPerPort[msAPI_MSDCtrl_GetDevicePort(deviceIndex)]+=1;
        FCTRL_DBG(1,printf("Partition %u at DeviceIndex %u is mounted with DriveIndex %u\n",drv.PartitionNo,drv.DeviceIndex,drv.DriveIndex););
        FCTRL_DBG(1,printf("    InitialStatus: %u\n",(U8)initialStatus););
        FCTRL_DBG(1,printf("    FileSystemType:%u. Total Drive Count:%u\n\n",drv.FileSystemType,drvCount););
         /*set drive*/
        msAPI_FS_MIU_Copy(GET_DRAM_ADDR(&drv),DRIVE_MEMORY_ADDR+drv.DriveIndex*sizeof(MSDCtrl_Drive),sizeof(MSDCtrl_Drive));

        /*set init free cluster*/
        #if(FILE_SYSTEM_WRITE_ENABLE)
        if(FILE_SYSTEM_TYPE_FAT == fsType)
        {
            FAT_Cache_SetFreeCluster(drv.DriveIndex);
        }
        #endif

        if(initialStatus)
        {
            return DRIVE_INITIAL_STATUS_SUCCESS;
        }
        else
        {
            return DRIVE_INITIAL_STATUS_ERROR;
        }
    }
    else
        return DRIVE_INITIAL_STATUS_NO_SLOT;
}

#ifdef ENABLE_PTP
static EN_DRIVE_INITIAL_STATUS msAPI_FCtrl_MountPTPDrive(U8 deviceIndex,EN_FILE_SYSTEM_TYPE fsType,U8* partitionBytes,U32 logicalBlockAddress,U8 partitionNo)
{
    U8 progressFlag=0;
    U8 i=0;
    MSDCtrl_Drive drv;

    fsType = fsType;
    partitionBytes = partitionBytes;
    for(i=0;i<drvCount;i++)
    {
        msAPI_FCtrl_GetDriveByIndex(i,&drv);
        if(drv.DeviceIndex!=INVALID_DEVICE_INDEX)
        {
            if(drv.DeviceIndex==deviceIndex&&drv.PartitionNo==partitionNo)
            {
                FCTRL_DBG(0,printf("  DeviceIndex=%bu, PartitionNo=%bu is already mounted at driveIndex=%bu\n",drv.DeviceIndex,partitionNo,drv.DriveIndex););
                return DRIVE_INITIAL_STATUS_MOUNTED_ALREADY;
            }
        }
    }

    if(drvCount<DISK_DRIVE_NUM)
    {
        MSDCtrl_Drive drv;
        BOOLEAN initialStatus = FALSE;

        drv.DeviceIndex=deviceIndex;
        drv.PartitionNo=partitionNo;
        drv.u32MBRLogicBlockAddress = 0;
        drv.u8IndexInMBR = INVALID_MBR_INDEX;
        drv.FileSystemType=FILE_SYSTEM_TYPE_NONE;
        drv.DriveIndex=msAPI_FCtrl_GetAvailableDriveIndex();
        drv.LBA=logicalBlockAddress;

        if(drv.DriveIndex==INVALID_DRIVE_INDEX)
        {
            //printf("no slot for new drive!!\n");
            return DRIVE_INITIAL_STATUS_NO_SLOT;
        }

        /*set drive count*/
        drvCount+=1;
        drvCountPerPort[msAPI_MSDCtrl_GetDevicePort(deviceIndex)]+=1;
        msAPI_FS_MIU_Copy(GET_DRAM_ADDR(&drv),DRIVE_MEMORY_ADDR+drv.DriveIndex*sizeof(MSDCtrl_Drive),sizeof(MSDCtrl_Drive));

        return DRIVE_INITIAL_STATUS_SUCCESS;
    }
    else
        return DRIVE_INITIAL_STATUS_NO_SLOT;
}
#endif

void msAPI_FCtrl_UnmountDrivesOnDevice(U8 deviceIndex)
{
    MSDCtrl_Drive drv;
    U8 i;
    U8 u8Port;

    memset(&drv,0,sizeof(drv));
    u8Port = (U8)msAPI_MSDCtrl_GetDevicePort(deviceIndex);
    FCTRL_DBG(0,printf("msAPI_FCtrl_UnmountDrivesOnDevice : Port[%bd]-Device[%bd]\n",u8Port,deviceIndex););
    //U8 fscount;
    for(i=0;i<DISK_DRIVE_NUM;i++)
    {
        if(msAPI_FCtrl_GetDriveByIndex(i, &drv))
        {
            if(drv.DeviceIndex==deviceIndex)
            {
                FCTRL_DBG(1,printf(" Drive %bu on Device %bu (PartitionNo=%bu) is removed, total driveCount=%bu\n", drv.DriveIndex,drv.DeviceIndex,drv.PartitionNo,drvCount-1););
                drv.DeviceIndex=INVALID_DEVICE_INDEX;
                drv.FileSystemType=FILE_SYSTEM_TYPE_NONE;
                drv.DriveIndex=INVALID_DRIVE_INDEX;
                drv.PartitionNo=0xFF;
                /*clear drive */
                msAPI_FS_MIU_Copy(GET_DRAM_ADDR(&drv),DRIVE_MEMORY_ADDR+(i)*sizeof(MSDCtrl_Drive),sizeof(MSDCtrl_Drive));
                /*set drive count*/
                if(drvCount>0)
                {
                    drvCount-=1;
                    if(u8Port>=MSD_PORT_NUM)
                    {
                        __ASSERT(0);
                        return;
                    }
                    if(drvCountPerPort[u8Port]>0)
                    {
                        FCTRL_DBG(0,printf("Drive count on Port[%bd] = reduce from %bd ",u8Port,drvCountPerPort[u8Port]););
                        drvCountPerPort[u8Port]-=1;
                        FCTRL_DBG(0,printf("to = %bd\n",drvCountPerPort[u8Port]););
                    }
                }
                #if 0
                else
                {
                    __ASSERT(0);
                }
                #endif

            }
        }
     }
}

void msAPI_FCtrl_RemoveDrivesOnDevice(U8 deviceIndex)
{
    FCTRL_DBG(0,printf("  Depricated API!!\n");HERE;);
    msAPI_FCtrl_UnmountDrivesOnDevice(deviceIndex);
}

void msAPI_FCtrl_Init()
{
    U8 i;
    MSDCtrl_Drive drv;

    if(DISK_DRIVE_NUM*(U32)FILE_SYS_STRUCT_SIZE > FILE_SYSTEM_MOUNTED_LEN)
    {
        __ASSERT(0);
    }


    if((FILE_SYSTEM_MOUNTED_ADDR&0xfff)>0)
    {
        __ASSERT(0);
    }

    drvCount=0;
    for(i=0;i<MSD_PORT_NUM;i++)
    {
        drvCountPerPort[i]=0;
    }
    msAPI_FCtrl_FileHandleResetAll();

    drv.DeviceIndex=INVALID_DEVICE_INDEX;
    drv.FileSystemType=FILE_SYSTEM_TYPE_NONE;
    drv.DriveIndex=INVALID_DRIVE_INDEX;
    drv.PartitionNo=0xFF;
    drv.LBA=0;

    //U8 fscount;
    for(i=0;i<DISK_DRIVE_NUM;i++)
    {
        msAPI_FS_MIU_Copy(GET_DRAM_ADDR(&drv),DRIVE_MEMORY_ADDR+(i)*sizeof(MSDCtrl_Drive),sizeof(MSDCtrl_Drive));
    }

}



//------------------------------------------------------------------------------
// MSDCtrl interface API
//------------------------------------------------------------------------------
void FCtrl_addPartitionCount(U8 u8PartitionCount,U32 *PartitionStatus)
{
    int offset = 24;
    U32 u32PartitionCount = ((U32)u8PartitionCount) << offset;
    *PartitionStatus = *PartitionStatus | u32PartitionCount;
}

/* Convert char[2] in little endian format to the host format integer
 */
static unsigned short le16_to_U16(unsigned char *le16)
{
	return ((le16[1] << 8) + le16[0]);
}

/* Convert char[4] in little endian format to the host format integer
 */
static unsigned long le32_to_U32(unsigned char *le32)
{
	return ((le32[3] << 24) + (le32[2] << 16) + (le32[1] << 8) + le32[0]);
}

/* Convert char[8] in little endian format to the host format integer
 */
static unsigned long long le64_to_U64(unsigned char *le64)
{
	return (((unsigned long long)le64[7] << 56) +
		((unsigned long long)le64[6] << 48) +
		((unsigned long long)le64[5] << 40) +
		((unsigned long long)le64[4] << 32) +
		((unsigned long long)le64[3] << 24) +
		((unsigned long long)le64[2] << 16) +
		((unsigned long long)le64[1] << 8) +
		(unsigned long long)le64[0]);
}

/*
 * Private functions
 */
/*
 * msAPI_pmbr_part_valid(): Check for EFI partition signature
 *
 * Returns: 1 if EFI GPT partition type is found.
 */
static U32 msAPI_pmbr_part_valid(struct partition *part)
{
	if (part->sys_ind == EFI_PMBR_OSTYPE_EFI_GPT &&
		le32_to_U32(part->start_sect) == 1UL) {
		return 1;
	}

	return 0;
}

/*
 * msAPI_is_pmbr_valid(): test Protective MBR for validity
 *
 * Returns: 1 if PMBR is valid, 0 otherwise.
 * Validity depends on two things:
 *  1) MSDOS signature is in the last two bytes of the MBR
 *  2) One partition of type EFI_PMBR_OSTYPE_EFI_GPT is found, checked by pmbr_part_valid()
 */
static U32 msAPI_is_pmbr_valid(legacy_mbr * mbr)
{
	U32 i = 0;

	if (!mbr || le16_to_U16(mbr->signature) != MSDOS_MBR_SIGNATURE) {
		return 0;
	}

	for (i = 0; i < 4; i++) {
		if (msAPI_pmbr_part_valid(&mbr->partition_record[i])) {
			return 1;
		}
	}
	return 0;
}

/**
 * msAPI_alloc_read_gpt_entries(): reads the first 4 partition entries from disk
 * @dev_desc
 * @gpt - GPT header
 *
 * Description: Returns ptes on success,  NULL on error.
 * Allocates space for PTEs based on information found in @gpt.
 * Notes: remember to free pte when you're done!
 */
static gpt_entry *msAPI_alloc_read_gpt_entries(U8 deviceIndex,
					 gpt_header * pgpt_head)
{
	U32 count = 0;
	gpt_entry *pte = NULL;

	if (!pgpt_head) {
		FCTRL_DBG(1,printf("%s: Invalid Argument(s)\n", __FUNCTION__););
		return NULL;
	}

	count = le32_to_U32(pgpt_head->num_partition_entries) *
		le32_to_U32(pgpt_head->sizeof_partition_entry);

	FCTRL_DBG(1,printf("%s: count = %lu * %lu = %u\n", __FUNCTION__,
		le32_to_U32(pgpt_head->num_partition_entries),
		le32_to_U32(pgpt_head->sizeof_partition_entry), count););

	/* Allocate memory for PTE, remember to FREE */
	if (count != 0) {
		pte = (gpt_entry *) malloc(512);
	}

	if (count == 0 || pte == NULL) {
		FCTRL_DBG(1,printf("%s: ERROR: Can't allocate 0x%X bytes for GPT Entries\n",
			__FUNCTION__, count););
		return NULL;
	}

    /* Read GPT Entries from device */

    if(!msAPI_MSDCtrl_SectorRead(deviceIndex, (U32)le64_to_U64(pgpt_head->partition_entry_lba),
            1, USB_IO_TEMP_ADDR))
    {
        FCTRL_DBG(1,printf("*** ERROR: Can't read GPT header ***\n"););
        free(pte);
        return NULL;
    }
    msAPI_FS_MIU_Copy(USB_IO_TEMP_ADDR, GET_DRAM_ADDR(pte), 512);

    return pte;
}

//#define GPT_CRC 1
#ifdef GPT_CRC
#define CRC_TABLE_MAX 256
static unsigned long g_crc32_table[CRC_TABLE_MAX];

U32 msAPI_FCtrl_Crc_GetCrc32(unsigned char *buffer, unsigned long length)
{
    U32 ulCRC = 0xFFFFFFFF;
    unsigned char *tmp = buffer;

    while (length--)
    {
        ulCRC = (ulCRC >> 8) ^ g_crc32_table[(unsigned char)(ulCRC & 0xFF) ^ *tmp++];
    }

    return (ulCRC);
}
static void msAPI_FCtrl_Init_CRC_Table(void)
{
    U32 i,j;
    //printf("crc32\n");
    for(i=0;i<CRC_TABLE_MAX;i++)
    {
        g_crc32_table[i]=i<<24;
        for(j=0;j<8;j++)
        {
            if((g_crc32_table[i]&0x80000000L) == 0)
                g_crc32_table[i]=(g_crc32_table[i]<<1);
            else
                g_crc32_table[i]=(g_crc32_table[i]<<1)^0x04C11DB7;
        }
        //printf("0x%08x,\n",drv_crc32_table[i]);
    }
    //printf("\n");
}
#endif

/**
 * msAPI_is_gpt_valid() - tests one GPT header and PTEs for validity
 *
 * lba is the logical block address of the GPT header to test
 * gpt is a GPT header ptr, filled on return.
 * ptes is a PTEs ptr, filled on return.
 *
 * Description: returns 1 if valid,  0 on error.
 * If valid, returns pointers to PTEs.
 */
static U32 msAPI_is_gpt_valid(U8 deviceIndex, gpt_entry ** pgpt_pte, unsigned long long lba,
			gpt_header * pgpt_head)
{
	unsigned long long last_lba;

	if (!pgpt_head) {
		FCTRL_DBG(1,printf("%s: Invalid Argument(s)\n", __FUNCTION__););
		return 0;
	}
    /* Read GPT Header from device */
    if(!msAPI_MSDCtrl_SectorRead(deviceIndex, lba, 1, USB_IO_TEMP_ADDR))
    {
        FCTRL_DBG(1,printf("*** ERROR: Can't read GPT header ***\n"););
    }

    msAPI_FS_MIU_Copy(USB_IO_TEMP_ADDR, GET_DRAM_ADDR(pgpt_head), sizeof(gpt_header));
	/* Check the GPT header signature */
	if (le64_to_U64(pgpt_head->signature) != GPT_HEADER_SIGNATURE) {
		FCTRL_DBG(1,printf("GUID Partition Table Header signature is wrong:"
			"0x%llX != 0x%llX\n",
			(unsigned long long)le64_to_U64(pgpt_head->signature),
			(unsigned long long)GPT_HEADER_SIGNATURE););
		return 0;
	}

#ifdef GPT_CRC
	unsigned char crc32_backup[4] = { 0 };
	unsigned long calc_crc32;
	static BOOLEAN bfirst=0;
	if(bfirst==0)
	{
		bfirst=1;
		msAPI_FCtrl_Init_CRC_Table();
	}
	/* Check the GUID Partition Table CRC */
	memcpy(crc32_backup, pgpt_head->header_crc32, sizeof(crc32_backup));
	memset(pgpt_head->header_crc32, 0, sizeof(pgpt_head->header_crc32));

	calc_crc32 = msAPI_FCtrl_Crc_GetCrc32((unsigned char *)pgpt_head,
		le32_to_U32(pgpt_head->header_size));

	memcpy(pgpt_head->header_crc32, crc32_backup, sizeof(crc32_backup));

	if (calc_crc32 != le32_to_U32(crc32_backup)) {
		FCTRL_DBG(1,printf("GUID Partition Table Header CRC is wrong:"
			"0x%08lX != 0x%08lX\n",
			le32_to_U32(crc32_backup), calc_crc32););
		return 0;
	}
#endif

	/* Check that the my_lba entry points to the LBA that contains the GPT */
	if (le64_to_U64(pgpt_head->my_lba) != lba) {
		FCTRL_DBG(1,printf("GPT: my_lba incorrect: %llX != %llX\n",
			(unsigned long long)le64_to_U64(pgpt_head->my_lba),
			(unsigned long long)lba););
		return 0;
	}

	/* Check the first_usable_lba and last_usable_lba are within the disk. */
	last_lba = (unsigned long long) msAPI_MSDCtrl_GetBlockNum(deviceIndex);
	if (le64_to_U64(pgpt_head->first_usable_lba) > last_lba) {
		FCTRL_DBG(1,printf("GPT: first_usable_lba incorrect: %llX > %llX\n",
			le64_to_U64(pgpt_head->first_usable_lba), last_lba););
		return 0;
	}
	if (le64_to_U64(pgpt_head->last_usable_lba) > last_lba) {
		FCTRL_DBG(1,printf("GPT: last_usable_lba incorrect: %llX > %llX\n",
			le64_to_U64(pgpt_head->last_usable_lba), last_lba););
		return 0;
	}

//	printf("GPT: first_usable_lba: %llX last_usable_lba %llX last lba %llX\n",
//		le64_to_int(pgpt_head->first_usable_lba),
//		le64_to_int(pgpt_head->last_usable_lba), lastlba);

	/* Read and allocate Partition Table Entries */
	*pgpt_pte = msAPI_alloc_read_gpt_entries(deviceIndex, pgpt_head);
	if (*pgpt_pte == NULL) {
		FCTRL_DBG(1,printf("GPT: Failed to allocate memory for PTE\n"););
		return 0;
	}

#ifdef GPT_CRC
	/* Check the GUID Partition Table Entry Array CRC */
	calc_crc32 = msAPI_FCtrl_Crc_GetCrc32((unsigned char *)*pgpt_pte,
		le32_to_U32(pgpt_head->num_partition_entries) *
		le32_to_U32(pgpt_head->sizeof_partition_entry));

	if (calc_crc32 != le32_to_U32(pgpt_head->partition_entry_array_crc32)) {
		FCTRL_DBG(1,printf("GUID Partition Table Entry Array CRC is wrong:"
			"0x%08lX != 0x%08lX\n",
			le32_to_U32(pgpt_head->partition_entry_array_crc32),
			calc_crc32););

		if (*pgpt_pte != NULL) {
			free(*pgpt_pte);
		}
		return 0;
	}
#endif

	/* We're done, all's well */
	return 1;
}

/**
 * msAPI_is_pte_valid(): validates a single Partition Table Entry
 * @gpt_entry - Pointer to a single Partition Table Entry
 *
 * Description: returns 1 if valid,  0 on error.
 */
static int msAPI_is_pte_valid(gpt_entry * pte)
{
	efi_guid_t unused_guid;
	if (!pte) {
		FCTRL_DBG(1,printf("%s: Invalid Argument(s)\n", __FUNCTION__););
		return 0;
	}

	/* Only one validation for now:
	 * The GUID Partition Type != Unused Entry (ALL-ZERO)
	 */
	memset(unused_guid.b, 0, sizeof(unused_guid.b));
	if (memcmp(pte->partition_type_guid.b, unused_guid.b,
		sizeof(unused_guid.b)) == 0) {

//		printf("%s: Found an unused PTE GUID at 0x%08X\n", __FUNCTION__,
//		(unsigned int)pte);

		return 0;
	} else {
		return 1;
	}
}

/**
 * msAPI_FCtrl_LoadGPT(): load GPT and identify partition info
 *
 * Description: returns partition no if valid,  0 on error.
 */
U8 msAPI_FCtrl_LoadGPT(U8 deviceIndex, void * mbr, U32 *PartitionStatus)
{
    gpt_header gpt_head;
    gpt_entry *pgpt_pte[4];
    U32 i = 0, block_count = 0, entry_no = 0;
    U32 u32LogicBlockAddress;
    EN_FILE_SYSTEM_TYPE fsType=FILE_SYSTEM_TYPE_FAT;
    EN_DRIVE_INITIAL_STATUS initialStatus=DRIVE_INITIAL_STATUS_ERROR;
    U8 partition_status = 0x80;     //0x80:active; 0x00:inactive
    U8 GPTpartitionNo = 0;
    legacy_mbr *mbr_p = (legacy_mbr *) mbr;
    if(!mbr_p || (msAPI_is_pmbr_valid(mbr_p) != 1))
        return 0;
    /* This function validates AND fills in the GPT header and PTE */
    if (msAPI_is_gpt_valid(deviceIndex, pgpt_pte, (unsigned long long)GPT_PRIMARY_PARTITION_TABLE_LBA,
            &(gpt_head)) != 1) {
        FCTRL_DBG(1,printf("%s: *** ERROR: Invalid GPT ***\n", __FUNCTION__););
        return 0;
    }

    for (i = 0; i < (U32)le32_to_U32(gpt_head.num_partition_entries); i++) {
        if(i && (i == block_count*4)){
            /* Read GPT Entries from device */
            if(!msAPI_MSDCtrl_SectorRead(deviceIndex, (U32)le64_to_U64(gpt_head.partition_entry_lba) + block_count,
                    1, USB_IO_TEMP_ADDR))
            {
                FCTRL_DBG(1,printf("GPT: Failed to allocate memory for PTE no:%d\n", block_count*4););
                free(*pgpt_pte);
                return 0;
            }
            msAPI_FS_MIU_Copy(USB_IO_TEMP_ADDR, GET_DRAM_ADDR(*pgpt_pte), 512);
        }
        entry_no = i % 4;   // 0~3

        if (msAPI_is_pte_valid(&(*pgpt_pte)[entry_no])) {
            FCTRL_DBG(1,printf("%s%d  0x%llX    0x%llX\n", GPT_ENTRY_NAME,
                        (i + 1), le64_to_U64((*pgpt_pte)[entry_no].starting_lba),
                        le64_to_U64((*pgpt_pte)[entry_no].ending_lba)););
            u32LogicBlockAddress = (U32)le64_to_U64((*pgpt_pte)[entry_no].starting_lba);
            initialStatus=msAPI_FCtrl_MountDrive(deviceIndex,fsType, &partition_status,u32LogicBlockAddress,GPTpartitionNo, 0, 0);
            if(initialStatus==DRIVE_INITIAL_STATUS_ERROR)
            {
                //In GPT, the MBR's fstype bytes is stand for EFI type.
                //So we only can do is trying the fs type when mounting.
                if(fsType==FILE_SYSTEM_TYPE_FAT)
                {
                    fsType = FILE_SYSTEM_TYPE_N51FS;
                    initialStatus=msAPI_FCtrl_MountDrive(deviceIndex,fsType,&partition_status,u32LogicBlockAddress,GPTpartitionNo, 0, 0);
                }
                else if(fsType==FILE_SYSTEM_TYPE_N51FS)
                {
                    fsType = FILE_SYSTEM_TYPE_FAT;
                    initialStatus=msAPI_FCtrl_MountDrive(deviceIndex,fsType,&partition_status,u32LogicBlockAddress,GPTpartitionNo, 0, 0);
                }
            }
            if(initialStatus==DRIVE_INITIAL_STATUS_ERROR)
            {
                FCTRL_DBG(1,printf("   Initial Partition Failed on DeviceID %bu at Partition %bu\n",deviceIndex,GPTpartitionNo););
                continue;
            }
            else if(initialStatus==DRIVE_INITIAL_STATUS_SUCCESS)
            {
                FCTRL_DBG(1,printf("    Initial Partition Success on DeviceID %bu at Partition %bu\n",deviceIndex,GPTpartitionNo););
                FS_SETBIT(*PartitionStatus,GPTpartitionNo);
            }
            else if(initialStatus==DRIVE_INITIAL_STATUS_MOUNTED_ALREADY)
            {
                FCTRL_DBG(1,printf("    Partition %bu on DeviceID %bu Already Initialized\n",GPTpartitionNo,deviceIndex););
                FS_SETBIT(*PartitionStatus,GPTpartitionNo);
            }
            else if(initialStatus==DRIVE_INITIAL_STATUS_NO_SLOT)
            {
                FCTRL_DBG(1,printf("    No Slot!!\n"););
            }
            GPTpartitionNo++;
        } else {
            break;	/* Stop at the first non valid PTE */
        }
        block_count = i / 4 + 1;    // 1block=512bytes has 4 entrys=4*128bytes
    }
    /* Remember to free pte */
    if (*pgpt_pte != NULL) {
        //printf("%s: Freeing pgpt_pte\n", __FUNCTION__);
        free(*pgpt_pte);
    }

    return GPTpartitionNo;
}

//The highest 8 bits mean of the return means how many paritions are founded on this device.
//The remain 24 bits mean whether the parition is loaded succesfully. Start from the lowest bit.
//ex: 0x04000002 means there are 4 paritions found on this device but only the 2nd (index=1) is loaded successfully.
U32 msAPI_FCtrl_LoadPartitionsOnDevice(U8 deviceIndex)
{
    U8 i=0;
    U8 partitionNo=0;
    U32 PartitionStatus=0;//first 8 bits represents partition counts.
                          //remains 24 bits, every bit represents the status of partition
    U32 u32Temp;
    U8 mbrBytes[512];

    EN_DRIVE_INITIAL_STATUS initialStatus=DRIVE_INITIAL_STATUS_ERROR;

    memset(mbrBytes,0xFF,512);
    if(!msAPI_MSDCtrl_SectorRead(deviceIndex, 0, 1, USB_IO_TEMP_ADDR))
    {
        return 0;
    }

    msAPI_FS_MIU_Copy(USB_IO_TEMP_ADDR, GET_DRAM_ADDR(&mbrBytes[0]), sizeof(mbrBytes));

    // We should check GPT before MBR
    partitionNo = msAPI_FCtrl_LoadGPT(deviceIndex, mbrBytes, &PartitionStatus);
    if(!partitionNo)
    {
        /***********check MBR firstly***********************/

        for(i=0;i<4;i++)//primary
        {
            EN_FILE_SYSTEM_TYPE fsType=FILE_SYSTEM_TYPE_NONE;
            U8* partitionBytes=&mbrBytes[PARTITION_TABLE0_BYTE_OFFSET+16*i];

            U32 u32LogicBlockAddress, u32LogicBlockAddress1;      //LBA
            U32 u32LengthOfPartition, u32LengthOfPartition1;

            //u32LogicBlockAddress=(*((U32*)&partitionBytes[8]));     //Eric won't use
            //u32LengthOfPartition=(*((U32*)&partitionBytes[12]));     //Eric won't use
            memcpy(&u32LogicBlockAddress,&partitionBytes[8],4);
            memcpy(&u32LengthOfPartition,&partitionBytes[12],4);

            //partitionBytes[4] : partitionType
            if(partitionBytes[4]==0 || u32LengthOfPartition== 0) //unused partition
            {
                continue;
            }

            if(partitionBytes[4]!=0x05&&partitionBytes[4]!=0x0F)
            {

                if(partitionBytes[4]==0x07)
                {
                    fsType=FILE_SYSTEM_TYPE_N51FS;
                }
                #if 0
                // original solution
                else if(partitionBytes[4]==0x01||partitionBytes[4]==0x04||partitionBytes[4]==0x06||partitionBytes[4]==0x0B||partitionBytes[4]==0x0C||partitionBytes[4]==0x0E||partitionBytes[4]==0x1C)
                {
                    fsType=FILE_SYSTEM_TYPE_FAT;
                }
                else
                {
                    FCTRL_DBG(1,printf("UnSupport SystemId=0x%02bx at %bu\n",partitionBytes[4],i););
                    fsType=FILE_SYSTEM_TYPE_NONE;
                    continue;
                }
                #else
                // In windows/linux, they don't use this byte to check if partition type is valid.
                // In linux&supernova, they allow user to retry mounting file system type
                // This modification can help mount succcessfully even this byte is random number.
                else if(partitionBytes[4]==0x01||partitionBytes[4]==0x04||partitionBytes[4]==0x06||partitionBytes[4]==0x0B||partitionBytes[4]==0x0C||partitionBytes[4]==0x0E||partitionBytes[4]==0x1C)
                {
                    fsType=FILE_SYSTEM_TYPE_FAT;
                }
                else
                {
                    FCTRL_DBG(1,printf("UnSupport SystemId=0x%02bx at %bu\n",partitionBytes[4],i););
                    fsType=FILE_SYSTEM_TYPE_FAT;
                }
                #endif

                initialStatus=msAPI_FCtrl_MountDrive(deviceIndex,fsType,partitionBytes,u32LogicBlockAddress,partitionNo, 0, i);
                if(initialStatus==DRIVE_INITIAL_STATUS_ERROR)
                {
                      if(fsType==FILE_SYSTEM_TYPE_FAT)
                      {
                               fsType = FILE_SYSTEM_TYPE_N51FS;

                               initialStatus=msAPI_FCtrl_MountDrive(deviceIndex,fsType,partitionBytes,u32LogicBlockAddress,partitionNo, 0, i);
                      }
                      else if(fsType==FILE_SYSTEM_TYPE_N51FS)
                      {
                              fsType = FILE_SYSTEM_TYPE_FAT;
                              initialStatus=msAPI_FCtrl_MountDrive(deviceIndex,fsType,partitionBytes,u32LogicBlockAddress,partitionNo, 0, i);
                      }
                 }
                if(initialStatus==DRIVE_INITIAL_STATUS_ERROR)
                {
                    FCTRL_DBG(1,printf("   Initial Partition Failed on DeviceID %bu at Partition %bu\n",deviceIndex,partitionNo););
                    continue;
                }
                else if(initialStatus==DRIVE_INITIAL_STATUS_SUCCESS)
                {
                    FCTRL_DBG(1,printf("    Initial Partition Success on DeviceID %bu at Partition %bu\n",deviceIndex,partitionNo););
                    FS_SETBIT(PartitionStatus,partitionNo);
                }
                else if(initialStatus==DRIVE_INITIAL_STATUS_MOUNTED_ALREADY)
                {
                    FCTRL_DBG(1,printf("    Partition %bu on DeviceID %bu Already Initialized\n",partitionNo,deviceIndex););
                    FS_SETBIT(PartitionStatus,partitionNo);
                }
                else if(initialStatus==DRIVE_INITIAL_STATUS_NO_SLOT)
                {
                    FCTRL_DBG(1,printf("    No Slot!!\n"););
                }
                partitionNo++;

            }
            else
            {
                //U32 extendStartSector=(*((U32*)&partitionBytes[8]));
                U32 u32PartitionBaseAddress = u32LogicBlockAddress;
                //U32 logicalStartSector=extendStartSector;
                U8* ebrBytes=(U8*)msAPI_FS_Memory_Allocate(512);
                U8 guard=0;

                if(ebrBytes==NULL)
                {
                    __ASSERT(0);
                    return PartitionStatus;
                }

                for(guard=0;guard<DISK_DRIVE_NUM;guard++)//logical drives
                {
                    if(!msAPI_MSDCtrl_SectorRead(deviceIndex, u32PartitionBaseAddress, 1, USB_IO_TEMP_ADDR)) //WBT Return value of "msAPI_MSDCtrl_SectorRead" is not checked
                    {
                        __ASSERT(0);
                        msAPI_FS_Memory_Free(ebrBytes);
                        return 0;
                    }
                    msAPI_FS_MIU_Copy(USB_IO_TEMP_ADDR, GET_DRAM_ADDR(&ebrBytes[0]), 512);

                    partitionBytes=&ebrBytes[PARTITION_TABLE0_BYTE_OFFSET];
                    if(partitionBytes[2]==0)
                        break;//finish the logical partition parse

                    //u32LogicBlockAddress1=(*((U32*)&partitionBytes[8]));  //Eric won't use
                    //u32LengthOfPartition1=(*((U32*)&partitionBytes[12]));  //Eric won't use
                    memcpy(&u32LogicBlockAddress1,&partitionBytes[8],4);
                    memcpy(&u32LengthOfPartition1,&partitionBytes[12],4);

                    if(partitionBytes[4]==0x07)
                    {
                        fsType=FILE_SYSTEM_TYPE_N51FS;
                    }
                    else if(partitionBytes[4]==0x01||partitionBytes[4]==0x04||partitionBytes[4]==0x06||partitionBytes[4]==0x0B||partitionBytes[4]==0x0C||partitionBytes[4]==0x0E || partitionBytes[4]==0x1C)
                    {
                        fsType=FILE_SYSTEM_TYPE_FAT;
                    }
                    else if(partitionBytes[4]==0x05 || partitionBytes[4]==0x0f) //Extended Partition
                    {
                        u32PartitionBaseAddress = u32LogicBlockAddress+u32LogicBlockAddress1;
                        continue;
                    }
                    else
                    {
                        fsType=FILE_SYSTEM_TYPE_NONE;
                    }

                    initialStatus=msAPI_FCtrl_MountDrive(deviceIndex,fsType,partitionBytes,u32PartitionBaseAddress+u32LogicBlockAddress1,partitionNo, u32PartitionBaseAddress, 0);
                    if(initialStatus==DRIVE_INITIAL_STATUS_ERROR)
                     {
                         if(fsType==FILE_SYSTEM_TYPE_FAT)
                         {
                               fsType = FILE_SYSTEM_TYPE_N51FS;

                               initialStatus=msAPI_FCtrl_MountDrive(deviceIndex,fsType,partitionBytes,u32PartitionBaseAddress+u32LogicBlockAddress1,partitionNo, u32PartitionBaseAddress, 0);
                        }
                        else if(fsType==FILE_SYSTEM_TYPE_N51FS)
                        {
                              fsType = FILE_SYSTEM_TYPE_FAT;
                              initialStatus=msAPI_FCtrl_MountDrive(deviceIndex,fsType,partitionBytes,u32PartitionBaseAddress+u32LogicBlockAddress1,partitionNo, u32PartitionBaseAddress, 0);
                        }
                     }
                    if(initialStatus==DRIVE_INITIAL_STATUS_NO_SLOT)
                    {
                        //msAPI_FS_Memory_Free(ebrBytes);
                        FCTRL_DBG(1,printf("    No Slot!!\n"););
                    }
                    else if(initialStatus==DRIVE_INITIAL_STATUS_ERROR)
                    {
                        FCTRL_DBG(1,printf("   Initial Partition Failed on DeviceID %bu at Partition %bu\n",deviceIndex,partitionNo););
                    }
                    else if(initialStatus==DRIVE_INITIAL_STATUS_SUCCESS)
                    {
                        FCTRL_DBG(1,printf("    Initial Partition Success on DeviceID %bu at Partition %bu\n",deviceIndex,partitionNo););
                        FS_SETBIT(PartitionStatus,partitionNo);
                    }
                    else if(initialStatus==DRIVE_INITIAL_STATUS_MOUNTED_ALREADY)
                    {
                        FCTRL_DBG(1,printf("    Partition %bu on DeviceID %bu Already Initialized\n",partitionNo,deviceIndex););
                        FS_SETBIT(PartitionStatus,partitionNo);
                    }
                    partitionNo++;
                    /*move to 2nd entry*/
                    partitionBytes=partitionBytes+16;
                    if(partitionBytes[2]!=0)
                    {
                        //u32PartitionBaseAddress=u32LogicBlockAddress+(*((U32*)&partitionBytes[8]));  //Eric won't use
                        memcpy(&u32Temp,&partitionBytes[8],4);
                        u32PartitionBaseAddress=u32LogicBlockAddress+u32Temp;
                    }
                    else//logical drives finish!!
                    {
                        break;
                    }
                }
                msAPI_FS_Memory_Free(ebrBytes);
                continue;
            }
        }
    }//For MBR without / with


    if(partitionNo==0 && (mbrBytes[0]==0xEB||mbrBytes[0]==0xE9))//single partition, no MBR
    {
        EN_FILE_SYSTEM_TYPE fsType=FILE_SYSTEM_TYPE_NONE;

        if(mbrBytes[3]=='N'&&mbrBytes[4]=='T'&&mbrBytes[5]=='F'&&mbrBytes[6]=='S')
        {
            fsType=FILE_SYSTEM_TYPE_N51FS;
        }
        else if(mbrBytes[3]=='M'&&mbrBytes[4]=='S'&&mbrBytes[5]=='D'&&mbrBytes[6]=='O')
        {
            fsType=FILE_SYSTEM_TYPE_FAT;
        }
        else if(mbrBytes[3]=='M'&&mbrBytes[4]=='S'&&mbrBytes[5]=='W'&&mbrBytes[6]=='I')
        {
            fsType=FILE_SYSTEM_TYPE_FAT;
        }
        else if(mbrBytes[3]=='m'&&mbrBytes[4]=='k'&&mbrBytes[5]=='d'&&mbrBytes[6]=='o')
        {
           fsType=FILE_SYSTEM_TYPE_FAT;
        }
        else if(mbrBytes[54]=='F'&&mbrBytes[55]=='A'&&mbrBytes[56]=='T')
        {
           fsType=FILE_SYSTEM_TYPE_FAT;
        }
        else if(mbrBytes[82]=='F'&&mbrBytes[83]=='A'&&mbrBytes[84]=='T')
        {
           fsType=FILE_SYSTEM_TYPE_FAT;
        }
        else
        {
            fsType=FILE_SYSTEM_TYPE_NONE;
            FCTRL_DBG(1,printf("    Unsupport FileSystemType on DeviceID %bu at Partition %bu\n",deviceIndex,partitionNo););
            goto RET_PARTITION_STATUS;
        }

        initialStatus=msAPI_FCtrl_MountDrive(deviceIndex,fsType,NULL,0,partitionNo, INVALID_MBR_ADDRESS, INVALID_MBR_INDEX);

        if(initialStatus==DRIVE_INITIAL_STATUS_ERROR)
        {
            FCTRL_DBG(1,printf("    Initial Partition Failed on DeviceID %bu at Partition %bu\n",deviceIndex,partitionNo););
        }
        else if(initialStatus==DRIVE_INITIAL_STATUS_NO_SLOT)
        {
            FCTRL_DBG(1,printf("    No Slot!!\n"););
        }
        else if(initialStatus==DRIVE_INITIAL_STATUS_SUCCESS)
        {
            FCTRL_DBG(1,printf("    Initial Partition Success on DeviceID %bu at Partition %bu\n",deviceIndex,partitionNo););
            FS_SETBIT(PartitionStatus,partitionNo);
        }
        else if(initialStatus==DRIVE_INITIAL_STATUS_MOUNTED_ALREADY)
        {
            FCTRL_DBG(1,printf("    Partition %bu on DeviceID %bu Already Initialized \n",partitionNo,deviceIndex););
            FS_SETBIT(PartitionStatus,partitionNo);
        }
        partitionNo++;
        FCtrl_addPartitionCount(partitionNo, &PartitionStatus);
        return PartitionStatus;

    }

RET_PARTITION_STATUS:
    FCtrl_addPartitionCount(partitionNo, &PartitionStatus);
    return PartitionStatus;
}

BOOLEAN msAPI_FCtrl_ActiveDevice(U8 deviceIndex)
{
    U32 PartitionStatus = 0;
    U8 PartitionCount = 0;
    U8 i=0;
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START(););

    //printf("msAPI_FCtrl_ActiveDevice(deviceIndex=%u)\n", deviceIndex);

    PartitionStatus = msAPI_FCtrl_LoadPartitionsOnDevice(deviceIndex);
    PartitionCount = (PartitionStatus >> 24) & 0xFF;
    FCTRL_DBG(1, printf("PartitionStatus = %lu\n",PartitionStatus););
    FCTRL_DBG(1, printf("PartitionCount  = %bd\n",PartitionCount););

    if(PartitionStatus==0)
    {
        msAPI_MSDCtrl_SetDeviceStatus(deviceIndex,MSD_STATUS_ERROR);
        DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END(););
        return FALSE;
    }
    for(i=0;i<PartitionCount;i++)
    {
        BOOLEAN check;
        check = (BOOLEAN)FS_GETBIT(PartitionStatus,i);
        if(check==1)
        {
            msAPI_MSDCtrl_SetDeviceStatus(deviceIndex,MSD_STATUS_IDLE);
            DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END(););
            return TRUE;
        }
    }

    msAPI_MSDCtrl_SetDeviceStatus(deviceIndex,MSD_STATUS_ERROR);

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END(););

    return FALSE;
}

#ifdef ENABLE_PTP
BOOLEAN msAPI_FCtrl_ActivePTPDevice(U8 deviceIndex)
{
    // Assume one partition.
    msAPI_FCtrl_MountPTPDrive(deviceIndex,FILE_SYSTEM_TYPE_NONE,NULL,0,0);
    msAPI_MSDCtrl_SetDeviceStatus(deviceIndex,MSD_STATUS_IDLE);
    return TRUE;
}
#endif

#if (FILE_SYSTEM_ENABLE_START_DEVICE)
U32 msAPI_FCtrl_StartDevice(U8 deviceIndex)
{
    FCTRL_DBG(1, printf(" deviceStatus=%bu before start...\n",msAPI_MSDCtrl_GetDeviceStatus(deviceIndex)););
    if(msAPI_MSDCtrl_GetDeviceStatus(deviceIndex)==MSD_STATUS_IDLE)
    {
        return DEVICE_START_STATUS_STARTED_ALREADY;
    }
    else if(msAPI_MSDCtrl_GetDeviceStatus(deviceIndex)==MSD_STATUS_ERROR)
    {
        return DEVICE_START_STATUS_ERROR;
    }

    if(msAPI_FCtrl_ActiveDevice(deviceIndex))
    {
        msAPI_MSDCtrl_SetDeviceStatus(deviceIndex,MSD_STATUS_IDLE);
        return DEVICE_START_STATUS_SUCCESS;
    }
    else
    {
        msAPI_MSDCtrl_SetDeviceStatus(deviceIndex,MSD_STATUS_ERROR);
        return DEVICE_START_STATUS_ERROR;
    }
}
#endif

BOOLEAN msAPI_FCtrl_FileSystemGetByID(U8 u8FileSysID, void *pFStruct)
{

    //U8 buff[FILE_SYS_STRUCT_SIZE];
    U8 *pBuffer;
    U32* fsptr;
    U8 fsType;

    if(u8FileSysID>=DISK_DRIVE_NUM)
    {
        return FALSE;
    }

    pBuffer = msAPI_FS_Memory_Allocate(FILE_SYS_STRUCT_SIZE);

    if(pBuffer == NULL)
    {
        __ASSERT(0);
        return FALSE;
    }

    fsptr=FCtrl_GetFileSystemInfo(u8FileSysID);

    memcpy(pBuffer, fsptr, FILE_SYS_STRUCT_SIZE);
    fsType=((N51FS_FileSysStruct*)fsptr)->FileSystemType;

    if(fsType==(U8)FILE_SYSTEM_TYPE_FAT)
    {
        memcpy((U8*)pFStruct, pBuffer, sizeof(FAT_FileSysStruct));
    }
    else if(fsType==(U8)FILE_SYSTEM_TYPE_N51FS)
    {
        memcpy((U8*)pFStruct, pBuffer, sizeof(N51FS_FileSysStruct));

    }
    else
    {
       __ASSERT(0);
        msAPI_FS_Memory_Free(pBuffer);
       return FALSE;
    }
    msAPI_FS_Memory_Free(pBuffer);
    return TRUE;
}




/***************************************************************************************/

/*###############################################################################################*/
/*////////////////////////////// file control -> file handle api ////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
/// Check if the given file name is opened or not at given drive number.
/// @param -u8DriveNo \b IN: Drive number (from A to Z)
/// @param -ps8FileName \b IN: File name.
/// @return -1: opened, 0: not opened yet.
/***************************************************************************************/


/***************************************************************************************/
/// Create a file handle for the given file system, drive number, file name, and open mode.
/// @param -pstFileSys \b IN: File system structure.
/// @param -u8DriveNo \b IN: Drive number (from A to Z)
/// @param -ps8FileName \b IN: File name.
/// @param -u8OpenMode \b msAPI_FCtrl_FileHandleCreateIN: Open mode, see the definition.
/// @return -File handle number.
/***************************************************************************************/
U8 msAPI_FCtrl_FileHandleCreate(void* pFileSys, FileEntry* pFileEntry, U8 u8OpenMode)
{

    U8 u8HandleNo;
    U8 handleID=INVALID_FILE_HANDLE;
    FileHandleStruct xdata * _pstFileHandle;

    for(u8HandleNo = 0; u8HandleNo < FS_FILE_HANDLE_NUM; u8HandleNo++)
    {
        handleID=INVALID_FILE_HANDLE;

        _pstFileHandle = FCtrl_GetFileHandleInfo(u8HandleNo);

        handleID=_pstFileHandle->HandleID;

        if(handleID==INVALID_FILE_HANDLE)
        {
            U8 fsType=*((U8*)pFileSys+1);
            handleID=u8HandleNo;

            //set the common file handle
            _pstFileHandle->HandleID=handleID;
            _pstFileHandle->FileSystemID = pFileEntry->FileSystemID;
            _pstFileHandle->OpenMode=u8OpenMode;

            if(fsType==(U8)FILE_SYSTEM_TYPE_FAT)
            {
                FAT_HandlePostCreate(handleID, pFileEntry, u8OpenMode);
                FCTRL_DBG(0,printf("create HandleID=0x%02bx for FileSystemType=%bu\n", u8HandleNo, fsType););
                return handleID;
            }
            else if(fsType==(U8)FILE_SYSTEM_TYPE_N51FS)
            {
            #if ENABLE_N51FS
                N51FS_HandlePostCreate(handleID, pFileEntry->FileSystemID,pFileEntry->FileLength.Hi,pFileEntry->FileLength.Lo,u8OpenMode);
                FCTRL_DBG(0,printf("create HandleID=0x%02bx for FileSystemType=%bu\n", u8HandleNo, fsType););
                return handleID;

            #else
                __ASSERT(0);
                return INVALID_FILE_HANDLE;
            #endif
            }
            else
            {
                __ASSERT(0);//unknown type
                return INVALID_FILE_HANDLE;
            }
        }
    }


    __ASSERT(0);// unable to find available handle;
    return INVALID_FILE_HANDLE;

}

/***************************************************************************************/
/// Free a file handle.
/// @param -u8HandleNo \b IN: File handle number.
/***************************************************************************************/
void msAPI_FCtrl_FileHandleFree(U8 u8HandleNo)
{
    FileHandleStruct xdata * _pstFileHandle;
    FileInodeStruct   xdata *pFileInode;
    U8 u8InodeId;

    _pstFileHandle = FCtrl_GetFileHandleInfo(u8HandleNo);
    _pstFileHandle->HandleID=INVALID_FILE_HANDLE;
    _pstFileHandle->FileSystemID=0xFF;
    _pstFileHandle->OpenMode=OPEN_MODE_NONE;
    u8InodeId = _pstFileHandle->InodeID;
    _pstFileHandle->InodeID = INVALID_FILE_INODEID;

  #if 0
    //_pstFileHandle[u8HandleNo].pstFileSys        = NULL;                                //<---(1)file sys
    _pstFileHandle[u8HandleNo].u8FileDrive        = FCTRL_INVALID_DRIVE;                //<---(2)file drive
    strcpy(_pstFileHandle[u8HandleNo].ps8FileName, "\0");                            //<---(3)file name
    _pstFileHandle[u8HandleNo].u8FileAttrib        = 0;                                //<---(4)file attribute
    _pstFileHandle[u8HandleNo].OpenMode=OPEN_MODE_NONE;
  #endif

    if(u8InodeId != INVALID_FILE_INODEID)
    {
        // printf("msAPI_FCtrl_FileHandleFree-->inode %02b of %02b\n", u8InodeID, u8HandleNo);
        pFileInode = FCtrl_GetFileInodeInfo(u8InodeId);
        __ASSERT(pFileInode->refCnt);
        if(--pFileInode->refCnt == 0)
            pFileInode->InodeID = INVALID_FILE_INODEID;

    }

    FCTRL_DBG(0,printf("Free u8HandleNo=0x%02bx\n",u8HandleNo););
}

/***************************************************************************************/
/// Change directory to the given directory name.
/// @param -ps8DirName \b IN: Directory name.
/// @return -Success or fail.
/***************************************************************************************/
BOOLEAN msAPI_FCtrl_DirectoryChange(U8 enId,FileEntry* pFileEntry)
{
    U8 fsType;
    U32 u32Temp;
    FS_EnvironmentStruct* pFSEnv;
    if(pFileEntry==NULL || pFileEntry->EnvironmentID==0xFF||pFileEntry->EntryType==ENTRY_TYPE_FILE)
    {
        __ASSERT(0);
        return FALSE;
    }

    if(pFileEntry->EntryType==ENTRY_TYPE_DIR_DOT)
    {
        return TRUE;
    }

    pFSEnv = msAPI_FSEnv_GetEnvironment(enId);
    if(pFSEnv == NULL)
    {
        __ASSERT(0);
        return FALSE;
    }
    else
    {
        fsType=pFSEnv->u8FileSystemType;
    }

    FCTRL_DBG(0,printf("enid=%bu, fsType=%bu\n",enId,fsType););

    if(fsType==(U8)FILE_SYSTEM_TYPE_FAT)
    {
        memcpy(&u32Temp,pFileEntry->EntryID,4);
        //return FAT_DirectoryChange(enId, *((U32*)pFileEntry->EntryID));
        return FAT_DirectoryChange(enId, u32Temp);
    }
    else if(fsType==(U8)FILE_SYSTEM_TYPE_N51FS)
    {
        #if ENABLE_N51FS
        memcpy(&u32Temp,pFileEntry->EntryID,4);
        //return N51FS_DirectoryChange(enId, *((U32*)pFileEntry->EntryID));
        return N51FS_DirectoryChange(enId, u32Temp);
        #else
        __ASSERT(0);
        return FALSE;
        #endif
    }
    else
    {
        __ASSERT(0);
        return FALSE;
    }
}

/***************************************************************************************/
/// Change directory to the given file name.
/// @param -ps8DirName \b IN: File name.
/// @return -Success or fail.
/***************************************************************************************/
#if FILE_SYSTEM_ENABLE_FCTRL_DIRECTORY_CHANGE_TO_CONTAINED
BOOLEAN msAPI_FCtrl_DirectoryChangeToContained(U8 enId,FileEntry* pFileEntry)
{
    U8 fsType;
    U32 u32Temp;
    if(pFileEntry==NULL || pFileEntry->EnvironmentID==0xFF||pFileEntry->EntryType!=ENTRY_TYPE_FILE)
    {
        __ASSERT(0);
        return FALSE;
    }

    fsType=msAPI_FSEnv_GetEnvironment(enId)->u8FileSystemType;
    FCTRL_DBG(0,printf("enid=%bu, fsType=%bu\n",enId,fsType););

    if(fsType==(U8)FILE_SYSTEM_TYPE_FAT)
    {
        memcpy(&u32Temp,pFileEntry->EntryID_Ext,4);
        return FAT_DirectoryChange(enId, u32Temp);
    }
    else if(fsType==(U8)FILE_SYSTEM_TYPE_N51FS)
    {
        #if ENABLE_N51FS
        memcpy(&u32Temp,pFileEntry->EntryID_Ext,4);
        return N51FS_DirectoryChange(enId, u32Temp);
        #else
        __ASSERT(0);
        return FALSE;
        #endif
    }
    else
    {
        __ASSERT(0);
        return FALSE;
    }
}
#endif

/***************************************************************************************/
/// Open file by the given file name and open mode.
/// @param -ps8FileName \b IN: File name.
/// @param -u8OpenMode \b IN: Open mode, see the definition.
/// @return -File handle number.
/***************************************************************************************/
U8 msAPI_FCtrl_FileOpen(const FileEntry* pFileEntry, U8 u8OpenMode)
{
    FAT_FileSysStruct stFAT_FileSys;
    FileEntry tmpEntry;
    BOOLEAN fastOpen=FALSE;

    FFLOW_CHECK(printf("\n>>>> FILE OPEN!! ID=0x%08lx\n",*((U32*)pFileEntry->EntryID)););

    if(u8OpenMode==(U8)OPEN_MODE_FAST_FOR_READ)
    {
        u8OpenMode=OPEN_MODE_FOR_READ;
        fastOpen=TRUE;
    }


    if(pFileEntry==NULL || pFileEntry->EntryType!=ENTRY_TYPE_FILE)
    {
        __ASSERT(0);
        return INVALID_FILE_HANDLE;
    }

    if ( !msAPI_FCtrl_FileSystemGetByID(pFileEntry->FileSystemID, &stFAT_FileSys) )
    {
          FCTRL_DBG(0,printf("Get FileSystem Failed. FileSystemID=%bu\n",pFileEntry->FileSystemID););
          return INVALID_FILE_HANDLE;
    }

    memcpy(&tmpEntry,pFileEntry,sizeof(FileEntry));

    FFLOW_CHECK(printf("    fsType=%bu\n",(U8)stFAT_FileSys.FileSystemType););

    if(stFAT_FileSys.FileSystemType == FILE_SYSTEM_TYPE_FAT)
    {
        U8 u8FileHandleID;


        u8FileHandleID = msAPI_FCtrl_FileHandleCreate(&stFAT_FileSys,&tmpEntry,u8OpenMode);

        if ( u8FileHandleID != INVALID_FILE_HANDLE )
        {
            if ( FAT_FileOpen(u8FileHandleID, &tmpEntry,fastOpen) )
            {
                 //FileHandleStruct* phandle;
                 //phandle=FCtrl_GetFileHandleInfo();
                 //phandle[u8FileHandleID].stFileEntry=tmpEntry;
                 FFLOW_CHECK(printf("    SUCCESS!! fileHandle=%bu\n",u8FileHandleID););
                 return u8FileHandleID;
            }
            else
            {
                  FCTRL_DBG(0,printf("Open Failed\n"););
                  msAPI_FCtrl_FileHandleFree(u8FileHandleID);
                  return INVALID_FILE_HANDLE;
            }
        }
        else
        {
            __ASSERT(0);
        }

    }
    else if(stFAT_FileSys.FileSystemType == FILE_SYSTEM_TYPE_N51FS)
    {
        #if ENABLE_N51FS
        U8 handleId;
        N51FS_FileSysStruct N51FS_fs;

        //U32 mfr = *((U32*)pFileEntry->EntryID);
        U32 mfr;
        memcpy(&mfr,pFileEntry->EntryID,4);

        memcpy((U8*)&N51FS_fs, (U8*)&stFAT_FileSys, sizeof(N51FS_FileSysStruct));

        handleId=msAPI_FCtrl_FileHandleCreate(&N51FS_fs,&tmpEntry,u8OpenMode);

        if(handleId!=INVALID_FILE_HANDLE)
        {

            if(N51FS_FileOpen(handleId, mfr))
            {
               // FileHandleStruct* phandle;
                //FCTRL_DBG(0,printf("name=%s,opening mfr=0x%08lx\n",pFileEntry->EntryLongName,mfr););
              //  phandle=FCtrl_GetFileHandleInfo();

              //  phandle[handleId].stFileEntry=tmpEntry;
                FFLOW_CHECK(printf("    SUCCESS!! fileHandle=%bu\n",handleId););
                return handleId;
            }

            __ASSERT(0);
            msAPI_FCtrl_FileHandleFree(handleId);

        }
        #else
        __ASSERT(0);
        #endif
        return INVALID_FILE_HANDLE;
    }


    //printf("unable to open file with FileSystemType=0x%02bx\n",pEnv->u8FileSystemType);
    return INVALID_FILE_HANDLE;
}

/***************************************************************************************/
/// Close file by the given file handle number.
/// @param -u8HandleNo \b IN: File handle number.
/// @return -Success or fail.
/***************************************************************************************/
EN_FILE_CLOSE_RESULT msAPI_FCtrl_FileClose(U8 u8HandleNo)
{

    FileHandleStruct handle;
    U8 fsType;
    FAT_FileSysStruct * pFAT_FileSys;
    EN_FILE_CLOSE_RESULT result=FILE_CLOSE_RESULT_ERROR;

    FFLOW_CHECK(printf("\n>>>> FILE CLOSE!! fileHandle=%bu\n",u8HandleNo););

    if(u8HandleNo==INVALID_FILE_HANDLE)
    {
        return FILE_CLOSE_RESULT_SUCCESS;
    }
    if(u8HandleNo>=FS_FILE_HANDLE_NUM)
    {
        __ASSERT(0);
        return FILE_CLOSE_RESULT_SUCCESS;
    }

    FCtrl_CopyFileHandleInfo(&handle, u8HandleNo);

    if(handle.OpenMode==OPEN_MODE_NONE)
    {
        return FILE_CLOSE_RESULT_SUCCESS;
    }

    pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemInfo(handle.FileSystemID);

    fsType = pFAT_FileSys->FileSystemType;
    if(fsType==(U8)FILE_SYSTEM_TYPE_FAT)
    {
        if(FAT_FileClose(u8HandleNo))
    {
            result=FILE_CLOSE_RESULT_SUCCESS;
        }
        else
        {
            result=FILE_CLOSE_RESULT_ERROR;
        }
    }

    else if(fsType==(U8)FILE_SYSTEM_TYPE_N51FS)
    {
        #if ENABLE_N51FS
        if(N51FS_FileClose(u8HandleNo))
        {
            result=FILE_CLOSE_RESULT_SUCCESS;
        }
        else
        {
            result=FILE_CLOSE_RESULT_ERROR;
        }
        #else
        __ASSERT(0);
        #endif
    }

    else
    {
        __ASSERT(0);
    }

    msAPI_FCtrl_FileHandleFree(u8HandleNo);

    return result;
}

/***************************************************************************************/
/// Read file by the given file handle number, read buffer, and read length.
/// @param -u8HandleNo \b IN: File handle number.
/// @param -pu8Buffer \b OUT: Read buffer.
/// @param -u32Length \b IN: Read length.
/// @return -Left bytes it is not able to read. If read successfully, should return 0.
/***************************************************************************************/
U32 msAPI_FCtrl_FileRead(U8 u8HandleNo, U32 u32Buffer, U32 u32Length)
{

    U8 fsType;
    FileHandleStruct* pHandle;
    FAT_FileSysStruct* pFAT_FileSys;
    U32 ret_val = 0;//hjkoh 080117 - Whitebox Test
    U8 u8fsid;
    U32 u32VABuffer;

    FFLOW_CHECK(printf("\n>>>> FILE READ!! fileHandle=%bu, length=%lu\n",u8HandleNo,u32Length););
    if(u8HandleNo==INVALID_FILE_HANDLE)
    {
        __ASSERT(0);
        return 0xFFFFFFFF;
    }

    u32VABuffer = _PA2VA(u32Buffer);

    FCTRL_DBG(0,printf("\n\nRead: handle=%bd,request_len=0x%08lx\n",u8HandleNo,u32Length););
    pHandle=FCtrl_GetFileHandleInfo(u8HandleNo);

    if(pHandle->HandleID==INVALID_FILE_HANDLE)
    {
      //you are now using one hande which has already been closed before
        __ASSERT(0);
        return 0xFFFFFFFF;
    }

    u8fsid = pHandle->FileSystemID;

    pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemInfo(u8fsid);

    fsType = pFAT_FileSys->FileSystemType;

    if(fsType==(U8)FILE_SYSTEM_TYPE_FAT)
    {
        ret_val = FAT_FileRead(u8HandleNo, u32VABuffer, u32Length);
    }
    else if(fsType==(U8)FILE_SYSTEM_TYPE_N51FS)
    {
      #if ENABLE_N51FS
        ret_val = N51FS_FileRead(u8HandleNo,u32VABuffer,u32Length);
      #else
        __ASSERT(0);
      #endif
    }
    else
    {
        __ASSERT(0);//unsuport type!!
        return 0xFFFFFFFF;
    }

    return ret_val;
}

/***************************************************************************************/
/// Read file by the given file handle number, "virtual" read buffer, and read length.
/// @param -u8HandleNo \b IN: File handle number.
/// @param -pu8Buffer \b OUT: Virtual read buffer.
/// @param -u32Length \b IN: Read length.
/// @return -Left bytes it is not able to read. If read successfully, should return 0.
/***************************************************************************************/
U32 msAPI_FCtrl_FileRead2(U8 u8HandleNo, U32 u32VABuffer, U32 u32Length)
{

    U8 fsType;
    FileHandleStruct* pHandle;
    FAT_FileSysStruct* pFAT_FileSys;
    U32 ret_val = 0;//hjkoh 080117 - Whitebox Test
    U8 u8fsid;
    //U32 u32VABuffer;

    FFLOW_CHECK(printf("\n>>>> FILE READ!! fileHandle=%bu, length=%lu\n",u8HandleNo,u32Length););
    if(u8HandleNo==INVALID_FILE_HANDLE)
    {
        __ASSERT(0);
        return 0xFFFFFFFF;
    }

    //u32VABuffer = _PA2VA(u32Buffer);

    FCTRL_DBG(0,printf("\n\nRead: handle=%bd,request_len=0x%08lx\n",u8HandleNo,u32Length););
    pHandle=FCtrl_GetFileHandleInfo(u8HandleNo);

    if(pHandle->HandleID==INVALID_FILE_HANDLE)
    {
        //you are now using one hande which has already been closed before
        __ASSERT(0);
        return 0xFFFFFFFF;
    }

    u8fsid = pHandle->FileSystemID;

    pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemInfo(u8fsid);

    fsType = pFAT_FileSys->FileSystemType;

    if(fsType==(U8)FILE_SYSTEM_TYPE_FAT)
    {
        ret_val = FAT_FileRead(u8HandleNo, u32VABuffer, u32Length);
    }
    else if(fsType==(U8)FILE_SYSTEM_TYPE_N51FS)
    {
      #if ENABLE_N51FS
        ret_val = N51FS_FileRead(u8HandleNo,u32VABuffer,u32Length);
      #else
        __ASSERT(0);
      #endif
    }
    else
    {
        __ASSERT(0);//unsuport type!!
        return 0xFFFFFFFF;
    }

    return ret_val;
}


/***************************************************************************************/
/// Seek file by the given file handle number to the given file position.
/// @param -u8HandleNo \b IN: File handle number.
/// @param -u32Position \b IN: File position.
/// @return -Success or fail.
/***************************************************************************************/
BOOLEAN msAPI_FCtrl_FileSeek(U8 u8HandleNo, U32 u32Length, EN_FILE_SEEK_OPTION option)
{
    U8 fsType;
    FileHandleStruct* pHandle;
    FAT_FileSysStruct * pFAT_FileSys;
    U8 u8fsid;

    FFLOW_CHECK(printf("\n>>>> FILE SEEK!! fileHandle=%bu,u32Length=0x%08lx,option=%bd\n",u8HandleNo,u32Length,option););


    if(u8HandleNo==INVALID_FILE_HANDLE)
        return FALSE;

    pHandle=FCtrl_GetFileHandleInfo(u8HandleNo);

    u8fsid = pHandle->FileSystemID;

    pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemInfo(u8fsid);

    fsType = pFAT_FileSys->FileSystemType;

    if(fsType == (U8)FILE_SYSTEM_TYPE_FAT)
    {
        BOOLEAN bResult = FALSE;
        bResult = FAT_FileSeek(u8HandleNo, u32Length, option);
        return bResult;
/*
        U32 u32SeekLength;
        BOOLEAN bResult = FALSE;
        u32SeekLength = (U32)s32Offset;

        if(option == FILE_SEEK_SET)
        {
            bResult = FAT_FileSeekBackward(u8HandleNo, u32SeekLength, FILE_SEEK_BACKWARD_FROM_START);

        }
        else if(option == FILE_SEEK_CUR)
        {
            if(s32Offset < 0)
            {
                __ASSERT(0);
                printf("current do not support seek back \n");
                bResult = FALSE;
                //bResult = FAT_FileSeekForward(u8HandleNo, u32SeekLength, FILE_SEEK_FORWARD_FROM_CURRENT);
            }
            else
                bResult = FAT_FileSeekBackward(u8HandleNo, u32SeekLength, FILE_SEEK_BACKWARD_FROM_CURRENT);
        }
        return bResult;
*/
    }
    else if(fsType == (U8)FILE_SYSTEM_TYPE_N51FS)
    {
        BOOLEAN bResult = FALSE;
        #if ENABLE_N51FS
        bResult = N51FS_FileSeek(u8HandleNo, u32Length, option);
        #else
        __ASSERT(0);
        #endif
        return bResult;
    }
    else
    {
        __ASSERT(0);
        return FALSE;
    }


}

/***************************************************************************************/
/// Get file position by the given file handle number
/// @param -u8HandleNo \b IN: File handle number.
/// @return -Current file position.
/***************************************************************************************/
#if FILE_SYSTEM_FILE_TELL_ENABLE
U32 msAPI_FCtrl_FileTell(U8 u8HandleNo)
{
    U32 u32FilePosition=0xFFFFFFFF;
    U8 fsType;
    FileHandleStruct xdata * _pstFileHandle;
    FAT_FileSysStruct* pFAT_FileSys;
    U8 u8fsid;

    FFLOW_CHECK(printf("\n>>>> FILE TELL!! fileHandle=%bu\n",u8HandleNo););
    if (u8HandleNo == INVALID_FILE_HANDLE)
    {
        return 0xFFFFFFFF;
    }

    _pstFileHandle = FCtrl_GetFileHandleInfo(u8HandleNo);

    u8fsid = _pstFileHandle->FileSystemID;

    if(u8fsid>=DISK_DRIVE_NUM)
    {
        __ASSERT(0);
        return 0xFFFFFFFF;
    }

    pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemInfo(u8fsid);

    fsType = pFAT_FileSys->FileSystemType;

    if(fsType==(U8)FILE_SYSTEM_TYPE_FAT)
    {
        u32FilePosition=FAT_FileTell(u8HandleNo);
    }
    else if(fsType==(U8)FILE_SYSTEM_TYPE_N51FS)
    {
#if ENABLE_N51FS
        u32FilePosition=N51FS_FileTell(u8HandleNo).Lo;
#else
        __ASSERT(0);
#endif
    }
    else
    {
        __ASSERT(0);
    }


    return u32FilePosition;
}
#endif

/***************************************************************************************/
/// Get the file length for the given file handle number.
/// @param -u8HandleNo \b IN: File handle number.
/// @return -Current File length.
/***************************************************************************************/
U32 msAPI_FCtrl_FileLength(U8 u8HandleNo)
{
    U32 u32FileTotalSize=0;
    U8 fsType;
    FileHandleStruct* pHandle;
    FAT_FileSysStruct* pFAT_FileSys;
    U8 u8fsid;

    if(u8HandleNo==INVALID_FILE_HANDLE)
    {
           return 0;
    }

    pHandle=FCtrl_GetFileHandleInfo(u8HandleNo);

    u8fsid = pHandle->FileSystemID;

    if(u8fsid>=DISK_DRIVE_NUM)
    {
        __ASSERT(0);
        return 0;
    }

    pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemInfo(u8fsid);

    fsType = pFAT_FileSys->FileSystemType;

    if(fsType==(U8)FILE_SYSTEM_TYPE_FAT)
    {
        FAT_FileInode *pstFAT_FileInode;

        pstFAT_FileInode = FAT_File_GetInodeFromHandle(u8HandleNo);
        if(pstFAT_FileInode == NULL)
        {
            __ASSERT(0);
            return 0;//File length = 0
        }
        else
        {
            u32FileTotalSize = pstFAT_FileInode->u32FileTotalSize;
        }
    }
    else if(fsType==(U8)FILE_SYSTEM_TYPE_N51FS)
    {
        #if ENABLE_N51FS
        u32FileTotalSize=N51FS_FileLength(u8HandleNo).Lo;
        #else
        __ASSERT(0);
        #endif

    }
    else
    {
        __ASSERT(0);
    }
    return u32FileTotalSize;
}


/***************************************************************************************/
/// Change the given environment ID's Current Directory to Root.
/// @param -environmentID \b IN: Environment ID.
/// @return -Success or fail.
/***************************************************************************************/
BOOLEAN msAPI_FCtrl_DirectoryChangeToRoot(U8 environmentID)
{
    FS_EnvironmentStruct* pFSEnv;
    pFSEnv=msAPI_FSEnv_GetEnvironment(environmentID);
    if(pFSEnv == NULL)
    {
        __ASSERT(0);
        return FALSE;
    }

    if(pFSEnv->u8FileSystemType==FILE_SYSTEM_TYPE_FAT)
    {
        FAT_FileSysStruct stFAT_fileSys;
        if ( !msAPI_FCtrl_FileSystemGetByID(pFSEnv->u8FileSystemID, &stFAT_fileSys) )
        {
            FCTRL_DBG(1, printf("get file system fail!\n"));
            __ASSERT(0);
            return FALSE;
        }
        return FAT_DirectoryChange( environmentID, stFAT_fileSys.u32RootDirStartClusterNo );

    }
    else if(pFSEnv->u8FileSystemType==FILE_SYSTEM_TYPE_N51FS)
    {
#if ENABLE_N51FS
        return N51FS_DirectoryChange(environmentID,N51FS_ROOT_MFR);
#else
        __ASSERT(0);
        return FALSE;
#endif
    }
    else
    {
        //printf("UnSupport File Type!!\n");
        return FALSE;
    }
}

/***************************************************************************************/
/// Reset All handle.
/***************************************************************************************/
void msAPI_FCtrl_FileHandleResetAll()
{
    FileHandleStruct* pHandle;
    FileInodeStruct*  pInode;
    U8 i=0;

    for(i=0; i < FS_FILE_HANDLE_NUM; i++)
    {
         pHandle= FCtrl_GetFileHandleInfo(i);
         pHandle->HandleID=INVALID_FILE_HANDLE;
         pHandle->InodeID=INVALID_FILE_INODEID;
         pHandle->FileSystemID=0xFF;
         pHandle->OpenMode=OPEN_MODE_NONE;
    }
    for(i=0; i < FS_FILE_HANDLE_NUM; i++)
    {
         pInode= FCtrl_GetFileInodeInfo(i);
         pInode->InodeID=INVALID_FILE_INODEID;
         pInode->FileSystemID=0xFF;
         pInode->refCnt=0;
    }
}


extern U8 FAT_EntryGetCurrentNameToMIU(U8 enid,U32 destMIUAddr,U8 charLen);

/***************************************************************************************/
/// Get current file name from entry and put it in given MIU address.
/// @param -enId \b IN: Environment ID.
/// @param -MIUAddr \b IN: MIU address.
/// @param -charLen \b IN: MIU address length.
/// @return -File name length.
/***************************************************************************************/
U8 msAPI_FCtrl_EntryGetCurrentName(U8 enId,U32 MIUAddr,U8 charLen)
{

    U8 fsType;
    U8 len=0;
    FS_EnvironmentStruct* pFS_Env;

    pFS_Env = msAPI_FSEnv_GetEnvironment(enId);
    if(pFS_Env == NULL)
    {
        __ASSERT(0);
        return 0;
    }
    else
    {
        fsType = pFS_Env->u8FileSystemType;
    }

    if(enId==INVALID_FILE_HANDLE)
    {
        __ASSERT(0);
        return 0;
    }

    if(fsType==FILE_SYSTEM_TYPE_FAT)
    {
        len=FAT_EntryGetCurrentNameToMIU(enId, MIUAddr, charLen);
    }
    else if(fsType==FILE_SYSTEM_TYPE_N51FS)
    {
#if ENABLE_N51FS
        len=N51FS_EntryGetCurrentNameToMIU(enId, MIUAddr, charLen);
#else
        __ASSERT(0);
#endif
    }
    else
    {
        __ASSERT(0);
    }

    return len;
}

/***************************************************************************************/
/// Reset all drives.
/***************************************************************************************/
#if FILE_SYSTEM_ENABLE_FCTRL_RESET_DEVICES
void msAPI_FCtrl_ResetDrives(void)
{
    U8 i;
    g_LocalDrive.DeviceIndex=INVALID_DEVICE_INDEX;
    g_LocalDrive.DriveIndex=INVALID_DRIVE_INDEX;
    g_LocalDrive.LBA=0;
    g_LocalDrive.PartitionNo=0xFF;
    g_LocalDrive.FileSystemType=FILE_SYSTEM_TYPE_NONE;

    for(g_LocalLoopIndex=0;g_LocalLoopIndex<DISK_DRIVE_NUM;g_LocalLoopIndex++)
    {
         msAPI_FS_MIU_Copy(GET_DRAM_ADDR(&g_LocalDrive), DRIVE_MEMORY_ADDR+g_LocalLoopIndex*sizeof(MSDCtrl_Drive), sizeof(MSDCtrl_Drive));

    }

    drvCount=0;
    for(i=0;i<MSD_PORT_NUM;i++)
    {
        drvCountPerPort[i]=0;
    }

}
#endif

/***************************************************************************************/
/// Get the counts of drive.
/// @return -Counts of drive.
/***************************************************************************************/
U8 msAPI_FCtrl_GetDriveCount()
{
   return drvCount;
}

#if FILE_SYSTEM_ENABLE_FCTRL_GET_DRIVE_COUNT_BY_PORT
/***************************************************************************************/
/// Get the counts of drive by port.
/// @param -portNum \b IN: Port num.
/// @return -Counts of drive.
/***************************************************************************************/
U8 msAPI_FCtrl_GetDriveCountByPort(U8 port)
{
    if(port<MSD_PORT_NUM)
    {
        return drvCountPerPort[port];
    }
    else
    {
        return 0xff;
    }
}
#endif

/***************************************************************************************/
/// Get the MSDCtrl_Drive struct by drive ID.
/// @param -driveID \b IN: Drive ID.
/// @param -pDrive \b IN: The pointer to the MSDCtrl_Drive struct which found by dirve ID.
/// @return -Success or fail.
/***************************************************************************************/
BOOLEAN msAPI_FCtrl_GetDriveByIndex(U8 driveID,MSDCtrl_Drive* pDrive)
{
    //MSDCtrl_Drive tmpDrive; //Eric won't use
    if(driveID==INVALID_DRIVE_INDEX||driveID>=DISK_DRIVE_NUM)
    {
        return FALSE;
    }

    //msAPI_FS_MIU_Copy(DRIVE_MEMORY_ADDR+driveID*sizeof(MSDCtrl_Drive),GET_DRAM_ADDR(&tmpDrive),sizeof(MSDCtrl_Drive)); //Eric won't use
    msAPI_FS_MIU_Copy(DRIVE_MEMORY_ADDR+driveID*sizeof(MSDCtrl_Drive),GET_DRAM_ADDR(pDrive),sizeof(MSDCtrl_Drive));

    //memcpy(pDrive,&tmpDrive,sizeof(MSDCtrl_Drive));  //Eric won't use

    if(pDrive->DriveIndex!=INVALID_DRIVE_INDEX)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }

    #if 0
    U8 i;
    MSDCtrl_Drive pBuff[DISK_DRIVE_NUM];
    if(driveID==INVALID_DRIVE_INDEX)
        return FALSE;

    msAPI_FS_MIU_Copy(DRIVE_MEMORY_ADDR,GET_DRAM_ADDR(pBuff),sizeof(MSDCtrl_Drive)*DISK_DRIVE_NUM);

    for(i=0;i<DISK_DRIVE_NUM;i++)
    {
        //printf("Get Drive By ID=%bd,%bd\n", ID,((Drive*)pBuff+i)->DriveID);
        if(pBuff[i].DriveIndex==driveID)
        {
            *pDrive=pBuff[i];
            return TRUE;
        }

    }

    return FALSE;
    #endif
}


/***************************************************************************************/
/// Check if the drive is mounted or not.
/// @param -u8DriveId \b IN: Drive ID.
/// @return -Success or fail.
/***************************************************************************************/
BOOLEAN msAPI_FCtrl_IsDriveMounted(U8 u8DriveId)
{
    return msAPI_FCtrl_GetDriveByIndex(u8DriveId, &g_LocalDrive);
}


#if(!FILE_SYSTEM_SMALL)

extern BOOLEAN FAT_EntryIsCurrentNameShortOnly(U8 enid);
#if (FILE_SYSTEM_ENABLE_IS_CURRENT_NAME_SHORT_ONLY)
BOOLEAN msAPI_FCtrl_EntryIsCurrentNameShortNameOnly(U8 enId)
{
    U8 fsType=FILE_SYSTEM_TYPE_NONE;


    if(enId>=FS_ENVIRONMENT_NUM)
    {
        __ASSERT(0);
        return FALSE;
    }
    fsType=msAPI_FSEnv_GetEnvironment(enId)->u8FileSystemType;

    if(fsType==FILE_SYSTEM_TYPE_FAT)
    {
        return FAT_EntryIsCurrentNameShortOnly(enId);
    }
    else if(fsType==FILE_SYSTEM_TYPE_N51FS)
    {
        return FALSE;
    }
    else
    {
        __ASSERT(0);
        return FALSE;
    }

}
#endif

/***************************************************************************************/
/// Delete file by the given file entry.
/// @param -pFileEntry \b IN: File entry.
/// @return -Success or fail.
/***************************************************************************************/
U8 msAPI_FCtrl_FileDelete(FileEntry* pFileEntry)
{

    FileEntry tmpEntry;
    FS_EnvironmentStruct* pFS_Env;
    U8 u8EnvironmentID, u8FileSysID;
    u8EnvironmentID = pFileEntry->EnvironmentID;
    pFS_Env = msAPI_FSEnv_GetEnvironment( pFileEntry->EnvironmentID );
    if(pFS_Env == NULL)
    {
        __ASSERT(0);
        return FALSE;
    }
    else
    {
        u8FileSysID = pFS_Env->u8FileSystemID;
    }

    memcpy(&tmpEntry,pFileEntry,sizeof(FileEntry));

    if ( u8EnvironmentID == 0xFF || u8FileSysID==0xFF
        || ((pFileEntry->EntryType != ENTRY_TYPE_FILE) && (pFileEntry->EntryType != ENTRY_TYPE_DIR)))
    {
             __ASSERT(0);
            return FALSE;
    }

    switch ( pFS_Env->u8FileSystemType )
    {
            case FILE_SYSTEM_TYPE_FAT:
            {
                    if ( FAT_FileDelete(&tmpEntry) )
                    {
                        msAPI_FCtrl_EntryFirst(tmpEntry.EnvironmentID);
                        return TRUE;
                    }
                    else
                    {
                        __ASSERT(0);
                        return FALSE;
                    }
            }
#if ENABLE_N51FS
            case FILE_SYSTEM_TYPE_N51FS:
                    if(N51FS_FileDelete(&tmpEntry))
                    {
                        msAPI_FCtrl_EntryFirst(tmpEntry.EnvironmentID);
                        return TRUE;
                    }
                    else
                    {
                        __ASSERT(0);
                        break; // just for make warning
                    }
#endif
            default:
            case FILE_SYSTEM_TYPE_NONE:
                    __ASSERT(0);
                    return INVALID_FILE_HANDLE;
    }

    return FALSE;
}

/***************************************************************************************/
/// Get parent's directory file entry .
/// @param -environmentId \b IN: Environment ID.
/// @param -pFileEntry \b IN: File entry to set.
/// @return -Success or fail.
/***************************************************************************************/
BOOLEAN msAPI_FCtrl_DirectoryGetDOTDOT(U8 environmentId,FileEntry* pFileToSet)
{
    FS_EnvironmentStruct* pFSEnv;
    U32 u32Temp;
    if(environmentId>=FS_ENVIRONMENT_NUM)
    {
        __ASSERT(0);
        return FALSE;
    }

    pFSEnv=msAPI_FSEnv_GetEnvironment(environmentId);
    if(pFSEnv == NULL)
    {
        __ASSERT(0);
        return FALSE;
    }

    pFileToSet->EnvironmentID=environmentId;

    pFileToSet->EntryType=ENTRY_TYPE_DIR_DOTDOT;
    pFileToSet->EntryAttrib=ENTRY_ATTRIB_DIRECTORY;

    pFileToSet->FileSystemID=pFSEnv->u8FileSystemID;
    pFileToSet->EntryFileLength=0;
    pFileToSet->EntrySeconds=0;
    LL_assign(&pFileToSet->FileLength,0);
    memset(pFileToSet->EntryID_Ext,0,sizeof(pFileToSet->EntryID_Ext));



    if(pFSEnv->u8FileSystemType==FILE_SYSTEM_TYPE_FAT)
    {
         //*((U32*)pFileToSet->EntryID)=FAT_DirectoryGetParentClusterNo(environmentId);
         u32Temp=FAT_DirectoryGetParentClusterNo(environmentId);
         memcpy(pFileToSet->EntryID,&u32Temp,4);
    }
    else if(pFSEnv->u8FileSystemType==FILE_SYSTEM_TYPE_N51FS)
    {
        #if ENABLE_N51FS
        //*((U32*)pFileToSet->EntryID)=N51FS_DirectoryGetParentMFR(environmentId);
        u32Temp=N51FS_DirectoryGetParentMFR(environmentId);
        memcpy(pFileToSet->EntryID,&u32Temp,4);
        #else
        __ASSERT(0);
        return FALSE;
        #endif
    }
    else
    {
        __ASSERT(0);
        return FALSE;
    }
    return TRUE;
}

/***************************************************************************************/
/// Get current directory file entry .
/// @param -environmentId \b IN: Environment ID.
/// @param -pFileEntry \b IN: File entry to set.
/// @return -Success or fail.
/***************************************************************************************/
#if FILE_SYSTEM_ENABLE_FCTRL_GET_DIRECTORY_DOT
BOOLEAN msAPI_FCtrl_DirectoryGetDOT(U8 environmentId,FileEntry* pFileToSet)
{

    FS_EnvironmentStruct* pFSEnv;
#if ENABLE_N51FS
    U32 u32Temp;
#endif
    if(environmentId>=FS_ENVIRONMENT_NUM)
    {
        __ASSERT(0);
        return FALSE;
    }

    pFSEnv=msAPI_FSEnv_GetEnvironment(environmentId);

    pFileToSet->EnvironmentID=environmentId;
    pFileToSet->EntryType=ENTRY_TYPE_DIR_DOT;
    pFileToSet->EntryAttrib=ENTRY_ATTRIB_DIRECTORY;

    pFileToSet->FileSystemID=pFSEnv->u8FileSystemID;
    pFileToSet->EntryFileLength=0;
    pFileToSet->EntrySeconds=0;
    LL_assign(&pFileToSet->FileLength,0);
    memset(pFileToSet->EntryID_Ext,0,sizeof(pFileToSet->EntryID_Ext));


    if(pFSEnv->u8FileSystemType==FILE_SYSTEM_TYPE_FAT)
    {
        FileEntry entry;

        FAT_GetCurrentFileEntry(environmentId, &entry);
        memcpy(pFileToSet->EntryID,entry.EntryID_Ext,4);
    }
    else if(pFSEnv->u8FileSystemType==FILE_SYSTEM_TYPE_N51FS)
    {
#if ENABLE_N51FS
        //*((U32*)pFileToSet->EntryID)=N51FS_DirectoryGetCurrentMFR(environmentId);
        u32Temp=N51FS_DirectoryGetCurrentMFR(environmentId);
        memcpy(pFileToSet->EntryID,&u32Temp,4);
#else
        UNUSED(pFileToSet);
        __ASSERT(0);
        return FALSE;
#endif
    }
    else
    {
        __ASSERT(0);
        return FALSE;
    }
    return TRUE;
}
#endif

/***************************************************************************************/
/// Check if the current directory is root directory or not.
/// @param -environmentId \b IN: Environment ID.
/// @return -Success or fail.
/***************************************************************************************/
BOOLEAN msAPI_FCtrl_DirectoryIsCurrentRoot(U8 environmentId)
{
    FS_EnvironmentStruct* pFSEnv;
    FAT_FileSysStruct stFAT_fileSys;
    FAT_Environment *pFAT_Env;
    U32 u32CurrentDirClusterNo;

    if(environmentId==0xFF)
           return FALSE;

    pFSEnv=msAPI_FSEnv_GetEnvironment(environmentId);
    if(pFSEnv == NULL)
    {
        __ASSERT(0);
        return FALSE;
    }

    if(pFSEnv->u8FileSystemType==FILE_SYSTEM_TYPE_FAT)
    {
           if ( !msAPI_FCtrl_FileSystemGetByID(pFSEnv->u8FileSystemID, &stFAT_fileSys) )
           {
              FCTRL_DBG(1, printf("get file system fail!\n"));
              return FALSE;
           }

           pFAT_Env = (FAT_Environment*)FAT_GetAddr(environmentId, FAT_XDATA_OPTION_ENVIRONMENT);

           u32CurrentDirClusterNo = pFAT_Env->stCurrentDirectory.u32CurrentDirStartClusterNo;

           if ( u32CurrentDirClusterNo == (stFAT_fileSys.u32RootDirStartClusterNo) )
           {
               return TRUE;
           }
           else
           {
               return FALSE;
           }
    }

    else if(pFSEnv->u8FileSystemType==FILE_SYSTEM_TYPE_N51FS)
    {
        BOOLEAN result=FALSE;
#if ENABLE_N51FS
        result=(N51FS_GetEnvironmentInfo(environmentId)->CurrentDirectoryMFR)==N51FS_ROOT_MFR;
#else
        __ASSERT(0);
#endif
        return result;

    }
    else
    {
        __ASSERT(0);
        return FALSE;
    }

}

#if FILE_SYSTEM_GET_FREE_SPACE_ENABLE
/***************************************************************************************/
/// Get free space size in KB.
/// @param -enId \b IN: Environment ID.
/// @return -Free space size in KB.
/***************************************************************************************/
U32 msAPI_FCtrl_GetUnusedSizeInKB_ByDriveIndex(U8 u8DriveIndex)
{
    FAT_FileSysStruct *pFsStruct;
    U8 u8fsType;

    //FS_EnvironmentStruct* pFSEnv;
    //pFSEnv=msAPI_FSEnv_GetEnvironment(enId);
    pFsStruct = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8DriveIndex);

    u8fsType=pFsStruct->FileSystemType;

    if(u8fsType==FILE_SYSTEM_TYPE_FAT)
    {
        return FAT_GetUnusedSizeInKB(u8DriveIndex);
    }
#if ENABLE_N51FS
    else if (u8fsType==FILE_SYSTEM_TYPE_N51FS)
    {

        return N51FS_GetFreeSpaceInKB(u8DriveIndex);
        //TODO for N51FS
    }
#endif
    else
    {
        __ASSERT(0);
        return 0;       //<<====error!!
    }
}

/***************************************************************************************/
/// Get free space size in KB.
/// @param -enId \b IN: Environment ID.
/// @return -Free space size in KB.
/***************************************************************************************/
U32 msAPI_FCtrl_GetUnusedSizeInKB_ByDriveIndex_New(U8 u8DriveIndex)
{
    FAT_FileSysStruct *pFsStruct;
    U8 u8fsType;

    //FS_EnvironmentStruct* pFSEnv;
    //pFSEnv=msAPI_FSEnv_GetEnvironment(enId);
    pFsStruct = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8DriveIndex);

    u8fsType=pFsStruct->FileSystemType;

    if(u8fsType==FILE_SYSTEM_TYPE_FAT)
    {
        //Fix DMS01156400 , some fat file system u32FSI_Free_Count = 0xFFFFFFFF
        return FAT_GetUnusedSizeInKB_New(u8DriveIndex);

    }
#if ENABLE_N51FS
    else if (u8fsType==FILE_SYSTEM_TYPE_N51FS)
    {

        return N51FS_GetFreeSpaceInKB(u8DriveIndex);
        //TODO for N51FS
    }
#endif
    else
    {
        __ASSERT(0);
        return 0;       //<<====error!!
    }
}
#endif

#if FILE_SYSTEM_GET_VOLUME_LABEL_ENABLE
// return the length of volume label
U8 msAPI_FCtrl_VolumeLabelGetByDriveIndex(U8 u8DriveIndex, U16 *VolLabName, U8 VolLabNameLen, BOOLEAN *pbIsUnicode)
{
#if 0
    U16 tempName[12] = {'T','E','M','P','_','V','O','L','L','A','B','\0'};
    VolLabNameLen=VolLabNameLen>11?11:VolLabNameLen;
    u8DriveIndex=u8DriveIndex;

    memset((U8 *)VolLabName,0,sizeof(U8)*(VolLabNameLen+1)*2);
    memcpy((U8 *)VolLabName,(U8 *)&tempName[0],sizeof(U8)*(VolLabNameLen+1)*2);

    return VolLabNameLen;
#else
    FAT_FileSysStruct *pFsStruct;
    U8 u8fsType;

    pFsStruct = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8DriveIndex);

    u8fsType=pFsStruct->FileSystemType;

    if(u8fsType==FILE_SYSTEM_TYPE_FAT)
    {
        U8 u8VolLabNoName[11] = {'N','O',0x20,'N','A','M','E',0x20,0x20,0x20,0x20};
        U8 pu8TempVolLab[12];
        BOOLEAN bIsNoName;
        U8 u8Count = 0;
        U8 len = 11;

        *pbIsUnicode = FALSE;
        pFsStruct = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8DriveIndex);

        memset(pu8TempVolLab,0,12);
        memcpy(pu8TempVolLab,pFsStruct->stBootSector.BS_VolLab,11);

        //Check if the stBootSector.BS_VolLab is "NO NAME"
        bIsNoName = TRUE;
        while(u8Count < len)
        {
            if(pu8TempVolLab[u8Count] != u8VolLabNoName[u8Count])
            {
                bIsNoName=FALSE;
                break;
            }
            u8Count ++;
        }

        if(!bIsNoName)
        {
            //stBootSector.BS_VolLab is not "NO NAME" and return it
            U8 i=11,j=0;
            U8 u8VolLabNameLenTemp=0;
            BOOLEAN bIsAllZero = TRUE;
            VolLabNameLen=VolLabNameLen>11?11:VolLabNameLen;

            FFLOW_CHECK(printf("BS_VolLab != \"NO NAME\"\n"));

            //check if all 0x00
            while(i>0)
            {
                i--;
                if(pu8TempVolLab[i]!=0x00)
                {
                    bIsAllZero=FALSE;
                    break;
                }
            }

            //truncate spaces at the end.
            i=11;
            while(i>0)
            {
                i--;
                if(pu8TempVolLab[i]!=0x20)
                {
                    break;
                }
            }
            //All 0x20 == empty
            if( ((i==0)&&(pu8TempVolLab[0]==0x20)) || bIsAllZero||
                ((pu8TempVolLab[0]==0x3f)&&(pu8TempVolLab[1]==0x3f)&&(pu8TempVolLab[2]==0x3f)))   //  0x3f 0x3f 0x3f ==  ???
            {
                return FAT_DirEntryFindVolumeLabel(u8DriveIndex, VolLabName, VolLabNameLen);;
            }

            for(j=0;j<(i+1);j++)
            {
                if(pu8TempVolLab[j]<0x80)
                {
                    VolLabName[u8VolLabNameLenTemp] = (U16)pu8TempVolLab[j];
                }
                else
                {
                    VolLabName[u8VolLabNameLenTemp] = (U16)( ((U16)pu8TempVolLab[j] << 8) | pu8TempVolLab[j+1]);
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
        else
        {
            FFLOW_CHECK(printf("BS_VolLab == \"NO NAME\" => Get VolumeEntry from RootDirEntry\n"));
            return FAT_DirEntryFindVolumeLabel(u8DriveIndex, VolLabName, VolLabNameLen);
        }
    }
#if ENABLE_N51FS
    else if (u8fsType==FILE_SYSTEM_TYPE_N51FS)
    {
        //TODO for N51FS
        *pbIsUnicode = TRUE;
        return N51FS_FileRecordFindVolumeLabel(u8DriveIndex, VolLabName, VolLabNameLen);
    }
#endif
    else
    {
        __ASSERT(0);
        return 0;       //<<====error!!
    }
#endif

}
#endif

#if FILE_SYSTEM_GET_TOTAL_SIZE_ENABLE
/***************************************************************************************/
/// Get total disk size in KB.
/// @param -environmentId \b IN: Environment ID.
/// @return -Total disk size in KB.
/***************************************************************************************/
U32 msAPI_FCtrl_GetTotalSizeInKB_ByDriveIndex(U8 u8DriveIndex)
{
    FAT_FileSysStruct *pFsStruct;
    U8 u8fsType;

    //FS_EnvironmentStruct* pFSEnv;
    //pFSEnv=msAPI_FSEnv_GetEnvironment(enId);
    pFsStruct = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8DriveIndex);

    u8fsType=pFsStruct->FileSystemType;

    if(u8fsType==FILE_SYSTEM_TYPE_FAT)
    {
        return FAT_GetTotalSizeInKB(u8DriveIndex);
    }
#if ENABLE_N51FS
    else if (u8fsType==FILE_SYSTEM_TYPE_N51FS)
    {
        return N51FS_GetTotalSizeInKB(u8DriveIndex);
        //TODO for N51FS
    }
#endif
    else
    {
        __ASSERT(0);
        return 0;       //<<====error!!
    }

}
#endif

#if FILE_SYSTEM_ENABLE_FCTRL_ENTRY_SEARCH_BY_NAME
/***************************************************************************************/
/// Search the file entry by given name.
/// @param -u8EnId \b IN: Environment ID.
/// @param -pu16FileNameToFind \b IN: File name to find.
/// @param -u8FileNameToFindLen \b IN: Length of the file name to find.
/// @param -pEntryToSet \b IN: File entry to set.
/// @return -Success or fail.
/***************************************************************************************/
BOOLEAN msAPI_FCtrl_EntrySearchByName(U8 u8EnId,U16 *pu16FileNameToFind,U8 u8FileNameToFindLen ,FileEntry *pEntryToSet)
{
    U16 *pu16FileName;
    BOOLEAN bIsFound = FALSE;
    FileEntry stFileEntry;

    pu16FileName= (U16*)msAPI_FS_Memory_Allocate(256*2);
    if(pu16FileName == NULL)
    {
        __ASSERT(0);
        return FALSE;
    }
    msAPI_FCtrl_EntryFirst(u8EnId);


    while(msAPI_FCtrl_EntryNext(u8EnId, &stFileEntry)==ENTRY_NEXT_RESULT_SUCCESS)
    {
        U8 u8Count = 0;
        U8 len=0;

        FS_RESET_WDT() ;

        len = msAPI_FCtrl_EntryGetCurrentName(u8EnId, GET_DRAM_ADDR(pu16FileName), 255);

        if(len!=u8FileNameToFindLen)
        {
            continue;
        }

        while(u8Count < len)
        {
            if( ((U8 *)pu16FileNameToFind)[u8Count*2] != ((U8 *)pu16FileName)[u8Count*2] ||
                ((U8 *)pu16FileNameToFind)[u8Count*2+1] != ((U8 *)pu16FileName)[u8Count*2+1] )
            {
                break;
            }
            u8Count ++;
        }

        if(u8Count == len)
        {
            bIsFound = TRUE;
            memcpy(pEntryToSet, &stFileEntry, sizeof(FileEntry));
            break;
        }

    }

    msAPI_FS_Memory_Free(pu16FileName);

    return bIsFound;
}
#endif


#if FILE_SYSTEM_SEARCH_BY_SHORT_NAME_ENABLE
/***************************************************************************************/
/// Search the file entry by given short name.
/// @param -u8EnId \b IN: Environment ID.
/// @param -pu16FileNameToFind \b IN: File name to find.
/// @param -u8FileNameToFindLen \b IN: Length of the file name to find.
/// @param -pEntryToSet \b IN: File entry to set.
/// @return -Success or fail.
/// If RD modifies this function, please do also modify "msAPI_FCtrl_EntrySearchByShortNameFromCurrentDirEntry()"
/***************************************************************************************/
BOOLEAN msAPI_FCtrl_EntrySearchByShortName(U8 u8EnId,U8 *pu8FileNameToFind,U8 u8FileNameToFindLen ,FileEntry *pEntryToSet)
{
    U8 *pu8FileName;
    BOOLEAN bIsFound = FALSE;
    FileEntry stFileEntry;

    pu8FileName= (U8*)msAPI_FS_Memory_Allocate(13);
    if(pu8FileName == NULL)
    {
        __ASSERT(0);
        return FALSE;
    }
    msAPI_FCtrl_EntryFirst(u8EnId);


    while(msAPI_FCtrl_EntryNext(u8EnId, &stFileEntry)==ENTRY_NEXT_RESULT_SUCCESS)
    {
        U8 u8Count = 0;
        U8 len=0;

        FS_RESET_WDT() ;

        len = msAPI_FCtrl_EntryGetShortNameByFileEntry(u8EnId, &stFileEntry,GET_DRAM_ADDR(pu8FileName),12);

        pu8FileName[len]=0;
        if(len!=u8FileNameToFindLen)
        {
            continue;
        }

        while(u8Count < len)
        {
            if(pu8FileNameToFind[u8Count] != pu8FileName[u8Count]     )
            {
                break;
            }
            u8Count ++;
        }

        if(u8Count == len)
        {
            bIsFound = TRUE;
            memcpy(pEntryToSet, &stFileEntry, sizeof(FileEntry));
            break;
        }

    }

    msAPI_FS_Memory_Free(pu8FileName);

    return bIsFound;
}
#endif

#if FILE_SYSTEM_SEARCH_BY_SHORT_NAME_ENABLE
void msAPI_FCtrl_SetCurrentDirEntryIndex(S32 s32CurrentDirEntryIndex)
{
    g_s32CurrentDirEntryIndex = s32CurrentDirEntryIndex;
    return;
}

S32 msAPI_FCtrl_GetCurrentDirEntryIndex(void)
{
    return g_s32CurrentDirEntryIndex;
}

void msAPI_FCtrl_ResetCurrentDirEntryIndex(void)
{
    g_s32CurrentDirEntryIndex = -1;
    return;
}
/***************************************************************************************/
/// Search the file entry from current directory entry index by given short name.
/// @param -u8EnId \b IN: Environment ID.
/// @param -pu16FileNameToFind \b IN: File name to find.
/// @param -u8FileNameToFindLen \b IN: Length of the file name to find.
/// @param -pEntryToSet \b IN: File entry to set.
/// @return -Success or fail.
/***************************************************************************************/
BOOLEAN msAPI_FCtrl_EntrySearchByShortNameFromCurrentDirEntry(U8 u8EnId,U8 *pu8FileNameToFind,U8 u8FileNameToFindLen ,FileEntry *pEntryToSet)
{
    U8 *pu8FileName;
    BOOLEAN bIsFound = FALSE;
    FileEntry stFileEntry;
    FAT_Environment* pFAT_Env;
    pFAT_Env=(FAT_Environment*)FAT_GetAddr(u8EnId, FAT_XDATA_OPTION_ENVIRONMENT);

    pu8FileName= (U8*)msAPI_FS_Memory_Allocate(u8FileNameToFindLen);
    if(pu8FileName == NULL)
    {
        __ASSERT(0);
        return FALSE;
    }
    //[Traverse from current index
    if (g_s32CurrentDirEntryIndex == -1) //do not indicate index of entry
        msAPI_FCtrl_EntryFirst(u8EnId);
    else
    {
        /* solution-1 */
        /*pFAT_Env=(FAT_Environment*)FAT_GetXData(u8EnId, FAT_XDATA_OPTION_ENVIRONMENT);
        pFAT_Env->stCurrentDirectory.s32CurrentDirEntryIndex = g_s32CurrentDirEntryIndex;
        pFAT_Env->stCurrentDirectory.s16DirEntryCacheCurrentIndex = g_s32CurrentDirEntryIndex;
        FAT_ReturnXData();*/

        /* solution-2 */
        msAPI_FCtrl_EntryFirst(u8EnId);
        BOOLEAN _btmp = TRUE;
        while(g_s32CurrentDirEntryIndex > pFAT_Env->stCurrentDirectory.s32CurrentDirEntryIndex)
        {
            _btmp = msAPI_FCtrl_EntryNext(u8EnId, &stFileEntry);
        }
    }
    //]

    while(msAPI_FCtrl_EntryNext(u8EnId, &stFileEntry)==ENTRY_NEXT_RESULT_SUCCESS)
    {
        U8 u8Count = 0;
        U8 len=0;

        FS_RESET_WDT() ;

        len = msAPI_FCtrl_EntryGetShortNameByFileEntry(u8EnId, &stFileEntry,GET_DRAM_ADDR(pu8FileName),u8FileNameToFindLen);

        pu8FileName[len-1]=0;
        if(len!=u8FileNameToFindLen)
        {
            continue;
        }

        while(u8Count < len)
        {
            if(pu8FileNameToFind[u8Count] != pu8FileName[u8Count]     )
            {
                break;
            }
            u8Count ++;
        }

        if(u8Count == len)
        {
            bIsFound = TRUE;
            memcpy(pEntryToSet, &stFileEntry, sizeof(FileEntry));
            break;
        }

    }

    msAPI_FS_Memory_Free(pu8FileName);

    //[keep current entry index for next time's traversing
    g_s32CurrentDirEntryIndex = pFAT_Env->stCurrentDirectory.s32CurrentDirEntryIndex;
    //]

    return bIsFound;
}
#endif

#if FILE_SYSTEM_GET_FILENAME_BY_FILEENTRY_ENABLE
/***************************************************************************************/
/// Get file name by given file entry.
/// @param -enId \b IN: Environment ID.
/// @param -pEntry \b IN: File entry to find.
/// @param -MIUAddr \b IN: MIU address to put thd found file name.
/// @param -charLen \b IN: Length of MIU address.
/// @param -bIsLongName \b IN: File name is long name or not.
/// @return -Length of file name.
/***************************************************************************************/
static U8 msAPI_FCtrl_GetNameByFileEntry(U8 enId, FileEntry* pEntry, U32 MIUAddr, U8 charLen, BOOLEAN *bIsLongName)
{
    U8 fsType=msAPI_FSEnv_GetEnvironment(enId)->u8FileSystemType;
    U8 len=0;

    FileEntry tmpEntry;


    memcpy(&tmpEntry,pEntry,sizeof(FileEntry));

    if(enId==INVALID_FILE_HANDLE)
    {
        __ASSERT(0);
        return 0;
    }

    if(fsType==FILE_SYSTEM_TYPE_FAT)
    {
        len=FAT_GetNameByFileEntry(enId, &tmpEntry, MIUAddr, charLen, bIsLongName);
    }
    else if(fsType==FILE_SYSTEM_TYPE_N51FS)
    {
#if ENABLE_N51FS
        len=N51FS_EntryGetFileNameByFileEntry(enId, &tmpEntry, MIUAddr, charLen, bIsLongName);
#else
        __ASSERT(0);
#endif
    }
    else
    {
        __ASSERT(0);
    }

    return len;
}

/***************************************************************************************/
/// Get long file name by given file entry.
/// @param -enId \b IN: Environment ID.
/// @param -pEntry \b IN: File entry to find.
/// @param -MIUAddr \b IN: MIU address to put thd found file name.
/// @param -charLen \b IN: Length of MIU address.
/// @param -pbShortNameOnly \b IN: File name is short name or not.
/// @return -Length of file name.
/***************************************************************************************/
U8 msAPI_FCtrl_EntryGetLongNameByFileEntry(U8 enId, FileEntry* pEntry, U32 MIUAddr, U8 charLen, BOOLEAN* pbShortNameOnly)
{
    BOOLEAN bIsLongName=TRUE;
    U8 u8fileLen;

    u8fileLen = msAPI_FCtrl_GetNameByFileEntry(enId,pEntry,MIUAddr,charLen,&bIsLongName);
    *pbShortNameOnly = (bIsLongName==FALSE)?TRUE:FALSE;

    return u8fileLen;
}

/***************************************************************************************/
/// Get short file name by given file entry.
/// @param -enId \b IN: Environment ID.
/// @param -pEntry \b IN: File entry to find.
/// @param -MIUAddr \b IN: MIU address to put thd found file name.
/// @param -charLen \b IN: Length of MIU address.
/// @return -Length of file name.
/***************************************************************************************/
U8 msAPI_FCtrl_EntryGetShortNameByFileEntry(U8 enId, FileEntry* pEntry, U32 MIUAddr, U8 charLen)
{
    BOOLEAN bIsLongName=FALSE;
    U8 u8fileLen;

    u8fileLen = msAPI_FCtrl_GetNameByFileEntry(enId,pEntry,MIUAddr,charLen,&bIsLongName);

    return u8fileLen;
}

#endif

#if FILE_SYSTEM_LONGLONG_API_ENABLE
/***************************************************************************************/
/// Get the file length in LongLong format.
/// @param -u8HandleNo \b IN: File handle number.
/// @return -File length in LongLong format.
/***************************************************************************************/
LongLong msAPI_FCtrl_FileLength_LongLong(U8 u8HandleNo)
{

    U8 fsType;
    FileHandleStruct* pHandle;
    FAT_FileSysStruct* pFAT_FileSys;
    U8 u8fsid;
    LongLong val;

    val.Hi=0;
    val.Lo=0;

    if(u8HandleNo==INVALID_FILE_HANDLE)
           return val;

    pHandle=FCtrl_GetFileHandleInfo(u8HandleNo);

    u8fsid = pHandle->FileSystemID;

    if(u8fsid>=DISK_DRIVE_NUM)
    {
        __ASSERT(0);
        return val;
    }

    pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemInfo(u8fsid);

    fsType = pFAT_FileSys->FileSystemType;

    if(fsType==(U8)FILE_SYSTEM_TYPE_FAT)
    {

        FAT_FileInode *pstFAT_FileInode;

       pstFAT_FileInode = FAT_File_GetInodeFromHandle(u8HandleNo);

        val.Lo = pstFAT_FileInode->u32FileTotalSize;
    }
    else if(fsType==(U8)FILE_SYSTEM_TYPE_N51FS)
    {
        #if ENABLE_N51FS
        val=N51FS_FileLength(u8HandleNo);
        #else
        __ASSERT(0);
        #endif

    }
    else
    {
        __ASSERT(0);
    }
    return val;
}

#if ( FILE_SYSTEM_ENABLE_TELL_LONG_LONG)
/***************************************************************************************/
/// Get the file current position in LongLong format.
/// @param -u8HandleNo \b IN: File handle number.
/// @return -File current position in LongLong format.
/***************************************************************************************/
LongLong msAPI_FCtrl_FileTell_LongLong(U8 u8HandleNo)
{

    U8 fsType;
    FileHandleStruct xdata * _pstFileHandle;
    FAT_FileSysStruct* pFAT_FileSys;
    U8 u8fsid;
    LongLong val;

    val.Hi=0xFFFFFFFF;
    val.Lo=0xFFFFFFFF;

    FCTRL_DBG(0,printf("\n>>>>>>>> FILE TELL!! fileHandle=%bu\n",u8HandleNo););
    if(u8HandleNo==INVALID_FILE_HANDLE)
    {
        return val;
    }

    _pstFileHandle = FCtrl_GetFileHandleInfo(u8HandleNo);

    u8fsid = _pstFileHandle->FileSystemID;

    if(u8fsid>=DISK_DRIVE_NUM)
    {
        __ASSERT(0);
        return val;
    }

    pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemInfo(u8fsid);

    fsType = pFAT_FileSys->FileSystemType;

    if(fsType==(U8)FILE_SYSTEM_TYPE_FAT)
    {
        val.Hi=0;
        val.Lo=FAT_FileTell(u8HandleNo);
    }
    else if(fsType==(U8)FILE_SYSTEM_TYPE_N51FS)
    {
      #if ENABLE_N51FS
        val=N51FS_FileTell(u8HandleNo);
      #else
        __ASSERT(0);
      #endif
    }
    else
    {
        __ASSERT(0);
    }

    return val;
}
#endif
/***************************************************************************************/
/// File Seek using LongLong length. This can seek position over 4G.
/// @param -u8HandleNo \b IN: Handle Number.
/// @param -u32Length \b IN: LongLong seek length.
/// @param -option \b IN: File seek option.
/// @return -Success or fail.
/***************************************************************************************/
BOOLEAN msAPI_FCtrl_FileSeek_LongLong(U8 u8HandleNo, LongLong u32Length, EN_FILE_SEEK_OPTION option)
{
    U32 u32SeekLength;
    LongLong fileLength;
    U32 i=0;
    if(u8HandleNo==INVALID_FILE_HANDLE)
        return FALSE;
    //seek length can't bigger than file length.
    fileLength=msAPI_FCtrl_FileLength_LongLong(u8HandleNo);
    u32Length=LL_greater_or_equal(&u32Length, &fileLength)? fileLength:u32Length;

    while(!LL_iszero(&u32Length) || i == 0)
    {
        //if seek length bigger than 4G, it should take more times to seek
        u32SeekLength= (u32Length.Hi>0)? 0xFFFFFFFF: u32Length.Lo;
        option = (i>0)? FILE_SEEK_CUR : option; // Next seek should start from current position
        if(msAPI_FCtrl_FileSeek(u8HandleNo, u32SeekLength, option))
        {
            u32Length = LL_subtract(&u32Length,u32SeekLength);
        }
        else
        {
            __ASSERT(0);
            return FALSE;
        }
        i++;
    }
    return TRUE;
}
#endif

#if ( FILE_SYSTEM_ENABLE_GET_SUPPORT_MODE )
/***************************************************************************************/
/// Get the file system support mode such as read, write and delete.
/// @param -u8FileSysID \b IN: File system ID.
/// @return -File system support mode.
/***************************************************************************************/
U8 msAPI_FCtrl_FileSystemGetSupportMode(U8 u8FileSysID)
{
    U8 u8Result = FILE_SYSTEM_SUPPORT_NONE;
    U32 *fsptr;
    U8 fsType;

    if(u8FileSysID >= DISK_DRIVE_NUM)
    {
        __ASSERT(0);
        return FILE_SYSTEM_SUPPORT_NONE;
    }

    fsptr=FCtrl_GetFileSystemInfo(u8FileSysID);

    fsType=((N51FS_FileSysStruct*)fsptr)->FileSystemType;

    if(fsType==(U8)FILE_SYSTEM_TYPE_FAT)
    {
        FAT_FileSysStruct* pFAT_FileSys;
        pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemInfo(u8FileSysID);

        u8Result = pFAT_FileSys->FileSystemSupport;
    }
    else if(fsType==(U8)FILE_SYSTEM_TYPE_N51FS)
    {
        #if ENABLE_N51FS
        N51FS_FileSysStruct* pN51FS_FileSys;
        pN51FS_FileSys = (N51FS_FileSysStruct *)FCtrl_GetFileSystemInfo(u8FileSysID);

        u8Result = pN51FS_FileSys->FileSystemSupport;
        #else
        __ASSERT(0);
        return FILE_SYSTEM_SUPPORT_NONE;
        #endif
    }
    else
    {
        __ASSERT(0);
        return FILE_SYSTEM_SUPPORT_NONE;
    }
    return u8Result;
}
#endif
#if ( FILE_SYSTEM_ENABLE_SET_SUPPORT_MODE )
/***************************************************************************************/
/// Set the file system support mode such as read, write and delete.
/// @param -u8FileSysID \b IN: File system ID.
/// @return -File system support mode.
/***************************************************************************************/
void msAPI_FCtrl_FileSystemSetSupportMode(U8 u8FileSysID,U8 mode)
{
    U32 *fsptr;
    U8 fsType;

    if(u8FileSysID >= DISK_DRIVE_NUM)
    {
        __ASSERT(0);
        return;
    }

    fsptr=FCtrl_GetFileSystemInfo(u8FileSysID);

    fsType=((N51FS_FileSysStruct*)fsptr)->FileSystemType;


    if(fsType==(U8)FILE_SYSTEM_TYPE_FAT)
    {
        FAT_FileSysStruct* pFAT_FileSys;
        pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemInfo(u8FileSysID);
        pFAT_FileSys->FileSystemSupport=mode;
    }
    else if(fsType==(U8)FILE_SYSTEM_TYPE_N51FS)
    {
        #if ENABLE_N51FS
        N51FS_FileSysStruct* pN51FS_FileSys;
        pN51FS_FileSys = (N51FS_FileSysStruct *)FCtrl_GetFileSystemInfo(u8FileSysID);

        pN51FS_FileSys->FileSystemSupport=mode;
        #else
        __ASSERT(0);
        return;
        #endif
    }
    else
    {
        __ASSERT(0);
        return;
    }
}
#endif
#endif //FILE_SYSTEM_SMALL


#if (FILE_SYSTEM_WRITE_ENABLE)
/***************************************************************************************/
/// Create a file for the given file name and without check if it is exists or not.
/// @param -u8enid \b IN: Environment ID.
/// @param -pu16LongName \b IN: Pointer to the Long file name.
/// @param -charLen \b IN: Long file name length.
/// @return -File handle number.
/***************************************************************************************/
U8 msAPI_FCtrl_FileCreate_WithoutNameChecking(U8 u8enid, U16 *pu16LongName, U8 charLen, EN_CREATE_MODE createMode)
{
    U8 u8Result;
    U8 fsType;

    fsType = msAPI_FSEnv_GetEnvironment(u8enid)->u8FileSystemType;
    if(fsType == (U8)FILE_SYSTEM_TYPE_FAT)
    {
        u8Result = FAT_FileCreate(u8enid,pu16LongName,charLen,createMode);
    }
    else
    {
        u8Result = INVALID_FILE_HANDLE;
        __ASSERT(0);//unsuport type!!

    }

    return u8Result;
}

/***************************************************************************************/
/// Create a file for the given file name. Before create, it will check if it is exists or not.
/// @param -u8enid \b IN: Environment ID.
/// @param -pu16LongName \b IN: Pointer to the Long file name.
/// @param -charLen \b IN: Long file name length.
/// @param -createMode \b IN: Create mode.
/// @return -File handle number.
/***************************************************************************************/
U8 msAPI_FCtrl_FileCreate(U8 u8enid, U16 *pu16LongName, U8 charLen, EN_CREATE_MODE createMode)
{

    U8 fsType;
    FileEntry entry;
    U8 doubleCheckLen;


    fsType = msAPI_FSEnv_GetEnvironment(u8enid)->u8FileSystemType;

    doubleCheckLen=FS_strlen_U(pu16LongName);
    if(doubleCheckLen==0 || charLen==0)
    {
        __ASSERT(0);//name is not correct
        return INVALID_FILE_HANDLE;
    }

    charLen=(charLen>doubleCheckLen)?doubleCheckLen:charLen;


    if(msAPI_FCtrl_EntrySearchByName(u8enid, pu16LongName, charLen, &entry))
    {
        if(createMode==CREATE_MODE_NEW_FORCE)
        {
            msAPI_FCtrl_FileDelete(&entry);
        }
        else
        {
            FCTRL_DBG(0,printf("File Existed!!\n"););
            return INVALID_FILE_HANDLE;
        }
    }

    return msAPI_FCtrl_FileCreate_WithoutNameChecking(u8enid,pu16LongName,charLen, createMode);

}

/***************************************************************************************/
/// Open directory by the given directory entry and open mode.
/// @param -pFileEntry \b IN: Directory entry.
/// @param -u8OpenMode \b IN: Open mode, see the definition.
/// @return -File handle number.
/***************************************************************************************/
U8 msAPI_FCtrl_DirectoryOpen(FileEntry* pFileEntry, U8 u8OpenMode)
{
    FAT_FileSysStruct stFAT_FileSys;
    FileEntry tmpEntry;

    BOOLEAN fastOpen=FALSE;

    FFLOW_CHECK(printf("\n>>>> Directory OPEN!! ID=0x%08lx\n",*((U32*)pFileEntry->EntryID)););

    if(u8OpenMode==(U8)OPEN_MODE_FAST_FOR_READ)
    {
        u8OpenMode=OPEN_MODE_FOR_READ;
        fastOpen=TRUE;
    }


    if((pFileEntry==NULL) || ((pFileEntry->EntryType!=ENTRY_TYPE_DIR) &&
       (pFileEntry->EntryType!=ENTRY_TYPE_DIR_DOT) && (pFileEntry->EntryType!=ENTRY_TYPE_DIR_DOTDOT)))
    {
        __ASSERT(0);
        return INVALID_FILE_HANDLE;
    }

    if ( !msAPI_FCtrl_FileSystemGetByID(pFileEntry->FileSystemID, &stFAT_FileSys) )
    {
          FCTRL_DBG(0,printf("Get FileSystem Failed. FileSystemID=%bu\n",pFileEntry->FileSystemID););
          return INVALID_FILE_HANDLE;
    }

    memcpy(&tmpEntry,pFileEntry,sizeof(FileEntry));

    FFLOW_CHECK(printf("    fsType=%bu\n",(U8)stFAT_FileSys.FileSystemType););

    if(stFAT_FileSys.FileSystemType == FILE_SYSTEM_TYPE_FAT)
    {
        U8 u8FileHandleID;


        u8FileHandleID = msAPI_FCtrl_FileHandleCreate(&stFAT_FileSys,&tmpEntry,u8OpenMode);

        if ( u8FileHandleID != INVALID_FILE_HANDLE )
        {
            if ( FAT_FileOpen(u8FileHandleID, &tmpEntry,fastOpen) )
            {
//                 FileHandleStruct* phandle;
             //    phandle=FCtrl_GetFileHandleInfo();
             //    phandle[u8FileHandleID].stFileEntry=tmpEntry;
            //   FCtrl_ReturnFileHandleXdata();
                 FFLOW_CHECK(printf("    SUCCESS!! fileHandle=%bu\n",u8FileHandleID););
                 return u8FileHandleID;
            }
            else
            {
                  FCTRL_DBG(0,printf("Open Failed\n"););
                  msAPI_FCtrl_FileHandleFree(u8FileHandleID);
                  return INVALID_FILE_HANDLE;
            }
        }
        else
        {
            __ASSERT(0);
        }

    }
    else if(stFAT_FileSys.FileSystemType == FILE_SYSTEM_TYPE_N51FS)
    {
        #if ENABLE_N51FS
        U8 handleId;
        N51FS_FileSysStruct N51FS_fs;

        //U32 mfr = *((U32*)pFileEntry->EntryID);
        U32 mfr;
        memcpy(&mfr,pFileEntry->EntryID,4);

        memcpy((U8*)&N51FS_fs, (U8*)&stFAT_FileSys, sizeof(N51FS_FileSysStruct));

        handleId=msAPI_FCtrl_FileHandleCreate(&N51FS_fs,&tmpEntry,u8OpenMode);

        if(handleId!=INVALID_FILE_HANDLE)
        {

            if(N51FS_FileOpen(handleId, mfr))
            {
                //FileHandleStruct* phandle;
                //FCTRL_DBG(0,printf("name=%s,opening mfr=0x%08lx\n",pFileEntry->EntryLongName,mfr););
                //phandle=FCtrl_GetFileHandleInfo();
                //phandle[handleId].stFileEntry=tmpEntry;
                //FCtrl_ReturnFileHandleXdata();
                FFLOW_CHECK(printf("    SUCCESS!! fileHandle=%bu\n",handleId););
                return handleId;
            }

            __ASSERT(0);
            msAPI_FCtrl_FileHandleFree(handleId);

        }
        #else
        __ASSERT(0);
        #endif
        return INVALID_FILE_HANDLE;
    }


    //printf("unable to open Directory with FileSystemType=0x%02bx\n",pEnv->u8FileSystemType);
    return INVALID_FILE_HANDLE;
}

#if FILE_SYSTEM_FOLDER_CREATE_ENABLE
BOOLEAN msAPI_FCtrl_DirectoryCreate(U8 u8enid, U16 *pu16LongName, U8 charLen)
{
    U8 u8Result;
    U8 fsType;
    FileEntry entry;
    U8 doubleCheckLen;

    fsType = msAPI_FSEnv_GetEnvironment(u8enid)->u8FileSystemType;

    doubleCheckLen=FS_strlen_U(pu16LongName);
    if(doubleCheckLen==0||charLen==0)
    {
        __ASSERT(0);//name is not correct
        return FALSE;
    }
    charLen=(charLen>doubleCheckLen)?doubleCheckLen:charLen;


    u8Result=FALSE;

    if(msAPI_FCtrl_EntrySearchByName(u8enid, pu16LongName, charLen, &entry))
    {
        FCTRL_DBG(0,printf("Directory Existed!!\n"););
        return u8Result;
    }


    if(fsType == (U8)FILE_SYSTEM_TYPE_FAT)
    {
        U8 _handle;
        _handle = FAT_FolderCreate(u8enid,pu16LongName,charLen);
        if(_handle==INVALID_FILE_HANDLE)
        {
            __ASSERT(0);

        }
        else
        {
            msAPI_FCtrl_FileClose(_handle);
            u8Result=TRUE;
        }

    }
    else
    {
        __ASSERT(0);//unsuport type!!

    }

    return u8Result;
}

BOOLEAN msAPI_FCtrl_DirectoryCreate_And_GetFileEntry(U8 u8enid, U16 *pu16LongName, U8 charLen, FileEntry *pstFileEntry)
{
    U8 u8Result;
    U8 fsType;
    U8 doubleCheckLen;

    fsType = msAPI_FSEnv_GetEnvironment(u8enid)->u8FileSystemType;

    doubleCheckLen=FS_strlen_U(pu16LongName);
    if(doubleCheckLen==0||charLen==0)
    {
        __ASSERT(0);//name is not correct
        return FALSE;
    }
    charLen=(charLen>doubleCheckLen)?doubleCheckLen:charLen;


    u8Result=FALSE;

    if(msAPI_FCtrl_EntrySearchByName(u8enid, pu16LongName, charLen, pstFileEntry))
    {
        FCTRL_DBG(0,printf("Directory Existed!!\n"););
        return TRUE;
        //return u8Result;
    }


    if(fsType == (U8)FILE_SYSTEM_TYPE_FAT)
    {
        U8 _handle;
        _handle = FAT_FolderCreate(u8enid,pu16LongName,charLen);
        if(_handle==INVALID_FILE_HANDLE)
        {
            printf("_handle==INVALID_FILE_HANDLE\n");
            __ASSERT(0);

        }
        else
        {
            msAPI_FCtrl_EntryGetByHandle(_handle, pstFileEntry);
            pstFileEntry->EntryType = ENTRY_TYPE_DIR;
            msAPI_FCtrl_FileClose(_handle);
            u8Result=TRUE;
        }

    }
    else
    {
        __ASSERT(0);//unsuport type!!

    }

    return u8Result;
}
#endif

U32 msAPI_FCtrl_FileWrite(U8 u8HandleNo, U32 u32Buffer, U32 u32Length)
{
    U32 u32Result;
    U8 fsType;
    FileHandleStruct* pHandle;
    FAT_FileSysStruct * pFAT_FileSys;
    U8 u8fsid;
    U32 u32VABuffer;

    //printf("msAPI_FCtrl_FileWrite(u8HandleNo=%u, u32Buffer=0x%X, u32Length=0x%X)\n", u8HandleNo, u32Buffer, u32Length);

    if(u8HandleNo == INVALID_FILE_HANDLE)
        return 0;

    u32VABuffer = _PA2VA(u32Buffer);

    pHandle=FCtrl_GetFileHandleInfo(u8HandleNo);

    if(pHandle->HandleID==INVALID_FILE_HANDLE)
    {
        //you are now using one hande which has already been closed before
        __ASSERT(0);
        return 0;
    }

    u8fsid = pHandle->FileSystemID;

    pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemInfo(u8fsid);

    fsType = pFAT_FileSys->FileSystemType;
    //printf("fsType=%u\n", fsType);

    if(fsType == (U8)FILE_SYSTEM_TYPE_FAT)
    {
        u32Result = FAT_FileWrite(u8HandleNo, u32VABuffer, u32Length);
    }
    else
    {
        //u32Result = 0;
        u32Result = u32Length; //return original length for Error!
        __ASSERT(0);//unsuport type!!
    }

    //printf("u32Result=%u\n", u32Result);
    return u32Result;
}

#if  (FILE_SYSTEM_ENABLE_ENTRY_GET_BY_HANDLE)
BOOLEAN msAPI_FCtrl_EntryGetByHandle(U8 u8HandleNo,FileEntry* pEntryToSet)
{
    FileHandleStruct* pHandle;
    FileInodeStruct*  pInode;
    U8 InodeID;


    if(u8HandleNo==INVALID_FILE_HANDLE)
    {
        return FALSE;
    }

    pHandle=FCtrl_GetFileHandleInfo(u8HandleNo);

    if(pHandle->HandleID==INVALID_FILE_HANDLE)
    {
        //not yet opened...
        return FALSE;
    }
    InodeID = pHandle->InodeID;
    if(InodeID == INVALID_FILE_INODEID)
    {
        return FALSE;
    }

    pInode = FCtrl_GetFileInodeInfo(InodeID);
    memcpy(pEntryToSet,&pInode->stFileEntry,sizeof(FileEntry));

    return TRUE;

}
#endif // #if  (FILE_SYSTEM_ENABLE_ENTRY_GET_BY_HANDLE)

#endif // #if (FILE_SYSTEM_WRITE_ENABLE)



#if (ENABLE_DREC)

#include "drvsys.h"

#define CACHE_CLUSTER_COUNT 1

static void _MarkUsedCluster(U8 deviceIndex,FAT_FileSysStruct* pfs,U32 startCluster,U32 len)
{
    U32 result=0;
    U32 endFlag=0xFFFFFF0F;
    U32 FATSector=pfs->stBootSector.BPB_RsvdSecCnt;
    U32 relativeSector=pfs->u32RelativeSector;

    if(len>0)
    {
        U32 totalCluster=(len-1)/(512*pfs->stBootSector.BPB_SecPerClus)+1;
        U32 q=startCluster/128;
        U32 r=startCluster%128;
        U32* pFATCache;
        U32 i=0;

        FATSector+=q;

        if(r>0) //aligned to a sector first
        {
            U32 fillCluster=128-r;
            BOOLEAN endInSector=FALSE;
            if(totalCluster<=fillCluster)
            {
                endInSector=TRUE;
                fillCluster=totalCluster;
            }

            pFATCache=msAPI_FS_Memory_Allocate(fillCluster*4);
            if(pFATCache==NULL)
            {
                __ASSERT(0);
                return;
            }
            for(i=0;i<fillCluster;i++)
            {
                startCluster+=1;
                pFATCache[i]=(startCluster);
            }

            if(endInSector)
                pFATCache[fillCluster-1]=endFlag;


            //printf("r=%lu,q=%lu,totalCluster=%lu,startCluster=%lu\n",r,q,totalCluster,startCluster);


            msAPI_MSDCtrl_SectorRead(deviceIndex, FATSector+relativeSector,1,DREC_RECORDER_FILE_CACHE);
            msAPI_FS_MIU_Copy(GET_DRAM_ADDR(pFATCache),DREC_RECORDER_FILE_CACHE+r*4,fillCluster*4);
            msAPI_MSDCtrl_SectorWrite(deviceIndex, FATSector+relativeSector,1,DREC_RECORDER_FILE_CACHE);
            msAPI_FS_Memory_Free(pFATCache);

            if(endInSector)
                return;

            FATSector+=1;
            totalCluster-=fillCluster;
        }

        //512 byte cluster one time
        pFATCache=msAPI_FS_Memory_Allocate(CACHE_CLUSTER_COUNT*512);
        if(pFATCache==NULL)
        {
            __ASSERT(0);
            return;
        }

        while(totalCluster>0)
        {
            FS_RESET_WDT();

            for(i=0;i<(CACHE_CLUSTER_COUNT*128);i++)
            {
                startCluster+=1;
                pFATCache[i]=(startCluster);
                totalCluster--;
                if(totalCluster==0)
                {
                    pFATCache[i]=endFlag;
                    i++;
                    break;
                }
            }

            msAPI_MSDCtrl_SectorRead(deviceIndex, FATSector+relativeSector,1,DREC_RECORDER_FILE_CACHE);
            msAPI_FS_MIU_Copy(GET_DRAM_ADDR(pFATCache),DREC_RECORDER_FILE_CACHE,i*4);
            msAPI_MSDCtrl_SectorWrite(deviceIndex, FATSector+relativeSector,1,DREC_RECORDER_FILE_CACHE);

            FATSector+=CACHE_CLUSTER_COUNT;

        }

        msAPI_FS_Memory_Free(pFATCache);
    }
}

static void _CreateDRECFileDirEntryInRoot(U8 deviceIndex,FAT_FileSysStruct* pfs,U8 fileNumber,U32 freeCluster)
{
    U32 rootSector;
    DirEntryStruct entry;
    U32 relativeSector=pfs->u32RelativeSector;

    memset(entry.pu8DirEntryName,0x20,8);
    entry.ps8DirEntryExtName[0]='T';
    entry.ps8DirEntryExtName[1]='R';
    entry.ps8DirEntryExtName[2]='P';

    if(fileNumber>9)
    {
        entry.pu8DirEntryName[0]=(U8)((fileNumber>>4)&0xF)+'0';
        entry.pu8DirEntryName[1]=(U8)(fileNumber&0xF)+'0';
    }
    else
    {
        entry.pu8DirEntryName[0]=(U8)(fileNumber&0xF)+'0';
    }

    entry.u8DirEntryAttrib=0;
    entry.u16DirEntryStartClusterLO=((U16)freeCluster);
    entry.u16DirEntryStartClusterHI=((U16)((freeCluster>>16)&0xFFFF));
    entry.u32DirEntryFileLength=0;

    rootSector=(U32)pfs->stBootSector.BPB_RsvdSecCnt+pfs->stBootSector.BPB_FATSz32*pfs->stBootSector.BPB_NumFATs+relativeSector;
    msAPI_MSDCtrl_SectorRead(deviceIndex,rootSector, 2, DREC_RECORDER_FILE_CACHE);

    msAPI_FS_MIU_Copy(GET_DRAM_ADDR(&entry),DREC_RECORDER_FILE_CACHE+(fileNumber-1)*sizeof(DirEntryStruct),sizeof(DirEntryStruct));
    msAPI_MSDCtrl_SectorWrite(deviceIndex,rootSector, 2, DREC_RECORDER_FILE_CACHE);
    //_MarkUsedCluster(deviceIndex, pfs, freeCluster, 0);

}

static U32 _GetFreeCluster(U8 deviceIndex,FAT_FileSysStruct* pfs)
{
    U32 result=0;
    U32 FATSector=pfs->stBootSector.BPB_RsvdSecCnt;
    U32 relativeSector=pfs->u32RelativeSector;
    U32* FATCache=msAPI_FS_Memory_Allocate(512);

    if(FATCache==NULL)
    {
        __ASSERT(0);
        return 0xFFFFFFFF;
    }

    while(FATSector < pfs->stBootSector.BPB_FATSz32)
    {
        U8 i=0;
        msAPI_MSDCtrl_SectorRead(deviceIndex, FATSector+relativeSector,1,DREC_RECORDER_FILE_CACHE);

        msAPI_FS_MIU_Copy(DREC_RECORDER_FILE_CACHE,GET_DRAM_ADDR(FATCache),512);

        FS_RESET_WDT();
        for(i=0;i<128;i++)
        {
            if((FATCache[i]&0xFFFFFF0F)==0)
                goto _FAT_OUT;
            result++;
        }
        FATSector++;
    }

_FAT_OUT:

    msAPI_FS_Memory_Free(FATCache);

    return result;
}

#if 0
U8 mApp_FileBrowser_GetFATType(S8 driveNo)
{

    FileSysStruct* pFS;
       pFS=msAPI_FCtrl_FileSysGet(driveNo);

       if( pFS== NULL)
           return 0;

       return pFS->stFAT.u8FATType;
}


U8 mApp_FileBrowser_GetSectorPerCluster(U8 driveNo)
{
    FileSysStruct* pFS;
    pFS=msAPI_FCtrl_FileSysGet(driveNo);

    if( pFS== NULL)
        return 0;

    return pFS->stBootSector.BPB_SecPerClus;
}
#endif

U32 msAPI_FCtrl_GetTotalSectors(U8 driveNo)
{
    FAT_FileSysStruct fs;

    if(!msAPI_FCtrl_FileSystemGetByID(driveNo,&fs))
        return 0;

    return fs.stFAT.u32FATTotalClusterNo* fs.stBootSector.BPB_SecPerClus;
}


BOOLEAN msAPI_FCtrl_CreateDRECFile(U8 driveNo,U8 fileNumber,U32* startCluster,U32* physicalSector)
{
    FAT_FileSysStruct fs;
    MSDCtrl_Drive drive;
    U32 freeCluster;
    printf("preparing DREC file: %bu.TRP\n",fileNumber);

    if(!msAPI_FCtrl_FileSystemGetByID(driveNo, &fs))
    {
        __ASSERT(0);
        return FALSE;
    }

    if(fs.stFAT.u8FATType!=FAT_TYPE_FAT32)
    {
        printf("DREC support FAT32 only!!\n");
        return FALSE;
    }

    if(fileNumber>99)
    {
        printf("root directory already has 99 more files!!\n");
        return FALSE;
    }

    if(!msAPI_FCtrl_GetDriveByIndex(driveNo,&drive))
    {
        __ASSERT(0);
        return FALSE;
    }

    freeCluster=_GetFreeCluster(drive.DeviceIndex,&fs);
    printf("freeCluster=0x%08lx\n",freeCluster);

    //4G limitiation check
    /*
    if((((0xFFFFFFFF>>9)/pFS->stBootSector.BPB_SecPerClus)+freeCluster)>pFS->stFAT.u32FATTotalClusterNo)
    {
       printf("there is no enough space!!\n");
       return FALSE;
    }
    */

    _CreateDRECFileDirEntryInRoot(drive.DeviceIndex,&fs,fileNumber,freeCluster);
    *physicalSector=(U32)fs.u32RelativeSector+fs.stBootSector.BPB_RsvdSecCnt+(U32)fs.stBootSector.BPB_NumFATs*fs.stBootSector.BPB_FATSz32+(freeCluster-2)*fs.stBootSector.BPB_SecPerClus;
    //printf("AA 0x%08lx, 0x%08lx, 0x%08lx, 0x%08lx, 0x%08lx, 0x%08lx\n",(U32)pFS->stPartitionTable.RelativeSector,(U32)pFS->stBootSector.BPB_RsvdSecCnt,(U32)pFS->stBootSector.BPB_NumFATs,(U32)pFS->stBootSector.BPB_FATSz32,(U32)freeCluster,(U32)pFS->stBootSector.BPB_SecPerClus);
    //printf("BB 0x%08lx\n",*physicalSector);
    *startCluster=freeCluster;

    return TRUE;
}

void msAPI_FCtrl_FinishDRECFile(U8 driveNo,U8 fileNumber,U32 startCluster,U32 len)
{
    FAT_FileSysStruct fs;
    MSDCtrl_Drive drive;
    U32 rootSector;
    DirEntryStruct entry;
    U32 relativeSector;


    printf("updating DREC file: %bu.TRP\n",fileNumber);
    if(!msAPI_FCtrl_FileSystemGetByID(driveNo, &fs))
        return;


    if(!msAPI_FCtrl_GetDriveByIndex(driveNo,&drive))
        return;

    relativeSector=fs.u32RelativeSector;

    rootSector=fs.stBootSector.BPB_RsvdSecCnt+fs.stBootSector.BPB_FATSz32*fs.stBootSector.BPB_NumFATs+relativeSector;

    msAPI_MSDCtrl_SectorRead(drive.DeviceIndex,rootSector, 2, DREC_RECORDER_FILE_CACHE);
    msAPI_FS_MIU_Copy(DREC_RECORDER_FILE_CACHE+(fileNumber-1)*sizeof(DirEntryStruct),GET_DRAM_ADDR(&entry),sizeof(DirEntryStruct));

    entry.u32DirEntryFileLength=(len);

    msAPI_FS_MIU_Copy(GET_DRAM_ADDR(&entry),DREC_RECORDER_FILE_CACHE+(fileNumber-1)*sizeof(DirEntryStruct),sizeof(DirEntryStruct));
    msAPI_MSDCtrl_SectorWrite(drive.DeviceIndex,rootSector, 2, DREC_RECORDER_FILE_CACHE);
    _MarkUsedCluster(drive.DeviceIndex, &fs, startCluster, len);


    printf("finish DREC file: %bu.TRP\n",fileNumber);
}
#endif // #if (ENABLE_DREC)


#if(FILE_SYSTEM_FORMAT_ENABLE)
static BOOLEAN FAT16_Format_BPB(U8 u8DeviceIndex, U32 u32RelativeSector, U32 u32TotalSec, U8 u8SecPerCluster, U32 *u32FATSize)
{
    U8 * pBPB;
    U32 temp;
    U16 u16FATSize;

    U8 u8Offset0_31[] = {0xEB, 0x3C, 0x90,      // 00-02 :BPB_jmpBoot
                                'M', 'S', 'D', 'O', 'S', '5', '.', '0',     // 03-10 :BS_OEMName
                                0, 0x02,    // 11-12 :BPB_BytsPerSec
                                0x10,       // 13    :BPB_SecPerClus
                                0x01, 0,    // 14-15 :BPB_RsvdSecCnt
                                0x02,       // 16    :BPB_NumFATs
                                0, 0x02,    // 17-18 :BPB_RootEntCnt
                                0, 0,       // 19-20 :BPB_TotSec16
                                0xF8,       // 21    :BPB_Media
                                0, 0,       // 22-23 :BPB_FATSz16
                                0x3F, 0,    // 24-25 :BPB_SecPerTrk
                                0xFF, 0,    // 26-27 :BPB_NumHeads
                                0, 0, 0, 0  // 28-31 :BPB_HiddSec
                                };

    U8 u8Offset39_61[] = {0x30, 0xC9, 0xC0, 0x10,   // 39-42 :BS_VolID
                                'N', 'O', ' ', 'N', 'A', 'M', 'E', ' ', ' ', ' ', ' ',  // 43-53 :BS_VolLab
                                'F', 'A', 'T', '1', '6', ' ', ' ', ' '};                // 54-63 :BS_FilSysType


    // get total size
    if(u32TotalSec == 0)
    {
        u32TotalSec = msAPI_MSDCtrl_GetBlockNum(u8DeviceIndex);
        FCTRL_DBG(1,printf("\n    Format TotalSec: 0x%08LX\n", u32TotalSec););
    }

    // get FAT size
    *u32FATSize = (u32TotalSec/256)/u8SecPerCluster +1;
    u16FATSize = (U16)(*u32FATSize);

    pBPB = (U8 xdata *)msAPI_FS_GetAddr(USB_IO_TEMP_ADDR);
    {
        memset((pBPB + 0), 0, 0x400);                         //Clean the memory : size 1024
        memcpy((pBPB + 0), u8Offset0_31, 32);                 //00-31
        memcpy((pBPB + 13), &u8SecPerCluster, 1);             //13    :BPB_SecPerClus
        memcpy((pBPB + 22), (U8 *)&u16FATSize, 2);   //22-23 :u16FATSize

        //0D Set Sector per Cluster, if u32TotalSec > 65535(32MB), offset 0x0D should be 0,
        //then record the u32TotalSec at offset 32-35
        if(u32TotalSec > 0xFFFF)
        {
            memcpy((pBPB + 32), (U8 *)&u32TotalSec, 4);  //20 Total Sector
        }
        else
        {
            FCTRL_DBG(1,printf("\n    TotalSecLo: %bd (0x%bX)\n", (U8)((u32TotalSec<<24)>>24),(U8)((u32TotalSec<<24)>>24)););
            FCTRL_DBG(1,printf("\n    TotalSecHi: %bd (0x%bX)\n", (U8)((u32TotalSec<<16)>>24),(U8)((u32TotalSec<<16)>>24)););
            memset((pBPB + 19), (U8)((u32TotalSec<<24)>>24), 1);
            memset((pBPB + 20), (U8)((u32TotalSec<<16)>>24), 1);
        }

        //Fat16 Structure Starting at Offset 36
        memset((pBPB + 36), 0x00, 1);   // 36 :BS_DrvNum
        memset((pBPB + 37), 0x00, 1);   // 37 :BS_Reserved1
        memset((pBPB + 38), 0x00, 1);   // 38 :BS_BootSig
        memcpy((pBPB + 39), u8Offset39_61, 23);

        //0xAA55 signature
        temp = 0xaa550000;
        memcpy((pBPB + 0x1FC), (U8 *)&temp, 4);
    }

  #if 0
    dumpMIU(USB_IO_TEMP_ADDR, 64);
  #else
    if(!msAPI_MSDCtrl_SectorWrite(u8DeviceIndex, u32RelativeSector, 2, USB_IO_TEMP_ADDR))
    {
        __ASSERT(0);
        return FALSE;
    }
  #endif

    return TRUE;
}

BOOLEAN msAPI_FCtrl_FAT16_Format(U8 driveNo)
{
    U8 u8DeviceIndex = 0;    // default
    U32 u32FATSize, u32TotalFATTableSec;
    U16 u16FatStartSec;
    U8 u8NumFATs;
    U8 *pu8Tmp;
    U32 u32WriteCount;
    U32 u32RelativeSector, u32TotalSec;
    U32 u32CurrentSector;
    U8 u8SecPerCluster = 8;
    U32 _time;
    //U32 u32Temp;

    // get u32RelativeSector
    if(!msAPI_MSDCtrl_SectorRead(u8DeviceIndex, 0, 1, USB_IO_TEMP_ADDR))
    {
        __ASSERT(0);
        return FALSE;
    }
    pu8Tmp = (U8 xdata* )msAPI_FS_GetAddr(USB_IO_TEMP_ADDR);

    if((*pu8Tmp == 0xEB) || (*pu8Tmp == 0xE9))
    {
        u32RelativeSector = 0;
        u32TotalSec = 0;
    }
    else
    {
        driveNo *= 0x10;
        if(*(pu8Tmp + 0x1C2 + driveNo)==0x01||*(pu8Tmp + 0x1C2 + driveNo)==0x04||*(pu8Tmp + 0x1C2 + driveNo)==0x06||*(pu8Tmp + 0x1C2 + driveNo)==0x0B||*(pu8Tmp + 0x1C2 + driveNo)==0x0C||*(pu8Tmp + 0x1C2 + driveNo)==0x0E||*(pu8Tmp + 0x1C2 + driveNo)==0x1C)
        {
            memcpy((U8 *)&u32RelativeSector, (pu8Tmp + 0x1C6 + driveNo), 4);
            memcpy((U8 *)&u32TotalSec, (pu8Tmp + 0x1CA + driveNo), 4);
            if(u32TotalSec == 0)
                u32RelativeSector = 0;
        }
        else
        {
            u32RelativeSector = 0;
            u32TotalSec = 0;
        }
    }

  #if 0       // for test
    printf("\nu32RelativeSector: %LX , u32TotalSec: %LX    ", u32RelativeSector, u32TotalSec);
    return TRUE;
  #endif


    if(driveNo)
    {
        if((0 == u32RelativeSector) || (0 == u32TotalSec))
            return FALSE;
    }

    FCTRL_DBG(1,printf("--- u32TotalSec = %lu\n",u32TotalSec););

    u16FatStartSec = 0x01;  // BPB_RsvdSecCnt
    u8NumFATs = 2;
    FAT16_Format_BPB(u8DeviceIndex, u32RelativeSector, u32TotalSec, u8SecPerCluster, &u32FATSize);

    u32TotalFATTableSec = (U32)u8NumFATs * u32FATSize;
    u32CurrentSector = u32RelativeSector + u16FatStartSec;
    //printf("\nu16FatStartSec: %X, u8NumFATs: %02bx, u32FATSize: %LX", u16FatStartSec, u8NumFATs, u32FATSize);

    pu8Tmp = (U8 xdata* )msAPI_FS_GetAddr(USB_IO_TEMP_ADDR);

    memset(pu8Tmp, 0, 0x1000);

    // clear up all FAT table
    u32WriteCount = 0;

    _time=msAPI_Timer_GetTime0();

    while(1)
    {
        if((u32WriteCount + 8) > u32TotalFATTableSec)
            break;

        if(!msAPI_MSDCtrl_SectorWrite(u8DeviceIndex, (U32)(u32CurrentSector+u32WriteCount), 0x8, USB_IO_TEMP_ADDR))
        {
            __ASSERT(0);
            return FALSE;
        }
        u32WriteCount +=0x8;

        if(msAPI_Timer_DiffTimeFromNow(_time)>3000)
        {
            FCTRL_DBG(1,printf("    .\n"););
            _time=msAPI_Timer_GetTime0();
        }

    }

    while(1)
    {
        if((u32WriteCount + 1) > u32TotalFATTableSec)
            break;

        if(!msAPI_MSDCtrl_SectorWrite(u8DeviceIndex, (U32)(u32CurrentSector+u32WriteCount), 1, USB_IO_TEMP_ADDR))
        {
            __ASSERT(0);
            return FALSE;
        }
        u32WriteCount ++;

    }

    FCTRL_DBG(1,printf("    Initial ROOT Dorectory...\n"););
    // init Root directory
    u32WriteCount = 0;
    FCTRL_DBG(1,printf("Root Start Sector = %lu\n",(U32)(u32CurrentSector+u32TotalFATTableSec + u32WriteCount)););
    {
        U8 u8RootSecCnt = 32;
        while(u8RootSecCnt >= 8)
        {
            if(!msAPI_MSDCtrl_SectorWrite(u8DeviceIndex, (U32)(u32CurrentSector+u32TotalFATTableSec + u32WriteCount), 8, USB_IO_TEMP_ADDR))
            {
                __ASSERT(0);
                return FALSE;
            }
            u8RootSecCnt -= 8;
           u32WriteCount += 8;
        }
        return TRUE;
    }
#if 0
    // init FAT table
    pu8Tmp = (U8 xdata* )msAPI_FS_GetAddr(USB_IO_TEMP_ADDR);
    memset(pu8Tmp, 0, 0x1000);
    //*((U32*)pu8Tmp ) = 0xF8FFFFFF;
    u32Temp = 0xF8FFFFFF;
    memcpy(pu8Tmp,&u32Temp,4);

    // FAT1
    FCTRL_DBG(1,printf("FAT 1 = %lu\n",(U32)u32CurrentSector););
    if(!msAPI_MSDCtrl_SectorWrite(u8DeviceIndex, (U32)u32CurrentSector, 1, USB_IO_TEMP_ADDR))
    {
        __ASSERT(0);
        return FALSE;
    }

    // FAT2
    FCTRL_DBG(1,printf("\nFAT 2 = %lu\n",(U32)(u32CurrentSector+u32FATSize)););
    if(!msAPI_MSDCtrl_SectorWrite(u8DeviceIndex, (U32)(u32CurrentSector+u32FATSize), 1, USB_IO_TEMP_ADDR))
    {
        __ASSERT(0);
        return FALSE;
    }

    return TRUE;
#endif
}

BOOLEAN msAPI_FCtrl_FormatPartitionByDriveIndex(EN_FORMAT_MODE formatMode,U8 u8DriveIndex)
{
    BOOLEAN bRet = FALSE;
    MSDCtrl_Drive target_drive;
    memset(&target_drive,0,sizeof(MSDCtrl_Drive));

    if(formatMode == FORMAT_COMPLETED)
    {
        bRet = FALSE;  //not support
    }
    else
    {
        if(!msAPI_FCtrl_GetDriveByIndex(u8DriveIndex, &target_drive))
        {
            bRet = FALSE;
        }

        if(target_drive.FileSystemType == FILE_SYSTEM_TYPE_FAT)
        {
            //FAT --> FAT32
            bRet = FAT_FastFormatByDriveIndex_enhance(target_drive);
        }
        else if(target_drive.FileSystemType == FILE_SYSTEM_TYPE_N51FS)
        {
            //NTFS --> FAT32
            bRet = FAT_FastFormatByDriveIndex_enhance(target_drive);
        }
        else
        {
            bRet = FALSE;  //not support
        }
    }

    return bRet;
}
#endif // #if(FILE_SYSTEM_FORMAT_ENABLE)

EN_FILE_SYSTEM_FORMAT msAPI_FCtrl_GetFileSystemFormatByDriveIndex(U8 u8DriveIndex)
{
    EN_FILE_SYSTEM_FORMAT eFSFormat=FILE_SYSTEM_FORMAT_UNKNOW;
    FAT_FileSysStruct *pFsStruct;

    pFsStruct = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8DriveIndex);

    if(pFsStruct->FileSystemType == FILE_SYSTEM_TYPE_FAT)
    {
        EN_FAT_TYPE eFatType;

        eFatType = pFsStruct->stFAT.u8FATType;

        if(eFatType == FAT_TYPE_FAT12)
        {
            eFSFormat = FILE_SYSTEM_FORMAT_FAT12;
        }
        else if(eFatType == FAT_TYPE_FAT16)
        {
            eFSFormat = FILE_SYSTEM_FORMAT_FAT16;
        }
        else if(eFatType == FAT_TYPE_FAT32)
        {
            eFSFormat = FILE_SYSTEM_FORMAT_FAT32;
        }
    }
    else if(pFsStruct->FileSystemType == FILE_SYSTEM_TYPE_NTFS)
    {
        eFSFormat = FILE_SYSTEM_FORMAT_NTFS;
    }

    return eFSFormat;
}


/*************************************************************************************************************/
#undef   MSAPI_FCTRL_C

