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

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file    drvPQ_Datatypes.h
/// @brief  PQ interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRVPQ_DATATYPES_H_
#define _DRVPQ_DATATYPES_H_

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
    MS_422To444_ON,
    MS_422To444_OFF,
    MS_422To444_SIMPLE,
    MS_422To444_BICUBIC,
    MS_422To444_BYPASS,
    MS_422To444_NUMS
}MS_422To444_TYPE;

typedef enum
{
    MS_420_CUP_ON,
    MS_420_CUP_OFF,
    MS_420_CUP_NUM,
}MS_420_CUP_TYPE;

typedef enum
{
    MS_HNONLINEAR_OFF,
    MS_HNONLINEAR_3840_1,
    MS_HNONLINEAR_3840_2,
    MS_HNONLINEAR_3840_3,
    MS_HNONLINEAR_3840_4,
    MS_HNONLINEAR_1920_0,
    MS_HNONLINEAR_1920_1,
    MS_HNONLINEAR_1920_2,
    MS_HNONLINEAR_1680,
    MS_HNONLINEAR_1440,
    MS_HNONLINEAR_1366_0,
    MS_HNONLINEAR_1366_1,
    MS_HNONLINEAR_1366_2,
    MS_HNONLINEAR_NUM,
}MS_HNONLINEAR_TYPE;


#ifndef PQ_SUPPORT_MADI_P_MODE_MOT10_NR_Yonly
    #define PQ_SUPPORT_MADI_P_MODE_MOT10_NR_Yonly   0
#endif

typedef enum
{
    MS_MADI_24_4R,
    MS_MADI_24_2R,
    MS_MADI_25_4R_MC,
    MS_MADI_25_4R,
    MS_MADI_25_2R,
    MS_MADI_26_4R,
    MS_MADI_26_2R,
    MS_MADI_27_4R,
    MS_MADI_27_2R,
    MS_MADI_P_MODE8,
    MS_MADI_P_MODE10,
    MS_MADI_P_MODE_MOT10,
    MS_MADI_P_MODE_MOT8,
    MS_MADI_24_RFBL_NFILM,
    MS_MADI_24_RFBL_FILM,
    MS_MADI_FBL_DNR,
    MS_MADI_FBL_MIU,
    MS_MADI_P_MODE8_NO_MIU,
    MS_MADI_24_4R_880,
    MS_MADI_24_2R_880,
    MS_MADI_25_4R_MC_NW,
    MS_MADI_25_6R_MC,
    MS_MADI_25_14F_6R_MC,    //Add New MADi mode
    MS_MADI_25_4R_884,
    MS_MADI_25_4R_880,
    MS_MADI_25_2R_884,
    MS_MADI_25_2R_880,
    MS_MADI_25_6R_MC_NW,
    MS_MADI_25_12F_8R_MC,
    MS_MADI_25_14F_8R_MC,
    MS_MADI_25_16F_8R_MC,
    MS_MADI_25_6R_FilmPreDet,
    MS_MADI_24_6R_FilmPreDet,
    MS_MADI_25_6R_FilmPreDet_PAL,
    MS_MADI_24_6R_FilmPreDet_PAL,
    MS_MADI_RFBL_2D,
    MS_MADI_RFBL_25D,
    MS_MADI_RFBL_3D,
    MS_MADI_RFBL_3D_YC,
    MS_MADI_RFBL_3D_FILM,
    MS_MADI_P_MODE8_444,
    MS_MADI_P_MODE10_444,
    MS_MADI_RFBL_P_MODE10_MOT,
    MS_MADI_RFBL_P_MODE8_MOT,
    MS_MADI_P_MODE_MOT10_8Frame,
    MS_MADI_P_MODE_MOT10_4Frame,
    MS_MADI_P_MODE_MC_3Frame,
    MS_MADI_P_MODE_MC_4Frame,
    MS_MADI_P_MODE_MC_6Frame_6R,
    MS_MADI_P_MODE_MC_12Frame_8R,
    MS_MADI_P_MODE_MC_8Frame_6R,
    MS_MADI_P_MODE_MC_16Frame_8R,
    MS_MADI_25_8F_4R_MC,
    MS_MADI_25_16F_6R_MC,
    MS_MADI_P_MODE8_2BYTE_3D,
    MS_MADi_25_8F_8R_MC,
    MS_MADI_RFBL_MC,
    MS_MADI_RFBL_P_MODE_MC,
	MS_MADi_25_4R_MC_Yonly,
    MS_MADI_P_MODE_P_MC_12Frame_8R,
    MS_MADI_P_MODE_N_MC_12Frame_8R,
    MS_MADI_25_6F_4R_MC_I,
    MS_MADI_25_6F_4R_MC_P,
    MS_MADI_P_MODE_MC_6Frame,
    MS_MADi_25_4R_I,
    MS_MADi_25_4R_P,
    MS_MADi_25_4R_M_MC,
    MS_MADi_25_16F_8R_M_MC,
    MS_MADi_25_16F_6R_M_MC,
    MS_MADi_P_MODE8_M_444,
    MS_MADi_P_MODE_MC_M_4F,
    MS_MADi_P_MODE10_M_444,
    MS_MADi_P_MODE8_M,
    MS_MADi_P_MODE10_M,
    MS_MADi_25_4R_M,
    MS_MADi_P_MODE_MOT10_M,
    MS_MADi_P_MODE_MOT8_M,
    MS_MADi_P_MODE_MOT10_M_4K,
    MS_MADi_P_MODE10_M_444_4K,
    MS_MADi_P_MODE_MC_12Frame_8R_M,
    MS_MADi_P_MODE_MC_8Frame_8R_M,
    MS_MADI_25_6F_4R_MC,
    MS_MADI_25_6F_4R_MC_Yonly,
    MS_MADI_25_8F_4R_MC_Yonly,

    MS_MADI_P_MODE_RY8, // Maya-4K
    MS_MADI_P_MODE_MOT10_NO_DNR,
    MS_MADI_25_12F_6R_MC,
#if(PQ_SUPPORT_MADI_P_MODE_MOT10_NR_Yonly) // MAZDA
    MS_MADI_P_MODE_MOT10_NR_Yonly,
#endif

    MS_MADI_NUM,
}MS_MADI_TYPE;

typedef enum
{
    MS_VD_SAMPLING_STANDARD,
    MS_VD_SAMPLING_1135,
    MS_VD_SAMPLING_1135_MUL_15,
    MS_VD_SAMPLING_NUM,
}MS_VD_SAMPLING_TYPE;

typedef enum
{
    MS_PQ_IP_VD_SAMPLING,
    MS_PQ_IP_HSD_SAMPLING,
    MS_PQ_IP_ADC_SAMPLING,
    MS_PQ_IP_NUM,
}MS_PQ_IP_TYPE;

typedef enum
{
    MS_ADC_SAMPLING_X_1,
    MS_ADC_SAMPLING_X_2,
    MS_ADC_SAMPLING_X_4,
    MS_ADC_SAMPLING_NUM,
}MS_ADC_SAMPLING_TYPE;

typedef enum
{
    MS_CSC_IP_CSC,
    MS_CSC_IP_VIP_CSC,
    MS_CSC_IP_NUMs,
}MS_CSC_IP_TYPE;

typedef enum
{
    MS_HSD_SAMPLING_Div_1_000,
    MS_HSD_SAMPLING_Div_1_125,
    MS_HSD_SAMPLING_Div_1_250,
    MS_HSD_SAMPLING_Div_1_375,
    MS_HSD_SAMPLING_Div_1_500,
    MS_HSD_SAMPLING_Div_1_625,
    MS_HSD_SAMPLING_Div_1_750,
    MS_HSD_SAMPLING_Div_1_875,
    MS_HSD_SAMPLING_Div_2_000,
    MS_HSD_SAMPLING_NUM,
}MS_HSD_SAMPLING_TYPE;

#ifdef __cplusplus
}
#endif

#endif /* _DRVPQ_DATATYPES_H_ */


