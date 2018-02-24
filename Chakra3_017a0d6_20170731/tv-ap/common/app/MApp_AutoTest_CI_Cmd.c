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
#if ENABLE_CI
#include "MApp_AutoTest.h"
#include "msAPI_CI.h"
#include "msAPI_audio.h"
#include "MApp_CIMMI.h"
#include "drvTVEncoder.h"
#include "MApp_ZUI_ACTcoexistWin.h"
#include "string.h"

extern CIMMI_INFO *pMMIdup;

#define MAX_LOG_STR_SIZE 50

//=======================================================================

BOOL CiTestGetCIMMI(void)
{
    char tmp[MAX_CIMMI_TEXT_SIZE];
    CIMMI_INFO *_pInfo = pMMIdup;
    U8 i;
    
    memset(tmp,0,MAX_CIMMI_TEXT_SIZE);
    
    if (NULL == _pInfo)
    {
        printf("CIMMI Get Data error!!!\n");
        return FALSE;
    }
    
    if(_pInfo->enType == EN_MMI_TYPE_MENU)
    {
        //show menu texts
        if (_pInfo->aTitleContent)
        {
            snprintf(tmp, sizeof(tmp), "%s\n", _pInfo->aTitleContent);
            MApp_AT_Msg_Add((U8*)tmp);
        }
        
        if (_pInfo->content.menu_data.au8Subtitle)
        {
            snprintf(tmp, sizeof(tmp), "%s\n", _pInfo->content.menu_data.au8Subtitle);
            MApp_AT_Msg_Add((U8*)tmp);
        }
        
        for (i = 0; i < _pInfo->content.menu_data.ListCnt; i++)
        {
            snprintf(tmp, sizeof(tmp), "%s\n",_pInfo->content.menu_data.pString[i]);
            MApp_AT_Msg_Add((U8*)tmp);
        }
        snprintf(tmp, sizeof(tmp), "\n");
        MApp_AT_Msg_Add((U8*)tmp);
        
        if (_pInfo->content.menu_data.au8Bottom)
        {
            snprintf(tmp, sizeof(tmp), "%s\n", _pInfo->content.menu_data.au8Bottom);
            MApp_AT_Msg_Add((U8*)tmp);
        }
        snprintf(tmp, sizeof(tmp), "\n");
        MApp_AT_Msg_Add((U8*)tmp);
    }
    else if(_pInfo->enType == EN_MMI_TYPE_LIST)
    {
        //show menu texts
        if (_pInfo->aTitleContent)
        {
            snprintf(tmp, sizeof(tmp), "%s\n", _pInfo->aTitleContent);
            MApp_AT_Msg_Add((U8*)tmp);
        }
        snprintf(tmp, sizeof(tmp), "\n");
        MApp_AT_Msg_Add((U8*)tmp);
        
        if (_pInfo->content.list_data.au8Subtitle)
        {
            snprintf(tmp, sizeof(tmp), "%s\n", _pInfo->content.list_data.au8Subtitle);
            MApp_AT_Msg_Add((U8*)tmp);
        }
        snprintf(tmp, sizeof(tmp), "\n\n");
        MApp_AT_Msg_Add((U8*)tmp);
        
        for (i = 0; i < _pInfo->content.list_data.ListCnt; i++)
        {
            snprintf(tmp, sizeof(tmp), "%s\n",_pInfo->content.list_data.pString[i]);
            MApp_AT_Msg_Add((U8*)tmp);
        }
        snprintf(tmp, sizeof(tmp), "\n");
        MApp_AT_Msg_Add((U8*)tmp);
        
        if (_pInfo->content.list_data.au8Bottom)
        {
            snprintf(tmp, sizeof(tmp), "%s\n", _pInfo->content.list_data.au8Bottom);
            MApp_AT_Msg_Add((U8*)tmp);
        }
    }
    return TRUE;
}

EN_AT_RESULT _MApp_AT_CICmdHandler(AT_CMD ATCmd)
{    
    char tmp[MAX_LOG_STR_SIZE];
    EN_AT_RESULT eRet = EN_AT_RESULT_ER ;

    memset(tmp,0,MAX_LOG_STR_SIZE);
    
    switch(ATCmd.u16CmdSubType)
    {
        case EN_AUTO_TEST_CI_CMD_CARD_INSERT: // 1
        {
            printf("EN_AUTO_TEST_CI_CMD_CARD_INSERT \n");
            
            msAPI_CI_SetDetectEnable(TRUE);
            snprintf(tmp, sizeof(tmp), "Insert Card\n");
            
            eRet = EN_AT_RESULT_OK;
            break;
        }
        case EN_AUTO_TEST_CI_CMD_CARD_REMOVE: // 2
        {
            printf("EN_AUTO_TEST_CI_CMD_CARD_REMOVE \n");
            
            msAPI_CI_SetDetectEnable(FALSE);
            snprintf(tmp, sizeof(tmp), "Remove Card\n");
            
            eRet = EN_AT_RESULT_OK;
            break;
        }
        case EN_AUTO_TEST_CI_CMD_ENTER_MENU: // 3
        {
            printf("EN_AUTO_TEST_CI_CMD_ENTER_MENU \n");
            
            msAPI_CI_MMIEnterMenu();
            
            eRet = EN_AT_RESULT_OK;
            break;
        }
        case EN_AUTO_TEST_CI_CMD_GET_CIMMI: // 4
        {
            printf("EN_AUTO_TEST_CI_CMD_GET_CIMMI \n");
            
            if(!CiTestGetCIMMI())
            {
                eRet = EN_AT_RESULT_ER;
                break;
            }
            eRet = EN_AT_RESULT_OK;
            break;
        }
        case EN_AUTO_TEST_CI_CMD_ANSWER_MENU: // 5
        {
            printf("EN_AUTO_TEST_CI_CMD_ANSWER_MENU \n");
            
            msAPI_CI_MMIAnswerMenu(ATCmd.iCmdPara[0]);
            
            eRet = EN_AT_RESULT_OK;
            break;
        }
        case EN_AUTO_TEST_CI_CMD_EXIT_MENU: // 6
        {
            printf("EN_AUTO_TEST_CI_CMD_EXIT_MENU \n");
            
            msAPI_CI_MMIClose();
            
            eRet = EN_AT_RESULT_OK;
            break;
        }
        case EN_AUTO_TEST_CI_CMD_GET_HSS: // 7
        {
#if ENABLE_CI_PLUS
            printf("EN_AUTO_TEST_CI_CMD_GET_HSS \n");

            if(msAPI_CI_HSS_Get())
            {
                snprintf(tmp, sizeof(tmp), "HSS = Active\n");
            }
            else
            {
                snprintf(tmp, sizeof(tmp), "HSS = Inactive\n");
            }
            eRet = EN_AT_RESULT_OK;
            break;
#else
            eRet = EN_AT_RESULT_ER;
            break;
#endif
        }
        case EN_AUTO_TEST_CI_CMD_GET_URI: // 8
        {
            printf("EN_AUTO_TEST_CI_CMD_GET_URI \n");
            
#if ENABLE_CI_PLUS
            U8 u8URI_RCT=0, u8URI_EMI=0, u8URI_APS=0, u8URI_ICT=0, u8URI_RL=0;
            
            if(!msAPI_CI_CC_GetURI(&u8URI_RCT, &u8URI_EMI, &u8URI_APS, &u8URI_ICT, &u8URI_RL))
            {
                printf("GetURI error!");
                eRet = EN_AT_RESULT_ER;
                break;
            }
            
            snprintf(tmp, sizeof(tmp), "URI [RCT, EMI, APS, ICT, RL] =[%d, %d, %d, %d, %d]\n\n", u8URI_RCT, u8URI_EMI, u8URI_APS, u8URI_ICT, u8URI_RL);
            eRet = EN_AT_RESULT_OK;
            break;
#else
            eRet = EN_AT_RESULT_ER;
            break;
#endif
        }
        case EN_AUTO_TEST_CI_CMD_GET_SCRAMBLE_STATUS: // 9
        {
            printf("EN_AUTO_TEST_CI_CMD_GET_SCRAMBLE_STATUS \n");
            
            MEMBER_SERVICETYPE serviceType;
            WORD wCurPosIdx;
            
            serviceType = msAPI_CM_GetCurrentServiceType();
            wCurPosIdx = msAPI_CM_GetCurrentPosition(serviceType);
            
            if(wCurPosIdx == INVALID_PROGRAM_POSITION)
            {
                printf("INVALID_PROGRAM_POSITION\n");
                eRet = EN_AT_RESULT_ER;
                break;
            }
            
            if(msAPI_CM_GetProgramAttribute(serviceType, wCurPosIdx, E_ATTRIBUTE_IS_SCRAMBLED))
            {
                snprintf(tmp, sizeof(tmp), "Scramble!\n");
            }
            else
            {
                snprintf(tmp, sizeof(tmp), "FTA!\n");
            }
            
            eRet = EN_AT_RESULT_OK;
            break;
        }
        case EN_AUTO_TEST_CI_CMD_GET_SCART_STATUS: // 10
        {
            printf("EN_AUTO_TEST_CI_CMD_GET_SCART_STATUS \n");
            
            BOOL bScartOut;
            BOOL bBlackScreen = MDrv_VE_IsBlackScreenEnabled();
            BOOL bCVBSOutMute = !MApi_XC_ADC_IsCVBSOutEnabled(OUTPUT_CVBS1);
#if (INPUT_SCART_VIDEO_COUNT > 1)
            bCVBSOutMute = bCVBSOutMute || (!MApi_XC_ADC_IsCVBSOutEnabled(OUTPUT_CVBS2));
#endif
            
            if( bCVBSOutMute || bBlackScreen )
                bScartOut = TRUE;
            else
                bScartOut = FALSE;
            
            snprintf(tmp, sizeof(tmp), "%d\n\n", bScartOut);
            
            eRet = EN_AT_RESULT_OK;
            break;
        }
        case EN_AUTO_TEST_CI_CMD_GET_LOG_FILE: // 11
        {
            printf("EN_AUTO_TEST_CI_CMD_GET_LOG_FILE \n");
            
            eRet = EN_AT_RESULT_OK;
            break;
        }
        case EN_AUTO_TEST_CI_CMD_GET_COPY_PROTECTION: // 12
        {
            printf("EN_AUTO_TEST_CI_CMD_GET_COPY_PROTECTION \n");

            U8 u8URI_RCT=0, u8URI_EMI=0, u8URI_APS=0, u8URI_ICT=0, u8URI_RL=0;
            
            if(!msAPI_CI_CC_GetURI(&u8URI_RCT, &u8URI_EMI, &u8URI_APS, &u8URI_ICT, &u8URI_RL))
            {
                printf("GetURI error!");
                eRet = EN_AT_RESULT_ER;
                break;
            }
            snprintf(tmp, sizeof(tmp), "%d\n\n",u8URI_EMI);
            
            eRet = EN_AT_RESULT_OK;
            break;
        }
        case EN_AUTO_TEST_CI_CMD_SPDIF_GET_SCMS: // 13
        {
            printf("EN_AUTO_TEST_CI_CMD_SPDIF_GET_SCMS \n");
            
            AUDIO_SPDIF_SCMS_MODE enSPDIF_SCMS_Result;
            
            enSPDIF_SCMS_Result = msAPI_AUD_SPDIF_GetSCMS();
            snprintf(tmp, sizeof(tmp), "%d\n\n",enSPDIF_SCMS_Result);
            
            eRet = EN_AT_RESULT_OK;
            break;
        }
        case EN_AUTO_TEST_CI_CMD_CLEAR_LOG_FILE: // 14
        {
            printf("EN_AUTO_TEST_CI_CMD_CLEAR_LOG_FILE \n");
            
            eRet = EN_AT_RESULT_OK;
            break;
        }
        case EN_AUTO_TEST_CI_CMD_ADD_CIMMI_EVENT_RECIPIENT: // 15
        {
            printf("EN_AUTO_TEST_CI_CMD_ADD_CIMMI_EVENT_RECIPIENT \n");
            
            eRet = EN_AT_RESULT_OK;
            break;
        }
        case EN_AUTO_TEST_CI_CMD_ADD_PVR_CI_PROTECTION_EVENT_RECIPIENT: // 16
        {
            printf("EN_AUTO_TEST_CI_CMD_ADD_PVR_CI_PROTECTION_EVENT_RECIPIENT \n");
            
            eRet = EN_AT_RESULT_OK;
            break;
        }
        case EN_AUTO_TEST_CI_CMD_SET_DTV_AV_MUTE: // 17
        {
            printf("EN_AUTO_TEST_CI_CMD_SET_DTV_AV_MUTE \n");

            BOOLEAN bIsAudioMuted;
            bIsAudioMuted = msAPI_AUD_IsAudioMutedByUser();
            
            if(ATCmd.iCmdPara[0]==1 && !bIsAudioMuted)
            {
                MApp_KeyProc_Mute();
                DEBUG_AUTOTEST(printf("Mute On\n"));
            }
            else if(ATCmd.iCmdPara[0]==0 && bIsAudioMuted)
            {
                MApp_KeyProc_Mute();
                DEBUG_AUTOTEST(printf("Mute Off\n"));
            }
            
            eRet = EN_AT_RESULT_OK;
            break;
        }
        case EN_AUTO_TEST_CI_CMD_GET_CURRENT_PROGRAM_LCN: // 18
        {
            printf("EN_AUTO_TEST_CI_CMD_GET_CURRENT_PROGRAM_LCN \n");
            
            MEMBER_SERVICETYPE serviceType;
            WORD wLCN;
            WORD wCurPosIdx;
            
            serviceType = msAPI_CM_GetCurrentServiceType();
            wCurPosIdx = msAPI_CM_GetCurrentPosition(serviceType);
            
            if(wCurPosIdx == INVALID_PROGRAM_POSITION)
            {
                printf("NO CHANNEL\n");
                eRet = EN_AT_RESULT_ER;
                break;
            }
            wLCN = msAPI_CM_GetLogicalChannelNumber(E_SERVICETYPE_DTV,wCurPosIdx);
            snprintf(tmp, sizeof(tmp), "%d\n\n",wLCN);
            
            eRet = EN_AT_RESULT_OK;
            break;
        }
        case EN_AUTO_TEST_CI_CMD_GET_CI_STATUS: // 19
        {
            printf("EN_AUTO_TEST_CI_CMD_GET_CI_STATUS \n");
            if(msAPI_CI_CardDetect())
            {
                snprintf(tmp, sizeof(tmp), "CI Insert Status\n");
                eRet = EN_AT_RESULT_OK;
            }
            else
            {
                snprintf(tmp, sizeof(tmp), "CI Remove Status\n");
                eRet = EN_AT_RESULT_ER;
            }
            break;
        }
        default:
        {
            printf("Wrong SubCmdType! \n");
            eRet = EN_AT_RESULT_ER;
            break;
        }
    }
    MApp_AT_Msg_Add((U8*)tmp);
    return eRet;
}
#endif
#endif
