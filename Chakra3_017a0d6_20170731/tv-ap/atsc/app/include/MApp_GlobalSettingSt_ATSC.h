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

#ifndef MAPP_GLOBALSETTINGST_ATSC_H
#define MAPP_GLOBALSETTINGST_ATSC_H

#include "Board.h"

#if (ENABLE_ATSC)

//==============================================================================
/*                              Include files                                   */
//==============================================================================
//#include "apiXC_PCMonitor.h"
#if(ATSC_CC != NO_CC)
#include "msAPI_cc_parser.h"
#include "msAPI_cc_sysinfo.h"
#endif

//#include "MApp_Picture_Setting.h"
#include "MApp_EpgDB_ATSC.h"
#include "msAPI_Demod_ATSC.h"

//==============================================================================
/*                                 Macro                                        */
//==============================================================================
#define MAX_AUD_LANG_NUM_ATSC                5
#define MAX_LENGTH_OF_SERVICE_NAME      16
#define ANT_TYPE stGenSetting.stScanMenuSetting.u8Antenna

#if (ENABLE_ATSC_1000_CHANNEL)
#define MAX_NUM_OF_AIR_VIR_CH           1000
#define MAX_NUM_OF_CATV_VIR_CH          1000
#else
#define MAX_NUM_OF_AIR_VIR_CH           500//199
#define MAX_NUM_OF_CATV_VIR_CH          500//599 //mengfu-T2; 599
#endif

#define MAX_AIR_PHYSICAL_CH_NUM         70  //2~69
#define MAX_CATV_PHYSICAL_CH_NUM        136 //1~135

//#define MAX_CND_BUFF_LENGTH             256

#define INVALID_SERVICE_IDX             0x00         // service index starts from 1


#define SCRAMBLE_AUDIO        BIT0
#define SCRAMBLE_VIDEO        BIT1
#define INVALID_MINOR_NUMBER        0x8000

#if ENABLE_ATSC_CHLIST_DISP_TOGETHER
#define PHY_CH_IDX_AIR(ch_idx)          (stChSettingDisp[ANT_AIR].astMainList[ch_idx].u8PhysicalChIdx)
#define VIR_CHINFO_IDX_AIR(ch_idx)        (stChSettingDisp[ANT_AIR].astPhysicalCh[PHY_CH_IDX_AIR(ch_idx)].u16VirChInfoStartIdx + stChSettingDisp[ANT_AIR].astMainList[ch_idx].u8VirChInfoIdx)
#define VIR_CH_IDX_AIR(ch_idx)            (stChSettingDisp[ANT_AIR].astVirtualChInfo[VIR_CHINFO_IDX_AIR(ch_idx)].u16VirChIdx)

#define PHY_CH_IDX_CATV(ch_idx)          (stChSettingDisp[ANT_CATV].astMainList[ch_idx].u8PhysicalChIdx)
#define VIR_CHINFO_IDX_CATV(ch_idx)        (stChSettingDisp[ANT_CATV].astPhysicalCh[PHY_CH_IDX_CATV(ch_idx)].u16VirChInfoStartIdx + stChSettingDisp[ANT_CATV].astMainList[ch_idx].u8VirChInfoIdx)
#define VIR_CH_IDX_CATV(ch_idx)            (stChSettingDisp[ANT_CATV].astVirtualChInfo[VIR_CHINFO_IDX_CATV(ch_idx)].u16VirChIdx)

#define PHY_CH_IDX(ch_idx)          (stChSetting.astMainList[ch_idx].u8PhysicalChIdx)
#define VIR_CHINFO_IDX(ch_idx)        (stChSetting.astPhysicalCh[PHY_CH_IDX(ch_idx)].u16VirChInfoStartIdx + stChSetting.astMainList[ch_idx].u8VirChInfoIdx)
#define VIR_CH_IDX(ch_idx)            (stChSetting.astVirtualChInfo[VIR_CHINFO_IDX(ch_idx)].u16VirChIdx)
#else
#define PHY_CH_IDX(ch_idx)          (stChSetting.astMainList[ch_idx].u8PhysicalChIdx)
#define VIR_CHINFO_IDX(ch_idx)        (stChSetting.astPhysicalCh[PHY_CH_IDX(ch_idx)].u16VirChInfoStartIdx + stChSetting.astMainList[ch_idx].u8VirChInfoIdx)
#define VIR_CH_IDX(ch_idx)            (stChSetting.astVirtualChInfo[VIR_CHINFO_IDX(ch_idx)].u16VirChIdx)
#endif

#define SET_DIR_CH_ATSC(ch_idx, FLAG)    (stChSetting.astVirtualChInfo[VIR_CHINFO_IDX(ch_idx)].fIsDirCh = FLAG)
#define SET_FAV_CH_ATSC(ch_idx, FLAG)    (stChSetting.astVirtualChInfo[VIR_CHINFO_IDX(ch_idx)].fIsFavCh = FLAG)
#define SET_HIDE_CH_ATSC(ch_idx, FLAG)    (stChSetting.astVirtualChInfo[VIR_CHINFO_IDX(ch_idx)].fIsHideCh = FLAG)
#define IS_HIDE_CH_ATSC(ch_idx)          stChSetting.astVirtualChInfo[VIR_CHINFO_IDX(ch_idx)].fIsHideCh
#define IS_FAV_CH_ATSC(ch_idx)            (stChSetting.astVirtualChInfo[VIR_CHINFO_IDX(ch_idx)].fIsFavCh)

//NeedCheck, original at msapi_global.h in CK2_ATSC
#if ENABLE_TVSCANSTEPTIME
INTERFACE U32 gU32TVScanStepTime ;
#define TVSCAN_STEP_SETUP()  do{ gU32TVScanStepTime = msAPI_Timer_GetTime0(); }while(0)
#define TVSCAN_STEP_CHECK()  do{ printf("TVSCAN_STEP_CHECK: %s %d,Running[%ld]ms\n",__FILE__, (int)__LINE__, msAPI_Timer_DiffTimeFromNow(gU32TVScanStepTime));\
                                                     } while(0)
#else
#define TVSCAN_STEP_SETUP()
#define TVSCAN_STEP_CHECK()
#endif

#ifdef DISABLE_COMPONENT_VBI
#define IsVBISrcInUse()        (!IsVgaInUse() && !IsHDMIInUse() && !IsStorageInUse() && !IsYPbPrInUse())
#else
#define IsVBISrcInUse()        (!IsVgaInUse() && !IsHDMIInUse() && !IsStorageInUse() )
#endif

//==============================================================================
//                                 Enum
//==============================================================================
////Channel proc///
typedef enum
{
    MAIN_LIST,
    FAV_LIST,
    DISP_LIST,
} EN_LIST_TYPE;

//there is EN_SCAN_TYPE, can use it, but later
typedef enum
{
    AUTO_SCAN,
    MANUAL_SCAN,
    SCAN_TYPE_NUM_ATSC //SCAN_TYPE_NUM not use at Ck2_ATSC
} EN_SCAN_TYPE_ATSC;

typedef enum
{
    VIDEO_STREAM_TYPE_MPEG1,
    VIDEO_STREAM_TYPE_MPEG2,
    VIDEO_STREAM_TYPE_OPTION_MPEG2,
    VIDEO_STREAM_TYPE_H264,
    VIDEO_STREAM_TYPE_H265,
    VIDEO_STREAM_TYPE_UNKOWN
} EN_VIDEO_STREAM_TYPE;

typedef enum
{
    AUDIO_ONLY_OFF,
    AUDIO_ONLY_ON,
    AUDIO_ONLY_NUM
} EN_ADUIO_ONLY;

typedef enum
{
    AUD_STREAM_TYPE_MPEG,
    AUD_STREAM_TYPE_AC3,
    AUD_STREAM_TYPE_AAC,
    AUD_STREAM_TYPE_NUMS,
} EN_AUD_STREAM_TYPE;

typedef enum
{
    CABLE_SYSTEM_STD,
    CABLE_SYSTEM_IRC,
    CABLE_SYSTEM_HRC,
    CABLE_SYSTEM_AUTO,
    CABLE_SYSTEM_TYPE_NUM
} EN_CABLE_SYSTEM_TYPE;

typedef enum
{
    SOUND_MAIN_AUDIO,
    SOUND_VI,
    SOUND_HI
}EN_ACCESSIBILITY;

typedef enum
{
    SOUND_ACCESSIBILITY,
    SOUND_AUDIO_LANGUAGE
}EN_PRIMART_AUDIO_PARAMETER;

typedef enum
{
    DAP_SOUND_LANGUAGE_ENGLISH,
    DAP_SOUND_LANGUAGE_FRENCH,
    DAP_SOUND_LANGUAGE_SPANISH,
}EN_DAP_AUDIO_LANGUAGE;

#if(ENABLE_ATSC_VIDEO_DESC)
typedef enum
{
    EN_VIDEO_DESCRIPTION_ITEM_ON,
    EN_VIDEO_DESCRIPTION_ITEM_OFF,
}EN_VIDEO_DESCRIPTION_ITEM;
#endif

#if (ENABLE_UI_SPDIF_SETTING==ENABLE)
typedef enum
{
    EN_SPDIF_MODE_PCM = 0,
    EN_SPDIF_MODE_NON_PCM,
    EN_SPDIF_MODE_NUM,
} EN_AUD_SPDIF_MODE;
#endif

typedef enum
{
    TIME_AUTO_SYNC_OFF,
    TIME_AUTO_SYNC_ON,
    TIME_AUTO_SYNC_ITEM_NUM
} EN_TIME_AUTO_SYNC_ITEM;

#if(ENABLE_ATSC)
#if EN_INPUT_LABEL_EDIT
typedef enum
{
    InputLabel_Default,
    InputLabel_Antenna,
    InputLabel_Cable,
    InputLabel_Satellite,
    InputLabel_DTV,
    InputLabel_DVD,
    InputLabel_Blu_ray,
    InputLabel_HD_DVD,
    InputLabel_XBOX,
    InputLabel_Wii,
    InputLabel_PS3,
    InputLabel_Game,
    InputLabel_Computer,
    InputLabel_VCR,
    InputLabel_DV,
    InputLabel_Num
}EN_INPUT_LABEL_PRESENT_TYPE;
#endif
#endif



typedef struct
{
    U8 u8_150Hz;
    U8 u8_500Hz;
    U8 u8_1000Hz;
    U8 u8_2000Hz;
    U8 u8_4000Hz;
} stSoundEqSetting;


//==============================================================================
/*                                 Structure                                    */
//==============================================================================

//NeedCheck, maybe can use dvb TP setting, now replace all MS_TP_SETTING_ATSC, at atsc app folder, and msapi_scan_atsc
typedef struct
{
    U16 u16Frequency;  //(50,000 ~ 860,000 Khz)/Tuner_Step
    U8 fModulation :2; //0:NTSC 1:256QAM 2:64QAM 3:8VSB
    U8 fSpectrum :2;   //0:normal 1:inverter 2:auto-tune
    U8 reserved :4;
} ATTR_PACK MS_TP_SETTING_ATSC;

///// MGT ////////////////////////////////////////////////////////////////////////////////
typedef struct
{
    //U16 table_type;
    U16 table_type_PID:13;
    U16 fDoNotRetrieveTable:1; //TRUE= not retrieve table, FALSE= retrieve table again
    U16 Reserved:2;
    U8 table_type_version_number;
} MS_MGT_ITEM;

typedef struct
{
    U8 version_number;

#if (ENABLE_ATSC_EPG_DB_2016)
    MS_MGT_ITEM astEitItem[NEW_MAX_TAB_NUM]; //EIT-0~55
    MS_MGT_ITEM astEttItem[NEW_MAX_TAB_NUM]; //ETT-0~55
#else
    MS_MGT_ITEM astEitItem[MAX_TBL_NUM]; //EIT-0~7
    MS_MGT_ITEM astEttItem[MAX_TBL_NUM]; //ETT-0~7
#endif

    MS_MGT_ITEM stVctItem;
#if (ENABLE_MEXICO_VCHIP)
    U8 u8RrtRegionNo;
#endif
} MS_MGT_ST;

///// EAS ////////////////////////////////////////////////////////////////////////////////
#define MAX_LENGTH_OF_EVENT_CODE    5       // EAS: max length of EAS event code
#define MAX_LENGTH_OF_NAT_ACT_TEXT  128       // EAS: max length of nature of activation text
#define MAX_LENGTH_OF_ALERT_TEXT  512       // EAS: max length of alert text
#define MAX_COUNT_OF_LOCATION_CODE 31       // EAS: max count of location code
#define MAX_COUNT_OF_EXCEPTION 31           // EAS: max count of exception

typedef struct
{
    U16 u16MajorNum;
    U16 u16MinorNum;
    U16 u16AlertTextLength;
    U8  au8AlertText[MAX_LENGTH_OF_ALERT_TEXT];

} MS_EAS_INFO;

typedef struct
{
    U8  u8StateCode;
    U8  u8CountySubdivision;
    U16 u16CountyCode;
} MS_EAS_LOCTION_CODE;

typedef struct
{
    BOOL bInBandRef;
    U16  u16ExcMajorNum:10;
    U16  u16ExcMinorNum:10;
    U16  u16ExcOOB_SrcID;
} MS_EAS_EXCEPTION;

typedef struct
{
    U8  version_number;             // sequence number
    U16 u16EAS_EventID;
    U8  au8EAS_OriginatorCode[3];
    U8  au8EAS_EventCode[MAX_LENGTH_OF_EVENT_CODE];
    U8  au8NatActText[MAX_LENGTH_OF_NAT_ACT_TEXT];
    U8  u8AlertTimeRemain;          // seconds, range: 0~120
    U32 u32EventStartTime;
    U16 u16EventDuration;           // minutes, range: 15~6000
    U8  Reserved:4;
    U8  u8AlertPriority:4;
    U16 u16DetailsOOB_SrcID;
    U16 u16DetailsMajorNum;
    U16 u16DetailsMinorNum;
    U16 u16AudioOOB_SrcID;
    U16 u16AlertTextLength;
    U8  au8AlertText[MAX_LENGTH_OF_ALERT_TEXT];
    MS_EAS_LOCTION_CODE astLoctionCode[MAX_COUNT_OF_LOCATION_CODE];  // range:1~31
    U8  u8ExceptionCount;
    MS_EAS_EXCEPTION    astException[MAX_COUNT_OF_EXCEPTION];
} MS_EAS_ST;
///// EAS END ////////////////////////////////////////////////////////////////////////////////

typedef struct //__attribute__ ((__packed__))
{
    U8 u8PhysicalChIdx;
    U8 u8VirChInfoIdx:7;  // 0 ~ MAX_VC_PER_PHYSICAL-1
    U8 Reserved:1;
} ATTR_PACK MS_MAINLIST_A;

typedef struct //__attribute__ ((__packed__))
{
    U16 major_num;
    U16 minor_num;
    U16 u16ChannelTsid;
    U8 u8VCTsctionNumber;
 #if (ONE_PART_CHNO==ENABLE)
   #if(ENABLE_NONDUPLICATE_PROGRAM_NAME == ENABLE)
        U8 fIsOnePartChNum:1;
        U8 fIsNoVctCh:1;
        U8 u8VideoStreamType:3;
        U8 u8Reserved:3;
   #else
        U8 fIsOnePartChNum:1;
        U8 u8VideoStreamType:3;
        U8 u8Reserved:4;
   #endif
 #endif
    U16 u16HideGuide:1;
    U16 u16HiddenFlag:1;
#if KOR_HIDE_3D_CHANNEL
    U16 u16fIs3DChannel:1;
#endif
} ATTR_PACK MS_VIRTUAL_CHANNEL_NUM;

typedef struct //__attribute__ ((__packed__))
{
    U16 u16AudioPid:13;
    U16 u16AudStreamType:2; //0=Mpeg, 1=AC3, 2= AAC
    U16 u16IsAudLangGetinPMT:1;

    U16 u8AudLangIdx:4;
    U16 u8AudPidInPMT:1;  // if this audio pid in PMT
    U16 u8AudAc3Bsmod:4;
    U16 u16AC3inPMT:1;
    U16 u8Priority:2;
    U16 u8Reserved:3;
} ATTR_PACK MS_SOUND_TRACK_ATSC;

#if 1//(NEW_VIRTUAL_CHANNEL_STRUCTURE == ENABLE)

typedef struct //__attribute__ ((__packed__))
{
    MS_TP_SETTING_ATSC stTPSetting;      ///3byte, 4 nibble remind
    U16 u8PatVersion:5;
    U16 u8PmtVersion:5;
    U16 u8VctVersion:5;
    U16 Reserved1:1;

    U16 u16TsId;

    U8  u8NumOfPatItem; // Channel number in PAT

} ATTR_PACK MS_RF_CHANNEL_new;

typedef struct //__attribute__ ((__packed__))
{
    U8 acServiceName[16];               ///16 byte
    U16 u16PcrPid:13;                       ///2byte
    U16 u16ScrambleChStatus:2;
    U16 bChannelFromVCT:1;

    U16 u16VideoPid:13;                     ///2byte, 1 nibble remind
    //U16 CharIdxLength:1;  // CHAR_IDX_1BYTE=1 byte, CHAR_IDX_2BYTE=2 bytes
    U16 fIsScrambleCh:1;  // 0=FTA, 1=Scramble
    U16 bScrambleCH:1;

    MS_SOUND_TRACK_ATSC astSoundTrack[MAX_AUD_LANG_NUM_ATSC];       ///15byte: 3byte*5, 1 nibble remind
    MS_VIRTUAL_CHANNEL_NUM stVirtualChNum;

    U16 u8AudLangNum:3;    // <= MAX_AUD_LANG_NUM
    U16 u16PmtPid:13;

    U16 u16ProgramNumber;
    U16 u16SourceId;

    U16 u16PatSectionNum:8;
    U16 u16StillPic:1;
    U16 u16Reserve:6;     // for sec scramble channel

    U8 u8ServiceType;
    U8 u8RfNum;               ///1byte

} ATTR_PACK MS_VIRTUAL_CHANNEL;

#else

typedef struct
{
    U8 acServiceName[MAX_LENGTH_OF_SERVICE_NAME];
    MS_TP_SETTING_ATSC stTPSetting;
    U16 u16PcrPid:13;
    U16 u16ScrambleChStatus:2;
    U16 u16VCTStatus:1;

    U16 u16VideoPid:13;
    //U16 CharIdxLength:1;  // CHAR_IDX_1BYTE=1 byte, CHAR_IDX_2BYTE=2 bytes
    U16 fIsScrambleCh:1;  // 0=FTA, 1=Scramble
    U16 u16StillPic:1;

    MS_SOUND_TRACK_ATSC astSoundTrack[MAX_AUD_LANG_NUM_ATSC];
    MS_VIRTUAL_CHANNEL_NUM stVirtualChNum;

    U8 u8VctVersion:5;
    U8 u8AudLangNum:3;    // <= MAX_AUD_LANG_NUM

#if ENABLE_PAT_MUTISECTION
    U16 u8PatVersion:5;
    U16 u16PatSectionNum:4;
    U16 u8PmtVersion:5;
    //U16 u16HideGuide:1;
    //U16 u16HiddenFlag:1;

    U16 u16PmtPid:13;
    U16 bChannelFromVCT:1;
    U16 bScrambleCH:1;
    U16 Reserved3:1;
#else
    U8 u8PatVersion:5;
    U8 bChannelFromVCT:1;
    U8 bScrambleCH:1;
    U8 Reserved1:1;

    U16 u16PmtPid:13;
    //U16 u16HideGuide:1;
    //U16 u16HiddenFlag:1;
    U16 Reserved2:1;

    U8 u8PmtVersion:5;
    U8 Reserved3:3;
#endif

    U8 u8ServiceType;
    U16 u16TsId;

    U16 u16ProgramNumber;
    U16 u16SourceId;
    #if 1//(ENABLE_MAX_RRT_DIMENSION_NUMBER == 1)
    U8  u8NumOfPatItem;
    #endif
} MS_VIRTUAL_CHANNEL;
#endif

typedef struct
{
    U8 u8NumOfVirCh;
    U16 u16VirChInfoStartIdx:10;
    U16 Reserved:6;
} MS_PHYSICAL_CHANNEL;

typedef struct
{
    U16 u16PcrPid:13;
    U16 Reserved1:3;
    U16 u16VideoPid:13;
    U16 Reserved2:3;
    U8 u8AudLangNum:3;
    U8 Reserved3:5;
    MS_SOUND_TRACK_ATSC astSoundTrack[MAX_AUD_LANG_NUM_ATSC];

}MS_VIRTUAL_VCT_CHANNEL;

typedef struct //__attribute__ ((__packed__))
{
    U16 u16VirChIdx:10;
    U16 fIsDirCh:1;
    U16 fIsFavCh:1;
    U16 fIsHideCh:1;
    U16 Reserved:3;

} ATTR_PACK MS_VIRTUAL_CHANNEL_INFO;

typedef struct
{
    U32 u32MagicCode_1;
    U8 au8VirChTbl[MAX_NUM_OF_CATV_VIR_CH/8+1]; // Coverity 95839
    MS_PHYSICAL_CHANNEL astPhysicalCh[MAX_CATV_PHYSICAL_CH_NUM];
    MS_VIRTUAL_CHANNEL_INFO astVirtualChInfo[MAX_NUM_OF_CATV_VIR_CH+1];
    MS_MAINLIST_A astMainList[MAX_NUM_OF_CATV_VIR_CH+1];
    U16 au16FavList[MAX_NUM_OF_CATV_VIR_CH+1];
    U16 u16MainListSrvNum;        // total service # of Main List
#ifdef MAINLISTSRV_ANALOGCH_NUM
    U16 u16MainListAnalogCHNum;
#endif
    U16 u16DispListSrvNum;     // total service # of Display List
    U16 u16FavListSrvNum;      // total service # of Favotire List
    U16 u16TotalHideSrvNum;    // total Hide service number
    U16 u16TotalDirTuneSrvNum; // total Hide service number
    //U32 U32DatabaseMagicCodeEnd;
    //U32 U32DatabaseMagicCodeEndExt;
    U32 u32MagicCode_2;
} MS_CHANNEL_SETTING;

/*
typedef struct
{
    U16 u16CheckSum;
    U8 u8Test;

} StuAtscSysSetting;
*/


#define INPUT_BLOCK_TV        BIT0
#define INPUT_BLOCK_AV        BIT1
#define INPUT_BLOCK_SV        BIT2
#define INPUT_BLOCK_YPBPR     BIT3
#define INPUT_BLOCK_SCART     BIT4
#define INPUT_BLOCK_HDMI      BIT5
#define INPUT_BLOCK_PC        BIT6

#define SCRAMBLE_AUDIO        BIT0
#define SCRAMBLE_VIDEO        BIT1

#if 0 //----VChip data moving
#define VCHIP_TVRATING_ALL    BIT5
#define VCHIP_TVRATING_FV     BIT4
#define VCHIP_TVRATING_V      BIT3
#define VCHIP_TVRATING_S      BIT2
#define VCHIP_TVRATING_L      BIT1
#define VCHIP_TVRATING_D      BIT0
#define VCHIP_TVRATING_VSL    0x0E
#define VCHIP_TVRATING_VSLD   0x0F

typedef struct
{
    U8 Item_TV_NONE;
    U8 Item_TV_Y;
    U8 Item_TV_Y7;
    U8 Item_TV_G;
    U8 Item_TV_PG;
    U8 Item_TV_14;
    U8 Item_TV_MA;
} MS_VCHIP_TV_ITEM;

typedef struct
{
    U16 vchipSettingCS;// check sum <<checksum should be put at top of the struct, do not move it to other place>>

    U8 u8VChipLockMode:4;
#if ENABLE_UNRATED_LOCK
    U8 u8UnRatedLock:4;
#else
    U8 u8VChipReserved:4;
#endif
    U8 u8VChipMPAAItem;
    U8 u8VChipCEItem;
    U8 u8VChipCFItem;
    U16 u16VChipPassword;
    U8 u8InputBlockItem;
    MS_VCHIP_TV_ITEM stVChipTVItem;
} MS_VCHIP_SETTING;

typedef struct
{
    U8 u8EIA608Data1;
    U8 u8EIA608Data2;
    U8 RatingType;
    U8 RatingLevel;
    U8 TV_FVSLD;
    U8 MPAALevel;
    U8 CanEngLevel:4;
    U8 CanFreLevel:4;
#if defined(ENABLE_PARSE_SAME_DIMENSION_IN_RRT5_CAD) && ENABLE_PARSE_SAME_DIMENSION_IN_RRT5_CAD
    U16 u8DimVal0;
    U16 u8DimVal1;
    U16 u8DimVal2;
    U16 u8DimVal3;
    U16 u8DimVal4;
    U16 u8DimVal5;
    U16 u8DimVal6;
    U16 u8DimVal7;
    U16 u8DimVal8;
    U16 u8DimVal9;
  #if (ENABLE_MAX_RRT_DIMENSION_NUMBER)
    U16 u8DimVal10;
    U16 u8DimVal11;
    U16 u8DimVal12;
    U16 u8DimVal13;
    U16 u8DimVal14;
    U16 u8DimVal15;
    U16 u8DimVal16;
    U16 u8DimVal17;
    U16 u8DimVal18;
    U16 u8DimVal19;
    U16 u8DimVal20;
    U16 u8DimVal21;
    U16 u8DimVal22;
    U16 u8DimVal23;
    U16 u8DimVal24;
    U16 u8DimVal25;
    U16 u8DimVal26;
    U16 u8DimVal27;
    U16 u8DimVal28;
    U16 u8DimVal29;
    U16 u8DimVal30;
    U16 u8DimVal31;
    U16 u8DimVal32;
    U16 u8DimVal33;
    U16 u8DimVal34;
    U16 u8DimVal35;
    U16 u8DimVal36;
    U16 u8DimVal37;
    U16 u8DimVal38;
    U16 u8DimVal39;
    U16 u8DimVal40;
  #endif
#else
    U8 u8DimVal0:4;
    U8 u8DimVal1:4;
    U8 u8DimVal2:4;
    U8 u8DimVal3:4;
    U8 u8DimVal4:4;
    U8 u8DimVal5:4;
    U8 u8DimVal6:4;
    U8 u8DimVal7:4;
    U8 u8DimVal8:4;
    U8 u8DimVal9:4;
#endif
} MS_VCHIP_RATING_INFO;

#endif


#if (ENABLE_MAX_RRT_DIMENSION_NUMBER)
    #define REGION5_DIMENSION_NUM               41
    #define REGION5_MAX_RATING_OPTION           20
#else
    #define REGION5_DIMENSION_NUM               10
    #define REGION5_MAX_RATING_OPTION           15
#endif
#define REGION5_DIMENSIONNAME_MAX_LENGTH    24  // 2(to Record Actuall Length)+ 20 (REGION5_DIMENSIONNAME_MAX_LENGTH) + 2 (additional 2 Null-terminated character)
#define REGION5_RATING_TEXT_MAX_LENGTH      12 // 2(to Record Actuall Length) + 8 (REGION5_RATING_TEXT_MAX_LENGTH) + 2(additional 2 Null-terminated character)
#define REGION5_RATING_DES_MAX_LENGTH       44 // 2(to Record Actuall Length) + 100 (REGION5_RATING_DES_MAX_LENGTH) + 2(additional 2 Null-terminated character (should be 151 to follow spec.))

#define MAX_RRT_SAVED   REGION5_DIMENSION_NUM

typedef struct
{
    // U.S. Dimension
    U8   u8DimensionName[REGION5_DIMENSIONNAME_MAX_LENGTH];
    U8   u8Values_Defined;
    U32  u32CurrentOption:20;  //REGION5_MAX_RATING_OPTION
    U16  u16Graduated_Scale:1;
    U8   stRatingText[REGION5_MAX_RATING_OPTION][REGION5_RATING_TEXT_MAX_LENGTH];
} MS_REGION5_DIMENSION;


#define REGION5_NAME_MAX_LEN    36 // The max Region name length is 32. 36 is : 2(to Record Actual length) +32 (Max Region Name Length)+2(End of string bytes(NULL Bytes))
typedef struct
{
    // U.S. region 5 Rating
    U16 RagionRatingSettingCS;// check sum <<checksum should be put at top of the struct, do not move it to other place>>
    U8  u8VersionNo;
    U8  u8NoDimension;
    U8  u8LastUpdateRegion;

    U8 u8NoSavedRRT;
    U8 u8IdxLastSavedRRT;

    U8  u8Region5Name[REGION5_NAME_MAX_LEN];   // The max Region name length is 32. 36 is : 2(to Record Actual length) +32 (Max Region Name Length)+2(End of string bytes(NULL Bytes))
    MS_REGION5_DIMENSION stRegin5Dimension[REGION5_DIMENSION_NUM];
} MS_REGION5_RATING; //1307 bytes
//-----------------------------------------------------------------------------
typedef struct
{
    U8   u8Values_Defined;
    U32  u32CurrentOption:20;  //REGION5_MAX_RATING_OPTION
    U16  u16Graduated_Scale:1;
} MS_EZ_REGION5_DIMENSION;

#define EZ_REGION5_NAME_MAX_LEN     33 // The max Region name length is 32. 36 is : 2(to Record Actual length) +32 (Max Region Name Length)+2(End of string bytes(NULL Bytes))
typedef struct
{
    U8  u8VersionNo;
    U8  u8NoDimension;
    U8  u8EZRegion5Name[EZ_REGION5_NAME_MAX_LEN];   // The max Region name length is 32.
    MS_EZ_REGION5_DIMENSION stRegin5Dimension[REGION5_DIMENSION_NUM];
} MS_EZ_REGION5_RATING; //59 bytes
//-----------------------------------------------------------------------------

typedef struct
{
    U16 u16ProgramNumber;
    U16 u16BuildChNumber;
    U16 u16PID;
#if ENABLE_PAT_MUTISECTION
    U8 u8SectionNum:4;
    U8 u8Resever:4;
#endif
} MS_PAT_ITEM_ATSC;


///// ISO639 language code
typedef enum
{
    AUD_LANG_ENG, // English
    AUD_LANG_FRA, // 1st French
    AUD_LANG_SPA, // 1st Spanish
    AUD_LANG_FRE, // 2nd French
    AUD_LANG_ESL, // 2nd Spanish
    AUD_LANG_KOR, // Korean
    AUD_LANG_JPN, // Japan
    AUD_LANG_CHI, // Chinese
    AUD_LANG_NUM, // maximum aud language
    AUD_LANG_UND = 0x0F// Undetermined//U8 u8AudLangIdx:4;
} EN_AUD_LANG;

typedef enum
{
    SOUND_AUDIO_LAN_ENGLISH,
    SOUND_AUDIO_LAN_FRENCH,
    SOUND_AUDIO_LAN_SPANISH,
    SOUND_AUDIO_LAN_FRENCH2,
    SOUND_AUDIO_LAN_SPANISH2,
    SOUND_AUDIO_LAN_KOREA,
    SOUND_AUDIO_LAN_JAPAN,
    SOUND_AUDIO_LAN_CHINESE,
    SOUND_AUDIO_LAN_RUS,
    SOUND_AUDIO_LAN_POR,
    SOUND_AUDIO_LAN_HIN,
    SOUND_AUDIO_LAN_ZHO,
    SOUND_AUDIO_LAN_NUM,
    SOUND_AUDIO_LANG_UND = 0x0F// Undetermined //U8 u8AudLangIdx:4;
} EN_ADUIO_LAN;

typedef enum
{
    SOUND_AUDIO_DIGITAL_DEFAULT,
    SOUND_AUDIO_DIGITAL_AUTO,
    SOUND_AUDIO_DIGITAL_NUM
} EN_DIGITAL_AUDIO_SECLECTION;

typedef struct
{
    U8 au8AudLangCode[3];
    EN_AUD_LANG enAudLangIndex;
} ST_AUD_LANG_ATSC;

typedef enum
{
    TIME_ZONE_ATLANTIC, // GMT - 04:00
    TIME_ZONE_EASTERN,  //GMT - 05:00
    TIME_ZONE_CENTRAL,  //GMT - 06:00
    TIME_ZONE_MOUNTAIN, //GMT - 07:00
    TIME_ZONE_PACIFIC,  //GMT - 08:00
    TIME_ZONE_ALASKA,   //GMT - 09:00
    TIME_ZONE_HAWAII,   //GMT - 10:00
    TIME_ZONE_NUM
} EN_TIME_ZONE;
#if ENABLE_ATSC_TTS
typedef enum
{
    EN_VOICE_GUIDE_VOLUME_LOW,
    EN_VOICE_GUIDE_VOLUME_MEDIUM,
    EN_VOICE_GUIDE_VOLUME_HIGH,
    EN_VOICE_GUIDE_VOLUME_NUM
} EN_VOICE_GUIDE_VOLUME;

typedef enum
{
    EN_VOICE_GUIDE_PITCH_LOW,
    EN_VOICE_GUIDE_PITCH_MEDIUM,
    EN_VOICE_GUIDE_PITCH_HIGH,
    EN_VOICE_GUIDE_PITCH_NUM
} EN_VOICE_GUIDE_PITCH;

typedef enum
{
    EN_VOICE_GUIDE_SPEED_SLOW,
    EN_VOICE_GUIDE_SPEED_NORMAL,
    EN_VOICE_GUIDE_SPEED_FAST,
    EN_VOICE_GUIDE_SPEED_NUM
} EN_VOICE_GUIDE_SPEED;
#endif
//==============================================================================
/*                       Function prototype                                     */
//==============================================================================
#ifdef INTERFACE
#undef INTERFACE
#endif

#ifdef MAPP_PSIP_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

//==============================================================================
/*                       Global variable                                        */
//==============================================================================

INTERFACE MS_REGION5_RATING g_VchipRegion5;
#define stGenSettingVchipRegion5    g_VchipRegion5

#define MAX_INPUTLLABEL_CHAR_NUM    19

INTERFACE MS_VIRTUAL_CHANNEL *pstVirtualCh;

#endif // ENABLE_ATSC


//******************************************************************************

#endif //MAPP_GLOBALSETTINGST_ATSC_H

