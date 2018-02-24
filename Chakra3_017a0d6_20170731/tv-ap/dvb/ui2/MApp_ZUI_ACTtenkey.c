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

#define MAPP_ZUI_ACTTENKEY_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "ZUI_tables_h.inl"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_ACTmainpage.h"
#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_ACTglobal.h"
#include "OSDcp_String_EnumIndex.h"
#include "ZUI_exefunc.h"
#include "MApp_GlobalFunction.h"
#include "MApp_TV.h"

#if ENABLE_ATSC
#include "msAPI_Scan_ATSC.h"
#endif

/////////////////////////////////////////////////////////////////////
extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);

void MApp_ZUI_ACT_AppShowTenKeyNumber(void)
{
    HWND wnd;
    RECT rect;
    E_OSD_ID osd_id = E_OSD_TENKEY_NUMBER;

    g_GUI_WindowList = GetWindowListOfOsdTable(osd_id);
    g_GUI_WinDrawStyleList = GetWindowStyleOfOsdTable(osd_id);
    g_GUI_WindowPositionList = GetWindowPositionOfOsdTable(osd_id);
#if ZUI_ENABLE_ALPHATABLE
    g_GUI_WinAlphaDataList = GetWindowAlphaDataOfOsdTable(osd_id);
#endif
    HWND_MAX = GetWndMaxOfOsdTable(osd_id);
    OSDPAGE_BLENDING_ENABLE = IsBlendingEnabledOfOsdTable(osd_id);
    OSDPAGE_BLENDING_VALUE = GetBlendingValueOfOsdTable(osd_id);

    if (!_MApp_ZUI_API_AllocateVarData())
    {
        ZUI_DBG_FAIL(printf("[ZUI]ALLOC\n"));
        ABORT();
        return;
    }

    RECT_SET(rect,
        ZUI_TENKEY_NUMBER_XSTART, ZUI_TENKEY_NUMBER_YSTART,
        ZUI_TENKEY_NUMBER_WIDTH, ZUI_TENKEY_NUMBER_HEIGHT);

    if (!MApp_ZUI_API_InitGDI(&rect))
    {
        ZUI_DBG_FAIL(printf("[ZUI]GDIINIT\n"));
        ABORT();
        return;
    }

    for (wnd = 0; wnd < HWND_MAX; wnd++)
    {
        //printf("create msg: %lu\n", (U32)wnd);
        MApp_ZUI_API_SendMessage(wnd, MSG_CREATE, 0);
    }

    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_SHOW);

    MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_NONE, E_ZUI_STATE_RUNNING);

}


//////////////////////////////////////////////////////////
// Key Handler

BOOLEAN MApp_ZUI_ACT_HandleTenKeyNumberKey(VIRTUAL_KEY_CODE key)
{
    //note: don't do anything here! keys will be handled in state machines
    //      moved to MApp_TV_ProcessAudioVolumeKey()
    UNUSED(key);
    ZUI_DBG_FAIL(printf("[ZUI]IDLEKEY\n"));
    //ABORT();
    return FALSE;
}

void MApp_ZUI_ACT_TerminateTenKeyNumber(void)
{
   ZUI_MSG( printf("[]term:tenkey\n");)


}

BOOLEAN MApp_ZUI_ACT_ExecuteTenKeyNumberAction(U16 act)
{
    switch(act)
    {
        case EN_EXE_CLOSE_CURRENT_OSD:
        case EN_EXE_POWEROFF:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            return TRUE;

        case EN_EXE_RESET_AUTO_CLOSE_TIMER:
            //reset timer if any key
            MApp_ZUI_API_ResetTimer(HWND_TENKEY_BG, 0);
            return FALSE;
    }
    return FALSE;
}

LPTSTR MApp_ZUI_ACT_GetTenKeyNumberDynamicText(HWND hwnd)
{
    // Marked it by coverity_304
    //U16 u16TempID = Empty;

    switch(hwnd)
    {
        case HWND_TENKEY_CHNUMBER:
          #if ENABLE_SBTVD_DTV_SYSTEM
            if(msAPI_SRC_IS_SBTVD_InUse())
            {
                if (enLCNTypeVerified == MAJOR_CH_NUM)
                {
                    return MApp_ZUI_API_GetU16String(u8IdleMajorValue);
                }
                else
                {
                    LPTSTR str = CHAR_BUFFER;

                    MApp_UlongToU16String((U32)u8IdleMajorValue, str, (S8)MApp_GetNoOfDigit((U32)u8IdleMajorValue));
                    str += (MApp_GetNoOfDigit((U32)u8IdleMajorValue));
                    if (u8IdleMinorValue == 0)
                    {
                        if (MApp_Get_IdleDigitCount()  == 1)
                        {
                            *str ++ = CHAR_DOT;
                            *str ++ = CHAR_0;
                            *str ++ = 0;
                        }
                        else if (MApp_Get_IdleDigitCount()  == 2)
                        {
                            *str ++ = CHAR_DOT;
                            *str ++ = CHAR_0;
                            *str ++ = CHAR_0;
                            *str ++ = 0;
                        }
                        else
                        {
                            *str ++ = CHAR_DOT;
                            *str ++ = 0;
                        }
                    }
                    else if (u8IdleMinorValue < 10 && MApp_Get_IdleDigitCount()  == 2)
                    {
                        *str ++ = CHAR_DOT;
                        *str ++ = CHAR_0;
                        MApp_UlongToU16String((U32)u8IdleMinorValue, str, (S8)MApp_GetNoOfDigit((U32)u8IdleMinorValue));
                    }
                    else
                    {
                        *str ++ = CHAR_DOT;
                        MApp_UlongToU16String((U32)u8IdleMinorValue, str, (S8)MApp_GetNoOfDigit((U32)u8IdleMinorValue));
                    }
                    return CHAR_BUFFER;
                }
            }
            else
          #endif
            {
#if ENABLE_ATSC
                if(IsAtscInUse()||IsATVInUse())
                {
                    if(enVirChType2bVerified == MAJOR_CH_NUM)
                    {
                       MApp_UlongToU16String((U32)stVirtualChNum.major_num,CHAR_BUFFER,u8IdleDigitCount);
                    }
                    else if(enVirChType2bVerified == MINOR_CH_NUM)
                    {
                        MApp_UlongToU16String((U32)stVirtualChNum.major_num,CHAR_BUFFER,u8MajorNumDigitCount);
                        CHAR_BUFFER[u8MajorNumDigitCount] = '-';

#if ONE_PART_CHNO
                        if(stVirtualChNum.minor_num == INVALID_MINOR_NUMBER)
                        {
                            MApp_UlongToU16String((U32)0,&CHAR_BUFFER[u8MajorNumDigitCount+1],u8IdleDigitCount);
                        }
                        else
#endif
                        {
                            MApp_UlongToU16String((U32)stVirtualChNum.minor_num,&CHAR_BUFFER[u8MajorNumDigitCount+1],u8IdleDigitCount);
                        }
                    }
                    return CHAR_BUFFER;
                }
#endif
                return MApp_ZUI_API_GetU16String(MApp_Get_IdleInputValue());
            }
    }

    //if (u16TempID != Empty)
    //    return MApp_ZUI_API_GetString(u16TempID);

    return NULL; //for empty string
}



/////////////////////////////////////////////////////////
// Customize Window Procedures

#undef MAPP_ZUI_ACTTENKEY_C
