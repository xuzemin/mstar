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

#define FAT_CACHE_C

#include "datatype.h"
#include "debug.h"

#include "FSUtil.h"
#include "msAPI_FSCommon.h"
#include "msAPI_FCtrl.h"
#include "msAPI_FAT.h"
#include "msAPI_FSEnv.h"
#include "msAPI_MSDCtrl.h"
#include "FAT_Cache.h"
#include <string.h>

#define FATC_DBG(x) //x

//to keep API clear
extern U32 FAT_FATStructureGetNextCluster( U8 u8fsid, U32 u32DirEntryClusterNo );
extern U32 FAT_FATGetSectorNo( U8 u8fsid, U32 u32ClusterNo );
extern U32 FAT_FATGetClusterStatus( U8 u8FatType, U32 u32FatTotalClusterNo, U32 u32ClusterNo );
extern FAT_FileInode *FAT_File_GetInodeFromHandle(U8 u8FileHandleID);


#if 0
//=======================================================================================
//This function should not be invoked under root of FAT16/12 partition
static BOOLEAN _DirectoryClusterChainFetch(U32 u32CurrentClusterNo,U8 u8EnvironmentId,FAT_FileSysStruct* pFAT_FileSys)
{
    FAT_Environment *pFAT_Env;
    U32 u32ClusterStatus;
    U16 u16Index;


    pFAT_Env = (FAT_Environment*)FAT_GetXData(u8EnvironmentId, FAT_XDATA_OPTION_ENVIRONMENT);
    memset( (U8*)&pFAT_Env->stCurrentDirectory.u32ClusterChain[0], 0xFF, sizeof(pFAT_Env->stCurrentDirectory.u32ClusterChain));
    FAT_ReturnXData();


    //*fetch cluster chain of current directory=====================================//
    u16Index = 0;
    while ( TRUE )
    {


        u32ClusterStatus = FAT_FATGetClusterStatus( pFAT_FileSys->stFAT.u8FATType, pFAT_FileSys->stFAT.u32FATTotalClusterNo, u32CurrentClusterNo );

        switch ( u32ClusterStatus )
        {
                case FAT_CLUSTER_NOT_USED:      break;

                case FAT_CLUSTER_ALLOCATED:
                {
                        pFAT_Env = (FAT_Environment*)FAT_GetXData(u8EnvironmentId, FAT_XDATA_OPTION_ENVIRONMENT);
                        pFAT_Env->stCurrentDirectory.u32ClusterChain[u16Index] = u32CurrentClusterNo;
                        FAT_ReturnXData();

                        break;
                }

                case FAT_CLUSTER_FINAL:
                {
                        pFAT_Env = (FAT_Environment*)FAT_GetXData(u8EnvironmentId, FAT_XDATA_OPTION_ENVIRONMENT);
                        pFAT_Env->stCurrentDirectory.u32ClusterChain[u16Index] = u32CurrentClusterNo;
                        pFAT_Env->stCurrentDirectory.u16ClusterChainIndex=0;
                        FAT_ReturnXData();

                        return TRUE;                      //last cluster# of cluster chain
                 }
                case FAT_CLUSTER_RESERVED:      break;

                case FAT_CLUSTER_DEFECTIVE:     break;
        }

        u32CurrentClusterNo = FAT_FATStructureGetNextCluster( u8EnvironmentId, u32CurrentClusterNo );
        u16Index++;

        if(u16Index>=FAT_MAX_DIRECTORY_CLUSTER_COUNT)
        {
            pFAT_Env = (FAT_Environment*)FAT_GetXData(u8EnvironmentId, FAT_XDATA_OPTION_ENVIRONMENT);
            pFAT_Env->stCurrentDirectory.u16ClusterChainIndex=0;
            FAT_ReturnXData();
            return TRUE;
        }

    }
}
#endif

//fetch clusters from directoryStartcluster
BOOLEAN FAT_Cache_DirectoryClusterFetch(U8 u8EnvironmentId)
{

    FAT_Environment *pFAT_Env;
    FAT_FileSysStruct* pstFAT_FileSys;
    U8 u8FAT_Type;
    FS_EnvironmentStruct *pFS_Env;
    U8 fsid;

    pFS_Env = msAPI_FSEnv_GetEnvironment(u8EnvironmentId);
    if(pFS_Env == NULL)
    {
        return FALSE;
    }

    fsid=pFS_Env->u8FileSystemID;
    pstFAT_FileSys=(FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(fsid);

    u8FAT_Type=pstFAT_FileSys->stFAT.u8FATType;

    pFAT_Env = (FAT_Environment*)FAT_GetAddr(u8EnvironmentId, FAT_XDATA_OPTION_ENVIRONMENT);
    pFAT_Env->stCurrentDirectory.u32CurrentCluster=pFAT_Env->stCurrentDirectory.u32CurrentDirStartClusterNo;

    return TRUE;
}


EN_FAT_CACHE_MOVE_RESULT FAT_Cache_DirectoryClusterNext(U8 u8EnvironmentId)
{

    FAT_Environment *pFAT_Env;
    FAT_FileSysStruct* pstFAT_FileSys;
    U8 u8FAT_Type;
    U32 _Cluster;
    U32 totalClusters;
    U32 currentCluster;
    U32 currentDirStartCluster;
    U32 rootDirStartClusterNo;

    EN_FAT_CACHE_MOVE_RESULT result=FAT_CACHE_MOVE_RESULT_ERROR;

    FS_EnvironmentStruct *pFS_Env;
    U8 fsid;

    pFS_Env = msAPI_FSEnv_GetEnvironment(u8EnvironmentId);
    if(pFS_Env == NULL)
    {
		__ASSERT(0);
        return FAT_CACHE_MOVE_RESULT_ERROR;
    }

    fsid=pFS_Env->u8FileSystemID;

    pstFAT_FileSys=(FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(fsid);

    u8FAT_Type=pstFAT_FileSys->stFAT.u8FATType;
    totalClusters=pstFAT_FileSys->stFAT.u32FATTotalClusterNo;
    rootDirStartClusterNo=pstFAT_FileSys->u32RootDirStartClusterNo;

    pFAT_Env = (FAT_Environment*)FAT_GetAddr(u8EnvironmentId, FAT_XDATA_OPTION_ENVIRONMENT);

    currentCluster=pFAT_Env->stCurrentDirectory.u32CurrentCluster;
    currentDirStartCluster=pFAT_Env->stCurrentDirectory.u32CurrentDirStartClusterNo;

    //for FAT16/12
    if((u8FAT_Type!=FAT_TYPE_FAT32)&&currentDirStartCluster==rootDirStartClusterNo)
    {
        result=FAT_CACHE_MOVE_RESULT_SUCCESS;
    }
    else
    {
        U32 clusterStatus=FAT_CLUSTER_RESERVED;
         _Cluster=FAT_FATStructureGetNextCluster(fsid,currentCluster);

        clusterStatus=FAT_FATGetClusterStatus(u8FAT_Type,totalClusters,_Cluster);
        if(clusterStatus==FAT_CLUSTER_FINAL)
        {
            result=FAT_CACHE_MOVE_RESULT_IS_LAST;
        }
        else if(clusterStatus==FAT_CLUSTER_ALLOCATED)
        {
            result=FAT_CACHE_MOVE_RESULT_SUCCESS;
            pFAT_Env = (FAT_Environment*)FAT_GetAddr(u8EnvironmentId, FAT_XDATA_OPTION_ENVIRONMENT);
            pFAT_Env->stCurrentDirectory.u32CurrentCluster=_Cluster;

        }
        else
        {
            __ASSERT(0);
            result=FAT_CACHE_MOVE_RESULT_IS_LAST; //mark as last cluster.
        }

    }

    return result;
}






U32 FAT_Cache_DirectoryClusterGetCurrent(U8 u8EnvironmentId)
{

    FAT_Environment *pFAT_Env;
    U32 u32CurrentClusterNo;

    pFAT_Env = (FAT_Environment*)FAT_GetAddr(u8EnvironmentId, FAT_XDATA_OPTION_ENVIRONMENT);

    u32CurrentClusterNo=pFAT_Env->stCurrentDirectory.u32CurrentCluster;

    return u32CurrentClusterNo;
}


//==============================================================================
// Means "always" to fetch bytes from disk to the cache at start at parameter sector.
// The u16OffsetSector is relative to u32CurClusterNo.

static BOOLEAN FAT_Cache_DirectoryDirEntryCacheFetch( U8 u8EnvironmentID, U32 u32CurClusterNo, U16 u16OffsetSector)
{
    U32 u32DirEntryStartSectorNo;
    FS_EnvironmentStruct *pFS_Env;
    FAT_Environment *pFAT_Env;
    FAT_FileSysStruct *pstFAT_fileSys;
    U8 u8DeviceIndex;
    U8 u8SecPerClus;
    U8 u8FATType;
    U32 u32FATTotalClusterNo;
    U32 u32RootDirStartClusterNo;
    U16 u16BytePerSec;
    U8 u8SectorSize;
//    U16 u16ChainIndex;
    U32 u32NextClusNo;
    U32 u8SectorReadSize;
    U16 directoryEntryCacheCount;

    EN_FAT_CACHE_MOVE_RESULT result=FAT_CACHE_MOVE_RESULT_SUCCESS;

    //*[01]get file system==============================================================*//
    pFS_Env = msAPI_FSEnv_GetEnvironment(u8EnvironmentID);
    if(pFS_Env == NULL)
    {
		__ASSERT(0);
        return FALSE;
    }

    pstFAT_fileSys=(FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(pFS_Env->u8FileSystemID);

    u8DeviceIndex=pstFAT_fileSys->DeviceIndex;
    u8SecPerClus = pstFAT_fileSys->stBootSector.BPB_SecPerClus;
    u8FATType=pstFAT_fileSys->stFAT.u8FATType;
    u32FATTotalClusterNo=pstFAT_fileSys->stFAT.u32FATTotalClusterNo;
    u32RootDirStartClusterNo=pstFAT_fileSys->u32RootDirStartClusterNo;
    u16BytePerSec=pstFAT_fileSys->stBootSector.BPB_BytsPerSec;
    directoryEntryCacheCount=pstFAT_fileSys->u16DirEntryCacheCount;

    u8SectorSize = (U8)(((U32)sizeof(DirEntryStruct))*directoryEntryCacheCount / u16BytePerSec);


    //*[02]read DirEntryCache to environment pool=======================================*//
    u32DirEntryStartSectorNo = FAT_FATGetSectorNo( pFS_Env->u8FileSystemID, u32CurClusterNo );

    //printf("\nDirEntryStartSectorNo:0x%08lx\n",u32DirEntryStartSectorNo);

    if(u8SecPerClus >= u8SectorSize ||
       ((u32CurClusterNo==u32RootDirStartClusterNo)&&(u8FATType==FAT_TYPE_FAT12||u8FATType==FAT_TYPE_FAT16))//For FAT12/16 in Root

      )
    {
        if ( !msAPI_MSDCtrl_SectorRead( u8DeviceIndex, u32DirEntryStartSectorNo + u16OffsetSector, (U32)u8SectorSize, ( U32 )FAT_GetMIUAddress(u8EnvironmentID, FAT_XDATA_OPTION_DIR_ENTRY_CACHE) ) )
        {
            __ASSERT(0);
            return FALSE;
        }
    }
    else
    {

        u8SectorReadSize = 0;
        while(u8SectorSize > 0)
        {
            if ( !msAPI_MSDCtrl_SectorRead( u8DeviceIndex, u32DirEntryStartSectorNo + u16OffsetSector, (U32)u8SecPerClus, ( U32 )FAT_GetMIUAddress(u8EnvironmentID, FAT_XDATA_OPTION_DIR_ENTRY_CACHE) + (U32)u16BytePerSec * u8SectorReadSize) )
            {
                __ASSERT(0);
                return FALSE;
            }

            result=FAT_Cache_DirectoryClusterNext(u8EnvironmentID);

            if(result==FAT_CACHE_MOVE_RESULT_IS_LAST)
            {
                break;
            }
            else if(result==FAT_CACHE_MOVE_RESULT_ERROR)
            {
                __ASSERT(0);
                return FALSE;
            }

            u32NextClusNo = FAT_Cache_DirectoryClusterGetCurrent(u8EnvironmentID);


            u32DirEntryStartSectorNo = FAT_FATGetSectorNo( pFS_Env->u8FileSystemID, u32NextClusNo );
            u8SectorSize -= u8SecPerClus;
            u8SectorReadSize += u8SecPerClus;

        }

    }

    //*[03]update FAT_Environment=======================================================*//
    pFAT_Env = (FAT_Environment*)FAT_GetAddr(u8EnvironmentID, FAT_XDATA_OPTION_ENVIRONMENT);

    pFAT_Env->stCurrentDirectory.u16DirEntryCacheOffsetSectorNo = u16OffsetSector;
    pFAT_Env->stCurrentDirectory.u32CurrentDirEntryCacheClusterNo = u32CurClusterNo;
    pFAT_Env->stCurrentDirectory.s16DirEntryCacheCurrentIndex = -1;

    //FATDBG(dumpMIU(( U32 )FAT_GetEnvironmentMIUAddress(u8EnvironmentID, FAT_DIR_ENTRY_CACHE), 32););

    return TRUE;
}


U8 FAT_Cache_DirecotryDirEntryCacheNext( U8 u8EnvironmentID )
{
    FS_EnvironmentStruct *pFS_Env;
    FAT_Environment *pFAT_Env;
    FAT_FileSysStruct *pstFAT_FileSys;
    U16 u16TempDirEntryCacheOffsetSectorNo;
    U32 u32CurrentDirEntryCacheClusterNo, u32NextDirEntryCacheClusterNo;
    U8 u8FAT_Type;
    U32 u32RootDirStartClusterNo;
    U32 u32RootDirTotalSectorCount;
    U32 u32FATTotalClusterNo;
    U8 BPB_SecPerClus;
    U16 u16BytePerSec;
    U8 u8SectorSize;
    U16 dirEntryCacheCount;

    //*get FAT file system=========================================================//
    pFS_Env = msAPI_FSEnv_GetEnvironment(u8EnvironmentID);
    if(pFS_Env == NULL)
    {
		__ASSERT(0);
        return FALSE;
    }

    pstFAT_FileSys=(FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(pFS_Env->u8FileSystemID);

    u8FAT_Type=pstFAT_FileSys->stFAT.u8FATType;
    u32RootDirStartClusterNo=pstFAT_FileSys->u32RootDirStartClusterNo;
    u32RootDirTotalSectorCount=pstFAT_FileSys->u32RootDirTotalSectorCount;
    BPB_SecPerClus=pstFAT_FileSys->stBootSector.BPB_SecPerClus;
    u32FATTotalClusterNo=pstFAT_FileSys->stFAT.u32FATTotalClusterNo;
    u16BytePerSec=pstFAT_FileSys->stBootSector.BPB_BytsPerSec;
    dirEntryCacheCount=pstFAT_FileSys->u16DirEntryCacheCount;


    u8SectorSize = (U8)(((U32)sizeof(DirEntryStruct))*dirEntryCacheCount/u16BytePerSec);

    //*get FAT_Environment info==========================================================*//
    pFAT_Env = (FAT_Environment*)FAT_GetAddr(u8EnvironmentID, FAT_XDATA_OPTION_ENVIRONMENT);

    u32CurrentDirEntryCacheClusterNo = pFAT_Env->stCurrentDirectory.u32CurrentDirEntryCacheClusterNo;
    u16TempDirEntryCacheOffsetSectorNo = pFAT_Env->stCurrentDirectory.u16DirEntryCacheOffsetSectorNo;

    u16TempDirEntryCacheOffsetSectorNo += u8SectorSize;
    u32NextDirEntryCacheClusterNo = u32CurrentDirEntryCacheClusterNo;

    //For FAT12/16 in Root
    if((u32CurrentDirEntryCacheClusterNo==u32RootDirStartClusterNo)&&(u8FAT_Type==FAT_TYPE_FAT12||u8FAT_Type==FAT_TYPE_FAT16))
    {
        if(u16TempDirEntryCacheOffsetSectorNo>=u32RootDirTotalSectorCount)
        {
            __ASSERT(0);//something is wrong..., should not fetch DirEntries this far
            return FALSE;
        }
    }
    else
    {

        if(u16TempDirEntryCacheOffsetSectorNo >= BPB_SecPerClus)//need next cluster
        {
              //*[01]get file system==============================================================*//

            EN_FAT_CACHE_MOVE_RESULT result=FAT_Cache_DirectoryClusterNext(u8EnvironmentID);
            if(result==FAT_CACHE_MOVE_RESULT_IS_LAST)
            {
                return DIR_ENTRY_CACHE_IS_LAST;
            }

            u32NextDirEntryCacheClusterNo=FAT_Cache_DirectoryClusterGetCurrent(u8EnvironmentID);
            u16TempDirEntryCacheOffsetSectorNo=0;
        }

    }

    //*update DirEntryCache to environment pool====================================*//
    if ( FAT_Cache_DirectoryDirEntryCacheFetch( u8EnvironmentID, u32NextDirEntryCacheClusterNo, u16TempDirEntryCacheOffsetSectorNo)==FAT_CACHE_MOVE_RESULT_ERROR)
    {
          __ASSERT(0);
          return FALSE;
    }
    else
    {
          return TRUE;
    }

}

BOOLEAN FAT_Cache_DirectoryDirEntryCacheFetchFromStart(U8 u8EnvironmentId,U32 clusterNo)
{
    return FAT_Cache_DirectoryDirEntryCacheFetch(u8EnvironmentId,clusterNo,0);
}


//===================================================================
#if (!FILE_SYSTEM_SMALL)
#if FILE_SYSTEM_GET_FILENAME_BY_FILEENTRY_ENABLE
EN_FAT_CACHE_MOVE_RESULT DirEntryIterator_DirectoryClusterPrevious(void)
{
    //for FAT16/12
    if((itrFATType!=FAT_TYPE_FAT32)&&itrDirectoryStartCluster==itrRootDirectoryStartCluster)
    {
        return FAT_CACHE_MOVE_RESULT_SUCCESS;
    }
    else
    {

        if(itrDirectoryStartCluster==itrCurrentCacheCluster)
        {
            return FAT_CACHE_MOVE_RESULT_IS_FIRST;
        }
        else
        {
            //from start

            U32 u32CurrentClusterNo=itrDirectoryStartCluster;
            U32 _Cluster;
            while(TRUE)
            {
                _Cluster=FAT_FATStructureGetNextCluster(itrFSID,u32CurrentClusterNo);

                if(_Cluster==itrCurrentCacheCluster)
                {
                    itrCurrentCacheCluster=u32CurrentClusterNo;
                    return FAT_CACHE_MOVE_RESULT_SUCCESS;
                }
                else
                {
                    u32CurrentClusterNo=_Cluster;
                }
            }

            __ASSERT(0);
            return FAT_CACHE_MOVE_RESULT_ERROR;
        }

    }


}



static BOOLEAN DirEntryIterator_DirEntryCacheFetch(U32 u32CurClusterNo, U16 u16OffsetSector,BOOLEAN forward)
{

    U32 u32DirEntryStartSectorNo;
    EN_FAT_CACHE_MOVE_RESULT result=FAT_CACHE_MOVE_RESULT_SUCCESS;


    u32DirEntryStartSectorNo = FAT_FATGetSectorNo( itrFSID, u32CurClusterNo );

    if(itrSectorsPerCluster >= itrDirEntryCacheSectorCount ||
       ((u32CurClusterNo==itrRootDirectoryStartCluster)&&(itrFATType!=FAT_TYPE_FAT32))//For FAT12/16 in Root

      )
    {

        if ( !msAPI_MSDCtrl_SectorRead( itrDeviceIndex, u32DirEntryStartSectorNo + u16OffsetSector, (U32)itrDirEntryCacheSectorCount, itrBufferAddress) )
        {
            __ASSERT(0);
            return FALSE;
        }
    }
    else
    {

        U8 u8SectorReadSize = 0;
        U8 sectorsToRead=itrDirEntryCacheSectorCount;
        while(sectorsToRead > 0)
        {

            if ( !msAPI_MSDCtrl_SectorRead( itrDeviceIndex, u32DirEntryStartSectorNo + u16OffsetSector, itrSectorsPerCluster, itrBufferAddress + (U32)itrBytesPerSector * u8SectorReadSize) )
            {
                __ASSERT(0);
                return FALSE;
            }

            if(forward)
            {
                __ASSERT(0);// support previous only now!!
                //result=DirEntryIterator_DirectoryClusterNext();
            }
            else
            {
                result=DirEntryIterator_DirectoryClusterPrevious();
            }

            if(  (forward&&result==FAT_CACHE_MOVE_RESULT_IS_LAST)
                ||((!forward)&&result==FAT_CACHE_MOVE_RESULT_IS_FIRST)
               )
            {
                break;
            }
            else if(result==FAT_CACHE_MOVE_RESULT_ERROR)
            {
                __ASSERT(0);
                return FALSE;
            }


            u32DirEntryStartSectorNo = FAT_FATGetSectorNo( itrFSID, itrCurrentCacheCluster);
            sectorsToRead -= itrSectorsPerCluster;
            u8SectorReadSize += itrSectorsPerCluster;

        }

    }

    itrCurrentCacheOffsetSector=u16OffsetSector;
    if(forward)
    {

        itrCurrentCacheDirEntryIndex=0;
    }
    else
    {
        itrCurrentCacheDirEntryIndex=itrDirEntryCacheCount-1;
    }


    return TRUE;
}





U8 DirEntryIterator_DirEntryCachePrevious(void)
{
    U16 u16TempDirEntryCacheOffsetSectorNo;
    U32 u32PreviousDirEntryCacheClusterNo;
    u16TempDirEntryCacheOffsetSectorNo=itrCurrentCacheOffsetSector-itrDirEntryCacheSectorCount;
    u32PreviousDirEntryCacheClusterNo = itrCurrentCacheCluster;


    if(u16TempDirEntryCacheOffsetSectorNo > itrCurrentCacheOffsetSector)//need previous cluster
    {

        EN_FAT_CACHE_MOVE_RESULT result=DirEntryIterator_DirectoryClusterPrevious();
        if(result==FAT_CACHE_MOVE_RESULT_IS_FIRST)
        {
            return DIR_ENTRY_CACHE_IS_FIRST;
        }


        if(itrFATType!=FAT_TYPE_FAT32&&itrCurrentCacheCluster==itrRootDirectoryStartCluster)
        {
            u32PreviousDirEntryCacheClusterNo=itrCurrentCacheCluster;
            u16TempDirEntryCacheOffsetSectorNo=itrCurrentCacheOffsetSector-itrDirEntryCacheSectorCount;

            if(u16TempDirEntryCacheOffsetSectorNo>=itrCurrentCacheOffsetSector)
            {
                __ASSERT(0);
                return FALSE;
            }
        }
        else
        {
            u32PreviousDirEntryCacheClusterNo=itrCurrentCacheCluster;

            if(itrSectorsPerCluster>itrDirEntryCacheSectorCount)
            {
                u16TempDirEntryCacheOffsetSectorNo=itrSectorsPerCluster-itrDirEntryCacheSectorCount;
            }
            else
            {
                u16TempDirEntryCacheOffsetSectorNo=0;
            }
        }
    }




    if ( DirEntryIterator_DirEntryCacheFetch(u32PreviousDirEntryCacheClusterNo, u16TempDirEntryCacheOffsetSectorNo,FALSE)==FAT_CACHE_MOVE_RESULT_ERROR)
    {
          __ASSERT(0);
          return FALSE;
    }
    else
    {
          return TRUE;
    }

}

BOOLEAN DirEntryIterator_Reset(U8 fsid,U32 directoryStartCluster,U32 dirEntryIndex,U32 bufferAddress4KAligned)
{
    FAT_FileSysStruct *pFAT_FileSys;


    itrFSID=fsid;
    itrBufferAddress=bufferAddress4KAligned;
    itrDirectoryStartCluster=directoryStartCluster;

    pFAT_FileSys = (FAT_FileSysStruct *)FCtrl_GetFileSystemInfo(fsid);

    itrDeviceIndex = (U8)pFAT_FileSys->DeviceIndex;
    itrBytesPerSector = pFAT_FileSys->stBootSector.BPB_BytsPerSec;
    itrSectorsPerCluster = pFAT_FileSys->stBootSector.BPB_SecPerClus;
    itrFATType=pFAT_FileSys->stFAT.u8FATType;

    itrRootEntryCount=pFAT_FileSys->stBootSector.BPB_RootEntCnt;
    itrTotalClusters=pFAT_FileSys->stFAT.u32FATTotalClusterNo;
    itrRootDirectoryStartCluster=pFAT_FileSys->u32RootDirStartClusterNo;
    itrRootDirectoryTotalSectorCount=pFAT_FileSys->u32RootDirTotalSectorCount;
    itrDirEntryCacheCount=pFAT_FileSys->u16DirEntryCacheCount;

    itrCurrentCacheDirEntryIndex=0;
    itrCurrentCacheCluster=itrDirectoryStartCluster;
    itrCurrentDirEntryIndex=dirEntryIndex;
    itrDirEntryCacheSectorCount=itrDirEntryCacheCount*sizeof(DirEntryStruct)/ itrBytesPerSector;


    if(itrFATType!=FAT_TYPE_FAT32&&itrCurrentCacheCluster==itrRootDirectoryStartCluster)
    {
        itrCurrentCacheOffsetSector=(itrCurrentDirEntryIndex*sizeof(DirEntryStruct)/itrBytesPerSector)/itrDirEntryCacheSectorCount;
        itrCurrentCacheOffsetSector*=itrDirEntryCacheSectorCount;
    }
    else
    {
        U32 clusterCount;

        clusterCount=((itrCurrentDirEntryIndex*sizeof(DirEntryStruct))/itrBytesPerSector)/itrSectorsPerCluster;
        for(;clusterCount>0;clusterCount--)
        {
            itrCurrentCacheCluster=FAT_FATStructureGetNextCluster(itrFSID,itrCurrentCacheCluster);
        }

        //use the itrCurrentCacheOffsetSector trickly

        itrCurrentCacheOffsetSector=(itrCurrentDirEntryIndex*sizeof(DirEntryStruct)/itrBytesPerSector)%itrSectorsPerCluster;
        itrCurrentCacheOffsetSector=(itrCurrentCacheOffsetSector/itrDirEntryCacheSectorCount)*itrDirEntryCacheSectorCount;
    }



    if(!DirEntryIterator_DirEntryCacheFetch(itrCurrentCacheCluster,itrCurrentCacheOffsetSector,FALSE))
    {
        __ASSERT(0);
        return FALSE;
    }

    itrCurrentCacheDirEntryIndex=dirEntryIndex%(U32)itrDirEntryCacheCount;

    return TRUE;

}


BOOLEAN DirEntryIterator_Previous(void)
{

    U16 cacheIndex=itrCurrentCacheDirEntryIndex;

    if(itrCurrentDirEntryIndex==0||itrCurrentDirEntryIndex==0xFFFFFFFF)
    {
        return FALSE;
    }

    if(cacheIndex==0)
    {

        U8 result;

        //printf("CachePrevious!!\n");
        result=DirEntryIterator_DirEntryCachePrevious();

        if(result==DIR_ENTRY_CACHE_IS_FIRST)
        {
            return FALSE;
        }
        if (result==FALSE)
        {
            __ASSERT(0);
            return FALSE;
        }
    }
    else
    {
        itrCurrentCacheDirEntryIndex--;
    }

    itrCurrentDirEntryIndex--;
    return TRUE;

}
#endif

#endif//FILE_SYSTEM_SMALL

#if 0//following code is not checked but should not be moved due to later development
EN_FAT_CACHE_MOVE_RESULT DirEntryIterator_DirectoryClusterNext()
{

    EN_FAT_CACHE_MOVE_RESULT result=FAT_CACHE_MOVE_RESULT_ERROR;
    U32 _Cluster;

    //for FAT16/12
    if((itrFATType!=FAT_TYPE_FAT32)&&itrDirectoryStartCluster==itrRootDirectoryStartCluster)
    {
        result=FAT_CACHE_MOVE_RESULT_SUCCESS;
    }
    else
    {
        U32 clusterStatus=FAT_CLUSTER_RESERVED;
         _Cluster=FAT_FATStructureGetNextCluster(itrFSID,itrCurrentCacheCluster);

        clusterStatus=FAT_FATGetClusterStatus(itrFATType,itrTotalClusters,_Cluster);
        if(clusterStatus==FAT_CLUSTER_FINAL)
        {
            result=FAT_CACHE_MOVE_RESULT_IS_LAST;
        }
        else if(clusterStatus==FAT_CLUSTER_ALLOCATED)
        {
            result=FAT_CACHE_MOVE_RESULT_SUCCESS;
            itrCurrentCacheCluster=_Cluster;

        }
        else
        {
            __ASSERT(0);
        }
    }
    return result;
}

U8 DirEntryIterator_DirEntryCacheNext()
{
    U16 u16TempDirEntryCacheOffsetSectorNo;
    U32 u32NextDirEntryCacheClusterNo;
    u16TempDirEntryCacheOffsetSectorNo=itrCurrentCacheOffsetSector+itrDirEntryCacheSectorCount;
    u32NextDirEntryCacheClusterNo = itrCurrentCacheCluster;

    //For FAT12/16 in Root
    if((itrDirectoryStartCluster== itrRootDirectoryStartCluster)&&(itrFATType!=FAT_TYPE_FAT32))
    {
        if(u16TempDirEntryCacheOffsetSectorNo>=itrRootDirectoryTotalSectorCount)
        {
            __ASSERT(0);//something is wrong..., should not fetch DirEntries this far
            return FALSE;
        }
    }
    else
    {

        if(u16TempDirEntryCacheOffsetSectorNo >= itrSectorsPerCluster)//need next cluster
        {

            EN_FAT_CACHE_MOVE_RESULT result=DirEntryIterator_DirectoryClusterNext();
            if(result==FAT_CACHE_MOVE_RESULT_IS_LAST)
            {
                return DIR_ENTRY_CACHE_IS_LAST;
            }


            u32NextDirEntryCacheClusterNo=itrCurrentCacheCluster;
            u16TempDirEntryCacheOffsetSectorNo=0;
        }


    }

    if ( DirEntryIterator_DirEntryCacheFetch(u32NextDirEntryCacheClusterNo, u16TempDirEntryCacheOffsetSectorNo,TRUE)==FAT_CACHE_MOVE_RESULT_ERROR)
    {
          __ASSERT(0);
          return FALSE;
    }
    else
    {
          return TRUE;
    }

}

static BOOLEAN DirEntryIterator_Next()
{

    U16 cacheIndex=itrCurrentCacheDirEntryIndex;
    cacheIndex++;


    if(itrFATType!=FAT_TYPE_FAT32&&itrDirectoryStartCluster==itrRootDirectoryStartCluster)
    {
        U32 entryCount=itrDirEntryCountPerSector*itrCurrentCacheOffsetSector;

        if((entryCount+cacheIndex)==itrRootEntryCount)
        {
            return FALSE;
        }
        else if((entryCount+cacheIndex)>itrRootEntryCount)
        {
            __ASSERT(0);
            return FALSE;
        }


    }

    if(cacheIndex>=itrDirEntryCacheCount)
    {
        U8 result=DirEntryIterator_DirEntryCacheNext();

        if(result==DIR_ENTRY_CACHE_IS_LAST)
        {
            return FALSE;
        }
        if (result==FALSE)
        {
            __ASSERT(0);
            return FALSE;
        }

    }
    else
    {
        itrCurrentCacheDirEntryIndex++;
        itrCurrentDirEntryIndex++;
    }

    return TRUE;
}
#endif




//===================================================================

#if 0//(FAT_CACHE_PREV_ENABLE)

BOOLEAN FAT_Cache_DirectoryClusterPrev(U8 u8EnvironmentId)
{

    FAT_Environment *pFAT_Env;
    FS_EnvironmentStruct *pFS_Env;
    FAT_FileSysStruct FAT_FileSys;
    U32 u32CurrentClusterNo, u32CurrentDirectoryStartClusterNo;
    U16 u16Index;

    pFS_Env = msAPI_FSEnv_GetEnvironment( u8EnvironmentId );

    if ( !msAPI_FCtrl_FileSystemGetByID(pFS_Env->u8FileSystemID, &FAT_FileSys) )
    {
        __ASSERT(0);
        return FALSE;
    }

    pFAT_Env = (FAT_Environment*)FAT_GetXData(u8EnvironmentId, FAT_XDATA_OPTION_ENVIRONMENT);
    u16Index=pFAT_Env->stCurrentDirectory.u16ClusterChainIndex;
    u32CurrentDirectoryStartClusterNo=pFAT_Env->stCurrentDirectory.u32CurrentDirStartClusterNo;
    u32CurrentClusterNo=pFAT_Env->stCurrentDirectory.u32ClusterChain[u16Index];

    FAT_ReturnXData();

    //for FAT16/12
    if((FAT_FileSys.stFAT.u8FATType!=FAT_TYPE_FAT32)&&u32CurrentClusterNo==FAT_FileSys.u32RootDirStartClusterNo)
    {
        return TRUE;
    }

    if(u16Index==0)
    {

        if(u32CurrentDirectoryStartClusterNo==u32CurrentClusterNo)
        {
            return FALSE;
        }
        else
        {
            //from start
            U32 buff[FAT_MAX_DIRECTORY_CLUSTER_COUNT];
            U32 stopCluster=u32CurrentClusterNo;

            u32CurrentClusterNo=u32CurrentDirectoryStartClusterNo;
            while ( TRUE )
            {
                FS_RESET_WDT();
                if(_DirectoryClusterChainFetch(u8EnvironmentId,u32CurrentClusterNo,&FAT_FileSys))
                {
                    __ASSERT(0);
                    return FALSE;
                }

                if(FAT_Cache_DirectoryClusterGetCurrent(u8EnvironmentId)==stopCluster)
                {

                    pFAT_Env = (FAT_Environment*)FAT_GetXData(u8EnvironmentId, FAT_XDATA_OPTION_ENVIRONMENT);
                    memcpy(pFAT_Env->stCurrentDirectory.u32ClusterChain,buff,sizeof(buff));
                    pFAT_Env->stCurrentDirectory.u16ClusterChainIndex = FAT_MAX_DIRECTORY_CLUSTER_COUNT-1;          //<<====means start cluster of current directory
                    FAT_ReturnXData();
                    return TRUE;
                }
                else
                {
                    pFAT_Env = (FAT_Environment*)FAT_GetXData(u8EnvironmentId, FAT_XDATA_OPTION_ENVIRONMENT);
                    memcpy(buff,pFAT_Env->stCurrentDirectory.u32ClusterChain,sizeof(buff));
                    FAT_ReturnXData();

                }
            }
        }
    }
    else
    {
        u16Index--;
        pFAT_Env = (FAT_Environment*)FAT_GetXData(u8EnvironmentId, FAT_XDATA_OPTION_ENVIRONMENT);
        pFAT_Env->stCurrentDirectory.u16ClusterChainIndex = u16Index;          //<<====means start cluster of current directory
        FAT_ReturnXData();
        return TRUE;
    }

}

#endif

#if (FILE_SYSTEM_WRITE_ENABLE)

static U8 code LONG_NAME_BYTE_POS_IN_DIRENTRY[13]={1,3,5,7,9,14,16,18,20,22,24,28,30};
extern BOOLEAN FAT_DirEntryWriteDirect(U8 u8EnvironmentID,U32 startCluster,U32 u32Index,DirEntryStruct* pDirEntry);
extern U32 FAT_FATTableUpdate(U8 u8fsid, U32 clusterNo, U32 u32ClusterNeeded);

static BOOLEAN FAT_DirEntryReadDirectInCluster(U8 u8fsid ,U32 startCluster,U32 u32Index,DirEntryStruct* pDirEntry)
{
    U32 sectorNo;
    S8 deviceIndex;
    U32 dirEntryCountPerSector;
    FAT_FileSysStruct* pFATFileSys;
    U32 u32BytesPerSector;

    pFATFileSys = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);

    u32BytesPerSector = pFATFileSys->stBootSector.BPB_BytsPerSec;
    deviceIndex = pFATFileSys->DeviceIndex;

    sectorNo=FAT_FATGetSectorNo(u8fsid,startCluster);

    dirEntryCountPerSector=u32BytesPerSector/sizeof(DirEntryStruct);
    sectorNo+=(u32Index/dirEntryCountPerSector);
    u32Index=u32Index%dirEntryCountPerSector;

    if(!msAPI_MSDCtrl_SectorRead(deviceIndex,sectorNo,1,USB_IO_TEMP_ADDR))
    {
        __ASSERT(0);
        return FALSE;
    }

    msAPI_FS_MIU_Copy((U32)USB_IO_TEMP_ADDR+u32Index*sizeof(DirEntryStruct), GET_DRAM_ADDR(pDirEntry), sizeof(DirEntryStruct));
    return TRUE;
}



BOOLEAN FAT_DirEntryUpdate(U8 u8Filehandle)
{
    DirEntryStruct dirEntry;
    FAT_FileHandle *pFileHandle;
    FAT_FileInode *pFATInode;
    U32 u32Size;
    FS_TIME _SysTime;
    U16 u16Date, u16Time;
    U32 u32DirEntryCluster;
    U32 u32DirEntryOffset;
    FAT_FileSysStruct *pFATFileSys;
    //U32 bytesPerSector, sectorsPerCluster;
    U16 u16DirEntryCountPerCluster;
    U16 u8BPB_BytesPerSector;
    U8 u8BPB_SecPerClus;
    U8 u8FATType;
    U8 fsid;
    U32 u32FileStartClusterNo;
    U16 temp;

    pFileHandle = FAT_File_GetHandleInfo(u8Filehandle);
    pFATInode = (FAT_FileInode*)FCtrl_GetFileInodeInfo(pFileHandle->pub_fileheader.InodeID);
   if(pFATInode == NULL)
   {
           __ASSERT(0);
           return FALSE;
   }

    u32Size = pFATInode->u32FileTotalSize;
    u32DirEntryCluster = pFATInode->u32DirStartCluster;
    u32DirEntryOffset = pFATInode->u32DirEntryOffset;
    fsid=pFileHandle->pub_fileheader.FileSystemID;
    u32FileStartClusterNo = pFATInode->u32FileStartClusterNo;

    pFATFileSys = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(fsid);

    u8BPB_BytesPerSector = pFATFileSys->stBootSector.BPB_BytsPerSec;
    u8BPB_SecPerClus = pFATFileSys->stBootSector.BPB_SecPerClus;
    u16DirEntryCountPerCluster=((U32)u8BPB_BytesPerSector*u8BPB_SecPerClus)/sizeof(DirEntryStruct);
    u8FATType = pFATFileSys->stFAT.u8FATType;
    //printf("\nu16DirEntryCountPerCluster: %u", u16DirEntryCountPerCluster);

    if((u8FATType==FAT_TYPE_FAT32)||u32DirEntryCluster!=0)
    {
        while(u32DirEntryOffset >= u16DirEntryCountPerCluster)
        {

            u32DirEntryCluster = FAT_FATStructureGetNextCluster(fsid, u32DirEntryCluster);
            u32DirEntryOffset -= u16DirEntryCountPerCluster;
            FS_RESET_WDT();

        }
    }

    if(!FAT_DirEntryReadDirectInCluster(fsid,u32DirEntryCluster, u32DirEntryOffset,&dirEntry))
    {
        __ASSERT(printf("u32DirEntryCluster: %lX, u32DirEntryOffset: %lX\n", u32DirEntryCluster, u32DirEntryOffset));
        return FALSE;
    }

    // update size
    memcpy((U8*)&dirEntry.u32DirEntryFileLength, (U8*)&u32Size, 4);

    // update time
    _SysTime = msAPI_FS_GetLocalTime();
    u16Date = (((_SysTime.u16Year-FS_DEFAULT_YEAR)&0x7F)<<9) |((_SysTime.u8Month&0x0F)<<5) |(_SysTime.u8Day&0x1F);
    dirEntry.u16DirEntryDate = (u16Date);
    u16Time = ((_SysTime.u8Hour&0x1F)<<11) |((_SysTime.u8Min&0x3F)<<5) |((_SysTime.u8Sec/2)&0x1F);
    dirEntry.u16DirEntryTime = (u16Time);

    dirEntry.u16DirEntryStartClusterLO=((U16)u32FileStartClusterNo);
    temp = ((U16)((u32FileStartClusterNo>>16)&0xFFFF));
    dirEntry.u16DirEntryStartClusterHI=(temp);

    if(!FAT_DirEntryWriteDirect(fsid, u32DirEntryCluster, u32DirEntryOffset, &dirEntry))
    {
        __ASSERT(0);
        return FALSE;
    }

    return TRUE;

}


//should write up to first cluster
//u32FileCurrentSectorNo & u32FileCurrentClusterNo need to be checked after this function
S32 FAT_Cache_FileWriteBegin(U8 handle,U32 u32SrcBufAddr,U32 buffLen)
{
    FAT_FileHandle *pFileHandle;
    FAT_FileInode  *pFATInode;
    FAT_FileSysStruct *pFATFileSys;//, stFat_FileSys;
    U8 u8DeviceIndex, u8BPB_SecPerClus;
    U32 u32FilePos;
    U32 bytesPerSector;
    U8 fsid;
    U32 sectorNo;
    U32 bytesPerCluster;
    U32 clusterNo;
    U32 len;
    U32 len2;
    U32 writeSector;
    U32 bytesOffsetInSector;


    pFileHandle = FAT_File_GetHandleInfo(handle);

   pFATInode = (FAT_FileInode*)FCtrl_GetFileInodeInfo(pFileHandle->pub_fileheader.InodeID);
   if(pFATInode == NULL)
   {
           __ASSERT(0);
           return -1;
   }

    //must be moved to correct Cluster and Sector already
    clusterNo=pFileHandle->u32FileCurrentClusterNo;
    sectorNo=pFileHandle->u32FileCurrentSectorNo;

    u32FilePos=pFileHandle->u32FilePosition;
    fsid=pFileHandle->pub_fileheader.FileSystemID;

    pFATFileSys = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(fsid);

    u8DeviceIndex = pFATFileSys->DeviceIndex;
    u8BPB_SecPerClus = pFATFileSys->stBootSector.BPB_SecPerClus;
    bytesPerSector=pFATFileSys->stBootSector.BPB_BytsPerSec;

    //printf("\n[FW]:WB step1: clusterNo=0x%08lx, sectorNo=0x%08lx, filePos=0x%08lx\n",clusterNo,sectorNo,u32FilePos);
    //printf("                 bufflen=0x%08lx, srcBufferAddr=0x%08lx\n",buffLen,u32SrcBufAddr);

    bytesPerCluster= ((U32)u8BPB_SecPerClus)*bytesPerSector;

    if((u32FilePos % bytesPerCluster)==0)
    {
        //already aligned at cluster start
        return 0;
    }

    //write up to current sector
    writeSector=FAT_FATGetSectorNo(fsid,clusterNo)+ sectorNo;

    if(!msAPI_MSDCtrl_SectorRead( u8DeviceIndex,writeSector,1,USB_IO_TEMP_ADDR))
    {
        __ASSERT(0);
        return -1;
    }

    bytesOffsetInSector=u32FilePos%bytesPerSector;

    len=(U32)bytesPerSector-bytesOffsetInSector;


    msAPI_FS_MIU_Copy(u32SrcBufAddr,USB_IO_TEMP_ADDR+bytesOffsetInSector,len);

    if(!msAPI_MSDCtrl_SectorWrite( u8DeviceIndex,writeSector,1,USB_IO_TEMP_ADDR))
    {
        __ASSERT(0);
        return -1;
    }


    sectorNo+=1;

    if(buffLen<len)//sector has not been totally used
    {
        pFileHandle = FAT_File_GetHandleInfo(handle);

        pFileHandle->u32FilePosition+=buffLen;
        pFATInode->u32FileTotalSize+=buffLen;
        return (S32)buffLen;
    }
    else //sector is full, update to next
    {
        pFileHandle = FAT_File_GetHandleInfo(handle);

        pFileHandle->u32FilePosition+=len;
        pFATInode->u32FileTotalSize+=len;
        pFileHandle->u32FileCurrentSectorNo=sectorNo;

    }


    if(sectorNo==u8BPB_SecPerClus)
    {
        //aligned to cluster start, return
        #if 0
        clusterNo=FAT_FATStructureGetNextCluster(fsid,clusterNo);
        pFileHandle = FAT_File_GetHandleXData(handle);
        pFileHandle->u32FileCurrentClusterNo=clusterNo;
        pFileHandle->u32FileCurrentSectorNo=0;

        FATC_DBG(printf("\n[FW]:WB step2: clusterNo=0x%08lx, sectorNo=0x%08lx, filePos=0x%08lx\n",clusterNo,sectorNo,pFileHandle->u32FilePosition););
        FAT_ReturnXData();
        #endif

        return (S32)len;

    }


    //write up to current cluster

    //don't care garbage
    if(!msAPI_MSDCtrl_SectorWrite( u8DeviceIndex,writeSector+1,((U32)u8BPB_SecPerClus-sectorNo),u32SrcBufAddr+len))
    {
        __ASSERT(0);
        return -1;
    }

    len2=(u8BPB_SecPerClus-sectorNo)*bytesPerSector;

    if((buffLen-len)<len2)
    {
        len2=(buffLen-len);
        sectorNo+=(len2/bytesPerSector);
    }
    else
    {
        #if 0
        clusterNo=FAT_FATStructureGetNextCluster(fsid,clusterNo);
        sectorNo=0;
        #endif
        sectorNo=u8BPB_SecPerClus;
    }

    pFileHandle = FAT_File_GetHandleInfo(handle);

    pFileHandle->u32FileCurrentSectorNo=sectorNo;
    pFileHandle->u32FilePosition+=len2;
    pFATInode->u32FileTotalSize+=len2;

    return (len+len2);

}



BOOLEAN FAT_DirEntryNew_Short(U8 u8fsid, U8* shortName,U8* extName, U32 u32ClusterNo, S32 s32Offset, BOOLEAN isFile, EN_CREATE_MODE createMode)
{

    FS_TIME _SysTime;
    U16 u16Date, u16Time;
    U8 *pu8Tmp;
    U32 sectorNo;
    S8 deviceIndex;
    U32 dirEntryCountPerSector, dirEntryCountPerCluster;
    FAT_FileSysStruct* pFAT_FileSys;
    U32 u32BytesPerSec;
    U32 u32SectorPerCluster;
    U8 u8FATType;


    pFAT_FileSys = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);

    u32BytesPerSec = pFAT_FileSys->stBootSector.BPB_BytsPerSec;
    u32SectorPerCluster = pFAT_FileSys->stBootSector.BPB_SecPerClus;
    deviceIndex = pFAT_FileSys->DeviceIndex;
    u8FATType = pFAT_FileSys->stFAT.u8FATType;

    dirEntryCountPerSector = (u32BytesPerSec/sizeof(DirEntryStruct));
    dirEntryCountPerCluster = (dirEntryCountPerSector*u32SectorPerCluster);

    if(u32ClusterNo!=0)
    {
        while(s32Offset >= (S32)dirEntryCountPerCluster)
        {
            u32ClusterNo = FAT_FATStructureGetNextCluster(u8fsid, u32ClusterNo);
            if(u32ClusterNo == 0)
            {
                __ASSERT(0);
                return FALSE;
            }
            s32Offset -= dirEntryCountPerCluster;
        }
    }


    //shift to sector
    sectorNo = FAT_FATGetSectorNo(u8fsid, u32ClusterNo);
    sectorNo += (s32Offset/dirEntryCountPerSector);
    s32Offset = (s32Offset % dirEntryCountPerSector);

    if(!msAPI_MSDCtrl_SectorRead(deviceIndex,sectorNo, 1, USB_IO_TEMP_ADDR))
    {
        __ASSERT(0);
        return FALSE;
    }

    pu8Tmp = (U8 xdata* )msAPI_FS_GetAddr(USB_IO_TEMP_ADDR);

    pu8Tmp += (s32Offset*sizeof(DirEntryStruct));
    memset(pu8Tmp, 0, sizeof(DirEntryStruct));
    memcpy(pu8Tmp, shortName, 8);
    memcpy((pu8Tmp + 8), extName, 3);

    if(isFile)
    {
        *(pu8Tmp + 0xB) = FAT_ATTRIB_ARCHIVE | (createMode==CREATE_MODE_NEW_ATTR_HIDDEN?FAT_ATTRIB_HIDDEN:0x00);
    }
    else
    {
        *(pu8Tmp + 0xB) = FAT_ATTRIB_DIRECTORY;
    }

    _SysTime = msAPI_FS_GetLocalTime();
    u16Date = (((_SysTime.u16Year-FS_DEFAULT_YEAR)&0x7F)<<9) |((_SysTime.u8Month&0x0F)<<5) |(_SysTime.u8Day&0x1F);
    u16Time = ((_SysTime.u8Hour&0x1F)<<11) |((_SysTime.u8Min&0x3F)<<5) |((_SysTime.u8Sec/2)&0x1F);
    u16Date = (u16Date);
    u16Time = (u16Time);
    memcpy(pu8Tmp + 0x0E, &u16Time, 2);
    memcpy(pu8Tmp + 0x10, &u16Date, 2);
    memcpy(pu8Tmp + 0x12, &u16Date, 2);
    memcpy(pu8Tmp + 0x16, &u16Time, 2);
    memcpy(pu8Tmp + 0x18, &u16Date, 2);

    if(!msAPI_MSDCtrl_SectorWrite(deviceIndex,sectorNo, 1, USB_IO_TEMP_ADDR))
    {
        __ASSERT(0);
        return FALSE;
    }

    return TRUE;
}

U8 FAT_DirEntryNew_Long(U8 u8fsid, U16 *pu16LongName, U8 charLen, U8 u8CheckSum, U8 u8TotalEntryNum, U32 u32ClusterNo, S32 s32Offset)
{
    U8 u8Loop, u8CharIndex, u8EntryNo;
    U8 *pu8Tmp;
    U32 sectorNo;
    S8 deviceIndex;
    U32 dirEntryCountPerSector, dirEntryCountPerCluster;
    FAT_FileSysStruct* pFAT_FileSys;
    U32 u32BytesPerSec;
    U32 u32SectorPerCluster;
    U32 u32TmpOffset;
    S32 s32Index;
    U8 u8FATType;
    U32 u32FATTotalClusterNo;

    pFAT_FileSys = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);

    u32BytesPerSec = pFAT_FileSys->stBootSector.BPB_BytsPerSec;
    u32SectorPerCluster = pFAT_FileSys->stBootSector.BPB_SecPerClus;
    deviceIndex = pFAT_FileSys->DeviceIndex;
    u8FATType = pFAT_FileSys->stFAT.u8FATType;
    u32FATTotalClusterNo = pFAT_FileSys->stFAT.u32FATTotalClusterNo;

    dirEntryCountPerSector = (u32BytesPerSec/sizeof(DirEntryStruct));
    dirEntryCountPerCluster = (dirEntryCountPerSector*u32SectorPerCluster);

    if(u32ClusterNo!=0)
    {
        while(s32Offset >= (S32)dirEntryCountPerCluster)
        {
            u32ClusterNo = FAT_FATStructureGetNextCluster(u8fsid, u32ClusterNo);
            if(u32ClusterNo == 0)
            {
                __ASSERT(0);
                return FALSE;
            }
            s32Offset -= dirEntryCountPerCluster;
        }
    }

    //shift to sector
    sectorNo = FAT_FATGetSectorNo(u8fsid, u32ClusterNo);
    u32TmpOffset = s32Offset;
    sectorNo += (s32Offset/dirEntryCountPerSector);
    s32Offset = (s32Offset % dirEntryCountPerSector);

    if(!msAPI_MSDCtrl_SectorRead(deviceIndex, sectorNo, 1, USB_IO_TEMP_ADDR))
    {
        __ASSERT(0);
        return FALSE;
    }

    pu8Tmp = (U8 xdata* )msAPI_FS_GetAddr(USB_IO_TEMP_ADDR);

    for(u8EntryNo= u8TotalEntryNum; u8EntryNo>0; u8EntryNo--)
    {
        s32Index = (s32Offset*sizeof(DirEntryStruct));
        memset((pu8Tmp + s32Index), 0, sizeof(DirEntryStruct));

        for(u8Loop=0; u8Loop<sizeof(LONG_NAME_BYTE_POS_IN_DIRENTRY); u8Loop++)
        {
            u8CharIndex = (u8EntryNo-1)*sizeof(LONG_NAME_BYTE_POS_IN_DIRENTRY) + u8Loop;

            if(u8CharIndex == charLen)
            {
                //*(U16 *)((pu8Tmp + s32Index)+LONG_NAME_BYTE_POS_IN_DIRENTRY[u8Loop]) = 0x0;
                ((pu8Tmp + s32Index)+LONG_NAME_BYTE_POS_IN_DIRENTRY[u8Loop])[0] = 0x0;
                ((pu8Tmp + s32Index)+LONG_NAME_BYTE_POS_IN_DIRENTRY[u8Loop])[1] = 0x0;
            }
            else if(u8CharIndex > charLen)
            {
                //*(U16 *)((pu8Tmp + s32Index)+LONG_NAME_BYTE_POS_IN_DIRENTRY[u8Loop]) = 0xFFFF;
                ((pu8Tmp + s32Index)+LONG_NAME_BYTE_POS_IN_DIRENTRY[u8Loop])[0] = 0xFF;
                ((pu8Tmp + s32Index)+LONG_NAME_BYTE_POS_IN_DIRENTRY[u8Loop])[1] = 0xFF;
            }
            else
            {
                //*(U16 *)((pu8Tmp + s32Index)+LONG_NAME_BYTE_POS_IN_DIRENTRY[u8Loop]) = (*(pu16LongName + u8CharIndex));
                memcpy(((pu8Tmp + s32Index)+LONG_NAME_BYTE_POS_IN_DIRENTRY[u8Loop]),(pu16LongName + u8CharIndex),2);
            }
        }


        *((pu8Tmp + s32Index) + 0x0) = u8EntryNo;

        if(u8TotalEntryNum == u8EntryNo)
        {
            *((pu8Tmp + s32Index) + 0x0) |= 0x40;
        }

        *((pu8Tmp + s32Index) + 0x0B) = FAT_ATTRIB_LONG_NAME;
        *((pu8Tmp + s32Index) + 0x0D) = u8CheckSum;
        *((pu8Tmp + s32Index) + 0x1A) = 0;
        *((pu8Tmp + s32Index) + 0x1B) = 0;

        s32Offset++;
        u32TmpOffset ++;

        if((u32TmpOffset >= dirEntryCountPerCluster) && (u32ClusterNo!=0))
        {
            U32 u32PrevClusterNo;
            U32 u32ClusterStatus;
            BOOLEAN bIsNewCluster=FALSE;

            if(!msAPI_MSDCtrl_SectorWrite(deviceIndex,sectorNo, 1, USB_IO_TEMP_ADDR))
            {
                __ASSERT(0);
                return FALSE;
            }

            u32PrevClusterNo = u32ClusterNo;
            u32ClusterNo = FAT_FATStructureGetNextCluster(u8fsid, u32ClusterNo);
            u32ClusterStatus = FAT_FATGetClusterStatus( u8FATType, u32FATTotalClusterNo,  u32ClusterNo);

            if(u32ClusterStatus == FAT_CLUSTER_FINAL)
            {
                u32ClusterNo = FAT_FATTableUpdate(u8fsid, u32PrevClusterNo, 1);
                if(0 == u32ClusterNo)
                {
                    return ENTRY_CREATE_RESULT_FULL;
                }
                //u32ClusterNo = FAT_FATStructureGetNextCluster(u8fsid, u32PrevClusterNo);
                bIsNewCluster = TRUE;
            }
            sectorNo = FAT_FATGetSectorNo(u8fsid, u32ClusterNo);

            if(!msAPI_MSDCtrl_SectorRead(deviceIndex, sectorNo, 1, USB_IO_TEMP_ADDR))
            {
                __ASSERT(0);
                return FALSE;
            }

            pu8Tmp = (U8 xdata* )msAPI_FS_GetAddr(USB_IO_TEMP_ADDR);

            if(bIsNewCluster == TRUE)
            {
                memset(pu8Tmp, 0, 0x1000);
            }

            u32TmpOffset = 0;
            s32Offset = 0;
        }
        else if(s32Offset >= (S32)dirEntryCountPerSector)
        {

            if(!msAPI_MSDCtrl_SectorWrite(deviceIndex,sectorNo, 1, USB_IO_TEMP_ADDR))
            {
                __ASSERT(0);
                return FALSE;
            }

            sectorNo ++;
            s32Offset = 0;

            if(!msAPI_MSDCtrl_SectorRead(deviceIndex, sectorNo, 1, USB_IO_TEMP_ADDR))
            {
                __ASSERT(0);
                return FALSE;
            }
            pu8Tmp = (U8 xdata* )msAPI_FS_GetAddr(USB_IO_TEMP_ADDR);

        }

    }

    if(!msAPI_MSDCtrl_SectorWrite(deviceIndex,sectorNo, 1, USB_IO_TEMP_ADDR))
    {
        __ASSERT(0);
        return FALSE;
    }

    return TRUE;
}

#if FILE_SYSTEM_FOLDER_CREATE_ENABLE
BOOLEAN FAT_DirEntryNew_Directory(U8 u8fsid, FileEntry *pFileToSet, U32 u32ClusterNo)
{
    FS_TIME _SysTime;
    U16 u16Date, u16Time;
    FAT_FileSysStruct* pFAT_FileSys;
    U8 deviceIndex;
    U32 sectorNo;
    U8 *pu8Tmp;
    //U16 addr=(USB_IO_TEMP_ADDR>>12);

    pFAT_FileSys = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);
    deviceIndex = pFAT_FileSys->DeviceIndex;
    //msAPI_FS_ReturnXData();

    sectorNo = FAT_FATGetSectorNo(u8fsid, u32ClusterNo);
    if(!msAPI_MSDCtrl_SectorRead(deviceIndex, sectorNo, 1, USB_IO_TEMP_ADDR))
    {
        __ASSERT(0);
        return FALSE;
    }

    pu8Tmp = (U8 xdata* )msAPI_FS_GetAddr(USB_IO_TEMP_ADDR);

    // Dot
    memset((pu8Tmp + 0x0), 0x20, 8);
    *(pu8Tmp + 0x0) = 0x2E;
    memset((pu8Tmp + 0x8), 0x20,3);
    memcpy( (pu8Tmp + 0x14), (U8*)&pFileToSet->EntryID[0], 2 );
    memcpy( (pu8Tmp + 0x1A), (U8*)&pFileToSet->EntryID[2], 2 );
    *(pu8Tmp + 0x0B) = FAT_ATTRIB_DIRECTORY;
    /* set local time */
    _SysTime = msAPI_FS_GetLocalTime();
    u16Date = ((_SysTime.u16Year&0x7F)<<9) |((_SysTime.u8Month&0x0F)<<5) |(_SysTime.u8Day&0x1F);
    *(pu8Tmp + 0x18) = (u16Date);
    u16Time = ((_SysTime.u8Hour&0x1F)<<11) |((_SysTime.u8Min&0x3F)<<5) |((_SysTime.u8Sec/2)&0x1F);
    *(pu8Tmp + 0x16) = (u16Time);

    pu8Tmp += 0x20;

    // DotDot
    memset((pu8Tmp + 0x0), 0x20, 8);
    *(pu8Tmp + 0x0) = 0x2E;
    *(pu8Tmp + 0x1) = 0x2E;
    memset((pu8Tmp + 0x8), 0x20,3);
    memcpy( (pu8Tmp + 0x14), (U8*)&pFileToSet->EntryID_Ext[2], 2 );
    memcpy( (pu8Tmp + 0x1A), (U8*)&pFileToSet->EntryID_Ext[0], 2 );
    *(pu8Tmp + 0x0B) = FAT_ATTRIB_DIRECTORY;
    /* set local time */
    _SysTime = msAPI_FS_GetLocalTime();
    u16Date = ((_SysTime.u16Year&0x7F)<<9) |((_SysTime.u8Month&0x0F)<<5) |(_SysTime.u8Day&0x1F);
    *(pu8Tmp + 0x18) = (u16Date);
    u16Time = ((_SysTime.u8Hour&0x1F)<<11) |((_SysTime.u8Min&0x3F)<<5) |((_SysTime.u8Sec/2)&0x1F);
    *(pu8Tmp + 0x16) = (u16Time);

    //FAT_ReturnXData();

    if(!msAPI_MSDCtrl_SectorWrite(deviceIndex,sectorNo, 1, USB_IO_TEMP_ADDR))
    {
        __ASSERT(0);
        return FALSE;
    }
    return TRUE;
}
#endif

BOOLEAN ConvertLongFileNameToShort(U8* shortName,U16* longName,U8 longNameLength)
{
    U8 i=0;
    U8 j=0;
    U8 len=8;

    memset(shortName,0x20,11);

    if(longNameLength==0)
    {
        return TRUE;
    }

    if(longName[0]=='.')
    {
        return FALSE;
    }

    //search suffixStartIndex
    for(i=longNameLength;i>0;i--)
    {
        if(longName[i-1]=='.')
        {
            break;
        }
    }

    //short name
    if(i==0)
    {
        len=longNameLength>8?8:longNameLength;
    }
    else
    {
        len=(i-1)>8?8:(i-1);
    }

    for(j=0;j<len;j++)
    {
        shortName[j]=(U8)longName[j];
    }

    //short name ext
    if(i>0)
    {
        len=(longNameLength-i)>3?3:(longNameLength-i);
        for(j=0;j<len;j++)
        {
            shortName[j+8]=(U8)longName[j+i];
        }
    }

    FS_strupr2(shortName,11);

    return TRUE;
}

static code U8 VALIDCHARTABLE[256]={
    0x4B,0x42,0x46,0x4A,0x4E,0x52,0x56,0x5A,0x44,0x48,0x4C,0x50,0x54,0x58,0x42,0x46,
    0x4A,0x41,0x45,0x49,0x4D,0x51,0x55,0x59,0x43,0x47,0x33,0x36,0x45,0x53,0x56,0x39,
    0x20,0x21,0x70,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x88,0x87,0x86,0x2D,0x84,0x83,
    0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x72,0x71,0x70,0x69,0x68,0x67,
    0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
    0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x65,0x66,0x67,0x5E,0x5F,
    0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
    0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x72,0x7D,0x7E,0x7F,
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
    0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
    0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
    0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
    0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
    0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,
    0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
    0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF
};

BOOLEAN ConvertLongFileNameToShort_Short(U8* shortName,U16* longName,U8 longNameLength)
{
    U8 i=0;
    U8 j=0;
    U8 len=8;
    U8 u8Loop;

    memset(shortName,0x20,11);

    if(longNameLength==0)
    {
        return TRUE;
    }

    if(longName[0]=='.')
    {
        return FALSE;
    }

    //search suffixStartIndex
    for(i=longNameLength;i>0;i--)
    {

        if(longName[i-1]=='.')
        {
            break;
        }
    }

    //short name
    if(i==0)
    {
        len=longNameLength>8?8:longNameLength;
    }
    else
    {
        len=(i-1)>8?8:(i-1);
    }

    shortName[0] = 0x48;
    for(u8Loop = 1; u8Loop<longNameLength; u8Loop++)
    {
        shortName[u8Loop%8] += (U8)(*(longName + u8Loop));
    }
    for(u8Loop = 0; u8Loop<8; u8Loop++)
    {
        shortName[u8Loop] = VALIDCHARTABLE[shortName[u8Loop]];
        if ((u8Loop == 0) && (shortName[u8Loop] == 0xE5))
            shortName[u8Loop] = 0x5F; //to avoid parsing error in FAT table.
        else if((u8Loop == 0) && (shortName[u8Loop] == 0x20))
            shortName[u8Loop] = 0x5F;   //first character can not be space
    }

    //short name ext
    if(i>0)
    {
        len=(longNameLength-i)>3?3:(longNameLength-i);
        for(j=0;j<len;j++)
        {
            shortName[j+8]=(U8)longName[j+i];
        }
    }

    FS_strupr2(shortName,11);

    return TRUE;
}

BOOLEAN FAT_IsLongName(U16 *pu16LongName, U8 charLen)
{
    BOOLEAN allSmall=FALSE;
    S8 indexOf0x2e=-1;
    U8 i=0;
    U8 checkLen=0;

    if(charLen > 12)
    {
        return TRUE;
    }
    if(charLen ==0)
    {
        __ASSERT(0);
        return FALSE;
    }

    //count the 0x2e
    for(i=0;i<charLen;i++)
    {
        if(pu16LongName[i]==0x2e)
        {
            //if(i>7)
            if(i > 8)
            {
                return TRUE;
            }
            else
            {
                indexOf0x2e=i;
            }
        }
    }

    //check no 0x2e condition
    //if((indexOf0x2e==-1 && charLen> 7)||((charLen-indexOf0x2e-1)>3))
    if((indexOf0x2e==-1 && charLen> 8)||(indexOf0x2e>0&&(charLen-indexOf0x2e-1)>3))
    {
        return TRUE;
    }

    checkLen= (indexOf0x2e==-1)?charLen:indexOf0x2e;

    //check the first ASCII
    for(i=0;i<checkLen;i++)
    {
        if( 'a'<=pu16LongName[i] && pu16LongName[i]<='z')
        {
            allSmall=TRUE;
            break;
        }
        else if( 'A'<=pu16LongName[i] && pu16LongName[i]<='Z')
        {
            allSmall=FALSE;
            break;
        }
    }


    //check name
    for(i=0;i<checkLen;i++)
    {
        if(pu16LongName[i]&0xFF00)
        {
            return TRUE;
        }
        else if( 'a'<=pu16LongName[i]&&pu16LongName[i]<='z')
        {
            if(!allSmall)
                return TRUE;

        }
        else if( 'A'<=pu16LongName[i]&&pu16LongName[i]<='Z')
        {
            if(allSmall)
                return TRUE;
        }
        else if('0'<=pu16LongName[i]&&pu16LongName[i]<='9')
        {
        }
        else if(  pu16LongName[i]==0x21
                ||pu16LongName[i]==0x23
                ||pu16LongName[i]==0x24
                ||pu16LongName[i]==0x25
                ||pu16LongName[i]==0x26
                ||pu16LongName[i]==0x27
                ||pu16LongName[i]==0x28
                ||pu16LongName[i]==0x29
                ||pu16LongName[i]==0x2D
                ||pu16LongName[i]==0x40
                ||pu16LongName[i]==0x5E
                ||pu16LongName[i]==0x5F
                ||pu16LongName[i]==0x60
                ||pu16LongName[i]==0x7B
                ||pu16LongName[i]==0x7D
                ||pu16LongName[i]==0x7E)
        {
        }
        else
        {
            return TRUE;
        }

    }

    if(indexOf0x2e==-1)
    {
        return FALSE;
    }

    //check extName
    for(i=(indexOf0x2e+1);i<charLen;i++)
    {
        if(pu16LongName[i]&0xFF00)
        {
            return TRUE;
        }
        else if( 'a'<=pu16LongName[i]&&pu16LongName[i]<='z')
        {
            if(!allSmall)
                return TRUE;

        }
        else if( 'A'<=pu16LongName[i]&&pu16LongName[i]<='Z')
        {
            if(allSmall)
                return TRUE;
        }
        else if('0'<=pu16LongName[i]&&pu16LongName[i]<='9')
        {
        }
        else if(  pu16LongName[i]==0x21
                ||pu16LongName[i]==0x23
                ||pu16LongName[i]==0x24
                ||pu16LongName[i]==0x25
                ||pu16LongName[i]==0x26
                ||pu16LongName[i]==0x27
                ||pu16LongName[i]==0x28
                ||pu16LongName[i]==0x29
                ||pu16LongName[i]==0x2D
                ||pu16LongName[i]==0x40
                ||pu16LongName[i]==0x5E
                ||pu16LongName[i]==0x5F
                ||pu16LongName[i]==0x60
                ||pu16LongName[i]==0x7B
                ||pu16LongName[i]==0x7D
                ||pu16LongName[i]==0x7E)
        {
        }
        else
        {
            return TRUE;
        }

    }




    return FALSE;
}


U8 FAT_FileCreateCheckName(U16 *pu16LongName, U8 charLen)
{
    U8 u8Loop;

    if(pu16LongName[0] == FS_CHAR_DOT)
        return FALSE;

    for(u8Loop=0; u8Loop<charLen; u8Loop++)
    {
        if(pu16LongName[u8Loop] == 0x22)    // "
            return FALSE;
        else if(pu16LongName[u8Loop] == FS_CHAR_STAR)    // *
            return FALSE;
        else if(pu16LongName[u8Loop] == FS_CHAR_SLASH)    // /
            return FALSE;
        else if(pu16LongName[u8Loop] == FS_CHAR_COLON)    // :
            return FALSE;
        else if(pu16LongName[u8Loop] == 0x3C)    // <
            return FALSE;
        else if(pu16LongName[u8Loop] == FS_CHAR_GT)    // >
            return FALSE;
        else if(pu16LongName[u8Loop] == FS_CHAR_QM)    // ?
            return FALSE;
        else if(pu16LongName[u8Loop] == 0x5C)    /* \ */
            return FALSE;
        else if(pu16LongName[u8Loop] == 0x7C)    // |
            return FALSE;

    }

    return TRUE;
}


U8 FAT_ClearCluster(U8 u8fsid, U32 u32ClusterNo)
{
    U8 *pu8Tmp;
    U8 u8DeviceIndex, fsid;
    U32 u32SectorNo;
    FAT_FileSysStruct *pFsStruct;
    U32 u32SecPerCluster;
    U8 u8WriteOffset, u8WriteCount;

    pu8Tmp = (U8 xdata* )msAPI_FS_GetAddr(USB_IO_TEMP_ADDR);

    memset(pu8Tmp, 0, 0x1000);

    pFsStruct = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);

    u8DeviceIndex = pFsStruct->DeviceIndex;
    fsid = pFsStruct->FileSystemID;
    u32SecPerCluster = pFsStruct->stBootSector.BPB_SecPerClus;

    u8WriteOffset = 0;
    u32SectorNo =  FAT_FATGetSectorNo(fsid, u32ClusterNo);
    while(u32SecPerCluster > 0)
    {
        u8WriteCount = (u32SecPerCluster>8)?8:u32SecPerCluster;

        if(!msAPI_MSDCtrl_SectorWrite(u8DeviceIndex, (u32SectorNo + u8WriteOffset), u8WriteCount, USB_IO_TEMP_ADDR))
        {
            __ASSERT(0);
            return FALSE;
        }
        if(u32SecPerCluster < 8)
            break;

        u32SecPerCluster -=8;
        u8WriteOffset += 8;
    }

    return TRUE;
}


BOOLEAN FAT_Cache_SetFreeCluster(U8 u8fsid)
{
    FAT_FileSysStruct *pFAT_FileSys;
    U32 u32CurrentClusterNo;
    U32 i;
    U8 *pu8FatTable;
    U32 u32TmpClusterNo=0;
    U8 u8DeviceIndex;
    U32 u32FATStartSectorNo;
    U16 u16BytePerSec;
    U8 u8SectorSize;
    U8 u8FatType;
    U32 u32BPB_TotSec;
    U16 u16Temp;

    /*[01]get file system=======================================================*/
    pFAT_FileSys = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);

    u32CurrentClusterNo = pFAT_FileSys->u32CurrentFreeCluster;
    u8DeviceIndex = (U8)pFAT_FileSys->DeviceIndex;
    u32FATStartSectorNo = pFAT_FileSys->stFAT.u32FATStartSectorNo;
    u16BytePerSec=pFAT_FileSys->stBootSector.BPB_BytsPerSec;
    u8FatType=pFAT_FileSys->stFAT.u8FATType;
    if(u8FatType == FAT_TYPE_FAT32)
    {
        u32BPB_TotSec = pFAT_FileSys->stBootSector.BPB_FATSz32;
    }
    else
        u32BPB_TotSec = 0x1000;

    if(u8FatType == FAT_TYPE_FAT12)
    {
        return FALSE;
    }

    u8SectorSize = (U8)(FAT_TABLE_CACHE_LEN / u16BytePerSec);

    /*[02]speed up=======================================================*/
    for(i=0; i<u32BPB_TotSec; i+=0x100)
    {
        if ( !msAPI_MSDCtrl_SectorRead(u8DeviceIndex, u32FATStartSectorNo + i, 1, USB_IO_TEMP_ADDR ) )
        {
            __ASSERT(0);
            return FALSE;
        }

        pu8FatTable = (U8 xdata* )msAPI_FS_GetAddr(USB_IO_TEMP_ADDR);

        if(u8FatType == FAT_TYPE_FAT32)
        {
            //u32TmpClusterNo = (*(U32*)(pu8FatTable));
            memcpy(&u32TmpClusterNo,pu8FatTable,4);
        }
        else if(u8FatType == FAT_TYPE_FAT16)
        {
            //u32TmpClusterNo = (*(U16*)(pu8FatTable));
            memcpy(&u16Temp,pu8FatTable,2);
            u32TmpClusterNo=(U32)u16Temp;
        }

        if(0x0 == u32TmpClusterNo)
        {
            if(i == 0x100)
                u32CurrentClusterNo = 2;
            break;
        }

        u32CurrentClusterNo = u32TmpClusterNo;
    }

    pFAT_FileSys = (FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);

    pFAT_FileSys->u32CurrentFreeCluster = u32CurrentClusterNo;
    //printf("(%02bx)Init u32CurrentFreeCluster: %LX, count: %LX\n", u8FatType, pFAT_FileSys->u32CurrentFreeCluster, i);

    return TRUE;
}


#endif
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


#define FAT32_ENTRY_CACHE_COUNT 1024 //4096/4
BOOLEAN FAT_FAT32ClusterChainScan(U8 u8fsid, U32 u32StartClusterNo, U32 *u32LenToSet, U32 *NextClusterToSet)
{
    FAT_FileSysStruct *pFsStruct;
    U16 u16BeginOffset=0;
    U16 u16BytePerSec;
    U32 FATStartSector;
    U8 deviceIndex;
    U32 u32TableCacheAddress= (FILE_FAT_TABLE_CACHE + (U32)u8fsid * FAT_TABLE_CACHE_LEN) ;

    pFsStruct=(FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);
    if(pFsStruct->bIsFATCacheDirty)
           FAT_FATStructureWrite(u8fsid);
    u16BytePerSec=pFsStruct->stBootSector.BPB_BytsPerSec;
    deviceIndex=pFsStruct->DeviceIndex;
    FATStartSector=pFsStruct->stFAT.u32FATStartSectorNo;

    s_u8ReadSectorCount=(U8)(FAT_TABLE_CACHE_LEN/u16BytePerSec);
    s_u32ClusterNo = u32StartClusterNo;
    s_u32SectorNo=(s_u32ClusterNo/FAT32_ENTRY_CACHE_COUNT)*s_u8ReadSectorCount;

    if ( !msAPI_MSDCtrl_SectorRead(deviceIndex, FATStartSector + s_u32SectorNo, s_u8ReadSectorCount, u32TableCacheAddress) )
    {
        __ASSERT(0);
        return FALSE;
    }
    else
    {
        pFsStruct=(FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);

        pFsStruct->u32FATTableOffsetSectorNo = s_u32SectorNo;
        s_u16FATEntryCacheOffset=s_u32ClusterNo%FAT32_ENTRY_CACHE_COUNT;
    }

    u16BeginOffset=s_u16FATEntryCacheOffset;
    s_pu32FAT32EntryCache= (U32*)FCtrl_GetFatTableCacheInfo(u8fsid);

    if(s_pu32FAT32EntryCache==NULL)
    {
        __ASSERT(0);
        return FALSE;
    }

    s_u16Count=0;
    while(TRUE)
    {

        while(s_u16FATEntryCacheOffset < FAT32_ENTRY_CACHE_COUNT)
        {
            s_u32ClusterNo++;
            if(s_u32ClusterNo!=(*(s_pu32FAT32EntryCache+s_u16FATEntryCacheOffset)))
            {
                if(s_u16Count>0)
                {
                    *u32LenToSet = ((U32)s_u16Count)*FAT32_ENTRY_CACHE_COUNT-u16BeginOffset+1+s_u16FATEntryCacheOffset;
                }
                else
                {
                    *u32LenToSet = s_u16FATEntryCacheOffset-u16BeginOffset+1;
                }
                *NextClusterToSet = (*(s_pu32FAT32EntryCache+s_u16FATEntryCacheOffset));

                if(*NextClusterToSet == 0)
                {
                        MS_DEBUG_MSG(printf("Detect FAT32 file cluster chain broken. Fix it.\n"));
                        ASSERT(0);
                        *(s_pu32FAT32EntryCache+s_u16FATEntryCacheOffset) = 0xfffffff8;
                        if ( !msAPI_MSDCtrl_SectorWrite(deviceIndex, FATStartSector + s_u32SectorNo,s_u8ReadSectorCount,u32TableCacheAddress))
                        {
                            __ASSERT(0);
                            return FALSE;
                        }
                        *NextClusterToSet = 0xFFFFFFF8;
                }

                pFsStruct=(FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);

                pFsStruct->u32FATTableOffsetSectorNo = s_u32SectorNo;
                return TRUE;
            }
            s_u16FATEntryCacheOffset ++;
        }


        s_u32SectorNo+= s_u8ReadSectorCount;
        if ( !msAPI_MSDCtrl_SectorRead(deviceIndex, FATStartSector + s_u32SectorNo,s_u8ReadSectorCount,u32TableCacheAddress) )
        {
            __ASSERT(0);
            return FALSE;
        }
        else
        {
            s_u16FATEntryCacheOffset=0;
        }

        s_u16Count+=1;

    }

    return TRUE;
}

#define FAT16_ENTRY_CACHE_COUNT 2048 //4096/2
BOOLEAN FAT_FAT16ClusterChainScan(U8 u8fsid, U32 u32StartClusterNo, U32 *u32LenToSet, U32 *NextClusterToSet)
{
    FAT_FileSysStruct *pFsStruct;
    U16 u16BeginOffset=0;
    U16 u16BytePerSec;
    U32 FATStartSector;
    U8 deviceIndex;
    U32 u32TableCacheAddress= (FILE_FAT_TABLE_CACHE + (U32)u8fsid * FAT_TABLE_CACHE_LEN) ;

    pFsStruct=(FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);
    if(pFsStruct->bIsFATCacheDirty)
           FAT_FATStructureWrite(u8fsid);
    u16BytePerSec=pFsStruct->stBootSector.BPB_BytsPerSec;
    deviceIndex=pFsStruct->DeviceIndex;
    FATStartSector=pFsStruct->stFAT.u32FATStartSectorNo;

    s_u8ReadSectorCount=(U8)(FAT_TABLE_CACHE_LEN/u16BytePerSec);
    s_u32ClusterNo = u32StartClusterNo;
    s_u32SectorNo=(s_u32ClusterNo/FAT16_ENTRY_CACHE_COUNT)*s_u8ReadSectorCount;

    if ( !msAPI_MSDCtrl_SectorRead(deviceIndex, FATStartSector + s_u32SectorNo, s_u8ReadSectorCount, u32TableCacheAddress) )
    {
        __ASSERT(0);
        return FALSE;
    }
    else
    {
        pFsStruct=(FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);

        pFsStruct->u32FATTableOffsetSectorNo = s_u32SectorNo;
        s_u16FATEntryCacheOffset=s_u32ClusterNo%FAT16_ENTRY_CACHE_COUNT;
    }

    u16BeginOffset=s_u16FATEntryCacheOffset;
    s_pu16FAT16EntryCache= (U16*)FCtrl_GetFatTableCacheInfo(u8fsid);

    if(s_pu16FAT16EntryCache==NULL)
    {
        __ASSERT(0);
        return FALSE;
    }

    s_u16Count=0;
    while(TRUE)
    {

        while(s_u16FATEntryCacheOffset < FAT16_ENTRY_CACHE_COUNT)
        {
            s_u32ClusterNo++;
            if(s_u32ClusterNo!=(*(s_pu16FAT16EntryCache+s_u16FATEntryCacheOffset)))
            {
                if(s_u16Count>0)
                {
                    *u32LenToSet = ((U32)s_u16Count)*FAT16_ENTRY_CACHE_COUNT-u16BeginOffset+1+s_u16FATEntryCacheOffset;
                }
                else
                {
                    *u32LenToSet = s_u16FATEntryCacheOffset-u16BeginOffset+1;
                }

                *NextClusterToSet = (*(s_pu16FAT16EntryCache+s_u16FATEntryCacheOffset));
                if(*NextClusterToSet == 0)
                {
                        MS_DEBUG_MSG(printf("Detect FAT16 file cluster chain broken. Fix it.\n"));
                        ASSERT(0);
                        *(s_pu16FAT16EntryCache+s_u16FATEntryCacheOffset) = 0xfff8;
                        if ( !msAPI_MSDCtrl_SectorWrite(deviceIndex, FATStartSector + s_u32SectorNo,s_u8ReadSectorCount,u32TableCacheAddress))
                        {
                            __ASSERT(0);
                            return FALSE;
                        }
                        *NextClusterToSet = 0xFFF8;
                }

                if(*NextClusterToSet >= 0xFFF8)
                {
                    *NextClusterToSet |= 0xFFFFF000;
                }

                pFsStruct=(FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);

                pFsStruct->u32FATTableOffsetSectorNo = s_u32SectorNo;
                return TRUE;
            }
            s_u16FATEntryCacheOffset ++;
        }


        s_u32SectorNo+= s_u8ReadSectorCount;
        if ( !msAPI_MSDCtrl_SectorRead(deviceIndex, FATStartSector + s_u32SectorNo,s_u8ReadSectorCount,u32TableCacheAddress) )
        {
            __ASSERT(0);
            return FALSE;
        }
        else
        {
            s_u16FATEntryCacheOffset=0;
        }

        s_u16Count+=1;

    }

    return TRUE;
}

// scan a continus cluster
BOOLEAN FAT_FAT12ClusterChainScan(U8 u8fsid, U32 u32StartClusterNo, U32 *u32LenToSet, U32 *NextClusterToSet)
{
    FAT_FileSysStruct *pFsStruct;
    U32 u8FatType;
    U32 u32TempFatTableOffsetSectorNo;
    U32 u32FatTableEntryOffset;
    U32 u32ClusterNo;
    U32 u32NextClusterNo;
    U16 u16BytePerSec;
    U16 u16TempEntry;
    U8 *pu8FatTable;

    U32 u32Count = 0;
    U32 u32High, u32Low;

    pFsStruct=(FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);

    u8FatType=pFsStruct->stFAT.u8FATType;
    u16BytePerSec=pFsStruct->stBootSector.BPB_BytsPerSec;
    u32TempFatTableOffsetSectorNo = pFsStruct->u32FATTableOffsetSectorNo;

    if(pFsStruct->bIsFATCacheDirty)
           FAT_FATStructureWrite(u8fsid);

    u32ClusterNo = u32StartClusterNo;
    u32Low = (u32TempFatTableOffsetSectorNo * u16BytePerSec) ;
    u32High = u32Low + FAT_TABLE_CACHE_LEN;
    while(TRUE)
    {
        u32FatTableEntryOffset = u32ClusterNo * 3UL / 2UL;

        if ( u32FatTableEntryOffset < u32Low || u32FatTableEntryOffset >= u32High)
        {

            //pFsStruct=(FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);

            u32TempFatTableOffsetSectorNo = u32FatTableEntryOffset / u16BytePerSec;

            if ( !FAT_FATStructureFetch(u8fsid, u32TempFatTableOffsetSectorNo) )
            {
                pFsStruct=(FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);

                pFsStruct->u32FATTableOffsetSectorNo = u32TempFatTableOffsetSectorNo;
                 __ASSERT(0);
                 return FALSE;
            }
            u32Low = u32TempFatTableOffsetSectorNo * u16BytePerSec;
            u32High = u32Low + FAT_TABLE_CACHE_LEN;
        }

        u32FatTableEntryOffset -= u32Low;
        pu8FatTable = (U8*)FCtrl_GetFatTableCacheInfo(u8fsid);

        if(pu8FatTable==NULL)
        {
            __ASSERT(0);
            return FALSE;
        }

        while((U16)u32FatTableEntryOffset < FAT_TABLE_CACHE_LEN)
        {
            if((U16)u32FatTableEntryOffset == FAT_TABLE_CACHE_LEN - 1)
            {
                pFsStruct = (FAT_FileSysStruct *)FCtrl_GetFileSystemInfo(u8fsid);

                u16TempEntry = (U16)(pFsStruct->u8FAT12LastEntryByte) << 8;
                u16TempEntry |= (U16)*(pu8FatTable + (U16)u32FatTableEntryOffset);
            }
            else
            {
                //u16TempEntry = (*(U16*)(pu8FatTable + (U16)u32FatTableEntryOffset));
                memcpy(&u16TempEntry,(pu8FatTable + (U16)u32FatTableEntryOffset),2);
            }

            if((u32ClusterNo & 1) == 0)
            {
                u32NextClusterNo = (U32)(u16TempEntry & 0x0FFF);
                u32FatTableEntryOffset ++;
            }
            else
            {
                u32NextClusterNo = (U32)(u16TempEntry >> 4);
                u32FatTableEntryOffset +=2;
            }
            if(u32NextClusterNo >= 0xFF8)
            {
                u32NextClusterNo |= 0xFFFFF000;
            }

            u32Count++;
            u32ClusterNo++;
            if(u32NextClusterNo != u32ClusterNo)
            {
                *u32LenToSet = u32Count;
                *NextClusterToSet = u32NextClusterNo;

                pFsStruct=(FAT_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);

                pFsStruct->u32FATTableOffsetSectorNo = u32TempFatTableOffsetSectorNo;

                return TRUE;
            }
        }

    }

    return TRUE;
}


#undef FAT_CACHE_C
