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

#ifndef _MApp_MHEG5_MAIN_H_
#define _MApp_MHEG5_MAIN_H_

#include "datatype.h"
#include "MApp_GlobalVar.h"
#include "MApp_IR.h"
#include "MApp_Key.h"
#include "MApp_MultiTasks.h"
#include "apiGOP.h"
//ZUI_TODO: #include "MApp_UiMenu.h"
#include "msAPI_IR.h"
#include "mapp_iframe.h"
#include "msAPI_MHEG5.h"
#include "apiGOP.h"
#include "MApp_Exit.h"
#include "mapp_si.h"

#undef INTERFACE
#ifdef _MAPP_MHEG5_MAIN_C_
#define INTERFACE
#else
#define INTERFACE extern
#endif

#if MHEG5_ENABLE
typedef enum
{
    STATE_MHEG5_INIT,
    STATE_MHEG5_WAIT,
    STATE_MHEG5_CHANNEL_CHANGE,
    STATE_MHEG5_TO_MENU,
    STATE_MHEG5_WITH_OSD,
    STATE_MHEG5_EXIT,
    STATE_MHEG5_MENU_EXIT,
    STATE_MHEG5_NONE,
} EN_MHEG5_STATE;

typedef enum
{
    GE_CONTROL_BY_MUTEX,
    GE_CONTROL_BY_SEMAPHORE,
    GE_CONTROL_BY_NONE,
} EN_MHEG5_GE_RESOURCE_CONTROL;



typedef enum
{
    EN_MHEG5_EM_BACKGROUND_LOADING,
    EN_MHEG5_EM_AUTOBOOT,

}EN_MHEG5_ENABLE_MODE;

typedef enum
{
    EN_MHEG5_DM_DISABLE_AND_STOPDSMCC,
    EN_MHEG5_DM_DISABLE_WITH_AUTOBOOT_LATER,
    EN_MHEG5_DM_DISABLE,
    EN_MHEG5_DM_DISABLE_AND_WAIT

}EN_MHEG5_DISABLE_MODE;

#if INTERACTION_CHANNEL
#define MHEG5IC_CHECKSERVER_STATUS    1
#define MHEG5IC_GETDATA_BY_GET           2
#define MHEG5IC_GETDATA_BY_POST           3
#define DIGEST_LENGTH 20
#endif

#define MHEG_WAIT_AEON_TIMEOUT  300

#if (MHEG5_X_STRETCH_WAY == MHEG5_USE_GOP_STRETCH)
 #if GOP_SCALERATIO_FIXED
  #define MHEG_OS_FB_WIDTH    ((g_IPanel.Width()+7)& ~7)/2
 #elif GOP_SCALERATIO_FIXED2
  #define MHEG_OS_FB_WIDTH MHEG_XRES_OS
 #else
  #define MHEG_OS_FB_WIDTH MHEG_XRES_OS
 #endif
#else
  #define MHEG_OS_FB_WIDTH    g_IPanel.Width()
 #endif

 #if (MHEG5_Y_STRETCH_WAY == MHEG5_USE_GOP_STRETCH)
  #if GOP_SCALERATIO_FIXED2
   #define MHEG_OS_FB_HEIGHT   MHEG_YRES
  #else
   #define MHEG_OS_FB_HEIGHT   ((g_IPanel.Height()+7)& ~7)/2//MHEG_YRES
  #endif
 #else
  #define MHEG_OS_FB_HEIGHT   g_IPanel.Height()
#endif

#if INTERACTION_CHANNEL
typedef struct Digest
{
    U8 digest_type;
    U8 name_count;
    U8 digest_byte[DIGEST_LENGTH];
} Digest;

typedef struct HashName
{
    U8 NameLength;
    char NameByte[500];
} HashName;
#endif

#if 1//ENABLE_PVR
INTERFACE BOOLEAN gbPVRSetModeWhenExitMheg5;
#endif

#if CIPLUS_MHEG_1_3
extern U8 u8InputMask[3];
#endif

//prototype
INTERFACE BOOLEAN MApp_MHEG5_Init(void);
INTERFACE void MApp_MHEG5_Force_Exit(void);
INTERFACE void MApp_MHEG5_Update_Program(U16 video, U16 audio, U16 audioType, VDEC_CodecType eVideoType  );
INTERFACE void MApp_MHEG5_SignalMonitor(void);
INTERFACE void MApp_MHEG5_RestoreWindow(U8 u8DoScreenMute);
// do processing MHEG in multitask
INTERFACE void _MApp_MHEG5_Process(void);
INTERFACE void MApp_MHEG5_RestoreOriginalAV(void);
INTERFACE void MApp_MHEG5_SetGoMHEG5Process(BOOLEAN bEnable);
INTERFACE BOOLEAN MApp_MHEG5_CheckGoMHEG5Process(void);

INTERFACE void MApp_MHEG5_Set_Display(bool bEnable, bool bRestoreVideoWindowSize);
INTERFACE void MApp_MHEG5_SetGraphARCInfo(U8 u8Flag ,EN_ASPECT_RATIO_TYPE enVideoScreen);

//========================================
//MHEG5 API for other APP.
//========================================
INTERFACE BOOLEAN MApi_MHEG5_Enable(EN_MHEG5_ENABLE_MODE EnableMode);
INTERFACE BOOLEAN MApi_MHEG5_Disable(EN_MHEG5_DISABLE_MODE DisableMode);
//========================================
//MHEG5 CallBack function for other GOP re-arrange.
//========================================
INTERFACE void MApp_MHEG5_fpGOP_CB(MS_U32 u32EventID, void* reserved0);
INTERFACE void MApp_MHEG5_Enable_LiveMHEG5(BOOL bEnable);
INTERFACE SI_MHEG5_STATUS MApp_MHEG5_CheckMHEG5Status( void );

#if INTERACTION_CHANNEL
INTERFACE U16 MApp_MHEG5_Init_Net(unsigned char *ICStrAddr, unsigned char *FullICStrAddr, U8 item);
U16 MApp_MHEG5_CheckServer_Status(char *ICStraddr);
U16 MApp_MHEG5_Connect_Server(char *ICStraddr, int *st);
U16 MApp_MHEG5_Send_And_Recv(char *dest, char *ReqStr, int *nRet, int *st, int RecvSize);
bool MApp_MHEG5_Get_ReturnStatus(unsigned char *tempstr, U16 *ReturnStatus);
#endif
INTERFACE void MApp_MHEG5_ExitMheg5(void);
#endif
#undef INTERFACE
#endif  // _MApp_MHEG5_MAIN_H_
