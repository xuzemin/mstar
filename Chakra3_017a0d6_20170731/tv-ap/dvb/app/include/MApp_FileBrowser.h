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

#ifndef _MAPP_FILEBROWSER_H
#define    _MAPP_FILEBROWSER_H
/*************************************************************************************************************/


#include "datatype.h"
#include "debug.h"
#include "mapp_mplayer.h"

/*definition ====================================================================================*/
#define FCTRL_MAX_CONCURRENCY_FILTER_NAMES      5
#define FCTRL_MAX_FILTER_VALUE                  32

// File type: This is mapped to 'fileTypeStr[]' and 'fileTypeStrLower[]'...
#define FS_FILETYPE_DIR                 (1UL << 0)      // Directory
#define FS_FILETYPE_FILE                (1UL << 1)      // All files
#define FS_FILETYPE_JPG                 (1UL << 2)
#define FS_FILETYPE_MP3                 (1UL << 3)
#define FS_FILETYPE_MP4                 (1UL << 4)
#define FS_FILETYPE_AVI                 (1UL << 5)

#define FS_FILETYPE_NONE                (1UL << (FCTRL_MAX_FILTER_VALUE-1))

#define SECTOR_SIZE_512_BYTE            512
#define INVALID_BROWSER_HANDLE          0xFF

typedef struct
{
    U8 ps8DirEntryName[8];
    U8 ps8DirEntryExtName[3];
    U8 u8DirEntryAttrib;
    U8 pu8DirEntryReserved[8];
    U16 u16DirEntryStartClusterHI;
    U16 u16DirEntryTime;
    U16 u16DirEntryDate;
    U16 u16DirEntryStartClusterLO;
    U32 u32DirEntryFileLength;
}DirEntryStruct;

/*enumeration ===================================================================================*/
// Error code for file system
enum FS_ERROR_CODE
{
    FS_ERROR_CODE_FAIL                  = 0,
    FS_ERROR_CODE_TRUE                  = 1,
    FS_ERROR_CODE_NO_SYS                = 2,
    FS_ERROR_CODE_NO_ROOT               = 3
};

/*function ======================================================================================*/
#ifdef MAPP_FILEBROWSER_C
#define FILEBROWSER_INTERFACE
#else
#define    FILEBROWSER_INTERFACE extern
#endif

FILEBROWSER_INTERFACE U8 MApp_FileBrowser_Init(U16 driveIndex);

FILEBROWSER_INTERFACE U8 MApp_FileBrowser_Create(U16 driveIndex);
FILEBROWSER_INTERFACE void MApp_FileBrowser_Destroy(U8 u8Handle);
FILEBROWSER_INTERFACE void MApp_FileBrowser_SetEnvironment(U8 u8Handle);
FILEBROWSER_INTERFACE U8 MApp_FileBrowser_GetEnvironment(void);

FILEBROWSER_INTERFACE U8 MApp_FileBrowser_GetCurrentLongName(U32 MIUAddr,U8 charLen);
FILEBROWSER_INTERFACE U8 MApp_FileBrowser_GetLongFileNameByFileEntry(FileEntry *pEntry, U32 MIUAddr,U8 charLen);
FILEBROWSER_INTERFACE BOOLEAN MApp_FileBrowser_GetCurrentShortName(U32 shortNameAddr, U32 extNameAddr);
FILEBROWSER_INTERFACE U8 MApp_FileBrowser_GetCurrentDirectoryName(U32 MIUAddr,U8 charLen);
FILEBROWSER_INTERFACE BOOLEAN MApp_FileBrowser_ToFirstEntryInCurrentDirectory(void);
FILEBROWSER_INTERFACE BOOLEAN MApp_FileBrowser_ChangeDrive(U8 driveIndex);
FILEBROWSER_INTERFACE BOOLEAN MApp_FileBrowser_ChangeToRootDirectory(void);
FILEBROWSER_INTERFACE BOOLEAN MApp_FileBrowser_EnterDirectory(S16 EntryIndex);
FILEBROWSER_INTERFACE BOOLEAN MApp_FileBrowser_EnterDirectoryToContained(FileEntry *pFileEntry);
FILEBROWSER_INTERFACE void MApp_FileBrowser_PrintCurrentName(void);
FILEBROWSER_INTERFACE void MApp_FileBrowser_PrintCurrentEntry(void);
FILEBROWSER_INTERFACE void MApp_FileBrowser_GetFileEntryFullpath(FileEntry *fileEntry, char *fullpath);
FILEBROWSER_INTERFACE BOOLEAN MApp_FilrBrowser_CheckNameExistedInCurrent(U16* pString,U8 charLen);
FILEBROWSER_INTERFACE EN_FILE_SYSTEM_TYPE MApp_FileBrowser_GetCurrentFileSystemType(void);
FILEBROWSER_INTERFACE U8 MApp_FileBrowser_OpenNewFileForWrite(U16* pString,U8 charLen);
FILEBROWSER_INTERFACE BOOLEAN MApp_FileBrowser_OpenNewFolder_And_GetFileEntry(U16* pString, U8 charLen, FileEntry *pstFileEntry);
FILEBROWSER_INTERFACE U32 u32InfoFileSize;
FILEBROWSER_INTERFACE BOOLEAN MApp_FileBrowser_GetCurrentFileEntry(FileEntry* pEntryToSet);
FILEBROWSER_INTERFACE U8 MApp_FileBrowser_GetCurrentDriveName(void);

FILEBROWSER_INTERFACE DirEntryStruct * MApp_FileBrowser_GetCurrentDirEntry(void);
FILEBROWSER_INTERFACE DirEntryStruct * MApp_FileBrowser_GetNextDirEntry(U16 NextEntryNo);
FILEBROWSER_INTERFACE DirEntryStruct * MApp_FileBrowser_GetPrevDirEntry(U16 PrevEntryNo);

FILEBROWSER_INTERFACE void MApp_FileBrowser_DeInit(void);
FILEBROWSER_INTERFACE U32 MApp_FileBrowser_GetCurrentLength(void);
FILEBROWSER_INTERFACE LongLong MApp_FileBrowser_GetCurrentLength_LongLong(void);
FILEBROWSER_INTERFACE U8 MApp_FileBrowser_EnterFile(S16 EntryIndex);
FILEBROWSER_INTERFACE BOOLEAN MApp_FileBrowser_DeleteFile(S16 EntryIndex);
FILEBROWSER_INTERFACE BOOLEAN MApp_FileBrowser_DeleteFileByFileEntry(FileEntry *pEntry);

#if 1//DYNAMIC_VECTOR_FONT_ENABLE  || ENABLE_DVD
FILEBROWSER_INTERFACE BOOLEAN MApp_FilrBrowser_GetNameExistedInCurrent(U16* pString,U8 charLen, FileEntry *pEntryToSet);
#endif

FILEBROWSER_INTERFACE BOOLEAN MApp_FileBrowser_OpenNewFolder(U16* pString,U8 charLen);
FILEBROWSER_INTERFACE BOOLEAN MApp_FileBrowser_DirectoryChange(FileEntry *pFileEntry);

/*debug function =================================================================================*/
FILEBROWSER_INTERFACE void MApp_FileBrowser_Write_Debug(S8 * s8WriteFileName, U32 u32WriteTotalLength, U32 u32BufferLength);
FILEBROWSER_INTERFACE void MApp_FileBrowser_Copy_Debug(S8 * s8WriteFileName, S8 * s8ReadFileName, U32 u32BufferLength);




/*************************************************************************************************************/
#endif    /*_MAPP_FILEBROWSER_H END */

