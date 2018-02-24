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
#define COLOR_REGISTER_VERSION          COLOR_REGISTER_VER_200

//------------------------------------------------------------------------------
// Init ADC
//------------------------------------------------------------------------------
#define INIT_ADC_RGB_RED_OFFSET             0x00
#define INIT_ADC_RGB_GREEN_OFFSET           0x00
#define INIT_ADC_RGB_BLUE_OFFSET            0x00

#define INIT_ADC_RGB_RED_GAIN               0x1000
#define INIT_ADC_RGB_GREEN_GAIN             0x1000
#define INIT_ADC_RGB_BLUE_GAIN              0x1000

//=====================================================
#define INIT_ADC_YPBPR_RED_OFFSET           0x00
#define INIT_ADC_YPBPR_GREEN_OFFSET         0x00
#define INIT_ADC_YPBPR_BLUE_OFFSET          0x00

#define INIT_ADC_YPBPR_RED_GAIN_SD          0x1000
#define INIT_ADC_YPBPR_GREEN_GAIN_SD        0x1000
#define INIT_ADC_YPBPR_BLUE_GAIN_SD         0x1000

#define INIT_ADC_YPBPR_RED_GAIN_HD          0x1000
#define INIT_ADC_YPBPR_GREEN_GAIN_HD        0x1000
#define INIT_ADC_YPBPR_BLUE_GAIN_HD         0x1000

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


#endif /* _QUALITYEX_H_ */
