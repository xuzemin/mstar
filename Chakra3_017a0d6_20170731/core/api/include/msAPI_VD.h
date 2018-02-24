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

#ifndef __MSAPI_VD_H__
#define __MSAPI_VD_H__

#include "drvAVD.h"
//#include "msAPI_ATVSystem.h"
#include "drvPQ.h"


#ifdef _MSAPI_VD_C_
#define INTERFACE
#else
#define INTERFACE extern
#endif


//------------------------------------
//  AGC Configuration
//------------------------------------
// !!! These defines should be specified in the board head files.       !!!
// !!! Here are just for the default setting if they are not specified. !!!
// Select Gain Control Type (default value and should be defined in the board head file)

#if !defined(VD_GAIN_OF_RF_SEL)
#define VD_GAIN_OF_RF_SEL                       VD_USE_AUTO_GAIN
#endif
#if !defined(VD_GAIN_OF_AV_SEL)
#define VD_GAIN_OF_AV_SEL                       VD_USE_AUTO_GAIN
#endif

#if !defined(VD_GAIN_OF_RF)
  #if ( (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD)   \
      ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)     \
      ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON)     \
      ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET)    \
      ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON)     \
      ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA) )
    #define VD_GAIN_OF_RF                       0x58
  #else
    #define VD_GAIN_OF_RF                       0x4C
  #endif
#endif

#if !defined(VD_GAIN_OF_AV)
  #if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD)    \
     ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)      \
     ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON)      \
     ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET)     \
     ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON)      \
     ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA))
    #define VD_GAIN_OF_AV                       0x58
  #else
    #define VD_GAIN_OF_AV                       0x4C
  #endif
#endif

#if !defined(VD_COLOR_KILL_HIGH_BOUND)
    #define VD_COLOR_KILL_HIGH_BOUND            0x18
#endif

#if !defined(VD_COLOR_KILL_LOW_BOUND)
    #define VD_COLOR_KILL_LOW_BOUND             0x0E
#endif


#ifdef ENABLE_VD_PACH_IN_CHINA
    #define BK_AFEC_D4_DEFAULT          0x00
    #define BK_AFEC_D5_DEFAULT          0x60
    #define BK_AFEC_D8_DEFAULT          0x20
    #define BK_AFEC_D9_DEFAULT          0x00

    #define BK_AFEC_D0_ADDRESS          0x1035D0
    #define BK_AFEC_D4_ADDRESS          0x1035D4
    #define BK_AFEC_D5_ADDRESS          0x1035D5
    #define BK_AFEC_D7_ADDRESS          0x1035D7
    #define BK_AFEC_D8_ADDRESS          0x1035D8
    #define BK_AFEC_D9_ADDRESS          0x1035D9
    #define BK_AFEC_66_ADDRESS          0x103566
    #define BK_AFEC_6E_ADDRESS          0x10356E
    #define BK_AFEC_43_ADDRESS          0x103543
    #define BK_AFEC_44_ADDRESS          0x103544
    #define BK_AFEC_55_ADDRESS          0x103555
    #define BK_AFEC_CB_ADDRESS          0x1035CB
    #define BK_AFEC_CF_ADDRESS          0x1035CF
    #define BK_AFEC_A0_ADDRESS          0x1035A0
    #define BK_AFEC_A1_ADDRESS          0x1035A1
    #define BK_AFEC_4E_ADDRESS          0x10354E
    #define BK_AFEC_4F_ADDRESS          0x10354F
#endif


//#define VD_STABLE_COUNT             0

// VD DSP already debounce, so app no need debounce too many time
//#define ATV_DETECT_THRESHOLD        5
//#define CVBS_DETECT_THRESHOLD       4

//#define SIGNAL_CHANGE_THRESHOLD     10//40

//#define NO_SIGNAL_DETECT_THRESHOLD_SCAN 10
//#define NO_SIGNAL_DETECT_THRESHOLD      40


//------------------------------------
//  Misc.
//------------------------------------
/// SCART Source type
typedef enum
{
    E_SCART_SRC_TYPE_CVBS,         ///< SCART source type - CVBS
    E_SCART_SRC_TYPE_RGB,          ///< SCART source type - RGB
    E_SCART_SRC_TYPE_SVIDEO,      ///< SCART source type - SVIDEO
    E_SCART_SRC_TYPE_UNKNOWN      ///< SCART source type - Unknown
} SCART_SOURCE_TYPE;

typedef enum
{
    E_VIDEO_PERMANENT_MUTEOFF                = 0x00,
    E_VIDEO_PERMANENT_MUTEON                 = 0x01,
    E_VIDEO_MOMENT_MUTEOFF                   = 0x10,
    E_VIDEO_MOMENT_MUTEON                    = 0x11,
    E_VIDEO_BYLOCK_MUTEOFF                   = 0x20,
    E_VIDEO_BYLOCK_MUTEON                    = 0x21,
    E_VIDEO_BYPARENTAL_MUTEOFF               = 0x30,
    E_VIDEO_BYPARENTAL_MUTEON                = 0x31,
    E_VIDEO_DURING_LIMITED_TIME_MUTEOFF      = 0x40,
    E_VIDEO_DURING_LIMITED_TIME_MUTEON       = 0x41
} VIDEOMUTETYPE;

/// Aspect ratio type
typedef enum
{
    ARC4x3_FULL,                        ///< Aspect ratio 4:3 Full
    ARC14x9_LETTERBOX_CENTER,           ///< Aspect ratio 14:9 letterbox center
    ARC14x9_LETTERBOX_TOP,              ///< Aspect ratio 14:9 letterbox TOP
    ARC16x9_LETTERBOX_CENTER,           ///< Aspect ratio 16:9 letterbox center
    ARC16x9_LETTERBOX_TOP,              ///< Aspect ratio 16:9 letterbox TOP
    ARC_ABOVE16x9_LETTERBOX_CENTER,     ///< Aspect ratio Above 16:9 letterbox center
    ARC14x9_FULL_CENTER,                ///< Aspect ratio 14:9 full center
    ARC16x9_ANAMORPHIC,                 ///< Aspect ratio 16:9 anamorphic
    ARC_INVALID                         ///< Invalid Aspect ratio
} ASPECT_RATIO_TYPE;

typedef enum
{
    TTX_DISPLAY_INVALID_MODE,
    TTX_DISPLAY_UPDATE_MODE,
    TTX_DISPLAY_PICTURE_MODE,
    TTX_DISPLAY_MIX_MODE,
    TTX_DISPLAY_TEXT_MODE,
    TTX_DISPLAY_LOCK_MODE,
    TTX_DISPLAY_SUBTITLE_MODE
} TELETEXT_DISPLAY_MODE;

///Get sync type
typedef enum
{
    GET_SYNC_DIRECTLY,  ///< 0:get sync directly
    GET_SYNC_STABLE,    ///< 1:get sync stable
    GET_SYNC_VIRTUAL,   ///< 2: get sync virtually
} EN_GET_SYNC_TYPE;

/// color standard select
typedef enum
{
    SIG_NTSC,           ///< NTSC
    SIG_PAL,            ///< PAL
    SIG_SECAM,          ///< SECAM
    SIG_NTSC_443,       ///< NTSC 443
    SIG_PAL_M,          ///< PAL M
    SIG_PAL_NC,         ///< PAL NC
    SIG_NUMS,           ///< signal numbers

    SIG_NONE = -1
}EN_VD_SIGNALTYPE;

// Operation method
typedef enum
{
    OPERATIONMETHOD_MANUALLY,        ///< Operation method manually
    OPERATIONMETHOD_AUTOMATICALLY   ///< Operation method automatically
} OPERATIONMETHOD;


// Signal Swing (just used in normal mode)
#define VD_SIG_SWING_THRESH                        2

#if 0 //(CHIP_FAMILY_TYPE == CHIP_FAMILY_S7J)
    #define MSVD_HTOTAL_TYPE    AVD_PATCH_HTOTAL_1135
#else
    #define MSVD_HTOTAL_TYPE    AVD_PATCH_HTOTAL_1135_MUL_15
#endif

#if(0)
    //---------------------------------------------------------
    //------------------------ MUL 1135------------------------
    //---------------------------------------------------------

    #define MSVD_HSTART_NTSC_1135_MUL_15            0xF5
    #define MSVD_HSTART_PAL_1135_MUL_15             0xED
    #define MSVD_HSTART_SECAM_1135_MUL_15           0xca//0xE6
    #define MSVD_HSTART_NTSC_443_1135_MUL_15        0xDF
    #define MSVD_HSTART_PAL_M_1135_MUL_15           0x7D
    #define MSVD_HSTART_PAL_NC_1135_MUL_15          0x83//0xEA

    #define MSVD_VSTART_NTSC_1135_MUL_15            0x12// 0x0A
    #define MSVD_VSTART_PAL_1135_MUL_15             0x0D //0x1B//0x0D
    #define MSVD_VSTART_SECAM_1135_MUL_15           0x0A
    #define MSVD_VSTART_NTSC_443_1135_MUL_15        0x06
    #define MSVD_VSTART_PAL_M_1135_MUL_15           0x09
    #define MSVD_VSTART_PAL_NC_1135_MUL_15          0x10

    #define VD_HT_NTSC_1135_MUL_15                  (1135L*3/2)
    #define VD_HT_PAL_1135_MUL_15                   (1135L*3/2)
    #define VD_HT_SECAM_1135_MUL_15                 (1135L*3/2)
    #define VD_HT_NTSC_443_1135_MUL_15              (1135L*3/2)
    #define VD_HT_PAL_M_1135_MUL_15                 (1135L*3/2)
    #define VD_HT_PAL_NC_1135_MUL_15                (1135L*3/2)
    #define VD_HT_PAL_60_1135_MUL_15                VD_HT_NTSC_443_1135_MUL_15

    #define MSVD_HACTIVE_NTSC_1135_MUL_15           (((MS_U32)720*VD_HT_NTSC_1135_MUL_15+429)/858)
    #define MSVD_HACTIVE_PAL_1135_MUL_15            (((MS_U32)720*VD_HT_PAL_1135_MUL_15+432)/864)
    #define MSVD_HACTIVE_SECAM_1135_MUL_15          (((MS_U32)720*VD_HT_SECAM_1135_MUL_15+432)/864)
    #define MSVD_HACTIVE_NTSC_443_1135_MUL_15       (((MS_U32)720*VD_HT_NTSC_443_1135_MUL_15+432)/864)
    #define MSVD_HACTIVE_PAL_M_1135_MUL_15          (((MS_U32)720*VD_HT_PAL_M_1135_MUL_15+429)/858)
    #define MSVD_HACTIVE_PAL_NC_1135_MUL_15         (((MS_U32)720*VD_HT_PAL_NC_1135_MUL_15+429)/858)
    #define MSVD_HACTIVE_PAL_60_1135_MUL_15         MSVD_HACTIVE_NTSC_443_1135_MUL_15


    //---------------------------------------------------------
    //------------------------ 1135 ------------------------
    //---------------------------------------------------------

    #define MSVD_HSTART_NTSC_1135            96
    #define MSVD_HSTART_PAL_1135             97// 99
    #define MSVD_HSTART_SECAM_1135           105
    #define MSVD_HSTART_NTSC_443_1135        90
    #define MSVD_HSTART_PAL_M_1135           97
    #define MSVD_HSTART_PAL_NC_1135          94//0xEA

    #define MSVD_VSTART_NTSC_1135            0x08
    #define MSVD_VSTART_PAL_1135             0x0F
    #define MSVD_VSTART_SECAM_1135           0x0D
    #define MSVD_VSTART_NTSC_443_1135        0x07
    #define MSVD_VSTART_PAL_M_1135           0x08
    #define MSVD_VSTART_PAL_NC_1135          0x10

    #define VD_HT_NTSC_1135                  (1135L)
    #define VD_HT_PAL_1135                   (1135L)
    #define VD_HT_SECAM_1135                 (1135L)
    #define VD_HT_NTSC_443_1135              (1135L)
    #define VD_HT_PAL_M_1135                 (1135L)
    #define VD_HT_PAL_NC_1135                (1135L)
    #define VD_HT_PAL_60_1135                VD_HT_NTSC_443_1135

    #define MSVD_HACTIVE_NTSC_1135           (((MS_U32)720*VD_HT_NTSC_1135+429)/858)
    #define MSVD_HACTIVE_PAL_1135            (((MS_U32)720*VD_HT_PAL_1135+432)/864)
    #define MSVD_HACTIVE_SECAM_1135          (((MS_U32)720*VD_HT_SECAM_1135+432)/864)
    #define MSVD_HACTIVE_NTSC_443_1135       (((MS_U32)720*VD_HT_NTSC_443_1135+432)/864)
    #define MSVD_HACTIVE_PAL_M_1135          (((MS_U32)720*VD_HT_PAL_M_1135+429)/858)
    #define MSVD_HACTIVE_PAL_NC_1135         (((MS_U32)720*VD_HT_PAL_NC_1135+429)/858)
    #define MSVD_HACTIVE_PAL_60_1135         MSVD_HACTIVE_NTSC_443_1135

    //---------------------------------------------------------
    //------------------------ Dynamic ------------------------
    //---------------------------------------------------------
    #define MSVD_HSTART_NTSC_DYNAMIC            0xF5
    #define MSVD_HSTART_PAL_DYNAMIC             0xED
    #define MSVD_HSTART_SECAM_DYNAMIC           0xE6
    #define MSVD_HSTART_NTSC_443_DYNAMIC        0xDF
    #define MSVD_HSTART_PAL_M_DYNAMIC           0x7D
    #define MSVD_HSTART_PAL_NC_DYNAMIC          0x83//0xEA

    #define MSVD_VSTART_NTSC_DYNAMIC            0x12// 0x0A
    #define MSVD_VSTART_PAL_DYNAMIC             0x0D //0x1B//0x0D
    #define MSVD_VSTART_SECAM_DYNAMIC           0x0A
    #define MSVD_VSTART_NTSC_443_DYNAMIC        0x06
    #define MSVD_VSTART_PAL_M_DYNAMIC           0x09
    #define MSVD_VSTART_PAL_NC_DYNAMIC          0x10

    #define VD_HT_NTSC_DYNAMIC                  (910L)
    #define VD_HT_PAL_DYNAMIC                   (1135L)
    #define VD_HT_SECAM_DYNAMIC                 (1097L)
    #define VD_HT_NTSC_443_DYNAMIC              (1127L)
    #define VD_HT_PAL_M_DYNAMIC                 (909L)
    #define VD_HT_PAL_NC_DYNAMIC                (917L)
    #define VD_HT_PAL_60_DYNAMIC                VD_HT_NTSC_443_DYNAMIC


    #define MSVD_HACTIVE_NTSC_DYNAMIC           (((MS_U32)720*VD_HT_NTSC_DYNAMIC+429)/858)
    #define MSVD_HACTIVE_PAL_DYNAMIC            (((MS_U32)720*VD_HT_PAL_DYNAMIC+432)/864)
    #define MSVD_HACTIVE_SECAM_DYNAMIC          (((MS_U32)720*VD_HT_SECAM_DYNAMIC+432)/864)
    #define MSVD_HACTIVE_NTSC_443_DYNAMIC       (((MS_U32)720*VD_HT_NTSC_443_DYNAMIC+432)/864)
    #define MSVD_HACTIVE_PAL_M_DYNAMIC          (((MS_U32)720*VD_HT_PAL_M_DYNAMIC+429)/858)
    #define MSVD_HACTIVE_PAL_NC_DYNAMIC         (((MS_U32)720*VD_HT_PAL_NC_DYNAMIC+429)/858)
    #define MSVD_HACTIVE_PAL_60_DYNAMIC         MSVD_HACTIVE_NTSC_443_DYNAMIC

#endif


#if (MSVD_HTOTAL_TYPE==AVD_PATCH_HTOTAL_1135_MUL_15)
    #define MSVD_HSTART_NTSC            0xF5
    #define MSVD_HSTART_PAL             0xED
    #define MSVD_HSTART_SECAM           0xca//0xE6
    #define MSVD_HSTART_NTSC_443        0xDF
    #define MSVD_HSTART_PAL_M           0x7D
    #define MSVD_HSTART_PAL_NC          0x83//0xEA

    #define MSVD_VSTART_NTSC            0x12// 0x0A
    #define MSVD_VSTART_PAL             0x0D //0x1B//0x0D
    #define MSVD_VSTART_SECAM           0x0A
    #define MSVD_VSTART_NTSC_443        0x06
    #define MSVD_VSTART_PAL_M           0x09
    #define MSVD_VSTART_PAL_NC          0x10

    #define VD_HT_NTSC                  (1135L*3/2)
    #define VD_HT_PAL                   (1135L*3/2)
    #define VD_HT_SECAM                 (1135L*3/2)
    #define VD_HT_NTSC_443              (1135L*3/2)
    #define VD_HT_PAL_M                 (1135L*3/2)
    #define VD_HT_PAL_NC                (1135L*3/2)
    #define VD_HT_PAL_60                VD_HT_NTSC_443
#elif (MSVD_HTOTAL_TYPE==AVD_PATCH_HTOTAL_1135)
  #if 0
    #define MSVD_HSTART_NTSC            (MS_U16)0xF5*2/3
    #define MSVD_HSTART_PAL             (MS_U16)0xED*2/3
    #define MSVD_HSTART_SECAM           (MS_U16)0xE6*2/3
    #define MSVD_HSTART_NTSC_443        (MS_U16)0xDF*2/3
    #define MSVD_HSTART_PAL_M           (MS_U16)0x7D*2/3
    #define MSVD_HSTART_PAL_NC          (MS_U16)0x83*2/3 //0xEA

    #define MSVD_HSTART_NTSC            83
    #define MSVD_HSTART_PAL             82
    #define MSVD_HSTART_SECAM           77
    #define MSVD_HSTART_NTSC_443        75
    #define MSVD_HSTART_PAL_M           83
    #define MSVD_HSTART_PAL_NC          80//0xEA

    #define MSVD_VSTART_NTSC            0x12// 0x0A
    #define MSVD_VSTART_PAL             0x0D //0x1B//0x0D
    #define MSVD_VSTART_SECAM           0x0A
    #define MSVD_VSTART_NTSC_443        0x06
    #define MSVD_VSTART_PAL_M           0x09
    #define MSVD_VSTART_PAL_NC          0x10
#else
// calibrated with TG39 Marker pattern, full hd panel, 20100203
    #define MSVD_HSTART_NTSC            96
    #define MSVD_HSTART_PAL            97// 99
    #define MSVD_HSTART_SECAM           105
    #define MSVD_HSTART_NTSC_443        90
    #define MSVD_HSTART_PAL_M           91
    #define MSVD_HSTART_PAL_NC          90//0xEA

    #define MSVD_VSTART_NTSC            0x08
    #define MSVD_VSTART_PAL             0x0F
    #define MSVD_VSTART_SECAM           0x0D
    #define MSVD_VSTART_NTSC_443        0x07
    #define MSVD_VSTART_PAL_M           0x08
    #define MSVD_VSTART_PAL_NC          0x10
#endif
    #define VD_HT_NTSC                  (1135L)
    #define VD_HT_PAL                   (1135L)
    #define VD_HT_SECAM                 (1135L)
    #define VD_HT_NTSC_443              (1135L)
    #define VD_HT_PAL_M                 (1135L)
    #define VD_HT_PAL_NC                (1135L)
    #define VD_HT_PAL_60                VD_HT_NTSC_443
#elif (MSVD_HTOTAL_TYPE==AVD_PATCH_HTOTAL_DYNAMIC)
    #define MSVD_HSTART_NTSC            0xF5
    #define MSVD_HSTART_PAL             0xED
    #define MSVD_HSTART_SECAM           0xE6
    #define MSVD_HSTART_NTSC_443        0xDF
    #define MSVD_HSTART_PAL_M           0x7D
    #define MSVD_HSTART_PAL_NC          0x83//0xEA

    #define MSVD_VSTART_NTSC            0x12// 0x0A
    #define MSVD_VSTART_PAL             0x0D //0x1B//0x0D
    #define MSVD_VSTART_SECAM           0x0A
    #define MSVD_VSTART_NTSC_443        0x06
    #define MSVD_VSTART_PAL_M           0x09
    #define MSVD_VSTART_PAL_NC          0x10

    #define VD_HT_NTSC                  (910L)
    #define VD_HT_PAL                   (1135L)
    #define VD_HT_SECAM                 (1097L)
    #define VD_HT_NTSC_443              (1127L)
    #define VD_HT_PAL_M                 (909L)
    #define VD_HT_PAL_NC                (917L)
    #define VD_HT_PAL_60                VD_HT_NTSC_443
#else // user mode
    #define MSVD_HSTART_NTSC            0xF5
    #define MSVD_HSTART_PAL             0xED
    #define MSVD_HSTART_SECAM           0xE6
    #define MSVD_HSTART_NTSC_443        0xDF
    #define MSVD_HSTART_PAL_M           0x7D
    #define MSVD_HSTART_PAL_NC          0x83//0xEA

    #define MSVD_VSTART_NTSC            0x12// 0x0A
    #define MSVD_VSTART_PAL             0x0D //0x1B//0x0D
    #define MSVD_VSTART_SECAM           0x0A
    #define MSVD_VSTART_NTSC_443        0x06
    #define MSVD_VSTART_PAL_M           0x09
    #define MSVD_VSTART_PAL_NC          0x10

    #define VD_HT_NTSC                  (1135L*3/2)
    #define VD_HT_PAL                   (1135L*3/2)
    #define VD_HT_SECAM                 (1135L*3/2)
    #define VD_HT_NTSC_443              (1135L*3/2)
    #define VD_HT_PAL_M                 (1135L*3/2)
    #define VD_HT_PAL_NC                (1135L*3/2)
    #define VD_HT_PAL_60                VD_HT_NTSC_443
#endif

#define MSVD_HACTIVE_NTSC               (((MS_U32)720*VD_HT_NTSC+429)/858)
#define MSVD_HACTIVE_PAL                (((MS_U32)720*VD_HT_PAL+432)/864)
#define MSVD_HACTIVE_SECAM              (((MS_U32)720*VD_HT_SECAM+432)/864)
#define MSVD_HACTIVE_NTSC_443           (((MS_U32)720*VD_HT_NTSC_443+432)/864)
#define MSVD_HACTIVE_PAL_M              (((MS_U32)720*VD_HT_PAL_M+429)/858)
#define MSVD_HACTIVE_PAL_NC             (((MS_U32)720*VD_HT_PAL_NC+429)/858)
#define MSVD_HACTIVE_PAL_60             MSVD_HACTIVE_NTSC_443

//------------------------------------
//  H Sensitivity Configuration
//------------------------------------
// for normal mode
#if !defined(VD_HSEN_NORMAL_DETECT_WIN_BEFORE_LOCK)
#define VD_HSEN_NORMAL_DETECT_WIN_BEFORE_LOCK      0x08
#endif
#if !defined(VD_HSEN_NOAMRL_DETECT_WIN_AFTER_LOCK)
#define VD_HSEN_NOAMRL_DETECT_WIN_AFTER_LOCK       0x08
#endif
#if !defined(VD_HSEN_NORMAL_CNTR_FAIL_BEFORE_LOCK)
#define VD_HSEN_NORMAL_CNTR_FAIL_BEFORE_LOCK       0x0F
#endif
#if !defined(VD_HSEN_NORMAL_CNTR_SYNC_BEFORE_LOCK)
#define VD_HSEN_NORMAL_CNTR_SYNC_BEFORE_LOCK       0x10
#endif
#if !defined(VD_HSEN_NORMAL_CNTR_SYNC_AFTER_LOCK)
#define VD_HSEN_NORMAL_CNTR_SYNC_AFTER_LOCK        0x1C
#endif

#if 0 //((FRONTEND_TUNER_TYPE == MxL_601SI_TUNER) || (FRONTEND_TUNER_TYPE == MxL_661SI_TUNER))
#if !defined(VD_HSEN_CHAN_SCAN_DETECT_WIN_BEFORE_LOCK)
#define VD_HSEN_CHAN_SCAN_DETECT_WIN_BEFORE_LOCK   0x02 // 0x04 // 0x03
#endif
#if !defined(VD_HSEN_CHAN_SCAN_DETECT_WIN_AFTER_LOCK)
#define VD_HSEN_CHAN_SCAN_DETECT_WIN_AFTER_LOCK    0x02 // 0x04 // 0x03
#endif
#if !defined(VD_HSEN_CHAN_SCAN_CNTR_FAIL_BEFORE_LOCK)
#define VD_HSEN_CHAN_SCAN_CNTR_FAIL_BEFORE_LOCK    0x08 // 0x08 // 0x08
#endif
#if !defined(VD_HSEN_CHAN_SCAN_CNTR_SYNC_BEFORE_LOCK)
#define VD_HSEN_CHAN_SCAN_CNTR_SYNC_BEFORE_LOCK    0x30 // 0x10 // 0x10
#endif
#if !defined(VD_HSEN_CHAN_SCAN_CNTR_SYNC_AFTER_LOCK)
#define VD_HSEN_CHAN_SCAN_CNTR_SYNC_AFTER_LOCK     0x18 // 0x1C // 0x05
#endif
#else
#if !defined(VD_HSEN_CHAN_SCAN_DETECT_WIN_BEFORE_LOCK)
#define VD_HSEN_CHAN_SCAN_DETECT_WIN_BEFORE_LOCK   0x04 // 0x03
#endif
#if !defined(VD_HSEN_CHAN_SCAN_DETECT_WIN_AFTER_LOCK)
#define VD_HSEN_CHAN_SCAN_DETECT_WIN_AFTER_LOCK    0x04 // 0x03
#endif
#if !defined(VD_HSEN_CHAN_SCAN_CNTR_FAIL_BEFORE_LOCK)
#define VD_HSEN_CHAN_SCAN_CNTR_FAIL_BEFORE_LOCK    0x08 // 0x08
#endif
#if !defined(VD_HSEN_CHAN_SCAN_CNTR_SYNC_BEFORE_LOCK)
#define VD_HSEN_CHAN_SCAN_CNTR_SYNC_BEFORE_LOCK    0x10 // 0x10
#endif
#if !defined(VD_HSEN_CHAN_SCAN_CNTR_SYNC_AFTER_LOCK)
#define VD_HSEN_CHAN_SCAN_CNTR_SYNC_AFTER_LOCK     0x1C // 0x05
#endif
#endif
//******************************************************************************
// Public functions.
//******************************************************************************
#if ENABLE_ATSC
U16 msAPI_AVD_GetStatus ( void );
void msAPI_AVD_Parameter_Initial(void);
#endif

void msAPI_AVD_Exit(void);
void msAPI_AVD_InitVideoSystem(void);
void msAPI_AVD_VideoProcessor(void);
AVD_VideoStandardType msAPI_AVD_GetVideoStandard(void);
BOOLEAN msAPI_AVD_IsVideoFormatChanged(void);
void msAPI_AVD_SetIsVideoFormatChangedAsFalse(void);  //20100330EL

BOOL msAPI_AVD_Is_VDStable(void);


BOOLEAN msAPI_AVD_IsVideoInputChanged(void);
BOOLEAN msAPI_AVD_CheckLockAudioCarrier(void);
BOOLEAN msAPI_AVD_CheckFalseChannel(void);
void msAPI_AVD_StartAutoStandardDetection(void);
void msAPI_AVD_ForceVideoStandard(AVD_VideoStandardType eVideoStandardType);
void msAPI_AVD_SetForceVideoStandardFlag(BOOLEAN bEnable);
BOOLEAN msAPI_AVD_GetForceVideoStandardFlag(void);

//BOOLEAN IsVDHasSignal(void);
#define IsVDHasSignal()     msAPI_AVD_IsHasStableSignal()
BOOLEAN msAPI_AVD_IsHasStableSignal(void);

AVD_VideoStandardType msAPI_AVD_GetResultOfAutoStandardDetection(void);

ASPECT_RATIO_TYPE msAPI_AVD_GetAspectRatioCode(void);
BOOLEAN msAPI_AVD_IsAspectRatioChanged(void);
void msAPI_AVD_WaitForVideoSyncLock(void);
AVD_InputSourceType msAPI_AVD_GetVideoSource(void);
void msAPI_AVD_SetMuxPower(AVD_InputSourceType eSource);
void msAPI_AVD_SetVideoSource(AVD_InputSourceType eSource);
void msAPI_AVD_DetectVideoStandard(OPERATIONMETHOD eOperationMethod);
AVD_VideoFreq msAPI_AVD_GetVerticalFreq(void);
BOOLEAN msAPI_AVD_IsSyncChanged(void);
BOOLEAN msAPI_AVD_IsSyncLocked(void); // H Sync locked
BOOLEAN msAPI_AVD_UpdateAutoAVState(void);
BOOLEAN msAPI_AVD_IsAutoAVActive(AVD_AutoAVSourceType eAutoAVSource);
void msAPI_AVD_TurnOffAutoAV(void);
void msAPI_AVD_SwitchAutoAV(void);
SCART_SOURCE_TYPE msAPI_AVD_GetScart1SrcType(void);
BOOLEAN msAPI_AVD_IsScart1SourceTypeChanged(void);
void msAPI_AVD_ClearAspectRatio(void);
void msAPI_AVD_SuppressAutoAV(void);
void msAPI_AVD_SetForcedFreeRun(BOOLEAN bEnable);
void msAPI_AVD_SetHsyncDetectionForTuning(BOOLEAN bEnable);
void msAPI_AVD_3DCombSpeedup(void);
void msAPI_AVD_SetChannelChange(void);
U8 msAPI_AVD_CheckStdDetStableCnt(void);
void msAPI_AVD_CheckStdDetStableReset(void);
void msAPI_AVD_SetFWStatus(BOOLEAN bFWStatus);
BOOLEAN msAPI_AVD_IsScartRGB(void);
AVD_VideoStandardType msAPI_AVD_GetStandardDetection(void);
AVD_VideoStandardType msAPI_AVD_GetCurrentVideoStandard(void);

void msAPI_AVD_SetRegFromDSP(void);
void msAPI_AVD_SetPatchOption(void);
U16 msAPI_AVD_CheckStatusLoop(void);
void msAPI_AVD_GetCaptureWindow(MS_WINDOW_TYPE *stCapWin, EN_VD_SIGNALTYPE enVideoSystem, MS_BOOL IsUseExtVD);
void msAPI_AVD_GetCaptureWindowByPQ(MS_WINDOW_TYPE *stCapWin, EN_VD_SIGNALTYPE enVideoSystem, MS_PQ_VD_Sampling_Info *pInfo);
void msAPI_AVD_Set_ForceVideoStd_CountDownTime(U32 u32Time);

#if (TV_FREQ_SHIFT_CLOCK)
void msAPI_AVD_ShiftClk(AVD_ATV_CLK_TYPE eShiftMode);
#endif
EN_VD_SIGNALTYPE mvideo_vd_get_videosystem(void);
void mvideo_vd_set_videosystem(EN_VD_SIGNALTYPE ucVideoSystem);

U16 msAPI_AVD_Get_LatchStatus(void);

U16 msAPI_Scaler_VD_GetVTotal(SCALER_WIN eWindow, INPUT_SOURCE_TYPE_t eCurrentSrc,EN_GET_SYNC_TYPE enGetSyncType, U16 u16HFreqX10);
U16 msAPI_Scaler_VD_GetHPeriod(SCALER_WIN eWindow, INPUT_SOURCE_TYPE_t eCurrentSrc, EN_GET_SYNC_TYPE enGetSyncType);

const char* msAPI_AVD_Get_StdString(AVD_VideoStandardType eVDStd);

BOOL msAPI_AVD_Is_Input50Hz(void);

void msAPI_AVD_PrintInfo(void);

//
/******************************************************************************/
//

#define DEBUG_VD_FLOW   0

#if( DEBUG_VD_FLOW )
#define msAPI_AVD_SetVideoStandard(std) do {    \
    printf("\n%s %s Line %d: Call msAPI_AVD_SetVideoStandard()\n", __FILE__, __FUNCTION__, __LINE__);   \
    msAPI_AVD_SetVideoStandard_2(std); \
} while(0)
#else
#define msAPI_AVD_SetVideoStandard(std) do {                 \
    msAPI_AVD_SetVideoStandard_2(std);                       \
} while(0)
#endif
void msAPI_AVD_SetVideoStandard_2(AVD_VideoStandardType eStandard);


#if( DEBUG_VD_FLOW )
#define msAPI_AVD_StartAutoStandardDetection(void) do {                 \
    printf("\n %lu:%s ", __LINE__, __FILE__);                           \
    msDebug_ANSI_SetColorText(E_FONT_COLOR_WHITE);                      \
    msDebug_ANSI_SetColorText(E_FONT_COLOR_YELLOW);                     \
    printf(" [VD] Auto Detect at %u\n", g_Debug_u32Time_ChangeChannel); \
    msDebug_ANSI_AllAttrOffText();                                      \
    msAPI_AVD_StartAutoStandardDetection_2();                           \
} while(0)
#else
#define msAPI_AVD_StartAutoStandardDetection(void) do {                 \
    msAPI_AVD_StartAutoStandardDetection_2(void);                       \
} while(0)
#endif
INTERFACE void msAPI_AVD_StartAutoStandardDetection_2(void);



#if( DEBUG_VD_FLOW )
#define msAPI_AVD_ForceVideoStandard(eVideoStandardType) do {                                           \
    printf("\n %lu:%s ", __LINE__, __FILE__);                                                           \
    msDebug_ANSI_SetColorText(E_FONT_COLOR_WHITE);                                                      \
    msDebug_ANSI_SetColorText(E_FONT_COLOR_YELLOW);                                                     \
    printf(" [VD] force = %s(%u) \n", msAPI_AVD_Get_StdString(eVideoStandardType), eVideoStandardType); \
    msDebug_ANSI_AllAttrOffText();                                                                      \
    msAPI_AVD_ForceVideoStandard_2(eVideoStandardType);                                                 \
} while(0)
#else
#define msAPI_AVD_ForceVideoStandard(eVideoStandardType) do {     \
    msAPI_AVD_ForceVideoStandard_2(eVideoStandardType);           \
} while(0)
#endif
INTERFACE void msAPI_AVD_ForceVideoStandard_2(AVD_VideoStandardType eVideoStandardType);
INTERFACE BOOLEAN msAPI_AVD_GetVDisStable(void);

//
/******************************************************************************/
//

#define ENABLE_SCART_MONITOR    1

#if(ENABLE_SCART_MONITOR)
void msAPI_AVD_Scart_Monitor(void);
#endif



//
/******************************************************************************/
//

#undef INTERFACE

#endif // __msAPI_AVD_H__

