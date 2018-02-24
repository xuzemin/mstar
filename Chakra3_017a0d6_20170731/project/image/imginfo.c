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

#define IMGINFO_C

#include <string.h>

#include "datatype.h"
#include "MsTypes.h"

#include "sysinfo.h"

#include "imginfo.h"
#include "BinInfo.h"
#include "InfoBlock.h"

#include "Panel.h"

#include "drvSERFLASH.h"
#include "MApp_Customer_Info.h"

#if ENABLE_SBOOT_LOAD_BIN
#include "drv_Joba.h"
#include "msAPI_Joba.h"
#endif

#if (ENABLE_FLASH_ON_DRAM)
#include "msAPI_FlashOnDram.h"
#endif




#if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN)     \
   ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA)     \
   ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER)    \
   ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA)     \
   ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_WHISKY)   \
   ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MELODY)   \
   ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA)      \
   )

    #define IMG_INFO_OFFSET     0x21180

#elif( (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD)    \
     ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)      \
     ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON)     \
     )

    #define IMG_INFO_OFFSET     0x21000

#else

    #error ""
#endif

#if (ORGINAL_ALL_MERGE)
    U32 u32ImgInfoOffset = IMG_INFO_OFFSET;
#else
    U32 u32ImgInfoOffset = IMG_INFO_OFFSET; //temp for bootloader //IMG_INFO_OFFSET + 0x20000;
#endif

/*
#ifdef SUPPORT_AP_BIN_IN_FLASH_2
extern volatile U8 BinaryInfoBlock[];
#else
extern volatile U8 const BinaryInfoBlock[];
#endif
*/

#if( ENABLE_SBOOT_LOAD_BIN )
extern StuJobaData g_ImgInfo_JobaData;
#endif

#if( ENABLE_FLASH_ON_DRAM)
extern StuFODDataForImgInfo g_ImgInfo_FODData;
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Any change of MS_IMG_INFO may not be backward compatible with external tool and previously released bootloader
MS_IMG_INFO code g_ImgInfo __attribute__((__section__ (".prog_img_info"))) =
{
// App image
    MAGIC_APP,                      // Magic number of app image

    // Pack bin bank number and offset on flash
    0,                              // Flash bank no of pack information
    0,                              // Flash offset of pack information
    0,
    #if 0
    // MCU8051 (System) code information
    {
        0,//MCU_CODE_SIZE,              // Source size in bytes
        0,                          // Flash offset relative to system image.
        0,//CODE_MAP_BASE_ADR           // DRAM start address to be loaded at.
    },

    #if (MCU_AEON_ENABLE)
    // AEON code information
    {
        0,                          // Source size in bytes. Invalid: need to get it from pack bin.
        0,                          // Flash offset. Invalid: need to get it from pack bin.
        AEON_MEM_ADR,          // DRAM start address to be loaded at.
    },
    #else
    // AEON code memory information: N/A
    {
        0,
        0,
        0
    },
    #endif

    // Database memory information
    {
        DATABASE_START_LEN,               // Source size in bytes
        SYSTEM_BANK_DATADASE_BASE,  // Flash offset. To be defined!
        ((DATABASE_START_MEMORY_TYPE & MIU1) ? (DATABASE_START_ADR | MIU_INTERVAL) : (DATABASE_START_ADR))          // DRAM start address to be loaded at.
    },
    #endif
    // OAD Version Control
    CUSTOMER_OUI,                   // OUI
    {INPUT_CL_LOW_BYTE,INPUT_CL_MIDDLE_BYTE,INPUT_CL_HIGH_BYTE,0}, // Selector Byte
    HW_MODEL,                       // HW Model
    HW_VERSION,                     // HW Version
    AP_SW_MODEL,                    // SW Model
    AP_SW_VERSION,                  // SW Version

    // Board type
    MS_BOARD_TYPE_SEL,

    // Model name
    MODEL_NAME,

    // Panel name
    "PANEL_NAME", // will be filled later in MApp_Imginfo_GetCurModel

    // Panel type
    0,             // will be filled later in MApp_Imginfo_GetCurModel

	{ 0, 0,	0 }, // U8  CompressMagicNum[3];

	0x00000000,  // U32  u32CompressedLength;

    // Reserved
    // U8      u8Reserved[32];        // Reserved for future use

    0, //U32 u32MagicId_2; // This is for BLoader: 0x55AAABCD

#if( ENABLE_SBOOT_LOAD_BIN )
    &g_ImgInfo_JobaData, //StuJobaData* pstJobaData;
#else
    0,//U32 u32Reserved_1;
#endif

#if( ENABLE_FLASH_ON_DRAM)
    &g_ImgInfo_FODData//void* pstFODData;
#else
    0,//U32 u32Reserved_2;
#endif

};

#if( ENABLE_SBOOT_LOAD_BIN )
StuJobaData g_ImgInfo_JobaData __attribute__((__section__ (".prog_img_info"))) =
{
    JOBA_DATA_MAGIC_ID,     // U32 u32MagicId;
    JOBA_DATA_LOAD_BIN_MAX, // U8 u8LoadBinCountMax;
    {
    #if( JOBA_LOAD_AUDIO_BIN )
        { BIN_ID_CODE_AUDIO_DEC_R2, MAD_BASE_BUFFER_ADR},
    #endif
        { 0, 0}, // End of data
    },
};
#endif

#if( ENABLE_FLASH_ON_DRAM)
StuFODDataForImgInfo g_ImgInfo_FODData __attribute__((__section__ (".prog_img_info"))) =
{
    FOD_MAGIC_ID, //U32 u32FODMagicId_1;

    FOD_DRAM_BASE, //U32 u32DramBaseAddr;

    FOD_AP_END_FLASH_ADDR, //U32 u32FlashDataAddr_1;
    FOD_FLASH_DATA_1_SIZE, //U32 u32FlashDataSize_1;

    FOD_FLASH_DATA_2_ADDR, //U32 u32FlashDataAddr_2;
    FOD_FLASH_DATA_2_SIZE, //U32 u32FlashDataSize_2;

    FOD_MAGIC_ID_2, //U32 u32FODMagicId_2;
};
#endif

///////////////////////////////////////////////////////

BOOLEAN MApp_ImgInfo_IsBootImage(MS_IMG_INFO *pImgInfo)
{
    return (pImgInfo->u32Magic == MAGIC_BOOTLOADER);
}

BOOLEAN MApp_ImgInfo_IsAppImage(MS_IMG_INFO *pImgInfo)
{
    return (pImgInfo->u32Magic == MAGIC_APP);
}

void MApp_ImgInfo_GetBootInfo(MS_IMG_INFO *pImgInfo)
{
    MDrv_FLASH_Read(IMG_INFO_OFFSET, sizeof(MS_IMG_INFO), (U8 *)pImgInfo);
}

void MApp_ImgInfo_GetAppInfo(MS_IMG_INFO *pImgInfo)
{
    MDrv_FLASH_Read((U32)0 + IMG_INFO_OFFSET, sizeof(MS_IMG_INFO), (U8 *)pImgInfo);
}

void MApp_Imginfo_GetCurModel(U8 *pModel)
{
#if 0
    MS_IMG_INFO ImgInfo;

    pModel[0] = 0;
    MApp_Imginfo_GetAppInfo(&ImgInfo);

    if (!MApp_ImgInfo_IsAppImage(&ImgInfo))
    {
        MApp_ImgInfo_GetBootInfo(&ImgInfo);
        if (!MApp_ImgInfo_IsBootImage(&ImgInfo))
        {
            return;
        }
    }

    memcpy(pModel, ImgInfo.u8ModelName, IMG_MODEL_NAME_LEN);
#else
    memcpy(pModel, g_ImgInfo.u8ModelName, IMG_MODEL_NAME_LEN);

    // save information
    memcpy(g_ImgInfo.u8PanelName, g_IPanel.Name(), IMG_PANEL_NAME_LEN);
    g_ImgInfo.u8PanelType = g_PNL_TypeSel;

    //memcpy(pModel, MODEL_NAME, IMG_MODEL_NAME_LEN);   // This will make MODEL_NAME a constant string at 0x100
#endif
    pModel[IMG_MODEL_NAME_LEN] = 0;

}

#if 0
BOOLEAN MApp_ImgInfo_IsSameModelAndPanelType(MS_IMG_INFO *pImgInfo, U8 *pModel)
{
    return ((pImgInfo->u8PanelType == g_PNL_TypeSel) && (0 == strcmp(pImgInfo->u8ModelName, pModel)));
}
#endif

#if 0
#if 0
void MApp_ImgInfo_VersionToString(U8 u8Major, U8 u8Minor, U16 *pBuffer)
{
    U8 ndx = 0;

    if (u8Major >= 100)
    {
        pBuffer[ndx++] = u8Major/100 + '0';
        u8Major %= 100;
    }
    pBuffer[ndx++] = u8Major/10 + '0';
    pBuffer[ndx++] = u8Major%10 + '0';

    pBuffer[ndx++] = '.';

    if (u8Minor >= 100)
    {
        pBuffer[ndx++] = u8Minor/100 + '0';
        u8Minor %= 100;
    }
    pBuffer[ndx++] = u8Minor/10 + '0';
    pBuffer[ndx++] = u8Minor%10 + '0';

    pBuffer[ndx] = 0;
}
#endif

#if 0
BOOLEAN MApp_ImgInfo_GetBootVersion(U16 *pBuffer)
{
    MS_IMG_INFO ImgInfo;

    MApp_ImgInfo_GetBootInfo(&ImgInfo);
    if (MApp_ImgInfo_IsBootImage(&ImgInfo))
    {
        if (ImgInfo.u8BL_VerMajor <= 99 && ImgInfo.u8BL_VerMinor <= 99)
        {
            MApp_ImgInfo_VersionToString(ImgInfo.u8BL_VerMajor, ImgInfo.u8BL_VerMinor, pBuffer);
            return TRUE;
        }
    }

    // Illegal version
    pBuffer[0] = 0;
    return FALSE;
}


BOOLEAN MApp_ImgInfo_GetAppVersion(U16 *pBuffer)
{
    MApp_ImgInfo_VersionToString((U8)SW_VER_EVENT, (U8)SW_VER_NUM, pBuffer);
    return TRUE;
}
#endif

#endif
