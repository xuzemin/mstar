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
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <mntent.h>
#include <sys/vfs.h>
#include <pthread.h>


#include "MsCommon.h"
#include "Wrapper_Common.h"
#include "N51FS_Wrapper.h"
#include "linux_51fs_wrap.h"

#include <assert.h>
#if (OBA2)
#include "madp.h"
#endif
static USB_PORT_STATUS g_usbConnectStatus;
static DRIVE_INFO  g_drvInfo[MAX_DRV_COUNT];
static U32 g_drvUsedMask[(MAX_DRV_COUNT+31)/32];

#define IS_DRV_SLOT_USED(i)    (g_drvUsedMask[i/32] & (1<<(i&31)))
#define SET_DRV_SLOT_USED(i)    do{g_drvUsedMask[i/32] |=  (1<<(i&31));}while(0)
#define CLR_DRV_SLOT_USED(i)    do{g_drvUsedMask[i/32] &= ~(1<<(i&31));}while(0)



typedef struct
{
   DIR *dir;
   U8 drvID;
   char envCurrentDir[MAX_PATH_NAME_LEN];
}ENV_INFO;


ENV_INFO  g_envInfo[MAX_ENV_CNT];
U32 g_EnvUsedMask[(MAX_ENV_CNT+31)/32];
#define IS_ENV_SLOT_USED(i)    (g_EnvUsedMask[i/32] & (1<<(i&31)))
#define SET_ENV_SLOT_USED(i)    do{g_EnvUsedMask[i/32] |=  (1<<(i&31));}while(0)
#define CLR_ENV_SLOT_USED(i)    do{g_EnvUsedMask[i/32] &= ~(1<<(i&31));}while(0)


typedef struct
{
   int fd;
   U8 drvID;
   char fullPathName[MAX_PATH_NAME_LEN];
}FILE_HANDLE_INFO;

#if (OBA2 == 1)
typedef struct
{
     U8 drvId;
     EN_FILE_SYSTEM_TYPE fsType;
     EN_FILE_SYSTEM_MNT_MODE mountMode;
     U8 portNO;
     char devName[MAX_PATH_NAME_LEN];
     char mountpoint[MAX_PATH_NAME_LEN];
}MNT_INFO;
typedef enum
{
    E_OBAMA_FS_MOUNT_POINT_ADD, //signal
    E_OBAMA_FS_MOUNT_POINT_REMOVE, //signal
    E_OBAMA_FS_GET_FIRST_DRV_INFO, //method call
    E_OBAMA_FS_GET_NEXT_DRV_INFO, //method call
}E_OBAMA_FS_MSG_TYPE;
#endif

#define MAX_FILEHANDLE_CNT 255
FILE_HANDLE_INFO g_fileHandle[MAX_FILEHANDLE_CNT];
U32 g_FdUsedMask[(MAX_FILEHANDLE_CNT+31)/32];
#define IS_FD_SLOT_USED(i)    (g_FdUsedMask[i/32] & (1<<(i&31)))
#define SET_FD_SLOT_USED(i)    do{g_FdUsedMask[i/32] |=  (1<<(i&31));}while(0)
#define CLR_FD_SLOT_USED(i)    do{g_FdUsedMask[i/32] &= ~(1<<(i&31));}while(0)
MS_S32 g_fswrapper_mutex  = -1;
long      g_fs_thread_lock_cnt = 0;
pthread_t g_cur_lock_owner = -1;

static void FS_LockThread(void)
{
    pthread_t   pTSelf;

    pTSelf = pthread_self();
   assert(0 <= g_fswrapper_mutex);

    if(pTSelf == g_cur_lock_owner)
    {
        assert(1 <= g_fs_thread_lock_cnt);
        g_fs_thread_lock_cnt++;
    }
    else
    {
        MsOS_ObtainMutex(g_fswrapper_mutex, MSOS_WAIT_FOREVER);
        g_fs_thread_lock_cnt = 1;
        g_cur_lock_owner = pTSelf;
    }

}
static void FS_UnlockThread(void)
{
    pthread_t   pTSelf;

    pTSelf = pthread_self();
    assert(0 <= g_fswrapper_mutex);
    assert(pTSelf == g_cur_lock_owner);
    assert(1 <= g_fs_thread_lock_cnt);

    if(0 == --g_fs_thread_lock_cnt)
    {
        g_cur_lock_owner = -1;
        MsOS_ReleaseMutex(g_fswrapper_mutex);
    }

}

void FS_Stub_Init()
{
    U8 i;
    memset(g_drvUsedMask, 0, sizeof(g_drvUsedMask));
    memset(&g_usbConnectStatus, 0, sizeof(g_usbConnectStatus));
    for( i=0; i<MAX_DEVICE_CNT; i++)
    {
         g_usbConnectStatus.deviceStatus[i] = MSD_STATUS_EMPTY;
         g_usbConnectStatus.devicePort[i] = INVALID_MSD_PORT;
    }

    memset(g_drvInfo, 0, sizeof(g_drvInfo));
    memset(g_envInfo, 0, sizeof(g_envInfo));
    memset(g_EnvUsedMask, 0, sizeof(g_EnvUsedMask));
    memset(g_fileHandle, 0, sizeof(g_fileHandle));
    memset(g_FdUsedMask, 0, sizeof(g_FdUsedMask));
    g_fswrapper_mutex = MsOS_CreateMutex(E_MSOS_FIFO, "N51FS_Wrapper",MSOS_PROCESS_PRIVATE);
    assert(0 <= g_fswrapper_mutex);
}

BOOL IsDevMounted(const char *devName)
{
    U32 i;
    FS_LockThread();
    for( i=0; i<MAX_DRV_COUNT; i++)
       if(IS_DRV_SLOT_USED(i) &&  strcmp(g_drvInfo[i].devName, devName) == 0)
       {
           FS_UnlockThread();
           return TRUE;
       }
    FS_UnlockThread();
    return FALSE;
}

U8 FindDrvByMountPoint(const char *mountpoint)
{
    U32 i;
    FS_LockThread();
    for( i=0; i<MAX_DRV_COUNT; i++)
       if(IS_DRV_SLOT_USED(i) &&  strcmp(g_drvInfo[i].mountpoint, mountpoint) == 0)
       {
           FS_UnlockThread();
           return i;
       }
    FS_UnlockThread();
    return INVALID_DRV_ID;
}

U8 GetFreeDrvSlot(void)
{
    U32 i;

    FS_LockThread();
    for( i=0; i<MAX_DRV_COUNT; i++)
       if(IS_DRV_SLOT_USED(i) == 0)
       {
           FS_UnlockThread();
           return i;
       }
    FS_UnlockThread();
    return INVALID_DRV_ID;
}

U8 GetFreeENVSlot(void)
{
    U32 i;

    FS_LockThread();
    for( i=0; i<MAX_ENV_CNT; i++)
       if(IS_ENV_SLOT_USED(i) == 0)
       {
           FS_UnlockThread();
           return i;
       }
    FS_UnlockThread();
    return INVALID_FS_ENVIRONMENT_INDEX;
}
U8 GetFreeFDSlot(void)
{
    U32 i;
    FS_LockThread();
    for( i=0; i<MAX_FILEHANDLE_CNT; i++)
       if(IS_FD_SLOT_USED(i) == 0)
       {
           FS_UnlockThread();
           return i;
       }
    FS_UnlockThread();
    return INVALID_FILE_HANDLE;
}

void FS_NotifyDrvMount(U8 busNo, U8 majorNo, U8 minorNo, const char *devName, const char *mountpoint, EN_FILE_SYSTEM_TYPE fsType,
                                    EN_FILE_SYSTEM_MNT_MODE fsMountMode,  U8 deviceType)
{
     U8 drvID;
     U8 portNO;
     U8 busNoMap2Port[MSD_PORT_NUM+1] = {0, 1, 2, 3, 4};
     U8 devIdx;
     pid_t pid = getpid();

     UNUSED(majorNo);

     WPFS_DBG("mount %s\n", devName);
     FS_LockThread();
     if(IsDevMounted(devName) || FindDrvByMountPoint(mountpoint)!=INVALID_DRV_ID)
     {
        WPFS_DBG("Serious error, drv already in mount list\n");
        FS_UnlockThread();
        return;
     }
     if(MSD_PORT_NUM<busNo || 0==busNo)
     {
        WPFS_DBG("Serious error, Unknow bus NO\n");
        FS_UnlockThread();
        return;
     }

     drvID = GetFreeDrvSlot();
     if(drvID == INVALID_DRV_ID)
     {
         WPFS_DBG("drv slot overflow for %s\n", devName);
         FS_UnlockThread();
         return;
     }

     portNO = busNoMap2Port[busNo];
     devIdx=minorNo>>4;

     switch (portNO)
     {
       case MSD_PORT_1:
           devIdx+=MSD_USB_INDEX_START;
           break;
       case MSD_PORT_2:
           devIdx+=MSD_USB_2_INDEX_START;
           break;

       case MSD_PORT_0:
       case MSD_PORT_3:
       case MSD_PORT_4:
       default:
           printf("ERROR!! MSD_PORT %d is not supported in Linux N51FS wrapper!!\n",portNO);
           return;
     }

     g_drvInfo[drvID].portNO = portNO;
     g_drvInfo[drvID].deviceID =devIdx;
     strcpy(g_drvInfo[drvID].devName, devName);
     strcpy(g_drvInfo[drvID].mountpoint, mountpoint);
     g_drvInfo[drvID].fsType = fsType;
     g_drvInfo[drvID].mountMode = fsMountMode;
     g_usbConnectStatus.driveNumber[portNO]++;
     g_usbConnectStatus.port_connect_status |= 1<<portNO;
     g_usbConnectStatus.devicePort[g_drvInfo[drvID].deviceID] = portNO;
     g_usbConnectStatus.deviceStatus[g_drvInfo[drvID].deviceID] = MSD_STATUS_IDLE;
     g_usbConnectStatus.deviceDrvCnt[g_drvInfo[drvID].deviceID]++;
     g_usbConnectStatus.usbPortStatus[portNO] = deviceType;
     SET_DRV_SLOT_USED(drvID);
     FS_UnlockThread();
  //  printf("mount drv %d port %d, dev%d\n", drvID, portNO, minorNo>>4);
#if (OBA2 == 1)
    // test DBUS
    U8 u8ChIndex ;

    u8ChIndex = MAdp_MSGCH_GetChannelIndex("FS_MOUNT_STATUS");

    U8 u8DataMnt[MAX_PATH_NAME_LEN+1+sizeof(pid_t)];
    u8DataMnt[0] = E_OBAMA_FS_MOUNT_POINT_ADD;
    memcpy(u8DataMnt+1, &pid, sizeof(pid_t));
    strcpy( (char *)&u8DataMnt[1]+sizeof(pid_t) ,g_drvInfo[drvID].mountpoint);
    if (MAdp_MSGCH_SendSignal(ALL_PID,u8ChIndex, u8DataMnt, sizeof(u8DataMnt)))
    {
        printf("[D-Bus] Send (E_OBAMA_FS_MOUNT_POINT_ADD) OK\n");
    }
    else
    {
        printf("[D-Bus] Send (E_OBAMA_FS_MOUNT_POINT_ADD) Error\n");
    }

#endif

}

void CloseAllFdOnDrv(U8 drvID)
{
    U8 u8HandleNo;
    FS_LockThread();
    for( u8HandleNo=0; u8HandleNo<MAX_FILEHANDLE_CNT; u8HandleNo++)
        if(IS_FD_SLOT_USED(u8HandleNo) && g_fileHandle[u8HandleNo].drvID == drvID)
       {
            assert(g_fileHandle[u8HandleNo].fd >= 0);
            FS_FileClose(u8HandleNo);
       }
    FS_UnlockThread();
}

void FS_ResetAllFileHandle(void)
{
    U8 u8HandleNo;

    FS_LockThread();
    for( u8HandleNo=0; u8HandleNo<MAX_FILEHANDLE_CNT; u8HandleNo++)
        if(IS_FD_SLOT_USED(u8HandleNo))
       {
            assert(g_fileHandle[u8HandleNo].fd >= 0);
            FS_FileClose(u8HandleNo);
       }
     FS_UnlockThread();
}


void CloseAllEnvOnDrv(U8 drvID)
{
    U8 envID;
    FS_LockThread();
    for( envID=0; envID<MAX_ENV_CNT; envID++)
        if(IS_ENV_SLOT_USED(envID) && g_envInfo[envID].drvID == drvID)
       {
            FS_DestroyEnv(envID);
       }
    FS_UnlockThread();
}
void FS_NotifyDrvUnMount(const char *mountpoint)
{
     U8 drvID;
     U8 portNO;
     pid_t pid = getpid();

     WPFS_DBG("unmount %s\n", mountpoint);

     FS_LockThread();
     drvID = FindDrvByMountPoint(mountpoint);
     if(drvID == INVALID_DRV_ID)
     {
        FS_UnlockThread();
        return;
     }
     CloseAllFdOnDrv(drvID);
     CloseAllEnvOnDrv(drvID);

     portNO =  g_drvInfo[drvID].portNO;

     ASSERT(g_usbConnectStatus.deviceDrvCnt[g_drvInfo[drvID].deviceID]);
     g_usbConnectStatus.deviceDrvCnt[g_drvInfo[drvID].deviceID]--;
     if(0 == g_usbConnectStatus.deviceDrvCnt[g_drvInfo[drvID].deviceID])
     {
          g_usbConnectStatus.deviceStatus[g_drvInfo[drvID].deviceID] = MSD_STATUS_EMPTY;
          g_usbConnectStatus.devicePort[g_drvInfo[drvID].deviceID] = INVALID_MSD_PORT;
     }


     ASSERT(g_usbConnectStatus.port_connect_status & (1<<portNO));
     ASSERT(g_usbConnectStatus.driveNumber[portNO]);
     if(--g_usbConnectStatus.driveNumber[portNO]  == 0)
     {
          g_usbConnectStatus.port_connect_status &= ~(1<<portNO);
     }
     CLR_DRV_SLOT_USED(drvID);
     FS_UnlockThread();

#if (OBA2 == 1)
    // test DBUS
    U8 u8ChIndex;

    u8ChIndex = MAdp_MSGCH_GetChannelIndex("FS_MOUNT_STATUS");
    printf("test\n");
    U8 u8DataMnt[MAX_PATH_NAME_LEN+1+sizeof(pid_t)];
    u8DataMnt[0] = E_OBAMA_FS_MOUNT_POINT_REMOVE;
    memcpy(u8DataMnt+1, &pid, sizeof(pid_t));
    strcpy( (char *)&u8DataMnt[1]+sizeof(pid_t) ,g_drvInfo[drvID].mountpoint);
    if (MAdp_MSGCH_SendSignal(ALL_PID,u8ChIndex, u8DataMnt, sizeof(u8DataMnt)))
    {
        printf("[D-Bus] Send (E_OBAMA_FS_MOUNT_POINT_REMOVE) OK\n");
    }
    else
    {
        printf("[D-Bus] Send (E_OBAMA_FS_MOUNT_POINT_REMOVE) Error\n");
    }
#endif
}

U8 FS_CreateEnv(U8 drvID)
{
     U8 envID;
     char buf[MAX_PATH_NAME_LEN];
     if(drvID >= MAX_DRV_COUNT)
        return INVALID_FS_ENVIRONMENT_INDEX;
     FS_LockThread();
     if(IS_DRV_SLOT_USED(drvID) == 0)
     {
         FS_UnlockThread();
         return INVALID_FS_ENVIRONMENT_INDEX;
     }

     envID = GetFreeENVSlot();
     if(envID == INVALID_FS_ENVIRONMENT_INDEX)
     {
         FS_UnlockThread();
         return INVALID_FS_ENVIRONMENT_INDEX;
     }
     g_envInfo[envID].drvID = drvID;
     sprintf(buf, "%s/", g_drvInfo[drvID].mountpoint);
     g_envInfo[envID].dir = opendir(buf);
     if(g_envInfo[envID].dir  == NULL)
     {
          FS_UnlockThread();
          return INVALID_FS_ENVIRONMENT_INDEX;
     }
     strcpy(g_envInfo[envID].envCurrentDir, g_drvInfo[drvID].mountpoint);
     SET_ENV_SLOT_USED(envID);
     FS_UnlockThread();
     return envID;
}
BOOL FS_DestroyEnv(U8 envID)
{
    if(envID>=MAX_ENV_CNT || IS_ENV_SLOT_USED(envID)==0)
        return FALSE;
    FS_LockThread();
    if(g_envInfo[envID].dir)
        closedir(g_envInfo[envID].dir);
    CLR_ENV_SLOT_USED(envID);
    FS_UnlockThread();
    return TRUE;
}
U8 FS_GetDrvID(U8 u8EnvID)
{
    if(u8EnvID>=MAX_ENV_CNT || IS_ENV_SLOT_USED(u8EnvID)==0)
        return INVALID_DRV_ID;
    return g_envInfo[u8EnvID].drvID;
}
const char *FS_GetMountPoint(U8 drvID)
{
    if(drvID>=MAX_DRV_COUNT || IS_DRV_SLOT_USED(drvID)==0)
        return NULL;
    return g_drvInfo[drvID].mountpoint;
}
BOOL FS_SetEnvCurrentDir(U8 envID, const char *targetDir)
{
    DIR *dir;
    char buf[MAX_PATH_NAME_LEN];
    if(envID>=MAX_ENV_CNT || IS_ENV_SLOT_USED(envID)==0)
        return FALSE;
     sprintf(buf, "%s/", targetDir);
     dir = opendir(buf);
     if(dir  == NULL)
        return FALSE;
      if(g_envInfo[envID].dir)
        closedir(g_envInfo[envID].dir);
      g_envInfo[envID].dir = dir;
     strcpy(g_envInfo[envID].envCurrentDir, targetDir);
     return TRUE;
}
const char* FS_GetEnvCurrentDir(U8 envID)
{
    if(envID>=MAX_ENV_CNT || IS_ENV_SLOT_USED(envID)==0)
        return NULL;
    return g_envInfo[envID].envCurrentDir;
}
BOOL FS_EntryFirst(U8 envID)
{
    FS_LockThread();
    if(envID>=MAX_ENV_CNT || IS_ENV_SLOT_USED(envID)==0)
    {
        FS_UnlockThread();
        return FALSE;
     }
    if(g_envInfo[envID].dir)
        closedir(g_envInfo[envID].dir);
    g_envInfo[envID].dir = opendir(g_envInfo[envID].envCurrentDir);
    FS_UnlockThread();
    return (g_envInfo[envID].dir!=NULL)?TRUE:FALSE;
}
EN_ENTRY_NEXT_RESULT FS_EntryNext(U8 envId,FileEntry* pFileToSet)
{
     struct dirent *next;
     struct stat statbuf;
     char fullpathname[MAX_PATH_NAME_LEN];

     FS_LockThread();
     if(envId>=MAX_ENV_CNT || IS_ENV_SLOT_USED(envId)==0)
     {
        FS_UnlockThread();
        return ENTRY_NEXT_RESULT_ERROR;
     }
    if(g_envInfo[envId].dir == NULL)
    {
         FS_UnlockThread();
        return ENTRY_NEXT_RESULT_ERROR;
   }


    while(1)
    {
        if((next = readdir(g_envInfo[envId].dir)) == NULL)
        {
               FS_UnlockThread();
               return ENTRY_NEXT_RESULT_LAST;
        }

        sprintf(fullpathname, "%s/%s", g_envInfo[envId].envCurrentDir, next->d_name);
        if(stat(fullpathname, &statbuf) < 0)
        {
            WPFS_DBG("Failed to stat %s, skip it\n", fullpathname);
            continue;
        }

        pFileToSet->EntryAttrib = 0;
        if(0 == (S_IWRITE& statbuf.st_mode))
             pFileToSet->EntryAttrib  |= ENTRY_ATTRIB_READ_ONLY;

        if(IS_DIR_DOT(next->d_name))
        {
               continue;
              // pFileToSet->EntryAttrib  |= ENTRY_ATTRIB_DIRECTORY;
              // pFileToSet->EntryType = ENTRY_TYPE_DIR_DOT;
        }
        else if(IS_DIR_DOTDOT(next->d_name))
        {
             //  if(isCurrentRoot)
                  continue;
             // pFileToSet->EntryAttrib  |= ENTRY_ATTRIB_DIRECTORY;
              // pFileToSet->EntryType = ENTRY_TYPE_DIR_DOTDOT;
        }
        else if(S_ISDIR(statbuf.st_mode))
        {
               pFileToSet->EntryAttrib  |= ENTRY_ATTRIB_DIRECTORY;
               pFileToSet->EntryType = ENTRY_TYPE_DIR;
        }
        else if(S_ISREG(statbuf.st_mode))
               pFileToSet->EntryType = ENTRY_TYPE_FILE;
        else
               continue;
        strcpy(pFileToSet->fullname, fullpathname);
        pFileToSet->FileSystemID = g_envInfo[envId].drvID;
        pFileToSet->st_mode = statbuf.st_mode;
        pFileToSet->FileLength.Hi = 0;
        pFileToSet->EntryFileLength = statbuf.st_size;
        pFileToSet->FileLength.Lo = statbuf.st_size;
        pFileToSet->EntrySeconds = statbuf.st_mtime;
        pFileToSet->EnvironmentID = envId;
        FS_UnlockThread();
        return ENTRY_NEXT_RESULT_SUCCESS;
     }
}
extern const char *GetParentDirectory(const char *pStrPath);
BOOL FS_GetRelativeDirEntry(U8 envId,FileEntry* pFileToSet, BOOL isGetParent)
{
     struct stat statbuf;
     BOOL bRes = FALSE;
     const char *currentDir;

     FS_LockThread();
     currentDir = FS_GetEnvCurrentDir(envId);

     if(currentDir == NULL)
        goto RET;

     if(isGetParent)
     {
        const char *mountpoint;
        currentDir = GetParentDirectory(currentDir);
        if(currentDir == NULL)
                goto RET;
        mountpoint = FS_GetMountPoint(FS_GetDrvID(envId));
        if(mountpoint == NULL)
        {
            WPFS_DBG("Somethine abnormal\n");
              goto RET;
        }
        if(strlen(currentDir) < strlen(mountpoint))
              goto RET;
        pFileToSet->EntryType = ENTRY_TYPE_DIR_DOTDOT;
     }
     else
        pFileToSet->EntryType = ENTRY_TYPE_DIR_DOT;


     if(stat(currentDir, &statbuf) < 0)
     {
           WPFS_DBG("Failed to stat %s\n", currentDir);
             goto RET;
     }

     strcpy(pFileToSet->fullname, currentDir);
     pFileToSet->FileSystemID = FS_GetDrvID(envId);
     pFileToSet->st_mode = statbuf.st_mode;
     pFileToSet->FileLength.Hi = 0;
     pFileToSet->EntryFileLength = statbuf.st_size;
     pFileToSet->FileLength.Lo = statbuf.st_size;
     pFileToSet->EntrySeconds = statbuf.st_mtime;
     pFileToSet->EnvironmentID = envId;
     pFileToSet->EntryAttrib = ENTRY_ATTRIB_DIRECTORY;
     bRes = TRUE;
 RET:
     FS_UnlockThread();
     return bRes;
}
BOOL FS_GetCurrentFileEntry(U8 envId,FileEntry* pFileToSet)
{
     off_t curDirPos;
     struct dirent *next;
     struct stat statbuf;
     char fullpathname[MAX_PATH_NAME_LEN];
     BOOL bRes = FALSE;

      FS_LockThread();
     if(envId>=MAX_ENV_CNT || IS_ENV_SLOT_USED(envId)==0)
        goto RET;
    if(g_envInfo[envId].dir == NULL)
        goto RET;

    curDirPos = telldir(g_envInfo[envId].dir);
    while(1)
    {
        if((next = readdir(g_envInfo[envId].dir)) == NULL)
        {
               seekdir(g_envInfo[envId].dir, curDirPos);
               goto RET;
        }

        sprintf(fullpathname, "%s/%s", g_envInfo[envId].envCurrentDir, next->d_name);

        if(stat(fullpathname, &statbuf) < 0)
        {
            WPFS_DBG("Failed to stat %s, skip it\n", fullpathname);
            continue;
        }


        pFileToSet->EntryAttrib = 0;
        if(0 == (S_IWRITE& statbuf.st_mode))
             pFileToSet->EntryAttrib  |= ENTRY_ATTRIB_READ_ONLY;

        if(IS_DIR_DOT(next->d_name))
        {
               pFileToSet->EntryAttrib  |= ENTRY_ATTRIB_DIRECTORY;
               pFileToSet->EntryType = ENTRY_TYPE_DIR_DOT;
        }
        else if(IS_DIR_DOTDOT(next->d_name))
        {
               pFileToSet->EntryAttrib  |= ENTRY_ATTRIB_DIRECTORY;
               pFileToSet->EntryType = ENTRY_TYPE_DIR_DOTDOT;
        }
        else if(S_ISDIR(statbuf.st_mode))
        {
               pFileToSet->EntryAttrib  |= ENTRY_ATTRIB_DIRECTORY;
               pFileToSet->EntryType = ENTRY_TYPE_DIR;
        }
        else if(S_ISREG(statbuf.st_mode))
               pFileToSet->EntryType = ENTRY_TYPE_FILE;

        strcpy(pFileToSet->fullname, fullpathname);
        pFileToSet->FileSystemID = g_envInfo[envId].drvID;
        pFileToSet->st_mode = statbuf.st_mode;
        pFileToSet->FileLength.Hi = 0;
        pFileToSet->EntryFileLength = statbuf.st_size;
        pFileToSet->FileLength.Lo = statbuf.st_size;
        pFileToSet->EntrySeconds = statbuf.st_mtime;
        pFileToSet->EnvironmentID = envId;

        seekdir(g_envInfo[envId].dir, curDirPos);
        bRes = TRUE;
        goto RET;
     }
 RET:
     FS_UnlockThread();
     return bRes;
}
U8 FS_FileOpen(const FileEntry *pFileEntry, EN_OPEN_MODE u8OpenMode)
{
   U8 u8HandleNo;
   U8 res = INVALID_FILE_HANDLE;

   FS_LockThread();
   if(pFileEntry->FileSystemID>=MAX_ENV_CNT || IS_DRV_SLOT_USED(pFileEntry->FileSystemID) == 0)
        goto RET;
   u8HandleNo = GetFreeFDSlot();
   if(u8HandleNo == INVALID_FILE_HANDLE)
        goto RET;
   switch(u8OpenMode)
   {
   case  OPEN_MODE_FOR_READ:
   case  OPEN_MODE_BINARY_FOR_READ:
   case OPEN_MODE_FAST_FOR_READ:
        g_fileHandle[u8HandleNo].fd = open(pFileEntry->fullname, O_RDONLY);
        break;
   case OPEN_MODE_FOR_READ_WRITE:
   case OPEN_MODE_BINARY_FOR_READ_WRITE:
         g_fileHandle[u8HandleNo].fd = open(pFileEntry->fullname, O_RDWR);
        break;
   case OPEN_MODE_EMPTY_FOR_WRITE:
   case OPEN_MODE_BINARY_EMPTY_FOR_WRITE:
     g_fileHandle[u8HandleNo].fd = open(pFileEntry->fullname,  O_WRONLY| O_TRUNC);
     break;
   case  OPEN_MODE_EMPTY_FOR_READ_WRITE:
   case OPEN_MODE_BINARY_EMPTY_FOR_READ_WRITE:
     g_fileHandle[u8HandleNo].fd = open(pFileEntry->fullname,  O_RDWR| O_TRUNC);
     break;
    case OPEN_MODE_FOR_APPEND:
    case OPEN_MODE_BINARY_FOR_APPEND:
    case OPEN_MODE_FOR_READ_APPEND:
    g_fileHandle[u8HandleNo].fd = open(pFileEntry->fullname,  O_RDWR| O_APPEND);
     break;
    default:
         goto RET;
    }
   if(g_fileHandle[u8HandleNo].fd != -1)
   {
        g_fileHandle[u8HandleNo].drvID = pFileEntry->FileSystemID;
        strcpy(g_fileHandle[u8HandleNo].fullPathName, pFileEntry->fullname);
        SET_FD_SLOT_USED(u8HandleNo);
        res =  u8HandleNo;
   }

 RET:
     FS_UnlockThread();
     return res;
}
EN_FILE_CLOSE_RESULT FS_FileClose(U8 u8FileHandle)
{
    FS_LockThread();
    if(u8FileHandle>=MAX_FILEHANDLE_CNT || IS_FD_SLOT_USED(u8FileHandle)==0
        || g_fileHandle[u8FileHandle].fd==-1)
   {
        FS_UnlockThread();
        return FILE_CLOSE_RESULT_CLOSED_ALREADY;
   }

    CLR_FD_SLOT_USED(u8FileHandle);
    close(g_fileHandle[u8FileHandle].fd);
    g_fileHandle[u8FileHandle].fd = -1;
    FS_UnlockThread();
    return FILE_CLOSE_RESULT_SUCCESS;
}
U32 FS_FileWrite(U8 u8HandleNo, void* pu32Buffer, U32 u32Length)
{
    int wrCnt;
    FS_LockThread();
    if(u8HandleNo>=MAX_FILEHANDLE_CNT || IS_FD_SLOT_USED(u8HandleNo)==0
        || g_fileHandle[u8HandleNo].fd==-1)
    {
           FS_UnlockThread();
           return u32Length;
    }
   wrCnt =  write(g_fileHandle[u8HandleNo].fd, pu32Buffer, u32Length);
   FS_UnlockThread();
   if(wrCnt < 0)
       return u32Length;
   return u32Length-wrCnt;
}
U32 FS_FileRead(U8 u8HandleNo, void* pu32Buffer, U32 u32Length)
{
    int rdCnt;
    FS_LockThread();
    if(u8HandleNo>=MAX_FILEHANDLE_CNT || IS_FD_SLOT_USED(u8HandleNo)==0
        || g_fileHandle[u8HandleNo].fd==-1)
    {
        FS_UnlockThread();
        return u32Length;
    }
   rdCnt =  read(g_fileHandle[u8HandleNo].fd, pu32Buffer, u32Length);
   FS_UnlockThread();
   if(rdCnt < 0)
       return u32Length;
   return u32Length-rdCnt;
}
BOOL FS_FileSeek(U8 u8HandleNo, LongLong seekOffset, EN_FILE_SEEK_OPTION option)
{
    off_t seekOff;
    off_t offset;

    if (sizeof(off_t) > 4)
        offset = ((off_t)seekOffset.Hi << 32) + seekOffset.Lo;
    else
        offset = seekOffset.Lo;

    FS_LockThread();
    if(u8HandleNo>=MAX_FILEHANDLE_CNT || IS_FD_SLOT_USED(u8HandleNo)==0
        || g_fileHandle[u8HandleNo].fd==-1)
   {
        FS_UnlockThread();
        return FALSE;
   }
   switch(option)
   {
    case FILE_SEEK_SET:
       seekOff =  lseek(g_fileHandle[u8HandleNo].fd, offset, SEEK_SET);
       break;
    case FILE_SEEK_CUR:
       seekOff =  lseek(g_fileHandle[u8HandleNo].fd, offset, SEEK_CUR);
       break;
    default:
        FS_UnlockThread();
        return FALSE;
    }
   FS_UnlockThread();
   return (seekOff>=0)?TRUE:FALSE;
}
BOOL FS_TellFile(U8 u8HandleNo,  LongLong *pRetLongLong)
{
   off_t seekoff;
   FS_LockThread();
    if(u8HandleNo>=MAX_FILEHANDLE_CNT || IS_FD_SLOT_USED(u8HandleNo)==0
        || g_fileHandle[u8HandleNo].fd==-1)
    {
        FS_UnlockThread();
        return FALSE;
    }
   seekoff =  lseek(g_fileHandle[u8HandleNo].fd, 0, SEEK_CUR);
   FS_UnlockThread();
   if(seekoff <0)
       return FALSE;

    pRetLongLong->Hi = ((seekoff >> 32) & 0xFFFFFFFF);
    pRetLongLong->Lo = ((seekoff) & 0xFFFFFFFF);

   return TRUE;
}
BOOL FS_FileLength(U8 u8HandleNo, LongLong *pRetLongLong)
{
    struct stat statbuf;
    FS_LockThread();
    if(u8HandleNo>=MAX_FILEHANDLE_CNT || IS_FD_SLOT_USED(u8HandleNo)==0
        || g_fileHandle[u8HandleNo].fd==-1)
     {
        FS_UnlockThread();
        return FALSE;
     }

   if(stat(g_fileHandle[u8HandleNo].fullPathName, &statbuf) < 0)
   {
            WPFS_DBG("Failed to stat %s,return FALSE\n", g_fileHandle[u8HandleNo].fullPathName);
            FS_UnlockThread();
            return FALSE;
   }

    pRetLongLong->Hi = ((statbuf.st_size >> 32) & 0xFFFFFFFF);
    pRetLongLong->Lo = ((statbuf.st_size) & 0xFFFFFFFF);

   FS_UnlockThread();
   return TRUE;
}
U8 FS_CreateFile(const FILE_CREATE_PARAM *pParam)
{
   const char *pEnvCurDir;
   char fullname[MAX_PATH_NAME_LEN];
   U8 u8HandleNo = INVALID_FILE_HANDLE;

   FS_LockThread();
   pEnvCurDir = FS_GetEnvCurrentDir(pParam->u8EnvID);
   if(pEnvCurDir == NULL)
       goto RET;

   u8HandleNo = GetFreeFDSlot();
   if(u8HandleNo == INVALID_FILE_HANDLE)
       goto RET;
   sprintf(fullname, "%s/%s", pEnvCurDir, pParam->filename);
   g_fileHandle[u8HandleNo].fd = open(fullname,  O_WRONLY| O_CREAT);
   if(g_fileHandle[u8HandleNo].fd != -1)
    {
        g_fileHandle[u8HandleNo].drvID = FS_GetDrvID(pParam->u8EnvID);
        strcpy(g_fileHandle[u8HandleNo].fullPathName, fullname);
        SET_FD_SLOT_USED(u8HandleNo);
    }
   else
      u8HandleNo = INVALID_FILE_HANDLE ;
RET:
   FS_UnlockThread();
   return u8HandleNo;
}
BOOL FS_FileDelete(const FileEntry *pFileEntry)
{
    if(unlink(pFileEntry->fullname)<0)
         return FALSE;
    else
        return TRUE;
}

BOOL FS_CreateDirectory(const FILE_CREATE_PARAM *pParam)
{

   const char *pEnvCurDir;
   char fullname[MAX_PATH_NAME_LEN];

   pEnvCurDir = FS_GetEnvCurrentDir(pParam->u8EnvID);
   if(pEnvCurDir == NULL)
       return INVALID_FILE_HANDLE;

   sprintf(fullname, "%s/%s/", pEnvCurDir, pParam->filename);

  if(mkdir(fullname, 0777) < 0)
    return FALSE;
  return TRUE;
}
BOOL FS_DeleteDirectory(const FileEntry *pFileEntry)
{
    if(rmdir(pFileEntry->fullname)<0)
         return FALSE;
    else
        return TRUE;
}

BOOL FS_GetUSBPortStatus(USB_PORT_STATUS *pUSBPortStatus)
{
    memcpy(pUSBPortStatus, &g_usbConnectStatus, sizeof(USB_PORT_STATUS));
    return TRUE;
}
BOOL FS_GetDriveInfo(U8 u8DrvID, DRIVE_INFO *pDriveInfo, BOOL bCalculateDiskSpace)
{
     struct statfs s;



     //printf(" driver %d %d\n", u8DrvID, IS_DRV_SLOT_USED(u8DrvID));

     if(u8DrvID >= MAX_DRV_COUNT)
        return FALSE;
     if(IS_DRV_SLOT_USED(u8DrvID) == 0)
        return FALSE;
    if(bCalculateDiskSpace)
    {
        if (statfs(g_drvInfo[u8DrvID].mountpoint, &s) != 0)
        {
          WPFS_DBG("Failed to statfs %s\n", g_drvInfo[u8DrvID].mountpoint);
          return FALSE;
        }
        g_drvInfo[u8DrvID].totalSpaceInKB = s.f_blocks;
        g_drvInfo[u8DrvID].freeSpaceInKB = s.f_bfree;
   }
   memcpy(pDriveInfo, &g_drvInfo[u8DrvID], sizeof(DRIVE_INFO));
   return TRUE;
}

// Let other module to query real file descriptor.
S32 FS_QueryFd(U8 u8FileHandle)
{
    if(u8FileHandle>=MAX_FILEHANDLE_CNT || IS_FD_SLOT_USED(u8FileHandle)==0
        || g_fileHandle[u8FileHandle].fd==-1)
        return -1;

    return g_fileHandle[u8FileHandle].fd;
}

extern bool N51FS_DBUS_ReceiveMsg(unsigned char * pu8Msg, unsigned short u16DataSize, unsigned char * pu8OutData, unsigned short u16OutDataSize)
{
    U16 drvId;
    MNT_INFO mntInfo;
    if(u16DataSize < 1)
    {
         return FALSE;
    }
    if(u16OutDataSize < sizeof(MNT_INFO))
    {
         return FALSE;
    }

    switch (pu8Msg[0])
    {
        case E_OBAMA_FS_GET_FIRST_DRV_INFO:
            FS_LockThread();
            for( drvId=0; drvId<MAX_DRV_COUNT; drvId++)
            {
                       if(IS_DRV_SLOT_USED(drvId))
                            break;
            }
            if(drvId >= MAX_DRV_COUNT)
            {
                  memset(&mntInfo, 0, sizeof(MNT_INFO));
                  mntInfo.drvId = 0xFF;//invalid
            }
            else
            {
                  mntInfo.drvId = drvId;
                  mntInfo.fsType = g_drvInfo[drvId].fsType;
                  mntInfo.mountMode = g_drvInfo[drvId].mountMode;
                  mntInfo.portNO = g_drvInfo[drvId].portNO;

                  strcpy(mntInfo.devName, g_drvInfo[drvId].devName);
                  strcpy(mntInfo.mountpoint, g_drvInfo[drvId].mountpoint);
            }
            FS_UnlockThread();
            memcpy(pu8OutData, &mntInfo, sizeof(MNT_INFO));
            return TRUE;
            break;
        case E_OBAMA_FS_GET_NEXT_DRV_INFO:
            if(u16DataSize < 2)
            {
                   return FALSE;
            }
            FS_LockThread();
            for( drvId=pu8Msg[1]+1; drvId<MAX_DRV_COUNT; drvId++)
            {
                  if(IS_DRV_SLOT_USED(drvId))
                       break;
            }
            if(drvId >= MAX_DRV_COUNT)
            {
                  memset(&mntInfo, 0, sizeof(MNT_INFO));
                  mntInfo.drvId = 0xFF;//invalid
            }
            else
            {
                  mntInfo.drvId = drvId;
                  mntInfo.fsType = g_drvInfo[drvId].fsType;
                  mntInfo.mountMode = g_drvInfo[drvId].mountMode;
                  mntInfo.portNO = g_drvInfo[drvId].portNO;

                  strcpy(mntInfo.devName, g_drvInfo[drvId].devName);
                  strcpy(mntInfo.mountpoint, g_drvInfo[drvId].mountpoint);
            }
            FS_UnlockThread();
            memcpy(pu8OutData, &mntInfo, sizeof(MNT_INFO));
            return TRUE;
            break;
    }
    return FALSE;
}


