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
// Copyright (c) 2006-2008 MStar Semiconductor, Inc.
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

#define _MAPP_PHOTO_DISPLAY_C_
///////////////////////////////////////////////////////////////////////////////
/// @file   mapp_photo_display.c
/// @author MStar Semiconductor Inc.
/// @brief  Photo display Module
///////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include "drvGlobal.h"
#include "msAPI_Timer.h"
#include "drvCPU.h"

#include "msAPI_MailBox.h"
#include "msAPI_FCtrl.h"
#include "msAPI_FSCommon.h"
#include "mapp_photo_display.h"

#if (defined(ENABLE_PTP) && (ENABLE_PTP))
#include "mapp_ptp.h"
#endif // #if (defined(ENABLE_PTP) && (ENABLE_PTP))

#include "mapp_photo.h"
#include "mapp_stillimage_sharememcfg.h"

#include "drvMIU.h"
#include "msAPI_MIU.h"

#include "msAPI_OSD.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "apiXC_Sys.h"
#include "msAPI_Video.h"
#include "MApp_Scaler.h"
#include "apiGOP.h"
#include "msAPI_Global.h"
#include "MApp_XC_PQ.h"
#include "MApp_XC_Sys.h"
#include "MApp_MVDMode.h"
#include "MApp_InputSource.h"
#if (ENABLE_SUPPORT_MM_PHOTO_4K_2K ==1)
#include "drvUrsa6M40.h"
#include "drvISR.h"
#include "MApp_ZUI_APIgdi.h"
#endif
//to solve __ASSERT problem
#include "debug.h"
#include "mapp_music.h"

#if (ENABLE_DMP)

//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------
#define GE_MARGIN       (8)

#define THUMBNAIL_SHRINK_BUFF_FMT               (GFX_FMT_YUV422)
#define THUMBNAIL_SHRINK_BUFF_BYTE_PER_PIXEL    (2) // for YUV422 format
#define THUMBNIAL_SHRINK_BUFF_BYTE_ALIGNMENT    (0x8) // 8 byte alignment
#define THUMBNIAL_SHRINK_BUFF_PIXEL_ALIGNMENT   (THUMBNIAL_SHRINK_BUFF_BYTE_ALIGNMENT / THUMBNAIL_SHRINK_BUFF_BYTE_PER_PIXEL)

#define _U32_MAX    (0xffffffff)
#define ENABLE_SPEED_MUSIC_BACKGROUND_PLAY       1

#if ENABLE_4K2K
#define NOT_FIT_SCREEN_IN_4K2K  0
#define ENABLE_4K2K_DUMP_BUF    0
// after we can get 4K2K panel width/height, need to remove below macro.
#define PANEL_4K2K_WIDTH    3840
#define PANEL_4K2K_HEIGHT   2160
#endif

//photo display size: 0: fit panel; 1: original size, but if resulotion > panel, it will fit panel.
#define  PHOTO_DISPLAY_BY_ORIGINAL 0
//photo zoom base: 0: base is fit panel, 1: base is original, but if resulotion > panel, using fit panel.
#define PHOTO_ZOOM_BY_ORIGINAL 0

//-------------------------------------------------------------------------------------------------
// Type and Structure Declaration
//-------------------------------------------------------------------------------------------------
typedef enum
{
    EN_PHOTO_INFO_NONE = 0,
    EN_PHOTO_INFO_ALL_COLLECT,
} EN_PHOTO_INSTANCE_INFO_STATE;

typedef struct
{
    U16 u16Width;
    U16 u16Height;
    EN_PHOTO_ORIENTATION enOrientation;
} ST_PHOTO_DECODE_INFO;

typedef struct
{
    EN_PHOTO_INSTANCE_INFO_STATE    enState;
    ST_PHOTO_CAPTURE_RECT           stSrcImg;       // source image
    ST_PHOTO_CAPTURE_RECT           stDstBuff;      // destination buffer
    EN_PHOTO_ALIGNMENT              enAlign;        // alignment method
    EN_PHOTO_RESIZE                 enResize;       // resize method
    U16                             u16ResizeRatio; // eg. 100 equals to 1, 10 equals to 0.1 and 1000 equals to 10
    EN_PHOTO_ROTATION               enRotation;
    BOOLEAN                         bMirrorX;
    BOOLEAN                         bMirrorY;
    ST_PHOTO_CAPTURE_RECT           stResizedImg;   // the image that has been resized, most likely shrinked
    ST_PHOTO_CAPTURE_RECT           stOutputImg;    // the information relating to really output image
    EN_PHOTO_ZOOMING                enZooming;
    EN_PHOTO_ZOOMING                enZoomingNew;   // the value user specified
} ST_PHOTO_INSTANCE_INFO;

typedef enum
{
    EN_SPECIAL_EFFECT_INIT = 0x1,
    EN_SPECIAL_EFFECT_ZOOM = 0x2,
    EN_SPECIAL_EFFECT_MOVE = 0x4,
    EN_SPECIAL_EFFECT_ROTATE = 0x8,
} EN_PHOTO_SPECIAL_EFFECT;

#if PHOTO_SLIDE_SHOW_EFFECT
typedef struct
{
    U16 u16Width;
    U16 u16Height;
    U16 u16Pitch;
} SlideShowPhotoInfo;
#endif

#if ENABLE_4K2K
typedef enum
{
    E_PHOTO_4K2K_LEFT_TOP = 0,
    E_PHOTO_4K2K_RIGHT_TOP,
    E_PHOTO_4K2K_LEFT_BOTTOM,
    E_PHOTO_4K2K_RIGHT_BOTTOM,
} EN_PHOTO_4K2K_BLOCK;
#endif

//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------
// error/debug/info message
#define PHOTO_DISP_MSG(x)       //(x)

// remove lnt warning message
#define SWAP32(a, b) \
    { \
        U32 c; \
        c = a; \
        a = b; \
        b = c; \
    }

#define SWAP16(a, b) \
    { \
        U16 c; \
        c = a; \
        a = b; \
        b = c; \
    }

#define SWAP8(a, b) \
    { \
        U8 c; \
        c = a; \
        a = b; \
        b = c; \
    }

#define HALF(x)         ((x+1)/2)
#define REST_HALF(x)    (x - (x+1)/2)

//-------------------------------------------------------------------------------------------------
// Global Variables
//-------------------------------------------------------------------------------------------------
extern BOOLEAN m_bFLG_PREVIEW;


//-------------------------------------------------------------------------------------------------
// Local Variables
//-------------------------------------------------------------------------------------------------
#if PHOTO_SLIDE_SHOW_EFFECT
static EN_PHOTO_ROTATION m_enRotation;
static EN_PHOTO_ZOOMING  m_enZooming;
static U16 m_u16PhotoSrcWidth, m_u16PhotoSrcHeight;
static U16 m_u16PhotoSrcX, m_u16PhotoSrcY;
static S16 m_s16PhotoOffsetX, m_s16PhotoOffsetY;
static U16 m_u16PhotoDstWidth, m_u16PhotoDstHeight;
static U16 m_u16PhotoDstX, m_u16PhotoDstY;
static EN_PHOTO_SLIDE_SHOW_EFFECT m_SlideShowEffect = E_SLIDE_SHOW_EFFECT_RANDOM;
#if ENABLE_ZOOM_MAP
static U16 m_u16ZoomImageWidth, m_u16ZoomImageHeight;
static U16 m_u16ZoomCaptureWidth, m_u16ZoomCaptureHeight;
static U16 m_u16ZoomDenominatorRotate, m_u16ZoomNumeratorRotate;
#endif
#endif // #if PHOTO_SLIDE_SHOW_EFFECT

#if (SHOW_PARTIALLY_DECODING_PHOTO)
static U16 m_u16PhotoPreviewWidth = 0, m_u16PhotoPreviewHeight = 0;
#endif // #if (SHOW_PARTIALLY_DECODING_PHOTO)

static BOOLEAN m_bMirrorX, m_bMirrorY;
static BOOLEAN m_bDoAutoRotateMirror;
static ST_PHOTO_INSTANCE_INFO stPhotoInstanceInfo;
static EN_PHOTO_ZOOMING enPhotoZooming = EN_PHOTO_ZOOM_1;
static U16 u16ViewWinX, u16ViewWinY, u16ViewWinWidth, u16ViewWinHeight;
//gif special
static BOOLEAN stbIsAllFrameDecodeDone = FALSE;
static BOOLEAN stbIsAllFrameDisplayedDone = FALSE;
static U32 stu32DisplayedFrameIndex = 0;
//MPO special
static BOOLEAN bMPODisplayEnabled = FALSE;

static ST_PHOTO_DECODE_INFO m_stPhotoDecodeInfo;

//-------------------------------------------------------------------------------------------------
// Local Function Prototypes
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Function Implementation
//-------------------------------------------------------------------------------------------------
EN_PHOTO_ROTATION MApp_Photo_GetRotationMode(void)
{
    return m_enRotation;
}

void MApp_Photo_SlideShow(BOOLEAN bEnable)
{
    m_SlideShowEffect = bEnable ? E_SLIDE_SHOW_EFFECT_RANDOM : E_SLIDE_SHOW_EFFECT_NORMAL;
}

static void _MApp_Photo_Display_ColorFmtTransfer(
        U16 u16Width, U16 u16Height,
        U32 u32SrcBuffAddr, GFX_Buffer_Format eSrcFmt,
        U32 u32DstBuffAddr, GFX_Buffer_Format enDstFmt)
{
    GEBitBltInfo BitbltInfo;
    GEPitBaseInfo PitBaseInfo;

    memset(&BitbltInfo, 0, sizeof(GEBitBltInfo));
    memset(&PitBaseInfo, 0, sizeof(GEPitBaseInfo));

    BitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;
    BitbltInfo.BmpFlag = GFXDRAW_FLAG_DEFAULT;
    BitbltInfo.dst_fm = enDstFmt;
    BitbltInfo.src_fm = eSrcFmt;
    BitbltInfo.BitbltCoordinate.v2_x = 0;
    BitbltInfo.BitbltCoordinate.v2_y = 0;
    BitbltInfo.BitbltCoordinate.direction = 0;

    BitbltInfo.BitbltCoordinate.width = u16Width & 0xfffe;
    BitbltInfo.BitbltCoordinate.height = u16Height & 0xfffe;

    BitbltInfo.BitbltCoordinate.v0_x = 0;
    BitbltInfo.BitbltCoordinate.v0_y = 0;

    BitbltInfo.src_width = u16Width & 0xfffe;
    BitbltInfo.src_height = u16Height & 0xfffe;

    if (eSrcFmt == GFX_FMT_ARGB8888)
    {
        PitBaseInfo.sb_pit = u16Width * 4;
    }
    else if (eSrcFmt==GFX_FMT_ARGB1555)
    {
        PitBaseInfo.sb_pit = u16Width*2;
    }
    else if (eSrcFmt==GFX_FMT_YUV422)
    {
        PitBaseInfo.sb_pit = u16Width * 2;
    }
    else
    {
        __ASSERT(0);
        return;
    }

    if (enDstFmt == GFX_FMT_ARGB8888)
    {
        PitBaseInfo.db_pit = u16Width * 4;

        // clear buffer to black
        msAPI_GE_ClearFrameBufferByWord((U32)u32DstBuffAddr, (4L * u16Width * u16Height), 0x00000000);
        // after clear frame buffer, flush cmd
        MApi_GFX_FlushQueue();
    }
    else if (enDstFmt == GFX_FMT_YUV422)
    {
        PitBaseInfo.db_pit = u16Width * 2;

        // clear buffer to black
        msAPI_GE_ClearFrameBufferByWord((U32)u32DstBuffAddr, (2L * u16Width * u16Height), 0x80008000);
        // after clear frame buffer, flush cmd
        MApi_GFX_FlushQueue();
    }
    else
    {
        __ASSERT(0);
        return;
    }

    PitBaseInfo.sb_base = u32SrcBuffAddr;
    PitBaseInfo.db_base = u32DstBuffAddr;

    msAPI_OSD_SetClipWindow(
            BitbltInfo.BitbltCoordinate.v0_x,
            BitbltInfo.BitbltCoordinate.v0_y,
            BitbltInfo.BitbltCoordinate.v0_x + BitbltInfo.BitbltCoordinate.width,
            BitbltInfo.BitbltCoordinate.v0_y + BitbltInfo.BitbltCoordinate.height);

    msAPI_GE_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_255, GFX_YUV_OUT_255, GFX_YUV_IN_255, GFX_YUV_YUYV, GFX_YUV_YUYV);

    msAPI_GE_SetPatchMode(TRUE);
    msAPI_GE_BitBlt(&BitbltInfo, &PitBaseInfo);
    // after BitBlt, flush cmd
    MApi_GFX_FlushQueue();
    msAPI_GE_SetPatchMode(FALSE);

    PHOTO_DISP_MSG(printf("stBitbltInfo: \n"));
    PHOTO_DISP_MSG(printf("\ttype flag: %u\n", BitbltInfo.BitBltTypeFlag));
    PHOTO_DISP_MSG(printf("\tbmp flag: %u\n", BitbltInfo.BmpFlag));
    PHOTO_DISP_MSG(printf("\tdest fmt: %u\n", BitbltInfo.dst_fm));
    PHOTO_DISP_MSG(printf("\tsrc fmt: %u\n", BitbltInfo.src_fm));
    PHOTO_DISP_MSG(printf("\tbmp hnd: %d\n", BitbltInfo.bmphandle));
    PHOTO_DISP_MSG(printf("\tsrc width: %u\n", BitbltInfo.src_width));
    PHOTO_DISP_MSG(printf("\tsrc height: %u\n", BitbltInfo.src_height));
    PHOTO_DISP_MSG(printf("\tcoord v0x: %u\n", BitbltInfo.BitbltCoordinate.v0_x));
    PHOTO_DISP_MSG(printf("\tcoord v0y: %u\n", BitbltInfo.BitbltCoordinate.v0_y));
    PHOTO_DISP_MSG(printf("\tcoord width: %u\n", BitbltInfo.BitbltCoordinate.width));
    PHOTO_DISP_MSG(printf("\tcoord height: %u\n", BitbltInfo.BitbltCoordinate.height));
    PHOTO_DISP_MSG(printf("\tcoord v2x: %u\n", BitbltInfo.BitbltCoordinate.v2_x));
    PHOTO_DISP_MSG(printf("\tcoord v2y: %u\n", BitbltInfo.BitbltCoordinate.v2_y));
    PHOTO_DISP_MSG(printf("\tcoord direct: %u\n", BitbltInfo.BitbltCoordinate.direction));
    PHOTO_DISP_MSG(printf("stPitBaseInfo: \n"));
    PHOTO_DISP_MSG(printf("\tsrc pitch: %x\n",PitBaseInfo.sb_pit));
    PHOTO_DISP_MSG(printf("\tdst pitch: %x\n",PitBaseInfo.db_pit));
    PHOTO_DISP_MSG(printf("\tsrc base: %x\n",PitBaseInfo.sb_base));
    PHOTO_DISP_MSG(printf("\tdst base: %x\n",PitBaseInfo.db_base));
}

extern VDEC_DispInfo gstVidStatus;
//******************************************************************************
/// Set Scaler/MVOP configuration
/// @param  InputX/InputY/InputWidth/InputHeight :  <--- Means input valid image which sending to XC through MVOP
/// @param  OutputX/OutputY/OutputWidth/OutputHeight : <--- Means panel size
/// @param  u32SrcAddr/u16SrcWidth/u16SrcHeight : <--- Means after adjust panel size
/// @return enumMPlayerMediaType
//******************************************************************************
static void _MApp_Photo_SetScalarVOP2Display(
        U16 u16InputX, U16 u16InputY, U16 u16InputWidth, U16 u16InputHeight,
        U16 u16OutputX, U16 u16OutputY, U16 u16OutputWidth, U16 u16OutputHeight,
        U32 u32SrcAddr, U16 u16SrcWidth, U16 u16SrcHeight)
{
    MVOP_InputCfg dc_param;
    MVOP_VidStat videoSetting;
    MS_WINDOW_TYPE tCropWin, tDstWin;

    //MVOP_Timing stMVOPTiming;


    // Enable Blue Screen
    //for gif animation , only first frame do blue screen. For other type, stu32DisplayedFrameIndex always is zero.
    if(stu32DisplayedFrameIndex == 0)
    {
    #if 1 // Use new method
        MApp_Scaler_MM_Set_VideoMute(ENABLE, E_XC_MM_VIDEO_MUTE_CASE_PHOTO_FULL_WIN);
    #else
        //Patch for MenuLoad write fail when power on
        //And add this here is to be pare with the disable operation at the end of this function
        MApi_XC_GenerateBlackVideo(ENABLE, MAIN_WINDOW);
        msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
    #endif
    }

    MDrv_MVOP_Init();


    // set mvop parameters
    MDrv_MVOP_EnableBlackBG();
    MDrv_MVOP_Enable(FALSE);

#if (ENABLE_MIU_1 == ENABLE)
    //switch MIU
    MDrv_MVOP_MiuSwitch((u32SrcAddr & MIU_INTERVAL) == MIU_INTERVAL);
#endif

    memset(&dc_param, 0, sizeof(dc_param));
    dc_param.u16HSize = (u16SrcWidth + 7) & 0xfff8;
    dc_param.u16VSize = u16SrcHeight;
    dc_param.u32YOffset = u32SrcAddr;
    dc_param.u32UVOffset = u32SrcAddr;
    dc_param.bSD = 1;
    dc_param.bYUV422 = 1;
    dc_param.bProgressive = 1;
    dc_param.bUV7bit = 0;
    dc_param.bDramRdContd = 1;
    dc_param.bField = 0;
    dc_param.b422pack = 1;
    dc_param.u16StripSize = dc_param.u16HSize;
    MDrv_MVOP_SetInputCfg(MVOP_INPUT_DRAM, &dc_param);

    memset(&videoSetting, 0, sizeof(MVOP_VidStat));
    videoSetting.u16HorSize = dc_param.u16HSize;
    videoSetting.u16VerSize = u16SrcHeight;

#if (SUPPORT_MM_PHOTO_4K)//defined(SCALER_DNR_4K_PHOTO_BUF_LEN) && (SCALER_DNR_4K_PHOTO_BUF_LEN!=0)
    videoSetting.u16FrameRate = 6000;//for 4K2K
#else
    if (MApi_XC_IsCurrentFrameBufferLessMode())
    {
        videoSetting.u16FrameRate = 60000;  //modify frame rate = 50000 for FBL
    }
    else
    {
        videoSetting.u16FrameRate = 25000;  //modify frame rate = 25000 to 20000 to save BW for Gop
    }
#endif
    videoSetting.u8AspectRate = ASP_4TO3;
    videoSetting.u8Interlace = 0;
    MDrv_MVOP_SetOutputCfg(&videoSetting, FALSE);

    // why odd width size doesn't work
    //stVOPTiming.u16Width = u16SrcWidth & 0xfffe;

    // set scaling aspect to program
    stSystemInfo[MAIN_WINDOW].enAspectRatio = VIDEOSCREEN_ORIGIN;

    gstVidStatus.u16CropBottom = 0;
    gstVidStatus.u16CropTop = 0;
    gstVidStatus.u16CropRight = u16SrcWidth - u16InputWidth;
    gstVidStatus.u16CropLeft = 0;

    tCropWin.x = u16InputX;
    tCropWin.y = u16InputY;

    tCropWin.width = u16InputWidth & 0xfffe;
    tCropWin.height = u16InputHeight;

    tDstWin.x = u16OutputX;
    tDstWin.y = u16OutputY;
    tDstWin.width = u16OutputWidth;
    tDstWin.height = u16OutputHeight;

    //printf("\n[Photo tCropWin] x = %x, y = %x, w = %x, h = %x", tCropWin.x, tCropWin.y, tCropWin.width, tCropWin.height);
    //printf("\n[Photo tDstWin] x = %x, y = %x, w = %x, h = %x", tDstWin.x, tDstWin.y, tDstWin.width, tDstWin.height);

#if SAVE_BW_PHOTO_SLIDE_SHOW
    if (MApi_XC_IsFreezeImg(MAIN_WINDOW))
    {
        MApi_XC_FreezeImg(FALSE, MAIN_WINDOW);
    }
#endif

    MApp_Scaler_EnableOverScan(FALSE);
    // enable mvop
    MDrv_MVOP_Enable(TRUE);


    // Setup scaler ....

#if ENABLE_3D_PROCESS
    if(!bMPODisplayEnabled)
    {
        MApp_Scaler_EnableManualDetectTiming(TRUE);
      #if ENABLE_NEW_3D_FLOW
        MApp_Scaler_SetVideo3DMode(EN_3D_BYPASS);
      #else
        MApp_Scaler_SetVideo3DMode(MAPP_Scaler_Map3DFormatTo3DUserMode(E_XC_3D_INPUT_MODE_NONE));
      #endif
    }
#endif
    MApp_Scaler_SetWindow(NULL, &tCropWin, &tDstWin, stSystemInfo[MAIN_WINDOW].enAspectRatio,
            SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);

    MApp_Picture_Setting_SetColor(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);

#if ENABLE_3D_PROCESS
    if(bMPODisplayEnabled)
    {
        MApp_Scaler_EnableManualDetectTiming(TRUE);
      #if ENABLE_NEW_3D_FLOW
        MApp_Scaler_SetVideo3DMode(EN_3D_FRAME_PACKING);
      #else
        MApp_Scaler_SetVideo3DMode(MAPP_Scaler_Map3DFormatTo3DUserMode(E_XC_3D_INPUT_FRAME_PACKING));
      #endif
    }
#endif

    // Setup output timing
    MApp_Scaler_SetTiming(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);

    // Enable scaler periodic task
    MAPI_XC_MUX_ONOFF_PERIODIC_HANDLER(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), ENABLE);

    // UnMute
#if 1 // Use new method

    MApp_Scaler_MM_Set_VideoMute(DISABLE, E_XC_MM_VIDEO_MUTE_CASE_PHOTO_FULL_WIN);

#else

    msAPI_Scaler_SetBlueScreen(DISABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);

    MDrv_MVOP_GetOutputTiming(&stMVOPTiming);
    // wait 4 input vsync before turn on scalar
    MApi_XC_WaitInputVSync(4, (1000/stMVOPTiming.u8Framerate)*4, MAIN_WINDOW);

    if(MApi_XC_IsCurrentFrameBufferLessMode())
    {
        MApi_XC_WaitFPLLDone();
        MApi_XC_GenerateBlackVideo(DISABLE, MAIN_WINDOW);
    }
    else
    {
        MApi_XC_GenerateBlackVideo(DISABLE, MAIN_WINDOW);
    }
#endif

    //printf("\n u32SrcAddr=%x ", u32SrcAddr );
    //printf("\n u16HSize=%x ,  u16VSize=%x ", ((u16SrcWidth&0xfffe) + 15) & 0xfff0, u16SrcHeight);
    //printf("\n u16InputX=%x,u16InputY=%x, u16InputWidth=%x , u16InputHeight=%x ", u16InputX, u16InputY , u16InputWidth, u16InputHeight);
    //printf("\n u16OutputX=%x,u16OutputY=%x, u16OutputWidth=%x , u16OutputHeight=%x ", u16OutputX, u16OutputY , u16OutputWidth, u16OutputHeight);
}

#if PHOTO_SLIDE_SHOW_EFFECT
static BOOLEAN _MApp_Photo_ShowEffect(void)
{
    //bitblt info, Capture
    GEBitBltInfo stBitbltInfo;
    GEPitBaseInfo stPitBaseInfo;
    S16 s16CapX, s16CapY;
    U16 u16CapW, u16CapH;
    U16 u16DstX, u16DstY, u16DstW, u16DstH; //destination info
    U16 u16numerator, u16denominator; //zooming scale
    U16 u16numeratorRotate=1, u16denominatorRotate=1; //rotating scale
    U16 u16ZoomWidth, u16ZoomHeight; //zooming width and height
    U16 u16FitPanelWidth, u16FitPanelHeight; //fitting panel width and height
    U16 u16DstBuffWidth, u16DstBuffHeight;  //destination buffer width and height
    U16 u16PhotoBaseWidth, u16PhotoBaseHeight; //zoom base width and height
    U16 U16PhotoRotatedWidth, U16PhotoRotatedHeight; //photo original resolution

    MVOP_Timing stMVOPTiming;

    memset(&stBitbltInfo, 0, sizeof(GEBitBltInfo));
    memset(&stPitBaseInfo, 0, sizeof(GEPitBaseInfo));
    //1. Photo info

    if(m_bDoAutoRotateMirror)
    {
        if(m_enRotation == EN_PHOTO_ROTATE_0 ||m_enRotation == EN_PHOTO_ROTATE_180)
        {
            u16DstBuffWidth = m_u16PhotoSrcWidth;
            u16DstBuffHeight = m_u16PhotoSrcHeight;
        }
        else
        {
            u16DstBuffWidth = m_u16PhotoSrcHeight;
            u16DstBuffHeight = m_u16PhotoSrcWidth;
        }
    }
    else
    {
        u16DstBuffWidth = PANEL_WIDTH;
        u16DstBuffHeight = PANEL_HEIGHT;
    }

    //2. Photo Rotated
    if(m_bDoAutoRotateMirror)    //pre-rotated display
    {
        switch(m_enRotation)
        {
            case EN_PHOTO_ROTATE_0:
            case EN_PHOTO_ROTATE_180:
                U16PhotoRotatedWidth = m_stPhotoDecodeInfo.u16Width;
                U16PhotoRotatedHeight = m_stPhotoDecodeInfo.u16Height;
                break;
            case EN_PHOTO_ROTATE_90:
            case EN_PHOTO_ROTATE_270:
                U16PhotoRotatedWidth = m_stPhotoDecodeInfo.u16Height;
                U16PhotoRotatedHeight = m_stPhotoDecodeInfo.u16Width;
                break;
            default:
                return FALSE;
        }
    }
    else
    {
        if((m_stPhotoDecodeInfo.enOrientation>=E_PHOTO_ORIENT_ROTATE_90_MIRROR_LR)&&(m_stPhotoDecodeInfo.enOrientation<=E_PHOTO_ORIENT_ROTATE_270))
        {
            switch(m_enRotation)
            {
                case EN_PHOTO_ROTATE_0:
                case EN_PHOTO_ROTATE_180:
                    U16PhotoRotatedWidth = m_stPhotoDecodeInfo.u16Height;
                    U16PhotoRotatedHeight = m_stPhotoDecodeInfo.u16Width;
                    break;
                case EN_PHOTO_ROTATE_90:
                case EN_PHOTO_ROTATE_270:
                    U16PhotoRotatedWidth = m_stPhotoDecodeInfo.u16Width;
                    U16PhotoRotatedHeight = m_stPhotoDecodeInfo.u16Height;
                    break;
                default:
                    return FALSE;
            }
        }
        else
        {
            switch(m_enRotation)
            {
                case EN_PHOTO_ROTATE_0:
                case EN_PHOTO_ROTATE_180:
                    U16PhotoRotatedWidth = m_stPhotoDecodeInfo.u16Width;
                    U16PhotoRotatedHeight = m_stPhotoDecodeInfo.u16Height;
                    break;
                case EN_PHOTO_ROTATE_90:
                case EN_PHOTO_ROTATE_270:
                    U16PhotoRotatedWidth = m_stPhotoDecodeInfo.u16Height;
                    U16PhotoRotatedHeight = m_stPhotoDecodeInfo.u16Width;
                    break;
                default:
                    return FALSE;
            }
        }
    }

    if((U32)u16DstBuffWidth * (U32)U16PhotoRotatedHeight >
       (U32)u16DstBuffHeight * (U32)U16PhotoRotatedWidth)
    {
        //going to this condition means shrink and the original picture is "tall"
        u16FitPanelWidth = (U16)((U32)U16PhotoRotatedWidth * u16DstBuffHeight /
                        U16PhotoRotatedHeight);
        u16FitPanelHeight = u16DstBuffHeight;

        u16denominatorRotate = u16FitPanelHeight; //small map

        if(m_enRotation == EN_PHOTO_ROTATE_90 || m_enRotation == EN_PHOTO_ROTATE_270)
        {
            u16numeratorRotate = m_u16PhotoSrcWidth;
        }
        else
        {
            u16numeratorRotate = m_u16PhotoSrcHeight;
        }

    }
    else
    {
        //going to this condition means shrink and the original picture is "fat"
        u16FitPanelHeight = (U16)((U32)U16PhotoRotatedHeight * (U32)u16DstBuffWidth /
                        U16PhotoRotatedWidth);
        u16FitPanelWidth = (U16)u16DstBuffWidth;

        u16denominatorRotate = u16FitPanelWidth; //small map

        if(m_enRotation == EN_PHOTO_ROTATE_90 || m_enRotation == EN_PHOTO_ROTATE_270)
        {
            u16numeratorRotate = m_u16PhotoSrcHeight;
        }
        else
        {
            u16numeratorRotate = m_u16PhotoSrcWidth;
        }
    }

    //3. Photo base
#if PHOTO_ZOOM_BY_ORIGINAL
//original
    if(MApp_Photo_GetInfo(E_PHOTO_INFO_SCALE_DOWN_FACTOR) > 1)
    {
        //If photo shrink and width/height is smaller than panel
        U16PhotoRotatedWidth = U16PhotoRotatedWidth * MApp_Photo_GetInfo(E_PHOTO_INFO_SCALE_DOWN_FACTOR);
        U16PhotoRotatedHeight = U16PhotoRotatedHeight * MApp_Photo_GetInfo(E_PHOTO_INFO_SCALE_DOWN_FACTOR);
    }
    if((U16PhotoRotatedWidth<u16DstBuffWidth)&&(U16PhotoRotatedHeight<u16DstBuffHeight))
    {
        u16PhotoBaseWidth = U16PhotoRotatedWidth;
        u16PhotoBaseHeight = U16PhotoRotatedHeight;
    }
    else
    { //if Width or Height >= Panel size
        u16PhotoBaseWidth = u16FitPanelWidth;   //Picture Width in internal buffer
        u16PhotoBaseHeight = u16FitPanelHeight; //Picture Height in internal buffer
    }
#else
//fill
    u16PhotoBaseWidth  = u16FitPanelWidth;
    u16PhotoBaseHeight = u16FitPanelHeight;
#endif

#if ENABLE_ZOOM_MAP
    //give fit panel size
    m_u16ZoomImageWidth =u16FitPanelWidth;
    m_u16ZoomImageHeight=u16FitPanelHeight;
#endif

    //4. Zoom scale
    switch(m_enZooming)
    {
    case EN_PHOTO_ZOOM_1_8:
        u16numerator = 10;
        u16denominator = 28;
        break;
    case EN_PHOTO_ZOOM_1_4:
        u16numerator = 1;
        u16denominator = 2;
        break;
    case EN_PHOTO_ZOOM_1_2:
        u16numerator = 10;
        u16denominator = 14;
        break;
    case EN_PHOTO_ZOOM_1:
        u16numerator = 1;
        u16denominator = 1;
        break;
    case EN_PHOTO_ZOOM_2:
        u16numerator = 14;
        u16denominator = 10;
        break;
    case EN_PHOTO_ZOOM_4:
        u16numerator = 2;
        u16denominator = 1;
        break;
    case EN_PHOTO_ZOOM_8:
        u16numerator = 28;
        u16denominator = 10;
        break;
    default:
        return FALSE;
    }

    u16ZoomWidth = u16PhotoBaseWidth*u16numerator/u16denominator;
    u16ZoomHeight = u16PhotoBaseHeight*u16numerator/u16denominator;

    //yuyv should set even number to avoid a pixel wrong
    u16ZoomWidth = u16ZoomWidth & (~0x1);

    //5. Destination width and height
    u16DstW = u16ZoomWidth;
    u16DstH = u16ZoomHeight;

    if(u16DstW > u16DstBuffWidth)
    {
        u16DstW = u16DstBuffWidth;
    }
    if(u16DstH > u16DstBuffHeight)
    {
        u16DstH = u16DstBuffHeight;
    }

    //6. Calculate capture width & height.
    if(m_enRotation == EN_PHOTO_ROTATE_90 || m_enRotation == EN_PHOTO_ROTATE_270)
    {
        u16CapW = m_u16PhotoSrcWidth * u16DstH / u16ZoomHeight;
        u16CapH = m_u16PhotoSrcHeight * u16DstW / u16ZoomWidth;
    }
    else
    {
        u16CapW = m_u16PhotoSrcWidth * u16DstW / u16ZoomWidth;
        u16CapH = m_u16PhotoSrcHeight * u16DstH / u16ZoomHeight;
    }

    // Calculate the deatination X & Y.
    u16DstX = (u16DstBuffWidth - u16DstW) / 2;
    u16DstY = (u16DstBuffHeight - u16DstH) / 2;

    //yuyv should set even number to avoid a pixel wrong
    u16DstX = u16DstX & (~0x1);

    // Calculate the capture X & Y.
    s16CapX = (S16)(u16DstBuffWidth - u16CapW) / 2 + m_s16PhotoOffsetX;
    s16CapY = (S16)(u16DstBuffHeight - u16CapH) / 2 + m_s16PhotoOffsetY;

#if ENABLE_ZOOM_MAP
    m_u16ZoomCaptureWidth=(U32)m_u16ZoomImageWidth*(U32)u16DstW/(U32)u16ZoomWidth;
    m_u16ZoomCaptureHeight=(U32)m_u16ZoomImageHeight*(U32)u16DstH/(U32)u16ZoomHeight;

    m_u16ZoomDenominatorRotate = u16denominatorRotate;
    m_u16ZoomNumeratorRotate = u16numeratorRotate;
#endif

#if 0
    printf("== Cap: %d %d %d %d, Photo: %d %d %d %d\n",
           s16CapX, s16CapY, u16CapW, u16CapH,
           m_u16PhotoSrcX, m_u16PhotoSrcY, m_u16PhotoSrcWidth, m_u16PhotoSrcHeight);
#endif

    // do parameters adjustment if boundary hits.
    if (s16CapX < (S16)m_u16PhotoSrcX) // right
    {
        m_s16PhotoOffsetX += (S16)m_u16PhotoSrcX - s16CapX;
        s16CapX = m_u16PhotoSrcX;
    }

    if ((s16CapX + (S16)u16CapW) > (S16)(m_u16PhotoSrcX + m_u16PhotoSrcWidth)) // left
    {
        m_s16PhotoOffsetX -= ((s16CapX + (S16)u16CapW) - (S16)(m_u16PhotoSrcX + m_u16PhotoSrcWidth));
        s16CapX = (S16)(m_u16PhotoSrcX + m_u16PhotoSrcWidth) - (S16)u16CapW;
    }

    if (s16CapY < (S16)m_u16PhotoSrcY) // top
    {
        m_s16PhotoOffsetY += (S16)m_u16PhotoSrcY - s16CapY;
        s16CapY = m_u16PhotoSrcY;
    }

    if ((s16CapY + (S16)u16CapH) > (S16)(m_u16PhotoSrcY + m_u16PhotoSrcHeight)) // bottom
    {
        m_s16PhotoOffsetY -= ((s16CapY + (S16)u16CapH) - (S16)(m_u16PhotoSrcY + m_u16PhotoSrcHeight));
        s16CapY = (S16)(m_u16PhotoSrcY + m_u16PhotoSrcHeight) - (S16)u16CapH;
    }

    if((s16CapX >= (S16)m_u16PhotoSrcX) &&
       ((s16CapX + (S16)u16CapW) <= (S16)(m_u16PhotoSrcX + m_u16PhotoSrcWidth)) &&
       (s16CapY >= (S16)m_u16PhotoSrcY) &&
       ((s16CapY + (S16)u16CapH) <= (S16)(m_u16PhotoSrcY + m_u16PhotoSrcHeight)))
    {
        U16 u16SrcPitch, u16DstPitch;
        U32 u32SrcBase, u32DstBase;
        BOOLEAN bShrink2Half=FALSE;

        if(m_bDoAutoRotateMirror)
        {
            u16SrcPitch = MApp_Photo_GetInfo(E_PHOTO_INFO_PITCH);
            u32SrcBase = PHOTO_OUTPUT_BUFFER_ADDR;
            u16DstPitch = u16FitPanelWidth;
            u32DstBase = PHOTO_DISPLAY_SRC_BUFFER_ADDR;
        }
        else
        {
            u16SrcPitch = PHOTO_ADJUSTED_PANEL_WIDTH;
            u32SrcBase = PHOTO_DISPLAY_SRC_BUFFER_ADDR;
            u16DstPitch = PHOTO_ADJUSTED_PANEL_WIDTH;
            u32DstBase = PHOTO_DISPLAY_BUFFER_ADDR;
        }

        if (MApi_XC_IsCurrentFrameBufferLessMode())
        {
            msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_MM, ENABLE, 0, MAIN_WINDOW);
        }
        else
        {
            MApi_XC_FreezeImg(TRUE, MAIN_WINDOW);
        }


        MDrv_MVOP_GetOutputTiming(&stMVOPTiming);
        MApi_XC_WaitInputVSync(1, (1000/stMVOPTiming.u8Framerate)*1, MAIN_WINDOW);

        // 1. Clear internal buffer to black.
        msAPI_GE_ClearFrameBufferByWord((U32)u32DstBase,
                                       PHOTO_DISPLAY_BUFFER_SIZE,
                                       0x80008000);
        // after clear frame buffer, flush cmd
        MApi_GFX_FlushQueue();

        //printf("\n PHOTO_DISPLAY_BUFFER_ADDR=%x , PHOTO_DISPLAY_BUFFER_SIZE=%x ",PHOTO_DISPLAY_BUFFER_ADDR,PHOTO_DISPLAY_BUFFER_SIZE );
        // 2. If the destination is too small, shrink to half.
        stBitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;
        stBitbltInfo.BmpFlag = GFXDRAW_FLAG_DEFAULT;
        stBitbltInfo.dst_fm = GFX_FMT_YUV422;
        stBitbltInfo.src_fm = GFX_FMT_YUV422;
        stBitbltInfo.BitbltCoordinate.direction = 0; // TODO: what's this?

        msAPI_GE_SetNearestMode(FALSE);
        msAPI_GE_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_PC, GFX_YUV_OUT_255, GFX_YUV_IN_255, GFX_YUV_YUYV, GFX_YUV_YUYV);

        if(m_enZooming <= EN_PHOTO_ZOOM_1_2)
        {
            if(m_enRotation == EN_PHOTO_ROTATE_0 || m_enRotation == EN_PHOTO_ROTATE_180)
            {
                if((u16DstW*2) <= u16CapW)
                {
                    bShrink2Half = TRUE;
                }
                else if((u16DstH*2) <= u16CapH)
                {
                    bShrink2Half = TRUE;
                }
            }
            else
            {
                if((u16DstW*2) <= u16CapH)
                {
                    bShrink2Half = TRUE;
                }
                else if((u16DstH*2) <= u16CapW)
                {
                    bShrink2Half = TRUE;
                }
            }
        }

        //printf("\n PHOTO_SHRINK_BUFFER_0_ADDR=%x , PHOTO_SHRINK_BUFFER_0_SIZE=%x ",PHOTO_SHRINK_BUFFER_0_ADDR,PHOTO_SHRINK_BUFFER_0_SIZE );
        //printf("\n PHOTO_DISPLAY_SRC_BUFFER_ADDR=%x , PHOTO_DISPLAY_BUFFER_ADDR=%x ",PHOTO_DISPLAY_SRC_BUFFER_ADDR,PHOTO_DISPLAY_BUFFER_ADDR );

        if(bShrink2Half)
        {
            msAPI_GE_ClearFrameBufferByWord((U32)PHOTO_SHRINK_BUFFER_0_ADDR,
                                           PHOTO_SHRINK_BUFFER_0_SIZE,
                                           0x80008000);
            // after clear frame buffer, flush cmd
            MApi_GFX_FlushQueue();

            stPitBaseInfo.sb_pit = u16SrcPitch * 2;
            stPitBaseInfo.sb_base = u32SrcBase;       // the address is referring to original image

            stPitBaseInfo.db_pit = PHOTO_SHRINK_BUFFER_0_WIDTH * 2;  // 2 bytes per pixel
            stPitBaseInfo.db_base = PHOTO_SHRINK_BUFFER_0_ADDR;

            stBitbltInfo.BitbltCoordinate.v2_x = m_u16PhotoSrcX;
            stBitbltInfo.BitbltCoordinate.v2_y = m_u16PhotoSrcY;
            stBitbltInfo.src_width = m_u16PhotoSrcWidth;
            stBitbltInfo.src_height = m_u16PhotoSrcHeight;

            stBitbltInfo.BitbltCoordinate.v0_x = 0;
            stBitbltInfo.BitbltCoordinate.v0_y = 0;
            stBitbltInfo.BitbltCoordinate.width = m_u16PhotoSrcWidth / 2 + 2;
            stBitbltInfo.BitbltCoordinate.height = m_u16PhotoSrcHeight / 2 + 2;

            msAPI_GE_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_PC, GFX_YUV_OUT_255, GFX_YUV_IN_255, GFX_YUV_YUYV, GFX_YUV_YUYV);
            msAPI_GE_SetPatchMode(TRUE);
            msAPI_GE_BitBlt(&stBitbltInfo, &stPitBaseInfo);

            // after BitBlt, flush cmd
            MApi_GFX_FlushQueue();
            msAPI_GE_SetPatchMode(FALSE);

            PHOTO_DISP_MSG(printf("\n bShrink2Half \n"));
            PHOTO_DISP_MSG(printf("stBitbltInfo: \n"));
            PHOTO_DISP_MSG(printf("\ttype flag: %u\n", stBitbltInfo.BitBltTypeFlag));
            PHOTO_DISP_MSG(printf("\tbmp flag: %u\n", stBitbltInfo.BmpFlag));
            PHOTO_DISP_MSG(printf("\tdest fmt: %u\n", stBitbltInfo.dst_fm));
            PHOTO_DISP_MSG(printf("\tsrc fmt: %u\n", stBitbltInfo.src_fm));
            PHOTO_DISP_MSG(printf("\tbmp hnd: %d\n", stBitbltInfo.bmphandle));
            PHOTO_DISP_MSG(printf("\tsrc width: %u\n", stBitbltInfo.src_width));
            PHOTO_DISP_MSG(printf("\tsrc height: %u\n", stBitbltInfo.src_height));
            PHOTO_DISP_MSG(printf("\tcoord v0x: %u\n", stBitbltInfo.BitbltCoordinate.v0_x));
            PHOTO_DISP_MSG(printf("\tcoord v0y: %u\n", stBitbltInfo.BitbltCoordinate.v0_y));
            PHOTO_DISP_MSG(printf("\tcoord width: %u\n", stBitbltInfo.BitbltCoordinate.width));
            PHOTO_DISP_MSG(printf("\tcoord height: %u\n", stBitbltInfo.BitbltCoordinate.height));
            PHOTO_DISP_MSG(printf("\tcoord v2x: %u\n", stBitbltInfo.BitbltCoordinate.v2_x));
            PHOTO_DISP_MSG(printf("\tcoord v2y: %u\n", stBitbltInfo.BitbltCoordinate.v2_y));
            PHOTO_DISP_MSG(printf("\tcoord direct: %u\n", stBitbltInfo.BitbltCoordinate.direction));
            PHOTO_DISP_MSG(printf("stPitBaseInfo: \n"));
            PHOTO_DISP_MSG(printf("\tsrc pitch: %x\n",stPitBaseInfo.sb_pit));
            PHOTO_DISP_MSG(printf("\tdst pitch: %x\n",stPitBaseInfo.db_pit));
            PHOTO_DISP_MSG(printf("\tsrc base: %x\n",stPitBaseInfo.sb_base));
            PHOTO_DISP_MSG(printf("\tdst base: %x\n",stPitBaseInfo.db_base));

            s16CapX = 0;
            s16CapY = 0;
            u16CapW = stBitbltInfo.BitbltCoordinate.width;
            u16CapH = stBitbltInfo.BitbltCoordinate.height;

            u16SrcPitch = PHOTO_SHRINK_BUFFER_0_WIDTH;
            u32SrcBase = PHOTO_SHRINK_BUFFER_0_ADDR;
        }

        // 3. Stretch source to internal buffer.
        // BitBlt information settings
        stPitBaseInfo.sb_pit = u16SrcPitch * 2;
        stPitBaseInfo.sb_base = u32SrcBase;              // the address is referring to original image

        stPitBaseInfo.db_pit = u16DstPitch*2;  // 2 bytes per pixel
        stPitBaseInfo.db_base = u32DstBase;

        stBitbltInfo.src_width = u16CapW;
        stBitbltInfo.src_height = u16CapH;

        stBitbltInfo.BitbltCoordinate.v0_x = u16DstX;
        stBitbltInfo.BitbltCoordinate.v0_y = u16DstY;

        m_u16PhotoDstX = stBitbltInfo.BitbltCoordinate.v0_x;
        m_u16PhotoDstY = stBitbltInfo.BitbltCoordinate.v0_y;
        if(m_enRotation == EN_PHOTO_ROTATE_0 || m_enRotation == EN_PHOTO_ROTATE_180)
        {
            stBitbltInfo.BitbltCoordinate.width = u16DstW;
            stBitbltInfo.BitbltCoordinate.height = u16DstH;

            m_u16PhotoDstWidth = stBitbltInfo.BitbltCoordinate.width;
            m_u16PhotoDstHeight = stBitbltInfo.BitbltCoordinate.height;
        }
        else
        {
            stBitbltInfo.BitbltCoordinate.width = u16DstH;
            stBitbltInfo.BitbltCoordinate.height = u16DstW;

            m_u16PhotoDstWidth = stBitbltInfo.BitbltCoordinate.height;
            m_u16PhotoDstHeight = stBitbltInfo.BitbltCoordinate.width;
        }

#if 0
        printf("-- Src: %d %d %d %d, Dst: %d %d %d %d\n",
                stBitbltInfo.BitbltCoordinate.v2_x,
                stBitbltInfo.BitbltCoordinate.v2_y,
                stBitbltInfo.src_width,
                stBitbltInfo.src_height,
                stBitbltInfo.BitbltCoordinate.v0_x,
                stBitbltInfo.BitbltCoordinate.v0_y,
                stBitbltInfo.BitbltCoordinate.width,
                stBitbltInfo.BitbltCoordinate.height
                );
#endif

        //do mirror and rotation
        if(m_bMirrorX)
        {
            stBitbltInfo.BitbltCoordinate.v2_x = (U16)s16CapX + stBitbltInfo.src_width - 1;
        }
        else
        {
            stBitbltInfo.BitbltCoordinate.v2_x = (U16)s16CapX;
        }

        if(m_bMirrorY)
        {
            stBitbltInfo.BitbltCoordinate.v2_y = (U16)s16CapY + stBitbltInfo.src_height - 1;
        }
        else
        {
            stBitbltInfo.BitbltCoordinate.v2_y = (U16)s16CapY;
        }

        if(m_bMirrorX || m_bMirrorY)
            msAPI_GE_SetMirror(m_bMirrorX, m_bMirrorY);

        switch (m_enRotation)
        {
        case EN_PHOTO_ROTATE_90:
            {
                msAPI_GE_SetRotate(GEROTATE_90);
            }
            break;
        case EN_PHOTO_ROTATE_180:
            {
                msAPI_GE_SetRotate(GEROTATE_180);
            }
            break;
        case EN_PHOTO_ROTATE_270:
            {
                msAPI_GE_SetRotate(GEROTATE_270);
            }
            break;
        case EN_PHOTO_ROTATE_0:
            {
                msAPI_GE_SetRotate(GEROTATE_0);
            }
            break;
        default:
            break;
        }

        //Before GE bitblt, after clear framebuffer, set clipwindow here.
        msAPI_OSD_SetClipWindow(0, 0, u16DstBuffWidth, u16DstBuffHeight);

        msAPI_GE_SetNearestMode(FALSE);
        msAPI_GE_SetPatchMode(TRUE);
        // output image to destination buffer
        msAPI_GE_BitBlt(&stBitbltInfo, &stPitBaseInfo);
        // after BitBlt, flush cmd
        MApi_GFX_FlushQueue();
        msAPI_GE_SetPatchMode(FALSE);

        PHOTO_DISP_MSG(printf("\n ZOOM / ROTATE \n"));
        PHOTO_DISP_MSG(printf("stBitbltInfo: \n"));
        PHOTO_DISP_MSG(printf("\ttype flag: %u\n", stBitbltInfo.BitBltTypeFlag));
        PHOTO_DISP_MSG(printf("\tbmp flag: %u\n", stBitbltInfo.BmpFlag));
        PHOTO_DISP_MSG(printf("\tdest fmt: %u\n", stBitbltInfo.dst_fm));
        PHOTO_DISP_MSG(printf("\tsrc fmt: %u\n", stBitbltInfo.src_fm));
        PHOTO_DISP_MSG(printf("\tbmp hnd: %d\n", stBitbltInfo.bmphandle));
        PHOTO_DISP_MSG(printf("\tsrc width: %u\n", stBitbltInfo.src_width));
        PHOTO_DISP_MSG(printf("\tsrc height: %u\n", stBitbltInfo.src_height));
        PHOTO_DISP_MSG(printf("\tcoord v0x: %u\n", stBitbltInfo.BitbltCoordinate.v0_x));
        PHOTO_DISP_MSG(printf("\tcoord v0y: %u\n", stBitbltInfo.BitbltCoordinate.v0_y));
        PHOTO_DISP_MSG(printf("\tcoord width: %u\n", stBitbltInfo.BitbltCoordinate.width));
        PHOTO_DISP_MSG(printf("\tcoord height: %u\n", stBitbltInfo.BitbltCoordinate.height));
        PHOTO_DISP_MSG(printf("\tcoord v2x: %u\n", stBitbltInfo.BitbltCoordinate.v2_x));
        PHOTO_DISP_MSG(printf("\tcoord v2y: %u\n", stBitbltInfo.BitbltCoordinate.v2_y));
        PHOTO_DISP_MSG(printf("\tcoord direct: %u\n", stBitbltInfo.BitbltCoordinate.direction));
        PHOTO_DISP_MSG(printf("stPitBaseInfo: \n"));
        PHOTO_DISP_MSG(printf("\tsrc pitch: %x\n",stPitBaseInfo.sb_pit));
        PHOTO_DISP_MSG(printf("\tdst pitch: %x\n",stPitBaseInfo.db_pit));
        PHOTO_DISP_MSG(printf("\tsrc base: %x\n",stPitBaseInfo.sb_base));
        PHOTO_DISP_MSG(printf("\tdst base: %x\n",stPitBaseInfo.db_base));
        // NOTE: it's critical to reset GE registers after rotation

        msAPI_GE_SetMirror(0, 0);
        msAPI_GE_SetRotate(GEROTATE_0);

        MDrv_MVOP_GetOutputTiming(&stMVOPTiming);
        MApi_XC_WaitOutputVSync(2, (1000/stMVOPTiming.u8Framerate)*2, MAIN_WINDOW);

        if (MApi_XC_IsCurrentFrameBufferLessMode())
        {
            msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_MM, DISABLE, 0, MAIN_WINDOW);
        }
        else
        {
            MApi_XC_FreezeImg(FALSE, MAIN_WINDOW);
        }
        msAPI_Timer_Delayms(150);

        msAPI_GE_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_PC, GFX_YUV_OUT_255, GFX_YUV_IN_255, GFX_YUV_YUYV, GFX_YUV_YUYV);
    }
    else
    {
        return FALSE;
    }

    return TRUE;
}

void MApp_Photo_SetSlideShowEffect(EN_PHOTO_SLIDE_SHOW_EFFECT eSlideShowEffect)
{
    m_SlideShowEffect = eSlideShowEffect;
}

EN_PHOTO_SLIDE_SHOW_EFFECT MApp_Photo_GetSlideShowEffect(void)
{
    return m_SlideShowEffect;
}

static void _MApp_Photo_SlideShow_Normal(void)
{
    GEBitBltInfo stBitbltInfo;
    GEPitBaseInfo stPitBaseInfo;

    stPitBaseInfo.sb_pit = PHOTO_ADJUSTED_PANEL_WIDTH * 2;
    stPitBaseInfo.sb_base = PHOTO_DISPLAY_SRC_BUFFER_ADDR;      // the address is referring to original image

    stPitBaseInfo.db_pit = PHOTO_ADJUSTED_PANEL_WIDTH * 2;         // 2 bytes per pixel
    stPitBaseInfo.db_base = PHOTO_DISPLAY_BUFFER_ADDR;

    stBitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;
    stBitbltInfo.BmpFlag = GFXDRAW_FLAG_DEFAULT;
    stBitbltInfo.dst_fm = GFX_FMT_YUV422;
    stBitbltInfo.src_fm = GFX_FMT_YUV422;

    stBitbltInfo.src_width = PHOTO_ADJUSTED_PANEL_WIDTH;
    stBitbltInfo.src_height = PANEL_HEIGHT;

    stBitbltInfo.BitbltCoordinate.v2_x = 0;
    stBitbltInfo.BitbltCoordinate.v2_y = 0;

    stBitbltInfo.BitbltCoordinate.direction = 0;    // TODO: what's this?

    stBitbltInfo.BitbltCoordinate.v0_x = 0;
    stBitbltInfo.BitbltCoordinate.v0_y = 0;
    stBitbltInfo.BitbltCoordinate.width = PHOTO_ADJUSTED_PANEL_WIDTH;
    stBitbltInfo.BitbltCoordinate.height = PANEL_HEIGHT;
    msAPI_OSD_SetClipWindow(0, 0, PHOTO_ADJUSTED_PANEL_WIDTH, PANEL_HEIGHT);
    msAPI_GE_SetNearestMode(TRUE);
    msAPI_GE_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_PC, GFX_YUV_OUT_255, GFX_YUV_IN_255, GFX_YUV_YUYV, GFX_YUV_YUYV);

    // output image to destination buffer
    MApi_XC_FreezeImg(TRUE, MAIN_WINDOW);
#if (SUPPORT_MM_PHOTO_4K)
    MVOP_Timing stMVOPTiming;
    MDrv_MVOP_GetOutputTiming(&stMVOPTiming);
    MApi_XC_WaitInputVSync(1, (1000/stMVOPTiming.u8Framerate)*1, MAIN_WINDOW);
#endif
    msAPI_GE_BitBlt(&stBitbltInfo, &stPitBaseInfo);
    // after BitBlt, flush cmd
    MApi_GFX_FlushQueue();

#if (SUPPORT_MM_PHOTO_4K)//defined(SCALER_DNR_4K_PHOTO_BUF_LEN) && (SCALER_DNR_4K_PHOTO_BUF_LEN!=0)
    //for 4K2K photo, need to wait 4 Vsync, avoid screen abnormal
    MApi_XC_WaitOutputVSync(4, (1000/stMVOPTiming.u8Framerate)*4, MAIN_WINDOW);
#endif

    MApi_XC_FreezeImg(FALSE, MAIN_WINDOW);
}

#if (ENABLE_PHOTO_TRANS_EFFECT_BLOCKS)
#define PHOTO_TRANS_EFFECT_BLOCK_UNIT_DELAY_MS  (PHOTO_TRANS_EFFECT_DELAY_MS/(PHOTO_TRANS_EFFECT_BLOCK_HORZ_NUM*PHOTO_TRANS_EFFECT_BLOCK_VERT_NUM))
#define PHOTO_TRANS_EFFECT_BLOCK_WIDTH          ((((PHOTO_ADJUSTED_PANEL_WIDTH+PHOTO_TRANS_EFFECT_BLOCK_HORZ_NUM-1)/PHOTO_TRANS_EFFECT_BLOCK_HORZ_NUM)+1)&0x7FFE)
#define PHOTO_TRANS_EFFECT_BLOCK_HEIGHT         ((((PANEL_HEIGHT+PHOTO_TRANS_EFFECT_BLOCK_VERT_NUM-1)/PHOTO_TRANS_EFFECT_BLOCK_VERT_NUM)+1)&0x7FFE)
static void _MApp_Photo_SlideShow_Blocks(EN_PHOTO_SLIDE_SHOW_EFFECT eSlideShowEffect)
{
    GEBitBltInfo stBitbltInfo;
    GEPitBaseInfo stPitBaseInfo;
    S16 s16outerIdx, s16innerIdx;
    S16 s16outerEnd, s16innerEnd;
    S16 s16innerIncX, s16outerIncX, s16innerIncY, s16outerIncY;
    S16 s16MovePosX, s16MovePosY;
    U16 u16PosX, u16PosY;
    S16 s16innerIncChangeX, s16innerIncChangeY;
    U32 u32Delayms;
    U32 u32StartTimeMs, u32ElapseTime;

    stPitBaseInfo.sb_pit = PHOTO_ADJUSTED_PANEL_WIDTH * 2;
    stPitBaseInfo.sb_base = PHOTO_DISPLAY_SRC_BUFFER_ADDR;          // the address is referring to original image

    stPitBaseInfo.db_pit = PHOTO_ADJUSTED_PANEL_WIDTH * 2;    // 2 bytes per pixel
    stPitBaseInfo.db_base = PHOTO_DISPLAY_BUFFER_ADDR;

    stBitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;
    stBitbltInfo.BmpFlag = GFXDRAW_FLAG_DEFAULT;
    stBitbltInfo.dst_fm = GFX_FMT_YUV422;
    stBitbltInfo.src_fm = GFX_FMT_YUV422;
    msAPI_OSD_SetClipWindow(0, 0, PHOTO_ADJUSTED_PANEL_WIDTH, PANEL_HEIGHT);
    stBitbltInfo.BitbltCoordinate.direction = 0;    // TODO: what's this?
    msAPI_GE_SetNearestMode(TRUE);
    msAPI_GE_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_PC, GFX_YUV_OUT_255, GFX_YUV_IN_255, GFX_YUV_YUYV, GFX_YUV_YUYV);

    s16innerIncChangeX = 1;
    s16innerIncChangeY = 1;
    switch(eSlideShowEffect)
    {
    case E_SLIDE_SHOW_EFFECT_HORZ_BLOCKS_TOPLEFT:
    case E_SLIDE_SHOW_EFFECT_HORZ_ZIGZAG_BLOCKS_TOPLEFT:
        s16MovePosX = 0;
        s16MovePosY = 0;
        s16innerIncX = PHOTO_TRANS_EFFECT_BLOCK_WIDTH;
        s16innerIncY = 0;
        s16outerIncX = -PHOTO_TRANS_EFFECT_BLOCK_WIDTH*(PHOTO_TRANS_EFFECT_BLOCK_HORZ_NUM-1);
        s16outerIncY = PHOTO_TRANS_EFFECT_BLOCK_HEIGHT;
        s16innerEnd = PHOTO_TRANS_EFFECT_BLOCK_HORZ_NUM;
        s16outerEnd = PHOTO_TRANS_EFFECT_BLOCK_VERT_NUM;
        break;
    case E_SLIDE_SHOW_EFFECT_HORZ_BLOCKS_TOPRIGHT:
    case E_SLIDE_SHOW_EFFECT_HORZ_ZIGZAG_BLOCKS_TOPRIGHT:
        s16MovePosX = PHOTO_ADJUSTED_PANEL_WIDTH - PHOTO_TRANS_EFFECT_BLOCK_WIDTH;
        s16MovePosY = 0;
        s16innerIncX = -PHOTO_TRANS_EFFECT_BLOCK_WIDTH;
        s16innerIncY = 0;
        s16outerIncX = PHOTO_TRANS_EFFECT_BLOCK_WIDTH*(PHOTO_TRANS_EFFECT_BLOCK_HORZ_NUM-1);
        s16outerIncY = PHOTO_TRANS_EFFECT_BLOCK_HEIGHT;
        s16innerEnd = PHOTO_TRANS_EFFECT_BLOCK_HORZ_NUM;
        s16outerEnd = PHOTO_TRANS_EFFECT_BLOCK_VERT_NUM;
        break;
    case E_SLIDE_SHOW_EFFECT_HORZ_BLOCKS_BOTTOMLEFT:
    case E_SLIDE_SHOW_EFFECT_HORZ_ZIGZAG_BLOCKS_BOTTOMLEFT:
        s16MovePosX = 0;
        s16MovePosY = PANEL_HEIGHT - PHOTO_TRANS_EFFECT_BLOCK_HEIGHT;
        s16innerIncX = PHOTO_TRANS_EFFECT_BLOCK_WIDTH;
        s16innerIncY = 0;
        s16outerIncX = -PHOTO_TRANS_EFFECT_BLOCK_WIDTH*(PHOTO_TRANS_EFFECT_BLOCK_HORZ_NUM-1);
        s16outerIncY = -PHOTO_TRANS_EFFECT_BLOCK_HEIGHT;
        s16innerEnd = PHOTO_TRANS_EFFECT_BLOCK_HORZ_NUM;
        s16outerEnd = PHOTO_TRANS_EFFECT_BLOCK_VERT_NUM;
        break;
    case E_SLIDE_SHOW_EFFECT_HORZ_BLOCKS_BOTTOMRIGHT:
    case E_SLIDE_SHOW_EFFECT_HORZ_ZIGZAG_BLOCKS_BOTTOMRIGHT:
        s16MovePosX = PHOTO_ADJUSTED_PANEL_WIDTH - PHOTO_TRANS_EFFECT_BLOCK_WIDTH;
        s16MovePosY = PANEL_HEIGHT - PHOTO_TRANS_EFFECT_BLOCK_HEIGHT;
        s16innerIncX = -PHOTO_TRANS_EFFECT_BLOCK_WIDTH;
        s16innerIncY = 0;
        s16outerIncX = +PHOTO_TRANS_EFFECT_BLOCK_WIDTH*(PHOTO_TRANS_EFFECT_BLOCK_HORZ_NUM-1);
        s16outerIncY = -PHOTO_TRANS_EFFECT_BLOCK_HEIGHT;
        s16innerEnd = PHOTO_TRANS_EFFECT_BLOCK_HORZ_NUM;
        s16outerEnd = PHOTO_TRANS_EFFECT_BLOCK_VERT_NUM;
        break;
    case E_SLIDE_SHOW_EFFECT_VERT_BLOCKS_TOPLEFT:
    case E_SLIDE_SHOW_EFFECT_VERT_ZIGZAG_BLOCKS_TOPLEFT:
        s16MovePosX = 0;
        s16MovePosY = 0;
        s16innerIncX = 0;
        s16innerIncY = PHOTO_TRANS_EFFECT_BLOCK_HEIGHT;
        s16outerIncX = PHOTO_TRANS_EFFECT_BLOCK_WIDTH;
        s16outerIncY = -PHOTO_TRANS_EFFECT_BLOCK_HEIGHT*(PHOTO_TRANS_EFFECT_BLOCK_VERT_NUM-1);
        s16innerEnd = PHOTO_TRANS_EFFECT_BLOCK_VERT_NUM;
        s16outerEnd = PHOTO_TRANS_EFFECT_BLOCK_HORZ_NUM;
        break;
    case E_SLIDE_SHOW_EFFECT_VERT_BLOCKS_TOPRIGHT:
    case E_SLIDE_SHOW_EFFECT_VERT_ZIGZAG_BLOCKS_TOPRIGHT:
        s16MovePosX = PHOTO_ADJUSTED_PANEL_WIDTH - PHOTO_TRANS_EFFECT_BLOCK_WIDTH;
        s16MovePosY = 0;
        s16innerIncX = 0;
        s16innerIncY = PHOTO_TRANS_EFFECT_BLOCK_HEIGHT;
        s16outerIncX = -PHOTO_TRANS_EFFECT_BLOCK_WIDTH;
        s16outerIncY = -PHOTO_TRANS_EFFECT_BLOCK_HEIGHT*(PHOTO_TRANS_EFFECT_BLOCK_VERT_NUM-1);
        s16innerEnd = PHOTO_TRANS_EFFECT_BLOCK_VERT_NUM;
        s16outerEnd = PHOTO_TRANS_EFFECT_BLOCK_HORZ_NUM;
        break;
    case E_SLIDE_SHOW_EFFECT_VERT_BLOCKS_BOTTOMLEFT:
    case E_SLIDE_SHOW_EFFECT_VERT_ZIGZAG_BLOCKS_BOTTOMLEFT:
        s16MovePosX = 0;
        s16MovePosY = PANEL_HEIGHT - PHOTO_TRANS_EFFECT_BLOCK_HEIGHT;
        s16innerIncX = 0;
        s16innerIncY = -PHOTO_TRANS_EFFECT_BLOCK_HEIGHT;
        s16outerIncX = PHOTO_TRANS_EFFECT_BLOCK_WIDTH;
        s16outerIncY = PHOTO_TRANS_EFFECT_BLOCK_HEIGHT*(PHOTO_TRANS_EFFECT_BLOCK_VERT_NUM-1);
        s16innerEnd = PHOTO_TRANS_EFFECT_BLOCK_VERT_NUM;
        s16outerEnd = PHOTO_TRANS_EFFECT_BLOCK_HORZ_NUM;
        break;
    case E_SLIDE_SHOW_EFFECT_VERT_BLOCKS_BOTTOMRIGHT:
    case E_SLIDE_SHOW_EFFECT_VERT_ZIGZAG_BLOCKS_BOTTOMRIGHT:
        s16MovePosX = PHOTO_ADJUSTED_PANEL_WIDTH - PHOTO_TRANS_EFFECT_BLOCK_WIDTH;
        s16MovePosY = PANEL_HEIGHT - PHOTO_TRANS_EFFECT_BLOCK_HEIGHT;
        s16innerIncX = 0;
        s16innerIncY = -PHOTO_TRANS_EFFECT_BLOCK_HEIGHT;
        s16outerIncX = -PHOTO_TRANS_EFFECT_BLOCK_WIDTH;
        s16outerIncY = PHOTO_TRANS_EFFECT_BLOCK_HEIGHT*(PHOTO_TRANS_EFFECT_BLOCK_VERT_NUM-1);
        s16innerEnd = PHOTO_TRANS_EFFECT_BLOCK_VERT_NUM;
        s16outerEnd = PHOTO_TRANS_EFFECT_BLOCK_HORZ_NUM;
        break;
    default:
        return;
    }

    if(eSlideShowEffect >= E_SLIDE_SHOW_EFFECT_HORZ_ZIGZAG_BLOCKS_TOPLEFT &&
       eSlideShowEffect <= E_SLIDE_SHOW_EFFECT_HORZ_ZIGZAG_BLOCKS_BOTTOMRIGHT)
    {
        s16outerIncX = 0;
        s16innerIncChangeX = -1;
    }
    else if(eSlideShowEffect >= E_SLIDE_SHOW_EFFECT_VERT_ZIGZAG_BLOCKS_TOPLEFT &&
            eSlideShowEffect <= E_SLIDE_SHOW_EFFECT_VERT_ZIGZAG_BLOCKS_BOTTOMRIGHT)
    {
        s16outerIncY = 0;
        s16innerIncChangeY = -1;
    }

    u32Delayms = PHOTO_TRANS_EFFECT_BLOCK_UNIT_DELAY_MS;

    u16PosX = s16MovePosX;
    u16PosY = s16MovePosY;
    for(s16outerIdx=0;s16outerIdx<s16outerEnd;s16outerIdx++)
    {
        for(s16innerIdx=0;s16innerIdx<s16innerEnd;s16innerIdx++)
        {
            u32StartTimeMs = msAPI_Timer_GetTime0();
            stBitbltInfo.BitbltCoordinate.v2_x = u16PosX;
            stBitbltInfo.BitbltCoordinate.v2_y = u16PosY;
            stBitbltInfo.src_width =
                (u16PosX + PHOTO_TRANS_EFFECT_BLOCK_WIDTH) > PHOTO_ADJUSTED_PANEL_WIDTH ?
                (PHOTO_ADJUSTED_PANEL_WIDTH - (u16PosX + PHOTO_TRANS_EFFECT_BLOCK_WIDTH)) :
                PHOTO_TRANS_EFFECT_BLOCK_WIDTH;
            stBitbltInfo.src_height=
                (u16PosY + PHOTO_TRANS_EFFECT_BLOCK_HEIGHT) > PANEL_HEIGHT?
                (PHOTO_TRANS_EFFECT_BLOCK_HEIGHT-(PANEL_HEIGHT - (u16PosY + PHOTO_TRANS_EFFECT_BLOCK_HEIGHT))) :
                PHOTO_TRANS_EFFECT_BLOCK_HEIGHT;
            stBitbltInfo.BitbltCoordinate.v0_x = u16PosX;
            stBitbltInfo.BitbltCoordinate.v0_y = u16PosY;
            stBitbltInfo.BitbltCoordinate.width = stBitbltInfo.src_width;
            stBitbltInfo.BitbltCoordinate.height = stBitbltInfo.src_height;

            // output image to destination buffer
            msAPI_GE_BitBlt(&stBitbltInfo, &stPitBaseInfo);
            // after BitBlt, flush cmd
            MApi_GFX_FlushQueue();
            msAPI_Timer_ResetWDT();
#if ENABLE_SPEED_MUSIC_BACKGROUND_PLAY
            MApp_Music_InputBackGroundMusicData();
#endif
            u32ElapseTime = msAPI_Timer_DiffTimeFromNow(u32StartTimeMs);
            if(u32ElapseTime < u32Delayms)
            {
                msAPI_Timer_Delayms(u32Delayms - u32ElapseTime);
            }

            if(s16innerIdx < s16innerEnd - 1)
            {
                s16MovePosX += s16innerIncX;
                s16MovePosY += s16innerIncY;
                u16PosX = (s16MovePosX < 0) ? 0 : (U16)s16MovePosX;
                u16PosY = (s16MovePosY < 0) ? 0 : (U16)s16MovePosY;
            }
        }
        s16innerIncX *= s16innerIncChangeX;
        s16innerIncY *= s16innerIncChangeY;
        s16MovePosX += s16outerIncX;
        s16MovePosY += s16outerIncY;
        u16PosX = (s16MovePosX < 0) ? 0 : (U16)s16MovePosX;
        u16PosY = (s16MovePosY < 0) ? 0 : (U16)s16MovePosY;
    }
}

#define  PHOTO_TRANS_EFFECT_BLOCK_RANDOM_NUM    (PHOTO_TRANS_EFFECT_BLOCK_HORZ_NUM*PHOTO_TRANS_EFFECT_BLOCK_VERT_NUM)
static void _MApp_Photo_SlideShow_Blocks_Random(void)
{
    GEBitBltInfo stBitbltInfo;
    GEPitBaseInfo stPitBaseInfo;
    BOOLEAN bPainted[PHOTO_TRANS_EFFECT_BLOCK_RANDOM_NUM];
    U16 u16BlockIdx, u16BlockX, u16BlockY, u16PosX, u16PosY, u16PaintedIdx;
    U32 u32Delayms;
    U32 u32StartTimeMs, u32ElapseTime;

    stPitBaseInfo.sb_pit = PHOTO_ADJUSTED_PANEL_WIDTH*2;
    stPitBaseInfo.sb_base = PHOTO_DISPLAY_SRC_BUFFER_ADDR;          // the address is referring to original image

    stPitBaseInfo.db_pit = PHOTO_ADJUSTED_PANEL_WIDTH * 2;    // 2 bytes per pixel
    stPitBaseInfo.db_base = PHOTO_DISPLAY_BUFFER_ADDR;

    stBitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;
    stBitbltInfo.BmpFlag = GFXDRAW_FLAG_DEFAULT;
    stBitbltInfo.dst_fm = GFX_FMT_YUV422;
    stBitbltInfo.src_fm = GFX_FMT_YUV422;
    msAPI_OSD_SetClipWindow(0, 0, PHOTO_ADJUSTED_PANEL_WIDTH, PANEL_HEIGHT);
    stBitbltInfo.BitbltCoordinate.direction = 0;    // TODO: what's this?
    msAPI_GE_SetNearestMode(TRUE);
    msAPI_GE_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_PC, GFX_YUV_OUT_255, GFX_YUV_IN_255, GFX_YUV_YUYV, GFX_YUV_YUYV);

    u32Delayms = PHOTO_TRANS_EFFECT_BLOCK_UNIT_DELAY_MS;
    memset(bPainted, 0, PHOTO_TRANS_EFFECT_BLOCK_RANDOM_NUM);

    srand(msAPI_Timer_GetTime0());
    for(u16BlockIdx=0;u16BlockIdx<PHOTO_TRANS_EFFECT_BLOCK_RANDOM_NUM;u16BlockIdx++)
    {
        u32StartTimeMs = msAPI_Timer_GetTime0();

        u16PaintedIdx = (U16)((U16)rand() % PHOTO_TRANS_EFFECT_BLOCK_RANDOM_NUM);
        if(bPainted[u16PaintedIdx] == TRUE)
        {   // Find the next non-paint block.
            U16 i;

            for(i=u16PaintedIdx+1;i<PHOTO_TRANS_EFFECT_BLOCK_RANDOM_NUM;i++)
            {
                if(bPainted[i] == FALSE)
                {
                    u16PaintedIdx = i;
                    break;
                }
            }
            if(i >= PHOTO_TRANS_EFFECT_BLOCK_RANDOM_NUM)
            {
                for(i=0;i<u16PaintedIdx;i++)
                {
                    if(bPainted[i] == FALSE)
                    {
                        u16PaintedIdx = i;
                        break;
                    }
                }
            }
        }

        bPainted[u16PaintedIdx] = TRUE;
        u16BlockY = u16PaintedIdx / PHOTO_TRANS_EFFECT_BLOCK_HORZ_NUM;
        u16BlockX = u16PaintedIdx % PHOTO_TRANS_EFFECT_BLOCK_HORZ_NUM;

        u16PosX = u16BlockX * PHOTO_TRANS_EFFECT_BLOCK_WIDTH;
        u16PosY = u16BlockY * PHOTO_TRANS_EFFECT_BLOCK_HEIGHT;

        stBitbltInfo.BitbltCoordinate.v2_x = u16PosX;
        stBitbltInfo.BitbltCoordinate.v2_y = u16PosY;
        stBitbltInfo.src_width =
            (u16PosX + PHOTO_TRANS_EFFECT_BLOCK_WIDTH) > PHOTO_ADJUSTED_PANEL_WIDTH ?
            (PHOTO_ADJUSTED_PANEL_WIDTH - (u16PosX + PHOTO_TRANS_EFFECT_BLOCK_WIDTH)) :
            PHOTO_TRANS_EFFECT_BLOCK_WIDTH;
        stBitbltInfo.src_height =
            (u16PosY + PHOTO_TRANS_EFFECT_BLOCK_HEIGHT) > PANEL_HEIGHT?
            (PANEL_HEIGHT - (u16PosY + PHOTO_TRANS_EFFECT_BLOCK_HEIGHT)) :
            PHOTO_TRANS_EFFECT_BLOCK_HEIGHT;
        stBitbltInfo.BitbltCoordinate.v0_x = u16PosX;
        stBitbltInfo.BitbltCoordinate.v0_y = u16PosY;
        stBitbltInfo.BitbltCoordinate.width = stBitbltInfo.src_width;
        stBitbltInfo.BitbltCoordinate.height = stBitbltInfo.src_height;

        // output image to destination buffer
        msAPI_GE_BitBlt(&stBitbltInfo, &stPitBaseInfo);
        // after BitBlt, flush cmd
        MApi_GFX_FlushQueue();
        msAPI_Timer_ResetWDT();
#if ENABLE_SPEED_MUSIC_BACKGROUND_PLAY
        MApp_Music_InputBackGroundMusicData();
#endif
        u32ElapseTime = msAPI_Timer_DiffTimeFromNow(u32StartTimeMs);
        if(u32ElapseTime < u32Delayms)
        {
            msAPI_Timer_Delayms(u32Delayms - u32ElapseTime);
        }
    }
}
#endif  // #if (ENABLE_PHOTO_TRANS_EFFECT_BLOCKS)

#if (ENABLE_PHOTO_TRANS_EFFECT_DIAGONAL_BLOCKS)
#define TRANS_EFFECT_DIAGONAL_BLOCK_HORZ_WIDTH  ((((PHOTO_ADJUSTED_PANEL_WIDTH+PHOTO_TRANS_EFFECT_DIAGONAL_BLOCK_NUM-1)/PHOTO_TRANS_EFFECT_DIAGONAL_BLOCK_NUM)+1)&0x7FFE)
#define TRANS_EFFECT_DIAGONAL_BLOCK_VERT_WIDTH  ((((PANEL_HEIGHT+PHOTO_TRANS_EFFECT_DIAGONAL_BLOCK_NUM-1)/PHOTO_TRANS_EFFECT_DIAGONAL_BLOCK_NUM)+1)&0x7FFE)
static void _MApp_Photo_SlideShow_Diagonal_Blocks(EN_PHOTO_SLIDE_SHOW_EFFECT eSlideShowEffect)
{
    GEBitBltInfo stBitbltInfo;
    GEPitBaseInfo stPitBaseInfo;
    S16 s16innerIdx, s16outerIdx;
    S16 s16IncX, s16IncY;
    S16 s16PosX, s16PosY;
    S16 s16outerIncX, s16outerIncY;
    U32 u32Delayms;
    U32 u32StartTimeMs, u32ElapseTime;
    BOOLEAN bNextLine;

    stPitBaseInfo.sb_pit = PHOTO_ADJUSTED_PANEL_WIDTH*2;
    stPitBaseInfo.sb_base = PHOTO_DISPLAY_SRC_BUFFER_ADDR;          // the address is referring to original image

    stPitBaseInfo.db_pit = PHOTO_ADJUSTED_PANEL_WIDTH*2;      // 2 bytes per pixel
    stPitBaseInfo.db_base = PHOTO_DISPLAY_BUFFER_ADDR;

    stBitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;
    stBitbltInfo.BmpFlag = GFXDRAW_FLAG_DEFAULT;
    stBitbltInfo.dst_fm = GFX_FMT_YUV422;
    stBitbltInfo.src_fm = GFX_FMT_YUV422;
    msAPI_OSD_SetClipWindow(0, 0, PHOTO_ADJUSTED_PANEL_WIDTH, PANEL_HEIGHT);
    stBitbltInfo.BitbltCoordinate.direction = 0;    // TODO: what's this?
    msAPI_GE_SetNearestMode(TRUE);
    msAPI_GE_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_PC, GFX_YUV_OUT_255, GFX_YUV_IN_255, GFX_YUV_YUYV, GFX_YUV_YUYV);

    switch(eSlideShowEffect)
    {
    case E_SLIDE_SHOW_EFFECT_DIAGONAL_BLOCKS_TOPLEFT:
        s16PosX = 0;
        s16PosY = 0;
        s16IncX = TRANS_EFFECT_DIAGONAL_BLOCK_HORZ_WIDTH;
        s16IncY = -TRANS_EFFECT_DIAGONAL_BLOCK_VERT_WIDTH;
        s16outerIncX = TRANS_EFFECT_DIAGONAL_BLOCK_HORZ_WIDTH/2;
        s16outerIncY = TRANS_EFFECT_DIAGONAL_BLOCK_VERT_WIDTH/2;
        break;
    case E_SLIDE_SHOW_EFFECT_DIAGONAL_BLOCKS_TOPRIGHT:
        s16PosX = PHOTO_ADJUSTED_PANEL_WIDTH - TRANS_EFFECT_DIAGONAL_BLOCK_HORZ_WIDTH;
        s16PosY = 0;
        s16IncX = -TRANS_EFFECT_DIAGONAL_BLOCK_HORZ_WIDTH;
        s16IncY = -TRANS_EFFECT_DIAGONAL_BLOCK_VERT_WIDTH;
        s16outerIncX = -TRANS_EFFECT_DIAGONAL_BLOCK_HORZ_WIDTH/2;
        s16outerIncY = TRANS_EFFECT_DIAGONAL_BLOCK_VERT_WIDTH/2;
        break;
    case E_SLIDE_SHOW_EFFECT_DIAGONAL_BLOCKS_BOTTOMLEFT:
        s16PosX = 0;
        s16PosY = PANEL_HEIGHT - TRANS_EFFECT_DIAGONAL_BLOCK_VERT_WIDTH;
        s16IncX = TRANS_EFFECT_DIAGONAL_BLOCK_HORZ_WIDTH;
        s16IncY = TRANS_EFFECT_DIAGONAL_BLOCK_VERT_WIDTH;
        s16outerIncX = TRANS_EFFECT_DIAGONAL_BLOCK_HORZ_WIDTH/2;
        s16outerIncY = -TRANS_EFFECT_DIAGONAL_BLOCK_VERT_WIDTH/2;
        break;
    case E_SLIDE_SHOW_EFFECT_DIAGONAL_BLOCKS_BOTTOMRIGHT:
        s16PosX = PHOTO_ADJUSTED_PANEL_WIDTH - TRANS_EFFECT_DIAGONAL_BLOCK_HORZ_WIDTH;
        s16PosY = PANEL_HEIGHT - TRANS_EFFECT_DIAGONAL_BLOCK_VERT_WIDTH;
        s16IncX = -TRANS_EFFECT_DIAGONAL_BLOCK_HORZ_WIDTH;
        s16IncY = TRANS_EFFECT_DIAGONAL_BLOCK_VERT_WIDTH;
        s16outerIncX = -TRANS_EFFECT_DIAGONAL_BLOCK_HORZ_WIDTH/2;
        s16outerIncY = -TRANS_EFFECT_DIAGONAL_BLOCK_VERT_WIDTH/2;
        break;
    default:
        return;
    }

    u32Delayms = PHOTO_TRANS_EFFECT_DELAY_MS/(PHOTO_TRANS_EFFECT_DIAGONAL_BLOCK_NUM*2-1);

    for(s16outerIdx=0;s16outerIdx<PHOTO_TRANS_EFFECT_DIAGONAL_BLOCK_NUM*2-1;s16outerIdx++)
    {
        u32StartTimeMs = msAPI_Timer_GetTime0();
        for(s16innerIdx=0;s16innerIdx<PHOTO_TRANS_EFFECT_DIAGONAL_BLOCK_NUM;s16innerIdx++)
        {
            s16PosX = (s16PosX < 0) ? 0 : s16PosX;
            s16PosY = (s16PosY < 0) ? 0 : s16PosY;
            stBitbltInfo.BitbltCoordinate.v2_x = s16PosX;
            stBitbltInfo.BitbltCoordinate.v2_y = s16PosY;
            stBitbltInfo.src_width =
                (s16PosX + TRANS_EFFECT_DIAGONAL_BLOCK_HORZ_WIDTH) > PHOTO_ADJUSTED_PANEL_WIDTH ?
                (PHOTO_ADJUSTED_PANEL_WIDTH - (s16PosX + TRANS_EFFECT_DIAGONAL_BLOCK_HORZ_WIDTH)) :
                TRANS_EFFECT_DIAGONAL_BLOCK_HORZ_WIDTH;
            stBitbltInfo.src_height =
                (s16PosY + TRANS_EFFECT_DIAGONAL_BLOCK_VERT_WIDTH) > PANEL_HEIGHT?
                (PANEL_HEIGHT - (s16PosY + TRANS_EFFECT_DIAGONAL_BLOCK_VERT_WIDTH)) :
                TRANS_EFFECT_DIAGONAL_BLOCK_VERT_WIDTH;
            stBitbltInfo.src_width = (stBitbltInfo.src_width > 0)? stBitbltInfo.src_width : 0;
            stBitbltInfo.src_height = (stBitbltInfo.src_height > 0)? stBitbltInfo.src_height : 0;
            stBitbltInfo.BitbltCoordinate.v0_x = s16PosX;
            stBitbltInfo.BitbltCoordinate.v0_y = s16PosY;
            stBitbltInfo.BitbltCoordinate.width = stBitbltInfo.src_width;
            stBitbltInfo.BitbltCoordinate.height = stBitbltInfo.src_height;

            // output image to destination buffer
            if(stBitbltInfo.src_width > 0 && stBitbltInfo.src_height > 0)
            {
                msAPI_GE_BitBlt(&stBitbltInfo, &stPitBaseInfo);
                // after BitBlt, flush cmd
                MApi_GFX_FlushQueue();
            }
            msAPI_Timer_ResetWDT();

            s16PosX += s16IncX;
            s16PosY += s16IncY;

            bNextLine = FALSE;
            if((s16PosX < 0) && (-s16PosX >= TRANS_EFFECT_DIAGONAL_BLOCK_HORZ_WIDTH))
            {
                bNextLine = TRUE;
            }
            else if((s16PosY < 0) && (-s16PosY >= TRANS_EFFECT_DIAGONAL_BLOCK_VERT_WIDTH))
            {
                bNextLine = TRUE;
            }
            else if((s16PosX >= PHOTO_ADJUSTED_PANEL_WIDTH) || (s16PosY >= PANEL_HEIGHT))
            {
                bNextLine = TRUE;
            }

            if(bNextLine)
            {
                s16IncX = -s16IncX;
                s16IncY = -s16IncY;
                s16PosX += s16outerIncX + s16IncX / 2;
                s16PosY += s16outerIncY + s16IncY / 2;

                if((s16PosX < 0) || (s16PosY < 0) ||
                   (s16PosX >= PHOTO_ADJUSTED_PANEL_WIDTH) || (s16PosY >= PANEL_HEIGHT))
                {
                    s16PosX += s16IncX;
                    s16PosY += s16IncY;
                }
                break;
            }
        }
#if ENABLE_SPEED_MUSIC_BACKGROUND_PLAY
        MApp_Music_InputBackGroundMusicData();
#endif
        u32ElapseTime = msAPI_Timer_DiffTimeFromNow(u32StartTimeMs);
        if(u32ElapseTime < u32Delayms)
        {
            msAPI_Timer_Delayms(u32Delayms - u32ElapseTime);
        }
    }
}
#endif  // #if (ENABLE_PHOTO_TRANS_EFFECT_DIAGONAL_BLOCKS)

#if (ENABLE_PHOTO_TRANS_EFFECT_WIPE)
#define BOX_WIPE_HORZ_STEP_LINES    ((((PHOTO_ADJUSTED_PANEL_WIDTH + PHOTO_TRANS_EFFECT_BOXWIPE_STEPS - 1) / PHOTO_TRANS_EFFECT_BOXWIPE_STEPS)+3)&0x7FFC)
#define BOX_WIPE_VERT_STEP_LINES    ((((PANEL_HEIGHT + PHOTO_TRANS_EFFECT_BOXWIPE_STEPS - 1) / PHOTO_TRANS_EFFECT_BOXWIPE_STEPS)+1)&0x7FFE)
#define IRIS_WIPE_HORZ_STEP_LINES   ((((PHOTO_ADJUSTED_PANEL_WIDTH + PHOTO_TRANS_EFFECT_IRISWIPE_STEPS - 1) / PHOTO_TRANS_EFFECT_IRISWIPE_STEPS)+3)&0x7FFC)
#define IRIS_WIPE_VERT_STEP_LINES   ((((PANEL_HEIGHT + PHOTO_TRANS_EFFECT_IRISWIPE_STEPS - 1) / PHOTO_TRANS_EFFECT_IRISWIPE_STEPS)+1)&0x7FFE)
static void _MApp_Photo_SlideShow_EdgeWipe(EN_PHOTO_SLIDE_SHOW_EFFECT eType)
{
    GEBitBltInfo stBitbltInfo;
    GEPitBaseInfo stPitBaseInfo;
    S16 s16StepIdx, s16StepNum;
    S16 s16StartX[4], s16EndX[4], s16StartY[4], s16EndY[4];
    S16 s16StartIncX[4], s16StartIncY[4], s16EndIncX[4], s16EndIncY[4];
    U32 u32Delayms;
    U16 u8RectIdx, u8RectNum;

    stPitBaseInfo.sb_pit = PHOTO_ADJUSTED_PANEL_WIDTH * 2;
    stPitBaseInfo.sb_base = PHOTO_DISPLAY_SRC_BUFFER_ADDR;          // the address is referring to original image

    stPitBaseInfo.db_pit = PHOTO_ADJUSTED_PANEL_WIDTH * 2;    // 2 bytes per pixel
    stPitBaseInfo.db_base = PHOTO_DISPLAY_BUFFER_ADDR;

    stBitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;
    stBitbltInfo.BmpFlag = GFXDRAW_FLAG_DEFAULT;
    stBitbltInfo.dst_fm = GFX_FMT_YUV422;
    stBitbltInfo.src_fm = GFX_FMT_YUV422;
    msAPI_OSD_SetClipWindow(0, 0, PHOTO_ADJUSTED_PANEL_WIDTH, PANEL_HEIGHT);
    stBitbltInfo.BitbltCoordinate.direction = 0;    // TODO: what's this?
    msAPI_GE_SetNearestMode(TRUE);
    msAPI_GE_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_PC, GFX_YUV_OUT_255, GFX_YUV_IN_255, GFX_YUV_YUYV, GFX_YUV_YUYV);

    //eType = E_SLIDE_SHOW_EFFECT_4BARWIPE_VERTICAL_FROM_LEFT;

    switch(eType)
    {
    case E_SLIDE_SHOW_EFFECT_BARWIPE_LEFT2RIGHT:
        s16StepNum = (PHOTO_ADJUSTED_PANEL_WIDTH + PHOTO_TRANS_EFFECT_BARWIPE_LINE_NUM - 1) /
                    PHOTO_TRANS_EFFECT_BARWIPE_LINE_NUM;
        s16StartX[0] = 0;
        s16EndX[0] = PHOTO_TRANS_EFFECT_BARWIPE_LINE_NUM;
        s16StartY[0] = 0;
        s16StartIncX[0] = PHOTO_TRANS_EFFECT_BARWIPE_LINE_NUM;
        s16EndY[0] = PANEL_HEIGHT;
        s16EndIncX[0] = PHOTO_TRANS_EFFECT_BARWIPE_LINE_NUM;
        s16StartIncY[0] = 0;
        s16EndIncY[0] = 0;
        u8RectNum = 1;
        break;

    case E_SLIDE_SHOW_EFFECT_BARWIPE_RIGHT2LEFT:
        s16StepNum = (PHOTO_ADJUSTED_PANEL_WIDTH + PHOTO_TRANS_EFFECT_BARWIPE_LINE_NUM - 1) /
                    PHOTO_TRANS_EFFECT_BARWIPE_LINE_NUM;
        s16StartX[0] = PHOTO_ADJUSTED_PANEL_WIDTH - PHOTO_TRANS_EFFECT_BARWIPE_LINE_NUM;
        s16StartY[0] = 0;
        s16EndX[0] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16EndY[0] = PANEL_HEIGHT;
        s16StartIncX[0] = -PHOTO_TRANS_EFFECT_BARWIPE_LINE_NUM;
        s16EndIncX[0] = -PHOTO_TRANS_EFFECT_BARWIPE_LINE_NUM;
        s16StartIncY[0] = 0;
        s16EndIncY[0] = 0;
        u8RectNum = 1;
        break;

    case E_SLIDE_SHOW_EFFECT_BARWIPE_TOP2BOTTOM:
        s16StepNum = (PANEL_HEIGHT + PHOTO_TRANS_EFFECT_BARWIPE_LINE_NUM - 1) /
                    PHOTO_TRANS_EFFECT_BARWIPE_LINE_NUM;
        s16StartX[0] = 0;
        s16StartY[0] = 0;
        s16EndX[0] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16EndY[0] = PHOTO_TRANS_EFFECT_BARWIPE_LINE_NUM;
        s16StartIncX[0] = 0;
        s16EndIncX[0] = 0;
        s16StartIncY[0] = PHOTO_TRANS_EFFECT_BARWIPE_LINE_NUM;
        s16EndIncY[0] = PHOTO_TRANS_EFFECT_BARWIPE_LINE_NUM;
        u8RectNum = 1;
        break;

    case E_SLIDE_SHOW_EFFECT_BARWIPE_BOTTOM2TOP:
        s16StepNum = (PANEL_HEIGHT + PHOTO_TRANS_EFFECT_BARWIPE_LINE_NUM - 1) /
                    PHOTO_TRANS_EFFECT_BARWIPE_LINE_NUM;
        s16StartX[0] = 0;
        s16StartY[0] = PANEL_HEIGHT - PHOTO_TRANS_EFFECT_BARWIPE_LINE_NUM;
        s16EndX[0] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16EndY[0] = PANEL_HEIGHT;
        s16StartIncX[0] = 0;
        s16EndIncX[0] = 0;
        s16StartIncY[0] = -PHOTO_TRANS_EFFECT_BARWIPE_LINE_NUM;
        s16EndIncY[0] = -PHOTO_TRANS_EFFECT_BARWIPE_LINE_NUM;
        u8RectNum = 1;
        break;

    case E_SLIDE_SHOW_EFFECT_BOXWIPE_TOPLEFT:
        s16StepNum = PHOTO_TRANS_EFFECT_BOXWIPE_STEPS;
        s16StartX[0] = 0;
        s16StartY[0] = 0;
        s16EndX[0] = BOX_WIPE_HORZ_STEP_LINES;
        s16EndY[0] = BOX_WIPE_VERT_STEP_LINES;
        s16StartIncX[0] = 0;
        s16StartIncY[0] = BOX_WIPE_VERT_STEP_LINES;
        s16EndIncX[0] = BOX_WIPE_HORZ_STEP_LINES;
        s16EndIncY[0] = BOX_WIPE_VERT_STEP_LINES;

        s16StartX[1] = 0;
        s16StartY[1] = 0;
        s16EndX[1] = BOX_WIPE_HORZ_STEP_LINES;
        s16EndY[1] = 0;
        s16StartIncX[1] = BOX_WIPE_HORZ_STEP_LINES;
        s16StartIncY[1] = 0;
        s16EndIncX[1] = BOX_WIPE_HORZ_STEP_LINES;
        s16EndIncY[1] = BOX_WIPE_VERT_STEP_LINES;
        u8RectNum = 2;
        break;

    case E_SLIDE_SHOW_EFFECT_BOXWIPE_TOPRIGHT:
        s16StepNum = PHOTO_TRANS_EFFECT_BOXWIPE_STEPS;
        s16StartX[0] = PHOTO_ADJUSTED_PANEL_WIDTH - BOX_WIPE_HORZ_STEP_LINES;
        s16StartY[0] = 0;
        s16EndX[0] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16EndY[0] = BOX_WIPE_VERT_STEP_LINES;
        s16StartIncX[0] = -BOX_WIPE_HORZ_STEP_LINES;
        s16StartIncY[0] = BOX_WIPE_VERT_STEP_LINES;
        s16EndIncX[0] = 0;
        s16EndIncY[0] = BOX_WIPE_VERT_STEP_LINES;

        s16StartX[1] = PHOTO_ADJUSTED_PANEL_WIDTH - BOX_WIPE_HORZ_STEP_LINES;
        s16StartY[1] = 0;
        s16EndX[1] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16EndY[1] = 0;
        s16StartIncX[1] = -BOX_WIPE_HORZ_STEP_LINES;
        s16StartIncY[1] = 0;
        s16EndIncX[1] = -BOX_WIPE_HORZ_STEP_LINES;
        s16EndIncY[1] = BOX_WIPE_VERT_STEP_LINES;
        u8RectNum = 2;
        break;

    case E_SLIDE_SHOW_EFFECT_BOXWIPE_BOTTOMLEFT:
        s16StepNum = PHOTO_TRANS_EFFECT_BOXWIPE_STEPS;
        s16StartX[0] = 0;
        s16StartY[0] = PANEL_HEIGHT - BOX_WIPE_VERT_STEP_LINES;
        s16EndX[0] = BOX_WIPE_HORZ_STEP_LINES;
        s16EndY[0] = PANEL_HEIGHT;
        s16StartIncX[0] = 0;
        s16StartIncY[0] = -BOX_WIPE_VERT_STEP_LINES;
        s16EndIncX[0] = BOX_WIPE_HORZ_STEP_LINES;
        s16EndIncY[0] = -BOX_WIPE_VERT_STEP_LINES;

        s16StartX[1] = 0;
        s16StartY[1] = PANEL_HEIGHT - BOX_WIPE_VERT_STEP_LINES;
        s16EndX[1] = BOX_WIPE_HORZ_STEP_LINES;
        s16EndY[1] = PANEL_HEIGHT;
        s16StartIncX[1] = BOX_WIPE_HORZ_STEP_LINES;
        s16StartIncY[1] = -BOX_WIPE_VERT_STEP_LINES;
        s16EndIncX[1] = BOX_WIPE_HORZ_STEP_LINES;
        s16EndIncY[1] = 0;
        u8RectNum = 2;
        break;

    case E_SLIDE_SHOW_EFFECT_BOXWIPE_BOTTOMRIGHT:
        s16StepNum = PHOTO_TRANS_EFFECT_BOXWIPE_STEPS;
        s16StartX[0] = PHOTO_ADJUSTED_PANEL_WIDTH - BOX_WIPE_HORZ_STEP_LINES;
        s16StartY[0] = PANEL_HEIGHT - BOX_WIPE_VERT_STEP_LINES;
        s16EndX[0] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16EndY[0] = PANEL_HEIGHT;
        s16StartIncX[0] = -BOX_WIPE_HORZ_STEP_LINES;
        s16StartIncY[0] = -BOX_WIPE_VERT_STEP_LINES;
        s16EndIncX[0] = 0;
        s16EndIncY[0] = -BOX_WIPE_VERT_STEP_LINES;

        s16StartX[1] = PHOTO_ADJUSTED_PANEL_WIDTH - BOX_WIPE_HORZ_STEP_LINES;
        s16StartY[1] = PANEL_HEIGHT;
        s16EndX[1] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16EndY[1] = PANEL_HEIGHT;
        s16StartIncX[1] = -BOX_WIPE_HORZ_STEP_LINES;
        s16StartIncY[1] = -BOX_WIPE_VERT_STEP_LINES;
        s16EndIncX[1] = -BOX_WIPE_HORZ_STEP_LINES;
        s16EndIncY[1] = 0;
        u8RectNum = 2;
        break;

    case E_SLIDE_SHOW_EFFECT_BARNDOORWIPE_HORIZONTAL_OPEN:
        s16StepNum = (PANEL_HEIGHT + PHOTO_TRANS_EFFECT_BARNDOORWIPE_LINE_NUM - 1) /
                      PHOTO_TRANS_EFFECT_BARNDOORWIPE_LINE_NUM;
        s16StartX[0] = 0;
        s16StartY[0] = PANEL_HEIGHT / 2 - PHOTO_TRANS_EFFECT_BARNDOORWIPE_LINE_NUM / 2;
        s16EndX[0] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16EndY[0] = PANEL_HEIGHT / 2;
        s16StartIncX[0] = 0;
        s16StartIncY[0] = -PHOTO_TRANS_EFFECT_BARNDOORWIPE_LINE_NUM/2;
        s16EndIncX[0] = 0;
        s16EndIncY[0] = -PHOTO_TRANS_EFFECT_BARNDOORWIPE_LINE_NUM/2;

        s16StartX[1] = 0;
        s16StartY[1] = PANEL_HEIGHT / 2;
        s16EndX[1] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16EndY[1] = PANEL_HEIGHT / 2 + PHOTO_TRANS_EFFECT_BARNDOORWIPE_LINE_NUM / 2;
        s16StartIncX[1] = 0;
        s16StartIncY[1] = PHOTO_TRANS_EFFECT_BARNDOORWIPE_LINE_NUM/2;
        s16EndIncX[1] = 0;
        s16EndIncY[1] = PHOTO_TRANS_EFFECT_BARNDOORWIPE_LINE_NUM/2;
        u8RectNum = 2;
        break;

    case E_SLIDE_SHOW_EFFECT_BARNDOORWIPE_HORIZONTAL_CLOSE:
        s16StepNum = (PANEL_HEIGHT + PHOTO_TRANS_EFFECT_BARNDOORWIPE_LINE_NUM - 1) /
                      PHOTO_TRANS_EFFECT_BARNDOORWIPE_LINE_NUM;
        s16StartX[0] = 0;
        s16StartY[0] = 0;
        s16EndX[0] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16EndY[0] = PHOTO_TRANS_EFFECT_BARNDOORWIPE_LINE_NUM / 2;
        s16StartIncX[0] = 0;
        s16StartIncY[0] = PHOTO_TRANS_EFFECT_BARNDOORWIPE_LINE_NUM/2;
        s16EndIncX[0] = 0;
        s16EndIncY[0] = PHOTO_TRANS_EFFECT_BARNDOORWIPE_LINE_NUM/2;

        s16StartX[1] = 0;
        s16StartY[1] = PANEL_HEIGHT - PHOTO_TRANS_EFFECT_BARNDOORWIPE_LINE_NUM / 2;
        s16EndX[1] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16EndY[1] = PANEL_HEIGHT;
        s16StartIncX[1] = 0;
        s16StartIncY[1] = -PHOTO_TRANS_EFFECT_BARNDOORWIPE_LINE_NUM/2;
        s16EndIncX[1] = 0;
        s16EndIncY[1] = -PHOTO_TRANS_EFFECT_BARNDOORWIPE_LINE_NUM/2;
        u8RectNum = 2;
        break;

    case E_SLIDE_SHOW_EFFECT_BARNDOORWIPE_VERTICAL_OPEN:
        s16StepNum = (PHOTO_ADJUSTED_PANEL_WIDTH + PHOTO_TRANS_EFFECT_BARNDOORWIPE_LINE_NUM - 1) /
                      PHOTO_TRANS_EFFECT_BARNDOORWIPE_LINE_NUM;
        s16StartX[0] = PHOTO_ADJUSTED_PANEL_WIDTH / 2 -
                          PHOTO_TRANS_EFFECT_BARNDOORWIPE_LINE_NUM / 2;
        s16StartY[0] = 0;
        s16EndX[0] = PHOTO_ADJUSTED_PANEL_WIDTH / 2;
        s16EndY[0] = PANEL_HEIGHT;
        s16StartIncX[0] = -PHOTO_TRANS_EFFECT_BARNDOORWIPE_LINE_NUM / 2;
        s16StartIncY[0] = 0;
        s16EndIncX[0] = -PHOTO_TRANS_EFFECT_BARNDOORWIPE_LINE_NUM / 2;
        s16EndIncY[0] = 0;

        s16StartX[1] = PHOTO_ADJUSTED_PANEL_WIDTH / 2;
        s16StartY[1] = 0;
        s16EndX[1] = PHOTO_ADJUSTED_PANEL_WIDTH / 2 +
                        PHOTO_TRANS_EFFECT_BARNDOORWIPE_LINE_NUM / 2;
        s16EndY[1] = PANEL_HEIGHT;
        s16StartIncX[1] = PHOTO_TRANS_EFFECT_BARNDOORWIPE_LINE_NUM / 2;
        s16StartIncY[1] = 0;
        s16EndIncX[1] = PHOTO_TRANS_EFFECT_BARNDOORWIPE_LINE_NUM / 2;
        s16EndIncY[1] = 0;
        u8RectNum = 2;
        break;

    case E_SLIDE_SHOW_EFFECT_BARNDOORWIPE_VERTICAL_CLOSE:
        s16StepNum = (PHOTO_ADJUSTED_PANEL_WIDTH + PHOTO_TRANS_EFFECT_BARNDOORWIPE_LINE_NUM - 1) /
                      PHOTO_TRANS_EFFECT_BARNDOORWIPE_LINE_NUM;
        s16StartX[0] = 0;
        s16StartY[0] = 0;
        s16EndX[0] = PHOTO_TRANS_EFFECT_BARNDOORWIPE_LINE_NUM / 2;
        s16EndY[0] = PANEL_HEIGHT;
        s16StartIncX[0] = PHOTO_TRANS_EFFECT_BARNDOORWIPE_LINE_NUM / 2;
        s16StartIncY[0] = 0;
        s16EndIncX[0] = PHOTO_TRANS_EFFECT_BARNDOORWIPE_LINE_NUM / 2;
        s16EndIncY[0] = 0;

        s16StartX[1] = PHOTO_ADJUSTED_PANEL_WIDTH - PHOTO_TRANS_EFFECT_BARNDOORWIPE_LINE_NUM / 2;
        s16StartY[1] = 0;
        s16EndX[1] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16EndY[1] = PANEL_HEIGHT;
        s16StartIncX[1] = -PHOTO_TRANS_EFFECT_BARNDOORWIPE_LINE_NUM / 2;
        s16StartIncY[1] = 0;
        s16EndIncX[1] = -PHOTO_TRANS_EFFECT_BARNDOORWIPE_LINE_NUM / 2;
        s16EndIncY[1] = 0;
        u8RectNum = 2;
        break;

    case E_SLIDE_SHOW_EFFECT_BOXWIPE_TOPCENTER:
        s16StepNum = PHOTO_TRANS_EFFECT_BOXWIPE_STEPS;
        s16StartX[0] = PHOTO_ADJUSTED_PANEL_WIDTH / 2 - BOX_WIPE_HORZ_STEP_LINES / 2;
        s16StartY[0] = 0;
        s16EndX[0] = PHOTO_ADJUSTED_PANEL_WIDTH / 2;
        s16EndY[0] = 0;
        s16StartIncX[0] = -BOX_WIPE_HORZ_STEP_LINES / 2;
        s16StartIncY[0] = 0;
        s16EndIncX[0] = -BOX_WIPE_HORZ_STEP_LINES / 2;
        s16EndIncY[0] = BOX_WIPE_VERT_STEP_LINES;

        s16StartX[1] = PHOTO_ADJUSTED_PANEL_WIDTH / 2 - BOX_WIPE_HORZ_STEP_LINES / 2;
        s16StartY[1] = 0;
        s16EndX[1] = PHOTO_ADJUSTED_PANEL_WIDTH / 2 + BOX_WIPE_HORZ_STEP_LINES / 2;
        s16EndY[1] = BOX_WIPE_VERT_STEP_LINES;
        s16StartIncX[1] = -BOX_WIPE_HORZ_STEP_LINES / 2;
        s16StartIncY[1] = BOX_WIPE_VERT_STEP_LINES;
        s16EndIncX[1] = BOX_WIPE_HORZ_STEP_LINES/2;
        s16EndIncY[1] = BOX_WIPE_VERT_STEP_LINES;

        s16StartX[2] = PHOTO_ADJUSTED_PANEL_WIDTH / 2;
        s16StartY[2] = 0;
        s16EndX[2] = PHOTO_ADJUSTED_PANEL_WIDTH / 2 + BOX_WIPE_HORZ_STEP_LINES / 2;
        s16EndY[2] = 0;
        s16StartIncX[2] = BOX_WIPE_HORZ_STEP_LINES / 2;
        s16StartIncY[2] = 0;
        s16EndIncX[2] = BOX_WIPE_HORZ_STEP_LINES / 2;
        s16EndIncY[2] = BOX_WIPE_VERT_STEP_LINES;
        u8RectNum = 3;
        break;

    case E_SLIDE_SHOW_EFFECT_BOXWIPE_RIGHTCENTER:
        s16StepNum = PHOTO_TRANS_EFFECT_BOXWIPE_STEPS;
        s16StartX[0] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16StartY[0] = PANEL_HEIGHT / 2 - BOX_WIPE_VERT_STEP_LINES / 2;
        s16EndX[0] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16EndY[0] = PANEL_HEIGHT / 2;
        s16StartIncX[0] = -BOX_WIPE_HORZ_STEP_LINES;
        s16StartIncY[0] = -BOX_WIPE_VERT_STEP_LINES / 2;
        s16EndIncX[0] = 0;
        s16EndIncY[0] = -BOX_WIPE_VERT_STEP_LINES / 2;

        s16StartX[1] = PHOTO_ADJUSTED_PANEL_WIDTH - BOX_WIPE_HORZ_STEP_LINES;
        s16StartY[1] = PANEL_HEIGHT / 2 - BOX_WIPE_VERT_STEP_LINES / 2;
        s16EndX[1] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16EndY[1] = PANEL_HEIGHT / 2 + BOX_WIPE_VERT_STEP_LINES / 2;
        s16StartIncX[1] = -BOX_WIPE_HORZ_STEP_LINES;
        s16StartIncY[1] = -BOX_WIPE_VERT_STEP_LINES/2;
        s16EndIncX[1] = -BOX_WIPE_HORZ_STEP_LINES;
        s16EndIncY[1] = BOX_WIPE_VERT_STEP_LINES/2;

        s16StartX[2] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16StartY[2] = PANEL_HEIGHT / 2;
        s16EndX[2] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16EndY[2] = PANEL_HEIGHT / 2 + BOX_WIPE_VERT_STEP_LINES / 2;
        s16StartIncX[2] = -BOX_WIPE_HORZ_STEP_LINES;
        s16StartIncY[2] = BOX_WIPE_VERT_STEP_LINES / 2;
        s16EndIncX[2] = 0;
        s16EndIncY[2] = BOX_WIPE_VERT_STEP_LINES/2;
        u8RectNum = 3;
        break;

    case E_SLIDE_SHOW_EFFECT_BOXWIPE_BOTTOMCENTER:
        s16StepNum = PHOTO_TRANS_EFFECT_BOXWIPE_STEPS;
        s16StartX[0] = PHOTO_ADJUSTED_PANEL_WIDTH / 2 - BOX_WIPE_HORZ_STEP_LINES / 2;
        s16StartY[0] = PANEL_HEIGHT;
        s16EndX[0] = PHOTO_ADJUSTED_PANEL_WIDTH / 2;
        s16EndY[0] = PANEL_HEIGHT;
        s16StartIncX[0] = -BOX_WIPE_HORZ_STEP_LINES / 2;
        s16StartIncY[0] = -BOX_WIPE_VERT_STEP_LINES;
        s16EndIncX[0] = -BOX_WIPE_HORZ_STEP_LINES / 2;
        s16EndIncY[0] = 0;

        s16StartX[1] = PHOTO_ADJUSTED_PANEL_WIDTH / 2 - BOX_WIPE_HORZ_STEP_LINES / 2;
        s16StartY[1] = PANEL_HEIGHT - BOX_WIPE_VERT_STEP_LINES;
        s16EndX[1] = PHOTO_ADJUSTED_PANEL_WIDTH / 2 + BOX_WIPE_HORZ_STEP_LINES / 2;
        s16EndY[1] = PANEL_HEIGHT;
        s16StartIncX[1] = -BOX_WIPE_HORZ_STEP_LINES / 2;
        s16StartIncY[1] = -BOX_WIPE_VERT_STEP_LINES;
        s16EndIncX[1] = BOX_WIPE_HORZ_STEP_LINES / 2;
        s16EndIncY[1] = -BOX_WIPE_VERT_STEP_LINES;

        s16StartX[2] = PHOTO_ADJUSTED_PANEL_WIDTH / 2;
        s16StartY[2] = PANEL_HEIGHT;
        s16EndX[2] = PHOTO_ADJUSTED_PANEL_WIDTH / 2 + BOX_WIPE_HORZ_STEP_LINES / 2;
        s16EndY[2] = PANEL_HEIGHT;
        s16StartIncX[2] = BOX_WIPE_HORZ_STEP_LINES / 2;
        s16StartIncY[2] = -BOX_WIPE_VERT_STEP_LINES;
        s16EndIncX[2] = BOX_WIPE_HORZ_STEP_LINES / 2;
        s16EndIncY[2] = 0;
        u8RectNum = 3;
        break;

    case E_SLIDE_SHOW_EFFECT_BOXWIPE_LEFTCENTER:
        s16StepNum = PHOTO_TRANS_EFFECT_BOXWIPE_STEPS;
        s16StartX[0] = 0;
        s16StartY[0] = PANEL_HEIGHT / 2 - BOX_WIPE_VERT_STEP_LINES / 2;
        s16EndX[0] = 0;
        s16EndY[0] = PANEL_HEIGHT / 2;
        s16StartIncX[0] = 0;
        s16StartIncY[0] = -BOX_WIPE_VERT_STEP_LINES / 2;
        s16EndIncX[0] = BOX_WIPE_HORZ_STEP_LINES;
        s16EndIncY[0] = -BOX_WIPE_VERT_STEP_LINES / 2;

        s16StartX[1] = 0;
        s16StartY[1] = PANEL_HEIGHT / 2 - BOX_WIPE_VERT_STEP_LINES / 2;
        s16EndX[1] = BOX_WIPE_HORZ_STEP_LINES;
        s16EndY[1] = PANEL_HEIGHT / 2 + BOX_WIPE_VERT_STEP_LINES / 2;
        s16StartIncX[1] = BOX_WIPE_HORZ_STEP_LINES;
        s16StartIncY[1] = -BOX_WIPE_VERT_STEP_LINES/2;
        s16EndIncX[1] = BOX_WIPE_HORZ_STEP_LINES;
        s16EndIncY[1] = BOX_WIPE_VERT_STEP_LINES/2;

        s16StartX[2] = 0;
        s16StartY[2] = PANEL_HEIGHT / 2;
        s16EndX[2] = 0;
        s16EndY[2] = PANEL_HEIGHT / 2 + BOX_WIPE_VERT_STEP_LINES / 2;
        s16StartIncX[2] = 0;
        s16StartIncY[2] = BOX_WIPE_VERT_STEP_LINES / 2;
        s16EndIncX[2] = BOX_WIPE_HORZ_STEP_LINES;
        s16EndIncY[2] = BOX_WIPE_VERT_STEP_LINES/2;
        u8RectNum = 3;
        break;

    case E_SLIDE_SHOW_EFFECT_IRISWIPE_CENTER:
        s16StepNum = PHOTO_TRANS_EFFECT_IRISWIPE_STEPS;
        s16StartX[0] = PHOTO_ADJUSTED_PANEL_WIDTH / 2;
        s16StartY[0] = PANEL_HEIGHT / 2 - IRIS_WIPE_VERT_STEP_LINES / 2;
        s16EndX[0] = PHOTO_ADJUSTED_PANEL_WIDTH / 2;
        s16EndY[0] = PANEL_HEIGHT / 2;
        s16StartIncX[0] = -IRIS_WIPE_HORZ_STEP_LINES / 2;
        s16StartIncY[0] = -IRIS_WIPE_VERT_STEP_LINES / 2;
        s16EndIncX[0] = IRIS_WIPE_HORZ_STEP_LINES / 2;
        s16EndIncY[0] = -IRIS_WIPE_VERT_STEP_LINES / 2;

        s16StartX[1] = PHOTO_ADJUSTED_PANEL_WIDTH / 2;
        s16StartY[1] = PANEL_HEIGHT / 2;
        s16EndX[1] = PHOTO_ADJUSTED_PANEL_WIDTH / 2;
        s16EndY[1] = PANEL_HEIGHT / 2 + IRIS_WIPE_VERT_STEP_LINES / 2;
        s16StartIncX[1] = -IRIS_WIPE_HORZ_STEP_LINES / 2;
        s16StartIncY[1] = IRIS_WIPE_VERT_STEP_LINES / 2;
        s16EndIncX[1] = IRIS_WIPE_HORZ_STEP_LINES / 2;
        s16EndIncY[1] = IRIS_WIPE_VERT_STEP_LINES / 2;

        s16StartX[2] = PHOTO_ADJUSTED_PANEL_WIDTH / 2 - IRIS_WIPE_HORZ_STEP_LINES / 2;
        s16StartY[2] = PANEL_HEIGHT / 2 - IRIS_WIPE_VERT_STEP_LINES / 2;
        s16EndX[2] = PHOTO_ADJUSTED_PANEL_WIDTH / 2;
        s16EndY[2] = PANEL_HEIGHT / 2 + IRIS_WIPE_VERT_STEP_LINES / 2;
        s16StartIncX[2] = -IRIS_WIPE_HORZ_STEP_LINES / 2;
        s16StartIncY[2] = -IRIS_WIPE_VERT_STEP_LINES / 2;
        s16EndIncX[2] = IRIS_WIPE_HORZ_STEP_LINES / 2;
        s16EndIncY[2] = IRIS_WIPE_VERT_STEP_LINES / 2;

        s16StartX[3] = PHOTO_ADJUSTED_PANEL_WIDTH / 2;
        s16StartY[3] = PANEL_HEIGHT / 2 - IRIS_WIPE_VERT_STEP_LINES / 2;
        s16EndX[3] = PHOTO_ADJUSTED_PANEL_WIDTH / 2 + IRIS_WIPE_HORZ_STEP_LINES / 2;
        s16EndY[3] = PANEL_HEIGHT / 2 + IRIS_WIPE_VERT_STEP_LINES / 2;
        s16StartIncX[3] = IRIS_WIPE_HORZ_STEP_LINES / 2;
        s16StartIncY[3] = -IRIS_WIPE_VERT_STEP_LINES / 2;
        s16EndIncX[3] = IRIS_WIPE_HORZ_STEP_LINES / 2;
        s16EndIncY[3] = IRIS_WIPE_VERT_STEP_LINES / 2;
        u8RectNum = 4;
        break;

    case E_SLIDE_SHOW_EFFECT_IRISWIPE_OUTER:
        s16StepNum = PHOTO_TRANS_EFFECT_IRISWIPE_STEPS;
        s16StartX[0] = IRIS_WIPE_HORZ_STEP_LINES / 2;
        s16StartY[0] = 0;
        s16EndX[0] = PHOTO_ADJUSTED_PANEL_WIDTH - IRIS_WIPE_HORZ_STEP_LINES / 2;
        s16EndY[0] = IRIS_WIPE_VERT_STEP_LINES / 2;
        s16StartIncX[0] = IRIS_WIPE_HORZ_STEP_LINES / 2;
        s16StartIncY[0] = IRIS_WIPE_VERT_STEP_LINES / 2;
        s16EndIncX[0] = -IRIS_WIPE_HORZ_STEP_LINES / 2;
        s16EndIncY[0] = IRIS_WIPE_VERT_STEP_LINES / 2;

        s16StartX[1] = IRIS_WIPE_HORZ_STEP_LINES / 2;
        s16StartY[1] = PANEL_HEIGHT - IRIS_WIPE_VERT_STEP_LINES / 2;
        s16EndX[1] = PHOTO_ADJUSTED_PANEL_WIDTH - IRIS_WIPE_HORZ_STEP_LINES / 2;
        s16EndY[1] = PANEL_HEIGHT;
        s16StartIncX[1] = IRIS_WIPE_HORZ_STEP_LINES / 2;
        s16StartIncY[1] = -IRIS_WIPE_VERT_STEP_LINES / 2;
        s16EndIncX[1] = -IRIS_WIPE_HORZ_STEP_LINES / 2;
        s16EndIncY[1] = -IRIS_WIPE_VERT_STEP_LINES / 2;

        s16StartX[2] = 0;
        s16StartY[2] = 0;
        s16EndX[2] = IRIS_WIPE_HORZ_STEP_LINES / 2;
        s16EndY[2] = PANEL_HEIGHT;
        s16StartIncX[2] = IRIS_WIPE_HORZ_STEP_LINES / 2;
        s16StartIncY[2] = IRIS_WIPE_VERT_STEP_LINES / 2;
        s16EndIncX[2] = IRIS_WIPE_HORZ_STEP_LINES / 2;
        s16EndIncY[2] = -IRIS_WIPE_VERT_STEP_LINES / 2;

        s16StartX[3] = PHOTO_ADJUSTED_PANEL_WIDTH - IRIS_WIPE_HORZ_STEP_LINES / 2;
        s16StartY[3] = 0;
        s16EndX[3] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16EndY[3] = PANEL_HEIGHT;
        s16StartIncX[3] = -IRIS_WIPE_HORZ_STEP_LINES / 2;
        s16StartIncY[3] = IRIS_WIPE_VERT_STEP_LINES / 2;
        s16EndIncX[3] = -IRIS_WIPE_HORZ_STEP_LINES / 2;
        s16EndIncY[3] = -IRIS_WIPE_VERT_STEP_LINES / 2;
        u8RectNum = 4;
        break;

    case E_SLIDE_SHOW_EFFECT_4BARWIPE_HORIZONTAL_FROM_TOP:
        s16StepNum = ((PANEL_HEIGHT + 3) / 4 + PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM - 1) /
                     PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16StartX[0] = 0;
        s16StartY[0] = 0;
        s16EndX[0] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16EndY[0] = PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16StartIncX[0] = 0;
        s16StartIncY[0] = PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16EndIncX[0] = 0;
        s16EndIncY[0] = PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;

        s16StartX[1] = 0;
        s16StartY[1] = PANEL_HEIGHT / 4;
        s16EndX[1] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16EndY[1] = PANEL_HEIGHT / 4 + PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16StartIncX[1] = 0;
        s16StartIncY[1] = PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16EndIncX[1] = 0;
        s16EndIncY[1] = PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;

        s16StartX[2] = 0;
        s16StartY[2] = PANEL_HEIGHT * 2 / 4;
        s16EndX[2] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16EndY[2] = PANEL_HEIGHT * 2 / 4 + PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16StartIncX[2] = 0;
        s16StartIncY[2] = PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16EndIncX[2] = 0;
        s16EndIncY[2] = PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;

        s16StartX[3] = 0;
        s16StartY[3] = PANEL_HEIGHT * 3 / 4;
        s16EndX[3] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16EndY[3] = PANEL_HEIGHT * 3 / 4 + PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16StartIncX[3] = 0;
        s16StartIncY[3] = PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16EndIncX[3] = 0;
        s16EndIncY[3] = PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        u8RectNum = 4;
        break;

    case E_SLIDE_SHOW_EFFECT_4BARWIPE_HORIZONTAL_FROM_BOTTOM:
        s16StepNum = ((PANEL_HEIGHT + 3) / 4 + PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM - 1) /
                     PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16StartX[0] = 0;
        s16StartY[0] = PANEL_HEIGHT / 4 - PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16EndX[0] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16EndY[0] = PANEL_HEIGHT / 4;
        s16StartIncX[0] = 0;
        s16StartIncY[0] = -PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16EndIncX[0] = 0;
        s16EndIncY[0] = -PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;

        s16StartX[1] = 0;
        s16StartY[1] = PANEL_HEIGHT * 2 / 4 - PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16EndX[1] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16EndY[1] = PANEL_HEIGHT * 2 / 4;
        s16StartIncX[1] = 0;
        s16StartIncY[1] = -PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16EndIncX[1] = 0;
        s16EndIncY[1] = -PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;

        s16StartX[2] = 0;
        s16StartY[2] = PANEL_HEIGHT * 3 / 4 - PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16EndX[2] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16EndY[2] = PANEL_HEIGHT * 3 / 4;
        s16StartIncX[2] = 0;
        s16StartIncY[2] = -PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16EndIncX[2] = 0;
        s16EndIncY[2] = -PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;

        s16StartX[3] = 0;
        s16StartY[3] = PANEL_HEIGHT - PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16EndX[3] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16EndY[3] = PANEL_HEIGHT;
        s16StartIncX[3] = 0;
        s16StartIncY[3] = -PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16EndIncX[3] = 0;
        s16EndIncY[3] = -PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        u8RectNum = 4;
        break;

    case E_SLIDE_SHOW_EFFECT_4BARWIPE_VERTICAL_FROM_LEFT:
        s16StepNum = ((PHOTO_ADJUSTED_PANEL_WIDTH + 3) / 4 + PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM - 1) /
                     PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16StartX[0] = 0;
        s16StartY[0] = 0;
        s16EndX[0] = PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16EndY[0] = PANEL_HEIGHT;
        s16StartIncX[0] = PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16StartIncY[0] = 0;
        s16EndIncX[0] = PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16EndIncY[0] = 0;

        s16StartX[1] = PHOTO_ADJUSTED_PANEL_WIDTH / 4;
        s16StartY[1] = 0;
        s16EndX[1] = PHOTO_ADJUSTED_PANEL_WIDTH / 4 + PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16EndY[1] = PANEL_HEIGHT;
        s16StartIncX[1] = PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16StartIncY[1] = 0;
        s16EndIncX[1] = PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16EndIncY[1] = 0;

        s16StartX[2] = PHOTO_ADJUSTED_PANEL_WIDTH * 2 / 4;
        s16StartY[2] = 0;
        s16EndX[2] = PHOTO_ADJUSTED_PANEL_WIDTH * 2 / 4 + PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16EndY[2] = PANEL_HEIGHT;
        s16StartIncX[2] = PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16StartIncY[2] = 0;
        s16EndIncX[2] = PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16EndIncY[2] = 0;

        s16StartX[3] = PHOTO_ADJUSTED_PANEL_WIDTH * 3 / 4;
        s16StartY[3] = 0;
        s16EndX[3] = PHOTO_ADJUSTED_PANEL_WIDTH * 3 / 4 + PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16EndY[3] = PANEL_HEIGHT;
        s16StartIncX[3] = PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16StartIncY[3] = 0;
        s16EndIncX[3] = PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16EndIncY[3] = 0;
        u8RectNum = 4;
        break;

    case E_SLIDE_SHOW_EFFECT_4BARWIPE_VERTICAL_FROM_RIGHT:
        s16StepNum = ((PHOTO_ADJUSTED_PANEL_WIDTH + 3) / 4 + PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM - 1) /
                     PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16StartX[0] = PHOTO_ADJUSTED_PANEL_WIDTH / 4 - PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16StartY[0] = 0;
        s16EndX[0] = PHOTO_ADJUSTED_PANEL_WIDTH / 4;
        s16EndY[0] = PANEL_HEIGHT;
        s16StartIncX[0] = -PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16StartIncY[0] = 0;
        s16EndIncX[0] = -PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16EndIncY[0] = 0;

        s16StartX[1] = PHOTO_ADJUSTED_PANEL_WIDTH * 2 / 4 - PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16StartY[1] = 0;
        s16EndX[1] = PHOTO_ADJUSTED_PANEL_WIDTH * 2 / 4;
        s16EndY[1] = PANEL_HEIGHT;
        s16StartIncX[1] = -PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16StartIncY[1] = 0;
        s16EndIncX[1] = -PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16EndIncY[1] = 0;

        s16StartX[2] = PHOTO_ADJUSTED_PANEL_WIDTH * 3 / 4 - PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16StartY[2] = 0;
        s16EndX[2] = PHOTO_ADJUSTED_PANEL_WIDTH * 3 / 4;
        s16EndY[2] = PANEL_HEIGHT;
        s16StartIncX[2] = -PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16StartIncY[2] = 0;
        s16EndIncX[2] = -PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16EndIncY[2] = 0;

        s16StartX[3] = PHOTO_ADJUSTED_PANEL_WIDTH - PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16StartY[3] = 0;
        s16EndX[3] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16EndY[3] = PANEL_HEIGHT;
        s16StartIncX[3] = -PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16StartIncY[3] = 0;
        s16EndIncX[3] = -PHOTO_TRANS_EFFECT_4BARWIPE_LINE_NUM;
        s16EndIncY[3] = 0;
        u8RectNum = 4;
        break;
    default:
        return;
    }
    u32Delayms = PHOTO_TRANS_EFFECT_DELAY_MS / s16StepNum;

    for(s16StepIdx=0;s16StepIdx<s16StepNum;s16StepIdx++)
    {
        U32 u32StartTimeMs, u32ElapseTime;

        u32StartTimeMs = msAPI_Timer_GetTime0();

        for(u8RectIdx = 0; u8RectIdx < u8RectNum; u8RectIdx++)
        {
            stBitbltInfo.BitbltCoordinate.v2_x = s16StartX[u8RectIdx];
            stBitbltInfo.BitbltCoordinate.v2_y = s16StartY[u8RectIdx];
            stBitbltInfo.src_width = s16EndX[u8RectIdx] - s16StartX[u8RectIdx];
            stBitbltInfo.src_height = s16EndY[u8RectIdx] - s16StartY[u8RectIdx];
            stBitbltInfo.BitbltCoordinate.v0_x = s16StartX[u8RectIdx];
            stBitbltInfo.BitbltCoordinate.v0_y = s16StartY[u8RectIdx];
            stBitbltInfo.BitbltCoordinate.width = stBitbltInfo.src_width;
            stBitbltInfo.BitbltCoordinate.height = stBitbltInfo.src_height;

            // output image to destination buffer
            if(s16EndX[u8RectIdx] > s16StartX[u8RectIdx] &&
               s16EndY[u8RectIdx] > s16StartY[u8RectIdx])
            {
                msAPI_GE_BitBlt(&stBitbltInfo, &stPitBaseInfo);
                // after BitBlt, flush cmd
                MApi_GFX_FlushQueue();
            }

            s16StartX[u8RectIdx] = s16StartX[u8RectIdx]+s16StartIncX[u8RectIdx];
            s16StartX[u8RectIdx] = (s16StartX[u8RectIdx] < 0) ? 0 : s16StartX[u8RectIdx];
            s16StartX[u8RectIdx] = (s16StartX[u8RectIdx] > PHOTO_ADJUSTED_PANEL_WIDTH) ?
                              PHOTO_ADJUSTED_PANEL_WIDTH : s16StartX[u8RectIdx];

            s16StartY[u8RectIdx] = s16StartY[u8RectIdx]+s16StartIncY[u8RectIdx];
            s16StartY[u8RectIdx] = (s16StartY[u8RectIdx] < 0) ? 0 : s16StartY[u8RectIdx];
            s16StartY[u8RectIdx] = (s16StartY[u8RectIdx] > PANEL_HEIGHT) ?
                              PANEL_HEIGHT : s16StartY[u8RectIdx];

            s16EndX[u8RectIdx] = s16EndX[u8RectIdx]+s16EndIncX[u8RectIdx];
            s16EndX[u8RectIdx] = (s16EndX[u8RectIdx] < 0) ? 0 : s16EndX[u8RectIdx];
            s16EndX[u8RectIdx] = (s16EndX[u8RectIdx] > PHOTO_ADJUSTED_PANEL_WIDTH) ?
                              PHOTO_ADJUSTED_PANEL_WIDTH : s16EndX[u8RectIdx];

            s16EndY[u8RectIdx] = s16EndY[u8RectIdx]+s16EndIncY[u8RectIdx];
            s16EndY[u8RectIdx] = (s16EndY[u8RectIdx] < 0) ? 0 : s16EndY[u8RectIdx];
            s16EndY[u8RectIdx] = (s16EndY[u8RectIdx] > PANEL_HEIGHT) ?
                              PANEL_HEIGHT : s16EndY[u8RectIdx];
        }
        msAPI_Timer_ResetWDT();

#if ENABLE_SPEED_MUSIC_BACKGROUND_PLAY
        MApp_Music_InputBackGroundMusicData();
#endif
        u32ElapseTime = msAPI_Timer_DiffTimeFromNow(u32StartTimeMs);
        if(u32ElapseTime < u32Delayms)
        {
            msAPI_Timer_Delayms(u32Delayms - u32ElapseTime);
        }
    }
}
#endif  // #if (ENABLE_PHOTO_TRANS_EFFECT_WIPE)

#if (ENABLE_PHOTO_TRANS_EFFECT_SLIDE)
#define TRANS_SLIDE_HORZ_LINE_NUM       ((PHOTO_ADJUSTED_PANEL_WIDTH + (PHOTO_TRANS_EFFECT_SLIDE_STEPS-1)) / PHOTO_TRANS_EFFECT_SLIDE_STEPS)
#define TRANS_SLIDE_VERT_LINE_NUM       ((PANEL_HEIGHT+ (PHOTO_TRANS_EFFECT_SLIDE_STEPS-1)) / PHOTO_TRANS_EFFECT_SLIDE_STEPS)
#define X4BARSLIDE_HORZ_LINE_NUM        ((TRANS_SLIDE_HORZ_LINE_NUM + 3) / 4)
#define X4BARSLIDE_VERT_LINE_NUM        ((TRANS_SLIDE_VERT_LINE_NUM + 3) / 4)
#define BARNDOORSLIDE_HORZ_LINE_NUM     ((TRANS_SLIDE_HORZ_LINE_NUM + 1) / 2)
#define BARNDOORSLIDE_VERT_LINE_NUM     ((TRANS_SLIDE_VERT_LINE_NUM + 1) / 2)
static void _MApp_Photo_SlideShow_Slide(EN_PHOTO_SLIDE_SHOW_EFFECT eType)
{
    GEBitBltInfo stBitbltInfo;
    GEPitBaseInfo stPitBaseInfo;
    S16 s16StepIdx;
    S16 s16SrcStartX[4], s16SrcEndX[4], s16SrcStartY[4], s16SrcEndY[4];
    S16 s16DstStartX[4], s16DstEndX[4], s16DstStartY[4], s16DstEndY[4];
    S16 s16SrcStartIncX[4], s16SrcEndIncX[4], s16SrcStartIncY[4], s16SrcEndIncY[4];
    S16 s16DstStartIncX[4], s16DstEndIncX[4], s16DstStartIncY[4], s16DstEndIncY[4];
    U32 u32Delayms;
    U16 u8RectIdx, u8RectNum;
    U16 i;

    stPitBaseInfo.sb_pit = PHOTO_ADJUSTED_PANEL_WIDTH * 2;
    stPitBaseInfo.sb_base = PHOTO_DISPLAY_SRC_BUFFER_ADDR;          // the address is referring to original image

    stPitBaseInfo.db_pit = PHOTO_ADJUSTED_PANEL_WIDTH * 2;    // 2 bytes per pixel
    stPitBaseInfo.db_base = PHOTO_DISPLAY_BUFFER_ADDR;

    stBitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;
    stBitbltInfo.BmpFlag = GFXDRAW_FLAG_DEFAULT;
    stBitbltInfo.dst_fm = GFX_FMT_YUV422;
    stBitbltInfo.src_fm = GFX_FMT_YUV422;
    msAPI_OSD_SetClipWindow(0, 0, PHOTO_ADJUSTED_PANEL_WIDTH, PANEL_HEIGHT);
    stBitbltInfo.BitbltCoordinate.direction = 0;    // TODO: what's this?
    msAPI_GE_SetNearestMode(TRUE);
    msAPI_GE_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_PC, GFX_YUV_OUT_255, GFX_YUV_IN_255, GFX_YUV_YUYV, GFX_YUV_YUYV);

    switch(eType)
    {
    case E_SLIDE_SHOW_EFFECT_BARSLIDE_LEFT2RIGHT:
        s16SrcStartX[0] = PHOTO_ADJUSTED_PANEL_WIDTH - TRANS_SLIDE_HORZ_LINE_NUM;
        s16SrcStartY[0] = 0;
        s16SrcEndX[0] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16SrcEndY[0] = PANEL_HEIGHT;
        s16SrcStartIncX[0] = -TRANS_SLIDE_HORZ_LINE_NUM;
        s16SrcStartIncY[0] = 0;
        s16SrcEndIncX[0] = 0;
        s16SrcEndIncY[0] = 0;

        s16DstStartX[0] = 0;
        s16DstStartY[0] = 0;
        s16DstEndX[0] = TRANS_SLIDE_HORZ_LINE_NUM;
        s16DstEndY[0] = PANEL_HEIGHT;
        s16DstStartIncX[0] = 0;
        s16DstStartIncY[0] = 0;
        s16DstEndIncX[0] = TRANS_SLIDE_HORZ_LINE_NUM;
        s16DstEndIncY[0] = 0;

        u8RectNum = 1;
        break;

    case E_SLIDE_SHOW_EFFECT_BARSLIDE_RIGHT2LEFT:
        s16SrcStartX[0] = 0;
        s16SrcStartY[0] = 0;
        s16SrcEndX[0] = TRANS_SLIDE_HORZ_LINE_NUM;
        s16SrcEndY[0] = PANEL_HEIGHT;
        s16SrcStartIncX[0] = 0;
        s16SrcStartIncY[0] = 0;
        s16SrcEndIncX[0] = TRANS_SLIDE_HORZ_LINE_NUM;
        s16SrcEndIncY[0] = 0;

        s16DstStartX[0] = PHOTO_ADJUSTED_PANEL_WIDTH - TRANS_SLIDE_HORZ_LINE_NUM;
        s16DstStartY[0] = 0;
        s16DstEndX[0] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16DstEndY[0] = PANEL_HEIGHT;
        s16DstStartIncX[0] = -TRANS_SLIDE_HORZ_LINE_NUM;
        s16DstStartIncY[0] = 0;
        s16DstEndIncX[0] = 0;
        s16DstEndIncY[0] = 0;

        u8RectNum = 1;
        break;

    case E_SLIDE_SHOW_EFFECT_BARSLIDE_TOP2BOTTOM:
        s16SrcStartX[0] = 0;
        s16SrcStartY[0] = PANEL_HEIGHT - TRANS_SLIDE_VERT_LINE_NUM;
        s16SrcEndX[0] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16SrcEndY[0] = PANEL_HEIGHT;
        s16SrcStartIncX[0] = 0;
        s16SrcStartIncY[0] = -TRANS_SLIDE_VERT_LINE_NUM;
        s16SrcEndIncX[0] = 0;
        s16SrcEndIncY[0] = 0;

        s16DstStartX[0] = 0;
        s16DstStartY[0] = 0;
        s16DstEndX[0] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16DstEndY[0] = TRANS_SLIDE_VERT_LINE_NUM;
        s16DstStartIncX[0] = 0;
        s16DstStartIncY[0] = 0;
        s16DstEndIncX[0] = 0;
        s16DstEndIncY[0] = TRANS_SLIDE_VERT_LINE_NUM;

        u8RectNum = 1;
        break;

    case E_SLIDE_SHOW_EFFECT_BARSLIDE_BOTTOM2TOP:
        s16SrcStartX[0] = 0;
        s16SrcStartY[0] = 0;
        s16SrcEndX[0] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16SrcEndY[0] = TRANS_SLIDE_VERT_LINE_NUM;
        s16SrcStartIncX[0] = 0;
        s16SrcStartIncY[0] = 0;
        s16SrcEndIncX[0] = 0;
        s16SrcEndIncY[0] = TRANS_SLIDE_VERT_LINE_NUM;

        s16DstStartX[0] = 0;
        s16DstStartY[0] = PANEL_HEIGHT - TRANS_SLIDE_VERT_LINE_NUM;
        s16DstEndX[0] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16DstEndY[0] = PANEL_HEIGHT;
        s16DstStartIncX[0] = 0;
        s16DstStartIncY[0] = -TRANS_SLIDE_VERT_LINE_NUM;
        s16DstEndIncX[0] = 0;
        s16DstEndIncY[0] = 0;

        u8RectNum = 1;
        break;

    case E_SLIDE_SHOW_EFFECT_BOXSLIDE_TOPLEFT:
        s16SrcStartX[0] = PHOTO_ADJUSTED_PANEL_WIDTH - TRANS_SLIDE_HORZ_LINE_NUM;
        s16SrcStartY[0] = PANEL_HEIGHT - TRANS_SLIDE_VERT_LINE_NUM;
        s16SrcEndX[0] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16SrcEndY[0] = PANEL_HEIGHT;
        s16SrcStartIncX[0] = -TRANS_SLIDE_HORZ_LINE_NUM;
        s16SrcStartIncY[0] = -TRANS_SLIDE_VERT_LINE_NUM;
        s16SrcEndIncX[0] = 0;
        s16SrcEndIncY[0] = 0;

        s16DstStartX[0] = 0;
        s16DstStartY[0] = 0;
        s16DstEndX[0] = TRANS_SLIDE_HORZ_LINE_NUM;
        s16DstEndY[0] = TRANS_SLIDE_VERT_LINE_NUM;
        s16DstStartIncX[0] = 0;
        s16DstStartIncY[0] = 0;
        s16DstEndIncX[0] = TRANS_SLIDE_HORZ_LINE_NUM;
        s16DstEndIncY[0] = TRANS_SLIDE_VERT_LINE_NUM;

        u8RectNum = 1;
        break;

    case E_SLIDE_SHOW_EFFECT_BOXSLIDE_TOPRIGHT:
        s16SrcStartX[0] = 0;
        s16SrcStartY[0] = PANEL_HEIGHT - TRANS_SLIDE_VERT_LINE_NUM;
        s16SrcEndX[0] = TRANS_SLIDE_HORZ_LINE_NUM;
        s16SrcEndY[0] = PANEL_HEIGHT;
        s16SrcStartIncX[0] = 0;
        s16SrcStartIncY[0] = -TRANS_SLIDE_VERT_LINE_NUM;
        s16SrcEndIncX[0] = TRANS_SLIDE_HORZ_LINE_NUM;
        s16SrcEndIncY[0] = 0;

        s16DstStartX[0] = PHOTO_ADJUSTED_PANEL_WIDTH - TRANS_SLIDE_HORZ_LINE_NUM;
        s16DstStartY[0] = 0;
        s16DstEndX[0] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16DstEndY[0] = TRANS_SLIDE_VERT_LINE_NUM;
        s16DstStartIncX[0] = -TRANS_SLIDE_HORZ_LINE_NUM;
        s16DstStartIncY[0] = 0;
        s16DstEndIncX[0] = 0;
        s16DstEndIncY[0] = TRANS_SLIDE_VERT_LINE_NUM;

        u8RectNum = 1;
        break;

    case E_SLIDE_SHOW_EFFECT_BOXSLIDE_BOTTOMLEFT:
        s16SrcStartX[0] = PHOTO_ADJUSTED_PANEL_WIDTH - TRANS_SLIDE_HORZ_LINE_NUM;
        s16SrcStartY[0] = 0;
        s16SrcEndX[0] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16SrcEndY[0] = TRANS_SLIDE_VERT_LINE_NUM;
        s16SrcStartIncX[0] = -TRANS_SLIDE_HORZ_LINE_NUM;
        s16SrcStartIncY[0] = 0;
        s16SrcEndIncX[0] = 0;
        s16SrcEndIncY[0] = TRANS_SLIDE_VERT_LINE_NUM;

        s16DstStartX[0] = 0;
        s16DstStartY[0] = PANEL_HEIGHT - TRANS_SLIDE_VERT_LINE_NUM;
        s16DstEndX[0] = TRANS_SLIDE_HORZ_LINE_NUM;
        s16DstEndY[0] = PANEL_HEIGHT;
        s16DstStartIncX[0] = 0;
        s16DstStartIncY[0] = -TRANS_SLIDE_VERT_LINE_NUM;
        s16DstEndIncX[0] = TRANS_SLIDE_HORZ_LINE_NUM;
        s16DstEndIncY[0] = 0;

        u8RectNum = 1;
        break;

    case E_SLIDE_SHOW_EFFECT_BOXSLIDE_BOTTOMRIGHT:
        s16SrcStartX[0] = 0;
        s16SrcStartY[0] = 0;
        s16SrcEndX[0] = TRANS_SLIDE_HORZ_LINE_NUM;
        s16SrcEndY[0] = TRANS_SLIDE_VERT_LINE_NUM;
        s16SrcStartIncX[0] = 0;
        s16SrcStartIncY[0] = 0;
        s16SrcEndIncX[0] = TRANS_SLIDE_HORZ_LINE_NUM;
        s16SrcEndIncY[0] = TRANS_SLIDE_VERT_LINE_NUM;

        s16DstStartX[0] = PHOTO_ADJUSTED_PANEL_WIDTH - TRANS_SLIDE_HORZ_LINE_NUM;
        s16DstStartY[0] = PANEL_HEIGHT - TRANS_SLIDE_VERT_LINE_NUM;
        s16DstEndX[0] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16DstEndY[0] = PANEL_HEIGHT;
        s16DstStartIncX[0] = -TRANS_SLIDE_HORZ_LINE_NUM;
        s16DstStartIncY[0] = -TRANS_SLIDE_VERT_LINE_NUM;
        s16DstEndIncX[0] = 0;
        s16DstEndIncY[0] = 0;

        u8RectNum = 1;
        break;

    case E_SLIDE_SHOW_EFFECT_BARNDOORSLIDE_HORIZONTAL_OPEN:
        s16SrcStartX[0] = 0;
        s16SrcStartY[0] = 0;
        s16SrcEndX[0] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16SrcEndY[0] = BARNDOORSLIDE_VERT_LINE_NUM;
        s16SrcStartIncX[0] = 0;
        s16SrcStartIncY[0] = 0;
        s16SrcEndIncX[0] = 0;
        s16SrcEndIncY[0] = BARNDOORSLIDE_VERT_LINE_NUM;

        s16DstStartX[0] = 0;
        s16DstStartY[0] = PANEL_HEIGHT / 2 - BARNDOORSLIDE_VERT_LINE_NUM;
        s16DstEndX[0] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16DstEndY[0] = PANEL_HEIGHT / 2;
        s16DstStartIncX[0] = 0;
        s16DstStartIncY[0] = -BARNDOORSLIDE_VERT_LINE_NUM;
        s16DstEndIncX[0] = 0;
        s16DstEndIncY[0] = 0;

        s16SrcStartX[1] = 0;
        s16SrcStartY[1] = PANEL_HEIGHT - BARNDOORSLIDE_VERT_LINE_NUM;
        s16SrcEndX[1] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16SrcEndY[1] = PANEL_HEIGHT;
        s16SrcStartIncX[1] = 0;
        s16SrcStartIncY[1] = -BARNDOORSLIDE_VERT_LINE_NUM;
        s16SrcEndIncX[1] = 0;
        s16SrcEndIncY[1] = 0;

        s16DstStartX[1] = 0;
        s16DstStartY[1] = PANEL_HEIGHT / 2;
        s16DstEndX[1] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16DstEndY[1] = PANEL_HEIGHT / 2 + BARNDOORSLIDE_VERT_LINE_NUM;
        s16DstStartIncX[1] = 0;
        s16DstStartIncY[1] = 0;
        s16DstEndIncX[1] = 0;
        s16DstEndIncY[1] = BARNDOORSLIDE_VERT_LINE_NUM;

        u8RectNum = 2;
        break;

    case E_SLIDE_SHOW_EFFECT_BARNDOORSLIDE_HORIZONTAL_CLOSE:
        s16SrcStartX[0] = 0;
        s16SrcStartY[0] = PANEL_HEIGHT / 2 - BARNDOORSLIDE_VERT_LINE_NUM;
        s16SrcEndX[0] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16SrcEndY[0] = PANEL_HEIGHT / 2;
        s16SrcStartIncX[0] = 0;
        s16SrcStartIncY[0] = -BARNDOORSLIDE_VERT_LINE_NUM;
        s16SrcEndIncX[0] = 0;
        s16SrcEndIncY[0] = 0;

        s16DstStartX[0] = 0;
        s16DstStartY[0] = 0;
        s16DstEndX[0] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16DstEndY[0] = BARNDOORSLIDE_VERT_LINE_NUM;
        s16DstStartIncX[0] = 0;
        s16DstStartIncY[0] = 0;
        s16DstEndIncX[0] = 0;
        s16DstEndIncY[0] = BARNDOORSLIDE_VERT_LINE_NUM;

        s16SrcStartX[1] = 0;
        s16SrcStartY[1] = PANEL_HEIGHT / 2;
        s16SrcEndX[1] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16SrcEndY[1] = PANEL_HEIGHT / 2 + BARNDOORSLIDE_VERT_LINE_NUM;
        s16SrcStartIncX[1] = 0;
        s16SrcStartIncY[1] = 0;
        s16SrcEndIncX[1] = 0;
        s16SrcEndIncY[1] = BARNDOORSLIDE_VERT_LINE_NUM;

        s16DstStartX[1] = 0;
        s16DstStartY[1] = PANEL_HEIGHT - BARNDOORSLIDE_VERT_LINE_NUM;
        s16DstEndX[1] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16DstEndY[1] = PANEL_HEIGHT;
        s16DstStartIncX[1] = 0;
        s16DstStartIncY[1] = -BARNDOORSLIDE_VERT_LINE_NUM;
        s16DstEndIncX[1] = 0;
        s16DstEndIncY[1] = 0;

        u8RectNum = 2;
        break;

    case E_SLIDE_SHOW_EFFECT_BARNDOORSLIDE_VERTICAL_OPEN:
        s16SrcStartX[0] = 0;
        s16SrcStartY[0] = 0;
        s16SrcEndX[0] = BARNDOORSLIDE_HORZ_LINE_NUM;
        s16SrcEndY[0] = PANEL_WIDTH;
        s16SrcStartIncX[0] = 0;
        s16SrcStartIncY[0] = 0;
        s16SrcEndIncX[0] = BARNDOORSLIDE_HORZ_LINE_NUM;
        s16SrcEndIncY[0] = 0;

        s16DstStartX[0] = PHOTO_ADJUSTED_PANEL_WIDTH / 2 - BARNDOORSLIDE_HORZ_LINE_NUM;
        s16DstStartY[0] = 0;
        s16DstEndX[0] = PHOTO_ADJUSTED_PANEL_WIDTH / 2;
        s16DstEndY[0] = PANEL_HEIGHT;
        s16DstStartIncX[0] = -BARNDOORSLIDE_HORZ_LINE_NUM;
        s16DstStartIncY[0] = 0;
        s16DstEndIncX[0] = 0;
        s16DstEndIncY[0] = 0;

        s16SrcStartX[1] = PHOTO_ADJUSTED_PANEL_WIDTH - BARNDOORSLIDE_HORZ_LINE_NUM;
        s16SrcStartY[1] = 0;
        s16SrcEndX[1] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16SrcEndY[1] = PANEL_WIDTH;
        s16SrcStartIncX[1] = -BARNDOORSLIDE_HORZ_LINE_NUM;
        s16SrcStartIncY[1] = 0;
        s16SrcEndIncX[1] = 0;
        s16SrcEndIncY[1] = 0;

        s16DstStartX[1] = PHOTO_ADJUSTED_PANEL_WIDTH / 2;
        s16DstStartY[1] = 0;
        s16DstEndX[1] = PHOTO_ADJUSTED_PANEL_WIDTH / 2 + BARNDOORSLIDE_HORZ_LINE_NUM;
        s16DstEndY[1] = PANEL_HEIGHT;
        s16DstStartIncX[1] = 0;
        s16DstStartIncY[1] = 0;
        s16DstEndIncX[1] = BARNDOORSLIDE_HORZ_LINE_NUM;
        s16DstEndIncY[1] = 0;

        u8RectNum = 2;
        break;

    case E_SLIDE_SHOW_EFFECT_BARNDOORSLIDE_VERTICAL_CLOSE:
        s16SrcStartX[0] = PHOTO_ADJUSTED_PANEL_WIDTH / 2 - BARNDOORSLIDE_HORZ_LINE_NUM;
        s16SrcStartY[0] = 0;
        s16SrcEndX[0] = PHOTO_ADJUSTED_PANEL_WIDTH / 2;
        s16SrcEndY[0] = PANEL_HEIGHT;
        s16SrcStartIncX[0] = -BARNDOORSLIDE_HORZ_LINE_NUM;
        s16SrcStartIncY[0] = 0;
        s16SrcEndIncX[0] = 0;
        s16SrcEndIncY[0] = 0;

        s16DstStartX[0] = 0;
        s16DstStartY[0] = 0;
        s16DstEndX[0] = BARNDOORSLIDE_HORZ_LINE_NUM;
        s16DstEndY[0] = PANEL_WIDTH;
        s16DstStartIncX[0] = 0;
        s16DstStartIncY[0] = 0;
        s16DstEndIncX[0] = BARNDOORSLIDE_HORZ_LINE_NUM;
        s16DstEndIncY[0] = 0;

        s16SrcStartX[1] = PHOTO_ADJUSTED_PANEL_WIDTH / 2;
        s16SrcStartY[1] = 0;
        s16SrcEndX[1] = PHOTO_ADJUSTED_PANEL_WIDTH / 2 + BARNDOORSLIDE_HORZ_LINE_NUM;
        s16SrcEndY[1] = PANEL_HEIGHT;
        s16SrcStartIncX[1] = 0;
        s16SrcStartIncY[1] = 0;
        s16SrcEndIncX[1] = BARNDOORSLIDE_HORZ_LINE_NUM;
        s16SrcEndIncY[1] = 0;

        s16DstStartX[1] = PHOTO_ADJUSTED_PANEL_WIDTH - BARNDOORSLIDE_HORZ_LINE_NUM;
        s16DstStartY[1] = 0;
        s16DstEndX[1] = PHOTO_ADJUSTED_PANEL_WIDTH;
        s16DstEndY[1] = PANEL_WIDTH;
        s16DstStartIncX[1] = -BARNDOORSLIDE_HORZ_LINE_NUM;
        s16DstStartIncY[1] = 0;
        s16DstEndIncX[1] = 0;
        s16DstEndIncY[1] = 0;

        u8RectNum = 2;
        break;

    case E_SLIDE_SHOW_EFFECT_4BARSLIDE_HORIZONTAL_FROM_TOP:
        for(i=0; i<4; i++)
        {
            s16SrcStartX[i] = 0;
            s16SrcStartY[i] = PANEL_HEIGHT * (i+1) / 4 - X4BARSLIDE_VERT_LINE_NUM;
            s16SrcEndX[i] = PHOTO_ADJUSTED_PANEL_WIDTH;
            s16SrcEndY[i] = PANEL_HEIGHT * (i+1) / 4;
            s16SrcStartIncX[i] = 0;
            s16SrcStartIncY[i] = -X4BARSLIDE_VERT_LINE_NUM;
            s16SrcEndIncX[i] = 0;
            s16SrcEndIncY[i] = 0;

            s16DstStartX[i] = 0;
            s16DstStartY[i] = PANEL_HEIGHT * i / 4;
            s16DstEndX[i] = PHOTO_ADJUSTED_PANEL_WIDTH;
            s16DstEndY[i] = PANEL_HEIGHT * i / 4 + i * X4BARSLIDE_VERT_LINE_NUM;
            s16DstStartIncX[i] = 0;
            s16DstStartIncY[i] = 0;
            s16DstEndIncX[i] = 0;
            s16DstEndIncY[i] = X4BARSLIDE_VERT_LINE_NUM;
        }
        u8RectNum = 4;
        break;

    case E_SLIDE_SHOW_EFFECT_4BARSLIDE_HORIZONTAL_FROM_BOTTOM:
        for(i=0; i<4; i++)
        {
            s16SrcStartX[i] = 0;
            s16SrcStartY[i] = PANEL_HEIGHT * i / 4;
            s16SrcEndX[i] = PHOTO_ADJUSTED_PANEL_WIDTH;
            s16SrcEndY[i] = PANEL_HEIGHT * i / 4 + i * X4BARSLIDE_VERT_LINE_NUM;
            s16SrcStartIncX[i] = 0;
            s16SrcStartIncY[i] = 0;
            s16SrcEndIncX[i] = 0;
            s16SrcEndIncY[i] = X4BARSLIDE_VERT_LINE_NUM;

            s16DstStartX[i] = 0;
            s16DstStartY[i] = PANEL_HEIGHT * (i+1) / 4 - X4BARSLIDE_VERT_LINE_NUM;
            s16DstEndX[i] = PHOTO_ADJUSTED_PANEL_WIDTH;
            s16DstEndY[i] = PANEL_HEIGHT * (i+1) / 4;
            s16DstStartIncX[i] = 0;
            s16DstStartIncY[i] = -X4BARSLIDE_VERT_LINE_NUM;
            s16DstEndIncX[i] = 0;
            s16DstEndIncY[i] = 0;
        }
        u8RectNum = 4;
        break;

    case E_SLIDE_SHOW_EFFECT_4BARSLIDE_VERTICAL_FROM_LEFT:
        for(i=0; i<4; i++)
        {
            s16SrcStartX[i] = PHOTO_ADJUSTED_PANEL_WIDTH * (i+1) / 4 - X4BARSLIDE_HORZ_LINE_NUM;
            s16SrcStartY[i] = 0;
            s16SrcEndX[i] = PHOTO_ADJUSTED_PANEL_WIDTH * (i+1) / 4;
            s16SrcEndY[i] = PANEL_HEIGHT;
            s16SrcStartIncX[i] = -X4BARSLIDE_HORZ_LINE_NUM;
            s16SrcStartIncY[i] = 0;
            s16SrcEndIncX[i] = 0;
            s16SrcEndIncY[i] = 0;

            s16DstStartX[i] = PHOTO_ADJUSTED_PANEL_WIDTH * i / 4;
            s16DstStartY[i] = 0;
            s16DstEndX[i] = PHOTO_ADJUSTED_PANEL_WIDTH * i / 4 + i * X4BARSLIDE_HORZ_LINE_NUM;
            s16DstEndY[i] = PANEL_HEIGHT;
            s16DstStartIncX[i] = 0;
            s16DstStartIncY[i] = 0;
            s16DstEndIncX[i] = X4BARSLIDE_HORZ_LINE_NUM;
            s16DstEndIncY[i] = 0;
        }
        u8RectNum = 4;
        break;

    case E_SLIDE_SHOW_EFFECT_4BARSLIDE_VERTICAL_FROM_RIGHT:
        for(i=0; i<4; i++)
        {
            s16SrcStartX[i] = PHOTO_ADJUSTED_PANEL_WIDTH * i / 4;
            s16SrcStartY[i] = 0;
            s16SrcEndX[i] = PHOTO_ADJUSTED_PANEL_WIDTH * i / 4 + i * X4BARSLIDE_HORZ_LINE_NUM;
            s16SrcEndY[i] = PANEL_HEIGHT;
            s16SrcStartIncX[i] = 0;
            s16SrcStartIncY[i] = 0;
            s16SrcEndIncX[i] = X4BARSLIDE_HORZ_LINE_NUM;
            s16SrcEndIncY[i] = 0;

            s16DstStartX[i] = PHOTO_ADJUSTED_PANEL_WIDTH * (i+1) / 4 - X4BARSLIDE_HORZ_LINE_NUM;
            s16DstStartY[i] = 0;
            s16DstEndX[i] = PHOTO_ADJUSTED_PANEL_WIDTH * (i+1) / 4;
            s16DstEndY[i] = PANEL_HEIGHT;
            s16DstStartIncX[i] = -X4BARSLIDE_HORZ_LINE_NUM;
            s16DstStartIncY[i] = 0;
            s16DstEndIncX[i] = 0;
            s16DstEndIncY[i] = 0;
        }
        u8RectNum = 4;
        break;

    default:
        return;
    }

    u32Delayms = PHOTO_TRANS_EFFECT_DELAY_MS / (PHOTO_TRANS_EFFECT_SLIDE_STEPS-1);

    for(s16StepIdx=0;s16StepIdx<PHOTO_TRANS_EFFECT_SLIDE_STEPS-1;s16StepIdx++)
    {
        U32 u32StartTimeMs, u32ElapseTime, u32FreezeStartMs;
        u32StartTimeMs = msAPI_Timer_GetTime0();
        MApi_XC_FreezeImg(TRUE, MAIN_WINDOW);

#if ENABLE_SPEED_MUSIC_BACKGROUND_PLAY
        u32FreezeStartMs = msAPI_Timer_GetTime0();
        while(msAPI_Timer_DiffTimeFromNow(u32FreezeStartMs) < PHOTO_TRANS_EFFECT_SLIDE_UNIT_DELAY)
        {
            MApp_Music_InputBackGroundMusicData();
        }
#else
        msAPI_Timer_Delayms(PHOTO_TRANS_EFFECT_SLIDE_UNIT_DELAY);
#endif
        for(u8RectIdx = 0; u8RectIdx < u8RectNum; u8RectIdx++)
        {
            stBitbltInfo.BitbltCoordinate.v2_x = s16SrcStartX[u8RectIdx];
            stBitbltInfo.BitbltCoordinate.v2_y = s16SrcStartY[u8RectIdx];
            stBitbltInfo.src_width = s16SrcEndX[u8RectIdx] - s16SrcStartX[u8RectIdx];
            stBitbltInfo.src_height = s16SrcEndY[u8RectIdx] - s16SrcStartY[u8RectIdx];
            stBitbltInfo.BitbltCoordinate.v0_x = s16DstStartX[u8RectIdx];
            stBitbltInfo.BitbltCoordinate.v0_y = s16DstStartY[u8RectIdx];
            stBitbltInfo.BitbltCoordinate.width = stBitbltInfo.src_width;
            stBitbltInfo.BitbltCoordinate.height = stBitbltInfo.src_height;
#if 0
            printf("-- src: %d %d %d %d, dst: %d %d %d %d\n",
                        stBitbltInfo.BitbltCoordinate.v2_x,
                        stBitbltInfo.BitbltCoordinate.v2_y,
                        stBitbltInfo.src_width,
                        stBitbltInfo.src_height,
                        stBitbltInfo.BitbltCoordinate.v0_x,
                        stBitbltInfo.BitbltCoordinate.v0_y,
                        stBitbltInfo.BitbltCoordinate.width,
                        stBitbltInfo.BitbltCoordinate.height
                        );
#endif
            // output image to destination buffer
            if(s16SrcEndX[u8RectIdx] > s16SrcStartX[u8RectIdx] &&
               s16SrcEndY[u8RectIdx] > s16SrcStartY[u8RectIdx])
            {
                msAPI_GE_BitBlt(&stBitbltInfo, &stPitBaseInfo);
                // after BitBlt, flush cmd
                MApi_GFX_FlushQueue();
            }

            s16SrcStartX[u8RectIdx] = s16SrcStartX[u8RectIdx]+s16SrcStartIncX[u8RectIdx];
            s16SrcStartX[u8RectIdx] = (s16SrcStartX[u8RectIdx] < 0) ? 0 : s16SrcStartX[u8RectIdx];
            s16SrcStartX[u8RectIdx] = (s16SrcStartX[u8RectIdx] > PHOTO_ADJUSTED_PANEL_WIDTH) ?
                              PHOTO_ADJUSTED_PANEL_WIDTH : s16SrcStartX[u8RectIdx];

            s16SrcEndX[u8RectIdx] = s16SrcEndX[u8RectIdx]+s16SrcEndIncX[u8RectIdx];
            s16SrcEndX[u8RectIdx] = (s16SrcEndX[u8RectIdx] < 0) ? 0 : s16SrcEndX[u8RectIdx];
            s16SrcEndX[u8RectIdx] = (s16SrcEndX[u8RectIdx] > PHOTO_ADJUSTED_PANEL_WIDTH) ?
                              PHOTO_ADJUSTED_PANEL_WIDTH : s16SrcEndX[u8RectIdx];

            s16SrcStartY[u8RectIdx] = s16SrcStartY[u8RectIdx]+s16SrcStartIncY[u8RectIdx];
            s16SrcStartY[u8RectIdx] = (s16SrcStartY[u8RectIdx] < 0) ? 0 : s16SrcStartY[u8RectIdx];
            s16SrcStartY[u8RectIdx] = (s16SrcStartY[u8RectIdx] > PHOTO_ADJUSTED_PANEL_WIDTH) ?
                              PHOTO_ADJUSTED_PANEL_WIDTH : s16SrcStartY[u8RectIdx];

            s16SrcEndY[u8RectIdx] = s16SrcEndY[u8RectIdx]+s16SrcEndIncY[u8RectIdx];
            s16SrcEndY[u8RectIdx] = (s16SrcEndY[u8RectIdx] < 0) ? 0 : s16SrcEndY[u8RectIdx];
            s16SrcEndY[u8RectIdx] = (s16SrcEndY[u8RectIdx] > PHOTO_ADJUSTED_PANEL_WIDTH) ?
                              PHOTO_ADJUSTED_PANEL_WIDTH : s16SrcEndY[u8RectIdx];

            s16DstStartX[u8RectIdx] = s16DstStartX[u8RectIdx]+s16DstStartIncX[u8RectIdx];
            s16DstStartX[u8RectIdx] = (s16DstStartX[u8RectIdx] < 0) ? 0 : s16DstStartX[u8RectIdx];
            s16DstStartX[u8RectIdx] = (s16DstStartX[u8RectIdx] > PHOTO_ADJUSTED_PANEL_WIDTH) ?
                              PHOTO_ADJUSTED_PANEL_WIDTH : s16DstStartX[u8RectIdx];

            s16DstEndX[u8RectIdx] = s16DstEndX[u8RectIdx]+s16DstEndIncX[u8RectIdx];
            s16DstEndX[u8RectIdx] = (s16DstEndX[u8RectIdx] < 0) ? 0 : s16DstEndX[u8RectIdx];
            s16DstEndX[u8RectIdx] = (s16DstEndX[u8RectIdx] > PHOTO_ADJUSTED_PANEL_WIDTH) ?
                              PHOTO_ADJUSTED_PANEL_WIDTH : s16DstEndX[u8RectIdx];

            s16DstStartY[u8RectIdx] = s16DstStartY[u8RectIdx]+s16DstStartIncY[u8RectIdx];
            s16DstStartY[u8RectIdx] = (s16DstStartY[u8RectIdx] < 0) ? 0 : s16DstStartY[u8RectIdx];
            s16DstStartY[u8RectIdx] = (s16DstStartY[u8RectIdx] > PHOTO_ADJUSTED_PANEL_WIDTH) ?
                              PHOTO_ADJUSTED_PANEL_WIDTH : s16DstStartY[u8RectIdx];

            s16DstEndY[u8RectIdx] = s16DstEndY[u8RectIdx]+s16DstEndIncY[u8RectIdx];
            s16DstEndY[u8RectIdx] = (s16DstEndY[u8RectIdx] < 0) ? 0 : s16DstEndY[u8RectIdx];
            s16DstEndY[u8RectIdx] = (s16DstEndY[u8RectIdx] > PHOTO_ADJUSTED_PANEL_WIDTH) ?
                              PHOTO_ADJUSTED_PANEL_WIDTH : s16DstEndY[u8RectIdx];
        }
        //        mvideo_sc_wait_output_vsync(2, 50);
        MApi_XC_FreezeImg(FALSE, MAIN_WINDOW);
#if ENABLE_SPEED_MUSIC_BACKGROUND_PLAY
        u32FreezeStartMs = msAPI_Timer_GetTime0();
        while(msAPI_Timer_DiffTimeFromNow(u32FreezeStartMs) < PHOTO_TRANS_EFFECT_SLIDE_UNIT_DELAY)
        {
            MApp_Music_InputBackGroundMusicData();
        }
#else
        msAPI_Timer_Delayms(PHOTO_TRANS_EFFECT_SLIDE_UNIT_DELAY);
#endif
        msAPI_Timer_ResetWDT();

        u32ElapseTime = msAPI_Timer_DiffTimeFromNow(u32StartTimeMs);
        if(u32ElapseTime < u32Delayms)
        {
            msAPI_Timer_Delayms(u32Delayms - u32ElapseTime);
        }
    }

    stBitbltInfo.src_width = PHOTO_ADJUSTED_PANEL_WIDTH;
    stBitbltInfo.src_height = PANEL_HEIGHT;
    stBitbltInfo.BitbltCoordinate.v2_x = 0;
    stBitbltInfo.BitbltCoordinate.v2_y = 0;
    stBitbltInfo.BitbltCoordinate.v0_x = 0;
    stBitbltInfo.BitbltCoordinate.v0_y = 0;
    stBitbltInfo.BitbltCoordinate.width = PHOTO_ADJUSTED_PANEL_WIDTH;
    stBitbltInfo.BitbltCoordinate.height = PANEL_HEIGHT;
    MApi_XC_FreezeImg(TRUE, MAIN_WINDOW);

    msAPI_Timer_Delayms(40);
    msAPI_GE_BitBlt(&stBitbltInfo, &stPitBaseInfo);
    // after BitBlt, flush cmd
    MApi_GFX_FlushQueue();

    MVOP_Timing stMVOPTiming;
    MDrv_MVOP_GetOutputTiming(&stMVOPTiming);
    MApi_XC_WaitOutputVSync(2, (1000/stMVOPTiming.u8Framerate)*2, MAIN_WINDOW);

    MApi_XC_FreezeImg(FALSE, MAIN_WINDOW);
}
#endif  // #if (ENABLE_PHOTO_TRANS_EFFECT_SLIDE)

#if (ENABLE_PHOTO_TRANS_EFFECT_FADE)
static void _MApp_Photo_SlideShow_Fade(EN_PHOTO_SLIDE_SHOW_EFFECT eType)
{
    UNUSED(eType);
    GEBitBltInfo stBitbltInfo;
    GEPitBaseInfo stPitBaseInfo;

    stPitBaseInfo.sb_pit = PHOTO_ADJUSTED_PANEL_WIDTH * 2;
    stPitBaseInfo.sb_base = PHOTO_DISPLAY_SRC_BUFFER_ADDR;      // the address is referring to original image

    stPitBaseInfo.db_pit = PHOTO_ADJUSTED_PANEL_WIDTH * 2;         // 2 bytes per pixel
    stPitBaseInfo.db_base = PHOTO_DISPLAY_BUFFER_ADDR;

    stBitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;
    stBitbltInfo.BmpFlag = GFXDRAW_FLAG_DEFAULT;
    stBitbltInfo.dst_fm = GFX_FMT_YUV422;
    stBitbltInfo.src_fm = GFX_FMT_YUV422;

    stBitbltInfo.src_width = PHOTO_ADJUSTED_PANEL_WIDTH;
    stBitbltInfo.src_height = PANEL_HEIGHT;

    stBitbltInfo.BitbltCoordinate.v2_x = 0;
    stBitbltInfo.BitbltCoordinate.v2_y = 0;

    stBitbltInfo.BitbltCoordinate.direction = 0;    // TODO: what's this?

    stBitbltInfo.BitbltCoordinate.v0_x = 0;
    stBitbltInfo.BitbltCoordinate.v0_y = 0;
    stBitbltInfo.BitbltCoordinate.width = PHOTO_ADJUSTED_PANEL_WIDTH;
    stBitbltInfo.BitbltCoordinate.height = PANEL_HEIGHT;
    msAPI_OSD_SetClipWindow(0, 0, PHOTO_ADJUSTED_PANEL_WIDTH, PANEL_HEIGHT);
    msAPI_GE_SetNearestMode(TRUE);
    msAPI_GE_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_PC, GFX_YUV_OUT_255, GFX_YUV_IN_255, GFX_YUV_YUYV, GFX_YUV_YUYV);

    U16 i, u16AlphaIncreaseUnit = PHOTO_TRANS_EFFECT_FADE_ALPHA_INCREASE_UNIT;
    U8 u8Alpha, u8Coef=0;
    for(i=(u16AlphaIncreaseUnit-1);i<256;i+=u16AlphaIncreaseUnit)
    {
        if(u8Coef == 255)
        {
            u8Alpha = 255;
        }
        else
        {
            u8Alpha = 255*(i-u8Coef)/(255-u8Coef);
        }
        u8Coef = u8Alpha + u8Coef*(255-u8Alpha)/255;

        MApi_GFX_SetAlpha(TRUE, COEF_CONST, ABL_FROM_CONST, u8Alpha);

        // output image to destination buffer
        msAPI_GE_BitBlt(&stBitbltInfo, &stPitBaseInfo);
        // after BitBlt, flush cmd
        MApi_GFX_FlushQueue();
        msAPI_Timer_Delayms(PHOTO_TRANS_EFFECT_FADE_UNIT_DELAY*u16AlphaIncreaseUnit);

        msAPI_Timer_ResetWDT();
    #if ENABLE_SPEED_MUSIC_BACKGROUND_PLAY
        MApp_Music_InputBackGroundMusicData();
    #endif
        if(u8Alpha == 255)
        {
            break;
        }
    }
}
#endif  // #if (ENABLE_PHOTO_TRANS_EFFECT_FADE)
#endif  // #if PHOTO_SLIDE_SHOW_EFFECT

#if PHOTO_SLIDE_SHOW_EFFECT
BOOLEAN MApp_Photo_InitFullScreenDisplay(void)
{
    msAPI_GE_ClearFrameBufferByWord((U32)PHOTO_DISPLAY_BUFFER_ADDR,
           (PHOTO_ADJUSTED_PANEL_WIDTH * PANEL_HEIGHT * 2),
           0x80008000);

    // after clear frame buffer, flush cmd
    MApi_GFX_FlushQueue();

#if (MirrorEnable)
    MApp_MVOP_SetMirrorMode(ENABLE);
#endif

    bMPODisplayEnabled = FALSE;


    MApp_Scaler_Setup_FB(E_XC_FB_CASE_MM_PHOTO_FULL_DISP);


#if ENABLE_3D_PROCESS
    //for avoid see garbage in screen
    msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
  #if ENABLE_NEW_3D_FLOW
    MApp_Scaler_SetVideo3DMode(EN_3D_BYPASS);
  #else
    MApp_Scaler_SetVideo3DMode(MAPP_Scaler_Map3DFormatTo3DUserMode(E_XC_3D_INPUT_MODE_NONE));
  #endif
    msAPI_Scaler_SetBlueScreen(DISABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
#endif
    _MApp_Photo_SetScalarVOP2Display(
            0,
            0,
            PANEL_WIDTH,
            PANEL_HEIGHT,
            0,
            0,
            PANEL_WIDTH,
            PANEL_HEIGHT,
            PHOTO_DISPLAY_BUFFER_ADDR,
            PHOTO_ADJUSTED_PANEL_WIDTH,
            PANEL_HEIGHT);

    return TRUE;
}

#if (SHOW_PARTIALLY_DECODING_PHOTO)
BOOLEAN MApp_Photo_InitPreviewDisplay(void)
{
    U16 u16Factor = 1;

    // calculate x, y, width, height
    while (1)
    {
        if ((u16Factor * u16ViewWinWidth > PHOTO_ADJUSTED_PANEL_WIDTH)
                || (u16Factor * u16ViewWinHeight > PANEL_HEIGHT))
        {
            break;
        }

        if ((u16Factor * u16ViewWinWidth <= PHOTO_ADJUSTED_PANEL_WIDTH)
                && ((u16Factor + 1) * u16ViewWinWidth > PHOTO_ADJUSTED_PANEL_WIDTH))
        {
            break;
        }

        if ((u16Factor * u16ViewWinHeight <= PANEL_HEIGHT)
                && ((u16Factor + 1) * u16ViewWinHeight > PANEL_HEIGHT))
        {
            break;
        }

        u16Factor++;
    }

    m_u16PhotoPreviewWidth = (U16)PHOTO_ALIGNMENT(u16ViewWinWidth * u16Factor);
    m_u16PhotoPreviewHeight = u16ViewWinHeight * u16Factor;

    msAPI_GE_ClearFrameBufferByWord((U32)PHOTO_DISPLAY_BUFFER_ADDR,
           (m_u16PhotoPreviewWidth * m_u16PhotoPreviewHeight * 2),
           0x80008000);
    // after clear frame buffer, flush cmd
    MApi_GFX_FlushQueue();
    m_bFLG_PREVIEW = TRUE;

    bMPODisplayEnabled = FALSE;


    MApp_Scaler_Setup_FB(E_XC_FB_CASE_MM_PHOTO_PREVIEW);

#if (MirrorEnable)
    MApp_MVOP_SetMirrorMode(ENABLE);
#endif

    _MApp_Photo_SetScalarVOP2Display(
            0,  0, m_u16PhotoPreviewWidth, m_u16PhotoPreviewHeight,
            u16ViewWinX, u16ViewWinY, u16ViewWinWidth, u16ViewWinHeight,
            PHOTO_DISPLAY_BUFFER_ADDR,
            m_u16PhotoPreviewWidth, m_u16PhotoPreviewHeight);

    return TRUE;
}
#endif // #if (SHOW_PARTIALLY_DECODING_PHOTO)

static void _MApp_Photo_SlideShow(GFX_Buffer_Format eSrcColorFmt, SlideShowPhotoInfo *pPhotoInfo, EN_PHOTO_SLIDE_SHOW_EFFECT eEffect)
{
    EN_PHOTO_SLIDE_SHOW_EFFECT slideShowEffect;
    U8 u8Rand;
    GEBitBltInfo stBitbltInfo;
    GEPitBaseInfo stPitBaseInfo;
    U16 u16DstW, u16DstH;
    U32 u32DecodeOutputBuffAddr;

    m_enRotation = EN_PHOTO_ROTATE_0;
    m_enZooming = EN_PHOTO_ZOOM_1;
    m_s16PhotoOffsetX = 0;
    m_s16PhotoOffsetY = 0;

    if(eSrcColorFmt != GFX_FMT_YUV422 && eSrcColorFmt != GFX_FMT_ARGB8888 && eSrcColorFmt != GFX_FMT_ARGB1555)
    {
        __ASSERT(0);
        return;
    }

    if(MApp_Photo_GetInfo(E_PHOTO_INFO_FILE_FORMAT) == E_PHOTO_FILE_GIF)
    {
        if(stu32DisplayedFrameIndex != 0)
        {
            eEffect = E_SLIDE_SHOW_EFFECT_NORMAL;
        }

        if(MApp_Photo_GetInfo(E_PHOTO_INFO_SLOT_NUM) == 0)
        {
            PHOTO_DISP_MSG(printf("[Photo Display] gif slot num is zero.\n"));
            return;
        }

        u32DecodeOutputBuffAddr = PHOTO_OUTPUT_BUFFER_ADDR +
             stu32DisplayedFrameIndex%MApp_Photo_GetInfo(E_PHOTO_INFO_SLOT_NUM)*MApp_Photo_GetInfo(E_PHOTO_INFO_FRAME_SIZE);
    }
    else
    {
        u32DecodeOutputBuffAddr = PHOTO_OUTPUT_BUFFER_ADDR;
    }

    if(eSrcColorFmt == GFX_FMT_ARGB8888)
    {
        // color format transfer
        _MApp_Photo_Display_ColorFmtTransfer(
                pPhotoInfo->u16Pitch,
                pPhotoInfo->u16Height,
                u32DecodeOutputBuffAddr,
                GFX_FMT_ARGB8888,
                PHOTO_DISPLAY_SRC_BUFFER_ADDR,
                GFX_FMT_YUV422);

        // Copy converted image (in internal buffer) to decoder buffer.
        msAPI_MIU_Copy(
                PHOTO_DISPLAY_SRC_BUFFER_ADDR,
                u32DecodeOutputBuffAddr,
                (U32)2L * pPhotoInfo->u16Pitch * pPhotoInfo->u16Height,
                MIU_SDRAM2SDRAM);
    }
    else if(eSrcColorFmt == GFX_FMT_ARGB1555)
    {
        // color format transfer
        _MApp_Photo_Display_ColorFmtTransfer(
                pPhotoInfo->u16Pitch,
                pPhotoInfo->u16Height,
                u32DecodeOutputBuffAddr,
                GFX_FMT_ARGB1555,
                PHOTO_DISPLAY_SRC_BUFFER_ADDR,
                GFX_FMT_YUV422);

        // Copy converted image (in internal buffer) to decoder buffer.
        msAPI_MIU_Copy(
                PHOTO_DISPLAY_SRC_BUFFER_ADDR,
                u32DecodeOutputBuffAddr,
                (U32)2L * pPhotoInfo->u16Pitch * pPhotoInfo->u16Height,
                MIU_SDRAM2SDRAM);
    }
    // 1. Clear internal buffer to black.
    msAPI_GE_ClearFrameBufferByWord((U32)PHOTO_DISPLAY_SRC_BUFFER_ADDR,
                                   PHOTO_DISPLAY_SRC_BUFFER_SIZE,
                                   0x80008000);
    // after clear frame buffer, flush cmd
    MApi_GFX_FlushQueue();
    //printf("\n  msAPI_GE_ClearFrameBufferByWord , PHOTO_DISPLAY_SRC_BUFFER_SIZE=%x\n ", PHOTO_DISPLAY_SRC_BUFFER_SIZE);

    // 2. Stretch source to internal buffer.
    // BitBlt information settings
    // Calculate the destination dimension.
#if  PHOTO_DISPLAY_BY_ORIGINAL
    if(MApp_Photo_GetInfo(E_PHOTO_INFO_SCALE_DOWN_FACTOR) == 1)
    {
        //going to this condition means no shrink in JPD
        if(((U32)pPhotoInfo->u16Width>(U32)g_IPanel.Width()) || ((U32)pPhotoInfo->u16Height > (U32)PANEL_HEIGHT))
        {
            //Even the picture isn't shrinked in JPD, the picture still has possibility to be larger than panel size
            if((U32)g_IPanel.Width() * (U32)pPhotoInfo->u16Height >
               (U32)PANEL_HEIGHT * (U32)pPhotoInfo->u16Width)
            {
                //the original picture is "tall"
                u16DstW = (U16)((U32)pPhotoInfo->u16Width * PANEL_HEIGHT /
                                pPhotoInfo->u16Height);
                u16DstH = PANEL_HEIGHT;
            }
            else
            {
                //the original picture is "fat"
                u16DstH = (U16)((U32)pPhotoInfo->u16Height * (U32)g_IPanel.Width() /
                                pPhotoInfo->u16Width);
                u16DstW = (U16)g_IPanel.Width();
            }
        }
        else
        {
            //If we don't shrink the photo, that means photo width/height is correct if we don't strech(SEC spec)
            u16DstW = pPhotoInfo->u16Width;
            u16DstH = pPhotoInfo->u16Height;
        }
    }
    else if(MApp_Photo_GetInfo(E_PHOTO_INFO_SCALE_DOWN_FACTOR) > 1
        && ((U32)(pPhotoInfo->u16Width * MApp_Photo_GetInfo(E_PHOTO_INFO_SCALE_DOWN_FACTOR)) < (U32)g_IPanel.Width())
        && ((U32)(pPhotoInfo->u16Height * MApp_Photo_GetInfo(E_PHOTO_INFO_SCALE_DOWN_FACTOR)) < (U32)PANEL_HEIGHT))
    {
        //If photo shrink and width/height is smaller than panel
        u16DstW = pPhotoInfo->u16Width * MApp_Photo_GetInfo(E_PHOTO_INFO_SCALE_DOWN_FACTOR);
        u16DstH = pPhotoInfo->u16Height * MApp_Photo_GetInfo(E_PHOTO_INFO_SCALE_DOWN_FACTOR);
    }
    else
#endif //PHOTO_DISPLAY_BY_ORIGINAL
    if((U32)g_IPanel.Width() * (U32)pPhotoInfo->u16Height >
       (U32)PANEL_HEIGHT * (U32)pPhotoInfo->u16Width)
    {
        u16DstW = (U16)((((U32)pPhotoInfo->u16Width * PANEL_HEIGHT /
                        pPhotoInfo->u16Height) +1) & (0xFFFFFFFE));
        u16DstH = PANEL_HEIGHT;
    }
    else
    {
        u16DstH = (U16)((U32)pPhotoInfo->u16Height * (U32)g_IPanel.Width() /
                        pPhotoInfo->u16Width);
        u16DstW = (U16)g_IPanel.Width();
    }

    stBitbltInfo.BitbltCoordinate.v0_x = (((U16)g_IPanel.Width() - u16DstW) / 2) & (0xFFFFFFFE);
    stBitbltInfo.BitbltCoordinate.v0_y = (PANEL_HEIGHT - u16DstH) / 2;

    //printf(" \n u16DstW=%x,  u16DstH=%x",u16DstW, u16DstH );
    //printf(" \n PHOTO_ADJUSTED_PANEL_WIDTH=%x,  PANEL_HEIGHT=%x",PHOTO_ADJUSTED_PANEL_WIDTH, PANEL_HEIGHT );

    stBitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;
    stBitbltInfo.BmpFlag = GFXDRAW_FLAG_DEFAULT;
    stBitbltInfo.BitbltCoordinate.direction = 0;

    stBitbltInfo.BitbltCoordinate.width = u16DstW;
    stBitbltInfo.BitbltCoordinate.height = u16DstH;
    stBitbltInfo.BitbltCoordinate.v2_x = 0; //src
    stBitbltInfo.BitbltCoordinate.v2_y = 0;
    stBitbltInfo.src_width= pPhotoInfo->u16Width & 0xFFFE;
    stBitbltInfo.src_height = pPhotoInfo->u16Height & 0xFFFE;
    stBitbltInfo.src_fm = GFX_FMT_YUV422;
    stBitbltInfo.dst_fm = GFX_FMT_YUV422;

    m_u16PhotoSrcX = stBitbltInfo.BitbltCoordinate.v0_x;
    m_u16PhotoSrcY = stBitbltInfo.BitbltCoordinate.v0_y;
    m_u16PhotoSrcWidth = u16DstW;
    m_u16PhotoSrcHeight = u16DstH;

    m_u16PhotoDstX = stBitbltInfo.BitbltCoordinate.v0_x;
    m_u16PhotoDstY = stBitbltInfo.BitbltCoordinate.v0_y;
    m_u16PhotoDstWidth = u16DstW;
    m_u16PhotoDstHeight = u16DstH;

    //printf(" \n pit=%x,  w=%x  ,  PHOTO_ADJUSTED_PANEL_WIDTH=%x",pPhotoInfo->u16Pitch, pPhotoInfo->u16Width , PHOTO_ADJUSTED_PANEL_WIDTH);

    stPitBaseInfo.sb_pit = pPhotoInfo->u16Pitch * 2;
    stPitBaseInfo.db_pit = PHOTO_ADJUSTED_PANEL_WIDTH * 2;  // 2 bytes per pixel
    stPitBaseInfo.sb_base = u32DecodeOutputBuffAddr;
    stPitBaseInfo.db_base = PHOTO_DISPLAY_SRC_BUFFER_ADDR;

    msAPI_OSD_SetClipWindow(0, 0, PHOTO_ADJUSTED_PANEL_WIDTH, PANEL_HEIGHT);

    MApi_GFX_EnableAlphaBlending(FALSE);
    msAPI_GE_SetNearestMode(FALSE);
    msAPI_GE_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_PC, GFX_YUV_OUT_255, GFX_YUV_IN_255, GFX_YUV_YUYV, GFX_YUV_YUYV);

    msAPI_GE_BitBlt(&stBitbltInfo, &stPitBaseInfo);
    // after BitBlt, flush cmd
    MApi_GFX_FlushQueue();

#if SAVE_BW_PHOTO_SLIDE_SHOW
    if (MApi_XC_IsFreezeImg(MAIN_WINDOW))
    {
        MApi_XC_FreezeImg(FALSE, MAIN_WINDOW);
    }
#endif
    // Prepare slide show type.
    if(eEffect == E_SLIDE_SHOW_EFFECT_RANDOM)
    {
        u8Rand = (U8)msAPI_Timer_GetTime0();
        slideShowEffect = (EN_PHOTO_SLIDE_SHOW_EFFECT)(u8Rand % E_SLIDE_SHOW_EFFECT_NUM);
    }
    else
    {
        slideShowEffect = eEffect;
    }

    if(0)
    {
    }
#if (ENABLE_PHOTO_TRANS_EFFECT_BLOCKS)
    else if(eEffect == E_SLIDE_SHOW_EFFECT_BLOCKS_RANDOM)
    {
        u8Rand = (U8)msAPI_Timer_GetTime0();
        slideShowEffect = (EN_PHOTO_SLIDE_SHOW_EFFECT)(E_SLIDE_SHOW_EFFECT_HORZ_BLOCKS_TOPLEFT + (u8Rand % (E_SLIDE_SHOW_EFFECT_RANDOM_BLOCKS-E_SLIDE_SHOW_EFFECT_HORZ_BLOCKS_TOPLEFT+1)));
        PHOTO_DISP_MSG(printf("E_SLIDE_SHOW_EFFECT_BLOCKS_RANDOM: %d\n", slideShowEffect));
    }
#endif
#if (ENABLE_PHOTO_TRANS_EFFECT_DIAGONAL_BLOCKS)
    else if(eEffect == E_SLIDE_SHOW_EFFECT_DIAGONAL_BLOCKS_RANDOM)
    {
        u8Rand = (U8)msAPI_Timer_GetTime0();
        slideShowEffect = (EN_PHOTO_SLIDE_SHOW_EFFECT)(E_SLIDE_SHOW_EFFECT_DIAGONAL_BLOCKS_TOPLEFT + (u8Rand % (E_SLIDE_SHOW_EFFECT_DIAGONAL_BLOCKS_BOTTOMRIGHT-E_SLIDE_SHOW_EFFECT_DIAGONAL_BLOCKS_TOPLEFT+1)));
        PHOTO_DISP_MSG(printf("E_SLIDE_SHOW_EFFECT_DIAGONAL_BLOCKS_RANDOM: %d\n", slideShowEffect));
    }
#endif
#if (ENABLE_PHOTO_TRANS_EFFECT_WIPE)
    else if(eEffect == E_SLIDE_SHOW_EFFECT_WIPE_RANDOM)
    {
        u8Rand = (U8)msAPI_Timer_GetTime0();
        slideShowEffect = (EN_PHOTO_SLIDE_SHOW_EFFECT)(E_SLIDE_SHOW_EFFECT_BARWIPE_LEFT2RIGHT + (u8Rand % (E_SLIDE_SHOW_EFFECT_4BARWIPE_VERTICAL_FROM_RIGHT-E_SLIDE_SHOW_EFFECT_BARWIPE_LEFT2RIGHT+1)));
        PHOTO_DISP_MSG(printf("E_SLIDE_SHOW_EFFECT_WIPE_RANDOM: %d\n", slideShowEffect));
    }
#endif
#if (ENABLE_PHOTO_TRANS_EFFECT_SLIDE)
    else if(eEffect == E_SLIDE_SHOW_EFFECT_SLIDE_RANDOM)
    {
        u8Rand = (U8)msAPI_Timer_GetTime0();
        slideShowEffect = (EN_PHOTO_SLIDE_SHOW_EFFECT)(E_SLIDE_SHOW_EFFECT_BARSLIDE_LEFT2RIGHT + (u8Rand % (E_SLIDE_SHOW_EFFECT_4BARSLIDE_VERTICAL_FROM_RIGHT-E_SLIDE_SHOW_EFFECT_BARSLIDE_LEFT2RIGHT+1)));
        PHOTO_DISP_MSG(printf("E_SLIDE_SHOW_EFFECT_SLIDE_RANDOM: %d\n", slideShowEffect));
    }
#endif
#if (ENABLE_PHOTO_TRANS_EFFECT_FADE)
    else if(eEffect == E_SLIDE_SHOW_EFFECT_FADE_RANDOM)
    {
        u8Rand = (U8)msAPI_Timer_GetTime0();
        slideShowEffect = (EN_PHOTO_SLIDE_SHOW_EFFECT)(E_SLIDE_SHOW_EFFECT_FADE + (u8Rand % (E_SLIDE_SHOW_EFFECT_FADE-E_SLIDE_SHOW_EFFECT_FADE+1)));
        PHOTO_DISP_MSG(printf("E_SLIDE_SHOW_EFFECT_FADE_RANDOM: %d\n", slideShowEffect));
    }
#endif

#if 0
    for(slideShowEffect = E_SLIDE_SHOW_EFFECT_BARSLIDE_LEFT2RIGHT;
        slideShowEffect <= E_SLIDE_SHOW_EFFECT_4BARSLIDE_VERTICAL_FROM_RIGHT;
        slideShowEffect++)
    {
        printf("Effect = %bd\n", slideShowEffect);
        msAPI_GE_ClearFrameBufferByWord((U32)PHOTO_DISPLAY_BUFFER_ADDR,
                                       PHOTO_DISPLAY_BUFFER_SIZE,
                                       0x00000000);
        // after clear frame buffer, flush cmd
        MApi_GFX_FlushQueue();
#endif
    if(0)
    {
    }
#if (ENABLE_PHOTO_TRANS_EFFECT_BLOCKS)
    else if(slideShowEffect >= E_SLIDE_SHOW_EFFECT_HORZ_BLOCKS_TOPLEFT &&
            slideShowEffect <= E_SLIDE_SHOW_EFFECT_VERT_ZIGZAG_BLOCKS_BOTTOMRIGHT)
    {
        _MApp_Photo_SlideShow_Blocks(slideShowEffect);
    }
    else if(slideShowEffect == E_SLIDE_SHOW_EFFECT_RANDOM_BLOCKS)
    {
        _MApp_Photo_SlideShow_Blocks_Random();
    }
#endif  // #if (ENABLE_PHOTO_TRANS_EFFECT_BLOCKS)
#if (ENABLE_PHOTO_TRANS_EFFECT_DIAGONAL_BLOCKS)
    else if(slideShowEffect >= E_SLIDE_SHOW_EFFECT_DIAGONAL_BLOCKS_TOPLEFT &&
            slideShowEffect <= E_SLIDE_SHOW_EFFECT_DIAGONAL_BLOCKS_BOTTOMRIGHT)
    {
        _MApp_Photo_SlideShow_Diagonal_Blocks(slideShowEffect);
    }
#endif  // #if (ENABLE_PHOTO_TRANS_EFFECT_DIAGONAL_BLOCKS)
#if (ENABLE_PHOTO_TRANS_EFFECT_WIPE)
    else if(slideShowEffect >= E_SLIDE_SHOW_EFFECT_BARWIPE_LEFT2RIGHT &&
            slideShowEffect <= E_SLIDE_SHOW_EFFECT_4BARWIPE_VERTICAL_FROM_RIGHT)
    {
        _MApp_Photo_SlideShow_EdgeWipe(slideShowEffect);
    }
#endif  // #if (ENABLE_PHOTO_TRANS_EFFECT_WIPE)
#if (ENABLE_PHOTO_TRANS_EFFECT_SLIDE)
    else if(slideShowEffect >= E_SLIDE_SHOW_EFFECT_BARSLIDE_LEFT2RIGHT &&
            slideShowEffect <= E_SLIDE_SHOW_EFFECT_4BARSLIDE_VERTICAL_FROM_RIGHT)
    {
        _MApp_Photo_SlideShow_Slide(slideShowEffect);
    }
#endif  // #if (ENABLE_PHOTO_TRANS_EFFECT_SLIDE)
#if (ENABLE_PHOTO_TRANS_EFFECT_FADE)
    else if(slideShowEffect >= E_SLIDE_SHOW_EFFECT_FADE &&
            slideShowEffect <= E_SLIDE_SHOW_EFFECT_FADE)
    {
        _MApp_Photo_SlideShow_Fade(slideShowEffect);
    }
#endif  // #if (ENABLE_PHOTO_TRANS_EFFECT_FADE)
    else
    {
        _MApp_Photo_SlideShow_Normal();
    }

#if SAVE_BW_PHOTO_SLIDE_SHOW
    if (MApi_XC_IsFreezeImg(MAIN_WINDOW))
    {
        // 1. need to ask GE? Is this reasonable?
        // 2. seems °{
        msAPI_Timer_Delayms(100);
        MApi_XC_FreezeImg(TRUE, MAIN_WINDOW);
    }
#endif
}

BOOLEAN MApp_Photo_Zooming(EN_PHOTO_ZOOMING en_Zooming)
{
    EN_PHOTO_ZOOMING enZoomingOld;

    enZoomingOld = m_enZooming;
    m_s16PhotoOffsetX = m_s16PhotoOffsetY = 0;
    switch(en_Zooming)
    {
    case EN_PHOTO_ZOOM_1_8:
    case EN_PHOTO_ZOOM_1_4:
    case EN_PHOTO_ZOOM_1_2:
    case EN_PHOTO_ZOOM_1:
    case EN_PHOTO_ZOOM_2:
    case EN_PHOTO_ZOOM_4:
    case EN_PHOTO_ZOOM_8:
        m_enZooming = en_Zooming;
        break;
    default:
        return FALSE;
    }

    if(!_MApp_Photo_ShowEffect())
    {
        m_enZooming = enZoomingOld;
        return FALSE;
    }
    return TRUE;
}

BOOLEAN MApp_Photo_MoveViewWindow(EN_PHOTO_DIRECTION enDirection, U16 u16LineCount)
{
    S16 s16PhotoOffsetXOld, s16PhotoOffsetY;

    s16PhotoOffsetXOld = m_s16PhotoOffsetX;
    s16PhotoOffsetY = m_s16PhotoOffsetY;

    switch(m_enRotation)
    {
    case EN_PHOTO_ROTATE_0:
        switch(enDirection)
        {
        case EN_PHOTO_MOVE_UP:
            m_s16PhotoOffsetY -= u16LineCount;
            break;
        case EN_PHOTO_MOVE_DOWN:
            m_s16PhotoOffsetY += u16LineCount;
            break;
        case EN_PHOTO_MOVE_LEFT:
            m_s16PhotoOffsetX -= u16LineCount;
            break;
        case EN_PHOTO_MOVE_RIGHT:
            m_s16PhotoOffsetX += u16LineCount;
            break;
        default:
            return FALSE;
        }
        break;
    case EN_PHOTO_ROTATE_90:
        switch(enDirection)
        {
        case EN_PHOTO_MOVE_UP:
            m_s16PhotoOffsetX -= u16LineCount;
            break;
        case EN_PHOTO_MOVE_DOWN:
            m_s16PhotoOffsetX += u16LineCount;
            break;
        case EN_PHOTO_MOVE_LEFT:
            m_s16PhotoOffsetY += u16LineCount;
            break;
        case EN_PHOTO_MOVE_RIGHT:
            m_s16PhotoOffsetY -= u16LineCount;
            break;
        default:
            return FALSE;
        }
        break;
    case EN_PHOTO_ROTATE_180:
        switch(enDirection)
        {
        case EN_PHOTO_MOVE_UP:
            m_s16PhotoOffsetY += u16LineCount;
            break;
        case EN_PHOTO_MOVE_DOWN:
            m_s16PhotoOffsetY -= u16LineCount;
            break;
        case EN_PHOTO_MOVE_LEFT:
            m_s16PhotoOffsetX += u16LineCount;
            break;
        case EN_PHOTO_MOVE_RIGHT:
            m_s16PhotoOffsetX -= u16LineCount;
            break;
        default:
            return FALSE;
        }
        break;
    case EN_PHOTO_ROTATE_270:
        switch(enDirection)
        {
        case EN_PHOTO_MOVE_UP:
            m_s16PhotoOffsetX += u16LineCount;
            break;
        case EN_PHOTO_MOVE_DOWN:
            m_s16PhotoOffsetX -= u16LineCount;
            break;
        case EN_PHOTO_MOVE_LEFT:
            m_s16PhotoOffsetY -= u16LineCount;
            break;
        case EN_PHOTO_MOVE_RIGHT:
            m_s16PhotoOffsetY += u16LineCount;
            break;
        default:
            return FALSE;
        }
        break;
    default:
        return FALSE;
    }

    if(!_MApp_Photo_ShowEffect())
    {
        m_s16PhotoOffsetX = s16PhotoOffsetXOld;
        m_s16PhotoOffsetY = s16PhotoOffsetY;
        return FALSE;
    }
    return TRUE;
}

BOOLEAN MApp_Photo_Rotate(EN_PHOTO_ROTATION enRotation)
{
    EN_PHOTO_ROTATION enRotationOld;

    enRotationOld = m_enRotation;
    m_s16PhotoOffsetX = m_s16PhotoOffsetY = 0;
    switch(enRotation)
    {
    case EN_PHOTO_ROTATE_0:
    case EN_PHOTO_ROTATE_90:
    case EN_PHOTO_ROTATE_180:
    case EN_PHOTO_ROTATE_270:
        m_enRotation = (EN_PHOTO_ROTATION)((enRotation) % (U8)EN_PHOTO_ROTATE_360);
        break;
    default:
        return FALSE;
    }

    if(!_MApp_Photo_ShowEffect())
    {
        m_enRotation = enRotationOld;
        return FALSE;
    }
    return TRUE;
}
#endif  // #if PHOTO_SLIDE_SHOW_EFFECT

void MApp_Photo_Display_SetViewWin(U16 u16X, U16 u16Y, U16 u16Width, U16 u16Height)
{
    u16ViewWinX = u16X;
    u16ViewWinY = u16Y;
    u16ViewWinWidth     = u16Width;
    u16ViewWinHeight    = u16Height;
}

#if ENABLE_4K2K
void MApp_Photo_Display_Disable4K2KPhotoDisplay(void)
{
    MDrv_Ursa_6M40_VIDEO_Enalbe(TRUE); //set black screen for ursa
    MDrv_URSA_6M40_Set_4K_2K_Mode(FALSE); //close 4Kx2k mode for ursa
    MDrv_Photo_Display_Set4K2KMode(FALSE);//Close the 4kx2k mode
    MApi_GOP_GWIN_DeleteWin(GOP1_GWIN_START); //delete the gwin for display 4kx2k photo
    MsOS_DelayTask(500);//wait for ursa
    MDrv_Ursa_6M40_VIDEO_Enalbe(FALSE); //close the black screen
}
static void _MApp_Photo_Display_Initialize_PhotoDisplaySetting(MS_U32 u32Buff)
{
    MS_U8 u8fbid;

    //Initiail GOP setting for displaying 1st photo
    MApi_GOP_GWIN_SetForceWrite(TRUE);
    u8fbid = MApi_GOP_GWIN_GetFreeFBID();
    MApi_GOP_GWIN_CreateFBbyStaticAddr(u8fbid, 0, 0, 1920, 1080,  GFX_FMT_YUV422, u32Buff );
    MApi_GOP_GWIN_CreateWin_Assign_FB(E_GOP_APP, u8fbid, 0, 0);
    MApi_GOP_GWIN_CreateStaticWin_Assign_FB(GOP1_GWIN_START, E_GOP_APP, u8fbid, 0, 0);
    MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);
    MApi_GOP_SetUVSwap(E_GOP_APP, TRUE);
    MApi_GOP_Initialize_StretchWindow(E_GOP_APP);
    MApi_GOP_GWIN_Set_HSCALE(FALSE, 1, 1) ;
    MApi_GOP_GWIN_Set_VSCALE(FALSE, 1, 1) ;
    MApi_GOP_GWIN_SetBlending(GOP1_GWIN_START, TRUE, 0xFF);
    MApi_GOP_GWIN_SetForceWrite(FALSE);
    MApi_GOP_GWIN_Enable(MApp_ZUI_API_QueryGWinID(),FALSE);

    //Ursa control
    MDrv_URSA_6M40_Set_4K_2K_Mode(TRUE);
    MDrv_Ursa_6M40_VIDEO_Enalbe(TRUE);
    MsOS_DelayTask(500);
    MDrv_Photo_Display_Set4K2KMode(TRUE);
    MDrv_Ursa_6M40_VIDEO_Enalbe(FALSE);
}

//******************************************************************************
/// Display 4K2K photo by GOP, use GE BitBlt to segment 4K2K photo to 4 FHD part,
/// and use URSA and GOP to display.
/// @param  bIsPreview \b IN  Specify is preview or normal play.
/// @return NA
//******************************************************************************
void MApp_Photo_4K2K_DisplayByGOP(BOOLEAN bIsPreview)
{
    U16 u16Pitch, u16Width, u16Height, u16DstW, u16DstH;
    GFX_Buffer_Format eColorFmt;
    U8 u8BytesPerPixel;

    u16Pitch = MApp_Photo_GetInfo(E_PHOTO_INFO_PITCH);
    u16Width = MApp_Photo_GetInfo(E_PHOTO_INFO_WIDTH);
    u16Height = MApp_Photo_GetInfo(E_PHOTO_INFO_HEIGHT);
    PHOTO_DISP_MSG(printf("[4K2K Photo Display]u16Pitch = %d, u16Width= %d, u16Height = %d\n", u16Pitch, u16Width, u16Height));

    // output format checking
    switch (MApp_Photo_GetInfo(E_PHOTO_INFO_OUTPUT_FORMAT))
    {
        case E_PHOTO_OUTPUT_ARGB8888:
            eColorFmt = GFX_FMT_ARGB8888;
            u8BytesPerPixel = 4;
            PHOTO_DISP_MSG(printf("[4K2K Photo Display]E_PHOTO_OUTPUT_ARGB8888\n"));
            break;
        case E_PHOTO_OUTPUT_ARGB1555:
            eColorFmt = GFX_FMT_ARGB1555;
            u8BytesPerPixel = 2;
            PHOTO_DISP_MSG(printf("[4K2K Photo Display]E_PHOTO_OUTPUT_ARGB1555\n"));
            break;
        case E_PHOTO_OUTPUT_YUV422:
            eColorFmt = GFX_FMT_YUV422;
            u8BytesPerPixel = 2;
            PHOTO_DISP_MSG(printf("[4K2K Photo Display]E_PHOTO_OUTPUT_YUV422\n"));
            break;

        default:
            PHOTO_DISP_MSG(printf("[4K2K Photo Display] Color format not supported!\n"));
            return;
    }

    if(u16Width == 0 || u16Height == 0)
    {
        PHOTO_DISP_MSG(printf("[4K2K Photo Display] MApp_Photo_Display() Error resolution.\n"));
        return;
    }

    if (bIsPreview)
    {
        // no preview
    }
    else
    {
        if (MDrv_Photo_Display_Get4K2KMode()== TRUE)
        {
            MDrv_URSA_6M40_Set_Video_Freeze(TRUE);
        }
    #if NOT_FIT_SCREEN_IN_4K2K
        u16DstW = u16Width;
        u16DstH = u16Height;
    #else
        #if 0
        // Calculate the destination dimension.
        if(MApp_Photo_GetInfo(E_PHOTO_INFO_SCALE_DOWN_FACTOR) == 1)
        {
            u16DstW = u16Width;
            u16DstH = u16Height;
        }
        else
        #endif
        if((U32)PANEL_4K2K_WIDTH * (U32)u16Height >
                (U32)PANEL_4K2K_HEIGHT * (U32)u16Width)
        {
            u16DstW = (U16)((((U32)u16Width * PANEL_4K2K_HEIGHT /
                            u16Height) +1) & (0xFFFFFFFE));
            u16DstH = PANEL_4K2K_HEIGHT;
        }
        else
        {
            u16DstH = (U16)((U32)u16Height * (U32)PANEL_4K2K_WIDTH /
                                u16Width);
            u16DstW = (U16)PANEL_4K2K_WIDTH;
        }
    #endif
        PHOTO_DISP_MSG(printf("[4K2K Photo Display]u16DstW = %d, u16DstH= %d\n", u16DstW, u16DstH));

        GEBitBltInfo stBitbltInfo;
        GEPitBaseInfo stPitBaseInfo;
        EN_PHOTO_4K2K_BLOCK eBlock;
        const U32 u32BlockSize = 1920*1080*2;
        U32 u32DecodeOutputBuffAddr = PHOTO_OUTPUT_BUFFER_ADDR;
        U32 u32DisplayBuffAddr = PHOTO_DISPLAY_BUFFER_ADDR;
        U32 u32DisplayBuffLen = PHOTO_DISPLAY_BUFFER_SIZE;

    #if ENABLE_4K2K_DUMP_BUF
        extern U8 MApp_FileBrowser_OpenNewFileForWrite(U16* pString,U8 charLen);
        U16 u16FileName0[15] = {'3', '8', '4', '0', 'x', '2', '1', '6', '0', '.', 'y', 'u', 'y', 'v', 0};
        U8 u8FileHandle0;

        u8FileHandle0 = MApp_FileBrowser_OpenNewFileForWrite(u16FileName0, 15);
        msAPI_FCtrl_FileWrite(u8FileHandle0, u32DecodeOutputBuffAddr, 0x1000000); //16M
        msAPI_FCtrl_FileClose(u8FileHandle0);
    #endif

            // clear display buffer to black.
            msAPI_GE_ClearFrameBufferByWord((U32)u32DisplayBuffAddr,
                                           u32DisplayBuffLen,
                                           0x80008000);
            // after clear frame buffer, flush cmd
            MApi_GFX_FlushQueue();

    #if (!NOT_FIT_SCREEN_IN_4K2K)
        //Step1 => OutputBuffer stretch to DisplayBuffer, Colorfmt transfer to YUV422.
        {
            stBitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;
            stBitbltInfo.BmpFlag = GFXDRAW_FLAG_DEFAULT;
            stBitbltInfo.BitbltCoordinate.direction = 0;

            // src
            stBitbltInfo.src_fm = eColorFmt;
            stBitbltInfo.BitbltCoordinate.v2_x = 0;
            stBitbltInfo.BitbltCoordinate.v2_y = 0;
            stBitbltInfo.src_width= u16Width;
            stBitbltInfo.src_height = u16Height;
            stPitBaseInfo.sb_pit = u16Pitch * u8BytesPerPixel;
            stPitBaseInfo.sb_base = u32DecodeOutputBuffAddr;

            // dst
            stBitbltInfo.dst_fm = GFX_FMT_YUV422;
            stBitbltInfo.BitbltCoordinate.v0_x = HALF(PANEL_4K2K_WIDTH - u16DstW);
            stBitbltInfo.BitbltCoordinate.v0_y = HALF(PANEL_4K2K_HEIGHT - u16DstH);
            stBitbltInfo.BitbltCoordinate.width = u16DstW;
            stBitbltInfo.BitbltCoordinate.height = u16DstH;
            stPitBaseInfo.db_pit = PANEL_4K2K_WIDTH * 2;  // 2 bytes per pixel
            stPitBaseInfo.db_base = u32DisplayBuffAddr;

            msAPI_OSD_SetClipWindow(0, 0, PANEL_4K2K_WIDTH, PANEL_4K2K_HEIGHT);

            MApi_GFX_EnableAlphaBlending(FALSE);
            msAPI_GE_SetNearestMode(FALSE);
            msAPI_GE_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_PC, GFX_YUV_OUT_255, GFX_YUV_IN_255, GFX_YUV_YUYV, GFX_YUV_YUYV);

            msAPI_GE_BitBlt(&stBitbltInfo, &stPitBaseInfo);
            // after BitBlt, flush cmd
            MApi_GFX_FlushQueue();
        }

        //Step2 => copy DisplayBuffer to OutputBuffer
        {
            stBitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;
            stBitbltInfo.BmpFlag = GFXDRAW_FLAG_DEFAULT;
            stBitbltInfo.BitbltCoordinate.direction = 0;

            // src
            stBitbltInfo.src_fm = GFX_FMT_YUV422;
            stBitbltInfo.BitbltCoordinate.v2_x = 0;
            stBitbltInfo.BitbltCoordinate.v2_y = 0;
            stBitbltInfo.src_width= PANEL_4K2K_WIDTH;
            stBitbltInfo.src_height = PANEL_4K2K_HEIGHT;
            stPitBaseInfo.sb_pit = PANEL_4K2K_WIDTH * 2;  // 2 bytes per pixel
            stPitBaseInfo.sb_base = u32DisplayBuffAddr;

            // dst
            stBitbltInfo.dst_fm = GFX_FMT_YUV422;
            stBitbltInfo.BitbltCoordinate.v0_x = 0;
            stBitbltInfo.BitbltCoordinate.v0_y = 0;
            stBitbltInfo.BitbltCoordinate.width = PANEL_4K2K_WIDTH;
            stBitbltInfo.BitbltCoordinate.height = PANEL_4K2K_HEIGHT;
            stPitBaseInfo.db_pit = PANEL_4K2K_WIDTH * 2;  // 2 bytes per pixel
            stPitBaseInfo.db_base = u32DecodeOutputBuffAddr;

            msAPI_OSD_SetClipWindow(0, 0, PANEL_4K2K_WIDTH, PANEL_4K2K_HEIGHT);

            MApi_GFX_EnableAlphaBlending(FALSE);
            msAPI_GE_SetNearestMode(FALSE);
            msAPI_GE_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_PC, GFX_YUV_OUT_255, GFX_YUV_IN_255, GFX_YUV_YUYV, GFX_YUV_YUYV);

            msAPI_GE_BitBlt(&stBitbltInfo, &stPitBaseInfo);
            // after BitBlt, flush cmd
            MApi_GFX_FlushQueue();
        }

        eColorFmt = GFX_FMT_YUV422;
        u8BytesPerPixel = 2;
        u16Pitch = u16Width = u16DstW = PANEL_4K2K_WIDTH;
        u16Height = u16DstH = PANEL_4K2K_HEIGHT;
    #endif

        //Step3 => OutputBuffer bitblt to DisplayBuffer as 4K2K buffer type
        {
            stBitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;
            stBitbltInfo.BmpFlag = GFXDRAW_FLAG_DEFAULT;
            stBitbltInfo.BitbltCoordinate.direction = 0;

            //src
            stBitbltInfo.src_fm = eColorFmt;
            stPitBaseInfo.sb_pit = u16Pitch * u8BytesPerPixel;
            stPitBaseInfo.sb_base = u32DecodeOutputBuffAddr;

            //dst
            stBitbltInfo.dst_fm = GFX_FMT_YUV422;
            stPitBaseInfo.db_pit = HALF(PANEL_4K2K_WIDTH) * 2;  // 2 bytes per pixel

            for(eBlock=E_PHOTO_4K2K_LEFT_TOP; eBlock<=E_PHOTO_4K2K_RIGHT_BOTTOM; eBlock++)
            {
                stPitBaseInfo.db_base = u32DisplayBuffAddr+(U32)eBlock*u32BlockSize;

                switch (eBlock)
                {
                    case E_PHOTO_4K2K_LEFT_TOP:
                        //src
                        stBitbltInfo.BitbltCoordinate.v2_x = 0;
                        stBitbltInfo.BitbltCoordinate.v2_y = 0;
                        stBitbltInfo.src_width= HALF(u16Width);
                        stBitbltInfo.src_height = HALF(u16Height);
                        //dst
                        stBitbltInfo.BitbltCoordinate.v0_x = HALF(PANEL_4K2K_WIDTH) - HALF(u16DstW);
                        stBitbltInfo.BitbltCoordinate.v0_y = HALF(PANEL_4K2K_HEIGHT) - HALF(u16DstH);
                        stBitbltInfo.BitbltCoordinate.width = HALF(u16DstW);
                        stBitbltInfo.BitbltCoordinate.height = HALF(u16DstH);
                        PHOTO_DISP_MSG(printf("[4K2K Photo Display][Left,Top]x:%d, y:%d, w:%d, h:%d -- X:%d, Y:%d, W:%d, H:%d\n"
                              ,stBitbltInfo.BitbltCoordinate.v2_x, stBitbltInfo.BitbltCoordinate.v2_y, stBitbltInfo.src_width, stBitbltInfo.src_height
                              ,stBitbltInfo.BitbltCoordinate.v0_x, stBitbltInfo.BitbltCoordinate.v0_y, stBitbltInfo.BitbltCoordinate.width, stBitbltInfo.BitbltCoordinate.height));
                        break;
                    case E_PHOTO_4K2K_RIGHT_TOP:
                        //src
                        stBitbltInfo.BitbltCoordinate.v2_x = HALF(u16Width);
                        stBitbltInfo.BitbltCoordinate.v2_y = 0;
                        stBitbltInfo.src_width= REST_HALF(u16Width);
                        stBitbltInfo.src_height = HALF(u16Height);
                        //dst
                        stBitbltInfo.BitbltCoordinate.v0_x = 0;
                        stBitbltInfo.BitbltCoordinate.v0_y = HALF(PANEL_4K2K_HEIGHT) - HALF(u16DstH);
                        stBitbltInfo.BitbltCoordinate.width = REST_HALF(u16DstW);
                        stBitbltInfo.BitbltCoordinate.height = HALF(u16DstH);
                        PHOTO_DISP_MSG(printf("[4K2K Photo Display][Right,Top]x:%d, y:%d, w:%d, h:%d -- X:%d, Y:%d, W:%d, H:%d\n"
                              ,stBitbltInfo.BitbltCoordinate.v2_x, stBitbltInfo.BitbltCoordinate.v2_y, stBitbltInfo.src_width, stBitbltInfo.src_height
                              ,stBitbltInfo.BitbltCoordinate.v0_x, stBitbltInfo.BitbltCoordinate.v0_y, stBitbltInfo.BitbltCoordinate.width, stBitbltInfo.BitbltCoordinate.height));
                        break;
                    case E_PHOTO_4K2K_LEFT_BOTTOM:
                        //src
                        stBitbltInfo.BitbltCoordinate.v2_x = 0;
                        stBitbltInfo.BitbltCoordinate.v2_y = HALF(u16Height);
                        stBitbltInfo.src_width= HALF(u16Width);
                        stBitbltInfo.src_height = REST_HALF(u16Height);
                        //dst
                        stBitbltInfo.BitbltCoordinate.v0_x = HALF(PANEL_4K2K_WIDTH) - HALF(u16DstW);
                        stBitbltInfo.BitbltCoordinate.v0_y = 0;
                        stBitbltInfo.BitbltCoordinate.width = HALF(u16DstW);
                        stBitbltInfo.BitbltCoordinate.height = REST_HALF(u16DstH);
                        PHOTO_DISP_MSG(printf("[4K2K Photo Display][Left,Bottom]x:%d, y:%d, w:%d, h:%d -- X:%d, Y:%d, W:%d, H:%d\n"
                              ,stBitbltInfo.BitbltCoordinate.v2_x, stBitbltInfo.BitbltCoordinate.v2_y, stBitbltInfo.src_width, stBitbltInfo.src_height
                              ,stBitbltInfo.BitbltCoordinate.v0_x, stBitbltInfo.BitbltCoordinate.v0_y, stBitbltInfo.BitbltCoordinate.width, stBitbltInfo.BitbltCoordinate.height));
                        break;
                    case E_PHOTO_4K2K_RIGHT_BOTTOM:
                        //src
                        stBitbltInfo.BitbltCoordinate.v2_x = HALF(u16Width);
                        stBitbltInfo.BitbltCoordinate.v2_y = HALF(u16Height);
                        stBitbltInfo.src_width= REST_HALF(u16Width);
                        stBitbltInfo.src_height = REST_HALF(u16Height);
                        //dst
                        stBitbltInfo.BitbltCoordinate.v0_x = 0;
                        stBitbltInfo.BitbltCoordinate.v0_y = 0;
                        stBitbltInfo.BitbltCoordinate.width = REST_HALF(u16DstW);
                        stBitbltInfo.BitbltCoordinate.height = REST_HALF(u16DstH);
                        PHOTO_DISP_MSG(printf("[4K2K Photo Display][Right,Bottom]x:%d, y:%d, w:%d, h:%d -- X:%d, Y:%d, W:%d, H:%d\n"
                              ,stBitbltInfo.BitbltCoordinate.v2_x, stBitbltInfo.BitbltCoordinate.v2_y, stBitbltInfo.src_width, stBitbltInfo.src_height
                              ,stBitbltInfo.BitbltCoordinate.v0_x, stBitbltInfo.BitbltCoordinate.v0_y, stBitbltInfo.BitbltCoordinate.width, stBitbltInfo.BitbltCoordinate.height));
                        break;
                    default:
                        PHOTO_DISP_MSG(printf("[4K2K Photo Display] Color format not supported!\n"));
                        return;
                }

                msAPI_OSD_SetClipWindow(0, 0, PANEL_4K2K_WIDTH, PANEL_4K2K_HEIGHT);

                MApi_GFX_EnableAlphaBlending(FALSE);
                msAPI_GE_SetNearestMode(FALSE);
                msAPI_GE_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_PC, GFX_YUV_OUT_255, GFX_YUV_IN_255, GFX_YUV_YUYV, GFX_YUV_YUYV);

                msAPI_GE_BitBlt(&stBitbltInfo, &stPitBaseInfo);
                // after BitBlt, flush cmd
                MApi_GFX_FlushQueue();
            }
        }
    #if ENABLE_4K2K_DUMP_BUF
        U16 u16FileName[17] = {'1', '9', '2', '0', 'x', '1', '0', '8', '0', '_', ' ', '.', 'y', 'u', 'y', 'v', 0};
        U8 u8FileHandle;

        for(eBlock=E_PHOTO_4K2K_LEFT_TOP; eBlock<=E_PHOTO_4K2K_RIGHT_BOTTOM; eBlock++)
        {
            u16FileName[10] = (U16)eBlock+'0';
            u8FileHandle = MApp_FileBrowser_OpenNewFileForWrite(u16FileName, 17);
            msAPI_FCtrl_FileWrite(u8FileHandle, u32DisplayBuffAddr+(U32)eBlock*u32BlockSize, u32BlockSize);
            msAPI_FCtrl_FileClose(u8FileHandle);
        }
    #endif
        //TODO:
        {
            U8 u8temp = 0;

            for (u8temp = 0; u8temp < 4; u8temp++)
            {
                MDrv_Photo_Display_Set4K2KPhotoBufAdd(u8temp, u32DisplayBuffAddr+u8temp*u32BlockSize);
            }

            if (MDrv_Photo_Display_Get4K2KMode()== FALSE)
            {
                _MApp_Photo_Display_Initialize_PhotoDisplaySetting(u32DisplayBuffAddr);
            }
            else
            {
                MDrv_Ursa_6M40_VIDEO_Enalbe(TRUE);
                MsOS_DelayTask(600); //wait ursa response
                MDrv_Ursa_6M40_VIDEO_Enalbe(FALSE);
                MDrv_URSA_6M40_Set_Video_Freeze(FALSE);
            }
        }
    }
}
#endif
//static void MAPP_RGBPicProcess_OutputImage(U32 displayBufAddr)
//for JPEG BMP PNG
void MApp_Photo_Display(BOOLEAN bIsPreview)
{
    SlideShowPhotoInfo photoInfo;
    EN_PHOTO_OUTPUT_FORMAT enPhotoFmt;
    U32 u32DecodeOutputBuffAddr;
#if ENABLE_AUTO_ROTATION
    EN_PHOTO_ORIENTATION eOrientation;
#endif
    memset(&m_stPhotoDecodeInfo,0,sizeof(ST_PHOTO_DECODE_INFO));

    photoInfo.u16Pitch = MApp_Photo_GetInfo(E_PHOTO_INFO_PITCH);
    photoInfo.u16Width = MApp_Photo_GetInfo(E_PHOTO_INFO_WIDTH);
    photoInfo.u16Height = MApp_Photo_GetInfo(E_PHOTO_INFO_HEIGHT);

    m_stPhotoDecodeInfo.u16Height = photoInfo.u16Height;
    m_stPhotoDecodeInfo.u16Width = photoInfo.u16Width;

    enPhotoFmt = (EN_PHOTO_OUTPUT_FORMAT)MApp_Photo_GetInfo(E_PHOTO_INFO_OUTPUT_FORMAT);

    PHOTO_DISP_MSG(printf("@@@ Photo Pitch=%d , W=%d , Height=%d @@@\n",photoInfo.u16Pitch,photoInfo.u16Width,photoInfo.u16Height));

    // output format checking
    switch (enPhotoFmt)
    {
        case E_PHOTO_OUTPUT_ARGB8888:
        case E_PHOTO_OUTPUT_ARGB1555:
        case E_PHOTO_OUTPUT_YUV422:
            break;

        default:
            PHOTO_DISP_MSG(printf("[Photo Display] Color format not supported!\n"));
            return;
    }

    if(MApp_Photo_GetInfo(E_PHOTO_INFO_FILE_FORMAT) == E_PHOTO_FILE_GIF)
    {
        if(MApp_Photo_GetInfo(E_PHOTO_INFO_SLOT_NUM) == 0)
        {
            PHOTO_DISP_MSG(printf("[Photo Display] gif slot num is zero.\n"));
            return;
        }
        u32DecodeOutputBuffAddr = PHOTO_OUTPUT_BUFFER_ADDR +
             stu32DisplayedFrameIndex%MApp_Photo_GetInfo(E_PHOTO_INFO_SLOT_NUM)*MApp_Photo_GetInfo(E_PHOTO_INFO_FRAME_SIZE);
    }
    else
    {
        u32DecodeOutputBuffAddr = PHOTO_OUTPUT_BUFFER_ADDR;
    }

    PHOTO_DISP_MSG(printf("@@@ u32DecodeOutputBuffAddr=0x%lx @@@\n",u32DecodeOutputBuffAddr));

#if ENABLE_AUTO_ROTATION
    eOrientation = (EN_PHOTO_ORIENTATION)MApp_Photo_GetInfo(E_PHOTO_INFO_ORIENTATION);
    m_stPhotoDecodeInfo.enOrientation = eOrientation;
    if(eOrientation > E_PHOTO_ORIENT_ROTATE_0 && eOrientation < E_PHOTO_ORIENT_NOT_FOUND
        && MApp_Photo_GetInfo(E_PHOTO_INFO_FILE_FORMAT) == E_PHOTO_FILE_JPEG)
    {
        //Do rotate firstly from decode buffer to display src buffer
        EN_PHOTO_ROTATION enRotationOld;

        enRotationOld = m_enRotation;

        switch(eOrientation)
        {
            case E_PHOTO_ORIENT_MIRROR_LR:
                {
                    m_bMirrorX = TRUE;
                    m_bMirrorY = FALSE;
                    m_enRotation = EN_PHOTO_ROTATE_0;
                    break;
                }
            case E_PHOTO_ORIENT_ROTATE_180:
                {
                    m_bMirrorX = TRUE;
                    m_bMirrorY = TRUE;
                    m_enRotation = EN_PHOTO_ROTATE_0;
                    break;
                }
            case E_PHOTO_ORIENT_MIRROR_TB:
                {
                    m_bMirrorX = FALSE;
                    m_bMirrorY = TRUE;
                    m_enRotation = EN_PHOTO_ROTATE_0;
                    break;
                }
            case E_PHOTO_ORIENT_ROTATE_90_MIRROR_LR:
                {
                    //for our hw interface, it does mirror firstly, then rotate.
                    m_bMirrorX = FALSE;
                    m_bMirrorY = TRUE;
                    m_enRotation = EN_PHOTO_ROTATE_90;
                    break;
                }
            case E_PHOTO_ORIENT_E_ORIENT_ROTATE_90:
                {
                    m_bMirrorX = FALSE;
                    m_bMirrorY = FALSE;
                    m_enRotation = EN_PHOTO_ROTATE_90;
                    break;
                }
            case E_PHOTO_ORIENT_ROTATE_90_MIRROR_TB:
                {
                    //for our hw interface, it does mirror  firstly, then rotate.
                    m_bMirrorX = TRUE;
                    m_bMirrorY = FALSE;
                    m_enRotation = EN_PHOTO_ROTATE_90;
                    break;
                }
            case E_PHOTO_ORIENT_ROTATE_270:
                {
                    m_bMirrorX = TRUE;
                    m_bMirrorY = TRUE;
                    m_enRotation = EN_PHOTO_ROTATE_90;
                    break;
                }
        default:
                {
                    m_bMirrorX = FALSE;
                    m_bMirrorY = FALSE;
                    m_enRotation = EN_PHOTO_ROTATE_0;
                    break;
                }
        }

        PHOTO_DISP_MSG(printf("[Photo Display] m_bMirrorX:%x,m_bMirrorY:%x, Rotate:%x\n",
              m_bMirrorX, m_bMirrorY,m_enRotation));
        m_enZooming = EN_PHOTO_ZOOM_1;
        m_s16PhotoOffsetX = m_s16PhotoOffsetY = 0;
        m_u16PhotoSrcX = 0;
        m_u16PhotoSrcY = 0;
        m_u16PhotoSrcWidth = photoInfo.u16Width;
        m_u16PhotoSrcHeight = photoInfo.u16Height;

        m_bDoAutoRotateMirror = TRUE;

        if(!_MApp_Photo_ShowEffect())
        {
            m_enRotation = enRotationOld;
            PHOTO_DISP_MSG(printf("[Photo Display] Auto rotate fail.\n"));
            return;
        }
        photoInfo.u16Pitch = m_u16PhotoDstWidth;
        photoInfo.u16Width = m_u16PhotoDstWidth;
        photoInfo.u16Height = m_u16PhotoDstHeight;

        //copy back to decode buffer
        msAPI_MIU_Copy(
                PHOTO_DISPLAY_SRC_BUFFER_ADDR,
                u32DecodeOutputBuffAddr,
                (U32)2L * photoInfo.u16Pitch * photoInfo.u16Height,
                MIU_SDRAM2SDRAM);
    }
#endif

    m_bDoAutoRotateMirror = FALSE;
    m_bMirrorX = FALSE;
    m_bMirrorY = FALSE;

    if(photoInfo.u16Width == 0 || photoInfo.u16Height == 0)
    {
        PHOTO_DISP_MSG(printf("[Photo Display] MApp_Photo_Display() Error resolution.\n"));
        return;
    }

    if (bIsPreview)
    {
        U16 u16DstX, u16DstY, u16DstW, u16DstH;

#if (SHOW_PARTIALLY_DECODING_PHOTO)
        GFX_Buffer_Format eColorFmt;
        GEBitBltInfo BitbltInfo;
        GEPitBaseInfo PitBaseInfo;

        // calculate x, y, width, height
        if((U32)m_u16PhotoPreviewWidth * (U32)photoInfo.u16Height >
           (U32)m_u16PhotoPreviewHeight * (U32)photoInfo.u16Width)
        {
            u16DstW = (U16)((U32)photoInfo.u16Width * m_u16PhotoPreviewHeight /
                            photoInfo.u16Height);
            u16DstH = m_u16PhotoPreviewHeight;
        }
        else
        {
            u16DstH = (U16)((U32)photoInfo.u16Height * m_u16PhotoPreviewWidth /
                            photoInfo.u16Width);
            u16DstW = m_u16PhotoPreviewWidth;
        }

        u16DstX = 0 + (m_u16PhotoPreviewWidth - u16DstW) / 2;
        u16DstY = 0 + (m_u16PhotoPreviewHeight - u16DstH) / 2;

        if (enPhotoFmt == E_PHOTO_OUTPUT_ARGB8888)
        {
            eColorFmt = GFX_FMT_ARGB8888;
        }
        else if (enPhotoFmt == E_PHOTO_OUTPUT_ARGB1555)
        {
            eColorFmt = GFX_FMT_ARGB1555;
        }
        else
        {
            eColorFmt = GFX_FMT_YUV422;
        }

        // transfer color format and copy it to destination buffer (by using BitBlt)
        memset(&BitbltInfo, 0, sizeof(GEBitBltInfo));
        memset(&PitBaseInfo, 0, sizeof(GEPitBaseInfo));

        BitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;
        BitbltInfo.BmpFlag = GFXDRAW_FLAG_DEFAULT;
        BitbltInfo.dst_fm = GFX_FMT_YUV422;
        BitbltInfo.src_fm = eColorFmt;
        BitbltInfo.BitbltCoordinate.v2_x = 0;
        BitbltInfo.BitbltCoordinate.v2_y = 0;
        BitbltInfo.BitbltCoordinate.direction = 0;

        BitbltInfo.BitbltCoordinate.width = u16DstW & 0xfffe;
        BitbltInfo.BitbltCoordinate.height = u16DstH & 0xfffe;

        BitbltInfo.BitbltCoordinate.v0_x = u16DstX;
        BitbltInfo.BitbltCoordinate.v0_y = u16DstY;

        BitbltInfo.src_width = photoInfo.u16Width & 0xfffe;
        BitbltInfo.src_height = photoInfo.u16Height & 0xfffe;

        if (eColorFmt == GFX_FMT_ARGB8888)
        {
            PitBaseInfo.sb_pit = photoInfo.u16Pitch * 4;
        }
        else if (eColorFmt == GFX_FMT_YUV422 || eColorFmt == GFX_FMT_ARGB1555)
        {
            PitBaseInfo.sb_pit = photoInfo.u16Pitch * 2;
        }
        else
        {
            __ASSERT(0);
            return;
        }

        PitBaseInfo.db_pit = m_u16PhotoPreviewWidth * 2;
        PitBaseInfo.sb_base = u32DecodeOutputBuffAddr;
        PitBaseInfo.db_base = PHOTO_DISPLAY_BUFFER_ADDR;

        msAPI_OSD_SetClipWindow(
                BitbltInfo.BitbltCoordinate.v0_x,
                BitbltInfo.BitbltCoordinate.v0_y,
                BitbltInfo.BitbltCoordinate.v0_x + BitbltInfo.BitbltCoordinate.width,
                BitbltInfo.BitbltCoordinate.v0_y + BitbltInfo.BitbltCoordinate.height);

        MApi_GFX_EnableAlphaBlending(FALSE);
        msAPI_GE_SetNearestMode(FALSE);

        msAPI_GE_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_PC, GFX_YUV_OUT_255, GFX_YUV_IN_255, GFX_YUV_YUYV, GFX_YUV_YUYV);

        msAPI_GE_SetPatchMode(TRUE);
        msAPI_GE_BitBlt(&BitbltInfo, &PitBaseInfo);
        // after BitBlt, flush cmd
        MApi_GFX_FlushQueue();
        msAPI_GE_SetPatchMode(FALSE);

#else // #if (SHOW_PARTIALLY_DECODING_PHOTO)
        if (enPhotoFmt == E_PHOTO_OUTPUT_ARGB8888)
        {
            // color format transfer
            _MApp_Photo_Display_ColorFmtTransfer(
                    photoInfo.u16Pitch,
                    photoInfo.u16Height,
                    u32DecodeOutputBuffAddr,
                    GFX_FMT_ARGB8888,
                    PHOTO_DISPLAY_BUFFER_ADDR,
                    GFX_FMT_YUV422);
        }
        else if (enPhotoFmt == E_PHOTO_OUTPUT_ARGB1555)
        {
            // color format transfer
            _MApp_Photo_Display_ColorFmtTransfer(
                    photoInfo.u16Pitch,
                    photoInfo.u16Height,
                    u32DecodeOutputBuffAddr,
                    GFX_FMT_ARGB1555,
                    PHOTO_DISPLAY_BUFFER_ADDR,
                    GFX_FMT_YUV422);
        }
        else
        {
            // copy data from PHOTO_OUTPUT_BUFFER_ADDR to PHOTO_DISPLAY_BUFFER_ADDR
            _MApp_Photo_Display_ColorFmtTransfer(
                    photoInfo.u16Pitch,
                    photoInfo.u16Height,
                    u32DecodeOutputBuffAddr,
                    GFX_FMT_YUV422,
                    PHOTO_DISPLAY_BUFFER_ADDR,
                    GFX_FMT_YUV422);
        }

        // calculate x, y, width, height
        if((U32)u16ViewWinWidth * (U32)photoInfo.u16Height >
           (U32)u16ViewWinHeight * (U32)photoInfo.u16Width)
        {
            u16DstW = (U16)((U32)photoInfo.u16Width * u16ViewWinHeight /
                            photoInfo.u16Height);
            u16DstH = u16ViewWinHeight;
        }
        else
        {
            u16DstH = (U16)((U32)photoInfo.u16Height * u16ViewWinWidth /
                            photoInfo.u16Width);
            u16DstW = u16ViewWinWidth;
        }

        u16DstX = u16ViewWinX + (u16ViewWinWidth - u16DstW) / 2;
        u16DstY = u16ViewWinY + (u16ViewWinHeight - u16DstH) / 2;

    #if (MEMORY_MAP <= MMAP_32MB)
        //printf("Set XC = DNR_Prev %X %X\n", SCALER_DNR_BUF_PREV_ADR, SCALER_DNR_BUF_PREV_LEN);
        //assign smaller buffer for scaler.
        MApi_XC_SetFrameBufferAddress(SCALER_DNR_BUF_PREV_ADR, SCALER_DNR_BUF_PREV_LEN, MAIN_WINDOW);
        MApi_XC_SetAutoPreScaling(ENABLE, MAIN_WINDOW);
        MApi_XC_EnableFrameBufferLess(DISABLE);
    #endif

        _MApp_Photo_SetScalarVOP2Display(
                0,  0, photoInfo.u16Width, photoInfo.u16Height,
                u16DstX, u16DstY, u16DstW, u16DstH,
                PHOTO_DISPLAY_BUFFER_ADDR,
                photoInfo.u16Pitch, photoInfo.u16Height);
#endif // #if (SHOW_PARTIALLY_DECODING_PHOTO)
    }
    else
    {
        if(bMPODisplayEnabled)
        {
            MApp_Photo_InitFullScreenDisplay();
        }
        if (enPhotoFmt == E_PHOTO_OUTPUT_ARGB8888)
        {
            _MApp_Photo_SlideShow(GFX_FMT_ARGB8888, &photoInfo, m_SlideShowEffect);
        }
        else if (enPhotoFmt == E_PHOTO_OUTPUT_ARGB1555)
        {
            _MApp_Photo_SlideShow(GFX_FMT_ARGB1555, &photoInfo, m_SlideShowEffect);
        }
        else
        {
            _MApp_Photo_SlideShow(GFX_FMT_YUV422, &photoInfo, m_SlideShowEffect);
        }
    }
}

void MApp_Photo_GIFDecodeDone(BOOLEAN bIsAllFrameDecodeDone)
{
    if(bIsAllFrameDecodeDone)
    {
        PHOTO_DISP_MSG(printf("[PHOTO] Gif all decode Done\n"));
    }
    stbIsAllFrameDecodeDone = bIsAllFrameDecodeDone;
}

BOOLEAN  MApp_Photo_GIFIsDisplayDone(void)
{
    return stbIsAllFrameDisplayedDone;
}

void MApp_Photo_GIFDisplay(BOOLEAN bIsPreview)
{
    U32 u32DecodedFrameIndex = MApp_Photo_GetInfo(E_PHOTO_INFO_DECODED_FRAME_INDEX);

    if(u32DecodedFrameIndex == _U32_MAX || MApp_Photo_GIFIsDisplayDone())
        return;

    //display when 1. decode done or 2. decode index > (display index + 1) because gif animation decode maybe refer former 2 frames.
    if(stbIsAllFrameDecodeDone ||
        ((u32DecodedFrameIndex >= MAX_GIF_BUFF_DISPLAY) && (u32DecodedFrameIndex > (stu32DisplayedFrameIndex + 1))))
    {
        U32 u32DelayTime = MApp_Photo_GetFrameDelayTime(u32DecodedFrameIndex);
        MApp_Photo_Display(bIsPreview);
        MApp_Photo_UpdateDisplayedFrameIndex(stu32DisplayedFrameIndex);
        PHOTO_DISP_MSG(printf("[PHOTO] display frame:%lu, delay 0x%lxms\n", stu32DisplayedFrameIndex, u32DelayTime));
        stu32DisplayedFrameIndex++;
        if(u32DelayTime != _U32_MAX && u32DelayTime < 1000)
        {
            if(u32DelayTime <=10)
            {
                u32DelayTime = 20;
            }
            msAPI_Timer_Delayms(u32DelayTime);
        }
    }
    if(stbIsAllFrameDecodeDone && stu32DisplayedFrameIndex > MApp_Photo_GetInfo(E_PHOTO_INFO_DECODED_FRAME_INDEX))
    {
        PHOTO_DISP_MSG(printf("[PHOTO] display Done\n"));
        stbIsAllFrameDisplayedDone = TRUE;
    }
}

void MApp_Photo_GIFResetDisplay(void)
{
    stu32DisplayedFrameIndex = 0;
    stbIsAllFrameDecodeDone = FALSE;
    stbIsAllFrameDisplayedDone = FALSE;
}


void MApp_Photo_MPODisplay(BOOLEAN bIsPreview)
{
    SlideShowPhotoInfo photoInfo;
    EN_PHOTO_OUTPUT_FORMAT enPhotoFmt;
    U32 u32DecodeOutputBuffAddr;

    photoInfo.u16Pitch = MApp_Photo_GetInfo(E_PHOTO_INFO_PITCH);
    photoInfo.u16Width = MApp_Photo_GetInfo(E_PHOTO_INFO_WIDTH);
    photoInfo.u16Height = MApp_Photo_GetInfo(E_PHOTO_INFO_HEIGHT);

    if(photoInfo.u16Width == 0 || photoInfo.u16Height == 0)
    {
        PHOTO_DISP_MSG(printf("[Photo Display] MApp_Photo_MPODisplay() Error resolution.\n"));
        return;
    }

    enPhotoFmt = (EN_PHOTO_OUTPUT_FORMAT)MApp_Photo_GetInfo(E_PHOTO_INFO_OUTPUT_FORMAT);

    // output format checking
    switch (enPhotoFmt)
    {
        case E_PHOTO_OUTPUT_ARGB8888:
        case E_PHOTO_OUTPUT_ARGB1555:
        case E_PHOTO_OUTPUT_YUV422:
            break;

        default:
            PHOTO_DISP_MSG(printf("[Photo Display] Color format not supported!\n"));
            return;
    }

    u32DecodeOutputBuffAddr = PHOTO_OUTPUT_BUFFER_ADDR;


    m_bDoAutoRotateMirror = FALSE;
    m_bMirrorX = FALSE;
    m_bMirrorY = FALSE;


    if (bIsPreview)
    {
        U16 u16DstX, u16DstY, u16DstW, u16DstH;

#if (SHOW_PARTIALLY_DECODING_PHOTO)
        GFX_Buffer_Format eColorFmt;
        GEBitBltInfo BitbltInfo;
        GEPitBaseInfo PitBaseInfo;

        // calculate x, y, width, height
        if((U32)m_u16PhotoPreviewWidth * (U32)photoInfo.u16Height >
           (U32)m_u16PhotoPreviewHeight * (U32)photoInfo.u16Width)
        {
            u16DstW = (U16)((U32)photoInfo.u16Width * m_u16PhotoPreviewHeight /
                            photoInfo.u16Height);
            u16DstH = m_u16PhotoPreviewHeight;
        }
        else
        {
            u16DstH = (U16)((U32)photoInfo.u16Height * m_u16PhotoPreviewWidth /
                            photoInfo.u16Width);
            u16DstW = m_u16PhotoPreviewWidth;
        }

        u16DstX = 0 + (m_u16PhotoPreviewWidth - u16DstW) / 2;
        u16DstY = 0 + (m_u16PhotoPreviewHeight - u16DstH) / 2;

        if (enPhotoFmt == E_PHOTO_OUTPUT_ARGB8888)
        {
            eColorFmt = GFX_FMT_ARGB8888;
        }
        else if (enPhotoFmt == E_PHOTO_OUTPUT_ARGB1555)
        {
            eColorFmt = GFX_FMT_ARGB1555;
        }
        else
        {
            eColorFmt = GFX_FMT_YUV422;
        }

        // transfer color format and copy it to destination buffer (by using BitBlt)
        memset(&BitbltInfo, 0, sizeof(GEBitBltInfo));
        memset(&PitBaseInfo, 0, sizeof(GEPitBaseInfo));

        BitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;
        BitbltInfo.BmpFlag = GFXDRAW_FLAG_DEFAULT;
        BitbltInfo.dst_fm = GFX_FMT_YUV422;
        BitbltInfo.src_fm = eColorFmt;
        BitbltInfo.BitbltCoordinate.v2_x = 0;
        BitbltInfo.BitbltCoordinate.v2_y = 0;
        BitbltInfo.BitbltCoordinate.direction = 0;

        BitbltInfo.BitbltCoordinate.width = u16DstW & 0xfffe;
        BitbltInfo.BitbltCoordinate.height = u16DstH & 0xfffe;

        BitbltInfo.BitbltCoordinate.v0_x = u16DstX;
        BitbltInfo.BitbltCoordinate.v0_y = u16DstY;

        BitbltInfo.src_width = photoInfo.u16Width & 0xfffe;
        BitbltInfo.src_height = photoInfo.u16Height & 0xfffe;

        if (eColorFmt == GFX_FMT_ARGB8888)
        {
            PitBaseInfo.sb_pit = photoInfo.u16Pitch * 4;
        }
        else if (eColorFmt == GFX_FMT_YUV422 || eColorFmt == GFX_FMT_ARGB1555)
        {
            PitBaseInfo.sb_pit = photoInfo.u16Pitch * 2;
        }

        PitBaseInfo.db_pit = m_u16PhotoPreviewWidth * 2;
        PitBaseInfo.sb_base = u32DecodeOutputBuffAddr;
        PitBaseInfo.db_base = PHOTO_DISPLAY_BUFFER_ADDR;

        msAPI_OSD_SetClipWindow(
                BitbltInfo.BitbltCoordinate.v0_x,
                BitbltInfo.BitbltCoordinate.v0_y,
                BitbltInfo.BitbltCoordinate.v0_x + BitbltInfo.BitbltCoordinate.width,
                BitbltInfo.BitbltCoordinate.v0_y + BitbltInfo.BitbltCoordinate.height);

        msAPI_GE_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_PC, GFX_YUV_OUT_255, GFX_YUV_IN_255, GFX_YUV_YUYV, GFX_YUV_YUYV);

        msAPI_GE_SetPatchMode(TRUE);
        msAPI_GE_BitBlt(&BitbltInfo, &PitBaseInfo);
        // after BitBlt, flush cmd
        MApi_GFX_FlushQueue();
        msAPI_GE_SetPatchMode(FALSE);

#else // #if (SHOW_PARTIALLY_DECODING_PHOTO)
        if (enPhotoFmt == E_PHOTO_OUTPUT_ARGB8888)
        {
            // color format transfer
            _MApp_Photo_Display_ColorFmtTransfer(
                    photoInfo.u16Pitch,
                    photoInfo.u16Height,
                    u32DecodeOutputBuffAddr,
                    GFX_FMT_ARGB8888,
                    PHOTO_DISPLAY_BUFFER_ADDR,
                    GFX_FMT_YUV422);
        }
        else if (enPhotoFmt == E_PHOTO_OUTPUT_ARGB1555)
        {
            // color format transfer
            _MApp_Photo_Display_ColorFmtTransfer(
                    photoInfo.u16Pitch,
                    photoInfo.u16Height,
                    u32DecodeOutputBuffAddr,
                    GFX_FMT_ARGB1555,
                    PHOTO_DISPLAY_BUFFER_ADDR,
                    GFX_FMT_YUV422);
        }
        else
        {
            // copy data from PHOTO_OUTPUT_BUFFER_ADDR to PHOTO_DISPLAY_BUFFER_ADDR
            _MApp_Photo_Display_ColorFmtTransfer(
                    photoInfo.u16Pitch,
                    photoInfo.u16Height,
                    u32DecodeOutputBuffAddr,
                    GFX_FMT_YUV422,
                    PHOTO_DISPLAY_BUFFER_ADDR,
                    GFX_FMT_YUV422);
        }

        // calculate x, y, width, height
        if((U32)u16ViewWinWidth * (U32)photoInfo.u16Height >
           (U32)u16ViewWinHeight * (U32)photoInfo.u16Width)
        {
            u16DstW = (U16)((U32)photoInfo.u16Width * u16ViewWinHeight /
                            photoInfo.u16Height);
            u16DstH = u16ViewWinHeight;
        }
        else
        {
            u16DstH = (U16)((U32)photoInfo.u16Height * u16ViewWinWidth /
                            photoInfo.u16Width);
            u16DstW = u16ViewWinWidth;
        }

        u16DstX = u16ViewWinX + (u16ViewWinWidth - u16DstW) / 2;
        u16DstY = u16ViewWinY + (u16ViewWinHeight - u16DstH) / 2;

        _MApp_Photo_SetScalarVOP2Display(
                0,  0, photoInfo.u16Width, photoInfo.u16Height,
                u16DstX, u16DstY, u16DstW, u16DstH,
                PHOTO_DISPLAY_BUFFER_ADDR,
                photoInfo.u16Pitch, photoInfo.u16Height);
#endif // #if (SHOW_PARTIALLY_DECODING_PHOTO)
    }
    else
    {
        GEBitBltInfo stBitbltInfo;
        GEPitBaseInfo stPitBaseInfo;
        U16 u16DstW, u16DstH;

        if(PHOTO_DISPLAY_MPO_BUFFER_ADDR == 0)
        {
            printf("PHOTO_DISPLAY_MPO_BUFFER_ADDR is invalid!!\n");
            return;
        }

        if (MApp_Photo_GetInfo(E_PHOTO_INFO_DECODED_FRAME_INDEX) == 0)
        {
            PHOTO_DISP_MSG(printf("[PHOTO] Blt frame:0\n"));

            msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);

            //blt first frame to dst buffer
            // 1. Clear internal buffer to black.
            msAPI_GE_ClearFrameBufferByWord((U32)PHOTO_DISPLAY_MPO_BUFFER_ADDR,
                                           PHOTO_DISPLAY_MPO_BUFFER_SIZE,
                                          0x80008000);
            // after clear frame buffer, flush cmd
            MApi_GFX_FlushQueue();
            //printf("\n  msAPI_GE_ClearFrameBufferByWord , PHOTO_DISPLAY_SRC_BUFFER_SIZE=%x\n ", PHOTO_DISPLAY_SRC_BUFFER_SIZE);

            // 2. Stretch source to internal buffer.
            // BitBlt information settings
            // Calculate the destination dimension.
            if((U32)g_IPanel.Width() * (U32)photoInfo.u16Height >
               (U32)PANEL_HEIGHT * (U32)photoInfo.u16Width)
            {
                u16DstW = (U16)((U32)photoInfo.u16Width * PANEL_HEIGHT /
                                photoInfo.u16Height);
                u16DstH = PANEL_HEIGHT;
            }
            else
            {
                u16DstH = (U16)((U32)photoInfo.u16Height * (U32)g_IPanel.Width() /
                                photoInfo.u16Width);
                u16DstW = (U16)g_IPanel.Width();
            }
            stBitbltInfo.BitbltCoordinate.v0_x = (((U16)g_IPanel.Width() - u16DstW) / 2) & (0xFFFFFFFE);
            stBitbltInfo.BitbltCoordinate.v0_y = (PANEL_HEIGHT - u16DstH) / 2;

            //printf(" \n u16DstW=%x,  u16DstH=%x",u16DstW, u16DstH );
            //printf(" \n PHOTO_ADJUSTED_PANEL_WIDTH=%x,  PANEL_HEIGHT=%x",PHOTO_ADJUSTED_PANEL_WIDTH, PANEL_HEIGHT );

            stBitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;
            stBitbltInfo.BmpFlag = GFXDRAW_FLAG_DEFAULT;
            stBitbltInfo.BitbltCoordinate.direction = 0;

            stBitbltInfo.BitbltCoordinate.width = u16DstW;
            stBitbltInfo.BitbltCoordinate.height = u16DstH;
            stBitbltInfo.BitbltCoordinate.v2_x = 0; //src
            stBitbltInfo.BitbltCoordinate.v2_y = 0;
            stBitbltInfo.src_width= photoInfo.u16Width & 0xFFFE;
            stBitbltInfo.src_height = photoInfo.u16Height & 0xFFFE;
            stBitbltInfo.src_fm = GFX_FMT_YUV422;
            stBitbltInfo.dst_fm = GFX_FMT_YUV422;

            m_u16PhotoSrcX = stBitbltInfo.BitbltCoordinate.v0_x;
            m_u16PhotoSrcY = stBitbltInfo.BitbltCoordinate.v0_y;
            m_u16PhotoSrcWidth = u16DstW;
            m_u16PhotoSrcHeight = u16DstH;

            m_u16PhotoDstX = stBitbltInfo.BitbltCoordinate.v0_x;
            m_u16PhotoDstY = stBitbltInfo.BitbltCoordinate.v0_y;
            m_u16PhotoDstWidth = u16DstW;
            m_u16PhotoDstHeight = u16DstH;

            //printf(" \n pit=%x,  w=%x  ,  PHOTO_ADJUSTED_PANEL_WIDTH=%x",pPhotoInfo->u16Pitch, pPhotoInfo->u16Width , PHOTO_ADJUSTED_PANEL_WIDTH);

            stPitBaseInfo.sb_pit = photoInfo.u16Pitch * 2;
            stPitBaseInfo.db_pit = PHOTO_ADJUSTED_PANEL_WIDTH * 2;  // 2 bytes per pixel
            stPitBaseInfo.sb_base = u32DecodeOutputBuffAddr;
            stPitBaseInfo.db_base = PHOTO_DISPLAY_MPO_BUFFER_ADDR;

            msAPI_OSD_SetClipWindow(0, 0, PHOTO_ADJUSTED_PANEL_WIDTH, PANEL_HEIGHT);

            MApi_GFX_EnableAlphaBlending(FALSE);
            msAPI_GE_SetNearestMode(FALSE);
            msAPI_GE_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_PC, GFX_YUV_OUT_255, GFX_YUV_IN_255, GFX_YUV_YUYV, GFX_YUV_YUYV);

            msAPI_GE_BitBlt(&stBitbltInfo, &stPitBaseInfo);
            // after BitBlt, flush cmd
            MApi_GFX_FlushQueue();
            //update display frame index
            MApp_Photo_UpdateDisplayedFrameIndex(0);
        }
        else
        {
            PHOTO_DISP_MSG(printf("[PHOTO] Blt frame:1\n"));
            if(!bMPODisplayEnabled)
            {
                PHOTO_DISP_MSG(printf("[PHOTO] Init mvop and scaler for mpo\n"));
                // after clear frame buffer, flush cmd
                MApi_GFX_FlushQueue();

                bMPODisplayEnabled = TRUE;
                _MApp_Photo_SetScalarVOP2Display(
                        0,
                        0,
                        PANEL_WIDTH,
                        (PANEL_HEIGHT + PANEL_HEIGHT +45),
                        0,
                        0,
                        PANEL_WIDTH,
                        (PANEL_HEIGHT + PANEL_HEIGHT +45),
                        PHOTO_DISPLAY_MPO_BUFFER_ADDR,
                        PHOTO_ADJUSTED_PANEL_WIDTH,
                        (PANEL_HEIGHT + PANEL_HEIGHT +45));
            }
            // Stretch second frame to mpo buffer.
            // BitBlt information settings
            // Calculate the destination dimension.
            if((U32)g_IPanel.Width() * (U32)photoInfo.u16Height >
               (U32)PANEL_HEIGHT * (U32)photoInfo.u16Width)
            {
                u16DstW = (U16)((U32)photoInfo.u16Width * PANEL_HEIGHT /
                                photoInfo.u16Height);
                u16DstH = PANEL_HEIGHT;
            }
            else
            {
                u16DstH = (U16)((U32)photoInfo.u16Height * (U32)g_IPanel.Width() /
                                photoInfo.u16Width);
                u16DstW = (U16)g_IPanel.Width();
            }
            stBitbltInfo.BitbltCoordinate.v0_x = (((U16)g_IPanel.Width() - u16DstW) / 2) & (0xFFFFFFFE);
            stBitbltInfo.BitbltCoordinate.v0_y = (PANEL_HEIGHT - u16DstH) / 2;

            //printf(" \n u16DstW=%x,  u16DstH=%x",u16DstW, u16DstH );
            //printf(" \n PHOTO_ADJUSTED_PANEL_WIDTH=%x,  PANEL_HEIGHT=%x",PHOTO_ADJUSTED_PANEL_WIDTH, PANEL_HEIGHT );

            stBitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;
            stBitbltInfo.BmpFlag = GFXDRAW_FLAG_DEFAULT;
            stBitbltInfo.BitbltCoordinate.direction = 0;

            stBitbltInfo.BitbltCoordinate.width = u16DstW;
            stBitbltInfo.BitbltCoordinate.height = u16DstH;
            stBitbltInfo.BitbltCoordinate.v2_x = 0; //src
            stBitbltInfo.BitbltCoordinate.v2_y = 0;
            stBitbltInfo.src_width= photoInfo.u16Width & 0xFFFE;
            stBitbltInfo.src_height = photoInfo.u16Height & 0xFFFE;
            stBitbltInfo.src_fm = GFX_FMT_YUV422;
            stBitbltInfo.dst_fm = GFX_FMT_YUV422;

            m_u16PhotoSrcX = stBitbltInfo.BitbltCoordinate.v0_x;
            m_u16PhotoSrcY = stBitbltInfo.BitbltCoordinate.v0_y;
            m_u16PhotoSrcWidth = u16DstW;
            m_u16PhotoSrcHeight = u16DstH;

            m_u16PhotoDstX = stBitbltInfo.BitbltCoordinate.v0_x;
            m_u16PhotoDstY = stBitbltInfo.BitbltCoordinate.v0_y;
            m_u16PhotoDstWidth = u16DstW;
            m_u16PhotoDstHeight = u16DstH;

            //printf(" \n pit=%x,  w=%x  ,  PHOTO_ADJUSTED_PANEL_WIDTH=%x",pPhotoInfo->u16Pitch, pPhotoInfo->u16Width , PHOTO_ADJUSTED_PANEL_WIDTH);

            stPitBaseInfo.sb_pit = photoInfo.u16Pitch * 2;
            stPitBaseInfo.db_pit = PHOTO_ADJUSTED_PANEL_WIDTH * 2;  // 2 bytes per pixel
            stPitBaseInfo.sb_base = u32DecodeOutputBuffAddr;
            stPitBaseInfo.db_base = PHOTO_DISPLAY_MPO_BUFFER_ADDR+PHOTO_ADJUSTED_PANEL_WIDTH*(PANEL_HEIGHT+45)*2;

            msAPI_OSD_SetClipWindow(0, 0, PHOTO_ADJUSTED_PANEL_WIDTH, PANEL_HEIGHT);

            MApi_GFX_EnableAlphaBlending(FALSE);
            msAPI_GE_SetNearestMode(FALSE);
            msAPI_GE_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_PC, GFX_YUV_OUT_255, GFX_YUV_IN_255, GFX_YUV_YUYV, GFX_YUV_YUYV);

            msAPI_GE_BitBlt(&stBitbltInfo, &stPitBaseInfo);
            // after BitBlt, flush cmd
            MApi_GFX_FlushQueue();
            msAPI_Scaler_SetBlueScreen(DISABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
            MApp_Photo_UpdateDisplayedFrameIndex(1);
        }
    }
}

void MApp_Photo_Display_Stop(void)
{
#if SAVE_BW_PHOTO_SLIDE_SHOW
    if (MApi_XC_IsFreezeImg(MAIN_WINDOW))
    {
        MApi_XC_FreezeImg(FALSE, MAIN_WINDOW);
    }
#endif

    msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);

    // Disable scaler periodic task
    MAPI_XC_MUX_ONOFF_PERIODIC_HANDLER(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), DISABLE);

    MDrv_MVOP_Enable(FALSE);

#if (MirrorEnable)
    MApp_MVOP_SetMirrorMode(DISABLE);
#endif

#if (ENABLE_MIU_1 == ENABLE)
    MDrv_MVOP_MiuSwitch(1);
#endif
    MApp_Photo_GIFResetDisplay();
    m_bFLG_PREVIEW = FALSE;
    bMPODisplayEnabled = FALSE;
    memset(&m_stPhotoDecodeInfo,0,sizeof(ST_PHOTO_DECODE_INFO));
}

#if defined(PHOTO_SLIDE_SHOW_EFFECT) && (PHOTO_SLIDE_SHOW_EFFECT == 1)
void MApp_Photo_GetImageCoordinatesOnScreen(U16 *pu16X, U16 *pu16Y, U16 *pu16W, U16 *pu16H)
{
    if (pu16X)
        *pu16X = m_u16PhotoDstX;

    if (pu16Y)
        *pu16Y = m_u16PhotoDstY;

    if (pu16W)
        *pu16W = m_u16PhotoDstWidth;

    if (pu16H)
        *pu16H = m_u16PhotoDstHeight;
}

void MApp_Photo_GetImageCoordinatesOnSource(U16 *pu16X, U16 *pu16Y, U16 *pu16W, U16 *pu16H)
{
    if (pu16X)
        *pu16X = m_u16PhotoSrcX;

    if (pu16Y)
        *pu16Y = m_u16PhotoSrcY;

    if (pu16W)
        *pu16W = m_u16PhotoSrcWidth;

    if (pu16H)
        *pu16H = m_u16PhotoSrcHeight;
}
#endif // #if defined(PHOTO_SLIDE_SHOW_EFFECT) && (PHOTO_SLIDE_SHOW_EFFECT == 1)

static void MApp_Photo_AdjustSrcWinSize(void)
{
    S8 s8ZoomingRatio;
    S16 s16CenterX, s16CenterY; // it's critical to use signed variable because the value can be negative
    U16 u16SrcWinX, u16SrcWinY, u16SrcWinW, u16SrcWinH;

    u16SrcWinX = stPhotoInstanceInfo.stSrcImg.u16RectX;;
    u16SrcWinY = stPhotoInstanceInfo.stSrcImg.u16RectY;;
    u16SrcWinW = stPhotoInstanceInfo.stSrcImg.u16RectW;;
    u16SrcWinH = stPhotoInstanceInfo.stSrcImg.u16RectH;;

    s16CenterX = stPhotoInstanceInfo.stResizedImg.u16RectX + (stPhotoInstanceInfo.stResizedImg.u16RectW >> 1);
    s16CenterY = stPhotoInstanceInfo.stResizedImg.u16RectY + (stPhotoInstanceInfo.stResizedImg.u16RectH >> 1);

    PHOTO_DISP_MSG(printf("oz: %u, nz: %u, rz: %d\n", stPhotoInstanceInfo.enZooming, stPhotoInstanceInfo.enZoomingNew, stPhotoInstanceInfo.enZoomingNew - EN_PHOTO_ZOOM_1));
    PHOTO_DISP_MSG(printf("cx: %d, cy: %d\n", s16CenterX, s16CenterY));
    PHOTO_DISP_MSG(printf("sx: %d, sy: %d, sw: %d, sh: %d\n", u16SrcWinX, u16SrcWinY, u16SrcWinW, u16SrcWinH));
    PHOTO_DISP_MSG(printf("ox: %u, oy: %u, ow: %u, oh: %u\n",
            stPhotoInstanceInfo.stResizedImg.u16RectX,
            stPhotoInstanceInfo.stResizedImg.u16RectY,
            stPhotoInstanceInfo.stResizedImg.u16RectW,
            stPhotoInstanceInfo.stResizedImg.u16RectH));

    s8ZoomingRatio = stPhotoInstanceInfo.enZoomingNew - EN_PHOTO_ZOOM_1;
    if (s8ZoomingRatio < 0)
    {
         // zooming to 1/2, 1/4, 1/8, not calculate here
        return;
    }

    // re-calculate x, y, w, h
    stPhotoInstanceInfo.stResizedImg.u16RectW = u16SrcWinW >> s8ZoomingRatio;
    stPhotoInstanceInfo.stResizedImg.u16RectH = u16SrcWinH >> s8ZoomingRatio;
    s16CenterX -= (stPhotoInstanceInfo.stResizedImg.u16RectW >> 1);
    s16CenterY -= (stPhotoInstanceInfo.stResizedImg.u16RectH >> 1);

    // re-calculate src window coordinates by checking if any boundary hit or not
    if (s16CenterX < 0) // left boundary hit
    {
        s16CenterX = u16SrcWinX;
    }
    else
    {
        if (((U16)s16CenterX + stPhotoInstanceInfo.stResizedImg.u16RectW) >
                (u16SrcWinX + u16SrcWinW)) // right boundary hit
        {
            s16CenterX = u16SrcWinX + u16SrcWinW - stPhotoInstanceInfo.stResizedImg.u16RectW;
        }
    }

    if (s16CenterY < 0) // top boundary hit
    {
        s16CenterY = u16SrcWinY;
    }
    else
    {
        if (((U16)s16CenterY + stPhotoInstanceInfo.stResizedImg.u16RectH) >
                (u16SrcWinY + u16SrcWinH)) // bottom boundary hit
        {
            s16CenterY = u16SrcWinY + u16SrcWinH - stPhotoInstanceInfo.stResizedImg.u16RectH;
        }
    }

    // assign new coordinates
    stPhotoInstanceInfo.stResizedImg.u16RectX = (U16)s16CenterX;
    stPhotoInstanceInfo.stResizedImg.u16RectY = (U16)s16CenterY;

    PHOTO_DISP_MSG(printf("nx: %u, ny: %u, nw: %u, nh: %u\n",
            stPhotoInstanceInfo.stResizedImg.u16RectX,
            stPhotoInstanceInfo.stResizedImg.u16RectY,
            stPhotoInstanceInfo.stResizedImg.u16RectW,
            stPhotoInstanceInfo.stResizedImg.u16RectH));
}

static void MApp_Photo_AdjustViewWinSize(void)
{
    U32 u32RatioW, u32RatioH;
    U16 u16W, u16H;
    S8 s8ZoomingRatio;

    PHOTO_DISP_MSG(printf("view res: %u\n", stPhotoInstanceInfo.enResize));

    // resize effect according to user request
    switch (stPhotoInstanceInfo.enResize)
    {
        case EN_PHOTO_IMAGE_SIZE:
        case EN_PHOTO_FIT_BOUNDARY:
            if ((stPhotoInstanceInfo.enRotation == EN_PHOTO_ROTATE_90) || (stPhotoInstanceInfo.enRotation == EN_PHOTO_ROTATE_270))
            {
                u16W = stPhotoInstanceInfo.stResizedImg.u16RectH;
                u16H = stPhotoInstanceInfo.stResizedImg.u16RectW;
            }
            else
            {
                u16W = stPhotoInstanceInfo.stResizedImg.u16RectW;
                u16H = stPhotoInstanceInfo.stResizedImg.u16RectH;
            }

            s8ZoomingRatio = stPhotoInstanceInfo.enZoomingNew - EN_PHOTO_ZOOM_1;
            if (s8ZoomingRatio < 0)
            {
                s8ZoomingRatio = 0;
            }
            u16W <<= s8ZoomingRatio;
            u16H <<= s8ZoomingRatio;
            u32RatioW = ((U32)stPhotoInstanceInfo.stDstBuff.u16RectW * 100) / u16W;
            u32RatioH = ((U32)stPhotoInstanceInfo.stDstBuff.u16RectH * 100) / u16H;
            PHOTO_DISP_MSG(printf("sw: %u, sh: %u, dw: %u, dh: %u, rw: %u, rh: %u\n", u16W, u16H, stPhotoInstanceInfo.stDstBuff.u16RectW, stPhotoInstanceInfo.stDstBuff.u16RectH, u32RatioW, u32RatioH));

            if ((stPhotoInstanceInfo.enResize == EN_PHOTO_IMAGE_SIZE) && (u32RatioW >= 100) && (u32RatioH >= 100))
            {
                stPhotoInstanceInfo.stOutputImg.u16RectW = u16W;
                stPhotoInstanceInfo.stOutputImg.u16RectH = u16H;

                PHOTO_DISP_MSG(printf("ow: %u, oh: %u\n", stPhotoInstanceInfo.stOutputImg.u16RectW, stPhotoInstanceInfo.stOutputImg.u16RectH));
                break;
            }
            // 2 conditions we will reszie the output image
            // 1. if exact jpeg image size is specified but the view window ins't big enough
            // 2. if enlarge or shrink to find best fit to height or width
            if (u32RatioW > u32RatioH)
            {
                // fit to height
                stPhotoInstanceInfo.stOutputImg.u16RectW = (u32RatioH *u16W) / 100;
                stPhotoInstanceInfo.stOutputImg.u16RectH = (u32RatioH *u16H) / 100;
                stPhotoInstanceInfo.u16ResizeRatio = u32RatioH;
            }
            else
            {
                // fit to width
                stPhotoInstanceInfo.stOutputImg.u16RectH = (u32RatioW *u16H) / 100;
                stPhotoInstanceInfo.stOutputImg.u16RectW = (u32RatioW *u16W) / 100;
                stPhotoInstanceInfo.u16ResizeRatio = u32RatioW;
            }

            PHOTO_DISP_MSG(printf("ow: %u, oh: %u, rr: %u\n", stPhotoInstanceInfo.stOutputImg.u16RectW, stPhotoInstanceInfo.stOutputImg.u16RectH, stPhotoInstanceInfo.u16ResizeRatio));
            break;
        case EN_PHOTO_FIT_VIEW_WINDOW:
        default:
            break;
    }

}

static void MApp_Photo_ReAdjustSrcWinViewWinSize(void)
{
    U32 u32RatioW, u32RatioH;
    S8 s8ZoomingRatio = stPhotoInstanceInfo.enZoomingNew - EN_PHOTO_ZOOM_1;
    U8 u8TimeW = 0, u8TimeH = 0;
    S16 s16CenterX, s16CenterY; // it's critical to use signed variable because the value can be negative
    U16 u16SrcWinX, u16SrcWinY, u16SrcWinW, u16SrcWinH;

    u32RatioW = ((U32)stPhotoInstanceInfo.stOutputImg.u16RectW * 100) / stPhotoInstanceInfo.stDstBuff.u16RectW;
    u32RatioH = ((U32)stPhotoInstanceInfo.stOutputImg.u16RectH * 100) / stPhotoInstanceInfo.stDstBuff.u16RectH;

    PHOTO_DISP_MSG(printf("re src, view win: orw: %u, orh: %u, zr: %d\n", u32RatioW, u32RatioH, s8ZoomingRatio));

    if (s8ZoomingRatio <= 0)
    {
        // this function don't apply to zooming 1, 1/2, 1/4, 1/8
        return;
    }

    while (s8ZoomingRatio)
    {
        if ((u32RatioW << 1) < 100)
        {
            // there is room for widht of src win and view win to be doubled
            u32RatioW <<= 1;
            u8TimeW++;
        }

        if ((u32RatioH << 1) < 100)
        {
            // there is room for height of src win and view win to be doubled
            u32RatioH <<= 1;
            u8TimeH++;
        }

        s8ZoomingRatio --;
    }

    PHOTO_DISP_MSG(printf("nrw: %u, nrh: %u, zr: %d, tw: %u, th: %u\n", u32RatioW, u32RatioH, s8ZoomingRatio, u8TimeW, u8TimeH));

    if ((u8TimeW == 0) && (u8TimeH == 0))
    {
        // re-adjust isn't needed
        return;
    }

    PHOTO_DISP_MSG(printf("ox: %u, oy: %u, ow: %u, oh: %u\n",
            stPhotoInstanceInfo.stResizedImg.u16RectX,
            stPhotoInstanceInfo.stResizedImg.u16RectY,
            stPhotoInstanceInfo.stResizedImg.u16RectW,
            stPhotoInstanceInfo.stResizedImg.u16RectH));
    PHOTO_DISP_MSG(printf("oow: %u, ooh: %u\n",
            stPhotoInstanceInfo.stOutputImg.u16RectW,
            stPhotoInstanceInfo.stOutputImg.u16RectH));

    // re-calculate w, h of view win
    stPhotoInstanceInfo.stOutputImg.u16RectW <<= u8TimeW;
    stPhotoInstanceInfo.stOutputImg.u16RectH <<= u8TimeH;

    if ((stPhotoInstanceInfo.enRotation == EN_PHOTO_ROTATE_90)
            || (stPhotoInstanceInfo.enRotation == EN_PHOTO_ROTATE_270))
    {
        SWAP32(u32RatioW, u32RatioH);
        SWAP8(u8TimeW, u8TimeH);
    }
    // decide the center, widht and height of src win
    u16SrcWinX = stPhotoInstanceInfo.stSrcImg.u16RectX;
    u16SrcWinY = stPhotoInstanceInfo.stSrcImg.u16RectY;
    u16SrcWinW = stPhotoInstanceInfo.stSrcImg.u16RectW;
    u16SrcWinH = stPhotoInstanceInfo.stSrcImg.u16RectH;

    s16CenterX = stPhotoInstanceInfo.stResizedImg.u16RectX + (stPhotoInstanceInfo.stResizedImg.u16RectW >> 1);
    s16CenterY = stPhotoInstanceInfo.stResizedImg.u16RectY + (stPhotoInstanceInfo.stResizedImg.u16RectH >> 1);

    // re-calculate x, y, w, h of src win
    stPhotoInstanceInfo.stResizedImg.u16RectW <<= u8TimeW;
    stPhotoInstanceInfo.stResizedImg.u16RectH <<= u8TimeH;
    s16CenterX -= (stPhotoInstanceInfo.stResizedImg.u16RectW >> 1);
    s16CenterY -= (stPhotoInstanceInfo.stResizedImg.u16RectH >> 1);

    // re-calculate src window coordinates by checking if any boundary hit or not
    if (s16CenterX < 0) // left boundary hit
    {
        s16CenterX = u16SrcWinX;
    }
    else
    {
        if (((U16)s16CenterX + stPhotoInstanceInfo.stResizedImg.u16RectW) >
                (u16SrcWinX + u16SrcWinW)) // right boundary hit
        {
            s16CenterX = u16SrcWinX + u16SrcWinW - stPhotoInstanceInfo.stResizedImg.u16RectW;
        }
    }

    if (s16CenterY < 0) // top boundary hit
    {
        s16CenterY = u16SrcWinY;
    }
    else
    {
        if (((U16)s16CenterY + stPhotoInstanceInfo.stResizedImg.u16RectH) >
                (u16SrcWinY + u16SrcWinH)) // bottom boundary hit
        {
            s16CenterY = u16SrcWinY + u16SrcWinH - stPhotoInstanceInfo.stResizedImg.u16RectH;
        }
    }

    // assign new coordinates
    stPhotoInstanceInfo.stResizedImg.u16RectX = (U16)s16CenterX;
    stPhotoInstanceInfo.stResizedImg.u16RectY = (U16)s16CenterY;

    PHOTO_DISP_MSG(printf("nx: %u, ny: %u, nw: %u, nh: %u\n",
            stPhotoInstanceInfo.stResizedImg.u16RectX,
            stPhotoInstanceInfo.stResizedImg.u16RectY,
            stPhotoInstanceInfo.stResizedImg.u16RectW,
            stPhotoInstanceInfo.stResizedImg.u16RectH));
    PHOTO_DISP_MSG(printf("now: %u, noh: %u\n",
            stPhotoInstanceInfo.stOutputImg.u16RectW,
            stPhotoInstanceInfo.stOutputImg.u16RectH));
}

static void MApp_Photo_AdjustViewWinPosition(void)
{
    U16 u16ShiftX = 0, u16ShiftY = 0;

    PHOTO_DISP_MSG(printf("pos: %u\n", stPhotoInstanceInfo.enAlign));

    if (stPhotoInstanceInfo.enResize == EN_PHOTO_FIT_VIEW_WINDOW)
        return;
    // calculate x shift
    switch (stPhotoInstanceInfo.enAlign)
    {
        case EN_PHOTO_ALIGN_MIDDLE_CENTERED:
        case EN_PHOTO_ALIGN_TOP_CENTERED:
        case EN_PHOTO_ALIGN_BOTTOM_CENTERED:
            if (stPhotoInstanceInfo.stDstBuff.u16RectW > stPhotoInstanceInfo.stOutputImg.u16RectW)
            {
                u16ShiftX = stPhotoInstanceInfo.stDstBuff.u16RectW - stPhotoInstanceInfo.stOutputImg.u16RectW;
                u16ShiftX >>= 1; //devide 2
            }
            break;

        case EN_PHOTO_ALIGN_MIDDLE_RIGHT:
        case EN_PHOTO_ALIGN_TOP_RIGHT:
        case EN_PHOTO_ALIGN_BOTTOM_RIGHT:
            if (stPhotoInstanceInfo.stDstBuff.u16RectW > stPhotoInstanceInfo.stOutputImg.u16RectW)
            {
                u16ShiftX = stPhotoInstanceInfo.stDstBuff.u16RectW - stPhotoInstanceInfo.stOutputImg.u16RectW;
            }
            break;

        case EN_PHOTO_ALIGN_MIDDLE_LEFT:
        case EN_PHOTO_ALIGN_TOP_LEFT:
        case EN_PHOTO_ALIGN_BOTTOM_LEFT:
        default:
            break;
    }

    // calculate y shift
    switch (stPhotoInstanceInfo.enAlign)
    {
        case EN_PHOTO_ALIGN_MIDDLE_CENTERED:
        case EN_PHOTO_ALIGN_MIDDLE_RIGHT:
        case EN_PHOTO_ALIGN_MIDDLE_LEFT:
            if (stPhotoInstanceInfo.stDstBuff.u16RectH > stPhotoInstanceInfo.stOutputImg.u16RectH)
            {
                u16ShiftY = stPhotoInstanceInfo.stDstBuff.u16RectH - stPhotoInstanceInfo.stOutputImg.u16RectH;
                u16ShiftY >>= 1; //devide 2
            }
            break;

        case EN_PHOTO_ALIGN_BOTTOM_CENTERED:
        case EN_PHOTO_ALIGN_BOTTOM_RIGHT:
        case EN_PHOTO_ALIGN_BOTTOM_LEFT:
            if (stPhotoInstanceInfo.stDstBuff.u16RectH > stPhotoInstanceInfo.stOutputImg.u16RectH)
            {
                u16ShiftY = stPhotoInstanceInfo.stDstBuff.u16RectH - stPhotoInstanceInfo.stOutputImg.u16RectH;
            }
            break;

        case EN_PHOTO_ALIGN_TOP_CENTERED:
        case EN_PHOTO_ALIGN_TOP_RIGHT:
        case EN_PHOTO_ALIGN_TOP_LEFT:
        default:
            break;
    }

    PHOTO_DISP_MSG(printf("ox: %u, oy: %u, sx: %u, sy: %u, nx: %u, ny: %u\n",
            stPhotoInstanceInfo.stOutputImg.u16RectX, stPhotoInstanceInfo.stOutputImg.u16RectY,
            u16ShiftX, u16ShiftY,
            stPhotoInstanceInfo.stOutputImg.u16RectX + u16ShiftX,
            stPhotoInstanceInfo.stOutputImg.u16RectY + u16ShiftY));

    stPhotoInstanceInfo.stOutputImg.u16RectX += u16ShiftX;
    stPhotoInstanceInfo.stOutputImg.u16RectY += u16ShiftY;
}

static void MApp_Photo_ZoomViewWin(void)
{
    S8 s8ZoomingRatio = stPhotoInstanceInfo.enZoomingNew - EN_PHOTO_ZOOM_1;
    U16 u16CenterX, u16CenterY;

    PHOTO_DISP_MSG(printf("zoom vw: %d\n", s8ZoomingRatio));

    if (s8ZoomingRatio >= 0)
    {
         // zooming to 1, 2, 4, 8, not calculate here
        return;
    }
    u16CenterX = stPhotoInstanceInfo.stOutputImg.u16RectX + (stPhotoInstanceInfo.stOutputImg.u16RectW >> 1);
    u16CenterY = stPhotoInstanceInfo.stOutputImg.u16RectY + (stPhotoInstanceInfo.stOutputImg.u16RectH >> 1);

    PHOTO_DISP_MSG(printf("ox: %u, oy: %u, ow: %u, oh: %u\n",
            stPhotoInstanceInfo.stOutputImg.u16RectX,
            stPhotoInstanceInfo.stOutputImg.u16RectY,
            stPhotoInstanceInfo.stOutputImg.u16RectW,
            stPhotoInstanceInfo.stOutputImg.u16RectH));

    s8ZoomingRatio = 0 - s8ZoomingRatio; // absolute value
    stPhotoInstanceInfo.stOutputImg.u16RectW >>= s8ZoomingRatio;
    stPhotoInstanceInfo.stOutputImg.u16RectH >>= s8ZoomingRatio;
    stPhotoInstanceInfo.stOutputImg.u16RectX = u16CenterX - (stPhotoInstanceInfo.stOutputImg.u16RectW >> 1);
    stPhotoInstanceInfo.stOutputImg.u16RectY = u16CenterY - (stPhotoInstanceInfo.stOutputImg.u16RectH >> 1);

    PHOTO_DISP_MSG(printf("nx: %u, ny: %u, nw: %u, nh: %u\n",
            stPhotoInstanceInfo.stOutputImg.u16RectX,
            stPhotoInstanceInfo.stOutputImg.u16RectY,
            stPhotoInstanceInfo.stOutputImg.u16RectW,
            stPhotoInstanceInfo.stOutputImg.u16RectH));
}

void MApp_Photo_ShrinkImage(GEBitBltInfo *pstBitbltInfo, GEPitBaseInfo *pstPitBaseInfo, ST_PHOTO_SHRINK_SETTING *pstShrinkSetting)
{
    GEBitBltInfo stBitbltInfo;
    GEPitBaseInfo stPitBaseInfo;

    U32 u32SpecialEffectDoubleBuffer[2];
    U8 u8SpecialEffectDoubleBufferIdx = 1;
    U32 u32CurSpecialEffectDoubleBufferLength;
    U16 u16HalfWidth, u16HalfHeight, u16Pitch;

    PHOTO_DISP_MSG(printf("Shrink Src Image\n"));

    u32SpecialEffectDoubleBuffer[0] = pstShrinkSetting->u32SpecialEffectBuffer0;
    u32SpecialEffectDoubleBuffer[1] = pstShrinkSetting->u32SpecialEffectBuffer1;

    PHOTO_DISP_MSG(printf("SpeEffBuf0: %x, SpeEffBuf1: %x\n", u32SpecialEffectDoubleBuffer[0], u32SpecialEffectDoubleBuffer[1]));


    while (1)
    {
        stBitbltInfo = *pstBitbltInfo;
        stPitBaseInfo = *pstPitBaseInfo;

        u16HalfWidth = (stBitbltInfo.src_width >> 1);
        u16HalfHeight = (stBitbltInfo.src_height >> 1);

        // check if criteria (src width / 2 >= dest width) || (src height / 2 >= dest height) hit
        if ((u16HalfWidth < stBitbltInfo.BitbltCoordinate.width)
                && (u16HalfHeight < stBitbltInfo.BitbltCoordinate.height))
        {
            return;
        }

        if ((u16HalfWidth <= GE_MARGIN) || (u16HalfHeight <= GE_MARGIN)) // we aren't capable to shrink the src image smaller because the dst width/height will never smaller than width/height
        {
            PHOTO_DISP_MSG(printf("Limitation hit\n"));
            return;
        }


        if ((pstShrinkSetting->enRotation == EN_PHOTO_ROTATE_90) || (pstShrinkSetting->enRotation == EN_PHOTO_ROTATE_270))
        {
            u16Pitch = (u16HalfHeight + (THUMBNIAL_SHRINK_BUFF_PIXEL_ALIGNMENT - 1)) & (~(THUMBNIAL_SHRINK_BUFF_PIXEL_ALIGNMENT - 1));
        }
        else
        {
            u16Pitch = (u16HalfWidth + (THUMBNIAL_SHRINK_BUFF_PIXEL_ALIGNMENT - 1)) & (~(THUMBNIAL_SHRINK_BUFF_PIXEL_ALIGNMENT - 1));
        }

        u8SpecialEffectDoubleBufferIdx ^= 1;
        stBitbltInfo.dst_fm = THUMBNAIL_SHRINK_BUFF_FMT;
        stBitbltInfo.BitbltCoordinate.width = u16HalfWidth;
        stBitbltInfo.BitbltCoordinate.height = u16HalfHeight;
        stBitbltInfo.BitbltCoordinate.v0_x = 0;
        stBitbltInfo.BitbltCoordinate.v0_y = 0;

        stPitBaseInfo.db_base = u32SpecialEffectDoubleBuffer[u8SpecialEffectDoubleBufferIdx];
        stPitBaseInfo.db_pit = u16Pitch * THUMBNAIL_SHRINK_BUFF_BYTE_PER_PIXEL;

        u32CurSpecialEffectDoubleBufferLength = (u8SpecialEffectDoubleBufferIdx == 0 ? pstShrinkSetting->u32SpecialEffectBuffer0Length : pstShrinkSetting->u32SpecialEffectBuffer1Length);
        if((U32)(stPitBaseInfo.db_pit * stBitbltInfo.BitbltCoordinate.height) > u32CurSpecialEffectDoubleBufferLength)
        {
            printf("Error!!! pitch*height (0x%x) > CurSpecialEffectBufferLength (0x%x)\n",stPitBaseInfo.db_pit * stBitbltInfo.BitbltCoordinate.height,u32CurSpecialEffectDoubleBufferLength);
            return;
        }

        // clear the shrink buffer acts as output buffer now
        msAPI_GE_ClearFrameBufferByWord((U32)u32SpecialEffectDoubleBuffer[u8SpecialEffectDoubleBufferIdx],
               stPitBaseInfo.db_pit * stBitbltInfo.BitbltCoordinate.height,
               0x80008000);
        // after clear frame buffer, flush cmd
        MApi_GFX_FlushQueue();

        PHOTO_DISP_MSG(printf("stBitbltInfo: \n"));
        PHOTO_DISP_MSG(printf("\ttype flag: %u\n", stBitbltInfo.BitBltTypeFlag));
        PHOTO_DISP_MSG(printf("\tbmp flag: %u\n", stBitbltInfo.BmpFlag));
        PHOTO_DISP_MSG(printf("\tdest fmt: %u\n", stBitbltInfo.dst_fm));
        PHOTO_DISP_MSG(printf("\tsrc fmt: %u\n", stBitbltInfo.src_fm));
        PHOTO_DISP_MSG(printf("\tbmp hnd: %d\n", stBitbltInfo.bmphandle));
        PHOTO_DISP_MSG(printf("\tsrc width: %u\n", stBitbltInfo.src_width));
        PHOTO_DISP_MSG(printf("\tsrc height: %u\n", stBitbltInfo.src_height));
        PHOTO_DISP_MSG(printf("\tcoord v0x: %u\n", stBitbltInfo.BitbltCoordinate.v0_x));
        PHOTO_DISP_MSG(printf("\tcoord v0y: %u\n", stBitbltInfo.BitbltCoordinate.v0_y));
        PHOTO_DISP_MSG(printf("\tcoord width: %u\n", stBitbltInfo.BitbltCoordinate.width));
        PHOTO_DISP_MSG(printf("\tcoord height: %u\n", stBitbltInfo.BitbltCoordinate.height));
        PHOTO_DISP_MSG(printf("\tcoord v2x: %u\n", stBitbltInfo.BitbltCoordinate.v2_x));
        PHOTO_DISP_MSG(printf("\tcoord v2y: %u\n", stBitbltInfo.BitbltCoordinate.v2_y));
        PHOTO_DISP_MSG(printf("\tcoord direct: %u\n", stBitbltInfo.BitbltCoordinate.direction));
        PHOTO_DISP_MSG(printf("stPitBaseInfo: \n"));
        PHOTO_DISP_MSG(printf("\tsrc pitch: %x\n",stPitBaseInfo.sb_pit));
        PHOTO_DISP_MSG(printf("\tdst pitch: %x\n",stPitBaseInfo.db_pit));
        PHOTO_DISP_MSG(printf("\tsrc base: %x\n",stPitBaseInfo.sb_base));
        PHOTO_DISP_MSG(printf("\tdst base: %x\n",stPitBaseInfo.db_base));

        msAPI_GE_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_PC, GFX_YUV_OUT_255, GFX_YUV_IN_255, GFX_YUV_YUYV, GFX_YUV_YUYV);

        msAPI_GE_SetPatchMode(TRUE);
        // output image to destination buffer
        msAPI_GE_BitBlt(&stBitbltInfo, &stPitBaseInfo);
        // after BitBlt, flush cmd
        MApi_GFX_FlushQueue();
        msAPI_GE_SetPatchMode(FALSE);

        // NOTE: it's critical to reset GE registers after rotation
        msAPI_GE_SetMirror(0, 0);
        msAPI_GE_SetRotate(GEROTATE_0);

        // store information back to src for next loop
        pstPitBaseInfo->sb_base = stPitBaseInfo.db_base;
        pstPitBaseInfo->sb_pit = stPitBaseInfo.db_pit;

        pstBitbltInfo->BitbltCoordinate.v2_x = stBitbltInfo.BitbltCoordinate.v0_x;
        pstBitbltInfo->BitbltCoordinate.v2_y = stBitbltInfo.BitbltCoordinate.v0_y;

        pstBitbltInfo->src_fm = stBitbltInfo.dst_fm;
        pstBitbltInfo->src_width = stBitbltInfo.BitbltCoordinate.width;
        pstBitbltInfo->src_height = stBitbltInfo.BitbltCoordinate.height;
        if ((pstShrinkSetting->enRotation == EN_PHOTO_ROTATE_90) || (pstShrinkSetting->enRotation == EN_PHOTO_ROTATE_270))
        {
            U16 u16Tmp;
            u16Tmp = pstBitbltInfo->src_width;
            pstBitbltInfo->src_width = pstBitbltInfo->src_height;
            pstBitbltInfo->src_height = u16Tmp;

            u16Tmp = pstBitbltInfo->BitbltCoordinate.width;
            pstBitbltInfo->BitbltCoordinate.width = pstBitbltInfo->BitbltCoordinate.height;
            pstBitbltInfo->BitbltCoordinate.height = u16Tmp;
        }
        pstShrinkSetting->enRotation = EN_PHOTO_ROTATE_0;

        PHOTO_DISP_MSG(printf("Adjust\n"));
        PHOTO_DISP_MSG(printf("pstBitbltInfo->: \n"));
        PHOTO_DISP_MSG(printf("\ttype flag: %u\n", pstBitbltInfo->BitBltTypeFlag));
        PHOTO_DISP_MSG(printf("\tbmp flag: %u\n", pstBitbltInfo->BmpFlag));
        PHOTO_DISP_MSG(printf("\tdest fmt: %u\n", pstBitbltInfo->dst_fm));
        PHOTO_DISP_MSG(printf("\tsrc fmt: %u\n", pstBitbltInfo->src_fm));
        PHOTO_DISP_MSG(printf("\tbmp hnd: %d\n", pstBitbltInfo->bmphandle));
        PHOTO_DISP_MSG(printf("\tsrc width: %u\n", pstBitbltInfo->src_width));
        PHOTO_DISP_MSG(printf("\tsrc height: %u\n", pstBitbltInfo->src_height));
        PHOTO_DISP_MSG(printf("\tcoord v0x: %u\n", pstBitbltInfo->BitbltCoordinate.v0_x));
        PHOTO_DISP_MSG(printf("\tcoord v0y: %u\n", pstBitbltInfo->BitbltCoordinate.v0_y));
        PHOTO_DISP_MSG(printf("\tcoord width: %u\n", pstBitbltInfo->BitbltCoordinate.width));
        PHOTO_DISP_MSG(printf("\tcoord height: %u\n", pstBitbltInfo->BitbltCoordinate.height));
        PHOTO_DISP_MSG(printf("\tcoord v2x: %u\n", pstBitbltInfo->BitbltCoordinate.v2_x));
        PHOTO_DISP_MSG(printf("\tcoord v2y: %u\n", pstBitbltInfo->BitbltCoordinate.v2_y));
        PHOTO_DISP_MSG(printf("\tcoord direct: %u\n", pstBitbltInfo->BitbltCoordinate.direction));
        PHOTO_DISP_MSG(printf("pstPitBaseInfo->: \n"));
        PHOTO_DISP_MSG(printf("\tsrc pitch: %x\n",pstPitBaseInfo->sb_pit));
        PHOTO_DISP_MSG(printf("\tdst pitch: %x\n",pstPitBaseInfo->db_pit));
        PHOTO_DISP_MSG(printf("\tsrc base: %x\n",pstPitBaseInfo->sb_base));
        PHOTO_DISP_MSG(printf("\tdst base: %x\n",pstPitBaseInfo->db_base));
     }
}


void MApp_Photo_ShrinkSrcImage_MovieThumbnail(GEBitBltInfo *pstBitbltInfo, GEPitBaseInfo *pstPitBaseInfo)
{
    ST_PHOTO_SHRINK_SETTING stShrinkSetting;
    memset(&stShrinkSetting, 0, sizeof(ST_PHOTO_SHRINK_SETTING));

    stShrinkSetting.enRotation = EN_PHOTO_ROTATE_0;
    stShrinkSetting.u32SpecialEffectBuffer0 = PHOTO_THUMBNAIL_SHRINK_BUFFER_0_ADDR;
    stShrinkSetting.u32SpecialEffectBuffer0Length = PHOTO_THUMBNAIL_SHRINK_BUFFER_0_SIZE;
    stShrinkSetting.u32SpecialEffectBuffer1 = PHOTO_THUMBNAIL_SHRINK_BUFFER_1_ADDR;
    stShrinkSetting.u32SpecialEffectBuffer1Length = PHOTO_THUMBNAIL_SHRINK_BUFFER_1_SIZE;
    MApp_Photo_ShrinkImage(pstBitbltInfo, pstPitBaseInfo, &stShrinkSetting);
}

static void MApp_Photo_ShrinkSrcImage(GEBitBltInfo *pstBitbltInfo, GEPitBaseInfo *pstPitBaseInfo)
{
    ST_PHOTO_SHRINK_SETTING stShrinkSetting;
    memset(&stShrinkSetting, 0, sizeof(ST_PHOTO_SHRINK_SETTING));

    stShrinkSetting.enRotation = stPhotoInstanceInfo.enRotation;
    stShrinkSetting.u32SpecialEffectBuffer0 = PHOTO_THUMBNAIL_SHRINK_BUFFER_0_ADDR;
    stShrinkSetting.u32SpecialEffectBuffer0Length = PHOTO_THUMBNAIL_SHRINK_BUFFER_0_SIZE;
    stShrinkSetting.u32SpecialEffectBuffer1 = PHOTO_THUMBNAIL_SHRINK_BUFFER_1_ADDR;
    stShrinkSetting.u32SpecialEffectBuffer1Length = PHOTO_THUMBNAIL_SHRINK_BUFFER_1_SIZE;
    MApp_Photo_ShrinkImage(pstBitbltInfo, pstPitBaseInfo, &stShrinkSetting);
}

static void MApp_Photo_ApplyEffect(void)
{
    stPhotoInstanceInfo.stOutputImg = stPhotoInstanceInfo.stDstBuff;
    MApp_Photo_AdjustSrcWinSize();
    MApp_Photo_AdjustViewWinSize();
    MApp_Photo_ReAdjustSrcWinViewWinSize();
    MApp_Photo_AdjustViewWinPosition();
    MApp_Photo_ZoomViewWin();
    // NOTE: rotation is not apply here because it depends on GE function
}

static void MApp_Photo_OutputImage(void)
{
    GEBitBltInfo stBitbltInfo;
    GEPitBaseInfo stPitBaseInfo;

    memset(&stBitbltInfo, 0, sizeof(GEBitBltInfo));
    memset(&stPitBaseInfo, 0, sizeof(GEPitBaseInfo));

    if (stPhotoInstanceInfo.stSrcImg.u8FbFmt == GFX_FMT_ARGB8888)
        stPitBaseInfo.sb_pit = stPhotoInstanceInfo.stSrcImg.u16BuffW * 4; // 4 bytes per pixel
    else
        stPitBaseInfo.sb_pit = stPhotoInstanceInfo.stSrcImg.u16BuffW * 2; // 2 bytes per pixel
    stPitBaseInfo.sb_base = stPhotoInstanceInfo.stSrcImg.u32BuffAddr;

    if (stPhotoInstanceInfo.stOutputImg.u8FbFmt == GFX_FMT_ARGB8888)
        stPitBaseInfo.db_pit = stPhotoInstanceInfo.stOutputImg.u16BuffW * 4; // 4 bytes per pixel
    else
        stPitBaseInfo.db_pit = stPhotoInstanceInfo.stOutputImg.u16BuffW * 2; // 2 bytes per pixel
    stPitBaseInfo.db_base = stPhotoInstanceInfo.stOutputImg.u32BuffAddr;

    stBitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;
    stBitbltInfo.BmpFlag = GFXDRAW_FLAG_DEFAULT;
    stBitbltInfo.dst_fm = stPhotoInstanceInfo.stOutputImg.u8FbFmt;
    stBitbltInfo.src_fm = stPhotoInstanceInfo.stSrcImg.u8FbFmt;

    stBitbltInfo.src_width = stPhotoInstanceInfo.stResizedImg.u16RectW;
    stBitbltInfo.src_height = stPhotoInstanceInfo.stResizedImg.u16RectH;

    //do mirror and rotation
    if(stPhotoInstanceInfo.bMirrorX)
    {
        stBitbltInfo.BitbltCoordinate.v2_x = stPhotoInstanceInfo.stResizedImg.u16RectX + stBitbltInfo.src_width - 1;
    }
    else
    {
        stBitbltInfo.BitbltCoordinate.v2_x = stPhotoInstanceInfo.stResizedImg.u16RectX;
    }

    if(stPhotoInstanceInfo.bMirrorY)
    {
        stBitbltInfo.BitbltCoordinate.v2_y = stPhotoInstanceInfo.stResizedImg.u16RectY + stBitbltInfo.src_height - 1;
    }
    else
    {
        stBitbltInfo.BitbltCoordinate.v2_y = stPhotoInstanceInfo.stResizedImg.u16RectY;
    }

    stBitbltInfo.BitbltCoordinate.direction = 0; // TODO: what's this?
    stBitbltInfo.BitbltCoordinate.v0_x = stPhotoInstanceInfo.stOutputImg.u16RectX;
    stBitbltInfo.BitbltCoordinate.v0_y = stPhotoInstanceInfo.stOutputImg.u16RectY;

    if ((stPhotoInstanceInfo.enRotation == EN_PHOTO_ROTATE_90) || (stPhotoInstanceInfo.enRotation == EN_PHOTO_ROTATE_270))
    {
        stBitbltInfo.BitbltCoordinate.width = stPhotoInstanceInfo.stOutputImg.u16RectH;
        stBitbltInfo.BitbltCoordinate.height = stPhotoInstanceInfo.stOutputImg.u16RectW;
    }
    else
    {
        stBitbltInfo.BitbltCoordinate.width = stPhotoInstanceInfo.stOutputImg.u16RectW;
        stBitbltInfo.BitbltCoordinate.height = stPhotoInstanceInfo.stOutputImg.u16RectH;
    }

    msAPI_OSD_SetClipWindow(0, 0, stPhotoInstanceInfo.stOutputImg.u16BuffW, stPhotoInstanceInfo.stOutputImg.u16BuffH);
    msAPI_GE_SetNearestMode(FALSE);

    if(stPhotoInstanceInfo.bMirrorX || stPhotoInstanceInfo.bMirrorY)
        msAPI_GE_SetMirror(stPhotoInstanceInfo.bMirrorX, stPhotoInstanceInfo.bMirrorY);

    switch (stPhotoInstanceInfo.enRotation)
    {
    case EN_PHOTO_ROTATE_90:
        {
            msAPI_GE_SetRotate(GEROTATE_90);
        }
        break;
    case EN_PHOTO_ROTATE_180:
        {
            msAPI_GE_SetRotate(GEROTATE_180);
        }
        break;
    case EN_PHOTO_ROTATE_270:
        {
            msAPI_GE_SetRotate(GEROTATE_270);
        }
        break;
    case EN_PHOTO_ROTATE_0:
        {
            msAPI_GE_SetRotate(GEROTATE_0);
        }
        break;
    default:
        break;
    }

    // shrink src image if the width or height of destination buffer is less than 1/2
    MApp_Photo_ShrinkSrcImage(&stBitbltInfo, &stPitBaseInfo);
    stBitbltInfo.src_height--; // Fix the bottom garbage line.

    PHOTO_DISP_MSG(printf("Img Out\n"));
    PHOTO_DISP_MSG(printf("stBitbltInfo: \n"));
    PHOTO_DISP_MSG(printf("\ttype flag: %u\n", stBitbltInfo.BitBltTypeFlag));
    PHOTO_DISP_MSG(printf("\tbmp flag: %u\n", stBitbltInfo.BmpFlag));
    PHOTO_DISP_MSG(printf("\tdest fmt: %u\n", stBitbltInfo.dst_fm));
    PHOTO_DISP_MSG(printf("\tsrc fmt: %u\n", stBitbltInfo.src_fm));
    PHOTO_DISP_MSG(printf("\tbmp hnd: %d\n", stBitbltInfo.bmphandle));
    PHOTO_DISP_MSG(printf("\tsrc width: %u\n", stBitbltInfo.src_width));
    PHOTO_DISP_MSG(printf("\tsrc height: %u\n", stBitbltInfo.src_height));
    PHOTO_DISP_MSG(printf("\tcoord v0x: %u\n", stBitbltInfo.BitbltCoordinate.v0_x));
    PHOTO_DISP_MSG(printf("\tcoord v0y: %u\n", stBitbltInfo.BitbltCoordinate.v0_y));
    PHOTO_DISP_MSG(printf("\tcoord width: %u\n", stBitbltInfo.BitbltCoordinate.width));
    PHOTO_DISP_MSG(printf("\tcoord height: %u\n", stBitbltInfo.BitbltCoordinate.height));
    PHOTO_DISP_MSG(printf("\tcoord v2x: %u\n", stBitbltInfo.BitbltCoordinate.v2_x));
    PHOTO_DISP_MSG(printf("\tcoord v2y: %u\n", stBitbltInfo.BitbltCoordinate.v2_y));
    PHOTO_DISP_MSG(printf("\tcoord direct: %u\n", stBitbltInfo.BitbltCoordinate.direction));
    PHOTO_DISP_MSG(printf("stPitBaseInfo: \n"));
    PHOTO_DISP_MSG(printf("\tsrc pitch: %x\n",stPitBaseInfo.sb_pit));
    PHOTO_DISP_MSG(printf("\tdst pitch: %x\n",stPitBaseInfo.db_pit));
    PHOTO_DISP_MSG(printf("\tsrc base: %x\n",stPitBaseInfo.sb_base));
    PHOTO_DISP_MSG(printf("\tdst base: %x\n",stPitBaseInfo.db_base));

    msAPI_GE_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_PC, GFX_YUV_OUT_255, GFX_YUV_IN_255, GFX_YUV_YUYV, GFX_YUV_YUYV);
    msAPI_GE_SetPatchMode(TRUE);

    // output image to destination buffer
    msAPI_GE_BitBlt(&stBitbltInfo, &stPitBaseInfo);
    // after BitBlt, flush cmd
    MApi_GFX_FlushQueue();

    msAPI_GE_SetPatchMode(FALSE);

    PHOTO_DISP_MSG(printf("2.end, sx: %u, sy: %u, sw: %u, sh: %u, sp: %u (0x%x)\n",
            stBitbltInfo.BitbltCoordinate.v2_x,
            stBitbltInfo.BitbltCoordinate.v2_y,
            stBitbltInfo.src_width,
            stBitbltInfo.src_height,
            stPitBaseInfo.sb_pit,
            stPitBaseInfo.sb_pit));
    PHOTO_DISP_MSG(printf("2.end, ox: %u, oy: %u, ow: %u, oh: %u, dp: %u (0x%x)\n",
            stBitbltInfo.BitbltCoordinate.v0_x,
            stBitbltInfo.BitbltCoordinate.v0_y,
            stBitbltInfo.BitbltCoordinate.width,
            stBitbltInfo.BitbltCoordinate.height,
            stPitBaseInfo.db_pit,
            stPitBaseInfo.db_pit));

    // NOTE: it's critical to reset GE registers after rotation
    msAPI_GE_SetMirror(0, 0);
    msAPI_GE_SetRotate(GEROTATE_0);

    // restore clip window to full screen
    msAPI_OSD_SetClipWindow(0, 0, g_IPanel.Width(), g_IPanel.Height());

    PHOTO_DISP_MSG(printf("-------Separate Line-------\n"));
}

void MApp_Photo_Display_Thumbnail(
        ST_PHOTO_CAPTURE_RECT *stTo,
        ST_PHOTO_CAPTURE_RECT *stFrom,
        EN_PHOTO_ALIGNMENT enAlign,
        EN_PHOTO_RESIZE enResize)
{
    U16 u16SrcW, u16SrcH, u16Pitch;

    // parameters checking
    if ((stTo == NULL) || (stFrom == NULL))
    {
        __ASSERT(0);
        return;
    }

    if ((stTo->u32BuffAddr == 0) || (stTo->u16BuffW == 0) || (stTo->u16BuffH == 0)) // destination buffer can't be right
    {
        __ASSERT(0);
        return;
    }

    if ((stTo->u8FbFmt != GFX_FMT_RGB565)
            && (stTo->u8FbFmt != GFX_FMT_ARGB8888)
            && (stTo->u8FbFmt != GFX_FMT_ARGB1555)
            && (stTo->u8FbFmt != GFX_FMT_ARGB4444)
            && (stTo->u8FbFmt != GFX_FMT_ARGB1555_DST)
            && (stTo->u8FbFmt != GFX_FMT_YUV422))
    {
        PHOTO_DISP_MSG(printf("[PHOTO DISPLAY] photo thumbnail output format (%d) isn't supported.\n", stTo->u8FbFmt));
        __ASSERT(0);
    }

    if ((stTo->u16RectW == 0) || (stTo->u16RectH == 0)) // specified destination isn't a rectangle
    {
        __ASSERT(0);
        return;
    }
    if ((enAlign >= EN_PHOTO_ALIGN_NOT_SUPPORT) || (enResize >= EN_PHOTO_RESIZE_NOT_SUPPORT)) // specified alignment or resize method not support
    {
        __ASSERT(0);
        return;
    }

    // reset variables
    memset(&stPhotoInstanceInfo, 0, sizeof(stPhotoInstanceInfo));
    stPhotoInstanceInfo.enState = EN_PHOTO_INFO_NONE;
    enPhotoZooming = EN_PHOTO_ZOOM_1;

    // calculate the actual source rectangle
    u16SrcW = MApp_Photo_GetInfo(E_PHOTO_INFO_WIDTH);
    u16SrcH = MApp_Photo_GetInfo(E_PHOTO_INFO_HEIGHT);
    u16Pitch = MApp_Photo_GetInfo(E_PHOTO_INFO_PITCH);

    PHOTO_DISP_MSG(printf("u16SrcW: %d, u16SrcH: %d\n", u16SrcW, u16SrcH));
    if (stFrom->u16RectX + stFrom->u16RectW > u16SrcW)
    {
        stFrom->u16RectW = u16SrcW - stFrom->u16RectX;
    }

    if (stFrom->u16RectY + stFrom->u16RectH > u16SrcH)
    {
        stFrom->u16RectH = u16SrcH - stFrom->u16RectY;
    }

    if ((stFrom->u16RectX >= u16SrcW)  || (stFrom->u16RectY >= u16SrcH)  // specified destination isn't a rectangle or out of range
            || (stFrom->u16RectW == 0) || (stFrom->u16RectH == 0))
    {
        return;
    }

    stPhotoInstanceInfo.stSrcImg = *stFrom;
    stPhotoInstanceInfo.stDstBuff = *stTo;

    // instance information initial
#if ENABLE_AUTO_ROTATION
    EN_PHOTO_ORIENTATION eOrientation;
    eOrientation = (EN_PHOTO_ORIENTATION)MApp_Photo_GetInfo(E_PHOTO_INFO_ORIENTATION);

    if(eOrientation > E_PHOTO_ORIENT_ROTATE_0 && eOrientation < E_PHOTO_ORIENT_NOT_FOUND
        && MApp_Photo_GetInfo(E_PHOTO_INFO_FILE_FORMAT) == E_PHOTO_FILE_JPEG)
    {
        switch(eOrientation)
        {
            case E_PHOTO_ORIENT_MIRROR_LR:
                {
                    stPhotoInstanceInfo.bMirrorX = TRUE;
                    stPhotoInstanceInfo.bMirrorY = FALSE;
                    stPhotoInstanceInfo.enRotation = EN_PHOTO_ROTATE_0;
                    break;
                }
            case E_PHOTO_ORIENT_ROTATE_180:
                {
                    stPhotoInstanceInfo.bMirrorX = TRUE;
                    stPhotoInstanceInfo.bMirrorY = TRUE;
                    stPhotoInstanceInfo.enRotation = EN_PHOTO_ROTATE_0;
                    break;
                }
            case E_PHOTO_ORIENT_MIRROR_TB:
                {
                    stPhotoInstanceInfo.bMirrorX = FALSE;
                    stPhotoInstanceInfo.bMirrorY = TRUE;
                    stPhotoInstanceInfo.enRotation = EN_PHOTO_ROTATE_0;
                    break;
                }
            case E_PHOTO_ORIENT_ROTATE_90_MIRROR_LR:
                {
                    //for our hw interface, it does mirror firstly, then rotate.
                    stPhotoInstanceInfo.bMirrorX = FALSE;
                    stPhotoInstanceInfo.bMirrorY = TRUE;
                    stPhotoInstanceInfo.enRotation = EN_PHOTO_ROTATE_90;
                    break;
                }
            case E_PHOTO_ORIENT_E_ORIENT_ROTATE_90:
                {
                    stPhotoInstanceInfo.bMirrorX = FALSE;
                    stPhotoInstanceInfo.bMirrorY = FALSE;
                    stPhotoInstanceInfo.enRotation = EN_PHOTO_ROTATE_90;
                    break;
                }
            case E_PHOTO_ORIENT_ROTATE_90_MIRROR_TB:
                {
                    //for our hw interface, it does mirror  firstly, then rotate.
                    stPhotoInstanceInfo.bMirrorX = TRUE;
                    stPhotoInstanceInfo.bMirrorY = FALSE;
                    stPhotoInstanceInfo.enRotation = EN_PHOTO_ROTATE_90;
                    break;
                }
            case E_PHOTO_ORIENT_ROTATE_270:
                {
                    stPhotoInstanceInfo.bMirrorX = TRUE;
                    stPhotoInstanceInfo.bMirrorY = TRUE;
                    stPhotoInstanceInfo.enRotation = EN_PHOTO_ROTATE_90;
                    break;
                }
        default:
                {
                    stPhotoInstanceInfo.bMirrorX = FALSE;
                    stPhotoInstanceInfo.bMirrorY = FALSE;
                    stPhotoInstanceInfo.enRotation = EN_PHOTO_ROTATE_0;
                    break;
                }
        }
    }
    else
    {
        stPhotoInstanceInfo.bMirrorX = FALSE;
        stPhotoInstanceInfo.bMirrorY = FALSE;
        stPhotoInstanceInfo.enRotation = EN_PHOTO_ROTATE_0;
    }
#else
    stPhotoInstanceInfo.bMirrorX = FALSE;
    stPhotoInstanceInfo.bMirrorY = FALSE;
    stPhotoInstanceInfo.enRotation = EN_PHOTO_ROTATE_0;
#endif
    stPhotoInstanceInfo.enZooming = EN_PHOTO_ZOOM_1;
    stPhotoInstanceInfo.enZoomingNew = EN_PHOTO_ZOOM_1;

    // fill in necessary information for jpeg special effect (rotate/zooming) and output desired picture
    stPhotoInstanceInfo.enAlign = enAlign;
    stPhotoInstanceInfo.enResize = enResize;
    stPhotoInstanceInfo.u16ResizeRatio = 100;

    stPhotoInstanceInfo.stSrcImg.u16BuffW = u16Pitch;
    stPhotoInstanceInfo.stSrcImg.u16BuffH = u16SrcH;
    stPhotoInstanceInfo.stSrcImg.u32BuffAddr = PHOTO_OUTPUT_BUFFER_ADDR;

    // output format checking
    switch ((EN_PHOTO_OUTPUT_FORMAT)MApp_Photo_GetInfo(E_PHOTO_INFO_OUTPUT_FORMAT))
    {
        case E_PHOTO_OUTPUT_ARGB8888:
            stPhotoInstanceInfo.stSrcImg.u8FbFmt = GFX_FMT_ARGB8888;
            break;

        case E_PHOTO_OUTPUT_YUV422:
            stPhotoInstanceInfo.stSrcImg.u8FbFmt = GFX_FMT_YUV422;
            break;

        default:
            PHOTO_DISP_MSG(printf("[PHOTO DISPLAY] thumbnail doesn't support output format %ld\n", MApp_Photo_GetInfo(E_PHOTO_INFO_OUTPUT_FORMAT)));
            return;
    }

    stPhotoInstanceInfo.stResizedImg = stPhotoInstanceInfo.stSrcImg;

    stPhotoInstanceInfo.enState = EN_PHOTO_INFO_ALL_COLLECT;

    MApp_Photo_ApplyEffect();
    MApp_Photo_OutputImage();
}

void MApp_Photo_Buf_Init(void)
{
    //copy disp buf to inter buf
    msAPI_MIU_Copy(PHOTO_DISPLAY_BUFFER_ADDR, PHOTO_DISPLAY_SRC_BUFFER_ADDR, PHOTO_DISPLAY_BUFFER_SIZE, MIU_SDRAM2SDRAM);  //ok but color error
}

void MApp_Photo_GetInterBuffInfo(U16 *pu16Width, U16 *pu16Height, U32 *pu32Addr, U32 *pu32Len)
{
    if (pu16Width)
    {
        *pu16Width = PHOTO_ADJUSTED_PANEL_WIDTH;
    }

    if (pu16Height)
    {
        *pu16Height = PANEL_HEIGHT;
    }

    if (pu32Addr)
    {
        *pu32Addr = PHOTO_DISPLAY_SRC_BUFFER_ADDR;
    }

    if (pu32Len)
    {
        *pu32Len = PHOTO_DISPLAY_SRC_BUFFER_SIZE;
    }
}

#if PHOTO_SLIDE_SHOW_EFFECT
#if ENABLE_ZOOM_MAP
U16 _MApp_Photo_GetZoomImageWidth(void)
{
    return (m_u16ZoomImageWidth<=g_IPanel.Width())?(m_u16ZoomImageWidth):(g_IPanel.Width());
}

U16 _MApp_Photo_GetZoomImageHeight(void)
{
    return (m_u16ZoomImageHeight<=g_IPanel.Height())?(m_u16ZoomImageHeight):(g_IPanel.Height());
}

S16 _MApp_Photo_GetZoomCaptureOffsetX(void)
{
    switch(m_enRotation)
    {
        case EN_PHOTO_ROTATE_0:
            return m_s16PhotoOffsetX*m_u16ZoomDenominatorRotate/m_u16ZoomNumeratorRotate;
        case EN_PHOTO_ROTATE_90:
            return (-m_s16PhotoOffsetY *m_u16ZoomDenominatorRotate/m_u16ZoomNumeratorRotate );
        case EN_PHOTO_ROTATE_180:
            return (-m_s16PhotoOffsetX*m_u16ZoomDenominatorRotate/m_u16ZoomNumeratorRotate);
        case EN_PHOTO_ROTATE_270:
            return (m_s16PhotoOffsetY *m_u16ZoomDenominatorRotate/m_u16ZoomNumeratorRotate );
        default:
            return m_s16PhotoOffsetX*m_u16ZoomDenominatorRotate/m_u16ZoomNumeratorRotate;
        break;
    }
}

S16 _MApp_Photo_GetZoomCaptureOffsetY(void)
{
    switch(m_enRotation)
    {
        case EN_PHOTO_ROTATE_0:
            return m_s16PhotoOffsetY*m_u16ZoomDenominatorRotate/m_u16ZoomNumeratorRotate;
        case EN_PHOTO_ROTATE_90:
            return (m_s16PhotoOffsetX*m_u16ZoomDenominatorRotate/m_u16ZoomNumeratorRotate);
        case EN_PHOTO_ROTATE_180:
            return (-m_s16PhotoOffsetY*m_u16ZoomDenominatorRotate/m_u16ZoomNumeratorRotate);
        case EN_PHOTO_ROTATE_270:
            return (-m_s16PhotoOffsetX*m_u16ZoomDenominatorRotate/m_u16ZoomNumeratorRotate);
        default:
            return m_s16PhotoOffsetY*m_u16ZoomDenominatorRotate/m_u16ZoomNumeratorRotate;
        break;
    }
}

U16 _MApp_Photo_GetZoomCaptureWidth(void)
{
    switch(m_enRotation)
    {
        case EN_PHOTO_ROTATE_0:
            return m_u16ZoomCaptureWidth;
        case EN_PHOTO_ROTATE_90:
            return m_u16ZoomCaptureWidth;
        case EN_PHOTO_ROTATE_180:
            return m_u16ZoomCaptureWidth;
        case EN_PHOTO_ROTATE_270:
            return m_u16ZoomCaptureWidth;
        default:
            return m_u16ZoomCaptureWidth;
        break;
    }
}

U16 _MApp_Photo_GetZoomCaptureHeight(void)
{
    switch(m_enRotation)
    {
        case EN_PHOTO_ROTATE_0:
            return m_u16ZoomCaptureHeight;
        case EN_PHOTO_ROTATE_90:
            return m_u16ZoomCaptureHeight;
        case EN_PHOTO_ROTATE_180:
            return m_u16ZoomCaptureHeight;
        case EN_PHOTO_ROTATE_270:
            return m_u16ZoomCaptureHeight;
        default:
            return m_u16ZoomCaptureHeight;
        break;
    }
}

void MApp_Photo_GetZoomMapInfo(ST_ZOOM_MAP_INFO *ZoomMap)
{
    ZoomMap->ScreenWidth = PHOTO_ADJUSTED_PANEL_WIDTH;
    ZoomMap->ScreenHeight = PHOTO_ADJUSTED_PANEL_HEIGHT;
    ZoomMap->ScreenX = 0;
    ZoomMap->ScreenY = 0;

    ZoomMap->ImageWidth = _MApp_Photo_GetZoomImageWidth();
    ZoomMap->ImageHeight = _MApp_Photo_GetZoomImageHeight();
    ZoomMap->ImageX = (ZoomMap->ScreenWidth - ZoomMap->ImageWidth)/2;
    ZoomMap->ImageY = (ZoomMap->ScreenHeight - ZoomMap->ImageHeight)/2;

    ZoomMap->CaptureWidth = _MApp_Photo_GetZoomCaptureWidth();
    ZoomMap->CaptureHeight = _MApp_Photo_GetZoomCaptureHeight();
    ZoomMap->CaptureX = (ZoomMap->ScreenWidth - ZoomMap->CaptureWidth)/2 + _MApp_Photo_GetZoomCaptureOffsetX();
    ZoomMap->CaptureY = (ZoomMap->ScreenHeight - ZoomMap->CaptureHeight)/2 + _MApp_Photo_GetZoomCaptureOffsetY();

    PHOTO_DISP_MSG(printf("ScreenX: %d, ScreenY: %d, ScreenWidth: %d, ScreenHeight: %d\n", ZoomMap->ScreenX, ZoomMap->ScreenY, ZoomMap->ScreenWidth, ZoomMap->ScreenHeight));
    PHOTO_DISP_MSG(printf("ImageX: %d, ImageY: %d, ImageWidth: %d, ImageHeight: %d\n", ZoomMap->ImageX, ZoomMap->ImageY, ZoomMap->ImageWidth, ZoomMap->ImageHeight));
    PHOTO_DISP_MSG(printf("CaptureX: %d, CaptureY: %d, CaptureWidth: %d, CaptureHeight: %d\n", ZoomMap->CaptureX, ZoomMap->CaptureY, ZoomMap->CaptureWidth, ZoomMap->CaptureHeight));

}

static void MApp_Photo_ShrinkZoomImage(GEBitBltInfo *pstBitbltInfo, GEPitBaseInfo *pstPitBaseInfo)
{
    ST_PHOTO_SHRINK_SETTING stShrinkSetting;
    memset(&stShrinkSetting, 0, sizeof(ST_PHOTO_SHRINK_SETTING));

    stShrinkSetting.enRotation = stPhotoInstanceInfo.enRotation;
    stShrinkSetting.u32SpecialEffectBuffer0 = PHOTO_SHRINK_BUFFER_0_ADDR;
    stShrinkSetting.u32SpecialEffectBuffer0Length = PHOTO_THUMBNAIL_SHRINK_BUFFER_0_SIZE;
    stShrinkSetting.u32SpecialEffectBuffer1 = PHOTO_SHRINK_BUFFER_1_ADDR;
    stShrinkSetting.u32SpecialEffectBuffer1Length = PHOTO_THUMBNAIL_SHRINK_BUFFER_1_SIZE;

    MApp_Photo_ShrinkImage(pstBitbltInfo, pstPitBaseInfo, &stShrinkSetting);
}

static void MApp_Photo_OutputZoomImage(void)
{
    GEBitBltInfo stBitbltInfo;
    GEPitBaseInfo stPitBaseInfo;

    memset(&stBitbltInfo, 0, sizeof(GEBitBltInfo));
    memset(&stPitBaseInfo, 0, sizeof(GEPitBaseInfo));

    if (stPhotoInstanceInfo.stSrcImg.u8FbFmt == GFX_FMT_ARGB8888)
        stPitBaseInfo.sb_pit = stPhotoInstanceInfo.stSrcImg.u16BuffW * 4; // 4 bytes per pixel
    else
        stPitBaseInfo.sb_pit = stPhotoInstanceInfo.stSrcImg.u16BuffW * 2; // 2 bytes per pixel
    stPitBaseInfo.sb_base = stPhotoInstanceInfo.stSrcImg.u32BuffAddr;

    if (stPhotoInstanceInfo.stOutputImg.u8FbFmt == GFX_FMT_ARGB8888)
        stPitBaseInfo.db_pit = stPhotoInstanceInfo.stOutputImg.u16BuffW * 4; // 4 bytes per pixel
    else
        stPitBaseInfo.db_pit = stPhotoInstanceInfo.stOutputImg.u16BuffW * 2; // 2 bytes per pixel
    stPitBaseInfo.db_base = stPhotoInstanceInfo.stOutputImg.u32BuffAddr;

    stBitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;
    stBitbltInfo.BmpFlag = GFXDRAW_FLAG_DEFAULT;
    stBitbltInfo.dst_fm = stPhotoInstanceInfo.stOutputImg.u8FbFmt;
    stBitbltInfo.src_fm = stPhotoInstanceInfo.stSrcImg.u8FbFmt;

    stBitbltInfo.src_width = stPhotoInstanceInfo.stResizedImg.u16RectW;
    stBitbltInfo.src_height = stPhotoInstanceInfo.stResizedImg.u16RectH;
    if (stPhotoInstanceInfo.enRotation == EN_PHOTO_ROTATE_180)
    {
        stBitbltInfo.BitbltCoordinate.v2_x = stPhotoInstanceInfo.stResizedImg.u16RectX + stBitbltInfo.src_width - 1;
        stBitbltInfo.BitbltCoordinate.v2_y = stPhotoInstanceInfo.stResizedImg.u16RectY + stBitbltInfo.src_height - 1;
    }
    else
    {
        stBitbltInfo.BitbltCoordinate.v2_x = stPhotoInstanceInfo.stResizedImg.u16RectX;
        stBitbltInfo.BitbltCoordinate.v2_y = stPhotoInstanceInfo.stResizedImg.u16RectY;
    }

    stBitbltInfo.BitbltCoordinate.direction = 0; // TODO: what's this?
    stBitbltInfo.BitbltCoordinate.v0_x = stPhotoInstanceInfo.stOutputImg.u16RectX;
    stBitbltInfo.BitbltCoordinate.v0_y = stPhotoInstanceInfo.stOutputImg.u16RectY;
    if ((stPhotoInstanceInfo.enRotation == EN_PHOTO_ROTATE_90) || (stPhotoInstanceInfo.enRotation == EN_PHOTO_ROTATE_270))
    {
        stBitbltInfo.BitbltCoordinate.width = stPhotoInstanceInfo.stOutputImg.u16RectH;
        stBitbltInfo.BitbltCoordinate.height = stPhotoInstanceInfo.stOutputImg.u16RectW;
    }
    else
    {
        stBitbltInfo.BitbltCoordinate.width = stPhotoInstanceInfo.stOutputImg.u16RectW;
        stBitbltInfo.BitbltCoordinate.height = stPhotoInstanceInfo.stOutputImg.u16RectH;
    }

    msAPI_OSD_SetClipWindow(0, 0, stPhotoInstanceInfo.stOutputImg.u16BuffW, stPhotoInstanceInfo.stOutputImg.u16BuffH);
    msAPI_GE_SetNearestMode(FALSE);

    // apply rotation
    switch (stPhotoInstanceInfo.enRotation)
    {
        case EN_PHOTO_ROTATE_90:
            msAPI_GE_SetRotate(GEROTATE_90);
            break;
        case EN_PHOTO_ROTATE_180:
            msAPI_GE_SetMirror(1, 1);
            break;
        case EN_PHOTO_ROTATE_270:
            msAPI_GE_SetRotate(GEROTATE_270);
            break;
        default: // 0, 360 or anything else
            break;
    }

    // shrink src image if the width or height of destination buffer is less than 1/2
    MApp_Photo_ShrinkZoomImage(&stBitbltInfo, &stPitBaseInfo);
    stBitbltInfo.src_height--; // Fix the bottom garbage line.

    PHOTO_DISP_MSG(printf("Img Out\n"));
    PHOTO_DISP_MSG(printf("stBitbltInfo: \n"));
    PHOTO_DISP_MSG(printf("\ttype flag: %u\n", stBitbltInfo.BitBltTypeFlag));
    PHOTO_DISP_MSG(printf("\tbmp flag: %u\n", stBitbltInfo.BmpFlag));
    PHOTO_DISP_MSG(printf("\tdest fmt: %u\n", stBitbltInfo.dst_fm));
    PHOTO_DISP_MSG(printf("\tsrc fmt: %u\n", stBitbltInfo.src_fm));
    PHOTO_DISP_MSG(printf("\tbmp hnd: %d\n", stBitbltInfo.bmphandle));
    PHOTO_DISP_MSG(printf("\tsrc width: %u\n", stBitbltInfo.src_width));
    PHOTO_DISP_MSG(printf("\tsrc height: %u\n", stBitbltInfo.src_height));
    PHOTO_DISP_MSG(printf("\tcoord v0x: %u\n", stBitbltInfo.BitbltCoordinate.v0_x));
    PHOTO_DISP_MSG(printf("\tcoord v0y: %u\n", stBitbltInfo.BitbltCoordinate.v0_y));
    PHOTO_DISP_MSG(printf("\tcoord width: %u\n", stBitbltInfo.BitbltCoordinate.width));
    PHOTO_DISP_MSG(printf("\tcoord height: %u\n", stBitbltInfo.BitbltCoordinate.height));
    PHOTO_DISP_MSG(printf("\tcoord v2x: %u\n", stBitbltInfo.BitbltCoordinate.v2_x));
    PHOTO_DISP_MSG(printf("\tcoord v2y: %u\n", stBitbltInfo.BitbltCoordinate.v2_y));
    PHOTO_DISP_MSG(printf("\tcoord direct: %u\n", stBitbltInfo.BitbltCoordinate.direction));
    PHOTO_DISP_MSG(printf("stPitBaseInfo: \n"));
    PHOTO_DISP_MSG(printf("\tsrc pitch: %x\n",stPitBaseInfo.sb_pit));
    PHOTO_DISP_MSG(printf("\tdst pitch: %x\n",stPitBaseInfo.db_pit));
    PHOTO_DISP_MSG(printf("\tsrc base: %x\n",stPitBaseInfo.sb_base));
    PHOTO_DISP_MSG(printf("\tdst base: %x\n",stPitBaseInfo.db_base));

    msAPI_GE_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_PC, GFX_YUV_OUT_255, GFX_YUV_IN_255, GFX_YUV_YUYV, GFX_YUV_YUYV);
    msAPI_GE_SetPatchMode(TRUE);

    // output image to destination buffer
    msAPI_GE_BitBlt(&stBitbltInfo, &stPitBaseInfo);
    // after BitBlt, flush cmd
    MApi_GFX_FlushQueue();

    msAPI_GE_SetPatchMode(FALSE);

    PHOTO_DISP_MSG(printf("2.end, sx: %u, sy: %u, sw: %u, sh: %u, sp: %u (0x%x)\n",
            stBitbltInfo.BitbltCoordinate.v2_x,
            stBitbltInfo.BitbltCoordinate.v2_y,
            stBitbltInfo.src_width,
            stBitbltInfo.src_height,
            stPitBaseInfo.sb_pit,
            stPitBaseInfo.sb_pit));
    PHOTO_DISP_MSG(printf("2.end, ox: %u, oy: %u, ow: %u, oh: %u, dp: %u (0x%x)\n",
            stBitbltInfo.BitbltCoordinate.v0_x,
            stBitbltInfo.BitbltCoordinate.v0_y,
            stBitbltInfo.BitbltCoordinate.width,
            stBitbltInfo.BitbltCoordinate.height,
            stPitBaseInfo.db_pit,
            stPitBaseInfo.db_pit));

    // NOTE: it's critical to reset GE registers after rotation
    msAPI_GE_SetMirror(0, 0);
    msAPI_GE_SetRotate(GEROTATE_0);

    // restore clip window to full screen
    msAPI_OSD_SetClipWindow(0, 0, g_IPanel.Width(), g_IPanel.Height());

    PHOTO_DISP_MSG(printf("-------Separate Line-------\n"));
}


void MApp_Photo_Display_ZoomImage(
        ST_PHOTO_CAPTURE_RECT *stTo,
        ST_PHOTO_CAPTURE_RECT *stFrom,
        EN_PHOTO_ALIGNMENT enAlign,
        EN_PHOTO_RESIZE enResize)
{
    // parameters checking
    if ((stTo == NULL) || (stFrom == NULL))
    {
        __ASSERT(0);
        return;
    }

    if ((stTo->u32BuffAddr == 0) || (stTo->u16BuffW == 0) || (stTo->u16BuffH == 0)) // destination buffer can't be right
    {
        __ASSERT(0);
        return;
    }

    if ((stTo->u8FbFmt != GFX_FMT_RGB565)
            && (stTo->u8FbFmt != GFX_FMT_ARGB8888)
            && (stTo->u8FbFmt != GFX_FMT_ARGB1555)
            && (stTo->u8FbFmt != GFX_FMT_ARGB4444)
            && (stTo->u8FbFmt != GFX_FMT_ARGB1555_DST)
            && (stTo->u8FbFmt != GFX_FMT_YUV422))
    {
        PHOTO_DISP_MSG(printf("[PHOTO DISPLAY] photo thumbnail output format (%d) isn't supported.\n", stTo->u8FbFmt));
        __ASSERT(0);
    }

    if ((stTo->u16RectW == 0) || (stTo->u16RectH == 0)) // specified destination isn't a rectangle
    {
        __ASSERT(0);
        return;
    }
    if ((enAlign >= EN_PHOTO_ALIGN_NOT_SUPPORT) || (enResize >= EN_PHOTO_RESIZE_NOT_SUPPORT)) // specified alignment or resize method not support
    {
        __ASSERT(0);
        return;
    }

    // reset variables
    memset(&stPhotoInstanceInfo, 0, sizeof(stPhotoInstanceInfo));
    stPhotoInstanceInfo.enState = EN_PHOTO_INFO_NONE;
    enPhotoZooming = EN_PHOTO_ZOOM_1;

    stPhotoInstanceInfo.stSrcImg = *stFrom;
    stPhotoInstanceInfo.stDstBuff = *stTo;

    // instance information initial
    stPhotoInstanceInfo.enRotation = m_enRotation;
    stPhotoInstanceInfo.enZooming = EN_PHOTO_ZOOM_1;
    stPhotoInstanceInfo.enZoomingNew = EN_PHOTO_ZOOM_1;

    // fill in necessary information for jpeg special effect (rotate/zooming) and output desired picture
    stPhotoInstanceInfo.enAlign = enAlign;
    stPhotoInstanceInfo.enResize = enResize;
    stPhotoInstanceInfo.u16ResizeRatio = 100;

    stPhotoInstanceInfo.stSrcImg.u16BuffW = PHOTO_ADJUSTED_PANEL_WIDTH;
    stPhotoInstanceInfo.stSrcImg.u16BuffH = m_u16PhotoSrcHeight;
    stPhotoInstanceInfo.stSrcImg.u32BuffAddr = PHOTO_DISPLAY_SRC_BUFFER_ADDR;
    stPhotoInstanceInfo.stSrcImg.u8FbFmt = GFX_FMT_YUV422;

    stPhotoInstanceInfo.stResizedImg = stPhotoInstanceInfo.stSrcImg;

    stPhotoInstanceInfo.enState = EN_PHOTO_INFO_ALL_COLLECT;

    MApp_Photo_ApplyEffect();
    MApp_Photo_OutputZoomImage();
}
#endif //ENABLE_ZOOM_MAP
#endif // #if PHOTO_SLIDE_SHOW_EFFECT

#endif  //#if (ENABLE_DMP)

#undef _MAPP_PHOTO_DISPLAY_C_

