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
// (MStar Confidential Information!L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define MSAPI_OCP_C

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "datatype.h"
#include "debug.h"
#include "sysinfo.h"
#include "SysInit.h"

#include "ms_decompress.h"

#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"

#include "drvCPU.h"
#include "drvSERFLASH.h"

#include "apiGOP.h"
#include "msAPI_OSD.h"
#include "msAPI_Memory.h"
#include "msAPI_Font.h"
#include "msAPI_Timer.h"
#include "msAPI_DrvInit.h"
#include "msAPI_MIU.h"
#include "msAPI_OSD_Resource.h"
#include "msAPI_OCP.h"
#include "msAPI_BDMA.h"
#include "msAPI_Flash.h"

#include "msAPI_MailBox.h"
#if 1//def ZUI
#include "InfoBlock.h"
#endif

#include "MApp_GlobalVar.h"  //20091124EL

#include "OSDcp_Bitmap_EnumIndex.h"

//=============================================================================

#define BITMAP_FMT_ARGB1555   1
#define BITMAP_FMT_ARGB4444   2
#define BITMAP_FMT_I8         3
#define BITMAP_FMT_ARGB8888   4

// BMP mem usage...
// 1. Bmp.bin
// 2. Decomp dst
// 3. Decomp tmp (src??)


#if (SW_LOAD_BMP_ON_DEMAND)
  #if( UI_SKIN_960X540XI8 == UI_SKIN_SEL )
    //The total size
    //It needs set bigger than ZUI_bitmap_SW_LOAD.bin.
    #define BMP_TMP_BUFFER_OFFSET       0x2A000  //This size is for LZMA compression only  960x540xI8 ZUI_bitmap_SW_LOAD.bin 166KB

    //It needs set bigger than all file size.
    //Please use the msAPI_OCP_GenerateBitmapHandle_SDRAMEx printf u32len.
    //It is raw data size. It depneds on reslution not depneds on real file size.
    //At turnky the biggeest file szie is EPG_IMG_SCHEDULE_LIST_BG1.PNG  0x1602C
    #define BMP_TMP_BUFFER_SIZE         0x10800     //This is is for LZMA compression only  //960x540xI8, biggest file EPG_IMG_SCHEDULE_LIST_BG1.BMP 45.1 KB , u32len = 0xB016 but set 0x10800(66KB)

    #define BMP_TMP_LZMA_TEMP_BUFFER_SIZE   0x10800// Buffer        0x10800 //Reserved 66KB for LZMA temp buffer

  #elif( (UI_SKIN_1366X768X565==UI_SKIN_SEL)||(UI_SKIN_960X540X565==UI_SKIN_SEL))
    //The total size
    //It needs set bigger than ZUI_bitmap_SW_LOAD.bin.
    #define BMP_TMP_BUFFER_OFFSET       0x4D800  //This size is for LZMA compression only    //0x90000

    //It needs set bigger than all file size.
    //Please use the msAPI_OCP_GenerateBitmapHandle_SDRAMEx printf u32len.
    //It is raw data size. It depneds on reslution not depneds on real file size.
    //At turnky the biggeest file szie is EPG_IMG_SCHEDULE_LIST_BG1.PNG  0x1602C
    #define BMP_TMP_BUFFER_SIZE         0x1C000     //This is is for LZMA compression only  //0x40000 //1366X768X565 biggest file EPOP_IMG1.png 124 KB  32len =0x1B6C0 set 0x1C000

    #define BMP_TMP_LZMA_TEMP_BUFFER_SIZE   0x10800// Buffer        0x10800 //Reserved 66KB for LZMA temp buffer

   #elif(UI_SKIN_1920X1080X565==UI_SKIN_SEL)
    //The total size
    //It needs set bigger than ZUI_bitmap_SW_LOAD.bin.
    #define BMP_TMP_BUFFER_OFFSET       0x4B400  //This size is for LZMA compression only    //0x90000

    //It needs set bigger than all file size.
    //Please use the msAPI_OCP_GenerateBitmapHandle_SDRAMEx printf u32len.
    //It is raw data size. It depneds on reslution not depneds on real file size.
    //At turnky the biggeest file szie is EPG_IMG_SCHEDULE_LIST_BG1.PNG  0x1602C
    #define BMP_TMP_BUFFER_SIZE         0x1C000     //This is is for LZMA compression only  //0x40000 //1366X768X565 biggest file EPOP_IMG1.png 124 KB  32len =0x1B6C0 set 0x1C000

    #define BMP_TMP_LZMA_TEMP_BUFFER_SIZE   0x10800// Buffer        0x10800 //Reserved 66KB for LZMA temp buffer
  #endif

    // 1st memory is for bmp.bin
    #define BMP_BIN_MEM_ADDR            (BMP_START_ADR)
    //#define BMP_BIN_SIZE_MAX              (BMP_TMP_BUFFER_OFFSET)
    #define BMP_BIN_BODY_SIZE_MAX       (BMP_TMP_BUFFER_OFFSET)

    // 2nd memory is for decompress-dest
    #define BMP_TMP_BUFFER_ADDR         (BMP_START_ADR + BMP_TMP_BUFFER_OFFSET)
    #define BMP_DECOMP_DST_BUF_ADDR     BMP_TMP_BUFFER_ADDR
    #define BMP_DECOMP_DST_BUF_SIZE     BMP_TMP_BUFFER_SIZE


    // 3nd memory is for decompress-temp
    #define BMP_TMP_LZMA_TEMP_BUFFER_OFFSET (BMP_TMP_BUFFER_OFFSET+BMP_TMP_BUFFER_SIZE)

    #define BMP_DECOMP_TMP_BUF_ADDR         (BMP_START_ADR + BMP_TMP_LZMA_TEMP_BUFFER_OFFSET)
    #define BMP_DECOMP_TMP_BUF_SIZE         BMP_TMP_LZMA_TEMP_BUFFER_SIZE//(BMP_START_LEN - (BMP_TMP_BUFFER_OFFSET + BMP_TMP_BUFFER_SIZE ))


    // Total use size...
    #define BMP_TMP_LZMA_ON_DEMAND_SIZE     (BMP_TMP_LZMA_TEMP_BUFFER_OFFSET+BMP_TMP_LZMA_TEMP_BUFFER_SIZE)     //0x73800, 462KB

  #if( BMP_TMP_LZMA_ON_DEMAND_SIZE > BMP_START_LEN )
    #error "BMP_START_LEN is too small"
  #endif


#else
    #define BMP_TMP_BUFFER_OFFSET   0x90000
    #define BMP_TMP_BUFFER_SIZE     0x40000
#endif



#define OCP_DBG(x)  //DEBUG_BMP(x)

#if 0
#define DEBUG_BMP(x)    do{ \
    msDebug_ANSI_SetColorText(E_FONT_COLOR_BLACK);              \
    msDebug_ANSI_SetColorText(E_FONT_BACKGROUND_COLOR_WHITE);   \
    x ; \
    msDebug_ANSI_AllAttrOffText();          \
} while(0)
#else
    #define DEBUG_BMP(x)
#endif

#define DEBUG_BMP_MEM(x)    //x
#define DEBUG_BMP_LOAD_EACH(x)  //x
#define DEBUG_BMP_DECOMP_EACH(x)  //x


//--------------------------------------------------------------------------------------------

//!!static  U32 fontCount;
//!!static U32 osdcp_fontpack_addr;
static U32 bmpaddr;
//!!static U32 fontaddr;


static BOOLEAN bmpCompressed;
//***************************************Bitmap

typedef struct
{
    U16 width;
    U16 height;
} OSDcp_loadbitmap_info_table;

typedef struct
{
    U16 u16BmpWidth;    //bmp dimension width
    U16 u16BmpHeight;   //bmp dimension height
    U16 u16BmpFmt;
    U32 u32BmpSrcSize;  //compressed source bitmap size
    U32 u32BmpAddr;     //32 bits addr in dram
}tCompressedBmp,*ptCompressedBmp;

#define MAX_BMP_NO  E_ZUI_BMP_MAX

#if SW_LOAD_BMP_ON_DEMAND

#define DEBUG_DYN_BMP(x)    //DEBUG_BMP(x)

static BOOLEAN u8bmpCompressedEach=0;
tCompressedBmp BmpEx[E_ZUI_BMP_MAX]; //MAX_BMP_NO*12 = 6K bytes to store bmp info
#endif

typedef struct
{
    U32 magicNumber;
    U32 headerSize;
    U32 bodySize;
    U32 binaryType;
    U32 bodyDecompressedSize;
    U16 bodyCompressMethod;
    U16 u16BmpNumber;
} BitmapBinaryInfo;

static U32 g_BMP_u32BinFlashAddr;
static U32 g_BMP_u32HeaderDramAddr;

void msAPI_OCP_Init(void)
{
    DEBUG_BMP( printf("msAPI_OCP_Init()\n"); );

    // Check if BMP_START_ADR   alignment
#if(BMP_START_ADR&0x0F)
    #error "BMP_START_ADR is not align to 16!!"
#endif

    bmpaddr = GE_ADDR_ALIGNMENT(((BMP_START_MEMORY_TYPE & MIU1) ? (BMP_START_ADR | MIU_INTERVAL) : (BMP_START_ADR)));
    bmpCompressed = FALSE;

    DEBUG_BMP( printf("bmpaddr=0x%X\n", bmpaddr); );

    DEBUG_BMP_MEM( printf("BMP_TMP_BUFFER_OFFSET=0x%X\n", BMP_TMP_BUFFER_OFFSET); );
    DEBUG_BMP_MEM( printf("BMP_TMP_BUFFER_SIZE=0x%X\n", BMP_TMP_BUFFER_SIZE); );

    DEBUG_BMP_MEM( printf("BMP_TMP_LZMA_TEMP_BUFFER_OFFSET=0x%X\n", BMP_TMP_LZMA_TEMP_BUFFER_OFFSET); );
    DEBUG_BMP_MEM( printf("BMP_TMP_LZMA_TEMP_BUFFER_SIZE=0x%X\n", BMP_TMP_LZMA_TEMP_BUFFER_SIZE); );

    DEBUG_BMP_MEM( printf("BMP_TMP_LZMA_ON_DEMAND_SIZE=0x%X\n", BMP_TMP_LZMA_ON_DEMAND_SIZE); );
}

void msAPI_DynBmp_ReadFlashToVirBuf(U32 u32StartAddr, U8* pu8BufAddr, U32 u32ReadSize)
{
    DEBUG_BMP( printf("ReadFlashToVirBuf(u32StartAddr=0x%X, u32ReadSize=%u(0x%X), pu8BufAddr=0x%X)\n", u32StartAddr, u32ReadSize, u32ReadSize, (U32)pu8BufAddr); );

#if 0
    msAPI_Flash_Read(u32StartAddr, u32ReadSize, pu8BufAddr);
#else
    //eRETCODE MApi_BDMA_CopyFromResource(U32 offset,U32 destVA,U32 len)
    //U32 u32PhyAddr = (U32)MsOS_VA2PA((U32)pu8BufAddr);

    //MApi_BDMA_CopyFromResource(u32StartAddr, u32PhyAddr, u32ReadSize);
    MApi_BDMA_CopyFromResource(u32StartAddr, (U32)pu8BufAddr, u32ReadSize);
#endif
}

void LoadU16(U32 pSpiAddr, U16 *pU16)
{
    DEBUG_BMP( printf("LoadU16(pSpiAddr=0x%X, pu8BufAddr=0x%X)\n", pSpiAddr, (U32)pU16); );

    //MApi_BDMA_CopyFromResource(pSpiAddr,(U32)pU16,sizeof(U16));
    msAPI_DynBmp_ReadFlashToVirBuf(pSpiAddr, (U8*)pU16, sizeof(U16));

    *pU16 = BE2ME16(*pU16);
}

void LoadBitmapInfoTable(U32 pSpiAddr, OSDcp_loadbitmap_info_table *pLIT)
{
    DEBUG_BMP( printf("LoadBitmapInfoTable(pSpiAddr=0x%X, pLIT=0x%X)\n", pSpiAddr, (U32)pLIT); );

    OSDcp_loadbitmap_info_table tbl;

    memset(&tbl, 0, sizeof(OSDcp_loadbitmap_info_table));   //Fix coverity CID200731
    //MApi_BDMA_CopyFromResource(pSpiAddr,(U32)&tbl,sizeof(tbl));
    msAPI_DynBmp_ReadFlashToVirBuf(pSpiAddr,(U8*)&tbl, sizeof(tbl));

    pLIT->width  = BE2ME16(tbl.width);
    pLIT->height = BE2ME16(tbl.height);
}

//Load Bitmap table extension with compressed for each bitmap object
void LoadBitmapInfoTableEx_FromFlash(U32 pSpiAddr, ptCompressedBmp pBmInfo, U32 nBmp, U32 u32BmpIndex)
{
    OSDcp_loadbitmap_info_table tbl;
    U8 u8Fmt = 0;
    U32 u32Size = 0;

    DEBUG_BMP( printf("LoadBitmapInfoTableEx_FromFlash(pSpiAddr=0x%X, pBmInfo=0x%X, nBmp=%u, u32BmpIndex=0x%X)\n", pSpiAddr, (U32)pBmInfo, nBmp, u32BmpIndex); );

    if( pBmInfo == NULL )
    {
        MS_DEBUG_MSG(printf("null pointer\n"));
        //MDrv_Sys_StopCpu(1);
        return;
    }

    memset(pBmInfo,0,sizeof(tCompressedBmp));
    memset(&tbl,0,sizeof(OSDcp_loadbitmap_info_table)); //Fix coverity CID200732

    //MApi_BDMA_CopyFromResource(pSpiAddr,(U32)&tbl,sizeof(tbl));
    //MApi_BDMA_CopyFromResource(pSpiAddr+((nBmp - u32BmpIndex)*4+u32BmpIndex),(U32)&u8Fmt,sizeof(u8Fmt));
    //MApi_BDMA_CopyFromResource(pSpiAddr+(nBmp*4+nBmp),(U32)&u32Size,sizeof(u32Size));

    msAPI_DynBmp_ReadFlashToVirBuf(pSpiAddr, (U8*)&tbl,sizeof(tbl));
    msAPI_DynBmp_ReadFlashToVirBuf(pSpiAddr+((nBmp - u32BmpIndex)*4+u32BmpIndex), &u8Fmt,sizeof(u8Fmt));
    msAPI_DynBmp_ReadFlashToVirBuf(pSpiAddr+(nBmp*4+nBmp), (U8*)&u32Size, sizeof(u32Size));

    pBmInfo->u16BmpWidth=BE2ME16(tbl.width);;
    pBmInfo->u16BmpHeight=BE2ME16(tbl.height);;
    pBmInfo->u16BmpFmt=(U16)u8Fmt;
    pBmInfo->u32BmpSrcSize=BE2ME32(u32Size);  //compressed source bitmap size
    pBmInfo->u32BmpAddr=0;     //32 bits addr in dram

    //printf(" W=%u, H=%u\n", pBmInfo->u16BmpWidth, pBmInfo->u16BmpHeight);
    //printf("  Fmt=%u, Size=%u\n", pBmInfo->u16BmpFmt, pBmInfo->u32BmpSrcSize);
}

void msAPI_OCP_ReadMemBytes(U32 u32MemAddr, U8* pu8Data, U32 u32Size )
{
    U32 i;
    U8 *pu8;

    pu8 = (U8*)MsOS_PA2KSEG1(u32MemAddr);

    //MsOS_FlushMemory();

    for( i = 0; i < u32Size; ++ i )
    {
        pu8Data[i] = *pu8;
        pu8 += 1;
    }
}

void LoadBitmapInfoTableEx_FromDram(U32 u32BmpInfoDramAddr, ptCompressedBmp pBmInfo, U32 nBmp, U32 u32BmpIndex)
{
    OSDcp_loadbitmap_info_table tbl;
    U8 u8Fmt = 0;
    U32 u32Size = 0;
    U32 u32MemAddr;

    DEBUG_BMP_LOAD_EACH( printf("LoadBitmapInfoTableEx_FromDram(u32BmpInfoDramAddr=0x%X, pBmInfo=0x%X, nBmp=%u, u32BmpIndex=0x%X)\n", u32BmpInfoDramAddr, (U32)pBmInfo, nBmp, u32BmpIndex); );

    memset(pBmInfo,0,sizeof(tCompressedBmp));
    memset(&tbl,0,sizeof(OSDcp_loadbitmap_info_table)); //Fix coverity CID200732


    // Get bmp width&height
    u32MemAddr = u32BmpInfoDramAddr + u32BmpIndex * 4;
    msAPI_OCP_ReadMemBytes(u32MemAddr, (U8*)&tbl, sizeof(tbl));

    // Get bmp format
    u32MemAddr = u32BmpInfoDramAddr + (nBmp * 4) + u32BmpIndex;
    msAPI_OCP_ReadMemBytes(u32MemAddr, (U8*)&u8Fmt, sizeof(u8Fmt));

    // Get bmp size
    u32MemAddr = u32BmpInfoDramAddr + (nBmp * 5) + u32BmpIndex * 4;
    //printf("  u32MemAddr=0x%X\n", u32MemAddr);
    msAPI_OCP_ReadMemBytes(u32MemAddr, (U8*)&u32Size, 4);
    //printf("  Size=0x%X, 0x%X\n", u32Size, BE2ME32(u32Size) );

    //Print_Buffer( (U8*)MsOS_PA2KSEG1(u32MemAddr), 0x10);

    pBmInfo->u16BmpWidth=BE2ME16(tbl.width);;
    pBmInfo->u16BmpHeight=BE2ME16(tbl.height);
    pBmInfo->u16BmpFmt=(U16)u8Fmt;

    u32Size = BE2ME32(u32Size);
    // Check size over flow
    if( u32Size > 0xFFFF )
    {
        printf("\nWarning: Bmp src size=%u is too large!\n", u32Size);
    }

    pBmInfo->u32BmpSrcSize = u32Size;  //compressed source bitmap size

    pBmInfo->u32BmpAddr = 0;     //32 bits addr in dram

    //printf(" W=%u, H=%u\n", pBmInfo->u16BmpWidth, pBmInfo->u16BmpHeight);
    //printf("  Fmt=%u, Size=%u\n", pBmInfo->u16BmpFmt, pBmInfo->u32BmpSrcSize);
}

void LoadBitmapBinaryInfo(U8* pu8BmpHeaderBuf, BitmapBinaryInfo *pBBI)
{
    DEBUG_BMP( printf("LoadBitmapBinaryInfo(pu8BmpHeaderBuf=0x%X)\n", pu8BmpHeaderBuf); );

    //Print_Buffer(au8TmpBuf, 22 );

    pBBI->magicNumber = ReadU32BE(pu8BmpHeaderBuf + 0);
    pBBI->headerSize  = ReadU32BE(pu8BmpHeaderBuf + 4);
    pBBI->bodySize    = ReadU32BE(pu8BmpHeaderBuf + 8);
    pBBI->binaryType  = ReadU32BE(pu8BmpHeaderBuf + 12);
    pBBI->bodyCompressMethod = ReadU16BE(pu8BmpHeaderBuf + 16);
    pBBI->bodyDecompressedSize = ReadU32BE(pu8BmpHeaderBuf + 18);
    pBBI->u16BmpNumber = ReadU16BE(pu8BmpHeaderBuf + INFO_SIZE);

    // Patch headerSize!!

    DEBUG_BMP( printf(" headerSize=%u\n", pBBI->headerSize); );
    DEBUG_BMP( printf(" bodySize=%u\n", pBBI->bodySize); );
    DEBUG_BMP( printf(" binaryType=%u\n", pBBI->binaryType); );
    DEBUG_BMP( printf(" bodyCompressMethod=%u\n", pBBI->bodyCompressMethod); );
    DEBUG_BMP( printf(" bodyDecompressedSize=%u\n", pBBI->bodyDecompressedSize); );
    DEBUG_BMP( printf(" u16BmpNumber=%u\n", pBBI->u16BmpNumber); );
}

void LoadBitmapBinaryInfo_FromDram(U32 u32DramAddr, BitmapBinaryInfo *pBBI)
{
    DEBUG_BMP( printf("LoadBitmapBinaryInfo_FromDram(u32DramAddr=0x%X)\n", u32DramAddr); );

    U8 au8TmpBuf[80];

    memcpy( au8TmpBuf, (void*)_PA2VA(u32DramAddr), 80);
    //Print_Buffer(au8TmpBuf, 22 );

    LoadBitmapBinaryInfo(au8TmpBuf, pBBI);
}

void LoadBitmapBinaryInfo_FromFlash(U32 pSpiAddr, BitmapBinaryInfo *pBBI)
{
    DEBUG_BMP( printf("LoadBitmapBinaryInfo_FromFlash(pSpiAddr=0x%X)\n", pSpiAddr); );

    U8 au8TmpBuf[80];

    msAPI_DynBmp_ReadFlashToVirBuf(pSpiAddr, au8TmpBuf, 80);

    //Print_Buffer(p, 22 );

    LoadBitmapBinaryInfo(au8TmpBuf, pBBI);
}

void msAPI_OCP_LoadBitmap(/*BMPHANDLE* pbmpHandle*/ void)
{
    BININFO BinInfo;
    U32 u32Offset;
    U16 u16Index;
    U16 bitmap_no;
    OSDcp_loadbitmap_info_table loadbitmap_info_table;
    BitmapBinaryInfo info;
    U8 u8Fmt;
    GFX_Buffer_Format fmt;
    BOOLEAN bResult;


    DEBUG_BMP(printf("%s()\n", __FUNCTION__););

    BinInfo.B_ID = BIN_ID_OSDCP_BMP;
    msAPI_MIU_Get_BinInfo(&BinInfo, &bResult);
    if( bResult != PASS )
    {
        printf("\nError: Get bin info failed!\n");
        return;
    }


    if( BinInfo.B_IsComp !=0 )
    {
        // BMP bin file is already load in POOL_BUFFER by msAPI_OCP_PrepareBitmapBinary()
        //osdcp_bmp_addr = ((POOL_BUFFER_ADR & MIU1) ? (POOL_BUFFER_ADR | MIU_INTERVAL) : (POOL_BUFFER_ADR));

        memcpy(&bitmap_no, (void*)_PA2VA(g_BMP_u32HeaderDramAddr+INFO_SIZE), sizeof(U16));
        bitmap_no = BE2ME16(bitmap_no);

        DEBUG_BMP( printf("bitmap_no = %d\n", bitmap_no); );

        for (u16Index=0; u16Index<bitmap_no; u16Index++)
        {
            u32Offset = g_BMP_u32HeaderDramAddr + INFO_SIZE + sizeof(bitmap_no);

            {
                memcpy(&loadbitmap_info_table, (void*)_PA2VA(u32Offset+u16Index*sizeof(OSDcp_loadbitmap_info_table)), sizeof(OSDcp_loadbitmap_info_table));
                loadbitmap_info_table.width = BE2ME16(loadbitmap_info_table.width);
                loadbitmap_info_table.height = BE2ME16(loadbitmap_info_table.height);
            }

            memcpy(&u8Fmt, (void*)_PA2VA(u32Offset+bitmap_no*sizeof(OSDcp_loadbitmap_info_table)+u16Index), 1);
            //printf("~~~ u8Fmt = %d\n",u8Fmt);

            switch (u8Fmt)
            {
                case BITMAP_FMT_ARGB8888:
                    fmt = GFX_FMT_ARGB8888;
                    break;
                case BITMAP_FMT_ARGB4444:
                    fmt = GFX_FMT_ARGB4444;
                    break;
                case BITMAP_FMT_I8:
                    fmt = GFX_FMT_I8;
                    break;
                default:
                    fmt = GFX_FMT_ARGB1555;
                    break;
            }

            //pbmpHandle[u16Index] = msAPI_OCP_GenerateBitmapHandle_SDRAM(loadbitmap_info_table.width, loadbitmap_info_table.height, fmt);
            msAPI_OCP_GenerateBitmapHandle_SDRAM(loadbitmap_info_table.width, loadbitmap_info_table.height, fmt);
        }
    }
    else
    {
        U32 u32BmpBinFlashAddr = BinInfo.B_FAddr;

        // Read bmp header
        LoadBitmapBinaryInfo_FromFlash(u32BmpBinFlashAddr, &info);
        bitmap_no = info.u16BmpNumber;

        // Get bmp number
        //LoadU16(osdcp_bmp_addr+INFO_SIZE, &bitmap_no);
        DEBUG_BMP( printf("bitmap_no=%u\n", bitmap_no); );

    #if SW_LOAD_BMP_ON_DEMAND

        DEBUG_DYN_BMP( printf("info.bodyCompressMethod=%u\n", info.bodyCompressMethod); );

        if((info.bodyCompressMethod==6) || (info.bodyCompressMethod==7))
        {
            u32Offset = u32BmpBinFlashAddr + INFO_SIZE + sizeof(bitmap_no);

            if(bitmap_no>MAX_BMP_NO)
            {
                printf("bmp no error max > :%d\n",MAX_BMP_NO);
                MDrv_Sys_StopCpu(1);
            }

            for (u16Index=0; u16Index<bitmap_no; u16Index++)
            {
                //printf("u16Index=%u\n",u16Index);

                //LoadBitmapInfoTableEx_FromFlash(u32Offset+u16Index*sizeof(OSDcp_loadbitmap_info_table), &BmpEx[u16Index],bitmap_no,u16Index);
                LoadBitmapInfoTableEx_FromDram( g_BMP_u32HeaderDramAddr + INFO_SIZE + sizeof(bitmap_no), &BmpEx[u16Index], bitmap_no, u16Index);


                //MApi_BDMA_CopyFromResource(u32Offset+bitmap_no*sizeof(OSDcp_loadbitmap_info_table)+u16Index,(U32)&u8Fmt,1);
                //BmpEx[u16Index].=u8Fmt;
                switch (BmpEx[u16Index].u16BmpFmt)
                {
                    case BITMAP_FMT_ARGB8888:
                        fmt = GFX_FMT_ARGB8888;
                        break;
                    case BITMAP_FMT_ARGB4444:
                        fmt = GFX_FMT_ARGB4444;
                        break;
                    case BITMAP_FMT_I8:
                        fmt = GFX_FMT_I8;
                        break;
                    default:
                        fmt = GFX_FMT_ARGB1555;
                        break;
                }

                //pbmpHandle[u16Index] = msAPI_OCP_GenerateBitmapHandle_SDRAMEx(BmpEx[u16Index].u16BmpWidth, BmpEx[u16Index].u16BmpHeight, fmt);
                msAPI_OCP_GenerateBitmapHandle_SDRAMEx(BmpEx[u16Index].u16BmpWidth, BmpEx[u16Index].u16BmpHeight, fmt);
            }

            BmpEx[0].u32BmpAddr = _PA2VA((BMP_START_MEMORY_TYPE & MIU1) ? (BMP_START_ADR | MIU_INTERVAL) : (BMP_START_ADR));

            for (u16Index=0; u16Index<bitmap_no; u16Index++)
            {
                if(u16Index==1)
                {
                    BmpEx[u16Index].u32BmpAddr=BmpEx[0].u32BmpAddr+BmpEx[0].u32BmpSrcSize;
                }
                else if(u16Index>0 && u16Index!=1)
                {
                    BmpEx[u16Index].u32BmpAddr=BmpEx[u16Index - 1].u32BmpAddr+BmpEx[u16Index - 1].u32BmpSrcSize;
                }

                DEBUG_DYN_BMP( printf("BmpEx[%d].u32BmpAddr=%x\n", u16Index, BmpEx[u16Index].u32BmpAddr); );
            }
        }
        else
    #endif
        {
            for (u16Index=0; u16Index<bitmap_no; u16Index++)
            {
                u32Offset = u32BmpBinFlashAddr + INFO_SIZE + sizeof(bitmap_no);
                LoadBitmapInfoTable(u32Offset+u16Index*sizeof(OSDcp_loadbitmap_info_table), &loadbitmap_info_table);
                MApi_BDMA_CopyFromResource(u32Offset+bitmap_no*sizeof(OSDcp_loadbitmap_info_table)+u16Index,(U32)&u8Fmt,1);

                switch (u8Fmt)
                {
                    case BITMAP_FMT_ARGB8888:
                        fmt = GFX_FMT_ARGB8888;
                        break;
                    case BITMAP_FMT_ARGB4444:
                        fmt = GFX_FMT_ARGB4444;
                        break;
                    case BITMAP_FMT_I8:
                        fmt = GFX_FMT_I8;
                        break;
                    default:
                        fmt = GFX_FMT_ARGB1555;
                        break;
                }

                //pbmpHandle[u16Index] = msAPI_OCP_GenerateBitmapHandle_SDRAM(loadbitmap_info_table.width, loadbitmap_info_table.height, fmt);
                msAPI_OCP_GenerateBitmapHandle_SDRAM(loadbitmap_info_table.width, loadbitmap_info_table.height, fmt);

            }
        }
    }
}

void msAPI_OCP_DecompressHandle(BMPHANDLE handle)
{
#if SW_LOAD_BMP_ON_DEMAND
    if(u8bmpCompressedEach)
    {
        DEBUG_BMP_DECOMP_EACH(printf("%s()\n", __FUNCTION__););

        //DEBUG_DYN_BMP( printf("u8bmpCompressedEach=%u\n", u8bmpCompressedEach); );
        if ( u8bmpCompressedEach == 1 )
        {
            //ms_DecompressInit((U8*)(_PA2VA((BMP_START_MEMORY_TYPE & MIU1) ? ((BMP_START_ADR+BMP_TMP_BUFFER_OFFSET) | MIU_INTERVAL) : (BMP_START_ADR+BMP_TMP_BUFFER_OFFSET))));
            ms_DecompressInit( (U8*)(_PA2VA(BMP_DECOMP_DST_BUF_ADDR)) );
            ms_Decompress((const U8*)(BmpEx[handle].u32BmpAddr), BmpEx[handle].u32BmpSrcSize);
            ms_DecompressDeInit();
        }
        else if ( u8bmpCompressedEach == 2 )
        {
            //BmpEx[handle].u32BmpSrcSize-2 is to minus 0xBEEF 2 bytes end tag
            //use non-cacheable decompression destination address here to avoid d-cache flush problem
            DEBUG_DYN_BMP( printf("BmpEx[%u].u32BmpAddr=0x%X\n", handle, BmpEx[handle].u32BmpAddr); );

            if( BmpEx[handle].u32BmpAddr == 0 )
            {
                return;
            }

            if ( !DoMsDecompression7(
                  (U8 *)(BmpEx[handle].u32BmpAddr & NON_CACHEABLE_TO_CACHEABLE_MASK),
                  //(U8 *)((_PA2VA((BMP_START_MEMORY_TYPE & MIU1) ? ((BMP_START_ADR+BMP_TMP_BUFFER_OFFSET) | MIU_INTERVAL) : (BMP_START_ADR+BMP_TMP_BUFFER_OFFSET))) & NON_CACHEABLE_TO_CACHEABLE_MASK),
                    (U8 *)( MsOS_PA2KSEG1(BMP_DECOMP_DST_BUF_ADDR) ),
                  //(U8 *)(((_PA2VA((BMP_START_MEMORY_TYPE & MIU1) ? ((BMP_START_ADR+BMP_TMP_BUFFER_OFFSET) | MIU_INTERVAL) : (BMP_START_ADR+BMP_TMP_BUFFER_OFFSET)))+BMP_TMP_BUFFER_SIZE) & NON_CACHEABLE_TO_CACHEABLE_MASK),
                  (U8 *)( MsOS_PA2KSEG1(BMP_DECOMP_TMP_BUF_ADDR) ),
                    BmpEx[handle].u32BmpSrcSize-2)
                )
            {
                printf("BMP decompress fail\n");
            }
        }

        //MsOS_Dcache_Flush( _PA2VA((BMP_START_MEMORY_TYPE & MIU1) ? ((BMP_START_ADR+BMP_TMP_BUFFER_OFFSET) | MIU_INTERVAL) : (BMP_START_ADR+BMP_TMP_BUFFER_OFFSET))  & NON_CACHEABLE_TO_CACHEABLE_MASK, BMP_TMP_BUFFER_SIZE );
        MsOS_Dcache_Flush( MsOS_PA2KSEG1(BMP_DECOMP_DST_BUF_ADDR), BMP_DECOMP_DST_BUF_SIZE );
        MsOS_FlushMemory();
    }
#else
    handle=handle;
#endif
}

void msAPI_OCP_PrepareBitmapBinary(void)
{
    BININFO BinInfo;
    //U32 osdcp_bmp_addr=0;
    U32 u32BmpBinDramAddr = 0;
    BitmapBinaryInfo info;
    BOOLEAN bResult;
    U16 bmpno;


    DEBUG_BMP(printf("%s()\n", __FUNCTION__););

    BinInfo.B_ID = BIN_ID_OSDCP_BMP;

    msAPI_MIU_Get_BinInfo(&BinInfo, &bResult);

    if ( bResult != PASS)
    {
        printf("ERROR!![%s]%d\n",__FILE__,__LINE__);
        return;
    }

    g_BMP_u32BinFlashAddr = BinInfo.B_FAddr;
    DEBUG_BMP( printf("g_BMP_u32BinFlashAddr=0x%X\n", g_BMP_u32BinFlashAddr ); );

    //printf("~~1 BinInfo.B_Len = %ld\n",BinInfo.B_Len);

#define BMP_TMP_BUF_ADR     (((POOL_BUFFER_ADR)& MIU1) ? ((POOL_BUFFER_ADR) | MIU_INTERVAL) : (POOL_BUFFER_ADR))
#define BMP_LOAD_BIN_DST_ADR (BMP_TMP_BUF_ADR + 0x100000)
#define BMP_LOAD_BIN_SRC_ADR (BMP_LOAD_BIN_DST_ADR + 0x600000)
#define BMP_LOAD_BIN_TMP_ADR (BMP_LOAD_BIN_SRC_ADR + 0x600000)

    // Load bin from flash to dram: (POOL_BUFFER_ADR+BUF_OFFSET_FOR_BITMAP_DECOMPRESS_DST)
    DEBUG_BMP( printf("Load BMP.bin to BMP_LOAD_BIN_DST_ADR=0x%X\n", BMP_LOAD_BIN_DST_ADR ); );

    if( SUCCESS == MDrv_DMA_LoadBin(&BinInfo,
                //_PA2VA(((POOL_BUFFER_ADR+BUF_OFFSET_FOR_BITMAP_DECOMPRESS_DST) & MIU1) ? ((POOL_BUFFER_ADR+BUF_OFFSET_FOR_BITMAP_DECOMPRESS_DST) | MIU_INTERVAL) : (POOL_BUFFER_ADR+BUF_OFFSET_FOR_BITMAP_DECOMPRESS_DST)),
                MsOS_PA2KSEG1(BMP_LOAD_BIN_DST_ADR),
                //_PA2VA(((POOL_BUFFER_ADR+ BUF_OFFSET_FOR_BITMAP_DECOMPRESS_SRC) & MIU1) ? ((POOL_BUFFER_ADR+ BUF_OFFSET_FOR_BITMAP_DECOMPRESS_SRC) | MIU_INTERVAL) : (POOL_BUFFER_ADR+ BUF_OFFSET_FOR_BITMAP_DECOMPRESS_SRC)),
                MsOS_PA2KSEG1(BMP_LOAD_BIN_SRC_ADR),
                //_PA2VA(((POOL_BUFFER_ADR+ BUF_OFFSET_FOR_BITMAP_DECOMPRESS_TMP) & MIU1) ? ((POOL_BUFFER_ADR+ BUF_OFFSET_FOR_BITMAP_DECOMPRESS_TMP) | MIU_INTERVAL) : (POOL_BUFFER_ADR+ BUF_OFFSET_FOR_BITMAP_DECOMPRESS_TMP)))
                MsOS_PA2KSEG1(BMP_LOAD_BIN_TMP_ADR)
            )
      )
    {
        switch(BinInfo.B_IsComp)
        {
            case LZSS_COMPRESS:
            case MS_COMPRESS:
            case MS_COMPRESS7:
                //printf("~~1~~  LZSS_COMPRESS\n");
                bmpCompressed=TRUE;
                break;

            default:
                bmpCompressed=FALSE;
                break;
        }

        MsOS_FlushMemory();  //20091229EL

        //osdcp_bmp_addr = (((POOL_BUFFER_ADR+BUF_OFFSET_FOR_BITMAP_DECOMPRESS_DST) & MIU1) ? ((POOL_BUFFER_ADR+BUF_OFFSET_FOR_BITMAP_DECOMPRESS_DST) | MIU_INTERVAL) : (POOL_BUFFER_ADR+BUF_OFFSET_FOR_BITMAP_DECOMPRESS_DST));
        //osdcp_bmp_addr = BMP_LOAD_BIN_DST_ADR;
        u32BmpBinDramAddr = BMP_LOAD_BIN_DST_ADR;
        g_BMP_u32HeaderDramAddr = BMP_LOAD_BIN_DST_ADR;

    #if 1
        LoadBitmapBinaryInfo_FromDram(u32BmpBinDramAddr, &info);
        bmpno = info.u16BmpNumber;
    #else
        {
            U8 p[80];
            memcpy(&p, (void*)_PA2VA(u32BmpBinDramAddr), 80);
            info.magicNumber = ReadU32BE(p + 0);
            info.headerSize  = ReadU32BE(p + 4);
            info.bodySize    = ReadU32BE(p + 8);
            info.binaryType  = ReadU32BE(p + 12);
            info.bodyCompressMethod = ReadU16BE(p + 16);
            info.bodyDecompressedSize = ReadU32BE(p + 18);
            bmpno=ReadU16BE(p+0x40);
        }
    #endif

        //printf(" info.magicNumber = %ld\n", info.magicNumber);
        //DEBUG_BMP( printf(" info.headerSize = %ld\n", info.headerSize); );
        //DEBUG_BMP( printf(" info.bodySize = %u(0x%X)\n", info.bodySize, info.bodySize); );
        //printf(" info.binaryType = %ld\n", info.binaryType);
        //printf(" info.bodyDecompressedSize = %ld\n", info.bodyDecompressedSize);
        //printf(" info.bodyCompressMethod = %d\n", info.bodyCompressMethod);
        //DEBUG_BMP( printf(" bmpno = %u\n", bmpno); );

        // Copy Header to POOL_BUFFER_ADR
        //DEBUG_BMP( printf("Copy header to BMP_TMP_BUF_ADR=0x%X\n", BMP_TMP_BUF_ADR ); );
        //MApi_BDMA_Copy((osdcp_bmp_addr),((POOL_BUFFER_ADR & MIU1) ? (POOL_BUFFER_ADR | MIU_INTERVAL) : (POOL_BUFFER_ADR)), GE_ALIGNED_VALUE(info.headerSize,8), MIU_SDRAM2SDRAM);
        //MApi_BDMA_Copy( (u32BmpBinDramAddr), BMP_TMP_BUF_ADR, GE_ALIGNED_VALUE(info.headerSize,8), MIU_SDRAM2SDRAM);
        //g_BMP_u32HeaderDramAddr = BMP_TMP_BUF_ADR;

    #if(CHAKRA3_AUTO_TEST)
        printf("Copy Body to BMP_START_ADR=0x%X, bodySize=0x%X\n", BMP_START_ADR, info.bodySize );
    #else
        DEBUG_BMP( printf("Copy Body to BMP_START_ADR=0x%X, bodySize=0x%X\n", BMP_START_ADR, info.bodySize ); );
    #endif


    #if SW_LOAD_BMP_ON_DEMAND
        switch(info.bodyCompressMethod)
        {
            case 6:
                u8bmpCompressedEach=1;
                break;
            case 7:
                u8bmpCompressedEach=2;
                break;
            default:
                u8bmpCompressedEach=0;
                break;
        }

        if((info.bodyCompressMethod==6) || (info.bodyCompressMethod==7))
        {
            // Check if size over~
            if( info.bodySize >= BMP_BIN_BODY_SIZE_MAX )
            {
                msDebug_FatalErrorHandler_Para_2(FATAL_ERR_ID_OCP_BMP_BIN_FILE_TOO_BIG, info.bodySize, BMP_BIN_BODY_SIZE_MAX);
                printf("\nError: bmp bodySize=0x%X >= BMP_BIN_BODY_SIZE_MAX=0x%X!!\n", info.bodySize, BMP_BIN_BODY_SIZE_MAX);
            }

            // Copy body to BMP_START_ADR
            MApi_BDMA_Copy(((u32BmpBinDramAddr+info.headerSize+(bmpno*4))), msAPI_OCP_GetBmpAddr(), info.bodySize, MIU_SDRAM2SDRAM);

            //msDebug_CheckMemChg_Init(msAPI_OCP_GetBmpAddr(), info.bodySize);
        }
        else
    #endif
        {
            // Copy body to BMP_START_ADR
            MApi_BDMA_Copy((u32BmpBinDramAddr+info.headerSize), msAPI_OCP_GetBmpAddr(), info.bodySize ,MIU_SDRAM2SDRAM);
        }
    }
    else
    {
        printf("ERROR!![%s]%d\n",__FILE__,__LINE__);
        return;
    }
}

BMPHANDLE msAPI_OCP_GenerateBitmapHandle_SDRAM(U16 u16width, U16 u16height, GFX_Buffer_Format fmt)
{
    U32 u32dstaddr = bmpaddr, u32len;

    DEBUG_BMP(printf("%s()\n", __FUNCTION__););

    if (fmt == GFX_FMT_I8)
        u32len = (U32)( (U32)u16width * u16height);
    else if (fmt == GFX_FMT_ARGB8888)
        u32len = (U32)( (U32)u16width * u16height) * 4;
    else
        u32len = (U32)( (U32)u16width * u16height) * 2;

    bmpaddr = GE_ADDR_ALIGNMENT(bmpaddr + u32len);
    return msAPI_OSD_RESOURCE_LoadBitmap(u32dstaddr, u32len, u16width, u16height, (BMP_Buffer_Format)fmt);
}

#if SW_LOAD_BMP_ON_DEMAND
BMPHANDLE msAPI_OCP_GenerateBitmapHandle_SDRAMEx(U16 u16width, U16 u16height, GFX_Buffer_Format fmt)
{
    //DEBUG_BMP(printf("%s()\n", __FUNCTION__););

    //use same address for bitmap rendering
    //This address must be physical address for GE HW
    U32 u32dstaddr = ((BMP_START_MEMORY_TYPE & MIU1) ? ((BMP_START_ADR+BMP_TMP_BUFFER_OFFSET) | MIU_INTERVAL) : (BMP_START_ADR+BMP_TMP_BUFFER_OFFSET)), u32len;
    if (fmt == GFX_FMT_I8)
        u32len = (U32)( (U32)u16width * u16height);
    else if (fmt == GFX_FMT_ARGB8888)
        u32len = (U32)( (U32)u16width * u16height) * 4;
    else
        u32len = (U32)( (U32)u16width * u16height) * 2;

    //bmpaddr = GE_ADDR_ALIGNMENT(bmpaddr + u32len);
    //printf("u16width %d u16height%d u32len =0x%x \r\n",u16width,u16height,u32len);
    return msAPI_OSD_RESOURCE_LoadBitmap(u32dstaddr, u32len, u16width, u16height, (BMP_Buffer_Format)fmt);
}
#endif

U32 msAPI_OCP_GetBmpAddr(void)
{
    return GE_ADDR_ALIGNMENT(((BMP_START_MEMORY_TYPE & MIU1) ? (BMP_START_ADR | MIU_INTERVAL) : (BMP_START_ADR)));
}

//*******************String
typedef struct
{
    U32 magicNumber;
    U32 headerSize;
    U32 bodySize;
    U32 binaryType;
    U16 bodyCompressMethod;
    U32 bodyDecompressedSize;
    U16 bodyEncodingMethod;
} StringBinaryInfo;

typedef struct
{
    U32 startaddr;
    U16 length;
} OSDcp_string_info_table;

#define STRBUFF_LENGTH 256

//static U32 osdcp_text_addr;
static U32 s_OCP_u32StringBinFlashAddr = 0;

static StringBinaryInfo sStringBininfo;


// Check STRING_START_ADR align?
#if( STRING_START_ADR&0x0F )
    #error "STRING_START_ADR is not align to 16!!"
#endif

#if 1
    #define msAPI_OCP_Get_StringBufAddr()   ((STRING_START_MEMORY_TYPE & MIU1) ? (STRING_START_ADR | MIU_INTERVAL) : (STRING_START_ADR))
#else

U32 msAPI_OCP_Get_StringBufAddr(void)
{
#if 1
    return ((STRING_START_MEMORY_TYPE & MIU1) ? (STRING_START_ADR | MIU_INTERVAL) : (STRING_START_ADR));
#else
    return GE_ADDR_ALIGNMENT(((STRING_START_MEMORY_TYPE & MIU1) ? (STRING_START_ADR | MIU_INTERVAL) : (STRING_START_ADR)));
#endif
}
#endif


#define DEBUG_STRING(x)     //x

static void LoadStringBinaryInfo(U8* p, StringBinaryInfo *pSBI)
{
    pSBI->magicNumber = ReadU32BE(p + 0);
    pSBI->headerSize = ReadU32BE(p + 4);
    pSBI->bodySize = ReadU32BE(p + 8);
    pSBI->binaryType = ReadU32BE(p + 12);
    pSBI->bodyCompressMethod = ReadU16BE(p + 16);
    pSBI->bodyDecompressedSize = ReadU32BE(p + 18);
    pSBI->bodyEncodingMethod = ReadU16BE(p + 22);

    DEBUG_STRING( printf("pSBI->magicNumber=0x%x\n", pSBI->magicNumber); );
    DEBUG_STRING( printf("pSBI->headerSize=0x%x\n", pSBI->headerSize); );
    DEBUG_STRING( printf("pSBI->bodySize=0x%x\n", pSBI->bodySize); );
    DEBUG_STRING( printf("pSBI->binaryType=0x%x\n", pSBI->binaryType); );
    DEBUG_STRING( printf("pSBI->bodyCompressMethod=0x%x\n", pSBI->bodyCompressMethod); );
    DEBUG_STRING( printf("pSBI->bodyDecompressedSize=0x%x\n", pSBI->bodyDecompressedSize); );
    DEBUG_STRING( printf("pSBI->bodyEncodingMethod=0x%x\n", pSBI->bodyEncodingMethod); );
}

void msAPI_OCP_PrepareStringBinary(void)
{
    DEBUG_STRING( printf("msAPI_OCP_PrepareStringBinary()\n"); );

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    BININFO BinInfo;
    BOOLEAN bResult;

    BinInfo.B_ID = BIN_ID_OSDCP_TEXT;

    msAPI_MIU_Get_BinInfo(&BinInfo, &bResult);

    if ( bResult != PASS)
    {
        printf("ERROR!![%s]%d\n",__FILE__,__LINE__);
        return;
    }

    s_OCP_u32StringBinFlashAddr = BinInfo.B_FAddr;
    DEBUG_STRING( printf("s_OCP_u32StringBinFlashAddr=0x%X\n", s_OCP_u32StringBinFlashAddr); );

    U32 u32DestVA = _PA2VA(msAPI_OCP_Get_StringBufAddr());
    U32 u32DecVA = _PA2VA((POOL_BUFFER_ADR & MIU1) ? (POOL_BUFFER_ADR | MIU_INTERVAL) : (POOL_BUFFER_ADR));
    U32 u32TmpVA = u32DecVA + BUF_FOR_DECOMPRESS_OFFSET1;

    if( SUCCESS == MDrv_DMA_LoadBin(&BinInfo, u32DestVA, u32DecVA, u32TmpVA ) )
    {
        switch(BinInfo.B_IsComp)
        {
        case LZSS_COMPRESS:
        case MS_COMPRESS:
        case MS_COMPRESS7:
            _bOCPFromMem   = TRUE;
            //osdcp_text_addr = msAPI_OCP_Get_StringBufAddr();
            LoadStringBinaryInfo((U8*)(_PA2VA( msAPI_OCP_Get_StringBufAddr() )), &sStringBininfo);
            break;
        default:
            {
                #define STRING_BIN_INFO_SIZE    24
                U8 au8TmpBuf[STRING_BIN_INFO_SIZE];
                //osdcp_text_addr =  BinInfo.B_FAddr;
                MApi_BDMA_CopyFromResource(s_OCP_u32StringBinFlashAddr,(U32)au8TmpBuf, STRING_BIN_INFO_SIZE);
                LoadStringBinaryInfo(au8TmpBuf, &sStringBininfo);
            }
            break;
        }

        // Check string.bin size with String buffer size
        if( (sStringBininfo.headerSize + sStringBininfo.bodySize) > (STRING_START_LEN) )
        {
            printf("\nError: String.bin size=0x%X > STRING_START_LEN=0x%X\n", (sStringBininfo.headerSize + sStringBininfo.bodySize), STRING_START_LEN );
            msDebug_FatalErrorHandler_Para_2(FATAL_ERR_ID_OCP_STRING_BIN_FILE_TOO_BIG, (sStringBininfo.headerSize + sStringBininfo.bodySize), STRING_START_LEN);
            return;
        }

    }
    else
    {
        printf("\nError: Load string.bin failed!\n");
        return;
    }

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

static U32 readbin_language_addr( U8 language )
{
    U32 language_addr;
    U32 language_id_addr;

    //printf("readbin_language_addr(language=%u)\n", language);

    language_id_addr = sizeof(U32) + language * sizeof(language_addr);

    //printf("language_id_addr=0x%X\n", language_id_addr);

    if(_bOCPFromMem)
    {
        //memcpy(&language_addr, (void *)_PA2VA((U32)(((STRING_START_MEMORY_TYPE & MIU1) ? (STRING_START_ADR | MIU_INTERVAL) : (STRING_START_ADR))+INFO_SIZE+language_id_addr)), sizeof(language_addr));
        memcpy(&language_addr, (void *)_PA2VA((U32)( msAPI_OCP_Get_StringBufAddr()+ INFO_SIZE + language_id_addr)), sizeof(language_addr));
    }
    else
    {

        MApi_BDMA_CopyFromResource(s_OCP_u32StringBinFlashAddr+INFO_SIZE+language_id_addr,(U32)&language_addr,sizeof(language_addr));
    }

    //printf("language_addr=0x%X\n", BE2ME32(language_addr));

    return BE2ME32(language_addr);
}

static OSDcp_string_info_table readbin_string_info(U32 language_addr, U16 id)
{
    OSDcp_string_info_table struct_string_info;

    U32 startaddr;
    U32 staraddr_next;
    U32 string_id_info_addr;

    //printf("readbin_string_info(language_addr=0x%X, id=%u)\n",language_addr, id);

    string_id_info_addr = language_addr+sizeof(U32)/*string count*/+id*sizeof(startaddr);

    //printf("string_id_info_addr=0x%X\n",string_id_info_addr);

    if(_bOCPFromMem)
    {
        //memcpy(&startaddr, (void *)_PA2VA((((STRING_START_MEMORY_TYPE & MIU1) ? (STRING_START_ADR | MIU_INTERVAL) : (STRING_START_ADR))+string_id_info_addr)), sizeof(startaddr));
        memcpy(&startaddr, (void *)_PA2VA(( msAPI_OCP_Get_StringBufAddr() + string_id_info_addr)), sizeof(startaddr));

        //memcpy(&staraddr_next, (void *)_PA2VA((((STRING_START_MEMORY_TYPE & MIU1) ? (STRING_START_ADR | MIU_INTERVAL) : (STRING_START_ADR))+string_id_info_addr+sizeof(startaddr))), sizeof(startaddr));
        memcpy(&staraddr_next, (void *)_PA2VA(( msAPI_OCP_Get_StringBufAddr() + string_id_info_addr+sizeof(startaddr))), sizeof(startaddr));
    }
    else
    {

        MApi_BDMA_CopyFromResource(s_OCP_u32StringBinFlashAddr+string_id_info_addr,(U32)&startaddr,sizeof(startaddr));
        MApi_BDMA_CopyFromResource(s_OCP_u32StringBinFlashAddr+string_id_info_addr+sizeof(startaddr),(U32)&staraddr_next,sizeof(startaddr));
    }

    startaddr = BE2ME32(startaddr);
    staraddr_next = BE2ME32(staraddr_next);

    //printf("startaddr=0x%X\n",startaddr);
    //printf("staraddr_next=0x%X\n",staraddr_next);

    struct_string_info.startaddr = startaddr;
    struct_string_info.length = (U16)(staraddr_next-startaddr);

    //printf("struct_string_info.length=%u\n",struct_string_info.length);

    return struct_string_info;
}

static void msAPI_OCP_ReadBinaryString_ptr(U8 language, U16 id, U16 *pu16stringbuffer)
{
    DEBUG_STRING( printf("msAPI_OCP_ReadBinaryString_ptr(lang=%u,id=%u)\n", language, id); );

    U32 language_addr;
    OSDcp_string_info_table struct_string_info;
    U8 CHAR_BUFFER2[STRBUFF_LENGTH];

    //printf("msAPI_OCP_ReadBinaryString_ptr(lang=%u, id=%u)\n", language, id);

    language_addr = readbin_language_addr(language);
    struct_string_info = readbin_string_info(language_addr, id);

    //printf("language_addr=0x%X\n", language_addr);
    //printf("startaddr=0x%X, length=0x%X\n", struct_string_info.startaddr, struct_string_info.length);

    if ( sStringBininfo.bodyEncodingMethod == ENCODING_UTF8 )
    {
        if(_bOCPFromMem)
        {
            //memcpy(CHAR_BUFFER2, (void *)_PA2VA((((STRING_START_MEMORY_TYPE & MIU1) ? (STRING_START_ADR | MIU_INTERVAL) : (STRING_START_ADR)) + sStringBininfo.headerSize + struct_string_info.startaddr)), struct_string_info.length);
            memcpy(CHAR_BUFFER2, (void *)_PA2VA(( msAPI_OCP_Get_StringBufAddr()+ sStringBininfo.headerSize + struct_string_info.startaddr)), struct_string_info.length);
        }
        else
        {
            MApi_BDMA_CopyFromResource(s_OCP_u32StringBinFlashAddr + sStringBininfo.headerSize + struct_string_info.startaddr,(U32)(&CHAR_BUFFER2[0]),struct_string_info.length);
        }


        msAPI_OCP_MappinUTF8ToUCS2( CHAR_BUFFER2, pu16stringbuffer, struct_string_info.length, STRBUFF_LENGTH );
        if ( pu16stringbuffer[0] == '\b' )
        {
            language_addr = readbin_language_addr(pu16stringbuffer[1]);
            struct_string_info = readbin_string_info(language_addr, id);
            MApi_BDMA_CopyFromResource(s_OCP_u32StringBinFlashAddr + sStringBininfo.headerSize + struct_string_info.startaddr,(U32)(&CHAR_BUFFER2[0]),struct_string_info.length);
            msAPI_OCP_MappinUTF8ToUCS2( CHAR_BUFFER2, pu16stringbuffer, struct_string_info.length, STRBUFF_LENGTH );
        }
    }
    else if ( sStringBininfo.bodyEncodingMethod == ENCODING_FLAG_FOR_ONE_OR_TWO )
    {
        U8  i = 0, bUseOneOrTwoByte;

        if(_bOCPFromMem)
        {
            //memcpy(CHAR_BUFFER2, (void *)_PA2VA((((STRING_START_MEMORY_TYPE & MIU1) ? (STRING_START_ADR | MIU_INTERVAL) : (STRING_START_ADR)) + sStringBininfo.headerSize + struct_string_info.startaddr)), struct_string_info.length);
            memcpy(CHAR_BUFFER2, (void *)_PA2VA(( msAPI_OCP_Get_StringBufAddr() + sStringBininfo.headerSize + struct_string_info.startaddr)), struct_string_info.length);
        }
        else
        {
            MApi_BDMA_CopyFromResource(s_OCP_u32StringBinFlashAddr + sStringBininfo.headerSize + struct_string_info.startaddr,(U32)(&CHAR_BUFFER2[0]),struct_string_info.length);
        }

        bUseOneOrTwoByte = CHAR_BUFFER2[0];
        if ( bUseOneOrTwoByte == 1 )
        {
            for ( i = 1; i < struct_string_info.length; i++ )
            {
                pu16stringbuffer[i - 1] = ( U16 )CHAR_BUFFER2[i];
            }
        }
        else if ( bUseOneOrTwoByte == 2 )
        {
            memcpy( ( U8 * )pu16stringbuffer, CHAR_BUFFER2 + 1, struct_string_info.length - 1 );
        }
    }
    else
    {
        U32 i;

        if(_bOCPFromMem)
        {
            //memcpy(pu16stringbuffer, (void *)_PA2VA((((STRING_START_MEMORY_TYPE & MIU1) ? (STRING_START_ADR | MIU_INTERVAL) : (STRING_START_ADR)) + sStringBininfo.headerSize + struct_string_info.startaddr)), struct_string_info.length);
            memcpy(pu16stringbuffer, (void *)_PA2VA(( msAPI_OCP_Get_StringBufAddr() + sStringBininfo.headerSize + struct_string_info.startaddr)), struct_string_info.length);
        }
        else
        {
            MApi_BDMA_CopyFromResource(s_OCP_u32StringBinFlashAddr + sStringBininfo.headerSize + struct_string_info.startaddr,(U32)pu16stringbuffer,struct_string_info.length);
        }

        if (sStringBininfo.bodyEncodingMethod == ENCODING_UTF16_BIG_ENDIAN)
        {
            //convert from big endian to little
            for(i=0;i<struct_string_info.length/2;i++)
            {
                pu16stringbuffer[i]=BE2ME16(pu16stringbuffer[i]);
            }
        }
        if ( pu16stringbuffer[0] == '\b' ) //reduce the code size for duplicate characters
        {
            language_addr = readbin_language_addr(pu16stringbuffer[1]);
            struct_string_info = readbin_string_info(language_addr, id);

            if(_bOCPFromMem)
            {
                //memcpy(pu16stringbuffer, (void *)_PA2VA((((STRING_START_MEMORY_TYPE & MIU1) ? (STRING_START_ADR | MIU_INTERVAL) : (STRING_START_ADR)) + sStringBininfo.headerSize + struct_string_info.startaddr)), struct_string_info.length);
                memcpy(pu16stringbuffer, (void *)_PA2VA(( msAPI_OCP_Get_StringBufAddr() + sStringBininfo.headerSize + struct_string_info.startaddr)), struct_string_info.length);
            }
            else
            {
                MApi_BDMA_CopyFromResource( s_OCP_u32StringBinFlashAddr + sStringBininfo.headerSize + struct_string_info.startaddr,(U32)pu16stringbuffer,struct_string_info.length);
            }

            if (sStringBininfo.bodyEncodingMethod == ENCODING_UTF16_BIG_ENDIAN)
            {
                //convert from big endian to little
                for(i=0;i<struct_string_info.length/2;i++)
                {
                    pu16stringbuffer[i]=BE2ME16(pu16stringbuffer[i]);
                }
            }
        }
    }
}

static void msAPI_OCP_ReadBinaryString_ptr_memory(U8 language, U16 id, U16 *pu16stringbuffer)
{
    DEBUG_STRING( printf("msAPI_OCP_ReadBinaryString_ptr_memory(lang=%u,id=%u)\n", language, id); );

    U32 language_addr;
    OSDcp_string_info_table struct_string_info;
    U8 CHAR_BUFFER2[STRBUFF_LENGTH];

    //printf("msAPI_OCP_ReadBinaryString_ptr_memory(lang=%u, id=%u)\n", language, id);

    language_addr = readbin_language_addr(language);
    struct_string_info = readbin_string_info(language_addr, id);

    //printf("language_addr=0x%X\n", language_addr);
    //printf("startaddr=0x%X, length=0x%X\n", struct_string_info.startaddr, struct_string_info.length);

    if ( sStringBininfo.bodyEncodingMethod == ENCODING_UTF8 )
    {
        //msAPI_MIU_Copy(((STRING_START_MEMORY_TYPE & MIU1) ? (STRING_START_ADR | MIU_INTERVAL) : (STRING_START_ADR)) + struct_string_info.startaddr, XD2PHY(&(CHAR_BUFFER2[0])), struct_string_info.length, MIU_SDRAM2SDRAM);
        msAPI_MIU_Copy( msAPI_OCP_Get_StringBufAddr() + struct_string_info.startaddr, XD2PHY(&(CHAR_BUFFER2[0])), struct_string_info.length, MIU_SDRAM2SDRAM);

        msAPI_OCP_MappinUTF8ToUCS2( CHAR_BUFFER2, pu16stringbuffer, struct_string_info.length, STRBUFF_LENGTH );
        if ( pu16stringbuffer[0] == '\b' )
        {
            language_addr = readbin_language_addr(pu16stringbuffer[1]);
            struct_string_info = readbin_string_info(language_addr, id);
            //msAPI_MIU_Copy(((STRING_START_MEMORY_TYPE & MIU1) ? (STRING_START_ADR | MIU_INTERVAL) : (STRING_START_ADR)) + struct_string_info.startaddr, XD2PHY(&(CHAR_BUFFER2[0])), struct_string_info.length, MIU_SDRAM2SDRAM);
            msAPI_MIU_Copy( msAPI_OCP_Get_StringBufAddr() + struct_string_info.startaddr, XD2PHY(&(CHAR_BUFFER2[0])), struct_string_info.length, MIU_SDRAM2SDRAM);
            msAPI_OCP_MappinUTF8ToUCS2( CHAR_BUFFER2, pu16stringbuffer, struct_string_info.length, STRBUFF_LENGTH );
        }
    }
    else if ( sStringBininfo.bodyEncodingMethod == ENCODING_FLAG_FOR_ONE_OR_TWO )
    {
        U8  i = 0, bUseOneOrTwoByte;

        //msAPI_MIU_Copy(((STRING_START_MEMORY_TYPE & MIU1) ? (STRING_START_ADR | MIU_INTERVAL) : (STRING_START_ADR)) + struct_string_info.startaddr, XD2PHY(&(CHAR_BUFFER2[0])), struct_string_info.length, MIU_SDRAM2SDRAM);
        msAPI_MIU_Copy( msAPI_OCP_Get_StringBufAddr() + struct_string_info.startaddr, XD2PHY(&(CHAR_BUFFER2[0])), struct_string_info.length, MIU_SDRAM2SDRAM);

        bUseOneOrTwoByte = CHAR_BUFFER2[0];
        if ( bUseOneOrTwoByte == 1 )
        {
            for ( i = 1; i < struct_string_info.length; i++ )
            {
                pu16stringbuffer[i - 1] = ( U16 )CHAR_BUFFER2[i];
            }
        }
        else if ( bUseOneOrTwoByte == 2 )
        {
            memcpy( ( U8 * )pu16stringbuffer, CHAR_BUFFER2 + 1, struct_string_info.length - 1 );
        }
    }
    else
    {
        //msAPI_MIU_Copy(((STRING_START_MEMORY_TYPE & MIU1) ? (STRING_START_ADR | MIU_INTERVAL) : (STRING_START_ADR)) + struct_string_info.startaddr, XD2PHY(&(pu16stringbuffer[0])), struct_string_info.length, MIU_SDRAM2SDRAM);
        msAPI_MIU_Copy( msAPI_OCP_Get_StringBufAddr() + struct_string_info.startaddr, XD2PHY(&(pu16stringbuffer[0])), struct_string_info.length, MIU_SDRAM2SDRAM);

        if ( pu16stringbuffer[0] == '\b' )
        {
            language_addr = readbin_language_addr(pu16stringbuffer[1]);
            struct_string_info = readbin_string_info(language_addr, id);
            //msAPI_MIU_Copy(((STRING_START_MEMORY_TYPE & MIU1) ? (STRING_START_ADR | MIU_INTERVAL) : (STRING_START_ADR)) + struct_string_info.startaddr, XD2PHY(&(pu16stringbuffer[0])), struct_string_info.length, MIU_SDRAM2SDRAM);
            msAPI_MIU_Copy( msAPI_OCP_Get_StringBufAddr() + struct_string_info.startaddr, XD2PHY(&(pu16stringbuffer[0])), struct_string_info.length, MIU_SDRAM2SDRAM);
        }
    }
}

void msAPI_OCP_ReadBinaryString(U8 language, U16 id, U16 *pu16stringbuffer)
{
    DEBUG_STRING( printf("msAPI_OCP_ReadBinaryString(lang=%u,id=%u)\n", language, id); );

    switch (sStringBininfo.bodyCompressMethod)
    {
        case SLZ_COMPRESS:
        case LZSS_COMPRESS:
        case MS_COMPRESS:  //20091127EL
        case MS_COMPRESS7:
            msAPI_OCP_ReadBinaryString_ptr_memory(language, id, pu16stringbuffer);
            break;
        default:
            msAPI_OCP_ReadBinaryString_ptr(language, id, pu16stringbuffer);
            break;
    }
}

#if 0
void msAPI_OCP_LoadAllStringToMem(void)
{
    _bOCPFromMem = TRUE;
    if (sStringBininfo.headerSize+sStringBininfo.bodySize <= STRING_START_LEN)
    {
        MApi_BDMA_CopyFromResource(s_OCP_u32StringBinFlashAddr, _PA2VA( msAPI_OCP_Get_StringBufAddr() ) , sStringBininfo.headerSize+sStringBininfo.bodySize);
    }
    else
    {
        msWarning(ERR_OUT_OF_MEMORY);
    }
}
#endif

#if 0
//************************Font

typedef struct
{
    U32 magicNumber;
    U32 headerSize;
    U32 bodySize;
    U32 binaryType;
    U16 bodyCompressMethod;
    U32 bodyDecompressedSize;
}FontPackBinaryInfo;


void msAPI_OCP_ReadFontBoundary(U32 *pFontDataBoundary)
{

    MDrv_Flash_Read(osdcp_fontpack_addr+INFO_SIZE+sizeof(U32)/*count*/,sizeof(U32)*fontCount,(U8*)pFontDataBoundary);
}

U32 msAPI_OCP_PrepareFontPackBinary()//return the font count
{


    BININFO BinInfo;
    FontPackBinaryInfo info;

    fontCount=0;
    BinInfo.B_ID = BIN_ID_OSDCP_FONTPACK;

    if (msAPI_MIU_Get_BinInfo(&BinInfo) == PASS)
    {
        osdcp_fontpack_addr= BinInfo.B_FAddr;
    }

    /*read out information from FLASH*/
    MDrv_Flash_Read(osdcp_fontpack_addr,sizeof(info),(U8 *)&info);
    MDrv_Flash_Read(osdcp_fontpack_addr+INFO_SIZE,sizeof(U32),(U8*)&fontCount);
      alignedBodyLen=(U32)(((info.bodySize-1)/8+1)*8);
    //pFontDataBoundary=(U32 *)msAPI_Memory_Allocate(sizeof(U32)*2*fontCount);

    //MDrv_Flash_Read(osdcp_fontpack_addr+INFO_SIZE+sizeof(U32)/*count*/,sizeof(U32)*fontCount,(U8*)pFontDataBoundary);

    /*prepare the binary*/
     if(info.bodyCompressMethod==LZ_COMPRESS)
        {

            OCP_DBG(printf("FONT_DE_START:%lu, SRC_ADDR=%lu\n",msAPI_Timer_GetTime0(),VDEC_FRAMEBUFFER_ADR));

            MApi_BDMA_Copy(osdcp_fontpack_addr+info.headerSize,VDEC_FRAMEBUFFER_ADR,alignedBodyLen, MIU_FLASH2SDRAM);



            msAPI_LZ_Init(500);
            while(!msAPI_LZ_Decoder_Ready())
            {
                msAPI_Timer_Delayms(10);
            }
            OCP_DBG(printf("FONT_DE_READY:%lu\n",msAPI_Timer_GetTime0()));
            msAPI_LZ_StartDecompress(info.bodySize,VDEC_FRAMEBUFFER_ADR,msAPI_OCP_GetBmpAddr());

            msAPI_LZ_WaitDecompressFinished(5000);

            OCP_DBG(printf("FONT_DE_END:%lu\n",msAPI_Timer_GetTime0()));


        }
        else
        {
            MApi_BDMA_Copy(osdcp_fontpack_addr+info.headerSize,msAPI_OCP_GetBmpAddr(),alignedBodyLen, MIU_FLASH2SDRAM);
        }


    return fontCount;


}


//*****************
//*
//*****************
//for OSD resource





/*must be called before loading bitmap*/
FONTHANDLE msAPI_OCP_LoadSDRAMFont(U32 fontStartAddr, EN_FONT_TARGET_BPP u8TargetBPP)
{
    FONTHANDLE handle = INVALID_FONTHANDLE;
    FONT_BIN_HEADER         FontBinHeader;
    ST_LOAD_FONT_SDRAM_REPORT FontSdramInfo;

    u8TargetBPP=u8TargetBPP;

    if (!msAPI_Font_LoadSDRAMFont_Decompress(fontStartAddr, fontaddr, &FontBinHeader, &FontSdramInfo))
    {
        return INVALID_FONTHANDLE;
    }

    if (fontaddr + FontSdramInfo.u32SdramLen <= ((FONT_START_MEMORY_TYPE & MIU1) ? (FONT_START_ADR | MIU_INTERVAL) : (FONT_START_ADR)) + FONT_START_LEN)
    {
        handle = MDrv_GE_LoadFont( FontSdramInfo.u32StartAddr,
                                   FontSdramInfo.u32GlyphAddr,
                                   FontSdramInfo.u32BBoxAddr,
                                   FontSdramInfo.u32CodemapAddr,
                                   FontBinHeader.u32CharNum,
                                   FontBinHeader.u32CodemapBlockNum,
                                   FontBinHeader.u32Width,
                                   FontBinHeader.u32Height,
                                   FontBinHeader.u32BPP,
                                   FontBinHeader.u32CharGlyphBytes,
                                   FontBinHeader.u32Pitch,
                                   MIU_SDRAM
                                   );

        // calc for next font table starting address
        fontaddr = GE_ADDR_ALIGNMENT(fontaddr + FontSdramInfo.u32SdramLen);
    }
    else
        msWarning(ERR_FONT_OUT_OF_BUFFER);

    return handle;
}
#endif



/******************************************************************************/
///-Convert UTF8 to UCS2
///@param pu8Str \b IN
///@param pu16Str \b IN
///@param srcByteLen \b IN
///@param dstWideCharLen \b IN
///- pu8Str ...
///- pu16Str ...
///- srcByteLen ...
///- dstWideCharLen ...
/******************************************************************************/
U16 msAPI_OCP_MappinUTF8ToUCS2(U8 *pu8Str, U16 *pu16Str, U16 srcByteLen, U16 dstWideCharLen)
{
    //see reference from http://en.wikipedia.org/wiki/Utf-8
    U8 u8Value;
    U16 i, j;

    if ((pu8Str == 0) || (srcByteLen == 0) || (pu16Str == 0) || (dstWideCharLen <= 1)) return 0;

    for (i=0, j=0; i<srcByteLen && j<dstWideCharLen-1; i++, j++)
    {
        u8Value = pu8Str[i];
        if (u8Value == 0)
        {
            break;
        }
        if ((u8Value & 0x80) == 0)
        {
            // 0zzzzzzz(00-7F) => 00000000 0zzzzzzz
            pu16Str[j] = (U16) (u8Value & 0x7F);
        }
        else if (((u8Value & 0xE0) == 0xC0) && ((i+1)<srcByteLen))
        {
            // 110yyyyy(C2-DF) 10zzzzzz(80-BF) => 00000yyy yyzzzzzz
            pu16Str[j] = (U16) ( ((u8Value & 0x1F) << 6) | (pu8Str[i+1] & 0x3F) );
            i += 1;
        }
        else if (((u8Value & 0xF0) == 0xE0) && ((i+2)<srcByteLen))
        {
            // 1110xxxx(E0-EF) 10yyyyyy 10zzzzzz => xxxxyyyy yyzzzzzz
            pu16Str[j] = (U16) ( ((u8Value & 0xF) << 12) | ((pu8Str[i+1] & 0x3F) << 6) | (pu8Str[i+2] & 0x3F));
            i += 2;
        }
        else
        {
            // Unknown, skip
            j--;
            continue;
        }

        // convert control code
        if ( pu16Str[j]>=0x80 && pu16Str[j]<=0x9F )
        {
            pu16Str[j] = (0xE000 | pu16Str[j]);
        }
    }

    // NULL termination character
    pu16Str[j] = 0;

    return j;
}


#undef  MSAPI_OCP_C

