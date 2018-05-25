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
// (��MStar Confidential Information��) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define MAPP_IR_C

#include <stdio.h>
#include <string.h>
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"
#include "SysInit.h"
#include "MApp_Init.h"
#include "MApp_ZUI_ACTcoexistWin.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "MApp_GlobalSettingSt.h"
#include "msAPI_Global.h"
#include "MApp_GlobalFunction.h"
#include "MApp_InputSource.h"
#include "msAPI_ATVSystem.h"
#include "msAPI_DTVSystem.h"
#include "msAPI_IR.h"
#include "msAPI_Timer.h"
#include "msAPI_Power.h"
#include "msAPI_MIU.h"
#include "drvUartDebug.h"
#include "BinInfo.h"
#include "MApp_DMP_Main.h"
//#if (DEBUG_SYS_INFO_REPORT && MHEG5_ENABLE)
#if (MHEG5_ENABLE)
#include "msAPI_MHEG5.h"
#endif
#include "MApp_ZUI_ACTcoexistWin.h"
#include "MApp_GlobalVar.h"
#include "MApp_Key.h"
#include "MApp_IR.h"
#include "MApp_DataBase.h"
#include "MApp_Sleep.h"
#include "MApp_NoOperate_AutoSleep.h"
#include "MApp_SaveData.h"
#include "MApp_ATVProc.h"
#include "MApp_ZUI_Main.h"
#include "ZUI_tables_h.inl"
#include "ZUI_exefunc.h"
#include "MApp_UiMenuDef.h" //ZUI: #include "MApp_UiMenu.h"
#include "MApp_Main.h"

#if ( ENABLE_CI_PLUS_V1_4 )
#include "MApp_CIMMI.h"
#endif  //ENABLE_CI_PLUS_V1_4

#if MHEG5_ENABLE
#include "MApp_ChannelChange.h"
#endif

//CEC
#if ENABLE_CEC
#include "msAPI_CEC.h"
#endif

#include "mstar_debug.h"
#include "msIR.h"
#include "GPIO.h"
#include "MApp_TopStateMachine.h"
#include "MApp_Func_Inputsource.h"
#include "msAPI_Tuning.h"
#include "mapp_videoplayer.h"
#include "MApp_RestoreToDefault.h"

#if (ENABLE_MFC_6M20)
#include "drvUrsaMFCAPI.h"
#endif

#if ENABLE_MFC_6M30
#include "drvUrsa6M30.h"
#endif

//MHL
#if (ENABLE_MHL == ENABLE)
#include "msAPI_MHL.h"
#endif

#if(CHAKRA3_AUTO_TEST)
#include "MApp_AutoTest.h"
#endif

#ifndef SCAN_TEST_MODE_ENABLE
#define SCAN_TEST_MODE_ENABLE 0
#endif
#if ENABLE_S2
#include "MApp_TV.h"
#include "MApp_MenuChannel.h"
#endif
#if ENABLE_KEY_LOGGER
#include "MApp_KeyLogger.h"
#endif
#if ENABLE_EWS
#include "MApp_EWS.h"
#endif
#if (ENABLE_AUDIO_ONLY_CUSTOMERMODE == 1)
#include "MApp_ChannelProc_ATSC.h"
#include "MApp_XC_PQ.h"
#include "MApp_UiMenuFunc_ATSC.h"
#endif

#if (NO_SIGNAL_AUTO_SHUTDOWN )
#include "MApp_NoSignal_AutoSleep.h"
#endif

//==============================================================================
/*                                 Macro                                        */
//==============================================================================
#define CUSTOM_CODE 0xAB
#define KEY_DEBUG(y)            //y
#define DEBUG_OBAMA_KEY 0
#define CEC_DEBUG(y)            //y

//==============================================================================
/*                                 Global                                        */
//==============================================================================
extern BOOLEAN gCECUserControlEnable;

//==============================================================================
/*                                 Local                                        */
//==============================================================================
static void MApp_ParseKey(void);
static void MApp_CheckKeyStatus(void);
static void MApp_SetKeyRepeatState(U8 u8KeyData);

static KEYSTAT stKeyStatus;

#define OSD_REPEAT_MASK     (BIT1|BIT0)
#define OSD_REPEAT_DISABLE  (0x00)
#define OSD_REPEAT_H_ENABLE (BIT0)
#define OSD_REPEAT_V_ENABLE (BIT1)
#define OSD_REPEAT_ENABLE   (BIT1|BIT0)

static U8 u8KeyRepeatState = OSD_REPEAT_ENABLE;
static U8 u8HwDebugFlag = 0;
#if (IR_MODE_SEL == IR_TYPE_FULLDECODE_MODE)
extern U8 u8IRTimerBlockstatus;
#endif

#if (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210) // GEM_SYNC_0815
#define MSTAR_VIF_MSB1210_DEBUG_MODE      0
#define GEMINI_KEY_NONE                   0
#define GEMINI_KEY_WAIT_1                 1
#define GEMINI_KEY_WAIT_2                 2
#define GEMINI_KEY_WAIT_3                 3
#define GEMINI_GET_KEY_1                  1
#define GEMINI_GET_KEY_2                  2

U8 gGemini_KeyState            =0;
U8 gGemini_FactoryMode_Enable  =0;
U8 gGemini_GetKey              =0;
U8 gGemini_KeyValue            =0;
extern U8 gVifTop;
#if (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)
extern void msVifTopAdjust(void);
#endif
#if (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)
extern BOOL msVifTopAdjust(BYTE ucVifTop);
#endif
extern U8 MApp_ProcessUserInput_MSVIF_Debug(U8 keycode);
#endif

#if ENABLE_IR_BIN
#define IR_BIN_HEADER   32 //32 bytes
#endif

#if(ENABLE_MBIR)
static ST_MBIR mbir = { TRUE, 0xFFFF, 0 , 0};
#endif

#if ENABLE_AUTOTEST
extern BOOLEAN g_bAutobuildDebug;
#endif
#if (ENABLE_MSTV_UART_DEBUG && ENABLE_MMS)
extern U8 g_DisableIr;
#endif





#if(ENABLE_CEC)
extern BOOLEAN gCECProcessCMDbyKey;
extern MS_U8 gCECProcessCMDKeycode;
MS_U16 u16CEC_UserCtrlReleasedTimeIsr = 0;
#endif

#if ENABLE_IR_BIN
U8 g_u8IR_HEADER_CODE0 =0;
U8 g_u8IR_HEADER_CODE1 =0;
#endif

#if EANBLE_V56_IO_KEY
#define VOL_POS() 	Volume_positive_get_level() //xzm @ 20171222
#define VOL_NEG() 	Volume_negative_get_level() //xzm @ 20171222
//按键属性
#define KEY_DOWN_FLAG        0xA0
#define KEY_LONG_FLAG        0xB0
#define KEY_LIAN_FLAG        0xC0
#define KEY_UP_FLAG          0xD0
#define KEY_SERIES_FLAG     150//200      //按键连发开始所需时间长度
#define KEY_SERIES_DELAY    5       //按键连发的时间间隔长度
#endif

//******************************************************************************

BOOLEAN MApp_isKeypadSourceKeyCanSelect(void)
{
    /*/ZUI_TODO:
    if((g_u8MenuPageIndex == MENU_SETUP_A1_Scan_CheckMenu)||
        (g_u8MenuPageIndex == MENU_SETUP_A1_Scan_ConfirmMsg_SkipATV)||
        (g_u8MenuPageIndex == MENU_SETUP_A1_Scan_ConfirmMsg_SkipDTV)||
        (g_u8MenuPageIndex == MENU_CHANNEL_DTV_ManualScan)||
        (g_u8MenuPageIndex == MENU_OPTION_FACTORY_RESET)||  //Restore to default
        (g_u8MenuPageIndex == MENU_TIME_D1_Clock)|| // Cur timer's close option
        (g_u8MenuPageIndex == MENU_TIME_D2_OffTimer)||// off timer 's close option
        (g_u8MenuPageIndex == MENU_TIME_D3_OnTimer)// on timer 's close option
        )
            return TRUE;
    else
            return FALSE;
    */
    return FALSE;
}

#if EANBLE_V56_IO_KEY
static U8 Get_KeyStore_Key(void) //xzm @ 20171222
{
    //if (VOL_POS()==0) return KEY_KEYSTONE_POS;
    //if (VOL_NEG()==0) return KEY_KEYSTONE_NEG;
    if (VOL_POS()==0) return KEY_VOLUME_PLUS;
    if (VOL_NEG()==0) return KEY_VOLUME_MINUS;
    return KEY_NULL;
}


static U8 KEY_SCAN(void)  //xzm @ 20171222
{
	static U8 KEY_STATE =0;//按键状态
	static U8 KEY_PREV  =0;//上一次按键
	static U8 KEY_DELAY =0;//按键连发时间
	static U8 KEY_SERIES = FALSE;//标志连发开始
	U8 KEY_PRESS = KEY_NULL;//按键值
	U8 KEY_RETURN =KEY_NULL;//按键返回值

	KEY_PRESS= Get_KeyStore_Key();

	switch(KEY_STATE)
	{
		case 0://按键初始状态0
			{
				if(KEY_PRESS != KEY_NULL)
				{
					KEY_STATE = 1;//转到按键确认
					KEY_PREV = KEY_PRESS;//保存按键状态
				}
			}
		break;
		case 1://按键确认态01
			{
				if(KEY_PRESS == KEY_PREV)//确认和上次按键相同
				{
					printf(" case 1 KEY_PRESS == KEY_PREV  \n");
					KEY_STATE =2;//ÅÐ¶Ï°´¼ü³¤°´
					//·µ»Ø°´¼ü°´ÏÂ¼üÖµ£¬°´¼ü°´ÏÂ¾ÍÏàÓ¦£¬Èç¹ûÏëµ¯ÆðÀ´ÔÙÏàÓ¦
					//¿ÉÒÔÔÚµ¯ÆðÀ´ºóÔÙ·µ»Ø°´¼üÖµ
					//KEY_RETURN = KEY_DOWN_FLAG| KEY_PREV;
				}
				else//按键抬起，是抖动，不响应按键
				{
					printf(" case 1 KEY_PRESS != KEY_PREV  \n");
					KEY_STATE =0;
				}
			}
		break;
		case 2://按键释放状态10
			{
				if(KEY_PRESS == KEY_NULL)
				{
					printf(" case 2 KEY_PRESS == KEY_NULL  \n");
					KEY_STATE =0;
					KEY_DELAY =0;
					KEY_SERIES=0;
					KEY_RETURN = KEY_UP_FLAG| KEY_PREV;
					break;
				}
				if(KEY_PRESS == KEY_PREV)
				{
					printf(" case 2 KEY_PRESS != KEY_PREV  \n");
					KEY_DELAY++;
					if((KEY_SERIES == TRUE) && (KEY_DELAY > KEY_SERIES_DELAY))
					{
						printf(" case 2 (KEY_SERIES == TRUE) && (KEY_DELAY > KEY_SERIES_DELAY)  \n");
						KEY_DELAY = 0;
						KEY_RETURN = KEY_LIAN_FLAG| KEY_PRESS;//返回连发的值
						KEY_PREV = KEY_PRESS;//记住上次的按键
						break;
					}
					if(KEY_DELAY > KEY_SERIES_FLAG)
					{
						printf(" case 2 KEY_DELAY > KEY_SERIES_FLAG \n");
						KEY_SERIES =TRUE;
						KEY_DELAY =0;
						KEY_RETURN = KEY_LONG_FLAG| KEY_PREV ;//返回长按后的值
						break;
					}
				 }
			}
		break;
		default://按键初始状态0
		break;
	}
	return KEY_RETURN;
}
#endif

#if (IR_CHANNEL_USE_AS_UPDOWN && IR_VOLUME_USE_AS_LEFTRIGHT)
BOOLEAN MApp_isKeypadUPLR(void)
{
   if ((MApp_ZUI_GetActiveOSD() == E_OSD_MAIN_MENU) ||
        (MApp_ZUI_GetActiveOSD() == E_OSD_INPUT_SOURCE) ||
        (MApp_ZUI_GetActiveOSD() == E_OSD_PROGRAM_EDIT) ||
#if(ENABLE_DTV)
        (MApp_ZUI_GetActiveOSD() == E_OSD_DTV_MANUAL_TUNING) ||
#endif
        (MApp_ZUI_GetActiveOSD() == E_OSD_ATV_MANUAL_TUNING) ||
        (MApp_ZUI_GetActiveOSD() == E_OSD_AUTO_TUNING) ||
        (MApp_ZUI_GetActiveOSD() == E_OSD_CHANNEL_LIST) ||
        (MApp_ZUI_GetActiveOSD() == E_OSD_AUDIO_LANGUAGE) ||
        (MApp_ZUI_GetActiveOSD() == E_OSD_SUBTITLE_LANGUAGE) ||
        (MApp_ZUI_GetActiveOSD() == E_OSD_INSTALL_GUIDE) ||
        (MApp_ZUI_GetActiveOSD() == E_OSD_FACTORY_MENU) ||
        (MApp_ZUI_GetActiveOSD() == E_OSD_AUDIO_LANGUAGE) ||
        (MApp_ZUI_GetActiveOSD() == E_OSD_AUDIO_LANGUAGE) ||
        (MApp_ZUI_GetActiveOSD() == E_OSD_AUDIO_LANGUAGE)
        )
    {
        //printf("@@ keypad LRUD\n");
        return TRUE;
    }
    else
        return FALSE;
}
#endif

/******************************************************************************/
/*                             Functions                                      */
/******************************************************************************/
static void MApp_ParseKey(void)
{
#if ENABLE_AUTOTEST
    if(g_bAutobuildDebug)
    {
        return;
    }
#endif

#if (ENABLE_MSTV_UART_DEBUG && ENABLE_MMS)
    if (g_DisableIr)
    {
        return;
    }
#endif

#if( ENABLE_SCRIPT_EXECUTE)
    msUS_UseScript(EN_SCRIPT_EVENT_PROCESSUSERINPUT);
#endif


    MWDBGprintf(MWDBG_KEYINPUT, MWDBGLVL_STATUS_B, "IR:%02dh\n", (int)stKeyStatus.keydata);
	printf("IR:%02dh\n",(int)stKeyStatus.keydata);  
#if (ENABLE_AUDIO_ONLY_CUSTOMERMODE == 1)
    if ( ( g_AudioOnly  == AUDIO_ONLY_ON ) && (IsAnyTVSourceInUse()) )
    {
        u32MonitorAudioOnlyTimer = msAPI_Timer_GetTime0();
        switch ( stKeyStatus.keydata )
        {
            case IRKEY_MUTE:
            case IRKEY_VOLUME_PLUS:
            case IRKEY_VOLUME_MINUS:
            case IRKEY_POWER:
                break;

            default:
                if(fEnableAudioOnlyFunc == ENABLE )
                {
                    g_AudioOnly = AUDIO_ONLY_OFF;
                    //if(!( (IsDTVInUse())&&(MApp_ChanProc_GetCurChannelPointer()->u16VideoPid==0) && (MApp_ChanProc_GetCurChannelPointer()->astSoundTrack[0].u16AudioPid !=0)))
                    //    MApp_SetPictureMode(MAIN_WINDOW, TRUE); //need check
                    MApp_UiMenuFunc_ExitAudioOnlyMode();
                    stKeyStatus.keydata = IRKEY_DUMY;

                }
                break;
        }
    }
#endif

    if(msAPI_IsMBIREnabled())//for OBAMA
    {
        // The key code is parsed in Linux.
        switch(stKeyStatus.keydata)
        {
            case KEY_SUBCODE: // subtitle function was opened by subcode key.
                u8KeyCode = KEY_SUBTITLE;
            break;

            //Mapping keycode,Because some keycode not correct. The same reason.
            //Because some IR key codes are defined un-correctly, so we have to change key mapping below.

            case KEY_FF:
            {
                u8KeyCode = KEY_NEXT;
                break;
            }
            case KEY_REWIND:
            {
                u8KeyCode = KEY_PREVIOUS;
                break;
            }
            case KEY_PREVIOUS:
            {
                u8KeyCode = KEY_REWIND;
                break;
            }
            case KEY_NEXT:
            {
                u8KeyCode = KEY_FF;
                break;
            }

            default:
                u8KeyCode = stKeyStatus.keydata;
                break;
        }

      #if DEBUG_OBAMA_KEY
        static U8 pre_u8KeyCode = 0xFF;
        if(u8KeyCode != pre_u8KeyCode)
        {
            printf("%s %s Line %d: u8KeyCode[0x%X]\n", __FILE__, __FUNCTION__, __LINE__,u8KeyCode);
            pre_u8KeyCode = u8KeyCode;
        }
      #endif
    }
    else
    {
        switch ( stKeyStatus.keydata )
        {
        #if (IR_TYPE_SEL == IR_TYPE_MSTAR_DTV)
            case IRKEY_HOME:                u8KeyCode = KEY_HOME;               break;
        #endif

        #if (ENABLE_DMP == DISABLE)
            case IRKEY_TV_RADIO:            u8KeyCode = KEY_TV_RADIO;           break;
        #endif

            case IRKEY_POWER:
            #if(CHAKRA3_AUTO_TEST)
                // Should not power down
            #else
                u8KeyCode = KEY_POWER;
            #endif
                break;

            case IRKEY_EXIT:                u8KeyCode = KEY_EXIT;               break;

        #if (ENABLE_DTV_EPG)
            case IRKEY_EPG:                 u8KeyCode = KEY_EPG;                break;
        #else
            case IRKEY_EPG:
                u8KeyCode = KEY_EPG;                break;
        #endif //#if (ENABLE_DTV_EPG)

            case IRKEY_UP:
                #if(IR_CHANNEL_USE_AS_UPDOWN==1)
                if((stKeyStatus.keytype == KEY_TYPE_KEYPAD)&&MApp_isKeypadUPLR())
                {
                    u8KeyCode = KEY_UP;
                }
                else if(stKeyStatus.keytype == KEY_TYPE_KEYPAD)
                {
                    u8KeyCode = KEY_CHANNEL_PLUS;
                }
                else
                {
                    u8KeyCode = KEY_UP;
                }
                #else
                 if ((stKeyStatus.keytype == KEY_TYPE_KEYPAD) )
                {
                    u8KeyCode = KEY_CHANNEL_PLUS;
                }
                else
                {
                    u8KeyCode = KEY_UP;
                }
                #endif
                break;
            case IRKEY_CHANNEL_RETURN:      u8KeyCode = KEY_CHANNEL_RETURN;     break;
            case IRKEY_DOWN:
              #if(IR_CHANNEL_USE_AS_UPDOWN==1)
                if ((stKeyStatus.keytype == KEY_TYPE_KEYPAD)&&MApp_isKeypadUPLR() )//ZUI_TODO: &&
                {
                    u8KeyCode = KEY_DOWN;
                }
                else if(stKeyStatus.keytype == KEY_TYPE_KEYPAD)
                {
                    u8KeyCode = KEY_CHANNEL_MINUS;
                }
                else
                {
                    u8KeyCode = KEY_DOWN;
                }
                #else
                if(stKeyStatus.keytype == KEY_TYPE_KEYPAD)
                {
                    u8KeyCode = KEY_CHANNEL_MINUS;
                }
                else
                {
                    u8KeyCode = KEY_DOWN;
                }
                #endif
                break;
            case IRKEY_RIGHT:
              // special case : when in input select mode, the KEYPAD LEFT/RIGHT is interpreted as VolUP/VolDOWN
              #if(IR_VOLUME_USE_AS_LEFTRIGHT==1)
                if ((stKeyStatus.keytype == KEY_TYPE_KEYPAD)&&MApp_isKeypadUPLR())
                {
                    u8KeyCode = KEY_RIGHT;
                }
                else if(stKeyStatus.keytype == KEY_TYPE_KEYPAD)
                {
                    u8KeyCode = KEY_VOLUME_PLUS;
					if(MApp_ZUI_GetActiveOSD() == E_OSD_INPUT_SOURCE||MApp_DMP_GetDmpUiState() == DMP_UI_STATE_MEDIA_SELECT||
					MApp_DMP_GetDmpUiState() == DMP_UI_STATE_FILE_SELECT)
					{
						u8KeyCode = KEY_DOWN; 
					}
                }
                else
                {
                    u8KeyCode = KEY_RIGHT;
                }
                #else
                if(stKeyStatus.keytype == KEY_TYPE_KEYPAD)
                {
                    u8KeyCode = KEY_VOLUME_PLUS;
					if(MApp_ZUI_GetActiveOSD() == E_OSD_INPUT_SOURCE||MApp_DMP_GetDmpUiState() == DMP_UI_STATE_MEDIA_SELECT||
					MApp_DMP_GetDmpUiState() == DMP_UI_STATE_FILE_SELECT)
					{
						u8KeyCode = KEY_DOWN; 
					}
                }
                else
                {
                    u8KeyCode = KEY_RIGHT;
                }
                #endif
                break;
            case IRKEY_LEFT:
               // special case : when in input select mode, the KEYPAD LEFT/RIGHT is interpreted as VolUP/VolDOWN
               #if(IR_VOLUME_USE_AS_LEFTRIGHT==1)
               if ((stKeyStatus.keytype == KEY_TYPE_KEYPAD)&&MApp_isKeypadUPLR() )
               {
                    u8KeyCode = KEY_LEFT;
                }
                else if(stKeyStatus.keytype == KEY_TYPE_KEYPAD)
                {
                    u8KeyCode = KEY_VOLUME_MINUS;
					if(MApp_ZUI_GetActiveOSD() == E_OSD_INPUT_SOURCE||MApp_DMP_GetDmpUiState() == DMP_UI_STATE_MEDIA_SELECT||
					MApp_DMP_GetDmpUiState() == DMP_UI_STATE_FILE_SELECT)
					{
						u8KeyCode = KEY_UP; 
					}
                }
                else
                {
                    u8KeyCode = KEY_LEFT;
                }
                #else
                if(stKeyStatus.keytype == KEY_TYPE_KEYPAD)
                {
                    u8KeyCode = KEY_VOLUME_MINUS;
					if(MApp_ZUI_GetActiveOSD() == E_OSD_INPUT_SOURCE||MApp_DMP_GetDmpUiState() == DMP_UI_STATE_MEDIA_SELECT||
					MApp_DMP_GetDmpUiState() == DMP_UI_STATE_FILE_SELECT)
					{
						u8KeyCode = KEY_UP; 
					}
                }
                else
                {
                    u8KeyCode = KEY_LEFT;
                }
                #endif
                break;
            case IRKEY_SELECT:              u8KeyCode = KEY_SELECT;             break;
#if (IR_TYPE_SEL != IR_TYPE_NEW)
            case IRKEY_BACK:                u8KeyCode = KEY_BACK;               break;
#endif
            case IRKEY_NUM_0:               u8KeyCode = KEY_0;                  break;
            case IRKEY_NUM_1:               u8KeyCode = KEY_1;                  break;
            case IRKEY_NUM_2:               u8KeyCode = KEY_2;                  break;
            case IRKEY_NUM_3:               u8KeyCode = KEY_3;                  break;
            case IRKEY_NUM_4:               u8KeyCode = KEY_4;                  break;
            case IRKEY_NUM_5:               u8KeyCode = KEY_5;                  break;
            case IRKEY_NUM_6:               u8KeyCode = KEY_6;                  break;

        #if (SCAN_TEST_MODE_ENABLE==1)
            case IRKEY_NUM_7:
                u8KeyCode = KEY_7;
                AutoScanTest.u8State= TEST_MODE_ATV_SCAN_STATE_DISABLE;
                AutoScanTest.u16VerifyCount=0;
                printf("Test--> Test Mode ATV Scan = Disable\n");
                break;

            case IRKEY_NUM_8:
                u8KeyCode = KEY_8;
                AutoScanTest.u8State= TEST_MODE_ATV_SCAN_STATE_SAVE_DATA;
                AutoScanTest.u16VerifyCount=0;
                printf("Test--> Test Mode ATV Scan = SAVE_DATA\n");
                break;

            case IRKEY_NUM_9:
                u8KeyCode = KEY_9;
                AutoScanTest.u8State= TEST_MODE_ATV_SCAN_STATE_VERIFY;
                AutoScanTest.u16VerifyCount=0;
                AutoScanTest.u16Total_Lost_Channel=0;
                AutoScanTest.u16Total_Ghost_Channel=0;
                switch (AutoScanTest.u16VerifyCountInput)
                {
                    case 1://30 min
                        AutoScanTest.u16VerifyCountInput=10;//60 min
                        printf("Test--> VerifyCountInput = 10, (30 minutes) \n");
                        break;
                    case 10://30 min
                        AutoScanTest.u16VerifyCountInput=20;//60 min
                        printf("Test--> VerifyCountInput = 20, (60 minutes) \n");
                        break;
                    case 20:
                        AutoScanTest.u16VerifyCountInput=50;//300 min = 5 hours
                        printf("Test--> VerifyCountInput = 50, (5 hours) \n");
                        break;
                    case 50://5 hours
                        AutoScanTest.u16VerifyCountInput=100;//10hours
                        printf("Test--> VerifyCountInput = 100, (10 hours) \n");
                        break;
                    case 100://10 hours
                        AutoScanTest.u16VerifyCountInput=10000;//1000hours = 41 days
                        printf("Test--> VerifyCountInput = 10000, (41 days) \n");
                        break;
                    default://10 hours
                        AutoScanTest.u16VerifyCountInput=1;
                        printf("Test--> VerifyCountInput = 1, (3~ minutes) \n");
                        break;
                }

                printf("Test--> Test Mode ATV Scan = Verify \n");
                break;
        #else
            case IRKEY_NUM_7:               u8KeyCode = KEY_7;                  break;
            case IRKEY_NUM_8:               u8KeyCode = KEY_8;                  break;
            case IRKEY_NUM_9:               u8KeyCode = KEY_9;                  break;
        #endif

            case IRKEY_CHANNEL_FAV_LIST:
        #if(IR_TYPE_SEL == IR_TYPE_MSTAR_DTV)
            case IRKEY_GUIDE:
        #endif
                u8KeyCode = KEY_CHANNEL_FAV_LIST;
                break;

            case IRKEY_MUTE:                u8KeyCode = KEY_MUTE;               break;
            case IRKEY_FREEZE:              u8KeyCode = KEY_FREEZE;             break;
            case IRKEY_INFO:                u8KeyCode = KEY_INFO;               break;
            case IRKEY_AUDIO:               u8KeyCode = KEY_AUDIO;              break;
            case IRKEY_MTS:                 u8KeyCode = KEY_MTS;                break;
#if (IR_TYPE_SEL != IR_TYPE_CUS21SH)
            case IRKEY_PICTURE:             u8KeyCode = KEY_PICTURE;            break;
#endif
            case IRKEY_ZOOM:                u8KeyCode = KEY_ZOOM;               break;
            case IRKEY_RED:                 u8KeyCode = KEY_RED;                break;
            case IRKEY_GREEN:               u8KeyCode = KEY_GREEN;              break;
            case IRKEY_YELLOW:              u8KeyCode = KEY_YELLOW;             break;
            case IRKEY_BLUE:                u8KeyCode = KEY_BLUE;               break;
#if (IR_TYPE_SEL != IR_TYPE_NEW)
            case IRKEY_RED2:                u8KeyCode = KEY_RED;                break;
            case IRKEY_GREEN2:              u8KeyCode = KEY_GREEN;              break;
#endif
            case IRKEY_SUBTITLE:            u8KeyCode = KEY_SUBTITLE;           break;

#if (IR_TYPE_SEL != IR_TYPE_NEW)
            case IRKEY_UPDATE:              u8KeyCode = KEY_UPDATE;             break;        // add UPDATE key
            case IRKEY_TTX_MODE:            u8KeyCode = KEY_TTX_MODE;           break;
#endif
            case IRKEY_MIX:                 u8KeyCode = KEY_MIX;                break;
#if (IR_TYPE_SEL != IR_TYPE_CUS21SH)
            case IRKEY_CLOCK:               u8KeyCode = KEY_CLOCK;              break;
#endif
            case IRKEY_TTX:                 u8KeyCode = KEY_TTX;                break;
            case IRKEY_SIZE:                u8KeyCode = KEY_SIZE;               break;
            case IRKEY_HOLD:                u8KeyCode = KEY_HOLD;               break;
            case IRKEY_INDEX:               u8KeyCode = KEY_INDEX;              break;

            case IRKEY_CHANNEL_LIST:        u8KeyCode = KEY_CHANNEL_LIST;       break;
            case IRKEY_SLEEP:               u8KeyCode = KEY_SLEEP;              break;
            case IRKEY_DASH:                u8KeyCode = KEY_DASH;               break;
            case IRKEY_TV_INPUT:            u8KeyCode = KEY_TV_INPUT;           break;

            //Because some IR key codes are defined un-correctly, so we have to change key mapping below.
            case IRKEY_BACKWARD:            u8KeyCode = KEY_PREVIOUS;            break;
            case IRKEY_FORWARD:             u8KeyCode = KEY_NEXT;                break;

          #if (ENABLE_DMP)
            case IRKEY_PAGE_UP:             u8KeyCode = KEY_PAGE_UP;             break;
          #endif

            case IRKEY_PAGE_DOWN:           u8KeyCode = KEY_PAGE_DOWN;           break;
            case IRKEY_PREVIOUS:            u8KeyCode = KEY_FF;                  break;
            case IRKEY_NEXT:                u8KeyCode = KEY_REWIND;              break;
#if (IR_TYPE_SEL != IR_TYPE_NEW)
            case IRKEY_CC:                  u8KeyCode = KEY_CC;                  break;
#endif

            case IRKEY_CHANNEL_PLUS:
             #if(IR_CHANNEL_USE_AS_UPDOWN==1)
                if((stKeyStatus.keytype == KEY_TYPE_KEYPAD)&&MApp_isKeypadUPLR())
             #else
                if ((stKeyStatus.keytype == KEY_TYPE_KEYPAD) )
             #endif
                {
                    u8KeyCode = KEY_UP;
                }
                else
                {
                    u8KeyCode = KEY_CHANNEL_PLUS;
                }
                break;

            case IRKEY_CHANNEL_MINUS:
              #if(IR_CHANNEL_USE_AS_UPDOWN==1)
                if ((stKeyStatus.keytype == KEY_TYPE_KEYPAD)&&MApp_isKeypadUPLR() )//ZUI_TODO: &&
              #else
                if ((stKeyStatus.keytype == KEY_TYPE_KEYPAD) )
              #endif
                {
                    u8KeyCode = KEY_DOWN;
                }
                else
                {
                    u8KeyCode = KEY_CHANNEL_MINUS;
                }
                break;

            case IRKEY_VOLUME_PLUS:
                // special case : when in input select mode, the KEYPAD LEFT/RIGHT is interpreted as VolUP/VolDOWN
              #if(IR_VOLUME_USE_AS_LEFTRIGHT==1)
                if ((stKeyStatus.keytype == KEY_TYPE_KEYPAD)&&MApp_isKeypadUPLR())
                {
                    u8KeyCode = KEY_RIGHT;
                }
                else
                {
                    u8KeyCode = KEY_VOLUME_PLUS;
                }
              #else
                if ((stKeyStatus.keytype == KEY_TYPE_KEYPAD) )//ZUI_TODO: &&
                {
                    u8KeyCode = KEY_VOLUME_PLUS;
                }
                else if((stKeyStatus.keytype == KEY_TYPE_KEYPAD) )//ZUI_TODO: &&
                {
                    u8KeyCode = KEY_SELECT;
                }
                else if((stKeyStatus.keytype == KEY_TYPE_KEYPAD) )//ZUI_TODO: &&
                    //ZUI_TODO: (enMenuFlowState != FS_WAIT_MENU))
                {
                    u8KeyCode = KEY_RIGHT;
                }
                else
                {
                    u8KeyCode = KEY_VOLUME_PLUS;
                }
              #endif
                break;

            case IRKEY_VOLUME_MINUS:
                // special case : when in input select mode, the KEYPAD LEFT/RIGHT is interpreted as VolUP/VolDOWN
               #if(IR_VOLUME_USE_AS_LEFTRIGHT==1)
                   if ((stKeyStatus.keytype == KEY_TYPE_KEYPAD)&&MApp_isKeypadUPLR() )
                   {
                    u8KeyCode = KEY_LEFT;
                    }
                else
                   {
				   	if(stGenSetting.g_SoundSetting.Volume != 0){
						u8KeyCode = KEY_VOLUME_MINUS;
					}
                   }
              #else
                if ((stKeyStatus.keytype == KEY_TYPE_KEYPAD) )//ZUI_TODO: &&
                {
                    u8KeyCode = KEY_VOLUME_MINUS;
                }
             else if((stKeyStatus.keytype == KEY_TYPE_KEYPAD) )//ZUI_TODO: &&
                    //ZUI_TODO: (g_u8MenuPageIndex==MENU_INPUT_SOURCE))
                {
                  u8KeyCode = KEY_SELECT;
                }
                else if((stKeyStatus.keytype == KEY_TYPE_KEYPAD) )//ZUI_TODO: &&
                    //ZUI_TODO: (enMenuFlowState != FS_WAIT_MENU))
                {
                    u8KeyCode = KEY_LEFT;
                }

                else
                {
                    u8KeyCode = KEY_VOLUME_MINUS;
                }
            #endif
                break;

            case IRKEY_MENU:
                u8KeyCode = KEY_MENU;
                break;

            case IRKEY_INPUT_SOURCE:
                if(stKeyStatus.keytype==KEY_TYPE_KEYPAD)
                {
                    if(MApp_isKeypadSourceKeyCanSelect() == TRUE)
                    {
                        u8KeyCode = KEY_SELECT;
                    }
                    u8KeyCode = KEY_INPUT_SOURCE;
                }
                else
                {
                    u8KeyCode = KEY_INPUT_SOURCE;
                }
                break;

            case IRKEY_ADJUST:                  u8KeyCode = KEY_ADJUST;             break;
            case IRKEY_KEY_DISABLE_KEYPAD:      u8KeyCode = KEY_DISABLE_KEYPAD;     break;
            case IRKEY_REVEAL:                  u8KeyCode = KEY_REVEAL;             break;

        #if ENABLE_DMP || ENABLE_PVR
            case IRKEY_RECORD:                  u8KeyCode = KEY_RECORD;           break;
            case IRKEY_STOP:                    u8KeyCode = KEY_STOP;             break;
        #else
            //CEC
        #endif

        #if 1
    //        case IRKEY_CC:                       u8KeyCode = KEY_UARTDEBUGPORT;      break;
          #if 1
            case IRKEY_PLAY:         printf("hotkey IR_KEY_PLAY \n");              u8KeyCode = KEY_PLAY;               break;
            case IRKEY_PAUSE:                    u8KeyCode = KEY_PAUSE;              break;
          #endif
        #endif

            case IRKEY_SUBPAGE:                 u8KeyCode = KEY_SUBPAGE;            break;
            case IRKEY_DTV:                     u8KeyCode = KEY_DTV;                 break;
            case IRKEY_TV:                      u8KeyCode = KEY_TV;                    break;
#if (IR_TYPE_SEL != IR_TYPE_CUS21SH)
            case IRKEY_SCART:                   u8KeyCode = KEY_SCART;             break;
            case IRKEY_HDMI:                    u8KeyCode = KEY_HDMI;                 break;
            case IRKEY_AV:                      u8KeyCode = KEY_AV;                 break;
#endif

            case IRKEY_PC:                      u8KeyCode = KEY_PC;                    break;
            case IRKEY_COMPONENT:               u8KeyCode = KEY_COMPONENT;             break;
            case IRKEY_SV:                      u8KeyCode = KEY_SV;                    break;

#if (IR_TYPE_SEL == IR_TYPE_SAMSUNG_REMOTE)
            case IRKEY_MEDIA_PLAYER:    u8KeyCode = KEY_MEDIA_PLAYER;   break;
            case IRKEY_TOOL:                u8KeyCode = KEY_TOOL;   break;
#endif
            default:                             u8KeyCode = KEY_NULL;               break;
        }
    }
	printf("IR:%02d \n", u8KeyCode); 
#if ( ENABLE_NO_OPERATE_AUTO_SLEEP )
    if( u8KeyCode != KEY_NULL )
    {
        MApp_NoOperateAutoSleep_ResetOpTime();
    }
#endif

#if ( ENABLE_CI_PLUS_V1_4 )
    if( u8KeyCode != KEY_EXIT )
    {
        if( g_bPowerDownCheckCICAM )
        {
            u8KeyCode = KEY_NULL;
        }
    }
    else
    {
        MApp_CI_PowerDown_Reset();
    }
#endif  //ENABLE_CI_PLUS_V1_4

#if (ENABLE_KEY_LOGGER && _KEYLOGGER_CAPTURE_BY_SPECIAL_IR_KEY_)
    MApp_KeyLogger_ComboKeyChecker(u8KeyCode);
#endif


  #if ( ENABLE_CHCHANGETIME )
    if (u8KeyCode != KEY_NULL)
    {
        gbKeyPress = TRUE;
        gU32ChChangeTime = msAPI_Timer_GetTime0();
        printf("[ch change time]start\n");
    }
  #endif

#if ( CHAKRA3_AUTO_TEST )
    if (u8KeyCode != KEY_NULL)
    {
        g_AT_en8ChangeChannelState = E_AUTO_TEST_CHANGE_CHANNEL_START;
        //printf("[CK3_Auto_Test] ch change start\n");
        MApp_AT_SendEvent( E_AT_EVENT_CHANGE_CHANNEL_TIME_START, (void*)MsOS_GetSystemTime() );
    }
#endif

#if(DEBUG_CHG_SRC_TIME)
    //printf("ChgSrc start %u\n", MsOS_GetSystemTime());
    g_Debug_u32Time_ChangeSrc = 0;
    g_Debug_bChangeSrc = 1;

 #if( ENABLE_LOG_FILE_IN_MEM )
    Debug_Log_Reset(0);
 #endif

    msDebug_PrintChgSrcTime("Got Key --> Start");
#endif

    g_Debug_u32Time_ChangeChannel = 0;

    MApp_SetKeyRepeatState(u8KeyCode);

#if(ENABLE_EWS)
    //if(u8KeyCode != KEY_NULL)
    //    printf("\r\nu8KeyCode=%x",u8KeyCode);

    if(MApp_EWS_DisasterStatusCheck()== TRUE) //customized
    {
        //printf("\r\nStatus=%x   Flage=%x",MApp_EWS_GetStatus(),MApp_EWS_GetMsgCancelFlag());
        if((MApp_EWS_GetStatus()== EN_EWS_WASPADA)&&(MApp_EWS_GetMsgCancelFlag()== TRUE))
        {
            //bypass: cancel WASPASA msg status
        }
        else
        {

            if((MApp_ZUI_GetActiveOSD() == E_OSD_MESSAGE_BOX) && (MApp_ZUI_API_IsWindowVisible(HWND_EWS_FRAME) == TRUE  || MApp_ZUI_API_IsWindowVisible(HWND_EWS_FRAME_WASPADA) == TRUE))
            {


                if(u8KeyCode != KEY_POWER)
                {
                    if((u8KeyCode == KEY_EXIT) && (MApp_EWS_GetStatus()== EN_EWS_WASPADA))
                    {
                        MApp_EWS_SetMsgCancelFlag(TRUE); //cancel EWS
                    }
                    else if((u8KeyCode == KEY_UP) && (MApp_EWS_GetStatus()== EN_EWS_WASPADA))
                    {
                        //SCROLL UP
                        MApp_EWS_Scroll_Text(EN_EWS_SCROLL_UP);
                    }
                    else if((u8KeyCode == KEY_DOWN) && (MApp_EWS_GetStatus()== EN_EWS_WASPADA))
                    {
                        //SCROLL DOWN
                        MApp_EWS_Scroll_Text(EN_EWS_SCROLL_DOWN);
                    }

                    if(MApp_EWS_GetStatus()!= EN_EWS_AWAS)
                        u8KeyCode = KEY_NULL;
                }
            }
        }
    }
    if(MApp_EWS_GetStatus()== EN_EWS_AWAS)
    {
       if(u8KeyCode != KEY_POWER)
       {
         if(u8KeyCode == KEY_UP)
        {
            //SCROLL UP
          MApp_EWS_Scroll();
          MApp_EWS_Scroll_Text(EN_EWS_SCROLL_UP);
        }
        else if(u8KeyCode == KEY_DOWN)
        {
            //SCROLL DOWN
             MApp_EWS_Scroll();
             MApp_EWS_Scroll_Text(EN_EWS_SCROLL_DOWN);
        }
        u8KeyCode = KEY_NULL;
      }
    }
#endif

#if 0
    if (u8KeyCode != KEY_NULL)
    {
        printf("ParseKey -> %u\n", u8KeyCode);
        if( u8KeyCode == KEY_POWER )
        {
            printf("Got KEY_POWER\n");
        }
    }
#endif
}

/******************************************************************************/
static void MApp_SetKeyRepeatState(U8 u8KeyData)
{
    if ( u8KeyData == KEY_UP             ||
         u8KeyData == KEY_DOWN           ||
         u8KeyData == KEY_LEFT           ||
         u8KeyData == KEY_RIGHT          ||
         u8KeyData == KEY_VOLUME_PLUS    ||
         u8KeyData == KEY_VOLUME_MINUS   ||
         u8KeyData == KEY_CHANNEL_PLUS   ||
         u8KeyData == KEY_CHANNEL_MINUS )
    {
        u8KeyRepeatState = OSD_REPEAT_ENABLE;
    }
    else
    {
        u8KeyRepeatState = OSD_REPEAT_DISABLE;
    }
}

#define System_Stable_Testing   0

#if System_Stable_Testing
#define KEY_TIMEOUT_1MS  (1000LU)
U8 Test_Key = 0;
U32 Test_Time = 0;
#endif

#if ENABLE_IR_BIN
U32 MApp_IR_Bin_Cal_Checksum(U8* pu8BinData, U32 u32BinDataSize)
{
    U32 i;
    U32 u32BinChecksum = 0;

    for( i = 0; i < u32BinDataSize; i++ )
    {
         if(i<IR_BIN_HEADER)
         {
            //do nothing
         }
         else
         {
            u32BinChecksum += pu8BinData[i];
         }
    }

    return u32BinChecksum;
}

void MApp_IrBin_Init(void)
{
#if 0
    g_u16IRkeyMap[IRKEY_MENU] = IRKEY_MENU;
    g_u16IRkeyMap[IRKEY_UP] = IRKEY_UP;
    g_u16IRkeyMap[IRKEY_DOWN] = IRKEY_DOWN;
    g_u16IRkeyMap[IRKEY_LEFT] = IRKEY_LEFT;
    g_u16IRkeyMap[IRKEY_RIGHT] = IRKEY_RIGHT;
    g_u16IRkeyMap[IRKEY_SELECT] = IRKEY_SELECT;
#endif

    BININFO BinInfo;
    BOOLEAN bResult;

    BinInfo.B_ID = BIN_ID_IR_MSTAR;

    msAPI_MIU_Get_BinInfo(&BinInfo, &bResult);

    if(bResult == PASS && BinInfo.B_Len < sizeof(g_u32Section))
    {
        U8* pu8Buf = au8Section;
        U32 u32CheckSum =0;

        U32 u32LoadBin_Dec = (((POOL_BUFFER_ADR+BUF_FOR_DECOMPRESS_OFFSET1) & MIU1) ? ((POOL_BUFFER_ADR+BUF_FOR_DECOMPRESS_OFFSET1) | MIU_INTERVAL) : (POOL_BUFFER_ADR+BUF_FOR_DECOMPRESS_OFFSET1));
        U32 u32LoadBin_Tmp = (((POOL_BUFFER_ADR+BUF_FOR_DECOMPRESS_OFFSET2) & MIU1) ? ((POOL_BUFFER_ADR+BUF_FOR_DECOMPRESS_OFFSET2) | MIU_INTERVAL) : (POOL_BUFFER_ADR+BUF_FOR_DECOMPRESS_OFFSET2));

        if( SUCCESS == MDrv_DMA_LoadBin(&BinInfo, (U32)pu8Buf, _PA2VA(u32LoadBin_Dec), _PA2VA(u32LoadBin_Tmp) ) )
        {
            U16 i;

            if((pu8Buf[2]==NULL)&&(pu8Buf[3]==NULL))
            {
                g_u8IR_HEADER_CODE0 = IR_HEADER_CODE0;
                g_u8IR_HEADER_CODE1 = IR_HEADER_CODE1;
                printf("The Custom ID in IR Bin is null!\n");
            }
            else
            {
                g_u8IR_HEADER_CODE0 = pu8Buf[2];
                g_u8IR_HEADER_CODE1 = pu8Buf[3];
            }

            //printf("g_u8IR_HEADER_CODE0=%X,g_u8IR_HEADER_CODE1=%X\n",g_u8IR_HEADER_CODE0,g_u8IR_HEADER_CODE1);

            U32 ChecksumInBin = (pu8Buf[31]<<24)+(pu8Buf[30]<<16)+(pu8Buf[29]<<8)+(pu8Buf[28]);
            //BinInfo.B_Len=BinDataSize + DummyZeroBytes + CRC16Bytes
            U32 BinDataSize = BinInfo.B_Len-2;//minus 2 bytes for CRC16Bytes
            BinDataSize= BinDataSize-(BinDataSize%8);//minus BinDataSize%8 bytes for dummy
            u32CheckSum=MApp_IR_Bin_Cal_Checksum(pu8Buf,BinDataSize);
            if(u32CheckSum!=ChecksumInBin)
            {
               printf("\nIR Bin checksum is wrong!!(%X,%X)\n",u32CheckSum,ChecksumInBin);
            }

            pu8Buf = pu8Buf + IR_BIN_HEADER;

            //printf("BinInfo.B_Len=%X\n",BinInfo.B_Len);

            for(i=IR_BIN_HEADER+1; i<BinInfo.B_Len; i+=3)
            {
                U8 u8Cmd    = *pu8Buf++;
                U8 u8Data1  = *pu8Buf++;
                U8 u8Data2  = *pu8Buf++;

                switch(u8Cmd)
                {
                    //case IRBIN_HEADER_CODE0:
                        //break;

                    //case IRBIN_HEADER_CODE1:
                        //break;

                    case IRBIN_KEYMAP_CODE:
                        g_u16IRkeyMap[u8Data1] = u8Data2 | 0x1000;
                        break;

                    case IRBIN_BIN_END:
                        i = BinInfo.B_Len;
                        break;
                }
                // printf(ANSI_COLOR_GREEN"u8Cmd %x, %x, %x\n", u8Cmd, u8Data1, u8Data2);
            }

        }

    }
}

U8 MApp_IrBin_GetKeyCode(U8 u8Key)
{
    U16 i;

    for(i=0; i<IRBIN_NUM; i++)
    {
        if((g_u16IRkeyMap[i]&0xff) == u8Key)
            return (U8)i;
    }
    return NULL;
}

#endif

static void MApp_CheckKeyStatus(void)
{
    U8 key;
    U8 KeyRepeatStatus;
  #if ENABLE_KEY_LOGGER
    U8 u8KeyType=0;
  #endif


    if ( msAPI_GetKeyPad(&key, &KeyRepeatStatus)== MSRET_OK )
    {
        stKeyStatus.keytype = KEY_TYPE_KEYPAD;
        stKeyStatus.keydown = TRUE;
        stKeyStatus.keydata = key;
        stKeyStatus.keyrepeat = KeyRepeatStatus;
      #if ENABLE_KEY_LOGGER
        MApp_KeyLogger_Action_Save(KEY_TYPE_KEYPAD, key, KeyRepeatStatus);

        //When user enter any key input during key logger simulation
        //Termination simulation and ignore current key
        if(MApp_KeyLogger_TerminateSimulation())
        {
            stKeyStatus.keydown = FALSE;
        }
      #endif
        //printf(" SAR value = 0x%02x, Repeat = %u \n", key, KeyRepeatStatus);
    }
    else if ( msAPI_GetIRKey(&key, &KeyRepeatStatus) == MSRET_OK )
    {
        stKeyStatus.keytype = KEY_TYPE_IR;
#if ENABLE_IR_BIN
        if(g_u16IRkeyMap[key])
        {
            stKeyStatus.keydown = TRUE;
            stKeyStatus.keydata = (U8)(g_u16IRkeyMap[key] & 0xFF);
        }
#else
        stKeyStatus.keydown = TRUE;
        stKeyStatus.keydata = key;
#endif
        stKeyStatus.keyrepeat = KeyRepeatStatus;
      #if ENABLE_KEY_LOGGER
        MApp_KeyLogger_Action_Save(KEY_TYPE_IR, key, KeyRepeatStatus);
        //When user enter any key input during key logger simulation
        //Termination simulation and ignore current key
        if(MApp_KeyLogger_TerminateSimulation())
        {
            stKeyStatus.keydown = FALSE;
        }
      #endif
        //printf(" IR value = 0x%02bx, Repeat = %bu \n", key, KeyRepeatStatus);
    }
  #if ENABLE_KEY_LOGGER
    else if (MApp_KeyLogger_GetSimulatedKey(&key, &u8KeyType, &KeyRepeatStatus))
    {
        stKeyStatus.keytype = u8KeyType;
        stKeyStatus.keydown = TRUE;
        stKeyStatus.keydata = key;
        stKeyStatus.keyrepeat = KeyRepeatStatus;
    }
  #endif
#if(ENABLE_MBIR)
    else if( mbir.empty == FALSE )
    {
        stKeyStatus.keytype=KEY_TYPE_IR;
        stKeyStatus.keydown=TRUE;
        stKeyStatus.keydata=(U8)mbir.keydata;
        printf("Has IR Key=0x%X\n", stKeyStatus.keydata);
        stKeyStatus.keyrepeat = mbir.repeat;
        mbir.empty = TRUE;
    }
#endif
    else
    {
        stKeyStatus.keydown   = FALSE;
        stKeyStatus.keydata   = KEY_NULL;
        stKeyStatus.keyrepeat = FALSE;
    }


#if System_Stable_Testing
    if (Test_Key != 0)
    {
        stKeyStatus.keytype = KEY_TYPE_IR;
        stKeyStatus.keydown = TRUE;
        stKeyStatus.keyrepeat = 0;
    }
#endif


#if(CHAKRA3_AUTO_TEST)
    if( stKeyStatus.keydown == FALSE )
    {
        if( MApp_AT_Get_SimuIRKey(&key) )
        {
            stKeyStatus.keydata = key;
            stKeyStatus.keytype = KEY_TYPE_IR;
            stKeyStatus.keydown = TRUE;
            stKeyStatus.keyrepeat = FALSE;
        }
    }
#endif

#if 0
    if( stKeyStatus.keydown )
    {
        if( KEY_TYPE_KEYPAD == stKeyStatus.keytype )
            printf(" [KEYPAD]");
        else if( KEY_TYPE_IR == stKeyStatus.keytype )
            printf(" [IR]");
        else
            printf(" keytype=%u\n", stKeyStatus.keytype);

        printf("keydata=%u\n", stKeyStatus.keydata);
        printf("keyrepeat=%u\n", stKeyStatus.keyrepeat);
    }
#endif
}

#define System_Script_Testing   0

#if System_Script_Testing
U8 u8KeyScriptOn=0;


U8 code u8ScriptKeys[] = {

    KEY_CHANNEL_PLUS,KEY_CHANNEL_PLUS,0x81,KEY_EXIT, 0x83,
    KEY_CHANNEL_MINUS,KEY_CHANNEL_MINUS,0x81,KEY_EXIT, 0x83,

    #if 0
    // rotate OSD
    KEY_MENU, KEY_RIGHT, KEY_RIGHT,
    //  scan channel
    KEY_SELECT, KEY_DOWN, KEY_DOWN, KEY_SELECT, KEY_DOWN, KEY_GREEN, 0x85,
    // adjust volume
    KEY_VOLUME_PLUS, KEY_VOLUME_PLUS, KEY_VOLUME_PLUS, 0x83,
    // change channel,
    KEY_SELECT, KEY_UP, KEY_SELECT, 0x84,
    // change to PC
    KEY_INPUT_SOURCE, KEY_UP, KEY_SELECT, 0x83,
    // mute
    KEY_MUTE,
    #endif
};
U16 u16ScriptIndex = 0;
U32 u32WaitTime = 0;
#endif

#if 0
#if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN)|| \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA)|| \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) )
BOOLEAN MDrv_Power_CheckPowerOnKey(void)
{
    U8 key;
    U8 KeyRepeatStatus;
    KEYSTAT tmpKeyStatus;

    memset(&tmpKeyStatus, 0, sizeof(KEYSTAT));

    tmpKeyStatus.keydata = 0xFF;
    tmpKeyStatus.keydown = FALSE;

    if ( msAPI_GetIRKey(&key, &KeyRepeatStatus) == MSRET_OK )
    {
        tmpKeyStatus.keytype = KEY_TYPE_IR;
        tmpKeyStatus.keydown = TRUE;
        tmpKeyStatus.keydata = key;
        tmpKeyStatus.keyrepeat = KeyRepeatStatus;
        KEY_DEBUG( printf(" IR key value = 0x%02bx, KeyRepeatStatus = %bu \n", key, KeyRepeatStatus) );
    }
    else if ( msAPI_GetKeyPad(&key, &KeyRepeatStatus)== MSRET_OK )
    {
        tmpKeyStatus.keytype = KEY_TYPE_KEYPAD;
        tmpKeyStatus.keydown = TRUE;
        tmpKeyStatus.keydata = key;
        tmpKeyStatus.keyrepeat = KeyRepeatStatus;
        KEY_DEBUG(printf(" Keypad key value = 0x%02bx, KeyRepeatStatus = %bu \n", key, KeyRepeatStatus));
    }

    if ( tmpKeyStatus.keydown )
    {
        MApp_ParseKey();

        if ( tmpKeyStatus.keydata == IRKEY_POWER )
            return TRUE;
    }

    return FALSE;
}
#endif
#endif


/*******************************************************************************************/
#if (IR_TYPE_SEL == IR_TYPE_SAMSUNG_REMOTE)
static void MApp_CheckRepeatKey(void)
{
#if System_Stable_Testing
    switch(u8KeyCode)
    {
        case KEY_NULL:
            break;
        case KEY_RED:
            Test_Key = 1;
            break;
        case KEY_HOLD:
            Test_Key = 2;
            break;
        case KEY_YELLOW:
            Test_Key = 3;
            break;
        case KEY_BLUE:
            Test_Key = 4;
            break;
        case KEY_PLAY:
            MDrv_Power_ResetAndPowerUp();
            break;
        default:
            Test_Key = 0;
            break;
    }

    switch(Test_Key)
    {
        case 1:
            u8KeyCode = KEY_RIGHT;
            break;
        case 2:
            if (msAPI_Timer_DiffTimeFromNow( Test_Time ) > KEY_TIMEOUT_1MS)
            {
                Test_Time = msAPI_Timer_GetTime0();
                u8KeyCode = KEY_LEFT;
            }
            break;
        case 3:
            u8KeyCode = KEY_DOWN;
            break;
        case 4:
            if (msAPI_Timer_DiffTimeFromNow( Test_Time ) > 5 * KEY_TIMEOUT_1MS)
            {
                Test_Time = msAPI_Timer_GetTime0();
                u8KeyCode = KEY_UP;
            }
            break;
        case 0:
        default:
            break;
    }
#endif

    switch(u8KeyCode)
    {
        case KEY_RIGHT:
        case KEY_LEFT:
        case KEY_VOLUME_PLUS:
        case KEY_VOLUME_MINUS:
        case KEY_UP:
        case KEY_PAGE_UP:
        case KEY_DOWN:
        case KEY_PAGE_DOWN:
        case KEY_CHANNEL_PLUS:
        case KEY_CHANNEL_MINUS:
        case KEY_INPUT_SOURCE:
            stKeyStatus.RepeatEnable = TRUE;
            break;
        default:
            stKeyStatus.RepeatEnable = FALSE;
            break;
    }
}
#endif

/******************************************************************************/

#if (ENABLE_CEC)
static void MApp_CEC_CheckRepeatKey(void)
{
    switch (u8KeyCode)
    {
        case KEY_SELECT:
        case KEY_LEFT:
        case KEY_RIGHT:
        case KEY_0:
        case KEY_1:
        case KEY_2:
        case KEY_3:
        case KEY_4:
        case KEY_5:
        case KEY_6:
        case KEY_7:
        case KEY_8:
        case KEY_9:
        case KEY_REWIND:
        case KEY_FF:
        case KEY_NEXT:
        case KEY_PREVIOUS:
        case KEY_BLUE:
        case KEY_RED:
        case KEY_GREEN:
        case KEY_YELLOW:
            stKeyStatus.RepeatEnable = TRUE;
            break;

        /*
        Only when System Audio Control is enabled.
        */
        case KEY_VOLUME_PLUS:
        case KEY_VOLUME_MINUS:
            stKeyStatus.RepeatEnable = (msAPI_CEC_QuerySystemAudioMode())? TRUE:FALSE;
            break;

        default:
            stKeyStatus.RepeatEnable = FALSE;
            break;
    }
}
#endif

//MHL
#if (ENABLE_MHL == ENABLE)
#define PRESS_RELEASE_TIMEOUT 150 // ms
#endif

void MApp_ProcessUserInput(void)
{
    //MHL
#if (ENABLE_MHL == ENABLE)
    static U32 u32KeydownTime = 0;
    static BOOL bIsPressed = FALSE;
    static U8 u8PrePressedKey = KEY_NULL;
#endif

#if (ENABLE_CEC)
  #if(CEC_VERSION_USING == CEC_NEW_VERSION)
    static BOOLEAN bIsUserCtrlPressed = FALSE;
    static U32 u32UserCtrlPressedTime = 0;
  #endif
#endif
	
    MApp_CheckKeyStatus();

#if(ENABLE_CEC)
  #if(CEC_VERSION_USING == CEC_NEW_VERSION)
    if(bIsUserCtrlPressed== TRUE) //if user pressed, send a UserControlRelease msg
    {
        if (stKeyStatus.RepeatEnable)
        {
            //passed 400ms, it means there's no the other key inputed.
            if(msAPI_Timer_DiffTimeFromNow(u32UserCtrlPressedTime) > CEC_IR_ENABLE_REPEAT_KEY_PRESS_TIME )
            {
                CEC_DEBUG(printf("\n\33[1;29m Sent UserControlRelease 1  -------- \33[0m"));
                CEC_DEBUG(printf("  TIME= %ld   ", msAPI_Timer_DiffTimeFromNow(u32UserCtrlPressedTime)));
                CEC_DEBUG(printf("\33[1;29m SENT!!! \33[0m \n"));
                u32UserCtrlPressedTime = 0;
                bIsUserCtrlPressed = FALSE;

                //Sent UserControlRelease
                msAPI_CEC_PostMsg_UserCtrlReleased(DIRECTMSG, gCECUserControlEnable, enUserCtrlPressedLA);
            }
        }
        else
        {
            if(msAPI_Timer_DiffTimeFromNow(u32UserCtrlPressedTime) > CEC_IR_DISABLE_REPEAT_KEY_RESET_TIME )
            {
                CEC_DEBUG(printf("\n\33[1;29m Sent UserControlRelease 2  -------- \33[0m"));
                CEC_DEBUG(printf("   TIME= %ld  ", msAPI_Timer_DiffTimeFromNow(u32UserCtrlPressedTime)));
                CEC_DEBUG(printf("\33[1;29m SENT!!! \33[0m \n"));
                u32UserCtrlPressedTime = 0;
                bIsUserCtrlPressed = FALSE;

                //Sent UserControlRelease
                msAPI_CEC_PostMsg_UserCtrlReleased(DIRECTMSG, gCECUserControlEnable, enUserCtrlPressedLA);
            }
        }
    }
  #endif
#endif // #if(ENABLE_CEC)
	
	
	if(gU8Timer10ms >= 10) //xzm @ 20171222
	{
		#if EANBLE_V56_IO_KEY //gchen @ 20180202 //remove key scan by io //MP333
		U8 u8KeyPadValue;
		u8KeyPadValue = KEY_SCAN();
		if((u8KeyPadValue == (KEY_VOLUME_PLUS | KEY_LONG_FLAG))
		  	||(u8KeyPadValue == (KEY_VOLUME_PLUS | KEY_LIAN_FLAG))
		  	||(u8KeyPadValue == (KEY_VOLUME_PLUS | KEY_UP_FLAG)))
		  {
			u8KeyCode = KEY_VOLUME_PLUS;
			MApp_UiMenu_TempDetWin_Show();
		  }
		  else if((u8KeyPadValue == (KEY_VOLUME_MINUS| KEY_LONG_FLAG))
		  	||(u8KeyPadValue == (KEY_VOLUME_MINUS | KEY_LIAN_FLAG))
		  	||(u8KeyPadValue == (KEY_VOLUME_MINUS | KEY_UP_FLAG)))
		  {
			if(stGenSetting.g_SoundSetting.Volume != 0){
				u8KeyCode = KEY_VOLUME_MINUS;
			}
		  }
		#endif
		gU8Timer10ms =0;
	}
	
    if ( stKeyStatus.keydown )
    {
        MApp_ParseKey();

    #if (ENABLE_ARABIC_OSD)
        if ( !msAPI_OSD_GetDivxSubtitleMode() )
        {
            switch ( MApp_GetMenuLanguage() )
            {
          #if (ENABLE_ARABIC_TEST_UI)
            case LANGUAGE_SPANISH:
          #endif
            case LANGUAGE_ARABIC:
            case LANGUAGE_PARSI:
            case LANGUAGE_KURDISH:
            case LANGUAGE_HEBREW:
                if ( u8KeyCode == KEY_LEFT )
                {
                    u8KeyCode = KEY_RIGHT;
                }
                else if ( u8KeyCode == KEY_RIGHT )
                {
                    u8KeyCode = KEY_LEFT;
                }
                break;
            default:
                break;
            }
        }
    #endif

#if (IR_TYPE_SEL == IR_TYPE_SAMSUNG_REMOTE)
    MApp_CheckRepeatKey();

#if (IR_MODE_SEL == IR_TYPE_SWDECODE_NEC_MODE)
      if(msIsNECKeyRepeat())
#endif
      {
          if( !stKeyStatus.RepeatEnable && stKeyStatus.keyrepeat)
          {
            u8KeyCode = KEY_NULL;
           }
      }
#endif

      //MHL
  #if (ENABLE_MHL == ENABLE)
    if (((UI_INPUT_SOURCE_HDMI <= UI_INPUT_SOURCE_TYPE) && (UI_INPUT_SOURCE_TYPE < UI_INPUT_SOURCE_HDMI_END))
        && mapi_mhl_SendMSGCmdFlag() \
        && (MApp_TopStateMachine_GetTopState() == STATE_TOP_DIGITALINPUTS)\
        && msAPI_MHL_IsCbusConnected()\
         )
        {
        if(msAPI_CheckMHL_IRKeyValid(u8KeyCode))
        {
            if ((FALSE == stKeyStatus.keyrepeat)&&(u8PrePressedKey != u8KeyCode)&&(DIFFERENCE(u32KeydownTime, msAPI_Timer_GetTime0()) > 350))
        {
                if (msAPI_MHL_IRKeyProcess(u8KeyCode, FALSE))
                {
                  //  printf("[press] IRKey Diff Time = %d\n", DIFFERENCE(u32KeydownTime, msAPI_Timer_GetTime0()));
                    u8PrePressedKey = u8KeyCode;
                    u8KeyCode = KEY_NULL;
                    u32KeydownTime = msAPI_Timer_GetTime0();
                    bIsPressed = TRUE;
                    return;
                }
                else
                {
                    u8PrePressedKey = u8KeyCode;
                    u8KeyCode       = KEY_NULL;
                    u32KeydownTime  = msAPI_Timer_GetTime0();
                    bIsPressed      = FALSE;
                }
        }
        else
            {
                if((TRUE == stKeyStatus.keyrepeat)
                    &&((u8KeyCode==KEY_UP)||(u8KeyCode==KEY_DOWN)||(u8KeyCode==KEY_LEFT)
                            ||(u8KeyCode==KEY_RIGHT)||(u8KeyCode==KEY_REWIND)||(u8KeyCode==KEY_FF))
                )
                {
                    u32KeydownTime  = msAPI_Timer_GetTime0();
                    if (msAPI_MHL_IRKeyProcess(u8KeyCode, FALSE))
                    {
                            u8PrePressedKey = u8KeyCode;
                            u8KeyCode = KEY_NULL;
                            u32KeydownTime = msAPI_Timer_GetTime0();
                            bIsPressed = TRUE;
                    }
                    else
                     {
                            u8PrePressedKey = u8KeyCode;
                            u8KeyCode       = KEY_NULL;
                            u32KeydownTime  = msAPI_Timer_GetTime0();
                            bIsPressed      = FALSE;
                     }
                }
                u8KeyCode       = KEY_NULL;
                }
            }
    else
        {
            bIsPressed = FALSE;
            u8PrePressedKey = KEY_NULL;
        }
        }
  #endif

#if (ENABLE_CEC)

    if (  (DB_HDMI_SETTING.g_bHdmiCecMode == ENABLE)  // CEC function Enable
       && (msAPI_CEC_GetDeviceTotalNum() > 0)                   // at least one connected CEC device
       )
    {
        if (  ( (IsHDMIInUse() && MApp_IsSrcHasSignal(MAIN_WINDOW))   // HDMI source and has singal
              &&(DB_HDMI_SETTING.g_bHdmiCecDeviceControl == ENABLE) ) // Device control turn on
#if(CEC_VERSION_USING == CEC_NEW_VERSION)
           || ( (msAPI_CEC_IsAudioSystemKeyValid())
#else
           || ( (stGenSetting.g_SoundSetting.TVspeakerMode == TVspeaker_Mode_ExtAmp)
#endif
              &&((u8KeyCode == KEY_VOLUME_PLUS) || (u8KeyCode == KEY_VOLUME_MINUS) || (u8KeyCode == KEY_MUTE)) ) //[4] Tv speaker is CEC and key is volume key
           )
        {
            MApp_CEC_CheckRepeatKey();

        #if(CEC_VERSION_USING == CEC_NEW_VERSION)
            if(stKeyStatus.keyrepeat == FALSE)
            {
                CEC_DEBUG(printf("\n\33[1;31m First key or Change Key \33[0m"));

                if(msAPI_Timer_DiffTimeFromNow(u32UserCtrlPressedTime) > CEC_IR_USER_CONTROL_PRESSED_TIME)
                {
                    if (msAPI_CEC_SendCECKeyFromTVtoDev(u8KeyCode))
                    {
                        u32UserCtrlPressedTime = msAPI_Timer_GetTime0();
                        bIsUserCtrlPressed = TRUE;

                        stKeyStatus.keydown = FALSE;
                        return;
                    }
                }
            }
            else if(stKeyStatus.keyrepeat && stKeyStatus.RepeatEnable)
            {
                CEC_DEBUG(printf("\n\33[1;32m Sent UserControlPress  -------- \33[0m"));
                CEC_DEBUG(printf("%ld  ", msAPI_Timer_DiffTimeFromNow(u32UserCtrlPressedTime)));
                 // sent UserControlPress msg durning 200~500ms, otherwise do nothing.
                 if(msAPI_Timer_DiffTimeFromNow(u32UserCtrlPressedTime) > CEC_IR_USER_CONTROL_PRESSED_TIME) //check if the time between 200 to 500 ms
                 {
                    if (msAPI_CEC_SendCECKeyFromTVtoDev(u8KeyCode))
                    {
                        CEC_DEBUG(printf("\33[1;32m SENT!!!  = %d \33[0m \n", bIsUserCtrlPressed));
                        u32UserCtrlPressedTime = msAPI_Timer_GetTime0();
                        bIsUserCtrlPressed = TRUE;

                        stKeyStatus.keydown = FALSE;
                        return;
                    }
                }
            }
        #else
            if (  (!stKeyStatus.keyrepeat)//new key
               || (stKeyStatus.keyrepeat && stKeyStatus.RepeatEnable)//repeat admitted key
               )
            {
                if ( msAPI_CEC_SendCECKeyFromTVtoDev(u8KeyCode) )
                {
                    stKeyStatus.keydown = FALSE;
                    return;
                }
            }
        #endif
        }
    }
  #endif // #if(ENABLE_CEC)


    #if (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)
      #if (MSTAR_VIF_MSB1210_DEBUG_MODE==1)
        if (MApp_ProcessUserInput_MSVIF_Debug(u8KeyCode)==1)
            return;
      #endif
    #endif

    #if System_Script_Testing
        if ( u8KeyCode == KEY_GREEN )
        {
            if(u8KeyScriptOn)
                u8KeyScriptOn=0;
            else
                u8KeyScriptOn=1;
        }
    #endif

    #if MHEG5_ENABLE
        if ( u8KeyCode == KEY_POWER )
            MApp_ChannelPosition_Restore();
    #endif

    #if 1//MCU_AEON_ENABLE
        // TODO, For debug only, remove it later!
        if ( u8KeyCode == KEY_UARTDEBUGPORT )
        {
            //ZUI_TODO: MApp_UiMenu_Show_Warning_Message_Dialog(MENU_CEC_DEVICE_ISR_MSG);
          #if 0
            switch(XBYTE[0x1EAA] & 0x1C)
            {
                case 0x00:
                    XBYTE[0x1EAA] &= ~0x1C;
                    XBYTE[0x1EAA] |= 0x0C; //aeon1
                    break;

                case 0x0C:
                    XBYTE[0x1EAA] &= ~0x1C;
                    XBYTE[0x1EAA] |= 0x14; //aeon2
                    break;

                default:
                case 0x14:
                    XBYTE[0x1EAA] &= ~0x1C; //hk51
                    printf("==>Uart for HK51\n");
                    break;
            }
          #endif
            u8KeyCode = KEY_NULL;
        }
      #if (MHEG5_ENABLE && DEBUG_SYS_INFO_REPORT)
        // Query System Inormation
        else if(u8KeyCode == KEY_INFO)
            msAPI_System_StatusReport();
      #endif
    #endif

        MApp_Sleep_SetAutoOn_OffTime(DISABLE);

        // Enter Serial Debug Mode through IR Command 8033
        switch ( u8HwDebugFlag )
        {
            case 1:
                if ( u8KeyCode == KEY_0 )
                {
                    u8HwDebugFlag++;
                }
                else
                {
                    u8HwDebugFlag=0;
                }
                break;

            case 2:
                if (u8KeyCode == KEY_3)
                {
                    u8HwDebugFlag++;
                }
                else
                {
                    u8HwDebugFlag=0;
                }
                break;

            case 3:
                if (u8KeyCode == KEY_4)
                {
                #if 0//Delet this function, It's danger when user kit this one day!
                    MApp_DataBase_RestoreFactoryDefault(RESTORE_GENSETTING|RESTORE_DATABASE);

                    MDrv_Sys_WholeChipReset();
                #endif
                }
              #if (ENABLE_DMP)
                else if (u8KeyCode == KEY_9)
                {
                    MApp_VDPlayer_UartSwitch(E_UART_SWITCH_TO_HK);
                    u8HwDebugFlag=0;
                }
                else if (u8KeyCode == KEY_0)
                {
                    MApp_VDPlayer_UartSwitch(E_UART_SWITCH_TO_COPROCESSOR);
                    u8HwDebugFlag=0;
                }
              #endif
                else
                {
                    u8HwDebugFlag=0;
                }
                break;

            case 0:
                if (u8KeyCode == KEY_8)
                {
                    u8HwDebugFlag++;
                }
                else
                {
                    u8HwDebugFlag=0;
                }
                break;

            default :
                u8HwDebugFlag=0;
                break;
        }

        // End Enter Serial Debug Mode through IR Command 8033

        if ( stKeyStatus.keyrepeat )
        {
            switch ( u8KeyRepeatState )
            {
            case OSD_REPEAT_DISABLE:
                u8KeyCode = KEY_NULL;
                break;

            case OSD_REPEAT_H_ENABLE:
                if (u8KeyCode == KEY_UP || u8KeyCode == KEY_DOWN)
                {
                     u8KeyCode = KEY_NULL;
                }
                break;

            case OSD_REPEAT_V_ENABLE:
                if ( u8KeyCode == KEY_LEFT || u8KeyCode == KEY_RIGHT)
                {
                     u8KeyCode = KEY_NULL;
                }
                break;
            }

        }

      #if (NO_SIGNAL_AUTO_SHUTDOWN )
        MApp_NoSignalAutoSleep_Reset_StartTime();
      #endif

        u32MonitorOsdTimer = msAPI_Timer_GetTime0();

        if (stKeyStatus.KeyFilterPower)
        {
            stKeyStatus.KeyFilterPower = FALSE;

            if ((u32MonitorOsdTimer < 8000) && ((u8KeyCode == KEY_POWER) || (u8KeyCode == DSC_KEY_PWROFF)))
            {
                u8KeyCode = KEY_NULL;
            }
        }
    }

  #if 0//(ENABLE_CEC) //don't know what this is??
    else if ( (gCECProcessCMDbyKey == TRUE)
            &&(gCECProcessCMDKeycode != 0xFF) )
    {
        U8 u8KeyDataTemp = 0xff;

        //fixed for CEC 11.1.3 System Standby
        u8KeyDataTemp = stKeyStatus.keydata;
        stKeyStatus.keydata = gCECProcessCMDKeycode;
        MApp_ParseKey();
        stKeyStatus.keydata = u8KeyDataTemp;

        if ( (UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_HDMI)
         #if (INPUT_HDMI_VIDEO_COUNT >= 2)
          || (UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_HDMI2)
          #if (INPUT_HDMI_VIDEO_COUNT >= 3)
          || (UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_HDMI3)
          #endif
         #endif
           )
        {
            if (msAPI_CEC_SendCECKeyFromTVtoDev(u8KeyCode))
            {
                return;
            }
        }

      #if 1//power off DVD in other source
        if(gCECProcessCMDKeycode == KEY_POWER)
        {
            msAPI_CEC_SendCECKeyFromTVtoDev(gCECProcessCMDKeycode);
        }
      #endif
    }
  #endif

  #if (ENABLE_MHL == ENABLE)
      else if (((UI_INPUT_SOURCE_HDMI <= UI_INPUT_SOURCE_TYPE) && (UI_INPUT_SOURCE_TYPE < UI_INPUT_SOURCE_HDMI_END))
            && mapi_mhl_SendMSGCmdFlag()&&msAPI_MHL_IsCbusConnected())
      {
          if ((bIsPressed == TRUE)&&(DIFFERENCE(u32KeydownTime, msAPI_Timer_GetTime0()) > PRESS_RELEASE_TIMEOUT))
          {
              //printf("[Release]DIFFERENCE=%d, PRESS_RELEASE_TIMEOUT=%d\n", DIFFERENCE(u32KeydownTime, msAPI_Timer_GetTime0()), PRESS_RELEASE_TIMEOUT);
              if (msAPI_MHL_IRKeyProcess(u8PrePressedKey, TRUE))
              {
                  //printf("[1]0x%x Key Released\r\n", u8PrePressedKey);
                  u8PrePressedKey = KEY_NULL;
                  u8KeyCode = KEY_NULL;
                  bIsPressed = FALSE;
                  return;
              }
              else
              {
                  //printf("[Release]MHL IR key False\r\n");
                  u8PrePressedKey = KEY_NULL;
                  u8KeyCode = KEY_NULL;
                  bIsPressed = FALSE;
              }
          }
      }
  #endif

  #if System_Script_Testing
    if(u8KeyScriptOn)
    {
        if (u16ScriptIndex < sizeof(u8ScriptKeys) / sizeof(u8ScriptKeys[0]))
        {
            if (u8ScriptKeys[u16ScriptIndex] & 0x80)
            {
                if (msAPI_Timer_DiffTime( msAPI_Timer_GetTime0(), u32WaitTime ) >
                    (u8ScriptKeys[u16ScriptIndex] & 0x7F) * 1000LU)
                {
                    u16ScriptIndex++;
                }
                u8KeyCode = KEY_NULL;
            }
            else
            {
                if (msAPI_Timer_DiffTime( msAPI_Timer_GetTime0(), u32WaitTime ) > 200LU)
                {
                    u32WaitTime = u32MonitorOsdTimer = msAPI_Timer_GetTime0();
                    u8KeyCode = u8ScriptKeys[u16ScriptIndex++];
                }

                else
                {
                    u8KeyCode = KEY_NULL;
                }
            }
        }
        else
        {
            u16ScriptIndex=0;
        }
    }
  #endif

    /* simple key leaner */
    #define STUDY_BEGIN_KEY        KEY_NULL//KEY_INDEX
    #define STUDY_SEND_KEY        KEY_HOLD

    if (STUDY_BEGIN_KEY != KEY_NULL && STUDY_SEND_KEY != KEY_NULL)
    {
        #define SK_STATE_NONE  0
        #define SK_STATE_LEARN 1
        #define SK_STATE_SEND  2
        #define SK_STATE_DELAY 3

        static U32 WaitTime;
        static U8 Keys[16];
        static U8 NumberOfKeys = 0;
        static U8 CurrentKeyIndex = 0;
        static U8 state = SK_STATE_NONE;
        static U8 u8LastKey = KEY_NULL;

        switch (state)
        {
        default:
        case SK_STATE_NONE:
            if (u8KeyCode == STUDY_BEGIN_KEY)    // begin of study
            {
                NumberOfKeys = 0;
                state = SK_STATE_LEARN;
                u8KeyCode = KEY_NULL;
//                printf("+\n");
            }
            else if (u8KeyCode == STUDY_SEND_KEY)// start to send keys
            {
                if (NumberOfKeys)
                {
                    CurrentKeyIndex = 0;
                    state = SK_STATE_SEND;
                    u8KeyCode = KEY_NULL;
//                    printf(">\n");
                }
            }
            break;

        case SK_STATE_LEARN:
            if (u8KeyCode == KEY_NULL)
                break;
            if (u8LastKey == STUDY_SEND_KEY)        // escape key
            {
                u8LastKey = KEY_NULL;

                // delay time
                if (u8KeyCode >= KEY_0 && u8KeyCode <= KEY_9)
                    u8KeyCode = 0x81 - KEY_0 + u8KeyCode;
            }
            else if (u8KeyCode == STUDY_SEND_KEY)    // escape
            {
                u8LastKey = u8KeyCode;
                u8KeyCode = KEY_NULL;
                break;
            }
            else if (u8KeyCode == STUDY_BEGIN_KEY)    // end of study
            {
                state = SK_STATE_NONE;
                u8KeyCode = KEY_NULL;
//                printf("-%d\n", (int)NumberOfKeys);
                break;
            }
            if (NumberOfKeys >= (sizeof(Keys) / sizeof(Keys[0])))
                break;
            Keys[NumberOfKeys++] = u8KeyCode;
//            printf("%x\n", (int)u8KeyCode);

            if (u8KeyCode >= 0x80)
                u8KeyCode = KEY_NULL;
            break;

        case SK_STATE_SEND:
        case SK_STATE_DELAY:
            if (u8KeyCode == STUDY_SEND_KEY)        // stop send
            {
                state = SK_STATE_NONE;
                u8KeyCode = KEY_NULL;
//                printf("<\n");
            }
            else
            {
                u32MonitorOsdTimer = msAPI_Timer_GetTime0();
                if (CurrentKeyIndex >= NumberOfKeys)
                    CurrentKeyIndex = 0;
                u8KeyCode = Keys[CurrentKeyIndex];
                if (u8KeyCode >= 0x80 /* && u8KeyCode <= 0x80 + 10 */)    // commented out for bank overflow
                {
                    if (state == SK_STATE_SEND)
                    {
                        state = SK_STATE_DELAY;
                        WaitTime = msAPI_Timer_GetSystemTime();
                    }
                    else if ((msAPI_Timer_GetSystemTime() - WaitTime) >= (U32)(u8KeyCode & 0x7F))
                    {
                        state = SK_STATE_SEND;
                        CurrentKeyIndex++;
                    }
                    u8KeyCode = KEY_NULL;
                    break;
                }
                CurrentKeyIndex++;
            }
            break;
        }
    }
}

/******************************************************************************/
void MApp_Key_Initial_Status(void)
{
    stKeyStatus.KeyFilterPower = TRUE;
    msAPI_ClearIRFIFO();
}

/******************************************************************************/
BOOLEAN MApp_GetCurrentKeyType(void)
{
    return stKeyStatus.keytype;
}

BOOLEAN MApp_KeyIsReapeatStatus(void)
{
    //printf("stKeyStatus.keyrepeat %bu\n", stKeyStatus.keyrepeat);
    if (stKeyStatus.keyrepeat == TRUE )
    {
        return TRUE;
    }

    return FALSE;
}

#if(ENABLE_MBIR)
void MApp_GetMBIR(ST_MBIR* pMBIR)
{
    memcpy(pMBIR,&mbir,sizeof(ST_MBIR));
}

void MApp_FillMBIR(U8 keycode, U8 repeat)
{
    mbir.empty=FALSE;
    mbir.keydata=keycode;
    mbir.repeat=repeat;
}

void MApp_ClearMBIR(void)
{
    mbir.empty=TRUE;
    mbir.keydata=0xFFFF;
    mbir.repeat=FALSE;
}

void MApp_SetMBIRFlag(U8 val)
{
    mbir.flag=val;
}

U8 MApp_GetMBIRFlag(void)
{
    return mbir.flag;
}
#endif

#if (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)
#if (MSTAR_VIF_MSB1210_DEBUG_MODE==1)

U8 MApp_ProcessUserInput_MSVIF_Debug(U8 keycode)
{
#if 0 //Debug
    printf("--Key = 0x%bx (gGemini_KeyState = 0x%bx)\n",keycode,gGemini_KeyState);
    printf("--gGemini_FactoryMode_Enable = 0x%bx (gGemini_KeyValue = 0x%bx)\n"
        ,gGemini_FactoryMode_Enable,gGemini_KeyValue);
#endif

    switch (keycode)
    {
        case KEY_1:
                if (gGemini_KeyState == GEMINI_KEY_WAIT_1)
                    gGemini_KeyState = GEMINI_KEY_WAIT_2;
                else
                {
                    gGemini_KeyState = GEMINI_KEY_NONE;
                }
        break;
        case KEY_2:
                if (gGemini_KeyState == GEMINI_KEY_WAIT_2)
                    gGemini_KeyState = GEMINI_KEY_WAIT_3;
                else
                {
                    gGemini_KeyState = GEMINI_KEY_NONE;
                }
        break;
        case KEY_3:
                if (gGemini_KeyState == GEMINI_KEY_WAIT_3)
                {
                    gGemini_KeyState = GEMINI_KEY_NONE;
                    gGemini_FactoryMode_Enable=1;
                    gGemini_GetKey = GEMINI_GET_KEY_1;
                    gGemini_KeyValue=0XFF;
                    printf("---> MSVIF Debug Enable...\n");
                }
                else
                {
                    gGemini_KeyState = GEMINI_KEY_NONE;
                }
        break;

        case KEY_RED:
                if (gGemini_FactoryMode_Enable ==1)
                {
                    gGemini_KeyState = GEMINI_KEY_NONE;
                    gGemini_FactoryMode_Enable = 0;
                    printf("---> MSVIF Debug Disable...\n");
                    break;
                }else
                {
                    if (gGemini_KeyState == GEMINI_KEY_NONE)
                        gGemini_KeyState = GEMINI_KEY_WAIT_1;
                    else
                    {
                        gGemini_KeyState = GEMINI_KEY_NONE;
                    }
                }
        break;

        default:

        break;
    }

    if (gGemini_FactoryMode_Enable == 1)
    {
        //To support Gemini Key Factory Mode from 1 to 15
           if ((keycode >= KEY_0) &&(keycode <= KEY_9) )
           {
            if (gGemini_GetKey == GEMINI_GET_KEY_1)
               {
                gGemini_KeyValue = keycode & 0x0F;
                gGemini_GetKey = GEMINI_GET_KEY_2;
            }
            else
            {
                gGemini_KeyValue = (gGemini_KeyValue *10) + (keycode & 0x0F);
                gGemini_GetKey = GEMINI_GET_KEY_1;
            }
       }
         if (keycode == KEY_SELECT)
         {
            printf("---> MSVIF Get Key = (0x%bx)\n",gGemini_KeyValue);
            if (gGemini_KeyValue <= 15)
            {
                gVifTop = gGemini_KeyValue;
                printf("---> MSVIF Call msVifTopAdjust(0x%bx)\n",gGemini_KeyValue);
                msVifTopAdjust(gVifTop);

            }
            gGemini_GetKey = GEMINI_GET_KEY_1;
            gGemini_KeyValue = 0XFF;
         }
    }

    if ((gGemini_FactoryMode_Enable == 1)||(gGemini_KeyState != GEMINI_KEY_NONE))
    {
         if (((keycode >= KEY_0) &&(keycode <= KEY_9) )
             ||(keycode == IRKEY_RED)||(keycode == KEY_SELECT))
            return (1);
    }
    return (0);

}
#endif
#endif
#undef MAPP_IR_C

