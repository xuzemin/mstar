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
// (!¡±MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
//==============================================================================
#ifndef MHAL_PQ_ADAPTIVE_H
#define MHAL_PQ_ADAPTIVE_H

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************/
/*                     definition                                             */
/* ****************************************************************************/
#define MSIF_ADAPTIVE_LIB_CODE_H            {'A','D','A','P','T','I','V','E','_'}
#define MSIF_ADAPTIVE_VERSION_H             {'0','0','0','0','0','1'}



#ifdef DRV_SCALER_NR_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

#define MFC_Debug_ENable 0
//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
#define DRVSCA_DBG(x)       //x
#define DBG_DEFEATHERING    0
#define DBG_DEFLICKERING    0
#define DBG_DEBOUNCING      0
#define DBG_DYNAMIC_DNR     0

// DeFeathering
#define MDP_CNT     2
#define ENABLE_MDP  0   //Motion decrase progressively enable

#define DEFETHERING_LV1_TH              30000
#define DEFETHERING_LV2_TH              5000
#define DEFETHERING_LV3_TH              2000
#define DEFETHERING_LV1_CNT             25
#define DEFETHERING_LV2_CNT             20
#define DEFETHERING_LV3_CNT             5

#define SST_STATIC_CORE_TH_LV1_VALUE    0x14              //ryan update
#define SST_STATIC_CORE_TH_LV2_VALUE    0x0C              //ryan update
#define SST_STATIC_CORE_TH_LV3_VALUE    0x06              //ryan update
#define SST_STATIC_CORE_TH_LV4_VALUE    0x00              //ryan update

// DeFlickering
#define DEFLICKERING_TH                 52000
#define DEFLICKERING_CNT                150

// DeBouncing
#define DEBOUNCING_TH                   35000
#define DEBOUNCING_CNT                  10

// Dynamic SNR
#define DYNAMIC_SNR_TH                  2000
#define DYNAMIC_SNR_CNT                 30

// Dynamic DNR
//#define DYNAMIC_DNR_TH                  6000

#define DNR_TABLEY_0L_Zero_VALUE        0xDD
#define DNR_TABLEY_0H_Zero_VALUE        0xBD
#define DNR_TABLEY_1L_Zero_VALUE        0x79
#define DNR_TABLEY_1H_Zero_VALUE        0x35
#define DNR_TABLEY_2L_Zero_VALUE        0x11
#define DNR_TABLEY_2H_Zero_VALUE        0x00
#define DNR_TABLEY_3L_Zero_VALUE        0x00
#define DNR_TABLEY_3H_Zero_VALUE        0x00

#define DNR_TABLEY_0L_LV2_VALUE         0xCC
#define DNR_TABLEY_0H_LV2_VALUE         0xAC
#define DNR_TABLEY_1L_LV2_VALUE         0x68
#define DNR_TABLEY_1H_LV2_VALUE         0x24
#define DNR_TABLEY_2L_LV2_VALUE         0x00
#define DNR_TABLEY_2H_LV2_VALUE         0x00
#define DNR_TABLEY_3L_LV2_VALUE         0x00
#define DNR_TABLEY_3H_LV2_VALUE         0x00

#define DNR_TABLEY_0L_LV3_VALUE         0x67
#define DNR_TABLEY_0H_LV3_VALUE         0x45
#define DNR_TABLEY_1L_LV3_VALUE         0x33
#define DNR_TABLEY_1H_LV3_VALUE         0x22
#define DNR_TABLEY_2L_LV3_VALUE         0x11
#define DNR_TABLEY_2H_LV3_VALUE         0x00
#define DNR_TABLEY_3L_LV3_VALUE         0x00
#define DNR_TABLEY_3H_LV3_VALUE         0x00

// Dynamic Film 22
#define DYNAMIC_FILM22_TH               520000

#define PRJ_MCNR                        TRUE
#define Auto_DeBlock_En                 TRUE

//-------------------------------------------------------------------------------------------------
//  Local Structurs
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------

/******************************************************************************/
/*                           Global Variables                                 */
/******************************************************************************/

//*************************************************************************
//          Enums
//*************************************************************************


//*************************************************************************
//          Structures
//*************************************************************************

typedef struct
{
    MS_U8 minMvXdir;
    MS_U8 minMvXBin;
    MS_U8 minMvYdir;
    MS_U8 minMvYBin;
}XC_Me1HisStates;

typedef struct
{
    MS_U8 minMvXdir;
    MS_U8 minMvYdir;
    MS_U8 h1XYsum;
    MS_U8 h2XYsum;
    MS_U8 h1XYdiff;
    MS_U8 h2XYdiff;
    MS_BOOL yMvIsMovingOdd;
}XC_GMvStates;

typedef struct
{
    MS_BOOL film32;
    MS_BOOL film22;
    MS_BOOL filmany;
    MS_BOOL film_act;
}XC_FilmStates;

typedef struct
{
    MS_U8 curOpFrame;
    MS_U8 maxOpFrame;

}XC_OpFrameStates;

typedef struct
{
    MS_U16 filmLikePrvPixels;
    MS_U16 filmLikeNxtPixels;
		MS_BOOL vaildStates;
}XC_McFilmStates;

typedef struct
{
    MS_U16 motion[16];
    MS_U16 unmatch_1[16];
    MS_U16 unmatch_3[16];
    MS_U8 vaildCnt[16];
		MS_BOOL vaild[16];
}XC_FilmRoStates;

typedef struct
{
    MS_U16 lumaBin[32];
}XC_LumaHistogramStates;

/********************************************************************************/
/*                   Function Prototypes                                        */
/********************************************************************************/
extern MS_U8 msAPI_Scaler_GetXC_Info(void);
INTERFACE MS_U8 Hal_PQ_GetCurrentMotionValue(void);
INTERFACE void Hal_PQ_AdaptiveTuning(void);
INTERFACE void Hal_PQ_FilmMode_AnyCandence_Enable(MS_BOOL bEnable);
INTERFACE void Hal_PQ_StoreCurrentValue(void);
INTERFACE void Hal_PQ_ReStoreToDefault(void);
INTERFACE void MApi_XC_Adaptive_Film(void);
INTERFACE MS_BOOL Hal_PQ_SetFakeOutEnable(MS_BOOL bEnable);

#undef INTERFACE
#ifdef __cplusplus
}
#endif

#endif

