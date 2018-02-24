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
// (MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef MSAPI_VIDEO_H
#define MSAPI_VIDEO_H

#include "drvMVOP.h"
#include "apiVDEC.h"

#ifdef MSAPI_VIDEO_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

#define ENABLE_VDEC_INFO_MONITOR     0

#define VIDEO_DEBUG 0//kk test default:0
#if VIDEO_DEBUG
#define SHOW_VIDEO_INFO(x)      \
{                               \
    printf("[Video]");          \
    printf x;                   \
    printf("\n");               \
}
#else
#define SHOW_VIDEO_INFO(x)
#endif


#define SHOW_VIDEO_ERR(x)       \
{                               \
    MS_DEBUG_MSG(printf("[Error][Video]"));   \
    MS_DEBUG_MSG(printf x);                   \
    MS_DEBUG_MSG(printf("\n"));               \
}

#define MSAPI_VID_PLAY              0 // Start decoding input buffer data and display the images
#define MSAPI_VID_PAUSE             1 // Stops the decoding process. The display will continue to show the last  picture.
#define MSAPI_VID_RESET             2 // The bit-stream buffer is flushed and the video decoder performs an internal reset.
#define MSAPI_VID_STOP              3 // Stops the decoding process.
#define MSAPI_VID_FREERUN           5 // Set MVD free run
#if (ENABLE_DMP || ENABLE_PVR)
#define MSAPI_VID_TRICK_PLAY        7 // Trick mode playback.
#define MSAPI_VID_STEP_PLAY         8 // Step Command
#define MSAPI_VID_PLAY_EXTENSION    9 // Play video widthout sequence start code.
#endif
#define MSAPI_VID_STEP_PLAY_EXTENSION    10 // Step Play video widthout sequence start code.

#define MSAPI_VID_RESUME            11 // Contunue play after pause command.

#define MVD_BITSTREAM_LEN_EX      (VDEC_BITSTREAM_LEN)

#if ( CHIP_SUPPORT_HEVC )//IMPLEMENT_DTV_H265
    #define IS_HVD_CODEC(codec) ((codec==E_VDEC_CODEC_TYPE_H264)||(codec==E_VDEC_CODEC_TYPE_AVS)||(codec==E_VDEC_CODEC_TYPE_HEVC))
#else
    #define IS_HVD_CODEC(codec) ((codec==E_VDEC_CODEC_TYPE_H264)||(codec==E_VDEC_CODEC_TYPE_AVS))
#endif
#define IS_MVD_CODEC(codec) ((codec==E_VDEC_CODEC_TYPE_MPEG2)||(codec==E_VDEC_CODEC_TYPE_MPEG4)||(codec==E_VDEC_CODEC_TYPE_VC1_ADV)||(codec==E_VDEC_CODEC_TYPE_VC1_MAIN))

typedef enum
{
    FORBIDDEN = 0,
    ASP_1TO1,       //    1 : 1
    ASP_4TO3,       //    4 : 3
    ASP_16TO9,      //   16 : 9
    ASP_221TO100,   // 2.21 : 1
    ASP_MAXNUM=15,
} ASPECT_RATIO_CODE;

/// Define MPEG video AFD (Active Format Description) information
typedef enum
{
    /// Unknow AFD.
    E_MVD_AFD_UNKNOWN           = 0,
    /// LetterBox 16:9, top posistion.
    E_MVD_AFD_BOX_16X9_TOP      = 2,
    /// LetterBox 14:9, top posistion.
    E_MVD_AFD_BOX_14X9_TOP      = 3,
    /// LetterBox 16:9, cnetre posistion.
    E_MVD_AFD_BOX_16X9          = 4,
    /// Full frame.
    E_MVD_AFD_FULL_FRAME        = 8,
    /// Centre 4:3
    E_MVD_AFD_CENTRE_4x3        = 9,
    /// Centre 16:9
    E_MVD_AFD_CENTRE_16X9       = 10,
    /// Centre 14:9
    E_MVD_AFD_CENTRE_14X9       = 11,
    /// 4:3 (with shoot and protect 14:9 centre).
    E_MVD_AFD_CENTRE_4X3_14X9   = 13,
    /// 16:9 (with shoot and protect 14:9 centre).
    E_MVD_AFD_CENTRE_16X9_14X9  = 14,
    /// 16:9 (with shoot and protect 4:3 centre).
    E_MVD_AFD_CENTRE_16X9_4X3   = 15
} MVD_AFD, *pMVD_AFD;

typedef enum
{
    MVD_FORBIDDEN=0,
    MVD_ASP_1TO1,       //    1 : 1
    MVD_ASP_4TO3,       //    4 : 3
    MVD_ASP_16TO9,      //   16 : 9
    MVD_ASP_221TO100,   // 2.21 : 1
    MVD_ASP_MAXNUM,
} MVD_ASPECT_RATIO_CODE;

/// Macrovision type
typedef enum
{
    EN_MACROVISION_COPY_PROTECTION_ENCODING_OFF   = 0x00,
    EN_MACROVISION_AGC_PROCESS_ON_SPLIT_BURST_OFF  = 0x01,
    EN_MACROVISION_AGC_PROCESS_ON_2_LINE_SPLIT_BURST_ON = 0x02,
    EN_MACROVISION_AGC_PROCESS_ON_4_LINE_SPLIT_BURST_ON = 0x03,
    EN_MACROVISION_INVALID        = 0xFF
} EN_MACROVISION;

#if ENABLE_FBL_ASPECT_RATIO_BY_MVOP
INTERFACE MS_U16 g_u16HorOffset;
INTERFACE MS_U16 g_u16VerOffset;
INTERFACE MS_BOOL g_bApplyMVOPCrop;
INTERFACE MS_WINDOW_TYPE g_tSrcWin;
INTERFACE MS_U16 g_u16StripSize;
#endif
INTERFACE MVOP_VIDEO_TYPE enMVOPVideoType;

INTERFACE VDEC_CodecType geVDEC_CodecType;
INTERFACE void msAPI_VID_SetMappingAVCParameter(VDEC_CodecType eVDEC_CodecType);
INTERFACE void msAPI_VID_SetCodecType(VDEC_CodecType eVDEC_CodecType);
INTERFACE VDEC_CodecType msAPI_VID_GetCodecType(void);
INTERFACE BOOLEAN msAPI_VID_Init(BOOLEAN bEnableDropErrFrame, VDEC_SrcMode enSrcMode);
INTERFACE VDEC_CodecType g_eCodecType;
INTERFACE void msAPI_VID_Command(U8 u8MVDCommand);
INTERFACE BOOLEAN msAPI_VID_GetVidInfo ( VDEC_DispInfo *pstVidStatus );
INTERFACE BOOLEAN msAPI_VID_SetMVDOutput ( INPUT_SOURCE_TYPE_t enInputSourceType,
                                           VDEC_DispInfo *pstVidStatus);
INTERFACE U8 msAPI_VID_IsSyncEnable(void);
INTERFACE U8 msAPI_VID_GetPlayMode(void);
INTERFACE U32 msAPI_VID_GetESWriteCnt(void);
INTERFACE BOOLEAN msAPI_VID_SetOutput(VDEC_DispInfo *pstVidStatus);
INTERFACE BOOLEAN msAPI_VID_AVCH264IsAspectRatioWide(VDEC_DispInfo *pstVidStatus, BOOLEAN *bResult);
INTERFACE BOOLEAN msAPI_VID_IsNeedFrameBufferLessMode(VDEC_DispInfo *pstVidStatus);

#if( CHIP_SUPPORT_HEVC )
INTERFACE BOOLEAN msAPI_VID_Is_CodecH265(void);
#endif

#if (ENABLE_DMP || ENABLE_PVR)
INTERFACE void msAPI_VID_SetTrickModeInfo(U8 u8DecodeType, U8 u8FrameDuration);
INTERFACE BOOLEAN msAPI_VID_MVDSetBuffAddr ( U32 u32BSstart, U32 u32BSend, U32 u32FrameAddr, U8 u8HdMode );
#endif

BOOLEAN msAPI_VID_Is_SrcOriginalInterlace(void);


#undef INTERFACE
#endif

