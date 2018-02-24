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

#ifndef _MAPP_PHOTO_DISPLAY_H_
#define _MAPP_PHOTO_DISPLAY_H_

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

///////////////////////////////////////////////////////////////////////////////
/// @file   mapp_photo_display.h
/// This file contains the interface for multimedia (MM) photo part
/// @author MStar Semiconductor Inc.
/// @brief  photo module, including display
///////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// Include Files
//------------------------------------------------------------------------------
#include "datatype.h"
//#include "mvideo_if.h"
#include "MApp_Exit.h"
#include "msAPI_OSD.h"
#include "MApp_UiMediaPlayer_Define.h"
#ifdef _MAPP_PHOTO_C_
#define INTERFACE
#else
#define INTERFACE extern
#endif // #if _MAPP_PHOTO_C_

//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
#define SAVE_BW_PHOTO_SLIDE_SHOW        (0)
//for gif animation, after some frames decoded done or all decoded done, it will display.
#define MAX_GIF_BUFF_DISPLAY                  (4)
//-------------------------------------------------------------------------------------------------
// Type and Structure Declaration
//-------------------------------------------------------------------------------------------------
typedef enum
{
    EN_PHOTO_ZOOM_1_8,
    EN_PHOTO_ZOOM_1_4,
    EN_PHOTO_ZOOM_1_2,
    EN_PHOTO_ZOOM_1, // X1
    EN_PHOTO_ZOOM_2, // X2
    EN_PHOTO_ZOOM_4, // X4
    EN_PHOTO_ZOOM_8, // X8
    EN_PHOTO_ZOOM_NOT_SUPPORT,
} EN_PHOTO_ZOOMING;

typedef enum
{
    EN_PHOTO_ROTATE_0 = 0,
    EN_PHOTO_ROTATE_90,
    EN_PHOTO_ROTATE_180,
    EN_PHOTO_ROTATE_270,
    EN_PHOTO_ROTATE_360,
    EN_PHOTO_ROTATE_NOT_SUPPORT,
} EN_PHOTO_ROTATION;

typedef enum
{
    EN_PHOTO_MOVE_UP = 0,
    EN_PHOTO_MOVE_DOWN,
    EN_PHOTO_MOVE_LEFT,
    EN_PHOTO_MOVE_RIGHT,
    EN_PHOTO_MOVE_NOT_SUPPORT,
} EN_PHOTO_DIRECTION;

typedef enum
{
    EN_PHOTO_ALIGN_MIDDLE_CENTERED = 0,
    EN_PHOTO_ALIGN_TOP_CENTERED,
    EN_PHOTO_ALIGN_BOTTOM_CENTERED,
    EN_PHOTO_ALIGN_MIDDLE_LEFT,
    EN_PHOTO_ALIGN_TOP_LEFT,
    EN_PHOTO_ALIGN_BOTTOM_LEFT,
    EN_PHOTO_ALIGN_MIDDLE_RIGHT,
    EN_PHOTO_ALIGN_TOP_RIGHT,
    EN_PHOTO_ALIGN_BOTTOM_RIGHT,
    EN_PHOTO_ALIGN_NOT_SUPPORT,
} EN_PHOTO_ALIGNMENT;

typedef enum
{
    EN_PHOTO_IMAGE_SIZE = 0,
    EN_PHOTO_FIT_BOUNDARY, //depends on width OR height of view window
    EN_PHOTO_FIT_VIEW_WINDOW,
    EN_PHOTO_RESIZE_NOT_SUPPORT,
} EN_PHOTO_RESIZE;

typedef struct
{
    U16 u16RectX; // the x coordinate of the capturing/captured rectangle
    U16 u16RectY; // the y coordinate of the capturing/captured rectangle
    U16 u16RectW; // the width coordinate of the capturing/captured rectangle
    U16 u16RectH; // the height coordinate of the capturing/captured rectangle

    U32 u32BuffAddr; // the address of the buffer that contains the capturing/captured rectangle
    U16 u16BuffW; // the width of the buffer that contains the capturing/captured rectangle
    U16 u16BuffH; // the height of the buffer that contains the capturing/captured rectangle
    U16 u8FbFmt; // the format of the buffer that contains the capturing/captured rectangle
} ST_PHOTO_CAPTURE_RECT;

#if PHOTO_SLIDE_SHOW_EFFECT
typedef enum
{
    E_SLIDE_SHOW_EFFECT_NORMAL,
#if (ENABLE_PHOTO_TRANS_EFFECT_BLOCKS)
    E_SLIDE_SHOW_EFFECT_HORZ_BLOCKS_TOPLEFT,
    E_SLIDE_SHOW_EFFECT_HORZ_BLOCKS_TOPRIGHT,
    E_SLIDE_SHOW_EFFECT_HORZ_BLOCKS_BOTTOMLEFT,
    E_SLIDE_SHOW_EFFECT_HORZ_BLOCKS_BOTTOMRIGHT,
    E_SLIDE_SHOW_EFFECT_VERT_BLOCKS_TOPLEFT,
    E_SLIDE_SHOW_EFFECT_VERT_BLOCKS_TOPRIGHT,
    E_SLIDE_SHOW_EFFECT_VERT_BLOCKS_BOTTOMLEFT,
    E_SLIDE_SHOW_EFFECT_VERT_BLOCKS_BOTTOMRIGHT,
    E_SLIDE_SHOW_EFFECT_HORZ_ZIGZAG_BLOCKS_TOPLEFT,
    E_SLIDE_SHOW_EFFECT_HORZ_ZIGZAG_BLOCKS_TOPRIGHT,
    E_SLIDE_SHOW_EFFECT_HORZ_ZIGZAG_BLOCKS_BOTTOMLEFT,
    E_SLIDE_SHOW_EFFECT_HORZ_ZIGZAG_BLOCKS_BOTTOMRIGHT,
    E_SLIDE_SHOW_EFFECT_VERT_ZIGZAG_BLOCKS_TOPLEFT,
    E_SLIDE_SHOW_EFFECT_VERT_ZIGZAG_BLOCKS_TOPRIGHT,
    E_SLIDE_SHOW_EFFECT_VERT_ZIGZAG_BLOCKS_BOTTOMLEFT,
    E_SLIDE_SHOW_EFFECT_VERT_ZIGZAG_BLOCKS_BOTTOMRIGHT,
    E_SLIDE_SHOW_EFFECT_RANDOM_BLOCKS,
    E_SLIDE_SHOW_EFFECT_BLOCKS_RANDOM,
#endif  // #if (ENABLE_PHOTO_TRANS_EFFECT_BLOCKS)
#if (ENABLE_PHOTO_TRANS_EFFECT_DIAGONAL_BLOCKS)
    E_SLIDE_SHOW_EFFECT_DIAGONAL_BLOCKS_TOPLEFT,
    E_SLIDE_SHOW_EFFECT_DIAGONAL_BLOCKS_TOPRIGHT,
    E_SLIDE_SHOW_EFFECT_DIAGONAL_BLOCKS_BOTTOMLEFT,
    E_SLIDE_SHOW_EFFECT_DIAGONAL_BLOCKS_BOTTOMRIGHT,
    E_SLIDE_SHOW_EFFECT_DIAGONAL_BLOCKS_RANDOM,
#endif  // #if (ENABLE_PHOTO_TRANS_EFFECT_DIAGONAL_BLOCKS)
#if (ENABLE_PHOTO_TRANS_EFFECT_WIPE)
    E_SLIDE_SHOW_EFFECT_BARWIPE_LEFT2RIGHT,
    E_SLIDE_SHOW_EFFECT_BARWIPE_RIGHT2LEFT,
    E_SLIDE_SHOW_EFFECT_BARWIPE_TOP2BOTTOM,
    E_SLIDE_SHOW_EFFECT_BARWIPE_BOTTOM2TOP,
    E_SLIDE_SHOW_EFFECT_BOXWIPE_TOPLEFT,
    E_SLIDE_SHOW_EFFECT_BOXWIPE_TOPRIGHT,
    E_SLIDE_SHOW_EFFECT_BOXWIPE_BOTTOMLEFT,
    E_SLIDE_SHOW_EFFECT_BOXWIPE_BOTTOMRIGHT,
    E_SLIDE_SHOW_EFFECT_BARNDOORWIPE_HORIZONTAL_OPEN,
    E_SLIDE_SHOW_EFFECT_BARNDOORWIPE_HORIZONTAL_CLOSE,
    E_SLIDE_SHOW_EFFECT_BARNDOORWIPE_VERTICAL_OPEN,
    E_SLIDE_SHOW_EFFECT_BARNDOORWIPE_VERTICAL_CLOSE,
    E_SLIDE_SHOW_EFFECT_BOXWIPE_TOPCENTER,
    E_SLIDE_SHOW_EFFECT_BOXWIPE_RIGHTCENTER,
    E_SLIDE_SHOW_EFFECT_BOXWIPE_BOTTOMCENTER,
    E_SLIDE_SHOW_EFFECT_BOXWIPE_LEFTCENTER,
    E_SLIDE_SHOW_EFFECT_IRISWIPE_CENTER,
    E_SLIDE_SHOW_EFFECT_IRISWIPE_OUTER,
    E_SLIDE_SHOW_EFFECT_4BARWIPE_HORIZONTAL_FROM_TOP,
    E_SLIDE_SHOW_EFFECT_4BARWIPE_HORIZONTAL_FROM_BOTTOM,
    E_SLIDE_SHOW_EFFECT_4BARWIPE_VERTICAL_FROM_LEFT,
    E_SLIDE_SHOW_EFFECT_4BARWIPE_VERTICAL_FROM_RIGHT,
    E_SLIDE_SHOW_EFFECT_WIPE_RANDOM,
#endif  // #if (ENABLE_PHOTO_TRANS_EFFECT_WIPE)
#if (ENABLE_PHOTO_TRANS_EFFECT_SLIDE)
    E_SLIDE_SHOW_EFFECT_BARSLIDE_LEFT2RIGHT,
    E_SLIDE_SHOW_EFFECT_BARSLIDE_RIGHT2LEFT,
    E_SLIDE_SHOW_EFFECT_BARSLIDE_TOP2BOTTOM,
    E_SLIDE_SHOW_EFFECT_BARSLIDE_BOTTOM2TOP,
    E_SLIDE_SHOW_EFFECT_BOXSLIDE_TOPLEFT,
    E_SLIDE_SHOW_EFFECT_BOXSLIDE_TOPRIGHT,
    E_SLIDE_SHOW_EFFECT_BOXSLIDE_BOTTOMLEFT,
    E_SLIDE_SHOW_EFFECT_BOXSLIDE_BOTTOMRIGHT,
    E_SLIDE_SHOW_EFFECT_BARNDOORSLIDE_HORIZONTAL_OPEN,
    E_SLIDE_SHOW_EFFECT_BARNDOORSLIDE_HORIZONTAL_CLOSE,
    E_SLIDE_SHOW_EFFECT_BARNDOORSLIDE_VERTICAL_OPEN,
    E_SLIDE_SHOW_EFFECT_BARNDOORSLIDE_VERTICAL_CLOSE,
    E_SLIDE_SHOW_EFFECT_4BARSLIDE_HORIZONTAL_FROM_TOP,
    E_SLIDE_SHOW_EFFECT_4BARSLIDE_HORIZONTAL_FROM_BOTTOM,
    E_SLIDE_SHOW_EFFECT_4BARSLIDE_VERTICAL_FROM_LEFT,
    E_SLIDE_SHOW_EFFECT_4BARSLIDE_VERTICAL_FROM_RIGHT,
    E_SLIDE_SHOW_EFFECT_SLIDE_RANDOM,
#endif  // #if (ENABLE_PHOTO_TRANS_EFFECT_SLIDE)
#if (ENABLE_PHOTO_TRANS_EFFECT_FADE)
    E_SLIDE_SHOW_EFFECT_FADE,
    E_SLIDE_SHOW_EFFECT_FADE_RANDOM,
#endif  // #if (ENABLE_PHOTO_TRANS_EFFECT_FADE)
//    E_SLIDE_SHOW_EFFECT_FADEIN,
#if 0
    E_SLIDE_SHOW_EFFECT_ZIGZAG_TOPLEFT,
    E_SLIDE_SHOW_EFFECT_ZIGZAG_TOPRIGHT,
    E_SLIDE_SHOW_EFFECT_ZIGZAG_BOTTOMLEFT,
    E_SLIDE_SHOW_EFFECT_ZIGZAG_BOTTOMRIGHT,
    E_SLIDE_SHOW_EFFECT_MOSAIC,
    E_SLIDE_SHOW_EFFECT_SPIRAL_CENTER,
    E_SLIDE_SHOW_EFFECT_SPIRAL_OUTER,
    E_SLIDE_SHOW_EFFECT_HORIZONTAL_BAR,
    E_SLIDE_SHOW_EFFECT_VERTICAL_BAR,
    E_SLIDE_SHOW_EFFECT_PUSH_LEFT,
    E_SLIDE_SHOW_EFFECT_PUSH_TOP,
    E_SLIDE_SHOW_EFFECT_PUSH_TOPLEFT,
    E_SLIDE_SHOW_EFFECT_PUSH_RIGHTTOP,
    E_SLIDE_SHOW_EFFECT_PUSH_BOTTOMLEFT,
    E_SLIDE_SHOW_EFFECT_PUSH_BOTTOMRIGHT,
    E_SLIDE_SHOW_EFFECT_FROM_LEFTRIGHT,
    E_SLIDE_SHOW_EFFECT_FROM_TOPBOTTOM,
    E_SLIDE_SHOW_EFFECT_FROM_CENTER_HORIZONTAL,
    E_SLIDE_SHOW_EFFECT_FROM_CENTER_VERTICAL,
#endif
    E_SLIDE_SHOW_EFFECT_NUM,
    E_SLIDE_SHOW_EFFECT_RANDOM,
}EN_PHOTO_SLIDE_SHOW_EFFECT;

typedef struct
{
   S16  ScreenX;
   S16  ScreenY;
   S16  ScreenWidth;
   S16  ScreenHeight;
   S16  ImageX;
   S16  ImageY;
   S16  ImageWidth;
   S16  ImageHeight;
   S16  CaptureX;
   S16  CaptureY;
   S16  CaptureWidth;
   S16  CaptureHeight;
} ST_ZOOM_MAP_INFO;
#endif

typedef struct
{
    U32 u32SpecialEffectBuffer0;
    U32 u32SpecialEffectBuffer0Length;
    U32 u32SpecialEffectBuffer1;
    U32 u32SpecialEffectBuffer1Length;
    EN_PHOTO_ROTATION enRotation;
} ST_PHOTO_SHRINK_SETTING;

//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Extern Functions
//------------------------------------------------------------------------------
INTERFACE BOOLEAN MApp_Photo_Zooming(EN_PHOTO_ZOOMING enZooming);
INTERFACE BOOLEAN MApp_Photo_MoveViewWindow(EN_PHOTO_DIRECTION enDirection, U16 u16LineCount);
INTERFACE BOOLEAN MApp_Photo_Rotate(EN_PHOTO_ROTATION enRotation);

INTERFACE void MApp_Photo_Display_SetViewWin(U16 u16X, U16 u16Y, U16 u16Width, U16 u16Height);
INTERFACE void MApp_Photo_Display(BOOLEAN bIsPreview);
INTERFACE void MApp_Photo_MPODisplay(BOOLEAN bIsPreview);
INTERFACE void MApp_Photo_Display_Stop(void);
INTERFACE void MApp_Photo_GetImageCoordinatesOnScreen(U16 *pu16X, U16 *pu16Y, U16 *pu16W, U16 *pu16H);
INTERFACE void MApp_Photo_GetImageCoordinatesOnSource(U16 *pu16X, U16 *pu16Y, U16 *pu16W, U16 *pu16H);
INTERFACE BOOLEAN MApp_Photo_InitFullScreenDisplay(void);
INTERFACE BOOLEAN MApp_Photo_InitPreviewDisplay(void);
INTERFACE EN_PHOTO_ROTATION MApp_Photo_GetRotationMode(void);
INTERFACE void MApp_Photo_SlideShow(BOOLEAN bEnable);
INTERFACE void MApp_Photo_Display_Thumbnail(
        ST_PHOTO_CAPTURE_RECT *stTo,
        ST_PHOTO_CAPTURE_RECT *stFrom,
        EN_PHOTO_ALIGNMENT enAlign,
        EN_PHOTO_RESIZE enResize);

INTERFACE void MApp_Photo_Buf_Init(void);
INTERFACE void MApp_Photo_ShrinkSrcImage_MovieThumbnail(GEBitBltInfo *pstBitbltInfo, GEPitBaseInfo *pstPitBaseInfo);
INTERFACE void MApp_Photo_GetInterBuffInfo(U16 *pu16Width, U16 *pu16Height, U32 *pu32Addr, U32 *pu32Len);
INTERFACE void MApp_Photo_GIFDecodeDone(BOOLEAN bIsAllFrameDecodeDone);
INTERFACE BOOLEAN  MApp_Photo_GIFIsDisplayDone(void);
INTERFACE void MApp_Photo_GIFDisplay(BOOLEAN bIsPreview);
INTERFACE void MApp_Photo_GIFResetDisplay(void);

INTERFACE void MApp_Photo_ShrinkImage(GEBitBltInfo *pstBitbltInfo, GEPitBaseInfo *pstPitBaseInfo, ST_PHOTO_SHRINK_SETTING *pstShrinkSetting);

#if PHOTO_SLIDE_SHOW_EFFECT
INTERFACE void MApp_Photo_SetSlideShowEffect(EN_PHOTO_SLIDE_SHOW_EFFECT eSlideShowEffect);
INTERFACE EN_PHOTO_SLIDE_SHOW_EFFECT MApp_Photo_GetSlideShowEffect(void);
INTERFACE void MApp_Photo_GetZoomMapInfo(ST_ZOOM_MAP_INFO *ZoomMap);
INTERFACE void MApp_Photo_Display_ZoomImage(
        ST_PHOTO_CAPTURE_RECT *stTo,
        ST_PHOTO_CAPTURE_RECT *stFrom,
        EN_PHOTO_ALIGNMENT enAlign,
        EN_PHOTO_RESIZE enResize);
#endif
#if ENABLE_4K2K
INTERFACE void MApp_Photo_4K2K_DisplayByGOP(BOOLEAN bIsPreview);
INTERFACE void MApp_Photo_Display_Disable4K2KPhotoDisplay(void);
#endif
#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#undef INTERFACE

#endif // _MAPP_PHOTO_H_

