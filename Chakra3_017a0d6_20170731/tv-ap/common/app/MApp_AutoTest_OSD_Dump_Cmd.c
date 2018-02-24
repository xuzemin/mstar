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

#include "MApp_AutoTest.h"
#include "ZUI_exefunc.h"
#include "MApp_MenuFunc.h"

extern BOOLEAN MApp_ZUI_ACT_ExecuteSetAudLangDialogAction(U16 act);

//=======================================================================

EN_AT_RESULT _MApp_AT_OSDCmdHandler(AT_CMD ATCmd)
{
    switch(ATCmd.u16CmdSubType)
    {
        case EN_AUTO_TEST_DIRECT_CMD_OSD_COUNTRY: // 14
        {
            printf("EN_AUTO_TEST_DIRECT_CMD_OSD_COUNTRY \n");
            
            MEMBER_COUNTRY mCountry;
            mCountry = MApp_AT_ConvertATCountryToMemCountry((EN_AT_MEMBER_COUNTRY)ATCmd.iCmdPara[0]);
            MApp_SetOSDCountrySetting((EN_OSD_COUNTRY_SETTING)mCountry, TRUE);
            DisplayCountry((MEMBER_COUNTRY)MApp_GetOSDCountrySetting());
            
            return EN_AT_RESULT_OK;
        }
        case EN_AUTO_TEST_DIRECT_CMD_OSD_AUDIO_PRIMARY_LANGUAGE: // 16
        {
            printf("EN_AUTO_TEST_DIRECT_CMD_OSD_AUDIO_PRIMARY_LANGUAGE \n");
            
            stUserSoundSettingType *pstSoundSetting = NULL;
            EN_LANGUAGE eLan;
            
            MApp_GetGenSetting(EN_GENSETTING_CLASS_SOUND,  (void *)&pstSoundSetting);
            if(pstSoundSetting->Primary_Flag)
            {
                DEBUG_AUTOTEST(printf("Audio language setting is secondary language\n"));
                if(!MApp_ZUI_ACT_ExecuteSetAudLangDialogAction((U16)EN_EXE_AUDIOLANG_SET))
                {
                    return EN_AT_RESULT_ER;
                }
            }
            else
            {
                DEBUG_AUTOTEST(printf("Audio language setting is primary language\n"));
            }
            eLan = MApp_AT_ConvertATLangToENLang((EN_AT_MEMBER_LANGUAGE)ATCmd.iCmdPara[0]);
            MApp_SetAudioLangMenuLanguage(eLan);
            DisplayLanguage(MApp_GetAudioLangMenuLanguage_DTG());
            
            return EN_AT_RESULT_OK;
        }
        case EN_AUTO_TEST_DIRECT_CMD_OSD_SUBTITLE_PRIMARY_LANGUAGE: // 18
        {
            printf("EN_AUTO_TEST_DIRECT_CMD_OSD_SUBTITLE_PRIMARY_LANGUAGE \n");
            EN_LANGUAGE eLan;
            
            if(MApp_MenuFunc_Setup_SubLanguage_Get())
            {
                DEBUG_AUTOTEST(printf("Subtitle language setting is secondary language\n"));
                MApp_MenuFunc_Setup_SubLanguage_Toggle();
            }
            else
            {
                DEBUG_AUTOTEST(printf("Subtitle language setting is primary language\n"));
            }
            eLan = MApp_AT_ConvertATLangToENLang((EN_AT_MEMBER_LANGUAGE)ATCmd.iCmdPara[0]);
            MApp_SetSubLangMenuLanguage(eLan);
            DisplayLanguage(MApp_GetSubLangMenuLanguage_DTG());
            
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
