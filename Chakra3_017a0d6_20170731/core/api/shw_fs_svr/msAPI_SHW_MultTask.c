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
#include "datatype.h"
#include "debug.h"
#include "Board.h"
#include "sysinfo.h"
#include "drvCPU.h"
#include "msAPI_MailBox.h"

#include "msAPI_FSEnv.h"
#include "msAPI_FCtrl.h"
#include "msAPI_MSDCtrl.h"
#include "msAPI_SHW_MultTask.h"

#define U32_B0(val)  ((U8)(val))
#define U32_B1(val)  ((U8)((val)>>8))
#define U32_B2(val)  ((U8)((val)>>16))
#define U32_B3(val)  ((U8)((val)>>24))
#define MK_U32(B0, B1, B2, B3) ((((U32)(B3))<<24) |(((U32)(B2))<<16)|(((U32)(B1))<<8)|((U32)(B0)))

typedef enum
{
//MIPS -->AEON
   SHWFS_FCNTL_ACK_AEON2MIPS = 0,
   SHWFS_FCNTL_INITIALIZE = 1,
   SHWFS_FCNTL_FINIALIZE = 2,
   SHWFS_FCNTL_CREAT_ENV = 3,
   SHWFS_FCNTL_CHG2ROOT = 4,
   SHWFS_FCNTL_CHG_DIRECTORY = 5,
   SHWFS_FCNTL_CHG_2_CONTAINER = 6,
   SHWFS_FCNTL_GET_PARENT_DIR = 7,
   SHWFS_FCNTL_GET_CURRENT_DIR = 8,
   SHWFS_FCNTL_CHG2FIRSTENTRY = 9,
   SHWFS_FCNTL_CHG2NEXTENTRY = 10,
   SHWFS_FCNTL_IS_CUR_ROOT = 11,
   SHWFS_FCNTL_DESTORY_ENV = 12,
   SHWFS_FCNTL_CREAT_FILE = 13,
   SHWFS_FCNTL_OPEN_FILE = 14,
   SHWFS_FCNTL_CLOSE_FILE = 15,
   SHWFS_FCNTL_WRITE_FILE = 16,
   SHWFS_FCNTL_READ_FILE = 17,
   SHWFS_FCNTL_SEEKSET_FILE = 18,
   SHWFS_FCNTL_SEEKCUR_FILE = 19,
   SHWFS_FCNTL_TELL_FILE = 20,
   SHWFS_FCNTL_FILE_LENGTH = 21,
   SHWFS_FCNTL_INFO_FILE = 22,
   SHWFS_FCNTL_DELETE_FILE = 23,
   SHWFS_FCNTL_CREATE_DIRECTORY = 24,
   SHWFS_FCNTL_GET_FILENAME_INFO = 25,

   SHWFS_FCNTL_GET_DEVICE_COUNT = 26,
   SHWFS_FCNTL_GET_DEVICE_STATUS = 27,
   SHWFS_FCNTL_GET_DRIVE_COUNT = 28,
   SHWFS_FCNTL_GET_DRIVE_INFO = 29,


   SHWFS_FCNTL_RESET_ALL_FILE_HANDLE = 30,  //get drive info all will calculate disk available space
//AEON-->MIPS

   SHWFS_FCNTL_ACK_MIPS2AEON_BASE=80,
   SHWFS_FCNTL_ALIVE_MSG = 0xFF
}SHWFS_FCNTL_ACTION;
#define SHWFS_AEON_ACK(x) (SHWFS_FCNTL_ACK_MIPS2AEON_BASE+(x))
typedef struct
{
   U8 u8EnvID;
   U32 createmode;
   U32 fileNameLength;
   U16 filename[1];
}SHWFS_FILE_CREATE_PARAM;


typedef struct
{
    U8  u8EnvID;
    U8  IsShortNameOnly;
    U8 u8LongNameBufLen;
    U8 u8ShortNameBufLen;
    FileEntry  fileEntry;
    U16 LongNameBuf[256];
    U8 ShortNameBuf[12];
}SHWFS_FILE_NAME_INFO;


#define SHWFS_PARAM_CNT 10
typedef struct
{
   //U8 u8Ctrl;
   U8 fsACTClass;
   U8 actionType;
   U8 u8ParamCnt;
   U32 u32Param1;
   U32 u32Param2;
   U8 u8Param;
   U8 sequenceID;
}SHWFS_MAIL_MSG;


#if 0
#define SHWFS_FCNTL_DBG(x)   do{printf("  Got cmd %s\n", #x);}while(0)
#else
#define SHWFS_FCNTL_DBG(x)   do{}while(0)
#endif

#define SHWFS_LOG(format, args...)   \
do   \
{    \
     printf(format, ##args); \
}while(0)


BOOL msAPI_SHWFS_SVR_Initialize(void)
{
    return TRUE;
}

void msAPI_SHWFSRoutine_Finalize(void)
{
}

static U8 g_SHWFS_sequenceID = 0x01;

static BOOL SendMail2MIPS(SHWFS_MAIL_MSG *pFSMsg)
{
    MBX_Msg mbxMsg;

    mbxMsg.eMsgType = E_MBX_MSG_TYPE_NORMAL;
    mbxMsg.u8MsgClass = pFSMsg->fsACTClass;
    mbxMsg.u8Index = pFSMsg->actionType;
    mbxMsg.u8ParameterCount = 10;
    mbxMsg.u8Parameters[0] = U32_B0(pFSMsg->u32Param1);
    mbxMsg.u8Parameters[1] = U32_B1(pFSMsg->u32Param1);
    mbxMsg.u8Parameters[2] = U32_B2(pFSMsg->u32Param1);
    mbxMsg.u8Parameters[3] = U32_B3(pFSMsg->u32Param1);
    mbxMsg.u8Parameters[4] = U32_B0(pFSMsg->u32Param2);
    mbxMsg.u8Parameters[5] = U32_B1(pFSMsg->u32Param2);
    mbxMsg.u8Parameters[6] = U32_B2(pFSMsg->u32Param2);
    mbxMsg.u8Parameters[7] = U32_B3(pFSMsg->u32Param2);
    mbxMsg.u8Parameters[8] = pFSMsg->u8Param;
    mbxMsg.u8Parameters[9] = pFSMsg->sequenceID = g_SHWFS_sequenceID++;

    if(E_MBX_SUCCESS == MSApi_MBX_SendMsg(&mbxMsg))
    {
        return TRUE;
    }

    return FALSE;
}

static void* MapMIPSMem2AEON(U32 u32AeonAddr)
{
    return (void*)((u32AeonAddr+0)|0x80000000);
}
static void FlushAEONMem2MIPS(void *pAddr, U32 size)
{
   UNUSED(pAddr);
   UNUSED(size);
}

BOOL SHW_FS_Get_Message(SHWFS_MAIL_MSG *pFSMsg)
{
    MBX_Msg mbxMsg;

    if(E_MBX_SUCCESS != MSApi_MBX_RecvMsg(E_MBX_CLASS_SHWFS, &mbxMsg, 0, MBX_CHECK_NORMAL_MSG))
    {
        return FALSE;

    }

    pFSMsg->fsACTClass = mbxMsg.u8MsgClass;
    pFSMsg->actionType = mbxMsg.u8Index;
    pFSMsg->u32Param1 = MK_U32(mbxMsg.u8Parameters[0], mbxMsg.u8Parameters[1], mbxMsg.u8Parameters[2], mbxMsg.u8Parameters[3]);
    pFSMsg->u32Param2 = MK_U32(mbxMsg.u8Parameters[4], mbxMsg.u8Parameters[5], mbxMsg.u8Parameters[6], mbxMsg.u8Parameters[7]);
    pFSMsg->u8Param = mbxMsg.u8Parameters[8];
    pFSMsg->sequenceID = mbxMsg.u8Parameters[9];
    return TRUE;
}


BOOL msAPI_SHWFS_DispatchTask(void)
{

   SHWFS_MAIL_MSG fsMsg;

   do
   {
       if(SHW_FS_Get_Message(&fsMsg) == FALSE)
           break;

          fsMsg.fsACTClass = E_MBX_CLASS_SHWFS;
          switch(fsMsg.actionType)
          {
             case SHWFS_FCNTL_ACK_AEON2MIPS:
                SHWFS_FCNTL_DBG(SHWFS_FCNTL_ACK_AEON2MIPS);
                break;
             case SHWFS_FCNTL_INITIALIZE:
                SHWFS_FCNTL_DBG(SHWFS_FCNTL_INITIALIZE);
                {
                      fsMsg.actionType = SHWFS_AEON_ACK(SHWFS_FCNTL_INITIALIZE);
                      fsMsg.u8Param = TRUE;
                      if(SendMail2MIPS(&fsMsg) == FALSE)
                      {
                         SHWFS_LOG("Failed to send ACK to MIPS\n");
                      }
                 }
                break;
             case SHWFS_FCNTL_FINIALIZE:
                SHWFS_FCNTL_DBG(SHWFS_FCNTL_FINIALIZE);
                break;
             case SHWFS_FCNTL_CREAT_ENV:
                SHWFS_FCNTL_DBG(SHWFS_FCNTL_CREAT_ENV);
                {
                      U8 u8DrvID = fsMsg.u8Param;
                      fsMsg.u8Param = msAPI_FSEnv_Register(u8DrvID);
                      fsMsg.actionType = SHWFS_AEON_ACK(SHWFS_FCNTL_CREAT_ENV);
                      if(SendMail2MIPS(&fsMsg) == FALSE)
                      {
                         SHWFS_LOG("Failed to send ACK to MIPS\n");
                      }
                 }
                break;
             case SHWFS_FCNTL_CHG2ROOT:
                SHWFS_FCNTL_DBG(SHWFS_FCNTL_CHG2ROOT);
                {
                      U8 u8EnvID= fsMsg.u8Param;

                      if(msAPI_FCtrl_DirectoryChangeToRoot(u8EnvID))
                      {
                            fsMsg.u8Param = TRUE;
                       }
                       else
                       {
                            fsMsg.u8Param = FALSE;
                       }
                        fsMsg.actionType = SHWFS_AEON_ACK(SHWFS_FCNTL_CHG2ROOT);
                       if(SendMail2MIPS(&fsMsg) == FALSE)
                       {
                         SHWFS_LOG("Failed to send ACK to AEON\n");
                       }
                 }
                break;

             case SHWFS_FCNTL_CHG_DIRECTORY:
                SHWFS_FCNTL_DBG(SHWFS_FCNTL_CHG_DIRECTORY);
                {
                      U8 u8EnvID= fsMsg.u8Param;
                      FileEntry *pFileEntry;

                      pFileEntry = (FileEntry*)MapMIPSMem2AEON(fsMsg.u32Param1);

            if(msAPI_FCtrl_DirectoryChange(u8EnvID, pFileEntry))
                fsMsg.u8Param = TRUE;
            else
                fsMsg.u8Param = FALSE;

                       fsMsg.actionType = SHWFS_AEON_ACK(SHWFS_FCNTL_CHG_DIRECTORY);
                       if(SendMail2MIPS(&fsMsg) == FALSE)
                       {
                         SHWFS_LOG("Failed to send ACK to AEON\n");
                       }
                 }
                break;
             case SHWFS_FCNTL_CHG_2_CONTAINER:
                 SHWFS_FCNTL_DBG(SHWFS_FCNTL_CHG_2_CONTAINER);
                {
                      U8 u8EnvID= fsMsg.u8Param;
                      FileEntry *pFileEntry;

                      pFileEntry = (FileEntry*)MapMIPSMem2AEON(fsMsg.u32Param1);

#if FILE_SYSTEM_ENABLE_FCTRL_DIRECTORY_CHANGE_TO_CONTAINED
                     if(msAPI_FCtrl_DirectoryChangeToContained(u8EnvID, pFileEntry))
                fsMsg.u8Param = TRUE;
            else
                fsMsg.u8Param = FALSE;
#else
                      fsMsg.u8Param = FALSE;
#endif
                       fsMsg.actionType = SHWFS_AEON_ACK(SHWFS_FCNTL_CHG_2_CONTAINER);
                       if(SendMail2MIPS(&fsMsg) == FALSE)
                       {
                         SHWFS_LOG("Failed to send ACK to AEON\n");
                       }
                 }
                break;
             case SHWFS_FCNTL_GET_PARENT_DIR:
              SHWFS_FCNTL_DBG(SHWFS_FCNTL_GET_PARENT_DIR);
              {
                      U8 u8EnvID= fsMsg.u8Param;
                      FileEntry *pFileEntry = (FileEntry*)MapMIPSMem2AEON(fsMsg.u32Param1);

                     if(msAPI_FCtrl_DirectoryGetDOTDOT(u8EnvID, pFileEntry))
                fsMsg.u8Param = TRUE;
            else
                fsMsg.u8Param = FALSE;
                      FlushAEONMem2MIPS((void*)pFileEntry, sizeof(FileEntry));
                      fsMsg.actionType = SHWFS_AEON_ACK(SHWFS_FCNTL_GET_PARENT_DIR);
                      if(SendMail2MIPS(&fsMsg) == FALSE)
                      {
                         SHWFS_LOG("Failed to send ACK to AEON\n");
                      }
              }
              break;
              case SHWFS_FCNTL_GET_CURRENT_DIR:
              SHWFS_FCNTL_DBG(SHWFS_FCNTL_GET_CURRENT_DIR);
              {
                      U8 u8EnvID= fsMsg.u8Param;
                      FileEntry *pFileEntry = (FileEntry*)MapMIPSMem2AEON(fsMsg.u32Param1);
#if FILE_SYSTEM_ENABLE_FCTRL_GET_DIRECTORY_DOT
                     if(msAPI_FCtrl_DirectoryGetDOT(u8EnvID,  pFileEntry))
                fsMsg.u8Param = TRUE;
            else
                fsMsg.u8Param = FALSE;
                     FlushAEONMem2MIPS((void*)pFileEntry, sizeof(FileEntry));
#else
                     fsMsg.u8Param = FALSE;
#endif
                      fsMsg.actionType = SHWFS_AEON_ACK(SHWFS_FCNTL_GET_CURRENT_DIR);
                      if(SendMail2MIPS(&fsMsg) == FALSE)
                      {
                         SHWFS_LOG("Failed to send ACK to AEON\n");
                      }
              }
              break;
             case SHWFS_FCNTL_CHG2FIRSTENTRY:
                SHWFS_FCNTL_DBG(SHWFS_FCNTL_CHG2FIRSTENTRY);
                {
                      U8 u8EnvID= fsMsg.u8Param;
                      if(msAPI_FCtrl_EntryFirst(u8EnvID))
                      {
                           fsMsg.u8Param = TRUE;
                      }
                      else
                      {
                           fsMsg.u8Param = FALSE;
                      }
                       fsMsg.actionType = SHWFS_AEON_ACK(SHWFS_FCNTL_CHG2FIRSTENTRY);
                       if(SendMail2MIPS(&fsMsg) == FALSE)
                       {
                         SHWFS_LOG("Failed to send ACK to AEON\n");
                       }
                }
                break;
             case SHWFS_FCNTL_CHG2NEXTENTRY:
                SHWFS_FCNTL_DBG(SHWFS_FCNTL_CHG2NEXTENTRY);
                {
                      U8 u8EnvID= fsMsg.u8Param;
                      FileEntry *pFileEntry = (FileEntry*)MapMIPSMem2AEON(fsMsg.u32Param1);

                      fsMsg.u8Param = msAPI_FCtrl_EntryNext(u8EnvID, pFileEntry);
                      FlushAEONMem2MIPS((void*)pFileEntry, sizeof(FileEntry));

                      fsMsg.actionType = SHWFS_AEON_ACK(SHWFS_FCNTL_CHG2NEXTENTRY);
                      if(SendMail2MIPS(&fsMsg) == FALSE)
                      {
                         SHWFS_LOG("Failed to send ACK to AEON\n");
                      }
                }
                break;

             case SHWFS_FCNTL_IS_CUR_ROOT:
                SHWFS_FCNTL_DBG(SHWFS_FCNTL_IS_CUR_ROOT);
                {
                      U8 u8EnvID= fsMsg.u8Param;


                      if(msAPI_FCtrl_DirectoryIsCurrentRoot(u8EnvID))
                          fsMsg.u8Param = TRUE;
                      else
                         fsMsg.u8Param = FALSE;

                      fsMsg.actionType = SHWFS_AEON_ACK(SHWFS_FCNTL_IS_CUR_ROOT);
                      if(SendMail2MIPS(&fsMsg) == FALSE)
                      {
                         SHWFS_LOG("Failed to send ACK to AEON\n");
                      }
                }
                break;
             case SHWFS_FCNTL_DESTORY_ENV:
               SHWFS_FCNTL_DBG(SHWFS_FCNTL_DESTORY_ENV);
               {
                      U8 u8EnvID = fsMsg.u8Param;
                      msAPI_FSEnv_UnRegister(u8EnvID);

                      fsMsg.u8Param = TRUE;

                      fsMsg.actionType = SHWFS_AEON_ACK(SHWFS_FCNTL_DESTORY_ENV);
                      if(SendMail2MIPS(&fsMsg) == FALSE)
                      {
                         SHWFS_LOG("Failed to send ACK to AEON\n");
                      }
                 }
                break;
             case SHWFS_FCNTL_CREAT_FILE:
                SHWFS_FCNTL_DBG(SHWFS_FCNTL_CREAT_FILE);
                {
                      SHWFS_FILE_CREATE_PARAM *pCreatParam = (SHWFS_FILE_CREATE_PARAM*)MapMIPSMem2AEON(fsMsg.u32Param1);

                      fsMsg.u8Param = msAPI_FCtrl_FileCreate(pCreatParam->u8EnvID, pCreatParam->filename,
                          pCreatParam->fileNameLength, (EN_CREATE_MODE)pCreatParam->createmode);
                      fsMsg.actionType =  SHWFS_AEON_ACK(SHWFS_FCNTL_CREAT_FILE);
                      if(SendMail2MIPS(&fsMsg) == FALSE)
                      {
                         SHWFS_LOG("Failed to send ACK to AEON\n");
                      }

                }
                break;
             case SHWFS_FCNTL_OPEN_FILE:
                SHWFS_FCNTL_DBG(SHWFS_FCNTL_OPEN_FILE);
               {
                      U8 u8OpenMode = fsMsg.u8Param;
                      FileEntry *pFileEntry = (FileEntry*)MapMIPSMem2AEON(fsMsg.u32Param1);

                      fsMsg.u8Param = msAPI_FCtrl_FileOpen(pFileEntry, u8OpenMode);
                      fsMsg.actionType =  SHWFS_AEON_ACK(SHWFS_FCNTL_OPEN_FILE);
                      if(SendMail2MIPS(&fsMsg) == FALSE)
                      {
                         SHWFS_LOG("Failed to send ACK to AEON\n");
                      }
                 }
                break;
             case SHWFS_FCNTL_CLOSE_FILE:
                SHWFS_FCNTL_DBG(SHWFS_FCNTL_CLOSE_FILE);
               {
                      U8 u8FileHandle = fsMsg.u8Param;

                      fsMsg.u8Param = msAPI_FCtrl_FileClose(u8FileHandle);
                      fsMsg.actionType =  SHWFS_AEON_ACK(SHWFS_FCNTL_CLOSE_FILE);
                      if(SendMail2MIPS(&fsMsg) == FALSE)
                      {
                         SHWFS_LOG("Failed to send ACK to AEON\n");
                      }
                 }
                break;
             case SHWFS_FCNTL_WRITE_FILE:
                SHWFS_FCNTL_DBG(SHWFS_FCNTL_WRITE_FILE);
                {
                      U8 u8FileHandle = fsMsg.u8Param;
                      void *pAddr = MapMIPSMem2AEON(fsMsg.u32Param1);
                      U32  writeLen = fsMsg.u32Param2;

                      fsMsg.u32Param1 = msAPI_FCtrl_FileWrite(u8FileHandle, (U32)pAddr, writeLen);
                      fsMsg.actionType =  SHWFS_AEON_ACK(SHWFS_FCNTL_WRITE_FILE);
                      if(SendMail2MIPS(&fsMsg) == FALSE)
                      {
                         SHWFS_LOG("Failed to send ACK to AEON\n");
                      }
                 }
                break;
             case SHWFS_FCNTL_READ_FILE:
                SHWFS_FCNTL_DBG(SHWFS_FCNTL_READ_FILE);
                {
                      U8 u8FileHandle = fsMsg.u8Param;
                      void *pAddr = (void*)MapMIPSMem2AEON(fsMsg.u32Param1);
                      U32  ReadLen = fsMsg.u32Param2;

                      fsMsg.u32Param1 = msAPI_FCtrl_FileRead(u8FileHandle, (U32)pAddr, ReadLen);
                      FlushAEONMem2MIPS((void*)pAddr, ReadLen-fsMsg.u32Param1);
                      fsMsg.actionType =  SHWFS_AEON_ACK(SHWFS_FCNTL_READ_FILE);
                      if(SendMail2MIPS(&fsMsg) == FALSE)
                      {
                         SHWFS_LOG("Failed to send ACK to AEON\n");
                      }
                 }
                break;
             case SHWFS_FCNTL_SEEKSET_FILE:
                SHWFS_FCNTL_DBG(SHWFS_FCNTL_SEEKSET_FILE);
                 {
                      U8 u8FileHandle = fsMsg.u8Param;
             if(fsMsg.u32Param1 == 0)
             {
                           if(msAPI_FCtrl_FileSeek(u8FileHandle, fsMsg.u32Param2, FILE_SEEK_SET))
                                  fsMsg.u8Param = TRUE;
                           else
                                  fsMsg.u8Param = FALSE;
             }
             else
             {
                 LongLong seekLen;
                 seekLen.Hi = fsMsg.u32Param1;
                 seekLen.Lo = fsMsg.u32Param2;
                          if(msAPI_FCtrl_FileSeek_LongLong(u8FileHandle, seekLen, FILE_SEEK_SET))
                                  fsMsg.u8Param = TRUE;
                          else
                                  fsMsg.u8Param = FALSE;
             }
                      fsMsg.actionType =  SHWFS_AEON_ACK(SHWFS_FCNTL_SEEKSET_FILE);
                      if(SendMail2MIPS(&fsMsg) == FALSE)
                      {
                         SHWFS_LOG("Failed to send ACK to AEON\n");
                      }
                 }
                break;
             case SHWFS_FCNTL_SEEKCUR_FILE:
                SHWFS_FCNTL_DBG(SHWFS_FCNTL_SEEKCUR_FILE);
                 {
                      U8 u8FileHandle = fsMsg.u8Param;

             if(fsMsg.u32Param1 == 0)
             {
                           if(msAPI_FCtrl_FileSeek(u8FileHandle, fsMsg.u32Param2, FILE_SEEK_CUR))
                                  fsMsg.u8Param = TRUE;
                           else
                                  fsMsg.u8Param = FALSE;
             }
             else
             {
                 LongLong seekLen;
                 seekLen.Hi = fsMsg.u32Param1;
                 seekLen.Lo = fsMsg.u32Param2;
                          if(msAPI_FCtrl_FileSeek_LongLong(u8FileHandle, seekLen, FILE_SEEK_CUR))
                                  fsMsg.u8Param = TRUE;
                          else
                                  fsMsg.u8Param = FALSE;
             }
                      fsMsg.actionType =  SHWFS_AEON_ACK(SHWFS_FCNTL_SEEKCUR_FILE);
                      if(SendMail2MIPS(&fsMsg) == FALSE)
                      {
                         SHWFS_LOG("Failed to send ACK to AEON\n");
                      }
                 }
                break;
             case SHWFS_FCNTL_TELL_FILE:
                 SHWFS_FCNTL_DBG(SHWFS_FCNTL_TELL_FILE);
                 {
                      U8 u8FileHandle = fsMsg.u8Param;
             U32 filePos;

             filePos = msAPI_FCtrl_FileTell(u8FileHandle);

                      fsMsg.u32Param1 =0;
                      fsMsg.u32Param2 =filePos;
                      fsMsg.actionType =  SHWFS_AEON_ACK(SHWFS_FCNTL_TELL_FILE);
             fsMsg.u8Param = TRUE;
                      if(SendMail2MIPS(&fsMsg) == FALSE)
                      {
                         SHWFS_LOG("Failed to send ACK to AEON\n");
                      }
                 }
                break;
              case SHWFS_FCNTL_FILE_LENGTH:
                 SHWFS_FCNTL_DBG(SHWFS_FCNTL_FILE_LENGTH);
                 {
                      U8 u8FileHandle = fsMsg.u8Param;
             U32 fileLength;

             fileLength = msAPI_FCtrl_FileLength(u8FileHandle);
                      fsMsg.u32Param1 =0;
                      fsMsg.u32Param2 =fileLength;
             fsMsg.u8Param = TRUE;
                      fsMsg.actionType =  SHWFS_AEON_ACK(SHWFS_FCNTL_FILE_LENGTH);
                      if(SendMail2MIPS(&fsMsg) == FALSE)
                      {
                         SHWFS_LOG("Failed to send ACK to AEON\n");
                      }
                 }
                break;
             case SHWFS_FCNTL_DELETE_FILE:
                SHWFS_FCNTL_DBG(SHWFS_FCNTL_DELETE_FILE);
                 {
                      FileEntry *pFileEntry = (FileEntry*)MapMIPSMem2AEON(fsMsg.u32Param1);

                      if(msAPI_FCtrl_FileDelete(pFileEntry))
                            fsMsg.u8Param = TRUE;
                      else
                            fsMsg.u8Param = FALSE;
                      fsMsg.actionType =  SHWFS_AEON_ACK(SHWFS_FCNTL_DELETE_FILE);
                      if(SendMail2MIPS(&fsMsg) == FALSE)
                      {
                         SHWFS_LOG("Failed to send ACK to AEON\n");
                      }
                 }
                break;
             case SHWFS_FCNTL_CREATE_DIRECTORY:
                SHWFS_FCNTL_DBG(SHWFS_FCNTL_CREATE_DIRECTORY);
                {
  #if FILE_SYSTEM_FOLDER_CREATE_ENABLE
                      SHWFS_FILE_CREATE_PARAM *pCreatParam = (SHWFS_FILE_CREATE_PARAM*)MapMIPSMem2AEON(fsMsg.u32Param1);
                      if(msAPI_FCtrl_DirectoryCreate(pCreatParam->u8EnvID, pCreatParam->filename, pCreatParam->fileNameLength))
                           fsMsg.u8Param = TRUE;
                      else
                           fsMsg.u8Param = FALSE;
  #else
                      fsMsg.u8Param = FALSE;
  #endif
                      fsMsg.actionType =  SHWFS_AEON_ACK(SHWFS_FCNTL_CREATE_DIRECTORY);
                      if(SendMail2MIPS(&fsMsg) == FALSE)
                      {
                         SHWFS_LOG("Failed to send ACK to AEON\n");
                      }

                }
                break;

             case SHWFS_FCNTL_GET_FILENAME_INFO:
                SHWFS_FCNTL_DBG(SHWFS_FCNTL_GET_FILENAME_INFO);
                {
                     BOOLEAN bShortNameOnly;
                     SHWFS_FILE_NAME_INFO *pFileNameInfo = (SHWFS_FILE_NAME_INFO*)MapMIPSMem2AEON(fsMsg.u32Param1);

                      if(pFileNameInfo->u8LongNameBufLen)
                      {
                            pFileNameInfo->u8LongNameBufLen = msAPI_FCtrl_EntryGetLongNameByFileEntry(
                        pFileNameInfo->u8EnvID, &pFileNameInfo->fileEntry, (U32)&pFileNameInfo->LongNameBuf[0],
                        pFileNameInfo->u8LongNameBufLen, &bShortNameOnly);
                   if(bShortNameOnly)
                          pFileNameInfo->IsShortNameOnly = TRUE;
                   else
                        pFileNameInfo->IsShortNameOnly = FALSE;
                      }
            if(pFileNameInfo->u8ShortNameBufLen)
            {
                   pFileNameInfo->u8ShortNameBufLen = msAPI_FCtrl_EntryGetShortNameByFileEntry(pFileNameInfo->u8EnvID,
                          &pFileNameInfo->fileEntry, (U32)&pFileNameInfo->ShortNameBuf[0], pFileNameInfo->u8ShortNameBufLen);
                }

                      fsMsg.u8Param = TRUE;


                      fsMsg.actionType =  SHWFS_AEON_ACK(SHWFS_FCNTL_GET_FILENAME_INFO);
                      if(SendMail2MIPS(&fsMsg) == FALSE)
                      {
                         SHWFS_LOG("Failed to send ACK to AEON\n");
                      }

                }
                break;

                case SHWFS_FCNTL_GET_DEVICE_COUNT:
                SHWFS_FCNTL_DBG(SHWFS_FCNTL_GET_DEVICE_COUNT);
                {

                      fsMsg.u8Param = msAPI_MSDCtrl_GetTotalDeviceCount();
                      fsMsg.actionType = SHWFS_AEON_ACK(SHWFS_FCNTL_GET_DEVICE_COUNT);
                      if(SendMail2MIPS(&fsMsg) == FALSE)
                      {
                         SHWFS_LOG("Failed to send ACK to AEON\n");
                      }
                }
                break;
                case SHWFS_FCNTL_GET_DEVICE_STATUS:
          SHWFS_FCNTL_DBG(SHWFS_FCNTL_GET_DEVICE_STATUS);
                {

                      fsMsg.u8Param = msAPI_MSDCtrl_GetDeviceStatus(fsMsg.u8Param);
                      fsMsg.actionType = SHWFS_AEON_ACK(SHWFS_FCNTL_GET_DEVICE_STATUS);
                      if(SendMail2MIPS(&fsMsg) == FALSE)
                      {
                         SHWFS_LOG("Failed to send ACK to AEON\n");
                      }
                }
                break;
                case SHWFS_FCNTL_GET_DRIVE_COUNT:
                SHWFS_FCNTL_DBG(SHWFS_FCNTL_GET_DRIVE_COUNT);
                {

                      fsMsg.u8Param = msAPI_FCtrl_GetDriveCount();
                      fsMsg.actionType = SHWFS_AEON_ACK(SHWFS_FCNTL_GET_DRIVE_COUNT);
                      if(SendMail2MIPS(&fsMsg) == FALSE)
                      {
                         SHWFS_LOG("Failed to send ACK to AEON\n");
                      }
                }
                break;
              case SHWFS_FCNTL_GET_DRIVE_INFO:
                SHWFS_FCNTL_DBG(SHWFS_FCNTL_GET_DRIVE_INFO);
                {
                      U8 drvID = fsMsg.u8Param;
                      MSDCtrl_Drive *pDriveInfo = (MSDCtrl_Drive*)MapMIPSMem2AEON(fsMsg.u32Param1);
                      if(msAPI_FCtrl_GetDriveByIndex(drvID, pDriveInfo))
                            fsMsg.u8Param = TRUE;
                      else
                            fsMsg.u8Param = FALSE;
                      fsMsg.actionType = SHWFS_AEON_ACK(SHWFS_FCNTL_GET_DRIVE_INFO);
                      FlushAEONMem2MIPS((void*)pDriveInfo, sizeof(MSDCtrl_Drive));
                      if(SendMail2MIPS(&fsMsg) == FALSE)
                      {
                         SHWFS_LOG("Failed to send ACK to AEON\n");
                      }
                }
                break;
              case SHWFS_FCNTL_RESET_ALL_FILE_HANDLE:
                SHWFS_FCNTL_DBG(SHWFS_FCNTL_RESET_ALL_FILE_HANDLE);
                {
                      msAPI_FCtrl_FileHandleResetAll();
                      fsMsg.actionType = SHWFS_AEON_ACK(SHWFS_FCNTL_RESET_ALL_FILE_HANDLE);
                      if(SendMail2MIPS(&fsMsg) == FALSE)
                      {
                         SHWFS_LOG("Failed to send ACK to AEON\n");
                      }
                }
                break;
              default:
                SHWFS_LOG("Seriously error, unsupported command index %d\n", fsMsg.actionType);
                break;

          }

   }while(1);

   return TRUE;
}








