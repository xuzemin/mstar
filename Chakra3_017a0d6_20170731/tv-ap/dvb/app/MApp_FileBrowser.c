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

#define  MAPP_FILEBROWSER_C

#include "datatype.h"
#include "debug.h"

#include <stdio.h>
#include <string.h>
#include "sysinfo.h"

#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"

#include "MsTypes.h"
#include "drvBDMA.h"
#include "IOUtil.h"
#include "msAPI_Memory.h"
#include "msAPI_MIU.h"
#include "msAPI_FCtrl.h"

#include "mapp_mplayer.h"
#include "MApp_FileBrowser.h"

#define FB_DBG(x)   //x
#define MAX_SUPPORT_FileBrowser_WIN1_LOCK_COUNT 1
#define MAPP_FILEBROWSER_DIR_NAME_CACHE_SIZE    0x1000UL

typedef struct
{
    U8 u8EnvId;
    FileEntry fileEntry;
    DirEntryStruct dirEntryStruct;
    S32 s32EntryIdx;
} FileBrowserEnv;

//static U8 u8FileBrowser_Win1LockCount = 0;
//static U16 u16FileBrowser_Win1BaseArray[1];

static BOOLEAN _bFilsBrowserInited = FALSE;

static U8 u8CurrentEnvHandle = INVALID_BROWSER_HANDLE;

//static FileBrowserEnv fileBrowserEnv[FS_ENVIRONMENT_NUM];
static FileBrowserEnv fileBrowserEnv[4];

/*
static U8 _getU16StringLength(U16* pString)
{
    U8 i=0;
    for(i=0;i<255;i++)
    {
        if(*(pString+i)==0)
            return i;
    }
    __ASSERT(0);//running too far!!
    return 0;
}
*/
#if KEEP_UNUSED_FUNC
void _printU16FileNameToU8(U32 miuAddress,U8 len)
{
    U8 i=0;
    U8 tmpBuff[256];


    len=(len>127?127:len);
    memcpy(&tmpBuff[0], (U8*)miuAddress, 2*len);

    for(i=0;i<len;i++)
    {
        tmpBuff[i]=tmpBuff[i*2+1];
    }
    tmpBuff[len]=0;
    printf("%s",tmpBuff);

    #if 0
    if (tmpBuff != NULL)
    {
        msAPI_Memory_Free(tmpBuff, BUF_ID_FILEBROWER);
        tmpBuff = NULL;
    }
    #endif

}
#endif

#if KEEP_UNUSED_FUNC
static void _MApp_FileBrowser_UpdateCurrentDirectoryName(U8 enid,U32 MIUAddr,U8 charLen,EN_ENTRY_TYPE dirType,BOOLEAN toROOT)
{
    U16 totalLen;
    U16 lastLen;
    U16* pu16;
    U16* pBuff;
    U16* pNameBuff;
    U8 i=0;

    if(enid>FS_ENVIRONMENT_NUM)
    {
        __ASSERT(0);
        return;
    }

    pu16=(U16 *)_PA2VA((((MAPP_FILEBROWSER_CURRENT_DIR_NAME_CACHE_MEMORY_TYPE & MIU1) ? (MAPP_FILEBROWSER_CURRENT_DIR_NAME_CACHE_ADR | MIU_INTERVAL) : (MAPP_FILEBROWSER_CURRENT_DIR_NAME_CACHE_ADR))+enid*MAPP_FILEBROWSER_DIR_NAME_CACHE_SIZE));
    pNameBuff=pu16+2;

    if(toROOT)//root
    {
        memset((U8*)pNameBuff,0,4096-2);
        *pNameBuff=(U16)'\\';

        totalLen=1;
        lastLen=0;

        *pu16=totalLen;
        *(pu16+1)=lastLen;

        return;
    }

    //not root
    totalLen=*pu16;
    lastLen=*(pu16+1);

    if(totalLen+charLen>(4096-4))// 0 is totalLen, 1 is lastLen, 4095 is 0 and an U16 for '\\'
    {
        charLen=4096-4-totalLen;
    }

    pBuff=(U16*)msAPI_Memory_Allocate(charLen*2, BUF_ID_FILEBROWER);
    if(pBuff==NULL)
    {
        __ASSERT(0);
        return;
    }

    memcpy(pBuff, (void*)MIUAddr, charLen*2);

    for(i=0;i<charLen;i++)
    {
        if(*(pBuff+i)==0)
        {
            charLen=i;
            break;
        }
    }

    if(dirType==ENTRY_TYPE_DIR_DOTDOT)
    {
        if(lastLen>0)
        {
            //U8 i=0;
            totalLen-=lastLen;
            memset((U8*)&pNameBuff[totalLen],0,lastLen*2);

            if(totalLen==1)
            {
                lastLen=0;
            }
            else
            {
                pNameBuff[--totalLen]=0;
                for(i=0;(i<255&&i<totalLen);i++)
                {
                    if( pNameBuff[totalLen-1-i] == (U16)'\\')
                        break;
                }

                lastLen=i;
            }

            *pu16=totalLen;
            *(pu16+1)=lastLen;
        }
    }
    else
    {
        if(lastLen>0)
        {
            pNameBuff[totalLen++]=(U16)'\\';
        }

        memcpy((U8*)&pNameBuff[totalLen],(U8*)pBuff,charLen*2);
        totalLen+=charLen;
        lastLen=charLen;

        *pu16=totalLen;
        *(pu16+1)=lastLen;

        pNameBuff[totalLen]=0;
    }

    if (pBuff != NULL)
    {
        msAPI_Memory_Free(pBuff, BUF_ID_FILEBROWER);
        pBuff = NULL;
    }

}
#endif

//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------
#define _DOT_ 0x002e // the dot in file name, 2 byte. For example, xxxxxxx.avi
#define _SPACE_ 0x0020
#define _QUOTE_ 0x0022
#define _SLASH_ 0x002f
#define _BACK_SLASH_ 0x005c
#define _LEFT_BRACKET_ 0x005b
#define _RIGHT_BRACKET_ 0x005d
#define _SEMICOLON_ 0x003b
#define _COLON_ 0x003a
#define _EQUAL_MARK_ 0x003d
#define _COMMA_ 0x002c
#define _END_OF_STRING_ 0x0000

#define CORRECT_CHAR(C) ((C != _SPACE_) \
                            && (C != _QUOTE_) \
                            && (C != _SLASH_) \
                            && (C != _BACK_SLASH_) \
                            && (C != _LEFT_BRACKET_) \
                            && (C != _RIGHT_BRACKET_) \
                            && (C != _SEMICOLON_) \
                            && (C != _COLON_) \
                            && (C != _EQUAL_MARK_) \
                            && (C != _COMMA_))


void _MApp_FileBrowser_ConvertLongNameToShortName(EN_ENTRY_TYPE bType, U16 *pu16LongName, U16 u16LongNameLen, S8 *ps8ShortName, S8 *ps8ShortNameExt)
{
    U16 u16j;
    S32 s32i, s32Dot = u16LongNameLen - 1;

    memset(ps8ShortName, ' ', 8);
    memset(ps8ShortNameExt, ' ', 3);

    switch (bType)
    {
        case ENTRY_TYPE_FILE:
            for ( ; s32Dot >= 0; s32Dot--)
            {
                if (pu16LongName[s32Dot] == _DOT_)
                {
                    break;
                }
            }

            if (s32Dot > 0) // dot (.) found and dot (.) isn't the first character --> non linux like system
            {
                // construct extension name
                s32i = s32Dot + 1;
                for (u16j = 0; (s32i < u16LongNameLen) && (u16j < 3); s32i++, u16j++)
                {
				#if 0//N51FS
                    pu8Name = (U8 *)&pu16LongName[s32i];
                    ps8ShortNameExt[u16j] = pu8Name[0];
				#endif
                    ps8ShortNameExt[u16j] = (S8)pu16LongName[s32i];
                }

                //N51FS #to upper case
                strupr2((U8*)ps8ShortNameExt,3);
            }

            // construct entry name

            for (s32i = 0, u16j = 0; (s32i < s32Dot) && (u16j < 8); s32i++,u16j++)
            {
                if (CORRECT_CHAR(pu16LongName[s32i]))
                {
                    ps8ShortName[s32i] = (S8)pu16LongName[s32i];
                }
            }

            //N51FS #to upper case
            strupr2((U8*)ps8ShortName,8);
            break;

        case ENTRY_TYPE_DIR_DOT:
            ps8ShortName[0]='.';
            break;

        case ENTRY_TYPE_DIR_DOTDOT:
            ps8ShortName[0]='.';
            ps8ShortName[1]='.';
            break;

        case ENTRY_TYPE_DIR:
            for (s32i = 0; (s32i < u16LongNameLen) && (s32i < 8); s32i++)
            {
                ps8ShortName[s32i] = (S8)pu16LongName[s32i];
            }
            strupr2((U8*)ps8ShortName,8);
            break;
        case ENTRY_TYPE_LAST:
        case ENTRY_TYPE_NULL:
        default:
            break;
    }
}

BOOLEAN _MApp_FileBrowser_NextEntry(void)
{
    BOOLEAN result=FALSE;
    FileEntry entryToSet;
    BOOLEAN notRoot=TRUE;

    notRoot=!msAPI_FCtrl_DirectoryIsCurrentRoot(fileBrowserEnv[u8CurrentEnvHandle].u8EnvId);

    if(fileBrowserEnv[u8CurrentEnvHandle].s32EntryIdx==-1)
    {
        result=msAPI_FCtrl_DirectoryGetDOT(fileBrowserEnv[u8CurrentEnvHandle].u8EnvId,&entryToSet);
    }
    else if(fileBrowserEnv[u8CurrentEnvHandle].s32EntryIdx==0&&notRoot)
    {
        result=msAPI_FCtrl_DirectoryGetDOTDOT(fileBrowserEnv[u8CurrentEnvHandle].u8EnvId,&entryToSet);
    }
    else
    {
        if(msAPI_FCtrl_EntryNext(fileBrowserEnv[u8CurrentEnvHandle].u8EnvId,&entryToSet)==ENTRY_NEXT_RESULT_SUCCESS)
        {
            result=TRUE;
        }
        else
        {
            result=FALSE;
        }
    }

    if(!result)
    {
        fileBrowserEnv[u8CurrentEnvHandle].fileEntry.EntryType=ENTRY_TYPE_NULL;
    }
    else
    {
        memcpy(&fileBrowserEnv[u8CurrentEnvHandle].fileEntry,&entryToSet,sizeof(FileEntry));
        fileBrowserEnv[u8CurrentEnvHandle].s32EntryIdx++;
    }

    return result;
}

void _MApp_FileBrowser_ConvertEntryToEntryStruct(FileEntry* pEntry,DirEntryStruct* pStruct,U16* pString,U8 len)
{
    if(pEntry==NULL||pEntry->EntryType==ENTRY_TYPE_NULL||pStruct==NULL)
    {
        __ASSERT(0);
        return;
    }

    memset(pStruct,0,sizeof(DirEntryStruct));
    pStruct->u32DirEntryFileLength=pEntry->EntryFileLength;

    if (pEntry->EntryType != ENTRY_TYPE_FILE)
    {
        pStruct->u8DirEntryAttrib = ENTRY_ATTRIB_DIRECTORY;
    }

    FS_TIME stTime;
    U16 u16Date, u16Time;

    msAPI_FS_ConvertSeconds2StTime(pEntry->EntrySeconds, &stTime);
    u16Date = (((stTime.u16Year-FS_DEFAULT_YEAR)&0x7F)<<9) |((stTime.u8Month&0x0F)<<5) |(stTime.u8Day&0x1F);
    u16Time = ((stTime.u8Hour&0x1F)<<11) |((stTime.u8Min&0x3F)<<5) |((stTime.u8Sec/2)&0x1F);

    pStruct->u16DirEntryDate = u16Date;
    pStruct->u16DirEntryTime = u16Time;

    //printf("~~ ");_printU16FileNameToU8((U32)(pString),len);printf("\n");

    _MApp_FileBrowser_ConvertLongNameToShortName(
            pEntry->EntryType,
            pString,
            len,
            (S8*)pStruct->ps8DirEntryName,
            (S8*)pStruct->ps8DirEntryExtName);
}

//======================================================================================

void MApp_FileBrowser_SetEnvironment(U8 u8Handle)
{
    u8CurrentEnvHandle=u8Handle;
}
U8 MApp_FileBrowser_GetEnvironment(void)
{
    return u8CurrentEnvHandle;
}

U8 MApp_FileBrowser_GetCurrentLongName(U32 MIUAddr,U8 charLen)
{
    if((u8CurrentEnvHandle>=FS_ENVIRONMENT_NUM)
            || (fileBrowserEnv[u8CurrentEnvHandle].u8EnvId==INVALID_FS_ENVIRONMENT_INDEX)
            || (fileBrowserEnv[u8CurrentEnvHandle].fileEntry.EntryType==ENTRY_TYPE_NULL))
    {
        __ASSERT(0);
        return 0;
    }

    if(fileBrowserEnv[u8CurrentEnvHandle].fileEntry.EntryType==ENTRY_TYPE_DIR_DOT)
    {
        U16 _au8String[1]={'.'};

        U8 len=sizeof(_au8String);
        len=len>(charLen*2)?(charLen*2):len;
        memcpy((void*)MIUAddr, &_au8String[0], len);
        return len/2;
    }
    else if(fileBrowserEnv[u8CurrentEnvHandle].fileEntry.EntryType==ENTRY_TYPE_DIR_DOTDOT)
    {
        U16 _au8String[2]={'.','.'};

        U8 len=sizeof(_au8String);
        len=len>(charLen*2)?(charLen*2):len;
        memcpy((void*)MIUAddr, &_au8String[0], len);
        return len/2;
    }
    else
    {
        return msAPI_FCtrl_EntryGetCurrentName(fileBrowserEnv[u8CurrentEnvHandle].u8EnvId,MIUAddr,charLen);
    }
}

U8 MApp_FileBrowser_GetLongFileNameByFileEntry(FileEntry *pEntry, U32 MIUAddr,U8 charLen)
{
    if ( (u8CurrentEnvHandle>=FS_ENVIRONMENT_NUM)
       || (fileBrowserEnv[u8CurrentEnvHandle].u8EnvId==INVALID_FS_ENVIRONMENT_INDEX)
       || (pEntry->EntryType==ENTRY_TYPE_NULL) )
    {
        __ASSERT(0);
        return 0;
    }

    if(pEntry->EntryType==ENTRY_TYPE_DIR_DOT)
    {
        U16 _au8String[1]={'.'};

        U8 len=sizeof(_au8String);
        len=len>(charLen*2)?(charLen*2):len;
        memcpy((void*)MIUAddr, &_au8String[0], len);
        return len/2;
    }
    else if(pEntry->EntryType==ENTRY_TYPE_DIR_DOTDOT)
    {
        U16 _au8String[2]={'.','.'};

        U8 len=sizeof(_au8String);
        len=len>(charLen*2)?(charLen*2):len;
        memcpy((void*)MIUAddr, &_au8String[0], len);
        return len/2;
    }
    else
    {
        BOOLEAN bShortNameOnly;
        return msAPI_FCtrl_EntryGetLongNameByFileEntry(fileBrowserEnv[u8CurrentEnvHandle].u8EnvId,
                                                       pEntry,
                                                       MIUAddr,
                                                       charLen,
                                                       &bShortNameOnly);
    }
}


BOOLEAN MApp_FileBrowser_GetCurrentShortName(U32 shortNameAddr, U32 extNameAddr)
{
    U8 u8ShortNameLen, i, u8Count;
    U8 u8ShortName[12];
    BOOLEAN bIsExtName = FALSE;
    U8 u8BaseFileName[8];
    U8 u8ExtFileName[3];

    if((u8CurrentEnvHandle>=FS_ENVIRONMENT_NUM)
            || (fileBrowserEnv[u8CurrentEnvHandle].u8EnvId==INVALID_FS_ENVIRONMENT_INDEX)
            || (fileBrowserEnv[u8CurrentEnvHandle].fileEntry.EntryType != ENTRY_TYPE_FILE))
    {
        __ASSERT(0);
        return 0;
    }

    u8ShortNameLen = msAPI_FCtrl_EntryGetShortNameByFileEntry(fileBrowserEnv[u8CurrentEnvHandle].u8EnvId, &fileBrowserEnv[u8CurrentEnvHandle].fileEntry, GET_DRAM_ADDR(&u8ShortName[0]), 12);
    if(u8ShortNameLen > 12)
    {
        __ASSERT(0);
        return 0;
    }

    u8Count = 0;
    for(i=0; i<u8ShortNameLen; i++)
    {
        if(CHAR_DOT == u8ShortName[i])
        {
            bIsExtName = TRUE;
            u8Count = 0;
            continue;
        }

        if(FALSE == bIsExtName)
        {
            u8BaseFileName[u8Count++] = u8ShortName[i];
        }
        else
        {
            u8ExtFileName[u8Count ++] = u8ShortName[i];
        }
    }
    msAPI_FS_MIU_Copy( GET_DRAM_ADDR(&u8BaseFileName[0]), shortNameAddr, 8);
    msAPI_FS_MIU_Copy( GET_DRAM_ADDR(&u8ExtFileName[0]), extNameAddr, 3);

    return TRUE;
}

BOOLEAN MApp_FilrBrowser_CheckNameExistedInCurrent(U16* pString,U8 charLen)
{
    FileEntry entry;

    if((u8CurrentEnvHandle>=FS_ENVIRONMENT_NUM) || (fileBrowserEnv[u8CurrentEnvHandle].u8EnvId==INVALID_FS_ENVIRONMENT_INDEX))
    {
        __ASSERT(0);
        return FALSE;
    }

    return msAPI_FCtrl_EntrySearchByName(fileBrowserEnv[u8CurrentEnvHandle].u8EnvId,pString,charLen,&entry);
}

#if 1//(DYNAMIC_VECTOR_FONT_ENABLE || ENABLE_WMDRMPD || ENABLE_DVD)
BOOLEAN MApp_FilrBrowser_GetNameExistedInCurrent(U16* pString,U8 charLen, FileEntry *pEntryToSet)
{

    if((u8CurrentEnvHandle>=FS_ENVIRONMENT_NUM) || (fileBrowserEnv[u8CurrentEnvHandle].u8EnvId==INVALID_FS_ENVIRONMENT_INDEX))
    {
        __ASSERT(0);
        return FALSE;
    }

    return msAPI_FCtrl_EntrySearchByName(fileBrowserEnv[u8CurrentEnvHandle].u8EnvId, pString, charLen, pEntryToSet);
}
#endif
U8 MApp_FileBrowser_OpenNewFileForWrite(U16* pString,U8 charLen)
{
    if((u8CurrentEnvHandle>=FS_ENVIRONMENT_NUM) || (fileBrowserEnv[u8CurrentEnvHandle].u8EnvId==INVALID_FS_ENVIRONMENT_INDEX))
    {
        __ASSERT(0);
        return INVALID_FILE_HANDLE;
    }

    return msAPI_FCtrl_FileCreate(fileBrowserEnv[u8CurrentEnvHandle].u8EnvId,pString,charLen,CREATE_MODE_NEW);
}

BOOLEAN MApp_FileBrowser_OpenNewFolder(U16* pString,U8 charLen)
{
    if((u8CurrentEnvHandle>=FS_ENVIRONMENT_NUM) || (fileBrowserEnv[u8CurrentEnvHandle].u8EnvId==INVALID_FS_ENVIRONMENT_INDEX))
    {
        __ASSERT(0);
        return FALSE;
    }

    return msAPI_FCtrl_DirectoryCreate(fileBrowserEnv[u8CurrentEnvHandle].u8EnvId,pString,charLen);
}

BOOLEAN MApp_FileBrowser_OpenNewFolder_And_GetFileEntry(U16* pString, U8 charLen, FileEntry *pstFileEntry)
{
    if((u8CurrentEnvHandle>=FS_ENVIRONMENT_NUM) || (fileBrowserEnv[u8CurrentEnvHandle].u8EnvId==INVALID_FS_ENVIRONMENT_INDEX))
    {
        __ASSERT(0);
        return FALSE;
    }

    return msAPI_FCtrl_DirectoryCreate_And_GetFileEntry(fileBrowserEnv[u8CurrentEnvHandle].u8EnvId,pString,charLen, pstFileEntry);
}

EN_FILE_SYSTEM_TYPE MApp_FileBrowser_GetCurrentFileSystemType()
{
    EN_FILE_SYSTEM_TYPE type=FILE_SYSTEM_TYPE_NONE;

    if((u8CurrentEnvHandle>=FS_ENVIRONMENT_NUM) || (fileBrowserEnv[u8CurrentEnvHandle].u8EnvId==INVALID_FS_ENVIRONMENT_INDEX))
    {
        __ASSERT(0);
        return FILE_SYSTEM_TYPE_NONE;
    }

    type = (EN_FILE_SYSTEM_TYPE)msAPI_FSEnv_GetEnvironment(fileBrowserEnv[u8CurrentEnvHandle].u8EnvId)->u8FileSystemType;
    return type;
}

#if 0
BOOLEAN MApp_FileBrowser_GetDirectoryDOT(FileEntry* pEntryToSet)
{
    return msAPI_FCtrl_DirectoryGetDOT(fileBrowserEnv[u8CurrentEnvHandle].u8EnvId,pEntryToSet);
}

BOOLEAN MApp_FileBrowser_GetDirectoryDOTDOT(FileEntry* pEntryToSet)
{
    return msAPI_FCtrl_DirectoryGetDOTDOT(fileBrowserEnv[u8CurrentEnvHandle].u8EnvId,pEntryToSet);
}
#endif

#if KEEP_UNUSED_FUNC
U8 MApp_FileBrowser_GetCurrentDirectoryName(U32 MIUAddr,U8 charLen)
{
    U16 lastLen;
    U16 totalLen;
    U16* pu16;
    if(charLen==0)
    return 0;

    pu16=(U16 *)_PA2VA((((MAPP_FILEBROWSER_CURRENT_DIR_NAME_CACHE_MEMORY_TYPE & MIU1) ? (MAPP_FILEBROWSER_CURRENT_DIR_NAME_CACHE_ADR | MIU_INTERVAL) : (MAPP_FILEBROWSER_CURRENT_DIR_NAME_CACHE_ADR))+fileBrowserEnv[u8CurrentEnvHandle].u8EnvId*MAPP_FILEBROWSER_DIR_NAME_CACHE_SIZE));
    totalLen=*pu16;
    lastLen=*(pu16+1);

    if(charLen>(U8)lastLen)
        charLen=(U8)lastLen;

    if(charLen>0)
    {
        memcpy((void*)MIUAddr,
            (void*)_PA2VA((((MAPP_FILEBROWSER_CURRENT_DIR_NAME_CACHE_MEMORY_TYPE & MIU1) ? (MAPP_FILEBROWSER_CURRENT_DIR_NAME_CACHE_ADR | MIU_INTERVAL) : (MAPP_FILEBROWSER_CURRENT_DIR_NAME_CACHE_ADR))+
            fileBrowserEnv[u8CurrentEnvHandle].u8EnvId*MAPP_FILEBROWSER_DIR_NAME_CACHE_SIZE)+sizeof(U16)*2+(totalLen-lastLen)*2),
            charLen*2);
    }

    return charLen;
}
#endif

BOOLEAN MApp_FileBrowser_ToFirstEntryInCurrentDirectory(void)
{
//    BOOLEAN result=FALSE;

    //N51FS # It seems an application bug that this function is called before initialization
    if((u8CurrentEnvHandle>=FS_ENVIRONMENT_NUM) || (fileBrowserEnv[u8CurrentEnvHandle].u8EnvId==INVALID_FS_ENVIRONMENT_INDEX))
    {
        __ASSERT(0);
        return FALSE;
    }

    fileBrowserEnv[u8CurrentEnvHandle].s32EntryIdx=-1;

    if(!msAPI_FCtrl_EntryFirst(fileBrowserEnv[u8CurrentEnvHandle].u8EnvId))
    {
        fileBrowserEnv[u8CurrentEnvHandle].fileEntry.EntryType=ENTRY_TYPE_NULL;
        __ASSERT(0);
        return FALSE;
    }

    return _MApp_FileBrowser_NextEntry();

}

BOOLEAN MApp_FileBrowser_ChangeToRootDirectory(void)
{
    if((u8CurrentEnvHandle>=FS_ENVIRONMENT_NUM) || (fileBrowserEnv[u8CurrentEnvHandle].u8EnvId==INVALID_FS_ENVIRONMENT_INDEX))
    {
        __ASSERT(0);
        return FALSE;
    }

     if(!msAPI_FCtrl_DirectoryChangeToRoot(fileBrowserEnv[u8CurrentEnvHandle].u8EnvId))
     {
        __ASSERT(0);
        return FALSE;
     }

    #if 0//no used
     _MApp_FileBrowser_UpdateCurrentDirectoryName(fileBrowserEnv[u8CurrentEnvHandle].u8EnvId, 0, 0, ENTRY_TYPE_DIR,TRUE);
    #endif

     return MApp_FileBrowser_ToFirstEntryInCurrentDirectory();
}

U8 MApp_FileBrowser_Init(U16 driveIndex)
{
    U8 u8Idx;

    for (u8Idx = 0; u8Idx < FS_ENVIRONMENT_NUM; u8Idx++)
    {
        fileBrowserEnv[u8Idx].u8EnvId = INVALID_FS_ENVIRONMENT_INDEX;
        fileBrowserEnv[u8Idx].s32EntryIdx = -1;
        fileBrowserEnv[u8Idx].fileEntry.EntryType = ENTRY_TYPE_NULL;
    }

    u8CurrentEnvHandle = INVALID_BROWSER_HANDLE;
    _bFilsBrowserInited = TRUE;
    FB_DBG(printf("MApp_FileBrowser Init!!\n"));

    u8Idx = MApp_FileBrowser_Create(driveIndex);
    if (u8Idx != INVALID_BROWSER_HANDLE)
    {
        MApp_FileBrowser_SetEnvironment(u8Idx);
    }
    return u8Idx;
}

void MApp_FileBrowser_DeInit(void)
{
    U8 u8Idx;

    for (u8Idx = 0; u8Idx < FS_ENVIRONMENT_NUM; u8Idx++)
    {
        if ((_bFilsBrowserInited == TRUE) && (fileBrowserEnv[u8Idx].u8EnvId != INVALID_FS_ENVIRONMENT_INDEX))
        {
            msAPI_FSEnv_UnRegister(fileBrowserEnv[u8Idx].u8EnvId);
        }

        fileBrowserEnv[u8Idx].u8EnvId = INVALID_FS_ENVIRONMENT_INDEX;
        fileBrowserEnv[u8Idx].s32EntryIdx = -1;
        fileBrowserEnv[u8Idx].fileEntry.EntryType = ENTRY_TYPE_NULL;
    }

    u8CurrentEnvHandle = INVALID_BROWSER_HANDLE;
    _bFilsBrowserInited = FALSE;
    FB_DBG(printf("MApp_FileBrowser DeInit!!\n"));
}

U8 MApp_FileBrowser_Create(U16 driveIndex)
{
    U8 u8NewHandle, u8OldHandle = u8CurrentEnvHandle;

    FB_DBG(printf("MApp_FileBrowser Create!!\n"));
    if(driveIndex>0xFF)//can't support drive Index bigger than 0xFF
    {
        __ASSERT(0);
        return INVALID_BROWSER_HANDLE;
    }

    if (_bFilsBrowserInited == FALSE)
    {
        for (u8NewHandle = 0; u8NewHandle < FS_ENVIRONMENT_NUM; u8NewHandle++)
        {
            fileBrowserEnv[u8NewHandle].u8EnvId = INVALID_FS_ENVIRONMENT_INDEX;
            fileBrowserEnv[u8NewHandle].s32EntryIdx = -1;
            fileBrowserEnv[u8NewHandle].fileEntry.EntryType = ENTRY_TYPE_NULL;
        }

        u8CurrentEnvHandle = INVALID_BROWSER_HANDLE;
        _bFilsBrowserInited = TRUE;
    }

    for (u8NewHandle = 0; u8NewHandle < FS_ENVIRONMENT_NUM; u8NewHandle++)
    {
        if (fileBrowserEnv[u8NewHandle].u8EnvId == INVALID_FS_ENVIRONMENT_INDEX)
        {
            if ((fileBrowserEnv[u8NewHandle].u8EnvId = msAPI_FSEnv_Register(driveIndex)) == INVALID_FS_ENVIRONMENT_INDEX)
            {
                __ASSERT(0);
                return INVALID_BROWSER_HANDLE;
            }

            u8CurrentEnvHandle = u8NewHandle;
            if (!MApp_FileBrowser_ChangeToRootDirectory())
            {
                __ASSERT(0);

                msAPI_FSEnv_UnRegister(fileBrowserEnv[u8NewHandle].u8EnvId);
                fileBrowserEnv[u8NewHandle].u8EnvId = INVALID_FS_ENVIRONMENT_INDEX;
                u8CurrentEnvHandle = u8OldHandle;
                return INVALID_BROWSER_HANDLE;
            }

            break;
        }
    }

    u8CurrentEnvHandle = u8OldHandle;
    if (u8NewHandle == FS_ENVIRONMENT_NUM)
    {
        return INVALID_BROWSER_HANDLE;
    }

    return u8NewHandle;
}

void MApp_FileBrowser_Destroy(U8 u8Handle)
{
    FB_DBG(printf("MApp_FileBrowser Destory !!\n"));
    if ((u8Handle < FS_ENVIRONMENT_NUM) && (fileBrowserEnv[u8Handle].u8EnvId != INVALID_FS_ENVIRONMENT_INDEX))
    {
        msAPI_FSEnv_UnRegister(fileBrowserEnv[u8Handle].u8EnvId);
        fileBrowserEnv[u8Handle].u8EnvId = INVALID_FS_ENVIRONMENT_INDEX;
        fileBrowserEnv[u8Handle].s32EntryIdx = -1;
        fileBrowserEnv[u8Handle].fileEntry.EntryType = ENTRY_TYPE_NULL;
    }
}

BOOLEAN MApp_FileBrowser_ChangeDrive(U8 driveIndex)
{
    UNUSED(driveIndex);
    __ASSERT(0);
    return FALSE;
}

DirEntryStruct * MApp_FileBrowser_GetCurrentDirEntry(void)
{
    U16 aString[256];
    U8 len;

    if((!_bFilsBrowserInited)
            || (u8CurrentEnvHandle>=FS_ENVIRONMENT_NUM)
            || (fileBrowserEnv[u8CurrentEnvHandle].u8EnvId==INVALID_FS_ENVIRONMENT_INDEX)
            || (fileBrowserEnv[u8CurrentEnvHandle].fileEntry.EntryType==ENTRY_TYPE_NULL))
    {
        __ASSERT(0);
        return NULL;
    }

    if(fileBrowserEnv[u8CurrentEnvHandle].fileEntry.EntryType==ENTRY_TYPE_DIR_DOT)
    {
        len=1;
        aString[0]='.';
        aString[1]=0;
    }
    else if(fileBrowserEnv[u8CurrentEnvHandle].fileEntry.EntryType==ENTRY_TYPE_DIR_DOTDOT)
    {
        len=2;
        aString[0]='.';
        aString[1]='.';
        aString[2]=0;
    }
    else
    {
        len=MApp_FileBrowser_GetCurrentLongName((U32)(&aString[0]),255);
    }

    _MApp_FileBrowser_ConvertEntryToEntryStruct(&fileBrowserEnv[u8CurrentEnvHandle].fileEntry,&fileBrowserEnv[u8CurrentEnvHandle].dirEntryStruct,&aString[0],len);

    return &fileBrowserEnv[u8CurrentEnvHandle].dirEntryStruct;
}

DirEntryStruct * MApp_FileBrowser_GetNextDirEntry(U16 NextEntryNo)
{
    if((u8CurrentEnvHandle>=FS_ENVIRONMENT_NUM) || (fileBrowserEnv[u8CurrentEnvHandle].u8EnvId==INVALID_FS_ENVIRONMENT_INDEX))
    {
        __ASSERT(0);
        return NULL;
    }

    if(NextEntryNo==0)
    {
       return MApp_FileBrowser_GetCurrentDirEntry();
    }

    while(NextEntryNo)
    {
        if(!_MApp_FileBrowser_NextEntry())
        {
            return NULL;
        }
            NextEntryNo--;
    }

    return MApp_FileBrowser_GetCurrentDirEntry();
}

BOOLEAN MApp_FileBrowser_GetCurrentFileEntry(FileEntry* pEntryToSet)
{
    if((u8CurrentEnvHandle>=FS_ENVIRONMENT_NUM)
            || (fileBrowserEnv[u8CurrentEnvHandle].u8EnvId==INVALID_FS_ENVIRONMENT_INDEX)
            || (fileBrowserEnv[u8CurrentEnvHandle].fileEntry.EntryType==ENTRY_TYPE_NULL))
    {
        __ASSERT(0);
        return FALSE;
    }

    memcpy(pEntryToSet,&fileBrowserEnv[u8CurrentEnvHandle].fileEntry,sizeof(FileEntry));

    return TRUE;
}

DirEntryStruct * MApp_FileBrowser_GetPrevDirEntry(U16 PrevEntryNo)
{
    if((u8CurrentEnvHandle>=FS_ENVIRONMENT_NUM) || (fileBrowserEnv[u8CurrentEnvHandle].u8EnvId==INVALID_FS_ENVIRONMENT_INDEX))
    {
        __ASSERT(0);
        return NULL;
    }

    if(PrevEntryNo==0)
    {
       return MApp_FileBrowser_GetCurrentDirEntry();
    }
    else if(PrevEntryNo!=1)
    {
        __ASSERT(0);
        return NULL;
    }

    __ASSERT(0);//Not Implemented Yet
    return NULL;
}

U32 MApp_FileBrowser_GetCurrentLength(void)
{
    if((u8CurrentEnvHandle>=FS_ENVIRONMENT_NUM) || (fileBrowserEnv[u8CurrentEnvHandle].u8EnvId==INVALID_FS_ENVIRONMENT_INDEX))
    {
        __ASSERT(0);
        return -1;
    }

    return fileBrowserEnv[u8CurrentEnvHandle].fileEntry.EntryFileLength;
}

LongLong  MApp_FileBrowser_GetCurrentLength_LongLong(void)
{
    LongLong size;
    size.Hi=0;
    size.Lo=0;

    if((u8CurrentEnvHandle>=FS_ENVIRONMENT_NUM) || (fileBrowserEnv[u8CurrentEnvHandle].u8EnvId==INVALID_FS_ENVIRONMENT_INDEX))
    {
        __ASSERT(0);
        return size;
    }

    return (fileBrowserEnv[u8CurrentEnvHandle].fileEntry.FileLength);
}

BOOLEAN MApp_FileBrowser_EnterDirectory(S16 EntryIndex)
{
    if((u8CurrentEnvHandle>=FS_ENVIRONMENT_NUM) || (fileBrowserEnv[u8CurrentEnvHandle].u8EnvId==INVALID_FS_ENVIRONMENT_INDEX))
    {
        __ASSERT(0);
        return FALSE;
    }

    /*[01]go to given entry ===========================================================*/
    if(EntryIndex>0)
    {
        while((EntryIndex--)>0)
        {
            if(!_MApp_FileBrowser_NextEntry())
            {
                __ASSERT(0);
                return FALSE;
            }
        }
    }
    else if(EntryIndex<0)
    {
        __ASSERT(0);//Not Implemented
        return FALSE;
    }

    /*[02]enter directory =============================================================*/
    if(fileBrowserEnv[u8CurrentEnvHandle].fileEntry.EntryType==ENTRY_TYPE_DIR||fileBrowserEnv[u8CurrentEnvHandle].fileEntry.EntryType==ENTRY_TYPE_DIR_DOTDOT)
    {
        if(!msAPI_FCtrl_DirectoryChange(fileBrowserEnv[u8CurrentEnvHandle].u8EnvId,&fileBrowserEnv[u8CurrentEnvHandle].fileEntry))
        {
            __ASSERT(0);
            return FALSE;
        }

    #if 0//no used
        {
        U16 aString[128];

        MApp_FileBrowser_GetCurrentLongName((U32)(&aString[0]),127);
        _MApp_FileBrowser_UpdateCurrentDirectoryName(fileBrowserEnv[u8CurrentEnvHandle].u8EnvId, (U32)(&aString[0]),127,fileBrowserEnv[u8CurrentEnvHandle].fileEntry.EntryType,FALSE);
        }
    #endif

        return TRUE;

    }
    /*[02-1]enter file ================================================================*/
    else
    {
        return FALSE;
    }
}

BOOLEAN MApp_FileBrowser_EnterDirectoryToContained(FileEntry *pFileEntry)
{
    if((u8CurrentEnvHandle>=FS_ENVIRONMENT_NUM) || (fileBrowserEnv[u8CurrentEnvHandle].u8EnvId==INVALID_FS_ENVIRONMENT_INDEX))
    {
        __ASSERT(0);
        return FALSE;
    }

    if(!msAPI_FCtrl_DirectoryChangeToContained(fileBrowserEnv[u8CurrentEnvHandle].u8EnvId,pFileEntry))
    {
        __ASSERT(0);
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

BOOLEAN MApp_FileBrowser_DirectoryChange(FileEntry *pFileEntry)
{
    if((u8CurrentEnvHandle>=FS_ENVIRONMENT_NUM) || (fileBrowserEnv[u8CurrentEnvHandle].u8EnvId==INVALID_FS_ENVIRONMENT_INDEX))
    {
        __ASSERT(0);
        return FALSE;
    }

    if(!msAPI_FCtrl_DirectoryChange(fileBrowserEnv[u8CurrentEnvHandle].u8EnvId,pFileEntry))
    {
        __ASSERT(0);
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

U8 MApp_FileBrowser_EnterFile(S16 EntryIndex)
{
    U8 u8HandleNo;

    if((u8CurrentEnvHandle>=FS_ENVIRONMENT_NUM) || (fileBrowserEnv[u8CurrentEnvHandle].u8EnvId==INVALID_FS_ENVIRONMENT_INDEX))
    {
        __ASSERT(0);
        return FALSE;
    }

    /*[01]go to given entry ===========================================================*/
    if(EntryIndex>0)
    {
        while((EntryIndex--)>0)
        {
            if(!_MApp_FileBrowser_NextEntry())
            {
                __ASSERT(0);
                return FALSE;
            }
        }
    }
    else if(EntryIndex<0)
    {
        __ASSERT(0);//Not Implemented
        return FALSE;
    }

    /*[02-1]enter directory ===========================================================*/
     if(fileBrowserEnv[u8CurrentEnvHandle].fileEntry.EntryType!=ENTRY_TYPE_FILE)
    {
        return INVALID_FILE_HANDLE;
    }
    /*[02-2]enter file ================================================================*/
    else
    {
        u8HandleNo = msAPI_FCtrl_FileOpen(&fileBrowserEnv[u8CurrentEnvHandle].fileEntry, OPEN_MODE_FOR_READ);
        if(u8HandleNo == INVALID_FILE_HANDLE)
        {
            __ASSERT(0);
            return u8HandleNo;
        }
    }

    return u8HandleNo;
}

BOOLEAN MApp_FileBrowser_DeleteFile(S16 EntryIndex)
{
    if((u8CurrentEnvHandle>=FS_ENVIRONMENT_NUM) || (fileBrowserEnv[u8CurrentEnvHandle].u8EnvId==INVALID_FS_ENVIRONMENT_INDEX))
    {
        __ASSERT(0);
        return FALSE;
    }

    /*[01]go to given entry ===========================================================*/
    if(EntryIndex>0)
    {
        while((EntryIndex--)>0)
        {
            if(!_MApp_FileBrowser_NextEntry())
            {
                __ASSERT(0);
                return FALSE;
            }
        }
    }
    else if(EntryIndex<0)
    {
        __ASSERT(0);//Not Implemented
        return FALSE;
    }

    /*[02-1]enter directory ===========================================================*/
     if(fileBrowserEnv[u8CurrentEnvHandle].fileEntry.EntryType!=ENTRY_TYPE_FILE)
    {
        __ASSERT(0);
        return FALSE;
    }
    /*[02-2]enter file ================================================================*/
    else
    {
        return msAPI_FCtrl_FileDelete(&fileBrowserEnv[u8CurrentEnvHandle].fileEntry);
    }
}

BOOLEAN MApp_FileBrowser_DeleteFileByFileEntry(FileEntry *pEntry)
{
    if((u8CurrentEnvHandle>=FS_ENVIRONMENT_NUM) || (fileBrowserEnv[u8CurrentEnvHandle].u8EnvId==INVALID_FS_ENVIRONMENT_INDEX))
    {
        __ASSERT(0);
        return FALSE;
    }

    /*[02-1]enter directory ===========================================================*/
     if(pEntry->EntryType!=ENTRY_TYPE_FILE)
    {
        __ASSERT(0);
        return FALSE;
    }
    /*[02-2]enter file ================================================================*/
    else
    {
        //If the drive of the selected file is the same as the drive of the current environment.
        //It is a patch. To change the environment id of the current handle if it can not support delete files in different drive.
        if(pEntry->FileSystemID == fileBrowserEnv[MApp_FileBrowser_GetEnvironment()].fileEntry.FileSystemID)
        {
            pEntry->EnvironmentID = fileBrowserEnv[MApp_FileBrowser_GetEnvironment()].u8EnvId;
        }
        return msAPI_FCtrl_FileDelete(pEntry);
    }
}

#if KEEP_UNUSED_FUNC
//=============================================
void MApp_FileBrowser_PrintCurrentName()
{
    U16* pString;
    U8 len=0;
    U8 i=0;

    pString=(U16*)msAPI_Memory_Allocate(256,BUF_ID_FILEBROWER);
    if(pString==NULL)
    {
        __ASSERT(0);
        return;
    }

    len=msAPI_FCtrl_EntryGetCurrentName(fileBrowserEnv[u8CurrentEnvHandle].u8EnvId,(U32)(pString),128);

    _printU16FileNameToU8((U32)(pString),len);printf("\n");
    msAPI_Memory_Free(pString,BUF_ID_FILEBROWER);
}
#endif

void MApp_FileBrowser_PrintCurrentEntry()
{
    MS_DEBUG_MSG(printf("currentEntry: EnvironmentID=%u, EntryID=0x%08lx, Length=%lu\n",(U8)fileBrowserEnv[u8CurrentEnvHandle].fileEntry.EnvironmentID,(U32)fileBrowserEnv[u8CurrentEnvHandle].fileEntry.EntryID,(U32)fileBrowserEnv[u8CurrentEnvHandle].fileEntry.EntryFileLength));
}


U8 MApp_FileBrowser_GetCurrentDriveName()
{
    return msAPI_FSEnv_GetEnvironment(fileBrowserEnv[u8CurrentEnvHandle].u8EnvId)->u8FileSystemID+'C';
}


#undef MAPP_FILEBROWSER_C


