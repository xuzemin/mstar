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
//////////////////////////////////////////////////////////////////////////////////

#include "Board.h"
#define MAPP_BLUE_SCREEN_C
/******************************************************************************/
/*                              Header Files                                  */
/******************************************************************************/
// C Library
#include <string.h>

// API Layer
#include "msAPI_Memory.h"
#include "msAPI_OSD.h"
#include "msAPI_OCP.h"
#include "apiGOP.h"
#include "MApp_Font.h"
/******************************************************************************/
/*                                 Macro                                      */
/******************************************************************************/

/******************************************************************************/
/*                                 Global Var                                 */
/******************************************************************************/
extern OSDClrBtn clrBtn1;

/******************************************************************************/
/*                                 Functions                                  */
/******************************************************************************/
extern void MApp_ZUI_ACTcoexist_Delete( void);
extern BOOLEAN MApp_ZUI_ACTcoexist_Create (U8 x,U16 win_x,U16 win_y,U16 win_w,U16 win_h);
extern void MApp_ZUI_ACTcoexist_Enable(BOOLEAN bEnable);
extern void MApp_ZUI_ACTcoexistWin_SwitchGwin(void);
extern void MApp_ZUI_ACTcoexistWin_RestoreGwin(void);

void MApp_BlueScreen_Init(void)
{
    OSDClrBtn *pclrBtn = &clrBtn1;
    U16 u16alignW = GE_ALIGNED_VALUE(UI_OSD_PANE_W, 8); //width need check if alignment

    if(u16alignW > UI_OSD_PANE_W)
       u16alignW = u16alignW - 8;

    MApp_ZUI_ACTcoexistWin_SwitchGwin();
    MApp_ZUI_ACTcoexist_Delete(); //delete MUTE gwin
    MApp_ZUI_ACTcoexist_Create(0,0, 0,  u16alignW, UI_OSD_PANE_H);
    MApi_GOP_GWIN_SetBlending(0, TRUE, (63*9/10));
    MApi_GFX_SetAlpha(FALSE, COEF_CONST, ABL_FROM_CONST, 0xFF);

    clrBtn1.x               = 0;
    clrBtn1.y               = 0;
    clrBtn1.width           = u16alignW; //UI_OSD_PANE_W;
    clrBtn1.height          = UI_OSD_PANE_H;
    clrBtn1.b_clr           = 0xFF;
    clrBtn1.f_clr           = 0xFF00;
    clrBtn1.u8Gradient      = CONSTANT_COLOR;
    clrBtn1.bFrameWidth     = 0;
    clrBtn1.fHighLight      = FALSE;

    msAPI_OSD_DrawBlock(pclrBtn);
    MApp_ZUI_ACTcoexist_Enable(TRUE);
    MApp_ZUI_ACTcoexistWin_RestoreGwin();
}


void MApp_BlueScreen_ShowString(U16 sX, U16 sY,U32 sColor, U8 * pString)
{
    U16 pStr[2048];

    memset(pStr, 0, 2048);

    MApi_GFX_SetAlpha(TRUE, COEF_CONST, ABL_FROM_ASRC, 1);

    clrBtn1.x               = sX;
    clrBtn1.y               = sY;
    clrBtn1.width           = UI_OSD_PANE_W;
    clrBtn1.height          = 28;
    clrBtn1.t_clr           = sColor;
    clrBtn1.enTextAlign         = EN_ALIGNMENT_LEFT;
    clrBtn1.bStringIndexWidth   = CHAR_IDX_2BYTE;
    clrBtn1.Fontfmt.flag        = GEFONT_FLAG_VARWIDTH|GEFONT_FLAG_GAP;
    clrBtn1.Fontfmt.ifont_gap   = 1;
    clrBtn1.bFrameWidth     = 0;
    clrBtn1.fHighLight      = FALSE;

    msAPI_OCP_MappinUTF8ToUCS2(pString,pStr,strlen((const char *)pString),2048);
    msAPI_OSD_DrawPunctuatedString(Font[FONT_2].fHandle, pStr, &clrBtn1, 10);
}


