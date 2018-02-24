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
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#include <string.h>

#include "sysinfo.h"
#include "MsCommon.h"
#include "MsTypes.h"
#include "hwreg_utility2.h"

#include "debug.h"

#include "drvXC_IOPort.h"
#include "apiXC.h"
#include "color_reg.h"
#include "drvPQ_Define.h"
#include "drvPQ.h"
#include "QualityMode.h"

#include "drvGlobal.h"

#include "msAPI_Video.h"
#include "mapp_videoplayer.h"

#include "MApp_ZUI_Main.h"
#include "ZUI_tables_h.inl"

//---------------------------------------------------------

extern  MS_PQ_Hdmi_Info  _stHDMI_Info[PQ_MAX_WINDOW];
extern  MS_PQ_Mode_Info  _stMode_Info[PQ_MAX_WINDOW];

extern MS_BOOL _gIsH264;
extern MS_BOOL _gIsMMplayer;
extern MS_BOOL _gIsPIPEnable;

//---------------------------------------------------------

#define BW_DBG(x)           //x

#if( CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA )
#define BW_TBL_DBG(x)       x
#else
#define BW_TBL_DBG(x)       //x
#endif


#define BW_TABLE_FORMAT_OLD         0
#define BW_TABLE_FORMAT_2015        1
#define BW_TABLE_FORMAT_2016_MARLON 2
#define BW_TABLE_FORMAT_2017_MAZDA  3

#if( CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA )
    #define BW_TABLE_FORMAT     BW_TABLE_FORMAT_2017_MAZDA

#elif( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON))

    #define BW_TABLE_FORMAT     BW_TABLE_FORMAT_2016_MARLON

#elif ( ( CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA )      \
    ||( CHIP_FAMILY_TYPE == CHIP_FAMILY_WHISKY )    \
    ||( CHIP_FAMILY_TYPE == CHIP_FAMILY_MELODY)     \
    )
    #define BW_TABLE_FORMAT     BW_TABLE_FORMAT_2015
#else

    #define BW_TABLE_FORMAT     BW_TABLE_FORMAT_OLD

#endif


#ifndef PQ_BW_PIP_ENABLE
#define PQ_BW_PIP_ENABLE    0
#endif

typedef struct
{
    MS_U8 *pIPTable;
    MS_U8 u8TabNums;
    MS_U8 u8TabIdx;
} TAB_Info;


#include "QualityMap_BW.c"

static  MS_U8 *pBwTable=(void*)BWTABLE;

/*static*/ void _MDrv_BW_LoadTable(MS_U8 u8TabIdx)
{
    TAB_Info tab_Info;
    tab_Info.pIPTable  = pBwTable;
    tab_Info.u8TabNums = BWTABLE_NUMS;
    tab_Info.u8TabIdx = u8TabIdx;

    BW_DBG(printf("[BW]LoadTable\n"));

    _MDrv_BW_DumpTable(&tab_Info);
}

void MDrv_BW_LoadInitTable(void)
{
    TAB_Info tab_Info;
    tab_Info.pIPTable = (void*)BWTABLE_COM;
    tab_Info.u8TabNums = 1;
    tab_Info.u8TabIdx = 0;

    BW_DBG(printf("[BW]LoadCommTable\n"));
    _MDrv_BW_DumpTable(&tab_Info);
}

#if( BW_TABLE_FORMAT == BW_TABLE_FORMAT_2017_MAZDA )
void MDrv_BW_LoadTableByContext(PQ_WIN eWindow)
{
    //PRINT_CURRENT_LINE();
    //printf("MDrv_BW_LoadTableByContext() \n");

    MS_U16 u16Input_HSize;
    MS_U16 u16Input_VSize;
    MS_U16 u16Input_VFreq;
    MS_BOOL bIsInterlaced;
    MS_U8 u8TabIdx = BWTABLE_Normal_mode;
    PQ_INPUT_SOURCE_TYPE pqInputSourceType;

    pqInputSourceType = MDrv_PQ_GetInputSourceType(eWindow);
    bIsInterlaced  = _stMode_Info[eWindow].bInterlace;
    u16Input_HSize = _stMode_Info[eWindow].u16input_hsize;
    u16Input_VSize = _stMode_Info[eWindow].u16input_vsize;
    u16Input_VFreq = _stMode_Info[eWindow].u16input_vfreq;

    BW_TBL_DBG(printf("[BW] InputSourceType = %d \r\n", pqInputSourceType));
    BW_TBL_DBG(printf("     Input = %u*%u@%u %s \r\n", u16Input_HSize, u16Input_VSize, u16Input_VFreq, (bIsInterlaced)?("i"):("p")));
/*
typedef enum
{
    BWTABLE_Normal_mode,
    BWTABLE_1080p_mode,
    BWTABLE_HDMI4kx2k_mode,
    BWTABLE_MM4kx2k_mode,
    BWTABLE_DTV4kx2k_mode,
    BWTABLE_MM_Photo,
    BWTABLE_NUMS
}
BWTABLE_Group;
*/

#define CONDITION_4K()      ( (u16Input_HSize > 1920) && (u16Input_VSize>1080) )
#define CONDITION_1080P()   ( (u16Input_HSize >= 1600) && (u16Input_VSize >= 900) && !bIsInterlaced && (u16Input_VFreq >= 490) )

    // Check special rule...
    if ( QM_IsSourceMultiMedia(pqInputSourceType) )
    {
        if( MDrv_PQ_Is_SourceTypeMMPhoto(eWindow) )
        {
            u8TabIdx = BWTABLE_MM_Photo;
            BW_TBL_DBG(printf("[BW] BWTABLE_MM_Photo\n"));
        }
        else if( CONDITION_4K() )
        {
            u8TabIdx = BWTABLE_MM4kx2k_mode;
            BW_TBL_DBG(printf("[BW] BWTABLE_MM4kx2k_mode\n"));
        }
    }
    else if( QM_IsSourceDTV(pqInputSourceType) )
    {
        if( CONDITION_4K() )
        {
            u8TabIdx = BWTABLE_DTV4kx2k_mode;
            BW_TBL_DBG(printf("[BW] BWTABLE_HDMI4kx2k_mode\n"));
        }
    }
    else if( QM_IsSourceHDMI(pqInputSourceType) )
    {
        if( CONDITION_4K() )
        {
            u8TabIdx = BWTABLE_HDMI4kx2k_mode;
            BW_TBL_DBG(printf("[BW] BWTABLE_MM4kx2k_mode\n"));
        }
    }

    // Basic rule ...
    if( u8TabIdx == BWTABLE_Normal_mode )
    {
        if( CONDITION_1080P() )
        {
            u8TabIdx = BWTABLE_1080p_mode;
            BW_TBL_DBG(printf("[BW] BWTABLE_1080p_mode \r\n"));
        }
        else
        {
            u8TabIdx = BWTABLE_Normal_mode;
            BW_TBL_DBG(printf("[BW] BWTABLE_Normal_mode \r\n"));
        }
    }

/*
    else if ( QM_IsSourceVD(pqInputSourceType) )
    else if( QM_IsSourceHDMI(pqInputSourceType)
          || QM_IsSourceYPbPr(pqInputSourceType)
          || QM_IsSourceVGA(pqInputSourceType)
          )
    {
    }
*/

    //BW_TBL_DBG(printf("[BW] load table #%d \r\n", u8TabIdx));

    MDrv_BW_LoadInitTable();

    _MDrv_BW_LoadTable(u8TabIdx);

}

#elif( BW_TABLE_FORMAT == BW_TABLE_FORMAT_2016_MARLON )

void MDrv_BW_LoadTableByContext(PQ_WIN eWindow)
{
    //printf("MDrv_BW_LoadTableByContext()\n");

    MS_U16 u16Input_HSize;
    MS_U16 u16Input_VSize;
    MS_U16 u16Input_VFreq;
    MS_BOOL bIsInterlaced;
    MS_U8 u8TabIdx = BWTABLE_Normal_mode;
    PQ_INPUT_SOURCE_TYPE pqInputSourceType;

    pqInputSourceType = MDrv_PQ_GetInputSourceType(eWindow);
    bIsInterlaced  = _stMode_Info[eWindow].bInterlace;
    u16Input_HSize = _stMode_Info[eWindow].u16input_hsize;
    u16Input_VSize = _stMode_Info[eWindow].u16input_vsize;
    u16Input_VFreq = _stMode_Info[eWindow].u16input_vfreq;

    BW_TBL_DBG(printf("[BW] InputSourceType = %d \r\n", pqInputSourceType));
    BW_TBL_DBG(printf("     Input = %u*%u@%u %s \r\n", u16Input_HSize, u16Input_VSize, u16Input_VFreq, (bIsInterlaced)?("i"):("p")));

    if ( QM_IsSourceMultiMedia(pqInputSourceType) )
    {
    #if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON)
        if( MDrv_PQ_Is_SourceTypeMMPhoto(eWindow) )
        {
            u8TabIdx = BWTABLE_MM_Photo;
            BW_TBL_DBG(printf("[BW] BWTABLE_MM_Photo \r\n"));
        }
        else
    #endif
        if ( (u16Input_HSize>1280) && (u16Input_VSize>=900) )
        {
        #if 0//( (MEMORY_MAP == MMAP_32MB)&&(CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA) ) // 32M
            if( MDrv_PQ_Is_SourceTypeMMPhoto(eWindow) )
            {
                // This table is used for NASA photo slide show garbage issue!
                // Mantis-599095.
                u8TabIdx = BWTABLE_PHOTO_MM_HD;
                BW_TBL_DBG(printf("[BW] BWTABLE_PHOTO_MM_HD \r\n"));
            }
            else
        #endif
            {
                u8TabIdx = BWTABLE_MM_HD;
                BW_TBL_DBG(printf("[BW] BWTABLE_MM_HD \r\n"));
            }
        }
        else if ( (u16Input_HSize>=1280) && (u16Input_VSize >= 720) )
        {
        #if( (MEMORY_MAP == MMAP_64MB)&&(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) )
            u8TabIdx = BWTABLE_MM_720p_DDR2_64MB;
            BW_TBL_DBG(printf("[BW] BWTABLE_MM_720p_DDR2_64MB \r\n"));
        #else
            u8TabIdx = BWTABLE_MM_720p;
            BW_TBL_DBG(printf("[BW] BWTABLE_MM_720p \r\n"));
        #endif
        }
        else
        {
            u8TabIdx = BWTABLE_MM_SD;
            BW_TBL_DBG(printf("[BW] BWTABLE_MM_SD \r\n"));
        }
    }
    else if ( QM_IsSourceVD(pqInputSourceType) )
    {
        u8TabIdx = BWTABLE_SDi_mode;
        BW_TBL_DBG(printf("[BW] BWTABLE_SDi_mode \r\n"));
    }
    else if ( QM_IsSourceVGA(pqInputSourceType) )
    {
        if ( (U32)(u16Input_HSize*u16Input_VSize*u16Input_VFreq) >= (1400 * 1050 * 600) )
        {
            u8TabIdx = BWTABLE_PC_HD_mode;
            BW_TBL_DBG(printf("[BW] BWTABLE_PC_HD_mode \r\n"));
        }
        else
        {
            u8TabIdx = BWTABLE_PC_SD_mode;
            BW_TBL_DBG(printf("[BW] BWTABLE_PC_SD_mode \r\n"));
        }
    }
    else if( QM_IsSourceHDMI(pqInputSourceType)
          || QM_IsSourceYPbPr(pqInputSourceType)
          || QM_IsSourceDTV(pqInputSourceType)
          )
    {
        if (u16Input_HSize>=1440 && u16Input_VSize >= 900 && !bIsInterlaced && (u16Input_VFreq >= 490))
        {
            u8TabIdx = BWTABLE_1080p_mode;
            BW_TBL_DBG(printf("[BW] BWTABLE_1080p_mode \r\n"));
        }
        else if (u16Input_HSize >= 1280 && u16Input_VSize >= 720)
        {
            if (bIsInterlaced)
            {
                u8TabIdx = BWTABLE_HDi_mode;
                BW_TBL_DBG(printf("[BW] BWTABLE_HDi_mode \r\n"));
            }
            else
            {
                u8TabIdx = BWTABLE_HDp_mode;
                BW_TBL_DBG(printf("[BW] BWTABLE_HDp_mode \r\n"));
            }
        }
        else
        {
            if (bIsInterlaced)
            {
                u8TabIdx = BWTABLE_SDi_mode;
                BW_TBL_DBG(printf("[BW] BWTABLE_SDi_mode \r\n"));
            }
            else
            {
                u8TabIdx = BWTABLE_SDp_mode;
                BW_TBL_DBG(printf("[BW] BWTABLE_SDp_mode \r\n"));
            }
        }
    }
    else
    {
        printf("\nWarning: Unknown BW case\n");
    }

    //BW_TBL_DBG(printf("[BW] load table #%d \r\n", u8TabIdx));

    MDrv_BW_LoadInitTable();

    _MDrv_BW_LoadTable(u8TabIdx);

    // Patch DTV and MM H265 1080p
#if 0//(CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)
    if( ((QM_IsSourceDTV(pqInputSourceType)&&(msAPI_VID_Is_CodecH265()))||\
        (QM_IsSourceMultiMedia(pqInputSourceType)&&(E_VDPLAYER_VIDEO_HEVC == g_enVDPlayerVideoType)))\
      &&(u16Input_HSize >= 1900)
      &&(u16Input_VSize >= 1060)
      &&(u16Input_VFreq >= 485) // 50P or 60P
      &&(bIsInterlaced == 0) // Non-Interlace
      ) // Codec is H265
    {
        MDrv_WriteByteMask(0x101428, 0x18, 0x1F);
    }
    else
    {
        MDrv_WriteByteMask(0x101428, 0x08, 0x1F);
    }
#endif

}

#elif( BW_TABLE_FORMAT == BW_TABLE_FORMAT_2015 )

void MDrv_BW_LoadTableByContext(PQ_WIN eWindow)
{
    MS_U16 u16Input_HSize;
    MS_U16 u16Input_VSize;
    MS_U16 u16Input_VFreq;
    MS_BOOL bIsInterlaced;
    MS_U8 u8TabIdx = BWTABLE_SDi_mode;
    PQ_INPUT_SOURCE_TYPE pqInputSourceType;


    pqInputSourceType = MDrv_PQ_GetInputSourceType(eWindow);
    bIsInterlaced  = _stMode_Info[eWindow].bInterlace;
    u16Input_HSize = _stMode_Info[eWindow].u16input_hsize;
    u16Input_VSize = _stMode_Info[eWindow].u16input_vsize;
    u16Input_VFreq = _stMode_Info[eWindow].u16input_vfreq;

    BW_TBL_DBG(printf("[BW] InputSourceType = %d \r\n", pqInputSourceType));
    BW_TBL_DBG(printf("     Input = %u*%u@%u %s \r\n", u16Input_HSize, u16Input_VSize, u16Input_VFreq, (bIsInterlaced)?("i"):("p")));


    if( QM_IsSourceDTV(pqInputSourceType) )
    {
        if (u16Input_HSize >= 1280 && u16Input_VSize >= 720)
        {
            u8TabIdx = BWTABLE_DTV_HD;
            BW_TBL_DBG(printf("[BW] BWTABLE_DTV_HD \r\n"));
        }
        else
        {
            u8TabIdx = BWTABLE_DTV_SD;
            BW_TBL_DBG(printf("[BW] BWTABLE_DTV_SD \r\n"));
        }
    }
    else if( QM_IsSourceHDMI(pqInputSourceType)
           &&((u16Input_HSize >= 3000) && (u16Input_VSize >= 1500)) // 4K
           )
    {
        u8TabIdx = BWTABLE_HDMI_4K;
        BW_TBL_DBG(printf("[BW] BWTABLE_HDMI_4K \r\n"));
    }
    else if( QM_IsSourceVGA(pqInputSourceType)
           &&( (u16Input_HSize >= 1280) && (u16Input_VSize >= 720) ) // PC_HD
           )
    {
        u8TabIdx = BWTABLE_PC_HD;
        BW_TBL_DBG(printf("[BW] BWTABLE_PC_HD \r\n"));
    }
    else if ( QM_IsSourceVD(pqInputSourceType) )
    {
        u8TabIdx = BWTABLE_VD_COMB;
        BW_TBL_DBG(printf("[BW] BWTABLE_VD_COMB \r\n"));
    }
    else if ( QM_IsSourceMultiMedia(pqInputSourceType) )
    {
        if( MDrv_PQ_Is_SourceTypeMMPhoto(eWindow) )
        {
            u8TabIdx = BWTABLE_MM_PHOTO;
            BW_TBL_DBG(printf("[BW] BWTABLE_MM_PHOTO \r\n"));
        }
        else // Movie
        {
            if ( (u16Input_HSize >= 1280) && (u16Input_VSize >= 720) )
            {
                u8TabIdx = BWTABLE_MM_MOVIE_HD;
                BW_TBL_DBG(printf("[BW] BWTABLE_MM_MOVIE_HD \r\n"));
            }
            else
            {
                u8TabIdx = BWTABLE_MM_MOVIE_SD;
                BW_TBL_DBG(printf("[BW] BWTABLE_MM_MOVIE_SD \r\n"));
            }
        }
    }
    else
    {
        if (u16Input_HSize >= 1280 && u16Input_VSize >= 720)
        {
          #if (CHIP_FAMILY_TYPE == CHIP_FAMILY_MELODY)
            if ( 0
               || (MApp_ZUI_GetActiveOSD() == E_OSD_FACTORY_MENU)
               || (MApp_ZUI_GetActiveOSD() == E_OSD_EXPERT_MENU)
               || (MApp_ZUI_GetActiveOSD() == E_OSD_DESIGN_MENU) )
            {
                u8TabIdx = BWTABLE_UI_HDMI_HD_mode;
                BW_TBL_DBG(printf("[BW] BWTABLE_UI_HDMI_HD_mode \r\n"));
            }
            else
          #endif
            {
                u8TabIdx = BWTABLE_HD_mode;
                BW_TBL_DBG(printf("[BW] BWTABLE_HD_mode \r\n"));
            }
        }
        else
        {
            if (bIsInterlaced)
            {
                u8TabIdx = BWTABLE_SDi_mode;
                BW_TBL_DBG(printf("[BW] BWTABLE_SDi_mode \r\n"));
            }
            else
            {
                u8TabIdx = BWTABLE_SDp_mode;
                BW_TBL_DBG(printf("[BW] BWTABLE_SDp_mode \r\n"));
            }
        }
    }

    BW_TBL_DBG(printf("[BW] load table #%d \r\n", u8TabIdx));

    _MDrv_BW_LoadTable(u8TabIdx);
}

#elif ( (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER)     \
      ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN)      \
      ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA)      \
      ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)     \
      )

void MDrv_BW_LoadTableByContext(PQ_WIN eWindow)
{
    MS_U16 u16Input_HSize;
    MS_U16 u16Input_VSize;
    MS_U16 u16Input_VFreq;
    MS_BOOL bIsInterlaced;
    MS_U8 u8TabIdx = BWTABLE_SDi_mode;
    PQ_INPUT_SOURCE_TYPE pqInputSourceType;

    pqInputSourceType = MDrv_PQ_GetInputSourceType(eWindow);
    bIsInterlaced  = _stMode_Info[eWindow].bInterlace;
    u16Input_HSize = _stMode_Info[eWindow].u16input_hsize;
    u16Input_VSize = _stMode_Info[eWindow].u16input_vsize;
    u16Input_VFreq = _stMode_Info[eWindow].u16input_vfreq;

    BW_TBL_DBG(printf("[BW] InputSourceType = %d \r\n", pqInputSourceType));
    BW_TBL_DBG(printf("     Input = %u*%u@%u %s \r\n", u16Input_HSize, u16Input_VSize, u16Input_VFreq, (bIsInterlaced)?("i"):("p")));

    if ( QM_IsSourceMultiMedia(pqInputSourceType) )
    {
    #if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN )
        if( MDrv_PQ_Is_SourceTypeMMPhoto(eWindow) )
        {
            u8TabIdx = BWTABLE_MM_Photo;
            BW_TBL_DBG(printf("[BW] BWTABLE_MM_Photo \r\n"));
        }
        else
    #endif
        if ( (u16Input_HSize>1280) && (u16Input_VSize>=900) )
        {
        #if( (MEMORY_MAP == MMAP_32MB)&&(CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA) ) // 32M
            if( MDrv_PQ_Is_SourceTypeMMPhoto(eWindow) )
            {
                // This table is used for NASA photo slide show garbage issue!
                // Mantis-599095.
                u8TabIdx = BWTABLE_PHOTO_MM_HD;
                BW_TBL_DBG(printf("[BW] BWTABLE_PHOTO_MM_HD \r\n"));
            }
            else
        #endif
            {
                u8TabIdx = BWTABLE_MM_HD;
                BW_TBL_DBG(printf("[BW] BWTABLE_MM_HD \r\n"));
            }
        }
        else if ( (u16Input_HSize>=1280) && (u16Input_VSize >= 720) )
        {
        #if( (MEMORY_MAP == MMAP_64MB)&&(CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) )
            u8TabIdx = BWTABLE_MM_720p_DDR2_64MB;
            BW_TBL_DBG(printf("[BW] BWTABLE_MM_720p_DDR2_64MB \r\n"));
        #else
            u8TabIdx = BWTABLE_MM_720p;
            BW_TBL_DBG(printf("[BW] BWTABLE_MM_720p \r\n"));
        #endif
        }
        else
        {
            u8TabIdx = BWTABLE_MM_SD;
            BW_TBL_DBG(printf("[BW] BWTABLE_MM_SD \r\n"));
        }
    }
    else if ( QM_IsSourceVD(pqInputSourceType) )
    {
        u8TabIdx = BWTABLE_SDi_mode;
        BW_TBL_DBG(printf("[BW] BWTABLE_SDi_mode \r\n"));
    }
    else if ( QM_IsSourceVGA(pqInputSourceType) )
    {
        if ( (U32)(u16Input_HSize*u16Input_VSize*u16Input_VFreq) >= (1400 * 1050 * 600) )
        {
            u8TabIdx = BWTABLE_PC_HD_mode;
            BW_TBL_DBG(printf("[BW] BWTABLE_PC_HD_mode \r\n"));
        }
        else
        {
            u8TabIdx = BWTABLE_PC_SD_mode;
            BW_TBL_DBG(printf("[BW] BWTABLE_PC_SD_mode \r\n"));
        }
    }
    else if ( QM_IsSourceHDMI(pqInputSourceType) || QM_IsSourceYPbPr(pqInputSourceType) )
    {
        if (u16Input_HSize>=1440 && u16Input_VSize >= 900 && !bIsInterlaced && (u16Input_VFreq >= 490))
        {
            u8TabIdx = BWTABLE_1080p_mode;
            BW_TBL_DBG(printf("[BW] BWTABLE_1080p_mode \r\n"));
        }
        else if (u16Input_HSize >= 1280 && u16Input_VSize >= 720)
        {
            if (bIsInterlaced)
            {
                u8TabIdx = BWTABLE_HDi_mode;
                BW_TBL_DBG(printf("[BW] BWTABLE_HDi_mode \r\n"));
            }
            else
            {
                u8TabIdx = BWTABLE_HDp_mode;
                BW_TBL_DBG(printf("[BW] BWTABLE_HDp_mode \r\n"));
            }
        }
        else
        {
            if (bIsInterlaced)
            {
                u8TabIdx = BWTABLE_SDi_mode;
                BW_TBL_DBG(printf("[BW] BWTABLE_SDi_mode \r\n"));
            }
            else
            {
                u8TabIdx = BWTABLE_SDp_mode;
                BW_TBL_DBG(printf("[BW] BWTABLE_SDp_mode \r\n"));
            }
        }
    }
#if(CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)
    else if( QM_IsSourceDTV(pqInputSourceType) )// DTV
    {
        //PRINT_CURRENT_LINE();

        if (u16Input_HSize>=1440 && u16Input_VSize >= 900 && !bIsInterlaced && (u16Input_VFreq >= 490))
        {
            u8TabIdx = BWTABLE_1080p_mode;
            BW_TBL_DBG(printf("[BW] BWTABLE_1080p_mode \r\n"));
        }
        else if (u16Input_HSize >= 1280 && u16Input_VSize >= 720)
        {
            if (bIsInterlaced)
            {
                u8TabIdx = BWTABLE_HDi_mode;
                BW_TBL_DBG(printf("[BW] BWTABLE_HDi_mode \r\n"));
            }
            else
            {
                u8TabIdx = BWTABLE_HDp_mode;
                BW_TBL_DBG(printf("[BW] BWTABLE_HDp_mode \r\n"));
            }
        }
        else
        {
            if (bIsInterlaced)
            {
                u8TabIdx = BWTABLE_SDi_mode;
                BW_TBL_DBG(printf("[BW] BWTABLE_SDi_mode \r\n"));
            }
            else
            {
                u8TabIdx = BWTABLE_SDp_mode;
                BW_TBL_DBG(printf("[BW] BWTABLE_SDp_mode \r\n"));
            }
        }
    }
#endif
    else
    {
        //PRINT_CURRENT_LINE();
        printf("\nWarning: Unknown BW case! use default=%u\n", u8TabIdx);
    }

    //BW_TBL_DBG(printf("[BW] load table #%d \r\n", u8TabIdx));

    _MDrv_BW_LoadTable(u8TabIdx);

    // Patch DTV and MM H265 1080p
#if(CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)
    if( ((QM_IsSourceDTV(pqInputSourceType)&&(msAPI_VID_Is_CodecH265()))||\
        (QM_IsSourceMultiMedia(pqInputSourceType)&&(E_VDPLAYER_VIDEO_HEVC == g_enVDPlayerVideoType)))\
      &&(u16Input_HSize >= 1900)
      &&(u16Input_VSize >= 1060)
      &&(u16Input_VFreq >= 485) // 50P or 60P
      &&(bIsInterlaced == 0) // Non-Interlace
      ) // Codec is H265
    {
        MDrv_WriteByteMask(0x101428, 0x18, 0x1F);
    }
    else
    {
        MDrv_WriteByteMask(0x101428, 0x08, 0x1F);
    }
    
    if(QM_IsSourceDTV(pqInputSourceType)
        &&msAPI_VID_Is_CodecH265()
        && (u16Input_HSize >= 1420)
        &&(u16Input_VSize >= 1060)
        &&(u16Input_VFreq >= 485)
        &&(bIsInterlaced == 0))
    {
        MDrv_WriteByte(0x101268, (MDrv_ReadByte(0x101268) & 0xF7));
    }
#endif

}

#elif( (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) ) // Emerald

void MDrv_BW_LoadTableByContext(PQ_WIN eWindow)
{

    MS_U16 u16Input_HSize;
    MS_U16 u16Input_VSize;
    MS_BOOL bIsInterlaced;
    MS_U8 u8TabIdx;
    MS_U16 u16Input_VFreq;

    u16Input_HSize = _stMode_Info[eWindow].u16input_hsize;
    u16Input_VSize = _stMode_Info[eWindow].u16input_vsize;
    bIsInterlaced  = _stMode_Info[eWindow].bInterlace;
    u16Input_VFreq = _stMode_Info[eWindow].u16input_vfreq;

  #if(PQ_BW_PIP_ENABLE)
    if(_gIsPIPEnable)
    {
          u8TabIdx = BWTABLE_PIP_mode;
    }
    else
  #endif
    if((u16Input_HSize>=1440) && (u16Input_VSize >= 900) && _gIsH264 &&_gIsMMplayer)
    {
        u8TabIdx = BWTABLE_MM_HD_H264_mode;
    }
    else if((u16Input_HSize>=1440) && (u16Input_VSize >= 900) && _gIsH264)
    {
        u8TabIdx = BWTABLE_HD_H264_mode;
    }
    else if ((u16Input_HSize>=1440) && (u16Input_VSize >= 900) && (_gIsMMplayer))
    {
        u8TabIdx = BWTABLE_MM_1080p_mode;
    }
    else    if ((u16Input_HSize>=1440) && (u16Input_VSize >= 900))
    {
        u8TabIdx = BWTABLE_1080p_mode;
    }
    else
    {
        if(_gIsMMplayer)
        {
            u8TabIdx = BWTABLE_MM_Normal_mode;
        }
        else
        {
            u8TabIdx = BWTABLE_Normal_mode ;

        }
    }
    _MDrv_BW_LoadTable(u8TabIdx);

}

#else

    #error "Undefine BW table"

#endif


