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

#define MAPP_LOADFONTINIT_C


#include <stdlib.h>
#include <stdio.h>
#include "MsCommon.h"
#include "msAPI_MIU.h"

// Common Definition
#include "apiXC.h"
#include "MApp_LoadFontInit.h"
#include "MApp_Font.h"
#include "MApp_ZUI_ACTglobal.h"
#include "BinInfo.h"
#include "InfoBlock.h"
#include "MApp_GlobalVar.h"

#if ( ENABLE_TTF_FONT )
#include "msAPI_MLE_font_base.h"
#include "msAPI_MLE_font_vector.h"
#endif

#if defined( TTF_BUFFER_ADR )
    #define TTF_DEC_BUFFER_OFFSET (TTF_BUFFER_LEN-0x21000)
    #define TTF_DEC_BUFFER_ADR (TTF_BUFFER_ADR+TTF_DEC_BUFFER_OFFSET)
    #define TTF_TMP_BUFFER_OFFSET (TTF_BUFFER_LEN-0x10800)
    #define TTF_TMP_BUFFER_ADR (TTF_BUFFER_ADR+TTF_TMP_BUFFER_OFFSET)
#endif //defined( TTF_BUFFER_ADR )

///////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////

//**********************************************************
#if (VECTOR_FONT_ENABLE)
extern BOOLEAN msAPI_MVF_init_mempool (void *pool, U32 size);
#endif

//**********************************************************
BOOLEAN bFontSysInit = FALSE;

#if (VECTOR_FONT_ENABLE)

#if (UI_SKIN_SEL == UI_SKIN_960X540X565)
LOADFONT_STRUCT g_astVecFont_info[] =
{
    {
        .FontID = 0,
        .output_bpp = 2,
        .output_size = 23,
        .output_width = 20,
        .output_height = 26,
        .unicode_from = { 0x0020, 0},
        .unicode_to = { 0xFFFF, 0},
    },
    {
        .FontID = 1,
        .output_bpp = 2,
        .output_size = 18,
        .output_width = 16,
        .output_height = 21,
        .unicode_from = { 0x0020, 0},
        .unicode_to = { 0xFFFF, 0},
    },
    {
        .FontID = 2,
        .output_bpp = 2,
        .output_size = 14,
        .output_width = 12,
        .output_height = 16,
        .unicode_from = { 0x0020, 0},
        .unicode_to = { 0xFFFF, 0},
    },
};
#elif (UI_SKIN_SEL == UI_SKIN_1920X1080X565)
LOADFONT_STRUCT g_astVecFont_info[] =
{
    {
        .FontID = 0,
        .output_bpp = 2,
        .output_size = 35,
        .output_width = 30,
        .output_height = 40,
        .unicode_from = { 0x0020, 0},
        .unicode_to = { 0xFFFF, 0},
    },
    {
        .FontID = 1,
        .output_bpp = 2,
        .output_size = 28,
        .output_width = 24,
        .output_height = 32,
        .unicode_from = { 0x0020, 0},
        .unicode_to = { 0xFFFF, 0},
    },
    {
        .FontID = 2,
        .output_bpp = 2,
        .output_size = 22,
        .output_width = 19,
        .output_height = 25,
        .unicode_from = { 0x0020, 0},
        .unicode_to = { 0xFFFF, 0},
    },
};
#else
LOADFONT_STRUCT g_astVecFont_info[] =
{
    {
        .FontID = 0,
        .output_bpp = 2,
        .output_size = 35,
        .output_width = 30,
        .output_height = 40,
        .unicode_from = { 0x0020, 0},
        .unicode_to = { 0xFFFF, 0},
    },
    {
        .FontID = 1,
        .output_bpp = 2,
        .output_size = 28,
        .output_width = 24,
        .output_height = 32,
        .unicode_from = { 0x0020, 0},
        .unicode_to = { 0xFFFF, 0},
    },
    {
        .FontID = 2,
        .output_bpp = 2,
        .output_size = 22,
        .output_width = 19,
        .output_height = 25,
        .unicode_from = { 0x0020, 0},
        .unicode_to = { 0xFFFF, 0},
    },
};
#endif

#endif // VECTOR_FONT_ENABLE

LOADFONT_STRUCT ttf_font_info[] =
{
    {
        .FontID = FONT_0,
        .output_bpp = 2,
        .output_size =18,
        .output_width = 18,
        .output_height = 23,
        .unicode_from = { 0x0020, 0},
        .unicode_to = { 0xFFFF, 0},
    },

    {
        .FontID = FONT_1,
        .output_bpp = 2,
        .output_size = 24.5,
        .output_width = 21,
        .output_height = 28,
        .unicode_from = { 0x0020, 0},
        .unicode_to = { 0xFFFF, 0},
    },

    {
        .FontID = FONT_2,
        .output_bpp = 2,
        .output_size = 35,
        .output_width = 30,
        .output_height = 40,
        .unicode_from = { 0x0020, 0},
        .unicode_to = { 0xFFFF, 0},
    },

    {
        .FontID = FONT_0,
        .output_bpp = 2,
        .output_size = 20,
        .output_width = 21,
        .output_height = 28,
        .unicode_from = { 0x0020, 0},
        .unicode_to = { 0xFFFF, 0},
    },
};

LOADFONT_PAIR fontpair[] =
{
#if (ENABLE_DVB_TAIWAN_APP || ENABLE_BIG5_TO_UNICODE ||CHINESE_BIG5_FONT_ENABLE)
    {FONT_BIG5,FONT_BIG5_I2},

#elif  (ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP||CHINESE_SIMP_FONT_ENABLE)
    {FONT_CHINESE,FONT_CHINESE_I2},

#else

    {FONT_CHINESE,FONT_CHINESE_I2},

#endif
};

#if VECTOR_FONT_ENABLE
void MApp_LoadFontInit_VEC(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START(););

    DEBUG_LOAD_VF(printf("MApp_LoadFontInit_VEC()\n"););

    U8 u8num = sizeof(g_astVecFont_info)/sizeof(LOADFONT_STRUCT) - 1;

    MApp_LoadFont_SetVecFontInfo(g_astVecFont_info, 0, u8num);

#if (ENABLE_ARABIC_OSD)
    Font[FONT_ARABIC_0].fHandle = msAPI_Font_LoadFlashFontToSDRAM(BIN_ID_FONT_ARABIC_35);
    FontHandleIndex[Font[FONT_ARABIC_0].fHandle] = FONT_ARABIC_0;
   // Font[FONT_ARABIC_1].fHandle = msAPI_Font_LoadFlashFontToSDRAM(BIN_ID_FONT_ARABIC_30);
   // FontHandleIndex[Font[FONT_ARABIC_1].fHandle] = FONT_ARABIC_1;
   // Font[FONT_ARABIC_2].fHandle = msAPI_Font_LoadFlashFontToSDRAM(BIN_ID_FONT_ARABIC_26);
   // FontHandleIndex[Font[FONT_ARABIC_2].fHandle] = FONT_ARABIC_2;
   // Font[FONT_ARABIC_50].fHandle = msAPI_Font_LoadFlashFontToSDRAM(BIN_ID_FONT_ARABIC_50);
   // FontHandleIndex[Font[FONT_ARABIC_50].fHandle] = FONT_ARABIC_50;
#endif

#if (ENABLE_THAI_OSD)
    Font[FONT_THAI_0].fHandle = msAPI_Font_LoadFlashFontToSDRAM(BIN_ID_FONT_THAI_26);
    FontHandleIndex[Font[FONT_THAI_0].fHandle] = FONT_THAI_0;
    //Font[FONT_THAI_1].fHandle = msAPI_Font_LoadFlashFontToSDRAM(BIN_ID_FONT_THAI_35);
    //FontHandleIndex[Font[FONT_THAI_1].fHandle] = FONT_THAI_1;
    //Font[FONT_THAI_2].fHandle = msAPI_Font_LoadFlashFontToSDRAM(BIN_ID_FONT_THAI_30);
    //FontHandleIndex[Font[FONT_THAI_2].fHandle] = FONT_THAI_2;
    //Font[FONT_THAI_50].fHandle = msAPI_Font_LoadFlashFontToSDRAM(BIN_ID_FONT_THAI_50);
    //FontHandleIndex[Font[FONT_THAI_50].fHandle] = FONT_THAI_50;
#endif

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END(););
}
#else
static void MApp_LoadFontInit_BMP(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START(););

    U8 u8num = sizeof(fontpair)/sizeof(LOADFONT_PAIR);
    MApp_LoadFont_SetBMPFontInfo(fontpair,u8num);

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END(););
}
#endif

BOOLEAN MApp_LoadFontInit_TTF(U16 u16FontBinID, BOOLEAN bUnloadFirst)
{
    BININFO   BinInfo;
    BOOLEAN     bResult;

    if ( bUnloadFirst )
    {
#if ( ENABLE_TTF_FONT )
        msAPI_MLE_FONTBASE_VectorFontUnInit();
#endif
    }

    BinInfo.B_ID = u16FontBinID;

    msAPI_MIU_Get_BinInfo(&BinInfo, &bResult);

    if ( bResult != PASS)
    {
        return FALSE;
    }

#if defined( TTF_BUFFER_ADR )
    if (SUCCESS == MDrv_DMA_LoadBin(&BinInfo,
                            _PA2VA((TTF_BUFFER_MEMORY_TYPE & MIU1) ? (TTF_BUFFER_ADR | MIU_INTERVAL) : (TTF_BUFFER_ADR)),
                            _PA2VA((TTF_BUFFER_MEMORY_TYPE & MIU1) ? ((TTF_DEC_BUFFER_ADR) | MIU_INTERVAL) : (TTF_DEC_BUFFER_ADR)),
                            _PA2VA((TTF_BUFFER_MEMORY_TYPE & MIU1) ? ((TTF_TMP_BUFFER_ADR) | MIU_INTERVAL) : (TTF_TMP_BUFFER_ADR))))
    {
        printf("TTF Load OK\n");
        printf("Font Addr=%x, Len=%d\n", BinInfo.B_FAddr, BinInfo.B_Len);

#if ( ENABLE_TTF_FONT )
        msAPI_MLE_FONTBASE_VectorFontChangeFontFromCus(0, BinInfo.B_Len);
#endif

        if ( !bUnloadFirst )
        {
            //Current we only support one TTF file loading at the same time
            Font[FONT_TTF].fHandle = msAPI_Font_LoadTTF();
            FontHandleIndex[Font[FONT_TTF].fHandle] = FONT_TTF;
        }

        return TRUE;
    }
    else
#endif
    {
        printf("TTF Load Fail\n");
        return FALSE;
    }

}

#define DEBUG_LOAD_FONT_TIME(x)  //x
void MApp_LoadFontInit(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START(););

    msAPI_Font_VariableInit();

    DEBUG_LOAD_FONT_TIME(printf("%u t=%u\n", __LINE__, MsOS_GetSystemTime()); );

#if VECTOR_FONT_ENABLE

  #if (!COPRO_MVF_ENABLE)
    msAPI_MVF_init_mempool((void*)_PA2VA(((POOL_BUFFER_MEMORY_TYPE&MIU1)?POOL_BUFFER_ADR|MIU_INTERVAL:POOL_BUFFER_ADR)), 0x800000/*POOL_BUFFER_LEN*/);
  #endif

    DEBUG_LOAD_FONT_TIME(printf("%u t=%u\n", __LINE__, MsOS_GetSystemTime()); );

    MApp_LoadFontInit_VEC();
#else
    MApp_LoadFontInit_BMP();
#endif

    DEBUG_LOAD_FONT_TIME(printf("%u t=%u\n", __LINE__, MsOS_GetSystemTime()); );

  #if ((BRAZIL_CC )|| (ATSC_CC == ATV_CC))
	MApp_LoadFont_CC_Init();
    MApp_LoadAll_Font_CC();
    enCCFontStatus=CC_FONT_LOAD;
  #endif

    DEBUG_LOAD_FONT_TIME(printf("%u t=%u\n", __LINE__, MsOS_GetSystemTime()); );

#if (ATSC_CC == DTV_CC)
    MApp_LoadFont_CC_Init();
    MApp_LoadAll_Font_CC();
#endif

    DEBUG_LOAD_FONT_TIME(printf("%u t=%u\n", __LINE__, MsOS_GetSystemTime()); );

#if ( ENABLE_TTF_FONT )
 #if ( !ENABLE_INDIA_OSD )
    //MApp_LoadFontInit_TTF(BIN_ID_FONT_UI_TTF_TAMIL, FALSE);
 #else
    MApp_LoadFontInit_TTF(BIN_ID_FONT_UI_TTF_HINDI, FALSE);
 #endif

    DEBUG_LOAD_FONT_TIME(printf("%u t=%u\n", __LINE__, MsOS_GetSystemTime()); );

    bFontSysInit = TRUE;
#endif

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END(););

}


