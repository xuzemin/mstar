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

#define MAPP_ZUI_ACTPVR_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal

/********************************************************************************/
/*                              Macro                                           */
/********************************************************************************/
#define PVR_TIMESHIFT_PLAYBACK_TIME_DBG(y) //y
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
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_ACTmainpage.h"
#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_ACTglobal.h"
#include "OSDcp_String_EnumIndex.h"
#include "ZUI_exefunc.h"

#include "MApp_ZUI_ACTpvr.h"
#include "MApp_PVR_Main.h"
#include "MApp_Menu_Main.h"

#include "msAPI_FSEnv.h"
#include "msAPI_PVRFileSystem.h"
#include "FSUtil.h"
#include "MApp_GlobalFunction.h"
#include "MApp_UiMenuDef.h"
#include "MApp_ZUI_ACTmenufunc.h"
#include "MApp_ZUI_GlobalFunction.h"
#include "MApp_MassStorage.h"
#include "msAPI_FCtrl.h"
#include "MApp_TimeShift.h"
#include "MApp_Playback.h"
#include "IOUtil.h"
#include "MApp_OSDPage_Main.h"
#include "MApp_TopStateMachine.h"

#include "msAPI_Timer.h"  //Add for resolving the issue that UI is flashing too fast after formatting disc 20100221EL
#if ENABLE_S2
#include "MApp_ZUI_ACTDishSetup.h"
extern EN_MENU_STATE enMainMenuState;
extern EN_DISHSETUP_STATE enDishSetupState;
#endif

/////////////////////////////////////////////////////////////////////
#if ENABLE_PVR
#define PVR_ICON_FLASH 0

#define PVR_ZUI_DBG(x)    //x

static EN_PVR_MENU_STATE _enTargetPvrState;


#if 0 //fix pvr
#define STRBUFF2_LENGTH 10
#define STRBUFF3_LENGTH 20
static U16 CHAR_BUFFER2[STRBUFF2_LENGTH];
static U16 CHAR_BUFFER3[STRBUFF3_LENGTH];
#else
#define STRBUFF4_LENGTH 10
#define STRBUFF3_LENGTH 20
static U16 CHAR_BUFFER4[STRBUFF4_LENGTH];
static U16 CHAR_BUFFER3[STRBUFF3_LENGTH];
#endif

extern void _MApp_ChannelList_ChannelChange(U16 u16ListOrdinal, U8 u8CMType, BOOLEAN bShowInfo, E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eProgramAccessibleBoundary);

MEMBER_SERVICETYPE PvrNewCMType;
U16 PvrNewPos;

extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);
extern BOOLEAN _MApp_ZUI_API_WindowProcOnIdle(void);
extern LPTSTR _MApp_ZUI_ACT_GetLocalClockTimeString(LPTSTR str);
static void _MApp_ZUI_ACT_PVR_SetFocus(HWND hwnd);

void MApp_ZUI_ACT_AppShowPVR(void)
{
    HWND wnd;
    RECT rect;
    E_OSD_ID osd_id = E_OSD_PVR;

    g_GUI_WindowList = GetWindowListOfOsdTable(osd_id);
    g_GUI_WinDrawStyleList = GetWindowStyleOfOsdTable(osd_id);
    g_GUI_WindowPositionList = GetWindowPositionOfOsdTable(osd_id);
#if ZUI_ENABLE_ALPHATABLE
    g_GUI_WinAlphaDataList = GetWindowAlphaDataOfOsdTable(osd_id);
#endif
    HWND_MAX = GetWndMaxOfOsdTable(osd_id);
    OSDPAGE_BLENDING_ENABLE = IsBlendingEnabledOfOsdTable(osd_id);
    OSDPAGE_BLENDING_VALUE = GetBlendingValueOfOsdTable(osd_id);

    _enTargetPvrState= STATE_PVR_MENU_CLEAN_UP;

    if (!_MApp_ZUI_API_AllocateVarData())
    {
        ZUI_DBG_FAIL(printf("[ZUI]ALLOC\n"));
        ABORT();
        return;
    }

    RECT_SET(rect,
        ZUI_PVR_XSTART, ZUI_PVR_YSTART,
        ZUI_PVR_WIDTH, ZUI_PVR_HEIGHT);

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

    _enTargetPvrState = STATE_PVR_NULL; //defaul value

    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_PVR_BG_CLEAN, SW_SHOW);

    if(enPvrState==STATE_PVR_CHECK_FS_INIT)
    {
        MApp_ZUI_API_ShowWindow(HWND_PVR_BG_PANE, SW_SHOW);
        MApp_ZUI_API_ShowWindow(HWND_PVR_SPEED_CHECK_SPEED_PERCENTAGE_BAR, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_PVR_SPEED_CHECK_SPEED_TAG_OPTION, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_PVR_FILE_SYS_PAGE_LIST, SW_SHOW);
        MApp_ZUI_API_SetFocus(HWND_PVR_SELECT_DISK_ITEM);
    }
    else
    {
        if(MApp_TopStateMachine_GetTopState() == STATE_TOP_OSDPAGE)
            MApp_OSDPage_SetState(STATE_OSDPAGE_EXIT);
        MApp_ZUI_API_KillTimer(HWND_PVR_BG, 0); //disable AUTO Close function
    }

    ZUI_MSG(printf("MApp_ZUI_ACT_AppShowPVR\n");)
    MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_PAGE_EXIT, E_ZUI_STATE_RUNNING);

}


//////////////////////////////////////////////////////////
// Key Handler

typedef struct _MENU_KEY2BTN_STRUCT
{
    VIRTUAL_KEY_CODE key;
    HWND hwnd;
} MENU_KEY2BTN_STRUCT;

BOOLEAN MApp_ZUI_ACT_HandlePvrKey(VIRTUAL_KEY_CODE key)
{
    //note: this function will be called in running state

    //reset timer if any key
    if(MApp_ZUI_API_IsExistTimer(HWND_PVR_BG, 0))
        MApp_ZUI_API_ResetTimer(HWND_PVR_BG, 0);

    if(MApp_ZUI_API_IsExistTimer(HWND_PVR_WARNING_DLG_PANE, 0))
        MApp_ZUI_API_ResetTimer(HWND_PVR_WARNING_DLG_PANE, 0);
/*
    //show click animation
    {
        static  MENU_KEY2BTN_STRUCT _ZUI_TBLSEG _key2btn[] =
        {
            {VK_SELECT, HWND_PVR_HELP_OK_BG},
            {VK_EXIT, HWND_PVR_HELP_EXIT_BG},
            {VK_MENU, HWND_PVR_HELP_MENU_BG},
            {VK_UP, HWND_PVR_HELP_UP_ARROW},
            {VK_DOWN, HWND_PVR_HELP_DOWN_ARROW},
            {VK_LEFT, HWND_PVR_HELP_LEFT_ARROW},
            {VK_RIGHT, HWND_PVR_HELP_RIGHT_ARROW},
        };
        U8 i;
        if(MApp_ZUI_API_IsSuccessor(HWND_PVR_FILE_SYS_PAGE_LIST, MApp_ZUI_API_GetFocus()))
        {
            for (i = 0; i < COUNTOF(_key2btn); i++)
            {
                if (_key2btn[i].key == key)
                {
                    MApp_ZUI_API_SetTimer(_key2btn[i].hwnd, 0, BUTTONANICLICK_PERIOD);
                    MApp_ZUI_API_InvalidateWindow(_key2btn[i].hwnd);
                    break;
                }
            }
        }
    }
*/
    switch(key)
    {
        case VK_EXIT:
            if(MApp_ZUI_API_IsSuccessor(HWND_PVR_FILE_SYS_PAGE_LIST, MApp_ZUI_API_GetFocus()))
            {
                MApp_ZUI_ACT_ExecutePvrAction(EN_EXE_CLOSE_CURRENT_OSD);
                return TRUE;
            }
            break;

        case VK_MENU:
            if(MApp_ZUI_API_IsSuccessor(HWND_PVR_FILE_SYS_PAGE_LIST, MApp_ZUI_API_GetFocus()))
            {
                _enReturnMenuItem = STATE_RETURN_PVR_FILE_SYS;
                MApp_ZUI_ACT_ExecutePvrAction(EN_EXE_GOTO_MAINMENU);
            }
            else if(MApp_ZUI_API_IsSuccessor(HWND_PVR_SELECT_DISK_PANE, MApp_ZUI_API_GetFocus()))
            {
                MApp_ZUI_ACT_ExecutePvrAction(EN_EXE_PVR_SELECT_DISK_RESTORE_DISK);
            }
            else if(MApp_ZUI_API_IsSuccessor(HWND_PVR_CREATE_PARTITION_PANE, MApp_ZUI_API_GetFocus()))
            {
                MApp_ZUI_ACT_ExecutePvrAction(EN_EXE_CREATE_PARTITION_GOTO_PVR_BG_PANE);
            }
            else if(MApp_ZUI_API_IsSuccessor(HWND_PVR_FILE_SYSTEM_SETTING_PANE, MApp_ZUI_API_GetFocus()))
            {
                MApp_ZUI_ACT_ExecutePvrAction(EN_EXE_FILE_SYSTEM_SIZE_GOTO_PVR_BG_PANE);
            }
            else if(MApp_ZUI_API_IsSuccessor(HWND_PVR_TIME_SHIFT_SIZE_PANE, MApp_ZUI_API_GetFocus()))
            {
                MApp_ZUI_ACT_ExecutePvrAction(EN_EXE_TIME_SHIFT_SIZE_GOTO_PVR_BG_PANE);
            }
            return TRUE;

        case VK_POWER:
            MApp_ZUI_ACT_ExecutePvrAction(EN_EXE_POWEROFF);
            return TRUE;
        default:
            break;
    }
    return FALSE;
}

void MApp_ZUI_ACT_TerminatePVR(void)
{
    ZUI_MSG(printf("MApp_ZUI_ACT_TerminatePVR\n");)
    g_PVR_PopUpWarning = E_PVR_WARNING_NONE;
    g_PvrMenuPageType = MENU_PVR_NONE;
    enPvrState = _enTargetPvrState;
    if(MApp_TopStateMachine_GetTopState() == STATE_TOP_OSDPAGE)
       MApp_OSDPage_SetState(STATE_OSDPAGE_CLEAN_UP);
}

void MApp_ZUI_ACT_RenewPvrUI(void)
{
    MApp_ZUI_API_InvalidateAllSuccessors(HWND_MAINFRAME);
}

BOOLEAN MApp_ZUI_ACT_ExecutePvrAction(U16 act)
{
    switch(act)
    {
        case EN_EXE_CLOSE_CURRENT_OSD:
            _enTargetPvrState = STATE_PVR_MENU_CLEAN_UP;
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            return TRUE;

        case EN_EXE_GOTO_MAINMENU:
            _enTargetPvrState = STATE_PVR_MENU_GOTO_MAIN_MENU;
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            return TRUE;

        case EN_EXE_POWEROFF:
            _enTargetPvrState = STATE_PVR_MENU_GOTO_STANDBY;
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            return TRUE;

        case EN_EXE_GOTO_PVR_SELECT_DISK_PANE:

            MApp_UiPvr_CheckFS_SelectActiveDisk();
            return TRUE;

        case EN_EXE_SELECT_DISK_GOTO_PVR_BG_PANE:
            MApp_ZUI_ACT_PVR_GOTO_MAINMENU(MENU_PVR_CHECKFS_MAIN,PVR_CHECKFS_ITEM_SELECT_DISK);
            return TRUE;

        case EN_EXE_PVR_SELECT_DISK_USB_LEFT:
        case EN_EXE_PVR_SELECT_DISK_USB_RIGHT:
            //Move from Pluto MApp_UiMenuFunc_Adjfunction() Case MAPP_UIMENUFUNC_ADJ_PVR_CHECKFS_SELECT_USB
            if(PVR_USB_COUNT == 0 || PVR_USB_COUNT >= 3)   //Currently, only 2 USB port supportted
            {
                return FALSE;
            }

            //if (action == MIA_INCVALUE || action == MIA_DECVALUE)
            {
                if((g_u8PVRActiveDevice == MSD_USB_INDEX_START) && (MApp_MassStorage_DeviceConnectionDetect() & MS_USB2_CONNECTED))
                {
                    g_u8PVRActiveDevice = MSD_USB_2_INDEX_START;
                }
                else if((g_u8PVRActiveDevice == MSD_USB_2_INDEX_START) && (MApp_MassStorage_DeviceConnectionDetect() & MS_USB_CONNECTED))
                {
                    g_u8PVRActiveDevice = MSD_USB_INDEX_START;
                }
                else
                {
                    return FALSE; //not refresh disk
                }
                msAPI_MSDCtrl_ResetDevice(g_u8PVRActiveDevice);
                msAPI_MSDCtrl_CheckDevices();
                if(msAPI_MSDCtrl_GetDeviceStatus(g_u8PVRActiveDevice)==MSD_STATUS_INSERTED)
                {
                    if (!msAPI_FCtrl_ActiveDevice(g_u8PVRActiveDevice))
                    {
                        __ASSERT(0);
                        break;
                    }
                }
            }

            switch(g_u8PVRActiveDevice)
            {
#if ENABLE_USB
                case MSD_USB_INDEX_START:
                    g_u8PVRActiveDisk = MApp_MassStorage_GetFirstDriveByPort(MSD_PORT_1);
                    break;
#endif
#if ENABLE_USB_2
                case MSD_USB_2_INDEX_START:
                    g_u8PVRActiveDisk = MApp_MassStorage_GetFirstDriveByPort(MSD_PORT_2);
                    break;
#endif
                default:
                    g_u8PVRActiveDisk = MApp_MassStorage_GetFirstDriveByPort(MSD_PORT_1);
                    break;
            }
            MApp_PVR_SetDiskDriveIndex(g_u8PVRActiveDisk, FALSE);
            if (msAPI_PVRFS_GetFileSystemType() == PVR_FS_BULKFS)
                msAPI_PVRFS_Initial(TRUE);
            else
                msAPI_PVRFS_Initial(FALSE);
            MApp_ZUI_API_InvalidateWindow(HWND_PVR_SELECT_DISK_USB_OPTION);
            MApp_ZUI_API_InvalidateWindow(HWND_PVR_SELECT_DISK_DISK_OPTION);
            return TRUE;

        case EN_EXE_PVR_SELECT_DISK_DISK_LEFT:
            //Move from Pluto MApp_UiMenuFunc_Adjfunction()  Case MAPP_UIMENUFUNC_ADJ_PVR_CHECKFS_SELECT_DISK:
            g_u8PVRActiveDisk = MApp_MassStorage_GetPrevDriveIndexByDevice(g_u8PVRActiveDevice, g_u8PVRActiveDisk);
            MApp_ZUI_API_InvalidateWindow(HWND_PVR_SELECT_DISK_DISK_OPTION);
            return TRUE;

        case EN_EXE_PVR_SELECT_DISK_DISK_RIGHT:
            //Move from Pluto MApp_UiMenuFunc_Adjfunction() Case MAPP_UIMENUFUNC_ADJ_PVR_CHECKFS_SELECT_DISK:
            g_u8PVRActiveDisk = MApp_MassStorage_GetNextDriveIndexByDevice(g_u8PVRActiveDevice, g_u8PVRActiveDisk);
            MApp_ZUI_API_InvalidateWindow(HWND_PVR_SELECT_DISK_DISK_OPTION);
            return TRUE;

        case EN_EXE_PVR_SELECT_FREE_REC_LIMIT_RIGHT:
        case EN_EXE_PVR_SELECT_FREE_REC_LIMIT_LEFT:
                stGenSetting.g_SysSetting.u32PVR_RecordMaxTime = (MApp_ZUI_ACT_DecIncValue_Cycle(
                act==EN_EXE_PVR_SELECT_FREE_REC_LIMIT_RIGHT,
                stGenSetting.g_SysSetting.u32PVR_RecordMaxTime/SECONDS_PER_HOUR, 1, PVR_CHECKFS_MAX_RECORD_TIME/SECONDS_PER_HOUR, 1)) * SECONDS_PER_HOUR;
            MApp_ZUI_API_InvalidateWindow(HWND_PVR_FREE_REC_LIMIT_OPTION);
            return TRUE;

        case EN_EXE_PVR_SELECT_DISK_SET_DISK:
            //Move from Pluto MApp_UiMenuFunc_MainItem_Execfunction() case MAPP_UIMENUFUNC_PVR_CHECKFS_SET_DISK:
            MApp_PVR_SetDiskDriveIndex(g_u8PVRActiveDisk, FALSE);
            if (msAPI_PVRFS_GetFileSystemType() == PVR_FS_BULKFS)
                msAPI_PVRFS_Initial(TRUE);
            else
                msAPI_PVRFS_Initial(FALSE);
            MApp_ZUI_ACT_PVR_GOTO_MAINMENU(MENU_PVR_CHECKFS_MAIN,PVR_CHECKFS_ITEM_SELECT_DISK);
            return TRUE;
        case EN_EXE_PVR_SELECT_DISK_RESTORE_DISK:
            //Move from Pluto MApp_UiMenuFunc_MainItem_Execfunction() case MAPP_UIMENUFUNC_PVR_CHECKFS_RESTORE_DISK:
            g_u8PVRActiveDisk = MApp_MassStorage_GetCurrentDriveIndex();
            MApp_ZUI_ACT_PVR_GOTO_MAINMENU(MENU_PVR_CHECKFS_MAIN,PVR_CHECKFS_ITEM_SELECT_DISK);
            return TRUE;

        case EN_EXE_PVR_CREATE_PARTITION_START:
        #if (ENABLE_BULK_FILE_SYSTEM)
            MApp_UiPvr_CheckFS_Confirm_CreatePartition();
        #endif
            break;
        case EN_EXE_CREATE_PARTITION_GOTO_PVR_BG_PANE:
            MApp_ZUI_ACT_PVR_GOTO_MAINMENU(MENU_PVR_CHECKFS_MAIN,PVR_CHECKFS_ITEM_CHECK_FILE_SYSTEM);
            break;
        case EN_EXE_GOTO_PVR_CHECK_FS_START:
            MApp_UiPvr_CheckFS_StartCheckAll();
            return TRUE;

        case EN_EXE_GOTO_PVR_FILE_SYSTEM_SIZE_PANE:
            MApp_ZUI_API_ShowWindow(HWND_PVR_BG_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_FILE_SYS_PAGE_LIST, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_FORMAT_DISK_CHECK_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_FILE_SYSTEM_SETTING_PANE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_PVR_FILE_SYSTEM_SETTING_TYPE_ITEM);
            MApp_UiPvr_CheckFS_StartFormat();
            #ifdef OBAMA
            g_u8PvrFormatFsType = PVR_FS_LINUX_FAT; //set default to FAT32, must link with UI'ssetting
            #else
            g_u8PvrFormatFsType = PVR_FS_N51FAT32; //set default to N51FAT32, must link with UI'ssetting
            #endif
            g_u16FileSystemDiskSize_GB = 0; //restore to ALL
            MApp_ZUI_API_EnableWindow(HWND_PVR_FILE_SYSTEM_SIZE_ITEM, DISABLE);
            MApp_ZUI_API_InvalidateWindow(HWND_PVR_FILE_SYSTEM_SETTING_PANE);
            return TRUE;

        case EN_EXE_FILE_SYSTEM_SIZE_GOTO_PVR_BG_PANE:
            MApp_ZUI_ACT_PVR_GOTO_MAINMENU(MENU_PVR_CHECKFS_MAIN,PVR_CHECKFS_ITEM_CHECK_FORMAT);
            return TRUE;

    case EN_EXE_GOTO_PVR_TIME_SHIFT_SIZE_PANE:
            if(g_u16TimeShiftDiskSize_GB == 0)
            {
                g_u16TimeShiftDiskSize_GB = PVR_TIMESHIFT_SIZE_512M_NUM;
            }
            MApp_ZUI_API_ShowWindow(HWND_PVR_BG_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_FILE_SYS_PAGE_LIST, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_TIME_SHIFT_SIZE_PANE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_PVR_TIME_SHIFT_DISK_SIZE_ITEM);
            return TRUE;

        case EN_EXE_TIME_SHIFT_SIZE_GOTO_PVR_BG_PANE:
        #if 0   // Wrong UI flow contorl.
            MApp_ZUI_API_ShowWindow(HWND_PVR_TIME_SHIFT_SIZE_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_BG_PANE, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_FILE_SYS_PAGE_LIST, SW_SHOW);

            MApp_ZUI_API_SetFocus(HWND_PVR_TIME_SHIFT_ITEM);
            _MApp_ZUI_API_WindowProcOnIdle();

            MApp_UiPvr_CheckFS_FlowControl();
        #endif
            MApp_ZUI_ACT_PVR_GOTO_MAINMENU(MENU_PVR_CHECKFS_MAIN,PVR_CHECKFS_ITEM_CHECK_TIMESHIFT_SIZE);
            return TRUE;

        case EN_EXE_DEC_FILE_SYSTEM_SIZE:
        case EN_EXE_INC_FILE_SYSTEM_SIZE:
            g_u16FileSystemDiskSize_GB = MApp_ZUI_ACT_DecIncValue_Cycle(
                act==EN_EXE_INC_FILE_SYSTEM_SIZE,
                g_u16FileSystemDiskSize_GB, 0, (MApp_PVR_DiskGetAvailableSizeMB()/MEGA_PER_GIGA), 1);
            MApp_ZUI_API_InvalidateWindow(HWND_PVR_FILE_SYSTEM_SIZE_RESLUT);
            MApp_ZUI_API_InvalidateWindow(HWND_PVR_SD_HD_SIZE_ITEM);
            return TRUE;

        case EN_EXE_DEC_TIME_SHIFT_DISK_SIZE:
        case EN_EXE_INC_TIME_SHIFT_DISK_SIZE:
        #if (ENABLE_BULK_FILE_SYSTEM)
            //Move from Pluto MApp_UiMenuFunc_Adjfunction()  case MAPP_UIMENUFUNC_ADJ_PVR_CHECKFS_TMSHFT_SIZE:
            {
            if(EN_EXE_INC_TIME_SHIFT_DISK_SIZE == act)
            {
                if(g_u16TimeShiftDiskSize_GB < TIME_SHIFT_MAX_DISK_SIZE_GB)
                {
                    g_u16TimeShiftDiskSize_GB++;
                }
                else if(g_u16TimeShiftDiskSize_GB == TIME_SHIFT_MAX_DISK_SIZE_GB)
                {
                    g_u16TimeShiftDiskSize_GB = PVR_TIMESHIFT_SIZE_512M_NUM;
                }
                else if(g_u16TimeShiftDiskSize_GB == PVR_TIMESHIFT_SIZE_512M_NUM)
                {
                    g_u16TimeShiftDiskSize_GB = 1;
                }
            }
            else if(EN_EXE_DEC_TIME_SHIFT_DISK_SIZE == act)
            {
                if(g_u16TimeShiftDiskSize_GB >1 && g_u16TimeShiftDiskSize_GB <= TIME_SHIFT_MAX_DISK_SIZE_GB)
                {
                    g_u16TimeShiftDiskSize_GB--;
                }
                else if(g_u16TimeShiftDiskSize_GB == 1)
                {
                    g_u16TimeShiftDiskSize_GB = PVR_TIMESHIFT_SIZE_512M_NUM;
                }
                else if(g_u16TimeShiftDiskSize_GB == PVR_TIMESHIFT_SIZE_512M_NUM)
                {
                    g_u16TimeShiftDiskSize_GB = TIME_SHIFT_MAX_DISK_SIZE_GB;
                }
            }

            }

            if(g_u16TimeShiftDiskSize_GB == PVR_TIMESHIFT_SIZE_512M_NUM)
            {
                MApp_PVR_TimeShiftSetRecordLengthMB((U32)512);
            }
            else
            {
                MApp_PVR_TimeShiftSetRecordLengthMB(g_u16TimeShiftDiskSize_GB*MEGA_PER_GIGA);
            }




            MApp_ZUI_API_InvalidateWindow(HWND_PVR_TIME_SHIFT_DISK_SIZE_OPTION);
            MApp_ZUI_API_InvalidateWindow(HWND_PVR_TIME_SHIFT_SIZE_SD_HD_TIME_ITEM);
            //printf("g_u16TimeShiftDiskSize_GB=%u \n",g_u16TimeShiftDiskSize_GB);
        #endif
            return TRUE;

        case EN_EXE_FILE_SYSTEM_SIZE_START_FORMAT_CHECK:
            MApp_ZUI_ACT_PVR_CheckFS_PopUIPage(MENU_PVR_CHECKFS_FORMAT_DISK_CHECK_MSG);
            return TRUE;

        case EN_EXE_FILE_SYSTEM_SIZE_START_FORMAT:
        #if (ENABLE_BULK_FILE_SYSTEM)
            msAPI_PVRFS_SetTotalDiskSizeUsedMB((U32)g_u16FileSystemDiskSize_GB*(U32)MEGA_PER_GIGA);
        #endif
            MApp_UiPvr_CheckFS_Confirm_Formating();
            MApp_UiPvr_CheckFS_FlowControl();
            MApp_ZUI_API_ShowWindow(HWND_PVR_FORMAT_DISK_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_FORMAT_DISK_CHECK_PANE, SW_HIDE);
            if (g_u8PvrFormatFsType == PVR_FS_N51FAT32)
            {
                MApp_ZUI_API_ShowWindow(HWND_PVR_BG_PANE, SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_PVR_FILE_SYS_PAGE_LIST, SW_SHOW);
                MApp_ZUI_API_SetFocus(HWND_PVR_FORMAT_ITEM);
            }
            return TRUE;
        case EN_EXE_CHANGE_TO_CREATE_PVR_FILE_SYSTEM_PLEASE_WAIT_TXT:
            MApp_ZUI_API_ShowWindow(HWND_PVR_FORMATTING_PLEASE_WAIT_TXT, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_CREATE_PVR_FILE_SYSTEM_PLEASE_WAIT_TXT, SW_SHOW);
            _MApp_ZUI_API_WindowProcOnIdle();
            return TRUE;
        case EN_EXE_TIME_SHIFT_SIZE_FORMAT:
            MApp_ZUI_API_ShowWindow(HWND_PVR_TIME_SHIFT_SIZE_PANE, SW_HIDE);

            MApp_ZUI_API_ShowWindow(HWND_PVR_BG_PANE, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_FILE_SYS_PAGE_LIST, SW_SHOW);

            MApp_ZUI_API_SetFocus(HWND_PVR_FORMAT_ITEM);
            _MApp_ZUI_API_WindowProcOnIdle();
            if(g_u16TimeShiftDiskSize_GB == PVR_TIMESHIFT_SIZE_512M_NUM)
            {
                MApp_PVR_TimeShiftSetRecordLengthMB((U32)512);
            }
            else
            {
                MApp_PVR_TimeShiftSetRecordLengthMB(g_u16TimeShiftDiskSize_GB*MEGA_PER_GIGA);
            }
            MApp_UiPvr_CheckFS_FlowControl();
            return TRUE;
        case EN_EXE_REPAINT_PVR_FORMAT_PROGRESS:
            MApp_ZUI_API_InvalidateWindow(HWND_PVR_FORMAT_DISK_PROGRESSBAR);
            _MApp_ZUI_API_WindowProcOnIdle();
            return TRUE;

        case EN_EXE_DLG_CONFIRM_OK://close PVR and channel change
            MApp_UiPvr_RecordStop();
            _MApp_ChannelList_ChannelChange(PvrNewPos, PvrNewCMType, TRUE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);

            MApp_ZUI_ACT_ShutdownOSD();

            MApp_ZUI_ACT_Startup_ChannelInfo_OSD();
            MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_BRIEF_CH_INFO);
            MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_TV_BANNER);
            return TRUE;

        case EN_EXE_DLG_CONFIRM_CANCEL:
            if(g_PvrMenuPageType == MENU_PVR_NONE)
            {
                MApp_ZUI_ACT_ExecutePvrAction(EN_EXE_CLOSE_CURRENT_OSD);
            }
            else
            {
                MApp_ZUI_API_ShowWindow(HWND_PVR_WARNING_DLG_PANE, SW_HIDE);
                MApp_ZUI_API_KillTimer(HWND_PVR_WARNING_DLG_PANE, 0);

                if(MApp_ZUI_API_IsWindowVisible(HWND_PVR_TIMESHIFT_OP_ICONS_PANE))
                {
                    _MApp_ZUI_ACT_PVR_SetFocus(HWND_PVR_TIMESHIFT_OP_ICONS_PANE);
                }
                else if(MApp_ZUI_API_IsWindowVisible(HWND_PVR_PLAY_OP_ICONS_PANE))
                {
                    _MApp_ZUI_ACT_PVR_SetFocus(HWND_PVR_PLAY_OP_ICONS_PANE);
                }
                else if(MApp_ZUI_API_IsWindowVisible(HWND_PVR_RECORDING_OP_ICONS_PANE))
                {
                    _MApp_ZUI_ACT_PVR_SetFocus(HWND_PVR_RECORDING_OP_ICONS_PANE);
                }
            }
            return TRUE;

        case EN_EXE_PVR_VIRTUAL_KEY:
            if((MApp_ZUI_API_GetFocus() == HWND_PVR_TIMESHIFT_ICON_STOP)||MApp_ZUI_API_GetFocus()==HWND_PVR_RECORDING_ICON_STOP)
            {
                g_PVR_PopUpWarning =E_PVR_WARNING_REC_PROCESSING;
                MApp_ZUI_ACT_GetPvrDynamicText(HWND_PVR_WARNING_MESSAGE_MID_TXT);
                MApp_ZUI_API_ShowWindow(HWND_PVR_WARNING_MESSAGE_PANE, SW_SHOW);
                MApp_ZUI_API_SetTimer(HWND_PVR_WARNING_MESSAGE_PANE, 0, 2000);
            }
            MApp_UiPvr_VirtualKeyProcessor(MApp_ZUI_API_GetFocus());
            return TRUE;

#if ENABLE_PVR
        case EN_EXE_DEC_FILE_SYSTEM_TYPE:
        case EN_EXE_INC_FILE_SYSTEM_TYPE:
            if(g_u8PvrFormatFsType == PVR_FS_BULKFS)
            {
                #ifdef OBAMA
                g_u8PvrFormatFsType = PVR_FS_LINUX_FAT;
                #else
                g_u8PvrFormatFsType = PVR_FS_N51FAT32;
                #endif
                g_u16FileSystemDiskSize_GB = 0; //restore to ALL
                MApp_ZUI_API_EnableWindow(HWND_PVR_FILE_SYSTEM_SIZE_ITEM, DISABLE);

            }
            else
            {
                #ifndef OBAMA
                g_u8PvrFormatFsType = PVR_FS_BULKFS;
                #else
                //add inc/dec value here.
                #endif
                MApp_ZUI_API_EnableWindow(HWND_PVR_FILE_SYSTEM_SIZE_ITEM, ENABLE);


            }

            MApp_ZUI_API_InvalidateWindow(HWND_PVR_FILE_SYSTEM_SETTING_PANE);
            return TRUE;
#endif
    }
    return FALSE;
}

S16 MApp_ZUI_ACT_GetPvrDynamicValue(HWND hwnd)
{
    switch(hwnd)
    {
        case HWND_PVR_TIMESHIFT_PERCENTAGE_BAR:
            return (S16)MApp_UiPvr_TimeShiftGetPlaybackPercentage();
        case HWND_PVR_PLAY_PERCENTAGE_BAR:
            return (S16)MApp_UiPvr_PlaybackGetPlaybackPercentage();
        case HWND_PVR_FORMAT_DISK_PROGRESSBAR:
        {
            if(g_PVRCheckFSStatus == EN_PVR_CHKSTS_FORMAT_PROGRESS)
            {
                return (S16)MApp_PVR_DiskFormatGetPercentage();
            }
        #if (ENABLE_BULK_FILE_SYSTEM)
            else if(g_PVRCheckFSStatus == EN_PVR_CHKSTS_CREATE_FILE_SYSTEM_PROGRESS)
            {
                return (S16)MApp_PVR_DiskFormatGetCreateFilePercentage();
            }
        #endif
            else
            {
                return 0;
            }
        }
        case HWND_PVR_SPEED_CHECK_SPEED_PERCENTAGE_BAR:
            //Move From  Pluto MApp_UiMenuFunc_GetU16DynamicNumber() case EN_DNUM_PVR_CHECKFS_CHECK_SPEED_PERCENTAGE:
        {
            if(g_PVRCheckFSStatus >= EN_PVR_CHKSTS_CHECK_SPEED_PASS)
            {
                U32 speed = (U32)MApp_PVR_DiskGetSpeed();
                if(speed > PVR_CHECKFS_MAX_SPEED)
                {
                    return 100;
                }
                else
                {
                    return (S16)(speed*100/PVR_CHECKFS_MAX_SPEED);
                }
            }
            else
                return 0;
        }
         default:
            break;
    }
    return 0; //for empty  data
}

S16 MApp_ZUI_ACT_GetPvrDynamicValue_2(HWND hwnd)
{
    switch(hwnd)
    {
        case HWND_PVR_TIMESHIFT_PERCENTAGE_BAR:
            return (S16)MApp_UiPvr_TimeShiftGetRecordPercentage();
        default:
            return 100;   //background rect fill the whole line
    }
}

LPTSTR MApp_ZUI_ACT_GetPvrDynamicText(HWND hwnd)
{
    U16 u16TempID = Empty;
    switch(hwnd)
    {
        case HWND_PVR_SELECT_DISK_OPTION:
            if(g_u8PVRActiveDisk >= DISK_DRIVE_NUM)
            {
                return 0;
            }

            CHAR_BUFFER[0] = g_u8PVRActiveDisk + CHAR_C;
            CHAR_BUFFER[1] = CHAR_COLON;
            CHAR_BUFFER[2] = 0;
            return (LPTSTR)CHAR_BUFFER;
            break;

        case  HWND_PVR_CHECK_FILE_SYS_OPTION:
            switch(g_PVRCheckFSStatus)
            {
                case EN_PVR_CHKSTS_OK:
                    u16TempID = en_str_SUCCESS;
                    break;

                case EN_PVR_CHKSTS_CHECK_USB:
                case EN_PVR_CHKSTS_CHECK_DISK:
                case EN_PVR_CHKSTS_CHECK_FORMAT:
            #if (ENABLE_BULK_FILE_SYSTEM)
                case EN_PVR_CHKSTS_CHECK_BULK:
            #endif
                case EN_PVR_CHKSTS_CHECK_FORMAT_PASS:
                case EN_PVR_CHKSTS_FORMAT_PROGRESS:
            #if (ENABLE_BULK_FILE_SYSTEM)
                case EN_PVR_CHKSTS_CREATE_FILE_SYSTEM_PROGRESS:
            #endif
                case EN_PVR_CHKSTS_CHECK_TMSHFT_SIZE:
                case EN_PVR_CHKSTS_CHECK_SPEED_START:
                case EN_PVR_CHKSTS_CHECK_SPEED_PASS:
                case EN_PVR_CHKSTS_CREATE_FILE_SYSTEM_PASS:
                    u16TempID = en_str_Checking;
                    break;

                case EN_PVR_CHKSTS_USB_NOT_CONNECT:
                case EN_PVR_CHKSTS_NO_PARTITION:
                case EN_PVR_CHKSTS_CHECK_SIZE_FAIL:
                case EN_PVR_CHKSTS_FORMAT_ERROR:
                case EN_PVR_CHKSTS_CREATE_FOLDER_ERROR:
                case EN_PVR_CHKSTS_CREATE_INDEX_ERROR:
                    u16TempID = en_str_Fail;
                    break;

                case EN_PVR_CHKSTS_INITIAL:
                    u16TempID = en_str_Start;
                    break;

                default:
                    return 0;
            }
            break;

        case HWND_PVR_USB_DISK_OPTION:
            switch(g_PVRCheckFSStatus)
            {
                case EN_PVR_CHKSTS_CHECK_USB:
                    u16TempID = en_str_Checking;
                    break;

                case EN_PVR_CHKSTS_USB_NOT_CONNECT:
                    u16TempID = en_str_No_USB_Disk;
                    break;

                case EN_PVR_CHKSTS_NO_PARTITION:
                    u16TempID = en_str_No_Partition_Found;
                    break;

                case EN_PVR_CHKSTS_CHECK_SIZE_FAIL:
                    u16TempID = en_str_Disk_Size_too_small;
                    break;

                case EN_PVR_CHKSTS_INITIAL:
                    return 0;

                default:
                    if(g_PVRCheckFSStatus >= EN_PVR_CHKSTS_CHECK_FORMAT)
                    {
                        u16TempID = en_str_Pass;
                    }
                    else
                    {
                        return 0;
                    }
                    break;
            }
            break;

        case HWND_PVR_FORMAT_OPTION:
            switch(g_PVRCheckFSStatus)
            {
                case EN_PVR_CHKSTS_CHECK_FORMAT:
                    u16TempID = en_str_Checking_Format3dot;
                    break;
#if (ENABLE_BULK_FILE_SYSTEM)
                case EN_PVR_CHKSTS_CHECK_BULK:
                {
                    U16 curStringLen = 0;
                    U8 digit;
                    U8 checkBulkPercent = MApp_UiPvr_CheckFS_GetCheckBulkPercent();
                    MApp_ZUI_API_Strcpy(&CHAR_BUFFER[0], MApp_ZUI_API_GetString(en_str_Checking_Format3dot));
                    curStringLen = MApp_ZUI_API_Strlen(CHAR_BUFFER);
                    CHAR_BUFFER[curStringLen] = CHAR_SPACE;
                    curStringLen +=1;
                    digit = MApp_GetNoOfDigit(checkBulkPercent);
                    __MApp_UlongToString(checkBulkPercent, (CHAR_BUFFER+curStringLen), digit);
                    curStringLen +=digit;
                    CHAR_BUFFER[curStringLen] = CHAR_PERCENT;
                    curStringLen +=1;
                    CHAR_BUFFER[curStringLen] = 0;
                    return (LPTSTR) CHAR_BUFFER;
                }
                    break;
#endif
                case EN_PVR_CHKSTS_FORMAT_ERROR:
                    u16TempID = en_str_Fail;
                    break;

                case EN_PVR_CHKSTS_CREATE_FOLDER_ERROR:
                    u16TempID = en_str_Create_Folder_Error;
                    break;

                case EN_PVR_CHKSTS_CREATE_INDEX_ERROR:
                    u16TempID = en_str_Create_Index_Error;
                    break;

                case EN_PVR_CHKSTS_CREATE_FILE_SYSTEM_PASS:
                    u16TempID = en_str_Pass;
                    break;

                default:
                    if(g_PVRCheckFSStatus >= EN_PVR_CHKSTS_CHECK_TMSHFT_SIZE)
                    {
                        u16TempID = en_str_Pass;
                    }
                    else
                    {
                        return 0;
                    }
                    break;
            }
            break;

        case HWND_PVR_TIME_SHIFT_OPTION:
        {
            U16 TimeShiftSize_GB;
            U16 TimeShiftSize_MB;
            U8 digit_TimeShiftDiskSize;

            if(g_PVRCheckFSStatus >= EN_PVR_CHKSTS_CHECK_TMSHFT_SIZE)
            {
                TimeShiftSize_GB = MApp_PVR_TimeShiftGetRecordLengthMB()/1024;
                if(TimeShiftSize_GB > 0)
                {
                    digit_TimeShiftDiskSize = MApp_GetNoOfDigit(TimeShiftSize_GB);

                    __MApp_UlongToString(TimeShiftSize_GB, CHAR_BUFFER4, digit_TimeShiftDiskSize);
                    CHAR_BUFFER4[digit_TimeShiftDiskSize] = CHAR_SPACE;
                    MApp_ZUI_API_Strcpy(CHAR_BUFFER4+digit_TimeShiftDiskSize+1, MApp_ZUI_API_GetString(en_str_GB));
                    return (LPTSTR) CHAR_BUFFER4;
                }
                else
                {
                    TimeShiftSize_MB = MApp_PVR_TimeShiftGetRecordLengthMB();
                    digit_TimeShiftDiskSize = MApp_GetNoOfDigit(TimeShiftSize_MB);

                    __MApp_UlongToString(TimeShiftSize_MB, CHAR_BUFFER4, digit_TimeShiftDiskSize);
                    CHAR_BUFFER4[digit_TimeShiftDiskSize] = CHAR_SPACE;
                    MApp_ZUI_API_Strcpy(CHAR_BUFFER4+digit_TimeShiftDiskSize+1, MApp_ZUI_API_GetString(en_str_MB));
                    return (LPTSTR) CHAR_BUFFER4;
                }
            }
            else
            {
                return 0;
            }
        }
            break;

        case HWND_PVR_SPEED_OPTION:
        {
            if(g_PVRCheckFSStatus >= EN_PVR_CHKSTS_CHECK_SPEED_PASS)
            {
                U16 speed = MApp_PVR_DiskGetSpeed();
                U8 digit_Speed = MApp_GetNoOfDigit(speed);
                U16 u16StrBuf[32];
                __MApp_UlongToString(speed, u16StrBuf, digit_Speed);
                u16StrBuf[digit_Speed] = CHAR_SPACE;
                MApp_ZUI_API_Strcpy(u16StrBuf+digit_Speed+1, MApp_ZUI_API_GetString(en_str_KBslashs));
                MApp_ZUI_API_Strcpy(CHAR_BUFFER, u16StrBuf);

                return (LPTSTR) CHAR_BUFFER;
            }
            else if(g_PVRCheckFSStatus == EN_PVR_CHKSTS_CHECK_SPEED_START)
            {
                u16TempID = en_str_Checking;
            }
            else
            {
                return 0;
            }
        }
            break;

        case HWND_PVR_SPEED_CHECK_SPEED_TAG_OPTION:
        {  //case PVR_CHECKFS_CHECK_SPEED_TAG:
        if(g_PVRCheckFSStatus >= EN_PVR_CHKSTS_CHECK_SPEED_PASS)
        {
            U16 speed = MApp_PVR_DiskGetSpeed();
            U16 curStringLen = 0;

            if(speed >= PVR_CHECKFS_FULLHD_SPEED)
            {
                //"Full HD Support"
                CHAR_BUFFER3[curStringLen++] = CHAR_F;
                CHAR_BUFFER3[curStringLen++] = CHAR_u;
                CHAR_BUFFER3[curStringLen++] = CHAR_l;
                CHAR_BUFFER3[curStringLen++] = CHAR_l;
                CHAR_BUFFER3[curStringLen++] = CHAR_SPACE;
                CHAR_BUFFER3[curStringLen++] = CHAR_H;
                CHAR_BUFFER3[curStringLen++] = CHAR_D;
                CHAR_BUFFER3[curStringLen++] = CHAR_SPACE;
                MApp_ZUI_API_Strcpy(CHAR_BUFFER3 + curStringLen, MApp_ZUI_API_GetString(en_str_support));
            }
            else if(speed >= PVR_CHECKFS_HD_SPEED)
            {
                //"HD Support"
                CHAR_BUFFER3[curStringLen++] = CHAR_H;
                CHAR_BUFFER3[curStringLen++] = CHAR_D;
                CHAR_BUFFER3[curStringLen++] = CHAR_SPACE;
                MApp_ZUI_API_Strcpy(CHAR_BUFFER3 + curStringLen, MApp_ZUI_API_GetString(en_str_support));
            }
            else if(speed >= PVR_CHECKFS_SD_SPEED)
            {
                //"SD Support"
                CHAR_BUFFER3[curStringLen++] = CHAR_S;
                CHAR_BUFFER3[curStringLen++] = CHAR_D;
                CHAR_BUFFER3[curStringLen++] = CHAR_SPACE;
                MApp_ZUI_API_Strcpy(CHAR_BUFFER3 + curStringLen, MApp_ZUI_API_GetString(en_str_support));
            }
            else
            {
                //"SD FAIL"
                CHAR_BUFFER3[curStringLen++] = CHAR_S;
                CHAR_BUFFER3[curStringLen++] = CHAR_D;
                CHAR_BUFFER3[curStringLen++] = CHAR_SPACE;
                MApp_ZUI_API_Strcpy(CHAR_BUFFER3 + curStringLen, MApp_ZUI_API_GetString(en_str_Fail));
            }
            return (LPTSTR) CHAR_BUFFER3;
            }
        else
            return 0;
        }
              break;

        case HWND_PVR_SELECT_DISK_USB_OPTION:
            {
                U8 u8DeviceStatus = MApp_MassStorage_DeviceConnectionDetect();
                if((u8DeviceStatus & MS_USB_CONNECTED) && (g_u8PVRActiveDevice == MSD_USB_INDEX_START))
                {
                    __MApp_UlongToString(MSD_USB_INDEX_START, CHAR_BUFFER, 1);
                }
                else if((u8DeviceStatus & MS_USB2_CONNECTED) && (g_u8PVRActiveDevice == MSD_USB_2_INDEX_START))
                {
                    __MApp_UlongToString(1, CHAR_BUFFER, 1);
                }
                else //auto detect connected USB
                {
                    if (u8DeviceStatus & MS_USB_CONNECTED)
                    {
                        g_u8PVRActiveDevice = MSD_USB_INDEX_START;
                        g_u8PVRActiveDisk = MApp_MassStorage_GetFirstDriveByPort(MSD_PORT_1);
                        __MApp_UlongToString(MSD_USB_INDEX_START, CHAR_BUFFER, 1);
                    }
                    else if (u8DeviceStatus & MS_USB2_CONNECTED)
                    {
                        g_u8PVRActiveDevice = MSD_USB_2_INDEX_START;
                        g_u8PVRActiveDisk = MApp_MassStorage_GetFirstDriveByPort(MSD_PORT_2);
                        __MApp_UlongToString(1, CHAR_BUFFER, 1);
                    }
                    else
                    {
                        g_u8PVRActiveDevice = MSD_USB_INDEX_START;
                        g_u8PVRActiveDisk = 0;
                        __MApp_UlongToString(MSD_USB_INDEX_START, CHAR_BUFFER, 1);
                    }

                }

                CHAR_BUFFER[1] = 0;
                return (LPTSTR) CHAR_BUFFER;
            }
            break;

        case HWND_PVR_SELECT_DISK_DISK_OPTION:
            MApp_MassStorage_DeviceChangeStatusCheck();
            MApp_MassStorage_DeviceStatusCheck();
            if(g_u8PVRActiveDisk >= DISK_DRIVE_NUM)
            {
                return 0;
            }

            CHAR_BUFFER[0] = g_u8PVRActiveDisk + CHAR_C;
            CHAR_BUFFER[1] = CHAR_COLON;
            CHAR_BUFFER[2] = 0;
            return (LPTSTR) CHAR_BUFFER;
            break;

        case HWND_PVR_FILE_SYSTEM_SIZE_RESLUT:

            if(g_u16FileSystemDiskSize_GB == 0)
            {
                snprintf((char*)CHAR_BUFFER, 4, "All");
            }
            else
            {
                snprintf((char*)CHAR_BUFFER, 6, "%u GB", g_u16FileSystemDiskSize_GB);
            }
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
            return CHAR_BUFFER;

        case HWND_PVR_FILE_SYSTEM_SETTING_TYPE_OPTION:
            if (g_u8PvrFormatFsType == PVR_FS_BULKFS)
                u16TempID = en_str_Hi_Speed_FS;
            else
                u16TempID = en_str_FAT32;
            break;

        case HWND_PVR_SD_TIME_TXT:
            {
            U16 fileSystemTime_Mins;
            //SD XXX mins
            if(g_u16FileSystemDiskSize_GB == 0)
            {
                fileSystemTime_Mins = MApp_PVR_DiskGetAvailableSizeMB()* TIME_SHIFT_SIZE_TO_TIME_RATIO_SD/MEGA_PER_GIGA;
            }
            else
            {
                fileSystemTime_Mins = g_u16FileSystemDiskSize_GB* TIME_SHIFT_SIZE_TO_TIME_RATIO_SD;
            }
            snprintf((char*)CHAR_BUFFER, 12, "SD %u Mins", fileSystemTime_Mins);
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
            return CHAR_BUFFER;
            }
        case HWND_PVR_HD_TIME_TXT:
            {
            U16 fileSystemTime_Mins;
            //HD XXX mins
            if(g_u16FileSystemDiskSize_GB == 0)
            {
                fileSystemTime_Mins = MApp_PVR_DiskGetAvailableSizeMB() * TIME_SHIFT_SIZE_TO_TIME_RATIO_HD/MEGA_PER_GIGA;
            }
            else
            {
                fileSystemTime_Mins = g_u16FileSystemDiskSize_GB * TIME_SHIFT_SIZE_TO_TIME_RATIO_HD;
            }
            snprintf((char*)CHAR_BUFFER, 12, "HD %u Mins", fileSystemTime_Mins);
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
            return CHAR_BUFFER;
            }
        case HWND_PVR_TIME_SHIFT_DISK_SIZE_OPTION:
            if(g_u16TimeShiftDiskSize_GB == PVR_TIMESHIFT_SIZE_512M_NUM)
            {
                snprintf((char*)CHAR_BUFFER, 6, "512 MB" );
            }
            else
            {
                snprintf((char*)CHAR_BUFFER, 6, "%u GB", g_u16TimeShiftDiskSize_GB);
            }
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
            return CHAR_BUFFER;
        case HWND_PVR_TIME_SHIFT_SIZE_SD_TIME_TXT:
        #if (ENABLE_BULK_FILE_SYSTEM)
            {
            U16 timeShiftTime_Mins;

            //SD XXX mins
            if(g_u16TimeShiftDiskSize_GB == PVR_TIMESHIFT_SIZE_512M_NUM)
            {
                timeShiftTime_Mins = TIME_SHIFT_SIZE_TO_TIME_RATIO_SD/2;
            }
            else
            {
                timeShiftTime_Mins = g_u16TimeShiftDiskSize_GB* TIME_SHIFT_SIZE_TO_TIME_RATIO_SD;
            }
            snprintf((char*)CHAR_BUFFER, 12, "SD %u Mins", timeShiftTime_Mins);
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
            return CHAR_BUFFER;
            }
        #else
            break;
        #endif

        case HWND_PVR_TIME_SHIFT_SIZE_HD_TIME_TXT:
        #if (ENABLE_BULK_FILE_SYSTEM)
            {
            U16 timeShiftTime_Mins;

            //HD XXX mins
            if(g_u16TimeShiftDiskSize_GB == PVR_TIMESHIFT_SIZE_512M_NUM)
            {
                timeShiftTime_Mins = TIME_SHIFT_SIZE_TO_TIME_RATIO_HD/2;
            }
            else
            {
                timeShiftTime_Mins = g_u16TimeShiftDiskSize_GB * TIME_SHIFT_SIZE_TO_TIME_RATIO_HD;
            }
            snprintf((char*)CHAR_BUFFER, 12, "HD %u Mins", timeShiftTime_Mins);
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
            return CHAR_BUFFER;
            }
        #else
            break;
        #endif

        case HWND_PVR_WARNING_MESSAGE_UP_TXT:
        {
            switch(g_PVR_PopUpWarning)
            {
                case E_PVR_WARNING_PLAY_NO_DEVICE:
                case E_PVR_WARNING_REC_NO_DEVICE:
                    u16TempID = en_str_Warning_No_Devic_Connection;
                    break;
                case E_PVR_WARNING_REC_URI_BLOCK:
                    u16TempID = en_str_URI_protect_block_PVR_function;
                    break;
                case E_PVR_WARNING_REC_NO_SIGNAL:
                    u16TempID = en_str_Warning_No_Signal;
                    break;
                case E_PVR_WARNING_REC_NO_DISK_SPACE:
                case E_PVR_WARNING_TIMESHIFT_NO_DISK_SPACE:
                    u16TempID = en_str_Warning_No_Disk_Space;
                    break;
                case E_PVR_WARNING_PLAY_LOW_DISK_SPEED:
                case E_PVR_WARNING_REC_LOW_DISK_SPEED:
                    u16TempID = en_str_Warning_Disk_Speed_too_Low;
                    break;
                case E_PVR_WARNING_REC_SCRAMBLE:
                    u16TempID = en_str_Warning_Scrambled_Channel;
                    break;

                default:
                    break;
            }
        }
            break;

        case HWND_PVR_WARNING_MESSAGE_MID_TXT:
        {
            switch(g_PVR_PopUpWarning)
            {
                case E_PVR_WARNING_USB_NOT_READY:
                    u16TempID = en_str_Disk_not_readydot;
                    break;
                case E_PVR_WARNING_DISK_FORMAT_ERROR:
                    u16TempID = en_str_Require_formatting_disk;
                    break;
                case E_PVR_WARNING_DISK_FORMAT_VERSION_CHANGED:
                    u16TempID = en_str_Format_version_changed;
                    break;
                case E_PVR_WARNING_CLOCK_NOT_SET:
                    u16TempID = en_str_Clock_Not_Set;
                    break;
                case E_PVR_WARNING_REC_PROCESSING:
                    u16TempID = en_str_Processing;
                    break;
                case E_PVR_WARNING_EPG_RECORDER_REC_PREPARING:
                    u16TempID = en_str_Preparing_Record;
                    break;
                case E_PVR_WARNING_PVR_FILE_READ_ERROR:
                    u16TempID = en_str_PVR_File_Error;
                    break;
                case E_PVR_WARNING_PVR_PLAYBACK_CANTSUPPORT:
                    u16TempID = en_str_PVR_Playback_Cant_Support;
                    break;
                case E_PVR_WARNING_PVR_RECORD_CANTSUPPORT:
                    u16TempID = en_str_This_Service_Cant_Support_Record;
                    break;
                case E_PVR_WARNING_PVR_TIMESHIFT_CANTSUPPORT:
                    u16TempID = en_str_PVR_TimeShift_Cant_Support;
                    break;
                default:
                    break;
            }
        }
            break;

        case HWND_PVR_WARNING_MESSAGE_DOWN_TXT:
        {
            switch(g_PVR_PopUpWarning)
            {
                case E_PVR_WARNING_PLAY_NO_DEVICE:
                case E_PVR_WARNING_PLAY_LOW_DISK_SPEED:
                    u16TempID = en_str_Stop_Playing;
                    break;
                case E_PVR_WARNING_REC_NO_DEVICE:
                case E_PVR_WARNING_REC_NO_SIGNAL:
                case E_PVR_WARNING_REC_NO_DISK_SPACE:
                case E_PVR_WARNING_REC_LOW_DISK_SPEED:
                case E_PVR_WARNING_REC_SCRAMBLE:
                    u16TempID = en_str_Stop_Recording;

                default:
                    break;
            }
        }
            break;

        case HWND_PVR_RECORDING_SYSTEM_CLOCK:
        case HWND_PVR_TIMESHIFT_SYSTEM_CLOCK:
        case HWND_PVR_PLAY_SYSTEM_CLOCK:
        {
            LPTSTR str = CHAR_BUFFER;
            str = _MApp_ZUI_ACT_GetLocalClockTimeString(str);
            *str = 0;

            return CHAR_BUFFER;
        }

#ifndef PVR_UTOPIA
        case HWND_PVR_RECORDING_TIME_BRIEF:
#endif
        case HWND_PVR_RECORDING_RECORD_TIME_TEXT:
        {
            ST_TIME _stTime;
            U32 period = MApp_Record_GetEndTimeSec(RECORD_PATH_DEFAULT) - MApp_Record_GetStartTimeSec(RECORD_PATH_DEFAULT);
            MApp_ConvertSeconds2StTime(period, &_stTime);

            CHAR_BUFFER[0] = CHAR_LEFT_BRACKET;
            __MApp_UlongToString((U16)_stTime.u8Hour, (CHAR_BUFFER+1), 2);
            CHAR_BUFFER[3] = CHAR_COLON;
            __MApp_UlongToString((U16)_stTime.u8Min, (CHAR_BUFFER+4), 2);
            CHAR_BUFFER[6] = CHAR_COLON;
            __MApp_UlongToString((U16)_stTime.u8Sec, (CHAR_BUFFER+7), 2);
            CHAR_BUFFER[9] = CHAR_RIGHT_BRACKET;
            CHAR_BUFFER[10] = 0;

            return CHAR_BUFFER;
        }

        case HWND_PVR_RECORDING_CHANNEL_NUMBER:
        {/*
             if (g_u16RecordingLCN != INVALID_LOGICAL_CHANNEL_NUMBER)
            {
                return MApp_ZUI_API_GetU16String(g_u16RecordingLCN);
            }
            else
            {
                return 0;
            }
            */
            return 0;
        }

        case HWND_PVR_RECORDING_CHANNEL_NAME:
        {
        #if(ENABLE_PVR_BROWSER)
            if(E_PVR_RET_OK == MApp_PvrBrowser_GetRecordingAttribute(E_PVR_ATTR_CHANNEL_NAME, (BYTE*)CHAR_BUFFER, UI_PVR_PROGRAM_NAME_MAX_UNICODE_LEN*2))
            {
                return CHAR_BUFFER;
            }
            else
        #endif
            {
                return 0;
            }

        }

        case HWND_PVR_RECORDING_EVENT_NAME:
        {
        #if(ENABLE_PVR_BROWSER)
            if(E_PVR_RET_OK == MApp_PvrBrowser_GetRecordingAttribute(E_PVR_ATTR_PROGRAM_NAME, (BYTE*)CHAR_BUFFER, UI_PVR_PROGRAM_NAME_MAX_UNICODE_LEN*2))
            {
                return CHAR_BUFFER;
            }
            else
        #endif
            {
                return 0;
            }
        }

        case HWND_PVR_RECORDING_DISK_REMAIN:
        {
            U8 strLen = 0;
            U32 diskSpace = msAPI_PVRFS_GetDriveFreeSpaceMB()+((U32)(BULK_SIZE/BYTES_PER_MEGA)); //to include current bulk file
            U16 consumeRate = MApp_Record_GetAvgRecordRateKB(RECORD_PATH_DEFAULT);  //to do:: change parameter u8PathNum
            U32 remainSec = 0;
            static U32 prvRemainSec = 0;

            if(diskSpace > 0 && consumeRate > 0)
            {
                static U32 prvDiskSpace = 0;
                static U32 prvRecordingTime = 0;

                if(prvDiskSpace != diskSpace)
                {
                    remainSec = (diskSpace * 1000)/consumeRate;
                    prvRemainSec = remainSec;
                    prvRecordingTime = MApp_Record_GetEndTimeSec(RECORD_PATH_DEFAULT);

                    prvDiskSpace = diskSpace;
                }
                else
                {
                    remainSec = prvRemainSec - (MApp_Record_GetEndTimeSec(RECORD_PATH_DEFAULT) - prvRecordingTime);
                    if(remainSec < 60)
                    {
                        if (remainSec > prvRemainSec)
                        {
                            remainSec = 0; //overflow
                        }
                    }
                }

                CHAR_BUFFER[strLen++] = CHAR_LEFT_QUOTE;
                MApp_UlongToU16String(remainSec/SECONDS_PER_HOUR, &CHAR_BUFFER[strLen], 4 );
                strLen += 4;
                CHAR_BUFFER[strLen++] = ':';
                MApp_UlongToU16String((remainSec%SECONDS_PER_HOUR)/SECONDS_PER_MIN, &CHAR_BUFFER[strLen], 2 );
                strLen += 2;
                CHAR_BUFFER[strLen++] = ':';
                MApp_UlongToU16String(remainSec%SECONDS_PER_MIN, &CHAR_BUFFER[strLen], 2 );
                strLen += 2;
                CHAR_BUFFER[strLen++] = CHAR_RIGHT_QUOTE;
                CHAR_BUFFER[strLen] = 0;
            }
            else
            {
                CHAR_BUFFER[0] =0;
            }
            return CHAR_BUFFER;
        }

        case HWND_PVR_TIMESHIFT_PLAYBACK_TIME_TXT:
        {
            ST_TIME _stTime;
            static U32 u32record_playtime_period = 0;
            U32 recordTime = MApp_TimeShift_GetRecordEndTimeSec();
            U32 playTime = MApp_TimeShift_GetPlaybackTimeSec();
            U32 u32ValidPeriod = MApp_TimeShift_GetRecordValidPeriodSec();

            static U32 u32LastDisplayTime = 0;

            if(recordTime  != 0  && recordTime >= g_u32TimeShiftStartRecordingTime_Sec)
            {
                u32record_playtime_period = (recordTime-g_u32TimeShiftStartRecordingTime_Sec)-playTime;

                switch(MApp_TimeShift_Playback_StateMachineGet())
                {
                    case E_TIMESHIFT_PLAYBACK_STATE_RUNNING:
                        if (u32record_playtime_period <= UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC)
                            u32record_playtime_period = 0;
                        else if (u32record_playtime_period != u32LastDisplayTime)
                        {
                            PVR_TIMESHIFT_PLAYBACK_TIME_DBG(printf("case RUNNING wrong, LastDisplay=%d, u32record_plyatime=%d to be update\n", u32LastDisplayTime, u32record_playtime_period));
                            u32record_playtime_period = u32LastDisplayTime;
                        }

                        break;
                    case E_TIMESHIFT_PLAYBACK_STATE_FASTFORWARD:
                        if (u32record_playtime_period >= u32LastDisplayTime)
                        {
                            PVR_TIMESHIFT_PLAYBACK_TIME_DBG(printf("case FastFowrad wrong, LastDisplay=%d, u32record_plyatime=%d to be update\n", u32LastDisplayTime, u32record_playtime_period));
                            u32record_playtime_period = u32LastDisplayTime;
                        }
                        break;
                    case E_TIMESHIFT_PLAYBACK_STATE_FASTBACKWARD:
                        if (u32record_playtime_period <= u32LastDisplayTime)
                        {
                            PVR_TIMESHIFT_PLAYBACK_TIME_DBG(printf("case FastBackward wrong, LastDisplay=%d, u32record_plyatime=%d to be update\n", u32LastDisplayTime, u32record_playtime_period));
                            u32record_playtime_period = u32LastDisplayTime;
                        }
                        break;
                    default:
                        PVR_TIMESHIFT_PLAYBACK_TIME_DBG(printf("Files=%s, line=%d, MApp_TimeShift_Playback_StateMachineGet() State=%d\n",__FUNCTION__,__LINE__,MApp_TimeShift_Playback_StateMachineGet()));
                        PVR_TIMESHIFT_PLAYBACK_TIME_DBG(printf("LastDisplay=%d, u32record_plyatime=%d\n", u32LastDisplayTime, u32record_playtime_period));
                }

                u32LastDisplayTime = u32record_playtime_period;
                if(u32record_playtime_period>u32ValidPeriod)
                {
                    u32record_playtime_period=u32ValidPeriod;
                }

                MApp_ConvertSeconds2StTime(u32record_playtime_period, &_stTime);
            }
            else
            {
                return 0;
            }

            CHAR_BUFFER[0] = CHAR_LEFT_BRACKET;
            CHAR_BUFFER[1] = CHAR_MINUS;
            __MApp_UlongToString((U16)_stTime.u8Hour, (CHAR_BUFFER+2), 2);
            CHAR_BUFFER[4] = CHAR_COLON;
            __MApp_UlongToString((U16)_stTime.u8Min, (CHAR_BUFFER+5), 2);
            CHAR_BUFFER[7] = CHAR_COLON;
            __MApp_UlongToString((U16)_stTime.u8Sec, (CHAR_BUFFER+8), 2);
            CHAR_BUFFER[10] = CHAR_SLASH;

            if(u32ValidPeriod > 0 && u32ValidPeriod < 0xffff)
            {
                MApp_ConvertSeconds2StTime(u32ValidPeriod, &_stTime);
                __MApp_UlongToString((U16)_stTime.u8Hour, (CHAR_BUFFER+11), 2);
                CHAR_BUFFER[13] = CHAR_COLON;
                __MApp_UlongToString((U16)_stTime.u8Min, (CHAR_BUFFER+14), 2);
                CHAR_BUFFER[16] = CHAR_COLON;
                __MApp_UlongToString((U16)_stTime.u8Sec, (CHAR_BUFFER+17), 2);
                CHAR_BUFFER[19] = CHAR_RIGHT_BRACKET;
            }
            else
            {
                CHAR_BUFFER[11] = CHAR_0;
                CHAR_BUFFER[12] = CHAR_0;
                CHAR_BUFFER[13] = CHAR_COLON;
                CHAR_BUFFER[14] = CHAR_0;
                CHAR_BUFFER[15] = CHAR_0;
                CHAR_BUFFER[16] = CHAR_COLON;
                CHAR_BUFFER[17] = CHAR_0;
                CHAR_BUFFER[18] = CHAR_0;
                CHAR_BUFFER[19] = CHAR_RIGHT_BRACKET;
            }
            CHAR_BUFFER[20] = 0;
            return CHAR_BUFFER;
        }

#ifndef   PVR_UTOPIA
        case HWND_PVR_TIMESHIFT_PLAYBACK_TIME_BRIEF_TXT:
        {
            ST_TIME _stTime;
            U32 recordTime = MApp_TimeShift_GetRecordEndTimeSec();
            U32 playTime = MApp_TimeShift_GetPlaybackTimeSec();

            if(recordTime  != 0 && recordTime >= g_u32TimeShiftStartRecordingTime_Sec)
            {
                if(playTime > 0)
                {
                    MApp_ConvertSeconds2StTime(playTime, &_stTime);
                }
                else
                {
                    MApp_ConvertSeconds2StTime((recordTime - g_u32TimeShiftStartRecordingTime_Sec), &_stTime);
                }
            }
            else
            {
                return 0;
            }

            CHAR_BUFFER[0] = CHAR_LEFT_BRACKET;
            CHAR_BUFFER[1] = CHAR_MINUS;
            __MApp_UlongToString((U16)_stTime.u8Hour, (CHAR_BUFFER+2), 2);
            CHAR_BUFFER[4] = CHAR_COLON;
            __MApp_UlongToString((U16)_stTime.u8Min, (CHAR_BUFFER+5), 2);
            CHAR_BUFFER[7] = CHAR_COLON;
            __MApp_UlongToString((U16)_stTime.u8Sec, (CHAR_BUFFER+8), 2);
            CHAR_BUFFER[10] = CHAR_RIGHT_BRACKET;
            CHAR_BUFFER[11] = 0;
            return CHAR_BUFFER;
        }
#endif

        ///////////////////PVR Playback UI dynamic text/////////////////////////////
        case HWND_PVR_PLAYBACK_INFO_EVENT_TITLE_TXT:
        {
        #if(ENABLE_PVR_BROWSER)
            if(E_PVR_RET_OK == MApp_PvrBrowser_GetPlayingAttribute(E_PVR_ATTR_PROGRAM_NAME, (BYTE*)CHAR_BUFFER, UI_PVR_PROGRAM_NAME_MAX_UNICODE_LEN*2))
            {
                return CHAR_BUFFER;
            }
            else
        #endif
            {
                return 0;
            }
        }
            break;

        case HWND_PVR_PLAYBACK_INFO_CH_NAME_TXT:
        {
        #if(ENABLE_PVR_BROWSER)
            if(E_PVR_RET_OK == MApp_PvrBrowser_GetPlayingAttribute(E_PVR_ATTR_CHANNEL_NAME, (BYTE*)CHAR_BUFFER, UI_PVR_CHANNEL_NAME_MAX_UNICODE_LEN*2))
            {
                return CHAR_BUFFER;
            }
            else
        #endif
            {
                return 0;
            }
        }
            break;

#ifndef   PVR_UTOPIA
        case HWND_PVR_PLAYBACK_PLAYBACK_TIME_BRIEF_TXT:
        {
            U32 recordTime = MApp_Playback_GetRecordEndTimeSec();
            U32 playTime = MApp_Playback_GetPlaybackTimeSec();
            U32 u32ValidPeriod = MApp_Playback_GetRecordValidPeriodSec();
            ST_TIME _stTimePlayTime;
            if(recordTime  != 0 && recordTime >= playTime && recordTime >= g_u32TimeShiftStartRecordingTime_Sec)
            {
                if(playTime > 0)
                {
                   // MApp_ConvertSeconds2StTime(u32ValidPeriod-(recordTime - playTime), &_stTimePlayTime);
                    MApp_ConvertSeconds2StTime(playTime, &_stTimePlayTime);
                }
                else
                {
                    MApp_ConvertSeconds2StTime(u32ValidPeriod-(recordTime - g_u32TimeShiftStartRecordingTime_Sec), &_stTimePlayTime);
                }
                snprintf((char*)CHAR_BUFFER, 11, "[%02u:%02u:%02u]",
                    (U16)_stTimePlayTime.u8Hour,(U16)_stTimePlayTime.u8Min,(U16)_stTimePlayTime.u8Sec
                    );
                FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                return CHAR_BUFFER;
            }
            else
            {
                u16TempID = Empty;
            }
        }
            break;
#endif
        case HWND_PVR_PLAY_PLAYBACK_TIME_TEXT:
        {
            U32 recordTime = MApp_Playback_GetRecordEndTimeSec();
            U32 playTime = MApp_Playback_GetPlaybackTimeSec();
            U32 u32TotalTime = MApp_Playback_GetTotalTimeSec();
            ST_TIME _stTimePlayTime;
            ST_TIME _stTimeTotalTime;
            if(recordTime  != 0  && recordTime >= g_u32TimeShiftStartRecordingTime_Sec)
            {
                MApp_ConvertSeconds2StTime(playTime, &_stTimePlayTime);

                MApp_ConvertSeconds2StTime(u32TotalTime, &_stTimeTotalTime);
                snprintf((char*)CHAR_BUFFER, 20, "[%02u:%02u:%02u/%02u:%02u:%02u]",
                    (U16)_stTimePlayTime.u8Hour,(U16)_stTimePlayTime.u8Min,(U16)_stTimePlayTime.u8Sec,
                    (U16)_stTimeTotalTime.u8Hour,(U16)_stTimeTotalTime.u8Min,(U16)_stTimeTotalTime.u8Sec);
                FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                return CHAR_BUFFER;
            }
            else
            {
                u16TempID = Empty;
            }
        }
            break;

        case HWND_PVR_FREE_REC_LIMIT_OPTION:
        {
            U8 curStringLen = 0;
            U8 digit_Text = MApp_GetNoOfDigit(stGenSetting.g_SysSetting.u32PVR_RecordMaxTime/SECONDS_PER_HOUR);

            __MApp_UlongToString(stGenSetting.g_SysSetting.u32PVR_RecordMaxTime/SECONDS_PER_HOUR, CHAR_BUFFER, digit_Text);
            curStringLen += digit_Text;
            CHAR_BUFFER[curStringLen++] = CHAR_SPACE;
            CHAR_BUFFER[curStringLen++] = CHAR_H;
            CHAR_BUFFER[curStringLen++] = CHAR_r;
            CHAR_BUFFER[curStringLen++] = CHAR_DOT;
            CHAR_BUFFER[curStringLen] = 0;
            return CHAR_BUFFER;
        }
            break;

        case HWND_PVR_TIMESHIFT_INFO_XN_TEXT:
        {
            switch( MApp_TimeShift_GetPlaybackSpeed() )
            {
                case E_PLAY_SPEED_2X:
                    CHAR_BUFFER[0] = CHAR_x;
                    CHAR_BUFFER[1] = CHAR_2;
                    CHAR_BUFFER[2] = 0;
                    break;
                case E_PLAY_SPEED_4X:
                    CHAR_BUFFER[0] = CHAR_x;
                    CHAR_BUFFER[1] = CHAR_4;
                    CHAR_BUFFER[2] = 0;
                    break;
                case E_PLAY_SPEED_8X:
                    CHAR_BUFFER[0] = CHAR_x;
                    CHAR_BUFFER[1] = CHAR_8;
                    CHAR_BUFFER[2] = 0;
                    break;
                case E_PLAY_SPEED_16X:
                    CHAR_BUFFER[0] = CHAR_x;
                    CHAR_BUFFER[1] = CHAR_1;
                    CHAR_BUFFER[2] = CHAR_6;
                    CHAR_BUFFER[3] = 0;
                    break;
                default:
                    u16TempID = Empty;
                    break;
            }
            return CHAR_BUFFER;
        }
            break;

        case HWND_PVR_PLAY_INFO_XN_TEXT:
        {
            switch( MApp_Playback_GetPlaybackSpeed() )
            {
                case E_PLAY_SPEED_2X:
                    CHAR_BUFFER[0] = CHAR_x;
                    CHAR_BUFFER[1] = CHAR_2;
                    CHAR_BUFFER[2] = 0;
                    break;
                case E_PLAY_SPEED_4X:
                    CHAR_BUFFER[0] = CHAR_x;
                    CHAR_BUFFER[1] = CHAR_4;
                    CHAR_BUFFER[2] = 0;
                    break;
                case E_PLAY_SPEED_8X:
                    CHAR_BUFFER[0] = CHAR_x;
                    CHAR_BUFFER[1] = CHAR_8;
                    CHAR_BUFFER[2] = 0;
                    break;
                case E_PLAY_SPEED_16X:
                    CHAR_BUFFER[0] = CHAR_x;
                    CHAR_BUFFER[1] = CHAR_1;
                    CHAR_BUFFER[2] = CHAR_6;
                    CHAR_BUFFER[3] = 0;
                    break;
                default:
                    u16TempID = Empty;
                    break;
            }
            return CHAR_BUFFER;
/*#if 1
        case HWND_PVR_FILE_SYSTEM_TYPE_RESLUT:
            if (g_u8PvrFormatFsType == PVR_FS_LINUX_NTFS)
                u16TempID = en_str_PvrFileSystemType_NTFS;
            else
                u16TempID = en_str_FAT32;
            break;
#endif*/
        }
            break;
        ///////////////////PVR Playback UI dynamic text/////////////////////////////
    }

    if (u16TempID != Empty)
    {
        return MApp_ZUI_API_GetString(u16TempID);
    }
    return 0; //for empty string....
}

static void _MApp_ZUI_ACT_PVR_SetFocus(HWND hwnd)
{
    HWND current = MApp_ZUI_API_GetFocus();
    switch(hwnd)
    {
        case HWND_PVR_TIMESHIFT_OP_ICONS_PANE:
            if(HWND_PVR_TIMESHIFT_ICON_PLAY != current
                    && HWND_PVR_TIMESHIFT_ICON_FB != current
                    && HWND_PVR_TIMESHIFT_ICON_FF != current
                    && HWND_PVR_TIMESHIFT_ICON_PREV != current
                    && HWND_PVR_TIMESHIFT_ICON_NEXT != current
                    && HWND_PVR_TIMESHIFT_ICON_PAUSE != current
                    && HWND_PVR_TIMESHIFT_ICON_STOP != current)
            {
                MApp_ZUI_API_SetFocus(HWND_PVR_TIMESHIFT_ICON_PLAY);
            }
            break;

        case HWND_PVR_PLAY_OP_ICONS_PANE:
            if(HWND_PVR_PLAY_ICON_PLAY != current
                    && HWND_PVR_PLAY_ICON_FB != current
                    && HWND_PVR_PLAY_ICON_FF != current
                    && HWND_PVR_PLAY_ICON_PREV != current
                    && HWND_PVR_PLAY_ICON_NEXT != current
                    && HWND_PVR_PLAY_ICON_PAUSE != current
                    && HWND_PVR_PLAY_ICON_STOP != current)
            {
                MApp_ZUI_API_SetFocus(HWND_PVR_PLAY_ICON_PLAY);
            }
            break;

        case HWND_PVR_RECORDING_OP_ICONS_PANE:
            if(HWND_PVR_RECORDING_ICON_PLAY != current
                    && HWND_PVR_RECORDING_ICON_FB != current
                    && HWND_PVR_RECORDING_ICON_FF != current
                    && HWND_PVR_RECORDING_ICON_PREV != current
                    && HWND_PVR_RECORDING_ICON_NEXT != current
                    && HWND_PVR_RECORDING_ICON_PAUSE != current
                    && HWND_PVR_RECORDING_ICON_STOP != current)
            {
            #if( ENABLE_HALF_PVR )
                MApp_ZUI_API_SetFocus(HWND_PVR_RECORDING_ICON_STOP);
            #else
                MApp_ZUI_API_SetFocus(HWND_PVR_RECORDING_ICON_PLAY);
            #endif
            }
            break;
        default:
            break;
    }
}

void MApp_ZUI_ACT_PVR_OpenUI(PvrMenuPageType newMenuPageIdx)
{
    PVR_ZUI_DBG(printf("MApp_ZUI_ACT_PVR_OpenUI=%d\n", newMenuPageIdx));

    if(MApp_ZUI_GetActiveOSD() == E_OSD_AUTO_TUNING)
        return;

    if(MApp_ZUI_GetActiveOSD() != E_OSD_PVR)
    {
        MApp_ZUI_ACT_StartupOSD(E_OSD_PVR);
    }

    g_PvrMenuPageType = newMenuPageIdx;

    switch(newMenuPageIdx)
    {
        case MENU_PVR_INITIAL:
            MApp_ZUI_API_ShowWindow(HWND_PVR_INITIAL_WARNING_MESSAGE_PANE,SW_SHOW);
            MApp_ZUI_API_SetTimer(HWND_PVR_INITIAL_WARNING_MESSAGE_PANE, 0, 1000);
        #if ENABLE_S2
            EN_TOP_STATE TopState;
            TopState = MApp_TopStateMachine_GetTopState();
            if (TopState == STATE_TOP_MENU || TopState == STATE_TOP_DISHSETUP)
            {
                MApp_TopStateMachine_SetTopState(STATE_TOP_DIGITALINPUTS);
                enMainMenuState = STATE_MENU_INIT;
                enDishSetupState = STATE_DISHSETUP_INIT;
            }
        #endif
            break;
        case MENU_PVR_RECORD:
#ifdef PVR_UTOPIA
        {
            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_STATUS_INFO_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_RECORDING_OP_ICONS_PANE, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_RECORDING_OP_MAKEUP_BG, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_RECORDING_OP_MAKEUP_LINE_BLUE_A, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_RECORDING_OP_MAKEUP_LINE_BLUE_B, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_RECORDING_INFO_ICON_REC, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_RECORDING_RECORD_TIME_TEXT, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_RECORDING_CHANNEL_NUMBER, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_RECORDING_CHANNEL_NAME, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_RECORDING_EVENT_NAME, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_RECORDING_DISK_REMAIN, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_RECORDING_SYSTEM_CLOCK, SW_SHOW);

            if(!MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_DLG_PANE))
            {
                _MApp_ZUI_ACT_PVR_SetFocus(HWND_PVR_RECORDING_OP_ICONS_PANE);
            }
            break;
        }
#else
        {
            MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_STATUS_INFO_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_RECORDING_STATUS_INFO_PANE, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_RECORDING_BALL_BRIEF_ICON, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_RECORDING_DISK_REMAIN, SW_SHOW);
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_PVR_RECORDING_STATUS_INFO_PANE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_RECORDING_TIME_BRIEF, SW_HIDE);
//#if PVR_ICON_FLASH
            if(!MApp_ZUI_API_IsExistTimer(HWND_PVR_RECORDING_STATUS_INFO_PANE, 0))
                MApp_ZUI_API_SetTimer(HWND_PVR_RECORDING_STATUS_INFO_PANE, 0, 750);  //for icon flash
//#endif
            break;
        }
#endif
        case MENU_PVR_RECORDING_BRIEF:
#ifdef PVR_UTOPIA
        {
            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_STATUS_INFO_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_RECORDING_STATUS_INFO_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_RECORDING_INFO_ICON_REC, SW_SHOW);
            break;
        }
#else
        {
            MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_STATUS_INFO_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_RECORDING_STATUS_INFO_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_RECORDING_BALL_BRIEF_ICON, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_RECORDING_TIME_BRIEF, SW_SHOW);

            if(!MApp_ZUI_API_IsExistTimer(HWND_PVR_RECORDING_STATUS_INFO_PANE, 0))
                MApp_ZUI_API_SetTimer(HWND_PVR_RECORDING_STATUS_INFO_PANE, 0, 750);  //for icon flash
            break;
        }
#endif
        case MENU_PVR_RECORD_CHANNEL_CHANGE_CHECK:
        {
            break;
        }
        case MENU_PVR_TIME_SHIFT:
#ifdef PVR_UTOPIA
        {
            enTimeShiftState TimeShiftState   = MApp_TimeShift_StateMachineGet();
            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_OP_MAKEUP_BG, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_OP_MAKEUP_LINE_BLUE_A, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_OP_MAKEUP_LINE_BLUE_B, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_PERCENTAGE_BAR, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_PLAYBACK_TIME_TXT, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_SYSTEM_CLOCK, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_OP_ICONS_PANE, SW_SHOW);

            #if 0   //20090903,Bug to fix: TimeShiftState may go wrong to E_TIMESHIFT_STATE_RECORDING
                if((TimeShiftState == E_TIMESHIFT_STATE_RECORDING)||MApp_TimeShift_IfPause())
            #else
            if(MApp_TimeShift_IfPause())
            #endif
            {
                MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_PAUSE, SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_PLAY, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_FB, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_FF, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_XN_TEXT, SW_HIDE);
            }
            else if((TimeShiftState == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING) ||
                    (TimeShiftState == E_TIMESHIFT_STATE_PLAYBACKING))
            {
                MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_PAUSE, SW_HIDE);
                switch(MApp_TimeShift_GetPlaybackSpeed())
                {
                    case E_PLAY_SPEED_1X:
                    {
                        MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_PLAY, SW_SHOW);
                        MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_FB, SW_HIDE);
                        MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_FF, SW_HIDE);
                        MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_XN_TEXT, SW_HIDE);
                        if(((enPVRState)MApp_PVR_StateMachineGet() == E_PVR_STATE_TIMESHIFT)
                        && (TimeShiftState == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING))
                        {
                            U32 u32RecordStartTime  = MApp_TimeShift_GetRecordStartTimeSec();
                            U32 u32PlaybackTime     = MApp_TimeShift_GetPlaybackTimeSec();
                            U32 u32RecordEndTime    = MApp_TimeShift_GetRecordEndTimeSec();

                            if ((u32PlaybackTime != 0) &&
                                (u32RecordEndTime - u32RecordStartTime - u32PlaybackTime) >= ((U32)MApp_TimeShift_GetRecordValidPeriodSec() - UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC))
                            {
                                    MApp_ZUI_API_EnableWindow (HWND_PVR_TIMESHIFT_ICON_FF, FALSE);
                                    MApp_ZUI_API_EnableWindow (HWND_PVR_TIMESHIFT_ICON_FB, FALSE);
                                    MApp_ZUI_API_EnableWindow (HWND_PVR_TIMESHIFT_ICON_PAUSE, FALSE);
                             }
                             else if((u32RecordEndTime - u32RecordStartTime) >= ((U32)MApp_TimeShift_GetRecordValidPeriodSec() - UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC ))
                            {
                                    MApp_ZUI_API_EnableWindow (HWND_PVR_TIMESHIFT_ICON_FF, FALSE);
                                    MApp_ZUI_API_EnableWindow (HWND_PVR_TIMESHIFT_ICON_FB, FALSE);
                                    MApp_ZUI_API_EnableWindow (HWND_PVR_TIMESHIFT_ICON_PAUSE, TRUE);
                            }
                         }
                    }
                        break;
                    case E_PLAY_SPEED_2X:
                    case E_PLAY_SPEED_4X:
                    case E_PLAY_SPEED_8X:
                    case E_PLAY_SPEED_16X:
                        if(MApp_TimeShift_IfFastForward())
                        {
                            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_PLAY, SW_HIDE);
                            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_FB, SW_HIDE);
                            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_FF, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_XN_TEXT, SW_SHOW);

                            MApp_ZUI_API_InvalidateWindow(HWND_PVR_TIMESHIFT_INFO_XN_TEXT);
                        }
                        else if(MApp_TimeShift_IfFastBackward())
                        {
                            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_PLAY, SW_HIDE);
                            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_FB, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_FF, SW_HIDE);
                            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_XN_TEXT, SW_SHOW);

                            MApp_ZUI_API_InvalidateWindow(HWND_PVR_TIMESHIFT_INFO_XN_TEXT);
                        }
                        break;
                    default:
                    break;
                }

                if(MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_B_set)
                {
                    MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_AB_SET_A, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_AB_LOOP, SW_SHOW);
                }
                else if(MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_A_set)
                {
                    MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_AB_SET_A, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_AB_LOOP, SW_HIDE);
                }
                else
                {
                    MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_AB_SET_A, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_AB_LOOP, SW_HIDE);
                }
            }

            if(TimeShiftState == E_TIMESHIFT_STATE_PLAYBACKING)
            {
                MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_NOSIGNAL_TXT, SW_SHOW);
            }
            else
            {
                MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_NOSIGNAL_TXT, SW_HIDE);
            }

            if(!MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_DLG_PANE))
            {
                _MApp_ZUI_ACT_PVR_SetFocus(HWND_PVR_TIMESHIFT_OP_ICONS_PANE);
            }
            break;
        }
#else
        {
            enTimeShiftState TimeShiftState   = MApp_TimeShift_StateMachineGet();
            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_STATUS_INFO_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_BG, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_BG_UP, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_BG_MIDDLE, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_BG_DOWN, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_TIMESHIFT_TITLE, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_PERCENTAGE_BAR, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_SYSTEM_CLOCK, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_PLAYBACK_TIME_TXT, SW_SHOW);

            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_PLAY_ICON, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);

            if((TimeShiftState == E_TIMESHIFT_STATE_RECORDING)||MApp_TimeShift_IfPause())
                MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_PAUSE_ICON, SW_SHOW);
            else if((TimeShiftState == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING) ||
                    (TimeShiftState == E_TIMESHIFT_STATE_PLAYBACKING))
            {
                MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_PAUSE_ICON, SW_HIDE);
                switch( MApp_TimeShift_GetPlaybackSpeed() )
                {
                    case E_PLAY_SPEED_1X:
                        MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_PLAY_ICON, SW_SHOW);
                        break;
                    case E_PLAY_SPEED_2X:
                        if( MApp_TimeShift_IfFastForward() )
                            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X2, SW_SHOW);
                        if( MApp_TimeShift_IfFastBackward() )
                            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FR_X2, SW_SHOW);
                        break;
                    case E_PLAY_SPEED_4X:
                        if( MApp_TimeShift_IfFastForward() )
                            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X4, SW_SHOW);
                        if( MApp_TimeShift_IfFastBackward() )
                            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FR_X4, SW_SHOW);
                        break;
                    case E_PLAY_SPEED_8X:
                        if( MApp_TimeShift_IfFastForward() )
                            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X8, SW_SHOW);
                        if( MApp_TimeShift_IfFastBackward() )
                            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FR_X8, SW_SHOW);
                        break;
                    case E_PLAY_SPEED_16X:
                        if( MApp_TimeShift_IfFastForward() )
                            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X16, SW_SHOW);
                        if( MApp_TimeShift_IfFastBackward() )
                            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FR_X16, SW_SHOW);
                        break;
                    default:
                    break;
                }
                if(MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_B_set)
                {
                    MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_LOOP_A_GREEN_ICON, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_LOOP_B_GREEN_ICON, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_AB_LOOP_ICON, SW_SHOW);
                }
                else if(MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_A_set)
                {
                    MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_LOOP_A_GREEN_ICON, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_LOOP_B_GRAY_ICON, SW_SHOW);
                }
                else
                {
                    MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_LOOP_A_GRAY_ICON, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_LOOP_B_GRAY_ICON, SW_SHOW);
                }
            }
            if((TimeShiftState == E_TIMESHIFT_STATE_PLAYBACKING))
            {
                MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_NOSIGNAL_TXT, SW_SHOW);
            }
//#if PVR_ICON_FLASH
            if(!MApp_ZUI_API_IsExistTimer(HWND_PVR_RECORDING_STATUS_INFO_PANE, 0))
                MApp_ZUI_API_SetTimer(HWND_PVR_RECORDING_STATUS_INFO_PANE, 0, 750);  //for icon flash
//#endif
            break;
        }
#endif

        case MENU_PVR_TIME_SHIFT_BRIEF:
#ifdef PVR_UTOPIA
        {
            enTimeShiftState TimeShiftState   = MApp_TimeShift_StateMachineGet();
            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_STATUS_INFO_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_OP_MAKEUP_BG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_OP_MAKEUP_LINE_BLUE_A, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_OP_MAKEUP_LINE_BLUE_B, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_PERCENTAGE_BAR, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_PLAYBACK_TIME_TXT, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_SYSTEM_CLOCK, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_OP_ICONS_PANE, SW_HIDE);

            if((TimeShiftState == E_TIMESHIFT_STATE_RECORDING)||MApp_TimeShift_IfPause())
            {
                MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_PAUSE, SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_PLAY, SW_HIDE);
            }
            else if((TimeShiftState == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING)
                        ||(TimeShiftState == E_TIMESHIFT_STATE_PLAYBACKING))
            {
                MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_PAUSE, SW_HIDE);
                switch(MApp_TimeShift_GetPlaybackSpeed())
                {
                    case E_PLAY_SPEED_1X:
                        MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_PLAY, SW_SHOW);
                        MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_FB, SW_HIDE);
                        MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_FF, SW_HIDE);
                        MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_XN_TEXT, SW_HIDE);
                        break;
                    case E_PLAY_SPEED_2X:
                    case E_PLAY_SPEED_4X:
                    case E_PLAY_SPEED_8X:
                    case E_PLAY_SPEED_16X:
                        if(MApp_TimeShift_IfFastForward())
                        {
                            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_PLAY, SW_HIDE);
                            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_FB, SW_HIDE);
                            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_FF, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_XN_TEXT, SW_SHOW);

                            MApp_ZUI_API_InvalidateWindow(HWND_PVR_TIMESHIFT_INFO_XN_TEXT);
                        }
                        else if(MApp_TimeShift_IfFastBackward())
                        {
                            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_PLAY, SW_HIDE);
                            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_FB, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_FF, SW_HIDE);
                            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_XN_TEXT, SW_SHOW);

                            MApp_ZUI_API_InvalidateWindow(HWND_PVR_TIMESHIFT_INFO_XN_TEXT);
                        }
                        break;
                    default:
                    break;
                }

                if(MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_B_set)
                {
                    MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_AB_SET_A, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_AB_LOOP, SW_SHOW);
                }
                else if(MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_A_set)
                {
                    MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_AB_SET_A, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_AB_LOOP, SW_HIDE);
                }
                else
                {
                    MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_AB_SET_A, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_AB_LOOP, SW_HIDE);
                }
            }
            break;
        }
#else
        {
            enTimeShiftState TimeShiftState   = MApp_TimeShift_StateMachineGet();

            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_STATUS_INFO_PANE, SW_HIDE);

            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_PLAYBACK_TIME_BRIEF_TXT, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);

            if((TimeShiftState == E_TIMESHIFT_STATE_RECORDING)||MApp_TimeShift_IfPause())
            {
                MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_PAUSE_BRIEF_ICON, SW_SHOW);
            }
            else if((TimeShiftState == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING)
                && E_PLAY_SPEED_1X == MApp_TimeShift_GetPlaybackSpeed())
            {
                if(MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_B_set)
                {
                    MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_AB_LOOP_BRIEF_ICON, SW_SHOW);
                }
                else
                {
                    MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_PLAY_BRIEF_ICON, SW_SHOW);
                }
            }

            if(!MApp_ZUI_API_IsExistTimer(HWND_PVR_RECORDING_STATUS_INFO_PANE, 0))
                MApp_ZUI_API_SetTimer(HWND_PVR_RECORDING_STATUS_INFO_PANE, 0, 750);  //for icon flash

            break;
        }
#endif

        case MENU_PVR_PLAYBACK_BRIEF:
#ifdef PVR_UTOPIA
        {
            enPVRState PVRState = MApp_PVR_StateMachineGet();
            enPlaybackState PlaybackState = MApp_Playback_StateMachineGet();

            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_STATUS_INFO_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_RECORDING_STATUS_INFO_PANE, SW_HIDE);

            if(PVRState == E_PVR_STATE_RECORDnPLAYBACK)
            {
                MApp_ZUI_API_ShowWindow(HWND_PVR_RECORDING_INFO_ICON_REC, SW_SHOW);
            }

            if(PlaybackState == E_PLAYBACK_STATE_PAUSE)
            {
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_PAUSE, SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_PLAY, SW_HIDE);
            }
            else if(PlaybackState == E_PLAYBACK_STATE_PLAYBACKING)
            {
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_PAUSE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_PLAY, SW_SHOW);
            }
            else if(PlaybackState == E_PLAYBACK_STATE_FASTBACKWARD || PlaybackState == E_PLAYBACK_STATE_FASTFORWARD)
            {
                switch(MApp_Playback_GetPlaybackSpeed())
                {
                    case E_PLAY_SPEED_2X:
                    case E_PLAY_SPEED_4X:
                    case E_PLAY_SPEED_8X:
                    case E_PLAY_SPEED_16X:
                        if(PlaybackState == E_PLAYBACK_STATE_FASTFORWARD)
                        {
                            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_PLAY, SW_HIDE);
                            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_FB, SW_HIDE);
                            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_FF, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_XN_TEXT, SW_SHOW);

                            MApp_ZUI_API_InvalidateWindow(HWND_PVR_TIMESHIFT_INFO_XN_TEXT);
                        }
                        else if(PlaybackState == E_PLAYBACK_STATE_FASTBACKWARD)
                        {
                            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_PLAY, SW_HIDE);
                            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_FB, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_FF, SW_HIDE);
                            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_XN_TEXT, SW_SHOW);

                            MApp_ZUI_API_InvalidateWindow(HWND_PVR_TIMESHIFT_INFO_XN_TEXT);
                        }
                        break;
                    default:
                    break;
                }
            }

            if(MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_B_set)
            {
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_AB_SET_A, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_AB_LOOP, SW_SHOW);
            }
            else if(MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_A_set)
            {
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_AB_SET_A, SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_AB_LOOP, SW_HIDE);
            }
            else
            {
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_AB_SET_A, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_AB_LOOP, SW_HIDE);
            }
            break;
        }
#else
        {
            enPvrABLoopState ABLoopState = MApp_UiPvr_GetABLoop_Status();
            enPlaybackState PlaybackState = MApp_Playback_StateMachineGet();

            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_STATUS_INFO_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_PLAYBACK_TIME_BRIEF_TXT, SW_SHOW);

            if((PlaybackState == E_PLAYBACK_STATE_PLAYBACKING) && ABLoopState == E_ABLOOP_B_set)
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_AB_LOOP_BRIEF_ICON, SW_SHOW);
            else if((PlaybackState == E_PLAYBACK_STATE_PLAYBACKING) && ABLoopState != E_ABLOOP_B_set)
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_PLAY_BRIEF_ICON, SW_SHOW);
            else if((PlaybackState == E_PLAYBACK_STATE_PAUSE))
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_PAUSE_BRIEF_ICON, SW_SHOW);

            MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);

            if(!MApp_ZUI_API_IsExistTimer(HWND_PVR_RECORDING_STATUS_INFO_PANE, 0))
                MApp_ZUI_API_SetTimer(HWND_PVR_RECORDING_STATUS_INFO_PANE, 0, 750);  //for icon flash

            break;
        }
#endif
        case MENU_PVR_PLAYBACK:
#ifdef PVR_UTOPIA
        {
            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_OP_MAKEUP_BG, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_OP_MAKEUP_LINE_BLUE_A, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_OP_MAKEUP_LINE_BLUE_B, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_PERCENTAGE_BAR, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_PLAYBACK_TIME_TEXT, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_SYSTEM_CLOCK, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_OP_ICONS_PANE, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_RECORDING_STATUS_INFO_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_RECORDING_INFO_ICON_REC, SW_HIDE);

            /*if(MApp_PVR_IsRecording())
            {
                MApp_ZUI_API_ShowWindow(HWND_PVR_RECORDING_INFO_ICON_REC, SW_SHOW);
            }
            else
            {
                MApp_ZUI_API_ShowWindow(HWND_PVR_RECORDING_INFO_ICON_REC, SW_HIDE);
            }*/

            //AB loop
            if(MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_A_set)
            {
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_AB_SET_A, SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_AB_LOOP, SW_HIDE);
            }
            else if(MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_B_set)
            {
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_AB_SET_A, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_AB_LOOP, SW_SHOW);
            }
            else
            {
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_AB_SET_A, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_AB_LOOP, SW_HIDE);
            }

            switch(MApp_Playback_StateMachineGet())
            {
                case E_PLAYBACK_STATE_PAUSE:
                    MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_PAUSE, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_PLAY, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_FB, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_FF, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_XN_TEXT, SW_HIDE);
                    break;
                case E_PLAYBACK_STATE_PLAYBACKING:
                    MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_PAUSE, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_PLAY, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_FB, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_FF, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_XN_TEXT, SW_HIDE);
                    break;
                case E_PLAYBACK_STATE_FASTBACKWARD:
                    MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_PAUSE, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_PLAY, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_FB, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_FF, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_XN_TEXT, SW_SHOW);
                    break;
                case E_PLAYBACK_STATE_FASTFORWARD:
                    MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_PAUSE, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_PLAY, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_FB, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_FF, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_XN_TEXT, SW_SHOW);
                    break;
                default:
                    break;
            }

            if(!MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_DLG_PANE))
            {
                _MApp_ZUI_ACT_PVR_SetFocus(HWND_PVR_PLAY_OP_ICONS_PANE);
            }
            break;
        }
#else
        {
            //RecordnPlayback need to hide Record UI and show Playback UI
            {
                MApp_ZUI_API_ShowWindow(HWND_PVR_RECORDING_BALL_BRIEF_ICON, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_PVR_RECORDING_TIME_BRIEF, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_PVR_RECORDING_STATUS_INFO_PANE, SW_HIDE);
            }

            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_STATUS_INFO_PANE, SW_SHOW);

            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_PAUSE_BRIEF_ICON, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_PLAY_BRIEF_ICON, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_AB_LOOP_BRIEF_ICON, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_PLAYBACK_TIME_BRIEF_TXT, SW_HIDE);

            //AB loop
            if(MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_A_set)
            {
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_LOOP_B_GREEN_ICON, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_AB_LOOP_ICON, SW_HIDE);
            }
            else if(MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_B_set)
            {
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_AB_LOOP_ICON, SW_SHOW);
            }
            else
            {
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_LOOP_A_GREEN_ICON, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_LOOP_B_GREEN_ICON, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_AB_LOOP_ICON, SW_HIDE);
            }

            MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_PLAY_ICON, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);

            switch( MApp_Playback_GetPlaybackSpeed() )
            {
                case E_PLAY_SPEED_1X:
                    MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_PLAY_ICON, SW_SHOW);
                    break;
                case E_PLAY_SPEED_2X:
                    if( MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_FASTFORWARD )
                        MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X2, SW_SHOW);
                    if( MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_FASTBACKWARD )
                        MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FR_X2, SW_SHOW);
                    break;
                case E_PLAY_SPEED_4X:
                    if( MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_FASTFORWARD )
                        MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X4, SW_SHOW);
                    if( MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_FASTBACKWARD )
                        MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FR_X4, SW_SHOW);
                    break;
                case E_PLAY_SPEED_8X:
                    if( MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_FASTFORWARD )
                        MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X8, SW_SHOW);
                    if( MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_FASTBACKWARD )
                        MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FR_X8, SW_SHOW);
                    break;
                case E_PLAY_SPEED_16X:
                    if( MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_FASTFORWARD )
                        MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X16, SW_SHOW);
                    if( MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_FASTBACKWARD )
                        MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FR_X16, SW_SHOW);
                    break;
                default:
                break;
            }
            //PAUSE
            if(MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_PAUSE)
            {
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_PLAY_ICON, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X2, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X4, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X8, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X16, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_AB_LOOP_ICON, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_PAUSE_ICON, SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_LOOP_A_GRAY_ICON, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_LOOP_B_GRAY_ICON, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_LOOP_A_GREEN_ICON, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_LOOP_B_GREEN_ICON, SW_HIDE);
            }
            else
                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_PAUSE_ICON, SW_HIDE);

            break;
        }
#endif

        case MENU_PVR_PAUSE_BRIEF:
#ifdef PVR_UTOPIA
        {
            enPVRState       PVRState         = MApp_PVR_StateMachineGet();
            switch(PVRState)
            {
                case E_PVR_STATE_PLAYBACK:
                case E_PVR_STATE_RECORDnPLAYBACK:
                {
                    MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_STATUS_INFO_PANE, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_PAUSE, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_PLAY, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_FB, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_FF, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_XN_TEXT, SW_HIDE);

                    if(MApp_PVR_IsRecording())
                    {
                        MApp_ZUI_API_ShowWindow(HWND_PVR_RECORDING_INFO_ICON_REC, SW_SHOW);
                    }
                    else
                    {
                        MApp_ZUI_API_ShowWindow(HWND_PVR_RECORDING_INFO_ICON_REC, SW_HIDE);
                    }

                    //AB loop
                    if(MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_A_set)
                    {
                        MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_AB_SET_A, SW_SHOW);
                        MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_AB_LOOP, SW_HIDE);
                    }
                    else if(MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_B_set)
                    {
                        MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_AB_SET_A, SW_HIDE);
                        MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_AB_LOOP, SW_SHOW);
                    }
                    else
                    {
                        MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_AB_SET_A, SW_HIDE);
                        MApp_ZUI_API_ShowWindow(HWND_PVR_PLAY_INFO_ICON_AB_LOOP, SW_HIDE);
                    }
                    break;
                }
                default:
                    break;
            }
            break;
        }

#else
        {
            enPVRState       PVRState         = MApp_PVR_StateMachineGet();
            switch(PVRState)
            {
                case E_PVR_STATE_TIMESHIFT:
                {
                    MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_STATUS_INFO_PANE, SW_HIDE);

                    if(!MApp_ZUI_API_IsExistTimer(HWND_PVR_RECORDING_STATUS_INFO_PANE, 0))
                        MApp_ZUI_API_SetTimer(HWND_PVR_RECORDING_STATUS_INFO_PANE, 0, 750);  //for icon flash
                    break;
                }
                case E_PVR_STATE_PLAYBACK:
                case E_PVR_STATE_RECORDnPLAYBACK:
                {
                    MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_STATUS_INFO_PANE, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_PLAYBACK_TIME_BRIEF_TXT, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_PLAY_BRIEF_ICON, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_AB_LOOP_BRIEF_ICON, SW_HIDE);

                    if(!MApp_ZUI_API_IsExistTimer(HWND_PVR_RECORDING_STATUS_INFO_PANE, 0))
                       MApp_ZUI_API_SetTimer(HWND_PVR_RECORDING_STATUS_INFO_PANE, 0, 750);  //for icon flash

                    break;
                }
                default:
                    break;
            }
            break;
        }
#endif
        case MENU_PVR_SOURCE_CHANGE_CHECK:
        {
            break;
        }
        default:
            break;
    }
}

void MApp_ZUI_ACT_PVR_CloseUI(void)
{
    PVR_ZUI_DBG(printf("MApp_ZUI_ACT_PVR_CloseUI\n"));

    if(MApp_ZUI_GetActiveOSD() == E_OSD_PVR)
    {
        if(g_PVR_PopUpWarning == E_PVR_WARNING_NONE) //only close warning message by Timer
            MApp_ZUI_ACT_ExecutePvrAction(EN_EXE_CLOSE_CURRENT_OSD);
    }
}

S32 MApp_ZUI_ACT_PvrWinProc(HWND hwnd, PMSG msg)
{
    switch(msg->message)
    {
        case MSG_TIMER:
        {
            MApp_ZUI_API_ResetTimer(hwnd, 0);
            switch(hwnd)
            {
                case HWND_PVR_RECORDING_STATUS_INFO_PANE:
                {
                  #if PVR_ICON_FLASH || !defined(PVR_UTOPIA) || PVR_ICON_FLASH
                    HWND PVRhwnd = 0;
                  #endif

                     switch(g_PvrMenuPageType)
                     {
                      #if PVR_ICON_FLASH
                        case MENU_PVR_RECORD: //flash REC icon
                            PVRhwnd = HWND_PVR_RECORDING_BALL_ICON;
                            break;
                      #endif

                        case MENU_PVR_RECORDING_BRIEF:
                          #ifndef PVR_UTOPIA
                            PVRhwnd = HWND_PVR_RECORDING_BALL_BRIEF_ICON;
                          #endif
                            break;

                      #if PVR_ICON_FLASH
                        case MENU_PVR_TIME_SHIFT:
                        {
                            enTimeShiftState TimeShiftState   = MApp_TimeShift_StateMachineGet();
                            if((TimeShiftState == E_TIMESHIFT_STATE_RECORDING)||MApp_TimeShift_IfPause())
                                PVRhwnd = HWND_PVR_TIMESHIFT_PAUSE_ICON;
                            else if((TimeShiftState == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING))
                            {
                                MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_PAUSE_ICON, SW_HIDE);
                                switch(MApp_TimeShift_GetPlaybackSpeed())
                                {
                                    default:
                                    case E_PLAY_SPEED_1X:
                                        if(MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_B_set)
                                            PVRhwnd = HWND_PVR_TIMESHIFT_AB_LOOP_ICON;
                                        else
                                            PVRhwnd = HWND_PVR_TIMESHIFT_PLAY_ICON;
                                        break;
                                    case E_PLAY_SPEED_2X:
                                        if( MApp_TimeShift_IfFastForward() )
                                            PVRhwnd = HWND_PVR_PLAYBACK_FF_X2;
                                        if( MApp_TimeShift_IfFastBackward() )
                                            PVRhwnd = HWND_PVR_PLAYBACK_FR_X2;
                                        break;
                                    case E_PLAY_SPEED_4X:
                                        if( MApp_TimeShift_IfFastForward() )
                                            PVRhwnd = HWND_PVR_PLAYBACK_FF_X4;
                                        if( MApp_TimeShift_IfFastBackward() )
                                            PVRhwnd = HWND_PVR_PLAYBACK_FR_X4;
                                        break;
                                    case E_PLAY_SPEED_8X:
                                        if( MApp_TimeShift_IfFastForward() )
                                            PVRhwnd = HWND_PVR_PLAYBACK_FF_X8;
                                        if( MApp_TimeShift_IfFastBackward() )
                                            PVRhwnd = HWND_PVR_PLAYBACK_FR_X8;
                                        break;
                                    case E_PLAY_SPEED_16X:
                                        if( MApp_TimeShift_IfFastForward() )
                                            PVRhwnd = HWND_PVR_PLAYBACK_FF_X16;
                                        if( MApp_TimeShift_IfFastBackward() )
                                            PVRhwnd = HWND_PVR_PLAYBACK_FR_X16;
                                        break;
                                }
                            }
                            else if((TimeShiftState == E_TIMESHIFT_STATE_PLAYBACKING))
                                PVRhwnd = HWND_PVR_TIMESHIFT_NOSIGNAL_TXT;
                        }
                            break;
                      #endif

                        case MENU_PVR_TIME_SHIFT_BRIEF:
                        {
                            enTimeShiftState TimeShiftState   = MApp_TimeShift_StateMachineGet();
                            if((TimeShiftState == E_TIMESHIFT_STATE_RECORDING)||MApp_TimeShift_IfPause())
                            {
                              #ifndef PVR_UTOPIA
                                PVRhwnd = HWND_PVR_TIMESHIFT_PAUSE_BRIEF_ICON;
                              #endif
                            }

                            else if((TimeShiftState == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING)||(TimeShiftState == E_TIMESHIFT_STATE_PLAYBACKING))
                            {
                              #ifndef PVR_UTOPIA
                                switch(MApp_TimeShift_GetPlaybackSpeed())
                                {
                                    default:
                                    case E_PLAY_SPEED_1X:
                                        if(MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_B_set)
                                        {
                                            PVRhwnd = HWND_PVR_TIMESHIFT_AB_LOOP_BRIEF_ICON;
                                        }
                                        else
                                        {
                                            PVRhwnd = HWND_PVR_TIMESHIFT_PLAY_BRIEF_ICON;
                                        }
                                        break;
                                    case E_PLAY_SPEED_2X:
                                        if( MApp_TimeShift_IfFastForward() )
                                            PVRhwnd = HWND_PVR_PLAYBACK_FF_X2_BRIEF;
                                        if( MApp_TimeShift_IfFastBackward() )
                                            PVRhwnd = HWND_PVR_PLAYBACK_FR_X2_BRIEF;
                                        break;
                                    case E_PLAY_SPEED_4X:
                                        if( MApp_TimeShift_IfFastForward() )
                                            PVRhwnd = HWND_PVR_PLAYBACK_FF_X4_BRIEF;
                                        if( MApp_TimeShift_IfFastBackward() )
                                            PVRhwnd = HWND_PVR_PLAYBACK_FR_X4_BRIEF;
                                        break;
                                    case E_PLAY_SPEED_8X:
                                        if( MApp_TimeShift_IfFastForward() )
                                            PVRhwnd = HWND_PVR_PLAYBACK_FF_X8_BRIEF;
                                        if( MApp_TimeShift_IfFastBackward() )
                                            PVRhwnd = HWND_PVR_PLAYBACK_FR_X8_BRIEF;
                                        break;
                                    case E_PLAY_SPEED_16X:
                                        if( MApp_TimeShift_IfFastForward() )
                                            PVRhwnd = HWND_PVR_PLAYBACK_FF_X16_BRIEF;
                                        if( MApp_TimeShift_IfFastBackward() )
                                            PVRhwnd = HWND_PVR_PLAYBACK_FR_X16_BRIEF;
                                        break;
                                }
                              #endif
                            }
                            break;
                        }

                        case MENU_PVR_PAUSE_BRIEF:
                      #ifndef PVR_UTOPIA
                        {
                            enPVRState       PVRState         = MApp_PVR_StateMachineGet();
                            switch(PVRState)
                            {
                              case E_PVR_STATE_TIMESHIFT:
                                    PVRhwnd = HWND_PVR_TIMESHIFT_PAUSE_BRIEF_ICON;
                                    break;
                              case E_PVR_STATE_PLAYBACK:
                              case E_PVR_STATE_RECORDnPLAYBACK:
                              default:
                                    PVRhwnd = HWND_PVR_PLAYBACK_PAUSE_BRIEF_ICON;
                                    break;
                             }
                        }
                      #endif
                        break;

                        case MENU_PVR_PLAYBACK_BRIEF:
                          #ifndef PVR_UTOPIA
                            switch( MApp_Playback_GetPlaybackSpeed() )
                            {
                                case E_PLAY_SPEED_1X:
                                    if(MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_B_set)
                                    {
                                        PVRhwnd = HWND_PVR_PLAYBACK_AB_LOOP_BRIEF_ICON;
                                    }
                                    else
                                    {
                                        PVRhwnd = HWND_PVR_PLAYBACK_PLAY_BRIEF_ICON;
                                    }
                                    break;
                                case E_PLAY_SPEED_2X:
                                    if( MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_FASTFORWARD )
                                    {
                                        PVRhwnd = HWND_PVR_PLAYBACK_FF_X2_BRIEF;
                                    }
                                    if( MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_FASTBACKWARD )
                                    {
                                        PVRhwnd = HWND_PVR_PLAYBACK_FR_X2_BRIEF;
                                    }
                                    break;
                                case E_PLAY_SPEED_4X:
                                    if( MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_FASTFORWARD )
                                    {
                                        PVRhwnd = HWND_PVR_PLAYBACK_FF_X4_BRIEF;
                                    }
                                    if( MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_FASTBACKWARD )
                                    {
                                        PVRhwnd = HWND_PVR_PLAYBACK_FR_X4_BRIEF;
                                    }
                                    break;
                                case E_PLAY_SPEED_8X:
                                    if( MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_FASTFORWARD )
                                    {
                                        PVRhwnd = HWND_PVR_PLAYBACK_FF_X8_BRIEF;
                                    }
                                    if( MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_FASTBACKWARD )
                                    {
                                        PVRhwnd = HWND_PVR_PLAYBACK_FR_X8_BRIEF;
                                    }
                                    break;
                                case E_PLAY_SPEED_16X:
                                    if( MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_FASTFORWARD )
                                    {
                                        PVRhwnd = HWND_PVR_PLAYBACK_FF_X16_BRIEF;
                                    }
                                    if( MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_FASTBACKWARD )
                                    {
                                        PVRhwnd = HWND_PVR_PLAYBACK_FR_X16_BRIEF;
                                    }
                                    break;
                                default:
                                break;
                            }
                           #endif
                               break;

                        default:
                            break;
                    }

                  #if PVR_ICON_FLASH || !defined(PVR_UTOPIA) || PVR_ICON_FLASH
                    if(PVRhwnd >0)
                    {
                        if(MApp_ZUI_API_IsWindowVisible(PVRhwnd))
                            MApp_ZUI_API_ShowWindow(PVRhwnd,  FALSE);
                        else
                            MApp_ZUI_API_ShowWindow(PVRhwnd,  TRUE);
                    }
                  #endif
                }
                break;

                case HWND_PVR_WARNING_DLG_PANE:
                {
                    MApp_ZUI_API_ShowWindow(HWND_PVR_WARNING_DLG_PANE, SW_HIDE);
                    if(MApp_ZUI_API_IsWindowVisible(HWND_PVR_TIMESHIFT_OP_ICONS_PANE))
                    {
                        _MApp_ZUI_ACT_PVR_SetFocus(HWND_PVR_TIMESHIFT_OP_ICONS_PANE);
                    }
                    else if(MApp_ZUI_API_IsWindowVisible(HWND_PVR_PLAY_OP_ICONS_PANE))
                    {
                        _MApp_ZUI_ACT_PVR_SetFocus(HWND_PVR_PLAY_OP_ICONS_PANE);
                    }
                    else if(MApp_ZUI_API_IsWindowVisible(HWND_PVR_RECORDING_OP_ICONS_PANE))
                    {
                        _MApp_ZUI_ACT_PVR_SetFocus(HWND_PVR_RECORDING_OP_ICONS_PANE);
                    }
                    break;
                }
                case HWND_PVR_INITIAL_WARNING_MESSAGE_PANE:
                if( MApp_PVR_StateMachineGet() == E_PVR_STATE_INIT)
                {
                    MApp_ZUI_API_ResetTimer(HWND_PVR_INITIAL_WARNING_MESSAGE_PANE, 0);
                    break;
                }
                else
                {
                    //PRINT_CURRENT_LINE();
                    //msAPI_Timer_Delayms(1000);  //Add for resolving the issue that UI is flashing too fast after formatting disc 20100221EL
                    MApp_ZUI_ACT_PVR_CloseUI();
                    break;
                }
                case HWND_PVR_WARNING_MESSAGE_PANE:
                {
                    enPVRState  PVRState = MApp_PVR_StateMachineGet();
                    if(PVRState == E_PVR_STATE_IDLE ||
                       PVRState == E_PVR_STATE_INIT ||
                       PVRState == E_PVR_STATE_WAIT||
                       PVRState == E_PVR_STATE_WAITFORMAT)
                    {
                        MApp_ZUI_ACT_PVR_CloseUI();
                    }
                    else
                    {
                        MApp_ZUI_API_ShowWindow(HWND_PVR_WARNING_MESSAGE_PANE, SW_HIDE);
                    }
                    g_PVR_PopUpWarning = E_PVR_WARNING_NONE;
                    break;
                }
            }
            break;
        }

        default:
            break;
    }
    return DEFAULTWINPROC(hwnd, msg);
}

void MApp_ZUI_ACT_PVR_PopUp_Msg(EN_PVR_POP_UP_WARNING popUpWarning)
{
    PVR_ZUI_DBG(printf("MApp_ZUI_ACT_PVR_PopUp_Msg=%d\n",popUpWarning));

    g_PVR_PopUpWarning = popUpWarning;

    if(MApp_ZUI_GetActiveOSD() != E_OSD_PVR)
    {
        MApp_ZUI_ACT_StartupOSD(E_OSD_PVR);
    }
    else
    {
        if( MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE) )
            MApp_ZUI_API_KillTimer(HWND_PVR_WARNING_MESSAGE_PANE, 0);
    }

    MApp_ZUI_API_ShowWindow(HWND_PVR_WARNING_MESSAGE_PANE, SW_SHOW);
    MApp_ZUI_API_SetTimer(HWND_PVR_WARNING_MESSAGE_PANE, 0, 1500); //aoto close the warning message
    //_MApp_ZUI_API_WindowProcOnIdle(); //force paint to scren...
}

BOOLEAN MApp_ZUI_ACT_PVR_Check_Switch_Channel(MEMBER_SERVICETYPE NewCMType, U16 u16NewPos)
{
    BYTE cRF1, cRF2;

    MEMBER_SERVICETYPE CurCMType = msAPI_CM_GetCurrentServiceType();
    U16 u16CurPos = msAPI_CM_GetCurrentPosition(CurCMType);

    cRF1 = msAPI_CM_GetPhysicalChannelNumber(CurCMType, u16CurPos);
    cRF2 = msAPI_CM_GetPhysicalChannelNumber(NewCMType, u16NewPos);

    PVR_ZUI_DBG(printf("CurCMType=%d\n",CurCMType));
    PVR_ZUI_DBG(printf("u16CurPos=%d\n",u16CurPos));
    PVR_ZUI_DBG(printf("NewCMType=%d\n",NewCMType));
    PVR_ZUI_DBG(printf("u16NewPos=%d\n",u16NewPos));
    PVR_ZUI_DBG(printf("cRF1=%d\n",cRF1));
    PVR_ZUI_DBG(printf("cRF2=%d\n",cRF2));

    if(((E_PVR_STATE_RECORD == MApp_PVR_StateMachineGet() || E_PVR_STATE_RECORDnPLAYBACK == MApp_PVR_StateMachineGet())
        && (E_RECORD_STATE_RECORDING == MApp_Record_StateMachineGet()))
        ||((E_PVR_STATE_TIMESHIFT== MApp_PVR_StateMachineGet())
        && (E_TIMESHIFT_STATE_RECORDING == MApp_TimeShift_StateMachineGet()||E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING == MApp_TimeShift_StateMachineGet())))
    {
        PvrNewCMType = NewCMType;
        PvrNewPos = u16NewPos;

        if(MApp_ZUI_GetActiveOSD() != E_OSD_PVR)
        {
            MApp_ZUI_ACT_ShutdownOSD();
            MApp_ZUI_ACT_StartupOSD(E_OSD_PVR);
        }

        MApp_ZUI_API_SetTimer(HWND_PVR_WARNING_DLG_PANE, 0, 5000); //auto close the warning message
        MApp_ZUI_API_ShowWindow(HWND_PVR_WARNING_DLG_PANE, SW_SHOW);
        MApp_ZUI_API_SetFocus(HWND_PVR_WARNING_DLG_CONFIRM_BTN_CANCEL);

        return FALSE;
    }

    if ((cRF1 != cRF2)
        && (E_PVR_STATE_RECORD == MApp_PVR_StateMachineGet() || E_PVR_STATE_RECORDnPLAYBACK == MApp_PVR_StateMachineGet())
        && (E_RECORD_STATE_RECORDING == MApp_Record_StateMachineGet()))
    {
        PvrNewCMType = NewCMType;
        PvrNewPos = u16NewPos;

        if(MApp_ZUI_GetActiveOSD() != E_OSD_PVR)
        {
            MApp_ZUI_ACT_ShutdownOSD();
            MApp_ZUI_ACT_StartupOSD(E_OSD_PVR);
        }

        MApp_ZUI_API_SetTimer(HWND_PVR_WARNING_DLG_PANE, 0, 5000); //auto close the warning message
        MApp_ZUI_API_ShowWindow(HWND_PVR_WARNING_DLG_PANE, SW_SHOW);
        MApp_ZUI_API_SetFocus(HWND_PVR_WARNING_DLG_CONFIRM_BTN_CANCEL);

        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

void MApp_ZUI_ACT_PVR_Record_TickInfo(void)
{
    PVR_ZUI_DBG(printf("MApp_ZUI_ACT_PVR_Record_TickInfo\n"));
#ifdef PVR_UTOPIA
    MApp_ZUI_API_InvalidateWindow(HWND_PVR_RECORDING_SYSTEM_CLOCK);
    MApp_ZUI_API_InvalidateWindow(HWND_PVR_RECORDING_RECORD_TIME_TEXT);
    MApp_ZUI_API_InvalidateWindow(HWND_PVR_RECORDING_DISK_REMAIN);
#else
    MApp_ZUI_API_InvalidateWindow(HWND_PVR_RECORDING_SYSTEMCLOCK);
    MApp_ZUI_API_InvalidateWindow(HWND_PVR_RECORDING_TIME);
    MApp_ZUI_API_InvalidateWindow(HWND_PVR_RECORDING_DISK_REMAIN);
#endif
}

void MApp_ZUI_ACT_PVR_TimeShift_TickInfo(void)
{
    PVR_ZUI_DBG(printf("MApp_ZUI_ACT_PVR_TimeShift_TickInfo\n"));
#ifdef PVR_UTOPIA
    MApp_ZUI_API_InvalidateWindow(HWND_PVR_TIMESHIFT_SYSTEM_CLOCK);
    MApp_ZUI_API_InvalidateWindow(HWND_PVR_TIMESHIFT_PERCENTAGE_BAR);
    MApp_ZUI_API_InvalidateWindow(HWND_PVR_TIMESHIFT_PLAYBACK_TIME_TXT);
#else
    MApp_ZUI_API_InvalidateWindow(HWND_PVR_TIMESHIFT_SYSTEMCLOCK);
    MApp_ZUI_API_InvalidateWindow(HWND_PVR_TIMESHIFT_PERCENTAGE_BAR);
    MApp_ZUI_API_InvalidateWindow(HWND_PVR_TIMESHIFT_PLAYBACK_TIME_TXT);
#endif
}

void MApp_ZUI_ACT_PVR_TimeShift_TickInfo_Brief(void)
{
    PVR_ZUI_DBG(printf("MApp_ZUI_ACT_PVR_TimeShift_TickInfo_Brief\n"));
#ifndef PVR_UTOPIA
    MApp_ZUI_API_InvalidateWindow(HWND_PVR_TIMESHIFT_PLAYBACK_TIME_BRIEF_TXT);
#endif
}

void MApp_ZUI_ACT_PVR_CheckFS_PopUIPage(U8 pageId)
{
    switch(pageId)
    {
        case MENU_PVR_CHECKFS_CREATE_PARTITION_MSG:
            MApp_ZUI_API_ShowWindow(HWND_PVR_CREATE_PARTITION_PANE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_PVR_CREATE_PARTITION_CONFIRM_BTN_CANCEL);
            break;

        case MENU_PVR_CHECKFS_FORMAT_DISK_CHECK_MSG:
            MApp_ZUI_API_ShowWindow(HWND_PVR_FILE_SYSTEM_SETTING_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_FORMAT_DISK_CHECK_PANE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_PVR_FORMAT_DISK_CHECK_CONFIRM_BTN_CANCEL);
            break;

        case MENU_PVR_CHECKFS_SELECT_DISK_MSG:
            MApp_ZUI_API_ShowWindow(HWND_PVR_SELECT_DISK_PANE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_PVR_SELECT_DISK_USB);
            MApp_ZUI_API_ShowWindow(HWND_PVR_BG_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_FILE_SYS_PAGE_LIST, SW_HIDE);
            break;

        case MENU_PVR_CHECKFS_FORMAT_SETTING_MSG:
            MApp_ZUI_API_ShowWindow(HWND_PVR_FORMAT_DISK_CHECK_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_FILE_SYSTEM_SETTING_PANE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_PVR_FILE_SYSTEM_SETTING_TYPE_ITEM);
            #ifdef OBAMA
            g_u8PvrFormatFsType = PVR_FS_LINUX_FAT; //set default to FAT32, must link with UI'ssetting
            #else
            g_u8PvrFormatFsType = PVR_FS_N51FAT32; //set default to N51FAT32, must link with UI'ssetting
            #endif
            MApp_ZUI_API_EnableWindow(HWND_PVR_FILE_SYSTEM_SIZE_ITEM, DISABLE);
            MApp_ZUI_API_InvalidateWindow(HWND_PVR_FILE_SYSTEM_SETTING_PANE);
            break;
/*
        case MENU_PVR_CHECKFS_SET_FILE_SYSTEM_SIZE_MSG:
            if( MApp_ZUI_API_IsWindowVisible(HWND_PVR_CREATE_PARTITION_PANE))
                MApp_ZUI_API_ShowWindow(HWND_PVR_CREATE_PARTITION_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_FILE_SYSTEM_SETTING_PANE, SW_SHOW);

            MApp_ZUI_API_ShowWindow(HWND_PVR_BG_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_FILE_SYS_PAGE_LIST, SW_HIDE);

            MApp_ZUI_API_SetFocus(HWND_PVR_FILE_SYSTEM_SIZE_ITEM);
            break;
*/
        case MENU_PVR_CHECKFS_FORMAT_PROGRESS_MSG:
            MApp_ZUI_API_ShowWindow(HWND_PVR_FORMAT_DISK_CHECK_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_FORMAT_DISK_PANE, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_CREATE_PVR_FILE_SYSTEM_PLEASE_WAIT_TXT, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_FILE_SYSTEM_SETTING_PANE, SW_HIDE);

            MApp_ZUI_API_ShowWindow(HWND_PVR_BG_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_FILE_SYS_PAGE_LIST, SW_HIDE);
            break;

        case MENU_PVR_CHECKFS_SET_TMSHFT_SIZE_MSG:
            if( MApp_ZUI_API_IsWindowVisible(HWND_PVR_FORMAT_DISK_PANE))
                MApp_ZUI_API_ShowWindow(HWND_PVR_FORMAT_DISK_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_TIME_SHIFT_SIZE_PANE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_PVR_TIME_SHIFT_DISK_SIZE_ITEM);
            break;

        default:
            break;
    }
}

void MApp_ZUI_ACT_PVR_GOTO_MAINMENU(U8 pageIdx, U8 itemIdx)
{
    if( pageIdx != MENU_PVR_CHECKFS_MAIN )
        return;

    switch(itemIdx)
    {
        case PVR_CHECKFS_ITEM_SELECT_DISK:
            MApp_ZUI_API_ShowWindow(HWND_PVR_SELECT_DISK_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_BG_PANE, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_FILE_SYS_PAGE_LIST, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_PVR_SELECT_DISK_ITEM);
            break;

        case PVR_CHECKFS_ITEM_CHECK_FILE_SYSTEM:
            MApp_ZUI_API_ShowWindow(HWND_PVR_CREATE_PARTITION_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_PVR_FORMAT_DISK_CHECK_PANE, SW_HIDE);
            g_PVRCheckFSStatus = EN_PVR_CHKSTS_INITIAL;
            MApp_ZUI_API_SetFocus(HWND_PVR_CHECK_FILE_SYS_ITEM);
            break;

        case PVR_CHECKFS_ITEM_CHECK_DISK://no run
            break;

        case PVR_CHECKFS_ITEM_CHECK_FORMAT:
            MApp_ZUI_API_ShowWindow(HWND_PVR_FILE_SYSTEM_SETTING_PANE, SW_HIDE);

            g_PVRCheckFSStatus = EN_PVR_CHKSTS_INITIAL;

            MApp_ZUI_API_ShowWindow(HWND_PVR_BG_PANE, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_FILE_SYS_PAGE_LIST, SW_SHOW);

            MApp_ZUI_API_SetFocus(HWND_PVR_FORMAT_ITEM);
            break;

        case PVR_CHECKFS_ITEM_CHECK_TIMESHIFT_SIZE:
            MApp_ZUI_API_ShowWindow(HWND_PVR_TIME_SHIFT_SIZE_PANE, SW_HIDE);

            g_PVRCheckFSStatus = EN_PVR_CHKSTS_INITIAL;

            MApp_ZUI_API_ShowWindow(HWND_PVR_BG_PANE, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PVR_FILE_SYS_PAGE_LIST, SW_SHOW);

            MApp_ZUI_API_SetFocus(HWND_PVR_TIME_SHIFT_ITEM);
            break;

        case PVR_CHECKFS_ITEM_CHECK_SPEED://no run
            break;

        default:
            break;
    }

}

void MApp_ZUI_ACT_PVR_CheckFS_UpdateUI(void)
{
    MApp_ZUI_API_InvalidateWindow(HWND_PVR_CHECK_FILE_SYS_OPTION);
    MApp_ZUI_API_InvalidateWindow(HWND_PVR_USB_DISK_OPTION);
    MApp_ZUI_API_InvalidateWindow(HWND_PVR_FORMAT_OPTION);
    MApp_ZUI_API_InvalidateWindow(HWND_PVR_TIME_SHIFT_OPTION);
    MApp_ZUI_API_InvalidateWindow(HWND_PVR_SPEED_OPTION);
    if(g_PVRCheckFSStatus >= EN_PVR_CHKSTS_CHECK_SPEED_PASS)
    {
        MApp_ZUI_API_ShowWindow(HWND_PVR_SPEED_CHECK_SPEED_PERCENTAGE_BAR, SW_SHOW);
        MApp_ZUI_API_ShowWindow(HWND_PVR_SPEED_CHECK_SPEED_TAG_OPTION, SW_SHOW);
    }
    else if(g_PVRCheckFSStatus == EN_PVR_CHKSTS_CHECK_SPEED_START)
    {
        MApp_ZUI_API_EnableWindow(HWND_PVR_SPEED_ITEM,TRUE);
        MApp_ZUI_API_ShowWindow(HWND_PVR_SPEED_CHECK_SPEED_PERCENTAGE_BAR, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_PVR_SPEED_CHECK_SPEED_TAG_OPTION, SW_HIDE);
    }
    else
    {
        MApp_ZUI_API_EnableWindow(HWND_PVR_SPEED_ITEM,FALSE);
        MApp_ZUI_API_ShowWindow(HWND_PVR_SPEED_CHECK_SPEED_PERCENTAGE_BAR, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_PVR_SPEED_CHECK_SPEED_TAG_OPTION, SW_HIDE);
    }
    _MApp_ZUI_API_WindowProcOnIdle();
    //MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_PVR_FORMAT_PROGRESS);
}

BOOLEAN MApp_ZUI_ACT_RecordPageActive(void)
{
    if (MApp_ZUI_GetActiveOSD() == E_OSD_PVR)
    {
        if (g_PvrMenuPageType == MENU_PVR_RECORD ||
            g_PvrMenuPageType == MENU_PVR_RECORDING_BRIEF ||
            g_PvrMenuPageType == MENU_PVR_TIME_SHIFT||
            g_PvrMenuPageType == MENU_PVR_TIME_SHIFT_BRIEF||
            g_PvrMenuPageType == MENU_PVR_RECORD_CHANNEL_CHANGE_CHECK )
            return TRUE;
    }
    return FALSE;
}

GUI_ENUM_DYNAMIC_LIST_STATE MApp_ZUI_ACT_QueryPvrFileSysStatus(HWND hwnd)
{
    switch(hwnd)
    {
        case HWND_PVR_SELECT_DISK_ITEM:
        case HWND_PVR_CHECK_FILE_SYS_ITEM:
        case HWND_PVR_FORMAT_ITEM:
        case HWND_PVR_TIME_SHIFT_ITEM:
        case HWND_PVR_FREE_REC_LIMIT_ITEM:
             return EN_DL_STATE_NORMAL;

        case HWND_PVR_USB_DISK_ITEM:
        case HWND_PVR_SPEED_ITEM:
            return  EN_DL_STATE_DISABLED;
        #if(ENABLE_TIMESHIT==DISABLE)
        case HWND_PVR_RECORDING_ICON_PLAY:
            return EN_DL_STATE_DISABLED;
        #endif


        case HWND_PVR_RECORDING_ICON_FB:
        case HWND_PVR_RECORDING_ICON_FF:
        case HWND_PVR_RECORDING_ICON_NEXT:
        case HWND_PVR_RECORDING_ICON_PREV:
        case HWND_PVR_RECORDING_ICON_PAUSE:
            return EN_DL_STATE_DISABLED;

        case HWND_PVR_PLAY_ICON_NEXT:
        case HWND_PVR_PLAY_ICON_PREV:
        {
        //if (MApp_PVR_StateMachineGet() ==  E_PVR_STATE_PLAYBACK)
            //return EN_DL_STATE_NORMAL;
        //else
            return EN_DL_STATE_DISABLED;
        }

        case HWND_PVR_TIMESHIFT_ICON_FB:
        case HWND_PVR_TIMESHIFT_ICON_FF:
        case HWND_PVR_TIMESHIFT_ICON_PAUSE:
        {
              return EN_DL_STATE_DISABLED;
              }

        case HWND_PVR_TIMESHIFT_ICON_NEXT:
        case HWND_PVR_TIMESHIFT_ICON_PREV:
        {
            return EN_DL_STATE_DISABLED;
        }

        case HWND_PVR_PLAY_ICON_FB:
        case HWND_PVR_PLAY_ICON_FF:
        {
        #if(ENABLE_PVR_BROWSER)
            if(MApp_UiPvr_Browser_GetPlayingServiceType() == E_SERVICETYPE_RADIO)
                return EN_DL_STATE_DISABLED;
            else
        #endif
                return EN_DL_STATE_NORMAL;

        }
        break;

        default:
            return EN_DL_STATE_NORMAL;
    }
}

BOOLEAN MApp_ZUI_ACT_CheckPvrBypassKey(U8 checkedKey)
{
    if(MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_DLG_PANE))
    {
        if(checkedKey == KEY_RIGHT||
           checkedKey == KEY_LEFT ||
           checkedKey == KEY_SELECT)
           return TRUE;
    }

    return FALSE;
}
#endif //#if(ENABLE_PVR ==1)
#undef MAPP_ZUI_ACTPVR_C
