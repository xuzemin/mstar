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

#ifndef _QUALITYEX_H_
#define _QUALITYEX_H_

//------------------------------------------------------------------------------
// Color Register Version
//------------------------------------------------------------------------------
#define COLOR_REGISTER_VERSION  COLOR_REGISTER_VER_200

//------------------------------------------------------------------------------
// Init ADC
//------------------------------------------------------------------------------
#define INIT_ADC_RGB_RED_OFFSET            0x80
#define INIT_ADC_RGB_GREEN_OFFSET        0x80
#define INIT_ADC_RGB_BLUE_OFFSET        0x80

#define INIT_ADC_RGB_RED_GAIN            0x80
#define INIT_ADC_RGB_GREEN_GAIN            0x80
#define INIT_ADC_RGB_BLUE_GAIN            0x80

//=====================================================
#define INIT_ADC_YPBPR_RED_OFFSET       0x80
#define INIT_ADC_YPBPR_GREEN_OFFSET     0x80
#define INIT_ADC_YPBPR_BLUE_OFFSET      0x80

#define INIT_ADC_YPBPR_RED_GAIN_SD        83
#define INIT_ADC_YPBPR_GREEN_GAIN_SD    70
#define INIT_ADC_YPBPR_BLUE_GAIN_SD        82

#define INIT_ADC_YPBPR_RED_GAIN_HD        79
#define INIT_ADC_YPBPR_GREEN_GAIN_HD    70
#define INIT_ADC_YPBPR_BLUE_GAIN_HD        79

//------------------------------------------------------------------------------
// Color Temperature
//------------------------------------------------------------------------------

#if ENABLE_PRECISE_RGBBRIGHTNESS
#define INIT_VIDEO_COLOR_BRIGHTNESS_COOL_R      (0x80<<3)
#define INIT_VIDEO_COLOR_BRIGHTNESS_COOL_G      (0x80<<3)
#define INIT_VIDEO_COLOR_BRIGHTNESS_COOL_B      (0x80<<3)

#define INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_R    (0x80<<3)
#define INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_G    (0x80<<3)
#define INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_B    (0x80<<3)

#define INIT_VIDEO_COLOR_BRIGHTNESS_WARM_R      (0x80<<3)
#define INIT_VIDEO_COLOR_BRIGHTNESS_WARM_G      (0x80<<3)
#define INIT_VIDEO_COLOR_BRIGHTNESS_WARM_B      (0x80<<3)

#define INIT_VIDEO_COLOR_BRIGHTNESS_USER_R      (0x80<<3)
#define INIT_VIDEO_COLOR_BRIGHTNESS_USER_G      (0x80<<3)
#define INIT_VIDEO_COLOR_BRIGHTNESS_USER_B      (0x80<<3)
#else
#define INIT_VIDEO_COLOR_BRIGHTNESS_COOL_R      0x80
#define INIT_VIDEO_COLOR_BRIGHTNESS_COOL_G      0x80
#define INIT_VIDEO_COLOR_BRIGHTNESS_COOL_B      0x80

#define INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_R    0x80
#define INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_G    0x80
#define INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_B    0x80

#define INIT_VIDEO_COLOR_BRIGHTNESS_WARM_R      0x80
#define INIT_VIDEO_COLOR_BRIGHTNESS_WARM_G      0x80
#define INIT_VIDEO_COLOR_BRIGHTNESS_WARM_B      0x80

#define INIT_VIDEO_COLOR_BRIGHTNESS_USER_R      0x80
#define INIT_VIDEO_COLOR_BRIGHTNESS_USER_G      0x80
#define INIT_VIDEO_COLOR_BRIGHTNESS_USER_B      0x80
#endif

//------------------------------------------------------------------------------
// Default Contrast & Saturation & Hue & Sharpness Value
//------------------------------------------------------------------------------
// Contrast
#define ACE_Contrast_DefaultValue_HDTV          128
#define ACE_Contrast_DefaultValue_SDTV          128
#define ACE_Contrast_DefaultValue_ATV           128
#define ACE_Contrast_DefaultValue_AV            128
#define ACE_Contrast_DefaultValue_SV            128
#define ACE_Contrast_DefaultValue_YPBPR_HD      128
#define ACE_Contrast_DefaultValue_YPBPR_SD      128
#define ACE_Contrast_DefaultValue_HDMI_HD       128
#define ACE_Contrast_DefaultValue_HDMI_SD       128
#define ACE_Contrast_DefaultValue_VGA_DVI       128

// Saturation
#define ACE_Saturation_DefaultValue_HDTV        128
#define ACE_Saturation_DefaultValue_SDTV        128
#define ACE_Saturation_DefaultValue_ATV         128
#define ACE_Saturation_DefaultValue_AV          128
#define ACE_Saturation_DefaultValue_SV          128
#define ACE_Saturation_DefaultValue_YPBPR_HD    128
#define ACE_Saturation_DefaultValue_YPBPR_SD    128
#define ACE_Saturation_DefaultValue_HDMI_HD     128
#define ACE_Saturation_DefaultValue_HDMI_SD     128
#define ACE_Saturation_DefaultValue_VGA_DVI     128

// Sharpness
#define ACE_Sharpness_DefaultValue_HDTV         31
#define ACE_Sharpness_DefaultValue_SDTV         23
#define ACE_Sharpness_DefaultValue_ATV          31
#define ACE_Sharpness_DefaultValue_AV           44
#define ACE_Sharpness_DefaultValue_SV           44
#define ACE_Sharpness_DefaultValue_YPBPR_HD     31
#define ACE_Sharpness_DefaultValue_YPBPR_SD     31
#define ACE_Sharpness_DefaultValue_HDMI_HD      32
#define ACE_Sharpness_DefaultValue_HDMI_SD      32
#define ACE_Sharpness_DefaultValue_VGA_DVI      32

// Hue
#define ACE_Hue_DefaultValue_HDTV               50
#define ACE_Hue_DefaultValue_SDTV               50
#define ACE_Hue_DefaultValue_ATV                50
#define ACE_Hue_DefaultValue_AV                 50
#define ACE_Hue_DefaultValue_SV                 50
#define ACE_Hue_DefaultValue_YPBPR              50
#define ACE_Hue_DefaultValue_HDMI               50
#define ACE_Hue_DefaultValue_VGA_DVI            50

// AV Black Level
#define ACE_AV_BLACK_LEVEL_HIGH_CONTRAST        0x7E
#define ACE_AV_BLACK_LEVEL_HIGH_BRIGHTNESS      0x90

#define ACE_AV_BLACK_LEVEL_LOW_CONTRAST         0x89
#define ACE_AV_BLACK_LEVEL_LOW_BRIGHTNESS       0x90

//ATV Mode
#define ACE_ATV_CONTRAST                        0x98
#define ACE_ATV_BRIGHTNESS                      0x88

// HDMI Black Level
#define ACE_HDMI_BLACK_LEVEL_HIGH_YC_OFFSET     0x00F0
#define ACE_HDMI_BLACK_LEVEL_HIGH_YC_GAIN       0x403B

#define ACE_HDMI_BLACK_LEVEL_LOW_YC_OFFSET      0x00E0
#define ACE_HDMI_BLACK_LEVEL_LOW_YC_GAIN        0x4045

//------------------------------------------------------------------------------
// GAMMA
//------------------------------------------------------------------------------
#define GAMMA_CONTROL   ENABLE

extern code short  tSRGB[3][3];
extern code short  tDefaultColorCorrectionMatrix[];
extern code short  tVideoColorCorrectionMatrix[];
extern code short  tHDTVColorCorrectionMatrix[];
extern code short  tSDTVColorCorrectionMatrix[];
extern code short  tATVColorCorrectionMatrix[];
extern code short  tSDYPbPrColorCorrectionMatrix[];
extern code short  tHDYPbPrColorCorrectionMatrix[];
extern code U8     g_DLC_CURVE_Default_TBL[];
extern code U8     g_DLC_CURVE_00_TBL[];
extern code U8     g_DLC_CURVE_01_TBL[];

#endif /* _QUALITYEX_H_ */
