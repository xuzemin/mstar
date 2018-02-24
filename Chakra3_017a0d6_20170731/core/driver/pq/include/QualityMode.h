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


#define QM_IsSourceVGA(x)               ((x)==PQ_INPUT_SOURCE_VGA)
#define QM_IsSourceHDMI(x)              ((x)==PQ_INPUT_SOURCE_HDMI)
#define QM_IsSourceDVI_HDMIPC(x,y)      (QM_IsSourceHDMI(x) && (_stHDMI_Info[y].bIsHDMI == FALSE))
#define QM_IsSourceHDMI_Video(x,y)      (QM_IsSourceHDMI(x) && (_stHDMI_Info[y].bIsHDMI == TRUE) && (_stHDMI_Info[y].bIsHDMIPC == FALSE))
#define QM_IsSourceHDMI_PC(x,y)         (QM_IsSourceHDMI(x) && (_stHDMI_Info[y].bIsHDMI == TRUE) && (_stHDMI_Info[y].bIsHDMIPC == TRUE))

#define QM_HDMIPC_COLORRGB(x)           (_stHDMI_Info[x].enColorFmt == PQ_HDMI_COLOR_RGB)
#define QM_HDMIPC_COLORYUV420(x)        (_stHDMI_Info[x].enColorFmt == PQ_HDMI_COLOR_YUV_420)
#define QM_HDMIPC_COLORYUV422(x)        (_stHDMI_Info[x].enColorFmt == PQ_HDMI_COLOR_YUV_422)
#define QM_HDMIPC_COLORYUV444(x)        (_stHDMI_Info[x].enColorFmt == PQ_HDMI_COLOR_YUV_444)

#define QM_IsSourceYPbPr(x)             ((x)==PQ_INPUT_SOURCE_YPBPR)

#define QM_IsSourceYPbPrSD(x,y)         (QM_IsSourceYPbPr(x)                        \
                                        && ( _u8ModeIndex[y] == PQ_MD_720x480_60I   \
                                           ||_u8ModeIndex[y] == PQ_MD_720x480_60P   \
                                           ||_u8ModeIndex[y] == PQ_MD_720x576_50I   \
                                           ||_u8ModeIndex[y] == PQ_MD_720x576_50P) )

#define QM_IsSourceDTV(x)               ((x)==PQ_INPUT_SOURCE_DTV)
#define QM_IsSourceMultiMedia(x) (((x)>=PQ_INPUT_SOURCE_STORAGE) && ((x)<=PQ_INPUT_SOURCE_JPEG))

#define QM_IsMultiMediaMOVIE(x)         (_stMultiMedia_Info[x].eType == E_PQ_MULTIMEDIA_MOVIE)
#define QM_IsMultiMediaPHOTO(x)         (_stMultiMedia_Info[x].eType == E_PQ_MULTIMEDIA_PHOTO)

#define QM_IsDTV_MPEG2(x)               (_stDTV_Info[x].eType == E_PQ_DTV_MPEG2)
#define QM_IsDTV_H264(x)                (_stDTV_Info[x].eType == E_PQ_DTV_H264)
#define QM_IsDTV_H265(x)                (_stDTV_Info[x].eType == E_PQ_DTV_H265)

#define QM_IsDTV_IFRAME(x)              (_stDTV_Info[x].eType == E_PQ_DTV_IFRAME)

#define QM_IsSourceScartRGB(x,y)   (((x)==PQ_INPUT_SOURCE_SCART) && (_stVD_Info[y].bIsSCART_RGB == TRUE))
#define QM_IsSourceScartCVBS(x,y)  (((x)==PQ_INPUT_SOURCE_SCART) && (_stVD_Info[y].bIsSCART_RGB == FALSE))
#define QM_IsSourceScart(x)             ((x)==PQ_INPUT_SOURCE_SCART)
#define QM_IsSourceATV(x)               ((x)==PQ_INPUT_SOURCE_TV)
#define QM_IsSourceSV(x)                ((x)==PQ_INPUT_SOURCE_SVIDEO)
#define QM_IsSourceAV(x)                ((x)==PQ_INPUT_SOURCE_CVBS)
#define QM_IsSourceVD(x)                (  QM_IsSourceATV(x)    \
                                        || QM_IsSourceAV(x)     \
                                        || QM_IsSourceSV(x)     \
                                        || QM_IsSourceScart(x) )

#define QM_Is3DVideo()           (_gIs3D_En == TRUE)

#define QM_FRONTEND_RFIN(x)             (!_stVD_Info[x].bIsVIFIN)
#define QM_FRONTEND_VIFIN(x)            (_stVD_Info[x].bIsVIFIN)

#define QM_GetInputHSize(x)             (_stMode_Info[x].u16input_hsize)
#define QM_GetInputVSize(x)             (_stMode_Info[x].u16input_vsize)

#define QM_H_Size_Check_x1(x, y)        ( ((x) < ((y)*1+50)) &&  ((x) > ((y)*1-50)) )
#define QM_H_Size_Check_x2(x, y)        ( ((x) < ((y)*2+50)) &&  ((x) > ((y)*2-50)) )
#define QM_H_Size_Check_x4(x, y)        ( ((x) < ((y)*4+50)) &&  ((x) > ((y)*4-50)) )
#define QM_H_Size_Check_x8(x, y)        ( ((x) < ((y)*8+50)) &&  ((x) > ((y)*8-50)) )

#define QM_IsYPbPr_720x480_60I(x)       (_u8ModeIndex[x] == PQ_MD_720x480_60I)
#define QM_IsYPbPr_720x480_60P(x)       (_u8ModeIndex[x] == PQ_MD_720x480_60P)
#define QM_IsYPbPr_720x576_50I(x)       (_u8ModeIndex[x] == PQ_MD_720x576_50I)
#define QM_IsYPbPr_720x576_50P(x)       (_u8ModeIndex[x] == PQ_MD_720x576_50P)
#define QM_IsYPbPr_1280x720_50P(x)      (_u8ModeIndex[x] == PQ_MD_1280x720_50P)
#define QM_IsYPbPr_1280x720_60P(x)      (_u8ModeIndex[x] == PQ_MD_1280x720_60P)
#define QM_IsYPbPr_1920x1080_50I(x)     (_u8ModeIndex[x] == PQ_MD_1920x1080_50I)
#define QM_IsYPbPr_1920x1080_60I(x)     (_u8ModeIndex[x] == PQ_MD_1920x1080_60I)

#define QM_IsYPbPr_1920x1080_24P(x)     (_u8ModeIndex[x] == PQ_MD_1920x1080_24P)
#define QM_IsYPbPr_1920x1080_25P(x)     (_u8ModeIndex[x] == PQ_MD_1920x1080_25P)
#define QM_IsYPbPr_1920x1080_30P(x)     (_u8ModeIndex[x] == PQ_MD_1920x1080_30P)
#define QM_IsYPbPr_1920x1080_50P(x)     (_u8ModeIndex[x] == PQ_MD_1920x1080_50P)
#define QM_IsYPbPr_1920x1080_60P(x)     (_u8ModeIndex[x] == PQ_MD_1920x1080_60P)

#define QM_GetInputVFreq(x)             (_stMode_Info[x].u16input_vfreq)
#define QM_IsInterlaced(x)              (_stMode_Info[x].bInterlace)

#define QM_GetDispHSize(x)              (_stMode_Info[x].u16display_hsize)
#define QM_GetDispVSize(x)              (_stMode_Info[x].u16display_vsize)

#define QM_GetATVStandard(x)            (_stVD_Info[x].enVideoStandard)

