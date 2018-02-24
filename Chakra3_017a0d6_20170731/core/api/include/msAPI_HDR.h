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
// Copyright (c) 2006-2007 MStar Semiconductor, Inc.
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
#ifndef MSAPI_HDR_H_
#define MSAPI_HDR_H_

#if (ENABLE_HDR)

#include "drvXC_HDMI_if.h"

#ifdef MSAPI_HDR_C_
#define INTERFACE
#else
#define INTERFACE extern
#endif

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
///////////////////////////
// HDR metadata type define
/// HDR metadata none type.
#define HDR_METATYPE_NONE 0x0000
/// HDR metadata MPEG VUI type. Document : JCTVC-P1005_v1_Annex_E_changes_for_Q0084_r1
#define HDR_METATYPE_MPEG_VUI 0x0001
/// HDR metadata MPEG SEI Tone mapping type. Document : w14700 SEI - D.2.15 : Tone mapping information SEI message syntax
#define HDR_METADATA_MPEG_SEI_TONE_MAPPING 0x0002
/// HDR metadata MPEG SEI mastering color volume type. Document : w14700 SEI - D.2.27 : Mastering display colour volume SEI message syntax
#define HDR_METADATA_MPEG_SEI_MASTERING_COLOR_VOLUME 0x0004
/// HDR metadata MPEG SEI Knee function type. Document : w14700 SEI - D.2.31 : Knee function information SEI message syntax
#define HDR_METADATA_MPEG_SEI_KNEE_FUNCTION 0x0008
/// HDR metadata HDMI infoframe type. Document : CEA-861.3_V16BallotDraft
#define HDR_METADATA_HDMI_INFOFRAME 0x0010
/// Dolby HDR metadata
#define HDR_METADATA_DOLBY_HDR 0x0020
/// HDR metadata SEI content light level info type
#define HDR_METADATA_SEI_CONTENT_LIGHT_LEVEL 0x0040

/// enum for event.
typedef enum
{
    /// Conflict event.
    E_MAPI_EVENT_CONFLICT,
    /// Video status event.
    E_MAPI_EVENT_VIDEO_STATUS,
    /// HDR UI status event.
    E_MAPI_EVENT_HDR_STATUS
} EN_MAPI_EVENT;

/// call back function
typedef  BOOL (*pfnEvent)(void *pObj, EN_MAPI_EVENT eEvent, U32 u32Ext1, U32 u32Ext2, U32 u32Ext3);
//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
/// enum for video status event.
typedef enum
{
    /// HDR is stop.
    E_MAPI_VIDEO_HDR_STOP,
    /// Open HDR is running.
    E_MAPI_VIDEO_OPEN_HDR_RUNNING,
    /// Dolby HDR is running..
    E_MAPI_VIDEO_DOLBY_HDR_RUNNING,
} EN_MAPI_VIDEO_STATUS;

/// the timing
typedef enum
{
    /// Default
    E_MAPI_TIMING_DEFAULT = 0,

    /// 480 timing enum start
    E_MAPI_TIMING_480 = 0x0100,
    /// 480@60P timing parameter
    E_MAPI_TIMING_480P_60,
    /// 480@60I timing parameter
    E_MAPI_TIMING_480I_60,
    /// 480 timing enum end
    E_MAPI_TIMING_480_MAX,

    /// 576 timing enum start
    E_MAPI_TIMING_576 = 0x0200,
    /// 576@50P timing parameter
    E_MAPI_TIMING_576P_50,
    /// 576@50I timing parameter
    E_MAPI_TIMING_576I_50,
    /// 576 timing enum end
    E_MAPI_TIMING_576_MAX,

    /// 720 timing enum start
    E_MAPI_TIMING_720 = 0x0300,
    /// 720@60P timing parameter
    E_MAPI_TIMING_720P_60,
    /// 720@50P timing parameter
    E_MAPI_TIMING_720P_50,
    /// 720 timing enum end
    E_MAPI_TIMING_720_MAX,

    /// 1440 timing enum start
    E_MAPI_TIMING_1440 = 0x0400,
    /// 1440@50P timing parameter
    E_MAPI_TIMING_1440P_50,
    /// 1440 timing enum end
    E_MAPI_TIMING_1440_MAX,

    /// 1470 timing enum start
    E_MAPI_TIMING_1470 = 0x0500,
    /// 1470@60P timing parameter
    E_MAPI_TIMING_1470P_60,
    /// 1470@30P timing parameter
    E_MAPI_TIMING_1470P_30,
    /// 1470@24P timing parameter
    E_MAPI_TIMING_1470P_24,
    /// 1470 timing enum end
    E_MAPI_TIMING_1470_MAX,

    /// 1080 timing enum start
    E_MAPI_TIMING_2K1K = 0x0600,
    /// 1080@60P timing parameter
    E_MAPI_TIMING_2K1KP_60,
    /// 1080@60I timing parameter
    E_MAPI_TIMING_2K1KI_60,
    /// 1080@50P timing parameter
    E_MAPI_TIMING_2K1KP_50,
    /// 1080@50I timing parameter
    E_MAPI_TIMING_2K1KI_50,
    /// 1080@30P timing parameter
    E_MAPI_TIMING_2K1KP_30,
    /// 1080@25P timing parameter
    E_MAPI_TIMING_2K1KP_25,
    /// 1080@24P timing parameter
    E_MAPI_TIMING_2K1KP_24,
    /// 1080 timing enum end
    E_MAPI_TIMING_2K1K_MAX,

    /// 2K2K timing enum start
    E_MAPI_TIMING_2K2K = 0x0700,
    /// 2K2K@60P timing parameter
    E_MAPI_TIMING_2K2KP_60,
    /// 2K2K@30P timing parameter
    E_MAPI_TIMING_2K2KP_30,
    /// 2K2K@25P timing parameter
    E_MAPI_TIMING_2K2KP_25,
    /// 2K2K@24P timing parameter
    E_MAPI_TIMING_2K2KP_24,
    /// 2K2K timing enum end
    E_MAPI_TIMING_2K2K_MAX,

    /// 4K0.5K timing enum, horizontal 1K = 960, vertical 1K = 1080
    E_MAPI_TIMING_4K540 = 0x0800,
    /// 4k0.5K@240P timing enum
    E_MAPI_TIMING_4K540P_240,
    /// 4k0.5K timing enum end
    E_MAPI_TIMING_4K540_MAX,

    /// 4K1K timing enum start
    E_MAPI_TIMING_4K1K = 0x0900,
    /// 4K1K@60P timing parameter
    E_MAPI_TIMING_4K1KP_120,
    /// 4K1K@60P timing parameter
    E_MAPI_TIMING_4K1KP_60,
    /// 4K1K@30P timing parameter
    E_MAPI_TIMING_4K1KP_30,
    /// 4K1K timing enum end
    E_MAPI_TIMING_4K1K_MAX,

    /// 4K2K timing enum start
    E_MAPI_TIMING_4K2K = 0x0a00,
    /// 4K2K@60P timing parameter
    E_MAPI_TIMING_4K2KP_60,
    /// 4K2K@50P timing parameter
    E_MAPI_TIMING_4K2KP_50,
    /// 4K2K@30P timing parameter
    E_MAPI_TIMING_4K2KP_30,
    /// 4K2K@25P timing parameter
    E_MAPI_TIMING_4K2KP_25,
    /// 4K2K@24P timing parameter
    E_MAPI_TIMING_4K2KP_24,
    /// 4K2K timing enum end
    E_MAPI_TIMING_4K2K_MAX,

    /// 4K2K timing enum start
    E_MAPI_TIMING_4096x2160 = 0x0b00,
    /// 4096X20160@24P timing parameter
    E_MAPI_TIMING_4096x2160P_24,
    /// 4096X20160 timing enum end
    E_MAPI_TIMING_4096x2160_MAX,

    /// Maximum value of this enum
    E_MAPI_TIMING_MAX = 0x0c00,

    /// Undefined.
    E_MAPI_TIMING_UNDEFINED = E_MAPI_TIMING_MAX
} EN_MAPI_TIMING;

///////////////////////////////
// HDR metadata structure
/// Document : JCTVC-P1005_v1_Annex_E_changes_for_Q0084_r1
typedef struct
{
    U8 u8ColorPrimaries;
    U8 u8TransferCharacteristics;
    U8 u8MatrixCoefficients;
} ST_MAPI_HDR_METADATA_MPEG_VUI;

/// Document : w14700 SEI - D.2.15 : Tone mapping information SEI message syntax
typedef struct
{
    U8      u8ToneMapId;
    BOOL   bToneMapCancelFlag;
    BOOL   bToneMapPersistenceFlag;
    U8      u8CodedDataBitDepth;
    U8      u8TargetBitDepth;
    U8      u8ToneMapModelId;
    U32    u32MinValue;
    U32    u32MaxValue;
    U32    u32SigmoidMidpoint;
    U32    u32SigmoidWidth;
    U16*   pu16StartOfCodedInterval; /// array size = (1 << target_bit_depth)
    U16     u16NumPivots;
    U16*   pu16CodedPivotValue;  /// array size = num_pivots
    U16*   pu16TargetPivotValue; /// array size = num_pivots
    U8       u8CameraIsoSpeedIdc;
    U32     u32CameraIsoSpeedValue;
    U8       u8ExposureIndexIdc;
    U32     u32ExposureIndexValue;
    BOOL   bExposureCompensationValueSignFlag;
    U16     u16ExposureCompensationValueNumerator;
    U16     u16ExposureCompensationValueDenomIdc;
    U32     u32RefScreenLuminanceWhite;
    U32     u32ExtendedRangeWhiteLevel;
    U16     u16NominalBlackLevelCodeValue;
    U16     u16NominalWhiteLevelCodeValue;
    U16     u16ExtendedWhiteLevelCodeValue;
} ST_MAPI_HDR_METADATA_MPEG_SEI_TONE_MAPPING;

/// Document : w14700 SEI - D.2.27 : Mastering display colour volume SEI message syntax
typedef struct
{
    U16     u16DisplayPrimariesX[3];
    U16     u16DisplayPrimariesY[3];
    U16     u16WhitePointX;
    U16     u16WhitePointY;
    U32     u32MaxDisplayMasteringLuminance;
    U32     u32MinDisplayMasteringLuminance;
} ST_MAPI_HDR_METADATA_MPEG_SEI_MASTERING_COLOR_VOLUME;

/// Document : w14700 SEI - D.2.31 : Knee function information SEI message syntax
typedef struct
{
    U8      u8KneeFunctionId;
    BOOL   bKneeFunctionCancelFlag;
    BOOL   bKneeFunctionPersistenceFlag;
    U32     u32InputDRange;
    U32     u32InputDispLuminance;
    U32     u32OutputDRange;
    U32     u32OutputDispLuminance;
    U16     u16NumKneePointsMinus1; /// num_knee_points_minus1 shall be in the range of 0 to 998, inclusive.
    U16*    pu16InputKneePoint; /// array size = num_knee_points_minus1+1
    U16*    pu16OutputKneePoint; /// array size = num_knee_points_minus1+1
} ST_MAPI_HDR_METADATA_MPEG_SEI_KNEE_FUNCTION;

/// Document : CEA-861.3_V16BallotDraft
typedef struct
{
    U8      u8EOTF; /// 0:SDR gamma, 1:HDR gamma, 2:SMPTE ST2084, 3:Future EOTF, 4-7:Reserved
    U8      u8StaticMetadataID; /// 0: Static Metadata Type 1, 1-7:Reserved for future use
    U16     u16Rx; /// display primaries Rx
    U16     u16Ry; /// display primaries Ry
    U16     u16Gx; /// display primaries Gx
    U16     u16Gy; /// display primaries Gy
    U16     u16Bx; /// display primaries Bx
    U16     u16By; /// display primaries By
    U16     u16Wx; /// display primaries Wx
    U16     u16Wy; /// display primaries Wy
    U16     u16Lmax; /// max display mastering luminance
    U16     u16Lmin; /// min display mastering luminance
    U16     u16MaxCLL; /// maximum content light level
    U16     u16MaxFALL; /// maximum frame-average light level
} ST_MAPI_HDR_METADATA_HDMI_INFOFRAME;

/// Avi information packet
typedef struct
{
    /// Pixel Format
    U8 PixelFormat;
    /// Color imetry
    U8 Colorimetry;
    /// Extended Color imetry
    U8 ExtendedColorimetry;
    /// Rgb Quantization Range
    U8 RgbQuantizationRange;
    /// Ycc Quantization Range
    U8 YccQuantizationRange;
    ///Static Metadata Descriptor ID
    U8 StaticMetadataDescriptorID;
} ST_MAPI_HDR_HDMIAVI_INFOFRAME;

/// SEI content light level info
typedef struct
{
    /// Used
    BOOL bUsed;
    /// Content light level enabled
    BOOL bContentLightLevelEnabled;
    /// Max content light level
    U16 u16MaxContentLightLevel;
    /// Max picture average light level
    U16 u16MaxPicAverageLightLevel;
} ST_MAPI_HDR_METADATA_SEI_CONTENT_LIGHT_LEVEL;

/// HDR Metadata.
typedef struct
{
    /// HDR Metadata type
    U16 u16HDRMetadataType;
    /// HDR Metadata Mpeg VUI
    ST_MAPI_HDR_METADATA_MPEG_VUI stHdrMetadataMpegVUI;
    /// MPEG SEI tone mapping metadata
    ST_MAPI_HDR_METADATA_MPEG_SEI_TONE_MAPPING stHdrMetadataMpegSEIToneMapping;
    /// MPEG SEI mastering color volume metadata
    ST_MAPI_HDR_METADATA_MPEG_SEI_MASTERING_COLOR_VOLUME stHdrMetadataMpegSEIMasteringColorVolume;
    /// MPEG SEI Knee Function metadata
    ST_MAPI_HDR_METADATA_MPEG_SEI_KNEE_FUNCTION stHdrMetadataMpegSEIKneeFunction;
    /// HDMI HDR infoframe
    ST_MAPI_HDR_METADATA_HDMI_INFOFRAME stHdrMetadataHdmiInfoframe;
    /// HDMI AVI infoframe
    ST_MAPI_HDR_HDMIAVI_INFOFRAME stHdrHdmiAviInfoframe;
    /// SEI content light level
    ST_MAPI_HDR_METADATA_SEI_CONTENT_LIGHT_LEVEL stHdrMetadataSeiContentLightLevel;
} ST_MAPI_HDR_METADATA;



//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
INTERFACE BOOLEAN msAPI_GetHdrAttributes(EN_MAPI_HDR_ATTRIBUTES enAttribueType, void *pAttributes, U16 u16AttributesSize);
INTERFACE BOOLEAN msAPI_IsHdrEnable(SCALER_WIN enWin);
INTERFACE BOOLEAN msAPI_RefreshHdrSetting(void);
INTERFACE BOOLEAN msAPI_SetHdrAttributes(EN_MAPI_HDR_ATTRIBUTES enAttribueType, void *pAttributes, U16 u16AttributesSize);
INTERFACE BOOLEAN msAPI_CheckHdrExtraCondition(SCALER_WIN enWin);
INTERFACE U16 msAPI_GetVideoHdrType(void);
INTERFACE U16 msAPI_GetVideoHdrType(void);
INTERFACE EN_MAPI_HDR_ERROR_CODE msAPI_SetDolbyHdrOn(BOOLEAN bHdrOn);
INTERFACE BOOLEAN msAPI_SetHdrOnOff(BOOLEAN bOn);
INTERFACE BOOLEAN msAPI_SetHDRMode(PQ_WIN eWindow, MS_U16 u16GRuleLevelIndex);
INTERFACE BOOLEAN msAPI_GetHDMIMode(void);
INTERFACE EN_MAPI_HDR_ERROR_CODE msAPI_LoadHdrMetadataByHdrIp(void);
INTERFACE PQ_INPUT_SOURCE_TYPE msAPI_SDK2PQInputSourcTypeTrans(INPUT_SOURCE_TYPE_t enApiInputSourceType);
INTERFACE BOOLEAN msAPI_FireCfd(void);
INTERFACE BOOLEAN msAPI_HDR_GetHDRMetaData(sHDR_METADATA *pstHDRMetadata);
INTERFACE BOOLEAN msAPI_SetHdmiCfd(SCALER_WIN eWindow);

#undef INTERFACE
#endif
#endif /* MSAPI_HDR_H_ */
