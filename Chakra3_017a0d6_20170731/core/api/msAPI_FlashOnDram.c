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
////////////////////////////////////////////////////////////////////////////////

#include "Board.h"


#if (ENABLE_FLASH_ON_DRAM)

#include "debug.h"
#include "mstar_debug.h"
#include "Utl.h"

#include "drvBDMA.h"

#include "msAPI_Global.h"
#include "msAPI_Timer.h"

#include "msAPI_FlashOnDram.h"


#define FOD_CHECK_MEM_CRC   0


#define FOD_MAGIC_ID_OFFSET     (0)
#define FOD_DATA_START_OFFSET   (4)
#define FOD_DATA_SIZE_OFFSET    (8)


static BOOLEAN g_FOD_bEnableFlashOnDram = FALSE;

static U32 g_FOD_u32DataFlashStartAddr = 0;
static U32 g_FOD_u32DataFlashEndAddr = 0;

static U32 g_FOD_u32DataDramStartAddr = 0;
static U32 g_FOD_u32DataSize = 0;

#if(FOD_CHECK_MEM_CRC)
static U32 g_FOD_u32DramDataCRC = 0;
#endif

#define DEBUG_FOD(x)    //x

void msAPI_FlashOnDram_Init(void)
{
    //PRINT_CURRENT_LINE();

    // Check if bin files already on dram...
    U32* pu32Header = (U32*)MsOS_PA2KSEG1(FOD_DRAM_BASE);

    U32 u32MagicId = pu32Header[0];
    g_FOD_u32DataDramStartAddr = pu32Header[1];
    g_FOD_u32DataSize = pu32Header[2];

    DEBUG_FOD( printf("u32MagicId=0x%X\n", u32MagicId); );
    DEBUG_FOD( printf("g_FOD_u32DataDramStartAddr=0x%X\n", g_FOD_u32DataDramStartAddr); );
    DEBUG_FOD( printf("g_FOD_u32DataDramSize=0x%X\n", g_FOD_u32DataSize); );


    if( u32MagicId != FOD_MAGIC_ID )
    {
        printf("\nError: FOD magic id is wrong! (0x%X)\n", u32MagicId);
        return;
    }


    g_FOD_bEnableFlashOnDram = TRUE;
    g_FOD_u32DataFlashStartAddr = g_FOD_u32DataDramStartAddr - FOD_DRAM_BASE;
    g_FOD_u32DataFlashEndAddr = g_FOD_u32DataFlashStartAddr + g_FOD_u32DataSize - 1;

    DEBUG_FOD( printf("g_FOD_u32DataFlashStartAddr=0x%X\n", g_FOD_u32DataFlashStartAddr); );
    DEBUG_FOD( printf("g_FOD_u32DataFlashEndAddr=0x%X\n", g_FOD_u32DataFlashEndAddr); );

#if(FOD_CHECK_MEM_CRC)
    PRINT_CURRENT_LINE();
    g_FOD_u32DramDataCRC = msAPI_CRC_Cal( (U8*)MsOS_PA2KSEG0(g_FOD_u32DataDramStartAddr), g_FOD_u32DataSize);
    printf("g_FOD_u32DramDataCRC=0x%X\n", g_FOD_u32DramDataCRC);
#endif

}

#define DEBUG_FOD_RANGE(x)  //x
BOOLEAN msAPI_FlashOnDram_IsDataOnDram(U32 u32FlashAddr, U32 u32Size )
{
    //return FALSE;
    //PRINT_CURRENT_LINE();
    DEBUG_FOD_RANGE( msDebug_ANSI_SetColorText_2(E_FONT_COLOR_BLACK, E_FONT_BACKGROUND_COLOR_PURPLE); );
    DEBUG_FOD_RANGE( printf("msAPI_FlashOnDram_IsDataOnDram(0x%X,0x%X)\n", u32FlashAddr, u32Size); );
    DEBUG_FOD_RANGE( msDebug_ANSI_AllAttrOffText(); );

    if( !g_FOD_bEnableFlashOnDram )
    {
        printf(" => False\n");
        return FALSE;
    }

    U32 u32DataFlashEndAddr = u32FlashAddr + u32Size - 1;
    DEBUG_FOD_RANGE( printf("u32DataFlashEndAddr=0x%X\n", u32DataFlashEndAddr); );

    if( (u32FlashAddr >= g_FOD_u32DataFlashStartAddr)
      &&(u32DataFlashEndAddr <= g_FOD_u32DataFlashEndAddr)
      )
    {
        DEBUG_FOD_RANGE( printf(" => True\n"); );
        return TRUE;
    }

    DEBUG_FOD_RANGE( printf(" => False\n"); );
    return FALSE;
}

BOOLEAN msAPI_FlashOnDram_CopyDataToDram(U32 u32FlashAddr, U32 u32DramAddr, U32 u32Size )
{
    //PRINT_CURRENT_LINE();
    DEBUG_FOD( msDebug_ANSI_SetColorText_2(E_FONT_COLOR_BLACK, E_FONT_BACKGROUND_COLOR_YELLOW); );
    DEBUG_FOD( printf("msAPI_FlashOnDram_CopyDataToDram(0x%X,0x%X,0x%X)\n", u32FlashAddr, u32DramAddr, u32Size); );
    DEBUG_FOD( msDebug_ANSI_AllAttrOffText(); );


    if( !g_FOD_bEnableFlashOnDram )
    {
        printf("\nError: Flash no on dram!\n");
        return FALSE;
    }

#if(FOD_CHECK_MEM_CRC)
    PRINT_CURRENT_LINE();
    U32 u32CurCRC = msAPI_CRC_Cal( (U8*)MsOS_PA2KSEG0(g_FOD_u32DataDramStartAddr), g_FOD_u32DataSize);
    printf("u32CurCRC=0x%X\n", u32CurCRC);
    if( u32CurCRC != g_FOD_u32DramDataCRC )
    {
        PRINT_CURRENT_LINE();
        printf("\nError: CRC changed! u32CurCRC=0x%X, g_FOD_u32DramDataCRC=0x%X\n", u32CurCRC, g_FOD_u32DramDataCRC);
    }
#endif


    U32 u32CopyDramSrcAddr = u32FlashAddr + FOD_DRAM_BASE;
    DEBUG_FOD( printf("u32CopyDramSrcAddr=0x%X\n", u32CopyDramSrcAddr); );

    //U32 t1 = MsOS_GetSystemTime();

#if 0 // Use CPU copy
    memcpy( (U8*)MsOS_PA2KSEG0(u32DramAddr), (U8*)MsOS_PA2KSEG0(u32CopyDramSrcAddr), u32Size );
    MsOS_Dcache_Flush( (MS_U32)MsOS_PA2KSEG0(u32DramAddr), u32Size);

#else

    BDMA_Result eResult = MDrv_BDMA_MemCopy(u32CopyDramSrcAddr, u32DramAddr, u32Size);
    if( E_BDMA_OK != eResult )
    {
        printf("BDMA eResult=%u\n", eResult );
    }

#endif

    //printf("BDMA use %u\n", msAPI_Timer_DiffTime_2(t1, MsOS_GetSystemTime()));

    MsOS_FlushMemory();

    return TRUE;
}

void msAPI_FlashOnDram_Disable(void)
{
    g_FOD_bEnableFlashOnDram = FALSE;
}

#endif // #if(ENABLE_FLASH_ON_DRAM)

