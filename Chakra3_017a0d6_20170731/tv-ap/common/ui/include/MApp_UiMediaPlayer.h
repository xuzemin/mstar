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

#ifndef MAPP_UIMEDIAPLAYER_H
#define MAPP_UIMEDIAPLAYER_H

#include "mapp_mplayer.h"
#include "MApp_UiMenuDef.h"


#define THUMB_MAX_CLUMN_NUM       6
#define TOTAL_DRIVE_PAGE_NUM      ((MApp_MPlayer_QueryTotalDriveNum()/NUM_OF_PHOTO_FILES_PER_PAGE) + 1)
#define REPEAT_COMPONENT_TIMEOUT  5000 //ms

typedef enum
{
    E_MEDIAPLAYER_DRAW_TYPE_MAIN_PAGE,
    E_MEDIAPLAYER_DRAW_TYPE_COMPONENT,
    E_MEDIAPLAYER_DRAW_TYPE_EXECUTEMENUEVENT,
    E_MEDIAPLAYER_DRAW_TYPE_MUSIC_EQ,
    E_MEDIAPLAYER_DRAW_TYPE_DRIVE_LIST_SCROLLBAR,
    E_MEDIAPLAYER_DRAW_TYPE_MSG_DIALOG,
    //invalid type
    E_MEDIAPLAYER_DRAW_TYPE_INVALID,
}enumDrawType;

typedef struct
{
    enumDrawType            eDrawType;
    U16                     u16GroupX;
    U16                     u16GroupY;
    //DrawComponentTypePtr    pComponent;
    //DrawComponentType       *pComponent;
    U8                      u8MenuIdx;
    U8                      u8MenuItemIdx;
    BOOLEAN                 bRestore;
    U8                      u8MenuRestoredIdx;
    U8                      u8MenuItemRestoredIdx;
    MenuItemActionType      eActionType;
} stComponentList, *pstComponentList;

#ifdef MAPP_UIMEDIAPLAYER_C
#define INTERFACE
#else
#define INTERFACE extern
#endif
#if 1
//////////////////////////////////////////////////
//
//          Global Variable
//
//////////////////////////////////////////////////
//INTERFACE enumMPlayerInternalState  g_eMPlayerInternalState;
INTERFACE U8                        g_u8ThumbIdx;
INTERFACE U8                        g_u8ThumbEndIdx;
INTERFACE BOOLEAN                   g_bSubtitleShown;
INTERFACE U8                        g_u8PrevFileItemIdx;    //used to distinguish page changing in file list
INTERFACE U8                        g_u8PrevDriveItemIdx;   //used to distinguish page changing in drive list
INTERFACE U8                        g_u8CurrentDriveIdx;    //used to redraw MENU_MEDIA_PLAYER_DRIVE_LIST
INTERFACE U8                        g_u8CurrentDrivePage;
INTERFACE U16                       g_u16MusicCurrentTime;
INTERFACE U16                       *g_pLyricString;
INTERFACE U16                       *g_pSubtitleString;
INTERFACE MenuItemActionType        g_eMenuItemActionType;  //used in MApp_MultiTasks.c for execute menu key event - parameter
INTERFACE BOOLEAN                   g_bUpdateFileListIcons; //flag TRUE to draw file list icons
INTERFACE U8                        g_u8MediaPlayerFocusedMenuIdx;
INTERFACE BOOLEAN                   g_bGotoMainMenu;
INTERFACE BOOLEAN                   g_bDriveConnectOk;
INTERFACE U8                        g_u8PrevKeyCode;
#if (ENABLE_POWERON_MUSIC)
INTERFACE BOOLEAN                   g_bCapturingMp3;
#endif
INTERFACE BOOLEAN                   g_bPlayError;
INTERFACE U8                        g_u8PrevNotify;
INTERFACE BOOLEAN                   g_bMusicPreview;
INTERFACE U8                        g_u8DriveTbl[NUM_OF_MAX_DRIVE];
#endif
//////////////////////////////////////////////////
//
//          Function Prototype
//
//////////////////////////////////////////////////
INTERFACE BOOLEAN MApp_UiMediaPlayer_IsMediaPlayerMenuPage(U8 u8MenuPageIndex);
INTERFACE void MApp_UiMediaPlayer_Switch2MediaPlayer(void);
//INTERFACE void MApp_UiMediaPlayer_CreateAndRedrawMenu(void);
INTERFACE BOOLEAN MApp_UiMediaPlayer_IsMediaPlayerInit(void);
INTERFACE void MApp_UiMediaPlayer_Reset(void);
INTERFACE void MApp_UiMediaPlayer_Init(void);
INTERFACE void MApp_UiMediaPlayer_ProcessKey(U8 u8KeyCode_);
INTERFACE BOOLEAN MApp_UiMediaPlayer_Notify(enumMPlayerNotifyType eNotify, void *pInfo);
INTERFACE BOOLEAN MApp_UiMediaPlayer_IsSubtitleEnabled(void);
INTERFACE void MApp_UiMediaPlayer_InsertComponent(pstComponentList pComponent);
INTERFACE void MApp_UiMediaPlayer_UpdateMainPage_Task(void);
INTERFACE void MApp_UiMediaPlayer_UpdateFileListIcons_Task(void);
INTERFACE void MApp_UiMediaPlayer_DrawComponent_Task(void);

//MISC functions
INTERFACE void MApp_UiMediaPlayer_ClearSavedMenuIdx(void);
INTERFACE void MApp_UiMediaPlayer_SaveMenuIdx(void);
INTERFACE void MApp_UiMediaPlayer_RedrawMusicInfo(void);
INTERFACE void MApp_UiMediaPlayer_LoadMenuIdxAndRedraw(void);
INTERFACE void MApp_UiMediaPlayer_GotoMainMenuFromThumbnailMode(void);
INTERFACE void MApp_UiMediaPlayer_RedrawMenuPageById(U8 u8MenuPageId, U16 u8MenuItemId);
INTERFACE void DrawUSBComponent(void);
INTERFACE void MApp_UiMediaPlayer_IsDisplayingTimeOut(void);
INTERFACE BOOLEAN MApp_UiMediaPlayer_IsRepeatComponentShowed(void);
INTERFACE void MApp_UiMediaPlayer_ClearRepeatComponent(void);
INTERFACE void DrawRepeatComponent(void);
INTERFACE void DrawFileListIcons(void);
INTERFACE BOOLEAN MApp_UiMediaPlayer_IsMediaFileExist(U8 u8FileIdx);
INTERFACE BOOLEAN MApp_MPlayer_IsMediaDriveExist(U8 u8DriveIdx);
INTERFACE BOOLEAN MApp_UiMediaPlayer_IsThumbnailItemExist(U8 u8ThumbnailIdx);
INTERFACE void MApp_UiMediaPlayer_FileOperationMode(BOOLEAN bYes);
INTERFACE void MApp_UiMediaPlayer_UpdateMainPage(void);
INTERFACE void MApp_UiMediaPlayer_UpdateFileListIcon(void);
INTERFACE void MApp_UiMediaPlayer_TurnOnMusicRelativeInfo(void);
INTERFACE void MApp_UiMediaPlayer_TurnOffMusicRelativeInfo(void);
#if 0
INTERFACE U8* MediaPlayerDummyFunc_CheckDriveListNextPage(void);
INTERFACE U8* MediaPlayerDummyFunc_CheckDriveListPrevPage(void);
INTERFACE U8* MediaPlayerDummyFunc_ConnectDriveAndUpdateFileList(void);
INTERFACE U8* MediaPlayerDummyFunc_UpdateMainPage(void);
INTERFACE U8* MediaPlayerDummyFunc_UpdateFileListIcon(void);
#endif
INTERFACE U8* MApp_UiMenu_MediaPlayerPhotoListItemSelString(void);
INTERFACE U8* MApp_UiMenu_MediaPlayerPhotoListItemUnselString(void);
#if 0
INTERFACE U8* MediaPlayerDummyFunc_CheckFileListNextPage(void);
INTERFACE U8* MediaPlayerDummyFunc_CheckFileListPrevPage(void);
INTERFACE U8* MediaPlayerDummyFunc_MediaPlayerStopPreview(void);
INTERFACE U8* MediaPlayerDummyFunc_MediaPlayerBeginPreviewAndUpdateInfo(void);
INTERFACE U8* MApp_UiMenu_MediaPlayerPhotoListItem0SelString(void);
INTERFACE U8* MApp_UiMenu_MediaPlayerPhotoListItem0UnselString(void);
INTERFACE U8* MApp_UiMenu_MediaPlayerPhotoListItem1SelString(void);
INTERFACE U8* MApp_UiMenu_MediaPlayerPhotoListItem1UnselString(void);
INTERFACE U8* MApp_UiMenu_MediaPlayerPhotoListItem2SelString(void);
INTERFACE U8* MApp_UiMenu_MediaPlayerPhotoListItem2UnselString(void);
INTERFACE U8* MApp_UiMenu_MediaPlayerPhotoListItem3SelString(void);
INTERFACE U8* MApp_UiMenu_MediaPlayerPhotoListItem3UnselString(void);
INTERFACE U8* MApp_UiMenu_MediaPlayerPhotoListItem4SelString(void);
INTERFACE U8* MApp_UiMenu_MediaPlayerPhotoListItem4UnselString(void);
INTERFACE U8* MApp_UiMenu_MediaPlayerPhotoListItem5SelString(void);
INTERFACE U8* MApp_UiMenu_MediaPlayerPhotoListItem5UnselString(void);
#if (6 < NUM_OF_PHOTO_FILES_PER_PAGE)
INTERFACE U8* MApp_UiMenu_MediaPlayerPhotoListItem6SelString(void);
INTERFACE U8* MApp_UiMenu_MediaPlayerPhotoListItem6UnselString(void);
#endif
#endif
INTERFACE U8* MApp_UiMenu_MediaPlayerDriveListItem0SelString(void);
INTERFACE U8* MApp_UiMenu_MediaPlayerDriveListItem0UnselString(void);
INTERFACE U8* MApp_UiMenu_MediaPlayerDriveListItem1SelString(void);
INTERFACE U8* MApp_UiMenu_MediaPlayerDriveListItem1UnselString(void);
INTERFACE U8* MApp_UiMenu_MediaPlayerDriveListItem2SelString(void);
INTERFACE U8* MApp_UiMenu_MediaPlayerDriveListItem2UnselString(void);
INTERFACE U8* MApp_UiMenu_MediaPlayerDriveListItem3SelString(void);
INTERFACE U8* MApp_UiMenu_MediaPlayerDriveListItem3UnselString(void);
INTERFACE U8* MApp_UiMenu_MediaPlayerDriveListItem4SelString(void);
INTERFACE U8* MApp_UiMenu_MediaPlayerDriveListItem4UnselString(void);
INTERFACE U8* MApp_UiMenu_MediaPlayerDriveListItem5SelString(void);
INTERFACE U8* MApp_UiMenu_MediaPlayerDriveListItem5UnselString(void);
#if (6 < NUM_OF_PHOTO_FILES_PER_PAGE)
INTERFACE U8* MApp_UiMenu_MediaPlayerDriveListItem6SelString(void);
INTERFACE U8* MApp_UiMenu_MediaPlayerDriveListItem6UnselString(void);
#endif
INTERFACE BOOLEAN MApp_UiMediaPlayer_MediaDriveList(void);
#ifdef MEDIA_PLAYER_HIGHLIGHT_CHANGE
INTERFACE void MApp_UiMediaPlayer_ScrollDownPage(BOOLEAN bDraw);
INTERFACE void MApp_UiMediaPlayer_ScrollUpPage(BOOLEAN bDraw);
#endif  // MEDIA_PLAYER_HIGHLIGHT_CHANGE

#if ENABLE_DMP
INTERFACE U8* MApp_UiMenu_MediaPlayerClickString(void);
INTERFACE U8* MApp_UiMenu_MediaPlayerPrgmNameString(void);
INTERFACE U8* MApp_UiMenu_MPlayerPageIndicator(void);
INTERFACE U8* MApp_UiMenu_MPlayerMUSICCurrentTime(void);
INTERFACE U8* MApp_UiMenu_MPlayerMUSICTotalTime(void);
INTERFACE U8* MApp_UiMenu_MPlayerGetLyric(void);
INTERFACE U8* MApp_UiMenu_MPlayerGetSubtitle(void);
INTERFACE U8* MApp_UiMenu_MPlayerGetMP3InfoAlbum(void);
INTERFACE U8* MApp_UiMenu_MPlayerGetMP3InfoTitle(void);
INTERFACE U8* MApp_UiMenu_MPlayerGetMP3InfoBitRate(void);
INTERFACE U8* MApp_UiMenu_MPlayerGetMP3InfoSamplingRate(void);
INTERFACE U8* MApp_UiMenu_MPlayerGetMP3InfoArtist(void);
INTERFACE U8* MApp_UiMenu_MPlayerGetMP3InfoYear(void);
INTERFACE U8* MApp_UiMenu_MPlayerGetPhotoInfoWxH(void);
INTERFACE U8* MApp_UiMenu_MPlayerGetPhotoInfoSize(void);
INTERFACE U8* MApp_UiMenu_MPlayerGetInfoFileSize(void);
INTERFACE U8* MApp_UiMenu_MPlayerPhotoInfoWxH(void);
INTERFACE U8* MApp_UiMenu_MPlayerPhotoInfoSize(void);
INTERFACE U8* MediaPlayerPhotoInfoWxHText(void);
INTERFACE U8* MediaPlayerInfoFileSizeText(void);
INTERFACE U8* MediaPlayerMp3InfoBitRateText(void) ;
INTERFACE U8* MediaPlayerMp3InfoSamplingRateText(void) ;
INTERFACE U8* MediaPlayerMp3InfoAlbumText(void) ;
INTERFACE U8* MediaPlayerMp3InfoTitleText(void);
INTERFACE U8* MediaPlayerMp3InfoArtistText(void);
INTERFACE U8* MediaPlayerMp3InfoYearText(void) ;
#if (DISPLAY_LOGO)
INTERFACE U8* MediaPlayerSaveLogoConfirmText(void);
#endif
INTERFACE U8* FileDelete_Dialog_ConfirmText(void);
INTERFACE U8* MediaPlayerSaveMp3ConfirmText(void);
INTERFACE U8* FileCopyPaste_Dialog_ConfirmText(void);
INTERFACE void MApp_UiMediaPlayer_ClearComponentList(void);
#endif

INTERFACE void MApp_UiMediaPlayer_TurnOnMusicRelativeInfo(void);
INTERFACE void MApp_UiMediaPlayer_TurnOffMusicRelativeInfo(void);

#undef INTERFACE

#endif //MAPP_UIMEDIAPLAYER_H

