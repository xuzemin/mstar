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

#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include "msAPI_VD.h"
#include "msAPI_Timer.h"

#include "MApp_ZUI_EventNotify.h"
#include "MApp_Func_Mainpage.h"

#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalVar.h"
#include "mapp_mplayer.h"
#include "MApp_DMP_Main.h"
#include "MApp_USBDownload.h"
#include "MApp_ChannelChange.h"
#include "MApp_GlobalFunction.h"
#include "MApp_InputSource.h"
#include "MApp_SaveData.h"
#include "MApp_Scan.h"
#include "MApp_MenuFunc.h"
#include "MApp_Scaler.h"

#if (ENABLE_ATSC)
#include "MApp_ChannelProc_ATSC.h"
#include "MApp_DataBase_ATSC.h"
#endif

#if (ENABLE_PIP)
#include "MApp_PIP.h"
#endif

extern EN_OSD_TUNE_TYPE_SETTING eTuneType;
extern BOOLEAN MApp_UiMainpage_Notify(MAINPAGE_NOTIFY_TYPE enMainpageNotify, U16 para1, U16 para2);
extern U16 _MApp_ZUI_ACT_PasswordConvertToSystemFormat(U16 password);

U8 MApp_Function_Mainpage_Usbupdate(pMainpageFuncCB pFuncCB)
{
#if ( ENABLE_SW_UPGRADE && ENABLE_FILESYSTEM )

    U8 u8PortEnStatus = 0;
#if ENABLE_DMP
    // for dmp
    if( UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_DMP)
    {
        if((MApp_MPlayer_IsMediaFileInPlaying()
            #if(ENABLE_MPLAYER_TEXT)
            ||MApp_MPlayer_QueryCurrentMediaType()==E_MPLAYER_TYPE_TEXT
            #endif
            )
            &&(MApp_DMP_GetDmpFlag()& DMP_FLAG_MEDIA_FILE_PLAYING))
        {
            MApp_MPlayer_Stop();
#if(ENABLE_MPLAYER_MOVIE)
            switch(MApp_MPlayer_QueryCurrentMediaType())
            {
                case E_MPLAYER_TYPE_MOVIE:
                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_STOP);
                    break;
                default:
                    break;
            }
#endif
        }
    }
#endif // #if ENABLE_DMP

    MApp_UiMainpage_Notify(EN_MAINPAGE_NOTIFY_STORE_FOCUS, 0, 0);

    u8PortEnStatus = MDrv_USBGetPortEnableStatus();
    if((u8PortEnStatus & BIT0) == BIT0)
    {
        if (!MDrv_UsbDeviceConnect())
        {
            MsOS_DelayTask(1000);
        }

        if (!MDrv_UsbDeviceConnect())
        {
            if((u8PortEnStatus & BIT1) != BIT1)
            {
                MApp_UiMainpage_Notify(EN_MAINPAGE_NOTIFY_COMMON_DLG, EN_NOTIFY_DLG_MODE_USB_NOT_DETECTED, 6000);
                return FALSE;
            }
        }
        else
        {
            MApp_UsbDownload_Init(BIT0, pFuncCB);

            if (MW_UsbDownload_Search())
            {
                MApp_UiMainpage_Notify(EN_MAINPAGE_NOTIFY_STORE_FOCUS, 0, 0);
                MApp_UiMainpage_Notify(EN_MAINPAGE_NOTIFY_COMMON_DLG, EN_NOTIFY_DLG_MODE_USB_UPDATE_CONFIRM, 0);
                return TRUE;
            }
            else //no sw file detected
            {
                MApp_UsbDownload_Exit();

                if((u8PortEnStatus & BIT1) != BIT1)
                {
                    MApp_UiMainpage_Notify(EN_MAINPAGE_NOTIFY_COMMON_DLG, EN_NOTIFY_DLG_MODE_SW_FILE_NOT_DETECTED, 6000);
                    return FALSE;
                }
            }
        }
    }

    if((u8PortEnStatus & BIT1) == BIT1)
    {
        if (!MDrv_UsbDeviceConnect_Port2())
        {
            MsOS_DelayTask(1000);
        }

        if (!MDrv_UsbDeviceConnect_Port2())
        {
            if((u8PortEnStatus & BIT2) != BIT2)
            {
                MApp_UiMainpage_Notify(EN_MAINPAGE_NOTIFY_COMMON_DLG, EN_NOTIFY_DLG_MODE_USB_NOT_DETECTED, 6000);
                return FALSE;
            }
        }
        else
        {
            MApp_UsbDownload_Init(BIT1, pFuncCB);

            if (MW_UsbDownload_Search())
            {
                MApp_UiMainpage_Notify(EN_MAINPAGE_NOTIFY_STORE_FOCUS, 0, 0);
                MApp_UiMainpage_Notify(EN_MAINPAGE_NOTIFY_COMMON_DLG, EN_NOTIFY_DLG_MODE_USB_UPDATE_CONFIRM, 0);
                return TRUE;
            }
            else //no sw file detected
            {
                MApp_UsbDownload_Exit();
                if((u8PortEnStatus & BIT2) != BIT2)
                {
                    MApp_UiMainpage_Notify(EN_MAINPAGE_NOTIFY_COMMON_DLG, EN_NOTIFY_DLG_MODE_SW_FILE_NOT_DETECTED, 6000);
                    return FALSE;
                }

            }
        }
    }

#if (ENABLE_USB_3)
    if((u8PortEnStatus & BIT2) == BIT2)
    {
        if (!MDrv_UsbDeviceConnect_Port3())
        {
            MsOS_DelayTask(1000);
        }

        if (!MDrv_UsbDeviceConnect_Port3())
        {
            if((u8PortEnStatus & BIT3) != BIT3)
            {
                MApp_UiMainpage_Notify(EN_MAINPAGE_NOTIFY_COMMON_DLG, EN_NOTIFY_DLG_MODE_USB_NOT_DETECTED, 6000);
                return FALSE;
            }
        }
        else
        {
            MApp_UsbDownload_Init(BIT2, pFuncCB);

            if (MW_UsbDownload_Search())
            {
                MApp_UiMainpage_Notify(EN_MAINPAGE_NOTIFY_STORE_FOCUS, 0, 0);
                MApp_UiMainpage_Notify(EN_MAINPAGE_NOTIFY_COMMON_DLG, EN_NOTIFY_DLG_MODE_USB_UPDATE_CONFIRM, 0);
                return TRUE;
            }
            else //no sw file detected
            {
                MApp_UsbDownload_Exit();
                if((u8PortEnStatus & BIT3) != BIT3)
                {
                    MApp_UiMainpage_Notify(EN_MAINPAGE_NOTIFY_COMMON_DLG, EN_NOTIFY_DLG_MODE_SW_FILE_NOT_DETECTED, 6000);
                    return FALSE;
                }
            }
        }
    }
#endif

#if (ENABLE_USB_4)
    if((u8PortEnStatus & BIT3) == BIT3)
    {
        PRINT_CURRENT_LINE();
        if (!MDrv_UsbDeviceConnect_Port4())
        {
            MsOS_DelayTask(1000);
        }

        if (!MDrv_UsbDeviceConnect_Port4())
        {
            MApp_UiMainpage_Notify(EN_MAINPAGE_NOTIFY_COMMON_DLG, EN_NOTIFY_DLG_MODE_USB_NOT_DETECTED, 6000);
            return FALSE;
        }
        else
        {
            MApp_UsbDownload_Init(BIT3, pFuncCB);

            if (MW_UsbDownload_Search())
            {
                MApp_UiMainpage_Notify(EN_MAINPAGE_NOTIFY_STORE_FOCUS, 0, 0);
                MApp_UiMainpage_Notify(EN_MAINPAGE_NOTIFY_COMMON_DLG, EN_NOTIFY_DLG_MODE_USB_UPDATE_CONFIRM, 0);
                return TRUE;
            }
            else //no sw file detected
            {
                MApp_UsbDownload_Exit();
                MApp_UiMainpage_Notify(EN_MAINPAGE_NOTIFY_COMMON_DLG, EN_NOTIFY_DLG_MODE_SW_FILE_NOT_DETECTED, 6000);
                return FALSE;
            }
        }
    }
#endif

    return FALSE;
#endif // #if ( ENABLE_SW_UPGRADE && ENABLE_FILESYSTEM )
}


FUNC_MAINPAGE_STATUS MApp_FuncExec_Mainpage(FUNC_MAINPAGE_TYPE func, void *para1, pMainpageFuncCB pFuncCB)
{
    FUNC_MAINPAGE_STATUS enResult = EN_FUNC_MAINPAGE_STATUS_FALSE;
    para1 = para1;

    switch(func)
    {
        case EN_FUNC_MAINPAGE_USB_UPDATE:
            MApp_Function_Mainpage_Usbupdate(pFuncCB);
            enResult = EN_FUNC_MAINPAGE_STATUS_TRUE;
            break;

        case EN_FUNC_MAINPAGE_SET_AUTO_TUNING:
            {
                //from case MIA_START_SCAN

            #if(ENABLE_SBTVD_DTV_SYSTEM)
                if(IS_SBTVD_APP)
                {
                    MApp_SetOSDCountrySetting(OSD_COUNTRY_BRAZIL, TRUE);
                    u8ScanCATVChNum = 0;
                    u8ScanAirTVChNum = 0;
                }
                else
            #endif
                {
                    MApp_SetOSDCountrySetting((EN_OSD_COUNTRY_SETTING)MApp_UiMainpage_Notify(EN_MAINPAGE_NOTIFY_GET_TUNNING_COUNTRY, 0, 0), TRUE);
                }

                u8ScanAtvChNum = 0;
                u16ScanDtvChNum = 0;
                u16ScanRadioChNum = 0;
            #if NORDIG_FUNC //for Nordig Spec v2.0
                u16ScanDataChNum = 0;
            #endif
                u8ScanPercentageNum = 0;

            #if (ENABLE_PIP)
                if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
                {
                    MApp_ClosePIPSubWindowSource();
                }
            #endif

                printf("eTuneType=%u\n", eTuneType);

        #if(ENABLE_DVB)
                if(
                #if (ENABLE_SBTVD_DTV_SYSTEM)
                    (/*IsISDBTInUse() &&*/ eTuneType == OSD_TUNE_TYPE_DTV_PLUS_ATV)||
                #endif
                    ( eTuneType == OSD_TUNE_TYPE_DTV_ONLY)
                  )
                {
                    MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);

            #if 1
                    // If current is not DTV, change to Dtv source
                    if( FALSE == MApp_InputSrc_Is_CurUiInputSrcTypeDtv() )
                    {
                        // Goto which Dtv? Depend on Customer~~
                        // Goto last Dtv source
                        //MApp_InputSrc_Set_UiInputSrcType(MApp_InputSrc_Get_LastDtvUiSrcType());

                        // Goto default Dtv source
                        MApp_InputSrc_Set_UiInputSrcType(SYS_DEFAULT_DTV_UI_INPUTSOURCE);
                    }

            #else

                #if ENABLE_DVBC
                    #if ENABLE_T_C_COMBO
                        if(!IsDVBCInUse())
                            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DTV;
                        else
                            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_CADTV;
                    #else
                        UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_CADTV;
                    #endif
                #else
                        UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DTV;
                #endif
            #endif

                #if (ENABLE_SBTVD_DTV_SYSTEM)    // fixed mantis 1136151
                    if(IS_SBTVD_APP)
                        MApp_InputSource_SwitchSource( UI_INPUT_SOURCE_ISDBT, MAIN_WINDOW );
                    else
                #endif
                    MApp_InputSource_ChangeInputSource(MAIN_WINDOW );


                }
                else
        #endif
                {
                    mvideo_vd_set_videosystem(SIG_PAL); //dealut value for DVB
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_INTERNAL_2_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                    MApp_Scaler_Setting_SetVDScale(EN_AspectRatio_16X9, MAIN_WINDOW);
                }

                printf("g_enScanType=%u\n", g_enScanType);

            //#if ENABLE_T_C_COMBO
              #if ENABLE_DVBC
                if( IsDVBCInUse() )
                {
                    if(g_enScanType == SCAN_TYPE_NETWORK)
                        stGenSetting.stScanMenuSetting.u8ScanType = SCAN_TYPE_NETWORK;
                    else //if(g_enScanType == SCAN_TYPE_AUTO)
                    {
                        g_enScanType = SCAN_TYPE_AUTO;
                        stGenSetting.stScanMenuSetting.u8ScanType = SCAN_TYPE_AUTO;
                    }
                }
                else
              #endif
                {
                    stGenSetting.stScanMenuSetting.u8ScanType = SCAN_TYPE_AUTO;
                }
            //#else
           //     {
          //          stGenSetting.stScanMenuSetting.u8ScanType = SCAN_TYPE_AUTO;
           //     }
           // #endif
            }
            break;

        case EN_FUNC_MAINPAGE_SET_DTV_TUNING:

    #if(ENABLE_DVB)
            //PRINT_CURRENT_LINE();

            // If current is not DTV, change to Dtv source
            if( MApp_InputSrc_Is_CurUiInputSrcTypeDtv() )
            {
                MApp_ChannelChange_DisableChannel(TRUE, MAIN_WINDOW);
            }
            else
            {
                // Goto which Dtv? Depend on Customer~~
                // Goto last Dtv source
                //MApp_InputSrc_Set_UiInputSrcType(MApp_InputSrc_Get_LastDtvUiSrcType());

                // Goto default Dtv source
                MApp_InputSrc_Set_UiInputSrcType(SYS_DEFAULT_DTV_UI_INPUTSOURCE);
            }

            MApp_InputSource_ChangeInputSource(MAIN_WINDOW );

            // Set can type
            stGenSetting.stScanMenuSetting.u8ScanType = SCAN_TYPE_MANUAL;

            // Reset UI vairable
            u16ScanDtvChNum = 0;
            u16ScanRadioChNum = 0;
        #if NORDIG_FUNC //for Nordig Spec v2.0
            u16ScanDataChNum = 0;
        #endif



        #if 0//(DVB_T_C_DIFF_DB)
            if(IsDVBCInUse())
            {
                MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);
                stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType=EN_DVB_T_TYPE;
                MApp_SaveScanMenuSetting();
                msAPI_Tuner_SwitchSource((EN_DVB_TYPE)stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType, TRUE);
                //stGenSetting.stScanMenuSetting.u8RFChannelNumber=stGenSetting.stScanMenuSetting.u8PreRFChannelNumber=INVALID_IDINDEX;
            //#if (!ENABLE_T_C_COMBO)
                msAPI_CM_ResetAllProgram();
            //#endif
            }
        #endif
        //#if ENABLE_T_C_COMBO
            //printf("setCurrenType : DVBT\n");
            //MApp_DVBType_SetCurrentType(EN_DVB_T_TYPE);
        //#endif
    #endif
            break;

        case EN_FUNC_MAINPAGE_CHECK_BLOCK_PASSWORD:
            {
                U16 u16Password = *((U16*)para1);

                if( MApp_MenuFunc_Setup_BlockSysLockMode_Get() == 1 &&
                    _MApp_ZUI_ACT_PasswordConvertToSystemFormat( u16Password ) != MApp_MenuFunc_Setup_BlockSysPassWord_Get() )
                {
                    enResult = EN_FUNC_MAINPAGE_STATUS_TRUE;
                }
                else
                {
                    enResult = EN_FUNC_MAINPAGE_STATUS_FALSE;
                }
            }
            break;

        case EN_FUNC_MAINPAGE_GET_SYS_BLOCK_MODE:
            if (MApp_MenuFunc_Setup_BlockSysLockMode_Get() == TRUE)
                enResult = EN_FUNC_MAINPAGE_STATUS_TRUE;
            else
                enResult = EN_FUNC_MAINPAGE_STATUS_FALSE;
            break;

    #if ENABLE_DVBC
        case EN_FUNC_MAINPAGE_SET_CADTV_TUNING:
        #if (DVB_T_C_DIFF_DB)
            if(!IsDVBCInUse())
            {
                MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);
                stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType=EN_DVB_C_TYPE;
                MApp_SaveScanMenuSetting();
                msAPI_Tuner_SwitchSource((EN_DVB_TYPE)stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType, TRUE);
            //#if (!ENABLE_T_C_COMBO)
                msAPI_CM_ResetAllProgram();
            //#endif
            }
        #endif
        //#if ENABLE_T_C_COMBO
            //printf("setCurrenType : DVBC\n");
            MApp_DVBType_SetCurrentType(EN_DVB_C_TYPE);
        //#endif
            break;
    #endif //ENABLE_DVBC

#if (ENABLE_ATSC)
    #if ENABLE_ATSC_MAIN_MENU_CHANNEL_PAGE
        case EN_FUNC_MAINPAFE_SET_FAV_CH_ATSC:
            {
                U16 u16Temp = MApp_ChanProc_GetCurProgIndex();
                SET_FAV_CH_ATSC(u16Temp, !IS_FAV_CH_ATSC(u16Temp));
                MApp_DB_ATSC_SaveCurChSetting();
                if(IS_FAV_CH_ATSC(u16Temp))
                {
                    SET_HIDE_CH_ATSC(u16Temp, FALSE);
                    enResult = EN_FUNC_MAINPAGE_STATUS_TRUE;
                }
                else
                {
                    enResult = EN_FUNC_MAINPAGE_STATUS_FALSE;
                }
            }
            break;

        case EN_FUNC_MAINPAGE_SET_HIDE_CH_ATSC:
            {
                U16 u16Temp = MApp_ChanProc_GetCurProgIndex();
                SET_HIDE_CH_ATSC(u16Temp, !IS_HIDE_CH_ATSC(u16Temp));
                if(IS_HIDE_CH_ATSC(u16Temp))
                {
                    SET_FAV_CH_ATSC(u16Temp, FALSE);
                    stChSetting.u16TotalHideSrvNum++;
                    MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);
                    enResult = EN_FUNC_MAINPAGE_STATUS_TRUE;
                }
                else
                {
                    stChSetting.u16TotalHideSrvNum--;
                    bChListKeyPress = TRUE;
                    u32ChListKeyPressStartTime = msAPI_Timer_GetTime0();
                    enResult = EN_FUNC_MAINPAGE_STATUS_FALSE;
                }
            }
            break;
    #endif //ENABLE_ATSC_MAIN_MENU_CHANNEL_PAGE
#endif //ENABLE_ATSC
       default:
            return enResult;
    }
    return enResult;
}

