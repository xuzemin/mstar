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
// (MStar Confidential Information) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define MAPP_ZUI_ACTMENUFUNC_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include <string.h>
#include "Board.h"

// Common Definition
#include "MsCommon.h"
#include "apiXC.h"
#include "msAPI_Timer.h"
#include "apiAUDIO.h"
#include"msAPI_VD.h"
#include "msAPI_Video.h"
#include "apiGOP.h"

#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "ZUI_tables_h.inl"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_ZUI_ACTmainpage.h"
#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_APIdraw.h"
#include "MApp_ZUI_ACTglobal.h"
#include "OSDcp_String_EnumIndex.h"
#include "ZUI_exefunc.h"
#include "MApp_ZUI_ACTmenufunc.h"
#include"MApp_ZUI_ACTcoexistWin.h"
#include "apiXC_Sys.h"
#include "apiXC_Adc.h"
#include "apiAUDIO.h"
#include "MApp_Menu_Main.h"
#include "MApp_DMP_Main.h"
#include "mapp_videoplayer.h"
#include "MApp_UiMenuDef.h"
#include "msAPI_Mode.h"
#include "apiXC_Ace.h"
#include "MApp_Scaler.h"
#include "MApp_XC_PQ.h"
#include "MApp_GlobalFunction.h"
#include "MApp_MVDMode.h"
#if MHEG5_ENABLE
#include "msAPI_MHEG5.h"
#include "MApp_MHEG5_Main.h"
#endif
#include "MApp_MultiTasks.h"
#include "MApp_BlockSys.h"
#include "MApp_Audio.h"
#include "MApp_Sleep.h"
#include "MApp_PCMode.h"
#include "MApp_DataBase.h"
#include "MApp_ChannelChange.h"
#include "apiXC_Hdmi.h"
#if ENABLE_PVR
#include "MApp_TimeShift.h"
#include "MApp_Playback.h"
#endif

#if ENABLE_DVB//(ENABLE_DTV)
//#include "mapp_demux.h"
//#include "mapp_si.h"
#include "MApp_Dvb_SI.h" // "mapp_si.h"
#include "msAPI_FreqTableDTV.h"
#endif

#if ENABLE_DVB_T2
#include "MApp_Scan.h"
#endif
#if (ENABLE_CI_PLUS)
#include "MApp_CIMMI.h"
#endif
#include "MApp_SaveData.h"
#include "msAPI_audio.h"

#if (BRAZIL_CC)
#include "mapp_closedcaption.h"
#endif

#if ENABLE_CI
#include "msAPI_CI.h"
#endif
#include "MApp_Version.h"
#include "drvpower_if.h"
#include "MApp_PVR.h"
//#if (ENABLE_PIP)
#include "MApp_InputSource.h" //switch audio source when enable pip mode
//#endif
#if ENABLE_TTX
#include "mapp_ttx.h"
#endif
#if (MWE_FUNCTION)
#include "apiXC_Ace.h"
#endif
#include "MApp_ZUI_ACTnetconfig.h"
#include "MApp_CustomerInfoInclude.h"

#include "drvGPIO.h"  // anvi22
#if ENABLE_DMP
#include "mapp_mplayer.h"
#endif


#if (ENABLE_PIP)
#include "MApp_PIP.h"
#endif

#include "drvPQ.h"
#include "drvIPAUTH.h"

#if ENABLE_DVBC
#include "MApp_CADTV_Proc.h"
#endif

#if (ENABLE_NEW_AUTO_NR)
#include "msAPI_NR.h"
#endif

#include "MApp_CharTable.h"

#if ENABLE_MFC_6M20
#include "drvUrsaMFCAPI.h"
#endif
#if ENABLE_MFC_6M30
#include "drvUrsa6M30.h"
#endif

#if(ENABLE_3D_PROCESS)
#include "apiXC.h"
#endif
#if ENABLE_CEC
#include "msAPI_CEC.h"
#include "apiCEC.h"
#endif
#if ENABLE_S2
#include "MApp_ZUI_GlobalFunction.h"
#endif
#include "MApp_GlobalVar.h"
#include "MApp_MenuFunc.h"
#include "MApp_TV.h"

#if ENABLE_ATSC
#include "MApp_Psip.h"

#if ENABLE_ATSC_MENU_UI
#include "MApp_ZUI_ACTmenufunc_ATSC.c"
#include "MApp_Scan_ATSC.h"
#include "MApp_UiMenuFunc_ATSC.h"
#include "MApp_ChannelProc_ATSC.h"
#endif
#if ENABLE_ATSC_SCAN_NEW_MODE
#include "MApp_Scan.h"
#endif
#endif

#if ENABLE_ATSC_TTS
#include "msAPI_Global.h"
#include "MApp_TTSControlHandler.h"
#include "MApp_TTS_Cus.h"
#include "MApp_TTS_Cus_Say.h"
#endif

#if((ATSC_CC == ATV_CC)||(ATSC_CC == DTV_CC)||ENABLE_ISDB_ATV_VCHIP)
#include "MApp_VChip.h"
#endif


#include "MApp_ZUI_ACTsetclockfunc.h"
#include "MApp_ParentalRating.h"
#include "MApp_TopStateMachine.h"
#include "MApp_NoOperate_AutoSleep.h"

#include "MApp_Func_HDMI.h"
#if ENABLE_GAMMA_ADJUST
#include "MApp_GammaAdjust.h"
#endif
#if (ENABLE_HDR)
#include "MApp_HDR.h"
#include "msAPI_HDR.h"
#endif
extern U16 _MApp_ZUI_ACT_GetPictureModeStringID(void);
extern EN_MENU_STATE enMainMenuState;
extern U32 u32ProtectOffTimer;
extern BOOLEAN bStopMonitorBlock;
extern BOOLEAN bParentalPWPassCheck;
extern unsigned char code Customer_hash[];
extern unsigned char Customer_info[];
extern void MApp_SetListMenuLanguage(U8 Direction);
extern U8 MApp_ZUI_ACT_GetOsdAudLangIndexMax(void);
/////////////////////////////////////////////////////////////////////
static const char SWVersionName[]      = _CODE_MAIN_VERSION_;
static const char SWCompileDate[]      = {_CODE_DATE_};
static const char SWCompileTime[]      = {_CODE_TIME_};

#if (ENABLE_ATSC_TTS)
#define CAHNNEL_SCAN_STATUS_TIMER (30*1000)
#endif
#if ENABLE_KEY_TO_SPEECH
#define KTS_TEXT_WORDS_LENGTH   10
#endif

#if (ENABLE_EWS)

BOOLEAN bEWS_Vaild=FALSE;
BOOLEAN bNeedShowEWS=TRUE;
BOOLEAN bFROM_ChannelMenu=FALSE;

U8 u8Temp_EWS_Num1 = 0;
U8 u8Temp_EWS_Num2 = 0;
U8 u8Temp_EWS_Num3 = 0;
U8 u8Temp_EWS_Num4 = 0;
U8 u8Temp_EWS_Num5 = 0;
#endif

//////////////////////////////////////////////////////////////////////
#if ENABLE_AUTOTEST
extern BOOLEAN g_bAutobuildDebug;
#endif
U16 tempcheck2 =0;
U16 tempcheck3 =0;

// 4
U16 PicMode =0;
U16 PicContrast =0;
U16 PicBright =0;
U16 PicColor =0;
U16 PicSharpness =0;
U16 PicTint =0;

U16 ColorTem =0;
U16 ColorR =0;
U16 ColorG =0;
U16 ColorB =0;

U16 AspectR =0;
U16 NoiseR =0;
U16 MPEGNoiseR =0;

// 5
U16 SoundMenu =0;
U16 SoundMenuT =0;
U16 SoundMenuB =0;
U16 AutoVolume =0;
U16 SurroundSound =0;

//6
U16 OSDClock =0;
U16 OffTime =0;
U16 OnTime =0;

U16 AutoSleep =0;
U16 TimeZone =0;

// 7
U16 OSD_L =0;
U16 Audio_L =0;
U16 Subtitle_L =0;
U16 Headphone_L =0;

//8
U16 LockS =0;
U16 ParentalG =0;

#if ENABLE_CEC  //  anvi cec
U8* u8HDMI_CEC_DevicesName[10];
U8 u8HDMI_CEC_Devices_Count = 0;

#define CEC_DEVICES_COUNT  10
HWND _ZUI_TBLSEG hdmi_cec_UI_list[CEC_DEVICES_COUNT] =
{
    HWND_MENU_HDMI_CEC_DEVICE_LIST_A,
    HWND_MENU_HDMI_CEC_DEVICE_LIST_B,
    HWND_MENU_HDMI_CEC_DEVICE_LIST_C,
    HWND_MENU_HDMI_CEC_DEVICE_LIST_D,
    HWND_MENU_HDMI_CEC_DEVICE_LIST_E,
    HWND_MENU_HDMI_CEC_DEVICE_LIST_F,
    HWND_MENU_HDMI_CEC_DEVICE_LIST_G,
    HWND_MENU_HDMI_CEC_DEVICE_LIST_H,
    HWND_MENU_HDMI_CEC_DEVICE_LIST_I,
    HWND_MENU_HDMI_CEC_DEVICE_LIST_J,
};
#define CEC_DEVICE_REFRESH_TIME         5000
#endif


extern EN_MENU_STATE _enTargetMenuState;
extern U16 MApp_ZUI_ACT_GetTimezoneStringID(EN_MENU_TIMEZONE timezone);
extern U16 MApp_ZUI_ACT_GetCountryStringID(EN_OSD_COUNTRY_SETTING country);
extern LPTSTR MApp_ZUI_ACT_GetMenuLanguageStringByIndex(U8 u8Index);


#if (ENABLE_ATSC)
#define VCHIP_MPAA_ITEMNUM 7
#define VCHIP_CANADAENG_ITEMNUM 7
#define VCHIP_CANADAFRE_ITEMNUM 6

const HWND _MenuChannelListHwndList[MAX_NUM_OF_SRV_ITEM]=
{
    HWND_MENU_CHANNEL_LIST_ITEM0,
    HWND_MENU_CHANNEL_LIST_ITEM1,
    HWND_MENU_CHANNEL_LIST_ITEM2,
    HWND_MENU_CHANNEL_LIST_ITEM3,
    HWND_MENU_CHANNEL_LIST_ITEM4,
    HWND_MENU_CHANNEL_LIST_ITEM5,
    HWND_MENU_CHANNEL_LIST_ITEM6,
    HWND_MENU_CHANNEL_LIST_ITEM7,
    HWND_MENU_CHANNEL_LIST_ITEM8,
    HWND_MENU_CHANNEL_LIST_ITEM9
};

static const HWND _ZUI_TBLSEG _RRTDimensionHwndList[]=
{
    HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM0,
    HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM1,
    HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM2,
    HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM3,
    HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM4,
    HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM5,
    HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM6,
    HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM7,
    HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM8,
    HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM9
};

static const HWND _ZUI_TBLSEG _RRTDimensionTextHwndList[]=
{
    HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM0_TEXT,
    HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM1_TEXT,
    HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM2_TEXT,
    HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM3_TEXT,
    HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM4_TEXT,
    HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM5_TEXT,
    HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM6_TEXT,
    HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM7_TEXT,
    HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM8_TEXT,
    HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM9_TEXT
};


const HWND _ZUI_TBLSEG _RRTAdjustHwndList[]=
{
    HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM0,
    HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM1,
    HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM2,
    HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM3,
    HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM4,
    HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM5,
    HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM6,
    HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM7,
    HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM8,
    HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM9,
};

static const HWND _MenuRRTAdjPageTextHwndList[]=
{
    HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM0_TEXT,
    HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM1_TEXT,
    HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM2_TEXT,
    HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM3_TEXT,
    HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM4_TEXT,
    HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM5_TEXT,
    HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM6_TEXT,
    HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM7_TEXT,
    HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM8_TEXT,
    HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM9_TEXT
};

static const HWND _ZUI_TBLSEG _lock_source_items[] =
{
    HWND_MENU_LOCK_INPUTBLOCKSUBPAGE_ITEM_TV,

#if (INPUT_AV_VIDEO_COUNT >= 1)
    HWND_MENU_LOCK_INPUTBLOCKSUBPAGE_ITEM_AV,
#endif

#if (INPUT_SV_VIDEO_COUNT >= 2)
    HWND_MENU_LOCK_INPUTBLOCKSUBPAGE_ITEM_SVIDEO,
#endif

#if (INPUT_YPBPR_VIDEO_COUNT>=1)
    HWND_MENU_LOCK_INPUTBLOCKSUBPAGE_ITEM_COMPONENT,
#endif

#if (ENABLE_HDMI)
    HWND_MENU_LOCK_INPUTBLOCKSUBPAGE_ITEM_HDMI,
#endif

    HWND_MENU_LOCK_INPUTBLOCKSUBPAGE_ITEM_PC
};

//for no RRT name/dimenstion
const U8 gStrRRTDefaultName[2][13]=
{
    {'D', 'i', 'm', 'e', 'n', 's', 'i', 'o', 'n', ' ', '0', '0', '\0'},
    {'L', 'e', 'v', 'e', 'l', ' ', '0', '0', '\0'},
};


static const HWND _MenuRRTAdjPageOptionHwndList[]=
{
    HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM0_OPTION,
    HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM1_OPTION,
    HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM2_OPTION,
    HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM3_OPTION,
    HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM4_OPTION,
    HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM5_OPTION,
    HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM6_OPTION,
    HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM7_OPTION,
    HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM8_OPTION,
    HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM9_OPTION
};

HWND _MApp_ZUI_ACT_MenuChannelListIdMapToWindow(U8 u8Index)
{
    return _MenuChannelListHwndList[u8Index];
}

HWND _MApp_ZUI_ACT_RRTDimensionIdMapToWindow(U8 u8Index)
{
    return _RRTDimensionHwndList[u8Index];
}

U8 _MApp_ZUI_ACT_RRTDimensionWindowMapToIndex(HWND hwnd)
{
    U8 i;
    U8 u8Num = COUNTOF(_RRTDimensionHwndList);
    for (i = 0; i < u8Num; i++)
    {
        if (hwnd == _RRTDimensionHwndList[i] ||
            MApp_ZUI_API_IsSuccessor(_RRTDimensionHwndList[i], hwnd))
        {
            return i;
        }
    }
    return 0;
}

U8 _MApp_ZUI_ACT_RRTAdjustWindowMapToIndex(HWND hwnd)
{
    U8 i;
    U8 u8Num = MAX_NUM_OF_RRT_ITEM;
    for (i = 0; i < u8Num; i++)
    {
        if (hwnd == _RRTAdjustHwndList[i] ||
            MApp_ZUI_API_IsSuccessor(_RRTAdjustHwndList[i], hwnd))
        {
            return i;
        }
    }
    return 0;
}
#endif

#if ENABLE_3D_PROCESS
void _MApp_ZUI_ACT_DecInc_3D_AspectRatio_Cycle(BOOLEAN bInc)
{
    if (bInc)
    {
        switch(ST_VIDEO.eAspectRatio)
        {
            case EN_AspectRatio_Original:
                ST_VIDEO.eAspectRatio = EN_AspectRatio_16X9;
                break;
            /*case EN_AspectRatio_16X9:
                ST_VIDEO.eAspectRatio = EN_AspectRatio_JustScan;
                break;*/
            case EN_AspectRatio_16X9:
                ST_VIDEO.eAspectRatio = EN_AspectRatio_Original;
                break;
            default:
                ST_VIDEO.eAspectRatio = EN_AspectRatio_Original;
                break;
        }
    }
    else
    {
        switch(ST_VIDEO.eAspectRatio)
        {
            /*case EN_AspectRatio_JustScan:
                ST_VIDEO.eAspectRatio = EN_AspectRatio_16X9;
                break;*/
            case EN_AspectRatio_16X9:
                ST_VIDEO.eAspectRatio = EN_AspectRatio_Original;
                break;
            case EN_AspectRatio_Original:
                ST_VIDEO.eAspectRatio = EN_AspectRatio_16X9;
                break;
            default:
                ST_VIDEO.eAspectRatio = EN_AspectRatio_Original;
                break;
        }
    }
    MApp_Scaler_EnableOverScan(TRUE);
#if ENABLE_PVR
    if(IsDTVInUse()
        &&(((MApp_PVR_StateMachineGet() == E_PVR_STATE_TIMESHIFT) &&(MApp_TimeShift_StateMachineGet()== E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING))
                ||((MApp_PVR_StateMachineGet() == E_PVR_STATE_RECORDnPLAYBACK || (MApp_PVR_StateMachineGet() == E_PVR_STATE_PLAYBACK)) &&(MApp_Playback_StateMachineGet()== E_PLAYBACK_STATE_PAUSE)))
        && !MApi_XC_IsCurrentFrameBufferLessMode()
        && MApi_XC_IsFreezeImg(MAIN_WINDOW))//switch Aspect ratio when Pause, 4:3 mode will in garbage. because DNR memory changed.
        {
            MApi_XC_FreezeImg(FALSE, MAIN_WINDOW);
            MApp_Scaler_Setting_SetVDScale( ST_VIDEO.eAspectRatio , MAIN_WINDOW );
            msAPI_Timer_Delayms(200);
            MApi_XC_FreezeImg(TRUE, MAIN_WINDOW);
        }
        else
 #endif
        {
            MApp_Scaler_Setting_SetVDScale( ST_VIDEO.eAspectRatio , MAIN_WINDOW );
        }

}
#endif

#define DEBUG_AS_CYCLE(x)   //x
void _MApp_ZUI_ACT_DecIncAspectRatio_Cycle(BOOLEAN bInc)
{
    DEBUG_AS_CYCLE(printf("_MApp_ZUI_ACT_DecIncAspectRatio_Cycle(bInc=%u)\n", bInc););
    DEBUG_AS_CYCLE(printf("ST_VIDEO.eAspectRatio=%u\n", ST_VIDEO.eAspectRatio););

#if 1
    EN_MENU_AspectRatio aeAspectRatioUiOrder[] =
    {
        EN_AspectRatio_Original,
        EN_AspectRatio_4X3,
        EN_AspectRatio_16X9,
        EN_AspectRatio_Zoom1,
        EN_AspectRatio_Zoom2,
        EN_AspectRatio_JustScan,
        EN_AspectRatio_Panorama,
        EN_AspectRatio_Point_to_Point,
    };

    #define UI_AspectRatioTable_NUM (sizeof(aeAspectRatioUiOrder)/sizeof(EN_MENU_AspectRatio))


    U8 u8CurUiAspectRatio = ST_VIDEO.eAspectRatio;
    EN_MENU_AspectRatio eNewUiAspectRatio;
    U8 u8CurIndex;
    U8 i;
    U8 u8NewIndex;


    if (MApp_IsImageFrozen())
    {
        MApp_SetImageFrozen(FALSE);
        MApi_XC_FreezeImg(FALSE, MAIN_WINDOW);

    }


    DEBUG_AS_CYCLE( printf("u8CurUiAspectRatio=%u\n", u8CurUiAspectRatio); );

    // Find out current index
    for( u8CurIndex = 0; u8CurIndex < UI_AspectRatioTable_NUM; ++ u8CurIndex )
    {
        if( aeAspectRatioUiOrder[u8CurIndex] == u8CurUiAspectRatio )
            break;
    }

    if( u8CurIndex >= UI_AspectRatioTable_NUM )
        u8CurIndex = 0;

    DEBUG_AS_CYCLE( printf("u8CurIndex=%u\n", u8CurIndex); );

    // Adjust to next
    u8NewIndex = u8CurIndex;
    for( i = 0; i < UI_AspectRatioTable_NUM; ++ i )
    {
        if( bInc ) // Up ==> --
        {
            if( u8NewIndex == 0 )
                u8NewIndex = UI_AspectRatioTable_NUM-1;
            else
                u8NewIndex -= 1;
        }
        else // Down ==> ++
        {
            if( u8NewIndex == UI_AspectRatioTable_NUM-1 )
                u8NewIndex = 0;
            else
                u8NewIndex += 1;
        }
        DEBUG_AS_CYCLE( printf("u8NewIndex=%u\n", u8NewIndex); );

        eNewUiAspectRatio = aeAspectRatioUiOrder[u8NewIndex];
        DEBUG_AS_CYCLE( printf("eNewUiAspectRatio=%u\n", eNewUiAspectRatio); );

        // Check if support this
        if( MApp_Scaler_Is_AspectRatioSupported_ByUI(eNewUiAspectRatio) )
            break;

        DEBUG_AS_CYCLE( printf("%u Unsupport! find next \n", i ); );

    }

    ST_VIDEO.eAspectRatio = eNewUiAspectRatio;
    DEBUG_AS_CYCLE( printf("Final ST_VIDEO.eAspectRatio=%u\n", ST_VIDEO.eAspectRatio); );

#else

    if (IsVgaInUse())
    {
        if (bInc)
        {
           switch(ST_VIDEO.eAspectRatio)
            {
               case EN_AspectRatio_4X3:
                  ST_VIDEO.eAspectRatio = EN_AspectRatio_Point_to_Point;
                  break;
               case EN_AspectRatio_Point_to_Point:
                  ST_VIDEO.eAspectRatio = EN_AspectRatio_JustScan;
                  break;
               case EN_AspectRatio_JustScan:
                  ST_VIDEO.eAspectRatio = EN_AspectRatio_16X9;
                  break;
               case EN_AspectRatio_16X9:
                  ST_VIDEO.eAspectRatio = EN_AspectRatio_4X3;
                  break;
               default:
                 ST_VIDEO.eAspectRatio = EN_AspectRatio_16X9;
                 break;
            }
        }
        else
        {
            switch(ST_VIDEO.eAspectRatio)
            {
               case EN_AspectRatio_4X3:
                  ST_VIDEO.eAspectRatio = EN_AspectRatio_16X9;
                  break;
               case EN_AspectRatio_16X9:
                  ST_VIDEO.eAspectRatio = EN_AspectRatio_JustScan;
                  break;
               case EN_AspectRatio_JustScan:
                  ST_VIDEO.eAspectRatio = EN_AspectRatio_Point_to_Point;
                  break;
               case EN_AspectRatio_Point_to_Point:
                  ST_VIDEO.eAspectRatio = EN_AspectRatio_4X3;
                  break;
               default:
                 ST_VIDEO.eAspectRatio = EN_AspectRatio_16X9;
                 break;
            }
        }
    }
   else if(IsStorageInUse())
   {
        if (bInc)
        {
             switch(ST_VIDEO.eAspectRatio)
            {
               case EN_AspectRatio_Original:
                  ST_VIDEO.eAspectRatio = EN_AspectRatio_16X9;
                  break;
               case EN_AspectRatio_4X3:
                  ST_VIDEO.eAspectRatio = EN_AspectRatio_Original;
                  break;
               case EN_AspectRatio_16X9:
                  ST_VIDEO.eAspectRatio = EN_AspectRatio_4X3;
                  break;
               default:
                 ST_VIDEO.eAspectRatio = EN_AspectRatio_Original;
                 break;
            }
        }
        else
        {
            switch(ST_VIDEO.eAspectRatio)
           {
               case EN_AspectRatio_Original:
                  ST_VIDEO.eAspectRatio = EN_AspectRatio_4X3;
                  break;
               case EN_AspectRatio_4X3:
                  ST_VIDEO.eAspectRatio = EN_AspectRatio_16X9;
                  break;
               case EN_AspectRatio_16X9:
                  ST_VIDEO.eAspectRatio = EN_AspectRatio_Original;
                  break;
              default:
                 ST_VIDEO.eAspectRatio = EN_AspectRatio_Original;
                 break;
            }

        }
    }
    else
    {
        //Original <-> 16x9 <-> 4x3
        if (bInc)
        {
            switch(ST_VIDEO.eAspectRatio)
            {
                case EN_AspectRatio_Original:
#if ENABLE_NZ_FREEVIEW
                   ST_VIDEO.eAspectRatio = EN_AspectRatio_JustScan;
#else
                    if (MApp_Scaler_Check_PointToPoint_Mode(PQ_MAIN_WINDOW))
                    {
                        ST_VIDEO.eAspectRatio = EN_AspectRatio_Point_to_Point;
                    }
                    else
                    {
                        ST_VIDEO.eAspectRatio = EN_AspectRatio_Panorama;
                    }
#endif
                    break;
                case EN_AspectRatio_Point_to_Point:
                    {
                        ST_VIDEO.eAspectRatio = EN_AspectRatio_Panorama;
                    }
                    break;

                case EN_AspectRatio_Panorama:
                    if (IsDigitalSourceInUse() || ( IsYPbPrInUse() && !MApi_XC_Sys_IsSrcHD(MAIN_WINDOW) ))
                    {
                        ST_VIDEO.eAspectRatio = EN_AspectRatio_Zoom2;
                    }
                    else
                    {
                        ST_VIDEO.eAspectRatio = EN_AspectRatio_JustScan;
                    }
                    break;
                case EN_AspectRatio_JustScan:
                    ST_VIDEO.eAspectRatio = EN_AspectRatio_Zoom2;
                    break;
                case EN_AspectRatio_Zoom2:
                    ST_VIDEO.eAspectRatio = EN_AspectRatio_Zoom1;
                    break;
                case EN_AspectRatio_Zoom1:
                    ST_VIDEO.eAspectRatio = EN_AspectRatio_16X9;
                    break;
                case EN_AspectRatio_16X9:
                    ST_VIDEO.eAspectRatio = EN_AspectRatio_4X3;
                    break;
                case EN_AspectRatio_4X3:
                    ST_VIDEO.eAspectRatio = EN_AspectRatio_Original;
                    break;
                default:
                    break;
            }
        }
        else
        {
            switch(ST_VIDEO.eAspectRatio)
            {
                case EN_AspectRatio_Original:
                    ST_VIDEO.eAspectRatio = EN_AspectRatio_4X3;
                break;
                case EN_AspectRatio_4X3:
                    ST_VIDEO.eAspectRatio = EN_AspectRatio_16X9;
                    break;
                case EN_AspectRatio_16X9:
                    ST_VIDEO.eAspectRatio = EN_AspectRatio_Zoom1;
                    break;
                case EN_AspectRatio_Zoom1:
                    ST_VIDEO.eAspectRatio = EN_AspectRatio_Zoom2;
                    break;
                case EN_AspectRatio_Zoom2:
                    if (IsDigitalSourceInUse() || ( IsYPbPrInUse() && !MApi_XC_Sys_IsSrcHD(MAIN_WINDOW) ))
                    {
                        ST_VIDEO.eAspectRatio = EN_AspectRatio_Panorama;
                    }
                    else
                    {
                        ST_VIDEO.eAspectRatio = EN_AspectRatio_JustScan;
                    }
                   break;

               case EN_AspectRatio_JustScan:
#if ENABLE_NZ_FREEVIEW
             ST_VIDEO.eAspectRatio = EN_AspectRatio_Original;
#else
                  ST_VIDEO.eAspectRatio = EN_AspectRatio_Panorama;
#endif
                  break;

               case EN_AspectRatio_Panorama:
                    if (MApp_Scaler_Check_PointToPoint_Mode(PQ_MAIN_WINDOW))
                    {
                        ST_VIDEO.eAspectRatio = EN_AspectRatio_Point_to_Point;
                    }
                    else
                    {
                        ST_VIDEO.eAspectRatio = EN_AspectRatio_Original;
                    }
                    break;
               case EN_AspectRatio_Point_to_Point:
                    {
                        ST_VIDEO.eAspectRatio = EN_AspectRatio_Original;
                    }
                    break;
                default:
                    break;
            }
        }
    }
#endif

/*
    // Over scan will be controled at mapp_scaler.c
    switch(ST_VIDEO.eAspectRatio)
    {
        case EN_AspectRatio_JustScan:
        case EN_AspectRatio_Point_to_Point:
            MApp_Scaler_EnableOverScan(DISABLE);
            break;
        case EN_AspectRatio_Zoom1:
        case EN_AspectRatio_Zoom2:
        case EN_AspectRatio_Panorama:
        default:
            MApp_Scaler_EnableOverScan(ENABLE);
            break;
    }
*/

 #if ENABLE_PVR
    if( IsDTVInUse()
      &&(((MApp_PVR_StateMachineGet() == E_PVR_STATE_TIMESHIFT) &&(MApp_TimeShift_StateMachineGet()== E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING))
         ||((MApp_PVR_StateMachineGet() == E_PVR_STATE_RECORDnPLAYBACK || (MApp_PVR_StateMachineGet() == E_PVR_STATE_PLAYBACK)) &&(MApp_Playback_StateMachineGet()== E_PLAYBACK_STATE_PAUSE)))
        && !MApi_XC_IsCurrentFrameBufferLessMode()
        && MApi_XC_IsFreezeImg(MAIN_WINDOW)
       )//switch Aspect ratio when Pause, 4:3 mode will in garbage. because DNR memory changed.
    {
        MApi_XC_FreezeImg(FALSE, MAIN_WINDOW);
        MApp_Scaler_Setting_SetVDScale( ST_VIDEO.eAspectRatio , MAIN_WINDOW );
        msAPI_Timer_Delayms(200);
        MApi_XC_FreezeImg(TRUE, MAIN_WINDOW);
    }
    else
 #endif
    {
        MApp_Scaler_Setting_SetVDScale( ST_VIDEO.eAspectRatio , MAIN_WINDOW );
        #if (MHEG5_ENABLE)
        if((g_MHEG5Video.bHaveVideo==FALSE)&&(msAPI_CM_GetCurrentServiceType()== E_SERVICETYPE_RADIO)&&(ST_VIDEO.eAspectRatio == EN_AspectRatio_4X3))
        {
           msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW); //set bluescreen when radio program with mheg5(without video)
        }
        #endif
    }
}

extern void _MApp_ZUI_ACT_DecIncSleepTimer_Cycle(BOOLEAN bInc);
#if 0//ENABLE_T_C_COMBO
extern void _MApp_ZUI_ACT_DecIncDVBType_Cycle(void);
#endif
#if (NTV_FUNCTION_ENABLE)
extern void _MApp_ZUI_ACT_DecIncBandWidthType_Cycle(void);
#endif
void _MApp_ZUI_ACT_CheckTimeInfo(void)
{
    if (!(g_u8TimeInfo_Flag & UI_TIME_MANUAL_SET))
    {
        g_u8TimeInfo_Flag = 0;
    }
}

void MApp_ZUI_ACT_DecIncAutoSleepTimer_Cycle(BOOLEAN bInc)
{
#if (ENABLE_NO_OPERATE_AUTO_SLEEP )

    //EN_AUTOSLEEP_TIME_STATE_SETTING eCurAutoSleepSel = stGenSetting.g_Time.cAutoSleepSetting;
    EN_AUTOSLEEP_TIME_STATE_SETTING eCurAutoSleepSel = MApp_NoOperateAutoSleep_Get_AutoSleepTime();


    if(bInc)
    {
        if (eCurAutoSleepSel != STATE_AUTOSLEEP_8HOUR)
            eCurAutoSleepSel ++;
        else
            eCurAutoSleepSel = STATE_AUTOSLEEP_NEVER;
    }
    else
    {
        if(eCurAutoSleepSel != STATE_AUTOSLEEP_NEVER)
            eCurAutoSleepSel --;
        else
            eCurAutoSleepSel = STATE_AUTOSLEEP_8HOUR;
    }

    //stGenSetting.g_Time.cAutoSleepSetting = eCurAutoSleepSel;
    MApp_NoOperateAutoSleep_Set_AutoSleepTime(eCurAutoSleepSel);

    //stGenSetting.g_Time.cAutoSleepSetting =(EN_AUTOSLEEP_TIME_STATE_SETTING)(U8)enAutoSleepTimeState;
    //stLMGenSetting.stMD.enD4_AutoSleepTimer = enAutoSleepTimeState;
#else
    bInc=bInc;
#endif
}

///////////////////////////////////////////////////////////////////////////////
///  private  MApp_ZUI_ACT_ExecuteMenuItemAction
///  execute a specific action in menu items
///
///  @param [in]       act U16      action ID
///
///  @return BOOLEAN     true for accept, false for ignore
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
#if (ENABLE_AUDIO_SURROUND_DBX==ENABLE)
#define SWITCH_AUDIO_MODE_DELAY 256
BOOLEAN MApp_ZUI_ACT_AdjustDBX_TotSonMode(BOOLEAN action)
{
        stGenSetting.g_SoundSetting.DBXTV_TotSonMode =
        (EN_DBXTV_TotSonMode)MApp_ZUI_ACT_DecIncValue_Cycle( action, stGenSetting.g_SoundSetting.DBXTV_TotSonMode, E_TOTSON_ON, E_TOTSON_OFF, 1);
       msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
       MApi_DBXTV_SetMode(stGenSetting.g_SoundSetting.DBXTV_TotSonMode,stGenSetting.g_SoundSetting.DBXTV_TotVolMode,stGenSetting.g_SoundSetting.TotSurMode,0x1F);
       msAPI_Timer_Delayms(SWITCH_AUDIO_MODE_DELAY);
       msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
       return TRUE;
}

BOOLEAN MApp_ZUI_ACT_AdjustDBX_TotVolMode(BOOLEAN action)
{
        stGenSetting.g_SoundSetting.DBXTV_TotVolMode =
        (EN_DBXTV_TotVolMode)MApp_ZUI_ACT_DecIncValue_Cycle( action, stGenSetting.g_SoundSetting.DBXTV_TotVolMode, E_TOTVOL_NORMAL, E_TOTVOL_OFF, 1 );
       if(stGenSetting.g_SoundSetting.DBXTV_TotVolMode == E_TOTVOL_NIGHT)
             stGenSetting.g_SoundSetting.TotSurMode = E_TOTSUR_OFF;

       msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
       MApi_DBXTV_SetMode(stGenSetting.g_SoundSetting.DBXTV_TotSonMode,stGenSetting.g_SoundSetting.DBXTV_TotVolMode,stGenSetting.g_SoundSetting.TotSurMode,0x1F);
       msAPI_Timer_Delayms(SWITCH_AUDIO_MODE_DELAY);
       msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
       return TRUE;
}

BOOLEAN MApp_ZUI_ACT_AdjustDBX_TotSurMode(BOOLEAN action)
{
        stGenSetting.g_SoundSetting.TotSurMode =
        (EN_DBXTV_TotSurMode)MApp_ZUI_ACT_DecIncValue_Cycle( action, stGenSetting.g_SoundSetting.TotSurMode, E_TOTSUR_ON, E_TOTSUR_OFF, 1);
       msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
       MApi_DBXTV_SetMode(stGenSetting.g_SoundSetting.DBXTV_TotSonMode,stGenSetting.g_SoundSetting.DBXTV_TotVolMode,stGenSetting.g_SoundSetting.TotSurMode,0x1F);
       msAPI_Timer_Delayms(SWITCH_AUDIO_MODE_DELAY);
       msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
       return TRUE;
}

#endif


//
//******************************************************************************
//

BOOLEAN MApp_ZUI_ACT_Action_COMMON_ADJ_ITEM1(U16 act)
{
    //printf("\e[31;1m >> %s(0x%X): %d  \33[m \n", __FUNCTION__, act, g_mainpage_common);

    if (g_mainpage_common == EN_COMMON_PICTURE_MODE_PAGE)
    {
        ST_VIDEO.ePicture = (EN_MS_PICTURE)MApp_ZUI_ACT_DecIncValue_Cycle(
            act==EN_EXE_INC_COMMON_ADJ_ITEM1,
            ST_VIDEO.ePicture, PICTURE_MIN, PICTURE_NUMS-1, 1);

    #if FIXED_3D_SWITCH_PIC_MODE_GARBAGE
        g_u8switchPicModeFlag = 1;
    #endif

    MApp_Picture_Setting_SetColor(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW); //MApp_SetPictureMode(MAIN_WINDOW);

    #if FIXED_3D_SWITCH_PIC_MODE_GARBAGE
        g_u8switchPicModeFlag = 0;
    #endif
    }
    else if (g_mainpage_common == EN_COMMON_PICTURE_COLOR_PAGE)
    {
        //from case MAPP_UIMENUFUNC_ADJENB2_COLORTEMP:
        ST_PICTURE.eColorTemp = (EN_MS_COLOR_TEMP)MApp_ZUI_ACT_DecIncValue_Cycle(
            act==EN_EXE_INC_COMMON_ADJ_ITEM1,
            ST_PICTURE.eColorTemp, MS_COLOR_TEMP_MIN, MS_COLOR_TEMP_MAX, 1);

        MApp_PQ_Set_ColorTemp(MAIN_WINDOW);
    }

#if ENABLE_GAMMA_ADJUST
    else if (g_mainpage_common == EN_COMMON_GAMMA_ADJUST_PAGE)
    {
        stGenSetting.g_GammaSetting.u8Gain = (EN_MS_GAMMA_ADJUST)MApp_ZUI_ACT_DecIncValue_Cycle(
            act==EN_EXE_INC_COMMON_ADJ_ITEM1,
            stGenSetting.g_GammaSetting.u8Gain, MS_GAMMAADJUST_MIN, MS_GAMMAADJUST_MAX, 1);

        stGenSetting.g_GammaSetting.u8RedColor=stGenSetting.g_GammaSetting.GammaAdjOSDValue[0][stGenSetting.g_GammaSetting.u8Gain];
        stGenSetting.g_GammaSetting.u8GreenColor=stGenSetting.g_GammaSetting.GammaAdjOSDValue[1][stGenSetting.g_GammaSetting.u8Gain];
        stGenSetting.g_GammaSetting.u8BlueColor=stGenSetting.g_GammaSetting.GammaAdjOSDValue[2][stGenSetting.g_GammaSetting.u8Gain];

    }
#endif
    else if (g_mainpage_common == EN_COMMON_SOUND_SWITCH_PAGE)
    {
    #if(ENABLE_DVB_AUDIO_DESC)
        stGenSetting.g_SoundSetting.bEnableAD = !stGenSetting.g_SoundSetting.bEnableAD;
    #endif

    #if( ENABLE_DTV && ENABLE_DVB_AUDIO_DESC )
        if( IsDTVInUse() )
        {
            if (stGenSetting.g_SoundSetting.bEnableAD)
            {
            #if (ENABLE_ATSC_AD_FUNC)
                if( IsAtscInUse() )
                {
                    MApp_Audio_SearchAdAudio_ATSC();
                    MApp_Audio_SetAdAudio_ATSC(g_u8AdAudSelected);
                }
                else
            #endif
                {
                #if(ENABLE_DVB)
                 #if ENABLE_CI_PLUS
                    if(TRUE == MApp_CI_IsOpMode())
                    {
                        MApp_Audio_OpSearchAdAudio();
                    }
                    else
                 #endif
                    {
                        MApp_Audio_SearchAdAudio();
                    }

                    // if ad exist
                    if (g_u8AdAudSelected != 0xFF)
                    {
                #if ENABLE_AD_DISABLE_MAINAUDIO
                        MApp_Audio_SwitchtoADAudio(TRUE);
                #endif
                        MApp_Audio_SetAdAudio(g_u8AdAudSelected);
                        MApi_AUDIO_SetADOutputMode(AD_OUT_BOTH);
                        MApp_Audio_AdjustADVolume(stGenSetting.g_SoundSetting.ADVolume);
                    }
                    else
                    {
                        MApp_ChannelChange_SearchBroadcastMixAudio();
                        MApp_Audio_SetAudioLanguage(g_u8AudLangSelected);
                    }
                #endif
                }

            }
            else
            {
            #if ENABLE_AD_DISABLE_MAINAUDIO
                MApp_Audio_SwitchtoADAudio(FALSE);
            #endif

                MApi_AUDIO_SetADOutputMode(AD_OUT_NONE);
                MApi_AUDIO_SetCommand(MSAPI_AUD_DVB2_DECCMD_STOP);

                #if((ENABLE_ATSC_AD_FUNC))
                if( IsAtscInUse() )
                {
                    msAPI_DMX_Stop(u8AudFid2);
                }
                else
                #endif
                {
                #if(ENABLE_DVB)
                    msAPI_DMX_Stop( *MApp_Dmx_GetFid(EN_AD_FID) );
                   if(g_u8AdAudSelected == 0xFF)
                   {
                    MApp_ChannelChange_SearchDefaultAudioLang();
                    MApp_Audio_SetAudioLanguage(g_u8AudLangSelected);
                   }
                #endif
                }

            }
        }
    #endif // #if ENABLE_DTV
    }
    else if(g_mainpage_common == EN_COMMON_OFFTIMER_PAGE)
    {
        stGenSetting.g_Time.cOffTimerFlag =
            (EN_MENU_TIME_OffTimer)MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_INC_COMMON_ADJ_ITEM1,
                stGenSetting.g_Time.cOffTimerFlag,(U16) EN_Time_OffTimer_Off, (U16)(EN_Time_OffTimer_Num-1), 1);

    }
    else if(g_mainpage_common == EN_COMMON_ONTIMER_PAGE)
    {
        stGenSetting.g_Time.cOnTimerFlag =
            (EN_MENU_TIME_OnTimer)MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_INC_COMMON_ADJ_ITEM1,
                stGenSetting.g_Time.cOnTimerFlag,(U16) EN_Time_OnTimer_Off, (U16)(EN_Time_OnTimer_Num-1), 1);

        MApp_Time_SetOnTime();
    }
#if ENABLE_ATSC_TTS
    else if(g_mainpage_common == EN_COMMON_OPTION_TTS_PAGE)
    {
        // Mantis-1142645: [SQC][Eden_165C-D01A-S][1ST_ATSC][TTS] Select TTS Off¡Ano TTS sound
        // When TTS from On to Off, should say "TTS Off"
        if( stGenSetting.g_SysSetting.bTTSOn ) // Current TTS is ON
        {
            //printf("TTS On --> off\n");
            MApp_TTS_Cus_Say_TTSOnOff(FALSE);
        }
        else
        {
            //fix that:When in ATV no signal,switch tts from off to on,has pop noise
            if(IsATVInUse()&&(IsVDHasSignal() == FALSE))
            {
                MApi_AUDIO_SetMixModeMute(E_AUDIO_INFO_GAME_IN, GAME1_VOL, TRUE);
            }
        }

        stGenSetting.g_SysSetting.bTTSOn = !stGenSetting.g_SysSetting.bTTSOn;
    }
#endif

    MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_COMMON_ADJ_ITEM1);
    MApp_ZUI_CTL_DynamicListRefreshContent(HWND_MENU_COMMON_ADJ_PAGE_LIST);

    return TRUE;
}


BOOLEAN MApp_ZUI_ACT_Action_COMMON_ADJ_ITEM2(U16 act)
{
    //printf("\e[31;1m >> %s(0x%X): %d  \33[m \n", __FUNCTION__, act, g_mainpage_common);

    if (g_mainpage_common == EN_COMMON_PICTURE_MODE_PAGE)
    {
         ST_PICTURE.u8Contrast = MApp_ZUI_ACT_DecIncValue(
                                        act==EN_EXE_INC_COMMON_ADJ_ITEM2,
                                        ST_PICTURE.u8Contrast, 0, 100, 1);

        MApp_XC_PQ_Set_Contrast( MAIN_WINDOW, FALSE);
    }
    else if (g_mainpage_common == EN_COMMON_PICTURE_COLOR_PAGE)
    {
        BOOLEAN bIsNeedToReset = FALSE;
        U8 u8ValueTmp = ST_COLOR_TEMP.cRedColor;

        ST_COLOR_TEMP.cRedColor = MApp_ZUI_ACT_DecIncValue(
                    act==EN_EXE_INC_COMMON_ADJ_ITEM2,
                    ST_COLOR_TEMP.cRedColor, MIN_USER_RGB, MAX_USER_RGB, 1);

        ST_COLOR_TEMP.cRedScaleValue = GetColorTemperatureScale100Value(
            u8ValueTmp, ST_COLOR_TEMP.cRedColor,
            MIN_USER_RGB, MAX_USER_RGB, ST_COLOR_TEMP.cRedScaleValue, &bIsNeedToReset);

        if (bIsNeedToReset == TRUE)
        {
            ST_COLOR_TEMP.cRedColor = u8ValueTmp;
        }

        if ((ST_COLOR_TEMP.cRedColor == u8ValueTmp) && !bIsNeedToReset)
        {
            ;
        }
        else
        {
            MApp_PQ_Set_ColorTemp(MAIN_WINDOW);
        }
    }

#if ENABLE_GAMMA_ADJUST
    else if (g_mainpage_common == EN_COMMON_GAMMA_ADJUST_PAGE)
    {
        stGenSetting.g_GammaSetting.u8RedColor = MApp_ZUI_ACT_DecIncValue(
                    act==EN_EXE_INC_COMMON_ADJ_ITEM2,
                    stGenSetting.g_GammaSetting.u8RedColor, 0, 100, 1);
        stGenSetting.g_GammaSetting.GammaAdjOSDValue[0][stGenSetting.g_GammaSetting.u8Gain]= stGenSetting.g_GammaSetting.u8RedColor;
        MApp_CaluculateNewGammaValue(EN_UI_ADJUST,0,stGenSetting.g_GammaSetting.u8Gain ,stGenSetting.g_GammaSetting.u8RedColor);
    }
#endif
    else if (g_mainpage_common == EN_COMMON_SOUND_BALANCE_PAGE)
    {
        U8 u8ValueTmp = stGenSetting.g_SoundSetting.Balance;

        stGenSetting.g_SoundSetting.Balance = MApp_ZUI_ACT_DecIncValue(
            act==EN_EXE_INC_COMMON_ADJ_ITEM2,
            stGenSetting.g_SoundSetting.Balance, 0, 100, 1);

        if (stGenSetting.g_SoundSetting.Balance == u8ValueTmp)
        {
            ;
        }
        else
        {
            MApi_AUDIO_SetBalance(stGenSetting.g_SoundSetting.Balance);
        }

        if (msAPI_AUD_IsAudioMutedByUser() == 1)
        {
            MApp_UiMenu_MuteWin_Hide();
        }

        // Force to disable mute no matter what the current mute state is
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
    }
    else if (g_mainpage_common == EN_COMMON_SOUND_SWITCH_PAGE)
    {
        stGenSetting.g_SoundSetting.ADVolume =
            MApp_ZUI_ACT_DecIncValue(
                act==EN_EXE_INC_COMMON_ADJ_ITEM2,
                stGenSetting.g_SoundSetting.ADVolume, 0, 100, 1);

    #if(ENABLE_S2)
        if(IsDTVInUse() || IsS2InUse())
    #else
        if(IsDTVInUse())
    #endif
        {
            MApi_AUDIO_SetADAbsoluteVolume(MApi_AUDIO_ConvertVolumeUnit(stGenSetting.g_SoundSetting.ADVolume));
        }
    }
    else if (g_mainpage_common == EN_COMMON_SOUND_AUDIO_DELAY_PAGE)
    {
        //U8 u8ValueTmp = stGenSetting.g_SoundSetting.Audiodelay;

        //stGenSetting.g_SoundSetting.Audiodelay = MApp_ZUI_ACT_DecIncValue(
        //    act==EN_EXE_INC_COMMON_ADJ_ITEM2,
        //    stGenSetting.g_SoundSetting.Audiodelay, 20, 250, 10);

        /*if (stGenSetting.g_SoundSetting.Audiodelay == u8ValueTmp)
        {
            ;
        }
        else
        {
            MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_setSpdifDelay, stGenSetting.g_SoundSetting.Audiodelay, 0);
        }
		*/
        if (msAPI_AUD_IsAudioMutedByUser()==1)
        {
            MApp_UiMenu_MuteWin_Hide();
        }

        // Force to disable mute no matter what the current mute state is
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
    }
    else if(g_mainpage_common == EN_COMMON_OFFTIMER_PAGE)
    {
        stGenSetting.g_Time.u16OffTimer_Info_Hour =
            MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_INC_COMMON_ADJ_ITEM2,
                stGenSetting.g_Time.u16OffTimer_Info_Hour, 0, 24-1, 1);

        if ( stGenSetting.g_Time.u16OnTimer_Info_Hour == stGenSetting.g_Time.u16OffTimer_Info_Hour
            && stGenSetting.g_Time.u16OnTimer_Info_Min == stGenSetting.g_Time.u16OffTimer_Info_Min)
        {
            EN_OSD_WNDEXEACTION_ENUM temp_act = (EN_OSD_WNDEXEACTION_ENUM)act;

            if (act == EN_EXE_INC_SET_OFFTIME_HOUR)
            {
                if (stGenSetting.g_Time.u16OffTimer_Info_Min >= (60-1))
                {
                    temp_act = EN_EXE_DEC_SET_OFFTIME_HOUR;
                }
            }
            else
            {
                if (stGenSetting.g_Time.u16OffTimer_Info_Min == 0)
                {
                    temp_act = EN_EXE_INC_SET_OFFTIME_HOUR;
                }
            }

            stGenSetting.g_Time.u16OffTimer_Info_Min =
                MApp_ZUI_ACT_DecIncValue_Cycle(temp_act==EN_EXE_INC_COMMON_ADJ_ITEM2,
                    stGenSetting.g_Time.u16OffTimer_Info_Min, 0, 60-1, 1);
        }
    }
    else if(g_mainpage_common == EN_COMMON_ONTIMER_PAGE)
    {
        stGenSetting.g_Time.u16OnTimer_Info_Hour =
            MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_INC_COMMON_ADJ_ITEM2,
                stGenSetting.g_Time.u16OnTimer_Info_Hour, 0, 24-1, 1);

        if( stGenSetting.g_Time.u16OnTimer_Info_Hour == stGenSetting.g_Time.u16OffTimer_Info_Hour
            && stGenSetting.g_Time.u16OnTimer_Info_Min == stGenSetting.g_Time.u16OffTimer_Info_Min)
        {
            EN_OSD_WNDEXEACTION_ENUM temp_act = (EN_OSD_WNDEXEACTION_ENUM)act;

            if(act == EN_EXE_INC_COMMON_ADJ_ITEM2)
            {
                if(stGenSetting.g_Time.u16OnTimer_Info_Min >= (60-1))
                {
                    temp_act = EN_EXE_DEC_COMMON_ADJ_ITEM2;
                }
            }
            else
            {
                if(stGenSetting.g_Time.u16OnTimer_Info_Min == 0)
                {
                    temp_act = EN_EXE_INC_COMMON_ADJ_ITEM2;
                }
            }

            stGenSetting.g_Time.u16OnTimer_Info_Min =
                MApp_ZUI_ACT_DecIncValue_Cycle(temp_act==EN_EXE_INC_COMMON_ADJ_ITEM2,
                    stGenSetting.g_Time.u16OnTimer_Info_Min, 0, 60-1, 1);
        }
        MApp_Time_SetOnTime();
    }
    else if(g_mainpage_common == EN_COMMON_TIME_CLOCK_PAGE)
    {
        ST_TIME _stTime;
        U16 MonthDays;

        MApp_ConvertSeconds2StTime(MApp_GetLocalSystemTime(), &_stTime);

        if (!(g_u8TimeInfo_Flag & UI_TIME_DAY_SET))
        {
            stLMGenSetting.stMD.u16Option_Info_Month = UI_TIME_MONTH_INIT;
            stLMGenSetting.stMD.u16Option_Info_Day = 0;
        }

        MonthDays = MApp_GetDaysOfThisMonth(stLMGenSetting.stMD.u16Option_Info_Year,
                                            stLMGenSetting.stMD.u16Option_Info_Month);

        stLMGenSetting.stMD.u16Option_Info_Day =
            MApp_ZUI_ACT_DecIncValue_Cycle(
                act==EN_EXE_INC_COMMON_ADJ_ITEM2,
                stLMGenSetting.stMD.u16Option_Info_Day, 1, MonthDays, 1);

        _stTime.u8Day = (U8)stLMGenSetting.stMD.u16Option_Info_Day;
        _stTime.u8Sec = 0;

        u32ProtectOffTimer = msAPI_Timer_GetTime0();
        MApp_SetLocalSystemTime(MApp_ConvertStTime2Seconds(&_stTime));
        g_u8TimeInfo_Flag |= UI_TIME_DAY_SET;

        MApp_Time_SetOnTime();
    }
#if (ENABLE_EXTERN_MFC_CHIP)
    else if(g_mainpage_common == EN_COMMON_SET_MFC_PAGE)
    {
        stGenSetting.stDevMfcSetting.enMFCStrength = (EN_URSA_MEMC_LEVEL) MApp_ZUI_ACT_DecIncValue_Cycle(act, (EN_URSA_MEMC_LEVEL)(stGenSetting.stDevMfcSetting.enMFCStrength), EN_URSA_MEMC_OFF,EN_URSA_MEMC_HIGH, 1);
        MDrv_Ursa_6M30_MFC_Level((EN_URSA_MEMC_LEVEL)stGenSetting.stDevMfcSetting.enMFCStrength);
    }
#endif
#if ENABLE_ATSC_TTS
    else if(g_mainpage_common == EN_COMMON_OPTION_TTS_PAGE)
    {
        stGenSetting.g_SysSetting.u8TTSVolume =MApp_ZUI_ACT_DecIncValue_Cycle((act==EN_EXE_INC_COMMON_ADJ_ITEM2),stGenSetting.g_SysSetting.u8TTSVolume, EN_VOICE_GUIDE_VOLUME_LOW, EN_VOICE_GUIDE_VOLUME_HIGH, 1);
        MApp_UiMenuFunc_SetTTSVolume(stGenSetting.g_SysSetting.u8TTSVolume);
    }
#endif

    MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_COMMON_ADJ_ITEM2);
    return TRUE;
}


BOOLEAN MApp_ZUI_ACT_Action_COMMON_ADJ_ITEM3(U16 act)
{
    //printf("\e[31;1m >> %s(0x%X): %d  \33[m \n", __FUNCTION__, act, g_mainpage_common);

    if(g_mainpage_common == EN_COMMON_PICTURE_MODE_PAGE)
    {
        ST_PICTURE.u8Brightness = MApp_ZUI_ACT_DecIncValue(
                                    act==EN_EXE_INC_COMMON_ADJ_ITEM3,
                                    ST_PICTURE.u8Brightness, 0, 100, 1);

        MApp_XC_PQ_Set_Brightness(MAIN_WINDOW, TRUE);
    }
    else if(g_mainpage_common == EN_COMMON_PICTURE_COLOR_PAGE)
    {
        BOOLEAN bIsNeedToReset = FALSE;
        U8 u8ValueTmp = ST_COLOR_TEMP.cGreenColor;

        ST_COLOR_TEMP.cGreenColor = MApp_ZUI_ACT_DecIncValue(
            act==EN_EXE_INC_COMMON_ADJ_ITEM3,
            ST_COLOR_TEMP.cGreenColor, MIN_USER_RGB, MAX_USER_RGB, 1);

        ST_COLOR_TEMP.cGreenScaleValue = GetColorTemperatureScale100Value(
            u8ValueTmp, ST_COLOR_TEMP.cGreenColor,
            MIN_USER_RGB, MAX_USER_RGB, ST_COLOR_TEMP.cGreenScaleValue, &bIsNeedToReset);

        if (bIsNeedToReset == TRUE)
        {
            ST_COLOR_TEMP.cGreenColor = u8ValueTmp;
        }

        if ((ST_COLOR_TEMP.cGreenColor == u8ValueTmp) && !bIsNeedToReset)
        {
            //bRet = FALSE;
        }
        else
        {
            //bRet = TRUE;
            MApp_PQ_Set_ColorTemp(MAIN_WINDOW);
        }
    }
#if ENABLE_GAMMA_ADJUST
    else if (g_mainpage_common == EN_COMMON_GAMMA_ADJUST_PAGE)
    {
        stGenSetting.g_GammaSetting.u8GreenColor= MApp_ZUI_ACT_DecIncValue(
                    act==EN_EXE_INC_COMMON_ADJ_ITEM3,
                    stGenSetting.g_GammaSetting.u8GreenColor, 0, 100, 1);
        stGenSetting.g_GammaSetting.GammaAdjOSDValue[1][stGenSetting.g_GammaSetting.u8Gain]= stGenSetting.g_GammaSetting.u8GreenColor;
        MApp_CaluculateNewGammaValue(EN_UI_ADJUST,1,stGenSetting.g_GammaSetting.u8Gain ,stGenSetting.g_GammaSetting.u8GreenColor);
    }
#endif
#if (ENABLE_ATSC_AD_FUNC)
    else if(g_mainpage_common == EN_COMMON_SOUND_SWITCH_PAGE)
    {
        U8 u8AdVolPara = 0;

        stGenSetting.g_SoundSetting.ADVolume =
            MApp_ZUI_ACT_DecIncValue(
                act==EN_EXE_INC_COMMON_ADJ_ITEM3,
                stGenSetting.g_SoundSetting.ADMixSetting, 0, 100, 25);

        if(stGenSetting.g_SoundSetting.ADMixSetting == 0)
            u8AdVolPara = (U8)AD_BALANCE_ADVOLUME_0;
        else if(stGenSetting.g_SoundSetting.ADMixSetting == 25)
            u8AdVolPara = (U8)AD_BALANCE_ADVOLUME_25;
        else if(stGenSetting.g_SoundSetting.ADMixSetting == 50)
            u8AdVolPara = (U8)AD_BALANCE_EQUAL;
        else if(stGenSetting.g_SoundSetting.ADMixSetting == 75)
            u8AdVolPara = (U8)AD_BALANCE_ADVOLUME_75;
        else if(stGenSetting.g_SoundSetting.ADMixSetting == 100)
            u8AdVolPara = (U8)AD_BALANCE_ADVOLUME_100;

        MApi_AUDIO_SetAC3PInfo(Audio_AC3P_infoType_Mixer_Balance, u8AdVolPara, 0);
    }
#endif
    else if(g_mainpage_common == EN_COMMON_OFFTIMER_PAGE)
    {
        stGenSetting.g_Time.u16OffTimer_Info_Min =
            MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_INC_COMMON_ADJ_ITEM3,
                stGenSetting.g_Time.u16OffTimer_Info_Min, 0, 60-1, 1);

        if( stGenSetting.g_Time.u16OnTimer_Info_Hour == stGenSetting.g_Time.u16OffTimer_Info_Hour
            && stGenSetting.g_Time.u16OffTimer_Info_Min == stGenSetting.g_Time.u16OnTimer_Info_Min)
        {

            EN_OSD_WNDEXEACTION_ENUM temp_act = (EN_OSD_WNDEXEACTION_ENUM)act;

            if (act == EN_EXE_INC_SET_OFFTIME_MIN)
            {
                if (stGenSetting.g_Time.u16OffTimer_Info_Min >= (60-1))
                {
                    temp_act = EN_EXE_DEC_SET_OFFTIME_MIN;
                }
            }
            else
            {
                if (stGenSetting.g_Time.u16OffTimer_Info_Min == 0)
                {
                    temp_act = EN_EXE_INC_SET_OFFTIME_MIN;
                }
            }

            stGenSetting.g_Time.u16OffTimer_Info_Min =
                MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_INC_COMMON_ADJ_ITEM3,
                    stGenSetting.g_Time.u16OffTimer_Info_Min, 0, 60-1, 1);
        }
    }
    else if(g_mainpage_common == EN_COMMON_ONTIMER_PAGE)
    {
        stGenSetting.g_Time.u16OnTimer_Info_Min =
            MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_INC_COMMON_ADJ_ITEM3,
                stGenSetting.g_Time.u16OnTimer_Info_Min, 0, 60-1, 1);

        if( stGenSetting.g_Time.u16OnTimer_Info_Hour == stGenSetting.g_Time.u16OffTimer_Info_Hour
            && stGenSetting.g_Time.u16OnTimer_Info_Min == stGenSetting.g_Time.u16OffTimer_Info_Min)
        {

            EN_OSD_WNDEXEACTION_ENUM temp_act = (EN_OSD_WNDEXEACTION_ENUM)act;

            if(act == EN_EXE_INC_COMMON_ADJ_ITEM3)
            {
                if(stGenSetting.g_Time.u16OnTimer_Info_Min >= (60-1))
                {
                    temp_act = EN_EXE_INC_COMMON_ADJ_ITEM3;
                }
            }
            else
            {
                if(stGenSetting.g_Time.u16OnTimer_Info_Min == 0)
                {
                    temp_act = EN_EXE_INC_COMMON_ADJ_ITEM3;
                }
            }

            stGenSetting.g_Time.u16OnTimer_Info_Min =
                MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_INC_COMMON_ADJ_ITEM3,
                    stGenSetting.g_Time.u16OnTimer_Info_Min, 0, 60-1, 1);
        }
        MApp_Time_SetOnTime();
    }
    else if(g_mainpage_common == EN_COMMON_TIME_CLOCK_PAGE)
    {
        ST_TIME _stTime;
        U16 MonthDays;

        MApp_ConvertSeconds2StTime(MApp_GetLocalSystemTime(),&_stTime);

        if (!(g_u8TimeInfo_Flag & UI_TIME_MONTH_SET))
        {
            stLMGenSetting.stMD.u16Option_Info_Month = 0;
        }

        stLMGenSetting.stMD.u16Option_Info_Month =
            MApp_ZUI_ACT_DecIncValue_Cycle(
                act==EN_EXE_INC_COMMON_ADJ_ITEM3,
                stLMGenSetting.stMD.u16Option_Info_Month, 1, 12, 1);

        _stTime.u8Month =(U8)stLMGenSetting.stMD.u16Option_Info_Month;
        MonthDays = MApp_GetDaysOfThisMonth(_stTime.u16Year, _stTime.u8Month);

        if ( stLMGenSetting.stMD.u16Option_Info_Day > MonthDays )
        {
            _stTime.u8Day = stLMGenSetting.stMD.u16Option_Info_Day = MonthDays;
        }

        _stTime.u8Sec = 0;
        u32ProtectOffTimer = msAPI_Timer_GetTime0();

        MApp_SetLocalSystemTime(MApp_ConvertStTime2Seconds(&_stTime));
        g_u8TimeInfo_Flag |= UI_TIME_MONTH_SET;

        MApp_Time_SetOnTime();

    }
#if (ENABLE_EXTERN_MFC_CHIP)
    else if(g_mainpage_common == EN_COMMON_SET_MFC_PAGE)
    {
        stGenSetting.stDevMfcSetting.enMEMCType = (EN_URSA_MFC_TYPE) MApp_ZUI_ACT_DecIncValue_Cycle(act, (EN_URSA_MFC_TYPE)(stGenSetting.stDevMfcSetting.enMEMCType), EN_URSA_MFC_Off, (EN_URSA_MFC_Num-1), 1);
        MDrv_Ursa_6M30_MFC_Demo(stGenSetting.stDevMfcSetting.enMEMCType);
    }
#endif
#if ENABLE_ATSC_TTS
    else if(g_mainpage_common == EN_COMMON_OPTION_TTS_PAGE)
    {
        stGenSetting.g_SysSetting.u8TTSSpeed = MApp_ZUI_ACT_DecIncValue_Cycle((act==EN_EXE_INC_COMMON_ADJ_ITEM3),stGenSetting.g_SysSetting.u8TTSSpeed, EN_VOICE_GUIDE_SPEED_SLOW, EN_VOICE_GUIDE_SPEED_FAST, 1);
        MApp_UiMenuFunc_SetTTSSpeed(stGenSetting.g_SysSetting.u8TTSSpeed);
    }
#endif

    MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_COMMON_ADJ_ITEM3);
    return TRUE;
}

BOOLEAN MApp_ZUI_ACT_Action_COMMON_ADJ_ITEM4(U16 act)
{
    //printf("\e[31;1m >> %s(0x%X): %d  \33[m \n", __FUNCTION__, act, g_mainpage_common);

    if (g_mainpage_common == EN_COMMON_PICTURE_MODE_PAGE)
    {
        ST_PICTURE.u8Saturation = MApp_ZUI_ACT_DecIncValue(
                                        act==EN_EXE_INC_COMMON_ADJ_ITEM4,
                                        ST_PICTURE.u8Saturation, 0, 100, 1);

        /*if (MApp_Scaler_Check_PointToPoint_Mode(PQ_MAIN_WINDOW))
        {
               ;// do nothing
        }
        else*/
        {
           MApi_XC_ACE_PicSetSaturation(MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW),
                                        msAPI_Mode_PictureSaturationN100toReallyValue(ST_PICTURE.u8Saturation) );
        }
    }
    else if (g_mainpage_common == EN_COMMON_PICTURE_COLOR_PAGE)
    {
        BOOLEAN bIsNeedToReset = FALSE;
        U8 u8ValueTmp = ST_COLOR_TEMP.cBlueColor;

        ST_COLOR_TEMP.cBlueColor = MApp_ZUI_ACT_DecIncValue(
                                    act==EN_EXE_INC_COMMON_ADJ_ITEM4,
                                    ST_COLOR_TEMP.cBlueColor, MIN_USER_RGB, MAX_USER_RGB, 1);

        ST_COLOR_TEMP.cBlueScaleValue = GetColorTemperatureScale100Value(
                                        u8ValueTmp, ST_COLOR_TEMP.cBlueColor,
                                        MIN_USER_RGB, MAX_USER_RGB,
                                        ST_COLOR_TEMP.cBlueScaleValue, &bIsNeedToReset);

        if (bIsNeedToReset == TRUE)
        {
            ST_COLOR_TEMP.cBlueColor = u8ValueTmp;
        }

        if ((ST_COLOR_TEMP.cBlueColor == u8ValueTmp) && !bIsNeedToReset)
        {
            ;
        }
        else
        {
            MApp_PQ_Set_ColorTemp(MAIN_WINDOW);
        }
    }
#if ENABLE_GAMMA_ADJUST
    else if (g_mainpage_common == EN_COMMON_GAMMA_ADJUST_PAGE)
    {
        stGenSetting.g_GammaSetting.u8BlueColor= MApp_ZUI_ACT_DecIncValue(
                    act==EN_EXE_INC_COMMON_ADJ_ITEM4,
                    stGenSetting.g_GammaSetting.u8BlueColor, 0, 100, 1);
        stGenSetting.g_GammaSetting.GammaAdjOSDValue[2][stGenSetting.g_GammaSetting.u8Gain]= stGenSetting.g_GammaSetting.u8BlueColor;
        MApp_CaluculateNewGammaValue(EN_UI_ADJUST,2,stGenSetting.g_GammaSetting.u8Gain ,stGenSetting.g_GammaSetting.u8BlueColor);
    }
#endif
    else if(g_mainpage_common == EN_COMMON_ONTIMER_PAGE)
    {
        stGenSetting.g_Time.cOnTimerSourceFlag =
            (EN_MENU_TIME_OnTimer_Source) MApp_ZUI_ACT_DecIncValue_Cycle((act==EN_EXE_INC_COMMON_ADJ_ITEM4), (U16)stGenSetting.g_Time.cOnTimerSourceFlag,(U16) (EN_Time_OnTimer_Source_Min+1), (U16)(EN_Time_OnTimer_Source_Num-1), 1);
    }
    else if(g_mainpage_common == EN_COMMON_TIME_CLOCK_PAGE)
    {
        ST_TIME _stTime;
        U16 MonthDays;

        MApp_ConvertSeconds2StTime(MApp_GetLocalSystemTime(),&_stTime);

        if (!(g_u8TimeInfo_Flag & UI_TIME_YEAR_SET))
        {
            stLMGenSetting.stMD.u16Option_Info_Year = UI_TIME_YEAR_INIT;
        }

        stLMGenSetting.stMD.u16Option_Info_Year =
            MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_COMMON_ADJ_ITEM4,
                    stLMGenSetting.stMD.u16Option_Info_Year, 2000, 2100, 1);

        _stTime.u16Year = stLMGenSetting.stMD.u16Option_Info_Year;
        MonthDays = MApp_GetDaysOfThisMonth(_stTime.u16Year, _stTime.u8Month);

        if( stLMGenSetting.stMD.u16Option_Info_Day > MonthDays )
        {
          _stTime.u8Day = stLMGenSetting.stMD.u16Option_Info_Day = MonthDays;
        }

        _stTime.u8Sec = 0;

        u32ProtectOffTimer = msAPI_Timer_GetTime0();
        MApp_SetLocalSystemTime(MApp_ConvertStTime2Seconds(&_stTime));
        g_u8TimeInfo_Flag |= UI_TIME_YEAR_SET;

        MApp_Time_SetOnTime();
    }
#if ENABLE_ATSC_TTS
    else if (g_mainpage_common == EN_COMMON_OPTION_TTS_PAGE)
    {
        stGenSetting.g_SysSetting.u8TTSPitch = MApp_ZUI_ACT_DecIncValue_Cycle((act==EN_EXE_INC_COMMON_ADJ_ITEM4),stGenSetting.g_SysSetting.u8TTSPitch, EN_VOICE_GUIDE_PITCH_LOW, EN_VOICE_GUIDE_PITCH_HIGH, 1);
        MApp_UiMenuFunc_SetTTSPitch(stGenSetting.g_SysSetting.u8TTSPitch);
    }
#endif

    MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_COMMON_ADJ_PAGE_LIST);
    return TRUE;
}

BOOLEAN MApp_ZUI_ACT_Action_COMMON_ADJ_ITEM5(U16 act)
{
    //printf("\e[31;1m >> %s(0x%X): %d  \33[m \n", __FUNCTION__, act, g_mainpage_common);

    if (g_mainpage_common == EN_COMMON_PICTURE_MODE_PAGE)
    {
        ST_PICTURE.u8Sharpness = MApp_ZUI_ACT_DecIncValue(
                                    act==EN_EXE_INC_COMMON_ADJ_ITEM5,
                                    ST_PICTURE.u8Sharpness, 0, 100, 1);

        /*if (MApp_Scaler_Check_PointToPoint_Mode(PQ_MAIN_WINDOW))
        {
            ;
        }
        else*/
        {
           MApi_XC_ACE_PicSetSharpness( MAIN_WINDOW,
                msAPI_Mode_PictureSharpnessN100toReallyValue(ST_PICTURE.u8Sharpness) );
        }
    }
    else if (g_mainpage_common == EN_COMMON_ONTIMER_PAGE)
    {
      #if (ENABLE_DVB)
        CHANNEL_LIST_TYPE eListMode = E_DTV_LIST;
      #endif

        switch (stGenSetting.g_Time.cOnTimerSourceFlag)
        {
        #if ENABLE_DTV
          #if (ENABLE_ATSC)
            case EN_Time_OnTimer_Source_ATSC:
                if (act == EN_EXE_INC_COMMON_ADJ_ITEM5)
                {
                    stGenSetting.g_Time.cOnTimerChannel =
                        MApp_GetPrevNextProgramIndex_ByProgIndex(
                                    FALSE, stGenSetting.g_Time.cOnTimerChannel);
                }
                else if (act == EN_EXE_DEC_COMMON_ADJ_ITEM5)
                {
                    stGenSetting.g_Time.cOnTimerChannel =
                        MApp_GetPrevNextProgramIndex_ByProgIndex(
                                    TRUE, stGenSetting.g_Time.cOnTimerChannel);
                }
                break;
          #endif // #if (ENABLE_ATSC)

         #if (ENABLE_DVB)
          #if (ENABLE_DVBT)
            case EN_Time_OnTimer_Source_DVBT:
            case EN_Time_OnTimer_Source_DVBT_RADIO:
           #if NORDIG_FUNC //for Nordig spec v2.0
            case EN_Time_OnTimer_Source_DVBT_DATA:
           #endif
          #endif // #if (ENABLE_DVBT)

          #if (ENABLE_DVBC)
            case EN_Time_OnTimer_Source_DVBC:
            case EN_Time_OnTimer_Source_DVBC_RADIO:
           #if NORDIG_FUNC //for Nordig spec v2.0
            case EN_Time_OnTimer_Source_DVBC_DATA:
           #endif
          #endif // #if (ENABLE_DVBC)

          #if (ENABLE_DTMB)
            case EN_Time_OnTimer_Source_DTMB:
            case EN_Time_OnTimer_Source_DTMB_RADIO:
           #if NORDIG_FUNC //for Nordig spec v2.0
            case EN_Time_OnTimer_Source_DTMB_DATA:
           #endif
          #endif // #if (ENABLE_DTMB)

          #if (ENABLE_ISDBT)
            case EN_Time_OnTimer_Source_ISDBT:
            case EN_Time_OnTimer_Source_ISDBT_RADIO:
           #if NORDIG_FUNC //for Nordig spec v2.0
            case EN_Time_OnTimer_Source_ISDBT_DATA:
           #endif
          #endif // #if (ENABLE_ISDBT)

          #if ENABLE_S2
            case EN_Time_OnTimer_Source_S2:
            case EN_Time_OnTimer_Source_S2_RADIO:
           #if NORDIG_FUNC //for Nordig spec v2.0
            case EN_Time_OnTimer_Source_S2_DATA:
           #endif
          #endif // #if ENABLE_S2
            {
                MEMBER_SERVICETYPE type=E_SERVICETYPE_DTV;
                if (  0
                 #if ENABLE_DVBT
                   || (stGenSetting.g_Time.cOnTimerSourceFlag == EN_Time_OnTimer_Source_DVBT)
                 #endif
                 #if ENABLE_DVBC
                   || (stGenSetting.g_Time.cOnTimerSourceFlag == EN_Time_OnTimer_Source_DVBC)
                 #endif
                 #if ENABLE_DTMB
                   || (stGenSetting.g_Time.cOnTimerSourceFlag == EN_Time_OnTimer_Source_DTMB)
                 #endif
                 #if ENABLE_ISDBT
                   || (stGenSetting.g_Time.cOnTimerSourceFlag == EN_Time_OnTimer_Source_ISDBT)
                 #endif
                 #if ENABLE_S2
                   || (stGenSetting.g_Time.cOnTimerSourceFlag == EN_Time_OnTimer_Source_S2)
                 #endif
                   )
                {
                    type = E_SERVICETYPE_DTV;
                    eListMode = E_DTV_LIST;
                }
                else if ( 0
                      #if ENABLE_DVBT
                        || (stGenSetting.g_Time.cOnTimerSourceFlag == EN_Time_OnTimer_Source_DVBT_RADIO)
                      #endif
                      #if ENABLE_DVBC
                        || (stGenSetting.g_Time.cOnTimerSourceFlag == EN_Time_OnTimer_Source_DVBC_RADIO)
                      #endif
                      #if ENABLE_DTMB
                        || (stGenSetting.g_Time.cOnTimerSourceFlag == EN_Time_OnTimer_Source_DTMB_RADIO)
                      #endif
                      #if ENABLE_ISDBT
                        || (stGenSetting.g_Time.cOnTimerSourceFlag == EN_Time_OnTimer_Source_ISDBT_RADIO)
                      #endif
                      #if ENABLE_S2
                        || (stGenSetting.g_Time.cOnTimerSourceFlag == EN_Time_OnTimer_Source_S2_RADIO)
                      #endif
                        )
                {
                    type = E_SERVICETYPE_RADIO;
                    eListMode = E_RADIO_LIST;
                }
            #if NORDIG_FUNC //for Nordig spec v2.0
                else if ( 0
                      #if ENABLE_DVBT
                        || (stGenSetting.g_Time.cOnTimerSourceFlag == EN_Time_OnTimer_Source_DVBT_DATA)
                      #endif
                      #if ENABLE_DVBC
                        ||(stGenSetting.g_Time.cOnTimerSourceFlag == EN_Time_OnTimer_Source_DVBC_DATA)
                      #endif
                      #if ENABLE_DTMB
                        || (stGenSetting.g_Time.cOnTimerSourceFlag == EN_Time_OnTimer_Source_DTMB_DATA)
                      #endif
                      #if ENABLE_ISDBT
                        || (stGenSetting.g_Time.cOnTimerSourceFlag == EN_Time_OnTimer_Source_ISDBT_DATA)
                      #endif
                      #if ENABLE_S2
                        || (stGenSetting.g_Time.cOnTimerSourceFlag == EN_Time_OnTimer_Source_S2_DATA)
                      #endif
                        )
                {
                    type = E_SERVICETYPE_DATA;
                    eListMode = E_DATA_LIST;
                }
            #endif

                if (act == EN_EXE_INC_COMMON_ADJ_ITEM5)
                {
                    stGenSetting.g_Time.cOnTimerChannel = msAPI_CM_GetNextProgramPosition(type, stGenSetting.g_Time.cOnTimerChannel, FALSE, eListMode,NULL);
                }
                else if (act == EN_EXE_DEC_COMMON_ADJ_ITEM5)
                {
                    stGenSetting.g_Time.cOnTimerChannel = msAPI_CM_GetPrevProgramPosition(type, stGenSetting.g_Time.cOnTimerChannel, FALSE, eListMode,NULL);
                }
            }
            break;
         #endif //ENABLE_DVB
        #endif //ENABLE_DTV

        #if (!ENABLE_ATSC)
            case EN_Time_OnTimer_Source_ATV:
            {
                if (act == EN_EXE_INC_COMMON_ADJ_ITEM5)
                {
                    stGenSetting.g_Time.cOnTimerChannel = msAPI_ATV_GetNextProgramNumber(stGenSetting.g_Time.cOnTimerChannel, FALSE);
                }
                else if (act == EN_EXE_DEC_COMMON_ADJ_ITEM5)
                {
                    stGenSetting.g_Time.cOnTimerChannel = msAPI_ATV_GetPrevProgramNumber(stGenSetting.g_Time.cOnTimerChannel, FALSE);
                }
            }
            break;
        #endif // #if (!ENABLE_ATSC)

            default:
                break;
        }

        MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_COMMON_ADJ_PAGE_LIST);
        return TRUE;
    }
    else if(g_mainpage_common == EN_COMMON_TIME_CLOCK_PAGE)
    {
        ST_TIME _stTime;

        //from case MAPP_UIMENUFUNC_ADJMENUDHOURVALUE:
        MApp_ConvertSeconds2StTime(MApp_GetLocalSystemTime(),&_stTime);

        if(!(g_u8TimeInfo_Flag & UI_TIME_HOUR_SET))
        {
            stLMGenSetting.stMD.u16Option_Info_Hour = UI_TIME_HOUR_INIT;
        }

        stLMGenSetting.stMD.u16Option_Info_Hour =
            MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_COMMON_ADJ_ITEM5,
                    stLMGenSetting.stMD.u16Option_Info_Hour, 0, 24-1, 1);

        _stTime.u8Hour =(U8)stLMGenSetting.stMD.u16Option_Info_Hour;
        _stTime.u8Sec  = 0;

        u32ProtectOffTimer = msAPI_Timer_GetTime0();
        MApp_SetLocalSystemTime(MApp_ConvertStTime2Seconds(&_stTime));
        g_u8TimeInfo_Flag |= UI_TIME_HOUR_SET;

        MApp_Time_SetOnTime();
    }

    MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_COMMON_ADJ_ITEM5);
    return TRUE;
}


BOOLEAN MApp_ZUI_ACT_Action_COMMON_ADJ_ITEM6(U16 act)
{
    //printf("\e[31;1m >> %s(0x%X): %d  \33[m \n", __FUNCTION__, act, g_mainpage_common);

    if (g_mainpage_common == EN_COMMON_PICTURE_MODE_PAGE)
    {
        ST_PICTURE.u8Hue = MApp_ZUI_ACT_DecIncValue(
                                act==EN_EXE_INC_COMMON_ADJ_ITEM6,
                                ST_PICTURE.u8Hue, 0, 100, 1);

        MApi_XC_ACE_PicSetHue(MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW),
                              msAPI_Mode_PictureHueN100toReallyValue(ST_PICTURE.u8Hue));
    }
    else if (g_mainpage_common == EN_COMMON_ONTIMER_PAGE)
    {
        stGenSetting.g_Time.cOnTimerVolume =
            (U8) MApp_ZUI_ACT_DecIncValue_Cycle(
                        (act==EN_EXE_INC_COMMON_ADJ_ITEM6),
                        stGenSetting.g_Time.cOnTimerVolume, 0, 100, 1);
    }
    else if (g_mainpage_common == EN_COMMON_TIME_CLOCK_PAGE)
    {
        ST_TIME _stTime;

        MApp_ConvertSeconds2StTime(MApp_GetLocalSystemTime(), &_stTime);

        if(!(g_u8TimeInfo_Flag & UI_TIME_MINUTE_SET))
        {
            stLMGenSetting.stMD.u16Option_Info_Min = UI_TIME_MINUTE_INIT;
        }

        stLMGenSetting.stMD.u16Option_Info_Min=
            MApp_ZUI_ACT_DecIncValue_Cycle(
                act==EN_EXE_INC_COMMON_ADJ_ITEM6,
                stLMGenSetting.stMD.u16Option_Info_Min, 0, 60-1, 1);

        _stTime.u8Min = (U8)stLMGenSetting.stMD.u16Option_Info_Min;
        _stTime.u8Sec = 0;

        u32ProtectOffTimer = msAPI_Timer_GetTime0();
        MApp_SetLocalSystemTime(MApp_ConvertStTime2Seconds(&_stTime));
        g_u8TimeInfo_Flag |= UI_TIME_MINUTE_SET;
        MApp_Time_SetOnTime();
    }

    MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_COMMON_ADJ_ITEM6);
    return TRUE;
}

//
//******************************************************************************
//

#define CEC_UI_MSG(x)           //x

//
//******************************************************************************
//

BOOLEAN MApp_ZUI_ACT_ExecuteMenuItemAction(U16 act)
{
    switch(act)
    {
    #if ENABLE_ATSC_MENU_UI
      #if ENABLE_TTSTEST_FROM_USB
         //case EN_EXE_DEC_SPEED_ADJ:
         case EN_EXE_INC_SPEED_ADJ:
         {
             stGenSetting.g_SysSetting.u8TTSSpeed = MApp_ZUI_ACT_DecIncValue_Cycle((act==EN_EXE_INC_SPEED_ADJ),stGenSetting.g_SysSetting.u8TTSSpeed, EN_VOICE_GUIDE_SPEED_SLOW, EN_VOICE_GUIDE_SPEED_FAST, 1);
             MApp_UiMenuFunc_SetTTSSpeed(stGenSetting.g_SysSetting.u8TTSSpeed);
             MApp_ZUI_API_InvalidateWindow(HWND_TTS_TEST_SPEED_ADJ_ITEM1);
             break;
         }

         //case EN_EXE_DEC_PITCH_ADJ:
         case EN_EXE_INC_PITCH_ADJ:
         {
             stGenSetting.g_SysSetting.u8TTSPitch = MApp_ZUI_ACT_DecIncValue_Cycle((act==EN_EXE_INC_PITCH_ADJ),stGenSetting.g_SysSetting.u8TTSPitch, EN_VOICE_GUIDE_PITCH_LOW, EN_VOICE_GUIDE_PITCH_HIGH, 1);
             MApp_UiMenuFunc_SetTTSPitch(stGenSetting.g_SysSetting.u8TTSPitch);
             MApp_ZUI_API_InvalidateWindow(HWND_TTS_TEST_PITCH_ADJ_ITEM2);
             break;
         }
      #endif
        case EN_EXE_INC_MTS:
            MApp_UiMenuFunc_AdjAudioLanguage(FALSE);
            break;
        case EN_EXE_DEC_MTS:
            MApp_UiMenuFunc_AdjAudioLanguage(TRUE);
            break;
    #endif


        case EN_EXE_ONOFF_SWUPDATE:
          #if(ENABLE_SOFTWAREUPDATE)
            //from case MAPP_UIMENUFUNC_ADJA7_SoftwareUpdateOFF
            stGenSetting.g_SysSetting.fSoftwareUpdate = !stGenSetting.g_SysSetting.fSoftwareUpdate;
            MApp_ZUI_API_InvalidateWindow(HWND_MENU_CHANNEL_SW_OAD_UPGRADE_OPTION);
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_CHANNEL_PAGE);
            MApp_ZUI_CTL_DynamicListRefreshContent(HWND_MENU_CHANNEL_PAGE_LIST);
          #endif
            return TRUE;


        case EN_EXE_ONOFF_5VANTENNA:
          #ifdef ENABLE_5VANTENNA
            //from case MAPP_UIMENUFUNC_ADJ5VAntennaPowerOFF:
            stGenSetting.g_SysSetting.f5VAntennaPower = !stGenSetting.g_SysSetting.f5VAntennaPower;
            // 5V Antenna Monitor
            AdjustAntenna5VMonitor((EN_MENU_5V_AntennaPower)stGenSetting.g_SysSetting.f5VAntennaPower);
            MApp_ZUI_API_InvalidateWindow(HWND_MENU_CHANNEL_5V_ANTENNA_OPTION);
          #endif
            return TRUE;
		
		
		        case EN_EXE_DEC_TINT:
        case EN_EXE_INC_TINT:
            ST_PICTURE.u8Hue = MApp_ZUI_ACT_DecIncValue(
                act==EN_EXE_INC_TINT,
                ST_PICTURE.u8Hue, 0, 100, 1);
            MApi_XC_ACE_PicSetHue( MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW), msAPI_Mode_PictureHueN100toReallyValue(ST_PICTURE.u8Hue) );
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_PIC_ADJ_TINT);
            return TRUE;

        case EN_EXE_DEC_BRIGHTNESS:
        case EN_EXE_INC_BRIGHTNESS:
        {
            U8 u8BR, u8BG, u8BB;

            ST_PICTURE.u8Brightness = MApp_ZUI_ACT_DecIncValue(
                act==EN_EXE_INC_BRIGHTNESS,
                ST_PICTURE.u8Brightness, 0, 100, 1);

            u8BR = MApi_XC_Sys_ACE_transfer_Bri((MApp_Scaler_FactoryAdjBrightness(msAPI_Mode_PictureBrightnessN100toReallyValue(ST_PICTURE.u8Brightness),ST_SUBCOLOR.u8SubBrightness)), BRIGHTNESS_R);
            u8BG = MApi_XC_Sys_ACE_transfer_Bri((MApp_Scaler_FactoryAdjBrightness(msAPI_Mode_PictureBrightnessN100toReallyValue(ST_PICTURE.u8Brightness),ST_SUBCOLOR.u8SubBrightness)), BRIGHTNESS_G);
            u8BB = MApi_XC_Sys_ACE_transfer_Bri((MApp_Scaler_FactoryAdjBrightness(msAPI_Mode_PictureBrightnessN100toReallyValue(ST_PICTURE.u8Brightness),ST_SUBCOLOR.u8SubBrightness)), BRIGHTNESS_B);

            MApi_XC_ACE_PicSetBrightnessInVsync(MAIN_WINDOW, u8BR, u8BG, u8BB);
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_PIC_ADJ_BRIGHTNESS);
            return TRUE;
        }

        case EN_EXE_DEC_SHARPNESS:
        case EN_EXE_INC_SHARPNESS:
            ST_PICTURE.u8Sharpness = MApp_ZUI_ACT_DecIncValue(
                act==EN_EXE_INC_SHARPNESS,
                ST_PICTURE.u8Sharpness, 0, 100, 1);
            MApi_XC_ACE_PicSetSharpness( MAIN_WINDOW, msAPI_Mode_PictureSharpnessN100toReallyValue(ST_PICTURE.u8Sharpness) );
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_PIC_ADJ_SHARPNESS);
            return TRUE;

        case EN_EXE_DEC_SATURATION:
        case EN_EXE_INC_SATURATION:
            ST_PICTURE.u8Saturation = MApp_ZUI_ACT_DecIncValue(
                act==EN_EXE_INC_SATURATION,
                ST_PICTURE.u8Saturation, 0, 100, 1);
                  #if VGA_HDMI_YUV_POINT_TO_POINT
                     if(IsHDMIInUse()&&MDrv_PQ_Get_HDMIPCMode())
                    {
                       ;// do nothing
                    }
                    else
                  #endif          
                    {
            MApi_XC_ACE_PicSetSaturation(MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW),  msAPI_Mode_PictureSaturationN100toReallyValue(ST_PICTURE.u8Saturation) );
                    }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_PIC_ADJ_COLOR);
            return TRUE;

        case EN_EXE_DEC_CONTRAST:
        case EN_EXE_INC_CONTRAST:
             ST_PICTURE.u8Contrast = MApp_ZUI_ACT_DecIncValue(
                act==EN_EXE_INC_CONTRAST,
                ST_PICTURE.u8Contrast, 0, 100, 1);
        #if VGA_HDMI_YUV_POINT_TO_POINT
            if(IsHDMIInUse()&&MDrv_PQ_Get_HDMIPCMode())
            {
                MApi_XC_ACE_SetPCYUV2RGB(MAIN_WINDOW, FALSE);
                MApi_XC_ACE_PicSetContrast(MAIN_WINDOW, FALSE, MApp_Scaler_FactoryContrast(msAPI_Mode_PictureContrastN100toReallyValue(ST_PICTURE.u8Contrast),ST_SUBCOLOR.u8SubContrast));
            }
            else
        #endif          
            {
            MApi_XC_ACE_PicSetContrast(MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW), MApp_Scaler_FactoryContrast(msAPI_Mode_PictureContrastN100toReallyValue(ST_PICTURE.u8Contrast),ST_SUBCOLOR.u8SubContrast));
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_PIC_ADJ_CONTRAST);
            return TRUE;

        case EN_EXE_DEC_PICTURE_MODE:
        case EN_EXE_INC_PICTURE_MODE:
            ST_VIDEO.ePicture = (EN_MS_PICTURE)MApp_ZUI_ACT_DecIncValue_Cycle(
                act==EN_EXE_INC_PICTURE_MODE,
                ST_VIDEO.ePicture, PICTURE_MIN, PICTURE_NUMS-1, 1);
#if VGA_HDMI_YUV_POINT_TO_POINT
            MDrv_PQ_SetUserColorMode(ENABLE);
#endif
            MApp_Picture_Setting_SetColor(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);  //MApp_PicSetPicture( (T_MS_PICTURE *) &ST_PICTURE, SYS_INPUT_SOURCE_TYPE);
#if VGA_HDMI_YUV_POINT_TO_POINT
            MDrv_PQ_SetUserColorMode(DISABLE);
#endif

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_PICMODE_PICMODE);
            MApp_ZUI_CTL_DynamicListRefreshContent(HWND_MENU_PICTURE_MODE_PAGE_LIST);

            return TRUE;
#if (ENABLE_LANGUAGE_SWITCH_LIST_MENU)
        case EN_EXE_DEC_LANGUAE_LIST:
                MApp_SetListMenuLanguage(FALSE);
                break;
            case EN_EXE_INC_LANGUAE_LIST:    
                MApp_SetListMenuLanguage(TRUE);
                break;
#endif
        case EN_EXE_DEC_COLOR_TEMP:
        case EN_EXE_INC_COLOR_TEMP:
            //from case MAPP_UIMENUFUNC_ADJENB2_COLORTEMP:
            ST_PICTURE.eColorTemp = (EN_MS_COLOR_TEMP)MApp_ZUI_ACT_DecIncValue_Cycle(
                act==EN_EXE_INC_COLOR_TEMP,
                ST_PICTURE.eColorTemp, MS_COLOR_TEMP_MIN, MS_COLOR_TEMP_MAX, 1);

        #if VGA_HDMI_YUV_POINT_TO_POINT
          if(IsHDMIInUse()&&MDrv_PQ_Get_HDMIPCMode())
          {
                 MApi_XC_ACE_SetPCYUV2RGB(MAIN_WINDOW, FALSE);

              #if ENABLE_NEW_COLORTEMP_METHOD
                #if ENABLE_PRECISE_RGBBRIGHTNESS
                    MApi_XC_ACE_PicSetColorTemp(MAIN_WINDOW, FALSE, (XC_ACE_color_temp_ex *) &ST_COLOR_TEMP);
                #else
                    MApi_XC_ACE_PicSetColorTemp(MAIN_WINDOW, FALSE, (XC_ACE_color_temp *) &ST_COLOR_TEMP);
                #endif
              #else
                #if ENABLE_PRECISE_RGBBRIGHTNESS
                    MApi_XC_ACE_PicSetColorTemp( MAIN_WINDOW, FALSE, (XC_ACE_color_temp_ex *) &ST_COLOR_TEMP );
                    MApi_XC_ACE_PicSetBrightnessPreciseInVsync(MAIN_WINDOW, MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cRedOffset, BRIGHTNESS_R ), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cGreenOffset, BRIGHTNESS_G), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cBlueOffset, BRIGHTNESS_B));
                #else
                    MApi_XC_ACE_PicSetColorTemp( MAIN_WINDOW, FALSE, (XC_ACE_color_temp *) &ST_COLOR_TEMP );
                    MApi_XC_ACE_PicSetBrightnessInVsync(MAIN_WINDOW, MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cRedOffset, BRIGHTNESS_R ), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cGreenOffset, BRIGHTNESS_G), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cBlueOffset, BRIGHTNESS_B));
                #endif
             #endif
          }
         else
        #endif    
          {
            #if ENABLE_NEW_COLORTEMP_METHOD
                #if ENABLE_PRECISE_RGBBRIGHTNESS
                    MApi_XC_ACE_PicSetColorTemp(MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW), (XC_ACE_color_temp_ex *) &ST_COLOR_TEMP);
                #else
                    MApi_XC_ACE_PicSetColorTemp(MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW), (XC_ACE_color_temp *) &ST_COLOR_TEMP);
                #endif
            #else
        #if ENABLE_PRECISE_RGBBRIGHTNESS
            MApi_XC_ACE_PicSetColorTemp( MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW), (XC_ACE_color_temp_ex *) &ST_COLOR_TEMP );
            MApi_XC_ACE_PicSetBrightnessPreciseInVsync(MAIN_WINDOW, MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cRedOffset, BRIGHTNESS_R ), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cGreenOffset, BRIGHTNESS_G), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cBlueOffset, BRIGHTNESS_B));
        #else
            MApi_XC_ACE_PicSetColorTemp( MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW), (XC_ACE_color_temp *) &ST_COLOR_TEMP );
            MApi_XC_ACE_PicSetBrightnessInVsync(MAIN_WINDOW, MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cRedOffset, BRIGHTNESS_R ), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cGreenOffset, BRIGHTNESS_G), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cBlueOffset, BRIGHTNESS_B));
        #endif
            #endif
           }
            MApp_ZUI_CTL_DynamicListRefreshContent(HWND_MENU_PICTURE_COLOR_PAGE_LIST);
            return TRUE;

        case EN_EXE_DEC_COLOR_RED:
        case EN_EXE_INC_COLOR_RED:
            //from case MAPP_UIMENUFUNC_ADJU16B2_COLORTEMP_USER_RED:
            {
                BOOLEAN bIsNeedToReset = FALSE;
                //U8 u8TmpRedScaleValue = ST_COLOR_TEMP.cRedScaleValue;
                U8 u8ValueTmp = ST_COLOR_TEMP.cRedColor;
                ST_COLOR_TEMP.cRedColor = MApp_ZUI_ACT_DecIncValue(
                    act==EN_EXE_INC_COLOR_RED,
                    ST_COLOR_TEMP.cRedColor, MIN_USER_RGB, MAX_USER_RGB, 1);

                ST_COLOR_TEMP.cRedScaleValue = GetColorTemperatureScale100Value(
                    u8ValueTmp, ST_COLOR_TEMP.cRedColor,
                    MIN_USER_RGB, MAX_USER_RGB, ST_COLOR_TEMP.cRedScaleValue, &bIsNeedToReset);
                if (bIsNeedToReset == TRUE) ST_COLOR_TEMP.cRedColor = u8ValueTmp;

                if ((ST_COLOR_TEMP.cRedColor == u8ValueTmp) && !bIsNeedToReset)
                {
                    //bRet = FALSE;
                }
                else
                {
               #if VGA_HDMI_YUV_POINT_TO_POINT
                    if(IsHDMIInUse()&&MDrv_PQ_Get_HDMIPCMode())
                    {
                         MApi_XC_ACE_SetPCYUV2RGB(MAIN_WINDOW, FALSE);

                       #if ENABLE_NEW_COLORTEMP_METHOD
                            #if ENABLE_PRECISE_RGBBRIGHTNESS
                               MApi_XC_ACE_PicSetColorTemp(MAIN_WINDOW, FALSE, (XC_ACE_color_temp_ex *) &ST_COLOR_TEMP);
                            #else
                               MApi_XC_ACE_PicSetColorTemp(MAIN_WINDOW, FALSE, (XC_ACE_color_temp *) &ST_COLOR_TEMP);
                            #endif
                      #else
                            #if ENABLE_PRECISE_RGBBRIGHTNESS
                               MApi_XC_ACE_PicSetColorTemp( MAIN_WINDOW, FALSE, (XC_ACE_color_temp_ex *) &ST_COLOR_TEMP );
                               MApi_XC_ACE_PicSetBrightnessPreciseInVsync(MAIN_WINDOW, MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cRedOffset, BRIGHTNESS_R ), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cGreenOffset, BRIGHTNESS_G), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cBlueOffset, BRIGHTNESS_B));
                            #else
                               MApi_XC_ACE_PicSetColorTemp( MAIN_WINDOW, FALSE, (XC_ACE_color_temp *) &ST_COLOR_TEMP );
                               MApi_XC_ACE_PicSetBrightnessInVsync(MAIN_WINDOW, MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cRedOffset, BRIGHTNESS_R ), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cGreenOffset, BRIGHTNESS_G), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cBlueOffset, BRIGHTNESS_B));
                            #endif
                      #endif
                  }
                  else
                 #endif   
                    {
                    #if ENABLE_NEW_COLORTEMP_METHOD
                        #if ENABLE_PRECISE_RGBBRIGHTNESS
                            MApi_XC_ACE_PicSetColorTemp(MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW), (XC_ACE_color_temp_ex *) &ST_COLOR_TEMP);
                        #else
                            MApi_XC_ACE_PicSetColorTemp(MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW), (XC_ACE_color_temp *) &ST_COLOR_TEMP);
                        #endif
                    #else
                #if ENABLE_PRECISE_RGBBRIGHTNESS
                    MApi_XC_ACE_PicSetColorTemp( MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW), (XC_ACE_color_temp_ex *) &ST_COLOR_TEMP );
                    MApi_XC_ACE_PicSetBrightnessPreciseInVsync(MAIN_WINDOW, MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cRedOffset, BRIGHTNESS_R ), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cGreenOffset, BRIGHTNESS_G), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cBlueOffset, BRIGHTNESS_B));
                #else
                    MApi_XC_ACE_PicSetColorTemp( MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW), (XC_ACE_color_temp *) &ST_COLOR_TEMP );
                    MApi_XC_ACE_PicSetBrightnessInVsync(MAIN_WINDOW, MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cRedOffset, BRIGHTNESS_R ), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cGreenOffset, BRIGHTNESS_G), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cBlueOffset, BRIGHTNESS_B));
                #endif
                    #endif
                    }
                    //bRet = TRUE;
                }
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_PIC_ADJ_TEMP_RED);
            return TRUE;


        case EN_EXE_DEC_COLOR_GREEN:
        case EN_EXE_INC_COLOR_GREEN:
            //from case MAPP_UIMENUFUNC_ADJU16B2_COLORTEMP_USER_GREEN:
            {
                BOOLEAN bIsNeedToReset = FALSE;
                //U8 u8TmpGreenScaleValue = ST_COLOR_TEMP.cGreenScaleValue;
                U8 u8ValueTmp = ST_COLOR_TEMP.cGreenColor;
                ST_COLOR_TEMP.cGreenColor = MApp_ZUI_ACT_DecIncValue(
                    act==EN_EXE_INC_COLOR_GREEN,
                    ST_COLOR_TEMP.cGreenColor, MIN_USER_RGB, MAX_USER_RGB, 1);

                ST_COLOR_TEMP.cGreenScaleValue = GetColorTemperatureScale100Value(
                    u8ValueTmp, ST_COLOR_TEMP.cGreenColor,
                    MIN_USER_RGB, MAX_USER_RGB, ST_COLOR_TEMP.cGreenScaleValue, &bIsNeedToReset);
                if (bIsNeedToReset == TRUE) ST_COLOR_TEMP.cGreenColor = u8ValueTmp;

                if ((ST_COLOR_TEMP.cGreenColor == u8ValueTmp) && !bIsNeedToReset)
                {
                    //bRet = FALSE;
                }
                else
                {
               #if VGA_HDMI_YUV_POINT_TO_POINT
                    if(IsHDMIInUse()&&MDrv_PQ_Get_HDMIPCMode())
                    {
                         MApi_XC_ACE_SetPCYUV2RGB(MAIN_WINDOW, FALSE);

                       #if ENABLE_NEW_COLORTEMP_METHOD
                            #if ENABLE_PRECISE_RGBBRIGHTNESS
                               MApi_XC_ACE_PicSetColorTemp(MAIN_WINDOW, FALSE, (XC_ACE_color_temp_ex *) &ST_COLOR_TEMP);
                            #else
                               MApi_XC_ACE_PicSetColorTemp(MAIN_WINDOW, FALSE, (XC_ACE_color_temp *) &ST_COLOR_TEMP);
                            #endif
                      #else
                            #if ENABLE_PRECISE_RGBBRIGHTNESS
                               MApi_XC_ACE_PicSetColorTemp( MAIN_WINDOW, FALSE, (XC_ACE_color_temp_ex *) &ST_COLOR_TEMP );
                               MApi_XC_ACE_PicSetBrightnessPreciseInVsync(MAIN_WINDOW, MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cRedOffset, BRIGHTNESS_R ), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cGreenOffset, BRIGHTNESS_G), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cBlueOffset, BRIGHTNESS_B));
                            #else
                               MApi_XC_ACE_PicSetColorTemp( MAIN_WINDOW, FALSE, (XC_ACE_color_temp *) &ST_COLOR_TEMP );
                               MApi_XC_ACE_PicSetBrightnessInVsync(MAIN_WINDOW, MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cRedOffset, BRIGHTNESS_R ), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cGreenOffset, BRIGHTNESS_G), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cBlueOffset, BRIGHTNESS_B));
                            #endif
                      #endif
                  }
                  else
                 #endif   
                 {   
                    #if ENABLE_NEW_COLORTEMP_METHOD
                        #if ENABLE_PRECISE_RGBBRIGHTNESS
                            MApi_XC_ACE_PicSetColorTemp(MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW), (XC_ACE_color_temp_ex *) &ST_COLOR_TEMP);
                        #else
                            MApi_XC_ACE_PicSetColorTemp(MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW), (XC_ACE_color_temp *) &ST_COLOR_TEMP);
                        #endif
                    #else
                #if ENABLE_PRECISE_RGBBRIGHTNESS
                    MApi_XC_ACE_PicSetColorTemp( MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW), (XC_ACE_color_temp_ex *) &ST_COLOR_TEMP );
                    MApi_XC_ACE_PicSetBrightnessPreciseInVsync(MAIN_WINDOW, MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cRedOffset, BRIGHTNESS_R ), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cGreenOffset, BRIGHTNESS_G), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cBlueOffset, BRIGHTNESS_B));
                #else
                    MApi_XC_ACE_PicSetColorTemp( MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW), (XC_ACE_color_temp *) &ST_COLOR_TEMP );
                    MApi_XC_ACE_PicSetBrightnessInVsync(MAIN_WINDOW, MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cRedOffset, BRIGHTNESS_R ), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cGreenOffset, BRIGHTNESS_G), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cBlueOffset, BRIGHTNESS_B));
                #endif
                    #endif
                  }
                    //bRet = TRUE;
                }
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_PIC_ADJ_TEMP_GREEN);
            return TRUE;

        case EN_EXE_DEC_COLOR_BLUE:
        case EN_EXE_INC_COLOR_BLUE:
            //from case MAPP_UIMENUFUNC_ADJU16B2_COLORTEMP_USER_BLUE:
            {
                BOOLEAN bIsNeedToReset = FALSE;
                //U8 u8TmpBlueScaleValue = ST_COLOR_TEMP.cBlueScaleValue;
                U8 u8ValueTmp = ST_COLOR_TEMP.cBlueColor;
                ST_COLOR_TEMP.cBlueColor = MApp_ZUI_ACT_DecIncValue(
                    act==EN_EXE_INC_COLOR_BLUE,
                    ST_COLOR_TEMP.cBlueColor, MIN_USER_RGB, MAX_USER_RGB, 1);

                ST_COLOR_TEMP.cBlueScaleValue = GetColorTemperatureScale100Value(
                    u8ValueTmp, ST_COLOR_TEMP.cBlueColor,
                    MIN_USER_RGB, MAX_USER_RGB, ST_COLOR_TEMP.cBlueScaleValue, &bIsNeedToReset);
                if (bIsNeedToReset == TRUE) ST_COLOR_TEMP.cBlueColor = u8ValueTmp;

                if ((ST_COLOR_TEMP.cBlueColor == u8ValueTmp) && !bIsNeedToReset)
                {
                    //bRet = FALSE;
                }
                else
                {
               #if VGA_HDMI_YUV_POINT_TO_POINT
                    if(IsHDMIInUse()&&MDrv_PQ_Get_HDMIPCMode())
                    {
                         MApi_XC_ACE_SetPCYUV2RGB(MAIN_WINDOW, FALSE);

                       #if ENABLE_NEW_COLORTEMP_METHOD
                            #if ENABLE_PRECISE_RGBBRIGHTNESS
                               MApi_XC_ACE_PicSetColorTemp(MAIN_WINDOW, FALSE, (XC_ACE_color_temp_ex *) &ST_COLOR_TEMP);
                            #else
                               MApi_XC_ACE_PicSetColorTemp(MAIN_WINDOW, FALSE, (XC_ACE_color_temp *) &ST_COLOR_TEMP);
                            #endif
                      #else
                            #if ENABLE_PRECISE_RGBBRIGHTNESS
                               MApi_XC_ACE_PicSetColorTemp( MAIN_WINDOW, FALSE, (XC_ACE_color_temp_ex *) &ST_COLOR_TEMP );
                               MApi_XC_ACE_PicSetBrightnessPreciseInVsync(MAIN_WINDOW, MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cRedOffset, BRIGHTNESS_R ), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cGreenOffset, BRIGHTNESS_G), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cBlueOffset, BRIGHTNESS_B));
                            #else
                               MApi_XC_ACE_PicSetColorTemp( MAIN_WINDOW, FALSE, (XC_ACE_color_temp *) &ST_COLOR_TEMP );
                               MApi_XC_ACE_PicSetBrightnessInVsync(MAIN_WINDOW, MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cRedOffset, BRIGHTNESS_R ), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cGreenOffset, BRIGHTNESS_G), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cBlueOffset, BRIGHTNESS_B));
                            #endif
                      #endif
                  }
                  else
                 #endif   
                 {  
                    #if ENABLE_NEW_COLORTEMP_METHOD
                        #if ENABLE_PRECISE_RGBBRIGHTNESS
                            MApi_XC_ACE_PicSetColorTemp(MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW), (XC_ACE_color_temp_ex *) &ST_COLOR_TEMP);
                        #else
                            MApi_XC_ACE_PicSetColorTemp(MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW), (XC_ACE_color_temp *) &ST_COLOR_TEMP);
                        #endif
                    #else
                #if ENABLE_PRECISE_RGBBRIGHTNESS
                    MApi_XC_ACE_PicSetColorTemp( MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW), (XC_ACE_color_temp_ex *) &ST_COLOR_TEMP );
                    MApi_XC_ACE_PicSetBrightnessPreciseInVsync(MAIN_WINDOW, MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cRedOffset, BRIGHTNESS_R ), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cGreenOffset, BRIGHTNESS_G), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cBlueOffset, BRIGHTNESS_B));
                #else
                    MApi_XC_ACE_PicSetColorTemp( MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW), (XC_ACE_color_temp *) &ST_COLOR_TEMP );
                    MApi_XC_ACE_PicSetBrightnessInVsync(MAIN_WINDOW, MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cRedOffset, BRIGHTNESS_R ), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cGreenOffset, BRIGHTNESS_G), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cBlueOffset, BRIGHTNESS_B));
                #endif
                    #endif
                    }
                    //bRet = TRUE;
                }
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_PIC_ADJ_TEMP_BLUE);
            return TRUE;
		
		
#if  (ENABLE_HDR)
        case EN_EXE_DEC_HDR:
        case EN_EXE_INC_HDR:
            stGenSetting.g_SysSetting.enHdrSetting = (EN_MS_HDR)MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_HDR,
                     stGenSetting.g_SysSetting.enHdrSetting,EN_HDR_MIN, EN_HDR_NUMS, 1);

            msAPI_RefreshHdrSetting();
           
            MApp_ZUI_API_InvalidateWindow(HWND_MENU_SINGLELIST_COMMON_PAGE_LIST);
            MApp_ZUI_API_InvalidateWindow(HWND_MENU_PICTURE_HDR_OPTION);
            return TRUE;
#endif

        case EN_EXE_DEC_NOISE_REDUCTION:
        case EN_EXE_INC_NOISE_REDUCTION:
            //from case MAPP_UIMENUFUNC_ADJENB3_NR:
            ST_VIDEO.eNRMode.eNR=
                (EN_MS_NR)MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_NOISE_REDUCTION,
                     ST_VIDEO.eNRMode.eNR,MS_NR_MIN, MS_NR_NUM-1, 1);
            if (ST_VIDEO.eNRMode.eNR == MS_NR_AUTO)
            {
                ST_VIDEO.eNRMode.eNR=
                (EN_MS_NR)MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_NOISE_REDUCTION,
                     ST_VIDEO.eNRMode.eNR,MS_NR_MIN, MS_NR_NUM-1, 1);
            }

        #if (ENABLE_NEW_AUTO_NR)
            msAPI_NR_SetDNRDefault();
            if ( MS_NR_LOW == ST_VIDEO.eNRMode.eNR )
            {
                msAPI_NR_SetDNRStatus(E_MAPI_AUTO_NR_STATUS_LOW,E_MAPI_AUTO_NR_STATUS_LOW);
                if(IsATVInUse())
                {
                    MDrv_PQ_LoadNRTable(PQ_MAIN_WINDOW, PQ_3D_NR_AUTO_LOW_L);
                }
                else
                {
                    MDrv_PQ_LoadNRTable(PQ_MAIN_WINDOW, PQ_3D_NR_LOW);
                }
            }
            else if ( (MS_NR_MIDDLE == ST_VIDEO.eNRMode.eNR)
                    ||(MS_NR_DEFAULT == ST_VIDEO.eNRMode.eNR) )
            {
                msAPI_NR_SetDNRStatus(E_MAPI_AUTO_NR_STATUS_MID,E_MAPI_AUTO_NR_STATUS_MID);
                if(IsATVInUse())
                {
                    MDrv_PQ_LoadNRTable(PQ_MAIN_WINDOW, PQ_3D_NR_AUTO_MID_M);
                }
                else
                {
                    MDrv_PQ_LoadNRTable(PQ_MAIN_WINDOW, PQ_3D_NR_MID);
                }
            }
            else if ( MS_NR_HIGH == ST_VIDEO.eNRMode.eNR )
            {
                msAPI_NR_SetDNRStatus(E_MAPI_AUTO_NR_STATUS_HIGH,E_MAPI_AUTO_NR_STATUS_HIGH);
                if(IsATVInUse())
                {
                    MDrv_PQ_LoadNRTable(PQ_MAIN_WINDOW, PQ_3D_NR_AUTO_HIGH_H);
                }
                else
                {
                    MDrv_PQ_LoadNRTable(PQ_MAIN_WINDOW, PQ_3D_NR_HIGH);
                }
            }
            else if( MS_NR_OFF == ST_VIDEO.eNRMode.eNR )
            {
                MApp_PicSetNR( (T_MS_NR_MODE*) &ST_VIDEO.eNRMode, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW) );
            }
        #else
            MApp_PicSetNR( (T_MS_NR_MODE*) &ST_VIDEO.eNRMode, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW) );
        #endif

            MApp_ZUI_API_InvalidateWindow(HWND_MENU_SINGLELIST_COMMON_PAGE_LIST);
            MApp_ZUI_API_InvalidateWindow(HWND_MENU_PICTURE_NOISE_REDUCTION_OPTION);
            return TRUE;


        case EN_EXE_DEC_MPEG_NOISE_REDUCTION:
        case EN_EXE_INC_MPEG_NOISE_REDUCTION:
            ST_VIDEO.eNRMode.eMPEG_NR=
                (EN_MS_MPEG_NR)MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_MPEG_NOISE_REDUCTION,
                     ST_VIDEO.eNRMode.eMPEG_NR,MS_MPEG_NR_MIN, MS_MPEG_NR_NUM-1, 1);

            if( MS_MPEG_NR_LOW == ST_VIDEO.eNRMode.eMPEG_NR )
            {
                MDrv_PQ_LoadMPEGNRTable(PQ_MAIN_WINDOW, PQ_MPEG_NR_LOW);
            }
            else if( MS_MPEG_NR_MIDDLE == ST_VIDEO.eNRMode.eMPEG_NR )
            {
                MDrv_PQ_LoadMPEGNRTable(PQ_MAIN_WINDOW, PQ_MPEG_NR_MID);
            }
            else if( MS_MPEG_NR_HIGH == ST_VIDEO.eNRMode.eMPEG_NR )
            {
                MDrv_PQ_LoadMPEGNRTable(PQ_MAIN_WINDOW, PQ_MPEG_NR_HIGH);
            }
            else if( MS_MPEG_NR_OFF == ST_VIDEO.eNRMode.eMPEG_NR )
            {
                MDrv_PQ_LoadMPEGNRTable(PQ_MAIN_WINDOW, PQ_MPEG_NR_OFF);
            }
            else if( MS_MPEG_NR_DEFAULT == ST_VIDEO.eNRMode.eMPEG_NR )
            {
                MDrv_PQ_LoadMPEGNRTable(PQ_MAIN_WINDOW, PQ_MPEG_NR_DEFAULT);
            }
            MApp_ZUI_API_InvalidateWindow(HWND_MENU_SINGLELIST_COMMON_PAGE_LIST);
            //MApp_ZUI_API_InvalidateWindow(HWND_MENU_PICTURE_MPEG_NOISE_REDUCTION_OPTION);
            return TRUE;


        case EN_EXE_ONOFF_AUTO_VOLUME:
            //from case MAPP_UIMENUFUNC_Audio_C2_AutoVolume:
            stGenSetting.g_SysSetting.fAutoVolume = !stGenSetting.g_SysSetting.fAutoVolume;

            // add AVL function
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            msAPI_Timer_Delayms(30);
            MApi_AUDIO_EnableAutoVolume((BOOLEAN)stGenSetting.g_SysSetting.fAutoVolume);
            msAPI_Timer_Delayms(256);

            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);

            MApp_ZUI_API_InvalidateWindow(HWND_MENU_SOUND_AUTO_VOLUME_OPTION);
            return TRUE;


        case EN_EXE_ONOFF_HARD_HEARING:
        {
          #if ENABLE_DTV
            //from case MAPP_UIMENUFUNC_ADJUST_SUBTITILE_LANGUAGE_HEARING:
            stGenSetting.g_SysSetting.fHardOfHearing = !stGenSetting.g_SysSetting.fHardOfHearing;
           #if (ENABLE_SUBTITLE)
            MApp_TV_SelectSubtileLang();
           #endif
           if(stGenSetting.g_SysSetting.fHardOfHearing)
            {
                if(OSD_COUNTRY_SETTING == OSD_COUNTRY_SWEDEN)
                    stGenSetting.g_SysSetting.fEnableSubTitle = TRUE;
            }
            MApp_ZUI_API_InvalidateWindow(HWND_MENU_OPTION_HARD_HEARING_OPTION);
          #endif
            return TRUE;
        }

#if ENABLE_SUBTITLE_SWITCH_MENU
        case EN_EXE_ONOFF_SUBTITLE_ONOFF:
        {
            MENU_OPTION_SUBTITLE_ON = !MENU_OPTION_SUBTITLE_ON;

            MApp_TV_SelectSubtileLang();

            MApp_ZUI_API_InvalidateWindow(HWND_MENU_OPTION_SUBTITLE_ONOFF_OPTION);

            return TRUE;
        }
#endif

    #if ENABLE_E_POP
        case EN_EXE_ONOFF_EPOP:
        {
            stGenSetting.g_SysSetting.fEpop = !stGenSetting.g_SysSetting.fEpop;
            MApp_ZUI_API_InvalidateWindow(HWND_MENU_OPTION_EPOP_OPTION);
            return TRUE;
        }
    #endif


    #if 0//ENABLE_EDID_SWITCH
        case EN_EXE_ONOFF_EDID_SWITCH:
          #if (  UI_SKIN_SEL == UI_SKIN_1920X1080X565   \
              || UI_SKIN_SEL == UI_SKIN_1366X768X565    \
              || UI_SKIN_SEL == UI_SKIN_1366X768X4444   \
              || UI_SKIN_SEL == UI_SKIN_1366X768X8888   \
              || UI_SKIN_SEL == UI_SKIN_960X540X565     \
              )
           stGenSetting.g_SysSetting.u8EDID_select = !stGenSetting.g_SysSetting.u8EDID_select;
            MApi_XC_Sys_SetHPD_ALL(DISABLE);
            _MApi_XC_DDCRam_Init();
            MApi_XC_Sys_SetHPD_ALL(ENABLE);
            MApp_ZUI_API_InvalidateWindow(HWND_MENU_OPTION_EDID_SWITCH_OPTION);
         #endif
            return TRUE;
    #endif


    #if (ENABLE_MAINPAGE_EFFECT)
        case EN_EXE_DEC_OSD_EFFECT_MODE:
        case EN_EXE_INC_OSD_EFFECT_MODE:
            stGenSetting.g_SysSetting.fEnableOsdAnimation =(U8) MApp_ZUI_ACT_DecIncValue_Cycle(
                act==EN_EXE_INC_OSD_EFFECT_MODE,
                stGenSetting.g_SysSetting.fEnableOsdAnimation, 0, EN_OSD_EFFECT_NUM-1, 1);
            MApp_ZUI_API_InvalidateWindow(HWND_MENU_OPTION_OSD_EFFECT_OPTION);
            return TRUE;
    #endif


    #if ENABLE_3D_PROCESS
        case EN_EXE_3D_TO_2D_MODE_ADJ:
            _MApp_ZUI_ACT_3D_TO_2D_Cycle(TRUE);
            MApp_ZUI_API_InvalidateWindow(HWND_MENU_OPTION_3D_TO_2D_OPTION);
            MApp_ZUI_CTL_DynamicListRefreshContent(HWND_MENU_OPTION_PAGE_LIST);
            MApp_ZUI_ACT_ShowMainMenuBackground(HWND_MENU_BOTTOM_BALL_FOCUS_OPTION);
            MApp_ZUI_API_ShowWindow(HWND_MENU_OPTION_PAGE, SW_SHOW);
            MApp_ZUI_CTL_DynamicListSetItemFocus(HWND_MENU_OPTION_PAGE_LIST, HWND_MENU_OPTION_3D_TO_2D);
            break;
    #endif


        case EN_EXE_ONOFF_LOCK_SYSTEM:
        {
            if(!MApp_MenuFunc_Setup_BlockSysEnterLockPage_Get())
            {
                MApp_ZUI_ACT_ExecuteMainMenuAction(EN_EXE_ENTER_MENU_LOCK_PAGE);
                MApp_MenuFunc_Setup_BlockSysEnterLockPage_Set(!MApp_MenuFunc_Setup_BlockSysEnterLockPage_Get());
                break;
            }
          #if ENABLE_ATSC
            if(IsAtscInUse()|| IsATVInUse()||IsAVInUse())
            {
                MApp_UiMenuFunc_AdjSystemLockMode();
                MApp_ZUI_API_ShowWindow(HWND_MENU_LOCK_PAGE_LIST, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MENU_LOCK_PAGE_LIST, SW_SHOW);
                MApp_ZUI_API_SetFocus(HWND_MENU_LOCK_SYSTEM);
            }
            else
          #endif
            {
                MApp_MenuFunc_Setup_BlockSysLockMode_Set(!MApp_MenuFunc_Setup_BlockSysLockMode_Get());
                if( MApp_MenuFunc_Setup_BlockSysLockMode_Get() == 0 )
                {
                    bStopMonitorBlock = TRUE;
                    bParentalPWPassCheck = TRUE;
                    MApp_Set_MonitorParental(FALSE);
                    MApp_EnableBlockProgramme(FALSE);
                    MApp_ParentalControl_SetBlockStatus(FALSE);
                }
                else
                {
                    bStopMonitorBlock = FALSE;
                    MApp_Set_MonitorParental(TRUE);
                  #if (ENABLE_DTV)
                    if(TRUE == MApp_Get_ParentalBlock_state())
                    {
                        MApp_Set_ParentalBlock_state(DISABLE);
                    }
                  #endif
                }

                MApp_CheckBlockProgramme();
            }

            MApp_ZUI_API_InvalidateWindow(HWND_MENU_LOCK_SYSTEM_OPTION);
            return TRUE;
        }


        //
        //**********************************************************************
        //
        case EN_EXE_DEC_COMMON_ADJ_ITEM1:
        case EN_EXE_INC_COMMON_ADJ_ITEM1:
        {
            return MApp_ZUI_ACT_Action_COMMON_ADJ_ITEM1(act);
            break;
        }

        case EN_EXE_DEC_COMMON_ADJ_ITEM2:
        case EN_EXE_INC_COMMON_ADJ_ITEM2:
        {
            return MApp_ZUI_ACT_Action_COMMON_ADJ_ITEM2(act);
            break;
        }

        case EN_EXE_DEC_COMMON_ADJ_ITEM3:
        case EN_EXE_INC_COMMON_ADJ_ITEM3:
        {
            return MApp_ZUI_ACT_Action_COMMON_ADJ_ITEM3(act);
            break;
        }

        case EN_EXE_DEC_COMMON_ADJ_ITEM4:
        case EN_EXE_INC_COMMON_ADJ_ITEM4:
        {
            return MApp_ZUI_ACT_Action_COMMON_ADJ_ITEM4(act);
            break;
        }

        case EN_EXE_DEC_COMMON_ADJ_ITEM5:
        case EN_EXE_INC_COMMON_ADJ_ITEM5:
        {
            return MApp_ZUI_ACT_Action_COMMON_ADJ_ITEM5(act);
            break;
        }

        case EN_EXE_DEC_COMMON_ADJ_ITEM6:
        case EN_EXE_INC_COMMON_ADJ_ITEM6:
        {
            return MApp_ZUI_ACT_Action_COMMON_ADJ_ITEM6(act);
            break;
        }

        //
        //**********************************************************************
        //


    #if ENABLE_ATSC_MENU_UI
        case EN_EXE_DEC_CC_MODE:
        case EN_EXE_INC_CC_MODE:
            stGenSetting.g_CaptionSetting.u8CCMode = (EN_CAPTIONMENU_MODE)MApp_ZUI_ACT_DecIncValue_Cycle(
            act==EN_EXE_INC_CC_MODE,
            stGenSetting.g_CaptionSetting.u8CCMode, CAPTIONMENU_MODE_OFF, CAPTIONMENU_MODE_NUM-1, 1);
            MApp_UiMenuFunc_CCGetUserCmd();
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTION_CLOSEDCAPTION_ITEM_CCMODE);
            return TRUE;

        case EN_EXE_DEC_BASICSELECTION_CC:
        case EN_EXE_INC_BASICSELECTION_CC:
            {
                EN_CAPTIONMENU_MODE pre_CCMode = (EN_CAPTIONMENU_MODE)stGenSetting.g_CaptionSetting.u8CCMode;
                if(act == EN_EXE_INC_BASICSELECTION_CC)
                {
                    MApp_UiMenuFunc_AdjustCCBasic(TRUE);
                }
                else
                {
                    MApp_UiMenuFunc_AdjustCCBasic(FALSE);
                }
                MApp_ZUI_API_InvalidateWindow(HWND_MENU_OPTION_CLOSEDCAPTION_ITEM_BASICSELECTION);
                if(stGenSetting.g_CaptionSetting.u8CCMode != pre_CCMode)
                {
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTION_CLOSEDCAPTION_ITEM_CCMODE);
                }
            }
            return TRUE;

        case EN_EXE_DEC_ADVANCESELECTION_CC:
        case EN_EXE_INC_ADVANCESELECTION_CC:
            {
                EN_CAPTIONMENU_MODE pre_CCMode = (EN_CAPTIONMENU_MODE)stGenSetting.g_CaptionSetting.u8CCMode;
                if(act == EN_EXE_INC_ADVANCESELECTION_CC)
                {
                    MApp_UiMenuFunc_AdjustCCAdvance(TRUE);
                }
                else
                {
                    MApp_UiMenuFunc_AdjustCCAdvance(FALSE);
                }
                if(stGenSetting.g_CaptionSetting.u8CaptionServiceModeDTV == CAPTIONMENU_SERVICE_OFF)
                {
                    MApp_ZUI_API_EnableWindow(HWND_MENU_OPTION_CLOSEDCAPTION_ITEM_OPTION,FALSE);
                }
                else
                {
                    MApp_ZUI_API_EnableWindow(HWND_MENU_OPTION_CLOSEDCAPTION_ITEM_OPTION, TRUE);
                }
                MApp_ZUI_API_InvalidateWindow(HWND_MENU_OPTION_CLOSEDCAPTION_ITEM_ADVANCESELECTION);
                if(stGenSetting.g_CaptionSetting.u8CCMode != pre_CCMode)
                {
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTION_CLOSEDCAPTION_ITEM_CCMODE);
                }
            }
            return TRUE;

        case EN_EXE_INC_OPTION_CC:
            MApp_ZUI_API_ShowWindow(HWND_MENU_OPTION_CLOSEDCAPTION_PAGE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_TRANSPARENT_BG, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_MENU_OPTION_CCOPTION_PAGE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_MENU_OPTION_CCOPTION_ITEM_MODE);
            if(stGenSetting.g_CaptionSetting.u8CSOptionMode == CAPTIONMENU_OPTIONMODE_DEFAULT)
            {
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTION_CCOPTION_ITEM_FONTSTYLE, FALSE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTION_CCOPTION_ITEM_FONTSIZE, FALSE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTION_CCOPTION_ITEM_FONTEDGESTYLE, FALSE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTION_CCOPTION_ITEM_FONTEDGECOLOR, FALSE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTION_CCOPTION_ITEM_FGCOLOR, FALSE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTION_CCOPTION_ITEM_BGCOLOR, FALSE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTION_CCOPTION_ITEM_FGOPACITY, FALSE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTION_CCOPTION_ITEM_BGOPACITY, FALSE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTION_CCOPTION_ITEM_WINDOWCOLOR, FALSE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTION_CCOPTION_ITEM_WINDOWOPACITY, FALSE);
                MApp_ZUI_API_ShowWindow(HWND_MENU_OPTION_CCOPTION_ITEM_MODE_UP_ARROW,SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MENU_OPTION_CCOPTION_ITEM_MODE_DOWN_ARROW,SW_HIDE);
            }
            else
            {
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTION_CCOPTION_ITEM_FONTSTYLE, TRUE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTION_CCOPTION_ITEM_FONTSIZE, TRUE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTION_CCOPTION_ITEM_FONTEDGESTYLE, TRUE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTION_CCOPTION_ITEM_FONTEDGECOLOR, TRUE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTION_CCOPTION_ITEM_FGCOLOR, TRUE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTION_CCOPTION_ITEM_BGCOLOR, TRUE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTION_CCOPTION_ITEM_FGOPACITY, TRUE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTION_CCOPTION_ITEM_BGOPACITY, TRUE);
            if(g_fCCAttrFlag.fCCAttr_EnableWindowOptionSetting)
            {
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTION_CCOPTION_ITEM_WINDOWCOLOR, TRUE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTION_CCOPTION_ITEM_WINDOWOPACITY, TRUE);
            }
            else
            {
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTION_CCOPTION_ITEM_WINDOWCOLOR, FALSE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_OPTION_CCOPTION_ITEM_WINDOWOPACITY, FALSE);

            }
                MApp_ZUI_API_ShowWindow(HWND_MENU_OPTION_CCOPTION_ITEM_MODE_UP_ARROW,SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_MENU_OPTION_CCOPTION_ITEM_MODE_DOWN_ARROW,SW_SHOW);
            }
            MApp_UiMenu_CreateCCPreviewWin();
            MApp_UiMenu_CC_Preview();
            return TRUE;

        case EN_EXE_INC_CS_VALUE:
            MApp_UiMenuFunc_AdjustCCOptionMode(TRUE);
            if(stGenSetting.g_CaptionSetting.u8CSOptionMode == CAPTIONMENU_OPTIONMODE_DEFAULT)
            {
                MApp_ZUI_API_ShowWindow(HWND_MENU_OPTION_CCOPTION_ITEM_MODE_UP_ARROW,SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MENU_OPTION_CCOPTION_ITEM_MODE_DOWN_ARROW,SW_HIDE);
            }
            else
            {
                MApp_ZUI_API_ShowWindow(HWND_MENU_OPTION_CCOPTION_ITEM_MODE_UP_ARROW,SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_MENU_OPTION_CCOPTION_ITEM_MODE_DOWN_ARROW,SW_SHOW);
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTION_CCOPTION_PAGE);
            MApp_ZUI_CTL_DynamicListRefreshContent(HWND_MENU_OPTION_CCOPTION_PAGE_LIST);
            return TRUE;

        case EN_EXE_DEC_CS_VALUE:
            MApp_UiMenuFunc_AdjustCCOptionMode(FALSE);
            if(stGenSetting.g_CaptionSetting.u8CSOptionMode == CAPTIONMENU_OPTIONMODE_DEFAULT)
            {
                MApp_ZUI_API_ShowWindow(HWND_MENU_OPTION_CCOPTION_ITEM_MODE_UP_ARROW,SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MENU_OPTION_CCOPTION_ITEM_MODE_DOWN_ARROW,SW_HIDE);
            }
            else
            {
                MApp_ZUI_API_ShowWindow(HWND_MENU_OPTION_CCOPTION_ITEM_MODE_UP_ARROW,SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_MENU_OPTION_CCOPTION_ITEM_MODE_DOWN_ARROW,SW_SHOW);
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTION_CCOPTION_PAGE);
            MApp_ZUI_CTL_DynamicListRefreshContent(HWND_MENU_OPTION_CCOPTION_PAGE_LIST);
            return TRUE;

        case EN_EXE_DOWN_CS_MODE:
            if(stGenSetting.g_CaptionSetting.u8CSOptionMode == CAPTIONMENU_OPTIONMODE_DEFAULT)
            {
                MApp_ZUI_API_SetFocus(HWND_MENU_OPTION_CCOPTION_ITEM_MODE);
                return TRUE;// do note pass to navigation, will abort
            }
            else// pass to navigation
                break;
    #endif // #if ENABLE_ATSC_MENU_UI


        case EN_EXE_COLOR_RANGE_SETTING:
          #if ENABLE_COLOR_RANGE_AUTO_SETTING
            if(stGenSetting.g_SysSetting.enCOLORRANGE == EN_COLOR_RANGE_0_255)
            {
                stGenSetting.g_SysSetting.enCOLORRANGE = EN_COLOR_RANGE_16_235;
                MDrv_PQ_SetColorRange(PQ_MAIN_WINDOW, FALSE);
            }
            else if(stGenSetting.g_SysSetting.enCOLORRANGE == EN_COLOR_RANGE_AUTO)
            {
                stGenSetting.g_SysSetting.enCOLORRANGE = EN_COLOR_RANGE_0_255;
                MDrv_PQ_SetColorRange(PQ_MAIN_WINDOW, TRUE);
            }
            else
            {
                stGenSetting.g_SysSetting.enCOLORRANGE = EN_COLOR_RANGE_AUTO;
                if(stGenSetting.g_SysSetting.enAUTOCOLORRANGE != stGenSetting.g_SysSetting.enCOLORRANGE)
                {
                    if(stGenSetting.g_SysSetting.enAUTOCOLORRANGE == EN_COLOR_RANGE_16_235)
                    {
                        MDrv_PQ_SetColorRange(PQ_MAIN_WINDOW, FALSE);
                    }
                    else if(stGenSetting.g_SysSetting.enAUTOCOLORRANGE == EN_COLOR_RANGE_0_255)
                    {
                        MDrv_PQ_SetColorRange(PQ_MAIN_WINDOW, TRUE);
                    }
               }
            }
          #else
            if(stGenSetting.g_SysSetting.enCOLORRANGE == EN_COLOR_RANGE_0_255)
            {
                stGenSetting.g_SysSetting.enCOLORRANGE = EN_COLOR_RANGE_16_235;
                MDrv_PQ_SetColorRange(PQ_MAIN_WINDOW, TRUE);
            }
            else if(stGenSetting.g_SysSetting.enCOLORRANGE == EN_COLOR_RANGE_16_235)
            {
                stGenSetting.g_SysSetting.enCOLORRANGE = EN_COLOR_RANGE_0_255;
                MDrv_PQ_SetColorRange(PQ_MAIN_WINDOW, FALSE);
            }
          #endif
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTION_COLOR_RANGE);
            return TRUE;


        case EN_EXE_SINGLELIST_UP:
            switch(MApp_ZUI_ACT_GetSingleListMode())
            {
            #if (ENABLE_ATSC)
                case EN_COMMON_SINGLELIST_MTS:
                    MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_INC_MTS);
                    break;
            #endif
                case EN_COMMON_SINGLELIST_ASPECT_RATIO:
                    MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_INC_ASPECT_RATIO);
                    break;
#if  (ENABLE_HDR)
                case EN_COMMON_SINGLELIST_HDR:
                    MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_DEC_HDR);
                    break;
#endif
                case EN_COMMON_SINGLELIST_NOISE_REDUCTION:
                    MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_DEC_NOISE_REDUCTION);
                    break;
                case EN_COMMON_SINGLELIST_MPEG_NOISE_REDUCTION:
                    MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_DEC_MPEG_NOISE_REDUCTION);
                    break;
                case EN_COMMON_SINGLELIST_SURROUND_SOUND:
                    MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_DEC_SURROUND_SOUND);
                    break;
                case EN_COMMON_SINGLELIST_TV_SPEAKER:
                    MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_DEC_SOUND_TVSPEAKERS);
                    break;
                case EN_COMMON_SINGLELIST_SLEEP_TIMER:
                    MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_DEC_SLEEP_TIMER);
                    break;
                case EN_COMMON_SINGLELIST_AUTOSLEEP_TIMER:
                    MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_DEC_AUTOSLEEP_TIMER);
                    break;
                case EN_COMMON_SINGLELIST_PARENTAL_GUIDANCE:
                    MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_DEC_PARENTAL_GUIDANCE);
                    break;

            #if (ENABLE_EDID_SWITCH)
                case EN_COMMON_SINGLELIST_EDID:
                    MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_DEC_EDID);
                    break;
            #endif

            #if 0//ENABLE_T_C_COMBO
                case EN_COMMON_SINGLELIST_DVB_SELECT:
                    MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_DVB_TYPE_SELECT);
                    break;
            #endif

            #if (NTV_FUNCTION_ENABLE)
                case EN_COMMON_SINGLELIST_BANDWIDTH_SELECT:
                    MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_BANDWIDTH_TYPE_SELECT);
                    break;
            #endif

            #if (ATSC_CC == ATV_CC)
                case EN_COMMON_SINGLELIST_CC_OPTION:
                    MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_DEC_OPTION_CC_OPTION);
                    break;
            #endif

            #if ENABLE_3D_PROCESS
                case EN_COMMON_SINGLELIST_3D_TYPE:
                    _MApp_ZUI_ACT_DecInc3DType_Cycle(FALSE);
                    break;
            #endif

            #if(ENABLE_SCART_SVIDEO)
                case EN_COMMON_SINGLELIST_SCART_IN:
                    MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_INC_SCARTIN);
                    break;
            #endif
            #if (ENABLE_LANGUAGE_SWITCH_LIST_MENU)
                  case EN_COMMON_SINGLELIST_LANGUAE_PAGE:
                    MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_DEC_LANGUAE_LIST);
					//<<--A-- SMC 20110510
					MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTION_OSDLANG_PAGE);
					//SMC 20110510 --A-->>
                    break;
              #endif

            #if (ENABLE_ATSC)
                case EN_COMMON_SINGLELIST_OSD_TIMEZONE:
                    MApp_UiMenuFunc_AdjTimeZone(FALSE);
                  break;
                case EN_COMMON_SINGLELIST_MENU_LANGUAGE:
                    MApp_UiMenuFunc_AdjustOptionLanguage(FALSE);
                    break;
            #endif
                default:
                    break;
            }
            return TRUE;


        case EN_EXE_SINGLELIST_DOWN:
            switch(MApp_ZUI_ACT_GetSingleListMode())
            {
            #if ENABLE_ATSC
                case EN_COMMON_SINGLELIST_MTS:
                    MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_DEC_MTS);
                    break;
            #endif
                case EN_COMMON_SINGLELIST_ASPECT_RATIO:
                    MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_DEC_ASPECT_RATIO);
                    break;
#if  (ENABLE_HDR)
                case EN_COMMON_SINGLELIST_HDR:
                    MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_INC_HDR);
                    break;
#endif
                case EN_COMMON_SINGLELIST_NOISE_REDUCTION:
                    MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_INC_NOISE_REDUCTION);
                    break;
                case EN_COMMON_SINGLELIST_MPEG_NOISE_REDUCTION:
                    MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_INC_MPEG_NOISE_REDUCTION);
                    break;
                case EN_COMMON_SINGLELIST_SURROUND_SOUND:
                    MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_INC_SURROUND_SOUND);
                    break;
                case EN_COMMON_SINGLELIST_TV_SPEAKER:
                    MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_INC_SOUND_TVSPEAKERS);
                    break;
                case EN_COMMON_SINGLELIST_SLEEP_TIMER:
                    MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_INC_SLEEP_TIMER);
                    break;
                case EN_COMMON_SINGLELIST_AUTOSLEEP_TIMER:
                    MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_INC_AUTOSLEEP_TIMER);
                    break;
                case EN_COMMON_SINGLELIST_PARENTAL_GUIDANCE:
                    MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_INC_PARENTAL_GUIDANCE);
                    break;
#if (ENABLE_EDID_SWITCH)
                case EN_COMMON_SINGLELIST_EDID:
                    MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_INC_EDID);
                    break;
#endif

            #if 0//ENABLE_T_C_COMBO
                case EN_COMMON_SINGLELIST_DVB_SELECT:
                    MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_DVB_TYPE_SELECT);
                    break;
            #endif
            #if (ENABLE_LANGUAGE_SWITCH_LIST_MENU)
                  case EN_COMMON_SINGLELIST_LANGUAE_PAGE:
                    MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_INC_LANGUAE_LIST);
					//<<--A-- SMC 20110510
					MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTION_OSDLANG_PAGE);
					//SMC 20110510 --A-->>
                    break;
              #endif
            #if (NTV_FUNCTION_ENABLE)
                case EN_COMMON_SINGLELIST_BANDWIDTH_SELECT:
                    MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_BANDWIDTH_TYPE_SELECT);
                    break;
            #endif

            #if (ATSC_CC == ATV_CC)
                case EN_COMMON_SINGLELIST_CC_OPTION:
                    MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_INC_OPTION_CC_OPTION);
                    break;
            #endif

            #if ENABLE_3D_PROCESS
                case EN_COMMON_SINGLELIST_3D_TYPE:
                    _MApp_ZUI_ACT_DecInc3DType_Cycle(TRUE);
                    break;
            #endif

            #if(ENABLE_SCART_SVIDEO)
                case EN_COMMON_SINGLELIST_SCART_IN:
                    MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_DEC_SCARTIN);
                    break;
            #endif


            #if (ENABLE_ATSC)
                case EN_COMMON_SINGLELIST_OSD_TIMEZONE:
                    MApp_UiMenuFunc_AdjTimeZone(TRUE);
                  break;
                case EN_COMMON_SINGLELIST_MENU_LANGUAGE:
                    MApp_UiMenuFunc_AdjustOptionLanguage(TRUE);
                    break;
            #endif
                default:
                    break;
            }
            return TRUE;
		case EN_EXE_DEC_OSD_TIME:
        case EN_EXE_INC_OSD_TIME:
              stGenSetting.g_SysSetting.OsdDuration= (EN_OSD_TIME)MApp_ZUI_ACT_DecIncValue_Cycle(
                act==EN_EXE_INC_OSD_TIME,
                stGenSetting.g_SysSetting.OsdDuration, EN_OSD_TIME_5, EN_OSD_TIME_NUM-1, 1);
               MApp_ZUI_API_InvalidateWindow(HWND_MENU_OPTION_DUETIME_OPTION);
               if(stGenSetting.g_SysSetting.OsdDuration==EN_OSD_TIME_ALWAYS)
               {
                    MApp_ZUI_API_KillTimer(HWND_MENU_MASK_BACKGROUND,0);
                    MApp_ZUI_API_KillTimer(HWND_MENU_TRANSPARENT_BG,0);
               }
               else
               {
                   MApp_ZUI_API_SetTimer(HWND_MENU_MASK_BACKGROUND, 0, stGenSetting.g_SysSetting.OsdDuration*5000);
                   MApp_ZUI_API_SetTimer(HWND_MENU_TRANSPARENT_BG, 0, stGenSetting.g_SysSetting.OsdDuration*5000);
               }
            return TRUE;
		
		#if 1//ENABLE_IVIEW
//>>wht121101_1
		//gchen @ 20180322 //MP333
	    case EN_EXE_DEC_PROJECTION_TYPE:
        case EN_EXE_INC_PROJECTION_TYPE:
              stGenSetting.g_SysSetting.ProjectionType= (EN_PROJECTION_TYPE)MApp_ZUI_ACT_DecIncValue_Cycle(
                act==EN_EXE_INC_PROJECTION_TYPE,
                stGenSetting.g_SysSetting.ProjectionType, EN_FRONT_DESKTOP, EN_PROJECTION_TYPE_NUM-1, 1);              
			   
               if(stGenSetting.g_SysSetting.ProjectionType==EN_FRONT_DESKTOP)
               {
					devOPE_Long_Axis_Flip(FALSE);
					devOPE_Short_Axis_Flip(FALSE);
					//printf("\n-FRONT_DESKTOP-\n");
               }
               else if(stGenSetting.g_SysSetting.ProjectionType==EN_FRONT_CEILING)
               {
					devOPE_Long_Axis_Flip(TRUE);
					devOPE_Short_Axis_Flip(TRUE);
					//printf("\n-FRONT_CEILING-\n");
               }
               else if(stGenSetting.g_SysSetting.ProjectionType==EN_REAR_DESKTOP)
               {
					devOPE_Long_Axis_Flip(FALSE);
					devOPE_Short_Axis_Flip(TRUE);
					//printf("\n-REAR_DESKTOP-\n");
               }
               else
               {
					devOPE_Long_Axis_Flip(TRUE);
					devOPE_Short_Axis_Flip(FALSE);
					//printf("\n-REAR_CEILING-\n");
               }
			    //MApp_SaveSysSetting();
			    MApp_ZUI_API_InvalidateWindow(HWND_MENU_PICTURE_PROJECTION_OPTION);
            return TRUE;
		/*
        case EN_EXE_DEC_PROJECTION_TYPE:
        case EN_EXE_INC_PROJECTION_TYPE:
              stGenSetting.g_SysSetting.ProjectionType= (EN_PROJECTION_TYPE)MApp_ZUI_ACT_DecIncValue
_Cycle(
                act==EN_EXE_INC_PROJECTION_TYPE,
                stGenSetting.g_SysSetting.ProjectionType, EN_FRONT_DESKTOP, EN_PROJECTION_TYPE_NUM-1
, 1);              
			   
               if(stGenSetting.g_SysSetting.ProjectionType==EN_FRONT_DESKTOP)
               {
					devOPE_set_Flip(ORTHOGRAPHY);
               }
               else if(stGenSetting.g_SysSetting.ProjectionType==EN_FRONT_CEILING)
               {
					devOPE_set_Flip(INVERSION);
               }
               else if(stGenSetting.g_SysSetting.ProjectionType==EN_REAR_DESKTOP)
               {
					devOPE_set_Flip(INVERSION_MIRROR);
               }
               else
               {
					devOPE_set_Flip(ORTHOGRAPHY_MIRROR);
               }
			    MApp_ZUI_API_InvalidateWindow(HWND_MENU_PICTURE_PROJECTION_OPTION);
            return TRUE;*/
//<<wht121101_1
		case EN_EXE_INC_KEYSTONE_TYPE:
			//act==EN_EXE_INC_PROJECTION_TYPE,
			 MApp_ZUI_ACT_ExecuteMainMenuAction(EN_EXE_INC_KEYSTONE_TYPE);
			printf("keystone\n");
			break;
		case EN_EXE_DEC_KEYSTONE_VALUE:
		case EN_EXE_INC_KEYSTONE_VALUE:
			if(act == EN_EXE_INC_KEYSTONE_VALUE){
				printf("ACTdmp VK_KEYSTONE_PLUS\n");
				stGenSetting.g_SysSetting.KeyStoneValue++;
				if(stGenSetting.g_SysSetting.KeyStoneValue >= 38)
				stGenSetting.g_SysSetting.KeyStoneValue=38;
				 printf("ks2=%d",stGenSetting.g_SysSetting.KeyStoneValue);
				 keystone_correction(stGenSetting.g_SysSetting.KeyStoneValue);
			}else{
				printf("ACTdmp VK_KEYSTONE_MINUS\n");
				stGenSetting.g_SysSetting.KeyStoneValue--;
				if(stGenSetting.g_SysSetting.KeyStoneValue <=-38)
				stGenSetting.g_SysSetting.KeyStoneValue=-38;
				printf("ks1=%d",stGenSetting.g_SysSetting.KeyStoneValue);
				keystone_correction(stGenSetting.g_SysSetting.KeyStoneValue);
			}
			MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_KEYSTONE_VALUE);
			return TRUE;
//>>wht121107_1
        case EN_EXE_DEC_POWER_ON_MUSIC:
        case EN_EXE_INC_POWER_ON_MUSIC:
              stGenSetting.g_SysSetting.UsrPowerOnMusic= MApp_ZUI_ACT_DecIncValue_Cycle(
                act==EN_EXE_INC_POWER_ON_MUSIC,
                stGenSetting.g_SysSetting.UsrPowerOnMusic, POWERON_MUSIC_OFF, POWERON_MUSIC_USER-1, 1);
               MApp_ZUI_API_InvalidateWindow(HWND_MENU_SOUND_POWER_ON_MUSIC_OPTION);
            return TRUE;
//<<wht121107_1
#endif
			            case EN_EXE_OPTIONLIST_LEFT:
            switch(MApp_ZUI_ACT_GetOptionListMode())
            {
                case EN_COMMON_OPTIONLIST_NETWORK_DNS:
                    switch (MApp_ZUI_API_GetFocus())
                    {
                          case HWND_MENU_OPTIONLIST_ITEM2:
                            MApp_ZUI_ACT_ExecuteNetDNSDialogAction(EN_EXE_DEC_NET_DNS_A);
                            break;
                          case HWND_MENU_OPTIONLIST_ITEM3:
                            MApp_ZUI_ACT_ExecuteNetDNSDialogAction(EN_EXE_DEC_NET_DNS_B);
                            break;
                          case HWND_MENU_OPTIONLIST_ITEM4:
                            MApp_ZUI_ACT_ExecuteNetDNSDialogAction(EN_EXE_DEC_NET_DNS_C);
                            break;
                          case HWND_MENU_OPTIONLIST_ITEM5:
                            MApp_ZUI_ACT_ExecuteNetDNSDialogAction(EN_EXE_DEC_NET_DNS_D);
                            break;
                          default:
                            break;
                    }
                    break;
                case EN_COMMON_OPTIONLIST_NETWORK_GW:
                    switch (MApp_ZUI_API_GetFocus())
                    {
                          case HWND_MENU_OPTIONLIST_ITEM2:
                            MApp_ZUI_ACT_ExecuteNetGatewayDialogAction(EN_EXE_DEC_NET_GATEWAY_A);
                            break;
                          case HWND_MENU_OPTIONLIST_ITEM3:
                            MApp_ZUI_ACT_ExecuteNetGatewayDialogAction(EN_EXE_DEC_NET_GATEWAY_B);
                            break;
                          case HWND_MENU_OPTIONLIST_ITEM4:
                            MApp_ZUI_ACT_ExecuteNetGatewayDialogAction(EN_EXE_DEC_NET_GATEWAY_C);
                            break;
                          case HWND_MENU_OPTIONLIST_ITEM5:
                            MApp_ZUI_ACT_ExecuteNetGatewayDialogAction(EN_EXE_DEC_NET_GATEWAY_D);
                            break;
                          default:
                            break;
                    }
                    break;
                case EN_COMMON_OPTIONLIST_NETWORK_IP:
                    switch (MApp_ZUI_API_GetFocus())
                    {
                          case HWND_MENU_OPTIONLIST_ITEM2:
                            MApp_ZUI_ACT_ExecuteNetIPDialogAction(EN_EXE_DEC_NET_IP_A);
                            break;
                          case HWND_MENU_OPTIONLIST_ITEM3:
                            MApp_ZUI_ACT_ExecuteNetIPDialogAction(EN_EXE_DEC_NET_IP_B);
                            break;
                          case HWND_MENU_OPTIONLIST_ITEM4:
                            MApp_ZUI_ACT_ExecuteNetIPDialogAction(EN_EXE_DEC_NET_IP_C);
                            break;
                          case HWND_MENU_OPTIONLIST_ITEM5:
                            MApp_ZUI_ACT_ExecuteNetIPDialogAction(EN_EXE_DEC_NET_IP_D);
                            break;
                          default:
                            break;
                    }
                    break;
                case EN_COMMON_OPTIONLIST_NETWORK_NETMASK:
                    switch (MApp_ZUI_API_GetFocus())
                    {
                          case HWND_MENU_OPTIONLIST_ITEM2:
                            MApp_ZUI_ACT_ExecuteNetNetmaskDialogAction(EN_EXE_DEC_NET_NETMASK_A);
                            break;
                          case HWND_MENU_OPTIONLIST_ITEM3:
                            MApp_ZUI_ACT_ExecuteNetNetmaskDialogAction(EN_EXE_DEC_NET_NETMASK_B);
                            break;
                          case HWND_MENU_OPTIONLIST_ITEM4:
                            MApp_ZUI_ACT_ExecuteNetNetmaskDialogAction(EN_EXE_DEC_NET_NETMASK_C);
                            break;
                          case HWND_MENU_OPTIONLIST_ITEM5:
                            MApp_ZUI_ACT_ExecuteNetNetmaskDialogAction(EN_EXE_DEC_NET_NETMASK_D);
                            break;
                          default:
                            break;
                    }
                    break;
                case EN_COMMON_OPTIONLIST_NETWORK_CONFIG:
#ifdef NETWORK_CONFIG
                    MApp_ZUI_API_ShowWindow(HWND_MENU_CHECK_NETWORK, SW_HIDE);//close network status osd
#endif
                    switch (MApp_ZUI_API_GetFocus())
                    {
                          case HWND_MENU_OPTIONLIST_ITEM1:
                            MApp_ZUI_ACT_ExecuteNetConfigDialogAction(EN_EXE_DEC_NET_CONFIG);
                            break;
                          case HWND_MENU_OPTIONLIST_ITEM2:
                            MApp_ZUI_ACT_ExecuteNetConfigDialogAction(EN_EXE_GOTO_NET_CONFIG_IP);
                            break;
                          case HWND_MENU_OPTIONLIST_ITEM3:
                            MApp_ZUI_ACT_ExecuteNetConfigDialogAction(EN_EXE_GOTO_NET_CONFIG_NETMASK);
                            break;
                          case HWND_MENU_OPTIONLIST_ITEM4:
                            MApp_ZUI_ACT_ExecuteNetConfigDialogAction(EN_EXE_GOTO_NET_CONFIG_GW);
                            break;
                          case HWND_MENU_OPTIONLIST_ITEM5:
                            MApp_ZUI_ACT_ExecuteNetConfigDialogAction(EN_EXE_GOTO_NET_CONFIG_DNS);
                            break;
                          case HWND_MENU_OPTIONLIST_ITEM6:
                            MApp_ZUI_ACT_ExecuteNetConfigDialogAction(EN_EXE_ONOFF_NET_CONFIG_PROXY);
                            break;
                          default:
                            break;
                    }
                    break;
                    case EN_COMMON_OPTIONLIST_SOUND_BALANCE:
                    switch (MApp_ZUI_API_GetFocus())
                    {
                          case HWND_MENU_OPTIONLIST_ITEM2:
                            MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_DEC_BALANCE);
                            break;
                          default:
                            break;
                    }
                    break;

                default:
                    break;
             }
            return TRUE;

		    case EN_EXE_OPTIONLIST_RIGHT:
            switch(MApp_ZUI_ACT_GetOptionListMode())
            {
                case EN_COMMON_OPTIONLIST_NETWORK_DNS:
                    switch (MApp_ZUI_API_GetFocus())
                    {
                          case HWND_MENU_OPTIONLIST_ITEM2:
                            MApp_ZUI_ACT_ExecuteNetDNSDialogAction(EN_EXE_INC_NET_DNS_A);
                            break;
                          case HWND_MENU_OPTIONLIST_ITEM3:
                            MApp_ZUI_ACT_ExecuteNetDNSDialogAction(EN_EXE_INC_NET_DNS_B);
                            break;
                          case HWND_MENU_OPTIONLIST_ITEM4:
                            MApp_ZUI_ACT_ExecuteNetDNSDialogAction(EN_EXE_INC_NET_DNS_C);
                            break;
                          case HWND_MENU_OPTIONLIST_ITEM5:
                            MApp_ZUI_ACT_ExecuteNetDNSDialogAction(EN_EXE_INC_NET_DNS_D);
                            break;
                          default:
                            break;
                    }
                    break;
                case EN_COMMON_OPTIONLIST_NETWORK_GW:
                    switch (MApp_ZUI_API_GetFocus())
                    {
                          case HWND_MENU_OPTIONLIST_ITEM2:
                            MApp_ZUI_ACT_ExecuteNetGatewayDialogAction(EN_EXE_INC_NET_GATEWAY_A);
                            break;
                          case HWND_MENU_OPTIONLIST_ITEM3:
                            MApp_ZUI_ACT_ExecuteNetGatewayDialogAction(EN_EXE_INC_NET_GATEWAY_B);
                            break;
                          case HWND_MENU_OPTIONLIST_ITEM4:
                            MApp_ZUI_ACT_ExecuteNetGatewayDialogAction(EN_EXE_INC_NET_GATEWAY_C);
                            break;
                          case HWND_MENU_OPTIONLIST_ITEM5:
                            MApp_ZUI_ACT_ExecuteNetGatewayDialogAction(EN_EXE_INC_NET_GATEWAY_D);
                            break;
                          default:
                            break;
                    }
                    break;
                case EN_COMMON_OPTIONLIST_NETWORK_IP:
                    switch (MApp_ZUI_API_GetFocus())
                    {
                          case HWND_MENU_OPTIONLIST_ITEM2:
                            MApp_ZUI_ACT_ExecuteNetIPDialogAction(EN_EXE_INC_NET_IP_A);
                            break;
                          case HWND_MENU_OPTIONLIST_ITEM3:
                            MApp_ZUI_ACT_ExecuteNetIPDialogAction(EN_EXE_INC_NET_IP_B);
                            break;
                          case HWND_MENU_OPTIONLIST_ITEM4:
                            MApp_ZUI_ACT_ExecuteNetIPDialogAction(EN_EXE_INC_NET_IP_C);
                            break;
                          case HWND_MENU_OPTIONLIST_ITEM5:
                            MApp_ZUI_ACT_ExecuteNetIPDialogAction(EN_EXE_INC_NET_IP_D);
                            break;
                          default:
                            break;
                    }
                    break;
                case EN_COMMON_OPTIONLIST_NETWORK_NETMASK:
                    switch (MApp_ZUI_API_GetFocus())
                    {
                          case HWND_MENU_OPTIONLIST_ITEM2:
                            MApp_ZUI_ACT_ExecuteNetNetmaskDialogAction(EN_EXE_INC_NET_NETMASK_A);
                            break;
                          case HWND_MENU_OPTIONLIST_ITEM3:
                            MApp_ZUI_ACT_ExecuteNetNetmaskDialogAction(EN_EXE_INC_NET_NETMASK_B);
                            break;
                          case HWND_MENU_OPTIONLIST_ITEM4:
                            MApp_ZUI_ACT_ExecuteNetNetmaskDialogAction(EN_EXE_INC_NET_NETMASK_C);
                            break;
                          case HWND_MENU_OPTIONLIST_ITEM5:
                            MApp_ZUI_ACT_ExecuteNetNetmaskDialogAction(EN_EXE_INC_NET_NETMASK_D);
                            break;
                          default:
                            break;
                    }
                    break;
                case EN_COMMON_OPTIONLIST_NETWORK_CONFIG:
#ifdef NETWORK_CONFIG
                    MApp_ZUI_API_ShowWindow(HWND_MENU_CHECK_NETWORK, SW_HIDE);
#endif
                    switch (MApp_ZUI_API_GetFocus())
                    {
                          case HWND_MENU_OPTIONLIST_ITEM1:
                            MApp_ZUI_ACT_ExecuteNetConfigDialogAction(EN_EXE_INC_NET_CONFIG);
                            break;
                          case HWND_MENU_OPTIONLIST_ITEM2:
                            MApp_ZUI_ACT_ExecuteNetConfigDialogAction(EN_EXE_GOTO_NET_CONFIG_IP);
                            break;
                          case HWND_MENU_OPTIONLIST_ITEM3:
                            MApp_ZUI_ACT_ExecuteNetConfigDialogAction(EN_EXE_GOTO_NET_CONFIG_NETMASK);
                            break;
                          case HWND_MENU_OPTIONLIST_ITEM4:
                            MApp_ZUI_ACT_ExecuteNetConfigDialogAction(EN_EXE_GOTO_NET_CONFIG_GW);
                            break;
                          case HWND_MENU_OPTIONLIST_ITEM5:
                            MApp_ZUI_ACT_ExecuteNetConfigDialogAction(EN_EXE_GOTO_NET_CONFIG_DNS);
                            break;
                          case HWND_MENU_OPTIONLIST_ITEM6:
                            MApp_ZUI_ACT_ExecuteNetConfigDialogAction(EN_EXE_ONOFF_NET_CONFIG_PROXY);
                            break;
                          default:
                            break;
                    }
                    break;
                case EN_COMMON_OPTIONLIST_SOUND_BALANCE:
                    switch (MApp_ZUI_API_GetFocus())
                    {
                          case HWND_MENU_OPTIONLIST_ITEM2:
                            MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_INC_BALANCE);
                            break;
                          default:
                            break;
                    }
                    break;

                default:
                    break;
            }
            return TRUE;
		
        case EN_EXE_DEC_ASPECT_RATIO:
        case EN_EXE_INC_ASPECT_RATIO:
          #if !ENABLE_FBL_ASPECT_RATIO_BY_MVOP
            if(MApi_XC_IsCurrentFrameBufferLessMode())
            {
                MS_DEBUG_MSG(printf("FrameBuffer less mode\n"));
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_COMMON_ADJ_PAGE);
                MApp_ZUI_API_ShowWindow(HWND_MENU_ALERT_WINDOW, SW_SHOW);
                break;
            }
          #endif
          #if 0//ENABLE_3D_PROCESS
              if(MApi_XC_Get_3D_Output_Mode() != E_XC_3D_OUTPUT_MODE_NONE)
              {
                  _MApp_ZUI_ACT_DecInc_3D_AspectRatio_Cycle(act==EN_EXE_INC_ASPECT_RATIO);
              }
              else
          #endif

        #if ENABLE_3D_PROCESS
            if(MApi_XC_Get_3D_Output_Mode() == E_XC_3D_OUTPUT_MODE_NONE)
        #endif
            {
                _MApp_ZUI_ACT_DecIncAspectRatio_Cycle(act==EN_EXE_INC_ASPECT_RATIO);
            }

            MApp_ZUI_API_InvalidateWindow(HWND_MENU_PICTURE_ASPECT_RATIO_OPTION);
            return TRUE;

        #if(ENABLE_SCART_SVIDEO)
        case EN_EXE_DEC_SCARTIN:
        case EN_EXE_INC_SCARTIN:
            stGenSetting.g_SysSetting.fSCARTInputSel=
                MApp_ZUI_ACT_DecIncValue_Cycle(
                act==EN_EXE_INC_SCARTIN,
                stGenSetting.g_SysSetting.fSCARTInputSel,
                EN_SCART_SEL_AV, EN_SCART_SEL_NUM - 1, 1);

            MApp_InputSource_SwitchSource( UI_INPUT_SOURCE_SCART, MAIN_WINDOW );
            MApp_ZUI_API_InvalidateWindow(HWND_MENU_OPTION_SCART_IN_OPTION);
            return TRUE;
        #endif
		/*
        case EN_EXE_DEC_SURROUND_SOUND:
        case EN_EXE_INC_SURROUND_SOUND:
            //from case MAPP_UIMENUFUNC_ADJUST_SURROUNDSOUND:
            do{
                stGenSetting.g_SoundSetting.SurroundSoundMode =(EN_SURROUND_SYSTEM_TYPE)MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_SURROUND_SOUND,
                    stGenSetting.g_SoundSetting.SurroundSoundMode, SURROUND_SYSTEM_OFF, SURROUND_SYSTEM_NUMS-1, 1);

                #if (ENABLE_AUDIO_SURROUND_SRS  ==  ENABLE)
                if ( stGenSetting.g_SoundSetting.SurroundSoundMode == SURROUND_SYSTEM_SRS   )
                    break;
                #endif

                #if ( ENABLE_AUDIO_SURROUND_BBE ==  ENABLE )
                if ( stGenSetting.g_SoundSetting.SurroundSoundMode == SURROUND_SYSTEM_BBE   )
                    break;
                #endif

                #if (ENABLE_AUDIO_SURROUND_VDS  ==  ENABLE)
                if ( stGenSetting.g_SoundSetting.SurroundSoundMode == SURROUND_SYSTEM_VDS   )
                    break;
                #endif

                #if (ENABLE_AUDIO_SURROUND_VSPK  ==  ENABLE)
                if ( stGenSetting.g_SoundSetting.SurroundSoundMode == SURROUND_SYSTEM_VSPK )
                    break;
                #endif

            }while (stGenSetting.g_SoundSetting.SurroundSoundMode != SURROUND_SYSTEM_SURROUNDMAX &&
                          stGenSetting.g_SoundSetting.SurroundSoundMode !=  SURROUND_SYSTEM_OFF
                          #if (ENABLE_AUDIO_SURROUND_DBX  ==  ENABLE)
                          && stGenSetting.g_SoundSetting.SurroundSoundMode !=  SURROUND_SYSTEM_DBX
                          #endif
                          );
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);

            MApp_Aud_SetSurroundMode( stGenSetting.g_SoundSetting.SurroundSoundMode );
            msAPI_Timer_Delayms(256);

            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);

            MApp_ZUI_API_InvalidateWindow(HWND_MENU_SOUND_SURROUND_OPTION);
            return TRUE;
		*/
        case EN_EXE_DEC_SOUND_TVSPEAKERS:
        case EN_EXE_INC_SOUND_TVSPEAKERS:
        {
        #if(ENABLE_CEC)
            stGenSetting.g_SoundSetting.TVspeakerMode=
                (EN_TVspeaker_MODE)MApp_ZUI_ACT_DecIncValue_Cycle(
                                    act==EN_EXE_INC_SOUND_TVSPEAKERS,
                                    stGenSetting.g_SoundSetting.TVspeakerMode,
                                    TVspeaker_Mode_IntSpeaker, TVspecker_Mode_NUM-1, 1);

            MApp_Aud_SetTVSpeaker();

            MApp_ZUI_API_InvalidateWindow(HWND_MENU_SOUND_TV_SPEAKER_OPTION);
        #endif
            return TRUE;
        }


        case EN_EXE_SPDIF_MODE_PCM_AUTO:
        {
            MS_U8 Spdif_Mute_Status=0;
            BOOLEAN bUnMuteRightNow = TRUE;
            stGenSetting.g_SysSetting.fSPDIFMODE = !stGenSetting.g_SysSetting.fSPDIFMODE;

          #if(ENABLE_CHECK_SPDIF_MUTE_STATUS)
            Spdif_Mute_Status = MApi_AUDIO_SPDIF_GetMute_Status(); // 1---Mute, 0---Unmute
          #endif

            if(Spdif_Mute_Status == 0)
                MApi_AUDIO_SPDIF_SetMute(TRUE);

            if ( IsHDMIInUse())
            {
                if (MApi_AUDIO_HDMI_Monitor()) // Non-PCM received
                {
                    if ( stGenSetting.g_SysSetting.fSPDIFMODE == 1 ) // non-PCM
                    {
                        MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_NONPCM); //msAPI_AUD_SPDIF_SetMode(MSAPI_AUD_SPDIF_NONPCM);
                    }
                    else
                    {
                        MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM); //msAPI_AUD_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
                    }
                }
                else
                {
                    MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_STOP); //MApi_AUDIO_SetCommand(MSAPI_AUD_STOP);
                    MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM); //msAPI_AUD_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
                }
            }
#if ENABLE_DVB
            else if(IsDTVInUse())
            {
                MApp_ChannelChange_SearchDefaultAudioLang();
                MApp_Audio_SetAudioLanguage(g_u8AudLangSelected);
            }
#endif
            else
            {
                if ( stGenSetting.g_SysSetting.fSPDIFMODE==1 ) // non-PCM
                {
                    MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_NONPCM); //msAPI_AUD_SPDIF_SetMode(MSAPI_AUD_SPDIF_NONPCM);
                #if( ENABLE_MPLAYER_MOVIE )
                    if(IsStorageInUse() && MApp_MPlayer_IsMoviePlaying())
                    {
                        bUnMuteRightNow = FALSE;
                    }
                #endif
                }
                else
                {
                    MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM); //msAPI_AUD_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
                }
            }
            if(bUnMuteRightNow)
            {
                if(Spdif_Mute_Status == 0)
                    MApi_AUDIO_SPDIF_SetMute(FALSE);
                //else
                    //MApi_AUDIO_SPDIF_SetMute(TRUE);
            }
            else
            {
                msAPI_AUD_SetSpdifMuteDuringLimitedTime(SPDIF_MUTE_LIMITED_TIME);
            }

            MApp_ZUI_API_InvalidateWindow(HWND_MENU_SOUND_SPDIF_MODE_OPTION);
            return TRUE;
        }


        case EN_EXE_DEC_SOUND_MODE:
        case EN_EXE_INC_SOUND_MODE:
            //from case MAPP_UIMENUFUNC_ADJENC1_SOUND:
            stGenSetting.g_SoundSetting.SoundMode = (EN_SOUND_MODE)MApp_ZUI_ACT_DecIncValue_Cycle(
                act==EN_EXE_INC_SOUND_MODE,
                stGenSetting.g_SoundSetting.SoundMode, EN_SoundMode_Standard, EN_SoundMode_Num-1, 1);
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            MApp_Audio_AdjustSoundMode();
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            MApp_ZUI_CTL_DynamicListRefreshContent(HWND_MENU_SOUND_MODE_PAGE_LIST);
            return TRUE;

        case EN_EXE_DEC_TREBLE:
        case EN_EXE_INC_TREBLE:
            {
                //from case MAPP_UIMENUFUNC_ADJU16C1_SOUND_USER_TREBLE:
                //MApp_UiMenuFunc_CheckAudioMode();
                U8 u8ValueTmp = stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Treble;
                stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Treble =
                    MApp_ZUI_ACT_DecIncValue(
                        act==EN_EXE_INC_TREBLE,
                        stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Treble, 0, 100, 1);

                if(stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Treble == u8ValueTmp)
                {
                    //bRet = FALSE;
                }
                else
                {
                    MApi_AUDIO_EnableTone(TRUE);
                    MApi_AUDIO_SetTreble(stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Treble);
                    //bRet = TRUE;
                }
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_SNDMODE_TREBLE);
            return TRUE;

        case EN_EXE_DEC_BASS:
        case EN_EXE_INC_BASS:
            {
                //from case MAPP_UIMENUFUNC_ADJU16C1_SOUND_USER_BASS:
                //MApp_UiMenuFunc_CheckAudioMode();
                U8 u8ValueTmp = stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Bass;
                stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Bass =
                    MApp_ZUI_ACT_DecIncValue(
                        act==EN_EXE_INC_BASS,
                        stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Bass, 0, 100, 1);

                if(stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Bass == u8ValueTmp)
                {
                    //bRet = FALSE;
                }
                else
                {
                    MApi_AUDIO_EnableTone(TRUE);
                    MApi_AUDIO_SetBass(stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Bass);
                }

            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_SNDMODE_BASS);
            return TRUE;
		
		case EN_EXE_DEC_BALANCE:
        case EN_EXE_INC_BALANCE:
            {
                U8 u8ValueTmp = stGenSetting.g_SoundSetting.Balance;
                stGenSetting.g_SoundSetting.Balance = MApp_ZUI_ACT_DecIncValue(
                    act==EN_EXE_INC_BALANCE,
                    stGenSetting.g_SoundSetting.Balance, 0, 100, 1);

                if (stGenSetting.g_SoundSetting.Balance == u8ValueTmp)
                {
                    //bRet = FALSE;
                }
                else
                {
                    MApi_AUDIO_SetBalance(stGenSetting.g_SoundSetting.Balance);
                    //bRet = TRUE;
                }
                   if(msAPI_AUD_IsAudioMutedByUser()==1)
                        MApp_UiMenu_MuteWin_Hide();
                // Force to disable mute no matter what the current mute state is
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);

            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTIONLIST_ITEM2_OPTION);
            return TRUE;
		
        case EN_EXE_DEC_SOUND_120_HZ:
        case EN_EXE_INC_SOUND_120_HZ:
            {
				printf("\r\n gchen @ 20180419 11111 A EQ 120Hz \n");//MP333 eq debug
                //MApp_UiMenuFunc_CheckAudioMode();
                //U8 u8ValueTmp = stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8120HZ;
                stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8120HZ =
                    MApp_ZUI_ACT_DecIncValue(
                        act==EN_EXE_INC_SOUND_120_HZ,
                        stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8120HZ, 0, 100, 1);
                MApi_AUDIO_EnableEQ(TRUE);
                MApi_AUDIO_SetEq(E_EQUALIZER_BAND_1, stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8120HZ);
            }
            MApp_ZUI_API_InvalidateWindow(HWND_MENU_SNDEQ_120_HZ);
            return TRUE;

        case EN_EXE_DEC_SOUND_200_HZ:
        case EN_EXE_INC_SOUND_200_HZ:
            {
				printf("\r\n gchen @ 20180419 11111 A EQ 200Hz \n");//MP333 eq debug
                //from case MAPP_UIMENUFUNC_ADJU16C1_SOUND_USER_200HZ:
                //MApp_UiMenuFunc_CheckAudioMode();
                //U8 u8ValueTmp = stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8200HZ;
                stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8200HZ =
                    MApp_ZUI_ACT_DecIncValue(
                        act==EN_EXE_INC_SOUND_200_HZ,
                        stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8200HZ, 0, 100, 1);
                MApi_AUDIO_EnableEQ(TRUE);
                MApi_AUDIO_SetEq(E_EQUALIZER_BAND_2, stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8200HZ);
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_SNDEQ_200_HZ);
            return TRUE;

        case EN_EXE_DEC_SOUND_500_HZ:
        case EN_EXE_INC_SOUND_500_HZ:
            {
				printf("\r\n gchen @ 20180419 11111 A EQ 500Hz \n");//MP333 eq debug
                //from case MAPP_UIMENUFUNC_ADJU16C1_SOUND_USER_500HZ:
                //MApp_UiMenuFunc_CheckAudioMode();
                //U8 u8ValueTmp = stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8500HZ;
                stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8500HZ =
                    MApp_ZUI_ACT_DecIncValue(
                        act==EN_EXE_INC_SOUND_500_HZ,
                        stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8500HZ, 0, 100, 1);
                MApi_AUDIO_EnableEQ(TRUE);
                MApi_AUDIO_SetEq(E_EQUALIZER_BAND_3, stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8500HZ);
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_SNDEQ_500_HZ);
            return TRUE;

        case EN_EXE_DEC_SOUND_1_2_KHZ:
        case EN_EXE_INC_SOUND_1_2_KHZ:
            {
				printf("\r\n gchen @ 20180419 11111 A EQ 1200Hz \n");//MP333 eq debug
                //from case MAPP_UIMENUFUNC_ADJU16C1_SOUND_USER_1_dot_2_KHZ:
                //MApp_UiMenuFunc_CheckAudioMode();
                //U8 u8ValueTmp = stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8_1_dot_2_KHZ;
                stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8_1_dot_2_KHZ =
                    MApp_ZUI_ACT_DecIncValue(
                        act==EN_EXE_INC_SOUND_1_2_KHZ, stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8_1_dot_2_KHZ, 0, 100, 1);
                MApi_AUDIO_EnableEQ(TRUE);
                MApi_AUDIO_SetEq(E_EQUALIZER_BAND_4, stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8_1_dot_2_KHZ);
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_SNDEQ_1_2_KHZ);
            return TRUE;

        case EN_EXE_DEC_SOUND_3_KHZ:
        case EN_EXE_INC_SOUND_3_KHZ:
            {
				printf("\r\n gchen @ 20180419 11111 A EQ 3000Hz \n");//MP333 eq debug
                //from case MAPP_UIMENUFUNC_ADJU16C1_SOUND_USER_3KHZ:
                //MApp_UiMenuFunc_CheckAudioMode();
                //U8 u8ValueTmp = stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8_3KHZ;
                stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8_3KHZ =
                    MApp_ZUI_ACT_DecIncValue(
                        act==EN_EXE_INC_SOUND_3_KHZ,
                        stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8_3KHZ, 0, 100, 1);
                MApi_AUDIO_EnableEQ(TRUE);
                MApi_AUDIO_SetEq(E_EQUALIZER_BAND_5, stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8_3KHZ);
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_SNDEQ_3_KHZ);
            return TRUE;

        case EN_EXE_DEC_SOUND_7_5_KHZ:
        case EN_EXE_INC_SOUND_7_5_KHZ:
            {
				printf("\r\n gchen @ 20180419 11111 A EQ 7500Hz \n");//MP333 eq debug
                //from case MAPP_UIMENUFUNC_ADJU16C1_SOUND_USER_7_dot_5_KHZ:
                //MApp_UiMenuFunc_CheckAudioMode();
                //U8 u8ValueTmp = stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8_7_dot_5_KHZ;
                stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8_7_dot_5_KHZ =
                    MApp_ZUI_ACT_DecIncValue(
                        act==EN_EXE_INC_SOUND_7_5_KHZ,
                        stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8_7_dot_5_KHZ, 0, 100, 1);
                // equalizer
                MApi_AUDIO_EnableEQ(TRUE);
                MApi_AUDIO_SetEq(E_EQUALIZER_BAND_6, stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8_7_dot_5_KHZ);
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_SNDEQ_7_5_KHZ);
            return TRUE;

        case EN_EXE_DEC_SOUND_12_KHZ:
        case EN_EXE_INC_SOUND_12_KHZ:
            {
				printf("\r\n gchen @ 20180419 11111 A EQ 1200Hz \n");//MP333 eq debug
                //from case MAPP_UIMENUFUNC_ADJU16C1_SOUND_USER_12KHZ:
                //MApp_UiMenuFunc_CheckAudioMode();
                //U8 u8ValueTmp = stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u812KHZ;
                stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u812KHZ =
                    MApp_ZUI_ACT_DecIncValue(
                        act==EN_EXE_INC_SOUND_12_KHZ,
                        stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u812KHZ, 0, 100, 1);
                // equalizer
                MApi_AUDIO_EnableEQ(TRUE);
                MApi_AUDIO_SetEq(E_EQUALIZER_BAND_7, stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u812KHZ);
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_SNDEQ_12_KHZ);
            return TRUE;

        case EN_EXE_GOTO_SET_PASSWORD_DLG:
            //ZUI_TODO: not yet
            return TRUE;

     /*   case EN_EXE_GOTO_AUTOSLEEP_TIMER_PAGE:
            //from case MAPP_UIMENUFUNC_ADJAUTOOFF:
            stGenSetting.g_Time.cAutoSleepFlag=(EN_MENU_TIME_AutoOff)!stGenSetting.g_Time.cAutoSleepFlag;
            MApp_NoSignal_SetAutoSleep((BOOLEAN)stGenSetting.g_Time.cAutoSleepFlag);

            MApp_ZUI_API_InvalidateWindow(HWND_MENU_TIME_SET_AUTO_SLEEP_OPTION);
            return TRUE; */

        case EN_EXE_DEC_SLEEP_TIMER:
        case EN_EXE_INC_SLEEP_TIMER:
            _MApp_ZUI_ACT_DecIncSleepTimer_Cycle(act==EN_EXE_INC_SLEEP_TIMER);
            MApp_ZUI_API_InvalidateWindow(HWND_MENU_SINGLELIST_COMMON_PAGE_LIST);
            return TRUE;

        case EN_EXE_DEC_AUTOSLEEP_TIMER:
        case EN_EXE_INC_AUTOSLEEP_TIMER:
            MApp_ZUI_ACT_DecIncAutoSleepTimer_Cycle(act==EN_EXE_INC_AUTOSLEEP_TIMER);
        #if( ENABLE_NO_OPERATE_AUTO_SLEEP )
            if( MApp_NoOperateAutoSleep_Get_AutoSleepTime() != STATE_AUTOSLEEP_NEVER )
            {
                stGenSetting.g_Time.cAutoSleepFlag = EN_Time_AutoOff_On;
            }
            else
        #endif
            {
               stGenSetting.g_Time.cAutoSleepFlag = EN_Time_AutoOff_Off;
            }

            MApp_ZUI_API_InvalidateWindow(HWND_MENU_SINGLELIST_COMMON_PAGE_LIST);
            return TRUE;

    #if 0//ENABLE_T_C_COMBO
        case EN_EXE_DVB_TYPE_SELECT:
            _MApp_ZUI_ACT_DecIncDVBType_Cycle();
            return TRUE;
    #endif


    #if (NTV_FUNCTION_ENABLE)
        case EN_EXE_BANDWIDTH_TYPE_SELECT:
            _MApp_ZUI_ACT_DecIncBandWidthType_Cycle();
            return FALSE;
    #endif

        case EN_EXE_DEC_TIMEZONE:
        case EN_EXE_INC_TIMEZONE:
            //from case MAPP_UIMENUFUNC_ADJMENUDTIMEZONEVALUE:
          #if ENABLE_SBTVD_DTV_SYSTEM
            if(IS_SBTVD_APP)
            {
                stGenSetting.g_Time.enTimeZone = (EN_MENU_TIMEZONE)MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_TIMEZONE,
                    stGenSetting.g_Time.enTimeZone, TIMEZONE_GMT_Minus5_START, TIMEZONE_GMT_Minus2_END, 1);

                if(MENU_TIMEZONE<=TIMEZONE_GMT_Minus5_END)
                {
                    stGenSetting.g_Time.en_Clock_TimeZone=EN_Clock_TimeZone_20;
                }
                else if(MENU_TIMEZONE>=TIMEZONE_GMT_Minus4_START && MENU_TIMEZONE<=TIMEZONE_GMT_Minus4_END)
                {
                    stGenSetting.g_Time.en_Clock_TimeZone=EN_Clock_TimeZone_22;
                }
                else if(MENU_TIMEZONE>=TIMEZONE_GMT_Minus3_START && MENU_TIMEZONE<=TIMEZONE_GMT_Minus3_END)
                {
                    stGenSetting.g_Time.en_Clock_TimeZone=EN_Clock_TimeZone_24;
                }
                else if(MENU_TIMEZONE>=TIMEZONE_GMT_Minus2_START && MENU_TIMEZONE<=TIMEZONE_GMT_Minus2_END)
                {
                    stGenSetting.g_Time.en_Clock_TimeZone=EN_Clock_TimeZone_26;
                }
                else
                {
                    stGenSetting.g_Time.en_Clock_TimeZone=EN_Clock_TimeZone_24;
                }
            }
            else
          #endif
            {
                stGenSetting.g_Time.enTimeZone = (EN_MENU_TIMEZONE)MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_TIMEZONE,
                    stGenSetting.g_Time.enTimeZone, TIMEZONE_GMT_0_START, TIMEZONE_NUM-1, 1);

                if((MENU_TIMEZONE<=TIMEZONE_GMT_0_END))
                {
                    stGenSetting.g_Time.en_Clock_TimeZone=EN_Clock_TimeZone_24;
                }
                else if(MENU_TIMEZONE>=TIMEZONE_GMT_1_START && MENU_TIMEZONE<=TIMEZONE_GMT_1_END)
                {
                    stGenSetting.g_Time.en_Clock_TimeZone=EN_Clock_TimeZone_26;
                }
                else if(MENU_TIMEZONE>=TIMEZONE_GMT_2_START && MENU_TIMEZONE<=TIMEZONE_GMT_2_END)
                {
                    stGenSetting.g_Time.en_Clock_TimeZone=EN_Clock_TimeZone_28;
                }
                else if(MENU_TIMEZONE>=TIMEZONE_GMT_3_START && MENU_TIMEZONE<=TIMEZONE_GMT_3_END)
                {
                    stGenSetting.g_Time.en_Clock_TimeZone=EN_Clock_TimeZone_30;
                }
                else if(MENU_TIMEZONE>=TIMEZONE_GMT_3Point5_START && MENU_TIMEZONE<=TIMEZONE_GMT_3Point5_END)
                {
                    stGenSetting.g_Time.en_Clock_TimeZone=EN_Clock_TimeZone_31;
                }
                else if(MENU_TIMEZONE>=TIMEZONE_GMT_8_START && MENU_TIMEZONE<=TIMEZONE_GMT_8_END)
                {
                    stGenSetting.g_Time.en_Clock_TimeZone=EN_Clock_TimeZone_40;
                }
                else if(MENU_TIMEZONE>=TIMEZONE_GMT_9Point5_START && MENU_TIMEZONE<=TIMEZONE_GMT_9Point5_END)
                {
                    stGenSetting.g_Time.en_Clock_TimeZone=EN_Clock_TimeZone_43;
                }
                else if(MENU_TIMEZONE>=TIMEZONE_GMT_10_START && MENU_TIMEZONE<=TIMEZONE_GMT_10_END)
                {
                    stGenSetting.g_Time.en_Clock_TimeZone=EN_Clock_TimeZone_44;
                }
                else if(MENU_TIMEZONE>=TIMEZONE_GMT_12_START && MENU_TIMEZONE<=TIMEZONE_GMT_12_END)
                {
                    stGenSetting.g_Time.en_Clock_TimeZone=EN_Clock_TimeZone_48;
                }
                else if(MENU_TIMEZONE == TIMEZONE_AZORES)
                {
                    stGenSetting.g_Time.en_Clock_TimeZone=EN_Clock_TimeZone_22;
                }
            }

        #if ENABLE_DVB
            MApp_SI_SetTimeZone(MApp_GetSITimeZone(stGenSetting.g_Time.enTimeZone));
            MApp_SI_SetClockTimeZone(MApp_GetSIClockTimeZone(stGenSetting.g_Time.en_Clock_TimeZone));
            MApp_SI_Update_Time(MApp_GetAutoSystemTimeFlag());
        #endif

            MApp_Time_SetOnTime();

            MApp_ZUI_API_InvalidateWindow(HWND_MENU_TIME_SET_TIMEZONE_OPTION);
            MApp_ZUI_API_InvalidateWindow(HWND_MENU_TIME_SET_CLOCK_OPTION);
            return TRUE;

        case EN_EXE_DEC_PARENTAL_GUIDANCE:
        case EN_EXE_INC_PARENTAL_GUIDANCE:
            //from case MAPP_UIMENUFUNC_PARENTAL_CONTROL:
#if(ENABLE_DTV)
#if ENABLE_SBTVD_DTV_SYSTEM
  if(IS_SBTVD_APP)
    {
            stGenSetting.g_BlockSysSetting.u8ParentalControl=
               (U8) MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_PARENTAL_GUIDANCE,
                    stGenSetting.g_BlockSysSetting.u8ParentalControl,EN_F4_LockSystem_Min, EN_F4_LockSystem_Max, 2);
    }
  else
#endif
    {
    #if(ENABLE_ZIGGO)
            stGenSetting.g_BlockSysSetting.u8ParentalControl=
               (U8) MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_PARENTAL_GUIDANCE,
                    stGenSetting.g_BlockSysSetting.u8ParentalControl,EN_F4_LockSystem_Min, EN_F4_LockSystem_AllLock, 1);
    #else
        #if(ENABLE_PARENTAL_GUIDANCE_CLASSIFICATION)
            stGenSetting.g_BlockSysSetting.u8ParentalControl=
                (U8)MApp_ZUI_ACT_DecIncParentalRatingClass_Cycle(
                    act==EN_EXE_INC_PARENTAL_GUIDANCE,
                    stGenSetting.g_BlockSysSetting.u8ParentalControl);
        #else
            stGenSetting.g_BlockSysSetting.u8ParentalControl=
               (U8) MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_PARENTAL_GUIDANCE,
                    stGenSetting.g_BlockSysSetting.u8ParentalControl,EN_F4_LockSystem_Min, EN_F4_LockSystem_Max, 1);
        #endif
    #endif
    }
            MApp_Set_ParentalBlock_state(FALSE);
            MApp_ZUI_API_InvalidateWindow(HWND_MENU_LOCK_PARENTAL_GUIDANCE_OPTION);
#endif
            return TRUE;

#if BRAZIL_CC  //ENABLE_SBTVD_BRAZIL_APP
        case EN_EXE_DEC_OPTION_CAPTION:
        case EN_EXE_INC_OPTION_CAPTION:

            if(IsDTVInUse())
            {
                DB_CC_SETTING.enDTVCaptionType=
                (EN_DTV_CAPTION_TYPE) MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_OPTION_CAPTION,
                    DB_CC_SETTING.enDTVCaptionType, DTV_CAPTION_OFF, DTV_CAPTION_ON, 1);
            }
            else if (IsATVInUse() || IsAVInUse() )
            {
                DB_CC_SETTING.enATVCaptionType=
                (EN_ATV_CAPTION_TYPE) MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_OPTION_CAPTION,
                    DB_CC_SETTING.enATVCaptionType, ATV_CAPTION_TYPE_OFF, ATV_CAPTION_TYPE_NUM-1, 1);
            }
            MApp_ZUI_API_InvalidateWindow(HWND_MENU_OPTION_CAPTION_OPTION);
            return TRUE;
#endif
        case EN_EXE_CLOSE_PCMODE_PAGE:
            MApp_ZUI_API_ShowWindow(HWND_MENU_PCMODE_PAGE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_PICTURE_PAGE, SW_SHOW);
            return FALSE; //note: don't eat this action and navigate...
        #if (ENABLE_PIP)
         case EN_EXE_CLOSE_PIP_PAGE:
            if(IsPIPSupported())
            {
                MApp_ZUI_API_ShowWindow(HWND_MENU_PIP_PAGE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MENU_PICTURE_PAGE, SW_SHOW);
            }
            return FALSE; //note: don't eat this action and navigate...
        #endif

#if (ENABLE_EDID_SWITCH)
        case EN_EXE_DEC_EDID:
        case EN_EXE_INC_EDID:
        {
            E_USER_HDMI_EDID_SEL eUserEdid = MApi_XC_Sys_Get_UserEdidSel();
            eUserEdid = (E_USER_HDMI_EDID_SEL)MApp_ZUI_ACT_DecIncValue_Cycle(
            act == EN_EXE_INC_EDID, eUserEdid,
            E_USER_HDMI_EDID_1p4, E_USER_HDMI_EDID_UNKNOWN-1, 1);

            MApp_Func_HDMI_Set_EdidSel(eUserEdid);

            MApp_ZUI_API_InvalidateWindow(HWND_MENU_SINGLELIST_COMMON_PAGE_LIST);
            return TRUE;
        }
#endif

         case EN_EXE_PCMODE_AUTO_ADJ:
            //from case MIA_PC_AUTO_CONFIG
            //from void MAPP_UiMenu_AutoConfig(void)
            {
               // U8 u8ModeIndex;

                if(IsVgaInUse())
                {
                    if(IsSrcTypeVga(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
                    {
                        if(MApp_PCMode_Enable_SelfAuto(ENABLE, MAIN_WINDOW))
                        {   // to do Auto adjust
                            MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                            MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_AUTO_ADJUSTING_MSGBOX);
                            MApp_TopStateMachine_SetTopState(STATE_TOP_DIGITALINPUTS);
                            enMainMenuState = STATE_MENU_INIT;
                            //MApp_PCMode_RunSelfAuto(MAIN_WINDOW);
                        }
                    }
                    else
                    {
                        if(MApp_PCMode_Enable_SelfAuto(ENABLE, SUB_WINDOW))
                        {   // to do Auto adjust
                            MApp_PCMode_RunSelfAuto(SUB_WINDOW);
                        }
                    }
                }

                //note: all values will be changed!
                //MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_PCMODE_PAGE_LIST);
            }
            return TRUE;

        case EN_EXE_DEC_PCMODE_HPOS:                     ///< decrease pcmode h-pos
        case EN_EXE_INC_PCMODE_HPOS:                     ///< increase pcmode h-pos
            //from case MAPP_UIMENUFUNC_ADJU16B7_PCMENU_HPOSITION:
            if(IsSrcTypeVga(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))||IsSrcTypeYPbPr(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
            {
                U16 u16ValueTmp = g_PcadcModeSetting[MAIN_WINDOW].u16HorizontalStart;
                //printf("[HorizontalStart] CUR=%d,MIN=%d,MAX=%d,def=%d\n", u16ValueTmp, MIN_PC_H_START(MAIN_WINDOW), MAX_PC_H_START(MAIN_WINDOW), g_PcadcModeSetting[MAIN_WINDOW].u16DefaultHStart);
                g_PcadcModeSetting[MAIN_WINDOW].u16HorizontalStart =
                    MApp_ZUI_ACT_DecIncValue(
                        act==EN_EXE_INC_PCMODE_HPOS,
                        g_PcadcModeSetting[MAIN_WINDOW].u16HorizontalStart, MIN_PC_H_START(MAIN_WINDOW), MAX_PC_H_START(MAIN_WINDOW), 1);

                if( IsSrcTypeYPbPr(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) )
                    MApi_XC_Set_Ypbpr_HPosition(u16ValueTmp, g_PcadcModeSetting[MAIN_WINDOW].u16HorizontalStart, MAIN_WINDOW);
                else
                    MApi_XC_Set_PC_HPosition((g_PcadcModeSetting[MAIN_WINDOW].u16DefaultHStart* 2 -g_PcadcModeSetting[MAIN_WINDOW].u16HorizontalStart), MAIN_WINDOW);

                MApp_SetSaveModeDataFlag();

                MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_PCMODE_HPOS);

            }
            #if (ENABLE_PIP)
            else if((MApp_Get_PIPMode() != EN_PIP_MODE_OFF) && (IsSrcTypeVga(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))||IsSrcTypeYPbPr(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))/*IsVgaInUse() || IsYPbPrInUse()*/)
            {
                U16 u16ValueTmp = g_PcadcModeSetting[SUB_WINDOW].u16HorizontalStart;
                g_PcadcModeSetting[SUB_WINDOW].u16HorizontalStart =
                    MApp_ZUI_ACT_DecIncValue(
                        act==EN_EXE_INC_PCMODE_HPOS,
                        g_PcadcModeSetting[SUB_WINDOW].u16HorizontalStart, MIN_PC_H_START(SUB_WINDOW), MAX_PC_H_START(SUB_WINDOW), 1);

                if( IsSrcTypeYPbPr(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) )
                    MApi_XC_Set_Ypbpr_HPosition(u16ValueTmp, g_PcadcModeSetting[SUB_WINDOW].u16HorizontalStart, SUB_WINDOW);
                else
                    MApi_XC_Set_PC_HPosition(g_PcadcModeSetting[SUB_WINDOW].u16HorizontalStart, SUB_WINDOW);

                MApp_SetSaveModeDataFlag();

                MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_PCMODE_HPOS);

            }
            #endif
            return TRUE;

        case EN_EXE_DEC_PCMODE_VPOS:                     ///< decrease pcmode V-pos
        case EN_EXE_INC_PCMODE_VPOS:                     ///< increase pcmode V-pos
            //from case MAPP_UIMENUFUNC_ADJU16B7_PCMENU_VPOSITION:
            if(IsSrcTypeVga(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))||IsSrcTypeYPbPr(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
            {

                U16 u16ValueTmp = g_PcadcModeSetting[MAIN_WINDOW].u16VerticalStart;
                g_PcadcModeSetting[MAIN_WINDOW].u16VerticalStart =
                    MApp_ZUI_ACT_DecIncValue(
                        act==EN_EXE_INC_PCMODE_VPOS,
                        g_PcadcModeSetting[MAIN_WINDOW].u16VerticalStart, MIN_PC_V_START, MAX_PC_V_START(MAIN_WINDOW), 1);

                if(IsSrcTypeYPbPr(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
                    MApi_XC_Set_Ypbpr_VPosition(u16ValueTmp, g_PcadcModeSetting[MAIN_WINDOW].u16VerticalStart, MAIN_WINDOW);
                else
                    MApi_XC_Set_PC_VPosition(g_PcadcModeSetting[MAIN_WINDOW].u16VerticalStart,MAIN_WINDOW);

                MApp_SetSaveModeDataFlag();

                MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_PCMODE_VPOS);

            }
            #if (ENABLE_PIP)
            else if((MApp_Get_PIPMode() != EN_PIP_MODE_OFF)&&(IsSrcTypeVga(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))||IsSrcTypeYPbPr(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))))
            {

                U16 u16ValueTmp = g_PcadcModeSetting[SUB_WINDOW].u16VerticalStart;
                g_PcadcModeSetting[SUB_WINDOW].u16VerticalStart =
                    MApp_ZUI_ACT_DecIncValue(
                        act==EN_EXE_INC_PCMODE_VPOS,
                        g_PcadcModeSetting[SUB_WINDOW].u16VerticalStart, MIN_PC_V_START, MAX_PC_V_START(SUB_WINDOW), 1);

                if(IsSrcTypeYPbPr(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
                    MApi_XC_Set_Ypbpr_VPosition(u16ValueTmp, g_PcadcModeSetting[SUB_WINDOW].u16VerticalStart, SUB_WINDOW);
                else
                    MApi_XC_Set_PC_VPosition(g_PcadcModeSetting[SUB_WINDOW].u16VerticalStart,SUB_WINDOW);

                MApp_SetSaveModeDataFlag();

                MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_PCMODE_VPOS);

            }
            #endif
            return TRUE;

        case EN_EXE_DEC_PCMODE_SIZE:                     ///< decrease pcmode size
        case EN_EXE_INC_PCMODE_SIZE:                     ///< increase pcmode size
            //from case MAPP_UIMENUFUNC_ADJU16B7_PCMENU_SIZE:
            if(IsSrcTypeVga(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
            {
                U16 u16ValueTmp = g_PcadcModeSetting[MAIN_WINDOW].u16HorizontalTotal;
                if(IsSrcTypeVga(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
                {
                    g_PcadcModeSetting[MAIN_WINDOW].u16HorizontalTotal =
                        MApp_ZUI_ACT_DecIncValue(
                            act==EN_EXE_INC_PCMODE_SIZE,
                            g_PcadcModeSetting[MAIN_WINDOW].u16HorizontalTotal, MIN_PC_CLOCK(MAIN_WINDOW), MAX_PC_CLOCK(MAIN_WINDOW), 1);
                    stLMGenSetting.stMB.u16B7_PCMenu_Size = g_PcadcModeSetting[MAIN_WINDOW].u16HorizontalTotal;
                }

                if(g_PcadcModeSetting[MAIN_WINDOW].u16HorizontalTotal == u16ValueTmp)
                {
                    //bRet = FALSE;
                }
                else
                {
                    MApi_XC_ADC_SetPcClock(stLMGenSetting.stMB.u16B7_PCMenu_Size);
                }

                MApp_SetSaveModeDataFlag();

                MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_PCMODE_SIZE);

            }
            #if (ENABLE_PIP)
            else if((MApp_Get_PIPMode() != EN_PIP_MODE_OFF)&&(IsSrcTypeVga(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))))
            {
                U16 u16ValueTmp = g_PcadcModeSetting[SUB_WINDOW].u16HorizontalTotal;
                if(IsSrcTypeVga(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
                {
                    g_PcadcModeSetting[SUB_WINDOW].u16HorizontalTotal =
                        MApp_ZUI_ACT_DecIncValue(
                            act==EN_EXE_INC_PCMODE_SIZE,
                            g_PcadcModeSetting[SUB_WINDOW].u16HorizontalTotal, MIN_PC_CLOCK(SUB_WINDOW), MAX_PC_CLOCK(SUB_WINDOW), 1);
                    stLMGenSetting.stMB.u16B7_PCMenu_Size = g_PcadcModeSetting[SUB_WINDOW].u16HorizontalTotal;
                }

                if(g_PcadcModeSetting[SUB_WINDOW].u16HorizontalTotal == u16ValueTmp)
                {
                    //bRet = FALSE;
                }
                else
                {
                    MApi_XC_ADC_SetPcClock(stLMGenSetting.stMB.u16B7_PCMenu_Size);
                }

                MApp_SetSaveModeDataFlag();

                MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_PCMODE_SIZE);

            }
            #endif
            return TRUE;

        case EN_EXE_DEC_PCMODE_PHASE:                     ///< decrease pcmode phase
        case EN_EXE_INC_PCMODE_PHASE:                     ///< increase pcmode phase
            //from case MAPP_UIMENUFUNC_ADJU16B7_PCMENU_PHASE:
            if(IsSrcTypeVga(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
            {
                U16 u16ValueTmp = g_PcadcModeSetting[MAIN_WINDOW].u16Phase;
                g_PcadcModeSetting[MAIN_WINDOW].u16Phase = MApp_ZUI_ACT_DecIncValue(
                    act==EN_EXE_INC_PCMODE_PHASE,
                    g_PcadcModeSetting[MAIN_WINDOW].u16Phase, MIN_PC_PHASE, MAX_PC_PHASE, 1);
                stLMGenSetting.stMB.u16B7_PCMenu_Phase = g_PcadcModeSetting[MAIN_WINDOW].u16Phase;
                if(g_PcadcModeSetting[MAIN_WINDOW].u16Phase == u16ValueTmp)
                {
                    //bRet = FALSE;
                }
                else
                {
                    MApi_XC_ADC_SetPhase(stLMGenSetting.stMB.u16B7_PCMenu_Phase);
                }
                MApp_SetSaveModeDataFlag();

                MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_PCMODE_PHASE);

            }
            #if (ENABLE_PIP)
            else if((MApp_Get_PIPMode() != EN_PIP_MODE_OFF)&&(IsSrcTypeVga(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))))
            {
                U16 u16ValueTmp = g_PcadcModeSetting[SUB_WINDOW].u16Phase;
                g_PcadcModeSetting[SUB_WINDOW].u16Phase = MApp_ZUI_ACT_DecIncValue(
                    act==EN_EXE_INC_PCMODE_PHASE,
                    g_PcadcModeSetting[SUB_WINDOW].u16Phase, MIN_PC_PHASE, MAX_PC_PHASE, 1);
                stLMGenSetting.stMB.u16B7_PCMenu_Phase = g_PcadcModeSetting[SUB_WINDOW].u16Phase;
                if(g_PcadcModeSetting[SUB_WINDOW].u16Phase == u16ValueTmp)
                {
                    //bRet = FALSE;
                }
                else
                {
                    MApi_XC_ADC_SetPhase(stLMGenSetting.stMB.u16B7_PCMenu_Phase);
                }
                MApp_SetSaveModeDataFlag();

                MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_PCMODE_PHASE);

            }
            #endif
            return TRUE;
        #if (ENABLE_PIP)
        case EN_EXE_DEC_PIP_SOUND_SRC:
        case EN_EXE_INC_PIP_SOUND_SRC:
            if(IsPIPSupported())
            {
                    stGenSetting.g_stPipSetting.enPipSoundSrc=
                (EN_PIP_SOUND_SRC) MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_PIP_SOUND_SRC,
                    stGenSetting.g_stPipSetting.enPipSoundSrc, EN_PIP_SOUND_SRC_MAIN, EN_PIP_SOUND_SRC_SUB, 1);

                if(stGenSetting.g_stPipSetting.enPipSoundSrc==EN_PIP_SOUND_SRC_MAIN)
                {
                    MApp_InputSource_PIP_ChangeAudioSource(MAIN_WINDOW);
                }
                else if(stGenSetting.g_stPipSetting.enPipSoundSrc==EN_PIP_SOUND_SRC_SUB)
                {
                    MApp_InputSource_PIP_ChangeAudioSource(SUB_WINDOW);
                }
                MApp_ZUI_API_InvalidateWindow(HWND_MENU_PIP_SOUND_SRC_OPTION);
                return TRUE;
            }
            return FALSE;

        case EN_EXE_DEC_PIP_BORDER:
        case EN_EXE_INC_PIP_BORDER:
            if(IsPIPSupported())
            {
                stGenSetting.g_stPipSetting.bBolderEnable = !stGenSetting.g_stPipSetting.bBolderEnable;
                MApi_XC_EnableBorder(stGenSetting.g_stPipSetting.bBolderEnable, SUB_WINDOW);
                MApp_ZUI_API_InvalidateWindow(HWND_MENU_PIP_BORDER_OPTION);
                return TRUE;
            }
            return FALSE;

        case EN_EXE_DEC_PIPMODE:
        case EN_EXE_INC_PIPMODE:
            if(IsPIPSupported())
            {
                EN_PIP_MODE enPIPMode;
                enPIPMode = stGenSetting.g_stPipSetting.enPipMode;
                U8 u8PipModeCount = 0;

                u8PipModeCount = 0;
                do
                {
                    enPIPMode=(EN_PIP_MODE) MApp_ZUI_ACT_DecIncValue_Cycle(
                                act==EN_EXE_INC_PIPMODE,
                                enPIPMode, EN_PIP_MODE_OFF, EN_PIP_MODE_MAX, 1);
                     u8PipModeCount ++;

                }
                while((!MApp_Check_PIPMode_Supported(enPIPMode)) ||u8PipModeCount <= (EN_PIP_MODE_MAX+1));

                MApp_Set_PIPMode(enPIPMode,NULL,NULL);
                MApp_ZUI_API_InvalidateWindow(HWND_MENU_PIP_PIPMODE_OPTION);
                MApp_ZUI_CTL_DynamicListRefreshContent(HWND_MENU_PIP_PAGE_LIST);
                return TRUE;
            }
            return FALSE;

        case EN_EXE_DEC_SUBSRC:
        case EN_EXE_INC_SUBSRC:
            if(IsPIPSupported())
            {
                E_UI_INPUT_SOURCE enSubSource = stGenSetting.g_stPipSetting.enSubInputSourceType;
            #if ENABLE_S2
                UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_S2;
            #elif ENABLE_DVBT
                UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBT;
            #elif ENABLE_DVBC
                UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBC;
            #elif ENABLE_DTMB
                UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DTMB;
            #elif ENABLE_ISDBT
                UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ISDBT;
            #else
                UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBT;
            #endif

                do{
                enSubSource=
                    (E_UI_INPUT_SOURCE) MApp_ZUI_ACT_DecIncValue_Cycle(
                      act==EN_EXE_INC_SUBSRC,
                #if(ENABLE_DTV)
                      enSubSource, UI_SUB_INPUT_SOURCE_TYPE, UI_INPUT_SOURCE_NUM-1, 1);
                #else
                      enSubSource, UI_INPUT_SOURCE_ATV, UI_INPUT_SOURCE_NUM-1, 1);
                #endif
                }while(!MApp_InputSource_PIP_IsSrcCompatible(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),
                            MApp_InputSource_GetInputSourceType(enSubSource)));

                MApp_InputSource_PIP_ChangeSource(enSubSource);
                MApp_ZUI_API_InvalidateWindow(HWND_MENU_PIP_SUBSRC_OPTION);
                return TRUE;
            }
            return FALSE;

        case EN_EXE_DEC_PIP_SIZE:
        case EN_EXE_INC_PIP_SIZE:
            if(IsPIPSupported())
            {
                EN_PIP_SIZE  enPipSize =stGenSetting.g_stPipSetting.enPipSize;

                enPipSize=
                    (EN_PIP_SIZE) MApp_ZUI_ACT_DecIncValue_Cycle(
                                act==EN_EXE_INC_PIP_SIZE,
                                enPipSize, EN_PIP_SIZE_SMALL, EN_PIP_SIZE_LARGE, 1);

                MApp_Set_PIPSize(enPipSize,NULL);
                MApp_ZUI_API_InvalidateWindow(HWND_MENU_PIP_SIZE_OPTION);
                return TRUE;
            }
            return FALSE;

        case EN_EXE_DEC_PIP_POSITION:
        case EN_EXE_INC_PIP_POSITION:
            if(IsPIPSupported())
            {
                EN_PIP_POSITION  enPipPosition =stGenSetting.g_stPipSetting.enPipPosition;
                enPipPosition=
                    (EN_PIP_POSITION) MApp_ZUI_ACT_DecIncValue_Cycle(
                        act==EN_EXE_INC_PIP_POSITION,
                        enPipPosition, EN_PIP_POSITION_LEFT_TOP, EN_PIP_POSITION_RIGHT_BOTTOM, 1);

                MApp_Set_PIPPosition(enPipPosition,NULL);
                MApp_ZUI_API_InvalidateWindow(HWND_MENU_PIP_POSITION_OPTION);
                return TRUE;
            }
            return FALSE;

        case EN_EXE_PIP_SWAP:
            if(IsPIPSupported())
            {
                //printf("Enter PIP swap api...\n");
                MApp_InputSource_PIP_Swap();
                MApp_ZUI_API_InvalidateWindow(HWND_MENU_PIP_SUBSRC_OPTION);
                return TRUE;
            }
            return FALSE;
        #endif //#if (ENABLE_PIP)

    #if (ATSC_CC == ATV_CC)
        case EN_EXE_DEC_OPTION_CC_OPTION:
        case EN_EXE_INC_OPTION_CC_OPTION:
            DB_CC_SETTING.enATVCaptionType=
                (EN_ATV_CAPTION_TYPE)MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_OPTION_CC_OPTION,
                     (U16)(DB_CC_SETTING.enATVCaptionType),0, (U16)ATV_CAPTION_TYPE_NUM-1, 1);
//            MApp_PicSetNR( (T_MS_NR_MODE*) &ST_VIDEO.eNRMode, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW) );
            MApp_ZUI_API_InvalidateWindow(HWND_MENU_SINGLELIST_COMMON_PAGE_LIST);
            MApp_ZUI_API_InvalidateWindow(HWND_MENU_OPTION_CC_OPTION_OPTION);
            break;
    #endif // #if (ATSC_CC == ATV_CC)


    #if ENABLE_3D_PROCESS

        case EN_EXE_3D_DETECT_MODE_ADJ:
            _MApp_ZUI_ACT_DecInc3DDetectMode_Cycle(TRUE);
            break;
        case EN_EXE_3D_LR_MODE_ADJ:
            _MApp_ZUI_ACT_DecInc3DLRMode_Cycle(TRUE);
            break;
        case EN_EXE_3D_HSHIFT_MODE_ADJ:
            _MApp_ZUI_ACT_DecInc3DHShift_Cycle(TRUE);
            break;
        case EN_EXE_3D_VIEW_POINT_MODE_ADJ:
            _MApp_ZUI_ACT_DecInc3DViewPoint_Cycle(TRUE);
            break;

      #if (ENABLE_EXTERN_MFC_CHIP)
        case EN_EXE_GOTO_MFC_PAGE:
            g_mainpage_common = EN_COMMON_SET_MFC_PAGE;
            MApp_ZUI_API_ShowWindow(HWND_MENU_OPTION_PAGE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_MASK_BACKGROUND, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_TRANSPARENT_BG, SW_SHOW);
            //MApp_ZUI_API_ShowWindow(HWND_MENU_OPTION_MFC_PAGE, SW_SHOW);
            //MApp_ZUI_API_SetFocus(HWND_MENU_OPTION_MFC_SET_MFC);
            MApp_ZUI_API_ShowWindow(HWND_MENU_COMMON_ADJ_PAGE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_MENU_COMMON_ADJ_ITEM2);
            break;

        case EN_EXE_6M30_MIRROR_MODE_ADJ:
            _MApp_ZUI_ACT_DecInc6M30Mirror_Cycle(TRUE);
            break;
      #endif

    #endif // #if ENABLE_3D_PROCESS

//===


    #if ENABLE_CEC
        case EN_EXE_HDMI_CEC_ADJ:
        {
            CEC_UI_MSG( printf("\n [%d] EN_EXE_HDMI_CEC_ADJ \n", __LINE__) );

            DB_HDMI_SETTING.g_bHdmiCecMode ^= 1;
            if (DB_HDMI_SETTING.g_bHdmiCecMode)
            {
                MApp_ZUI_API_EnableWindow(HWND_MENU_HDMI_CEC_ARC, ENABLE);
            }
            else
            {
                DB_HDMI_SETTING.g_enHDMIARC = ENABLE;
            #if (CEC_VERSION_USING == CEC_NEW_VERSION)
                msAPI_CEC_ARC_TX_Control(FALSE);
            #else
                MDrv_HDMI_ARC_PINControl(INPUT_PORT_DVI0, FALSE, FALSE);
            #endif
                MApp_ZUI_API_EnableWindow(HWND_MENU_HDMI_CEC_ARC, DISABLE);
            }

            MApp_ZUI_API_InvalidateWindow(HWND_MENU_HDMI_CEC_HDMI);
            MApp_ZUI_API_InvalidateWindow(HWND_MENU_HDMI_CEC_ARC);
            return TRUE;
        }

        case EN_EXE_HDMI_ARC_ADJ:
        {
            CEC_UI_MSG( printf("\n [%d] EN_EXE_HDMI_ARC_ADJ \n", __LINE__) );

            stGenSetting.stHDMISetting.g_enHDMIARC ^= 1;

          #if 0
            if (stGenSetting.stHDMISetting.g_enHDMIARC == TRUE)
            {
                msAPI_CEC_ARC_Off2On();
            }
            else
            {
                msAPI_CEC_ARC_On2Off();
            }
          #else
            if (stGenSetting.stHDMISetting.g_enHDMIARC == TRUE)
            {
                msAPI_CEC_RequestARCAction(CEC_ARC_REQUEST_INITIATION);
            }
            else
            {
                msAPI_CEC_RequestARCAction(CEC_ARC_REQUEST_TERMINATION);
            }
          #endif

            MApp_ZUI_API_InvalidateWindow(HWND_MENU_HDMI_CEC_HDMI);
            MApp_ZUI_API_InvalidateWindow(HWND_MENU_HDMI_CEC_ARC);

            return TRUE;
        }

        case EN_EXE_HDMI_CEC_FUNCTION:
        {
            U8 j;

            CEC_UI_MSG( printf("\n [%d] EN_EXE_HDMI_CEC_FUNCTION \n", __LINE__) );

            g_stMenuCecDeviceList.u8CECDeviceNum = 0;
            for (j=E_LA_TV; j<E_LA_MAX; j++)
            {
                g_stMenuCecDeviceList.au8CecDeviceName[j][0] = '\0';
                g_stMenuCecDeviceList.aenDeviceLA[j] = E_LA_UNREGISTERED;
                g_stMenuCecDeviceList.wPhyAddr[j] = 0;
            }
#if ENABLE_ATSC_TTS
            MApp_TTS_Cus_Add_Str_By_StrId(en_str_HDMI_Device_Searching);
            MApp_TTSControlSetOn(TRUE);
#endif
            MApp_ZUI_API_ShowWindow(HWND_MENU_HDMI_CEC_PAGE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_TRANSPARENT_BG, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_MENU_HDMI_CEC_DEVICE_LIST_PAGE, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_MENU_HDMI_CEC_DEVICE_LIST_PAGE_LIST, SW_HIDE);

            msAPI_CEC_ForceImmediatelyPolling(TRUE);

            MApp_ZUI_API_SetTimer(HWND_MENU_HDMI_CEC_DEVICE_SEARCHING, 0, CEC_DEVICE_REFRESH_TIME);

            return TRUE;
        }

        case EN_EXE_HDMI_CEC_SELECT:
        {
            if (MApp_ZUI_API_GetFocus() == HWND_MENU_HDMI_CEC_HDMI)
            {
                CEC_UI_MSG( printf("\n [%d] HWND_MENU_HDMI_CEC_HDMI(%d) \n", __LINE__, DB_HDMI_SETTING.g_bHdmiCecMode) );

                if ( stGenSetting.stHDMISetting.g_bHdmiCecMode == ENABLE)
                {
            #if 1 // Move to MApp_CEC_Set_Enable()
                    MApp_CEC_Set_Enable(DISABLE);

            #else
                #if (CEC_VERSION_USING == CEC_NEW_VERSION)

                  #if (!ENABLE_ARC_CHANGE_SPDIF)
                    msAPI_CEC_ARC_TX_Control(FALSE);
                  #endif

                    if ( msAPI_CEC_IsDeviceExist(E_LA_AUDIO_SYS) )
                    {
                        if (stGenSetting.stHDMISetting.g_enHDMIARC == TRUE)
                        {
                            msAPI_CEC_PostMsg_RequestARCTermination(DIRECTMSG, E_LA_AUDIO_SYS);
                        }

                      #if (AMP_OFF_IF_CEC_OFF)
                        msAPI_CEC_TxMsgSystemAudioModeRequest(DIRECTMSG, FALSE);
                      #else
                        msAPI_CEC_TxMsgSystemAudioModeRequest(DIRECTMSG, TRUE);
                      #endif
                    }

                    msAPI_CEC_SetSystemUnMute();

                #else

                    MDrv_HDMI_ARC_PINControl(INPUT_PORT_DVI0, FALSE, FALSE);

                    if (msAPI_AUD_IsAudioMutedByUser()==TRUE)
                    {
                        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                    }

                #endif

                    MApp_Audio_Set_AmpMute(AUDIO_AMP_MUTE_OFF);

                    MApi_CEC_Enabled(DISABLE);  // Disable CEC HW

                    stGenSetting.stHDMISetting.g_bHdmiCecMode = DISABLE;
                    stGenSetting.stHDMISetting.g_enHDMIARC = ENABLE;
                    stGenSetting.stHDMISetting.g_bHdmiCecAutoTvOn = ENABLE;
                    stGenSetting.stHDMISetting.g_bHdmiCecDeviceAutoStandby = ENABLE;
                    stGenSetting.stHDMISetting.g_bHdmiCecDeviceControl = ENABLE;

                    MsOS_DelayTask(500);
                    msAPI_CEC_EmptyAllMsgFifo();

            #endif

                    MApp_ZUI_API_EnableWindow(HWND_MENU_HDMI_CEC_ARC, DISABLE);
                    MApp_ZUI_API_EnableWindow(HWND_MENU_HDMI_CEC_AUTO_STANDBY, DISABLE);
                    MApp_ZUI_API_EnableWindow(HWND_MENU_HDMI_CEC_AUTO_TV_ON, DISABLE);
                    MApp_ZUI_API_EnableWindow(HWND_MENU_HDMI_CEC_DEVICE_CONTROL, DISABLE);
                    MApp_ZUI_API_EnableWindow(HWND_MENU_HDMI_CEC_DEVICE_LIST, DISABLE);

                }
                else
                {
                #if 1 // Move to MApp_CEC_Set_Enable()
                    MApp_CEC_Set_Enable(ENABLE);

                #else
                    msAPI_CEC_EmptyAllMsgFifo();

                    MApi_CEC_Enabled(ENABLE);   // Enable CEC HW

                    DB_HDMI_SETTING.g_bHdmiCecMode = ENABLE;

                    msAPI_CEC_ForceImmediatelyPolling(FALSE);

                #endif

                #if (!ENABLE_WAIT_CEC_READY)

                  #if (!ENABLE_ARC_CHANGE_SPDIF)
                    MApp_ZUI_API_EnableWindow(HWND_MENU_HDMI_CEC_ARC, ENABLE);
                  #else
                    MApp_ZUI_API_EnableWindow(HWND_MENU_HDMI_CEC_ARC, DISABLE);
                  #endif

                    MApp_ZUI_API_EnableWindow(HWND_MENU_HDMI_CEC_AUTO_STANDBY, ENABLE);
                    MApp_ZUI_API_EnableWindow(HWND_MENU_HDMI_CEC_AUTO_TV_ON, ENABLE);
                    MApp_ZUI_API_EnableWindow(HWND_MENU_HDMI_CEC_DEVICE_CONTROL, ENABLE);
                    MApp_ZUI_API_EnableWindow(HWND_MENU_HDMI_CEC_DEVICE_LIST, ENABLE);
                #endif

                #if ENABLE_WAIT_CEC_READY

                #if ENABLE_ATSC_TTS
                    MApp_TTS_Cus_Add_Str_By_StrId(en_str_HDMI_Device_Searching);
                    MApp_TTSControlSetOn(TRUE);
                #endif
                    MApp_ZUI_API_ShowWindow(HWND_MENU_HDMI_CEC_PAGE_WAIT,SW_SHOW);
                    MApp_ZUI_API_EnableWindow(HWND_MENU_HDMI_CEC_HDMI, DISABLE);
                    MApp_ZUI_API_SetTimer(HWND_MENU_HDMI_CEC_PAGE_WAIT, 0, CEC_DEVICE_REFRESH_TIME);
                #endif

                }
            }
            else if(MApp_ZUI_API_GetFocus() == HWND_MENU_HDMI_CEC_AUTO_STANDBY)
            {
                CEC_UI_MSG( printf("\n [%d] HWND_MENU_HDMI_CEC_AUTO_STANDBY \n", __LINE__) );

                if (DB_HDMI_SETTING.g_bHdmiCecDeviceAutoStandby == TRUE)
                    DB_HDMI_SETTING.g_bHdmiCecDeviceAutoStandby = FALSE;
                else
                    DB_HDMI_SETTING.g_bHdmiCecDeviceAutoStandby = TRUE;
            }
            else if(MApp_ZUI_API_GetFocus() == HWND_MENU_HDMI_CEC_ARC)
            {
                CEC_UI_MSG( printf("\n [%d] HWND_MENU_HDMI_CEC_ARC \n", __LINE__) );

                if (stGenSetting.stHDMISetting.g_enHDMIARC == TRUE)
                {
                    stGenSetting.stHDMISetting.g_enHDMIARC = FALSE;

                    msAPI_CEC_RequestARCAction(CEC_ARC_REQUEST_TERMINATION);

                #if 0  //for mantis: 905461
                    if(msAPI_AUD_IsAudioMutedByUser()==TRUE)
                    {
                        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                    }
                #endif
                }
                else
                {
                    stGenSetting.stHDMISetting.g_enHDMIARC = TRUE;

                    msAPI_CEC_RequestARCAction(CEC_ARC_REQUEST_INITIATION);

                #if 0 //for mantis: 905461
                    if(msAPI_AUD_IsAudioMutedByUser()==FALSE)
                    {
                        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                    }
                #endif
                }
            }
            else if(MApp_ZUI_API_GetFocus() == HWND_MENU_HDMI_CEC_AUTO_TV_ON)
            {
                CEC_UI_MSG( printf("\n [%d] HWND_MENU_HDMI_CEC_AUTO_TV_ON \n", __LINE__) );

                if (stGenSetting.stHDMISetting.g_bHdmiCecAutoTvOn == TRUE)
                {
                    stGenSetting.stHDMISetting.g_bHdmiCecAutoTvOn = FALSE;
                }
                else
                {
                    DB_HDMI_SETTING.g_bHdmiCecAutoTvOn = TRUE;
                }
            }
            else if(MApp_ZUI_API_GetFocus() == HWND_MENU_HDMI_CEC_DEVICE_CONTROL)
            {
                CEC_UI_MSG( printf("\n [%d] HWND_MENU_HDMI_CEC_DEVICE_CONTROL \n", __LINE__));

                if (DB_HDMI_SETTING.g_bHdmiCecDeviceControl == TRUE)
                {
                    DB_HDMI_SETTING.g_bHdmiCecDeviceControl = FALSE;
                }
                else
                {
                    DB_HDMI_SETTING.g_bHdmiCecDeviceControl = TRUE;
                }
            }

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_HDMI_CEC_PAGE);
            return TRUE;
        }

        case EN_EXE_CHANGE_DEVICES:
        case EN_EXE_SELECT_UP_DEVICES:
        case EN_EXE_SELECT_DOWN_DEVICES:
        {
            HWND hwnd = MApp_ZUI_API_GetFocus();
            U8 i;

            if (g_stMenuCecDeviceList.u8CECDeviceNum == 0)
                return TRUE;

            for( i=0; i<CEC_DEVICES_COUNT; i++)
            {
                if(hwnd == hdmi_cec_UI_list[i]) // get index in CEC UI list
                    break;
            }

            if(i == CEC_DEVICES_COUNT)//fixed out of bounds read
                return TRUE;

            if(act == EN_EXE_CHANGE_DEVICES)
            {
                msAPI_CEC_DeviceChange(g_stMenuCecDeviceList.aenDeviceLA[i]);

                if (E_OSD_MAIN_MENU == MApp_ZUI_GetActiveOSD())
                {
                    MApp_ZUI_API_ShowWindow(HWND_MENU_HDMI_CEC_DEVICE_LIST_PAGE, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_MENU_TRANSPARENT_BG, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_MENU_HDMI_CEC_PAGE, SW_SHOW);
                #if ENABLE_WAIT_CEC_READY
                    MApp_ZUI_API_ShowWindow(HWND_MENU_HDMI_CEC_PAGE_WAIT,SW_HIDE);
                #endif
                    MApp_ZUI_API_SetFocus(HWND_MENU_HDMI_CEC_DEVICE_LIST);
                }

                //CEC 11.1.12-4
                msAPI_CEC_PostMsg_MenuRequest(DIRECTMSG,g_stMenuCecDeviceList.aenDeviceLA[i],E_MSG_MENU_REQ_ACTIVATED);
            }
            else if(act == EN_EXE_SELECT_UP_DEVICES)
            {
                if(i == 0)
                    MApp_ZUI_API_SetFocus(hdmi_cec_UI_list[(g_stMenuCecDeviceList.u8CECDeviceNum-1)]); // now is 1st, Set focus to final devices
                else
                    MApp_ZUI_API_SetFocus(hdmi_cec_UI_list[(i -1)]); // Set focus to up devices

                MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_HDMI_CEC_DEVICE_LIST_PAGE);
            }
            else if(act == EN_EXE_SELECT_DOWN_DEVICES)
            {
                if(i  == (g_stMenuCecDeviceList.u8CECDeviceNum-1))
                    MApp_ZUI_API_SetFocus(hdmi_cec_UI_list[0]); // now is final, Set focus to 1st devices
                else
                    MApp_ZUI_API_SetFocus(hdmi_cec_UI_list[(i + 1)]); // Set focus to down devices

                MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_HDMI_CEC_DEVICE_LIST_PAGE);
            }

            return TRUE;
        }

    #endif // #if ENABLE_CEC


    #if (ENABLE_AUDIO_SURROUND_DBX==ENABLE)
        case EN_EXE_DBX_TOTAL_SONICS:
            MApp_ZUI_ACT_AdjustDBX_TotSonMode(TRUE);
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_SOUND_DBX_TOTAL_SONICS);
            break;

        case EN_EXE_DBX_TOTAL_VOLUME:
            MApp_ZUI_ACT_AdjustDBX_TotVolMode(TRUE);
            MApp_ZUI_CTL_DynamicListSetItemFocus(HWND_MENU_SOUND_PAGE_LIST,HWND_MENU_SOUND_DBX_TOTAL_VOLUME);
            break;

        case EN_EXE_DBX_TOTAL_SURROUND:
            MApp_ZUI_ACT_AdjustDBX_TotSurMode(TRUE);
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_SOUND_DBX_TOTAL_SURROUND);
            break;
    #endif

        default:
            ZUI_DBG_FAIL(printf("[ZUI]MENUACT:%u/%u\n", act,(U16)EN_EXE_MAX));
            //ABORT();
    }

    return FALSE;
}

U16 _MApp_ZUI_ACT_GetAudioModeStringID(void)
{
    U16 u16TempID = Empty;
    //from case AUDIOMODESELECTTEXT:
    {
        switch(stGenSetting.g_SoundSetting.SoundMode)
        {
            case EN_SoundMode_Standard:
                u16TempID=en_str_Standard;
                break;
            case EN_SoundMode_Music:
                u16TempID=en_str_Music;
                break;
            case EN_SoundMode_Movie:
                u16TempID=en_str_Movie;
                break;
            case EN_SoundMode_Sports:
                u16TempID=en_str_Sports;
                break;
            case EN_SoundMode_User:
                u16TempID=en_str_User;
                break;
            default:
            break;

        }
    }

  #if ENABLE_AUTOTEST
    if(g_bAutobuildDebug)
    {
        if(SoundMenu != u16TempID)
        {
            printf("51_SoundMenu\n");
        }
        SoundMenu = u16TempID;
    }
  #endif

    return u16TempID;
}

U16 _MApp_ZUI_ACT_GetAspectRatioStringID(void)
{
    U16 u16TempID = Empty;
    //from case B5_ASPECTRATIO_SELECTTEXT:

    switch(ST_VIDEO.eAspectRatio) //MApp_UiMenuFunc_GetenB5_AspectRatioValue())
    {
        case EN_AspectRatio_Original:
            u16TempID=en_str_Auto;
            break;
        case EN_AspectRatio_4X3:
            u16TempID=en_str_4colon3;
            break;
        case EN_AspectRatio_16X9:
            u16TempID=en_str_16colon9;
            break;
        case EN_AspectRatio_14X9:
            u16TempID=en_str_14colon9;
            break;
        case EN_AspectRatio_Zoom1:
            u16TempID=en_str_Zoom1;
            break;
        case EN_AspectRatio_Zoom2:
            u16TempID=en_str_Zoom2;
            break;
        case EN_AspectRatio_JustScan:
            u16TempID=en_str_Just_Scan;
            break;
       case EN_AspectRatio_Panorama:
            u16TempID=en_str_Panorama;
            break;
        case EN_AspectRatio_Point_to_Point:
            u16TempID=en_str_PointToPoint;
            break;
        default: //wrong aspect radio
            u16TempID=en_str_dashdash;
            break;
    }
    #if ENABLE_AUTOTEST
    if(g_bAutobuildDebug)
    {
        switch(tempcheck2)
        {
            case HWND_MENU_PICTURE_ASPECT_RATIO_OPTION:
                if(AspectR != u16TempID)
                {
                    printf("43_AspectRatio\n");
                }
                AspectR = u16TempID;
                break;

            default:
                break;
        }
    }
    #endif
    return u16TempID;
}

U16 _MApp_ZUI_ACT_GetPictureModeStringID(void)
{
    U16 u16TempID = Empty;
    //from case B1_PICTURE_SELECTTEXT:
    switch(ST_VIDEO.ePicture)
    {
        default:
        case PICTURE_DYNAMIC:
            u16TempID=en_str_Picture_Daylight;
            break;
        case PICTURE_NORMAL:
            u16TempID=en_str_Picture_Normal;
            break;
        case PICTURE_MILD:
            u16TempID=en_str_Picture_NightTime;
            break;
        case PICTURE_USER:
    #if PICTURE_USER_2
             u16TempID=en_str_Picture_User;
    #else
            u16TempID=en_str_ColorTemp_User;
    #endif
            break;
    #if PICTURE_USER_2
        case PICTURE_USER2:
            u16TempID=en_str_Picture_User2;
            break;
    #endif
    }
    #if ENABLE_AUTOTEST
    if(g_bAutobuildDebug)
    {
        switch(tempcheck2)
        {
            case HWND_MENU_PICTURE_PICMODE_OPTION:
                if(PicMode != u16TempID)
                {
                    printf("41_PictureMode\n");
                }
                PicMode = u16TempID;
                break;

            default:
                break;
        }
    }
    #endif
    return u16TempID;
}

static U16 _MApp_ZUI_ACT_GetColorTempColorValue(HWND hwnd)
{
    switch(hwnd)
    {
        case HWND_MENU_PIC_ADJ_TEMP_RED_OPTION:
        case HWND_MENU_PICCOLOR_COLOR_RED_OPTION:
            //from case EN_DNUM_Getu16B2_ColorTemp_User_RedValue_Percent:
            if (ST_PICTURE.eColorTemp == MS_COLOR_TEMP_USER)
                return ST_COLOR_TEMP.cRedScaleValue;
            else return GetScale100Value(ST_COLOR_TEMP.cRedColor,MIN_USER_RGB, MAX_USER_RGB);

        case HWND_MENU_PIC_ADJ_TEMP_GREEN_OPTION:
        case HWND_MENU_PICCOLOR_COLOR_GREEN_OPTION:
            //from case EN_DNUM_Getu16B2_ColorTemp_User_GreenValue_Percent:
            if (ST_PICTURE.eColorTemp == MS_COLOR_TEMP_USER)
                return ST_COLOR_TEMP.cGreenScaleValue;
            else return GetScale100Value(ST_COLOR_TEMP.cGreenColor,MIN_USER_RGB, MAX_USER_RGB);

        case HWND_MENU_PIC_ADJ_TEMP_BLUE_OPTION:
        case HWND_MENU_PICCOLOR_COLOR_BLUE_OPTION:
            //from case EN_DNUM_Getu16B2_ColorTemp_User_BlueValue_Percent:
            if (ST_PICTURE.eColorTemp == MS_COLOR_TEMP_USER)
                return ST_COLOR_TEMP.cBlueScaleValue;
            else return GetScale100Value(ST_COLOR_TEMP.cBlueColor,MIN_USER_RGB, MAX_USER_RGB);

    }
    return 0;
}

#if ENABLE_GAMMA_ADJUST
static U16 _MApp_ZUI_ACT_GetGammaRGBValue(HWND hwnd)
{
    switch(hwnd)
    {
        case HWND_MENU_COMMON_ADJ_ITEM2_OPTION:
                return stGenSetting.g_GammaSetting.u8RedColor;

        case HWND_MENU_COMMON_ADJ_ITEM3_OPTION:
                return stGenSetting.g_GammaSetting.u8GreenColor;

        case HWND_MENU_COMMON_ADJ_ITEM4_OPTION:
                return stGenSetting.g_GammaSetting.u8BlueColor;
    }
    return 0;
}
#endif

static U16 MApp_ZUI_ACT_GetPcModeAdjustValue(HWND hwnd)
{
    switch(hwnd)
    {
        //case HWND_MENU_PCMODE_SIZE_BAR:
        case HWND_MENU_PCMODE_SIZE_OPTION:
        //from case EN_DNUM_Getu16B7_PCMenu_SizeValue:
        {
            if(IsSrcTypeVga(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))||IsSrcTypeYPbPr(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
            {
                stLMGenSetting.stMB.u16B7_PCMenu_Size = msAPI_Mode_GetPcClockValue( MAIN_WINDOW, g_PcadcModeSetting[MAIN_WINDOW].u16HorizontalTotal);
            }
            #if (ENABLE_PIP)
            else if((MApp_Get_PIPMode() != EN_PIP_MODE_OFF)&& (IsSrcTypeVga(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))||IsSrcTypeYPbPr(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))))
            {
                stLMGenSetting.stMB.u16B7_PCMenu_Size = msAPI_Mode_GetPcClockValue( SUB_WINDOW, g_PcadcModeSetting[SUB_WINDOW].u16HorizontalTotal);
            }
            #endif
            return stLMGenSetting.stMB.u16B7_PCMenu_Size;
        } break;

        //case HWND_MENU_PCMODE_PHASE_BAR:
        case HWND_MENU_PCMODE_PHASE_OPTION:
        //from case EN_DNUM_Getu16B7_PCMenu_PhaseValue:
        {
            if(IsSrcTypeVga(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))||IsSrcTypeYPbPr(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
            {
                stLMGenSetting.stMB.u16B7_PCMenu_Phase = msAPI_Mode_GetPcPhaseValue(g_PcadcModeSetting[MAIN_WINDOW].u16Phase);
            }
            #if (ENABLE_PIP)
            else if((MApp_Get_PIPMode() != EN_PIP_MODE_OFF)&& (IsSrcTypeVga(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))||IsSrcTypeYPbPr(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))))
            {
                stLMGenSetting.stMB.u16B7_PCMenu_Phase = msAPI_Mode_GetPcPhaseValue(g_PcadcModeSetting[SUB_WINDOW].u16Phase);
            }
            #endif
            return stLMGenSetting.stMB.u16B7_PCMenu_Phase;
        } break;

        //case HWND_MENU_PCMODE_HPOS_BAR:
        case HWND_MENU_PCMODE_HPOS_OPTION:
        //from case EN_DNUM_Getu16B7_PCMenu_PositionH:
        {
            U32 tmp;
            #if (ENABLE_PIP)
            if((MApp_Get_PIPMode() != EN_PIP_MODE_OFF)&& (IsSrcTypeVga(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))||IsSrcTypeYPbPr(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))))
            {
                tmp = g_PcadcModeSetting[SUB_WINDOW].u16HorizontalStart;
                tmp = (tmp - MIN_PC_H_START(SUB_WINDOW) ) * 100 / ( MAX_PC_H_START(SUB_WINDOW) - MIN_PC_H_START(SUB_WINDOW) );//46lu) * 100lu / 292lu;
            }
            else
            #endif
            {
                tmp = g_PcadcModeSetting[MAIN_WINDOW].u16HorizontalStart;
                tmp = (tmp - MIN_PC_H_START(MAIN_WINDOW) ) * 100 / ( MAX_PC_H_START(MAIN_WINDOW) - MIN_PC_H_START(MAIN_WINDOW) );//46lu) * 100lu / 292lu;
            }

            return tmp;
        } break;

        //case HWND_MENU_PCMODE_VPOS_BAR:
        case HWND_MENU_PCMODE_VPOS_OPTION:
        //from case EN_DNUM_Getu16B7_PCMenu_PositionV:
        {
            U32 tmp;
            #if (ENABLE_PIP)
            if((MApp_Get_PIPMode() != EN_PIP_MODE_OFF)&& (IsSrcTypeVga(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))||IsSrcTypeYPbPr(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))))
            {
                tmp = g_PcadcModeSetting[SUB_WINDOW].u16VerticalStart;
                tmp = (tmp - MIN_PC_V_START ) * 100 / ( MAX_PC_V_START(SUB_WINDOW) - MIN_PC_V_START );//46lu) * 100lu / 292lu;
            }
            else
            #endif
            {
                tmp = g_PcadcModeSetting[MAIN_WINDOW].u16VerticalStart;
                tmp = (tmp - MIN_PC_V_START ) * 100 / ( MAX_PC_V_START(MAIN_WINDOW) - MIN_PC_V_START );//46lu) * 100lu / 292lu;
            }


            return tmp;
        } break;
    }
    return 0;
}

static U16 _MApp_ZUI_ACT_GetSoundAdjustValue(HWND hwnd)
{
    #if ENABLE_AUTOTEST
    if(g_bAutobuildDebug)
    {
        switch(tempcheck2)
        {
            case HWND_MENU_SNDMODE_TREBLE_OPTION:
                if(SoundMenuT != stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Treble)
                {
                    printf("51_SoundMenuTreble\n");
                }
                SoundMenuT = stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Treble;
                break;

            case HWND_MENU_SNDMODE_BASS_OPTION:
                if(SoundMenuB != stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Bass)
                {
                    printf("51_SoundMenuBass\n");
                }
                SoundMenuB = stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Bass;
                break;
            default:
                break;
        }
    }
    #endif

    switch(hwnd)
    {
        //case HWND_MENU_SNDMODE_TREBLE_BAR:
        case HWND_MENU_SNDMODE_TREBLE_OPTION:
            //from case EN_DNUM_Getu16C4_Sound_User_TrebleValue:
            return (
                stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Treble);
        //case HWND_MENU_SNDMODE_BASS_BAR:
        case HWND_MENU_SNDMODE_BASS_OPTION:
            return (
                stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Bass);
        //case HWND_MENU_SNDEQ_120_HZ_BAR:
        case HWND_MENU_SNDEQ_120_HZ_OPTION:
            return (
                stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8120HZ);
        //case HWND_MENU_SNDEQ_200_HZ_BAR:
        case HWND_MENU_SNDEQ_200_HZ_OPTION:
            return (
                stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8200HZ);
        //case HWND_MENU_SNDEQ_500_HZ_BAR:
        case HWND_MENU_SNDEQ_500_HZ_OPTION:
            return (
                stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8500HZ);
        //case HWND_MENU_SNDEQ_1_2_KHZ_BAR:
        case HWND_MENU_SNDEQ_1_2_KHZ_OPTION:
            return (
                stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8_1_dot_2_KHZ);
        //case HWND_MENU_SNDEQ_3_KHZ_BAR:
        case HWND_MENU_SNDEQ_3_KHZ_OPTION:
            return (
                stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8_3KHZ);
        //case HWND_MENU_SNDEQ_7_5_KHZ_BAR:
        case HWND_MENU_SNDEQ_7_5_KHZ_OPTION:
            return (
                stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8_7_dot_5_KHZ);
        //case HWND_MENU_SNDEQ_12_KHZ_BAR:
        case HWND_MENU_SNDEQ_12_KHZ_OPTION:
            return (
                stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u812KHZ);

        case HWND_MENU_SOUND_BALANCE_OPTION:
            //from case EN_DNUM_Getu16C3_BalanceValue:
            return (
                stGenSetting.g_SoundSetting.Balance);

        /*case HWND_MENU_SOUND_AUDIO_DELAY_OPTION:
            return (
                stGenSetting.g_SoundSetting.Audiodelay);
				*/
    }
    return 0;
}

U16 _MApp_ZUI_ACT_GetBalanceValue(void)
{
       return (stGenSetting.g_SoundSetting.Balance);
}


static  OSDCP_EN_STRING_INDEX _ZUI_TBLSEG _WeekString[7]=
{
    en_str_Sun,
    en_str_Mon,
    en_str_Tue,
    en_str_Wed,
    en_str_Thurs,
    en_str_Fri,
    en_str_Sat,
};

void _MApp_ZUI_ACT_LoadWeekString(U8 month, LPTSTR str)
{
    MApp_ZUI_API_LoadString(_WeekString[month], str);
}


static  OSDCP_EN_STRING_INDEX _ZUI_TBLSEG _MonthString[12] =
{
    en_str_Jan,
    en_str_Feb,
    en_str_Mar,
    en_str_Apr,
    en_str_May,
    en_str_Jun,
    en_str_Jul,
    en_str_Aug,
    en_str_Sep,
    en_str_Oct,
    en_str_Nov,
    en_str_Dec
};

void _MApp_ZUI_ACT_LoadMonthString(U8 month, LPTSTR str)
{
    MApp_ZUI_API_LoadString(_MonthString[month], str);
}

LPTSTR _MApp_ZUI_ACT_GetLocalClockDateString(LPTSTR str)
{
    ST_TIME _stTime;

    //format:  DAY/MON     HOUR:MIN
    //format:   --   --      --   --

    //only do it just one time...
    MApp_ConvertSeconds2StTime(MApp_GetLocalSystemTime(), &_stTime);

    if ( (g_u8TimeInfo_Flag & UI_TIME_DAY_SET)
      #if ENABLE_DVB
       || MApp_SI_IsAutoClockValid()
      #endif
       )
    {
        stLMGenSetting.stMD.u16Option_Info_Day = _stTime.u8Day;
        __MApp_UlongToString((U16)stLMGenSetting.stMD.u16Option_Info_Day, str, 2);
        str += 2;
    }
    else
    {
        MApp_ZUI_API_LoadString(en_str_dashdash, str);
        str += MApp_ZUI_API_Strlen(str);
    }

    //from case D1_OPTION_DAYSLASHTEXT:
    //from case D1_OPTION_MONTHVALUETEXT:
    if ( ((g_u8TimeInfo_Flag & UI_TIME_MONTH_SET) && (g_u8TimeInfo_Flag & UI_TIME_MINUTE_SET))
      #if ENABLE_DVB
       || MApp_SI_IsAutoClockValid()
      #endif
        )
    {
        MApp_ZUI_API_LoadString(en_str_Slash, str);
        str += MApp_ZUI_API_Strlen(str);

        stLMGenSetting.stMD.u16Option_Info_Month = _stTime.u8Month;
        _MApp_ZUI_ACT_LoadMonthString(stLMGenSetting.stMD.u16Option_Info_Month-1, str);
        str += MApp_ZUI_API_Strlen(str);

        *str++ = CHAR_SPACE;
        stLMGenSetting.stMD.u16Option_Info_Year=_stTime.u16Year;
        __MApp_UlongToString((U16)stLMGenSetting.stMD.u16Option_Info_Year, str, 4);
        str += MApp_ZUI_API_Strlen(str);
    }
    else
    {
        *str++ = CHAR_SPACE;
        *str++ = CHAR_SPACE;

        MApp_ZUI_API_LoadString(en_str_dashdash, str);
        str += MApp_ZUI_API_Strlen(str);
    }

    return str;

}

LPTSTR _MApp_ZUI_ACT_GetLocalClockTimeString(LPTSTR str)
{
    ST_TIME _stTime;

    //format:  DAY/MON     HOUR:MIN
    //format:   --   --      --   --

    //only do it just one time...
    MApp_ConvertSeconds2StTime(MApp_GetLocalSystemTime(),&_stTime);

    //from case D1_OPTION_HOURVALUETEXT:
    //U16 u16Hour;
    if ( (g_u8TimeInfo_Flag & UI_TIME_HOUR_SET)
      #if ENABLE_DVB
       || MApp_SI_IsAutoClockValid()
      #endif
       )
    {
        MApp_ConvertSeconds2StTime(MApp_GetLocalSystemTime(), &_stTime);
        stLMGenSetting.stMD.u16Option_Info_Hour = _stTime.u8Hour;

        if (stLMGenSetting.stMD.u16Option_Info_Hour >= 12)
        {
            //u16Hour = stLMGenSetting.stMD.u16Option_Info_Hour - 12;
            stLMGenSetting.stMD.bTimer_Info_PM |= UI_TIME_CLOCK_PM;
        }
        else
        {
           // u16Hour = stLMGenSetting.stMD.u16Option_Info_Hour;
            stLMGenSetting.stMD.bTimer_Info_PM &= ~UI_TIME_CLOCK_PM;
        }

        __MApp_UlongToString((U16)stLMGenSetting.stMD.u16Option_Info_Hour, str, 2);
        str += 2;
    }
    else
    {
        MApp_ZUI_API_LoadString(en_str_dashdash, str);
        str += MApp_ZUI_API_Strlen(str);
    }

    //from case D_OPTION_TIME_INFO_COLON_TEXT:
    //from case D1_OPTION_MINVALUETEXT:
    if ( (g_u8TimeInfo_Flag & UI_TIME_MINUTE_SET)
      #if ENABLE_DVB
       || MApp_SI_IsAutoClockValid()
      #endif
       )
    {
        MApp_ZUI_API_LoadString(en_str_colon, str);
        str += MApp_ZUI_API_Strlen(str);

        stLMGenSetting.stMD.u16Option_Info_Min = _stTime.u8Min;
        __MApp_UlongToString((U16)stLMGenSetting.stMD.u16Option_Info_Min, str, 2);
        str += 2;
    }
    else
    {
        *str++ = CHAR_SPACE;
        *str++ = CHAR_SPACE;

        MApp_ZUI_API_LoadString(en_str_dashdash, str);
        str += MApp_ZUI_API_Strlen(str);
    }

    return str;
}

LPTSTR _MApp_ZUI_ACT_GetLocalClockTimeSecString(LPTSTR str)
{
    ST_TIME _stTime;

    MApp_ConvertSeconds2StTime(MApp_GetLocalSystemTime(),&_stTime);

    MApp_ZUI_API_LoadString(en_str_colon, str);
    str += MApp_ZUI_API_Strlen(str);

    __MApp_UlongToString((U16)_stTime.u8Sec, str, 2);
    str += 2;

    return str;
}

static LPTSTR _MApp_ZUI_ACT_GetLocalClockString(void)
{
    LPTSTR str = CHAR_BUFFER;

    str = _MApp_ZUI_ACT_GetLocalClockDateString(str);

    *str++ = CHAR_SPACE;
    *str++ = CHAR_SPACE;
    *str++ = CHAR_SPACE;
    *str++ = CHAR_SPACE;

    str = _MApp_ZUI_ACT_GetLocalClockTimeString(str);
    *str = 0;

#if ENABLE_AUTOTEST
    if(g_bAutobuildDebug)
    {
        if(OSDClock == 1)
        {
            printf("61_Clock\n");
            OSDClock = 0;
        }
        else
            OSDClock = 1;
    }
#endif

    return CHAR_BUFFER;
}

extern void _MApp_ZUI_ACT_GetSleepTimerString(LPTSTR str);

U16 _MApp_ZUI_ACT_GetLanguageStringID(EN_LANGUAGE lang, BOOLEAN bDefaultEnglish)
{
    U16 u16TempID;

    //from case MENULANGUAGESELECTTEXT:
    //from function MApp_UiMenu_GetLanguageStringID()
    switch(lang)
    {
        case LANGUAGE_CZECH:
            u16TempID=en_str_Czech;
            break;
        case LANGUAGE_DANISH:
            u16TempID=en_str_Dansk;
            break;
        case LANGUAGE_GERMAN:
            u16TempID=en_str_Deutsch;
            break;
        case LANGUAGE_ENGLISH:
            u16TempID=en_str_English;
            break;
        case LANGUAGE_SPANISH:
            u16TempID=en_str_Spanish;
            break;
        case LANGUAGE_GREEK:
            u16TempID=en_str_Greek;
            break;
        case LANGUAGE_FRENCH:
            u16TempID=en_str_France;
            break;
        case LANGUAGE_CROATIAN:
            u16TempID=en_str_Hrvatski;
            break;
        case LANGUAGE_ITALIAN:
            u16TempID=en_str_Italiano;
            break;
        case LANGUAGE_HUNGARIAN:
            u16TempID=en_str_Magyar;
            break;
        case LANGUAGE_DUTCH:
            u16TempID=en_str_Nederlands;
            break;
        case LANGUAGE_NORWEGIAN:
            u16TempID=en_str_Norsk;
            break;
        case LANGUAGE_POLISH:
            u16TempID=en_str_Polski;
            break;
        case LANGUAGE_PORTUGUESE:
            u16TempID=en_str_Portuguese;
            break;
        case LANGUAGE_RUSSIAN:
            u16TempID=en_str_Russian1;
            break;
        case LANGUAGE_ROMANIAN:
            u16TempID=en_str_Romanian;
            break;
        case LANGUAGE_SLOVENIAN:
            u16TempID=en_str_Slovene;
            break;
        case LANGUAGE_SERBIAN:
            u16TempID=en_str_Srpski;
            break;
        case LANGUAGE_FINNISH:
            u16TempID=en_str_Suomi;
            break;
        case LANGUAGE_SWEDISH:
            u16TempID=en_str_Svenska;
            break;
        case LANGUAGE_BULGARIAN:
            u16TempID=en_str_Bulgarian;
            break;
        case LANGUAGE_SLOVAK:
            u16TempID=en_str_Slovak;
            break;
        case LANGUAGE_GAELIC:
            u16TempID=en_str_Gaelic;
            break;
        case LANGUAGE_AKAN:
            u16TempID=en_str_Akan;
            break;
        case LANGUAGE_EWE:
            u16TempID=en_str_Ewe;
            break;
        case LANGUAGE_TWI:
            u16TempID=en_str_Twi;
            break;
        case LANGUAGE_NZEMA:
            u16TempID=en_str_Nzema;
            break;
        case LANGUAGE_HAUSA:
            u16TempID=en_str_Hausa;
            break;
        case LANGUAGE_KASEM:
            u16TempID=en_str_Kasem;
            break;
        case LANGUAGE_WELSH:
            u16TempID=en_str_Welsh;
            break;

    #if (  ENABLE_ATV_CHINA_APP             \
        || ENABLE_DTMB_CHINA_APP            \
        || ENABLE_DVBC_PLUS_DTMB_CHINA_APP  \
        || CHINESE_SIMP_FONT_ENABLE)
        case LANGUAGE_CHINESE:
          #if (MS_SW_CUS_SEL == SW_CONFIG_TRUNK_NASA_64M_DTMB_SZ)
            u16TempID = en_str_SimpleChinese;
          #else
            u16TempID = en_str_Chinese;
          #endif
            break;
    #if (CHINESE_BIG5_FONT_ENABLE)
        case LANGUAGE_CHINESE_TRAD:
            if(MApp_ZUI_API_IsWindowVisible(HWND_MENU_OPTION_OSDLANG_GRID))
                u16TempID = Empty;
            else
                u16TempID = en_str_Chinese;
            break;
    #endif
    #endif

        case LANGUAGE_IRISH:
            u16TempID=en_str_Irish;
            break;
        case LANGUAGE_KOREAN:
            u16TempID=en_str_Korean;
            break;
        case LANGUAGE_JAPAN:
            u16TempID=en_str_Japanese;
            break;
        case LANGUAGE_HINDI:
            u16TempID=en_str_Hindi;
            break;

#if 0//(ENABLE_TTF_FONT)
        case LANGUAGE_MYANMAR:
            u16TempID=en_str_Myanmar;
            break;
        case LANGUAGE_UYGHUR:
            u16TempID=en_str_Uyghur;
            break;
        case LANGUAGE_KHMER:
            u16TempID=en_str_Khmer;
            break;
        case LANGUAGE_LAO:
            u16TempID=en_str_Lao;
            break;
#endif
        case LANGUAGE_MAORI:
            u16TempID=en_str_Maori;
            break;

        case LANGUAGE_INDONESIA:
            u16TempID=en_str_Indonesia;
            break;

        case LANGUAGE_MALAYSIA:
            u16TempID=en_str_Melayu;
            break;

        case LANGUAGE_VIETNAM:
            u16TempID=en_str_Vietnam;
            break;

        case LANGUAGE_MANDARIN:
            u16TempID=en_str_Mandarin;
            break;
        case LANGUAGE_CANTONESE:
            u16TempID=en_str_Cantonese;
            break;
        case LANGUAGE_GALLEGAN:
            u16TempID=en_str_Gallegan;
            break;
        case LANGUAGE_BASQUE:
            u16TempID=en_str_Basque;
            break;
        case LANGUAGE_LUXEMBOURGISH:
            u16TempID=en_str_Luxembourgish;
            break;
        case LANGUAGE_ICELANDIC:
            u16TempID=en_str_Icelandic;
            break;
        case LANGUAGE_LATVIAN:
            u16TempID=en_str_Latvian;
            break;
        case LANGUAGE_ESTONIAN:
            u16TempID=en_str_Estonian;
            break;
        case LANGUAGE_LITHUANIAN:
            u16TempID=en_str_Lithuanian;
            break;
        case LANGUAGE_UKRANIAN:
            u16TempID=en_str_Ukranian;
            break;
        case LANGUAGE_BELARUSIAN:
            u16TempID=en_str_Belarusian;
            break;
        case LANGUAGE_SPANISH_CAT:
            u16TempID=en_str_Catalan;
            break;
        case LANGUAGE_SAMI:
            u16TempID=en_str_Sami;
            break;
        case LANGUAGE_HEBREW:
            u16TempID=en_str_Hebrew;
            break;
        case LANGUAGE_TURKISH:
            u16TempID=en_str_Turkish;
            break;
        case LANGUAGE_THAI:
            u16TempID=en_str_Thailand;
            break;
        case LANGUAGE_SGA:
            u16TempID=en_str_Sga;
            break;
        case LANGUAGE_TAMIL:
            u16TempID=en_str_Tamil;
            break;

    #if 0
        default:
            if (!bDefaultEnglish)
                return Empty;
    #else // Modified by coverity_331
        default:
            if (!bDefaultEnglish)
                return Empty;

            u16TempID = en_str_English;
            break;
    #endif
    }

    return u16TempID;
}

LPTSTR _MApp_ZUI_ACT_CombineTextAndOption(HWND hwnd)
{
    LPTSTR u16str = CHAR_BUFFER;
    U16 u16len = 0;
    U16 u16TextID = 0;
    U32 u16OptionID = 0;
    U16 u16con_buffer[32];
    BOOLEAN Load_Flag = FALSE;

    switch (hwnd)
    {
		case HWND_MENU_PIC_ADJ_TEMP_RED_OPTION:
        case HWND_MENU_PICCOLOR_COLOR_RED_OPTION:
            u16TextID = en_strCCRedText;
            u16OptionID = _MApp_ZUI_ACT_GetColorTempColorValue(hwnd);
            #if ENABLE_AUTOTEST
            if(g_bAutobuildDebug)
            {
                if(ColorR != u16OptionID)
                {
                    printf("42_ColorR\n");
                }
                ColorR = u16OptionID;
            }
            #endif
            break;
        case HWND_MENU_PIC_ADJ_TEMP_GREEN_OPTION:
        case HWND_MENU_PICCOLOR_COLOR_GREEN_OPTION:
            u16TextID = en_strCCGreenText;
            u16OptionID = _MApp_ZUI_ACT_GetColorTempColorValue(hwnd);
            #if ENABLE_AUTOTEST
            if(g_bAutobuildDebug)
            {
                if(ColorG != u16OptionID)
                {
                    printf("42_ColorG\n");
                }
                ColorG = u16OptionID;
            }
            #endif
            break;
        case HWND_MENU_PIC_ADJ_TEMP_BLUE_OPTION:
        case HWND_MENU_PICCOLOR_COLOR_BLUE_OPTION:
            u16TextID = en_strCCBlueText;
            u16OptionID = _MApp_ZUI_ACT_GetColorTempColorValue(hwnd);
            #if ENABLE_AUTOTEST
            if(g_bAutobuildDebug)
            {
                if(ColorB != u16OptionID)
                {
                    printf("42_ColorB\n");
                }
                ColorB = u16OptionID;
            }
            #endif
            break;
        case HWND_MENU_PIC_ADJ_CONTRAST_OPTION:
        case HWND_MENU_PICMODE_CONTRAST_OPTION:
            u16TextID = en_str_Picture_User_Contrast;
            u16OptionID = ST_PICTURE.u8Contrast;
            #if ENABLE_AUTOTEST
            if(g_bAutobuildDebug)
            {
                if(PicContrast != u16OptionID)
                {
                    printf("41_PicContrast\n");
                }
                PicContrast = u16OptionID;
            }
            #endif
            break;
        case HWND_MENU_PIC_ADJ_BRIGHTNESS_OPTION:
        case HWND_MENU_PICMODE_BRIGHTNESS_OPTION:
            u16TextID = en_str_Picture_User_Brightness;
            u16OptionID = ST_PICTURE.u8Brightness;
            #if ENABLE_AUTOTEST
            if(g_bAutobuildDebug)
            {
                if(PicBright != u16OptionID)
                {
                    printf("41_PicBright\n");
                }
                PicBright = u16OptionID;
            }
            #endif
            break;
        case HWND_MENU_PIC_ADJ_COLOR_OPTION:
        case HWND_MENU_PICMODE_COLOR_OPTION:
            u16TextID = en_str_Picture_User_Color;
            u16OptionID = ST_PICTURE.u8Saturation;
            #if ENABLE_AUTOTEST
            if(g_bAutobuildDebug)
            {
                if(PicColor != u16OptionID)
                {
                    printf("41_PicColor\n");
                }
                PicColor = u16OptionID;
            }
            #endif
            break;
        case HWND_MENU_PIC_ADJ_SHARPNESS_OPTION:
        case HWND_MENU_PICMODE_SHARPNESS_OPTION:
            u16TextID = en_str_Picture_User_Sharpness;
            u16OptionID = ST_PICTURE.u8Sharpness;
            #if ENABLE_AUTOTEST
            if(g_bAutobuildDebug)
            {
                if(PicSharpness != u16OptionID)
                {
                    printf("41_PicSharpness\n");
                }
                PicSharpness = u16OptionID;
            }
            #endif
            break;
        case HWND_MENU_PIC_ADJ_TINT_OPTION:
        case HWND_MENU_PICMODE_TINT_OPTION:
            u16TextID = en_str_Picture_User_Tint;
            u16OptionID = ST_PICTURE.u8Hue;
            #if ENABLE_AUTOTEST
            if(g_bAutobuildDebug)
            {
                if(PicTint != u16OptionID)
                {
                    printf("41_PicTint\n");
                }
                PicTint = u16OptionID;
            }
            #endif
            break;
    #if ENABLE_ATSC_MENU_UI
    #if ENABLE_TTSTEST_FROM_USB
      case HWND_TTS_TEST_SPEED_ADJ_ITEM1_OPTION:
          u16TextID = en_str_Speed;

          switch(stGenSetting.g_SysSetting.u8TTSSpeed)
          {

              case EN_VOICE_GUIDE_SPEED_SLOW:
                   u16OptionID = en_str_Low;
                   break;
              case EN_VOICE_GUIDE_SPEED_NORMAL:
                   u16OptionID = en_str_Middle;
                   break;
              case EN_VOICE_GUIDE_SPEED_FAST:
                   u16OptionID = en_str_High;
                   break;
          }

          MApp_ZUI_API_LoadString(u16OptionID, u16con_buffer);
          Load_Flag = TRUE;
          break;

      case HWND_TTS_TEST_PITCH_ADJ_ITEM2_OPTION:
          u16TextID = en_str_Pitch;
          switch(stGenSetting.g_SysSetting.u8TTSPitch)
          {
              case EN_VOICE_GUIDE_PITCH_LOW:
                   u16OptionID = en_str_Low;
                   break;
              case EN_VOICE_GUIDE_PITCH_MEDIUM:
                   u16OptionID = en_str_Middle;
                   break;
              case EN_VOICE_GUIDE_PITCH_HIGH:
                   u16OptionID = en_str_High;
                   break;
          }
          MApp_ZUI_API_LoadString(u16OptionID, u16con_buffer);
          Load_Flag = TRUE;
          break;
    #endif
        case HWND_MENU_OPTION_CLOSEDCAPTION_ITEM_BASICSELECTION_OPTION:
            switch(stGenSetting.g_CaptionSetting.u8CaptionServiceModeATV)
            {
                default:
                case CAPTIONMENU_SERVICE_CC1:
                    u16OptionID = en_str_CC_1;
                    break;
                case CAPTIONMENU_SERVICE_CC2:
                    u16OptionID = en_str_CC_2;
                    break;
                case CAPTIONMENU_SERVICE_CC3:
                    u16OptionID = en_str_CC_3;
                    break;
                case CAPTIONMENU_SERVICE_CC4:
                    u16OptionID = en_str_CC_4;
                    break;
                case CAPTIONMENU_SERVICE_TEXT1:
                    u16OptionID = en_str_Text1;
                    break;
                case CAPTIONMENU_SERVICE_TEXT2:
                    u16OptionID = en_str_Text2;
                    break;
                case CAPTIONMENU_SERVICE_TEXT3:
                    u16OptionID = en_str_Text3;
                    break;
                case CAPTIONMENU_SERVICE_TEXT4:
                    u16OptionID = en_str_Text4;
                    break;
                case CAPTIONMENU_SERVICE_OFF:
                    u16OptionID = en_str_Off;
                    break;
            }
            u16TextID = en_str_Basic_Selection;
            MApp_ZUI_API_LoadString(u16OptionID, u16con_buffer);
            Load_Flag = TRUE;
            break;
        case HWND_MENU_OPTION_CLOSEDCAPTION_ITEM_ADVANCESELECTION_OPTION:
            switch(stGenSetting.g_CaptionSetting.u8CaptionServiceModeDTV)
            {
            default:
            case CAPTIONMENU_SERVICE_SERVICE1:
                u16OptionID = en_str_Service1;
                break;
            case CAPTIONMENU_SERVICE_SERVICE2:
                u16OptionID = en_str_Service2;
                break;
            case CAPTIONMENU_SERVICE_SERVICE3:
                u16OptionID = en_str_Service3;
                break;
            case CAPTIONMENU_SERVICE_SERVICE4:
                u16OptionID = en_str_Service4;
                break;
            case CAPTIONMENU_SERVICE_SERVICE5:
                u16OptionID = en_str_Service5;
                break;
            case CAPTIONMENU_SERVICE_SERVICE6:
                u16OptionID = en_str_Service6;
                break;
            case CAPTIONMENU_SERVICE_OFF:
                u16OptionID = en_str_Off;
                break;
            }
            u16TextID = en_str_Advanced_Selection;
            MApp_ZUI_API_LoadString(u16OptionID, u16con_buffer);
            Load_Flag = TRUE;
            break;
        case HWND_MENU_SOUND_EQ_ADVANCE_150HZ_VALUE:
            u16OptionID = MApp_UiMenuFunc_GetAudio150HzValue();
            u16TextID = en_str_120Hz;
            break;
        case HWND_MENU_SOUND_EQ_ADVANCE_500HZ_VALUE:
            u16OptionID = MApp_UiMenuFunc_GetAudio500HzValue();
            u16TextID = en_str_500Hz;
            break;
        case HWND_MENU_SOUND_EQ_ADVANCE_1000HZ_VALUE:
            u16OptionID = MApp_UiMenuFunc_GetAudio1000HzValue();
            u16TextID =en_str_1_dot_5_KHz;
            break;
        case HWND_MENU_SOUND_EQ_ADVANCE_2000HZ_VALUE:
            u16OptionID = MApp_UiMenuFunc_GetAudio2000HzValue();
            u16TextID = en_str_5KHz;
            break;
        case HWND_MENU_SOUND_EQ_ADVANCE_4000HZ_VALUE:
            u16OptionID = MApp_UiMenuFunc_GetAudio4000HzValue();
            u16TextID = en_str_10KHz;
            break;
		case HWND_MENU_KEYSTONE_VALUE_OPTION:
			printf("stGenSetting.g_SysSetting.KeyStoneValue--------%d \n",stGenSetting.g_SysSetting.KeyStoneValue);
			u16OptionID = stGenSetting.g_SysSetting.KeyStoneValue;
			u16TextID = en_str_10KHz;
			break;
        case HWND_MENU_SOUND_EQ_ADVANCE_BALANCE_VALUE:
            u16OptionID = MApp_UiMenuFunc_GetAudioBalanceValue();
            u16TextID = en_str_Balance;
            break;
    #endif
        case HWND_MENU_COMMON_ADJ_ITEM2_OPTION:
            if(g_mainpage_common == EN_COMMON_PICTURE_MODE_PAGE)
            {
                u16TextID = en_str_Contrast;
                u16OptionID = ST_PICTURE.u8Contrast;
                #if ENABLE_AUTOTEST
                if(g_bAutobuildDebug)
                {
                    if(PicContrast != u16OptionID)
                    {
                        printf("41_PicContrast\n");
                    }
                    PicContrast = u16OptionID;
                }
                #endif
            }
            else if(g_mainpage_common == EN_COMMON_PICTURE_COLOR_PAGE)
            {
                u16TextID = en_str_Red;
                u16OptionID = _MApp_ZUI_ACT_GetColorTempColorValue(hwnd);
                #if ENABLE_AUTOTEST
                if(g_bAutobuildDebug)
                {
                    if(ColorR != u16OptionID)
                    {
                        printf("42_ColorR\n");
                    }
                    ColorR = u16OptionID;
                }
                #endif
            }

         #if ENABLE_GAMMA_ADJUST
            else if(g_mainpage_common == EN_COMMON_GAMMA_ADJUST_PAGE)
            {
                u16TextID = en_str_Red;
                u16OptionID = _MApp_ZUI_ACT_GetGammaRGBValue(hwnd);
            }
         #endif
            else if(g_mainpage_common == EN_COMMON_SOUND_SWITCH_PAGE)
            {
                u16TextID = en_str_AD_Volume;
                u16OptionID = stGenSetting.g_SoundSetting.ADVolume;
            }
            else if(g_mainpage_common == EN_COMMON_OFFTIMER_PAGE)
            {
                return MApp_ZUI_ACT_GetSetOffTimeDynamicText(hwnd);
            }
            else if(g_mainpage_common == EN_COMMON_ONTIMER_PAGE)
            {
                return MApp_ZUI_ACT_GetSetOnTimeDynamicText(hwnd);
            }
            else if(g_mainpage_common == EN_COMMON_TIME_CLOCK_PAGE)
            {
                return MApp_ZUI_ACT_GetSetClockDynamicText(hwnd);
            }
        #if (ENABLE_EXTERN_MFC_CHIP)
            else if(g_mainpage_common == EN_COMMON_SET_MFC_PAGE)
            {
                u16TextID = en_str_MFC;
                switch(stGenSetting.stDevMfcSetting.enMFCStrength)
                {
                    case EN_MFC_Strength_Off:
                        u16OptionID = en_str_Off;
                        break;
                    case EN_MFC_Strength_Weak:
                        u16OptionID = en_str_Low;
                        break;
                    case EN_MFC_Strength_Strong:
                        u16OptionID = en_str_High;
                        break;
                    default:
                        u16OptionID = en_str_Middle;
                        break;
                }
                MApp_ZUI_API_LoadString(u16OptionID, u16con_buffer);
                Load_Flag = TRUE;

            }
        #endif
        #if ENABLE_ATSC_TTS
            else if(g_mainpage_common == EN_COMMON_OPTION_TTS_PAGE)
            {
                u16TextID = en_str_Volume;

                switch(stGenSetting.g_SysSetting.u8TTSVolume)
                {
                    case EN_VOICE_GUIDE_VOLUME_LOW:
                         u16OptionID = en_str_Low;
                         break;
                    case EN_VOICE_GUIDE_VOLUME_MEDIUM:
                         u16OptionID = en_str_Middle;
                         break;
                    case EN_VOICE_GUIDE_VOLUME_HIGH:
                         u16OptionID = en_str_High;
                         break;
                }

                MApp_ZUI_API_LoadString(u16OptionID, u16con_buffer);
                Load_Flag = TRUE;
            }
        #endif
            break;


        case HWND_MENU_COMMON_ADJ_ITEM3_OPTION:
            if(g_mainpage_common == EN_COMMON_PICTURE_MODE_PAGE)
            {
                u16TextID = en_str_Brightness;
                u16OptionID = ST_PICTURE.u8Brightness;
                #if ENABLE_AUTOTEST
                if(g_bAutobuildDebug)
                {
                    if(PicBright != u16OptionID)
                    {
                        printf("41_PicBright\n");
                    }
                    PicBright = u16OptionID;
                }
                #endif
            }
        #if (ENABLE_ATSC_AD_FUNC)
            else if(g_mainpage_common == EN_COMMON_SOUND_SWITCH_PAGE)
            {
                u16TextID = en_str_AD_Mix_Setting;
                u16OptionID = stGenSetting.g_SoundSetting.ADMixSetting;
            }
        #endif
            else if(g_mainpage_common == EN_COMMON_PICTURE_COLOR_PAGE)
            {
                u16TextID = en_str_Green;
                u16OptionID = _MApp_ZUI_ACT_GetColorTempColorValue(hwnd);
                #if ENABLE_AUTOTEST
                if(g_bAutobuildDebug)
                {
                    if(ColorG != u16OptionID)
                    {
                        printf("42_ColorG\n");
                    }
                    ColorG = u16OptionID;
                }
                #endif

            }
       #if ENABLE_GAMMA_ADJUST
            else if(g_mainpage_common == EN_COMMON_GAMMA_ADJUST_PAGE)
            {
                u16TextID = en_str_Green;
                u16OptionID = _MApp_ZUI_ACT_GetGammaRGBValue(hwnd);

            }
       #endif
            else if(g_mainpage_common == EN_COMMON_OFFTIMER_PAGE)
            {
                MApp_ZUI_ACT_GetSetOffTimeDynamicText(hwnd);
            }
            else if(g_mainpage_common == EN_COMMON_ONTIMER_PAGE)
            {
                MApp_ZUI_ACT_GetSetOnTimeDynamicText(hwnd);
            }
            else if(g_mainpage_common == EN_COMMON_TIME_CLOCK_PAGE)
            {
                return MApp_ZUI_ACT_GetSetClockDynamicText(hwnd);
            }
        #if (ENABLE_EXTERN_MFC_CHIP)
            else if(g_mainpage_common == EN_COMMON_SET_MFC_PAGE)
            {
                u16TextID = en_str_MFC_Demo;
                switch(stGenSetting.stDevMfcSetting.enMEMCType)
                {
                    case MFC_Horizantal:
                        u16OptionID = en_str_Horizon;
                        break;
                    case MFC_Vertical:
                        u16OptionID = en_str_Vertical;
                        break;
                    default:
                        u16OptionID = en_str_Off;
                        break;
                }

                MApp_ZUI_API_LoadString(u16OptionID, u16con_buffer);
                Load_Flag = TRUE;
            }
        #endif
        #if ENABLE_ATSC_TTS
            else if(g_mainpage_common == EN_COMMON_OPTION_TTS_PAGE)
            {
                u16TextID = en_str_Speed;

                switch(stGenSetting.g_SysSetting.u8TTSSpeed)
                {

                    case EN_VOICE_GUIDE_SPEED_SLOW:
                         u16OptionID = en_str_Low;
                         break;
                    case EN_VOICE_GUIDE_SPEED_NORMAL:
                         u16OptionID = en_str_Middle;
                         break;
                    case EN_VOICE_GUIDE_SPEED_FAST:
                         u16OptionID = en_str_High;
                         break;
                }

                MApp_ZUI_API_LoadString(u16OptionID, u16con_buffer);
                Load_Flag = TRUE;
            }
        #endif
            break;


        case HWND_MENU_COMMON_ADJ_ITEM4_OPTION:
            if(g_mainpage_common == EN_COMMON_PICTURE_MODE_PAGE)
            {
                u16TextID = en_str_Color;
                u16OptionID = ST_PICTURE.u8Saturation;
                #if ENABLE_AUTOTEST
                if(g_bAutobuildDebug)
                {
                    if(PicColor != u16OptionID)
                    {
                        printf("41_PicColor\n");
                    }
                    PicColor = u16OptionID;
                }
                #endif
            }
            else if(g_mainpage_common == EN_COMMON_PICTURE_COLOR_PAGE)
            {
                u16TextID = en_str_Blue;
                u16OptionID = _MApp_ZUI_ACT_GetColorTempColorValue(hwnd);
                #if ENABLE_AUTOTEST
                if(g_bAutobuildDebug)
                {
                if(ColorB != u16OptionID)
                {
                printf("42_ColorB\n");
                }
                ColorB = u16OptionID;
                }
                #endif
            }
        #if ENABLE_GAMMA_ADJUST
            else if(g_mainpage_common == EN_COMMON_GAMMA_ADJUST_PAGE)
            {
                u16TextID = en_str_Blue;
                u16OptionID = _MApp_ZUI_ACT_GetGammaRGBValue(hwnd);
            }
        #endif
            else if(g_mainpage_common == EN_COMMON_ONTIMER_PAGE)
            {
// Thomas to
            }
            else if(g_mainpage_common == EN_COMMON_TIME_CLOCK_PAGE)
            {
                return MApp_ZUI_ACT_GetSetClockDynamicText(hwnd);
            }
        #if ENABLE_ATSC_TTS
            else if(g_mainpage_common == EN_COMMON_OPTION_TTS_PAGE)
            {
                u16TextID = en_str_Pitch;
                switch(stGenSetting.g_SysSetting.u8TTSPitch)
                {
                    case EN_VOICE_GUIDE_PITCH_LOW:
                         u16OptionID = en_str_Low;
                         break;
                    case EN_VOICE_GUIDE_PITCH_MEDIUM:
                         u16OptionID = en_str_Middle;
                         break;
                    case EN_VOICE_GUIDE_PITCH_HIGH:
                         u16OptionID = en_str_High;
                         break;
                }
                MApp_ZUI_API_LoadString(u16OptionID, u16con_buffer);
                Load_Flag = TRUE;
            }
        #endif
            break;


        case HWND_MENU_COMMON_ADJ_ITEM5_OPTION:
            u16TextID = en_str_Sharpness;
            u16OptionID = ST_PICTURE.u8Sharpness;
            #if ENABLE_AUTOTEST
            if(g_bAutobuildDebug)
            {
                if(PicSharpness != u16OptionID)
                {
                    printf("41_PicSharpness\n");
                }
                PicSharpness = u16OptionID;
            }
            #endif
            break;
        case HWND_MENU_COMMON_ADJ_ITEM6_OPTION:
            u16TextID = en_str_Tint;
            u16OptionID = ST_PICTURE.u8Hue;
            #if ENABLE_AUTOTEST
            if(g_bAutobuildDebug)
            {
                if(PicTint != u16OptionID)
                {
                    printf("41_PicTint\n");
                }
                PicTint = u16OptionID;
            }
            #endif
            break;
        case HWND_MENU_SNDMODE_TREBLE_OPTION:
            u16TextID = en_str_Treble;
            u16OptionID = _MApp_ZUI_ACT_GetSoundAdjustValue(hwnd);
            break;
        case HWND_MENU_SNDMODE_BASS_OPTION:
            u16TextID = en_str_Bass;
            u16OptionID = _MApp_ZUI_ACT_GetSoundAdjustValue(hwnd);
            break;
        case HWND_MENU_SNDEQ_120_HZ_OPTION:
            u16TextID = en_str_120Hz;
            u16OptionID = _MApp_ZUI_ACT_GetSoundAdjustValue(hwnd);
            break;

        case HWND_MENU_SNDEQ_200_HZ_OPTION:
          #if (  CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD   \
              || CHIP_FAMILY_TYPE == CHIP_FAMILY_A7     \
              || CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA)
            u16TextID = en_str_500Hz;
          #else
            u16TextID = en_str_200Hz;
          #endif

            u16OptionID = _MApp_ZUI_ACT_GetSoundAdjustValue(hwnd);
            break;


        case HWND_MENU_SNDEQ_500_HZ_OPTION:
          #if (  CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD   \
              || CHIP_FAMILY_TYPE == CHIP_FAMILY_A7     \
              || CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA)
            u16TextID = en_str_1_dot_5_KHz;
          #else
            u16TextID = en_str_500Hz;
          #endif
            u16OptionID = _MApp_ZUI_ACT_GetSoundAdjustValue(hwnd);
            break;

        case HWND_MENU_SNDEQ_1_2_KHZ_OPTION:
            #if(CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD \
                || CHIP_FAMILY_TYPE == CHIP_FAMILY_A7\
                || CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA)
            u16TextID = en_str_5KHz;
            #else
            u16TextID = en_str_1_dot_2_KHz;
            #endif
            u16OptionID = _MApp_ZUI_ACT_GetSoundAdjustValue(hwnd);
            break;

        case HWND_MENU_SNDEQ_3_KHZ_OPTION:
            #if(CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD \
                || CHIP_FAMILY_TYPE == CHIP_FAMILY_A7\
                || CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA)
            u16TextID = en_str_10KHz;
            #else
            u16TextID = en_str_3KHz;
            #endif
            u16OptionID = _MApp_ZUI_ACT_GetSoundAdjustValue(hwnd);
            break;

        case HWND_MENU_SNDEQ_7_5_KHZ_OPTION:
            u16TextID = en_str_7dot5KHz;
            u16OptionID = _MApp_ZUI_ACT_GetSoundAdjustValue(hwnd);
            break;

        case HWND_MENU_SNDEQ_12_KHZ_OPTION:
            u16TextID = en_str_12KHz;
            u16OptionID = _MApp_ZUI_ACT_GetSoundAdjustValue(hwnd);
            break;

#if (ENABLE_PIP)
         case HWND_MENU_PIP_SUBSRC_OPTION:
            if(IsPIPSupported())
            {
                u16TextID = en_str_Sub_Source;
                //Check source compatibility here
                if(!MApp_InputSource_PIP_IsSrcCompatible(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),
                            MApp_InputSource_GetInputSourceType(UI_SUB_INPUT_SOURCE_TYPE)))
                {
                    stGenSetting.g_stPipSetting.enSubInputSourceType = MApp_InputSource_GetUIInputSourceType(MApp_InputSource_PIP_Get1stCompatibleSrc(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)));
                }
                switch(stGenSetting.g_stPipSetting.enSubInputSourceType)
                {
                    default:
                #if(ENABLE_DTV)
                    #if ((UI_SKIN_SEL == UI_SKIN_1366X768X565) \
                        || (UI_SKIN_SEL == UI_SKIN_1366X768X4444) \
                        || (UI_SKIN_SEL == UI_SKIN_1366X768X8888) \
                        || (UI_SKIN_SEL == UI_SKIN_1920X1080X565) \
                        || UI_SKIN_SEL == UI_SKIN_960X540X565\
                        )
                        case UI_INPUT_SOURCE_DVBT:
                            u16OptionID = en_str_DVBdashT;
                            break;

                        case UI_INPUT_SOURCE_DVBC:
                            u16OptionID = en_str_DVBdashC;
                            break;

                        case UI_INPUT_SOURCE_DTMB:
                            u16OptionID = en_str_DTMB;
                            break;

                        case UI_INPUT_SOURCE_ISDBT:
                            u16OptionID = en_str_ISDB;
                            break;

                        case UI_INPUT_SOURCE_ATSC:
                            u16OptionID = en_str_ATSC;
                            break;

                    #else
                    case UI_INPUT_SOURCE_DVBT:
                    case UI_INPUT_SOURCE_DVBC:
                    case UI_INPUT_SOURCE_DTMB:
                    case UI_INPUT_SOURCE_ISDBT:
                    case UI_INPUT_SOURCE_ATSC:
                        u16OptionID = en_str_DTV;
                        break;
                    #endif
                #endif

                    case UI_INPUT_SOURCE_ATV:
                        u16OptionID = en_str_ATV;
                        break;
                    case UI_INPUT_SOURCE_RGB:
                        u16OptionID = en_str_PCdashRGB;
                        break;
                #if (INPUT_AV_VIDEO_COUNT >= 1)
                    case UI_INPUT_SOURCE_AV:
                        u16OptionID = en_str_AV_1;
                        break;
                #endif
                #if (INPUT_AV_VIDEO_COUNT >= 2)
                    case UI_INPUT_SOURCE_AV2:
                        u16OptionID = en_str_AV_2;
                        break;
                #endif
                #if (INPUT_AV_VIDEO_COUNT >= 3)
                    case UI_INPUT_SOURCE_AV3:
                        u16OptionID = en_str_AV_3;
                        break;
                #endif
                #if (INPUT_YPBPR_VIDEO_COUNT >= 1)
                    case UI_INPUT_SOURCE_COMPONENT:
                        u16OptionID = en_str_Component1;
                        break;
                #endif
                #if (INPUT_YPBPR_VIDEO_COUNT >= 2)
                    case UI_INPUT_SOURCE_COMPONENT2:
                        u16OptionID = en_str_Component2;
                        break;
                #endif
                #if (INPUT_HDMI_VIDEO_COUNT >= 1)
                    case UI_INPUT_SOURCE_HDMI:
                        u16OptionID = en_str_HDMI1;
                        break;
                #endif
                #if (INPUT_HDMI_VIDEO_COUNT >= 2)
                    case UI_INPUT_SOURCE_HDMI2:
                        u16OptionID = en_str_HDMI2;
                        break;
                #endif
                #if (INPUT_HDMI_VIDEO_COUNT >= 3)
                    case UI_INPUT_SOURCE_HDMI3:
                        u16OptionID = en_str_HDMI3;
                        break;
                #endif
                #if (INPUT_HDMI_VIDEO_COUNT >= 4)
                    case UI_INPUT_SOURCE_HDMI4:
                        u16OptionID = en_str_HDMI4;
                        break;
                #endif
                #if (INPUT_SCART_VIDEO_COUNT >= 1)
                    case UI_INPUT_SOURCE_SCART:
                        u16OptionID = en_str_SCART_1;
                        break;
                #endif
                #if (INPUT_SCART_VIDEO_COUNT >= 2)
                    case UI_INPUT_SOURCE_SCART2:
                        u16OptionID = en_str_SCART_2;
                        break;
                #endif
                #if (INPUT_SV_VIDEO_COUNT >= 1)
                    case UI_INPUT_SOURCE_SVIDEO:
                         u16OptionID = en_str_SdashVideo_1;
                        break;
                #endif
                #if (INPUT_SV_VIDEO_COUNT >= 2)
                    case UI_INPUT_SOURCE_SVIDEO2:
                        u16OptionID = en_str_SdashVideo_2;
                        break;
                #endif
                }
                MApp_ZUI_API_LoadString(u16OptionID, u16con_buffer);
                Load_Flag = TRUE;
            }
            break;
         case HWND_MENU_PIP_SIZE_OPTION:
            if(IsPIPSupported())
            {
                u16TextID = en_str_Size;
                switch(stGenSetting.g_stPipSetting.enPipSize)
                {
                    default:
                    case EN_PIP_SIZE_SMALL:
                        u16OptionID = en_str_Small;
                        break;
                    case EN_PIP_SIZE_MEDIUM:
                        u16OptionID = en_str_Medium;
                        break;
                    case EN_PIP_SIZE_LARGE:
                        u16OptionID = en_str_Large;
                        break;
                }
                MApp_ZUI_API_LoadString(u16OptionID, u16con_buffer);
                Load_Flag = TRUE;
            }
            break;
         case HWND_MENU_PIP_POSITION_OPTION:
            if(IsPIPSupported())
            {
                u16TextID = en_str_Position;
                switch(stGenSetting.g_stPipSetting.enPipPosition)
                {
                    default:
                    case EN_PIP_POSITION_LEFT_TOP:
                        u16OptionID = en_str_LeftdashTop;
                        break;
                    case EN_PIP_POSITION_RIGHT_TOP:
                        u16OptionID = en_str_RightdashTop;
                        break;
                    case EN_PIP_POSITION_LEFT_BOTTOM:
                        u16OptionID = en_str_LeftdashBottom;
                        break;
                    case EN_PIP_POSITION_RIGHT_BOTTOM:
                        u16OptionID = en_str_RightdashBottom;
                        break;
                }
                MApp_ZUI_API_LoadString(u16OptionID, u16con_buffer);
                Load_Flag = TRUE;
            }
            break;
         case HWND_MENU_PIP_SOUND_SRC_OPTION:
            if(IsPIPSupported())
            {
                u16TextID = en_str_Sound_Source;
                if(!stGenSetting.g_stPipSetting.enPipSoundSrc)
                    u16OptionID=en_str_Main;
                else
                    u16OptionID=en_str_Sub;

                MApp_ZUI_API_LoadString(u16OptionID, u16con_buffer);
                Load_Flag = TRUE;
            }
            break;
        case HWND_MENU_PIP_BORDER_OPTION:
            if(IsPIPSupported())
            {
                u16TextID = en_str_Border;
                if(!stGenSetting.g_stPipSetting.bBolderEnable)
                    u16OptionID=en_str_Off;
                else
                    u16OptionID=en_str_On;

                MApp_ZUI_API_LoadString(u16OptionID, u16con_buffer);
                Load_Flag = TRUE;
            }
            break;
#endif //#if (ENABLE_PIP)
        case HWND_MENU_PCMODE_HPOS_OPTION:
            u16TextID = en_str_Horizontal_Posdot;
            u16OptionID = MApp_ZUI_ACT_GetPcModeAdjustValue(hwnd);
            break;
        case HWND_MENU_PCMODE_VPOS_OPTION:
            u16TextID = en_str_Vertical_Pos;
            u16OptionID = MApp_ZUI_ACT_GetPcModeAdjustValue(hwnd);
            break;
        case HWND_MENU_PCMODE_SIZE_OPTION:
            u16TextID = en_str_Size;
            u16OptionID = MApp_ZUI_ACT_GetPcModeAdjustValue(hwnd);
            break;
        case HWND_MENU_PCMODE_PHASE_OPTION:
            u16TextID = en_str_Phase;
            u16OptionID = MApp_ZUI_ACT_GetPcModeAdjustValue(hwnd);
            break;

    #if(ENABLE_DTV)
        case HWND_MENU_DLG_SIGNAL_INFORMAT_MODULATION_NAME:
        {
        #if 0//ENABLE_S2
            if (IsS2InUse())
            {
                u16str[0] = CHAR_SPACE;
                u16str[1] = 0;
                return u16str;
            }
        #endif
            WORD ModulMode=0;
            WORD SignalStrength=0;
            u16TextID = en_str_Constellation;
            msAPI_Tuner_CheckSignalStrength(&SignalStrength);

            if(SignalStrength>3)
            {
                if (msAPI_Tuner_GetSignalModulMode(&ModulMode))
                {
                    if(ModulMode == 0)
                        u16OptionID = en_str_QPSK;
                    else if(ModulMode == 1)
                    #if ENABLE_S2
                        if (IsS2InUse())
                        {
                            u16OptionID = en_str_8PSK;
                        }
                        else
                    #endif
                        {
                        u16OptionID = en_str_16QAM;
                        }
                    else if(ModulMode == 2)
                        u16OptionID = en_str_64QAM;
                    else if(ModulMode == 3)
                    {
                    #if ENABLE_DVB_T2
                        if(DVB_T2_DEMOD == MApp_DTV_Scan_T2_ScanCheckSignal())
                            u16OptionID = en_str_256QAM;
                        else
                    #endif
                            u16OptionID = en_str_128QAM;
                    }
                    else if(ModulMode == 4)
                        u16OptionID = en_str_256QAM;
                    else
                        u16OptionID = en_str_Unknow;
                }
                else
                {
                    u16OptionID = en_str_Unknow;
                }
            }
            else
                u16OptionID = en_str_Unknow;

            MApp_ZUI_API_LoadString(u16OptionID, u16con_buffer);
            Load_Flag = TRUE;
            break;
        }
        #if(ENABLE_DTV)
         case HWND_MENU_DLG_SIGNAL_INFORMAT_CHANNEL_NAME:
        #if ENABLE_DVBC
            if(IsDVBCInUse())
            {
                u16TextID   = en_str_Frequency;
                u16OptionID = MApp_CadtvManualTuning_GetFrequency();
            }
            else
        #endif
        #if ENABLE_S2
            if (IsS2InUse())
            {
                U16 u16Count, u16Pos=0;
                MEMBER_SERVICETYPE bServiceType;
            #if MHEG5_ENABLE
                bServiceType=g_eCurrentUserServiceType;
                u16Count = msAPI_CM_CountProgram(bServiceType, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                if (bServiceType == E_SERVICETYPE_DTV)
                    u16Pos = g_wCurrentTVUserServicePosition;
                else if(bServiceType == E_SERVICETYPE_RADIO)
                    u16Pos = g_wCurrentRadioUserServicePosition;
            #if NORDIG_FUNC
                else if(bServiceType == E_SERVICETYPE_DATA)
                    u16Pos = g_wCurrentDataUserServicePosition;
            #endif
                else
                    u16Pos = 0;
            #else
                bServiceType = msAPI_CM_GetCurrentServiceType();
                u16Count = msAPI_CM_CountProgram(bServiceType, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                u16Pos = msAPI_CM_GetCurrentPosition(bServiceType);
            #endif
                u16OptionID = msAPI_CM_GetLogicalChannelNumber(bServiceType, u16Pos);
            }
            else
        #endif
            {
                u16TextID   = en_str_Channel;
                u16OptionID = msAPI_CM_GetPhysicalChannelNumber(msAPI_CM_GetCurrentServiceType(),msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()));
            }
            break;
        #endif
        case HWND_MENU_DLG_SIGNAL_INFORMAT_QUALITY_PERCENT_VAL:
            u16TextID = en_str_Quality;
            u16OptionID = msAPI_Tuner_GetSignalQualityPercentage();
            if(u16OptionID > 100)
            {
                u16OptionID = 100;
            }
            break;
        case HWND_MENU_DLG_SIGNAL_INFORMAT_STRENGTH_PERCENT_VAL:
        {
            WORD SignalStrength=0;
            u16TextID = en_str_Strength;
            msAPI_Tuner_CheckSignalStrength(&SignalStrength);
            u16OptionID = SignalStrength;
            if(u16OptionID > 100)
            {
                u16OptionID = 100;
            }
            break;
        }
    #endif

    }
    MApp_ZUI_API_LoadString(u16TextID, u16str);
    u16len = MApp_ZUI_API_Strlen(u16str);
    u16str[u16len++] = CHAR_SPACE;
    u16str[u16len++] = 0;
    if(Load_Flag == FALSE)
    {
        MApp_UlongToU16String(u16OptionID, (U16*)u16con_buffer, MApp_GetNoOfDigit(u16OptionID));
    }

    MApp_ZUI_API_Strcat(u16str,(U16*)u16con_buffer);
    return u16str;
}
#if ENABLE_GAMMA_ADJUST
LPTSTR MApp_ZUI_ACT_GetGammaAdjustDynamicText(void)
{
    U16 u16TempID = Empty;

            U16 u16Len = 0;
            LPTSTR u16str = CHAR_BUFFER;
    U8 Gamma_Adjust;
            switch(stGenSetting.g_GammaSetting.u8Gain)
            {
                default:
                case MS_GAMMAADJUST_5:
                    Gamma_Adjust=5;
                    break;
                case MS_GAMMAADJUST_10:
                    Gamma_Adjust=10;
                    break;
                case MS_GAMMAADJUST_20:
                    Gamma_Adjust=20;
                    break;
                case MS_GAMMAADJUST_30:
                    Gamma_Adjust=30;
                    break;
                case MS_GAMMAADJUST_40:
                    Gamma_Adjust=40;
                    break;
                case MS_GAMMAADJUST_50:
                    Gamma_Adjust=50;
                    break;
                case MS_GAMMAADJUST_60:
                    Gamma_Adjust=60;
                    break;
                case MS_GAMMAADJUST_70:
                    Gamma_Adjust=70;
                    break;
                case MS_GAMMAADJUST_80:
                    Gamma_Adjust=80;
                    break;
                case MS_GAMMAADJUST_90:
                    Gamma_Adjust=90;
                    break;
                case MS_GAMMAADJUST_100:
                    Gamma_Adjust=100;
                    break;

            }
            MApp_UlongToU16String(Gamma_Adjust, u16str, MApp_GetNoOfDigit(Gamma_Adjust));
            u16Len = MApp_ZUI_API_Strlen(u16str);
            u16str[u16Len++] = CHAR_SPACE;
            u16str[u16Len++] = CHAR_PERCENT;
            u16str[u16Len++] = 0;
            return u16str;

    if (u16TempID != Empty)
        return MApp_ZUI_API_GetString(u16TempID);
    return 0; //for empty string....
}
#endif
#if ENABLE_ATSC
U8 _MApp_ZUI_ACT_MenuChannelListWindowMapToIndex(HWND hwnd)
{
    U8 i;
    for (i = 0; i < MAX_NUM_OF_SRV_ITEM; i++)
    {
        if (hwnd == _MenuChannelListHwndList[i] ||
            MApp_ZUI_API_IsSuccessor(_MenuChannelListHwndList[i], hwnd))
        {
            return i;
        }
    }
    return 0;
}

#endif

void _MApp_ZUI_ACT_CombineDureTimerString(LPTSTR str, U32 TIMER)
{
    U32 u32SleepTime = TIMER;
    U8 u8SleepDigits = MApp_GetNoOfDigit(u32SleepTime);
    __MApp_UlongToString(u32SleepTime, str, u8SleepDigits);
    MApp_ZUI_API_LoadString(en_str_SleepTimer_Sec, str + u8SleepDigits);
}

///////////////////////////////////////////////////////////////////////////////
///  private  MApp_ZUI_ACT_GetMenuItemDynamicText
///  dynamic text content provider in menu items
///
///  @param [in]       hwnd HWND     window handle we are processing
///
///  @return LPCTSTR     string content
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
LPTSTR MApp_ZUI_ACT_GetMenuItemDynamicText(HWND hwnd)
{
    U16 u16TempID = Empty;
    tempcheck2 = hwnd;
    U16 u16Value = 0;
#if ENABLE_ATSC
    U8 *pu8String;
    //LPTSTR Au8String;
#endif

    // Fix unused warning
    u16Value=u16Value;

    switch (hwnd)
    {
#if ((ATSC_CC == ATV_CC) || ENABLE_ISDB_ATV_VCHIP)
        case HWND_MENU_LOCK_VCHIPSUBPAGE_ITEM1_TEXT:
            if(g_vchipPageType == EN_VCHIP_MPAA)
            {
                u16TempID = en_str_G;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAENG)
            {
                u16TempID = en_str_C;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAFRE)
            {
                u16TempID = en_str_G;
            }
            break;
        case HWND_MENU_LOCK_VCHIPSUBPAGE_ITEM2_TEXT:
            if(g_vchipPageType == EN_VCHIP_MPAA)
            {
                u16TempID = en_str_PG;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAENG)
            {
                u16TempID = en_str_C8plus;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAFRE)
            {
                u16TempID = en_str_8ansplus;
            }
            break;
        case HWND_MENU_LOCK_VCHIPSUBPAGE_ITEM3_TEXT:
            if(g_vchipPageType == EN_VCHIP_MPAA)
            {
                u16TempID = en_str_PGdash13;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAENG)
            {
                u16TempID = en_str_G;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAFRE)
            {
                u16TempID = en_str_13ansplus;
            }
            break;
        case HWND_MENU_LOCK_VCHIPSUBPAGE_ITEM4_TEXT:
            if(g_vchipPageType == EN_VCHIP_MPAA)
            {
                u16TempID = en_str_R;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAENG)
            {
                u16TempID = en_str_PG;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAFRE)
            {
                u16TempID = en_str_16ansplus;
            }
            break;
        case HWND_MENU_LOCK_VCHIPSUBPAGE_ITEM5_TEXT:
            if(g_vchipPageType == EN_VCHIP_MPAA)
            {
                u16TempID = en_str_NCdash17;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAENG)
            {
                u16TempID = en_str_14plus;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAFRE)
            {
                u16TempID = en_str_18ansplus;
            }
            break;
        case HWND_MENU_LOCK_VCHIPSUBPAGE_ITEM6_TEXT:
            if(g_vchipPageType == EN_VCHIP_MPAA)
            {
                u16TempID = en_str_X;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAENG)
            {
                u16TempID = en_str_18plus;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAFRE)
            {
                u16TempID = en_str_EXEMPT;
            }
            break;
        case HWND_MENU_LOCK_VCHIPSUBPAGE_ITEM7_TEXT:
            if(g_vchipPageType == EN_VCHIP_MPAA)
            {
                u16TempID = en_str_NshashR;
            }
            break;

        case HWND_MENU_LOCK_VCHIPSUBPAGE_ITEM1_OPTION:
            if(g_vchipPageType == EN_VCHIP_MPAA)
            {
                if(stGenSetting.g_VChipSetting.u8VChipMPAAItem & VCHIP_MPAARATING_G)
                    u16TempID = en_str_LOCK;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAENG)
            {
                if(stGenSetting.g_VChipSetting.u8VChipCEItem == VCHIP_ENGRATING_C)
                    u16TempID = en_str_LOCK;
            }
            else
            {
                if(stGenSetting.g_VChipSetting.u8VChipCFItem == VCHIP_FRERATING_G)
                    u16TempID = en_str_LOCK;
            }
            break;
        case HWND_MENU_LOCK_VCHIPSUBPAGE_ITEM2_OPTION:
            if(g_vchipPageType == EN_VCHIP_MPAA)
            {
                if(stGenSetting.g_VChipSetting.u8VChipMPAAItem & VCHIP_MPAARATING_PG)
                    u16TempID = en_str_LOCK;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAENG)
            {
                if((stGenSetting.g_VChipSetting.u8VChipCEItem >=VCHIP_ENGRATING_C) && (stGenSetting.g_VChipSetting.u8VChipCEItem <=VCHIP_ENGRATING_C8Plus))
                    u16TempID = en_str_LOCK;
            }
            else
            {
                if((stGenSetting.g_VChipSetting.u8VChipCFItem >=VCHIP_FRERATING_G) && (stGenSetting.g_VChipSetting.u8VChipCFItem <=VCHIP_FRERATING_8ansPlus))
                   u16TempID = en_str_LOCK;
            }
            break;
        case HWND_MENU_LOCK_VCHIPSUBPAGE_ITEM3_OPTION:
            if(g_vchipPageType == EN_VCHIP_MPAA)
            {
                if(stGenSetting.g_VChipSetting.u8VChipMPAAItem & VCHIP_MPAARATING_PG_13)
                    u16TempID = en_str_LOCK;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAENG)
            {
                if((stGenSetting.g_VChipSetting.u8VChipCEItem >=VCHIP_ENGRATING_C) && (stGenSetting.g_VChipSetting.u8VChipCEItem <=VCHIP_ENGRATING_G))
                    u16TempID = en_str_LOCK;
            }
            else
            {
                if((stGenSetting.g_VChipSetting.u8VChipCFItem >=VCHIP_FRERATING_G) && (stGenSetting.g_VChipSetting.u8VChipCFItem <=VCHIP_FRERATING_13ansPlus))
                   u16TempID = en_str_LOCK;
            }
            break;
        case HWND_MENU_LOCK_VCHIPSUBPAGE_ITEM4_OPTION:
            if(g_vchipPageType == EN_VCHIP_MPAA)
            {
                if(stGenSetting.g_VChipSetting.u8VChipMPAAItem & VCHIP_MPAARATING_R)
                    u16TempID = en_str_LOCK;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAENG)
            {
                if((stGenSetting.g_VChipSetting.u8VChipCEItem >=VCHIP_ENGRATING_C) && (stGenSetting.g_VChipSetting.u8VChipCEItem <=VCHIP_ENGRATING_PG))
                    u16TempID = en_str_LOCK;
            }
            else
            {
                if((stGenSetting.g_VChipSetting.u8VChipCFItem >=VCHIP_FRERATING_G) && (stGenSetting.g_VChipSetting.u8VChipCFItem <=VCHIP_FRERATING_16ansPlus))
                   u16TempID = en_str_LOCK;
            }
            break;
        case HWND_MENU_LOCK_VCHIPSUBPAGE_ITEM5_OPTION:
            if(g_vchipPageType == EN_VCHIP_MPAA)
            {
                if(stGenSetting.g_VChipSetting.u8VChipMPAAItem & VCHIP_MPAARATING_NC_17)
                    u16TempID = en_str_LOCK;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAENG)
            {
                if((stGenSetting.g_VChipSetting.u8VChipCEItem >=VCHIP_ENGRATING_C) && (stGenSetting.g_VChipSetting.u8VChipCEItem <=VCHIP_ENGRATING_14Plus))
                    u16TempID = en_str_LOCK;
            }
            else
            {
                if((stGenSetting.g_VChipSetting.u8VChipCFItem >=VCHIP_FRERATING_G) && (stGenSetting.g_VChipSetting.u8VChipCFItem <=VCHIP_FRERATING_18ansPlus))
                   u16TempID = en_str_LOCK;
            }
            break;
        case HWND_MENU_LOCK_VCHIPSUBPAGE_ITEM6_OPTION:
            if(g_vchipPageType == EN_VCHIP_MPAA)
            {
                if(stGenSetting.g_VChipSetting.u8VChipMPAAItem & VCHIP_MPAARATING_X)
                    u16TempID = en_str_LOCK;
            }
            else
            {
                if((stGenSetting.g_VChipSetting.u8VChipCEItem >=VCHIP_ENGRATING_C) && (stGenSetting.g_VChipSetting.u8VChipCEItem <=VCHIP_ENGRATING_18Plus))
                    u16TempID = en_str_LOCK;
            }

            break;
        case HWND_MENU_LOCK_VCHIPSUBPAGE_ITEM7_OPTION:
            if(stGenSetting.g_VChipSetting.u8VChipMPAAItem & VCHIP_MPAARATING_NOT_RATED)
                u16TempID = en_str_LOCK;
            break;
		
#endif
//>>wht121101_1
           case HWND_MENU_PICTURE_PROJECTION_OPTION:
	           switch(stGenSetting.g_SysSetting.ProjectionType)
	           {
		            case EN_FRONT_DESKTOP:
		                u16TempID=en_str_Front_Desktop;
		                break;
		            case EN_FRONT_CEILING:
		                u16TempID=en_str_Front_Ceiling;
		                break;
		            case EN_REAR_DESKTOP:
		                u16TempID=en_str_Rear_Desktop;
		                break;
		            case EN_REAR_CEILING:
		                u16TempID=en_str_Rear_Ceiling;
		                break;
		            default:
		                break;
	            }
            break;
//<<wht121101_1
			case HWND_MENU_KEYSTONE_VALUE_OPTION:
			printf("stGenSetting.g_SysSetting.KeyStoneValue--------%d \n",stGenSetting.g_SysSetting.KeyStoneValue);
			return MApp_ZUI_API_GetS16SignString(stGenSetting.g_SysSetting.KeyStoneValue);
//>>wht121107_1
           case HWND_MENU_SOUND_POWER_ON_MUSIC_OPTION:
	           switch(stGenSetting.g_SysSetting.UsrPowerOnMusic)
	           {
		            case POWERON_MUSIC_DEFAULT:
		                u16TempID=en_str_On;
		                break;
		            case POWERON_MUSIC_OFF:
		                u16TempID=en_str_Off;
		                break;
		            default:
		                break;
	            }
            break;
//<<wht121107_1
		case HWND_MENU_OPTION_DUETIME_OPTION:
           switch(stGenSetting.g_SysSetting.OsdDuration)
           {
            case EN_OSD_TIME_5:
                _MApp_ZUI_ACT_CombineDureTimerString(CHAR_BUFFER, 5);
                 return CHAR_BUFFER;
            case EN_OSD_TIME_10:
                _MApp_ZUI_ACT_CombineDureTimerString(CHAR_BUFFER, 10);
                 return CHAR_BUFFER;
            case EN_OSD_TIME_15:
                _MApp_ZUI_ACT_CombineDureTimerString(CHAR_BUFFER, 15);
                 return CHAR_BUFFER;
            case EN_OSD_TIME_ALWAYS:
                u16TempID=en_str_Off;
                break;
            default:
                break;
		   }
		   break;
    #if ENABLE_ATSC_MENU_UI
      #if ENABLE_TTSTEST_FROM_USB
        case HWND_TEST_TTS_MIAN_PAGE_STRING_OPTION:
            return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, MApp_ZUI_ACT_GetTTSTestString(), strlen((char*)MApp_ZUI_ACT_GetTTSTestString()));

        case HWND_TEST_TTS_MIAN_PAGE_TRANSL_OPTION:
            return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, MApp_ZUI_ACT_GetTTSStrEngTransl(), strlen((char*)MApp_ZUI_ACT_GetTTSStrEngTransl()));

        case HWND_TTS_TEST_PLAYBACK_INFOBAR_ITEM1_STRING:     //add by hanson
            if(MApp_ZUI_ACT_QueryTTSTestPlayMode() == EN_TTSTEST_PAUSE)
            {
                u16TempID = en_str_Auto;//en_str_Pause;
            }
            else
            {
                u16TempID = en_str_Pause;//en_str_Auto;
            }
            break;

        case HWND_TTS_TEST_SPEED_ADJ_ITEM1_OPTION:
            return _MApp_ZUI_ACT_CombineTextAndOption(hwnd);
            break;

        case HWND_TTS_TEST_PITCH_ADJ_ITEM2_OPTION:
            return _MApp_ZUI_ACT_CombineTextAndOption(hwnd);
            break;
      #endif
        case HWND_MENU_CHANNEL_AUTO_SCAN_RESULT_PERCENT:
            return MApp_ZUI_API_GetU16String(MApp_Scan_ATSC_GetScanPercentageValue());
        case HWND_MENU_CHANNEL_AUTO_SCAN_RESULT_RF_CHANNEL_OPTION:
            return MApp_ZUI_API_GetU16String(MApp_Scan_ATSC_GetCurRfCh());
        case HWND_MENU_CHANNEL_AUTO_SCAN_RESULT_CH_TYPE_OPTION:
        #if ENABLE_ATSC_SCAN_NEW_MODE
            if(MApp_Scan_ATSC_GetScanType() == ATSC_SCAN_TYPE_AIR_DTV)
                u16TempID = en_str_Air_DTV;
            else if(MApp_Scan_ATSC_GetScanType() == ATSC_SCAN_TYPE_AIR_ATV)
                u16TempID = en_str_Air_TV;
            if(MApp_Scan_ATSC_GetScanType() == ATSC_SCAN_TYPE_CABLE_DTV)
                u16TempID = en_str_CADTV;
            else if(MApp_Scan_ATSC_GetScanType() == ATSC_SCAN_TYPE_CABLE_ATV)
                u16TempID = en_str_CATV;
        #else
            if(MApp_Scan_ATSC_GetScanChannelType() == SCAN_ANALOG_CHANNEL)
                u16TempID = en_str_ATV;
            else if(MApp_Scan_ATSC_GetScanChannelType() == SCAN_DIGITAL_CHANNEL)
                u16TempID = en_str_DTV;
            else
                u16TempID = en_str_DTV_plus_ATV;
        #endif
            break;
        case HWND_MENU_CHANNEL_AUTO_SCAN_RESULT_FOUND_OPTION:
            u16TempID = MApp_Scan_ATSC_GetScanCHFound();
            return MApp_ZUI_API_GetU16String(u16TempID);
        case HWND_MENU_CHANNEL_AUTO_SCAN_RESULT_ANALOG_OPTION:
            return MApp_ZUI_API_GetU16String(MApp_Scan_ATSC_GetScanAnalogCHFound());
        case HWND_MENU_CHANNEL_AUTO_SCAN_RESULT_DIGITAL_OPTION:
            return MApp_ZUI_API_GetU16String(MApp_Scan_ATSC_GetScanDigitalCHFound());
        case HWND_MENU_OPTION_CLOSEDCAPTION_ITEM_CCMODE_OPTION:
            switch(stGenSetting.g_CaptionSetting.u8CCMode)
            {
                default:
                case CAPTIONMENU_MODE_OFF:
                    u16TempID = en_str_CC_Off;
                    break;

                case CAPTIONMENU_MODE_ON:
                    u16TempID = en_str_CC_On;
                    break;
                #if (PARSING_CC_WHENMUTE)
                case CAPTIONMENU_MODE_CC_WHEN_MUTE:
                    u16TempID = en_str_CC_On_Mute;
                    break;
                #endif
            }
            break;
        case HWND_MENU_OPTION_CLOSEDCAPTION_ITEM_BASICSELECTION_OPTION:
            return _MApp_ZUI_ACT_CombineTextAndOption(hwnd);
            break;
        case HWND_MENU_OPTION_CLOSEDCAPTION_ITEM_ADVANCESELECTION_OPTION:
            return _MApp_ZUI_ACT_CombineTextAndOption(hwnd);
            break;

        case HWND_MENU_OPTION_CCOPTION_ITEM_MODE_OPTION:
            switch(stGenSetting.g_CaptionSetting.u8CSOptionMode)
            {
                default:
                case CAPTIONMENU_OPTIONMODE_DEFAULT:
                    u16TempID = en_str_Default;
                    break;

                case CAPTIONMENU_OPTIONMODE_CUSTOM:
                    u16TempID = en_str_Custom;
                    break;
            }
            break;
        case HWND_MENU_OPTION_CCOPTION_ITEM_FONTSTYLE_OPTION:
            if (stGenSetting.g_CaptionSetting.u8CSOptionMode==CAPTIONMENU_OPTIONMODE_DEFAULT)
            {
                u16TempID = en_str_Default;
                break;
            }
            switch(stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSFontStyle)
            {
                default:
                case CAPTIONMENU_FONT_STYLE_DEFAULT:
                    u16TempID = en_str_Default;
                    break;
                case CAPTIONMENU_FONT_STYLE_0:
                    u16TempID = en_str_Font_0;
                    break;
                case CAPTIONMENU_FONT_STYLE_1:
                    u16TempID = en_str_Font_1;
                    break;
                case CAPTIONMENU_FONT_STYLE_2:
                    u16TempID = en_str_Font_2;
                    break;
                case CAPTIONMENU_FONT_STYLE_3:
                    u16TempID = en_str_Font_3;
                    break;
                case CAPTIONMENU_FONT_STYLE_4:
                    u16TempID = en_str_Font_4;
                    break;
                case CAPTIONMENU_FONT_STYLE_5:
                    u16TempID = en_str_Font_5;
                    break;
                case CAPTIONMENU_FONT_STYLE_6:
                    u16TempID = en_str_Font_6;
                    break;
                case CAPTIONMENU_FONT_STYLE_7:
                    u16TempID = en_str_Font_7;
                    break;
            }
            break;
        case HWND_MENU_OPTION_CCOPTION_ITEM_FONTSIZE_OPTION:
            if (stGenSetting.g_CaptionSetting.u8CSOptionMode==CAPTIONMENU_OPTIONMODE_DEFAULT)
            {
                u16TempID = en_str_Default;
                break;
            }
            switch(stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSFontSize)
            {
                case CAPTIONMENU_FONT_SIZE_DEFAULT:
                    u16TempID = en_str_Default;
                    break;
                case CAPTIONMENU_FONT_SIZE_NORMAL:
                    u16TempID = en_str_Normal;
                    break;
                case CAPTIONMENU_FONT_SIZE_LARGE:
                    u16TempID = en_str_Large;
                    break;
                case CAPTIONMENU_FONT_SIZE_SMALL:
                    u16TempID = en_str_Small;
                    break;
                default:
                //
                break;
            }
            break;
        case HWND_MENU_OPTION_CCOPTION_ITEM_FONTEDGESTYLE_OPTION:
            if (stGenSetting.g_CaptionSetting.u8CSOptionMode==CAPTIONMENU_OPTIONMODE_DEFAULT)
            {
                u16TempID = en_str_Default;
                break;
            }
            switch(stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionEdgeStyle)
            {
                default:
                case CAPTIONMENU_FONT_EDGESTYLE_DEFAULT:
                    u16TempID = en_str_Default;
                    break;
                case CAPTIONMENU_FONT_EDGESTYLE_NONE:
                    u16TempID = en_str_None;
                    break;
                case CAPTIONMENU_FONT_EDGESTYLE_RAISED:
                    u16TempID = en_str_Raised;
                    break;
                case CAPTIONMENU_FONT_EDGESTYLE_DEPRESSED:
                    u16TempID = en_str_Depressed;
                    break;
                case CAPTIONMENU_FONT_EDGESTYLE_UNIFORM:
                    u16TempID = en_str_Uniform;
                    break;
                case CAPTIONMENU_FONT_EDGESTYLE_LEFTDROPSHADOW:
                    u16TempID = en_str_Left_Shadow;
                    break;
                case CAPTIONMENU_FONT_EDGESTYLE_RIGHTDROPSHADOW:
                    u16TempID = en_str_Right_Shadow;
                    break;
            }
            break;
        case HWND_MENU_OPTION_CCOPTION_ITEM_FONTEDGECOLOR_OPTION:
            if (stGenSetting.g_CaptionSetting.u8CSOptionMode==CAPTIONMENU_OPTIONMODE_DEFAULT)
            {
                u16TempID = en_str_Default;
                break;
            }
            switch(stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionEdgeColor)
            {
                default:
                case CAPTIONMENU_FONT_EDGECOLOR_DEFAULT:
                    u16TempID = en_str_Default;
                    break;
                case CAPTIONMENU_FONT_EDGECOLOR_BLACK:
                    u16TempID = en_str_Black;
                    break;
                case CAPTIONMENU_FONT_EDGECOLOR_WHITE:
                    u16TempID = en_str_White;
                    break;
                case CAPTIONMENU_FONT_EDGECOLOR_RED:
                    u16TempID = en_str_Red;
                    break;
                case CAPTIONMENU_FONT_EDGECOLOR_GREEN:
                    u16TempID = en_str_Green;
                    break;
                case CAPTIONMENU_FONT_EDGECOLOR_BLUE:
                    u16TempID = en_str_Blue;
                    break;
                case CAPTIONMENU_FONT_EDGECOLOR_YELLOW:
                    u16TempID = en_str_Yellow;
                    break;
                case CAPTIONMENU_FONT_EDGECOLOR_MAGENTA:
                    u16TempID = en_str_Magenta;
                    break;
                case CAPTIONMENU_FONT_EDGECOLOR_CYAN:
                    u16TempID = en_str_Cyan;
                    break;
            }
            break;
        case HWND_MENU_OPTION_CCOPTION_ITEM_FGCOLOR_OPTION:
            if (stGenSetting.g_CaptionSetting.u8CSOptionMode==CAPTIONMENU_OPTIONMODE_DEFAULT)
            {
                u16TempID = en_str_Default;
                break;
            }
            switch(stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionFGColor)
            {
                default:
                case CAPTIONMENU_FG_COLOR_DEFAULT:
                    u16TempID = en_str_Default;
                    break;
                case CAPTIONMENU_FG_COLOR_WHITE:
                    u16TempID = en_str_White;
                    break;
                case CAPTIONMENU_FG_COLOR_BLACK:
                    u16TempID = en_str_Black;
                    break;
                case CAPTIONMENU_FG_COLOR_RED:
                    u16TempID = en_str_Red;
                    break;
                case CAPTIONMENU_FG_COLOR_GREEN:
                    u16TempID = en_str_Green;
                    break;
                case CAPTIONMENU_FG_COLOR_BLUE:
                    u16TempID = en_str_Blue;
                    break;
                case CAPTIONMENU_FG_COLOR_YELLOW:
                    u16TempID = en_str_Yellow;
                    break;
                case CAPTIONMENU_FG_COLOR_MAGENTA:
                    u16TempID = en_str_Magenta;
                    break;
                case CAPTIONMENU_FG_COLOR_CYAN:
                    u16TempID = en_str_Cyan;
                    break;
            }
            break;
        case HWND_MENU_OPTION_CCOPTION_ITEM_BGCOLOR_OPTION:
            if (stGenSetting.g_CaptionSetting.u8CSOptionMode==CAPTIONMENU_OPTIONMODE_DEFAULT)
            {
                u16TempID = en_str_Default;
                break;
            }
            switch(stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionBGColor)
            {
                default:
                case CAPTIONMENU_BG_COLOR_DEFAULT:
                    u16TempID = en_str_Default;
                    break;
                case CAPTIONMENU_BG_COLOR_WHITE:
                    u16TempID = en_str_White;
                    break;
                case CAPTIONMENU_BG_COLOR_BLACK:
                    u16TempID = en_str_Black;
                    break;
                case CAPTIONMENU_BG_COLOR_RED:
                    u16TempID = en_str_Red;
                    break;
                case CAPTIONMENU_BG_COLOR_GREEN:
                    u16TempID = en_str_Green;
                    break;
                case CAPTIONMENU_BG_COLOR_BLUE:
                    u16TempID = en_str_Blue;
                    break;
                case CAPTIONMENU_BG_COLOR_YELLOW:
                    u16TempID = en_str_Yellow;
                    break;
                case CAPTIONMENU_BG_COLOR_MAGENTA:
                    u16TempID = en_str_Magenta;
                    break;
                case CAPTIONMENU_BG_COLOR_CYAN:
                    u16TempID = en_str_Cyan;
                    break;
            }
            break;
        case HWND_MENU_OPTION_CCOPTION_ITEM_FGOPACITY_OPTION:
            if (stGenSetting.g_CaptionSetting.u8CSOptionMode==CAPTIONMENU_OPTIONMODE_DEFAULT)
            {
                u16TempID = en_str_Default;
                break;
            }
            switch(stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionFGOpacity)
            {
                case CAPTIONMENU_FG_OPACITY_DEFAULT:
                    u16TempID = en_str_Default;
                    break;
                case CAPTIONMENU_FG_OPACITY_SOLID:
                    u16TempID = en_str_Solid;
                    break;
                case CAPTIONMENU_FG_OPACITY_FLASHING:
                    u16TempID = en_str_Flashing;
                    break;
                case CAPTIONMENU_FG_OPACITY_TRANSLUCENT:
                    u16TempID = en_str_Translucent;
                    break;
                case CAPTIONMENU_FG_OPACITY_TRANSPARENT:
                    u16TempID = en_str_Transparent;
                    break;
                default:
                    //
                    break;
            }
            break;
        case HWND_MENU_OPTION_CCOPTION_ITEM_BGOPACITY_OPTION:
            if (stGenSetting.g_CaptionSetting.u8CSOptionMode==CAPTIONMENU_OPTIONMODE_DEFAULT)
            {
                u16TempID = en_str_Default;
                break;
            }
            switch(stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionBGOpacity)
            {
                case CAPTIONMENU_BG_OPACITY_DEFAULT:
                    u16TempID = en_str_Default;
                    break;
                case CAPTIONMENU_BG_OPACITY_SOLID:
                    u16TempID = en_str_Solid;
                    break;
                case CAPTIONMENU_BG_OPACITY_FLASHING:
                    u16TempID = en_str_Flashing;
                    break;
                case CAPTIONMENU_BG_OPACITY_TRANSLUCENT:
                    u16TempID = en_str_Translucent;
                    break;
                case CAPTIONMENU_BG_OPACITY_TRANSPARENT:
                    u16TempID = en_str_Transparent;
                    break;
                default:
                    //
                    break;
            }
            break;

        case HWND_MENU_OPTION_CCOPTION_ITEM_WINDOWCOLOR_OPTION:
            if (stGenSetting.g_CaptionSetting.u8CSOptionMode==CAPTIONMENU_OPTIONMODE_DEFAULT)
            {
                u16TempID = en_str_Default;
                break;
            }
            switch(stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionWindowColor)
            {
                default:
                case CAPTIONMENU_WINDOW_COLOR_DEFAULT:
                    u16TempID = en_str_Default;
                    break;
                case CAPTIONMENU_WINDOW_COLOR_WHITE:
                    u16TempID = en_str_White;
                    break;
                case CAPTIONMENU_WINDOW_COLOR_BLACK:
                    u16TempID = en_str_Black;
                    break;
                case CAPTIONMENU_WINDOW_COLOR_RED:
                    u16TempID = en_str_Red;
                    break;
                case CAPTIONMENU_WINDOW_COLOR_GREEN:
                    u16TempID = en_str_Green;
                    break;
                case CAPTIONMENU_WINDOW_COLOR_BLUE:
                    u16TempID = en_str_Blue;
                    break;
                case CAPTIONMENU_WINDOW_COLOR_YELLOW:
                    u16TempID = en_str_Yellow;
                    break;
                case CAPTIONMENU_WINDOW_COLOR_MAGENTA:
                    u16TempID = en_str_Magenta;
                    break;
                case CAPTIONMENU_WINDOW_COLOR_CYAN:
                    u16TempID = en_str_Cyan;
                    break;
            }
            break;
        case HWND_MENU_OPTION_CCOPTION_ITEM_WINDOWOPACITY_OPTION:
            if (stGenSetting.g_CaptionSetting.u8CSOptionMode==CAPTIONMENU_OPTIONMODE_DEFAULT)
            {
                u16TempID = en_str_Default;
                break;
            }
            switch(stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionWindowOpacity)
            {
                case CAPTIONMENU_WINDOW_OPACITY_DEFAULT:
                    u16TempID = en_str_Default;
                    break;
                case CAPTIONMENU_WINDOW_OPACITY_SOLID:
                    u16TempID = en_str_Solid;
                    break;
                case CAPTIONMENU_WINDOW_OPACITY_FLASHING:
                    u16TempID = en_str_Flashing;
                    break;
                case CAPTIONMENU_WINDOW_OPACITY_TRANSLUCENT:
                    u16TempID = en_str_Translucent;
                    break;
                case CAPTIONMENU_WINDOW_OPACITY_TRANSPARENT:
                    u16TempID = en_str_Transparent;
                    break;
                default:
                //
                break;
            }
            break;
        #if ENABLE_ATSC_MENU_LOCK_UI
        case HWND_MENU_LOCK_VCHIPSUBPAGE_TITLE:
            if(g_vchipPageType == EN_VCHIP_MPAA)
            {
                u16TempID = en_str_MPAA;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAENG)
            {
                u16TempID = en_str_Canada_Eng;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAFRE)
            {
                u16TempID = en_str_Canada_Fre;
            }
            break;

        case HWND_MENU_LOCK_INPUTBLOCKSUBPAGE_ITEM_TV_OPTION:
            if (stGenSetting.g_VChipSetting.u8InputBlockItem & INPUT_BLOCK_TV)
                u16TempID = en_str_Block;
            else
                u16TempID = en_str_UnBlock;
            break;
        case HWND_MENU_LOCK_INPUTBLOCKSUBPAGE_ITEM_AV_OPTION:
            if (stGenSetting.g_VChipSetting.u8InputBlockItem & INPUT_BLOCK_AV)
                u16TempID = en_str_Block;
            else
                u16TempID = en_str_UnBlock;
            break;
        case HWND_MENU_LOCK_INPUTBLOCKSUBPAGE_ITEM_SVIDEO_OPTION:
            if (stGenSetting.g_VChipSetting.u8InputBlockItem & INPUT_BLOCK_SV)
                u16TempID = en_str_Block;
            else
                u16TempID = en_str_UnBlock;
            break;
        case HWND_MENU_LOCK_INPUTBLOCKSUBPAGE_ITEM_COMPONENT_OPTION:
            if (stGenSetting.g_VChipSetting.u8InputBlockItem & INPUT_BLOCK_YPBPR)
                u16TempID = en_str_Block;
            else
                u16TempID = en_str_UnBlock;
            break;
        case HWND_MENU_LOCK_INPUTBLOCKSUBPAGE_ITEM_HDMI_OPTION:
            if (stGenSetting.g_VChipSetting.u8InputBlockItem & INPUT_BLOCK_HDMI)
                u16TempID = en_str_Block;
            else
                u16TempID = en_str_UnBlock;
            break;
        case HWND_MENU_LOCK_INPUTBLOCKSUBPAGE_ITEM_PC_OPTION:
            if (stGenSetting.g_VChipSetting.u8InputBlockItem & INPUT_BLOCK_PC)
                u16TempID = en_str_Block;
            else
                u16TempID = en_str_UnBlock;
            break;
        case HWND_MENU_LOCK_VCHIPSUBPAGE_ITEM1_TEXT:
            if(g_vchipPageType == EN_VCHIP_MPAA)
            {
                u16TempID = en_str_G;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAENG)
            {
                u16TempID = en_str_C;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAFRE)
            {
                u16TempID = en_str_G;
            }
            break;
        case HWND_MENU_LOCK_VCHIPSUBPAGE_ITEM2_TEXT:
            if(g_vchipPageType == EN_VCHIP_MPAA)
            {
                u16TempID = en_str_PG;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAENG)
            {
                u16TempID = en_str_C8plus;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAFRE)
            {
                u16TempID = en_str_8ansplus;
            }
            break;
        case HWND_MENU_LOCK_VCHIPSUBPAGE_ITEM3_TEXT:
            if(g_vchipPageType == EN_VCHIP_MPAA)
            {
                u16TempID = en_str_PGdash13;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAENG)
            {
                u16TempID = en_str_G;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAFRE)
            {
                u16TempID = en_str_13ansplus;
            }
            break;
        case HWND_MENU_LOCK_VCHIPSUBPAGE_ITEM4_TEXT:
            if(g_vchipPageType == EN_VCHIP_MPAA)
            {
                u16TempID = en_str_R;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAENG)
            {
                u16TempID = en_str_PG;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAFRE)
            {
                u16TempID = en_str_16ansplus;
            }
            break;
        case HWND_MENU_LOCK_VCHIPSUBPAGE_ITEM5_TEXT:
            if(g_vchipPageType == EN_VCHIP_MPAA)
            {
                u16TempID = en_str_NCdash17;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAENG)
            {
                u16TempID = en_str_14plus;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAFRE)
            {
                u16TempID = en_str_18ansplus;
            }
            break;
        case HWND_MENU_LOCK_VCHIPSUBPAGE_ITEM6_TEXT:
            if(g_vchipPageType == EN_VCHIP_MPAA)
            {
                u16TempID = en_str_X;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAENG)
            {
                u16TempID = en_str_18plus;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAFRE)
            {
                u16TempID = en_str_EXEMPT;
            }
            break;
        case HWND_MENU_LOCK_VCHIPSUBPAGE_ITEM7_TEXT:
            if(g_vchipPageType == EN_VCHIP_MPAA)
            {
                u16TempID = en_str_NshashR;
            }
            break;

        case HWND_MENU_LOCK_VCHIPSUBPAGE_ITEM1_OPTION:
            if(g_vchipPageType == EN_VCHIP_MPAA)
            {
                if(stGenSetting.g_VChipSetting.u8VChipMPAAItem & VCHIP_MPAARATING_G)
                    u16TempID = en_str_LOCK;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAENG)
            {
                if(stGenSetting.g_VChipSetting.u8VChipCEItem == VCHIP_ENGRATING_C)
                    u16TempID = en_str_LOCK;
            }
            else
            {
                if(stGenSetting.g_VChipSetting.u8VChipCFItem == VCHIP_FRERATING_G)
                    u16TempID = en_str_LOCK;
            }
            break;
        case HWND_MENU_LOCK_VCHIPSUBPAGE_ITEM2_OPTION:
            if(g_vchipPageType == EN_VCHIP_MPAA)
            {
                if(stGenSetting.g_VChipSetting.u8VChipMPAAItem & VCHIP_MPAARATING_PG)
                    u16TempID = en_str_LOCK;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAENG)
            {
                if((stGenSetting.g_VChipSetting.u8VChipCEItem >=VCHIP_ENGRATING_C) && (stGenSetting.g_VChipSetting.u8VChipCEItem <=VCHIP_ENGRATING_C8Plus))
                    u16TempID = en_str_LOCK;
            }
            else
            {
                if((stGenSetting.g_VChipSetting.u8VChipCFItem >=VCHIP_FRERATING_G) && (stGenSetting.g_VChipSetting.u8VChipCFItem <=VCHIP_FRERATING_8ansPlus))
                   u16TempID = en_str_LOCK;
            }
            break;
        case HWND_MENU_LOCK_VCHIPSUBPAGE_ITEM3_OPTION:
            if(g_vchipPageType == EN_VCHIP_MPAA)
            {
                if(stGenSetting.g_VChipSetting.u8VChipMPAAItem & VCHIP_MPAARATING_PG_13)
                    u16TempID = en_str_LOCK;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAENG)
            {
                if((stGenSetting.g_VChipSetting.u8VChipCEItem >=VCHIP_ENGRATING_C) && (stGenSetting.g_VChipSetting.u8VChipCEItem <=VCHIP_ENGRATING_G))
                    u16TempID = en_str_LOCK;
            }
            else
            {
                if((stGenSetting.g_VChipSetting.u8VChipCFItem >=VCHIP_FRERATING_G) && (stGenSetting.g_VChipSetting.u8VChipCFItem <=VCHIP_FRERATING_13ansPlus))
                   u16TempID = en_str_LOCK;
            }
            break;
        case HWND_MENU_LOCK_VCHIPSUBPAGE_ITEM4_OPTION:
            if(g_vchipPageType == EN_VCHIP_MPAA)
            {
                if(stGenSetting.g_VChipSetting.u8VChipMPAAItem & VCHIP_MPAARATING_R)
                    u16TempID = en_str_LOCK;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAENG)
            {
                if((stGenSetting.g_VChipSetting.u8VChipCEItem >=VCHIP_ENGRATING_C) && (stGenSetting.g_VChipSetting.u8VChipCEItem <=VCHIP_ENGRATING_PG))
                    u16TempID = en_str_LOCK;
            }
            else
            {
                if((stGenSetting.g_VChipSetting.u8VChipCFItem >=VCHIP_FRERATING_G) && (stGenSetting.g_VChipSetting.u8VChipCFItem <=VCHIP_FRERATING_16ansPlus))
                   u16TempID = en_str_LOCK;
            }
            break;
        case HWND_MENU_LOCK_VCHIPSUBPAGE_ITEM5_OPTION:
            if(g_vchipPageType == EN_VCHIP_MPAA)
            {
                if(stGenSetting.g_VChipSetting.u8VChipMPAAItem & VCHIP_MPAARATING_NC_17)
                    u16TempID = en_str_LOCK;
            }
            else if(g_vchipPageType == EN_VCHIP_CANADAENG)
            {
                if((stGenSetting.g_VChipSetting.u8VChipCEItem >=VCHIP_ENGRATING_C) && (stGenSetting.g_VChipSetting.u8VChipCEItem <=VCHIP_ENGRATING_14Plus))
                    u16TempID = en_str_LOCK;
            }
            else
            {
                if((stGenSetting.g_VChipSetting.u8VChipCFItem >=VCHIP_FRERATING_G) && (stGenSetting.g_VChipSetting.u8VChipCFItem <=VCHIP_FRERATING_18ansPlus))
                   u16TempID = en_str_LOCK;
            }
            break;
        case HWND_MENU_LOCK_VCHIPSUBPAGE_ITEM6_OPTION:
            if(g_vchipPageType == EN_VCHIP_MPAA)
            {
                if(stGenSetting.g_VChipSetting.u8VChipMPAAItem & VCHIP_MPAARATING_X)
                    u16TempID = en_str_LOCK;
            }
            else
            {
                if((stGenSetting.g_VChipSetting.u8VChipCEItem >=VCHIP_ENGRATING_C) && (stGenSetting.g_VChipSetting.u8VChipCEItem <=VCHIP_ENGRATING_18Plus))
                    u16TempID = en_str_LOCK;
            }

            break;
        case HWND_MENU_LOCK_VCHIPSUBPAGE_ITEM7_OPTION:
            if(stGenSetting.g_VChipSetting.u8VChipMPAAItem & VCHIP_MPAARATING_NOT_RATED)
                u16TempID = en_str_LOCK;
            break;

        case HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM0_TEXT:
        case HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM1_TEXT:
        case HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM2_TEXT:
        case HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM3_TEXT:
        case HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM4_TEXT:
        case HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM5_TEXT:
        case HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM6_TEXT:
        case HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM7_TEXT:
        case HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM8_TEXT:
        case HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM9_TEXT:
            {
                U8 u8TextItemIdx=0;
                for(u8TextItemIdx=0; u8TextItemIdx< MAX_NUM_OF_DIM_ITEM; u8TextItemIdx++)
                {
                    if(hwnd==_RRTDimensionTextHwndList[u8TextItemIdx])
                    {
                        break;
                    }
                }
                if((g_u8CurrentRRT_1stDimension_Item+u8TextItemIdx+1) > TOTAL_DIM_ITEM_NUM)
                {
                    u16TempID = Empty;
                }
                else
                {
                    stGenSettingVchipRegion5.stRegin5Dimension[g_u8CurrentRRT_1stDimension_Item+u8TextItemIdx].u8DimensionName[REGION5_DIMENSIONNAME_MAX_LENGTH-1]='\0';
                    u16Value = strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[g_u8CurrentRRT_1stDimension_Item+u8TextItemIdx].u8DimensionName));

                    if(u16Value>=REGION5_DIMENSIONNAME_MAX_LENGTH)
                    {
                        u16Value=0;
                    }

                    if(u16Value == 0)
                    {
                        memcpy((char *)(&stGenSettingVchipRegion5.stRegin5Dimension[g_u8CurrentRRT_1stDimension_Item+u8TextItemIdx].u8DimensionName), (char *)(gStrRRTDefaultName[0]), 13);
                        stGenSettingVchipRegion5.stRegin5Dimension[g_u8CurrentRRT_1stDimension_Item+u8TextItemIdx].u8DimensionName[10]+= ((g_u8CurrentRRT_1stDimension_Item+u8TextItemIdx)/10);
                        stGenSettingVchipRegion5.stRegin5Dimension[g_u8CurrentRRT_1stDimension_Item+u8TextItemIdx].u8DimensionName[11]+=((g_u8CurrentRRT_1stDimension_Item+u8TextItemIdx)%10);
                        stGenSettingVchipRegion5.stRegin5Dimension[g_u8CurrentRRT_1stDimension_Item+u8TextItemIdx].u8DimensionName[12]= '\0';
                        u16Value = 13;
                        if((g_u8CurrentRRT_1stDimension_Item+u8TextItemIdx)<10)
                        {
                            stGenSettingVchipRegion5.stRegin5Dimension[g_u8CurrentRRT_1stDimension_Item+u8TextItemIdx].u8DimensionName[10] = stGenSettingVchipRegion5.stRegin5Dimension[g_u8CurrentRRT_1stDimension_Item+u8TextItemIdx].u8DimensionName[11];
                            stGenSettingVchipRegion5.stRegin5Dimension[g_u8CurrentRRT_1stDimension_Item+u8TextItemIdx].u8DimensionName[11] = '0';
                            u16Value = 12;
                        }
                    }
                    return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, stGenSettingVchipRegion5.stRegin5Dimension[g_u8CurrentRRT_1stDimension_Item+u8TextItemIdx].u8DimensionName, u16Value);
                }
            }
            break;

        case HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM0_TEXT:
        case HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM1_TEXT:
        case HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM2_TEXT:
        case HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM3_TEXT:
        case HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM4_TEXT:
        case HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM5_TEXT:
        case HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM6_TEXT:
        case HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM7_TEXT:
        case HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM8_TEXT:
        case HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM9_TEXT:
            #if 0
            u16TempID = g_u8CurrentRRT_Option / MAX_NUM_OF_RRT_ITEM * MAX_NUM_OF_RRT_ITEM;
            u16TempID += _MApp_ZUI_ACT_RRTAdjustWindowMapToIndex(hwnd);
            stGenSetting.g_VchipRegion5.stRegin5Dimension[g_u8CurrentRRT_Dimension].stRatingText[u16TempID][REGION5_RATING_TEXT_MAX_LENGTH-1]='\0';
            u16Value = strlen((char *)(stGenSetting.g_VchipRegion5.stRegin5Dimension[g_u8CurrentRRT_Dimension].stRatingText[u16TempID]));
            return  MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, stGenSetting.g_VchipRegion5.stRegin5Dimension[g_u8CurrentRRT_Dimension].stRatingText[u16TempID], u16Value);
            #else
                {
                    U8 u8TextItemIdx=0;
                    //printf("g_u8CurrentRRT_1stOption = %d\n", g_u8CurrentRRT_1stOption);
                    for(u8TextItemIdx=0; u8TextItemIdx<MAX_NUM_OF_RRT_ITEM; u8TextItemIdx++)
                    {
                       if(hwnd==_MenuRRTAdjPageTextHwndList[u8TextItemIdx])
                        {
                            break;
                        }
                    }
                    if(g_u8CurrentRRT_1stOption+u8TextItemIdx==0)  // First page first item
                    {
                        u16TempID = en_str_ALL;
                    }
                    else if(g_u8CurrentRRT_1stOption+u8TextItemIdx+1>RRT_ITEM_NUM_IN_CUR_DIM)
                    {
                        u16TempID = Empty;
                    }
                    else
                    {
                        stGenSettingVchipRegion5.stRegin5Dimension[g_u8CurrentRRT_Dimension].stRatingText[g_u8CurrentRRT_1stOption+u8TextItemIdx-1][REGION5_RATING_TEXT_MAX_LENGTH-1]='\0';
                        u16Value = strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[g_u8CurrentRRT_Dimension].stRatingText[g_u8CurrentRRT_1stOption+u8TextItemIdx-1]));
                        if(u16Value>=REGION5_RATING_TEXT_MAX_LENGTH)
                        {
                            u16Value=0;
                        }
                        if(u16Value == 0)
                        {
                            memcpy((char *)(&stGenSettingVchipRegion5.stRegin5Dimension[g_u8CurrentRRT_Dimension].stRatingText[g_u8CurrentRRT_1stOption+u8TextItemIdx-1]), (char *)(gStrRRTDefaultName[1]), 9);
                            stGenSettingVchipRegion5.stRegin5Dimension[g_u8CurrentRRT_Dimension].stRatingText[g_u8CurrentRRT_1stOption+u8TextItemIdx-1][6]+=((g_u8CurrentRRT_1stOption+u8TextItemIdx)/10);
                            stGenSettingVchipRegion5.stRegin5Dimension[g_u8CurrentRRT_Dimension].stRatingText[g_u8CurrentRRT_1stOption+u8TextItemIdx-1][7]+=((g_u8CurrentRRT_1stOption+u8TextItemIdx)%10);
                            stGenSettingVchipRegion5.stRegin5Dimension[g_u8CurrentRRT_Dimension].stRatingText[g_u8CurrentRRT_1stOption+u8TextItemIdx-1][8]= '\0';
                            u16Value = 9;
                            if(g_u8CurrentRRT_Option<10)
                            {
                                stGenSettingVchipRegion5.stRegin5Dimension[g_u8CurrentRRT_Dimension].stRatingText[g_u8CurrentRRT_1stOption+u8TextItemIdx-1][6] = stGenSettingVchipRegion5.stRegin5Dimension[g_u8CurrentRRT_Dimension].stRatingText[g_u8CurrentRRT_1stOption+u8TextItemIdx-1][7];
                                stGenSettingVchipRegion5.stRegin5Dimension[g_u8CurrentRRT_Dimension].stRatingText[g_u8CurrentRRT_1stOption+u8TextItemIdx-1][7] = '\0';
                                u16Value = 8;
                            }
                        }
                        return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, stGenSettingVchipRegion5.stRegin5Dimension[g_u8CurrentRRT_Dimension].stRatingText[g_u8CurrentRRT_1stOption+u8TextItemIdx-1], u16Value);
                    }
            }

            break;
            #endif
        case HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM0_OPTION:
        case HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM1_OPTION:
        case HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM2_OPTION:
        case HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM3_OPTION:
        case HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM4_OPTION:
        case HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM5_OPTION:
        case HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM6_OPTION:
        case HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM7_OPTION:
        case HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM8_OPTION:
        case HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM9_OPTION:
        {
            U8 u8OptionItemIdx=0;
            for(u8OptionItemIdx=0; u8OptionItemIdx<MAX_NUM_OF_CHL_ITEM; u8OptionItemIdx++)
            {
                if(hwnd==_MenuRRTAdjPageOptionHwndList[u8OptionItemIdx])
                {
                    break;
                }
            }
            if(g_u8CurrentRRT_1stOption+u8OptionItemIdx==0)
            {
                // ALL
                if(MApp_ZUI_ACT_MainMenuCurDimRRTIsAllRating(g_u8CurrentRRT_Dimension) == TRUE)
                {
                    u16TempID = en_str_On;
                }
                else
                {
                    u16TempID = en_str_Off;
                }
            }
            else if(g_u8CurrentRRT_1stOption+u8OptionItemIdx+1>RRT_ITEM_NUM_IN_CUR_DIM)
            {
                u16TempID = en_str_Off;
            }
            else
            {
                U16 u16Temp;
                u16Temp = 0x01 << (g_u8CurrentRRT_1stOption+u8OptionItemIdx-1);
                if (stGenSettingVchipRegion5.stRegin5Dimension[g_u8CurrentRRT_Dimension].u32CurrentOption & u16Temp)
                {
                    u16TempID = en_str_On;
                }
                else
                {
                    u16TempID = en_str_Off;
                }
            }
        }
            break;
        case HWND_MENU_LOCK_MAINSUBPAGE_ITEM_UNRATED_OPTION:
            if (stGenSetting.g_VChipSetting.u8UnRatedLock==0)
                u16TempID = en_str_Off;
            else
                u16TempID = en_str_On;
            break;
        #endif
          case HWND_MENU_CHANNEL_LIST_BG_SELECTION:

            if(bChannelListType == 0)//favorite list
            {
                u16TempID = en_str_Favorite;
            }
            else
            {
               u16TempID = en_str_ShowslashHide;
            }
#if (ENABLE_ATSC_TTS)
            MApp_TTSControlSetInputText(MApp_ZUI_API_GetString(u16TempID), MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetString(u16TempID)));
            MApp_TTSControlSetOn(TRUE);
#endif
            break;
        case HWND_MENU_CHANNEL_LIST_ITEM0_CHANNELNO:
        case HWND_MENU_CHANNEL_LIST_ITEM1_CHANNELNO:
        case HWND_MENU_CHANNEL_LIST_ITEM2_CHANNELNO:
        case HWND_MENU_CHANNEL_LIST_ITEM3_CHANNELNO:
        case HWND_MENU_CHANNEL_LIST_ITEM4_CHANNELNO:
        case HWND_MENU_CHANNEL_LIST_ITEM5_CHANNELNO:
        case HWND_MENU_CHANNEL_LIST_ITEM6_CHANNELNO:
        case HWND_MENU_CHANNEL_LIST_ITEM7_CHANNELNO:
        case HWND_MENU_CHANNEL_LIST_ITEM8_CHANNELNO:
        case HWND_MENU_CHANNEL_LIST_ITEM9_CHANNELNO:
            u16Value = MApp_ChanProc_GetCurProgIndex();
            u16Value = MApp_ChanProc_CalculateCurPageBaseIdx( u16Value, MAX_NUM_OF_SRV_ITEM );
            u16Value += _MApp_ZUI_ACT_MenuChannelListWindowMapToIndex(hwnd);
            MApp_UiMenuFunc_ConvertProgramNumber2Str(&MApp_ChanProc_GetChannelPointer(VIR_CH_IDX(u16Value))->stVirtualChNum, au8Section);
            MApp_ChanProc_RefreshChannelBuffer(MAIN_LIST);
            return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, au8Section, strlen((char *)au8Section));

        case HWND_MENU_CHANNEL_LIST_ITEM0_CHANNELNAME:
        case HWND_MENU_CHANNEL_LIST_ITEM1_CHANNELNAME:
        case HWND_MENU_CHANNEL_LIST_ITEM2_CHANNELNAME:
        case HWND_MENU_CHANNEL_LIST_ITEM3_CHANNELNAME:
        case HWND_MENU_CHANNEL_LIST_ITEM4_CHANNELNAME:
        case HWND_MENU_CHANNEL_LIST_ITEM5_CHANNELNAME:
        case HWND_MENU_CHANNEL_LIST_ITEM6_CHANNELNAME:
        case HWND_MENU_CHANNEL_LIST_ITEM7_CHANNELNAME:
        case HWND_MENU_CHANNEL_LIST_ITEM8_CHANNELNAME:
        case HWND_MENU_CHANNEL_LIST_ITEM9_CHANNELNAME:
            u16Value = MApp_ChanProc_GetCurProgIndex();
            u16Value = MApp_ChanProc_CalculateCurPageBaseIdx( u16Value, MAX_NUM_OF_SRV_ITEM );
            u16Value += _MApp_ZUI_ACT_MenuChannelListWindowMapToIndex(hwnd);
            pu8String = MApp_ChanProc_GetChannelPointer(VIR_CH_IDX(u16Value))->acServiceName;
            //MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, pu8String, strlen((char *)pu8String));
            MApp_ZUI_API_StringBufferUTF16toU16(CHAR_BUFFER, pu8String, MAX_LENGTH_OF_SERVICE_NAME/2+1);
            MApp_ChanProc_RefreshChannelBuffer(MAIN_LIST);
            return CHAR_BUFFER;

        case HWND_MENU_CHANNEL_CHANNEL_NO_OPTION:
            #if ATSC_READY
               if(IsDTVInUse() || IsATVInUse())
                {
                    if ( (stChSetting.u16MainListSrvNum != 0)&&(stChSetting.u16MainListSrvNum-stChSetting.u16TotalHideSrvNum>0) )
                    {
                        MApp_UiMenuFunc_ConvertProgramNumber2Str(&MApp_ChanProc_GetChannelPointer(VIR_CH_IDX(MApp_ChanProc_GetCurProgIndex()))->stVirtualChNum, au8Section);
                        return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, au8Section, strlen((char *)au8Section));
                    }
                    else
                    {
                        return 0;
                    }
                }
            #else
                u16TempID = Empty;
            #endif
                break;
        case HWND_MENU_CHANNEL_CHANNEL_LABEL_OPTION:
            #if ATSC_READY
            if(IsDTVInUse() || IsATVInUse())
            {
                if ( (stChSetting.u16MainListSrvNum != 0)&&(stChSetting.u16MainListSrvNum-stChSetting.u16TotalHideSrvNum>0) )
                {
                    pu8String = MApp_ChanProc_GetChannelPointer(VIR_CH_IDX(MApp_ChanProc_GetCurProgIndex()))->acServiceName;
                    return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, pu8String, strlen((char *)pu8String));
                }
                else
                {
                    return 0;
                }
            }
            #else
                u16TempID = Empty;
            #endif
            break;
        case HWND_MENU_CHANNEL_LABEL_EDIT_CHAR1_TEXT:
            #if ATSC_READY
            Au8String = MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, &u8ChannelLabel[0], 1);
            Au8String[1] = 0;
            return Au8String;
            #else
            u16TempID = Empty;
            break;
            #endif
        case HWND_MENU_CHANNEL_LABEL_EDIT_CHAR2_TEXT:
            #if ATSC_READY
            Au8String = MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, &u8ChannelLabel[1], 1);
            Au8String[1] = 0;
            return Au8String;
            #else
            u16TempID = Empty;
            break;
            #endif

        case HWND_MENU_CHANNEL_LABEL_EDIT_CHAR3_TEXT:
            #if ATSC_READY
            Au8String = MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, &u8ChannelLabel[2], 1);
            Au8String[1] = 0;
            return Au8String;
            #else
            u16TempID = Empty;
            break;
            #endif

        case HWND_MENU_CHANNEL_LABEL_EDIT_CHAR4_TEXT:
            #if ATSC_READY
            Au8String = MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, &u8ChannelLabel[3], 1);
            Au8String[1] = 0;
            return Au8String;
            #else
            u16TempID = Empty;
            break;
            #endif

        case HWND_MENU_CHANNEL_LABEL_EDIT_CHAR5_TEXT:
            #if ATSC_READY
            Au8String = MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, &u8ChannelLabel[4], 1);
            Au8String[1] = 0;
            return Au8String;
            #else
            u16TempID = Empty;
            break;
            #endif

        case HWND_MENU_CHANNEL_LABEL_EDIT_CHAR6_TEXT:
            #if ATSC_READY
            Au8String = MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, &u8ChannelLabel[5], 1);
            Au8String[1] = 0;
            return Au8String;
            #else
            u16TempID = Empty;
            break;
            #endif

        case HWND_MENU_CHANNEL_LABEL_EDIT_CHAR7_TEXT:
            #if ATSC_READY
            Au8String = MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, &u8ChannelLabel[6], 1);
            Au8String[1] = 0;
            return Au8String;
            #else
            u16TempID = Empty;
            break;
            #endif
        case HWND_MENU_CHANNEL_NON_TV_TEXT:
        {
            #if ATSC_READY
            MApp_UiMenuFunc_InputLabel_Init(stGenSetting.g_SysSetting.enUIInputSourceType);
            switch (MApp_UiMenuFunc_InputLabel_GetPresentType())
            {
                case InputLabel_Default:
                    switch(stGenSetting.g_SysSetting.enUIInputSourceType)
                    {
                        case UI_INPUT_SOURCE_TV:
                        u16TempID = en_str_TV;
                        break;
                        #if (INPUT_AV_VIDEO_COUNT>=1)
                        case UI_INPUT_SOURCE_AV:
                        u16TempID = en_str_AV;
                        break;
                        #endif
                        #if (INPUT_AV_VIDEO_COUNT>=2)
                        case UI_INPUT_SOURCE_AV2:
                        u16TempID = en_str_AV_2;
                        break;
                        #endif
                        #if (INPUT_SV_VIDEO_COUNT>=1)
                        case UI_INPUT_SOURCE_SVIDEO:
                        u16TempID = en_str_SdashVideo;
                        break;
                        #endif
                        #if (INPUT_SV_VIDEO_COUNT>=2)
                        case UI_INPUT_SOURCE_SVIDEO2:
                        u16TempID = en_str_SdashVideo_2;
                        break;
                        #endif
                        #if (INPUT_HDMI_VIDEO_COUNT>=1)
                        case UI_INPUT_SOURCE_HDMI:
                        u16TempID = en_str_HDMI1;
                        break;
                        #endif
                        #if (INPUT_HDMI_VIDEO_COUNT>=2)
                        case UI_INPUT_SOURCE_HDMI2:
                        u16TempID = en_str_HDMI2;
                        break;
                        #endif
                        #if (INPUT_HDMI_VIDEO_COUNT>=3)
                        case UI_INPUT_SOURCE_HDMI3:
                        u16TempID = en_str_HDMI3;
                        break;
                        #endif
                        #if (INPUT_HDMI_VIDEO_COUNT>=4)
                        case UI_INPUT_SOURCE_HDMI4:
                        u16TempID = en_str_HDMI4;
                        break;
                        #endif

                        case UI_INPUT_SOURCE_DTV:
                        u16TempID = en_str_DTV;
                        break;
                #if ENABLE_DMP
                        case UI_INPUT_SOURCE_DMP:
                        u16TempID = en_str_DMP;
                        break;
                      #if( ENABLE_DMP_SWITCH )
                        case UI_INPUT_SOURCE_DMP1:
                        u16TempID = en_str_USB1;
                        break;
                        case UI_INPUT_SOURCE_DMP2:
                        u16TempID = en_str_USB2;
                        break;
                          #endif
                #endif
                        #if (INPUT_YPBPR_VIDEO_COUNT>=1)
                        case UI_INPUT_SOURCE_COMPONENT:
                        u16TempID = en_str_Component1;
                        break;
                        #endif
                        #if (INPUT_YPBPR_VIDEO_COUNT>=2)
                        case UI_INPUT_SOURCE_COMPONENT2:
                        u16TempID = en_str_Component2;
                        break;
                        #endif
                        #if (INPUT_YPBPR_VIDEO_COUNT>=3)
                        case UI_INPUT_SOURCE_COMPONENT3:
                        u16TempID = en_str_DVD;
                        break;
                        #endif
                        case UI_INPUT_SOURCE_RGB:
                        u16TempID = en_str_PC;
                        break;
                        default:
                            u16TempID = en_str_StarSign; //for debug
                            break;
                    }
                break;
                    #if EN_INPUT_LABEL_CUSTOM_EDIT
                        case InputLabel_Custom:
                        {
                            U8 CustomLabel[MAX_INPUTLLABEL_CHAR_NUM+1];
                            MApp_UiMenuFunc_InputLabel_GetCustomLabel(CustomLabel);
                            return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, CustomLabel, strlen((S8 *)CustomLabel));
                        }
                            #endif
                            default:
                            u16TempID = PresentStrTab[MApp_UiMenuFunc_InputLabel_GetPresentType()];
                            break;
                        }
            #endif//ATSC_READY
            }//case HWND_MENU_CHANNEL_NON_TV_TEXT
            break;

        case HWND_MENU_PICTURE_ADJUST_BACKLIGHT_SUB_OPTION:
            #if ATSC_READY
            u16Value = MApp_UiMenuFunc_GetPictureBacklightValue();
            return _MApp_ZUI_ACT_CombineTextAndOption(hwnd, u16Value);
            #endif
            break;

        case HWND_MENU_PICTURE_DLC_OPTION:
            #if ATSC_READY
            if(MApp_UiMenuFunc_GetDLCValue() == TRUE)
            {
                u16TempID = en_str_On;
            }
            else
            {
                u16TempID = en_str_Off;
            }
            #endif
            break;

        case HWND_MENU_SOUND_EQUALIZER_OPTION:
            switch(stGenSetting.g_SoundSetting.SoundMode)
            {
                case SOUND_MODE_STANDARD:
                    u16TempID = en_str_Standard;
                    break;
                case SOUND_MODE_MUSIC:
                    u16TempID = en_str_Music;
                    break;
                case SOUND_MODE_MOVIE:
                    u16TempID = en_str_Movie;
                    break;
                case SOUND_MODE_SPORTS:
                    u16TempID = en_str_Sports;
                    break;
                case SOUND_MODE_USER:
                    u16TempID = en_str_Personal;
                    break;
                default:
                    break;
            }
            break;
		
        case HWND_MENU_SOUND_EQ_EQUALIZER_OPTION:
            switch(stGenSetting.g_SoundSetting.SoundMode)
            {
                case SOUND_MODE_STANDARD:
                    u16TempID = en_str_Standard;
                    break;
                case SOUND_MODE_MUSIC:
                    u16TempID = en_str_Music;
                    break;
                case SOUND_MODE_MOVIE:
                    u16TempID = en_str_Movie;
                    break;
                case SOUND_MODE_SPORTS:
                    u16TempID = en_str_Sports;
                    break;
                case SOUND_MODE_USER:
                    u16TempID = en_str_Personal;
                    break;
                default:
                    break;
            }
            break;

        case HWND_MENU_SOUND_EQ_ADVANCE_150HZ_VALUE:
            return _MApp_ZUI_ACT_CombineTextAndOption(hwnd);

        case HWND_MENU_SOUND_EQ_ADVANCE_500HZ_VALUE:
            return _MApp_ZUI_ACT_CombineTextAndOption(hwnd);

        case HWND_MENU_SOUND_EQ_ADVANCE_1000HZ_VALUE:
            return _MApp_ZUI_ACT_CombineTextAndOption(hwnd);

        case HWND_MENU_SOUND_EQ_ADVANCE_2000HZ_VALUE:
            return _MApp_ZUI_ACT_CombineTextAndOption(hwnd);

        case HWND_MENU_SOUND_EQ_ADVANCE_4000HZ_VALUE:
            return _MApp_ZUI_ACT_CombineTextAndOption(hwnd);

        case HWND_MENU_SOUND_EQ_ADVANCE_BALANCE_VALUE:
            return _MApp_ZUI_ACT_CombineTextAndOption(hwnd);

        case HWND_MENU_SOUND_MTS_OPTION:
            if(IsATVInUse() || IsAtscInUse())
            {
                switch(stGenSetting.g_SoundSetting.Mts)
                {
                    case SOUND_MTS_MONO:
                        u16TempID = en_str_Mono;
                        break;
                    case SOUND_MTS_STEREO:
                        u16TempID = en_str_Stereo;
                        break;
                    case SOUND_MTS_SAP:
                        u16TempID = en_str_SAP;
                        break;
                    default:
                        break;
                }
            }
            break;

#if 0
        case HWND_MENU_SOUND_DIGITAL_AUDIO_SELECTION_TEXT_OPTION:
            if (IsAtscInUse())
            {
                if ( stGenSetting.g_SoundSetting.enSoundDigitalSelect == SOUND_AUDIO_DIGITAL_DEFAULT)
                    u16TempID = en_str_Default;
                else
                    u16TempID = en_str_Auto;
            }
            else
                u16TempID = Empty;
            break;

        case HWND_MENU_SOUND_AUDIO_OPTION_OPTION:
            if ( IsAtscInUse())
            {
                u16TempID = en_str_Accessibility;
            }
            else
                u16TempID = Empty;
            break;
#endif

    #if( ENABLE_ATSC_VIDEO_DESC )
        case HWND_MENU_SOUND_VIDEO_DESCRIPTION_TEXT_OPTION:
            if ( IsAtscInUse())
            {
                switch(stGenSetting.g_SoundSetting.enVideoDescription)
                {
                    case EN_VIDEO_DESCRIPTION_ITEM_ON:
                        u16TempID = en_str_On;
                        break;

                    case EN_VIDEO_DESCRIPTION_ITEM_OFF:
                        u16TempID = en_str_Off;
                        break;

                    default:
                        break;
                }

            }
            else
            {
                u16TempID = Empty;
            }
            break;
    #endif

        case HWND_MENU_SOUND_AUDIO_LANGUAGE_OPTION:
            if ( IsAtscInUse())
            {
                if ( stGenSetting.g_SoundSetting.enSoundAudioLan == SOUND_AUDIO_LAN_ENGLISH)
                    u16TempID = en_str_English;
                else if(stGenSetting.g_SoundSetting.enSoundAudioLan == SOUND_AUDIO_LAN_SPANISH)
                    u16TempID = en_str_Spanish;
                else
                    u16TempID = en_str_French;
            }
            else
                u16TempID = Empty;
            break;

        case HWND_MENU_SOUND_AUDIO_OPTION_ACCESSIBILITY_VALUE_2:
            if ( IsAtscInUse())
            {
                if ( stGenSetting.g_SoundSetting.enAccessibility == SOUND_MAIN_AUDIO)
                    u16TempID = en_str_CM;
                else if(stGenSetting.g_SoundSetting.enAccessibility == SOUND_VI)
                    u16TempID = en_str_VI;
                else
                    u16TempID = en_str_HI;
            }
            else
                u16TempID = Empty;
            break;

        case HWND_MENU_SOUND_AUDIO_OPTION_LANGUAGE_VALUE_2:
            if ( IsAtscInUse())
            {
                if ( stGenSetting.g_SoundSetting.enSoundAudioLan == SOUND_AUDIO_LAN_ENGLISH)
                    u16TempID = en_str_English;
                else if(stGenSetting.g_SoundSetting.enSoundAudioLan == SOUND_AUDIO_LAN_SPANISH)
                    u16TempID = en_str_Spanish;
                else
                    u16TempID = en_str_French;
            }
            else
                u16TempID = Empty;
            break;
        case HWND_MENU_SOUND_PRIMARY_PARAMETER_VALUE_2:
            if ( IsAtscInUse())
            {
                if ( stGenSetting.g_SoundSetting.enPrimartAudioPmt == SOUND_ACCESSIBILITY)
                    u16TempID = en_str_Accessibility;
                else
                    u16TempID = en_str_Audio_Language;
            }
            else
                u16TempID = Empty;
            break;

        case HWND_MENU_SOUND_AUDIO_ONLY_OPTION:
            #if ENABLE_ATSC
            #if (ENABLE_AUDIO_ONLY_CUSTOMERMODE == 1)
                if( g_AudioOnly == AUDIO_ONLY_ON )
                    u16TempID = en_str_On;
                else
            #endif
                u16TempID = en_str_Off;
            #else
                u16TempID = en_str_Off;
            #endif//ATSC_RAEDY
            break;

        case HWND_MENU_SOUND_AVC_OPTION:
           {
              if( stGenSetting.g_SoundSetting.bEnableAVC)
                 u16TempID = en_str_On;
             else
                 u16TempID = en_str_Off;
           }
           break;

#if 0
           case HWND_MENU_TIME_DST_OPTION:
            switch(stGenSetting.g_SysSetting.fTimeDST)
               {
               case TIME_DST_OFF:
                   u16TempID = en_str_Off;
                   break;
               case TIME_DST_ON:
                   u16TempID = en_str_On;
                   break;
               default:
                   break;
           }
           break;
#endif

        case HWND_MENU_TIME_TIME_FORMAT_OPTION:
            if (stGenSetting.g_SysSetting.fTimeFormat == 0)
                u16TempID = en_str_24dashhour;
            else
                u16TempID = en_str_12dashhour;
            break;

        case HWND_MENU_TIME_AUTO_SYNC_OPTION:
            switch (stGenSetting.g_SysSetting.fTimeAutoSync)
            {
                case TIME_AUTO_SYNC_OFF:
                    u16TempID = en_str_Off;
                    break;
                case TIME_AUTO_SYNC_ON:
                    u16TempID = en_str_On;
                    break;
                default:
                    break;
            }
            break;

        case HWND_MENU_CHANNEL_DTV_SIGNAL_QULITY_TEXT:
            switch(enDTVSignalStatus)
            {
                    case DTV_SIGNAL_NONE:
                    case DTV_SIGNAL_BAD:
                        u16TempID = en_str_Bad;
                        break;
                    case DTV_SIGNAL_NORMAL:
                        u16TempID = en_str_Normal;
                        break;
                    case DTV_SIGNAL_GOOD:
                    default:
                        u16TempID = en_str_Good;
                        break;
            }
            break;

    #endif//ENABLE_ATSC_MENU_UI

		
		        case HWND_MENU_PICTURE_PICMODE_OPTION:
            u16TempID = _MApp_ZUI_ACT_GetPictureModeStringID();
            break;

        case HWND_MENU_PICMODE_PICMODE_OPTION:
            u16TempID = _MApp_ZUI_ACT_GetPictureModeStringID();
            break;

        case HWND_MENU_PICTURE_ASPECT_RATIO_OPTION:
            u16TempID = _MApp_ZUI_ACT_GetAspectRatioStringID();
            break;
	#if ENABLE_LIGHT_MODE
        case HWND_MENU_PICTURE_LIGHTMODE_OPTION:
            u16TempID = _MApp_ZUI_ACT_GetLightModeStringID();
            break;
	#endif
        case HWND_MENU_PIC_ADJ_TEMP_RED_OPTION:
        case HWND_MENU_PICCOLOR_COLOR_RED_OPTION:
        case HWND_MENU_PIC_ADJ_TEMP_GREEN_OPTION:
        case HWND_MENU_PICCOLOR_COLOR_GREEN_OPTION:
        case HWND_MENU_PIC_ADJ_TEMP_BLUE_OPTION:
        case HWND_MENU_PICCOLOR_COLOR_BLUE_OPTION:
            return _MApp_ZUI_ACT_CombineTextAndOption(hwnd);

		case HWND_MENU_PICTURE_BACKLIGHT_OPTION:
		MApp_UlongToU16String(stGenSetting.g_SysSetting.u8Backlight, CHAR_BUFFER, (S8)MApp_GetNoOfDigit(stGenSetting.g_SysSetting.u8Backlight));
		return CHAR_BUFFER;
            break;
        case HWND_MENU_PICCOLOR_COLOR_TEMP_OPTION:
            switch( ST_PICTURE.eColorTemp )
            {
                default:
                case MS_COLOR_TEMP_COOL:

                    u16TempID=en_str_ColorTemp_Cool;
                    break;
                case MS_COLOR_TEMP_MEDIUM:
                    u16TempID=en_str_ColorTemp_Medium;
                    break;
                case MS_COLOR_TEMP_WARM:
                    u16TempID=en_str_ColorTemp_Warm;
                    break;
            #if(MS_COLOR_TEMP_COUNT ==4)
                case MS_COLOR_TEMP_USER:
                    u16TempID=en_str_ColorTemp_User;
                    break;
            #endif
            }
            break;

        case HWND_MENU_PIC_ADJ_CONTRAST_OPTION:
        case HWND_MENU_PICMODE_CONTRAST_OPTION:
        case HWND_MENU_PIC_ADJ_BRIGHTNESS_OPTION:
        case HWND_MENU_PICMODE_BRIGHTNESS_OPTION:
        case HWND_MENU_PIC_ADJ_COLOR_OPTION:
        case HWND_MENU_PICMODE_COLOR_OPTION:
        case HWND_MENU_PIC_ADJ_SHARPNESS_OPTION:
        case HWND_MENU_PICMODE_SHARPNESS_OPTION:
        case HWND_MENU_PIC_ADJ_TINT_OPTION:
        case HWND_MENU_PICMODE_TINT_OPTION:
            return _MApp_ZUI_ACT_CombineTextAndOption(hwnd);

		
		
    #if (ENABLE_EWS)
        case  HWND_MENU_DLG_INPUT_EWS_LOCATION_PASSWORD_INPUT0_TEXT_1:
        {

            return MApp_ZUI_API_GetU16String(u8Temp_EWS_Num1);
        }

        case  HWND_MENU_DLG_INPUT_EWS_LOCATION_PASSWORD_INPUT0_TEXT_2:
        {
            return MApp_ZUI_API_GetU16String(u8Temp_EWS_Num2);
        }

        case  HWND_MENU_DLG_INPUT_EWS_LOCATION_PASSWORD_INPUT0_TEXT_3:
        {
            return MApp_ZUI_API_GetU16String(u8Temp_EWS_Num3);
        }


        case  HWND_MENU_DLG_INPUT_EWS_LOCATION_PASSWORD_INPUT0_TEXT_4:
        {
            return MApp_ZUI_API_GetU16String(u8Temp_EWS_Num4);
        }

        case  HWND_MENU_DLG_INPUT_EWS_LOCATION_PASSWORD_INPUT0_TEXT_5:
        {
            return MApp_ZUI_API_GetU16String(u8Temp_EWS_Num5);
        }
    #endif // #if (ENABLE_EWS)


        case HWND_MENU_CHANNEL_ANTENNA_OPTION:
          #if(ENABLE_DVB_TAIWAN_APP)
            switch(msAPI_ATV_GetCurrentAntenna())
            {

                case ANT_CATV:
                    u16TempID = en_str_Cable;
                    break;
                case ANT_AIR:
                    u16TempID = en_str_Air;
                    break;
                default:
                    u16TempID = Empty;
                    break;
            }
          #elif(ENABLE_ATSC_MENU_UI)
            switch(stGenSetting.stScanMenuSetting.u8Antenna)
            {
                case ANT_CATV:
                    u16TempID = en_str_Cable;
                    break;
                case ANT_AIR:
                    u16TempID = en_str_Air;
                    break;
            }
            break;
          #else
            u16TempID = Empty;
          #endif
            break;


    #if ENABLE_CI
        case HWND_MENU_CHANNEL_CI_INFORMATION_OPTION:
        {
            U8 SmartCard_Name[36];//[32];   //[32]->[36]Fix coverity CID 207401
            U8 i=0;

            msAPI_CI_GetCICAMName(SmartCard_Name,32);

            if (msAPI_CI_CardDetect())
            {
                for(i=0;i<32;i++)
                {
                    if ((SmartCard_Name[i]==0)||(i>19)) break;
                }

                if (i>19)
                {
                    SmartCard_Name[i++] = CHAR_DOT;
                    SmartCard_Name[i++] = CHAR_DOT;
                    SmartCard_Name[i++] = CHAR_DOT;
                }
                SmartCard_Name[i] = 0;
                return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, SmartCard_Name, 32);
             }
        }
        break;
    #endif // #if ENABLE_CI


        case HWND_MENU_CHANNEL_SW_OAD_UPGRADE_OPTION:
            //from case A7_OPTION_SOFTWAREUPDATETEXT:
            if(!stGenSetting.g_SysSetting.fSoftwareUpdate)
                u16TempID = en_str_Off;
            else
                u16TempID = en_str_On;
            break;

        case HWND_MENU_SW_VERSION_TEXT:
        {
            //printf("\e[31;1m [%d]: %s \33[m \n", __LINE__, __FUNCTION__);
            //printf("\e[31;1m TO DO: %d \33[m \n", (U8)hwnd);

        #if 1
            /*
            char *ptr;
            char ptr_head[128];

            unsigned char * pu8Temp;
            U8 u8Data,u8Temp_i,u8Temp_j;
            U8 u8ASCII_Mapping[16] = {'0','1','2','3','4','5','6','7','8','9','A',
                'B','C','D','E','F'};
            unsigned char Customer_info_others[48];
            U32 u32Temp;

            ptr = ptr_head;

            //<1>.For Customer ID
            //ptr = strcpy(ptr, "CID:" );
            //ptr +=4;

            ptr = memcpy(ptr, &Customer_info[0],4);
            ptr +=4;
            *ptr = '-';
            ptr++;

            //<2>.For Customer ID
            //ptr = strcpy(ptr, "MID:" );
            //ptr +=4;
            ptr = memcpy(ptr, &Customer_info[4],4);
            ptr +=4;
            *ptr = '-';
            ptr++;

            //<3>.For Customer ID
            //ptr = strcpy(ptr, "Chip:" );
            //ptr +=5;

            ptr = memcpy(ptr, &Customer_info[8],4);
            ptr +=4;
            *ptr = '-';
            ptr++;

            //<3>.To prepare the Customer Info Others
            u8Temp_i=0;
            //Get SW Project Name:01 => Chakra
            pu8Temp = &CID_Buf[CUSTOMER_INFO_START_SW_PROJECT];
            u8Data = ((*(pu8Temp))>> 4);
            Customer_info_others[u8Temp_i++] = u8ASCII_Mapping[u8Data];
            u8Data = (*(pu8Temp) & 0x0F);
            Customer_info_others[u8Temp_i++] =  u8ASCII_Mapping[u8Data];
            Customer_info_others[u8Temp_i++] =  '-';

            //Get SW Project Generation:01 => 1.0
            pu8Temp = &CID_Buf[CUSTOMER_INFO_START_SW_PROJECT_GENERATION];
            u8Data = ((*(pu8Temp))>> 4);
            Customer_info_others[u8Temp_i++] = u8ASCII_Mapping[u8Data];
            u8Data = (*(pu8Temp) & 0x0F);
            Customer_info_others[u8Temp_i++] =  u8ASCII_Mapping[u8Data];
            Customer_info_others[u8Temp_i++] =  '-';

            //Get Product Type:TV-01
            pu8Temp = &CID_Buf[CUSTOMER_INFO_START_PRODUCT];
            u8Data = ((*(pu8Temp))>> 4);
            Customer_info_others[u8Temp_i++] = u8ASCII_Mapping[u8Data];
            u8Data = (*(pu8Temp) & 0x0F);
            Customer_info_others[u8Temp_i++] =  u8ASCII_Mapping[u8Data];
            Customer_info_others[u8Temp_i++] =  '-';

            //Get TV System
            pu8Temp = &CID_Buf[CUSTOMER_INFO_START_TV_SYSTEM];
            u8Data = ((*(pu8Temp))>> 4);
            Customer_info_others[u8Temp_i++] = u8ASCII_Mapping[u8Data];
            u8Data = (*(pu8Temp) & 0x0F);
            Customer_info_others[u8Temp_i++] =  u8ASCII_Mapping[u8Data];
            Customer_info_others[u8Temp_i++] =  '-';

            pu8Temp = &CID_Buf[CUSTOMER_INFO_START_LABEL];
            u32Temp = ((*(pu8Temp+2))<<16)|((*(pu8Temp+1))<<8)|((*(pu8Temp+0)));

            for (u8Temp_j=0;u8Temp_j<6;u8Temp_j++)
            {
                u8Data = u32Temp%10;
                u32Temp = u32Temp/10;
                Customer_info_others[u8Temp_i+5-u8Temp_j] = u8ASCII_Mapping[u8Data];
            }
            u8Temp_i +=6;
            Customer_info_others[u8Temp_i++] =  '-';


            pu8Temp = &CID_Buf[CUSTOMER_INFO_START_CL];
            u32Temp = ((*(pu8Temp+2))<<16)|((*(pu8Temp+1))<<8)|((*(pu8Temp+0)));
            for (u8Temp_j=0;u8Temp_j<8;u8Temp_j++)
            {
                u8Data = u32Temp%10;
                u32Temp = u32Temp/10;
                Customer_info_others[u8Temp_i+7-u8Temp_j] = u8ASCII_Mapping[u8Data];
            }
            u8Temp_i +=8;
            Customer_info_others[u8Temp_i++] =  '-';

            //Get SW Release Purpose:01 => 1.0
            pu8Temp = &CID_Buf[CUSTOMER_INFO_START_RELEASE_PURPOSE];
            u8Data = ((*(pu8Temp))>> 4);
            Customer_info_others[u8Temp_i++] = u8ASCII_Mapping[u8Data];
            u8Data = (*(pu8Temp) & 0x0F);
            Customer_info_others[u8Temp_i++] =  u8ASCII_Mapping[u8Data];

            ptr = memcpy(ptr, &Customer_info_others[0],(u8Temp_i));

            ptr +=(u8Temp_i);
            *ptr = 0;

            return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8 *)ptr_head, strlen(ptr_head));
            */

        #else

          #if 0
            char *ptr;
            char ptr_head[128];

            ptr = ptr_head;
            ptr = strcpy(ptr, SWVersionName );
            return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8 *)ptr_head, strlen(ptr_head));
          #else // Modifed it by coverity_0544
            char ptr_head[128];
            strcpy(ptr_head, SWVersionName );
            return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8 *)ptr_head, strlen(ptr_head));
          #endif

        #endif

            break;
        }


        case HWND_MENU_SW_BUILD_TIME_TEXT:
        {
            //printf("\e[31;1m [%d]: %s \33[m \n", __LINE__, __FUNCTION__);
            //printf("\e[31;1m TO DO: %d \33[m \n", (U8)hwnd);

            /*
            char *ptr;
            char ptr_head[128];

            ptr = ptr_head;
          #if 0
            strcpy(ptr, SWCompileDate );
            strcat(ptr, ", ");
            strcat(ptr, SWCompileTime);
          #else // Modified by coverity_683
            strncpy(ptr, SWCompileDate, sizeof(SWCompileDate) );
            strncat(ptr, ", ", 2);
            strncat(ptr, SWCompileTime, sizeof(SWCompileTime));
          #endif

            return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8 *)ptr_head, strlen(ptr_head));
            */

            break;
        }


        case HWND_MENU_CHANNEL_5V_ANTENNA_OPTION:
            //from case A6_OPTION_5VANTENNAPOWERTEXT:
            if(!stGenSetting.g_SysSetting.f5VAntennaPower)
                u16TempID=en_str_Off;
            else
                u16TempID=en_str_On;
            break;


    #if (ENABLE_PIP)
        case HWND_MENU_PIP_PIPMODE_OPTION:
        case HWND_MENU_PICTURE_PIP_OPTION:
            if(IsPIPSupported())
            {
                switch(MApp_Get_PIPMode())
                {
                   default:
                   case EN_PIP_MODE_PIP:
                        u16TempID = en_str_PIP;
                        break;
                   case EN_PIP_MODE_POP_FULL:
                        u16TempID = en_str_POP_FULL;
                        break;
                   case EN_PIP_MODE_POP:
                        u16TempID = en_str_POP;
                        break;
                   case EN_PIP_MODE_OFF:
                        u16TempID = en_str_Off;
                        break;
                }
            }
            break;

        case HWND_MENU_PIP_BORDER_OPTION:
        case HWND_MENU_PIP_SOUND_SRC_OPTION:
        case HWND_MENU_PIP_SUBSRC_OPTION:
        case HWND_MENU_PIP_SIZE_OPTION:
        case HWND_MENU_PIP_POSITION_OPTION:
            if(IsPIPSupported())
            {
                return _MApp_ZUI_ACT_CombineTextAndOption(hwnd);
            }
            break;
    #endif // #if (ENABLE_PIP)

        case HWND_MENU_COMMON_ADJ_ITEM1_TEXT:
        {
            if(g_mainpage_common ==EN_COMMON_PICTURE_MODE_PAGE)
                u16TempID = en_str_Picture_Mode;
            else if (g_mainpage_common ==EN_COMMON_PICTURE_COLOR_PAGE)
                u16TempID = en_str_Color_Temperature;
          #if ENABLE_GAMMA_ADJUST
            else if (g_mainpage_common ==EN_COMMON_GAMMA_ADJUST_PAGE)
                u16TempID = en_str_GammaAdjust;
          #endif
            else if(g_mainpage_common == EN_COMMON_SOUND_BALANCE_PAGE)
                u16TempID = en_str_Balance;
            else if(g_mainpage_common == EN_COMMON_SOUND_SWITCH_PAGE)
                u16TempID = en_str_AD_Switch;
            //else if(g_mainpage_common == EN_COMMON_SOUND_AUDIO_DELAY_PAGE)
            //   u16TempID = en_str_AudioDelay;
            else if(g_mainpage_common == EN_COMMON_OFFTIMER_PAGE)
                u16TempID = en_str_Off_Time;
            else if(g_mainpage_common == EN_COMMON_ONTIMER_PAGE)
                u16TempID = en_str_On_Time;
            else if(g_mainpage_common == EN_COMMON_TIME_CLOCK_PAGE)
                u16TempID = en_str_Clock;
          #if (ENABLE_EXTERN_MFC_CHIP)
            else if(g_mainpage_common == EN_COMMON_SET_MFC_PAGE)
                u16TempID = en_str_MFC;
          #endif
          #if ENABLE_ATSC_TTS
            else if(g_mainpage_common == EN_COMMON_OPTION_TTS_PAGE)
                u16TempID = en_str_TTS;
          #endif
            break;
        }


        case HWND_MENU_COMMON_ADJ_ITEM1_OPTION:
        {
            if (g_mainpage_common == EN_COMMON_PICTURE_MODE_PAGE)
            {
                u16TempID = _MApp_ZUI_ACT_GetPictureModeStringID();
            }
            else if(g_mainpage_common == EN_COMMON_PICTURE_COLOR_PAGE)
            {
                switch( ST_PICTURE.eColorTemp )
                {
                    default:
                    case MS_COLOR_TEMP_COOL:

                        u16TempID=en_str_Cool;
                        break;
                    case MS_COLOR_TEMP_MEDIUM:
                        u16TempID=en_str_Medium;
                        break;
                    case MS_COLOR_TEMP_WARM:
                        u16TempID=en_str_Warm;
                        break;
                #if(MS_COLOR_TEMP_COUNT ==4)
                    case MS_COLOR_TEMP_USER:
                        u16TempID=en_str_User;
                        break;
                #endif
                }
            }
           #if ENABLE_GAMMA_ADJUST
            else if(g_mainpage_common == EN_COMMON_GAMMA_ADJUST_PAGE)
            {
                return MApp_ZUI_ACT_GetGammaAdjustDynamicText();
            }
           #endif
            else if(g_mainpage_common == EN_COMMON_SOUND_SWITCH_PAGE)
            {
            #if(ENABLE_DVB_AUDIO_DESC) //ENABLE_DTV
                //from case OPTION_SOUND_AD_SWITCH_TEXT:
                if(stGenSetting.g_SoundSetting.bEnableAD)
                {
                    u16TempID = en_str_On;
                }
                else
             #endif
                {
                    u16TempID = en_str_Off;
                }
            }
            else if(g_mainpage_common == EN_COMMON_OFFTIMER_PAGE)
            {
                return MApp_ZUI_ACT_GetSetOffTimeDynamicText(hwnd);
            }
            else if(g_mainpage_common == EN_COMMON_ONTIMER_PAGE)
            {
                return MApp_ZUI_ACT_GetSetOnTimeDynamicText(hwnd);
            }
          #if ENABLE_ATSC_TTS
            else if(g_mainpage_common == EN_COMMON_OPTION_TTS_PAGE)
            {
                 if(stGenSetting.g_SysSetting.bTTSOn)
                    u16TempID = en_str_On;
                else
                    u16TempID = en_str_Off;
            }
          #endif

            break;
        }

    #if (ENABLE_SCART_SVIDEO)
        case HWND_MENU_OPTION_SCART_IN_OPTION:
            switch(stGenSetting.g_SysSetting.fSCARTInputSel)
            {
                default:
                case EN_SCART_SEL_AV:
                    u16TempID = en_str_AV;
                    break;
                case EN_SCART_SEL_SV:
                    u16TempID = en_str_SdashVideo;
                    break;
            }
            break;
    #endif // #if (ENABLE_SCART_SVIDEO)

#if  (ENABLE_HDR)
        case HWND_MENU_PICTURE_HDR_OPTION:
        {
            switch(stGenSetting.g_SysSetting.enHdrSetting)
            {
                default:
                case EN_HDR_OFF:
                    u16TempID = en_str_Off;
                    break;
                case EN_HDR_AUTO:
                    u16TempID = en_str_Auto;
                    break;
                case EN_HDR_LOW:
                    u16TempID = en_str_Low;
                    break;
                case EN_HDR_MIDDLE:
                    u16TempID = en_str_Middle;
                    break;
                case EN_HDR_HIGH:
                    u16TempID = en_str_High;
                    break;
                case EN_HDR_REF:
                    u16TempID = en_str_Reference;
                    break;
            }
            break;
        }
#endif

        case HWND_MENU_PICTURE_NOISE_REDUCTION_OPTION:
        {
            switch(ST_VIDEO.eNRMode.eNR)
            {
                default:
                case MS_NR_OFF:
                    u16TempID=en_str_Off;
                    break;
                case MS_NR_LOW:
                    u16TempID=en_str_Low;
                    break;
                case MS_NR_MIDDLE:
                    u16TempID=en_str_Middle;
                    break;
                case MS_NR_HIGH:
                    u16TempID=en_str_High;
                    break;
                case MS_NR_AUTO:
                    u16TempID=en_str_Auto;
                    break;
                case MS_NR_DEFAULT:
                    u16TempID=en_str_Default;
                    break;
            }

          #if ENABLE_AUTOTEST
            if(g_bAutobuildDebug)
            {
                if(NoiseR != u16TempID)
                {
                    printf("44_NoiseReduction\n");
                }
                NoiseR = u16TempID;
            }
          #endif

            break;
        }


        case HWND_MENU_PICTURE_MPEG_NOISE_REDUCTION_OPTION:
        {
            switch (ST_VIDEO.eNRMode.eMPEG_NR)
            {
                default:
                case MS_MPEG_NR_OFF:
                    u16TempID=en_str_Off;
                    break;
                case MS_MPEG_NR_LOW:
                    u16TempID=en_str_Low;
                    break;
                case MS_MPEG_NR_MIDDLE:
                    u16TempID=en_str_Middle;
                    break;
                case MS_MPEG_NR_HIGH:
                    u16TempID=en_str_High;
                    break;
                case MS_MPEG_NR_DEFAULT:
                    u16TempID=en_str_Default;
                    break;
            }

          #if ENABLE_AUTOTEST
            if (g_bAutobuildDebug)
            {
                if(MPEGNoiseR != u16TempID)
                {
                    printf("44_MPEGNoiseReduction\n");
                }
                MPEGNoiseR = u16TempID;
            }
          #endif

            break;
        }


        case HWND_MENU_PICTURE_COLOR_TEMP_OPTION:
        {
            switch ( ST_PICTURE.eColorTemp )
            {
                default:
                case MS_COLOR_TEMP_COOL:

                    u16TempID=en_str_Cool;
                    break;
                case MS_COLOR_TEMP_MEDIUM:
                    u16TempID=en_str_Medium;
                    break;
                case MS_COLOR_TEMP_WARM:
                    u16TempID=en_str_Warm;
                    break;
            #if(MS_COLOR_TEMP_COUNT ==4)
                case MS_COLOR_TEMP_USER:
                    u16TempID=en_str_User;
                    break;
            #endif
            }

          #if ENABLE_AUTOTEST
            if(g_bAutobuildDebug)
            {
                if (ColorTem != u16TempID)
                {
                    printf("42_ColorTemperature\n");
                }
                ColorTem = u16TempID;
            }
          #endif

            break;
        }


        case HWND_MENU_COMMON_ADJ_ITEM2_OPTION:
        case HWND_MENU_COMMON_ADJ_ITEM3_OPTION:
        case HWND_MENU_COMMON_ADJ_ITEM4_OPTION:
        case HWND_MENU_COMMON_ADJ_ITEM5_OPTION:
        case HWND_MENU_COMMON_ADJ_ITEM6_OPTION:
        {
            if(g_mainpage_common == EN_COMMON_PICTURE_MODE_PAGE)
            {
                return _MApp_ZUI_ACT_CombineTextAndOption(hwnd);
            }
            else if(g_mainpage_common == EN_COMMON_PICTURE_COLOR_PAGE)
            {
                return _MApp_ZUI_ACT_CombineTextAndOption(hwnd);
            }

          #if ENABLE_GAMMA_ADJUST
            else if(g_mainpage_common == EN_COMMON_GAMMA_ADJUST_PAGE)
            {
                return _MApp_ZUI_ACT_CombineTextAndOption(hwnd);
            }
          #endif
            else if(g_mainpage_common == EN_COMMON_SOUND_BALANCE_PAGE)
            {
                return MApp_ZUI_API_GetS16SignString((S16)_MApp_ZUI_ACT_GetBalanceValue()-50);
            }
            else if(g_mainpage_common == EN_COMMON_SOUND_SWITCH_PAGE)
            {
                return _MApp_ZUI_ACT_CombineTextAndOption(hwnd);
            }
            //else if(g_mainpage_common == EN_COMMON_SOUND_AUDIO_DELAY_PAGE)
            //{
            //    return MApp_ZUI_API_GetU16String((S16)_MApp_ZUI_ACT_GetSpdifAudioDelayValue());
            //}
            else if(g_mainpage_common == EN_COMMON_OFFTIMER_PAGE)
            {
                return MApp_ZUI_ACT_GetSetOffTimeDynamicText(hwnd);
            }
            else if(g_mainpage_common == EN_COMMON_ONTIMER_PAGE)
            {
                return MApp_ZUI_ACT_GetSetOnTimeDynamicText(hwnd);
            }
            else if(g_mainpage_common == EN_COMMON_TIME_CLOCK_PAGE)
            {
                return MApp_ZUI_ACT_GetSetClockDynamicText(hwnd);
            }
          #if ENABLE_ATSC_TTS
            else if(g_mainpage_common == EN_COMMON_OPTION_TTS_PAGE)
            {
                return _MApp_ZUI_ACT_CombineTextAndOption(hwnd);
            }
          #endif

            break;
        }

        case HWND_MENU_SOUND_SNDMODE_OPTION:
        case HWND_MENU_SNDMODE_SNDMODE_OPTION:
            u16TempID = _MApp_ZUI_ACT_GetAudioModeStringID();
            break;


        case HWND_MENU_SNDMODE_TREBLE_OPTION:
        case HWND_MENU_SNDMODE_BASS_OPTION:
        case HWND_MENU_SNDEQ_120_HZ_OPTION:
        case HWND_MENU_SNDEQ_200_HZ_OPTION:
        case HWND_MENU_SNDEQ_500_HZ_OPTION:
        case HWND_MENU_SNDEQ_1_2_KHZ_OPTION:
        case HWND_MENU_SNDEQ_3_KHZ_OPTION:
        case HWND_MENU_SNDEQ_7_5_KHZ_OPTION:
        case HWND_MENU_SNDEQ_12_KHZ_OPTION:
            return _MApp_ZUI_ACT_CombineTextAndOption(hwnd);

        case HWND_MENU_SOUND_BALANCE_OPTION:
            return MApp_ZUI_API_GetS16SignString(
                (S16)_MApp_ZUI_ACT_GetSoundAdjustValue(hwnd)-50);

        case HWND_MENU_SOUND_AUDIO_DELAY_OPTION:
            return MApp_ZUI_API_GetU16String(
                (S16)_MApp_ZUI_ACT_GetSoundAdjustValue(hwnd));

        case HWND_MENU_SOUND_AUTO_VOLUME_OPTION:
        {
			if(!stGenSetting.g_SysSetting.fAutoVolume)
                u16TempID=en_str_Off;
            else
                u16TempID=en_str_On;

          #if ENABLE_AUTOTEST
            if(g_bAutobuildDebug)
            {
                if(AutoVolume != u16TempID)
                    {
                        printf("52_AutoVolume\n");
                    }
                    AutoVolume = u16TempID;
            }
          #endif

            break;
        }


        case HWND_MENU_SOUND_TV_SPEAKER_OPTION:// anvi22
        {
            //printf("\n [%d]: %s \33[m \n", __LINE__, __FUNCTION__);
            //printf(" TVspeakerMode:%d \n", stGenSetting.g_SoundSetting.TVspeakerMode);
        #if(ENABLE_CEC)
            switch (stGenSetting.g_SoundSetting.TVspeakerMode)
            {
                default:
                case TVspeaker_Mode_IntSpeaker :
                    u16TempID = en_str_TV_Speaker;
                    break;

                case TVspeaker_Mode_ExtAmp  :
                    u16TempID = en_str_External_Amp;
                    break;
            }
        #else
            u16TempID = en_str_TV_Speaker;
        #endif
            break;
        }


        case HWND_MENU_SOUND_SPDIF_MODE_OPTION:
            if(!stGenSetting.g_SysSetting.fSPDIFMODE)
                u16TempID=en_str_PCM;
            else
                u16TempID=en_str_Auto;
            break;


        case HWND_MENU_SOUND_SURROUND_OPTION:
        {
            //from case SOUND_SURROUNDSOUND_SELECTTEXT:
            switch(stGenSetting.g_SoundSetting.SurroundSoundMode & SURROUND_SYSTEM_TYPE_MASK)
            {
                case SURROUND_SYSTEM_SURROUNDMAX:
                    u16TempID = en_str_Surround;
                    break;

            #if (ENABLE_AUDIO_SURROUND_BBE  == ENABLE )
                case SURROUND_SYSTEM_BBE:
                    u16TempID = en_str_BBE;
                    break;
            #endif

            #if (ENABLE_AUDIO_SURROUND_SRS  == ENABLE )
                case SURROUND_SYSTEM_SRS:
                    u16TempID = en_str_SRS_TruSurround_XT;
                    break;
            #endif

            #if (ENABLE_AUDIO_SURROUND_VDS  == ENABLE )
                case SURROUND_SYSTEM_VDS:
                    u16TempID = en_str_Dolby_Virtual;
                    break;
            #endif

            #if (ENABLE_AUDIO_SURROUND_VSPK == ENABLE )
                case SURROUND_SYSTEM_VSPK:
                    u16TempID = en_str_Dolby_VS;
                    break;
            #endif

            #if (ENABLE_AUDIO_SURROUND_DBX  == ENABLE )
                case SURROUND_SYSTEM_DBX:
                    u16TempID = en_str_DBX;
                    break;
            #endif

                default:
                    u16TempID = en_str_Off;

            }

          #if ENABLE_AUTOTEST
            if(g_bAutobuildDebug)
            {
                if(SurroundSound != u16TempID)
                    {
                        printf("53_SurroundSound\n");
                    }
                    SurroundSound = u16TempID;
            }
          #endif

            break;
        }


    #if (ENABLE_AUDIO_SURROUND_DBX == ENABLE)
        case HWND_MENU_SOUND_DBX_TOTAL_SONICS_OPTION:
        {
            if( stGenSetting.g_SoundSetting.DBXTV_TotSonMode)
                u16TempID = en_str_Off;
            else
                u16TempID = en_str_On;

            break;
        }


        case HWND_MENU_SOUND_DBX_TOTAL_VOLUME_OPTION:
        {
            switch( stGenSetting.g_SoundSetting.DBXTV_TotVolMode)
            {
                case E_TOTVOL_NORMAL:
                    u16TempID = en_str_Normal_Mode;
                    break;

                case E_TOTVOL_NIGHT:
                    u16TempID = en_str_Night_Mode;
                    break;

                case E_TOTVOL_OFF:
                    u16TempID = en_str_Off;
                    break;
            }

            break;
        }


        case HWND_MENU_SOUND_DBX_TOTAL_SURROUND_OPTION:
        {
            if (stGenSetting.g_SoundSetting.TotSurMode)
                u16TempID = en_str_Off;
            else
                u16TempID = en_str_On;

            break;
        }

    #endif // #if (ENABLE_AUDIO_SURROUND_DBX == ENABLE)


        case HWND_MENU_TIME_SET_CLOCK_OPTION:
            return _MApp_ZUI_ACT_GetLocalClockString();

        case HWND_MENU_TIME_SET_OFFTIME_OPTION:
            //from case D2_OPTION_OFFTIMER_SELECTTEXT:
            if (!stGenSetting.g_Time.cOffTimerFlag)
            {
                u16TempID = en_str_Off;
            }
            else
            {
                LPTSTR str = CHAR_BUFFER;
                MApp_UlongToU16String( (U32)stGenSetting.g_Time.u16OffTimer_Info_Hour , str , 2);
                str += 2;

                *str ++ = CHAR_COLON;

                MApp_UlongToU16String( (U32)stGenSetting.g_Time.u16OffTimer_Info_Min , str , 2);
                //str += 2;

                //*str=0;
                return CHAR_BUFFER;
            }
            break;


        case HWND_MENU_TIME_SET_ONTIME_OPTION:
            //from case D3_OPTION_ONTIMER_SELECTTEXT:
            if(!stGenSetting.g_Time.cOnTimerFlag)
                u16TempID=en_str_Off;
            else
            {
                LPTSTR str = CHAR_BUFFER;

                MApp_UlongToU16String( (U32)stGenSetting.g_Time.u16OnTimer_Info_Hour  , str , 2);
                str += 2;

                *str ++ = CHAR_COLON;

                MApp_UlongToU16String( (U32)stGenSetting.g_Time.u16OnTimer_Info_Min , str , 2);
                //str += 2;

                //*str=0;
                return CHAR_BUFFER;
            }
            break;


        case HWND_MENU_TIME_SET_SLEEP_TIMER_OPTION:
            _MApp_ZUI_ACT_GetSleepTimerString(CHAR_BUFFER);
            return CHAR_BUFFER;


        case HWND_MENU_TIME_SET_AUTO_SLEEP_OPTION:
        {
            //from case D5_OPTION_AUTOOFF_SELECTTEXT:
          #if ENABLE_AUTOTEST
            if(g_bAutobuildDebug)
            {
                if(AutoSleep != u16TempID)
                {
                    printf("61_AutoSleep\n");
                }
                AutoSleep = u16TempID;
            }
          #endif

        #if( ENABLE_NO_OPERATE_AUTO_SLEEP )
            switch(MApp_NoOperateAutoSleep_Get_AutoSleepTime())
            {
                default:
               case STATE_AUTOSLEEP_NEVER:
                   u16TempID = en_str_Nerver;
                   break;

               case STATE_AUTOSLEEP_4HOUR:
                   u16TempID = en_str_4Hours;
                   break;

               case STATE_AUTOSLEEP_6HOUR:
                   u16TempID = en_str_6Hours;
                   break;

               case STATE_AUTOSLEEP_8HOUR:
                   u16TempID = en_str_8Hours;
                   break;
            }
        #endif

            break;
        }


        case HWND_MENU_TIME_SET_TIMEZONE_OPTION:
        {
        #if ENABLE_DTV
          #if (ENABLE_ATSC)
            if (IsAtscInUse() || IsATVInUse())
            {
                //printf("[ms] ATSC time zone,  %d,  %d\n", IsAtscInUse(), IsATVInUse());
                switch(stGenSetting.g_SysSetting.u8TimeZone)
                {
                    case TIME_ZONE_ATLANTIC:
                        u16TempID = en_str_Atlantic;
                        break;
                    case TIME_ZONE_EASTERN:
                        u16TempID = en_str_Eastern;
                        break;
                    case TIME_ZONE_CENTRAL:
                        u16TempID = en_str_Central;
                        break;
                    case TIME_ZONE_MOUNTAIN:
                        u16TempID = en_str_Mountain;
                        break;
                    case TIME_ZONE_PACIFIC:
                        u16TempID = en_str_Pacific;
                        break;
                    case TIME_ZONE_ALASKA:
                        u16TempID = en_str_Alaska;
                        break;
                    case TIME_ZONE_HAWAII:
                        u16TempID = en_str_Hawaii;
                        break;
                    default:
                        break;
                }
            }
            else
          #endif
            {
                //printf("[ms] DVB time zone\n");
                u16TempID = MApp_ZUI_ACT_GetTimezoneStringID(stGenSetting.g_Time.enTimeZone);
            }

          #if ENABLE_AUTOTEST
            if(g_bAutobuildDebug)
            {
                if(TimeZone != u16TempID)
                    {
                        printf("61_TimeZone\n");
                    }
                    TimeZone = u16TempID;
            }
          #endif
        #endif // #if ENABLE_DTV

            break;
        }


        case HWND_MENU_OPTION_OSD_LANG_OPTION:
        {
          #if ENABLE_AUTOTEST
            if(g_bAutobuildDebug)
            {
                u16TempID = _MApp_ZUI_ACT_GetLanguageStringID(GET_OSD_MENU_LANGUAGE_DTG(), TRUE);

                if(OSD_L != u16TempID)
                {
                     printf("71_OSD_Language\n");
                }
                OSD_L = u16TempID;
            }
          #endif

            LPTSTR str = MApp_ZUI_ACT_GetMenuLanguageStringByIndex(GET_OSD_MENU_LANGUAGE_DTG());

            if(str)
                return str;

            u16TempID = en_str_English;
        }
            break;


        case HWND_MENU_OPTION_AUDIO_LANG_OPTION:
        {
        #if ENABLE_DTV
          #if ENABLE_AUTOTEST
            //from case AUDIOLANGUAGESELECTTEXT:
            u16TempID = _MApp_ZUI_ACT_GetLanguageStringID(
                (EN_LANGUAGE)stGenSetting.g_SoundSetting.enSoundAudioLan1, TRUE);

            if (g_bAutobuildDebug)
            {
                if (Audio_L != u16TempID)
                {
                     printf("71_Audio_Language\n");
                }
                Audio_L = u16TempID;
            }
          #endif

            LPTSTR str = MApp_ZUI_ACT_GetMenuLanguageStringByIndex((EN_LANGUAGE)stGenSetting.g_SoundSetting.enSoundAudioLan1);

            if(str)
                return str;

            u16TempID = en_str_English;

        #endif

            break;
        }

        case HWND_MENU_OPTION_SUBTITLE_LANG_OPTION:
        {
        #if ENABLE_DTV
          #if ENABLE_AUTOTEST
            //from case SUBTITLELANGUAGESELECTTEXT:
            u16TempID =_MApp_ZUI_ACT_GetLanguageStringID(
                (EN_LANGUAGE)SUBTITLE_DEFAULT_LANGUAGE_1, TRUE);

            if (g_bAutobuildDebug)
            {
                if (Subtitle_L != u16TempID)
                {
                     printf("71_Subtitle_Language\n");
                }
                Subtitle_L = u16TempID;
            }
          #endif

            LPTSTR str = MApp_ZUI_ACT_GetMenuLanguageStringByIndex((EN_LANGUAGE)SUBTITLE_DEFAULT_LANGUAGE_1);

            if(str)
                return str;

            u16TempID = en_str_English;
        #endif

            break;
        }


        case HWND_MENU_OPTION_HARD_HEARING_OPTION:
        {
        #if ENABLE_DTV
            //from case LANGUAGE_SUBTITLE_MODE_HEARING_SELECTTEXT:
            switch (stGenSetting.g_SysSetting.fHardOfHearing)
            {
                case EN_SUBTITILE_SYSTEM_OFF:
                    u16TempID=en_str_Off;
                    break;
                case EN_SUBTITILE_SYSTEM_ON:
                    u16TempID=en_str_On;
                    break;
            }

          #if ENABLE_AUTOTEST
            if(g_bAutobuildDebug)
            {
                if(Headphone_L != u16TempID)
                    {
                        printf("72_Headphone\n");
                    }
                    Headphone_L = u16TempID;
            }
          #endif
        #endif

            break;
        }

#if ENABLE_SUBTITLE_SWITCH_MENU
        case HWND_MENU_OPTION_SUBTITLE_ONOFF_OPTION:
        {
            if(MENU_OPTION_SUBTITLE_ON)
            {
                u16TempID = en_str_On;
            }
            else
            {
                u16TempID = en_str_Off;
            }
            break;
        }
#endif

        case HWND_MENU_OPTION_DIVX:
        {
        #if ENABLE_DRM
            u16TempID=en_str_DIVX_Regdot_Code;
        #else
            u16TempID=Empty;
        #endif

            break;
        }


    #if (ENABLE_MAINPAGE_EFFECT)
        case HWND_MENU_OPTION_OSD_EFFECT_OPTION:
            switch (stGenSetting.g_SysSetting.fEnableOsdAnimation)
            {
                case EN_OSD_EFFECT_ON:
                    u16TempID=en_str_On;
                    break;
                case EN_OSD_EFFECT_ROTATION_ONLY:
                    u16TempID=en_str_Rotation_only;
                    break;
            }
            break;
    #endif

    #if ENABLE_ATSC
      #if ENABLE_ATSC_MAIN_MENU_PICTURE_PAGE
        case HWND_MENU_PICTURE_COLRANGE_OPTION:
      #endif
    #endif


        case HWND_MENU_OPTION_COLOR_RANGE_OPTION:
            if (stGenSetting.g_SysSetting.enCOLORRANGE == EN_COLOR_RANGE_0_255)
                  u16TempID=en_str_0_255;
            else if (stGenSetting.g_SysSetting.enCOLORRANGE == EN_COLOR_RANGE_16_235)
                  u16TempID=en_str_16_235;
            else
                  u16TempID=en_str_Auto;
            break;

    #if (ENABLE_3D_PROCESS)
        case HWND_MENU_OPTION_3D_TYPE_OPTION:
            switch(DB_3D_SETTING.en3DType)
            {
                case EN_3D_BYPASS:
                    u16TempID = en_str_2D;
                    break;
                case EN_3D_FRAME_PACKING:
                     u16TempID = en_str_Frame_packing;
                     break;
                case EN_3D_SIDE_BY_SIDE:
                    u16TempID = en_str_side_by_side;
                    break;
                case EN_3D_TOP_BOTTOM:
                    u16TempID = en_str_top_bottom;
                    break;
                case EN_3D_LINE_ALTERNATIVE:
                    u16TempID = en_str_line_by_line;
                    break;
                case EN_3D_FRAME_ALTERNATIVE:
                     u16TempID = en_str_Frame_alternative;
                     break;
                case EN_3D_2DConvertTo3D:
                    u16TempID = en_str_2D_to_3D;
                    break;
                default:
                     u16TempID = en_str_2D;
                    break;
            }
            break ;

        case HWND_MENU_OPTION_3D_TO_2D_OPTION:
            switch(DB_3D_SETTING.en3DTo2DType)
            {
                case EN_3D_TO_2D_OFF:
                    u16TempID = en_str_Off;
                    break;
              #if 0
                case EN_3D_TO_2D_FRAME_PARKING:
                     u16TempID = en_str_Frame_packing;
                     break;
                case EN_3D_TO_2D_SIDE_BY_SIDE:
                    u16TempID = en_str_side_by_side;
                    break;
                case EN_3D_TO_2D_TOP_BOTTOM:
                    u16TempID = en_str_top_bottom;
                    break;
                case EN_3D_TO_2D_LINE_BY_LINE:
                    u16TempID = en_str_line_by_line;
                    break;
                case EN_3D_TO_2D_FRAME_ALTERNATIVE:
                     u16TempID = en_str_Frame_alternative;
                     break;
              #else
                case EN_3D_TO_2D_ON:
                    u16TempID = en_str_On;
                    break;
              #endif
                default:
                     u16TempID = en_str_Off;
                    break;
            }
            break ;

        case HWND_MENU_OPTION_3D_DETECT_OPTION:
            switch(DB_3D_SETTING.en3DDetectMode)
            {
                case EN_3D_DETECT_AUTO:
                     u16TempID = en_str_Auto;
                     break;
                case EN_3D_DETECT_MANUAL:
                     u16TempID = en_str_manual;
                     break;
                default:
                     u16TempID = en_str_Auto;
                     break;
            }
            break;

        case HWND_MENU_OPTION_3D_LR_OPTION:
            switch(DB_3D_SETTING.en3DLRMode)
            {
                case EN_3D_LR_L:
                     u16TempID = en_str_R;
                     break;
                case EN_3D_LR_R:
                     u16TempID = en_str_L;
                     break;
                default:
                     u16TempID = en_str_R;
                     break;
            }
            break;

        case HWND_MENU_OPTION_3D_HSHIFT_OPTION:
            switch(DB_3D_SETTING.en3DHShiftMode)
            {
                case EN_3D_HSHIFT_WEAK:
                    u16TempID = en_str_Low;
                    break;
                default:
                case EN_3D_HSHIFT_MID:
                    u16TempID = en_str_Middle;
                    break;
                case EN_3D_HSHIFT_STRONG:
                    u16TempID = en_str_High;
                    break;
            }
            break;

        case HWND_MENU_OPTION_3D_VIEW_POINT_OPTION:
            switch(DB_3D_SETTING.en3DViewPointMode)
            {
                case EN_3D_VIEW_POINT_WEAK:
                    u16TempID = en_str_Low;
                    break;
                default:
                case EN_3D_VIEW_POINT_MID:
                    u16TempID = en_str_Middle;
                    break;
                case EN_3D_VIEW_POINT_STRONG:
                    u16TempID = en_str_High;
                    break;
            }
            break;

      #if (ENABLE_EXTERN_MFC_CHIP)
        case HWND_MENU_OPTION_MFC_SET_MFC_OPTION:
            switch(stGenSetting.stDevMfcSetting.enMFCStrength)
            {
                case EN_MFC_Strength_Off:
                    u16TempID = en_str_Off;
                    break;
                case EN_MFC_Strength_Weak:
                    u16TempID = en_str_Low;
                    break;
                case EN_MFC_Strength_Normal:
                    u16TempID = en_str_Middle;
                    break;
                case EN_MFC_Strength_Strong:
                    u16TempID = en_str_High;
                    break;
                default:
                    u16TempID = en_str_Middle;
                    break;
            }
            break;

        case HWND_MENU_OPTION_MFC_SET_MFC_DEMO_OPTION:
            switch(stGenSetting.stDevMfcSetting.enMEMCType)
            {
                case MFC_Off:
                    u16TempID = en_str_Off;
                    break;
                case MFC_Horizantal:
                    u16TempID = en_str_Horizon;
                    break;
                case MFC_Vertical:
                    u16TempID = en_str_Vertical;
                    break;
                default:
                    u16TempID = en_str_Off;
                    break;
            }
                break;
        case HWND_MENU_OPTION_6M30_MIRROR_OPTION:
            switch(stGenSetting.stDevMfcSetting.en6M30MirrorMode)
            {
                case EN_6M30_MIRROR_ON:
                    u16TempID = en_str_On;
                    break;
                default:
                case EN_6M30_MIRROR_OFF:
                    u16TempID = en_str_Off;
                    break;
            }
            break;

         case HWND_MENU_OPTION_6M30_VERSION_OPTION:
            {
                U16 u16VersionData = 0;
                u16VersionData = (U16)(MDrv_Ursa_6M30_Ver_Main() << 8)|MDrv_Ursa_6M30_Ver_Minor();
                return MApp_ZUI_API_GetU16HexString(u16VersionData);
            }
            break;
      #endif // #if (ENABLE_EXTERN_MFC_CHIP)
    #endif // #if (ENABLE_3D_PROCESS)


        case HWND_MENU_OPTION_COUNTRY_OPTION:
            u16TempID = MApp_ZUI_ACT_GetCountryStringID(OSD_COUNTRY_SETTING);
            break;

    #if ENABLE_E_POP
        case HWND_MENU_OPTION_EPOP_OPTION:
			return EN_DL_STATE_HIDDEN;
             if(!stGenSetting.g_SysSetting.fEpop)
                u16TempID=en_str_Off;
            else
                u16TempID=en_str_On;
            break;
    #endif


    #if (ENABLE_EDID_SWITCH)
      #if (  UI_SKIN_SEL == UI_SKIN_1920X1080X565   \
          || UI_SKIN_SEL == UI_SKIN_1366X768X565    \
          || UI_SKIN_SEL == UI_SKIN_1366X768X4444   \
          || UI_SKIN_SEL == UI_SKIN_1366X768X8888   \
          || UI_SKIN_SEL == UI_SKIN_960X540X565     \
          )
        case HWND_MENU_OPTION_EDID_SWITCH_OPTION:
        {
            if(MApi_XC_Sys_Get_UserEdidSel() == E_USER_HDMI_EDID_1p4)
                u16TempID = en_str_EDID_1dot4;
            else if(MApi_XC_Sys_Get_UserEdidSel() == E_USER_HDMI_EDID_2p0)
                u16TempID = en_str_EDID_2dot0;
            else
                u16TempID = en_str_EDID_Switch;

            break;
        }
        #endif
    #endif // #if (ENABLE_EDID_SWITCH)


        case HWND_MENU_LOCK_SYSTEM_OPTION:
        {
          #if ENABLE_ATSC
            if(IsAtscInUse()|| IsATVInUse()||IsAVInUse())
            {
                if(!stGenSetting.g_VChipSetting.u8VChipLockMode)
                    u16TempID=en_str_Off;
                else
                    u16TempID=en_str_On;
            }
            else
          #endif
            {
                if(!MApp_MenuFunc_Setup_BlockSysEnterLockPage_Get())
                {
                    MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_SET_PASSWORD, DISABLE);
                    MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_BLOCK_PROGRAM, DISABLE);
                    MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_PARENTAL_GUIDANCE, DISABLE);
                    MApp_ZUI_API_InvalidateWindow(HWND_MENU_LOCK_PAGE_LIST);
                    break;
                }
                else
                {
                    MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_SET_PASSWORD, ENABLE);
                    MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_BLOCK_PROGRAM, ENABLE);
                    MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_PARENTAL_GUIDANCE, ENABLE);
                    MApp_ZUI_API_InvalidateWindow(HWND_MENU_LOCK_PAGE_LIST);
                }

                if(!MApp_MenuFunc_Setup_BlockSysLockMode_Get())
                    u16TempID=en_str_Off;
                else
                    u16TempID=en_str_On;
            }

          #if ENABLE_AUTOTEST
            if(g_bAutobuildDebug)
            {
                if(LockS != u16TempID)
                {
                    printf("81_LockSystem\n");
                }
                LockS = u16TempID;
            }
          #endif

            break;
        }


        case HWND_MENU_LOCK_PARENTAL_GUIDANCE_OPTION:
        {
          #if ENABLE_AUTOTEST
            if(g_bAutobuildDebug)
            {
                if(ParentalG != stGenSetting.g_BlockSysSetting.u8ParentalControl)
                {
                    printf("81_ParentalGuidance\n");
                }
                ParentalG = stGenSetting.g_BlockSysSetting.u8ParentalControl;
            }
          #endif

            if (stGenSetting.g_BlockSysSetting.u8ParentalControl<=EN_F4_ParentalControl_Off )
            {
                stGenSetting.g_BlockSysSetting.u8ParentalControl= EN_F4_ParentalControl_Off;
                u16TempID=en_str_Off;
            }
            else
            {
              #if(ENABLE_ZIGGO)
                if(stGenSetting.g_BlockSysSetting.u8ParentalControl == EN_F4_LockSystem_AllLock)
                    u16TempID=en_str_ALLLOCK;
                else
                    return MApp_ZUI_API_GetU16String(stGenSetting.g_BlockSysSetting.u8ParentalControl);
              #elif(ENABLE_PARENTAL_GUIDANCE_CLASSIFICATION)
                switch(stGenSetting.g_BlockSysSetting.u8ParentalControl)
                {
                    case 4:
                        u16TempID=en_str_G;
                        break;
                    case 7:
                        u16TempID=en_str_PG;
                        break;
                    case 13:
                        u16TempID=en_str_PGdash13;
                        break;
                    case 16:
                        return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8*)"NC-16", STRING_BUFFER_LENGTH);
                    case 18:
                        return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8*)"M-18", STRING_BUFFER_LENGTH);
                    case 21:
                        return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8*)"R-21", STRING_BUFFER_LENGTH);

                    default:
                        printf("error! no match parental value!!\n");
                        return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8*)"Error!", STRING_BUFFER_LENGTH);

                }
              #else
                return MApp_ZUI_API_GetU16String(stGenSetting.g_BlockSysSetting.u8ParentalControl);
              #endif
            }

            break;
        }


    #if BRAZIL_CC  //ENABLE_SBTVD_BRAZIL_APP
        case HWND_MENU_OPTION_CAPTION_OPTION:
        {
            if(IsDTVInUse())
            {
                if(DB_CC_SETTING.enDTVCaptionType == DTV_CAPTION_ON)
                {
                    u16TempID=en_str_On;
                }
                else
                {
                    u16TempID=en_str_Off;
                }
            }
            else
            {
                if(DB_CC_SETTING.enATVCaptionType == ATV_CAPTION_TYPE_CC1)
                {
                    u16TempID=en_str_CC_1;
                }
                else if(DB_CC_SETTING.enATVCaptionType == ATV_CAPTION_TYPE_CC2)
                {
                    u16TempID=en_str_CC_2;
                }
                else if(DB_CC_SETTING.enATVCaptionType == ATV_CAPTION_TYPE_CC3)
                {
                    u16TempID=en_str_CC_3;
                }
                else if(DB_CC_SETTING.enATVCaptionType == ATV_CAPTION_TYPE_CC4)
                {
                    u16TempID=en_str_CC_4;
                }
                else if(DB_CC_SETTING.enATVCaptionType == ATV_CAPTION_TYPE_TEXT1)
                {
                    u16TempID=en_str_Text_1;
                }
                else if(DB_CC_SETTING.enATVCaptionType == ATV_CAPTION_TYPE_TEXT2)
                {
                    u16TempID=en_str_Text_2;
                }
                else if(DB_CC_SETTING.enATVCaptionType == ATV_CAPTION_TYPE_TEXT3)
                {
                    u16TempID=en_str_Text_3;
                }
                else if(DB_CC_SETTING.enATVCaptionType == ATV_CAPTION_TYPE_TEXT4)
                {
                    u16TempID=en_str_Text_4;
                }
                else
                {
                    DB_CC_SETTING.enATVCaptionType = ATV_CAPTION_TYPE_OFF;
                    u16TempID=en_str_Off;
                }
            }

            break;
        }
    #endif // #if BRAZIL_CC


        case HWND_MENU_PCMODE_HPOS_OPTION:
        case HWND_MENU_PCMODE_VPOS_OPTION:
        case HWND_MENU_PCMODE_SIZE_OPTION:
        case HWND_MENU_PCMODE_PHASE_OPTION:
            return _MApp_ZUI_ACT_CombineTextAndOption(hwnd);


    #if 0//ENABLE_DTV
        case HWND_MENU_DLG_SIGNAL_INFORMAT_CHANNEL_NAME:
        {
        #if ENABLE_DTV
            BYTE cRFChannelNumber = msAPI_CM_GetPhysicalChannelNumber(msAPI_CM_GetCurrentServiceType(),msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()));
            LPTSTR u16ChaConStr = NULL;
        #endif
            LPTSTR u16ChaStr = CHAR_BUFFER;

            U16 u16ChaLen = 0;
            MApp_ZUI_API_LoadString(en_str_Channel, u16ChaStr);
            u16ChaLen = MApp_ZUI_API_Strlen(u16ChaStr);
            u16ChaStr[u16ChaLen++] = CHAR_SPACE;
            if(cRFChannelNumber == INVALID_PHYSICAL_CHANNEL_NUMBER)
            {
                u16ChaStr[u16ChaLen++] = '.';
                u16ChaStr[u16ChaLen++] = '.';
                u16ChaStr[u16ChaLen++] = '.';
                u16ChaStr[u16ChaLen++] = 0;
                return u16ChaStr;
            }
            else
            {
                u16ChaStr[u16ChaLen++] = 0;
                u16ChaConStr = MApp_ZUI_API_GetU16String(cRFChannelNumber);
                MApp_ZUI_API_Strcat(u16ChaStr, (U16*)u16ChaConStr);
                return u16ChaStr;
            }

            break;
        }
    #endif


        case HWND_MENU_DLG_SIGNAL_INFORMAT_CHANNEL_UHF:
            return 0;// can return Freq here,if need be

      #if ENABLE_DVB
        case HWND_MENU_DLG_SIGNAL_INFORMAT_NETWORK_NAME:
        {
        #if (ENABLE_S2&&(CHIP_FAMILY_TYPE != CHIP_FAMILY_MAYA))
            if (IsS2InUse())
            {
                return MApp_ZUI_GetCurrentChName(MAIN_WINDOW);
            }
        #endif
            U8 i;
            U8 au8NetWorkName[MAX_NETWORK_NAME];
            U8 u8NetWorkNameLen = 0;
            U16 u16NetLen;
            WORD SignalStrength = 0;
            LPTSTR u16NetStr = CHAR_BUFFER;
            U16 u16CharBuffer[MAX_NETWORK_NAME]={ 0,  };

            msAPI_Tuner_CheckSignalStrength(&SignalStrength);
            //printf("SignalStrength=%u\n", SignalStrength);

            MApp_ZUI_API_LoadString(en_str_Network, u16NetStr);
            u16NetLen = MApp_ZUI_API_Strlen(u16NetStr);
            //printf("u16NetLen=%u\n", u16NetLen);

            u16NetStr[u16NetLen++] = CHAR_SPACE;

            memset(au8NetWorkName,0,MAX_NETWORK_NAME);

        #if 1 //mantis:0331500
            if ((TRUE == MApp_SI_Get_NetWorkName(au8NetWorkName,&u8NetWorkNameLen,MAX_NETWORK_NAME)) /*&& (0!=au8NetWorkName[0])*/)
            {
                msAPI_CM_SetCurrentNetworkName(au8NetWorkName, u8NetWorkNameLen);
            }
        #endif

            //printf("u8NetWorkNameLen=%u\n", u8NetWorkNameLen);

            if (  msAPI_CM_GetCurrentNetworkName(au8NetWorkName,&u8NetWorkNameLen,MAX_NETWORK_NAME)
               && (SignalStrength>2))
            {
                MApp_CharTable_MappingDVBTextToUCS2(au8NetWorkName, u16CharBuffer, u8NetWorkNameLen, MAX_NETWORK_NAME, REMOVE_00AD_SOFT_HYPHEN);
                //MApp_CharTable_MappingDVBTextToUCS2(au8NetWorkName, u16CharBuffer, MAX_NETWORK_NAME, MAX_NETWORK_NAME, REMOVE_00AD_SOFT_HYPHEN);

                //printf("u16NetLen=%u\n", u16NetLen);
                for( i=0; i<u8NetWorkNameLen; i++)
                {
                    if( u16CharBuffer[i] !=0 )
                    {
                        u16NetStr[u16NetLen+i] = u16CharBuffer[i];
                    }
                    else
                    {
                        break;
                    }
                }
                u16NetStr[u16NetLen+i] = 0;

            }
            else
            {
                u16NetStr[u16NetLen++] = '.';
                u16NetStr[u16NetLen++] = '.';
                u16NetStr[u16NetLen++] = '.';
                u16NetStr[u16NetLen++] = 0;
            }
            //printf("\n---[%s]->%d.{NetStr=%s}\n",__func__,__LINE__,u16NetStr);

            return u16NetStr;
        }
      #endif // #if ENABLE_DVB


        case HWND_MENU_DLG_SIGNAL_INFORMAT_QUALITY_PERCENT_VAL:
        case HWND_MENU_DLG_SIGNAL_INFORMAT_STRENGTH_PERCENT_VAL:
        case HWND_MENU_DLG_SIGNAL_INFORMAT_MODULATION_NAME:
            return _MApp_ZUI_ACT_CombineTextAndOption(hwnd);


    #if(ENABLE_DTV)
        case HWND_MENU_DLG_SIGNAL_INFORMAT_CHANNEL_NAME:
        {
           #if(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA)
            if(IsS2InUse())
            {
             return 0;
            }
            else
           #endif
              return _MApp_ZUI_ACT_CombineTextAndOption(hwnd);
        }

        case HWND_MENU_DLG_SIGNAL_INFORMAT_QUALITY_INDEX_STRING:
        {
            WORD SignalQuality = 0;

            SignalQuality = msAPI_Tuner_GetSignalQualityPercentage();

            if(SignalQuality > 100)
            {
                SignalQuality = 100;
            }
            if(SignalQuality>=60)
            {
                u16TempID = en_str_bracketsGood;
            }
            else
            {
                u16TempID = en_str_bracketsPoor;
            }

            break;
        }


        case HWND_MENU_DLG_SIGNAL_INFORMAT_STRENGTH_INDEX_STRING:
        {
            WORD SignalStrength = 0;

            msAPI_Tuner_CheckSignalStrength(&SignalStrength);

            if(SignalStrength>=100)
            {
                SignalStrength = 100;
            }
            if(SignalStrength>=70)
            {
                u16TempID = en_str_bracketsStrong;
            }
            else if(SignalStrength>=40)
            {
                u16TempID = en_str_bracketsAverage;
            }
            else
            {
                u16TempID = en_str_bracketsWeak;
            }

            break;
        }

    #endif // #if(ENABLE_DTV)

    #if (ATSC_CC == ATV_CC)
        case HWND_MENU_OPTION_CC_OPTION_OPTION:
        {
            switch(DB_CC_SETTING.enATVCaptionType)
            {
                case ATV_CAPTION_TYPE_OFF:
                     u16TempID = en_str_Off;
                     break;
               case ATV_CAPTION_TYPE_CC1:
                    u16TempID = en_str_CC_1;
                    break;
                case ATV_CAPTION_TYPE_CC2:
                    u16TempID = en_str_CC_2;
                    break;
                case ATV_CAPTION_TYPE_CC3:
                    u16TempID = en_str_CC_3;
                    break;
                case ATV_CAPTION_TYPE_CC4:
                    u16TempID = en_str_CC_4;
                    break;
                case ATV_CAPTION_TYPE_TEXT1:
                    u16TempID = en_str_Text_1;
                    break;
                case ATV_CAPTION_TYPE_TEXT2:
                    u16TempID = en_str_Text_2;
                    break;
                case ATV_CAPTION_TYPE_TEXT3:
                    u16TempID = en_str_Text_3;
                    break;
                case ATV_CAPTION_TYPE_TEXT4:
                    u16TempID = en_str_Text_4;
                    break;
                default:
                    break;
            }

            break ;
        }
    #endif // #if (ATSC_CC == ATV_CC)


    #if ENABLE_CEC  //anvi  cec
        case HWND_MENU_HDMI_CEC_ARC_OPTION:
        {
            if (stGenSetting.stHDMISetting.g_enHDMIARC)
                u16TempID = en_str_On;
            else
                u16TempID = en_str_Off;

            break;
        }

        case HWND_MENU_HDMI_CEC_HDMI_OPTION:
            if (DB_HDMI_SETTING.g_bHdmiCecMode == EN_E4_HDMICEC_On)
                u16TempID = en_str_On;
            else
                u16TempID = en_str_Off;
            break;

        case HWND_MENU_HDMI_CEC_AUTO_STANDBY_OPTION:
            if (DB_HDMI_SETTING.g_bHdmiCecDeviceAutoStandby)
                u16TempID = en_str_On;
            else
                u16TempID = en_str_Off;
            break;

        case HWND_MENU_HDMI_CEC_AUTO_TV_ON_OPTION:
            if (DB_HDMI_SETTING.g_bHdmiCecAutoTvOn)
                u16TempID = en_str_On;
            else
                u16TempID = en_str_Off;
            break;

        case HWND_MENU_HDMI_CEC_DEVICE_CONTROL_OPTION:
            if (DB_HDMI_SETTING.g_bHdmiCecDeviceControl)
                u16TempID = en_str_On;
            else
                u16TempID = en_str_Off;
            break;

        case HWND_MENU_HDMI_CEC_DEVICE_LIST_A_PORT_TEXT :
        case HWND_MENU_HDMI_CEC_DEVICE_LIST_B_PORT_TEXT :
        case HWND_MENU_HDMI_CEC_DEVICE_LIST_C_PORT_TEXT :
        case HWND_MENU_HDMI_CEC_DEVICE_LIST_D_PORT_TEXT :
        case HWND_MENU_HDMI_CEC_DEVICE_LIST_E_PORT_TEXT :
        case HWND_MENU_HDMI_CEC_DEVICE_LIST_F_PORT_TEXT :
        case HWND_MENU_HDMI_CEC_DEVICE_LIST_G_PORT_TEXT :
        case HWND_MENU_HDMI_CEC_DEVICE_LIST_H_PORT_TEXT :
        case HWND_MENU_HDMI_CEC_DEVICE_LIST_I_PORT_TEXT :
        case HWND_MENU_HDMI_CEC_DEVICE_LIST_J_PORT_TEXT :
            if(g_stMenuCecDeviceList.u8CECDeviceNum >(hwnd-HWND_MENU_HDMI_CEC_DEVICE_LIST_A_PORT_TEXT)/3)
            {
                //MS_U16 u16Value;
                U8 i;
                i = 0+(hwnd-HWND_MENU_HDMI_CEC_DEVICE_LIST_A_PORT_TEXT)/3;
                u16Value = (((g_stMenuCecDeviceList.wPhyAddr[i] & 0xF000) >> 12) & 0x000F);
                memset(au8Section,0,256);
                strncpy((char *)au8Section, "HDMI", strlen("HDMI")+1);
                MApp_UlongToU8String((U32)u16Value, &au8Section[4],1);
                return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, au8Section, strlen((char *)au8Section));
            }
            break;

        case HWND_MENU_HDMI_CEC_DEVICE_LIST_A_TEXT:
        case HWND_MENU_HDMI_CEC_DEVICE_LIST_B_TEXT:
        case HWND_MENU_HDMI_CEC_DEVICE_LIST_C_TEXT:
        case HWND_MENU_HDMI_CEC_DEVICE_LIST_D_TEXT:
        case HWND_MENU_HDMI_CEC_DEVICE_LIST_E_TEXT:
        case HWND_MENU_HDMI_CEC_DEVICE_LIST_F_TEXT:
        case HWND_MENU_HDMI_CEC_DEVICE_LIST_G_TEXT:
        case HWND_MENU_HDMI_CEC_DEVICE_LIST_H_TEXT:
        case HWND_MENU_HDMI_CEC_DEVICE_LIST_I_TEXT:
        case HWND_MENU_HDMI_CEC_DEVICE_LIST_J_TEXT:
            if(g_stMenuCecDeviceList.u8CECDeviceNum > (hwnd-HWND_MENU_HDMI_CEC_DEVICE_LIST_A_TEXT)/3)
            {
                U8 i;
                i = 0+(hwnd-HWND_MENU_HDMI_CEC_DEVICE_LIST_A_TEXT)/3;
                memset(au8Section,0,256);
                strcpy((char *)au8Section,(char *)g_stMenuCecDeviceList.au8CecDeviceName[i]);
                return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, au8Section, strlen((char *)au8Section));
            }
            break;

        case HWND_MENU_HDMI_CEC_DEVICE_LIST_B:
            if(u8HDMI_CEC_DevicesName[1] != NULL)
                return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, u8HDMI_CEC_DevicesName[1], strlen((const char *)u8HDMI_CEC_DevicesName[1]));
            break;

        case HWND_MENU_HDMI_CEC_DEVICE_LIST_C:
            if(u8HDMI_CEC_DevicesName[2] != NULL)
                return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, u8HDMI_CEC_DevicesName[2], strlen((const char *)u8HDMI_CEC_DevicesName[2]));
            break;

        case HWND_MENU_HDMI_CEC_DEVICE_LIST_D:
            if(u8HDMI_CEC_DevicesName[3] != NULL)
                return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, u8HDMI_CEC_DevicesName[3], strlen((const char *)u8HDMI_CEC_DevicesName[3]));
            break;

        case HWND_MENU_HDMI_CEC_DEVICE_LIST_E:
            if(u8HDMI_CEC_DevicesName[4] != NULL)
                return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, u8HDMI_CEC_DevicesName[4], strlen((const char *)u8HDMI_CEC_DevicesName[4]));
            break;

        case HWND_MENU_HDMI_CEC_DEVICE_LIST_F:
            if(u8HDMI_CEC_DevicesName[5] != NULL)
                return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, u8HDMI_CEC_DevicesName[5], strlen((const char *)u8HDMI_CEC_DevicesName[5]));
            break;

        case HWND_MENU_HDMI_CEC_DEVICE_LIST_G:
            if(u8HDMI_CEC_DevicesName[6] != NULL)
                return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, u8HDMI_CEC_DevicesName[6], strlen((const char *)u8HDMI_CEC_DevicesName[6]));
            break;

        case HWND_MENU_HDMI_CEC_DEVICE_LIST_H:
            if(u8HDMI_CEC_DevicesName[7] != NULL)
                return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, u8HDMI_CEC_DevicesName[7], strlen((const char *)u8HDMI_CEC_DevicesName[7]));
            break;

        case HWND_MENU_HDMI_CEC_DEVICE_LIST_I:
            if(u8HDMI_CEC_DevicesName[8] != NULL)
                return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, u8HDMI_CEC_DevicesName[8], strlen((const char *)u8HDMI_CEC_DevicesName[8]));
            break;

        case HWND_MENU_HDMI_CEC_DEVICE_LIST_J:
            if(u8HDMI_CEC_DevicesName[9] != NULL)
                return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, u8HDMI_CEC_DevicesName[9], strlen((const char *)u8HDMI_CEC_DevicesName[9]));
            break;
        // Temp define 10 devices in UI and source code
#endif // #if ENABLE_CEC
#if ENABLE_KEY_TO_SPEECH
        case HWND_MENU_OPTION_KTS_TEXT:
            return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8*)"KTS", KTS_TEXT_WORDS_LENGTH);
            break;

        case HWND_MENU_OPTION_KTS_TEXT_OPTION:
            if(stGenSetting.g_SysSetting.bKTSOn)
                u16TempID = en_str_On;
            else
                u16TempID = en_str_Off;
            break;
#endif
    }

    if (u16TempID != Empty)
        return MApp_ZUI_API_GetString(u16TempID);
    return 0; //for empty string....
}

///////////////////////////////////////////////////////////////////////////////
///  private  MApp_ZUI_ACT_GetMainMenuDynamicValue
///  [OSD page handler] dynamic integer value provider in MENU application
///
///  @param [in]       hwnd HWND     window handle we are processing
///
///  @return S16 integer value
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
S16 MApp_ZUI_ACT_GetMainMenuDynamicValue(HWND hwnd)
{
    switch(hwnd)
    {
        /*case HWND_MENU_DLG_SIGNAL_INFORMAT_QUALITY_PERCENT_BAR:
            return msAPI_Tuner_GetSignalQualityPercentage();

        case HWND_MENU_DLG_SIGNAL_INFORMAT_STRENGTH_PERCENT_BAR:
        {
            WORD SignalStrength;
            msAPI_Tuner_CheckSignalStrength(&SignalStrength);
            return SignalStrength;
        }*/
#if ENABLE_ATSC
        case HWND_MENU_CHANNEL_AUTO_SCAN_RESULT_PROGRESS_BAR:
            if((IsAtscInUse()) || (IsATVInUse()))
            {
                return MApp_Scan_ATSC_GetScanPercentageValue();
            }
            break;
#endif

    }

    return 0; //for empty  data
}

char* GUIDynamicList2String(GUI_ENUM_DYNAMIC_LIST_STATE bVal)
{
    switch (bVal)
    {
        case EN_DL_STATE_NORMAL:
            return "Normal";

        case EN_DL_STATE_DISABLED:
            return "Disable";

        case EN_DL_STATE_HIDDEN:
            return "Hidden";

        default:
            return " ";
    }
}

GUI_ENUM_DYNAMIC_LIST_STATE MApp_ZUI_ACT_QueryMainMenuItemStatus(HWND hwnd)
{
    GUI_ENUM_DYNAMIC_LIST_STATE bReturnValue = EN_DL_STATE_DISABLED;

    //printf("\e[31;1m >> %s(%d) \33[m \n", __FUNCTION__, hwnd);

    switch(hwnd)
    {
		case HWND_MENU_PICCOLOR_COLOR_RED:
        case HWND_MENU_PICCOLOR_COLOR_GREEN:
        case HWND_MENU_PICCOLOR_COLOR_BLUE:
            //from case MI_VIDEO_COLORTEMP_USER_MODE:
            if (ST_PICTURE.eColorTemp == MS_COLOR_TEMP_USER)
            {
                return EN_DL_STATE_NORMAL;
            }
            else
            {
                return EN_DL_STATE_DISABLED;
            }
            break;

		//from MENU_VIDEO_B =========================
        case HWND_MENU_PICMODE_BRIGHTNESS:
        case HWND_MENU_PICMODE_COLOR:
        case HWND_MENU_PICMODE_CONTRAST:
        case HWND_MENU_PICMODE_TINT:
        case HWND_MENU_PICMODE_SHARPNESS:
            #if PICTURE_USER_2
            if((ST_VIDEO.ePicture==PICTURE_USER) || (ST_VIDEO.ePicture==PICTURE_USER2) )
            #else
            if(ST_VIDEO.ePicture==PICTURE_USER)
            #endif
            {
                 if((hwnd ==HWND_MENU_PICMODE_COLOR)||(hwnd ==HWND_MENU_PICMODE_SHARPNESS))
                {
                   #if VGA_HDMI_YUV_POINT_TO_POINT
                    if(IsHDMIInUse()&&MDrv_PQ_Get_HDMIPCMode())
                    {
                        return EN_DL_STATE_DISABLED;
                    }
                    else if(IsVgaInUse())
                    {
                        return EN_DL_STATE_DISABLED;
                    }
                    else
                    #endif
                    {
                       return EN_DL_STATE_NORMAL;
                    }
                }

                if(hwnd ==HWND_MENU_PICMODE_TINT)
                {
                    if(IsAVInUse() || IsATVInUse() || IsSVInUse())//smc.chy 2010/05/08
                    {
                        switch (mvideo_vd_get_videosystem() )
                        {
                            case SIG_NTSC:
                            case SIG_NTSC_443:
                                return EN_DL_STATE_NORMAL;

                            case SIG_PAL:
                            case SIG_PAL_M:
                            case SIG_PAL_NC:
                            case SIG_SECAM:
                                return EN_DL_STATE_DISABLED;

                            default:
                                return EN_DL_STATE_DISABLED;
                        }
                    }
                    else
                    {
                        return EN_DL_STATE_DISABLED;
                    }
                }

                return EN_DL_STATE_NORMAL;
            }
            else
            {
                return EN_DL_STATE_DISABLED;
            }
            break;
    // ============================
    #if ENABLE_ATSC
        case HWND_MENU_OPTION_CCOPTION_ITEM_FONTSTYLE:
          #if (ENABLE == KOREAN_CC_ENABLE)
            return EN_DL_STATE_DISABLED;
          #endif

        case HWND_MENU_OPTION_CCOPTION_ITEM_FONTSIZE:
        case HWND_MENU_OPTION_CCOPTION_ITEM_FONTEDGESTYLE:
        case HWND_MENU_OPTION_CCOPTION_ITEM_FONTEDGECOLOR:
        case HWND_MENU_OPTION_CCOPTION_ITEM_FGCOLOR:
        case HWND_MENU_OPTION_CCOPTION_ITEM_BGCOLOR:
        case HWND_MENU_OPTION_CCOPTION_ITEM_FGOPACITY:
        case HWND_MENU_OPTION_CCOPTION_ITEM_BGOPACITY:
            if(stGenSetting.g_CaptionSetting.u8CSOptionMode != CAPTIONMENU_OPTIONMODE_CUSTOM)
                return EN_DL_STATE_DISABLED;
            break;


        case HWND_MENU_OPTION_CCOPTION_ITEM_WINDOWCOLOR:
        case HWND_MENU_OPTION_CCOPTION_ITEM_WINDOWOPACITY:
            if(stGenSetting.g_CaptionSetting.u8CSOptionMode == CAPTIONMENU_OPTIONMODE_CUSTOM && g_fCCAttrFlag.fCCAttr_EnableWindowOptionSetting)
                return EN_DL_STATE_NORMAL;
            else
                return EN_DL_STATE_DISABLED;
            break;


        case HWND_MENU_CHANNEL_LIST_ITEM0:
        case HWND_MENU_CHANNEL_LIST_ITEM1:
        case HWND_MENU_CHANNEL_LIST_ITEM2:
        case HWND_MENU_CHANNEL_LIST_ITEM3:
        case HWND_MENU_CHANNEL_LIST_ITEM4:
        case HWND_MENU_CHANNEL_LIST_ITEM5:
        case HWND_MENU_CHANNEL_LIST_ITEM6:
        case HWND_MENU_CHANNEL_LIST_ITEM7:
        case HWND_MENU_CHANNEL_LIST_ITEM8:
        case HWND_MENU_CHANNEL_LIST_ITEM9:
        {
            U16 u16CurrentIndex;
            U16 u16PageBaseIndex;

            u16CurrentIndex = MApp_ChanProc_GetCurProgIndex();
            u16PageBaseIndex = MApp_ChanProc_CalculateCurPageBaseIdx( u16CurrentIndex, MAX_NUM_OF_SRV_ITEM );
            u16CurrentIndex = _MApp_ZUI_ACT_MenuChannelListWindowMapToIndex(hwnd);

            if(bChannelListType == 0)//favorite list
            {
                if ( ( u16PageBaseIndex + u16CurrentIndex ) > stChSetting.u16MainListSrvNum )
                    return EN_DL_STATE_HIDDEN;
                else if(IS_HIDE_CH_ATSC(u16PageBaseIndex + u16CurrentIndex) && (MApp_ChanProc_GetCurProgIndex()!=(u16PageBaseIndex + u16CurrentIndex)))
                    return EN_DL_STATE_DISABLED;
            }
            else
            {
                if ( ( u16PageBaseIndex + u16CurrentIndex ) > stChSetting.u16MainListSrvNum )
                    return EN_DL_STATE_HIDDEN;
            }

            break;
        }


        case HWND_MENU_SOUND_EQ_ADVANCE_150HZ:
        case HWND_MENU_SOUND_EQ_ADVANCE_500HZ:
        case HWND_MENU_SOUND_EQ_ADVANCE_1000HZ:
        case HWND_MENU_SOUND_EQ_ADVANCE_2000HZ:
        case HWND_MENU_SOUND_EQ_ADVANCE_4000HZ:
        case HWND_MENU_SOUND_EQ_ADVANCE_BALANCE:
        {
            if(stGenSetting.g_SoundSetting.SoundMode != SOUND_MODE_USER)
                return EN_DL_STATE_DISABLED;

            break;
        }


        case HWND_MENU_TIME_SET_AUTO_SLEEP:
        {
            return EN_DL_STATE_HIDDEN;
        }


        case HWND_MENU_LOCK_SET_PASSWORD:
        {
            if(!MApp_MenuFunc_Setup_BlockSysEnterLockPage_Get())
                return EN_DL_STATE_DISABLED;

            break;
        }


        case HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM0:
        case HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM1:
        case HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM2:
        case HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM3:
        case HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM4:
        case HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM5:
        case HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM6:
        case HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM7:
        case HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM8:
        case HWND_MENU_LOCK_RRTDIMENTIONSUBPAGE_ITEM9:
        {
            if (_MApp_ZUI_ACT_RRTDimensionWindowMapToIndex(hwnd) < stGenSettingVchipRegion5.u8NoDimension)
            {
                return EN_DL_STATE_NORMAL;
            }
            return EN_DL_STATE_HIDDEN;
        }


        case HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM0:
        case HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM1:
        case HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM2:
        case HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM3:
        case HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM4:
        case HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM5:
        case HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM6:
        case HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM7:
        case HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM8:
        case HWND_MENU_LOCK_RRTADJUSTSUBPAGE_ITEM9:
        {
            U16 u16CurrentIndex;
            u16CurrentIndex = (g_u8CurrentRRT_Option/MAX_NUM_OF_RRT_ITEM) * MAX_NUM_OF_RRT_ITEM;
            u16CurrentIndex = stGenSettingVchipRegion5.stRegin5Dimension[g_u8CurrentRRT_Dimension].u8Values_Defined - u16CurrentIndex;
            if(_MApp_ZUI_ACT_RRTAdjustWindowMapToIndex(hwnd) <= u16CurrentIndex)
            {
                return EN_DL_STATE_NORMAL;
            }
            return EN_DL_STATE_HIDDEN;

            break;
        }


        case HWND_MENU_LOCK_PARENTAL_GUIDANCE:
        {
            if(IsDVBInUse())
                return EN_DL_STATE_NORMAL;
            else
                return EN_DL_STATE_HIDDEN;
        }


        case HWND_MENU_LOCK_INPUTBLOCKSUBPAGE_ITEM_TV:
        case HWND_MENU_LOCK_INPUTBLOCKSUBPAGE_ITEM_AV:
        case HWND_MENU_LOCK_INPUTBLOCKSUBPAGE_ITEM_SVIDEO:
        case HWND_MENU_LOCK_INPUTBLOCKSUBPAGE_ITEM_COMPONENT:
        case HWND_MENU_LOCK_INPUTBLOCKSUBPAGE_ITEM_HDMI:
        case HWND_MENU_LOCK_INPUTBLOCKSUBPAGE_ITEM_PC:
        {
            U8 i;
            for (i = 0; i < COUNTOF(_lock_source_items); i++)
            {
                if (hwnd == _lock_source_items[i])
                {
                    return EN_DL_STATE_NORMAL;
                }
            }
            return EN_DL_STATE_HIDDEN;
        }


        case HWND_MENU_LOCK_VCHIPSUBPAGE_ITEM6:
        {
            if(g_vchipPageType == EN_VCHIP_CANADAFRE)
                return EN_DL_STATE_HIDDEN;

            break;
        }


        case HWND_MENU_LOCK_VCHIPSUBPAGE_ITEM7:
        {
            if(g_vchipPageType != EN_VCHIP_MPAA)
                return EN_DL_STATE_HIDDEN;

            break;
        }

    #endif // #if ENABLE_ATSC
    // ============================


        case HWND_MENU_SOUND_AD_SWITCH:

          #if (ENABLE_SBTVD_DTV_SYSTEM)
            if(IS_SBTVD_APP)
            return EN_DL_STATE_HIDDEN;
            else
          #endif
            {
           #if ENABLE_DTV
            if(IsDVBInUse())
            {
                return EN_DL_STATE_NORMAL;
            }
            else
            {
            #if (ENABLE_ATSC_AD_FUNC)
                return EN_DL_STATE_NORMAL;
            #else
              #if(CHIP_FAMILY_TYPE == CHIP_FAMILY_WHISKY)
                 return EN_DL_STATE_HIDDEN;
              #else
                return EN_DL_STATE_DISABLED;
              #endif
            #endif
            }
           #else
            return EN_DL_STATE_HIDDEN;
           #endif
            }

    #if (  UI_SKIN_SEL == UI_SKIN_1920X1080X565 \
        || UI_SKIN_SEL == UI_SKIN_1366X768X565  \
        || UI_SKIN_SEL == UI_SKIN_1366X768X4444 \
        || UI_SKIN_SEL == UI_SKIN_1366X768X8888 \
        || UI_SKIN_SEL == UI_SKIN_960X540X565   \
        || (ENABLE_ATSC)                        \
        )
      #if(ENABLE_EWS)
        case HWND_MENU_EWS_LOCATION:
            return EN_DL_STATE_NORMAL;
      #else
        case HWND_MENU_EWS_LOCATION:
            return EN_DL_STATE_HIDDEN;
      #endif


      #if (!ENABLE_ATSC_TTS)
        case HWND_MENU_OPTION_TTS:
            return EN_DL_STATE_HIDDEN;
      #endif


      #if (ENABLE_EDID_SWITCH)
        case HWND_MENU_OPTION_EDID_SWITCH:
            if (IsHDMIInUse())
                return EN_DL_STATE_NORMAL;
            else
                return EN_DL_STATE_HIDDEN;
      #else
        case HWND_MENU_OPTION_EDID_SWITCH:
            return EN_DL_STATE_HIDDEN;
      #endif


        case HWND_MENU_LOCK_MAINSUBPAGE_ITEM_UNRATED:
          #if ENABLE_ATSC
            if (IsDVBInUse())
                return EN_DL_STATE_HIDDEN;
            else
            {
                if (stGenSetting.g_VChipSetting.u8VChipLockMode!= 0 && MApp_MenuFunc_Setup_BlockSysEnterLockPage_Get())
                    return EN_DL_STATE_NORMAL;
                else
                    return EN_DL_STATE_DISABLED;
            }
          #else
            return EN_DL_STATE_HIDDEN;
          #endif


        case HWND_MENU_OPTION_SETUPWIZARD:
          #if ENABLE_ATSC
            if(IsDVBInUse())
                return EN_DL_STATE_HIDDEN;
            else
                return EN_DL_STATE_NORMAL;
          #else
            return EN_DL_STATE_HIDDEN;
          #endif
            break;


        case HWND_MENU_LOCK_MAINSUBPAGE_ITEM_RRTSETTING:
        case HWND_MENU_LOCK_MAINSUBPAGE_ITEM_RESETRRT:
          #if ENABLE_ATSC
            if(IsDVBInUse())
                return EN_DL_STATE_HIDDEN;
            else
            {
                if ( (stGenSetting.g_VChipSetting.u8VChipLockMode!= 0)&&(stGenSettingVchipRegion5.u8NoDimension!=0) && IsAtscInUse() && MApp_MenuFunc_Setup_BlockSysEnterLockPage_Get())
                    return EN_DL_STATE_NORMAL;
                else
                    return EN_DL_STATE_DISABLED;
            }
          #else
            return EN_DL_STATE_HIDDEN;
          #endif
            break;


        case HWND_MENU_SOUND_AUDIO_LANGUAGE:
          #if( ENABLE_ATSC )
            if(IsAtscInUse())
            {
            #if(ENABLE_ATSC_VIDEO_DESC)
                if(stGenSetting.g_SoundSetting.enVideoDescription != EN_VIDEO_DESCRIPTION_ITEM_OFF)
                    return EN_DL_STATE_DISABLED;
            #endif
            }
            else if(IsATVInUse())
                return EN_DL_STATE_DISABLED;
            else
                return EN_DL_STATE_HIDDEN;
          #else
            return EN_DL_STATE_HIDDEN;
          #endif
            break;


        case HWND_MENU_LOCK_MAINSUBPAGE_ITEM_INPUTBLOCK:
          #if ENABLE_ATSC
            if ( (stGenSetting.g_VChipSetting.u8VChipLockMode != 0)
               &&(MApp_MenuFunc_Setup_BlockSysEnterLockPage_Get()) )
                return EN_DL_STATE_NORMAL;
            else
                return EN_DL_STATE_DISABLED;
          #else
            return EN_DL_STATE_HIDDEN;
          #endif


        case HWND_MENU_LOCK_MAINSUBPAGE_ITEM_US:
        case HWND_MENU_LOCK_MAINSUBPAGE_ITEM_CANADA:
          #if ENABLE_ATSC
            if(IsDVBInUse())
                return EN_DL_STATE_HIDDEN;
            else
            {
                if (IsVBISrcInUse() && stGenSetting.g_VChipSetting.u8VChipLockMode!= 0 && MApp_MenuFunc_Setup_BlockSysEnterLockPage_Get())
                    return EN_DL_STATE_NORMAL;
                else
                    return EN_DL_STATE_DISABLED;
            }
          #else
#if ((ATSC_CC == ATV_CC) || ENABLE_ISDB_ATV_VCHIP)
            if(IsDVBInUse())
            {
                return EN_DL_STATE_HIDDEN;
            }
            else
            {
                if (IsVBISrcInUse() && MApp_MenuFunc_Setup_BlockSysEnterLockPage_Get())
                {
                    return EN_DL_STATE_NORMAL;
                }
                else
                {
                    return EN_DL_STATE_DISABLED;
                }
            }
#endif
            return EN_DL_STATE_HIDDEN;
          #endif
            break;


        case HWND_MENU_TIME_AUTO_SYNC:
          #if ENABLE_ATSC
            if (IsDVBInUse())
                return EN_DL_STATE_HIDDEN;
          #else
            return EN_DL_STATE_HIDDEN;
          #endif
            break;

#if 0
        case HWND_MENU_TIME_DST:
          #if ENABLE_ATSC
            if (IsDVBInUse())
                return EN_DL_STATE_HIDDEN;
            else if(stGenSetting.g_SysSetting.fTimeAutoSync == TIME_AUTO_SYNC_ON)
            {
                return EN_DL_STATE_DISABLED;
            }
          #else
            return EN_DL_STATE_HIDDEN;
          #endif
            break;
#endif

        case HWND_MENU_SOUND_AUDIO_ONLY:
          #if ENABLE_ATSC
            if( IsAnyTVSourceInUse() )
                return EN_DL_STATE_NORMAL;
            else
                return EN_DL_STATE_DISABLED;
          #else
            return EN_DL_STATE_HIDDEN;
          #endif


        case HWND_MENU_SOUND_VIDEO_DESCRIPTION:
          #if ENABLE_ATSC
            if(IsAtscInUse())
                return EN_DL_STATE_NORMAL;
            else if(IsATVInUse())
                return EN_DL_STATE_DISABLED;
            else
            {
                return EN_DL_STATE_HIDDEN;
            }
          #else
            return EN_DL_STATE_HIDDEN;
          #endif


        case HWND_MENU_SOUND_MTS:
          #if ENABLE_ATSC
            if(IsATVInUse())
                return EN_DL_STATE_NORMAL;
            else if(IsAtscInUse())
                return EN_DL_STATE_DISABLED;
            else
                return EN_DL_STATE_HIDDEN;
          #else
            return EN_DL_STATE_HIDDEN;
          #endif


        case HWND_MENU_PICTURE_COLRANGE:
          #if ENABLE_ATSC
            if (IsDVBInUse())
                return EN_DL_STATE_HIDDEN;
            else if( IsHDMIInUse() )
                return EN_DL_STATE_NORMAL;
            else
                return EN_DL_STATE_DISABLED;
          #else
            return EN_DL_STATE_HIDDEN;
          #endif

        case HWND_MENU_PICTURE_GAMMA_ADJUST:
          #if ENABLE_GAMMA_ADJUST
              return EN_DL_STATE_NORMAL;
          #else
              return EN_DL_STATE_HIDDEN;
          #endif

        case HWND_MENU_CHANNEL_DTV_SIGNAL:
          #if ENABLE_ATSC
            if(IsAtscInUse())
            {
                if(enDTVSignalStatus == DTV_SIGNAL_NONE)
                {
                    return EN_DL_STATE_DISABLED;
                }
                else if ((stChSetting.u16MainListSrvNum == 0))
                {
                    return EN_DL_STATE_DISABLED;
                }
                else
                {
                    MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_DTV_SIGNAL_QLITY_BAR_BAD, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_DTV_SIGNAL_QLITY_BAR_NORMAL, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_DTV_SIGNAL_QLITY_BAR_GOOD, SW_SHOW);
                    return EN_DL_STATE_NORMAL;
                }
            }
            else
                return EN_DL_STATE_HIDDEN;
          #else
            return EN_DL_STATE_HIDDEN;
          #endif
            break;


        case HWND_MENU_CHANNEL_FAVORITE:
        case HWND_MENU_CHANNEL_SHOW_HIDE:
          #if ENABLE_ATSC
            if(IsAtscInUse()||IsATVInUse())
            {
                if(stChSetting.u16MainListSrvNum == 0)
                    return EN_DL_STATE_DISABLED;
                else if(stChSetting.u16TotalHideSrvNum >= stChSetting.u16MainListSrvNum)
                {
                    if(hwnd == HWND_MENU_CHANNEL_FAVORITE)
                        return EN_DL_STATE_DISABLED;
                }
            }
            else if(IsDVBInUse())
                return EN_DL_STATE_HIDDEN;
            else
                return EN_DL_STATE_DISABLED;
          #else
            return EN_DL_STATE_HIDDEN;
          #endif
            break;


        case HWND_MENU_OPTION_CLOSED_CAPTION:
          #if ENABLE_ATSC
            if(IsDVBInUse())
                return EN_DL_STATE_HIDDEN;
            else
                return EN_DL_STATE_NORMAL;
          #else
            return EN_DL_STATE_HIDDEN;
          #endif


        case HWND_MENU_CHANNEL_AUTO_SCAN_ATSC:
          #if ENABLE_ATSC
            if (IsAtscInUse() || IsATVInUse())
                return EN_DL_STATE_NORMAL;
            else if(IsDVBInUse())
                return EN_DL_STATE_HIDDEN;
            else
                return EN_DL_STATE_DISABLED;
          #else
            return EN_DL_STATE_HIDDEN;
          #endif


      #if (UI_SKIN_SEL ==  UI_SKIN_1366X768X565)

        case HWND_MENU_SOUND_DBX_TOTAL_SONICS:
        {
          #if (ENABLE_AUDIO_SURROUND_DBX == ENABLE)
            if(stGenSetting.g_SoundSetting.SurroundSoundMode == SURROUND_SYSTEM_DBX)
            {
                return EN_DL_STATE_NORMAL;
            }
            else
            {
                return EN_DL_STATE_DISABLED;
            }
          #else
            return EN_DL_STATE_HIDDEN;
          #endif
            break;
        }
		
        case HWND_MENU_SOUND_DBX_TOTAL_VOLUME:
        {
        #if (ENABLE_AUDIO_SURROUND_DBX == ENABLE)
            if(stGenSetting.g_SoundSetting.SurroundSoundMode == SURROUND_SYSTEM_DBX)
            {
                return EN_DL_STATE_NORMAL;
            }
            else
            {
                return EN_DL_STATE_DISABLED;
            }
        #else
            return EN_DL_STATE_HIDDEN;
        #endif

            break;
        }


        case HWND_MENU_SOUND_DBX_TOTAL_SURROUND:
        {
        #if (ENABLE_AUDIO_SURROUND_DBX == ENABLE)
            if ( (stGenSetting.g_SoundSetting.SurroundSoundMode == SURROUND_SYSTEM_DBX)\
            &&(stGenSetting.g_SoundSetting.DBXTV_TotVolMode != E_TOTVOL_NIGHT) )
            {
                return EN_DL_STATE_NORMAL;
            }
            else
            {
                return EN_DL_STATE_DISABLED;
            }
        #else
            return EN_DL_STATE_HIDDEN;
        #endif

            break;
        }

      #endif // #if (UI_SKIN_SEL ==  UI_SKIN_1366X768X565)


////==================================================================
        case HWND_MENU_CHANNEL_CHANNEL_NO:
        case HWND_MENU_CHANNEL_CHANNEL_LABEL:
        case HWND_MENU_CHANNEL_NON_TV:
        case HWND_MENU_PICTURE_3DNR:
		case HWND_MENU_SOUND_AUTO_VOLUME:
		case HWND_MENU_SOUND_SURROUND:
        case HWND_MENU_PICTURE_BACKLIGHT:
        case HWND_MENU_PICTURE_DLC:
        case HWND_MENU_SOUND_EQUALIZER:
        case HWND_MENU_SOUND_AVC:
        case HWND_MENU_TIME_TIME_FORMAT:
        case HWND_MENU_LOCK_MAINSUBPAGE_ITEM_SYSTEMLOCK:
        case HWND_MENU_OPTION_TRANSPARENT:
        case HWND_MENU_LOCK_ENTER_PASSWORD:
            return EN_DL_STATE_HIDDEN;
////==================================================================

    #endif

    ////==================================================================
    #if(ENABLE_S2)
        case HWND_MENU_CHANNEL_DISHSETUP:
            if(IsS2InUse())
                return EN_DL_STATE_NORMAL;
            else
                return EN_DL_STATE_HIDDEN;

      #if ENABLE_S2_DATABASE_DBM
        case HWND_MENU_CHANNEL_DB_MANGAGE:
            if (IsS2InUse())
                return EN_DL_STATE_NORMAL;
            else
                return EN_DL_STATE_HIDDEN;
      #endif
    #else
         case HWND_MENU_CHANNEL_DISHSETUP:
               return EN_DL_STATE_HIDDEN;
    #endif // #if(ENABLE_S2)
    ////==================================================================


        case HWND_MENU_COMMON_ADJ_ITEM1:
        {
            if (  g_mainpage_common == EN_COMMON_TIME_CLOCK_PAGE
               || g_mainpage_common == EN_COMMON_SOUND_BALANCE_PAGE
               || g_mainpage_common == EN_COMMON_SOUND_AUDIO_DELAY_PAGE
             #if (ENABLE_EXTERN_MFC_CHIP)
               || g_mainpage_common == EN_COMMON_SET_MFC_PAGE
             #endif
               )
                return EN_DL_STATE_DISABLED;
            else
                return EN_DL_STATE_NORMAL;

            break;
        }


        //from MENU_VIDEO_B =========================
        case HWND_MENU_COMMON_ADJ_ITEM2:
        case HWND_MENU_COMMON_ADJ_ITEM3:
        case HWND_MENU_COMMON_ADJ_ITEM4:
        case HWND_MENU_COMMON_ADJ_ITEM5:
        case HWND_MENU_COMMON_ADJ_ITEM6:
            if(g_mainpage_common ==EN_COMMON_PICTURE_MODE_PAGE)
            {
              #if PICTURE_USER_2
                if((ST_VIDEO.ePicture==PICTURE_USER) || (ST_VIDEO.ePicture==PICTURE_USER2) )
              #else
                if(ST_VIDEO.ePicture==PICTURE_USER)
              #endif
                {
                #if( DISABLE_ADJ_SHARPNESS_WHEN_PTP )
                    if( (hwnd ==HWND_MENU_COMMON_ADJ_ITEM5) // Sharpness
                       )
                    {
                        if ( MApp_Scaler_Check_PointToPoint_Mode(PQ_MAIN_WINDOW) )
                        {
                            return EN_DL_STATE_DISABLED;
                        }
                        else
                        {
                            return EN_DL_STATE_NORMAL;
                        }
                    }
                #endif

                    if (hwnd ==HWND_MENU_COMMON_ADJ_ITEM6) // Hue
                    {
                        if (IsAVInUse() || IsATVInUse())
                        {
                            switch (mvideo_vd_get_videosystem() )
                            {
                                case SIG_NTSC:
                                case SIG_NTSC_443:
                                    return EN_DL_STATE_NORMAL;
                                case SIG_PAL:
                                case SIG_PAL_M:
                                case SIG_PAL_NC:
                                case SIG_SECAM:
                                    return EN_DL_STATE_DISABLED;
                                default:
                                    return EN_DL_STATE_DISABLED;
                            }
                        }
                        else
                        {
                            return EN_DL_STATE_DISABLED;
                        }
                    }
                    return EN_DL_STATE_NORMAL;
                }
                else
                {
                    return EN_DL_STATE_DISABLED;
                }
            }
            else if (g_mainpage_common ==EN_COMMON_PICTURE_COLOR_PAGE)
            {
                if (hwnd >= HWND_MENU_COMMON_ADJ_ITEM5)
                    return EN_DL_STATE_HIDDEN;

                //from case MI_VIDEO_COLORTEMP_USER_MODE:
                if (ST_PICTURE.eColorTemp == MS_COLOR_TEMP_USER)
                {
                    return EN_DL_STATE_NORMAL;
                }
                else
                {
                    return EN_DL_STATE_DISABLED;
                }
            }

          #if ENABLE_GAMMA_ADJUST
            else if (g_mainpage_common ==EN_COMMON_GAMMA_ADJUST_PAGE)
            {
                if (hwnd >= HWND_MENU_COMMON_ADJ_ITEM5)
                    return EN_DL_STATE_HIDDEN;
            }
          #endif
            else if (  g_mainpage_common == EN_COMMON_SOUND_BALANCE_PAGE
                    || g_mainpage_common == EN_COMMON_SOUND_AUDIO_DELAY_PAGE
            )
            {
                if(hwnd >= HWND_MENU_COMMON_ADJ_ITEM3)
                    return EN_DL_STATE_HIDDEN;
                else
                    return EN_DL_STATE_NORMAL;
            }
            else if(g_mainpage_common == EN_COMMON_SOUND_SWITCH_PAGE)
            {
            #if (ENABLE_SBTVD_DTV_SYSTEM)
                if(IS_SBTVD_APP)
                    return EN_DL_STATE_HIDDEN;
                else
            #endif
                {
                  //from case MI_AD_SWITCH:
#if (ENABLE_ATSC_AD_FUNC)
                  if(hwnd >= HWND_MENU_COMMON_ADJ_ITEM4)
#else
                  if(hwnd >= HWND_MENU_COMMON_ADJ_ITEM3)
#endif
                      return EN_DL_STATE_HIDDEN;

#if(ENABLE_DVB_AUDIO_DESC)
                  if (stGenSetting.g_SoundSetting.bEnableAD)
                  {
                      return EN_DL_STATE_NORMAL;
                  }
                  else
#endif
                  {
                      return EN_DL_STATE_DISABLED;
                  }

                }

            }
            else if(g_mainpage_common == EN_COMMON_OFFTIMER_PAGE)
            {
                if(hwnd >= HWND_MENU_COMMON_ADJ_ITEM4)
                    return EN_DL_STATE_HIDDEN;
                if(stGenSetting.g_Time.cOffTimerFlag == EN_Time_OffTimer_Off)
                    return EN_DL_STATE_DISABLED;
                else
                    return EN_DL_STATE_NORMAL;
            }
            else if(g_mainpage_common == EN_COMMON_ONTIMER_PAGE)
            {
                if(stGenSetting.g_Time.cOnTimerFlag == EN_Time_OnTimer_Off)
                    return EN_DL_STATE_DISABLED;
                else
                    return EN_DL_STATE_NORMAL;
            }
            else if(g_mainpage_common == EN_COMMON_TIME_CLOCK_PAGE)
            {
                return EN_DL_STATE_NORMAL;
            }
        #if (ENABLE_EXTERN_MFC_CHIP)
            else if(g_mainpage_common == EN_COMMON_SET_MFC_PAGE)
            {
                if(hwnd >= HWND_MENU_COMMON_ADJ_ITEM4)
                    return EN_DL_STATE_HIDDEN;
                else
                    return EN_DL_STATE_NORMAL;
            }
        #endif
        #if ENABLE_ATSC_TTS
            else if(g_mainpage_common == EN_COMMON_OPTION_TTS_PAGE)
            {
                if(hwnd >= HWND_MENU_COMMON_ADJ_ITEM5)
                    return EN_DL_STATE_HIDDEN;
                if(stGenSetting.g_SysSetting.bTTSOn)
                    return EN_DL_STATE_NORMAL;
                else
                    return EN_DL_STATE_DISABLED;
            }
        #endif
            break;


        case HWND_MENU_OPTION_OSD_EFFECT:
          #if ENABLE_MAINPAGE_EFFECT
            return EN_DL_STATE_NORMAL;
          #else
            return EN_DL_STATE_HIDDEN;
          #endif
            break;


        case HWND_MENU_OPTION_HDMI_CEC:
        {
          #if ENABLE_CEC
            bReturnValue = EN_DL_STATE_NORMAL;
          #else
            bReturnValue = EN_DL_STATE_HIDDEN;
          #endif

            //printf("\e[31;1m[%d] HWND_MENU_OPTION_HDMI_CEC: %s \33[m \n", __LINE__, GUIDynamicList2String(bReturnValue));
            return bReturnValue;
            break;
        }


        case HWND_MENU_SOUND_AUDIO_DELAY:
        {
			return EN_DL_STATE_HIDDEN;
          #if (HW_SPDIF_ENABLE == ENABLE)
            bReturnValue = EN_DL_STATE_NORMAL;
          #else
            bReturnValue = EN_DL_STATE_HIDDEN;
          #endif

            //printf("\e[31;1m[%d] HWND_MENU_SOUND_AUDIO_DELAY: %s \33[m \n", __LINE__, GUIDynamicList2String(bReturnValue));
            return bReturnValue;
            break;
        }


        case HWND_MENU_SOUND_SPDIF_MODE:
        {
			return EN_DL_STATE_HIDDEN;
          #if (HW_SPDIF_ENABLE == ENABLE)
            if(IsDTVInUse() || IsHDMIInUse()||IsStorageInUse())
            {
                bReturnValue = EN_DL_STATE_NORMAL;
            }
            else
            {
                bReturnValue = EN_DL_STATE_DISABLED;
            }
          #else
            bReturnValue = EN_DL_STATE_HIDDEN;
          #endif

            //printf("\e[31;1m[%d] HWND_MENU_SOUND_SPDIF_MODE: %s \33[m \n", __LINE__, GUIDynamicList2String(bReturnValue));
            return bReturnValue;
            break;
        }
		case HWND_MENU_SOUND_EQMODE:
		#if SOUND_EQMODE_ENABLE
			return EN_DL_STATE_NORMAL;
		#else
			return EN_DL_STATE_HIDDEN;
		#endif
        case HWND_MENU_SOUND_TV_SPEAKER:
        {
			return EN_DL_STATE_HIDDEN;
            if (ARC_SUPPORT_PORT == 0) // no ARC support port
            {
                bReturnValue = EN_DL_STATE_DISABLED;
            }
        #if(ENABLE_CEC)
            else if ( msAPI_CEC_IsDeviceExist(E_LA_AUDIO_SYS) )
            {
                bReturnValue = EN_DL_STATE_NORMAL;
            }
        #endif
            else
            {
                bReturnValue = EN_DL_STATE_DISABLED;
            }

            //printf("\e[31;1m[%d] HWND_MENU_SOUND_TV_SPEAKER: %s \33[m \n", __LINE__, GUIDynamicList2String(bReturnValue));
            return bReturnValue;
            break;
        }

    //==========================================================================
    #if (UI_SKIN_SEL ==  UI_SKIN_1920X1080X565)
        case HWND_MENU_SOUND_DBX_TOTAL_SONICS:
          #if (ENABLE_AUDIO_SURROUND_DBX == ENABLE)
            if(stGenSetting.g_SoundSetting.SurroundSoundMode == SURROUND_SYSTEM_DBX)
            {
                return EN_DL_STATE_NORMAL;
            }
            else
            {
                return EN_DL_STATE_DISABLED;
            }
          #else
            return EN_DL_STATE_HIDDEN;
          #endif
            break;


        case HWND_MENU_SOUND_DBX_TOTAL_VOLUME:
          #if (ENABLE_AUDIO_SURROUND_DBX == ENABLE)
            if(stGenSetting.g_SoundSetting.SurroundSoundMode == SURROUND_SYSTEM_DBX)
            {
                return EN_DL_STATE_NORMAL;
            }
            else
            {
                return EN_DL_STATE_DISABLED;
            }
          #else
            return EN_DL_STATE_HIDDEN;
          #endif
            break;


        case HWND_MENU_SOUND_DBX_TOTAL_SURROUND:
          #if (ENABLE_AUDIO_SURROUND_DBX == ENABLE)
            if ( (stGenSetting.g_SoundSetting.SurroundSoundMode == SURROUND_SYSTEM_DBX)\
               &&(stGenSetting.g_SoundSetting.DBXTV_TotVolMode != E_TOTVOL_NIGHT) )
            {
                return EN_DL_STATE_NORMAL;
            }
            else
            {
                return EN_DL_STATE_DISABLED;
            }
          #else
            return EN_DL_STATE_HIDDEN;
          #endif
            break;

    #endif // #if (UI_SKIN_SEL ==  UI_SKIN_1920X1080X565)
    //==========================================================================


        case HWND_MENU_HDMI_CEC_HDMI:
          #if ENABLE_CEC
            return EN_DL_STATE_NORMAL;
          #else
            return EN_DL_STATE_HIDDEN;
          #endif
            break;


        case HWND_MENU_HDMI_CEC_ARC:
        {
         #if ENABLE_CEC
          #if (!ENABLE_ARC_CHANGE_SPDIF)
            if (ARC_SUPPORT_PORT == 0) // no ARC support port
            {
                bReturnValue = EN_DL_STATE_DISABLED;
            }
            else if (DB_HDMI_SETTING.g_bHdmiCecMode == DISABLE)
            {
                bReturnValue = EN_DL_STATE_DISABLED;
            }
            else
            {
                bReturnValue = EN_DL_STATE_NORMAL;
            }
          #else
            bReturnValue = EN_DL_STATE_DISABLED;
          #endif
         #else
            bReturnValue = EN_DL_STATE_HIDDEN;
         #endif

            //printf("\e[31;1m[%d] HWND_MENU_HDMI_CEC_ARC: %s \33[m \n", __LINE__, GUIDynamicList2String(bReturnValue));
            return bReturnValue;
            break;
        }


        case HWND_MENU_HDMI_CEC_AUTO_STANDBY:
        {
          #if ENABLE_CEC
            if(DB_HDMI_SETTING.g_bHdmiCecMode == DISABLE)
            {
                bReturnValue = EN_DL_STATE_DISABLED;
            }
            else
            {
                bReturnValue = EN_DL_STATE_NORMAL;
            }
          #else
            bReturnValue = EN_DL_STATE_HIDDEN;
          #endif

            //printf("\e[31;1m[%d] HWND_MENU_HDMI_CEC_ARC: %s \33[m \n", __LINE__, GUIDynamicList2String(bReturnValue));
            return bReturnValue;
            break;
        }


        case HWND_MENU_HDMI_CEC_AUTO_TV_ON:
        {
          #if ENABLE_CEC
            if(DB_HDMI_SETTING.g_bHdmiCecMode == DISABLE)
            {
                bReturnValue = EN_DL_STATE_DISABLED;
            }
            else
            {
                bReturnValue = EN_DL_STATE_NORMAL;
            }
          #else
            bReturnValue = EN_DL_STATE_HIDDEN;
          #endif

            //printf("\e[31;1m[%d] HWND_MENU_HDMI_CEC_ARC: %s \33[m \n", __LINE__, GUIDynamicList2String(bReturnValue));
            return bReturnValue;
            break;
        }


        case HWND_MENU_HDMI_CEC_DEVICE_CONTROL:
        {
          #if ENABLE_CEC
            if(DB_HDMI_SETTING.g_bHdmiCecMode == DISABLE)
            {
                bReturnValue = EN_DL_STATE_DISABLED;
            }
            else
            {
                bReturnValue = EN_DL_STATE_NORMAL;
            }
          #else
            bReturnValue = EN_DL_STATE_HIDDEN;
          #endif

            //printf("\e[31;1m[%d] HWND_MENU_HDMI_CEC_ARC: %s \33[m \n", __LINE__, GUIDynamicList2String(bReturnValue));
            return bReturnValue;
            break;
        }


        case HWND_MENU_HDMI_CEC_DEVICE_LIST:
        {
          #if ENABLE_CEC
            if(DB_HDMI_SETTING.g_bHdmiCecMode == DISABLE)
            {
                bReturnValue = EN_DL_STATE_DISABLED;
            }
            else
            {
                bReturnValue = EN_DL_STATE_NORMAL;
            }
          #else
            bReturnValue = EN_DL_STATE_HIDDEN;
          #endif

            //printf("\e[31;1m[%d] HWND_MENU_HDMI_CEC_ARC: %s \33[m \n", __LINE__, GUIDynamicList2String(bReturnValue));
            return bReturnValue;
            break;
        }


        case HWND_MENU_OPTION_HDMI_ARC:
        {
            return EN_DL_STATE_HIDDEN;
            break;
        }



    #if  ENABLE_3D_PROCESS
        case HWND_MENU_OPTION_3D_TO_2D:
        {
			return EN_DL_STATE_HIDDEN;
            #if ENABLE_DMP
            if(IsStorageInUse())
            {
                if ( MApp_MPlayer_IsPhotoPlaying()
                  #if ENABLE_MPLAYER_MOVIE
                   ||(MApp_MPlayer_IsMoviePlaying() && !MApi_XC_IsCurrentFrameBufferLessMode())
                  #endif
                    )
                {
                     return EN_DL_STATE_NORMAL;
                }
                else
                {
                     return EN_DL_STATE_DISABLED;
                }
            }
            else
            #endif
            {
                if(MApp_IsSrcHasSignal(MAIN_WINDOW))
                {
                     return EN_DL_STATE_NORMAL;
                }
                else
                {
                     return EN_DL_STATE_DISABLED;
                }
            }
            break;
        }
    #else
        case HWND_MENU_OPTION_3D_TO_2D:
            return EN_DL_STATE_HIDDEN;
            break;
    #endif

        // ========== SINGLELIST_ITEM1 ==========
        case HWND_MENU_SINGLELIST_ITEM1:
        {
            switch(MApp_ZUI_ACT_GetSingleListMode())
            {
                case EN_COMMON_SINGLELIST_ASPECT_RATIO:// en_str_AspectRatio_orignal
                {
                    if ( !MApp_Scaler_Is_AspectRatioSupported_ByUI(EN_AspectRatio_Original)  )
                        return EN_DL_STATE_HIDDEN;
                    else
                        return EN_DL_STATE_NORMAL;
                }

            #if (ENABLE_3D_PROCESS)
                case EN_COMMON_SINGLELIST_3D_TYPE: // Item1
                {
                    if( MApp_Scaler_Is_3DTypeSupported(0) ) // Item1
                        return EN_DL_STATE_NORMAL;
                    else
                        return EN_DL_STATE_DISABLED;
                }
            #endif

            #if (ENABLE_ATSC)
                case EN_COMMON_SINGLELIST_OSD_TIMEZONE:
                    return EN_DL_STATE_NORMAL;
            #endif
#if (ENABLE_LANGUAGE_SWITCH_LIST_MENU)
                case EN_COMMON_SINGLELIST_LANGUAE_PAGE:
                    if (MApp_ZUI_ACT_GetOsdAudLangIndexMax() >=1)
                        return EN_DL_STATE_NORMAL;
                     else
                         return EN_DL_STATE_HIDDEN;
#endif
                default:
                   return EN_DL_STATE_NORMAL;
            }
            break;
        }
        // ==========================================================


        // ========== SINGLELIST_ITEM2 ==========
        case HWND_MENU_SINGLELIST_ITEM2:
        {
            switch(MApp_ZUI_ACT_GetSingleListMode())
            {
                case EN_COMMON_SINGLELIST_ASPECT_RATIO:// en_str_4colon3
                    if( !MApp_Scaler_Is_AspectRatioSupported_ByUI(EN_AspectRatio_4X3) )
                        return EN_DL_STATE_HIDDEN;
                    else
                        return EN_DL_STATE_NORMAL;
                    break;

            #if (ENABLE_3D_PROCESS)
                case EN_COMMON_SINGLELIST_3D_TYPE: // For Item2
                {
                    if( MApp_Scaler_Is_3DTypeSupported(1) ) // Item2
                        return EN_DL_STATE_NORMAL;
                    else
                        return EN_DL_STATE_DISABLED;
                }
              #endif // #if ENABLE_3D_PROCESS

                case EN_COMMON_SINGLELIST_SURROUND_SOUND:
                {
                  #if (ENABLE_AUDIO_SURROUND_BBE== ENABLE )
                     return EN_DL_STATE_NORMAL;
                  #else
                     return EN_DL_STATE_HIDDEN;
                  #endif

                    break;
                }

            #if (ENABLE_ATSC)
                case EN_COMMON_SINGLELIST_OSD_TIMEZONE:
                    return EN_DL_STATE_NORMAL;
            #endif
#if (ENABLE_LANGUAGE_SWITCH_LIST_MENU)
                case EN_COMMON_SINGLELIST_LANGUAE_PAGE:
                    if (MApp_ZUI_ACT_GetOsdAudLangIndexMax() >=2)
                        return EN_DL_STATE_NORMAL;
                     else
                         return EN_DL_STATE_HIDDEN;
#endif
                default:
                    return EN_DL_STATE_NORMAL;
            }

            break;
        }
        // ==========================================================


        // ========== SINGLELIST_ITEM3 ==========
        case HWND_MENU_SINGLELIST_ITEM3:
            switch(MApp_ZUI_ACT_GetSingleListMode())
            {
                case EN_COMMON_SINGLELIST_ASPECT_RATIO: // en_str_16colon9
                    if( !MApp_Scaler_Is_AspectRatioSupported_ByUI(EN_AspectRatio_16X9)  )
                        return EN_DL_STATE_HIDDEN;
                    else
                        return EN_DL_STATE_NORMAL;
                    break;

                case EN_COMMON_SINGLELIST_SURROUND_SOUND:
                {
                #if (ENABLE_AUDIO_SURROUND_SRS  == ENABLE )
                     return EN_DL_STATE_NORMAL;
                #else
                     return EN_DL_STATE_HIDDEN;
                #endif
                }
                break;


                case EN_COMMON_SINGLELIST_TV_SPEAKER:
            #if(ENABLE_SCART_SVIDEO)
                case EN_COMMON_SINGLELIST_SCART_IN:
            #endif
                    return EN_DL_STATE_HIDDEN;

            #if (ENABLE_3D_PROCESS)
                case EN_COMMON_SINGLELIST_3D_TYPE: // Item3
                {
                    if( MApp_Scaler_Is_3DTypeSupported(2) ) // Item3
                        return EN_DL_STATE_NORMAL;
                    else
                        return EN_DL_STATE_DISABLED;
                }
           #endif

            #if (ENABLE_ATSC)
                case EN_COMMON_SINGLELIST_OSD_TIMEZONE:
                    return EN_DL_STATE_NORMAL;
            #endif
#if (ENABLE_LANGUAGE_SWITCH_LIST_MENU)
                case EN_COMMON_SINGLELIST_LANGUAE_PAGE:
                    if (MApp_ZUI_ACT_GetOsdAudLangIndexMax() >=3)
                        return EN_DL_STATE_NORMAL;
                     else
                         return EN_DL_STATE_HIDDEN;
#endif
                default:
                   return EN_DL_STATE_NORMAL;
            }
            break;
        // ==========================================================


        // ========== SINGLELIST_ITEM4 ==========
        case HWND_MENU_SINGLELIST_ITEM4:
            switch(MApp_ZUI_ACT_GetSingleListMode())
            {
            #if (ENABLE_ATSC)
                case EN_COMMON_SINGLELIST_MTS:
                    return EN_DL_STATE_HIDDEN;
            #endif

                case EN_COMMON_SINGLELIST_ASPECT_RATIO: //en_str_14colon9
                    if( !MApp_Scaler_Is_AspectRatioSupported_ByUI(EN_AspectRatio_14X9)  )
                        return EN_DL_STATE_HIDDEN;
                    else
                        return EN_DL_STATE_NORMAL;


                case EN_COMMON_SINGLELIST_SURROUND_SOUND:
                {
                  #if (ENABLE_AUDIO_SURROUND_VDS == ENABLE)
                     return EN_DL_STATE_NORMAL;
                  #else
                     return EN_DL_STATE_HIDDEN;
                  #endif
                }
                break;


                case EN_COMMON_SINGLELIST_TV_SPEAKER:
            #if(ENABLE_SCART_SVIDEO)
                case EN_COMMON_SINGLELIST_SCART_IN:
            #endif
                    return EN_DL_STATE_HIDDEN;


            #if (ENABLE_3D_PROCESS)
                case EN_COMMON_SINGLELIST_3D_TYPE: // Item4
                {
                    if( MApp_Scaler_Is_3DTypeSupported(3) ) // Item4
                        return EN_DL_STATE_NORMAL;
                    else
                        return EN_DL_STATE_DISABLED;
                }
           #endif

            #if (ENABLE_ATSC)
                case EN_COMMON_SINGLELIST_OSD_TIMEZONE:
                    return EN_DL_STATE_NORMAL;
                case EN_COMMON_SINGLELIST_MENU_LANGUAGE:
                    return EN_DL_STATE_HIDDEN;
            #endif

            #if (ENABLE_EDID_SWITCH)
                case EN_COMMON_SINGLELIST_EDID:
                    return EN_DL_STATE_HIDDEN;
            #endif
#if (ENABLE_LANGUAGE_SWITCH_LIST_MENU)
                case EN_COMMON_SINGLELIST_LANGUAE_PAGE:
                    if (MApp_ZUI_ACT_GetOsdAudLangIndexMax() >=4)
                        return EN_DL_STATE_NORMAL;
                     else
                         return EN_DL_STATE_HIDDEN;
#endif
                default:
                   return EN_DL_STATE_NORMAL;
            }
            break;
        // ==========================================================


        // ========== SINGLELIST_ITEM5 ==========
        case HWND_MENU_SINGLELIST_ITEM5:
            switch(MApp_ZUI_ACT_GetSingleListMode())
            {
				case EN_COMMON_SINGLELIST_NOISE_REDUCTION:
					return EN_DL_STATE_HIDDEN;
            #if (ENABLE_ATSC)
                case EN_COMMON_SINGLELIST_MTS:
                    return EN_DL_STATE_HIDDEN;
            #endif

                case EN_COMMON_SINGLELIST_AUTOSLEEP_TIMER:
              #if (ENABLE_EDID_SWITCH)
                case EN_COMMON_SINGLELIST_EDID:
              #endif
                    return EN_DL_STATE_HIDDEN;

                case EN_COMMON_SINGLELIST_ASPECT_RATIO://en_str_AspectRatio_zoom1
                {
                    if( !MApp_Scaler_Is_AspectRatioSupported_ByUI(EN_AspectRatio_Zoom1)  )
                        return EN_DL_STATE_HIDDEN;
                    else
                        return EN_DL_STATE_NORMAL;
                }
                case EN_COMMON_SINGLELIST_SURROUND_SOUND:
                {
                  #if (ENABLE_AUDIO_SURROUND_VSPK== ENABLE )
                     return EN_DL_STATE_NORMAL;
                #else
                     return EN_DL_STATE_HIDDEN;
                #endif
                }
                break;


                case EN_COMMON_SINGLELIST_TV_SPEAKER:
            #if(ENABLE_SCART_SVIDEO)
                case EN_COMMON_SINGLELIST_SCART_IN:
            #endif
                    return EN_DL_STATE_HIDDEN;


            #if (ENABLE_3D_PROCESS)
                case EN_COMMON_SINGLELIST_3D_TYPE: // Item5
                {
                    if( MApp_Scaler_Is_3DTypeSupported(4) ) // Item5
                        return EN_DL_STATE_NORMAL;
                    else
                        return EN_DL_STATE_DISABLED;
                }
            #endif

            #if (ENABLE_ATSC)
                case EN_COMMON_SINGLELIST_OSD_TIMEZONE:
                    return EN_DL_STATE_NORMAL;
                case EN_COMMON_SINGLELIST_MENU_LANGUAGE:
                    return EN_DL_STATE_HIDDEN;
            #endif
#if (ENABLE_LANGUAGE_SWITCH_LIST_MENU)
                case EN_COMMON_SINGLELIST_LANGUAE_PAGE:
                    if (MApp_ZUI_ACT_GetOsdAudLangIndexMax() >=5)
                        return EN_DL_STATE_NORMAL;
                     else
                         return EN_DL_STATE_HIDDEN;
#endif
                default:
                   return EN_DL_STATE_NORMAL;
            }
            break;
        // ==========================================================


        // ========== SINGLELIST_ITEM6 ==========
        case HWND_MENU_SINGLELIST_ITEM6:
            switch(MApp_ZUI_ACT_GetSingleListMode())
            {
              #if (ENABLE_ATSC)
                case EN_COMMON_SINGLELIST_MTS:
                    return EN_DL_STATE_HIDDEN;
              #endif

                case EN_COMMON_SINGLELIST_AUTOSLEEP_TIMER:
              #if (ENABLE_EDID_SWITCH)
                case EN_COMMON_SINGLELIST_EDID:
              #endif
                    return EN_DL_STATE_HIDDEN;
                case EN_COMMON_SINGLELIST_ASPECT_RATIO://en_str_AspectRatio_zoom2
                {
                    if( !MApp_Scaler_Is_AspectRatioSupported_ByUI(EN_AspectRatio_Zoom2)  )
                        return EN_DL_STATE_HIDDEN;
                    else
                        return EN_DL_STATE_NORMAL;
                }

                case EN_COMMON_SINGLELIST_NOISE_REDUCTION:
                   return EN_DL_STATE_HIDDEN;

                case EN_COMMON_SINGLELIST_MPEG_NOISE_REDUCTION:
                   return EN_DL_STATE_HIDDEN;

                case EN_COMMON_SINGLELIST_TV_SPEAKER:
            #if (ENABLE_SCART_SVIDEO)
                case EN_COMMON_SINGLELIST_SCART_IN:
            #endif
                    printf("\e[31;1m [%d]: %s \33[m \n", __LINE__, __FUNCTION__);
                    return EN_DL_STATE_HIDDEN;


            #if (ENABLE_3D_PROCESS)
                case EN_COMMON_SINGLELIST_3D_TYPE: // Item 6
                {
                    if( MApp_Scaler_Is_3DTypeSupported(5) ) // Item6
                        return EN_DL_STATE_NORMAL;
                    else
                        return EN_DL_STATE_DISABLED;
                }
            #endif

            #if (ENABLE_ATSC)
                case EN_COMMON_SINGLELIST_OSD_TIMEZONE:
                    return EN_DL_STATE_NORMAL;
                case EN_COMMON_SINGLELIST_MENU_LANGUAGE:
                    return EN_DL_STATE_HIDDEN;
            #endif
#if (ENABLE_LANGUAGE_SWITCH_LIST_MENU)
                case EN_COMMON_SINGLELIST_LANGUAE_PAGE:
                    if (MApp_ZUI_ACT_GetOsdAudLangIndexMax() >=6)
                        return EN_DL_STATE_NORMAL;
                     else
                         return EN_DL_STATE_HIDDEN;
#endif
                default:
                   return EN_DL_STATE_NORMAL;
            }
            break;
        // ==========================================================


        // ========== SINGLELIST_ITEM7 ==========
        case HWND_MENU_SINGLELIST_ITEM7:
            switch(MApp_ZUI_ACT_GetSingleListMode())
            {
            #if (ENABLE_ATSC)
                case EN_COMMON_SINGLELIST_MTS:
                    return EN_DL_STATE_HIDDEN;
            #endif

                case EN_COMMON_SINGLELIST_ASPECT_RATIO: //en_str_Just_Scan
                {
                    if( !MApp_Scaler_Is_AspectRatioSupported_ByUI(EN_AspectRatio_JustScan)  )
                        return EN_DL_STATE_HIDDEN;
                    else
                        return EN_DL_STATE_NORMAL;
                }

                case EN_COMMON_SINGLELIST_SURROUND_SOUND:
                {
                  #if (ENABLE_AUDIO_SURROUND_DBX == ENABLE )
                    return EN_DL_STATE_NORMAL;
                  #else
                    return EN_DL_STATE_HIDDEN;
                  #endif
                }
                   break;


                case EN_COMMON_SINGLELIST_AUTOSLEEP_TIMER:
                case EN_COMMON_SINGLELIST_NOISE_REDUCTION:
                case EN_COMMON_SINGLELIST_MPEG_NOISE_REDUCTION:
                case EN_COMMON_SINGLELIST_TV_SPEAKER:
            #if (ENABLE_EDID_SWITCH)
                case EN_COMMON_SINGLELIST_EDID:
            #endif
            #if(ENABLE_SCART_SVIDEO)
                case EN_COMMON_SINGLELIST_SCART_IN:
            #endif
#if  (ENABLE_HDR)
                case EN_COMMON_SINGLELIST_HDR:
#endif
                    return EN_DL_STATE_HIDDEN;


                case EN_COMMON_SINGLELIST_PARENTAL_GUIDANCE:
                #if (ENABLE_SBTVD_DTV_SYSTEM)
                    if(IS_SBTVD_APP)
                        return EN_DL_STATE_HIDDEN;
                    else
                #endif
                    {
                        return EN_DL_STATE_NORMAL;
                    }

            #if (ENABLE_3D_PROCESS)
                case EN_COMMON_SINGLELIST_3D_TYPE: // Item 7
                {
                    if( MApp_Scaler_Is_3DTypeSupported(6) ) // Item7
                        return EN_DL_STATE_NORMAL;
                    else
                        return EN_DL_STATE_DISABLED;
                }
            #endif

            #if (ENABLE_ATSC)
                case EN_COMMON_SINGLELIST_OSD_TIMEZONE:
                    return EN_DL_STATE_NORMAL;
                case EN_COMMON_SINGLELIST_MENU_LANGUAGE:
                    return EN_DL_STATE_HIDDEN;
            #endif
#if (ENABLE_LANGUAGE_SWITCH_LIST_MENU)
                case EN_COMMON_SINGLELIST_LANGUAE_PAGE:
                    if (MApp_ZUI_ACT_GetOsdAudLangIndexMax() >=7)
                        return EN_DL_STATE_NORMAL;
                     else
                         return EN_DL_STATE_HIDDEN;
#endif
                default:
                   return EN_DL_STATE_NORMAL;
            }
            break;
        // ==========================================================


        // ========== SINGLELIST_ITEM8 ==========
        case HWND_MENU_SINGLELIST_ITEM8:
            switch(MApp_ZUI_ACT_GetSingleListMode())
            {
            #if (ENABLE_ATSC)
                case EN_COMMON_SINGLELIST_MTS:
                    return EN_DL_STATE_HIDDEN;
            #endif

                case EN_COMMON_SINGLELIST_ASPECT_RATIO://en_str_AspectRatio_Panoramma
                {
                    if( !MApp_Scaler_Is_AspectRatioSupported_ByUI(EN_AspectRatio_Panorama) )
                        return EN_DL_STATE_HIDDEN;
                    else
                        return EN_DL_STATE_NORMAL;

                    break;
                }

                case EN_COMMON_SINGLELIST_AUTOSLEEP_TIMER:
                case EN_COMMON_SINGLELIST_NOISE_REDUCTION:
                case EN_COMMON_SINGLELIST_MPEG_NOISE_REDUCTION:
                case EN_COMMON_SINGLELIST_SURROUND_SOUND:
                case EN_COMMON_SINGLELIST_TV_SPEAKER:
            #if (ENABLE_EDID_SWITCH)
                case EN_COMMON_SINGLELIST_EDID:
            #endif
            #if(ENABLE_SCART_SVIDEO)
                case EN_COMMON_SINGLELIST_SCART_IN:
            #endif
            #if (ENABLE_3D_PROCESS)
                case EN_COMMON_SINGLELIST_3D_TYPE:
            #endif
#if  (ENABLE_HDR)
                case EN_COMMON_SINGLELIST_HDR:
#endif
                    return EN_DL_STATE_HIDDEN;

                case EN_COMMON_SINGLELIST_PARENTAL_GUIDANCE:
                  #if ENABLE_SBTVD_BRAZIL_APP
                   return EN_DL_STATE_HIDDEN;
                  #elif ENABLE_PARENTAL_GUIDANCE_CLASSIFICATION
                   return EN_DL_STATE_HIDDEN;
                  #else
                   return EN_DL_STATE_NORMAL;
                  #endif

            #if (ENABLE_ATSC)
                case EN_COMMON_SINGLELIST_OSD_TIMEZONE:
                    return EN_DL_STATE_HIDDEN;
                case EN_COMMON_SINGLELIST_MENU_LANGUAGE:
                    return EN_DL_STATE_HIDDEN;
            #endif
#if (ENABLE_LANGUAGE_SWITCH_LIST_MENU)
                case EN_COMMON_SINGLELIST_LANGUAE_PAGE:
                    if (MApp_ZUI_ACT_GetOsdAudLangIndexMax() >=8)
                        return EN_DL_STATE_NORMAL;
                     else
                         return EN_DL_STATE_HIDDEN;
#endif
                default:
                   return EN_DL_STATE_NORMAL;
            }
            break;
        // ==========================================================


        // ========== SINGLELIST_ITEM9 ==========
        case HWND_MENU_SINGLELIST_ITEM9:
            switch(MApp_ZUI_ACT_GetSingleListMode())
            {
            #if (ENABLE_ATSC)
                case EN_COMMON_SINGLELIST_MTS:
                    return EN_DL_STATE_HIDDEN;
            #endif

                case EN_COMMON_SINGLELIST_AUTOSLEEP_TIMER:
                case EN_COMMON_SINGLELIST_NOISE_REDUCTION:
                case EN_COMMON_SINGLELIST_MPEG_NOISE_REDUCTION:
                case EN_COMMON_SINGLELIST_SURROUND_SOUND:
                case EN_COMMON_SINGLELIST_TV_SPEAKER:
            #if (ENABLE_EDID_SWITCH)
                case EN_COMMON_SINGLELIST_EDID:
            #endif
            #if(ENABLE_SCART_SVIDEO)
                case EN_COMMON_SINGLELIST_SCART_IN:
            #endif
            #if (ENABLE_3D_PROCESS)
                case EN_COMMON_SINGLELIST_3D_TYPE:
            #endif
#if  (ENABLE_HDR)
                case EN_COMMON_SINGLELIST_HDR:
#endif
                    return EN_DL_STATE_HIDDEN;

                case EN_COMMON_SINGLELIST_PARENTAL_GUIDANCE:
                    #if (ENABLE_SBTVD_DTV_SYSTEM)
                        if(IS_SBTVD_APP)
                            return EN_DL_STATE_HIDDEN;
                        else
                    #endif
                        {
                        #if ENABLE_PARENTAL_GUIDANCE_CLASSIFICATION
                            return EN_DL_STATE_HIDDEN;
                        #else
                            return EN_DL_STATE_NORMAL;
                        #endif
                        }

                case EN_COMMON_SINGLELIST_ASPECT_RATIO: // P to P
                {
                    if( !MApp_Scaler_Is_AspectRatioSupported_ByUI(EN_AspectRatio_Point_to_Point) )
                    {
                        return EN_DL_STATE_HIDDEN;
                    }
                    else
                    {
                        return EN_DL_STATE_NORMAL;
                    }
                }

            #if (ENABLE_ATSC)
                case EN_COMMON_SINGLELIST_OSD_TIMEZONE:
                    return EN_DL_STATE_HIDDEN;
                case EN_COMMON_SINGLELIST_MENU_LANGUAGE:
                    return EN_DL_STATE_HIDDEN;
            #endif
#if (ENABLE_LANGUAGE_SWITCH_LIST_MENU)
                case EN_COMMON_SINGLELIST_LANGUAE_PAGE:
                    if (MApp_ZUI_ACT_GetOsdAudLangIndexMax() >=9)
                        return EN_DL_STATE_NORMAL;
                     else
                         return EN_DL_STATE_HIDDEN;
#endif
                default:
                   return EN_DL_STATE_NORMAL;
            }
            break;
        // ==========================================================


        // ========== SINGLELIST_ITEM10 ==========
        case HWND_MENU_SINGLELIST_ITEM10:
            switch(MApp_ZUI_ACT_GetSingleListMode())
            {
            #if (ENABLE_ATSC)
                case EN_COMMON_SINGLELIST_MTS:
                    return EN_DL_STATE_HIDDEN;
            #endif
                case EN_COMMON_SINGLELIST_AUTOSLEEP_TIMER:
                case EN_COMMON_SINGLELIST_ASPECT_RATIO:
                case EN_COMMON_SINGLELIST_NOISE_REDUCTION:
                case EN_COMMON_SINGLELIST_MPEG_NOISE_REDUCTION:
                case EN_COMMON_SINGLELIST_SURROUND_SOUND:
                case EN_COMMON_SINGLELIST_TV_SPEAKER:
                case EN_COMMON_SINGLELIST_SLEEP_TIMER:
            #if (ENABLE_EDID_SWITCH)
                case EN_COMMON_SINGLELIST_EDID:
            #endif
            #if (ENABLE_SCART_SVIDEO)
                case EN_COMMON_SINGLELIST_SCART_IN:
            #endif
            #if (ENABLE_3D_PROCESS)
                case EN_COMMON_SINGLELIST_3D_TYPE:
            #endif
#if  (ENABLE_HDR)
                case EN_COMMON_SINGLELIST_HDR:
#endif
                    return EN_DL_STATE_HIDDEN;

                case EN_COMMON_SINGLELIST_PARENTAL_GUIDANCE:
                    #if (ENABLE_SBTVD_DTV_SYSTEM)
                        if(IS_SBTVD_APP)
                            return EN_DL_STATE_HIDDEN;
                        else
                    #endif
                        {
                        #if (ENABLE_PARENTAL_GUIDANCE_CLASSIFICATION)
                            return EN_DL_STATE_HIDDEN;
                        #else
                            return EN_DL_STATE_NORMAL;
                        #endif
                        }


            #if (ATSC_CC == ATV_CC)
                case EN_COMMON_SINGLELIST_CC_OPTION:
                   return EN_DL_STATE_HIDDEN;
            #endif

            #if (ENABLE_ATSC)
                case EN_COMMON_SINGLELIST_OSD_TIMEZONE:
                    return EN_DL_STATE_HIDDEN;
                case EN_COMMON_SINGLELIST_MENU_LANGUAGE:
                    return EN_DL_STATE_HIDDEN;
            #endif
#if (ENABLE_LANGUAGE_SWITCH_LIST_MENU)
                case EN_COMMON_SINGLELIST_LANGUAE_PAGE:
                    if (MApp_ZUI_ACT_GetOsdAudLangIndexMax() >=10)
                        return EN_DL_STATE_NORMAL;
                     else
                         return EN_DL_STATE_HIDDEN;
#endif
                default:
                   return EN_DL_STATE_NORMAL;
            }
            break;
        // ==========================================================


        // ========== SINGLELIST_ITEM11 ==========
        case HWND_MENU_SINGLELIST_ITEM11:
            switch(MApp_ZUI_ACT_GetSingleListMode())
            {
            #if (ENABLE_ATSC)
                case EN_COMMON_SINGLELIST_MTS:
                    return EN_DL_STATE_HIDDEN;
            #endif
                case EN_COMMON_SINGLELIST_AUTOSLEEP_TIMER:
                case EN_COMMON_SINGLELIST_ASPECT_RATIO:
                case EN_COMMON_SINGLELIST_NOISE_REDUCTION:
                case EN_COMMON_SINGLELIST_MPEG_NOISE_REDUCTION:
                case EN_COMMON_SINGLELIST_SURROUND_SOUND:
                case EN_COMMON_SINGLELIST_TV_SPEAKER:
                case EN_COMMON_SINGLELIST_SLEEP_TIMER:
            #if (ENABLE_EDID_SWITCH)
                case EN_COMMON_SINGLELIST_EDID:
            #endif
            #if(ENABLE_SCART_SVIDEO)
                case EN_COMMON_SINGLELIST_SCART_IN:
            #endif
            #if (ENABLE_3D_PROCESS)
                case EN_COMMON_SINGLELIST_3D_TYPE:
            #endif
#if  (ENABLE_HDR)
                case EN_COMMON_SINGLELIST_HDR:
#endif
                    return EN_DL_STATE_HIDDEN;

                case EN_COMMON_SINGLELIST_PARENTAL_GUIDANCE:
                    #if (ENABLE_SBTVD_DTV_SYSTEM)
                        if(IS_SBTVD_APP)
                            return EN_DL_STATE_HIDDEN;
                        else
                    #endif
                        {
                        #if ENABLE_PARENTAL_GUIDANCE_CLASSIFICATION
                            return EN_DL_STATE_HIDDEN;
                        #else
                            return EN_DL_STATE_NORMAL;
                        #endif
                        }

            #if (ATSC_CC == ATV_CC)
                case EN_COMMON_SINGLELIST_CC_OPTION:
                   return EN_DL_STATE_HIDDEN;
            #endif

            #if (ENABLE_ATSC)
                case EN_COMMON_SINGLELIST_OSD_TIMEZONE:
                    return EN_DL_STATE_HIDDEN;
                case EN_COMMON_SINGLELIST_MENU_LANGUAGE:
                    return EN_DL_STATE_HIDDEN;
            #endif
#if (ENABLE_LANGUAGE_SWITCH_LIST_MENU)
                case EN_COMMON_SINGLELIST_LANGUAE_PAGE:
                    if (MApp_ZUI_ACT_GetOsdAudLangIndexMax() >=11)
                        return EN_DL_STATE_NORMAL;
                     else
                         return EN_DL_STATE_HIDDEN;
#endif
                default:
                   return EN_DL_STATE_NORMAL;
            }
            break;
        // ==========================================================


        // ========== SINGLELIST_ITEM12 ==========
        case HWND_MENU_SINGLELIST_ITEM12:
            switch (MApp_ZUI_ACT_GetSingleListMode())
            {
            #if (ENABLE_ATSC)
                case EN_COMMON_SINGLELIST_MTS:
                    return EN_DL_STATE_HIDDEN;
            #endif
                case EN_COMMON_SINGLELIST_AUTOSLEEP_TIMER:
                case EN_COMMON_SINGLELIST_ASPECT_RATIO:
                case EN_COMMON_SINGLELIST_NOISE_REDUCTION:
                case EN_COMMON_SINGLELIST_MPEG_NOISE_REDUCTION:
                case EN_COMMON_SINGLELIST_SURROUND_SOUND:
                case EN_COMMON_SINGLELIST_TV_SPEAKER:
                case EN_COMMON_SINGLELIST_SLEEP_TIMER:
            #if (ENABLE_EDID_SWITCH)
                case EN_COMMON_SINGLELIST_EDID:
            #endif
            #if(ENABLE_SCART_SVIDEO)
                case EN_COMMON_SINGLELIST_SCART_IN:
            #endif
            #if (ENABLE_3D_PROCESS)
                case EN_COMMON_SINGLELIST_3D_TYPE:
            #endif
#if  (ENABLE_HDR)
                case EN_COMMON_SINGLELIST_HDR:
#endif
                    return EN_DL_STATE_HIDDEN;


                case EN_COMMON_SINGLELIST_PARENTAL_GUIDANCE:
                    #if (ENABLE_SBTVD_DTV_SYSTEM)
                        if(IS_SBTVD_APP)
                            return EN_DL_STATE_HIDDEN;
                        else
                    #endif
                        {
                    #if ENABLE_PARENTAL_GUIDANCE_CLASSIFICATION
                            return EN_DL_STATE_HIDDEN;
                    #else
                            return EN_DL_STATE_NORMAL;
                    #endif
                        }

            #if (ATSC_CC == ATV_CC)
                case EN_COMMON_SINGLELIST_CC_OPTION:
                    return EN_DL_STATE_HIDDEN;
            #endif

            #if (ENABLE_ATSC)
                case EN_COMMON_SINGLELIST_OSD_TIMEZONE:
                    return EN_DL_STATE_HIDDEN;
                case EN_COMMON_SINGLELIST_MENU_LANGUAGE:
                    return EN_DL_STATE_HIDDEN;
            #endif
#if (ENABLE_LANGUAGE_SWITCH_LIST_MENU)
                case EN_COMMON_SINGLELIST_LANGUAE_PAGE:
                    if (MApp_ZUI_ACT_GetOsdAudLangIndexMax() >=12)
                        return EN_DL_STATE_NORMAL;
                     else
                         return EN_DL_STATE_HIDDEN;
#endif
                default:
                    return EN_DL_STATE_NORMAL;
            }
            break;
        // ==========================================================


        // ========== SINGLELIST_ITEM13 ==========
        case HWND_MENU_SINGLELIST_ITEM13:
            switch(MApp_ZUI_ACT_GetSingleListMode())
            {
            #if (ENABLE_ATSC)
                case EN_COMMON_SINGLELIST_MTS:
                    return EN_DL_STATE_HIDDEN;
            #endif
                case EN_COMMON_SINGLELIST_AUTOSLEEP_TIMER:
                case EN_COMMON_SINGLELIST_ASPECT_RATIO:
                case EN_COMMON_SINGLELIST_NOISE_REDUCTION:
                case EN_COMMON_SINGLELIST_MPEG_NOISE_REDUCTION:
                case EN_COMMON_SINGLELIST_SURROUND_SOUND:
                case EN_COMMON_SINGLELIST_TV_SPEAKER:
            #if(ENABLE_SCART_SVIDEO)
                case EN_COMMON_SINGLELIST_SCART_IN:
            #endif
                case EN_COMMON_SINGLELIST_SLEEP_TIMER:
            #if (ENABLE_EDID_SWITCH)
                case EN_COMMON_SINGLELIST_EDID:
            #endif
            #if (ENABLE_3D_PROCESS)
                case EN_COMMON_SINGLELIST_3D_TYPE:
            #endif
#if  (ENABLE_HDR)
                case EN_COMMON_SINGLELIST_HDR:
#endif
                    return EN_DL_STATE_HIDDEN;

                case EN_COMMON_SINGLELIST_PARENTAL_GUIDANCE:
                    #if (ENABLE_SBTVD_DTV_SYSTEM)
                        if(IS_SBTVD_APP)
                            return EN_DL_STATE_HIDDEN;
                        else
                    #endif
                        {
                    #if ENABLE_PARENTAL_GUIDANCE_CLASSIFICATION
                            return EN_DL_STATE_HIDDEN;
                    #else
                            return EN_DL_STATE_NORMAL;
                    #endif
                        }

            #if (ATSC_CC == ATV_CC)
                case EN_COMMON_SINGLELIST_CC_OPTION:
                   return EN_DL_STATE_HIDDEN;
            #endif

            #if (ENABLE_ATSC)
                case EN_COMMON_SINGLELIST_OSD_TIMEZONE:
                    return EN_DL_STATE_HIDDEN;
                case EN_COMMON_SINGLELIST_MENU_LANGUAGE:
                    return EN_DL_STATE_HIDDEN;
            #endif
#if (ENABLE_LANGUAGE_SWITCH_LIST_MENU)
                case EN_COMMON_SINGLELIST_LANGUAE_PAGE:
                    if (MApp_ZUI_ACT_GetOsdAudLangIndexMax() >=13)
                        return EN_DL_STATE_NORMAL;
                     else
                         return EN_DL_STATE_HIDDEN;
#endif
                default:
                   return EN_DL_STATE_NORMAL;
            }
            break;
        // ==========================================================


        // ========== SINGLELIST_ITEM14 ==========
        case HWND_MENU_SINGLELIST_ITEM14:
            switch(MApp_ZUI_ACT_GetSingleListMode())
            {
            #if (ENABLE_ATSC)
                case EN_COMMON_SINGLELIST_MTS:
                    return EN_DL_STATE_HIDDEN;
            #endif
                case EN_COMMON_SINGLELIST_AUTOSLEEP_TIMER:
                case EN_COMMON_SINGLELIST_ASPECT_RATIO:
                case EN_COMMON_SINGLELIST_NOISE_REDUCTION:
                case EN_COMMON_SINGLELIST_MPEG_NOISE_REDUCTION:
                case EN_COMMON_SINGLELIST_SURROUND_SOUND:
                case EN_COMMON_SINGLELIST_TV_SPEAKER:
            #if(ENABLE_SCART_SVIDEO)
                case EN_COMMON_SINGLELIST_SCART_IN:
            #endif
                case EN_COMMON_SINGLELIST_SLEEP_TIMER:
            #if (ENABLE_EDID_SWITCH)
                case EN_COMMON_SINGLELIST_EDID:
            #endif
            #if (ENABLE_3D_PROCESS)
                case EN_COMMON_SINGLELIST_3D_TYPE:
            #endif
#if  (ENABLE_HDR)
                case EN_COMMON_SINGLELIST_HDR:
#endif
                    return EN_DL_STATE_HIDDEN;

                case EN_COMMON_SINGLELIST_PARENTAL_GUIDANCE:
                    #if (ENABLE_SBTVD_DTV_SYSTEM)
                        if(IS_SBTVD_APP)
                            return EN_DL_STATE_HIDDEN;
                        else
                    #endif
                        {
                    #if ENABLE_PARENTAL_GUIDANCE_CLASSIFICATION
                            return EN_DL_STATE_HIDDEN;
                    #else
                            return EN_DL_STATE_NORMAL;
                    #endif
                        }

            #if (ATSC_CC == ATV_CC)
                case EN_COMMON_SINGLELIST_CC_OPTION:
                   return EN_DL_STATE_HIDDEN;
            #endif

            #if (ENABLE_ATSC)
                case EN_COMMON_SINGLELIST_OSD_TIMEZONE:
                    return EN_DL_STATE_HIDDEN;
                case EN_COMMON_SINGLELIST_MENU_LANGUAGE:
                    return EN_DL_STATE_HIDDEN;
            #endif
#if (ENABLE_LANGUAGE_SWITCH_LIST_MENU)
                case EN_COMMON_SINGLELIST_LANGUAE_PAGE:
                    if (MApp_ZUI_ACT_GetOsdAudLangIndexMax() >=14)
                        return EN_DL_STATE_NORMAL;
                     else
                         return EN_DL_STATE_HIDDEN;
#endif
                default:
                   return EN_DL_STATE_NORMAL;
            }
            break;
        // ==========================================================


        // ========== SINGLELIST_ITEM15 ==========
        case HWND_MENU_SINGLELIST_ITEM15:
            switch (MApp_ZUI_ACT_GetSingleListMode())
            {
            #if (ENABLE_ATSC)
                case EN_COMMON_SINGLELIST_MTS:
                    return EN_DL_STATE_HIDDEN;
            #endif
                case EN_COMMON_SINGLELIST_AUTOSLEEP_TIMER:
                case EN_COMMON_SINGLELIST_ASPECT_RATIO:
                case EN_COMMON_SINGLELIST_NOISE_REDUCTION:
                case EN_COMMON_SINGLELIST_MPEG_NOISE_REDUCTION:
                case EN_COMMON_SINGLELIST_SURROUND_SOUND:
                case EN_COMMON_SINGLELIST_TV_SPEAKER:
            #if(ENABLE_SCART_SVIDEO)
                case EN_COMMON_SINGLELIST_SCART_IN:
            #endif
                case EN_COMMON_SINGLELIST_SLEEP_TIMER:
            #if (ENABLE_EDID_SWITCH)
                case EN_COMMON_SINGLELIST_EDID:
            #endif
            #if (ENABLE_3D_PROCESS)
                case EN_COMMON_SINGLELIST_3D_TYPE:
            #endif
#if  (ENABLE_HDR)
                case EN_COMMON_SINGLELIST_HDR:
#endif
                    return EN_DL_STATE_HIDDEN;

                case EN_COMMON_SINGLELIST_PARENTAL_GUIDANCE:
                    #if (ENABLE_SBTVD_DTV_SYSTEM)
                        if(IS_SBTVD_APP)
                            return EN_DL_STATE_HIDDEN;
                        else
                    #endif
                        {
                    #if ENABLE_PARENTAL_GUIDANCE_CLASSIFICATION
                            return EN_DL_STATE_HIDDEN;
                    #else
                            return EN_DL_STATE_NORMAL;
                    #endif
                        }


            #if (ATSC_CC == ATV_CC)
                case EN_COMMON_SINGLELIST_CC_OPTION:
                   return EN_DL_STATE_HIDDEN;
            #endif

            #if (ENABLE_ATSC)
                case EN_COMMON_SINGLELIST_OSD_TIMEZONE:
                    return EN_DL_STATE_HIDDEN;
                case EN_COMMON_SINGLELIST_MENU_LANGUAGE:
                    return EN_DL_STATE_HIDDEN;
            #endif
#if (ENABLE_LANGUAGE_SWITCH_LIST_MENU)
                case EN_COMMON_SINGLELIST_LANGUAE_PAGE:
                    if (MApp_ZUI_ACT_GetOsdAudLangIndexMax() >=15)
                        return EN_DL_STATE_NORMAL;
                     else
                         return EN_DL_STATE_HIDDEN;
#endif
                default:
                   return EN_DL_STATE_NORMAL;
            }
            break;
        // ==========================================================


        // ========== SINGLELIST_ITEM16 ==========
        case HWND_MENU_SINGLELIST_ITEM16:
            switch (MApp_ZUI_ACT_GetSingleListMode())
            {
            #if (ENABLE_ATSC)
                case EN_COMMON_SINGLELIST_MTS:
                    return EN_DL_STATE_HIDDEN;
            #endif

                case EN_COMMON_SINGLELIST_AUTOSLEEP_TIMER:
                case EN_COMMON_SINGLELIST_ASPECT_RATIO:
                case EN_COMMON_SINGLELIST_NOISE_REDUCTION:
                case EN_COMMON_SINGLELIST_MPEG_NOISE_REDUCTION:
                case EN_COMMON_SINGLELIST_SURROUND_SOUND:
                case EN_COMMON_SINGLELIST_TV_SPEAKER:
            #if(ENABLE_SCART_SVIDEO)
                case EN_COMMON_SINGLELIST_SCART_IN:
            #endif
                case EN_COMMON_SINGLELIST_SLEEP_TIMER:
            #if (ENABLE_EDID_SWITCH)
                case EN_COMMON_SINGLELIST_EDID:
            #endif
            #if (ENABLE_3D_PROCESS)
                case EN_COMMON_SINGLELIST_3D_TYPE:
            #endif
#if  (ENABLE_HDR)
                case EN_COMMON_SINGLELIST_HDR:
#endif
                    return EN_DL_STATE_HIDDEN;

                case EN_COMMON_SINGLELIST_PARENTAL_GUIDANCE:
                    #if (ENABLE_SBTVD_DTV_SYSTEM)
                        if(IS_SBTVD_APP)
                            return EN_DL_STATE_HIDDEN;
                        else
                    #endif
                        {
                    #if ENABLE_PARENTAL_GUIDANCE_CLASSIFICATION
                            return EN_DL_STATE_HIDDEN;
                    #else
                            return EN_DL_STATE_NORMAL;
                    #endif
                        }


            #if (ATSC_CC == ATV_CC)
                case EN_COMMON_SINGLELIST_CC_OPTION:
                    return EN_DL_STATE_HIDDEN;
            #endif


            #if (ENABLE_ATSC)
                case EN_COMMON_SINGLELIST_OSD_TIMEZONE:
                    return EN_DL_STATE_HIDDEN;
                case EN_COMMON_SINGLELIST_MENU_LANGUAGE:
                    return EN_DL_STATE_HIDDEN;
            #endif
#if (ENABLE_LANGUAGE_SWITCH_LIST_MENU)
                case EN_COMMON_SINGLELIST_LANGUAE_PAGE:
                    if (MApp_ZUI_ACT_GetOsdAudLangIndexMax() >=16)
                        return EN_DL_STATE_NORMAL;
                     else
                         return EN_DL_STATE_HIDDEN;
#endif

                default:
                   return EN_DL_STATE_NORMAL;
            }
            break;
        // ==========================================================

        // ========== SINGLELIST_ITEM17 ==========
        case HWND_MENU_SINGLELIST_ITEM17:
            switch (MApp_ZUI_ACT_GetSingleListMode())
            {
                case EN_COMMON_SINGLELIST_PARENTAL_GUIDANCE:
                    #if ENABLE_ZIGGO
                        return EN_DL_STATE_NORMAL;
                    #elif ENABLE_PARENTAL_GUIDANCE_CLASSIFICATION
                        return EN_DL_STATE_HIDDEN;
                    #else
                        return EN_DL_STATE_HIDDEN;
                    #endif
                default:
                   return EN_DL_STATE_HIDDEN;
            }
            break;
        // ==========================================================




        case HWND_MENU_PICTURE_NOISE_REDUCTION: //from case MI_NOT_RGB_MODE:
        {

			
			//SMC 20110421 --增加酒店功能-- --A-->> 		
            //from case MI_NOT_RGB_MODE:
            if (IsStorageInUse())//smc.chy 2010/04/29
            {
                return EN_DL_STATE_DISABLED;
            }
             else  if(IsVgaInUse()!=TRUE)
            {
                return EN_DL_STATE_NORMAL;
            }
            else
            {
                return EN_DL_STATE_DISABLED;
            }
            break;
        }


        case HWND_MENU_PICTURE_MPEG_NOISE_REDUCTION: //from case MI_NOT_RGB_MODE:
        {
			return EN_DL_STATE_HIDDEN;
            XC_ApiStatus stXC_WinTime_Info;

            if(MApi_XC_GetStatus(&stXC_WinTime_Info, MAIN_WINDOW) == FALSE)
            {
                ASSERT(0);
            }

            if(IsVgaInUse()||(IsHDMIInUse()&&(stXC_WinTime_Info.bMemFmt422==FALSE))||stXC_WinTime_Info.bFBL==TRUE)
            {
                return EN_DL_STATE_DISABLED;
            }
            else
            {
                return EN_DL_STATE_NORMAL;
            }

            break;
        }


        case HWND_MENU_PICTURE_PC_ADJUST:
			return EN_DL_STATE_HIDDEN;
            //from case MI_PC_ONLY:
            if(IsVgaInUse())
            {
                return EN_DL_STATE_NORMAL;
            }
            else
            {
                return EN_DL_STATE_DISABLED;
            }
            break;

#if(UI_SKIN_SEL ==  UI_SKIN_1920X1080X565)
        case  HWND_MENU_PICTURE_HDR:
  #if  (ENABLE_HDR)
                return EN_DL_STATE_NORMAL;
  #else
                return EN_DL_STATE_HIDDEN;
  #endif
            break;
#endif

        case HWND_MENU_PICTURE_ASPECT_RATIO:
			return EN_DL_STATE_HIDDEN;
          #if (ENABLE_PIP)
            if((MApp_Get_PIPMode() == EN_PIP_MODE_POP)||(MApp_Get_PIPMode() == EN_PIP_MODE_POP_FULL))
            {
                return EN_DL_STATE_DISABLED;
            }
            else
          #endif
            {
           #if ENABLE_DMP
           // if (IsStorageInUse() && MApp_MPlayer_QueryMoviePlayMode() == E_MPLAYER_MOVIE_PAUSE) //wht120726_2  remove 
				if ((IsStorageInUse() && MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_PHOTO)
				|| !MApp_IsSrcHasSignal(MAIN_WINDOW)) //wht120726_3  add
				{
                return EN_DL_STATE_DISABLED;
				}
				else
				#endif
				{
				if (IsStorageInUse()) //smc.chy 2010/05/21
				{            
	            if((MApp_MPlayer_QueryCurrentMediaType() ==E_MPLAYER_TYPE_MOVIE||MApp_MPlayer_QueryCurrentMediaType() ==E_MPLAYER_TYPE_PHOTO)
					&& (MApp_DMP_GetDmpFlag()& DMP_FLAG_MEDIA_FILE_PLAYING))//truth.xu add 20100827
	            	{
				     if(MApi_XC_IsCurrentFrameBufferLessMode() || g_bForceToFB)
			                return EN_DL_STATE_DISABLED;
				     else
			                return EN_DL_STATE_NORMAL;
			         }
		     	else	     
                	return EN_DL_STATE_DISABLED;
				}
				else
				{
                return EN_DL_STATE_NORMAL;
				}
				}
            }
            break;

        case HWND_MENU_PICTURE_PIP:
          #if (ENABLE_PIP)
            //PIP Limitations: If current input source is MM or Internet APs, do not allow entering PIP/POP mode.
            if(IsPIPSupported())
            {
                return EN_DL_STATE_NORMAL;
            }
            else
          #endif
            {
                return EN_DL_STATE_HIDDEN;
            }
            break;

    #if (ENABLE_PIP)
        case HWND_MENU_PIP_SUBSRC:
            if(MApp_Get_PIPMode() == EN_PIP_MODE_OFF)
            {
                return EN_DL_STATE_DISABLED;
            }
            else
            {
                return EN_DL_STATE_NORMAL;
            }

        case HWND_MENU_PIP_SOUND_SRC:
        case HWND_MENU_PIP_SWAP:
            if(IsStorageInUse()||(MApp_Get_PIPMode() == EN_PIP_MODE_OFF) )
            {
                return EN_DL_STATE_DISABLED;
            }
            else
            {
                return EN_DL_STATE_NORMAL;
            }

        case HWND_MENU_PIP_SIZE:
        case HWND_MENU_PIP_POSITION:
        case HWND_MENU_PIP_BORDER:
            if(IsPIPSupported() && MApp_Get_PIPMode() == EN_PIP_MODE_PIP )
            {
                return EN_DL_STATE_NORMAL;
            }
            else
            {
                return EN_DL_STATE_DISABLED;
            }
    #endif // #if (ENABLE_PIP)


        //from MENU_CHANNEL_A ===========================
        case HWND_MENU_CHANNEL_ANTENNA:
        {
        #if ENABLE_ATSC_MENU_UI
          #if ENABLE_ATSC_MAIN_MENU_CHANNEL_PAGE
            if(IsAtscInUse()|| IsATVInUse())
            {
            #if ENABLE_ATSC_CHLIST_DISP_TOGETHER
                return EN_DL_STATE_HIDDEN;
            #else
                return EN_DL_STATE_NORMAL;
            #endif
            }
            else if(IsDVBInUse())
            {
                return EN_DL_STATE_HIDDEN;
            }
            else
            {
                return EN_DL_STATE_DISABLED;
            }
          #endif
        #endif
        #if(ENABLE_DVB_TAIWAN_APP)
            if(msAPI_InputSrcType_InUsedType(MAIN_WINDOW,EN_SYS_INPUT_SOURCE_TYPE_ATV))
            {
                return EN_DL_STATE_NORMAL;
            }
            else
            {
                return EN_DL_STATE_DISABLED;
            }
        #else
            return EN_DL_STATE_HIDDEN;
        #endif
        }


        case HWND_MENU_CHANNEL_CI_INFORMATION:
        {
        #if(ENABLE_CI_FUNCTION)
          #if (ENABLE_DTV == 0)
            return EN_DL_STATE_HIDDEN;
          #else
            if ( IsDTVInUse()
              #if ENABLE_S2
               ||IsS2InUse()
              #endif
               )
            {
                return EN_DL_STATE_NORMAL;
            }
            else
            {
                return EN_DL_STATE_DISABLED;
            }
          #endif
        #else
            return EN_DL_STATE_HIDDEN;
        #endif
        }


        case HWND_MENU_CHANNEL_SW_OAD_UPGRADE:
        {
        #if ( ENABLE_OAD && ENABLE_DTV )

         #if ENABLE_SBTVD_BRAZIL_APP
            return EN_DL_STATE_HIDDEN;
         #else

          #if (ENABLE_SOFTWAREUPDATE)
            if (IsDTVInUse())
            {
                return EN_DL_STATE_NORMAL;
            }
            else
            {
                return EN_DL_STATE_DISABLED;
            }
          #else
            return EN_DL_STATE_HIDDEN;
          #endif

         #endif

        #else // #if ( ENABLE_OAD && ENABLE_DTV )

            return EN_DL_STATE_HIDDEN;

        #endif
        }


        case HWND_MENU_CHANNEL_SW_OAD_TUNING:
        {
        #if ( ENABLE_OAD && ENABLE_DTV )

         #if (ENABLE_SBTVD_DTV_SYSTEM)
             if(IS_SBTVD_APP)
                return EN_DL_STATE_HIDDEN;
             else
         #endif
             {
                  #if (ENABLE_SOFTWAREUPDATE)
                    if (IsDTVInUse() && stGenSetting.g_SysSetting.fSoftwareUpdate)
                    {
                        return EN_DL_STATE_NORMAL;
                    }
                    else
                    {
                        return EN_DL_STATE_DISABLED;
                    }
                  #else
                    return EN_DL_STATE_HIDDEN;
                  #endif
             }
        #else // #if ( ENABLE_OAD && ENABLE_DTV )
            return EN_DL_STATE_HIDDEN;
        #endif
        }


        case HWND_MENU_CHANNEL_SW_USB_UPGRADE:
            return EN_DL_STATE_NORMAL;


        case HWND_MENU_CHANNEL_5V_ANTENNA:
        {
        #if (ENABLE_SBTVD_DTV_SYSTEM)
            if(IS_SBTVD_APP)
                return EN_DL_STATE_HIDDEN;
            else
        #endif
            {
              #ifdef ENABLE_5VANTENNA
                if(IsAnyTVSourceInUse())
                {
                    return EN_DL_STATE_NORMAL;
                }
                else
                {
                    return EN_DL_STATE_DISABLED;
                }
              #else
                return EN_DL_STATE_HIDDEN;
              #endif
            }
        }
        case HWND_MENU_CHANNEL_DTV_MAN_TUNE:
      #if !ENABLE_DTV  //add bydaifq
	   return EN_DL_STATE_HIDDEN;
	  #endif
			
          if(IsDVBCInUse()||IsS2InUse())
                return EN_DL_STATE_HIDDEN;
      #if ENABLE_ATSC_SCAN_NEW_MODE
          if (IsAnyTVSourceInUse())
                return EN_DL_STATE_NORMAL;
            else
                return EN_DL_STATE_HIDDEN;
      #elif ENABLE_ATSC
          return EN_DL_STATE_HIDDEN;
      #endif

        #if (ENABLE_SBTVD_DTV_SYSTEM)
            if((IS_SBTVD_APP)&&(msAPI_ATV_GetCurrentAntenna() == ANT_CATV))
            {
                return EN_DL_STATE_DISABLED;
            }
        #endif
            break;

        case HWND_MENU_CHANNEL_CADTV_MAN_TUNE:
        #if(ENABLE_S2)
            if(IsS2InUse())
                 return EN_DL_STATE_HIDDEN;
            else
        #endif
        {
        #if (ENABLE_DVBC)
            if (IsDVBCInUse() && hwnd == HWND_MENU_CHANNEL_DTV_MAN_TUNE)
            {
                return EN_DL_STATE_HIDDEN;
            }
            else if (!IsDVBCInUse() && hwnd == HWND_MENU_CHANNEL_CADTV_MAN_TUNE)
            {
                return EN_DL_STATE_HIDDEN;
            }
        #else
            if(hwnd == HWND_MENU_CHANNEL_CADTV_MAN_TUNE)
            {
                return EN_DL_STATE_HIDDEN;
            }
        #endif
        }
            break;

        case HWND_MENU_CHANNEL_AUTOTUNE:
        case HWND_MENU_CHANNEL_ATV_MAN_TUNE:
        #if ENABLE_ATSC_MENU_UI
          #if ENABLE_ATSC_MAIN_MENU_CHANNEL_PAGE
            if (IsDVBTInUse() || IsDVBCInUse() || IsISDBTInUse() || IsDTMBInUse())
                return EN_DL_STATE_NORMAL;
            else
                return EN_DL_STATE_HIDDEN;
          #endif
        #endif
        #if ENABLE_S2
            if (IsS2InUse())
                return EN_DL_STATE_HIDDEN;
        #endif
            break; // Fix coverity

        case HWND_MENU_CHANNEL_PROGRAM_EDIT:
        #if ENABLE_ATSC_MENU_UI
            if (IsDVBInUse())
            {
                return EN_DL_STATE_NORMAL;
            }
            else
            {
                return EN_DL_STATE_HIDDEN;
            }
        #endif
        #if ENABLE_PVR
            if( MApp_PVR_IsPlaybacking() || MApp_PVR_IsRecording())
            {
                return EN_DL_STATE_DISABLED;
            }
            //go on  next check
        #endif
        #if(ENABLE_CI_PLUS)
            if(MApp_CI_IsOpMode()==TRUE)
            {
               return EN_DL_STATE_DISABLED;
            }
            else
            {
               return EN_DL_STATE_NORMAL;
            }
        #endif
        break;

    #if ENABLE_ATSC_MENU_UI
        case HWND_MENU_CHANNEL_SIGNAL_INFORMAT:
            if (IsDVBInUse())
            {
                return EN_DL_STATE_NORMAL;
            }
            else
            {
                return EN_DL_STATE_HIDDEN;
            }
            break; // Fix coverity
    #endif

        case HWND_MENU_LOCK_BLOCK_PROGRAM:
        {
            #if (ENABLE_DVBC)
            MApi_AUTH_Process(Customer_info,Customer_hash);
            if(MDrv_AUTH_IPCheck(IPAUTH_CONTROL_XC_DVBC) != TRUE && hwnd == HWND_MENU_CHANNEL_CADTV_MAN_TUNE)
                return EN_DL_STATE_HIDDEN;
            #endif

        #if (ENABLE_DTV == 0)
            if((hwnd == HWND_MENU_CHANNEL_DTV_MAN_TUNE)||(hwnd == HWND_MENU_CHANNEL_SIGNAL_INFORMAT))
            {
                return EN_DL_STATE_HIDDEN;
            }
            else
            {
                //from case MI_TV_ONLY:
                if( IsAnyTVSourceInUse() )
                {
                    return EN_DL_STATE_NORMAL;
                }
                else
                {
                    return EN_DL_STATE_DISABLED;
                }
            }
        #elif ENABLE_ATSC
            if(IsDVBInUse())
                return EN_DL_STATE_NORMAL;
            else
                return EN_DL_STATE_HIDDEN;
        #else
            //from case MI_TV_ONLY:
            if( IsAnyTVSourceInUse() )
            {
                if( IsATVInUse() && hwnd == HWND_MENU_CHANNEL_SIGNAL_INFORMAT)
                {
                    return EN_DL_STATE_DISABLED;
                }
                return EN_DL_STATE_NORMAL;
            }
            else
            {
                return EN_DL_STATE_DISABLED;
            }
            #endif
         }
         break;

        //from MMI_C2_Audio ===============================
#if(CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD || CHIP_FAMILY_TYPE == CHIP_FAMILY_A7)
        case HWND_MENU_SNDEQ_1_2_KHZ:
        case HWND_MENU_SNDEQ_3_KHZ:
        case HWND_MENU_SNDEQ_120_HZ:
        case HWND_MENU_SNDEQ_200_HZ:
        case HWND_MENU_SNDEQ_500_HZ:
#if (SOUNDMODE == SOUNDMODE_EQ)
        {
#ifdef ENABLE_AUDIO_FREQ
            if(stGenSetting.g_SoundSetting.SoundMode != EN_SoundMode_User)
            {
                return EN_DL_STATE_DISABLED;
            }
            else
            {
                return EN_DL_STATE_NORMAL;
            }
#else
            return EN_DL_STATE_HIDDEN;
#endif
        }
#else
            return EN_DL_STATE_HIDDEN;
#endif

        case HWND_MENU_SNDEQ_12_KHZ:
        case HWND_MENU_SNDEQ_7_5_KHZ:
        {
            return EN_DL_STATE_HIDDEN;
        }

#else
        case HWND_MENU_SNDEQ_12_KHZ:
        case HWND_MENU_SNDEQ_1_2_KHZ:
        case HWND_MENU_SNDEQ_3_KHZ:
        case HWND_MENU_SNDEQ_7_5_KHZ:
        case HWND_MENU_SNDEQ_120_HZ:
        case HWND_MENU_SNDEQ_200_HZ:
        case HWND_MENU_SNDEQ_500_HZ:
#if (SOUNDMODE == SOUNDMODE_EQ)
        {
#ifdef ENABLE_AUDIO_FREQ
            if(stGenSetting.g_SoundSetting.SoundMode != EN_SoundMode_User)
            {
                return EN_DL_STATE_DISABLED;
            }
            else
            {
                return EN_DL_STATE_NORMAL;
            }
#else
            return EN_DL_STATE_HIDDEN;
#endif
        }
#else
            return EN_DL_STATE_HIDDEN;
#endif
#endif
        case HWND_MENU_SNDMODE_BASS:
        case HWND_MENU_SNDMODE_TREBLE:
            //from case MI_AUDIO_USER_MODE:
#if (SOUNDMODE == SOUNDMODE_TONE)
            if(stGenSetting.g_SoundSetting.SoundMode==SOUND_MODE_USER)
            {
                return EN_DL_STATE_NORMAL;
            }
            else
            {
                return EN_DL_STATE_DISABLED;
            }
#else
            return EN_DL_STATE_HIDDEN;
#endif

        case HWND_MENU_SNDMODE_SNDMODE_EMPTY:
            return EN_DL_STATE_HIDDEN;

        //from MENU_TIME_D ==================================
        case HWND_MENU_TIME_SET_CLOCK:
        {
            //from case MI_MANUAL_TIME:
        #if ENABLE_DTV
          #if ENABLE_ATSC_MENU_UI
            if(stGenSetting.g_SysSetting.fTimeAutoSync == TIME_AUTO_SYNC_ON)
            {
                return EN_DL_STATE_DISABLED;
            }
            else
            {
                return EN_DL_STATE_NORMAL;
            }
          #else
            if (!MApp_SI_IsAutoClockValid())
            {
                return EN_DL_STATE_NORMAL;
            }
            else
            {
                return EN_DL_STATE_DISABLED;
            }
          #endif
        #else
            return EN_DL_STATE_NORMAL;
        #endif
        }

        //from MENU_OPTION ===============================
        case HWND_MENU_OPTION_COUNTRY:
        {
        #if ENABLE_SBTVD_BRAZIL_APP
            return EN_DL_STATE_HIDDEN;
        #elif ENABLE_ATV_CHINA_APP
            return EN_DL_STATE_HIDDEN;
        #else
            return EN_DL_STATE_HIDDEN;
        #endif
        }

        case HWND_MENU_OPTION_FACTORY_RESET:
        #if ENABLE_PVR
            if( MApp_PVR_IsPlaybacking() || MApp_PVR_IsRecording())
            {
                return EN_DL_STATE_DISABLED;
            }
            else
             {
                return EN_DL_STATE_NORMAL;
            }
        #else
            return EN_DL_STATE_NORMAL;
        #endif

        case HWND_MENU_OPTION_AUDIO_LANG:
        {
        #if ENABLE_ATSC
            if(IsDVBInUse())
            {
                return EN_DL_STATE_NORMAL;
            }
            else
            {
                return EN_DL_STATE_HIDDEN;
            }
    #endif
        #if ENABLE_DTV
            if(IsDTVInUse()
        #if ENABLE_S2
            ||IsS2InUse()
        #endif
            )
            {
                return EN_DL_STATE_NORMAL;
            }
            else
            {
                return EN_DL_STATE_DISABLED;
            }
        #else
            return EN_DL_STATE_HIDDEN;
        #endif
        }

#if ENABLE_SUBTITLE_SWITCH_MENU
        case HWND_MENU_OPTION_SUBTITLE_ONOFF:
#else
        case HWND_MENU_OPTION_SUBTITLE_ONOFF:
            return EN_DL_STATE_HIDDEN;
#endif
        case HWND_MENU_OPTION_SUBTITLE_LANG:
        {
        #if ENABLE_ATSC
            if(IsDVBInUse())
            {
                return EN_DL_STATE_NORMAL;
            }
            else
            {
                return EN_DL_STATE_HIDDEN;
            }
        #endif
        #if (ENABLE_SBTVD_DTV_SYSTEM)
            if(IS_SBTVD_APP)
                return EN_DL_STATE_HIDDEN;
            else
        #endif
            {
                #if ENABLE_DTV
                    if(IsDTVInUse()
                #if ENABLE_S2
                    ||IsS2InUse()
                #endif
                    )
                    {
                        return EN_DL_STATE_NORMAL;
                    }
                    else
                    {
                        return EN_DL_STATE_DISABLED;
                    }
                  #else
                    return EN_DL_STATE_HIDDEN;
                  #endif
             }
         }
    #if ENABLE_DTV
        case HWND_MENU_DLG_SIGNAL_INFORMAT_MODULATION:
        {
            WORD ModulMode = 0;

            if (!msAPI_Tuner_GetSignalModulMode(&ModulMode))
            {
                return EN_DL_STATE_HIDDEN;
            }
            else
            {
                return EN_DL_STATE_NORMAL;
            }
        }
    #endif

        case HWND_MENU_OPTION_HARD_HEARING:
        {
        #if ENABLE_ATSC
            if(IsDVBInUse())
            {
                return EN_DL_STATE_NORMAL;
            }
            else
            {
                return EN_DL_STATE_HIDDEN;
            }
        #endif
        #if (ENABLE_SBTVD_DTV_SYSTEM)
            if(IS_SBTVD_APP)
                return EN_DL_STATE_HIDDEN;
            else
        #endif
            {
              #if ENABLE_DTV
                    if(IsDTVInUse())
                    {
                        return EN_DL_STATE_NORMAL;
                    }
                    else
                    {
                        return EN_DL_STATE_DISABLED;
                    }
              #else
                    return EN_DL_STATE_HIDDEN;
              #endif
            }
        }

        case HWND_MENU_OPTION_RSS:
        {
            return EN_DL_STATE_HIDDEN;
        }
        case HWND_MENU_OPTION_DIVX:
        {
			return EN_DL_STATE_HIDDEN;
        #if ENABLE_DRM
            return EN_DL_STATE_NORMAL;
        #else
            return EN_DL_STATE_HIDDEN;
        #endif
        }


    #if (ENABLE_3D_PROCESS)
        case HWND_MENU_OPTION_3D_DETECT:
            return EN_DL_STATE_HIDDEN;

        case HWND_MENU_OPTION_3D_TYPE:
			return EN_DL_STATE_HIDDEN;
            if (DB_3D_SETTING.en3DTo2DType == EN_3D_TO_2D_ON)
            {
                return EN_DL_STATE_DISABLED;
            }
            else
            {
                #if ENABLE_DMP
                if(IsStorageInUse())
                {
                    if ( MApp_MPlayer_IsPhotoPlaying()
                      #if (ENABLE_MPLAYER_MOVIE)
                       ||MApp_MPlayer_IsMoviePlaying()
                      #endif
                        )
                    {
                        if ( (MApp_MPlayer_QueryPhotoPlayMode() == E_MPLAYER_PHOTO_PAUSE)
                          #if (ENABLE_MPLAYER_MOVIE)
                           ||(MApp_MPlayer_QueryMoviePlayMode() == E_MPLAYER_MOVIE_PAUSE)
                          #endif
                           )
                        {
                            return EN_DL_STATE_DISABLED;
                        }
                        else
                        {
                            return EN_DL_STATE_NORMAL;
                        }
                    }
                }
                #endif
            }
            break;

        case HWND_MENU_OPTION_3D_LR:
			return EN_DL_STATE_HIDDEN;
        {
          if(DB_3D_SETTING.en3DTo2DType == EN_3D_TO_2D_ON)
          {
                return EN_DL_STATE_DISABLED;
          }
          else
          {
            #if ENABLE_DMP
            if(IsStorageInUse())
            {
                if(MApp_MPlayer_IsPhotoPlaying()
#if (ENABLE_MPLAYER_MOVIE)
                    ||(MApp_MPlayer_IsMoviePlaying() && !MApi_XC_IsCurrentFrameBufferLessMode())
#endif
                    )
                {
                     return EN_DL_STATE_NORMAL;
                }
                else
                {
                     return EN_DL_STATE_DISABLED;
                }
            }
            else
            #endif
            {
                if(MApp_IsSrcHasSignal(MAIN_WINDOW))
                {
                     return EN_DL_STATE_NORMAL;
                }
                else
                {
                     return EN_DL_STATE_DISABLED;
                }
            }
              }

            break;
        }

        case HWND_MENU_OPTION_3D_HSHIFT:
        {
			return EN_DL_STATE_HIDDEN;
#if ENABLE_DMP
            if(IsStorageInUse())
            {
                if(MApp_MPlayer_IsPhotoPlaying()
#if (ENABLE_MPLAYER_MOVIE)
                    ||MApp_MPlayer_IsMoviePlaying()
#endif
                    )
                {
                     if(DB_3D_SETTING.en3DType == EN_3D_2DConvertTo3D)
                     {
                         return EN_DL_STATE_NORMAL;
                     }
                     else
                     {
                         return EN_DL_STATE_DISABLED;
                     }
                }
                else
                {
                     return EN_DL_STATE_DISABLED;
                }
            }
            else
#endif
            {
                if(MApp_IsSrcHasSignal(MAIN_WINDOW))
                {
                    if(DB_3D_SETTING.en3DType == EN_3D_2DConvertTo3D)
                    {
                        return EN_DL_STATE_NORMAL;
                    }
                    else
                    {
                        return EN_DL_STATE_DISABLED;
                    }
                }
                else
                {
                     return EN_DL_STATE_DISABLED;
                }
            }
            break;
        }

        case HWND_MENU_OPTION_3D_VIEW_POINT:
        {
			return EN_DL_STATE_HIDDEN;
        #if ((CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN) || \
             (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || \
             (CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA))
            return EN_DL_STATE_HIDDEN;
        #else
                #if ENABLE_DMP
            if(IsStorageInUse())
            {
                if(MApp_MPlayer_IsPhotoPlaying()
#if (ENABLE_MPLAYER_MOVIE)
                    ||MApp_MPlayer_IsMoviePlaying()
#endif
                    )
                {
                     if(DB_3D_SETTING.en3DType == EN_3D_2DConvertTo3D)
                     {
                         return EN_DL_STATE_NORMAL;
                     }
                     else
                     {
                         return EN_DL_STATE_DISABLED;
                     }
                }
                else
                {
                     return EN_DL_STATE_DISABLED;
                }
            }
            else
                #endif
            {
                if(MApp_IsSrcHasSignal(MAIN_WINDOW))
                {
                    if(DB_3D_SETTING.en3DType == EN_3D_2DConvertTo3D)
                    {
                        return EN_DL_STATE_NORMAL;
                    }
                    else
                    {
                        return EN_DL_STATE_DISABLED;
                    }
                }
                else
                {
                     return EN_DL_STATE_DISABLED;
                }
            }
        #endif
            break;
        }

    case HWND_MENU_OPTION_6M30_MIRROR:
    case HWND_MENU_OPTION_6M30_VERSION:
    case HWND_MENU_OPTION_MFC:
#if (ENABLE_EXTERN_MFC_CHIP)
        return EN_DL_STATE_NORMAL;
#else
        return EN_DL_STATE_HIDDEN;
#endif

#else
    case HWND_MENU_OPTION_3D_DETECT:
    case HWND_MENU_OPTION_3D_TYPE:
    case HWND_MENU_OPTION_3D_LR:
    case HWND_MENU_OPTION_3D_HSHIFT:
    case HWND_MENU_OPTION_3D_VIEW_POINT:
    case HWND_MENU_OPTION_6M30_MIRROR:
    case HWND_MENU_OPTION_6M30_VERSION:
        return EN_DL_STATE_HIDDEN;
#endif
        case HWND_MENU_OPTION_EXTENSION:
        {
            return EN_DL_STATE_HIDDEN;
        }

        case HWND_MENU_OPTION_CAPTION:
        {
            #if (ENABLE_SBTVD_DTV_SYSTEM)
                if(IS_SBTVD_APP)
                {
                    if(IsDTVInUse()||IsATVInUse()||IsAVInUse())
                        return  EN_DL_STATE_NORMAL;
                    else
                        return EN_DL_STATE_DISABLED;
                }
                else
            #endif
            return EN_DL_STATE_HIDDEN;

        }

        case HWND_MENU_OPTION_PVR_FILE_SYSTEM:
        {
#if ENABLE_PVR
    #if (ENABLE_DTV)

            if(IsDTVInUse() && !MApp_PVR_IsRecording() && !MApp_PVR_IsPlaybacking())
            {
                return EN_DL_STATE_NORMAL;
            }
            else
            {
                return EN_DL_STATE_DISABLED;
            }
    #else
            return EN_DL_STATE_HIDDEN;
    #endif
#else
            return EN_DL_STATE_HIDDEN;
#endif
        }

        case HWND_MENU_OPTION_CC_MODE:
          #if  (ATSC_CC == ATV_CC)
            if(IsATVInUse()||IsAVInUse()||IsSVInUse())
                return EN_DL_STATE_HIDDEN;
            else
          #endif
                return EN_DL_STATE_HIDDEN;

        case HWND_MENU_OPTION_CC_OPTION:
          #if  (ATSC_CC == ATV_CC)
            if(IsATVInUse()||IsAVInUse()||IsSVInUse())
                return EN_DL_STATE_NORMAL;
            else
          #endif
                return EN_DL_STATE_HIDDEN;

        case HWND_MENU_OPTION_COLOR_RANGE:
			return EN_DL_STATE_HIDDEN;
        #if ENABLE_ATSC
            return EN_DL_STATE_HIDDEN;
        #else
            if (IsHDMIInUse())
                return EN_DL_STATE_NORMAL;
            else
                return EN_DL_STATE_DISABLED;
        #endif

        case HWND_MENU_OPTION_EPOP:
			return EN_DL_STATE_HIDDEN;
        #if ENABLE_ATSC
            if (!IsDVBInUse())
            return EN_DL_STATE_HIDDEN;
        #else
            if(ENABLE_E_POP)
                return EN_DL_STATE_NORMAL;
            else
                return EN_DL_STATE_DISABLED;
        #endif

        case HWND_MENU_OPTION_SCART_IN:
        #if(ENABLE_SCART_SVIDEO)
            return EN_DL_STATE_NORMAL;
        #else
            return EN_DL_STATE_HIDDEN;
        #endif

        //from menu_time===================================
        case HWND_MENU_TIME_SET_TIMEZONE:
        {
          #if ENABLE_DTV
            return EN_DL_STATE_NORMAL;
          #else
            return EN_DL_STATE_HIDDEN;
          #endif
        }

        case HWND_MENU_APP_DMP:
          #if (ENABLE_DMP)
            return EN_DL_STATE_NORMAL;
          #else
            return EN_DL_STATE_HIDDEN;
          #endif //#if (ENABLE_DMP)

    #if (UI_SKIN_SEL == UI_SKIN_1366X768X565 || UI_SKIN_SEL == UI_SKIN_960X540XI8)
        case HWND_MENU_OPTION_KTS:
        {
        #if ENABLE_KEY_TO_SPEECH
            return EN_DL_STATE_NORMAL;
        #else
            return EN_DL_STATE_HIDDEN;
        #endif
        }
    #endif
        default:
            break;
    }

    return EN_DL_STATE_NORMAL;
}


#if(0)

#define MSG_MAC(x)         //x
#ifndef U64
typedef unsigned long long U64;
#endif
#define MAC_ARRR_MS_INDEX  0
#define MAC_ADDR_LEN       18
#define MAC_ARRR_NAME      "/mac_addr.txt"
#define MAC_SYS_ADDR       "/etc/mac_addr.txt"

extern const char *FS_GetMountPoint(U8 drvID);
//MAC_EX:"21-1F-3C-1F-B1-A8"

U8 ASII_TO_HEX(char x)
{
    if(x>='0'&&x<='9')
    {
        return (x-'0');
    }
    else if(x>='A'&&x<='F')
    {
        return (x-'A')+10;
    }
    else if(x>='a'&&x<='f')
    {
        return (x-'a')+10;
    }
    else
    {
        return 0;
    }
}

char HEX_TO_ASII(U8 x)
{
    if(x<=9)
    {
        return (x+'0');
    }
    else if(x>=10&&x<=15)
    {
        return (x-10+'A');
    }
    else
    {
        return '0';
    }
}

U64 MAC_ADDR_TEXT_TO_HEX(char *pTEXT)
{
    char Mac_Text[MAC_ADDR_LEN];
    U64 Hex=0;
    U8 i=0;
    memcpy(Mac_Text,pTEXT,sizeof(Mac_Text));
    for(i=0;i<(MAC_ADDR_LEN-1);i+=3)
    {
        Hex=(Hex<<8)+(ASII_TO_HEX(Mac_Text[i])<<4)+ASII_TO_HEX(Mac_Text[i+1]);
    }
    return Hex;
}

void MAC_ADDR_HEX_TO_TEXT(U64 MAC_HEX,char *pText)
{
    U64 Hex=MAC_HEX;
    U8 i=0,j=0;
    for(i=0;i<(MAC_ADDR_LEN-1);i+=3)
    {
        j= (Hex>>((5-i/3)*8))&0xFF;
        pText[i]=HEX_TO_ASII(j>>4);
        pText[i+1]=HEX_TO_ASII(j&0x0f);
        pText[i+2]='-';
    }
    pText[MAC_ADDR_LEN-1]='\0';
}


BOOL MApp_ZUI_ACT_ConfigMAC_Address(void)
{
    char MacAddrFileName[256],*p_mp;
    char mac_addr_Data[MAC_ADDR_LEN];
    BOOL rel=FALSE;
    U64 MAC_HEX=0;
    int fd=-1;

    p_mp=MacAddrFileName;
    MSG_MAC(printf("\nMApp_ZUI_ACT_ConfigMAC_Address\n"));

    memset(MacAddrFileName,0x00,sizeof(MacAddrFileName));
    memset(mac_addr_Data,0x00,sizeof(mac_addr_Data));

    memcpy(MacAddrFileName,FS_GetMountPoint(MAC_ARRR_MS_INDEX),sizeof(MacAddrFileName));
    p_mp+=strlen(MacAddrFileName);
    memcpy(p_mp,MAC_ARRR_NAME,strlen(MAC_ARRR_NAME));
    MSG_MAC(printf("\nMP_Name:%s",MacAddrFileName));
    rel=ReadFromFile(MacAddrFileName, 0x00, mac_addr_Data, sizeof(mac_addr_Data));
    MSG_MAC(printf("\nMAC:%s\n",mac_addr_Data));
    MAC_HEX=MAC_ADDR_TEXT_TO_HEX(mac_addr_Data);
    MSG_MAC(printf("\nMAC_HEX:%X\n",MAC_HEX));

    if(1)
    {
        if( (fd=open(MAC_SYS_ADDR,O_WRONLY|O_CREAT|O_TRUNC|O_SYNC)) < 0 )
        {
            perror("INIT MAC_SYS_ADDR FAIL:\n");
            return FALSE;
        }
        if(fd>=0)
        {
            close(fd);
            MSG_MAC(printf("INIT MAC_SYS_ADDR DONE\n"));
        }
        WriteToFile(MAC_SYS_ADDR,0x00,mac_addr_Data, sizeof(mac_addr_Data));
    }
    MAC_HEX += 1;//Mac addr auto inc 1for factory mp
    MAC_ADDR_HEX_TO_TEXT(MAC_HEX,mac_addr_Data);
    MSG_MAC(printf("\nMAC2:%s\n",mac_addr_Data));
    WriteToFile(MacAddrFileName,0x00,mac_addr_Data, sizeof(mac_addr_Data));

    return rel;
}
#endif

void MApp_ZUI_ACT_SetOsdDuration(void) //smc.chy 2010/01/19
{
          if(stGenSetting.g_SysSetting.OsdDuration==EN_OSD_TIME_ALWAYS)
           {
                MApp_ZUI_API_KillTimer(HWND_MENU_MASK_BACKGROUND,0);
                MApp_ZUI_API_KillTimer(HWND_MENU_TRANSPARENT_BG,0);
           }
           else
           {
               MApp_ZUI_API_SetTimer(HWND_MENU_MASK_BACKGROUND, 0, stGenSetting.g_SysSetting.OsdDuration*5000);
               MApp_ZUI_API_SetTimer(HWND_MENU_TRANSPARENT_BG, 0, stGenSetting.g_SysSetting.OsdDuration*5000);
           }
}


#if (ENABLE_UI_3D_PROCESS)
BOOLEAN MApp_ZUI_ACT_SetEnv3DOutputMode(E_UI_3D_OUTPUT_MODE eDirectType)
{
    #ifdef MSOS_TYPE_LINUX
    //printf("set env 3DOutputMode\n");
    if(eDirectType == E_UI_3D_OUTPUT_TOP_BOTTOM)
    {
        if(system("echo TOP_BOTTOM>/conf/system_3dOutputMode.conf")==0)
            return TRUE;
    }
    else if(eDirectType == E_UI_3D_OUTPUT_SIDE_BY_SIDE_HALF)
    {
        if(system("echo SIDE_HALF>/conf/system_3dOutputMode.conf")==0)
            return TRUE;
    }
    else
    {
        if(system("echo NONE>/conf/system_3dOutputMode.conf")==0)
            return TRUE;
    }

    return FALSE;
    #else
    eDirectType = eDirectType;
    return TRUE;
    #endif
}
#endif

#if((ATSC_CC == ATV_CC)||(ATSC_CC == DTV_CC)||ENABLE_ISDB_ATV_VCHIP)
void MApp_ZUI_ACT_VChip_CompareRating(void)
{
    BOOLEAN bPreLockStatus = MApp_VChip_GetCurVChipBlockStatus();
    BOOLEAN fVChipPassWordEnteredBk;

    fVChipPassWordEnteredBk = fVChipPassWordEntered;
    fVChipPassWordEntered = FALSE;
    if (bPreLockStatus != MApp_VChip_CompareRating(&g_stVChipRatingInfo, &stGenSetting.g_VChipSetting))
    {
        fVChipPassWordEntered = FALSE;
        memset(&g_stVChipRatingInfo, 0, sizeof(g_stVChipRatingInfo));
        g_stVChipRatingInfo.u8EIA608Data1 = BIT6;
    }
    else
    {
        fVChipPassWordEntered = fVChipPassWordEnteredBk;
    }
}


BOOLEAN MApp_ZUI_ACT_SetVChip_TVRating_TV_NONE_ALL(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_NONE & VCHIP_TVRATING_ALL)
    {
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_NONE &= ~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV_NONE_ALL_BG, TRUE);
    }
    else
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_NONE = VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y = VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y7 = VCHIP_TVRATING_FV|VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G |= VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG = VCHIP_TVRATING_VSLD|VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 = VCHIP_TVRATING_VSLD|VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA = VCHIP_TVRATING_VSL|VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV_NONE_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_FV_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_D_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_D_BG, FALSE);
      #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_NONE = VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV_NONE_ALL_BG, FALSE);
      #endif
    }
    MApp_ZUI_ACT_VChip_CompareRating();
    return TRUE;
}

BOOLEAN MApp_ZUI_ACT_SetVChip_TVRating_TV_Y_ALL(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y & VCHIP_TVRATING_ALL)
    {
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y &= ~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY_ALL_BG, TRUE);
    }
    else
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y = VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y7 = VCHIP_TVRATING_FV|VCHIP_TVRATING_ALL;
         stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G |= VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG = VCHIP_TVRATING_VSLD|VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 = VCHIP_TVRATING_VSLD|VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA = VCHIP_TVRATING_VSL|VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_ALL_BG, FALSE);
         MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_FV_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_D_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_D_BG, FALSE);
      #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y = VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y7 = VCHIP_TVRATING_FV|VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_FV_BG, FALSE);
      #endif
    }
    MApp_ZUI_ACT_VChip_CompareRating();
    return TRUE;
}

BOOLEAN MApp_ZUI_ACT_SetVChip_TVRating_TV_Y7_ALL(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y7 & VCHIP_TVRATING_ALL)
    {
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y7 = 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y = 0;//~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_FV_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY_ALL_BG, TRUE);
    }
    else
    {
  #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y7 = VCHIP_TVRATING_FV|VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G |= VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG = VCHIP_TVRATING_VSLD|VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 = VCHIP_TVRATING_VSLD|VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA = VCHIP_TVRATING_VSL|VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_FV_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_D_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_D_BG, FALSE);
 #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y7 = VCHIP_TVRATING_FV|VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_FV_BG, FALSE);
 #endif
    }
    MApp_ZUI_ACT_VChip_CompareRating();
    return TRUE;
}

BOOLEAN MApp_ZUI_ACT_SetVChip_TVRating_TV_G_ALL(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G & VCHIP_TVRATING_ALL)
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G = 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y7 = 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y = 0;//~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_FV_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
      #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G = 0;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
      #endif
    }
    else
    {
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G |= VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG = VCHIP_TVRATING_VSLD|VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 = VCHIP_TVRATING_VSLD|VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA = VCHIP_TVRATING_VSL|VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_D_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_D_BG, FALSE);
    }
    MApp_ZUI_ACT_VChip_CompareRating();
    return TRUE;
}


BOOLEAN MApp_ZUI_ACT_SetVChip_TVRating_TV_PG_ALL(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG & VCHIP_TVRATING_ALL)
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG = 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G = 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y7 = 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y = 0;//~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_FV_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_D_BG, TRUE);
      #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG = 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G = 0;//~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_D_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
      #endif
    }
    else
    {
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG = VCHIP_TVRATING_VSLD|VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 = VCHIP_TVRATING_VSLD|VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA = VCHIP_TVRATING_VSL|VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_D_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_D_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_L_BG, FALSE);
    }
    MApp_ZUI_ACT_VChip_CompareRating();
    return TRUE;
}

BOOLEAN MApp_ZUI_ACT_SetVChip_TVRating_TV_14_ALL(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 & VCHIP_TVRATING_ALL)
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 = 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG = 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G = 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y7 = 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y = 0;//~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_FV_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_D_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_D_BG, TRUE);
      #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 = 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG = 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G = 0;//~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_D_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_D_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
      #endif
    }
    else
    {
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 = VCHIP_TVRATING_VSLD|VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA = VCHIP_TVRATING_VSL|VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_D_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_L_BG, FALSE);
    }
    MApp_ZUI_ACT_VChip_CompareRating();
    return TRUE;
}


BOOLEAN MApp_ZUI_ACT_SetVChip_TVRating_TV_MA_ALL(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_ALL)
    {
  #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y7 = 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y = 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA &= 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 &= 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G &= 0;//~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_FV_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_D_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_D_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_L_BG, TRUE);
  #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA &= 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 &= 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G &= 0;//~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_D_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_D_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
  #endif
    }
    else
    {
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA = VCHIP_TVRATING_VSL|VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_L_BG, FALSE);
    }
    MApp_ZUI_ACT_VChip_CompareRating();
    return TRUE;
}


BOOLEAN MApp_ZUI_ACT_SetVChip_TVRating_TV_Y7_FV(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y7 & VCHIP_TVRATING_FV)
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y7 &= ~VCHIP_TVRATING_FV;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_FV_BG, TRUE);
     #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y7 = 0;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y = 0;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_FV_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY_ALL_BG, TRUE);
     #endif
    }
    else
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y7 |= VCHIP_TVRATING_FV;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_FV_BG, FALSE);
      #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y7 = VCHIP_TVRATING_FV|VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_FV_BG, FALSE);
      #endif
    }
    MApp_ZUI_ACT_VChip_CompareRating();
    return TRUE;
}

#if (!ENABLE_VCHIP_ALL_AS_AGEBASED)
static void MApp_ZUI_ACT_CheckVChip_TVRating_TV_PG(void)
{
    if((stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG & VCHIP_TVRATING_V)
    &&(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG & VCHIP_TVRATING_S)
    &&(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG & VCHIP_TVRATING_L)
    &&(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG & VCHIP_TVRATING_D)
    &&(!(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG & VCHIP_TVRATING_ALL))
    )
    {
        MApp_ZUI_ACT_SetVChip_TVRating_TV_MA_ALL();
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, FALSE);
        if(!(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 & VCHIP_TVRATING_ALL))
        {
            MApp_ZUI_ACT_SetVChip_TVRating_TV_14_ALL();
            MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, FALSE);
        }
        if(!(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_ALL))
        {
            MApp_ZUI_ACT_SetVChip_TVRating_TV_MA_ALL();
            MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG, FALSE);
        }

    }
    else if((stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_V)
    &&(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_S)
    &&(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_L)
    &&(!(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_ALL)))
    {
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG, FALSE);
    }
}

static void MApp_ZUI_ACT_CheckVChip_TVRating_TV_14(void)
{
    if((stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 & VCHIP_TVRATING_V)
    &&(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 & VCHIP_TVRATING_S)
    &&(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 & VCHIP_TVRATING_L)
    &&(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 & VCHIP_TVRATING_D)
    &&(!(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 & VCHIP_TVRATING_ALL))
    )
    {
        MApp_ZUI_ACT_SetVChip_TVRating_TV_14_ALL();
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, FALSE);
        if(!(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_ALL))
        {
            MApp_ZUI_ACT_SetVChip_TVRating_TV_MA_ALL();
            MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG, FALSE);
        }
    }
    else if((stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_V)
    &&(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_S)
    &&(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_L)
    &&(!(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_ALL)))
    {
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG, FALSE);
    }
}

static void MApp_ZUI_ACT_CheckVChip_TVRating_TV_MA(void)
{
    if((stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_V)
    &&(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_S)
    &&(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_L)
    &&(!(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_ALL))
    )
    {
        MApp_ZUI_ACT_SetVChip_TVRating_TV_MA_ALL();
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG, FALSE);
    }
}
#endif

BOOLEAN MApp_ZUI_ACT_SetVChip_TVRating_TV_PG_V(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG & VCHIP_TVRATING_V)
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~VCHIP_TVRATING_V;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, TRUE);
      #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~(VCHIP_TVRATING_V|VCHIP_TVRATING_ALL);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G &= ~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
      #endif
    }
    else
    {
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG |= VCHIP_TVRATING_V;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 |= VCHIP_TVRATING_V;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA |= VCHIP_TVRATING_V;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_V_BG, FALSE);
      #if (!ENABLE_VCHIP_ALL_AS_AGEBASED)
        MApp_ZUI_ACT_CheckVChip_TVRating_TV_PG();
      #endif
    }
    MApp_ZUI_ACT_VChip_CompareRating();
    return TRUE;
}

BOOLEAN MApp_ZUI_ACT_SetVChip_TVRating_TV_14_V(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 & VCHIP_TVRATING_V)
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 &= ~VCHIP_TVRATING_V;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~VCHIP_TVRATING_V;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, TRUE);
     #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 &= ~(VCHIP_TVRATING_V|VCHIP_TVRATING_ALL);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~(VCHIP_TVRATING_ALL|VCHIP_TVRATING_V);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G &= ~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
     #endif
    }
    else
    {
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 |= VCHIP_TVRATING_V;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA |= VCHIP_TVRATING_V;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_V_BG, FALSE);
    #if (!ENABLE_VCHIP_ALL_AS_AGEBASED)
        MApp_ZUI_ACT_CheckVChip_TVRating_TV_14();
    #endif
    }
    MApp_ZUI_ACT_VChip_CompareRating();
    return TRUE;
}


BOOLEAN MApp_ZUI_ACT_SetVChip_TVRating_TV_MA_V(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_V)
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA &= ~VCHIP_TVRATING_V;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 &= ~VCHIP_TVRATING_V;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~VCHIP_TVRATING_V;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_V_BG, TRUE);
      #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA &= ~(VCHIP_TVRATING_V|VCHIP_TVRATING_ALL);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 &= ~(VCHIP_TVRATING_ALL|VCHIP_TVRATING_V);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~(VCHIP_TVRATING_ALL|VCHIP_TVRATING_V);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G &= ~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
      #endif
    }
    else
    {
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA |= VCHIP_TVRATING_V;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_V_BG, FALSE);
    #if (!ENABLE_VCHIP_ALL_AS_AGEBASED)
        MApp_ZUI_ACT_CheckVChip_TVRating_TV_MA();
    #endif
    }
    MApp_ZUI_ACT_VChip_CompareRating();
    return TRUE;
}


BOOLEAN MApp_ZUI_ACT_SetVChip_TVRating_TV_PG_S(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG & VCHIP_TVRATING_S)
    {
    #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~VCHIP_TVRATING_S;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, TRUE);
    #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~(VCHIP_TVRATING_S|VCHIP_TVRATING_ALL);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G &= ~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
    #endif
    }
    else
    {
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG |= VCHIP_TVRATING_S;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 |= VCHIP_TVRATING_S;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA |= VCHIP_TVRATING_S;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_S_BG, FALSE);
      #if (!ENABLE_VCHIP_ALL_AS_AGEBASED)
        MApp_ZUI_ACT_CheckVChip_TVRating_TV_PG();
      #endif
    }
    MApp_ZUI_ACT_VChip_CompareRating();
    return TRUE;
}


BOOLEAN MApp_ZUI_ACT_SetVChip_TVRating_TV_14_S(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 & VCHIP_TVRATING_S)
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 &= ~VCHIP_TVRATING_S;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~VCHIP_TVRATING_S;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, TRUE);
      #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 &= ~(VCHIP_TVRATING_S|VCHIP_TVRATING_ALL);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~(VCHIP_TVRATING_ALL|VCHIP_TVRATING_S);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G &= ~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
      #endif
    }
    else
    {
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 |= VCHIP_TVRATING_S;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA |= VCHIP_TVRATING_S;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_S_BG, FALSE);
      #if (!ENABLE_VCHIP_ALL_AS_AGEBASED)
        MApp_ZUI_ACT_CheckVChip_TVRating_TV_14();
      #endif
    }
    MApp_ZUI_ACT_VChip_CompareRating();
    return TRUE;
}

BOOLEAN MApp_ZUI_ACT_SetVChip_TVRating_TV_MA_S(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_S)
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA &= ~VCHIP_TVRATING_S;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 &= ~VCHIP_TVRATING_S;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~VCHIP_TVRATING_S;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_S_BG, TRUE);
      #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA &= ~(VCHIP_TVRATING_S|VCHIP_TVRATING_ALL);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 &= ~(VCHIP_TVRATING_ALL|VCHIP_TVRATING_S);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~(VCHIP_TVRATING_ALL|VCHIP_TVRATING_S);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G &= ~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
      #endif
    }
    else
    {
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA |= VCHIP_TVRATING_S;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_S_BG, FALSE);
      #if (!ENABLE_VCHIP_ALL_AS_AGEBASED)
        MApp_ZUI_ACT_CheckVChip_TVRating_TV_MA();
      #endif
    }
    MApp_ZUI_ACT_VChip_CompareRating();
    return TRUE;
}

BOOLEAN MApp_ZUI_ACT_SetVChip_TVRating_TV_PG_L(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG & VCHIP_TVRATING_L)
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~VCHIP_TVRATING_L;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, TRUE);
     #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~(VCHIP_TVRATING_L|VCHIP_TVRATING_ALL);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G &= ~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
    #endif
    }
    else
    {

        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG |= VCHIP_TVRATING_L;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 |= VCHIP_TVRATING_L;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA |= VCHIP_TVRATING_L;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_L_BG, FALSE);
      #if (!ENABLE_VCHIP_ALL_AS_AGEBASED)
        MApp_ZUI_ACT_CheckVChip_TVRating_TV_PG();
      #endif
    }
    MApp_ZUI_ACT_VChip_CompareRating();
    return TRUE;
}

BOOLEAN MApp_ZUI_ACT_SetVChip_TVRating_TV_14_L(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 & VCHIP_TVRATING_L)
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 &= ~VCHIP_TVRATING_L;
     stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~VCHIP_TVRATING_L;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, TRUE);
      #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 &= ~(VCHIP_TVRATING_L|VCHIP_TVRATING_ALL);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~(VCHIP_TVRATING_ALL|VCHIP_TVRATING_L);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G &= ~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
      #endif
    }
    else
    {
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 |= VCHIP_TVRATING_L;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA |= VCHIP_TVRATING_L;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_L_BG, FALSE);
      #if (!ENABLE_VCHIP_ALL_AS_AGEBASED)
        MApp_ZUI_ACT_CheckVChip_TVRating_TV_14();
      #endif
    }
    MApp_ZUI_ACT_VChip_CompareRating();
    return TRUE;
}


BOOLEAN MApp_ZUI_ACT_SetVChip_TVRating_TV_MA_L(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_L)
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA &= ~VCHIP_TVRATING_L;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 &= ~VCHIP_TVRATING_L;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~VCHIP_TVRATING_L;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_L_BG, TRUE);
      #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA &= ~(VCHIP_TVRATING_L|VCHIP_TVRATING_ALL);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 &= ~(VCHIP_TVRATING_ALL|VCHIP_TVRATING_L);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~(VCHIP_TVRATING_ALL|VCHIP_TVRATING_L);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G &= ~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
      #endif
    }
    else
    {
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA |= VCHIP_TVRATING_L;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_L_BG, FALSE);
      #if (!ENABLE_VCHIP_ALL_AS_AGEBASED)
        MApp_ZUI_ACT_CheckVChip_TVRating_TV_MA();
      #endif
    }

    MApp_ZUI_ACT_VChip_CompareRating();

    return TRUE;
}

BOOLEAN MApp_ZUI_ACT_SetVChip_TVRating_TV_PG_D(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG & VCHIP_TVRATING_D)
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~VCHIP_TVRATING_D;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_D_BG, TRUE);
      #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~(VCHIP_TVRATING_D|VCHIP_TVRATING_ALL);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G &= ~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_D_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
      #endif
    }
    else
    {
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG |= VCHIP_TVRATING_D;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 |= VCHIP_TVRATING_D;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_D_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_D_BG, FALSE);
    #if (!ENABLE_VCHIP_ALL_AS_AGEBASED)
        MApp_ZUI_ACT_CheckVChip_TVRating_TV_PG();
      #endif
    }
    MApp_ZUI_ACT_VChip_CompareRating();
    return TRUE;
}


BOOLEAN MApp_ZUI_ACT_SetVChip_TVRating_TV_14_D(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 & VCHIP_TVRATING_D)
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 &= ~VCHIP_TVRATING_D;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~VCHIP_TVRATING_D;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_D_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_D_BG, TRUE);
      #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 &= ~(VCHIP_TVRATING_D|VCHIP_TVRATING_ALL);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~(VCHIP_TVRATING_ALL|VCHIP_TVRATING_D);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G &= ~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_D_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_D_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
      #endif
    }
    else
    {
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 |= VCHIP_TVRATING_D;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_D_BG, FALSE);
      #if (!ENABLE_VCHIP_ALL_AS_AGEBASED)
        MApp_ZUI_ACT_CheckVChip_TVRating_TV_14();
      #endif
    }
    MApp_ZUI_ACT_VChip_CompareRating();
    return TRUE;
}
#endif

#if ENABLE_3D_PROCESS

//============================================================================
//_MApp_ZUI_ACT_DecIncAspectRatio_Cycle
BOOLEAN _MApp_ZUI_ACT_DecInc3DType_Cycle(BOOLEAN action)
{
#if ENABLE_NEW_3D_FLOW
    U8 u83DTypeOptionMax = EN_3D_FRAME_ALTERNATIVE;

    if( MApp_Scaler_Is_3DTypeSupported(EN_3D_2DConvertTo3D) )
        u83DTypeOptionMax = EN_3D_2DConvertTo3D;


    printf("Org DB_3D_SETTING.en3DType=%u\n", DB_3D_SETTING.en3DType);

    DB_3D_SETTING.en3DType =
        (EN_3D_TYPE)MApp_ZUI_ACT_DecIncValue_Cycle(
            action,  (U16)(DB_3D_SETTING.en3DType), EN_3D_BYPASS, (U16)u83DTypeOptionMax/*EN_3D_2DConvertTo3D*/, 1);

    printf("New DB_3D_SETTING.en3DType=%u\n", DB_3D_SETTING.en3DType);

    MApp_Scaler_EnableManualDetectTiming(TRUE);

    ST_VIDEO.eAspectRatio = EN_AspectRatio_16X9;

    msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);

    //MApp_Scaler_Setting_SetVDScale(EN_AspectRatio_16X9, MAIN_WINDOW);
    MApp_Scaler_SetVideo3DMode(DB_3D_SETTING.en3DType);

    msAPI_Scaler_SetBlueScreen(DISABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
    return TRUE;
#else
      E_XC_3D_INPUT_MODE eInput3DMode;
  #if ((ENABLE_EXTERN_MFC_CHIP) ||ENABLE_6M40_4KX2K_PROCESS ||ENABLE_6M50_4KX2K_PROCESS)
    if(DB_3D_SETTING.en3DType == EN_3D_2DConvertTo3D)
    {
        msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
        MApp_Scaler_SetVideo3DMode(E_USER_3D_MODE_OFF);
        msAPI_Scaler_SetBlueScreen(DISABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
    }
  #endif
        DB_3D_SETTING.en3DType=
                (EN_3D_TYPE)MApp_ZUI_ACT_DecIncValue_Cycle(
                    action,  (EN_3D_TYPE)(DB_3D_SETTING.en3DType),EN_3D_BYPASS, (EN_3D_TYPE_NUM-2), 1);

        eInput3DMode = (E_XC_3D_INPUT_MODE)MAPP_Scaler_MapUI3DModeToXCInput3DMode(DB_3D_SETTING.en3DType);

        MApp_Scaler_EnableManualDetectTiming(TRUE);
        msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
  #if (ENABLE_EXTERN_MFC_CHIP)
        if(DB_3D_SETTING.en3DType == EN_3D_2DConvertTo3D)
        {
            MDrv_Ursa_6M30_3D_MODE(PANEL_3D_MODE_NONE);
            MApp_Scaler_SetVideo3DMode(MAPP_Scaler_Map3DFormatTo3DUserMode(eInput3DMode));
        }
        else
        {
            MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CLOSE_CURRENT_OSD);
            if(DB_3D_SETTING.en3DType == EN_3D_SIDE_BY_SIDE)
            {
                MApp_ZUI_Set_UI_3D_Mode(E_UI_3D_OUTPUT_SIDE_BY_SIDE_HALF);
            }
            else if(DB_3D_SETTING.en3DType == EN_3D_TOP_BOTTOM)
            {
                MApp_ZUI_Set_UI_3D_Mode(E_UI_3D_OUTPUT_TOP_BOTTOM);
            }
            else
            {
                MApp_ZUI_Set_UI_3D_Mode(E_UI_3D_OUTPUT_MODE_NONE);
            }
            MDrv_Ursa_6M30_3D_MODE(MAPP_Scaler_MapUi3DFormatToUrsa3DMode(DB_3D_SETTING.en3DType));
        }
  #elif(ENABLE_6M40_4KX2K_PROCESS || ENABLE_6M50_4KX2K_PROCESS)
        if(DB_3D_SETTING.en3DType == EN_3D_2DConvertTo3D)
        {
            MDrv_Ursa_6M40_3D_MODE(PANEL_3D_MODE_NONE);
            MApp_Scaler_SetVideo3DMode(MAPP_Scaler_Map3DFormatTo3DUserMode(eInput3DMode));
        }
        else
        {
            MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CLOSE_CURRENT_OSD);
            if(DB_3D_SETTING.en3DType == EN_3D_SIDE_BY_SIDE)
            {
                MApp_ZUI_Set_UI_3D_Mode(E_UI_3D_OUTPUT_SIDE_BY_SIDE_HALF);
            }
            else if(DB_3D_SETTING.en3DType == EN_3D_TOP_BOTTOM)
            {
                MApp_ZUI_Set_UI_3D_Mode(E_UI_3D_OUTPUT_TOP_BOTTOM);
            }
            else
            {
                MApp_ZUI_Set_UI_3D_Mode(E_UI_3D_OUTPUT_MODE_NONE);
            }

            MDrv_Ursa_6M40_3D_MODE(MAPP_Scaler_MapUi3DFormatToUrsa3DMode(DB_3D_SETTING.en3DType));
        }

  #else
    MApp_Scaler_SetVideo3DMode(MAPP_Scaler_Map3DFormatTo3DUserMode(eInput3DMode));
  #endif
    msAPI_Scaler_SetBlueScreen(DISABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
    return TRUE;
#endif

}
BOOLEAN _MApp_ZUI_ACT_3D_TO_2D_Cycle(BOOLEAN action)
{
#if 0
    E_XC_3D_INPUT_MODE eInput3DMode;
    U16 u16User3DMode = E_USER_3D_MODE_OFF;

    DB_3D_SETTING.en3DTo2DType=
            (EN_3D_TO_2D_TYPE)MApp_ZUI_ACT_DecIncValue_Cycle(
                action,  (EN_3D_TO_2D_TYPE)(DB_3D_SETTING.en3DTo2DType),EN_3D_TO_2D_OFF, (EN_3D_TO_2D_TYPE_NUM-1), 1);

      switch( DB_3D_SETTING.en3DTo2DType)
      {
          case EN_3D_TO_2D_OFF:
              eInput3DMode = E_XC_3D_INPUT_MODE_NONE;
              break;
          case EN_3D_TO_2D_FRAME_PARKING:
              eInput3DMode = E_XC_3D_INPUT_FRAME_PACKING;
              break;
          case EN_3D_TO_2D_SIDE_BY_SIDE:
              eInput3DMode = E_XC_3D_INPUT_SIDE_BY_SIDE_HALF;
              break;
          case EN_3D_TO_2D_TOP_BOTTOM:
              eInput3DMode = E_XC_3D_INPUT_TOP_BOTTOM;
              break;
          case EN_3D_TO_2D_LINE_BY_LINE:
              eInput3DMode = E_XC_3D_INPUT_LINE_ALTERNATIVE;
              break;
          case EN_3D_TO_2D_FRAME_ALTERNATIVE:
              eInput3DMode = E_XC_3D_INPUT_FRAME_ALTERNATIVE;
              break;
          default:
              eInput3DMode = E_XC_3D_INPUT_MODE_NONE;
              break;
      }

      MApp_Scaler_EnableManualDetectTiming(TRUE);
      msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);

      if(eInput3DMode == E_XC_3D_INPUT_FRAME_PACKING)
      {
          u16User3DMode = E_USER_3D_MODE_FRAME_PACKING_2_FRAME_L;
          MApi_Scaler_Set3DInfo(eInput3DMode, E_XC_3D_OUTPUT_FRAME_L);
      }
      else if(eInput3DMode == E_XC_3D_INPUT_SIDE_BY_SIDE_HALF)
      {
          u16User3DMode = E_USER_3D_MODE_SIDE_BY_SIDE_HALF_2_FRAME_L;
          MApi_Scaler_Set3DInfo(eInput3DMode, E_XC_3D_OUTPUT_FRAME_L);
      }
      else if(eInput3DMode == E_XC_3D_INPUT_TOP_BOTTOM)
      {
          u16User3DMode = E_USER_3D_MODE_TOP_BOTTOM_2_FRAME_L;
          MApi_Scaler_Set3DInfo(eInput3DMode, E_XC_3D_OUTPUT_FRAME_L);
      }
      else if(eInput3DMode == E_XC_3D_INPUT_LINE_ALTERNATIVE)
      {
          u16User3DMode = E_USER_3D_MODE_LINE_ALTERNATIVE_2_FRAME_L;
          MApi_Scaler_Set3DInfo(eInput3DMode, E_XC_3D_OUTPUT_FRAME_L);
      }
      else if(eInput3DMode == E_XC_3D_INPUT_FRAME_ALTERNATIVE)
      {
          u16User3DMode = E_USER_3D_MODE_FRAME_ALTERNATIVE_2_FRAME_L;
          MApi_Scaler_Set3DInfo(eInput3DMode, E_XC_3D_OUTPUT_FRAME_L);
      }
      else
      {
        if (IsSrcTypeHDMI(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
        {
            eInput3DMode = g_HdmiInput3DFormat;
            u16User3DMode = MAPP_Scaler_Map3DFormatTo3DUserMode(eInput3DMode);
        }
        else
        {
            u16User3DMode = E_USER_3D_MODE_OFF;
            MApi_Scaler_Set3DInfo(eInput3DMode,E_XC_3D_OUTPUT_MODE_NONE);
        }
      }

      MApp_Scaler_SetVideo3DMode(u16User3DMode);

      msAPI_Scaler_SetBlueScreen(DISABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
#else

    DB_3D_SETTING.en3DTo2DType=
            (EN_3D_TO_2D_TYPE)MApp_ZUI_ACT_DecIncValue_Cycle(
                action,  (EN_3D_TO_2D_TYPE)(DB_3D_SETTING.en3DTo2DType),EN_3D_TO_2D_OFF, (EN_3D_TO_2D_TYPE_NUM-1), 1);

    MApp_Scaler_EnableManualDetectTiming(TRUE);
    msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
    MApp_Scaler_SetVideo3DMode(DB_3D_SETTING.en3DType);
    msAPI_Scaler_SetBlueScreen(DISABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
#endif
      return TRUE;
}
BOOLEAN _MApp_ZUI_ACT_DecInc3DDetectMode_Cycle(BOOLEAN action)
{
    DB_3D_SETTING.en3DDetectMode=
                (EN_3D_DETECT_MODE)MApp_ZUI_ACT_DecIncValue_Cycle(
                    action, (U16)(DB_3D_SETTING.en3DDetectMode),EN_3D_DETECT_AUTO, (U16)EN_3D_DETECT_NUM-1, 1);
     MApp_Scaler_EnableManualDetectTiming(MAPP_Scaler_MapUIDetectMode(DB_3D_SETTING.en3DDetectMode));
     MApp_ZUI_API_InvalidateWindow(HWND_MENU_OPTION_3D_DETECT);
     return TRUE;
}
BOOLEAN _MApp_ZUI_ACT_DecInc3DLRMode_Cycle(BOOLEAN action)
{
    static MS_BOOL _b3DLRSwtichFlag = DISABLE;

    DB_3D_SETTING.en3DLRMode=
                (EN_3D_LR_MODE)MApp_ZUI_ACT_DecIncValue_Cycle(
                    action, (U16)(DB_3D_SETTING.en3DLRMode),EN_3D_LR_L, (U16)EN_3D_LR_NUM-1, 1);
    MApi_XC_Set_3D_LR_Frame_Exchg(MAIN_WINDOW);
#if (ENABLE_EXTERN_MFC_CHIP)
    _b3DLRSwtichFlag = _b3DLRSwtichFlag;
    MDrv_Ursa_6M30_LRExchange_MODE((EN_URSA_LR_TYPE)DB_3D_SETTING.en3DLRMode);
#else
    if(_b3DLRSwtichFlag == DISABLE)
    {
        MApp_3D_SetLRSwitchFlag(TRUE);
        _b3DLRSwtichFlag = ENABLE;
    }
    else
    {
        MApp_3D_SetLRSwitchFlag(FALSE);
        _b3DLRSwtichFlag = DISABLE;
    }
#endif
    MApp_ZUI_API_InvalidateWindow(HWND_MENU_OPTION_3D_LR);
    return TRUE;
}

#if ((CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN))
BOOLEAN _MApp_ZUI_ACT_DecInc3DHShift_Cycle(BOOLEAN action)
{
    U16 u16HShift;

    DB_3D_SETTING.en3DHShiftMode = (EN_3D_HSHIFT_MODE)MApp_ZUI_ACT_DecIncValue_Cycle(
                    action, (U16)(DB_3D_SETTING.en3DHShiftMode),EN_3D_HSHIFT_WEAK, (U16)EN_3D_HSHIFT_NUM-1, 1);

     if(DB_3D_SETTING.en3DHShiftMode == EN_3D_HSHIFT_WEAK)
     {
         u16HShift = 0x05;
     }
     else if(DB_3D_SETTING.en3DHShiftMode == EN_3D_HSHIFT_MID)
     {
         u16HShift = 0x11;
     }
     else
     {
         u16HShift = 0x1D;
     }
     msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
     MApi_XC_Set_3D_HShift(u16HShift);
     MApp_Scaler_SetWindow(NULL, NULL, NULL, stSystemInfo[MAIN_WINDOW].enAspectRatio,
                             SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
     MApp_Picture_Setting_SetColor(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
     msAPI_Scaler_SetBlueScreen(DISABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
     MApp_ZUI_API_InvalidateWindow(HWND_MENU_OPTION_3D_HSHIFT);
     return TRUE;
}
#else
BOOLEAN _MApp_ZUI_ACT_DecInc3DHShift_Cycle(BOOLEAN action)
{
    DB_3D_SETTING.en3DHShiftMode=
                (EN_3D_HSHIFT_MODE)MApp_ZUI_ACT_DecIncValue_Cycle(
                    action, (U16)(DB_3D_SETTING.en3DHShiftMode),EN_3D_HSHIFT_WEAK, (U16)EN_3D_HSHIFT_NUM-1, 1);

     MS_XC_3D_HW2DTO3D_PARA stHw2Dto3DPara;
     memset(&stHw2Dto3DPara, 0, sizeof(MS_XC_3D_HW2DTO3D_PARA));
     MApi_XC_Get_3D_HW2DTo3D_Parameters(&stHw2Dto3DPara);
     if(DB_3D_SETTING.en3DHShiftMode == EN_3D_HSHIFT_WEAK)
     {
         stHw2Dto3DPara.u16Gain = 0x05;
     }
     else if(DB_3D_SETTING.en3DHShiftMode == EN_3D_HSHIFT_MID)
     {
         stHw2Dto3DPara.u16Gain = 0x11;
     }
     else
     {
         stHw2Dto3DPara.u16Gain = 0x1D;
     }
     MApi_XC_Set_3D_HW2DTo3D_Parameters(stHw2Dto3DPara);
     MApp_ZUI_API_InvalidateWindow(HWND_MENU_OPTION_3D_HSHIFT);
     return TRUE;
}
#endif

BOOLEAN _MApp_ZUI_ACT_DecInc3DViewPoint_Cycle(BOOLEAN action)
{
    DB_3D_SETTING.en3DViewPointMode =
                (EN_3D_VIEW_POINT_MODE)MApp_ZUI_ACT_DecIncValue_Cycle(
                    action, (U16)(DB_3D_SETTING.en3DViewPointMode),EN_3D_VIEW_POINT_WEAK, (U16)EN_3D_VIEW_POINT_NUM-1, 1);

     MS_XC_3D_HW2DTO3D_PARA stHw2Dto3DPara;
     memset(&stHw2Dto3DPara, 0, sizeof(MS_XC_3D_HW2DTO3D_PARA));
     MApi_XC_Get_3D_HW2DTo3D_Parameters(&stHw2Dto3DPara);
     if(DB_3D_SETTING.en3DViewPointMode == EN_3D_VIEW_POINT_WEAK)
     {
         stHw2Dto3DPara.u16Offset = 0x0F;
     }
     else if(DB_3D_SETTING.en3DViewPointMode == EN_3D_VIEW_POINT_MID)
     {
         stHw2Dto3DPara.u16Offset = 0x7F;
     }
     else
     {
         stHw2Dto3DPara.u16Offset = 0xEF;
     }
     MApi_XC_Set_3D_HW2DTo3D_Parameters(stHw2Dto3DPara);
     MApp_ZUI_API_InvalidateWindow(HWND_MENU_OPTION_3D_VIEW_POINT);
     return TRUE;
}

#if (ENABLE_EXTERN_MFC_CHIP)
BOOLEAN _MApp_ZUI_ACT_DecInc6M30Mirror_Cycle(BOOLEAN action)
{
    stGenSetting.stDevMfcSetting.en6M30MirrorMode=
                (EN_6M30_MIRROR_MODE)MApp_ZUI_ACT_DecIncValue_Cycle(
                    action, (U16)(stGenSetting.stDevMfcSetting.en6M30MirrorMode),EN_6M30_MIRROR_ON, (U16)EN_6M30_MIRROR_NUM-1, 1);
     MDrv_Ursa_6M30_MIRROR_MODE((EN_URSA_MIRROR_TYPE)stGenSetting.stDevMfcSetting.en6M30MirrorMode);
     MApp_ZUI_API_InvalidateWindow(HWND_MENU_OPTION_6M30_MIRROR);
     return TRUE;
}
#endif

#if HDMI_DVI_AUDIO_MODE_CONFIG
BOOLEAN _MApp_ZUI_ACT_ChangeHdmiDviAudioMode(BOOLEAN action)
{
    EN_HDMI_DVI_AUDIOMODE _enPreAudioMode;
    _enPreAudioMode = stGenSetting.g_SysSetting.fEnableHdmiDviAudioModeConfig;
    stGenSetting.g_SysSetting.fEnableHdmiDviAudioModeConfig =
                (EN_HDMI_DVI_AUDIOMODE)MApp_ZUI_ACT_DecIncValue_Cycle(
                    action, (U16)(stGenSetting.g_SysSetting.fEnableHdmiDviAudioModeConfig),EN_HDMI_DVI_AUDIOMODE_AUTO, (U16)EN_HDMI_DVI_AUDIOMODE_NUM-1, 1);

    switch(stGenSetting.g_SysSetting.fEnableHdmiDviAudioModeConfig)
    {
        case EN_HDMI_DVI_AUDIOMODE_AUTO:
            if(MApi_XC_HDMI_GetHdmiType(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) == E_HDMI_STATUS_HDMI)
            {
                g_HdmiAudioModeChanged = TRUE;
                MAPP_InputSource_SwitchHDMI_DVI(E_HDMI_STATUS_HDMI);
            }
            else
            {
                MAPP_InputSource_SwitchHDMI_DVI(E_HDMI_STATUS_DVI);
            }
            break;
        case EN_HDMI_DVI_AUDIOMODE_DIGTAL:
            g_HdmiAudioModeChanged = TRUE;
            MAPP_InputSource_SwitchHDMI_DVI(E_HDMI_STATUS_HDMI);
            break;
        case EN_HDMI_DVI_AUDIOMODE_ANALOG:
            MAPP_InputSource_SwitchHDMI_DVI(E_HDMI_STATUS_DVI);
            break;
        default:
            break;
    }
    return TRUE;

}

#endif // #if HDMI_DVI_AUDIO_MODE_CONFIG

#endif // #if ENABLE_3D_PROCESS

#undef MAPP_ZUI_ACTMENUFUNC_C

