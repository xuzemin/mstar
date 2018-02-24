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

#ifndef _DRV_MWE_H_
#define _DRV_MWE_H_

#include "datatype.h"
#include "Analog_Reg.h"
#include "drvGlobal.h"

#ifdef _DRV_MWE_C_
  #define INTERFACE
#else
  #define INTERFACE extern
#endif

#define MWE_AT_LEFT         0
#define MWE_AT_RIGHT        1
#define MWE_POSITION        MWE_AT_LEFT

typedef enum MWEType
{
	MWE_OFF,
	MWE_H_SPLIT,
	MWE_MOVE,
	MWE_ZOOM,
	MWE_NUMS,
}MWEType;

typedef struct _PanelSizeType
{
	U32 wPANEL_HSTART;
	U32 wPANEL_VSTART;
	U32 wPANEL_WIDTH;
	U32 wPANEL_HEIGHT;
}PanelSizeType;

typedef struct {
    U32 Xpos;
    U32 Ypos;
    U32 Xsize;
    U32 Ysize;
}MWE_RECT;

typedef enum
{
	MWE_MODE_OFF,
	MWE_MODE_H_SPLIT,
	MWE_MODE_MOVE,
	MWE_MODE_ZOOM,
	MWE_MODE_H_SCAN,
	MWE_MODE_NUMS=MWE_MODE_H_SCAN,
} MWE_FUNC;
INTERFACE U8 g_ucDemoTimeCounter;
INTERFACE PanelSizeType MWEPanel;
INTERFACE U8 g_bMWEInit; // to do
INTERFACE U8 g_u8MWE_Status;
//Color Demo Define below -------------------------------------------------
typedef enum _msMWEStepType
{
    MWE_ANALIZE_NONE,
    MWE_ANALIZE_BEGIN,
    MWE_ANALIZE_COLOR= MWE_ANALIZE_BEGIN,
    MWE_ANALIZE_BORDER,
    MWE_ANALIZE_BRIGHT,
    MWE_ANALIZE_COLORFIELD,
    MWE_ANALIZE_FINISH,
    MWE_ANALIZE_NUMS,
}msMWEStepType;
typedef enum _msMWEColorFieldType
{
	MWE_FIELD_RED,
	MWE_FIELD_GREEN,
	MWE_FIELD_BLUE,
	MWE_FIELD_CYAN,
	MWE_FIELD_PURPLE,
	MWE_FIELD_YELLOW,
	MWE_FIELD_SKIN,
	MWE_FIELD_NUMS,
}msMWEColorFieldType;

enum	EN_MWE_AN_TYPE
{
	TYPE_MWE_AN_OFF=0,
	TYPE_MWE_AN_ING,
	TYPE_MWE_AN_OK,
	TYPE_MWE_AN_END,		
};

typedef struct _st_MWE_Analize
{
	U8 bColorAn:2;
	U8 bBorderAn:2;
	U8 bSceneAn:2;
	U8 bFeildAn:2;
	U8 bAnalizeSts;
	U16 bStepCnt:4;
	U16 bCnt:12;
}st_MWE_Analize;
INTERFACE st_MWE_Analize g_stMWEAnSts;
//-----------------------------------------------------------
INTERFACE void MDrv_MWE_Init(void);
INTERFACE void MDrv_MWE_WinOnOff(BOOLEAN bEnable);
INTERFACE MWE_RECT* MDrv_MWE_GetRect(void);
INTERFACE void MDrv_MWE_Refresh(void);
INTERFACE void MDrv_MWE_FuncSel(U8 ucMWE_Type,PanelSizeType* pMWEPanel);
INTERFACE void MDrv_MWE_SetQuality(void);
INTERFACE void MDrv_MWE_SetMainQuality(void);
INTERFACE void MDrv_MWE_SetEnhanceQuality(void);
INTERFACE void msAPI_ACE_MWEHandle( void );
INTERFACE void msAPI_ACE_MWEFuncSel(MWE_FUNC  mwe_func);
INTERFACE BOOLEAN msAPI_ACE_MWEStatus(void);

#undef INTERFACE
#endif //_DRV_MWE_H_

