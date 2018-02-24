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

#ifndef MAPP_WMA_H
#define MAPP_WMA_H

//-------------------------------------------------------------------------------------------------
// Standard include files:
//-------------------------------------------------------------------------------------------------
#include "datatype.h"
#include "msAPI_WMA.h"
#include "MApp_Exit.h"
#include "MApp_Key.h"

#ifdef MAPP_WMA_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

//-------------------------------------------------------------------------------------------------
// Project include files:
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------
typedef enum
{
    WMA_STATUS_STOP,
    WMA_STATUS_PLAYING,
    WMA_STATUS_PAUSE,
    WMA_STATUS_SCAN,
} WMA_PLAY_STATUS;

typedef enum
{
    STATE_WMA_INIT =0,
    STATE_WMA_OPEN_FILE,
    STATE_WMA_INPUT,
    STATE_WMA_WAIT_DECODE_DONE,
    STATE_WMA_WAIT,
    STATE_WMA_STANDBY,
    STATE_WMA_EXIT,
    STATE_WMA_SKIP_PLAY_NEXT,
    STATE_WMA_SKIP_PLAY_PREV,
    STATE_WMA_NONE,
} EN_WMA_STATE;

typedef enum
{
    WMA_RETURN_SUCCESS,
    WMA_RETURN_ERR_FILE,
} EN_WMA_RETURN;

typedef enum
{
    WMA_INFO_BITRATE,
    WMA_INFO_SAMPLINGRATE,
    WMA_INFO_ALBUM,
    WMA_INFO_TITLE,
    WMA_INFO_ARTIST,
    WMA_INFO_YEAR,
    WMA_INFO_CHECK_FF_FB,
} EN_WMA_INFO;

typedef enum
{
    EN_WMA_SPEED_X1 = 0,
    EN_WMA_SPEED_X2,
    EN_WMA_SPEED_X4,
    EN_WMA_SPEED_X8,
    EN_WMA_SPEED_X16,
    EN_WMA_SPEED_X32,
    EN_WMA_SPEED_MAX = EN_WMA_SPEED_X32,
} EN_WMA_SPEED;

typedef enum
{
    EN_ASF_FILE_PROPERTIES = 0,
    EN_ASF_STREAM_PROPERTIES,
    EN_ASF_CONTENT_DESCRIPTION,
} EN_WMA_HEADERID;

typedef enum
{
    E_WMA_ERR_NONE = 0,
    E_WMA_ERR_NOT_SUPPORT_DRM,
    E_WMA_ERR_NOT_SUPPORT_CHANNEL_NUM,
    E_WMA_ERR_NOT_SUPPORT_SAMPLE_RATE,
    E_WMA_ERR_DECODE_HEADER_FAILURE,
    E_WMA_ERR_DECODE_FAILURE,
    E_WMA_ERR_DATA_OPERATION_FAILURE,
    E_WMA_ERR_GET_LICENSE_FAILURE,
    E_WMA_ERR_NOT_SUPPORT_CODECID,
} EN_WMA_ERRCODE;

//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Type and Structure Declaration
//-------------------------------------------------------------------------------------------------




#define PROBE_WMA_INFO_LENGTH 128
#define PROBE_WMA_INFO_YEAR_LENGTH 32

typedef struct
{
    U8 u8Title[PROBE_WMA_INFO_LENGTH];
    U8 u8Artist[PROBE_WMA_INFO_LENGTH];
    U8 u8Album[PROBE_WMA_INFO_LENGTH];
    U8 u8Year[PROBE_WMA_INFO_YEAR_LENGTH];
    U16 u16BitRate;
    U32 u32SampleRate;
    U32 u32Duration;
    U32 u32PicOffset;
    U32 u32PicSize;
} ST_WMA_PROBE_INFO;




//-------------------------------------------------------------------------------------------------
// Extern Global Variabls
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Extern Functions
///-------------------------------------------------------------------------------------------------
INTERFACE void MApp_WMA_SetFileEntry(FileEntry *pEntry);
INTERFACE EN_RET MApp_WMA_Main(void);
INTERFACE void MApp_WMA_Stop(void);
INTERFACE BOOLEAN MApp_WMA_ProcessKey (void);
INTERFACE BOOLEAN MApp_WMA_Pause(void);
INTERFACE void MApp_WMA_Resume(void);
INTERFACE void MApp_WMA_DrawEQ(void);
INTERFACE U8* MApp_WMA_GetInfoString(EN_WMA_INFO enInfo, U8* pu8Length);
INTERFACE U32 MApp_WMA_GetTotalTime(void);
INTERFACE U16 MApp_WMA_GetCurrentTime(void);
INTERFACE U32 MApp_WMA_GetCurrentTimeMs(void);
INTERFACE EN_WMA_SPEED MApp_WMA_GetFfRewSpeed(void);
INTERFACE BOOLEAN MApp_WMA_ProcessTimeOffset(U32 u32GotoTimeMs);
INTERFACE BOOLEAN MApp_WMA_FastForwardBackward(BOOLEAN bForward, EN_WMA_SPEED eSpeed);
INTERFACE EN_WMA_ERRCODE MApp_Wma_GetErrCode(void);
INTERFACE void MApp_Wma_StopAfterFBBegin(BOOLEAN bEnabled);
INTERFACE void MApp_Wma_Init(void);
INTERFACE BOOLEAN MApp_WMA_Probe(U32 u32Hdl, ST_WMA_PROBE_INFO *pstWmaProbeInfo, U32 u32InfoAttr);
#undef INTERFACE

#endif // _MAPP_WMA_H

