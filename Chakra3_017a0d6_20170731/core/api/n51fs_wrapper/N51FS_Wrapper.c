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
#include <unistd.h>

#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"

#include "datatype.h"
#include "debug.h"
#include "Board.h"
#include "sysinfo.h"
#include "drvCPU.h"
#include "msAPI_MailBox.h"
#include "MsTypes.h"
#include "drvBDMA.h"
#include "N51FS_Wrapper.h"
#include "msAPI_Timer.h"
#include "linux_51fs_wrap.h"
#include "linux_usb_mount.h"
#include "madp.h"
#include "stream.h"

#define TRACE_WFPS() do{printf("%s\n", __FUNCTION__);}while(0)

#define FIFO_PIPE_NAME "/subsystem/pipe_Xjys"

static USB_PORT_STATUS g_usbStatus;
//static U8 g_deviceStatus[MAX_DEVICE_CNT];
static BOOLEAN g_bPortChanged[MSD_PORT_NUM];
static char g_strTmpPathName[MAX_PATH_NAME_LEN];
static FS_EnvironmentStruct g_environment_list[MAX_ENV_CNT];
const char *NormalizePathName(const char *pDirPath);
static int g_fifo_fd = -1;
static bool bFSInited = false;

BOOL IsDescendant(const char *pStrAncestor, const char *curentDir);
const char *GetParentDirectory(const char *pStrPath);
int recursive_dev_folder(char *fileName, unsigned depth, unsigned maxdepth);

#define IS_StoragePartiton(devname) (strlen(devname)>=3 &&  \
                 ((devname[0]=='s' &&   devname[1]=='d' && (devname[2]>='a' && devname[2]<='p')) || \
                 (devname[0]=='s' &&   devname[1]=='r' && (devname[2]>='0' && devname[2]<='4'))) )


#define HD_MAGIC_NUMBER 0x55AAA55A
#define MAX_MESSAGE_STRING_LEN 256
#define MAX_MESSAGE_LEN (MAX_MESSAGE_STRING_LEN+sizeof(PIPE_MSG_HEADER))

#define ACTION_ADD 0x0001
#define ACTION_DELETE  0x0002

typedef struct _PIPE_MSG_HEADER
{
  U32 magic_number;
  U16 action;
  U16 stringLen;
}PIPE_MSG_HEADER;


long UNI_2_UTF8(U8 *pDest, const U16*pSrc, long destLen, long sourceLen);
long UTF8_2_UNI(U16 *pDest, const U8 *pSrc, long destLen);
void *N51FS_Wrapper_MultiTask(void *ctx);

//msg channel callback function
extern bool N51FS_DBUS_ReceiveMsg(unsigned char * pu8Msg, unsigned short u16DataSize, unsigned char * pu8OutData, unsigned short u16OutDataSize);

void msAPI_FS_Init(void)
{
    int i;
    pthread_t monThread;
    FILE * fpdev;
    char *devtypefname = "proc/bus/usb/devices";
    int maxdepth[2] = {0,0};
    char linebuf[256];
    char hotpoint[64];
    char *hotloc;
    char hotnum[8];
    int nLev = 0;
    STREAM_HANDLE handle;
    int readLen;

    
    if(bFSInited == true)
        return;
    unlink(FIFO_PIPE_NAME);
    mkfifo(FIFO_PIPE_NAME, 0666);


    g_fifo_fd = open(FIFO_PIPE_NAME, O_RDONLY| O_NONBLOCK);

    if (g_fifo_fd == -1) {
        WPFS_DBG("Serious error currented, can not open named pipe %s for read.\n",
                FIFO_PIPE_NAME);
    }

    FS_Stub_Init();

    memset(&g_usbStatus, 0, sizeof(USB_PORT_STATUS));
    memset(&g_bPortChanged, 0, sizeof(g_bPortChanged));
    for(i = 0; i<MAX_ENV_CNT; i++)
    {
       g_environment_list[i].u8CurrentDirectoryIndex = 0xFF;
       g_environment_list[i].u8DeviceIndex = 0xFF;
       g_environment_list[i].u8FileSystemID = 0xFF;
       g_environment_list[i].u8FileSystemType = FILE_SYSTEM_TYPE_NONE;
       g_environment_list[i].bIsInit = FALSE;
    }

    msAPI_FCtrl_Init();
    MAdp_MSGCH_Init();
    MAdp_MSGCH_SetCallBack(MAdp_MSGCH_GetChannelIndex("FS_MOUNT_STATUS"), N51FS_DBUS_ReceiveMsg);
    pthread_create( &monThread, NULL, N51FS_Wrapper_MultiTask, (void*) "hogplug monitor");

    fpdev = fopen(devtypefname, "r");
    if(fpdev == NULL)
    {
        printf("failed to open /proc/bus/usb/devices\n");
        //complete = 0;
    }
    else
    {
        if((handle=Init_streamFile(fpdev)) == INVALID_STREAM_HANDLE)
        {
            printf("Failed to read file /proc/bus/usb/device!\n");
        }
        else
        {
            while(!IsStreamEnd(handle))
            {
                readLen = GetOneLine(handle, linebuf, 256);
                if(readLen)
                {
                    sprintf(hotpoint,"Lev=");//Check lev No
                    if((hotloc = strstr(linebuf, hotpoint)) != NULL)
                    {
                        hotloc += 4;
                        memset(hotnum,0,8);
                        strncpy(hotnum, hotloc, 3);
                        nLev = atoi(hotnum);

                        sprintf(hotpoint,"Bus=02");//Check Bus No
                        if((hotloc = strstr(linebuf, hotpoint)) != NULL)
                        {
                            if(nLev > maxdepth[0])
                                maxdepth[0] = nLev;
                        }
                        else
                        {
                            if(nLev > maxdepth[1])
                                maxdepth[1] = nLev;
                        }
                        
                    }
                }
            }
        }
        fclose(fpdev);
    }
    
    recursive_dev_folder("/sys/devices/platform/Mstar-ehci-1.0/usb2", 0, maxdepth[0]+8);
    recursive_dev_folder("/sys/devices/platform/Mstar-ehci-2.1/usb1", 0, maxdepth[1]+8);
    bFSInited = true;

}
void msAPI_FCtrl_Init(void)
{
}
BOOL BuildEnvironmentStruct(U8 u8EnvID, U8 u8DriveNo)
{
    MSDCtrl_Drive driveInfo;
    if(MAX_ENV_CNT <= u8EnvID)
    {
       WPFS_DBG("Fatal error, envid %d >= %d\n", u8EnvID, MAX_ENV_CNT);
        WPFS_ASSERT(0);
        return FALSE;
    }
    if( FALSE == msAPI_FCtrl_GetDriveByIndex(u8DriveNo, &driveInfo))
        return FALSE;
    g_environment_list[u8EnvID].u8CurrentDirectoryIndex = 0xFF;
    g_environment_list[u8EnvID].u8DeviceIndex = driveInfo.DeviceIndex;
    g_environment_list[u8EnvID].u8FileSystemID = driveInfo.DriveIndex;
    g_environment_list[u8EnvID].u8FileSystemType = driveInfo.FileSystemType;
    g_environment_list[u8EnvID].bIsInit = TRUE;
    return TRUE;
}
void DestroyEnvironmentStruct(U8 u8EnvID)
{
    if(MAX_ENV_CNT <= u8EnvID)
    {
       WPFS_DBG("Fatal error, envid %d >= %d\n", u8EnvID, MAX_ENV_CNT);
        WPFS_ASSERT(0);
        return;
    }
    g_environment_list[u8EnvID].u8CurrentDirectoryIndex = 0xFF;
    g_environment_list[u8EnvID].u8DeviceIndex = 0xFF;
    g_environment_list[u8EnvID].u8FileSystemID =0xFF;
    g_environment_list[u8EnvID].u8FileSystemType = FILE_SYSTEM_TYPE_NONE;
    g_environment_list[u8EnvID].bIsInit = FALSE;
}

U8 msAPI_FSEnv_Register(U8 u8DriveNo)
{
   U8 envID;
   envID = FS_CreateEnv(u8DriveNo);

   if(INVALID_FS_ENVIRONMENT_INDEX == envID)
   {
       return INVALID_FS_ENVIRONMENT_INDEX;
   }
   if(FALSE == BuildEnvironmentStruct(envID, u8DriveNo))
   {
        FS_DestroyEnv(envID);
        return INVALID_FS_ENVIRONMENT_INDEX;
   }
   return envID;
}
void msAPI_FSEnv_UnRegister(U8 u8HandleNo)
{
     FS_DestroyEnv(u8HandleNo);
     DestroyEnvironmentStruct(u8HandleNo);
}
/***************************************************************************************/
/// Change the given environment ID's Current Directory to Root.
/// @param -environmentID \b IN: Environment ID.
/// @return -Success or fail.
/***************************************************************************************/
BOOLEAN msAPI_FCtrl_DirectoryChangeToRoot(U8 environmentID)
{

       U8 U8DrvID = FS_GetDrvID(environmentID);
       const char *pStrMNTPoint;

       if(U8DrvID != INVALID_DRV_ID)
       {
               pStrMNTPoint = FS_GetMountPoint(U8DrvID);
       }
       else
       {
               pStrMNTPoint = NULL;
       }

       if(pStrMNTPoint == NULL)
             return FALSE;

       if(FS_SetEnvCurrentDir(environmentID, pStrMNTPoint))
             return TRUE;
       return FALSE;
}

/***************************************************************************************/
/// Change directory to the given directory name.
/// @param -ps8DirName \b IN: Directory name.
/// @return -Success or fail.
/***************************************************************************************/
BOOLEAN msAPI_FCtrl_DirectoryChange(U8 enId,FileEntry* pFileEntry)
{
       U8 U8DrvID = FS_GetDrvID(enId);
       const char *pStrMNTPoint;
       const char *pDstPathName;

       if(U8DrvID != INVALID_DRV_ID)
       {
                 pStrMNTPoint = FS_GetMountPoint(U8DrvID);
        }
        else
        {
                 pStrMNTPoint = NULL;
        }
        if(pStrMNTPoint == NULL || pFileEntry==NULL)
              return FALSE;


        pDstPathName = pFileEntry->fullname;
        pDstPathName = NormalizePathName(pDstPathName);
        if(pDstPathName &&
                                        (IsDescendant(pStrMNTPoint, pDstPathName)||strcmp(pStrMNTPoint, pDstPathName)==0))
       {

                if(FS_SetEnvCurrentDir(enId, pDstPathName))
                        return TRUE;
        }
        return FALSE;
}

BOOLEAN msAPI_FCtrl_EntryFirst(U8 enId)
{

        if(FS_EntryFirst(enId))
         {
               return TRUE;
         }
         else
         {
               return FALSE;
         }

}

BOOLEAN msAPI_FCtrl_DirectoryChangeToContained(U8 enId,FileEntry* pFileEntry)
{

       U8 U8DrvID = FS_GetDrvID(enId);
       const char *pStrMNTPoint;
       const char *pDstPathName;

       if(pFileEntry == NULL)
           return FALSE;

       if(U8DrvID != INVALID_DRV_ID)
       {
             pStrMNTPoint = FS_GetMountPoint(U8DrvID);
       }
       else
       {
            return FALSE;
       }

       pDstPathName =  NormalizePathName(pFileEntry->fullname);
       pDstPathName = GetParentDirectory(pDstPathName);


       if(pDstPathName &&
                                        (IsDescendant(pStrMNTPoint, pDstPathName)||strcmp(pStrMNTPoint, pDstPathName)==0))
       {

                if(FS_SetEnvCurrentDir(enId, pDstPathName))
                         return TRUE;
      }

      return FALSE;
}

BOOLEAN msAPI_FCtrl_DirectoryGetDOTDOT(U8 environmentId,FileEntry* pFileToSet)
{
      if(FS_GetRelativeDirEntry(environmentId, pFileToSet, TRUE))
           return TRUE;
      return FALSE;

}

BOOLEAN msAPI_FCtrl_DirectoryGetDOT(U8 environmentId,FileEntry* pFileToSet)
{
      if(FS_GetRelativeDirEntry(environmentId, pFileToSet, FALSE))
           return TRUE;
      return FALSE;
}

/***************************************************************************************/
/// Check if the current directory is root directory or not.
/// @param -environmentId \b IN: Environment ID.
/// @return -Success or fail.
/***************************************************************************************/
BOOLEAN msAPI_FCtrl_DirectoryIsCurrentRoot(U8 environmentId)
{
       const char *curEnvDir = FS_GetEnvCurrentDir(environmentId);
       const char *mountPoint = FS_GetMountPoint(FS_GetDrvID(environmentId));

        if(curEnvDir && mountPoint && strcmp(curEnvDir, mountPoint)==0)
             return TRUE;
        return FALSE;
}

EN_ENTRY_NEXT_RESULT msAPI_FCtrl_EntryNext(U8 enId, FileEntry* pFileToSet)
{
    return FS_EntryNext(enId, pFileToSet);
}

BOOLEAN msAPI_FCtrl_FileSeek(U8 u8HandleNo, U32 u32Length, EN_FILE_SEEK_OPTION option)
{
    LongLong offset;
    offset.Hi = 0;
    offset.Lo = u32Length;
    return FS_FileSeek(u8HandleNo, offset, option);
}

BOOLEAN msAPI_FCtrl_FileSeek_LongLong(U8 u8HandleNo, LongLong u32Length, EN_FILE_SEEK_OPTION option)
{
    return FS_FileSeek(u8HandleNo, u32Length, option);
}

U32 msAPI_FCtrl_FileTell(U8 u8HandleNo)
{
    LongLong tellLength;
    if (FS_TellFile(u8HandleNo, &tellLength))
        return tellLength.Lo;
    else
        return 0xFFFFFFFF;
}

LongLong msAPI_FCtrl_FileTell_LongLong(U8 u8HandleNo)
{
    LongLong tellLength;
    if (!FS_TellFile(u8HandleNo, &tellLength))
    {
        tellLength.Hi = 0xFFFFFFFF;
        tellLength.Lo = 0xFFFFFFFF;
    }
    return tellLength;
}

U32 msAPI_FCtrl_FileLength(U8 u8HandleNo)
{
    LongLong fileLength;
    if(FS_FileLength(u8HandleNo, &fileLength))
        return fileLength.Lo;
    else
        return 0;
}

LongLong msAPI_FCtrl_FileLength_LongLong(U8 u8HandleNo)
{
    LongLong fileLength;
    if (!FS_FileLength(u8HandleNo, &fileLength))
    {
        fileLength.Hi = 0;
        fileLength.Lo = 0;
    }
    return fileLength;
}

U8 msAPI_FCtrl_FileOpen(FileEntry* pFileEntry, U8 u8OpenMode)
{
    return FS_FileOpen(pFileEntry, (EN_OPEN_MODE)u8OpenMode);
}
EN_FILE_CLOSE_RESULT msAPI_FCtrl_FileClose(U8 u8HandleNo)
{
     EN_FILE_CLOSE_RESULT res;
     res =  FS_FileClose(u8HandleNo);
     sync();
     return res;
}

U32 msAPI_FCtrl_FileRead(U8 u8HandleNo, U32 u32Buffer, U32 u32Length)
{
    return  FS_FileRead(u8HandleNo, (void*)_PA2VA(u32Buffer), u32Length);
}

U32 msAPI_FCtrl_FileWrite(U8 u8HandleNo, U32 u32Buffer, U32 u32Length)
{
      return  FS_FileWrite(u8HandleNo, (void*)_PA2VA(u32Buffer), u32Length);
}

U8 msAPI_FCtrl_FileCreate(U8 u8enid,U16 *pu16LongName,U8 charLen,EN_CREATE_MODE createMode)
{
     FILE_CREATE_PARAM createParam;
     long destlen;

     destlen =  UNI_2_UTF8( (U8*)createParam.filename, pu16LongName, 256,  (long)charLen);
     if(destlen > 0)
     {
         createParam.filename[destlen] = 0;
         createParam.fileNameLength = destlen;
         createParam.createmode = createMode;
         createParam.u8EnvID = u8enid;
         return FS_CreateFile(&createParam);
     }
     else
        return INVALID_FILE_HANDLE;

}
BOOLEAN msAPI_FCtrl_DirectoryCreate(U8 u8enid, U16 *pu16LongName, U8 charLen)
{
     FILE_CREATE_PARAM createParam;
     long destlen;

     destlen =  UNI_2_UTF8( (U8*)createParam.filename, pu16LongName, 256,  charLen);
     if(destlen > 0)
     {
         createParam.filename[destlen] = 0;
         createParam.fileNameLength = destlen;
         createParam.u8EnvID = u8enid;

         if(FS_CreateDirectory(&createParam))
             return TRUE;
         return FALSE;
     }
     else
        return FALSE;
}
const char *GetEntryDname(const char *pFullName)
{
   int len = strlen(pFullName);
   int len1;

   if(len >= MAX_PATH_NAME_LEN||len<=1)
       return NULL;

   if(pFullName[len-1] == '/')
       len--;
   len1 = len;
   while(len && pFullName[len-1] != '/')
    {
       len--;
    }

   memcpy(g_strTmpPathName, pFullName+len, len1-len);
   g_strTmpPathName[len1-len] = 0;

   return g_strTmpPathName;
}
U8 msAPI_FCtrl_EntryGetLongNameByFileEntry(U8 enId, FileEntry *entry, U32 MIUAddr, U8 charLen, BOOLEAN* pbShortNameOnly)
{
    UNUSED(enId);

    const U8 *pDname = (const U8 *)GetEntryDname(entry->fullname);
    long retlen;

    if(entry->EntryAttrib & ENTRY_ATTRIB_DIRECTORY)
    {
        if(ENTRY_TYPE_DIR_DOT == entry->EntryType)
        {
            ((U16*)MIUAddr)[0] = '.';
            return 1;
        }
        else if(ENTRY_TYPE_DIR_DOTDOT == entry->EntryType)
        {
            ((U16*)MIUAddr)[0] = '.';
            ((U16*)MIUAddr)[1] = '.';
            return 2;
        }
    }

    if(pDname == NULL)
        return 0;

    retlen = UTF8_2_UNI((U16*)MIUAddr, pDname, (long)charLen);
    if(retlen <= 0)
        return 0;
    *pbShortNameOnly = FALSE;
    return (U8)retlen;
}

U32 msAPI_FCtrl_GetUnusedSizeInKB_ByDriveIndex(U8 u8DriveIndex)
{
    DRIVE_INFO drvInfo;

    if(FS_GetDriveInfo(u8DriveIndex, &drvInfo, TRUE))
          return drvInfo.freeSpaceInKB;
    return 0;
}
U32 msAPI_FCtrl_GetTotalSizeInKB_ByDriveIndex(U8 u8DriveIndex)
{
    DRIVE_INFO drvInfo;

    if(FS_GetDriveInfo(u8DriveIndex, &drvInfo, TRUE))
          return drvInfo.totalSpaceInKB;
    return 0;
}
BOOLEAN msAPI_FCtrl_GetDriveByIndex(U8 driveID,MSDCtrl_Drive* pDrive)
{
    DRIVE_INFO drvInfo;
   //TRACE_WFPS();
   if(!FS_GetDriveInfo(driveID, &drvInfo, TRUE))
    {
       //   WPFS_DBG("get drive %d failed \n", driveID);
          return FALSE;
    }

    pDrive->DeviceIndex = drvInfo.deviceID;
    pDrive->DriveIndex = driveID;
    pDrive->FileSystemType = drvInfo.fsType;
    pDrive->LBA = 0;
    pDrive->PartitionNo = 0;

    return TRUE;

}

U8 msAPI_FCtrl_FileDelete(FileEntry* pFileEntry)
{
   if(FS_FileDelete(pFileEntry))
       return TRUE;
   return FALSE;
}
BOOLEAN msAPI_FCtrl_EntrySearchByName(U8 u8EnId,U16 *pu16FileNameToFind,U8 u8FileNameToFindLen ,FileEntry *pEntryToSet)
{
    BOOLEAN bIsFound = FALSE;

    U16 u16FileName[256];


    msAPI_FCtrl_EntryFirst(u8EnId);


    while(1)
    {
        U8 u8Count = 0;
        U8 len=0;
        BOOL bShortNameOnly;
        FileEntry stFileEntry;
        if(msAPI_FCtrl_EntryNext(u8EnId, &stFileEntry) != ENTRY_NEXT_RESULT_SUCCESS)
            break;


       // len = msAPI_FCtrl_EntryGetCurrentName(u8EnId, (U32)pu16FileName, 255);
       len = (U8)msAPI_FCtrl_EntryGetLongNameByFileEntry(u8EnId, &stFileEntry, (U32)u16FileName, 255, &bShortNameOnly);

        len=len>u8FileNameToFindLen?u8FileNameToFindLen:len;

        if(len!=u8FileNameToFindLen)
        {
            continue;
        }

        while(u8Count < len)
        {
            if( ((U8 *)pu16FileNameToFind)[u8Count*2] != ((U8 *)u16FileName)[u8Count*2] ||
                ((U8 *)pu16FileNameToFind)[u8Count*2+1] != ((U8 *)u16FileName)[u8Count*2+1] )
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


    return bIsFound;
}

void msAPI_FCtrl_FileHandleResetAll()
{
      FS_ResetAllFileHandle();
}

BOOL MSDCtrl_Flush_USB_Status(void)
{
    int i;
    USB_PORT_STATUS  usbStatus;


    if(!FS_GetUSBPortStatus(&usbStatus))
        return FALSE;


    for( i=0; i<MSD_PORT_NUM; i++)
    {
         if((g_usbStatus.port_connect_status^usbStatus.port_connect_status) & (1<<i))
          {
                 WPFS_DBG("USB port %d changed \n", i);
              //   g_deviceStatus[i] = ((usbStatus.port_connect_status) & (1<<i))?
                //                                                        MSD_STATUS_IDLE:MSD_STATUS_EMPTY;
                 g_bPortChanged[i] = TRUE;
          }
    }
    memcpy(&g_usbStatus, &usbStatus, sizeof(g_usbStatus));
    return FALSE;
}
EN_MSD_STATUS msAPI_MSDCtrl_GetDeviceStatus(U8 u8DeviceIndex)
{

   // MSDCtrl_Flush_USB_Status();

    if(MAX_DEVICE_CNT <= u8DeviceIndex)
    {
        WPFS_DBG("Invalid Parameter\n");
        WPFS_ASSERT(0);
        return MSD_STATUS_ERROR;
    }
 // printf("return device %d status %d\n", u8DeviceIndex, g_deviceStatus[u8DeviceIndex]);
    return (EN_MSD_STATUS)g_usbStatus.deviceStatus[u8DeviceIndex];

}

BOOLEAN msAPI_FCtrl_ActiveDevice(U8 deviceIndex)
{
   UNUSED(deviceIndex);
   //TRACE_WFPS();
    if(MAX_DEVICE_CNT <= deviceIndex)
    {
        WPFS_DBG("Invalid Parameter\n");
        WPFS_ASSERT(0);
        return FALSE;
    }

   return TRUE;
}
U8 msAPI_FCtrl_GetDriveCount(void)
{
       long i;
       U8 count = 0;
       for( i=0; i<MSD_PORT_NUM; i++)
       {
            if(g_usbStatus.port_connect_status & (1<<i))
                count += (U8)g_usbStatus.driveNumber[i];
       }
       return count;
}
U8 msAPI_FCtrl_GetDriveCountByPort(U8 port)
{
       if(port >= MSD_PORT_NUM)
        {
          WPFS_DBG("Invalid parameter about port number %d\n", port);
          ASSERT(0);
          return 0;
        }
       return  (U8)g_usbStatus.driveNumber[port];
}
BOOLEAN msAPI_FCtrl_IsDriveMounted(U8 u8DriveId)
{
    MSDCtrl_Drive drive;
    return msAPI_FCtrl_GetDriveByIndex(u8DriveId, &drive);
}
BOOLEAN msAPI_MSDCtrl_IsPortChanged(EN_MSD_PORT port)
{
       if(port >= MSD_PORT_NUM)
        {
          WPFS_DBG("Invalid parameter about port number %d\n", port);
          ASSERT(0);
          return FALSE;
        }
      MSDCtrl_Flush_USB_Status();
      return g_bPortChanged[port];
}
void msAPI_MSDCtrl_CheckDevicesOnPort(EN_MSD_PORT port)
{
   UNUSED(port);
   MSDCtrl_Flush_USB_Status();
}
U32 msAPI_MSDCtrl_GetPortStatus(void)
{
    MSDCtrl_Flush_USB_Status();
    return g_usbStatus.port_connect_status;
}
BOOLEAN MDrv_UsbDeviceConnect(void)
{
    MSDCtrl_Flush_USB_Status();
    return g_usbStatus.port_connect_status & (1 << MSD_PORT_1);
}
BOOLEAN MDrv_UsbDeviceConnect_Port2(void)
{
    MSDCtrl_Flush_USB_Status();
    return g_usbStatus.port_connect_status & (1 << MSD_PORT_2 );
}
void msAPI_MSDCtrl_ResetDevicesOnPort(EN_MSD_PORT port)
{
     UNUSED(port);
     MSDCtrl_Flush_USB_Status();
     WPFS_DBG("msAPI_MSDCtrl_ResetDevicesOnPort is not implementedn");
}
BOOLEAN msAPI_MSDCtrl_IsDeviceConnected(EN_MSD_PORT port)
{
    if(MSD_PORT_NUM <= port)
    {
        ASSERT(0);
        return FALSE;
    }

    switch(port)
    {
        case MSD_PORT_1://USB 1
            return MDrv_UsbDeviceConnect();
#if ENABLE_USB_2
        case MSD_PORT_2://USB 2
            return MDrv_UsbDeviceConnect_Port2();
#endif
        default:
            return FALSE;
    }
}
BOOLEAN msAPI_MSDCtrl_IsPortOpened(EN_MSD_PORT port)
{
       if(MSD_PORT_NUM <= port)
        {
          WPFS_DBG("Invalid parameter about port number %d\n", port);
          ASSERT(0);
          return FALSE;
        }
       if(g_usbStatus.port_connect_status & (1<<port))
           return TRUE;
       return FALSE;
}
void msAPI_MSDCtrl_CheckDevices(void)
{
       //TRACE_WFPS();
       MSDCtrl_Flush_USB_Status();
}
EN_MSD_PORT msAPI_MSDCtrl_GetDevicePort(U8 deviceIndex)
{
      //TRACE_WFPS();
      ASSERT(MAX_DEVICE_CNT > deviceIndex);
    //  MSDCtrl_Flush_USB_Status();
      return (EN_MSD_PORT)g_usbStatus.devicePort[deviceIndex];

}
BOOLEAN msAPI_MSDCtrl_DevicesChangeStatusCheck(void)
{
       U32 i;

       //TRACE_WFPS();
       for( i=0; i<MSD_PORT_NUM; i++)
             g_bPortChanged[i] = FALSE;
       MSDCtrl_Flush_USB_Status();

       return TRUE;
}
void msAPI_MSDCtrl_ResetDevice(U8 deviceIndex)
{
     UNUSED(deviceIndex);
     //TRACE_WFPS();

     MSDCtrl_Flush_USB_Status();
     WPFS_DBG("msAPI_MSDCtrl_ResetDevice is not implemented  for MBFS\n");
}
void msAPI_MSDCtrl_ResetDevices(void)
{
   MSDCtrl_Flush_USB_Status();
   WPFS_DBG("msAPI_MSDCtrl_ResetDevices is not implemented for MBFS\n");
}

void msAPI_MSDCtrl_ResetPorts(void)
{
    return;
}

U8 msAPI_GetUsbDeviceStatus(void)
{
    U8 status = 0;
    U8 i;

    //TRACE_WFPS();

    MSDCtrl_Flush_USB_Status();

    for( i=0; i<MAX_DEVICE_CNT; i++)
         if(g_usbStatus.devicePort[i] == 1)
            status |= 1<<i;

    return status?g_usbStatus.usbPortStatus[1]:NO_DEVICE;
}
U8 msAPI_GetUsbDeviceStatusPort2(void)
{
    U8 status = 0;
    U8 i;

    //TRACE_WFPS();

    MSDCtrl_Flush_USB_Status();

    for( i=0; i<MAX_DEVICE_CNT; i++)
         if(g_usbStatus.devicePort[i] == 2)
            status |= 1<<i;

     return status?g_usbStatus.usbPortStatus[2]:NO_DEVICE;
}
U8 msAPI_MSDCtrl_GetTotalDeviceCount()
{
    ASSERT(STORAGE_DEVICE_NUM <= MAX_DEVICE_CNT);
    return STORAGE_DEVICE_NUM;
}
FS_EnvironmentStruct* msAPI_FSEnv_GetEnvironment(U8 u8EnvID)
{
    if(MAX_ENV_CNT <= u8EnvID)
    {
       WPFS_DBG("Fatal error, envid %d >= %d\n", u8EnvID, MAX_ENV_CNT);
        WPFS_ASSERT(0);
    }
    return  &g_environment_list[u8EnvID];
}
void msAPI_MSDCtrl_SetDeviceStatus(U8 u8DeviceIndex, EN_MSD_STATUS status)
{
    UNUSED(u8DeviceIndex);
    UNUSED(status);
    WPFS_DBG("msAPI_MSDCtrl_SetDeviceStatus is not implemented for MBFS\n");
}

long UTF8_2_UNI(U16 *pDest, const U8 *pSrc, long destLen)
{
   long i = 0;
   long size_d = 0;
   long size_s = strlen((const char*)pSrc);

   if (pSrc == NULL)
   {
      return -1;
   }
   while(pSrc[i])
   {
      U16 unicode;
       if((pSrc[i]&0x80) == 0)
       {
           unicode = (U16)pSrc[i+0];
           size_s--;
            i += 1;
       }
      else if((pSrc[i]&0xE0) == 0xC0)
      {  //two byte  110x-xxxx 10xx-xxxx
          if(size_s < 2)
             break;
          if((pSrc[i+1] &0xC0)!=0x80)
          {
                WPFS_DBG("Serious error when convert UTF-8 to unicode, unsync header code at %d\n", (int)i+1);
                return -1;
          }
          unicode =( (((U16)pSrc[i+0])&0x1F)<<6) | (pSrc[i+1]&0x3F);
          size_s -= 2;
           i += 2;
      }
      else if((pSrc[i]&0xF0) == 0xE0)
      {  //three byte  1110-xxxx 10xx-xxxx 10xx-xxxx
          if(size_s < 3)
             break;
          if((pSrc[i+1] &0xC0)!=0x80 || (pSrc[i+2] &0xC0)!=0x80)
          {
                WPFS_DBG("Serious error when convert UTF-8 to unicode, unsync header code at %d\n", (int)i+1);
                return -1;
          }
          unicode = ((((U16)pSrc[i+0])&0x0F)<<12) | ((((U16)pSrc[i+1])&0x3F)<<6) | (pSrc[i+2]&0x3F) ;
          size_s -= 3;
          i += 3;
      }
      else
      {
         WPFS_DBG("Serious error when convert UTF-8 to unicode, unsync header code at %d\n", (int)i);
         return -1;
      }

      if(pDest)
      {
         if(destLen)
            destLen--, *pDest = unicode, pDest++;
         else
            break;
      }

      size_d++;
   }

 return size_d;
}

long UNI_2_UTF8(U8 *pDest, const U16*pSrc, long destLen, long sourceLen)
{
   long i = 0;
   long size_d = 0;

   if (pSrc == NULL)
   {
      return -1;
   }
   while(i < sourceLen)
   {
       if(pSrc[i] < 0x80)
       {
           if(pDest)
           {
              if(destLen<1)
                  break;
              pDest[0] = (U8)pSrc[i];
              destLen--;
              pDest++;
           }
           size_d++;
       }
      else  if(pSrc[i] < 0x800)
      {  //two byte  110x-xxxx 10xx-xxxx
           if(pDest)
           {
              if(destLen<2)
                  break;
              pDest[0] = (U8)((pSrc[i]>>6)&0x1F)|0xC0;
              pDest[1] = (U8)(pSrc[i]&0x3F)|0x80;
              destLen -= 2;
              pDest += 2;
           }
           size_d += 2;
      }
      else
      {  //three byte  1110-xxxx 10xx-xxxx 10xx-xxxx
           if(pDest)
           {
              if(destLen<3)
                  break;
              pDest[0] = (U8)((pSrc[i]>>12)&0x0F)|0xE0;
              pDest[1] = (U8)((pSrc[i]>>6)&0x3F)|0x80;
              pDest[2] = (U8)(pSrc[i]&0x3F)|0x80;
              destLen -= 3;
              pDest += 3;
           }
           size_d += 3;
      }
      i++;
   }

   return size_d;
}

/******************************************************************************/
/// API for MIU Copy::
/// Memory Copy Interface
/// @param srcaddr \b IN Source address
/// @param dstaddr \b IN Destination address
/// @param len \b IN Size
/// @param type \b IN The Type of Memory copy
/******************************************************************************/
void msAPI_FS_MIU_Copy(U32 srcaddr, U32 dstaddr, U32 len)
{
    memcpy((void*)dstaddr, (void*)srcaddr, len);
}
#if 0
void FSRoutine_Test(void)
{
 //   static U8 u8Cmd = 0;
  U16 dirName[10] = {'s', 'u', 'n', 'm', 'y', '_', 't', 'e', 's', 't'};
  const char *teststring = "hi, ok, you can write file now, congratulation!\n";
  U16 testfile[7] = {0x5b59, 0x660e,  0x52c7, 0x002e,  0x0074,0x0078, 0x0074};
  char readbuf[256];
  U8 drvID;
  U8 u8FileHandle;
  FileEntry fileEntry, lstDirEntry;
  U32 writeLen;
  MSDCtrl_Drive MSDDrv;
  printf("Enter FSRoutine_Test\n");
  msAPI_GetUsbDeviceStatus();
  if(msAPI_MSDCtrl_GetDeviceStatus(0) == MSD_STATUS_IDLE)
       printf("BUS 2 connect");

  for( drvID=0; drvID<MAX_DRV_COUNT; drvID++)
    if(msAPI_FCtrl_GetDriveByIndex(drvID, &MSDDrv))
    {
       U8 u8EnvID;
       printf(" Drv %d mounted, format %d, freespace%d\n",drvID, MSDDrv.FileSystemType,
                           msAPI_FCtrl_GetUnusedSizeInKB_ByDriveIndex(drvID));

       u8EnvID = msAPI_FSEnv_Register(drvID);
       if(u8EnvID == INVALID_FS_ENVIRONMENT_INDEX)
       {
           printf(" Failed to regisiter env on Drv %d\n", drvID);
           continue;
       }
       if(msAPI_FCtrl_EntrySearchByName(u8EnvID, testfile, 7, &fileEntry))
        {
            U8 handle;
            int readLen;
            printf("Found my file\n");
            handle = msAPI_FCtrl_FileOpen(&fileEntry, OPEN_MODE_FOR_READ);
            if(handle == INVALID_FILE_HANDLE)
                printf("Failed to open my file\n");
            else
            {
                int tellLen = msAPI_FCtrl_FileLength(handle);
                readLen = msAPI_FCtrl_FileRead(handle, (U32)readbuf, 256);
                readbuf[256-readLen] = 0;
                printf("read from my file:%s, telllen=%d\n", readbuf, tellLen);
                printf("fseek to offset 24");
                if(msAPI_FCtrl_FileSeek(handle, 24, FILE_SEEK_SET) == FALSE)
                    printf("seek failed\n");
                tellLen = msAPI_FCtrl_FileTell(handle);
                readLen = msAPI_FCtrl_FileRead(handle, (U32)readbuf, 256);
                readbuf[256-readLen] = 0;
                printf("read after seek from my file:%s, tell pos=%d\n", readbuf, tellLen);

                msAPI_FCtrl_FileClose(handle);
            }
        }
       if(msAPI_FCtrl_DirectoryCreate(u8EnvID, dirName, 10) == FALSE)
       {
            printf(" Failed to create test directory \'sunmy_test\'\n");
       }
       if(msAPI_FCtrl_DirectoryGetDOT(u8EnvID, &lstDirEntry) == FALSE)
       {
            printf("failed to save lst directory\n");
            continue;
        }
        if(msAPI_FCtrl_EntrySearchByName(u8EnvID, dirName, 10, &fileEntry))
       {
           printf("Found sunmy\n");
           if(fileEntry.EntryType == ENTRY_TYPE_DIR)
           {
               if(msAPI_FCtrl_DirectoryChange(u8EnvID, &fileEntry) == TRUE)
               {
                   printf("change to sub folder sunmy\n");
               }
           }
       }
       u8FileHandle = msAPI_FCtrl_FileCreate(u8EnvID, testfile, 7, CREATE_MODE_NEW);
       if(u8FileHandle == INVALID_FILE_HANDLE)
       {
           printf(" Failed to create test file\n");
           msAPI_FSEnv_UnRegister(drvID);
           continue;
       }
       writeLen = msAPI_FCtrl_FileWrite(u8FileHandle, (U32)teststring, strlen(teststring));
       printf("finished write %d bytes\n", strlen(teststring)-writeLen);
       msAPI_FCtrl_FileClose(u8FileHandle);
#if 0
      // if(msAPI_FCtrl_DirectoryChangeToContained(u8EnvID, &fileEntry) == FALSE)
    //  if(msAPI_FCtrl_DirectoryChangeToRoot(u8EnvID) == FALSE)
       if(msAPI_FCtrl_DirectoryGetDOTDOT(u8EnvID, &fileEntry) == FALSE)
           printf("failed to get to root entry\n");
       else if(msAPI_FCtrl_DirectoryChange(u8EnvID, &fileEntry) == FALSE)
       {
                   printf("change to change to parent folder sunmy\n");
        }
  #else
       if(msAPI_FCtrl_DirectoryChange(u8EnvID, &lstDirEntry) == FALSE)
       {
                   printf("failed to restore last directory\n");
        }
  #endif

       u8FileHandle = msAPI_FCtrl_FileCreate(u8EnvID, testfile, 7, CREATE_MODE_NEW);
       if(u8FileHandle == INVALID_FILE_HANDLE)
       {
           printf("  Failed to create test file\n");
           msAPI_FSEnv_UnRegister(drvID);
           continue;
       }
       writeLen = msAPI_FCtrl_FileWrite(u8FileHandle, (U32)teststring, strlen(teststring));
       printf("finished write %d bytes\n", strlen(teststring)-writeLen);
       msAPI_FCtrl_FileClose(u8FileHandle);
       msAPI_FSEnv_UnRegister(u8EnvID);

    }
     printf("leave FSRoutine_Test\n");

}
#endif

const char *NormalizePathName(const char *pDirPath)
{
    const char *dname;

    if(pDirPath == NULL)
        return NULL;

    dname = GetEntryDname(pDirPath);

    if(dname == NULL)
        return NULL;

    if(IS_DIR_DOT(dname))
    {
         return GetParentDirectory(pDirPath);
    }
    else if(IS_DIR_DOTDOT(dname))
    {
         return GetParentDirectory(GetParentDirectory(pDirPath));
    }
    return pDirPath;
}

BOOL IsDescendant(const char *pStrAncestor, const char *curentDir)
{
   unsigned ancestorPathLen = strlen(pStrAncestor);

   if(ancestorPathLen >= strlen(curentDir))
      return FALSE;
   if(memcmp(pStrAncestor, curentDir, ancestorPathLen) == 0)
       return TRUE;
   return FALSE;
}
const char *GetParentDirectory(const char *pStrPath)
{

   int len;


   if(pStrPath == NULL)
       return NULL;
   len = strlen(pStrPath);

   if(len >= MAX_PATH_NAME_LEN||len<=1)
       return NULL;

   if(pStrPath != g_strTmpPathName)
          memcpy(g_strTmpPathName, pStrPath, len);

   if(g_strTmpPathName[len-1] == '/')
       len--;
   while(len && g_strTmpPathName[len-1] != '/')
       len--;
   if(len == 0)
         return NULL;
   g_strTmpPathName[len-1] = 0;
   return g_strTmpPathName;
}
const char *dev_basename(const char *name)
{
    const char *cp = strrchr(name, '/');
    if (cp)
        return cp + 1;
    return name;
}

int recursive_dev_folder(char *fileName, unsigned depth, unsigned maxdepth)
{
    struct stat statbuf;
    int status;
    DIR *dir;
       int res = 0;
    struct dirent *next;
      const char *dev_name;
      int curlen;
      static char filepathname[256];

      if(depth == 0)
        strcpy(filepathname, fileName);

    status = stat(filepathname, &statbuf);
    if (status < 0) {
              WPFS_DBG("stat %s failed\n", filepathname);
        return -1;
    }

    /* If S_ISLNK(m), then we know that !S_ISDIR(m).
     * Then we can skip checking first part: if it is true, then
     * (!dir) is also true! */
    if ( /* (!(flags & ACTION_FOLLOWLINKS) && S_ISLNK(statbuf.st_mode)) || */
     !S_ISDIR(statbuf.st_mode)
    )
    {
            return 0;
    }
      else
      {
           if(depth >= maxdepth)
               return 0;
        dir = opendir(filepathname);
        if (!dir)
           {
                 WPFS_DBG("Failed to open dir %s\n", filepathname);
            return -1;
           }
           curlen = strlen(filepathname);
         while ((next = readdir(dir)) != NULL)
            {
                 int tmp;

                      if(IS_DOT_OR_DOTDOT(next->d_name))
                         continue;
                      if(strcmp(next->d_name, "driver")==0)
                            continue;
                       if(strncmp(next->d_name, "usb_de", 6)==0)
                            continue;
                       if(strncmp(next->d_name, "usb_en", 6)==0)
                            continue;
                      if(strncmp(next->d_name, "subsys", 6)==0)
                            continue;

                      if(strcmp(next->d_name, "dev") == 0)
                      {
                           dev_name = dev_basename(filepathname);
                           if(IS_StoragePartiton(dev_name))
                           {
                                   int fifo_fd;
                                   WPFS_DBG("   find storage partition %s\n", filepathname);
                                   fifo_fd = open(FIFO_PIPE_NAME, O_WRONLY | O_NONBLOCK);
                                   if (fifo_fd == -1)
                                   {
                                        printf("Serious error currented, can not open named pipe %s for write.\n",   FIFO_PIPE_NAME);
                                   }
                                   else
                                   {
                                         union
                                        {
                                         char fifoCmdBuf[MAX_MESSAGE_LEN+1];
                                         PIPE_MSG_HEADER msgHeader;
                                        } tmpBuf;
                                         PIPE_MSG_HEADER *pMsgHeader = &tmpBuf.msgHeader;
                                         strcpy((char*)pMsgHeader + sizeof(PIPE_MSG_HEADER), filepathname);
                                         pMsgHeader->magic_number = HD_MAGIC_NUMBER;
                                         pMsgHeader->action = ACTION_ADD;
                                         pMsgHeader->stringLen = strlen(filepathname);
                                         write(fifo_fd, pMsgHeader, pMsgHeader->stringLen+ sizeof(PIPE_MSG_HEADER));
                                         close(fifo_fd);
                                   }
                              //  if(usb_mount_dev(filepathname, dev_name)==MNT_SUCCESS)
                                  //    return 1;
                           }
                      }
                      sprintf(filepathname+curlen, "/%s", next->d_name);
                      /* now descend into it (NB: ACTION_RECURSE is set in flags) */
                       tmp = recursive_dev_folder(filepathname, depth+1, maxdepth);
                      if(tmp < 0)
                      {
                            WPFS_DBG("Failed to open  %s\n", filepathname);
                      }
                      else
                        res += tmp;
                      filepathname[curlen] = 0;
          }
            closedir(dir);
            return res;
        }

}

void *N51FS_Wrapper_MultiTask(void *ctx)
{
    union
    {
        PIPE_MSG_HEADER header;
        char tmp[MAX_MESSAGE_LEN+1+3];
    }fifo_buf;
    const char *dev_name;
    PIPE_MSG_HEADER *pMsgHeader = &fifo_buf.header;
    char *fifoCmdBuf = (char*)pMsgHeader;

    long readLen;

    UNUSED(ctx);
   //FSRoutine_Test();

   printf("N51FS_Wrapper_MultiTask Start...\n");

    while(1)
    {
        if (g_fifo_fd != -1) {
            readLen = read(g_fifo_fd, pMsgHeader, sizeof(PIPE_MSG_HEADER));
            if (readLen > 0) {
                if (readLen != sizeof(PIPE_MSG_HEADER) || pMsgHeader->magic_number
                    != HD_MAGIC_NUMBER || pMsgHeader->stringLen
                    > MAX_MESSAGE_STRING_LEN) {
                    WPFS_DBG("   message header error!\n");
                   continue;
                }

                readLen = read(g_fifo_fd, pMsgHeader + 1, pMsgHeader->stringLen);
                if (readLen != pMsgHeader->stringLen) {
                    WPFS_DBG("  Read MSG string error\n");
                    continue;
                }


                fifoCmdBuf[sizeof(PIPE_MSG_HEADER) + pMsgHeader->stringLen] = 0;
                //printf("  received cmd [%s %s]\n", (pMsgHeader->action==ACTION_ADD)?"add":"delete", fifoCmdBuf+sizeof(PIPE_MSG_HEADER));
                WPFS_DBG("get message from XJYS, %s:%s\n", pMsgHeader->action == ACTION_ADD?"add":"de",
                    fifoCmdBuf + sizeof(PIPE_MSG_HEADER));

                dev_name = dev_basename(fifoCmdBuf + sizeof(PIPE_MSG_HEADER));
                if (IS_StoragePartiton(dev_name))
                {
                    // LOG("action:%s path:%s, devname=%s\n",
                    //         (pMsgHeader->action==ACTION_ADD)?"add":"delete", path_buf, dev_name);

                    if (pMsgHeader->action == ACTION_ADD)
                        usb_mount_dev(fifoCmdBuf + sizeof(PIPE_MSG_HEADER),
                        dev_name);
                    else
                        usb_umount_dev(dev_name);

                }
            }
        }
        else
        {
            WPFS_DBG("USB Message FIFO not openned!\n");
        }
        usleep(100*1000);
    }

}
