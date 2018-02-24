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
// (MStar Confidential Information) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
/// @file   drvdma.c
/// @brief  DRAM BDMA control driver
/// @author MStar Semiconductor Inc.
///
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Include List
////////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>

#include "Board.h"

#include "sysinfo.h"
#include "drvGlobal.h"

#include "SysInit.h"
#include "debug.h"

#include "MsCommon.h"
#include "drvSERFLASH.h"

#include "ms_decompress.h"

#include "msAPI_MIU.h"
#include "msAPI_DrvInit.h"
#include "msAPI_Flash.h"
#include "msAPI_BDMA.h"

#include "msAPI_Global.h"
#include "msAPI_Timer.h"

#include "Utl.h"

#if (ENABLE_FLASH_ON_DRAM)
#include "msAPI_FlashOnDram.h"
#endif


////////////////////////////////////////////////////////////////////////////////
// Local defines & local structures
////////////////////////////////////////////////////////////////////////////////
//#define DECOMPRESS_BLOCK_SIZE   (32*1024)

#define IS_ADDR_IN_RANGE(addr, memStart, memSize)   ( ((addr) >= (memStart)) && ((addr) < ((memStart)+(memSize)) ) )
#define IS_ADDR_IN_BMP_MEM(addr)                    IS_ADDR_IN_RANGE(addr, BMP_START_ADR, BMP_START_LEN)

#define ENABLE_DEBUG_BMP_MEM    0

////////////////////////////////////////////////////////////////////////////////
// Local Global Variables
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// External Funciton
////////////////////////////////////////////////////////////////////////////////
//extern void mhal_dcache_flush(U32 u32Base, U32 u32Size);


////////////////////////////////////////////////////////////////////////////////
// Global Funciton
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: _MApi_BDMA_Convert_Type()
/// @brief \b Function \b Description : convert type to bdma copy type
/// @param <IN>        \b eType       : MEMCOPYTYPE
/// @param <OUT>       \b None :
/// @param <RET>       \b BDMA_CpyType : BDMA copy type
/// @param <GLOBAL>    \b None        :
////////////////////////////////////////////////////////////////////////////////
static BDMA_CpyType _MApi_BDMA_Convert_Type(MEMCOPYTYPE eType)
{
    switch(eType)
    {
    case MIU_FLASH2SDRAM:
        return E_BDMA_FLASH2SDRAM;

    case MIU_SDRAM2SRAM:
        return E_BDMA_SDRAM2SRAM1K_HK51;

    case MIU_SDRAM2SDRAM:
    case MIU_SDRAM2SDRAM_I:
        return E_BDMA_SDRAM2SDRAM;

    case MIU_SDRAM02SDRAM1:
        return E_BDMA_SDRAM2SDRAM1;

    case MIU_SDRAM12SDRAM0:
        return E_BDMA_SDRAM12SDRAM;

    case MIU_SDRAM12SDRAM1:
        return E_BDMA_SDRAM12SDRAM1;

    case MIU_FLASH2VDMCU:
        return E_BDMA_FLASH2VDMCU;

    default:
        return E_BDMA_CPYTYPE_MAX;
    }

}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: MApi_BDMA_Copy()
/// @brief \b Function \b Description : Get Specific Bin information
/// @param <IN>        \b None        :
/// @param <OUT>       \b pBinInfo    : Get Bin Information
/// @param <RET>       \b BOOL     : Success or Fail
/// @param <GLOBAL>    \b None        :
////////////////////////////////////////////////////////////////////////////////
BDMA_Result MApi_BDMA_Copy(MS_PHYADDR u32Srcaddr, MS_PHYADDR u32Dstaddr, U32 u32Len, MEMCOPYTYPE eType)
{
    U8 u8OpCfg = (MIU_SDRAM2SDRAM_I == eType) ? BDMA_OPCFG_INV_COPY : BDMA_OPCFG_DEF;

    // Check address range
    CHECK_PHY_ADDR(u32Dstaddr);
    CHECK_PHY_ADDR(u32Srcaddr);

#if(ENABLE_DEBUG_BMP_MEM)
    if( MIU_FLASH2SDRAM == eType )
    {
        if( IS_ADDR_IN_BMP_MEM(u32Dstaddr) )
        {
            PRINT_CURRENT_LINE();
            printf("u32Srcaddr=0x%X, u32Dstaddr=0x%X, u32Dstaddr=0x%X\n", u32Srcaddr, u32Dstaddr, u32Len);
        }
    }
#endif

    switch( eType )
    {
        case MIU_FLASH2SDRAM:
            MDrv_SERFLASH_CopyHnd(u32Srcaddr, u32Dstaddr, u32Len, E_SPIDMA_DEV_MIU0, SPIDMA_OPCFG_DEF);
            break;

        case MIU_FLASH2VDMCU:
            MDrv_SERFLASH_CopyHnd(u32Srcaddr, u32Dstaddr, u32Len, E_SPIDMA_DEV_VDMCU, SPIDMA_OPCFG_DEF);
            break;

        default:
            MDrv_BDMA_CopyHnd(u32Srcaddr, u32Dstaddr, u32Len, _MApi_BDMA_Convert_Type(eType), u8OpCfg);
            break;
    }
    return E_BDMA_OK;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: MApi_BDMA_XCopy
/// @brief \b Function \b Description : Memory copy for specific operation
/// @param <IN>        \b type    : Memory copy operation type
/// @param <IN>        \b u32Srcaddr : Source address
/// @param <IN>        \b u32Dstaddr : Destination address
/// @param <IN>        \b u32Len     : Length of data
/// @param <OUT>       \b None    :
/// @param <RET>       \b None    :
/// @param <GLOBAL>    \b None    :
////////////////////////////////////////////////////////////////////////////////
BDMA_Result MApi_BDMA_XCopy(MCPY_TYPE eType, U32 u32Srcaddr, U32 u32Dstaddr, U32 u32Len)
{
    //PRINT_CURRENT_LINE();
    //printf("MApi_BDMA_XCopy( eType=%u, u32Srcaddr=0x%X, u32Dstaddr=0x%X, u32Dstaddr=0x%X\n", eType, u32Srcaddr, u32Dstaddr, u32Len);

    switch (eType)
    {
    case MCPY_LOADFONT:
    case MCPY_LOADBITMAP:

    #if(ENABLE_DEBUG_BMP_MEM)
        if( MCPY_LOADBITMAP == eType )
        {
            if( IS_ADDR_IN_BMP_MEM(u32Dstaddr) )
            {
                PRINT_CURRENT_LINE();
                printf("u32Srcaddr=0x%X, u32Dstaddr=0x%X, u32Dstaddr=0x%X\n", u32Srcaddr, u32Dstaddr, u32Len);
            }
        }
    #endif

        MApi_BDMA_CopyFromResource(u32Srcaddr,_PA2VA(u32Dstaddr),u32Len);
        break;

    case MCPY_LOADVDMCUFW:
        MApi_BDMA_Copy(u32Srcaddr, u32Dstaddr, u32Len, MIU_FLASH2VDMCU);
        break;

    case MCPY_LOADLOGO:
    #if(ENABLE_FLASH_ON_DRAM)
        if( msAPI_FlashOnDram_IsDataOnDram(u32Srcaddr, u32Len ) )
        {
            if( FALSE == msAPI_FlashOnDram_CopyDataToDram(u32Srcaddr, u32Dstaddr, u32Len ) )
            {
                return E_BDMA_FAIL;
            }
        }
        else
    #endif
        {
            MApi_BDMA_Copy(u32Srcaddr, u32Dstaddr, u32Len, MIU_FLASH2SDRAM);
        }

        break;

    case MCPY_CCS:
        MApi_BDMA_Copy(u32Srcaddr, u32Dstaddr, u32Len, MIU_SDRAM2SDRAM);
        break;

    default:
        MS_DEBUG_MSG(printf("BDMA Xcopy not support:%u", eType));
        break;
    }

    return E_BDMA_OK;
}

BOOLEAN (*DoDecompressionFunc)(U8 *pSrc, U8 *pDst, U8 *pTmp, U32 srclen);


char* GetComprressName(U8 u8Comp)
{
    char* pName = "Unknown";

    switch (u8Comp)
    {
        case LZSS_COMPRESS:
        {
            pName = "LZSS";
            break;
        }

        case MS_COMPRESS:
        {
            pName = "G";
            break;
        }

        case MS_COMPRESS7:
        {
            pName = "7";
            break;
        }

        default:
            pName = "Un-Defined";
            break;
    }

    return pName;
}

#if(ENABLE_BIN_FILE_CRC)

#define DEBUG_CHECK_BIN_CRC(x)  //x
BOOL MApi_BDMA_CheckBinCRC(U16 u16BinId, U32 u32BinLen, U32 u32BinBuf_VA)
{
    DEBUG_CHECK_BIN_CRC( PRINT_CURRENT_LINE(); );
    DEBUG_CHECK_BIN_CRC( printf("Check binId=0x%X, u32BinLen=0x%X\n", u16BinId, u32BinLen ); );

    DEBUG_CHECK_BIN_CRC( U32 u32T1 = MsOS_GetSystemTime(); );

#if 1
    U16 u16Crc = msAPI_CRC16_BinFile( (U8*)u32BinBuf_VA, u32BinLen);

    if( 0 != u16Crc )
    {
        printf("\nError: bin file(0x%X) CRC error! %X\n", u16BinId, u16Crc);
        msDebug_FatalErrorHandler_Para_2(FATAL_ERR_ID_BIN_FILE_CRC_ERROR, u16Crc, 0);
        return FALSE;
    }

    DEBUG_CHECK_BIN_CRC( printf(" Use %u\n", msAPI_Timer_DiffTime_2(u32T1, MsOS_GetSystemTime())); );

#else
    U16 u16Crc1, u16Crc2;

    u16Crc1 = *(U8*)(u32BinBuf_VA+u32BinLen-2);
    u16Crc1 = (u16Crc1<<8) + *(U8*)(u32BinBuf_VA+u32BinLen-1);

    u16Crc2 = msAPI_CRC16_BinFile( (U8*)u32BinBuf_VA, u32BinLen-2);

    DEBUG_CHECK_BIN_CRC( printf(" u16Crc1=0x%X, u16Crc2=0x%X\n", u16Crc1, u16Crc2 ); );

    if( u16Crc1 != u16Crc2 )
    {
        printf("\nError: bin file(0x%X) CRC error! %X %X\n", u16BinId, u16Crc1, u16Crc2);
        msDebug_FatalErrorHandler_Para_2(FATAL_ERR_ID_BIN_FILE_CRC_ERROR, u16Crc1, u16Crc2);
        return FALSE;
    }
#endif

    return TRUE;
}
#endif

extern U8 g_MsDecomp7_u8Debug;

#define DEBUG_DMA_LOADBIN(x)    //x

eRETCODE MDrv_DMA_LoadBin(BININFO *pBinInfo, U32 u32DstVA, U32 u32DecVA, U32 u32TmpVA)
{
    U32 u32BinLen;
    U32 u32BinAddr;
    int i;
    U8* pu8DecompTmpBuf = (U8 *)(u32TmpVA & NON_CACHEABLE_TO_CACHEABLE_MASK);

    u32BinLen = pBinInfo->B_Len;
    u32BinAddr = pBinInfo->B_FAddr;

    DEBUG_DMA_LOADBIN( printf("\n >> MDrv_DMA_LoadBin(0x%X, %s)\n",
                        pBinInfo->B_ID, GetComprressName(pBinInfo->B_IsComp)) );

    DEBUG_DMA_LOADBIN( printf(" u32DstVA=0x%X\n", u32DstVA); );
    DEBUG_DMA_LOADBIN( printf(" u32DecVA=0x%X\n", u32DecVA); );
    DEBUG_DMA_LOADBIN( printf(" u32TmpVA=0x%X\n", u32TmpVA); );

    DEBUG_DMA_LOADBIN( printf(" u32BinLen=0x%X\n", u32BinLen); );
    DEBUG_DMA_LOADBIN( printf(" u32BinAddr=0x%X\n", u32BinAddr); );

#if(ENABLE_DEBUG_BMP_MEM)
    //if( MCPY_LOADBITMAP == eType )
    {
        if( IS_ADDR_IN_BMP_MEM( MsOS_VA2PA(u32DstVA) ) )
        {
            PRINT_CURRENT_LINE();
            printf("u32DstVA=0x%X, u32DecVA=0x%X, u32TmpVA=0x%X\n", u32DstVA, u32DecVA, u32TmpVA);
        }
    }
#endif

    CHECK_MIU_PROTECT_LOG_AND_CLEAR();

    switch(pBinInfo->B_IsComp)
    {
        case LZSS_COMPRESS:
        {
            // fixme: need to find a buffer to put compressed data => u32DecAddr
        #if 1
            printf("\nError: Not uspport LZSS!\n");
        #else
          #if (ENABLE_BOOTTIME)
             gU32CompressStepTime = msAPI_Timer_GetTime0();
          #endif

            MApi_BDMA_CopyFromResource(u32BinAddr,u32DecVA,u32BinLen);

          #if (ENABLE_BOOTTIME)
            gU32TmpTime = msAPI_Timer_DiffTimeFromNow(gU32CompressStepTime);
            printf("[TIME] [CopyFromResource]Bin ID = %x, Copy time = %ld\n",
                        pBinInfo->B_ID, msAPI_Timer_DiffTimeFromNow(gU32TmpTime));
            gU32CompressStepTime = msAPI_Timer_GetTime0();
          #endif

            if (ms_DecompressInit((U8*)u32DstVA) == FALSE)
            {
                printf("decompress fail!\n");
                return FAILURE;
            }

            ms_Decompress((U8*)u32DecVA, u32BinLen);
            ms_DecompressDeInit();

          #if (ENABLE_BOOTTIME)
            gU32TmpTime = msAPI_Timer_DiffTimeFromNow(gU32CompressStepTime);
            gU32CompressTotalStepTime += gU32TmpTime;
            printf("[TIME] [Decompress time]Bin ID = %x, Decompress time = %ld\n", pBinInfo->B_ID, gU32TmpTime);
          #endif
        #endif
            break;
        }

        case MS_COMPRESS:
        case MS_COMPRESS7:
        {
            U32 OriginalFileLength = 0;

          #if (ENABLE_BOOTTIME)
            gU32CompressStepTime = msAPI_Timer_GetTime0();
          #endif


            MApi_BDMA_CopyFromResource(u32BinAddr, u32DecVA, u32BinLen);

        #if (ENABLE_BIN_FILE_CRC)
            // Check bin CRC16
            //PRINT_CURRENT_LINE();
            MApi_BDMA_CheckBinCRC(pBinInfo->B_ID, u32BinLen, u32DecVA);
        #endif


          #if (ENABLE_BOOTTIME)
            gU32TmpTime = msAPI_Timer_DiffTimeFromNow(gU32CompressStepTime);
            printf("[TIME] [CopyFromResource]Bin ID = %x, Copy time = %ld\n",
                        pBinInfo->B_ID, msAPI_Timer_DiffTimeFromNow(gU32TmpTime));
            gU32CompressStepTime = msAPI_Timer_GetTime0();
          #endif

            //Print_Buffer( (U8*)u32DecVA, 16 );

            //search compressed file real length
            for(i=3;i<12;i++)
            {
                if ( *((U8 *)(u32DecVA+u32BinLen-i)) == 0xEF )
                {
                    if ( *((U8 *)(u32DecVA+u32BinLen-i-1)) == 0xBE )
                        u32BinLen -= (i+1);
                }
            }

            //printf(" CRC2_1=0x%X\n", msAPI_CRC_Cal( (U8*)u32DecVA, u32BinLen) );

            DEBUG_DMA_LOADBIN( printf(" Compressed File real Len = %u(0x%X)\n", u32BinLen, u32BinLen); );

            // restore the real length of decompressed bin to Bininfo 20100108EL
            if ( pBinInfo->B_IsComp == MS_COMPRESS7 )
            {
                DoDecompressionFunc = DoMsDecompression7;

                for (i = 0; i < 8; i++)
                {
                    OriginalFileLength += ( (U32)((U8 *)u32DecVA)[5 + i] << (i << 3) );
                }

                pBinInfo->B_Len = OriginalFileLength;
                DEBUG_DMA_LOADBIN( printf(" Original File Length = %u(0x%X)\n", OriginalFileLength, OriginalFileLength); );

            #if( ENABLE_DECOMP7_USE_HK_MEMORY )
                pu8DecompTmpBuf = g_au8Decomp7TmpBuf;
            #endif
            }
            else
            {
                DoDecompressionFunc = DoMsDecompression;

                memcpy(&(pBinInfo->B_Len), (void*)(u32DecVA+u32BinLen-4), 4);
                //printf("^^^G3^^^ pBinInfo->B_Len = %ld\n", pBinInfo->B_Len);
            }

            //printf(" CRC2_2=0x%X\n", msAPI_CRC_Cal( (U8*)u32DecVA, u32BinLen) );

            //g_MsDecomp7_u8Debug = 1;

            if( !DoDecompressionFunc(
                        (U8 *)(u32DecVA & NON_CACHEABLE_TO_CACHEABLE_MASK),
                        (U8 *)(u32DstVA & NON_CACHEABLE_TO_CACHEABLE_MASK),
                    #if 1
                        pu8DecompTmpBuf,
                    #else
                        (U8 *)(u32TmpVA & NON_CACHEABLE_TO_CACHEABLE_MASK),
                    #endif
                        u32BinLen )
              )
            {
                printf("\nError: DoDecompressionFunc fail!\n");
                return FAILURE;
            }

            MsOS_Dcache_Flush((MS_U32)((u32DstVA & NON_CACHEABLE_TO_CACHEABLE_MASK) & (~15)),(MS_U32)((pBinInfo->B_Len+15) & (~15)));
            MsOS_FlushMemory();

            //printf(" CRC3=0x%X\n", msAPI_CRC_Cal( (U8*)u32DstVA, OriginalFileLength) );

          #if (ENABLE_BOOTTIME)
            gU32TmpTime = msAPI_Timer_DiffTimeFromNow(gU32CompressStepTime);
            gU32CompressTotalStepTime += gU32TmpTime;
            printf("[TIME] [Decompress time]Bin ID = %x, Decompress time = %ld\n", pBinInfo->B_ID, gU32TmpTime);
          #endif

            break;
        }

        default:    //no compressed bin
        {
        #if (!BLOADER)

            if ( (pBinInfo->B_ID == BIN_ID_OSDCP_TEXT)
             #if( VDEC_BIN_IS_FW_VPU )
               ||(pBinInfo->B_ID == BIN_ID_CODE_VDEC_FW_VPU)
             #else
              #if(SUPPORT_VDEC_2_0 == 0)
               ||(pBinInfo->B_ID == BIN_ID_CODE_AEON_MVD)
              #endif
               ||(pBinInfo->B_ID == BIN_ID_CODE_AEON_H264)  //20100422EL Add
             #endif

             #if( (CHIP_FAMILY_TYPE==CHIP_FAMILY_NASA)&& (CHIP_SUPPORT_HEVC) ) //IMPLEMENT_DTV_H265
               ||(pBinInfo->B_ID == BIN_ID_CODE_AEON_H265)
             #endif
               ||(pBinInfo->B_ID == FONT_MSTAR_UNICODE_MVF) //20100301EL
               )
            {
                //printf("~~~~~~~~Do nothing at these bins !!\n");
            }
            else
            {
                MApi_BDMA_CopyFromResource(u32BinAddr,u32DstVA,u32BinLen);
                //printf(" CRC1=0x%X\n", msAPI_CRC_Cal( (U8*)u32DstVA, u32BinLen) );

            #if(ENABLE_BIN_FILE_CRC)
                // Cal CRC16
                //if( pBinInfo->B_ID == BIN_ID_CODE_DEMUX )
                {
                    //PRINT_CURRENT_LINE();
                    MApi_BDMA_CheckBinCRC(pBinInfo->B_ID, u32BinLen, u32DstVA);
                }
            #endif

            }

        #else
            MApi_BDMA_CopyFromResource(u32BinAddr,u32DstVA,u32BinLen);
        #endif

            break;
        }
    }

    CHECK_MIU_PROTECT_LOG_AND_CLEAR();

    return SUCCESS;
}

/*
eRETCODE MDrv_DMA_Copy(U32 u32Srcaddr, U32 u32Dstaddr, U32 u32Len, MEMCOPYTYPE eType)
{
    MApi_BDMA_Copy(u32Srcaddr, u32Dstaddr, u32Len, eType);
    return SUCCESS;
}
*/

eRETCODE MApi_BDMA_CopyFromResource(U32 offset,U32 destVA,U32 len)
{
    //printf("MApi_BDMA_CopyFromResource(offset=0x%X, destVA=0x%X, len=0x%x)\n", offset, destVA, len);

#if 1 // use BDMA
    BDMA_Result enBDMA_Result = E_BDMA_OK;
    U32 u32PhyAdr = MsOS_VA2PA(destVA);


  #if(ENABLE_DEBUG_BMP_MEM)
    {
        if( IS_ADDR_IN_BMP_MEM( u32PhyAdr ) )
        {
            PRINT_CURRENT_LINE();
            printf("offset=0x%X, destVA=0x%X, len=0x%X\n", offset, destVA, len);
        }
    }
  #endif


    CHECK_PHY_ADDR(u32PhyAdr);

  #if(ENABLE_FLASH_ON_DRAM)
    if( msAPI_FlashOnDram_IsDataOnDram(offset, len ) )
    {
        if( FALSE == msAPI_FlashOnDram_CopyDataToDram(offset, u32PhyAdr, len ) )
        {
            return FAILURE;
        }
    }
    else
  #endif
    {
        enBDMA_Result = MApi_BDMA_Copy(offset, u32PhyAdr, len, MIU_FLASH2SDRAM);

        if( enBDMA_Result != E_BDMA_OK )
            return FAILURE;
    }

#else
    // change to use msAPI_Flash_Read due to strange stuck problems when BDMA small amount of data
    msAPI_Flash_Read(offset, len, (U8 *)destVA);
#endif


    return SUCCESS;
}

