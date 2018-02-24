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
#define MSAPI_PVR_FILE_SYSTEM_C

#if 1//ndef ATSC_SYSTEM //do not support ATSC now, sicne subtitle issue needs to be fixed

#include <string.h>
#include <ctype.h>
#include "datatype.h"
#include "IOUtil.h"
#include "msAPI_Timer.h"
#include "msAPI_PVRFileSystem.h"
#include "MApp_GlobalVar.h"

//N51FS Related
#include "msAPI_BulkFileSystem.h"

#if 1//ndef OBAMA
#include "msAPI_MSDCtrl.h"
#include "msAPI_FCtrl.h"
#include "msAPI_FAT.h"
#ifdef PVR_8051 //[8051]
#include "msAPI_NTFS.h"
#else
#include "msAPI_N51FS.h"
#endif
#else
#include "debug.h"
#include "N51FS_Wrapper.h"
#include "Linux_format_warp.h"
#endif //#ifndef OBAMA

#include "FSUtil.h"
#include "MApp_UiPvr.h"
#include "MApp_MassStorage.h"

//Porting Related
#ifdef PVR_8051 //[8051]
  #define PVRFSSwap32(a) Swap32(a)
  //#define BKFSSwap16(a) Swap16(a)
#else //[aron or mips]
  #if 1//defined(MIPS_CHAKRA) || defined(ARM_CHAKRA)
    //#define msAPI_FS_MIU_Copy(a, b, c) memcpy((void*)_PA2VA(b), (void*)_PA2VA(a), c)
  #endif
  #define msAPI_FS_GetXData(a) msAPI_FS_GetAddr((a)<<12)
  #define FAT_ReturnXData()
  #define msAPI_FS_ReturnXData()
  //#define FAT_File_GetHandleXData(a) FAT_File_GetHandleInfo(a)
  #define FCtrl_GetFileSystemXData(a) FCtrl_GetFileSystemInfo(a)
  //#define FCtrl_GetFatTableCacheXData(a) FCtrl_GetFatTableCacheInfo(a)
  #define FS_ByteSwapCopy(a, b, c) memcpy(a, b, c)
  #define PVRFSSwap32(a) ((U32)(a))
  //#define BKFSSwap16(a) ((U16)(a))
#endif

/*******************************************************/
/****************** Global Variables *******************/
/*******************************************************/
#define PVRFSDBG(x)                           //(x)
#define MAX_PARTITION_COUNT                   4
#define FAT_WRITE_SECTOR_CNT                  8
#define FAT_WRITE_SECTOR_CNT_PER_SECTION      512 //if reach write-count, return to UI to draw progress bar
#define FAT_AVERAGE_READ_WRITE_KBYTES         0x80 //128 KBytes
#define FAT_DEFAULT_DISK_SPEED_KBYTES_PER_SEC 2048 //2048 KBytes/sec
#define BYTES_PER_KBYTES                      1024
#define KBYTES_PER_MEGA                       1024

#if ENABLE_PVR

U16 g_u16DiskSpeed = FAT_DEFAULT_DISK_SPEED_KBYTES_PER_SEC;

/****************** Environment Handle *****************/
static EN_PVRFS_FSTYPE _enPVRFSFileSystemType = PVR_FS_BULKFS;
static U8 _u8DiskDriveIndex = INVALID_DRIVE_INDEX;
static U8 _u8DeviceIndex = INVALID_DEVICE_INDEX;
static BOOLEAN _bPVRFSInitialized = FALSE;

/********************* Disk Related ********************/
static U32 _u32DiskFreeSizeKB = 0;
static LongLong _llTotalRecordedSize;
static U32 MaxRecordSize = 512; // Default Timeshift 512MB


/********************* FAT Related *********************/
static U32 g_DriveFATSectors = 0;
#ifndef OBAMA
static U32 g_u32RelativeSector = 0xFFFFFFFF; //Only for format FAT
#endif

/*******************************************************/
/****************** Global Functions *******************/
/*******************************************************/

/****************** Environment Handle *****************/
BOOLEAN msAPI_PVRFS_SetFileSystemType(EN_PVRFS_FSTYPE type)
{
    if (type >= PVR_FS_MAX)
        return FALSE;
    else _enPVRFSFileSystemType = type;

    return TRUE;
}

EN_PVRFS_FSTYPE msAPI_PVRFS_GetFileSystemType(void)
{
    return _enPVRFSFileSystemType;
}

BOOLEAN msAPI_PVRFS_IsLinuxFileSystemType(EN_PVRFS_FSTYPE enPVRFSFileSystemType)
{
    switch(enPVRFSFileSystemType)
    {
        case PVR_FS_LINUX_FAT:
        case PVR_FS_LINUX_NTFS:
        case PVR_FS_LINUX_EXT2:
        case PVR_FS_LINUX_EXT3:
        {
            return TRUE;
        }
        default:
        {
            return FALSE;
        }
    }
    return FALSE;
}

BOOLEAN msAPI_PVRFS_SetDeviceIndex(U8 u8DeviceIndex)
{
    if (u8DeviceIndex == INVALID_DEVICE_INDEX)
    {
        __ASSERT(0);
        return FALSE;
    }

    _u8DeviceIndex = u8DeviceIndex;
#ifndef OBAMA
    //if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
    return msAPI_BKFS_SetDeviceIndex(u8DeviceIndex);
#endif
    return TRUE;
}

BOOLEAN msAPI_PVRFS_SetDiskDriveIndex(U8 u8DriveIndex)
{
#ifndef OBAMA
    U8 u8EnvironmentID;
    U8 fsid;
    U8 u8NumFATs;
    U32 u32FATSize;
    FAT_FileSysStruct* pFAT_FileSys;
#endif

    if (u8DriveIndex >= DISK_DRIVE_NUM)
    {
        __ASSERT(0);
        g_DriveFATSectors = 0;
        return FALSE;
    }

#ifndef OBAMA
    _u8DiskDriveIndex = u8DriveIndex;
    if ((_enPVRFSFileSystemType == PVR_FS_BULKFS) || (_enPVRFSFileSystemType == PVR_FS_N51FAT32))
    {
        _u8DiskDriveIndex = u8DriveIndex;
        if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
            msAPI_BKFS_SetDiskDriveIndex(u8DriveIndex);

        u8EnvironmentID = msAPI_FSEnv_Register(u8DriveIndex);
        if(u8EnvironmentID==INVALID_FS_ENVIRONMENT_INDEX)
        {
            //__ASSERT(0);
            g_DriveFATSectors = 0;
            return FALSE;
        }

        fsid = msAPI_FSEnv_GetEnvironment(u8EnvironmentID)->u8FileSystemID;
        pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemXData(fsid);
        if (pFAT_FileSys == NULL)
        {
            g_DriveFATSectors = 0;
        }
        else
        {
            u8NumFATs = pFAT_FileSys->stBootSector.BPB_NumFATs;
            u32FATSize = pFAT_FileSys->stBootSector.BPB_FATSz32;
            g_DriveFATSectors = (U32)u8NumFATs * u32FATSize;
        }
        FAT_ReturnXData();
        msAPI_FSEnv_UnRegister(u8EnvironmentID);

        PVRFSDBG(printf("Set BKFS DiskDriveIndex=%bu\n",_u8DiskDriveIndex));
        return TRUE;
    }
    return FALSE;

#else
    _u8DiskDriveIndex = u8DriveIndex;
    return TRUE;
#endif
}

U8 msAPI_PVRFS_GetDriveIndex(void)
{
    return _u8DiskDriveIndex;
}

U8 msAPI_PVRFS_GetDeviceIndex(void)
{
    return _u8DeviceIndex;
}

static BOOLEAN PVRFS_PrepareDrive(void)
{
#ifdef OBAMA
    //do nothing here.
    return TRUE;
#else
    U8 i=0;

    if(!msAPI_FCtrl_IsDriveMounted(_u8DiskDriveIndex))
    {
        msAPI_MSDCtrl_CheckDevices();

        if(msAPI_PVRFS_GetDeviceIndex()==INVALID_DEVICE_INDEX)
        {
            for(i=0;i<STORAGE_DEVICE_NUM;i++)
            {
                if(msAPI_MSDCtrl_GetDeviceStatus(i)==MSD_STATUS_INSERTED)
                {
                    if (!msAPI_PVRFS_SetDeviceIndex(i))
                    {
                        __ASSERT(0);
                        return FALSE;
                    }
                }
            }
        }

        if(msAPI_MSDCtrl_GetDeviceStatus(msAPI_PVRFS_GetDeviceIndex())==MSD_STATUS_INSERTED)
        {
            if(!msAPI_FCtrl_ActiveDevice(msAPI_PVRFS_GetDeviceIndex()))
            {
                __ASSERT(0);
                return FALSE;
            }
        }
        else
        {
            return FALSE;
        }

    }
    return TRUE;
#endif
}

static BOOLEAN PVRFS_DiskDriveInitiate(void)
{
    if (!PVRFS_PrepareDrive())
    {
        //__ASSERT(0);
    }
    else
    {
        if(_u8DiskDriveIndex == INVALID_DRIVE_INDEX)
        {
            U8 i;
            for(i=0; i<DISK_DRIVE_NUM; i++)
            {
                if(msAPI_FCtrl_IsDriveMounted(i))
                {
                    _u8DiskDriveIndex = i;
                    break;
                }
            }
        }
        if(_u8DiskDriveIndex == INVALID_DRIVE_INDEX)
        {
            return FALSE;
        }
        return TRUE;
    }

    return FALSE;
}

static BOOLEAN PVRFS_CreatePVRDirectory(void)
{
    FileEntry entry;
    U16 PVRFolderName[]={'_','M','S','T','P','V','R',0};
    U8 u8PVRFolderLength = FS_strlen_U(PVRFolderName);
    U8 u8EnvironmentID = msAPI_FSEnv_Register(_u8DiskDriveIndex);

    if(u8EnvironmentID==INVALID_FS_ENVIRONMENT_INDEX)
    {
        __ASSERT(0);
        return FALSE;
    }

    if(!msAPI_FCtrl_DirectoryChangeToRoot(u8EnvironmentID))
    {
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        __ASSERT(0);
        return FALSE;
    }

    //check if the forlder _MSTBKFS existed or not
    if(msAPI_FCtrl_EntrySearchByName(u8EnvironmentID, PVRFolderName , u8PVRFolderLength, &entry))
    {
        //if (entry.EntryAttrib == FAT_ATTRIB_DIRECTORY)
        if(entry.EntryType == ENTRY_TYPE_DIR)
        {
            msAPI_FSEnv_UnRegister(u8EnvironmentID);
            return TRUE;
        }
    }

    if (!msAPI_FCtrl_DirectoryCreate(u8EnvironmentID, PVRFolderName, u8PVRFolderLength))
    {
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        __ASSERT(0);
        return FALSE;
    }

    msAPI_FSEnv_UnRegister(u8EnvironmentID);
    return TRUE;
}

BOOLEAN msAPI_PVRFS_IsInitialized(void)
{
    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
    {
#ifndef OBAMA
        return msAPI_BKFS_IsInitialized();
#endif
    }
    else if ((_enPVRFSFileSystemType == PVR_FS_N51FAT32) || (msAPI_PVRFS_IsLinuxFileSystemType(_enPVRFSFileSystemType)))
    {
        if ((_u8DiskDriveIndex < DISK_DRIVE_NUM) && (_u8DeviceIndex != INVALID_DEVICE_INDEX))
            return _bPVRFSInitialized;
    }

    return FALSE;
}

void msAPI_PVRFS_Reset(void)
{
    _enPVRFSFileSystemType = PVR_FS_BULKFS;
	_bPVRFSInitialized = FALSE;
}

BOOLEAN msAPI_PVRFS_Initial(BOOLEAN force)
{
    if(_bPVRFSInitialized)
    {
        if (force)
        {
            _bPVRFSInitialized = FALSE;
            if(g_bPvrChgSrcInitFs)
            {
                msAPI_FS_Init();
                g_bPvrChgSrcInitFs = 0;
            }
        }
        else if (_enPVRFSFileSystemType == PVR_FS_N51FAT32)
        {
            return TRUE;
        }
    }
#ifndef OBAMA
    //detect BKFS
    //if BULK exists but the version is out of date, can not be found here.
    if (msAPI_BKFS_Initial(force))
    {
        _enPVRFSFileSystemType = PVR_FS_BULKFS;
        _bPVRFSInitialized = TRUE;
        PVRFSDBG(printf("Initiate BKFS successly\n"));
        return TRUE;
    }
    else //detect N51FS_FAT32
    {
        //check N51FS FAT32 file system
        U8 u8EnvironmentID;
        FS_EnvironmentStruct* pFS_Env;

        u8EnvironmentID = msAPI_FSEnv_Register(_u8DiskDriveIndex);
        if(u8EnvironmentID==INVALID_FS_ENVIRONMENT_INDEX)
        {
            __ASSERT(0);
            return FALSE;
        }

        pFS_Env = msAPI_FSEnv_GetEnvironment(u8EnvironmentID);
        if (!pFS_Env)
        {
            __ASSERT(0);
            msAPI_FSEnv_UnRegister(u8EnvironmentID);
            return FALSE;
        }

        if (pFS_Env->u8FileSystemType == FILE_SYSTEM_TYPE_FAT) // FAT16/FAT32
        {
            if (PVRFS_DiskDriveInitiate())
            {
                U32 u32CurrentDiskFreeSizeMB;
                _enPVRFSFileSystemType = PVR_FS_N51FAT32;
                _u32DiskFreeSizeKB = 0;
                _llTotalRecordedSize.Lo = 0;
                _llTotalRecordedSize.Hi = 0;
                g_u16DiskSpeed = FAT_DEFAULT_DISK_SPEED_KBYTES_PER_SEC;
                if (!PVRFS_CreatePVRDirectory())
                {
                    msAPI_FSEnv_UnRegister(u8EnvironmentID);
                    return FALSE;
                }
                u32CurrentDiskFreeSizeMB = msAPI_PVRFS_GetDriveFreeSpaceMB(); //detect free space
                _bPVRFSInitialized = TRUE;
                msAPI_FSEnv_UnRegister(u8EnvironmentID);
                PVRFSDBG(printf("Initiate N51FS FAT32 successly, _u32DiskFreeSizeKB is %ld\n", _u32DiskFreeSizeKB));
                return TRUE;
            }
        }
        else{
            _bPVRFSInitialized = FALSE;
            _enPVRFSFileSystemType = PVR_FS_LINUX_UNSUPPORTED;
        }
        FAT_ReturnXData();
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
    }
#else
    if (PVRFS_DiskDriveInitiate())
    {
        U32 u32CurrentDiskFreeSizeMB = 0;
        U8 u8EnvironmentID = msAPI_FSEnv_Register(_u8DiskDriveIndex);
        FS_EnvironmentStruct* pFS_Env;

        //set file system
        if(u8EnvironmentID == INVALID_FS_ENVIRONMENT_INDEX)
        {
            __ASSERT(0);
            return FALSE;
        }
        pFS_Env = msAPI_FSEnv_GetEnvironment(u8EnvironmentID);
        if (!pFS_Env)
        {
            __ASSERT(0);
            msAPI_FSEnv_UnRegister(u8EnvironmentID);
            return FILE_SYSTEM_TYPE_ERROR;
        }
        if (pFS_Env->u8FileSystemType == FILE_SYSTEM_TYPE_FAT) // FAT16/FAT32
            _enPVRFSFileSystemType = PVR_FS_LINUX_FAT;
        else if (pFS_Env->u8FileSystemType == FILE_SYSTEM_TYPE_NTFS) // NTFS
            _enPVRFSFileSystemType = PVR_FS_LINUX_NTFS;
        else if (pFS_Env->u8FileSystemType == FILE_SYSTEM_TYPE_EXT2) // EXT2
            _enPVRFSFileSystemType = PVR_FS_LINUX_EXT2;
        else if (pFS_Env->u8FileSystemType == FILE_SYSTEM_TYPE_EXT3) // EXT3
            _enPVRFSFileSystemType = PVR_FS_LINUX_EXT3;
        else _enPVRFSFileSystemType = PVR_FS_LINUX_UNSUPPORTED; // Others
        msAPI_FSEnv_UnRegister(u8EnvironmentID);

        //init static variables
        _u32DiskFreeSizeKB = 0;
        _llTotalRecordedSize.Lo = 0;
        _llTotalRecordedSize.Hi = 0;

        //create default PVR directory
        if (!PVRFS_CreatePVRDirectory())
            return FALSE;

        //get free space
        u32CurrentDiskFreeSizeMB = msAPI_PVRFS_GetDriveFreeSpaceMB(); //detect free space

        //init. successfully
        _bPVRFSInitialized = TRUE;
        PVRFSDBG(printf("Initiate LINUX file system successly, _u32DiskFreeSizeKB is %d\n", _u32DiskFreeSizeKB));
        return TRUE;
    }
#endif

    return FALSE;
}

BOOLEAN msAPI_PVRFS_SetMemory(U32 poolAddress,U32 len)
{
    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
    {
#ifndef OBAMA
        return msAPI_BKFS_SetMemory(poolAddress, len);
#else
        UNUSED(poolAddress);
        UNUSED(len);
#endif
    }

    return TRUE; //Always return true for nonBKFS.
}
//]
/******************** Disk ***********************************************************************/
//get remnant free space of current disk
U32 msAPI_PVRFS_GetDriveFreeSpaceMB(void)
{
    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
    {
#ifndef OBAMA
        return msAPI_BKFS_GetDriveFreeSpaceMB();
#endif
    }
    else if (_enPVRFSFileSystemType == PVR_FS_N51FAT32)
    {
#ifndef OBAMA
        if (msAPI_PVRFS_IsInitialized())
        {
            LongLong llTotalRecordedSizeKB;
            llTotalRecordedSizeKB = LL_LongDivU32(&_llTotalRecordedSize, BYTES_PER_KBYTES);
            return ((_u32DiskFreeSizeKB - llTotalRecordedSizeKB.Lo)/KBYTES_PER_MEGA);
        }
        else
        {
            _u32DiskFreeSizeKB = FAT_FAT32_GetUnusedSizeInKB(_u8DiskDriveIndex);
            return (_u32DiskFreeSizeKB/KBYTES_PER_MEGA);
        }
#endif
    }
    else if (msAPI_PVRFS_IsLinuxFileSystemType(_enPVRFSFileSystemType))
    {
        if (msAPI_PVRFS_IsInitialized())
        {
            LongLong llTotalRecordedSizeKB;
            llTotalRecordedSizeKB = LL_LongDivU32(&_llTotalRecordedSize, BYTES_PER_KBYTES);
            return ((_u32DiskFreeSizeKB - llTotalRecordedSizeKB.Lo)/KBYTES_PER_MEGA);
        }
        else
        {
            _u32DiskFreeSizeKB = msAPI_FCtrl_GetUnusedSizeInKB_ByDriveIndex(_u8DiskDriveIndex);
            return (_u32DiskFreeSizeKB/KBYTES_PER_MEGA);
        }
    }

    return 0;
}

//get total space of current disk
U32 msAPI_PVRFS_GetAvailableDiskSizeMB(U8 u8EnvironmentID)
{
#ifndef OBAMA
    FS_EnvironmentStruct* pFS_Env;
    FAT_FileSysStruct* pFAT_FileSys;
    #ifdef PVR_8051 //[8051]
    NTFS_FileSysStruct *pNTFS_FileSys;
    #else
    N51FS_FileSysStruct *pN51FS_FileSys;
    #endif

    U32 u32AvailableDiskSizeMB = 0;
    U32 u32TotalSectors = 0;
    U16 u16BytesPerSector = 0;

    if (u8EnvironmentID >= FS_ENVIRONMENT_NUM)
    {
        __ASSERT(0);
        return 0;
    }

    if ((_enPVRFSFileSystemType == PVR_FS_BULKFS) || (_enPVRFSFileSystemType == PVR_FS_N51FAT32) ||
        (_enPVRFSFileSystemType == PVR_FS_LINUX_UNSUPPORTED)) //other format -> FAT32 or BULK
    {
        pFS_Env = msAPI_FSEnv_GetEnvironment(u8EnvironmentID);
        if (!pFS_Env) return 0;

        if(FILE_SYSTEM_TYPE_FAT==pFS_Env->u8FileSystemType)
        {
            pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemXData(pFS_Env->u8FileSystemID);
            if (!pFAT_FileSys) return 0;

            u32TotalSectors = pFAT_FileSys->stBootSector.BPB_TotSec32;
            u16BytesPerSector = pFAT_FileSys->stBootSector.BPB_BytsPerSec;
        }
        #ifdef PVR_8051 //[8051]
        else if(FILE_SYSTEM_TYPE_NTFS==pFS_Env->u8FileSystemType)
        {
             pNTFS_FileSys=(NTFS_FileSysStruct*)FCtrl_GetFileSystemXData(pFS_Env->u8FileSystemID);
             if (!pNTFS_FileSys) return 0;
             u32TotalSectors = pNTFS_FileSys->TotalSectors;
             u16BytesPerSector = pNTFS_FileSys->BytesPerSector;
        }
        #else
        else if(FILE_SYSTEM_TYPE_N51FS==pFS_Env->u8FileSystemType)
        {
             pN51FS_FileSys=(N51FS_FileSysStruct*)FCtrl_GetFileSystemXData(pFS_Env->u8FileSystemID);
             if (!pN51FS_FileSys) return 0;
             u32TotalSectors = pN51FS_FileSys->TotalSectors;
             u16BytesPerSector = pN51FS_FileSys->BytesPerSector;
        }

        #endif
        else u32TotalSectors = u16BytesPerSector = 0;

        u32AvailableDiskSizeMB = (U32)((((u32TotalSectors/BYTES_PER_KBYTE)*u16BytesPerSector)/BYTES_PER_KBYTE));
        FAT_ReturnXData();
        return u32AvailableDiskSizeMB;
    }
#endif
    if (msAPI_PVRFS_IsLinuxFileSystemType(_enPVRFSFileSystemType))
    {
        UNUSED(u8EnvironmentID);
        if (msAPI_PVRFS_IsInitialized())
        {
            return (msAPI_FCtrl_GetTotalSizeInKB_ByDriveIndex(_u8DiskDriveIndex)/KBYTES_PER_MEGA);
        }
    }

    return 0;
}

BOOLEAN msAPI_PVRFS_IsDeviceRAWDisk(U8 u8DeviceIndex)
{
    U8 u8DriveId;
    U8 u8DriveCnt;
    MSDCtrl_Drive driveInfo;
    memset(&driveInfo,0,sizeof(MSDCtrl_Drive));

    if ((_enPVRFSFileSystemType == PVR_FS_BULKFS) || (_enPVRFSFileSystemType == PVR_FS_N51FAT32) ||
        (msAPI_PVRFS_IsLinuxFileSystemType(_enPVRFSFileSystemType)))
    {
        if (INVALID_DEVICE_INDEX == u8DeviceIndex)
        {
            __ASSERT(0);
            return FALSE;
        }
        if(msAPI_MSDCtrl_GetDeviceStatus(u8DeviceIndex) == MSD_STATUS_ERROR)
        {
            msAPI_MSDCtrl_ResetDevice(u8DeviceIndex);
            msAPI_MSDCtrl_CheckDevices();
        }
        if(msAPI_MSDCtrl_GetDeviceStatus(u8DeviceIndex)!=MSD_STATUS_INSERTED)
            return FALSE;
        #ifdef ENABLE_PTP
        if(msAPI_MSDCtrl_GetDeviceClass(u8DeviceIndex) != USB_CLASS_MSD)
            return FALSE;
        #endif

        u8DriveCnt = msAPI_FCtrl_GetDriveCount();
        for( u8DriveId=0; u8DriveId<u8DriveCnt; u8DriveId++)
        {
            if(msAPI_FCtrl_GetDriveByIndex(u8DriveId, &driveInfo) == FALSE)
                continue;
            if(driveInfo.DriveIndex == u8DeviceIndex)
                return FALSE;
        }
        return TRUE;
    }

    return FALSE;
}


/******************** FAT Table ******************************************************************/
#ifndef OBAMA
static BOOLEAN PVRFS_FAT_Format_BPB(U8 u8DeviceIndex, U32 u32RelativeSector, U32 u32TotalSec, U8* u8SecPerCluster, U32 *u32FATSize)
{
    U8 * pBPB;
    U16 u16BytesPerSec;
    U32 /*addr,*/ temp;
    U8 u8Offset0_31[] = {0xEB, 0x58, 0x90,  // BPB_jmpBoot
                                'M', 'S', 'D', 'O', 'S', '5', '.', '0',     // BS_OEMName
                                0, 2,       // BPB_BytsPerSec
                                0x08,       // BPB_SecPerClus
                                0x20, 0,    // BPB_RsvdSecCnt
                                2,          // BPB_NumFATs
                                0, 0, 0, 0, 0xF8, 0, 0, 0x3F, 0, 0xFF, 0, 0, 0, 0, 0};

    U8 u8Offset40_89[] = {0, 0, 0, 0,
                                2, 0, 0, 0, // BPB_RootClus
                                1, 0, 6, 0,
                                0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,    // BPB_Reserved
                                0, 1, 0x29,
                                0x30, 0xC9, 0xC0, 0x10,    // BS_VolID
                                'N', 'O', ' ', 'N', 'A', 'M', 'E', ' ', ' ', ' ', ' ',    // BS_VolLab
                                'F', 'A', 'T', '3', '2', ' ', ' ', ' '};    // BS_FilSysType


    // get total size
    if(u32TotalSec == 0)
    {
        u32TotalSec = msAPI_MSDCtrl_GetBlockNum(u8DeviceIndex);
        PVRFSDBG(printf("\n    Format TotalSec: 0x%08LX", u32TotalSec));
    }
    u16BytesPerSec = msAPI_MSDCtrl_GetBlockSize(u8DeviceIndex);
    if(u16BytesPerSec == 0)
    {
        u16BytesPerSec = 0x200;
    }
    u8Offset0_31[11] = (u16BytesPerSec&0xFF);
    u8Offset0_31[12] = (u16BytesPerSec >> 8);

    PVRFSDBG(printf("MSD block number = 0x%x\n", msAPI_MSDCtrl_GetBlockNum(u8DeviceIndex)));
    PVRFSDBG(printf("MSD block size = 0x%x\n", msAPI_MSDCtrl_GetBlockSize(u8DeviceIndex)));
    PVRFSDBG(printf("\n    Format TotalSec: 0x%08LX [%lu]", u32TotalSec,u32TotalSec));

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
    PVRFSDBG(printf("PVRFS_FAT_Format_BPB : u8SecPerCluster[%bd], u32FATSize[%lu]",*u8SecPerCluster, u32FATSize));

    //addr = (USB_IO_TEMP_ADDR>>12);
    //pBPB = (U8 xdata *)msAPI_FS_GetXData(addr);
    pBPB = (U8 xdata *)msAPI_FS_GetXData(USB_IO_TEMP_ADDR>>12);
    {
        memset((pBPB + 0), 0, 0x400);
        memcpy((pBPB + 0), u8Offset0_31, 32);
        memcpy((pBPB + 0xD), u8SecPerCluster, 1);
        FS_ByteSwapCopy((pBPB + 0x20), (U8 *)&u32TotalSec, 4);
        FS_ByteSwapCopy((pBPB + 0x24), (U8 *)u32FATSize, 4);
        memcpy((pBPB + 0x28), u8Offset40_89, 50);
        temp = 0xaa550000;
        FS_ByteSwapCopy((pBPB + 0x1FC), (U8 *)&temp, 4);

        // setup FSI_LeadSig, FSI_StrucSig, FSI_TrailSig
        temp = 0x41615252;
        FS_ByteSwapCopy((pBPB + 0x200), (U8 *)&temp, 4);
        temp = 0x61417272;
        FS_ByteSwapCopy((pBPB + 0x3E4), (U8 *)&temp, 4);
        temp = 0xFFFFFFFF;
        FS_ByteSwapCopy((pBPB + 0x3E8), (U8 *)&temp, 4);
        temp = 0x2;
        FS_ByteSwapCopy((pBPB + 0x3EC), (U8 *)&temp, 4);
        temp = 0xaa550000;
        FS_ByteSwapCopy((pBPB + 0x3FC), (U8 *)&temp, 4);
    }
    msAPI_FS_ReturnXData();

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

static BOOLEAN PVRFS_Probe_BPB(U8 u8DeviceIndex, U32 u32RelativeSector,
                                                                 U16*pu16ReservedSectors, U8 *pu8NumFATs,  U8* pu8SecPerCluster, U32 *pu32TotalSec, U32 *pu32FATSize)
{
    //U32 addr;
    U8 *pBPB;

    if(!msAPI_MSDCtrl_SectorRead(u8DeviceIndex, u32RelativeSector, 1, USB_IO_TEMP_ADDR))
    {
        __ASSERT(0);
        return FALSE;
    }
    //addr = (USB_IO_TEMP_ADDR>>12);
    //pBPB = (U8 xdata *)msAPI_FS_GetXData(addr);
    pBPB = (U8 xdata *)msAPI_FS_GetXData(USB_IO_TEMP_ADDR>>12);

    ///check if this is an valid FAT32 BPB
    if(pBPB[0]!=0xEB || pBPB[2]!=0x90 ||
        pBPB[82]!='F' || pBPB[84]!='T'|| pBPB[86]!='2')
    {
         __ASSERT(0);
          msAPI_FS_ReturnXData();
         return FALSE;
    }
     if(pu8NumFATs)
             *pu8NumFATs = *(pBPB + 0x10);
     if(pu8SecPerCluster)
             *pu8SecPerCluster= *(pBPB + 0xD);
    if(pu16ReservedSectors)
         FS_ByteSwapCopy((U8 *)pu16ReservedSectors, (pBPB + 0x0E),  2);
    if(pu32TotalSec)
         FS_ByteSwapCopy((U8 *)pu32TotalSec, (pBPB + 0x20),  4);
    if(pu32FATSize)
         FS_ByteSwapCopy ((U8 *)pu32FATSize, (pBPB + 0x24), 4);

    msAPI_FS_ReturnXData();

    return TRUE;
}

//u32WriteCount need to start from 0, or it will not format BPB.
static BOOLEAN PVRFS_FAT_Format(U32 u32MBRLogicBlockAddress, U8 u8IndexInMBR, U32* u32WriteCount, BOOLEAN* bFinished)
{
    U8 u8DeviceID = msAPI_BKFS_GetDeviceIndex();    // default
    U8 u8NumFATs;
    U8 *pu8Tmp;
    U8 u8SecPerCluster = 0; // 0->dynamic detect
    //U32 addr = (USB_IO_TEMP_ADDR>>12);
    U32 u32CurrentSector;
    U16 u16ReservedSectors;
    U32 u32FATSize, u32TotalFATTableSec;
    U32 u32FATClearCnt = 0;
    U32 u32TotalSec;
    U32 u32ClusterID;
    U32 u16IndexInMBR = u8IndexInMBR;


    msAPI_FCtrl_UnmountDrivesOnDevice(u8DeviceID);

    if(u8IndexInMBR >= MAX_PARTITION_COUNT && u8IndexInMBR!=INVALID_MBR_INDEX)
    {
        __ASSERT(0);
        return FALSE;
    }


    *bFinished = FALSE;
    // step1: get u32RelativeSector & format BPB
    if (*u32WriteCount == 0)
    {
        U32 u32RelativeSector;

        if(u32MBRLogicBlockAddress != INVALID_MBR_ADDRESS)
        {

            if(!msAPI_MSDCtrl_SectorRead(u8DeviceID, u32MBRLogicBlockAddress, 1, USB_IO_TEMP_ADDR))
            {
                __ASSERT(0);
                return FALSE;
            }
            //pu8Tmp = (U8 xdata* )msAPI_FS_GetXData(addr);
            pu8Tmp = (U8 xdata* )msAPI_FS_GetXData(USB_IO_TEMP_ADDR>>12);
            if(u8IndexInMBR>=MAX_PARTITION_COUNT)
            {
                u32RelativeSector = 0;
                u32TotalSec = 0;
            }
            else
            {
                u16IndexInMBR *= 0x10;
                if(*(pu8Tmp + 0x1C2 + u16IndexInMBR)==0x01||*(pu8Tmp + 0x1C2 + u16IndexInMBR)==0x04||*(pu8Tmp + 0x1C2 + u16IndexInMBR)==0x06
                    ||*(pu8Tmp + 0x1C2 + u16IndexInMBR)==0x07
                    ||*(pu8Tmp + 0x1C2 + u16IndexInMBR)==0x0B||*(pu8Tmp + 0x1C2 + u16IndexInMBR)==0x0C||*(pu8Tmp + 0x1C2 + u16IndexInMBR)==0x0E
                    ||*(pu8Tmp + 0x1C2 + u16IndexInMBR)==0x1C)
                {
                    FS_ByteSwapCopy((U8 *)&u32RelativeSector, (pu8Tmp + 0x1C6 + u16IndexInMBR), 4);
                    FS_ByteSwapCopy((U8 *)&u32TotalSec, (pu8Tmp + 0x1CA + u16IndexInMBR), 4);
                    if(u32TotalSec == 0)
                        u32RelativeSector = 0;
                    else
                    {
                        u32RelativeSector += u32MBRLogicBlockAddress;
                        *(pu8Tmp + 0x1C2 + u16IndexInMBR) = 0x0B;
                        if(!msAPI_MSDCtrl_SectorWrite(u8DeviceID, u32MBRLogicBlockAddress, 1, USB_IO_TEMP_ADDR))
                        {
                            __ASSERT(0);
                            return FALSE;
                        }
                    }
                }
                else if(*(pu8Tmp + 0x1C2 + u16IndexInMBR)==0xEE)
                {
                    unsigned long long u64FirstRelativeSector, u64LastRelativeSector;
                    //primary partition entry always in 2 LBA
                    if(!msAPI_MSDCtrl_SectorRead(u8DeviceID, 2, 1, USB_IO_TEMP_ADDR))
                    {
                        __ASSERT(0);
                        return FALSE;
                    }

                    pu8Tmp = (U8 xdata* )msAPI_FS_GetXData(USB_IO_TEMP_ADDR>>12);

                    FS_ByteSwapCopy((U8 *)&u64FirstRelativeSector, (pu8Tmp + 0x20), 8);
                    FS_ByteSwapCopy((U8 *)&u64LastRelativeSector, (pu8Tmp + 0x28), 8);
                    if((u64LastRelativeSector<u64FirstRelativeSector) || u64FirstRelativeSector>>32 || u64LastRelativeSector>>32)
                    {
                        PVRFSDBG(printf("PVRFS_FAT_Format : partition size/offset illegal or >2T,"));
                        PVRFSDBG(printf("u64FirstRelativeSector[%llu], u64LastRelativeSector[%llu]\n",
                                            u64FirstRelativeSector, u64LastRelativeSector));
                        u32RelativeSector = 0;
                        u32TotalSec = 0;
                    }
                    else
                    {
                        u32RelativeSector = (U32) u64FirstRelativeSector;
                        u32TotalSec = (U32) (u64LastRelativeSector - u64FirstRelativeSector + 1);
                    }
                }
                else
                {
                    u32RelativeSector = 0;
                    u32TotalSec = 0;
                }
            }

            FAT_ReturnXData();
            g_u32RelativeSector = u32RelativeSector;

#if 0       // for test
            PVRFSDBG(printf("\nu32RelativeSector: %LX , u32TotalSec: %LX    ", u32RelativeSector, u32TotalSec));
            return TRUE;
#endif

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
            PVRFS_FAT_Format_BPB(u8DeviceID, u32RelativeSector, u32TotalSec, &u8SecPerCluster, &u32FATSize);
            u32TotalFATTableSec = (U32)u8NumFATs * u32FATSize;

            PVRFSDBG(printf("\nu32RelativeSector: 0x%08LX, u16FatStartSec: %X, u8NumFATs: %02bx, u32FATSize: %LX",u32RelativeSector, (U16)0x20, u8NumFATs, u32FATSize));
        }
        else
        {
            //FAT16
            PVRFSDBG(printf("    No Partition Table was Found, Create BPB Directly...\n"));
            g_u32RelativeSector = 0;
            u32TotalSec = 0;
            u8NumFATs = 2;
            PVRFS_FAT_Format_BPB(u8DeviceID, g_u32RelativeSector, u32TotalSec, &u8SecPerCluster, &u32FATSize); //no partition table found, force to create BPB
            u32TotalFATTableSec = (U32)u8NumFATs * u32FATSize;
            g_DriveFATSectors = u32TotalFATTableSec;

        }
    }

#if 1
    if(PVRFS_Probe_BPB(u8DeviceID, g_u32RelativeSector, &u16ReservedSectors, &u8NumFATs,
        &u8SecPerCluster, &u32TotalSec, &u32FATSize) == FALSE)
    {
        __ASSERT(0);
        return FALSE;
    }

#else
    {
        U8 u8EnvironmentID;
        U8 fsid;
        FAT_FileSysStruct* pFAT_FileSys;
        u8EnvironmentID = msAPI_FSEnv_Register(driveNo);
        if(u8EnvironmentID==INVALID_FS_ENVIRONMENT_INDEX)
        {
            __ASSERT(0);
            return FALSE;
        }

        // get FAT data from BPB for step2: format FAT table
        fsid = msAPI_FSEnv_GetEnvironment( u8EnvironmentID )->u8FileSystemID;
        pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemXData(fsid);
        u8SecPerCluster = pFAT_FileSys->stBootSector.BPB_SecPerClus;
        u8NumFATs = pFAT_FileSys->stBootSector.BPB_NumFATs;
        u32FATSize = pFAT_FileSys->stBootSector.BPB_FATSz32;
        u16ReservedSectors = pFAT_FileSys->stBootSector.BPB_RsvdSecCnt;
        FAT_ReturnXData();
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
    }
#endif

    u32TotalFATTableSec = (U32)u8NumFATs * u32FATSize;
    *bFinished = FALSE;
    u32CurrentSector = g_u32RelativeSector + u16ReservedSectors; //0x20:FatStartSec
    //  u32TotalFATTableSec ;

    //pu8Tmp = (U8 xdata* )msAPI_FS_GetXData(addr);
    pu8Tmp = (U8 xdata* )msAPI_FS_GetXData(USB_IO_TEMP_ADDR>>12);
    memset(pu8Tmp, 0, 0x1000);
    FAT_ReturnXData();


    //printf("...Start clear FAT at %ld\n", u32CurrentSector+*u32WriteCount);

    // clear up all FAT table
    while(1)
    {
        if((*u32WriteCount + FAT_WRITE_SECTOR_CNT) > u32TotalFATTableSec)
            break;

        if(!msAPI_MSDCtrl_SectorWrite(u8DeviceID, (U32)(u32CurrentSector+*u32WriteCount), FAT_WRITE_SECTOR_CNT, USB_IO_TEMP_ADDR))
        {
            __ASSERT(0);
            return FALSE;
        }
        *u32WriteCount +=FAT_WRITE_SECTOR_CNT;
        u32FATClearCnt++;

        //Break to let UI to draw progress bar.
        if ((u32FATClearCnt == FAT_WRITE_SECTOR_CNT_PER_SECTION) && (*u32WriteCount < u32TotalFATTableSec))
        {
            return TRUE; //return here to let UI to draw progress bar, *bFinish still be FALSE.
        }

    }

    while(1)
    {
        if((*u32WriteCount + 1) > u32TotalFATTableSec)
            break;

        if(!msAPI_MSDCtrl_SectorWrite(u8DeviceID, (U32)(u32CurrentSector+*u32WriteCount), 1, USB_IO_TEMP_ADDR))
        {
            __ASSERT(0);
            return FALSE;
        }
        (*u32WriteCount) ++;
    }

    PVRFSDBG(printf("    Initial ROOT Dorectory...\n"));
    // init Root directory
    *u32WriteCount = 0;
    while(u8SecPerCluster >= 8)
    {
        if(!msAPI_MSDCtrl_SectorWrite(u8DeviceID, (U32)(u32CurrentSector+u32TotalFATTableSec + *u32WriteCount), FAT_WRITE_SECTOR_CNT, USB_IO_TEMP_ADDR))
        {
            __ASSERT(0);
            return FALSE;
        }
        u8SecPerCluster -= 8;
        *u32WriteCount += FAT_WRITE_SECTOR_CNT;
    }

    // init FAT table
    //pu8Tmp = (U8 xdata* )msAPI_FS_GetXData(addr);
    pu8Tmp = (U8 xdata* )msAPI_FS_GetXData(USB_IO_TEMP_ADDR>>12);
    // memset(pu8Tmp, 0, 0x1000);
    u32ClusterID =  PVRFSSwap32(0x0FFFFFF8);
    memcpy(pu8Tmp, &u32ClusterID, FAT32ENTRYSIZE);
    u32ClusterID = PVRFSSwap32(0x0FFFFFFF);
    memcpy(pu8Tmp+4, &u32ClusterID, FAT32ENTRYSIZE);
    memcpy(pu8Tmp+8, &u32ClusterID, FAT32ENTRYSIZE);
    FAT_ReturnXData();


    // FAT1
    if(!msAPI_MSDCtrl_SectorWrite(u8DeviceID, (U32)u32CurrentSector, 1, USB_IO_TEMP_ADDR))
    {
        __ASSERT(0);
        return FALSE;
    }

    // FAT2
    if(!msAPI_MSDCtrl_SectorWrite(u8DeviceID, (U32)(u32CurrentSector+u32FATSize), 1, USB_IO_TEMP_ADDR))
    {
        __ASSERT(0);
        return FALSE;
    }
    *bFinished = TRUE;

    return TRUE;
}

U32 msAPI_PVRFS_GetFATFormatWriteCnt(U8 u8DriveNo)
{

#if 1
    if ((_enPVRFSFileSystemType == PVR_FS_BULKFS) || (_enPVRFSFileSystemType == PVR_FS_N51FAT32))
    {
        if (u8DriveNo != msAPI_PVRFS_GetDriveIndex())
            return 0;

        if(g_DriveFATSectors == 0)
        {
            if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
                msAPI_PVRFS_SetDiskDriveIndex(u8DriveNo);
            _u8DiskDriveIndex = u8DriveNo;
        }
        return g_DriveFATSectors;
    }
    return 0;
#else

    U32 u32TotalFATTableSec;
    U8 u8NumFATs;
    U32 u32FATSize;
    U8 u8DeviceID = msAPI_BKFS_GetDeviceIndex();    // default
    U8 u8EnvironmentID;
    U8 fsid;

    FAT_FileSysStruct* pFAT_FileSys;

    if (u8DriveNo >= DISK_DRIVE_NUM)
    {
        __ASSERT(0);
        return 0;
    }

    u8EnvironmentID = msAPI_FSEnv_Register(u8DriveNo);
    if(u8EnvironmentID==INVALID_FS_ENVIRONMENT_INDEX)
    {
        __ASSERT(0);
        return 0;
    }

    fsid = msAPI_FSEnv_GetEnvironment( u8EnvironmentID )->u8FileSystemID;
    pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemXData(fsid);
    if (pFAT_FileSys == NULL)
    {
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        return 0;
    }
    u8NumFATs = pFAT_FileSys->stBootSector.BPB_NumFATs;
    u32FATSize = pFAT_FileSys->stBootSector.BPB_FATSz32;
    u32TotalFATTableSec = (U32)u8NumFATs * u32FATSize;
    FAT_ReturnXData();
    msAPI_FSEnv_UnRegister(u8EnvironmentID);

    u32TotalFATTableSec = (U32)u8NumFATs * u32FATSize;
    return u32TotalFATTableSec;

#endif
}
#endif //#ifndef OBAMA

#ifdef OBAMA
U8 msAPI_PVRFS_GetFormatPercentage(void)
{
    return GetFormatPercent();
}
#endif

#ifndef OBAMA
BOOLEAN msAPI_PVRFS_Format(U32 u32MBRLogicBlockAddress, U8 u8IndexInMBR, U32* u32WriteCount, BOOLEAN* bFinished)
{
    if ((_enPVRFSFileSystemType != PVR_FS_BULKFS) && (_enPVRFSFileSystemType != PVR_FS_N51FAT32) &&
        (_enPVRFSFileSystemType != PVR_FS_LINUX_UNSUPPORTED))
        return FALSE;

    if (!PVRFS_FAT_Format(u32MBRLogicBlockAddress, u8IndexInMBR, u32WriteCount, bFinished))
    {
        __ASSERT(0);
        return FALSE;
    }

    return TRUE;
}
#else
BOOLEAN msAPI_PVRFS_Format(EN_PVRFS_FSTYPE ePVRFSFileSystemType, U8 u8DiskDriveIndex)
{
    FORMAT_TYPE type = FORMAT2FAT;

    if (u8DiskDriveIndex == INVALID_DRIVE_INDEX)
        return FALSE;

    if (!msAPI_PVRFS_IsLinuxFileSystemType(ePVRFSFileSystemType))
        return FALSE;

    switch(ePVRFSFileSystemType)
    {
        case PVR_FS_LINUX_FAT:
        {
            type = FORMAT2FAT;
            break;
        }
        case PVR_FS_LINUX_NTFS:
        {
            type = FORMAT2NTFS;
            break;
        }
        case PVR_FS_LINUX_EXT2:
        {
            type = FORMAT2EXT2;
            break;
        }
        case PVR_FS_LINUX_EXT3:
        {
            type = FORMAT2EXT3;
            break;
        }
        default:
        {
            __ASSERT(0);
            return FALSE;
        }
    }

    if (Linux_Format(type, u8DiskDriveIndex))
    {
       return TRUE;
    }

    return FALSE;
}
#endif

BOOLEAN msAPI_PVRFS_IsFormated(U8 u8DiskDriveIndex)
{
#ifndef OBAMA
    U8 u8EnvironmentID;
    U16 BKFSDirName[9]={'_','M','S','T','B','K','F','S',0};
    U16 BKFSIndexFileName[13] = {'M','S','T','_','B','K','F','S','.','I','D','X',0};
    FileEntry entry;

    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
    {
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
    else if (_enPVRFSFileSystemType == PVR_FS_N51FAT32)
    {
        //check N51FS FAT32 file system
        U8 u8FileSystemID;
        U8 u8EnvID;
        FAT_FileSysStruct* pFAT_FileSys;

        u8EnvID = msAPI_FSEnv_Register(_u8DiskDriveIndex);
        if(u8EnvID==INVALID_FS_ENVIRONMENT_INDEX)
        {
            __ASSERT(0);
            return FALSE;
        }

        u8FileSystemID = msAPI_FSEnv_GetEnvironment(u8EnvID)->u8FileSystemID;
        pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemXData(u8FileSystemID);
        if ((pFAT_FileSys) && (pFAT_FileSys->stFAT.u8FATType == FAT_TYPE_FAT32))
        {
            FAT_ReturnXData();
            msAPI_FSEnv_UnRegister(u8EnvID);
            return TRUE;
        }
        FAT_ReturnXData();
        msAPI_FSEnv_UnRegister(u8EnvID);
    }
#else
    UNUSED(u8DiskDriveIndex);
    if (msAPI_PVRFS_IsLinuxFileSystemType(_enPVRFSFileSystemType))
    {
        return TRUE;
    }
#endif //#ifndef OBAMA
    return FALSE;
}

/******************** Partition Table *******************************************************************/
BOOLEAN msAPI_PVRFS_IsPartitionReady(U8 u8DiskDriveIndex,U8 u8DeviceIndex)
{
    if ((u8DiskDriveIndex==INVALID_DRIVE_INDEX) || (u8DeviceIndex==INVALID_DEVICE_INDEX))
    {
        __ASSERT(0);
        return FALSE;
    }
    else
    {
        if (!msAPI_FCtrl_IsDriveMounted(u8DiskDriveIndex))
        {
            msAPI_MSDCtrl_CheckDevices();
            if (msAPI_MSDCtrl_GetDeviceStatus(u8DeviceIndex)==MSD_STATUS_INSERTED)
            {
                if (msAPI_FCtrl_ActiveDevice(u8DeviceIndex))
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

#if __PVRFS_SUPPORT_PARTITION__

BOOLEAN msAPI_PVRFS_ClearMBR(U8 u8DeviceIndex, U32 lba)
{
    //U32 addr = (USB_IO_TEMP_ADDR>>12);
    U8 *pu8Tmp;

    pu8Tmp = (U8 xdata* )msAPI_FS_GetXData(USB_IO_TEMP_ADDR>>12);
    memset(pu8Tmp, 0, 512);
    pu8Tmp[16] = 'M';//mstar magic number
    pu8Tmp[17] = 'S';//mstar magic number
    pu8Tmp[18] = 'T';//mstar magic number
    pu8Tmp[19] = 'A';//mstar magic number
    pu8Tmp[20] = 'R';//mstar magic number
    pu8Tmp[510] = 0x55;
    pu8Tmp[511] = 0xAA;
    FAT_ReturnXData();

    if(!msAPI_MSDCtrl_SectorWrite(u8DeviceIndex, lba, 1, USB_IO_TEMP_ADDR))
    {
          __ASSERT(0);
          return FALSE;
    }
    return TRUE;
}


static U32 PVRFS_FDISK_GetTotalSecCnt(U8 u8DeviceIndex)
{
    if(u8DeviceIndex == INVALID_DEVICE_INDEX)
        return 0;
    return msAPI_MSDCtrl_GetBlockNum(u8DeviceIndex);
}

static BOOLEAN PVRFS_FDISK_AddMainPartition2MBR( U8 u8DeviceIndex, U8 partitionID, BOOLEAN isMainPartition,
                                                                                                               U32 startLBA, U32 LBACnt)
{
    //U32 addr = (USB_IO_TEMP_ADDR>>12);
    U8 *pu8Tmp;
    U16 u16Index;

    PVRFSDBG(printf(" Add partition %bd, %lx:%lx\n", partitionID, startLBA, LBACnt));
    if(u8DeviceIndex == INVALID_DEVICE_INDEX)
             return FALSE;
    if(partitionID >= MAX_PARTITION_COUNT)
        return FALSE;

    if(startLBA==0 || startLBA+LBACnt>PVRFS_FDISK_GetTotalSecCnt(u8DeviceIndex))
    {
        __ASSERT(0);
        return FALSE;
    }


    u16Index = 446+((U16)partitionID<<4);
    if(!msAPI_MSDCtrl_SectorRead(u8DeviceIndex, 0, 1, USB_IO_TEMP_ADDR))
    {
          __ASSERT(0);
          return FALSE;
    }

    pu8Tmp = (U8 xdata* )msAPI_FS_GetXData(USB_IO_TEMP_ADDR>>12);


    __ASSERT(pu8Tmp[16]=='M' && pu8Tmp[17]=='S' && pu8Tmp[18]=='T');

#if 0
   {
       U16 i;
       U32 begSect, endSect;
       for( i=0; i<MAX_PARTITION_COUNT; i++)
       {
           if( i == partitionID)
              continue;
           begSect = PVRFSSwap32(*(U32*)(pu8Tmp+446+i*16+8));
           endSect = PVRFSSwap32(*(U32*)(pu8Tmp+446+i*16+12))+begSect;

           if(startLBA>=endSect || startLBA+LBACnt<=begSect)
            continue;
           __ASSERT(0);
           return FALSE;

         //  if(PVRFSSwap32(*(U32*)(pu8Tmp+446+i*16+8))
       }
   }
#endif


    memset(pu8Tmp+u16Index, 0, 16);
    pu8Tmp[u16Index+4] = isMainPartition?0x0C:0x0F;//FAT32 LBA
    pu8Tmp[u16Index+1] = 0x00;
    pu8Tmp[u16Index+2] = 0x00;

    pu8Tmp[u16Index+8] = (U8)startLBA;
    pu8Tmp[u16Index+9] = (U8)(startLBA>>8);
    pu8Tmp[u16Index+10] = (U8)(startLBA>>16);
    pu8Tmp[u16Index+11] = (U8)(startLBA>>24);

    pu8Tmp[u16Index+12] = (U8)LBACnt;
    pu8Tmp[u16Index+13] = (U8)(LBACnt>>8);
    pu8Tmp[u16Index+14] = (U8)(LBACnt>>16);
    pu8Tmp[u16Index+15] = (U8)(LBACnt>>24);
    FAT_ReturnXData();

    if(!msAPI_MSDCtrl_SectorWrite(u8DeviceIndex, 0, 1, USB_IO_TEMP_ADDR))
    {
          __ASSERT(0);
          return FALSE;
    }

    if(isMainPartition == FALSE)
    {
          msAPI_PVRFS_ClearMBR(u8DeviceIndex, startLBA);
    }

    return TRUE;
}

static BOOLEAN PVRFS_FDISK_AddLogicPartition2MBR(U8 u8DeviceIndex,  U8 expandPartitionID, U8 logicPartitionID, U32 startLBA,
                                                                                        U32 LBACnt)
{
    U32 expandPartitionStart = 0;
    U32 expandPartitionEnd = 0;
    //U32 addr = (USB_IO_TEMP_ADDR>>12);
    U8 *pu8Tmp;
    U16 u16Index;

    if(u8DeviceIndex == INVALID_DEVICE_INDEX)
             return FALSE;
    if(expandPartitionID >= MAX_PARTITION_COUNT ||logicPartitionID>=MAX_PARTITION_COUNT)
        return FALSE;

    if(startLBA==0 || startLBA+LBACnt>PVRFS_FDISK_GetTotalSecCnt(u8DeviceIndex))
    {
        __ASSERT(0);
        return FALSE;
    }

    u16Index = 446+((U16)expandPartitionID<<4);
    if(!msAPI_MSDCtrl_SectorRead(u8DeviceIndex, 0, 1, USB_IO_TEMP_ADDR))
    {
          __ASSERT(0);
          return FALSE;
    }

    pu8Tmp = (U8 xdata* )msAPI_FS_GetXData(USB_IO_TEMP_ADDR>>12);
    __ASSERT(pu8Tmp[16]=='M' && pu8Tmp[17]=='S' && pu8Tmp[18]=='T');
   __ASSERT(pu8Tmp[u16Index+4]==0x0F || pu8Tmp[u16Index+4]==0x05);

    ByteSwapCopy((U8 *)&expandPartitionStart, pu8Tmp+u16Index+8, 4);
    ByteSwapCopy((U8 *)&expandPartitionEnd, pu8Tmp+u16Index+12, 4);
    FAT_ReturnXData();

    if(expandPartitionStart==0 || expandPartitionEnd==0)
    {
        //no expanded partition here
        __ASSERT(0);
        return FALSE;
    }
    expandPartitionEnd += expandPartitionStart;

    if(startLBA<=expandPartitionStart || startLBA+LBACnt>expandPartitionEnd)
    {
        //exceed expanded partition range
        //expanded partition is in range [expandPartitionStart+1, expandPartitionEnd]
        __ASSERT(0);
        return FALSE;
    }
    startLBA -= expandPartitionStart;

     //read expanded MBR
     u16Index = 446+(logicPartitionID<<4);
    if(!msAPI_MSDCtrl_SectorRead(u8DeviceIndex, expandPartitionStart, 1, USB_IO_TEMP_ADDR))
    {
          __ASSERT(0);
          return FALSE;
    }
    pu8Tmp = (U8 xdata* )msAPI_FS_GetXData(USB_IO_TEMP_ADDR>>12);

    __ASSERT(pu8Tmp[16]=='M' && pu8Tmp[17]=='S' && pu8Tmp[18]=='T');
    memset(pu8Tmp+u16Index, 0, 16);
    pu8Tmp[u16Index+4] = 0x0c;//FAT32 LBA
    pu8Tmp[u16Index+1] = 0x00;
    pu8Tmp[u16Index+2] = 0x00;

    pu8Tmp[u16Index+8] = (U8)startLBA;
    pu8Tmp[u16Index+9] = (U8)(startLBA>>8);
    pu8Tmp[u16Index+10] = (U8)(startLBA>>16);
    pu8Tmp[u16Index+11] = (U8)(startLBA>>24);

    pu8Tmp[u16Index+12] = (U8)LBACnt;
    pu8Tmp[u16Index+13] = (U8)(LBACnt>>8);
    pu8Tmp[u16Index+14] = (U8)(LBACnt>>16);
    pu8Tmp[u16Index+15] = (U8)(LBACnt>>24);
    FAT_ReturnXData();



    if(!msAPI_MSDCtrl_SectorWrite(u8DeviceIndex, expandPartitionStart, 1, USB_IO_TEMP_ADDR))
    {
          __ASSERT(0);
          return FALSE;
    }


    return TRUE;
}
//u32WriteCount need to start from 0, or it will not format BPB.

static U32 PVRFS_FDISK_GetExpandParttionMBRLBA(U8 u8DeviceIndex,  U8 expandPartitionID)
{
    U32 expandPartitionStart = 0;
    U16 u16Index;
    U8 *pu8Tmp;

    if(u8DeviceIndex == INVALID_DEVICE_INDEX)
    {
         __ASSERT(0);
         return 0xFFFFFFFF;
    }
    if(expandPartitionID >= MAX_PARTITION_COUNT)
    {
         __ASSERT(0);
         return 0xFFFFFFFF;
    }

    u16Index = 446+((U16)expandPartitionID<<4);
    if(!msAPI_MSDCtrl_SectorRead(u8DeviceIndex, 0, 1, USB_IO_TEMP_ADDR))
    {
          __ASSERT(0);
          return 0xFFFFFFFF;
    }
    pu8Tmp = (U8 xdata* )msAPI_FS_GetXData(USB_IO_TEMP_ADDR>>12);

    ByteSwapCopy((U8 *)&expandPartitionStart, pu8Tmp+u16Index+8, 4);
    FAT_ReturnXData();
    return expandPartitionStart;
}
//u32WriteCount need to start from 0, or it will not format BPB.

BOOLEAN msAPI_PVRFS_AddLogicPartition(U8 u8DeviceIndex,  U8 expandPartitionID, U8 logicPartitionID, U32 startLBA,
                                                                                        U32 LBACnt)
{
     BOOLEAN bFinished;
     U32 u32WriteCount;
     if(!PVRFS_FDISK_AddLogicPartition2MBR(u8DeviceIndex,  expandPartitionID, logicPartitionID, startLBA,
                                                                                        LBACnt))
     {
              return FALSE;
     }
     u32WriteCount = 0;
     PVRFSDBG(printf("start format logic partition %bd in expanded partition %bd ..\n", logicPartitionID, expandPartitionID));
     do
     {
            if(!PVRFS_FAT_Format(PVRFS_FDISK_GetExpandParttionMBRLBA(u8DeviceIndex, expandPartitionID), logicPartitionID, &u32WriteCount, &bFinished))
            {
                   MS_DEBUG_MSG(printf("...Format failed.\n"));
                   break;
            }
            else
            {
                    FS_RESET_WDT();
                    PVRFSDBG(printf("...Format write %ld.\n", u32WriteCount));
            }
      }while(!bFinished);

     return bFinished;
}

BOOLEAN msAPI_PVRFS_AddMainPartition( U8 u8DeviceIndex, U8 partitionID, BOOLEAN isMainPartition,
                                                                                                               U32 startLBA, U32 LBACnt)
{
     BOOLEAN bFinished;
     U32 u32WriteCount;
     if(!PVRFS_FDISK_AddMainPartition2MBR( u8DeviceIndex, partitionID,  isMainPartition,
                                                                                                                startLBA,  LBACnt))
     {
          return FALSE;
     }
     //for expanded partition, do not clear it now
     if(isMainPartition == FALSE)
           return TRUE;

     u32WriteCount = 0;
     PVRFSDBG(printf("start format main partition %bd..\n", partitionID));
     do
     {
            if(!PVRFS_FAT_Format(0, partitionID, &u32WriteCount, &bFinished))
            {
                   MS_DEBUG_MSG(printf("...Format failed.\n"));
                   break;
            }
            else
            {
                    FS_RESET_WDT();
                    PVRFSDBG(printf("...Format write %ld.\n", u32WriteCount));
            }
      }while(!bFinished);

     return bFinished;
}

#if  0 //for test only
BOOLEAN PVRFS_DBG_CHECKMBR(U8 u8DeviceIndex)
{
    U32 addr = (USB_IO_TEMP_ADDR>>12);
    U8 *pu8Tmp;
    BOOLEAN bInitialized = FALSE;

    if(!msAPI_MSDCtrl_SectorRead(u8DeviceIndex, 0, 1, USB_IO_TEMP_ADDR))
    {
          __ASSERT(0);
          return FALSE;
    }
    pu8Tmp = (U8 xdata* )msAPI_FS_GetXData(addr);
    if(pu8Tmp[16] =='M' &&  pu8Tmp[17]=='S' && pu8Tmp[18] == 'T' && pu8Tmp[510] == 0x55
        &&  pu8Tmp[511] == 0xAA)
        bInitialized = TRUE;
    FAT_ReturnXData();
    return bInitialized;
}

BOOLEAN msAPI_PVRFS_FDISK_Format_TEST(void)
{

        U32 totalSector;
        U32 usedSector;
        static U8 inited = 0;
        U8   uDeviceID = msAPI_PVRFS_GetDeviceIndex();


        if(inited == 0 && uDeviceID != INVALID_DEVICE_INDEX
            && msAPI_MSDCtrl_GetDeviceStatus(uDeviceID)==MSD_STATUS_IDLE)
        {
            printf("start init\n");
             inited = 1;
             if(BKFS_DBG_CHECKMBR(uDeviceID) == FALSE)
             {

                 totalSector = PVRFS_FDISK_GetTotalSecCnt(uDeviceID);
                 usedSector = 1;//main MBR
                 msAPI_PVRFS_ClearMBR(uDeviceID, 0);
                 printf("create main partition 0...\n");
                 msAPI_PVRFS_AddMainPartition(uDeviceID, 0, TRUE, usedSector, (U32)68*2*1024*1024);
                 usedSector +=  (U32)68*2*1024*1024;
                 printf("create main partition 1...\n");
                 msAPI_PVRFS_AddMainPartition(uDeviceID, 1, TRUE, usedSector, (totalSector-usedSector)/4);
                 usedSector +=  (totalSector-usedSector)/4;
                 printf("create main expanded partition 2...\n");
                 msAPI_PVRFS_AddMainPartition(uDeviceID, 2, FALSE, usedSector, totalSector-usedSector);
                 usedSector += 1;//expanded MBR
                 printf("create logic partition 0 in expanded partition 2...\n");
                 msAPI_PVRFS_AddLogicPartition(uDeviceID, 2, 0, usedSector, (totalSector-usedSector)/2);
                 printf("create logic partition 1 in expanded partition 2...\n");
                 usedSector += (totalSector-usedSector)/2;
                 msAPI_PVRFS_AddLogicPartition(uDeviceID, 2, 1, usedSector, totalSector-usedSector);
             }

         }
        if(msAPI_PVRFS_IsInitialized())
            printf("Disk Free Space is %lx MB\n", msAPI_PVRFS_GetDriveFreeSpaceMB());
        return TRUE;

}
#endif
#endif //#if __PVRFS_SUPPORT_PARTITION__

/******************** File Handle ****************************************************************/
BOOLEAN PVRFS_EnterPVRDirectory(U8 u8EnvironmentID)
{
    U16 PVRFolderName[]={'_','M','S','T','P','V','R',0}; //default directory
    U8 u8PVRFolderLength = FS_strlen_U(PVRFolderName);
    FileEntry entry;

    if(u8EnvironmentID == INVALID_FS_ENVIRONMENT_INDEX)
    {
        __ASSERT(0);
        return FALSE;
    }

    if(!msAPI_FCtrl_DirectoryChangeToRoot(u8EnvironmentID))
    {
        __ASSERT(0);
        return FALSE;
    }

    //check the forlder existed or not
    if(!msAPI_FCtrl_EntrySearchByName(u8EnvironmentID, PVRFolderName , u8PVRFolderLength, &entry))
    {
        __ASSERT(0);
        return FALSE;
    }

    if(entry.EntryType != ENTRY_TYPE_DIR)
    {
        __ASSERT(0);
        return FALSE;
    }

    //change to default PVR folder
    if(!msAPI_FCtrl_DirectoryChange(u8EnvironmentID,&entry))
    {
        __ASSERT(0);
        return FALSE;
    }

    return TRUE;
}

/***************************************************************************************/
/// Create file in specific dorectory. If BKFS: only for timeshift mode
/// @param -pu16FileName \b IN: File name.
/// @return -success: return file handle; else: return INVALID_FILE_HANDLE.
/***************************************************************************************/
U8 msAPI_PVRFS_FileCreate(U16* pu16FileName)
{
    if (pu16FileName == NULL)
        return INVALID_FILE_HANDLE;

    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
    {
#ifndef OBAMA
        return msAPI_BKFS_FileCreate(pu16FileName);
#endif
    }
    else if ((_enPVRFSFileSystemType == PVR_FS_N51FAT32) || (msAPI_PVRFS_IsLinuxFileSystemType(_enPVRFSFileSystemType)))
    {
        U8 u8EnvironmentID = msAPI_FSEnv_Register(_u8DiskDriveIndex);
        U8 u8Handle;

        if(u8EnvironmentID == INVALID_FS_ENVIRONMENT_INDEX)
        {
            __ASSERT(0);
            return INVALID_FILE_HANDLE;
        }

        if (msAPI_PVRFS_FileExist(pu16FileName))
        {
            msAPI_FSEnv_UnRegister(u8EnvironmentID);
            return INVALID_FILE_HANDLE;
        }

        if (!PVRFS_EnterPVRDirectory(u8EnvironmentID))
        {
            msAPI_FSEnv_UnRegister(u8EnvironmentID);
            return INVALID_FILE_HANDLE;
        }

        //create target file
        u8Handle = msAPI_FCtrl_FileCreate(u8EnvironmentID, pu16FileName, FS_strlen_U(pu16FileName), CREATE_MODE_NEW);
        if (u8Handle == INVALID_FILE_HANDLE)
        {
            __ASSERT(0);
            msAPI_FSEnv_UnRegister(u8EnvironmentID);
            return INVALID_FILE_HANDLE;
        }

        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        return u8Handle;
    }

    return INVALID_FILE_HANDLE;
}
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
BOOL msAPI_CIPVRFS_FileCreate(U16* pu16FileName, U8 *pineventHandleID, U8 *urilicenseHandleID)
{
    if (pu16FileName == NULL)
        return INVALID_FILE_HANDLE;

    U16 PVRFolderName[RECORD_NAME_LENGTH]={0};
    U16 tmpFolderName[RECORD_NAME_LENGTH]={0};
    U8 u8FileNameLen = FS_strlen_U(pu16FileName);
    U8 u8FoldNameLen = u8FileNameLen;

    U16 _pu16TimeShiftFileName[]={'T','I','M','E','S','H','I','F','T','.','T','S',0};
    BOOL bIsTimeshift = false;
    if(strcmp((char*)pu16FileName,(char*)_pu16TimeShiftFileName) == 0)
    {
        bIsTimeshift = true;
    }
    if(bIsTimeshift)
    {
        memcpy(tmpFolderName, _pu16TimeShiftFileName, sizeof(_pu16TimeShiftFileName));
        int i = 0;
        for(i=0;i<u8FileNameLen;i++)
        {
            if(tmpFolderName[i] != CHAR_DOT)
            {
                PVRFolderName[i] = tmpFolderName[i];
            }
            else
            {
                PVRFolderName[i]='\0';
                u8FoldNameLen = i;
                break;
            }
        }
    }
    else
    {
        memcpy(tmpFolderName, pu16FileName, sizeof(U16)*u8FileNameLen);
        int i = 0;
        if(u8FileNameLen >= RECORD_NAME_LENGTH)
            u8FoldNameLen = u8FileNameLen = RECORD_NAME_LENGTH;
        for(i=0;i<u8FileNameLen;i++)
        {
            if(tmpFolderName[i] != CHAR_RIGHT_BRACKET)
            {
                PVRFolderName[i] = tmpFolderName[i];
            }
            else
            {
                PVRFolderName[i] = CHAR_RIGHT_BRACKET;
                PVRFolderName[i+1]='\0';
                u8FoldNameLen = i+1;
                break;
            }
        }
    }
    ////////////////////pvr ts file folder////////////////////////////
    if ((_enPVRFSFileSystemType == PVR_FS_N51FAT32) || (msAPI_PVRFS_IsLinuxFileSystemType(_enPVRFSFileSystemType)))
    {
        FileEntry entry;

        U8 u8EnvironmentID = msAPI_FSEnv_Register(_u8DiskDriveIndex);

        if(u8EnvironmentID==INVALID_FS_ENVIRONMENT_INDEX)
        {
            __ASSERT(0);
            return FALSE;
        }

        if (!PVRFS_EnterPVRDirectory(u8EnvironmentID))
        {
            msAPI_FSEnv_UnRegister(u8EnvironmentID);
            printf("......msAPI_CIPVRFS_FileCreate....error#1..........\n");
            return FALSE;
        }

        //check if the forlder _MSTBKFS existed or not
        BOOL ret = FALSE;
        U8 u8Handle = 0;

        ret = msAPI_FCtrl_EntrySearchByName(u8EnvironmentID, PVRFolderName , u8FoldNameLen, &entry);
        if((!ret) || (ret && (entry.EntryType != ENTRY_TYPE_DIR)))
        {
            if (!msAPI_FCtrl_DirectoryCreate(u8EnvironmentID, PVRFolderName, u8FoldNameLen))
            {
                msAPI_FSEnv_UnRegister(u8EnvironmentID);
                __ASSERT(0);
                printf("......msAPI_CIPVRFS_FileCreate....error#2..........\n");
                return FALSE;
            }
            //check the forlder existed or not
            if(!msAPI_FCtrl_EntrySearchByName(u8EnvironmentID, PVRFolderName , u8FoldNameLen, &entry))
            {
                msAPI_FSEnv_UnRegister(u8EnvironmentID);
                __ASSERT(0);
                printf("......msAPI_CIPVRFS_FileCreate....error#3..........\n");
                return FALSE;
            }
            if(!msAPI_FCtrl_DirectoryChange(u8EnvironmentID,&entry))
            {
                msAPI_FSEnv_UnRegister(u8EnvironmentID);
                __ASSERT(0);
                printf("......msAPI_CIPVRFS_FileCreate....error#4..........\n");
                return FALSE;
            }
            u8Handle = msAPI_FCtrl_DirectoryOpen(&entry, OPEN_MODE_FOR_READ_WRITE);
            if(u8Handle != INVALID_FILE_HANDLE)
            {
                msAPI_BKFS_Show_Hide_File(u8Handle, FALSE);
                msAPI_FCtrl_FileClose(u8Handle);
            }
        }

        U16 SecureFolderName[]= PVR_SECURE_CONTENT_FOLDER;
        U8 u8SecureFolderLength = FS_strlen_U(SecureFolderName);
        ret = msAPI_FCtrl_EntrySearchByName(u8EnvironmentID, SecureFolderName, u8SecureFolderLength, &entry);
        if((!ret) || (ret && (entry.EntryType != ENTRY_TYPE_DIR)))
        {
            if (!msAPI_FCtrl_DirectoryCreate(u8EnvironmentID, SecureFolderName, u8SecureFolderLength))
            {
                msAPI_FSEnv_UnRegister(u8EnvironmentID);
                __ASSERT(0);
                printf("......msAPI_CIPVRFS_FileCreate....error#5..........\n");
                return FALSE;
            }
            //check the forlder existed or not
            if(!msAPI_FCtrl_EntrySearchByName(u8EnvironmentID, SecureFolderName , u8SecureFolderLength, &entry))
            {
                msAPI_FSEnv_UnRegister(u8EnvironmentID);
                __ASSERT(0);
                printf("......msAPI_CIPVRFS_FileCreate....error#6..........\n");
                return FALSE;
            }
            if(!msAPI_FCtrl_DirectoryChange(u8EnvironmentID,&entry))
            {
                msAPI_FSEnv_UnRegister(u8EnvironmentID);
                __ASSERT(0);
                printf("......msAPI_CIPVRFS_FileCreate....error#7..........\n");
                return FALSE;
            }
            u8Handle = msAPI_FCtrl_DirectoryOpen(&entry, OPEN_MODE_FOR_READ_WRITE);
            if(u8Handle != INVALID_FILE_HANDLE)
            {
                msAPI_BKFS_Show_Hide_File(u8Handle, FALSE);
                msAPI_FCtrl_FileClose(u8Handle);
            }
        }

        U8 u8pinHandle;
        U8 u8uriHandle;
        U16 SecurePineventName[] = PVR_PIN_EVENT_MAP_FILENAME;
        U16 SecureLicenseName[] = PVR_URI_LICENSE_MAP_FILENAME;
        if(msAPI_FCtrl_EntrySearchByName(u8EnvironmentID, SecurePineventName, FS_strlen_U(SecurePineventName), &entry))
        {
             msAPI_FSEnv_UnRegister(u8EnvironmentID);
           __ASSERT(0);
            printf("......msAPI_CIPVRFS_FileCreate....error#8..........\n");
            return FALSE;
        }
        //create target file
        u8pinHandle = msAPI_FCtrl_FileCreate(u8EnvironmentID, SecurePineventName, FS_strlen_U(SecurePineventName), CREATE_MODE_NEW);
        if (u8pinHandle == INVALID_FILE_HANDLE)
        {
             msAPI_FSEnv_UnRegister(u8EnvironmentID);
           __ASSERT(0);
            printf("......msAPI_CIPVRFS_FileCreate....error#8-1..........\n");
            return FALSE;
        }

        if(msAPI_FCtrl_EntrySearchByName(u8EnvironmentID, SecureLicenseName, FS_strlen_U(SecureLicenseName), &entry))
        {
            msAPI_FCtrl_FileClose(u8pinHandle);
            msAPI_FSEnv_UnRegister(u8EnvironmentID);
            __ASSERT(0);
            printf("......msAPI_CIPVRFS_FileCreate....error#9..........\n");
            return FALSE;
        }

        //create target file
        u8uriHandle = msAPI_FCtrl_FileCreate(u8EnvironmentID, SecureLicenseName, FS_strlen_U(SecureLicenseName), CREATE_MODE_NEW);
        if (u8uriHandle == INVALID_FILE_HANDLE)
        {
            msAPI_FCtrl_FileClose(u8pinHandle);
            msAPI_FSEnv_UnRegister(u8EnvironmentID);
            __ASSERT(0);
            printf("......msAPI_CIPVRFS_FileCreate....error#9-1..........\n");
            return FALSE;
        }

        *pineventHandleID = u8pinHandle;
        *urilicenseHandleID = u8uriHandle;

        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        printf("......msAPI_CIPVRFS_FileCreate....success #7-2..........\n");
        return true;
    }
    printf("......msAPI_CIPVRFS_FileCreate....error#10..........\n");
    return FALSE;
}

BOOL msAPI_CIPVRFS_FileOpen(U16* pu16FileName, EN_PVRFS_OPEN_MODE mode, U8 *pineventHandleID, U8 *urilicenseHandleID)
{
    if (pu16FileName == NULL)
    {
        printf("......CIPVRFS_PlaybackFileOpen....error#1..........\n");
        return FALSE;
    }

    U16 PVRFolderName[RECORD_NAME_LENGTH]={0};
    U16 tmpFolderName[RECORD_NAME_LENGTH]={0};
    U8 u8FileNameLen = FS_strlen_U(pu16FileName);
    U8 u8FoldNameLen = u8FileNameLen;

    U16 _pu16TimeShiftFileName[]={'T','I','M','E','S','H','I','F','T','.','T','S',0};
    BOOL bIsTimeshift = false;
    if(strcmp((char*)pu16FileName,(char*)_pu16TimeShiftFileName) == 0)
    {
        bIsTimeshift = true;
    }
    if(bIsTimeshift)
    {
        memcpy(tmpFolderName, _pu16TimeShiftFileName, sizeof(_pu16TimeShiftFileName));
        int i = 0;
        for(i=0;i<u8FileNameLen;i++)
        {
            if(tmpFolderName[i] != CHAR_DOT)
            {
                PVRFolderName[i] = tmpFolderName[i];
            }
            else
            {
                PVRFolderName[i]='\0';
                u8FoldNameLen = i;
                break;
            }
        }
    }
    else
    {
        memcpy(tmpFolderName, pu16FileName, sizeof(U16)*u8FileNameLen);
        int i = 0;
        if(u8FileNameLen >= RECORD_NAME_LENGTH)
        {
            u8FoldNameLen = u8FileNameLen = RECORD_NAME_LENGTH;
        }
        for(i=0;i<u8FileNameLen;i++)
        {
            if(tmpFolderName[i] != CHAR_RIGHT_BRACKET)
            {
                PVRFolderName[i] = tmpFolderName[i];
            }
            else
            {
                PVRFolderName[i] = CHAR_RIGHT_BRACKET;
                PVRFolderName[i+1]='\0';
                u8FoldNameLen = i+1;
                break;
            }
        }
    }

    if ((_enPVRFSFileSystemType == PVR_FS_N51FAT32) || (msAPI_PVRFS_IsLinuxFileSystemType(_enPVRFSFileSystemType)))
    {
        FileEntry entry;
        U8 N51FSMode = OPEN_MODE_BINARY_FOR_READ;
        U8 u8EnvironmentID = msAPI_FSEnv_Register(_u8DiskDriveIndex);

        if(u8EnvironmentID == INVALID_FS_ENVIRONMENT_INDEX)
        {
            __ASSERT(0);
            printf("......CIPVRFS_PlaybackFileOpen....error#2..........\n");
            return FALSE;
        }

        if (!PVRFS_EnterPVRDirectory(u8EnvironmentID))
        {
            msAPI_FSEnv_UnRegister(u8EnvironmentID);
            printf("......CIPVRFS_PlaybackFileOpen....error#3..........\n");
            return FALSE;
        }

        if(!msAPI_FCtrl_EntrySearchByName(u8EnvironmentID, PVRFolderName , u8FoldNameLen, &entry))
        {
            printf("......CIPVRFS_PlaybackFileOpen....error#4..........\n");
            msAPI_FSEnv_UnRegister(u8EnvironmentID);
           __ASSERT(0);
            return FALSE;
        }
        if(entry.EntryType != ENTRY_TYPE_DIR)
        {
            msAPI_FSEnv_UnRegister(u8EnvironmentID);
            printf("......CIPVRFS_PlaybackFileOpen....error#4.1..........\n");
            __ASSERT(0);
            return FALSE;
        }
        if(!msAPI_FCtrl_DirectoryChange(u8EnvironmentID,&entry))
        {
            msAPI_FSEnv_UnRegister(u8EnvironmentID);
            printf("......CIPVRFS_PlaybackFileOpen....error#5..........\n");
            __ASSERT(0);
            return FALSE;
        }

        U16 SecureFolderName[]= PVR_SECURE_CONTENT_FOLDER;
        if(!msAPI_FCtrl_EntrySearchByName(u8EnvironmentID, SecureFolderName , FS_strlen_U(SecureFolderName), &entry))
        {
            printf("......CIPVRFS_PlaybackFileOpen....error#6..........\n");
            msAPI_FSEnv_UnRegister(u8EnvironmentID);
            __ASSERT(0);
           return FALSE;
        }
        if(!msAPI_FCtrl_DirectoryChange(u8EnvironmentID,&entry))
        {
            printf("......CIPVRFS_PlaybackFileOpen....error#7..........\n");
            msAPI_FSEnv_UnRegister(u8EnvironmentID);
            __ASSERT(0);
           return FALSE;
        }

        switch(mode)
        {
            case PVRFS_OPEN_FOR_READ:
            {
                N51FSMode = OPEN_MODE_BINARY_FOR_READ;
                break;
            }
            case PVRFS_OPEN_FOR_WRITE:
            {
                N51FSMode = OPEN_MODE_BINARY_FOR_APPEND;
                break;
            }
            case PVRFS_OPEN_FOR_RING_WRITE:
            {
                N51FSMode = OPEN_MODE_BINARY_FOR_READ_APPEND;
                break;
            }
            default:
            {
                printf("......CIPVRFS_PlaybackFileOpen....error#8..........\n");
                msAPI_FSEnv_UnRegister(u8EnvironmentID);
                __ASSERT(0);
                return FALSE;
            }
        }

        U8 u8pinHandle;
        U8 u8uriHandle;
        U16 SecurePineventName[] = PVR_PIN_EVENT_MAP_FILENAME;
        U16 SecureLicenseName[] = PVR_URI_LICENSE_MAP_FILENAME;
        if(!msAPI_FCtrl_EntrySearchByName(u8EnvironmentID, SecurePineventName, FS_strlen_U(SecurePineventName), &entry))
        {
            msAPI_FSEnv_UnRegister(u8EnvironmentID);
            printf("......CIPVRFS_PlaybackFileOpen....error#9..........\n");
            return FALSE;
        }
        u8pinHandle = msAPI_FCtrl_FileOpen(&entry, N51FSMode);
        if (u8pinHandle == INVALID_FILE_HANDLE)
        {
            msAPI_FSEnv_UnRegister(u8EnvironmentID);
            printf("......CIPVRFS_PlaybackFileOpen....error#10..........\n");
            return FALSE;
        }

        if(!msAPI_FCtrl_EntrySearchByName(u8EnvironmentID, SecureLicenseName, FS_strlen_U(SecureLicenseName), &entry))
        {
            msAPI_FCtrl_FileClose(u8pinHandle);
            msAPI_FSEnv_UnRegister(u8EnvironmentID);
            printf("......CIPVRFS_PlaybackFileOpen....error#11..........\n");
            return FALSE;
        }
        u8uriHandle = msAPI_FCtrl_FileOpen(&entry, N51FSMode);
        if (u8uriHandle == INVALID_FILE_HANDLE)
        {
            msAPI_FCtrl_FileClose(u8pinHandle);
            msAPI_FSEnv_UnRegister(u8EnvironmentID);
            printf("......CIPVRFS_PlaybackFileOpen....error#12..........\n");
            return FALSE;
        }
        *pineventHandleID = u8pinHandle;
        *urilicenseHandleID = u8uriHandle;
        printf("......CIPVRFS_PlaybackFileOpen....success.......\n");
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        return TRUE;
    }
    printf("......CIPVRFS_PlaybackFileOpen....error#13..........\n");
    return FALSE;
}

U32 msAPI_CIPVRFS_FileWrite(U8 u8HandleID,U32 u32Buffer,U32 u32WriteLength)
{
    if (u8HandleID == INVALID_FILE_HANDLE)
        return FAT_MAX_FILE_LENGTH;

    if ((_enPVRFSFileSystemType == PVR_FS_N51FAT32) || (msAPI_PVRFS_IsLinuxFileSystemType(_enPVRFSFileSystemType)))
    {
        U32 u32LeftBytes;
        LongLong llFilePos;
        llFilePos = msAPI_PVRFS_FileTell(u8HandleID);

      #if 0//ndef MIPS_CHAKRA
        u32LeftBytes = msAPI_FCtrl_FileWrite(u8HandleID, u32Buffer, u32WriteLength); //return left bytes, for 8051+AEON
      #else //Obama+Chakra2
        u32LeftBytes = msAPI_FCtrl_FileWrite(u8HandleID, _VA2PA(u32Buffer), u32WriteLength); //return left bytes, for MIPS
      #endif

        return (u32WriteLength - u32LeftBytes); //return processed bytes
    }

    return FAT_MAX_FILE_LENGTH;
}

BOOL msAPI_CIPVRFS_FileClose(U8 pineventHandleID, U8 urilicenseHandleID)
{
    if ((pineventHandleID == INVALID_FILE_HANDLE) || (urilicenseHandleID == INVALID_FILE_HANDLE))
        return FALSE;
    printf("......msAPI_CIPVRFS_FileClose..........\n");

    if ((_enPVRFSFileSystemType == PVR_FS_N51FAT32) || (msAPI_PVRFS_IsLinuxFileSystemType(_enPVRFSFileSystemType)))
    {
        if ((msAPI_FCtrl_FileClose(pineventHandleID) != FILE_CLOSE_RESULT_ERROR)
            && (msAPI_FCtrl_FileClose(urilicenseHandleID) != FILE_CLOSE_RESULT_ERROR))
        {
            return TRUE;
        }
    }

    return FALSE;
}

BOOL msAPI_CIPVRFS_FileDelete(U16* pu16FileName)
{
    if (pu16FileName == NULL)
        return FALSE;

    U16 PVRFolderName[RECORD_NAME_LENGTH]={0};
    U16 tmpFolderName[RECORD_NAME_LENGTH]={0};
    U8 u8FileNameLen = FS_strlen_U(pu16FileName);
    U8 u8FoldNameLen = u8FileNameLen;

    U16 _pu16TimeShiftFileName[]={'T','I','M','E','S','H','I','F','T','.','T','S',0};
    BOOL bIsTimeshift = false;
    if(strcmp((char*)pu16FileName,(char*)_pu16TimeShiftFileName) == 0)
    {
        bIsTimeshift = true;
    }

    if(bIsTimeshift)
    {
        memcpy(tmpFolderName, _pu16TimeShiftFileName, sizeof(_pu16TimeShiftFileName));
        int i = 0;
        for(i=0;i<u8FileNameLen;i++)
        {
            if(tmpFolderName[i] != CHAR_DOT)
            {
                PVRFolderName[i] = tmpFolderName[i];
            }
            else
            {
                PVRFolderName[i]='\0';
                u8FoldNameLen = i;
                break;
            }
        }
    }
    else
    {
        memcpy(tmpFolderName, pu16FileName, sizeof(U16)*u8FileNameLen);
        int i = 0;
        if(u8FileNameLen >= RECORD_NAME_LENGTH)
            u8FileNameLen = RECORD_NAME_LENGTH;
        for(i=0;i<u8FileNameLen;i++)
        {
            if(tmpFolderName[i] != CHAR_RIGHT_BRACKET)
            {
                PVRFolderName[i] = tmpFolderName[i];
            }
            else
            {
                PVRFolderName[i] = CHAR_RIGHT_BRACKET;
                PVRFolderName[i+1]='\0';
                u8FoldNameLen = i+1;
                break;
            }
        }
    }
    if ((_enPVRFSFileSystemType == PVR_FS_N51FAT32) || (msAPI_PVRFS_IsLinuxFileSystemType(_enPVRFSFileSystemType)))
    {
        U16 SecureFolderName[]= PVR_SECURE_CONTENT_FOLDER;
        printf("......msAPI_CIPVRFS_FileDelete....#1..%d........\n",_enPVRFSFileSystemType);
        FileEntry PVRFolderentry;
        FileEntry SecureFolderentry;
        FileEntry fileentry;
        U8 u8EnvironmentID = msAPI_FSEnv_Register(_u8DiskDriveIndex);

        if(u8EnvironmentID == INVALID_FS_ENVIRONMENT_INDEX)
        {
            __ASSERT(0);
            printf("......msAPI_CIPVRFS_FileDelete....error#2..........\n");
            return FALSE;
        }

        if (!PVRFS_EnterPVRDirectory(u8EnvironmentID))
        {
            msAPI_FSEnv_UnRegister(u8EnvironmentID);
            printf("......msAPI_CIPVRFS_FileDelete....error#3..........\n");
            return FALSE;
        }

        if(!msAPI_FCtrl_EntrySearchByName(u8EnvironmentID, PVRFolderName , u8FoldNameLen, &PVRFolderentry))
        {
            msAPI_FSEnv_UnRegister(u8EnvironmentID);
            printf("......msAPI_CIPVRFS_FileDelete....error#4.0..........\n");
            __ASSERT(0);
            return FALSE;
        }
        if(PVRFolderentry.EntryType != ENTRY_TYPE_DIR)
        {
            msAPI_FSEnv_UnRegister(u8EnvironmentID);
            printf("......msAPI_CIPVRFS_FileDelete....error#4.1..........\n");
            __ASSERT(0);
            return FALSE;
        }
        if(msAPI_FCtrl_DirectoryChange(u8EnvironmentID,&PVRFolderentry))
        {
            if(msAPI_FCtrl_EntrySearchByName(u8EnvironmentID, SecureFolderName , FS_strlen_U(SecureFolderName), &SecureFolderentry))
            {
                if(msAPI_FCtrl_DirectoryChange(u8EnvironmentID,&SecureFolderentry))
                {
                    U16 SecurePineventName[] = PVR_PIN_EVENT_MAP_FILENAME;
                    U16 SecureLicenseName[] = PVR_URI_LICENSE_MAP_FILENAME;
                    if(msAPI_FCtrl_EntrySearchByName(u8EnvironmentID, SecurePineventName, FS_strlen_U(SecurePineventName), &fileentry))
                    {
                        if (!msAPI_FCtrl_FileDelete(&fileentry))
                        {
                            printf("......msAPI_CIPVRFS_FileDelete....error#5..........\n");
                        }
                    }

                    if(msAPI_FCtrl_EntrySearchByName(u8EnvironmentID, SecureLicenseName, FS_strlen_U(SecureLicenseName), &fileentry))
                    {
                        if (!msAPI_FCtrl_FileDelete(&fileentry))
                        {
                            printf("......msAPI_CIPVRFS_FileDelete....error#6..........\n");
                        }
                    }
                }
                if (!msAPI_FCtrl_FileDelete(&SecureFolderentry))
                {
                    printf("......msAPI_CIPVRFS_FileDelete....error#7.........\n");
                }
            }
        }
        if (!msAPI_FCtrl_FileDelete(&PVRFolderentry))
        {
            __ASSERT(0);
            printf("......msAPI_CIPVRFS_FileDelete....error#8..........\n");
            msAPI_FSEnv_UnRegister(u8EnvironmentID);
            return FALSE;
        }
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        return TRUE;
    }

    return FALSE;
}
#endif
/***************************************************************************************/
/// Open file for sequential read/write
/// @param -pu16FileName \b IN: File name.
/// @return -success: return file handle; else: return INVALID_FILE_HANDLE.
/***************************************************************************************/
U8 msAPI_PVRFS_FileOpen(U16* pu16FileName, EN_PVRFS_OPEN_MODE mode)
{
    if (pu16FileName == NULL)
        return INVALID_FILE_HANDLE;

    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
    {
#ifndef OBAMA
        EN_BKF_OPEN_MODE BKFSMode = BKF_OPEN_FOR_READ;
        switch(mode)
        {
            case PVRFS_OPEN_FOR_READ:
            {
                BKFSMode = BKF_OPEN_FOR_READ;
                break;
            }
            case PVRFS_OPEN_FOR_WRITE:
            {
                BKFSMode = BKF_OPEN_FOR_WRITE;
                break;
            }
            case PVRFS_OPEN_FOR_RING_WRITE:
            {
                BKFSMode = BKF_OPEN_FOR_RING_WRITE;
                break;
            }
            default:
            {
                __ASSERT(0);
                return INVALID_FILE_HANDLE;
            }
        }
        return msAPI_BKFS_FileOpen(pu16FileName, BKFSMode);
#endif
    }
    else if ((_enPVRFSFileSystemType == PVR_FS_N51FAT32) || (msAPI_PVRFS_IsLinuxFileSystemType(_enPVRFSFileSystemType)))
    {
        FileEntry entry;
        U8 u8HandleID = INVALID_FILE_HANDLE;
        U8 N51FSMode = OPEN_MODE_BINARY_FOR_READ;
        U8 u8EnvironmentID = msAPI_FSEnv_Register(_u8DiskDriveIndex);

        if(u8EnvironmentID == INVALID_FS_ENVIRONMENT_INDEX)
        {
            __ASSERT(0);
            return INVALID_FILE_HANDLE;
        }

        if (!PVRFS_EnterPVRDirectory(u8EnvironmentID))
        {
            __ASSERT(0);
            msAPI_FSEnv_UnRegister(u8EnvironmentID);
            return INVALID_FILE_HANDLE;
        }

        if(!msAPI_FCtrl_EntrySearchByName(u8EnvironmentID, pu16FileName, FS_strlen_U(pu16FileName), &entry))
        {
            msAPI_FSEnv_UnRegister(u8EnvironmentID);
            return INVALID_FILE_HANDLE;
        }

        switch(mode)
        {
            case PVRFS_OPEN_FOR_READ:
            {
                N51FSMode = OPEN_MODE_BINARY_FOR_READ;
                break;
            }
            case PVRFS_OPEN_FOR_WRITE:
            {
                N51FSMode = OPEN_MODE_BINARY_FOR_APPEND;
                break;
            }
            case PVRFS_OPEN_FOR_RING_WRITE:
            {
                N51FSMode = OPEN_MODE_BINARY_FOR_READ_APPEND;
                break;
            }
            default:
            {
                __ASSERT(0);
                msAPI_FSEnv_UnRegister(u8EnvironmentID);
                return INVALID_FILE_HANDLE;
            }
        }

        u8HandleID = msAPI_FCtrl_FileOpen(&entry, N51FSMode);
        if (u8HandleID == INVALID_FILE_HANDLE)
        {
            msAPI_FSEnv_UnRegister(u8EnvironmentID);
            return INVALID_FILE_HANDLE;
        }

        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        return u8HandleID;
    }

    return INVALID_FILE_HANDLE;
}

/***************************************************************************************/
/// Close file with file handle
/// @param -u8HandleID \b IN: File handle which comes from file open.
/// @return -success: return true; else: return false.
/***************************************************************************************/
BOOLEAN msAPI_PVRFS_FileClose(U8 u8HandleID)
{
    if (u8HandleID == INVALID_FILE_HANDLE)
        return FALSE;

    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
    {
#ifndef OBAMA
        return msAPI_BKFS_FileClose(u8HandleID);
#endif
    }
    else if ((_enPVRFSFileSystemType == PVR_FS_N51FAT32) || (msAPI_PVRFS_IsLinuxFileSystemType(_enPVRFSFileSystemType)))
    {
        if (msAPI_FCtrl_FileClose(u8HandleID) != FILE_CLOSE_RESULT_ERROR)
        {
            //update disk free space
            LongLong llTotalRecordedSizeKB;
            llTotalRecordedSizeKB = LL_LongDivU32(&_llTotalRecordedSize, BYTES_PER_KBYTES);
            if (_u32DiskFreeSizeKB > llTotalRecordedSizeKB.Lo)
                _u32DiskFreeSizeKB = _u32DiskFreeSizeKB - llTotalRecordedSizeKB.Lo;
            else _u32DiskFreeSizeKB = 0; //disk full
            _llTotalRecordedSize.Lo = 0;
            _llTotalRecordedSize.Hi = 0;
            return TRUE;
        }
    }

    return FALSE;
}

/***************************************************************************************/
/// Delete file with specific name and directory
/// @param -u8EnvironmentID \b IN: Environment Id which implicate specific directory
/// @param -pu16FileName \b IN: File name
/// @return -success: return true; else: return false.
/***************************************************************************************/
BOOLEAN msAPI_PVRFS_FileDelete(U16* pu16FileName)
{
    if (pu16FileName == NULL)
        return FALSE;

    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
    {
#ifndef OBAMA
        return msAPI_BKFS_FileDelete(pu16FileName);
#endif
    }
    else if ((_enPVRFSFileSystemType == PVR_FS_N51FAT32) || (msAPI_PVRFS_IsLinuxFileSystemType(_enPVRFSFileSystemType)))
    {
        FileEntry entry;
        U8 u8EnvironmentID = msAPI_FSEnv_Register(_u8DiskDriveIndex);

        if(u8EnvironmentID == INVALID_FS_ENVIRONMENT_INDEX)
        {
            __ASSERT(0);
            return FALSE;
        }

        //enter default PVR directory
        if (!PVRFS_EnterPVRDirectory(u8EnvironmentID))
        {
            msAPI_FSEnv_UnRegister(u8EnvironmentID);
            return FALSE;
        }

        if(msAPI_FCtrl_EntrySearchByName(u8EnvironmentID, pu16FileName, FS_strlen_U(pu16FileName), &entry))
        {
            LongLong llFileLength;
            U8 u8HandleID = msAPI_FCtrl_FileOpen(&entry, OPEN_MODE_BINARY_FOR_READ);
            if (u8HandleID == INVALID_FILE_HANDLE)
            {
                 __ASSERT(0);
                msAPI_FSEnv_UnRegister(u8EnvironmentID);
                return FALSE;
            }
            llFileLength = msAPI_PVRFS_FileLength(u8HandleID);

            if (msAPI_FCtrl_FileClose(u8HandleID) == FILE_CLOSE_RESULT_ERROR)
            {
                __ASSERT(0);
                msAPI_FSEnv_UnRegister(u8EnvironmentID);
                return FALSE;
            }

            if (!msAPI_FCtrl_FileDelete(&entry))
            {
                __ASSERT(0);
                msAPI_FSEnv_UnRegister(u8EnvironmentID);
                return FALSE;
            }
            //update disk free space
            _u32DiskFreeSizeKB = _u32DiskFreeSizeKB + (llFileLength.Lo/BYTES_PER_KBYTES);

            msAPI_FSEnv_UnRegister(u8EnvironmentID);
            return TRUE;
        }
        msAPI_FSEnv_UnRegister(u8EnvironmentID);
    }

    return FALSE;
}
#if 0
/***************************************************************************************/
/// Check if file exists in _MSPVR directory
/// @param -u8EnvironmentID \b IN: Environment Id which implicate specific directory
/// @param -pu16FileName \b IN: File name
/// @return -success: return true; else: return false.
/***************************************************************************************/
BOOLEAN msAPI_PVRFS_FileExist_InPVRDirectory(U8 u8EnvironmentID, U16* pu16FileName)
{
    if ((u8EnvironmentID == INVALID_FS_ENVIRONMENT_INDEX) || (pu16FileName == NULL))
        return FALSE;

    if (_enPVRFSFileSystemType != PVR_FS_N51FAT32)
        return FALSE;

    //enter default PVR directory
    if (!PVRFS_EnterPVRDirectory(u8EnvironmentID))
        return FALSE;

    return msAPI_PVRFS_FileExist(u8EnvironmentID, pu16FileName);
}
#endif
/***************************************************************************************/
/// Check if file exists in current directory
/// @param -u8EnvironmentID \b IN: Environment Id which implicate specific directory
/// @param -pu16FileName \b IN: File name
/// @return -success: return true; else: return false.
/***************************************************************************************/
BOOLEAN msAPI_PVRFS_FileExist(U16* pu16FileName)
{
    if (pu16FileName == NULL)
        return FALSE;

    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
    {
#ifndef OBAMA
        return msAPI_BKFS_FileExist(pu16FileName);
#endif
    }
    else if ((_enPVRFSFileSystemType == PVR_FS_N51FAT32) || (msAPI_PVRFS_IsLinuxFileSystemType(_enPVRFSFileSystemType)))
    {
        FileEntry entry;
        U8 u8EnvironmentID = msAPI_FSEnv_Register(_u8DiskDriveIndex);

        if(u8EnvironmentID == INVALID_FS_ENVIRONMENT_INDEX)
        {
            __ASSERT(0);
            return FALSE;
        }

        //enter default PVR directory
        if (!PVRFS_EnterPVRDirectory(u8EnvironmentID))
        {
            msAPI_FSEnv_UnRegister(u8EnvironmentID);
            return FALSE;
        }

        if(msAPI_FCtrl_EntrySearchByName(u8EnvironmentID, pu16FileName, FS_strlen_U(pu16FileName), &entry))
        {
            msAPI_FSEnv_UnRegister(u8EnvironmentID);
            return TRUE;
        }

        msAPI_FSEnv_UnRegister(u8EnvironmentID);
        return FALSE;
    }

    return FALSE;
}

/***************************************************************************************/
/// Get total file length by specific file handle
/// @param -u8HandleID \b IN: File handle which comes from file open.
/// @return file length with unit "byte"
/***************************************************************************************/
LongLong msAPI_PVRFS_FileLength(U8 u8HandleID)
{
    LongLong fileLen;
    fileLen.Hi=FAT_MAX_FILE_LENGTH;
    fileLen.Lo=FAT_MAX_FILE_LENGTH;

    if (u8HandleID == INVALID_FILE_HANDLE)
        return fileLen;

    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
    {
#ifndef OBAMA
        return msAPI_BKFS_FileLength(u8HandleID);
#endif
    }
    else if ((_enPVRFSFileSystemType == PVR_FS_N51FAT32) || (msAPI_PVRFS_IsLinuxFileSystemType(_enPVRFSFileSystemType)))
    {
        fileLen = msAPI_FCtrl_FileLength_LongLong(u8HandleID);
        return fileLen;
    }

    return fileLen;
}

/***************************************************************************************/
/// Read file by given file handle id, read buffer, and read length.
/// @param -u8HandleID \b IN: File handle which comes from file open.
/// @param -u32Buffer \b OUT: Buffer that will be written with read data.
/// @param -u32ReadLength \b IN: Read length.
/// @return -processed bytes. If read successfully, should return u32ReadLength.
/***************************************************************************************/
U32 msAPI_PVRFS_FileRead(U8 u8HandleID, U32 u32Buffer, U32 u32ReadLength)
{
    if ((u8HandleID == INVALID_FILE_HANDLE) || (u32Buffer == 0))
        return FAT_MAX_FILE_LENGTH;

    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
    {
#ifndef OBAMA
        return msAPI_BKFS_FileRead(u8HandleID, u32Buffer, u32ReadLength); //return processed bytes
#endif
    }
    else if ((_enPVRFSFileSystemType == PVR_FS_N51FAT32) || (msAPI_PVRFS_IsLinuxFileSystemType(_enPVRFSFileSystemType)))
    {
        U32 u32LeftBytes;

      #ifdef __aeon__ //ndef MIPS_CHAKRA //[8051+Aeon]
        u32LeftBytes = msAPI_FCtrl_FileRead(u8HandleID, u32Buffer, u32ReadLength); //return left bytes, for 8051+Aeon, NonOS
      #else //[mips][arm]
        u32LeftBytes = msAPI_FCtrl_FileRead2(u8HandleID, u32Buffer, u32ReadLength); //return left bytes, for MIPS, OS
      #endif

        return (u32ReadLength - u32LeftBytes); //return processed bytes
    }

    return FAT_MAX_FILE_LENGTH;
}

/***************************************************************************************/
/// Write file by given file handle id, write buffer, and write length.
/// @param -u8HandleID \b IN: File handle which comes from file open.
/// @param -u32Buffer \b OUT: Buffer with the data that will be written to file.
/// @param -u32WriteLength \b IN: Write length.
/// @return -processed bytes. If write successfully, should return u32WriteLength.
/***************************************************************************************/
U32 msAPI_PVRFS_FileWrite(U8 u8HandleID,U32 u32Buffer,U32 u32WriteLength)
{
    //printf("msAPI_PVRFS_FileWrite(u8HandleID=%u, u32Buffer=0x%X, u32WriteLength=0x%X)\n", u8HandleID, u32Buffer, u32WriteLength);
    //printf("_enPVRFSFileSystemType=%u\n", _enPVRFSFileSystemType);

    if (u8HandleID == INVALID_FILE_HANDLE)
        return FAT_MAX_FILE_LENGTH;

    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
    {
#ifndef OBAMA
        return msAPI_BKFS_FileWrite(u8HandleID, u32Buffer, u32WriteLength); //return processed bytes
#endif
    }
    else if ((_enPVRFSFileSystemType == PVR_FS_N51FAT32) || (msAPI_PVRFS_IsLinuxFileSystemType(_enPVRFSFileSystemType)))
    {
        U32 u32LeftBytes;
        LongLong llFilePos;

        llFilePos = msAPI_PVRFS_FileTell(u8HandleID);

        //printf("llFilePos=%u\n", llFilePos);

      #if 0//ndef MIPS_CHAKRA
        u32LeftBytes = msAPI_FCtrl_FileWrite(u8HandleID, u32Buffer, u32WriteLength); //return left bytes, for 8051+AEON
      #else //Obama+Chakra2
        u32LeftBytes = msAPI_FCtrl_FileWrite(u8HandleID, _VA2PA(u32Buffer), u32WriteLength); //return left bytes, for MIPS
      #endif

        //printf("u32LeftBytes=0x%X\n", u32LeftBytes);

        //update total used disk space
        if (!LL_iszero(&llFilePos))
        {
            _llTotalRecordedSize = LL_add(&_llTotalRecordedSize, u32WriteLength - u32LeftBytes);
        }

        return (u32WriteLength - u32LeftBytes); //return processed bytes
    }

    return FAT_MAX_FILE_LENGTH;
}

/***************************************************************************************/
/// File Seek using LongLong length. This can seek position over 4G.
/// @param -u8HandleNo \b IN: File handle id.
/// @param -u32Length \b IN: LongLong seek length. At least 1 sector(for example:512bytes)
/// @param -option \b IN: File seek option.
/// @return -Success: true, else false.
/***************************************************************************************/
BOOLEAN msAPI_PVRFS_FileSeek(U8 u8HandleID,LongLong seekLength,EN_PVRFS_SEEK_OPTION option)
{
    if (u8HandleID == INVALID_FILE_HANDLE)
        return FALSE;

    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
    {
#ifndef OBAMA
        EN_BKF_SEEK_OPTION enBKFSOption = BKF_SEEK_OPTION_FROM_BEGIN;
        switch(option)
        {
            case PVRFS_SEEK_OPTION_FROM_BEGIN:
            {
                enBKFSOption = BKF_SEEK_OPTION_FROM_BEGIN;
                break;
            }
            case PVRFS_SEEK_OPTION_FROM_CURRENT_FORWARD:
            {
                enBKFSOption = BKF_SEEK_OPTION_FROM_CURRENT_FORWARD;
                break;
            }
            case PVRFS_SEEK_OPTION_FROM_CURRENT_BACKWARD:
            {
                enBKFSOption = BKF_SEEK_OPTION_FROM_CURRENT_BACKWARD;
                break;
            }
            default:
            {
                __ASSERT(0);
                return FALSE;
            }
        }
        return msAPI_BKFS_FileSeek(u8HandleID, seekLength, enBKFSOption);
#endif
    }
    else if ((_enPVRFSFileSystemType == PVR_FS_N51FAT32) || (msAPI_PVRFS_IsLinuxFileSystemType(_enPVRFSFileSystemType)))
    {
        EN_FILE_SEEK_OPTION enN51FSOption = FILE_SEEK_SET;
        LongLong fileLen;
        //can not seek an empty file
        fileLen = msAPI_PVRFS_FileLength(u8HandleID);
        if (LL_iszero(&fileLen))
        {
            return FALSE;
        }

        switch(option)
        {
            case PVRFS_SEEK_OPTION_FROM_BEGIN:
            {
                enN51FSOption = FILE_SEEK_SET;
                break;
            }
            case PVRFS_SEEK_OPTION_FROM_CURRENT_FORWARD:
            {
                enN51FSOption = FILE_SEEK_CUR;
                break;
            }
            default:
            {
                __ASSERT(0);
                return FALSE;
            }
        }
        return msAPI_FCtrl_FileSeek_LongLong(u8HandleID, seekLength, enN51FSOption);
    }

    return FALSE;
}

/***************************************************************************************/
/// Get the file current position in LongLong format.
/// @param -u8HandleID \b IN: File handle id.
/// @return -File current position in LongLong format.
/***************************************************************************************/
LongLong msAPI_PVRFS_FileTell(U8 u8HandleID)
{
    LongLong filePos;
    filePos.Hi=FAT_MAX_FILE_LENGTH;
    filePos.Lo=FAT_MAX_FILE_LENGTH;

    if (u8HandleID == INVALID_FILE_HANDLE)
        return filePos;

    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
    {
#ifndef OBAMA
        return msAPI_BKFS_FileTell(u8HandleID);
#endif
    }
    else if ((_enPVRFSFileSystemType == PVR_FS_N51FAT32) || (msAPI_PVRFS_IsLinuxFileSystemType(_enPVRFSFileSystemType)))
    {
        filePos = msAPI_FCtrl_FileTell_LongLong(u8HandleID);
        return filePos;
    }

    return filePos;
}

/***************************************************************************************/
/// Get first file entry in specific directory (default directory of PVR)
/// @param -u8EnvironmentID \b IN: Environment ID.
/// @param -pEntry \b IN: File entry to find.
/// @return -success: return TRUE; else: return FALSE.
/***************************************************************************************/
BOOLEAN msAPI_PVRFS_GetFirstPVRFile(U8 u8EnvironmentID, FileEntry* fileEntry)
{
    EN_ENTRY_NEXT_RESULT eResult;
    if (u8EnvironmentID >= FS_ENVIRONMENT_NUM)
    {
        __ASSERT(0);
        return FALSE;
    }

    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
        return FALSE;
    else if ((_enPVRFSFileSystemType == PVR_FS_N51FAT32) || (msAPI_PVRFS_IsLinuxFileSystemType(_enPVRFSFileSystemType)))
    {
        if (!PVRFS_EnterPVRDirectory(u8EnvironmentID))
            return FALSE;

        if (!msAPI_FCtrl_EntryFirst(u8EnvironmentID))
            return FALSE;

        while ((eResult = msAPI_FCtrl_EntryNext(u8EnvironmentID, fileEntry)) != ENTRY_NEXT_RESULT_ERROR)
        {
            if ((fileEntry->EntryType == ENTRY_TYPE_LAST) || (eResult == ENTRY_NEXT_RESULT_LAST))
                return FALSE;

            if ((fileEntry->EntryType == ENTRY_TYPE_DIR_DOT) ||
                (fileEntry->EntryType == ENTRY_TYPE_DIR_DOTDOT) ||
                (fileEntry->EntryAttrib & ENTRY_ATTRIB_HIDDEN))
                continue;

            break; //find first file
        }
        if (fileEntry) return TRUE;
    }

    return FALSE;
}

/***************************************************************************************/
/// Get next file entry in specific directory
/// @param -u8EnvironmentID \b IN: Environment ID.
/// @param -pEntry \b IN: File entry to find.
/// @return -success: return TRUE; else: return FALSE.
/***************************************************************************************/
BOOLEAN msAPI_PVRFS_GetNextPVRFile(U8 u8EnvironmentID, FileEntry* fileEntry)
{
    EN_ENTRY_NEXT_RESULT eResult;
    if (u8EnvironmentID >= FS_ENVIRONMENT_NUM)
    {
        __ASSERT(0);
        return FALSE;
    }

    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
        return FALSE;

    else if ((_enPVRFSFileSystemType == PVR_FS_N51FAT32) || (msAPI_PVRFS_IsLinuxFileSystemType(_enPVRFSFileSystemType)))
    {
        while ((eResult = msAPI_FCtrl_EntryNext(u8EnvironmentID, fileEntry)) != ENTRY_NEXT_RESULT_ERROR)
        {
            if ((fileEntry->EntryType == ENTRY_TYPE_LAST) || (eResult == ENTRY_NEXT_RESULT_LAST))
                return FALSE;

            if ((fileEntry->EntryType == ENTRY_TYPE_DIR_DOT) ||
                (fileEntry->EntryType == ENTRY_TYPE_DIR_DOTDOT) ||
                (fileEntry->EntryAttrib & ENTRY_ATTRIB_HIDDEN))
                continue;

            break; //find next file entry
        }
        if (fileEntry) return TRUE;
    }

    return FALSE;
}

/***************************************************************************************/
/// Get long file name by given file entry.
/// @param -u8EnvironmentID \b IN: Environment ID.
/// @param -pEntry \b IN: File entry to find.
/// @param -address \b IN: MIU address to put thd found file name.
/// @param -charLen \b IN: Length of MIU address.
/// @param -pbShortNameOnly \b IN: File name is short name or not.
/// @return -Length of file name.
/***************************************************************************************/
U8 msAPI_PVRFS_GetFileNameByFileEntry(U8 u8EnvironmentID, FileEntry* pEntry, U32 address, U8 charLen)
{
    BOOLEAN bShortNameOnly;

    if (u8EnvironmentID >= FS_ENVIRONMENT_NUM)
    {
        __ASSERT(0);
        return FALSE;
    }

    return msAPI_FCtrl_EntryGetLongNameByFileEntry(u8EnvironmentID, pEntry, address, charLen, &bShortNameOnly);
}

U16 msAPI_PVRFS_SpeedCheck(void)
{
    U16 PVRFSCheckFileName[13] = {'T','I','M','E','S','H','I','F','T','.','T','S',0}; //must be, need this action to occupy 1st index in index file.
    U16 u16Speed = 0;
    U16 u16CurrentSpeed = 0;
    U32 u32WriteLength = (U32)0x00040000;
    U32 u32ReadLength = (U32)0x00040000;
    U32 u32BestRWLength = (U32)0x00040000;
    U32 u32PrefixWriteLength = (U32)0x00100000; //1MB
    U32 u32TotalWriteLength = 0;
    U32 u32TotalReadLength = 0;
    U8  u8handle_w, u8handle_r;
    //U8  u8BulkCount = 1;
    U8  u8LoopCnt = 5;
    U8  u8Index;
    U32 u32Ts;
    U32 u32testTime = 3000;
    U8  u8DeviceIndex;
    U8  u8DiskDriveIndex;
    BOOLEAN bRet = FALSE;

    if (0 == PVR_READ_SDRAM_LEN)
    {
        u32ReadLength = 0;
    }

    if ((_enPVRFSFileSystemType != PVR_FS_BULKFS) &&
        (_enPVRFSFileSystemType != PVR_FS_N51FAT32) &&
        (!msAPI_PVRFS_IsLinuxFileSystemType(_enPVRFSFileSystemType))
       )
    {
        return 0;
    }

    if (msAPI_PVRFS_IsInitialized() == FALSE)
    {
        __ASSERT(0);
        return 0;
    }

    u8DeviceIndex = msAPI_PVRFS_GetDeviceIndex();
    u8DiskDriveIndex = msAPI_PVRFS_GetDriveIndex();

    if(msAPI_PVRFS_IsPartitionReady(u8DiskDriveIndex, u8DeviceIndex))
    {
        for (u8Index = 0; u8Index < u8LoopCnt; u8Index++)
        {
            if(msAPI_PVRFS_FileExist(PVRFSCheckFileName))
            {
                if(!msAPI_PVRFS_FileDelete(PVRFSCheckFileName))
                {
                    __ASSERT(0);
                    return 0;
                }
            }

            //u8handle_w=BKFS_FileCreateForWrite(PVRFSCheckFileName, BKF_OPEN_FOR_RING_WRITE, &u8BulkCount); //if use BKF_OPEN_FOR_WRITE, it will create TS file.
            u8handle_w=msAPI_PVRFS_FileCreate(PVRFSCheckFileName); //if use BKF_OPEN_FOR_WRITE, it will create TS file.
            u8handle_r=msAPI_PVRFS_FileOpen(PVRFSCheckFileName,PVRFS_OPEN_FOR_READ);

            if( (INVALID_FILE_HANDLE == u8handle_w) || (INVALID_FILE_HANDLE == u8handle_r))
            {
                __ASSERT(0);
                return 0;
            }

        #if 0//def OBAMA
            msAPI_PVRFS_FileWrite(u8handle_w,_PA2VA(((PVR_WRITE_SDRAM_MEMORY_TYPE&MIU1)?PVR_WRITE_SDRAM_ADR|MIU_INTERVAL:PVR_WRITE_SDRAM_ADR)),u32PrefixWriteLength); //Prepare 1M data to stagger R/W sectors.
        #elif 1//defined(MIPS_CHAKRA)
            //msAPI_PVRFS_FileWrite(u8handle_w,_PA2VA(((PVR_WRITE_SDRAM_MEMORY_TYPE&MIU1)?PVR_WRITE_SDRAM_ADR|MIU_INTERVAL:PVR_WRITE_SDRAM_ADR)),u32PrefixWriteLength); //Prepare 1M data to stagger R/W sectors.
            msAPI_PVRFS_FileWrite(u8handle_w, PvrGetWriteSdramAdr_VA(), u32PrefixWriteLength); //Prepare 1M data to stagger R/W sectors.
        #else
            msAPI_PVRFS_FileWrite(u8handle_w,PVR_WRITE_SDRAM_ADR,u32PrefixWriteLength); //Prepare 1M data to stagger R/W sectors.
        #endif

            //Start to write for 5 seconds
            PVRFSDBG(printf("u32WriteLength[0x%lx]\n", u32WriteLength));
            u32TotalWriteLength = 0;
            u32TotalReadLength = 0;
            u32Ts=msAPI_Timer_GetTime0();
            U8 u8USBState = MApp_MassStorage_DeviceConnectionDetect();
            while(msAPI_Timer_DiffTimeFromNow(u32Ts)<u32testTime)
            {
                U32 u32tempLength_w = 0;
                U32 u32tempLength_r = 0;

            #if 0//def OBAMA
                u32tempLength_w=msAPI_PVRFS_FileWrite(u8handle_w,_PA2VA(((PVR_WRITE_SDRAM_MEMORY_TYPE&MIU1)?PVR_WRITE_SDRAM_ADR|MIU_INTERVAL:PVR_WRITE_SDRAM_ADR)),u32WriteLength);
                if (0 != PVR_READ_SDRAM_LEN)
                {
                    u32tempLength_r=msAPI_PVRFS_FileRead(u8handle_r,_PA2VA(((PVR_READ_SDRAM_MEMORY_TYPE&MIU1)?PVR_READ_SDRAM_ADR|MIU_INTERVAL:PVR_READ_SDRAM_ADR)),u32ReadLength);
                }
            #elif 1//defined(MIPS_CHAKRA)
                //u32tempLength_w=msAPI_PVRFS_FileWrite(u8handle_w,_PA2VA(((PVR_WRITE_SDRAM_MEMORY_TYPE&MIU1)?PVR_WRITE_SDRAM_ADR|MIU_INTERVAL:PVR_WRITE_SDRAM_ADR)),u32WriteLength);
                u32tempLength_w=msAPI_PVRFS_FileWrite(u8handle_w, PvrGetWriteSdramAdr_VA(), u32WriteLength);
                if (0 != PVR_READ_SDRAM_LEN)
                {
                    //u32tempLength_r=msAPI_PVRFS_FileRead(u8handle_r,_PA2VA(((PVR_READ_SDRAM_MEMORY_TYPE&MIU1)?PVR_READ_SDRAM_ADR|MIU_INTERVAL:PVR_READ_SDRAM_ADR)),u32ReadLength);
                    u32tempLength_r=msAPI_PVRFS_FileRead(u8handle_r, PvrGetReadSdramAdr_VA(), u32ReadLength);
                }
            #else
                u32tempLength_w=msAPI_PVRFS_FileWrite(u8handle_w,((PVR_WRITE_SDRAM_MEMORY_TYPE&MIU1)?PVR_WRITE_SDRAM_ADR|MIU_INTERVAL:PVR_WRITE_SDRAM_ADR),u32WriteLength);
                if (0 != PVR_READ_SDRAM_LEN)
                {
                    u32tempLength_r=msAPI_PVRFS_FileRead(u8handle_r,((PVR_READ_SDRAM_MEMORY_TYPE&MIU1)?PVR_READ_SDRAM_ADR|MIU_INTERVAL:PVR_READ_SDRAM_ADR),u32ReadLength);
                }
            #endif

                if ((u32tempLength_w != u32WriteLength) || (u32tempLength_r != u32ReadLength))
                {
                    if((!(u8USBState & MS_USB_CONNECTED)) || (!(u8USBState & MS_USB2_CONNECTED)))
                    {
                        bRet = msAPI_PVRFS_FileClose(u8handle_r);
                        bRet = msAPI_PVRFS_FileClose(u8handle_w);
                    }
                    __ASSERT(0); //read, write fail. Fix ID:81984
                    return 0;
                }
                u32TotalWriteLength += u32tempLength_w;
                u32TotalReadLength += u32tempLength_r;
            }
            MS_DEBUG_MSG(printf(" WriteLength[%lu]\n",u32TotalWriteLength));
            PVRFSDBG(printf(" ReadLength[%lu]\n",u32TotalReadLength));

            bRet = msAPI_PVRFS_FileClose(u8handle_r);
            bRet = msAPI_PVRFS_FileClose(u8handle_w);

            //do not delete created timeshift file to occupy 1st index in bulk index file,
            //unless there is no any timeshift bulk to be reserved.
            #ifndef OBAMA
            if (msAPI_PVRFS_GetTimeShiftReservedBulkCnt() == 0)
            #endif
            {
                if(msAPI_PVRFS_FileExist(PVRFSCheckFileName))
                {
                    if(!msAPI_PVRFS_FileDelete(PVRFSCheckFileName))
                    {
                        __ASSERT(0);
                    }
                }
            }

            u16CurrentSpeed = (U16)(((u32TotalWriteLength/(u32testTime/1000)))/BYTES_PER_KBYTES);
            if (u16CurrentSpeed > u16Speed)
            {
                u16Speed = u16CurrentSpeed;
                u32BestRWLength = u32WriteLength;
            }
            //printf("u32WriteLength is %ld, u16CurrentSpeed is %d\n", u32WriteLength/BYTES_PER_KBYTES, u16CurrentSpeed);
            u32WriteLength = u32WriteLength/2; //test 256KB->128KB->64KB->32KB->16KB
            u32ReadLength = u32ReadLength/2;
        }
        //u16Speed = (U16)(((u32TotalWriteLength/(u32testTime/1000)))/BYTES_PER_KBYTES);
        //printf("u32BestRWLength is %ld, u16Speed is %d\n", u32BestRWLength/BYTES_PER_KBYTES, u16Speed);
        #ifndef OBAMA
        if (!msAPI_PVRFS_SetBulkSpeed(u16Speed))
            {__ASSERT(0);}
        if (!msAPI_PVRFS_SetBulkRWKByteOfSpeed((U16)(u32BestRWLength/BYTES_PER_KBYTES)))
            {__ASSERT(0);}
        #endif
        return u16Speed;
    }
    else
    {
        return 0;
    }

    return 0;
}


/******************** Bulk only ******************************************************************/
#if (ENABLE_BULK_FILE_SYSTEM)
BOOLEAN msAPI_PVRFS_CreateBulks(EN_CREATE_BULKS_STATE enCreateBulksState, U8 u8EnvironmentID, U16* u16BulkNum)
{
    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
        return msAPI_BKFS_CreateBulks(enCreateBulksState, u8EnvironmentID, u16BulkNum);

    return FALSE;
}

BKFS_POSITION msAPI_PVRFS_FindFirstPOS(void)
{
    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
        return msAPI_BKFS_FindFirstPOS();

    return 0;
}

BKFS_POSITION msAPI_PVRFS_FindNextBulkFile(BKFS_POSITION pos, U16 *pCurBulkFileName, U16 *pBufU16Len)
{
    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
        return msAPI_BKFS_FindNextBulkFile(pos, pCurBulkFileName, pBufU16Len);

    return 0;
}

BFK_PARA_OPT_RES msAPI_PVRFS_SetBulkFileInfo(U16* pu16BulkFileName, U16* u16BulkFileID, BFK_PROG_INFO info, void *pBuffer, U16 bufLen)
{
    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
        return msAPI_BKFS_SetBulkFileInfo(pu16BulkFileName,  u16BulkFileID, info, pBuffer, bufLen);

    return BKF_PARA_ERROR_NOFILE;
}

BFK_PARA_OPT_RES msAPI_PVRFS_GetBulkFileInfo(U16* pu16BulkFileName, U16* u16BulkFileID, BFK_PROG_INFO info, void *pBuffer, U16 *pBufLen)
{
    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
        return msAPI_BKFS_GetBulkFileInfo(pu16BulkFileName, u16BulkFileID, info, pBuffer, pBufLen);

    return BKF_PARA_ERROR_NOFILE;
}

U32 msAPI_PVRFS_GetBulkVersionNo(void)
{
    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
        return msAPI_BKFS_GetBulkVersionNo();

    return 0;
}

U32 msAPI_PVRFS_GetTotalDiskSizeSetToUsedMB(void)
{
    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
        return msAPI_BKFS_GetTotalDiskSizeSetToUsedMB();

    return 0;
}

U16 msAPI_PVRFS_GetTotalBulkCnt(void)
{
    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
        return msAPI_BKFS_GetTotalBulkCnt();

    return 0;
}

BOOLEAN msAPI_PVRFS_SetBulkRWKByteOfSpeed(U16 u16RWKByteOfSpeed)
{
    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
        return msAPI_BKFS_SetBulkRWKByteOfSpeed(u16RWKByteOfSpeed);

    return TRUE;
}

U16 msAPI_PVRFS_GetBulkRWKByteOfSpeed(void)
{
    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
        return msAPI_BKFS_GetBulkRWKByteOfSpeed();
    else if (_enPVRFSFileSystemType == PVR_FS_N51FAT32)
        return FAT_AVERAGE_READ_WRITE_KBYTES;

    return 0;
}

U16 msAPI_PVRFS_GetBulksNumToCreate(void)
{
    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
        return msAPI_BKFS_GetBulksNumToCreate();

    return 0;
}

U16 msAPI_PVRFS_GetBulkSpeed(void)
{
    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
        return msAPI_BKFS_GetBulkSpeed();

    return FAT_DEFAULT_DISK_SPEED_KBYTES_PER_SEC; //if non BKFS, must return > 0
}

BOOLEAN msAPI_PVRFS_SetBulkSpeed(U16 u16Speed)
{
    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
        return msAPI_BKFS_SetBulkSpeed(u16Speed);

    return TRUE;
}

BOOLEAN msAPI_PVRFS_SetTimeShiftReservedBulkCnt(U16 u16BulkCnt)
{
    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
        return msAPI_BKFS_SetTimeShiftReservedBulkCnt(u16BulkCnt);

    return FALSE;
}

U16 msAPI_PVRFS_GetTimeShiftReservedBulkCnt(void)
{
    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
        return msAPI_BKFS_GetTimeShiftReservedBulkCnt();

    return 0;
}

BOOLEAN msAPI_PVRFS_SetTimeShiftRecordLengthMB(U32 u32TimeShiftRecordLengthMB)
{
    MaxRecordSize = u32TimeShiftRecordLengthMB;

    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
        return msAPI_BKFS_SetTimeShiftRecordLengthMB(u32TimeShiftRecordLengthMB);

    return FALSE;
}

U32 msAPI_PVRFS_GetTimeShiftRecordLengthMB(void)
{
    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
    {
        return msAPI_BKFS_GetTimeShiftRecordLengthMB();
    }
    else
        return MaxRecordSize;

    return 0;
}

BOOLEAN msAPI_PVRFS_SetMaxUsedBulkFileEntryIndex(U16 u16MaxUsedBulkFileEntryIndex)
{
    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
        return msAPI_BKFS_SetMaxUsedBulkFileEntryIndex(u16MaxUsedBulkFileEntryIndex);

    return FALSE;
}

U16 msAPI_PVRFS_GetMaxUsedBulkFileEntryIndex(void)
{
    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
        return msAPI_BKFS_GetMaxUsedBulkFileEntryIndex();

    return 0;
}

BOOLEAN msAPI_PVRFS_SetDefaultDiskDriveIndex(U8 u8DefaultDrive)
{
    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
        return msAPI_BKFS_SetDefaultDiskDriveIndex(u8DefaultDrive);

    return FALSE;
}

U8 msAPI_PVRFS_GetDefaultDiskDriveIndex(void)
{
    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
        return msAPI_BKFS_GetDefaultDiskDriveIndex();

    return 0;
}

void msAPI_PVRFS_SetCreateBulksState(EN_CREATE_BULKS_STATE enState)
{
    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
        msAPI_BKFS_SetCreateBulksState(enState);

    return;
}

EN_CREATE_BULKS_STATE msAPI_PVRFS_GetCreateBulksState(void)
{
    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
        return msAPI_BKFS_GetCreateBulksState();

    return EN_CREATE_BULKS_DONE;
}

U16 msAPI_PVRFS_GetCurrentCreateBulkNum(void)
{
    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
        return msAPI_BKFS_GetCurrentCreateBulkNum();

    return 0;
}

BOOLEAN msAPI_PVRFS_IsBulkFileReady(U8 u8DiskDriveIndex, U16* u16BulkIndex, BOOLEAN* bFinished)
{
    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
        return msAPI_BKFS_IsBulkFileReady(u8DiskDriveIndex, u16BulkIndex, bFinished);

    return 0;
}

EN_BFK_VERSION_CHECK msAPI_PVRFS_isBulkVersionChanged(void)
{
    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
        return msAPI_BKFS_isBulkVersionChanged();

    return BKF_VERCHK_ERROR_GET_VERSION;
}

void msAPI_PVRFS_ResetCurrentCreateBulkNum(void)
{
    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
        msAPI_BKFS_ResetCurrentCreateBulkNum();

    return;
}

void msAPI_PVRFS_SetTotalDiskSizeUsedMB(U32 u32TotalDiskSizeSetToUsed)
{
    //if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
        msAPI_BKFS_SetTotalDiskSizeUsedMB(u32TotalDiskSizeSetToUsed);

    return;
}

BOOLEAN msAPI_PVRFS_ResetFreeCluster(void)
{
    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
        return msAPI_BKFS_ResetFreeCluster();

    return FALSE;
}

/*U16 msAPI_PVRFS_SpeedCheck(void)
{
    if (_enPVRFSFileSystemType == PVR_FS_BULKFS)
        return msAPI_BKFS_SpeedCheck();

    return 0;
}*/
#endif //#if (ENABLE_BULK_FILE_SYSTEM)

//#else
//    code U8 _DUMMY;
//#endif
#endif // #if ENABLE_PVR

#endif //#ifndef ATSC_SYSTEM
#undef MSAPI_PVR_FILE_SYSTEM_C
