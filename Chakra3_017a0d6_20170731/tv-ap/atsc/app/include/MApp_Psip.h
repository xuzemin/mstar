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

#ifndef MAPP_PSIP_H
#define MAPP_PSIP_H

#include "Board.h"
#include "msAPI_demux.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_EpgDB_ATSC.h"

/*****************************************************************************/
/*                                 Macro                                        */
/*****************************************************************************/
#define CRC_CHECK                1
#define NON_CRC_CHECK            0
#define MAX_NUM_OF_CRC_ERROR     1
#define ENABLE_NON_STANDARD_ISO639LANGUAGE_CODE 1
#define ENABLE_PAT_TIMEOUT_NOSIGNAL 0
#define ENABLE_DYNAMIC_UPDATE_AUDIO_LANGUAGE 0


#define INVALID_VERSION_NUM     0xFF

#define SECTION_TIME_OUT_MS     2000 /* ms */
#define PAT_SECTION_TIME_OUT_MS 350 //Max modify for spec: PAT cycle 1000ms time out 3000ms

//Ben++ for reduce getting vct table time 2011/11/03
#define TVCT_SECTION_TIME_OUT_MS     200 /* ms */
#define CVCT_SECTION_TIME_OUT_MS     2000 /* ms */

#define STT_SECTION_LENGTH      24          /* 8 bytes aligned */

// Time to monitor table
#define STT_MONITOR_PERIOD      1000 /* ms */
#define MGT_MONITOR_PERIOD      2000 /* ms */
#define VCT_MONITOR_PERIOD      2000 /* ms */
#define PAT_MONITOR_PERIOD      10000 //10000 /* ms */
#define PMT_MONITOR_PERIOD      500 //10000 /* ms */
#if ENABLE_OAD
#define PMT_OTHER_MONITOR_PERIOD    2000    /* ms */    //ABNT NBR 15603-2 Table 6
#define PMT_OTHER_MONITOR_TIMEOUT    2000    /* ms */
#endif
#define RRT_MONITOR_PERIOD      5000
#define EAS_MONITOR_PERIOD      5000

// max/min major and minor number
#define MIN_MAJOR_NO    1
#define MAX_MAJOR_NO    1023
#if (ENABLE_EXTERN_DTV_MAX_MINOR_NO)
#define MAX_MINOR_NO    65534
#else
#define MAX_MINOR_NO    999 // spec
#endif

#define PAT_MAX_SECTION_NUMBER     16 // 4 bit, refer u16PatSectionNum & u8SectionNum
#define PAT_MAX_CH_IN_MUTISECTION     1 //max channle number in PAT muti-section


/******************************************************************************/
/*                                 Enum                                       */
/******************************************************************************/
/* PID definition */
/*use  mapp_demux.h at dvb,*for ATSC merge CK3*
typedef enum
{
    // MPEG-2 PID
    PID_PAT = 0x0000,
    PID_CAT = 0x0001,
    PID_TSDT= 0x0002,

    // PSIP PID
    PID_BASE= 0x1FFB
} EN_PSIP_PID;
*/
/* TABLE ID definition */
/*use  mapp_si.h at dvb,*for ATSC merge CK3*
typedef enum
{
    // MPEG-2 table id
    TID_PAS         = 0x00,     //program_association_section
    TID_CAS         = 0x01,     //conditional_access_section
    TID_PMS         = 0x02,        //program_map_section
    TID_TSDS        = 0x03,     //transport_stream_description_section

    //PSIP table id
    TID_MGS         = 0xC7,     //master_guide_section
    TID_TVCS        = 0xC8,     //terrestrial_virtual_channel_section
    TID_CVCS        = 0xC9,     //cable_virtual_channel_section
    TID_RRS         = 0xCA,     //ratting_region_section
    TID_EIS         = 0xCB,     //event_information_section
    TID_ETS         = 0xCC,     //extended_text_section
    TID_STS         = 0xCD,     //system_time_section
    //TID_other         = 0xCE ~ 0xD2//ATSC coordinated values which are defined in other standards
    TID_DCCS        = 0xD3,     //program_association_section
    TID_DCCSCS      = 0xD4,     //program_association_section
    TID_EAS         = 0xD8,     //emergency alert signaling
    //TID_other         = 0xD5 ~ 0xDF//ATSC coordinated values which are defined in other standards
    //TID_other         = 0xE0 ~ 0xE5//other systems
    //TID_reserved      = 0xE6 ~ 0xFE//ATSC_reserved
    //TID_reserved      = 0xFF       //reserved
} EN_PSIP_TID;
*/
/* TABLE ID definition , only declare difference with DVB si declare *for ATSC merge CK3**/
typedef enum
{
    TID_EAS         = 0xD8     //emergency alert signaling
} EN_PSIP_TID_ATSC;
/* descriptor tag definition */
/*use  mapp_si.h at dvb,*for ATSC merge CK3*
typedef enum
{
    // MPEG-2 descriptor tag
    TAG_VSD         = 0x02,     //video_stream_descriptor
    TAG_ASD         = 0x03,     //audio_stream_descriptor
    TAG_HiD         = 0x04,     //hierarchy_descriptor
    TAG_RgD         = 0x05,     //registration_descriptor
    TAG_DSAD        = 0x06,     //data_stream_alignment_descriptor
    TAG_TBGD        = 0x07,     //target_background_grid_descriptor
    TAG_VWD         = 0x08,     //video_window_descriptor
    TAG_CaD         = 0x09,     //CA_descriptor
    TAG_LnD         = 0x0A,     //ISO_639_language_descriptor
    TAG_SCD         = 0x0B,     //system_clock_descriptor
    TAG_MBUD        = 0x0C,     //multiplex_buffer_utilization_descriptor
    TAG_CRD         = 0x0D,     //copyright_descriptor
    TAG_MBD         = 0x0E,     //maximum_bitrate_descriptor
    TAG_PDID        = 0x0F,     //private_data_indicator_descriptor
    TAG_SBD         = 0x10,     //smoothing_buffer_descriptor
    TAG_STDD        = 0x11,     //STD_descriptor
    TAG_IBPD        = 0x12,     //IBP_descriptor

    //PSIP descriptor tag
    TAG_StD         = 0x80,        //stuffing_descriptor
    TAG_AC3AD       = 0x81,        //AC3_audio_descriptor
    TAG_CSD         = 0x86,        //caption_service_descriptor
    TAG_CAD         = 0x87,        //content_advisory_descriptor
    TAG_ECND        = 0xA0,        //extended_channel_name_descriptor
    TAG_SLD         = 0xA1,        //service_location_descriptor
    TAG_TSSD        = 0xA2,        //time_shifted_service_descriptor
    TAG_CND         = 0xA3,        //component_name_descriptor
    TAG_DCCDRD      = 0xA8,        //DCC_departing_request_descriptor
    TAG_DCCARD      = 0xA9,        //DCC_arriving_request_descriptor
    TAG_RCD         = 0xAA,        //redistribution_control_descriptor
    //TAG_user        = 0xC0 ~ 0xFE//user_private
    //TAG_forbidden = 0xFF,      //Forbidden
} EN_DESCRIPTOR_TAG;
*/
//rename conflict name,*for ATSC merge CK3*
typedef enum{
    TAG_SSD_ATSC         = 0x35,        //StereoScopic descriptor
    TAG_StD_ATSC         = 0x80,        //stuffing_descriptor,need to check value with StD at dvb SI *for ATSC merge CK3*
    TAG_CSD_ATSC         = 0x86,        //caption_service_descriptor,need to check value with TAG_SAD at dvb SI *for ATSC merge CK3*
    TAG_CAD_ATSC         = 0x87,        //content_advisory_descriptor,need to check value with TAG_LCD2 at dvb SI *for ATSC merge CK3*
    TAG_SLD_ATSC         = 0xA1,        //service_location_descriptor
    TAG_TSSD_ATSC        = 0xA2,        //time_shifted_service_descriptor
} EN_DESCRIPTOR_TAG_ATSC;

/* tabel types definition */
/*use  mapp_si.h at dvb,*for ATSC merge CK3*
typedef enum
{
    TABLE_TYPE_CURRENT_TVCT = 0x0000,
    TABLE_TYPE_NEXT_TVCT     = 0x0001,
    TABLE_TYPE_CURRENT_CVCT = 0x0002,
    TABLE_TYPE_NEXT_CVCT     = 0x0003,
    TABLE_TYPE_CHAN_EIT        = 0x0004,
    TABLE_TYPE_DCCSCT        = 0x0005,
    //TABLE_TYPE_RESERVED     = 0x0006 ~ 0x00FF//reserved for future ATSC use
    TABLE_TYPE_EIT_0        = 0x0100, //EIT-0
    TABLE_TYPE_EIT_1        = 0x0101, //EIT-1
    TABLE_TYPE_EIT_2        = 0x0102, //EIT-2
    TABLE_TYPE_EIT_3        = 0x0103, //EIT-3
    TABLE_TYPE_EIT_7        = 0x0107, //EIT-7
    TABLE_TYPE_EIT_127        = 0x017F, //EIT-127
    //TABLE_TYPE_RESERVED     = 0x0180 ~ 0x01FF//reserved for future ATSC use
    TABLE_TYPE_ETT_0        = 0x0200, //ETT-0
    TABLE_TYPE_ETT_1        = 0x0201, //ETT-1
    TABLE_TYPE_ETT_2        = 0x0202, //ETT-2
    TABLE_TYPE_ETT_3        = 0x0203, //ETT-3
    TABLE_TYPE_ETT_7        = 0x0207, //ETT-7
    TABLE_TYPE_ETT_127        = 0x027F, //ETT-127
    //TABLE_TYPE_RESERVED     = 0x0280 ~ 0x0300//reserved for future ATSC use
    TABLE_TYPE_RRT_1        = 0x0301, //RRT with rating region 1
    TABLE_TYPE_RRT_255        = 0x03FF, //RRT with rating region 255
    //TABLE_TYPE_USER         = 0x0400 ~ 0x0FFF//user private
    //TABLE_TYPE_RESERVED     = 0x1000 ~ 0x13FF//reserved for future ATSC use
    TABLE_TYPE_DCCT_0        = 0x1400, //DCCT with dcc_id 0
    TABLE_TYPE_DCCT_255        = 0x14FF, //DCCT with dcc_id 255
    //TABLE_TYPE_RESERVED     = 0x1500 ~ 0xFFFF//reserved for future ATSC use
} EN_TABLE_TYPE;
*/
//add psip additional enum, *for ATSC merge CK3*
typedef enum{
    TABLE_TYPE_EIT_7        = 0x0107, //EIT-7
    TABLE_TYPE_EIT_55       = 0x0137, //EIT-55
    TABLE_TYPE_ETT_7        = 0x0207, //ETT-7
    TABLE_TYPE_ETT_55       = 0x0237, //ETT-55
} EN_TABLE_TYPE_ATSC;
/* Stream Type */
/*use  mapp_si.h at dvb,*for ATSC merge CK3*
typedef enum
{
    ST_MPEG1_VID    = 0x01,
    ST_MPEG2_VID    = 0x02,
    ST_MPEG1_AUD    = 0x03,
    ST_MPEG2_AUD    = 0x04,
    ST_PRIVATE_DATA = 0x06,
    ST_AAC_AUD      = 0x0f,
    ST_HEAAC_AUD    = 0x11,
    ST_AVCH264_VID  = 0x1B,
    ST_HEVC_H265_VID  = 0x24,
    ST_OP_MPEG2_VID = 0x80,
    ST_AC3_AUD      = 0x81,
    ST_AC3P_AUD     = 0x87,
} EN_STREAM_TYPE;
*/
/* Stream Type */
//add psip different name enum,*for ATSC merge CK3*
typedef enum
{
    ST_HEAAC_AUD    = 0x11,
    ST_HEVC_H265_VID  = 0x24,
    ST_AC3P_AUD     = 0x87
} EN_STREAM_TYPE_ATSC;

/* PSIP Table */
/*use  mapp_si.h at dvb,*for ATSC merge CK3*
typedef enum
{
    EN_PAT,
    EN_CAT,
    EN_PMT,
    EN_MGT,
    EN_TVCT,
    EN_CVCT,
    EN_RRT,
    EN_EIT,
    EN_ETT,
    EN_STT,
    EN_DCCT,
    EN_DCCSCT
} EN_PSIP_TABLE;
*/
//add psip different name enum,*for ATSC merge CK3*
typedef enum
{
    EN_MGT    =31,
    EN_STT
} EN_PSIP_TABLE_ATSC;

/* Parser Status */
typedef enum
{
    EN_PARSER_NO_ERROR,
    EN_PARSER_USER_ABORT,
    EN_PARSER_TIMEOUT,
    EN_PARSER_ERROR
} EN_PARSER_STATUS;

typedef enum
{
    EN_GET_SCAN_TBL_CONTINUE,
    EN_GET_SCAN_TBL_END,
    EN_GET_SCAN_TBL_PAT_FAIL
} EN_GET_SCAN_TBL_RETURN;
typedef enum
{
    ///invaild service
    EN_PSIP_SERVICE_INVALID           = 0,
    ///Analog  service
    EN_PSIP_SERVICE_ANALOG            = 1,
    ///DTV service
    EN_PSIP_SERVICE_DTV               = 2,
    ///Audio only service
    EN_PSIP_SERVICE_AUDIO             = 3,
    ///Data service
    EN_PSIP_SERVICE_DATA              = 4,
    ///Error service
    EN_PSIP_SERVICE_ERROR           = 5,
} MAPI_PSIP_SERVICE_TYPE;

typedef enum
{
    EN_PSIP_AC3_BSMOD_CM,
    EN_PSIP_AC3_BSMOD_ME,
    EN_PSIP_AC3_BSMOD_VI,
    EN_PSIP_AC3_BSMOD_HI,
    EN_PSIP_AC3_BSMOD_D,
    EN_PSIP_AC3_BSMOD_C,
    EN_PSIP_AC3_BSMOD_E,
    EN_PSIP_AC3_BSMOD_VO,
    EN_PSIP_AC3_BSMOD_NUM
} MAPI_PSIP_AC3_DESCRIPTOR_BSMOD;



typedef enum
{
    EN_PSIP_AC3_SAMPLE_RATE_BSID =2,  //first byte
    EN_PSIP_AC3_BIT_RATE_SURROUND, //second byte
    EN_PSIP_AC3_BSMOD_CHANNEL_SVC, //3rd byte
    EN_PSIP_AC3_LANGCODE,         //4th byte
    EN_PSIP_AC3_LANGCODE2,         //Option 5th byte if num_channels ==0
    EN_PSIP_AC3_MAINID_PRIORITY_ASVC,  // (5+x)th  byte  x=1 if num_channels ==0
    EN_PSIP_AC3_TEXT_LENGTH,    // (6+x)th  byte  x=1 if num_channels ==0
    EN_PSIP_AC3_TEXT,    // (7+x)th byte, length Y byte  x=1 if num_channels ==0 , y is text length
    EN_PSIP_AC3_LANGFLAG, //(8+x+y)th byte  x=1 if num_channels ==0 , y is text length
    EN_PSIP_AC3_LANG_1,   //(9+x+y)th, (9+x+y)th, (10+x+y)th  byte  x=1 if num_channels ==0 , y is text length
    EN_PSIP_AC3_LANG_2,  //(12+x+y)th, (12+x+y)th, (13+x+y)th  byte  x=1 if num_channels ==0 , y is text length
} MAPI_PSIP_AC3_DESCRIPTOR;



typedef struct
{
    U8 u8Sample_rate_Code;
    U8 u8Bsid;
    U8 u8BiteRateCode;
    U8 u8SurroundMode;
    U8 u8NumberOfChannel;  // if this audio pid in PMT
    U8 u8BsMod;
    U8 u8FullSVC;
    U8 u8LangCode2;
    U8 u8MainID;
    U8 u8Priority;
    U8 u8ASVCFlag;
    U8 u8LangFlag1;
    U8 u8LangFlag2;
    U8 u8Lang1[3];
    U8 u8Lang2[3];
} MAPI_PSIP_AC3_DES_A;

typedef enum
{
    EN_PSIP_EIT_EVNET_NO_OP,
    EN_PSIP_EIT_EVNET_DROP,
    EN_PSIP_EIT_EVNET_REPLACE,
    EN_PSIP_EIT_EVNET_NUM
} MAPI_PSIP_EIT_EVNET;


/*****************************************************************************/
/*                              Structures                                   */
/*****************************************************************************/
#define CONVERT_VIDEO_TYPE(src,dst)                     \
    switch(src)                                         \
    {                                                   \
        case ST_MPEG1_VID:                              \
            dst = VIDEO_STREAM_TYPE_MPEG1; \
            break;                                          \
        case ST_MPEG2_VID:                              \
            dst = VIDEO_STREAM_TYPE_MPEG2;  \
            break;                                          \
        case ST_AVCH264_VID:                               \
            dst = VIDEO_STREAM_TYPE_H264;   \
            break;                                          \
        case ST_HEVC_H265_VID:                              \
            dst = VIDEO_STREAM_TYPE_H265;  \
            break;                                          \
        case ST_OP_MPEG2_VID:                               \
            dst = VIDEO_STREAM_TYPE_OPTION_MPEG2;  \
            break;                                          \
        default:                                            \
            dst = VIDEO_STREAM_TYPE_OPTION_MPEG2;   \
            break;                                          \
}

#define CONVERT_AUDIO_TYPE(src,dst)                     \
    switch(src)                                         \
    {                                                   \
        case ST_MPEG1_AUD:                              \
            dst = AUD_STREAM_TYPE_MPEG;                        \
            break;                                          \
        case ST_MPEG2_AUD:                               \
            dst = AUD_STREAM_TYPE_MPEG;                         \
            break;                                          \
        case ST_AAC_AUD:                              \
            dst = AUD_STREAM_TYPE_AAC;                        \
            break;                                          \
        case ST_HEAAC_AUD:                              \
            dst = AUD_STREAM_TYPE_AAC;                        \
            break;                                          \
        case ST_AC3_AUD:                               \
            dst = AUD_STREAM_TYPE_AC3;                        \
            break;                                          \
        case ST_AC3P_AUD:                              \
            dst = AUD_STREAM_TYPE_AC3;                        \
            break;                                          \
        default:                                            \
            dst = AUD_STREAM_TYPE_AC3;                     \
            break;                                          \
    }


/******************************************************************************/
/*                       Global Variable Declarations                         */
/******************************************************************************/
#ifdef MAPP_PSIP_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

// pointer to channel list related structures
INTERFACE MS_VIRTUAL_CHANNEL  *pastVirtualCh;
INTERFACE MS_PHYSICAL_CHANNEL *pstPhysicalCh;
INTERFACE MS_VIRTUAL_VCT_CHANNEL *pastVirtualCh_VCT;
INTERFACE MS_VIRTUAL_CHANNEL_INFO *pastVirtualChInfo, *pastVirtualChInfo_2;

INTERFACE MS_RF_CHANNEL_new pastRfCh; // todo: Rename&Move to msAPI_DTVSystem_ATSC

INTERFACE MS_MGT_ST   stMGT;
INTERFACE MS_EAS_ST   stEAS;

//INTERFACE MS_PAT_ITEM_ATSC*pastPATItem;     //PAT Items

INTERFACE U8 u8NumOfNitItem;            //NIT Items #
INTERFACE U8 u8NumOfPatItem;            //PAT Items #
INTERFACE U8 u8NumOfVCTItem;            //PAT Items #
INTERFACE U8 u8TotalTableItem;            //PAT +VCT Items #
//INTERFACE U8 u8LastPatItemNo;           //PAT item Last number #
#if ENABLE_PAT_MUTISECTION
INTERFACE U8 u8CurSectionItemOfPat;           //PAT current section items #
INTERFACE U8 u8LastSectionNumOfPat;           //PAT Last section number #
#endif

INTERFACE U8 u8GpsUtcOffset;            // GPS to UTC offset time in seconds
INTERFACE U8 u8DaylightSavingDay;       // Daylight saving day of month
INTERFACE U8 u8DaylightSavingHour;      // Daylight saving hour

#if (ENABLE_MEXICO_VCHIP)
INTERFACE U8 u8CurrentRrtRegionNo; //mgt and cad region number
INTERFACE U8 u8LastRrtRegionNo; //last rrt table region number
INTERFACE U8 u8RrtRegionNo; //rrt table region number
#if (ENABLE_RRT5_UPDATE_BY_LATEST_VERSION)
INTERFACE U8 u8RrtRegionNoUpgrade; //rrt table update flag
#endif
#endif

// Flags to enable table monitor
INTERFACE MS_U8 fEnableTableMonitor;
INTERFACE MS_U8 fEnablePatMonitor;        // PAT
INTERFACE MS_U8 fEnablePmtMonitor;            // PMT
#if ENABLE_OAD
INTERFACE MS_U8 fEnablePmtOtherMonitor;   // PMT
#endif
INTERFACE MS_U8 fEnableSttMonitor;        // STT
INTERFACE MS_U8 fEnableMgtMonitor;        // MGT
INTERFACE MS_U8 fEnableEasMonitor;        // EAS
INTERFACE MS_U8 fEnableVctMonitor;        // VCT
//INTERFACE MS_U8 fEnableMvdTimingMonitor;
INTERFACE MS_U8 fTableAudioNumChanged;     // channel audio number change indicator
INTERFACE MS_U8 fTableVersionChanged;     // channel stream change indicator
INTERFACE MS_U8 fTableAudioStreamTypeChange;     // channel audio stream type change indicator
INTERFACE MS_U8 fTableAudioLanguageChange; // for UI us to differ auto program sacn or  TableVersionChanged

INTERFACE MS_U8 fEnableRRTMonitor;        //RRT monitor flag
INTERFACE MS_U8 fSearchRatingfromPMT;
INTERFACE MS_U8 fSearchEventTitlefromEIT;

// Filter IDs
INTERFACE U8 u8PcrFid;                  // PCR
INTERFACE U8 u8AudFid;                  // Audio PES
#if (ENABLE_ATSC_AD_FUNC)
INTERFACE U8 u8AudFid2;                 // Audio PES for AD
#endif
INTERFACE U8 u8VidFid;                  // Video PES
INTERFACE U8 u8PatFid;                  // PAT
INTERFACE U8 u8PmtFid;                  // PMT
INTERFACE U8 u8SttFid;                  // STT
INTERFACE U8 u8MgtFid;                  // MGT
INTERFACE U8 u8VctFid;                  // VCT
INTERFACE U8 u8EasFid;                  // EAS

INTERFACE U8 u8RRTFid;                  //Filter ID of Mgt
#if ENABLE_OAD
INTERFACE U8 u8PmtOtherFid;        // PMT
#endif

INTERFACE U8 u8MonitoringFID;


/******************************************************************************/
/*                       Global Function Prototypes                           */
/******************************************************************************/
// Monitor function for PSI/PSIP Table
INTERFACE void MApp_Dmx_PAT_Monitor_ATSC(void);
INTERFACE void MApp_Dmx_PMT_Monitor_ATSC(void);
#if ENABLE_OAD
INTERFACE void MApp_Dmx_PMT_Other_Monitor_ATSC(void);
#endif
INTERFACE void MApp_Dmx_STT_Monitor(void);
INTERFACE void MApp_Dmx_MGT_Monitor(void);
INTERFACE void MApp_Dmx_EAS_Monitor(void);
INTERFACE void MApp_Dmx_VCT_Monitor(void);
INTERFACE void MApp_Dmx_EIT_Monitor(void);
INTERFACE void MApp_Dmx_ETT_Monitor(MS_EPG_ETT* pstETT);
INTERFACE void MApp_Dmx_RRT_Monitor(void);

#if (ENABLE_MEXICO_VCHIP)
INTERFACE void MApp_Dmx_RRT_Reset(void);
#endif

#if (ENABLE_ATSC_EPG_DB_2016)
void MApp_Dmx_Eit_ResetSiDemux(void);
#endif

// Function to get scanning talbe information
INTERFACE EN_PARSER_STATUS MApp_Dmx_GetScanTables_ATSC(void);

// Function to enable and disable table monitor
INTERFACE void MApp_Dmx_EnableTableMonitor_ATSC(void);
INTERFACE BOOLEAN MApp_Dmx_CheckPATTimeout(void);

INTERFACE void MApp_Dmx_DisableTableMonitor_ATSC(void);
INTERFACE void MApp_Dmx_PMT_ChChange(void);

// Function to manage filter
INTERFACE void MApp_Dmx_CloseAllFilters_ATSC(void);

INTERFACE BOOL MApp_Dmx_EAS_GetStatus(MS_EAS_INFO *pstEAS_info);
#if ENABLE_OAD
INTERFACE BOOLEAN MApp_Dmx_Get_IsAllPmtReady_ATSC(void);
INTERFACE void MApp_Dmx_ResetAllPmtReady_ATSC(void);
#endif

#if( ENABLE_ATSC_EPG_DB_2016 )
MS_EPG_EVENT_New* MApp_Dmx_GetCurrentEvent(void);
#endif

const MS_PAT_ITEM_ATSC* MApp_PSIP_Get_PATItem(U8 u8PatItemIdx);

void MApp_Psip_Print_EPGInfo(void);


#undef INTERFACE

#endif
