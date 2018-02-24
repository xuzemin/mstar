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

#define MAPP_WMDRMPD_C

//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include "mapp_mplayer.h"
#include "mapp_wmdrmpd.h"
#include "mapp_videoplayer.h"
#include "MApp_FileBrowser.h"
#include "lib_wmdrmpd.h"
#include "msAPI_FCtrl.h"
#include "msAPI_VDPlayer_MemCfg.h"

#if ENABLE_WMDRMPD

#define WMDRMPD_DBG(x) x

/******************************************************************************/
/*                                 Enum                                                                                            */
/******************************************************************************/

//-------------------------------------------------------------------------------------------------
// Global Variables
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Local Variables
//-------------------------------------------------------------------------------------------------
static WMDRMPD_IO_CALLBACK ioCtx;

//-------------------------------------------------------------------------------------------------
// Local Function Prototypes
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Function Implementation
//-------------------------------------------------------------------------------------------------

static U8 LenOfWString(unsigned short *pStr)
{
    U8 i = 0;

    for (i = 0 ; i < 128; i++)
    {
        if (pStr[i] == 0x0)
            break;
    }

    return i;
}

static int WMDRMPD_IO_fexist(unsigned short *path)
{
    FileEntry entry;
    U8 len;

    len = LenOfWString(path);
    if (MApp_FilrBrowser_GetNameExistedInCurrent((U16 *)((void *)path), len, &entry))
    {
        return TRUE;
    }

    return FALSE;
}

static int WMDRMPD_IO_fopen(unsigned short *path, char *mode)
{
    FileEntry entry;
    U8 len;
    U8 handle;
    U8 readWrite= 0;

    mode = mode;
    len = LenOfWString(path);

    if (mode[1] == '+')
    {
        readWrite = 1;
    }

    if (MApp_FilrBrowser_GetNameExistedInCurrent((U16 *)((void *)path), len, &entry))
    {
        U8 u8OpenMode = OPEN_MODE_BINARY_FOR_READ;

        if (readWrite)
        {
            u8OpenMode = OPEN_MODE_BINARY_FOR_READ_WRITE;
        }
        handle = msAPI_FCtrl_FileOpen(&entry, u8OpenMode);
        if (handle != INVALID_FILE_HANDLE)
        {
            printf("[WMDRMPD_IO_fopen]File successfully opened at handle:%d!!\n", handle);
            return handle;
        }
    }
    else
    {
        handle = MApp_FileBrowser_OpenNewFileForWrite((U16 *)((void *)path), len);
        if (handle != INVALID_FILE_HANDLE)
        {
            printf("[WMDRMPD_IO_fopen]File successfully opened at handle:%d!!\n", handle);
            return handle;
        }
    }
    printf("[N51FS] Open failed!!\n");
    return -1;
}

static int WMDRMPD_IO_fclose(int fp)
{
    printf("WMDRMPD_IO_fclose: handle = %d\n", fp);
    msAPI_FCtrl_FileClose((U8)fp);

    return 0;
}

static int WMDRMPD_IO_fread(void *ptr, int len, int stream)
{
    int read;

    read = msAPI_FCtrl_FileRead((U8)stream, (U32)ptr, len);

    return (len - read);
}

static int WMDRMPD_IO_fwrite(void *ptr, int len, int stream)
{
    int write;

    write = msAPI_FCtrl_FileWrite((U8)stream, (U32)ptr, len);

    return (len - write);
}

static int WMDRMPD_IO_fseek(int stream, long offset, int whence)
{
    return msAPI_FCtrl_FileSeek(stream, (U32)offset, (EN_FILE_SEEK_OPTION)whence);
}

static int WMDRMPD_IO_flength(int stream)
{
    return (int)msAPI_FCtrl_FileLength((U8)stream);
}

static long WMDRMPD_IO_ftell(int stream)
{
    return (long)msAPI_FCtrl_FileTell((U8)stream);
}

void WMDRMPD_LicenseChallengeReq(void *pData, int size)
{
    pData = pData;
    size = size;
    printf("LicenseChallengeReq->\n");
}

BOOLEAN MApp_WMDRMPD_Initialize(enumWMDRMPDMediaType type)
{
    WMDRMPD_DBG(printf("MApp_WMDRMPD_Initialize->\n"));

    ioCtx.fexist = WMDRMPD_IO_fexist;
    ioCtx.fopen = WMDRMPD_IO_fopen;
    ioCtx.fclose = WMDRMPD_IO_fclose;
    ioCtx.fread = WMDRMPD_IO_fread;
    ioCtx.fwrite = WMDRMPD_IO_fwrite;
    ioCtx.fseek = WMDRMPD_IO_fseek;
    ioCtx.flength = WMDRMPD_IO_flength;
    ioCtx.ftell = WMDRMPD_IO_ftell;

    if (type == E_WMDRMPD_MEDIA_TYPE_WMA)
    {
        WMDRMPD_Initialize(NULL);
    }
    else if (type == E_WMDRMPD_MEDIA_TYPE_WMV)
    {
        U32 u32Addr;

        if (MApp_VDPlayer_WMDRMPD_QueryShareMemoryAddr(&u32Addr))
        {
            WMDRMPD_Initialize(u32Addr);
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        return FALSE;
    }

    WMDRMPD_InitIoCallback(&ioCtx);

    return TRUE;
}

BOOLEAN MApp_WMDRMPD_Finalize(void)
{
    WMDRMPD_Finalize();

    return TRUE;
}

enumWMDRMPDLicenseStatus MApp_WMDRMPD_GetLicense(void *pXML, int size)
{
    return (enumWMDRMPDLicenseStatus)WMDRMPD_GetLicense(pXML, size);
}

int MApp_WMDRMPD_QueryLicenseChallenge(int *size, int *urlSize)
{
    return WMDRMPD_QueryLicenseChallenge(size, urlSize);
}

int MApp_WMDRMPD_GetLicenseChallenge(void *pXML, void *pUrl, int size, int sizeUrl)
{
    return WMDRMPD_GetLicenseChallenge(pXML, pUrl, size, sizeUrl);
}

int MApp_WMDRMPD_SetLicenseResponse(void *pXML, int size)
{
    S32 i;
    U8 tmp[] = "jazz1_response.xml";
    U16 filename[128];
    FileEntry entry;
    U8 readFileHandle;
    U32 length;
    U32 *addr;

    for (i = 0; i < (S32)strlen((char *)tmp); i++)
    {
        filename[i] = (U16)tmp[i];
    }

    filename[i] = 0x0;

    if (MApp_FilrBrowser_GetNameExistedInCurrent((U16 *)filename, (U8)strlen((char *)tmp), &entry))
    {
        readFileHandle = msAPI_FCtrl_FileOpen(&entry, OPEN_MODE_BINARY_FOR_READ);
        if (readFileHandle != INVALID_FILE_HANDLE)
        {
            printf("[WMDRMPD_IO_fopen]File successfully opened at handle:%d!!\n", readFileHandle);
            return -1;
        }
    }

    length = msAPI_FCtrl_FileLength(readFileHandle);

    addr = (U32 *)((VDPLAYER_DATA_MEMORY_TYPE & MIU1) ? (VDPLAYER_DATA_ADR | MIU_INTERVAL) : (VDPLAYER_DATA_ADR));
    msAPI_FCtrl_FileRead(readFileHandle, (U32)_PA2VA((void *)((VDPLAYER_DATA_MEMORY_TYPE & MIU1) ? (VDPLAYER_DATA_ADR | MIU_INTERVAL) : (VDPLAYER_DATA_ADR))), length);

    pXML= pXML;
    size = size;

    return MApp_WMDRMPD_SetLicenseResponse((void *)addr, length);
}

int MApp_WMDRMPD_QueryKey(void *key)
{
    WMDRMPD_QueryKey(key);

    return 0;
}

int MApp_WMDRMPD_Decrypt(void *pData, int size)
{
    WMDRMPD_Decrypt(pData, size);

    return 0;
}

int MApp_WMDRMPD_UpdateLicense(void)
{
    return WMDRMPD_UpdateLicense();
}

#undef MAPP_WMDRMPD_C

#endif  // ENABLE_WMDRMPD
