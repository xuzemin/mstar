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

////////////////////////////////////////////////////////////////////////////////
//
/// @file msAPI_Font.h
/// This file includes MStar application interface for FONT.
/// @brief API for font handling
/// @author MStar Semiconductor, Inc.
//
////////////////////////////////////////////////////////////////////////////////
#define    _MSAPI_FONT_DYNAMIC_MVF_C
/******************************************************************************/
/*                              Header Files                                  */
/******************************************************************************/

// C Library
#include <stdio.h>

#include "Board.h"
#include "datatype.h"
#include "hwreg.h"

#if DYNAMIC_VECTOR_FONT_ENABLE
// Global Layer
#include "sysinfo.h"
#include "imginfo.h"

// Driver Layer
#include "drvUSB.h"
#include "GPIO.h"
#include "drvTVEncoder.h"
#include "SysInit.h"

// API Layer
#include "IOUtil.h"
#include "msAPI_Timer.h"
#include "msAPI_FCtrl.h"
//#include "msAPI_FAT.h"
#include "msAPI_MSDCtrl.h"
#include "msAPI_Memory.h"
#include "msAPI_Font.h"
#include "msAPI_OSD.h"
#include "apiXC_Sys.h"
#include "drvXC.h"
#include "MApp_FileBrowser.h"

#include "msAPI_Font_Dynamic_MVF.h"


#define DYN_MVF_DBG(y) //y
#define DYN_MVF_UNICODE_DBG(y) //y

#define CHAR_QM_UNICODE  0x003F  // char '?'  unicode is 0x003F


static BOOLEAN msAPI_DynamicMVF_SearchUnicode(U32 u32IndexFileBuffer, U16 unicode, U32 *pOffset, U16*pDataSize)
{
    U16 u16index;
    U32 u32Offset, addrTemp;
    S32 mid, low, high;

    DYN_MVF_DBG(printf("Unicode[%x]\n", unicode));

    //find the first entry which >= unicode
    low=0; high=QUICK_SERACH_INDEX_1_COUNT -1;
    do
    {
        mid = (low+high)>>1;
        addrTemp = (U32)(mid<<1); // <<1 for 2byte
        u16index = (U16)(((U8 *)u32IndexFileBuffer)[addrTemp+1]<<8 | ((U8 *)u32IndexFileBuffer)[addrTemp]);
        DYN_MVF_UNICODE_DBG(printf(" mid [%d] addr[%lx]   F_UNC[%x]\n", mid, addrTemp, u16index));

        if( u16index<unicode)
            low = mid+1;
        else if( u16index>unicode)
            high = mid-1;
        else
        {
            low = mid;
            break;
        }
    }while(low <= high);

    u16index = low;
    DYN_MVF_UNICODE_DBG(printf("index[%d]\n", u16index));

    if(u16index > QUICK_SERACH_INDEX_1_COUNT)
        return FALSE;

    //find the Sencond entry which >= unicode
    u32Offset = (U32)(u16index<<12) + QUICK_SERACH_INDEX_1_COUNT*2; // for 4K size
    low = 0; high = low + 512 -1; // 512 = 4K / 8 // 4k and 8byte
    do
    {
        mid = (low+high)>>1;
        addrTemp = u32Offset + (U32)(mid<<3); // <<3 for 8byte
        u16index = (U16)(((U8 *)u32IndexFileBuffer)[addrTemp+1]<<8 | ((U8 *)u32IndexFileBuffer)[addrTemp]);
        DYN_MVF_UNICODE_DBG(printf(" mid [%d] addr[%lx]   F_UNC[%x]\n", mid, addrTemp, u16index));

        if( u16index<unicode)
            low = mid+1;
        else if( u16index>unicode)
            high = mid-1;
        else
        {
            low = mid;
            break;
        }
    }while(low <= high);

    u16index = low;
    DYN_MVF_UNICODE_DBG(printf("index2[%d]\n", u16index));
    if(u16index > QUICK_SERACH_INDEX_1_COUNT *8 )
        return FALSE;

    addrTemp = u32Offset + (U32)(u16index<<3) +4 ; // <<3 for 8byte
    DYN_MVF_UNICODE_DBG(printf("addr[%lx]\n", addrTemp));

    *pOffset = (U32)(((U8 *)u32IndexFileBuffer)[addrTemp+3]<<24 | ((U8 *)u32IndexFileBuffer)[addrTemp+2]<<16 |((U8 *)u32IndexFileBuffer)[addrTemp+1]<<8 | ((U8 *)u32IndexFileBuffer)[addrTemp]);
    addrTemp += 8; // Next 8byte;
    u32Offset = (U32)(((U8 *)u32IndexFileBuffer)[addrTemp+3]<<24 | ((U8 *)u32IndexFileBuffer)[addrTemp+2]<<16 |((U8 *)u32IndexFileBuffer)[addrTemp+1]<<8 | ((U8 *)u32IndexFileBuffer)[addrTemp]);
    *pDataSize = u32Offset - *pOffset;

    DYN_MVF_DBG(printf("pOffset[%lx], pDataSize[%lx]\n", *pOffset, *pDataSize));
    return TRUE;

}


U32 msAPI_DynamicMVF_Generate_MVF(U8 u8SrcFileHandleNo, U32 dstBuffer,  U16 *tblUnicode, U16 tableSize)
{
    U16  curU16Val;
    U16   fontCnt;

    U16 numberGlyElm;
    U16  dataSize;
    U32 offset;

    U32 index, curWRAddr, curOffset;

    fontCnt = 0;
    curWRAddr = dstBuffer;
    curOffset = 0;

#if 1
    {
        MS_VE_OUTPUT_CTRL OutputCtrl;

        // disable VE
        OutputCtrl.bEnable = FALSE;
        MDrv_VE_set_output_ctrl(&OutputCtrl);
    }
    // disable DNR by enabling blue screen
    msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLUE, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
    // enforce the screen color is blue
    //MDrv_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLUE, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
#endif

    msAPI_FCtrl_FileSeek(u8SrcFileHandleNo, 0, FILE_SEEK_SET);
    if(msAPI_FCtrl_FileRead(u8SrcFileHandleNo, (U32)( &curU16Val), 2) !=0)
    {
        printf("Read source file failed!");
        return 0;
    }
    curOffset += 2;

#if (MPS_VER_SEL == MPS_VER1)
    if(curU16Val != (U16)MVF_PLUS_FILE_MAGIC_NUMBER)
    {
        printf("%x<->%x\n", curU16Val, (U16)MVF_PLUS_FILE_MAGIC_NUMBER_1);
        printf("Source File Magic Error");
        return 0;
    }
#else
    if(curU16Val != (U16)MVF_PLUS_FILE_MAGIC_NUMBER_1)
    {
        printf("%x<->%x\n", curU16Val, (U16)MVF_PLUS_FILE_MAGIC_NUMBER_1);
        printf("Source File Magic Error");
        return 0;
    }
    if(msAPI_FCtrl_FileRead(u8SrcFileHandleNo, (U32)( &curU16Val), 2) !=0)
    {
        printf("Read source file failed!");
        return 0;
    }
    curOffset += 2;
    if(curU16Val != (U16)MVF_PLUS_FILE_MAGIC_NUMBER_2)
    {
        printf("%x<->%x\n", curU16Val, (U16)MVF_PLUS_FILE_MAGIC_NUMBER_1);
        printf("Source File Magic Error");
        return 0;
    }
#endif

    curU16Val = (U16)(MVF_FILE_FORMAT_VER_1);
    MDrv_Sys_CopyVAR2MIU(&curU16Val, curWRAddr, 2);
    curWRAddr += 2;

    //read version number
    if(msAPI_FCtrl_FileRead(u8SrcFileHandleNo, (U32)( &curU16Val), 2) != 0)
    {
        printf("Read source file failed!");
        return 0;
    }
    curOffset += 2;
    if(curU16Val!=(U16)MVF_FILE_FORMAT_VER_2&& curU16Val!=(U16)MVF_FILE_FORMAT_VER_2_7052)
    {
        printf("Unsupported MVF PLUS version!");
        return 0;
    }
    MDrv_Sys_CopyVAR2MIU(&curU16Val, curWRAddr, 2);
    curWRAddr += 2;

    if(msAPI_FCtrl_FileRead(u8SrcFileHandleNo, (U32)(&numberGlyElm), 2) != 0)
    {
        printf("Read source file failed!");
        return 0;
    }
    curOffset += 2;
    curWRAddr += 2;//will feed numberGlyElm later, currently just skip it

    if(numberGlyElm==0 || numberGlyElm&0x8000)
    {
        printf("Invalid source file!");
        return 0;
    }
    if(numberGlyElm > MAX_FONT_NUMBER)
    {
        printf("Font Cnt is larger than 32767, can not support!");
        return 0;
    }

    DYN_MVF_DBG(printf("\r\n DYNAXIC_MVF_FONT_BUFFER_ADR:[%lx]", DYNAXIC_MVF_FONT_BUFFER_ADR));
    DYN_MVF_DBG(printf("\r\n MVF_GEN_INDEX_TBL_BUFFER_ADR:[%lx]", MVF_GEN_INDEX_TBL_BUFFER_ADR));

    //msAPI_FCtrl_FileSeek(u8SrcFileHandleNo, 0, FILE_SEEK_SET);
    if(msAPI_FCtrl_FileRead(u8SrcFileHandleNo, MVF_GEN_INDEX_TBL_BUFFER_ADR, ((U32)numberGlyElm*8+8+QUICK_SERACH_INDEX_1_COUNT*2)) != 0)// *2 for Unicode is 2byte
    {
        printf("Read fast index table failed!");
        return 0;
    }
    DYN_MVF_DBG(printf("read file size[%lx + 0x80]\n", (U32)numberGlyElm*8+8));

    for( index=0, fontCnt = 0; index<tableSize; index++)
    {
        // End font load
        if(tblUnicode[index] == 0)
            break;

        // if search unicode fail, will insert char "?"
        if( !msAPI_DynamicMVF_SearchUnicode(MVF_GEN_INDEX_TBL_BUFFER_ADR,  tblUnicode[index], &offset, &dataSize))
        {
            printf("search unicode fail, will insert char '?' !\n");
            msAPI_DynamicMVF_SearchUnicode(MVF_GEN_INDEX_TBL_BUFFER_ADR,  CHAR_QM_UNICODE, &offset, &dataSize);
        }

        if( !msAPI_FCtrl_FileSeek(u8SrcFileHandleNo, offset, FILE_SEEK_SET) )
        {
            printf("Seek src file error!");
            return 0;
        }

        if(msAPI_FCtrl_FileRead(u8SrcFileHandleNo, curWRAddr, dataSize) != 0)
        {
            printf("Read fast index table failed!");
            return 0;
        }

        curWRAddr += dataSize;
        fontCnt++;
    }

    MDrv_Sys_CopyVAR2MIU(&fontCnt, dstBuffer+4, 2);

    DYN_MVF_DBG(printf("Size[%lx]", curWRAddr-dstBuffer));

    return curWRAddr-dstBuffer;
}
/******************************************************************************/
/// Read font Lib file on Usb
/// @return BOOLEAN:
///- TRUE: Success
///- FALSE: Fail
/******************************************************************************/
U32 msAPI_LoadUsbFontLib2MVF(U16 *tblUnicode, U32 tableSize)
{
    U32 uRet;
    static FileEntry stFileEntry;

   U8  fontLibFileName[] = { 'u', 0x00, 's', 0x00, 'b', 0x00, '_', 0x00, 'f', 0x00, 'o', 0x00, 'n', 0x00, 't', 0x00, '.', 0x00, 'm', 0x00, 'p', 0x00, 's', 0x00, 0x00, 0x00};


    if(MApp_FilrBrowser_GetNameExistedInCurrent(  (U16*)&fontLibFileName[0], 12/*(U16*)MVF_FILE_NAME ,  (U8)strlen(MVF_FILE_NAME)*/,  &stFileEntry ))
    {
        U8 handle = msAPI_FCtrl_FileOpen(  &stFileEntry ,   OPEN_MODE_FOR_READ ) ;
        if(handle !=  INVALID_FILE_HANDLE)
        {
            DYN_MVF_DBG(printf("successfully open font library(*.mps) file.\n"));
            msAPI_Timer_ResetWDT();
            uRet = msAPI_DynamicMVF_Generate_MVF(handle, DYNAXIC_MVF_FONT_BUFFER_ADR, tblUnicode, tableSize);
            msAPI_FCtrl_FileClose(handle);
        }
        else
        {
            DYN_MVF_DBG(printf("Failed to open font lib file.\n"));
            uRet = 0;
        }
    }
    else
    {
        DYN_MVF_DBG(printf("Failed to find font lib file.\n"));
        uRet = 0;
    }

    DYN_MVF_DBG(printf("finish!!\n"));
    return uRet;

}


#endif
