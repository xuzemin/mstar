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

#define MAPP_ZUI_CTL_EFFECT_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "msAPI_Timer.h"
#include "MsTypes.h"
#include "apiGOP.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APItables.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_APIstyletables.h"
#include "MApp_ZUI_CTLeffect.h"
#include "MApp_ZUI_CTLeffectpopup.h"
#include "MApp_ZUI_CTLeffectslideitem.h"
#include "MApp_ZUI_CTLeffectzoom.h"
#include "MApp_ZUI_CTLeffectroll.h"
#include "MApp_ZUI_CTLmotiontrans.h"
#include "MApp_ZUI_CTLfake3d.h"

//EFF_3D_SETTING_CTL stEff3DSettingCTL ={EN_3D_MAIN_PAGE_Fake3D, EN_3D_MAIN_MENU_ITEM_ON, EN_3D_POPUP_DIALOG_ON};

extern BOOLEAN _MApp_ZUI_API_WindowProcOnIdle(void);

#if 0
void MApp_ZUI_CTL_Set3DEffectSettingPara(S8 s8Para, EN_3D_SETTING_CTL_PARA ePara)
{
    if(ePara >= EN_3D_CTL_INVALID_PARA)
    {
        printf("Error!! invalid input parameter to MApp_ZUI_CTL_Set3DEffectSettingPara()\n");
    }

    switch(ePara)
    {
        case EN_3D_MAIN_PAGE_PARA:
            stEff3DSettingCTL.eMainPageEff = (EN_3D_MAIN_PAGE) s8Para;
            break;
        case EN_3D_MAIN_MENU_ITEM_PARA:
            stEff3DSettingCTL.eMainMenuItemEff = (EN_3D_MAIN_MENU_ITEM) s8Para;
            break;
        case EN_3D_POPUP_DIALOG_PARA:
            stEff3DSettingCTL.ePopupDialogEff = (EN_3D_POPUP_DIALOG) s8Para;
            break;
        case EN_3D_CTL_INVALID_PARA:
            break;
    }
}

S8 MApp_ZUI_CTL_Get3DEffectSettingPara(EN_3D_SETTING_CTL_PARA ePara)
{
    S8 s8Para;
    if(ePara >= EN_3D_CTL_INVALID_PARA)
    {
        printf("Error!! invalid input parameter to MApp_ZUI_CTL_Get3DEffectSettingPara()\n");
    }

    switch(ePara)
    {
        case EN_3D_MAIN_PAGE_PARA:
            s8Para = (S8) stEff3DSettingCTL.eMainPageEff;
            break;
        case EN_3D_MAIN_MENU_ITEM_PARA:
            s8Para = (S8) stEff3DSettingCTL.eMainMenuItemEff;
            break;
        case EN_3D_POPUP_DIALOG_PARA:
            s8Para = (S8) stEff3DSettingCTL.ePopupDialogEff;
            break;
        default:
            s8Para = (S8) stEff3DSettingCTL.eMainPageEff;
            break;
    }
    return s8Para;
}
#endif

S32 MApp_ZUI_CTL_MainPageIconWinProc(HWND hWnd, PMSG pMsg)
{
#if 0
    switch(stEff3DSettingCTL.eMainPageEff)
    {
        case EN_3D_MAIN_PAGE_MotionTrans:
            MApp_ZUI_CTL_MotionTrans_Icon_WinProc(hWnd, pMsg);
            return 0;
        case EN_3D_MAIN_PAGE_Fake3D:
            MApp_ZUI_CTL_Fake3D_Icon_WinProc(hWnd, pMsg);
            return 0;
        default:
            break;
    }
#endif
    return DEFAULTWINPROC(hWnd, pMsg);
}

S32 MApp_ZUI_CTL_MainPageWinProc(HWND hWnd, PMSG pMsg)
{
#if 0
    switch(stEff3DSettingCTL.eMainPageEff)
    {
        case EN_3D_MAIN_PAGE_MotionTrans:
            MApp_ZUI_CTL_MotionTransWinProc(hWnd, pMsg);
            return 0;
        case EN_3D_MAIN_PAGE_Fake3D:
            MApp_ZUI_CTL_Fake3D_WinProc(hWnd, pMsg);
            return 0;
        default:
            break;
    }
#endif
    return DEFAULTWINPROC(hWnd, pMsg);
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_CTL_EffectWinProc
///  Window Proc for "effect popup" control
///
///
///  @param [in]       hWnd HWND     window handle
///  @param [in]       pMsg PMSG     message type
///
///  @return S32 message execute result
///
///  @author MStarSemi @date 2009/2/11
///////////////////////////////////////////////////////////////////////////////

S32 MApp_ZUI_CTL_EffectWinProc(HWND hWnd, PMSG pMsg)
{
#if 0
    switch(pMsg->message)
    {
        case MSG_EFFECT_POPUP:
            if(stEff3DSettingCTL.eMainMenuItemEff == EN_3D_MAIN_MENU_ITEM_ON)
            {
                EFFECTPOPUP_WINPROC(hWnd, pMsg);
                return 0;
            }
            break;

        case MSG_EFFECT_SLIDEITEM:
            return EFFECTSLIDEITEM_WINPROC(hWnd, pMsg);

        case MSG_EFFECT_ZOOMIN:
        case MSG_EFFECT_ZOOMOUT:
            if(stEff3DSettingCTL.ePopupDialogEff == EN_3D_POPUP_DIALOG_ON)
            {
                EFFECTZOOM_WINPROC(hWnd, pMsg);
                return 0;
            }
            break;  // Add it by coverity_0526

        case MSG_EFFECT_SPREADOUT:
        case MSG_EFFECT_ROLLUP:
            if(stEff3DSettingCTL.ePopupDialogEff == EN_3D_POPUP_DIALOG_ON)
            {
                EFFECTROLL_WINPROC(hWnd, pMsg);
                return 0;
            }

        default:
            break;
    }
#endif
    return DEFAULTWINPROC(hWnd, pMsg);
}


#undef MAPP_ZUI_CTL_EFFECT_C
