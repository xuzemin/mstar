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
#ifndef __MBFS_STUB__HH__
#define __MBFS_STUB__HH__
#include "Wrapper_Common.h"

#define GET_DRAM_ADDR(x) (U32)(x)


#define U32_B0(val)  ((U8)(val))
#define U32_B1(val)  ((U8)((val)>>8))
#define U32_B2(val)  ((U8)((val)>>16))
#define U32_B3(val)  ((U8)((val)>>24))

#define MK_U32(B0, B1, B2, B3) ((((U32)(B3))<<24) |(((U32)(B2))<<16)|(((U32)(B1))<<8)|((U32)(B0)))


#define FS_DEFAULT_YEAR                           1980
#define FS_DEFAULT_MONTH                       1
#define FS_DEFAULT_DAY                             1
#define FS_DEFAULT_HOUR                          0
#define FS_DEFAULT_MIN                              0
#define FS_DEFAULT_SEC                             0
#define FAT_GET_DAY(x)      ((x >> 8) & 0x1F)
#define FAT_GET_MONTH(x)    (((x >>13) & 0x0F) + ((x & 0x01) * 8) )
#define FAT_GET_YEAR(x)     ((x >> 1) & 0x7F) + FS_DEFAULT_YEAR
#define FAT_GET_SEC(x)      (((x >> 8) & 0x1F) * 2 )
#define FAT_GET_MIN(x)      (((x >>13) & 0x3F) + ((x & 0x07) * 8) )
#define FAT_GET_HOUR(x)     ((x >> 3) & 0x1F)

#define INVALID_DRV_ID 0xFF
#define MAX_DRV_COUNT 32
#define MAX_ENV_CNT 4

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


typedef struct
{
    U8 u8CurrentDirectoryIndex;
    U8 u8FileSystemID;
    U8 u8FileSystemType;
    U8 u8DeviceIndex;
    BOOLEAN bIsInit;
}  FS_EnvironmentStruct;

/*interfaces*/
void msAPI_FS_Init(void);
void msAPI_FCtrl_Init(void);
U8 msAPI_FSEnv_Register(U8 u8DriveNo);
void msAPI_FSEnv_UnRegister(U8 u8HandleNo);
BOOLEAN msAPI_FCtrl_DirectoryChangeToRoot(U8 environmentID);
BOOLEAN msAPI_FCtrl_DirectoryChange(U8 enId,FileEntry* pFileEntry);
BOOLEAN msAPI_FCtrl_EntryFirst(U8 enId);
BOOLEAN msAPI_FCtrl_DirectoryChangeToContained(U8 enId,FileEntry* pFileEntry);
BOOLEAN msAPI_FCtrl_DirectoryGetDOTDOT(U8 environmentId,FileEntry* pFileToSet);
BOOLEAN msAPI_FCtrl_DirectoryGetDOT(U8 environmentId,FileEntry* pFileToSet);
BOOLEAN msAPI_FCtrl_DirectoryIsCurrentRoot(U8 environmentId);
EN_ENTRY_NEXT_RESULT msAPI_FCtrl_EntryNext(U8 enId, FileEntry* pFileToSet);
BOOLEAN msAPI_FCtrl_FileSeek(U8 u8HandleNo, U32 u32Length, EN_FILE_SEEK_OPTION option);
U32 msAPI_FCtrl_FileTell(U8 u8HandleNo);
U32 msAPI_FCtrl_FileLength(U8 u8HandleNo);
U8 msAPI_FCtrl_FileOpen(FileEntry* pFileEntry, U8 u8OpenMode);
EN_FILE_CLOSE_RESULT msAPI_FCtrl_FileClose(U8 u8HandleNo);
U32 msAPI_FCtrl_FileRead(U8 u8HandleNo, U32 u32Buffer, U32 u32Length);
U32 msAPI_FCtrl_FileWrite(U8 u8HandleNo, U32 u32Buffer, U32 u32Length);
U8 msAPI_FCtrl_FileCreate(U8 u8enid,U16 *pu16LongName,U8 charLen,EN_CREATE_MODE createMode);
BOOLEAN msAPI_FCtrl_DirectoryCreate(U8 u8enid, U16 *pu16LongName, U8 charLen);
U8 msAPI_FCtrl_EntryGetLongNameByFileEntry(U8 enId, FileEntry *entry, U32 MIUAddr, U8 charLen, BOOLEAN* pbShortNameOnly);
U32 msAPI_FCtrl_GetUnusedSizeInKB_ByDriveIndex(U8 u8DriveIndex);
U32 msAPI_FCtrl_GetTotalSizeInKB_ByDriveIndex(U8 u8DriveIndex);
BOOLEAN msAPI_FCtrl_GetDriveByIndex(U8 driveID,MSDCtrl_Drive* pDrive);
EN_MSD_STATUS msAPI_MSDCtrl_GetDeviceStatus(U8 u8DeviceIndex);
U8 msAPI_FCtrl_FileDelete(FileEntry* pFileEntry);
BOOLEAN msAPI_FCtrl_EntrySearchByName(U8 u8EnId,U16 *pu16FileNameToFind,U8 u8FileNameToFindLen ,FileEntry *pEntryToSet);
LongLong msAPI_FCtrl_FileLength_LongLong(U8 u8HandleNo);
LongLong msAPI_FCtrl_FileTell_LongLong(U8 u8HandleNo);
BOOLEAN msAPI_FCtrl_ActiveDevice(U8 deviceIndex);
BOOLEAN msAPI_FCtrl_FileSeek_LongLong(U8 u8HandleNo, LongLong u32Length, EN_FILE_SEEK_OPTION option);
U8 msAPI_FCtrl_EntryGetCurrentName(U8 enId,U32 MIUAddr,U8 charLen);
U8 msAPI_FCtrl_EntryGetShortNameByFileEntry(U8 enId, FileEntry* pEntry, U32 MIUAddr, U8 charLen);
void msAPI_FCtrl_FileHandleResetAll(void);
U8 msAPI_FCtrl_GetDriveCount(void);
U8 msAPI_FCtrl_GetDriveCountByPort(U8 port);
U8 msAPI_MSDCtrl_GetTotalDeviceCount(void);
BOOLEAN msAPI_FCtrl_IsDriveMounted(U8 u8DriveId);
BOOLEAN msAPI_MSDCtrl_IsPortChanged(EN_MSD_PORT port);
void msAPI_MSDCtrl_CheckDevicesOnPort(EN_MSD_PORT port);
void msAPI_MSDCtrl_ResetDevicesOnPort(EN_MSD_PORT port);
BOOLEAN msAPI_MSDCtrl_IsDeviceConnected(EN_MSD_PORT port);
BOOLEAN msAPI_MSDCtrl_IsPortOpened(EN_MSD_PORT port);
void msAPI_MSDCtrl_CheckDevices(void);
EN_MSD_PORT msAPI_MSDCtrl_GetDevicePort(U8 deviceIndex);
BOOLEAN msAPI_MSDCtrl_DevicesChangeStatusCheck(void);
void msAPI_MSDCtrl_ResetDevice(U8 deviceIndex);
void msAPI_MSDCtrl_ResetDevices(void);
void msAPI_MSDCtrl_ResetPorts(void);
U8 msAPI_GetUsbDeviceStatus(void);
U8 msAPI_GetUsbDeviceStatusPort2(void);
void msAPI_FS_MIU_Copy(U32 srcaddr, U32 dstaddr, U32 len);
U32 msAPI_MSDCtrl_GetPortStatus(void);
BOOLEAN MDrv_UsbDeviceConnect(void);
BOOLEAN MDrv_UsbDeviceConnect_Port2(void);
void msAPI_MSDCtrl_SetDeviceStatus(U8 u8DeviceIndex, EN_MSD_STATUS status);

FS_EnvironmentStruct* msAPI_FSEnv_GetEnvironment(U8 u8EnvID);

#endif
