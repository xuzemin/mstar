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

#ifndef MAPP_VCHIP_H
#define MAPP_VCHIP_H

#include "datatype.h"

#include "mapi_cc_monitor.h"
#include "MApp_GlobalSettingSt.h"
#if (ENABLE_ATSC_VCHIP)
#include "MApp_EpgDB_ATSC.h"
#endif

#ifdef MAPP_VCHIP_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

#ifndef ENABLE_VCHIP_ALL_AS_AGEBASED
#define ENABLE_VCHIP_ALL_AS_AGEBASED    DISABLE
#endif

#ifndef ENABLE_UNRATED_LOCK
#define ENABLE_UNRATED_LOCK     DISABLE
#endif

#define NEW_VCHIP

//==============================================================================
/*                    Enum                                                      */
//==============================================================================
typedef enum
{
    //TV-Y: 1
    VCHIP_TV_Y_ALL,
    //TV-Y7 : 2
    VCHIP_TV_Y7_ALL,
    VCHIP_TV_Y7_FV,
    //TV-G: 1
    VCHIP_TV_G_ALL,
    //TV-PG: 5
    VCHIP_TV_PG_ALL,
    VCHIP_TV_PG_V,
    VCHIP_TV_PG_S,
    VCHIP_TV_PG_L,
    VCHIP_TV_PG_D,
    //TV-14: 5
    VCHIP_TV_14_ALL,
    VCHIP_TV_14_V,
    VCHIP_TV_14_S,
    VCHIP_TV_14_L,
    VCHIP_TV_14_D,
    //TV-MA: 4
    VCHIP_TV_MA_ALL,
    VCHIP_TV_MA_V,
    VCHIP_TV_MA_S,
    VCHIP_TV_MA_L,
    VCHIP_TV_NUM,
    VCHIP_TV_FVSLD_MIN_LEVEL = VCHIP_TV_Y_ALL,
    VCHIP_TV_FVSLD_MAX_LEVEL = VCHIP_TV_MA_L
} EN_VCHIP_TV_FVSLD_ITEM;

typedef enum
{
    VCHIP_RATING_REGION_NONE,
    VCHIP_RATING_REGION_US,
    VCHIP_RATING_REGION_CANADA,
    VCHIP_RATING_REGION_REG5,
    VCHIP_RATING_REGION_NUM
} EN_VCHIP_RATING_REGION;

typedef enum
{
    VCHIP_RATING_TYPE_NONE,
    VCHIP_RATING_TYPE_TV,
    VCHIP_RATING_TYPE_MPAA,
    VCHIP_RATING_TYPE_CANADA_ENG,
    VCHIP_RATING_TYPE_CANADA_FRE,
    VCHIP_RATING_TYPE_REG5,
    VCHIP_RATING_TYPE_NUM
} EN_VCHIP_RATING_TYPE;

typedef enum
{
    VCHIP_TVRATING_NONE,
    VCHIP_TVRATING_TV_Y,
    VCHIP_TVRATING_TV_Y7,
    VCHIP_TVRATING_TV_G,
    VCHIP_TVRATING_TV_PG,
    VCHIP_TVRATING_TV_14,
    VCHIP_TVRATING_TV_MA,
    VCHIP_TVRATING_INVALID,

    VCHIP_TVRATING_NUM,
    VCHIP_TVRATING_MAX_LEVEL = VCHIP_TVRATING_TV_MA
} EnuVChipTVRating;

typedef enum
{
    VCHIP_MPAARATING_NA         = BIT0, //not applicable
    VCHIP_MPAARATING_G          = BIT1,
    VCHIP_MPAARATING_PG         = BIT2,
    VCHIP_MPAARATING_PG_13      = BIT3,
    VCHIP_MPAARATING_R          = BIT4,
    VCHIP_MPAARATING_NC_17      = BIT5,
    VCHIP_MPAARATING_X          = BIT6,
    VCHIP_MPAARATING_NOT_RATED  = BIT7, // EIA-608B: indicates a motion picture that did not receive a rating for a variety of possible reasons.

} EnuVChipMPAARating;

#define INCLUDE_MPAA_G          (BIT0 | BIT1 | BIT2 | BIT3 | BIT4| BIT5 | BIT6)
#define INCLUDE_MPAA_PG         (BIT0 | BIT2 | BIT3 | BIT4| BIT5 | BIT6)
#define INCLUDE_MPAA_PG_13      (BIT0 | BIT3 | BIT4| BIT5 | BIT6)
#define INCLUDE_MPAA_R          (BIT0 | BIT4| BIT5 | BIT6)
#define INCLUDE_MPAA_NC_17      (BIT0 | BIT5 | BIT6)
#define INCLUDE_MPAA_X          (BIT0 | BIT6)

#define EXCLUDE_MPAA_G          ~(BIT1)
#define EXCLUDE_MPAA_PG         ~(BIT1 | BIT2)
#define EXCLUDE_MPAA_PG_13      ~(BIT1 | BIT2 | BIT3)
#define EXCLUDE_MPAA_R          ~(BIT1 | BIT2 | BIT3 | BIT4)
#define EXCLUDE_MPAA_NC_17      ~(BIT1 | BIT2 | BIT3 | BIT4| BIT5)
#define EXCLUDE_MPAA_X          ~(BIT1 | BIT2 | BIT3 | BIT4| BIT5 | BIT6)

#define EXCELUDE_MPAA_NA        0xFE        // ~VCHIP_MPAARATING_NA

typedef enum
{
    VCHIP_ENGRATING_EXEMPT,
    VCHIP_ENGRATING_C,
    VCHIP_ENGRATING_C8Plus,
    VCHIP_ENGRATING_G,
    VCHIP_ENGRATING_PG,
    VCHIP_ENGRATING_14Plus,
    VCHIP_ENGRATING_18Plus,
    VCHIP_ENGRATING_NUM,
    VCHIP_ENGRATING_MAX_LEVEL = VCHIP_ENGRATING_18Plus
} EnuENGLISHRating;

typedef enum
{
    VCHIP_FRERATING_EXEMPT,
    VCHIP_FRERATING_G,
    VCHIP_FRERATING_8ansPlus,
    VCHIP_FRERATING_13ansPlus,
    VCHIP_FRERATING_16ansPlus,
    VCHIP_FRERATING_18ansPlus,
    VCHIP_FRERATING_NUM,
    VCHIP_FRERATING_MAX_LEVEL = VCHIP_FRERATING_18ansPlus
} EnuFRENCHRating;

//==============================================================================
/*                    Global                                                    */
//==============================================================================
INTERFACE MS_U8 fVChipPassWordEntered;
INTERFACE MS_VCHIP_RATING_INFO g_stVChipRatingInfo;


//==============================================================================
/*                    Function Prototype                                        */
//==============================================================================
#if((ENABLE_ATSC_VCHIP)||((ATSC_CC == ATV_CC))||ENABLE_ISDB_ATV_VCHIP)
INTERFACE void MApp_VChip_Init(void);
INTERFACE void MApp_VChip_SetBlockStatus(BOOLEAN bVChipBlockStatus);
INTERFACE void MApp_VChip_MonitorVChip(void);
INTERFACE BOOLEAN MApp_VChip_GetCurVChipBlockStatus(void);
INTERFACE BOOLEAN MApp_VChip_GetRatingUpdateStatus(void);
#if (ENABLE_ATSC_VCHIP)
INTERFACE void MApp_VChip_EPGRating2RatingInfo(MS_EPG_RATING *pstCurEvn, MS_VCHIP_RATING_INFO *pstVChipRatingInfo);
#endif
INTERFACE BOOLEAN MApp_VChip_CompareRating(MS_VCHIP_RATING_INFO *pstVChipRatingInfo, MS_VCHIP_SETTING *pstVChipSetting);

INTERFACE U8 UiMenuStr_GetVChip1RatingString(U8* pu8Str);
#else
#define MApp_VChip_GetCurVChipBlockStatus() 0
#endif

#undef INTERFACE
#endif

