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
/// @file    drvPQ.h
/// @brief  PQ interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRVPQ_H_
#define _DRVPQ_H_

#define ENABLE_DEBUG_FILM   0

#include "apiXC.h"

#ifdef __cplusplus
extern "C"
{
#endif

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------

#define MSIF_PQ_TAG                    {'M','S','I','F'}                   // MSIF
#define MSIF_PQ_CLASS                  {'0','0'}                           // DRV/API (DDI)
#define MSIF_PQ_CUS                    0x0000                              // MStar Common library
#define MSIF_PQ_MOD                    0x0000                              // MStar Common library
#define MSIF_PQ_CHIP                   0x0000
#define MSIF_PQ_CPU                    '0'
#define MSIF_PQ_OS                     '0'

//  library information

/// the PQ lib code
#define MSIF_PQ_LIB_CODE               {'P','Q','_','_'}
/// the PQ lib version
#define MSIF_PQ_LIBVER                 {'0','0'}
/// the PQ build number
#define MSIF_PQ_BUILDNUM               {'0','7'}
/// the PQ CL
#define MSIF_PQ_CHANGELIST             {'0','0','3','5','3','5','7','6'}

/// the PQ driver version
#define PQ_DRV_VERSION /* Character String for DRV/API version */  \
    MSIF_PQ_TAG,          /* 'MSIF'                               */  \
    MSIF_PQ_CLASS,        /* '00'                                 */  \
    MSIF_PQ_CUS,          /* 0x0000                               */  \
    MSIF_PQ_MOD,          /* 0x0000                               */  \
    MSIF_PQ_CHIP,                                                     \
    MSIF_PQ_CPU,                                                      \
    MSIF_PQ_LIB_CODE  , /* IP__                                */  \
    MSIF_PQ_LIBVER    , /* 0.0 ~ Z.Z                           */  \
    MSIF_PQ_BUILDNUM  , /* 00 ~ 99                             */  \
    MSIF_PQ_CHANGELIST, /* CL#                                 */  \
    MSIF_PQ_OS
//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------

#define ENABLE_PQ_LOAD_TABLE_INFO   0   ///<Pr init PQ load table info

#ifndef QMAP_ONLY_SUPPORT_ONE_PANEL
  #if( MEMORY_MAP <= MMAP_32MB )
    #define QMAP_ONLY_SUPPORT_ONE_PANEL 1
  #else
    #define QMAP_ONLY_SUPPORT_ONE_PANEL 0
  #endif
#endif


#define PQ_SUPPORT_4K_PANEL   SUPPORT_4K2K_OUTPUT


#ifndef PQ_VGASubCaseForceTo422Mode
#define PQ_VGASubCaseForceTo422Mode        0
#endif

#define PQ_REG_READ_FUNC( u32Reg)    MApi_XC_ReadByte( u32Reg )
#define PQ_REG_FUNC( u32Reg, u8Value, u8Mask )    MApi_XC_WriteByteMask( u32Reg, u8Value, u8Mask )
#define PQ_REG_MLOAD_FUNC(u32Reg,u8Value,u8Mask) \
    do{ \
        if(u32Reg%2) \
        { \
            MApi_XC_MLoad_WriteCmd_And_Fire(u32Reg-1, ((MS_U16)u8Value)<<8, ((MS_U16)u8Mask)<<8); \
        } \
        else \
        { \
            MApi_XC_MLoad_WriteCmd_And_Fire(u32Reg, u8Value, u8Mask); \
        } \
    }while(0)

#define PQ_REG_MLOAD_WRITE_CMD(u32Reg,u8Value,u8Mask) \
    do{ \
        if(u32Reg%2) \
        { \
            _u32MLoadCmd[_u16MLoadCmdCnt] = u32Reg-1; \
            _u16MLoadMsk[_u16MLoadCmdCnt] = ((MS_U16)u8Mask)<<8; \
            _u16MLoadVal[_u16MLoadCmdCnt] = ((MS_U16)u8Value)<<8; \
        } \
        else \
        { \
            _u32MLoadCmd[_u16MLoadCmdCnt] = u32Reg; \
            _u16MLoadMsk[_u16MLoadCmdCnt] = ((MS_U16)u8Mask); \
            _u16MLoadVal[_u16MLoadCmdCnt] = ((MS_U16)u8Value); \
        } \
        _u16MLoadCmdCnt++; \
        if(_u16MLoadCmdCnt >= MLOAD_MAX_CMD)\
        {\
            printf("[PQ ERROR] ====ML overflow !!! \n");\
            _u16MLoadCmdCnt = MLOAD_MAX_CMD - 1;        \
        }\
    }while(0)

//----------------------------
// Return value
//----------------------------
/**
 *  The return value for PQ fuction.
 */
typedef enum
{
    /// fail
    E_PQ_RET_FAIL = 0,
    /// success
    E_PQ_RET_OK,
} PQ_ReturnValue;

typedef enum
{
    E_DRVPQ_RET_FAIL = 0,   ///<Fail
    E_DRVPQ_RET_OK,         ///<OK
} E_DRVPQ_ReturnValue;

#if 0
/**
 * PQ DEINTERLACE MODE
 */
typedef enum
{
    /// off
    PQ_DEINT_OFF=0,
    /// 2DDI BOB
    PQ_DEINT_2DDI_BOB,
    /// 2DDI AVG
    PQ_DEINT_2DDI_AVG,
    /// 3DDI History(24 bit)
    PQ_DEINT_3DDI_HISTORY,
    /// 3DDI(16 bit)
    PQ_DEINT_3DDI,
} PQ_DEINTERLACE_MODE;
#endif

/**
 * PQ 3D_NR_FUNCTION_TYPE
 */
typedef enum
{
    /// off
    PQ_3D_NR_MIN,
    /// off
    PQ_3D_NR_OFF = PQ_3D_NR_MIN,
    /// Low
    PQ_3D_NR_LOW,
    /// Middle
    PQ_3D_NR_MID,
    /// High
    PQ_3D_NR_HIGH,
    /// Auto
    PQ_3D_NR_AUTO,
    /// Auto Low For Low level
    PQ_3D_NR_AUTO_LOW_L,
    /// Auto Mid For Low level
    PQ_3D_NR_AUTO_LOW_M,
    /// Auto High For Low level
    PQ_3D_NR_AUTO_LOW_H,
    /// Auto Low For Mid level
    PQ_3D_NR_AUTO_MID_L,
    /// Auto Mid For Mid level
    PQ_3D_NR_AUTO_MID_M,
    /// Auto High For Mid level
    PQ_3D_NR_AUTO_MID_H,
    /// Auto Low For High level
    PQ_3D_NR_AUTO_HIGH_L,
    /// Auto Mid For High level
    PQ_3D_NR_AUTO_HIGH_M,
    /// Auto High For High level
    PQ_3D_NR_AUTO_HIGH_H,
    /// Default
    PQ_3D_NR_DEFAULT,
    /// The max support number of PQ 3D Noise reduction
    PQ_3D_NR_NUM,
}PQ_3D_NR_FUNCTION_TYPE;

/**
 * PQ MPEG_NR_FUNCTION_TYPE
 */
typedef enum
{
    /// off
    PQ_MPEG_NR_MIN,
    /// off
    PQ_MPEG_NR_OFF = PQ_MPEG_NR_MIN,
    /// Low
    PQ_MPEG_NR_LOW,
    /// Middle
    PQ_MPEG_NR_MID,
    /// High
    PQ_MPEG_NR_HIGH,
    /// Auto
    PQ_MPEG_NR_AUTO,
    /// Default
    PQ_MPEG_NR_DEFAULT,
    /// The max support number of PQ MPEG Noise reduction
    PQ_MPEG_NR_NUM,
}PQ_MPEG_NR_FUNCTION_TYPE;

typedef enum
{
    /// off
    PQ_FilmMode_MIN,
    /// off
    PQ_FilmMode_OFF = PQ_FilmMode_MIN,
    /// On
    PQ_FilmMode_ON,
    /// Default
    PQ_FilmMode_DEFAULT,
    /// The max support number of PQ Perfect Clear
    PQ_FilmMode_NUM,
}PQ_FILM_MODE_FUNCTION_TYPE;

typedef enum
{
    /// off
    PQ_DynContr_MIN,
    /// off
    PQ_DynContr_OFF = PQ_DynContr_MIN,
    /// On
    PQ_DynContr_ON,
    /// Default
    PQ_DynContr_DEFAULT,
    /// The max support number of PQ Vibrant Colour
    PQ_DynContr_NUM,
}PQ_DYNAMIC_CONTRAST_FUNCTION_TYPE;


typedef enum
{
    PQ_OSD_BW_ON,
    PQ_OSD_BW_NUM,
}PQ_OSD_BW_FUNCTION_TYPE;

typedef enum
{
    PQ_PTP_PTP,
    PQ_PTP_NUM,
}PQ_PTP_FUNCTION_TYPE;

typedef enum
{
    PQ_COLOR_FOR_VIVID_ON,
    PQ_COLOR_FOR_VIVID_NUM,
}PQ_COLOR_FOR_VIVID_FUNCTION_TYPE;

typedef enum
{
    Level_Low=0,
    Level_MID,
    Level_High,

    MAX_Level
}PQ_CTRL_LEVEL;

#if 0
/**
 *  INPUT SOURCE TYPE
 */
typedef enum
{
    /// VGA
    PQ_INPUT_SOURCE_VGA,
    /// TV
    PQ_INPUT_SOURCE_TV,

    /// CVBS
    PQ_INPUT_SOURCE_CVBS,

    /// S-video
    PQ_INPUT_SOURCE_SVIDEO,

    /// Component
    PQ_INPUT_SOURCE_YPBPR,
    /// Scart
    PQ_INPUT_SOURCE_SCART,


    /// HDMI
    PQ_INPUT_SOURCE_HDMI,

    /// DTV
    PQ_INPUT_SOURCE_DTV,

    /// DVI
    PQ_INPUT_SOURCE_DVI,

    // Application source
    /// Storage
    PQ_INPUT_SOURCE_STORAGE,
    /// KTV
    PQ_INPUT_SOURCE_KTV,
    /// JPEG
    PQ_INPUT_SOURCE_JPEG,

    /// The max support number of PQ input source
    PQ_INPUT_SOURCE_NUM,
    /// None
    PQ_INPUT_SOURCE_NONE = PQ_INPUT_SOURCE_NUM,
} PQ_INPUT_SOURCE_TYPE;
#endif

/**
 *  HDMI COLOR FORMAT
 */
typedef enum
{
    /// RGB
    PQ_HDMI_COLOR_RGB,
    /// YUV422
    PQ_HDMI_COLOR_YUV_422,
    /// YUV444
    PQ_HDMI_COLOR_YUV_444,
    /// YUV420
    PQ_HDMI_COLOR_YUV_420,
}PQ_HDMI_COLOR_TYPE;

#if 0
/**
 *  The active Window for PQ function to takes place.
 */
typedef enum
{
    /// Main window
    PQ_MAIN_WINDOW=0,
    /// Sub window
    PQ_SUB_WINDOW=1,
    /// The max support window of PQ
    PQ_MAX_WINDOW
}PQ_WIN;

/**
 *  FOURCE COLOR FMT
 */
typedef enum
{
    /// Default
    PQ_FOURCE_COLOR_DEFAULT,
    /// RGB
    PQ_FOURCE_COLOR_RGB,
    /// YUV
    PQ_FOURCE_COLOR_YUV,
}PQ_FOURCE_COLOR_FMT;
#endif

/**
 *  VIDEO STANDARD TYPE
 */
typedef enum
{
    /// PAL BGHI
    E_PQ_VIDEOSTANDARD_PAL_BGHI        = 0x00,
    /// NTSC M
    E_PQ_VIDEOSTANDARD_NTSC_M          = 0x01,
    /// SECAM
    E_PQ_VIDEOSTANDARD_SECAM           = 0x02,
    /// NTSC 44
    E_PQ_VIDEOSTANDARD_NTSC_44         = 0x03,
    /// PAL M
    E_PQ_VIDEOSTANDARD_PAL_M           = 0x04,
    /// PAL N
    E_PQ_VIDEOSTANDARD_PAL_N           = 0x05,
    /// PAL 60
    E_PQ_VIDEOSTANDARD_PAL_60          = 0x06,
    /// NOT standard
    E_PQ_VIDEOSTANDARD_NOTSTANDARD     = 0x07,
    /// AUTO
    E_PQ_VIDEOSTANDARD_AUTO            = 0x08,
    /// The max support number of Video standard
    E_PQ_VIDEOSTANDARD_MAX
} PQ_VIDEOSTANDARD_TYPE;

typedef enum
{
    PQ_DISPLAY_ONE,
    PQ_DISPLAY_PIP,
    PQ_DISPLAY_POP,
}PQ_DISPLAY_TYPE;

/**
 *  Different PQ Types for PQ information merged to code, need to re-compile if changed PQ setting.
 */
typedef enum
{
    /// Select main window standard PQ setting for each input source/resolution
    PQ_BIN_STD_MAIN,
    /// Select sub window standard PQ setting for each input source/resolution
    PQ_BIN_STD_SUB,
    /// Select main window extension PQ setting for each input source/resolution
    PQ_BIN_EXT_MAIN,
    /// Select sub window extension PQ setting for each input source/resolution
    PQ_BIN_EXT_SUB,
    /// Select main window extension PQ setting for each input source/resolution
    PQ_BIN_CUSTOMER_MAIN,
    /// Select sub window extension PQ setting for each input source/resolution
    PQ_BIN_CUSTOMER_SUB,
    /// The max number of PQ Bin
    MAX_PQ_BIN_NUM,
}PQ_BIN_TYPE;

/**
 *  Different PQ Types for PQ information merged to binary, need to modify binary if changed PQ setting.
 */
typedef enum
{
    /// Select main window standard PQ setting for each input source/resolution
    PQ_TEXT_BIN_STD_MAIN,
    /// Select sub window standard PQ setting for each input source/resolution
    PQ_TEXT_BIN_STD_SUB,
    /// The max number of PQ Text Bin
    MAX_PQ_TEXT_BIN_NUM,
}PQ_TEXT_BIN_TYPE;

typedef enum
{
    /// PQ VD sampling is on
    PQ_VD_SAMPLING_ON,
    /// PQ VD sampling is off
    PQ_VD_SAMPLING_OFF,
    /// the max number of PQ VD sampling
    PQ_VD_SAMPLING_NUM,
}PQ_VD_SAMPLING_TYPE;


/**
 *  PQ library idetifcation information.
 */
typedef struct
{
    /// ID
    MS_U8  u8PQID;
    /// Virtual address
    void * pPQBin_AddrVirt;
    /// Physical address
    MS_PHYADDR PQBin_PhyAddr;
}PQ_Bin_Info;

/**
 *  PQ initialize information.
 */
typedef struct
{
    /// DDR2
    MS_BOOL bDDR2;
    ///MIU0 mem size
    MS_U32 u32miu0em_size;
    ///MIU1 mem size
    MS_U32 u32miu1em_size;
    /// DDR Frequency
    MS_U32  u32DDRFreq;
    /// Bus width
    MS_U8   u8BusWidth;
    /// Panel width
    MS_U16  u16PnlWidth;
    /// Panel height
    MS_U16  u16PnlHeight;
    /// Panel Vtotal
    MS_U16  u16Pnl_vtotal;
    /// OSD Hsize
    MS_U16  u16OSD_hsize;
    /// Bin count
    MS_U8   u8PQBinCnt;
    /// Text Bin count
    MS_U8   u8PQTextBinCnt;
    /// Customer Bin count
    MS_U8   u8PQBinCustomerCnt;
    /// PQ Bin informaton array
    PQ_Bin_Info  stPQBinInfo[MAX_PQ_BIN_NUM];
    /// PQ Text bin information array
    PQ_Bin_Info  stPQTextBinInfo[MAX_PQ_TEXT_BIN_NUM];
}MS_PQ_Init_Info;

/**
 *  The information to infer whether the input source is HDMI or DVI, and format.
 */
typedef struct
{
    /// is HDMI or not
    MS_BOOL bIsHDMI;
    /// HDMI color format
    PQ_HDMI_COLOR_TYPE enColorFmt;
    /// is HDMI Video or PC
    MS_BOOL bIsHDMIPC;
}MS_PQ_Hdmi_Info;

/**
 *  The information of video.
 */
typedef struct
{
    /// is SCART_RGB or not
    MS_BOOL bIsSCART_RGB;
    /// Video standard type
    PQ_VIDEOSTANDARD_TYPE enVideoStandard;
    /// is VIFIN or not
    MS_BOOL bIsVIFIN;
}MS_PQ_Vd_Info;
#if 0
/**
 *  Video data information to supply when in PQ mode.
 */
typedef struct
{
    /// is FBL or not
    MS_BOOL bFBL;
    /// is interlace mode or not
    MS_BOOL bInterlace;
    /// input Horizontal size
    MS_U16  u16input_hsize;
    /// input Vertical size
    MS_U16  u16input_vsize;
    /// input Vertical total
    MS_U16  u16input_vtotal;
    /// input Vertical frequency
    MS_U16  u16input_vfreq;
    /// output Vertical frequency
    MS_U16  u16ouput_vfreq;
    /// Display Horizontal size
    MS_U16  u16display_hsize;
    /// Display Vertical size
    MS_U16  u16display_vsize;
}MS_PQ_Mode_Info;
#endif
/**
 *  The media type. Photo or Movie
 */
typedef enum
{
    /// Photo
    E_PQ_MULTIMEDIA_PHOTO,
    /// Movie
    E_PQ_MULTIMEDIA_MOVIE,
}MS_PQ_MULTIMEDIA_TYPE;
/**
 *  MultiMedia information.
 */
typedef struct
{
    /// PQ MultiMedia information
    MS_PQ_MULTIMEDIA_TYPE eType;
}MS_PQ_MuliMedia_Info;


/**
 *  Supported DTV TYPE
 */
typedef enum
{
    /// H264
    E_PQ_DTV_H264,
    /// MPEG2
    E_PQ_DTV_MPEG2,
    /// IFrame
    E_PQ_DTV_IFRAME,
    /// H264
    E_PQ_DTV_H265,
}MS_PQ_DTV_TYPE;


typedef enum
{
    E_PQ_ADC_SAMPLING_NONE          = 0x00,
    E_PQ_ADC_SAMPLING_X_1           = 0x01,
    E_PQ_ADC_SAMPLING_X_2           = 0x02,
    E_PQ_ADC_SAMPLING_X_4           = 0x04,
    E_PQ_ADC_SAMPLING_X_8           = 0x08,
    E_PQ_ADC_SAMPLING_NOT_SUPPORT   = 0xFE,
    E_PQ_ADC_SAMPLING_MAX           = 0xFF,
}MS_PQ_ADC_SAMPLING_TYPE;

/**
 *  PQ table loading, Sub is for the PIP feature
 */
 typedef enum
{
    /// PQ table for Main window
    PQ_LOAD_TABLE_MAIN,
    /// PQ table for Sub window
    PQ_LOAD_TABLE_SUB,
    /// PQ Ext table for Main window
    PQ_LOAD_TABLE_MAIN_EX,
    /// PQ Ext table for Sub window
    PQ_LOAD_TABLE_SUB_EX,
    /// PQ color table for Main window
    PQ_LOAD_TABLE_MAIN_COLOR,
    /// PQ color table for Sub window
    PQ_LOAD_TABLE_SUB_COLOR,
} MS_PQ_PQLOADTABLE_WIN;

/**
 *  The Detail information of supported DTV
 */
typedef struct
{
    /// PQ DTV information
    MS_PQ_DTV_TYPE eType;
}MS_PQ_Dtv_Info;

#define PQ_DBG_PQTAB        (0x0001) ///< Debug PQ Table
#define PQ_DBG_SRULE        (0x0002)///< Debug S RULE
#define PQ_DBG_CSCRULE      (0x0004)///< Debug CSC RULE
#define PQ_DBG_GRULE        (0x0008)///< Debug G RULE
#define PQ_DBG_BW           (0x0010)///< Debug BANDWIDTH
#define PQ_DBG_MADI         (0x0020)///< Debug MADI
#define PQ_DBG_INFO         (0x0040)///< Debug INFO
#define PQ_DBG_IOCTL        (0x0080)///< Debug MADI
#define PQ_DBG_P2P          (0x0100)///< Debug point to point
#define PQ_DBG_CUSTOMER     (0x0200)///< Debug point to bby


/**
*   PQ Status
*/
typedef struct
{
    MS_BOOL bIsInitialized;
    MS_BOOL bIsRunning;
}MS_PQ_Status;

/**
*   PQ Information
*/
typedef struct
{
    MS_U16   u16Input_Src_Num;
    MS_U8    u8IP_Num;
}MS_PQ_INFO;


typedef struct
{
    PQ_VD_SAMPLING_TYPE eType;
    MS_U16 u16Hstart;
    MS_U16 u16Vstart;
    MS_U16 u16Hsize;
    MS_U16 u16Vsize;
    MS_U16 u16Htt;
}MS_PQ_VD_Sampling_Info;

typedef struct
{
    MS_BOOL bPIP_Supported;
    MS_BOOL b3DVideo_Supported;
}MS_PQ_CAP_INFO;

#if(ENABLE_PQ_LOAD_TABLE_INFO)
typedef struct
{
    MS_U16  _u16CurInputSrcType;
    //MS_U8    _au8IPGroupIdx[PQ_IP_NUM_Main]; // current table of each IP
    MS_U8   _au8IPGroupIdx[512]; // current table of each IP, because of build problem, use 512 instead PQ_IP_NUM_Main
}MS_PQ_LOAD_TABLE_INFO;
#endif

/**
*   PQ RFBL mode info
*/
typedef struct
{
    ///RFBL mode enable/disable
    MS_BOOL bEnable;
    ///RFBL mode with/without film type
    MS_BOOL bFilm;
    ///PQ MADi type
    MS_U8 u8MADiType;
}MS_PQ_RFBL_INFO;

/**
*   PQ Switch Control
*/
typedef enum
{
    /// PQ AP FEATURE On
    PQ_FEATURE_SWITCH_ON,
    /// PQ AP FEATURE Off
    PQ_FEATURE_SWITCH_OFF,
    ///  The max support number of PQ AP FEATURE
    PQ_FEATURE_SWITCH_NUM,
}PQ_FEATURE_SWITCH_TYPE;

/**
*   PQ Level Control
*/
typedef enum
{
    /// PQ AP FEATURE Level Low
    PQ_FEATURE_LEVEL_LOW,
    /// PQ AP FEATURE Level Middle
    PQ_FEATURE_LEVEL_MIDDLE,
    /// PQ AP FEATURE Level High
    PQ_FEATURE_LEVEL_HIGH,
    /// PQ AP FEATURE Level Auto
    PQ_FEATURE_LEVEL_AUTO,
    /// The max support number of  Level
    PQ_FEATURE_LEVEL_NUM,
}PQ_FEATURE_LEVEL_TYPE;

/**
*   PQ GRule Support List
*/
typedef enum
{
    /// PQ GRule Support Film
    E_PQ_SUPPORTED_FILM,
    /// PQ GRule Support NR
    E_PQ_SUPPORTED_NR,
    /// PQ GRule Support MPEG NR
    E_PQ_SUPPORTED_MPEG_NR,
    /// PQ GRule Support Black Level
    E_PQ_SUPPORTED_BLACK_LEVEL,
    /// PQ GRule Support Ultra Clear
    E_PQ_SUPPORTED_ULTRA_CLEAR,
    /// PQ GRule Support Max number
    E_PQ_SUPPORTED_MAX,
} PQ_SUPPORTED_TYPE;

/// HDR GRULE INDEX setting enum
typedef enum
{
    E_MAPI_PQL_HDR_OFF,
    E_MAPI_PQL_HDR_OPEN_AUTO,
    E_MAPI_PQL_HDR_OPEN_HIGH,
    E_MAPI_PQL_HDR_OPEN_MID,
    E_MAPI_PQL_HDR_OPEN_LOW,
    E_MAPI_PQL_HDR_OPEN_REF,
    E_MAPI_PQL_HDR_DOLBY_VIVID,
    E_MAPI_PQL_HDR_DOLBY_USER,
    E_MAPI_PQL_HDR_DOLBY_BRIGHTNESS,
    E_MAPI_PQL_HDR_DOLBY_DARK,
    E_MAPI_PQL_HDR_HLG_AUTO,
    E_MAPI_PQL_HDR_HLG_HIGH,
    E_MAPI_PQL_HDR_HLG_MID,
    E_MAPI_PQL_HDR_HLG_LOW,
} EN_MAPI_PQL_HDR_GRULE_INDEX;


//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
/// Get library version
/// @param  ppVersion                    \b OUT: point to point to MSIF_Version
/// @return PQ_ReturnValue
//-------------------------------------------------------------------------------------------------
E_DRVPQ_ReturnValue MDrv_PQ_GetLibVer(const MSIF_Version **ppVersion);

//-------------------------------------------------------------------------------------------------
/// Get PQ information
/// @param  pInfo                    \b OUT: point to PQ information
/// @return PQ_ReturnValue
//-------------------------------------------------------------------------------------------------
PQ_ReturnValue    MDrv_PQ_GetInfo(MS_PQ_INFO *pInfo);

//-------------------------------------------------------------------------------------------------
/// Get PQ status
/// @param  pStatus                    \b OUT: point to PQ status
/// @return MS_BOOL
//-------------------------------------------------------------------------------------------------
MS_BOOL           MDrv_PQ_GetStatus(MS_PQ_Status *pStatus);
/*
DEBUG MASK:
0x01;///< Debug PQ Table
0x02;///< Debug S RULE
0x04;///< Debug CSC RULE
0x08;///< Debug G RULE
0x10;///< Debug BANDWIDTH
0x20;///< Debug INFO
*/

//-------------------------------------------------------------------------------------------------
/// Get PQ debug message output level
/// @param  u16DbgSwitch                    \b IN: DEBUG MASK, the debug message output level
/// 0x01;///< Debug PQ Table
/// 0x02;///< Debug S RULE
/// 0x04;///< Debug CSC RULE
/// 0x08;///< Debug G RULE
/// 0x10;///< Debug BANDWIDTH
/// 0x20;///< Debug INFO
/// @return MS_BOOL
//-------------------------------------------------------------------------------------------------
MS_BOOL           MDrv_PQ_SetDbgLevel(MS_U16 u16DbgSwitch);

// common PQ function
//-------------------------------------------------------------------------------------------------
/// Initial function
/// @param  pstPQInitInfo                 \b IN: point to PQ initial information
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_Init(MS_PQ_Init_Info *pstPQInitInfo);

//-------------------------------------------------------------------------------------------------
/// Exit function
/// @retval Success or fail
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_Exit(void);

//-------------------------------------------------------------------------------------------------
/// Deside source type
/// @param  eWindow                    \b IN: TBD
/// @param  enInputSourceType          \b IN: input source type
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_DesideSrcType(PQ_WIN eWindow, PQ_INPUT_SOURCE_TYPE enInputSourceType);

//-------------------------------------------------------------------------------------------------
/// Get source type
/// @param  eWindow                    \b IN: TBD
/// @return Main window or Sub window
//-------------------------------------------------------------------------------------------------
MS_U16 MDrv_PQ_GetSrcType(PQ_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Get PQ delay time
/// @return delay time value
//-------------------------------------------------------------------------------------------------
MS_U16 MDrv_PQ_GetDelayTime(void);

//-------------------------------------------------------------------------------------------------
/// Get input source type
/// @param  eWindow                    \b IN: TBD
/// @return Input Source Type of Main window or Sub window
//-------------------------------------------------------------------------------------------------
PQ_INPUT_SOURCE_TYPE MDrv_PQ_GetInputSourceType(PQ_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Set color range
/// @param  eWindow                     \b IN: TBD
/// @param  bColorRange0_255            \b IN: Color range
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_SetColorRange(PQ_WIN eWindow, MS_BOOL bColorRange0_255);

//-------------------------------------------------------------------------------------------------
/// Set CSC
/// @param  eWindow                          \b IN: TBD
/// @param  enFourceColor                    \b IN: TBD
/// @retval TBD
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_SetCSC(PQ_WIN eWindow, PQ_FOURCE_COLOR_FMT enFourceColor);


//-------------------------------------------------------------------------------------------------
/// Get Memory color format
/// @param  eWindow                          \b IN: TBD
/// @param  enFourceColor                    \b IN: TBD
/// @retval TBD
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_Get_MemYUVFmt(PQ_WIN eWindow, PQ_FOURCE_COLOR_FMT enFourceColor);

//-------------------------------------------------------------------------------------------------
/// Load scaling table
/// @param  eWindow                          \b IN: TBD
/// @param  eScalingType                     \b IN: TBD
/// @param  bPreV_ScalingDown                \b IN: TBD
/// @param  bInterlace                       \b IN: TBD
/// @param  bColorSpaceYUV                   \b IN: TBD
/// @param  u16InputSize                     \b IN: TBD
/// @param  u16SizeAfterScaling              \b IN: TBD
/// @retval TBD
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_LoadScalingTable(PQ_WIN eWindow,
                                  MS_U8 eScalingType,
                                  MS_BOOL bPreV_ScalingDown,
                                  MS_BOOL bInterlace,
                                  MS_BOOL bColorSpaceYUV,
                                  MS_U16 u16InputSize,
                                  MS_U16 u16SizeAfterScaling);

//-------------------------------------------------------------------------------------------------
/// Set Memory format
/// @param  eWindow                          \b IN: TBD
/// @param  bMemFmt422                       \b IN: TBD
/// @param  bFBL                             \b IN: TBD
/// @param  u8BitsPerPixel                   \b IN: TBD
/// @return TBD
//-------------------------------------------------------------------------------------------------
PQ_DEINTERLACE_MODE MDrv_PQ_SetMemFormat(PQ_WIN eWindow,
                                                MS_BOOL bMemFmt422,
                                                MS_BOOL bFBL,
                                                MS_U8 *u8BitsPerPixel);

//-------------------------------------------------------------------------------------------------
/// Reduce Bandwidth for OSD
/// @param  eWindow                          \b IN: TBD
/// @param  bOSD_On                          \b IN: TBD
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_ReduceBW_ForOSD(PQ_WIN eWindow, MS_BOOL bOSD_On);

//-------------------------------------------------------------------------------------------------
/// Reduce Bandwidth for PVR
/// @param  eWindow                          \b IN: TBD
/// @param  bPVR_On                          \b IN: TBD
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_ReduceBW_ForPVR(PQ_WIN eWindow, MS_BOOL bPVR_On);

//-------------------------------------------------------------------------------------------------
/// Enable MADI Force
/// @param  eWindow                          \b IN: PQ Window
/// @param  bFullMotion                      \b IN: Full Motion
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_EnableMADIForce(PQ_WIN eWindow, MS_BOOL bFullMotion);

//-------------------------------------------------------------------------------------------------
/// Set 420 up sampling
/// @param  eWindow                          \b IN: TBD
/// @param  bFBL                             \b IN: TBD
/// @param  bPreV_ScalingDown                \b IN: TBD
/// @param  u16V_CropStart                   \b IN: TBD
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_Set420upsampling(PQ_WIN eWindow, MS_BOOL bFBL, MS_BOOL bPreV_ScalingDown, MS_U16 u16V_CropStart);

//-------------------------------------------------------------------------------------------------
/// Set Film mode
/// @param  eWindow                          \b IN: TBD
/// @param  bEnable                          \b IN: TBD
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_SetFilmMode(PQ_WIN eWindow, MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// Load NR Table
/// @param  eWindow                          \b IN: TBD
/// @param  en3DNRType                       \b IN: TBD
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_LoadNRTable(PQ_WIN eWindow, PQ_3D_NR_FUNCTION_TYPE en3DNRType);

//-------------------------------------------------------------------------------------------------
/// To Set Specified GRule's Specified Status
/// @param  eWindow                     \b IN: TBD
/// @param u16GruleType               \b IN: Specified Grule type
/// @param u16GruleStatus             \b IN: Specified status of u16GruleType
/// @return MAPI_BOOL                  \b TRUE: success; FALSE: fail
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_SetGRuleStatus(PQ_WIN eWindow, MS_U16 u16GruleType, MS_U16 u16GruleStatus);

//-------------------------------------------------------------------------------------------------
/// To Get Specified GRule's Level Num
/// @param  eWindow                          \b IN: TBD
/// @param  u16GruleType                  \b IN: TBD
/// @return  MAPI_U16                        \b 0: fail;   non-0: success
//-------------------------------------------------------------------------------------------------
MS_U16 MDrv_PQ_GetGRule_LvlNum(PQ_WIN eWindow, MS_U16 u16GRuleType);

//-------------------------------------------------------------------------------------------------
/// To Get Total GRule Type Num
/// @param  eWindow                          \b IN: TBD
/// @return total Grule type num
//-------------------------------------------------------------------------------------------------
MS_U16 MDrv_PQ_GetGRule_GRuleNum(PQ_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Load MPEG NR Table
/// @param  eWindow                          \b IN: TBD
/// @param  enMPEGNRType                \b IN: TBD
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_LoadMPEGNRTable(PQ_WIN eWindow, PQ_MPEG_NR_FUNCTION_TYPE enMPEGNRType);

//-------------------------------------------------------------------------------------------------
/// Load DynamicContrast Table
/// @param  eWindow                          \b IN: TBD
/// @param  enDynamicContrastType   \b IN: TBD
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_LoadDynamicContrastTable(PQ_WIN eWindow, PQ_DYNAMIC_CONTRAST_FUNCTION_TYPE enDynamicContrastType);

//-------------------------------------------------------------------------------------------------
/// Load FilmMode Table
/// @param  eWindow                          \b IN: TBD
/// @param  enFilmModeType               \b IN: TBD
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_LoadFilmModeTable(PQ_WIN eWindow, PQ_FILM_MODE_FUNCTION_TYPE enFilmModeType);

//-------------------------------------------------------------------------------------------------
/// Load UltraClear Table
/// @param  eWindow                          \b IN: TBD
/// @param  enCtrlType                       \b IN: TBD
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_Load_ULTRACLEAR_Table(PQ_WIN eWindow, PQ_FEATURE_SWITCH_TYPE enCtrlType);

//-------------------------------------------------------------------------------------------------
/// Set non-linear scaling
/// @param  eWindow                       \b IN: TBD
/// @param  u8Level                       \b IN: TBD
/// @param  bEnable                       \b IN: TBD
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_SetNonLinearScaling(PQ_WIN eWindow, MS_U8 u8Level, MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// Check settings
/// @param  eWindow                       \b IN: TBD
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_CheckSettings(PQ_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Load settings
/// @param  eWindow                       \b IN: TBD
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_LoadSettings(PQ_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Load customer settings
/// @param  eWindow                       \b IN: TBD
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_LoadCustomerSettings(PQ_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Load table
/// @param  eWindow                         \b IN: TBD
/// @param  u16TabIdx                       \b IN: TBD
/// @param  u16PQIPIdx                      \b IN: TBD
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_LoadTable(PQ_WIN eWindow, MS_U16 u16TabIdx, MS_U16 u16PQIPIdx);

//-------------------------------------------------------------------------------------------------
/// Clone table, the PQ assgined value is ignored, this function will read value from hw reg
///  of u16PQMainIPIdx, then copy to hw reg of u16PQSubIPIdx
/// @param  eWindow                         \b IN: Main window or sub window
/// @param  u16TabIdx                       \b IN: useless currently
/// @param  u16PQMainIPIdx                      \b IN: copy from
/// @param  u16PQSubIPIdx                      \b IN: copy to
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_CloneTable(PQ_WIN eWindow, MS_U16 u16TabIdx, MS_U16 u16PQMainIPIdx, MS_U16 u16PQSubIPIdx);

//-------------------------------------------------------------------------------------------------
/// Load customer table
/// @param  eWindow                         \b IN: TBD
/// @param  u16TabIdx                       \b IN: TBD
/// @param  u16PQIPIdx                      \b IN: TBD
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_LoadCustomerTable(PQ_WIN eWindow, MS_U16 u16TabIdx, MS_U16 u16PQIPIdx);

//-------------------------------------------------------------------------------------------------
/// Get IP number
/// @param  eWindow                         \b IN: TBD
/// @retval TBD
//-------------------------------------------------------------------------------------------------
MS_U16 MDrv_PQ_GetIPNum(PQ_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Get current table number
/// @param  eWindow                         \b IN: TBD
/// @param  u16PQIPIdx                      \b IN: TBD
/// @retval TBD
//-------------------------------------------------------------------------------------------------
MS_U16 MDrv_PQ_GetTableNum(PQ_WIN eWindow, MS_U16 u16PQIPIdx);

//-------------------------------------------------------------------------------------------------
/// Get current table index
/// @param  eWindow                         \b IN: TBD
/// @param  u16PQIPIdx                      \b IN: TBD
/// @retval TBD
//-------------------------------------------------------------------------------------------------
MS_U16 MDrv_PQ_GetCurrentTableIndex(PQ_WIN eWindow, MS_U16 u16PQIPIdx);

//-------------------------------------------------------------------------------------------------
/// 3D pq clone,  sub win sync with main win
/// @param bIpSync                            \b IN: do Ip sync operation
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_3DCloneforPIP(MS_BOOL bIpSync);

//-------------------------------------------------------------------------------------------------
/// Disable film mode
/// @param  eWindow                     \b IN: Window type
/// @param  bOn                         \b IN: TBD
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_DisableFilmMode(PQ_WIN eWindow, MS_BOOL bOn);

//-------------------------------------------------------------------------------------------------
/// Get Source type name
/// @param  eWindow                         \b IN: Window type
/// @retval TBD
//-------------------------------------------------------------------------------------------------
char* MDrv_PQ_GetSrcTypeName(PQ_WIN eWindow);
char* MDrv_PQ_GetSrcTypeName_2(PQ_WIN eWindow, U16 u16SrcType);

//-------------------------------------------------------------------------------------------------
/// Get IP name
/// @param  u8PQIPIdx                         \b IN: TBD
/// @retval TBD
//-------------------------------------------------------------------------------------------------
char* MDrv_PQ_GetIPName(MS_U8 u8PQIPIdx);

//-------------------------------------------------------------------------------------------------
/// Get table name
/// @param  u8PQIPIdx                        \b IN: TBD
/// @param  u8TabIdx                         \b IN: TBD
/// @retval TBD
//-------------------------------------------------------------------------------------------------
char* MDrv_PQ_GetTableName(MS_U8 u8PQIPIdx, MS_U8 u8TabIdx);

//-------------------------------------------------------------------------------------------------
/// Adaptive tuning
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_AdaptiveTuning(void);
void MDrv_PQ_AdaptiveTuning_ISR(void);


//-------------------------------------------------------------------------------------------------
/// Set DTV Info
/// @param  eWindow                        \b IN: TBD
/// @param  pstPQDTVInfo                   \b IN: TBD
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_Set_DTVInfo(PQ_WIN eWindow, MS_PQ_Dtv_Info *pstPQDTVInfo);

//-------------------------------------------------------------------------------------------------
/// Set MultiMedia information
/// @param  eWindow                        \b IN: TBD
/// @param  pstPQMMInfo                    \b IN: TBD
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_Set_MultiMediaInfo(PQ_WIN eWindow, MS_PQ_MuliMedia_Info *pstPQMMInfo);

//-------------------------------------------------------------------------------------------------
/// Set H264 information
/// @param  bEn                                \b IN: it's H264? TRUE or FALSE
/// @return MS_BOOL
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_SetH264_OnOff(MS_BOOL bEn);

//-------------------------------------------------------------------------------------------------
/// Set 4kx2k MVC information
/// @param  bEn                                \b IN: it's H264? TRUE or FALSE
/// @return MS_BOOL
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_SetMVC4kx1k_OnOff(MS_BOOL bEn);

//-------------------------------------------------------------------------------------------------
/// Set Network mm information
/// @param  bEn                                \b IN: it's network mm case? TRUE or FALSE
/// @return MS_BOOL
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_SetNetworkMM_OnOff(MS_BOOL bEn);


//-------------------------------------------------------------------------------------------------
/// Set MM information
/// @param  bEn                                \b IN: it's MM? TRUE or FALSE
/// @return MS_BOOL
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_SetMM_OnOff(MS_BOOL bEn);

//-------------------------------------------------------------------------------------------------
/// Set Rmvb information
/// @param  bEn                                \b IN: it's Rmvb? TRUE or FALSE
/// @return MS_BOOL
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_SetRmvb_OnOff(MS_BOOL bEn, PQ_WIN ePQWindow);

//-------------------------------------------------------------------------------------------------
/// Set Video Decoder information
/// @param  eWindow                        \b IN: TBD
/// @param  pstPQVDInfo                    \b IN: TBD
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_Set_VDInfo(PQ_WIN eWindow, MS_PQ_Vd_Info* pstPQVDInfo);

void MDrv_PQ_Get_ModeInfo(PQ_WIN eWindow, MS_PQ_Mode_Info *pstPQModeInfo);

//-------------------------------------------------------------------------------------------------
/// Set mode information
/// @param  eWindow                             \b IN: TBD
/// @param  enInputSourceType                   \b IN: TBD
/// @param  pstPQModeInfo                       \b IN: TBD
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_Set_ModeInfo(PQ_WIN eWindow, PQ_INPUT_SOURCE_TYPE enInputSourceType, MS_PQ_Mode_Info *pstPQModeInfo);

//-------------------------------------------------------------------------------------------------
/// Set HDMI information
/// @param  eWindow                             \b IN: TBD
/// @param  pstPQHDMIInfo                       \b IN: TBD
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_SetHDMIInfo(PQ_WIN eWindow, const MS_PQ_Hdmi_Info* const pstPQHDMIInfo);

//-------------------------------------------------------------------------------------------------
/// Set HDMI information
/// @param  eWindow                             \b IN: TBD
/// @param  bIsTrue                       \b IN: TBD
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_SetHDMI_PC(PQ_WIN eWindow, MS_BOOL bIsTrue);

//-------------------------------------------------------------------------------------------------
/// Set HDMI information
/// @param  eWindow                             \b IN: TBD
/// @retval TBD
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_GetHDMI_PC_Status(PQ_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Load table by context
/// @param  eWindow                             \b IN: TBD
//-------------------------------------------------------------------------------------------------
void MDrv_BW_LoadTableByContext(PQ_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Bandwidth load initial table
//-------------------------------------------------------------------------------------------------
void MDrv_BW_LoadInitTable(void);

//-------------------------------------------------------------------------------------------------
/// Set HDMI information
/// @param  u16DisplayWidth                     \b IN: TBD
/// @param  enDisplaType                        \b IN: TBD
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_Set_DisplayType(MS_U16 u16DisplayWidth, PQ_DISPLAY_TYPE enDisplaType);

//-------------------------------------------------------------------------------------------------
/// Set force Y motion
/// @param  eWindow                             \b IN: TBD
/// @param  bEnable                             \b IN: TBD
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_MADiForceMotionY(PQ_WIN eWindow, MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// Set force C motion
/// @param  eWindow                             \b IN: TBD
/// @param  bEnable                             \b IN: TBD
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_MADiForceMotionC(PQ_WIN eWindow, MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// Set RFBL mode for U4 skip field mechanism
/// @param  bEnable                         \b IN: TBD
/// @param  bFilm                             \b IN: TBD
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_SetRFblMode(MS_BOOL bEnable,MS_BOOL bFilm);

//-------------------------------------------------------------------------------------------------
/// Get RFBL mode for U4 skip field mechanism
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_GetRFblMode(MS_PQ_RFBL_INFO * stInfo);

//-------------------------------------------------------------------------------------------------
/// Get VD Sampling
/// @param  eWindow                             \b IN: TBD
/// @param  enInputSourceType                   \b IN: TBD
/// @param  eStandard                           \b IN: TBD
/// @param  pInfo                               \b OUT: TBD
/// @return MS_BOOL
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_Get_VDSampling_Info(PQ_WIN eWindow, PQ_INPUT_SOURCE_TYPE enInputSourceType, PQ_VIDEOSTANDARD_TYPE eStandard, MS_PQ_VD_Sampling_Info *pInfo);


//-------------------------------------------------------------------------------------------------
/// IOCTL function
/// @param  eWindow                             \b IN: TBD
/// @param  u32Flag                             \b IN: TBD
/// @param  pBuf                                \b OUT: TBD
/// @param  u32BufSize                                \b OUT: TBD
/// @return MS_BOOL
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_IOCTL(PQ_WIN eWindow, MS_U32 u32Flag, void *pBuf, MS_U32 u32BufSize);


//-------------------------------------------------------------------------------------------------
/// Set MLoad enable/disable
/// @param  eWindow                             \b IN: TBD
/// @param  bEn                                 \b IN: TBD
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_Set_MLoadEn(PQ_WIN eWindow, MS_BOOL bEn);


//-------------------------------------------------------------------------------------------------
/// Get ADC Sampling
/// @param  eWindow                             \b IN: TBD
/// @param  enInputSourceType                   \b IN: TBD
/// @param  pstPQModeInfo                       \b IN: TBD
/// @return MS_PQ_ADC_SAMPLING_TYPE
//-------------------------------------------------------------------------------------------------
MS_PQ_ADC_SAMPLING_TYPE MDrv_PQ_Get_ADCSampling_Info(PQ_WIN eWindow, PQ_INPUT_SOURCE_TYPE enInputSourceType, MS_PQ_Mode_Info *pstPQModeInfo);

//-------------------------------------------------------------------------------------------------
/// set 3D Video mode
/// @param  bEn                                \b IN: TBD
/// @return MS_BOOL
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_Set3D_OnOff(MS_BOOL bEn);

//-------------------------------------------------------------------------------------------------
/// disable UCFeature
/// @param  eWindow                            \b IN: TBD
/// @param  BOOL                               \b OUT: TBD
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_DisableUCFeature(PQ_WIN eWindow);

//------------------------------------------------------------------------------
/// Set DMS V12 L on/off
/// @param  eWindow                            \b IN: TBD
/// @param bEnable                 \b IN: Enable DMS V12L if it is TRUE
/// @return MS_BOOL
//------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_SetDMSV12L(PQ_WIN eWindow, MS_BOOL bEnable);

//------------------------------------------------------------------------------
/// Get DMS V12 L on/off
/// @param  eWindow                            \b IN: TBD
/// @return                         \b OUT: BOOL TURE for DMSV 12L on
//------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_GetDMSV12LFromXRuleTable(PQ_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// get the capibility of PQ
/// @param  pInfo                              \b IN: TBD
/// @return MS_BOOL
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_GetCaps(MS_PQ_CAP_INFO *pInfo);

//-------------------------------------------------------------------------------------------------
/// Set Dynamic Scaling on/off
/// @param  eWindow                             \b IN: TBD
/// @param  bEn                                 \b IN: TBD
/// @return MS_BOOL
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_SetDS_OnOFF(PQ_WIN eWindow, MS_BOOL bEn);

//-------------------------------------------------------------------------------------------------
/// print out table information of each IP
/// @param  enPQWin                             \b IN: TBD
//-------------------------------------------------------------------------------------------------
void MDRV_PQ_PrintLoadTableInfo(MS_PQ_PQLOADTABLE_WIN enPQWin);

//-------------------------------------------------------------------------------------------------
/// Get madi information
/// @param  eWindow                             \b IN: TBD
/// @return MS_BOOL MADI:True , NULL : False
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_Get_RFBL_Info( PQ_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// get src hd/sd information
/// @param  eWindow                             \b IN: TBD
/// @return MS_BOOL
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_CheckHDMode( PQ_WIN eWindow );

//-------------------------------------------------------------------------------------------------
/// get Interlace SD mode
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_Get_Interlace_SD_mode(void);

//-------------------------------------------------------------------------------------------------
/// Set Dynamic Scaling on/off
/// @param  enType                             \b IN: TBD
/// @retval Support or not
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_GRULE_Get_Support_Status(PQ_SUPPORTED_TYPE enType);

//-------------------------------------------------------------------------------------------------
/// Set point to point mode on/off
/// @param  bEnable                             \b IN: TBD
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_SetDotByDotMode(MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// Update the Memory Format
/// @retval Success or not
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_Update_MemFormat(void);

//-------------------------------------------------------------------------------------------------
/// set low 3d picture quality, for user demo
/// @param  bEnable                             \b IN: low or high quality
/// @return NONE
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_LOW_3dQuality(MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// set enhance quality, for mwe demo
/// @return NONE
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_MWE_SetEnhanceQuality(void);
//-------------------------------------------------------------------------------------------------
/// restore enhance quality, for mwe demo
/// @return NONE
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_MWE_RestoreEnhanceQuality(void);
//-------------------------------------------------------------------------------------------------
/// set enhance quality, for mwe demo
/// @return NONE
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_MWE_RestoreOffQuality(void);
//-------------------------------------------------------------------------------------------------
/// set enhance quality, for mwe demo
/// @return NONE
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_MWE_SetOffQuality(void);

//-------------------------------------------------------------------------------------------------
/// Get the H size
/// @return MS_U16 Horizontal size
//-------------------------------------------------------------------------------------------------
MS_U16 MDrv_PQ_GetHsize(PQ_WIN enPQWin);
//-------------------------------------------------------------------------------------------------
/// Get the V size
/// @return MS_U16 Vertical size
//-------------------------------------------------------------------------------------------------
MS_U16 MDrv_PQ_GetVsize(PQ_WIN enPQWin);
//-------------------------------------------------------------------------------------------------
/// Check interlace
/// @return MS_BOOL
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_IsInterlace(PQ_WIN enPQWin);

//-------------------------------------------------------------------------------------------------
/// selection to VIP CSC
/// Both equation selection rules are
/// 0: SDTV(601) R  G  B  : 16-235
/// 1: SDTV(601) R  G  B  : 0-255
/// @param  u16selection                          \b IN: Select 16-235 or 0-255
/// @param  eWindow                          \b IN: PQ Window Main or sub
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_SetSelectCSC(MS_U16 u16selection, PQ_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Get R2Y EQ Select
/// @param  eWindow                          \b IN: PQ Window Main or sub
/// @return   TRUE: 709 to 601    , FALSE: not 709 to 601
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_GetR2YEqSelect(PQ_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Load PTP Table
/// @param  eWindow                          \b IN: PQ Window Main or sub
/// @param  enPTP_Type                       \b IN: QMap PTP type
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_LoadPTPTable(PQ_WIN eWindow, PQ_PTP_FUNCTION_TYPE enPTP_Type);

//-------------------------------------------------------------------------------------------------
/// LoadCUSTOMER Table
/// @param  eWindow                          \b IN: PQ Window Main or sub
/// @param  enCOLOR_FOR_VIVID_Type                       \b IN: QMap COLOR_FOR_VIVID
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_LoadColor_For_VIVIDTable(PQ_WIN eWindow, PQ_COLOR_FOR_VIVID_FUNCTION_TYPE enCOLOR_FOR_VIVID_Type);

//-------------------------------------------------------------------------------------------------
/// Enable or diable PTP
/// @param  pstXC_SetWin_Info                \b IN: Set Win Info
/// @param  bEnable                          \b IN: Enable or disable the PTP
/// @param  eWindow                          \b IN: PQ Window Main or sub
/// @return the result of Setting
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_Set_PointToPoint(XC_SETWIN_INFO *pstXC_SetWin_Info,
                               MS_BOOL bEnable,
                               PQ_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Enable or diable Dualview state
/// @param  bEnable                          \b IN: Enable or disable the dualview
/// @return the result of Setting
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_SetDualViewState(MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// Get the current Dualview state(Enable or diable)
/// @return the state
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_GetDualViewState(void);

//-------------------------------------------------------------------------------------------------
/// get PTP current status, enable or disable
/// @param  eWindow                          \b IN: PQ Window Main or sub
/// @return the current status
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_Get_PointToPoint(PQ_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Check current input timing is suitable for PTP or not
/// @param  pstXC_SetWin_Info                \b IN: Set Win Info
/// @param  eWindow                          \b IN: PQ Window Main or sub
/// @return TRUE: suitable for PTP, FALSE: not suitable
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_Check_PointToPoint_Condition(XC_SETWIN_INFO *pstXC_SetWin_Info, PQ_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Set PQ array for the sub win of the display type.
/// Only works for non-bin mode.
/// @param  u16DisplayWidth                \b IN: Panel width
/// @param  enDisplaType                   \b IN: One, PIP, POP
/// @param  bSkipCommTable                 \b IN: whether need to load Common Table, only initialize needs to load it
/// @return TRUE: Success, FALSE: failed
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_Set_DisplayType_Sub(MS_U16 u16DisplayWidth, PQ_DISPLAY_TYPE enDisplaType, MS_BOOL bSkipCommTable);

//-------------------------------------------------------------------------------------------------
/// Set PQ array for the main win of the display type.
/// Only works for non-bin mode.
/// @param  u16DisplayWidth                \b IN: Panel width
/// @param  enDisplaType                   \b IN: One, PIP, POP
/// @param  bSkipCommTable                 \b IN: whether need to load Common Table, only initialize needs to load it
/// @return TRUE: Success, FALSE: failed
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_Set_DisplayType_Main(MS_U16 u16DisplayWidth, PQ_DISPLAY_TYPE enDisplaType, MS_BOOL bSkipCommTable);

MS_BOOL MDrv_PQ_GetMADiFromGrule_OSDBW(PQ_WIN eWindow,
                                           MS_U16 *pu16TabIdx_MADi,
                                           MS_U16 *pu16TabIdx_MADi_Motion,
                                           MS_U16 *pu16TabIdx_MADi_DFK,
                                           MS_U16 *pu16TabIdx_MADi_SST,
                                           MS_U16 *pu16TabIdx_MADi_EODiW,
                                           MS_U16 *pu16TabIdx_UCCTL);
MS_BOOL MDrv_PQ_GetMemFmtInGeneral(PQ_WIN eWindow,
                                            MS_BOOL bMemFmt422,
                                            MS_U16 *pu16TabIdx_MemFormat,
                                            MS_U16 *pu16TabIdx_444To422,
                                            MS_U16 *pu16TabIdx_422To444
                                            );
MS_BOOL MDrv_PQ_GetMADiInGeneral(PQ_WIN eWindow,
                                           MS_U16 *pu16TabIdx_MADi,
                                           MS_U16 *pu16TabIdx_MADi_Motion,
                                           MS_U16 *pu16TabIdx_MADi_DFK,
                                           MS_U16 *pu16TabIdx_MADi_SST,
                                           MS_U16 *pu16TabIdx_MADi_EODiW,
                                           MS_U16 *pu16TabIdx_UCCTL);
MS_BOOL MDrv_PQ_GetDDRSelectInfo_Ver1(PQ_WIN eWindow,
                                           MS_U16 *pu16TabIdx_MADi,
                                           MS_U16 *pu16TabIdx_MADi_Motion,
                                           MS_U16 *pu16TabIdx_MADi_DFK,
                                           MS_U16 *pu16TabIdx_MADi_SST,
                                           MS_U16 *pu16TabIdx_MADi_EODiW,
                                           MS_U16 *pu16TabIdx_UCCTL);
MS_BOOL MDrv_PQ_GetDDRSelectInfo_Ver2(PQ_WIN eWindow,
                                           MS_U16 *pu16TabIdx_MADi,
                                           MS_U16 *pu16TabIdx_MADi_Motion,
                                           MS_U16 *pu16TabIdx_MADi_DFK,
                                           MS_U16 *pu16TabIdx_MADi_SST,
                                           MS_U16 *pu16TabIdx_MADi_EODiW,
                                           MS_U16 *pu16TabIdx_UCCTL);
MS_BOOL MDrv_PQ_GetMADiForRFBL(PQ_WIN eWindow, MS_BOOL bFBL, MS_U16 *pu16TabIdx_MADi_Motion, MS_U16 *pu16TabIdx_MADi);
MS_BOOL MDrv_PQ_Patch2Rto4RForFieldPackingMode(PQ_WIN eWindow, MS_U16 u16TabIdx_MADi);
MS_BOOL MDrv_PQ_GetBPPInfoFromMADi(PQ_WIN eWindow,
                                              MS_BOOL bMemFmt422,
                                              MS_U16 u16TabIdx_MADi,
                                              MS_U16 u16TabIdx_MemFormat,
                                              MS_U8 *pu8BitsPerPixel,
                                              PQ_DEINTERLACE_MODE *peDeInterlaceMode,
                                              MS_U8 *pu8FrameCount
                                              );
MS_BOOL MDrv_PQ_ChangeMemConfigFor3D(PQ_WIN eWindow,
                                            MS_BOOL bMemFmt422,
                                            MS_U16 *pu16TabIdx_MemFormat,
                                            MS_U16 *pu16TabIdx_444To422,
                                            MS_U16 *pu16TabIdx_422To444,
                                            MS_U8 *pu8BitsPerPixel,
                                            MS_U16 *pu16TabIdx_MADi_Motion,
                                            MS_U16 *pu16TabIdx_MADi
                                            );
MS_BOOL MDrv_PQ_ForceBPPForDynamicMemFmt(PQ_WIN eWindow, MS_BOOL bMemFmt422, MS_U8 *pu8BitsPerPixel);
MS_BOOL MDrv_PQ_SuggestFrameNum(PQ_WIN eWindow, MS_U16 u16TabIdx_MADi, MS_U8 u8FrameCount);

//-------------------------------------------------------------------------------------------------
/// Set Game mode, enable or disable
/// @param  eWindow                          \b IN: PQ Window Main or sub
/// @param  bEnable                           \b IN: enable or disable
/// @return TRUE: Success, FALSE: failed
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_SetGameMode(PQ_WIN eWindow, MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// Get current Game mode status
/// @param  eWindow                          \b IN: PQ Window Main or sub
/// @return the current status
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_GetGameMode_Status(PQ_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Set bypass mode, enable or disable
/// @param  eWindow                          \b IN: PQ Window Main or sub
/// @param  bEnable                           \b IN: enable or disable
/// @return TRUE: Success, FALSE: failed
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_SetBypassMode(PQ_WIN eWindow, MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// Get current bypass mode status
/// @param  eWindow                          \b IN: PQ Window Main or sub
/// @return the current status
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_GetBypassModeStatus(PQ_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Get Qmap Version
/// @param  eWindow                    \b IN:  PQ Window
/// @return                                 \b OUT: the Version of PQ
//-------------------------------------------------------------------------------------------------
char* MDrv_PQ_GetVersion(PQ_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// map inputsource type into index for QMap
/// @param  eWindow                          \b IN: PQ Window Main or sub
/// @param  enInputSourceType                   \b IN: the query input source type
/// @return corresponding index
//-------------------------------------------------------------------------------------------------
MS_U16 QM_InputSourceToIndex(PQ_WIN eWindow, MS_U8 enInputSourceType);


//-------------------------------------------------------------------------------------------------
/// ATSC trunk code customize functions
//-------------------------------------------------------------------------------------------------
///3D sensio mode
MS_BOOL MDrv_PQ_Get_SensioMode(void);
void  MDrv_PQ_Set_SensioMode(MS_BOOL bEnable);
//mirror ypbpr 1080i burst noise reduce
void  MDrv_PQ_Set_DIPF(void);//a6 only feature

//-------------------------------------------------------------------------------------------------
/// Get Load  Scaling Table Flags
///@return Load Scaling Table Flags
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_Get_NOLoadScalingTable(void);
//-------------------------------------------------------------------------------------------------
/// Enable or diable Load  Scaling Table Flags
/// @param  bEnable                          \b IN: Enable or disable Scaling Table Flags
//-------------------------------------------------------------------------------------------------
void  MDrv_PQ_Set_NOLoadScalingTable(MS_BOOL  bEnable);

//-------------------------------------------------------------------------------------------------
/// Adaptive tuning
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_AdaptiveTuning(void);

//-------------------------------------------------------------------------------------------------
/// Film Mode Any Candence Enable
/// @param  bEnable                           \b IN: enable or disable
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_FilmMode_AnyCandence_Enable(MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// Film Mode Any Candence Enable
/// @param  bEnable                           \b IN: enable or disable
/// @param  eLevel                           \b IN: PQ_CTRL_LEVEL
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_DBK_Control(MS_BOOL bEnable, PQ_CTRL_LEVEL eLevel);

//-------------------------------------------------------------------------------------------------
/// Film Mode Any Candence Enable
/// @param  bEnable                           \b IN: enable or disable
/// @param  eLevel                           \b IN: PQ_CTRL_LEVEL
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_DMS_Control(MS_BOOL bEnable, PQ_CTRL_LEVEL eLevel);

//-------------------------------------------------------------------------------------------------
/// ReStore To Default
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_ReStoreToDefault(void);

//-------------------------------------------------------------------------------------------------
/// Store Current Value
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_StoreCurrentValue(void);

//-------------------------------------------------------------------------------------------------
/// Get Current Motion Value
/// @return MS_U8 Motion Value
//-------------------------------------------------------------------------------------------------
MS_U8 MDrv_PQ_GetCurrentMotionValue(void);

//-------------------------------------------------------------------------------------------------
/// Set FPLL thresh mode registers
/// @param  u8PQWin                         \b IN: PQ Window Main or sub
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_SetFPLLThreshMode(MS_U8 u8PQWin);

//-------------------------------------------------------------------------------------------------
/// Film driver HW Ver1
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_FilmDriverHWVer1(void);

//-------------------------------------------------------------------------------------------------
/// Film driver HW Ver2
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_FilmDriverHWVer2(void);

//-------------------------------------------------------------------------------------------------
/// whether need to do vga force to 422 mode, for ucnr cbcr swap problem
/// @return need or not
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PQ_GetVGASubCaseForceTo422Mode(void);


BOOL MDrv_PQ_Is_SourceTypeMMPhoto(PQ_WIN eWindow);

MS_BOOL MDrv_PQ_EnableHDRMode(PQ_WIN eWindow ,MS_U16 u16GRuleLevelIndex);


#if (ENABLE_TEST_PATTERN)
//-------------------------------------------------------------------------------------------------
/// force PQ to set to special SrcType
/// @return need or not
//-------------------------------------------------------------------------------------------------
void MDrv_PQ_ForceSrcType(PQ_WIN eWindow, MS_U16 u16SrcType);

//-------------------------------------------------------------------------------------------------
/// Get SrcType for Test Pattern Mode
/// @return PQ SrcType
//-------------------------------------------------------------------------------------------------
MS_U16 MDrv_PQ_Get_Test_Pattern_SrcType(void);
#endif

#if( ENABLE_DEBUG_FILM )
void MDrv_PQ_Film_Print_Info(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* _DRVPQ_H_ */

