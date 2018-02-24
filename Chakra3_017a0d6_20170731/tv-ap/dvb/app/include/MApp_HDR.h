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
#ifndef _APP_HDR_H_
#define _APP_HDR_H_

#if (ENABLE_HDR)

#ifdef _APP_HDR_C_
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
//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
/// HDR level enum
typedef enum
{
    E_MAPI_XC_HDR_LOW,
    E_MAPI_XC_HDR_MIDDLE,
    E_MAPI_XC_HDR_HIGH,
    E_MAPI_XC_HDR_REF_MODE,
    E_MAPI_XC_HDR_MAX,
} E_MAPI_XC_HDR_LEVEL;


/// Dolby HDR mode.
typedef enum
{
    /// None mode
    E_MAPI_DOLBY_HDR_MODE_NONE,
    /// Vivid mode.
    E_MAPI_DOLBY_HDR_MODE_VIVID,
    ///brightness mode.
    E_MAPI_DOLBY_HDR_MODE_BRIGHTNESS,
    /// dark mode.
    E_MAPI_DOLBY_HDR_MODE_DARK,
    /// Max mode count.
    E_MAPI_DOLBY_HDR_MODE_MAX
} EN_MAPI_DOLBY_HDR_MODE;

#if (ENABLE_DOLBY_HDR)
/// Dolby HDR mode & 3D LUT table.
typedef struct
{
    /// Dolby HDR mode.
    EN_MAPI_DOLBY_HDR_MODE eMode;
    /// 3D LUT file path.
    String s3dLutPath;
    /// Specify 3D LUT have been load.
    BOOLEAN bCheckLoad;
    /// Specify 3D LUT data size.
    U32 u323dLutSize;
    /// 3D LUT data buffer.
    U8 *p3dLut;
} MAPI_DOLBY_HDR_MODE;
#endif

/// HDR setting.
typedef struct
{
    /// Open HDR on / off.
    BOOLEAN bOpenHdrOn;
    /// Open HDR auto detect level enable.
    BOOLEAN bOpenHdrAutoLevelEnable;
    /// Open HDR manual level.
    E_MAPI_XC_HDR_LEVEL eOpenHdrManualLevel;
    /// Dolby HDR on / off.
    BOOLEAN bDolbyHdrOn;
    /// Dolby HDR mode.
    EN_MAPI_DOLBY_HDR_MODE eDolbyHdrMode;
} ST_MAPI_HDR_SETTING;

/// HDR error code.
typedef enum{
    /// Success.
    E_MAPI_HDR_ERROR_SUCCESS,
    /// Undefined fail.
    E_MAPI_HDR_ERROR_UNDEFINED_FAIL,
    /// Driver doesn't support.
    E_MAPI_HDR_ERROR_DRIVER_NOT_SUPPORT,
    /// Driver still work.
    E_MAPI_HDR_ERROR_STILL_WORK,
    /// Input source doesn't support.
    E_MAPI_HDR_ERROR_INPUT_SOUCE_NOT_SUPPORT,
    /// HDR conflict.
    E_MAPI_HDR_CONFLICT,
} EN_MAPI_HDR_ERROR_CODE;

/// HDR level attributes.
typedef struct
{
    /// Is auto detect HDR level.
    BOOLEAN bAuto;
    /// Manual HDR level setting. Reference to E_MAPI_XC_HDR_LEVEL in mapi_syscfg_table.h
    U8 u8Level;
} ST_MAPI_HDR_LEVEL_ATTRIBUTES;

/// Dolby HDR mode.
typedef struct
{
    /// Dolby mode.
    U8 u8Mode;
    /// Get or set attribute error code. (Read only)
    EN_MAPI_HDR_ERROR_CODE eResult;
} ST_MAPI_DOLBY_HDR_MODE_ATTRIBUTES;

/// HDR setting attributes.
typedef struct
{
    /// Is Open / Dolby HDR video. If metadata is VUI/SEI/Dolby, this value set MAPI_TRUE, otherwise this value set MAPI_FALSE. (Read only)
    BOOLEAN bHdrVideo;
    /// Open / Dolby HDR on or off. This value means user set HDR on / off. (Read / Write)
    BOOLEAN bHdrOn;
    /// Is HDR HW working. (Read only)
    BOOLEAN bHdrHwWorking;
    union
    {
        /// Open HDR level. (Read / Write)
        ST_MAPI_HDR_LEVEL_ATTRIBUTES stHdrLevel;
        /// Dolby HDR mode. (Read / Write)
        ST_MAPI_DOLBY_HDR_MODE_ATTRIBUTES stMode;
    };
    /// Get or set attribute error code. (Read only)
    EN_MAPI_HDR_ERROR_CODE eResult;
} ST_MAPI_HDR_SETTING_ATTRIBUTES;

/// enum for HDR attributes.
typedef enum{
    /// Open HDR on / off attributes. Attribute data type is BOOL. (Get / Set)
    EN_MAPI_HDR_ONOFF_ATTRIBUTES,
    /// Open HDR init auto detect attributes. Attribute data type is ST_MAPI_HDR_LEVEL_ATTRIBUTES. (Set only)
    EN_MAPI_HDR_INIT_AUTO_DETECT_ATTRIBUTES,
    /// Open HDR level attributes. Attribute data type is ST_MAPI_HDR_LEVEL_ATTRIBUTES. (Get / Set)
    EN_MAPI_HDR_LEVEL_ATTRIBUTES,
    /// HDR video metadata type attributes. Attribute data type is U16. (Get only)
    EN_MAPI_HDR_TYPE_ATTRIBUTES,
    /// Dolby HDR mode attributes. Attribute data type is ST_MAPI_DOLBY_HDR_MODE_ATTRIBUTES. (Get / Set)
    EN_MAPI_HDR_DOLBY_MODE_ATTRIBUTES,
    /// Open HDR setting attributes. Attribute data type is ST_MAPI_HDR_SETTING_ATTRIBUTES. (Get / Set)
    EN_MAPI_HDR_OPEN_SETTING_ATTRIBUTES,
    /// Dolby HDR setting attributes. Attribute data type is ST_MAPI_HDR_SETTING_ATTRIBUTES. (Get / Set)
    EN_MAPI_HDR_DOLBY_SETTING_ATTRIBUTES,
    /// Dolby HDR on / off attributes. Attribute data type is BOOL. (Get only)
    EN_MAPI_HDR_DOLBY_ONOFF_ATTRIBUTES,
    /// HDR internal attribute that is used in Supernova.
    EN_MAPI_HDR_INTERNAL_ATTRIBUTES = 500,
    /// HDR video timing attributes. Attribute data type is EN_MAPI_TIMING. (Set only)
    EN_MAPI_HDR_VIDEO_TIMING_ATTRIBUTES = EN_MAPI_HDR_INTERNAL_ATTRIBUTES,
} EN_MAPI_HDR_ATTRIBUTES;

/// HDR setting enum
typedef enum
{
    /// HDR DLC setting, reference MAPI_HDR_CUSTOMER_DLC structure.
    E_MAPI_HDR_CUSTOMER_DLC_SETTING,
    /// HDR customer gamma table setting, reference MAPI_TIMING_GAMMA_TABLE_MAPPING structure.
    E_MAPI_HDR_CUSTOMER_GAMMA_TABLE_SETTING,
    /// HDR customer color primaries setting, reference MAPI_HDR_CUSTOMER_COLOR_PRIMARIES structure.
    E_MAPI_HDR_CUSTOMER_COLOR_PRIMARIES_SETTING,
    /// Dolby HDR default mode, reference EN_MAPI_DOLBY_HDR_MODE enum.
    E_MAPI_HDR_DEFAULT_DOLBY_MODE_SETTING,
    /// Dolby HDR Mode setting, reference MAPI_DOLBY_HDR_MODE structure.
    E_MAPI_HDR_DOLBY_MODE_SETTING,
    /// Open HDR tone mapping setting. reference MAPI_OPEN_HDR_TONE_MAPPING structure.
    E_MAPI_HDR_OPEN_TONE_MAPPING_SETTING
} E_MAPI_HDR_SETTING;

/// HDR customer DLC curve setting.
typedef struct
{
    U16   u16Timing;
    BOOL bFixDlcEnable;
    U8    u8FixDlcCurve[18];
} MAPI_HDR_CUSTOMER_DLC;

/// HDR customer color primaries setting.
typedef struct
{
    BOOL bCustomerEnable;
    U16 u16sWx;
    U16 u16sWy;
} MAPI_HDR_CUSTOMER_COLOR_PRIMARIES;

/// Gamma table setting.
typedef struct
{
    U16 u16Timing;
    U8 u8GammaTableIndex;
} MAPI_TIMING_GAMMA_TABLE_MAPPING;

/// Open HDR new TMO attribute
typedef struct
{
    /// Open HDR level.
    E_MAPI_XC_HDR_LEVEL eLevel;
    /// Soruce min ratio
    U16 u16SrcMinRatio;
    /// Source med ratio
    U16 u16SrcMedRatio;
    /// Source max ratio
    U16 u16SrcMaxRatio;

    /// Target min ratio
    U16 u16TgtMinRatio;
    /// Target med ratio
    U16 u16TgtMedRatio;
    /// Target max ratio
    U16 u16TgtMaxRatio;

    /// Front min slope
    U16 u16FrontSlopeMin;
    /// Front max slope
    U16 u16FrontSlopeMax;
    /// Back min slope
    U16 u16BackSlopeMin;
    /// Back max slope
    U16 u16BackSlopeMax;

    /// Scene change threshold
    U16 u16SceneChangeThrd;
    /// Scene change max ratio
    U16 u16SceneChangeRatioMax;
    /// IIR ratio
    U8 u8IIRRatio;

    /// TMO Target mode. default 0. 0 : keeps the value in initial function  1 : from output source
    U8 u8TMO_TargetMode;
    /// SDR panel gain
    U16 u16SDRPanelGain;
} MAPI_OPEN_HDR_TONE_MAPPING;

/// HDR level attributes
typedef struct
{
    U16 u16Smin;
    U16 u16Smed;
    U16 u16Smax;
    U16 u16Tmin;
    U16 u16Tmed;
    U16 u16Tmax;
    U16 u16MidSourceOffset;
    U16 u16MidTargetOffset;
    U16 u16MidSourceRatio;
    U16 u16MidTargetRatio;
} MAPI_XC_HDR_LEVEL_ATTRIBUTES;
#if (ENABLE_DOLBY_HDR)
/// Dolby global dimming attributes.
typedef struct
{
    /// dolby global dimming on/off
    BOOL bGlobalDimming;
    /// dolby global delay frame count
    S8 s8DelayFrame;
} ST_MAPI_DOLBY_HDR_GLOBAL_DIMMING_ATTRIBUTES;
#endif

/// CFD attribute
typedef struct
{
    /// Color attribute
    /// Panel Rx
    U16 u16tRx;
    /// Panel Ry
    U16 u16tRy;
    /// Panel Gx
    U16 u16tGx;
    /// Panel Gy
    U16 u16tGy;
    /// Panel Bx
    U16 u16tBx;
    /// Panel By
    U16 u16tBy;
    /// Panel Wx
    U16 u16tWx;
    /// Panel Wy
    U16 u16tWy;
    /// Panel max luminance
    U16 u16MaxLuminance;
    /// Panel med luminance
    U16 u16MedLuminance;
    /// Panel min luminance
    U16 u16MinLuminance;
    /// Panel color format, BT.601/BT.709/BT.2020/....
    U8 u8ColorFormat;
    /// Panel color data format, RGB/YUV422/YUV444/YUV420
    U8 u8ColorDataFormat;
    /// Panel Full range
    BOOL bIsFullRange;
    /// Linear RGB
    BOOL bLinearRgb;
    /// Customer color primaries
    BOOL bCustomerColorPrimaries;
    /// Source white x
    U16 u16SourceWx;
    /// Source white y
    U16 u16SourceWy;
} ST_MAPI_PANEL_CFD_ATTRIBUTE;

typedef struct
{
    //int length;
    char *PanelAttr;
    // Panel DCLK (U16 data type), used to break DCLK up bound 255.
    U16 u16PanelMaxDCLK;
    U16 u16PanelDCLK;
    U16 u16PanelMinDCLK;
    // Panel ext type, used to record ext panel type, for example: Vx1.
    U16 u16PanelLinkExtType;

    /// CFD attribute
    ST_MAPI_PANEL_CFD_ATTRIBUTE stCfdAttribute;
} PanelInfo_t;

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
INTERFACE BOOLEAN MApp_GetAutoDetectHdrLevel(SCALER_WIN enWin);
INTERFACE BOOLEAN MApp_SetAutoDetectHdrLevel(BOOLEAN bAuto, SCALER_WIN enWin, E_MAPI_XC_HDR_LEVEL enAutoHdrLevel);
INTERFACE E_MAPI_XC_HDR_LEVEL MApp_GetHdrLevel(SCALER_WIN enWin);
INTERFACE BOOLEAN MApp_IsSupportHdr(void);
INTERFACE BOOLEAN MApp_InitHdrAttributes(EN_MAPI_HDR_ATTRIBUTES enAttribueType, SCALER_WIN enWin, void *pAttributes, U16 u16AttributesSize);
#if (ENABLE_DOLBY_HDR)
INTERFACE EN_MAPI_HDR_ERROR_CODE MApp_GetDolbyHdrMode(EN_MAPI_DOLBY_HDR_MODE *peMode, SCALER_WIN enWin);
INTERFACE EN_MAPI_HDR_ERROR_CODE MApp_SetDolbyHdrMode(EN_MAPI_DOLBY_HDR_MODE eMode, SCALER_WIN enWin);
INTERFACE BOOLEAN MApp_IsDolbyHdrVideo(void);
#endif
INTERFACE BOOLEAN MApp_IsOpenHdrVideo(void);
INTERFACE BOOLEAN MApp_IsHlgHdrVideo(void);
INTERFACE BOOLEAN MApp_IsHdrWorking(void);
INTERFACE BOOLEAN MApp_GetHdrOnOff(void);
INTERFACE BOOLEAN MApp_GetDolbyHdrOnOff(void);
INTERFACE BOOLEAN MApp_SetHdrLevel(E_MAPI_XC_HDR_LEVEL enHdrLevel, SCALER_WIN enWin);

INTERFACE BOOLEAN MApp_GetHdrSetting(E_MAPI_HDR_SETTING eType, void *pSetting, U16 u16SettingSize);
INTERFACE BOOLEAN MApp_GetHdrLevelAttribues(E_MAPI_XC_HDR_LEVEL enHdrLevel, MAPI_XC_HDR_LEVEL_ATTRIBUTES *pAttribues);
INTERFACE BOOLEAN MApp_GetHlgLevelAttributes(E_MAPI_XC_HDR_LEVEL enHlgLevel, MAPI_XC_HDR_LEVEL_ATTRIBUTES *pAttributes);
INTERFACE BOOLEAN MApp_GetHdrCustomerDlcSetting(MAPI_HDR_CUSTOMER_DLC *pstHdrDlc);
INTERFACE BOOLEAN MApp_GetHdrCustomerGammaTableSetting(MAPI_TIMING_GAMMA_TABLE_MAPPING *pstHdrGammaTable);
INTERFACE void MApp_LoadHdrLevelAttributes(MAPI_XC_HDR_LEVEL_ATTRIBUTES stHdrLevelAttributes[E_MAPI_XC_HDR_MAX], MAPI_XC_HDR_LEVEL_ATTRIBUTES stHlgLevelAttributes[E_MAPI_XC_HDR_MAX]);
INTERFACE void MApp_LoadHdrToneMappingAttributes(MAPI_OPEN_HDR_TONE_MAPPING stToneMapping[E_MAPI_XC_HDR_MAX]);
INTERFACE BOOLEAN MApp_LoadHdrCustomerDlcAttributes(U8 u8ResType, MAPI_HDR_CUSTOMER_DLC *pstHdrDlc);
INTERFACE BOOLEAN MApp_LoadHdrCustomerGammaTableAttributes(U8 u8ResType, MAPI_TIMING_GAMMA_TABLE_MAPPING *pstHdrCustomerGammaTable);
INTERFACE EN_MS_HDR MApp_GetHDRUserSetting(void);
INTERFACE void MApp_HDR_Handler(void);
INTERFACE void MApp_AutoDownload_Config(void);
INTERFACE BOOLEAN MApp_HDR_Init(void);

#undef INTERFACE
#endif
#endif /* _APP_HDR_H_ */
