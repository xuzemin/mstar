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

#ifndef MAPP_SCALER_H
#define MAPP_SCALER_H

#include "MApp_Exit.h"
#include "MApp_Key.h"
#include "msAPI_Global.h"
#include "MApp_GlobalSettingSt_Common.h"
#include "MApp_GlobalSettingSt.h"

#ifdef MAPP_SCALER_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

//*************************************************************************
//          Defines
//*************************************************************************

#define ENABLE_CHECK_SET_WIN_RESULT     1

#define HDMI_STABLE_WIN_USE_MODE_INFO   1


#if( ENABLE_3D_PROCESS )//( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA)|| (CHIP_FAMILY_TYPE == CHIP_FAMILY_WHISKY))  // anvi
    #define ENABLE_NEW_3D_FLOW     1
#else
    #define ENABLE_NEW_3D_FLOW     0
#endif

//*************************************************************************
//          Enums
//*************************************************************************
typedef struct
{
    U16 u16VideoWidth;
    U16 u16VideoHeight;
    U8 u8AspectRate;
    U8 u8AFD;
    ///display width
    U32 u32SarWidth;
    ///display height
    U32 u32SarHeight;
} SRC_RATIO_INFO;


typedef struct
{
    MS_WINDOW_TYPE stCapWin;        ///<Capture window

    U8 u8HCrop_Left;    // H Crop Left
    U8 u8HCrop_Right;    // H crop Right
    U8 u8VCrop_Up;      // V Crop Up
    U8 u8VCrop_Down;      // V Crop Down

    U8 u8H_OverScanRatio; //H Crop for DTV,storage
    U8 u8V_OverScanRatio; //V Crop for DTV,storage

} MS_VIDEO_Window_Info_EXT;


//*************************************************************************
//          Global variables
//*************************************************************************

//*************************************************************************
//          Function prototypes
//*************************************************************************

typedef enum
{
    PICTURE_VALUE_CONTRAST,
    PICTURE_VALUE_BRIGHTNESS,
    PICTURE_VALUE_SHARPNESS,
    PICTURE_VALUE_HUE,
    PICTURE_VALUE_SATURATION,
} EN_PICTURE_VALUE;

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


#if ENABLE_3D_PROCESS
typedef enum
{
    E_3D_FULLSCREEN  = 0,
    E_3D_AUTOADAPT   = 1,
    E_3D_CENTER      = 2,
}EN_SC_3D_SIZE ;

typedef enum
{
    E_USER_3D_MODE_OFF   = 0x00,
//To line alternative
    E_USER_3D_MODE_FRAME_PACKING_2_LINE_ALTERNATIVE    = 0x01,
    E_USER_3D_MODE_SIDE_BY_SIDE_HALF_2_LINE_ALTERNATIVE    = 0x02,
    E_USER_3D_MODE_SIDE_BY_SIDE_HALF_INTERLACE_2_LINE_ALTERNATIVE    = 0x03,
    E_USER_3D_MODE_VERTICAL_LINE_ALTERNATIVE_2_VERTICAL_LINE_ALTERNATIVE    = 0x04,
    E_USER_3D_MODE_LINE_ALTERNATIVE_2_LINE_ALTERNATIVE    = 0x05,
    E_USER_3D_MODE_TOP_BOTTOM_2_LINE_ALTERNATIVE    = 0x6,
    E_USER_3D_MODE_FRAME_ALTERNATIVE_2_LINE_ALTERNATIVE    = 0x07,

    E_USER_3D_MODE_FRAME_PACKING_2_TOP_BOTTOM    = 0x10,
    E_USER_3D_MODE_TOP_BOTTOM_2_TOP_BOTTOM    = 0x11,
    E_USER_3D_MODE_FRAME_ALTERNATIVE_2_TOP_BOTTOM    = 0x12,

    E_USER_3D_MODE_FRAME_PACKING_2_SIDE_BY_SIDE_HALF    = 0x20,
    E_USER_3D_MODE_SIDE_BY_SIDE_HALF_2_SIDE_BY_SIDE_HALF    = 0x21,
    E_USER_3D_MODE_LINE_ALTERNATIVE_2_SIDE_BY_SIDE_HALF    = 0x22,

    E_USER_3D_MODE_FRAME_PACKING_2_FRAME_L    = 0x30,
    E_USER_3D_MODE_SIDE_BY_SIDE_HALF_2_FRAME_L    = 0x31,
    E_USER_3D_MODE_TOP_BOTTOM_2_FRAME_L    = 0x32,

    E_USER_3D_MODE_FRAME_PACKING_2_FRAME_ALTERNATIVE_NOFRC    = 0x40,
    E_USER_3D_MODE_SIDE_BY_SIDE_HALF_2_FRAME_ALTERNATIVE_NOFRC    = 0x41,
    E_USER_3D_MODE_SIDE_BY_SIDE_HALF_INTERLACE_2_FRAME_ALTERNATIVE_NOFRC    = 0x42,
    E_USER_3D_MODE_LINE_ALTERNATIVE_2_FRAME_ALTERNATIVE_NOFRC    = 0x43,
    E_USER_3D_MODE_TOP_BOTTOM_2_FRAME_ALTERNATIVE_NOFRC    = 0x44,

    E_USER_3D_MODE_FRAME_PACKING_2_FRAME_ALTERNATIVE    = 0x50,
    E_USER_3D_MODE_SIDE_BY_SIDE_HALF_2_FRAME_ALTERNATIVE    = 0x51,
    E_USER_3D_MODE_LINE_ALTERNATIVE_2_FRAME_ALTERNATIVE    = 0x52,
    E_USER_3D_MODE_TOP_BOTTOM_2_FRAME_ALTERNATIVE    = 0x53,

    E_USER_3D_MODE_NORMAL_2D_2_LINE_ALTERNATIVE    = 0x60,// 2d-->3d, use HShift for shift
    E_USER_3D_MODE_NORMAL_2D_2_FRAME_ALTERNATIVE_NOFRC    = 0x61,// 2d-->3d, use HShift for shift
    E_USER_3D_MODE_NORMAL_2D_HW_2_LINE_ALTERNATIVE_HW = 0x62,

	E_USER_3D_MODE_TOP_BOTTOM_2_SIDE_BY_SIDE_HALF		 = 0x63,
	E_USER_3D_MODE_FRAME_ALTERNATIVE_2_SIDE_BY_SIDE_HALF  = 0x64,
	E_USER_3D_MODE_LINE_ALTERNATIVE_2_TOP_BOTTOM		 = 0x65,
	E_USER_3D_MODE_SIDE_BY_SIDE_HALF_2_TOP_BOTTOM		 = 0x66,
	E_USER_3D_MODE_FRAME_ALTERNATIVE_2_FRAME_L			 = 0x67,
	E_USER_3D_MODE_LINE_ALTERNATIVE_2_FRAME_L			 = 0x68,

    E_USER_3D_MODE_80 = 0x80,
}EN_USER_3D_MODE ;

typedef enum
{
    E_OUTPUT_RESOLUTION_3840X2160,
    E_OUTPUT_RESOLUTION_1920X1080,
    E_OUTPUT_RESOLUTION_3840X1080,
    E_OUTPUT_RESOLUTION_MAX,
}EN_4K2K_OUTPUT_RESOLUTION_TYPE;

typedef struct
{
    /// scaler input 3d type
    EN_3D_TYPE enScalerInput3DType;
    /// scaler output 3d type
    EN_3D_TYPE enScalerOutput3DType;
    /// back end input 3d type
    EN_3D_TYPE enBackEndInput3DType;
    /// Outout timing
    EN_4K2K_OUTPUT_RESOLUTION_TYPE enResolution;
}ST_3D_CONVERTRULE;

typedef struct
{
    /// 3D convert rule
    ST_3D_CONVERTRULE st3DConvertRule[EN_3D_TYPE_NUM];
    /// 3D To 2D convert rule
    ST_3D_CONVERTRULE st3DTo2DConvertRule[EN_3D_TYPE_NUM];
    /// 4K2K 3D convert rule
    ST_3D_CONVERTRULE st4K2K_Under60Hz_3DConvertRule[EN_3D_TYPE_NUM];
    /// 4K2K 60Hz 3D convert rule
    ST_3D_CONVERTRULE st4K2K_60Hz_3DConvertRule[EN_3D_TYPE_NUM];
}ST_3D_BEHAVIOR;

#define _EN_3D_BEHAVIOR_IDX_All_Passive_        (0)
#define _EN_3D_BEHAVIOR_IDX_IN8903_Simple_      (1)
#define _EN_3D_BEHAVIOR_IDX_IN8903_PQ_Optimize_ (2)
#define _EN_3D_BEHAVIOR_MAX_                    (3)

typedef enum
{
    EN_3D_BEHAVIOR_IDX_All_Passive = _EN_3D_BEHAVIOR_IDX_All_Passive_,
    EN_3D_BEHAVIOR_IDX_IN8903_Simple = _EN_3D_BEHAVIOR_IDX_IN8903_Simple_,
    EN_3D_BEHAVIOR_IDX_IN8903_PQ_Optimize = _EN_3D_BEHAVIOR_IDX_IN8903_PQ_Optimize_,
    EN_3D_BEHAVIOR_MAX = _EN_3D_BEHAVIOR_MAX_,
}EN_3D_BEHAVIOR_IDX;
#endif

// MHEG must use crop align, other source dosen't need
#define DTV_CROP_ALIGN_X            2   // 8 byte alignment
#define DTV_CROP_ALIGN_Y            2
#define MEDIA_CROP_ALIGN_X          DTV_CROP_ALIGN_X
#define MEDIA_CROP_ALIGN_Y          DTV_CROP_ALIGN_Y
#define DIGITAL_CROP_ALIGN_X        1
#define DIGITAL_CROP_ALIGN_Y        2
#define ANALOG_CROP_ALIGN_X         1
#define ANALOG_CROP_ALIGN_Y         2
#define OVERSCAN_RATIO              1000

//===============================================================

#if(ENABLE_CHECK_SET_WIN_RESULT)
extern BOOLEAN g_Scaler_bSetWidnowResult;
#endif

//===============================================================

#if ENABLE_BACKLIGHT_PWM_SYNC_WITH_FRAMERATE
INTERFACE void SetPWMto2PanelVFreq(U8 ratio);
#endif
INTERFACE void MApp_PreInitPanelTiming(void);

INTERFACE U8 MApp_Scaler_FactoryAdjBrightness(U8 u8Brightness, U8 u8SubBrightness);
INTERFACE U8 MApp_Scaler_DesignAdjBrightness(U8 u8Brightness, U8 u8SubBrightness);
INTERFACE U8 MApp_Scaler_FactoryContrast(U8 u8Contrast, U8 u8SubContrast);
INTERFACE U8 MApp_Scaler_DesignContrast(U8 u8Contrast, U8 u8SubContrast);
INTERFACE void MApp_Scaler_ResetZoomFactor(EN_MENU_AspectRatio enAspectratio);
INTERFACE BOOLEAN MApp_Scaler_IncLeftZoomfactor(S16 s16ZoomFator);
INTERFACE BOOLEAN MApp_Scaler_IncRightZoomfactor(S16 s16ZoomFator);
INTERFACE BOOLEAN MApp_Scaler_IncUpZoomfactor(S16 s16ZoomFator);
INTERFACE BOOLEAN MApp_Scaler_IncDownZoomfactor(S16 s16ZoomFator);


#if 0 // Debug Over Scan flow
    #define MApp_Scaler_EnableOverScan(en)  do { \
        printf("\n%s():%u: call EnableOverScan(%u)", __FUNCTION__, __LINE__, (en)); \
    MApp_Scaler_EnableOverScan_2((en)); \
} while(0)
#else
    #define MApp_Scaler_EnableOverScan  MApp_Scaler_EnableOverScan_2
#endif

INTERFACE void MApp_Scaler_EnableOverScan_2(BOOLEAN bEnable);


INTERFACE void MApp_Scaler_Adjust_OverscanRatio( SCALER_WIN eWindow,
                        INPUT_SOURCE_TYPE_t enInputSourceType,
                        XC_SETWIN_INFO *pstXC_SetWin_Info);

#if (MEMORY_MAP <= MMAP_32MB)
INTERFACE void MApp_Scaler_Adjust_OverscanRatio_RFBL(
                       INPUT_SOURCE_TYPE_t enInputSourceType,
                       XC_SETWIN_INFO *pstXC_SetWin_Info);
#endif
INTERFACE void MApp_Scaler_Adjust_AspectRatio(SCALER_WIN eWindow,
                                                EN_ASPECT_RATIO_TYPE enVideoScreen,
                                                MS_WINDOW_TYPE *pstCropWin,
                                                MS_WINDOW_TYPE *pstDstWin,
                                                SRC_RATIO_INFO *pstSrcRatioInfo,
                                                BOOL bSkipAFDCrop);

#if ENABLE_FBL_ASPECT_RATIO_BY_MVOP
INTERFACE void MApp_Scaler_SetFixVtotal(U8 u8Interlace, U16 u16FrameRate, U16 u16VDE);
INTERFACE void MApp_Scaler_SetFBLTimingForAspectRatio(EN_ASPECT_RATIO_TYPE enVideoScreen);
INTERFACE void MApp_Scaler_Adjust_AspectRatio_FBL(EN_ASPECT_RATIO_TYPE enVideoScreen, MS_WINDOW_TYPE *ptSrcWin);
#endif

#if 0
#define MApp_Scaler_SetWindow(a,b,c,d,e,f) do {                            \
    PRINT_CURRENT_LINE(); printf(" Call MApp_Scaler_SetWindow\n");         \
    MApp_Scaler_SetWindow2(a,b,c,d,e,f);                                  \
} while(0)
#else
#define MApp_Scaler_SetWindow(a,b,c,d,e,f)  MApp_Scaler_SetWindow2((a),(b),(c),(d),(e),(f))
#endif
INTERFACE void MApp_Scaler_SetWindow2(MS_WINDOW_TYPE *ptSrcWin,
                                            MS_WINDOW_TYPE *ptCropWin,
                                            MS_WINDOW_TYPE *ptDstWin,
                                            EN_ASPECT_RATIO_TYPE enVideoScreen,
                                            INPUT_SOURCE_TYPE_t enInputSourceType,
                                            SCALER_WIN eWindow);
///
/// Make sure that the display window won't change by other function
///  implicitly
///
INTERFACE void MApp_Scaler_AlignWindow(MS_WINDOW_TYPE *pWindow, U16 u8AlignX, U16 u8AlignY);
INTERFACE void MApp_Scaler_Setting_SetVDScale (EN_MENU_AspectRatio eAspect, SCALER_WIN eWindow);

//#define MApp_Scaler_GetAspectRatio(eWindow,eAspect) ((printf("%u : %s\n", __LINE__, __FILE__))?(MApp_Scaler_GetAspectRatio_2(eWindow,eAspect)):(0))
INTERFACE EN_ASPECT_RATIO_TYPE MApp_Scaler_GetAspectRatio(SCALER_WIN eWindow,EN_MENU_AspectRatio eAspect);


INTERFACE void MApp_Scaler_CalculateAspectRatio(XC_SETWIN_INFO *pstXC_SetWin_Info,
                                        EN_ASPECT_RATIO_TYPE enVideoScreen,
                                       MS_WINDOW_TYPE *pstCropWin,
                                       MS_WINDOW_TYPE *pstDstWin);
INTERFACE void MApp_Scaler_Setting_HDMI_PAR(void);

INTERFACE void MApp_Scaler_MainWindowSyncEventHandler(INPUT_SOURCE_TYPE_t src, void* para);
INTERFACE void MApp_Scaler_SubWindowSyncEventHandler(INPUT_SOURCE_TYPE_t src, void* para);
INTERFACE void MApp_Scaler_MainWindowOnOffEventHandler(INPUT_SOURCE_TYPE_t src, void* para);
INTERFACE void MApp_Scaler_SubWindowOnOffEventHandler(INPUT_SOURCE_TYPE_t src, void* para);
INTERFACE void MApp_Scaler_MainWindowPeriodicHandler(INPUT_SOURCE_TYPE_t src, BOOLEAN bRealTimeMonitorOnly);
INTERFACE void MApp_Scaler_SubWindowPeriodicHandler(INPUT_SOURCE_TYPE_t src, BOOLEAN bRealTimeMonitorOnly);
INTERFACE void MApp_Scaler_CVBS1OutSyncEventHandler(INPUT_SOURCE_TYPE_t src, void* para);
INTERFACE void MApp_Scaler_CVBS1OutOnOffEventHandler(INPUT_SOURCE_TYPE_t src, void* para);

INTERFACE void MApp_Scaler_CVBS2OutSyncEventHandler(INPUT_SOURCE_TYPE_t src, void* para);
INTERFACE void MApp_Scaler_CVBS2OutOnOffEventHandler(INPUT_SOURCE_TYPE_t src, void* para);

INTERFACE void MApp_Scaler_GetVidWinInfo(MS_VIDEO_Window_Info_EXT *pstWindow_info, SCALER_WIN eWindow);
INTERFACE void MApp_Scaler_SetVidWinInfo(INPUT_SOURCE_TYPE_t src,MS_VIDEO_Window_Info_EXT *pstWindow_info, SCALER_WIN eWindow);
INTERFACE void MApp_Scaler_GetOverScan(INPUT_SOURCE_TYPE_t src, XC_SETWIN_INFO *pstXC_SetWin_Info);

INTERFACE void MApp_Scaler_SetTiming(INPUT_SOURCE_TYPE_t enInputSourceType, SCALER_WIN eWindow);
INTERFACE BOOLEAN MApp_Scaler_Check_PointToPoint_Mode(PQ_WIN eWindow);

INTERFACE void MApp_Scaler_SetScalerDNRAddress(U32 mmap_s_adrress,U32 mmap_length);
INTERFACE void MApp_Scaler_SetOutputPanelType(U8 u8ResolutionType, SCALER_WIN eWindow);

#if ENABLE_3D_PROCESS
INTERFACE BOOLEAN MApp_3D_SetLRSwitchFlag(MS_BOOL bEnable);
INTERFACE BOOLEAN MAPP_Scaler_Is3DSubWin(SCALER_WIN eWindow);
INTERFACE void MApp_Scaler_Adjust3DDisplayWin(XC_SETWIN_INFO *pstXC_SetWin_Info, SCALER_WIN eWindow, EN_ASPECT_RATIO_TYPE en3DARCType);
INTERFACE E_XC_3D_INPUT_MODE MAPP_Scaler_MapUI3DModeToXCInput3DMode(EN_3D_TYPE eInputUI3DType);
INTERFACE EN_3D_TYPE MAPP_Scaler_MapXC3DModeToUI3DMode(E_XC_3D_INPUT_MODE eInput3DMode);
INTERFACE BOOL MAPP_Scaler_MapUIDetectMode(EN_3D_DETECT_MODE eDetect3DMode);
INTERFACE U16 MAPP_Scaler_Map3DFormatTo3DUserMode(E_XC_3D_INPUT_MODE eInput3DFormat);

#if(ENABLE_NEW_3D_FLOW)
INTERFACE BOOLEAN MApp_Scaler_SetVideo3DMode(EN_3D_TYPE eUi3DType);
#else
INTERFACE BOOLEAN MApp_Scaler_SetVideo3DMode(U16 u16_Video3Dmode);
INTERFACE E_XC_3D_OUTPUT_MODE MApp_Set_3DOutputMode(U16 u16_Video3Dmode);
#endif

INTERFACE void MApp_Scaler_EnableManualDetectTiming(BOOLEAN bEnable);
INTERFACE BOOLEAN MApp_Scaler_IsManualDetectTiming(void);

#if(ENABLE_NEW_3D_FLOW)
typedef enum
{
    SCLAER_3D_CFG_FOR_FORCE_2D,
    SCLAER_3D_CFG_FOR_AUTO,
} EnuScaler3DConfigCase;
void MApp_Scaler_3D_Config(EnuScaler3DConfigCase eScaler3DConfigCase);
INTERFACE BOOLEAN MApp_Scaler_Set_3DMode(E_XC_3D_INPUT_MODE eXcInput3DFormat);
#else
INTERFACE BOOLEAN MApp_Scaler_Set_3DMode(U16 u16_Video3Dmode);
#endif

INTERFACE MS_BOOL MApi_Scaler_Set3DInfo(E_XC_3D_INPUT_MODE enInMode,E_XC_3D_OUTPUT_MODE enOutMode);
INTERFACE void MApp_Scaler_Adjust_3D_CropWin(MS_WINDOW_TYPE *pstCropWin);
#if ENABLE_3D_PROCESS
INTERFACE BOOLEAN MApp_3D_GetLRSwitchFlag(void);
#endif
#if (ENABLE_MFC_6M20 || ENABLE_MFC_6M30 || ENABLE_6M40_4KX2K_PROCESS || ENABLE_6M50_4KX2K_PROCESS)
INTERFACE PANEL_3D_MODE MAPP_Scaler_MapUi3DFormatToUrsa3DMode(EN_3D_TYPE enUi3DType);
INTERFACE void MAPP_Scaler_Map3DFormatToUrsa3DMode(E_XC_3D_INPUT_MODE eInput3DFormat);
#endif
#if ENABLE_3D_PROCESS   // anvi
void MApp_Scaler_3D_Behavior_init(void);
#endif
#endif
INTERFACE void MApp_Scaler_GetWinInfo(XC_SETWIN_INFO* pWindowInfo, SCALER_WIN eWindow);

#if(PATCH_FOR_V_RANGE)
INTERFACE void MApp_Scaler_SetCustomerWindow(MS_WINDOW_TYPE *ptSrcWin, MS_WINDOW_TYPE *ptCropWin, MS_WINDOW_TYPE *ptDstWin, SCALER_WIN eWindow);
#endif

typedef enum
{
    E_XC_FB_CASE_MM_PHOTO_PREVIEW,
    E_XC_FB_CASE_MM_PHOTO_FULL_DISP,
} EnuScalerFBCase;
void MApp_Scaler_Setup_FB(EnuScalerFBCase eScalerFBCase);

BOOL MApp_Scaler_Is_InputSignal3D(void);
BOOL MApp_Scaler_Is_Input3DMode(void);
BOOL MApp_Scaler_Is_Output3DMode(void);

BOOL MApp_Scaler_Is_3DTypeSupported(U8 u8Index);
BOOL MApp_Scaler_Is_AspectRatioSupported_ByUI(EN_MENU_AspectRatio eUiAspectRatio);
void MApp_Scaler_UpdateAspectRatioVar( SCALER_WIN eWindow );

#if(ENABLE_3D_PROCESS)
char* MApp_Scaler_Get_Xc3DInputName(E_XC_3D_INPUT_MODE eXC_3D_INPUT_MODE);
char* MApp_Scaler_Get_Xc3DOutputName(E_XC_3D_OUTPUT_MODE eXC_3D_OUTPUT_MODE);
char* MApp_Scaler_Get_Ui3DTypeName(EN_3D_TYPE eUi_3D_TYPE);
BOOL MApp_Scaler_3D_IsSrcTypeSupport3DFunction(void);
void MApp_Scaler_3D_ResetForChangeTiming(void);
void MApp_Scaler_3D_ResetForChangeSrc(void);
#endif

void MApp_Scaler_AutoDisablePQ_UC(void);

void MApp_Scaler_SetupADC(SCALER_WIN eWindow);
#if(INPUT_SCART_VIDEO_COUNT > 0)
void MApp_Scaler_SetupADC_ScartRGB(SCALER_WIN eWindow);
#endif

//===========================================================================
typedef enum
{
    E_XC_MM_VIDEO_MUTE_CASE_PHOTO_SMALL_WIN,
    E_XC_MM_VIDEO_MUTE_CASE_PHOTO_FULL_WIN,
} EnuScalerMMVideoMuteCase;
void MApp_Scaler_MM_Set_VideoMute(BOOLEAN bEnableMute, EnuScalerMMVideoMuteCase eScalerMMVideoMuteCase);

//============================================================================

#undef INTERFACE
#endif

