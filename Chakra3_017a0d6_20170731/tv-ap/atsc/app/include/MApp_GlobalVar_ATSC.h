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

#ifndef MAPP_GlOBALVAL_ATSC_H
#define MAPP_GlOBALVAL_ATSC_H

#include "mapp_closedcaption.h"

#ifdef MAPP_MAIN_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

INTERFACE MS_CHANNEL_SETTING stChSetting;
INTERFACE MS_VIRTUAL_CHANNEL g_stPreVirtualCh;
INTERFACE MS_VIRTUAL_VCT_CHANNEL *pstVirtualCh_VCT;
INTERFACE MS_VIRTUAL_CHANNEL g_stVirtualCh; // current virtual channel
#if ENABLE_ATSC_CHLIST_DISP_TOGETHER
INTERFACE MS_CHANNEL_SETTING stChSettingDisp[2];
#endif
INTERFACE MS_U8 fUpdateDataBase;

INTERFACE U8 u8CandidateAudioNum;  //This variable must lower than MAX_AUD_LANG_NUM
INTERFACE U8 u8CandidateAudioIndex[MAX_AUD_LANG_NUM_ATSC];
INTERFACE U32 start_decode_audio_time;     //  the time we set a new prefer audio PID, and start the audio decoder
INTERFACE S8 unchecked_audio_track_num; //  number of remaing audio tracks that are not checked yet
INTERFACE U8 u8AudioType;

INTERFACE U32 u32ChListKeyPressStartTime;

INTERFACE U32 g_u32AutoIrDecodeData;
INTERFACE BOOLEAN g_bExecuteAUTOIrResponse;

//NeedCheck, if other define need???? or rename
INTERFACE BOOLEANS  g_globalVal;
#define bIsScanNSTCState            g_globalVal.bBOOL_0
#define bEpgEventSorted             g_globalVal.bBOOL_1
#define bFlagTrackChecker           g_globalVal.bBOOL_2
#define bChListKeyPress             g_globalVal.bBOOL_3
#define g_bIsFastEtt                g_globalVal.bBOOL_4
#define g_bFastEttUTF16             g_globalVal.bBOOL_5


#define STRBUFF_LENGTH_ATSC  512 //256


//NeedCheck, at CK2_ATSC, this declare at msAPI_Global.h
INTERFACE U32 gU32TVScanTotalTime ;

INTERFACE ST_TIME stDate;

INTERFACE U8 iu8Loop_k,iu8Loop_l;
INTERFACE U8 iu8Buffer_i,iu8Buffer_j,iu8Buffer_k,iu8Buffer_l;

INTERFACE U16 iu16Loop_j;
INTERFACE U16 iu16Buffer_i,iu16Buffer_j,iu16Buffer_k,iu16Buffer_l,iu16Buffer_m;

INTERFACE U32 iu32Loop_i;
INTERFACE U32 iu32Buffer_i, iu32Buffer_j;

INTERFACE U16 *iu16Ptr;

INTERFACE MS_EPG_RATING stPMTRatinginfo; //20120515Max Seperate pmt eit rating storage location

INTERFACE MS_SOUND_TRACK_ATSC astgSoundTrack[MAX_AUD_LANG_NUM_ATSC];

// Move to mapp_psip.c
//INTERFACE U8 au8CompoenetDesBuff[MAX_CND_BUFF_LENGTH]; //CND string buffer

//INTERFACE U16 u16AudioPID;
INTERFACE U8 fEnableClosedCaptionFunc;
INTERFACE U8 g_u8CCType_Option;

INTERFACE U8 u8PreSignalSNR;
INTERFACE U8 u8SlaveOSDWinId;//For Mute OSD

#if(ENABLE_ATSC_EPG_DB_2016)
INTERFACE MS_EPG_EVENT_New stEpgEventInfo;
#else
INTERFACE MS_EPG_EVENT stEpgEventInfo;
#endif


#if (PARSING_CC_WHENMUTE)
extern MS_U8 fEnableCCWhenMuteFunc;
#endif
INTERFACE U32 gU32TVScanQAMTime ;
#define TVSCAN_QAM_SETUP()  do{ gU32TVScanQAMTime = msAPI_Timer_GetTime0(); }while(0)
#define TVSCAN_QAM_CHECK()  do{ printf("TVSCAN_QAM_CHECK : %s %d,Running[%ld]ms\n",__FILE__, (int)__LINE__, msAPI_Timer_DiffTimeFromNow(gU32TVScanQAMTime));\
                            gU32TVScanQAMTime = msAPI_Timer_GetTime0();} while(0)



INTERFACE U8 g_u8CurrentRRT_Dimension;  // 0 based...
INTERFACE U8 g_u8CurrentRRT_Option;  // 0 based...
INTERFACE U8 g_u8CurrentRRT_1stDimension_Item;  // 0 based...
INTERFACE U8 g_u8CurrentRRT_1stOption;  // 0 based...
INTERFACE U8 g_u8CurrentRRT_Descriptor[REGION5_RATING_DES_MAX_LENGTH];

#if (ENABLE_AUDIO_ONLY_CUSTOMERMODE ==1)
INTERFACE EN_ADUIO_ONLY g_AudioOnly;
INTERFACE MS_U8 fEnableAudioOnlyFunc;
INTERFACE U32 u32MonitorAudioOnlyTimer;
#define AUDIO_ONLY_TIMER        5000ul
#endif


// ============ CC Selection Menu Defines ==============
typedef enum
{
    CAPTIONMENU_SERVICE_OFF =0,
    CAPTIONMENU_SERVICE_CC1,
    CAPTIONMENU_SERVICE_CC2,
    CAPTIONMENU_SERVICE_CC3,
    CAPTIONMENU_SERVICE_CC4,
    CAPTIONMENU_SERVICE_TEXT1,
    CAPTIONMENU_SERVICE_TEXT2,
    CAPTIONMENU_SERVICE_TEXT3,
    CAPTIONMENU_SERVICE_TEXT4,
    CAPTIONMENU_SERVICE_SERVICE1,
    CAPTIONMENU_SERVICE_SERVICE2,
    CAPTIONMENU_SERVICE_SERVICE3,
    CAPTIONMENU_SERVICE_SERVICE4,
    CAPTIONMENU_SERVICE_SERVICE5,
    CAPTIONMENU_SERVICE_SERVICE6,
    CAPTIONMENU_SERVICE_NUM,
    CAPTIONMENU_DIGITAL_SEVICE_NUM = CAPTIONMENU_SERVICE_NUM,
    CAPTIONMENU_ANALOG_SEVICE_NUM = CAPTIONMENU_SERVICE_TEXT4 + 1
} EN_CAPTIONMENU_SERVICE_TYPE;




//******************************************************************************

#undef INTERFACE

//******************************************************************************

#endif // #ifndef MAPP_GlOBALVAL_ATSC_H

