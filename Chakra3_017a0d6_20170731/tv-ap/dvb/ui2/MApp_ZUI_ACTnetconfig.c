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

#define MAPP_ZUI_ACTNETCONFIG_C
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

#include "msAPI_Global.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "ZUI_tables_h.inl"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_ACTmainpage.h"
#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_APIdraw.h"
#include "MApp_ZUI_ACTglobal.h"
#include "MApp_ZUI_ACTnetconfig.h"
#include "OSDcp_String_EnumIndex.h"
#include "ZUI_exefunc.h"
#include "MApp_ZUI_ACTmainpage.h"
#include "MApp_GlobalFunction.h"
#include "MApp_Sleep.h"
#include "msAPI_Timer.h"
#include "MApp_UiMenuDef.h"
#include "msAPI_DTVSystem.h"
#include "msAPI_ATVSystem.h"
#include "MApp_Key.h"

#if (ENABLE_DTV)
#include "mapp_demux.h"
#include "mapp_si.h"
#endif

#include "drvpower_if.h"
#include "MApp_GlobalVar.h"

//extern ST_NETWORK stNetwork;
////////////////////////////////////////////////////


BOOLEAN MApp_ZUI_ACT_ExecuteNetConfigDialogAction(U16 act)
{
#if 1
    act=act;
#else
    switch(act)
    {

        case EN_EXE_CLOSE_NET_CONFIG:
            MApp_ZUI_ACT_ShowMainMenuBackground(HWND_MENU_BOTTOM_BALL_FOCUS_OPTION);
            MApp_ZUI_API_ShowWindow(HWND_MENU_OPTION_PAGE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_MENU_OPTION_NET_CONFIG);
            return TRUE;

        case EN_EXE_INC_NET_CONFIG:
        case EN_EXE_DEC_NET_CONFIG:
            stGenSetting.g_SysSetting.g_Network.Net_Config_mode =
               (EN_NET_CONFIG_MODE) MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_NET_CONFIG,
                    stGenSetting.g_SysSetting.g_Network.Net_Config_mode,
                    EN_NET_CLOSE,
                    EN_NET_STATIC,
                    1);
            MApp_ZUI_API_InvalidateWindow(HWND_MENU_OPTIONLIST_ITEM1_OPTION);
            if(stGenSetting.g_SysSetting.g_Network.Net_Config_mode == EN_NET_STATIC)
            {
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTIONLIST_ITEM2, TRUE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTIONLIST_ITEM3, TRUE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTIONLIST_ITEM4, TRUE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTIONLIST_ITEM5, TRUE);
            }
            else if(stGenSetting.g_SysSetting.g_Network.Net_Config_mode == EN_NET_DHCP)
            {
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTIONLIST_ITEM2, FALSE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTIONLIST_ITEM3, FALSE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTIONLIST_ITEM4, FALSE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTIONLIST_ITEM5, FALSE);
            }
            else
            {
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTIONLIST_ITEM2, FALSE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTIONLIST_ITEM3, FALSE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTIONLIST_ITEM4, FALSE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTIONLIST_ITEM5, FALSE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTIONLIST_ITEM6, FALSE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTIONLIST_ITEM7, FALSE);
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTIONLIST_COMMON_PAGE);
            return TRUE;

        case EN_EXE_GOTO_NET_CONFIG_IP:
            MApp_ZUI_API_ShowWindow(HWND_MENU_OPTIONLIST_COMMON_PAGE, SW_HIDE);
            MApp_ZUI_ACT_SetOptionListMode(EN_COMMON_OPTIONLIST_NETWORK_IP);
            MApp_ZUI_API_ShowWindow(HWND_MENU_OPTIONLIST_COMMON_PAGE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_MENU_OPTIONLIST_ITEM2);
            return TRUE;

        case EN_EXE_GOTO_NET_CONFIG_NETMASK:
            MApp_ZUI_API_ShowWindow(HWND_MENU_OPTIONLIST_COMMON_PAGE, SW_HIDE);
            MApp_ZUI_ACT_SetOptionListMode(EN_COMMON_OPTIONLIST_NETWORK_NETMASK);
            MApp_ZUI_API_ShowWindow(HWND_MENU_OPTIONLIST_COMMON_PAGE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_MENU_OPTIONLIST_ITEM2);
            return TRUE;

        case EN_EXE_GOTO_NET_CONFIG_GW:
            MApp_ZUI_API_ShowWindow(HWND_MENU_OPTIONLIST_COMMON_PAGE, SW_HIDE);
            MApp_ZUI_ACT_SetOptionListMode(EN_COMMON_OPTIONLIST_NETWORK_GW);
            MApp_ZUI_API_ShowWindow(HWND_MENU_OPTIONLIST_COMMON_PAGE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_MENU_OPTIONLIST_ITEM2);
            return TRUE;

        case EN_EXE_GOTO_NET_CONFIG_DNS:
            MApp_ZUI_API_ShowWindow(HWND_MENU_OPTIONLIST_COMMON_PAGE, SW_HIDE);
            MApp_ZUI_ACT_SetOptionListMode(EN_COMMON_OPTIONLIST_NETWORK_DNS);
            MApp_ZUI_API_ShowWindow(HWND_MENU_OPTIONLIST_COMMON_PAGE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_MENU_OPTIONLIST_ITEM2);
            return TRUE;

        case EN_EXE_ONOFF_NET_CONFIG_PROXY:
            stGenSetting.g_SysSetting.g_Network.bProxyMode = !stGenSetting.g_SysSetting.g_Network.bProxyMode;
            MApp_ZUI_API_InvalidateWindow(HWND_MENU_OPTIONLIST_ITEM6_OPTION);
            return TRUE;

        case EN_EXE_GOTO_NET_CONFIG_MAC:
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTIONLIST_ITEM7_OPTION);
            return TRUE;


        default:// enable below is correct now
            break;

    }
#endif
    return FALSE;
}

BOOLEAN MApp_ZUI_ACT_ExecuteNetIPDialogAction(U16 act)
{
#if 1
    act=act;
#else

    switch(act)
    {
        case EN_EXE_CLOSE_NET_IP:
            return TRUE;

        case EN_EXE_DEC_NET_IP_A:
        case EN_EXE_INC_NET_IP_A:
            if(!(stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Network_Flag & UI_NET_ADDRESS_A_SET))
            {
                stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_A = UI_NETWORK_INIT;
            }

            stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_A=(U8)
                MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_NET_IP_A,
                    stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_A, 0, 255, 1);
            stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Network_Flag |= UI_NET_ADDRESS_A_SET;
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTIONLIST_ITEM2_OPTION);

            // automatically set the network mask
            if(!(stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Network_Flag & UI_NET_ADDRESS_A_SET))
            {
                stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_A = UI_NETWORK_INIT + 255;
                //stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Network_Flag |= UI_NET_ADDRESS_A_SET;
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTIONLIST_ITEM2_OPTION);
            }

            // automatically set the gateway address
            if(!(stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Network_Flag & UI_NET_ADDRESS_A_SET))
            {
                stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_A = stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_A;
                //stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Network_Flag |= UI_NET_ADDRESS_A_SET;
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTIONLIST_ITEM2_OPTION);
            }

            // automatically set the dns address
            if(!(stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Network_Flag & UI_NET_ADDRESS_A_SET))
            {
                stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_A = stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_A;
                //stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Network_Flag |= UI_NET_ADDRESS_A_SET;
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTIONLIST_ITEM2_OPTION);
            }
            return TRUE;

        case EN_EXE_DEC_NET_IP_B:
        case EN_EXE_INC_NET_IP_B:
            if(!(stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Network_Flag & UI_NET_ADDRESS_B_SET))
            {
                stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_B = UI_NETWORK_INIT;
            }

            stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_B=(U8)
                MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_NET_IP_B,
                    stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_B, 0, 255, 1);

            stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Network_Flag |= UI_NET_ADDRESS_B_SET;
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTIONLIST_ITEM3_OPTION);

            // automatically set the network mask
            if(!(stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Network_Flag & UI_NET_ADDRESS_B_SET))
            {
                stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_B = UI_NETWORK_INIT + 255;
                //stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Network_Flag |= UI_NET_ADDRESS_B_SET;
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTIONLIST_ITEM3_OPTION);
            }

            // automatically set the gateway address
            if(!(stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Network_Flag & UI_NET_ADDRESS_B_SET))
            {
                stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_B = stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_B;
                //stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Network_Flag |= UI_NET_ADDRESS_B_SET;
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTIONLIST_ITEM3_OPTION);
            }

            // automatically set the dns address
            if(!(stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Network_Flag & UI_NET_ADDRESS_B_SET))
            {
                stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_B = stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_B;
                //stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Network_Flag |= UI_NET_ADDRESS_B_SET;
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTIONLIST_ITEM3_OPTION);
            }
            return TRUE;

        case EN_EXE_DEC_NET_IP_C:
        case EN_EXE_INC_NET_IP_C:
            if(!(stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Network_Flag & UI_NET_ADDRESS_C_SET))
            {
                stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_C = UI_NETWORK_INIT;
            }

            stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_C=(U8)
                MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_NET_IP_C,
                    stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_C, 0, 255, 1);

            stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Network_Flag |= UI_NET_ADDRESS_C_SET;
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTIONLIST_ITEM4_OPTION);

            // automatically set the network mask
            if(!(stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Network_Flag & UI_NET_ADDRESS_C_SET))
            {
                stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_C = UI_NETWORK_INIT + 255;
                //stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Network_Flag |= UI_NET_ADDRESS_C_SET;
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTIONLIST_ITEM4_OPTION);
            }

            // automatically set the gateway address
            if(!(stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Network_Flag & UI_NET_ADDRESS_C_SET))
            {
                stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_C = stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_C;
                //stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Network_Flag |= UI_NET_ADDRESS_C_SET;
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTIONLIST_ITEM4_OPTION);
            }

            // automatically set the dns address
            if(!(stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Network_Flag & UI_NET_ADDRESS_C_SET))
            {
                stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_C = stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_C;
                //stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Network_Flag |= UI_NET_ADDRESS_C_SET;
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTIONLIST_ITEM4_OPTION);
            }
            return TRUE;

        case EN_EXE_DEC_NET_IP_D:
        case EN_EXE_INC_NET_IP_D:
            if(!(stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Network_Flag & UI_NET_ADDRESS_D_SET))
            {
                stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_D = UI_NETWORK_INIT;
            }

            stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_D=(U8)
                MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_NET_IP_D,
                    stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_D, 0, 255, 1);

            stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Network_Flag |= UI_NET_ADDRESS_D_SET;
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTIONLIST_ITEM5_OPTION);

            return TRUE;

        default:
            ZUI_DBG_FAIL(printf("[ZUI]Network ip failed\n"));
            ABORT();


    }
#endif
    return FALSE;
}

BOOLEAN MApp_ZUI_ACT_ExecuteNetNetmaskDialogAction(U16 act)
{
#if 1
    act=act;
#else

    switch(act)
    {
        case EN_EXE_CLOSE_NET_NETMASK:
            return TRUE;

        case EN_EXE_DEC_NET_NETMASK_A:
        case EN_EXE_INC_NET_NETMASK_A:
            if(!(stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Network_Flag & UI_NET_ADDRESS_A_SET) && (stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_A == UI_NETWORK_INIT))
            {
                stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_A = UI_NETWORK_INIT;
            }

            stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_A=(U8)
                MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_NET_NETMASK_A,
                    stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_A, 0, 255, 1);

            stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Network_Flag |= UI_NET_ADDRESS_A_SET;

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTIONLIST_ITEM2_OPTION);

            return TRUE;

        case EN_EXE_DEC_NET_NETMASK_B:
        case EN_EXE_INC_NET_NETMASK_B:

            if(!(stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Network_Flag & UI_NET_ADDRESS_B_SET) && (stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_B == UI_NETWORK_INIT))
            {
                stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_B = UI_NETWORK_INIT;
            }

            stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_B=(U8)
                MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_NET_NETMASK_B,
                    stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_B, 0, 255, 1);

            stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Network_Flag |= UI_NET_ADDRESS_B_SET;

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTIONLIST_ITEM3_OPTION);

            return TRUE;

        case EN_EXE_DEC_NET_NETMASK_C:
        case EN_EXE_INC_NET_NETMASK_C:
            if(!(stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Network_Flag & UI_NET_ADDRESS_C_SET) && (stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_C == UI_NETWORK_INIT))
            {
                stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_C = UI_NETWORK_INIT;
            }

            stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_C=(U8)
                MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_NET_NETMASK_C,
                    stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_C, 0, 255, 1);

            stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Network_Flag |= UI_NET_ADDRESS_C_SET;

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTIONLIST_ITEM4_OPTION);

            return TRUE;

        case EN_EXE_DEC_NET_NETMASK_D:
        case EN_EXE_INC_NET_NETMASK_D:
            if(!(stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Network_Flag & UI_NET_ADDRESS_D_SET))
            {
                stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_D = UI_NETWORK_INIT;
            }

            stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_D=(U8)
                MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_NET_NETMASK_D,
                    stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_D, 0, 255, 1);

            stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Network_Flag |= UI_NET_ADDRESS_D_SET;

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTIONLIST_ITEM5_OPTION);

            return TRUE;

        default:
            ZUI_DBG_FAIL(printf("[ZUI]Network netmask failed\n"));
            ABORT();


    }
#endif

    return FALSE;
}

BOOLEAN MApp_ZUI_ACT_ExecuteNetGatewayDialogAction(U16 act)
{
#if 1
    act=act;
#else

    switch(act)
    {
        case EN_EXE_CLOSE_NET_GATEWAY:
            return TRUE;

        case EN_EXE_DEC_NET_GATEWAY_A:
        case EN_EXE_INC_NET_GATEWAY_A:
            if(!(stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Network_Flag & UI_NET_ADDRESS_A_SET) && (stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_A == UI_NETWORK_INIT))
            {
                stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_A = UI_NETWORK_INIT;
            }

            stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_A=(U8)
                MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_NET_GATEWAY_A,
                    stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_A, 0, 255, 1);

            stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Network_Flag |= UI_NET_ADDRESS_A_SET;

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTIONLIST_ITEM2_OPTION);

            return TRUE;

        case EN_EXE_DEC_NET_GATEWAY_B:
        case EN_EXE_INC_NET_GATEWAY_B:
            if(!(stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Network_Flag & UI_NET_ADDRESS_B_SET) && (stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_B == UI_NETWORK_INIT))
            {
                stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_B = UI_NETWORK_INIT;
            }

            stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_B=(U8)
                MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_NET_GATEWAY_B,
                    stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_B, 0, 255, 1);

            stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Network_Flag |= UI_NET_ADDRESS_B_SET;

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTIONLIST_ITEM3_OPTION);

            return TRUE;

        case EN_EXE_DEC_NET_GATEWAY_C:
        case EN_EXE_INC_NET_GATEWAY_C:
            if(!(stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Network_Flag & UI_NET_ADDRESS_C_SET) && (stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_C == UI_NETWORK_INIT))
            {
                stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_C = UI_NETWORK_INIT;
            }

            stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_C=(U8)
                MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_NET_GATEWAY_C,
                    stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_C, 0, 255, 1);

            stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Network_Flag |= UI_NET_ADDRESS_C_SET;

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTIONLIST_ITEM4_OPTION);

            return TRUE;

        case EN_EXE_DEC_NET_GATEWAY_D:
        case EN_EXE_INC_NET_GATEWAY_D:
            if(!(stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Network_Flag & UI_NET_ADDRESS_D_SET))
            {
                stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_D = UI_NETWORK_INIT;
            }

            stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_D=(U8)
                MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_NET_GATEWAY_D,
                    stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_D, 0, 255, 1);

            stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Network_Flag |= UI_NET_ADDRESS_D_SET;

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTIONLIST_ITEM5_OPTION);

            return TRUE;

        default:
            ZUI_DBG_FAIL(printf("[ZUI]Network gateway failed\n"));
            ABORT();
    }
#endif

    return FALSE;
}

BOOLEAN MApp_ZUI_ACT_ExecuteNetDNSDialogAction(U16 act)
{
#if 1
    act=act;
#else

    switch(act)
    {
        case EN_EXE_CLOSE_NET_DNS:
            return TRUE;

        case EN_EXE_DEC_NET_DNS_A:
        case EN_EXE_INC_NET_DNS_A:
            if(!(stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Network_Flag & UI_NET_ADDRESS_A_SET) && (stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_A == UI_NETWORK_INIT))
            {
                stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_A = UI_NETWORK_INIT;
            }

            stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_A=(U8)
                MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_NET_DNS_A,
                    stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_A, 0, 255, 1);

            stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Network_Flag |= UI_NET_ADDRESS_A_SET;

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTIONLIST_ITEM2_OPTION);

            return TRUE;

        case EN_EXE_DEC_NET_DNS_B:
        case EN_EXE_INC_NET_DNS_B:
            if(!(stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Network_Flag & UI_NET_ADDRESS_B_SET) && (stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_B == UI_NETWORK_INIT))
            {
                stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_B = UI_NETWORK_INIT;
            }

            stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_B=(U8)
                MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_NET_DNS_B,
                    stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_B, 0, 255, 1);

            stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Network_Flag |= UI_NET_ADDRESS_B_SET;

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTIONLIST_ITEM3_OPTION);

            return TRUE;

        case EN_EXE_DEC_NET_DNS_C:
        case EN_EXE_INC_NET_DNS_C:
            if(!(stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Network_Flag & UI_NET_ADDRESS_C_SET) && (stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_C == UI_NETWORK_INIT))
            {
                stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_C = UI_NETWORK_INIT;
            }

            stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_C=(U8)
                MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_NET_DNS_C,
                    stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_C, 0, 255, 1);

            stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Network_Flag |= UI_NET_ADDRESS_C_SET;

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTIONLIST_ITEM4_OPTION);

            return TRUE;

        case EN_EXE_DEC_NET_DNS_D:
        case EN_EXE_INC_NET_DNS_D:
            if(!(stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Network_Flag & UI_NET_ADDRESS_D_SET))
            {
                stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_D = UI_NETWORK_INIT;
            }

            stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_D=(U8)
                MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_NET_DNS_D,
                    stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_D, 0, 255, 1);

            stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Network_Flag |= UI_NET_ADDRESS_D_SET;

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTIONLIST_ITEM5_OPTION);

            return TRUE;

        default:
            ZUI_DBG_FAIL(printf("[ZUI]Network DNS failed\n"));
            ABORT();


    }
#endif

    return FALSE;
}

LPTSTR MApp_ZUI_ACT_GetNetConfigDynamicText(HWND hwnd)
{
#if 1
    hwnd=hwnd;
#else

    U16 u16TempID = Empty;


    switch(hwnd)
    {
        case HWND_MENU_OPTIONLIST_ITEM1_OPTION:
        {
            if(stGenSetting.g_SysSetting.g_Network.Net_Config_mode == EN_NET_DHCP)
            {
                u16TempID = en_str_DHCP;
            }
            else if(stGenSetting.g_SysSetting.g_Network.Net_Config_mode == EN_NET_STATIC)
            {
                u16TempID = en_str_Static;
            }
            else
            {
                u16TempID = en_str_Off;
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTIONLIST_ITEM1_OPTION);
        }
        break;

        case HWND_MENU_OPTIONLIST_ITEM2_OPTION:
        {
            LPTSTR str = CHAR_BUFFER;
            MApp_ZUI_API_LoadString(en_str_IP, str);
            str += MApp_ZUI_API_Strlen(str);
            *str ++ = CHAR_SPACE;
            MApp_UlongToU16String( (U32)stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_A ,
                                   str,
                                   MApp_GetNoOfDigit((U32) stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_A));
           str += MApp_GetNoOfDigit((U32) stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_A);
           *str ++ = CHAR_DOT;

           MApp_UlongToU16String( (U32)stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_B,
                                   str,
                                   MApp_GetNoOfDigit((U32) stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_B));
           str += MApp_GetNoOfDigit((U32) stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_B);
           *str ++ = CHAR_DOT;

           MApp_UlongToU16String( (U32)stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_C,
                                   str,
                                   MApp_GetNoOfDigit((U32) stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_C));
           str += MApp_GetNoOfDigit((U32) stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_C);
           *str ++ = CHAR_DOT;

           MApp_UlongToU16String( (U32)stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_D,
                                   str,
                                   MApp_GetNoOfDigit((U32) stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_D));

              #if 0 // Coverity_0946
                if(CHAR_BUFFER != (LPTSTR)Empty)
                    return CHAR_BUFFER;
                else
                    u16TempID=en_str_dashdash;
              #else
                return CHAR_BUFFER;
              #endif
        }
        break;

        case HWND_MENU_OPTIONLIST_ITEM3_OPTION:
        {

                LPTSTR str = CHAR_BUFFER;
                MApp_ZUI_API_LoadString(en_str_Netmask, str);
                str += MApp_ZUI_API_Strlen(str);
                *str ++ = CHAR_SPACE;
                MApp_UlongToU16String( (U32)stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_A,
                                        str,
                                        MApp_GetNoOfDigit((U32) stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_A));
                str += MApp_GetNoOfDigit((U32) stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_A);
                *str ++ = CHAR_DOT;

                MApp_UlongToU16String( (U32)stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_B,
                                        str,
                                        MApp_GetNoOfDigit((U32) stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_B));
                str += MApp_GetNoOfDigit((U32) stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_B);
                *str ++ = CHAR_DOT;

                MApp_UlongToU16String( (U32)stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_C,
                                        str,
                                        MApp_GetNoOfDigit((U32) stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_C));
                str += MApp_GetNoOfDigit((U32) stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_C);
                *str ++ = CHAR_DOT;

                MApp_UlongToU16String( (U32)stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_D,
                                        str,
                                        MApp_GetNoOfDigit((U32) stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_D));

              #if 0 // Coverity_0946
                if(CHAR_BUFFER != (LPTSTR)Empty)
                    return CHAR_BUFFER;
                else
                    u16TempID=en_str_dashdash;
              #else
                return CHAR_BUFFER;
              #endif
        }
        break;

        case HWND_MENU_OPTIONLIST_ITEM4_OPTION:
        {
                LPTSTR str = CHAR_BUFFER;
                MApp_ZUI_API_LoadString(en_str_Gateway, str);
                str += MApp_ZUI_API_Strlen(str);
                *str ++ = CHAR_SPACE;
                MApp_UlongToU16String( (U32)stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_A,
                                        str,
                                        MApp_GetNoOfDigit((U32) stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_A));
                str += MApp_GetNoOfDigit((U32) stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_A);
                *str ++ = CHAR_DOT;

                MApp_UlongToU16String( (U32)stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_B,
                                        str,
                                        MApp_GetNoOfDigit((U32) stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_B));
                str += MApp_GetNoOfDigit((U32) stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_B);
                *str ++ = CHAR_DOT;

                MApp_UlongToU16String( (U32)stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_C,
                                        str,
                                        MApp_GetNoOfDigit((U32) stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_C));
                str += MApp_GetNoOfDigit((U32) stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_C);
                *str ++ = CHAR_DOT;

                MApp_UlongToU16String( (U32)stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_D,
                                        str,
                                        MApp_GetNoOfDigit((U32) stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_D));

              #if 0 // Coverity_0946
                if(CHAR_BUFFER != (LPTSTR)Empty)
                    return CHAR_BUFFER;
                else
                    u16TempID=en_str_dashdash;
              #else
                return CHAR_BUFFER;
              #endif
        }
        break;

        case HWND_MENU_OPTIONLIST_ITEM5_OPTION:
        {

                LPTSTR str = CHAR_BUFFER;
                MApp_ZUI_API_LoadString(en_str_DNS, str);
                str += MApp_ZUI_API_Strlen(str);
                *str ++ = CHAR_SPACE;
                MApp_UlongToU16String( (U32)stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_A,
                                        str,
                                        MApp_GetNoOfDigit((U32) stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_A));
                str += MApp_GetNoOfDigit((U32) stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_A);

                *str ++ = CHAR_DOT;

                MApp_UlongToU16String( (U32)stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_B,
                                        str,
                                        MApp_GetNoOfDigit((U32) stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_B));
                str += MApp_GetNoOfDigit((U32) stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_B);

                *str ++ = CHAR_DOT;

                MApp_UlongToU16String( (U32)stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_C,
                                        str,
                                        MApp_GetNoOfDigit((U32) stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_C));
                str += MApp_GetNoOfDigit((U32) stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_C);

                *str ++ = CHAR_DOT;

                MApp_UlongToU16String( (U32)stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_D,
                                        str,
                                        MApp_GetNoOfDigit((U32) stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_D));

              #if 0 // Coverity_0946
                if(CHAR_BUFFER != (LPTSTR)Empty)
                    return CHAR_BUFFER;
                else
                    u16TempID=en_str_dashdash;
              #else
                return CHAR_BUFFER;
              #endif
       }
        break;

        case HWND_MENU_OPTIONLIST_ITEM6_OPTION:
       {
            LPTSTR u16str = CHAR_BUFFER;
            U16 u16len = NULL;
            U16 u16TextID = NULL;
            U16 u16OptionID = NULL;
            U16 u16con_buffer[64];
            u16TextID = en_str_Proxy;
            if(!stGenSetting.g_SysSetting.g_Network.bProxyMode)
                u16OptionID = en_str_Off;
            else
                u16OptionID = en_str_On;
            MApp_ZUI_API_LoadString(u16TextID, u16str);
            u16len = MApp_ZUI_API_Strlen(u16str);
            u16str[u16len++] = CHAR_SPACE;
            u16str[u16len++] = 0;
            MApp_ZUI_API_LoadString(u16OptionID, u16con_buffer);
            MApp_ZUI_API_Strcat(u16str,(U16*)u16con_buffer);
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTIONLIST_ITEM6_OPTION);
            return u16str;
       }
        break;

       }

       if (u16TempID != Empty)
            return MApp_ZUI_API_GetString(u16TempID);
#endif
       return 0; //for empty string....
}

LPTSTR MApp_ZUI_ACT_GetNetIPDynamicText(HWND hwnd)
{
#if 1
    hwnd=hwnd;
    return CHAR_BUFFER;
#else

    // Marked it by coverity_302
    //U16 u16TempID = Empty;
    LPTSTR u16str = CHAR_BUFFER;
    U16 u16len = NULL;
    U16 u16TextID = NULL;
    U16 u16OptionID = NULL;
    U16 u16con_buffer[12];
    switch(hwnd)
    {
        case HWND_MENU_OPTIONLIST_ITEM2_OPTION:
        {
            u16TextID = en_str_CLASS_A;
            u16OptionID = (U16)stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_A;
            break;
        }
        case HWND_MENU_OPTIONLIST_ITEM3_OPTION:
        {
            u16TextID = en_str_CLASS_B;
            u16OptionID = (U16)stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_B;
            break;
        }
        case HWND_MENU_OPTIONLIST_ITEM4_OPTION:
        {
            u16TextID = en_str_CLASS_C;
            u16OptionID = (U16)stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_C;
            break;
        }
        case HWND_MENU_OPTIONLIST_ITEM5_OPTION:
        {
            u16TextID = en_str_CLASS_D;
            u16OptionID = (U16)stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_D;
            break;
        }
        default:
            return 0; //for empty string....
    }
    MApp_ZUI_API_LoadString(u16TextID, u16str);
    u16len = MApp_ZUI_API_Strlen(u16str);
    u16str[u16len++] = CHAR_SPACE;
    u16str[u16len++] = 0;
    MApp_UlongToU16String(u16OptionID, (U16*)u16con_buffer, 3);
    MApp_ZUI_API_Strcat(u16str,(U16*)u16con_buffer);
    //if (u16TempID != Empty)
    //    return MApp_ZUI_API_GetString(u16TempID);

    return u16str;
#endif
}

LPTSTR MApp_ZUI_ACT_GetNetNetmaskDynamicText(HWND hwnd)
{
#if 1
    hwnd=hwnd;
    return CHAR_BUFFER;
#else

    // Marked it by coverity_303
    //U16 u16TempID = Empty;
    LPTSTR u16str = CHAR_BUFFER;
    U16 u16len = NULL;
    U16 u16TextID = NULL;
    U16 u16OptionID = NULL;
    U16 u16con_buffer[12];
    switch(hwnd)
    {
        case HWND_MENU_OPTIONLIST_ITEM2_OPTION:
        {
            u16TextID = en_str_CLASS_A;
            u16OptionID = (U16)stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_A;
            break;
        }
        case HWND_MENU_OPTIONLIST_ITEM3_OPTION:
        {
            u16TextID = en_str_CLASS_B;
            u16OptionID = (U16)stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_B;
            break;
        }
        case HWND_MENU_OPTIONLIST_ITEM4_OPTION:
        {
            u16TextID = en_str_CLASS_C;
            u16OptionID = (U16)stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_C;
            break;
        }
        case HWND_MENU_OPTIONLIST_ITEM5_OPTION:
        {
            u16TextID = en_str_CLASS_D;
            u16OptionID = (U16)stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_D;
            break;
        }
        default:
            return 0; //for empty string....
    }
    MApp_ZUI_API_LoadString(u16TextID, u16str);
    u16len = MApp_ZUI_API_Strlen(u16str);
    u16str[u16len++] = CHAR_SPACE;
    u16str[u16len++] = 0;
    MApp_UlongToU16String(u16OptionID, (U16*)u16con_buffer, 3);
    MApp_ZUI_API_Strcat(u16str,(U16*)u16con_buffer);
    //if (u16TempID != Empty)
    //    return MApp_ZUI_API_GetString(u16TempID);

    return u16str;
#endif
}

LPTSTR MApp_ZUI_ACT_GetNetGatewayDynamicText(HWND hwnd)
{
#if 1
    hwnd=hwnd;
    return CHAR_BUFFER;
#else

    // Marked it by coverity_301
    //U16 u16TempID = Empty;
    LPTSTR u16str = CHAR_BUFFER;
    U16 u16len = NULL;
    U16 u16TextID = NULL;
    U16 u16OptionID = NULL;
    U16 u16con_buffer[12];
    switch(hwnd)
    {
         case HWND_MENU_OPTIONLIST_ITEM2_OPTION:
        {
            u16TextID = en_str_CLASS_A;
            u16OptionID = (U16)stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_A;
            break;
        }
        case HWND_MENU_OPTIONLIST_ITEM3_OPTION:
        {
            u16TextID = en_str_CLASS_B;
            u16OptionID = (U16)stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_B;
            break;
        }
        case HWND_MENU_OPTIONLIST_ITEM4_OPTION:
        {
            u16TextID = en_str_CLASS_C;
            u16OptionID = (U16)stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_C;
            break;
        }
        case HWND_MENU_OPTIONLIST_ITEM5_OPTION:
        {
            u16TextID = en_str_CLASS_D;
            u16OptionID = (U16)stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_D;
            break;
        }
        default:
            return 0; //for empty string....
    }
    MApp_ZUI_API_LoadString(u16TextID, u16str);
    u16len = MApp_ZUI_API_Strlen(u16str);
    u16str[u16len++] = CHAR_SPACE;
    u16str[u16len++] = 0;
    MApp_UlongToU16String(u16OptionID, (U16*)u16con_buffer, 3);
    MApp_ZUI_API_Strcat(u16str,(U16*)u16con_buffer);
    //if (u16TempID != Empty)
    //    return MApp_ZUI_API_GetString(u16TempID);

    return u16str;
#endif
}

LPTSTR MApp_ZUI_ACT_GetNetDNSDynamicText(HWND hwnd)
{
#if 1
    hwnd=hwnd;
    return CHAR_BUFFER;
#else

    // Marked it by coverity_300
    //U16 u16TempID = Empty;
    LPTSTR u16str = CHAR_BUFFER;
    U16 u16len = NULL;
    U16 u16TextID = NULL;
    U16 u16OptionID = NULL;
    U16 u16con_buffer[12];
    switch(hwnd)
    {
        case HWND_MENU_OPTIONLIST_ITEM2_OPTION:
        {
            u16TextID = en_str_CLASS_A;
            u16OptionID = (U16)stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_A;
            break;
        }
        case HWND_MENU_OPTIONLIST_ITEM3_OPTION:
        {
            u16TextID = en_str_CLASS_B;
            u16OptionID = (U16)stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_B;
            break;
        }
        case HWND_MENU_OPTIONLIST_ITEM4_OPTION:
        {
            u16TextID = en_str_CLASS_C;
            u16OptionID = (U16)stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_C;
            break;
        }
        case HWND_MENU_OPTIONLIST_ITEM5_OPTION:
        {
            u16TextID = en_str_CLASS_D;
            u16OptionID = (U16)stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_D;
            break;
        }
        default:
            return 0;   //for empty string....
    }
    MApp_ZUI_API_LoadString(u16TextID, u16str);
    u16len = MApp_ZUI_API_Strlen(u16str);
    u16str[u16len++] = CHAR_SPACE;
    u16str[u16len++] = 0;
    MApp_UlongToU16String(u16OptionID, (U16*)u16con_buffer, 3);
    MApp_ZUI_API_Strcat(u16str,(U16*)u16con_buffer);
    //if (u16TempID != Empty)
    //    return MApp_ZUI_API_GetString(u16TempID);

    return u16str;
#endif
}

#undef MAPP_ZUI_ACTNETCONFIG_C
