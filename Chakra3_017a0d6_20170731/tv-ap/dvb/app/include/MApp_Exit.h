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
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef MAPP_EXIT_H
#define MAPP_EXIT_H

#include "Board.h"

#if 0 //ZUI
typedef enum
{
    EXIT_TV_NULL = 0,
    EXIT_TV_TRAN_MENU,
    EXIT_TV_TRAN_CHANNELCHANGE,
    EXIT_TV_TRAN_STANDBY,
    EXIT_TV_TRAN_SCAN,
    EXIT_TV_TRAN_USB,

    EXIT_TV_TRAN_TT,
    EXIT_TV_TRAN_MMI,
    EXIT_TRAN_ANALOGINPUTS_WAIT,
#if ENABLE_DMP
    EXIT_TV_TRAN_MEDIAPLAYER,
#endif

    EXIT_ANALOGINPUTS_NULL,
    EXIT_ANALOGINPUTS_TRAN_ANALOGINPUTS_WAIT,
    EXIT_ANALOGINPUTS_TRAN_MENU,
    EXIT_ANALOGINPUTS_TRAN_CHANNELCHANGE,
    EXIT_ANALOGINPUTS_TRAN_STANDBY,
#if ENABLE_DMP
    EXIT_ANALOGINPUTS_TRAN_MEDIAPLAYER,
#endif

    EXIT_TT_NULL,
    EXIT_TT_EXIT,
    EXIT_TT_TRAN_STANDBY,
    EXIT_TT_TRAN_CHANNELCHANGE,
    EXIT_TT_TRAN_ANALOG_SHOW_BANNER,
    EXIT_TV_TRAN_SUBTITLE,

    #if ENABLE_CI
    EXIT_ANALOGINPUTS_TRAN_MMI,
    #endif
    EXIT_MENU_NULL,
    EXIT_MENU_TRAN_STANDBY,
    EXIT_MENU_TRAN_SCAN,
    EXIT_MENU_TRAN_EPG,
#if ENABLE_DMP
    EXIT_MENU_TRAN_MEDIA_PLAYER,    //hardes
#endif
    EXIT_MENU_CLOSE,

    EXIT_SUBMENU_NULL,
    EXIT_SUBMENU_END,
    EXIT_SUBMENU_EXIT,
    EXIT_SUBMENU_TRAN_STANDBY,
    EXIT_SUBMENU_TRAN_UIMENU,
    EXIT_CHANNELCHANGE_NULL,
    EXIT_CHANNELCHANGE_DONE,
    EXIT_SCAN_NULL,
    // EXIT_SCAN_TRAN_MENU,
    EXIT_SCAN_TRAN_WAIT,
    EXIT_SCAN_TRAN_PREVIOUS,
    EXIT_SCAN_TRAN_CHANNELCHANGE,
    EXIT_SCAN_TRAN_STANDBY,

    EXIT_ATV_SCAN_NULL,
    EXIT_ATV_SCAN_TRAN_WAIT,
    EXIT_ATV_SCAN_TRAN_PREVIOUS,
    EXIT_ATV_SCAN_TRAN_CHANNELCHANGE,
    EXIT_ATV_SCAN_TRAN_STANDBY,
    EXIT_ATV_SCAN_TRAN_DTVSCAN,

    EXIT_STANDBY_NULL,
    EXIT_STANDBY_ENTER,
    EXIT_STANDBY_EXIT,
    EXIT_STANDBY_TRAN_CHANNELCHANGE,

    EXIT_TV_TRAN_EPG,
    EXIT_EPGUI_NULL,
    EXIT_EPGUI_DONE,
    EXIT_EPGUI_EXIT,
    EXIT_EPGUI_TRAN_STANDBY,
    EXIT_EPGUI_TRAN_MENU,

    EXIT_MMI_NULL,
    EXIT_MMI_EXIT,
    ,

    #ifdef SUBTITLE
    EXIT_SUBTITLE_DECODING,
    EXIT_SUBTITLE_EXIT,
    #endif

    EXIT_USB_DOWNLOAD_TRAN_REBOOT,
    EXIT_USB_DOWNLOAD_CANCEL,
    EXIT_USB_DOWNLOAD_WAIT,

#if ENABLE_DMP
    EXIT_MPLAYER_NULL,
    EXIT_MPLAYER_EXIT,
    EXIT_MPLAYER_TRAN_STANDBY,
    EXIT_MPLAYER_TRAN_MENU,

    EXIT_PHOTO_DECODING,
    EXIT_PHOTO_DECODE_DONE,
    EXIT_PHOTO_DECODE_NO_THUMBNAIL,
    EXIT_PHOTO_DECODE_FAIL,
    EXIT_PHOTO_EXIT,
    EXIT_PHOTO_PREVIEW_EXIT,
    EXIT_PHOTO_PREVIEW_FAIL,
    EXIT_PHOTO_WAIT,

    EXIT_BMP_DECODING,
    EXIT_BMP_DECODE_DONE,
    EXIT_BMP_DECODE_FAIL,
    EXIT_BMP_EXIT,
    EXIT_BMP_PREVIEW_EXIT,
    EXIT_BMP_PREVIEW_GET_IMG_SIZE,
    EXIT_BMP_WAIT,
    EXIT_BMP_WAIT_PLAY_PREV,

    EXIT_PNG_DECODING,
    EXIT_PNG_DECODE_DONE,
    EXIT_PNG_DECODE_FAIL,
    EXIT_PNG_EXIT,
    EXIT_PNG_PREVIEW_EXIT,
    EXIT_PNG_PREVIEW_GET_IMG_SIZE,
    EXIT_PNG_WAIT,
    EXIT_PNG_WAIT_PLAY_PREV,

    EXIT_MP3_INIT,
    EXIT_MP3_DECODING,
    EXIT_MP3_EXIT,
    EXIT_MP3_TRAN_STANDBY,
    EXIT_MP3_WAIT,
    EXIT_MP3_WAIT_PLAY_PREV,

    EXIT_WMA_INIT,
    EXIT_WMA_DECODING,
    EXIT_WMA_EXIT,
    EXIT_WMA_TRAN_STANDBY,
    EXIT_WMA_WAIT,
    EXIT_WMA_WAIT_PLAY_PREV,

    EXIT_MP4_NULL,
    EXIT_MP4_PREDECODE_OK,
    EXIT_MP4_DECODING,
    EXIT_MP4_EXIT,
    EXIT_MP4_TRAN_STANDBY,
    EXIT_MP4_WAIT,
    EXIT_MP4_WAIT_PLAY_PREV,

    EXIT_VDPLAYER_DECODING,
    EXIT_VDPLAYER_EXIT,
    EXIT_VDPLAYER_TRAN_STANDBY,
    EXIT_VDPLAYER_WAIT,
    EXIT_VDPLAYER_WAIT_PLAY_PREV,

    EXIT_MPEG2_NULL,
    EXIT_MPEG2_PREDECODE_OK,
    EXIT_MPEG2_EXIT,
    EXIT_MPEG2_WAIT,
    EXIT_MPEG2_WAIT_PLAY_PREV,
    EXIT_MENU_EXIT_STORAGESELECT,
#endif  // #if ENABLE_DMP

} EN_RET;
#endif

typedef enum
{
    EXIT_NULL = 0,
    EXIT_CLOSE,

    //for state transition
    EXIT_GOTO_MENU,
    EXIT_GOTO_CHANNELCHANGE,
    EXIT_GOTO_STANDBY,
    EXIT_GOTO_DTVSCAN,
    EXIT_GOTO_ATVSCAN,
#if ENABLE_SBTVD_ATV_SYSTEM
    EXIT_GOTO_CATVSCAN,
#endif
    EXIT_GOTO_SCAN,
#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
    EXIT_GOTO_SCAN_NEW_MUX,
#endif
    EXIT_GOTO_USB,
#if ENABLE_OAD
    EXIT_GOTO_OAD,
#endif
#if 0//NTV_FUNCTION_ENABLE // wait to do
    EXIT_GOTO_NTV_LIST,
#endif
    EXIT_GOTO_INSTALLGUIDE,
    EXIT_GOTO_TT,
    EXIT_GOTO_MMI,
    EXIT_GOTO_SUBTITLE,
    EXIT_GOTO_EPG,
    EXIT_GOTO_EPG_COUNT_DOWN,
    EXIT_GOTO_DTV_MANUALTUNING,
    EXIT_GOTO_ATV_MANUALTUNING,
    EXIT_GOTO_TV,
    EXIT_GOTO_PREVIOUS,
    EXIT_GOTO_INPUTSOURCE,
    EXIT_GOTO_AUDIOLANGUAGE,

#if ENABLE_DMP
    EXIT_GOTO_DMP,
#endif
    EXIT_GOTO_BT,
#ifdef ENABLE_KTV
    EXIT_GOTO_KTV,
#endif
    EXIT_GOTO_OSDPAGE,
    EXIT_GOTO_INFO,
#ifdef ENABLE_YOUTUBE
    EXIT_GOTO_YOUTUBE,
#endif
#ifdef ENABLE_RSS
    EXIT_GOTO_RSS,
#endif
//#ifdef ENABLE_NETFLIX
//    EXIT_GOTO_NETFLIX,
//#endif
#if GAME_ENABLE
    EXIT_GOTO_GAME_LIST,
#endif

#ifdef ENABLE_EXTENSION
    EXIT_GOTO_EXTENSION,
#endif
    EXIT_GOTO_WAIT,
    //for specialized actions
    EXIT_STANDBY_ENTER,
    EXIT_SUBTITLE_DECODING,
    EXIT_SUBTITLE_EXIT,
    EXIT_SUBMENU_END,
    EXIT_USB_DOWNLOAD_TRAN_REBOOT,
    EXIT_USB_DOWNLOAD_CANCEL,
    EXIT_USB_DOWNLOAD_WAIT,
    EXIT_GOTO_ANALOG_SHOW_BANNER,
#if ENABLE_DMP
    EXIT_ANALOGINPUTS_TRAN_DMP,
    EXIT_MPLAYER_NULL,
    EXIT_MPLAYER_EXIT,
    EXIT_MPLAYER_TRAN_STANDBY,
    EXIT_MPLAYER_TRAN_MENU,
    EXIT_MPLAYER_TRAN_INPUTSOURCE,
#if ENABLE_DMP_MINI_MENU
    EXIT_MPLAYER_TRAN_DMP_MINIMENU,
#endif
    EXIT_PHOTO_DECODING,
    EXIT_PHOTO_DECODE_DONE,
    EXIT_PHOTO_DECODE_ONE_FRAME_DONE,
    EXIT_PHOTO_DECODE_NO_THUMBNAIL,
    EXIT_PHOTO_DECODE_FAIL,
    EXIT_PHOTO_EXIT,
    EXIT_PHOTO_PREVIEW_EXIT,
    EXIT_PHOTO_PREVIEW_FAIL,
    EXIT_PHOTO_WAIT,

    EXIT_BMP_DECODING,
    EXIT_BMP_DECODE_DONE,
    EXIT_BMP_DECODE_FAIL,
    EXIT_BMP_EXIT,
    EXIT_BMP_PREVIEW_EXIT,
    EXIT_BMP_PREVIEW_GET_IMG_SIZE,
    EXIT_BMP_WAIT,
    EXIT_BMP_WAIT_PLAY_PREV,

    EXIT_PNG_DECODING,
    EXIT_PNG_DECODE_DONE,
    EXIT_PNG_DECODE_FAIL,
    EXIT_PNG_EXIT,
    EXIT_PNG_PREVIEW_EXIT,
    EXIT_PNG_PREVIEW_GET_IMG_SIZE,
    EXIT_PNG_WAIT,
    EXIT_PNG_WAIT_PLAY_PREV,

    EXIT_MP3_INIT,
    EXIT_MP3_INPUT,
    EXIT_MP3_DECODING,
    EXIT_MP3_EXIT,
    EXIT_MP3_TRAN_STANDBY,
    EXIT_MP3_WAIT,
    EXIT_MP3_WAIT_PLAY_PREV,

    EXIT_WMA_INIT,
    EXIT_WMA_INPUT,
    EXIT_WMA_DECODING,
    EXIT_WMA_EXIT,
    EXIT_WMA_TRAN_STANDBY,
    EXIT_WMA_WAIT,
    EXIT_WMA_WAIT_PLAY_PREV,

    EXIT_VDPLAYER_NULL,
    EXIT_VDPLAYER_PREDECODE_OK,
    EXIT_VDPLAYER_DECODING,
    EXIT_VDPLAYER_EXIT,
    EXIT_VDPLAYER_TRAN_STANDBY,
    EXIT_VDPLAYER_WAIT,
    EXIT_VDPLAYER_WAIT_PLAY_PREV,

    EXIT_MPEG2_NULL,
    EXIT_MPEG2_PREDECODE_OK,
    EXIT_MPEG2_EXIT,
    EXIT_MPEG2_WAIT,
    EXIT_MPEG2_INIT_DONE,
    EXIT_MPEG2_WAIT_PLAY_PREV,
    EXIT_MENU_EXIT_STORAGESELECT,

    EXIT_TS_NULL,
    EXIT_TS_PREDECODE_OK,
    EXIT_TS_EXIT,
    EXIT_TS_WAIT,
#endif
    EXIT_APENGINE_EXIT,

#ifdef ENABLE_BT
    EXIT_ANALOGINPUTS_TRAN_BT,
    EXIT_BT_NULL,
    EXIT_BT_EXIT,
    EXIT_BT_TRAN_STANDBY,
    EXIT_BT_TRAN_MENU,
#endif

    EXIT_GOTO_CLOSEDCAPTION,
    EXIT_CLOSEDCAPTION_NULL,
    EXIT_CLOSEDCAPTION_DONE,
    EXIT_TV_GOTO_CLOSEDCAPTION,

#ifdef ENABLE_KTV
    EXIT_KTV_TRAN_MENU,
#endif
#if(ENABLE_PVR ==1)
    EXIT_GOTO_PVR_CHECK_FS, //check File system menu page
#endif
#if ENABLE_DVBC
    EXIT_GOTO_CADTV_MANUALTUNING,
#endif
#if(ENABLE_S2)
    EXIT_GOTO_DISHSETUP,
#endif

#if (ENABLE_ATSC)
    EXIT_GOTO_ATSC_SCAN,
    EXIT_SCAN_NULL,
    EXIT_SCAN_DONE,
    EXIT_SCAN_TRAN_TV,
    EXIT_SCAN_TRAN_STANDBY,
#endif

#if ENABLE_FM_RADIO
    EXIT_GOTO_FMRADIO,
#endif

} EN_RET;

#endif // MAPP_EXIT_H

