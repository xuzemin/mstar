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
#ifndef MHAL_PQ_H
#define MHAL_PQ_H

#define MEMFMT24BIT_YC10BIT_MOT     0xBB
#define MEMFMT24BIT_YC8BIT_MOT      0xAA
#define MEMFMT24BIT_YC10BIT         0x99
#define MEMFMT24BIT_YC8BIT          0x88
#define MEMFMT24BIT_CLEAR           0x00

#define SC_FILTER_Y_SRAM1               0x00
#define SC_FILTER_Y_SRAM2               0x01
#define SC_FILTER_Y_SRAM3               0x02
#define SC_FILTER_Y_SRAM4               0x03
#define SC_FILTER_C_SRAM1               0x04
#define SC_FILTER_C_SRAM2               0x05
#define SC_FILTER_C_SRAM3               0x06
#define SC_FILTER_C_SRAM4               0x07
#define SC_FILTER_SRAM_COLOR_INDEX      0x08
#define SC_FILTER_SRAM_COLOR_GAIN_SNR   0x09
#define SC_FILTER_SRAM_COLOR_GAIN_DNR   0x0A
#define SC_FILTER_SRAM_ICC_CRD          0x0B
#define SC_FILTER_SRAM_IHC_CRD          0x0C
#define SC_FILTER_SRAM_XVYCC_DE_GAMMA   0x0D
#define SC_FILTER_SRAM_XVYCC_GAMMA      0x0E

#define SUPPORT_SCMI_V2     TRUE
#define SUPPORT_DYNAMIC_MEM_FMT TRUE

#define Y2Y_709_601_VERSION 1

void Hal_PQ_init_riu_base(MS_U32 u32riu_base);
MS_U8 Hal_PQ_get_sync_flag(MS_BOOL bMainWin);
MS_U8 Hal_PQ_get_input_vsync_value(MS_BOOL bMainWin);
MS_U8 Hal_PQ_get_output_vsync_value(MS_BOOL bMainWin);
MS_U8 Hal_PQ_get_input_vsync_polarity(MS_BOOL bMainWin);
void Hal_PQ_set_memfmt_doublebuffer(MS_BOOL bEn);
void Hal_PQ_set_sourceidx(MS_BOOL bMain, MS_U16 u16Idx);
void Hal_PQ_set_mem_fmt(MS_BOOL bMainWin, MS_U16 u16val, MS_U16 u16Mask);
void Hal_PQ_set_mem_fmt_en(MS_BOOL bMainWin, MS_U16 u16val, MS_U16 u16Mask);
void Hal_PQ_set_420upSample(MS_U16 u16value);
void Hal_PQ_set_force_y_motion(MS_BOOL bMainWin, MS_U16 u16value);
MS_U8 Hal_PQ_get_force_y_motion(MS_BOOL bMainWin);
void Hal_PQ_set_force_c_motion(MS_BOOL bMainWin, MS_U16 u16value);
MS_U8 Hal_PQ_get_force_c_motion(MS_BOOL bMainWin);
void Hal_PQ_set_dipf_temporal(MS_BOOL bMainWin, MS_U16 u16val);
MS_U16 Hal_PQ_get_dipf_temporal(MS_BOOL bMainWin);
void Hal_PQ_set_dipf_spatial(MS_BOOL bMainWin, MS_U16 u16val);
MS_U8 Hal_PQ_get_dipf_spatial(MS_BOOL bMainWin);
void Hal_PQ_set_vsp_sram_filter(MS_U8 u8vale);
MS_U8 Hal_PQ_get_vsp_sram_filter(void);
void Hal_PQ_set_dnr(MS_BOOL bMainWin, MS_U8 u8val);
MS_U8 Hal_PQ_get_dnr(MS_BOOL bMainWin);
void Hal_PQ_set_presnr(MS_BOOL bMainWin, MS_U8 u8val);
MS_U8 Hal_PQ_get_presnr(MS_BOOL bMainWin);
void Hal_PQ_set_film(MS_BOOL bMainWin, MS_U16 u16val);
MS_U8 Hal_PQ_get_film(MS_BOOL bMainWin);
void Hal_PQ_set_c_sram_table(MS_U8 u8sramtype, void *pData);
void Hal_PQ_set_y_sram_table(MS_U8 u8sramtype, void *pData);
void Hal_PQ_set_sram_color_index_table(MS_U8 u8sramtype, void *pData);
void Hal_PQ_set_sram_color_gain_snr_table(MS_U8 u8sramtype, void *pData);
void Hal_PQ_set_sram_color_gain_dnr_table(MS_U8 u8sramtype, void *pData);
MS_U16 Hal_PQ_get_420_cup_idx(MS_BOOL bMainWin,MS_420_CUP_TYPE etype);
MS_U16 Hal_PQ_get_hnonlinear_idx(MS_HNONLINEAR_TYPE etype);
MS_U16 Hal_PQ_get_422To444_idx(MS_BOOL bMainWin, MS_422To444_TYPE etype);
MS_U8 Hal_PQ_get_422To444_mode(MS_BOOL bMemFmt422);
MS_U8 Hal_PQ_get_madi_fbl_mode(MS_BOOL bMemFmt422,MS_BOOL bInterlace);
MS_U16 Hal_PQ_get_csc_ip_idx(MS_BOOL bMainWin,MS_CSC_IP_TYPE enCSC);
MS_U16 Hal_PQ_get_madi_idx(MS_BOOL bMainWin, MS_MADI_TYPE etype);
MS_U16 Hal_PQ_get_sram_size(MS_U16 u16sramtype);
MS_U16 Hal_PQ_get_ip_idx(MS_BOOL bMainWin, MS_PQ_IP_TYPE eType);
MS_U16 Hal_PQ_get_hsd_sampling_idx(MS_BOOL bMainWin,MS_HSD_SAMPLING_TYPE eType);
void Hal_PQ_OPWriteOff_Enable(MS_BOOL bEna);
MS_U16 Hal_PQ_get_adc_sampling_idx(MS_BOOL bMainWin,MS_ADC_SAMPLING_TYPE eType);
void Hal_PQ_set_sram_ihc_crd_table(MS_U8 u8sramtype, void *pData);
void Hal_PQ_set_sram_icc_crd_table(MS_U8 u8sramtype, void *pData);
MS_U16 Hal_PQ_get_rw_method(MS_BOOL bMainWin);
void Hal_PQ_set_rw_method(MS_BOOL bMainWin, MS_U16 u16method);
MS_BOOL HAL_PQ_user_mode_control(void);
void HAL_PQ_set_SelectCSC(MS_U16 u16selection, MS_BOOL  bMainWin);
#ifdef UFO_XC_SUPPORT_2STEP_SCALING
void Hal_PQ_Set2StepScaling(MS_BOOL bEnable);
#endif

#endif
void Hal_PQ_set_sram_xvycc_gamma_table(MS_U8 u8sramtype, void *pData);


#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************/
/*                     definition                                             */
/* ****************************************************************************/
#ifdef DRV_SCALER_NR_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

#define DRVSCA_DBG(x)       //x
#define DBG_DEFEATHERING    0
#define DBG_DEFLICKERING    0
#define DBG_DEBOUNCING      0
#define DBG_DYNAMIC_SNR     0
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

/******************************************************************************/
/*                           Global Variables                                 */
/******************************************************************************/

//*************************************************************************
//          Enums
//*************************************************************************


//*************************************************************************
//          Structures
//*************************************************************************


/********************************************************************************/
/*                   Function Prototypes                                        */
/********************************************************************************/
INTERFACE MS_U8 Hal_PQ_GetCurrentMotionValue(void);
INTERFACE void Hal_PQ_AdaptiveTuning(void);
INTERFACE void Hal_PQ_FilmMode_AnyCandence_Enable(MS_BOOL bEnable);
INTERFACE void Hal_PQ_SotreCurrentValue(void);
INTERFACE void Hal_PQ_ReSotreToDefault(void);

#undef INTERFACE
#ifdef __cplusplus
}
#endif

