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
// (MStar Confidential Information) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define MAPP_SCALER_C

/******************************************************************************/
// [SC_PATCH_03]
// Date: 20090112
// Descriptions: fix right boundary green line problem due to CTI will refer to
// green points outside right boundary of capture range.
//
/******************************************************************************/
/*             Header Files                                                   */
/* ****************************************************************************/

//Env header
//#include <string.h>
#include "datatype.h"
#include "debug.h"
#include "Board.h"
#include "Panel.h"

#include "Utl.h"

#include "color_reg.h"
#if (ENABLE_MHL == ENABLE)
    #include"Mhl.h"
#endif


//Utopia - DRV layer
#include "hal_misc.h"

#include "drvGPIO.h"
#include "drvXC_HDMI_if.h"
#include "drvCPU.h"
#include "drvPQ.h"
#include "drvPQ_Define.h"
//#include "drvPWM.h"
#include "drvGlobal.h"

//Utopia - API layer header
#include "apiXC.h"
#include "apiXC_Sys.h"
#include "apiXC_Hdmi.h"
#include "apiXC_Adc.h"
#include "apiXC_ModeParse.h"
#include "apiXC_Cus.h"
#include "apiXC_Ace.h"
#include "apiXC_Auto.h"
#include "apiXC_PCMonitor.h"
#include "apiXC_Dlc.h"
#include "apiPNL.h"


//msAPI layer
#include "msAPI_Global.h"
#include "msAPI_Mode.h"
#include "msAPI_Video.h"
#include "msAPI_Timer.h"
#include "msAPI_VD.h"
#include "msAPI_Tuning.h"
#if(ENABLE_NEW_AUTO_NR == 1)
   #include "msAPI_NR.h"
#endif

#if ENABLE_DBC
#include "apiXC_DBC.h"
#endif

//MApp layer header
#include "MApp_GlobalSettingSt.h"
#include "MApp_DataBase.h"
#include "MApp_PCMode.h"
#include "MApp_GlobalVar.h"
#include "MApp_Scaler.h"
#include "MApp_XC_Sys.h"
#include "MApp_XC_PQ.h"
#include "MApp_MVDMode.h"
#include "MApp_SaveData.h"
#include "MApp_GlobalFunction.h"
#if MHEG5_ENABLE
#include "MApp_MHEG5_Main.h"
#endif
#include "MApp_TopStateMachine.h"
#if ENABLE_DMP
#include "mapp_mplayer.h"
#endif
#if (ENABLE_PIP)
#include "MApp_InputSource.h"
#include "MApp_PIP.h"
#endif
#include "mapp_videoplayer.h"

//UI layer header
//#include "MApp_ZUI_Main.h"
//#include "ZUI_tables_h.inl"

#if ENABLE_3D_PROCESS
#if (ENABLE_MFC_6M20 || ENABLE_MFC_6M30)
#include "ZUI_exefunc.h"
#endif
#endif

#if ENABLE_ATSC
#include "MApp_VChip.h"
#endif

//Device layer
#if (ENABLE_TCON_IN8903_PROCESS)
#include "drvTcon_Inx8903.h"
#endif

#if (LD_ENABLE)
#include "msAPI_LD.h"
#endif

#if( CHAKRA3_AUTO_TEST )
#include "MApp_AutoTest.h"
#endif


/******************************************************************************/
/*                     Definition                                             */
/* ****************************************************************************/

#define NEWCROPMSG(x)                   //x
#define MSG(x)                          //x
#define DEBUG_SET_WIN(x)                //x
#define DEBUG_CAP_WIN(x)                //x
#define DEBUG_ASPECT_RATIO(x)           //x
#define DEBUG_SCALER_FLOW(x)            //x
#define DEBUG_SCALER_INPUT_TIMING(x)    //x
#define DEBUG_OVERSCAN(x)               //x

#define MENU_3D_DBG(x)                 // x
#if 0
    #define DEBUG_3D(x)  do { \
        msDebug_ANSI_SetColorText(E_FONT_COLOR_GREEN); \
        msDebug_ANSI_SetColorText(E_FONT_ATTRIBUTE_BOLD); \
        x ; \
        msDebug_ANSI_AllAttrOffText();  \
    } while(0)
#else
    #define DEBUG_3D(x)                 //x
#endif
#define DEBUG_3D_INPUT(x)               //x


#define VERIFY_SCALER_FPGA      0

//******************************************************************************
//          Structures
//******************************************************************************

typedef struct
{
    U16 u16H_CapStart;          ///< Capture window H start
    U16 u16V_CapStart;          ///< Capture window V start

    U8 u8HCrop_Left;    // H Crop Left
    U8 u8HCrop_Right;    // H crop Right
    U8 u8VCrop_Up;      // V Crop Up
    U8 u8VCrop_Down;      // V Crop Down
} MS_VIDEO_Window_Info;

typedef enum
{
    E_YPbPr480i_60,         // 0
    E_YPbPr480p_60,        // 1
    E_YPbPr576i_50,         // 2
    E_YPbPr576p_50,        // 3
    E_YPbPr720p_60,        // 4
    E_YPbPr720p_50,        // 5
    E_YPbPr1080i_60,       // 6
    E_YPbPr1080i_50,       // 7
    E_YPbPr1080p_60,      // 8
    E_YPbPr1080p_50,      // 9
    E_YPbPr1080p_30,      // 10
    E_YPbPr1080p_24,      // 11
    E_YPbPr1080p_25,      // 12
    E_YPbPr720p_25,       // 13
    E_YPbPr720p_30,       // 14
    #if (SUPPORT_EURO_HDTV)
     E_YPbPr108oi_25,      // 15
     #endif
    E_YPbPr_MAX,   // 16
}MAX_YPbPr_Resolution_Info;

typedef enum
{
    E_HDMI480i_60,          // 0
    E_HDMI480p_60,          // 1
    E_HDMI576i_50,          // 2
    E_HDMI576p_50,          // 3
    E_HDMI720p_60,          // 4
    E_HDMI720p_50,          // 5
    E_HDMI1080i_60,         // 6
    E_HDMI1080i_50,         // 7
    E_HDMI1080p_60,         // 8
    E_HDMI1080p_50,         // 9
    E_HDMI1080p_30,         // 10
    E_HDMI1080p_24,         // 11

    E_HDMI1440x480i_60,     // 12
    E_HDMI1440x480p_60,     // 13
    E_HDMI1440x576i_50,     // 14
    E_HDMI1440x576p_50,     // 15

    E_HDMI640x480i_60,      // 16
    E_HDMI640x480P_60,      // 17
    E_HDMI_MAX,             // 18

}MAX_HDMI_Resolution_Info;
/*
typedef enum
{
    E_AR_DEFAULT = 0,  // 0
    E_AR_16x9,              // 1
    E_AR_4x3,                // 2
    E_AR_AUTO,             // 3
    E_AR_Panorama,     // 4
    E_AR_JustScan,       // 5
    E_AR_Zoom2,          // 6
    E_AR_Zoom1,          // 7

    E_AR_MAX,
}MAX_AspectRatio_Info;
*/

#if ENABLE_3D_PROCESS
typedef struct
{
    /// 3D input type
    E_XC_3D_INPUT_MODE    enInput3DMode;
    /// 3D output type
    E_XC_3D_OUTPUT_MODE   enOutput3DMode;
}ST_MAPI_3D_INFO;

ST_MAPI_3D_INFO m_st3DInfo;
MS_BOOL _bLRSwitch = FALSE;
#endif

#if ENABLE_AUTOTEST
extern BOOLEAN g_bAutobuildDebug;
#endif
extern BOOLEAN m_bFLG_PREVIEW;

//------------------------------------------------------------------------------
// ARC
//------------------------------------------------------------------------------
#define ARC_14X19_OVS_UP                62
#define ARC_14X19_OVS_DOWN              62

#define ARC_CINEMA_OVS_H                100
#define ARC_CINEMA_OVS_V                100

//------------------------------------------------------------------------------
// Over Scan
//------------------------------------------------------------------------------
#define OVERSCAN_DEFAULT_H              30 // 1.0%
#define OVERSCAN_DEFAULT_V              35 // 1.0%

//------------------------------------------------------------------------------
// VD Timing Window (Table)
//------------------------------------------------------------------------------

U8 SV_OffsetH[] =
{
    0x10,   //NTSC
   0x12,// 0x0E,   //PAL
    0x00,   //SECAM
    0x0D,   //NTSC-443/PAL-60
    0x12,   //PAL-M
    0x12    //PAL-NC
};

U8 SV_OffsetV[] =
{
    0x82,   //NTSC
    0x82,   //PAL
    0x0,    //SECAM
    0x82,   //NTSC-443/PAL-60
    0x83,   //PAL-M
    0x82    //PAL-NC
};

MS_VIDEO_Window_Info CVBS_WinInfo[][E_AR_MAX] =
{
#if 1//For HD Panel overscan
    {  //NTSC, 0
        {MSVD_HSTART_NTSC, MSVD_VSTART_NTSC,   46, 37, 28, 28},  // Default
        {MSVD_HSTART_NTSC, MSVD_VSTART_NTSC,   46, 37, 28, 28},  // 16:9
        {MSVD_HSTART_NTSC, MSVD_VSTART_NTSC,   46, 37, 28, 28},  // 4:3
        {MSVD_HSTART_NTSC, MSVD_VSTART_NTSC,   46, 37, 28, 28},  // Auto
        {MSVD_HSTART_NTSC, MSVD_VSTART_NTSC,   46, 37, 28, 28},  // Panorama
        {MSVD_HSTART_NTSC, MSVD_VSTART_NTSC,   46, 37, 28, 28},  // Just Scan
        {MSVD_HSTART_NTSC, MSVD_VSTART_NTSC,   46, 37, 28, 28},  // Zoom2
        {MSVD_HSTART_NTSC, MSVD_VSTART_NTSC,   46, 37, 28, 28},  // Zoom1
    },
    {  //PAL, 1
        {MSVD_HSTART_PAL, MSVD_VSTART_PAL,   49, 36, 18, 18},  // Default
        {MSVD_HSTART_PAL, MSVD_VSTART_PAL,   49, 36, 18, 18},  // 16:9
        {MSVD_HSTART_PAL, MSVD_VSTART_PAL,   49, 36, 18, 18},  // 4:3
        {MSVD_HSTART_PAL, MSVD_VSTART_PAL,   49, 36, 18, 18},  // Auto
        {MSVD_HSTART_PAL, MSVD_VSTART_PAL,   49, 36, 18, 18},  // Panorama
        {MSVD_HSTART_PAL, MSVD_VSTART_PAL,   49, 36, 18, 18},  // Just Scan
        {MSVD_HSTART_PAL, MSVD_VSTART_PAL,   49, 36, 18, 18},  // Zoom2
        {MSVD_HSTART_PAL, MSVD_VSTART_PAL,   49, 36, 18, 18},  // Zoom1
    },
    {  //SECAM, 2
        {MSVD_HSTART_SECAM, MSVD_VSTART_SECAM,   32, 17, 10, 18},  // Default
        {MSVD_HSTART_SECAM, MSVD_VSTART_SECAM,   32, 17, 10, 18},  // 16:9
        {MSVD_HSTART_SECAM, MSVD_VSTART_SECAM,   32, 17, 10, 18},  // 4:3
        {MSVD_HSTART_SECAM, MSVD_VSTART_SECAM,   32, 17, 10, 18},  // Auto
        {MSVD_HSTART_SECAM, MSVD_VSTART_SECAM,   32, 17, 10, 18},  // Panorama
        {MSVD_HSTART_SECAM, MSVD_VSTART_SECAM,   32, 17, 10, 18},  // Just Scan
        {MSVD_HSTART_SECAM, MSVD_VSTART_SECAM,   32, 17, 10, 18},  // Zoom2
        {MSVD_HSTART_SECAM, MSVD_VSTART_SECAM,   32, 17, 10, 18},  // Zoom1
    },
    {  //NTSC-443/PAL-60, 3
        {MSVD_HSTART_NTSC_443, MSVD_VSTART_NTSC_443,   25, 25, 11, 11},  // Default
        {MSVD_HSTART_NTSC_443, MSVD_VSTART_NTSC_443,   25, 25, 11, 11},  // 16:9
        {MSVD_HSTART_NTSC_443, MSVD_VSTART_NTSC_443,   25, 25, 11, 11},  // 4:3
        {MSVD_HSTART_NTSC_443, MSVD_VSTART_NTSC_443,   25, 25, 11, 11},  // Auto
        {MSVD_HSTART_NTSC_443, MSVD_VSTART_NTSC_443,   25, 25, 11, 11},  // Panorama
        {MSVD_HSTART_NTSC_443, MSVD_VSTART_NTSC_443,   25, 25, 11, 11},  // Just Scan
        {MSVD_HSTART_NTSC_443, MSVD_VSTART_NTSC_443,   25, 25, 11, 11},  // Zoom2
        {MSVD_HSTART_NTSC_443, MSVD_VSTART_NTSC_443,   25, 25, 11, 11},  // Zoom1
    },
    {  //PAL-M, 4
        {MSVD_HSTART_PAL_M, MSVD_VSTART_PAL_M,   22, 22, 11, 11},  // Default
        {MSVD_HSTART_PAL_M, MSVD_VSTART_PAL_M,   22, 22, 11, 11},  // 16:9
        {MSVD_HSTART_PAL_M, MSVD_VSTART_PAL_M,   22, 22, 11, 11},  // 4:3
        {MSVD_HSTART_PAL_M, MSVD_VSTART_PAL_M,   22, 22, 11, 11},  // Auto
        {MSVD_HSTART_PAL_M, MSVD_VSTART_PAL_M,   22, 22, 11, 11},  // Panorama
        {MSVD_HSTART_PAL_M, MSVD_VSTART_PAL_M,   22, 22, 11, 11},  // Just Scan
        {MSVD_HSTART_PAL_M, MSVD_VSTART_PAL_M,   22, 22, 11, 11},  // Zoom2
        {MSVD_HSTART_PAL_M, MSVD_VSTART_PAL_M,   22, 22, 11, 11},  // Zoom1
    },
    {  //PAL-NC, 5
        {MSVD_HSTART_PAL_NC, MSVD_VSTART_PAL_NC,   25, 25, 14, 14},  // Default
        {MSVD_HSTART_PAL_NC, MSVD_VSTART_PAL_NC,   25, 25, 14, 14},  // 16:9
        {MSVD_HSTART_PAL_NC, MSVD_VSTART_PAL_NC,   25, 25, 14, 14},  // 4:3
        {MSVD_HSTART_PAL_NC, MSVD_VSTART_PAL_NC,   25, 25, 14, 14},  // Auto
        {MSVD_HSTART_PAL_NC, MSVD_VSTART_PAL_NC,   25, 25, 14, 14},  // Panorama
        {MSVD_HSTART_PAL_NC, MSVD_VSTART_PAL_NC,   25, 25, 14, 14},  // Just Scan
        {MSVD_HSTART_PAL_NC, MSVD_VSTART_PAL_NC,   25, 25, 14, 14},  // Zoom2
        {MSVD_HSTART_PAL_NC, MSVD_VSTART_PAL_NC,   25, 25, 14, 14},  // Zoom1
    },
#else//For SD Panel overscan
    {  //NTSC, 0
        {MSVD_HSTART_NTSC, MSVD_VSTART_NTSC,   46, 37, 28, 28},  // Default
        {MSVD_HSTART_NTSC, MSVD_VSTART_NTSC,   46, 37, 28, 28},  // 16:9
        {MSVD_HSTART_NTSC, MSVD_VSTART_NTSC,   46, 37, 28, 28},  // 4:3
        {MSVD_HSTART_NTSC, MSVD_VSTART_NTSC,   46, 37, 28, 28},  // Auto
        {MSVD_HSTART_NTSC, MSVD_VSTART_NTSC,   46, 37, 28, 28},  // Panorama
        {MSVD_HSTART_NTSC, MSVD_VSTART_NTSC,   46, 37, 28, 28},  // Just Scan
        {MSVD_HSTART_NTSC, MSVD_VSTART_NTSC,   46, 37, 28, 28},  // Zoom2
        {MSVD_HSTART_NTSC, MSVD_VSTART_NTSC,   46, 37, 28, 28},  // Zoom1
    },
    {  //PAL, 1
        {MSVD_HSTART_PAL, MSVD_VSTART_PAL,   49, 36, 18, 18},  // Default
        {MSVD_HSTART_PAL, MSVD_VSTART_PAL,   49, 36, 18, 18},  // 16:9
        {MSVD_HSTART_PAL, MSVD_VSTART_PAL,   49, 36, 18, 18},  // 4:3
        {MSVD_HSTART_PAL, MSVD_VSTART_PAL,   49, 36, 18, 18},  // Auto
        {MSVD_HSTART_PAL, MSVD_VSTART_PAL,   49, 36, 18, 18},  // Panorama
        {MSVD_HSTART_PAL, MSVD_VSTART_PAL,   49, 36, 18, 18},  // Just Scan
        {MSVD_HSTART_PAL, MSVD_VSTART_PAL,   49, 36, 18, 18},  // Zoom2
        {MSVD_HSTART_PAL, MSVD_VSTART_PAL,   49, 36, 18, 18},  // Zoom1
    },
    {  //SECAM, 2
        {MSVD_HSTART_SECAM, MSVD_VSTART_SECAM,   14, 35, 10, 18},  // Default
        {MSVD_HSTART_SECAM, MSVD_VSTART_SECAM,   14, 35, 10, 18},  // 16:9
        {MSVD_HSTART_SECAM, MSVD_VSTART_SECAM,   14, 35, 10, 18},  // 4:3
        {MSVD_HSTART_SECAM, MSVD_VSTART_SECAM,   14, 35, 10, 18},  // Auto
        {MSVD_HSTART_SECAM, MSVD_VSTART_SECAM,   14, 35, 10, 18},  // Panorama
        {MSVD_HSTART_SECAM, MSVD_VSTART_SECAM,   14, 35, 10, 18},  // Just Scan
        {MSVD_HSTART_SECAM, MSVD_VSTART_SECAM,   14, 35, 10, 18},  // Zoom2
        {MSVD_HSTART_SECAM, MSVD_VSTART_SECAM,   14, 35, 10, 18},  // Zoom1
    },
    {  //NTSC-443/PAL-60, 3
        {MSVD_HSTART_NTSC_443, MSVD_VSTART_NTSC_443,   25, 25, 11, 11},  // Default
        {MSVD_HSTART_NTSC_443, MSVD_VSTART_NTSC_443,   25, 25, 11, 11},  // 16:9
        {MSVD_HSTART_NTSC_443, MSVD_VSTART_NTSC_443,   25, 25, 11, 11},  // 4:3
        {MSVD_HSTART_NTSC_443, MSVD_VSTART_NTSC_443,   25, 25, 11, 11},  // Auto
        {MSVD_HSTART_NTSC_443, MSVD_VSTART_NTSC_443,   25, 25, 11, 11},  // Panorama
        {MSVD_HSTART_NTSC_443, MSVD_VSTART_NTSC_443,   25, 25, 11, 11},  // Just Scan
        {MSVD_HSTART_NTSC_443, MSVD_VSTART_NTSC_443,   25, 25, 11, 11},  // Zoom2
        {MSVD_HSTART_NTSC_443, MSVD_VSTART_NTSC_443,   25, 25, 11, 11},  // Zoom1
    },
    {  //PAL-M, 4
        {MSVD_HSTART_PAL_M, MSVD_VSTART_PAL_M,   22, 22, 11, 11},  // Default
        {MSVD_HSTART_PAL_M, MSVD_VSTART_PAL_M,   22, 22, 11, 11},  // 16:9
        {MSVD_HSTART_PAL_M, MSVD_VSTART_PAL_M,   22, 22, 11, 11},  // 4:3
        {MSVD_HSTART_PAL_M, MSVD_VSTART_PAL_M,   22, 22, 11, 11},  // Auto
        {MSVD_HSTART_PAL_M, MSVD_VSTART_PAL_M,   22, 22, 11, 11},  // Panorama
        {MSVD_HSTART_PAL_M, MSVD_VSTART_PAL_M,   22, 22, 11, 11},  // Just Scan
        {MSVD_HSTART_PAL_M, MSVD_VSTART_PAL_M,   22, 22, 11, 11},  // Zoom2
        {MSVD_HSTART_PAL_M, MSVD_VSTART_PAL_M,   22, 22, 11, 11},  // Zoom1
    },
    {  //PAL-NC, 5
        {MSVD_HSTART_PAL_NC, MSVD_VSTART_PAL_NC,   25, 25, 14, 14},  // Default
        {MSVD_HSTART_PAL_NC, MSVD_VSTART_PAL_NC,   25, 25, 14, 14},  // 16:9
        {MSVD_HSTART_PAL_NC, MSVD_VSTART_PAL_NC,   25, 25, 14, 14},  // 4:3
        {MSVD_HSTART_PAL_NC, MSVD_VSTART_PAL_NC,   25, 25, 14, 14},  // Auto
        {MSVD_HSTART_PAL_NC, MSVD_VSTART_PAL_NC,   25, 25, 14, 14},  // Panorama
        {MSVD_HSTART_PAL_NC, MSVD_VSTART_PAL_NC,   25, 25, 14, 14},  // Just Scan
        {MSVD_HSTART_PAL_NC, MSVD_VSTART_PAL_NC,   25, 25, 14, 14},  // Zoom2
        {MSVD_HSTART_PAL_NC, MSVD_VSTART_PAL_NC,   25, 25, 14, 14},  // Zoom1
    },
#endif
};

//  720x 480
#define MSVD_YPbPr_HSTART_480i60  0x74
#define MSVD_YPbPr_VSTART_480i60  0x1c
#define MSVD_YPbPr_HSTART_480p60  0x7C
#define MSVD_YPbPr_VSTART_480p60  0x1C
//  720x 576
#define MSVD_YPbPr_HSTART_576i50  0x86
#define MSVD_YPbPr_VSTART_576i50  0x20
#define MSVD_YPbPr_HSTART_576p50  0x8C
#define MSVD_YPbPr_VSTART_576p50  0x25
// 1280x 720
#define MSVD_YPbPr_HSTART_720p60  0xff//0xf2 // 0x102
#define MSVD_YPbPr_VSTART_720p60  0x13//0x18 // 0x22
#define MSVD_YPbPr_HSTART_720p50  0xfc//0xf4
#define MSVD_YPbPr_VSTART_720p50  0x10//0x1C
#define MSVD_YPbPr_HSTART_720p25  0xC1//0xf4
#define MSVD_YPbPr_VSTART_720p25  0x05//0x1C
#define MSVD_YPbPr_HSTART_720p30  0xC2//0xf2 // 0x102
#define MSVD_YPbPr_VSTART_720p30  0x05//0x18 // 0x22
// 1920x1080, interlace
#define MSVD_YPbPr_HSTART_1080i60  0xbc
#define MSVD_YPbPr_VSTART_1080i60  0x17
#define MSVD_YPbPr_HSTART_1080i50  0xbc//0x9C
#define MSVD_YPbPr_VSTART_1080i50  0x17//0x2C
#if (SUPPORT_EURO_HDTV)
#define MSVD_YPbPr_HSTART_108oi25  0x138//0x9C
#define MSVD_YPbPr_VSTART_108oi25  0x9b//0x2C
#endif
// 1920x1080, progressive
#define MSVD_YPbPr_HSTART_1080p60  0xBA
#define MSVD_YPbPr_VSTART_1080p60  0x20
#define MSVD_YPbPr_HSTART_1080p50  0xBC
#define MSVD_YPbPr_VSTART_1080p50  0x20
#define MSVD_YPbPr_HSTART_1080p30  0xBC
#define MSVD_YPbPr_VSTART_1080p30  0x20
#define MSVD_YPbPr_HSTART_1080p24  0xBA
#define MSVD_YPbPr_VSTART_1080p24  0x21
#define MSVD_YPbPr_HSTART_1080p25  0xBD
#define MSVD_YPbPr_VSTART_1080p25  0x20

MS_VIDEO_Window_Info YPbPr_WinInfo[E_YPbPr_MAX][E_AR_MAX] =
{
    {  //480i_60, 0
        {MSVD_YPbPr_HSTART_480i60, MSVD_YPbPr_VSTART_480i60, 50, 50, 20, 20},  // Default
        {MSVD_YPbPr_HSTART_480i60, MSVD_YPbPr_VSTART_480i60, 32, 41, 20, 33},  // 16:9
        {MSVD_YPbPr_HSTART_480i60, MSVD_YPbPr_VSTART_480i60, 50, 50, 20, 20},  // 4:3
        {MSVD_YPbPr_HSTART_480i60, MSVD_YPbPr_VSTART_480i60, 50, 50, 20, 20},  // Auto
        {MSVD_YPbPr_HSTART_480i60, MSVD_YPbPr_VSTART_480i60, 50, 50, 20, 20},  // Panorama
        {MSVD_YPbPr_HSTART_480i60, MSVD_YPbPr_VSTART_480i60, 50, 50, 20, 20},  // Just Scan
        {MSVD_YPbPr_HSTART_480i60, MSVD_YPbPr_VSTART_480i60, 50, 50, 20, 20},  // Zoom2
        {MSVD_YPbPr_HSTART_480i60, MSVD_YPbPr_VSTART_480i60, 50, 50, 20, 20},  // Zoom1
    },
    {  //480p_60, 1
        {MSVD_YPbPr_HSTART_480p60, MSVD_YPbPr_VSTART_480p60, 50, 50, 20, 20},  // Default
        {MSVD_YPbPr_HSTART_480p60, MSVD_YPbPr_VSTART_480p60, 50, 50, 20, 20},  // 16:9
        {MSVD_YPbPr_HSTART_480p60, MSVD_YPbPr_VSTART_480p60, 50, 50, 20, 20},  // 4:3
        {MSVD_YPbPr_HSTART_480p60, MSVD_YPbPr_VSTART_480p60, 50, 50, 20, 20},  // Auto
        {MSVD_YPbPr_HSTART_480p60, MSVD_YPbPr_VSTART_480p60, 50, 50, 20, 20},  // Panorama
        {MSVD_YPbPr_HSTART_480p60, MSVD_YPbPr_VSTART_480p60, 50, 50, 20, 20},  // Just Scan
        {MSVD_YPbPr_HSTART_480p60, MSVD_YPbPr_VSTART_480p60, 50, 50, 20, 20},  // Zoom2
        {MSVD_YPbPr_HSTART_480p60, MSVD_YPbPr_VSTART_480p60, 50, 50, 20, 20},  // Zoom1
    },
    {  //576i_50, 2
        {MSVD_YPbPr_HSTART_576i50, MSVD_YPbPr_VSTART_576i50, 40, 40, 20, 20},  // Default
        {MSVD_YPbPr_HSTART_576i50, MSVD_YPbPr_VSTART_576i50, 40, 40, 20, 20},  // 16:9
        {MSVD_YPbPr_HSTART_576i50, MSVD_YPbPr_VSTART_576i50, 40, 40, 20, 20},  // 4:3
        {MSVD_YPbPr_HSTART_576i50, MSVD_YPbPr_VSTART_576i50, 40, 40, 20, 20},  // Auto
        {MSVD_YPbPr_HSTART_576i50, MSVD_YPbPr_VSTART_576i50, 50, 50, 20, 20},  // Panorama
        {MSVD_YPbPr_HSTART_576i50, MSVD_YPbPr_VSTART_576i50, 50, 50, 20, 20},  // Just Scan
        {MSVD_YPbPr_HSTART_576i50, MSVD_YPbPr_VSTART_576i50, 50, 50, 20, 20},  // Zoom2
        {MSVD_YPbPr_HSTART_576i50, MSVD_YPbPr_VSTART_576i50, 50, 50, 20, 20},  // Zoom1
    },
    {  //576p_50, 3
        {MSVD_YPbPr_HSTART_576p50, MSVD_YPbPr_VSTART_576p50, 50, 50, 20, 20},  // Default
        {MSVD_YPbPr_HSTART_576p50, MSVD_YPbPr_VSTART_576p50, 50, 50, 20, 20},  // 16:9
        {MSVD_YPbPr_HSTART_576p50, MSVD_YPbPr_VSTART_576p50, 50, 50, 20, 20},  // 4:3
        {MSVD_YPbPr_HSTART_576p50, MSVD_YPbPr_VSTART_576p50, 50, 50, 20, 20},  // Auto
        {MSVD_YPbPr_HSTART_576p50, MSVD_YPbPr_VSTART_576p50, 50, 50, 20, 20},  // Panorama
        {MSVD_YPbPr_HSTART_576p50, MSVD_YPbPr_VSTART_576p50, 50, 50, 20, 20},  // Just Scan
        {MSVD_YPbPr_HSTART_576p50, MSVD_YPbPr_VSTART_576p50, 50, 50, 20, 20},  // Zoom2
        {MSVD_YPbPr_HSTART_576p50, MSVD_YPbPr_VSTART_576p50, 50, 50, 20, 20},  // Zoom1
    },
    {  //720p_60, 4
        {MSVD_YPbPr_HSTART_720p60, MSVD_YPbPr_VSTART_720p60, 50, 50, 20, 20},  // Default
        {MSVD_YPbPr_HSTART_720p60, MSVD_YPbPr_VSTART_720p60, 10, 10, 10, 10},  // 16:9
        {MSVD_YPbPr_HSTART_720p60, MSVD_YPbPr_VSTART_720p60,10, 10, 10,10},  // 4:3
        {MSVD_YPbPr_HSTART_720p60, MSVD_YPbPr_VSTART_720p60,10, 10, 10, 10},  // Auto
        {MSVD_YPbPr_HSTART_720p60, MSVD_YPbPr_VSTART_720p60, 50, 50, 20, 20},  // Panorama
        {MSVD_YPbPr_HSTART_720p60, MSVD_YPbPr_VSTART_720p60, 50, 50, 20, 20},  // Just Scan
        {MSVD_YPbPr_HSTART_720p60, MSVD_YPbPr_VSTART_720p60, 50, 50, 20, 20},  // Zoom2
        {MSVD_YPbPr_HSTART_720p60, MSVD_YPbPr_VSTART_720p60, 50, 50, 20, 20},  // Zoom1
    },
    {  //720p_50, 5
        {MSVD_YPbPr_HSTART_720p50, MSVD_YPbPr_VSTART_720p50, 10, 10, 10, 10},  // Default
        {MSVD_YPbPr_HSTART_720p50, MSVD_YPbPr_VSTART_720p50, 10, 10, 10,10},  // 16:9
        {MSVD_YPbPr_HSTART_720p50, MSVD_YPbPr_VSTART_720p50, 10, 10, 10, 10},  // 4:3
        {MSVD_YPbPr_HSTART_720p50, MSVD_YPbPr_VSTART_720p50, 10, 10, 10,10},  // Auto
        {MSVD_YPbPr_HSTART_720p50, MSVD_YPbPr_VSTART_720p50, 50, 50, 20, 20},  // Panorama
        {MSVD_YPbPr_HSTART_720p50, MSVD_YPbPr_VSTART_720p50, 50, 50, 20, 20},  // Just Scan
        {MSVD_YPbPr_HSTART_720p50, MSVD_YPbPr_VSTART_720p50, 50, 50, 20, 20},  // Zoom2
        {MSVD_YPbPr_HSTART_720p50, MSVD_YPbPr_VSTART_720p50, 50, 50, 20, 20},  // Zoom1
    },
    {  //1080i_60, 6
        {MSVD_YPbPr_HSTART_1080i60, MSVD_YPbPr_VSTART_1080i60, 10, 10, 10, 10},  // Default
        {MSVD_YPbPr_HSTART_1080i60, MSVD_YPbPr_VSTART_1080i60, 10, 10, 10, 10},  // 16:9
        {MSVD_YPbPr_HSTART_1080i60, MSVD_YPbPr_VSTART_1080i60, 10, 10, 10, 10},  // 4:3
        {MSVD_YPbPr_HSTART_1080i60, MSVD_YPbPr_VSTART_1080i60, 50, 50, 20, 20},  // Auto
        {MSVD_YPbPr_HSTART_1080i60, MSVD_YPbPr_VSTART_1080i60, 50, 50, 20, 20},  // Panorama
        {MSVD_YPbPr_HSTART_1080i60, MSVD_YPbPr_VSTART_1080i60, 50, 50, 20, 20},  // Just Scan
        {MSVD_YPbPr_HSTART_1080i60, MSVD_YPbPr_VSTART_1080i60, 50, 50, 20, 20},  // Zoom2
        {MSVD_YPbPr_HSTART_1080i60, MSVD_YPbPr_VSTART_1080i60, 50, 50, 20, 20},  // Zoom1
    },
    {  //1080i_50, 7
        {MSVD_YPbPr_HSTART_1080i50, MSVD_YPbPr_VSTART_1080i50, 10, 10, 10, 10},  // Default
        {MSVD_YPbPr_HSTART_1080i50, MSVD_YPbPr_VSTART_1080i50, 10, 10, 10, 10},  // 16:9
        {MSVD_YPbPr_HSTART_1080i50, MSVD_YPbPr_VSTART_1080i50, 10, 10, 10, 10},  // 4:3
        {MSVD_YPbPr_HSTART_1080i50, MSVD_YPbPr_VSTART_1080i50, 10,10, 10, 10},  // Auto
        {MSVD_YPbPr_HSTART_1080i50, MSVD_YPbPr_VSTART_1080i50, 50, 50, 20, 20},  // Panorama
        {MSVD_YPbPr_HSTART_1080i50, MSVD_YPbPr_VSTART_1080i50, 50, 50, 20, 20},  // Just Scan
        {MSVD_YPbPr_HSTART_1080i50, MSVD_YPbPr_VSTART_1080i50, 50, 50, 20, 20},  // Zoom2
        {MSVD_YPbPr_HSTART_1080i50, MSVD_YPbPr_VSTART_1080i50, 50, 50, 20, 20},  // Zoom1
    },
    {  //1080p_60, 8
        {MSVD_YPbPr_HSTART_1080p60, MSVD_YPbPr_VSTART_1080p60, 10, 10, 10, 10},  // Default
        {MSVD_YPbPr_HSTART_1080p60, MSVD_YPbPr_VSTART_1080p60, 10, 10, 10, 10},  // 16:9
        {MSVD_YPbPr_HSTART_1080p60, MSVD_YPbPr_VSTART_1080p60, 10, 10, 10, 10},  // 4:3
        {MSVD_YPbPr_HSTART_1080p60, MSVD_YPbPr_VSTART_1080p60, 10, 10, 10, 10},  // Auto
        {MSVD_YPbPr_HSTART_1080p60, MSVD_YPbPr_VSTART_1080p60, 50, 50, 20, 20},  // Panorama
        {MSVD_YPbPr_HSTART_1080p60, MSVD_YPbPr_VSTART_1080p60, 50, 50, 20, 20},  // Just Scan
        {MSVD_YPbPr_HSTART_1080p60, MSVD_YPbPr_VSTART_1080p60, 50, 50, 20, 20},  // Zoom2
        {MSVD_YPbPr_HSTART_1080p60, MSVD_YPbPr_VSTART_1080p60, 50, 50, 20, 20},  // Zoom1
    },
    {  //1080p_50, 9
        {MSVD_YPbPr_HSTART_1080p50, MSVD_YPbPr_VSTART_1080p50, 10, 10, 10, 10},  // Default
        {MSVD_YPbPr_HSTART_1080p50, MSVD_YPbPr_VSTART_1080p50, 10, 10, 5, 5},  // 16:9
        {MSVD_YPbPr_HSTART_1080p50, MSVD_YPbPr_VSTART_1080p50, 10, 10, 10, 10},  // 4:3
        {MSVD_YPbPr_HSTART_1080p50, MSVD_YPbPr_VSTART_1080p50, 10, 10,10,10},  // Auto
        {MSVD_YPbPr_HSTART_1080p50, MSVD_YPbPr_VSTART_1080p50, 50, 50, 20, 20},  // Panorama
        {MSVD_YPbPr_HSTART_1080p50, MSVD_YPbPr_VSTART_1080p50, 50, 50, 20, 20},  // Just Scan
        {MSVD_YPbPr_HSTART_1080p50, MSVD_YPbPr_VSTART_1080p50, 50, 50, 20, 20},  // Zoom2
        {MSVD_YPbPr_HSTART_1080p50, MSVD_YPbPr_VSTART_1080p50, 50, 50, 20, 20},  // Zoom1
    },
    {  //1080p_30, 10
        {MSVD_YPbPr_HSTART_1080p30, MSVD_YPbPr_VSTART_1080p30, 10, 10, 10, 10},  // Default
        {MSVD_YPbPr_HSTART_1080p30, MSVD_YPbPr_VSTART_1080p30, 10, 10, 10, 10},  // 16:9
        {MSVD_YPbPr_HSTART_1080p30, MSVD_YPbPr_VSTART_1080p30, 10, 10, 10, 10},  // 4:3
        {MSVD_YPbPr_HSTART_1080p30, MSVD_YPbPr_VSTART_1080p30, 10, 10, 10, 10},  // Auto
        {MSVD_YPbPr_HSTART_1080p30, MSVD_YPbPr_VSTART_1080p30, 17, 17, 11, 11},  // Panorama
        {MSVD_YPbPr_HSTART_1080p30, MSVD_YPbPr_VSTART_1080p30, 17, 17, 11, 11},  // Just Scan
        {MSVD_YPbPr_HSTART_1080p30, MSVD_YPbPr_VSTART_1080p30, 17, 17, 11, 11},  // Zoom2
        {MSVD_YPbPr_HSTART_1080p30, MSVD_YPbPr_VSTART_1080p30, 17, 17, 11, 11},  // Zoom1
    },
    {  //1080p_24, 11
        {MSVD_YPbPr_HSTART_1080p24, MSVD_YPbPr_VSTART_1080p24, 10, 00, 11, 11},  // Default
        {MSVD_YPbPr_HSTART_1080p24, MSVD_YPbPr_VSTART_1080p24, 10, 00, 10, 10},  // 16:9
        {MSVD_YPbPr_HSTART_1080p24, MSVD_YPbPr_VSTART_1080p24, 10, 00, 10, 10},  // 4:3
        {MSVD_YPbPr_HSTART_1080p24, MSVD_YPbPr_VSTART_1080p24, 10, 00, 10, 10},  // Auto
        {MSVD_YPbPr_HSTART_1080p24, MSVD_YPbPr_VSTART_1080p24, 10, 00, 11, 11},  // Panorama
        {MSVD_YPbPr_HSTART_1080p24, MSVD_YPbPr_VSTART_1080p24, 10, 00, 11, 11},  // Just Scan
        {MSVD_YPbPr_HSTART_1080p24, MSVD_YPbPr_VSTART_1080p24, 10, 00, 11, 11},  // Zoom2
        {MSVD_YPbPr_HSTART_1080p24, MSVD_YPbPr_VSTART_1080p24, 10, 00, 11, 11},  // Zoom1
    },
    {  //1080p_25, 12
        {MSVD_YPbPr_HSTART_1080p25, MSVD_YPbPr_VSTART_1080p25, 10, 00, 11, 11},  // Default
        {MSVD_YPbPr_HSTART_1080p25, MSVD_YPbPr_VSTART_1080p25, 10, 00, 10, 10},  // 16:9
        {MSVD_YPbPr_HSTART_1080p25, MSVD_YPbPr_VSTART_1080p25, 10, 00, 10, 10},  // 4:3
        {MSVD_YPbPr_HSTART_1080p25, MSVD_YPbPr_VSTART_1080p25, 10, 00, 10, 10},  // Auto
        {MSVD_YPbPr_HSTART_1080p25, MSVD_YPbPr_VSTART_1080p25, 10, 00, 11, 11},  // Panorama
        {MSVD_YPbPr_HSTART_1080p25, MSVD_YPbPr_VSTART_1080p25, 10, 00, 11, 11},  // Just Scan
        {MSVD_YPbPr_HSTART_1080p25, MSVD_YPbPr_VSTART_1080p25, 10, 00, 11, 11},  // Zoom2
        {MSVD_YPbPr_HSTART_1080p25, MSVD_YPbPr_VSTART_1080p25, 10, 00, 11, 11},  // Zoom1
    },
    {  //720p_25, 13
        {MSVD_YPbPr_HSTART_720p25, MSVD_YPbPr_VSTART_720p25, 10, 10, 10, 10},  // Default
        {MSVD_YPbPr_HSTART_720p25, MSVD_YPbPr_VSTART_720p25, 10, 10, 10, 10},  // 16:9
        {MSVD_YPbPr_HSTART_720p25, MSVD_YPbPr_VSTART_720p25, 10, 10, 10, 10},  // 4:3
        {MSVD_YPbPr_HSTART_720p25, MSVD_YPbPr_VSTART_720p25, 10, 10, 10, 10},  // Auto
        {MSVD_YPbPr_HSTART_720p25, MSVD_YPbPr_VSTART_720p25, 50, 50, 20, 20},  // Panorama
        {MSVD_YPbPr_HSTART_720p25, MSVD_YPbPr_VSTART_720p25, 50, 50, 20, 20},  // Just Scan
        {MSVD_YPbPr_HSTART_720p25, MSVD_YPbPr_VSTART_720p25, 50, 50, 20, 20},  // Zoom2
        {MSVD_YPbPr_HSTART_720p25, MSVD_YPbPr_VSTART_720p25, 50, 50, 20, 20},  // Zoom1
    },
    {  //720p_30, 14
        {MSVD_YPbPr_HSTART_720p30, MSVD_YPbPr_VSTART_720p30, 50, 50, 20, 20},  // Default
        {MSVD_YPbPr_HSTART_720p30, MSVD_YPbPr_VSTART_720p30, 10, 10, 10, 10},  // 16:9
        {MSVD_YPbPr_HSTART_720p30, MSVD_YPbPr_VSTART_720p30, 10, 10, 10, 10},  // 4:3
        {MSVD_YPbPr_HSTART_720p30, MSVD_YPbPr_VSTART_720p30, 10, 10, 10, 10},  // Auto
        {MSVD_YPbPr_HSTART_720p30, MSVD_YPbPr_VSTART_720p30, 50, 50, 20, 20},  // Panorama
        {MSVD_YPbPr_HSTART_720p30, MSVD_YPbPr_VSTART_720p30, 50, 50, 20, 20},  // Just Scan
        {MSVD_YPbPr_HSTART_720p30, MSVD_YPbPr_VSTART_720p30, 50, 50, 20, 20},  // Zoom2
        {MSVD_YPbPr_HSTART_720p30, MSVD_YPbPr_VSTART_720p30, 50, 50, 20, 20},  // Zoom1
    },
    #if (SUPPORT_EURO_HDTV)
    {  //1080i_25, 15
        {MSVD_YPbPr_HSTART_108oi25, MSVD_YPbPr_VSTART_108oi25, 10, 10, 10, 10},  // Default
        {MSVD_YPbPr_HSTART_108oi25, MSVD_YPbPr_VSTART_108oi25, 10, 10, 10, 10},  // 16:9
        {MSVD_YPbPr_HSTART_108oi25, MSVD_YPbPr_VSTART_108oi25, 10, 10, 10, 10},  // 4:3
        {MSVD_YPbPr_HSTART_108oi25, MSVD_YPbPr_VSTART_108oi25, 10, 10, 10, 10},  // Auto
        {MSVD_YPbPr_HSTART_108oi25, MSVD_YPbPr_VSTART_108oi25, 50, 50, 20, 20},  // Panorama
        {MSVD_YPbPr_HSTART_108oi25, MSVD_YPbPr_VSTART_108oi25, 50, 50, 20, 20},  // Just Scan
        {MSVD_YPbPr_HSTART_108oi25, MSVD_YPbPr_VSTART_108oi25, 50, 50, 20, 20},  // Zoom2
        {MSVD_YPbPr_HSTART_108oi25, MSVD_YPbPr_VSTART_108oi25, 50, 50, 20, 20},  // Zoom1
    },
    #endif
};

//  720x 480
#define MSVD_HDMI_HSTART_480i60  0x51//0x8A
#define MSVD_HDMI_VSTART_480i60  0x25
#define MSVD_HDMI_HSTART_480p60  0x4F//0x88
#define MSVD_HDMI_VSTART_480p60  0x25
//  720x 576
#define MSVD_HDMI_HSTART_576i50  0x4D//0x86
#define MSVD_HDMI_VSTART_576i50  0x22
#define MSVD_HDMI_HSTART_576p50  0x56//0x8F
#define MSVD_HDMI_VSTART_576p50  0x2C
// 1280x 720
#define MSVD_HDMI_HSTART_720p60  0x13B//0x174
#define MSVD_HDMI_VSTART_720p60  0x1A
#define MSVD_HDMI_HSTART_720p50  0x289//0x2C2
#define MSVD_HDMI_VSTART_720p50  0x1C
// 1920x1080, interlace
#define MSVD_HDMI_HSTART_1080i60  0xE3//0x11C
#define MSVD_HDMI_VSTART_1080i60  0x24
#define MSVD_HDMI_HSTART_1080i50  0x29F//0x2D8
#define MSVD_HDMI_VSTART_1080i50  0x24
// 1920x1080, progressive
#define MSVD_HDMI_HSTART_1080p60  0xDE//0x117
#define MSVD_HDMI_VSTART_1080p60  0x20
#define MSVD_HDMI_HSTART_1080p50  0x296//0x2CF
#define MSVD_HDMI_VSTART_1080p50  0x25
#define MSVD_HDMI_HSTART_1080p30  0x83//0xBC
#define MSVD_HDMI_VSTART_1080p30  0x20
#define MSVD_HDMI_HSTART_1080p24  0x83//0xBC
#define MSVD_HDMI_VSTART_1080p24  0x21
// 1440x480
#define MSVD_HDMI_HSTART_1440x480i60  0xD9//0x112
#define MSVD_HDMI_VSTART_1440x480i60  0x28
#define MSVD_HDMI_HSTART_1440x480p60  0xD9//0x112
#define MSVD_HDMI_VSTART_1440x480p60  0x28
// 1440x576
#define MSVD_HDMI_HSTART_1440x576i50  0xE7//0x120
#define MSVD_HDMI_VSTART_1440x576i50  0x32
#define MSVD_HDMI_HSTART_1440x576p50  0xE7//0x120
#define MSVD_HDMI_VSTART_1440x576p50  0x32


MS_VIDEO_Window_Info HDMI_WinInfo[E_HDMI_MAX][E_AR_MAX] =
{
    {  //480i_60, 0
        {MSVD_HDMI_HSTART_480i60, MSVD_HDMI_VSTART_480i60, 16, 16, 13, 13},  // Default
        {MSVD_HDMI_HSTART_480i60, MSVD_HDMI_VSTART_480i60, 16, 16, 13, 13},  // 16:9
        {MSVD_HDMI_HSTART_480i60, MSVD_HDMI_VSTART_480i60, 16, 16, 13, 13},  // 4:3
        {MSVD_HDMI_HSTART_480i60, MSVD_HDMI_VSTART_480i60, 16, 16, 13, 13},  // Auto
        {MSVD_HDMI_HSTART_480i60, MSVD_HDMI_VSTART_480i60, 16, 16, 13, 13},  // Panorama
        {MSVD_HDMI_HSTART_480i60, MSVD_HDMI_VSTART_480i60, 16, 16, 13, 13},  // Just Scan
        {MSVD_HDMI_HSTART_480i60, MSVD_HDMI_VSTART_480i60, 16, 16, 13, 13},  // Zoom2
        {MSVD_HDMI_HSTART_480i60, MSVD_HDMI_VSTART_480i60, 16, 16, 13, 13},  // Zoom1
    },
    {  //480p_60, 1
        {MSVD_HDMI_HSTART_480p60, MSVD_HDMI_VSTART_480p60, 13, 13, 9, 9},  // Default
        {MSVD_HDMI_HSTART_480p60, MSVD_HDMI_VSTART_480p60, 13, 13, 9, 9},  // 16:9
        {MSVD_HDMI_HSTART_480p60, MSVD_HDMI_VSTART_480p60, 13, 13, 9, 9},  // 4:3
        {MSVD_HDMI_HSTART_480p60, MSVD_HDMI_VSTART_480p60, 13, 13, 9, 9},  // Auto
        {MSVD_HDMI_HSTART_480p60, MSVD_HDMI_VSTART_480p60, 13, 13, 9, 9},  // Panorama
        {MSVD_HDMI_HSTART_480p60, MSVD_HDMI_VSTART_480p60, 13, 13, 9, 9},  // Just Scan
        {MSVD_HDMI_HSTART_480p60, MSVD_HDMI_VSTART_480p60, 13, 13, 9, 9},  // Zoom2
        {MSVD_HDMI_HSTART_480p60, MSVD_HDMI_VSTART_480p60, 13, 13, 9, 9},  // Zoom1
    },
    {  //576i_50, 2
        {MSVD_HDMI_HSTART_576i50, MSVD_HDMI_VSTART_576i50, 12, 12, 12, 12},  // Default
        {MSVD_HDMI_HSTART_576i50, MSVD_HDMI_VSTART_576i50, 12, 12, 12, 12},  // 16:9
        {MSVD_HDMI_HSTART_576i50, MSVD_HDMI_VSTART_576i50, 12, 12, 12, 12},  // 4:3
        {MSVD_HDMI_HSTART_576i50, MSVD_HDMI_VSTART_576i50, 12, 12, 12, 12},  // Auto
        {MSVD_HDMI_HSTART_576i50, MSVD_HDMI_VSTART_576i50, 12, 12, 12, 12},  // Panorama
        {MSVD_HDMI_HSTART_576i50, MSVD_HDMI_VSTART_576i50, 12, 12, 12, 12},  // Just Scan
        {MSVD_HDMI_HSTART_576i50, MSVD_HDMI_VSTART_576i50, 12, 12, 12, 12},  // Zoom2
        {MSVD_HDMI_HSTART_576i50, MSVD_HDMI_VSTART_576i50, 12, 12, 12, 12},  // Zoom1
    },
    {  //576p_50, 3
        {MSVD_HDMI_HSTART_576p50, MSVD_HDMI_VSTART_576p50, 50, 50, 20, 20},  // Default
        {MSVD_HDMI_HSTART_576p50, MSVD_HDMI_VSTART_576p50, 50, 50, 20, 20},  // 16:9
        {MSVD_HDMI_HSTART_576p50, MSVD_HDMI_VSTART_576p50, 50, 50, 20, 20},  // 4:3
        {MSVD_HDMI_HSTART_576p50, MSVD_HDMI_VSTART_576p50, 50, 20, 20, 20},  // Auto
        {MSVD_HDMI_HSTART_576p50, MSVD_HDMI_VSTART_576p50, 50, 50, 20, 20},  // Panorama
        {MSVD_HDMI_HSTART_576p50, MSVD_HDMI_VSTART_576p50, 50, 50, 20, 20},  // Just Scan
        {MSVD_HDMI_HSTART_576p50, MSVD_HDMI_VSTART_576p50, 50, 50, 20, 20},  // Zoom2
        {MSVD_HDMI_HSTART_576p50, MSVD_HDMI_VSTART_576p50, 50, 50, 20, 20},  // Zoom1
    },
    {  //720p_60, 4
        {MSVD_HDMI_HSTART_720p60, MSVD_HDMI_VSTART_720p60, 50, 50, 20, 20},  // Default
        {MSVD_HDMI_HSTART_720p60, MSVD_HDMI_VSTART_720p60, 10, 10, 10, 10},  // 16:9
        {MSVD_HDMI_HSTART_720p60, MSVD_HDMI_VSTART_720p60, 10, 10, 10,10},  // 4:3
        {MSVD_HDMI_HSTART_720p60, MSVD_HDMI_VSTART_720p60, 10, 10, 10, 10},  // Auto
        {MSVD_HDMI_HSTART_720p60, MSVD_HDMI_VSTART_720p60, 50, 50, 20, 20},  // Panorama
        {MSVD_HDMI_HSTART_720p60, MSVD_HDMI_VSTART_720p60, 50, 50, 20, 20},  // Just Scan
        {MSVD_HDMI_HSTART_720p60, MSVD_HDMI_VSTART_720p60, 50, 50, 20, 20},  // Zoom2
        {MSVD_HDMI_HSTART_720p60, MSVD_HDMI_VSTART_720p60, 50, 50, 20, 20},  // Zoom1
    },
    {  //720p_50, 5
        {MSVD_HDMI_HSTART_720p50, MSVD_HDMI_VSTART_720p50, 50, 50, 20, 20},  // Default
        {MSVD_HDMI_HSTART_720p50, MSVD_HDMI_VSTART_720p50, 10, 10, 10, 10},  // 16:9
        {MSVD_HDMI_HSTART_720p50, MSVD_HDMI_VSTART_720p50, 10, 10, 10, 10},  // 4:3
        {MSVD_HDMI_HSTART_720p50, MSVD_HDMI_VSTART_720p50, 10, 10, 10, 10},  // Auto
        {MSVD_HDMI_HSTART_720p50, MSVD_HDMI_VSTART_720p50, 50, 50, 20, 20},  // Panorama
        {MSVD_HDMI_HSTART_720p50, MSVD_HDMI_VSTART_720p50, 50, 50, 20, 20},  // Just Scan
        {MSVD_HDMI_HSTART_720p50, MSVD_HDMI_VSTART_720p50, 50, 50, 20, 20},  // Zoom2
        {MSVD_HDMI_HSTART_720p50, MSVD_HDMI_VSTART_720p50, 50, 50, 20, 20},  // Zoom1
    },
    {  //1080i_60, 6
        {MSVD_HDMI_HSTART_1080i60, MSVD_HDMI_VSTART_1080i60, 50, 50, 20, 20},  // Default
        {MSVD_HDMI_HSTART_1080i60, MSVD_HDMI_VSTART_1080i60, 10,10, 10, 10},  // 16:9
        {MSVD_HDMI_HSTART_1080i60, MSVD_HDMI_VSTART_1080i60, 10, 10, 10, 10},  // 4:3
        {MSVD_HDMI_HSTART_1080i60, MSVD_HDMI_VSTART_1080i60, 10, 10, 10, 10},  // Auto
        {MSVD_HDMI_HSTART_1080i60, MSVD_HDMI_VSTART_1080i60, 50, 50, 20, 20},  // Panorama
        {MSVD_HDMI_HSTART_1080i60, MSVD_HDMI_VSTART_1080i60, 0, 0, 0, 0},  // Just Scan
        {MSVD_HDMI_HSTART_1080i60, MSVD_HDMI_VSTART_1080i60, 50, 50, 20, 20},  // Zoom2
        {MSVD_HDMI_HSTART_1080i60, MSVD_HDMI_VSTART_1080i60, 50, 50, 20, 20},  // Zoom1
    },
    {  //1080i_50, 7
        {MSVD_HDMI_HSTART_1080i50, MSVD_HDMI_VSTART_1080i50, 50, 50, 20, 20},  // Default
        {MSVD_HDMI_HSTART_1080i50, MSVD_HDMI_VSTART_1080i50, 10, 10, 10, 10},  // 16:9
        {MSVD_HDMI_HSTART_1080i50, MSVD_HDMI_VSTART_1080i50, 10, 10, 10, 10},  // 4:3
        {MSVD_HDMI_HSTART_1080i50, MSVD_HDMI_VSTART_1080i50, 50, 50, 20, 20},  // Auto
        {MSVD_HDMI_HSTART_1080i50, MSVD_HDMI_VSTART_1080i50, 50, 50, 20, 20},  // Panorama
        {MSVD_HDMI_HSTART_1080i50, MSVD_HDMI_VSTART_1080i50, 0, 0, 0, 0},  // Just Scan
        {MSVD_HDMI_HSTART_1080i50, MSVD_HDMI_VSTART_1080i50, 50, 50, 20, 20},  // Zoom2
        {MSVD_HDMI_HSTART_1080i50, MSVD_HDMI_VSTART_1080i50, 50, 50, 20, 20},  // Zoom1
    },
    {  //1080p_60, 8
        {MSVD_HDMI_HSTART_1080p60, MSVD_HDMI_VSTART_1080p60, 50, 50, 20, 20},  // Default
        {MSVD_HDMI_HSTART_1080p60, MSVD_HDMI_VSTART_1080p60, 0, 0, 0, 0},  // 16:9
        {MSVD_HDMI_HSTART_1080p60, MSVD_HDMI_VSTART_1080p60, 50, 50, 20, 20},  // 4:3
        {MSVD_HDMI_HSTART_1080p60, MSVD_HDMI_VSTART_1080p60, 50, 50, 20, 20},  // Auto
        {MSVD_HDMI_HSTART_1080p60, MSVD_HDMI_VSTART_1080p60, 50, 50, 20, 20},  // Panorama
        {MSVD_HDMI_HSTART_1080p60, MSVD_HDMI_VSTART_1080p60, 0, 0, 0, 0},  // Just Scan
        {MSVD_HDMI_HSTART_1080p60, MSVD_HDMI_VSTART_1080p60, 50, 50, 20, 20},  // Zoom2
        {MSVD_HDMI_HSTART_1080p60, MSVD_HDMI_VSTART_1080p60, 50, 50, 20, 20},  // Zoom1
    },
    {  //1080p_50, 9
        {MSVD_HDMI_HSTART_1080p50, MSVD_HDMI_VSTART_1080p50, 50, 50, 20, 20},  // Default
        {MSVD_HDMI_HSTART_1080p50, MSVD_HDMI_VSTART_1080p50, 10, 10, 10, 10},  // 16:9
        {MSVD_HDMI_HSTART_1080p50, MSVD_HDMI_VSTART_1080p50, 10, 10, 10, 10},  // 4:3
        {MSVD_HDMI_HSTART_1080p50, MSVD_HDMI_VSTART_1080p50, 10, 10, 10, 10},  // Auto
        {MSVD_HDMI_HSTART_1080p50, MSVD_HDMI_VSTART_1080p50, 50, 50, 20, 20},  // Panorama
        {MSVD_HDMI_HSTART_1080p50, MSVD_HDMI_VSTART_1080p50, 0, 0, 0, 0},  // Just Scan
        {MSVD_HDMI_HSTART_1080p50, MSVD_HDMI_VSTART_1080p50, 50, 50, 20, 20},  // Zoom2
        {MSVD_HDMI_HSTART_1080p50, MSVD_HDMI_VSTART_1080p50, 50, 50, 20, 20},  // Zoom1
    },
    {  //1080p_30, 10
        {MSVD_HDMI_HSTART_1080p30, MSVD_HDMI_VSTART_1080p30, 50, 50, 20, 20},  // Default
        {MSVD_HDMI_HSTART_1080p30, MSVD_HDMI_VSTART_1080p30, 10, 10, 10, 10},  // 16:9
        {MSVD_HDMI_HSTART_1080p30, MSVD_HDMI_VSTART_1080p30, 10, 10, 10, 10},  // 4:3
        {MSVD_HDMI_HSTART_1080p30, MSVD_HDMI_VSTART_1080p30, 10, 10, 10, 10},  // Auto
        {MSVD_HDMI_HSTART_1080p30, MSVD_HDMI_VSTART_1080p30, 50, 50, 20, 20},  // Panorama
        {MSVD_HDMI_HSTART_1080p30, MSVD_HDMI_VSTART_1080p30, 0, 0, 0, 0},  // Just Scan
        {MSVD_HDMI_HSTART_1080p30, MSVD_HDMI_VSTART_1080p30, 50, 50, 20, 20},  // Zoom2
        {MSVD_HDMI_HSTART_1080p30, MSVD_HDMI_VSTART_1080p30, 50, 50, 20, 20},  // Zoom1
    },
    {  //1080p_24, 11
        {MSVD_HDMI_HSTART_1080p24, MSVD_HDMI_VSTART_1080p24, 50, 50, 20, 20},  // Default
        {MSVD_HDMI_HSTART_1080p24, MSVD_HDMI_VSTART_1080p24, 10, 10, 10, 10},  // 16:9
        {MSVD_HDMI_HSTART_1080p24, MSVD_HDMI_VSTART_1080p24, 10, 10, 10, 10},  // 4:3
        {MSVD_HDMI_HSTART_1080p24, MSVD_HDMI_VSTART_1080p24, 10, 10, 10, 10},  // Auto
        {MSVD_HDMI_HSTART_1080p24, MSVD_HDMI_VSTART_1080p24, 50, 50, 20, 20},  // Panorama
        {MSVD_HDMI_HSTART_1080p24, MSVD_HDMI_VSTART_1080p24, 0, 0, 0, 0},  // Just Scan
        {MSVD_HDMI_HSTART_1080p24, MSVD_HDMI_VSTART_1080p24, 50, 50, 20, 20},  // Zoom2
        {MSVD_HDMI_HSTART_1080p24, MSVD_HDMI_VSTART_1080p24, 50, 50, 20, 20},  // Zoom1
    },
    {  //1440x480i, 12
        {MSVD_HDMI_HSTART_1440x480i60, MSVD_HDMI_VSTART_1440x480i60, 50, 50, 20, 20},  // Default
        {MSVD_HDMI_HSTART_1440x480i60, MSVD_HDMI_VSTART_1440x480i60, 50, 50, 20, 20},  // 16:9
        {MSVD_HDMI_HSTART_1440x480i60, MSVD_HDMI_VSTART_1440x480i60, 50, 50, 20, 20},  // 4:3
        {MSVD_HDMI_HSTART_1440x480i60, MSVD_HDMI_VSTART_1440x480i60, 50, 50, 20, 20},  // Auto
        {MSVD_HDMI_HSTART_1440x480i60, MSVD_HDMI_VSTART_1440x480i60, 50, 50, 20, 20},  // Panorama
        {MSVD_HDMI_HSTART_1440x480i60, MSVD_HDMI_VSTART_1440x480i60, 0, 0, 0, 0},  // Just Scan
        {MSVD_HDMI_HSTART_1440x480i60, MSVD_HDMI_VSTART_1440x480i60, 50, 50, 20, 20},  // Zoom2
        {MSVD_HDMI_HSTART_1440x480i60, MSVD_HDMI_VSTART_1440x480i60, 50, 50, 20, 20},  // Zoom1
    },
    {  //1440x480p, 13
        {MSVD_HDMI_HSTART_1440x480p60, MSVD_HDMI_VSTART_1440x480p60, 50, 50, 20, 20},  // Default
        {MSVD_HDMI_HSTART_1440x480p60, MSVD_HDMI_VSTART_1440x480p60, 50, 50, 20, 20},  // 16:9
        {MSVD_HDMI_HSTART_1440x480p60, MSVD_HDMI_VSTART_1440x480p60, 50, 50, 20, 20},  // 4:3
        {MSVD_HDMI_HSTART_1440x480p60, MSVD_HDMI_VSTART_1440x480p60, 50, 50, 20, 20},  // Auto
        {MSVD_HDMI_HSTART_1440x480p60, MSVD_HDMI_VSTART_1440x480p60, 50, 50, 20, 20},  // Panorama
        {MSVD_HDMI_HSTART_1440x480p60, MSVD_HDMI_VSTART_1440x480p60, 0, 0, 0, 0},  // Just Scan
        {MSVD_HDMI_HSTART_1440x480p60, MSVD_HDMI_VSTART_1440x480p60, 50, 50, 20, 20},  // Zoom2
        {MSVD_HDMI_HSTART_1440x480p60, MSVD_HDMI_VSTART_1440x480p60, 50, 50, 20, 20},  // Zoom1
    },
    {  //1440x576i, 14
        {MSVD_HDMI_HSTART_1440x576i50, MSVD_HDMI_VSTART_1440x576i50, 50, 50, 20, 20},  // Default
        {MSVD_HDMI_HSTART_1440x576i50, MSVD_HDMI_VSTART_1440x576i50, 50, 50, 20, 20},  // 16:9
        {MSVD_HDMI_HSTART_1440x576i50, MSVD_HDMI_VSTART_1440x576i50, 50, 50, 20, 20},  // 4:3
        {MSVD_HDMI_HSTART_1440x576i50, MSVD_HDMI_VSTART_1440x576i50, 50, 50, 20, 20},  // Auto
        {MSVD_HDMI_HSTART_1440x576i50, MSVD_HDMI_VSTART_1440x576i50, 50, 50, 20, 20},  // Panorama
        {MSVD_HDMI_HSTART_1440x576i50, MSVD_HDMI_VSTART_1440x576i50, 0, 0, 0, 0},  // Just Scan
        {MSVD_HDMI_HSTART_1440x576i50, MSVD_HDMI_VSTART_1440x576i50, 50, 50, 20, 20},  // Zoom2
        {MSVD_HDMI_HSTART_1440x576i50, MSVD_HDMI_VSTART_1440x576i50, 50, 50, 20, 20},  // Zoom1
    },
    {  //1440x576p, 15
        {MSVD_HDMI_HSTART_1440x576p50, MSVD_HDMI_VSTART_1440x576p50, 50, 50, 20, 20},  // Default
        {MSVD_HDMI_HSTART_1440x576p50, MSVD_HDMI_VSTART_1440x576p50, 50, 50, 20, 20},  // 16:9
        {MSVD_HDMI_HSTART_1440x576p50, MSVD_HDMI_VSTART_1440x576p50, 50, 50, 20, 20},  // 4:3
        {MSVD_HDMI_HSTART_1440x576p50, MSVD_HDMI_VSTART_1440x576p50, 50, 50, 20, 20},  // Auto
        {MSVD_HDMI_HSTART_1440x576p50, MSVD_HDMI_VSTART_1440x576p50, 50, 50, 20, 20},  // Panorama
        {MSVD_HDMI_HSTART_1440x576p50, MSVD_HDMI_VSTART_1440x576p50, 0, 0, 0, 0},  // Just Scan
        {MSVD_HDMI_HSTART_1440x576p50, MSVD_HDMI_VSTART_1440x576p50, 50, 50, 20, 20},  // Zoom2
        {MSVD_HDMI_HSTART_1440x576p50, MSVD_HDMI_VSTART_1440x576p50, 50, 50, 20, 20},  // Zoom1
    },
    {  //640x480i_60, 16    //Copy from 720x480i
        {MSVD_HDMI_HSTART_480i60, MSVD_HDMI_VSTART_480i60, 16, 16, 13, 13},  // Default
        {MSVD_HDMI_HSTART_480i60, MSVD_HDMI_VSTART_480i60, 16, 16, 13, 13},  // 16:9
        {MSVD_HDMI_HSTART_480i60, MSVD_HDMI_VSTART_480i60, 16, 16, 13, 13},  // 4:3
        {MSVD_HDMI_HSTART_480i60, MSVD_HDMI_VSTART_480i60, 16, 16, 13, 13},  // Auto
        {MSVD_HDMI_HSTART_480i60, MSVD_HDMI_VSTART_480i60, 16, 16, 13, 13},  // Panorama
        {MSVD_HDMI_HSTART_480i60, MSVD_HDMI_VSTART_480i60, 16, 16, 13, 13},  // Just Scan
        {MSVD_HDMI_HSTART_480i60, MSVD_HDMI_VSTART_480i60, 16, 16, 13, 13},  // Zoom2
        {MSVD_HDMI_HSTART_480i60, MSVD_HDMI_VSTART_480i60, 16, 16, 13, 13},  // Zoom1
    },
    {  //640x480P_60, 17    //Copy from 720x480P
        {MSVD_HDMI_HSTART_480p60, MSVD_HDMI_VSTART_480p60, 13, 13, 9, 9},  // Default
        {MSVD_HDMI_HSTART_480p60, MSVD_HDMI_VSTART_480p60, 13, 13, 9, 9},  // 16:9
        {MSVD_HDMI_HSTART_480p60, MSVD_HDMI_VSTART_480p60, 13, 13, 9, 9},  // 4:3
        {MSVD_HDMI_HSTART_480p60, MSVD_HDMI_VSTART_480p60, 13, 13, 9, 9},  // Auto
        {MSVD_HDMI_HSTART_480p60, MSVD_HDMI_VSTART_480p60, 13, 13, 9, 9},  // Panorama
        {MSVD_HDMI_HSTART_480p60, MSVD_HDMI_VSTART_480p60, 13, 13, 9, 9},  // Just Scan
        {MSVD_HDMI_HSTART_480p60, MSVD_HDMI_VSTART_480p60, 13, 13, 9, 9},  // Zoom2
        {MSVD_HDMI_HSTART_480p60, MSVD_HDMI_VSTART_480p60, 13, 13, 9, 9},  // Zoom1
    },

};

//********************************************************************************
//                     Local
//********************************************************************************

// zoom numerator of left/right/up/down & zoom denumerator
#define ZOOM_NUMERATOR_LEFTMAX      200
#define ZOOM_NUMERATOR_RIGHTMAX     200
#define ZOOM_NUMERATOR_UPMAX        200
#define ZOOM_NUMERATOR_DOWNMAX      200
#define ZOOM_DENUMERATOR            1000

#define ACCURATE_VFREQ_TOLERANCE 1000

static S16 _s16ZoomLeft;
static S16 _s16ZoomRight;
static S16 _s16ZoomUp;
static S16 _s16ZoomDown;

static BOOLEAN _u8EnableOverScan;
static U8 _u8H_OverScanRatio;
static U8 _u8V_OverScanRatio;

static U8 _u8H_CropRatio_Left;
static U8 _u8H_CropRatio_Right;
static U8 _u8V_CropRatio_Up;
static U8 _u8V_CropRatio_Down;

static BOOLEAN _bEnNonLinearScaling[PIP_WINDOWS];             // Daten FixMe, MAX_WINDOW will be removed and can be obtained from MApi_XC_GetInfo()
static BOOLEAN _bEnHDMI_RefineHVStart = FALSE;

#if ENABLE_3D_PROCESS
static BOOLEAN _bManualDetectTiming = FALSE;
#endif

static XC_SETWIN_INFO stXC_SetWin_Info[PIP_WINDOWS];
static MS_VIDEO_Window_Info_EXT st_VidWin_Info;

// DTV
static U16 _u16OverscanDtvDefaultH = 10;
static U16 _u16OverscanDtvDefaultV = 10;
static U16 _u16OverscanDtv480iH = 35;
static U16 _u16OverscanDtv480iV = 28;
static U16 _u16OverscanDtv480pH = 34;
static U16 _u16OverscanDtv480pV = 34;
static U16 _u16OverscanDtv576iH = 32;
static U16 _u16OverscanDtv576iV = 23;
static U16 _u16OverscanDtv576pH = 20;
static U16 _u16OverscanDtv576pV = 20;
static U16 _u16OverscanDtv720pH = 34;
static U16 _u16OverscanDtv720pV = 34;
static U16 _u16OverscanDtv1080iH = 31;
static U16 _u16OverscanDtv1080iV = 30;
static U16 _u16OverscanDtv1080pH = 33;
static U16 _u16OverscanDtv1080pV = 33;

#if (ENABLE_3D_PROCESS )
static ST_3D_BEHAVIOR st3DBehavior_All_Passive;
static ST_3D_BEHAVIOR st3DBehavior_IN8903_Simple;
static ST_3D_BEHAVIOR st3DBehavior_IN8903_PQ_Optimize;

static ST_3D_BEHAVIOR* ast3DBehaviorTbl[] =
{
    &st3DBehavior_All_Passive,
    &st3DBehavior_IN8903_Simple,
    &st3DBehavior_IN8903_PQ_Optimize,
};

static EN_3D_BEHAVIOR_IDX en3DBehaviorSelect = (EN_3D_BEHAVIOR_IDX)DEFAULT_3D_BEHAVIOR_SEL;
#endif


#if(ENABLE_CHECK_SET_WIN_RESULT)
BOOLEAN g_Scaler_bSetWidnowResult = TRUE;
#endif

/********************************************************************************/
/*              Functions                                           */
/* ******************************************************************************/
static U8 _MApp_Scaler_Resolution_Remapping(XC_SETWIN_INFO *pstXC_SetWin_Info, SCALER_WIN eWindow );
static U8 _MApp_Scaler_Aspect_Ratio_Remapping(EN_ASPECT_RATIO_TYPE enVideoScreen);
PQ_WIN _MApp_Scaler_SCALER_WIN_to_PQ_WIN(SCALER_WIN eWindow);
#if (ENABLE_TCON_IN8903_PROCESS)
IN8903_PANEL_3D_FORMAT MAPP_Scaler_MapUi3DFormatToIn8903_3DMode(EN_3D_TYPE enUi3DType);
#endif
void MApp_Gop_init(void);


#if ENABLE_BACKLIGHT_PWM_SYNC_WITH_FRAMERATE
void SetPWMto2PanelVFreq(U8 ratio)
{
    MS_U32 OutputVFreqX100 = MApi_XC_GetOutputVFreqX100();
    MS_U32 u32PWM_PERIOD;

    u32PWM_PERIOD = (long)(12000000 * 100)/(OutputVFreqX100 * ratio);

    MDrv_PWM_Period(E_PWM_CH0, u32PWM_PERIOD);
    MDrv_PWM_DutyCycle(E_PWM_CH0, 50);
    printf("\n wz@ OutputVFreqX100=%d\n", OutputVFreqX100);
    printf("\n wz@ u32PWM_PERIOD=%d\n", u32PWM_PERIOD);
    printf("\n wz@ u32PWM_PERIOD=0x%x\n", u32PWM_PERIOD);
}
#endif

#if (ENABLE_3D_PROCESS)   // anvi
char* MApp_Scaler_Get_Ui3DTypeName(EN_3D_TYPE e3DType)
{
    if(e3DType >= EN_3D_TYPE_NUM)
    {
        return NULL;
    }

    switch(e3DType)
    {
        default:
        case EN_3D_BYPASS:
            return "EN_3D_BYPASS";

        case EN_3D_FRAME_PACKING:
            return "EN_3D_FRAME_PACKING";

        case EN_3D_SIDE_BY_SIDE:
            return "EN_3D_SIDE_BY_SIDE";

        case EN_3D_TOP_BOTTOM:
            return "EN_3D_TOP_BOTTOM";

        case EN_3D_LINE_ALTERNATIVE:
            return "EN_3D_LINE_ALTERNATIVE";

        case EN_3D_FRAME_ALTERNATIVE:
            return "EN_3D_FRAME_ALTERNATIVE";

        case EN_3D_2DConvertTo3D:
            return "EN_3D_2DConvertTo3D";

        case EN_3D_FRAME_L:
            return "EN_3D_FRAME_L(L-only)";
    }

    return "Ui3DType_XXX";
}

char* _MApp_Scaler_3D_GetResolutionTypeString(EN_4K2K_OUTPUT_RESOLUTION_TYPE eResType)
{
    if(eResType >= E_OUTPUT_RESOLUTION_MAX)
    {
        return NULL;
    }

    switch(eResType)
    {
        default:
        case E_OUTPUT_RESOLUTION_3840X2160:
            return "OUTPUT_RESOLUTION_3840X2160";

        case E_OUTPUT_RESOLUTION_1920X1080:
            return "OUTPUT_RESOLUTION_1920X1080";

        case E_OUTPUT_RESOLUTION_3840X1080:
            return "OUTPUT_RESOLUTION_3840X1080";
    }
}

void MApp_Scaler_3D_Behavior_init(void)
{
    U16 u16PanelWidth = g_IPanel.Width();
    EN_4K2K_OUTPUT_RESOLUTION_TYPE enFixedResolutionForNormalPanel;

    if(u16PanelWidth == 3840)
    {
        enFixedResolutionForNormalPanel = E_OUTPUT_RESOLUTION_3840X2160;
    }
    else
    {
        enFixedResolutionForNormalPanel = E_OUTPUT_RESOLUTION_1920X1080;
    }

    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_BYPASS].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_BYPASS].enScalerOutput3DType = EN_3D_BYPASS;
    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_BYPASS].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_BYPASS].enResolution = enFixedResolutionForNormalPanel;

    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_FRAME_PACKING].enScalerInput3DType = EN_3D_FRAME_PACKING;
    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_FRAME_PACKING].enScalerOutput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_FRAME_PACKING].enBackEndInput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_FRAME_PACKING].enResolution = enFixedResolutionForNormalPanel;

    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_SIDE_BY_SIDE].enScalerInput3DType = EN_3D_SIDE_BY_SIDE;
    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_SIDE_BY_SIDE].enScalerOutput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_SIDE_BY_SIDE].enBackEndInput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_SIDE_BY_SIDE].enResolution = enFixedResolutionForNormalPanel;

    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_TOP_BOTTOM].enScalerInput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_TOP_BOTTOM].enScalerOutput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_TOP_BOTTOM].enBackEndInput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_TOP_BOTTOM].enResolution = enFixedResolutionForNormalPanel;

    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_LINE_ALTERNATIVE].enScalerInput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_LINE_ALTERNATIVE].enScalerOutput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_LINE_ALTERNATIVE].enBackEndInput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_LINE_ALTERNATIVE].enResolution = enFixedResolutionForNormalPanel;

    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enScalerInput3DType = EN_3D_FRAME_ALTERNATIVE;
    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enScalerOutput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enBackEndInput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enResolution = enFixedResolutionForNormalPanel;

#if 1//((CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA)||(CHIP_FAMILY_TYPE == CHIP_FAMILY_WHISKY))
    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_2DConvertTo3D].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_2DConvertTo3D].enScalerOutput3DType = EN_3D_BYPASS;    //Maya doesn't support 2Dto3D
    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_2DConvertTo3D].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_2DConvertTo3D].enResolution = enFixedResolutionForNormalPanel;
#else
    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_2DConvertTo3D].enScalerInput3DType = EN_3D_2DConvertTo3D;
    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_2DConvertTo3D].enScalerOutput3DType = EN_3D_2DConvertTo3D;    //Maya doesn't support 2Dto3D
    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_2DConvertTo3D].enBackEndInput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_2DConvertTo3D].enResolution = enFixedResolutionForNormalPanel;
#endif

    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_FRAME_L].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_FRAME_L].enScalerOutput3DType = EN_3D_BYPASS;
    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_FRAME_L].enBackEndInput3DType = EN_3D_BYPASS ;
    st3DBehavior_All_Passive.st3DConvertRule[EN_3D_FRAME_L].enResolution = enFixedResolutionForNormalPanel;



    st3DBehavior_All_Passive.st4K2K_Under60Hz_3DConvertRule[EN_3D_BYPASS].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_All_Passive.st4K2K_Under60Hz_3DConvertRule[EN_3D_BYPASS].enScalerOutput3DType = EN_3D_BYPASS;
    st3DBehavior_All_Passive.st4K2K_Under60Hz_3DConvertRule[EN_3D_BYPASS].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_All_Passive.st4K2K_Under60Hz_3DConvertRule[EN_3D_BYPASS].enResolution = enFixedResolutionForNormalPanel;

    st3DBehavior_All_Passive.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_PACKING].enScalerInput3DType = EN_3D_FRAME_PACKING;
    st3DBehavior_All_Passive.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_PACKING].enScalerOutput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_PACKING].enBackEndInput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_PACKING].enResolution = enFixedResolutionForNormalPanel;

    st3DBehavior_All_Passive.st4K2K_Under60Hz_3DConvertRule[EN_3D_SIDE_BY_SIDE].enScalerInput3DType = EN_3D_SIDE_BY_SIDE;
    st3DBehavior_All_Passive.st4K2K_Under60Hz_3DConvertRule[EN_3D_SIDE_BY_SIDE].enScalerOutput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st4K2K_Under60Hz_3DConvertRule[EN_3D_SIDE_BY_SIDE].enBackEndInput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st4K2K_Under60Hz_3DConvertRule[EN_3D_SIDE_BY_SIDE].enResolution = enFixedResolutionForNormalPanel;

    st3DBehavior_All_Passive.st4K2K_Under60Hz_3DConvertRule[EN_3D_TOP_BOTTOM].enScalerInput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_All_Passive.st4K2K_Under60Hz_3DConvertRule[EN_3D_TOP_BOTTOM].enScalerOutput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st4K2K_Under60Hz_3DConvertRule[EN_3D_TOP_BOTTOM].enBackEndInput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st4K2K_Under60Hz_3DConvertRule[EN_3D_TOP_BOTTOM].enResolution = enFixedResolutionForNormalPanel;

    st3DBehavior_All_Passive.st4K2K_Under60Hz_3DConvertRule[EN_3D_LINE_ALTERNATIVE].enScalerInput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st4K2K_Under60Hz_3DConvertRule[EN_3D_LINE_ALTERNATIVE].enScalerOutput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st4K2K_Under60Hz_3DConvertRule[EN_3D_LINE_ALTERNATIVE].enBackEndInput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st4K2K_Under60Hz_3DConvertRule[EN_3D_LINE_ALTERNATIVE].enResolution = enFixedResolutionForNormalPanel;

    st3DBehavior_All_Passive.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enScalerInput3DType = EN_3D_FRAME_ALTERNATIVE;
    st3DBehavior_All_Passive.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enScalerOutput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enBackEndInput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enResolution = enFixedResolutionForNormalPanel;

    st3DBehavior_All_Passive.st4K2K_Under60Hz_3DConvertRule[EN_3D_2DConvertTo3D].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_All_Passive.st4K2K_Under60Hz_3DConvertRule[EN_3D_2DConvertTo3D].enScalerOutput3DType = EN_3D_BYPASS;    //Maya doesn't support 2Dto3D
    st3DBehavior_All_Passive.st4K2K_Under60Hz_3DConvertRule[EN_3D_2DConvertTo3D].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_All_Passive.st4K2K_Under60Hz_3DConvertRule[EN_3D_2DConvertTo3D].enResolution = enFixedResolutionForNormalPanel;

    st3DBehavior_All_Passive.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_L].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_All_Passive.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_L].enScalerOutput3DType = EN_3D_BYPASS;
    st3DBehavior_All_Passive.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_L].enBackEndInput3DType = EN_3D_BYPASS ;
    st3DBehavior_All_Passive.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_L].enResolution = enFixedResolutionForNormalPanel;



    st3DBehavior_All_Passive.st4K2K_60Hz_3DConvertRule[EN_3D_BYPASS].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_All_Passive.st4K2K_60Hz_3DConvertRule[EN_3D_BYPASS].enScalerOutput3DType = EN_3D_BYPASS;
    st3DBehavior_All_Passive.st4K2K_60Hz_3DConvertRule[EN_3D_BYPASS].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_All_Passive.st4K2K_60Hz_3DConvertRule[EN_3D_BYPASS].enResolution = enFixedResolutionForNormalPanel;

    st3DBehavior_All_Passive.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_PACKING].enScalerInput3DType = EN_3D_FRAME_PACKING;
    st3DBehavior_All_Passive.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_PACKING].enScalerOutput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_PACKING].enBackEndInput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_PACKING].enResolution = enFixedResolutionForNormalPanel;

    st3DBehavior_All_Passive.st4K2K_60Hz_3DConvertRule[EN_3D_SIDE_BY_SIDE].enScalerInput3DType = EN_3D_SIDE_BY_SIDE;
    st3DBehavior_All_Passive.st4K2K_60Hz_3DConvertRule[EN_3D_SIDE_BY_SIDE].enScalerOutput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st4K2K_60Hz_3DConvertRule[EN_3D_SIDE_BY_SIDE].enBackEndInput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st4K2K_60Hz_3DConvertRule[EN_3D_SIDE_BY_SIDE].enResolution = enFixedResolutionForNormalPanel;

    st3DBehavior_All_Passive.st4K2K_60Hz_3DConvertRule[EN_3D_TOP_BOTTOM].enScalerInput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_All_Passive.st4K2K_60Hz_3DConvertRule[EN_3D_TOP_BOTTOM].enScalerOutput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st4K2K_60Hz_3DConvertRule[EN_3D_TOP_BOTTOM].enBackEndInput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st4K2K_60Hz_3DConvertRule[EN_3D_TOP_BOTTOM].enResolution = enFixedResolutionForNormalPanel;

    st3DBehavior_All_Passive.st4K2K_60Hz_3DConvertRule[EN_3D_LINE_ALTERNATIVE].enScalerInput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st4K2K_60Hz_3DConvertRule[EN_3D_LINE_ALTERNATIVE].enScalerOutput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st4K2K_60Hz_3DConvertRule[EN_3D_LINE_ALTERNATIVE].enBackEndInput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st4K2K_60Hz_3DConvertRule[EN_3D_LINE_ALTERNATIVE].enResolution = enFixedResolutionForNormalPanel;

    st3DBehavior_All_Passive.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enScalerInput3DType = EN_3D_FRAME_ALTERNATIVE;
    st3DBehavior_All_Passive.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enScalerOutput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enBackEndInput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enResolution = enFixedResolutionForNormalPanel;

    st3DBehavior_All_Passive.st4K2K_60Hz_3DConvertRule[EN_3D_2DConvertTo3D].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_All_Passive.st4K2K_60Hz_3DConvertRule[EN_3D_2DConvertTo3D].enScalerOutput3DType = EN_3D_BYPASS;    //Maya doesn't support 2Dto3D
    st3DBehavior_All_Passive.st4K2K_60Hz_3DConvertRule[EN_3D_2DConvertTo3D].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_All_Passive.st4K2K_60Hz_3DConvertRule[EN_3D_2DConvertTo3D].enResolution = enFixedResolutionForNormalPanel;

    st3DBehavior_All_Passive.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_L].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_All_Passive.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_L].enScalerOutput3DType = EN_3D_BYPASS;
    st3DBehavior_All_Passive.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_L].enBackEndInput3DType = EN_3D_BYPASS ;
    st3DBehavior_All_Passive.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_L].enResolution = enFixedResolutionForNormalPanel;



    st3DBehavior_All_Passive.st3DTo2DConvertRule[EN_3D_BYPASS].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_All_Passive.st3DTo2DConvertRule[EN_3D_BYPASS].enScalerOutput3DType = EN_3D_BYPASS;
    st3DBehavior_All_Passive.st3DTo2DConvertRule[EN_3D_BYPASS].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_All_Passive.st3DTo2DConvertRule[EN_3D_BYPASS].enResolution = enFixedResolutionForNormalPanel;

    st3DBehavior_All_Passive.st3DTo2DConvertRule[EN_3D_FRAME_PACKING].enScalerInput3DType = EN_3D_FRAME_PACKING;
    st3DBehavior_All_Passive.st3DTo2DConvertRule[EN_3D_FRAME_PACKING].enScalerOutput3DType = EN_3D_FRAME_L;
    st3DBehavior_All_Passive.st3DTo2DConvertRule[EN_3D_FRAME_PACKING].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_All_Passive.st3DTo2DConvertRule[EN_3D_FRAME_PACKING].enResolution = enFixedResolutionForNormalPanel;

    st3DBehavior_All_Passive.st3DTo2DConvertRule[EN_3D_SIDE_BY_SIDE].enScalerInput3DType = EN_3D_SIDE_BY_SIDE;
    st3DBehavior_All_Passive.st3DTo2DConvertRule[EN_3D_SIDE_BY_SIDE].enScalerOutput3DType = EN_3D_FRAME_L;
    st3DBehavior_All_Passive.st3DTo2DConvertRule[EN_3D_SIDE_BY_SIDE].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_All_Passive.st3DTo2DConvertRule[EN_3D_SIDE_BY_SIDE].enResolution = enFixedResolutionForNormalPanel;

    st3DBehavior_All_Passive.st3DTo2DConvertRule[EN_3D_TOP_BOTTOM].enScalerInput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_All_Passive.st3DTo2DConvertRule[EN_3D_TOP_BOTTOM].enScalerOutput3DType = EN_3D_FRAME_L;
    st3DBehavior_All_Passive.st3DTo2DConvertRule[EN_3D_TOP_BOTTOM].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_All_Passive.st3DTo2DConvertRule[EN_3D_TOP_BOTTOM].enResolution = enFixedResolutionForNormalPanel;

    st3DBehavior_All_Passive.st3DTo2DConvertRule[EN_3D_LINE_ALTERNATIVE].enScalerInput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_All_Passive.st3DTo2DConvertRule[EN_3D_LINE_ALTERNATIVE].enScalerOutput3DType = EN_3D_FRAME_L;
    st3DBehavior_All_Passive.st3DTo2DConvertRule[EN_3D_LINE_ALTERNATIVE].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_All_Passive.st3DTo2DConvertRule[EN_3D_LINE_ALTERNATIVE].enResolution = enFixedResolutionForNormalPanel;

    st3DBehavior_All_Passive.st3DTo2DConvertRule[EN_3D_FRAME_ALTERNATIVE].enScalerInput3DType = EN_3D_FRAME_ALTERNATIVE;
    st3DBehavior_All_Passive.st3DTo2DConvertRule[EN_3D_FRAME_ALTERNATIVE].enScalerOutput3DType = EN_3D_FRAME_L;
    st3DBehavior_All_Passive.st3DTo2DConvertRule[EN_3D_FRAME_ALTERNATIVE].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_All_Passive.st3DTo2DConvertRule[EN_3D_FRAME_ALTERNATIVE].enResolution = enFixedResolutionForNormalPanel;

    st3DBehavior_All_Passive.st3DTo2DConvertRule[EN_3D_2DConvertTo3D].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_All_Passive.st3DTo2DConvertRule[EN_3D_2DConvertTo3D].enScalerOutput3DType = EN_3D_BYPASS;    //Maya doesn't support 2Dto3D
    st3DBehavior_All_Passive.st3DTo2DConvertRule[EN_3D_2DConvertTo3D].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_All_Passive.st3DTo2DConvertRule[EN_3D_2DConvertTo3D].enResolution = enFixedResolutionForNormalPanel;

    st3DBehavior_All_Passive.st3DTo2DConvertRule[EN_3D_FRAME_L].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_All_Passive.st3DTo2DConvertRule[EN_3D_FRAME_L].enScalerOutput3DType = EN_3D_BYPASS;
    st3DBehavior_All_Passive.st3DTo2DConvertRule[EN_3D_FRAME_L].enBackEndInput3DType = EN_3D_BYPASS ;
    st3DBehavior_All_Passive.st3DTo2DConvertRule[EN_3D_FRAME_L].enResolution = enFixedResolutionForNormalPanel;




    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_BYPASS].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_BYPASS].enScalerOutput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_BYPASS].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_BYPASS].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_FRAME_PACKING].enScalerInput3DType = EN_3D_FRAME_PACKING;
    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_FRAME_PACKING].enScalerOutput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_FRAME_PACKING].enBackEndInput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_FRAME_PACKING].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_SIDE_BY_SIDE].enScalerInput3DType = EN_3D_SIDE_BY_SIDE;
    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_SIDE_BY_SIDE].enScalerOutput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_SIDE_BY_SIDE].enBackEndInput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_SIDE_BY_SIDE].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_TOP_BOTTOM].enScalerInput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_TOP_BOTTOM].enScalerOutput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_TOP_BOTTOM].enBackEndInput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_TOP_BOTTOM].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_LINE_ALTERNATIVE].enScalerInput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_LINE_ALTERNATIVE].enScalerOutput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_LINE_ALTERNATIVE].enBackEndInput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_LINE_ALTERNATIVE].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enScalerInput3DType = EN_3D_FRAME_ALTERNATIVE;
    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enScalerOutput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enBackEndInput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

#if 1//((CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA)||(CHIP_FAMILY_TYPE == CHIP_FAMILY_WHISKY))
    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_2DConvertTo3D].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_2DConvertTo3D].enScalerOutput3DType = EN_3D_BYPASS;    //Maya doesn't support 2Dto3D
    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_2DConvertTo3D].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_2DConvertTo3D].enResolution = E_OUTPUT_RESOLUTION_3840X2160;
#else
    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_2DConvertTo3D].enScalerInput3DType = EN_3D_2DConvertTo3D;
    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_2DConvertTo3D].enScalerOutput3DType = EN_3D_2DConvertTo3D;    //Maya doesn't support 2Dto3D
    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_2DConvertTo3D].enBackEndInput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_2DConvertTo3D].enResolution = E_OUTPUT_RESOLUTION_3840X2160;
#endif

    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_FRAME_L].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_FRAME_L].enScalerOutput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_FRAME_L].enBackEndInput3DType = EN_3D_BYPASS ;
    st3DBehavior_IN8903_Simple.st3DConvertRule[EN_3D_FRAME_L].enResolution = E_OUTPUT_RESOLUTION_3840X2160;



    st3DBehavior_IN8903_Simple.st4K2K_Under60Hz_3DConvertRule[EN_3D_BYPASS].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_Simple.st4K2K_Under60Hz_3DConvertRule[EN_3D_BYPASS].enScalerOutput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_Simple.st4K2K_Under60Hz_3DConvertRule[EN_3D_BYPASS].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_Simple.st4K2K_Under60Hz_3DConvertRule[EN_3D_BYPASS].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_Simple.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_PACKING].enScalerInput3DType = EN_3D_FRAME_PACKING;
    st3DBehavior_IN8903_Simple.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_PACKING].enScalerOutput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_Simple.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_PACKING].enBackEndInput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_Simple.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_PACKING].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_Simple.st4K2K_Under60Hz_3DConvertRule[EN_3D_SIDE_BY_SIDE].enScalerInput3DType = EN_3D_SIDE_BY_SIDE;
    st3DBehavior_IN8903_Simple.st4K2K_Under60Hz_3DConvertRule[EN_3D_SIDE_BY_SIDE].enScalerOutput3DType = EN_3D_FRAME_ALTERNATIVE;
    st3DBehavior_IN8903_Simple.st4K2K_Under60Hz_3DConvertRule[EN_3D_SIDE_BY_SIDE].enBackEndInput3DType = EN_3D_FRAME_ALTERNATIVE;
    st3DBehavior_IN8903_Simple.st4K2K_Under60Hz_3DConvertRule[EN_3D_SIDE_BY_SIDE].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_Simple.st4K2K_Under60Hz_3DConvertRule[EN_3D_TOP_BOTTOM].enScalerInput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_Simple.st4K2K_Under60Hz_3DConvertRule[EN_3D_TOP_BOTTOM].enScalerOutput3DType = EN_3D_FRAME_ALTERNATIVE;
    st3DBehavior_IN8903_Simple.st4K2K_Under60Hz_3DConvertRule[EN_3D_TOP_BOTTOM].enBackEndInput3DType = EN_3D_FRAME_ALTERNATIVE;
    st3DBehavior_IN8903_Simple.st4K2K_Under60Hz_3DConvertRule[EN_3D_TOP_BOTTOM].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_Simple.st4K2K_Under60Hz_3DConvertRule[EN_3D_LINE_ALTERNATIVE].enScalerInput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_IN8903_Simple.st4K2K_Under60Hz_3DConvertRule[EN_3D_LINE_ALTERNATIVE].enScalerOutput3DType = EN_3D_FRAME_ALTERNATIVE;
    st3DBehavior_IN8903_Simple.st4K2K_Under60Hz_3DConvertRule[EN_3D_LINE_ALTERNATIVE].enBackEndInput3DType = EN_3D_FRAME_ALTERNATIVE;
    st3DBehavior_IN8903_Simple.st4K2K_Under60Hz_3DConvertRule[EN_3D_LINE_ALTERNATIVE].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_Simple.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enScalerInput3DType = EN_3D_FRAME_ALTERNATIVE;
    st3DBehavior_IN8903_Simple.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enScalerOutput3DType = EN_3D_FRAME_ALTERNATIVE;
    st3DBehavior_IN8903_Simple.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enBackEndInput3DType = EN_3D_FRAME_ALTERNATIVE;
    st3DBehavior_IN8903_Simple.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_Simple.st4K2K_Under60Hz_3DConvertRule[EN_3D_2DConvertTo3D].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_Simple.st4K2K_Under60Hz_3DConvertRule[EN_3D_2DConvertTo3D].enScalerOutput3DType = EN_3D_BYPASS;    //Maya doesn't support 2Dto3D
    st3DBehavior_IN8903_Simple.st4K2K_Under60Hz_3DConvertRule[EN_3D_2DConvertTo3D].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_Simple.st4K2K_Under60Hz_3DConvertRule[EN_3D_2DConvertTo3D].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_Simple.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_L].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_Simple.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_L].enScalerOutput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_Simple.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_L].enBackEndInput3DType = EN_3D_BYPASS ;
    st3DBehavior_IN8903_Simple.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_L].enResolution = E_OUTPUT_RESOLUTION_3840X2160;



    st3DBehavior_IN8903_Simple.st4K2K_60Hz_3DConvertRule[EN_3D_BYPASS].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_Simple.st4K2K_60Hz_3DConvertRule[EN_3D_BYPASS].enScalerOutput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_Simple.st4K2K_60Hz_3DConvertRule[EN_3D_BYPASS].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_Simple.st4K2K_60Hz_3DConvertRule[EN_3D_BYPASS].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_Simple.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_PACKING].enScalerInput3DType = EN_3D_FRAME_PACKING;
    st3DBehavior_IN8903_Simple.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_PACKING].enScalerOutput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_Simple.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_PACKING].enBackEndInput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_Simple.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_PACKING].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_Simple.st4K2K_60Hz_3DConvertRule[EN_3D_SIDE_BY_SIDE].enScalerInput3DType = EN_3D_SIDE_BY_SIDE;
    st3DBehavior_IN8903_Simple.st4K2K_60Hz_3DConvertRule[EN_3D_SIDE_BY_SIDE].enScalerOutput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_Simple.st4K2K_60Hz_3DConvertRule[EN_3D_SIDE_BY_SIDE].enBackEndInput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_Simple.st4K2K_60Hz_3DConvertRule[EN_3D_SIDE_BY_SIDE].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_Simple.st4K2K_60Hz_3DConvertRule[EN_3D_TOP_BOTTOM].enScalerInput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_Simple.st4K2K_60Hz_3DConvertRule[EN_3D_TOP_BOTTOM].enScalerOutput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_Simple.st4K2K_60Hz_3DConvertRule[EN_3D_TOP_BOTTOM].enBackEndInput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_Simple.st4K2K_60Hz_3DConvertRule[EN_3D_TOP_BOTTOM].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_Simple.st4K2K_60Hz_3DConvertRule[EN_3D_LINE_ALTERNATIVE].enScalerInput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_IN8903_Simple.st4K2K_60Hz_3DConvertRule[EN_3D_LINE_ALTERNATIVE].enScalerOutput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_Simple.st4K2K_60Hz_3DConvertRule[EN_3D_LINE_ALTERNATIVE].enBackEndInput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_Simple.st4K2K_60Hz_3DConvertRule[EN_3D_LINE_ALTERNATIVE].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_Simple.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enScalerInput3DType = EN_3D_FRAME_ALTERNATIVE;
    st3DBehavior_IN8903_Simple.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enScalerOutput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_Simple.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enBackEndInput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_Simple.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_Simple.st4K2K_60Hz_3DConvertRule[EN_3D_2DConvertTo3D].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_Simple.st4K2K_60Hz_3DConvertRule[EN_3D_2DConvertTo3D].enScalerOutput3DType = EN_3D_BYPASS;    //Maya doesn't support 2Dto3D
    st3DBehavior_IN8903_Simple.st4K2K_60Hz_3DConvertRule[EN_3D_2DConvertTo3D].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_Simple.st4K2K_60Hz_3DConvertRule[EN_3D_2DConvertTo3D].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_Simple.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_L].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_Simple.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_L].enScalerOutput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_Simple.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_L].enBackEndInput3DType = EN_3D_BYPASS ;
    st3DBehavior_IN8903_Simple.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_L].enResolution = E_OUTPUT_RESOLUTION_3840X2160;



    st3DBehavior_IN8903_Simple.st3DTo2DConvertRule[EN_3D_BYPASS].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_Simple.st3DTo2DConvertRule[EN_3D_BYPASS].enScalerOutput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_Simple.st3DTo2DConvertRule[EN_3D_BYPASS].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_Simple.st3DTo2DConvertRule[EN_3D_BYPASS].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_Simple.st3DTo2DConvertRule[EN_3D_FRAME_PACKING].enScalerInput3DType = EN_3D_FRAME_PACKING;
    st3DBehavior_IN8903_Simple.st3DTo2DConvertRule[EN_3D_FRAME_PACKING].enScalerOutput3DType = EN_3D_FRAME_L;
    st3DBehavior_IN8903_Simple.st3DTo2DConvertRule[EN_3D_FRAME_PACKING].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_Simple.st3DTo2DConvertRule[EN_3D_FRAME_PACKING].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_Simple.st3DTo2DConvertRule[EN_3D_SIDE_BY_SIDE].enScalerInput3DType = EN_3D_SIDE_BY_SIDE;
    st3DBehavior_IN8903_Simple.st3DTo2DConvertRule[EN_3D_SIDE_BY_SIDE].enScalerOutput3DType = EN_3D_FRAME_L;
    st3DBehavior_IN8903_Simple.st3DTo2DConvertRule[EN_3D_SIDE_BY_SIDE].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_Simple.st3DTo2DConvertRule[EN_3D_SIDE_BY_SIDE].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_Simple.st3DTo2DConvertRule[EN_3D_TOP_BOTTOM].enScalerInput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_Simple.st3DTo2DConvertRule[EN_3D_TOP_BOTTOM].enScalerOutput3DType = EN_3D_FRAME_L;
    st3DBehavior_IN8903_Simple.st3DTo2DConvertRule[EN_3D_TOP_BOTTOM].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_Simple.st3DTo2DConvertRule[EN_3D_TOP_BOTTOM].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_Simple.st3DTo2DConvertRule[EN_3D_LINE_ALTERNATIVE].enScalerInput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_IN8903_Simple.st3DTo2DConvertRule[EN_3D_LINE_ALTERNATIVE].enScalerOutput3DType = EN_3D_FRAME_L;
    st3DBehavior_IN8903_Simple.st3DTo2DConvertRule[EN_3D_LINE_ALTERNATIVE].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_Simple.st3DTo2DConvertRule[EN_3D_LINE_ALTERNATIVE].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_Simple.st3DTo2DConvertRule[EN_3D_FRAME_ALTERNATIVE].enScalerInput3DType = EN_3D_FRAME_ALTERNATIVE;
    st3DBehavior_IN8903_Simple.st3DTo2DConvertRule[EN_3D_FRAME_ALTERNATIVE].enScalerOutput3DType = EN_3D_FRAME_L;
    st3DBehavior_IN8903_Simple.st3DTo2DConvertRule[EN_3D_FRAME_ALTERNATIVE].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_Simple.st3DTo2DConvertRule[EN_3D_FRAME_ALTERNATIVE].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_Simple.st3DTo2DConvertRule[EN_3D_2DConvertTo3D].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_Simple.st3DTo2DConvertRule[EN_3D_2DConvertTo3D].enScalerOutput3DType = EN_3D_BYPASS;    //Maya doesn't support 2Dto3D
    st3DBehavior_IN8903_Simple.st3DTo2DConvertRule[EN_3D_2DConvertTo3D].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_Simple.st3DTo2DConvertRule[EN_3D_2DConvertTo3D].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_Simple.st3DTo2DConvertRule[EN_3D_FRAME_L].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_Simple.st3DTo2DConvertRule[EN_3D_FRAME_L].enScalerOutput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_Simple.st3DTo2DConvertRule[EN_3D_FRAME_L].enBackEndInput3DType = EN_3D_BYPASS ;
    st3DBehavior_IN8903_Simple.st3DTo2DConvertRule[EN_3D_FRAME_L].enResolution = E_OUTPUT_RESOLUTION_3840X2160;



    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_BYPASS].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_BYPASS].enScalerOutput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_BYPASS].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_BYPASS].enResolution = E_OUTPUT_RESOLUTION_1920X1080;

    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_FRAME_PACKING].enScalerInput3DType = EN_3D_FRAME_PACKING;
    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_FRAME_PACKING].enScalerOutput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_FRAME_PACKING].enBackEndInput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_FRAME_PACKING].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_SIDE_BY_SIDE].enScalerInput3DType = EN_3D_SIDE_BY_SIDE;
    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_SIDE_BY_SIDE].enScalerOutput3DType = EN_3D_SIDE_BY_SIDE;
    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_SIDE_BY_SIDE].enBackEndInput3DType = EN_3D_SIDE_BY_SIDE;
    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_SIDE_BY_SIDE].enResolution = E_OUTPUT_RESOLUTION_1920X1080;

    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_TOP_BOTTOM].enScalerInput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_TOP_BOTTOM].enScalerOutput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_TOP_BOTTOM].enBackEndInput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_TOP_BOTTOM].enResolution = E_OUTPUT_RESOLUTION_1920X1080;

    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_LINE_ALTERNATIVE].enScalerInput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_LINE_ALTERNATIVE].enScalerOutput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_LINE_ALTERNATIVE].enBackEndInput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_LINE_ALTERNATIVE].enResolution = E_OUTPUT_RESOLUTION_1920X1080;

    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enScalerInput3DType = EN_3D_FRAME_ALTERNATIVE;
    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enScalerOutput3DType = EN_3D_FRAME_ALTERNATIVE;
    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enBackEndInput3DType = EN_3D_FRAME_ALTERNATIVE;
    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enResolution = E_OUTPUT_RESOLUTION_1920X1080;

#if 1//((CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA)||(CHIP_FAMILY_TYPE == CHIP_FAMILY_WHISKY))
    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_2DConvertTo3D].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_2DConvertTo3D].enScalerOutput3DType = EN_3D_BYPASS;    //Maya doesn't support 2Dto3D
    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_2DConvertTo3D].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_2DConvertTo3D].enResolution = E_OUTPUT_RESOLUTION_1920X1080;
#else
    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_2DConvertTo3D].enScalerInput3DType = EN_3D_2DConvertTo3D;
    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_2DConvertTo3D].enScalerOutput3DType = EN_3D_2DConvertTo3D;
    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_2DConvertTo3D].enBackEndInput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_2DConvertTo3D].enResolution = E_OUTPUT_RESOLUTION_1920X1080;
#endif

    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_FRAME_L].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_FRAME_L].enScalerOutput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_FRAME_L].enBackEndInput3DType = EN_3D_BYPASS ;
    st3DBehavior_IN8903_PQ_Optimize.st3DConvertRule[EN_3D_FRAME_L].enResolution = E_OUTPUT_RESOLUTION_3840X2160;



    st3DBehavior_IN8903_PQ_Optimize.st4K2K_Under60Hz_3DConvertRule[EN_3D_BYPASS].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_Under60Hz_3DConvertRule[EN_3D_BYPASS].enScalerOutput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_Under60Hz_3DConvertRule[EN_3D_BYPASS].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_Under60Hz_3DConvertRule[EN_3D_BYPASS].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_PQ_Optimize.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_PACKING].enScalerInput3DType = EN_3D_FRAME_PACKING;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_PACKING].enScalerOutput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_PACKING].enBackEndInput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_PACKING].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_PQ_Optimize.st4K2K_Under60Hz_3DConvertRule[EN_3D_SIDE_BY_SIDE].enScalerInput3DType = EN_3D_SIDE_BY_SIDE;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_Under60Hz_3DConvertRule[EN_3D_SIDE_BY_SIDE].enScalerOutput3DType = EN_3D_FRAME_ALTERNATIVE;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_Under60Hz_3DConvertRule[EN_3D_SIDE_BY_SIDE].enBackEndInput3DType = EN_3D_FRAME_ALTERNATIVE;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_Under60Hz_3DConvertRule[EN_3D_SIDE_BY_SIDE].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_PQ_Optimize.st4K2K_Under60Hz_3DConvertRule[EN_3D_TOP_BOTTOM].enScalerInput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_Under60Hz_3DConvertRule[EN_3D_TOP_BOTTOM].enScalerOutput3DType = EN_3D_FRAME_ALTERNATIVE;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_Under60Hz_3DConvertRule[EN_3D_TOP_BOTTOM].enBackEndInput3DType = EN_3D_FRAME_ALTERNATIVE;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_Under60Hz_3DConvertRule[EN_3D_TOP_BOTTOM].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_PQ_Optimize.st4K2K_Under60Hz_3DConvertRule[EN_3D_LINE_ALTERNATIVE].enScalerInput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_Under60Hz_3DConvertRule[EN_3D_LINE_ALTERNATIVE].enScalerOutput3DType = EN_3D_FRAME_ALTERNATIVE;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_Under60Hz_3DConvertRule[EN_3D_LINE_ALTERNATIVE].enBackEndInput3DType = EN_3D_FRAME_ALTERNATIVE;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_Under60Hz_3DConvertRule[EN_3D_LINE_ALTERNATIVE].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_PQ_Optimize.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enScalerInput3DType = EN_3D_FRAME_ALTERNATIVE;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enScalerOutput3DType = EN_3D_FRAME_ALTERNATIVE;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enBackEndInput3DType = EN_3D_FRAME_ALTERNATIVE;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_PQ_Optimize.st4K2K_Under60Hz_3DConvertRule[EN_3D_2DConvertTo3D].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_Under60Hz_3DConvertRule[EN_3D_2DConvertTo3D].enScalerOutput3DType = EN_3D_BYPASS;    //Maya doesn't support 2Dto3D
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_Under60Hz_3DConvertRule[EN_3D_2DConvertTo3D].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_Under60Hz_3DConvertRule[EN_3D_2DConvertTo3D].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_PQ_Optimize.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_L].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_L].enScalerOutput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_L].enBackEndInput3DType = EN_3D_BYPASS ;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_Under60Hz_3DConvertRule[EN_3D_FRAME_L].enResolution = E_OUTPUT_RESOLUTION_3840X2160;



    st3DBehavior_IN8903_PQ_Optimize.st4K2K_60Hz_3DConvertRule[EN_3D_BYPASS].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_60Hz_3DConvertRule[EN_3D_BYPASS].enScalerOutput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_60Hz_3DConvertRule[EN_3D_BYPASS].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_60Hz_3DConvertRule[EN_3D_BYPASS].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_PQ_Optimize.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_PACKING].enScalerInput3DType = EN_3D_FRAME_PACKING;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_PACKING].enScalerOutput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_PACKING].enBackEndInput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_PACKING].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_PQ_Optimize.st4K2K_60Hz_3DConvertRule[EN_3D_SIDE_BY_SIDE].enScalerInput3DType = EN_3D_SIDE_BY_SIDE;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_60Hz_3DConvertRule[EN_3D_SIDE_BY_SIDE].enScalerOutput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_60Hz_3DConvertRule[EN_3D_SIDE_BY_SIDE].enBackEndInput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_60Hz_3DConvertRule[EN_3D_SIDE_BY_SIDE].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_PQ_Optimize.st4K2K_60Hz_3DConvertRule[EN_3D_TOP_BOTTOM].enScalerInput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_60Hz_3DConvertRule[EN_3D_TOP_BOTTOM].enScalerOutput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_60Hz_3DConvertRule[EN_3D_TOP_BOTTOM].enBackEndInput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_60Hz_3DConvertRule[EN_3D_TOP_BOTTOM].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_PQ_Optimize.st4K2K_60Hz_3DConvertRule[EN_3D_LINE_ALTERNATIVE].enScalerInput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_60Hz_3DConvertRule[EN_3D_LINE_ALTERNATIVE].enScalerOutput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_60Hz_3DConvertRule[EN_3D_LINE_ALTERNATIVE].enBackEndInput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_60Hz_3DConvertRule[EN_3D_LINE_ALTERNATIVE].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_PQ_Optimize.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enScalerInput3DType = EN_3D_FRAME_ALTERNATIVE;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enScalerOutput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enBackEndInput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_ALTERNATIVE].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_PQ_Optimize.st4K2K_60Hz_3DConvertRule[EN_3D_2DConvertTo3D].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_60Hz_3DConvertRule[EN_3D_2DConvertTo3D].enScalerOutput3DType = EN_3D_BYPASS;    //Maya doesn't support 2Dto3D
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_60Hz_3DConvertRule[EN_3D_2DConvertTo3D].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_60Hz_3DConvertRule[EN_3D_2DConvertTo3D].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_PQ_Optimize.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_L].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_L].enScalerOutput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_L].enBackEndInput3DType = EN_3D_BYPASS ;
    st3DBehavior_IN8903_PQ_Optimize.st4K2K_60Hz_3DConvertRule[EN_3D_FRAME_L].enResolution = E_OUTPUT_RESOLUTION_3840X2160;



    st3DBehavior_IN8903_PQ_Optimize.st3DTo2DConvertRule[EN_3D_BYPASS].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_PQ_Optimize.st3DTo2DConvertRule[EN_3D_BYPASS].enScalerOutput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_PQ_Optimize.st3DTo2DConvertRule[EN_3D_BYPASS].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_PQ_Optimize.st3DTo2DConvertRule[EN_3D_BYPASS].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_PQ_Optimize.st3DTo2DConvertRule[EN_3D_FRAME_PACKING].enScalerInput3DType = EN_3D_FRAME_PACKING;
    st3DBehavior_IN8903_PQ_Optimize.st3DTo2DConvertRule[EN_3D_FRAME_PACKING].enScalerOutput3DType = EN_3D_FRAME_L;
    st3DBehavior_IN8903_PQ_Optimize.st3DTo2DConvertRule[EN_3D_FRAME_PACKING].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_PQ_Optimize.st3DTo2DConvertRule[EN_3D_FRAME_PACKING].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_PQ_Optimize.st3DTo2DConvertRule[EN_3D_SIDE_BY_SIDE].enScalerInput3DType = EN_3D_SIDE_BY_SIDE;
    st3DBehavior_IN8903_PQ_Optimize.st3DTo2DConvertRule[EN_3D_SIDE_BY_SIDE].enScalerOutput3DType = EN_3D_FRAME_L;
    st3DBehavior_IN8903_PQ_Optimize.st3DTo2DConvertRule[EN_3D_SIDE_BY_SIDE].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_PQ_Optimize.st3DTo2DConvertRule[EN_3D_SIDE_BY_SIDE].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_PQ_Optimize.st3DTo2DConvertRule[EN_3D_TOP_BOTTOM].enScalerInput3DType = EN_3D_TOP_BOTTOM;
    st3DBehavior_IN8903_PQ_Optimize.st3DTo2DConvertRule[EN_3D_TOP_BOTTOM].enScalerOutput3DType = EN_3D_FRAME_L;
    st3DBehavior_IN8903_PQ_Optimize.st3DTo2DConvertRule[EN_3D_TOP_BOTTOM].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_PQ_Optimize.st3DTo2DConvertRule[EN_3D_TOP_BOTTOM].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_PQ_Optimize.st3DTo2DConvertRule[EN_3D_LINE_ALTERNATIVE].enScalerInput3DType = EN_3D_LINE_ALTERNATIVE;
    st3DBehavior_IN8903_PQ_Optimize.st3DTo2DConvertRule[EN_3D_LINE_ALTERNATIVE].enScalerOutput3DType = EN_3D_FRAME_L;
    st3DBehavior_IN8903_PQ_Optimize.st3DTo2DConvertRule[EN_3D_LINE_ALTERNATIVE].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_PQ_Optimize.st3DTo2DConvertRule[EN_3D_LINE_ALTERNATIVE].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_PQ_Optimize.st3DTo2DConvertRule[EN_3D_FRAME_ALTERNATIVE].enScalerInput3DType = EN_3D_FRAME_ALTERNATIVE;
    st3DBehavior_IN8903_PQ_Optimize.st3DTo2DConvertRule[EN_3D_FRAME_ALTERNATIVE].enScalerOutput3DType = EN_3D_FRAME_L;
    st3DBehavior_IN8903_PQ_Optimize.st3DTo2DConvertRule[EN_3D_FRAME_ALTERNATIVE].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_PQ_Optimize.st3DTo2DConvertRule[EN_3D_FRAME_ALTERNATIVE].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_PQ_Optimize.st3DTo2DConvertRule[EN_3D_2DConvertTo3D].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_PQ_Optimize.st3DTo2DConvertRule[EN_3D_2DConvertTo3D].enScalerOutput3DType = EN_3D_BYPASS;    //Maya doesn't support 2Dto3D
    st3DBehavior_IN8903_PQ_Optimize.st3DTo2DConvertRule[EN_3D_2DConvertTo3D].enBackEndInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_PQ_Optimize.st3DTo2DConvertRule[EN_3D_2DConvertTo3D].enResolution = E_OUTPUT_RESOLUTION_3840X2160;

    st3DBehavior_IN8903_PQ_Optimize.st3DTo2DConvertRule[EN_3D_FRAME_L].enScalerInput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_PQ_Optimize.st3DTo2DConvertRule[EN_3D_FRAME_L].enScalerOutput3DType = EN_3D_BYPASS;
    st3DBehavior_IN8903_PQ_Optimize.st3DTo2DConvertRule[EN_3D_FRAME_L].enBackEndInput3DType = EN_3D_BYPASS ;
    st3DBehavior_IN8903_PQ_Optimize.st3DTo2DConvertRule[EN_3D_FRAME_L].enResolution = E_OUTPUT_RESOLUTION_3840X2160;
}

BOOLEAN _MApp_Scaler_3D_GetBehavior(ST_3D_BEHAVIOR* p3DBhv)
{
    if(p3DBhv == NULL)
        return FALSE;

    DEBUG_3D( printf(" 3D Behavior Select = %d\n", en3DBehaviorSelect); );

    if(en3DBehaviorSelect >= EN_3D_BEHAVIOR_MAX)
        return FALSE;

    memcpy(p3DBhv, ast3DBehaviorTbl[en3DBehaviorSelect], sizeof(ST_3D_BEHAVIOR));

    return TRUE;
}

void _MApp_Scaler_3D_PrintConvertRule(ST_3D_CONVERTRULE* pst3DConv)
{
    if(pst3DConv == NULL)
        return;

    printf("\n\n\r=============================");
    printf("\n\r In=%d(%s), Out=%d(%s), Back=%d(%s), Res=%d(%s)",
        pst3DConv->enScalerInput3DType, MApp_Scaler_Get_Ui3DTypeName(pst3DConv->enScalerInput3DType), \
        pst3DConv->enScalerOutput3DType, MApp_Scaler_Get_Ui3DTypeName(pst3DConv->enScalerOutput3DType), \
        pst3DConv->enBackEndInput3DType, MApp_Scaler_Get_Ui3DTypeName(pst3DConv->enBackEndInput3DType), \
        pst3DConv->enResolution, _MApp_Scaler_3D_GetResolutionTypeString(pst3DConv->enResolution));
    printf("\n\r=============================");
}

#if ENABLE_NEW_3D_FLOW
BOOLEAN MApp_Scaler_3D_GetOutputConfiguration(EN_3D_TYPE eInput3DType, EN_3D_TYPE* penOutput3DType, EN_3D_TYPE* penBackend3DType, EN_4K2K_OUTPUT_RESOLUTION_TYPE* penResType)
{
    ST_3D_BEHAVIOR st3DBehavior;
    //XC_SETWIN_INFO stSetWinInfo;
    U16 u16InputWidth=0, u16InputHeight=0;
    U16 u16InputVfreqX10 = MApi_XC_PCMonitor_Get_VFreqx10( MAIN_WINDOW);
    BOOLEAN b3Dto2DEnable = DB_3D_SETTING.en3DTo2DType;
    BOOLEAN bIsCurrentInputSrcYpbprOrVga;

    DEBUG_3D( printf("MApp_Scaler_3D_GetOutputConfiguration(eInput3DType=%u(%s))\n", eInput3DType, MApp_Scaler_Get_Ui3DTypeName(eInput3DType)); );

    if((penOutput3DType == NULL) || (penOutput3DType == NULL) || (penOutput3DType == NULL))
        return FALSE;

    memset(&st3DBehavior, 0, sizeof(ST_3D_BEHAVIOR));


    DEBUG_3D( printf("b3Dto2DEnable=%u\n", b3Dto2DEnable); );

    //MApp_Scaler_GetWinInfo(&stSetWinInfo);  //Get input signal width/height
    bIsCurrentInputSrcYpbprOrVga = (IsYPbPrInUse() || IsVgaInUse());
    u16InputWidth = MApp_PCMode_Get_HResolution(MAIN_WINDOW, bIsCurrentInputSrcYpbprOrVga);
    u16InputHeight = MApp_PCMode_Get_VResolution(MAIN_WINDOW, bIsCurrentInputSrcYpbprOrVga);

    //Get behavior table
    if(_MApp_Scaler_3D_GetBehavior(&st3DBehavior) == FALSE)
    {
        printf("\n\r Cannot get valid 3D behavior at %s-%d", __FUNCTION__, __LINE__);
        return FALSE;
    }

    //Table look up
    if(b3Dto2DEnable == FALSE)  //3D
    {
        //if((stSetWinInfo.stCapWin.width >= 3840) && (stSetWinInfo.stCapWin.height >= 2160))
        if((u16InputWidth >= 3840) && (u16InputHeight >= 2160))
        {
            if(u16InputVfreqX10 > 400) //48Hz, 50Hz, 60Hz
            {
                DEBUG_3D( printf("Use st4K2K_60Hz_3DConvertRule\n"); );
                *penOutput3DType = st3DBehavior.st4K2K_60Hz_3DConvertRule[eInput3DType].enScalerOutput3DType;
                *penBackend3DType = st3DBehavior.st4K2K_60Hz_3DConvertRule[eInput3DType].enBackEndInput3DType;
                *penResType = st3DBehavior.st4K2K_60Hz_3DConvertRule[eInput3DType].enResolution;
            }
            else    //30Hz, 25Hz, 24Hz
            {
                DEBUG_3D( printf("Use st4K2K_Under60Hz_3DConvertRule\n"); );
                *penOutput3DType = st3DBehavior.st4K2K_Under60Hz_3DConvertRule[eInput3DType].enScalerOutput3DType;
                *penBackend3DType = st3DBehavior.st4K2K_Under60Hz_3DConvertRule[eInput3DType].enBackEndInput3DType;
                *penResType = st3DBehavior.st4K2K_Under60Hz_3DConvertRule[eInput3DType].enResolution;
            }
        }
        else
        {
            DEBUG_3D( printf("Use st3DConvertRule\n"); );
            *penOutput3DType = st3DBehavior.st3DConvertRule[eInput3DType].enScalerOutput3DType;
            *penBackend3DType = st3DBehavior.st3DConvertRule[eInput3DType].enBackEndInput3DType;
            *penResType = st3DBehavior.st3DConvertRule[eInput3DType].enResolution;
        }
    }
    else  //3D to 2D (L only)
    {
        DEBUG_3D( printf("Use st3DTo2DConvertRule\n"); );
        *penOutput3DType = st3DBehavior.st3DTo2DConvertRule[eInput3DType].enScalerOutput3DType;
        *penBackend3DType = st3DBehavior.st3DTo2DConvertRule[eInput3DType].enBackEndInput3DType;
        *penResType = st3DBehavior.st3DTo2DConvertRule[eInput3DType].enResolution;
    }

    MENU_3D_DBG(printf("\n\r Input resolution = %d X %d", u16InputWidth, u16InputHeight););
    MENU_3D_DBG(printf("\n\r OutputType=%d(%s), ", *penOutput3DType, MApp_Scaler_Get_Ui3DTypeName(*penOutput3DType)););
    MENU_3D_DBG(printf("\n\r BackEndInputType=%d(%s), ", *penBackend3DType, MApp_Scaler_Get_Ui3DTypeName(*penBackend3DType)););
    MENU_3D_DBG(printf("\n\r Output resolution=%d(%s). \n", *penResType, _MApp_Scaler_3D_GetResolutionTypeString(*penResType)););

    return TRUE;
}
#endif

void MApp_Scaler_3D_SetPanelTiming_ByResolution(EN_4K2K_OUTPUT_RESOLUTION_TYPE eResType, EN_3D_TYPE eBackEnd3DType)
{
    PANEL_RESOLUTION_TYPE enNewPanelIndex = PNL_RES_MAX_NUM;
    U16 u16PanelWidth = 0;
  #if ENABLE_TCON_IN8903_PROCESS
    EN_IN8903_4K2K_MODE eIn8903_4k2kMode = E_IN8903_4K2K_MODE_4K2K;
    static IN8903_PANEL_3D_FORMAT s_eIn8903_InputFmt = IN8903_PANEL_3D_FORMAT_2D_YUV;
    IN8903_PANEL_3D_FORMAT eNewIn8903_InputFmt = MAPP_Scaler_MapUi3DFormatToIn8903_3DMode(eBackEnd3DType);
  #endif

    // Fix unused warning
    eBackEnd3DType=eBackEnd3DType;

    switch(eResType)
    {
        case E_OUTPUT_RESOLUTION_3840X2160:
            enNewPanelIndex = g_PNL_TypeSel_4K2K;
          #if ENABLE_TCON_IN8903_PROCESS
            eIn8903_4k2kMode = E_IN8903_4K2K_MODE_4K2K;
          #endif
            break;

        case E_OUTPUT_RESOLUTION_1920X1080:
            enNewPanelIndex = g_PNL_TypeSel_FHD;
          #if ENABLE_TCON_IN8903_PROCESS
            eIn8903_4k2kMode = E_IN8903_4K2K_MODE_FULLHD;
          #endif
            break;

        case E_OUTPUT_RESOLUTION_3840X1080:
            enNewPanelIndex = g_PNL_TypeSel_4K1K;
          #if ENABLE_TCON_IN8903_PROCESS
            eIn8903_4k2kMode = E_IN8903_4K2K_MODE_4K1K;
          #endif
            break;

        default:
            enNewPanelIndex = PNL_RES_MAX_NUM;
            break;
    }

    if(enNewPanelIndex >= PNL_RES_MAX_NUM)
    {
        printf("\n\r Resolution type = %d (%s), cannot find valid corresponding panel index @ %s-%d", eResType, _MApp_Scaler_3D_GetResolutionTypeString(eResType), __FUNCTION__, __LINE__);
        return;
    }

    if(enNewPanelIndex != g_PNL_TypeSel)
    {
        printf("!! 3D change Panel type=%u\n", enNewPanelIndex);
        g_PNL_TypeSel = enNewPanelIndex;

      #if SUPPORT_VX1_OUTPUT
        if(devPanel_IsVx1(g_PNL_TypeSel))
        {
            //MApi_PNL_MOD_OutputChannelOrder(APIPNL_OUTPUT_CHANNEL_ORDER_USER, 0x2108, 0x493a, 0xb765, 0xdc);
            if(MApi_XC_GetPanelSpec(g_PNL_TypeSel)->m_bPanelDualPort == 1)// 2BLK
            {
                MApi_PNL_MOD_OutputChannelOrder(APIPNL_OUTPUT_CHANNEL_ORDER_USER, _VX1_LANE_ORDER_2BLK_);
            }
            else //1BLK
            {
                MApi_PNL_MOD_OutputChannelOrder(APIPNL_OUTPUT_CHANNEL_ORDER_USER, _VX1_LANE_ORDER_1BLK_);
            }
            MApi_BD_LVDS_Output_Type(0x04);//4: user mode
            MApi_PNL_MOD_OutputConfig_User(0x4454, 0x0015, 0x00);
            MApi_XC_SetPanelExtType(g_PNL_TypeSel);
            MApi_PNL_ForceSetPanelDCLK(MApi_PNL_Get_PanelTypicalDclk(g_PNL_TypeSel) , TRUE);
        }

      #endif

      #if (CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA)    //only maya utopia extend to 6 entry FRC table.
        SC_FRC_SETTING sFRC_Tbl_Temp[6] =
        {
            {0, 160, 1, 4, MS_FRC_1_4},
            {160, 245, 2, 5, MS_FRC_2_5},
            {245, 260, 1, 2, MS_FRC_1_2},
            {260, 400, 1, 2, MS_FRC_1_2},
            {400, 510, 1, 1, MS_FRC_1_1},
            {510, 0xFFFF, 1, 1, MS_FRC_1_1},
        };

        MApi_XC_CustomizeFRCTable(sFRC_Tbl_Temp);
      #else
        MApi_XC_CustomizeFRCTable(NULL);
      #endif

      #if ENABLE_TCON_IN8903_PROCESS
        s_eIn8903_InputFmt = eNewIn8903_InputFmt;
        MDrv_IN8903_SwitchMode(eIn8903_4k2kMode, s_eIn8903_InputFmt);
      #endif
        msAPI_Scaler_ChangePanelType(g_PNL_TypeSel, MAIN_WINDOW);

        u16PanelWidth = PANEL_WIDTH;

        if(u16PanelWidth <= 1366)
        {
            u16PanelWidth = 1366;
        }
        else if(u16PanelWidth >= 3840)
        {
            u16PanelWidth = 3840;
        }
        else
        {
            u16PanelWidth = 1920;
        }

        MDrv_PQ_Set_DisplayType_Sub(u16PanelWidth, PQ_DISPLAY_ONE, FALSE);
        MDrv_PQ_Set_DisplayType_Main(u16PanelWidth, PQ_DISPLAY_ONE, FALSE);

        MApp_Gop_init();
    }
  #if ENABLE_TCON_IN8903_PROCESS
    else if(eNewIn8903_InputFmt != s_eIn8903_InputFmt)
    {
        s_eIn8903_InputFmt = eNewIn8903_InputFmt;
        MDrv_IN8903_3D_MODE(s_eIn8903_InputFmt);
    }
  #endif

}
#endif

void MApp_PreInitPanelTiming(void)
{
    XC_SetTiming_Info stTimingInfo;

    stTimingInfo.bFastFrameLock = FALSE;
    stTimingInfo.bMVOPSrc       = FALSE;
  #if (TV_SYSTEM == TV_NTSC)
    stTimingInfo.u16InputVFreq  = 600;
    stTimingInfo.u16InputVTotal = 525;;
  #else
    stTimingInfo.u16InputVFreq  = 500;
    stTimingInfo.u16InputVTotal = 625;;
  #endif
    stTimingInfo.bInterlace     = TRUE;

#if(CHAKRA3_AUTO_TEST)
    MApi_SC_ForceFreerun(TRUE);
    MApi_SC_SetFreerunVFreq(VFREQ_60HZ);
#endif

    MApi_XC_SetPanelTiming(&stTimingInfo, MAIN_WINDOW);

#if ENABLE_BACKLIGHT_PWM_SYNC_WITH_FRAMERATE
    SetPWMto2PanelVFreq(RATIO_OF_BACKLIGHT_FREQ_OVER_FRAMERATE);
#endif
}

U8 MApp_Scaler_FactoryAdjBrightness(U8 u8Brightness, U8 u8SubBrightness)
{
    U16 u16TempBrightness;
    u16TempBrightness = (U16)u8Brightness * u8SubBrightness / SUB_BRIGHTNESS_BYPASS;
    u16TempBrightness = MIN(u16TempBrightness, 255);
    return (U8)u16TempBrightness;
}

U8 MApp_Scaler_DesignAdjBrightness(U8 u8Brightness, U8 u8SubBrightness)
{
    U16 u16TempBrightness;
    u16TempBrightness = (U16)u8Brightness * u8SubBrightness / SUB_BRIGHTNESS_BYPASS;
    u16TempBrightness = MIN(u16TempBrightness, 255);
    return (U8)u16TempBrightness;
}

U8 MApp_Scaler_FactoryContrast(U8 u8Contrast, U8 u8SubContrast)
{
    U16 u16TempContrast;
    u16TempContrast = (U16)u8Contrast * u8SubContrast / SUB_CONTRAST_BYPASS;

#if (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)
    u16TempContrast+=50;
#endif

    u16TempContrast = MIN(u16TempContrast, 255);
    return (U8)u16TempContrast;
}

U8 MApp_Scaler_DesignContrast(U8 u8Contrast, U8 u8SubContrast)
{
    U16 u16TempContrast;
    u16TempContrast = (U16)u8Contrast * u8SubContrast / SUB_CONTRAST_BYPASS;

#if (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)
    u16TempContrast+=50;
#endif

    u16TempContrast = MIN(u16TempContrast, 255);
    return (U8)u16TempContrast;
}

void MApp_Scaler_WaitInputStable(INPUT_SOURCE_TYPE_t enInputSourceType, SCALER_WIN eWindow)
{
#define CHECK_VF_TIMEOUT    50
    U8 i;
    U32 u32InputVFreq;
    U32 u32HighAccurateInputVFreq;
    U32 u32VF_Diff;


    if( IsSrcTypeAnalog(enInputSourceType) || IsSrcTypeHDMI(enInputSourceType) )
    {
        for( i = 0; i < CHECK_VF_TIMEOUT; ++ i )
        {
            u32InputVFreq = MApi_XC_PCMonitor_Get_VFreqx10(eWindow) * 100;
            u32HighAccurateInputVFreq = MApi_XC_PCMonitor_Get_VFreqx1K(eWindow);
            u32VF_Diff = abs(u32InputVFreq - u32HighAccurateInputVFreq);

            printf("InVf=%u %u %u at %u\n", u32InputVFreq, u32HighAccurateInputVFreq, u32VF_Diff, MsOS_GetSystemTime());

            if( u32VF_Diff < 100 )
            {
                break;
            }

            msAPI_Timer_Delayms(10);
        }
    }
}

#define DEBUG_SET_TIMING(x) x
void MApp_Scaler_SetTiming(INPUT_SOURCE_TYPE_t enInputSourceType, SCALER_WIN eWindow)
{
    XC_SetTiming_Info stTimingInfo;
    MS_U16 u16InputHFreq;
    MVOP_Timing stMVOPTiming;
    MS_U8 u8Count=0;


    DEBUG_SCALER_FLOW(printf("MApp_Scaler_SetTiming(src=%u,) at %u\n", enInputSourceType, MsOS_GetSystemTime()););

    memset( &stTimingInfo, 0, sizeof(XC_SetTiming_Info) );

    stTimingInfo.bFastFrameLock = FALSE;

    if( IsSrcTypeAnalog(enInputSourceType) || IsSrcTypeHDMI(enInputSourceType))
    {
        // If input V freq is not stable, then FPLL will failed!!!
        MApp_Scaler_WaitInputStable(enInputSourceType, eWindow);

        stTimingInfo.u16InputVTotal = MApi_XC_PCMonitor_Get_Vtotal(eWindow);
        stTimingInfo.bInterlace     = MApi_XC_PCMonitor_GetSyncStatus(eWindow) & XC_MD_INTERLACE_BIT ? TRUE : FALSE;
        stTimingInfo.bMVOPSrc       = 0;
        stTimingInfo.u16InputVFreq  = MApi_XC_PCMonitor_Get_VFreqx10(eWindow);

        DEBUG_SCALER_INPUT_TIMING( printf("stTimingInfo.u16InputVTotal=%u\n", stTimingInfo.u16InputVTotal); );
        DEBUG_SCALER_INPUT_TIMING( printf("stTimingInfo.bInterlace=%u\n", stTimingInfo.bInterlace); );
        DEBUG_SCALER_INPUT_TIMING( printf("stTimingInfo.u16InputVFreq=%u\n", stTimingInfo.u16InputVFreq); );

        while(stTimingInfo.u16InputVFreq==0 && u8Count<3)
        {
            printf("Delay 10\n");
            MsOS_DelayTask(10);
            stTimingInfo.u16InputVFreq = MApi_XC_PCMonitor_Get_VFreqx10(eWindow);
            u8Count++;
        }
        if(stTimingInfo.u16InputVFreq==0)
        {
               return;
        }

        stTimingInfo.u32HighAccurateInputVFreq = MApi_XC_PCMonitor_Get_VFreqx1K(eWindow);
        DEBUG_SCALER_INPUT_TIMING( printf("stTimingInfo.u32HighAccurateInputVFreq=%u\n", stTimingInfo.u32HighAccurateInputVFreq); );

        if(abs(stTimingInfo.u16InputVFreq * 100 - stTimingInfo.u32HighAccurateInputVFreq) >= ACCURATE_VFREQ_TOLERANCE)
        {
            stTimingInfo.u32HighAccurateInputVFreq = (MS_U32)stTimingInfo.u16InputVFreq * 100; //In tolerance range, using new accurate vfreq
            DEBUG_SCALER_INPUT_TIMING( printf("stTimingInfo.u32HighAccurateInputVFreq=%u\n", stTimingInfo.u32HighAccurateInputVFreq); );
        }

    }
    else if( IsSrcTypeATV(enInputSourceType) || IsSrcTypeDigitalVD(enInputSourceType) )
    {
        BOOL bVdInputIs50Hz =  msAPI_AVD_Is_Input50Hz();

        stTimingInfo.bMVOPSrc       = FALSE;
        stTimingInfo.bInterlace     = TRUE;

        if( !IsVDHasSignal() ) // VD no signal
        {
            //printf("VD no signal!");
            u16InputHFreq = 157;
            if( bVdInputIs50Hz )
                stTimingInfo.u16InputVTotal = 625;
            else
                stTimingInfo.u16InputVTotal = 525;
        }
        else
        {
            u16InputHFreq = MApi_XC_CalculateHFreqx10(msAPI_Scaler_VD_GetHPeriod(eWindow, enInputSourceType, GET_SYNC_VIRTUAL));
            //stTimingInfo.u16InputVTotal = msAPI_Scaler_VD_GetVTotal(eWindow, enInputSourceType, GET_SYNC_VIRTUAL, u16InputHFreq);
            stTimingInfo.u16InputVTotal = MDrv_AVD_GetVTotal();
        }

        DEBUG_SCALER_INPUT_TIMING(printf("stTimingInfo.u16InputVTotal=%u\n", stTimingInfo.u16InputVTotal););
        if( stTimingInfo.u16InputVTotal == 0 )
        {
            if( bVdInputIs50Hz )
                stTimingInfo.u16InputVTotal = 625;
            else
                stTimingInfo.u16InputVTotal = 525;
        }

        stTimingInfo.u16InputVFreq  = MApi_XC_CalculateVFreqx10(u16InputHFreq, stTimingInfo.u16InputVTotal)*2;
        DEBUG_SCALER_INPUT_TIMING(printf(" .u16InputVFreq=%u\n", stTimingInfo.u16InputVFreq););

        if( bVdInputIs50Hz ) // VD 50Hz
        {
            DEBUG_SCALER_INPUT_TIMING(printf("Vd 50~\n"););
            if( (stTimingInfo.u16InputVFreq > 510) || (stTimingInfo.u16InputVFreq < 490) )
            {
                printf("\nWarning: VD is 50Hz, u16InputVFreq=%u is abnormal!\n", stTimingInfo.u16InputVFreq);
                stTimingInfo.u16InputVFreq = 500;
            }
        }
        else
        {
            DEBUG_SCALER_INPUT_TIMING(printf("Vd 60~\n"););
            if( (stTimingInfo.u16InputVFreq > 610) || (stTimingInfo.u16InputVFreq < 590) )
            {
                printf("\nWarning: VD is 60Hz, u16InputVFreq=%u is abnormal!\n", stTimingInfo.u16InputVFreq);
                stTimingInfo.u16InputVFreq = 600;
            }
        }

        stTimingInfo.u32HighAccurateInputVFreq = (MS_U32)stTimingInfo.u16InputVFreq * 100;

    }
    else
    {
        MDrv_MVOP_GetOutputTiming(&stMVOPTiming);

        stTimingInfo.u16InputVTotal = stMVOPTiming.u16V_TotalCount;
        stTimingInfo.bInterlace     = stMVOPTiming.bInterlace;
        if(stTimingInfo.bInterlace)
        {
            stTimingInfo.u16InputVFreq = (U16)((stMVOPTiming.u16ExpFrameRate * 2 + 50) / 100);
            stTimingInfo.u32HighAccurateInputVFreq = (U32)(stMVOPTiming.u16ExpFrameRate * 2);
        }
        else
        {
            stTimingInfo.u16InputVFreq = (U16)((stMVOPTiming.u16ExpFrameRate + 50) / 100);
            stTimingInfo.u32HighAccurateInputVFreq = (U32)(stMVOPTiming.u16ExpFrameRate);
        }

        stTimingInfo.bMVOPSrc = TRUE;

      #if 0 // Check and wait MVOP --> Scaler timing stable
        {
            XC_IP_SYNC_STATUS stXC_IP_SYNC_STATUS;

            MApi_XC_GetSyncStatus(enInputSourceType, &stXC_IP_SYNC_STATUS, eWindow);

            BOOL bInterlace = (stXC_IP_SYNC_STATUS.u8SyncStatus& XC_MD_INTERLACE_BIT) ? TRUE : FALSE;

            DEBUG_SCALER_INPUT_TIMING( printf("bInterlace=%u\n", bInterlace); );
            //DEBUG_SCALER_INPUT_TIMING( printf("u16Hperiod=%u\n", stXC_IP_SYNC_STATUS.u16Hperiod); );
            DEBUG_SCALER_INPUT_TIMING( printf("u16Vtotal=%u\n", stXC_IP_SYNC_STATUS.u16Vtotal); );


            if( (stXC_IP_SYNC_STATUS.u16Vtotal != stMVOPTiming.u16V_TotalCount)
              ||(bInterlace != stMVOPTiming.bInterlace)
              )
            {
                printf("Wait Timing stable at %u\n", MsOS_GetSystemTime() );
                U32 u32Wait_StartTime = MsOS_GetSystemTime();
                while(1)
                {
                    MApi_XC_GetSyncStatus(enInputSourceType, &stXC_IP_SYNC_STATUS, eWindow);
                    bInterlace = (stXC_IP_SYNC_STATUS.u8SyncStatus& XC_MD_INTERLACE_BIT) ? TRUE : FALSE;

                    printf("[%u %u at %u]", bInterlace, stXC_IP_SYNC_STATUS.u16Vtotal, MsOS_GetSystemTime());

                    if( (stXC_IP_SYNC_STATUS.u16Vtotal == stMVOPTiming.u16V_TotalCount)
                      &&(bInterlace == stMVOPTiming.bInterlace)
                      )
                    {
                        break;
                    }

                    if( msAPI_Timer_DiffTime_2(u32Wait_StartTime, MsOS_GetSystemTime()) > 500 )
                    {
                        printf("Wait MVOP timing stable timeout!\n");
                        break;
                    }

                }
                printf("Wait Timing stable end at %u\n", MsOS_GetSystemTime() );
            }
        }
      #endif
    }

    LOG_CHANGE_CHANNEL_TIME("PnlTiming-4");

#if(CHAKRA3_AUTO_TEST)
    MApi_SC_ForceFreerun(TRUE);
    MApi_SC_SetFreerunVFreq(VFREQ_60HZ);
#endif


    DEBUG_SCALER_INPUT_TIMING( printf(" is FBL=%u\n", MApi_XC_IsCurrentFrameBufferLessMode()); );
    DEBUG_SCALER_INPUT_TIMING( printf(" is RFBL=%u\n", MApi_XC_IsCurrentRequest_FrameBufferLessMode()); );
    DEBUG_SCALER_INPUT_TIMING( printf(" FPLL_Thresh_Mode=%u\n", MApi_XC_Get_FPLL_Thresh_Mode()); );

    DEBUG_SCALER_INPUT_TIMING( printf("stTimingInfo:\n"); );
    DEBUG_SCALER_INPUT_TIMING( printf(" .bInterlace=%u\n", stTimingInfo.bInterlace); );
    DEBUG_SCALER_INPUT_TIMING( printf(" .u16InputVTotal=%u\n", stTimingInfo.u16InputVTotal); );
    DEBUG_SCALER_INPUT_TIMING( printf(" .u16InputVFreq=%u\n", stTimingInfo.u16InputVFreq); );
    DEBUG_SCALER_INPUT_TIMING( printf(" .u32HighAccurateInputVFreq=%u\n", stTimingInfo.u32HighAccurateInputVFreq); );
    //DEBUG_SCALER_INPUT_TIMING( printf(" .bMVOPSrc=%u\n", stTimingInfo.bMVOPSrc); );
    //DEBUG_SCALER_INPUT_TIMING( printf(" .bFastFrameLock=%u\n", stTimingInfo.bFastFrameLock); );


//    MApi_XC_SetDbgLevel(XC_DBGLEVEL_SETTIMING|XC_DBGLEVEL_SETTIMING_ISR);
    //MApi_XC_SetDbgLevel(XC_DBGLEVEL_SETTIMING);

    MApi_XC_SetPanelTiming(&stTimingInfo, eWindow);

    LOG_CHANGE_CHANNEL_TIME("PnlTiming-5");

#if ENABLE_BACKLIGHT_PWM_SYNC_WITH_FRAMERATE
    SetPWMto2PanelVFreq(RATIO_OF_BACKLIGHT_FREQ_OVER_FRAMERATE);
#endif

#if(LD_ENABLE)
    MApi_LD_Set_OutputVFreq( MApi_XC_GetOutputVFreqX100() );
#endif
}

//*************************************************************************
//Function name:    MApp_Scaler_Setting_SetVDScale
//Passing parameter:    none
//Return parameter:     none
//Description:      Set video scale
//*************************************************************************
void MApp_Scaler_Setting_SetVDScale (EN_MENU_AspectRatio eAspect, SCALER_WIN eWindow)
{
    EN_ASPECT_RATIO_TYPE enVideoScreen;

    //static EN_MENU_AspectRatio ePreARC = EN_AspectRatio_Num;

    DEBUG_SET_WIN( printf("MApp_Scaler_Setting_SetVDScale(eAspect=%u)\n", eAspect); );

/* Skip may cause some problem
    if( eAspect == ePreARC)
    {
        MSG(printf("AspectRatio pass \r\n"));
        return;
    }
    else
    {
        ePreARC = eAspect;
    }
    */

    switch(eWindow)
    {
    case MAIN_WINDOW:
        if( //(!(stSystemInfo[MAIN_WINDOW].u8PanelPowerStatus & PANEL_POWER_BLUESCREEN)) // Blue screen is Off
            ( FALSE == MApi_XC_Sys_Get_BlueScreenStatus(MAIN_WINDOW) ) // Blue screen is Off
          #if (MHEG5_ENABLE)
            || msAPI_MHEG5_IsRunning()
          #endif
            )
        {
            enVideoScreen = MApp_Scaler_GetAspectRatio(MAIN_WINDOW,eAspect);
            stSystemInfo[MAIN_WINDOW].enAspectRatio = enVideoScreen;

            if(MApp_IsSrcHasSignal(MAIN_WINDOW)
                #if (MHEG5_ENABLE)
                || msAPI_MHEG5_IsRunning()
                #endif
                )
            {
            #if (CHANGE_AR_WITHOUT_BLUESCREEN == DISABLE)
              #if FIXED_SCART_OUT_GARBAGE_SWITCH_AR
                #if(ENABLE_VE)
                MDrv_VE_SetBlackScreen(ENABLE);
                #endif
                g_u8switchAspectFlag = 1;
              #endif
                msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
            #endif

            #if (MHEG5_ENABLE)
                if(msAPI_MHEG5_IsRunning())
                {
                    if  (msAPI_Picture_isAFDEnable(stSystemInfo[MAIN_WINDOW].enAspectRatio) &&
                        msAPI_Picture_isCurrentAFDVaild(MApi_VDEC_GetActiveFormat()))
                    {
                        MApp_MHEG5_SetGraphARCInfo(SENDARC_AFD_FOR_GE,stSystemInfo[MAIN_WINDOW].enAspectRatio);
                        MApp_MHEG5_SetGraphARCInfo(SENDARC_AFD,stSystemInfo[MAIN_WINDOW].enAspectRatio);
                        msAPI_MHEG5_VID_SendUserArcEvent();
                    }
                    else
                    {
                        MApp_MHEG5_SetGraphARCInfo(SENDARC_ARC_CHANGE,stSystemInfo[MAIN_WINDOW].enAspectRatio);
                    }
                }
            #endif

                MS_DEBUG_MSG(printf("[%s]: SetT&W------------------------------\n", __FUNCTION__));
              #if ENABLE_FBL_ASPECT_RATIO_BY_MVOP
                if(MApi_XC_IsCurrentFrameBufferLessMode() && (IsSrcTypeStorage(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) || IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))))
                {
                    MApp_Scaler_SetFBLTimingForAspectRatio(enVideoScreen);
                }
                else
              #endif
                {
                    MApp_Scaler_SetWindow(NULL, NULL, NULL,
                                           enVideoScreen, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);

                    MApp_Picture_Setting_SetColor(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);

                #if (CHANGE_AR_WITHOUT_BLUESCREEN == DISABLE)
                    MApp_Scaler_SetTiming(SYS_INPUT_SOURCE_TYPE(eWindow), eWindow);

                    MApi_XC_WaitInputVSync(4, 200, MAIN_WINDOW);


                    msAPI_Scaler_SetBlueScreen(DISABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
                    #if FIXED_SCART_OUT_GARBAGE_SWITCH_AR
                    g_u8switchAspectFlag = 0;
                    msAPI_Timer_Delayms(200);
                    #if(ENABLE_VE)
                    MDrv_VE_SetBlackScreen(DISABLE);
                    #endif
                    #endif
                #endif
                }
            }
        }
        break;

#if (ENABLE_PIP)
    case SUB_WINDOW:
        if(IsPIPSupported())
        {
            //if( !(stSystemInfo[SUB_WINDOW].u8PanelPowerStatus & PANEL_POWER_BLUESCREEN) ) // Blue screen is Off
            if( FALSE == MApi_XC_Sys_Get_BlueScreenStatus(SUB_WINDOW) ) // Blue screen is Off
            {
                enVideoScreen = MApp_Scaler_GetAspectRatio(SUB_WINDOW,eAspect);
                stSystemInfo[SUB_WINDOW].enAspectRatio = enVideoScreen;

                if(MApp_IsSrcHasSignal(SUB_WINDOW))
                {
                    msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, SUB_WINDOW);
                    printf("[%s]: Set sub window T&W------------------------------\n", __FUNCTION__);
                    printf("sub window position x:%u y:%u width:%u hight:%u",stSubWindowPosition.x,stSubWindowPosition.y,stSubWindowPosition.width,stSubWindowPosition.height);
                    MApp_Scaler_SetWindow(NULL, NULL, &stSubWindowPosition,
                                               enVideoScreen, SYS_INPUT_SOURCE_TYPE(SUB_WINDOW), SUB_WINDOW);
                    MApp_Picture_Setting_SetColor(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW), SUB_WINDOW);
                    MApp_Scaler_SetTiming(SYS_INPUT_SOURCE_TYPE(eWindow), eWindow);
                    msAPI_Scaler_SetBlueScreen(DISABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, SUB_WINDOW);
                }
            }
        }
        break;
#endif

    default:
        MS_DEBUG_MSG(printf("invalid window number!\n"));
        break;
    }
}

static void _MApp_Scaler_CheckHDMode(SCALER_WIN eWindow)
{
    U16 u16H_CapSize=0, u16V_CapSize=0;

    if( IsSrcTypeDigitalVD(SYS_INPUT_SOURCE_TYPE(eWindow)) )
    {
        MApi_XC_Sys_SetSrcIsHD( FALSE, eWindow );
    }
    else
    {

        #if (INPUT_HDMI_VIDEO_COUNT > 0)
        if(IsSrcTypeHDMI(SYS_INPUT_SOURCE_TYPE(eWindow)))
        {
            u16H_CapSize = MApp_PCMode_Get_HResolution(eWindow,FALSE);
            u16V_CapSize = MApp_PCMode_Get_VResolution(eWindow,FALSE);
        }
        else
        #endif
        if(IsSrcTypeVga(SYS_INPUT_SOURCE_TYPE(eWindow)) || IsSrcTypeYPbPr(SYS_INPUT_SOURCE_TYPE(eWindow)))
        {
            u16H_CapSize = MApp_PCMode_Get_HResolution( eWindow, TRUE); // standard display width
            u16V_CapSize = MApp_PCMode_Get_VResolution( eWindow, TRUE); // standard display height
        }
        else if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(eWindow)) )
        {
            u16H_CapSize = MDrv_MVOP_GetHSize();
            u16V_CapSize = MDrv_MVOP_GetVSize();
        }

        // Setup HD flag
        //Fixed 800*600,1024*768 Lv and x y error,
        //Modify "RGB To YUV CSC Set HD matrix,but frontend YUV To RGB CSC Set SD matrix" error
        if(u16H_CapSize <= 720 && u16V_CapSize <= 576)
        {
            MApi_XC_Sys_SetSrcIsHD( FALSE, eWindow );

        }
        else
        {
            MApi_XC_Sys_SetSrcIsHD( TRUE, eWindow );

        }
    }
}

#define MUTE_TIME_FOR_HDMI_AR_CHANGE    800

void MApp_Scaler_Setting_HDMI_PAR(void)
{
    DEBUG_SCALER_FLOW( printf("MApp_Scaler_Setting_HDMI_PAR() at %u\n", MsOS_GetSystemTime()); );

    //PRINT_CURRENT_LINE();
    //printf("Black=%u\n", MApi_XC_IsBlackVideoEnable(MAIN_WINDOW) );

    // When player send a AR change, TV should mute for a while.
    // Mute is not only for TV, also for player!! (Player also gen garbage!!)
    //msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, ENABLE, MUTE_TIME_FOR_HDMI_AR_CHANGE, MAIN_WINDOW);


    if( ST_VIDEO.eAspectRatio == EN_AspectRatio_Original )
    {
        EN_ASPECT_RATIO_TYPE enVideoScreen;

        enVideoScreen = MApp_Scaler_GetAspectRatio(MAIN_WINDOW,ST_VIDEO.eAspectRatio);

        if( enVideoScreen != stSystemInfo[MAIN_WINDOW].enAspectRatio )
        {
            printf("MApp_Scaler_SetWindow() by HDMI AR changed\n");

            stSystemInfo[MAIN_WINDOW].enAspectRatio = enVideoScreen;

            MApp_Scaler_SetWindow(NULL, NULL, NULL,
                                       enVideoScreen, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
            MApp_Picture_Setting_SetColor(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),MAIN_WINDOW);
            MApp_Scaler_SetTiming(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
        }
    }
}

/******************************************************************************/
///Setup input and output window information including aspect ratio, scaling.(analog part)
///@param enPortType \b IN
///- input Port (RGB or YPbPr) only could be use
///@param pstModesetting \b IN
///- pointer to mode settings
///@param u8CurrentSyncStatus \b IN
///- current mode index
///@return
///- pointer to current window information
/******************************************************************************/
#if 1//(ENABLE_SET_WIN_CHECK_DE)
BOOLEAN MApp_Scaler_Get_StableDE(SCALER_WIN eWindow, INPUT_SOURCE_TYPE_t enInputSourceType, MS_WINDOW_TYPE *pstDEWin )
{
#if( HDMI_STABLE_WIN_USE_MODE_INFO )

    return MApp_PCMode_Get_CurModeInfo(eWindow, enInputSourceType, pstDEWin);

#else
    //MApi_XC_GetDEWindow(&(pstXC_SetWin_Info->stCapWin), eWindow);
    U8 i;

    for( i = 0; i < 10; ++ i )
    {
        if( MApi_XC_HDMI_CheckTimingStable(eWindow, enInputSourceType, pstDEWin ) )
        {
          #if 0 // Test force fail
            printf("pstDEWin->y=%u\n", pstDEWin->y);
            if( pstDEWin->height== 576 )
            {
                pstDEWin->height = 30;
                return 0;
            }
          #endif

            return TRUE;
        }

        msAPI_Timer_Delayms(2);
    }

    printf("\nError: Get stable DE failed!\n");

    return FALSE;
#endif
}
#endif

static void _MApp_Scaler_ProgAnalogWin ( INPUT_SOURCE_TYPE_t enInputSourceType,
                                         MS_PCADC_MODESETTING_TYPE *pstModesetting,
                                         U8 u8AspectRatio,
                                         U8 u8CurrentSyncStatus,
                                         XC_SETWIN_INFO *pstXC_SetWin_Info,
                                         SCALER_WIN eWindow)
{
    U8 u8Resolution;
    PQ_WIN enPQWin;
    pstXC_SetWin_Info->bHDuplicate    = FALSE;
    pstXC_SetWin_Info->u16InputVTotal = MApi_XC_PCMonitor_Get_Vtotal(eWindow);

    if(IsSrcTypeYPbPr(enInputSourceType) && (g_PcadcModeSetting[eWindow].u8ModeIndex == MD_720x480_60I_P))
    {
        // this is patch for DVD 480i -> Sherwood -> component output -> OSD unsupport mode
        pstXC_SetWin_Info->bInterlace = TRUE;
    }
    else
    {
        pstXC_SetWin_Info->bInterlace = u8CurrentSyncStatus & XC_MD_INTERLACE_BIT ? TRUE : FALSE;
    }

    pstXC_SetWin_Info->u16InputVFreq  = MApi_XC_PCMonitor_Get_VFreqx10(eWindow);

    DEBUG_CAP_WIN(printf(" AnaWin-1 stCapWin: w,h,x,y=%u,%u,%u,%u\n",
        pstXC_SetWin_Info->stCapWin.width, pstXC_SetWin_Info->stCapWin.height,
        pstXC_SetWin_Info->stCapWin.x, pstXC_SetWin_Info->stCapWin.y););


#if (INPUT_HDMI_VIDEO_COUNT > 0)
    if( IsSrcTypeHDMI(enInputSourceType) )
    {
        // DVI or HDMI

        //if (MApi_XC_GetHdmiSyncMode() == HDMI_SYNC_DE)
        {
        #if 1 //(ENABLE_SET_WIN_CHECK_DE)
            if( FALSE == MApp_Scaler_Get_StableDE( eWindow, enInputSourceType, &(pstXC_SetWin_Info->stCapWin) ) )
            {
            #if(ENABLE_CHECK_SET_WIN_RESULT)
                g_Scaler_bSetWidnowResult = FALSE;
            #endif

                // Force timing change...
                //MApi_XC_PCMonitor_Restart(eWindow);
                MApp_PCMode_Reset_TimingMonitor(eWindow);

                return;
            }
        #else
            MApi_XC_GetDEWindow(&(pstXC_SetWin_Info->stCapWin), eWindow);
        #endif

            DEBUG_CAP_WIN(printf(" AnaWin-2 stCapWin: w,h,x,y=%u,%u,%u,%u\n",
                pstXC_SetWin_Info->stCapWin.width, pstXC_SetWin_Info->stCapWin.height,
                pstXC_SetWin_Info->stCapWin.x, pstXC_SetWin_Info->stCapWin.y););

            u8Resolution = _MApp_Scaler_Resolution_Remapping(pstXC_SetWin_Info, eWindow);

            if( u8Resolution >= E_HDMI_MAX )
            {
                u8Resolution=0;
            }
        #if (ENABLE_PIP)
            if (u8Resolution == E_HDMI_MAX)
            {
                pstXC_SetWin_Info->stCapWin.x = pstXC_SetWin_Info->stCapWin.y = 8;
                pstXC_SetWin_Info->stCapWin.width = MApp_PCMode_Get_HResolution( eWindow ,FALSE); // standard display width
                pstXC_SetWin_Info->stCapWin.height = MApp_PCMode_Get_VResolution( eWindow ,FALSE); // standard display height
            }
        #endif

            if( (g_HdmiPollingStatus.bIsHDMIMode == FALSE))     // DVI mode
            {
                // Use DE information
            }
            else if (_bEnHDMI_RefineHVStart)
            {                                                   // HDMI mode
                pstXC_SetWin_Info->stCapWin.x = HDMI_WinInfo[u8Resolution][u8AspectRatio].u16H_CapStart;
                pstXC_SetWin_Info->stCapWin.y = HDMI_WinInfo[u8Resolution][u8AspectRatio].u16V_CapStart;
            }

            DEBUG_CAP_WIN(printf(" AnaWin-2-2 stCapWin: w,h,x,y=%u,%u,%u,%u\n",
                pstXC_SetWin_Info->stCapWin.width, pstXC_SetWin_Info->stCapWin.height,
                pstXC_SetWin_Info->stCapWin.x, pstXC_SetWin_Info->stCapWin.y););

        }
        /*else
        {
            // The capture window is uncontrollable in HDMI HV DE-Bypass mode. So Capture start will assigned by driver itself.
            // Here we just assign a value to capture start
            pstXC_SetWin_Info->stCapWin.x = pstXC_SetWin_Info->stCapWin.y = 8;
            pstXC_SetWin_Info->stCapWin.width = MApp_PCMode_Get_HResolution( eWindow ,FALSE); // standard display width
            pstXC_SetWin_Info->stCapWin.height = MApp_PCMode_Get_VResolution( eWindow ,FALSE); // standard display height
        }
        */

    /*
        DEBUG_CAP_WIN(printf(" AnaWin-3 stCapWin: w,h,x,y=%u,%u,%u,%u\n",
            pstXC_SetWin_Info->stCapWin.width, pstXC_SetWin_Info->stCapWin.height,
            pstXC_SetWin_Info->stCapWin.x, pstXC_SetWin_Info->stCapWin.y););
            */
    }
    else
#endif
    {
        MS_PQ_Mode_Info stModeInfo;
        PQ_WIN ePQWin = _MApp_Scaler_SCALER_WIN_to_PQ_WIN(eWindow);
        MS_PQ_ADC_SAMPLING_TYPE eADC_Sampling_type;

        // VGA or YPbPr
        pstXC_SetWin_Info->stCapWin.x      = pstModesetting->u16DefaultHStart* 2 -pstModesetting->u16HorizontalStart;
        pstXC_SetWin_Info->stCapWin.y      = pstModesetting->u16VerticalStart;

        pstXC_SetWin_Info->stCapWin.width  = MApp_PCMode_Get_HResolution( eWindow ,TRUE); // standard display width
        pstXC_SetWin_Info->stCapWin.height = MApp_PCMode_Get_VResolution( eWindow ,TRUE); // standard display height

        u8Resolution = _MApp_Scaler_Resolution_Remapping(pstXC_SetWin_Info, eWindow);

        if(IsSrcTypeYPbPr(enInputSourceType))  // Coverity 90816 // For Fix coverity #208459 - Overrunning array.
        {
            if( u8Resolution >= E_YPbPr_MAX )
            {
                u8Resolution=0;
            }
        }
        else
        {
            u8Resolution=0;

        }

        stModeInfo.bFBL = FALSE;
        stModeInfo.bInterlace = pstXC_SetWin_Info->bInterlace;
        stModeInfo.u16input_hsize = pstXC_SetWin_Info->stCapWin.width;
        stModeInfo.u16input_vsize = pstXC_SetWin_Info->stCapWin.height;
        stModeInfo.u16input_vfreq = pstXC_SetWin_Info->u16InputVFreq;
        eADC_Sampling_type = MDrv_PQ_Get_ADCSampling_Info(ePQWin, IsSrcTypeYPbPr(enInputSourceType) ? PQ_INPUT_SOURCE_YPBPR : PQ_INPUT_SOURCE_VGA, &stModeInfo);


        MS_U16 u16ratio;

        switch(eADC_Sampling_type)
        {
        default:
            u16ratio = 1;
            pstXC_SetWin_Info->bHDuplicate = FALSE;
            MS_ASSERT(0);
            break;

        case E_PQ_ADC_SAMPLING_NOT_SUPPORT:
            u16ratio = 1;
            if(IsSrcTypeYPbPr(enInputSourceType))
            {
                if(g_PcadcModeSetting[eWindow].u8ModeIndex == MD_720x480_60I ||
                   g_PcadcModeSetting[eWindow].u8ModeIndex == MD_720x480_60P ||
                   g_PcadcModeSetting[eWindow].u8ModeIndex == MD_720x576_50I ||
                   g_PcadcModeSetting[eWindow].u8ModeIndex == MD_720x576_50P ||
                   g_PcadcModeSetting[eWindow].u8ModeIndex == MD_720x480_60I_P)
                {
                    pstXC_SetWin_Info->stCapWin.x <<= 1; // for better quality
                    pstXC_SetWin_Info->stCapWin.width <<= 1;
                    pstXC_SetWin_Info->bHDuplicate = TRUE;
                }

                pstXC_SetWin_Info->stCapWin.x = YPbPr_WinInfo[u8Resolution][u8AspectRatio].u16H_CapStart;
                pstXC_SetWin_Info->stCapWin.y = YPbPr_WinInfo[u8Resolution][u8AspectRatio].u16V_CapStart;
            }
            break;

        case E_PQ_ADC_SAMPLING_NONE:
            u16ratio = 1;
            pstXC_SetWin_Info->bHDuplicate = FALSE;
            break;

        case E_PQ_ADC_SAMPLING_X_1:
            u16ratio = 1;
            pstXC_SetWin_Info->bHDuplicate = FALSE;
            break;
        case E_PQ_ADC_SAMPLING_X_2:
            u16ratio = 2;
            pstXC_SetWin_Info->bHDuplicate = TRUE;
            break;

        case E_PQ_ADC_SAMPLING_X_4:
            u16ratio = 4;
            pstXC_SetWin_Info->bHDuplicate = TRUE;
            break;

        case E_PQ_ADC_SAMPLING_X_8:
            u16ratio = 8;
            pstXC_SetWin_Info->bHDuplicate = TRUE;
            break;
        }

        printf("~~~~~~~~~~~~~~~~~~#########~~~~~~~~~~~~~~  ADC Sampling %d %d \n", u16ratio, pstXC_SetWin_Info->stCapWin.width);
        pstXC_SetWin_Info->stCapWin.x *= u16ratio;
        pstXC_SetWin_Info->stCapWin.width *= u16ratio;

        if(IsSrcTypeYPbPr(enInputSourceType)&& (u16ratio>=2))
        {
            pstXC_SetWin_Info->stCapWin.x = YPbPr_WinInfo[u8Resolution][u8AspectRatio].u16H_CapStart * u16ratio / 2;
            pstXC_SetWin_Info->stCapWin.y = YPbPr_WinInfo[u8Resolution][u8AspectRatio].u16V_CapStart;
        }
        else if(IsSrcTypeYPbPr(enInputSourceType)&& (u16ratio == 1))
        {
            pstXC_SetWin_Info->stCapWin.x = YPbPr_WinInfo[u8Resolution][u8AspectRatio].u16H_CapStart;
            pstXC_SetWin_Info->stCapWin.y = YPbPr_WinInfo[u8Resolution][u8AspectRatio].u16V_CapStart;
        }
        // these 2 settings only for VGA/YPbPr
        // must be mode table user data because everytime called set window such as change Aspect Ratio
        // these values will be set again to ADC
        // UI can change VGA Htotal and Phase, so must pass UI setting
        pstXC_SetWin_Info->u16DefaultHtotal = g_PcadcModeSetting[eWindow].u16HorizontalTotal;

        //TODO: Check end of SetWindow
        pstXC_SetWin_Info->u8DefaultPhase   = g_PcadcModeSetting[eWindow].u16Phase;
    }

    _u8H_OverScanRatio = OVERSCAN_DEFAULT_H;
    _u8V_OverScanRatio = OVERSCAN_DEFAULT_V;

    enPQWin = _MApp_Scaler_SCALER_WIN_to_PQ_WIN(eWindow);

    if(IsSrcTypeHDMI(enInputSourceType))
    {
        MS_PQ_Hdmi_Info stPQHDMI_Info;

        memset(&(stPQHDMI_Info), 0, sizeof(MS_PQ_Hdmi_Info) );

        stPQHDMI_Info.bIsHDMI = g_HdmiPollingStatus.bIsHDMIMode;
        switch(g_HdmiPollingStatus.u8ColorFormat)
        {
        default:
        case MS_HDMI_COLOR_RGB:
            stPQHDMI_Info.enColorFmt = PQ_HDMI_COLOR_RGB;
            break;

    #if(SUPPORT_HDMI_COLOR_YUV_420)
        case MS_HDMI_COLOR_YUV_420:
          #if 1
            stPQHDMI_Info.enColorFmt = PQ_HDMI_COLOR_YUV_422;
            printf("\nWarning: MS_HDMI_COLOR_YUV_420 => PQ_HDMI_COLOR_YUV_422\n");
          #else
            stPQHDMI_Info.enColorFmt = PQ_HDMI_COLOR_YUV_420;
          #endif
            break;
    #endif

        case MS_HDMI_COLOR_YUV_422:
            stPQHDMI_Info.enColorFmt = PQ_HDMI_COLOR_YUV_422;
            break;

        case MS_HDMI_COLOR_YUV_444:
            stPQHDMI_Info.enColorFmt = PQ_HDMI_COLOR_YUV_444;
            break;
        }

        MDrv_PQ_SetHDMIInfo(enPQWin, &stPQHDMI_Info);
    }
}

PQ_WIN _MApp_Scaler_SCALER_WIN_to_PQ_WIN(SCALER_WIN eWindow)
{
    PQ_WIN enPQWin;

    switch(eWindow)
    {
    default:
    case MAIN_WINDOW:
        enPQWin = PQ_MAIN_WINDOW;
        break;
    case SUB_WINDOW:
        enPQWin = PQ_SUB_WINDOW;
        break;
    }

    return enPQWin;
}

static void _MApp_Scaler_ProgDigitalWin (INPUT_SOURCE_TYPE_t enInputSourceType, EN_VD_SIGNALTYPE enVideoSystem,
                                            U8 u8AspectRatio, XC_SETWIN_INFO *pstXC_SetWin_Info, SCALER_WIN eWindow)
{
    U16 u16InputHFreq;
    PQ_WIN enPQWin;
    MS_PQ_Vd_Info stPQVDInfo;
    EN_VD_SIGNALTYPE enVideoSystem_ForCaptureWindow;
    PQ_VIDEOSTANDARD_TYPE enPQ_VdStd_ForCapWin;
    AVD_VideoStandardType enCurVDStd;

#if(PQ_ENABLE_VD_SAMPLING)
    MS_PQ_VD_Sampling_Info stVDSamplingInfo;
#endif
    BOOL bVdInputIs50Hz =  msAPI_AVD_Is_Input50Hz();


    DEBUG_CAP_WIN(printf("_MApp_Scaler_ProgDigitalWin(enVideoSystem=%u)\n", enVideoSystem););
    UNUSED(enVideoSystem);

    enCurVDStd = msAPI_AVD_GetVideoStandard();

    DEBUG_CAP_WIN(printf(" enCurVDStd=%u\n", enCurVDStd););

    // Setup PQ env...
    enPQWin = _MApp_Scaler_SCALER_WIN_to_PQ_WIN(eWindow);

    switch( msAPI_AVD_GetScart1SrcType() )
    {
    case E_SCART_SRC_TYPE_RGB:
        stPQVDInfo.bIsSCART_RGB = TRUE;
        break;
    case E_SCART_SRC_TYPE_CVBS:
    default:
        stPQVDInfo.bIsSCART_RGB = FALSE;
        break;
    }

#if (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)
    stPQVDInfo.bIsVIFIN = TRUE;
#else
    stPQVDInfo.bIsVIFIN = FALSE;
#endif

    switch( enCurVDStd )
    {
    case E_VIDEOSTANDARD_NTSC_M:
        stPQVDInfo.enVideoStandard = E_PQ_VIDEOSTANDARD_NTSC_M;
        enVideoSystem_ForCaptureWindow = SIG_NTSC;
        break;

    case E_VIDEOSTANDARD_PAL_BGHI:
        stPQVDInfo.enVideoStandard = E_PQ_VIDEOSTANDARD_PAL_BGHI;
        enVideoSystem_ForCaptureWindow = SIG_PAL;
        break;

    case E_VIDEOSTANDARD_SECAM:
        stPQVDInfo.enVideoStandard = E_PQ_VIDEOSTANDARD_SECAM;
        enVideoSystem_ForCaptureWindow = SIG_SECAM;
        break;

    case E_VIDEOSTANDARD_NTSC_44:
        stPQVDInfo.enVideoStandard = E_PQ_VIDEOSTANDARD_NTSC_44;
        enVideoSystem_ForCaptureWindow = SIG_NTSC_443;
        break;

    case E_VIDEOSTANDARD_PAL_M:
        stPQVDInfo.enVideoStandard = E_PQ_VIDEOSTANDARD_PAL_M;
        enVideoSystem_ForCaptureWindow = SIG_PAL_M;
        break;

    case E_VIDEOSTANDARD_PAL_N:
        stPQVDInfo.enVideoStandard = E_PQ_VIDEOSTANDARD_PAL_N;
        enVideoSystem_ForCaptureWindow = SIG_PAL_NC;
        break;

    case E_VIDEOSTANDARD_PAL_60:
        stPQVDInfo.enVideoStandard = E_PQ_VIDEOSTANDARD_PAL_60;
        enVideoSystem_ForCaptureWindow = SIG_PAL_M;
        break;

    default:
        ASSERT(0);
        stPQVDInfo.enVideoStandard = E_PQ_VIDEOSTANDARD_PAL_BGHI;
        enVideoSystem_ForCaptureWindow = SIG_PAL;
        break;
    }

    enPQ_VdStd_ForCapWin = stPQVDInfo.enVideoStandard;


    DEBUG_CAP_WIN( printf(" msAPI_AVD_GetCurrentVideoStandard()=%u\n", msAPI_AVD_GetCurrentVideoStandard()););

    if( IsVDHasSignal() )
    {
        DEBUG_CAP_WIN(printf(" VD has Signal\n"););
        switch ( enVideoSystem_ForCaptureWindow )
        {
            default:
                break;

            // 60Hz
            case SIG_NTSC:
            case SIG_NTSC_443:
            case SIG_PAL_M:
                if( bVdInputIs50Hz ) // VD is 50Hz
                {
                    enPQ_VdStd_ForCapWin = E_PQ_VIDEOSTANDARD_PAL_BGHI;
                    enVideoSystem_ForCaptureWindow = SIG_PAL;
                    printf(" enVideoSystem_ForCaptureWindow=SIG_PAL\n");
                }
                break;

            // 50Hz
            case SIG_PAL:
            case SIG_SECAM:
            case SIG_PAL_NC:
                if( bVdInputIs50Hz == FALSE ) // vd is 60Hz
                {
                    enPQ_VdStd_ForCapWin = E_PQ_VIDEOSTANDARD_NTSC_M;
                    enVideoSystem_ForCaptureWindow = SIG_NTSC;
                    printf(" enVideoSystem_ForCaptureWindow=SIG_NTSC\n");
                }
                break;
        }
    }
    else // No signal
    {
        DEBUG_CAP_WIN(printf(" VD is no Signal\n"););
    #if ( TV_SYSTEM == TV_NTSC )
        stPQVDInfo.enVideoStandard = E_PQ_VIDEOSTANDARD_NTSC_M;
        enVideoSystem_ForCaptureWindow = SIG_NTSC;
    #else // ( TV_SYSTEM == TV_PAL || TV_SYSTEM == TV_CHINA)
        stPQVDInfo.enVideoStandard = E_PQ_VIDEOSTANDARD_PAL_BGHI;
        enVideoSystem_ForCaptureWindow = SIG_PAL;
    #endif
        enPQ_VdStd_ForCapWin = stPQVDInfo.enVideoStandard;
    }

    MDrv_PQ_Set_VDInfo(enPQWin, &stPQVDInfo);

    DEBUG_CAP_WIN(printf(" 1 pstXC_SetWin_Info->stCapWin.width=%u\n", pstXC_SetWin_Info->stCapWin.width););
    DEBUG_CAP_WIN(printf(" 1 pstXC_SetWin_Info->stCapWin.height=%u\n", pstXC_SetWin_Info->stCapWin.height););
    DEBUG_CAP_WIN(printf(" 1 pstXC_SetWin_Info->stCapWin.x=%u\n", pstXC_SetWin_Info->stCapWin.x););
    DEBUG_CAP_WIN(printf(" 1 pstXC_SetWin_Info->stCapWin.y=%u\n", pstXC_SetWin_Info->stCapWin.y););

  #ifdef __EXTVD
    if(IsUseExtVDPort((INPUT_PORT_TYPE_t)enInputSourceType))
    {
        msAPI_AVD_GetCaptureWindow(&(pstXC_SetWin_Info->stCapWin), enVideoSystem_ForCaptureWindow, TRUE);
    }
    else
  #endif
    {
    #if(PQ_ENABLE_VD_SAMPLING)
        memset(&stVDSamplingInfo, 0, sizeof(MS_PQ_VD_Sampling_Info));
        MDrv_PQ_Get_VDSampling_Info(PQ_MAIN_WINDOW, PQ_INPUT_SOURCE_CVBS, enPQ_VdStd_ForCapWin, &stVDSamplingInfo);
        msAPI_AVD_GetCaptureWindowByPQ(&(pstXC_SetWin_Info->stCapWin), enVideoSystem_ForCaptureWindow, &stVDSamplingInfo);
    #else
        msAPI_AVD_GetCaptureWindow(&(pstXC_SetWin_Info->stCapWin), enVideoSystem_ForCaptureWindow, FALSE);
    #endif
    }

    DEBUG_CAP_WIN(printf(" 2 pstXC_SetWin_Info->stCapWin.width=%u\n", pstXC_SetWin_Info->stCapWin.width););
    DEBUG_CAP_WIN(printf(" 2 pstXC_SetWin_Info->stCapWin.height=%u\n", pstXC_SetWin_Info->stCapWin.height););
    DEBUG_CAP_WIN(printf(" 2 pstXC_SetWin_Info->stCapWin.x=%u\n", pstXC_SetWin_Info->stCapWin.x););
    DEBUG_CAP_WIN(printf(" 2 pstXC_SetWin_Info->stCapWin.y=%u\n", pstXC_SetWin_Info->stCapWin.y););

    if( /*IsSrcTypeATV(enInputSourceType) &&*/ !IsVDHasSignal() )
    {
        if( enVideoSystem_ForCaptureWindow == SIG_NTSC )
        {
            pstXC_SetWin_Info->stCapWin.height = 432;  //480 * 0.9 (V sync is unstable now, so setting capture height as standard * .9 (overscan 10%) )
        }
        else
        {
            pstXC_SetWin_Info->stCapWin.height = 518;
        }
        DEBUG_CAP_WIN(printf(" 3 pstXC_SetWin_Info->stCapWin.height=%u\n", pstXC_SetWin_Info->stCapWin.height););
    }

  #if ( TV_SYSTEM == TV_PAL || TV_SYSTEM == TV_CHINA)
    // for cut off some garbage on screen bottom while channel auto scan
    if( IsSrcTypeATV(enInputSourceType)
     && msAPI_Tuner_IsTuningProcessorBusy() == TRUE
     //&& MApp_ZUI_GetActiveOSD() == E_OSD_AUTO_TUNING
     && MApp_Is_InAutoScan_ATV()
      )
    {
        pstXC_SetWin_Info->stCapWin.height = 510;
        DEBUG_CAP_WIN(printf(" 4 pstXC_SetWin_Info->stCapWin.height=%u\n", pstXC_SetWin_Info->stCapWin.height););
    }
  #endif

    pstXC_SetWin_Info->bHDuplicate    = FALSE;     // not set in this path

//----------------------------------------------------------------------
    pstXC_SetWin_Info->bInterlace     = TRUE;

    if( !IsVDHasSignal() ) // VD no signal
    {
        u16InputHFreq = 157;
        if( bVdInputIs50Hz )
            pstXC_SetWin_Info->u16InputVTotal = 625;
        else
            pstXC_SetWin_Info->u16InputVTotal = 525;
    }
    else
    {
        u16InputHFreq = MApi_XC_CalculateHFreqx10(msAPI_Scaler_VD_GetHPeriod(eWindow, enInputSourceType, GET_SYNC_VIRTUAL));
        //stTimingInfo.u16InputVTotal = msAPI_Scaler_VD_GetVTotal(eWindow, enInputSourceType, GET_SYNC_VIRTUAL, u16InputHFreq);
        pstXC_SetWin_Info->u16InputVTotal = MDrv_AVD_GetVTotal();
    }

    if( pstXC_SetWin_Info->u16InputVTotal == 0 )
    {
        if( bVdInputIs50Hz )
            pstXC_SetWin_Info->u16InputVTotal = 625;
        else
            pstXC_SetWin_Info->u16InputVTotal = 525;
    }

    pstXC_SetWin_Info->u16InputVFreq = MApi_XC_CalculateVFreqx10(u16InputHFreq, pstXC_SetWin_Info->u16InputVTotal)*2;

    //printf(" u16InputHFreq=%u\n", u16InputHFreq);
    //printf(" .u16InputVTotal=%u\n", stTimingInfo.u16InputVTotal);
    //printf(" .u16InputVFreq=%u\n", pstXC_SetWin_Info->u16InputVFreq);

    if( bVdInputIs50Hz ) // VD 50Hz
    {
        //printf("Vd 50~\n");
        if( (pstXC_SetWin_Info->u16InputVFreq > 510) || (pstXC_SetWin_Info->u16InputVFreq < 490) )
        {
            printf("\nWarning: VD is 50Hz, u16InputVFreq=%u is abnormal!\n", pstXC_SetWin_Info->u16InputVFreq);
            pstXC_SetWin_Info->u16InputVFreq = 500;
        }
    }
    else
    {
        //printf("Vd 60~\n");
        if( (pstXC_SetWin_Info->u16InputVFreq > 610) || (pstXC_SetWin_Info->u16InputVFreq < 590) )
        {
            printf("\nWarning: VD is 60Hz, u16InputVFreq=%u is abnormal!\n", pstXC_SetWin_Info->u16InputVFreq);
            pstXC_SetWin_Info->u16InputVFreq = 600;
        }
    }


    // refine H/V capture start
    //MSG(printf("video system %d, aspect ratio %d\n", enVideoSystem, enVideoSystem));
#if(PQ_ENABLE_VD_SAMPLING)
    if(stVDSamplingInfo.eType == PQ_VD_SAMPLING_ON)
    {
        pstXC_SetWin_Info->stCapWin.x = stVDSamplingInfo.u16Hstart;
        pstXC_SetWin_Info->stCapWin.y = stVDSamplingInfo.u16Vstart;
    }
    else
#endif
    {
        pstXC_SetWin_Info->stCapWin.x = CVBS_WinInfo[enVideoSystem_ForCaptureWindow][u8AspectRatio].u16H_CapStart;
        pstXC_SetWin_Info->stCapWin.y = CVBS_WinInfo[enVideoSystem_ForCaptureWindow][u8AspectRatio].u16V_CapStart;
    }

    DEBUG_CAP_WIN(printf(" 8 pstXC_SetWin_Info->stCapWin.x=%u\n", pstXC_SetWin_Info->stCapWin.x););
    DEBUG_CAP_WIN(printf(" 8 pstXC_SetWin_Info->stCapWin.y=%u\n", pstXC_SetWin_Info->stCapWin.y););

    if (IsSrcTypeSV(enInputSourceType))
    {
        pstXC_SetWin_Info->stCapWin.x += SV_OffsetH[enVideoSystem_ForCaptureWindow];

        if(SV_OffsetV[enVideoSystem_ForCaptureWindow] & 0x80)
            pstXC_SetWin_Info->stCapWin.y -= SV_OffsetV[enVideoSystem_ForCaptureWindow] & 0x3F;
        else
            pstXC_SetWin_Info->stCapWin.y += SV_OffsetV[enVideoSystem_ForCaptureWindow] & 0x3F;
    }
    else if (IsSrcTypeScart(enInputSourceType))
    {
        if( stPQVDInfo.bIsSCART_RGB == TRUE )
        {
            // New method is adjust ADC, not Scaler!!
            //pstXC_SetWin_Info->stCapWin.x -= 112;//pach for scart RGB
        }
    }

    _u8H_OverScanRatio = OVERSCAN_DEFAULT_H;
    _u8V_OverScanRatio = OVERSCAN_DEFAULT_V;

    DEBUG_CAP_WIN(printf(" 10 pstXC_SetWin_Info->stCapWin.width=%u\n", pstXC_SetWin_Info->stCapWin.width););
    DEBUG_CAP_WIN(printf(" 10 pstXC_SetWin_Info->stCapWin.height=%u\n", pstXC_SetWin_Info->stCapWin.height););
    DEBUG_CAP_WIN(printf(" 10 pstXC_SetWin_Info->stCapWin.x=%u\n", pstXC_SetWin_Info->stCapWin.x););
    DEBUG_CAP_WIN(printf(" 10 pstXC_SetWin_Info->stCapWin.y=%u\n", pstXC_SetWin_Info->stCapWin.y););
}

/******************************************************************************/
///Setup input and output window information including aspect ratio, scaling.(MVD part)
///@param u8ModeIndex of DTV \b IN
///@param ptiming \b IN
///-pointer to VOP Timing information
/******************************************************************************/
static void _MApp_Scaler_ProgMVDWin(SCALER_WIN eWindow, INPUT_SOURCE_TYPE_t enInputSourceType, MVOP_Timing *ptiming, XC_SETWIN_INFO *pstXC_SetWin_Info)
{
    PQ_WIN enPQWin;
#if( ENABLE_DTV )
    MS_PQ_Dtv_Info stPQDTVInfo;
#endif
    MS_PQ_MuliMedia_Info stPQMMInfo;

    pstXC_SetWin_Info->stCapWin.x = MDrv_MVOP_GetHStart();
    pstXC_SetWin_Info->stCapWin.y = MDrv_MVOP_GetVStart();
    pstXC_SetWin_Info->stCapWin.width = ptiming->u16Width;
    pstXC_SetWin_Info->stCapWin.height = ptiming->u16Height;

    pstXC_SetWin_Info->bHDuplicate    = ptiming->bHDuplicate;
    pstXC_SetWin_Info->u16InputVTotal = ptiming->u16V_TotalCount;
    pstXC_SetWin_Info->bInterlace     = ptiming->bInterlace;

    if(pstXC_SetWin_Info->bInterlace)
    {
        pstXC_SetWin_Info->u16InputVFreq = (U16)((ptiming->u16ExpFrameRate * 2 + 50) / 100);
    }
    else
    {
        pstXC_SetWin_Info->u16InputVFreq = (U16)((ptiming->u16ExpFrameRate + 50) / 100);
    }

    _u8H_OverScanRatio = _u16OverscanDtvDefaultH;
    _u8V_OverScanRatio = _u16OverscanDtvDefaultV;


    enPQWin = _MApp_Scaler_SCALER_WIN_to_PQ_WIN(eWindow);

#if( ENABLE_DTV )
    if( IsSrcTypeDTV(enInputSourceType) )
    {
    #if MHEG5_ENABLE
        if( msAPI_MHEG5_IsIFrameExist() )
        {
            stPQDTVInfo.eType = E_PQ_DTV_IFRAME;
        }
        else
    #endif
        {
        #if ( CHIP_SUPPORT_HEVC )// IMPLEMENT_DTV_H265
            if( (g_eCodecType == E_VDEC_CODEC_TYPE_HEVC) )
            {
                stPQDTVInfo.eType = E_PQ_DTV_H265;
                MDrv_PQ_SetH264_OnOff(true);
            }
            else
        #endif
            if( (g_eCodecType == E_VDEC_CODEC_TYPE_H264) )
            {
                stPQDTVInfo.eType = E_PQ_DTV_H264;
                MDrv_PQ_SetH264_OnOff(true);
            }
            else
            {
                stPQDTVInfo.eType = E_PQ_DTV_MPEG2;
                MDrv_PQ_SetH264_OnOff(false);
            }
        }

        MDrv_PQ_Set_DTVInfo(enPQWin, &stPQDTVInfo);
    }
#endif

    if(IsSrcTypeStorage(enInputSourceType) || IsSrcTypeJpeg(enInputSourceType))
    {
    #if ENABLE_DMP
    #if ENABLE_MPLAYER_MOVIE

        if(E_MPLAYER_TYPE_MOVIE == MApp_MPlayer_QueryCurrentMediaType())
        {
            stPQMMInfo.eType = E_PQ_MULTIMEDIA_MOVIE;
        }
        else
   #endif
            if(E_MPLAYER_TYPE_PHOTO == MApp_MPlayer_QueryCurrentMediaType())
        {
            stPQMMInfo.eType = E_PQ_MULTIMEDIA_PHOTO;
        }
        else if(E_MPLAYER_TYPE_MUSIC == MApp_MPlayer_QueryCurrentMediaType())//Music album need to load photo bw table
        {
            stPQMMInfo.eType = E_PQ_MULTIMEDIA_PHOTO;
        }
        else
        {
            ASSERT(0);
        }
    #else
        stPQMMInfo.eType = E_PQ_MULTIMEDIA_MOVIE;
    #endif

        if(enMVOPVideoType == MVOP_H264)
        {
            MDrv_PQ_SetH264_OnOff(true);
            MSG(printf("enMVOPVideoType==MVOP_H264 \n"));
        }
        else
        {
            MDrv_PQ_SetH264_OnOff(false);
            MSG(printf(" enMVOPVideoType!=MVOP_H264 \n"));
        }


        MDrv_PQ_SetMM_OnOff(true);
        MDrv_PQ_Set_MultiMediaInfo(enPQWin, &stPQMMInfo);
    }
}

static void _MApp_Scaler_CropCodecSrcWin( VDEC_DispInfo *stVidStatus, XC_SETWIN_INFO *pstXC_SetWin_Info)
{
    MVOP_Handle stHdl = {E_MVOP_MODULE_MAIN};
    MVOP_DrvMirror enMirror = E_VOPMIRROR_NONE;

    MDrv_MVOP_GetCommand(&stHdl, E_MVOP_CMD_GET_MIRROR_MODE, &enMirror, sizeof(MVOP_DrvMirror));

    // this is from MVD additional information and it is MVD's crop window
    if((enMirror == E_VOPMIRROR_HVBOTH) || (enMirror == E_VOPMIRROR_HORIZONTALL))
    {
        pstXC_SetWin_Info->stCapWin.x += stVidStatus->u16CropRight;
    }
    else
    {
        pstXC_SetWin_Info->stCapWin.x += stVidStatus->u16CropLeft;
    }

    if((enMirror == E_VOPMIRROR_HVBOTH)  || (enMirror == E_VOPMIRROR_VERTICAL))
    {
        //H264 FW does not make MVOP transport crop_bottom to Scaler
        if( (IsStorageInUse() && (E_VDPLAYER_VIDEO_H264 == g_enVDPlayerVideoType))
          ||(IsDTVInUse() && (msAPI_VID_GetCodecType() == E_VDEC_CODEC_TYPE_H264))
          )
        {
            // do nothing!
        }
        else
        {
            pstXC_SetWin_Info->stCapWin.y += stVidStatus->u16CropBottom;
        }
    }
    else
    {
        pstXC_SetWin_Info->stCapWin.y += stVidStatus->u16CropTop;
    }

    pstXC_SetWin_Info->stCapWin.width -= (stVidStatus->u16CropLeft + stVidStatus->u16CropRight);
    pstXC_SetWin_Info->stCapWin.height -= (stVidStatus->u16CropTop + stVidStatus->u16CropBottom);

    MSG(printf("codec crop left=%u, top=%u, right=%u, bottom=%u\n",
                    stVidStatus->u16CropLeft, stVidStatus->u16CropTop,
                    stVidStatus->u16CropRight, stVidStatus->u16CropBottom));
}

static void _MApp_Scaler_CropCodecDisWin( XC_SETWIN_INFO *pstXC_SetWin_Info)
{
    MVOP_Handle stHdl = {E_MVOP_MODULE_MAIN};
    MVOP_DrvMirror enMirror = E_VOPMIRROR_NONE;
    MDrv_MVOP_GetCommand(&stHdl, E_MVOP_CMD_GET_MIRROR_MODE, &enMirror, sizeof(MVOP_DrvMirror));

    if((enMirror == E_VOPMIRROR_HVBOTH)  || (enMirror == E_VOPMIRROR_HORIZONTALL))
    {
        pstXC_SetWin_Info->stCropWin.x = pstXC_SetWin_Info->stCapWin.width - pstXC_SetWin_Info->stCropWin.x  - pstXC_SetWin_Info->stCropWin.width ;
        if(g_IPanel.Width() > (pstXC_SetWin_Info->stDispWin.x + pstXC_SetWin_Info->stDispWin.width))
        {
             pstXC_SetWin_Info->stDispWin.x = g_IPanel.Width() - (pstXC_SetWin_Info->stDispWin.x + pstXC_SetWin_Info->stDispWin.width);
        }
        else
        {
             pstXC_SetWin_Info->stDispWin.x = 0;
        }
    }

    if((enMirror == E_VOPMIRROR_HVBOTH)  || (enMirror == E_VOPMIRROR_VERTICAL))
    {
        pstXC_SetWin_Info->stCropWin.y = pstXC_SetWin_Info->stCapWin.height - pstXC_SetWin_Info->stCropWin.y  - pstXC_SetWin_Info->stCropWin.height ;
        if(g_IPanel.Height() > (pstXC_SetWin_Info->stDispWin.y + pstXC_SetWin_Info->stDispWin.height))
        {
             pstXC_SetWin_Info->stDispWin.y = g_IPanel.Height() - (pstXC_SetWin_Info->stDispWin.y + pstXC_SetWin_Info->stDispWin.height);
        }
        else
        {
             pstXC_SetWin_Info->stDispWin.y = 0;
        }
    }
}

void MApp_Scaler_EnableHDMI_RefineHVStart(BOOLEAN bEnable)
{
    _bEnHDMI_RefineHVStart = bEnable;
}

//********************************************************************************************
// Program capture win/crop win/display window
//   parameter:
//     pDisplayWindow  - The display window before adjust it .i.e: adjust aspect ratio to it.
//     eWindow             - Display window id, i.e Main_WINDOW or SUB_WINDOW
//********************************************************************************************
static void _MApp_XC_check_crop_win( XC_SETWIN_INFO *pstXC_SetWin_Info )
{
    if (pstXC_SetWin_Info->stCropWin.width > pstXC_SetWin_Info->stCapWin.width)
    {
        ASSERT(0);
        pstXC_SetWin_Info->stCropWin.width = pstXC_SetWin_Info->stCapWin.width;
    }

    if (pstXC_SetWin_Info->stCropWin.height > pstXC_SetWin_Info->stCapWin.height)
    {
        ASSERT(0);
        pstXC_SetWin_Info->stCropWin.height = pstXC_SetWin_Info->stCapWin.height;
    }

    if (pstXC_SetWin_Info->stCropWin.x > pstXC_SetWin_Info->stCapWin.width - pstXC_SetWin_Info->stCropWin.width)
    {
        ASSERT(0);
        pstXC_SetWin_Info->stCropWin.x = pstXC_SetWin_Info->stCapWin.width - pstXC_SetWin_Info->stCropWin.width;
    }
    if (pstXC_SetWin_Info->stCropWin.y > pstXC_SetWin_Info->stCapWin.height - pstXC_SetWin_Info->stCropWin.height)
    {
        ASSERT(0);
        pstXC_SetWin_Info->stCropWin.y = pstXC_SetWin_Info->stCapWin.height - pstXC_SetWin_Info->stCropWin.height;
    }
}

#if ENABLE_FBL_ASPECT_RATIO_BY_MVOP

void MApp_Scaler_AdjustDisplayContent(MS_WINDOW_TYPE *ptWin, U16 u16X, U16 u16Y, U16 u16Width, U16 u16Height)
{
    if(NULL == ptWin)
    {
        printf("Invalid Pointer!\n");
        return;
    }

    if(u16X >= ptWin->width || u16Y >= ptWin->height
       || u16Width > ptWin->width || u16Height > ptWin->height
       || u16X + u16Width > ptWin->width || u16Y + u16Height > ptWin->height)
    {
        printf("May have invalid input parameters!\n");
    }

    if(u16X < ptWin->width)
    {
        ptWin->x = u16X;
    }

    if(u16Y < ptWin->height)
    {
        ptWin->y = u16Y;
    }

    if(u16Width < ptWin->width)
    {
        if(ptWin->x + u16Width <= ptWin->width)
        {
            ptWin->width = u16Width;
        }
        else
        {
            ptWin->width -= ptWin->x;
        }
    }

    if(u16Height < ptWin->height)
    {
        if(ptWin->y + u16Height <= ptWin->height)
        {
            ptWin->height = u16Height;
        }
        else
        {
            ptWin->height -= ptWin->y;
        }
    }
}


U16 MApp_Scaler_GetMVOPMinVDE_ForFixVtotal(U8 u8Interlace, U16 u16FrameRate, U16 u16PanelVotal, U16 u16PanelHeight)
{
    MS_BOOL b50HZOutput = (!u8Interlace && (u16FrameRate > 49500) && (u16FrameRate <= 50000))
                        || (u8Interlace && (u16FrameRate > 24500) && (u16FrameRate <= 25000));
    U16 u16MVOPMinVBlank = 0;
    U16 u16MinVDE = 0;
    if(u8Interlace)
    {
        u16MVOPMinVBlank = 35;
    }
    else
    {
        u16MVOPMinVBlank = 20;
    }
    if(b50HZOutput)
    {
        u16MinVDE = (u16MVOPMinVBlank * 5 * u16PanelHeight) / (6 * u16PanelVotal - 5 * u16PanelHeight) + 1;
    }
    else
    {
        u16MinVDE = (u16MVOPMinVBlank * u16PanelHeight) / (u16PanelVotal - u16PanelHeight) + 1;
    }
    return u16MinVDE;
}

void MApp_Scaler_SetFixVtotal(U8 u8Interlace, U16 u16FrameRate, U16 u16VDE)
{
    if(MApi_XC_IsCurrentFrameBufferLessMode())
    {
        MS_U16 TargetVtt = 0;
        MSG(printf("Panel_Vtotal=%u,Panel_Vde=%u\n", g_IPanel.VTotal(), devPanel_HEIGHT());)
        MSG(printf("u8Interlace=%u,u16FrameRate=%u,u16VDE=%u\n", u8Interlace, u16FrameRate, u16VDE);)

        if(u16VDE >= MApp_Scaler_GetMVOPMinVDE_ForFixVtotal(u8Interlace, u16FrameRate, g_IPanel.VTotal(), devPanel_HEIGHT()))
        {
            if((!u8Interlace && (u16FrameRate > 49500) && (u16FrameRate <= 50000))
                || (u8Interlace && (u16FrameRate > 24500) && (u16FrameRate <= 25000)))
            {
                TargetVtt = g_IPanel.VTotal() * 6 / 5 * u16VDE / devPanel_HEIGHT();
                MSG(printf("change vtt in aeonmm TargetVtt = %u\n", TargetVtt);)
            }
            else
            {
                TargetVtt = g_IPanel.VTotal() * u16VDE / devPanel_HEIGHT();
            }
            // Force Mvop adjust its timing when FBL
            MSG(printf("TargetVtt:%u\n",TargetVtt);)
            if(MDrv_MVOP_SetFixVtt(TargetVtt) == FALSE)
            {
                printf("-------Attention! Fix VTotal Feature is not Enabled!-------\n");
            }
        }
        else
        {
            printf("-------Attention! we can not support such display method since mvop vblank is too small!-------\n");
        }
    }
    else
    {
        printf("-------Attention! FB doesn't support this feature!-------\n");
    }
}

void MApp_Scaler_Adjust_AspectRatio_FBL(EN_ASPECT_RATIO_TYPE enVideoScreen, MS_WINDOW_TYPE *ptSrcWin)
{
    U32 u32MVOP_Black_Width = 0;
    U32 u32MVOP_Black_Height = 0;
    U16 u16Temp = 0;
    U16 x0 = 0, y0 = 0,x1 = 0, y1 = 0;
    U16 u16TempUp = 0;
    U16 u16TempDown = 0;

    if(NULL == ptSrcWin)
    {
        printf("Invalid Pointer:ptSrcWin\n");
        return;
    }

    if(!MApi_XC_IsCurrentFrameBufferLessMode())
    {
        MSG(printf("this function only support for FBL!\n");)
        return;
    }

    MSG(printf("enVideoScreen=%u\n\n", enVideoScreen);)

    g_u16HorOffset = 0;
    g_u16VerOffset = 0;
    g_bApplyMVOPCrop = FALSE;
    ptSrcWin->width = gstVidStatus.u16HorSize;
    ptSrcWin->height = gstVidStatus.u16VerSize;

    switch(enVideoScreen)
    {
    case VIDEOSCREEN_PROGRAM_16X9:
        u16Temp = (U32)devPanel_HEIGHT() * 16 / 9;
        if(u16Temp <= devPanel_WIDTH())
        {
            g_u16HorOffset = (float)(devPanel_WIDTH() - u16Temp) / ((float)u16Temp / gstVidStatus.u16HorSize) / 2;
        }
        else
        {
            u16Temp = (U32)devPanel_WIDTH() * 9 / 16;
            g_u16VerOffset = (float)(devPanel_HEIGHT() - u16Temp) / ((float)u16Temp / gstVidStatus.u16VerSize) / 2;
        }
        break;
    case VIDEOSCREEN_PROGRAM_4X3:
#if 0
      #if 0
        MSG(printf("should not enter VIDEOSCREEN_PROGRAM_4X3!\n");)
        u16Temp = (U32)devPanel_HEIGHT() * 4 / 3;
        if(u16Temp <= devPanel_WIDTH())
        {
            g_u16HorOffset = (float)(devPanel_WIDTH() - u16Temp) / ((float)u16Temp / gstVidStatus.u16HorSize) / 2;
        }
        else
        {
            u16Temp = (U32)devPanel_WIDTH() * 3 / 4;
            g_u16VerOffset = (float)(devPanel_HEIGHT() - u16Temp) / ((float)u16Temp / gstVidStatus.u16VerSize) / 2;
        }
      #else
        MApp_VDPlayer_GetMVOPBlackSize((U32)gstVidStatus.u16HorSize, (U32)gstVidStatus.u16VerSize, &u32MVOP_Black_Width, &u32MVOP_Black_Height);
        MSG(printf("w=%u, h=%u,  black_W=%lu, black_H=%lu \n",gstVidStatus.u16HorSize, gstVidStatus.u16VerSize, u32MVOP_Black_Width, u32MVOP_Black_Height);)
        g_u16HorOffset = u32MVOP_Black_Width;
        g_u16VerOffset = u32MVOP_Black_Height;
      #endif
#endif
        break;

    case VIDEOSCREEN_ZOOM1:
        MApp_Scaler_ResetZoomFactor(EN_AspectRatio_Zoom1);
        ptSrcWin->x = 0;
        ptSrcWin->y = 0;
        ptSrcWin->width = gstVidStatus.u16HorSize - gstVidStatus.u16CropLeft - gstVidStatus.u16CropRight;
        ptSrcWin->height = gstVidStatus.u16VerSize - gstVidStatus.u16CropTop - gstVidStatus.u16CropBottom;
        x0 = (U16)((U32)ptSrcWin->width * _s16ZoomLeft / ZOOM_DENUMERATOR);
        y0 = (U16)((U32)ptSrcWin->height * _s16ZoomUp / ZOOM_DENUMERATOR);
        x1 = (U16)((U32)ptSrcWin->width * _s16ZoomRight / ZOOM_DENUMERATOR);
        y1 = (U16)((U32)ptSrcWin->height * _s16ZoomDown / ZOOM_DENUMERATOR);
        MApp_Scaler_AdjustDisplayContent(ptSrcWin, x0, y0, ptSrcWin->width - (x0 + x1), ptSrcWin->height - (y0 + y1));
        gstVidStatus.u16HorSize = ptSrcWin->width;
        gstVidStatus.u16VerSize = ptSrcWin->height;
        g_u16HorOffset = 0;
        g_u16VerOffset = 0;
        g_bApplyMVOPCrop = TRUE;
        break;
    case VIDEOSCREEN_ZOOM2:
        MApp_Scaler_ResetZoomFactor(EN_AspectRatio_Zoom2);
        ptSrcWin->x = 0;
        ptSrcWin->y = 0;
        ptSrcWin->width = gstVidStatus.u16HorSize - gstVidStatus.u16CropLeft - gstVidStatus.u16CropRight;
        ptSrcWin->height = gstVidStatus.u16VerSize - gstVidStatus.u16CropTop - gstVidStatus.u16CropBottom;
        x0 = (U16)((U32)ptSrcWin->width * _s16ZoomLeft / ZOOM_DENUMERATOR);
        y0 = (U16)((U32)ptSrcWin->height * _s16ZoomUp / ZOOM_DENUMERATOR);
        x1 = (U16)((U32)ptSrcWin->width * _s16ZoomRight / ZOOM_DENUMERATOR);
        y1 = (U16)((U32)ptSrcWin->height * _s16ZoomDown / ZOOM_DENUMERATOR);
        MApp_Scaler_AdjustDisplayContent(ptSrcWin, x0, y0, ptSrcWin->width - (x0 + x1), ptSrcWin->height - (y0 + y1));
        gstVidStatus.u16HorSize = ptSrcWin->width;
        gstVidStatus.u16VerSize = ptSrcWin->height;
        g_u16HorOffset = 0;
        g_u16VerOffset = 0;
        g_bApplyMVOPCrop = TRUE;
        break;
    case VIDEOSCREEN_PROGRAM: // Set Capture/Crop/Display window by function directly
        ptSrcWin->x = 0;
        ptSrcWin->y = 0;
        ptSrcWin->width = gstVidStatus.u16HorSize - gstVidStatus.u16CropLeft - gstVidStatus.u16CropRight;
        ptSrcWin->height = gstVidStatus.u16VerSize - gstVidStatus.u16CropTop - gstVidStatus.u16CropBottom;
        x0 = (U16)((U32)ptSrcWin->width * _s16ZoomLeft / ZOOM_DENUMERATOR);
        y0 = (U16)((U32)ptSrcWin->height * _s16ZoomUp / ZOOM_DENUMERATOR);
        x1 = (U16)((U32)ptSrcWin->width * _s16ZoomRight / ZOOM_DENUMERATOR);
        y1 = (U16)((U32)ptSrcWin->height * _s16ZoomDown / ZOOM_DENUMERATOR);
        MApp_Scaler_AdjustDisplayContent(ptSrcWin, x0, y0, ptSrcWin->width - (x0 + x1), ptSrcWin->height - (y0 + y1));
        gstVidStatus.u16HorSize = ptSrcWin->width;
        gstVidStatus.u16VerSize = ptSrcWin->height;
        g_u16HorOffset = 0;
        g_u16VerOffset = 0;
        g_bApplyMVOPCrop = TRUE;
        break;
    case VIDEOSCREEN_CINEMA:
        ptSrcWin->x = 0;
        ptSrcWin->y = 0;
        ptSrcWin->width = gstVidStatus.u16HorSize - gstVidStatus.u16CropLeft - gstVidStatus.u16CropRight;
        ptSrcWin->height = gstVidStatus.u16VerSize - gstVidStatus.u16CropTop - gstVidStatus.u16CropBottom;
        MApp_Scaler_AdjustDisplayContent(ptSrcWin, ((U32)ptSrcWin->width * ARC_CINEMA_OVS_H) / 1000, ((U32)ptSrcWin->height * ARC_CINEMA_OVS_V) / 1000,
                                         ptSrcWin->width - 2 * ((U32)ptSrcWin->width * ARC_CINEMA_OVS_H) / 1000,
                                         ptSrcWin->height - 2 * ((U32)ptSrcWin->height * ARC_CINEMA_OVS_V) / 1000);
        gstVidStatus.u16HorSize = ptSrcWin->width;
        gstVidStatus.u16VerSize = ptSrcWin->height;
        g_u16HorOffset = 0;
        g_u16VerOffset = 0;
        g_bApplyMVOPCrop = TRUE;
        break;
    case VIDEOSCREEN_14by9:
        ptSrcWin->x = 0;
        ptSrcWin->y = 0;
        ptSrcWin->width = gstVidStatus.u16HorSize - gstVidStatus.u16CropLeft - gstVidStatus.u16CropRight;
        ptSrcWin->height = gstVidStatus.u16VerSize - gstVidStatus.u16CropTop - gstVidStatus.u16CropBottom;
        u16TempUp = ((U32)ptSrcWin->height * ARC_14X19_OVS_UP + 500) / 1000;
        u16TempDown = ((U32)ptSrcWin->height * ARC_14X19_OVS_DOWN + 500) / 1000;
        MApp_Scaler_AdjustDisplayContent(ptSrcWin, 0, u16TempUp, ptSrcWin->width, ptSrcWin->height - (u16TempUp + u16TempDown));

        gstVidStatus.u16HorSize = ptSrcWin->width;
        gstVidStatus.u16VerSize = ptSrcWin->height;

        u16Temp = (U32)devPanel_HEIGHT() * 14 / 9;
        if (u16Temp <= devPanel_WIDTH()) // H:V >= 14:9
        {
            g_u16HorOffset = (float)(devPanel_WIDTH() - u16Temp) / ((float)u16Temp / gstVidStatus.u16HorSize) / 2;
        }
        else // H:V <= 4:3
        {
            u16Temp = (U32)devPanel_WIDTH() * 9 / 14;
            g_u16VerOffset = (float)(devPanel_HEIGHT() - u16Temp) / ((float)u16Temp / gstVidStatus.u16VerSize) / 2;
        }
        g_bApplyMVOPCrop = TRUE;
        break;
    case VIDEOSCREEN_16by9_SUBTITLE:
        ptSrcWin->x = 0;
        ptSrcWin->y = 0;
        ptSrcWin->width = gstVidStatus.u16HorSize - gstVidStatus.u16CropLeft - gstVidStatus.u16CropRight;
        ptSrcWin->height = gstVidStatus.u16VerSize - gstVidStatus.u16CropTop - gstVidStatus.u16CropBottom;
        MApp_Scaler_AdjustDisplayContent(ptSrcWin, 0, ptSrcWin->height * 1 / 8, ptSrcWin->width, ptSrcWin->height * 6 / 8);
        gstVidStatus.u16HorSize = ptSrcWin->width;
        gstVidStatus.u16VerSize = ptSrcWin->height;

        u16Temp = (U32)devPanel_HEIGHT() * 32 / 21; // 640x420 => 1097x720 Display
        if (u16Temp <= devPanel_WIDTH()) // H:V >= 32:21
        {
            g_u16HorOffset = (float)(devPanel_WIDTH() - u16Temp) / ((float)u16Temp / gstVidStatus.u16HorSize) / 2;
        }
        else // H:V <= 32:21
        {
            u16Temp = (U32)devPanel_WIDTH() * 21 / 32;
            g_u16VerOffset = (float)(devPanel_HEIGHT() - u16Temp) / ((float)u16Temp / gstVidStatus.u16VerSize) / 2;
        }
        g_bApplyMVOPCrop = TRUE;
        break;
    case VIDEOSCREEN_PANORAMA:
        _bEnNonLinearScaling[MAIN_WINDOW] = TRUE;
        break;
    case VIDEOSCREEN_NORMAL:
#if 0
      #if 0
        if ((g_IPanel.AspectRatio()==E_PNL_ASPECT_RATIO_WIDE))
        {
            MSG(printf("should not enter into VIDEOSCREEN_NORMAL\n");)
            u16Temp = (U32)devPanel_HEIGHT() * 4 / 3;
            if(u16Temp <= devPanel_WIDTH())
            {
                g_u16HorOffset = (float)(devPanel_WIDTH() - u16Temp) / ((float)u16Temp / gstVidStatus.u16HorSize) / 2;
            }
            else
            {
                u16Temp = (U32)devPanel_WIDTH() * 3 / 4;
                g_u16VerOffset = (float)(devPanel_HEIGHT() - u16Temp) / ((float)u16Temp / gstVidStatus.u16VerSize) / 2;
            }
        }
        else
        {
            u16Temp = (U32)devPanel_HEIGHT() * 16 / 9;
            if(u16Temp <= devPanel_WIDTH())
            {
                g_u16HorOffset = (float)(devPanel_WIDTH() - u16Temp) / ((float)u16Temp / gstVidStatus.u16HorSize) / 2;
            }
            else
            {
                u16Temp = (U32)devPanel_WIDTH() * 9 / 16;
                g_u16VerOffset = (float)(devPanel_HEIGHT() - u16Temp) / ((float)u16Temp / gstVidStatus.u16VerSize) / 2;
            }
        }
      #else
        MApp_VDPlayer_GetMVOPBlackSize((U32)gstVidStatus.u16HorSize, (U32)gstVidStatus.u16VerSize, &u32MVOP_Black_Width, &u32MVOP_Black_Height);
        MSG(printf("w=%u, h=%u,  black_W=%lu, black_H=%lu \n",gstVidStatus.u16HorSize, gstVidStatus.u16VerSize, u32MVOP_Black_Width, u32MVOP_Black_Height);)
        g_u16HorOffset = u32MVOP_Black_Width;
        g_u16VerOffset = u32MVOP_Black_Height;
      #endif
#endif
        break;

    case VIDEOSCREEN_LETTERBOX:
        u16Temp = (U32)devPanel_WIDTH() * 9 / 16;
        g_u16VerOffset = (float)(devPanel_HEIGHT() - u16Temp) / ((float)u16Temp / gstVidStatus.u16VerSize) / 2;
        break;
    case VIDEOSCREEN_WSS_16by9:
        ptSrcWin->x = 0;
        ptSrcWin->y = 0;
        ptSrcWin->width = gstVidStatus.u16HorSize - gstVidStatus.u16CropLeft - gstVidStatus.u16CropRight;
        ptSrcWin->height = gstVidStatus.u16VerSize - gstVidStatus.u16CropTop - gstVidStatus.u16CropBottom;
        MApp_Scaler_AdjustDisplayContent(ptSrcWin, 0, ptSrcWin->height * 1 / 8, ptSrcWin->width, ptSrcWin->height * 6 / 8);
        gstVidStatus.u16HorSize = ptSrcWin->width;
        gstVidStatus.u16VerSize = ptSrcWin->height;
        g_bApplyMVOPCrop = TRUE;
        break;

#if defined(ENABLE_MEDIAPLAYER) || (DISPLAY_LOGO)
    case VIDEOSCREEN_ORIGIN:
        if((gstVidStatus.u16HorSize <= devPanel_WIDTH())
           && (gstVidStatus.u16VerSize <= devPanel_HEIGHT()))
        {
            MSG(printf("Display Original!\n");)
            g_u16HorOffset = (devPanel_WIDTH() - gstVidStatus.u16HorSize) / 2;
            g_u16VerOffset = (devPanel_HEIGHT() - gstVidStatus.u16VerSize) / 2;
        }
        else
        {
            //for FBL set MVOP for maintain video ratio
            MApp_VDPlayer_GetMVOPBlackSize((U32)gstVidStatus.u16HorSize, (U32)gstVidStatus.u16VerSize, &u32MVOP_Black_Width, &u32MVOP_Black_Height);
            MSG(printf("\n w=%u, h=%u,  black_W=%lu, black_H=%lu \n",gstVidStatus.u16HorSize, gstVidStatus.u16VerSize, u32MVOP_Black_Width, u32MVOP_Black_Height);)
            g_u16HorOffset = u32MVOP_Black_Width;
            g_u16VerOffset = u32MVOP_Black_Height;
        }
        break;
#endif

    case VIDEOSCREEN_FULL:
    default:
        MApp_VDPlayer_GetMVOPBlackSize((U32)gstVidStatus.u16HorSize, (U32)gstVidStatus.u16VerSize, &u32MVOP_Black_Width, &u32MVOP_Black_Height);
        MSG(printf("w=%u, h=%u,  black_W=%lu, black_H=%lu \n",gstVidStatus.u16HorSize, gstVidStatus.u16VerSize, u32MVOP_Black_Width, u32MVOP_Black_Height);)
        g_u16HorOffset = u32MVOP_Black_Width;
        g_u16VerOffset = u32MVOP_Black_Height;
        break;
    }
    ptSrcWin->width = (ptSrcWin->width >> 3) << 3; // 8 bytes align
    ptSrcWin->height = (ptSrcWin->height>> 1) << 1; // even
    gstVidStatus.u16HorSize = ptSrcWin->width;
    gstVidStatus.u16VerSize = ptSrcWin->height;
}

void MApp_Scaler_SetFBLTimingForAspectRatio(EN_ASPECT_RATIO_TYPE enVideoScreen)
{
    MS_WINDOW_TYPE tSrcWin;
    U16 u16VDE = 0;
    MVOP_VidStat stMvopVidSt;

    if(!MApi_XC_IsCurrentFrameBufferLessMode())
    {
        MSG(printf("this function only support for FBL!\n");)
        return;
    }

    if(enMVOPVideoType == MVOP_MJPEG)
    {
        //no FBL case
        printf("No FBL for MJPEG yet!\n");
        return;
    }

    msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
    memset(&tSrcWin, 0, sizeof(tSrcWin));
    memset(&stMvopVidSt, 0, sizeof(MVOP_VidStat));

    if(IsSrcTypeStorage(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
    {
        // load video information
        gstVidStatus.u32FrameRate = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_FRAME_RATE);
        gstVidStatus.u8Interlace = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_INTERLACE);
        gstVidStatus.u16HorSize =  _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WIDTH);
        gstVidStatus.u16VerSize = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_HEIGHT);
        gstVidStatus.u16CropRight = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_VIDEO_CROP_RIGHT);
        gstVidStatus.u16CropLeft = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_VIDEO_CROP_LEFT);
        gstVidStatus.u16CropBottom = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_VIDEO_CROP_BOTTOM);
        gstVidStatus.u16CropTop = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_VIDEO_CROP_TOP);
    }

    MSG(printf("width=%u, height=%u, framerate=%u, Interlace=%u\n", gstVidStatus.u16HorSize, gstVidStatus.u16VerSize, gstVidStatus.u32FrameRate, gstVidStatus.u8Interlace);)
    MSG(printf("cropleft=%u, cropright=%u, croptop=%u, cropbottom=%u\n", gstVidStatus.u16CropLeft, gstVidStatus.u16CropRight, gstVidStatus.u16CropTop, gstVidStatus.u16CropBottom);)

    MApp_Scaler_Adjust_AspectRatio_FBL(enVideoScreen, &tSrcWin);

    if((gstVidStatus.u32FrameRate > 24500) && (gstVidStatus.u32FrameRate <= 25000))
    {
        //gstVidStatus.u32FrameRate = 25000;
    }
    else if((gstVidStatus.u32FrameRate > 49500) && (gstVidStatus.u32FrameRate <= 50000))
    {
        gstVidStatus.u32FrameRate = gstVidStatus.u32FrameRate / 2; //25
    }
    else if((gstVidStatus.u32FrameRate > 23500) && (gstVidStatus.u32FrameRate <= 24000) )
    {
        gstVidStatus.u32FrameRate = (U32)gstVidStatus.u32FrameRate * 5 / 4; //30
    }
    else if((gstVidStatus.u32FrameRate > 29500) && (gstVidStatus.u32FrameRate <= 30000))
    {
        //~30
    }
    else
    {
        gstVidStatus.u32FrameRate = 30000;
    }

    if (gstVidStatus.u8Interlace == FALSE)   // progressive
    {
        gstVidStatus.u32FrameRate *= 2;
    }

    MDrv_MVOP_Init();
    stMvopVidSt.u16HorSize   = gstVidStatus.u16HorSize;
    stMvopVidSt.u16VerSize   = gstVidStatus.u16VerSize;
    stMvopVidSt.u16FrameRate = gstVidStatus.u32FrameRate;
    stMvopVidSt.u8AspectRate = gstVidStatus.u8AspectRate;
    stMvopVidSt.u8Interlace  = gstVidStatus.u8Interlace;
    stMvopVidSt.u16HorOffset = g_u16HorOffset;
    stMvopVidSt.u16VerOffset = g_u16VerOffset;
    u16VDE = gstVidStatus.u16VerSize - (gstVidStatus.u16CropTop + gstVidStatus.u16CropBottom) + 2 * g_u16VerOffset;
    MApp_Scaler_SetFixVtotal(stMvopVidSt.u8Interlace, stMvopVidSt.u16FrameRate, u16VDE);
    MDrv_MVOP_SetOutputCfg(&stMvopVidSt, FALSE);

    MDrv_MVOP_Enable(FALSE);

    switch (enMVOPVideoType)
    {
        case MVOP_MPEG4:
        case MVOP_MPG:
            if(g_bApplyMVOPCrop)
            {
                MVOP_InputCfg dc_param;
                memset(&dc_param, 0, sizeof(MVOP_InputCfg));
                dc_param.u16CropWidth = tSrcWin.width;
                dc_param.u16CropHeight = tSrcWin.height;
                dc_param.u16CropX = tSrcWin.x;
                dc_param.u16CropY = tSrcWin.y;
                dc_param.enVideoType = MVOP_MPG;
              #if (VIDEO_FIRMWARE_CODE >= VIDEO_FIRMWARE_CODE_HD)
                dc_param.u16StripSize = 1920;
              #else
                dc_param.u16StripSize = 720;
              #endif
                MDrv_MVOP_SetInputCfg(MVOP_INPUT_CLIP, &dc_param);
            }
            else
            {
                MDrv_MVOP_SetInputCfg(MVOP_INPUT_MVD, NULL);
            }
            break;

        case MVOP_H264:
            if(g_bApplyMVOPCrop)
            {
                MVOP_InputCfg dc_param;
                memset(&dc_param, 0, sizeof(MVOP_InputCfg));
                dc_param.u16CropWidth = tSrcWin.width;
                dc_param.u16CropHeight = tSrcWin.height;
                dc_param.u16CropX = tSrcWin.x;
                dc_param.u16CropY = tSrcWin.y;
                dc_param.enVideoType = MVOP_H264;
                if(IsSrcTypeStorage(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
                {
                    dc_param.u16StripSize = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WIDTH);
                }
                else if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
                {
                    dc_param.u16StripSize = g_u16StripSize;
                }
                else
                {
                    printf("this input source type is not supported\n");
                }
                MDrv_MVOP_SetInputCfg(MVOP_INPUT_CLIP, &dc_param);
            }
            else
            {
                MDrv_MVOP_SetInputCfg(MVOP_INPUT_H264, NULL);
            }
            break;

        case MVOP_RM:
            if(g_bApplyMVOPCrop)
            {
                MVOP_InputCfg dc_param;
                memset(&dc_param, 0, sizeof(MVOP_InputCfg));
                dc_param.u16CropWidth = tSrcWin.width;
                dc_param.u16CropHeight = tSrcWin.height;
                dc_param.u16CropX = tSrcWin.x;
                dc_param.u16CropY = tSrcWin.y;
                dc_param.enVideoType = MVOP_RM;
                if(IsSrcTypeStorage(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
                {
                    dc_param.u16StripSize = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WIDTH);
                }
                else if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
                {
                    dc_param.u16StripSize = g_u16StripSize;
                }
                else
                {
                    printf("this input source type is not supported\n");
                }
                MDrv_MVOP_SetInputCfg(MVOP_INPUT_CLIP, &dc_param);
            }
            else
            {
                MDrv_MVOP_SetInputCfg(MVOP_INPUT_RVD, NULL);
            }
            break;
        default:
            break;
    }

    MApp_Scaler_EnableOverScan(FALSE);
    MDrv_MVOP_Enable(TRUE);
    MApp_Scaler_SetWindow(NULL, NULL, NULL, stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);

    MApp_Picture_Setting_SetColor(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
    MApp_Scaler_SetTiming(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
    msAPI_Scaler_SetBlueScreen(DISABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
}

#endif // #if ENABLE_FBL_ASPECT_RATIO_BY_MVOP

#if ENABLE_3D_PROCESS
void MApp_Scaler_Adjust_3D_CropWin(MS_WINDOW_TYPE *pstCropWin)
{
    E_XC_3D_INPUT_MODE e_XC_3D_INPUT_MODE = MApi_XC_Get_3D_Input_Mode(MAIN_WINDOW);

    DEBUG_3D( printf(" 3D e_XC_3D_INPUT_MODE=%d\n", e_XC_3D_INPUT_MODE); );

    if((e_XC_3D_INPUT_MODE == E_XC_3D_INPUT_SIDE_BY_SIDE_HALF)
       ||(e_XC_3D_INPUT_MODE == E_XC_3D_INPUT_SIDE_BY_SIDE_HALF_INTERLACE)
     )
    {
        pstCropWin->x /= 2;
    }
    else if((e_XC_3D_INPUT_MODE == E_XC_3D_INPUT_TOP_BOTTOM)
      ||(e_XC_3D_INPUT_MODE == E_XC_3D_INPUT_FRAME_PACKING)
      ||(e_XC_3D_INPUT_MODE == E_XC_3D_INPUT_LINE_ALTERNATIVE))
    {
        pstCropWin->y /= 2;
    }
}

BOOLEAN MApp_3D_SetLRSwitchFlag(MS_BOOL bEnable)
{
    _bLRSwitch =bEnable;
    return TRUE;
}

BOOLEAN MApp_3D_GetLRSwitchFlag(void)
{
     return _bLRSwitch;
}

static void MApp_3D_AdjustIndividualDisplayWin(XC_SETWIN_INFO *pstXC_SetWin_Info, SCALER_WIN eWindow, EN_ASPECT_RATIO_TYPE en3DARCType)
{
    MENU_3D_DBG(printf("3D: after _AdjustIndividualDisplayWin: (%u,%u,%u,%u)\n", pstXC_SetWin_Info->stDispWin.x,
            pstXC_SetWin_Info->stDispWin.y, pstXC_SetWin_Info->stDispWin.width, pstXC_SetWin_Info->stDispWin.height);)

    if(MApi_XC_Get_3D_Input_Mode(eWindow) == E_XC_3D_INPUT_FRAME_PACKING)
    {
        return;
    }

#if (MHEG5_ENABLE)
    if((msAPI_MHEG5_IsRunning())&&(( msAPI_MHEG5_IsIFrameExist() || !g_MHEG5Video.bHaveVideo)||(!msAPI_MHEG5_VID_IsFullScreen(&g_MHEG5Video.stMHEG5VideoAction))))
    {
        return;
    }
#endif

    if(en3DARCType == VIDEOSCREEN_3D_FULL)
    {
        if((MApi_XC_Get_3D_Output_Mode() == E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF)
           ||
           (MApi_XC_Get_3D_Output_Mode() == E_XC_3D_OUTPUT_TOP_BOTTOM))
        {
            // use pass-in param's ptDstWin
        }
        else if(MApi_XC_Get_3D_Panel_Type() != E_XC_3D_PANEL_NONE)//we don't want none-3D case fall into here
        {
            pstXC_SetWin_Info->stDispWin.x = 0;
            pstXC_SetWin_Info->stDispWin.y = 0;
            pstXC_SetWin_Info->stDispWin.width = g_IPanel.Width();
            pstXC_SetWin_Info->stDispWin.height = g_IPanel.Height();
        }
    }
    else if(en3DARCType == VIDEOSCREEN_3D_AUTO)
    {
        if((MS_U32)g_IPanel.Width() * pstXC_SetWin_Info->stCropWin.height > (MS_U32)pstXC_SetWin_Info->stCropWin.width * g_IPanel.Height())
        {
            if(MApi_XC_Get_3D_Output_Mode() == E_XC_3D_OUTPUT_TOP_BOTTOM)
            {
                pstXC_SetWin_Info->stDispWin.width =
                    (MS_U32)pstXC_SetWin_Info->stCropWin.width * g_IPanel.Height() / pstXC_SetWin_Info->stCropWin.height;
                pstXC_SetWin_Info->stDispWin.height = g_IPanel.Height() / 2;
                pstXC_SetWin_Info->stDispWin.x = (g_IPanel.Width() - pstXC_SetWin_Info->stDispWin.width) / 2;
                //don't set y, because main and sub's y will be different and specified at outside
            }
            else if(MApi_XC_Get_3D_Output_Mode() == E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF)
            {
                pstXC_SetWin_Info->stDispWin.width =
                    (MS_U32)pstXC_SetWin_Info->stCropWin.width * g_IPanel.Height() / (pstXC_SetWin_Info->stCropWin.height * 2);
                pstXC_SetWin_Info->stDispWin.height = g_IPanel.Height();
                //need use x+=, because main and sub's y will be different and specified at outside
                pstXC_SetWin_Info->stDispWin.x += (g_IPanel.Width() - pstXC_SetWin_Info->stDispWin.width * 2) / 4;
                pstXC_SetWin_Info->stDispWin.y = 0;
            }
            else if(MApi_XC_Get_3D_Panel_Type() != E_XC_3D_PANEL_NONE)//we don't want none-3D case fall into here
            {
                pstXC_SetWin_Info->stDispWin.width =
                    (MS_U32)pstXC_SetWin_Info->stCropWin.width * g_IPanel.Height() / pstXC_SetWin_Info->stCropWin.height;
                pstXC_SetWin_Info->stDispWin.height = g_IPanel.Height();
                pstXC_SetWin_Info->stDispWin.x = (g_IPanel.Width() - pstXC_SetWin_Info->stDispWin.width) / 2;
                pstXC_SetWin_Info->stDispWin.y = 0;
            }
        }
        else
        {
            if(MApi_XC_Get_3D_Output_Mode() == E_XC_3D_OUTPUT_TOP_BOTTOM)
            {
                pstXC_SetWin_Info->stDispWin.height = (MS_U32)g_IPanel.Width() * pstXC_SetWin_Info->stCropWin.height / (pstXC_SetWin_Info->stCropWin.width * 2);
                pstXC_SetWin_Info->stDispWin.y += (g_IPanel.Height() - pstXC_SetWin_Info->stDispWin.height * 2) / 4;
                pstXC_SetWin_Info->stDispWin.width = g_IPanel.Width();
                pstXC_SetWin_Info->stDispWin.x = 0;
            }
            else if(MApi_XC_Get_3D_Output_Mode() == E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF)
            {
                pstXC_SetWin_Info->stDispWin.height = (MS_U32)g_IPanel.Width() * pstXC_SetWin_Info->stCropWin.height / pstXC_SetWin_Info->stCropWin.width;
                pstXC_SetWin_Info->stDispWin.width = g_IPanel.Width() / 2;
                pstXC_SetWin_Info->stDispWin.y = (g_IPanel.Height() - pstXC_SetWin_Info->stDispWin.height) / 2;
            }
            else if(MApi_XC_Get_3D_Panel_Type() != E_XC_3D_PANEL_NONE)//we don't want none-3D case fall into here
            {
                pstXC_SetWin_Info->stDispWin.height = (MS_U32)g_IPanel.Width() * pstXC_SetWin_Info->stCropWin.height / pstXC_SetWin_Info->stCropWin.width;
                pstXC_SetWin_Info->stDispWin.width = g_IPanel.Width();
                pstXC_SetWin_Info->stDispWin.y = (g_IPanel.Height() - pstXC_SetWin_Info->stDispWin.height) / 2;
                pstXC_SetWin_Info->stDispWin.x = 0;
            }
        }
    }
    else if(en3DARCType == VIDEOSCREEN_3D_CENTER)
    {
        if(MApi_XC_Get_3D_Output_Mode() == E_XC_3D_OUTPUT_TOP_BOTTOM)
        {
            if(pstXC_SetWin_Info->stCropWin.width <= g_IPanel.Width())
            {
                pstXC_SetWin_Info->stDispWin.x = (g_IPanel.Width() - pstXC_SetWin_Info->stCropWin.width) / 2;
                pstXC_SetWin_Info->stDispWin.width = pstXC_SetWin_Info->stCropWin.width;
            }
            else
            {
                pstXC_SetWin_Info->stDispWin.x = 0;
                pstXC_SetWin_Info->stDispWin.width = g_IPanel.Width();
            }

            if(pstXC_SetWin_Info->stCropWin.height <= g_IPanel.Height())
            {
                pstXC_SetWin_Info->stDispWin.y += (g_IPanel.Height() - pstXC_SetWin_Info->stCropWin.height) / (2 * 2);
                pstXC_SetWin_Info->stDispWin.height = pstXC_SetWin_Info->stCropWin.height / 2;
            }
            else
            {
                pstXC_SetWin_Info->stDispWin.y = 0;
                pstXC_SetWin_Info->stDispWin.height = g_IPanel.Height() / 2;
            }
        }
        else if(MApi_XC_Get_3D_Output_Mode() == E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF)
        {
            if(pstXC_SetWin_Info->stCropWin.width <= g_IPanel.Width())
            {
                pstXC_SetWin_Info->stDispWin.x += (g_IPanel.Width() - pstXC_SetWin_Info->stCropWin.width) / (2 * 2);
            }

            if(pstXC_SetWin_Info->stCropWin.height <= g_IPanel.Height())
            {
                pstXC_SetWin_Info->stDispWin.y = (g_IPanel.Height() - pstXC_SetWin_Info->stCropWin.height) / 2;
            }
            else
            {
                pstXC_SetWin_Info->stDispWin.y = 0;
            }

            pstXC_SetWin_Info->stDispWin.width = pstXC_SetWin_Info->stCropWin.width / 2;
            pstXC_SetWin_Info->stDispWin.height = pstXC_SetWin_Info->stCropWin.height;
        }
        else if(MApi_XC_Get_3D_Panel_Type() != E_XC_3D_PANEL_NONE)//we don't want none-3D case fall into here
        {
            if(pstXC_SetWin_Info->stCropWin.width <= g_IPanel.Width())
            {
                pstXC_SetWin_Info->stDispWin.x = (g_IPanel.Width() - pstXC_SetWin_Info->stCropWin.width) / 2;
            }
            else
            {
                pstXC_SetWin_Info->stDispWin.x = 0;
            }

            if(pstXC_SetWin_Info->stCropWin.height <= g_IPanel.Height())
            {
                pstXC_SetWin_Info->stDispWin.y = (g_IPanel.Height() - pstXC_SetWin_Info->stCropWin.height) / 2;
            }
            else
            {
                pstXC_SetWin_Info->stDispWin.y = 0;
            }
            pstXC_SetWin_Info->stDispWin.width = pstXC_SetWin_Info->stCropWin.width;
            pstXC_SetWin_Info->stDispWin.height = pstXC_SetWin_Info->stCropWin.height;
        }
    }

    if(MApi_XC_Get_3D_HW_Version() == 0)
    {
        if((((MApi_XC_Get_3D_Input_Mode(eWindow) == E_XC_3D_INPUT_TOP_BOTTOM)
        ||(MApi_XC_Get_3D_Input_Mode(eWindow) == E_XC_3D_INPUT_NORMAL_2D_INTERLACE_PTP))
            && (MApi_XC_Get_3D_Output_Mode() == E_XC_3D_OUTPUT_LINE_ALTERNATIVE)) ||
           ((MApi_XC_Get_3D_Input_Mode(eWindow) == E_XC_3D_INPUT_MODE_NONE)
            && (MApi_XC_Get_3D_Output_Mode() == E_XC_3D_OUTPUT_MODE_NONE)
            && (MApi_XC_Get_3D_Panel_Type() != E_XC_3D_PANEL_NONE)))
        {
            pstXC_SetWin_Info->stCapWin.y += MApi_XC_Get_3D_VerVideoOffset();
            pstXC_SetWin_Info->stCapWin.height -= 2 * MApi_XC_Get_3D_VerVideoOffset();
            pstXC_SetWin_Info->stCropWin.height = pstXC_SetWin_Info->stCapWin.height;
            //E_XC_3D_INPUT_TOP_BOTTOM cannot scale up, because the line count should be same with the input.
            //so here keep original size with input.
            if(g_IPanel.Width() > pstXC_SetWin_Info->stCapWin.width)
            {
                pstXC_SetWin_Info->stDispWin.x = (g_IPanel.Width()-pstXC_SetWin_Info->stCapWin.width)/2;
                pstXC_SetWin_Info->stDispWin.width = pstXC_SetWin_Info->stCapWin.width;
            }
            else
            {
                pstXC_SetWin_Info->stDispWin.x = 0;
                pstXC_SetWin_Info->stDispWin.width = g_IPanel.Width();
            }

            if(g_IPanel.Height() > (pstXC_SetWin_Info->stCapWin.height))
            {
                pstXC_SetWin_Info->stDispWin.y = (g_IPanel.Height()-pstXC_SetWin_Info->stCapWin.height)/2;
                pstXC_SetWin_Info->stDispWin.height = (pstXC_SetWin_Info->stCapWin.height);
            }
            else
            {
                pstXC_SetWin_Info->stDispWin.y = 0;
                pstXC_SetWin_Info->stDispWin.height = g_IPanel.Height();
            }
            if(pstXC_SetWin_Info->stDispWin.width > g_IPanel.Width())
            {
                pstXC_SetWin_Info->stDispWin.width = g_IPanel.Width();
            }
            if(pstXC_SetWin_Info->stDispWin.height > g_IPanel.Height())
            {
                pstXC_SetWin_Info->stDispWin.height = g_IPanel.Height();
            }
            MENU_3D_DBG(printf("3D: E_XC_3D_INPUT_TOP_BOTTOM only support centering and point-to-point\n");)
        }
        else if(((MApi_XC_Get_3D_Input_Mode(eWindow) == E_XC_3D_INPUT_SIDE_BY_SIDE_HALF)
                || (MApi_XC_Get_3D_Input_Mode(eWindow) == E_XC_3D_INPUT_SIDE_BY_SIDE_HALF_INTERLACE)
                || (MApi_XC_Get_3D_Input_Mode(eWindow) == E_XC_3D_INPUT_NORMAL_2D)
                || (MApi_XC_Get_3D_Input_Mode(eWindow) == E_XC_3D_INPUT_NORMAL_2D_INTERLACE)
                || (MApi_XC_Get_3D_Input_Mode(MAIN_WINDOW) == E_XC_3D_INPUT_FRAME_ALTERNATIVE))
                && (MApi_XC_Get_3D_Output_Mode() == E_XC_3D_OUTPUT_LINE_ALTERNATIVE))
        {
            //in E_XC_3D_INPUT_SIDE_BY_SIDE_HALF case:
            //if source v size >=540, we can pre-scale down to 540 and finally show as 1920*1080.
            //if source v size <540, we have to do only double v,h size, and center.
            if((en3DARCType == VIDEOSCREEN_3D_FULL) || (en3DARCType == VIDEOSCREEN_3D_AUTO))
            {
                if(pstXC_SetWin_Info->stCapWin.height < 1080/2)
                {
                    MENU_3D_DBG(printf("3D: E_XC_3D_INPUT_SIDE_BY_SIDE_HALF expand mode(720p to fullscreen, 480p to double size)\n");)
                    if(g_IPanel.Width() >= pstXC_SetWin_Info->stCapWin.width*2)
                    {
                        pstXC_SetWin_Info->stDispWin.x = (g_IPanel.Width()-pstXC_SetWin_Info->stCapWin.width*2)/2;
                        pstXC_SetWin_Info->stDispWin.width = pstXC_SetWin_Info->stCapWin.width*2;
                    }
                    else
                    {
                        MENU_3D_DBG(printf("3D: source width(%u) is too long case, special handler\n",pstXC_SetWin_Info->stCapWin.width);)
                        pstXC_SetWin_Info->stDispWin.x = (g_IPanel.Width()-pstXC_SetWin_Info->stCapWin.width)/2;
                        pstXC_SetWin_Info->stDispWin.width = pstXC_SetWin_Info->stCapWin.width;
                    }
                    pstXC_SetWin_Info->stDispWin.y =  (g_IPanel.Height()-pstXC_SetWin_Info->stCapWin.height*2)/2;
                    pstXC_SetWin_Info->stDispWin.height = pstXC_SetWin_Info->stCapWin.height*2;

                    //tDstWin.width must be less than panel width, otherwise 1440*576 case will be bad.
                    if (pstXC_SetWin_Info->stDispWin.width > g_IPanel.Width())
                    {
                        MENU_3D_DBG(printf("3D: tDstWin.width(%u) is too big, set to panel width\n", pstXC_SetWin_Info->stDispWin.width);)
                        pstXC_SetWin_Info->stDispWin.width = g_IPanel.Width();
                    }
                }
                else{
                    pstXC_SetWin_Info->stDispWin.x = 0;
                    pstXC_SetWin_Info->stDispWin.y = 0;
                    pstXC_SetWin_Info->stDispWin.width = g_IPanel.Width();
                    pstXC_SetWin_Info->stDispWin.height = g_IPanel.Height();
                }
            }
            pstXC_SetWin_Info->stCapWin.y += MApi_XC_Get_3D_VerVideoOffset();
            pstXC_SetWin_Info->stCapWin.height -= 2 * MApi_XC_Get_3D_VerVideoOffset();
            pstXC_SetWin_Info->stCropWin.height = pstXC_SetWin_Info->stCapWin.height;
        }
    }

    if(MApi_XC_Get_3D_Panel_Type() != E_XC_3D_PANEL_NONE)
    {
        if(pstXC_SetWin_Info->stDispWin.width > g_IPanel.Width())
        {
            pstXC_SetWin_Info->stDispWin.width = g_IPanel.Width();
        }
        if(pstXC_SetWin_Info->stDispWin.height > g_IPanel.Height())
        {
            pstXC_SetWin_Info->stDispWin.height = g_IPanel.Height();
        }
    }

    MENU_3D_DBG(printf("3D: after _AdjustIndividualDisplayWin: (%u,%u,%u,%u)\n", pstXC_SetWin_Info->stDispWin.x,
            pstXC_SetWin_Info->stDispWin.y, pstXC_SetWin_Info->stDispWin.width, pstXC_SetWin_Info->stDispWin.height);)
}
static void MApp_3D_AdjustWholeDisplayWin(XC_SETWIN_INFO *pstXC_SetWin_Info, SCALER_WIN eWindow, EN_ASPECT_RATIO_TYPE en3DARCType)
{
    MENU_3D_DBG(printf("3D: before _AdjustWholeDisplayWin: (%u,%u,%u,%u)\n", pstXC_SetWin_Info->stDispWin.x,
            pstXC_SetWin_Info->stDispWin.y, pstXC_SetWin_Info->stDispWin.width, pstXC_SetWin_Info->stDispWin.height);)

    if((MApi_XC_Get_3D_Panel_Type() != E_XC_3D_PANEL_NONE)
       && (MApi_XC_Get_3D_Input_Mode(eWindow) != E_XC_3D_INPUT_FRAME_PACKING))
    {
        if(en3DARCType == VIDEOSCREEN_3D_CENTER)
        {
            pstXC_SetWin_Info->stDispWin.width = pstXC_SetWin_Info->stCropWin.width;
            pstXC_SetWin_Info->stDispWin.height = pstXC_SetWin_Info->stCropWin.height;
        }
        else if(en3DARCType == VIDEOSCREEN_3D_AUTO)
        {
            if((MS_U32)g_IPanel.Width() * pstXC_SetWin_Info->stCropWin.height > (MS_U32)g_IPanel.Height() * pstXC_SetWin_Info->stCropWin.width)
            {
                pstXC_SetWin_Info->stDispWin.width =
                    (MS_U32)pstXC_SetWin_Info->stCropWin.width * g_IPanel.Height() / pstXC_SetWin_Info->stCropWin.height;
                pstXC_SetWin_Info->stDispWin.height = g_IPanel.Height();
            }
            else
            {
                pstXC_SetWin_Info->stDispWin.width = g_IPanel.Width();
                pstXC_SetWin_Info->stDispWin.height = (MS_U32)g_IPanel.Width() * pstXC_SetWin_Info->stCropWin.height / pstXC_SetWin_Info->stCropWin.width;
            }
        }
        if(pstXC_SetWin_Info->stDispWin.width > g_IPanel.Width())
        {
            pstXC_SetWin_Info->stDispWin.width = g_IPanel.Width();
        }
        if(pstXC_SetWin_Info->stDispWin.height > g_IPanel.Height())
        {
            pstXC_SetWin_Info->stDispWin.height = g_IPanel.Height();
        }
    }

    MENU_3D_DBG(printf("3D: after _AdjustWholeDisplayWin: (%u,%u,%u,%u)\n", pstXC_SetWin_Info->stDispWin.x,
                pstXC_SetWin_Info->stDispWin.y, pstXC_SetWin_Info->stDispWin.width, pstXC_SetWin_Info->stDispWin.height);)
}
void MApp_Scaler_Adjust3DDisplayWin(XC_SETWIN_INFO *pstXC_SetWin_Info, SCALER_WIN eWindow, EN_ASPECT_RATIO_TYPE en3DARCType)
{
    if((MApi_XC_Get_3D_HW_Version() < 2) ||
       ((MApi_XC_Get_3D_Output_Mode() != E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF)
        && (MApi_XC_Get_3D_Output_Mode() != E_XC_3D_OUTPUT_TOP_BOTTOM)))
    {
        MApp_3D_AdjustIndividualDisplayWin(pstXC_SetWin_Info, eWindow, en3DARCType);
    }
    else
    {
        MApp_3D_AdjustWholeDisplayWin(pstXC_SetWin_Info, eWindow, en3DARCType);
    }
}

void MApp_Scaler_EnableManualDetectTiming(BOOLEAN bEnable)
{
    DEBUG_3D( printf("MApp_Scaler_EnableManualDetectTiming(bEnable=%u)\n", bEnable); );
    _bManualDetectTiming = bEnable;
}

BOOLEAN MApp_Scaler_IsManualDetectTiming(void)
{
    return _bManualDetectTiming;
}

E_XC_3D_INPUT_MODE MAPP_Scaler_MapUI3DModeToXCInput3DMode(EN_3D_TYPE eInputUI3DType)
{
    E_XC_3D_INPUT_MODE eInput3DMode;

    DEBUG_3D( printf("MAPP_Scaler_MapUI3DModeToXCInput3DMode(eInputUI3DType=%u)\n", eInputUI3DType); );

    if(eInputUI3DType == EN_3D_FRAME_PACKING)
    {
        eInput3DMode = E_XC_3D_INPUT_FRAME_PACKING;
    }
    else if(eInputUI3DType == EN_3D_SIDE_BY_SIDE)
    {
        eInput3DMode = E_XC_3D_INPUT_SIDE_BY_SIDE_HALF;
    }
    else if(eInputUI3DType == EN_3D_TOP_BOTTOM)
    {
        eInput3DMode = E_XC_3D_INPUT_TOP_BOTTOM;
    }
    else if(eInputUI3DType == EN_3D_LINE_ALTERNATIVE)
    {
        eInput3DMode = E_XC_3D_INPUT_LINE_ALTERNATIVE;
    }
    else if(eInputUI3DType == EN_3D_BYPASS)
    {
        eInput3DMode = E_XC_3D_INPUT_MODE_NONE;
    }
    else if(eInputUI3DType == EN_3D_2DConvertTo3D)
    {
#ifdef SCALER_2DTO3D_DD_BUF_ADR
        if(MApi_XC_Get_3D_IsSupportedHW2DTo3D())
        {
            eInput3DMode = E_XC_3D_INPUT_NORMAL_2D_HW;
        }
        else
#endif
        {
            eInput3DMode = E_XC_3D_INPUT_NORMAL_2D;
        }
    }
    else if(eInputUI3DType == EN_3D_FRAME_ALTERNATIVE)
    {
        eInput3DMode = E_XC_3D_INPUT_FRAME_ALTERNATIVE;
    }
    else
    {
        eInput3DMode = E_XC_3D_INPUT_MODE_NONE;
    }

    DEBUG_3D( printf(" => eInput3DMode=%u\n", eInput3DMode); );

    return eInput3DMode;
}

E_XC_3D_OUTPUT_MODE MAPP_Scaler_MapUI3DModeToXCOutput3DMode(EN_3D_TYPE eOutputUI3DType)
{
    E_XC_3D_OUTPUT_MODE eOutput3DMode;

    DEBUG_3D( printf("MAPP_Scaler_MapUI3DModeToXCOutput3DMode(eInputUI3DType=%u)\n", eOutputUI3DType); );

    if(eOutputUI3DType == EN_3D_SIDE_BY_SIDE)
    {
        eOutput3DMode = E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF;
    }
    else if(eOutputUI3DType == EN_3D_TOP_BOTTOM)
    {
        eOutput3DMode = E_XC_3D_OUTPUT_TOP_BOTTOM;
    }
    else if(eOutputUI3DType == EN_3D_LINE_ALTERNATIVE)
    {
        eOutput3DMode = E_XC_3D_OUTPUT_LINE_ALTERNATIVE;
    }
    else if(eOutputUI3DType == EN_3D_BYPASS)
    {
        eOutput3DMode = E_XC_3D_OUTPUT_MODE_NONE;
    }
    else if(eOutputUI3DType == EN_3D_2DConvertTo3D)
    {
#ifdef SCALER_2DTO3D_DD_BUF_ADR
        if(MApi_XC_Get_3D_IsSupportedHW2DTo3D())
        {
            eOutput3DMode = E_XC_3D_OUTPUT_LINE_ALTERNATIVE_HW;
        }
        else
#endif
        {
            eOutput3DMode = E_XC_3D_OUTPUT_LINE_ALTERNATIVE;
        }
    }
    else if(eOutputUI3DType == EN_3D_FRAME_ALTERNATIVE)
    {
        eOutput3DMode = E_XC_3D_OUTPUT_FRAME_ALTERNATIVE;
    }
    else if(eOutputUI3DType == EN_3D_FRAME_L)
    {
        eOutput3DMode = E_XC_3D_OUTPUT_FRAME_L;
    }
    else
    {
        eOutput3DMode = E_XC_3D_OUTPUT_MODE_NONE;
    }

    DEBUG_3D( printf(" => eOutput3DMode=%u\n", eOutput3DMode); );

    return eOutput3DMode;
}

EN_3D_TYPE MAPP_Scaler_MapXC3DModeToUI3DMode(E_XC_3D_INPUT_MODE eInput3DMode)
{
    EN_3D_TYPE eInputUI3DType;

    switch(eInput3DMode)
    {
         case  E_XC_3D_INPUT_FRAME_PACKING:
                eInputUI3DType=EN_3D_FRAME_PACKING;
                break;
         case  E_XC_3D_INPUT_SIDE_BY_SIDE_HALF:
                eInputUI3DType=EN_3D_SIDE_BY_SIDE;
                break;
         case  E_XC_3D_INPUT_TOP_BOTTOM:
                eInputUI3DType=EN_3D_TOP_BOTTOM;
                break;
         case  E_XC_3D_INPUT_LINE_ALTERNATIVE:
                eInputUI3DType=EN_3D_LINE_ALTERNATIVE;
                break;
         case  E_XC_3D_INPUT_NORMAL_2D_HW:
         case  E_XC_3D_INPUT_NORMAL_2D:
                eInputUI3DType=EN_3D_2DConvertTo3D;
                break;
         case  E_XC_3D_INPUT_FRAME_ALTERNATIVE:
                eInputUI3DType=EN_3D_FRAME_ALTERNATIVE;
                break;
         case  E_XC_3D_INPUT_MODE_NONE:
         default:
                eInputUI3DType=EN_3D_BYPASS;
                break;
    }

    return eInputUI3DType;
}

MS_BOOL MApi_Scaler_Set3DInfo(E_XC_3D_INPUT_MODE enInMode,E_XC_3D_OUTPUT_MODE enOutMode)
{
    DEBUG_3D( printf("MApi_Scaler_Set3DInfo(enInMode=%u, enOutMode=%u)\n", enInMode, enOutMode); );

    m_st3DInfo.enInput3DMode = enInMode;
    m_st3DInfo.enOutput3DMode = enOutMode;
    return TRUE;
}

BOOL MAPP_Scaler_MapUIDetectMode(EN_3D_DETECT_MODE eDetect3DMode)
{
    BOOL bAutoDetect = FALSE;

    if(eDetect3DMode == EN_3D_DETECT_AUTO)
    {
        bAutoDetect = TRUE;
    }
    else
    {
        bAutoDetect = FALSE;
    }
    return bAutoDetect;
}

U16 MAPP_Scaler_Map3DFormatTo3DUserMode(E_XC_3D_INPUT_MODE eInput3DFormat)
{
    U16 u16User3DMode = E_USER_3D_MODE_OFF;

    DEBUG_3D( printf("MAPP_Scaler_Map3DFormatTo3DUserMode(eInput3DFormat=%u(%s))\n", eInput3DFormat, MApp_Scaler_Get_Xc3DInputName(eInput3DFormat)); );

#if (ENABLE_MFC_6M20 || ENABLE_MFC_6M30)
    U16 u16H = MApp_PCMode_Get_HResolution(MAIN_WINDOW,FALSE);
    if(eInput3DFormat == E_XC_3D_INPUT_FRAME_PACKING)
    {
        if(u16H> 1270 && u16H < 1290)
        {
            u16User3DMode = E_USER_3D_MODE_FRAME_PACKING_2_LINE_ALTERNATIVE;
            MApi_Scaler_Set3DInfo(eInput3DFormat, E_XC_3D_OUTPUT_LINE_ALTERNATIVE);
        }
        else
        {
            u16User3DMode = E_USER_3D_MODE_FRAME_PACKING_2_FRAME_ALTERNATIVE;
            MApi_Scaler_Set3DInfo(eInput3DFormat, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE);
        }
    }
    else if(eInput3DFormat == E_XC_3D_INPUT_SIDE_BY_SIDE_HALF)
    {
        u16User3DMode = E_USER_3D_MODE_OFF;
    }
    else if(eInput3DFormat == E_XC_3D_INPUT_TOP_BOTTOM)
    {
        u16User3DMode = E_USER_3D_MODE_OFF;
    }
    else if(eInput3DFormat == E_XC_3D_INPUT_LINE_ALTERNATIVE)
    {
        u16User3DMode = E_USER_3D_MODE_OFF;
    }
    else if(eInput3DFormat == E_XC_3D_INPUT_NORMAL_2D)
    {
        u16User3DMode = E_USER_3D_MODE_OFF;
    }
    else if(eInput3DFormat == E_XC_3D_INPUT_NORMAL_2D_HW)
    {
        u16User3DMode = E_USER_3D_MODE_NORMAL_2D_HW_2_LINE_ALTERNATIVE_HW;
        MApi_Scaler_Set3DInfo(eInput3DFormat, E_XC_3D_OUTPUT_LINE_ALTERNATIVE_HW);
    }
    else if(eInput3DFormat == E_XC_3D_INPUT_FRAME_ALTERNATIVE)
    {
        u16User3DMode = E_USER_3D_MODE_OFF;
    }
    else
    {
        u16User3DMode = E_USER_3D_MODE_OFF;
    }
#elif(ENABLE_6M40_4KX2K_PROCESS || ENABLE_6M50_4KX2K_PROCESS)
    U16 u16H = MApp_PCMode_Get_HResolution(MAIN_WINDOW,FALSE);
    if(eInput3DFormat == E_XC_3D_INPUT_FRAME_PACKING)
    {
        if(u16H> 1270 && u16H < 1290)
        {
            u16User3DMode = E_USER_3D_MODE_FRAME_PACKING_2_TOP_BOTTOM;
            MApi_Scaler_Set3DInfo(eInput3DFormat, E_XC_3D_OUTPUT_TOP_BOTTOM);
        }
        else
        {
            u16User3DMode = E_USER_3D_MODE_FRAME_PACKING_2_FRAME_ALTERNATIVE;
            MApi_Scaler_Set3DInfo(eInput3DFormat, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE);
        }
    }
    else if(eInput3DFormat == E_XC_3D_INPUT_SIDE_BY_SIDE_HALF)
    {
        u16User3DMode = E_USER_3D_MODE_OFF;
    }
    else if(eInput3DFormat == E_XC_3D_INPUT_TOP_BOTTOM)
    {
        u16User3DMode = E_USER_3D_MODE_OFF;
    }
    else if(eInput3DFormat == E_XC_3D_INPUT_LINE_ALTERNATIVE)
    {
        u16User3DMode = E_USER_3D_MODE_OFF;
    }
    else if(eInput3DFormat == E_XC_3D_INPUT_NORMAL_2D)
    {
        u16User3DMode = E_USER_3D_MODE_OFF;
    }
    else if(eInput3DFormat == E_XC_3D_INPUT_NORMAL_2D_HW)
    {
        u16User3DMode = E_USER_3D_MODE_NORMAL_2D_HW_2_LINE_ALTERNATIVE_HW;
        MApi_Scaler_Set3DInfo(eInput3DFormat, E_XC_3D_OUTPUT_LINE_ALTERNATIVE_HW);
    }
    else if(eInput3DFormat == E_XC_3D_INPUT_FRAME_ALTERNATIVE)
    {
        u16User3DMode = E_USER_3D_MODE_OFF;
    }
    else
    {
        u16User3DMode = E_USER_3D_MODE_OFF;
    }
#else
    if(eInput3DFormat == E_XC_3D_INPUT_FRAME_PACKING)
    {
         u16User3DMode = E_USER_3D_MODE_FRAME_PACKING_2_LINE_ALTERNATIVE;
         MApi_Scaler_Set3DInfo(eInput3DFormat, E_XC_3D_OUTPUT_LINE_ALTERNATIVE);
    }
    else if(eInput3DFormat == E_XC_3D_INPUT_SIDE_BY_SIDE_HALF)
    {
        u16User3DMode = E_USER_3D_MODE_SIDE_BY_SIDE_HALF_2_LINE_ALTERNATIVE;
        MApi_Scaler_Set3DInfo(eInput3DFormat, E_XC_3D_OUTPUT_LINE_ALTERNATIVE);
    }
    else if(eInput3DFormat == E_XC_3D_INPUT_TOP_BOTTOM)
    {
        u16User3DMode = E_USER_3D_MODE_TOP_BOTTOM_2_LINE_ALTERNATIVE;
        MApi_Scaler_Set3DInfo(eInput3DFormat, E_XC_3D_OUTPUT_LINE_ALTERNATIVE);
    }
    else if(eInput3DFormat == E_XC_3D_INPUT_LINE_ALTERNATIVE)
    {
        u16User3DMode = E_USER_3D_MODE_LINE_ALTERNATIVE_2_LINE_ALTERNATIVE;
        MApi_Scaler_Set3DInfo(eInput3DFormat, E_XC_3D_OUTPUT_LINE_ALTERNATIVE);
    }
    else if(eInput3DFormat == E_XC_3D_INPUT_NORMAL_2D)
    {
        u16User3DMode = E_USER_3D_MODE_NORMAL_2D_2_LINE_ALTERNATIVE;
        MApi_Scaler_Set3DInfo(eInput3DFormat, E_XC_3D_OUTPUT_LINE_ALTERNATIVE);
    }
    else if(eInput3DFormat == E_XC_3D_INPUT_NORMAL_2D_HW)
    {
        u16User3DMode = E_USER_3D_MODE_NORMAL_2D_HW_2_LINE_ALTERNATIVE_HW;
        MApi_Scaler_Set3DInfo(eInput3DFormat, E_XC_3D_OUTPUT_LINE_ALTERNATIVE_HW);
    }
    else if(eInput3DFormat == E_XC_3D_INPUT_FRAME_ALTERNATIVE)
    {
        u16User3DMode = E_USER_3D_MODE_FRAME_ALTERNATIVE_2_LINE_ALTERNATIVE;
        MApi_Scaler_Set3DInfo(eInput3DFormat, E_XC_3D_OUTPUT_LINE_ALTERNATIVE);
    }
    else
    {
        u16User3DMode = E_USER_3D_MODE_OFF;
        MApi_Scaler_Set3DInfo(eInput3DFormat,E_XC_3D_OUTPUT_MODE_NONE);
    }
#endif


    DEBUG_3D( printf(" => u16User3DMode=%u\n", u16User3DMode); );

    return u16User3DMode;
}

BOOL MApp_Scaler_3D_IsSrcTypeSupport3DFunction(void)
{
    if( MApi_XC_IsCurrentFrameBufferLessMode() )
    {
        //PRINT_CURRENT_LINE();
        return FALSE;
    }

#if 0
    // DTV support 3D??
  #if (MHEG5_ENABLE)
    if( (msAPI_MHEG5_IsRunning())
      &&(( msAPI_MHEG5_IsIFrameExist() || !g_MHEG5Video.bHaveVideo)||(!msAPI_MHEG5_VID_IsFullScreen(&g_MHEG5Video.stMHEG5VideoAction)))
      )
    {
        if( enInput3DType != EN_3D_BYPASS && enInput3DType != EN_3D_2DConvertTo3D)
        {
            enInput3DType = EN_3D_BYPASS;
        }
    }
  #endif
#endif

    if( IsHDMIInUse()
      ||IsVgaInUse()
   #if (ENABLE_FORCE_MM_HD_FB)
      ||IsStorageInUse()
   #endif
      )
    {
        //PRINT_CURRENT_LINE();
        return TRUE;
    }

    return FALSE;
}

#if ENABLE_NEW_3D_FLOW
void MApp_Scaler_3D_ResetForChangeTiming(void)
{
    MApp_Scaler_EnableManualDetectTiming(FALSE);

    //MApp_Scaler_Set_3DMode(E_XC_3D_INPUT_MODE_NONE);
    MApp_Scaler_3D_Config(SCLAER_3D_CFG_FOR_FORCE_2D); // For change timing
}

void MApp_Scaler_3D_ResetForChangeSrc(void)
{
    MApp_Scaler_3D_ResetForChangeTiming();

    //MApp_Scaler_EnableManualDetectTiming(FALSE);
    //MApp_Scaler_Set_3DMode(E_XC_3D_INPUT_MODE_NONE);
}

void MApp_Scaler_3D_Config(EnuScaler3DConfigCase eScaler3DConfigCase)
{
    DEBUG_3D( printf("MApp_Scaler_3D_Config(eScaler3DConfigCase=%u)\n", eScaler3DConfigCase ); );

    DEBUG_3D( printf("MApi_XC_Get_3D_HW_Version()=%u\n", MApi_XC_Get_3D_HW_Version() ); );


    // Get cur signal 3D flag
    //BOOL MApp_Scaler_Is_InputSignal3D(void)
    DEBUG_3D( printf("g_HdmiInput3DFormatStatus=%u(%s))\n", g_HdmiInput3DFormatStatus, MApp_Scaler_Get_Xc3DInputName(g_HdmiInput3DFormatStatus)); );

    // Get User setting
    DEBUG_3D( printf("DB_3D_SETTING.en3DType =%u(%s))\n", DB_3D_SETTING.en3DType, MApp_Scaler_Get_Ui3DTypeName(DB_3D_SETTING.en3DType)); );


    EN_3D_TYPE enInput3DType = EN_3D_BYPASS;
    EN_3D_TYPE enOutput3DType = EN_3D_BYPASS;
    EN_3D_TYPE enBackendInput3DType = EN_3D_BYPASS;
    EN_4K2K_OUTPUT_RESOLUTION_TYPE enResolutionType = E_OUTPUT_RESOLUTION_1920X1080;

    // If input source support 3D function
    if( SCLAER_3D_CFG_FOR_FORCE_2D == eScaler3DConfigCase )
    {
        enInput3DType = EN_3D_BYPASS;
    }
    else
    {
        if( MApp_Scaler_3D_IsSrcTypeSupport3DFunction() )
        {
            if( _bManualDetectTiming ) // User force 3D mode
            {
                enInput3DType = DB_3D_SETTING.en3DType;
            }
            else
            {
                if( IsHDMIInUse() )
                {
                    enInput3DType = MAPP_Scaler_MapXC3DModeToUI3DMode(g_HdmiInput3DFormatStatus);
                    if( DB_3D_SETTING.en3DType != enInput3DType )
                    {
                        printf("Change DB_3D_SETTING.en3DType=%u(%s) by HDMI pkt\n", enInput3DType, MApp_Scaler_Get_Ui3DTypeName(enInput3DType));
                        DB_3D_SETTING.en3DType = enInput3DType;
                    }
                }
            }

            //enInput3DType = DB_3D_SETTING.en3DType;
        }
    }

    DEBUG_3D( printf("enInput3DType=%u(%s)\n", enInput3DType, MApp_Scaler_Get_Ui3DTypeName(enInput3DType)); );

    if( MApp_Scaler_3D_GetOutputConfiguration(enInput3DType, &enOutput3DType, &enBackendInput3DType, &enResolutionType) == TRUE )
    {
        DEBUG_3D( printf("enOutput3DType=%u(%s)\n", enOutput3DType, MApp_Scaler_Get_Ui3DTypeName(enOutput3DType)); );

        E_XC_3D_INPUT_MODE eXC_3D_INPUT_MODE = MAPP_Scaler_MapUI3DModeToXCInput3DMode(enInput3DType);
        E_XC_3D_OUTPUT_MODE eXC_3D_OUTPUT_MODE = MAPP_Scaler_MapUI3DModeToXCOutput3DMode(enOutput3DType);

        DEBUG_3D( printf("eXC_3D_INPUT_MODE=%u(%s)\n", eXC_3D_INPUT_MODE, MApp_Scaler_Get_Xc3DInputName(eXC_3D_INPUT_MODE) ); );
        DEBUG_3D( printf("eXC_3D_OUTPUT_MODE=%u(%s)\n", eXC_3D_OUTPUT_MODE, MApp_Scaler_Get_Xc3DOutputName(eXC_3D_OUTPUT_MODE)); );

        if(enOutput3DType == EN_3D_BYPASS)  //2D
        {
            DEBUG_3D( printf("Output 3D off\n"); );
            Set_3D_OFF();

            MApi_XC_Set_3D_Mode(eXC_3D_INPUT_MODE, eXC_3D_OUTPUT_MODE, E_XC_3D_PANEL_NONE, MAIN_WINDOW);
            MApi_XC_Set_3D_Mode(eXC_3D_INPUT_MODE, eXC_3D_OUTPUT_MODE, E_XC_3D_PANEL_NONE, SUB_WINDOW);
        }
        else // 3D
        {
            DEBUG_3D( printf("Output 3D On\n"); );
            Set_3D_ON();

            MApi_XC_Set_3D_Mode(eXC_3D_INPUT_MODE, eXC_3D_OUTPUT_MODE, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
            MApi_XC_Set_3D_Mode(eXC_3D_INPUT_MODE, eXC_3D_OUTPUT_MODE, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
        }

        MApp_Scaler_3D_SetPanelTiming_ByResolution(enResolutionType, enBackendInput3DType);
    }
    else
    {
        printf("\nMApp_Scaler_3D_GetOutputConfiguration() failed!\n");
    }

}

#else
E_XC_3D_OUTPUT_MODE MApp_Set_3DOutputMode(U16 u16_Video3Dmode)
{
    E_XC_3D_OUTPUT_MODE Output3DTmp = E_XC_3D_OUTPUT_LINE_ALTERNATIVE;
    if(MApi_XC_Get_3D_HW_Version()<2)
    {
        switch(u16_Video3Dmode)
        {
            case E_USER_3D_MODE_FRAME_PACKING_2_LINE_ALTERNATIVE:
            case E_USER_3D_MODE_SIDE_BY_SIDE_HALF_2_LINE_ALTERNATIVE:
            case E_USER_3D_MODE_SIDE_BY_SIDE_HALF_INTERLACE_2_LINE_ALTERNATIVE:
            case E_USER_3D_MODE_LINE_ALTERNATIVE_2_LINE_ALTERNATIVE:
            case E_USER_3D_MODE_TOP_BOTTOM_2_LINE_ALTERNATIVE:
            case E_USER_3D_MODE_FRAME_ALTERNATIVE_2_LINE_ALTERNATIVE:
            case E_USER_3D_MODE_NORMAL_2D_2_LINE_ALTERNATIVE:
            {
                Output3DTmp = E_XC_3D_OUTPUT_TOP_BOTTOM;
            }
                 break;

        }
    }
    return Output3DTmp;
}
#endif

#if ENABLE_NEW_3D_FLOW
BOOLEAN MApp_Scaler_SetVideo3DMode(EN_3D_TYPE eUi3DType)
{
    eUi3DType=eUi3DType;

    //EN_3D_TYPE enInput3DType = EN_3D_BYPASS;
    EN_3D_TYPE enOutput3DType = EN_3D_BYPASS;
    //EN_3D_TYPE enBackendInput3DType = EN_3D_BYPASS;
    //EN_4K2K_OUTPUT_RESOLUTION_TYPE enResolutionType = E_OUTPUT_RESOLUTION_1920X1080;

    //XC_ApiStatus stXCApiStatus;


    DEBUG_3D( printf("MApp_Scaler_SetVideo3DMode(eUi3DType=%u(%s))\n", eUi3DType, MApp_Scaler_Get_Ui3DTypeName(eUi3DType)); );

    if( FALSE == MApp_Scaler_3D_IsSrcTypeSupport3DFunction()
      ||(FALSE == MApp_IsSrcHasSignal(MAIN_WINDOW))
      )
    {
        printf("\nWarning: Can not support 3D!\n");
        //printf("MApp_Scaler_3D_IsSrcTypeSupport3DFunction()=%u\n", MApp_Scaler_3D_IsSrcTypeSupport3DFunction());
        //printf("MApp_IsSrcHasSignal(MAIN_WINDOW)=%u\n", MApp_IsSrcHasSignal(MAIN_WINDOW));
        return FALSE;
    }

#if 0//(MHEG5_ENABLE)
    if((msAPI_MHEG5_IsRunning())&&(( msAPI_MHEG5_IsIFrameExist() || !g_MHEG5Video.bHaveVideo)||(!msAPI_MHEG5_VID_IsFullScreen(&g_MHEG5Video.stMHEG5VideoAction))))
    {
        if( enInput3DType != EN_3D_BYPASS && enInput3DType != EN_3D_2DConvertTo3D)
        {
            enInput3DType = EN_3D_BYPASS;
        }
    }
#endif

/*
    memset(&stXCApiStatus, 0, sizeof(XC_ApiStatus));
    if (MApi_XC_GetStatus(&stXCApiStatus, MAIN_WINDOW) == FALSE)
    {
        printf("MApi_XC_GetStatus failed.\n");
        return FALSE;
    }
    */

#if 1
    MApp_Scaler_3D_Config(SCLAER_3D_CFG_FOR_AUTO); // at MApp_Scaler_SetVideo3DMode()

#else

    if(MApp_Scaler_3D_GetOutputConfiguration(&enOutput3DType, &enBackendInput3DType, &enResolutionType) == FALSE)
    {
        return FALSE;
    }

    DEBUG_3D( printf("enInput3DType=%u\n", enInput3DType); );
    DEBUG_3D( printf("enOutput3DType=%u\n", enOutput3DType); );

    E_XC_3D_INPUT_MODE eXC_3D_INPUT_MODE = MAPP_Scaler_MapUI3DModeToXCInput3DMode(enInput3DType);
    E_XC_3D_OUTPUT_MODE eXC_3D_OUTPUT_MODE = MAPP_Scaler_MapUI3DModeToXCOutput3DMode(enOutput3DType);

    DEBUG_3D( printf("eXC_3D_INPUT_MODE=%u(%s)\n", eXC_3D_INPUT_MODE, MApp_Scaler_Get_Xc3DInputName(eXC_3D_INPUT_MODE) ); );
    DEBUG_3D( printf("eXC_3D_OUTPUT_MODE=%u\n", eXC_3D_OUTPUT_MODE); );

    if(enOutput3DType == EN_3D_BYPASS)  //2D
    {
        printf("Output 3D off\n");
        Set_3D_OFF();

        MApi_XC_Set_3D_Mode(eXC_3D_INPUT_MODE, eXC_3D_OUTPUT_MODE, E_XC_3D_PANEL_NONE, MAIN_WINDOW);
        MApi_XC_Set_3D_Mode(eXC_3D_INPUT_MODE, eXC_3D_OUTPUT_MODE, E_XC_3D_PANEL_NONE, SUB_WINDOW);
    }
    else
    {
        printf("Output 3D On\n");
        Set_3D_ON();

        MApi_XC_Set_3D_Mode(eXC_3D_INPUT_MODE, eXC_3D_OUTPUT_MODE, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
        MApi_XC_Set_3D_Mode(eXC_3D_INPUT_MODE, eXC_3D_OUTPUT_MODE, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
    }

    MApp_Scaler_3D_SetPanelTiming_ByResolution(enResolutionType, enBackendInput3DType);
#endif


    if(enOutput3DType == EN_3D_2DConvertTo3D)
    {
        MApi_XC_Set_3D_HShift(16);
    }
    else
    {
        MApi_XC_Set_3D_HShift(0); //Default set shift to 0 to avoid Non-2d->3d case use this shift to adjust 3D quality
    }

    //MApp_Scaler_EnableOverScan(TRUE);

    MApp_Scaler_SetWindow(
        NULL,
        NULL,
        NULL,
        stSystemInfo[MAIN_WINDOW].enAspectRatio,
        SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),
        MAIN_WINDOW);

    MApp_Picture_Setting_SetColor(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);


    MApp_Scaler_AutoDisablePQ_UC();

    MApp_Scaler_SetTiming(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);

    if((E_XC_3D_OUTPUT_LINE_ALTERNATIVE == MApi_XC_Get_3D_Output_Mode())
           || (E_XC_3D_OUTPUT_TOP_BOTTOM == MApi_XC_Get_3D_Output_Mode())
           || (E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF == MApi_XC_Get_3D_Output_Mode()))
    {
        MApi_XC_ACE_3DClonePQMap(E_ACE_WEAVETYPE_NONE);

        if(MApi_XC_Get_3D_HW_Version() < 2)
        {
            MApi_XC_DisableInputSource(FALSE, SUB_WINDOW);
            MApi_XC_3DMainSub_IPSync();
        }
        MApi_XC_3D_PostPQSetting(MAIN_WINDOW);
    }

    return TRUE;
}

BOOLEAN MApp_Scaler_Set_3DMode(E_XC_3D_INPUT_MODE eXcInput3DFormat)
{
    EN_3D_TYPE enInput3DType = EN_3D_BYPASS;
    EN_3D_TYPE enOutput3DType = EN_3D_BYPASS;
    EN_3D_TYPE enBackendInput3DType = EN_3D_BYPASS;
    EN_4K2K_OUTPUT_RESOLUTION_TYPE enResolutionType = E_OUTPUT_RESOLUTION_1920X1080;
    //XC_ApiStatus stXCApiStatus;


    DEBUG_3D( printf("MApp_Scaler_Set_3DMode(eXcInput3DFormat=%u(%s))\n", eXcInput3DFormat, MApp_Scaler_Get_Xc3DInputName(eXcInput3DFormat)); );

    enInput3DType = MAPP_Scaler_MapXC3DModeToUI3DMode(eXcInput3DFormat);
    DEBUG_3D( printf("enInput3DType=%u(%s)\n", enInput3DType, MApp_Scaler_Get_Ui3DTypeName(enInput3DType)); );

    //MApi_XC_Set_3D_HShift(0); //Default set shift to 0 to avoid Non-2d->3d case use this shift to adjust 3D quality

/*
    memset(&stXCApiStatus, 0, sizeof(XC_ApiStatus));
    if (MApi_XC_GetStatus(&stXCApiStatus, MAIN_WINDOW) == FALSE)
    {
        printf("MApi_XC_GetStatus failed.\n");
    } */

    if(MApp_Scaler_3D_GetOutputConfiguration(enInput3DType, &enOutput3DType, &enBackendInput3DType, &enResolutionType) == FALSE)
    {
        return FALSE;
    }


    //DEBUG_3D( printf("enOutput3DType=%u\n", enOutput3DType); );

    E_XC_3D_INPUT_MODE eXC_3D_INPUT_MODE = MAPP_Scaler_MapUI3DModeToXCInput3DMode(enInput3DType);
    E_XC_3D_OUTPUT_MODE eXC_3D_OUTPUT_MODE = MAPP_Scaler_MapUI3DModeToXCOutput3DMode(enOutput3DType);

    DEBUG_3D( printf("eXC_3D_INPUT_MODE=%u(%s)\n", eXC_3D_INPUT_MODE, MApp_Scaler_Get_Xc3DInputName(eXC_3D_INPUT_MODE) ); );
    DEBUG_3D( printf("eXC_3D_OUTPUT_MODE=%u\n", eXC_3D_OUTPUT_MODE); );

    if(enOutput3DType == EN_3D_BYPASS)  //2D
    {
        MApi_XC_Set_3D_Mode(eXC_3D_INPUT_MODE, eXC_3D_OUTPUT_MODE, E_XC_3D_PANEL_NONE, MAIN_WINDOW);
        MApi_XC_Set_3D_Mode(eXC_3D_INPUT_MODE, eXC_3D_OUTPUT_MODE, E_XC_3D_PANEL_NONE, SUB_WINDOW);
    }
    else
    {
        MApi_XC_Set_3D_Mode(eXC_3D_INPUT_MODE, eXC_3D_OUTPUT_MODE, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
        MApi_XC_Set_3D_Mode(eXC_3D_INPUT_MODE, eXC_3D_OUTPUT_MODE, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
    }

    //MApp_Scaler_3D_SetPanelTiming_ByResolution(enResolutionType, enBackendInput3DType);

    if(enOutput3DType == EN_3D_2DConvertTo3D)
    {
        MApi_XC_Set_3D_HShift(16);
    }
    else
    {
        MApi_XC_Set_3D_HShift(0); //Default set shift to 0 to avoid Non-2d->3d case use this shift to adjust 3D quality
    }

    MApp_Scaler_AutoDisablePQ_UC();

    return TRUE;
}
#else
BOOLEAN MApp_Scaler_SetVideo3DMode(U16 u16_Video3Dmode)
{
    MENU_3D_DBG(printf("SetVideo3DMode u16_Video3Dmode<<0x%x>>\n", u16_Video3Dmode);)
    if(MApi_XC_IsCurrentFrameBufferLessMode())
    {
         return FALSE;
    }
    MApi_XC_Set_3D_HShift(0); //Default set shift to 0 to avoid Non-2d->3d case use this shift to adjust 3D quality
    E_XC_3D_OUTPUT_MODE Output3DMode;
    Output3DMode = MApp_Set_3DOutputMode(u16_Video3Dmode);
#if (MHEG5_ENABLE)
    if((msAPI_MHEG5_IsRunning())&&(( msAPI_MHEG5_IsIFrameExist() || !g_MHEG5Video.bHaveVideo)||(!msAPI_MHEG5_VID_IsFullScreen(&g_MHEG5Video.stMHEG5VideoAction))))
    {
        if( u16_Video3Dmode != E_USER_3D_MODE_OFF && u16_Video3Dmode != E_USER_3D_MODE_NORMAL_2D_HW_2_LINE_ALTERNATIVE_HW)
        {
            u16_Video3Dmode = E_USER_3D_MODE_OFF;
        }
    }
#endif
    switch(u16_Video3Dmode)
    {
        case E_USER_3D_MODE_80:
        {
            MENU_3D_DBG(printf("******************************Usage Note******************************\n");)
            MENU_3D_DBG(printf("[0x00]3D:Close 3D\n");)

            MENU_3D_DBG(printf("[0x01]3D: Begin 3D. FRAME_PACKING ===> LINE_ALTERNATIVE\n");)
            MENU_3D_DBG(printf("[0x02]3D: Begin 3D. SIDE_BY_SIDE_HALF ===> LINE_ALTERNATIVE\n");)
            MENU_3D_DBG(printf("[0x03]3D: Begin 3D. Vertical LINE_ALTERNATIVE to Vertical LINE_ALTERNATIVE\n");)
            MENU_3D_DBG(printf("[0x04]3D: Begin 3D. LINE_ALTERNATIVE ===> LINE_ALTERNATIVE\n");)
            MENU_3D_DBG(printf("[0x05]3D: Begin 3D. SIDE_BY_SIDE_HALF_INTERLACE ===> LINE_ALTERNATIVE\n");)

            MENU_3D_DBG(printf("[0x11]3D: Begin 3D. LINE_ALTERNATIVE ====> TOP_BOTTOM\n");)
            MENU_3D_DBG(printf("[0x12]3D: Begin 3D. TOP_BOTTOM ====> TOP_BOTTOM\n");)
            MENU_3D_DBG(printf("[0x13]3D: Begin 3D. FRAME_ALTERNATIVE ====> TOP_BOTTOM\n");)
            MENU_3D_DBG(printf("[0x14]3D: Begin 3D. SIDE_BY_SIDE_HALF ====> SIDE_BY_SIDE_HALF\n");)
            MENU_3D_DBG(printf("[0x15]3D: Begin 3D. FRAME_PACKING ====> FRAME_ALTERNATIVE\n");)
            MENU_3D_DBG(printf("*********************************************************************\n");)
        }
            break;
        //2D
        case E_USER_3D_MODE_OFF:

        //vertical line alternative output
        case E_USER_3D_MODE_VERTICAL_LINE_ALTERNATIVE_2_VERTICAL_LINE_ALTERNATIVE:

        //line alternative output
        case E_USER_3D_MODE_FRAME_PACKING_2_LINE_ALTERNATIVE:
        case E_USER_3D_MODE_SIDE_BY_SIDE_HALF_2_LINE_ALTERNATIVE:
        case E_USER_3D_MODE_SIDE_BY_SIDE_HALF_INTERLACE_2_LINE_ALTERNATIVE:
        case E_USER_3D_MODE_LINE_ALTERNATIVE_2_LINE_ALTERNATIVE:
        case E_USER_3D_MODE_TOP_BOTTOM_2_LINE_ALTERNATIVE:
        case E_USER_3D_MODE_FRAME_ALTERNATIVE_2_LINE_ALTERNATIVE:
        case E_USER_3D_MODE_NORMAL_2D_2_LINE_ALTERNATIVE:

        //top bottom output
        case E_USER_3D_MODE_FRAME_PACKING_2_TOP_BOTTOM:
        case E_USER_3D_MODE_TOP_BOTTOM_2_TOP_BOTTOM:
        case E_USER_3D_MODE_FRAME_ALTERNATIVE_2_TOP_BOTTOM:
        case E_USER_3D_MODE_LINE_ALTERNATIVE_2_TOP_BOTTOM:
        case E_USER_3D_MODE_SIDE_BY_SIDE_HALF_2_TOP_BOTTOM:

        //side by side half output
        case E_USER_3D_MODE_LINE_ALTERNATIVE_2_SIDE_BY_SIDE_HALF:
        case E_USER_3D_MODE_SIDE_BY_SIDE_HALF_2_SIDE_BY_SIDE_HALF:
        case E_USER_3D_MODE_FRAME_PACKING_2_SIDE_BY_SIDE_HALF:
        case E_USER_3D_MODE_TOP_BOTTOM_2_SIDE_BY_SIDE_HALF:
        case E_USER_3D_MODE_FRAME_ALTERNATIVE_2_SIDE_BY_SIDE_HALF:

        //frame alternative nofrc output
        case E_USER_3D_MODE_FRAME_PACKING_2_FRAME_ALTERNATIVE_NOFRC:
        case E_USER_3D_MODE_SIDE_BY_SIDE_HALF_2_FRAME_ALTERNATIVE_NOFRC:
        case E_USER_3D_MODE_SIDE_BY_SIDE_HALF_INTERLACE_2_FRAME_ALTERNATIVE_NOFRC:
        case E_USER_3D_MODE_LINE_ALTERNATIVE_2_FRAME_ALTERNATIVE_NOFRC:
        case E_USER_3D_MODE_TOP_BOTTOM_2_FRAME_ALTERNATIVE_NOFRC:
        case E_USER_3D_MODE_NORMAL_2D_2_FRAME_ALTERNATIVE_NOFRC:

        //frame alternative output
        case E_USER_3D_MODE_FRAME_PACKING_2_FRAME_ALTERNATIVE:
        case E_USER_3D_MODE_TOP_BOTTOM_2_FRAME_ALTERNATIVE:
        case E_USER_3D_MODE_SIDE_BY_SIDE_HALF_2_FRAME_ALTERNATIVE:
        case E_USER_3D_MODE_LINE_ALTERNATIVE_2_FRAME_ALTERNATIVE:

        //L only
        case E_USER_3D_MODE_FRAME_PACKING_2_FRAME_L:
        case E_USER_3D_MODE_SIDE_BY_SIDE_HALF_2_FRAME_L:
        case E_USER_3D_MODE_TOP_BOTTOM_2_FRAME_L:
        case E_USER_3D_MODE_FRAME_ALTERNATIVE_2_FRAME_L:
        case E_USER_3D_MODE_LINE_ALTERNATIVE_2_FRAME_L:

        //hw 2d to 3d
        case E_USER_3D_MODE_NORMAL_2D_HW_2_LINE_ALTERNATIVE_HW:
        {
            XC_ApiStatus stXCApiStatus;
            memset(&stXCApiStatus, 0, sizeof(XC_ApiStatus));
            if (MApi_XC_GetStatus(&stXCApiStatus, MAIN_WINDOW) == FALSE)
            {
                printf("MApi_XC_GetStatus failed.\n");
            }

            if(E_USER_3D_MODE_OFF==u16_Video3Dmode)
            {
                //MApp_ZUI_API_Enable3DTwinMode(FALSE);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_MODE_NONE, E_XC_3D_OUTPUT_MODE_NONE, E_XC_3D_PANEL_NONE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_MODE_NONE, E_XC_3D_OUTPUT_MODE_NONE, E_XC_3D_PANEL_NONE, SUB_WINDOW);
                MENU_3D_DBG(printf("\n\n=================================================\n");)
                MENU_3D_DBG(printf("3D:Close 3D\n");)
                MENU_3D_DBG(printf("=================================================\n");)

            }
            else if(E_USER_3D_MODE_FRAME_PACKING_2_LINE_ALTERNATIVE==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_PACKING, Output3DMode, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_PACKING, Output3DMode, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("\n\n=================================================\n");)
                MENU_3D_DBG(printf("3D: Begin 3D. FRAME_PACKING ===> LINE_ALTERNATIVE\n");)
                MENU_3D_DBG(printf("=================================================\n");)
            }
            else if(E_USER_3D_MODE_FRAME_ALTERNATIVE_2_LINE_ALTERNATIVE==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_ALTERNATIVE, Output3DMode, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_ALTERNATIVE, Output3DMode, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("\n\n=================================================\n");)
                MENU_3D_DBG(printf("3D: Begin 3D. FRAME_ALTERNATIVE ===> LINE_ALTERNATIVE\n");)
                MENU_3D_DBG(printf("=================================================\n");)
            }
            else if(E_USER_3D_MODE_SIDE_BY_SIDE_HALF_2_LINE_ALTERNATIVE==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_SIDE_BY_SIDE_HALF, Output3DMode, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_SIDE_BY_SIDE_HALF, Output3DMode, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("\n\n=================================================\n");)
                MENU_3D_DBG(printf("3D: Begin 3D. SIDE_BY_SIDE_HALF ===> LINE_ALTERNATIVE\n");)
                MENU_3D_DBG(printf("=================================================\n");)
            }
            else if(E_USER_3D_MODE_VERTICAL_LINE_ALTERNATIVE_2_VERTICAL_LINE_ALTERNATIVE==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_MODE_NONE, E_XC_3D_OUTPUT_MODE_NONE, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_MODE_NONE, E_XC_3D_OUTPUT_MODE_NONE, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("\n\n=================================================\n");)
                MENU_3D_DBG(printf("3D: Begin 3D. ByPassMode\n");)
                MENU_3D_DBG(printf("=================================================\n");)
            }
            else if(E_USER_3D_MODE_LINE_ALTERNATIVE_2_LINE_ALTERNATIVE==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_LINE_ALTERNATIVE, Output3DMode, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_LINE_ALTERNATIVE, Output3DMode, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("\n\n=================================================\n");)
                MENU_3D_DBG(printf("3D: Begin 3D. LINE_ALTERNATIVE ===> LINE_ALTERNATIVE\n");)
                MENU_3D_DBG(printf("=================================================\n");)
            }
            else if(E_USER_3D_MODE_LINE_ALTERNATIVE_2_SIDE_BY_SIDE_HALF==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_LINE_ALTERNATIVE, E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_LINE_ALTERNATIVE, E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("\n\n=================================================\n");)
                MENU_3D_DBG(printf("3D: Begin 3D. LINE_ALTERNATIVE ===> SIDE_BY_SIDE_HALF\n");)
                MENU_3D_DBG(printf("=================================================\n");)
            }
            else if(E_USER_3D_MODE_TOP_BOTTOM_2_SIDE_BY_SIDE_HALF==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_TOP_BOTTOM, E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_TOP_BOTTOM, E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("\n\n=================================================\n");)
                MENU_3D_DBG(printf("3D: Begin 3D. TOP_BOTTOM ===> SIDE_BY_SIDE_HALF\n");)
                MENU_3D_DBG(printf("=================================================\n");)
            }
            else if(E_USER_3D_MODE_FRAME_ALTERNATIVE_2_SIDE_BY_SIDE_HALF==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_ALTERNATIVE, E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_ALTERNATIVE, E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("\n\n=================================================\n");)
                MENU_3D_DBG(printf("3D: Begin 3D. FRAME_ALTERNATIVE ===> SIDE_BY_SIDE_HALF\n");)
                MENU_3D_DBG(printf("=================================================\n");)
            }
            else if(E_USER_3D_MODE_SIDE_BY_SIDE_HALF_INTERLACE_2_LINE_ALTERNATIVE==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_SIDE_BY_SIDE_HALF_INTERLACE, Output3DMode, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_SIDE_BY_SIDE_HALF_INTERLACE, Output3DMode, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("\n\n=================================================\n");)
                MENU_3D_DBG(printf("3D: Begin 3D. SIDE_BY_SIDE_HALF_INTERLACE ===> LINE_ALTERNATIVE\n");)
                MENU_3D_DBG(printf("=================================================\n");)
            }
            else  if(E_USER_3D_MODE_FRAME_PACKING_2_FRAME_ALTERNATIVE_NOFRC==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_PACKING, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE_NOFRC, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_PACKING, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE_NOFRC, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. FRAME_PACKING ====> FRAME_ALTERNATIVE_NOFRC\n");)
            }
            else  if(E_USER_3D_MODE_TOP_BOTTOM_2_FRAME_ALTERNATIVE_NOFRC==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_TOP_BOTTOM, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE_NOFRC, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_TOP_BOTTOM, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE_NOFRC, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. TOP_BOTTOM ====> FRAME_ALTERNATIVE_NOFRC\n");)
            }
            else  if(E_USER_3D_MODE_SIDE_BY_SIDE_HALF_2_FRAME_ALTERNATIVE_NOFRC==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_SIDE_BY_SIDE_HALF, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE_NOFRC, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_SIDE_BY_SIDE_HALF, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE_NOFRC, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. SIDE_BY_SIDE_HALF ====> FRAME_ALTERNATIVE_NOFRC\n");)
            }
            else  if(E_USER_3D_MODE_LINE_ALTERNATIVE_2_FRAME_ALTERNATIVE_NOFRC==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_LINE_ALTERNATIVE, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE_NOFRC, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_LINE_ALTERNATIVE, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE_NOFRC, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. LINE_ALTERNATIVE ====> FRAME_ALTERNATIVE_NOFRC\n");)
            }
            else  if(E_USER_3D_MODE_FRAME_PACKING_2_FRAME_ALTERNATIVE==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_PACKING, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_PACKING, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. FRAME_PACKING ====> FRAME_ALTERNATIVE\n");)
            }
            else  if(E_USER_3D_MODE_TOP_BOTTOM_2_FRAME_ALTERNATIVE==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_TOP_BOTTOM, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_TOP_BOTTOM, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. TOP_BOTTOM ====> FRAME_ALTERNATIVE\n");)
            }
            else  if(E_USER_3D_MODE_SIDE_BY_SIDE_HALF_2_FRAME_ALTERNATIVE==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_SIDE_BY_SIDE_HALF, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_SIDE_BY_SIDE_HALF, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. SIDE_BY_SIDE_HALF ====> FRAME_ALTERNATIVE\n");)
            }
            else  if(E_USER_3D_MODE_LINE_ALTERNATIVE_2_FRAME_ALTERNATIVE==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_LINE_ALTERNATIVE, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_LINE_ALTERNATIVE, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. LINE_ALTERNATIVE ====> FRAME_ALTERNATIVE\n");)
            }
            else  if(E_USER_3D_MODE_FRAME_PACKING_2_FRAME_L==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_PACKING, E_XC_3D_OUTPUT_FRAME_L, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_PACKING, E_XC_3D_OUTPUT_FRAME_L, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. FRAME_PACKING ====> FRAME_L\n");)
            }
            else  if(E_USER_3D_MODE_SIDE_BY_SIDE_HALF_2_FRAME_L==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_SIDE_BY_SIDE_HALF, E_XC_3D_OUTPUT_FRAME_L, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_SIDE_BY_SIDE_HALF, E_XC_3D_OUTPUT_FRAME_L, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. FRAME_PACKING ====> FRAME_L\n");)
            }
            else  if(E_USER_3D_MODE_TOP_BOTTOM_2_FRAME_L==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_TOP_BOTTOM, E_XC_3D_OUTPUT_FRAME_L, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_TOP_BOTTOM, E_XC_3D_OUTPUT_FRAME_L, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. FRAME_PACKING ====> FRAME_L\n");)
            }
            else  if(E_USER_3D_MODE_FRAME_ALTERNATIVE_2_FRAME_L==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_ALTERNATIVE, E_XC_3D_OUTPUT_FRAME_L, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_ALTERNATIVE, E_XC_3D_OUTPUT_FRAME_L, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. FRAME_ALTERNATIVE ====> FRAME_L\n");)
            }
            else  if(E_USER_3D_MODE_LINE_ALTERNATIVE_2_FRAME_L==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_LINE_ALTERNATIVE, E_XC_3D_OUTPUT_FRAME_L, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_LINE_ALTERNATIVE, E_XC_3D_OUTPUT_FRAME_L, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. LINE_ALTERNATIVE ====> FRAME_L\n");)
            }
            else if(E_USER_3D_MODE_SIDE_BY_SIDE_HALF_INTERLACE_2_FRAME_ALTERNATIVE_NOFRC==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_SIDE_BY_SIDE_HALF_INTERLACE, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE_NOFRC, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_SIDE_BY_SIDE_HALF_INTERLACE, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE_NOFRC, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. SIDE_BY_SIDE_HALF_INTERLACE ====> FRAME_ALTERNATIVE_NOFRC\n");)
            }
            else if(E_USER_3D_MODE_FRAME_PACKING_2_TOP_BOTTOM==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_PACKING, E_XC_3D_OUTPUT_TOP_BOTTOM, E_XC_3D_PANEL_SHUTTER, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_PACKING, E_XC_3D_OUTPUT_TOP_BOTTOM, E_XC_3D_PANEL_SHUTTER, SUB_WINDOW);
                //MAPI_XC_Set_3D_MainSub_FirstMode(FALSE);
                //MApi_XC_SetFrameBufferAddress(((SCALER_DNR_BUF_MEMORY_TYPE & MIU1) ? (SCALER_DNR_BUF_ADR | MIU_INTERVAL) : (SCALER_DNR_BUF_ADR)), SCALER_DNR_BUF_LEN, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. FRAME_PACKING ====> TOP_BOTTOM\n");)
            }
            else if(E_USER_3D_MODE_TOP_BOTTOM_2_TOP_BOTTOM==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_TOP_BOTTOM, E_XC_3D_OUTPUT_TOP_BOTTOM, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_TOP_BOTTOM, E_XC_3D_OUTPUT_TOP_BOTTOM, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                //MApi_XC_SetFrameBufferAddress(((SCALER_DNR_BUF_MEMORY_TYPE & MIU1) ? (SCALER_DNR_BUF_ADR | MIU_INTERVAL) : (SCALER_DNR_BUF_ADR)), SCALER_DNR_BUF_LEN, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. TOP_BOTTOM ====> TOP_BOTTOM\n");)
            }
            else  if(E_USER_3D_MODE_FRAME_ALTERNATIVE_2_TOP_BOTTOM==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_ALTERNATIVE, E_XC_3D_OUTPUT_TOP_BOTTOM, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_ALTERNATIVE, E_XC_3D_OUTPUT_TOP_BOTTOM, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. FRAME_ALTERNATIVE ====> TOP_BOTTOM\n");)
            }
            else  if(E_USER_3D_MODE_LINE_ALTERNATIVE_2_TOP_BOTTOM==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_LINE_ALTERNATIVE, E_XC_3D_OUTPUT_TOP_BOTTOM, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_LINE_ALTERNATIVE, E_XC_3D_OUTPUT_TOP_BOTTOM, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. LINE_ALTERNATIVE ====> TOP_BOTTOM\n");)
            }
            else  if(E_USER_3D_MODE_SIDE_BY_SIDE_HALF_2_TOP_BOTTOM==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_SIDE_BY_SIDE_HALF, E_XC_3D_OUTPUT_TOP_BOTTOM, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_SIDE_BY_SIDE_HALF, E_XC_3D_OUTPUT_TOP_BOTTOM, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. SIDE_BY_SIDE_HALF ====> TOP_BOTTOM\n");)
            }
            else  if(E_USER_3D_MODE_SIDE_BY_SIDE_HALF_2_SIDE_BY_SIDE_HALF==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_SIDE_BY_SIDE_HALF, E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_SIDE_BY_SIDE_HALF, E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. SIDE_BY_SIDE_HALF ====> SIDE_BY_SIDE_HALF\n");)
            }
            else if(E_USER_3D_MODE_FRAME_PACKING_2_SIDE_BY_SIDE_HALF==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_PACKING, E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF, E_XC_3D_PANEL_SHUTTER, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_PACKING, E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF, E_XC_3D_PANEL_SHUTTER, SUB_WINDOW);
                //MAPI_XC_Set_3D_MainSub_FirstMode(FALSE);
                //MApi_XC_SetFrameBufferAddress(((SCALER_DNR_BUF_MEMORY_TYPE & MIU1) ? (SCALER_DNR_BUF_ADR | MIU_INTERVAL) : (SCALER_DNR_BUF_ADR)), SCALER_DNR_BUF_LEN, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. FRAME_PACKING ====> Side_By_Side\n");)
            }
            else if(E_USER_3D_MODE_TOP_BOTTOM_2_LINE_ALTERNATIVE==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_TOP_BOTTOM, Output3DMode, E_XC_3D_PANEL_SHUTTER, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_TOP_BOTTOM, Output3DMode, E_XC_3D_PANEL_SHUTTER, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. TOP_BOTTOM ====> LINE_ALTERNATIVE\n");)
            }
            else if(E_USER_3D_MODE_NORMAL_2D_2_LINE_ALTERNATIVE==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_HShift(16);

                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_NORMAL_2D, Output3DMode, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_NORMAL_2D, Output3DMode, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D: Begin 3D. NORMAL_2D ===> LINE_ALTERNATIVE\n");)
            }
            else if(E_USER_3D_MODE_NORMAL_2D_2_FRAME_ALTERNATIVE_NOFRC==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_HShift(16);

                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_NORMAL_2D, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE_NOFRC, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_NORMAL_2D, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE_NOFRC, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D: Begin 3D. NORMAL_2D ===> FRAME_ALTERNATIVE\n");)
            }
#ifdef SCALER_2DTO3D_DD_BUF_ADR
            else if(E_USER_3D_MODE_NORMAL_2D_HW_2_LINE_ALTERNATIVE_HW==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_HW2DTo3D_Buffer(((SCALER_2DTO3D_DD_BUF_MEMORY_TYPE&MIU1?SCALER_2DTO3D_DD_BUF_ADR|MIU_INTERVAL:SCALER_2DTO3D_DD_BUF_ADR)),((SCALER_2DTO3D_DR_BUF_MEMORY_TYPE&MIU1)?SCALER_2DTO3D_DR_BUF_ADR|MIU_INTERVAL:SCALER_2DTO3D_DR_BUF_ADR));
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_NORMAL_2D_HW, E_XC_3D_OUTPUT_LINE_ALTERNATIVE_HW, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_MODE_NONE, E_XC_3D_OUTPUT_LINE_ALTERNATIVE_HW, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D: Begin 3D. NORMAL_2D_HW ===> LINE_ALTERNATIVE\n");)
            }
#endif
        //MApp_Scaler_EnableOverScan(TRUE);

        if(ST_VIDEO.eAspectRatio != EN_AspectRatio_Original && ST_VIDEO.eAspectRatio != EN_AspectRatio_16X9 && ST_VIDEO.eAspectRatio != EN_AspectRatio_JustScan)
        {
            ST_VIDEO.eAspectRatio = EN_AspectRatio_16X9;
        }

        stSystemInfo[MAIN_WINDOW].enAspectRatio = MApp_Scaler_GetAspectRatio(MAIN_WINDOW, ST_VIDEO.eAspectRatio );
             MApp_Scaler_SetWindow(
                NULL,
                NULL,
                NULL,
                stSystemInfo[MAIN_WINDOW].enAspectRatio,
                SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),
                MAIN_WINDOW);

            MApp_Picture_Setting_SetColor(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);

            MApp_Scaler_AutoDisablePQ_UC();

            MApp_Scaler_SetTiming(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);

            if((E_XC_3D_OUTPUT_LINE_ALTERNATIVE == MApi_XC_Get_3D_Output_Mode())
                   || (E_XC_3D_OUTPUT_TOP_BOTTOM == MApi_XC_Get_3D_Output_Mode())
                   || (E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF == MApi_XC_Get_3D_Output_Mode()))
            {
                MApi_XC_ACE_3DClonePQMap(E_ACE_WEAVETYPE_NONE);

                if(MApi_XC_Get_3D_HW_Version() < 2)
                {
                    MApi_XC_DisableInputSource(FALSE, SUB_WINDOW);
                    MApi_XC_3DMainSub_IPSync();
                }
                MApi_XC_3D_PostPQSetting(MAIN_WINDOW);
            }
        }
            break;

        default:
            break;
    }

    return FALSE;
}

BOOLEAN MApp_Scaler_Set_3DMode(U16 u16_Video3Dmode)
{
    E_XC_3D_OUTPUT_MODE Output3DMode;

    DEBUG_3D( printf("MApp_Scaler_Set_3DMode( u16_Video3Dmode=%u )\n", u16_Video3Dmode); );

    MApi_XC_Set_3D_HShift(0); //Default set shift to 0 to avoid Non-2d->3d case use this shift to adjust 3D quality

    Output3DMode = MApp_Set_3DOutputMode(u16_Video3Dmode);
    switch(u16_Video3Dmode)
    {
        case E_USER_3D_MODE_80:
        {
            MENU_3D_DBG(printf("******************************Usage Note******************************\n");)
            MENU_3D_DBG(printf("[0x00]3D:Close 3D\n");)

            MENU_3D_DBG(printf("[0x01]3D: Begin 3D. FRAME_PACKING ===> LINE_ALTERNATIVE\n");)
            MENU_3D_DBG(printf("[0x02]3D: Begin 3D. SIDE_BY_SIDE_HALF ===> LINE_ALTERNATIVE\n");)
            MENU_3D_DBG(printf("[0x03]3D: Begin 3D. Vertical LINE_ALTERNATIVE to Vertical LINE_ALTERNATIVE\n");)
            MENU_3D_DBG(printf("[0x04]3D: Begin 3D. LINE_ALTERNATIVE ===> LINE_ALTERNATIVE\n");)
            MENU_3D_DBG(printf("[0x05]3D: Begin 3D. SIDE_BY_SIDE_HALF_INTERLACE ===> LINE_ALTERNATIVE\n");)

            MENU_3D_DBG(printf("[0x11]3D: Begin 3D. LINE_ALTERNATIVE ====> TOP_BOTTOM\n");)
            MENU_3D_DBG(printf("[0x12]3D: Begin 3D. TOP_BOTTOM ====> TOP_BOTTOM\n");)
            MENU_3D_DBG(printf("[0x13]3D: Begin 3D. FRAME_ALTERNATIVE ====> TOP_BOTTOM\n");)
            MENU_3D_DBG(printf("[0x14]3D: Begin 3D. SIDE_BY_SIDE_HALF ====> SIDE_BY_SIDE_HALF\n");)
            MENU_3D_DBG(printf("[0x15]3D: Begin 3D. FRAME_PACKING ====> FRAME_ALTERNATIVE\n");)
            MENU_3D_DBG(printf("*********************************************************************\n");)
        }
            break;
        //2D
        case E_USER_3D_MODE_OFF:

        //vertical line alternative output
        case E_USER_3D_MODE_VERTICAL_LINE_ALTERNATIVE_2_VERTICAL_LINE_ALTERNATIVE:

        //line alternative output
        case E_USER_3D_MODE_FRAME_PACKING_2_LINE_ALTERNATIVE:
        case E_USER_3D_MODE_SIDE_BY_SIDE_HALF_2_LINE_ALTERNATIVE:
        case E_USER_3D_MODE_SIDE_BY_SIDE_HALF_INTERLACE_2_LINE_ALTERNATIVE:
        case E_USER_3D_MODE_LINE_ALTERNATIVE_2_LINE_ALTERNATIVE:
        case E_USER_3D_MODE_TOP_BOTTOM_2_LINE_ALTERNATIVE:
        case E_USER_3D_MODE_FRAME_ALTERNATIVE_2_LINE_ALTERNATIVE:
        case E_USER_3D_MODE_NORMAL_2D_2_LINE_ALTERNATIVE:

        //top bottom output
        case E_USER_3D_MODE_FRAME_PACKING_2_TOP_BOTTOM:
        case E_USER_3D_MODE_TOP_BOTTOM_2_TOP_BOTTOM:
        case E_USER_3D_MODE_FRAME_ALTERNATIVE_2_TOP_BOTTOM:
        case E_USER_3D_MODE_LINE_ALTERNATIVE_2_TOP_BOTTOM:
        case E_USER_3D_MODE_SIDE_BY_SIDE_HALF_2_TOP_BOTTOM:

        //side by side half output
        case E_USER_3D_MODE_LINE_ALTERNATIVE_2_SIDE_BY_SIDE_HALF:
        case E_USER_3D_MODE_SIDE_BY_SIDE_HALF_2_SIDE_BY_SIDE_HALF:
        case E_USER_3D_MODE_FRAME_PACKING_2_SIDE_BY_SIDE_HALF:
        case E_USER_3D_MODE_TOP_BOTTOM_2_SIDE_BY_SIDE_HALF:
        case E_USER_3D_MODE_FRAME_ALTERNATIVE_2_SIDE_BY_SIDE_HALF:

        //frame alternative nofrc output
        case E_USER_3D_MODE_FRAME_PACKING_2_FRAME_ALTERNATIVE_NOFRC:
        case E_USER_3D_MODE_SIDE_BY_SIDE_HALF_2_FRAME_ALTERNATIVE_NOFRC:
        case E_USER_3D_MODE_SIDE_BY_SIDE_HALF_INTERLACE_2_FRAME_ALTERNATIVE_NOFRC:
        case E_USER_3D_MODE_LINE_ALTERNATIVE_2_FRAME_ALTERNATIVE_NOFRC:
        case E_USER_3D_MODE_TOP_BOTTOM_2_FRAME_ALTERNATIVE_NOFRC:
        case E_USER_3D_MODE_NORMAL_2D_2_FRAME_ALTERNATIVE_NOFRC:

        //frame alternative output
        case E_USER_3D_MODE_FRAME_PACKING_2_FRAME_ALTERNATIVE:
        case E_USER_3D_MODE_TOP_BOTTOM_2_FRAME_ALTERNATIVE:
        case E_USER_3D_MODE_SIDE_BY_SIDE_HALF_2_FRAME_ALTERNATIVE:
        case E_USER_3D_MODE_LINE_ALTERNATIVE_2_FRAME_ALTERNATIVE:

        //L only
        case E_USER_3D_MODE_FRAME_PACKING_2_FRAME_L:
        case E_USER_3D_MODE_SIDE_BY_SIDE_HALF_2_FRAME_L:
        case E_USER_3D_MODE_TOP_BOTTOM_2_FRAME_L:
        case E_USER_3D_MODE_FRAME_ALTERNATIVE_2_FRAME_L:
        case E_USER_3D_MODE_LINE_ALTERNATIVE_2_FRAME_L:

        //hw 2d to 3d
        case E_USER_3D_MODE_NORMAL_2D_HW_2_LINE_ALTERNATIVE_HW:
        {
            XC_ApiStatus stXCApiStatus;
            memset(&stXCApiStatus, 0, sizeof(XC_ApiStatus));
            if (MApi_XC_GetStatus(&stXCApiStatus, MAIN_WINDOW) == FALSE)
            {
                printf("MApi_XC_GetStatus failed.\n");
            }

            if(E_USER_3D_MODE_OFF==u16_Video3Dmode)
            {
                //MApp_ZUI_API_Enable3DTwinMode(FALSE);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_MODE_NONE, E_XC_3D_OUTPUT_MODE_NONE, E_XC_3D_PANEL_NONE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_MODE_NONE, E_XC_3D_OUTPUT_MODE_NONE, E_XC_3D_PANEL_NONE, SUB_WINDOW);
                MENU_3D_DBG(printf("\n\n=================================================\n");)
                MENU_3D_DBG(printf("3D:Close 3D\n");)
                MENU_3D_DBG(printf("=================================================\n");)

            }
            else if(E_USER_3D_MODE_FRAME_PACKING_2_LINE_ALTERNATIVE==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_PACKING, Output3DMode, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_PACKING, Output3DMode, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("\n\n=================================================\n");)
                MENU_3D_DBG(printf("3D: Begin 3D. FRAME_PACKING ===> LINE_ALTERNATIVE\n");)
                MENU_3D_DBG(printf("=================================================\n");)
            }
            else if(E_USER_3D_MODE_FRAME_ALTERNATIVE_2_LINE_ALTERNATIVE==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_ALTERNATIVE, Output3DMode, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_ALTERNATIVE, Output3DMode, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("\n\n=================================================\n");)
                MENU_3D_DBG(printf("3D: Begin 3D. FRAME_ALTERNATIVE ===> LINE_ALTERNATIVE\n");)
                MENU_3D_DBG(printf("=================================================\n");)
            }
            else if(E_USER_3D_MODE_SIDE_BY_SIDE_HALF_2_LINE_ALTERNATIVE==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_SIDE_BY_SIDE_HALF, Output3DMode, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_SIDE_BY_SIDE_HALF, Output3DMode, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("\n\n=================================================\n");)
                MENU_3D_DBG(printf("3D: Begin 3D. SIDE_BY_SIDE_HALF ===> LINE_ALTERNATIVE\n");)
                MENU_3D_DBG(printf("=================================================\n");)
            }
            else if(E_USER_3D_MODE_VERTICAL_LINE_ALTERNATIVE_2_VERTICAL_LINE_ALTERNATIVE==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_MODE_NONE, E_XC_3D_OUTPUT_MODE_NONE, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_MODE_NONE, E_XC_3D_OUTPUT_MODE_NONE, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("\n\n=================================================\n");)
                MENU_3D_DBG(printf("3D: Begin 3D. ByPassMode\n");)
                MENU_3D_DBG(printf("=================================================\n");)
            }
            else if(E_USER_3D_MODE_LINE_ALTERNATIVE_2_LINE_ALTERNATIVE==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_LINE_ALTERNATIVE, Output3DMode, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_LINE_ALTERNATIVE, Output3DMode, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("\n\n=================================================\n");)
                MENU_3D_DBG(printf("3D: Begin 3D. LINE_ALTERNATIVE ===> LINE_ALTERNATIVE\n");)
                MENU_3D_DBG(printf("=================================================\n");)
            }
            else if(E_USER_3D_MODE_LINE_ALTERNATIVE_2_SIDE_BY_SIDE_HALF==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_LINE_ALTERNATIVE, E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_LINE_ALTERNATIVE, E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("\n\n=================================================\n");)
                MENU_3D_DBG(printf("3D: Begin 3D. LINE_ALTERNATIVE ===> SIDE_BY_SIDE_HALF\n");)
                MENU_3D_DBG(printf("=================================================\n");)
            }
            else if(E_USER_3D_MODE_TOP_BOTTOM_2_SIDE_BY_SIDE_HALF==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_TOP_BOTTOM, E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_TOP_BOTTOM, E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("\n\n=================================================\n");)
                MENU_3D_DBG(printf("3D: Begin 3D. TOP_BOTTOM ===> SIDE_BY_SIDE_HALF\n");)
                MENU_3D_DBG(printf("=================================================\n");)
            }
            else if(E_USER_3D_MODE_FRAME_ALTERNATIVE_2_SIDE_BY_SIDE_HALF==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_ALTERNATIVE, E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_ALTERNATIVE, E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("\n\n=================================================\n");)
                MENU_3D_DBG(printf("3D: Begin 3D. FRAME_ALTERNATIVE ===> SIDE_BY_SIDE_HALF\n");)
                MENU_3D_DBG(printf("=================================================\n");)
            }
            else if(E_USER_3D_MODE_SIDE_BY_SIDE_HALF_INTERLACE_2_LINE_ALTERNATIVE==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_SIDE_BY_SIDE_HALF_INTERLACE, Output3DMode, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_SIDE_BY_SIDE_HALF_INTERLACE, Output3DMode, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("\n\n=================================================\n");)
                MENU_3D_DBG(printf("3D: Begin 3D. SIDE_BY_SIDE_HALF_INTERLACE ===> LINE_ALTERNATIVE\n");)
                MENU_3D_DBG(printf("=================================================\n");)
            }
            else  if(E_USER_3D_MODE_FRAME_PACKING_2_FRAME_ALTERNATIVE_NOFRC==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_PACKING, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE_NOFRC, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_PACKING, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE_NOFRC, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. FRAME_PACKING ====> FRAME_ALTERNATIVE_NOFRC\n");)
            }
            else  if(E_USER_3D_MODE_TOP_BOTTOM_2_FRAME_ALTERNATIVE_NOFRC==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_TOP_BOTTOM, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE_NOFRC, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_TOP_BOTTOM, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE_NOFRC, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. TOP_BOTTOM ====> FRAME_ALTERNATIVE_NOFRC\n");)
            }
            else  if(E_USER_3D_MODE_SIDE_BY_SIDE_HALF_2_FRAME_ALTERNATIVE_NOFRC==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_SIDE_BY_SIDE_HALF, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE_NOFRC, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_SIDE_BY_SIDE_HALF, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE_NOFRC, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. SIDE_BY_SIDE_HALF ====> FRAME_ALTERNATIVE_NOFRC\n");)
            }
            else  if(E_USER_3D_MODE_LINE_ALTERNATIVE_2_FRAME_ALTERNATIVE_NOFRC==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_LINE_ALTERNATIVE, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE_NOFRC, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_LINE_ALTERNATIVE, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE_NOFRC, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. LINE_ALTERNATIVE ====> FRAME_ALTERNATIVE_NOFRC\n");)
            }
            else  if(E_USER_3D_MODE_FRAME_PACKING_2_FRAME_ALTERNATIVE==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_PACKING, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_PACKING, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. FRAME_PACKING ====> FRAME_ALTERNATIVE\n");)
            }
            else  if(E_USER_3D_MODE_TOP_BOTTOM_2_FRAME_ALTERNATIVE==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_TOP_BOTTOM, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_TOP_BOTTOM, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. TOP_BOTTOM ====> FRAME_ALTERNATIVE\n");)
            }
            else  if(E_USER_3D_MODE_SIDE_BY_SIDE_HALF_2_FRAME_ALTERNATIVE==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_SIDE_BY_SIDE_HALF, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_SIDE_BY_SIDE_HALF, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. SIDE_BY_SIDE_HALF ====> FRAME_ALTERNATIVE\n");)
            }
            else  if(E_USER_3D_MODE_LINE_ALTERNATIVE_2_FRAME_ALTERNATIVE==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_LINE_ALTERNATIVE, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_LINE_ALTERNATIVE, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. LINE_ALTERNATIVE ====> FRAME_ALTERNATIVE\n");)
            }
            else  if(E_USER_3D_MODE_FRAME_PACKING_2_FRAME_L==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_PACKING, E_XC_3D_OUTPUT_FRAME_L, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_PACKING, E_XC_3D_OUTPUT_FRAME_L, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. FRAME_PACKING ====> FRAME_L\n");)
            }
            else  if(E_USER_3D_MODE_SIDE_BY_SIDE_HALF_2_FRAME_L==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_SIDE_BY_SIDE_HALF, E_XC_3D_OUTPUT_FRAME_L, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_SIDE_BY_SIDE_HALF, E_XC_3D_OUTPUT_FRAME_L, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. FRAME_PACKING ====> FRAME_L\n");)
            }
            else  if(E_USER_3D_MODE_TOP_BOTTOM_2_FRAME_L==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_TOP_BOTTOM, E_XC_3D_OUTPUT_FRAME_L, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_TOP_BOTTOM, E_XC_3D_OUTPUT_FRAME_L, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. FRAME_PACKING ====> FRAME_L\n");)
            }
            else  if(E_USER_3D_MODE_FRAME_ALTERNATIVE_2_FRAME_L==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_ALTERNATIVE, E_XC_3D_OUTPUT_FRAME_L, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_ALTERNATIVE, E_XC_3D_OUTPUT_FRAME_L, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. FRAME_ALTERNATIVE ====> FRAME_L\n");)
            }
            else  if(E_USER_3D_MODE_LINE_ALTERNATIVE_2_FRAME_L==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_LINE_ALTERNATIVE, E_XC_3D_OUTPUT_FRAME_L, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_LINE_ALTERNATIVE, E_XC_3D_OUTPUT_FRAME_L, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. LINE_ALTERNATIVE ====> FRAME_L\n");)
            }
            else if(E_USER_3D_MODE_SIDE_BY_SIDE_HALF_INTERLACE_2_FRAME_ALTERNATIVE_NOFRC==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_SIDE_BY_SIDE_HALF_INTERLACE, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE_NOFRC, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_SIDE_BY_SIDE_HALF_INTERLACE, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE_NOFRC, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. SIDE_BY_SIDE_HALF_INTERLACE ====> FRAME_ALTERNATIVE_NOFRC\n");)
            }
            else if(E_USER_3D_MODE_FRAME_PACKING_2_TOP_BOTTOM==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_PACKING, E_XC_3D_OUTPUT_TOP_BOTTOM, E_XC_3D_PANEL_SHUTTER, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_PACKING, E_XC_3D_OUTPUT_TOP_BOTTOM, E_XC_3D_PANEL_SHUTTER, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. FRAME_PACKING ====> TOP_BOTTOM\n");)
            }
            else if(E_USER_3D_MODE_TOP_BOTTOM_2_TOP_BOTTOM==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_TOP_BOTTOM, E_XC_3D_OUTPUT_TOP_BOTTOM, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_TOP_BOTTOM, E_XC_3D_OUTPUT_TOP_BOTTOM, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. TOP_BOTTOM ====> TOP_BOTTOM\n");)
            }
            else  if(E_USER_3D_MODE_FRAME_ALTERNATIVE_2_TOP_BOTTOM==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_ALTERNATIVE, E_XC_3D_OUTPUT_TOP_BOTTOM, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_ALTERNATIVE, E_XC_3D_OUTPUT_TOP_BOTTOM, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. FRAME_ALTERNATIVE ====> TOP_BOTTOM\n");)
            }
            else  if(E_USER_3D_MODE_LINE_ALTERNATIVE_2_TOP_BOTTOM==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_LINE_ALTERNATIVE, E_XC_3D_OUTPUT_TOP_BOTTOM, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_LINE_ALTERNATIVE, E_XC_3D_OUTPUT_TOP_BOTTOM, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. LINE_ALTERNATIVE ====> TOP_BOTTOM\n");)
            }
            else  if(E_USER_3D_MODE_SIDE_BY_SIDE_HALF_2_TOP_BOTTOM==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_SIDE_BY_SIDE_HALF, E_XC_3D_OUTPUT_TOP_BOTTOM, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_SIDE_BY_SIDE_HALF, E_XC_3D_OUTPUT_TOP_BOTTOM, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. SIDE_BY_SIDE_HALF ====> TOP_BOTTOM\n");)
            }
            else  if(E_USER_3D_MODE_SIDE_BY_SIDE_HALF_2_SIDE_BY_SIDE_HALF==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_SIDE_BY_SIDE_HALF, E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_SIDE_BY_SIDE_HALF, E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. SIDE_BY_SIDE_HALF ====> SIDE_BY_SIDE_HALF\n");)
            }
            else if(E_USER_3D_MODE_FRAME_PACKING_2_SIDE_BY_SIDE_HALF==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_PACKING, E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF, E_XC_3D_PANEL_SHUTTER, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_PACKING, E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF, E_XC_3D_PANEL_SHUTTER, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. FRAME_PACKING ====> Side_By_Side\n");)
            }
            else if(E_USER_3D_MODE_TOP_BOTTOM_2_LINE_ALTERNATIVE==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_TOP_BOTTOM, Output3DMode, E_XC_3D_PANEL_SHUTTER, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_TOP_BOTTOM, Output3DMode, E_XC_3D_PANEL_SHUTTER, SUB_WINDOW);
                MENU_3D_DBG(printf("3D:Begin 3D. TOP_BOTTOM ====> LINE_ALTERNATIVE\n");)
            }
            else if(E_USER_3D_MODE_NORMAL_2D_2_LINE_ALTERNATIVE==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_HShift(16);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_NORMAL_2D, Output3DMode, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_NORMAL_2D, Output3DMode, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D: Begin 3D. NORMAL_2D ===> LINE_ALTERNATIVE\n");)
            }
            else if(E_USER_3D_MODE_NORMAL_2D_2_FRAME_ALTERNATIVE_NOFRC==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_HShift(16);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_NORMAL_2D, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE_NOFRC, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_NORMAL_2D, E_XC_3D_OUTPUT_FRAME_ALTERNATIVE_NOFRC, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D: Begin 3D. NORMAL_2D ===> FRAME_ALTERNATIVE\n");)
            }
#ifdef SCALER_2DTO3D_DD_BUF_ADR
            else if(E_USER_3D_MODE_NORMAL_2D_HW_2_LINE_ALTERNATIVE_HW==u16_Video3Dmode)
            {
                MApi_XC_Set_3D_HW2DTo3D_Buffer(((SCALER_2DTO3D_DD_BUF_MEMORY_TYPE&MIU1?SCALER_2DTO3D_DD_BUF_ADR|MIU_INTERVAL:SCALER_2DTO3D_DD_BUF_ADR)),((SCALER_2DTO3D_DR_BUF_MEMORY_TYPE&MIU1)?SCALER_2DTO3D_DR_BUF_ADR|MIU_INTERVAL:SCALER_2DTO3D_DR_BUF_ADR));

                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_NORMAL_2D_HW, E_XC_3D_OUTPUT_LINE_ALTERNATIVE_HW, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
                MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_MODE_NONE, E_XC_3D_OUTPUT_LINE_ALTERNATIVE_HW, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
                MENU_3D_DBG(printf("3D: Begin 3D. NORMAL_2D_HW ===> LINE_ALTERNATIVE\n");)
            }
#endif

            MApp_Scaler_AutoDisablePQ_UC();

            break;
         }
        default:
            break;
    }
    return FALSE;
}
#endif

#if (ENABLE_MFC_6M20 || ENABLE_MFC_6M30 || ENABLE_6M50_4KX2K_PROCESS)
PANEL_3D_MODE MAPP_Scaler_MapUi3DFormatToUrsa3DMode(EN_3D_TYPE enUi3DType)
{
    PANEL_3D_MODE Ursa3DMode;

    switch(enUi3DType)
    {
        case EN_3D_BYPASS:
            Ursa3DMode = PANEL_3D_MODE_NONE;
            break;
        case EN_3D_FRAME_PACKING:
            Ursa3DMode = PANEL_3D_MODE_FRAME_INTERLEAVE_25X;
            break;
        case EN_3D_SIDE_BY_SIDE:
            Ursa3DMode = PANEL_3D_MODE_SIDE_BY_SIDE_2X;
            break;
        case EN_3D_TOP_BOTTOM:
            Ursa3DMode = PANEL_3D_MODE_TOP_BOTTOM_2X;
            break;
        case EN_3D_LINE_ALTERNATIVE:
            Ursa3DMode = PANEL_3D_MODE_LINE_INTERLEAVED_2X;
            break;
        case EN_3D_FRAME_ALTERNATIVE:
            Ursa3DMode = PANEL_3D_MODE_FRAME_INTERLEAVE_2X;
            break;
        case EN_3D_2DConvertTo3D:
            Ursa3DMode = PANEL_3D_MODE_NONE;
            break;
        default :
            Ursa3DMode = PANEL_3D_MODE_NONE;
            break;

    }
    return Ursa3DMode;
}

void MAPP_Scaler_Map3DFormatToUrsa3DMode(E_XC_3D_INPUT_MODE eInput3DFormat)
{
    U16 u16H = MApp_PCMode_Get_HResolution(MAIN_WINDOW,FALSE);
    if(eInput3DFormat == E_XC_3D_INPUT_FRAME_PACKING)
    {
        if(u16H> 1270 && u16H < 1290)
        {
            MApp_ZUI_Set_UI_3D_Mode(E_UI_3D_OUTPUT_MODE_NONE);
            MDrv_Ursa_6M30_3D_MODE(PANEL_3D_MODE_LINE_INTERLEAVED_2X);
        }
        else
        {
            MApp_ZUI_Set_UI_3D_Mode(E_UI_3D_OUTPUT_MODE_NONE);
            MDrv_Ursa_6M30_3D_MODE(PANEL_3D_MODE_FRAME_INTERLEAVE_25X);
        }
    }
    else if(eInput3DFormat == E_XC_3D_INPUT_SIDE_BY_SIDE_HALF)
    {
        MApp_ZUI_Set_UI_3D_Mode(E_UI_3D_OUTPUT_SIDE_BY_SIDE_HALF);
        MDrv_Ursa_6M30_3D_MODE(PANEL_3D_MODE_SIDE_BY_SIDE_2X);
    }
    else if(eInput3DFormat == E_XC_3D_INPUT_TOP_BOTTOM)
    {
        MApp_ZUI_Set_UI_3D_Mode(E_UI_3D_OUTPUT_TOP_BOTTOM);
        MDrv_Ursa_6M30_3D_MODE(PANEL_3D_MODE_TOP_BOTTOM_2X);
    }
    else if(eInput3DFormat == E_XC_3D_INPUT_LINE_ALTERNATIVE)
    {
        MApp_ZUI_Set_UI_3D_Mode(E_UI_3D_OUTPUT_MODE_NONE);
        MDrv_Ursa_6M30_3D_MODE(PANEL_3D_MODE_LINE_INTERLEAVED_2X);
    }
    else if(eInput3DFormat == E_XC_3D_INPUT_NORMAL_2D)
    {
        MApp_ZUI_Set_UI_3D_Mode(E_UI_3D_OUTPUT_MODE_NONE);
        MDrv_Ursa_6M30_3D_MODE(PANEL_3D_MODE_NONE);
    }
    else if(eInput3DFormat == E_XC_3D_INPUT_NORMAL_2D_HW)
    {
        MApp_ZUI_Set_UI_3D_Mode(E_UI_3D_OUTPUT_MODE_NONE);
        MDrv_Ursa_6M30_3D_MODE(PANEL_3D_MODE_NONE);
    }
    else if(eInput3DFormat == E_XC_3D_INPUT_FRAME_ALTERNATIVE)
    {
        MApp_ZUI_Set_UI_3D_Mode(E_UI_3D_OUTPUT_MODE_NONE);
        MDrv_Ursa_6M30_3D_MODE(PANEL_3D_MODE_FRAME_INTERLEAVE_2X);
    }
    else
    {
        MApp_ZUI_Set_UI_3D_Mode(E_UI_3D_OUTPUT_MODE_NONE);
        MDrv_Ursa_6M30_3D_MODE(PANEL_3D_MODE_NONE);
    }
    if (MApp_ZUI_GetActiveOSD() != E_OSD_EMPTY)
    {
        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CLOSE_CURRENT_OSD);
    }
}
#endif

#if (ENABLE_TCON_IN8903_PROCESS)
IN8903_PANEL_3D_FORMAT MAPP_Scaler_MapUi3DFormatToIn8903_3DMode(EN_3D_TYPE enUi3DType)
{
    IN8903_PANEL_3D_FORMAT enIn8903Fmt;

    switch(enUi3DType)
    {
        case EN_3D_BYPASS:
            enIn8903Fmt = IN8903_PANEL_3D_FORMAT_2D_YUV;
            break;

        case EN_3D_SIDE_BY_SIDE:
            enIn8903Fmt = IN8903_PANEL_3D_FORMAT_3D_LR;
            break;

        case EN_3D_TOP_BOTTOM:
            enIn8903Fmt = IN8903_PANEL_3D_FORMAT_3D_UD;
            break;

        case EN_3D_FRAME_ALTERNATIVE:
            enIn8903Fmt = IN8903_PANEL_3D_FORMAT_3D_FI;
            break;

        default :
            enIn8903Fmt = IN8903_PANEL_3D_FORMAT_2D_YUV;
            break;

    }
    return enIn8903Fmt;
}
#endif

#endif

void _MApp_Scaler_GetPreScalingDown_CheckCapture(XC_SETWIN_INFO* pXC_SETWIN_INFO, INPUT_SOURCE_TYPE_t enInputSourceType, SCALER_WIN eWindow)
{
    UNUSED(enInputSourceType);
    UNUSED(eWindow);

#if ( ENABLE_DTV_PRESCALINGDOWN == DISABLE )
    if (IsSrcTypeDTV(enInputSourceType))
        return;
#endif

    if(pXC_SETWIN_INFO==NULL)
        return;
    #if (ENABLE_PIP)
    #if(PIP_SIZE_WITH_BLACKSCREEN == DISABLE)
    if((MApp_Get_PIPMode() == EN_PIP_MODE_PIP) && (eWindow == SUB_WINDOW))
    {
        pXC_SETWIN_INFO->bPreHCusScaling = TRUE;
        pXC_SETWIN_INFO->u16PreHCusScalingSrc = pXC_SETWIN_INFO->stCapWin.width;
        pXC_SETWIN_INFO->u16PreHCusScalingDst = pXC_SETWIN_INFO->stCapWin.width;
        if(pXC_SETWIN_INFO->u16PreHCusScalingDst >= 807)
        {
            pXC_SETWIN_INFO->u16PreHCusScalingDst = 807;
        }
        pXC_SETWIN_INFO->bPreVCusScaling = TRUE;           ///<assign pre V customized scaling instead of using XC scaling
        pXC_SETWIN_INFO->u16PreVCusScalingDst =pXC_SETWIN_INFO->stCapWin.height;       ///<pre V customized scaling dst width
        pXC_SETWIN_INFO->u16PreVCusScalingSrc = pXC_SETWIN_INFO->stCapWin.height;
        if(pXC_SETWIN_INFO->u16PreVCusScalingDst >= 600 )
        {
              pXC_SETWIN_INFO->u16PreVCusScalingDst = 600;
        }
    }
    #endif
    #endif

#if (DYNSCALING == 0)
    pXC_SETWIN_INFO->bHCusScaling = pXC_SETWIN_INFO->bVCusScaling = FALSE;
#endif

   #if (MPEG_HD_PRE_SCAL_DOWN)
    if(IsSrcTypeDTV(enInputSourceType))
    {
        if(pXC_SETWIN_INFO->stCapWin.width >=1440)
         {
         // H pre-scaling down
            pXC_SETWIN_INFO->bPreHCusScaling = TRUE;           ///<assign pre H customized scaling instead of using XC scaling
            pXC_SETWIN_INFO->u16PreHCusScalingDst = 1192;       ///<pre H customized scaling dst width
            pXC_SETWIN_INFO->u16PreHCusScalingSrc = pXC_SETWIN_INFO->stCapWin.width;
           printf("pXC_SETWIN_INFO->stCapWin.width~=%d\n",pXC_SETWIN_INFO->stCapWin.width);

          }
        /*
        if(pXC_SETWIN_INFO->stCapWin.height>=900)
        {    //V pri-post scaling
            pXC_SETWIN_INFO->bPreVCusScaling = TRUE;           ///<assign pre V customized scaling instead of using XC scaling
            pXC_SETWIN_INFO->u16PreVCusScalingDst =900;       ///<pre V customized scaling dst width
            pXC_SETWIN_INFO->u16PreVCusScalingSrc = pXC_SETWIN_INFO->stCapWin.height;
           printf("pXC_SETWIN_INFO->stCapWin.height~~=%d\n",pXC_SETWIN_INFO->stCapWin.height);
        }
        */
    }
    #endif
 #if MM_1080I_USE_FB
  if(IsStorageInUse() && MApp_MPlayer_IsMoviePlaying())
   {
     if(pXC_SETWIN_INFO->stCapWin.width >=1920
        && pXC_SETWIN_INFO->bInterlace)
    {
        // H pre-scaling down
        pXC_SETWIN_INFO->bPreHCusScaling = TRUE;           ///<assign pre H customized scaling instead of using XC scaling
        pXC_SETWIN_INFO->u16PreHCusScalingDst = 1600;       ///<pre H customized scaling dst width
        pXC_SETWIN_INFO->u16PreHCusScalingSrc = pXC_SETWIN_INFO->stCapWin.width;
        printf("MM1080i pXC_SETWIN_INFO->stCapWin.width~=%d\n",pXC_SETWIN_INFO->stCapWin.width);
    }
   }
#endif
#if (MEMORY_MAP <= MMAP_64MB)
    if(IsSrcTypeHDMI(enInputSourceType)||IsSrcTypeVga(enInputSourceType))
    {
        if((pXC_SETWIN_INFO->stCapWin.height >1080 && !pXC_SETWIN_INFO->bInterlace)
#if ENABLE_3D_PROCESS
           && (MApi_XC_Get_3D_Input_Mode(eWindow) == E_XC_3D_INPUT_MODE_NONE)
           && (MApi_XC_Get_3D_Output_Mode() == E_XC_3D_OUTPUT_MODE_NONE)
#endif
        )
        {
        // V pre-scaling down
            pXC_SETWIN_INFO->bPreVCusScaling = TRUE;           ///<assign pre H customized scaling instead of using XC scaling
            pXC_SETWIN_INFO->u16PreVCusScalingDst = 1080;       ///<pre H customized scaling dst width
            pXC_SETWIN_INFO->u16PreVCusScalingSrc = pXC_SETWIN_INFO->stCapWin.height;
            printf("\r\n V size >1080 , pre-down to 1080");

        }
    }
#endif
}

void _MApp_Scaler_GetPreScalingDown_CheckDisplay(XC_SETWIN_INFO* pXC_SETWIN_INFO, INPUT_SOURCE_TYPE_t enInputSourceType)
{
    UNUSED(enInputSourceType);

#if ( ENABLE_DTV_PRESCALINGDOWN == DISABLE )
    if (IsSrcTypeDTV(enInputSourceType))
        return;
#endif

    if(pXC_SETWIN_INFO==NULL)
        return;
    #if (ENABLE_MIU_1 == 0 && MEMORY_MAP <= MMAP_64MB) //need to check , IS_HVD_CODEC(msAPI_VID_GetCodecType() is valid or not
        // For reduce bandwidth ...
        //Block some small window like MM preview or DTV channel edit window enter below patch
        //and also need prevent customer scaling when enter 3D mode, like half side by side
        if (pXC_SETWIN_INFO->stCapWin.width >= 1900 && pXC_SETWIN_INFO->stDispWin.width > (g_IPanel.Width()+1)/2
            && (MApi_XC_Get_3D_Output_Mode() == E_XC_3D_OUTPUT_MODE_NONE))
        {
            if ( (IsSrcTypeStorage(enInputSourceType) && (!MApi_XC_IsCurrentFrameBufferLessMode()) && (MEMORY_MAP>MMAP_64MB))
               || (IsSrcTypeDTV(enInputSourceType) && IS_HVD_CODEC(msAPI_VID_GetCodecType())) )
            {
               // printf("************** => Cap:W,H=%d,%d\n",pXC_SETWIN_INFO->stCapWin.width,pXC_SETWIN_INFO->stCapWin.height);
                pXC_SETWIN_INFO->bPreHCusScaling = TRUE;            ///<assign pre H customized scaling instead of using XC scaling
                //pXC_SETWIN_INFO->bHCusScaling = TRUE;

                pXC_SETWIN_INFO->u16PreHCusScalingDst = 960-4;       ///<pre H customized scaling dst width
                pXC_SETWIN_INFO->u16PreHCusScalingSrc = pXC_SETWIN_INFO->stCapWin.width;

                pXC_SETWIN_INFO->u16HCusScalingSrc = 960-4;
                pXC_SETWIN_INFO->u16HCusScalingDst = pXC_SETWIN_INFO->stDispWin.width;

                if ( IsSrcTypeStorage(enInputSourceType) && (!MApi_XC_IsCurrentFrameBufferLessMode()) && (MEMORY_MAP>MMAP_64MB) )
                {
                    pXC_SETWIN_INFO->u16PreHCusScalingDst = 992-4;      ///<pre H customized scaling dst width
                    pXC_SETWIN_INFO->u16HCusScalingSrc = 992-4;
                }
            }
        }
    #endif

    #if( ENABLE_MM_HD_FB && (MEMORY_MAP==MMAP_64MB) )
        if ((pXC_SETWIN_INFO->stCapWin.width >= 1200) && (pXC_SETWIN_INFO->stDispWin.width > (g_IPanel.Width()+1)/2))
        {
            if (IsSrcTypeStorage(enInputSourceType) && (!MApi_XC_IsCurrentFrameBufferLessMode()))
            {
                //printf("*** => Cap:W,H=%d,%d\n",pXC_SETWIN_INFO->stCapWin.width,pXC_SETWIN_INFO->stCapWin.height);
                printf("--MM HD scale down to 960--[Memory >= 6M]\n");
                pXC_SETWIN_INFO->bPreHCusScaling = TRUE;
                pXC_SETWIN_INFO->u16PreHCusScalingDst = 960; //<pre H customized scaling dst width
                pXC_SETWIN_INFO->u16PreHCusScalingSrc = pXC_SETWIN_INFO->stCapWin.width;
            }
        }
    #endif
}

#if 0
void MApp_Scaler_Set_ADC_HWCalibration(INPUT_SOURCE_TYPE_t enInputSourceType, SCALER_WIN eWindow)
{
    switch (enInputSourceType)
    {
        case INPUT_SOURCE_VGA:
            if (E_XC_HW_CALIBRATION == (XC_Auto_CalibrationMode)MApp_GetCalibrationMode(ADC_SET_VGA))
            {
                MApi_XC_ADC_EnableHWCalibration(TRUE);
            }
            else
            {
                MApi_XC_ADC_EnableHWCalibration(FALSE);
            }
            break;
        case INPUT_SOURCE_YPBPR:
        case INPUT_SOURCE_YPBPR2:
        case INPUT_SOURCE_YPBPR3:
            if (MApi_XC_Sys_IsSrcHD(eWindow))
            {
                if (E_XC_HW_CALIBRATION == (XC_Auto_CalibrationMode)MApp_GetCalibrationMode(ADC_SET_YPBPR_SD))
                {
                    MApi_XC_ADC_EnableHWCalibration(TRUE);
                }
                else
                {
                    MApi_XC_ADC_EnableHWCalibration(FALSE);
                }
            }
            else
            {
                if (E_XC_HW_CALIBRATION == (XC_Auto_CalibrationMode)MApp_GetCalibrationMode(ADC_SET_YPBPR_HD))
                {
                    MApi_XC_ADC_EnableHWCalibration(TRUE);
                }
                else
                {
                    MApi_XC_ADC_EnableHWCalibration(FALSE);
                }
            }
            break;
        case INPUT_SOURCE_SCART:
        case INPUT_SOURCE_SCART2:
            if (E_XC_HW_CALIBRATION == (XC_Auto_CalibrationMode)MApp_GetCalibrationMode(ADC_SET_SCART_RGB))
            {
                MApi_XC_ADC_EnableHWCalibration(TRUE);
            }
            else
            {
                MApi_XC_ADC_EnableHWCalibration(FALSE);
            }
            break;
        default:
            break;
    }
}
#endif

void MApp_Scaler_Print_Win(char* pcInfoStr, MS_WINDOW_TYPE* pWin)
{
    if( pcInfoStr )
    {
        printf(" %s ", pcInfoStr);
    }
    else
    {
        printf(" Win: ");
    }

    printf(" x,y,w,h=%u,%u,%u,%u\n", pWin->x, pWin->y, pWin->width, pWin->height);
}

void MApp_Scaler_Print_3Win(char* pcInfoStr, XC_SETWIN_INFO* pSetWinInfo)
{
    if( pcInfoStr )
    {
        printf(" %s\n", pcInfoStr);
    }

    MApp_Scaler_Print_Win(" CapWin:", &(pSetWinInfo->stCapWin) );
    MApp_Scaler_Print_Win(" CropWin:", &(pSetWinInfo->stCropWin) );
    MApp_Scaler_Print_Win(" DispWin:", &(pSetWinInfo->stDispWin) );
}

//********************************************************************************************
// Program capture win/crop win/display window
//   parameter:
//     ptSrcWin  - pointer to src window (not including timing hstart/vstart)
//                 NULL to use default value
//     ptCropWin - pointer to crop window
//                 NULL to use default value
//     ptDstWin  - pointer to dst window (not including timing hstart/vstart)
//                 NULL to use default value
//     enVideoScreen - aspect ratio code
//********************************************************************************************
void MApp_Scaler_SetWindow2(MS_WINDOW_TYPE *ptSrcWin,                                // start from (0,0)
                                            MS_WINDOW_TYPE *ptCropWin,              // start from (0,0)
                                            MS_WINDOW_TYPE *ptDstWin,               // start from (0,0)
                                            EN_ASPECT_RATIO_TYPE enVideoScreen,
                                            INPUT_SOURCE_TYPE_t enInputSourceType,
                                            SCALER_WIN eWindow)
{
    U16 u16AlignX=0, u16AlignY=0;
    U8 u8AspectRatio;
    SRC_RATIO_INFO tSrcRatioInfo;
    MVOP_Timing stMVOPTiming;
    PQ_WIN  enPQWin;
    XC_DLC_CAPTURE_Range stDLC_CapRange;
    E_XC_3D_INPUT_MODE eXC_3D_INPUT_MODE = E_XC_3D_INPUT_MODE_NONE;

#if(ENABLE_CHECK_SET_WIN_RESULT)
    g_Scaler_bSetWidnowResult = TRUE;
#endif

#if ENABLE_3D_PROCESS
    XC_SETWIN_INFO stXC_SetWin_Info_Sub;
    eXC_3D_INPUT_MODE = MApi_XC_Get_3D_Input_Mode(eWindow);
#else
    eXC_3D_INPUT_MODE = eXC_3D_INPUT_MODE;
#endif
#if ENABLE_MPLAYER_MOVIE
    BOOLEAN bInputSourceEnabled = FALSE;
#endif


    DEBUG_SET_WIN( PRINT_CURRENT_LINE(); );
    DEBUG_SET_WIN(printf("MApp_Scaler_SetWindow2(src=%u,eWindow=%u)\n", enInputSourceType, eWindow););

    LOG_CHANGE_CHANNEL_TIME_FUNC_START();

    DEBUG_ASPECT_RATIO(printf(" enVideoScreen=%u\n", enVideoScreen););

#if ENABLE_3D_PROCESS
    DEBUG_3D_INPUT(printf("g_HdmiInput3DFormatStatus=%u(%s)\n", g_HdmiInput3DFormatStatus, MApp_Scaler_Get_Xc3DInputName(g_HdmiInput3DFormatStatus)););
    DEBUG_3D_INPUT(printf("eXC_3D_INPUT_MODE=%u(%s)\n", eXC_3D_INPUT_MODE, MApp_Scaler_Get_Xc3DInputName(eXC_3D_INPUT_MODE)););
    DEBUG_3D_INPUT(printf("MApi_XC_Get_3D_HW_Version() =%u\n", MApi_XC_Get_3D_HW_Version()););
#endif

    MDrv_PQ_SetH264_OnOff(false);
    MDrv_PQ_SetMM_OnOff(false);
    memset(&stXC_SetWin_Info[eWindow], 0, sizeof(XC_SETWIN_INFO));
    memset(&stDLC_CapRange, 0, sizeof(XC_DLC_CAPTURE_Range));

    stXC_SetWin_Info[eWindow].enInputSourceType = enInputSourceType;

#if  MHEG5_ENABLE
    if( IsDTVInUse()
      && msAPI_MHEG5_IsRunning()
#if (ENABLE_DTV_EPG)
      && (STATE_TOP_EPG != MApp_TopStateMachine_GetTopState())
#endif
       )
    {
        MDrv_MVOP_GetOutputTiming(&stMVOPTiming);
        _MApp_Scaler_ProgMVDWin(eWindow, enInputSourceType, &stMVOPTiming, &stXC_SetWin_Info[eWindow]);

        _MApp_Scaler_CropCodecSrcWin(&gstVidStatus, &stXC_SetWin_Info[eWindow]);
        // In MHEG's concept, the capture win is start from (0,0), so convert to (0,0) first before MHEG calculated it's own parameters
        stXC_SetWin_Info[eWindow].stCapWin.x = 0;
        stXC_SetWin_Info[eWindow].stCapWin.y = 0;

        if(msAPI_MHEG5_VID_SetWindowInfo(&stXC_SetWin_Info[MAIN_WINDOW],eWindow))
        {
            // ok
        }
        else
        {
            MS_DEBUG_MSG(printf("MApp_Scaler_SetWindow  msAPI_MHEG5_VID_SetWindowInfo == FALSE\n"));
            return;
        }

        // XC capture win start from "capture start", not from 0
        stXC_SetWin_Info[eWindow].stCapWin.x += MDrv_MVOP_GetHStart();
        stXC_SetWin_Info[eWindow].stCapWin.y += MDrv_MVOP_GetVStart();
    #if VERIFY_SCALER_FPGA //non-scaling function
        stXC_SetWin_Info[eWindow].stDispWin.height = stXC_SetWin_Info[eWindow].stCropWin.height = stXC_SetWin_Info[eWindow].stCapWin.height;
        stXC_SetWin_Info[eWindow].stDispWin.width= stXC_SetWin_Info[eWindow].stCropWin.width = stXC_SetWin_Info[eWindow].stCapWin.width;
        stXC_SetWin_Info[eWindow].stDispWin.x = stXC_SetWin_Info[eWindow].stDispWin.y = 0;
    #endif
    }
    else
#endif
    {
        u8AspectRatio = _MApp_Scaler_Aspect_Ratio_Remapping(stSystemInfo[eWindow].enAspectRatio);

        if( IsSrcTypeAnalog(enInputSourceType) || IsSrcTypeHDMI(enInputSourceType))
        {
            _MApp_Scaler_ProgAnalogWin(enInputSourceType, &g_PcadcModeSetting[eWindow], u8AspectRatio,
                                        MApi_XC_PCMonitor_GetSyncStatus(eWindow), &stXC_SetWin_Info[eWindow], eWindow);

        #if(ENABLE_CHECK_SET_WIN_RESULT)
            if( FALSE == g_Scaler_bSetWidnowResult )
            {
                printf("\nError: _MApp_Scaler_ProgAnalogWin() failed\n");
                msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_SET_WIN, ENABLE, 0, eWindow);
                return;
            }
        #endif


            u16AlignX = ANALOG_CROP_ALIGN_X;
            u16AlignY = ANALOG_CROP_ALIGN_Y;
        }
        else if( IsSrcTypeATV(enInputSourceType) || IsSrcTypeDigitalVD(enInputSourceType))
        {
            _MApp_Scaler_ProgDigitalWin( enInputSourceType, mvideo_vd_get_videosystem(), u8AspectRatio, &stXC_SetWin_Info[eWindow], eWindow );
            u16AlignX = DIGITAL_CROP_ALIGN_X;
            u16AlignY = DIGITAL_CROP_ALIGN_Y;
        }
        else if( IsSrcTypeDTV(enInputSourceType) )
        {
            MDrv_MVOP_GetOutputTiming(&stMVOPTiming);
            _MApp_Scaler_ProgMVDWin(eWindow, enInputSourceType, &stMVOPTiming, &stXC_SetWin_Info[eWindow]);
            _MApp_Scaler_CropCodecSrcWin(&gstVidStatus, &stXC_SetWin_Info[eWindow]);
            u16AlignX = DTV_CROP_ALIGN_X;
            u16AlignY = DTV_CROP_ALIGN_Y;
        }
    #if ((ENABLE_DMP) || (DISPLAY_LOGO))
        else
        {
            MDrv_MVOP_GetOutputTiming(&stMVOPTiming);
            _MApp_Scaler_ProgMVDWin(eWindow, enInputSourceType, &stMVOPTiming, &stXC_SetWin_Info[eWindow]);

            _MApp_Scaler_CropCodecSrcWin(&gstVidStatus, &stXC_SetWin_Info[eWindow]);
            u16AlignX = MEDIA_CROP_ALIGN_X;
            u16AlignY = MEDIA_CROP_ALIGN_Y;
        }
    #endif // #if ((ENABLE_DMP) || (DISPLAY_LOGO))
        DEBUG_SET_WIN(printf(" %s timing \n", (stXC_SetWin_Info[eWindow].bInterlace)?("Interlace"):("Progress")));

        //printf("Start(%d, %d) Size(%d, %d)\n", g_SrcInfo.u16H_CapStart,g_SrcInfo.u16V_CapStart,
        //g_SrcInfo.u16H_CapSize,g_SrcInfo.u16V_CapSize);

        // PIP/POP: In PIP/POP mode, we need set window size before signal stable.
        // Width and height of capture window set to zero will cause pre-scale crash.
        // Therefore we correct invalid value on there.
        if((stXC_SetWin_Info[eWindow].stCapWin.width==0) || (stXC_SetWin_Info[eWindow].stCapWin.height==0))
        {
            stXC_SetWin_Info[eWindow].stCapWin.width=10;
            stXC_SetWin_Info[eWindow].stCapWin.height=10;
        }

        if (ptSrcWin)
        {
            // XC concept: capture window never start from (0,0) because it's base is input signal
            memcpy(&stXC_SetWin_Info[eWindow].stCapWin, ptSrcWin, sizeof(MS_WINDOW_TYPE));
            ASSERT(stXC_SetWin_Info[eWindow].stCapWin.x != 0);
            ASSERT(stXC_SetWin_Info[eWindow].stCapWin.y != 0);
        }

        //ToDo: MMAP<=32 equals to request frame buffer less is from Chakra2_ATSC.
        //Not sure this also can be adopted for all ICs in Chakra3, removed for temp
        #if 0//(MEMORY_MAP <= MMAP_32MB)
        if (MApi_XC_IsCurrentFrameBufferLessMode()||MApi_XC_IsCurrentRequest_FrameBufferLessMode())
        {
            MApp_Scaler_Adjust_OverscanRatio_RFBL(enInputSourceType, &stXC_SetWin_Info[eWindow]);
        }
        #endif

        tSrcRatioInfo.u16VideoWidth = stXC_SetWin_Info[eWindow].stCapWin.width;
        tSrcRatioInfo.u16VideoHeight = stXC_SetWin_Info[eWindow].stCapWin.height;
        tSrcRatioInfo.u8AspectRate = gstVidStatus.u8AspectRate;
        tSrcRatioInfo.u8AFD = gstVidStatus.u8AFD;
        tSrcRatioInfo.u32SarWidth = gstVidStatus.u16SarWidth;
        tSrcRatioInfo.u32SarHeight = gstVidStatus.u16SarHeight;

        if (ptCropWin)
        {
            // XC concept: crop window must start from (0,0) because it's base is frame buffer window
            memcpy(&stXC_SetWin_Info[eWindow].stCropWin, ptCropWin, sizeof(MS_WINDOW_TYPE));
            ASSERT(stXC_SetWin_Info[eWindow].stCropWin.x == 0);
            ASSERT(stXC_SetWin_Info[eWindow].stCropWin.y == 0);
        }
        else
        {
            stXC_SetWin_Info[eWindow].stCropWin.x = 0;
            stXC_SetWin_Info[eWindow].stCropWin.y = 0;
            stXC_SetWin_Info[eWindow].stCropWin.width = stXC_SetWin_Info[eWindow].stCapWin.width;
            stXC_SetWin_Info[eWindow].stCropWin.height= stXC_SetWin_Info[eWindow].stCapWin.height;
        }

        if (ptDstWin)
        {
            //printf(" Has DstWin!\n");
            // XC concept: disp window must start from (0,0) because it's base is display and which is aligned to UI, all start from (0,0)
            memcpy(&stXC_SetWin_Info[eWindow].stDispWin, ptDstWin, sizeof(MS_WINDOW_TYPE));
        }
        else
        {
            //printf(" No DstWin => Panel~\n");
            stXC_SetWin_Info[eWindow].stDispWin.x = 0;
            stXC_SetWin_Info[eWindow].stDispWin.y = 0;
            stXC_SetWin_Info[eWindow].stDispWin.width = g_IPanel.Width();
            stXC_SetWin_Info[eWindow].stDispWin.height = g_IPanel.Height();
        }


        DEBUG_SET_WIN(printf("SYS_INPUT_SOURCE_TYPE(%d) %x\n", (U16)eWindow, (U16)SYS_INPUT_SOURCE_TYPE(eWindow)));
        DEBUG_SET_WIN(printf("enAspectRatio %x\n", (U16)stSystemInfo[eWindow].enAspectRatio));
        DEBUG_SET_WIN(printf("%s timing \n", (stXC_SetWin_Info[eWindow].bInterlace)?("Interlace"):("Progress")));

        DEBUG_SET_WIN(printf("src: x,y,w,h=%u,%u,%u,%u\n", stXC_SetWin_Info[eWindow].stCapWin.x, stXC_SetWin_Info[eWindow].stCapWin.y, stXC_SetWin_Info[eWindow].stCapWin.width, stXC_SetWin_Info[eWindow].stCapWin.height));
        DEBUG_SET_WIN(printf("crop1: x,y,w,h=%u,%u,%u,%u\n", stXC_SetWin_Info[eWindow].stCropWin.x, stXC_SetWin_Info[eWindow].stCropWin.y, stXC_SetWin_Info[eWindow].stCropWin.width, stXC_SetWin_Info[eWindow].stCropWin.height));
        DEBUG_SET_WIN(printf("dst1 : x,y,w,h=%u,%u,%u,%u\n", stXC_SetWin_Info[eWindow].stDispWin.x, stXC_SetWin_Info[eWindow].stDispWin.y, stXC_SetWin_Info[eWindow].stDispWin.width, stXC_SetWin_Info[eWindow].stDispWin.height));


        // Force control pre-scaling ...
        // 1. Reset pre-scaling falg
        stXC_SetWin_Info[eWindow].bPreHCusScaling = FALSE;
        stXC_SetWin_Info[eWindow].bPreVCusScaling = FALSE;

        // 2. Over write pre-scaling flag by case
    #if (ENABLE_DMP)
        if( IsSrcTypeStorage(enInputSourceType) && (eXC_3D_INPUT_MODE == E_XC_3D_INPUT_MODE_NONE)) // MM and not preview
        {
            if( MApp_MPlayer_IsPhotoPlaying()
                #if ENABLE_MPLAYER_MOVIE
                ||MApp_MPlayer_IsMoviePlaying()
                #endif
                )
            {
                if(((enVideoScreen > VIDEOSCREEN_MM_CAL_BY_VIDEOPLAYER)||\
                  (enVideoScreen < VIDEOSCREEN_MM_KEEP_RATIO_AND_SCALE)))
               {
                    enVideoScreen = VIDEOSCREEN_MM_KEEP_RATIO_AND_SCALE;
                    DEBUG_SET_WIN(printf(" Force Aspect Ratio to VIDEOSCREEN_MM_KEEP_RATIO_AND_SCALE\n"));

               }

                if( MApp_MPlayer_QueryZoomScale() != E_MPLAYER_ZOOM_1 )
                {
                    // Use the videoplayer's dst window
                    enVideoScreen = VIDEOSCREEN_MM_CAL_BY_VIDEOPLAYER;
                    DEBUG_SET_WIN(printf("MApp_Scaler_SetWindow: Force Aspect Ratio to FULL\n"));
                }
            }
            else // Preview or play photo
            {
                 if(((enVideoScreen > VIDEOSCREEN_MM_CAL_BY_VIDEOPLAYER)||\
                  (enVideoScreen < VIDEOSCREEN_MM_KEEP_RATIO_AND_SCALE))||\
                  m_bFLG_PREVIEW)
                {
                    enVideoScreen = VIDEOSCREEN_MM_KEEP_RATIO_AND_SCALE;
                    DEBUG_SET_WIN(printf(" Preview Force Aspect Ratio to VIDEOSCREEN_MM_KEEP_RATIO_AND_SCALE\n"));

                }
            }
        }
        else
    #endif
        {
        #if (CHANGE_AR_WITHOUT_BLUESCREEN == ENABLE)
        {
            stXC_SetWin_Info[eWindow].bPreHCusScaling = TRUE;
            stXC_SetWin_Info[eWindow].u16PreHCusScalingSrc = stXC_SetWin_Info[eWindow].stCapWin.width;
            stXC_SetWin_Info[eWindow].u16PreHCusScalingDst = stXC_SetWin_Info[eWindow].stDispWin.width;
        }
        #endif
        }

        //If you are forced to do some patch for pre-scaling down
        //Ex: DRAM size is not enough.
        //And your condition is not related to display window
        //Please add your condition in _MApp_Scaler_GetPreScalingDown_CheckCapture
        if(!MApi_XC_IsCurrentFrameBufferLessMode())
        {
            _MApp_Scaler_GetPreScalingDown_CheckCapture(&stXC_SetWin_Info[eWindow], enInputSourceType, eWindow);
        }

        // tCropWin should keep to non-cropped size for MApp_Scaler_Adjust_AspectRatio()
        // because indirect caller _msAPI_Picture_AdjustWidth_CutByHeight() need to
        // original video size


        // [Set display window 1]    keep the display window before processing it.
        // [Set display window 2.1] processing the display window...
    #if(ENABLE_PIP)
        if((eWindow==MAIN_WINDOW)
            && (MApp_Get_PIPMode()  != EN_PIP_MODE_POP_FULL)
            && (MApp_Get_PIPMode()  != EN_PIP_MODE_POP)
            )
    #endif
        {
          #if ENABLE_FBL_ASPECT_RATIO_BY_MVOP
            if((!MApi_XC_IsCurrentFrameBufferLessMode()) || (enVideoScreen == VIDEOSCREEN_NORMAL) || (!IsSrcTypeStorage(enInputSourceType) && !IsSrcTypeDTV(enInputSourceType)))
          #endif
            {
                MApp_Scaler_Adjust_AspectRatio(eWindow, enVideoScreen, &stXC_SetWin_Info[eWindow].stCropWin, &stXC_SetWin_Info[eWindow].stDispWin, &tSrcRatioInfo,!IsSrcTypeDTV(enInputSourceType));    // adjust CropWin according to aspect ratio
                DEBUG_SET_WIN(printf("crop2: x,y,w,h=%u,%u,%u,%u\n", stXC_SetWin_Info[eWindow].stCropWin.x, stXC_SetWin_Info[eWindow].stCropWin.y, stXC_SetWin_Info[eWindow].stCropWin.width, stXC_SetWin_Info[eWindow].stCropWin.height));
                DEBUG_SET_WIN(printf("dst2 : x,y,w,h=%u,%u,%u,%u\n", stXC_SetWin_Info[eWindow].stDispWin.x, stXC_SetWin_Info[eWindow].stDispWin.y, stXC_SetWin_Info[eWindow].stDispWin.width, stXC_SetWin_Info[eWindow].stDispWin.height));
            }
        }


        // [Set display window 2.2] proceesing the dispaly window..
        MApp_Scaler_Adjust_OverscanRatio(eWindow, enInputSourceType, &stXC_SetWin_Info[eWindow]);           // adjust CropWin according to overscan ratio
        DEBUG_SET_WIN(printf("crop3: x,y,w,h=%u,%u,%u,%u\n", stXC_SetWin_Info[eWindow].stCropWin.x, stXC_SetWin_Info[eWindow].stCropWin.y, stXC_SetWin_Info[eWindow].stCropWin.width, stXC_SetWin_Info[eWindow].stCropWin.height));

        MApp_Scaler_AlignWindow(&stXC_SetWin_Info[eWindow].stCropWin, u16AlignX, u16AlignY);
        DEBUG_SET_WIN(printf("crop4: x,y,w,h=%u,%u,%u,%u\n", stXC_SetWin_Info[eWindow].stCropWin.x, stXC_SetWin_Info[eWindow].stCropWin.y, stXC_SetWin_Info[eWindow].stCropWin.width, stXC_SetWin_Info[eWindow].stCropWin.height));

        if( MApi_XC_IsCurrentFrameBufferLessMode() )
        {
            //memcpy(&stXC_SetWin_Info[eWindow].stCapWin, &stXC_SetWin_Info[eWindow].stCropWin, sizeof(MS_WINDOW_TYPE));
            stXC_SetWin_Info[eWindow].stCapWin.x += stXC_SetWin_Info[eWindow].stCropWin.x;
            stXC_SetWin_Info[eWindow].stCapWin.y += stXC_SetWin_Info[eWindow].stCropWin.y;
            stXC_SetWin_Info[eWindow].stCapWin.height = stXC_SetWin_Info[eWindow].stCropWin.height;
            stXC_SetWin_Info[eWindow].stCapWin.width  = stXC_SetWin_Info[eWindow].stCropWin.width;
            stXC_SetWin_Info[eWindow].stCropWin.x = 0;
            stXC_SetWin_Info[eWindow].stCropWin.y = 0;
            DEBUG_SET_WIN(printf("FBL src: x,y,w,h=%u,%u,%u,%u\n", stXC_SetWin_Info[eWindow].stCapWin.x, stXC_SetWin_Info[eWindow].stCapWin.y, stXC_SetWin_Info[eWindow].stCapWin.width, stXC_SetWin_Info[eWindow].stCapWin.height));
        }

    #if (VERIFY_SCALER_FPGA || _TEST_VGA_) //non-scaling function
        stXC_SetWin_Info[eWindow].stDispWin.height = stXC_SetWin_Info[eWindow].stCropWin.height = stXC_SetWin_Info[eWindow].stCapWin.height;
        stXC_SetWin_Info[eWindow].stDispWin.width= stXC_SetWin_Info[eWindow].stCropWin.width = stXC_SetWin_Info[eWindow].stCapWin.width;
        stXC_SetWin_Info[eWindow].stDispWin.x = stXC_SetWin_Info[eWindow].stDispWin.y = 0;
    #endif

    #if (ENABLE_TCON)
        if (g_PNL_TypeSel == TCON_PNL_WXGA_BOE_HV320WXC)
        {   // BOE_HV320WXC panel has 2-bit dummy pixel
            DEBUG_SET_WIN(printf("BOE_HV320WXC_03 : x = %u, w = %u, \n", stXC_SetWin_Info[eWindow].stDispWin.x, stXC_SetWin_Info[eWindow].stDispWin.width));
            stXC_SetWin_Info[eWindow].stDispWin.x += 0;
            stXC_SetWin_Info[eWindow].stDispWin.width -= 2;
            DEBUG_SET_WIN(printf("BOE_HV320WXC_04 : x = %u, w = %u, \n", stXC_SetWin_Info[eWindow].stDispWin.x, stXC_SetWin_Info[eWindow].stDispWin.width));
        }
    #endif

        //If you are forced to do some patch for pre-scaling down
        //Ex: DRAM size is not enough.
        //And your condition is related to display window
        //Please add your condition in _MApp_Scaler_GetPreScalingDown_CheckDisplay
        if(!MApi_XC_IsCurrentFrameBufferLessMode())
        {
            _MApp_Scaler_GetPreScalingDown_CheckDisplay(&stXC_SetWin_Info[eWindow], enInputSourceType);
        }

    }

    if(stXC_SetWin_Info[eWindow].bInterlace)
    {
          if(stXC_SetWin_Info[eWindow].stCapWin.height%2)
          {
              stXC_SetWin_Info[eWindow].stCapWin.height -= 1;
          }
    }

#if(ENABLE_DMP & DYNSCALING)
    if( IsSrcTypeStorage(enInputSourceType) ) // MM
    {
        MApp_VDPlayer_SetVirtualBox(&stXC_SetWin_Info[eWindow], ptSrcWin, ptDstWin);
    }
#endif

#if(ENABLE_DMP)
    if( IsSrcTypeStorage(enInputSourceType) ) // MM
    {
        MApp_VDPlayer_SetQuarterPixel(&stXC_SetWin_Info[eWindow]);
    }
#endif

    _MApp_XC_check_crop_win( &stXC_SetWin_Info[eWindow] );
    _MApp_Scaler_CropCodecDisWin(&stXC_SetWin_Info[eWindow] );

#if ENABLE_MPLAYER_MOVIE
    if((IsStorageInUse()) && (MApp_MPlayer_IsMoviePlaying()) &&
       (E_MPLAYER_MOVIE_PAUSE==MApp_MPlayer_QueryMoviePlayMode()))
    {
        if(MApi_XC_IsInputSourceDisabled(MAIN_WINDOW))
        {
            MApi_XC_DisableInputSource(FALSE, eWindow);
            bInputSourceEnabled = TRUE;
        }
        MApi_XC_set_FD_Mask(FALSE);
    }
#endif

    if(stXC_SetWin_Info[eWindow].u16PreHCusScalingDst > stXC_SetWin_Info[eWindow].u16PreHCusScalingSrc)
    {
        stXC_SetWin_Info[eWindow].bPreHCusScaling = FALSE;
        printf("Customer H PreScaling setting error %u->%u: change to auto prescaling\n",
                stXC_SetWin_Info[eWindow].u16PreHCusScalingSrc, stXC_SetWin_Info[eWindow].u16PreHCusScalingDst);
    }

    if(stXC_SetWin_Info[eWindow].u16PreVCusScalingDst > stXC_SetWin_Info[eWindow].u16PreVCusScalingSrc)
    {
        stXC_SetWin_Info[eWindow].bPreVCusScaling = FALSE;
        printf("Customer V PreScaling setting error %u->%u: change to auto prescaling\n",
                stXC_SetWin_Info[eWindow].u16PreVCusScalingSrc, stXC_SetWin_Info[eWindow].u16PreVCusScalingDst);
    }

    if ( stXC_SetWin_Info[eWindow].bPreHCusScaling )
    {
        DEBUG_SET_WIN(printf("Cus Pre H scaling from %d to %d\n", stXC_SetWin_Info[eWindow].u16PreHCusScalingSrc,
                                                        stXC_SetWin_Info[eWindow].u16PreHCusScalingDst));
    }
    if ( stXC_SetWin_Info[eWindow].bPreVCusScaling )
    {
        DEBUG_SET_WIN(printf("Cus Pre V scaling from %d to %d\n", stXC_SetWin_Info[eWindow].u16PreVCusScalingSrc,
                                                        stXC_SetWin_Info[eWindow].u16PreVCusScalingDst));
    }
    if ( stXC_SetWin_Info[eWindow].bHCusScaling )
    {
        DEBUG_SET_WIN(printf("Cus Post H scaling from %d to %d\n", stXC_SetWin_Info[eWindow].u16HCusScalingSrc,
                                                         stXC_SetWin_Info[eWindow].u16HCusScalingDst));
    }
    if ( stXC_SetWin_Info[eWindow].bVCusScaling )
    {
        DEBUG_SET_WIN(printf("Cus Post V scaling from %d to %d\n", stXC_SetWin_Info[eWindow].u16VCusScalingSrc,
                                                         stXC_SetWin_Info[eWindow].u16VCusScalingDst));
    }


#if ENABLE_3D_PROCESS
    if(MApi_XC_Get_3D_HW_Version() < 2)
    {
        memcpy(&stXC_SetWin_Info_Sub, &stXC_SetWin_Info[MAIN_WINDOW], sizeof(XC_SETWIN_INFO));
        if((MApi_XC_Get_3D_Output_Mode() == E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF)
            &&eWindow == MAIN_WINDOW)
        {
            stXC_SetWin_Info[MAIN_WINDOW].stDispWin.width /= 2;
        }
        else if(MApi_XC_Get_3D_Output_Mode() == E_XC_3D_OUTPUT_TOP_BOTTOM)
        {
            stXC_SetWin_Info[MAIN_WINDOW].stDispWin.height /= 2;
        }
    }

    MApp_Scaler_Adjust3DDisplayWin(stXC_SetWin_Info, MAIN_WINDOW, enVideoScreen);
    if((MApi_XC_Get_3D_HW_Version() == 1) &&
       (MApi_XC_Get_3D_Output_Mode() == E_XC_3D_OUTPUT_TOP_BOTTOM)&&
       (m_st3DInfo.enOutput3DMode== E_XC_3D_OUTPUT_LINE_ALTERNATIVE))//try not to mess with real top_bottom output
    {
        //set reg_3dlr_side2line_en, then enlarge main_win size to fullscreen.
        MApi_XC_Enable_3D_LR_Sbs2Line(TRUE);
    }
    else
    {
#if (ENABLE_PIP)
        if(MApp_Get_PIPMode() == EN_PIP_MODE_OFF)
#endif
        {
            if(MApi_XC_Is_SubWindowEanble())
            {
                MApi_XC_DisableInputSource(TRUE, SUB_WINDOW);
                MApi_XC_DisableSubWindow();
            }
        }
        MApi_XC_Enable_3D_LR_Sbs2Line(FALSE);
    }
#endif

#if (ENABLE_PIP)
    if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
    {
        MDrv_PQ_SetDMSV12L((PQ_WIN)eWindow,FALSE);
    }
    else
    {
        MDrv_PQ_SetDMSV12L((PQ_WIN)eWindow,TRUE);
    }
#endif


    LOG_CHANGE_CHANNEL_TIME("  SetWin-5");

    // Move to _MApp_PCMode_SetMode_Adc()
    //MApp_Scaler_Set_ADC_HWCalibration(enInputSourceType, eWindow);


#if (CHIP_FAMILY_MAYA == CHIP_FAMILY_TYPE)
  #if(ENABLE_MPLAYER_PHOTO)
    if( IsStorageInUse()
      &&(MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_PHOTO) // Media type is photo
      &&(MApp_MPlayer_QueryPreviewState(E_MPLAYER_TYPE_PHOTO) != E_PHOTO_PREVIEW_NONE ) // Normal play
      ) // MM-Photo&&Full display
    {
        MApi_XC_Enable_LockFreqOnly(FALSE);
    }
    else
    {
        MApi_XC_Enable_LockFreqOnly(TRUE);
    }
  #endif
#endif

    DEBUG_SET_WIN( MApp_Scaler_Print_3Win( "Win 10:", &(stXC_SetWin_Info[eWindow]) ); );
    DEBUG_SET_WIN(printf("src 10: x,y,w,h=%u,%u,%u,%u\n", stXC_SetWin_Info[eWindow].stCapWin.x, stXC_SetWin_Info[eWindow].stCapWin.y, stXC_SetWin_Info[eWindow].stCapWin.width, stXC_SetWin_Info[eWindow].stCapWin.height));
    DEBUG_SET_WIN(printf("crop 10: x,y,w,h=%u,%u,%u,%u\n", stXC_SetWin_Info[eWindow].stCropWin.x, stXC_SetWin_Info[eWindow].stCropWin.y, stXC_SetWin_Info[eWindow].stCropWin.width, stXC_SetWin_Info[eWindow].stCropWin.height));
    DEBUG_SET_WIN(printf("dst 10: x,y,w,h=%u,%u,%u,%u\n", stXC_SetWin_Info[eWindow].stDispWin.x, stXC_SetWin_Info[eWindow].stDispWin.y, stXC_SetWin_Info[eWindow].stDispWin.width, stXC_SetWin_Info[eWindow].stDispWin.height));

    TIMER_SET_DELAY_ID_START(E_DELAY_ID_DRV_XC_SET_WIN);
    if(MApi_XC_SetWindow(&stXC_SetWin_Info[eWindow], sizeof(XC_SETWIN_INFO), eWindow) == FALSE)
    {
        MS_DEBUG_MSG(printf("MApi_XC_SetWindow failed because of InitData wrong, please update header file and compile again\n"));
        printf("\nError: MApi_XC_SetWindow() failed!\n");
    }
    TIMER_SET_DELAY_ID_END();
    LOG_CHANGE_CHANNEL_TIME("  SetWin-6");

#if(INPUT_SCART_VIDEO_COUNT > 0)
    MApp_Scaler_SetupADC_ScartRGB(eWindow);
#endif

#if ENABLE_3D_PROCESS
    if(MApi_XC_Get_3D_HW_Version() < 2)
    {
        if((m_st3DInfo.enOutput3DMode == E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF)||
            (m_st3DInfo.enOutput3DMode == E_XC_3D_OUTPUT_TOP_BOTTOM) ||
            ((MApi_XC_Get_3D_Output_Mode() == E_XC_3D_OUTPUT_TOP_BOTTOM)&&
               (m_st3DInfo.enOutput3DMode == E_XC_3D_OUTPUT_LINE_ALTERNATIVE)))
        {
            if(MApi_XC_Get_3D_Output_Mode() == E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF)
            {
                stXC_SetWin_Info_Sub.stDispWin.x += stXC_SetWin_Info_Sub.stDispWin.width/2;
                stXC_SetWin_Info_Sub.stDispWin.width /= 2;
            }
            else if(MApi_XC_Get_3D_Output_Mode() == E_XC_3D_OUTPUT_TOP_BOTTOM)
            {
                stXC_SetWin_Info_Sub.stDispWin.y += stXC_SetWin_Info_Sub.stDispWin.height/2;
                stXC_SetWin_Info_Sub.stDispWin.height /= 2;
            }
            //printf("SrcWin3: x,y,w,h=%u,%u,%u,%u\n", stXC_SetWin_Info_Sub.stCapWin.x, stXC_SetWin_Info_Sub.stCapWin.y, stXC_SetWin_Info_Sub.stCapWin.width, stXC_SetWin_Info_Sub.stCapWin.height);
            //printf("CropWin3: x,y,w,h=%u,%u,%u,%u\n", stXC_SetWin_Info_Sub.stCropWin.x, stXC_SetWin_Info_Sub.stCropWin.y, stXC_SetWin_Info_Sub.stCropWin.width, stXC_SetWin_Info_Sub.stCropWin.height);
            //printf("DispWin3: x,y,w,h=%u,%u,%u,%u\n", stXC_SetWin_Info_Sub.stDispWin.x, stXC_SetWin_Info_Sub.stDispWin.y, stXC_SetWin_Info_Sub.stDispWin.width, stXC_SetWin_Info_Sub.stDispWin.height);
            MApp_Scaler_Adjust3DDisplayWin(&stXC_SetWin_Info_Sub, SUB_WINDOW, enVideoScreen);
            //printf("SrcWin3: x,y,w,h=%u,%u,%u,%u\n", stXC_SetWin_Info_Sub.stCapWin.x, stXC_SetWin_Info_Sub.stCapWin.y, stXC_SetWin_Info_Sub.stCapWin.width, stXC_SetWin_Info_Sub.stCapWin.height);
            //printf("CropWin3: x,y,w,h=%u,%u,%u,%u\n", stXC_SetWin_Info_Sub.stCropWin.x, stXC_SetWin_Info_Sub.stCropWin.y, stXC_SetWin_Info_Sub.stCropWin.width, stXC_SetWin_Info_Sub.stCropWin.height);
            //printf("DispWin3: x,y,w,h=%u,%u,%u,%u\n", stXC_SetWin_Info_Sub.stDispWin.x, stXC_SetWin_Info_Sub.stDispWin.y, stXC_SetWin_Info_Sub.stDispWin.width, stXC_SetWin_Info_Sub.stDispWin.height);


            if(MApi_XC_SetWindow(&stXC_SetWin_Info_Sub, sizeof(XC_SETWIN_INFO), SUB_WINDOW) == FALSE)
            {
                printf("MApi_XC_SetWindow failed because of InitData wrong, please update header file and compile again\n");
            }

            MApi_XC_3D_PostPQSetting(MAIN_WINDOW);
            MApi_XC_ACE_3DClonePQMap(E_ACE_WEAVETYPE_NONE);
            if(!MApi_XC_Is_SubWindowEanble())
            {
                MApi_XC_EnableSubWindow(&stXC_SetWin_Info_Sub.stDispWin);
            }

            // E_3D_AR_AUTO,E_3D_AR_CENTER case should also consider y pos
            // notice: there is case that 3D will not show on fullscreen(such as 3DUI), should
            //         not follow into these codes(should call E_3D_AR_FULL)
            if(VIDEOSCREEN_3D_FULL != enVideoScreen)
            {
                MS_WINDOW_TYPE stDispWin;
                if((MApi_XC_Get_3D_HW_Version() == 1) &&
                   (MApi_XC_Get_3D_Output_Mode() == E_XC_3D_OUTPUT_TOP_BOTTOM)&&
                   (m_st3DInfo.enOutput3DMode == E_XC_3D_OUTPUT_LINE_ALTERNATIVE))//try not to mess with real top_bottom output
                {
                    //change display window.
                    //height should not be doubled, because it has been double at driver.
                    //if y position is not from top, then we need to adjust y to center
                    MApi_XC_GetDispWinFromReg(&stDispWin, MAIN_WINDOW);
                    //stDispWin.height *=2;
                    if(stDispWin.y != 0)
                    {
                        stDispWin.y = (g_IPanel.Height() - stDispWin.height)/2;
                    }
                    MApi_XC_SetDispWinToReg(&stDispWin, MAIN_WINDOW);
                }
            }

        }
        else
        {
#if (ENABLE_PIP)
            if(MApp_Get_PIPMode() == EN_PIP_MODE_OFF)
#endif
            {
                if(MApi_XC_Is_SubWindowEanble())
                {
                    MApi_XC_DisableInputSource(TRUE, SUB_WINDOW);
                    MApi_XC_DisableSubWindow();
                }
            }
            MApi_XC_Enable_3D_LR_Sbs2Line(FALSE);
        }
    }
    else
    {
        if(((MApi_XC_Get_3D_Output_Mode() == E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF)
               || (MApi_XC_Get_3D_Output_Mode() == E_XC_3D_OUTPUT_TOP_BOTTOM))
             && ((VIDEOSCREEN_3D_AUTO == enVideoScreen)
                 || (VIDEOSCREEN_3D_CENTER == enVideoScreen)))
        {
            XC_SETWIN_INFO stXC_SetWin_Info_Main_Temp;
            XC_SETWIN_INFO stXC_SetWin_Info_Sub_Temp;
            memcpy(&stXC_SetWin_Info_Main_Temp, &stXC_SetWin_Info, sizeof(XC_SETWIN_INFO));
            stXC_SetWin_Info_Main_Temp.stDispWin.x = 0;
            stXC_SetWin_Info_Main_Temp.stDispWin.y = 0;
            stXC_SetWin_Info_Main_Temp.stDispWin.width = g_IPanel.Width();
            stXC_SetWin_Info_Main_Temp.stDispWin.height = g_IPanel.Height();
            memcpy(&stXC_SetWin_Info_Sub_Temp, &stXC_SetWin_Info_Main_Temp, sizeof(XC_SETWIN_INFO));
            if(MApi_XC_Get_3D_Output_Mode() == E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF)
            {
          #if MirrorEnable
               if(MApp_Image_GetMirror())
               {
                    stXC_SetWin_Info_Main_Temp.stDispWin.x += stXC_SetWin_Info_Main_Temp.stDispWin.width/2;
                }
               else
                {
                     stXC_SetWin_Info_Sub_Temp.stDispWin.x += stXC_SetWin_Info_Sub_Temp.stDispWin.width/2;
                }
            #else
                stXC_SetWin_Info_Sub_Temp.stDispWin.x += stXC_SetWin_Info_Sub_Temp.stDispWin.width/2;
         #endif
                stXC_SetWin_Info_Main_Temp.stDispWin.width /= 2;
                stXC_SetWin_Info_Sub_Temp.stDispWin.width /= 2;
            }
            else if(MApi_XC_Get_3D_Output_Mode() == E_XC_3D_OUTPUT_TOP_BOTTOM)
            {
          #if MirrorEnable
               if(MApp_Image_GetMirror())
               {
                    stXC_SetWin_Info_Main_Temp.stDispWin.y += stXC_SetWin_Info_Main_Temp.stDispWin.height/2;
                }
               else
                {
                     stXC_SetWin_Info_Sub_Temp.stDispWin.y += stXC_SetWin_Info_Sub_Temp.stDispWin.height/2;
                }
            #else
                stXC_SetWin_Info_Sub_Temp.stDispWin.y += stXC_SetWin_Info_Sub_Temp.stDispWin.height/2;
         #endif
                stXC_SetWin_Info_Main_Temp.stDispWin.height /= 2;
                stXC_SetWin_Info_Sub_Temp.stDispWin.height /= 2;
            }
            MApp_3D_AdjustIndividualDisplayWin(&stXC_SetWin_Info_Main_Temp, MAIN_WINDOW, enVideoScreen);
            MApp_3D_AdjustIndividualDisplayWin(&stXC_SetWin_Info_Sub_Temp, SUB_WINDOW, enVideoScreen);
            stXC_SetWin_Info_Main_Temp.stDispWin.x += g_IPanel.HStart();
            stXC_SetWin_Info_Main_Temp.stDispWin.y += g_IPanel.VStart();
            stXC_SetWin_Info_Sub_Temp.stDispWin.x += g_IPanel.HStart();
            stXC_SetWin_Info_Sub_Temp.stDispWin.y += g_IPanel.VStart();
            MApi_XC_SetDispWinToReg(&(stXC_SetWin_Info_Main_Temp.stDispWin), MAIN_WINDOW);
            MApi_XC_SetDispWinToReg(&(stXC_SetWin_Info_Sub_Temp.stDispWin), SUB_WINDOW);
        }
    }
#endif

#if ENABLE_MPLAYER_MOVIE
    if((IsStorageInUse()) && (MApp_MPlayer_IsMoviePlaying()) &&
       (E_MPLAYER_MOVIE_PAUSE==MApp_MPlayer_QueryMoviePlayMode()))
    {
        MApi_XC_WaitInputVSync(4, 100, MAIN_WINDOW);//For M10, maximum is 4 filed support, so wait 4 vsync here
        MApi_XC_set_FD_Mask(TRUE);//if set true will cause zoom out 1/4 1080i video crash.
        if(bInputSourceEnabled)
        {
            MApi_XC_DisableInputSource(TRUE, eWindow);
        }
    }
#endif

    // for Dynamic change DLC capture range
    {
        MS_WINDOW_TYPE stDstWin;

        MS_PNL_DST_DispInfo stPNL_DST_DispInfo = {1,1,1,1,1,1,1,1};

        MApi_PNL_GetDstInfo(&stPNL_DST_DispInfo, sizeof(MS_PNL_DST_DispInfo));
        //printf("pDstInfo.DEHST=%u\n", stPNL_DST_DispInfo.DEHST);

        MApi_XC_GetDispWinFromReg(&stDstWin, MAIN_WINDOW);
        //printf("stDstWin.x=%u\n", stDstWin.x);
        //printf("stDstWin.width=%u\n", stDstWin.width);

        stDLC_CapRange.wHStart = stDstWin.x - stPNL_DST_DispInfo.DEHST + 1;

        // patch for display window larger than DE window case in pixel shift function
        if(stDstWin.x >= stPNL_DST_DispInfo.DEHST)
        {
            stDLC_CapRange.wHEnd = stDLC_CapRange.wHStart + stDstWin.width;
        }
        else
        {
            stDLC_CapRange.wHEnd = stPNL_DST_DispInfo.DEHEND - stPNL_DST_DispInfo.DEHST + 1;
        }

        //DLC capture height range need to set (display windows height * 6/8) .
        stDLC_CapRange.wVStart = stDstWin.height/8;
        //stDLC_CapRange.wVEnd = stDLC_CapRange.wVStart + stDstWin.height*3/4;
        stDLC_CapRange.wVEnd = stDLC_CapRange.wVStart*7;

        //printf("DLC Range= %u %u %u %u\n", stDLC_CapRange.wHStart, stDLC_CapRange.wHEnd, stDLC_CapRange.wVStart, stDLC_CapRange.wVEnd);
        MApi_XC_DLC_SetCaptureRange(&stDLC_CapRange);
    }


    // non-linear scaling control
    if (_bEnNonLinearScaling[eWindow] && (stXC_SetWin_Info[eWindow].stDispWin.width != g_IPanel.Width()) ) {
        //ASSERT(0); printf("display window width != panel width and cannot do non-linear scaling\n");
        _bEnNonLinearScaling[eWindow] = FALSE;
    }

    enPQWin = _MApp_Scaler_SCALER_WIN_to_PQ_WIN(eWindow);

    MDrv_PQ_SetNonLinearScaling(enPQWin, 0, _bEnNonLinearScaling[eWindow]);

#if ENABLE_3D_PROCESS
    if(MApp_3D_GetLRSwitchFlag())
    {
        MApi_XC_Set_3D_LR_Frame_Exchg(MAIN_WINDOW);
    }
#endif

    if(_bEnNonLinearScaling[eWindow])
    {
        //If we set a bad Linear scaling setting, then the display will turn bad
        //and we now correct it, it may cause garbage flash out, so must done this in blue screen case
        if(MApi_XC_Check_HNonLinearScaling() == FALSE)
        {
            //If beyond the max offset, then disable non-linear scaling
            _bEnNonLinearScaling[eWindow] = FALSE;
            MDrv_PQ_SetNonLinearScaling(enPQWin, 0, _bEnNonLinearScaling[eWindow]);
        }
    }

#if (MWE_FUNCTION)
    MApi_XC_ACE_MWESetDispWin(stXC_SetWin_Info[eWindow].stDispWin.x, stXC_SetWin_Info[eWindow].stDispWin.y, stXC_SetWin_Info[eWindow].stDispWin.width, stXC_SetWin_Info[eWindow].stDispWin.height);
#endif

#if(ENABLE_CHECK_SET_WIN_RESULT)
    if( g_Scaler_bSetWidnowResult )
    {
        msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_SET_WIN, DISABLE, 0, eWindow);
    }
#endif

    LOG_CHANGE_CHANNEL_TIME_FUNC_END();
}

//********************************************************************************************
// Get saved display window
//   parameter:
//          eWin: MAIN_WINDOW/SUB_WINDOW
//********************************************************************************************
void MApp_Scaler_ResetZoomFactor(EN_MENU_AspectRatio enAspectratio)
{
    S16 s16Left,s16Rigth,s16Up,s16Down;

    s16Left = 0;
    s16Rigth = 0;
    s16Up = 0;
    s16Down = 0;
    switch(enAspectratio)
    {
        case EN_AspectRatio_Zoom1:
            s16Left = 50;
            s16Rigth = 50;
            s16Up = 60;
            s16Down = 60;
            break;

        case EN_AspectRatio_Zoom2:
            s16Left = 100;
            s16Rigth = 100;
            s16Up = 120;
            s16Down = 120;
            break;

        case EN_AspectRatio_Panorama:
            s16Left = 20;
            s16Rigth = 20;
            s16Up = 30;
            s16Down = 30;
            break;

        default:
            break;
    }
    _s16ZoomLeft = s16Left;
    _s16ZoomRight = s16Rigth;
    _s16ZoomUp = s16Up;
    _s16ZoomDown = s16Down;
}

//////////////////////////////////////////////////////////////////
// increment/decrement left zoom factor
// for horizontal shift video, this factor should be independently
// set
// parameter:
//    s16Hfator: increment/decrement count,
//               unit: ZOOM_NUMERATOR/ZOOM_DENUMERATOR
// return:
//    TRUE if really increment/decrement
//    FALSE otherwise
//////////////////////////////////////////////////////////////////
BOOLEAN MApp_Scaler_IncLeftZoomfactor(S16 s16ZoomFator)
{
    if (s16ZoomFator > 0)
    {
        if (_s16ZoomLeft + s16ZoomFator < ZOOM_NUMERATOR_LEFTMAX)
        {
            _s16ZoomLeft += s16ZoomFator;
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        if (_s16ZoomLeft + s16ZoomFator > 0)
        {
            _s16ZoomLeft += s16ZoomFator;
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
}

//////////////////////////////////////////////////////////////////
// increment/decrement right zoom factor
// for horizontal shift video, this factor should be independently
// set
// parameter:
//    s16Hfator: increment/decrement count,
//               unit: ZOOM_NUMERATOR/ZOOM_DENUMERATOR
// return:
//    TRUE if really increment/decrement
//    FALSE otherwise
//////////////////////////////////////////////////////////////////
BOOLEAN MApp_Scaler_IncRightZoomfactor(S16 s16ZoomFator)
{
    if (s16ZoomFator > 0)
    {
        if (_s16ZoomRight+ s16ZoomFator < ZOOM_NUMERATOR_RIGHTMAX)
        {
            _s16ZoomRight += s16ZoomFator;
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        if (_s16ZoomRight + s16ZoomFator > 0)
        {
            _s16ZoomRight += s16ZoomFator;
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
}

//////////////////////////////////////////////////////////////////
// increment/decrement up zoom factor
// for vertical shift video, this factor should be independently
// set
// parameter:
//    s16Hfator: increment/decrement count,
//               unit: ZOOM_NUMERATOR/ZOOM_DENUMERATOR
// return:
//    TRUE if really increment/decrement
//    FALSE otherwise
//////////////////////////////////////////////////////////////////
BOOLEAN MApp_Scaler_IncUpZoomfactor(S16 s16ZoomFator)
{
    if (s16ZoomFator > 0)
    {
        if (_s16ZoomUp + s16ZoomFator < ZOOM_NUMERATOR_UPMAX)
        {
            _s16ZoomUp += s16ZoomFator;
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        if (_s16ZoomUp + s16ZoomFator > 0)
        {
            _s16ZoomUp += s16ZoomFator;
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
}

//////////////////////////////////////////////////////////////////
// increment/decrement down zoom factor
// for vertical shift video, this factor should be independently
// set
// parameter:
//    s16Hfator: increment/decrement count,
//               unit: ZOOM_NUMERATOR/ZOOM_DENUMERATOR
// return:
//    TRUE if really increment/decrement
//    FALSE otherwise
//////////////////////////////////////////////////////////////////
BOOLEAN MApp_Scaler_IncDownZoomfactor(S16 s16ZoomFator)
{
    if (s16ZoomFator > 0)
    {
        if (_s16ZoomDown+ s16ZoomFator < ZOOM_NUMERATOR_DOWNMAX)
        {
            _s16ZoomDown += s16ZoomFator;
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        if (_s16ZoomDown + s16ZoomFator > 0)
        {
            _s16ZoomDown += s16ZoomFator;
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
}

//////////////////////////////////////////////////////////////////
// calculate cropwin by zoom factor
// parameter:
//    pstCropWin [IN/OUT]: cropping window
//////////////////////////////////////////////////////////////////

static void _MApp_Scaler_ZoomCropWin(MS_WINDOW_TYPE *pstCropWin)
{
    U16 x0, y0,x1, y1;

    x0 = (U16)((U32)pstCropWin->width * _s16ZoomLeft / ZOOM_DENUMERATOR);
    y0 = (U16)((U32)pstCropWin->height * _s16ZoomUp / ZOOM_DENUMERATOR);
    x1 = (U16)((U32)pstCropWin->width * _s16ZoomRight / ZOOM_DENUMERATOR);
    y1 = (U16)((U32)pstCropWin->height * _s16ZoomDown / ZOOM_DENUMERATOR);

    x0 &= ~0x1;
    y0 &= ~0x1;
    x1 &= ~0x1;
    y1 &= ~0x1;
    pstCropWin->x += x0;
    pstCropWin->y += y0;
    pstCropWin->x &= ~0x1;
    pstCropWin->y &= ~0x1;

    pstCropWin->width = pstCropWin->width - (x0 + x1);
    pstCropWin->height = pstCropWin->height - (y0 + y1);
}

EN_ASPECT_RATIO_TYPE MApp_Scaler_GetAspectRatio(SCALER_WIN eWindow, EN_MENU_AspectRatio eAspect)
{
    EN_ASPECT_RATIO_TYPE eResult;


    DEBUG_ASPECT_RATIO( printf("MApp_Scaler_GetAspectRatio(UI-eAspect=%u)\n", eAspect); );

    _MApp_Scaler_CheckHDMode(eWindow);
    switch (eAspect)
    {
        case EN_AspectRatio_JustScan:
            // If UI(App) want just Scan, should let it "JustScan"
            /*if ( MApi_XC_Sys_IsSrcHD(MAIN_WINDOW) &&
               (IsSrcTypeHDMI(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) ||
                IsSrcTypeYPbPr(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) ||
                IsSrcTypeVga(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))) */
            {
             #if (ENABLE_3D_PROCESS)
                if(MApi_XC_Get_3D_Output_Mode() != E_XC_3D_OUTPUT_MODE_NONE)
                {
                    eResult = VIDEOSCREEN_3D_CENTER;
                }
                else
             #endif
                {
                    eResult = VIDEOSCREEN_JUSTSCAN;
                }
                break;
            }
            /*else
            {
            // same as Oringal
            }*/


        default:
        case EN_AspectRatio_Original: // UI -Auto
            if( SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW) == INPUT_SOURCE_DTV )
            {
            #if (ENABLE_3D_PROCESS)
                if(MApi_XC_Get_3D_Output_Mode() != E_XC_3D_OUTPUT_MODE_NONE)
                {
                    eResult = VIDEOSCREEN_3D_AUTO;
                }
                else
            #endif
                {
                    eResult = VIDEOSCREEN_PROGRAM;
                }

                #if 0//MHEG5_ENABLE
                if ( g_InMHEG5 )
                {
                    if ( g_MHEG5Video.bIFrame || !g_MHEG5Video.bHaveVideo )
                    {
                        eResult = VIDEOSCREEN_FULL;
                    }
                }
                #endif
            }
            else if( SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW) == INPUT_SOURCE_STORAGE )
            {
            #if (ENABLE_3D_PROCESS)
                if(MApi_XC_Get_3D_Output_Mode() != E_XC_3D_OUTPUT_MODE_NONE)
                {
                    eResult = VIDEOSCREEN_3D_FULL;
                }
                else
            #endif
                {
                    eResult= VIDEOSCREEN_MM_KEEP_RATIO_AND_SCALE; // H and V scale to fit panel
                }
            }
            else if ( IsSrcTypeYPbPr(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
                    || IsSrcTypeHDMI(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) )
            {
                if( MApp_PCMode_IsAspectRatioWide(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) == TRUE )
                {
                #if (ENABLE_3D_PROCESS)
                    if(MApi_XC_Get_3D_Output_Mode() != E_XC_3D_OUTPUT_MODE_NONE)
                    {
                        eResult = VIDEOSCREEN_3D_FULL;
                    }
                    else
                #endif
                    {
                        eResult = VIDEOSCREEN_FULL;
                    }
                }
                else
                {
                #if (ENABLE_3D_PROCESS)
                    if(MApi_XC_Get_3D_Output_Mode() != E_XC_3D_OUTPUT_MODE_NONE)
                    {
                        eResult = VIDEOSCREEN_3D_AUTO;
                    }
                    else
                #endif
                    {
                        eResult = VIDEOSCREEN_FULL;
                    }
                }
            }
            else if( IsSrcTypeDigitalVD(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
            { // ATV, SCART, AV
                U8 u8WSSARCType;
                //WSS information only for wide panel
                if (!(g_IPanel.AspectRatio()==E_PNL_ASPECT_RATIO_WIDE))
                {
                    #if (ENABLE_3D_PROCESS)
                    if(MApi_XC_Get_3D_Output_Mode() != E_XC_3D_OUTPUT_MODE_NONE)
                    {
                        eResult = VIDEOSCREEN_3D_AUTO;
                    }
                    else
                    {
                        eResult = VIDEOSCREEN_NORMAL;
                    }
                    #else
                    eResult = VIDEOSCREEN_NORMAL;
                    #endif
                }
                else
                {
                    u8WSSARCType = msAPI_AVD_GetAspectRatioCode();

                    switch(u8WSSARCType)
                    {
                        case ARC4x3_FULL:
                        eResult  =   VIDEOSCREEN_NORMAL;
                        break;

                        case ARC14x9_LETTERBOX_CENTER:
                        case ARC14x9_FULL_CENTER:
                        eResult = VIDEOSCREEN_WSS_14by9_LETTERBOX_CENTER;
                        break;

                        case ARC14x9_LETTERBOX_TOP:
                        eResult = VIDEOSCREEN_WSS_14by9_LETTERBOX_TOP;
                        break;

                        case ARC16x9_LETTERBOX_CENTER:
                        case ARC_ABOVE16x9_LETTERBOX_CENTER:
                        eResult = VIDEOSCREEN_WSS_16by9_LETTERBOX_CENTER;
                        break;

                        case ARC16x9_LETTERBOX_TOP:
                        eResult = VIDEOSCREEN_WSS_16by9_LETTERBOX_TOP;
                        break;

                        case ARC16x9_ANAMORPHIC:
                        eResult = VIDEOSCREEN_FULL;
                        break;

                        case ARC_INVALID:
                        eResult = VIDEOSCREEN_FULL;
                        break;

                        default:
                        eResult = VIDEOSCREEN_NORMAL;
                        break;
                    }
                }
            }
            else //PC
            {
                #if (ENABLE_3D_PROCESS)
                if(MApi_XC_Get_3D_Output_Mode() != E_XC_3D_OUTPUT_MODE_NONE)
                {
                    eResult = VIDEOSCREEN_3D_AUTO;
                }
                else
                {
                    eResult = VIDEOSCREEN_NORMAL;
                }
                #else
                eResult = VIDEOSCREEN_NORMAL;
                #endif
            }
            break;
            /*
            case EN_AspectRatio_Full:
            eResult = VIDEOSCREEN_FULL;
            break;
            */
            case EN_AspectRatio_4X3:
             if( IsSrcTypeStorage(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW) ))
             {
                eResult= VIDEOSCREEN_MM_4_3; // H and V scale to fit panel
             }
             else
             {
                if ((g_IPanel.AspectRatio()==E_PNL_ASPECT_RATIO_WIDE))
                   eResult = VIDEOSCREEN_NORMAL;
                else
                   eResult = VIDEOSCREEN_FULL;
              }
              break;

        case EN_AspectRatio_16X9:
            if( IsSrcTypeStorage(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW) ))
            {
                eResult= VIDEOSCREEN_MM_16_9; // H and V scale to fit panel
            }
            else
            {
                if ((g_IPanel.AspectRatio()==E_PNL_ASPECT_RATIO_WIDE))
               {
                  #if (ENABLE_3D_PROCESS)
                    if(MApi_XC_Get_3D_Output_Mode() != E_XC_3D_OUTPUT_MODE_NONE)
                    {
                         eResult = VIDEOSCREEN_3D_FULL;
                    }
                   else
                   {
                         eResult = VIDEOSCREEN_FULL;
                   }
                   #else
                     eResult = VIDEOSCREEN_FULL;
                   #endif
                }
                else
                 {
                    eResult = VIDEOSCREEN_NORMAL;
                 }
             }
            break;

        case EN_AspectRatio_14X9:
            eResult = VIDEOSCREEN_14by9;
            break;

        case EN_AspectRatio_Zoom1:
            eResult = VIDEOSCREEN_ZOOM1;
            break;

        case EN_AspectRatio_Zoom2:
            eResult = VIDEOSCREEN_ZOOM2;
            break;
        case EN_AspectRatio_Panorama:
            eResult = VIDEOSCREEN_PANORAMA;
            break;

        case EN_AspectRatio_Point_to_Point:
            if(MApi_XC_IsCurrentFrameBufferLessMode()||MApi_XC_IsCurrentRequest_FrameBufferLessMode())
            {
                  eResult = VIDEOSCREEN_FULL;
                  //ST_VIDEO.eAspectRatio = EN_AspectRatio_16X9;
            }
            else
            {
                  eResult = VIDEOSCREEN_POINT_TO_POINT;
            }
            break;
    }

    DEBUG_ASPECT_RATIO( printf(" => VIDEOSCREEN_xxx=%u\n", eResult); );

    return eResult;
}

static U8 _MApp_Scaler_Resolution_Remapping(XC_SETWIN_INFO *pstXC_SetWin_Info, SCALER_WIN eWindow )
{
    U16 u16HSize, u16VSize, u16InputVFreq;
    U8 u8_Resolution=E_YPbPr480i_60;

    if(IsYPbPrInUse())
    {
        u16HSize = MApp_PCMode_Get_HResolution(eWindow,TRUE);
        u16VSize = MApp_PCMode_Get_VResolution(eWindow,TRUE);
    }
    else
    {
        u16HSize = pstXC_SetWin_Info->stCapWin.width;
        u16VSize = pstXC_SetWin_Info->stCapWin.height;
    }

    MSG(printf("\r\n _MApp_Scaler_Resolution_Remapping -> Mode H Size = %d",u16HSize));
    MSG(printf("\r\n _MApp_Scaler_Resolution_Remapping -> Mode V Size = %d\n",u16VSize));

    u16InputVFreq = pstXC_SetWin_Info->u16InputVFreq;

    if(IsSrcTypeYPbPr(SYS_INPUT_SOURCE_TYPE(eWindow)))
    {
        switch(g_PcadcModeSetting[eWindow].u8ModeIndex)
        {
            case MD_720x480_60I:
                u8_Resolution = E_YPbPr480i_60;
                break;
            case MD_720x480_60P:
                u8_Resolution = E_YPbPr480p_60;
                break;
            case MD_720x576_50I:
                u8_Resolution = E_YPbPr576i_50;
                break;
            case MD_720x576_50P:
                u8_Resolution = E_YPbPr576p_50;
                break;
            case MD_1280x720_60P:
                u8_Resolution = E_YPbPr720p_60;
                break;
            case MD_1280x720_50P:
                u8_Resolution = E_YPbPr720p_50;
                break;
            case MD_1280x720_25P:
                u8_Resolution = E_YPbPr720p_25;
                break;
            case MD_1280x720_30P:
                u8_Resolution = E_YPbPr720p_30;
                break;
            case MD_1920x1080_60I:
                u8_Resolution = E_YPbPr1080i_60;
                break;
            case MD_1920x1080_50I:
                u8_Resolution = E_YPbPr1080i_50;
                break;
            case MD_1920x1080_60P:
                u8_Resolution = E_YPbPr1080p_60;
                break;
            case MD_1920x1080_50P:
                u8_Resolution = E_YPbPr1080p_50;
                break;
            case MD_1920x1080_30P:
                u8_Resolution = E_YPbPr1080p_30;
                break;
            case MD_1920x1080_24P:
                u8_Resolution = E_YPbPr1080p_24;
                break;
             case MD_1920x1080_25P:
                u8_Resolution = E_YPbPr1080p_25;
                break;
           #if (SUPPORT_EURO_HDTV)
            case  MD_1920x1080_50I_EURO:
                u8_Resolution = E_YPbPr108oi_25;
                break;
           #endif
            default:
                u8_Resolution = E_YPbPr480i_60;
                break;
        }
    }
    else if(IsSrcTypeHDMI(SYS_INPUT_SOURCE_TYPE(eWindow)))
    {
        if((u16HSize>=630 && u16HSize<=650) && (u16VSize>=470 && u16VSize<=490))
        {// 640
            if(pstXC_SetWin_Info->bInterlace)
            {// 480i
               u8_Resolution = E_HDMI640x480i_60;
            }
            else
            {// 480p
               u8_Resolution = E_HDMI640x480P_60;
            }
        }
        else if((u16HSize>=710 && u16HSize<=730) && (u16VSize>=470 && u16VSize<=490))
        {// 720
            if(pstXC_SetWin_Info->bInterlace)
            {// 480i
               u8_Resolution = E_HDMI480i_60;
            }
            else
            {// 480p
               u8_Resolution = E_HDMI480p_60;
            }
        }
        else if((u16HSize>=710 && u16HSize<=730) && (u16VSize>=566 && u16VSize<=586))
        {// 720
            if(pstXC_SetWin_Info->bInterlace)
            {// 576i
               u8_Resolution = E_HDMI576i_50;
            }
            else
            {// 576p
               u8_Resolution = E_HDMI576p_50;
            }
        }
        else if((u16HSize>=1430 && u16HSize<=1450) && (u16VSize>=470 && u16VSize<=490))
        {// 720
            if(pstXC_SetWin_Info->bInterlace)
            {// 480i
               u8_Resolution = E_HDMI1440x480i_60;
            }
            else
            {// 480p
               u8_Resolution = E_HDMI1440x480p_60;
            }
        }
        else if((u16HSize>=1430 && u16HSize<=1450) && (u16VSize>=566 && u16VSize<=586))
        {// 720
            if(pstXC_SetWin_Info->bInterlace)
            {// 576i
               u8_Resolution = E_HDMI1440x576i_50;
            }
            else
            {// 576p
               u8_Resolution = E_HDMI1440x576p_50;
            }
        }
        else if((u16HSize>=1270 && u16HSize<=1290) && (u16VSize>=710 && u16VSize<=730))
        {// 1280
            // 720P
            if( u16InputVFreq > 550 )
               u8_Resolution = E_HDMI720p_60;
            else
                u8_Resolution = E_HDMI720p_50;
        }
        else if((u16HSize>=1910 && u16HSize<=1930) && (u16VSize>=1070 && u16VSize<=1090))
        {// 1920
            if (pstXC_SetWin_Info->bInterlace)
            {//1080i
                if( u16InputVFreq > 550 )
                   u8_Resolution = E_HDMI1080i_60;
                else
                    u8_Resolution = E_HDMI1080i_50;
            }
            else
            {
                if( u16InputVFreq > 550 )
                {// 1080P (60)
                   u8_Resolution = E_HDMI1080p_60;
                }
                else if( u16InputVFreq > 450 )
                {// 1080P (50)
                   u8_Resolution = E_HDMI1080p_50;
                }
                else if( u16InputVFreq > 275 )
                {// 1080P (30)
                   u8_Resolution = E_HDMI1080p_30;
                }
                else if( u16InputVFreq > 200 )
                {// 1080P (24P)
                   u8_Resolution = E_HDMI1080p_24;
                }
            }
        }
        else
        {
            u8_Resolution = E_HDMI640x480P_60;   //default use 480p
            //  no suitable value given.
            //__ASSERT( 0 );
        }
    }
    MSG(printf("\r\n _MApp_Scaler_Resolution_Remapping -> u8_Resolution = %d\n",u8_Resolution));
    return u8_Resolution;
}

static U8 _MApp_Scaler_Aspect_Ratio_Remapping(EN_ASPECT_RATIO_TYPE enVideoScreen)
{
    U8 u8_AR_NUM;

    switch(enVideoScreen)
    {
        case VIDEOSCREEN_FULL:
            u8_AR_NUM = E_AR_16x9;
            break;
        case VIDEOSCREEN_NORMAL:
            u8_AR_NUM = E_AR_4x3;
            break;
//        case VIDEOSCREEN_FULL:
//            u8_AR_NUM = E_AR_AUTO;
            break;
        case VIDEOSCREEN_PANORAMA:
            u8_AR_NUM = E_AR_Panorama;
            break;
        case VIDEOSCREEN_JUSTSCAN:
            u8_AR_NUM = E_AR_JustScan;
            break;
        case VIDEOSCREEN_ZOOM2:
            u8_AR_NUM = E_AR_Zoom2;
            break;
        case VIDEOSCREEN_ZOOM1:
            u8_AR_NUM = E_AR_Zoom1;
            break;
        default:
            u8_AR_NUM = E_AR_AUTO;
            break;
    }
    MSG(printf("Scaler aspect ratio remap: %u -> %u \n", enVideoScreen, u8_AR_NUM));
    return u8_AR_NUM;

}

void MApp_Scaler_EnableOverScan_2(BOOLEAN bEnable)
{
    DEBUG_OVERSCAN( printf("MApp_Scaler_EnableOverScan(bEnable=%u)\n", bEnable); );
    _u8EnableOverScan = bEnable;
}

//-----------------------------------------------------------------------------
// Get Over Scan Ratio from table
//-----------------------------------------------------------------------------
void MApp_Scaler_GetOverScan(INPUT_SOURCE_TYPE_t enInputSrcType, XC_SETWIN_INFO *pstXC_SetWin_Info)
{
    U16 u16HSize, u16VSize;
    U8 u8_AspectRatio;
    U8 u8_Resolution;
    //MS_VIDEO_Window_Info *pstVideoWinInfo;

    DEBUG_OVERSCAN( printf("MApp_Scaler_GetOverScan()\n"); );

    u16HSize = pstXC_SetWin_Info->stCapWin.width;
    u16VSize = pstXC_SetWin_Info->stCapWin.height;

    u8_AspectRatio = _MApp_Scaler_Aspect_Ratio_Remapping(stSystemInfo[MAIN_WINDOW].enAspectRatio);
    if( IsSrcTypeYPbPr(enInputSrcType) || IsSrcTypeHDMI(enInputSrcType) )
        u8_Resolution = _MApp_Scaler_Resolution_Remapping( pstXC_SetWin_Info, MAIN_WINDOW );
    else
        u8_Resolution = 0;

    if(IsSrcTypeYPbPr(enInputSrcType)) // Coverity 90814 // For Fix coverity #208460 - Overrunning array.
    {
        if( u8_Resolution >= E_YPbPr_MAX )
        {
            u8_Resolution = 0;
        }
    }
    else
    {
        u8_Resolution = 0;
    }

    //clear static value
    _u8H_CropRatio_Left = st_VidWin_Info.u8HCrop_Left = 0;
    _u8H_CropRatio_Right = st_VidWin_Info.u8HCrop_Right = 0;
    _u8V_CropRatio_Up = st_VidWin_Info.u8VCrop_Up = 0;
    _u8V_CropRatio_Down = st_VidWin_Info.u8VCrop_Down = 0;
    _u8H_OverScanRatio = st_VidWin_Info.u8H_OverScanRatio = 0;
    _u8V_OverScanRatio = st_VidWin_Info.u8V_OverScanRatio = 0;

    //printf("Vidoe AR = %bx,%bx,Res = %bx\n",stSystemInfo.enAspectRatio,u8_AspectRatio,u8_Resolution);

    if(IsSrcTypeDTV(enInputSrcType) ||
      (IsSrcTypeStorage(enInputSrcType) && !IsSrcTypeJpeg(enInputSrcType))) // storage type except JPEG
    {
        if(u16HSize <= 750 && u16VSize <= 500)
        {
           if(pstXC_SetWin_Info->bInterlace)
           {// 480i
                _u8H_OverScanRatio = _u16OverscanDtv480iH;
                _u8V_OverScanRatio = _u16OverscanDtv480iV;
                //patch:  [Boxer].DNK/776 services 'AVCSD1', 'AVCSD2', and 'AVCSD6','AVCSD3', 'AVCSD4', and 'AVCSD5'
                //Boundary line with arrows should be visible without any cut.
                #if ENABLE_BOXER_OVERSCAN_PATCH
                    if((u16HSize==704)&&(u16VSize==288))
                    {//288i
                        _u8H_OverScanRatio = 0;
                       _u8V_OverScanRatio  = 0;
                    }
                #endif
           }
           else
           {// 480p
                _u8H_OverScanRatio = _u16OverscanDtv480pH;
                _u8V_OverScanRatio = _u16OverscanDtv480pV;
           }
        }
        else if(u16HSize <= 750 && u16VSize <= 600)
        {
            if (pstXC_SetWin_Info->bInterlace)
            {// 576i
                _u8H_OverScanRatio = _u16OverscanDtv576iH;
                _u8V_OverScanRatio = _u16OverscanDtv576iV;
                //patch:  [Boxer].DNK/776 services 'AVCSD1', 'AVCSD2', and 'AVCSD6','AVCSD3', 'AVCSD4', and 'AVCSD5'
                //Boundary line with arrows should be visible without any cut.
                #if ENABLE_BOXER_OVERSCAN_PATCH
                    if((u16HSize==704||u16HSize==720)&&(u16VSize==576))
                    {//576i
                        _u8H_OverScanRatio = 0;
                       _u8V_OverScanRatio  = 0;
                    }
                #endif
            }
            else
            {// 576p
                _u8H_OverScanRatio = _u16OverscanDtv576pH;
                _u8V_OverScanRatio = _u16OverscanDtv576pV;
                //patch:  [Boxer].DNK/776 services 'AVCSD1', 'AVCSD2', and 'AVCSD6','AVCSD3', 'AVCSD4', and 'AVCSD5'
                //Boundary line with arrows should be visible without any cut.
                #if ENABLE_BOXER_OVERSCAN_PATCH
                    if((u16HSize==704)&&(u16VSize==576))
                    {//576p
                        _u8H_OverScanRatio = 0;
                       _u8V_OverScanRatio  = 0;
                    }
                #endif
            }
        }
        else if(u16HSize <= 1300 && u16VSize <= 750)
        {   //720P
            _u8H_OverScanRatio = _u16OverscanDtv720pH;
            _u8V_OverScanRatio = _u16OverscanDtv720pV;
            //patch:  [Boxer].DNK/776 services 'AVCSD1', 'AVCSD2', and 'AVCSD6','AVCSD3', 'AVCSD4', and 'AVCSD5'
            //Boundary line with arrows should be visible without any cut.
            #if ENABLE_BOXER_OVERSCAN_PATCH
                if (pstXC_SetWin_Info->bInterlace)
                {//576i
                    if((u16HSize==1088||u16HSize==960)&&(u16VSize==576))
                    {
                        _u8H_OverScanRatio = 0;
                       _u8V_OverScanRatio  = 0;
                    }
                }
            #endif
        }
        else if(u16HSize <= 1950 && u16VSize <= 1200)
        {
            if (pstXC_SetWin_Info->bInterlace)
            {//1080i
                _u8H_OverScanRatio = _u16OverscanDtv1080iH;
                _u8V_OverScanRatio = _u16OverscanDtv1080iV;
            }
            else
            {// 1080P
                _u8H_OverScanRatio = _u16OverscanDtv1080pH;
                _u8V_OverScanRatio = _u16OverscanDtv1080pV;
            }
        }

        st_VidWin_Info.u8H_OverScanRatio =  _u8H_OverScanRatio;
        st_VidWin_Info.u8V_OverScanRatio =  _u8V_OverScanRatio;

     }
    else if(IsSrcTypeYPbPr(enInputSrcType))
    {
        _u8H_CropRatio_Left = YPbPr_WinInfo[u8_Resolution][u8_AspectRatio].u8HCrop_Left;
        _u8H_CropRatio_Right = YPbPr_WinInfo[u8_Resolution][u8_AspectRatio].u8HCrop_Right;
        _u8V_CropRatio_Up = YPbPr_WinInfo[u8_Resolution][u8_AspectRatio].u8VCrop_Up;
        _u8V_CropRatio_Down = YPbPr_WinInfo[u8_Resolution][u8_AspectRatio].u8VCrop_Down;
    }
    else if(IsSrcTypeDigitalVD(enInputSrcType))
    {
        EN_VD_SIGNALTYPE eVdSignalType = mvideo_vd_get_videosystem();

        //pstVideoWinInfo = &CVBS_WinInfo[mvideo_vd_get_videosystem()][u8_AspectRatio];

        DEBUG_OVERSCAN( printf("eVdSignalType=%u\n", eVdSignalType); );
        DEBUG_OVERSCAN(printf("u8_AspectRatio=%u\n", u8_AspectRatio););

        _u8H_CropRatio_Left = CVBS_WinInfo[eVdSignalType][u8_AspectRatio].u8HCrop_Left;
        _u8H_CropRatio_Right = CVBS_WinInfo[eVdSignalType][u8_AspectRatio].u8HCrop_Right;
        _u8V_CropRatio_Up = CVBS_WinInfo[eVdSignalType][u8_AspectRatio].u8VCrop_Up;
        _u8V_CropRatio_Down = CVBS_WinInfo[eVdSignalType][u8_AspectRatio].u8VCrop_Down;

        DEBUG_OVERSCAN(printf("_u8H_CropRatio_Left=%u\n", _u8H_CropRatio_Left););
        DEBUG_OVERSCAN(printf("_u8H_CropRatio_Right=%u\n", _u8H_CropRatio_Right););
        DEBUG_OVERSCAN(printf("_u8V_CropRatio_Up=%u\n", _u8V_CropRatio_Up););
        DEBUG_OVERSCAN(printf("_u8V_CropRatio_Down=%u\n", _u8V_CropRatio_Down););

        //_u8H_CropRatio_Left = 0;
        //_u8H_CropRatio_Right = 0;
    }
#if (INPUT_HDMI_VIDEO_COUNT>0)
   else if(IsSrcTypeHDMI(enInputSrcType) && (g_HdmiPollingStatus.bIsHDMIMode == TRUE)&&(u8_Resolution<E_HDMI_MAX))
    //else if(IsSrcTypeHDMI(enInputSrcType))
    {  // make sure this is HDMI mode, not DVI mode
        _u8H_CropRatio_Left = HDMI_WinInfo[u8_Resolution][u8_AspectRatio].u8HCrop_Left;
        _u8H_CropRatio_Right = HDMI_WinInfo[u8_Resolution][u8_AspectRatio].u8HCrop_Right;
        _u8V_CropRatio_Up = HDMI_WinInfo[u8_Resolution][u8_AspectRatio].u8VCrop_Up;
        _u8V_CropRatio_Down = HDMI_WinInfo[u8_Resolution][u8_AspectRatio].u8VCrop_Down;

        /*printf("HDMI src type [%bu][%bu]\n\n===========",u8_Resolution, u8_AspectRatio);
        printf("HDMI src type !==========\n\nCropRatio Hstart, Vstart, left, right, up, down = 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x\n",
               HDMI_WinInfo[u8_Resolution][u8_AspectRatio].u16H_CapStart,
               HDMI_WinInfo[u8_Resolution][u8_AspectRatio].u16V_CapStart,
               HDMI_WinInfo[u8_Resolution][u8_AspectRatio].u8HCrop_Left,
               HDMI_WinInfo[u8_Resolution][u8_AspectRatio].u8HCrop_Right,
               HDMI_WinInfo[u8_Resolution][u8_AspectRatio].u8VCrop_Up,
               HDMI_WinInfo[u8_Resolution][u8_AspectRatio].u8VCrop_Down
               );*/

    }
#endif
    else
    {
        _u8H_CropRatio_Left = 0;
        _u8H_CropRatio_Right = 0;
        _u8V_CropRatio_Up = 0;
        _u8V_CropRatio_Down = 0;
    }

    st_VidWin_Info.u8H_OverScanRatio = _u8H_OverScanRatio;
    st_VidWin_Info.u8V_OverScanRatio = _u8V_OverScanRatio;
    st_VidWin_Info.u8HCrop_Left = _u8H_CropRatio_Left;
    st_VidWin_Info.u8HCrop_Right = _u8H_CropRatio_Right;
    st_VidWin_Info.u8VCrop_Up = _u8V_CropRatio_Up;
    st_VidWin_Info.u8VCrop_Down = _u8V_CropRatio_Down;

}

//-----------------------------------------------------------------------------
static void _MApp_Scaler_CalculateOverScan(INPUT_SOURCE_TYPE_t enInputSrcType, MS_WINDOW_TYPE *pstCropWin)
{
    U32 u32Temp, u32Temp2;

#if ENABLE_SZ_FACTORY_OVER_SCAN_FUNCTION
    u32Temp2=0;//avoid compolier error

    MApp_LoadOverScanData();

    DEBUG_OVERSCAN(printf("G_OVERSCAN_HRatio=%u\n", G_OVERSCAN_HRatio););
    DEBUG_OVERSCAN(printf("G_OVERSCAN_HPOSITION=%u\n", G_OVERSCAN_HPOSITION););
    DEBUG_OVERSCAN(printf("G_OVERSCAN_VRatio=%u\n", G_OVERSCAN_VRatio););
    DEBUG_OVERSCAN(printf("G_OVERSCAN_VPOSITION=%u\n", G_OVERSCAN_VPOSITION););

    enInputSrcType=enInputSrcType;//avoid compolier error
    _u8H_OverScanRatio = G_OVERSCAN_HRatio;
    _u8V_OverScanRatio = G_OVERSCAN_VRatio;

    DEBUG_OVERSCAN(printf("_u8H_OverScanRatio=%u\n", _u8H_OverScanRatio););
    DEBUG_OVERSCAN(printf("_u8V_OverScanRatio=%u\n", _u8V_OverScanRatio););


    if (_u8H_OverScanRatio) // Horizontal
    {
        u32Temp = ((U32)pstCropWin->width * (U32)_u8H_OverScanRatio + 500 )/OVERSCAN_RATIO;

        DEBUG_OVERSCAN(printf("u32Temp=%u\n", u32Temp););

        pstCropWin->x += (U16) u32Temp;
        pstCropWin->width = pstCropWin->width - (U16)u32Temp*2;

        DEBUG_OVERSCAN(printf("pstCropWin->x=%u\n", pstCropWin->x););
        DEBUG_OVERSCAN(printf("pstCropWin->width=%u\n", pstCropWin->width););

        if((G_OVERSCAN_HPOSITION < 0)&&(-G_OVERSCAN_HPOSITION >= (pstCropWin->x-1)))
        {
            pstCropWin->x=1;
        }
        else
        {
            pstCropWin->x += G_OVERSCAN_HPOSITION;
        }

        DEBUG_OVERSCAN(printf("pstCropWin->x=%u\n", pstCropWin->x););
        //MSG(printf("pstCropWin->width=%u\n", pstCropWin->width););

    }

    if (_u8V_OverScanRatio) // Vertical
    {
        u32Temp = ((U32)pstCropWin->height * (U32)_u8V_OverScanRatio + 500 )/OVERSCAN_RATIO;
        pstCropWin->y += (U16) u32Temp;
        pstCropWin->height = pstCropWin->height - (U16)u32Temp*2;

        if((G_OVERSCAN_VPOSITION<0)&&(-G_OVERSCAN_VPOSITION >= (pstCropWin-> y-1)))
        {
            pstCropWin->y = 1;
        }
        else
        {
            pstCropWin->y += G_OVERSCAN_VPOSITION;
        }
    }
#else
    if(IsSrcTypeDTV(enInputSrcType) ||
      (IsSrcTypeStorage(enInputSrcType) && !IsSrcTypeJpeg(enInputSrcType))) // storage type except JPEG
    {
        if (_u8H_OverScanRatio) // Horizontal
        {
            u32Temp = ((U32)pstCropWin->width * (U32)_u8H_OverScanRatio + 500 )/OVERSCAN_RATIO;
            pstCropWin->x += (U16) u32Temp;
            pstCropWin->width = pstCropWin->width - (U16)u32Temp*2;
        }

        if (_u8V_OverScanRatio) // Vertical
        {
            u32Temp = ((U32)pstCropWin->height * (U32)_u8V_OverScanRatio + 500 )/OVERSCAN_RATIO;
            pstCropWin->y += (U16) u32Temp;
            pstCropWin->height = pstCropWin->height - (U16)u32Temp*2;
        }
        //printf("OVS H=%bx,V=%bx\n",_u8H_OverScanRatio,_u8V_OverScanRatio);
    }
    else
    {
        MSG(printf("OVS L=%u, R=%u\n", _u8H_CropRatio_Left, _u8H_CropRatio_Right));
        MSG(printf("OVS U=%bx,D=%bx\n",_u8V_CropRatio_Up, _u8V_CropRatio_Down));

        // Horizontal
        u32Temp = u32Temp2 = 0;
        if (_u8H_CropRatio_Left)
            u32Temp = ((U32)pstCropWin->width * (U32)_u8H_CropRatio_Left + 500 )/OVERSCAN_RATIO;

        if (_u8H_CropRatio_Right)
            u32Temp2 = ((U32)pstCropWin->width * (U32)_u8H_CropRatio_Right + 500 )/OVERSCAN_RATIO;

        pstCropWin->x += (U16) u32Temp;
        pstCropWin->width -= (U16)(u32Temp + u32Temp2);

        // Vertical
        u32Temp = u32Temp2 = 0;
        if (_u8V_CropRatio_Up)
            u32Temp = ((U32)pstCropWin->height * (U32)_u8V_CropRatio_Up + 500 )/OVERSCAN_RATIO;

        if (_u8V_CropRatio_Down)
            u32Temp2 = ((U32)pstCropWin->height * (U32)_u8V_CropRatio_Down + 500 )/OVERSCAN_RATIO;

        pstCropWin->y += (U16) u32Temp;
        pstCropWin->height -= (U16)(u32Temp + u32Temp2);
    }
#endif
}

void MApp_Scaler_CalculateAspectRatio(XC_SETWIN_INFO *pstXC_SetWin_Info,
                                       EN_ASPECT_RATIO_TYPE enVideoScreen,
                                       MS_WINDOW_TYPE *pstCropWin,
                                       MS_WINDOW_TYPE *pstDstWin)
{
    U16 u16Temp;

    //restore according to my setting history

    if ( enVideoScreen != VIDEOSCREEN_PANORAMA)
    {
        _bEnNonLinearScaling[MAIN_WINDOW] = FALSE;
    }

    if(enVideoScreen ==VIDEOSCREEN_ORIGIN)
    {
        if(IsATVInUse())
        {
            enVideoScreen = VIDEOSCREEN_NORMAL;
        }
        else
        {
            enVideoScreen = VIDEOSCREEN_NORMAL;
        }
    }

    DEBUG_ASPECT_RATIO( printf("enVideoScreen=%u\n", enVideoScreen); );

    if( (enVideoScreen == VIDEOSCREEN_JUSTSCAN)||
        (enVideoScreen == VIDEOSCREEN_POINT_TO_POINT)||
        ( (enVideoScreen >= VIDEOSCREEN_MM_KEEP_RATIO_AND_SCALE)
         &&(enVideoScreen <= VIDEOSCREEN_MM_CAL_BY_VIDEOPLAYER)
        )
      )
    {
        MApp_Scaler_EnableOverScan(DISABLE);
    }
    else
    {
        MApp_Scaler_EnableOverScan(ENABLE);
    }

    if( MApi_XC_IsCurrentFrameBufferLessMode()||MApi_XC_IsCurrentRequest_FrameBufferLessMode())
    {
         MApp_Scaler_EnableOverScan(FALSE);
         if( enVideoScreen == VIDEOSCREEN_POINT_TO_POINT )
            enVideoScreen = VIDEOSCREEN_JUSTSCAN;
    }

    DEBUG_ASPECT_RATIO( printf("Set PQ-PTP=0\n"); );
    MDrv_PQ_Set_PointToPoint(pstXC_SetWin_Info, FALSE, PQ_MAIN_WINDOW);

    switch( enVideoScreen )
    {
        case VIDEOSCREEN_PROGRAM_16X9:
            DEBUG_ASPECT_RATIO(printf("VIDEOSCREEN_PROGRAM_16X9\n"));
            break;

        case VIDEOSCREEN_PROGRAM_4X3:
            DEBUG_ASPECT_RATIO(printf("VIDEOSCREEN_PROGRAM_4X3\n"));
            u16Temp = (U32)pstDstWin->height * 4 / 3;
            if (u16Temp <= pstDstWin->width) // H:V >= 4:3
            {
                pstDstWin->x += (pstDstWin->width - u16Temp) / 2;
                pstDstWin->width = u16Temp;
            }
            else // H:V <= 4:3
            {
                u16Temp = (U32)pstDstWin->width * 3 / 4;
                pstDstWin->y += (pstDstWin->height - u16Temp) / 2;
                pstDstWin->height = u16Temp;
            }
            break;

        case VIDEOSCREEN_FULL:
            DEBUG_ASPECT_RATIO(printf("VIDEOSCREEN_FULL\n"));
            pstDstWin->x = 0;
            pstDstWin->y = 0;
            pstDstWin->width = g_IPanel.Width();
            pstDstWin->height = g_IPanel.Height();
        default:
            break;

        case VIDEOSCREEN_ZOOM:
        case VIDEOSCREEN_ZOOM1:
            DEBUG_ASPECT_RATIO(printf("VIDEOSCREEN_ZOOM\n"));
            MApp_Scaler_ResetZoomFactor(EN_AspectRatio_Zoom1);
            _MApp_Scaler_ZoomCropWin(pstCropWin);
            break;

        case VIDEOSCREEN_ZOOM2:
            DEBUG_ASPECT_RATIO(printf("VIDEOSCREEN_ZOOM2\n"));
            MApp_Scaler_ResetZoomFactor(EN_AspectRatio_Zoom2);
            _MApp_Scaler_ZoomCropWin(pstCropWin);
            break;

         case VIDEOSCREEN_JUSTSCAN: // Disable OverScan
            DEBUG_ASPECT_RATIO(printf("VIDEOSCREEN_JUSTSCAN\n"));
            pstDstWin->x = 0;
            pstDstWin->y = 0;
            pstDstWin->width = g_IPanel.Width();
            pstDstWin->height = g_IPanel.Height();

            /*
            if(MDrv_PQ_Check_PointToPoint_Condition(pstXC_SetWin_Info, PQ_MAIN_WINDOW))
            {
                printf("Set PQ-PTP=1\n");
                MDrv_PQ_Set_PointToPoint(pstXC_SetWin_Info, TRUE, PQ_MAIN_WINDOW);
            }
            else
            {
                if(pstCropWin->width <= g_IPanel.Width() )
                {
                    pstDstWin->x = (g_IPanel.Width() - pstCropWin->width)/2;
                    pstDstWin->width = pstCropWin->width;
                }
                else
                {
                    pstDstWin->x = 0;
                    pstDstWin->width = g_IPanel.Width();
                }

                if(pstCropWin->height <= g_IPanel.Height())
                {
                    pstDstWin->y = (g_IPanel.Height() - pstCropWin->height)/2;
                    pstDstWin->height = pstCropWin->height;
                }
                else
                {
                    pstDstWin->y = 0;
                    pstDstWin->height = g_IPanel.Height();
                }
            }
            */
            break;

        case VIDEOSCREEN_PROGRAM: // Set Capture/Crop/Display window by function directly
            DEBUG_ASPECT_RATIO(printf("VIDEOSCREEN_PROGRAM\n"));
            _MApp_Scaler_ZoomCropWin(pstCropWin);
            break;

        case VIDEOSCREEN_CINEMA:
            DEBUG_ASPECT_RATIO(printf("VIDEOSCREEN_CINEMA\n"));
            u16Temp =( ( U32 ) pstCropWin->height * ARC_CINEMA_OVS_V) / 1000;

            pstCropWin->y += u16Temp;
            pstCropWin->height = ( pstCropWin->height - 2 * u16Temp );

            u16Temp = (( U32 ) pstCropWin->width * ARC_CINEMA_OVS_H) / 1000;//
            pstCropWin->x += u16Temp;
            pstCropWin->width = ( pstCropWin->width - 2 * u16Temp );
            break;

        case VIDEOSCREEN_14by9:
            DEBUG_ASPECT_RATIO(printf("VIDEOSCREEN_14by9\n"));
            u16Temp = ((U32) pstCropWin->height * ARC_14X19_OVS_UP + 500) / 1000;
            pstCropWin->y += u16Temp;

            u16Temp += ((U32) pstCropWin->height * ARC_14X19_OVS_DOWN + 500) / 1000;
            pstCropWin->height -= (u16Temp);

            u16Temp = (U32)pstDstWin->height * 14 / 9;
            if (u16Temp <= pstDstWin->width) // H:V >= 14:9
            {
                pstDstWin->x += (pstDstWin->width - u16Temp) / 2;
                pstDstWin->width = u16Temp;
                pstDstWin->width = (pstDstWin->width + 1) & ~1;
            }
            else // H:V <= 4:3
            {
                u16Temp = (U32)pstDstWin->width * 9 / 14;
                pstDstWin->y += (pstDstWin->height - u16Temp) / 2;
                pstDstWin->height = u16Temp;
            }
            break;

        case VIDEOSCREEN_16by9_SUBTITLE: // W?1/8Ai?AU?Odr
            DEBUG_ASPECT_RATIO(printf("VIDEOSCREEN_16by9_SUBTITLE\n"));
            pstCropWin->y += pstCropWin->height * 1 / 8;
            pstCropWin->height = pstCropWin->height * 7 / 8; // * 420 / 480;

            u16Temp = (U32)pstDstWin->height * 32 / 21; // 640x420 => 1097x720 Display
            if (u16Temp <= pstDstWin->width) // H:V >= 32:21
            {
                pstDstWin->x += (pstDstWin->width - u16Temp) / 2;
                pstDstWin->width = u16Temp;
            }
            else // H:V <= 32:21
            {
                u16Temp = (U32)pstDstWin->width * 21 / 32;
                pstDstWin->y += (pstDstWin->height - u16Temp) / 2;
                pstDstWin->height = u16Temp;
            }
            break;

        case VIDEOSCREEN_PANORAMA:
            _bEnNonLinearScaling[MAIN_WINDOW] = TRUE;
            DEBUG_ASPECT_RATIO(printf("VIDEOSCREEN_PANORAMA\n"));
            break;

        case VIDEOSCREEN_NORMAL:
            DEBUG_ASPECT_RATIO(printf("VIDEOSCREEN_NORMAL\n"));
            if ((g_IPanel.AspectRatio()==E_PNL_ASPECT_RATIO_WIDE))
            {
                u16Temp = (U32)pstDstWin->height * 4 / 3;
                if (u16Temp <= pstDstWin->width) // H:V >= 4:3
                {
                    pstDstWin->x += (pstDstWin->width - u16Temp) / 2;
                    pstDstWin->width = u16Temp;
                }
                else // H:V <= 4:3
                {
                    u16Temp = (U32)pstDstWin->width * 3 / 4;
                    pstDstWin->y += (pstDstWin->height - u16Temp) / 2;
                    pstDstWin->height = u16Temp;
                }
            }
            else
            {
                u16Temp = (U32)pstDstWin->width * 9 / 16;
                if(u16Temp <= pstDstWin->width) // H:V <= 16:9
                {
                    pstDstWin->y += (pstDstWin->height - u16Temp)/2;
                    pstDstWin->height = u16Temp;
                }
                else// H:V > 16:9
                {
                    u16Temp = (U32) pstDstWin->width * 16/ 9;
                    pstDstWin->x += (pstDstWin->width - u16Temp)/2;
                    pstDstWin->width = u16Temp;
                }
            }
            break;

        case VIDEOSCREEN_LETTERBOX: // WUd¡A16:9 Display
            //DEBUG_ASPECT_RATIO(printf("%s\n", (enVideoScreen==VIDEOSCREEN_LETTERBOX)?("VIDEOSCREEN_LETTERBOX"):("VIDEOSCREEN_WIDE2")));
            DEBUG_ASPECT_RATIO(printf("VIDEOSCREEN_LETTERBOX\n"));
            u16Temp = (U32)pstDstWin->width * 9 / 16;
            pstDstWin->y += (pstDstWin->height - u16Temp) / 2;
            pstDstWin->height = u16Temp;
            break;

        case VIDEOSCREEN_WSS_16by9:// first cut 1/8 size of top and bottom and then expand to full screen
            DEBUG_ASPECT_RATIO(printf("VIDEOSCREEN_WSS_16by9\n"));
            pstCropWin->y += pstCropWin->height * 1 / 8;
            pstCropWin->height = pstCropWin->height * 6 / 8;
            break;
        case VIDEOSCREEN_ORIGIN:
            DEBUG_ASPECT_RATIO(printf("VIDEOSCREEN_ORIGIN\n"));
            break;

        case VIDEOSCREEN_MM_CAL_BY_VIDEOPLAYER:    // Keep source H/V ratio and scale to fit panel
            DEBUG_ASPECT_RATIO(printf("\nVIDEOSCREEN_MM_CAL_BY_VIDEOPLAYER"));
            // Direct use videoplayer's dst window
            break;

        case VIDEOSCREEN_MM_KEEP_RATIO_AND_SCALE:    // Keep source H/V ratio and scale to fit panel
            DEBUG_ASPECT_RATIO(printf("\nVIDEOSCREEN_MM_KEEP_RATIO_AND_SCALE"));
            // Direct use videoplayer's dst window
            break;

        case VIDEOSCREEN_MM_FULL:    // H and V scale to fit panel
            DEBUG_ASPECT_RATIO(printf("VIDEOSCREEN_MM_FULL\n"));
            pstDstWin->x = 0;
            pstDstWin->y = 0;
            pstDstWin->width = g_IPanel.Width();
            pstDstWin->height = g_IPanel.Height();
            break;

        case VIDEOSCREEN_MM_1_1:     // Bypass scale
            DEBUG_ASPECT_RATIO(printf("VIDEOSCREEN_MM_1_1\n"));
            pstDstWin->width = pstCropWin->width;
            if( pstDstWin->width > g_IPanel.Width() )
                pstDstWin->width = g_IPanel.Width();
            pstDstWin->height = pstCropWin->height;
            if( pstDstWin->height > g_IPanel.Height() )
                pstDstWin->height = g_IPanel.Height();
            pstDstWin->x = (g_IPanel.Width()-pstDstWin->width)/2;
            pstDstWin->y = (g_IPanel.Height()-pstDstWin->height)/2;
            break;

        case VIDEOSCREEN_MM_16_9:    // Display window: H:V=16:9
            DEBUG_ASPECT_RATIO(printf("VIDEOSCREEN_MM_16_9\n"));
            if( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
                pstDstWin->x = 0;
                pstDstWin->y = 0;
                pstDstWin->width = g_IPanel.Width();
                pstDstWin->height = g_IPanel.Height();
            }
            else
            {
                if( g_IPanel.Width()*9 > g_IPanel.Height()*16 )
                {
                    pstDstWin->height = g_IPanel.Height();
                    pstDstWin->y = 0;
                    pstDstWin->width = g_IPanel.Height()*16/9;
                    pstDstWin->x = (g_IPanel.Width()-pstDstWin->width)/2;
                }
                else
                {
                    pstDstWin->width = g_IPanel.Width();
                    pstDstWin->x = 0;
                    pstDstWin->height = g_IPanel.Width()*9/16;
                    pstDstWin->y = (g_IPanel.Height()-pstDstWin->height)/2;
                }
            }
            break;

        case VIDEOSCREEN_MM_4_3:     // Display window: H:V=4:3
            DEBUG_ASPECT_RATIO(printf("VIDEOSCREEN_MM_4_3\n"));
            if( g_IPanel.Width()*3 > g_IPanel.Height()*4 )
            {
                pstDstWin->height = g_IPanel.Height();
                pstDstWin->y = 0;
                pstDstWin->width = g_IPanel.Height()*4/3;
                pstDstWin->x = (g_IPanel.Width()-pstDstWin->width)/2;
            }
            else
            {
                pstDstWin->width = g_IPanel.Width();
                pstDstWin->x = 0;
                pstDstWin->height = g_IPanel.Width()*3/4;
                pstDstWin->y = (g_IPanel.Height()-pstDstWin->height)/2;
            }
            break;

        case VIDEOSCREEN_MM_ZOOM1:   // TO BE defined
            DEBUG_ASPECT_RATIO(printf("VIDEOSCREEN_MM_ZOOM1\n"));
            break;

        case VIDEOSCREEN_MM_ZOOM2:   // TO BE defined
            DEBUG_ASPECT_RATIO(printf("VIDEOSCREEN_MM_ZOOM2\n"));
            break;

        case VIDEOSCREEN_POINT_TO_POINT:
            DEBUG_ASPECT_RATIO(printf("VIDEOSCREEN_POINT_TO_POINT\n"));
       #if 1
            if( MDrv_PQ_Check_PointToPoint_Condition(pstXC_SetWin_Info, PQ_MAIN_WINDOW) )
            {
                printf("Set PQ-PTP=1\n");
                MDrv_PQ_Set_PointToPoint(pstXC_SetWin_Info, TRUE, PQ_MAIN_WINDOW);
            }
            else
            {
                if( pstCropWin->width <= g_IPanel.Width() )
                {
                    pstDstWin->x = (g_IPanel.Width() - pstCropWin->width)/2;
                    pstDstWin->width = pstCropWin->width;
                }
                else
                {
                    pstDstWin->x = 0;
                    pstDstWin->width = g_IPanel.Width();
                }

                if( pstCropWin->height <= g_IPanel.Height() )
                {
                    pstDstWin->y = (g_IPanel.Height() - pstCropWin->height)/2;
                    pstDstWin->height = pstCropWin->height;
                }
                else
                {
                    pstDstWin->y = 0;
                    pstDstWin->height = g_IPanel.Height();
                }
            }

      #else
           if((pstCropWin->width <= PANEL_WIDTH) && (pstCropWin->height <= PANEL_HEIGHT))
           {
               pstDstWin->x = (PANEL_WIDTH - pstCropWin->width)/2;
               pstDstWin->width = pstCropWin->width;
               pstDstWin->y = (PANEL_HEIGHT - pstCropWin->height)/2;
               pstDstWin->height = pstCropWin->height;
           }
      #endif
            break;
    }

}

#if (MEMORY_MAP <= MMAP_32MB)
void MApp_Scaler_Adjust_OverscanRatio_RFBL(INPUT_SOURCE_TYPE_t enInputSourceType,
                                        XC_SETWIN_INFO *pstXC_SetWin_Info)
{
    MApp_Scaler_GetOverScan(enInputSourceType, pstXC_SetWin_Info);
    _MApp_Scaler_CalculateOverScan(enInputSourceType, &(pstXC_SetWin_Info->stCapWin));
}
#endif

void MApp_Scaler_PrintCropWin(char* pcStr, XC_SETWIN_INFO *pstXC_SetWin_Info)
{
    if( pcStr )
    {
        printf("%s", pcStr);
    }

    printf("CropWin: x,y,w,h=%u,%u,%u,%u\n",
        pstXC_SetWin_Info->stCropWin.x,
        pstXC_SetWin_Info->stCropWin.y,
        pstXC_SetWin_Info->stCropWin.width,
        pstXC_SetWin_Info->stCropWin.height );
}

BOOL MApp_Scaler_Check_IfCanEnableOverScan(
    SCALER_WIN eWindow,
    INPUT_SOURCE_TYPE_t enInputSourceType )
{
    PQ_WIN ePQ_Win = (eWindow==MAIN_WINDOW)?PQ_MAIN_WINDOW:PQ_SUB_WINDOW;
    BOOL bEnableOverScan = TRUE;


    DEBUG_OVERSCAN( printf("MApp_Scaler_Check_IfCanEnableOverScan()\n" ); );

    enInputSourceType=enInputSourceType;

    if( IsHDMIInUse() )
    {
    #if ((ENABLE_MHL == ENABLE) && (ENABLE_MHL_NO_OVERSCAN == ENABLE))
        if( msAPI_MHL_IsCbusConnected() && (UI_INPUT_SOURCE_TYPE == HDMI_PORT_FOR_MHL) )
        {
            printf(" MHL Force OverScan Off\n");
            bEnableOverScan = FALSE; // MHL  don't  overscan
        }
    #endif
    }

#if ENABLE_3D_PROCESS
    // When  input 3D timing, don't enable overscan.
    // Fix Mantis-0940646
    if( MApp_Scaler_Is_InputSignal3D() )
    {
        printf("Input Signal 3D => OverScan off\n");
        bEnableOverScan = FALSE;
    }

    if( MApp_Scaler_Is_Input3DMode() )
    {
        printf("Input 3D => OverScan off\n");
        bEnableOverScan = FALSE;
    }

    if( MApp_Scaler_Is_Output3DMode() )
    {
        printf("Output 3D => OverScan off\n");
        bEnableOverScan = FALSE;
    }
#endif

    if( MDrv_PQ_Get_PointToPoint(ePQ_Win) )
    {
        printf("PToP => OverScan off\n");
        bEnableOverScan = FALSE;
    }

    DEBUG_OVERSCAN( printf(" => bEnableOverScan=%u\n", bEnableOverScan); );

    return bEnableOverScan;
}

void MApp_Scaler_Adjust_OverscanRatio(
    SCALER_WIN eWindow,
    INPUT_SOURCE_TYPE_t enInputSourceType,
    XC_SETWIN_INFO *pstXC_SetWin_Info )
{
    DEBUG_OVERSCAN(printf("AdjOverScan: crop-1: x,y,w,h=%u,%u,%u,%u\n", pstXC_SetWin_Info->stCropWin.x, pstXC_SetWin_Info->stCropWin.y, pstXC_SetWin_Info->stCropWin.width, pstXC_SetWin_Info->stCropWin.height));

#if 0//((ENABLE_MHL == ENABLE) && (ENABLE_MHL_NO_OVERSCAN == ENABLE))
    if (IsHDMIInUse() && msAPI_MHL_IsCbusConnected() && (UI_INPUT_SOURCE_TYPE == HDMI_PORT_FOR_MHL))
    {
        MApp_Scaler_EnableOverScan(DISABLE); // MHL  don't  overscan
    }
#endif

    // When  input 3D timing, don't enable overscan.
    // Fix Mantis-0940646
#if 0//ENABLE_3D_PROCESS
    if( MApp_Scaler_Is_Input3DMode() )
    {
        printf("Input 3D => OverScan off\n");
        MApp_Scaler_EnableOverScan(DISABLE);
    }
#endif

    DEBUG_OVERSCAN(printf("AdjOverScan: crop-2: x,y,w,h=%u,%u,%u,%u\n", pstXC_SetWin_Info->stCropWin.x, pstXC_SetWin_Info->stCropWin.y, pstXC_SetWin_Info->stCropWin.width, pstXC_SetWin_Info->stCropWin.height));

    //if (_u8EnableOverScan && (!MDrv_PQ_Get_PointToPoint(PQ_MAIN_WINDOW)))
    if( _u8EnableOverScan
      && MApp_Scaler_Check_IfCanEnableOverScan(eWindow, enInputSourceType)
      )
    {
        MApp_Scaler_GetOverScan(enInputSourceType, pstXC_SetWin_Info);

        DEBUG_OVERSCAN( MApp_Scaler_PrintCropWin("Adjust_OverscanRatio: - 1\n",pstXC_SetWin_Info); );

        _MApp_Scaler_CalculateOverScan(enInputSourceType,&(pstXC_SetWin_Info->stCropWin));

        DEBUG_OVERSCAN( MApp_Scaler_PrintCropWin("Adjust_OverscanRatio: - 2\n", pstXC_SetWin_Info); );
    }

    DEBUG_OVERSCAN(printf("AdjOverScan: crop-3: x,y,w,h=%u,%u,%u,%u\n", pstXC_SetWin_Info->stCropWin.x, pstXC_SetWin_Info->stCropWin.y, pstXC_SetWin_Info->stCropWin.width, pstXC_SetWin_Info->stCropWin.height));

#if ENABLE_3D_PROCESS
    MApp_Scaler_Adjust_3D_CropWin(&(pstXC_SetWin_Info->stCropWin));
#endif

    DEBUG_OVERSCAN(printf("AdjOverScan: crop-4: x,y,w,h=%u,%u,%u,%u\n", pstXC_SetWin_Info->stCropWin.x, pstXC_SetWin_Info->stCropWin.y, pstXC_SetWin_Info->stCropWin.width, pstXC_SetWin_Info->stCropWin.height));
}

void MApp_Scaler_Adjust_AspectRatio(SCALER_WIN eWindow,
                                            EN_ASPECT_RATIO_TYPE enVideoScreen,
                                            MS_WINDOW_TYPE *pstCropWin,
                                            MS_WINDOW_TYPE *pstDstWin,
                                            SRC_RATIO_INFO *pstSrcRatioInfo,
                                            BOOL skipAFDCrop)
{
    MSG(printf("MApp_Scaler_Adjust_AspectRatio:%u,(CropWin:%u,%u,%u,%u)\n",enVideoScreen,pstCropWin->x,pstCropWin->y,pstCropWin->width,pstCropWin->height));

    MS_WINDOW_TYPE tmpCropWin,tmpAFDCropWin;
    tmpCropWin = tmpAFDCropWin = *pstCropWin;

    if( MApi_XC_IsCurrentFrameBufferLessMode() ||MApi_XC_IsCurrentRequest_FrameBufferLessMode())
    {
        //FBL mode can not do overscan and cropping.
        MApp_Scaler_EnableOverScan(FALSE);

        if( IsStorageInUse() )
        {
            switch( enVideoScreen )
            {
                case VIDEOSCREEN_MM_4_3:
                    // Do nothing
                    break;

                default:
                    enVideoScreen = VIDEOSCREEN_MM_KEEP_RATIO_AND_SCALE;
                    printf("Force enVideoScreen = VIDEOSCREEN_MM_KEEP_RATIO_AND_SCALE\n");
                    break;
            }
        }
        else if(IsDTVInUse())
        {
            switch( enVideoScreen )
            {
                case VIDEOSCREEN_NORMAL:
                case VIDEOSCREEN_FULL:
                    // Do nothing
                    break;

                default:
                    enVideoScreen = VIDEOSCREEN_FULL;
                    ST_VIDEO.eAspectRatio = EN_AspectRatio_16X9;
                    (printf("Force enVideoScreen = VIDEOSCREEN_FULL\n"));
                    break;
            }
        }
        else if ( IsVgaInUse()
              #if (INPUT_HDMI_VIDEO_COUNT > 0)
               || ( IsHDMIInUse()&& !g_HdmiPollingStatus.bIsHDMIMode )
              #endif
                )
        {
            switch( enVideoScreen )
            {
                case VIDEOSCREEN_NORMAL:
                case VIDEOSCREEN_FULL:
                    // Do nothing
                    break;
                default:
                    enVideoScreen = VIDEOSCREEN_FULL;
                    ST_VIDEO.eAspectRatio = EN_AspectRatio_16X9;
                    break;
            }
        }
       else
        {
            if( enVideoScreen != VIDEOSCREEN_NORMAL )
            {
                enVideoScreen = VIDEOSCREEN_FULL;
            }
        }
    }

    if((!MDrv_PQ_Check_PointToPoint_Condition(&stXC_SetWin_Info[MAIN_WINDOW],PQ_MAIN_WINDOW) )
        && (enVideoScreen == VIDEOSCREEN_POINT_TO_POINT))
     {
        enVideoScreen = VIDEOSCREEN_FULL;
        printf("\n-Not support ptp change to VIDEOSCREEN_FULL-\n");
     }

    if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) &&
        ((enVideoScreen == VIDEOSCREEN_PROGRAM)           ||
           ((enVideoScreen == VIDEOSCREEN_PROGRAM_4X3)    ||
            (enVideoScreen == VIDEOSCREEN_PROGRAM_16X9)   ||
            (enVideoScreen == VIDEOSCREEN_PROGRAM_14X9))
        ))
    {
        // Scene Aspec Ratio
    #if (MHEG5_ENABLE)
        if(msAPI_MHEG5_IsRunning())
        {
            if(msAPI_MHEG5_CalcSceneAspectRatio(pstDstWin))
            {
                NEWCROPMSG(printf("    |1.GetARC:SCENE!\n"));
            }
            else if(( msAPI_MHEG5_IsIFrameExist() || !g_MHEG5Video.bHaveVideo)||(!msAPI_MHEG5_VID_IsFullScreen(&g_MHEG5Video.stMHEG5VideoAction)))
            {
                MApp_Scaler_CalculateAspectRatio(&stXC_SetWin_Info[eWindow], enVideoScreen,&tmpCropWin,pstDstWin);

                NEWCROPMSG(printf("    |1.GetARC:IFRAME or No Video or non-Full screen\n"));
            }
            else
            {
                NEWCROPMSG(printf("    | 1.GetARC:AFD!\n"));
                msAPI_Picture_CalculateAFDWindow(&stXC_SetWin_Info[eWindow], enVideoScreen,&tmpAFDCropWin,pstDstWin, pstSrcRatioInfo);
            }
        }
        else
    #endif
        {

            NEWCROPMSG(printf("    | 1.GetARC:AFD!\n"));
            msAPI_Picture_CalculateAFDWindow(&stXC_SetWin_Info[eWindow], enVideoScreen,&tmpAFDCropWin,pstDstWin, pstSrcRatioInfo);
        }
        if(skipAFDCrop == FALSE)
        {
            *pstCropWin = tmpAFDCropWin;
        }
    }
    else
    {   // UI ARC
#if(ENABLE_USERARC_WITH_AFD == ENABLE)
        MS_WINDOW_TYPE tmpDstWin;
        tmpDstWin = *pstDstWin;
        msAPI_Picture_CalculateAFDWindow(&stXC_SetWin_Info[eWindow], enVideoScreen,&tmpAFDCropWin,&tmpDstWin,pstSrcRatioInfo);

        if(skipAFDCrop == FALSE)
        {
            *pstCropWin = tmpAFDCropWin;
        }
#endif
        MApp_Scaler_CalculateAspectRatio(&stXC_SetWin_Info[eWindow], enVideoScreen,pstCropWin,pstDstWin);
    }
}

void MApp_Scaler_AlignWindow(MS_WINDOW_TYPE *pWindow, U16 u16AlignX, U16 u16AlignY)
{
    U16 u16temp;
    u16temp = ((pWindow->x + u16AlignX-1) & (~(u16AlignX-1))) - pWindow->x;
    pWindow->x += u16temp;
    pWindow->width -= (u16temp*2);

    u16temp = ((pWindow->y + u16AlignY-1) & (~(u16AlignY-1))) - pWindow->y;
    pWindow->y += u16temp;
    pWindow->height -= (u16temp*2);
}

///////////////////////////////////////////////////////////
/// Scaler MainWin Handler
///////////////////////////////////////////////////////////

/*
    Parameter 'Src' comes from PathSyncEvent.
    Setup scaler main window when sync event happen.
*/
void MApp_Scaler_MainWindowSyncEventHandler(INPUT_SOURCE_TYPE_t src, void* para)
{
    UNUSED(src); UNUSED(para);
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START(););

#if 0//(ENABLE_3D_PROCESS && ENABLE_NEW_3D_FLOW )
    EN_3D_TYPE enInput3DType = DB_3D_SETTING.en3DType;//stGenSetting.g_SysSetting.en3DType;
    EN_3D_TYPE enOutput3DType = EN_3D_BYPASS;
    EN_3D_TYPE enBackendInput3DType = EN_3D_BYPASS;
    EN_4K2K_OUTPUT_RESOLUTION_TYPE enResolutionType = E_OUTPUT_RESOLUTION_1920X1080;
#endif

    LOG_CHANGE_CHANNEL_TIME_FUNC_START();

    DEBUG_SCALER_FLOW(printf("MApp_Scaler_MainWindowSyncEventHandler(src=%u)\n", src););

#if( ENABLE_LOG_CHANGE_CHANNEL )
    printf(" SyncEvent at %u\n", g_Debug_u32Time_ChangeChannel);
#endif

#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("SyncEvent - Start" );
#endif
#if(CHAKRA3_AUTO_TEST)
    AT_LOG("SyncEvent Start" );
#endif

    // Setup ADC ...
    MApp_Scaler_SetupADC(MAIN_WINDOW);

#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("SyncEvent - SetADC" );
#endif


    stSystemInfo[MAIN_WINDOW].enAspectRatio = MApp_Scaler_GetAspectRatio(MAIN_WINDOW,ST_VIDEO.eAspectRatio);

#if 0//(ENABLE_3D_PROCESS && ENABLE_NEW_3D_FLOW )

    DEBUG_3D( printf("enInput3DType=%u\n", enInput3DType); );
    DEBUG_3D( printf("enOutput3DType=%u\n", enOutput3DType); );

    E_XC_3D_INPUT_MODE eXC_3D_INPUT_MODE = MAPP_Scaler_MapUI3DModeToXCInput3DMode(enInput3DType);
    E_XC_3D_OUTPUT_MODE eXC_3D_OUTPUT_MODE = MAPP_Scaler_MapUI3DModeToXCOutput3DMode(enOutput3DType);

    DEBUG_3D( printf("eXC_3D_INPUT_MODE=%u(%s)\n", eXC_3D_INPUT_MODE, MApp_Scaler_Get_Xc3DInputName(eXC_3D_INPUT_MODE) ); );
    DEBUG_3D( printf("eXC_3D_OUTPUT_MODE=%u\n", eXC_3D_OUTPUT_MODE); );

    if(MApp_Scaler_3D_GetOutputConfiguration(&enOutput3DType, &enBackendInput3DType, &enResolutionType) == TRUE)
    {
        if(enOutput3DType == EN_3D_BYPASS)  //2D
        {
            MApi_XC_Set_3D_Mode(eXC_3D_INPUT_MODE, eXC_3D_OUTPUT_MODE, E_XC_3D_PANEL_NONE, MAIN_WINDOW);
            MApi_XC_Set_3D_Mode(eXC_3D_INPUT_MODE, eXC_3D_OUTPUT_MODE, E_XC_3D_PANEL_NONE, SUB_WINDOW);
        }
        else
        {
            MApi_XC_Set_3D_Mode(eXC_3D_INPUT_MODE, eXC_3D_OUTPUT_MODE, E_XC_3D_PANEL_PELLICLE, MAIN_WINDOW);
            MApi_XC_Set_3D_Mode(eXC_3D_INPUT_MODE, eXC_3D_OUTPUT_MODE, E_XC_3D_PANEL_PELLICLE, SUB_WINDOW);
        }

        MApp_Scaler_3D_SetPanelTiming_ByResolution(enResolutionType, enBackendInput3DType);
    }
#endif

#if (ENABLE_3D_PROCESS && ENABLE_NEW_3D_FLOW )
    // Reset 3D setting to default
    DB_3D_SETTING.en3DType = EN_3D_BYPASS;
    MApp_Scaler_EnableManualDetectTiming(FALSE);

    MApp_Scaler_3D_Config(SCLAER_3D_CFG_FOR_AUTO); // at MApp_Scaler_MainWindowSyncEventHandler

    //MApi_XC_ForceSet_OPWriteOffEnable(ENABLE, MAIN_WINDOW);
  #if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("SyncEvent - Set3D" );
  #endif

#endif

    _MApp_Scaler_CheckHDMode(MAIN_WINDOW);

    LOG_CHANGE_CHANNEL_TIME("  SyncEvent-1");

#if (ENABLE_PIP)
    if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
    {
        MS_WINDOW_TYPE stPOPMainWin;
        if(MApp_InputSource_PIP_GetMainWinRect(&stPOPMainWin))
        {
            MApp_Scaler_SetWindow(
                NULL,
                NULL,
                &stPOPMainWin,
                stSystemInfo[MAIN_WINDOW].enAspectRatio,
                src,
                MAIN_WINDOW);

        }
        else
        {
            MApp_Scaler_SetWindow(NULL, NULL, NULL,
                stSystemInfo[MAIN_WINDOW].enAspectRatio,
                src,
                MAIN_WINDOW);
        }
    }
    else
#endif
    {
#if  MHEG5_ENABLE
        if(msAPI_MHEG5_IsRunning())
        {
            MApp_MHEG5_SetGraphARCInfo(SENDARC_AFD_FOR_GE,stSystemInfo[MAIN_WINDOW].enAspectRatio);
            MApp_MHEG5_SetGraphARCInfo(SENDARC_AFD,stSystemInfo[MAIN_WINDOW].enAspectRatio);
        }
#endif

        MApp_Scaler_SetWindow(NULL, NULL, NULL,
            stSystemInfo[MAIN_WINDOW].enAspectRatio,
            src,
            MAIN_WINDOW);
    }

#if(CHAKRA3_AUTO_TEST)
    AT_LOG("SetWindow done" );
#endif

    LOG_CHANGE_CHANNEL_TIME("  SyncEvent-2");
#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("SyncEvent - SetWindow" );
#endif

    MApp_Scaler_SetTiming(src, MAIN_WINDOW);
    //printf(" MApp_Scaler_SetTiming at %u\n", MsOS_GetSystemTime());
#if(CHAKRA3_AUTO_TEST)
    AT_LOG("SetTiming done" );
#endif

    LOG_CHANGE_CHANNEL_TIME("  SyncEvent-3");
#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("SyncEvent - SetTiming" );
#endif

    MAPI_XC_MUX_ONOFF_PERIODIC_HANDLER(src, ENABLE);

#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("SyncEvent - End" );
#endif
#if(CHAKRA3_AUTO_TEST)
    AT_LOG("SyncEvent end" );
#endif

    LOG_CHANGE_CHANNEL_TIME_FUNC_END();
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END(););
}

/*
    Put jobs which need to do when destination on/off event happen
 */

//extern U16 g_Debug_TestMuteTime;

#define DEBUG_UNMUTE(x)     //x
void MApp_Scaler_MainWindowOnOffEventHandler(INPUT_SOURCE_TYPE_t src, void* para)
{
    U8 u8Enable = *((U8*)para);
#if ENABLE_3D_PROCESS
    BOOL bOutputIs3D = FALSE;
#endif
    BOOL bVDHasSignal = IsVDHasSignal();

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START(););
    LOG_CHANGE_CHANNEL_TIME_FUNC_START();

    DEBUG_SCALER_FLOW(printf("MApp_Scaler_MainWindowOnOffEventHandler(src=%u, En=%u) at %u\n", src, u8Enable, MsOS_GetSystemTime()););

    //printf("===> [%s] Line=%d, %d, %d\n",__FUNCTION__, __LINE__, src, u8Enable);

// Log time for ChangeChannel
#if( ENABLE_LOG_CHANGE_CHANNEL )
    printf(" OnOffEvent at %u\n", g_Debug_u32Time_ChangeChannel);
#endif

#if(DEBUG_CHG_SRC_TIME)
    //if(u8Enable)
    {
        msDebug_PrintChgSrcTime("WindowOnOff Start");
    }
#endif

#if(CHAKRA3_AUTO_TEST)
    AT_LOG("WindowOnOff Start" );
#endif

    // Turn on Main window
    if( u8Enable )
    {
        MApi_XC_Sys_PQ_ReduceBW_ForOSD(MAIN_WINDOW, MApi_GOP_GWIN_IsEnabled());

        LOG_CHANGE_CHANNEL_TIME("OnOffEvent-1");

        MApp_Picture_Setting_SetColor(src, MAIN_WINDOW);

    #if(CHAKRA3_AUTO_TEST)
        AT_LOG("SetColor done" );
    #endif

        LOG_CHANGE_CHANNEL_TIME("OnOffEvent-2");

     #if(ENABLE_NEW_AUTO_NR == 1)
        msAPI_NR_SetDNRDefault();
     #endif

    #if ENABLE_3D_PROCESS
        MApp_Scaler_AutoDisablePQ_UC();

    #if(CHAKRA3_AUTO_TEST)
        //AT_LOG("AutoDisablePQ_UC done" );
    #endif

        if((E_XC_3D_OUTPUT_LINE_ALTERNATIVE == MApi_XC_Get_3D_Output_Mode())
            || (E_XC_3D_OUTPUT_TOP_BOTTOM == MApi_XC_Get_3D_Output_Mode())
            || (E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF == MApi_XC_Get_3D_Output_Mode()))
        {
            MApi_XC_ACE_3DClonePQMap(E_ACE_WEAVETYPE_NONE);

            if(MApi_XC_Get_3D_HW_Version() < 2)
            {
                MApi_XC_DisableInputSource(FALSE, SUB_WINDOW);
                MApi_XC_3DMainSub_IPSync();
            }
            MApi_XC_3D_PostPQSetting(MAIN_WINDOW);

            // When output is 3D mode, should wait frame lock,
            // Otherwise, garbage appear
            //msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_SCALER_FPLL, ENABLE, 0, MAIN_WINDOW);
            bOutputIs3D = TRUE;

        #if(CHAKRA3_AUTO_TEST)
            AT_LOG("Set 3D done" );
        #endif

        }
    #endif

        //MApi_XC_Sys_CheckFrameCount();
    }
    else
    {
        msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_FREERUN, ENABLE, 0, MAIN_WINDOW);
        MAPI_XC_MUX_ONOFF_PERIODIC_HANDLER(src, DISABLE);

    #if ENABLE_DLC
        MApi_XC_DLC_CGC_Reset();
      #if ENABLE_DBC
        MApi_XC_DLC_DBC_Reset();
      #endif
    #endif
    }


    LOG_CHANGE_CHANNEL_TIME("OnOffEvent-4");

    U16 u16UnMuteTime = 0;

    {
        if( u8Enable ) // Disable BlueScreen
        {
            MS_U16 u16PQDelayTime = MDrv_PQ_GetDelayTime();
            BOOL bInterlace = 0;
            MS_U16 u16InVFreq = 0;
            U32 u32TimePerFrame = 20;
            U8 u8FrameCount = MHAL_XC_Get_FrameCount();
            BOOL bNeedWaitFpllLock = FALSE;

            DEBUG_UNMUTE( printf("u8FrameCount = %u\n", u8FrameCount); );
            DEBUG_UNMUTE( printf("u16PQDelyaTime = %u\n", u16PQDelayTime); );

            if( IsAnalogSourceInUse() )
            {
                bInterlace = MApi_XC_PCMonitor_GetSyncStatus(MAIN_WINDOW) & XC_MD_INTERLACE_BIT ? TRUE : FALSE;
                u16InVFreq = MApi_XC_PCMonitor_Get_VFreqx10(MAIN_WINDOW);
                DEBUG_UNMUTE( printf("bInterlace = %u\n", bInterlace); );
                DEBUG_UNMUTE( printf("u16InVFreq = %u\n", u16InVFreq); );
                if( u16InVFreq )
                {
                    u32TimePerFrame = (10000 / u16InVFreq) + 1;
                    DEBUG_UNMUTE( printf("u32TimePerFrame = %u\n", u32TimePerFrame); );
                }
            }

            // Use PQ delay time as default unmute time
            u16UnMuteTime = u16PQDelayTime;

            // Modify unmute time for special case
        #if ENABLE_3D_PROCESS
            if( bOutputIs3D )
            {
                if( IsHDMIInUse() )
                {
                    if( (E_XC_3D_INPUT_FRAME_PACKING == MApi_XC_Get_3D_Input_Mode(MAIN_WINDOW))
                      &&(u16InVFreq <= 260 ) // 24/25Hz
                      )
                    {
                        //printf("##################Vf = %u\n", u16InVF);
                        // Finetune at 1080p24 FP
                        //u16UnMuteTime = 1500;
                        u16UnMuteTime = 200;
                        bNeedWaitFpllLock = TRUE;
                    }
                    else if( u16InVFreq <= 490 ) // For 24/25Hz
                    {
                        // 3 frame * 43ms
                        u16UnMuteTime = u32TimePerFrame * u8FrameCount;
                        bNeedWaitFpllLock = TRUE;
                    }
                }
            }
            else
        #endif
          #if 0//(ENABLE_ATSC)
            // Why?? Need refine!!
            if( IsAtscInUse() && MApp_VChip_GetCurVChipBlockStatus() )
            {
                u16UnMuteTime = DEFAULT_SCREEN_UNMUTE_TIME_ATSC;
            }
            else
          #endif
            if ( IsSrcTypeDigitalVD(src) )
            {
            #if(ENABLE_ATSC)
                if (u16UnMuteTime < 200)
                {
                    u16UnMuteTime = 200;
                }
            #else
                if (u16UnMuteTime < 200)
                {
                    u16UnMuteTime = 200;
                }
            #endif
            }
            else if( IsDTVInUse() // For DTV HD FBL mode, need to wait FPLL done
                  &&(MApi_XC_IsCurrentFrameBufferLessMode()||MApi_XC_IsCurrentRequest_FrameBufferLessMode())
                   )
            {

            #if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_WHISKY)&&(MEMORY_MAP == MMAP_32MB) )
                u16UnMuteTime = 100;
                bNeedWaitFpllLock = TRUE;

            #elif(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON)
                u16UnMuteTime = 100;
                bNeedWaitFpllLock = TRUE;

            #else
                u16UnMuteTime = 400;
            #endif

            }
            else if( IsAnalogSourceInUse() )//( IsHDMIInUse() )
            {
                if( u16InVFreq <= 490 ) // For 24/25 Hz
                {
                    u16UnMuteTime = SCREEN_UNMUTE_TIME__SRC_MHL; // Rex.Wang: For MHL
                }
                else if(bInterlace) // 480i/576i/1080i
                {
                    u16UnMuteTime = u32TimePerFrame * u8FrameCount;
                    //bNeedWaitFpllLock = TRUE;
                }
                else // 50/60P
                {
                    u16UnMuteTime = u32TimePerFrame * u8FrameCount;

                #if 0//(CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)
                    // This is a patch!! // Don't know why need mute so long
                    // I guess:  Sclaer some IP need frame lock done!?
                    u16UnMuteTime = 300;
                    bNeedWaitFpllLock = TRUE;
                #endif
                }
            }

        #if(ENABLE_BOOTTIME)
            printf("[TIME] PQ Delay=%u at %u\n", u16UnMuteTime, MsOS_GetSystemTime());
        #endif

        #if(CHAKRA3_AUTO_TEST)
            {
                printf("u16UnMuteTime=%u\n", u16UnMuteTime);
            }
        #endif

            DEBUG_UNMUTE( printf("u16UnMuteTime=%u\n", u16UnMuteTime); );
            /*if( g_Debug_TestMuteTime )
            {
                u16UnMuteTime = g_Debug_TestMuteTime;
                printf(" Force mute time=%u\n", u16UnMuteTime);
            }*/
            if( bNeedWaitFpllLock )
            {
                printf("Ummute need to wait fpll done\n");
                msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_SCALER_FPLL, ENABLE, 0, MAIN_WINDOW);
            }
        }

        msAPI_Scaler_SetBlueScreen( !u8Enable , E_XC_FREE_RUN_COLOR_BLACK, u16UnMuteTime, MAIN_WINDOW);
    }

    LOG_CHANGE_CHANNEL_TIME("OnOffEvent-5");

#if(CHAKRA3_AUTO_TEST)
    AT_LOG("Set Audio mute");
#endif

    // Control audio mute
    if ( u8Enable ) // Enable window
    {
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE_DURING_LIMITED_TIME, u16UnMuteTime, E_AUDIOMUTESOURCE_ACTIVESOURCE);
        if(IsATVInUse())
        {
            if(bVDHasSignal==TRUE)
            {
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYSYNC_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            }
        }
        else
        {
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYSYNC_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
        }
    }
    else // Disable window
    {
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYSYNC_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
    }

#if(DEBUG_CHG_SRC_TIME)
    //if(u8Enable)
    {
        msDebug_PrintChgSrcTime("WindowOnOff End");
    }
#endif

#if(CHAKRA3_AUTO_TEST)
    AT_LOG("WindowOnOff End");
#endif

    LOG_CHANGE_CHANNEL_TIME_FUNC_END();
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END(););
}

/*
    Put jobs which need to do when periodic handler executed
 */
void MApp_Scaler_MainWindowPeriodicHandler(INPUT_SOURCE_TYPE_t src, BOOLEAN bRealTimeMonitorOnly)
{
    UNUSED(src);

    //printf("PeriodicHandler(src=%u, %u)\n", src, bRealTimeMonitorOnly);

    MApi_XC_Sys_Periodic_Handler(MAIN_WINDOW, bRealTimeMonitorOnly);
}

///////////////////////////////////////////////////////////
/// Scaler SubWin Handler
///////////////////////////////////////////////////////////

/*
    Setup scaler sub window when sync event happen.
 */
#if (ENABLE_PIP)
void MApp_Scaler_SubWindowSyncEventHandler(INPUT_SOURCE_TYPE_t src, void* para)
{
    UNUSED(src); UNUSED(para);

    if(!IsPIPSupported())
    {
        printf("MApp_Scaler_SubWindowSyncEventHandler: This chip do not support PIP!\n");
        return;
    }

    stSystemInfo[SUB_WINDOW].enAspectRatio = MApp_Scaler_GetAspectRatio(SUB_WINDOW,ST_VIDEO.eAspectRatio);
    if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
    {
        MS_WINDOW_TYPE stWinRect;
        MApp_InputSource_PIP_GetSubWinRect(&stWinRect);
        MApp_Scaler_SetWindow(
            NULL,
            NULL,
            &stWinRect,
            stSystemInfo[SUB_WINDOW].enAspectRatio,
            SYS_INPUT_SOURCE_TYPE(SUB_WINDOW),
            SUB_WINDOW);
    }
    else
    {
        MApp_Scaler_SetWindow(NULL, NULL, NULL, stSystemInfo[SUB_WINDOW].enAspectRatio, src, SUB_WINDOW);
    }

    MAPI_XC_MUX_ONOFF_PERIODIC_HANDLER(src, ENABLE);
}

/*
    Put jobs which need to do when destination on/off event happen
 */
void MApp_Scaler_SubWindowOnOffEventHandler(INPUT_SOURCE_TYPE_t src, void* para)
{
    U8 u8Enable = *((U8*)para);

    DEBUG_SCALER_FLOW(printf("MApp_Scaler_SubWindowOnOffEventHandler(src=%u, En=%u)\n", src, u8Enable););

    // Turn on Sub window
    if ( u8Enable )
    {
        MApi_XC_Sys_PQ_ReduceBW_ForOSD(SUB_WINDOW, MApi_GOP_GWIN_IsEnabled());
        MApp_Picture_Setting_SetColor(src, SUB_WINDOW);
    }
    else
    {
        MAPI_XC_MUX_ONOFF_PERIODIC_HANDLER(src, DISABLE);
    }

    msAPI_Scaler_SetBlueScreen( !u8Enable , E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, SUB_WINDOW);
}


/*
    Put jobs which need to do when periodic handler executed
 */
void MApp_Scaler_SubWindowPeriodicHandler(INPUT_SOURCE_TYPE_t src, BOOLEAN bRealTimeMonitorOnly)
{
    UNUSED(src);

    MApi_XC_Sys_Periodic_Handler(SUB_WINDOW, bRealTimeMonitorOnly);
}

#endif
///////////////////////////////////////////////////////////
/// CVBS out Handler
///////////////////////////////////////////////////////////
/*
    Setup CVBS out when sync event happen.
 */
void MApp_Scaler_CVBS1OutSyncEventHandler(INPUT_SOURCE_TYPE_t src, void* para)
{
    UNUSED(para);
    UNUSED(src); // temp

    // Only DTV need to set.
    if ( src == INPUT_SOURCE_DTV || src == INPUT_SOURCE_STORAGE)
    {
        msAPI_Scaler_SetVE(src,OUTPUT_CVBS1);
    }
}

/*
    Put jobs which need to do when destination on/off event happen
 */
void MApp_Scaler_CVBS1OutOnOffEventHandler(INPUT_SOURCE_TYPE_t src, void* para)
{
    U8 u8Enable = *((U8*)para);
    if(1)//(IsATVInUse())
    {
        BYTE cCurrentProgramNumber;
        cCurrentProgramNumber = msAPI_ATV_GetCurrentProgramNumber();
        if(msAPI_ATV_IsProgramLocked((BYTE)cCurrentProgramNumber))
        {
            u8Enable = 0;
        }
    }

    msAPI_Scaler_SetCVBSMute(!u8Enable, E_VE_MUTE_GEN, src,OUTPUT_CVBS1);
}

/*
    Setup CVBS out when sync event happen.
 */
void MApp_Scaler_CVBS2OutSyncEventHandler(INPUT_SOURCE_TYPE_t src, void* para)
{
    UNUSED(para);
    UNUSED(src); // temp

    // Only DTV need to set.
    if ( src == INPUT_SOURCE_DTV || src == INPUT_SOURCE_STORAGE )
    {
        msAPI_Scaler_SetVE(src,OUTPUT_CVBS2);
    }
}

/*
    Put jobs which need to do when destination on/off event happen
 */
void MApp_Scaler_CVBS2OutOnOffEventHandler(INPUT_SOURCE_TYPE_t src, void* para)
{
    U8 u8Enable = *((U8*)para);
    if(1)//(IsATVInUse())
    {
        BYTE cCurrentProgramNumber;
        cCurrentProgramNumber = msAPI_ATV_GetCurrentProgramNumber();
        if(msAPI_ATV_IsProgramLocked((BYTE)cCurrentProgramNumber))
        {
            u8Enable = 0;
        }
    }
    msAPI_Scaler_SetCVBSMute(!u8Enable, E_VE_MUTE_GEN, src,OUTPUT_CVBS2);
}

void MApp_Scaler_SetOutputPanelType(U8 u8ResolutionType, SCALER_WIN eWindow)
{
     msAPI_Scaler_ChangePanelType( u8ResolutionType, eWindow);
     MApi_XC_GenerateBlackVideoForBothWin(ENABLE);
     MApp_Scaler_SetWindow(NULL, NULL, NULL, stSystemInfo[eWindow].enAspectRatio, SYS_INPUT_SOURCE_TYPE(eWindow), eWindow);
     MApp_Scaler_SetTiming(SYS_INPUT_SOURCE_TYPE(eWindow), eWindow);
     if (MApp_IsSrcHasSignal(MAIN_WINDOW))
    {
       MApi_XC_DisableInputSource(FALSE, MAIN_WINDOW);
          if(MApi_XC_IsCurrentFrameBufferLessMode() || MApi_XC_IsCurrentRequest_FrameBufferLessMode())
          {
              MApi_XC_WaitFPLLDone();
          }
        // wait 4 input vsync before turn on scalar
        MApi_XC_WaitInputVSync(4, 200, MAIN_WINDOW);
           MApi_XC_GenerateBlackVideoForBothWin(DISABLE);
    }
}

//wrapper of MDrv_PQ_Check_PointToPoint_Condition() for App layer (other than setwindow process) usage
BOOLEAN MApp_Scaler_Check_PointToPoint_Mode(PQ_WIN eWindow)
{
    if( ST_VIDEO.eAspectRatio != EN_AspectRatio_Point_to_Point )
        return FALSE;

    MS_BOOL bRet = FALSE;
    XC_SETWIN_INFO stXC_SetWin_InfoEx;
    XC_ApiStatusEx stXCStatusEx;

    memset(&stXC_SetWin_InfoEx, 0, sizeof(XC_SETWIN_INFO));
    memset(&stXCStatusEx, 0, sizeof(XC_ApiStatusEx));

    stXCStatusEx.u16ApiStatusEX_Length = sizeof(XC_ApiStatusEx);
    stXCStatusEx.u32ApiStatusEx_Version = API_STATUS_EX_VERSION;

    if(MApi_XC_GetStatusEx(&stXCStatusEx, MAIN_WINDOW) == sizeof(XC_ApiStatusEx))
    {
        stXC_SetWin_InfoEx.enInputSourceType = stXCStatusEx.enInputSourceType;
        stXC_SetWin_InfoEx.bInterlace = stXCStatusEx.bInterlace;
        memcpy(&stXC_SetWin_InfoEx.stCropWin, &stXCStatusEx.stCropWin, sizeof(MS_WINDOW_TYPE));

        bRet = MDrv_PQ_Check_PointToPoint_Condition(&stXC_SetWin_InfoEx, eWindow);
    }
    else
    {
        bRet = FALSE;
    }

    //printf("[MDrv_PQ_Check_PointToPoint_Mode] %u\n",bRet);

    return bRet;
}

/// Get current window settings: includes Capture window, Display window
/// and Crop window
void MApp_Scaler_GetWinInfo(XC_SETWIN_INFO* pWindowInfo, SCALER_WIN eWindow)
{
    memcpy((void*)pWindowInfo, (void*)&stXC_SetWin_Info[eWindow],sizeof(XC_SETWIN_INFO));
}


void MApp_Scaler_GetVidWinInfo(MS_VIDEO_Window_Info_EXT *pstWindow_info, SCALER_WIN eWindow)
{
    st_VidWin_Info.stCapWin = stXC_SetWin_Info[eWindow].stCapWin;
    memcpy((void*)pstWindow_info, (void*)&st_VidWin_Info,sizeof(MS_VIDEO_Window_Info_EXT));
}


void MApp_Scaler_SetVidWinInfo(INPUT_SOURCE_TYPE_t enInputSrcType,MS_VIDEO_Window_Info_EXT *pstWindow_info, SCALER_WIN eWindow)
{
    U16 u16HSize, u16VSize;
    U8 u8_AspectRatio;
    U8 u8_Resolution;
    //MS_VIDEO_Window_Info *pstVideoWinInfo;

    u16HSize = stXC_SetWin_Info[eWindow].stCapWin.width;
    u16VSize = stXC_SetWin_Info[eWindow].stCapWin.height;

    u8_AspectRatio = _MApp_Scaler_Aspect_Ratio_Remapping(stSystemInfo[MAIN_WINDOW].enAspectRatio);
    if( IsSrcTypeYPbPr(enInputSrcType) || IsSrcTypeHDMI(enInputSrcType) )
        u8_Resolution = _MApp_Scaler_Resolution_Remapping( &stXC_SetWin_Info[eWindow], MAIN_WINDOW);
    else
        u8_Resolution = 0;

    if(IsSrcTypeYPbPr(enInputSrcType))  // For Fix coverity #90815 - Out-of-bounds read
    {
        if( u8_Resolution >= E_YPbPr_MAX )
        {
            return;
        }
    }
    else if(IsSrcTypeHDMI(enInputSrcType))  // For Fix coverity #90815 - Out-of-bounds read
    {
        if( u8_Resolution >= E_HDMI_MAX )
        {
            return;
        }
    }

    MS_DEBUG_MSG(printf("Before SetWindow cap H[%d] V[%d], crop: H[%d]-V[%d] L[%d] R[%d] U[%d] D[%d]\n" ,
            st_VidWin_Info.stCapWin.x, st_VidWin_Info.stCapWin.y,
            st_VidWin_Info.u8H_OverScanRatio, st_VidWin_Info.u8V_OverScanRatio,
            _u8H_CropRatio_Left, _u8H_CropRatio_Right,
            _u8V_CropRatio_Up, _u8V_CropRatio_Down));

    st_VidWin_Info.u8H_OverScanRatio = pstWindow_info->u8H_OverScanRatio;
    st_VidWin_Info.u8V_OverScanRatio = pstWindow_info->u8V_OverScanRatio;
    st_VidWin_Info.u8HCrop_Left = pstWindow_info->u8HCrop_Left;
    st_VidWin_Info.u8HCrop_Right = pstWindow_info->u8HCrop_Right;
    st_VidWin_Info.u8VCrop_Up = pstWindow_info->u8VCrop_Up;
    st_VidWin_Info.u8VCrop_Down = pstWindow_info->u8VCrop_Down;
    st_VidWin_Info.stCapWin = pstWindow_info->stCapWin;

    if(IsSrcTypeDTV(enInputSrcType) ||
      (IsSrcTypeStorage(enInputSrcType) && !IsSrcTypeJpeg(enInputSrcType))) // storage type except JPEG
    {
        if(u16HSize <= 750 && u16VSize <= 500)
        {
           if(stXC_SetWin_Info[eWindow].bInterlace)
           {// 480i
                _u16OverscanDtv480iH = st_VidWin_Info.u8H_OverScanRatio;
                _u16OverscanDtv480iV = st_VidWin_Info.u8V_OverScanRatio;
           }
           else
           {// 480p
                _u16OverscanDtv480pH = st_VidWin_Info.u8H_OverScanRatio;
                _u16OverscanDtv480pV = st_VidWin_Info.u8V_OverScanRatio;
           }
        }
        else if(u16HSize <= 750 && u16VSize <= 600)
        {
            if (stXC_SetWin_Info[eWindow].bInterlace)
            {// 576i
                _u16OverscanDtv576iH = st_VidWin_Info.u8H_OverScanRatio;
                _u16OverscanDtv576iV = st_VidWin_Info.u8V_OverScanRatio;
            }
            else
            {// 576p
                _u16OverscanDtv576pH = st_VidWin_Info.u8H_OverScanRatio;
                _u16OverscanDtv576pV = st_VidWin_Info.u8V_OverScanRatio;
            }
        }
        else if(u16HSize <= 1300 && u16VSize <= 750)
        {   //720P
            _u16OverscanDtv720pH = st_VidWin_Info.u8H_OverScanRatio;
            _u16OverscanDtv720pV = st_VidWin_Info.u8V_OverScanRatio;
        }
        else if(u16HSize <= 1950 && u16VSize <= 1200)
        {
            if (stXC_SetWin_Info[eWindow].bInterlace)
            {//1080i
                _u16OverscanDtv1080iH = st_VidWin_Info.u8H_OverScanRatio;
                _u16OverscanDtv1080iV = st_VidWin_Info.u8V_OverScanRatio;
            }
            else
            {// 1080P
                _u16OverscanDtv1080pH = st_VidWin_Info.u8H_OverScanRatio;
                _u16OverscanDtv1080pV = st_VidWin_Info.u8V_OverScanRatio;
            }
        }
        _u8H_OverScanRatio = st_VidWin_Info.u8H_OverScanRatio;
        _u8V_OverScanRatio = st_VidWin_Info.u8V_OverScanRatio;
    }
    else if(IsSrcTypeYPbPr(enInputSrcType))
    {
        if( u8_Resolution >= E_YPbPr_MAX )
        {
            u8_Resolution=0;
        }

        YPbPr_WinInfo[u8_Resolution][u8_AspectRatio].u8HCrop_Left = st_VidWin_Info.u8HCrop_Left;
        YPbPr_WinInfo[u8_Resolution][u8_AspectRatio].u8HCrop_Right = st_VidWin_Info.u8HCrop_Right;
        YPbPr_WinInfo[u8_Resolution][u8_AspectRatio].u8VCrop_Up = st_VidWin_Info.u8VCrop_Up;
        YPbPr_WinInfo[u8_Resolution][u8_AspectRatio].u8VCrop_Down = st_VidWin_Info.u8VCrop_Down;

        _u8H_CropRatio_Left = st_VidWin_Info.u8HCrop_Left;
        _u8H_CropRatio_Right = st_VidWin_Info.u8HCrop_Right;
        _u8V_CropRatio_Up = st_VidWin_Info.u8VCrop_Up;
        _u8V_CropRatio_Down = st_VidWin_Info.u8VCrop_Down;
    }
    else if(IsSrcTypeDigitalVD(enInputSrcType))
    {
        //pstVideoWinInfo = &CVBS_WinInfo[mvideo_vd_get_videosystem()][u8_AspectRatio];

        CVBS_WinInfo[mvideo_vd_get_videosystem()][u8_AspectRatio].u8HCrop_Left = st_VidWin_Info.u8HCrop_Left;
        CVBS_WinInfo[mvideo_vd_get_videosystem()][u8_AspectRatio].u8HCrop_Right = st_VidWin_Info.u8HCrop_Right;
        CVBS_WinInfo[mvideo_vd_get_videosystem()][u8_AspectRatio].u8VCrop_Up = st_VidWin_Info.u8VCrop_Up;
        CVBS_WinInfo[mvideo_vd_get_videosystem()][u8_AspectRatio].u8VCrop_Down = st_VidWin_Info.u8VCrop_Down;

        _u8H_CropRatio_Left = st_VidWin_Info.u8HCrop_Left;
        _u8H_CropRatio_Right = st_VidWin_Info.u8HCrop_Right;
        _u8V_CropRatio_Up = st_VidWin_Info.u8VCrop_Up;
        _u8V_CropRatio_Down = st_VidWin_Info.u8VCrop_Down;
    }
#if (INPUT_HDMI_VIDEO_COUNT>0)
    //else if(IsSrcTypeHDMI(enInputSrcType) && (g_HdmiPollingStatus.bIsHDMIMode == TRUE))
    else if(IsSrcTypeHDMI(enInputSrcType))
    {  // make sure this is HDMI mode, not DVI mode

        if( u8_Resolution >= E_HDMI_MAX )
        {
            u8_Resolution=0;
        }

        HDMI_WinInfo[u8_Resolution][u8_AspectRatio].u8HCrop_Left = st_VidWin_Info.u8HCrop_Left;
        HDMI_WinInfo[u8_Resolution][u8_AspectRatio].u8HCrop_Right = st_VidWin_Info.u8HCrop_Right;
        HDMI_WinInfo[u8_Resolution][u8_AspectRatio].u8VCrop_Up = st_VidWin_Info.u8VCrop_Up;
        HDMI_WinInfo[u8_Resolution][u8_AspectRatio].u8VCrop_Down = st_VidWin_Info.u8VCrop_Down;

        _u8H_CropRatio_Left = st_VidWin_Info.u8HCrop_Left;
        _u8H_CropRatio_Right = st_VidWin_Info.u8HCrop_Right;
        _u8V_CropRatio_Up = st_VidWin_Info.u8VCrop_Up;
        _u8V_CropRatio_Down = st_VidWin_Info.u8VCrop_Down;
    }
#endif
    else
    {
        _u8H_CropRatio_Left = 0;
        _u8H_CropRatio_Right = 0;
        _u8V_CropRatio_Up = 0;
        _u8V_CropRatio_Down = 0;
    }

    MS_DEBUG_MSG(printf("After SetWindow cap H[%d] V[%d], crop: H[%d]-V[%d] L[%d] R[%d] U[%d] D[%d]\n"
    ,st_VidWin_Info.stCapWin.x,st_VidWin_Info.stCapWin.y
        ,st_VidWin_Info.u8H_OverScanRatio,st_VidWin_Info.u8V_OverScanRatio
            ,_u8H_CropRatio_Left,_u8H_CropRatio_Right
                ,_u8V_CropRatio_Up,_u8V_CropRatio_Down ));
}

#if(PATCH_FOR_V_RANGE)
void MApp_Scaler_SetCustomerWindow(MS_WINDOW_TYPE *ptSrcWin, MS_WINDOW_TYPE *ptCropWin, MS_WINDOW_TYPE *ptDstWin, SCALER_WIN eWindow)
{
#if 0
    XC_SETWIN_INFO stSetWinInfo;

    MApp_Scaler_GetWinInfo(&stSetWinInfo, eWindow);

    if(ptSrcWin)
    {
        stSetWinInfo.stCapWin = *ptSrcWin;
        printf("CustomerWin: x:%d,y:%d,w:%d,h:%d\n",
            ptSrcWin->x, ptSrcWin->y, ptSrcWin->width, ptSrcWin->height);
        //Print_Buffer((U8*)ptSrcWin, 16);
    }

    if(ptCropWin)
        stSetWinInfo.stCropWin = *ptCropWin;

    if(ptDstWin)
        stSetWinInfo.stDispWin = *ptDstWin;
#endif

     MApp_Scaler_SetWindow(
                        ptSrcWin,
                        ptCropWin,
                        ptDstWin,
                        stSystemInfo[MAIN_WINDOW].enAspectRatio,
                        SYS_INPUT_SOURCE_TYPE(eWindow),
                        eWindow);

     MApp_Picture_Setting_SetColor(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), eWindow);

     MApp_Scaler_SetTiming(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), eWindow);
}
#endif

#define DEBUG_SCALER_FB(x)  //x
void MApp_Scaler_Setup_FB(EnuScalerFBCase eScalerFBCase)
{
    BOOL bIsFBL = FALSE;
    U32 u32ScalerFBAddr = ((SCALER_DNR_BUF_MEMORY_TYPE & MIU1) ? (SCALER_DNR_BUF_ADR | MIU_INTERVAL) : (SCALER_DNR_BUF_ADR));
    U32 u32ScalerFBSize = SCALER_DNR_BUF_LEN;


    DEBUG_SCALER_FB(printf("MApp_Scaler_Setup_FB(eScalerFBCase=%u)\n", eScalerFBCase););

    switch( eScalerFBCase )
    {
        case E_XC_FB_CASE_MM_PHOTO_PREVIEW:

        #if( defined(SCALER_MEM_MM_PHOTO_ADR) )
            u32ScalerFBAddr = SCALER_MEM_MM_PHOTO_ADR;
            u32ScalerFBSize = SCALER_MEM_MM_PHOTO_LEN;

        #elif (MEMORY_MAP <= MMAP_32MB)
            #if defined(SCALER_DNR_BUF_PREV_MM_LEN)
            u32ScalerFBAddr = SCALER_DNR_BUF_PREV_MM_ADR;
            u32ScalerFBSize = SCALER_DNR_BUF_PREV_MM_LEN;
            #else
            u32ScalerFBAddr = SCALER_DNR_BUF_PREV_ADR;
            u32ScalerFBSize = SCALER_DNR_BUF_PREV_LEN;
            #endif

        #elif( SUPPORT_MM_PHOTO_4K )
            u32ScalerFBAddr = SCALER_DNR_4K_PHOTO_BUF_ADR;
            u32ScalerFBSize = SCALER_DNR_4K_PHOTO_BUF_LEN;

        #endif

            break;

        case E_XC_FB_CASE_MM_PHOTO_FULL_DISP:

        #if (MEMORY_MAP <= MMAP_32MB)
            bIsFBL = TRUE;

        #elif( SUPPORT_MM_PHOTO_4K )
            u32ScalerFBAddr = SCALER_DNR_4K_PHOTO_BUF_ADR;
            u32ScalerFBSize = SCALER_DNR_4K_PHOTO_BUF_LEN;

        #elif( defined(SCALER_MEM_MM_PHOTO_ADR) )
            u32ScalerFBAddr = SCALER_MEM_MM_PHOTO_ADR;
            u32ScalerFBSize = SCALER_MEM_MM_PHOTO_LEN;

        #endif

            break;

        default:
            break;

    }

    DEBUG_SCALER_FB(printf(" bIsFBL = %u\n", bIsFBL););
    DEBUG_SCALER_FB(printf(" u32ScalerFBAddr=0x%X, u32ScalerFBSize=0x%X\n", u32ScalerFBAddr, u32ScalerFBSize););

    if( bIsFBL )
    {
        MApi_XC_EnableFrameBufferLess(bIsFBL);
        MApi_XC_SetFrameBufferAddress(u32ScalerFBAddr, u32ScalerFBSize, MAIN_WINDOW);
    }
    else // Use frame buffer
    {
        MApi_XC_SetFrameBufferAddress(u32ScalerFBAddr, u32ScalerFBSize, MAIN_WINDOW);
        MApi_XC_EnableFrameBufferLess(bIsFBL);
    }
}

// This function is checking if  input signal/timing 3D
BOOL MApp_Scaler_Is_InputSignal3D(void)
{
#if( ENABLE_3D_PROCESS )
    if( IsHDMIInUse() )
    {
        if( g_HdmiInput3DFormatStatus != E_XC_3D_INPUT_MODE_NONE )
            return TRUE;
    }
#endif

    return FALSE;
}

// This function is checking if treat input as 3D timing
BOOL MApp_Scaler_Is_Input3DMode(void)
{
#if( ENABLE_3D_PROCESS )
    if( MApp_Scaler_Is_InputSignal3D() // Input signal is 3D
      ||(MApi_XC_Get_3D_Input_Mode(MAIN_WINDOW) != E_XC_3D_INPUT_MODE_NONE ) // XC driver do 3D job
      )
        return TRUE;
#endif

    return FALSE;
}

// This function is checking if treat input as 3D timing
BOOL MApp_Scaler_Is_Output3DMode(void)
{
#if( ENABLE_3D_PROCESS )
    if( MApi_XC_Get_3D_Output_Mode() != E_XC_3D_OUTPUT_MODE_NONE )
        return TRUE;
#endif

    return FALSE;
}

BOOL MApp_Scaler_Is_3DTypeSupported(U8 u8Index)
{
#if(ENABLE_3D_PROCESS)

  #if( CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA )
    if( u8Index == EN_3D_2DConvertTo3D )
        return FALSE;
  #endif

    switch( u8Index )
    {
        case EN_3D_BYPASS:
        case EN_3D_FRAME_PACKING:
        case EN_3D_SIDE_BY_SIDE:
        case EN_3D_TOP_BOTTOM:
        case EN_3D_LINE_ALTERNATIVE:
        case EN_3D_FRAME_ALTERNATIVE:
        case EN_3D_2DConvertTo3D:
            #if ENABLE_DMP
            if( IsStorageInUse() )
            {
                if( MApp_MPlayer_IsPhotoPlaying()
    #if ENABLE_MPLAYER_MOVIE
                    ||(MApp_MPlayer_IsMoviePlaying() && !MApi_XC_IsCurrentFrameBufferLessMode())
    #endif
                    )
                {
                     return TRUE;
                }
                else
                {
                     return FALSE;
                }
            }
            else
            #endif
            {
                if(MApp_IsSrcHasSignal(MAIN_WINDOW))
                {
                     return TRUE;
                }
                else
                {
                     return FALSE;
                }
            }
            break;

        default:
            break;
    }
#else
    UNUSED(u8Index);
#endif

    return FALSE;
}

BOOL MApp_Scaler_Is_AspectRatioSupported_ByUI(EN_MENU_AspectRatio eUiAspectRatio)
{
    if( eUiAspectRatio >= EN_AspectRatio_Num )
        return FALSE;


    switch( eUiAspectRatio )
    {
        case EN_AspectRatio_16X9:
        #if (ENABLE_3D_PROCESS)
            if( MApi_XC_Get_3D_Output_Mode() != E_XC_3D_OUTPUT_MODE_NONE )
                return FALSE;
        #endif
            break;

        case EN_AspectRatio_JustScan:
        {
        #if (ENABLE_3D_PROCESS)
            // Output 3D mode
            if( MApi_XC_Get_3D_Output_Mode() != E_XC_3D_OUTPUT_MODE_NONE )
                return FALSE;
        #endif

            if( IsDigitalSourceInUse()
              ||( IsYPbPrInUse() && !MApi_XC_Sys_IsSrcHD(MAIN_WINDOW) )
              )
            {
                return FALSE;
            }
            else if (IsStorageInUse())
            {
                return FALSE;
            }
            else
            {
                return TRUE;
            }
        }
            break;

        case EN_AspectRatio_Original:
            {
            #if (ENABLE_3D_PROCESS)
                if( MApi_XC_Get_3D_Output_Mode() != E_XC_3D_OUTPUT_MODE_NONE)
                    return FALSE;
            #endif

                if( IsVgaInUse()
            //  #if (INPUT_HDMI_VIDEO_COUNT > 0)
            //  || ( IsHDMIInUse() && !g_HdmiPollingStatus.bIsHDMIMode )
            //  #endif
                 )
                {
                    return FALSE;
                }
                else if(IsDTVInUse()&&MApi_XC_IsCurrentFrameBufferLessMode())
                {
                    return FALSE;
                }
                else
                {
                    return TRUE;
                }
            }
            break;

        case EN_AspectRatio_4X3:
        #if (ENABLE_3D_PROCESS)
            if( MApi_XC_Get_3D_Output_Mode() != E_XC_3D_OUTPUT_MODE_NONE)
                return FALSE;
        #endif
            break;

        case EN_AspectRatio_14X9:
            return FALSE;
            break;

        case EN_AspectRatio_Zoom1:
        case EN_AspectRatio_Zoom2:
            if ( IsVgaInUse()||IsStorageInUse() )
            {
                return FALSE;
            }
            else
            {
            #if ENABLE_3D_PROCESS
                if(MApi_XC_Get_3D_Output_Mode() != E_XC_3D_OUTPUT_MODE_NONE)
                    return FALSE;
                else
            #endif
                    return TRUE;
            }
            break;

        case EN_AspectRatio_Panorama:
            {
            #if ENABLE_NZ_FREEVIEW
                //printf("Unsupport EN_AspectRatio_Panorama!\n");
                return FALSE;
            #endif
                 if (IsVgaInUse()||IsStorageInUse())
                 {
                     return FALSE;
                 }
                 else
                 {
                 #if ENABLE_3D_PROCESS
                     if(MApi_XC_Get_3D_Output_Mode() != E_XC_3D_OUTPUT_MODE_NONE)
                        return FALSE;
                     else
                        return TRUE;
                 #else
                     return TRUE;
                 #endif
                 }
            }
            break;

        case EN_AspectRatio_Point_to_Point:
            if( IsVgaInUse()
          #if (INPUT_HDMI_VIDEO_COUNT > 0)
              ||( IsHDMIInUse()
                 &&(!MApi_XC_IsCurrentFrameBufferLessMode())
                 &&(!MApi_XC_IsCurrentRequest_FrameBufferLessMode())
                )
          #endif
               )
            {
                return TRUE;
            }
            else
            {
                return FALSE;
            }
            break;

        default:
            break;
    }

    return TRUE;
}

// Convert UI-Setting to Sclaer-driver
void MApp_Scaler_UpdateAspectRatioVar( SCALER_WIN eWindow )
{
    if( eWindow >= MAX_WINDOW )
        return;

    DEBUG_ASPECT_RATIO( printf("MApp_Scaler_UpdateAspectRatioVar()\n"); );

    EN_MENU_AspectRatio eUI_AspectRatio = ST_VIDEO.eAspectRatio;

    switch(eUI_AspectRatio)
    {
        case EN_AspectRatio_JustScan:
            MApp_Scaler_EnableOverScan(FALSE);
            break;
        case EN_AspectRatio_Zoom1:
        case EN_AspectRatio_Zoom2:
        case EN_AspectRatio_Panorama:
            //MApp_Picture_ResetZoomFactor(ST_VIDEO.eAspectRatio);
        default:
            MApp_Scaler_EnableOverScan(ENABLE);
            break;
    }

    stSystemInfo[eWindow].enAspectRatio = MApp_Scaler_GetAspectRatio( eWindow, eUI_AspectRatio );
}

#if(ENABLE_3D_PROCESS)
char* MApp_Scaler_Get_Xc3DInputName(E_XC_3D_INPUT_MODE eXC_3D_INPUT_MODE)
{
    switch(eXC_3D_INPUT_MODE)
    {
        default:
            break;

        case E_XC_3D_INPUT_FRAME_PACKING:
            return "E_XC_3D_INPUT_FRAME_PACKING";

        case E_XC_3D_INPUT_FRAME_ALTERNATIVE:
            return "E_XC_3D_INPUT_FRAME_ALTERNATIVE";

        case E_XC_3D_INPUT_FIELD_ALTERNATIVE:
            return "E_XC_3D_INPUT_FIELD_ALTERNATIVE";

        case E_XC_3D_INPUT_LINE_ALTERNATIVE:
            return "E_XC_3D_INPUT_LINE_ALTERNATIVE";

        case E_XC_3D_INPUT_SIDE_BY_SIDE_FULL:
            return "E_XC_3D_INPUT_SIDE_BY_SIDE_FULL";

        case E_XC_3D_INPUT_TOP_BOTTOM:
            return "E_XC_3D_INPUT_TOP_BOTTOM";

        case E_XC_3D_INPUT_SIDE_BY_SIDE_HALF:
            return "E_XC_3D_INPUT_SIDE_BY_SIDE_HALF";

        case E_XC_3D_INPUT_MODE_NONE:
            return "E_XC_3D_INPUT_MODE_NONE";

    }

    return "E_XC_3D_INPUT_MODE_xx";
}

char* MApp_Scaler_Get_Xc3DOutputName(E_XC_3D_OUTPUT_MODE eXC_3D_OUTPUT_MODE)
{
    switch(eXC_3D_OUTPUT_MODE)
    {
        default:
            break;

        case E_XC_3D_OUTPUT_MODE_NONE:
            return "E_XC_3D_OUTPUT_MODE_NONE";

        case E_XC_3D_OUTPUT_LINE_ALTERNATIVE:
            return "E_XC_3D_OUTPUT_LINE_ALTERNATIVE";

        case E_XC_3D_OUTPUT_FRAME_ALTERNATIVE:
            return "E_XC_3D_OUTPUT_FRAME_ALTERNATIVE";
    }

    return "E_XC_3D_OUTPUT_MODE_XXX";
}
#endif

void MApp_Scaler_AutoDisablePQ_UC(void)
{
    XC_ApiStatus stXCApiStatus;
    BOOL bNeedDisableUC = FALSE;

    memset(&stXCApiStatus, 0, sizeof(XC_ApiStatus));
    if (MApi_XC_GetStatus(&stXCApiStatus, MAIN_WINDOW) == FALSE)
    {
        printf("MApi_XC_GetStatus failed.\n");
        return ;
    }

    // prescaring ,freerun,framebufferless
    if( stXCApiStatus.bPreV_ScalingDown
       ||MApi_SC_IsForceFreerun()
       ||MApi_XC_IsCurrentFrameBufferLessMode()
       )
    {
        bNeedDisableUC = TRUE;
    }

    //using sub window and 2d version >=2
#if (ENABLE_3D_PROCESS )
    else if( (2 <= MApi_XC_Get_3D_HW_Version()) //3d version >=2 && using sub window
           &&( (E_XC_3D_OUTPUT_LINE_ALTERNATIVE == MApi_XC_Get_3D_Output_Mode())
             || (E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF == MApi_XC_Get_3D_Output_Mode())
             || (E_XC_3D_OUTPUT_TOP_BOTTOM == MApi_XC_Get_3D_Output_Mode())
             || (E_XC_3D_OUTPUT_FRAME_R == MApi_XC_Get_3D_Output_Mode()) //sub window can not use ucnr
             )
           )
    {
        bNeedDisableUC = TRUE;
    }
#endif

    if( bNeedDisableUC )
    {
    #if 0//(!CHAKRA3_AUTO_TEST)
        //PRINT_CURRENT_LINE();
        printf("MDrv_PQ_DisableUCFeature()\n");
    #endif
        MDrv_PQ_DisableUCFeature(PQ_MAIN_WINDOW);
    }
}

void MApp_Scaler_SetupADC(SCALER_WIN eWindow)
{
    //INPUT_SOURCE_TYPE_t enInputSourceType = SYS_INPUT_SOURCE_TYPE(eWindow);
    MS_PCADC_MODETABLE_TYPE_EX sModeTbl;
    U32 u32InputPixelClock = 0;


    if( IsDTVInUse()
     || IsStorageInUse()
      )
    {
        return;
    }

    // Set SOG clamp delay
    //For customer set Scart RGB sync on green clamp delay
    if(msAPI_AVD_IsScartRGB() && IsScartInUse())
    {
        MApi_XC_ADC_ScartRGB_SOG_ClampDelay(0x280,0xC0);
    }

    //set phase
    if( IsYPbPrInUse() )//For customer set default adc phase
    {
        MApi_XC_ADC_SetPhaseEx(MApi_XC_GetCustomAdcPhase(g_PcadcModeSetting[eWindow].u8ModeIndex));
    }
    else if( IsVgaInUse() )
    {
        MApi_XC_ADC_SetPhaseEx(g_PcadcModeSetting[eWindow].u16Phase);
    }

    // Set SOG Bandwidth
    if( IsYPbPrInUse() )
    {
        MApi_XC_ModeParse_GetModeTbl(g_PcadcModeSetting[eWindow].u8ModeIndex, &sModeTbl);

        //U16->U32 because pixel clock is around 150M for FHD input. 150,000,000 exceed 65,535 a lot...
        u32InputPixelClock=(U32)((U32)sModeTbl.u16VerticalTotal * (U32)sModeTbl.u16HorizontalTotal * (U32)sModeTbl.u16VerticalFrequency)/(10*1000*1000);//(10*1024*1024);
        if(MApi_XC_PCMonitor_GetSyncStatus(eWindow)&XC_MD_INTERLACE_BIT)
        {
            u32InputPixelClock = u32InputPixelClock/2;
        }

        if(u32InputPixelClock<26)//dot bw 26mhz
        {
            MApi_XC_ADC_Set_SOGBW(0x1f);
        }
        else if(u32InputPixelClock<32)//dot bw 32mhz
        {
            MApi_XC_ADC_Set_SOGBW(0xf);
        }
        else if(u32InputPixelClock<43)//dot bw 43mhz
        {
            MApi_XC_ADC_Set_SOGBW(0x7);
        }
        else if(u32InputPixelClock<63)//dot bw 63mhz
        {
            MApi_XC_ADC_Set_SOGBW(0x3);
        }
        else if(u32InputPixelClock<116)//dot bw 116mhz
        {
            MApi_XC_ADC_Set_SOGBW(0x1);
        }
        else //if(116<dotFre<973)
        {
            MApi_XC_ADC_Set_SOGBW(0x0);
        }
    }
    else
    {
        MApi_XC_ADC_Set_SOGBW(0x00);
    }

}

#if(INPUT_SCART_VIDEO_COUNT > 0)
// Maybe it need change in other chip!?
#define SCART_FB_DELAY  0x52 //Test in Milan
#define SCART_RGB_DELAY 0x4C //Test in Milan

void MApp_Scaler_SetupADC_ScartRGB(SCALER_WIN eWindow)
{
    eWindow=eWindow;

    if( !IsScartInUse() )
        return;

    // Patch temply  before utopia api finish
#if( UTOPIA_SUPPORT_ADC_FB_DELAY )

    //Set SCART FB PIPE Delay
    MApi_XC_ADC_SetFB_PIPE_Delay(SCART_FB_DELAY);

    //Set SCART RGB PIPE Delay
    MApi_XC_ADC_SetRGB_PIPE_Delay(SCART_RGB_DELAY);

#else
    MHAL_ADC_Set_ScartFBDelay(SCART_FB_DELAY);

    MHAL_ADC_Set_ScartRGBDelay(SCART_RGB_DELAY);
#endif
}
#endif

//======================================================================================================
void MApp_Scaler_MM_Set_VideoMute(BOOLEAN bEnableMute, EnuScalerMMVideoMuteCase eScalerMMVideoMuteCase)
{
    switch( eScalerMMVideoMuteCase )
    {
        case E_XC_MM_VIDEO_MUTE_CASE_PHOTO_SMALL_WIN:
        case E_XC_MM_VIDEO_MUTE_CASE_PHOTO_FULL_WIN:
            if( bEnableMute )
            {
                //MApi_XC_GenerateBlackVideo(ENABLE, MAIN_WINDOW);
                msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, 0, MAIN_WINDOW);
            }
            else
            {
                // If is FBL, must wait fpll done~
                if( MApi_XC_IsCurrentFrameBufferLessMode() )
                {
                    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_SCALER_FPLL, ENABLE, 0, MAIN_WINDOW);
                }

                msAPI_Scaler_SetBlueScreen(DISABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);

                //MDrv_MVOP_GetOutputTiming(&stMVOPTiming);
                // wait 4 input vsync before turn on scalar
                //MApi_XC_WaitInputVSync(4, (1000/stMVOPTiming.u8Framerate)*4, MAIN_WINDOW);
            /*
                if( MApi_XC_IsCurrentFrameBufferLessMode() )
                {
                    MApi_XC_WaitFPLLDone();
                    MApi_XC_GenerateBlackVideo(DISABLE, MAIN_WINDOW);
                }
                else
                {
                    MApi_XC_GenerateBlackVideo(DISABLE, MAIN_WINDOW);
                } */

            }
            break;

        default:
            break;
    }

}

//======================================================================================================


#undef MAPP_SCALER_C
