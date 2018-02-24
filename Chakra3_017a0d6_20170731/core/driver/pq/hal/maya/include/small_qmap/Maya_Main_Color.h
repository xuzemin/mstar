////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (; MStar; Confidential; Information; ) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
//****************************************************
//   Quality Map CodeGen Version 4.0
// 1920
// Maya
// 9/8/2015  9:00:49 PM
// 39630.43853
//****************************************************

#ifndef _MAYA_MAIN_COLOR_H_
#define _MAYA_MAIN_COLOR_H_

#define PQ_IP_NUM_Main_Color 22

typedef enum
{
    #if PQ_QM_CVBS
    QM_RF_NTSC_44_Main_Color, //0
    #endif
    #if PQ_QM_CVBS
    QM_RF_NTSC_M_Main_Color, //1
    #endif
    #if PQ_QM_CVBS
    QM_RF_PAL_BGHI_Main_Color, //2
    #endif
    #if PQ_QM_CVBS
    QM_RF_PAL_60_Main_Color, //3
    #endif
    #if PQ_QM_CVBS
    QM_RF_PAL_M_Main_Color, //4
    #endif
    #if PQ_QM_CVBS
    QM_RF_PAL_N_Main_Color, //5
    #endif
    #if PQ_QM_CVBS
    QM_RF_SECAM_Main_Color, //6
    #endif
    #if PQ_QM_CVBS
    QM_VIF_NTSC_44_Main_Color, //7
    #endif
    #if PQ_QM_CVBS
    QM_VIF_NTSC_M_Main_Color, //8
    #endif
    #if PQ_QM_CVBS
    QM_VIF_PAL_BGHI_Main_Color, //9
    #endif
    #if PQ_QM_CVBS
    QM_VIF_PAL_60_Main_Color, //10
    #endif
    #if PQ_QM_CVBS
    QM_VIF_PAL_M_Main_Color, //11
    #endif
    #if PQ_QM_CVBS
    QM_VIF_PAL_N_Main_Color, //12
    #endif
    #if PQ_QM_CVBS
    QM_VIF_SECAM_Main_Color, //13
    #endif
    #if PQ_QM_CVBS
    QM_SV_NTSC_44_Main_Color, //14
    #endif
    #if PQ_QM_CVBS
    QM_SV_NTSC_M_Main_Color, //15
    #endif
    #if PQ_QM_CVBS
    QM_SV_PAL_BGHI_Main_Color, //16
    #endif
    #if PQ_QM_CVBS
    QM_SV_PAL_60_Main_Color, //17
    #endif
    #if PQ_QM_CVBS
    QM_SV_PAL_M_Main_Color, //18
    #endif
    #if PQ_QM_CVBS
    QM_SV_PAL_N_Main_Color, //19
    #endif
    #if PQ_QM_CVBS
    QM_SV_SECAM_Main_Color, //20
    #endif
    #if PQ_QM_CVBS
    QM_AV_NTSC_44_Main_Color, //21
    #endif
    #if PQ_QM_CVBS
    QM_AV_NTSC_M_Main_Color, //22
    #endif
    #if PQ_QM_CVBS
    QM_AV_PAL_BGHI_Main_Color, //23
    #endif
    #if PQ_QM_CVBS
    QM_AV_PAL_60_Main_Color, //24
    #endif
    #if PQ_QM_CVBS
    QM_AV_PAL_M_Main_Color, //25
    #endif
    #if PQ_QM_CVBS
    QM_AV_PAL_N_Main_Color, //26
    #endif
    #if PQ_QM_CVBS
    QM_AV_SECAM_Main_Color, //27
    #endif
    #if PQ_QM_CVBS
    QM_SCART_AV_NTSC_44_Main_Color, //28
    #endif
    #if PQ_QM_CVBS
    QM_SCART_AV_NTSC_M_Main_Color, //29
    #endif
    #if PQ_QM_CVBS
    QM_SCART_AV_PAL_BGHI_Main_Color, //30
    #endif
    #if PQ_QM_CVBS
    QM_SCART_AV_PAL_60_Main_Color, //31
    #endif
    #if PQ_QM_CVBS
    QM_SCART_AV_PAL_M_Main_Color, //32
    #endif
    #if PQ_QM_CVBS
    QM_SCART_AV_PAL_N_Main_Color, //33
    #endif
    #if PQ_QM_CVBS
    QM_SCART_AV_SECAM_Main_Color, //34
    #endif
    #if PQ_QM_CVBS
    QM_SCART_SV_NTSC_44_Main_Color, //35
    #endif
    #if PQ_QM_CVBS
    QM_SCART_SV_NTSC_M_Main_Color, //36
    #endif
    #if PQ_QM_CVBS
    QM_SCART_SV_PAL_BGHI_Main_Color, //37
    #endif
    #if PQ_QM_CVBS
    QM_SCART_SV_PAL_60_Main_Color, //38
    #endif
    #if PQ_QM_CVBS
    QM_SCART_SV_PAL_M_Main_Color, //39
    #endif
    #if PQ_QM_CVBS
    QM_SCART_SV_PAL_N_Main_Color, //40
    #endif
    #if PQ_QM_CVBS
    QM_SCART_SV_SECAM_Main_Color, //41
    #endif
    #if PQ_QM_CVBS
    QM_SCART_RGB_NTSC_Main_Color, //42
    #endif
    #if PQ_QM_CVBS
    QM_SCART_RGB_PAL_Main_Color, //43
    #endif
    #if PQ_QM_YPBPR
    QM_YPbPr_480i_Main_Color, //44
    #endif
    #if PQ_QM_YPBPR
    QM_YPbPr_576i_Main_Color, //45
    #endif
    #if PQ_QM_YPBPR
    QM_YPbPr_480p_Main_Color, //46
    #endif
    #if PQ_QM_YPBPR
    QM_YPbPr_576p_Main_Color, //47
    #endif
    #if PQ_QM_YPBPR
    QM_YPbPr_720p_24hz_Main_Color, //48
    #endif
    #if PQ_QM_YPBPR
    QM_YPbPr_720p_50hz_Main_Color, //49
    #endif
    #if PQ_QM_YPBPR
    QM_YPbPr_720p_60hz_Main_Color, //50
    #endif
    #if PQ_QM_YPBPR
    QM_YPbPr_1080i_50hz_Main_Color, //51
    #endif
    #if PQ_QM_YPBPR
    QM_YPbPr_1080i_60hz_Main_Color, //52
    #endif
    #if PQ_QM_YPBPR
    QM_YPbPr_1080p_24hz_Main_Color, //53
    #endif
    #if PQ_QM_YPBPR
    QM_YPbPr_1080p_50hz_Main_Color, //54
    #endif
    #if PQ_QM_YPBPR
    QM_YPbPr_1080p_60hz_Main_Color, //55
    #endif
    #if PQ_QM_HMDI
    QM_HDMI_480i_Main_Color, //56
    #endif
    #if PQ_QM_HMDI
    QM_HDMI_576i_Main_Color, //57
    #endif
    #if PQ_QM_HMDI
    QM_HDMI_480p_Main_Color, //58
    #endif
    #if PQ_QM_HMDI
    QM_HDMI_576p_Main_Color, //59
    #endif
    #if PQ_QM_HMDI
    QM_HDMI_720p_24hz_Main_Color, //60
    #endif
    #if PQ_QM_HMDI
    QM_HDMI_720p_50hz_Main_Color, //61
    #endif
    #if PQ_QM_HMDI
    QM_HDMI_720p_60hz_Main_Color, //62
    #endif
    #if PQ_QM_HMDI
    QM_HDMI_FP_720p_Main_Color, //63
    #endif
    #if PQ_QM_HMDI
    QM_HDMI_1080i_50hz_Main_Color, //64
    #endif
    #if PQ_QM_HMDI
    QM_HDMI_1080i_60hz_Main_Color, //65
    #endif
    #if PQ_QM_HMDI
    QM_HDMI_1080p_24hz_Main_Color, //66
    #endif
    #if PQ_QM_HMDI
    QM_HDMI_1080p_60hz_Main_Color, //67
    #endif
    #if PQ_QM_HMDI
    QM_HDMI_1080p_50hz_Main_Color, //68
    #endif
    #if PQ_QM_HMDI
    QM_HDMI_FP_1080i_Main_Color, //69
    #endif
    #if PQ_QM_HMDI
    QM_HDMI_FP_1080p_Main_Color, //70
    #endif
    #if PQ_QM_HMDI
    QM_4K2K_24Hz_Main_Color, //71
    #endif
    #if PQ_QM_HMDI
    QM_4K2K_30Hz_Main_Color, //72
    #endif
    #if PQ_QM_HMDI
    QM_4K2K_60Hz_Main_Color, //73
    #endif
    #if PQ_QM_HDMI_PC
    QM_HDMI_444_PC_Hup_Vup_Main_Color, //74
    #endif
    #if PQ_QM_HDMI_PC
    QM_HDMI_444_PC_Hup_Vdown_Main_Color, //75
    #endif
    #if PQ_QM_HDMI_PC
    QM_HDMI_444_PC_Hup_Vno_Main_Color, //76
    #endif
    #if PQ_QM_HDMI_PC
    QM_HDMI_444_PC_Hdown_Vup_Main_Color, //77
    #endif
    #if PQ_QM_HDMI_PC
    QM_HDMI_444_PC_Hdown_Vdown_Main_Color, //78
    #endif
    #if PQ_QM_HDMI_PC
    QM_HDMI_444_PC_Hdown_Vno_Main_Color, //79
    #endif
    #if PQ_QM_HDMI_PC
    QM_HDMI_444_PC_Hno_Vup_Main_Color, //80
    #endif
    #if PQ_QM_HDMI_PC
    QM_HDMI_444_PC_Hno_Vdown_Main_Color, //81
    #endif
    #if PQ_QM_HDMI_PC
    QM_HDMI_444_PC_Hno_Vno_Main_Color, //82
    #endif
    #if PQ_QM_HDMI_PC
    QM_HDMI_444_PC_Hno_Vno_4K_Main_Color, //83
    #endif
    #if PQ_QM_HDMI_PC
    QM_HDMI_422_PC_Hup_Vup_Main_Color, //84
    #endif
    #if PQ_QM_HDMI_PC
    QM_HDMI_422_PC_Hup_Vdown_Main_Color, //85
    #endif
    #if PQ_QM_HDMI_PC
    QM_HDMI_422_PC_Hup_Vno_Main_Color, //86
    #endif
    #if PQ_QM_HDMI_PC
    QM_HDMI_422_PC_Hdown_Vup_Main_Color, //87
    #endif
    #if PQ_QM_HDMI_PC
    QM_HDMI_422_PC_Hdown_Vdown_Main_Color, //88
    #endif
    #if PQ_QM_HDMI_PC
    QM_HDMI_422_PC_Hdown_Vno_Main_Color, //89
    #endif
    #if PQ_QM_HDMI_PC
    QM_HDMI_422_PC_Hno_Vup_Main_Color, //90
    #endif
    #if PQ_QM_HDMI_PC
    QM_HDMI_422_PC_Hno_Vdown_Main_Color, //91
    #endif
    #if PQ_QM_HDMI_PC
    QM_HDMI_422_PC_Hno_Vno_Main_Color, //92
    #endif
    #if PQ_QM_PC
    QM_DVI_Dsub_HDMI_RGB_PC_Hup_Vup_Main_Color, //93
    #endif
    #if PQ_QM_PC
    QM_DVI_Dsub_HDMI_RGB_PC_Hup_Vdown_Main_Color, //94
    #endif
    #if PQ_QM_PC
    QM_DVI_Dsub_HDMI_RGB_PC_Hup_Vno_Main_Color, //95
    #endif
    #if PQ_QM_PC
    QM_DVI_Dsub_HDMI_RGB_PC_Hdown_Vup_Main_Color, //96
    #endif
    #if PQ_QM_PC
    QM_DVI_Dsub_HDMI_RGB_PC_Hdown_Vdown_Main_Color, //97
    #endif
    #if PQ_QM_PC
    QM_DVI_Dsub_HDMI_RGB_PC_Hdown_Vno_Main_Color, //98
    #endif
    #if PQ_QM_PC
    QM_DVI_Dsub_HDMI_RGB_PC_Hno_Vup_Main_Color, //99
    #endif
    #if PQ_QM_PC
    QM_DVI_Dsub_HDMI_RGB_PC_Hno_Vdown_Main_Color, //100
    #endif
    #if PQ_QM_PC
    QM_DVI_Dsub_HDMI_RGB_PC_Hno_Vno_Main_Color, //101
    #endif
    #if PQ_QM_PC
    QM_DVI_Dsub_HDMI_RGB_PC_Hno_Vno_4K_Main_Color, //102
    #endif
    #if PQ_QM_DTV
    QM_DTV_480i_352x480_MPEG2_Main_Color, //103
    #endif
    #if PQ_QM_DTV
    QM_DTV_480i_MPEG2_Main_Color, //104
    #endif
    #if PQ_QM_DTV
    QM_DTV_576i_MPEG2_Main_Color, //105
    #endif
    #if PQ_QM_DTV
    QM_DTV_480p_MPEG2_Main_Color, //106
    #endif
    #if PQ_QM_DTV
    QM_DTV_576p_MPEG2_Main_Color, //107
    #endif
    #if PQ_QM_DTV
    QM_DTV_720p_24hz_MPEG2_Main_Color, //108
    #endif
    #if PQ_QM_DTV
    QM_DTV_720p_50hz_MPEG2_Main_Color, //109
    #endif
    #if PQ_QM_DTV
    QM_DTV_720p_60hz_MPEG2_Main_Color, //110
    #endif
    #if PQ_QM_DTV
    QM_DTV_1080i_50hz_MPEG2_Main_Color, //111
    #endif
    #if PQ_QM_DTV
    QM_DTV_1080i_60hz_MPEG2_Main_Color, //112
    #endif
    #if PQ_QM_DTV
    QM_DTV_1080p_24hz_MPEG2_Main_Color, //113
    #endif
    #if PQ_QM_DTV
    QM_DTV_1080p_50hz_MPEG2_Main_Color, //114
    #endif
    #if PQ_QM_DTV
    QM_DTV_1080p_60hz_MPEG2_Main_Color, //115
    #endif
    #if PQ_QM_DTV
    QM_DTV_4K2K_MPEG2_Main_Color, //116
    #endif
    #if PQ_QM_DTV
    QM_DTV_4K2K_60Hz_MPEG2_Main_Color, //117
    #endif
    #if PQ_QM_DTV
    QM_DTV_480i_352x480_H264_Main_Color, //118
    #endif
    #if PQ_QM_DTV
    QM_DTV_480i_H264_Main_Color, //119
    #endif
    #if PQ_QM_DTV
    QM_DTV_576i_H264_Main_Color, //120
    #endif
    #if PQ_QM_DTV
    QM_DTV_480p_H264_Main_Color, //121
    #endif
    #if PQ_QM_DTV
    QM_DTV_576p_H264_Main_Color, //122
    #endif
    #if PQ_QM_DTV
    QM_DTV_720p_24hz_H264_Main_Color, //123
    #endif
    #if PQ_QM_DTV
    QM_DTV_720p_50hz_H264_Main_Color, //124
    #endif
    #if PQ_QM_DTV
    QM_DTV_720p_60hz_H264_Main_Color, //125
    #endif
    #if PQ_QM_DTV
    QM_DTV_1080i_50hz_H264_Main_Color, //126
    #endif
    #if PQ_QM_DTV
    QM_DTV_1080i_60hz_H264_Main_Color, //127
    #endif
    #if PQ_QM_DTV
    QM_DTV_1080p_24hz_H264_Main_Color, //128
    #endif
    #if PQ_QM_DTV
    QM_DTV_1080p_50hz_H264_Main_Color, //129
    #endif
    #if PQ_QM_DTV
    QM_DTV_1080p_60hz_H264_Main_Color, //130
    #endif
    #if PQ_QM_DTV
    QM_DTV_4K2K_H264_Main_Color, //131
    #endif
    #if PQ_QM_DTV
    QM_DTV_4K2K_60Hz_H264_Main_Color, //132
    #endif
    #if PQ_QM_MM_VIDEO
    QM_Multimedia_video_SD_interlace_Main_Color, //133
    #endif
    #if PQ_QM_MM_VIDEO
    QM_Multimedia_video_SD_progressive_Main_Color, //134
    #endif
    #if PQ_QM_MM_VIDEO
    QM_Multimedia_video_SD_progressive_24hz_Main_Color, //135
    #endif
    #if PQ_QM_MM_VIDEO
    QM_Multimedia_video_HD_interlace_Main_Color, //136
    #endif
    #if PQ_QM_MM_VIDEO
    QM_Multimedia_video_HD_progressive_Main_Color, //137
    #endif
    #if PQ_QM_MM_VIDEO
    QM_Multimedia_video_HD_progressive_24hz_Main_Color, //138
    #endif
    #if PQ_QM_MM_PHOTO
    QM_Multimedia_photo_SD_progressive_Main_Color, //139
    #endif
    #if PQ_QM_MM_PHOTO
    QM_Multimedia_photo_HD_progressive_Main_Color, //140
    #endif
    #if PQ_QM_MM_VIDEO
    QM_Multimedia_video_online_SD_interlace_Main_Color, //141
    #endif
    #if PQ_QM_MM_VIDEO
    QM_Multimedia_video_online_SD_progressive_Main_Color, //142
    #endif
    #if PQ_QM_MM_VIDEO
    QM_Multimedia_video_online_SD_progressive_24hz_Main_Color, //143
    #endif
    #if PQ_QM_MM_VIDEO
    QM_Multimedia_video_online_HD_interlace_Main_Color, //144
    #endif
    #if PQ_QM_MM_VIDEO
    QM_Multimedia_video_online_HD_progressive_Main_Color, //145
    #endif
    #if PQ_QM_MM_VIDEO
    QM_Multimedia_video_online_HD_progressive_24hz_Main_Color, //146
    #endif
    #if PQ_QM_MM_VIDEO
    QM_Multimedia_video_4K2K_FS_progressive_Main_Color, //147
    #endif
    #if PQ_QM_MM_VIDEO
    QM_MM_4K2K_Main_Color, //148
    #endif
    #if PQ_QM_MM_PHOTO
    QM_MM_4K2K_Photo_Main_Color, //149
    #endif
    #if PQ_QM_MM_VIDEO
    QM_MM_4K2K_60Hz_Main_Color, //150
    #endif
    #if PQ_QM_MM_VIDEO
    QM_MM_non_4K2K_Main_Color, //151
    #endif
    #if PQ_QM_DTV
    QM_DTV_iFrame_SD_interlace_Main_Color, //152
    #endif
    #if PQ_QM_DTV
    QM_DTV_iFrame_SD_progressive_Main_Color, //153
    #endif
    #if PQ_QM_DTV
    QM_DTV_iFrame_HD_interlace_Main_Color, //154
    #endif
    #if PQ_QM_DTV
    QM_DTV_iFrame_HD_progressive_Main_Color, //155
    #endif
    #if PQ_QM_3D
    QM_3D_Video_interlace_Main_Color, //156
    #endif
    #if PQ_QM_3D
    QM_3D_Video_progressive_Main_Color, //157
    #endif
    QM_INPUTTYPE_NUM_Main_Color, // 158
} SC_QUALITY_MAP_INDEX_e_Main_Color;

typedef enum
{
PQ_IP_VIP_FCC_full_range_Main_Color,  //0
PQ_IP_VIP_FCC_T1_Main_Color,  //1
PQ_IP_VIP_FCC_T2_Main_Color,  //2
PQ_IP_VIP_FCC_T3_Main_Color,  //3
PQ_IP_VIP_FCC_T4_Main_Color,  //4
PQ_IP_VIP_FCC_T5_Main_Color,  //5
PQ_IP_VIP_FCC_T6_Main_Color,  //6
PQ_IP_VIP_FCC_T7_Main_Color,  //7
PQ_IP_VIP_FCC_T8_Main_Color,  //8
PQ_IP_VIP_FCC_T9_Main_Color,  //9
PQ_IP_VIP_IHC_Main_Color,  //10
PQ_IP_VIP_IHC_Ymode_Main_Color,  //11
PQ_IP_VIP_IHC_SETTING_Main_Color,  //12
PQ_IP_VIP_ICC_Main_Color,  //13
PQ_IP_VIP_ICC_Ymode_Main_Color,  //14
PQ_IP_VIP_ICC_SETTING_Main_Color,  //15
PQ_IP_VIP_Ymode_Yvalue_ALL_Main_Color,  //16
PQ_IP_VIP_Ymode_Yvalue_SETTING_Main_Color,  //17
PQ_IP_VIP_IBC_Main_Color,  //18
PQ_IP_VIP_IBC_SETTING_Main_Color,  //19
PQ_IP_VIP_Peaking_band_Main_Color,  //20
PQ_IP_VIP_Peaking_Pcoring_Main_Color,  //21
 }   PQ_IPTYPE_Main_Color;

typedef enum
{
PQ_IP_VIP_FCC_full_range_COM_Main_Color,  //0
PQ_IP_VIP_FCC_T1_COM_Main_Color,  //1
PQ_IP_VIP_FCC_T2_COM_Main_Color,  //2
PQ_IP_VIP_FCC_T3_COM_Main_Color,  //3
PQ_IP_VIP_FCC_T4_COM_Main_Color,  //4
PQ_IP_VIP_FCC_T5_COM_Main_Color,  //5
PQ_IP_VIP_FCC_T6_COM_Main_Color,  //6
PQ_IP_VIP_FCC_T7_COM_Main_Color,  //7
PQ_IP_VIP_FCC_T8_COM_Main_Color,  //8
PQ_IP_VIP_FCC_T9_COM_Main_Color,  //9
PQ_IP_VIP_IHC_COM_Main_Color,  //10
PQ_IP_VIP_IHC_Ymode_COM_Main_Color,  //11
PQ_IP_VIP_IHC_SETTING_COM_Main_Color,  //12
PQ_IP_VIP_ICC_COM_Main_Color,  //13
PQ_IP_VIP_ICC_Ymode_COM_Main_Color,  //14
PQ_IP_VIP_ICC_SETTING_COM_Main_Color,  //15
PQ_IP_VIP_Ymode_Yvalue_ALL_COM_Main_Color,  //16
PQ_IP_VIP_Ymode_Yvalue_SETTING_COM_Main_Color,  //17
PQ_IP_VIP_IBC_COM_Main_Color,  //18
PQ_IP_VIP_IBC_SETTING_COM_Main_Color,  //19
PQ_IP_VIP_Peaking_band_COM_Main_Color,  //20
PQ_IP_VIP_Peaking_Pcoring_COM_Main_Color,  //21
PQ_IP_COM_NUMS_Main_Color
} PQ_IP_COM_Group_Main_Color;

typedef enum
{
PQ_IP_VIP_FCC_full_range_OFF_Main_Color,
PQ_IP_VIP_FCC_full_range_ON_Main_Color,
PQ_IP_VIP_FCC_full_range_NUMS_Main_Color
} PQ_IP_VIP_FCC_full_range_Group_Main_Color;

typedef enum
{
PQ_IP_VIP_FCC_T1_OFF_Main_Color,
PQ_IP_VIP_FCC_T1_S4_Main_Color,
PQ_IP_VIP_FCC_T1_NUMS_Main_Color
} PQ_IP_VIP_FCC_T1_Group_Main_Color;

typedef enum
{
PQ_IP_VIP_FCC_T2_OFF_Main_Color,
PQ_IP_VIP_FCC_T2_S8_Main_Color,
PQ_IP_VIP_FCC_T2_NUMS_Main_Color
} PQ_IP_VIP_FCC_T2_Group_Main_Color;

typedef enum
{
PQ_IP_VIP_FCC_T3_OFF_Main_Color,
PQ_IP_VIP_FCC_T3_S4_Main_Color,
PQ_IP_VIP_FCC_T3_NUMS_Main_Color
} PQ_IP_VIP_FCC_T3_Group_Main_Color;

typedef enum
{
PQ_IP_VIP_FCC_T4_OFF_Main_Color,
PQ_IP_VIP_FCC_T4_S4_Main_Color,
PQ_IP_VIP_FCC_T4_NUMS_Main_Color
} PQ_IP_VIP_FCC_T4_Group_Main_Color;

typedef enum
{
PQ_IP_VIP_FCC_T5_OFF_Main_Color,
PQ_IP_VIP_FCC_T5_S6_Main_Color,
PQ_IP_VIP_FCC_T5_S8_Main_Color,
PQ_IP_VIP_FCC_T5_NUMS_Main_Color
} PQ_IP_VIP_FCC_T5_Group_Main_Color;

typedef enum
{
PQ_IP_VIP_FCC_T6_OFF_Main_Color,
PQ_IP_VIP_FCC_T6_S6_Main_Color,
PQ_IP_VIP_FCC_T6_S8_Main_Color,
PQ_IP_VIP_FCC_T6_NUMS_Main_Color
} PQ_IP_VIP_FCC_T6_Group_Main_Color;

typedef enum
{
PQ_IP_VIP_FCC_T7_OFF_Main_Color,
PQ_IP_VIP_FCC_T7_S8_Main_Color,
PQ_IP_VIP_FCC_T7_NUMS_Main_Color
} PQ_IP_VIP_FCC_T7_Group_Main_Color;

typedef enum
{
PQ_IP_VIP_FCC_T8_OFF_Main_Color,
PQ_IP_VIP_FCC_T8_S5_Main_Color,
PQ_IP_VIP_FCC_T8_NUMS_Main_Color
} PQ_IP_VIP_FCC_T8_Group_Main_Color;

typedef enum
{
PQ_IP_VIP_FCC_T9_OFF_Main_Color,
PQ_IP_VIP_FCC_T9_S5_Main_Color,
PQ_IP_VIP_FCC_T9_NUMS_Main_Color
} PQ_IP_VIP_FCC_T9_Group_Main_Color;

typedef enum
{
PQ_IP_VIP_IHC_OFF_Main_Color,
PQ_IP_VIP_IHC_ON_Main_Color,
PQ_IP_VIP_IHC_ON_Sram_Main_Color,
PQ_IP_VIP_IHC_NUMS_Main_Color
} PQ_IP_VIP_IHC_Group_Main_Color;

typedef enum
{
PQ_IP_VIP_IHC_Ymode_OFF_Main_Color,
PQ_IP_VIP_IHC_Ymode_ON_Main_Color,
PQ_IP_VIP_IHC_Ymode_ON_diff_c_Main_Color,
PQ_IP_VIP_IHC_Ymode_NUMS_Main_Color
} PQ_IP_VIP_IHC_Ymode_Group_Main_Color;

typedef enum
{
PQ_IP_VIP_IHC_SETTING_OFF_Main_Color,
PQ_IP_VIP_IHC_SETTING_N_20_Main_Color,
PQ_IP_VIP_IHC_SETTING_P_20_Main_Color,
PQ_IP_VIP_IHC_SETTING_0x22_Main_Color,
PQ_IP_VIP_IHC_SETTING_RF_PAL_Main_Color,
PQ_IP_VIP_IHC_SETTING_RF_PAL_V_Main_Color,
PQ_IP_VIP_IHC_SETTING_RF_NTSC_Main_Color,
PQ_IP_VIP_IHC_SETTING_RF_NTSC_V_Main_Color,
PQ_IP_VIP_IHC_SETTING_AV_PAL_Main_Color,
PQ_IP_VIP_IHC_SETTING_AV_PAL_V_Main_Color,
PQ_IP_VIP_IHC_SETTING_AV_NTSC_Main_Color,
PQ_IP_VIP_IHC_SETTING_AV_NTSC_V_Main_Color,
PQ_IP_VIP_IHC_SETTING_YPBPR_SD_Main_Color,
PQ_IP_VIP_IHC_SETTING_YPBPR_SD_V_Main_Color,
PQ_IP_VIP_IHC_SETTING_YPBPR_HD_Main_Color,
PQ_IP_VIP_IHC_SETTING_YPBPR_HD_V_Main_Color,
PQ_IP_VIP_IHC_SETTING_HDMI_SD_Main_Color,
PQ_IP_VIP_IHC_SETTING_HDMI_SD_V_Main_Color,
PQ_IP_VIP_IHC_SETTING_HDMI_HD_Main_Color,
PQ_IP_VIP_IHC_SETTING_HDMI_HD_V_Main_Color,
PQ_IP_VIP_IHC_SETTING_DTV_SD_Main_Color,
PQ_IP_VIP_IHC_SETTING_DTV_SD_V_Main_Color,
PQ_IP_VIP_IHC_SETTING_DTV_HD_Main_Color,
PQ_IP_VIP_IHC_SETTING_DTV_HD_V_Main_Color,
PQ_IP_VIP_IHC_SETTING_MM_SD_Main_Color,
PQ_IP_VIP_IHC_SETTING_MM_SD_V_Main_Color,
PQ_IP_VIP_IHC_SETTING_MM_HD_Main_Color,
PQ_IP_VIP_IHC_SETTING_MM_HD_V_Main_Color,
PQ_IP_VIP_IHC_SETTING_HDMI_IHC_V3_Main_Color,
PQ_IP_VIP_IHC_SETTING_NUMS_Main_Color
} PQ_IP_VIP_IHC_SETTING_Group_Main_Color;

typedef enum
{
PQ_IP_VIP_ICC_OFF_Main_Color,
PQ_IP_VIP_ICC_ON_Main_Color,
PQ_IP_VIP_ICC_ON_Sram_Main_Color,
PQ_IP_VIP_ICC_NUMS_Main_Color
} PQ_IP_VIP_ICC_Group_Main_Color;

typedef enum
{
PQ_IP_VIP_ICC_Ymode_OFF_Main_Color,
PQ_IP_VIP_ICC_Ymode_ON_Main_Color,
PQ_IP_VIP_ICC_Ymode_HDMI_HD_Main_Color,
PQ_IP_VIP_ICC_Ymode_NUMS_Main_Color
} PQ_IP_VIP_ICC_Ymode_Group_Main_Color;

typedef enum
{
PQ_IP_VIP_ICC_SETTING_OFF_Main_Color,
PQ_IP_VIP_ICC_SETTING_INC_8_Main_Color,
PQ_IP_VIP_ICC_SETTING_INC_3_Main_Color,
PQ_IP_VIP_ICC_SETTING_INC_B_Main_Color,
PQ_IP_VIP_ICC_SETTING_DEC_3_Main_Color,
PQ_IP_VIP_ICC_SETTING_RF_PAL_Main_Color,
PQ_IP_VIP_ICC_SETTING_RF_PAL_V_Main_Color,
PQ_IP_VIP_ICC_SETTING_RF_NTSC_Main_Color,
PQ_IP_VIP_ICC_SETTING_RF_NTSC_V_Main_Color,
PQ_IP_VIP_ICC_SETTING_AV_PAL_Main_Color,
PQ_IP_VIP_ICC_SETTING_AV_PAL_V_Main_Color,
PQ_IP_VIP_ICC_SETTING_AV_NTSC_Main_Color,
PQ_IP_VIP_ICC_SETTING_AV_NTSC_V_Main_Color,
PQ_IP_VIP_ICC_SETTING_YPBPR_SD_Main_Color,
PQ_IP_VIP_ICC_SETTING_YPBPR_SD_V_Main_Color,
PQ_IP_VIP_ICC_SETTING_YPBPR_HD_Main_Color,
PQ_IP_VIP_ICC_SETTING_YPBPR_HD_V_Main_Color,
PQ_IP_VIP_ICC_SETTING_HDMI_SD_Main_Color,
PQ_IP_VIP_ICC_SETTING_HDMI_SD_V_Main_Color,
PQ_IP_VIP_ICC_SETTING_HDMI_HD_Main_Color,
PQ_IP_VIP_ICC_SETTING_HDMI_HD_V_Main_Color,
PQ_IP_VIP_ICC_SETTING_DTV_SD_Main_Color,
PQ_IP_VIP_ICC_SETTING_DTV_SD_V_Main_Color,
PQ_IP_VIP_ICC_SETTING_DTV_HD_Main_Color,
PQ_IP_VIP_ICC_SETTING_DTV_HD_V_Main_Color,
PQ_IP_VIP_ICC_SETTING_MM_SD_Main_Color,
PQ_IP_VIP_ICC_SETTING_MM_SD_V_Main_Color,
PQ_IP_VIP_ICC_SETTING_MM_HD_Main_Color,
PQ_IP_VIP_ICC_SETTING_MM_HD_V_Main_Color,
PQ_IP_VIP_ICC_SETTING_HDMI_ICC_V3_Main_Color,
PQ_IP_VIP_ICC_SETTING_NUMS_Main_Color
} PQ_IP_VIP_ICC_SETTING_Group_Main_Color;

typedef enum
{
PQ_IP_VIP_Ymode_Yvalue_ALL_Y1_Main_Color,
PQ_IP_VIP_Ymode_Yvalue_ALL_NUMS_Main_Color
} PQ_IP_VIP_Ymode_Yvalue_ALL_Group_Main_Color;

typedef enum
{
PQ_IP_VIP_Ymode_Yvalue_SETTING_Y1_Main_Color,
PQ_IP_VIP_Ymode_Yvalue_SETTING_Y2_Main_Color,
PQ_IP_VIP_Ymode_Yvalue_SETTING_Y_15Win2_Main_Color,
PQ_IP_VIP_Ymode_Yvalue_SETTING_NUMS_Main_Color
} PQ_IP_VIP_Ymode_Yvalue_SETTING_Group_Main_Color;

typedef enum
{
PQ_IP_VIP_IBC_OFF_Main_Color,
PQ_IP_VIP_IBC_ON_Main_Color,
PQ_IP_VIP_IBC_NUMS_Main_Color
} PQ_IP_VIP_IBC_Group_Main_Color;

typedef enum
{
PQ_IP_VIP_IBC_SETTING_OFF_Main_Color,
PQ_IP_VIP_IBC_SETTING_DEC_10_Main_Color,
PQ_IP_VIP_IBC_SETTING_DEC_18_Main_Color,
PQ_IP_VIP_IBC_SETTING_DEC_0C_Main_Color,
PQ_IP_VIP_IBC_SETTING_RF_PAL_Main_Color,
PQ_IP_VIP_IBC_SETTING_RF_PAL_V_Main_Color,
PQ_IP_VIP_IBC_SETTING_RF_NTSC_Main_Color,
PQ_IP_VIP_IBC_SETTING_RF_NTSC_V_Main_Color,
PQ_IP_VIP_IBC_SETTING_AV_PAL_Main_Color,
PQ_IP_VIP_IBC_SETTING_AV_PAL_V_Main_Color,
PQ_IP_VIP_IBC_SETTING_AV_NTSC_Main_Color,
PQ_IP_VIP_IBC_SETTING_AV_NTSC_V_Main_Color,
PQ_IP_VIP_IBC_SETTING_YPBPR_SD_Main_Color,
PQ_IP_VIP_IBC_SETTING_YPBPR_SD_V_Main_Color,
PQ_IP_VIP_IBC_SETTING_YPBPR_HD_Main_Color,
PQ_IP_VIP_IBC_SETTING_YPBPR_HD_V_Main_Color,
PQ_IP_VIP_IBC_SETTING_HDMI_SD_Main_Color,
PQ_IP_VIP_IBC_SETTING_HDMI_SD_V_Main_Color,
PQ_IP_VIP_IBC_SETTING_HDMI_HD_Main_Color,
PQ_IP_VIP_IBC_SETTING_HDMI_HD_V_Main_Color,
PQ_IP_VIP_IBC_SETTING_DTV_SD_Main_Color,
PQ_IP_VIP_IBC_SETTING_DTV_SD_V_Main_Color,
PQ_IP_VIP_IBC_SETTING_DTV_HD_Main_Color,
PQ_IP_VIP_IBC_SETTING_DTV_HD_V_Main_Color,
PQ_IP_VIP_IBC_SETTING_MM_SD_Main_Color,
PQ_IP_VIP_IBC_SETTING_MM_SD_V_Main_Color,
PQ_IP_VIP_IBC_SETTING_MM_HD_Main_Color,
PQ_IP_VIP_IBC_SETTING_MM_HD_V_Main_Color,
PQ_IP_VIP_IBC_SETTING_HDMI_IBC_V3_Main_Color,
PQ_IP_VIP_IBC_SETTING_NUMS_Main_Color
} PQ_IP_VIP_IBC_SETTING_Group_Main_Color;

typedef enum
{
PQ_IP_VIP_Peaking_band_RF_NTSC_0_Main_Color,
PQ_IP_VIP_Peaking_band_RF_NTSC_1_Main_Color,
PQ_IP_VIP_Peaking_band_RF_NTSC_Main_Color,
PQ_IP_VIP_Peaking_band_RF_NTSC_3_Main_Color,
PQ_IP_VIP_Peaking_band_RF_NTSC_4_Main_Color,
PQ_IP_VIP_Peaking_band_RF_SECAM_Main_Color,
PQ_IP_VIP_Peaking_band_AV_NTSC_Main_Color,
PQ_IP_VIP_Peaking_band_AV_PAL_Main_Color,
PQ_IP_VIP_Peaking_band_AV_SECAM_Main_Color,
PQ_IP_VIP_Peaking_band_AV_1_Main_Color,
PQ_IP_VIP_Peaking_band_SV_NTSC_Main_Color,
PQ_IP_VIP_Peaking_band_480i_Main_Color,
PQ_IP_VIP_Peaking_band_480i_1_Main_Color,
PQ_IP_VIP_Peaking_band_720p_Main_Color,
PQ_IP_VIP_Peaking_band_1080i_Main_Color,
PQ_IP_VIP_Peaking_band_H_480i_Main_Color,
PQ_IP_VIP_Peaking_band_H_480p_Main_Color,
PQ_IP_VIP_Peaking_band_H_576i_Main_Color,
PQ_IP_VIP_Peaking_band_H_720p_Main_Color,
PQ_IP_VIP_Peaking_band_H_1080i_Main_Color,
PQ_IP_VIP_Peaking_band_H_1080i_P3D_Main_Color,
PQ_IP_VIP_Peaking_band_DT_MPEG2_480is_Main_Color,
PQ_IP_VIP_Peaking_band_DT_MPEG2_720p_Main_Color,
PQ_IP_VIP_Peaking_band_DT_MPEG2_1080i_Main_Color,
PQ_IP_VIP_Peaking_band_DT_H264_480is_Main_Color,
PQ_IP_VIP_Peaking_band_DT_H264_720p_Main_Color,
PQ_IP_VIP_Peaking_band_MM_photo_Main_Color,
PQ_IP_VIP_Peaking_band_MM_SD_Main_Color,
PQ_IP_VIP_Peaking_band_MM_HD_Main_Color,
PQ_IP_VIP_Peaking_band_PC_mode_Main_Color,
PQ_IP_VIP_Peaking_band_DTV_480i_Main_Color,
PQ_IP_VIP_Peaking_band_DT_MPEG2_720p_FBL_Main_Color,
PQ_IP_VIP_Peaking_band_DT_MPEG2_1080i_FBL_Main_Color,
PQ_IP_VIP_Peaking_band_4K2K_Main_Color,
PQ_IP_VIP_Peaking_band_4K2K_H_Main_Color,
PQ_IP_VIP_Peaking_band_NUMS_Main_Color
} PQ_IP_VIP_Peaking_band_Group_Main_Color;

typedef enum
{
PQ_IP_VIP_Peaking_Pcoring_S00_0_Main_Color,
PQ_IP_VIP_Peaking_Pcoring_S21_0_Main_Color,
PQ_IP_VIP_Peaking_Pcoring_S21_1_Main_Color,
PQ_IP_VIP_Peaking_Pcoring_S30_0_Main_Color,
PQ_IP_VIP_Peaking_Pcoring_S30_1_Main_Color,
PQ_IP_VIP_Peaking_Pcoring_S31_0_Main_Color,
PQ_IP_VIP_Peaking_Pcoring_S31_1_Main_Color,
PQ_IP_VIP_Peaking_Pcoring_S31_2_Main_Color,
PQ_IP_VIP_Peaking_Pcoring_S20_1_Main_Color,
PQ_IP_VIP_Peaking_Pcoring_S32_0_Main_Color,
PQ_IP_VIP_Peaking_Pcoring_S32_1_Main_Color,
PQ_IP_VIP_Peaking_Pcoring_S42_1_Main_Color,
PQ_IP_VIP_Peaking_Pcoring_S32_2_Main_Color,
PQ_IP_VIP_Peaking_Pcoring_S32_3_Main_Color,
PQ_IP_VIP_Peaking_Pcoring_S42_2_Main_Color,
PQ_IP_VIP_Peaking_Pcoring_S43_2_Main_Color,
PQ_IP_VIP_Peaking_Pcoring_NUMS_Main_Color
} PQ_IP_VIP_Peaking_Pcoring_Group_Main_Color;

extern code U8 MST_SkipRule_IP_Main_Color[PQ_IP_NUM_Main_Color];
extern code EN_IPTAB_INFO PQ_IPTAB_INFO_Main_Color[];
extern code U8 QMAP_1920_Main_Color[QM_INPUTTYPE_NUM_Main_Color][PQ_IP_NUM_Main_Color];

#endif
