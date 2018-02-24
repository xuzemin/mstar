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

#define MAPP_ZUI_CTL_KEYBOARD_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "datatype.h"
#include "msAPI_OSD.h"
#include "msAPI_Memory.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "MApp_ZUI_APItables.h"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIdraw.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_APIcomponent.h"
#include "MApp_ZUI_APIalphatables.h"
#include "MApp_ZUI_ACTglobal.h"
#include "OSDcp_Bitmap_EnumIndex.h"

////////////////////////////////////////////////////
// Key Board Grid



//*************************************************************************
//              Defines
//*************************************************************************

/********************************************************************************/
/*                    Macro                                                     */
/********************************************************************************/
#define CHARTYPE 3
#define BUTTONCLICK_TIMER 200


/********************************************************************************/
/*                      Local                                                   */
/********************************************************************************/
static U16 _ZUI_TBLSEG idx2key[][CHARTYPE] =
{
{'Q','q','0'},
{'A','a','#'},
{'Z','z','^'},
{'W','w','1'},
{'S','s','_'},
{'X','x','*'},
{'E','e','2'},
{'D','d','-'},
{'C','c','='},
{'R','r','3'},
{'F','f','['},
{'V','v',']'},
{'T','t','4'},
{'G','g',':'},
{'B','b','?'},
{'Y','y','5'},
{'H','h',';'},
{'N','n',','},
{'U','u','6'},
{'J','j','!'},
{'M','m','%'},
{'I','i','7'},
{'K','k','@'},
{'O','o','8'},
{'L','l','"'},
{'P','p','9'},
};


static U8 _MApp_ZUI_CTL_Keyboard_MapHwnd2Index(HWND hwndGrid,HWND hwnd)
{
    if(!MApp_ZUI_API_IsSuccessor(hwndGrid,hwnd))
        return 0;

    GUI_DATA_KEYBOARD * windata = (GUI_DATA_KEYBOARD*) GETWNDDATA(hwndGrid);
    U8 u8idx = hwnd - windata->pVarData->hwndFirstShown;

    return u8idx;
}

static HWND _MApp_ZUI_CTL_Keyboard_MapIndex2Hwnd(HWND hwndGrid,U8 u8idx)
{
    GUI_DATA_KEYBOARD * windata = (GUI_DATA_KEYBOARD*) GETWNDDATA(hwndGrid);

    if(u8idx >= COUNTOF(idx2key))
        return HWND_INVALID;

    HWND hwnd;
    hwnd = windata->pVarData->hwndFirstShown + (U16)u8idx;
    return hwnd;
}

static LPTSTR _MApp_ZUI_CTL_KeyboardStringByIndex(U8 u8Index,U8 u8TypeIdx)
{
    LPTSTR str = CHAR_BUFFER;
    str[0] = idx2key[u8Index][u8TypeIdx];
    str[1] = 0;

    return str;
}


///////////////////////////////////////////////////////////////////////////////
///  public  MApp_ZUI_CTL_Keyboard_SetFnEditText
///  Set keyboard edit char infomation ,Setting char by CB function.
///     
///
///  @param [in]       HWND hwndGrid     keyboard handle
///  @param [in]       HWND hlist        char list
///  @param [in]       U8   u8charmax    how many char can edit
///  @param [in]       fnGetEditText     Call back function that can "Get" edit text
///  @param [in]       fnSetEditText     Call back function that can "Set" edit text
///
///  @return
///
///  @author MStarSemi @date 2009/8/21
///////////////////////////////////////////////////////////////////////////////

void MApp_ZUI_CTL_Keyboard_SetFnEditText(HWND hwndGrid,HWND hbar, HWND hlist,FN_ZUI_CTL_Keyboard_GetEditText fnGetEditText, FN_ZUI_CTL_Keyboard_SetEditText fnSetEditText)
{
    GUI_DATA_KEYBOARD * windata = (GUI_DATA_KEYBOARD*) GETWNDDATA(hwndGrid);


    //no dynamic list setting data...
    if (windata == 0)
        return;

    windata->hwndcharlist = hlist;
    windata->hwndbar = hbar;
    windata->u8CharMax = MApp_ZUI_API_CountChildren(hlist);
    windata->fnGetEditText = fnGetEditText;
    windata->fnSetEditText = fnSetEditText;
}


///////////////////////////////////////////////////////////////////////////////
///  public  MApp_ZUI_CTL_KeyboardGetDynamicText
///  return dynamic text that char on keyboard char on char list that want to edit
///     
///
///  @param [in]       HWND hwndGrid     keyboard handle
///  @param [in]       HWND hwndText     target handle 
///
///  @return string content
///
///  @author MStarSemi @date 2009/8/21
///////////////////////////////////////////////////////////////////////////////

LPTSTR MApp_ZUI_CTL_KeyboardGetDynamicText(HWND hwndGrid, HWND hwndText)
{
    GUI_DATA_KEYBOARD * windata = (GUI_DATA_KEYBOARD*) GETWNDDATA(hwndGrid);
    U8 u8Index;

    //no dynamic list setting data...
    if (windata == 0)
        return 0;

    //show keyboard grid key
    if(MApp_ZUI_API_IsSuccessor(hwndGrid,hwndText))
    {
        u8Index = _MApp_ZUI_CTL_Keyboard_MapHwnd2Index(hwndGrid,hwndText);
        return _MApp_ZUI_CTL_KeyboardStringByIndex(u8Index,windata->u8CharType);
    }
    else//get show edit text content
    {
        U8 u8Temp[windata->u8CharMax];
        U8 str[2];
        windata->fnGetEditText(u8Temp);
        str[0] = u8Temp[(U8)(hwndText-(windata->hwndcharlist+1))];
        str[1] = 0;
        MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,str,2);
        return CHAR_BUFFER;
    }
}


///////////////////////////////////////////////////////////////////////////////
///  public  MApp_ZUI_CTL_KeyBoardInputWinProc
///  Window Proc for "keyboard" control,
///     which can show edit content and change keyboard content 
///      Press[select] u16CapIndex : change keyboard content to uppercase or lowercase
///      Press[select] u16BackspaceIndex : erase pre-char and decrease edit index
///      Press[select] u16SymbolIndex : change keyboard content to symbol
///
///  @param [in]       hWnd HWND     window handle
///  @param [in]       pMsg PMSG     message
///
///  @return S32 event handler result
///
///  @author MStarSemi @date 2008/5/26
///////////////////////////////////////////////////////////////////////////////


S32 MApp_ZUI_CTL_KeyBoardInputWinProc(HWND hwnd, PMSG msg)
{
    GUI_DATA_KEYBOARD * windata = (GUI_DATA_KEYBOARD*) GETWNDDATA(hwnd);


    //no dynamic list setting data...
    if (windata == 0 || windata->pVarData == 0)
    {
        return DEFAULTWINPROC(hwnd, msg);
    }

    switch (msg->message)
    {
        case MSG_NOTIFY_SHOW:
            {
                windata->u8CurIndex = 0;
                windata->pVarData->hwndFirstShown = hwnd+1;
                windata->pVarData->hwndLastShown = MApp_ZUI_API_GetLastSuccessor(hwnd);
                windata->u8CharIndex = 0 ;
                windata->u8CharType = 0;
            }
            break;


        case MSG_NOTIFY_KEYDOWN:
            {
                HWND hwndFocus = MApp_ZUI_API_GetFocus();
                if (hwndFocus == HWND_INVALID)
                    return 0;

                U8 u8Index = windata->u8CurIndex;
                U8 s8NextIndex = 0;
                switch (msg->wParam)
                {
                    case VK_SELECT:
                    {

                        //change char box content
                        U8 u8Temp[windata->u8CharMax];

                        windata->fnGetEditText(u8Temp);
                        if(windata->u8CharIndex >= windata->u8CharMax -1)
                            return 0;

                        u8Temp[windata->u8CharIndex] = idx2key[windata->u8CurIndex][windata->u8CharType];

                        if(windata->u8CharIndex < windata->u8CharMax -1)
                        {
                            windata->u8CharIndex++;
                        }

                        windata->fnSetEditText(u8Temp);
                        
                        MApp_ZUI_API_SetTimer(windata->hwndbar+5, 0, BUTTONCLICK_TIMER);
                        MApp_ZUI_API_InvalidateWindow(windata->hwndbar+5);

                        MApp_ZUI_API_InvalidateAllSuccessors(windata->hwndcharlist);
                        return 0;
                    }
                    break;
                    case VK_YELLOW: //space
                    {
                        //change char box content
                        U8 u8Temp[windata->u8CharMax];


                        if(windata->u8CharIndex >= windata->u8CharMax)
                            return 0;
                            
                        windata->fnGetEditText(u8Temp);
                        
                        u8Temp[windata->u8CharIndex] = 0;
                        
                        if(windata->u8CharIndex < (windata->u8CharMax-2))
                            windata->u8CharIndex++;

                        windata->fnSetEditText(u8Temp);
                        MApp_ZUI_API_SetTimer(windata->hwndbar+2, 0, BUTTONCLICK_TIMER);
                        MApp_ZUI_API_InvalidateWindow(windata->hwndbar+2);

                        MApp_ZUI_API_InvalidateAllSuccessors(windata->hwndcharlist);
                        return 0;
                    }

                    case VK_BLUE: //delete
                    {
                        //change char box content
                        U8 u8Temp[windata->u8CharMax];


                        if(windata->u8CharIndex >= windata->u8CharMax)
                            return 0;
                            
                        windata->fnGetEditText(u8Temp);

                        if(windata->u8CharIndex != 0)
                            windata->u8CharIndex--;

                        u8Temp[windata->u8CharIndex] = 0;

                        windata->fnSetEditText(u8Temp);

                        MApp_ZUI_API_SetTimer(windata->hwndbar+3, 0, BUTTONCLICK_TIMER);
                        MApp_ZUI_API_InvalidateWindow(windata->hwndbar+3);
                        
                        MApp_ZUI_API_InvalidateAllSuccessors(windata->hwndcharlist);

                        return 0;
                    }
                    case VK_GREEN:
                    {
                        windata->u8CharType++;
                        windata->u8CharType %= (CHARTYPE-1);
                        MApp_ZUI_API_SetTimer(windata->hwndbar+4, 0, BUTTONCLICK_TIMER);
                        MApp_ZUI_API_InvalidateAllSuccessors(hwnd);
                    }
                    return 0;

                    case VK_RED:
                    {
                        windata->u8CharType = (CHARTYPE-1);
                        MApp_ZUI_API_SetTimer(windata->hwndbar+1, 0, BUTTONCLICK_TIMER);
                        MApp_ZUI_API_InvalidateAllSuccessors(hwnd);
                    }
                    return 0;

                    case VK_LEFT:
                        if(u8Index < windata->u8Rows )
                            s8NextIndex = u8Index;
                        else if(u8Index > 22)
                            s8NextIndex = u8Index - 2;
                        else
                            s8NextIndex = u8Index - windata->u8Rows;
                        break;
                    case VK_UP:
                        if(u8Index != 0)
                            s8NextIndex = u8Index - 1;
                        break;
                    case VK_RIGHT:
                        s8NextIndex = u8Index + windata->u8Rows;
                        if(u8Index == 20)
                            s8NextIndex = u8Index;
                        else if(u8Index >= 21)
                            s8NextIndex = u8Index + 2;
                        if ( s8NextIndex >= COUNTOF(idx2key))
                            s8NextIndex = u8Index;
                        break;
                    default:
                    case VK_DOWN:
                        s8NextIndex = u8Index + 1;
                        if(s8NextIndex >= COUNTOF(idx2key))
                            s8NextIndex = COUNTOF(idx2key)-1;
                        break;
                }

                hwndFocus = _MApp_ZUI_CTL_Keyboard_MapIndex2Hwnd(hwnd,s8NextIndex);
                MApp_ZUI_API_SetFocus(hwndFocus);
                windata->u8CurIndex = s8NextIndex;
            }
            return 0;

        default:
            break;
    }

    return DEFAULTWINPROC(hwnd, msg);

}

#undef MAPP_ZUI_CTL_KEYBOARD_C
