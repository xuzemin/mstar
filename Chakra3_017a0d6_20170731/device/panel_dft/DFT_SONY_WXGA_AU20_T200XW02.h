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

#define FINE_TUNE      "DFT_SONY_WXGA_AU20_T200XW02"

//*************************************************************************
//              Local Definition
//*************************************************************************
#define VIVID_BACKLIGHT             100
#define VIVID_CONTRAST              85
#define VIVID_BRIGHTNESS            48
#define VIVID_SATURATION            48
#define VIVID_SHARPNESS             60
#define VIVID_HUE                   50
#define VIVID_COLOR_TEMP            MS_COLOR_TEMP_COOL


#define STANDARD_BACKLIGHT          100
#define STANDARD_CONTRAST           85
#define STANDARD_BRIGHTNESS         50//48
#define STANDARD_SATURATION         48
#define STANDARD_SHARPNESS          60
#define STANDARD_HUE                50
#define STANDARD_COLOR_TEMP         MS_COLOR_TEMP_COOL

//HDMI STANARD
#define STANDARD_HDMI_BACKLIGHT     100
#define STANDARD_HDMI_CONTRAST      85
#define STANDARD_HDMI_BRIGHTNESS    50//48
#define STANDARD_HDMI_SATURATION    50//48
#define STANDARD_HDMI_SHARPNESS     60
#define STANDARD_HDMI_HUE           50
#define STANDARD_COLOR_HDMI_TEMP    MS_COLOR_TEMP_COOL

//AV STANDARD
#define STANDARD_AV_BACKLIGHT       100
#define STANDARD_AV_CONTRAST        80
#define STANDARD_AV_BRIGHTNESS      50//48
#define STANDARD_AV_SATURATION      70//48
#define STANDARD_AV_SHARPNESS       40//50//60
#define STANDARD_AV_HUE             50
#define STANDARD_COLOR_AV_TEMP      MS_COLOR_TEMP_COOL

//YPBPR STANDARD
#define STANDARD_YPBPR_BACKLIGHT    100
#define STANDARD_YPBPR_CONTRAST     80
#define STANDARD_YPBPR_BRIGHTNESS   50//48
#define STANDARD_YPBPR_SATURATION   50
#define STANDARD_YPBPR_SHARPNESS    60
#define STANDARD_YPBPR_HUE          50
#define STANDARD_COLOR_YPBPR_TEMP   MS_COLOR_TEMP_COOL

//ATV PAL STANDARD
#define STANDARD_ATV_BACKLIGHT      100
#if (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)        // GEM_SYNC_0815
#define STANDARD_ATV_CONTRAST       82//PQ for Gemini
#define STANDARD_ATV_BRIGHTNESS     50//48//PQ for Gemini
#define STANDARD_ATV_SATURATION     55//PQ for Gemini
#else
#define STANDARD_ATV_CONTRAST       82
#define STANDARD_ATV_BRIGHTNESS     50//48
#define STANDARD_ATV_SATURATION     55
#endif
#define STANDARD_ATV_SHARPNESS      60
#define STANDARD_ATV_HUE            50
#define STANDARD_COLOR_ATV_TEMP     MS_COLOR_TEMP_COOL

//SV STANDARD
#define STANDARD_SV_BACKLIGHT       100
#define STANDARD_SV_CONTRAST        82
#define STANDARD_SV_BRIGHTNESS      50//48
#define STANDARD_SV_SATURATION      55
#define STANDARD_SV_SHARPNESS       60
#define STANDARD_SV_HUE             50
#define STANDARD_COLOR_SV_TEMP      MS_COLOR_TEMP_COOL

#define SOFT_BACKLIGHT              100
#define SOFT_CONTRAST               82
#define SOFT_BRIGHTNESS             48
#define SOFT_SATURATION             55
#define SOFT_SHARPNESS              60
#define SOFT_HUE                    50
#define SOFT_COLOR_TEMP             MS_COLOR_TEMP_COOL//XX_COLOR_TEMP_WARM

//------------------------------------------------------------------------------
// Color Temperature
//------------------------------------------------------------------------------

#define INIT_VIDEO_COLOR_TEMP_COOL_R            128//126//111//0x80
#define INIT_VIDEO_COLOR_TEMP_COOL_G            128//128//106//0x80
#define INIT_VIDEO_COLOR_TEMP_COOL_B            128//110//128//0x80

#define INIT_VIDEO_COLOR_TEMP_NORMAL_R          128//118//0x80
#define INIT_VIDEO_COLOR_TEMP_NORMAL_G          128//109//0x80
#define INIT_VIDEO_COLOR_TEMP_NORMAL_B          128//128//0x80

#define INIT_VIDEO_COLOR_TEMP_WARM_R            0x80
#define INIT_VIDEO_COLOR_TEMP_WARM_G            0x80
#define INIT_VIDEO_COLOR_TEMP_WARM_B            0x80

#define INIT_VIDEO_COLOR_TEMP_USER_R            0x80
#define INIT_VIDEO_COLOR_TEMP_USER_G            0x80
#define INIT_VIDEO_COLOR_TEMP_USER_B            0x80

#define INIT_VIDEO_COLOR_TEMP_USER_R_SCALE      0x80 //must refer INIT_VIDEO_COLOR_TEMP_USER_R, for example: 0x80 -> 0x32
#define INIT_VIDEO_COLOR_TEMP_USER_G_SCALE      0x80 //must refer INIT_VIDEO_COLOR_TEMP_USER_G, for example: 0x80 -> 0x32
#define INIT_VIDEO_COLOR_TEMP_USER_B_SCALE      0x80 //must refer INIT_VIDEO_COLOR_TEMP_USER_B, for example: 0x80 -> 0x32



#if ENABLE_DLC

#define DLC_ALGORITHM_OLD                 0
#define DLC_ALGORITHM_NEW                 1

#define DLC_PARAMETER_ALGORITHM_MODE       DLC_ALGORITHM_OLD//DLC_ALGORITHM_NEW

#if DLC_PARAMETER_ALGORITHM_MODE   //for NEW DLC ALGORITHM

#include "New_NoOS_DLC.h"


#else  //for OLD DLC ALGORITHM
#define DLC_PARAMETER_L_L_U                4; // default value: 10
#define DLC_PARAMETER_L_L_D                0; // default value: 10
#define DLC_PARAMETER_L_H_U                0; // default value: 10
#define DLC_PARAMETER_L_H_D                0; // default value: 10
#define DLC_PARAMETER_S_L_U                64; // default value: 128 (0x80)
#define DLC_PARAMETER_S_L_D                12; // default value: 128 (0x80)
#define DLC_PARAMETER_S_H_U                128; // default value: 128 (0x80)
#define DLC_PARAMETER_S_H_D                192; // default value: 128 (0x80)
#define DLC_PARAMETER_PURE_IMAGE_MODE      DLC_PURE_IMAGE_LINEAR_CURVE; // Compare difference of max and min bright
#define DLC_PARAMETER_LEVEL_LIMIT          3; // n = 0 ~ 4 => Limit n levels => ex. n=2, limit 2 level 0xF7, 0xE7
#define DLC_PARAMETER_AVG_DELTA            0; // n = 0 ~ 50, default value: 12
#define DLC_PARAMETER_AVG_DELTA_STILL      0; // n = 0 ~ 15 => 0: disable still curve, 1 ~ 15: enable still curve
#define DLC_PARAMETER_FAST_ALPHA_BLENDING  31; // min 17 ~ max 32
#define DLC_PARAMETER_Y_AVG_THRESHOLD_L    12; // default value: 0
#define DLC_PARAMETER_Y_AVG_THRESHOLD_H    210; // default value: 128
#define DLC_PARAMETER_BLE_POINT            48; // n = 24 ~ 64, default value: 48
#define DLC_PARAMETER_WLE_POINT            48; // n = 24 ~ 64, default value: 48
#define DLC_PARAMETER_ENABLE_BLE           0; // 1: enable; 0: disable
#define DLC_PARAMETER_ENABLE_WLE           0; // 1: enable; 0: disable

#define DLC_CGC_ENABLE                     0; // 1: enable; 0: disable
#define DLC_CGC_CGAIN_OFFSET               0x08; // -31 ~ 31 (bit7 = minus, ex. 0x88 => -8)
#define DLC_CGC_CGAIN_LIMIT_H              0x0C; // 0x00~0x6F
#define DLC_CGC_CGAIN_LIMIT_L              0x38; // 0x00~0x10
#define DLC_CGC_YC_SLOPE                   0x00; // 0x01~0x20
#define DLC_CGC_Y_TH                       0x01; // 0x01~0x0A

#define DLC_PARAMETER_CURVE_MODE           E_XC_DLC_CURVE_MODE_BY_MIX//E_XC_DLC_PURE_IMAGE_DO_NOTHING
#define DLC_PARAMETER_Y_AVG_THRESHOLD_M    70 //99//64 // 180 // 128
#define DLC_PARAMETER_CURVE_MIXALPHA       72 //55//38 // 180 // 128

#define DLC_PARAMETER_SepPoint_H           188
#define DLC_PARAMETER_SepPoint_L           80
#define DLC_PARAMETER_BLEStartPointTH      640 //768
#define DLC_PARAMETER_BLEEndPointTH        320 //420
#define DLC_PARAMETER_DLC_CurveDiff_L_TH   56
#define DLC_PARAMETER_DLC_CurveDiff_H_TH   148
#define DLC_PARAMETER_BLE_Slop_Point1      1032 //1032
#define DLC_PARAMETER_BLE_Slop_Point2      1172 //1196
#define DLC_PARAMETER_BLE_Slop_Point3      1242 //1312
#define DLC_PARAMETER_BLE_Slop_Point4      1324 //1460
#define DLC_PARAMETER_BLE_Slop_Point5      1396 //1630
#define DLC_PARAMETER_BLE_Dark_Slop_Min    1200
#define DLC_PARAMETER_DLC_CurveDiff_Coring_TH 2
#define DLC_PARAMETER_DLC_FAST_ALPHA_BLENDING_MIN 1
#define DLC_PARAMETER_DLC_FAST_ALPHA_BLENDING_MAX 128
#define DLC_PARAMETER_DLC_FlICKER_ALPHA    96
#define DLC_PARAMETER_DLC_YAVG_L_TH        56
#define DLC_PARAMETER_DLC_YAVG_H_TH        136

#define DLC_PARAMETER_DLC_DiffBase_L        4
#define DLC_PARAMETER_DLC_DiffBase_M        14
#define DLC_PARAMETER_DLC_DiffBase_H        20


#endif




extern MS_U8 mApi_DLC_GetLumaCurve(MS_U8 u8Index);
extern MS_U8 mApi_DLC_GetLumaCurve2_a(MS_U8 u8Index);
extern MS_U8 mApi_DLC_GetLumaCurve2_b(MS_U8 u8Index);
extern MS_U8 mApi_DLC_GetDlcHistogramLimitCurve(MS_U8 u8Index);
#endif // #if ENABLE_DLC

