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

#include "Board.h"

#if( CHAKRA3_AUTO_TEST )
#if(ENABLE_SUBTITLE)

#include "MApp_AutoTest.h"
#include "MApp_Subtitle.h"
#include "MApp_UiMenuDef.h"
#if ENABLE_PVR
#include "MApp_PVR.h"
#endif


//=======================================================================

EN_AT_RESULT _MApp_AT_SubtitleCmdHandler(AT_CMD ATCmd)
{
    char tmp[50] = {'\0'};
    switch(ATCmd.u16CmdSubType)
    {
        case EN_AUTO_TEST_SUBTITLE_ENABLE: // 1
        {
            printf("EN_AUTO_TEST_SUBTITLE_ENABLE \n");
            U8 i;
            U8 selectidx;
            EN_LANGUAGE enlan;
            
            enlan = MApp_GetSubLangMenuLanguage_DTG();
            selectidx=1;
            for(i=1; i<=u8SubtitleMenuNum; i++)
            {
                if(enlan == MApp_GetLanguageBySILanguage(msAPI_SI_GetLanguageByISO639LangCode((U8 *)SubtitleMenu[i-1].StringCodes)))
                {
                    selectidx = i;
                    break;
                }
            }
            
            u8SubtitleItemSelIdx = selectidx;
            
            if(u8SubtitleItemSelIdx != 0)
            {
                stGenSetting.g_SysSetting.fEnableSubTitle = EN_SUBTITILE_SYSTEM_ON;

#if ENABLE_TTX
                if(SubtitleMenu[u8SubtitleItemSelIdx-1].u8SubtitleType == SUBTITLING_TYPE_TELETEXT
                    ||SubtitleMenu[u8SubtitleItemSelIdx-1].u8SubtitleType == SUBTITLING_TYPE_TELETEXT_HOH)
                {
                    U8 Magazine = 0;
                    U8 Page = 0;
                    U16 u16Pid = 0;

                    //close the window and reopen it latter by the new parameters
#if PVR_AND_TTX_DIFF_WITH_MHEG5
					MApp_TTX_TurnTTXOnOff(TRUE);
#endif
                    MApp_TTX_TeletextCommand(TTX_TV);

                    stGenSetting.g_SysSetting.fEnableTTXSubTitle=TRUE;
                    MApp_TTX_Subtitle_GetData((u8SubtitleItemSelIdx-1), &Magazine, &Page, &u16Pid);
                    MApp_TTX_SetSubtitleTTX_PID(u16Pid);
#if ENABLE_PVR
                    if (MApp_PVR_IsPlaybacking())
                        MApp_TTX_SetDefaultTTX_PID(u16Pid);
#endif
                    MApp_TTX_SetSubtitlePage(((U16)Magazine<<8) | Page, 0xFFFF);
                    MApp_Subtitle_Select_Language(u8SubtitleItemSelIdx-1);  //set subtitle new index
                }
                else
#endif
                if(SubtitleMenu[u8SubtitleItemSelIdx-1].u8SubtitleType == SUBTITLING_TYPE_HH_NO)
                {
                    stGenSetting.g_SysSetting.fEnableTTXSubTitle=FALSE;
                    MApp_Subtitle_Select_Language(u8SubtitleItemSelIdx-1);
                }
                else
                {
                    stGenSetting.g_SysSetting.fEnableTTXSubTitle=FALSE;
                    MApp_Subtitle_Select_Language(u8SubtitleItemSelIdx-1);
                }
            }
            else
            {
                stGenSetting.g_SysSetting.fEnableTTXSubTitle = FALSE;
                stGenSetting.g_SysSetting.fEnableSubTitle = EN_SUBTITILE_SYSTEM_OFF;
            }

            return EN_AT_RESULT_OK;
        }
        case EN_AUTO_TEST_SUBTITLE_DISABLE: // 2
        {
            printf("EN_AUTO_TEST_SUBTITLE_DISABLE \n");
            
            u8SubtitleItemSelIdx = 0;

            stGenSetting.g_SysSetting.fEnableTTXSubTitle = FALSE;
            stGenSetting.g_SysSetting.fEnableSubTitle = EN_SUBTITILE_SYSTEM_OFF;
            
            return EN_AT_RESULT_OK;
        }
        case EN_AUTO_TEST_SUBTITLE_HH_ENABLE: // 3
        {
            printf("EN_AUTO_TEST_SUBTITLE_HH_ENABLE \n");
            
            stGenSetting.g_SysSetting.fHardOfHearing = 1;
            
            return EN_AT_RESULT_OK;
        }
        case EN_AUTO_TEST_SUBTITLE_HH_DISABLE: // 4
        {
            printf("EN_AUTO_TEST_SUBTITLE_HH_DISABLE \n");
            
            stGenSetting.g_SysSetting.fHardOfHearing = 0;
            
            return EN_AT_RESULT_OK;
        }
        case EN_AUTO_TEST_SUBTITLE_GET_CURRENT_LANGUAGE: // 5
        {
            printf("EN_AUTO_TEST_SUBTITLE_GET_CURRENT_LANGUAGE \n");
			
            switch(ATCmd.iCmdPara[0])
            {
            	case E_SUBTITLE_LAN:
            		DisplayLanguage(MApp_GetLanguageBySILanguage(msAPI_SI_GetLanguageByISO639LangCode((U8 *)SubtitleMenu[u8SubtitleItemSelIdx-1].StringCodes)));
            		break;
            	case E_SUBTITLE_TYPE:
            		switch(SubtitleMenu[u8SubtitleItemSelIdx-1].u8SubtitleType)
            		{
            			case SUBTITLING_TYPE_TELETEXT:
                            snprintf(tmp, sizeof(tmp), "TELETEXT\n");
            				break;
            			case SUBTITLING_TYPE_TELETEXT_HOH:
                            snprintf(tmp, sizeof(tmp), "TELETEXT_HOH\n");
            				break;
            			case SUBTITLING_TYPE_NORMAL_NO:
                            snprintf(tmp, sizeof(tmp), "NORMAL_NO\n");
            				break;
            			case SUBTITLING_TYPE_NORMAL_4X3:
                            snprintf(tmp, sizeof(tmp), "NORMAL_4X3\n");
            				break;
            			case SUBTITLING_TYPE_NORMAL_16X9:
                            snprintf(tmp, sizeof(tmp), "NORMAL_16X9\n");
            				break;
            			case SUBTITLING_TYPE_NORMAL_221X100:
                            snprintf(tmp, sizeof(tmp), "NORMAL_221X100\n");
            				break;
            			case SUBTITLING_TYPE_NORMAL_HD:
                            snprintf(tmp, sizeof(tmp), "NORMAL_HD\n");
            				break;
            			case SUBTITLING_TYPE_HH_NO:
                            snprintf(tmp, sizeof(tmp), "HH_NO\n");
            				break;
            			case SUBTITLING_TYPE_HH_4X3:
                            snprintf(tmp, sizeof(tmp), "HH_4X3\n");
            				break;
            			case SUBTITLING_TYPE_HH_16X9:
                            snprintf(tmp, sizeof(tmp), "HH_16X9\n");
            				break;
            			case SUBTITLING_TYPE_HH_221X100:
                            snprintf(tmp, sizeof(tmp), "HH_221X100\n");
            				break;
            			case SUBTITLING_TYPE_HH_HD:
                            snprintf(tmp, sizeof(tmp), "HH_HD\n");
            				break;
            			default:
                            snprintf(tmp, sizeof(tmp), "None\n");
            				break;
            		}
                    MApp_AT_Msg_Add((U8*)tmp);
            		break;
            	default:
            		return EN_AT_RESULT_ER;
            }
            return EN_AT_RESULT_OK;
        }
        default:
        {
            printf("Wrong SubCmdType! \n");
            return EN_AT_RESULT_ER;
        }
    }
}

#endif
#endif

