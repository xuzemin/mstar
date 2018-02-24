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
#ifndef __FS__STUB__HH__
#define __FS__STUB__HH__

#define MAX_PATH_NAME_LEN 256
#define MAX_DRV_COUNT 32
#define MAX_ENV_CNT 4
#define MAX_DEVICE_CNT 16

#define U32_B0(val)  ((U8)(val))
#define U32_B1(val)  ((U8)((val)>>8))
#define U32_B2(val)  ((U8)((val)>>16))
#define U32_B3(val)  ((U8)((val)>>24))

#define MK_U32(B0, B1, B2, B3) ((((U32)(B3))<<24) |(((U32)(B2))<<16)|(((U32)(B1))<<8)|((U32)(B0)))



#define WPFS_DBG(format, args...)   \
do   \
{    \
     printf(format, ##args); \
}while(0)

#define WPFS_ASSERT(x) do{ if(!(x)) printf("MBFS assert at %s:%d \n", __FUNCTION__, __LINE__);}while(0)



U8 FS_CreateEnv(U8 drvID);
BOOL FS_DestroyEnv(U8 envID);
U8 FS_GetDrvID(U8 u8EnvID);
const char *FS_GetMountPoint(U8 drvID);
BOOL FS_SetEnvCurrentDir(U8 envID, const char *targetDir);
BOOL FS_GetRelativeDirEntry(U8 enId,FileEntry* pFileToSet, BOOL isGetParent);
const char* FS_GetEnvCurrentDir(U8 envID);
BOOL FS_EntryFirst(U8 envID);
EN_ENTRY_NEXT_RESULT FS_EntryNext(U8 enId,FileEntry* pFileToSet);
BOOL FS_GetCurrentFileEntry(U8 envId,FileEntry* pFileToSet);
U8 FS_FileOpen(const FileEntry *pFileEntry, EN_OPEN_MODE u8OpenMode);
EN_FILE_CLOSE_RESULT FS_FileClose(U8 u8FileHandle);
U32 FS_FileWrite(U8 u8HandleNo, void* pu32Buffer, U32 u32Length);
U32 FS_FileRead(U8 u8HandleNo, void* pu32Buffer, U32 u32Length);
BOOL FS_FileSeek(U8 u8HandleNo,  LongLong seekOffset, EN_FILE_SEEK_OPTION option);
BOOL FS_TellFile(U8 u8HandleNo, LongLong *pRetLongLong);
BOOL FS_FileLength(U8 u8HandleNo, LongLong *pRetLongLong);
U8 FS_CreateFile(const FILE_CREATE_PARAM *pParam);
BOOL FS_FileDelete(const FileEntry *pFileEntry);
BOOL FS_CreateDirectory(const FILE_CREATE_PARAM *pParam);
BOOL FS_DeleteDirectory(const FileEntry *pFileEntry);
BOOL FS_GetUSBPortStatus(USB_PORT_STATUS *pUSBPortStatus);
BOOL FS_GetDriveInfo(U8 u8DrvID, DRIVE_INFO *pDriveInfo, BOOL bCalculateDiskSpace);

void FS_NotifyDrvMount(U8 busNo, U8 majorNo, U8 minorNO, const char *devName, const char *mountpoint, EN_FILE_SYSTEM_TYPE fsType,
                                    EN_FILE_SYSTEM_MNT_MODE fsMountMode, U8 deviceType);
void FS_NotifyDrvUnMount(const char *mountpoint);
void FS_ResetAllFileHandle(void);
void FS_Stub_Init(void);

S32 FS_QueryFd(U8 u8FileHandle);
int FS_StartXjysTask(void);
#endif
