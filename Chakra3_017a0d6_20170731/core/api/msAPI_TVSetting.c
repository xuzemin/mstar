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
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <mntent.h>
#include <sys/vfs.h>
#include <pthread.h>

#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"

#include "datatype.h"
#include "debug.h"
#include "Board.h"
#include "sysinfo.h"
#include "drvCPU.h"
#include "msAPI_MailBox.h"
#include "MsTypes.h"
#include "drvBDMA.h"
#include "N51FS_Wrapper.h"
#include "msAPI_Timer.h"
#include "linux_51fs_wrap.h"
#include "linux_usb_mount.h"
#include "msAPI_TVSetting.h"
#include "madp.h"
#include <sys/ioctl.h>
#include "MApp_InputSource.h"
#include "MApp_GlobalSettingSt.h"
#include "msAPI_audio.h"
#include "MApp_GlobalVar.h"
#include "msAPI_ATVSystem.h"
#include "MApp_ChannelChange.h"
#include "MApp_BlockSys.h"
#include "msAPI_VD.h"
#include "msAPI_Tuning.h"
#include "MApp_ChannelList.h"
#include "MApp_GlobalSettingSt_Common.h"
#include "MApp_Audio.h"
#include "apiXC_Ace.h"
#include "MApp_Scaler.h"
#include "apiXC_Sys.h"
#include "apiXC.h"
#include "MApp_ZUI_ACTglobal.h"
#include "MApp_XC_PQ.h"
#include "MApp_SaveData.h"
#include "MApp_ZUI_GlobalFunction.h"
#include "apiAUDIO.h"
#include "drvAVD.h"
#include "MApp_ATV_Scan.h"
#include "msAPI_FreqTableATV.h"
/*
#include "msAPI_Tuning.c"
#include "MApp_ATV_Scan.h"
#include "IF_Demodulator.h"
#include "ZUI_exefunc.h"*/

//#include "msAPI_TVSetting_common.h"
#define MSAPI_TVSETTING_C
#define TVSETTING_NAME "TVSETTING_CLASS"
#define MAX_NUM_OF_VOL_LEVEL 100
bool bTVSettingInited = FALSE;
U8 picSetting[100] ="sendsingal";
U16 tempfreq ;


U8 testforloop  =1;
//EN_SCAN_STATE enScanState = STATE_SCAN_INIT;
//EN_SCAN_STATE enPreScanState = STATE_SCAN_INIT;
//BOOLEAN fReturnToPrevious=FALSE;
BOOLEAN fEndHalt=FALSE;
//EN_DVB_SCAN_STATE enDVBScanState = STATE_DVB_SCAN_INIT;
EN_RET enDVBScanRetVal;

//EN_ATV_SCAN_STATE enATVScanState = STATE_ATV_SCAN_INIT;
//EN_ATV_SCAN_STATE enPreATVScanState = STATE_ATV_SCAN_INIT;
BOOLEAN fReturnToPrevious=FALSE;
//BOOLEAN fEndHalt=FALSE;

U8 PreATVScanPercent;
static XC_SETWIN_INFO stXC_SetWinInfo;

/////////////////////////////////////////////////
//message channel callback
////////////////////////////////////////////////
bool msAPI_TVSetting_ChakraReceiveMsg (unsigned char * pu8InMsg, unsigned short u16InDataSize, unsigned char * pu8OutData, unsigned short u16OutDataSize)
{
    printf("chuli message %s------------------------\n",pu8InMsg);
    if( 'T' != pu8InMsg[0]|| 'V' !=pu8InMsg[1])
        return FALSE;
    UNUSED(u16InDataSize);
    UNUSED(u16OutDataSize);
    U8 u8temp  = pu8InMsg[2];
    switch (u8temp)
    {
        case VCP_PowerMode:
            {
            switch(pu8InMsg[3])
                {
                    case TV_POWER_SAVING_ACOFF:
                        break;
                    case TV_POWER_SAVING_DCOFF:
                        break;
                     case TV_POWER_SAVING_DISPLAYOFF:
                        break;
                    case  TV_POWER_SAVING_LIGHTOFF:
                        MApi_PNL_SetBackLight(pu8InMsg[4]);
                        break;
                }
             //MApp_Standby_Init();
            break;
            }
        case VCP_ChangeInputSource:
            {
                printf("VCP_ChangeInputSource:\n");
                if(pu8InMsg[3] <=7)
                {
                    printf("test %d\n",pu8InMsg[3]);
                    MApp_TVSetting_ChangeDataInputSource((E_DATA_INPUT_SOURCE)GetUIInputSource((EN_TV_UI_INPUT_SOURCE)pu8InMsg[3]));
                }
                else
                {
                   UI_INPUT_SOURCE_TYPE  = (E_UI_INPUT_SOURCE)pu8InMsg[3];
                   MApp_InputSource_ChangeInputSource((SCALER_WIN)0);
                }

                break;
            }
        case VCP_ADJ_TV_Channel:
            ///////pu8InMsg[4] is channel number//////////////////////////
            {
             printf(" VCP_ADJ_TV_Channel::\n");
                MApp_TVSetting_ChannelChange( pu8InMsg[3]);
                break;
            }
        case VCP_ADJ_TV_Set_ChannelNumber:
            {
                    printf("VCP_ADJ_TV_Set_ChannelNumber,%d\n",pu8InMsg[3]);
                     msAPI_ATV_SetCurrentProgramNumber(pu8InMsg[3]);
                     msAPI_Tuner_ChangeProgram();
                     break;
            }
        case VCP_ADJ_MANUL_CHANGE_CHANNEL:
            printf("VCP_ADJ_MANUL_CHANGE_CHANNEL:%d\n",pu8InMsg[3]);
            msAPI_ATV_SetCurrentProgramNumber(pu8InMsg[3]);
            break;
        case VCP_ADJ_Brightness:
             {
             printf("VCP_ADJ_Brightness\n");

                BOOLEAN IsIncreat;
                IsIncreat = pu8InMsg[3];
                    ST_SUBCOLOR.u8SubBrightness =
                        (U8)MApp_ZUI_ACT_DecIncValue(IsIncreat, ST_SUBCOLOR.u8SubBrightness, SUB_BRIGHTNESS_MIN, SUB_BRIGHTNESS_MAX, 1);

                    MApp_SaveSubColorSetting(DATA_INPUT_SOURCE_TYPE(MAIN_WINDOW));

                    MApp_XC_PQ_Set_Brightness(MAIN_WINDOW, TRUE);

                    pu8OutData[0] = (ST_PICTURE.u8Brightness-50);
                break;
             }
          case VCP_ADJ_Sharpness:
              {
              printf("VCP_ADJ_Sharpness\n");
                BOOLEAN IsIncreat;
                IsIncreat = pu8InMsg[3];
                ST_PICTURE.u8Sharpness = MApp_ZUI_ACT_DecIncValue(
                        IsIncreat,ST_PICTURE.u8Sharpness, 0, 100, 1);
                MApi_XC_ACE_PicSetSharpness( MAIN_WINDOW, msAPI_Mode_PictureSharpnessN100toReallyValue(ST_PICTURE.u8Sharpness) );
                 pu8OutData[0] =  (ST_PICTURE.u8Sharpness);
                 break;
              }
          case VCP_ADJ_TV_Saturation:
             {
                printf("VCP_ADJ_TV_Saturation\n");
                BOOLEAN IsIncreat;
                IsIncreat = pu8InMsg[3];
                ST_PICTURE.u8Saturation = MApp_ZUI_ACT_DecIncValue(
                        IsIncreat,ST_PICTURE.u8Saturation, 0, 100, 1);
                MApi_XC_ACE_PicSetSaturation(MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW),  msAPI_Mode_PictureSaturationN100toReallyValue(ST_PICTURE.u8Saturation) );
                pu8OutData[0] = (ST_PICTURE.u8Saturation) ;
                 break;
              }
           case VCP_ADJ_TV_Hue:
             {
             printf("VCP_ADJ_TV_Hue\n");
                BOOLEAN IsIncreat;
                IsIncreat = pu8InMsg[3];
                ST_PICTURE.u8Hue = MApp_ZUI_ACT_DecIncValue(
                        IsIncreat,ST_PICTURE.u8Hue, 0, 100, 1);
               MApi_XC_ACE_PicSetHue( MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW), msAPI_Mode_PictureHueN100toReallyValue(ST_PICTURE.u8Hue) );
                pu8OutData[0] =(ST_PICTURE.u8Hue);
                 break;
              }
            case VCP_ADJ_TV_Contrast:
             {
              printf("VCP_ADJ_TV_Contrast\n");
                BOOLEAN IsIncreat;
                IsIncreat = pu8InMsg[3];
               ST_SUBCOLOR.u8SubContrast =
                       (U8) MApp_ZUI_ACT_DecIncValue(IsIncreat, ST_SUBCOLOR.u8SubContrast, SUB_CONTRAST_MIN, SUB_CONTRAST_MAX, 1);

                    MApp_SaveSubColorSetting(DATA_INPUT_SOURCE_TYPE(MAIN_WINDOW));

                    MApp_XC_PQ_Set_Contrast( MAIN_WINDOW, FALSE);

                 break;
             }
             case VCP_ADJ_AudioVolume:
             {
                printf("VCP_ADJ_AudioVolume\n");
                BOOLEAN IsIncreat;
                IsIncreat = pu8InMsg[3];
                msAPI_TVSetting_Adjvol(IsIncreat);
                 pu8OutData[0] =  stGenSetting.g_SoundSetting.Volume;
                 printf(" stGenSetting.g_SoundSetting.Volume:%d\n", stGenSetting.g_SoundSetting.Volume);
                 break;
             }
             case VCP_ADJ_EFFECT:
             {
              printf("VCP_ADJ_EFFECT\n");
                MApp_Aud_SetSurroundMode(MApp_TVSetting_GetSuroundFromEffect (pu8InMsg[3]));
                 break;
             }
             case VCP_ATV_COLORSYS:
             {
                   printf("VCP_ATV_COLORSYS  %d\n",pu8InMsg[3]);
                   MApp_TVSetting_SetATVColorSystem(pu8InMsg[3]);
                    pu8OutData[0] = '0';
                   break;
             }
             case VCP_ATV_SOUNDRSYS:
             {
              printf("VCP_ATV_SOUNDRSYS  %d\n",pu8InMsg[3]);
                    MApp_TVSetting_SetATVSoundSystem(pu8InMsg[3]);
                     pu8OutData[0] = '0';
                    break;
             }
            case VCP_Query:
            {
                    printf("VCP_Query\n");
                    MApp_TVSetting_Query(pu8InMsg[3], pu8OutData);
                    printf("MApp_TVSetting_Query  %d\n",pu8OutData[4]);
                    break;
            }
         case VCP_ADJ_TV_Audio_Treble:
         {
           printf("VCP_ADJ_TV_Audio_Treble\n");
            msAPI_Adjust_Audio_Treble(pu8InMsg[3]);
             pu8OutData[0] = '0';
             break;
         }

         case VCP_ADJ_TV_Audio_Bass:
         {
         printf("VCP_ADJ_TV_Audio_Bass\n");
            msAPI_Adjust_Audio_Bass(pu8InMsg[3]);
             pu8OutData[0] = '0';
             break;
         }
         case VCP_ADJ_TV_Audio_Balance:
         {
          printf("VCP_ADJ_TV_Audio_Balance\n");
            msAPI_Adjust_Audio_Balance(pu8InMsg[3]);
             pu8OutData[0] = '0';
             break;
         }
         case VCP_ATV_AUTO_SCAN:
         {
          printf("VCP_ATV_AUTO_SCAN\n");
            stGenSetting.stScanMenuSetting.u8ScanType = SCAN_TYPE_AUTO;
           // enATVScanState = STATE_ATV_SCAN_INIT;
           // msAPI_TVSetting_Scan();
           printf("ATV scan");
           MApp_ATV_Scan_State_Init ();
           u8KeyCode  = VK_NULL;
           MApp_ATV_Scan();
           pu8OutData[0] ='0';
            break;
         }
         case VCP_ATV_MANUL_SCAN:
         {
             printf("VCP_ATV_MANUL_SCAN\n");
            stGenSetting.stScanMenuSetting.u8ScanType = SCAN_TYPE_MANUAL;
            stGenSetting.stScanMenuSetting.u8ATVManScanType = ATV_MAN_SCAN_TYPE_ONECH;
            if(pu8InMsg[3])
                stGenSetting.stScanMenuSetting.u8ATVManScanDir = ATV_MAN_SCAN_UP;
            else
                stGenSetting.stScanMenuSetting.u8ATVManScanDir = ATV_MAN_SCAN_DOWN;
            MApp_ATV_Scan_State_Init ();
            u8KeyCode  = VK_NULL;
            MApp_ATV_Scan();
            pu8OutData[0] = '0';
            printf("percent %d\n", msAPI_Tuner_GetTuningProcessPercent());

            break;
         }
         case VCP_ATV_SET_SCAN_STATE:
         {
            EN_ATV_SCAN_STATE etempscanstate = STATE_ATV_SCAN_INIT;
            switch((EN_TV_SCAN_STATE) pu8InMsg[3])
            {
                case TV_SCAN_INIT:
                    etempscanstate =  STATE_ATV_SCAN_INIT;
                    break;
                case TV_SCAN_PAUSE:
                    etempscanstate =  STATE_ATV_SCAN_PAUSE;
                    break;
                case TV_SCAN_END:
                    etempscanstate =  STATE_ATV_SCAN_END;
                    break;
                case TV_SCAN_STANDBY:
                    etempscanstate = STATE_ATV_SCAN_GOTO_STANDBY;
            }
            if (MApp_ATV_Scan_ScanState()  != etempscanstate)
               {
                    MApp_ATV_SetATVScanState(etempscanstate);
               }

                MApp_ATV_Scan();
            break;
         }
        case VCP_ATV_SET_AFC:
        {
            printf("VCP_ATV_MANUL_SCAN\n");
            msAPI_ATV_NeedAFT(msAPI_ATV_GetCurrentProgramNumber(),pu8InMsg[3]);
            break;
        }
        case VCP_ATV_SET_FINETUNE:
        {
          printf("VCP_ATV_SET_FINETUNE\n");
            //msAPI_TVSetting_SetAFC((U16)pu8InMsg[3]);
            msAPI_Tuner_AdjustUnlimitedFineTune((DIRECTION)((pu8InMsg[3]+1)%2));
              pu8OutData[0] = msAPI_TVSetting_getpercent();
              pu8OutData[1] =  msAPI_ATV_GetCurrentProgramNumber();
              tempfreq =  msAPI_Tuner_GetCurrentChannelPLL();
              pu8OutData[2] =(U8)tempfreq;
              pu8OutData[3] = (tempfreq>>8) & 0xFF;
            break;
        }
        case VCP_ADJ_Set_AudioChannel:
            switch((EN_AP_AUDIO_CHANNEL)pu8InMsg[3])
                {
                case  TV_AUDIO_CHANNEL_HEADPHONE:
                    stGenSetting.g_SoundSetting.ADOutput = AD_HEADPHONE;
                    break;
                case TV_AUDIO_CHANNEL_SPEAKER:
                    stGenSetting.g_SoundSetting.ADOutput = AD_SPEAKER;
                    break;
                default:
                    pu8OutData[0] = 100;
                   break;
                 }
            MApi_AUDIO_SetADOutputMode(stGenSetting.g_SoundSetting.ADOutput);
            break;
        case VCP_ATV_MANUL_SAVE_INFO:
            MApp_SaveScanMenuSetting();
            break;
        case VCP_SCALER_SET_WINDOW:
            //
            // pu8InMsg[3] : 0 input window, 1 output window
            //
            printf("VCP_SET_DISPLAY_WIN\n");
            {
                U32 u32Left;
                U32 u32Top;
                U32 u32Width;
                U32 u32Height;

                u32Left     = pu8InMsg[4]  | (pu8InMsg[5] << 8) | (pu8InMsg[6] << 16) | (pu8InMsg[7] << 24);
                u32Top     = pu8InMsg[8]  | (pu8InMsg[9] << 8) | (pu8InMsg[10] << 16) | (pu8InMsg[11] << 24);
                u32Width  = pu8InMsg[12]  | (pu8InMsg[13] << 8) | (pu8InMsg[14] << 16) | (pu8InMsg[15] << 24);
                u32Height = pu8InMsg[16]  | (pu8InMsg[17] << 8) | (pu8InMsg[18] << 16) | (pu8InMsg[18] << 24);

                printf("left = %d, top = %d, width = %d, height = %d\n", u32Left, u32Top, u32Width, u32Height);

                if(pu8InMsg[3])   // output window
                {
                    printf("set output window in chakra\n");
                    stXC_SetWinInfo.stDispWin.x           = u32Left;
                    stXC_SetWinInfo.stDispWin.y           = u32Top;
                    stXC_SetWinInfo.stDispWin.width     = u32Width;
                    stXC_SetWinInfo.stDispWin.height    = u32Height;
                }
                else
                {
                    printf("set input window in chakra\n");
                    stXC_SetWinInfo.stCropWin.x           = u32Left;
                    stXC_SetWinInfo.stCropWin.y           = u32Top;
                    stXC_SetWinInfo.stCropWin.width     = u32Width;
                    stXC_SetWinInfo.stCropWin.height    = u32Height;
                }

                if((stXC_SetWinInfo.stCropWin.width == 0)  && (stXC_SetWinInfo.stDispWin.width == 0))// if input win is 0, use the default value
                {
                    MApp_Scaler_SetWindow(NULL, NULL, NULL, stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
                }
                else if(stXC_SetWinInfo.stCropWin.width == 0)
                {
                    MApp_Scaler_SetWindow(NULL, NULL, &stXC_SetWinInfo.stDispWin, stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
                }
                else if (stXC_SetWinInfo.stDispWin.width == 0)
                {
                    MApp_Scaler_SetWindow(NULL, &stXC_SetWinInfo.stCropWin, NULL, stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
                }
                else
                {
                    MApp_Scaler_SetWindow(NULL, &stXC_SetWinInfo.stCropWin, &stXC_SetWinInfo.stDispWin, stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
                }
            }

            break;

    }
printf("over\n");
return TRUE;
}
#if 0
bool msAPI_TVSetting_test_ChakraReceiveMsg (unsigned char * pu8InMsg, unsigned short u16InDataSize, unsigned char * pu8OutData, unsigned short u16OutDataSize)
{
    printf("pin message %s\n",pu8InMsg);
    UNUSED(u16InDataSize);
    pu8OutData[0] = 'X';
     pu8OutData[1] = 'X';
      pu8OutData[2] = 'X';
       pu8OutData[3] = 'X';
        pu8OutData[4] = 'X';

}
#endif
void msAPI_TVSetting_Init( void )
{
    printf("\nTVSetting_Init\n");
    MAdp_MSGCH_Init();
    MAdp_MSGCH_SetCallBack(MAdp_MSGCH_GetChannelIndex("TVSETTING_CLASS"), msAPI_TVSetting_ChakraReceiveMsg);
    memset(&stXC_SetWinInfo, 0, sizeof(stXC_SetWinInfo));
}

bool msAPI_TVSetting_SendToAPPacket(U8* TVSetting)
{

      U8 u8ChIndex = MAdp_MSGCH_GetChannelIndex(TVSETTING_NAME);

  // pid_t cur_activated_ap = pthread_self() ; //MAdp_APMNG_GetActivatedAppPid();





    pid_t cur_activated_ap = MAdp_APMNG_GetActivatedAppPid();
    if(cur_activated_ap != 0)  // application is running
    {
        printf("Send signal to pid: %d\n", cur_activated_ap);
        if (MAdp_MSGCH_SendSignal(cur_activated_ap,u8ChIndex, (unsigned char *)TVSetting, sizeof(TVSetting)))
       // MAdp_MSGCH_Communicate(pid, MAdp_MSGCH_GetChannelIndex("FS_MOUNT_STATUS"), msg, 1, (unsigned char*)&mnt_point, sizeof(mnt_point));

        {
            printf("[D-Bus] Send signal to TVSETTING channel OK\n");

            return TRUE;
        }
        else
        {
            printf("[D-Bus] Send signal to TVSETTING channel fail\n");
            return FALSE;
        }
    }
    else
    {
        printf("No AP is running\n");
        return FALSE;
    }
}
////////////////////////////////////////////////////////////////////////////////////////
U8 GetUIInputSource(EN_TV_UI_INPUT_SOURCE enTv_inputsource )
{
    printf("enTv_inputsource: %d\n",(U8)enTv_inputsource);
    switch(enTv_inputsource)
    {
    #if (ENABLE_DTV)
        case TV_UI_INPUT_SOURCE_DTV:
            return DATA_INPUT_SOURCE_DTV;
    #endif
        case TV_UI_INPUT_SOURCE_ATV:            // VIDEO - TV Tuner
             return DATA_INPUT_SOURCE_ATV;
        case TV_UI_INPUT_SOURCE_AV:                // VIDEO - CVBS
             return DATA_INPUT_SOURCE_AV;
        case TV_UI_INPUT_SOURCE_SVIDEO:            // VIDEO - Y/C
             return DATA_INPUT_SOURCE_SVIDEO;
        case TV_UI_INPUT_SOURCE_COMPONENT:        // VIDEO - YPbPr
             return DATA_INPUT_SOURCE_COMPONENT;
        case TV_UI_INPUT_SOURCE_RGB:                // PC - VGA
             return DATA_INPUT_SOURCE_RGB;
        case TV_UI_INPUT_SOURCE_HDMI:        // HDMI
            return DATA_INPUT_SOURCE_HDMI;
        default:
            return DATA_INPUT_SOURCE_NONE;
    }
}
////////////////////////////////////////////////////////////////////////
U8  MApp_TVSetting_GetSuroundFromEffect(U8 u8Effect)
{
    switch (u8Effect)
    {
        case TV_AUDIO_EFFECT_OFF:
            return 0;
        case TV_AUDIO_EFFECT_BBE:
            return 1;
        case TV_AUDIO_EFFECT_SRS:
            return 2;
        case TV_AUDIO_EFFECT_DOLBY:
            return 6;
    }
    return 8;
}
#if 0
///////////////////for switch input source////////////////////////////////////
static void MApp_TVSetting_SetLastChByType(U8 chtype)
{
    U16 progIdx=1;

    chtype = chtype;

    MApp_ChannelChange_DisableChannel(TRUE, MAIN_WINDOW);

    msAPI_CM_SetCurrentServiceType((MEMBER_SERVICETYPE)progIdx);

    MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
}
#endif
void MApp_TVSetting_ChangeDataInputSource(E_DATA_INPUT_SOURCE eDataInputSource)
{
    //from function MApp_UiMenuFunc_ChangeDataInputSource()

    switch(eDataInputSource)
    {
        default:
    #if (ENABLE_DTV)
        case DATA_INPUT_SOURCE_DTV:
          // MApp_TVSetting_SetLastChByType(CH_TYPE_DTV);
           UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DTV;
            MApp_InputSource_ChangeInputSource((SCALER_WIN) 0);
            break;
    #endif
        case DATA_INPUT_SOURCE_ATV:
           // MApp_TVSetting_SetLastChByType(CH_TYPE_ATV);
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ATV;
            MApp_InputSource_ChangeInputSource((SCALER_WIN) 0);
            break;
    #if (INPUT_AV_VIDEO_COUNT >= 1)
        case DATA_INPUT_SOURCE_AV:
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_AV;
            MApp_InputSource_ChangeInputSource((SCALER_WIN) 0);
            break;
    #endif
    #if (INPUT_AV_VIDEO_COUNT >= 2)
        case DATA_INPUT_SOURCE_AV2:
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_AV2;
            MApp_InputSource_ChangeInputSource((SCALER_WIN) 0);
            break;
    #endif
    #if (INPUT_AV_VIDEO_COUNT >= 3)
        case DATA_INPUT_SOURCE_AV3:
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_AV3;
            MApp_InputSource_ChangeInputSource((SCALER_WIN) 0);
            break;
    #endif

    #if    (INPUT_SV_VIDEO_COUNT >= 1)
        case DATA_INPUT_SOURCE_SVIDEO:
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_SVIDEO;
            MApp_InputSource_ChangeInputSource((SCALER_WIN) 0);
            break;
    #endif

    #if (INPUT_SV_VIDEO_COUNT >= 2)
        case DATA_INPUT_SOURCE_SVIDEO2:
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_SVIDEO2;
            MApp_InputSource_ChangeInputSource((SCALER_WIN)0);
            break;
    #endif
    #if    (INPUT_YPBPR_VIDEO_COUNT >= 1)
        case DATA_INPUT_SOURCE_COMPONENT:
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_COMPONENT;
            MApp_InputSource_ChangeInputSource((SCALER_WIN) 0);
            break;
    #endif

    #if    (INPUT_YPBPR_VIDEO_COUNT >= 2)
        case DATA_INPUT_SOURCE_COMPONENT2:
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_COMPONENT2;
            MApp_InputSource_ChangeInputSource((SCALER_WIN)0);
            break;
    #endif

        case DATA_INPUT_SOURCE_RGB:
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_RGB;
            MApp_InputSource_ChangeInputSource((SCALER_WIN) 0);
            break;

    #if (INPUT_HDMI_VIDEO_COUNT > 0)
        case DATA_INPUT_SOURCE_HDMI:
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_HDMI;
            MApp_InputSource_ChangeInputSource((SCALER_WIN) 0);
            break;
    #endif
    #if    (INPUT_HDMI_VIDEO_COUNT >= 2)
        case DATA_INPUT_SOURCE_HDMI2:
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_HDMI2;
            MApp_InputSource_ChangeInputSource((SCALER_WIN) 0);
            break;
    #endif
    #if    (INPUT_HDMI_VIDEO_COUNT >= 3)
        case DATA_INPUT_SOURCE_HDMI3:
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_HDMI3;
            MApp_InputSource_ChangeInputSource((SCALER_WIN) 0);
            break;
    #endif
    #if    (INPUT_HDMI_VIDEO_COUNT >= 4)
        case DATA_INPUT_SOURCE_HDMI4:
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_HDMI4;
            MApp_InputSource_ChangeInputSource((SCALER_WIN) 0);
            break;
    #endif
    #if ENABLE_DMP
        case DATA_INPUT_SOURCE_STORAGE:
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DMP;
            MApp_InputSource_ChangeInputSource((SCALER_WIN) 0);
            break;
    #endif //#if ENABLE_DMP
    }
}

////////////////////////for channel change////////////////////////////////////////
void MApp_TVSetting_ChannelChange( BOOLEAN IsChannelPlus )
{
 /*   #if ENABLE_SBTVD_CM_APP
    U16 u16CurOridinal,u16NextOridinal,u16NextPosition;
    MEMBER_SERVICETYPE bNextServiceType;
    //E_UI_INPUT_SOURCE ePreInput_Source_Type;
    #endif
  //  if(u8KeyCode == KEY_CHANNEL_PLUS || u8KeyCode == KEY_CHANNEL_MINUS)
    {
        MApp_ZUI_ACT_ResetInfoTimer();
         #if ENABLE_SBTVD_CM_APP
            {
                u16NextOridinal =0;
                u16CurOridinal = msAPI_CHPROC_CM_GetCurrentOrdinal(E_SERVICETYPE_UNITED_TV,E_PROGACESS_INCLUDE_VISIBLE_ONLY);

                if(IsChannelPlus)
                    u16NextOridinal = msAPI_CHPROC_CM_GetNextOrdinal(E_SERVICETYPE_UNITED_TV,u16CurOridinal,FALSE);
                else //if(u8KeyCode == KEY_CHANNEL_MINUS)
                    u16NextOridinal = msAPI_CHPROC_CM_GetPrevOrdinal(E_SERVICETYPE_UNITED_TV,u16CurOridinal,FALSE);

                msAPI_CHPROC_CM_GetOrdinal_SerType_Position_Brazil(u16NextOridinal,&bNextServiceType,&u16NextPosition);

                //ePreInput_Source_Type = UI_INPUT_SOURCE_TYPE;

                if(bNextServiceType == E_SERVICETYPE_ATV)
                    UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ATV;
                else
                    UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DTV;

                MApp_InputSource_SwitchSource( UI_INPUT_SOURCE_TYPE, MAIN_WINDOW );
            }
            #endif
    }*/
  if (IsChannelPlus)
        {
        #if (ENABLE_DTV)
            if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
                #if (ENABLE_PIP)
                || (IsPIPEnable() && IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
                #endif
                )
            {
                MEMBER_SERVICETYPE bServiceType,bNewServiceType;
                WORD wNextProgramPosition;

                #if ENABLE_SBTVD_CM_APP
                bNewServiceType = bNextServiceType;
                bServiceType = E_SERVICETYPE_INVALID;
                wNextProgramPosition = u16NextPosition;
                #else
                bNewServiceType = bServiceType = msAPI_CM_GetCurrentServiceType();
                wNextProgramPosition = msAPI_CM_GetNextProgramPosition(bServiceType, msAPI_CM_GetCurrentPosition(bServiceType), FALSE, E_ALL_LIST,&bNewServiceType);
                #endif
                if( wNextProgramPosition != INVALID_PROGRAM_POSITION )
                {
                    dmSetLastWatchedOrdinal();

                    if(bNewServiceType != bServiceType)
                    {
                        bServiceType = bNewServiceType;
                        msAPI_CM_SetCurrentServiceType(bNewServiceType);
                    }

                    msAPI_CM_SetCurrentPosition(bServiceType, wNextProgramPosition);
                    if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) )
                        MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);
                    #if (ENABLE_PIP)
                    if(IsPIPSupported())
                    {
                        if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) )
                            MApp_ChannelChange_DisableChannel(TRUE,SUB_WINDOW);
                    }
                    #endif
                    stGenSetting.stScanMenuSetting.u8RFChannelNumber= msAPI_CM_GetPhysicalChannelNumber(bServiceType, wNextProgramPosition);
                }

            }
            else
        #endif
            {
                if( msAPI_ATV_GetCurrentProgramNumber() == msAPI_ATV_GetNextProgramNumber(msAPI_ATV_GetCurrentProgramNumber(), FALSE) )
                {
                  //  u8KeyCode = KEY_NULL;
                    return;
                }

            #if ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_ATV_SYSTEM || (TV_SYSTEM == TV_NTSC) )
                msAPI_ATV_SetDirectTuneFlag(TRUE);
            #endif

                dmSetLastWatchedOrdinal();

            #if ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_ATV_SYSTEM || (TV_SYSTEM == TV_NTSC) )
                msAPI_ATV_SetDirectTuneFlag(FALSE);
            #endif

                if( IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) )
                    MApp_ChannelChange_DisableAV(MAIN_WINDOW);
                #if (ENABLE_PIP)
                if(IsPIPSupported())
                {
                    if( IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) )
                        MApp_ChannelChange_DisableAV(SUB_WINDOW);
                }
                #endif
                //Cancel Freeze
                if(g_bIsImageFrozen)
                {
                    g_bIsImageFrozen = FALSE;
                    MApi_XC_FreezeImg(g_bIsImageFrozen, MAIN_WINDOW);
                }

                msAPI_ATV_SetCurrentProgramNumber(msAPI_ATV_GetNextProgramNumber(msAPI_ATV_GetCurrentProgramNumber(), FALSE));
                //BY 20090406 msAPI_VD_AdjustVideoFactor(E_ADJUST_VIDEOMUTE_DURING_LIMITED_TIME, DELAY_FOR_STABLE_TUNER);

                msAPI_AVD_TurnOffAutoAV();
                msAPI_Tuner_ChangeProgram();
                //msAPI_VD_ClearSyncCheckCounter();
                msAPI_AVD_ClearAspectRatio();

                MApp_CheckBlockProgramme();        // 070711_SK_1 block programme
            }
            //u8KeyCode = KEY_NULL;

         }
        else
        {
        #if (ENABLE_DTV)
            if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
            {
                MEMBER_SERVICETYPE bServiceType,bNewServiceType;
                WORD wPrevProgramPosition;

                bNewServiceType = bServiceType = msAPI_CM_GetCurrentServiceType();
                wPrevProgramPosition = msAPI_CM_GetPrevProgramPosition(bServiceType, msAPI_CM_GetCurrentPosition(bServiceType), FALSE, E_ALL_LIST, &bNewServiceType);
                if( wPrevProgramPosition != INVALID_PROGRAM_POSITION )
                {
                    dmSetLastWatchedOrdinal();

                    if(bNewServiceType != bServiceType)
                    {
                        msAPI_CM_SetCurrentServiceType(bNewServiceType);
                        bServiceType = bNewServiceType;
                    }

                    msAPI_CM_SetCurrentPosition(bServiceType, wPrevProgramPosition);
                    if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) )
                        MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);
                    #if (ENABLE_PIP)
                    if(IsPIPSupported())
                    {
                        if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) )
                            MApp_ChannelChange_DisableChannel(TRUE,SUB_WINDOW);
                    }
                    #endif
                    stGenSetting.stScanMenuSetting.u8RFChannelNumber= msAPI_CM_GetPhysicalChannelNumber(bServiceType, wPrevProgramPosition);

                }


            }
            else
        #endif
            {

            #if ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_ATV_SYSTEM || (TV_SYSTEM == TV_NTSC) )
                msAPI_ATV_SetDirectTuneFlag(TRUE);
            #endif

                dmSetLastWatchedOrdinal();

            #if ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_ATV_SYSTEM || (TV_SYSTEM == TV_NTSC) )
                msAPI_ATV_SetDirectTuneFlag(FALSE);
            #endif

                if( IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) )
                    MApp_ChannelChange_DisableAV(MAIN_WINDOW);
                if(g_bIsImageFrozen)
                {
                    g_bIsImageFrozen = FALSE;
                    MApi_XC_FreezeImg(g_bIsImageFrozen, MAIN_WINDOW);
                }

                msAPI_ATV_SetCurrentProgramNumber(msAPI_ATV_GetPrevProgramNumber(msAPI_ATV_GetCurrentProgramNumber(), FALSE));
                //BY 20090406 msAPI_VD_AdjustVideoFactor(E_ADJUST_VIDEOMUTE_DURING_LIMITED_TIME, DELAY_FOR_STABLE_TUNER);
                msAPI_AVD_TurnOffAutoAV();
                msAPI_Tuner_ChangeProgram();
                //msAPI_VD_ClearSyncCheckCounter();
                msAPI_AVD_ClearAspectRatio();

                MApp_CheckBlockProgramme();        // 070711_SK_1 block programme
            }

        }
}

void msAPI_TVSetting_Adjvol(BOOLEAN IsincVol)
{
         if(IsincVol)
            {
                if ( stGenSetting.g_SoundSetting.Volume < MAX_NUM_OF_VOL_LEVEL )
                {
                    stGenSetting.g_SoundSetting.Volume+= 5;
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, stGenSetting.g_SoundSetting.Volume, 0);
                }
            }
            else
            {
                if ( stGenSetting.g_SoundSetting.Volume > 0 )
                {
                    stGenSetting.g_SoundSetting.Volume-= 5;
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, stGenSetting.g_SoundSetting.Volume, 0);
                }
            }
}
void MApp_TVSetting_SetATVColorSystem(U8 u8colorSystem)
{
     AVD_VideoStandardType eVideoSystem;
    switch ((EN_ATV_COLOR_SYSTEM)u8colorSystem)
    {
        case ATV_COLOR_AUTO:
            eVideoSystem= E_VIDEOSTANDARD_AUTO;
            break;
        case ATV_COLOR_PAL:
            eVideoSystem= E_VIDEOSTANDARD_PAL_M ;   // PAL
            break;
        case ATV_COLOR_NTSC:
            eVideoSystem= E_VIDEOSTANDARD_NTSC_M;   // NTSC-M/N
            break;
        case ATV_COLOR_SECAM:
            eVideoSystem= E_VIDEOSTANDARD_SECAM;   // SECAM-L'
            break;
        default :
            eVideoSystem = E_VIDEOSTANDARD_AUTO;
            break;
    }
    if (eVideoSystem == E_VIDEOSTANDARD_AUTO)
    {
         msAPI_AVD_StartAutoStandardDetection();
         msAPI_AVD_GetResultOfAutoStandardDetection();
     }
     else
        msAPI_AVD_ForceVideoStandard(eVideoSystem);
    msAPI_ATV_SetVideoStandardOfProgram((msAPI_ATV_GetCurrentProgramNumber()), eVideoSystem);
}

void MApp_TVSetting_SetATVSoundSystem(U8 u8SoundSystem)
{
    AUDIOSTANDARD_TYPE eAudioStandard = E_AUDIOSTANDARD_DK;
    //EN_ATV_SYSTEM_TYPE u8AudioSystem =EN_ATV_SystemType_BG;
    switch ((EN_ATV_SOUND_SYSTEM) u8SoundSystem )
    {
        case ATV_SOUND_DK:
            eAudioStandard = E_AUDIOSTANDARD_DK;
            break;
        case ATV_SOUND_BG:
             eAudioStandard = E_AUDIOSTANDARD_BG ;
            break;
        case ATV_SOUND_I:
             eAudioStandard = E_AUDIOSTANDARD_I;
            break;
        case ATV_SOUND_MN:
             eAudioStandard = E_AUDIOSTANDARD_M;
            break;
         default :
            break;
    }
        msAPI_AUD_SetAudioStandard(eAudioStandard);

}
////////////////////////////////////////////////////////////
//audio  bass balance treble
////////////////////////////////////////////////////////////
void msAPI_Adjust_Audio_Bass(U8 Isup)
{

    //from case MAPP_UIMENUFUNC_ADJU16C1_SOUND_USER_BASS:
    //MApp_UiMenuFunc_CheckAudioMode();
    U8 u8ValueTmp = stGenSetting.g_SoundSetting.astSoundModeSetting[SOUND_MODE_STANDARD].Bass;
    stGenSetting.g_SoundSetting.astSoundModeSetting[SOUND_MODE_STANDARD].Bass =
          MApp_ZUI_ACT_DecIncValue(
                        Isup,
                        stGenSetting.g_SoundSetting.astSoundModeSetting[SOUND_MODE_STANDARD].Bass, 0, 100, 1);

     if(stGenSetting.g_SoundSetting.astSoundModeSetting[SOUND_MODE_STANDARD].Bass == u8ValueTmp)
         {
                    //bRet = FALSE;
          }
      else
          {
              MApi_AUDIO_EnableTone(TRUE);
              MApi_AUDIO_SetBass(stGenSetting.g_SoundSetting.astSoundModeSetting[SOUND_MODE_STANDARD].Bass);
          }

}
void msAPI_Adjust_Audio_Balance(U8 Isup)
{
     U8 u8ValueTmp = stGenSetting.g_SoundSetting.Balance;
     stGenSetting.g_SoundSetting.Balance = MApp_ZUI_ACT_DecIncValue(
           Isup,
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
                // Force to disable mute no matter what the current mute state is
       msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);

}
void msAPI_Adjust_Audio_Treble(U8 Isup)
{
                //from case MAPP_UIMENUFUNC_ADJU16C1_SOUND_USER_TREBLE:
                //MApp_UiMenuFunc_CheckAudioMode();
     U8 u8ValueTmp = stGenSetting.g_SoundSetting.astSoundModeSetting[SOUND_MODE_STANDARD].Treble;
     stGenSetting.g_SoundSetting.astSoundModeSetting[SOUND_MODE_STANDARD].Treble =
         MApp_ZUI_ACT_DecIncValue(
             Isup,
              stGenSetting.g_SoundSetting.astSoundModeSetting[SOUND_MODE_STANDARD].Treble, 0, 100, 1);

     if(stGenSetting.g_SoundSetting.astSoundModeSetting[SOUND_MODE_STANDARD].Treble == u8ValueTmp)
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

#if 0
void msAPI_TVSetting_SetAFC(U16 u16PLL)
{
  _bIsPreProgramDetected = FALSE;

    if ( u16PLL < VHF_LOWMIN_PLL )
    {
        u16PLL = VHF_LOWMIN_PLL;
    }
    else if ( UHF_MAX_PLL < u16PLL )
    {
        if(u16PLL == DEFAULT_PLL) //DEFAULT_PLL
            ; //keep original Default PLL
        else
            u16PLL = UHF_MAX_PLL;
    }

    if  ( DIFFERENCE(_u16TunerPLL, u16PLL) < TUNER_PLL_PLUS_0p25MHz )
    {
#if TV_SCAN_PAL_SECAM_ONCE//For L Search, From BG to SCEAM-L, Step=0, u16TuningWaitTimer = WAIT_230ms;
        if ((_bIsLSearch))
            _u16TuningWaitTimer = AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_0P25MHZ_STEP_L;
        else
#endif
        _u16TuningWaitTimer = AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_0P25MHZ_STEP;
    }
    else if ( DIFFERENCE(_u16TunerPLL, u16PLL) < TUNER_PLL_PLUS_0p5MHz )
    {
        _u16TuningWaitTimer = AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_0P5MHZ_STEP;
    }
    else if ( DIFFERENCE(_u16TunerPLL, u16PLL) < TUNER_PLL_PLUS_4MHz )
    {
        _u16TuningWaitTimer = AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_4MHZ_STEP;
    }
    else
    {
        _u16TuningWaitTimer = AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_MAX_STEP;
    }

    if ( _GetBand(_u16TunerPLL) != _GetBand(u16PLL) )
    {
        _u16TuningWaitTimer = AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_CROSS_BAND_STEP;
    }

    _u16TunerPLL = u16PLL;

#if ENABLE_AUTOTEST
    if(g_bAutobuildDebug && (msAPI_CFT_ConvertPLLtoIntegerOfFrequency(_u16TunerPLL) == 850))
    {
        printf("31_ATV_Failed\n");
    }
#endif

    devTunerSetPLLData( _u16TunerPLL+msAPI_Tuner_GetIF(), _GetBand(_u16TunerPLL) );
#if((FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)||(FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)||(FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF))
    _SetVifIfFreq();
#endif
}
#endif
////////////////////////////////////////////////////////////
//Query
////////////////////////////////////////////////////////////
void  MApp_TVSetting_Query(U8 u8querytype,U8* returnvalue)
{
   switch (u8querytype)
    {
       case VCP_ADJ_Get_AudioChannel:
            returnvalue[0]=stGenSetting.g_SoundSetting.ADOutput;
            break;
       case VCP_ADJ_Brightness:
            returnvalue[0]= ST_SUBCOLOR.u8SubBrightness-78;
            break;
      case VCP_ADJ_Sharpness:
           returnvalue[0]=ST_PICTURE.u8Sharpness;
            break;
        case VCP_ADJ_Contrast:
           returnvalue[0]= MApp_Scaler_FactoryContrast(ST_PICTURE.u8Contrast,ST_SUBCOLOR.u8SubContrast);//ST_SUBCOLOR.u8SubContrast;
            break;
        case VCP_ADJ_TV_Saturation:
            returnvalue[0]=ST_PICTURE.u8Saturation;
            break;
         case VCP_ADJ_TV_Hue:
           returnvalue[0]=ST_PICTURE.u8Hue;
            break;
         case VCP_ADJ_GET_PICTURE_SETTING:
            returnvalue[0]= MApp_Scaler_FactoryContrast(ST_PICTURE.u8Contrast,ST_SUBCOLOR.u8SubContrast);///ST_SUBCOLOR.u8SubContrast;
            returnvalue[1]=ST_SUBCOLOR.u8SubBrightness -78;
            returnvalue[2]=ST_PICTURE.u8Saturation;
            returnvalue[3]= ST_PICTURE.u8Sharpness;
            returnvalue[4]=ST_PICTURE.u8Hue;
            printf("VCP_ADJ_GET_PICTURE_SETTING :%d,%d,%d,%d,%d\n",ST_SUBCOLOR.u8SubContrast,ST_SUBCOLOR.u8SubBrightness,ST_PICTURE.u8Saturation,ST_PICTURE.u8Sharpness,returnvalue[4]);
            break;
        // case VCP_ChangeInputSource:
          // returnvalue[0]=MApp_InputSource_GetRecordSource();
            break;
         case VCP_ADJ_TV_Channel:
           returnvalue[0]= msAPI_ATV_GetCurrentProgramNumber();

            break;
         case VCP_ADJ_AudioVolume:
           returnvalue[0]=stGenSetting.g_SoundSetting.Volume;
            break;
         case VCP_ADJ_EFFECT:
            returnvalue[0]= '0';
            break;
         case VCP_ATV_COLORSYS:

            switch (msAPI_ATV_GetVideoStandardOfProgram(msAPI_ATV_GetCurrentProgramNumber()))
            {
                printf("--%d\n",msAPI_ATV_GetVideoStandardOfProgram(msAPI_ATV_GetCurrentProgramNumber()));
                case E_VIDEOSTANDARD_AUTO:
                    returnvalue[0] = (U8)ATV_COLOR_AUTO;
                    break;
                case E_VIDEOSTANDARD_PAL_60:
                case E_VIDEOSTANDARD_PAL_BGHI:
                case E_VIDEOSTANDARD_PAL_M:
                case E_VIDEOSTANDARD_PAL_N:
                    returnvalue[0] = (U8)ATV_COLOR_PAL;
                    break;
                case E_VIDEOSTANDARD_NTSC_44:
                case E_VIDEOSTANDARD_NTSC_M:
                    returnvalue[0] = (U8)ATV_COLOR_NTSC;
                    break;
                case E_VIDEOSTANDARD_SECAM:
                    returnvalue[0] = (U8)ATV_COLOR_SECAM;
                    break;
                 default:
                    returnvalue[0]= ATV_COLOR_AUTO;
                    break;
            }
            printf("VCP_ATV_COLORSYS:%d\n",returnvalue[0]);
            break;
         case VCP_ATV_SOUNDRSYS:

            //AUDIOSTANDARD_TYPE temp = msAPI_AUD_GetAudioStandard();
             switch (msAPI_AUD_GetAudioStandard())
             {
                case E_AUDIOSTANDARD_BG:
                case E_AUDIOSTANDARD_BG_A2:
                case E_AUDIOSTANDARD_BG_NICAM:
                    returnvalue[0] = (U8)ATV_SOUND_BG;
                    break;
                case E_AUDIOSTANDARD_DK:
                case E_AUDIOSTANDARD_DK1_A2:
                case E_AUDIOSTANDARD_DK3_A2:
                case E_AUDIOSTANDARD_DK2_A2:
                case E_AUDIOSTANDARD_DK_NICAM:
                      returnvalue[0] = (U8)ATV_SOUND_DK;
                      break;
                case E_AUDIOSTANDARD_I:
                      returnvalue[0] = (U8)ATV_SOUND_I;
                      break;
                case E_AUDIOSTANDARD_M:
                case E_AUDIOSTANDARD_M_A2:
                case E_AUDIOSTANDARD_M_BTSC:
                case E_AUDIOSTANDARD_M_EIA_J:
                     returnvalue[0] = (U8)ATV_SOUND_MN;
                     break;
                default:
                    returnvalue[0]= 100;
                    break;

             }
             printf(" returnvalue[0] : %d\n",  returnvalue[0]);
            break;
         case VCP_ADJ_TV_Audio_Treble:
           returnvalue[0]=stGenSetting.g_SoundSetting.astSoundModeSetting[SOUND_MODE_STANDARD].Treble;
            break;
         case VCP_ADJ_TV_Audio_Bass:
            returnvalue[0]=stGenSetting.g_SoundSetting.astSoundModeSetting[SOUND_MODE_STANDARD].Bass;
            break;
         case VCP_ADJ_TV_Audio_Balance:
           returnvalue[0]=stGenSetting.g_SoundSetting.Balance;
            break;
         case VCP_ADJ_GET_AUDIO_SETTING:
            returnvalue[0]=stGenSetting.g_SoundSetting.astSoundModeSetting[SOUND_MODE_STANDARD].Treble;
            returnvalue[1]=stGenSetting.g_SoundSetting.astSoundModeSetting[SOUND_MODE_STANDARD].Bass;
            returnvalue[2]=stGenSetting.g_SoundSetting.Balance;
            printf("VCP_ADJ_GET_AUDIO_SETTING:%d,%d,%d\n",stGenSetting.g_SoundSetting.astSoundModeSetting[SOUND_MODE_STANDARD].Treble,stGenSetting.g_SoundSetting.astSoundModeSetting[SOUND_MODE_STANDARD].Bass,stGenSetting.g_SoundSetting.Balance);
            break;
         case VCP_ATV_GET_TUNE_INFO:
            returnvalue[0]= msAPI_TVSetting_getpercent();//msAPI_Tuner_GetTuningProcessPercent();// percent;
            returnvalue[1]=msAPI_ATV_GetCurrentProgramNumber();
           // msAPI_ATV_GetProgramPLLData( msAPI_ATV_GetCurrentProgramNumber());
           U16 tempfrequry = msAPI_Tuner_GetCurrentChannelPLL();
            returnvalue[2]=  tempfrequry;
            returnvalue[3] = (tempfrequry>>8) & 0xFF;
            returnvalue[4] = 'T';
           break;
         case VCP_GET_SCAN_STATE:
            switch( MApp_ATV_Scan_ScanState())
            {
                case STATE_ATV_SCAN_END:
                    returnvalue[0] = TV_SCAN_END;
                    break;
                 case STATE_ATV_SCAN_INIT:
                    returnvalue[0]= TV_SCAN_INIT;
                    break;
                 case STATE_ATV_SCAN_GOTO_STANDBY:
                    returnvalue[0]= TV_SCAN_STANDBY;
                    break;
                 case STATE_ATV_SCAN_PAUSE:
                    returnvalue[0]= TV_SCAN_PAUSE;
                    break;
                 default:
                    returnvalue[0]=100;
                    break;
            }
            break;
         case VCP_ChangeInputSource:
           switch (UI_INPUT_SOURCE_TYPE)
           {
                case  UI_INPUT_SOURCE_ATV:
                    returnvalue[0] = TV_UI_INPUT_SOURCE_ATV;
                    break;
                case UI_INPUT_SOURCE_COMPONENT:
                // case UI_INPUT_SOURCE_COMPONENT2:
                    returnvalue[0] = TV_UI_INPUT_SOURCE_COMPONENT;
                    break;
                case UI_INPUT_SOURCE_AV:
               // case UI_INPUT_SOURCE_AV3:
               // case UI_INPUT_SOURCE_AV2:
                    returnvalue[0] = TV_UI_INPUT_SOURCE_AV;
                    break;
                case UI_INPUT_SOURCE_SVIDEO:
                //case UI_INPUT_SOURCE_SVIDEO2:
                    returnvalue[0] = TV_UI_INPUT_SOURCE_SVIDEO;
                    break;
                case UI_INPUT_SOURCE_RGB:
                    returnvalue[0] = TV_UI_INPUT_SOURCE_RGB;
                    break;
                case UI_INPUT_SOURCE_HDMI:
                case UI_INPUT_SOURCE_HDMI2:
                case UI_INPUT_SOURCE_HDMI3:
                //case UI_INPUT_SOURCE_HDMI4:
                    returnvalue[0] = TV_UI_INPUT_SOURCE_HDMI;
                    break;
                case UI_INPUT_SOURCE_DTV:
                    returnvalue[0] = TV_UI_INPUT_SOURCE_DTV;
                    break;
                 default:
                    returnvalue[0] = TV_UI_INPUT_SOURCE_NUMS;
                    break;
           }

            break;
    }
}

U8 msAPI_TVSetting_getpercent()
{

    U8 u8Percent;
    U32 u32UHFMAXPLL;
    U32 u32VHFLOWMINPLL;
    U32 u32TunerPLL;

    u8Percent = 0;

    u32UHFMAXPLL = UHF_MAX_PLL;

    u32VHFLOWMINPLL = VHF_LOWMIN_PLL;

    u32TunerPLL =msAPI_Tuner_GetCurrentChannelPLL();

    if ( (u32UHFMAXPLL - u32VHFLOWMINPLL) )
    {
        u8Percent = (U8)(((u32TunerPLL - u32VHFLOWMINPLL)+1)*100 / (u32UHFMAXPLL - u32VHFLOWMINPLL)) ;
    }

#if (TV_SCAN_PAL_SECAM_ONCE == 0)
    if ( _bIsLSearch == TRUE )
    {
        if ( msAPI_AUD_GetAudioStandard() == E_AUDIOSTANDARD_L )
        {
            u8Percent = u8Percent / 2;
        }
        else

        {
            u8Percent = 50 + (u8Percent / 2);
        }
    }
#endif

    return u8Percent;

}
/////////////////for test ////////////////////////
#if 0
void msAPI_TVSetting_test()
{


ST_TV_DBUS_PACKET  testsendPacket;
testsendPacket.u8_TV_tag[0] = 'T';
testsendPacket.u8_TV_tag[1] = 'V';
testsendPacket.u8_TV_tag[2] = 'S';
testsendPacket.u8_TV_tag[3] = 'T';
testsendPacket.u16_TV_ver= 1;
testsendPacket.u16_TV_type= 0x81;
testsendPacket.u32_TV_datalen= 8;
    testsendPacket.u8_TV_datacontent[0]=0;
   testsendPacket.u8_TV_datacontent[1]=0; //message length is 0
   testsendPacket.u8_TV_datacontent[2]=0;
   testsendPacket.u8_TV_datacontent[3]=0; //file name length is 0
   testsendPacket.u8_TV_datacontent[4]=0;
  testsendPacket.u8_TV_datacontent[5]=3; //command length is 3
    testsendPacket.u8_TV_datacontent[6]=0x03;  //set net bandwidth command
   testsendPacket.u8_TV_datacontent[7]=1; //var num
    testsendPacket.u8_TV_datacontent[8]=8;

U8  poutputtest[10];
poutputtest[0]= 'T';
poutputtest[1]= 'V';
poutputtest[2]=VCP_ChangeInputSource;
while(testforloop<7)
{
poutputtest[3] = testforloop;
testforloop++;
msAPI_TVSetting_SendToAPPacket((U8 *) poutputtest);

}


}
#endif
