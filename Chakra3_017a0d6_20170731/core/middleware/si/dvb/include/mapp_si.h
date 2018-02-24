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

#ifndef MAPP_SI_H
#define MAPP_SI_H
#if defined(BUILD_LIB)
#include "MsVersion.h"
#endif
#if(ENABLE_DTV)
#include "MsTypes.h"
#include "mapp_si_if.h"

//-------------------------------------------------------------------------------------------------
// Version Control
//-------------------------------------------------------------------------------------------------
#define MSIF_SI_LIB_CODE          {'S','I','D','V'}                    //Lib code
//#define MSIF_SI_LIBVER          {'0','3','9'}                        //LIB version
#define SI_VERSION                69 //0~999                          //LIB version
#define MSIF_SI_LIBVER            {'0'+(SI_VERSION/100),'0'+((SI_VERSION/10)%10),'0'+(SI_VERSION%10)}
#define MSIF_SI_BRANCHCL          {'@','0','0','0','0','0','0','0'}    //for branch update code
#define MSIF_SI_CHANGELIST        {'@','b','a','d','b','0','f','7'}    //for truck update code

#define MW_SI_VER                  /* Character String for DRV/API version             */  \
    MSIF_TAG,                       /* 'MSIF'                                           */  \
    MSIF_CLASS,                     /* '00'                                             */  \
    MSIF_CUS,                       /* 0x0000                                           */  \
    MSIF_MOD,                       /* 0x0000                                           */  \
    MSIF_CHIP,                                                                              \
    MSIF_CPU,                                                                               \
    MSIF_SI_LIB_CODE,              /* IP__                                             */  \
    MSIF_SI_LIBVER,                /* 0.0 ~ Z.Z                                        */  \
    MSIF_SI_BRANCHCL,              /* 00 ~ 99999999                                    */  \
    MSIF_SI_CHANGELIST,            /* 00 ~ 99999999                                    */  \
    MSIF_OS



/******************************************************************************/
/*                                 Macro                                      */
/******************************************************************************/


/* Control Codes Type */
#define KEEP_CONTROL_CODE_NONE            0x00
#define KEEP_CONTROL_CODE_EMPHASIS        0x01
#define KEEP_CONTROL_CODE_CR_LF           0x02
#define KEEP_CONTROL_CODE_ALL            (KEEP_CONTROL_CODE_EMPHASIS|KEEP_CONTROL_CODE_CR_LF)


/* Private data specifier descriptor id */
#define PDSDID_UK           0x0000233A
#define PDSDID_SWEDEN       0x00000014
#define PDSDID_NORDIG       0x00000029
#define PDSDID_NZ           0x00000037
#define PDSDID_CIPLUS       0x00000040
#define PDSDID_UAE          0x00000028
#define PDSDID_THAILAND     0x000022FC
#define PDSDID_MALAYSIA     0x000021CA
#define PDSDID_SINGAPORE    0x00000019
#define PDSDID_INDONESIA_EWS       0x00002168
#define PDSDID_AUS          0x00003200

/* EWS  OrginalNetworkID */
#define ONID_INDONESIA_EWS 0x2168
#define SI_EWS_NUMBER_CHAR_LOCTION              256
#define SI_EWS_NUMBER_CHAR_DISASTER_TYPE        256
#define SI_EWS_NUMBER_CHAR_DISASTER_POSITION    256
#define SI_EWS_NUMBER_CHAR_DISASTER_DATE        256
#define SI_EWS_NUMBER_CHAR_DISASTER_CHARACTER   256
#define SI_EWS_NUMBER_CHAR_MESSAGE              3201

#if (ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
#define PDSDID_ASTRA        0x00000001
#endif //#if (ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)

#define MAX_TTXINFO_NUM     12 // 6

#define SI_PARSER_DVB       0
#define SI_PARSER_ISDB_ABNT 1
#define NORDIG_SIMULCAST_REPLACEMENT_SERVICE    0x82
#define SERVICE_REPLACEMENT_SERVICE    0x05
#define CA_REPLACEMENT_SERVICE 0x03

#define MAX_COUNTRY_REGION_NUM     2 // 6
#define MAX_PRIMARY_REGION_NUM     10 // 6
#define MAX_SECONDARY_REGION_NUM     10 // 6
#define MAX_TERTIARY_REGION_NUM     10 // 6
#define MAX_REGION_NAME     40 // 6

#define DVB_T2_PLP_ID_INVALID   0xFFFF
#define MAX_SI_T2_CELL_CENTREFREQ   8
#define MAX_SI_T2_CENTREFREQ        16

/******************************************************************************/
/*                                 Enum                                       */
/******************************************************************************/
/* descriptor tag definition */
typedef enum
{
    // MPEG-2 descriptor tag
    TAG_VSD             = 0x02,         // video_stream_descriptor
    TAG_ASD             = 0x03,         // audio_stream_descriptor
    //TAG_T2DSD             = 0x04,         //T2_delivery_system_descriptor
    TAG_HiD             = 0x04,         // hierarchy_descriptor
    TAG_RgD             = 0x05,         // registration_descriptor
    TAG_DSAD            = 0x06,         // data_stream_alignment_descriptor
    TAG_TBGD            = 0x07,         // target_background_grid_descriptor
    TAG_VWD             = 0x08,         // video_window_descriptor
    TAG_CaD             = 0x09,         // CA_descriptor
    TAG_LnD             = 0x0A,         // ISO_639_language_descriptor
    TAG_SCD             = 0x0B,         // system_clock_descriptor
    TAG_MBUD            = 0x0C,         // multiplex_buffer_utilization_descriptor
    TAG_CRD             = 0x0D,         // copyright_descriptor
    TAG_MBD             = 0x0E,         // maximum_bitrate_descriptor
    TAG_PDID            = 0x0F,         // private_data_indicator_descriptor
    TAG_SBD             = 0x10,         // smoothing_buffer_descriptor
    TAG_STDD            = 0x11,         // STD_descriptor
    TAG_IBPD            = 0x12,         // IBP_descriptor
    TAG_CID             = 0x13,         // carousel_id_descriptor
    TAG_AVCVD           = 0x28,         // avc_video_descriptor

    TAG_NND             = 0x40,         // network_name_descriptor
    TAG_SLD             = 0x41,         // service_list_descriptor
    TAG_StD             = 0x42,         // stuffing_descriptor
    TAG_SDSD            = 0x43,         // satellite_delivery_system_descriptor
    TAG_CDSD            = 0x44,         // cable_delivery_system_descriptor
  //TAG_reserved        = 0x45,         // reserved_for_future_use
  //TAG_reserved        = 0x46,         // reserved_for_future_use
    TAG_BND             = 0x47,         // bouquet_name_descriptor
    TAG_SeD             = 0x48,         // service_descriptor
    TAG_CAD             = 0x49,         // country_avaliability_descriptor
    TAG_LD              = 0x4A,         // linkage_descriptor
    TAG_NVODRD          = 0x4B,         // NVOD_reference_descriptor
    TAG_TSSD            = 0x4C,         // time_shifted_service_descriptor
    TAG_SED             = 0x4D,         // short_event_descriptor
    TAG_EED             = 0x4E,         // extended_event_descriptor
    TAG_TSED            = 0x4F,         // time_shifted_event_descriptor
    TAG_CpD             = 0x50,         // component_descriptor
    TAG_MD              = 0x51,         // mosaic_descriptor
    TAG_SID             = 0x52,         // stream_identifier_descriptor
    TAG_CAID            = 0x53,         // CA_identifier_descriptor
    TAG_CtD             = 0x54,         // content_descriptor
    TAG_PRD             = 0x55,         // parental_rating_descriptor
    TAG_TtD             = 0x56,         // teletext_descriptor
    TAG_TpD             = 0x57,         // telephone_descriptor
    TAG_LTOD            = 0x58,         // local_time_offset_descriptor
    TAG_SbD             = 0x59,         // subtitling_descriptor
    TAG_TDSD            = 0x5A,         // terrestrial_delivery_system_descriptor
    TAG_MNND            = 0x5B,         // multilingual_network_name_descriptor
    TAG_MBND            = 0x5C,         // multilingual_bouquet_name_descriptor
    TAG_MSND            = 0x5D,         // multilingual_service_name_descriptor
    TAG_MCD             = 0x5E,         // multilingual_component_descriptor
    TAG_PDSD            = 0x5F,         // private_date_specifier_descriptor
    TAG_SMD             = 0x60,         // service_move_descriptor
    TAG_SSBD            = 0x61,         // short_smoothing_buffer_descriptor
    TAG_FLD             = 0x62,         // frequency_list_descriptor
    TAG_PTSD            = 0x63,         // partial_transport_stream_descriptor
    TAG_DBD             = 0x64,         // data_broadcast_descriptor
    TAG_CASD            = 0x65,         // CA_system_descriptor
    TAG_DBID            = 0x66,            // data_broadcast_id_descriptor
    TAG_PDC             = 0x69,         // PDC_descriptor
    TAG_AC3D            = 0x6A,            // AC3_descriptor
    TAG_CFLD            = 0x6D,         //cell_frequency_link_descriptor
    TAG_SAAD            = 0x72,         // service_availability_descriptor
    TAG_CIDD            = 0x76,         // content_identifier_descriptor
    TAG_S2DSD           = 0x79,         // S2_satellite_delivery_system_descriptor
    TAG_AC3PD           = 0x7A,         // AC3_plus_descriptor
    TAG_AAC             = 0x7C,         // AAC_descriptor
    TAG_CMG             = 0x7E,         // FTA_Content_Management_descriptor
    TAG_ED              = 0x7F,         // extension descriptor
    // PSIP descriptor tag
    TAG_UDSD            = 0x80,         // user_defined_start_descriptor
    TAG_AC3AD           = 0x81,         // AC3_audio_descriptor
    TAG_LCD             = 0x83,         // logical_channel_descriptor
    TAG_PNL             = 0x84,         // Prefered name list descriptor
    TAG_PNI                = 0x85,         // Prefered name identifier descriptor
    TAG_SAD             = 0x86,         // service_attribute_descriptor
    // Seems we don't cate shotr_service_name_descriptor
    // Disalbe it for logical channel descriptor version 2.
  //TAG_SSN             = 0x87,         // short_service_name_descriptor
    TAG_LCD2            = 0x87,         // Nordig spec, logical_channel_descriptor version 2.
    TAG_SIMU_LCD = 0x88,     //HD Simulcast Logical Channel Descriptor
#if (ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
    TAG_SLND            = 0x88,          ///< Service List Name Descriptor for Astra (DVBS only)
#endif //#if (ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
    TAG_GUIDE       =0x89,              //guidance_descriptor
    TAG_DRAD            = 0xA0,     //audio type
  // TAG_ECND                  = 0xA0,         // extended_channel_name_descriptor
  //TAG_SLD                     = 0xA1,         // service_location_descriptor
  //TAG_TSSD                   = 0xA2,         // time_shifted_service_descriptor
    TAG_CND             = 0xA3,         // component_name_descriptor
    TAG_DCCDRD          = 0xA8,         // DCC_departing_request_descriptor
    TAG_DCCARD          = 0xA9,         // DCC_arriving_request_descriptor
    TAG_RCD             = 0xAA,         // redistribution_control_descriptor
    TAG_LC_LCD          = 0xB0,         // France Numericable cable LCD
#if 1//ENABLE_SBTVD_BRAZIL_APP
    TAG_TID             = 0xCD,         // ts_information_descriptor
    TAG_ACD             = 0xC4,         // audio_component_descriptor
    TAG_CICTLD          = 0xCB,          ///< ciplus_content_label_descriptor
    TAG_CISED           = 0xCC,         ///< ciplus_service_descriptor
    TAG_CIPD            = 0xCE,          // CI_protection_descrptior
#if (ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
    TAG_VSID            = 0xD1,         // virtual service ID descriptor
#endif //#if (ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
    TAG_CIVIRCH             = 0xD2,         // cicam_virtual_channel_descriptor ENABLE_CI_PLUS_V1_4

    TAG_PRED            = 0xFB,         // partial_reception_descrptior
#endif
    TAG_UDED            = 0xFE,         // user_defined_end_descriptor
  //TAG_forbidden       = 0xFF,         // Forbidden
} EN_DESCRIPTOR_TAG;

/* descriptor tag extension definition */
typedef enum
{
    ///< T2_delivery_system_descriptor
    TAG_T2DSD           = 0x04,
    TAG_SMAD         = 0x06,
    TAG_TRD         = 0x09,
    TAG_TRND         = 0x0a,
    TAG_SRD         = 0x0B,
    ///< C2_delivery_system_descriptor
    TAG_C2DSD           = 0x0D,
    /// URI_linkage_descriptor ENABLE_CI_PLUS_V1_4
    TAG_ULD           = 0x13,
}EN_DESCRIPTOR_TAG_EXT;


/* TABLE ID definition */
typedef enum
{
    // MPEG-2 table id
    TID_PAS         = 0x00,             // program_association_section
    TID_CAS         = 0x01,             // conditional_access_section
    TID_PMS         = 0x02,             // program_map_section
    TID_TSDS        = 0x03,             // transport_stream_description_section

    // PSIP table id [todo: remove]
    TID_MGS         = 0xC7,             // master_guide_section
    TID_TVCS        = 0xC8,             // terrestrial_virtual_channel_section
    TID_CVCS        = 0xC9,             // cable_virtual_channel_section
    TID_RRS         = 0xCA,             // ratting_region_section
    TID_EIS         = 0xCB,             // event_information_section
    TID_ETS         = 0xCC,             // extended_text_section
    TID_STS         = 0xCD,             // system_time_section
  //TID_other       = 0xCE ~ 0xD2       // ATSC coordinated values which are defined in other standards
    TID_DCCS        = 0xD3,             // program_association_section
    TID_DCCSCS      = 0xD4,             // program_association_section
  //TID_other       = 0xD5 ~ 0xDF       // ATSC coordinated values which are defined in other standards
  //TID_other       = 0xE0 ~ 0xE5       // other systems
  //TID_reserved    = 0xE6 ~ 0xFE       // ATSC_reserved
  //TID_reserved    = 0xFF              // reserved

    // DVB-T table id
    // 0x04 ~ 0x3f reserved
    TID_NIS_ACTUAL      = 0x40,         // network information section - actual network
    TID_NIS_OTHER       = 0x41,         // network information section - other network
    TID_SDS_ACTUAL      = 0x42,         // service description section - actual transport stream
    TID_SDS_OTHER       = 0x46,         // service description section - other network stream
    TID_BAS             = 0x4a,         // bouquet association section
    TID_EIS_ACTUAL_PF   = 0x4e,         // event information section - actual transport stream, present/following
    TID_EIS_OTHER_PF    = 0x4f,         // event information section - other transport stream, present/following
    TID_EIS_ACTUAL_SB   = 0x50,         // event information section - actual transport stream, schedule, enum begin
    TID_EIS_ACTUAL_SE   = 0x5f,         // event information section - actual transport stream, schedule, enum end
    TID_EIS_OTHER_SB    = 0x60,         // event information section - other transport stream, schedule, enum begin
    TID_EIS_OTHER_SE    = 0x6f,         // event information section - other transport stream, schedule, enum end
    TID_TDS             = 0x70,         // time date section
    TID_RSS             = 0x71,         // running status section
    TID_ST              = 0x72,         // stuffing section
    TID_TOS             = 0x73,         // time offset section
    TID_RNS             = 0x74,         // resolution notification section (TS 102 323 [36])
    TID_CS              = 0x75,         // container section (TS 102 323 [36])
    TID_RCS             = 0x76,         // related content section (TS 102 323 [36])
    TID_CIS             = 0x77,         // content identification section (TS 102 323 [36])
    TID_MFS             = 0x78,         // MPE-FEC section (TS 301 192 [37])
    TID_DIS             = 0x7e,         // discontinuity information section
    TID_SIS             = 0x7f,         // selection information section
    TID_EWS             = 0x80,

#if (ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
    TID_SGS             = 0x91,         //SGT Table
#endif  //#if (ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
#if(M7_DVBS_FAST_SCAN_ENABLE)
    TID_FNS             =0xBC,
    TID_FSS             =0xBD,
#endif //#if (M7_DVBS_FAST_SCAN_ENABLE)
} EN_PSIP_TID;

typedef enum
{
    TID_EX_EWS_TRDW = 0x01,
    TID_EX_EWS_TCDW = 0x02,
    TID_EX_EWS_TMDW = 0x03,
}EN_EWS_TID_EX;

typedef enum
{
    EWS_AWAS = 0x01,
    EWS_SLAGA = 0x02,
    EWS_WASPADA = 0x03,
}EN_EWS_Location_TYPE;

/* tabel types definition */
typedef enum
{
    TABLE_TYPE_CURRENT_TVCT = 0x0000,
    TABLE_TYPE_NEXT_TVCT    = 0x0001,
    TABLE_TYPE_CURRENT_CVCT = 0x0002,
    TABLE_TYPE_NEXT_CVCT    = 0x0003,
    TABLE_TYPE_CHAN_EIT     = 0x0004,
    TABLE_TYPE_DCCSCT       = 0x0005,
  //TABLE_TYPE_RESERVED     = 0x0006 ~ 0x00FF   // reserved for future ATSC use
    TABLE_TYPE_EIT_0        = 0x0100,           // EIT-0
    TABLE_TYPE_EIT_1        = 0x0101,           // EIT-1
    TABLE_TYPE_EIT_2        = 0x0102,           // EIT-2
    TABLE_TYPE_EIT_3        = 0x0103,           // EIT-3
    TABLE_TYPE_EIT_127      = 0x017F,           // EIT-127
  //TABLE_TYPE_RESERVED     = 0x0180 ~ 0x01FF   // reserved for future ATSC use
    TABLE_TYPE_ETT_0        = 0x0200,           // ETT-0
    TABLE_TYPE_ETT_1        = 0x0201,           // ETT-1
    TABLE_TYPE_ETT_2        = 0x0202,           // ETT-2
    TABLE_TYPE_ETT_3        = 0x0203,           // ETT-3
    TABLE_TYPE_ETT_127      = 0x027F,           // ETT-127
  //TABLE_TYPE_RESERVED     = 0x0280 ~ 0x0300   // reserved for future ATSC use
    TABLE_TYPE_RRT_1        = 0x0301,           // RRT with rating region 1
    TABLE_TYPE_RRT_255      = 0x03FF,           // RRT with rating region 255
  //TABLE_TYPE_USER         = 0x0400 ~ 0x0FFF   // user private
  //TABLE_TYPE_RESERVED     = 0x1000 ~ 0x13FF   // reserved for future ATSC use
    TABLE_TYPE_DCCT_0       = 0x1400,           // DCCT with dcc_id 0
    TABLE_TYPE_DCCT_255     = 0x14FF,           // DCCT with dcc_id 255
  //TABLE_TYPE_RESERVED     = 0x1500 ~ 0xFFFF   // reserved for future ATSC use
} EN_TABLE_TYPE;


typedef enum
{
    EN_TTX_INVALID         = 0x00,
    EN_TTX_INIT_TTX        = 0x01,
    EN_TTX_SUBTITLE        = 0x02,
    EN_TTX_ADDITIONAL_INFO = 0x03,
    EN_TTX_PROG_SCHEDULE   = 0x04,
    EN_TTX_SUBTITLE_HEAR   = 0x05,
} EN_TTX_TYPE;

typedef enum
{
    SI_MHEG5_DISABLE,
    SI_MHEG5_WITH_VIDEO,
    SI_MHEG5_DATA_ONLY,
} SI_MHEG5_STATUS;

typedef enum
{
    SI_RESET_SCAN = 1,
    SI_RESET_CHNCHANGE,    // Channel change.
    SI_RESET_SOURCECHANGE, // Source change.
} SI_RESET_TYPE;

typedef enum
{
    SI_AUDTYPE_UNDEFINED,
    SI_AUDTYPE_CLEANEFFECTS,
    SI_AUDTYPE_HEARING,
    SI_AUDTYPE_VISUAL,
} SI_AUDIO_TYPE;

typedef enum
{
    SI_SDT_FREECA_FTA = 0x00,
    SI_SDT_FREECA_SCR = 0x01,
} SI_SDT_FREECAMODE;

typedef enum
{
    SI_SDT_RUN_UNDEFINED = 0x00,
    SI_SDT_RUN_NOT_RUN   = 0x01,
    SI_SDT_RUN_START_SOON= 0x02,
    SI_SDT_RUN_PAUSE     = 0x03,
    SI_SDT_RUN_RUNNING   = 0x04,
    SI_SDT_SERVICE_AIR_OFF = 0x05
} SI_SDT_RUNNINGSTATUS;
/* PSIP Table */
typedef enum
{
    EN_PAT,
    EN_CAT,
    EN_PMT,
    EN_PMT_OTHER,
    EN_SDT,
    EN_SDT_OTHER,
    EN_NIT,
    EN_TVCT,
    EN_CVCT,
    EN_RRT,
    EN_EIT,
    EN_ETT,
    EN_TDT,
    EN_DCCT,
    EN_DCCSCT,
    EN_BAT,
    EN_RST,
    EN_TOT,
    EN_DIT,
    EN_SIT,
    EN_TRDW,
    EN_TCDW,
    EN_TMDW,
    EN_SGT ,//SGT
    EN_FNT, //FNT
    EN_FST, //FST
    EN_NIT_Other
} EN_PSIP_TABLE;

typedef enum
{
    EN_FIRSTLOOP = 1,
    EN_SECONDLOOP,
} EN_LOOP_TYPE;



/* Stream Type */
typedef enum
{
    ST_MPEG1_VID            = 0x01,
    ST_MPEG2_VID            = 0x02,
    ST_MPEG1_AUD            = 0x03,
    ST_MPEG2_AUD            = 0x04,
    ST_MPEG4_AUD            = 0x11,
    /* private sectoin */
    ST_PRIVATE_SECTION      = 0x05,
    ST_PRIVATE_DATA         = 0x06,
    ST_DSMCC_DATA_TYPE_A    = 0x0A,
    ST_DSMCC_DATA_TYPE_B    = 0x0B,
    ST_DSMCC_DATA_TYPE_C    = 0x0C,
    ST_DSMCC_DATA_TYPE_D    = 0x0D,
    ST_DSMCC_DATA_TYPE_E    = 0x0E,
    ST_AAC_AUD              = 0x0F,
    ST_AVCH264_VID          = 0x1B,
    ST_HEVC_VID             = 0x24,//H265
    ST_AVS_VID              = 0x42,
    ST_OP_MPEG2_VID         = 0x80,
    ST_AC3_AUD              = 0x81,
    ST_E_AC3_AUD            = 0x87,
    ST_VC1_VID              = 0xEA

} EN_SI_STREAM_TYPE;


typedef enum
{
    E_SI_AUDIOSTREAM_INVALID          = 0x00,
    E_SI_AUDIOSTREAM_MPEG          = 0x01,
    E_SI_AUDIOSTREAM_AC3           = 0x02,
    E_SI_AUDIOSTREAM_MPEG4         = 0x03,
    E_SI_AUDIOSTREAM_AAC           = 0x04,
    E_SI_AUDIOSTREAM_AC3P          = 0x05,
    E_SI_AUDIOSTREAM_DRA           = 0x06
} SI_AUDIOSTREAM_TYPE;


typedef enum
{
    E_SI_AUDIOMODE_STEREO          = 0x00,
    E_SI_AUDIOMODE_RR           = 0x01,
    E_SI_AUDIOMODE_LL         = 0x02
} SI_AUDIOMODE_TYPE;

typedef enum{
    ST_AUD_SINGLE_MONO = 0x01,
    ST_AUD_DUAL_MONO = 0x02,
    ST_AUD_STEREO = 0x03,
    ST_AUD_MULTICHANNEL=0x04,
    ST_AUD_SURROUND_SOUND=0x05

} EN_SI_COMPONENT_TYPE;

typedef enum
{
    EN_SI_TDT=0,
    EN_SI_TOT=1,
    EN_SI_TDT_TOT=2,
}EN_SI_TIME_TYPE;

typedef enum
{
    EN_SI_NONE      =0x0000,  //0000
    EN_SI_VERSION   =0x0001,  //0001
    EN_SI_ADD       =0x0002,  //0010
    EN_SI_REMOVE    =0x0004,  //0100
    EN_SI_LCN       =0x0008,  //1000
    EN_SI_NITUPDATE =0x0010,
    EN_SI_BAT       =0x0020,
    EN_SI_QUICKSCAN =0x0040,
    EN_SI_SCAN      =0x0080,
    EN_SI_PMT       =0x0160,
    EN_SI_SGT       =0x0320
}EN_SI_DEBUG_LEVEL;

//#if ENABLE_CI_PLUS_V1_4
typedef enum
{
    //No OSDT
    EN_OSDT_SCHEME_TYPE_NONE = 0x0,
    //OSDT from CICAM
    EN_OSDT_SCHEME_TYPE_CICAM,
    //OSDT from HTTP
    EN_OSDT_SCHEME_TYPE_HTTP
} EN_SI_OSDT_SCHEME_TYPE;
//#endif

/*****************************************************************************/
/*                              Structures                                   */
/*****************************************************************************/
typedef struct
{
    U16 u16Code;
    U8 name[MAX_REGION_NAME];
} MW_DVB_TERTIARY_REGION_INFO;
typedef struct
{
    U8 u8Code;
    U8 name[MAX_REGION_NAME];
    U16 u16TertiaryRegionNum;
    MW_DVB_TERTIARY_REGION_INFO* pTertiaryRegionInfo;
} MW_DVB_SECONDARY_REGION_INFO;

typedef struct
{
    U8 u8Code;
    U8 name[MAX_REGION_NAME];
    U16 u16SecondaryRegionNum;
    MW_DVB_SECONDARY_REGION_INFO* pSecondaryRegionInfo;
} MW_DVB_PRIMARY_REGION_INFO;

typedef struct
{
    U8 au8CountryCode[3];
    U16 u16PrimaryRegionNum;
    MW_DVB_PRIMARY_REGION_INFO* pPrimaryRegionInfo;
} MW_DVB_COUNTRY_INFO;

typedef struct
{
    U8 u8CountryNum;
    MW_DVB_COUNTRY_INFO* pCountryInfo;
} MW_DVB_TARGET_REGION_INFO;
/*@ <Definitions> @*/


typedef struct
{
    U16 u16ONID;
    U16 u16TSID;
    U16 u16SID; //0=>TS layer,other=>service layer
    MW_DVB_TARGET_REGION_INFO stInfo;
} MW_DVB_TS_REGION_INFO;


typedef struct
{
    U16 u16TSNum;
    MW_DVB_TS_REGION_INFO* pInfo;
} MW_DVB_ALL_Service_REGION_INFO;




typedef struct
{
    U32 u32CentreFreq;//0.1KHz
    U32 u32Symbol_rate:24;//0.1K symbol/s
    U32 u8Modulation:8;//0=>not defined,1=>16 QAM,2=>32 QAM,3=>64 QAM,4=>128 QAM,5=>256 QAM
    U16 u16ONID;
    U16 u16NetworkID;
    U16 u16TSID;
} MS_CABLE_PARAMETER; // Cable delivery system descript

typedef struct
{
    U32 u32CentreFreq;
    U16 u16Orbital_pos;
    U32 u32Symbol_rate:28;
    U32 u8Polarization:2;
    U32 U32West_east_flag:1;
    U32 reserved :1;
    U16 u16Tsid;
    U16 u16Onid;
    U16 u16Nid;
} MS_SAT_PARAMETER; // Sat delivery system descript


typedef struct
{
    U16 u16NetworkID;
    U8  au8NetworkName[SI_MAX_NETWORK_NAME];
} MS_NETWORK_NAME_INFO;



typedef struct
{
    U16 u16TSId;
    U16 u16ONId;
    U16 u16ServiceId;
    U8  u8LinkageType;
    U8  u8RunningStatus;
    U8  u8Ser_Replacement:1;
    U8  u8FreeCAMode:1;
    U8  u8Reserved:6;
}RP_SERVICE_INFO;

typedef struct
{
    U16 wONID;
    U16 wTSID;
    U16 wSID;
}MOVE_SERVICE_IDS;


typedef enum
{
    E_SERVICE_REMOVED,
    E_SERVICE_MOVE,
    E_SERVICE_CHANGED
} E_SERVICE_CHANGE;

typedef struct   //Same Service ID
{
    U8  u8bStillPic :1;
    U8  u8fMHEG5    :1;
    U8  u8IsCAExist :1;
    U8  eVideoType  :3;
    U8  u8Reserved  :2;
    U16 wPmtPid;
    U16 wVideo_PID;
    U16 wPCRPid;
    U8  u8AudStreamNum;
    SI_AUD_INFO stAudInfo[SI_MAX_AUD_LANG_NUM];
} MS_SI_CUR_SERVICE_INFO;


typedef enum
{
    E_MODULATION_UNDEFINED=0x00,
    E_MODULATION_16_QAM=0x01,
    E_MODULATION_32_QAM=0x02,
    E_MODULATION_64_QAM=0x03,
    E_MODULATION_128_QAM=0x04,
    E_MODULATION_256_QAM=0x05,
} E_CABLE_MODULATION;



typedef enum
{
    EN_SI_Clock_TimeZone_0,  //GMT - 12:00
    EN_SI_Clock_TimeZone_1,  //GMT - 11:30
    EN_SI_Clock_TimeZone_2,  //GMT - 11:00
    EN_SI_Clock_TimeZone_3,  //GMT - 10:30
    EN_SI_Clock_TimeZone_4,  //GMT - 10:00
    EN_SI_Clock_TimeZone_5,  //GMT - 09:30
    EN_SI_Clock_TimeZone_6,  //GMT - 09:00
    EN_SI_Clock_TimeZone_7,  //GMT - 08:30
    EN_SI_Clock_TimeZone_8,  //GMT - 08:00
    EN_SI_Clock_TimeZone_9,  //GMT - 07:30
    EN_SI_Clock_TimeZone_10, //GMT - 07:00
    EN_SI_Clock_TimeZone_11, //GMT - 06:30
    EN_SI_Clock_TimeZone_12, //GMT - 06:00
    EN_SI_Clock_TimeZone_13, //GMT - 05:30
    EN_SI_Clock_TimeZone_14, //GMT - 05:00
    EN_SI_Clock_TimeZone_15, //GMT - 04:30
    EN_SI_Clock_TimeZone_16, //GMT - 04:00
    EN_SI_Clock_TimeZone_17, //GMT - 03:30
    EN_SI_Clock_TimeZone_18, //GMT - 03:00
    EN_SI_Clock_TimeZone_19, //GMT - 02:30
    EN_SI_Clock_TimeZone_20, //GMT - 02:00
    EN_SI_Clock_TimeZone_21, //GMT - 01:30
    EN_SI_Clock_TimeZone_22, //GMT - 01:00
    EN_SI_Clock_TimeZone_23, //GMT - 00:30
    EN_SI_Clock_TimeZone_24, //GMT + 00:00
    EN_SI_Clock_TimeZone_25, //GMT + 00:30
    EN_SI_Clock_TimeZone_26, //GMT + 01:00
    EN_SI_Clock_TimeZone_27, //GMT + 01:30
    EN_SI_Clock_TimeZone_28, //GMT + 02:00
    EN_SI_Clock_TimeZone_29, //GMT + 02:30
    EN_SI_Clock_TimeZone_30, //GMT + 03:00
    EN_SI_Clock_TimeZone_31, //GMT + 03:30
    EN_SI_Clock_TimeZone_32, //GMT + 04:00
    EN_SI_Clock_TimeZone_33, //GMT + 04:30
    EN_SI_Clock_TimeZone_34, //GMT + 05:00
    EN_SI_Clock_TimeZone_35, //GMT + 05:30
    EN_SI_Clock_TimeZone_36, //GMT + 06:00
    EN_SI_Clock_TimeZone_37, //GMT + 06:30
    EN_SI_Clock_TimeZone_38, //GMT + 07:00
    EN_SI_Clock_TimeZone_39, //GMT + 07:30
    EN_SI_Clock_TimeZone_40, //GMT + 08:00 /* Taipei, Beijing, Hong Kong */
    EN_SI_Clock_TimeZone_41, //GMT + 08:30
    EN_SI_Clock_TimeZone_42, //GMT + 09:00
    EN_SI_Clock_TimeZone_43, //GMT + 09:30
    EN_SI_Clock_TimeZone_44, //GMT + 10:00
    EN_SI_Clock_TimeZone_45, //GMT + 10:30
    EN_SI_Clock_TimeZone_46, //GMT + 11:00
    EN_SI_Clock_TimeZone_47, //GMT + 11:30
    EN_SI_Clock_TimeZone_48, //GMT + 12:00
    EN_SI_Clock_TimeZone_Num
} EN_SI_Clock_TimeZone;

typedef struct
{
    U8  u8lanuage_code[3];
    U8  u8TTXType   :5; // EN_TTX_TYPE
    U8  u8TTXMagNum :3;
    U8  u8TTXPageNum;
} TELETEXT_Info;

typedef struct   //Same Service ID
{
    U16 u16TTX_Pid;
    U8 u8NumTTXType;
    TELETEXT_Info stTTXInfo[MAX_TTXINFO_NUM];
} MS_TELETEXT_INFO;


#if (ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)

#define MAPI_SI_MAX_SERVICE_LIST_NAME 31
#define MAPI_SI_MAX_SERVICE           5000

 /// servicelist id ;servicelsit name only;
 typedef struct
 {
     /// service list name
     U8  au8ServiceListName[MAPI_SI_MAX_SERVICE_LIST_NAME];
     /// service list id
     U16 u16ServiceListID;

 }MS_SI_SGT_BASIC_SERVICE_LIST_INFO;

 /// Define struct Coutry availability descriptor
 typedef struct
 {
     /// country code
     U8 au8CountryCode[3];
     /// is country available
     BOOLEAN    bIsCountryAvailability;

 }MS_SI_COUNTRY_AVAILABILITY_INFO;

typedef struct
{
    /// service list name ;service list id;
    MS_SI_SGT_BASIC_SERVICE_LIST_INFO stBasicServiceListInfo;
    /// country availablity descriptor
    MS_SI_COUNTRY_AVAILABILITY_INFO stCountryAvailability;
    /// language code
    U8  au8LangCode[3];
    /// is service conditional access or not
    BOOLEAN bIsCA;
    ///Program Number Count
    U16 u16ServiceID_Count;
     /// services info
   MS_SI_SGT_SERVICE_INFO stServiceInfo[MAPI_SI_MAX_SERVICE];

}MS_SI_TABLE_SGT;

#endif // #if (ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)

//////////////////////////////////////////////////////////////////////////////////////////
//  PSIP Structure Type
//////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
    U16 u16ProgramNumber;
    U16 u16PID;
} MS_PAT_ITEM;

typedef enum
{
    EN_SI_UPDATE_TYPE_SDT_ONLY=0,
    EN_SI_UPDATE_TYPE_SDT_PAT_COMBO,
}EN_SI_PROG_UPDATE_TYPE;

typedef struct
{
    U8 eSI_Type;
    U32 u32SIBufferStartAddress;
    U32 u32SIBufferSize;
    U32 u32SINameBufferAddress;
    BOOLEAN bSkipUnsupportService;
    BOOLEAN bEnableEPG;
    void (*pfNotify_PMT)(U8 *pu8Section);
    void (*pfNotify_FileIn_PMT)(U8 *pu8Section);
    void (*pfNotify_NIT)(U8 *pu8Section);
    void (*pfNotify_SDT)(U8 *pu8Section);
    EN_SI_PROG_UPDATE_TYPE enProgUpdateType;
    U32 u32NITScanTimeOut;
    BOOLEAN bDisableOneSegProgFilter;
    U8 u8MaxServiceOneMux;
    BOOLEAN bEnablePATCRCcheck;
} MS_SI_INIT_PARAMETER;

/// Define information of ci plus content label
typedef struct
{
    /// iso 639 language
    U8 au8Iso639Lang[3];
    /// label char
    U8 au8LabelChar[SI_MAX_CIPLUS_LABEL_CHAR];
    /// min content byte
    U8 u8ContentByteMin;
    /// max content byte
    U8 u8ContentByteMax;

}MS_SI_CIPLUS_CONTENT_LABEL;

typedef struct
{
    U32 u32CentreFreq;
    U8  u8BW            :3; //bandwidth
    U8  u8fPriority     :1; //priority
    U8  u8fTimeSlice    :1; //Time_Slicing_indicator
    U8  u8fMPEGFEC      :1; //MPE-FEC_indicator
    U8  u8Reserved      :2; //reserved_future_use
    U8  u8Constellation :2; //constellation
    U8  u8hierarchyInfo :3; //hierarchy_information
    U8  u8CodeRateHPStr :3; //code_rate-HP_stream
    U8  u8CodeRateLPStr :3; //code_rate-LP_stream
    U8  u8GuardInt      :2; //guard_interval
    U8  u8XmitMode      :2; //transmission_mode
    U8  u8fOtherFreq    :1; //other_frequency
    U32 u32Reserved;
    BOOLEAN fFilled;        //flag to distinguish the descriptor is parsed and the structure is filled or not
} DESC_TERR_DEL_SYS; // Terrestrial delivery system descriptor

typedef struct
{
    U32 u32CentreFreq;
    U8 reserved1;
    U8 reserved2     :4;
    U8  u8FEC_outer            :4;
    U8  u8Modulation;
    U32  u32Symbol_rate    :28;
    U32  FEC_inner      :4;
    BOOLEAN fFilled;        //flag to distinguish the descriptor is parsed and the structure is filled or not
} DESC_CABLE_DEL_SYS; // Terrestrial delivery system descript

/// Define struct information of desc_satellite_del_sys
typedef struct
{
    U32 u32CentreFreq; ////K/10 Hz
    U16 u16Orbital_pos;
    U8 u8West_east_flag     :1;
    U8 u8Polarization       :2; //2 bits 00:linear-horizontal, 01:linear-vertical
    U8 u8Roll_off           :2; //00:0,35 , 01:0,25 ,10:0,20 for DVB-S2
    U8 u8Modulation_system  :1; //1 bits 0:DVB-S, 1:DVB-S2
    U8 u8Modulation_type    :2; //2 bits 00:Auto, 01:QPSK, 10:8PSK, 11:16-QAM(n/a for DVB-S2)
    U32  u32Symbol_rate     :28; //Ms/s
    U32  FEC_inner          :4;
    U16  u16Tsid;
    U16  u16Onid;
    U16  u16Nid;
    BOOLEAN fFilled;        //flag to distinguish the descriptor is parsed and the structure is filled or not
} DESC_SATELLITE_DEL_SYS; // Satellite delivery system descript

/// Define struct information of t2 cell centfreq
typedef struct _T2_CELLS_CENTREFREQ
{
    /// cell id
    U16 u16Cell;
    /// centfreq
    U32 u32CentreFreq[MAX_SI_T2_CENTREFREQ];
}T2_CELLS_CENTREFREQ;

/// Define struct information of desc_t2 delivery system
typedef struct
{
    /// plp_id
    U8  u8PLD;
    /// T2_system_id
    U16 u16T2SystemId;
    /// SISO/MISO
    U8  u8SISO_MISO;
    /// bandwidth
    U8  u8BW;
    /// guard_interval
    U8  u8GuardInt;
    /// transmission_mode
    U8  u8XmitMode;
    /// other_frequency flag
    U8  u8fOtherFreqFlag;
    /// tfs flag
    U8  u8TfsFlag;
    /// cell centfreq
    T2_CELLS_CENTREFREQ stT2CellCentreFreq[MAX_SI_T2_CELL_CENTREFREQ];

}DESC_T2_DEL_SYS; // T2 delivery system descriptor

typedef struct
{
    U16 wPMT_PID;
    U16 wVideo_PID;
    U16 wVideoType;
    FileIn_SI_AUD_INFO stAudInfo[SI_MAX_AUD_LANG_NUM];
    U16 wPCR_PID;
    U16 wSubtitle_PID;
} FileIn_SERVICE_INFO;

//========== SI table Monitor  End=============

#if (M7_DVBS_FAST_SCAN_ENABLE)

//========== SI FST table struct  Start=============

#define MAPI_SI_FST_MAX_SERVICE_NAME   32

/// Service List Descriptor
typedef struct
{
    U16 awService_ID[SI_MAX_VC_PER_PHYSICAL];
    MEMBER_SI_SERVICETYPE aeServiceType[SI_MAX_VC_PER_PHYSICAL];
}MS_SI_SERVICE_INFO;

/// Service Info Scratch from service descriptor
typedef struct
{
    /// service name
    U8 au8ServiceName[MAPI_SI_FST_MAX_SERVICE_NAME];
    /// service type
    U8 u8ServiceType;
}MS_SI_FST_SERVICE_DESC_INFO;

///to record the triple id for Nvod timeshifted services
typedef struct
{
    U16 u16OnId;
    U16 u16TsId;
    U16 u16SrvId;

}ST_TRIPLE_PROGRAM_ID;

/// Define service info carried in FST
typedef struct
{
    /// service triple id
    ST_TRIPLE_PROGRAM_ID  stTripleIds;
    /// service information scratch from service descriptor
    MS_SI_FST_SERVICE_DESC_INFO   stServiceFstDescInfo;
    /// Default video PID
    U16 u16DefaultVideoPID;
    /// Default audio PID
    U16 u16DefaultAudioPID;
    /// Default video ECM PID
    U16 u16DefaultVideo_ECM_PID;
    /// Default audio ECM PID
    U16 u16DefaultAudio_ECM_PID;
    /// Default PCR PID
    U16 u16PCRPID;
}MS_SI_FST_SERVICE_INFO;

/// Define FST struct Fast Scan Service table info
typedef struct
{   /// FST services info
    MS_SI_FST_SERVICE_INFO  stFstServiceListInfo[SI_MAX_VC_PER_PHYSICAL];
    /// Version Number
    U8 u8Version;
    /// ISO Reserved
    //U8 u8ISOReserve;
}MS_SI_TABLE_FST;

//========== SI FST table struct  END=============

//========== SI FNT table struct  Start=============
//#define MAX_DTV_FNT_MUX_NUMBER                    2000

/// In FNT TSInfo List Service info
typedef struct
{
    /// service_id
    U16  u16ServiceID;
/// Logical_channel_number
    U16  u16LCNNumber;
///service type
    U8   u8ServiceType;
///flag of service visible or not
    BOOLEAN bIsHidden;
}MS_SI_FNT_TS_SERVICE_INFO;

/// Define FNT Struct TSInfo Struct
typedef struct
{
    /// information of satellite delivery system descriptor
    DESC_SATELLITE_DEL_SYS stSatelliteDeliveryInfoList;
    ///service info
    MS_SI_FNT_TS_SERVICE_INFO  stFntSerivceList;
    /// original_network_id
    U16 u16ONID;
   /// transport_stream_id
    U16 u16TSID;
}MS_SI_FNT_TS_INFO;

/// Define FNT struct Fast Scan network table info
typedef struct
{
    /// Network id
    U16 u16NID;
    /// network name
    U8  au8NetWorkName[SI_MAX_NETWORK_NAME];
    /// network name length
    U8  u8NetWrokNameLen;
    /// Version Number
    U8 u8Version;
    /// ISO Reserved
    //U8 u8ISOReserve;
   ///Program Number Count
    U16 u16Service_Count;
   ///FNT services info
   MS_SI_FNT_TS_INFO  stFntTsInfoList[MAX_DTV_FNT_MUX_NUMBER];
}MS_SI_TABLE_FNT;

//========== SI FNT table struct  END=============

#endif //#if (M7_DVBS_FAST_SCAN_ENABLE)

#define FREEVIEWID         0x2F
#define SKYNETWODKID       0xA9
#define SI_MAX_MUX_IN_BAT  20
#define SI_MAX_BAT_SERVICE 50
typedef struct
{
    MS_LCN_INFO  stLcnInfo[SI_MAX_BAT_SERVICE];
    U16 u16OnId;
    U16 u16TsId;
} MS_SI_LCN_INFO;

/******************************************************************************/
/*                       Global Variable Declarations                         */
/******************************************************************************/
#ifdef MAPP_SI_C
#define INTERFACE
#else
#define INTERFACE extern
#endif
// for EWS Ui  to show warning
typedef struct
{
    U8 u8_EwsDisasterSymbol;
    U8 u8_EwsAuthor;
    U8 u8_EwsDisasterLoctionStatus; //EWS warnning level : 1 -high, 2 -middle, 3-low, 0xFF is invalid
    U8 u8_EwsLocationDisaster[SI_EWS_NUMBER_CHAR_LOCTION];   //from TRDW
    U8 u8_EwsDisasterType[SI_EWS_NUMBER_CHAR_DISASTER_TYPE];      //from TCDW
    U8 u8_EwsDisasterDate[SI_EWS_NUMBER_CHAR_DISASTER_DATE];      //from TCDW
    U8 u8_EwsDisasterLongitude[SI_EWS_NUMBER_CHAR_DISASTER_POSITION]; //from TCDW
    U8 u8_EwsDisasterCharacter[SI_EWS_NUMBER_CHAR_DISASTER_CHARACTER]; //from TCDW
    U8 u8_EwsDisasterRemark[SI_EWS_NUMBER_CHAR_MESSAGE];         //from TMDW
    bool bisValid;
} MS_EWSSETTING;

typedef struct
{
    U16 u16EWSAudioPID;
    U16 u16EWSAudioType;
    bool bisValid;
}MS_EWSAUDIOINFO;

typedef enum
{
    E_CHSAVE_BY_SDT,
    E_CHSAVE_BY_PAT,
    E_CHSAVE_BY_SDT_PAT,
}EN_CHSAVE_BY_TABLE;

/******************************************************************************/
/*                       Global Function Prototypes                           */
/******************************************************************************/
INTERFACE void MApp_SI_SetDebugLevel(U16 eDebugLevel);
extern void SetASTRA_HD_ENABLE(BOOLEAN bflag);
extern BOOLEAN GetASTRA_HD_ENABLE(void);
extern void Mapp_SI_Set_Ziggo_ENABLE(BOOLEAN bflag);
extern BOOLEAN Mapp_SI_Get_Ziggo_ENABLE(void);

INTERFACE void MApp_SI_SetLocationCode(U8* array);
INTERFACE void MApp_SI_GetEWSAudioInfo(MS_EWSAUDIOINFO* stAudioInfo);
INTERFACE void MApp_SI_GetEWSSetting(MS_EWSSETTING* stEwsSetting);
INTERFACE void MApp_SI_ExitEWS(void);

// API functions
INTERFACE U8 MApp_SI_GetSharpProjSelection(void);
INTERFACE void MApp_SI_Reset(SI_RESET_TYPE eType);
INTERFACE SI_MHEG5_STATUS MApp_SI_CheckMHEG5Status(void);
INTERFACE U16 MApp_SI_Get_Nit_NetworkID(void);
INTERFACE BOOLEAN MApp_SI_CheckCurProgScramble(void);
INTERFACE BOOLEAN MApp_SI_Get_UTCTime(U8* time);
INTERFACE U8 MApp_SI_Get_PSISIVersion(E_PSI_SI_VERSION eVerMember);
INTERFACE BOOLEAN MApp_SI_Is_Running(BOOLEAN *pu8Replacement);
INTERFACE void MApp_SI_MonitorRunningStatusbyServiceid(U16 u16ServiceID);
INTERFACE SI_SDT_RUNNINGSTATUS MApp_SI_GetRunningStatus(void);
INTERFACE U16 MApp_SI_Get_PMT_PID(void);

INTERFACE U16 MApp_SI_Get_CC_PID(void);
INTERFACE BOOLEAN MApp_SI_Get_NetWorkName(U8* name, U8* len, U8 u16MaxLen);
INTERFACE BOOLEAN MApp_SI_Scan_End(void);
INTERFACE BOOLEAN MApp_SI_Scan_Init(void);
INTERFACE void MApp_SI_Update_Time(BOOLEAN bAutoClock);
INTERFACE void MApp_SI_Get_Service_Replacement_Info(RP_SERVICE_INFO *stRP_Info);
INTERFACE void MApp_SI_Get_MoveServiceIDS(MOVE_SERVICE_IDS *pMoveSrv);
INTERFACE void MApp_SI_Disable_Auto_Update(BOOLEAN bDisable);//for MHEG5 quietly change channel
INTERFACE BOOLEAN MApp_SI_Is_Service_Change(MS_SI_CUR_SERVICE_INFO *pServiceInfo, E_SERVICE_CHANGE *pChangeType);
INTERFACE void MApp_SI_Reset_NetworkInfo(void);

INTERFACE void MApp_SI_ResetNetwork(void);
//FileIn function
INTERFACE U16 MApp_SI_GetFileInServiceID(void);
INTERFACE U16 MApp_SI_GetFileIn_PMT_PID(void);
//INTERFACE void MApp_SI_GetFileInPIDS(U16 *VideoPID, U16 *AudioPID, U16 *PCRPID, U16 *SubtPID);
INTERFACE void MApp_SI_GetFileInPIDS(FileIn_SERVICE_INFO *stFileInServiceInfo);
INTERFACE void MApp_SI_FileIn_Parse(void);


INTERFACE BOOLEAN MApp_SI_Action_CheckServiceInfo( SI_DTV_CHANNEL_INFO *pstVirtualCh );
INTERFACE BOOLEAN MApp_SI_Action_CheckServiceType( U8 u8OriginalType, U8* pNewType );

INTERFACE void MApp_SI_GetDtvPmgData(SI_SHORT_DTV_CHANNEL_INFO *pstDtvPmgDataNoSrvName, U8 SrvNameIdx, SI_DTV_CHANNEL_INFO *pstDtvPgmData);

INTERFACE U8 MApp_SI_GetString( U8 *pu8Dest, U8 u8DestBufLen, U8 *pu8Src, U8 u8SrcBufLen, U8 ControlCodes );
INTERFACE BOOLEAN MApp_SI_SetTimeZone(EN_SI_TIMEZONE eTimeZone);
INTERFACE BOOLEAN MApp_SI_IsAutoClockValid(void);
INTERFACE void MApp_SI_Table_Monitor(void);

#if 1//def ENABLE_DVB_S2
INTERFACE BOOLEAN MApp_SI_gets2tpInfo( SI_DTVPROGRAMID *pstVirtualCh );
#endif

INTERFACE void MApp_SI_Init(MS_SI_INIT_PARAMETER* pSIParameter);
INTERFACE SI_SHORT_DTV_CHANNEL_INFO*  MApp_SI_Get_PastVirtualCh(void);
INTERFACE U8 MApp_SI_GetScanNumOfPatItem(void);
INTERFACE MS_PAT_ITEM*  MApp_SI_Get_PastPATItem(void);

#if (ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
INTERFACE U16 MApp_SI_Get_SGT_PID(void);
INTERFACE MS_SGT_ITEM*  MApp_SI_Get_PastSGTItem(void);
INTERFACE U16 MApp_SI_GetCurrentServiceListID(void);
INTERFACE U16 MApp_SI_GetAvailableServiceListID(void);
INTERFACE U8 MApp_SI_GetScanNumOfSgtItem(void);
INTERFACE MS_SI_DESC_NIT_LINKAGE_INFO*  MApp_SI_Get_PastSGTNITLDItem(void);
#endif  // #if (ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)

INTERFACE void  MApp_SI_SetClockTimeZone(EN_SI_Clock_TimeZone eClock_TimeZone);
INTERFACE void  MApp_SI_SetDefaultCountry(EN_SI_COUNTRY_SETTING eSICountry);

INTERFACE BOOLEAN MApp_SI_IsTSChanged(void);
INTERFACE U8 * MApp_SI_FindLoopHead(U8 *pu8Section, EN_PSIP_TABLE enTable, EN_LOOP_TYPE enType);
INTERFACE U8 * MApp_SI_FindNextLoop(U8 *pu8Section, U8 *pu8LoopPosition, U16 u16TotalDescriptorLength, EN_PSIP_TABLE enTable);
INTERFACE void  MApp_SI_SetDefaultLanguage(EN_SI_LANGUAGE eSILanguage);
INTERFACE void MApp_SI_Force_PAT_Parse(void);
INTERFACE void MApp_SI_Force_PMT_Parse(void);
INTERFACE void MApp_SI_Force_NIT_Parse(void);
INTERFACE void MApp_SI_Force_SDT_Parse(void);
INTERFACE void MApp_Dmx_SetOADScanMode(BOOLEAN bEnable);
INTERFACE BOOLEAN MApp_Dmx_GetOADScanMode(void);
INTERFACE U16 MApp_Dmx_GetOADScanONID(void);
INTERFACE void MApp_Dmx_SetOADScanONID(U16 tempONID);
#if 1//ENABLE_OAD
INTERFACE void MApp_SI_ResetPATMonitor(void);
#endif

/*Network Update function*///ENABLE_UPDATE_MULTIPLEX_VIA_NIT
INTERFACE U8 MApp_SI_Get_New_RF_Index(void);
INTERFACE BOOLEAN MApp_SI_Reset_New_RF_Index(U8 u8RFIndex);
INTERFACE BOOLEAN MApp_SI_Is_NetworkChange(BOOLEAN *bMuxAdd, BOOLEAN *bMuxRemove, BOOLEAN *bCellRemove, BOOLEAN *bFreqChange);
INTERFACE BOOLEAN MApp_SI_RemoveMismatchedMux(void);
INTERFACE void MApp_SI_ResetNetworkNewService(void);
INTERFACE void MApp_SI_EnableNetworkCheck(BOOLEAN bEnable);
INTERFACE void MApp_SI_Free_NetworkChangeInfo(void);
INTERFACE void MApp_SI_AddNewTSService(void);
INTERFACE BOOLEAN MApp_SI_Recollect_TSRFList2Scan(U16 u16NID, U16 u16ONID, U16 u16TSID);
INTERFACE void MApp_SI_SetCheckFreqChange(BOOLEAN bFlag);
INTERFACE BOOLEAN MApp_SI_GetCheckFreqChange(void);
INTERFACE BOOLEAN MApp_SI_IS_GotTDTOrTOT(void);

/*********************/
/*NZ Time Display function*///ENABLE_NZ_EIT_TIME_DISPLAY
INTERFACE S32 MApp_SI_Get_OffsetTime(U32 u32Seconds, BOOLEAN *bDayLightTime, BOOLEAN *bGotTOT, BOOLEAN bIsStartTime);
/**********************/

/*SDT other montior function*///ENABLE_SDT_OTHER_MONITOR
INTERFACE BOOLEAN _MApp_SI_IsServiceMove(U16 u16SID, U16 u16LCN);
INTERFACE void MApp_SI_Reset_CheckSameServiceTimer(void);
INTERFACE BOOLEAN MApp_SI_Is_ChangeTOSameService(void);
/******************/
#if 1//ENABLE_DVBC
/*DVB-S*/
INTERFACE BOOLEAN  MApp_SI_GetNextSatParameter(MS_SAT_PARAMETER *desc,U16 *RemainFreq,BOOLEAN bUsed );
INTERFACE BOOLEAN  MApp_SI_GetSatParameterById(MS_SAT_PARAMETER *desc, U16 u16Tsid);
#endif
/*DVB-C*/
#if 1//ENABLE_DVBC
INTERFACE BOOLEAN  MApp_SI_GetNextCableParameter(MS_CABLE_PARAMETER *desc,MS_SERVICE_LIST_INFO** pServiceListInfo, MS_SERVICE_LCN_INFO** pLCNInfo, U16* pu16ServiceNumber, U16 *RemainFreq , BOOLEAN bUsed);
INTERFACE U16 MApp_SI_GetNetworkNumberFeq(void);
INTERFACE void ResetSDTParsingParameter(void);
INTERFACE U16 GetSDTParsingTSID(void);
INTERFACE void SetSDTParsingTSID(U16 u16TSID);
INTERFACE BOOLEAN IsSDTParsingTSIDUsed(U16 u16TSID);
#endif
/*DVB-T2*/
#if 1//def DVB_T2_ENABLE
INTERFACE  BOOLEAN MApp_SI_GetNextT2Parameter(U8 *pu8PLP_ID);
INTERFACE BOOLEAN MApp_SI_GetServiceGuidanceInfoTextWithIDs(U16 u16OnId, U16 u16TsId, U16 u16SrvId, U16* pu16DestBuf, U16 *pu16DestRetLen, U16 u16MaxDestLen);
INTERFACE BOOLEAN MApp_SI_GetServiceCMG(U8 *u8DoNotScramble, U8 *u8CtrlRemoteAOI, U8 *u8DoNotApplyRevococate);
#endif
INTERFACE BOOLEAN MApp_SI_GetLibVer(const MSIF_Version **ppVersion);
INTERFACE BOOLEAN MApp_SI_Is_Save_Audio(void);//20090806
INTERFACE void MApp_SI_Get_CICamBrandIdent(U16 *pu16Ident);
INTERFACE BOOLEAN MApp_SI_IsSdtOtherCome(void);
INTERFACE void MApp_SI_ResetSdtOtherComeFlag(void);
#if ENABLE_TARGET_REGION
INTERFACE MW_DVB_TARGET_REGION_INFO* MApp_SI_GetTargetRegionNameInfo(void);
INTERFACE BOOLEAN msAPI_CM_UpdateLCDV2(U8* pu8Country, U8 u8RegionId);
INTERFACE void MApp_SI_SetTargetRegion(U8* pu8Country, U8 u8PrimaryRegion, U8 u8SecondaryRegion, U16 u16Tertiary);
#endif
//#if ENABLE_SBTVD_BRAZIL_APP
INTERFACE BOOLEAN MApp_SI_Update_Audio(U8 tag, SI_LANG_ISO639 *pISOLangInfo, U8 u8AudioNumber);//20090806
//#endif
#if 1//ENABLE_DVBC
INTERFACE BOOLEAN MApp_SI_GetNextNetoworkInfo(MS_NETWORK_NAME_INFO* pInfo);
INTERFACE void MApp_SI_SetNetworkID(U16 u16NetworkID);
#endif
#if 1//def ENABLE_SAVE_MULTILINGUAL_SERVICE_NAME
INTERFACE void MApp_SI_SetSaveMultiLingualServiceNameNumber(U8 u8LanguageNumber);
INTERFACE BOOLEAN MApp_SI_GetMultiLingualServiceNameByID(U16 u16ServiceID, U8 u8Index, EN_SI_LANGUAGE* peLanguage, U8* pName, U8 u8MaxLen);
#endif
INTERFACE void MApp_SI_SetManualSumerTimeFlag(BOOLEAN bOnOff);
INTERFACE void MApp_SI_SetSumerTimeCountryFlag(BOOLEAN bOnOff);
INTERFACE BOOLEAN MApp_SI_GetLTOTimeFlag(void);
INTERFACE BOOLEAN MApp_SI_IsSummerTimeFlag(void);
INTERFACE void MApp_SI_SetSummerTimeOn(BOOLEAN bOnOff);
INTERFACE BOOLEAN MApp_SI_GetCurrentServiceName(U8 *pu8Buffer, U8 u8MaxBufSize);
INTERFACE BOOLEAN MApp_SI_GetSeviceNameByIndex(U8* pDest, U8 MaxLen, U8 u8Index);
#if(MHEG5_SIINFO_ENABLE)
INTERFACE BOOLEAN MApp_SI_GetProviderNameByIndex(U8* pDest, U8 MaxLen, U8 u8Index);
#endif //#if(MHEG5_SIINFO_ENABLE)
INTERFACE BOOLEAN MApp_SI_GetCurrentServiceTypeOrgValue(U8* pValue);

#if ENABLE_EPG_MUX
INTERFACE BOOLEAN MApp_SI_IsLinkageEPGExist(void);
INTERFACE BOOLEAN MApp_SI_GetEPGMUXInfo(U16 *pu16ONID, U16 *pu16TSID);
INTERFACE void MApp_SI_SetEPGMuxMode(BOOLEAN bON);
INTERFACE void MApp_SI_ResetEPGMUXInfo(void);
INTERFACE BOOLEAN MApp_SI_GetEPGMuxMode(void);
#endif
INTERFACE void MApp_SI_ResetTdtTot(EN_SI_TIME_TYPE enTimeType);
#if 1//def DVB_T2_ENABLE
INTERFACE void MApp_SI_AddT2DelSysDesc(U8 u8PLP_ID, BOOLEAN bUsed);
INTERFACE BOOLEAN  MApp_SI_GetNextT2Parameter(U8 *pu8PLP_ID);
INTERFACE void MApp_SI_FreeT2DelSysDesc(void);
#endif
INTERFACE void MApp_SI_SetAddOpChannel(BOOL bIsResetDb);
INTERFACE void MApp_SI_CICAM_NIT_Parse(U8 *pu8SectionData, U16 u16SecCount);
INTERFACE EN_SI_DELIVERY_SYS_TYPE MApp_SI_GetDeliveryTypeFromNIT(U8 *pu8SectionData, U16 u16SecCount);
INTERFACE BOOLEAN MApp_SI_CompareCIContentByte(U8 u8ContentByte, U8 *pu8LabelChar, U8 u8LabelLen);
INTERFACE void MApp_Dmx_PMT_FileIn_Parse(U8 *pu8Section);
INTERFACE BOOLEAN MApp_Dmx_GetDeliveryDescriptorData(EN_DESCRIPTOR_TAG enTag, void *punDesc, U8 *pu8Descp);
//INTERFACE void MApp_SI_Force_SDT_Parse(void);

//def ENABLE_PAT_BASE_PARSE
INTERFACE BOOLEAN MApp_SI_SetChannelTuningMode(EN_CHSAVE_BY_TABLE bChTunMode);
//def One Segment Signal
INTERFACE BOOLEAN MApp_SI_GetOneSegmentSignalData(void);
//Add TOT All Information
INTERFACE SI_TOT_MONITOR_ALL_INFO MApp_SI_GetTOTInfoAllData(void);
//Get SI Version
INTERFACE U16 MApp_Get_SI_VersionNumber(void);

//Def Service Name Show Or Not
INTERFACE BOOLEAN MApp_SI_SetServiceNameMode(BOOLEAN bChNameMode);

INTERFACE void MApp_Dmx_EnableFileInMonitorNumber(U16 u16ProgrammeNumberServiceID);

#if (M7_DVBS_FAST_SCAN_ENABLE)
INTERFACE void MApp_SI_Set_M7DVBS_OpenMonitor(BOOLEAN bEnable);
INTERFACE BOOLEAN MApp_SI_Get_M7DVBS_NetWorkName(U8* name, U8* len, U8 u16MaxLen);
#endif   // #if (M7_DVBS_FAST_SCAN_ENABLE)

INTERFACE U16 Mapp_SI_Get_SizeofStruct_SI_AUD_INFO(void);
INTERFACE U16 Mapp_SI_Get_SizeofStruct_SI_SHORT_DTV_CHANNEL_INFO(void);
INTERFACE U16 Mapp_SI_Get_SizeofStruct_MS_NETWORK_INFO(void);
INTERFACE U16 Mapp_SI_Get_SizeofStruct_SI_DTV_CHANNEL_INFO(void);
INTERFACE U16 Mapp_SI_Get_SizeofStruct_DTV_TS_RF_INFO(void);
INTERFACE U16 Mapp_SI_Get_SizeofStruct_MS_NETWORKID_TS(void);
INTERFACE U16 Mapp_SI_Get_SizeofStruct_MS_ALL_NETWORKID_INFO(void);
#if (ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
INTERFACE U16 Mapp_SI_Get_SizeofStruct_MS_SI_DESC_NIT_LINKAGE_INFO(void);
#endif
#if (M7_DVBS_FAST_SCAN_ENABLE)
INTERFACE U16 Mapp_SI_Get_SizeofStruct_MS_SI_FST_DATA(void);
INTERFACE U16 Mapp_SI_Get_SizeofStruct_MS_SI_FST_INFO(void);
#endif
INTERFACE U16 Mapp_SI_Get_SizeofEnum_E_SI_DATA_MEMBER(void);
INTERFACE void MApp_SI_GetBATLcn(U8 *pu8NumBatMux, MS_SI_LCN_INFO *pBatLcnInfo);

//#if ENABLE_CI_PLUS_V1_4
INTERFACE EN_SI_OSDT_SCHEME_TYPE MApp_SI_GetOSDTSchemeType(void);
//#endif
#undef INTERFACE

#endif//#if(ENABLE_DTV)
#endif

