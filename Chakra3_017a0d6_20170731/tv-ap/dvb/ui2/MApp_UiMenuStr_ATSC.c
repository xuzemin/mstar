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

#define MAPP_UI_MENUSTR_ATSC_C

#include <string.h>
#include "stdio.h"
#include "sysinfo.h"
#include "MApp_ZUI_APIcommon.h"

#include "msAPI_Timer.h"
#include "msAPI_audio.h"
#include "msAPI_Memory.h"
#include "apiXC_Sys.h"
#include "apiXC.h"
#include "apiXC_Adc.h"

#include "MApp_GlobalFunction.h"
#include "MApp_GlobalVar.h"
#include "MApp_ChannelProc_ATSC.h"
#include "MApp_VChip.h"
#include "MApp_MVDMode.h"
#include "MApp_Psip.h"
#include "MApp_RestoreToDefault.h"
#include "MApp_Audio.h"
//#include "MApp_UiMenu.h"
#include "MApp_UiMenuStr_ATSC.h"
//#include "MApp_UiMenuEpg.h"
#include "MApp_UiMenuFunc_ATSC.h"
#include "MApp_ZUI_ACTglobal.h"
#include "MApp_ZUI_APIstrings.h"

#include "OSDcp_String_EnumIndex.h"
#if ENABLE_ATSC_CHLIST_DISP_TOGETHER
#include "MApp_DataBase_ATSC.h"
#endif
#define INFO_BANNER_TIME_ALWAYS_BY_STREAM   DISABLE

#define GetDimLockOption(p, n) ((p)->u8DownloadableRatingD ## n)
#define GetDimLockOption1(n) (g_stVChipRatingInfo.u8DimVal ## n)
#define GetValuesDefined(n)    (stGenSettingVchipRegion5.stRegin5Dimension[n].u8Values_Defined)
#define GetValuesDefined1(n)    (1 << stGenSettingVchipRegion5.stRegin5Dimension[n].u8Values_Defined)

extern U32 g_u32StreamTime;
extern MS_U8 bPreviousSoundMode, bCurrentSoundMode;
extern U16* MApp_ZUI_API_GetString(U16 id);

static U8 str_add(U8* dec, U8*src)
{
    U8 count = 0;

    while (*src)
    {
        *dec = *src;

        dec++;
        src++;
        count++;
    }

    return count;
}

// ==================== Program Number Text ====================
U8* AMPMText(U8 u8Hour)
{
    U16 u16TempStringID;

    if (stGenSetting.g_SysSetting.fTimeFormat == 0) // 24-hour notation
        return (U8 *)"";
    else // 12-hour notation
    {
        if (u8Hour < 12)
            u16TempStringID= en_str_AM;
        else // hour >= 12
            u16TempStringID= en_str_PM;

         MApp_U16StringToU8String(MApp_ZUI_API_GetString(u16TempStringID),(U8*)CHAR_BUFFER,MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetString(u16TempStringID)));
         return  (U8*)CHAR_BUFFER;
    }
}

U16 GetSourceTypeTextID(void)
{
    //switch(stSystemInfo[MAIN_WINDOW].enInputSourceType)
    switch(UI_INPUT_SOURCE_TYPE)
    {
    /********************* < PC > *********************/
        case UI_INPUT_SOURCE_RGB:
            return en_str_PC;

    /********************* < TV > *********************/
        case UI_INPUT_SOURCE_ATSC:
            return en_str_TV;

    /********************* < AV > *********************/
    #if (INPUT_AV_VIDEO_COUNT == 1)
        case UI_INPUT_SOURCE_AV:
            return en_str_AV;
    #elif (INPUT_AV_VIDEO_COUNT == 2)
        case UI_INPUT_SOURCE_AV:
            return en_str_AV_1;
        case UI_INPUT_SOURCE_AV2:
            return en_str_AV_2;
    #endif

    /********************* < SV > *********************/
    #if (INPUT_SV_VIDEO_COUNT == 1)
        case UI_INPUT_SOURCE_SVIDEO:
            return en_str_SdashVideo;
    #elif (INPUT_SV_VIDEO_COUNT == 2)
        case UI_INPUT_SOURCE_SVIDEO:
            return en_str_SdashVideo_1;
        case UI_INPUT_SOURCE_SVIDEO2:
            return en_str_SdashVideo_2;
    #endif

    /********************* < YPBPR > *********************/
    #if (INPUT_YPBPR_VIDEO_COUNT == 1)
        case UI_INPUT_SOURCE_COMPONENT:
            return en_str_Component1;
    #elif (INPUT_YPBPR_VIDEO_COUNT == 2)
        case UI_INPUT_SOURCE_COMPONENT:
            return en_str_Component1;
        case UI_INPUT_SOURCE_COMPONENT2:
            return en_str_Component2;
    #elif (INPUT_YPBPR_VIDEO_COUNT == 3)
        case UI_INPUT_SOURCE_COMPONENT:
            return en_str_Component1;
        case UI_INPUT_SOURCE_COMPONENT2:
            return en_str_Component2;
        case UI_INPUT_SOURCE_COMPONENT3:
            return en_str_DVD;
    #endif

    /********************* < SCART > *********************/
    #if   (INPUT_SCART_VIDEO_COUNT == 1)
        case UI_INPUT_SOURCE_SCART:
            return en_str_SCART;
    #elif (INPUT_SCART_VIDEO_COUNT == 2)
        case UI_INPUT_SOURCE_SCART:
            return en_str_SCART;
        case UI_INPUT_SOURCE_SCART2:
            return en_str_SCART;
    #endif

    /********************* < HDMI > *********************/
    #if (ENABLE_HDMI)
      #if (INPUT_HDMI_VIDEO_COUNT >= 1)
        case UI_INPUT_SOURCE_HDMI:
          if (g_HdmiPollingStatus.bIsHDMIMode)
               return en_str_HDMI;
          else
               return en_str_DVI;
      #endif
      #if (INPUT_HDMI_VIDEO_COUNT >= 2)
        case UI_INPUT_SOURCE_HDMI2:
          if (g_HdmiPollingStatus.bIsHDMIMode)
               return en_str_HDMI2;
          else
               return en_str_DVI;
      #endif
      #if (INPUT_HDMI_VIDEO_COUNT >= 3)
        case UI_INPUT_SOURCE_HDMI3:
            return en_str_HDMI3;
      #endif
      #if (INPUT_HDMI_VIDEO_COUNT >= 4)
        case UI_INPUT_SOURCE_HDMI4:
            return en_str_HDMI4;
      #endif
    #endif

    /********************* < DTV > *********************/
        default:
            return en_str_DTV;

/********************* < STORAGE > *********************/

        // TODO: fix me, new string for dmp?
    #if ENABLE_DMP
        case UI_INPUT_SOURCE_DMP:
            return en_str_DMP;

      #if(ATSC_READY)
       #if( ENABLE_DMP_SWITCH )
        case UI_INPUT_SOURCE_DMP1:
            return en_str_USB1;
        case UI_INPUT_SOURCE_DMP2:
            return en_str_USB2;
       #endif
      #endif

    #endif
    }
}


U8* CurProgramNumberText(void)
{
    if(IsDTVInUse() || IsATVInUse())
    {
    #if ENABLE_ATSC_CHLIST_DISP_TOGETHER
        if (MApp_ChanProc_IsCurProgIndexAir())
        {
            MApp_DB_ATSC_InitBaseAddr(ANT_AIR);
            MApp_UiMenuFunc_ConvertProgramNumber2Str(&MApp_ChanProc_GetChannelPointer(VIR_CH_IDX_AIR(MApp_ChanProc_GetCurProgIndex()))->stVirtualChNum, au8Section);
        }
        else
        {
            MApp_DB_ATSC_InitBaseAddr(ANT_CATV);
            MApp_UiMenuFunc_ConvertProgramNumber2Str(&MApp_ChanProc_GetChannelPointer(VIR_CH_IDX_CATV(MApp_ChanProc_GetCurCableProgIndex()))->stVirtualChNum, au8Section);
        }
        MApp_DB_ATSC_InitBaseAddr((EN_ANT_TYPE)ANT_TYPE);
    #else
        MApp_UiMenuFunc_ConvertProgramNumber2Str(&MApp_ChanProc_GetChannelPointer(VIR_CH_IDX(MApp_ChanProc_GetCurProgIndex()))->stVirtualChNum, au8Section);
    #endif
        return au8Section;
    }
    else
    {
        return (U8 *)"";
    }
}

LPTSTR CurProgramNameText(void)
{
    CHAR_BUFFER[0] = 0;

    if(IsDTVInUse() || IsATVInUse())
    {
        U8 *str;
        str = MApp_ChanProc_GetCurChannelPointer()->acServiceName;
        if(IsATVInUse())
        {
            U16 u16Len =  (U16)strlen((char*)str);

            if(u16Len)
                return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, str, u16Len);
        }
        else
        {
        #if 0
            int i;
            for(i=0;i<MAX_LENGTH_OF_SERVICE_NAME;i++)
            {
                printf("\r\n %c", *(str+i));
            }
        #endif

            MApp_ZUI_API_StringBufferUTF16toU16(CHAR_BUFFER, str, MAX_LENGTH_OF_SERVICE_NAME/2+1);

            CHAR_BUFFER[MAX_LENGTH_OF_SERVICE_NAME/2] = 0;
        }
    }

    return CHAR_BUFFER;
}


U16 CurProgramScrambleStatusTextID(void)
{
#if ENABLE_ATSC_CHLIST_DISP_TOGETHER
    if (MApp_ChanProc_IsCurProgIndexAir())
    {
        MApp_DB_ATSC_InitBaseAddr(ANT_AIR);
        if ( ((MApp_ChanProc_GetChannelPointer(VIR_CH_IDX_AIR(MApp_ChanProc_GetCurProgIndex()))->u16ScrambleChStatus & SCRAMBLE_AUDIO) &&
          (MApp_ChanProc_GetChannelPointer(VIR_CH_IDX_AIR(MApp_ChanProc_GetCurProgIndex()))->u16ScrambleChStatus & SCRAMBLE_VIDEO) )
          ||(MApp_ChanProc_GetChannelPointer(VIR_CH_IDX_AIR(MApp_ChanProc_GetCurProgIndex()))->fIsScrambleCh) )
        {
            MApp_DB_ATSC_InitBaseAddr((EN_ANT_TYPE)ANT_TYPE);
            return en_str_Scrambled;
        }
    else if (MApp_ChanProc_GetChannelPointer(VIR_CH_IDX_AIR(MApp_ChanProc_GetCurProgIndex()))->u16ScrambleChStatus & SCRAMBLE_AUDIO)
        {
            MApp_DB_ATSC_InitBaseAddr((EN_ANT_TYPE)ANT_TYPE);
            return en_str_Audio_Scrambled;
        }
    else if (MApp_ChanProc_GetChannelPointer(VIR_CH_IDX_AIR(MApp_ChanProc_GetCurProgIndex()))->u16ScrambleChStatus & SCRAMBLE_VIDEO)
        {
            MApp_DB_ATSC_InitBaseAddr((EN_ANT_TYPE)ANT_TYPE);
            return en_str_Video_Scrambled;
        }
    else
        {
            MApp_DB_ATSC_InitBaseAddr((EN_ANT_TYPE)ANT_TYPE);
            return en_str_FTA;
        }
    }
    else
    {
        MApp_DB_ATSC_InitBaseAddr(ANT_CATV);
        pstVirtualCh = MApp_ChanProc_GetChannelPointer(VIR_CH_IDX_CATV(MApp_ChanProc_GetCurCableProgIndex()));
        if ( ((MApp_ChanProc_GetChannelPointer(VIR_CH_IDX_CATV(MApp_ChanProc_GetCurCableProgIndex()))->u16ScrambleChStatus & SCRAMBLE_AUDIO) &&
          (MApp_ChanProc_GetChannelPointer(VIR_CH_IDX_CATV(MApp_ChanProc_GetCurCableProgIndex()))->u16ScrambleChStatus & SCRAMBLE_VIDEO) )
          ||(MApp_ChanProc_GetChannelPointer(VIR_CH_IDX_CATV(MApp_ChanProc_GetCurCableProgIndex()))->fIsScrambleCh) )
        {
            MApp_DB_ATSC_InitBaseAddr((EN_ANT_TYPE)ANT_TYPE);
            return en_str_Scrambled;
        }
    else if (MApp_ChanProc_GetChannelPointer(VIR_CH_IDX_CATV(MApp_ChanProc_GetCurCableProgIndex()))->u16ScrambleChStatus & SCRAMBLE_AUDIO)
        {
            MApp_DB_ATSC_InitBaseAddr((EN_ANT_TYPE)ANT_TYPE);
            return en_str_Audio_Scrambled;
        }
    else if (MApp_ChanProc_GetChannelPointer(VIR_CH_IDX_CATV(MApp_ChanProc_GetCurCableProgIndex()))->u16ScrambleChStatus & SCRAMBLE_VIDEO)
        {
            MApp_DB_ATSC_InitBaseAddr((EN_ANT_TYPE)ANT_TYPE);
            return en_str_Video_Scrambled;
        }
    else
        {
            MApp_DB_ATSC_InitBaseAddr((EN_ANT_TYPE)ANT_TYPE);
            return en_str_FTA;
        }
    }
#else
    if ( ((MApp_ChanProc_GetChannelPointer(VIR_CH_IDX(MApp_ChanProc_GetCurProgIndex()))->u16ScrambleChStatus & SCRAMBLE_AUDIO) &&
          (MApp_ChanProc_GetChannelPointer(VIR_CH_IDX(MApp_ChanProc_GetCurProgIndex()))->u16ScrambleChStatus & SCRAMBLE_VIDEO) )
          ||(MApp_ChanProc_GetChannelPointer(VIR_CH_IDX(MApp_ChanProc_GetCurProgIndex()))->fIsScrambleCh) )
        return en_str_Scrambled;
    else if (MApp_ChanProc_GetChannelPointer(VIR_CH_IDX(MApp_ChanProc_GetCurProgIndex()))->u16ScrambleChStatus & SCRAMBLE_AUDIO)
        return en_str_Audio_Scrambled;
    else if (MApp_ChanProc_GetChannelPointer(VIR_CH_IDX(MApp_ChanProc_GetCurProgIndex()))->u16ScrambleChStatus & SCRAMBLE_VIDEO)
        return en_str_Video_Scrambled;
    else
        return en_str_FTA;
#endif
}

U8* AudSoundModeText(void)
{
    switch(MApp_GetMenuLanguage())
    {
        case LANGUAGE_ENGLISH:
        {
            switch(stGenSetting.g_SoundSetting.enSoundAudioChannel)
            {
                case 0:
                    return (U8 *)"L | R";
                case 1:
                    return (U8 *)"L | L";
                case 2:
                    return (U8 *)"R | R";
                default:
                    break;
            }
        }
        break;

        case LANGUAGE_FRENCH:
        {
            switch(stGenSetting.g_SoundSetting.enSoundAudioChannel)
            {
                case 0:
                    return (U8 *)"G+D";
                case 1:
                    return (U8 *)"G+G";
                case 2:
                    return (U8 *)"D+D";
                default:
                    break;
            }
        }
        break;

        case LANGUAGE_SPANISH:
        {
            switch(stGenSetting.g_SoundSetting.enSoundAudioChannel)
            {
                case 0:
                    return (U8 *)"I+D";
                case 1:
                    return (U8 *)"I+I";
                case 2:
                    return (U8 *)"D+D";
                default:
                    break;
            }
        }
        break;

        default:
            break;
    }
    return (U8 *)"";
}

U8* ScrambleText(void)
{
    U16 u16TempStringID;

    if(pstVirtualCh->fIsScrambleCh)
       u16TempStringID = en_str_Scrambled;
    else
       u16TempStringID = en_str_FTA;

    MApp_U16StringToU8String(MApp_ZUI_API_GetString(u16TempStringID),(U8*)CHAR_BUFFER,MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetString(u16TempStringID)));
    return  (U8*)CHAR_BUFFER;
}

U8* DtvReslutionTypeText(void)
{
    U8 tempCount;
    tempCount=MApp_GetNoOfDigit(gstVidStatus.u16HorSize);
    MApp_UlongToString(gstVidStatus.u16HorSize, (U8*)CHAR_BUFFER, tempCount);
    ((U8*)CHAR_BUFFER)[tempCount++]='x';
    MApp_UlongToString(gstVidStatus.u16VerSize, ((U8*)CHAR_BUFFER)+tempCount, MApp_GetNoOfDigit(gstVidStatus.u16VerSize));
    return (U8*)CHAR_BUFFER;
}

U16 CCInfoTextID(void)
{
    if(MApp_IsSrcHasSignal(MAIN_WINDOW))
    {
        if(MApp_UiMenuFunc_IsCCEnable())
        {
            switch(stGenSetting.g_CaptionSetting.u8CaptionServiceMode)
            {
                case CAPTIONMENU_SERVICE_OFF:
                    return en_str_CC_Off;

                case CAPTIONMENU_SERVICE_CC1:
                    return en_str_CC_1;

                case CAPTIONMENU_SERVICE_CC2:
                    return en_str_CC_2;

                case CAPTIONMENU_SERVICE_CC3:
                    return en_str_CC_3;

                case CAPTIONMENU_SERVICE_CC4:
                    return en_str_CC_4;

                case CAPTIONMENU_SERVICE_TEXT1:
                    return en_str_Text1;

                case CAPTIONMENU_SERVICE_TEXT2:
                    return en_str_Text2;

                case CAPTIONMENU_SERVICE_TEXT3:
                    return en_str_Text3;

                case CAPTIONMENU_SERVICE_TEXT4:
                    return en_str_Text4;

                case CAPTIONMENU_SERVICE_SERVICE1:
                    return en_str_Service1;

                case CAPTIONMENU_SERVICE_SERVICE2:
                    return en_str_Service2;

                case CAPTIONMENU_SERVICE_SERVICE3:
                    return en_str_Service3;

                case CAPTIONMENU_SERVICE_SERVICE4:
                    return en_str_Service4;

                case CAPTIONMENU_SERVICE_SERVICE5:
                    return en_str_Service5;

                case CAPTIONMENU_SERVICE_SERVICE6:
                    return en_str_Service6;
                default:
                    return en_str_CC_Off;
            }
        }
        else
        {
            return  Empty;
        }
    }
    else
    {
        return  Empty;
    }
}

void MApp_UiMenuStr_GetRRT5String(MS_EPG_RATING *pEpgRating, U8 *pu8Str, U8 buf_size)
{
    U8 i;
    BOOLEAN precede_common;

    if (!pEpgRating || !pu8Str || buf_size <= 2)
        return;

    pu8Str[0] = '\0';
    // for safety
    pu8Str[buf_size - 1] = '\0';
    pu8Str[buf_size - 2] = '\0';
    buf_size -= 2;

    if (!pEpgRating->fRatingRxIsOK)
        return;

    precede_common = FALSE;
    printf("(%d)(%s)\n", __LINE__, __func__);

    if (GetDimLockOption(pEpgRating, 1))
    {
        for (i = 0; i < GetValuesDefined(0); ++i)
        {
            if (GETBIT(GetDimLockOption(pEpgRating, 1), i))
            {
                //if (precede_common&& stGenSetting.g_VchipRegion5.stRegin5Dimension[0].stRatingText[i].u8Rating_Text[0])
                if (precede_common&& stGenSettingVchipRegion5.stRegin5Dimension[0].stRatingText[i][0])
                {
                    //strncat((S8*)pu8Str, ", ", buf_size - strlen((S8 *)pu8Str));
                    strncat((char*)pu8Str, ", ", buf_size - strlen((char *)pu8Str));
                }
                //strncat((S8*)pu8Str, (S8*)stGenSetting.g_VchipRegion5.stRegin5Dimension[0].stRatingText[i].u8Rating_Text, buf_size - strlen((S8 *)pu8Str));
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[0].stRatingText[i], buf_size - strlen((char *)pu8Str));
                precede_common = TRUE;
            }
        }
    }

    if (GetDimLockOption(pEpgRating, 2))
    {
        for (i = 0; i < GetValuesDefined(1); ++i)
        {
            if (GETBIT(GetDimLockOption(pEpgRating, 2), i))
            {
                //if (precede_common && stGenSetting.g_VchipRegion5.stRegin5Dimension[1].stRatingText[i].u8Rating_Text[0])
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[1].stRatingText[i][0])
                {
                    //strncat((S8*)pu8Str, ", ", buf_size - strlen((S8 *)pu8Str));
                    strncat((char*)pu8Str, ", ", buf_size - strlen((char *)pu8Str));
                }
                //strncat((S8*)pu8Str, (S8*)stGenSetting.g_VchipRegion5.stRegin5Dimension[1].stRatingText[i].u8Rating_Text, buf_size - strlen((S8 *)pu8Str));
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[1].stRatingText[i], buf_size - strlen((char *)pu8Str));
                precede_common = TRUE;
            }
        }
    }

    if (GetDimLockOption(pEpgRating, 3))
    {
        for (i = 0; i < GetValuesDefined(2); ++i)
        {
            if (GETBIT(GetDimLockOption(pEpgRating, 3), i))
            {
                //if (precede_common && stGenSetting.g_VchipRegion5.stRegin5Dimension[2].stRatingText[i].u8Rating_Text[0])
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[2].stRatingText[i][0])
                {
                    //strncat((S8*)pu8Str, ", ", buf_size - strlen((S8 *)pu8Str));
                    strncat((char*)pu8Str, ", ", buf_size - strlen((char *)pu8Str));
                }
                //strncat((S8*)pu8Str, (S8*)stGenSetting.g_VchipRegion5.stRegin5Dimension[2].stRatingText[i].u8Rating_Text, buf_size - strlen((S8 *)pu8Str));
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[2].stRatingText[i], buf_size - strlen((char *)pu8Str));
                precede_common = TRUE;
            }
        }
    }

    if (GetDimLockOption(pEpgRating, 4))
    {
        for (i = 0; i < GetValuesDefined(3); ++i)
        {
            if (GETBIT(GetDimLockOption(pEpgRating, 4), i))
            {
//                if (precede_common && stGenSetting.g_VchipRegion5.stRegin5Dimension[3].stRatingText[i].u8Rating_Text[0])
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[3].stRatingText[i][0])
                {
                    //strncat((S8*)pu8Str, ", ", buf_size - strlen((S8 *)pu8Str));
                    strncat((char*)pu8Str, ", ", buf_size - strlen((char *)pu8Str));
                }
                //strncat((S8*)pu8Str, (S8*)stGenSetting.g_VchipRegion5.stRegin5Dimension[3].stRatingText[i].u8Rating_Text, buf_size - strlen((S8 *)pu8Str));
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[3].stRatingText[i], buf_size - strlen((char *)pu8Str));
                precede_common = TRUE;
            }
        }
    }

    if (GetDimLockOption(pEpgRating, 5))
    {
        for (i = 0; i < GetValuesDefined(4); ++i)
        {
            if (GETBIT(GetDimLockOption(pEpgRating, 5), i))
            {
                //if (precede_common && stGenSetting.g_VchipRegion5.stRegin5Dimension[4].stRatingText[i].u8Rating_Text[0])
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[4].stRatingText[i][0])
                {
                   //strncat((S8*)pu8Str, ", ", buf_size - strlen((S8 *)pu8Str));
                    strncat((char*)pu8Str, ", ", buf_size - strlen((char *)pu8Str));
                }
                //strncat((S8*)pu8Str, (S8*)stGenSetting.g_VchipRegion5.stRegin5Dimension[4].stRatingText[i].u8Rating_Text, buf_size - strlen((S8 *)pu8Str));
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[4].stRatingText[i], buf_size - strlen((char *)pu8Str));
                precede_common = TRUE;
            }
        }
    }

    if (GetDimLockOption(pEpgRating, 6))
    {
        for (i = 0; i < GetValuesDefined(5); ++i)
        {
            if (GETBIT(GetDimLockOption(pEpgRating, 6), i))
            {
                //if (precede_common && stGenSetting.g_VchipRegion5.stRegin5Dimension[5].stRatingText[i].u8Rating_Text[0])
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[5].stRatingText[i][0])
                {
                    //strncat((S8*)pu8Str, ", ", buf_size - strlen((S8 *)pu8Str));
                    strncat((char*)pu8Str, ", ", buf_size - strlen((char *)pu8Str));
                }
                //strncat((S8*)pu8Str, (S8*)stGenSetting.g_VchipRegion5.stRegin5Dimension[5].stRatingText[i].u8Rating_Text, buf_size - strlen((S8 *)pu8Str));
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[5].stRatingText[i], buf_size - strlen((char *)pu8Str));
                precede_common = TRUE;
            }
        }
    }

    if (GetDimLockOption(pEpgRating, 7))
    {
        for (i = 0; i < GetValuesDefined(6); ++i)
        {
            if (GETBIT(GetDimLockOption(pEpgRating, 7), i))
            {
                //if (precede_common && stGenSetting.g_VchipRegion5.stRegin5Dimension[6].stRatingText[i].u8Rating_Text[0])
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[6].stRatingText[i][0])
                {
                    //strncat((S8*)pu8Str, ", ", buf_size - strlen((S8 *)pu8Str));
                    strncat((char*)pu8Str, ", ", buf_size - strlen((char *)pu8Str));
                }
                //strncat((S8*)pu8Str, (S8*)stGenSetting.g_VchipRegion5.stRegin5Dimension[6].stRatingText[i].u8Rating_Text, buf_size - strlen((S8 *)pu8Str));
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[6].stRatingText[i], buf_size - strlen((char *)pu8Str));
                precede_common = TRUE;
            }
        }
    }

    if (GetDimLockOption(pEpgRating, 8))
    {
        for (i = 0; i < GetValuesDefined(7); ++i)
        {
            if (GETBIT(GetDimLockOption(pEpgRating, 8), i))
            {
                //if (precede_common && stGenSetting.g_VchipRegion5.stRegin5Dimension[7].stRatingText[i][0])
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[7].stRatingText[i][0])
                {
                    //strncat((S8*)pu8Str, ", ", buf_size - strlen((S8 *)pu8Str));
                    strncat((char*)pu8Str, ", ", buf_size - strlen((char *)pu8Str));
                }
                //strncat((S8*)pu8Str, (S8*)stGenSetting.g_VchipRegion5.stRegin5Dimension[7].stRatingText[i].u8Rating_Text, buf_size - strlen((S8 *)pu8Str));
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[7].stRatingText[i], buf_size - strlen((char *)pu8Str));
                precede_common = TRUE;
            }
        }
    }

    if (GetDimLockOption(pEpgRating, 9))
    {
        for (i = 0; i < GetValuesDefined(8); ++i)
        {
            if (GETBIT(GetDimLockOption(pEpgRating, 9), i))
            {
                //if (precede_common && stGenSetting.g_VchipRegion5.stRegin5Dimension[8].stRatingText[i].u8Rating_Text[0])
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[8].stRatingText[i][0])
                {
                    //strncat((S8*)pu8Str, ", ", buf_size - strlen((S8 *)pu8Str));
                    strncat((char*)pu8Str, ", ", buf_size - strlen((char *)pu8Str));
                }
                //strncat((S8*)pu8Str, (S8*)stGenSetting.g_VchipRegion5.stRegin5Dimension[8].stRatingText[i].u8Rating_Text, buf_size - strlen((S8 *)pu8Str));
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[8].stRatingText[i], buf_size - strlen((char *)pu8Str));
                precede_common = TRUE;
            }
        }
    }

    if (GetDimLockOption(pEpgRating, 10))
    {
        for (i = 0; i < GetValuesDefined(9); ++i)
        {
            if (GETBIT(GetDimLockOption(pEpgRating, 10), i))
            {
                //if (precede_common && stGenSetting.g_VchipRegion5.stRegin5Dimension[9].stRatingText[i].u8Rating_Text[0])
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[9].stRatingText[i][0])
                {
                    //strncat((S8*)pu8Str, ", ", buf_size - strlen((S8 *)pu8Str));
                    strncat((char*)pu8Str, ", ", buf_size - strlen((char *)pu8Str));
                }
                //strncat((S8*)pu8Str, (S8*)stGenSetting.g_VchipRegion5.stRegin5Dimension[9].stRatingText[i].u8Rating_Text, buf_size - strlen((S8 *)pu8Str));
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[9].stRatingText[i], buf_size - strlen((char *)pu8Str));
                precede_common = TRUE;
            }
        }
    }
}

void UiMenuStr_GetVChip2RatingString(U8 *pu8Str)
{
#if (ENABLE_PARSE_SAME_DIMENSION_IN_RRT5_CAD)
    S8 i;
    BOOLEAN precede_common = FALSE;

    pu8Str[0] = '\0';

    if (GetDimLockOption1(0))
    {
        //for (i = 0; i < GetValuesDefined(0); ++i)
        for (i = GetValuesDefined(0); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(0), i))
            {
                if (precede_common&& stGenSettingVchipRegion5.stRegin5Dimension[0].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[0].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[0].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(1))
    {
        //for (i = 0; i < GetValuesDefined(1); ++i)
        for (i = GetValuesDefined(1); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(1), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[1].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[1].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[1].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(2))
    {
        //for (i = 0; i < GetValuesDefined(2); ++i)
        for (i = GetValuesDefined(2); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(2), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[2].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[2].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[2].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(3))
    {
        //for (i = 0; i < GetValuesDefined(3); ++i)
        for (i = GetValuesDefined(3); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(3), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[3].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[3].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[3].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(4))
    {
        //for (i = 0; i < GetValuesDefined(4); ++i)
        for (i = GetValuesDefined(4); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(4), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[4].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[4].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[4].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(5))
    {
        //for (i = 0; i < GetValuesDefined(5); ++i)
        for (i = GetValuesDefined(5); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(5), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[5].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[5].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[5].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(6))
    {
        //for (i = 0; i < GetValuesDefined(6); ++i)
        for (i = GetValuesDefined(6); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(6), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[6].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[6].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[6].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(7))
    {
        //for (i = 0; i < GetValuesDefined(7); ++i)
        for (i = GetValuesDefined(7); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(7), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[7].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[7].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[7].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(8))
    {
        //for (i = 0; i < GetValuesDefined(8); ++i)
        for (i = GetValuesDefined(8); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(8), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[8].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[8].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[8].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(9))
    {
        //for (i = 0; i < GetValuesDefined(9); ++i)
        for (i = GetValuesDefined(9); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(9), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[9].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[9].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[9].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

  #if (ENABLE_MAX_RRT_DIMENSION_NUMBER)
    if (GetDimLockOption1(10))
    {
        for (i = GetValuesDefined(10); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(10), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[10].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[10].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[10].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(11))
    {
        for (i = GetValuesDefined(11); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(11), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[11].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[11].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[11].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(12))
    {
        for (i = GetValuesDefined(12); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(12), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[12].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[12].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[12].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }


    if (GetDimLockOption1(13))
    {
        for (i = GetValuesDefined(13); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(13), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[13].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[13].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[13].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(14))
    {
        for (i = GetValuesDefined(14); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(14), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[14].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[14].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[14].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(15))
    {
        for (i = GetValuesDefined(15); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(15), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[15].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[15].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[15].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(16))
    {
        for (i = GetValuesDefined(16); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(16), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[16].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[16].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[16].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(17))
    {
        for (i = GetValuesDefined(17); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(17), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[17].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[17].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[17].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(18))
    {
        for (i = GetValuesDefined(18); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(18), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[18].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[18].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[18].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(19))
    {
        for (i = GetValuesDefined(19); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(19), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[19].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[19].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[19].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(20))
    {
        for (i = GetValuesDefined(20); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(20), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[20].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[20].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[20].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(21))
    {
        for (i = GetValuesDefined(21); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(21), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[21].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[21].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[21].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(22))
    {
        for (i = GetValuesDefined(22); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(22), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[22].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[22].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[22].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(23))
    {
        for (i = GetValuesDefined(23); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(23), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[23].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[23].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[23].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(24))
    {
        for (i = GetValuesDefined(24); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(24), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[24].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[24].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[24].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(25))
    {
        for (i = GetValuesDefined(25); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(25), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[25].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[25].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[25].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(26))
    {
        for (i = GetValuesDefined(26); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(26), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[26].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[26].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[26].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(27))
    {
        for (i = GetValuesDefined(27); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(27), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[27].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[27].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[27].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(28))
    {
        for (i = GetValuesDefined(28); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(28), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[28].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[28].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[28].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(29))
    {
        for (i = GetValuesDefined(29); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(29), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[29].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[29].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[29].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }


    if (GetDimLockOption1(30))
    {
        for (i = GetValuesDefined(30); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(30), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[30].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[30].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[30].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(31))
    {
        for (i = GetValuesDefined(31); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(31), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[31].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[31].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[31].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(32))
    {
        for (i = GetValuesDefined(32); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(32), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[32].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[32].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[32].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(33))
    {
        for (i = GetValuesDefined(33); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(33), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[33].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[33].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[33].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(34))
    {
        for (i = GetValuesDefined(34); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(34), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[34].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[34].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[34].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(35))
    {
        for (i = GetValuesDefined(35); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(35), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[35].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[35].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[35].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }


    if (GetDimLockOption1(36))
    {
        for (i = GetValuesDefined(36); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(36), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[36].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[36].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[36].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(37))
    {
        for (i = GetValuesDefined(37); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(37), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[37].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[37].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[37].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(38))
    {
        for (i = GetValuesDefined(38); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(38), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[38].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[38].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[38].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(39))
    {
        for (i = GetValuesDefined(39); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(39), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[39].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[39].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[39].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }

    if (GetDimLockOption1(40))
    {
        for (i = GetValuesDefined(40); i >= 0; --i)
        {
            if (GETBIT(GetDimLockOption1(40), i))
            {
                if (precede_common && stGenSettingVchipRegion5.stRegin5Dimension[40].stRatingText[i][0])
                {
                    strcat((char*)pu8Str, ", ");
                }
                strncat((char*)pu8Str, (char*)stGenSettingVchipRegion5.stRegin5Dimension[40].stRatingText[i], strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[40].stRatingText[i])));
                precede_common = TRUE;
                break;
            }
        }
    }
  #endif

#else

    U8 u8Dim, u8Val;
    BOOLEAN bSkip;

    pu8Str[0] = 0;

    u8Dim = 0;
    u8Val = 0;
    bSkip = FALSE;

    if (g_stVChipRatingInfo.u8DimVal0 && !bSkip)
    {
        u8Dim = 0;
        u8Val = g_stVChipRatingInfo.u8DimVal0;
        if ((stGenSettingVchipRegion5.stRegin5Dimension[0].u32CurrentOption)>>(g_stVChipRatingInfo.u8DimVal0-1)&0x01)
            bSkip = TRUE;
    }
    if (g_stVChipRatingInfo.u8DimVal1 && !bSkip)
    {
        u8Dim = 1;
        u8Val = g_stVChipRatingInfo.u8DimVal1;
        if ((stGenSettingVchipRegion5.stRegin5Dimension[1].u32CurrentOption)>>(g_stVChipRatingInfo.u8DimVal1-1)&0x01)
            bSkip = TRUE;
    }
    if (g_stVChipRatingInfo.u8DimVal2 && !bSkip)
    {
        u8Dim = 2;
        u8Val = g_stVChipRatingInfo.u8DimVal2;
        if ((stGenSettingVchipRegion5.stRegin5Dimension[2].u32CurrentOption)>>(g_stVChipRatingInfo.u8DimVal2-1)&0x01)
            bSkip = TRUE;
    }
    if (g_stVChipRatingInfo.u8DimVal3 && !bSkip)
    {
        u8Dim = 3;
        u8Val = g_stVChipRatingInfo.u8DimVal3;
        if ((stGenSettingVchipRegion5.stRegin5Dimension[3].u32CurrentOption)>>(g_stVChipRatingInfo.u8DimVal3-1)&0x01)
             bSkip = TRUE;
   }
    if (g_stVChipRatingInfo.u8DimVal4 && !bSkip)
    {
        u8Dim = 4;
        u8Val = g_stVChipRatingInfo.u8DimVal4;
        if ((stGenSettingVchipRegion5.stRegin5Dimension[4].u32CurrentOption)>>(g_stVChipRatingInfo.u8DimVal4-1)&0x01)
            bSkip = TRUE;
    }
    if (g_stVChipRatingInfo.u8DimVal5 && !bSkip)
    {
        u8Dim = 5;
        u8Val = g_stVChipRatingInfo.u8DimVal5;
        if ((stGenSettingVchipRegion5.stRegin5Dimension[5].u32CurrentOption)>>(g_stVChipRatingInfo.u8DimVal5-1)&0x01)
            bSkip = TRUE;
    }
    if (g_stVChipRatingInfo.u8DimVal6 && !bSkip)
    {
        u8Dim = 6;
        u8Val = g_stVChipRatingInfo.u8DimVal6;
        if ((stGenSettingVchipRegion5.stRegin5Dimension[6].u32CurrentOption)>>(g_stVChipRatingInfo.u8DimVal6-1)&0x01)
             bSkip = TRUE;
   }
    if (g_stVChipRatingInfo.u8DimVal7 && !bSkip)
    {
        u8Dim = 7;
        u8Val = g_stVChipRatingInfo.u8DimVal7;
        if ((stGenSettingVchipRegion5.stRegin5Dimension[7].u32CurrentOption)>>(g_stVChipRatingInfo.u8DimVal7-1)&0x01)
            bSkip = TRUE;
    }
    if (g_stVChipRatingInfo.u8DimVal8 && !bSkip)
    {
        u8Dim = 8;
        u8Val = g_stVChipRatingInfo.u8DimVal8;
        if ((stGenSettingVchipRegion5.stRegin5Dimension[8].u32CurrentOption)>>(g_stVChipRatingInfo.u8DimVal8-1)&0x01)
            bSkip = TRUE;
    }
    if (g_stVChipRatingInfo.u8DimVal9 && !bSkip)
    {
        u8Dim = 9;
        u8Val = g_stVChipRatingInfo.u8DimVal9;
        if ((stGenSettingVchipRegion5.stRegin5Dimension[9].u32CurrentOption)>>(g_stVChipRatingInfo.u8DimVal9-1)&0x01)
            bSkip = TRUE;
    }

    if(u8Val>0)
    {
        strncpy((char *)pu8Str, (char *)(stGenSettingVchipRegion5.stRegin5Dimension[u8Dim].stRatingText[u8Val-1]), strlen((char *)(stGenSettingVchipRegion5.stRegin5Dimension[u8Dim].stRatingText[u8Val-1])));
    }

#endif // #if (ENABLE_PARSE_SAME_DIMENSION_IN_RRT5_CAD)
}

#define _VChip2_ TRUE
static void UiMenuStr_GetRatingString(U8 *pu8Str)
{
    U8 u8Strlen;
    BOOLEAN bExtra = TRUE;

    if (!pu8Str)
        return;

    pu8Str[0] = 0;
    u8Strlen = 0;

    if(!IsVBISrcInUse() || g_stVChipRatingInfo.RatingType == VCHIP_RATING_TYPE_NONE)
    {
        return;
    }

    if (g_stVChipRatingInfo.RatingType == VCHIP_RATING_TYPE_REG5)
    {
        if (bExtra)
        {
            u8Strlen = UiMenuStr_GetVChip1RatingString(pu8Str);
            pu8Str += u8Strlen;
        #if _VChip2_
            if (stGenSettingVchipRegion5.u8NoDimension != 0)
            {
                if ( (g_stVChipRatingInfo.u8DimVal0 > 0 && (g_stVChipRatingInfo.u8DimVal0 < GetValuesDefined1(0)))
                   ||(g_stVChipRatingInfo.u8DimVal1 > 0 && (g_stVChipRatingInfo.u8DimVal1 < GetValuesDefined1(1)))
                   ||(g_stVChipRatingInfo.u8DimVal2 > 0 && (g_stVChipRatingInfo.u8DimVal2 < GetValuesDefined1(2)))
                   ||(g_stVChipRatingInfo.u8DimVal3 > 0 && (g_stVChipRatingInfo.u8DimVal3 < GetValuesDefined1(3)))
                   ||(g_stVChipRatingInfo.u8DimVal4 > 0 && (g_stVChipRatingInfo.u8DimVal4 < GetValuesDefined1(4)))
                   ||(g_stVChipRatingInfo.u8DimVal5 > 0 && (g_stVChipRatingInfo.u8DimVal5 < GetValuesDefined1(5)))
                   ||(g_stVChipRatingInfo.u8DimVal6 > 0 && (g_stVChipRatingInfo.u8DimVal6 < GetValuesDefined1(6)))
                   ||(g_stVChipRatingInfo.u8DimVal7 > 0 && (g_stVChipRatingInfo.u8DimVal7 < GetValuesDefined1(7)))
                   ||(g_stVChipRatingInfo.u8DimVal8 > 0 && (g_stVChipRatingInfo.u8DimVal8 < GetValuesDefined1(8)))
                   ||(g_stVChipRatingInfo.u8DimVal9 > 0 && (g_stVChipRatingInfo.u8DimVal9 < GetValuesDefined1(9)))
                  #if (ENABLE_MAX_RRT_DIMENSION_NUMBER)
                   ||(g_stVChipRatingInfo.u8DimVal10 > 0 && (g_stVChipRatingInfo.u8DimVal1 < GetValuesDefined1(10)))
                   ||(g_stVChipRatingInfo.u8DimVal11 > 0 && (g_stVChipRatingInfo.u8DimVal2 < GetValuesDefined1(11)))
                   ||(g_stVChipRatingInfo.u8DimVal12 > 0 && (g_stVChipRatingInfo.u8DimVal3 < GetValuesDefined1(12)))
                   ||(g_stVChipRatingInfo.u8DimVal13 > 0 && (g_stVChipRatingInfo.u8DimVal4 < GetValuesDefined1(13)))
                   ||(g_stVChipRatingInfo.u8DimVal14 > 0 && (g_stVChipRatingInfo.u8DimVal5 < GetValuesDefined1(14)))
                   ||(g_stVChipRatingInfo.u8DimVal15 > 0 && (g_stVChipRatingInfo.u8DimVal6 < GetValuesDefined1(15)))
                   ||(g_stVChipRatingInfo.u8DimVal16 > 0 && (g_stVChipRatingInfo.u8DimVal7 < GetValuesDefined1(16)))
                   ||(g_stVChipRatingInfo.u8DimVal17 > 0 && (g_stVChipRatingInfo.u8DimVal8 < GetValuesDefined1(17)))
                   ||(g_stVChipRatingInfo.u8DimVal18 > 0 && (g_stVChipRatingInfo.u8DimVal9 < GetValuesDefined1(18)))
                   ||(g_stVChipRatingInfo.u8DimVal19 > 0 && (g_stVChipRatingInfo.u8DimVal9 < GetValuesDefined1(19)))
                   ||(g_stVChipRatingInfo.u8DimVal20 > 0 && (g_stVChipRatingInfo.u8DimVal1 < GetValuesDefined1(20)))
                   ||(g_stVChipRatingInfo.u8DimVal21 > 0 && (g_stVChipRatingInfo.u8DimVal2 < GetValuesDefined1(21)))
                   ||(g_stVChipRatingInfo.u8DimVal22 > 0 && (g_stVChipRatingInfo.u8DimVal3 < GetValuesDefined1(22)))
                   ||(g_stVChipRatingInfo.u8DimVal23 > 0 && (g_stVChipRatingInfo.u8DimVal4 < GetValuesDefined1(23)))
                   ||(g_stVChipRatingInfo.u8DimVal24 > 0 && (g_stVChipRatingInfo.u8DimVal5 < GetValuesDefined1(24)))
                   ||(g_stVChipRatingInfo.u8DimVal25 > 0 && (g_stVChipRatingInfo.u8DimVal6 < GetValuesDefined1(25)))
                   ||(g_stVChipRatingInfo.u8DimVal26 > 0 && (g_stVChipRatingInfo.u8DimVal7 < GetValuesDefined1(26)))
                   ||(g_stVChipRatingInfo.u8DimVal27 > 0 && (g_stVChipRatingInfo.u8DimVal8 < GetValuesDefined1(27)))
                   ||(g_stVChipRatingInfo.u8DimVal28 > 0 && (g_stVChipRatingInfo.u8DimVal9 < GetValuesDefined1(28)))
                   ||(g_stVChipRatingInfo.u8DimVal29 > 0 && (g_stVChipRatingInfo.u8DimVal9 < GetValuesDefined1(29)))
                   ||(g_stVChipRatingInfo.u8DimVal30 > 0 && (g_stVChipRatingInfo.u8DimVal1 < GetValuesDefined1(30)))
                   ||(g_stVChipRatingInfo.u8DimVal31 > 0 && (g_stVChipRatingInfo.u8DimVal2 < GetValuesDefined1(31)))
                   ||(g_stVChipRatingInfo.u8DimVal32 > 0 && (g_stVChipRatingInfo.u8DimVal3 < GetValuesDefined1(32)))
                   ||(g_stVChipRatingInfo.u8DimVal33 > 0 && (g_stVChipRatingInfo.u8DimVal4 < GetValuesDefined1(33)))
                   ||(g_stVChipRatingInfo.u8DimVal34 > 0 && (g_stVChipRatingInfo.u8DimVal5 < GetValuesDefined1(34)))
                   ||(g_stVChipRatingInfo.u8DimVal35 > 0 && (g_stVChipRatingInfo.u8DimVal6 < GetValuesDefined1(35)))
                   ||(g_stVChipRatingInfo.u8DimVal36 > 0 && (g_stVChipRatingInfo.u8DimVal7 < GetValuesDefined1(36)))
                   ||(g_stVChipRatingInfo.u8DimVal37 > 0 && (g_stVChipRatingInfo.u8DimVal8 < GetValuesDefined1(37)))
                   ||(g_stVChipRatingInfo.u8DimVal38 > 0 && (g_stVChipRatingInfo.u8DimVal9 < GetValuesDefined1(38)))
                   ||(g_stVChipRatingInfo.u8DimVal39 > 0 && (g_stVChipRatingInfo.u8DimVal9 < GetValuesDefined1(39)))
                   ||(g_stVChipRatingInfo.u8DimVal40 > 0 && (g_stVChipRatingInfo.u8DimVal9 < GetValuesDefined1(40)))
                  #endif
                   )
                {
                    if (u8Strlen > 0)
                    {
                        *pu8Str++ = CHAR_SPACE;
                        *pu8Str++ = CHAR_SLASH;
                        *pu8Str++ = CHAR_SPACE;
                        *pu8Str = '\0';
                        u8Strlen += 3;
                    }
                }
            }
        #endif // #if _VChip2_
        }

    #if _VChip2_
        UiMenuStr_GetVChip2RatingString(pu8Str);
    #endif
    }
    else if (g_stVChipRatingInfo.RatingType >= VCHIP_RATING_TYPE_TV && g_stVChipRatingInfo.RatingType <= VCHIP_RATING_TYPE_CANADA_FRE)
    {
        u8Strlen = UiMenuStr_GetVChip1RatingString(pu8Str);
        pu8Str += u8Strlen;

    #if _VChip2_
        if (stGenSettingVchipRegion5.u8NoDimension!=0)
        {
            if ( (g_stVChipRatingInfo.u8DimVal0 > 0 && (g_stVChipRatingInfo.u8DimVal0 < GetValuesDefined1(0)))
               ||(g_stVChipRatingInfo.u8DimVal1 > 0 && (g_stVChipRatingInfo.u8DimVal1 < GetValuesDefined1(1)))
               ||(g_stVChipRatingInfo.u8DimVal2 > 0 && (g_stVChipRatingInfo.u8DimVal2 < GetValuesDefined1(2)))
               ||(g_stVChipRatingInfo.u8DimVal4 > 0 && (g_stVChipRatingInfo.u8DimVal4 < GetValuesDefined1(4)))
               ||(g_stVChipRatingInfo.u8DimVal5 > 0 && (g_stVChipRatingInfo.u8DimVal5 < GetValuesDefined1(5)))
               ||(g_stVChipRatingInfo.u8DimVal6 > 0 && (g_stVChipRatingInfo.u8DimVal6 < GetValuesDefined1(6)))
               ||(g_stVChipRatingInfo.u8DimVal7 > 0 && (g_stVChipRatingInfo.u8DimVal7 < GetValuesDefined1(7)))
               ||(g_stVChipRatingInfo.u8DimVal8 > 0 && (g_stVChipRatingInfo.u8DimVal8 < GetValuesDefined1(8)))
               ||(g_stVChipRatingInfo.u8DimVal9 > 0 && (g_stVChipRatingInfo.u8DimVal9 < GetValuesDefined1(9)))
              #if (ENABLE_MAX_RRT_DIMENSION_NUMBER)
               ||(g_stVChipRatingInfo.u8DimVal10 > 0 && (g_stVChipRatingInfo.u8DimVal1 < GetValuesDefined1(10)))
               ||(g_stVChipRatingInfo.u8DimVal11 > 0 && (g_stVChipRatingInfo.u8DimVal2 < GetValuesDefined1(11)))
               ||(g_stVChipRatingInfo.u8DimVal12 > 0 && (g_stVChipRatingInfo.u8DimVal3 < GetValuesDefined1(12)))
               ||(g_stVChipRatingInfo.u8DimVal13 > 0 && (g_stVChipRatingInfo.u8DimVal4 < GetValuesDefined1(13)))
               ||(g_stVChipRatingInfo.u8DimVal14 > 0 && (g_stVChipRatingInfo.u8DimVal5 < GetValuesDefined1(14)))
               ||(g_stVChipRatingInfo.u8DimVal15 > 0 && (g_stVChipRatingInfo.u8DimVal6 < GetValuesDefined1(15)))
               ||(g_stVChipRatingInfo.u8DimVal16 > 0 && (g_stVChipRatingInfo.u8DimVal7 < GetValuesDefined1(16)))
               ||(g_stVChipRatingInfo.u8DimVal17 > 0 && (g_stVChipRatingInfo.u8DimVal8 < GetValuesDefined1(17)))
               ||(g_stVChipRatingInfo.u8DimVal18 > 0 && (g_stVChipRatingInfo.u8DimVal9 < GetValuesDefined1(18)))
               ||(g_stVChipRatingInfo.u8DimVal19 > 0 && (g_stVChipRatingInfo.u8DimVal9 < GetValuesDefined1(19)))
               ||(g_stVChipRatingInfo.u8DimVal20 > 0 && (g_stVChipRatingInfo.u8DimVal1 < GetValuesDefined1(20)))
               ||(g_stVChipRatingInfo.u8DimVal21 > 0 && (g_stVChipRatingInfo.u8DimVal2 < GetValuesDefined1(21)))
               ||(g_stVChipRatingInfo.u8DimVal22 > 0 && (g_stVChipRatingInfo.u8DimVal3 < GetValuesDefined1(22)))
               ||(g_stVChipRatingInfo.u8DimVal23 > 0 && (g_stVChipRatingInfo.u8DimVal4 < GetValuesDefined1(23)))
               ||(g_stVChipRatingInfo.u8DimVal24 > 0 && (g_stVChipRatingInfo.u8DimVal5 < GetValuesDefined1(24)))
               ||(g_stVChipRatingInfo.u8DimVal25 > 0 && (g_stVChipRatingInfo.u8DimVal6 < GetValuesDefined1(25)))
               ||(g_stVChipRatingInfo.u8DimVal26 > 0 && (g_stVChipRatingInfo.u8DimVal7 < GetValuesDefined1(26)))
               ||(g_stVChipRatingInfo.u8DimVal27 > 0 && (g_stVChipRatingInfo.u8DimVal8 < GetValuesDefined1(27)))
               ||(g_stVChipRatingInfo.u8DimVal28 > 0 && (g_stVChipRatingInfo.u8DimVal9 < GetValuesDefined1(28)))
               ||(g_stVChipRatingInfo.u8DimVal29 > 0 && (g_stVChipRatingInfo.u8DimVal9 < GetValuesDefined1(29)))
               ||(g_stVChipRatingInfo.u8DimVal30 > 0 && (g_stVChipRatingInfo.u8DimVal1 < GetValuesDefined1(30)))
               ||(g_stVChipRatingInfo.u8DimVal31 > 0 && (g_stVChipRatingInfo.u8DimVal2 < GetValuesDefined1(31)))
               ||(g_stVChipRatingInfo.u8DimVal32 > 0 && (g_stVChipRatingInfo.u8DimVal3 < GetValuesDefined1(32)))
               ||(g_stVChipRatingInfo.u8DimVal33 > 0 && (g_stVChipRatingInfo.u8DimVal4 < GetValuesDefined1(33)))
               ||(g_stVChipRatingInfo.u8DimVal34 > 0 && (g_stVChipRatingInfo.u8DimVal5 < GetValuesDefined1(34)))
               ||(g_stVChipRatingInfo.u8DimVal35 > 0 && (g_stVChipRatingInfo.u8DimVal6 < GetValuesDefined1(35)))
               ||(g_stVChipRatingInfo.u8DimVal36 > 0 && (g_stVChipRatingInfo.u8DimVal7 < GetValuesDefined1(36)))
               ||(g_stVChipRatingInfo.u8DimVal37 > 0 && (g_stVChipRatingInfo.u8DimVal8 < GetValuesDefined1(37)))
               ||(g_stVChipRatingInfo.u8DimVal38 > 0 && (g_stVChipRatingInfo.u8DimVal9 < GetValuesDefined1(38)))
               ||(g_stVChipRatingInfo.u8DimVal39 > 0 && (g_stVChipRatingInfo.u8DimVal9 < GetValuesDefined1(39)))
               ||(g_stVChipRatingInfo.u8DimVal40 > 0 && (g_stVChipRatingInfo.u8DimVal9 < GetValuesDefined1(40)))
              #endif
               )
            {
                if (bExtra)
                {
                    if (u8Strlen > 0)
                    {
                        *pu8Str++ = CHAR_SPACE;
                        *pu8Str++ = CHAR_SLASH;
                        *pu8Str++ = CHAR_SPACE;
                        *pu8Str = '\0';
                        u8Strlen += 3;
                    }
                    UiMenuStr_GetVChip2RatingString(pu8Str);
                }
            }
        }
    #endif // #if _VChip2_
    }
}

//#if (EPG_THIS_CH)
U8* ThisEpg_EventTitleText(void)
{
    //printf("EventTitleText=%X,%X\n", au8EpgUiBuf[0], au8EpgUiBuf[1]);
    return &(au8EpgUiBuf[0]);
}

U8* ThisEpg_EventTimeText(void)
{
    return pu8EpgString;
}

U8* ThisEpg_EventVChipInfoText(void)
{
    return pu8EpgString;
}

U8* ThisEpg_DrawLeftArrowColonText(void)
{

    pu8EpgString[0] = CHAR_P;
    pu8EpgString[1] = CHAR_R;
    pu8EpgString[2] = CHAR_E;
    pu8EpgString[3] = CHAR_V;
    pu8EpgString[4] = '\0';

    return pu8EpgString;
}
U8* ThisEpg_DrawRightArrowColonText(void)
{
    pu8EpgString[0] = CHAR_N;
    pu8EpgString[1] = CHAR_E;
    pu8EpgString[2] = CHAR_X;
    pu8EpgString[3] = CHAR_T;
    pu8EpgString[4] = '\0';

    return pu8EpgString;
}

U8* ThisEpg_EventEttText(void)
{
    if (IsATVInUse())
        return (U8 *)"( No title. )";
    else
        return &(au8EpgUiBuf[0]);
}

U8* RatingInfoText(void)
{
    memset(au8Section,0,256);

    UiMenuStr_GetRatingString(au8Section);

    return au8Section;
}

U8* ThisEpg_SystemTimeText(void)
{
    return pu8EpgString;
}

U8* CurEPGProgramInfoText(void)
{
    U8 i;
    U8* u8StrBuffer2 = NULL;
    U8 u8EpgTitlePrefix[] = "CH. ";

    //Get program number
    if(IsDTVInUse())  // Remove ATV case.....ATV no EPG ui
    {
        U16 u16ProgLen = MApp_UiMenu_u16Strlen(CurProgramNameText());
        U8 u8EpgTitlelen = strlen((char *)u8EpgTitlePrefix);
        str_add(au8Section, u8EpgTitlePrefix);
        MApp_UiMenuFunc_ConvertProgramNumber2Str(&MApp_ChanProc_GetChannelPointer(VIR_CH_IDX(MApp_ChanProc_GetCurProgIndex()))->stVirtualChNum, au8Section+u8EpgTitlelen);
        u8StrBuffer2 = malloc(u16ProgLen);

        if( u8StrBuffer2 != NULL )
        {
            // Fix coverity-CID-185103: Uninitialized scalar variable
            memset(u8StrBuffer2, 0, u16ProgLen);

            MApp_U16StringToU8String(CurProgramNameText(), u8StrBuffer2, u16ProgLen);
            i = strlen((char *)au8Section);
            i += str_add(au8Section+i, u8StrBuffer2);
            au8Section[i] = NULL;
            free(u8StrBuffer2);   // coverity@109704
            return au8Section;
        }
    }

    return au8Section;
}

U8* EPGPrevProgramNumberText(void)
{

    U16 PreProgIndx;

    // Get Pre-Program index
    PreProgIndx = MApp_GetPrevNextProgramIndex(TRUE);

    //Get program number
    if(IsDTVInUse() || IsATVInUse())
    {
        MApp_UiMenuFunc_ConvertTempChannelProgramNumber2Str(&(MApp_ChanProc_GetTempChannelPointer(VIR_CH_IDX(PreProgIndx))->stVirtualChNum), au8Section);
    }

    return au8Section;
}

U8* EPGNextProgramNumberText(void)
{

    U16 NextProgIndx;

    // Get Next-Program index
    NextProgIndx = MApp_GetPrevNextProgramIndex(FALSE);

    //Get program number
    if(IsDTVInUse() || IsATVInUse())
    {
        MApp_UiMenuFunc_ConvertTempChannelProgramNumber2Str(&(MApp_ChanProc_GetTempChannelPointer(VIR_CH_IDX(NextProgIndx))->stVirtualChNum), au8Section);
    }
    return au8Section;
}
//#endif


U8* AudioTitleText(void)
{
    U16 u16TempStringID = en_str_Audio;

    MApp_U16StringToU8String(MApp_ZUI_API_GetString(u16TempStringID),(U8*)CHAR_BUFFER,MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetString(u16TempStringID)));
    return  (U8*)CHAR_BUFFER;
}

U8* MtsStereoText(void)
{
     U16 u16TempStringID = en_str_Stereo;

    MApp_U16StringToU8String(MApp_ZUI_API_GetString(u16TempStringID),(U8*)CHAR_BUFFER,MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetString(u16TempStringID)));
    return  (U8*)CHAR_BUFFER;
}

U8* EventInfoLine2Left(void)
{
    au8Section[0]= 0;
    iu8Buffer_i=0;
    if(IsDTVInUse())
    {
        iu8Buffer_j = strlen((char *)DtvReslutionTypeText());
        memcpy(au8Section, DtvReslutionTypeText(), (iu8Buffer_j)); //including '\0'
        iu8Buffer_i += iu8Buffer_j;
    }
    else
    {
        MApp_ReturnResolution(au8Section);
        iu8Buffer_j = strlen((char *)au8Section);
        iu8Buffer_i += iu8Buffer_j;
    }

    au8Section[iu8Buffer_i++] = CHAR_SPACE;
    au8Section[iu8Buffer_i++] = CHAR_SPACE;

    /* sound track text*/
    pstVirtualCh = MApp_ChanProc_GetCurChannelPointer();
    if((pstVirtualCh->u8AudLangNum && IsDTVInUse()) || IsATVInUse())
    {
        if(IsDTVInUse())
        {
            iu8Buffer_j = strlen((char *)AudioTitleText());
            memcpy(au8Section+iu8Buffer_i, (AudioTitleText()), iu8Buffer_j);
            iu8Buffer_i +=iu8Buffer_j;
            au8Section[iu8Buffer_i++] = CHAR_SPACE;
            MApp_UlongToString(g_u8AudLangSelected + 1, au8Section+iu8Buffer_i, 1);
            iu8Buffer_i++;
            au8Section[iu8Buffer_i++] = CHAR_SLASH;
            MApp_UlongToString(pstVirtualCh->u8AudLangNum, au8Section+iu8Buffer_i, 1);
            iu8Buffer_i++;
            au8Section[iu8Buffer_i++] = '(';
            iu8Buffer_j = strlen((char *)AudSoundModeText());
            strncpy((char *)au8Section+iu8Buffer_i, (char *)AudSoundModeText(),iu8Buffer_j);
            iu8Buffer_i += iu8Buffer_j;
            au8Section[iu8Buffer_i++] = ')';
        }
        else if(IsATVInUse()) // Here Signal Info should be show.
        {
            if(MApp_SoundMtsSifSoundModeTrans(g_u8AudLangSelected)==E_AUDIOMODE_K_STEREO)
            {
                if(MApp_AUDIO_IsSifSoundModeExist( SOUND_MTS_STEREO))
                {
                    iu8Buffer_j = strlen((char *)MtsStereoText());
                    memcpy(au8Section+iu8Buffer_i, MtsStereoText(), iu8Buffer_j);
                    iu8Buffer_i +=iu8Buffer_j;
                }
            }
            else if(MApp_SoundMtsSifSoundModeTrans(g_u8AudLangSelected)==E_AUDIOMODE_MONO_SAP)
            {
                if(MApp_AUDIO_IsSifSoundModeExist(SOUND_MTS_SAP))
                {
                    iu8Buffer_j = strlen("SAP");
                    memcpy(au8Section+iu8Buffer_i, "SAP", iu8Buffer_j);
                    iu8Buffer_i +=iu8Buffer_j;
                }
            }
            else if(MApp_SoundMtsSifSoundModeTrans(g_u8AudLangSelected)==E_AUDIOMODE_DUAL_AB)
            {
                iu8Buffer_j = strlen("DUAL");
                memcpy(au8Section+iu8Buffer_i, "DUAL", iu8Buffer_j);
                iu8Buffer_i +=iu8Buffer_j;

            }
            else
            {
                iu8Buffer_j = strlen("Mono");
                memcpy(au8Section+iu8Buffer_i, "Mono", iu8Buffer_j);
                iu8Buffer_i +=iu8Buffer_j;
            }
        }
    }
    au8Section[iu8Buffer_i] = 0;
    return au8Section;
}

U8* EventInfoLine2Right(void)
{
    au8Section[0]= 0;
    memset(au8Section,0x00,1024);
    iu8Buffer_i=0;
/* Scramble text*/
    #if SHOW_CHANNEL_SCRAMBLE_INFO
    if(IsDTVInUse())
    {
        iu8Buffer_j = strlen((char *)ScrambleText());
        memcpy(au8Section+iu8Buffer_i, ScrambleText(), iu8Buffer_j);
        iu8Buffer_i +=iu8Buffer_j;
        au8Section[iu8Buffer_i++] = CHAR_SPACE;
    }
    #endif

/* Rating String */
    UiMenuStr_GetRatingString(au8Section+iu8Buffer_i);

    iu8Buffer_j = strlen((char *)au8Section);
    printf("iu8Buffer_j = %d, rating = %s\n", iu8Buffer_j, au8Section);
    au8Section[iu8Buffer_j] = 0;
    return au8Section;
}

U8* EventInfoLine3Left(void)
{
    U32 u32StartTime;
    U32 u32EndTime;
    au8Section[0]= 0;
    iu8Buffer_i=0;


    /* current time text */
    stGenSetting.g_Time.s32Offset_Time = (U32)MApp_GetTimeZoneOffset(stGenSetting.g_SysSetting.u8TimeZone);

#if INFO_BANNER_TIME_ALWAYS_BY_STREAM
    if (g_u32StreamTime==0)
    {
        return au8Section;
    }

    MApp_ConvertLocalTime2Date((S32)(g_u32StreamTime + stGenSetting.g_Time.s32Offset_Time), &stDate);
#else
    if( stGenSetting.g_SysSetting.fTimeAutoSync && (g_u32StreamTime==0) )
    {
        return au8Section;
    }

    MApp_ConvertLocalTime2Date((S32)(msAPI_Timer_GetSystemTime() + stGenSetting.g_Time.s32Offset_Time), &stDate);
#endif

    iu8Buffer_j = stDate.u8Hour;
    if (stGenSetting.g_SysSetting.fTimeFormat == 1) // 12-hour
    {
        if (stDate.u8Hour == 0)
        {
            iu8Buffer_j = 12;
        }
        else if (stDate.u8Hour > 12)
        {
            iu8Buffer_j -= 12;
        }
    }

    char* locbuff = NULL; //[MSAPI_DMX_SECTION_4K];
#define SIZE_OF_LOC_BUF 1024
    locbuff = msAPI_Memory_Allocate( SIZE_OF_LOC_BUF, BUF_ID_ZUI_STR_BUF);
    if( locbuff == NULL )
    {
        return au8Section;
    }

    memset(locbuff, 0, SIZE_OF_LOC_BUF);

    if (stGenSetting.g_SysSetting.fTimeAutoSync == TIME_AUTO_SYNC_OFF)
    {
        if (stGenSetting.g_SysSetting.fTimeFormat == 0) // 24-hour
        {
            iu8Buffer_i += snprintf((char *)locbuff,SIZE_OF_LOC_BUF, "%04u/%02u/%02u %02u:%02u",
                stDate.u16Year, stDate.u8Month, stDate.u8Day, stDate.u8Hour, stDate.u8Min);
        }
        else
        {
            iu8Buffer_i += snprintf((char *)locbuff,SIZE_OF_LOC_BUF, "%04u/%02u/%02u %02u:%02u %s",
                stDate.u16Year, stDate.u8Month, stDate.u8Day, iu8Buffer_j, stDate.u8Min, AMPMText(stDate.u8Hour));
        }
    }
    else
    {
        if (stGenSetting.g_SysSetting.fTimeFormat == 0) // 24-hour
        {
            iu8Buffer_i += snprintf((char *)locbuff,SIZE_OF_LOC_BUF, "%04u/%02u/%02u %02u:%02u    ",
                stDate.u16Year, stDate.u8Month, stDate.u8Day, stDate.u8Hour, stDate.u8Min);
        }
        else
        {
            iu8Buffer_i += snprintf((char *)locbuff,SIZE_OF_LOC_BUF, "%04u/%02u/%02u %02u:%02u%s   ",
                stDate.u16Year, stDate.u8Month, stDate.u8Day,iu8Buffer_j, stDate.u8Min,  AMPMText(stDate.u8Hour));
        }

        /* program duration text */
        // start time
        if (IsDTVInUse() && MApp_EpgDB_GetCurEvent(&stEpgEventInfo))
        {
            //clrBtn1.bStringIndexWidth = CHAR_IDX_1BYTE;

            u32StartTime    = stEpgEventInfo.start_time - DEFAULT_SYSTEM_TIME - u8GpsUtcOffset + stGenSetting.g_Time.s32Offset_Time;
        #if( ENABLE_ATSC_EPG_DB_2016 )
            u32EndTime = u32StartTime + stEpgEventInfo.u32TimeLen;
        #else
            u32EndTime = u32StartTime + EPG_EVENT_LENGTH(stEpgEventInfo.length[0], stEpgEventInfo.length[1], stEpgEventInfo.length[2]);
        #endif

            MApp_ConvertLocalTime2Date((S32)u32StartTime, &stDate);

            iu8Buffer_j = stDate.u8Hour;
            if (stGenSetting.g_SysSetting.fTimeFormat == 1) // 12-hour
            {
                if (stDate.u8Hour == 0)
                    iu8Buffer_j = 12;
                else if (stDate.u8Hour > 12)
                    iu8Buffer_j -= 12;

                //iu8Buffer_i += snprintf((char *)au8Section+iu8Buffer_i, sizeof(au8Section)-iu8Buffer_i, "%02u:%02u%s-",
                //        iu8Buffer_j, stDate.u8Min, AMPMText(stDate.u8Hour));

                iu8Buffer_i += snprintf((char *)locbuff+iu8Buffer_i, SIZE_OF_LOC_BUF-iu8Buffer_i, "%02u:%02u%s-",
                        iu8Buffer_j, stDate.u8Min, AMPMText(stDate.u8Hour));

            }
            else
            {
                iu8Buffer_i += snprintf((char *)locbuff+iu8Buffer_i, SIZE_OF_LOC_BUF-iu8Buffer_i, "%02u:%02u-",
                        stDate.u8Hour, stDate.u8Min);
            }

            MApp_ConvertLocalTime2Date((S32)u32EndTime, &stDate);

            iu8Buffer_j = stDate.u8Hour;
            if (stGenSetting.g_SysSetting.fTimeFormat == 1) // 12-hour
            {
                if (stDate.u8Hour == 0)
                    iu8Buffer_j = 12;
                else if (stDate.u8Hour > 12)
                    iu8Buffer_j -= 12;

                snprintf((char *)locbuff+iu8Buffer_i, SIZE_OF_LOC_BUF - iu8Buffer_i, "%02u:%02u%s",
                         iu8Buffer_j, stDate.u8Min, AMPMText(stDate.u8Hour));

            }
            else
            {
                snprintf((char *)locbuff+iu8Buffer_i, SIZE_OF_LOC_BUF - iu8Buffer_i, "%02u:%02u",
                         stDate.u8Hour, stDate.u8Min);
            }
        }
    }

#ifdef DISABLE_SYSTEM_AUTO_SYNC_UI
    if ( !IsDTVInUse() )
    {
        au8Section[0] = 0;
    }
#endif

    strncpy((char *)au8Section, (char *)locbuff, SIZE_OF_LOC_BUF);

    msAPI_Memory_Free(locbuff, BUF_ID_ZUI_STR_BUF);

    return au8Section;
}

U16 VidResIconTextId(void)
{
    if(IsHDMIInUse())
    {
         if(g_HdmiPollingStatus.bIsHDMIMode != TRUE)
            return en_str_DVI;
         else
            return 0;
    }
    else
    {
        if ( MApi_XC_Sys_IsSrcHD(MAIN_WINDOW))
       {
          return en_str_HD;
       }
       else
       {
           return en_str_SD;
       }
   }
}

