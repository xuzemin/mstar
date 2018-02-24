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

#define MAPP_PSIP_C
////////////////////////////////////////////////////////////////////////////////
/// @file MApp_Psip.c
/// @author MStar Semiconductor Inc.
/// @brief Demux table parsing for APP layer
////////////////////////////////////////////////////////////////////////////////

/******************************************************************************/
/*                              Include files                                 */
/******************************************************************************/
// C Library
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Global Layer
#include "Board.h"
#include "datatype.h"
#if ENABLE_PAT_MUTISECTION
#include "Panel.h"
#endif
#include "drvpower_if.h"

// API Layer
#include "msAPI_Timer.h"
#include "msAPI_Memory.h"
#include "msAPI_MIU.h"
#include "msAPI_Mode.h"
#include "msAPI_Video.h"
#include "apiXC.h"
#include "apiXC_Sys.h"
#include "apiXC_ModeParse.h"
#include "apiXC_Cus.h"

// AP Layer
#include "MApp_Key.h"
#include "MApp_GlobalVar.h"
#include "MApp_GlobalFunction.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_RestoreToDefault.h"
#include "MApp_ChannelProc_ATSC.h"
#include "MApp_ChannelChange.h"
#include "MApp_Psip.h"
#include "MApp_HuffmanDecode.h"
#include "MApp_DataBase_ATSC.h"
#include "sysinfo.h"
#include "MApp_VChip.h"
#include "MApp_SaveData.h"
#include "msAPI_Tuner_ATSC.h"
#include "MApp_UiMenuDef.h"

#if ENABLE_OAD
#include "MApp_OAD.h"
#include "imginfo.h"
#endif
//#include "debug.h"

/*****************************************************************************/
/*                                 Macro                                       */
/*****************************************************************************/
// Debug message
#define DMX_PAT         0x01
#define DMX_PMT         0x02
#define DMX_STT         0x04
#define DMX_MGT         0x08
#define DMX_VCT         0x10
#define DMX_RRT         0x20
#define DMX_SCAN        0x40
#define DMX_EAS         0x80

#define DMX_DEBUG       0x00
#if (DMX_DEBUG)
#define DMX_DBG( flag, s )    { if (DMX_DEBUG & flag)    {s;} }
#else
#define DMX_DBG( flag, s )
#endif

#define DMX_PATCHECK_VERSION         0x01
#define DMX_PMTCHECK_VERSION         0x02
#define DMX_VCTCHECK_VERSION         0x04

#define DMX_VERSION_DEBUG       0x00

#if (DMX_VERSION_DEBUG)
#define DMX_VERSION_DBG( flag, s )    { if (DMX_VERSION_DEBUG & flag)    {s;} }
#else
#define DMX_VERSION_DBG( flag, s )
#endif



// Debug message for EIT/ETT
#define    EIT_MONITOR     0x01
#define    EIT_CB          0x02
#define    EIT_CHECK       0x04
#define    EIT_EVENT       0x08
#define    EIT_SETFLAG     0x10
#define    PARSE_MSS       0x20
#define    ETT_CHECK       0x40
#define    ETT_PARSE       0x80

#define    EIT_DEBUG       0x00

#if        (EIT_DEBUG)
#define    EIT_DBG( flag, s )    { if (EIT_DEBUG & flag)    {printf s;} }
#else
#define    EIT_DBG( flag, s )
#endif


#define AC3_DESCRIPTOR       0x01
#define DES_DEBUG 0x00
#if (DES_DEBUG)
#define DES_DBG( flag, s )    { if (DES_DEBUG & flag)    {s;} }
#else
#define DES_DBG( flag, s )
#endif



#define DMX_DBINFO(y) //y
#define DBG_CAD(msg) //msg
#define DBG_CSD(msg) //msg

#define CHECK_CA_DESC_ENABLE     1//check CA descriptor in PMT

#define ENABLE_VCT_TSID_MASK              1
#define SECTION_GET_ERROR_CHECK_TIME      5
#define PAT_SECTION_GET_ERROR_CHECK_TIME  5  //4 / / 4 is minimum
#define ENABLE_SKIP_RRT_NULL_MSS_VALUE    (0)
#define PARSE_SLD_IN_VCT                0
#define CHECK_TALBEFIELDS_BEFORE_VERCHANGE 1
#define EAS_MIN_DURATION_TIME   15 //sec.
#define EIT_DROP_INSERT_EVENT   0
#define SUPPORT_COMPONENT_NAME_DESCRIPTOR_FUNC 0

#define FILTER_4K_FOR_MGT_EAS   2
#define FILTER_4K_OTHER         4
#define FREE_FILTER_COUNT_EIT   (MSAPI_DMX_SEC4K_FILTER_NUMBER-FILTER_4K_FOR_MGT_EAS-FILTER_4K_OTHER)


#if (ENABLE_ATSC_EPG_DB_2016)
    #define PSIP_EIT_TABLE_NUMBER       NEW_MAX_TAB_NUM
    #define PSIP_ETT_TABLE_NUMBER       NEW_MAX_TAB_NUM
#else
    #define PSIP_EIT_TABLE_NUMBER       MAX_TBL_NUM
    #define PSIP_ETT_TABLE_NUMBER       MAX_TBL_NUM
#endif

#if( PSIP_EIT_TABLE_NUMBER == PSIP_ETT_TABLE_NUMBER )
    #define PSIP_EIT_ETT_TABLE_NUMBER   PSIP_EIT_TABLE_NUMBER
#endif

/*****************************************************************************/
/*                              Structures                                   */
/*****************************************************************************/
typedef struct
{
    U8    u8Tbl;            // denotes EIT-0, EIT-1, EIT-2, EIT-3 or ETT-0, ETT-1, ETT-2, ETT-3
    U8    u8SrcIdx;        // denotes source sequence in structure
    U8    u8TblID;        // Table ID - EIT >> 0xCB, ETT >> 0xCC
#if (ENABLE_ATSC_EPG_DB_2016)
    //U8    u8EitSaveIndex[NEW_MAX_TAB_NUM];    //
#else
    U8    u8EitSaveIndex[MAX_TBL_NUM];    //
#endif

    U8    u8VerNum;
    U16   u16SrcID;
    U16   u16EventID;
    U8    u8SecNum;
    U8    u8LastSecNum;
    U8    u8ProtocolVer;
    U8    u8NumOfEvents;
    U8    u8EventIdx;
#if (MONITOR_ETT_ALL)
    U16   u16EttTidExt;
#endif
} MS_EIT_PARSE_PARAM_ATSC;


#if (ENABLE_ATSC_EPG_DB_2016)
typedef struct
{
    // used to check if all sections of virtual channel has received
    U8              au8SecMask [NEW_MAX_TAB_NUM][MAX_SEG_NUM];          // 4 X 32 Bytes = 128 Bytes
    U8              u8CntSec[NEW_MAX_TAB_NUM];                          // 4 Bytes
} MS_SI_EPG_VCH_MASK;

static MS_SI_EPG_VCH_MASK stSiEpgSecMask[ATSC_EPG_VIR_CH_NUM];
#endif


/*****************************************************************************/
/*                          Static Local Variables                           */
/*****************************************************************************/
static U8 u8OpenedFltCounter;                              //Filter
static U8 au8CrcErrorCounter[MSAPI_DMX_MAX_FILTER_NUMBER]; //Filter

static U8 au8FID2ItemIdx[MSAPI_DMX_MAX_FILTER_NUMBER];     //PMT (filter id <=> PAT item)

#if (ENABLE_ATSC_EPG_DB_2016)
static U8 u8EttReceived[NEW_MAX_TAB_NUM];        //0: not received 1: received....this data will clear to zero while channel change
static U8 u8EttNumber;                           //Get Ett number in MGT
//static U8 au8EitFID2ItemIdx[MSAPI_DMX_MAX_FILTER_NUMBER];     //Eit (filter id <=> Eit item)
static MS_EPG_EVENT_New  g_stRxEventNew;
static MS_EPG_EVENT_New  g_stCurrentEvent;
#else
static U8 u8CheckEit0_3Received;
#endif

static U8 u8CurrentEitFilterUse;
//static U8 au8EttFID2ItemIdx[MSAPI_DMX_MAX_FILTER_NUMBER];     //Ett (filter id <=> Ett item)

static U16 au16PID2ItemIdx[MSAPI_DMX_MAX_FILTER_NUMBER];     //PMT (filter id <=> PAT item)

static MS_SOUND_TRACK_ATSC astSoundTrackPMT[MAX_AUD_LANG_NUM_ATSC];
static U8 u8Version;

static BOOLEANS gPSIPVal;
#define DecompressSetFilterDelay        gPSIPVal.bBOOL_0
#define g_fPatTimeout                   gPSIPVal.bBOOL_1
#define g_fIsUTF16                      gPSIPVal.bBOOL_2
#define bEASGotData                     gPSIPVal.bBOOL_3
#define bIsEASinProgress                gPSIPVal.bBOOL_4
#define bIsZeroRemainTime               gPSIPVal.bBOOL_5
#define g_fPatTimeoutNeedRecover        gPSIPVal.bBOOL_6


// variables for demux parsing function
static U16 u16ActualTSid;
static U8 u8FirstSectionNo;
static U8 u8LastSectionNo;
static U8 u8ErrorCheckCount;


// timer variables which are used to monitor table
static U32 u32MonitorSttTimer;                          //monitor system timer count
static U32 u32MonitorMgtTimer;                             //monitor MGT timer count
static U32 u32MonitorVctTimer;                             //monitor VCT timer count
static U32 u32MonitorPatTimer;                             //monitor PAT timer count
static U32 u32MonitorRRTTimer;                             //monitor RRT timer count
static U32 u32MonitorPmtTimer;                             //monitor PMT timer count
#if ENABLE_OAD
static void MApp_Dmx_PMT_Other_Monitor_Cb(U8 u8FID, U32 enEvent);
static BOOLEAN bAllPmtReady = FALSE;
static U32 u32MonitorPmtOtherTimer;             // monitor PMT timer count
static U8 u8ServicePMTIndex = 0;
static U16 u16ServiceIdArray[MAX_VC_PER_PHYSICAL];
static U16 u16PmtPidArray[MAX_VC_PER_PHYSICAL];
static U16 u8CurPatItemNum = 0;
#endif
static void MApp_Dmx_EIT_Cb(U8 u8FID, DMX_EVENT enEvent);
static void MApp_Dmx_EIT_For_RRT_Monitor(void);
static U32 u32MonitorEasTimer;                             //monitor EAS timer count
static U32 g_u32MonitorCADTimer;
static U16 u16ProgramNumberArray[MAX_VC_PER_PHYSICAL];

// flag for table timeout monitor


// EAS Variables
static U32 u32EasProcessTimer;
static U16 u16EATtextLength;
static U8 u8EAStimeRemaining;

#if PARSE_SLD_IN_VCT
// variables for audio language flag in vct
static U16 u16AudLangNumflag;
#endif

static MS_PAT_ITEM_ATSC g_PSIP_astPATItem[MAX_VC_PER_PHYSICAL]; //PAT Items
#define pastPATItem     (g_PSIP_astPATItem)

#if (SUPPORT_COMPONENT_NAME_DESCRIPTOR_FUNC)
//----------------------------------------------------------------
#define MAX_CND_BUFF_LENGTH             256
static U8 au8CompoenetDesBuff[MAX_CND_BUFF_LENGTH]; //CND string buffer
//----------------------------------------------------------------
#endif

#if 0
typedef enum
{
    GET_SCAN_TABLE_1,
    GET_SCAN_TABLE_2,
    GET_SCAN_TABLE_3,
    GET_SCAN_TABLE_4
} STATE_GET_SCAN_TABLE;
static STATE_GET_SCAN_TABLE enGetScanTableState = GET_SCAN_TABLE_1;

static U8 u8ReceivedSecNum;
static U8 u8ScanTbl2_Loop;
#endif

static code ST_AUD_LANG_ATSC iso639_LanguageCode[] =
{
    {{'e','n','g'}, AUD_LANG_ENG}, // English
    {{'f','r','a'}, AUD_LANG_FRA}, // French
    {{'s','p','a'}, AUD_LANG_SPA}, // Spanish
    {{'f','r','e'}, AUD_LANG_FRA}, // French
    {{'e','s','l'}, AUD_LANG_SPA}, // Spanish
    {{'k','o','r'}, AUD_LANG_KOR}, // Korean
    {{'j','p','n'}, AUD_LANG_JPN}, // Japanese
    {{'c','h','i'}, AUD_LANG_CHI}, // Chinese
    {{'z','h','o'}, AUD_LANG_CHI}, // Chinese
    {{'c','o','n'}, AUD_LANG_CHI}, // Chinese

    {{'e','n','m'}, AUD_LANG_ENG}, // English, Middle (ca. 1100-1500)
    {{'a','n','g'}, AUD_LANG_ENG}, // English, Old (ca. 450-1100)
    {{'f','r','m'}, AUD_LANG_FRA}, // French, Middle (ca. 1400-1600)
    {{'f','r','o'}, AUD_LANG_FRA}, // French, Old (842- ca. 1400)

// ISO 639: 2-letter codes
    {{'e','n',0x00}, AUD_LANG_ENG}, // English
    {{'f','r',0x00}, AUD_LANG_FRA}, // French
    {{'e','s',0x00}, AUD_LANG_SPA}, // Spanish
    {{'j','a',0x00}, AUD_LANG_JPN}, // Japanese
    {{'k','o',0x00}, AUD_LANG_KOR}, // Korean
    {{'z','h',0x00}, AUD_LANG_CHI}, // Chinese

#if (ENABLE_NON_STANDARD_ISO639LANGUAGE_CODE)
    {{'E','N','G'}, AUD_LANG_ENG},
    {{'F','R','A'}, AUD_LANG_FRA},
    {{'S','P','A'}, AUD_LANG_SPA},
    {{'F','R','E'}, AUD_LANG_FRA},
    {{'E','S','L'}, AUD_LANG_SPA},
    {{'K','O','R'}, AUD_LANG_KOR},
    {{'J','P','N'}, AUD_LANG_JPN},
    {{'C','H','I'}, AUD_LANG_CHI},
#endif
};

static MS_EIT_PARSE_PARAM_ATSC   stEitParseParam;
U32 g_u32StreamTime = 0;

/*****************************************************************************/
/*                               Functions                                      */
/*****************************************************************************/
#if 0
// Disable it to avoid the shadow compliering warning.
static void MApp_Dmx_DumpSectionData(U16 u16SecLength)
{
    printf("Section Data @ 0x%X, u16SectionLength: %x", au8Section, u16SecLength);

    for(iu16Loop_i = 0; iu16Loop_i < u16SecLength + 3; iu16Loop_i++)
    {
        if((iu16Loop_i % 16) == 0)
            printf("\r\n");

        printf("%02bx ", au8Section[iu16Loop_i]);
    }

    printf("\r\n");
}
#endif

static EN_AUD_LANG MApp_Dmx_GetISO639LangCode(U8 *pStrSource)
{
    for(iu8Buffer_i=0; iu8Buffer_i<COUNTOF(iso639_LanguageCode); iu8Buffer_i++)
    {
        if(memcmp(pStrSource, iso639_LanguageCode[iu8Buffer_i].au8AudLangCode, 3) == 0)
        {
            return iso639_LanguageCode[iu8Buffer_i].enAudLangIndex;
        }
    }
    return AUD_LANG_UND;
}
/*****************************************************************************/
#define DestBufferOffset    2
#define DestBufferTerminLen 2
#define DestBufferLength    4096
static S32 MApp_Dmx_Parse_MSS (U8* pu8_dst, U8 *pu8_src, S32 s32DestBuf_Len, BOOLEAN bEnMutiLang)
{
    U8	  u8_loop_i;
    U8	  u8_loop_j, u8_loop_k;
    U8	  number_strings;
    U8	  number_segments;
    S32   number_bytes = 0;
    S32   decomp_len32 = 0;
    BOOLEAN bStopProcessFlag, bLangFound;
    U16 u16DestBufIndex=0;
    BOOLEAN bForceLangSaved, bFirstLangSaved, bMatchLangFound;
    //U8 u8FirstLangBuf[DestBufferLength] = {0};
    U8* pu8_FirstLangBuf = 0;

    U16 u16FirstLangBufIndex=0;

    //printf("MApp_Dmx_Parse_MSS(pu8_dst=0x%X, pu8_src=0x%X,s32DestBuf_Len=%u)\n", (U32)pu8_dst,(U32)pu8_src,s32DestBuf_Len);

    pu8_FirstLangBuf = msAPI_Memory_Allocate( DestBufferLength, BUF_ID_ATSC_PARSE_MSS);
    if( pu8_FirstLangBuf == NULL )
    {
        printf("\nError: memory alloc failed!\n");
        return (u16DestBufIndex+DestBufferTerminLen); // Why?
    }
    //printf("pu8_FirstLangBuf=0x%X)\n", (U32)pu8_FirstLangBuf);


        g_fIsUTF16 = FALSE;

        number_strings = pu8_src[0];
        pu8_src += 1;

        bLangFound = FALSE;
        bStopProcessFlag = FALSE;
        u16DestBufIndex = DestBufferOffset;//Two Bytes to store string length

        bForceLangSaved = FALSE;
        bFirstLangSaved = FALSE;
        u16FirstLangBufIndex = DestBufferOffset;

        EIT_DBG(PARSE_MSS, ("\n[MSS] number_string = %bX, len=%lu\n", number_strings, s32DestBuf_Len));

        if(s32DestBuf_Len>DestBufferLength)
        {
            s32DestBuf_Len = (S32)DestBufferLength;
        }


        for (u8_loop_i = 0; u8_loop_i<number_strings; u8_loop_i++)
        {
            EIT_DBG(PARSE_MSS, ("Lang = \"%c%c%c\"\r\n", pu8_src[0], pu8_src[1], pu8_src[2]));

            if(bStopProcessFlag == TRUE)
                break;

#if 1
            u8_loop_k = MApp_Dmx_GetISO639LangCode(pu8_src);

            if(u8_loop_k != AUD_LANG_UND)
                bLangFound = TRUE;
#else
            for (u8_loop_k = 0; u8_loop_k<AUD_LANG_NUM; u8_loop_k++)
            {
                if(memcmp(pu8_src, iso639_LanguageCode[u8_loop_k].au8AudLangCode, 3) == 0)
                {
                    bLangFound = TRUE;
                    break;
                }

#if (ENABLE_NON_STANDARD_ISO639LANGUAGE_CODE)
                if(memcmp(pu8_src, stLanguageCodeExtraCase[u8_loop_k].au8AudLangCode, 3) == 0)
                {
                    bLangFound = TRUE;
                    break;
                }
#endif
            }
#endif
            if(bEnMutiLang)
            {
                bMatchLangFound = FALSE;
                if(bLangFound)
                {
                    switch(MENU_LANGUAGE)
                    {
                        default:
                        case LANGUAGE_ENGLISH:
                            if((AUD_LANG_ENG == u8_loop_k))
                            {
                                bMatchLangFound = TRUE;
                            }
                        break;
                        case LANGUAGE_FRENCH:
                            if(AUD_LANG_FRA == u8_loop_k)
                            {
                                bMatchLangFound = TRUE;
                            }
                            else if(AUD_LANG_FRE == u8_loop_k)
                            {
                                bMatchLangFound = TRUE;
                            }
                        break;
                        case LANGUAGE_SPANISH:
                            if(AUD_LANG_SPA == u8_loop_k)
                            {
                                bMatchLangFound = TRUE;
                            }
                            else if(AUD_LANG_ESL == u8_loop_k)
                            {
                                bMatchLangFound = TRUE;
                            }
                        break;
#if ENABLE_LANGUAGE_KOREA
                        case LANGUAGE_KOREA:
                            if(AUD_LANG_KOR == u8_loop_k)
                            {
                                bMatchLangFound = TRUE;
                            }
                        break;
#endif
                    }
                }

                if(number_strings == 1)  //only one language
                {
                    bLangFound = TRUE;
                    bMatchLangFound = TRUE;
                }
                else if((bLangFound == TRUE) && (bMatchLangFound == FALSE)
                            && (bFirstLangSaved == FALSE) && (bForceLangSaved == FALSE))
                {
                    bForceLangSaved = TRUE;
                    bMatchLangFound = TRUE;
                }
            }
            else
            {
                bForceLangSaved = FALSE;
                bMatchLangFound = TRUE;
            }

            number_segments = pu8_src[3];
            pu8_src += 4;

            EIT_DBG(PARSE_MSS, ("number_segments = %bX\n", number_segments));

            for (u8_loop_j = 0; u8_loop_j<number_segments; u8_loop_j++)
            {
                number_bytes = pu8_src[2];
                EIT_DBG(PARSE_MSS,("u16DestBufIndex = %d, number_bytes = %d, s32DestBuf_Len =%d\n",
                u16DestBufIndex, number_bytes, s32DestBuf_Len));

                if((u16DestBufIndex + number_bytes + DestBufferTerminLen)>(s32DestBuf_Len))
                {
                    number_bytes = s32DestBuf_Len - u16DestBufIndex - DestBufferTerminLen;
                }

                if (bStopProcessFlag == FALSE && bLangFound == TRUE)
                {
                    EIT_DBG(PARSE_MSS, ("compression_type = %bX, mode = %bX\n", pu8_src[0], pu8_src[1]));
                    EIT_DBG(PARSE_MSS, ("number_bytes = %bX\n", number_bytes));

                    if (pu8_src[0] != 0)	// compression_type
                    {
                        if(bMatchLangFound)
                        {
                            DecompressSetFilterDelay = TRUE;

                            if (bForceLangSaved)
                            {
                                decomp_len32 = DecodeStr(&pu8_src[3], number_bytes, pu8_src[0], &pu8_FirstLangBuf[u16FirstLangBufIndex],(s32DestBuf_Len-u16FirstLangBufIndex));
                                if (decomp_len32 > 0)
                                {
                                    bFirstLangSaved = TRUE;
                                    u16FirstLangBufIndex += (decomp_len32-1);
                                }
                            }
                            else
                            {
                                decomp_len32 = DecodeStr(&pu8_src[3], number_bytes, pu8_src[0], &pu8_dst[u16DestBufIndex],(s32DestBuf_Len-u16DestBufIndex));
                                if (decomp_len32 > 0)
                                {
                                    u16DestBufIndex += (decomp_len32-1); //remove 'TERM 0x00'
                                }
                            }
                        }

                        EIT_DBG(PARSE_MSS, ("After Deompressed:%bX bytes, %bX\n", decomp_len32, u16DestBufIndex));
                    }
                    else
                    {
                        DecompressSetFilterDelay = FALSE;

                        if(bMatchLangFound)
                        {
                            if (bForceLangSaved)
                            {
                                bFirstLangSaved = TRUE;
                                    memcpy(&pu8_FirstLangBuf[u16FirstLangBufIndex], &pu8_src[3], number_bytes);
                                u16FirstLangBufIndex += number_bytes;
                            }
                            else
                            {
                                memcpy(&pu8_dst[u16DestBufIndex], &pu8_src[3], number_bytes);
                                u16DestBufIndex += number_bytes;
                            }
                        }

                        EIT_DBG(PARSE_MSS, ("No Deompressed:%bX, number_bytes=%d\n", u16DestBufIndex, number_bytes));
                    }

                    //20120827 Max: need reserve 2bytes for storing string length and 2bytes for \0
                    if( u16DestBufIndex >= (s32DestBuf_Len - DestBufferOffset - DestBufferTerminLen))
                    {
                        bStopProcessFlag = TRUE;
                    }

#if ENABLE_LANGUAGE_KOREA
                    if (pu8_src[1] == 0)		// mode - ISO Latin-1
                    {
                        pu8_dst[0] = number_bytes;

                        pu8_dst[(number_bytes+DestBufferTerminLen)] = '\0';
                        EIT_DBG(PARSE_MSS, ("compressed_strnig_bytes = \"%s\"\r\n", pu8_dst+1));
                        //cc: KR
                        g_fIsUTF16 = FALSE;
                    }
                    else if (pu8_src[1] == 0x3F)	// mode - UTF-16
                    {
                        //printf("\nnumber_bytes: 0x%LX", number_bytes);
                        pu8_dst[0]=number_bytes;
                        pu8_dst[number_bytes+DestBufferTerminLen] = '\0';
                        //cc: KR
                        g_fIsUTF16 = TRUE;
                    }
#else
                    if (pu8_src[1] == 0)		// mode - ISO Latin-1
                    {
                        //printf(" g_fIsUTF16 = FALSE; \r\n");
                        g_fIsUTF16 = FALSE;
                    }
                    else if (pu8_src[1] == 0x3F)	// mode - UTF-16
                    {
                        //printf(" g_fIsUTF16 = TRUE; \r\n");
                        g_fIsUTF16 = TRUE;
                    }
#endif
                }
                pu8_src = pu8_src + 3 + number_bytes;

                if( bStopProcessFlag == TRUE )
                break;
            }

			//Get only one language segment for each language
            if((number_segments > 0) && (u16DestBufIndex > DestBufferOffset))
            {
                bStopProcessFlag = TRUE;
            }

            bLangFound = FALSE;
            bForceLangSaved =FALSE;
        }

        if(bEnMutiLang && (u16DestBufIndex == DestBufferOffset))
        {
            pu8_FirstLangBuf[0] = ((u16FirstLangBufIndex-DestBufferOffset) >> 8);
            pu8_FirstLangBuf[1] = (u16FirstLangBufIndex-DestBufferOffset);
            pu8_FirstLangBuf[u16FirstLangBufIndex] = '\0';
            pu8_FirstLangBuf[u16FirstLangBufIndex+1] = '\0';
            memcpy(&pu8_dst[0], &pu8_FirstLangBuf[0], u16FirstLangBufIndex);
            u16DestBufIndex = u16FirstLangBufIndex;
        }
        else
        {
            pu8_dst[0] = ((u16DestBufIndex-DestBufferOffset) >> 8);
            pu8_dst[1] = (u16DestBufIndex-DestBufferOffset);
            pu8_dst[u16DestBufIndex] = '\0';
            pu8_dst[u16DestBufIndex+1] = '\0';
        }

    EIT_DBG(PARSE_MSS, ("Final u16DestBufIndex = %d, Dst_buf =%s, FirstLangBuf=%s.\r\n", u16DestBufIndex, &pu8_dst[DestBufferOffset], &pu8_FirstLangBuf[DestBufferOffset]));

    if( pu8_FirstLangBuf )
    {
        MSAPI_MEMORY_FREE(pu8_FirstLangBuf, BUF_ID_ATSC_PARSE_MSS);
    }

    return (u16DestBufIndex+DestBufferTerminLen);
}


/*****************************************************************************/
#if defined(ENABLE_PARSE_SAME_DIMENSION_IN_RRT5_CAD) && ENABLE_PARSE_SAME_DIMENSION_IN_RRT5_CAD
#define DBG_CR(msg) //msg
static U8* MApp_Dmx_Parse_CAD_RRT5(U8 *pu8CAD, MS_EPG_RATING *pRating)
{
    U8 u8rated_dimensions = pu8CAD[1];
    DBG_CR(printf("\n[region 5] u8_rated_dimensions = %d", pu8CAD[1]));

    // pu8CAD[1] is number of rated dimensions
    for (iu8Loop_j = 0; iu8Loop_j < u8rated_dimensions; iu8Loop_j++)
    {
        pu8CAD += 2;
        #if 0
        //Don't set these flags to 0.
        //Stream may send region 1 and region 5 CAD at the same time.
        //Ex. Sarnoff RRT test stream R24MSR.trp
        //pRating->u8CaEngFlag = 0;
        //pRating->u8CaFreFlag = 0;
        //pRating->u8MPAAFlag = 0;
        #endif

        DBG_CR(printf("\n[region 5] %d, %d", pu8CAD[0], pu8CAD[1] & 0x0F));

        if ((pu8CAD[1] & 0x0F) == 0) // because we store the value - 1. Thus it can not be 0
        {
            continue;
        }

#if 0
        // marked out because CAD may be received before RRT is received
        // ex. RRT is resetted
        if (pu8CAD[0] >= stGenSetting.g_VchipRegion5.u8NoDimension)
        {
            DBG_CR(printf("\n[region 5] skip invalid dim %d", pu8CAD[0]));
            continue;
        }
#endif

        DBG_CR(printf("\n[region 5] %d values defined in dim %d",
            stGenSettingVchipRegion5.stRegin5Dimension[pu8CAD[0]].u8Values_Defined,
            pu8CAD[0]));

#if 0 // defined(ENABLE_RRT5_RATING_VALUE_CHECK) && ENABLE_RRT5_RATING_VALUE_CHECK
        // marked out because CAD may be received before RRT is received
        // ex. RRT is resetted
        if ((pu8CAD[1] & 0x0F) > (stGenSetting.g_VchipRegion5.stRegin5Dimension[pu8CAD[0]].u8Values_Defined))
        {
            DBG_CR(printf("\n[region 5] skip rating value %d", (pu8CAD[1] & 0x0F));)
            continue;
        }
#endif

        // check rating_dimension_j
        switch (pu8CAD[0])
        {
            case 0:
                pRating->u8DownloadableRatingD1 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 1:
                pRating->u8DownloadableRatingD2 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 2:
                pRating->u8DownloadableRatingD3 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 3:
                pRating->u8DownloadableRatingD4 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 4:
                pRating->u8DownloadableRatingD5 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 5:
                pRating->u8DownloadableRatingD6 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 6:
                pRating->u8DownloadableRatingD7 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 7:
                pRating->u8DownloadableRatingD8 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 8:
                pRating->u8DownloadableRatingD9 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 9:
                pRating->u8DownloadableRatingD10 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
#if(ENABLE_MAX_RRT_DIMENSION_NUMBER)
            case 10:
                pRating->u8DownloadableRatingD11 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 11:
                pRating->u8DownloadableRatingD12 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 12:
                pRating->u8DownloadableRatingD13 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 13:
                pRating->u8DownloadableRatingD14 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 14:
                pRating->u8DownloadableRatingD15 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 15:
                pRating->u8DownloadableRatingD16 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 16:
                pRating->u8DownloadableRatingD17 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 17:
                pRating->u8DownloadableRatingD18 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 18:
                pRating->u8DownloadableRatingD19 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 19:
                 pRating->u8DownloadableRatingD20 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                 break;
            case 20:
                pRating->u8DownloadableRatingD21 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 21:
                pRating->u8DownloadableRatingD22 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 22:
                pRating->u8DownloadableRatingD23 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 23:
                pRating->u8DownloadableRatingD24 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 24:
                pRating->u8DownloadableRatingD25 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 25:
                pRating->u8DownloadableRatingD26 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 26:
                pRating->u8DownloadableRatingD27 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 27:
                pRating->u8DownloadableRatingD28 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 28:
                pRating->u8DownloadableRatingD29 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 29:
                pRating->u8DownloadableRatingD30 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 30:
                pRating->u8DownloadableRatingD31 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 31:
                pRating->u8DownloadableRatingD32 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 32:
                pRating->u8DownloadableRatingD33 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 33:
                pRating->u8DownloadableRatingD34 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 34:
                pRating->u8DownloadableRatingD35 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 35:
                pRating->u8DownloadableRatingD36 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 36:
                pRating->u8DownloadableRatingD37 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 37:
                pRating->u8DownloadableRatingD38 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 38:
                pRating->u8DownloadableRatingD39 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 39:
                pRating->u8DownloadableRatingD40 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;
            case 40:
                pRating->u8DownloadableRatingD41 |= 0x01 << ((pu8CAD[1] & 0x0F) - 1);
                break;

#endif
            default:
                break;
        }
    }
    return pu8CAD;
}
#endif

static BOOLEAN MApp_Dmx_Parse_Tag_CAD (U8 *pu8CAD, MS_EPG_RATING *pRating)
{
    U8  u8_loop_i;
    U8  u8_loop_j;
    U8  u8_rating_region_count;
    U8  u8_rated_dimensions = 0;
    U8  u8_rating_description_length;
    U8  u8_RatingRegion;
    U8  *pu8CADes;

    DBG_CAD( printf("\n[Parse_Tag_CAD] pRating->fRatingRxIsOK = %d, TV rating for entire: %d",
             pRating->fRatingRxIsOK, (U8)pRating->u8TVRatingForEntire); )
/*
    DBG_CAD(
        if (pRating->fRatingRxIsOK)
        {
            extern void MApp_VChip_DumpEPGRating(MS_EPG_RATING * r);
            MApp_VChip_DumpEPGRating(pRating);
        }
    )
*/
    pRating->u8MPAARatingD2 =0;

    pu8CADes = pu8CAD;

    if(pu8CADes != NULL)
    {
        u8_rating_region_count = (pu8CADes[2] & 0x3F);
        DBG_CAD(printf("\nu8_rating_region_count = %d", u8_rating_region_count); )

        pu8CADes += 3;

        for (u8_loop_i = 0; u8_loop_i < u8_rating_region_count; u8_loop_i++)
        {
            u8_RatingRegion = pu8CADes[0];
            DBG_CAD(printf("\nregion %d", u8_RatingRegion));
            // rating_region = 1 >> American
            if (u8_RatingRegion == 1)
            {
                u8_rated_dimensions    = pu8CADes[1];

                if (u8_rated_dimensions)
                {
                    pRating->fRatingRxIsOK = TRUE;
                }
                DBG_CAD(printf("\n[region 1] u8_rated_dimensions = %d", u8_rated_dimensions));

                for (u8_loop_j = 0; u8_loop_j < u8_rated_dimensions;u8_loop_j++)
                {
                    pu8CADes += 2;

                    DBG_CAD(printf("\n[region 1] pu8CADes[0] = %d, %d", pu8CADes[0], pu8CADes[1] & 0x0F));

                    if ((pRating->u8TVRatingForEntire == INVALID_TV_RATING_FOR_ENTIRE)
                        && ((pu8CADes[0] == 0) || (pu8CADes[0] == 5)))
                    {
                        //indicate region 1 was been received
                        pRating->u8TVRatingForEntire = 0x00;
                    }

                    // check rating_dimension_j
                    switch (pu8CADes[0])
                    {
                        case 0:
                            if ((pu8CADes[1] & 0x0F) <= 5)
                            {
                                pRating->u8TVRatingForEntire = pu8CADes[1] & 0x0F;
                            }
                            else
                            {
                                DBG_CAD(printf("\ninvalid TVRatingForEntire %d", pu8CADes[1] & 0x0F));
                            }
                            break;
                        case 1:
                            if ((pu8CADes[1] & 0x0F) <= 1)
                            {
                                pRating->fDialog = pu8CADes[1] & 0x0F;
                            }
                            else
                            {
                                DBG_CAD(printf("\ninvalid Dialog %d", pu8CADes[1] & 0x0F));
                            }
                            break;
                        case 2:
                            if ((pu8CADes[1] & 0x0F) <= 1)
                            {
                            pRating->fLanguage = pu8CADes[1] & 0x0F;
                            }
                            else
                            {
                                DBG_CAD(printf("\ninvalid Language %d", pu8CADes[1] & 0x0F));
                            }
                            break;
                        case 3:
                            if ((pu8CADes[1] & 0x0F) <= 1)
                            {
                            pRating->fSexualContent = pu8CADes[1] & 0x0F;
                            }
                            else
                            {
                                DBG_CAD(printf("\ninvalid SexualContent %d", pu8CADes[1] & 0x0F));
                            }
                            break;
                        case 4:
                            if ((pu8CADes[1] & 0x0F) <= 1)
                            {
                                pRating->fViolence = pu8CADes[1] & 0x0F;
                            }
                            else
                            {
                                DBG_CAD(printf("\ninvalid Violence %d", pu8CADes[1] & 0x0F));
                            }

                            break;
                        case 5:
                            if ((pu8CADes[1] & 0x0F) <= 2)
                            {
                                pRating->u8TVRatingForChild = pu8CADes[1] & 0x0F;
                            }
                            else
                            {
                                DBG_CAD(printf("\ninvalid TVRatingForChild %d", pu8CADes[1] & 0x0F));
                            }
                            break;
                        case 6:
                            if ((pu8CADes[1] & 0x0F) <= 1)
                            {
                                pRating->fFantasyViolence = pu8CADes[1] & 0x0F;
                            }
                            else
                            {
                                DBG_CAD(printf("\ninvalid FantasyViolence %d", pu8CADes[1] & 0x0F));
                            }
                            break;
                        case 7:
                            // According to CEA-766-A Table 3, only 1~8 are valid
                        {
                            U8 tempval = pu8CADes[1] & 0x0F ;
                            if (tempval >= 1 && tempval <= 8)
                            {
                                pRating->u8MPAAFlag = 1;
                                pRating->u8MPAARatingD2 |= 1<<(tempval-1);
                            }
                            else
                            {
                                DBG_CAD(printf("\ninvalid MPAA rating %d", tempval));
                            }
                        }
                            break;
                        default:
                            break;
                    }
                }

                u8_rating_description_length = pu8CADes[2];

                pu8CADes += 3 + u8_rating_description_length;
            }
            else if (u8_RatingRegion == 2 ) // Canadian Rating Region
            {
                u8_rated_dimensions    = pu8CADes[1];
                if (u8_rated_dimensions)
                {
                    pRating->fRatingRxIsOK = TRUE;
                }
                DBG_CAD(printf("\n[region 2] u8_rated_dimensions = %d", u8_rated_dimensions));

                for (u8_loop_j = 0; u8_loop_j < u8_rated_dimensions;u8_loop_j++)
                {
                    pu8CADes += 2;

                    DBG_CAD(printf("\n[region 2] pu8CADes[0] = %d, %d", pu8CADes[0], pu8CADes[1] & 0x0F));
                    // check rating_dimension_j
                    switch (pu8CADes[0])
                    {
                        case 0: // Canadian English Language Rating
                            // According to CEA-766-A Table 4
                            // Only 0~6 are valid
                            if ((pu8CADes[1] & 0x0F) >=0 && (pu8CADes[1] & 0x0F) <= 6)
                            {
                            pRating->u8CaEngFlag = 1;
                            pRating->u8CaEngRatingD0 = pu8CADes[1] & 0x0F;
                            }
                            else
                            {
                                DBG_CAD(printf("\ninvalid CaEng rating %d", pu8CADes[1] & 0x0F));
                            }
                            break;

                        case 1: // Canadian French Language Rating
                            // According to CEA-766-A Table 4
                            // Only 0~5 are valid
                            if ((pu8CADes[1] & 0x0F) >=0 && (pu8CADes[1] & 0x0F) <= 5)
                            {
                                pRating->u8CaFreFlag = 1;
                                pRating->u8CaFreRatingD1 = pu8CADes[1] & 0x0F;
                            }
                            else
                            {
                                DBG_CAD(printf("\ninvalid CaFre rating %d", pu8CADes[1] & 0x0F));
                            }
                            break;

                        default:
                            break;
                    }
                }

                u8_rating_description_length = pu8CADes[2];

                pu8CADes += 3 + u8_rating_description_length;
            }
#if (ENABLE_MEXICO_VCHIP)
            else if (u8_RatingRegion >= 5 )// Downloadable U.S. (50 states+ possessions) rating system
#else
            else if (u8_RatingRegion == 5 )// Downloadable U.S. (50 states+ possessions) rating system
#endif
            {
#if (ENABLE_MEXICO_VCHIP)
                u8CurrentRrtRegionNo = u8_RatingRegion;
#endif

#if defined(ENABLE_PARSE_SAME_DIMENSION_IN_RRT5_CAD) && ENABLE_PARSE_SAME_DIMENSION_IN_RRT5_CAD
                pu8CADes = MApp_Dmx_Parse_CAD_RRT5(pu8CADes, pRating);
#else
                u8_rated_dimensions    = pu8CADes[1];

                if (u8_rated_dimensions)
                {
                    pRating->fRatingRxIsOK = TRUE;
                }

                for (u8_loop_j = 0; u8_loop_j < u8_rated_dimensions;u8_loop_j++)
                {
                    pu8CADes += 2;

                    #if 0
                    //Don't set these flags to 0.
                    //Stream may send region 1 and region 5 CAD at the same time.
                    //Ex. Sarnoff RRT test stream R24MSR.trp
                    pRating->u8CaEngFlag = 0;
                    pRating->u8CaFreFlag = 0;
                    pRating->u8MPAAFlag = 0;
                    #endif

                    // check rating_dimension_j
                    switch (pu8CADes[0])
                    {
                        case 0:
                            pRating->u8DownloadableRatingD1 = pu8CADes[1] & 0x0F;
                            break;
                        case 1:
                            pRating->u8DownloadableRatingD2 = pu8CADes[1] & 0x0F;
                            break;
                        case 2:
                            pRating->u8DownloadableRatingD3 = pu8CADes[1] & 0x0F;
                            break;
                        case 3:
                            pRating->u8DownloadableRatingD4 = pu8CADes[1] & 0x0F;
                            break;
                        case 4:
                            pRating->u8DownloadableRatingD5 = pu8CADes[1] & 0x0F;
                            break;
                        case 5:
                            pRating->u8DownloadableRatingD6 = pu8CADes[1] & 0x0F;
                            break;
                        case 6:
                            pRating->u8DownloadableRatingD7 = pu8CADes[1] & 0x0F;
                            break;
                        case 7:
                            pRating->u8DownloadableRatingD8 = pu8CADes[1] & 0x0F;
                            break;
                        case 8:
                            pRating->u8DownloadableRatingD9 = pu8CADes[1] & 0x0F;
                            break;
                        case 9:
                            pRating->u8DownloadableRatingD10 = pu8CADes[1] & 0x0F;
                            break;
#if(ENABLE_MAX_RRT_DIMENSION_NUMBER)
                        case 10:
                            pRating->u8DownloadableRatingD11 = pu8CADes[1] & 0x0F;
                            break;
                        case 11:
                            pRating->u8DownloadableRatingD12 = pu8CADes[1] & 0x0F;
                            break;
                        case 12:
							pRating->u8DownloadableRatingD13 = pu8CADes[1] & 0x0F;
                            break;
                        case 13:
                            pRating->u8DownloadableRatingD14 = pu8CADes[1] & 0x0F;
                            break;
                        case 14:
                            pRating->u8DownloadableRatingD15 = pu8CADes[1] & 0x0F;
                            break;
                        case 15:
                            pRating->u8DownloadableRatingD16 = pu8CADes[1] & 0x0F;
                            break;
                        case 16:
                            pRating->u8DownloadableRatingD17 = pu8CADes[1] & 0x0F;
                            break;
                        case 17:
                            pRating->u8DownloadableRatingD18 = pu8CADes[1] & 0x0F;
                            break;
                        case 18:
                            pRating->u8DownloadableRatingD19 = pu8CADes[1] & 0x0F;
                            break;
                        case 19:
                            pRating->u8DownloadableRatingD20 = pu8CADes[1] & 0x0F;
                            break;
                        case 20:
                            pRating->u8DownloadableRatingD21 = pu8CADes[1] & 0x0F;
                        break;
                        case 21:
                            pRating->u8DownloadableRatingD22 = pu8CADes[1] & 0x0F;
                        break;
                        case 22:
                            pRating->u8DownloadableRatingD23 = pu8CADes[1] & 0x0F;
                        break;
                        case 23:
                            pRating->u8DownloadableRatingD24 = pu8CADes[1] & 0x0F;
                        break;
                        case 24:
                            pRating->u8DownloadableRatingD25 = pu8CADes[1] & 0x0F;
                        break;
                        case 25:
                            pRating->u8DownloadableRatingD26 = pu8CADes[1] & 0x0F;
                        break;
                        case 26:
                            pRating->u8DownloadableRatingD27 = pu8CADes[1] & 0x0F;
                        break;
                        case 27:
                            pRating->u8DownloadableRatingD28 = pu8CADes[1] & 0x0F;
                        break;
                        case 28:
                            pRating->u8DownloadableRatingD29 = pu8CADes[1] & 0x0F;
                        break;
                        case 29:
                            pRating->u8DownloadableRatingD30 = pu8CADes[1] & 0x0F;
                        break;
                        case 30:
                            pRating->u8DownloadableRatingD31 = pu8CADes[1] & 0x0F;
                        break;
                        case 31:
                            pRating->u8DownloadableRatingD32 = pu8CADes[1] & 0x0F;
                        break;
                        case 32:
                            pRating->u8DownloadableRatingD33 = pu8CADes[1] & 0x0F;
                        break;
                        case 33:
                            pRating->u8DownloadableRatingD34 = pu8CADes[1] & 0x0F;
                        break;
                        case 34:
                            pRating->u8DownloadableRatingD35 = pu8CADes[1] & 0x0F;
                        break;
                        case 35:
                            pRating->u8DownloadableRatingD36 = pu8CADes[1] & 0x0F;
                        break;
                        case 36:
                            pRating->u8DownloadableRatingD37 = pu8CADes[1] & 0x0F;
                        break;
                        case 37:
                            pRating->u8DownloadableRatingD38 = pu8CADes[1] & 0x0F;
                        break;
                        case 38:
                            pRating->u8DownloadableRatingD39 = pu8CADes[1] & 0x0F;
                        break;
                        case 39:
                            pRating->u8DownloadableRatingD40 = pu8CADes[1] & 0x0F;
                        break;
                        case 40:
                            pRating->u8DownloadableRatingD41 = pu8CADes[1] & 0x0F;
                        break;
#endif
                        default:
                            break;
                    }
                }
#endif

                u8_rating_description_length = pu8CADes[2];

                pu8CADes += 3 + u8_rating_description_length;
            }
            else // 3:Taiwan, 4:South Korean
            {
                u8_rated_dimensions    = pu8CADes[1];

                if (u8_rated_dimensions)
                {
                    pRating->fRatingRxIsOK = TRUE;
                }
                for (u8_loop_j = 0; u8_loop_j < u8_rated_dimensions;u8_loop_j++)
                {
                    pu8CADes += 2;
                }
                u8_rating_description_length = pu8CADes[2];
                pu8CADes += 3 + u8_rating_description_length;

            }
        }

        pRating->fRatingRxIsOK = TRUE;

        return TRUE;
    }
    else
    {
        pRating->fRatingRxIsOK = TRUE;
        return FALSE;
    }
}
/*****************************************************************************/
#if (!ENABLE_ATSC_EPG_DB_2016)
static BOOLEAN MApp_Dmx_Parse_Tag_CSD (U8 *pu8CSD, MS_EPG_EVENT *pEvent)
{
    U8  u8_number_of_services = 0;
    BOOLEAN bRet = FALSE;
    U8  *pu8CSDes;

    DBG_CSD(printf("\n[Parse_Tag_CSD]\n ");)

    pu8CSDes = pu8CSD;

    if(pu8CSDes != NULL)
    {
        u8_number_of_services  = (pu8CSDes[2] & 0x1F);
        DBG_CSD(printf("Caption service number = %bx\n", (U8)u8_number_of_services);)

        if (u8_number_of_services == 0)
        {
            pEvent->fHasCCInfo = FALSE;
            return FALSE;
        }

        if (u8_number_of_services > MAX_CAPTION_SERVICE_NUMBER)
        {
            u8_number_of_services = MAX_CAPTION_SERVICE_NUMBER;
            printf("caption service number invalid\n");
        }
		pEvent->stCaptionService.u8NumOfService = u8_number_of_services;
        for (iu8Loop_i = 0; iu8Loop_i < MAX_CAPTION_SERVICE_NUMBER ; iu8Loop_i++)
        {
            memset(&pEvent->stCaptionService.stCaptionServiceItem[iu8Loop_i], 0x00, sizeof(MS_EPG_Caption_Service_Item));
        }

        pu8CSDes += 3;
        pEvent->fHasCCInfo = TRUE;

        for (iu8Loop_i = 0; iu8Loop_i < u8_number_of_services; iu8Loop_i++)
        {
            memcpy(&pEvent->stCaptionService.stCaptionServiceItem[iu8Loop_i].au8Language[0], &pu8CSDes[0], 3);

            //4  u8CaptionSrvNum, bEasy_Reader and bWide_aspect_ratio are vaild only when bDigital_CC is true.
            pEvent->stCaptionService.stCaptionServiceItem[iu8Loop_i].bDigital_CC = GETBIT(pu8CSDes[3], 7);
            if (pEvent->stCaptionService.stCaptionServiceItem[iu8Loop_i].bDigital_CC)
            {
                /* Digital */
                pEvent->stCaptionService.stCaptionServiceItem[iu8Loop_i].u8CaptionSrvNum = (pu8CSDes[3] & 0x3F);
                pEvent->stCaptionService.stCaptionServiceItem[iu8Loop_i].bEasy_Reader = GETBIT(pu8CSDes[4], 7);
                pEvent->stCaptionService.stCaptionServiceItem[iu8Loop_i].bWide_aspect_ratio = GETBIT(pu8CSDes[4], 6);
            }
            else
            {
                /* Analog */
                pEvent->stCaptionService.stCaptionServiceItem[iu8Loop_i].bLin21_field = GETBIT(pu8CSDes[3], 0);
            }

            //next caption service
            pu8CSDes+= 6;

            DBG_CSD(printf ("===>[%bx] u8NumOfService=%d, bDigital_CC=%bx,  u8CaptionSrvNum=%bx, %bx, %bx, %bx, lang=%c%c%c\n", iu8Loop_i,
                pEvent->stCaptionService.u8NumOfService,
                (U8)pEvent->stCaptionService.stCaptionServiceItem[iu8Loop_i].bDigital_CC,
                (U8)pEvent->stCaptionService.stCaptionServiceItem[iu8Loop_i].u8CaptionSrvNum,
                (U8)pEvent->stCaptionService.stCaptionServiceItem[iu8Loop_i].bLin21_field,
                (U8)pEvent->stCaptionService.stCaptionServiceItem[iu8Loop_i].bEasy_Reader,
                (U8)pEvent->stCaptionService.stCaptionServiceItem[iu8Loop_i].bWide_aspect_ratio,
                pEvent->stCaptionService.stCaptionServiceItem[iu8Loop_i].au8Language[0], pEvent->stCaptionService.stCaptionServiceItem[iu8Loop_i].au8Language[1], pEvent->stCaptionService.stCaptionServiceItem[iu8Loop_i].au8Language[2]
                );)
        }

        bRet = TRUE;
    }

    return bRet;
}
#endif

static BOOLEAN MApp_Dmx_PMT_CheckSoundTrackData(void)
{
    U8 u8i =0;
    BOOLEAN bRet = FALSE;
    for(u8i = 0; u8i< pstVirtualCh->u8AudLangNum; u8i++)
    {
        if((pstVirtualCh->astSoundTrack[u8i].u8AudPidInPMT))
        {
            if(astSoundTrackPMT[u8i].u16AudioPid != pstVirtualCh->astSoundTrack[u8i].u16AudioPid)
            {
                bRet = TRUE;
                DMX_DBG(DMX_PMT, printf("[PMT VerChg]index = %d audio pid changed! Old = 0x%x --> New = 0x%x\n", u8i, pstVirtualCh->astSoundTrack[u8i].u16AudioPid, astSoundTrackPMT[u8i].u16AudioPid));
                break;
            }

            if(pstVirtualCh->astSoundTrack[u8i].u16AC3inPMT)
            {
                if(astSoundTrackPMT[u8i].u8AudAc3Bsmod != pstVirtualCh->astSoundTrack[u8i].u8AudAc3Bsmod)
                {
                    bRet = TRUE;
                    DMX_DBG(DMX_PMT, printf("[PMT VerChg]index = %d Ac3Bsmod changed! Old = 0x%x --> New = 0x%x\n", u8i, pstVirtualCh->astSoundTrack[u8i].u8AudAc3Bsmod, astSoundTrackPMT[u8i].u8AudAc3Bsmod));
                    break;
                }

                if(pstVirtualCh->astSoundTrack[u8i].u16IsAudLangGetinPMT)
                {
                    if(astSoundTrackPMT[u8i].u8AudLangIdx != pstVirtualCh->astSoundTrack[u8i].u8AudLangIdx)
                    {
                        bRet = TRUE;
                        DMX_DBG(DMX_PMT, printf("[PMT VerChg]index = %d u16AudLangIdx changed! Old = 0x%x --> New = 0x%x\n", u8i, pstVirtualCh->astSoundTrack[u8i].u8AudLangIdx, astSoundTrackPMT[u8i].u8AudLangIdx));
                        break;
                    }
                }

                if(astSoundTrackPMT[u8i].u8Priority != pstVirtualCh->astSoundTrack[u8i].u8Priority)
                {
                    bRet = TRUE;
                    DMX_DBG(DMX_PMT, printf("[PMT VerChg]index = %d u8Priority changed! Old = 0x%x --> New = 0x%x\n", u8i, pstVirtualCh->astSoundTrack[u8i].u8Priority, astSoundTrackPMT[u8i].u8Priority));
                    break;
                }
            }
        }
    }
    return bRet;
}



void MApp_Dmx_Parse_AC3Descriptor(U8 *pu8Section, MAPI_PSIP_AC3_DES_A* pstAC3Descriptor)
{
    U8 u8Descriptor_length = (pu8Section[1]);
    U8 u8DescriptorIndex = 2;
    U8 u8AC3SyntaxIndex = 2;
    U8 u8Sample_rate_Code = 0;
    U8 u8Bsid = 0;
    U8 u8BiteRateCode = 0;
    U8 u8SurroundMode = 0;
    U8 u8NumberOfChannel = 0;
    U8 u8BsMod = 0;
    U8 u8FullSVC = 0;
    U8 u8LangCode = 0;
    U8 u8LangCode2 = 0;
    U8 u8MainID = 0;
    U8 u8Priority = 0;
    U8 u8ASVCFlag = 0;
    U8 u8TextLength = 0;
    U8 u8TextCode = 0;
    U8 u8LangFlag1 = 0;
    U8 u8LangFlag2 = 0;
    U8 u8Lang1[3] ={0};
    U8 u8Lang2[3] ={0};
    DES_DBG(AC3_DESCRIPTOR, printf("[TAG_AC3AD] u8Descriptor_length:%d\n", u8Descriptor_length));
    DES_DBG(AC3_DESCRIPTOR, printf("[TAG_AC3AD] Raw Data: "));
    while(u8DescriptorIndex < (u8Descriptor_length+1))
    {
        switch(u8AC3SyntaxIndex)
        {
            case EN_PSIP_AC3_SAMPLE_RATE_BSID:
            {
                u8Sample_rate_Code = ((pu8Section[u8DescriptorIndex]>>5));
                u8Bsid = ((pu8Section[u8DescriptorIndex])&(0x1f));
            }
            break;

            case EN_PSIP_AC3_BIT_RATE_SURROUND:
            {
                u8BiteRateCode = ((pu8Section[u8DescriptorIndex]>>2));
                u8SurroundMode = ((pu8Section[u8DescriptorIndex])&(0x3));
            }
            break;

            case EN_PSIP_AC3_BSMOD_CHANNEL_SVC:
            {
                u8BsMod = (pu8Section[u8DescriptorIndex]>>5);
                u8NumberOfChannel = ((pu8Section[u8DescriptorIndex]>>1)&(0xf));
                u8FullSVC = ((pu8Section[u8DescriptorIndex])&(0x1));
            }
            break;

            case EN_PSIP_AC3_LANGCODE:
            {
                u8LangCode = (pu8Section[u8DescriptorIndex]);
                if(u8NumberOfChannel != 0)
                    u8AC3SyntaxIndex++;
            }
            break;


            case EN_PSIP_AC3_LANGCODE2:
            {
                if(u8NumberOfChannel == 0)
                    u8LangCode2 = (pu8Section[u8DescriptorIndex]);
            }
            break;

            case EN_PSIP_AC3_MAINID_PRIORITY_ASVC:
            {
                if(u8BsMod < 2)
                {
                    u8MainID = (pu8Section[u8DescriptorIndex]>>5);
                    u8Priority = ((pu8Section[u8DescriptorIndex]>>3)&0x3);
                }
                else
                {
                    u8ASVCFlag = (pu8Section[u8DescriptorIndex]);
                }
            }
            break;
            case EN_PSIP_AC3_TEXT_LENGTH:
            {
                u8TextLength = (pu8Section[u8DescriptorIndex]>>1);
                u8TextCode = (pu8Section[u8DescriptorIndex]&0x1);
                if(u8TextLength == 0)
                    u8AC3SyntaxIndex++;
            }
            break;

            case EN_PSIP_AC3_TEXT:
                {
                    U8 u8Text[256] ={0};
                    for(iu8Loop_l=0 ; iu8Loop_l < u8TextLength ; iu8Loop_l++)
                    {
                        memcpy(&u8Text[iu8Loop_l], &pu8Section[u8DescriptorIndex], 1);
                        u8DescriptorIndex++;
                        //printf("%x \n", u8Text[iu8Loop_l]);
                    }
                }
            break;

            case EN_PSIP_AC3_LANGFLAG:
            {
                u8LangFlag1 = pu8Section[u8DescriptorIndex]>>7;
                u8LangFlag2 = (pu8Section[u8DescriptorIndex]>>6)&0x1;
            }
            break;

            case EN_PSIP_AC3_LANG_1:
            {
                if(u8LangFlag1)
                {
                    //need total three bytes.....or treat it is abnormal data
                    if((u8DescriptorIndex+2) < (u8Descriptor_length+2))
                    {
                        memcpy(&u8Lang1[0], &(pu8Section[u8DescriptorIndex]),3);
                        DES_DBG(AC3_DESCRIPTOR, printf("%x %x", pu8Section[u8DescriptorIndex], pu8Section[u8DescriptorIndex+1]));
                        u8DescriptorIndex = u8DescriptorIndex+2; //language 3bytes...so need add extra 2 for index!
                    }
                }
            }
            break;

            case EN_PSIP_AC3_LANG_2:
            {
                if(u8LangFlag2)
                {
                    //need total three bytes.....or treat it is abnormal data
                    if((u8DescriptorIndex+2) < (u8Descriptor_length+2))
                    {
                        memcpy(&u8Lang2[0], &(pu8Section[u8DescriptorIndex]),3);
                        DES_DBG(AC3_DESCRIPTOR, printf("%x %x", pu8Section[u8DescriptorIndex], pu8Section[u8DescriptorIndex+1]));
                        u8DescriptorIndex = u8DescriptorIndex+2; //language 3bytes...so need add extra 2 for index!
                    }
                }
            }
            break;
            default:
            break;
        }
        u8AC3SyntaxIndex++;
        DES_DBG(AC3_DESCRIPTOR, printf("%x ", pu8Section[u8DescriptorIndex]));
        u8DescriptorIndex++;
    }
    DES_DBG(AC3_DESCRIPTOR, printf("\n"));
    pstAC3Descriptor->u8Sample_rate_Code = u8Sample_rate_Code;
    pstAC3Descriptor->u8Bsid = u8Bsid;
    pstAC3Descriptor->u8BiteRateCode = u8BiteRateCode;
    pstAC3Descriptor->u8SurroundMode = u8SurroundMode;
    pstAC3Descriptor->u8BsMod = u8BsMod;
    pstAC3Descriptor->u8NumberOfChannel = u8NumberOfChannel;
    pstAC3Descriptor->u8FullSVC = u8FullSVC;
    pstAC3Descriptor->u8MainID = u8MainID;
    pstAC3Descriptor->u8Priority = u8Priority;
    pstAC3Descriptor->u8LangFlag1 = u8LangFlag1;
    pstAC3Descriptor->u8LangFlag2 = u8LangFlag2;
    DES_DBG(AC3_DESCRIPTOR, printf("================================================\n"));
    DES_DBG(AC3_DESCRIPTOR, printf("u8Sample_rate_Code = %d, u8Bsid = %d,  u8BiteRateCode =%d\n", u8Sample_rate_Code, u8Bsid, u8BiteRateCode));
    DES_DBG(AC3_DESCRIPTOR, printf("u8BsMod = %d, u8NumberOfChannel = %d,  u8FullSVC =%d\n", u8BsMod, u8NumberOfChannel, u8FullSVC));
    DES_DBG(AC3_DESCRIPTOR, printf("u8LangFlag1 = %d, u8LangFlag2 = %d, u8Lang1 =%s\n", u8LangFlag1, u8LangFlag2, u8Lang1));
    DES_DBG(AC3_DESCRIPTOR, printf("================================================\n"));
    memcpy(&(pstAC3Descriptor->u8Lang1[0]), &u8Lang1[0],3);
    memcpy(&(pstAC3Descriptor->u8Lang2[0]), &u8Lang2[0],3);
}




/*****************************************************************************/
static U8 * MApp_Dmx_FindFirstLoop(U8 *pu8Section, EN_PSIP_TABLE enTable)
{
    U16 u16SecLength;
    U16 u16TotalDescriptorLength;
    /*[01]check error condition =============================================*/
    /*
    if( pu8Section == NULL )
    {
       return NULL;
    }
    */

    /*[02]get section length ================================================*/
    u16SecLength = ((pu8Section[1] & 0x0f) << 8) | pu8Section[2];
    u16SecLength += 3;

    /*[03]find first item position ==========================================*/
    switch(enTable)
    {
        case EN_PMT:
            {
                /* skip all descriptors in program info. loop */
                u16TotalDescriptorLength = ((pu8Section[10] & 0x0f) << 8) | pu8Section[11];
                iu8Ptr = pu8Section + 12 + u16TotalDescriptorLength;
                break;
            }
        case EN_TVCT:
            {
                iu8Ptr = pu8Section + 10;
                break;
            }
        case EN_EIT:
            {
                iu8Ptr = pu8Section + 10;
                break;
            }
        case EN_ETT:
            {
                iu8Ptr = pu8Section + 13;
                break;
            }
        default:
            {
                iu8Ptr = NULL;
                break;
            }
    }

    /*[04]check error condition ==============================================*/
    if((U32) iu8Ptr >= (U32) (pu8Section + u16SecLength - 4))
    {
        iu8Ptr = NULL;
    }

    return iu8Ptr;
}
/*****************************************************************************/
static U8 * MApp_Dmx_FindNextLoop(U8 *pu8Section, U8 *pu8LoopPosition_func, U16 u16TotalDescriptorLength, EN_PSIP_TABLE enTable)
{
    U16 u16SecLength;
    /*[01]check error condition ===================================================*/
    /*
    if( pu8Section == NULL || pu8LoopPosition == NULL )
    {
       return NULL;
    }
    */

    /*[02]get section length ================================================*/
    u16SecLength = ((pu8Section[1] & 0x0f) << 8) | pu8Section[2];
    u16SecLength += 3;

    /*[03]for each kind of table ============================================*/
    switch(enTable)
    {
        case EN_PMT:
            {
                pu8LoopPosition_func += (5 + u16TotalDescriptorLength);

                /*[04]check error condition ==============================================*/
                if((U32) pu8LoopPosition_func >= (U32) (pu8Section + u16SecLength - 4))
                    pu8LoopPosition_func = NULL;
                break;
            }
        case EN_TVCT:
            {
                pu8LoopPosition_func += (32 + u16TotalDescriptorLength);
                break;
            }
        #if 0
        case EN_EIT:
            {
                pu8LoopPosition += (12 + u16TotalDescriptorLength);

                /*[04]check error condition ==============================================*/
                if((U16) pu8LoopPosition >= (U16) (pu8Section + u16SecLength - 4))
                    pu8LoopPosition = NULL;
                break;
            }
        #endif
        default:
            {
                pu8LoopPosition_func = NULL;
                break;
            }
    }

    return pu8LoopPosition_func;
}
/*****************************************************************************/
static U8 * MApp_Dmx_FindDescriptorTag(U8 *pu8Descriptor, U8 u8Tag, S16 s16TotalDescriptorLength)
{
    U16 u16DescriptorLength;

    /*[01]check error condition ===================================================*/
    /*
    if( pu8Descriptor == NULL )
    {
       return NULL;
    }
    */

    /*[02]search until last byte ==================================================*/
    while(s16TotalDescriptorLength > 0)
    {
        /* got desired descriptor */
        if(pu8Descriptor[0] == u8Tag)
        {
            return pu8Descriptor;
        }

        /* move to next descriptor */
        u16DescriptorLength = pu8Descriptor[1] + 2;
        s16TotalDescriptorLength -= u16DescriptorLength;
        pu8Descriptor += u16DescriptorLength;
    }

    return NULL;
}
/*****************************************************************************/
#if 0//jhsiang, 2bytes case, ENABLE_LANGUAGE_KOREA
static U8 MApp_Dmx_GetServiceName(MS_VIRTUAL_CHANNEL *pstVirtualCh_func, U8 *pu8Src,U8 u8BufSize, U8 u8StrLength)
{
    U8  u8Loop_i,u8Buffer_i=0;
    pstVirtualCh_func->CharIdxLength = CHAR_IDX_2BYTE;
    if(pu8Src[0])
    {
        u8BufSize--;
        for(u8Loop_i = 0; u8Loop_i<u8StrLength && u8Loop_i<u8BufSize; u8Loop_i++)
        {
            //cc: KR
            pstVirtualCh_func->acServiceName[u8Buffer_i] = pu8Src[u8Loop_i];
            u8Buffer_i++;
        }

        pstVirtualCh_func->acServiceName[u8Buffer_i] = 0;
    }

    return u8Buffer_i;
}
#else
static void MApp_Dmx_GetServiceName( MS_VIRTUAL_CHANNEL *pstVirtualCh_func, U8 *pu8Src, U8 u8BufSize, U8 u8StrLength )
{
    U8  u8ShortName_i, u8Buffer_i;
    U16 codeUTF16;

    // Coverity-CID-185048
    if( u8BufSize <= 2 )
    {
        return;
    }

    //pstVirtualCh_func->CharIdxLength = CHAR_IDX_2BYTE;
    for ( u8ShortName_i = 0, u8Buffer_i = 0 ; u8Buffer_i < u8BufSize-1 ; ++u8ShortName_i )
    {
        if ( u8ShortName_i < u8StrLength )
            codeUTF16 = ((U16)(pu8Src[u8ShortName_i<<1]) << 8) + pu8Src[(u8ShortName_i<<1) + 1];
        else
            codeUTF16 = 0;

        /* skip two bytes control codes, please refer to EN300 468 Annex A.1 */
        if ( codeUTF16 >= 0xE080 && codeUTF16 <= 0xE09F )
            continue;

//        pstVirtualCh_func->acServiceName[u8Buffer_i] = codeUTF16;
//        ++u8Buffer_i;

            pstVirtualCh_func->acServiceName[u8Buffer_i] = HIGHBYTE(codeUTF16);
            u8Buffer_i++;
            pstVirtualCh_func->acServiceName[u8Buffer_i] = LOWBYTE(codeUTF16);
            u8Buffer_i++;

    }
    pstVirtualCh_func->acServiceName[u8BufSize-1] = 0; // end of string
    pstVirtualCh_func->acServiceName[u8BufSize-2] = 0; // end of string

    return;
}
#endif
/*****************************************************************************/
U16 MApp_Dmx_MakeBuildChNo( MS_PAT_ITEM_ATSC *pastPATItem_func, U8 u8ChannelIndex, U16 u16ProgramNo )
{
    U16     u16BuildChNo;
    MS_U8     fIsExist = FALSE;

    if ( u16ProgramNo > MAX_MINOR_NO )
    {
        u16BuildChNo = (u16ProgramNo % (MAX_MINOR_NO+1)) - 1;
        do
        {
            fIsExist = FALSE;
            u16BuildChNo += 1;
            if (u16BuildChNo > MAX_MINOR_NO)
            {
                u16BuildChNo = 1;
            }

            for(iu8Loop_k = 0; iu8Loop_k < u8ChannelIndex; iu8Loop_k++)
            {
                if ( pastPATItem_func[iu8Loop_k].u16BuildChNumber == u16BuildChNo )
                {
                    fIsExist = TRUE;
                    break;
                }
            } /* end of for loop of programs */



        } while (fIsExist || (u16BuildChNo == 0));
    }
    else
    {
        u16BuildChNo = u16ProgramNo;
    }

    DMX_DBG(DMX_PAT, printf("== programNo : %u -> buildChNo : %u\n", u16ProgramNo, u16BuildChNo));
    return u16BuildChNo;
}

#if ENABLE_OAD
static void MApp_Dmx_Other_PMT_Parse(U8 *pu8Section)
{
    U8 u8Tag;
    U16 u16DescriptorLength,u16TotalParseLength;
    U16       u16TotalDescriptorLength;
    U8                       *pu8LoopPosition;
    U8                       *pu8Descriptor;
    U16 u16DSMCC_PID = MSAPI_DMX_INVALID_PID;
    U16 u16Service_ID;
    u16Service_ID = TSGetU16(&pu8Section[3]);
    {
        pu8LoopPosition = MApp_SI_FindLoopHead(pu8Section,EN_PMT,EN_SECONDLOOP);
        while(pu8LoopPosition != NULL)
        {
            u16TotalDescriptorLength = TSGetBitsFromU16(&pu8LoopPosition[3], 0, 0x0fff);
            // Go through the descriptors part.
            pu8Descriptor = pu8LoopPosition + 5;
            u16TotalParseLength = 0;

            switch(pu8LoopPosition[0]) //stream type
            {
                case ST_DSMCC_DATA_TYPE_A:
                case ST_DSMCC_DATA_TYPE_B:
                case ST_DSMCC_DATA_TYPE_C:
                case ST_DSMCC_DATA_TYPE_D:
                case ST_DSMCC_DATA_TYPE_E:
                case ST_OP_MPEG2_VID:
                {
                    u16DSMCC_PID = TSGetBitsFromU16(&pu8LoopPosition[1],0,0x1fff);
                    u16TotalParseLength = 0;
                    while(u16TotalParseLength<u16TotalDescriptorLength)
                    {
                        u8Tag= pu8Descriptor[0];   //descripter Tag
                        switch(u8Tag)
                        {
                            case TAG_DBID:
                            {
                                #if ENABLE_OAD
                                #define DATA_BC_ID_SSU              0x000A // DVB-SSU
                                #define DATA_BC_ID_UK_EC        0x0111 // UK Engineering Channel
                                #define DVB_OUI                 0x00015A
                                #define SSU_UPDATETYPE_STANDARD             0x01
                                if(((pu8Descriptor[1] - 2) >0) && TSGetU16(&pu8Descriptor[2]) == DATA_BC_ID_SSU)
                                {
                                    // Send OAD info & Update Status to OAD module.
                                    WORD wONId;
                                    U32 ouiData=0;
                                    U8 updateType=0 ;
                                    ouiData = (pu8Descriptor[5]<<16)|(pu8Descriptor[6]<<8)|(pu8Descriptor[7]) ;
                                    updateType = pu8Descriptor[8]&0x0f ;
                                    wONId = msAPI_CM_GetON_ID(msAPI_CM_GetCurrentServiceType(),msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()));

                                    if((IS_NORDIC_COUNTRY(OSD_COUNTRY_SETTING)== FALSE)
                                        ||((wONId == 0x2242 && OSD_COUNTRY_SETTING==OSD_COUNTRY_NORWAY)
                                        ||(wONId == 0x20D0 && OSD_COUNTRY_SETTING==OSD_COUNTRY_DENMARK)
                                        ||(wONId == 0x22F1 && OSD_COUNTRY_SETTING==OSD_COUNTRY_SWEDEN)
                                        ||(wONId == 0x20F6 && OSD_COUNTRY_SETTING==OSD_COUNTRY_FINLAND)
                                        ||(wONId == 0x2174 && OSD_COUNTRY_SETTING==OSD_COUNTRY_IRELAND))
                                        || (wONId == 0xFFFF)
                                        ||((ouiData==CUSTOMER_OUI) || (ouiData==DVB_OUI && updateType==SSU_UPDATETYPE_STANDARD)))
                                    {
                                        MApp_OAD_SetPmtSignal(u16DSMCC_PID,DATA_BC_ID_SSU, &pu8Descriptor[4],TAG_DBID, u16Service_ID);
                                    }
                                }
                                else if(((pu8Descriptor[1] - 2) >=0)  && TSGetU16(&pu8Descriptor[2]) == DATA_BC_ID_UK_EC)
                                {
                                    // Send OAD info & Update Status to OAD module.
                                    MApp_OAD_SetPmtSignal(u16DSMCC_PID,DATA_BC_ID_UK_EC, &pu8Descriptor[4],TAG_DBID, u16Service_ID);
                                }
                                #endif
                                break;
                            }
                            case TAG_SID:
                            {
                                #if ENABLE_OAD
                                WORD wONId;

                                wONId = msAPI_CM_GetON_ID(msAPI_CM_GetCurrentServiceType(),msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()));
                                if((IS_NORDIC_COUNTRY(OSD_COUNTRY_SETTING)== FALSE)
                                    ||((wONId == 0x2242 && OSD_COUNTRY_SETTING==OSD_COUNTRY_NORWAY)
                                    ||(wONId == 0x20D0 && OSD_COUNTRY_SETTING==OSD_COUNTRY_DENMARK)
                                    ||(wONId == 0x22F1 && OSD_COUNTRY_SETTING==OSD_COUNTRY_SWEDEN)
                                    ||(wONId == 0x20F6 && OSD_COUNTRY_SETTING==OSD_COUNTRY_FINLAND)
                                    ||(wONId == 0x2174 && OSD_COUNTRY_SETTING==OSD_COUNTRY_IRELAND)))
                                {
                                    MApp_OAD_SetPmtSignal(u16DSMCC_PID,DATA_BC_ID_SSU, &pu8Descriptor[2],TAG_SID, u16Service_ID);
                                }
                                #endif
                                break;
                            }
                            default: break;
                        }
                        /* move to next descriptor */
                        u16DescriptorLength = pu8Descriptor[1] + 2;
                        u16TotalParseLength += u16DescriptorLength;
                        pu8Descriptor += u16DescriptorLength;
                    }
                    break;
                }
                default:
                {
                    break;
                }
            }
            pu8LoopPosition = MApp_SI_FindNextLoop(pu8Section, pu8LoopPosition, u16TotalDescriptorLength, EN_PMT);
        }
        if(TRUE == MApp_Dmx_Get_IsAllPmtReady_ATSC())
        {
            MApp_OAD_Set_PMT_Ready(TRUE);
            MApp_Dmx_ResetAllPmtReady_ATSC();
        }
    }
}

static void MApp_Dmx_Get_Pat_SrvIDInfo(U8 *pu8Section)
{
    U16 u16ProgramNumber;
    U8 u8Loop;
    U8 u8PatItemNum;
    /*[2]move to first item position =======================================*/
    DMX_DBG(DMX_PAT, printf("==============================================>>>>\r\n"));
    u8PatItemNum = (((U16)(pu8Section[1] & 0x0f) << 8 | ((U16)pu8Section[2])) - 9) / 4;

    pu8Section += 8;
    u8CurPatItemNum = 0;
    for(u8Loop = 0; u8Loop < u8PatItemNum; u8Loop++)
    {
        u16ProgramNumber = (pu8Section[0] << 8) | pu8Section[1];

        if (u16ProgramNumber == 0)
        {
            pu8Section += 4;    //move to next item
            continue;
        }
        u16ServiceIdArray[u8Loop]     = u16ProgramNumber;
        u16PmtPidArray[u8Loop]         = ((pu8Section[2] & 0x1f) << 8) | pu8Section[3];
        u8CurPatItemNum++;
        pu8Section += 4;    //move to next item
    }
    DMX_DBG(DMX_PAT, printf("==============================================>>>>\r\n"));
}

static void MApp_Dmx_PMT_Other_Monitor_Parse(U8 *pu8Section)
{
    MApp_Dmx_Other_PMT_Parse(pu8Section);
}

void MApp_Dmx_PMT_Other_Monitor_Cb(U8 u8FID,  DMX_EVENT enEvent)
{
    U32 u32ActualSize,u32RmnSize;
    MSAPI_DMX_FILTER_STATUS enStatus;
    enStatus=(MSAPI_DMX_FILTER_STATUS)enEvent;
    /*[1]check enStatus ====================================================*/
    switch(enStatus)
    {
        case MSAPI_DMX_FILTER_STATUS_SECAVAILABLE:
            {
                //DMX_DBG(DMX_PMT, printf("********MSAPI_DMX_FILTER_STATUS_SECAVAILABLE!! \r\n"));
                /* get section data */
                if(MApi_DMX_CopyData(u8FID, au8Section, MSAPI_DMX_SECTION_1K,&u32ActualSize,&u32RmnSize,NULL) == DMX_FILTER_STATUS_ERROR)
                {
                    DMX_DBG(DMX_PMT, printf("[FID=%bu] PMT get section fail!! \r\n", u8FID));
                    break;
                }

                if(msAPI_DMX_CheckCRC32(au8Section) == FALSE)
                {
                    DMX_DBG(DMX_PMT, printf("[FID=%bu] PMT get section check CRC error!!  case 1\n", u8FID));
                    enStatus = MSAPI_DMX_FILTER_STATUS_CRCINCORRECT;
                    au8CrcErrorCounter[u8FID]++;
                    break;
                }
                MApp_Dmx_PMT_Other_Monitor_Parse(au8Section);
                break;
            }

        case MSAPI_DMX_FILTER_STATUS_CRCINCORRECT:
            {
            	DMX_DBG(DMX_PMT, printf("[FID=%bu] PMT get section check CRC error!! \r\n", u8FID));
                au8CrcErrorCounter[u8FID]++;
                break;
            }

        case MSAPI_DMX_FILTER_STATUS_TIMEOUT:
            {
            DMX_DBG(DMX_PMT, printf("[FID=%bu] PMT get section timeout!! \r\n", u8FID));
                break;
            }

         case MSAPI_DMX_FILTER_STATUS_OVERFLOW:
            {
            DMX_DBG(DMX_PMT, printf("[FID=%bu] PMT get section overflow!! \r\n", u8FID));
                break;
            }

       default:
            {
            DMX_DBG(DMX_PMT, printf("[FID=%bu] PMT get section unknow error!! \r\n", u8FID));
                break;
            }
    }

    /*[02]finalize ==========================================================*/
    if(enStatus == MSAPI_DMX_FILTER_STATUS_SECAVAILABLE)
    {
        msAPI_DMX_CloseFilter(u8FID);
        u8PmtOtherFid = MSAPI_DMX_INVALID_FLT_ID;
    }
    else
    {
        msAPI_DMX_CloseFilter(u8FID);
        u8PmtOtherFid = MSAPI_DMX_INVALID_FLT_ID;
    }
}
void MApp_Dmx_PMT_Other_Monitor_ATSC(void)
{
    MS_DMX_SECTIONMONITOR_PARA   stSectionMonitor;
    if (fEnablePmtOtherMonitor || (msAPI_Timer_DiffTimeFromNow(u32MonitorPmtOtherTimer) > PMT_OTHER_MONITOR_PERIOD))
    {
        if(u8PmtOtherFid == MSAPI_DMX_INVALID_FLT_ID)
        {
            if((u8CurPatItemNum > 1))
            {
                if(u8ServicePMTIndex >= u8CurPatItemNum)
                {
                    u8ServicePMTIndex =0;
                }
                if (u16PmtPidArray[u8ServicePMTIndex] == 0x00)
                {
                    if(++u8ServicePMTIndex >= u8CurPatItemNum)
                    {
                        u8ServicePMTIndex =0;
                        bAllPmtReady = TRUE;
                    }
                }
                pstVirtualCh = MApp_ChanProc_GetCurChannelPointer();
                if((u16ServiceIdArray[u8ServicePMTIndex] != pstVirtualCh->u16ProgramNumber)
                    && (u16ServiceIdArray[u8ServicePMTIndex] != 0))
                {
                    memset(stSectionMonitor.au8MaskByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);
                    memset(stSectionMonitor.au8NotMatchByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);

                    stSectionMonitor.u16PID = u16PmtPidArray[u8ServicePMTIndex];
                    stSectionMonitor.au8MaskByte[0] = 0xFF;
                    stSectionMonitor.au8MaskByte[3] = 0xFF;
                    stSectionMonitor.au8MaskByte[4] = 0xFF;
                    stSectionMonitor.au8MaskByte[5] = 0x01;
                    stSectionMonitor.au8MatchByte[0] = TID_PMS; //table id
                    stSectionMonitor.au8MatchByte[3] = HIGHBYTE(u16ServiceIdArray[u8ServicePMTIndex]); //subtable id
                    stSectionMonitor.au8MatchByte[4] = LOWBYTE(u16ServiceIdArray[u8ServicePMTIndex]);
                    stSectionMonitor.au8MatchByte[5] = 0x01;
                    stSectionMonitor.u32SectionFltType = MSAPI_DMX_FILTER_TYPE_SECTION_1K;
                    stSectionMonitor.pfNotify = MApp_Dmx_PMT_Other_Monitor_Cb;
                    stSectionMonitor.u16TimeoutMilliSec = PMT_OTHER_MONITOR_TIMEOUT;
                    stSectionMonitor.pu8FID = &u8PmtOtherFid;
                    stSectionMonitor.SectMode = DMX_SECT_MODE_ONESHOT|DMX_SECT_MODE_CRCCHK;
                    if(msAPI_DMX_SectionMonitor(&stSectionMonitor,FALSE) == DMX_FILTER_STATUS_OK)
                    {
                        fEnablePmtOtherMonitor = FALSE;
                        u32MonitorPmtOtherTimer = msAPI_Timer_GetTime0();
                    }
                    u8ServicePMTIndex++;
                    if(u8ServicePMTIndex >= u8CurPatItemNum)
                    {
                        bAllPmtReady = TRUE;
                    }
                }
                else
                {
                    u8ServicePMTIndex++;
                }
            }
        }
        else
        {
            fEnablePmtOtherMonitor = FALSE;
            u32MonitorPmtOtherTimer = msAPI_Timer_GetTime0();
        }
    }

}

BOOLEAN MApp_Dmx_Get_IsAllPmtReady_ATSC(void)
{
    return bAllPmtReady;
}
void MApp_Dmx_ResetAllPmtReady_ATSC(void)
{
    bAllPmtReady = FALSE;
}
#endif

static BOOLEAN MApp_Dmx_Parse_PMTAudio(U8 *pu8Section, U8 u8AudioTrackIndex)
{
    U8 *pu8Descriptor;
    U16 u16TotalDescriptorLength = ((pu8Section[3] & 0x0f) << 8) | pu8Section[4];
    BOOLEAN bRet = FALSE;
    switch(pu8Section[0])
    {
    /*audio */
#if(ENABLE_DTV_MPEG_AUDIO)
        case ST_MPEG1_AUD:
            //mpeg 1 audio
        case ST_MPEG2_AUD:
            //mpeg 2 audio
#endif
        case ST_AC3_AUD:
#if (ENABLE_AC3P_AUDIO)
        case ST_AC3P_AUD:
#endif
        case ST_AAC_AUD:
        case ST_HEAAC_AUD:
            //AC-3 audio
            {
                BOOLEAN bLangInAC3Des = 0;
                astSoundTrackPMT[u8AudioTrackIndex].u8AudPidInPMT = TRUE;
                /* audio stream type */
                if((pu8Section[0] == ST_AC3_AUD) || (pu8Section[0] == ST_AC3P_AUD))
                {
                    astSoundTrackPMT[u8AudioTrackIndex].u16AudStreamType = AUD_STREAM_TYPE_AC3;
                }
                else if((pu8Section[0] == ST_AAC_AUD)||(pu8Section[0] == ST_HEAAC_AUD))
                {
                    astSoundTrackPMT[u8AudioTrackIndex].u16AudStreamType = AUD_STREAM_TYPE_AAC;
                }
#if(ENABLE_DTV_MPEG_AUDIO)
                else
                {
                    astSoundTrackPMT[u8AudioTrackIndex].u16AudStreamType = AUD_STREAM_TYPE_MPEG;
                }
#endif
                /* audio pid */
                astSoundTrackPMT[u8AudioTrackIndex].u16AudioPid = ((pu8Section[1] & 0x1f) << 8) | pu8Section[2];
                if((pu8Section[0] == ST_AC3_AUD) || (pu8Section[0] == ST_AC3P_AUD))
                {
                    /* get AC3 descriptor */
                    DES_DBG(AC3_DESCRIPTOR, printf("\n================================================\n"));
                    DES_DBG(AC3_DESCRIPTOR, printf("audio pid = 0x%x\n", astSoundTrackPMT[u8AudioTrackIndex].u16AudioPid));
                    pu8Descriptor = MApp_Dmx_FindDescriptorTag(pu8Section + 5, TAG_AC3AD, u16TotalDescriptorLength);
                    if(pu8Descriptor != NULL)
                    {
                        MAPI_PSIP_AC3_DES_A stAC3Descriptor;
                        memset(&stAC3Descriptor, 0, sizeof(MAPI_PSIP_AC3_DES_A));
                        stAC3Descriptor.u8BsMod =EN_PSIP_AC3_BSMOD_NUM;
                        MApp_Dmx_Parse_AC3Descriptor(pu8Descriptor, &stAC3Descriptor);
                        astSoundTrackPMT[u8AudioTrackIndex].u8AudAc3Bsmod = stAC3Descriptor.u8BsMod;
                        astSoundTrackPMT[u8AudioTrackIndex].u8Priority = stAC3Descriptor.u8Priority;
                        if(stAC3Descriptor.u8LangFlag1)
                        {
                            astSoundTrackPMT[u8AudioTrackIndex].u8AudLangIdx = MApp_Dmx_GetISO639LangCode(&(stAC3Descriptor.u8Lang1[0]));
                            astSoundTrackPMT[u8AudioTrackIndex].u16IsAudLangGetinPMT = 1;
                            bLangInAC3Des = 1;
                            astSoundTrackPMT[u8AudioTrackIndex].u16AC3inPMT = 1;
                            //printf("u8AudLangIdx  = %d\n", pstVirtualChSndTrk_func->astSoundTrack[pstVirtualChSndTrk_func->u8AudLangNum].u16AudLangIdx);
                        }
                    }
                }
                /* get language descriptor */

                {
                    pu8Descriptor = MApp_Dmx_FindDescriptorTag(pu8Section + 5, TAG_LnD, u16TotalDescriptorLength);
                    if(pu8Descriptor != NULL)
                    {
                        astSoundTrackPMT[u8AudioTrackIndex].u8AudLangIdx = MApp_Dmx_GetISO639LangCode(&pu8Descriptor[2]);
                    }
                    else if(bLangInAC3Des ==0)
                    {
                        astSoundTrackPMT[u8AudioTrackIndex].u8AudLangIdx = AUD_LANG_UND;
                    }
                }
            }
        bRet = TRUE;
        break;
    }
    return bRet;
}

/*****************************************************************************/
/*         Monitor, Callback and Parsing function for PSI Table              */
/*****************************************************************************/
/***                                                                       ***/
/***  === PAT ===   1. MApp_Dmx_PAT_CheckVersionChange                     ***/
/***                2. MApp_Dmx_PAT_Parse                                  ***/
/***                3. MApp_Dmx_PAT_Cb                                     ***/
/***                                                                       ***/
/***  === PMT ===   1. MApp_Dmx_PAT_Monitor                                ***/
/***                2. MApp_Dmx_PMT_Cb                                     ***/
/***                                                                       ***/
/*****************************************************************************/
static void MApp_Dmx_PAT_CheckVersionChange(U8 *pu8Section)
{
    U8 u8CurPatItem;
    U16 u16SecLength;

    pstVirtualCh = MApp_ChanProc_GetCurChannelPointer();

    // Get RF ch
    MS_RF_CHANNEL_new stCurRfCh;
    memset(&stCurRfCh, 0x00, sizeof(MS_RF_CHANNEL_new));
    MApp_ChanProc_GetRfChannelPointer(pstVirtualCh, &stCurRfCh);

    u16ActualTSid = ((U16)pu8Section[3] << 8) | ((U16)pu8Section[4]);
    u8Version = (pu8Section[5] & 0x3f) >> 1;
    u16SecLength = ((U16)(pu8Section[1] & 0x0f) << 8) | ((U16)pu8Section[2]);
    u8CurPatItem = (u16SecLength - 9) / 4;

#if ENABLE_PAT_MUTISECTION
    U8 u8CurSecNum, u8LastSecNum;

    u8CurSecNum = pu8Section[6];
    u8LastSecNum = pu8Section[7];

    //4   In muti-section, parser will limit one channel in one section due to DB size. the total channel number should same as total section number.
    if(pu8Section[7]) //muti-section
    {
        u8CurPatItem = u8LastSecNum+1;
    }


    DMX_VERSION_DBG(DMX_PATCHECK_VERSION, printf("******** PAT_CheckVersionChange: service type = %d, Tsid [%x->%x], Ver [%bx->%bx], PatNum [%bx->%bx], TotalPatItem=%u\r\n",
                                            pstVirtualCh->u8ServiceType,
                                            stCurRfCh.u16TsId, u16ActualTSid,
                                            stCurRfCh.u8PatVersion, u8Version,
                                            u8NumOfPatItem, u8CurPatItem, u8LastSecNum+1));

    if(u8CurSecNum > PAT_MAX_SECTION_NUMBER)
    {
        DMX_VERSION_DBG(DMX_PATCHECK_VERSION,printf("[PAT VerChg] skip section[%u], [%u]\n", pstVirtualCh->u16PatSectionNum, u8CurSecNum));
        return;
    }
#endif

    U8 u8NumOfCurVirCh = stChSetting.astPhysicalCh[stChSetting.astMainList[MApp_ChanProc_GetCurProgIndex()].u8PhysicalChIdx].u8NumOfVirCh;
    //DMX_VERSION_DBG(DMX_PATCHECK_VERSION, printf("******** PAT_CheckVersionChange: service type = %d, Tsid [%x->%x], Ver [%bx->%bx], PatNum [%bx->%bx]\r\n",
    //                                                                                                                                    pstVirtualCh->u8ServiceType,
    //                                                                                                                                    pstVirtualCh->u16TsId, u16ActualTSid,
    //                                                                                                                                   pstVirtualCh->u8PatVersion, u8Version,
    //                                                                                                                                     u8NumOfPatItem, u8CurPatItem));

#if 0//(ENABLE_MAX_RRT_DIMENSION_NUMBER == 0)
    if((u8LastPatItemNo == 0)
  #if (ENABLE_PAT_TIMEOUT_NOSIGNAL)
	&&(g_fPatTimeoutNeedRecover == FALSE)
  #endif
		)
    {
        u8LastPatItemNo = u8CurPatItem;
    }
#endif

#if ENABLE_PAT_MUTISECTION
    if(u8CurSecNum != pstVirtualCh->u16PatSectionNum)
    {
        DMX_VERSION_DBG(DMX_PATCHECK_VERSION,printf("[PAT VerChg] skip section[%u], [%u]\n", pstVirtualCh->u16PatSectionNum, u8CurSecNum));
        return;
    }
#endif

    if((stCurRfCh.u16TsId != u16ActualTSid))
    {
        DMX_VERSION_DBG(DMX_PATCHECK_VERSION,printf("[PAT VerChg] Tsid [%x->%x]\n", stCurRfCh.u16TsId, u16ActualTSid));
        fTableVersionChanged = TRUE;
    }
    else
    {
        if(!pstVirtualCh->bChannelFromVCT)
        {
            U16 u16ProgramNumber = pstVirtualCh->u16ProgramNumber;
            U16 u16PmtPid = pstVirtualCh->u16PmtPid;

            if(u8CurPatItem > MAX_VC_PER_PHYSICAL)
            {
                u8CurPatItem = (U8)MAX_VC_PER_PHYSICAL;
            }


            if( stCurRfCh.u8NumOfPatItem != u8CurPatItem )
            {
                DMX_VERSION_DBG(DMX_PATCHECK_VERSION, printf("[PAT VerChg] u8CurPatItem=%u, u8NumOfPatItem=%u\n", u8CurPatItem, stCurRfCh.u8NumOfPatItem ) );
                fTableVersionChanged = TRUE;
            }

            if((pstVirtualCh->u16PmtPid == 0) &&(pstVirtualCh->u16VideoPid != 0))
            {
                for(iu8Loop_i = 0; iu8Loop_i < u8CurPatItem; iu8Loop_i++)
                {
                    if(pstVirtualCh->u16ProgramNumber == pastPATItem[iu8Loop_i].u16ProgramNumber)
                        break;
                }

                // Coverity-198274:
                // iu8Loop_i will be 0 ~ (MAX_VC_PER_PHYSICAL)
                // If iu8Loop_i==MAX_VC_PER_PHYSICAL, it over array size!!
                if( iu8Loop_i < MAX_VC_PER_PHYSICAL )
                {
                    u16ProgramNumber = pastPATItem[iu8Loop_i].u16ProgramNumber;
                    u16PmtPid = pastPATItem[iu8Loop_i].u16PID;
                }

            }

            pu8Section += 8;

            {
                DMX_VERSION_DBG(DMX_PATCHECK_VERSION, printf("[PAT] Current Program NO = 0x%bx, PmtPid = 0x%bx\n", u16ProgramNumber, u16PmtPid));
                BOOLEAN bHasProgramNumberInDB = FALSE;
                //search program number <--->pmt id in db
                for(iu8Loop_i = 0; iu8Loop_i < u8CurPatItem; iu8Loop_i++)
                {
                    DMX_VERSION_DBG(DMX_PATCHECK_VERSION, printf("[Loop%d]New Programber = 0x%bx\n", iu8Loop_i, ((pu8Section[0] << 8) | pu8Section[1])));
                    if(u16ProgramNumber == ((pu8Section[0] << 8) | pu8Section[1]))
                    {
                        if(u16PmtPid != (((pu8Section[2] & 0x1f) << 8) | pu8Section[3]))
                        {
                            fTableVersionChanged = TRUE;
                        }
                        bHasProgramNumberInDB = TRUE;
                        break;
                    }
                    pu8Section += 4;
                }

                if((bHasProgramNumberInDB== FALSE) && (u8CurPatItem != 0))
                {
                    printf(">>>>>PAT version number same but program number and pmtpid are different>>>>\n");
                    fTableVersionChanged = TRUE;
                }
            }
        }
    }

    if(!fTableVersionChanged)
    {
        if((u8NumOfCurVirCh ==1)&& ((u8NumOfPatItem != u8CurPatItem)))
        {
            if(pstVirtualCh->bScrambleCH == 1)
            {
                fTableVersionChanged = TRUE;
            }
        }
    }
    else
    {
        if( u8Version != stCurRfCh.u8PatVersion )
            stCurRfCh.u8PatVersion = u8Version;
    }


    if(fTableVersionChanged)
    {
        printf(">>>>>>PAT VersionChange_%d>>>>>>>\n",__LINE__);

#if (ENABLE_ATSC_EPG_DB_2016)
        msAPI_AtscEpgDb_Delete_Event_By_RfNum(pstVirtualCh->u8RfNum);
#endif
#if (ENABLE_PAT_TIMEOUT_NOSIGNAL)
        g_fPatTimeoutNeedRecover = FALSE;
#endif
        bIsEASinProgress = FALSE;
        u8KeyCode = KEY_EXIT;
    }

}

/*****************************************************************************/
static void MApp_Dmx_PAT_Parse(MS_PAT_ITEM_ATSC*pastPATItem_func, U8 *pu8Section)
{
    U16 u16ProgramNumber;

    /*[1]check error condition =============================================*/
    /*
    if( pastPATItem_func == NULL || pu8Section == NULL )
    {
       return;
    }
    */

#if ENABLE_PAT_MUTISECTION
    U8 u8Loop, u8ChIndex, u8CurSectionNum, u8MaxChNumOfMutiSec;

    //verify current section number range
    if(pu8Section[6] > PAT_MAX_SECTION_NUMBER )
    {
        DMX_DBG(DMX_PAT, printf("<Warning> PAT Section number over %u\n", PAT_MAX_SECTION_NUMBER));
        return;
    }
#endif

    /*[2]move to first item position =======================================*/
    DMX_DBG(DMX_PAT, printf("==============================================>>>>\r\n"));
    u16ActualTSid = (pu8Section[3] << 8) | pu8Section[4];
    u8Version = (pu8Section[5] & 0x3f) >> 1;

#if ENABLE_PAT_MUTISECTION
    u8CurSectionNum = pu8Section[6];
    u8LastSectionNumOfPat = pu8Section[7];
    u8CurSectionItemOfPat = (((U16)(pu8Section[1] & 0x0f) << 8 | ((U16)pu8Section[2])) - 9) / 4;
#endif

    DMX_DBG(DMX_PAT, printf("parse PAT, u16ActualTSid = %u\n", u16ActualTSid));
    pu8Section += 8;

#if ENABLE_PAT_MUTISECTION
    //Limit max channel number in muti-section
    if(u8LastSectionNumOfPat)
    {
        //4  In muti-section, parser will limit one channel in one section due to DB size.
        u8MaxChNumOfMutiSec = PAT_MAX_CH_IN_MUTISECTION;
        DMX_DBG(DMX_PAT, printf("Warning! u8CurSectionItemOfPat(%u) > MAX_VC_PER_PHYSICAL !!\r\n", u8CurSectionItemOfPat));
    }
    else
    {
        u8MaxChNumOfMutiSec = u8CurSectionItemOfPat;
    }
#endif

    /*[3]get items =========================================================*/

#if ENABLE_PAT_MUTISECTION
    if(u8CurSectionItemOfPat == 0)
    {
        pastRfCh.u8PatVersion       = u8Version;
        pastRfCh.u16TsId            = u16ActualTSid;
    }
#endif


#if ENABLE_PAT_MUTISECTION
    DMX_DBG(DMX_PAT, printf("parse PAT, u16ActualTSid = %u, u8CurSectionItemOfPat=%d,  u8CurSecNum=%u\n", u16ActualTSid, u8CurSectionItemOfPat,  u8CurSectionNum));

    for(u8Loop = 0; u8Loop < u8MaxChNumOfMutiSec; u8Loop++)
    {
        u16ProgramNumber = (pu8Section[0] << 8) | pu8Section[1];
        u8ChIndex =  u8Loop + u8NumOfPatItem;

        //verify channel index range
        if(u8ChIndex > MAX_VC_PER_PHYSICAL)
        {
            DMX_DBG(DMX_PAT, printf("Warning! u8ChIndex > MAX_VC_PER_PHYSICAL !!\r\n"));
            break;
        }
        pastPATItem_func[u8ChIndex].u16ProgramNumber     = u16ProgramNumber;
        pastPATItem_func[u8ChIndex].u16PID               = ((pu8Section[2] & 0x1f) << 8) | pu8Section[3];
        pastPATItem_func[u8ChIndex].u8SectionNum    = u8CurSectionNum;
        pastPATItem_func[u8ChIndex].u16BuildChNumber     = MApp_Dmx_MakeBuildChNo(pastPATItem_func, u8ChIndex, pastPATItem_func[u8ChIndex].u16ProgramNumber);

        pastRfCh.u8PatVersion       = u8Version;
        pastRfCh.u16TsId            = u16ActualTSid;

        pastVirtualCh[u8ChIndex].u16PatSectionNum    = u8CurSectionNum;
        pastVirtualCh[u8ChIndex].u16ProgramNumber   = u16ProgramNumber;

        pu8Section += 4;    //move to next item

        DMX_DBG(DMX_PAT, printf ("PAT Item %d >> TSid = 0x%04X, PN = 0x%04X, PID = 0x%04X \n", u8ChIndex, u16ActualTSid, u16ProgramNumber, pastPATItem_func[u8ChIndex].u16PID));
    }
#else
    DMX_DBG(DMX_PAT, printf("parse PAT, u8NumOfPatItem # = %d\n", u8NumOfPatItem));

    for(iu8Loop_i = 0; iu8Loop_i < u8NumOfPatItem; iu8Loop_i++)
    {
        u16ProgramNumber = (pu8Section[0] << 8) | pu8Section[1];

        pastPATItem_func[iu8Loop_i].u16ProgramNumber     = u16ProgramNumber;
        pastPATItem_func[iu8Loop_i].u16PID               = ((pu8Section[2] & 0x1f) << 8) | pu8Section[3];
        pastPATItem_func[iu8Loop_i].u16BuildChNumber     = MApp_Dmx_MakeBuildChNo(pastPATItem_func, iu8Loop_i, pastPATItem_func[iu8Loop_i].u16ProgramNumber);

        pastRfCh.u8PatVersion       = u8Version;
        pastRfCh.u16TsId            = u16ActualTSid;

        pastVirtualCh[iu8Loop_i].u16ProgramNumber   = u16ProgramNumber;
        pu8Section += 4;    //move to next item

        DMX_DBG(DMX_PAT, printf ("PAT Item %d >> TSid = 0x%04X, PN = 0x%04X, PID = 0x%04X \n", iu8Loop_i, u16ActualTSid, u16ProgramNumber, pastPATItem_func[iu8Loop_i].u16PID));
    }
#endif

    DMX_DBG(DMX_PAT, printf("==============================================>>>>\r\n"));
}

/*****************************************************************************/
void MApp_Dmx_PAT_Cb(U8 u8FID, DMX_EVENT enEvent)
{
    U32 u32ActualSize,u32RmnSize;
    MSAPI_DMX_FILTER_STATUS enStatus;
    enStatus=(MSAPI_DMX_FILTER_STATUS)enEvent;

    /*[1]check enStatus ====================================================*/
    switch(enStatus)
    {
        case MSAPI_DMX_FILTER_STATUS_SECAVAILABLE:
            {
                /* get section data */
                if(MApi_DMX_CopyData(u8FID, au8Section, MSAPI_DMX_SECTION_1K,&u32ActualSize,&u32RmnSize,NULL) == DMX_FILTER_STATUS_ERROR)
                {
                    DMX_DBG(DMX_PAT, printf("[FID=%d] PAT get section fail!! \r\n", u8FID));
                    break;
                }

                if(msAPI_DMX_CheckCRC32(au8Section) == FALSE)
                {
                    DMX_DBG(DMX_PAT, printf("[FID=%d] PAT get section check CRC error!!  case 1\n", u8FID));
                    enStatus = MSAPI_DMX_FILTER_STATUS_CRCINCORRECT;
                    au8CrcErrorCounter[u8FID]++;
                    break;
                }

                /* parsing table */
#if ENABLE_PAT_MUTISECTION
                if (!fEnableTableMonitor)
                {
                    MApp_Dmx_PAT_Parse(pastPATItem, au8Section);

                    u8NumOfPatItem += u8CurSectionItemOfPat;
                    if(u8NumOfPatItem > MAX_VC_PER_PHYSICAL)
                    {
                        u8NumOfPatItem = MAX_VC_PER_PHYSICAL;
                        DMX_DBG(DMX_SCAN, printf("Warning! u8NumOfPatItem > MAX_VC_PER_PHYSICAL !!\r\n"));
                    }
                    DMX_DBG(DMX_SCAN, printf("\033[31m  [%s][%d] current SN=%d, last SN=%d, u8NumOfPatItem=%d \033[0m\n",__FUNCTION__,__LINE__, au8Section[6], au8Section[7], u8NumOfPatItem));

                  #if 0//(ENABLE_MAX_RRT_DIMENSION_NUMBER == 0)
                    u8LastPatItemNo = u8NumOfPatItem;
                  #endif

                    u8TotalTableItem = u8NumOfPatItem;
                }
                else
#endif
                {
                    MApp_Dmx_PAT_CheckVersionChange(au8Section);
#if ENABLE_OAD
                    MApp_Dmx_Get_Pat_SrvIDInfo(au8Section);
#endif
                }
                break;
            }

    #if (!ENABLE_NEW_DMX_INTERFACE)
        case MSAPI_DMX_FILTER_STATUS_CRCINCORRECT:
            {
                DMX_DBG(DMX_PAT, printf("[FID=%d] PAT get section check CRC error!! \r\n", u8FID));
                au8CrcErrorCounter[u8FID]++;
                break;
            }

        case MSAPI_DMX_FILTER_STATUS_TIMEOUT:
            {
            DMX_DBG(DMX_PAT, printf("[FID=%d] PAT get section timeout!! \r\n", u8FID));
                break;
            }

         case MSAPI_DMX_FILTER_STATUS_OVERFLOW:
            {
            DMX_DBG(DMX_PAT, printf("[FID=%d] PAT get section overflow!! \r\n", u8FID));
                break;
            }
    #endif

       default:
            {
                printf("[FID=%d] PAT get section unknow error!! \r\n", u8FID);
                break;
            }
    }

#if ENABLE_PAT_MUTISECTION
    if (!fEnableTableMonitor)
    {
        /*[02]finalize ==========================================================*/
        if(enStatus==MSAPI_DMX_FILTER_STATUS_CRCINCORRECT && au8CrcErrorCounter[u8FID]<=MAX_NUM_OF_CRC_ERROR)
        {
            DMX_DBG(DMX_VCT, printf("Restart PAT filter>> [FID=%d]\r\n", u8FID));
            msAPI_DMX_RestartFilter(u8FID);
        }
        else
        {
            msAPI_DMX_CloseFilter(u8FID);

            u8OpenedFltCounter--;
            au8CrcErrorCounter[u8FID] = 0;
        }
    }
    else
#endif
    {
        /*[02]finalize ==========================================================*/
        if(enStatus == MSAPI_DMX_FILTER_STATUS_SECAVAILABLE)
        {
            msAPI_DMX_CloseFilter(u8FID);
            u8PatFid = MSAPI_DMX_INVALID_FLT_ID;
            fEnablePatMonitor = TRUE;
        }
        else
        {
            msAPI_DMX_RestartFilter(u8FID);
        }
    }
}
/*****************************************************************************/
#if 0
void MApp_Dmx_PAT_Cb(U8 u8FID, MAPI_DMX_EVENT enEvent)
{
    MSAPI_DMX_FILTER_STATUS enStatus;
    enStatus=(MSAPI_DMX_FILTER_STATUS)enEvent;

    /*[1]check enStatus ====================================================*/
    switch(enStatus)
    {
        case MSAPI_DMX_FILTER_STATUS_SECAVAILABLE:
            {
                /* get section data */
                if(MApi_DMX_CopyData(u8FID, au8Section, MSAPI_DMX_SECTION_1K) == MAPI_DMX_FILTER_STATUS_ERROR)
                {
                    DMX_DBINFO(printf("[FID=%d] PAT get section fail!! \r\n", u8FID));
                    break;
                }

                /* get PAT items */
                u16SecLength = (au8Section[1] & 0x0f) << 8;
                u16SecLength |= au8Section[2];
                u8NumOfPatItem = (u16SecLength - 9) / 4;
                if(u8NumOfPatItem > MAX_VC_PER_PHYSICAL)
                {
                    u8NumOfPatItem = MAX_VC_PER_PHYSICAL;
                    DMX_DBINFO(printf("Warning! u8NumOfPatItem > MAX_VC_PER_PHYSICAL !!\r\n"));
                }

                //MApp_Dmx_DumpSectionData( u16SecLength );

                /* parsing table */
                MApp_Dmx_PAT_Parse(pastPATItem, au8Section);
                break;
            }

        case MSAPI_DMX_FILTER_STATUS_CRCINCORRECT:
            {
                DMX_DBINFO(printf("[FID=%d] PAT get section check CRC error!! \r\n", u8FID));
                au8CrcErrorCounter[u8FID]++;
                break;
            }

        case MSAPI_DMX_FILTER_STATUS_TIMEOUT:
            {
                DMX_DBINFO(printf("[FID=%d] PAT get section timeout!! \r\n", u8FID));
                break;
            }

        case MSAPI_DMX_FILTER_STATUS_OVERFLOW:
            {
                DMX_DBINFO(printf("[FID=%d] PAT get section overflow!! \r\n", u8FID));
                break;
            }

        default:
            {
                DMX_DBINFO(printf("[FID=%d] PAT get section unknow error!! \r\n", u8FID));
                break;
            }
    }

    /*[02]finalize ==========================================================*/
    if(enStatus==MSAPI_DMX_FILTER_STATUS_CRCINCORRECT && au8CrcErrorCounter[u8FID]<=MAX_NUM_OF_CRC_ERROR)
    {
        DMX_DBINFO(printf("Restart PAT filter>> [FID=%d]\r\n", u8FID));
        msAPI_DMX_RestartFilter(u8FID);
    }
    else
    {
        msAPI_DMX_CloseFilter(u8FID);

        u8OpenedFltCounter--;
        au8CrcErrorCounter[u8FID] = 0;
    }
}
#endif
/*****************************************************************************/
static BOOLEAN MApp_Dmx_PMT_CheckVersionChange(U8 *pu8Section)
{
    pstVirtualCh = MApp_ChanProc_GetCurChannelPointer();

    // Get cur RF ch
    MS_RF_CHANNEL_new vRfCh;
    memset(&vRfCh, 0x00, sizeof(MS_RF_CHANNEL_new));
    MApp_ChanProc_GetRfChannelPointer(pstVirtualCh, &vRfCh);

    u8Version = (pu8Section[5] & 0x3f) >> 1;

#if 0 //remove version number change condition
    if (u8Version != pstVirtualCh->u8PmtVersion)
    {
        DMX_DBG(DMX_PMT, printf("[PMT VerChg] Ver= %bx -> %bx\r\n", pstVirtualCh->u8PmtVersion, u8Version));
        fTableVersionChanged = TRUE;
    }
#else

    if (u8Version != vRfCh.u8PmtVersion)
    {
        DMX_VERSION_DBG(DMX_PMTCHECK_VERSION, printf("[PMT VerChg] Ver= %bx -> %bx\r\n", vRfCh.u8PmtVersion, u8Version));
    }


    U16 u16TotalDescriptorLength = ((pu8Section[10] & 0x0f) << 8) | pu8Section[11];
    U8 *pu8LoopPosition;
    U8 u8AudLangNum_New = 0;
    U8 u8ValidAudLangNum = 0;
    U8 u8AudioNuminVCT = 0;
    BOOLEAN fVaildAudioTrack =FALSE;
    BOOLEAN fAudioTrackFindInDB =FALSE;
    U8 u8AudioTrackUpdateIndex[MAX_AUD_LANG_NUM_ATSC] = {0};
    U8 u8AudioupdateLoopCount = 0;
    U16 u16AudioLangMask=0;
    MS_SOUND_TRACK_ATSC astSoundTrackVCT[MAX_AUD_LANG_NUM_ATSC];
    memset(astSoundTrackPMT, 0, sizeof(MS_SOUND_TRACK_ATSC)*MAX_AUD_LANG_NUM_ATSC);
    iu8Loop_j =0;

    memset(astSoundTrackPMT, 0, sizeof(MS_SOUND_TRACK_ATSC)*MAX_AUD_LANG_NUM_ATSC);

    for(iu8Loop_i = 0; iu8Loop_i < pstVirtualCh->u8AudLangNum; iu8Loop_i++)
    {
        if(!pstVirtualCh->astSoundTrack[iu8Loop_i].u8AudPidInPMT)
        {
            u8AudioNuminVCT++;

            if( iu8Loop_j >= MAX_AUD_LANG_NUM_ATSC )
            {
                PRINT_CURRENT_LINE();
                printf("\nError: iu8Loop_j=%u\n", iu8Loop_j);
                break;
            }
            memcpy(&astSoundTrackVCT[iu8Loop_j], &pstVirtualCh->astSoundTrack[iu8Loop_i], sizeof(MS_SOUND_TRACK_ATSC));
            iu8Loop_j++;
        }
    }
    pu8LoopPosition = MApp_Dmx_FindFirstLoop(pu8Section, EN_PMT);
    BOOLEAN bHasFindVideoPidInDB = FALSE;
#if (ENABLE_DYNAMIC_UPDATE_AUDIO_LANGUAGE)
    U8 *pu8Descriptor;
#endif

    if(pstVirtualCh->bChannelFromVCT)
    {
        DMX_VERSION_DBG(DMX_PMTCHECK_VERSION, printf("Current Channelinfo in only from VCT\n"));
    goto LeaveCheckVersionChange;
    }

    while(pu8LoopPosition != NULL)
    {
        fVaildAudioTrack = FALSE;
        fAudioTrackFindInDB = FALSE;
        u16TotalDescriptorLength = ((pu8LoopPosition[3] & 0x0f) << 8) | pu8LoopPosition[4];
        if(pstVirtualCh->u16VideoPid)
        {
            if(pstVirtualCh->u16VideoPid ==(((pu8LoopPosition[1] & 0x1f) << 8) | pu8LoopPosition[2]))
            {
                bHasFindVideoPidInDB = TRUE;
                //check videostream type and other fields
                switch(pu8LoopPosition[0])
                {
                    case ST_MPEG1_VID:
                    if(pstVirtualCh->stVirtualChNum.u8VideoStreamType!= VIDEO_STREAM_TYPE_MPEG1)
                    {
                        DMX_VERSION_DBG(DMX_PMTCHECK_VERSION, printf("Video stream type is changed, not mpeg1!\n"));
                        fTableVersionChanged = TRUE;
                        goto LeaveCheckVersionChange;
                    }
                    break;

                    case ST_MPEG2_VID:
                    if(pstVirtualCh->stVirtualChNum.u8VideoStreamType!= VIDEO_STREAM_TYPE_MPEG2)
                    {

                        DMX_VERSION_DBG(DMX_PMTCHECK_VERSION, printf("Video stream type is changed, not mpeg2!\n"));
                        fTableVersionChanged = TRUE;
                        goto LeaveCheckVersionChange;
                    }
                     break;
                    case ST_OP_MPEG2_VID:
                    if(pstVirtualCh->stVirtualChNum.u8VideoStreamType!= VIDEO_STREAM_TYPE_OPTION_MPEG2)
                    {

                        DMX_VERSION_DBG(DMX_PMTCHECK_VERSION, printf("Video stream type is changed, not option mpeg2!\n"));
                        fTableVersionChanged = TRUE;
                        goto LeaveCheckVersionChange;
                    }
                    break;

                    case ST_AVCH264_VID:
                    if(pstVirtualCh->stVirtualChNum.u8VideoStreamType!= VIDEO_STREAM_TYPE_H264)
                    {
                        DMX_VERSION_DBG(DMX_PMTCHECK_VERSION, printf("Video stream type is changed, not H264!\n"));
                        fTableVersionChanged = TRUE;
                        goto LeaveCheckVersionChange;
                    }
                    break;
                    default:
                        DMX_VERSION_DBG(DMX_PMTCHECK_VERSION,printf("Unkown video stream type!\n"));
                    break;
                }
            }
        }

        if(u8ValidAudLangNum < MAX_AUD_LANG_NUM_ATSC)
        {
            if(MApp_Dmx_Parse_PMTAudio(pu8LoopPosition, u8ValidAudLangNum))
            {
                u8ValidAudLangNum++;
                fVaildAudioTrack = TRUE;
                DMX_VERSION_DBG(DMX_PMTCHECK_VERSION,printf("u8ValidAudLangNum = %d, stream type = 0x%x, audpid = 0x%x\n", u8ValidAudLangNum, pu8LoopPosition[0],  astSoundTrackPMT[u8ValidAudLangNum-1].u16AudioPid ));
            }
        }

        if(u8AudLangNum_New < MAX_AUD_LANG_NUM_ATSC)
        {
            if( pstVirtualCh->u8AudLangNum >= MAX_AUD_LANG_NUM_ATSC )
            {
                PRINT_CURRENT_LINE();
                printf("\nError: pstVirtualCh->u8AudLangNum=%u\n", pstVirtualCh->u8AudLangNum);
            }

            for(iu8Loop_i=0; iu8Loop_i<pstVirtualCh->u8AudLangNum; iu8Loop_i++)
            {
                if(pstVirtualCh->astSoundTrack[iu8Loop_i].u8AudPidInPMT)
                {
                    if(pstVirtualCh->astSoundTrack[iu8Loop_i].u16AudioPid == (((pu8LoopPosition[1] & 0x1f) << 8) | pu8LoopPosition[2])
                        && ((u16AudioLangMask & (1 << iu8Loop_i)) == 0))
                    {
                        //check videostream type and other fields
                        fAudioTrackFindInDB = TRUE;
                        switch(pu8LoopPosition[0])
                        {
#if(ENABLE_DTV_MPEG_AUDIO)
                            case ST_MPEG1_AUD:
                            //mpeg 1 audio
                            case ST_MPEG2_AUD:
                            //mpeg 2 audio
                            if(pstVirtualCh->astSoundTrack[iu8Loop_i].u16AudStreamType != AUD_STREAM_TYPE_MPEG)
                            {
                                DMX_VERSION_DBG(DMX_PMTCHECK_VERSION,printf("Change audio stream type to MPEG\n"));
                                pstVirtualCh->astSoundTrack[iu8Loop_i].u16AudStreamType = AUD_STREAM_TYPE_MPEG;
                                fTableAudioStreamTypeChange = TRUE;
                            }
                            break;
#endif

                            case ST_AC3_AUD:
#if (ENABLE_AC3P_AUDIO)
                            case ST_AC3P_AUD:
#endif
                            if(pstVirtualCh->astSoundTrack[iu8Loop_i].u16AudStreamType != AUD_STREAM_TYPE_AC3)
                            {
                                DMX_VERSION_DBG(DMX_PMTCHECK_VERSION,printf("Change audio stream type to AC3\n"));
                                pstVirtualCh->astSoundTrack[iu8Loop_i].u16AudStreamType = AUD_STREAM_TYPE_AC3;
                                fTableAudioStreamTypeChange = TRUE;
                            }

                            break;
                            case ST_AAC_AUD:
                            case ST_HEAAC_AUD:
                            if(pstVirtualCh->astSoundTrack[iu8Loop_i].u16AudStreamType != AUD_STREAM_TYPE_AAC)
                            {
                                DMX_VERSION_DBG(DMX_PMTCHECK_VERSION,printf("Change audio stream type to AAC\n"));
                                pstVirtualCh->astSoundTrack[iu8Loop_i].u16AudStreamType = AUD_STREAM_TYPE_AAC;
                                fTableAudioStreamTypeChange = TRUE;
                            }
                            break;
                            default:
                            {
                                DMX_VERSION_DBG(DMX_PMTCHECK_VERSION,printf("Unknow audio stream type!\n"));
                                //fTableVersionChanged = TRUE;
                                goto LeaveCheckVersionChange;
                            }
                            break;
                        }
#if (ENABLE_DYNAMIC_UPDATE_AUDIO_LANGUAGE)
                        {
                            /* get language descriptor */
                            pu8Descriptor = MApp_Dmx_FindDescriptorTag(pu8LoopPosition + 5, TAG_LnD, u16TotalDescriptorLength);
                            if(pu8Descriptor != NULL)
                            {
                                if(pstVirtualCh->astSoundTrack[iu8Loop_i].u8AudLangIdx != MApp_Dmx_GetISO639LangCode(&pu8Descriptor[2]))
                                {
                                    DMX_VERSION_DBG(DMX_PMTCHECK_VERSION, printf("[TAG_LnD] Lang %d = %c%c%c Idx = %d is changed!\n", u8AudLangNum_New, pu8Descriptor[2], pu8Descriptor[3], pu8Descriptor[4], (U8)pstVirtualCh->astSoundTrack[iu8Loop_i].u8AudLangIdx));
                                    fTableAudioLanguageChange = TRUE;
                                    pstVirtualCh->astSoundTrack[iu8Loop_i].u8AudLangIdx = MApp_Dmx_GetISO639LangCode(&pu8Descriptor[2]);
                                    goto LeaveCheckVersionChange;
                                }
                            }
                            else
                            {
                                if(pstVirtualCh->astSoundTrack[iu8Loop_i].u8AudLangIdx != AUD_LANG_UND)
                                {
                                    DMX_VERSION_DBG(DMX_PMTCHECK_VERSION, printf("[TAG_LnD Not find default to other] Lang %d =other \n", u8AudLangNum_New));
                                    fTableAudioLanguageChange = TRUE;
                                    pstVirtualCh->astSoundTrack[iu8Loop_i].u8AudLangIdx=AUD_LANG_UND;
                                    memcpy(&(pstVirtualCh->astSoundTrack[iu8Loop_i]), &(pstVirtualCh->astSoundTrack[iu8Loop_i]), sizeof(MS_SOUND_TRACK_ATSC));
                                    goto LeaveCheckVersionChange;
                                }
                            }
                        }
#endif
                        u8AudLangNum_New++;

                        if(u16AudioLangMask < (1<<MAX_AUD_LANG_NUM_ATSC))
                        {
                            u16AudioLangMask |= (1 << iu8Loop_i);
                        }
                        else
                        {
                            printf("Warning: AudioLangMask size is too small!\r\n");
                        }

                        //printf("\033[46;31m [%s][%d]  <%d> AuPid=%d, %d, 0X%x \033[0m\n",__FUNCTION__,__LINE__, iu8Loop_i, pstVirtualCh->astSoundTrack[iu8Loop_i].u16AudioPid, u8AudLangNum_New, u16AudioLangMask);
                        break;
                    }
                }
            }
        }

        if((fVaildAudioTrack == TRUE)&&(fAudioTrackFindInDB ==FALSE))
        {
            u8AudioTrackUpdateIndex[u8AudioupdateLoopCount] = (u8ValidAudLangNum-1);
            u8AudioupdateLoopCount++;

        }
        pu8LoopPosition = MApp_Dmx_FindNextLoop(pu8Section, pu8LoopPosition, u16TotalDescriptorLength, EN_PMT);
    }

    if(pstVirtualCh->u16VideoPid)
    {
        if(bHasFindVideoPidInDB==FALSE)
        {
            fTableVersionChanged = TRUE;
            goto LeaveCheckVersionChange;
        }
    }
    // coverity 95838
    if(u8ValidAudLangNum && u8ValidAudLangNum != (pstVirtualCh->u8AudLangNum - u8AudioNuminVCT))
    {
        if(u8ValidAudLangNum < (pstVirtualCh->u8AudLangNum - u8AudioNuminVCT))
        {
            ;
            DMX_DBG(DMX_PMT, printf("[PMT VerChg]Audio LangNum is descreasing %d -- > %d \r\n", (pstVirtualCh->u8AudLangNum - u8AudioNuminVCT), u8ValidAudLangNum));
        }
        else
        {
            ;
            DMX_DBG(DMX_PMT, printf("[PMT VerChg]Audio LangNum is increasing: %d -- > %d \r\n", (pstVirtualCh->u8AudLangNum - u8AudioNuminVCT), u8ValidAudLangNum));
        }
        fTableAudioNumChanged = TRUE;

        if((u8ValidAudLangNum) >= MAX_AUD_LANG_NUM_ATSC)
            u8ValidAudLangNum = (U8)MAX_AUD_LANG_NUM_ATSC;

        if(u8ValidAudLangNum != 0)
            pstVirtualCh->u8AudLangNum = u8ValidAudLangNum;
        for(iu8Loop_k = 0; iu8Loop_k < u8ValidAudLangNum; iu8Loop_k++)
        {
            memcpy(&pstVirtualCh->astSoundTrack[iu8Loop_k], &astSoundTrackPMT[iu8Loop_k], sizeof(MS_SOUND_TRACK_ATSC));
        }

        if((u8AudioNuminVCT != 0)&&(u8ValidAudLangNum<(U8)MAX_AUD_LANG_NUM_ATSC))
        {
            //Add VCT
            if(u8AudioNuminVCT >= (U8)MAX_AUD_LANG_NUM_ATSC-u8ValidAudLangNum)
                u8AudioNuminVCT = (U8)MAX_AUD_LANG_NUM_ATSC-u8ValidAudLangNum;

            iu8Loop_k = (pstVirtualCh->u8AudLangNum-1);
            for(iu8Loop_j = 0; iu8Loop_j < u8AudioNuminVCT; iu8Loop_j++)
            {
                memcpy(&pstVirtualCh->astSoundTrack[iu8Loop_k], &astSoundTrackVCT[iu8Loop_j], sizeof(MS_SOUND_TRACK_ATSC));
                pstVirtualCh->u8AudLangNum++;
            }
            //MApp_ChanProc_SetSingleChannel
        }
    #if ENABLE_ATSC_CHLIST_DISP_TOGETHER
        if (MApp_ChanProc_IsCurProgIndexAir())
        {
            MApp_ChanProc_SetSingleChannel(pstVirtualCh, VIR_CH_IDX_AIR(MApp_ChanProc_GetCurProgIndex()));
        }
        else
        {
            MApp_ChanProc_SetSingleChannel(pstVirtualCh, VIR_CH_IDX_CATV(MApp_ChanProc_GetCurCableProgIndex()));
         }
     #else
        MApp_ChanProc_SetSingleChannel(pstVirtualCh, VIR_CH_IDX(MApp_ChanProc_GetCurProgIndex()));
    #endif
        goto LeaveCheckVersionChange;
    }
    else
    {
        //list order, bsmod, priority, audio lang idx
        if(MApp_Dmx_PMT_CheckSoundTrackData())
        {
            for(iu8Loop_k = 0; iu8Loop_k < u8ValidAudLangNum; iu8Loop_k++)
            {
                memcpy(&pstVirtualCh->astSoundTrack[iu8Loop_k], &astSoundTrackPMT[iu8Loop_k], sizeof(MS_SOUND_TRACK_ATSC));
            }
            fTableAudioNumChanged = TRUE;
        #if ENABLE_ATSC_CHLIST_DISP_TOGETHER
            if (MApp_ChanProc_IsCurProgIndexAir())
            {
                MApp_ChanProc_SetSingleChannel(pstVirtualCh, VIR_CH_IDX_AIR(MApp_ChanProc_GetCurProgIndex()));
            }
            else
            {
                MApp_ChanProc_SetSingleChannel(pstVirtualCh, VIR_CH_IDX_CATV(MApp_ChanProc_GetCurCableProgIndex()));
            }
        #else
            MApp_ChanProc_SetSingleChannel(pstVirtualCh, VIR_CH_IDX(MApp_ChanProc_GetCurProgIndex()));
        #endif
        }
    }


LeaveCheckVersionChange:
#endif
    if(fTableVersionChanged)
    {
        printf(">>>>>>PMT VersionChange_%d>>>>>>>\n",__LINE__);
#if (ENABLE_ATSC_EPG_DB_2016)
        msAPI_AtscEpgDb_Delete_Event_By_RfNum(pstVirtualCh->u8RfNum);
#endif

        u8KeyCode = KEY_EXIT;
    }
    else
    {
        if (u8Version != vRfCh.u8PmtVersion)
        {
            vRfCh.u8PmtVersion = u8Version;
        }
    }

    if(fTableAudioNumChanged)
    {
        printf(">>>>>>PMT Audio Sound Track Change >>>>>>>\n");
    }

    return fTableVersionChanged;
}

void MApp_Dmx_PAT_Monitor_ATSC(void)
{
    MS_DMX_SECTIONMONITOR_PARA   stSectionMonitor;

    if (fEnablePatMonitor)
    {
        if(u8PatFid == MSAPI_DMX_INVALID_FLT_ID)
        {
            memset(stSectionMonitor.au8MaskByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);
            memset(stSectionMonitor.au8NotMatchByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);

            stSectionMonitor.u16PID = PID_PAT;
            stSectionMonitor.u32SectionFltType = MSAPI_DMX_FILTER_TYPE_SECTION_1K;
            stSectionMonitor.au8MatchByte[0] = TID_PAS; //table id
            stSectionMonitor.au8MaskByte[0] = 0xFF;
            stSectionMonitor.au8MatchByte[5] = 0x01;
            stSectionMonitor.au8MaskByte[5] = 0x01;
#if ENABLE_PAT_MUTISECTION
            stSectionMonitor.au8MatchByte[6] = MApp_ChanProc_GetCurChannelPointer()->u16PatSectionNum; //section number, we only need current channel section number
#else
            stSectionMonitor.au8MatchByte[6] = 0; //section number, we only need 1st section
#endif
            stSectionMonitor.au8MaskByte[6] = 0xFF;
            stSectionMonitor.pfNotify = MApp_Dmx_PAT_Cb;
            stSectionMonitor.u16TimeoutMilliSec = MSAPI_DMX_TIMEOUT_INFINITE;
            stSectionMonitor.pu8FID = &u8PatFid;
            stSectionMonitor.SectMode = DMX_SECT_MODE_ONESHOT|DMX_SECT_MODE_CRCCHK;

            if(msAPI_DMX_SectionMonitor(&stSectionMonitor, FALSE) == DMX_FILTER_STATUS_OK)
            {
                fEnablePatMonitor = FALSE;
                u32MonitorPatTimer = msAPI_Timer_GetTime0();
                g_fPatTimeout = FALSE;
            }
            else
            {
            }
        }
    }

    if(msAPI_Timer_DiffTimeFromNow(u32MonitorPatTimer) > PAT_MONITOR_PERIOD)
    {
        if(u8PatFid != MSAPI_DMX_INVALID_FLT_ID)
        {
          #if (ENABLE_PAT_TIMEOUT_NOSIGNAL)
            //PAT timeout monitor
            if((fEnablePatMonitor == FALSE) && (g_fPatTimeout == FALSE))
            {
                //if((stSystemInfo[0].u8PanelPowerStatus & PANEL_POWER_BLUESCREEN) != PANEL_POWER_BLUESCREEN)
                if( FALSE == MApi_XC_Sys_Get_BlueScreenStatus(MAIN_WINDOW) ) // Blue screen is Off
                {
                    g_fPatTimeout = TRUE;
                    g_fPatTimeoutNeedRecover = TRUE;
                    fTableVersionChanged = TRUE;
                    u8KeyCode = KEY_EXIT;

                    MApp_ChannelChange_DisableAV();

                    //disbale audio
                    MApi_AUDIO_SetCommand( (En_DVB_decCmdType)MSAPI_AUD_STOP );
                    msAPI_DMX_Stop( u8AudFid );

                    //disable video
                    msAPI_DMX_Stop( u8VidFid );
                    msAPI_VID_Command( MSAPI_VID_STOP );
                    MDrv_MVOP_Enable(FALSE);
                }
            }
          #else
            //PAT timeout monitor
            if((fEnablePatMonitor == FALSE) && (g_fPatTimeout == FALSE))
            {
            #if ENABLE_PAT_MUTISECTION
                //if((stSystemInfo[0].u8PanelPowerStatus & PANEL_POWER_BLUESCREEN) != PANEL_POWER_BLUESCREEN)
                if( FALSE == MApi_XC_Sys_Get_BlueScreenStatus(MAIN_WINDOW) ) // Blue screen is Off
            #endif
                {
                    printf("\033[33m >>>>>>PAT MONITOR VersionChange (%d)>>>>>>>\033[0m\n",__LINE__);

                    msAPI_DMX_Print_AllFilter();

                    fTableVersionChanged = TRUE;
                    u8KeyCode = KEY_EXIT;
                }
            }
          #endif

            u32MonitorPatTimer = msAPI_Timer_GetTime0();
        }
    }
}

void PrintEPGRatingInfo( MS_EPG_RATING *pstEPGRatingInfo)
{
    U8 iloop;
    UNUSED(pstEPGRatingInfo);
    for(iloop =0; iloop < 3/*sizeof(MS_EPG_RATING)*/;iloop++)
    {
        //printf("[%02bx]",(U8)(((U8*)pstEPGRatingInfo)[iloop]));
    }
}

static BOOLEAN MApp_Dmx_PMT_ChChange_Parse(U8 *pu8Section)
{

   // U8                u8_loop_i;
    U16 u16TotalDescriptorLength;
    U8* pu8Descriptor;

	//20120515Max Seperate pmt eit rating storage location
	memset(&stPMTRatinginfo, 0x00, sizeof(MS_EPG_RATING));

    // To indicate that no TV rating has received from EPG
    stPMTRatinginfo.u8TVRatingForEntire = INVALID_TV_RATING_FOR_ENTIRE;

    //PrintEPGRatingInfo(&stEventInfo.stRating);
    u16TotalDescriptorLength = ((pu8Section[10] & 0x0f) << 8) | pu8Section[11];

#if (SUPPORT_COMPONENT_NAME_DESCRIPTOR_FUNC)
{
    U8 *pu8LoopPosition;
    pu8LoopPosition = MApp_Dmx_FindFirstLoop(pu8Section, EN_PMT);
    while(pu8LoopPosition != NULL)
    {
        u16TotalDescriptorLength = ((pu8LoopPosition[3] & 0x0f) << 8) | pu8LoopPosition[4];
        if(pu8LoopPosition[0] == ST_AC3_AUD)//stream type
        {
            if(astgSoundTrack[g_u8AudLangSelected].u16AudioPid ==(((pu8LoopPosition[1] & 0x1f) << 8) | pu8LoopPosition[2]))
            {
                pu8Descriptor =MApp_Dmx_FindDescriptorTag(pu8LoopPosition + 5, TAG_CND, u16TotalDescriptorLength);
                if(pu8Descriptor != NULL)
                {
                    // U8 u8DesLength = pu8Descriptor[1];
                    MApp_Dmx_Parse_MSS(au8CompoenetDesBuff, &pu8Descriptor[2], MAX_CND_BUFF_LENGTH, ENABLE);
                    au8CompoenetDesBuff[0] = g_fIsUTF16;
                }
            }
        }
        pu8LoopPosition = MApp_Dmx_FindNextLoop(pu8Section, pu8LoopPosition, u16TotalDescriptorLength, EN_PMT);
    }
}
#endif



    pu8Descriptor = MApp_Dmx_FindDescriptorTag(pu8Section + 12, TAG_CAD_ATSC, u16TotalDescriptorLength);
    if(pu8Descriptor != NULL)
    {
        MApp_Dmx_Parse_Tag_CAD(pu8Descriptor, &(stPMTRatinginfo));
        PrintEPGRatingInfo(&stPMTRatinginfo);
        fSearchRatingfromPMT =TRUE;
        return TRUE;
    }
    return FALSE;
}
static BOOLEAN MApp_Dmx_PMT_Monitor_Parse(U8 *pu8Section)
{
    U16 u16TotalDescriptorLength = 0;
    U8* pu8Descriptor;
#if (!ENABLE_ATSC_EPG_DB_2016)
    U8 u8_loop_i=0,u8_loop_j=0;
    MS_EPG_EVENT    stEventInfo;
    U32 u32StartTime, u32EndTime;
    BOOLEAN bFindEvent = FALSE;
#endif
#if 1//parse rating in PMT
    {
        //if (GETBIT(stEpgDBInfo.u8EitRxOK, 0) == FALSE)
        {
            MApp_Dmx_PMT_ChChange_Parse(pu8Section);
        }
    }
#endif
#if ENABLE_OAD
    MApp_Dmx_Other_PMT_Parse(pu8Section);
#endif


#if (ENABLE_ATSC_EPG_DB_2016)  // Need to add this part
    u16TotalDescriptorLength = ((pu8Section[10] & 0x0f) << 8) | pu8Section[11];
    pu8Descriptor = MApp_Dmx_FindDescriptorTag(pu8Section + 12, TAG_CAD_ATSC, u16TotalDescriptorLength);
    //20120515Max Seperate pmt eit rating storage location -- PMT rating  no need to save it in db
    memset(&stPMTRatinginfo, 0x00, sizeof(MS_EPG_RATING));
    // To indicate that no TV rating has received from EPG
    stPMTRatinginfo.u8TVRatingForEntire = INVALID_TV_RATING_FOR_ENTIRE;

    if(pu8Descriptor != NULL)
    {
        MApp_Dmx_Parse_Tag_CAD(pu8Descriptor, &(stPMTRatinginfo));
        return TRUE;
    }
#else

    if ((GETBIT(stEpgDBInfo.u8EitRxOK, 0) == FALSE) || g_u32StreamTime == 0)
    {
        if(msAPI_Timer_DiffTimeFromNow(g_u32MonitorCADTimer) < 2000)
        {
            fEnablePmtMonitor = TRUE;
        }
        return FALSE;
    }

    for(u8_loop_j = 0; u8_loop_j <MAX_TBL_NUM;u8_loop_j++)
    {
        if(astEpgDbVchBuf[0].au8CntEvent_InTbl[u8_loop_j]==0)//check each Table event exist.
            break;

        // Find current event in current service channel
        for (u8_loop_i = 0; u8_loop_i < astEpgDbVchBuf[0].au8CntEvent_InTbl[u8_loop_j]; u8_loop_i++)
        {
            MApp_EpgDB_LoadEvent(0, 0, u8_loop_i, &stEventInfo);

            u32StartTime = stEventInfo.start_time - DEFAULT_SYSTEM_TIME - u8GpsUtcOffset;
            u32EndTime = u32StartTime + EPG_EVENT_LENGTH(stEventInfo.length[0], stEventInfo.length[1], stEventInfo.length[2]);
            // Corresponding event >> Event end time > Page start time     AND    Event start < Page end time
            if ((u32StartTime <= g_u32StreamTime) && (u32EndTime > g_u32StreamTime))
            {
                bFindEvent = TRUE;
                break;
            }
        }
    }
    if(bFindEvent == TRUE && (BOOLEAN)(stEventInfo.stRating.fRatingRxIsOK) == FALSE)//no CAD descriptor in EIT
    {
        u16TotalDescriptorLength = ((pu8Section[10] & 0x0f) << 8) | pu8Section[11];
        pu8Descriptor = MApp_Dmx_FindDescriptorTag(pu8Section + 12, TAG_CAD_ATSC, u16TotalDescriptorLength);
    	//20120515Max Seperate pmt eit rating storage location -- PMT rating  no need to save it in db
    	memset(&stPMTRatinginfo, 0x00, sizeof(MS_EPG_RATING));
        // To indicate that no TV rating has received from EPG
        stPMTRatinginfo.u8TVRatingForEntire = INVALID_TV_RATING_FOR_ENTIRE;

        if(pu8Descriptor != NULL)
        {
            MApp_Dmx_Parse_Tag_CAD(pu8Descriptor, &(stPMTRatinginfo));
            return TRUE;
        }
    }
#endif
    return FALSE;
}
void MApp_Dmx_PMT_Monitor_Cb(U8 u8FID,  DMX_EVENT enEvent)
{
    U32 u32ActualSize,u32RmnSize;
    MSAPI_DMX_FILTER_STATUS enStatus;
    enStatus=(MSAPI_DMX_FILTER_STATUS)enEvent;
    /*[1]check enStatus ====================================================*/
    switch(enStatus)
    {
        case MSAPI_DMX_FILTER_STATUS_SECAVAILABLE:
            {
                //DMX_DBG(DMX_PMT, printf("********MSAPI_DMX_FILTER_STATUS_SECAVAILABLE!! \r\n"));
                /* get section data */
                if(MApi_DMX_CopyData(u8FID, au8Section, MSAPI_DMX_SECTION_1K,&u32ActualSize,&u32RmnSize,NULL) == DMX_FILTER_STATUS_ERROR)
                {
                    DMX_DBG(DMX_PMT, printf("[FID=%bu] PMT get section fail!! \r\n", u8FID));
                    break;
                }

                if(msAPI_DMX_CheckCRC32(au8Section) == FALSE)
                {
                    DMX_DBG(DMX_PMT, printf("[FID=%bu] PMT get section check CRC error!!  case 1\n", u8FID));
                    enStatus = MSAPI_DMX_FILTER_STATUS_CRCINCORRECT;
                    au8CrcErrorCounter[u8FID]++;
                    break;
                }

                if(MApp_Dmx_PMT_CheckVersionChange(au8Section) == FALSE)
                {
                    //NO version change happen, parse PMT
                    MApp_Dmx_PMT_Monitor_Parse(au8Section);
                }
                break;
            }

        case MSAPI_DMX_FILTER_STATUS_CRCINCORRECT:
            {
            	DMX_DBG(DMX_PMT, printf("[FID=%bu] PMT get section check CRC error!! \r\n", u8FID));
                au8CrcErrorCounter[u8FID]++;
                break;
            }

        case MSAPI_DMX_FILTER_STATUS_TIMEOUT:
            {
            DMX_DBG(DMX_PMT, printf("[FID=%bu] PMT get section timeout!! \r\n", u8FID));
                break;
            }

         case MSAPI_DMX_FILTER_STATUS_OVERFLOW:
            {
            DMX_DBG(DMX_PMT, printf("[FID=%bu] PMT get section overflow!! \r\n", u8FID));
                break;
            }

       default:
            {
            DMX_DBG(DMX_PMT, printf("[FID=%bu] PMT get section unknow error!! \r\n", u8FID));
                break;
            }
    }

    /*[02]finalize ==========================================================*/
    if(enStatus == MSAPI_DMX_FILTER_STATUS_SECAVAILABLE)
    {
        msAPI_DMX_CloseFilter(u8FID);
        u8PmtFid = MSAPI_DMX_INVALID_FLT_ID;
    }
    else
    {
        msAPI_DMX_CloseFilter(u8FID);
    }
}
void MApp_Dmx_PMT_Monitor_ATSC(void)
{
    MS_DMX_SECTIONMONITOR_PARA   stSectionMonitor;

    if (fEnablePmtMonitor || (msAPI_Timer_DiffTimeFromNow(u32MonitorPmtTimer) > PMT_MONITOR_PERIOD))
    {
        if(u8PmtFid == MSAPI_DMX_INVALID_FLT_ID)
        {
	     memset(stSectionMonitor.au8MaskByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);
            memset(stSectionMonitor.au8NotMatchByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);

            pstVirtualCh = MApp_ChanProc_GetCurChannelPointer();
            stSectionMonitor.u16PID = pstVirtualCh->u16PmtPid;
            stSectionMonitor.au8MaskByte[0] = 0xFF;
            stSectionMonitor.au8MaskByte[3] = 0xFF;
            stSectionMonitor.au8MaskByte[4] = 0xFF;
            stSectionMonitor.au8MaskByte[5] = 0x01;
            stSectionMonitor.au8MatchByte[0] = TID_PMS; //table id
            stSectionMonitor.au8MatchByte[3] = HIGHBYTE(pstVirtualCh->u16ProgramNumber); //subtable id
            stSectionMonitor.au8MatchByte[4] = LOWBYTE(pstVirtualCh->u16ProgramNumber);
            stSectionMonitor.au8MatchByte[5] = 0x01;
            stSectionMonitor.u32SectionFltType = MSAPI_DMX_FILTER_TYPE_SECTION_1K;
            stSectionMonitor.pfNotify = MApp_Dmx_PMT_Monitor_Cb;
            stSectionMonitor.u16TimeoutMilliSec = MSAPI_DMX_TIMEOUT_INFINITE;
            stSectionMonitor.pu8FID = &u8PmtFid;
            stSectionMonitor.SectMode = DMX_SECT_MODE_ONESHOT|DMX_SECT_MODE_CRCCHK;
            if(msAPI_DMX_SectionMonitor(&stSectionMonitor,FALSE) == DMX_FILTER_STATUS_OK)
            {
                fEnablePmtMonitor = FALSE;
                u32MonitorPmtTimer = msAPI_Timer_GetTime0();
            }
        }
        else
        {
            fEnablePmtMonitor = FALSE;
            u32MonitorPmtTimer = msAPI_Timer_GetTime0();
        }
    }

}

/*****************************************************************************/
static void MApp_Dmx_PMT_Parse(MS_VIRTUAL_CHANNEL *pstVirtualCh_func, U8 *pu8Section)
{
    U8 *pu8LoopPosition, *pu8Descriptor;
    U16 u16TotalDescriptorLength;

    #if (CHECK_CA_DESC_ENABLE == 1)
    MS_U8 b8CAdescriptor;
    #endif

    /*[1]check error condition =============================================*/
    /*
    if( pstVirtualCh_func == NULL || pu8Section == NULL)
    {
       return;
    }
    */

    pastRfCh.u8PmtVersion = (pu8Section[5] & 0x3f) >> 1;

    /*[2]initial variables =================================================*/
    #if (CHECK_CA_DESC_ENABLE == 1)
    b8CAdescriptor = FALSE; //default = no CA descriptor
    #endif

    for(iu8Loop_l=0 ; iu8Loop_l < MAX_AUD_LANG_NUM_ATSC ; iu8Loop_l++)
    {
        pstVirtualCh_func->astSoundTrack[iu8Loop_l].u8AudAc3Bsmod = EN_PSIP_AC3_BSMOD_NUM;
        pstVirtualCh_func->astSoundTrack[iu8Loop_l].u8AudLangIdx = AUD_LANG_UND;
    }


    /*[3]get PCR Pid ======================================*/
    pstVirtualCh_func->u16PcrPid = ((pu8Section[8] & 0x1f) << 8) | pu8Section[9]; //PCR pid
    DMX_DBG(DMX_PMT, printf("==============================================>>>>\r\n"));
    DMX_DBG(DMX_PMT, printf("PMT section: PcrPid = 0x%04x\n", (U16)pstVirtualCh_func->u16PcrPid));

    /*[4]check whether has CA Descriptor in program layer ==================*/
    u16TotalDescriptorLength = ((pu8Section[10] & 0x0f) << 8) | pu8Section[11];
    DMX_DBG(DMX_PMT, printf("PMT section: u16TotalDescriptorLength = %d\n", (U16)u16TotalDescriptorLength));

    #if (CHECK_CA_DESC_ENABLE == 1)
    if(MApp_Dmx_FindDescriptorTag(pu8Section + 12, TAG_CaD, u16TotalDescriptorLength) != NULL)
    {
        DMX_DBG(DMX_PMT, printf("TAG_CaD is Scramble\r\n"));
        b8CAdescriptor = TRUE;
    }
    #endif

    /*[6]get programs ======================================================*/
    pu8LoopPosition = MApp_Dmx_FindFirstLoop(pu8Section, EN_PMT);
    while(pu8LoopPosition != NULL)
    {
        u16TotalDescriptorLength = ((pu8LoopPosition[3] & 0x0f) << 8) | pu8LoopPosition[4];

        switch(pu8LoopPosition[0]) //stream type
        {
            /* [5-1]video */
            case ST_MPEG1_VID:
                //mpeg 1 video
            case ST_MPEG2_VID:
            case ST_OP_MPEG2_VID:
                //mpeg 2 video
            case ST_AVCH264_VID:
            #if (ENABLE_H265)
            case ST_HEVC_H265_VID:
            #endif
                //AVC H.264 video
                {
                    /* only allow to get video pid once */
                    if(!pstVirtualCh_func->u16VideoPid /*== MSAPI_DMX_INVALID_PID*/)
                    {
                        /* video pid */
                        pstVirtualCh_func->u16VideoPid = ((pu8LoopPosition[1] & 0x1f) << 8) | pu8LoopPosition[2];
                        DMX_DBG(DMX_PMT, printf("VID_Pid = 0x%04x \r\n", (U16)pstVirtualCh_func->u16VideoPid));

                        /* video stream type */
                        CONVERT_VIDEO_TYPE(pu8LoopPosition[0], pstVirtualCh_func->stVirtualChNum.u8VideoStreamType);
                        DMX_DBG(DMX_PMT, printf("[PMT] VID stream type = 0x%x \r\n", (U16)pstVirtualCh_func->stVirtualChNum.u8VideoStreamType));

                        #if (CHECK_CA_DESC_ENABLE == 1)
                        /* find CA descriptor in component layer */
                        if(MApp_Dmx_FindDescriptorTag(pu8LoopPosition + 5, TAG_CaD, u16TotalDescriptorLength) != NULL)
                        {
                            DMX_DBG(DMX_PMT, printf("Video is Scramble\r\n"));
                            b8CAdescriptor = TRUE;
                            pstVirtualCh_func->u16ScrambleChStatus |= SCRAMBLE_VIDEO;
                        }
                        #endif
                    }
                    break;
                }
            break;
                /* [5-2]audio */
#if(ENABLE_DTV_MPEG_AUDIO)
            case ST_MPEG1_AUD:
                //mpeg 1 audio
            case ST_MPEG2_AUD:
                //mpeg 2 audio
#endif
            case ST_AC3_AUD:
#if (ENABLE_AC3P_AUDIO)
            case ST_AC3P_AUD:
#endif
            case ST_AAC_AUD:
            case ST_HEAAC_AUD:
                //AC-3 audio
                {
                    /* store MAX_AUD_LANG_NUM_ATSC audio PIDs only */
                    if(pstVirtualCh_func->u8AudLangNum < MAX_AUD_LANG_NUM_ATSC)
                    {
                        BOOLEAN bLangInAC3Des = 0;

                        /* audio stream type */
                        CONVERT_AUDIO_TYPE(pu8LoopPosition[0], pstVirtualCh_func->astSoundTrack[pstVirtualCh_func->u8AudLangNum].u16AudStreamType);
                        DMX_DBG(DMX_PMT, printf("u16AudStreamType=[0x%x]>>\r\n", pu8LoopPosition[0]));

                        /* audio pid */
                        pstVirtualCh_func->astSoundTrack[pstVirtualCh_func->u8AudLangNum].u16AudioPid = ((pu8LoopPosition[1] & 0x1f) << 8) | pu8LoopPosition[2];
                        DMX_DBG(DMX_PMT, printf("AUD[%d]>> Pid 0x%04x \r\n", (U8) pstVirtualCh_func->u8AudLangNum, (U16)pstVirtualCh_func->astSoundTrack[pstVirtualCh_func->u8AudLangNum].u16AudioPid));

                        /* get AC3 descriptor */
                        pu8Descriptor = MApp_Dmx_FindDescriptorTag(pu8LoopPosition + 5, TAG_AC3AD, u16TotalDescriptorLength);
                        if(pu8Descriptor != NULL)
                        {
                            MAPI_PSIP_AC3_DES_A stAC3Descriptor;
                            memset(&stAC3Descriptor, 0, sizeof(MAPI_PSIP_AC3_DES_A));
                            stAC3Descriptor.u8BsMod =EN_PSIP_AC3_BSMOD_NUM;
                            MApp_Dmx_Parse_AC3Descriptor(pu8Descriptor, &stAC3Descriptor);

                            pstVirtualCh_func->astSoundTrack[pstVirtualCh_func->u8AudLangNum].u8AudAc3Bsmod = stAC3Descriptor.u8BsMod;
                            pstVirtualCh_func->astSoundTrack[pstVirtualCh_func->u8AudLangNum].u8Priority = stAC3Descriptor.u8Priority;
                            if(stAC3Descriptor.u8LangFlag1)
                            {
                                pstVirtualCh_func->astSoundTrack[pstVirtualCh_func->u8AudLangNum].u8AudLangIdx = MApp_Dmx_GetISO639LangCode(&(stAC3Descriptor.u8Lang1[0]));
                                pstVirtualCh_func->astSoundTrack[pstVirtualCh_func->u8AudLangNum].u16IsAudLangGetinPMT = 1;
                                bLangInAC3Des = 1;
                                pstVirtualCh_func->astSoundTrack[pstVirtualCh_func->u8AudLangNum].u16AC3inPMT = 1;
                                //printf("u8AudLangIdx  = %d\n", pstVirtualChSndTrk_func->astSoundTrack[pstVirtualChSndTrk_func->u8AudLangNum].u16AudLangIdx);
                            }
                        }


                        {
                            /* get language descriptor */
                            pu8Descriptor = MApp_Dmx_FindDescriptorTag(pu8LoopPosition + 5, TAG_LnD, u16TotalDescriptorLength);
                            if(pu8Descriptor != NULL)
                            {
                                pstVirtualCh_func->astSoundTrack[pstVirtualCh_func->u8AudLangNum].u8AudLangIdx = MApp_Dmx_GetISO639LangCode(&pu8Descriptor[2]);
                                pstVirtualCh_func->astSoundTrack[pstVirtualCh_func->u8AudLangNum].u16IsAudLangGetinPMT = 1;
                            }
                            else if(bLangInAC3Des == 0)
                            {
                                pstVirtualCh_func->astSoundTrack[pstVirtualCh_func->u8AudLangNum].u8AudLangIdx = AUD_LANG_UND;
                                pstVirtualCh_func->astSoundTrack[pstVirtualCh_func->u8AudLangNum].u16IsAudLangGetinPMT = 0;
                                DMX_DBG(DMX_PMT, printf("[TAG_LnD Not find default to other] Lang %d =other \n", (U8)pstVirtualCh_func->u8AudLangNum));
                            }
                        }
                        pstVirtualCh_func->astSoundTrack[pstVirtualCh_func->u8AudLangNum].u8AudPidInPMT = TRUE;
                        pstVirtualCh_func->u8AudLangNum++;
                    }

                    #if (CHECK_CA_DESC_ENABLE == 1)
                    /* find CA descriptor in component layer */
                    if(MApp_Dmx_FindDescriptorTag(pu8LoopPosition + 5, TAG_CaD, u16TotalDescriptorLength) != NULL)
                    {
                        DMX_DBG(DMX_PMT, printf("Audio is Scramble\r\n" ));
                        b8CAdescriptor = TRUE;
                        pstVirtualCh_func->u16ScrambleChStatus |= SCRAMBLE_AUDIO;
                    }
                    #endif
                    //sync parse still pic field
                    pu8Descriptor = MApp_Dmx_FindDescriptorTag(pu8LoopPosition + 5, TAG_VSD, u16TotalDescriptorLength);
                    if(pu8Descriptor != NULL)
                    {
                        pstVirtualCh_func->u16StillPic = _bit0_(pu8Descriptor[2]);
                    }
                    break;
                }

            /*[5-3]private data ============================================*/
            #if 0
             case ST_PRIVATE_DATA:
             {
                 break;
             }
            #endif

            /*[5-4]otsher ===================================================*/
            default:
                {
                    break;
                }
        }
        pu8LoopPosition = MApp_Dmx_FindNextLoop(pu8Section, pu8LoopPosition, u16TotalDescriptorLength, EN_PMT);
    }

    /*[7]final correction ==================================================*/

    //printf("<< PMT >> PCR = 0x%04X, Video = 0x%04X, Audio = 0x%04X\r\n", (U16)pstVirtualCh_func->u16PcrPid, (U16)pstVirtualCh_func->u16VideoPid, pstVirtualCh_func->astSoundTrack[0].u16AudioPid);

    #if (CHECK_CA_DESC_ENABLE == 1)
    /* FTA/CA */
    DMX_DBG(DMX_PMT, printf("b8CAdescriptor = %d\n", (U8)b8CAdescriptor));
    if(b8CAdescriptor == TRUE)
    {
        pstVirtualCh_func->fIsScrambleCh = TRUE;
    }
    else
    {
        pstVirtualCh_func->fIsScrambleCh = FALSE;
    }
    #endif
    DMX_DBG(DMX_PMT, printf("==============================================>>>>\r\n"));
}
/*****************************************************************************/
void MApp_Dmx_PMT_Cb(U8 u8FID, DMX_EVENT enEvent)
{
    U32 u32ActualSize,u32RmnSize;
    MSAPI_DMX_FILTER_STATUS enStatus;
    enStatus=(MSAPI_DMX_FILTER_STATUS)enEvent;

    /*[1]check enStatus ====================================================*/
    DMX_DBG(DMX_PMT, printf("pmt cb>> u8FID %d enStatus %d\n", u8FID, (U8)enStatus));

    switch(enStatus)
    {
        case MSAPI_DMX_FILTER_STATUS_SECAVAILABLE:
        {
            /* get section data */
            if(MApi_DMX_CopyData(u8FID, au8Section, MSAPI_DMX_SECTION_1K,&u32ActualSize,&u32RmnSize,NULL) == DMX_FILTER_STATUS_ERROR)
            {
                DMX_DBG(DMX_PMT, printf("[FID=%d] PMT %d Prog# 0x%x get section fail\n", u8FID, au8FID2ItemIdx[u8FID], pastPATItem[au8FID2ItemIdx[u8FID]].u16ProgramNumber));
                break;
            }

    // To Do: Need to modify with new MDDI, 2009/04/03
    #if (!ENABLE_NEW_DMX_INTERFACE)
            if(msAPI_DMX_CheckCRC32(au8Section) == FALSE)
            {
//                DMX_DBG(DMX_PMT, printf("[FID=%d] PMT %d Prog# 0x%x check CRC error Case 1\n", u8FID, au8PsiFID2ItemIdx[u8FID], pastPATItem[au8PsiFID2ItemIdx[u8FID]].u16ProgramNumber));
                enStatus = MSAPI_DMX_FILTER_STATUS_CRCINCORRECT;
                au8CrcErrorCounter[u8FID]++;
                break;
            }
    #endif
        #if 0   // should be remove after
            if ( (au8Section[0]!=0x02) && ( au8Section[7] > 0 ))
            {
                printf( "<< Wrong PMT Section >>\r\n" );
                MApp_Dmx_DumpSectionData( 29);
            }
        #endif

            /* parsing table */
            #if 0
            if( au8Section[7] > 0 ) //last section num
            {
                DMX_DBG(DMX_PMT, printf( "Warning! No of PMT section > 1!!\r\n" ) );
            }
            #endif

            MApp_Dmx_PMT_Parse(pastVirtualCh + au8FID2ItemIdx[u8FID], au8Section);
            (pastVirtualCh + au8FID2ItemIdx[u8FID])->u16PmtPid = au16PID2ItemIdx[u8FID];

            break;
        }

    #if (!ENABLE_NEW_DMX_INTERFACE)
        case MSAPI_DMX_FILTER_STATUS_CRCINCORRECT:
            {
                DMX_DBG(DMX_PMT, printf("[FID=%d] PMT %d Prog# 0x%x check CRC error\n", u8FID, au8FID2ItemIdx[u8FID], pastPATItem[au8FID2ItemIdx[u8FID]].u16ProgramNumber));
                au8CrcErrorCounter[u8FID]++;
                break;
            }

        case MSAPI_DMX_FILTER_STATUS_TIMEOUT:
            {
                DMX_DBG(DMX_PMT, printf("[FID=%d] PMT %d Prog# 0x%x timeout\n", u8FID, au8FID2ItemIdx[u8FID], pastPATItem[au8FID2ItemIdx[u8FID]].u16ProgramNumber));
                break;
            }

        case MSAPI_DMX_FILTER_STATUS_OVERFLOW:
            {
                DMX_DBG(DMX_PMT, printf("[FID=%d] PMT %d Prog# 0x%x overflow\n", u8FID, au8FID2ItemIdx[u8FID], pastPATItem[au8FID2ItemIdx[u8FID]].u16ProgramNumber));
                break;
            }
    #endif

        default:
            {
                DMX_DBG(DMX_PMT, printf("[FID=%d] PMT %d Prog# 0x%x unknow error\n", u8FID, au8FID2ItemIdx[u8FID], pastPATItem[au8FID2ItemIdx[u8FID]].u16ProgramNumber));
                break;
            }
    }

    /*[02]finalize ==========================================================*/
    // To Do: Need to modify with new MDDI, 2009/04/03
    if(enStatus==MSAPI_DMX_FILTER_STATUS_CRCINCORRECT && au8CrcErrorCounter[u8FID]<=MAX_NUM_OF_CRC_ERROR)
    {
        DMX_DBG(DMX_PMT, printf("Restart PMT[%d] filter >> [FID=%d] Prog# 0x%x\n", au8FID2ItemIdx[u8FID], u8FID, pastPATItem[au8FID2ItemIdx[u8FID]].u16ProgramNumber));
        msAPI_DMX_RestartFilter(u8FID);
    }
    else
    {
        msAPI_DMX_CloseFilter(u8FID);
        //printf ("Close Filter PMT %d \n", u8FID);

        u8OpenedFltCounter--;
        au8CrcErrorCounter[u8FID] = 0;
        au8FID2ItemIdx[u8FID] = MSAPI_DMX_INVALID_FLT_ID;
    }
}
void MApp_Dmx_PMT_ChChange(void)
{
    MS_DMX_SECTIONMONITOR_PARA   stSectionMonitor;

    if(u8PmtFid == MSAPI_DMX_INVALID_FLT_ID)
    {
        memset(stSectionMonitor.au8MaskByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);
        memset(stSectionMonitor.au8NotMatchByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);

        pstVirtualCh = MApp_ChanProc_GetCurChannelPointer();
        stSectionMonitor.u16PID = pstVirtualCh->u16PmtPid;
        stSectionMonitor.au8MaskByte[0] = 0xFF;
        stSectionMonitor.au8MaskByte[3] = 0xFF;
        stSectionMonitor.au8MaskByte[4] = 0xFF;
        stSectionMonitor.au8MaskByte[5] = 0x01;
        stSectionMonitor.au8MatchByte[0] = TID_PMS; //table id
        stSectionMonitor.au8MatchByte[3] = HIGHBYTE(pstVirtualCh->u16ProgramNumber); //subtable id
        stSectionMonitor.au8MatchByte[4] = LOWBYTE(pstVirtualCh->u16ProgramNumber);
        stSectionMonitor.au8MatchByte[5] = 0x01;
        stSectionMonitor.u32SectionFltType = MSAPI_DMX_FILTER_TYPE_SECTION_1K;
        stSectionMonitor.pfNotify = MApp_Dmx_PMT_Monitor_Cb;
        stSectionMonitor.u16TimeoutMilliSec = MSAPI_DMX_TIMEOUT_INFINITE;
        stSectionMonitor.pu8FID = &u8PmtFid;
        stSectionMonitor.SectMode = DMX_SECT_MODE_ONESHOT|DMX_SECT_MODE_CRCCHK;

        if(msAPI_DMX_SectionMonitor(&stSectionMonitor,FALSE) == DMX_FILTER_STATUS_OK)
        {
            fEnablePmtMonitor = FALSE;
            u32MonitorPmtTimer = msAPI_Timer_GetTime0();
        }
    }
    else
    {
        fEnablePmtMonitor = FALSE;
        u32MonitorPmtTimer = msAPI_Timer_GetTime0();
    }
}
#if 1
/*****************************************************************************/
/*         Monitor, Callback and Parsing function for PSIP Table             */
/*****************************************************************************/
/***                                                                       ***/
/***  === STT ===   1. MApp_Dmx_STT_Cb                                     ***/
/***                2. MApp_Dmx_STT_Monitor                                ***/
/***                                                                       ***/
/***  === MGT ===   1. MApp_Dmx_MGT_Parse                                  ***/
/***                2. MApp_Dmx_MGT_Cb                                     ***/
/***                3. MApp_Dmx_MGT_Monitor                                ***/
/***                                                                       ***/
/***  === VCT ===   1. MApp_Dmx_TVCT_CheckVersionChange                    ***/
/***                2. MApp_Dmx_CVCT_CheckVersionChange                    ***/
/***                3. MApp_Dmx_TVCT_NoParser_Cb                           ***/
/***                4. MApp_Dmx_CVCT_NoParser_Cb                           ***/
/***                5. MApp_Dmx_VCT_Parse                                  ***/
/***                6. MApp_Dmx_TVCT_Cb                                    ***/
/***                7. MApp_Dmx_CVCT_Cb                                    ***/
/***                8. MApp_Dmx_TVCT_Monitor                               ***/
/***                9. MApp_Dmx_CVCT_Monitor                               ***/
/***                                                                       ***/
/***                  === MApp_Dmx_GetScanTables_ATSC ===                       ***/
/***                                                                       ***/
/***  === EIT ===   1. MApp_Dmx_EIT_Check                                  ***/
/***                2. MApp_Dmx_EIT_Set_Flag                               ***/
/***                3. MApp_Dmx_EIT_Monitor                                ***/
/***                4. MApp_Dmx_EIT_Cb                                     ***/
/***                5. MApp_Dmx_EIT_Monitor                                ***/
/***                                                                       ***/
/***  = Scramble =  1. MApp_Dmx_Scramble_Cb                                ***/
/***                2. MApp_Dmx_Scramble_Monitor                           ***/
/***                                                                       ***/
/***  === RRT ===   1. MApp_Dmx_RRT_Parse                                  ***/
/***                2. MApp_Dmx_RRT_Cb                                     ***/
/***                3. MApp_Dmx_RRT_Monitor                                ***/
/***                                                                       ***/
/*****************************************************************************/
#endif
/*****************************************************************************/
extern S32 volatile gS32OffsetTime;

void MApp_Dmx_STT_Cb(U8 u8FID, DMX_EVENT enEvent)
{
    BOOL bDS_status;
    U32 u32ActualSize,u32RmnSize;
    MSAPI_DMX_FILTER_STATUS enStatus;
    enStatus=(MSAPI_DMX_FILTER_STATUS)enEvent;

    /*[1]check enStatus ====================================================*/
    DMX_DBG(DMX_STT, printf("stt cb>> u8FID %d enStatus %d\n", u8FID, (U8)enStatus));

    switch(enStatus)
    {
        /* TDT has no CRC, so demux will return either incorrect crc or section available to application */
        case MSAPI_DMX_FILTER_STATUS_SECAVAILABLE:
            {
                /* get section data */
                if(MApi_DMX_CopyData(u8FID, au8Section, MSAPI_DMX_SECTION_1K,&u32ActualSize,&u32RmnSize,NULL) == DMX_FILTER_STATUS_ERROR)
                {
                    DMX_DBG(DMX_STT, printf("[FID=%d] STT get section fail!! \r\n", u8FID));
                    break;
                }

                if(msAPI_DMX_CheckCRC32(au8Section) == FALSE)
                {
                      DMX_DBG(DMX_STT, printf("[FID=%d] STT get section check CRC error!! Case 1\n", u8FID));
                      enStatus = MSAPI_DMX_FILTER_STATUS_CRCINCORRECT;
                      break;
                }

                DMX_DBG(DMX_STT, printf("STT: %02bX %02bX %02bX %02bX %02bX %02bX %02bX \r\n", au8Section[9], au8Section[10], au8Section[11], au8Section[12], au8Section[13], au8Section[14], au8Section[15]));

                /* UTC time = GPS time - GPS_UTC_Offset */
                u8GpsUtcOffset = au8Section[13];
                //memcpy(&iu32Buffer_i, au8Section+9, 4);
                iu32Buffer_i = au8Section[9];
                iu32Buffer_i <<= 8;
                iu32Buffer_i |= au8Section[10];
                iu32Buffer_i <<= 8;
                iu32Buffer_i |= au8Section[11];
                iu32Buffer_i <<= 8;
                iu32Buffer_i |= au8Section[12];
                iu32Buffer_i -= u8GpsUtcOffset;

                if(iu32Buffer_i > DEFAULT_SYSTEM_TIME)
                    iu32Buffer_i -= DEFAULT_SYSTEM_TIME;
                else
                {
                    iu32Buffer_i = 0;
                }
                g_u32StreamTime = iu32Buffer_i;

                DMX_DBG(DMX_STT, printf("Stream Time=%lu, GpsUtcOffset=%u\n", g_u32StreamTime, u8GpsUtcOffset));

                if ( stGenSetting.g_SysSetting.fTimeAutoSync )
                {
                    msAPI_Timer_SetSystemTime(iu32Buffer_i);
                    g_u8TimeInfo_Flag |= UI_TIME_MANUAL_SET;
                }
                /* Daylight saving time control */
                bDS_status = (BOOL)(au8Section[14] >> 7);
                u8DaylightSavingDay = (au8Section[14] & 0x1F);
                u8DaylightSavingHour = au8Section[15];
                if ( stGenSetting.g_SysSetting.fTimeAutoSync )
                {
                    if((0 != u8DaylightSavingDay) && (0 != u8DaylightSavingHour)) //Need to compare with stream time(+time zone) and DS_Day&&DS_Hour
                    {
                        ST_TIME stTempClock;

                        //stGenSetting.g_SysSetting.fTimeDST = bDS_status;
                        stGenSetting.g_SysSetting.fTimeDSTStatusControl = bDS_status;
                        gS32OffsetTime = (U32)MApp_GetTimeZoneOffset(stGenSetting.g_SysSetting.u8TimeZone);

                        MApp_ConvertLocalTime2Date((S32)(g_u32StreamTime + stGenSetting.g_Time.s32Offset_Time),&stTempClock);
                        if(((stTempClock.u8Day == u8DaylightSavingDay) && (stTempClock.u8Hour >= u8DaylightSavingHour))
                            ||(stTempClock.u8Day > u8DaylightSavingDay))
                        {
                            if(bDS_status)
                            {
                                bDS_status = FALSE; // OUT of daylight savings time
                            }
                            else
                            {
                                bDS_status = TRUE; // INTO daylight savings time
                            }
                            DMX_DBG(DMX_STT, printf("DaylightSaving=%u\n", (U8)bDS_status));
                        }
                    }
                    //stGenSetting.g_SysSetting.fTimeDST = bDS_status;
                    stGenSetting.g_SysSetting.fTimeDSTStatusControl = bDS_status;
                    gS32OffsetTime = (U32)MApp_GetTimeZoneOffset(stGenSetting.g_SysSetting.u8TimeZone);
                }
                break;
            }

    #if (!ENABLE_NEW_DMX_INTERFACE)
        case MSAPI_DMX_FILTER_STATUS_CRCINCORRECT:
            {
            DMX_DBG(DMX_STT, printf("[FID=%d] STT get section check CRC error!! \r\n", u8FID));
                break;
            }

        case MSAPI_DMX_FILTER_STATUS_TIMEOUT:
            {
            DMX_DBG(DMX_STT, printf("[FID=%d] STT get section timeout!! \r\n", u8FID));
                break;
            }

        case MSAPI_DMX_FILTER_STATUS_OVERFLOW:
            {
            DMX_DBG(DMX_STT, printf("[FID=%d] STT get section overflow!! \r\n", u8FID));
                break;
            }
    #endif

        default:
            {
            DMX_DBG(DMX_STT, printf("[FID=%d] STT get section unknow error!! \r\n", u8FID));
                break;
            }
    }

    /*[02]finalize ==========================================================*/
    if(enStatus == MSAPI_DMX_FILTER_STATUS_SECAVAILABLE)
    {
        msAPI_DMX_CloseFilter(u8FID);
        u8SttFid = MSAPI_DMX_INVALID_FLT_ID;
    }
    else
    {
        DMX_DBG(DMX_STT, printf("Restart STT filter>> [FID=%d]\r\n", u8FID));
        msAPI_DMX_RestartFilter(u8FID);
    }
}
/*****************************************************************************/
void MApp_Dmx_STT_Monitor(void)
{
    MS_DMX_SECTIONMONITOR_PARA   stSectionMonitor;

    if(fEnableSttMonitor || msAPI_Timer_DiffTimeFromNow(u32MonitorSttTimer) > STT_MONITOR_PERIOD)
    {
        if(u8SttFid == MSAPI_DMX_INVALID_FLT_ID)
        {
            memset(stSectionMonitor.au8MaskByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);
            memset(stSectionMonitor.au8NotMatchByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);
            stSectionMonitor.u16PID = PID_BASE;
            stSectionMonitor.u32SectionFltType = MSAPI_DMX_FILTER_TYPE_SECTION_1K;
            stSectionMonitor.au8MatchByte[0] = TID_STS; //table id
            stSectionMonitor.au8MaskByte[0] = 0xFF;
            //stSectionMonitor.au8MatchByte[3] = 0x00;  //subtable id
            //stSectionMonitor.au8MatchByte[4] = 0x00;
            //stSectionMonitor.au8MaskByte[3] = 0x00;
            //stSectionMonitor.au8MaskByte[4] = 0x00;
            //stSectionMonitor.au8MatchByte[6] = 0x00;  //section number
            //stSectionMonitor.au8MaskByte[6] = 0x00;
            stSectionMonitor.au8MatchByte[8]    = 0x00;    // protocol_version
            stSectionMonitor.au8MaskByte[8]    = 0xFF;
            stSectionMonitor.pfNotify = MApp_Dmx_STT_Cb;
            stSectionMonitor.u16TimeoutMilliSec = MSAPI_DMX_TIMEOUT_INFINITE;
            stSectionMonitor.pu8FID = &u8SttFid;
            stSectionMonitor.SectMode = DMX_SECT_MODE_ONESHOT|DMX_SECT_MODE_CRCCHK;

            if(msAPI_DMX_SectionMonitor(&stSectionMonitor, FALSE) == DMX_FILTER_STATUS_OK)
            {
                DMX_DBG(DMX_STT, printf("monitoring STT at Filter #%d \r\n", u8SttFid));
                fEnableSttMonitor = FALSE;
                u32MonitorSttTimer = msAPI_Timer_GetTime0();
            }
            else
            {
                DMX_DBG(DMX_STT, printf("monitor STT fail!! \r\n"));
            }
        }
        else
        {
            DMX_DBG(DMX_STT, printf("monitoring STT at Filter #%d \r\n", u8SttFid));
            //msAPI_DMX_RestartFilter(u8SttFid);
            fEnableSttMonitor = FALSE;
            u32MonitorSttTimer = msAPI_Timer_GetTime0();
        }
    }
}
/*****************************************************************************/
static void MApp_Dmx_MGT_Parse(MS_MGT_ST *pstMgt, U8 *pu8Section)
{
    U8 version_number;
    U16 tables_defined, table_type, descriptors_length;
    U8 u8Idx;

    /*[1]check error condition =============================================*/
    /*
    if( pstMgt == NULL || pu8Section == NULL )
    {
       return;
    }
    */

    /*[2]check version change ==============================================*/
    DMX_DBG(DMX_MGT, printf("==============================================>>>>\r\n"));
    version_number = (pu8Section[5]>>1)&0x1f;
    if(version_number == stMGT.version_number) //same version
    {
        DMX_DBG(DMX_MGT, printf("Parse MGT>> same version number %d\n", stMGT.version_number));
        return;
    }

    /*[3]init variables ====================================================*/
    memset(pstMgt, 0, sizeof(MS_MGT_ST));
#if (ENABLE_ATSC_EPG_DB_2016)
    u8EttNumber = 0;
    memset(u8EttReceived, 0, sizeof(U8)*NEW_MAX_TAB_NUM);
#endif
    stMGT.version_number = version_number;

    tables_defined = pu8Section[9]<<8 | pu8Section[10];


    DMX_DBG(DMX_MGT, printf("parse MGT, version_number = %d, tables_defined # = %u\n", (U8)stMGT.version_number, (U16)tables_defined));

    /*[4]move to first item position =======================================*/
    pu8Section += 11;

    /*[5]get items =========================================================*/
    for(iu16Loop_i = 0; iu16Loop_i < tables_defined; iu16Loop_i++)
    {
        table_type = pu8Section[0]<<8 | pu8Section[1];
#if (ENABLE_ATSC_EPG_DB_2016)
    #if (NEW_MAX_TAB_NUM==8)
        if(table_type>=TABLE_TYPE_EIT_0 && table_type<=TABLE_TYPE_EIT_7) //store standard EIT-0~55
    #else
        if(table_type>=TABLE_TYPE_EIT_0 && table_type<=TABLE_TYPE_EIT_55) //store standard EIT-0~55
    #endif
#else
        if(table_type>=TABLE_TYPE_EIT_0 && table_type<=TABLE_TYPE_EIT_7) //store standard EIT-0~7
#endif
        {
            u8Idx = table_type-TABLE_TYPE_EIT_0;

            /*[5-1] retrieve table again once pid or version number change ===============================================*/
            if (stMGT.astEitItem[u8Idx].table_type_PID                 != (((pu8Section[2] & 0x1f) << 8) | pu8Section[3])
            ||  stMGT.astEitItem[u8Idx].table_type_version_number     !=  (pu8Section[4]&0x1f))
            {
                stMGT.astEitItem[u8Idx].table_type_PID                 = ((pu8Section[2] & 0x1f) << 8) | pu8Section[3];
                stMGT.astEitItem[u8Idx].table_type_version_number     = pu8Section[4]&0x1f;
                stMGT.astEitItem[u8Idx].fDoNotRetrieveTable = FALSE;
            }

            DMX_DBG(DMX_MGT, printf("EIT-%d>> Pid=0x%04X, version_number=%d, fDoNotRetrieveTable=%d\n", u8Idx, (U16)stMGT.astEitItem[u8Idx].table_type_PID, (U8)stMGT.astEitItem[u8Idx].table_type_version_number, (U8)stMGT.astEitItem[u8Idx].fDoNotRetrieveTable) );
        }
#if (ENABLE_ATSC_EPG_DB_2016)
    #if (NEW_MAX_TAB_NUM==8)
        else if(table_type>=TABLE_TYPE_ETT_0 && table_type<=TABLE_TYPE_ETT_7) //store standard ETT-0~7
    #else
        else if(table_type>=TABLE_TYPE_ETT_0 && table_type<=TABLE_TYPE_ETT_55) //store standard ETT-0~7
    #endif
#else
        else if(table_type>=TABLE_TYPE_ETT_0 && table_type<=TABLE_TYPE_ETT_7) //store standard ETT-0~7
#endif
        {
            u8Idx = table_type-TABLE_TYPE_ETT_0;

            /*[5-1] retrieve table again once pid or version number change ===============================================*/
            if(stMGT.astEttItem[u8Idx].table_type_PID                 != (((pu8Section[2] & 0x1f) << 8) | pu8Section[3])
            || stMGT.astEttItem[u8Idx].table_type_version_number     != (pu8Section[4]&0x1f))
            {
                stMGT.astEttItem[u8Idx].table_type_PID                 = ((pu8Section[2] & 0x1f) << 8) | pu8Section[3];
                stMGT.astEttItem[u8Idx].table_type_version_number     = pu8Section[4]&0x1f;
                stMGT.astEttItem[u8Idx].fDoNotRetrieveTable = FALSE;
                #if (ENABLE_ATSC_EPG_DB_2016)
                u8EttNumber++;
                #endif
            }
            DMX_DBG(DMX_MGT, printf("ETT-%d>> Pid=0x%04X, version_number=%d, fDoNotRetrieveTable=%d\n", u8Idx, (U16)stMGT.astEttItem[u8Idx].table_type_PID, (U8)stMGT.astEttItem[u8Idx].table_type_version_number, (U8)stMGT.astEttItem[u8Idx].fDoNotRetrieveTable) );
        }
        else if(table_type==TABLE_TYPE_CURRENT_TVCT || table_type==TABLE_TYPE_CURRENT_CVCT)
        {
            /*[5-1] retrieve table again once pid or version number change ===============================================*/
            if(stMGT.stVctItem.table_type_PID                 != (((pu8Section[2] & 0x1f) << 8) | pu8Section[3]) ||
               stMGT.stVctItem.table_type_version_number     != (pu8Section[4]&0x1f))
            {
            stMGT.stVctItem.table_type_PID = ((pu8Section[2] & 0x1f) << 8) | pu8Section[3];
            stMGT.stVctItem.table_type_version_number = pu8Section[4]&0x1f;
                stMGT.stVctItem.fDoNotRetrieveTable = FALSE;
            }

            DMX_DBG(DMX_MGT, printf("VCT>> Pid=0x%04X, version_number=%d, fDoNotRetrieveTable=%d\n", (U16)stMGT.stVctItem.table_type_PID, (U8)stMGT.stVctItem.table_type_version_number, (U8)stMGT.stVctItem.fDoNotRetrieveTable) );
        }
#if (ENABLE_MEXICO_VCHIP)
        else if(table_type>=TABLE_TYPE_RRT_1 && table_type<=TABLE_TYPE_RRT_255)
        {
            //update RRT region
            stMGT.u8RrtRegionNo = (table_type-TABLE_TYPE_RRT_1)+1;
            u8CurrentRrtRegionNo = stMGT.u8RrtRegionNo;
            DMX_DBG(DMX_MGT, printf("RRT [0x%02X]>> Pid=0x%04X, version_number=%d\n", (table_type-TABLE_TYPE_RRT_1)+1, (((pu8Section[2] & 0x1f) << 8) | pu8Section[3]), (pu8Section[4]&0x1f)) );
        }
#endif

        descriptors_length = (pu8Section[9]<<8 | pu8Section[10])&0x0FFF;
        pu8Section += (11 + descriptors_length);    //move to next item
    }

    DMX_DBG(DMX_MGT, printf("==============================================>>>>\r\n"));
}
/*****************************************************************************/
void MApp_Dmx_MGT_Cb(U8 u8FID, DMX_EVENT enEvent)
{
    U32 u32ActualSize,u32RmnSize;
    MSAPI_DMX_FILTER_STATUS enStatus;
    enStatus=(MSAPI_DMX_FILTER_STATUS)enEvent;

    /*[1]check enStatus ====================================================*/
    DMX_DBG(DMX_MGT, printf("mgt cb>> u8FID %d enStatus %d\n", u8FID, (U8)enStatus));

    switch(enStatus)
    {
        case MSAPI_DMX_FILTER_STATUS_SECAVAILABLE:
            {
                /* get section data */
                if(MApi_DMX_CopyData(u8FID, au8Section, MSAPI_DMX_SECTION_4K,&u32ActualSize,&u32RmnSize,NULL) == DMX_FILTER_STATUS_ERROR)
                {
                    DMX_DBG(DMX_MGT, printf("[FID=%d] MGT get section fail!! \r\n", u8FID));
                    break;
                }

                if(msAPI_DMX_CheckCRC32(au8Section) == FALSE)
                {
                    DMX_DBG(DMX_MGT, printf("[FID=%d] MGT get section check CRC error!! Case 1\n", u8FID));
                    enStatus = MSAPI_DMX_FILTER_STATUS_CRCINCORRECT;
                    break;
                }

                //MApp_Dmx_DumpSectionData( ((au8Section[1]<<8)|au8Section[2])&0x0fff );

                /* parsing table */
                #if 0
                if( au8Section[7] > 0 ) //last section num
                {
                DMX_DBG( printf( "Warning! No of MGT section > 1!!\r\n" ) );
                }
                #endif

                MApp_Dmx_MGT_Parse(&stMGT, au8Section);
                break;
            }

    #if (!ENABLE_NEW_DMX_INTERFACE)
        case MSAPI_DMX_FILTER_STATUS_CRCINCORRECT:
            {
            DMX_DBG(DMX_MGT, printf("[FID=%d] MGT get section check CRC error!! \r\n", u8FID));
                break;
            }

        case MSAPI_DMX_FILTER_STATUS_TIMEOUT:
            {
            DMX_DBG(DMX_MGT, printf("[FID=%d] MGT get section timeout!! \r\n", u8FID));
                break;
            }

        case MSAPI_DMX_FILTER_STATUS_OVERFLOW:
            {
            DMX_DBG(DMX_MGT, printf("[FID=%d] MGT get section overflow!! \r\n", u8FID));
                break;
            }
    #endif

        default:
            {
            DMX_DBG(DMX_MGT, printf("[FID=%d] MGT get section unknow error!! \r\n", u8FID));
                break;
            }
    }

    /*[02]finalize ==========================================================*/
    if(enStatus == MSAPI_DMX_FILTER_STATUS_SECAVAILABLE)
    {
        msAPI_DMX_CloseFilter(u8FID);
        u8MgtFid = MSAPI_DMX_INVALID_FLT_ID;
    }
    else
    {
        DMX_DBG(DMX_MGT, printf("Restart MGT filter>> [FID=%d]\r\n", u8FID));
        msAPI_DMX_RestartFilter(u8FID);
    }
}
/*****************************************************************************/
void MApp_Dmx_MGT_Monitor(void)
{
    MS_DMX_SECTIONMONITOR_PARA   stSectionMonitor;

    if(fEnableMgtMonitor || msAPI_Timer_DiffTimeFromNow(u32MonitorMgtTimer) > MGT_MONITOR_PERIOD)
    {
        if(u8MgtFid == MSAPI_DMX_INVALID_FLT_ID)
        {
            memset(stSectionMonitor.au8MaskByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);
            memset(stSectionMonitor.au8NotMatchByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);


            stSectionMonitor.u16PID = PID_BASE;
            stSectionMonitor.u32SectionFltType = MSAPI_DMX_FILTER_TYPE_SECTION_4K;
            stSectionMonitor.au8MatchByte[0] = TID_MGS; //table id
            stSectionMonitor.au8MaskByte[0] = 0xFF;
            //stSectionMonitor.au8MatchByte[3] = 0x00;  //subtable id
            //stSectionMonitor.au8MatchByte[4] = 0x00;
            //stSectionMonitor.au8MaskByte[3] = 0x00;
            //stSectionMonitor.au8MaskByte[4] = 0x00;
            stSectionMonitor.au8MatchByte[5] = 0x01;
            stSectionMonitor.au8MaskByte[5] = 0x01;
            //stSectionMonitor.au8MatchByte[6] = 0x00;  //section number
            //stSectionMonitor.au8MaskByte[6] = 0x00;
            stSectionMonitor.au8MatchByte[8]    = 0x00;    // protocol_version
            stSectionMonitor.au8MaskByte[8]    = 0xFF;
            stSectionMonitor.pfNotify = MApp_Dmx_MGT_Cb;
            stSectionMonitor.u16TimeoutMilliSec = MSAPI_DMX_TIMEOUT_INFINITE;
            stSectionMonitor.pu8FID = &u8MgtFid;
            stSectionMonitor.SectMode = DMX_SECT_MODE_ONESHOT|DMX_SECT_MODE_CRCCHK;

            if(msAPI_DMX_SectionMonitor(&stSectionMonitor, FALSE) == DMX_FILTER_STATUS_OK)
            {
                DMX_DBG(DMX_MGT, printf("monitoring MGT at Filter #%d \r\n", u8MgtFid));
                fEnableMgtMonitor = FALSE;
                u32MonitorMgtTimer = msAPI_Timer_GetTime0();
            }
            else
            {
                DMX_DBG(DMX_MGT, printf("monitor MGT fail!! \r\n"));
            }
        }
        else
        {
            DMX_DBG(DMX_MGT, printf("monitoring MGT at Filter #%d \r\n", u8MgtFid));
            //msAPI_DMX_RestartFilter(u8MgtFid);
            fEnableMgtMonitor = FALSE;
            u32MonitorMgtTimer = msAPI_Timer_GetTime0();
        }
    }
}
/*****************************************************************************/
static void MApp_Dmx_EAS_Parse(MS_EAS_ST *pstEas, U8 *pu8Section)
{
    U8 version_number;
    U16 u16Descriptors_length;
    U8 u8Idx,u8DiffCount;
    U8 u8EventCodeLength,u8NatActTextLength;
    U8 u8LocationCodeCount,u8ExceptionCount;

    /*[1]check error condition =============================================*/
    /*
    if( pstEas == NULL || pu8Section == NULL )
    {
       return;
    }
    */

    /*[2]check version change ==============================================*/
    DMX_DBG(DMX_EAS, printf("==============================================>>>>\r\n"));
    version_number = (pu8Section[5]>>1)&0x1f;
    if(version_number == pstEas->version_number) //same version
    {
        DMX_DBG(DMX_EAS, printf("Parse EAS>> same version number %d\n", pstEas->version_number));
        return;
    }

    /*[3]init variables ====================================================*/
    memset(pstEas, 0, sizeof(MS_EAS_ST));
    pstEas->version_number = version_number;

    bEASGotData = TRUE;

    /*[4]move to first item position =======================================*/
    pu8Section += 9;

    /*[5]get items =========================================================*/
    pstEas->u16EAS_EventID = pu8Section[0];
    pstEas->u16EAS_EventID <<= 8;
    pstEas->u16EAS_EventID |= pu8Section[1];

    pstEas->au8EAS_OriginatorCode[0] = pu8Section[2];
    pstEas->au8EAS_OriginatorCode[1] = pu8Section[3];
    pstEas->au8EAS_OriginatorCode[2] = pu8Section[4];

    // move to EAS event code length position
    pu8Section += 5;

    u8EventCodeLength = pu8Section[0];
    if (u8EventCodeLength > MAX_LENGTH_OF_EVENT_CODE)
    {
        DMX_DBG(DMX_EAS, printf("[Warning!!] u8EventCodeLength > MAX_LENGTH_OF_EVENT_CODE !!\n"));
        u8DiffCount = u8EventCodeLength - MAX_LENGTH_OF_EVENT_CODE;
        u8EventCodeLength = MAX_LENGTH_OF_EVENT_CODE;
    }
    else
    {
        u8DiffCount = 0;
    }
    // move to EAS event code position
    pu8Section++;

    for (u8Idx = 0; u8Idx < u8EventCodeLength; u8Idx++)
    {
        pstEas->au8EAS_EventCode[u8Idx] = pu8Section[u8Idx];
    }

    // move to nature of activation text length position and overflow handle
    pu8Section += (u8EventCodeLength + u8DiffCount);

    u8NatActTextLength = pu8Section[0];

    // move to nature of activaction text position
    pu8Section ++;

    if(u8NatActTextLength > 0)
    {
        MApp_Dmx_Parse_MSS(pstEas->au8NatActText,pu8Section,sizeof(U8)*MAX_LENGTH_OF_NAT_ACT_TEXT, DISABLE);
    }

    // move to alert message time remaining position
    pu8Section += u8NatActTextLength;

    pstEas->u8AlertTimeRemain = pu8Section[0];
    pstEas->u32EventStartTime = pu8Section[1];
    pstEas->u32EventStartTime <<= 8;
    pstEas->u32EventStartTime |= pu8Section[2];
    pstEas->u32EventStartTime <<= 8;
    pstEas->u32EventStartTime |= pu8Section[3];
    pstEas->u32EventStartTime <<= 8;
    pstEas->u32EventStartTime |= pu8Section[4];
    pstEas->u16EventDuration = pu8Section[5];
    pstEas->u16EventDuration <<= 8;
    pstEas->u16EventDuration |= pu8Section[6];
    pstEas->u8AlertPriority = (pu8Section[8] & 0x0F);
    pstEas->u16DetailsOOB_SrcID = pu8Section[9];
    pstEas->u16DetailsOOB_SrcID <<= 8;
    pstEas->u16DetailsOOB_SrcID |= pu8Section[10];
    pstEas->u16DetailsMajorNum = (pu8Section[11] & 0x03);
    pstEas->u16DetailsMajorNum <<= 8;
    pstEas->u16DetailsMajorNum |= pu8Section[12];
    pstEas->u16DetailsMinorNum = (pu8Section[13] & 0x03);
    pstEas->u16DetailsMinorNum <<= 8;
    pstEas->u16DetailsMinorNum |= pu8Section[14];
    pstEas->u16AudioOOB_SrcID = pu8Section[15];
    pstEas->u16AudioOOB_SrcID <<= 8;
    pstEas->u16AudioOOB_SrcID |= pu8Section[16];

    pstEas->u16AlertTextLength = pu8Section[17];
    pstEas->u16AlertTextLength <<= 8;
    pstEas->u16AlertTextLength |= pu8Section[18];

    // move to alert text position
    pu8Section += 19;

    if(pstEas->u16AlertTextLength > 0)
    {
        MApp_Dmx_Parse_MSS(pstEas->au8AlertText,pu8Section,sizeof(U8)*MAX_LENGTH_OF_ALERT_TEXT, DISABLE);
    }

    // move to location code count position
    pu8Section += pstEas->u16AlertTextLength;

    u8LocationCodeCount = pu8Section[0];
    if (u8LocationCodeCount > MAX_COUNT_OF_LOCATION_CODE)
    {
        DMX_DBG(DMX_EAS, printf("[Warning!!] u8LocationCodeCount > MAX_COUNT_OF_LOCATION_CODE !!\n"));
        u8DiffCount = u8LocationCodeCount - MAX_COUNT_OF_LOCATION_CODE;
        u8LocationCodeCount = MAX_COUNT_OF_LOCATION_CODE;
    }
    else
    {
        u8DiffCount = 0;
    }

    pu8Section++;

    for(u8Idx = 0; u8Idx < u8LocationCodeCount; u8Idx++)
    {
        pstEas->astLoctionCode[u8Idx].u8StateCode = pu8Section[0];
        pstEas->astLoctionCode[u8Idx].u8CountySubdivision = ((pu8Section[1] & 0xF0) >> 4);
        pstEas->astLoctionCode[u8Idx].u16CountyCode = (pu8Section[1] & 0x03);
        pstEas->astLoctionCode[u8Idx].u16CountyCode <<= 8;
        pstEas->astLoctionCode[u8Idx].u16CountyCode |= pu8Section[2];
        pu8Section += 3;
    }

    // overflow handle
    pu8Section += (u8DiffCount * 3);

    u8ExceptionCount = pu8Section[0];
    if (u8LocationCodeCount > MAX_COUNT_OF_EXCEPTION)
    {
        DMX_DBG(DMX_EAS, printf("[Warning!!] u8LocationCodeCount > MAX_COUNT_OF_EXCEPTION !!\n"));
        u8DiffCount = u8ExceptionCount - MAX_COUNT_OF_EXCEPTION;
        u8ExceptionCount = MAX_COUNT_OF_EXCEPTION;
    }
    else
    {
        u8DiffCount = 0;
    }

    pu8Section++;

    pstEas->u8ExceptionCount = u8ExceptionCount;

    for(u8Idx = 0; u8Idx < u8ExceptionCount; u8Idx++)
    {
        pstEas->astException[u8Idx].bInBandRef = ((pu8Section[0] & 0x80) >> 7);
        if (pstEas->astException[u8Idx].bInBandRef)
        {
            pstEas->astException[u8Idx].u16ExcMajorNum = (pu8Section[1] & 0x03);
            pstEas->astException[u8Idx].u16ExcMajorNum <<= 8;
            pstEas->astException[u8Idx].u16ExcMajorNum |= pu8Section[2];
            pstEas->astException[u8Idx].u16ExcMinorNum = (pu8Section[3] & 0x03);
            pstEas->astException[u8Idx].u16ExcMinorNum <<= 8;
            pstEas->astException[u8Idx].u16ExcMinorNum |= pu8Section[4];
        }
        else
        {
            pstEas->astException[u8Idx].u16ExcOOB_SrcID = pu8Section[3];
            pstEas->astException[u8Idx].u16ExcOOB_SrcID <<= 8;
            pstEas->astException[u8Idx].u16ExcOOB_SrcID |= pu8Section[4];
        }
        pu8Section += 5;
    }

    // overflow handle
    pu8Section += (u8DiffCount * 5);

    u16Descriptors_length = (pu8Section[0] & 0x03);
    u16Descriptors_length <<= 8;
    u16Descriptors_length |= pu8Section[1];


    DMX_DBG(DMX_EAS, printf("==================[EAS info]==================>>>>\r\n"));
    DMX_DBG(DMX_EAS, printf("Sequence number = %d\n",pstEas->version_number));
    DMX_DBG(DMX_EAS, printf("EAS event ID = 0x%x\n",pstEas->u16EAS_EventID));
    DMX_DBG(DMX_EAS, printf("EAS originator code = %c%c%c\n",pstEas->au8EAS_OriginatorCode[0],pstEas->au8EAS_OriginatorCode[1],pstEas->au8EAS_OriginatorCode[2]));
    DMX_DBG(DMX_EAS, printf("EAS event code = "));
    for (u8Idx = 0; u8Idx < u8EventCodeLength; u8Idx++)
    {
        DMX_DBG(DMX_EAS, printf("%c",pstEas->au8EAS_EventCode[u8Idx]));
    }
    DMX_DBG(DMX_EAS, printf("\n"));
    DMX_DBG(DMX_EAS, printf("Activation text length = %d\n",u8NatActTextLength));
    DMX_DBG(DMX_EAS, printf("Nature of activation text = %s\n",&pstEas->au8NatActText[2]));
    DMX_DBG(DMX_EAS, printf("Alert time remaining = %d(sec)\n",pstEas->u8AlertTimeRemain));
    DMX_DBG(DMX_EAS, printf("Event start time = 0x%lx\n",pstEas->u32EventStartTime));
    DMX_DBG(DMX_EAS, printf("Event duration = 0x%x\n",pstEas->u16EventDuration));
    DMX_DBG(DMX_EAS, printf("Alert priority = %d\n",pstEas->u8AlertPriority));
    DMX_DBG(DMX_EAS, printf("Details OOB source ID = 0x%x\n",pstEas->u16DetailsOOB_SrcID));
    DMX_DBG(DMX_EAS, printf("Details major channel Num = %d\n",pstEas->u16DetailsMajorNum));
    DMX_DBG(DMX_EAS, printf("Details minor channel Num = %d\n",pstEas->u16DetailsMinorNum));
    DMX_DBG(DMX_EAS, printf("Audio OOB source ID = 0x%x\n",pstEas->u16AudioOOB_SrcID));
    DMX_DBG(DMX_EAS, printf("Alert text length = %d\n",pstEas->u16AlertTextLength));
    DMX_DBG(DMX_EAS, printf("Alert text = %s\n",&pstEas->au8AlertText[2]));

    for(u8Idx = 0; u8Idx < u8LocationCodeCount; u8Idx++)
    {
        DMX_DBG(DMX_EAS, printf("Location code [%d]:\n",u8Idx));
        DMX_DBG(DMX_EAS, printf("   -State code = %d \n",pstEas->astLoctionCode[u8Idx].u8StateCode));
        DMX_DBG(DMX_EAS, printf("   -County subdivision = %d \n",pstEas->astLoctionCode[u8Idx].u8CountySubdivision));
        DMX_DBG(DMX_EAS, printf("   -County code = %d \n",pstEas->astLoctionCode[u8Idx].u16CountyCode));
    }
    for(u8Idx = 0; u8Idx < u8ExceptionCount; u8Idx++)
    {
        DMX_DBG(DMX_EAS, printf("Exception [%d]:\n",u8Idx));
        DMX_DBG(DMX_EAS, printf("   -In band Ref. = %d\n",pstEas->astException[u8Idx].bInBandRef));
        DMX_DBG(DMX_EAS, printf("   -Exception major channel Num = %d\n",pstEas->astException[u8Idx].u16ExcMajorNum));
        DMX_DBG(DMX_EAS, printf("   -Exception minor channel Num = %d\n",pstEas->astException[u8Idx].u16ExcMinorNum));
        DMX_DBG(DMX_EAS, printf("   -Exception OOB source ID = 0x%x\n",pstEas->astException[u8Idx].u16ExcOOB_SrcID));
    }


    DMX_DBG(DMX_EAS, printf("Descriptor length = 0x%x\n",u16Descriptors_length));
    DMX_DBG(DMX_EAS, printf("==================[EAS  END]==================>>>>\r\n"));
}
/*****************************************************************************/
void MApp_Dmx_EAS_Process(void)
{
    if (bEASGotData == TRUE)
    {
        U8 loop_i;
        MS_VIRTUAL_CHANNEL *pstCurVirtualCh;
        pstCurVirtualCh = MApp_ChanProc_GetChannelPointer(VIR_CH_IDX(MApp_ChanProc_GetCurMainListProgIndex()));
        // check if current service in exception list
        for (loop_i = 0; loop_i < stEAS.u8ExceptionCount; loop_i++)
        {
            if((pstCurVirtualCh->stVirtualChNum.major_num == stEAS.astException[loop_i].u16ExcMajorNum)
                && (pstCurVirtualCh->stVirtualChNum.minor_num == stEAS.astException[loop_i].u16ExcMinorNum))
            {
                bEASGotData = FALSE;
                printf("Current channel is in exception list! \n");
                return;
            }
        }

        // check if priority high enough to process
        if (stEAS.u8AlertPriority == 0)
        {
            bEASGotData = FALSE;
            printf("This EAS priority is ZERO! \n");
            return;
        }

        // Current have NOT support "event start time != 0" yet.
        if (stEAS.u32EventStartTime != 0)
        {
            bEASGotData = FALSE;
            printf("Current event start time is NOT immediate! \n");
            return;
        }

        // check if detail channel available
        if (stEAS.u16DetailsMajorNum > 0)
        {
            if (stEAS.u8AlertTimeRemain > 0)
            {
                //4 FIX ME!!
                if (stEAS.u8AlertTimeRemain > EAS_MIN_DURATION_TIME)
                {
                    // update alert message time remaining
                    u8EAStimeRemaining = stEAS.u8AlertTimeRemain;
                }
                else
                {
                    if ((stEAS.au8EAS_EventCode[0] == 'E')
                        && (stEAS.au8EAS_EventCode[1] == 'A')
                        && (stEAS.au8EAS_EventCode[2] == 'T')) //EAS Termination event should not use min duration time
                    {
                        u8EAStimeRemaining = stEAS.u8AlertTimeRemain;
                    }
                    else
                    {
                        u8EAStimeRemaining = EAS_MIN_DURATION_TIME;
                    }
                }
                bIsZeroRemainTime = FALSE;
            }
            else
            {
                bIsZeroRemainTime = TRUE;
            }

            u32EasProcessTimer = msAPI_Timer_GetTime0();
            bIsEASinProgress = TRUE;

        }

        //check if EAS text available
        if (stEAS.u16AlertTextLength > 1)
        {
            u16EATtextLength = ((stEAS.au8AlertText[0] << 8) | (stEAS.au8AlertText[1]));
            bIsEASinProgress = TRUE;
        }
        else
        {
            u16EATtextLength = 0;
        }
        // this EAS processing has done
        bEASGotData = FALSE;

    }
}
/*****************************************************************************/
void MApp_Dmx_EAS_Timer(void)
{
    if (bIsEASinProgress == TRUE)
    {
        if ((!bIsZeroRemainTime)&&
            (msAPI_Timer_DiffTimeFromNow(u32EasProcessTimer) > (U32)u8EAStimeRemaining*1000))
        {
            /* re-acquire original channel */
            bIsEASinProgress = FALSE;
        }
    }

}
/*****************************************************************************/
BOOL MApp_Dmx_EAS_GetStatus(MS_EAS_INFO *pstEAS_info)
{
    pstEAS_info->u16MajorNum = stEAS.u16DetailsMajorNum;
    pstEAS_info->u16MinorNum = stEAS.u16DetailsMinorNum;
    pstEAS_info->u16AlertTextLength = u16EATtextLength;
    if (u16EATtextLength > 0)
    {
        memcpy(pstEAS_info->au8AlertText,&stEAS.au8AlertText[2],MAX_LENGTH_OF_ALERT_TEXT-2);
    }
    else
    {
        memset(pstEAS_info->au8AlertText,'\0',MAX_LENGTH_OF_ALERT_TEXT);
    }
    return bIsEASinProgress;
}
/*****************************************************************************/
void MApp_Dmx_EAS_Cb(U8 u8FID, DMX_EVENT enEvent)
{
    U32 u32ActualSize,u32RmnSize;
    MSAPI_DMX_FILTER_STATUS enStatus;
    enStatus=(MSAPI_DMX_FILTER_STATUS)enEvent;

    /*[1]check enStatus ====================================================*/
    DMX_DBG(DMX_EAS, printf("EAS Callback: u8FID = %d ; enStatus = %d\n", u8FID, (U8)enStatus));

    switch(enStatus)
    {
        case MSAPI_DMX_FILTER_STATUS_SECAVAILABLE:
            {
                /* get section data */
                if(MApi_DMX_CopyData(u8FID, au8Section, MSAPI_DMX_SECTION_4K,&u32ActualSize,&u32RmnSize,NULL) == DMX_FILTER_STATUS_ERROR)
                {
                    DMX_DBG(DMX_EAS, printf("[FID=%d] EAS get section fail!! \r\n", u8FID));
                    break;
                }

                /* parsing table */
                MApp_Dmx_EAS_Parse(&stEAS, au8Section);

                /* process si data */
                MApp_Dmx_EAS_Process();
                break;
            }

    #if (!ENABLE_NEW_DMX_INTERFACE)
        case MSAPI_DMX_FILTER_STATUS_CRCINCORRECT:
            {
                DMX_DBG(DMX_EAS, printf("[FID=%d] EAS get section check CRC error!! \r\n", u8FID));
                break;
            }

        case MSAPI_DMX_FILTER_STATUS_TIMEOUT:
            {
                DMX_DBG(DMX_EAS, printf("[FID=%d] EAS get section timeout!! \r\n", u8FID));
                break;
            }

        case MSAPI_DMX_FILTER_STATUS_OVERFLOW:
            {
                DMX_DBG(DMX_EAS, printf("[FID=%d] EAS get section overflow!! \r\n", u8FID));
                break;
            }
    #endif

        default:
            {
                DMX_DBG(DMX_EAS, printf("[FID=%d] EAS get section unknow error!! \r\n", u8FID));
                break;
            }
    }

    /*[02]finalize ==========================================================*/
    if(enStatus == MSAPI_DMX_FILTER_STATUS_SECAVAILABLE)
    {
        msAPI_DMX_CloseFilter(u8FID);
        u8EasFid = MSAPI_DMX_INVALID_FLT_ID;
        fEnableEasMonitor = TRUE;
    }
    else
    {
        DMX_DBG(DMX_EAS, printf("Restart EAS filter>> [FID=%d]\r\n", u8FID));
        msAPI_DMX_RestartFilter(u8FID);
    }
}
/*****************************************************************************/
void MApp_Dmx_EAS_Monitor(void)
{
    MS_DMX_SECTIONMONITOR_PARA   stSectionMonitor;

    if(fEnableEasMonitor || msAPI_Timer_DiffTimeFromNow(u32MonitorEasTimer) > EAS_MONITOR_PERIOD)
    {
        if(u8EasFid == MSAPI_DMX_INVALID_FLT_ID)
        {
            memset(stSectionMonitor.au8MaskByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);
            memset(stSectionMonitor.au8NotMatchByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);


            stSectionMonitor.u16PID = PID_BASE;
            stSectionMonitor.u32SectionFltType = MSAPI_DMX_FILTER_TYPE_SECTION_4K;
            stSectionMonitor.au8MatchByte[0] = TID_EAS; //table id
            stSectionMonitor.au8MaskByte[0] = 0xFF;

            stSectionMonitor.au8MatchByte[5] = 0x01;
            stSectionMonitor.au8MaskByte[5] = 0x01;

            stSectionMonitor.au8MatchByte[8]    = 0x00;    // protocol_version
            stSectionMonitor.au8MaskByte[8]    = 0xFF;
            stSectionMonitor.pfNotify = MApp_Dmx_EAS_Cb;
            stSectionMonitor.u16TimeoutMilliSec = MSAPI_DMX_TIMEOUT_INFINITE;
            stSectionMonitor.pu8FID = &u8EasFid;
            stSectionMonitor.SectMode = DMX_SECT_MODE_ONESHOT|DMX_SECT_MODE_CRCCHK;

            if(msAPI_DMX_SectionMonitor(&stSectionMonitor, FALSE) == DMX_FILTER_STATUS_OK)
            {
                DMX_DBG(DMX_EAS, printf("Create a new monitoring EAS at Filter #%d \r\n", u8EasFid));
                fEnableEasMonitor = FALSE;
                u32MonitorEasTimer = msAPI_Timer_GetTime0();
            }
            else
            {
                DMX_DBG(DMX_EAS, printf("monitor EAS fail!! \r\n"));
            }
        }
        else
        {
            DMX_DBG(DMX_EAS, printf("monitoring EAS at Filter #%d \r\n", u8EasFid));
            //msAPI_DMX_RestartFilter(u8EasFid);
            fEnableEasMonitor = FALSE;
            u32MonitorEasTimer = msAPI_Timer_GetTime0();
        }
    }

    MApp_Dmx_EAS_Timer();

}
/*****************************************************************************/
void MApp_ATSC_PrintServiceName(U8* pu8ServiceName )
{
    U8 i;
    U16 u16Data;

    printf(" ServiceName=[");

    for( i = 0; i < MAX_LENGTH_OF_SERVICE_NAME; i += 2 )
    {
        u16Data = (pu8ServiceName[i]<<8) + pu8ServiceName[i+1];
        if( u16Data == 0 )
        {
            //printf("(%x,%X)", pu8ServiceName[i],pu8ServiceName[i+1]);
            break;
        }
        if( u16Data < 0x80 )
            putchar(u16Data);
        else
            printf("(%x)", u16Data);
    }

#if 0
    U8 u8Data;
    printf("<");
    for( i = 0; i < 6; ++ i )
    {
        u8Data = pu8ServiceName[i];
        printf(" %x", u8Data);
    }
    printf(" >");
#endif

    printf("] ");
}

static void MApp_Dmx_VCT_Parse(MS_VIRTUAL_CHANNEL *pastVirtualCh_func,U8 *pu8Section)
{
    U8 u8NumOfChsInSection,u8VctVersion,u8Loop_i,u8Loop_j;
    U8 *pu8LoopPosition;
    U16 u16ProgramNumner;
    U16 u16TotalDescriptorLength;
    U8 u8ServiceType;
#if PARSE_SLD_IN_VCT
    U8 *pu8Descriptor;
    U8 u8NumOfElements,*pu8Data,u8Loop_k,u8Loop_l;
    U16 u16EleStreamPid;
#else
    #if (KOR_HIDE_3D_CHANNEL)
    U8 *pu8Descriptor;
#endif
#endif



    /*[1]check error condition =============================================*/
    /*
    if(pstPhysicalCh == NULL || pastVirtualCh_func == NULL || pu8Section == NULL)
    {
       return;
    }
    */

    /*[2]goto first loop position ==========================================*/
    DMX_DBG(DMX_VCT, printf("<<<<==============================================\r\n"));
    DMX_DBG(DMX_VCT, printf("VCT section:\r\n"));
    u16ActualTSid = ((U16)pu8Section[3] << 8) | ((U16) pu8Section[4]);
    u8NumOfChsInSection = pu8Section[9];
    DMX_DBG(DMX_VCT, printf("u8NumOfChsInSection = %d\n", u8NumOfChsInSection));

    pu8LoopPosition = MApp_Dmx_FindFirstLoop(pu8Section, EN_TVCT);
    DMX_DBG(DMX_VCT, printf("first loop pos. = %p\n", pu8LoopPosition));

    u8VctVersion = (pu8Section[5] & 0x3f) >> 1;
	U8 u8SectionNumber = pu8Section[6];

    /* find coressponded service with PAT */

    pastRfCh.u8VctVersion = u8VctVersion;

    /*[3]get service information ===========================================*/
    for(u8Loop_i = 0; u8Loop_i < u8NumOfChsInSection; u8Loop_i++)
    {
        DMX_DBG(DMX_VCT, printf("---------------------------------------------------\r\n"));

        /* total descriptor length */
        u16TotalDescriptorLength = ((pu8LoopPosition[30] & 0x03) << 8) | pu8LoopPosition[31];
        DMX_DBG(DMX_VCT, printf("u16TotalDescriptorLength = %u\n", u16TotalDescriptorLength));

        /* parse actual TSID only */
        DMX_DBG(DMX_VCT, printf("u16ChTSID = %u\n", (pu8LoopPosition[22] << 8 | pu8LoopPosition[23]) ));
        if((pu8LoopPosition[22] << 8 | pu8LoopPosition[23]) == u16ActualTSid)
        {
            /* program number */
            u16ProgramNumner = (pu8LoopPosition[24] << 8) | pu8LoopPosition[25];
            DMX_DBG(DMX_VCT, printf("u16ProgramNumner = %u\n", u16ProgramNumner));
            //parse service type
            u8ServiceType = pu8LoopPosition[27] & 0x3f;
            DMX_DBG(DMX_VCT, printf("u8ServiceType = %u\n", u8ServiceType));
            /* skip inactive channels (program number = 0) and analog service (program number = 0xFFFF) */
            if(u16ProgramNumner != 0 && u16ProgramNumner != 0xFFFF)
            {
                /* find coressponded service with PAT */
                for(u8Loop_j = 0; u8Loop_j < u8TotalTableItem; u8Loop_j++)
                {
                    if(pastVirtualCh_func[u8Loop_j].u16ProgramNumber == u16ProgramNumner)
                    {
                        break; //found same program
	            }
                } // end of for

                /* add additional service */
                if(u8Loop_j==u8TotalTableItem && u8TotalTableItem<MAX_VC_PER_PHYSICAL)
                {
                    pastRfCh.u8PatVersion = u8Version;
                    pastRfCh.u8VctVersion = u8VctVersion;
                    //mantis  1076964: PAT tsid is different from VCT tsid....we add a new vairable which names "u16ChannelTsid" for storing it.
                    //pastRfCh.u16TsId = u16ActualTSid;

                    pastVirtualCh_func[u8Loop_j].u16ProgramNumber = u16ProgramNumner;
                    pastVirtualCh_func[u8Loop_j].bChannelFromVCT = 1;

                    u8NumOfVCTItem++;
                    u8TotalTableItem++;
                }

                /* store service information */
                if(u8Loop_j < MAX_VC_PER_PHYSICAL)
                {
                    switch(u8ServiceType)
                    {
                        case 0:
                            pastVirtualCh_func[u8Loop_j].u8ServiceType = EN_PSIP_SERVICE_INVALID;
                            break;
                        case 1:
                            pastVirtualCh_func[u8Loop_j].u8ServiceType = EN_PSIP_SERVICE_ANALOG;
                            break;
                        case 2:
                            pastVirtualCh_func[u8Loop_j].u8ServiceType = EN_PSIP_SERVICE_DTV;
                            break;
                        case 3:
                            pastVirtualCh_func[u8Loop_j].u8ServiceType = EN_PSIP_SERVICE_AUDIO;
                            break;
                        case 4:
                            pastVirtualCh_func[u8Loop_j].u8ServiceType = EN_PSIP_SERVICE_DATA;
                            break;
                        default:
                            pastVirtualCh_func[u8Loop_j].u8ServiceType = EN_PSIP_SERVICE_ERROR;
                            break;
                    }

                    //init flag of audio language number
                    #if PARSE_SLD_IN_VCT
                    u16AudLangNumflag=0;
                    #endif

                    pastVirtualCh_func[u8Loop_j].stVirtualChNum.u16ChannelTsid = u16ActualTSid;
                    pastVirtualCh_func[u8Loop_j].stVirtualChNum.u8VCTsctionNumber = u8SectionNumber;
                    printf("ChannelTsid = %d, section number = %d\n", pastVirtualCh_func[u8Loop_j].stVirtualChNum.u16ChannelTsid, pastVirtualCh_func[u8Loop_j].stVirtualChNum.u8VCTsctionNumber);
                    /* short name */
                    MApp_Dmx_GetServiceName(pastVirtualCh_func+u8Loop_j, pu8LoopPosition, MAX_LENGTH_OF_SERVICE_NAME, MAX_LENGTH_OF_SERVICE_NAME-1);
                   //#if (ENABLE_TVSCAN_DEBUGINFO)
                     //printf("short name = %s\n", pastVirtualCh_func[u8Loop_j].acServiceName);
                    {
                        printf("short name =>  ");
                        MApp_ATSC_PrintServiceName(pastVirtualCh_func[u8Loop_j].acServiceName);
                    }

                   //#endif
                    /* major numner and minor number */
                    pastVirtualCh_func[u8Loop_j].stVirtualChNum.major_num = ((pu8LoopPosition[14] & 0x0f) << 6) | (pu8LoopPosition[15] >> 2);
                    pastVirtualCh_func[u8Loop_j].stVirtualChNum.minor_num = ((pu8LoopPosition[15] & 0x03) << 8) | pu8LoopPosition[16];
                   #if (ENABLE_TVSCAN_DEBUGINFO)
                    DMX_DBG(DMX_VCT, printf("major-minor = %u-%u\n", pastVirtualCh_func[u8Loop_j].stVirtualChNum.major_num, pastVirtualCh_func[u8Loop_j].stVirtualChNum.minor_num));
                   #endif
                    /* source id*/
                    pastVirtualCh_func[u8Loop_j].u16SourceId = pu8LoopPosition[28] << 8 | pu8LoopPosition[29];
#if (ENABLE_ATSC_EPG_DB_2016)
                    stEpgDBInfo.au16SrcID[u8Loop_j]= pastVirtualCh_func[u8Loop_j].u16SourceId;
#endif

                    DMX_DBG(DMX_VCT, printf("source id = %u\n", pastVirtualCh_func[u8Loop_j].u16SourceId));
                    pastVirtualCh_func[u8Loop_j].stVirtualChNum.u16HiddenFlag =  (pu8LoopPosition[26] >> 4) &(0x1);
                    pastVirtualCh_func[u8Loop_j].stVirtualChNum.u16HideGuide =  (pu8LoopPosition[26] >> 1) &(0x1);

#if KOR_HIDE_3D_CHANNEL
                    pu8Descriptor = MApp_Dmx_FindDescriptorTag(pu8LoopPosition + 32, TAG_SSD_ATSC, u16TotalDescriptorLength);
                    if(pu8Descriptor!= NULL)
                    {
                        pastVirtualCh_func[u8Loop_j].stVirtualChNum.u16fIs3DChannel = 1;
                        //printf("Get StereoScopicProgramInfo Descriptor!!!\n");
                    }
                    else
                    {
                        pastVirtualCh_func[u8Loop_j].stVirtualChNum.u16fIs3DChannel = 0;
                    }
#endif

#if PARSE_SLD_IN_VCT
                    /* get service location descriptor */
                    pu8Descriptor = MApp_Dmx_FindDescriptorTag(pu8LoopPosition + 32, TAG_SLD_ATSC, u16TotalDescriptorLength);
                    if(pu8Descriptor != NULL)
                    {
                        /* get PCR Pid */
                        if(pastVirtualCh_func[u8Loop_j].u16PcrPid ==0)
                            pastVirtualCh_func[u8Loop_j].u16PcrPid = ((pu8Descriptor[2] & 0x1f) << 8) | pu8Descriptor[3]; //PCR pid
                        DMX_DBG(DMX_VCT, printf("PcrPid = 0x%04x\n", (U16)pastVirtualCh_func[u8Loop_j].u16PcrPid));

                        u8NumOfElements = pu8Descriptor[4];
                        pu8Data = pu8Descriptor + 5;
                        for(u8Loop_k = 0; u8Loop_k < u8NumOfElements; u8Loop_k++)
                        {
                            switch(pu8Data[0]) //stream type
                            {
                                /* [5-1]video */
                                case ST_MPEG1_VID:
                                    //mpeg 1 video
                                case ST_MPEG2_VID:
                                case ST_OP_MPEG2_VID:
                                    //mpeg 2 video
                                case ST_AVCH264_VID:
                                #if (ENABLE_H265)
                                case ST_HEVC_H265_VID:
                                #endif
                                    //AVC H.264 video
                                {
                                    /* video pid */
                                    if(!pastVirtualCh_func[u8Loop_j].u16VideoPid)
                                    {
                                        pastVirtualCh_func[u8Loop_j].u16VideoPid = ((pu8Data[1] & 0x1f) << 8) | pu8Data[2];
                                        DMX_DBG(DMX_VCT, printf("VID_Pid = 0x%04x \r\n", (U16)pastVirtualCh_func[u8Loop_j].u16VideoPid));

                                        /* video stream type */
                                        CONVERT_VIDEO_TYPE(pu8Data[0],pastVirtualCh_func->stVirtualChNum.u8VideoStreamType);
                                        DMX_DBG(DMX_VCT, printf("[VCT] VID stream type = 0x%x \r\n", (U16)pastVirtualCh_func->stVirtualChNum.u8VideoStreamType));
                                    }
                                    else
                                    {
                                        DMX_DBG(DMX_VCT, printf("VID_Pid = 0x%04x \r\n", (U16)pastVirtualCh_func[u8Loop_j].u16VideoPid));
                                    }
                                    DMX_DBG(DMX_VCT, printf("[VCT] VID stream type = 0x%x \r\n", (U16)pastVirtualCh_func->stVirtualChNum.u8VideoStreamType));
                                }
                                break;

                                /* [5-2]audio */
#if(ENABLE_DTV_MPEG_AUDIO)
                                case ST_MPEG1_AUD:
                                    //mpeg 1 audio
                                case ST_MPEG2_AUD:
                                    //mpeg 2 audio
#endif
                                case ST_AC3_AUD:
#if (ENABLE_AC3P_AUDIO)
                                case ST_AC3P_AUD:
#endif
                                case ST_AAC_AUD:
                                case ST_HEAAC_AUD:
                                    //AC-3 audio
                                {
                                    u16EleStreamPid = (pu8Data[1] & 0x1f) << 8 | pu8Data[2];
                                    for(u8Loop_l=0; u8Loop_l<pastVirtualCh_func[u8Loop_j].u8AudLangNum; u8Loop_l++)
                                    {
                                        if(u16EleStreamPid == pastVirtualCh_func[u8Loop_j].astSoundTrack[u8Loop_l].u16AudioPid)
                                        {
                                            if (!GETBIT(u16AudLangNumflag, u8Loop_l))
                                            {
                                                break; //found same audio pid
                                            }
                                        }
                                    }

                                    if(u8Loop_l < MAX_AUD_LANG_NUM_ATSC)
                                    {
                                        if(u8Loop_l == pastVirtualCh_func[u8Loop_j].u8AudLangNum) //found new audio pid
                                        {

                                            /* audio stream type */
                                            CONVERT_AUDIO_TYPE(pu8Data[0],pastVirtualCh_func[u8Loop_j].astSoundTrack[u8Loop_l].u16AudStreamType);
                                            DMX_DBG(DMX_VCT, printf("[VCT] AUDIO stream type = 0x%x \r\n", (U16)pastVirtualCh_func[u8Loop_j].astSoundTrack[u8Loop_l].u16AudStreamType));

                                            pastVirtualCh_func[u8Loop_j].astSoundTrack[u8Loop_l].u16AudioPid = u16EleStreamPid;
                                            DMX_DBG(DMX_VCT, printf("[VCT] AUDIO_Pid = 0x%04x \r\n", (U16)pastVirtualCh_func[u8Loop_j].astSoundTrack[u8Loop_l].u16AudioPid));

                                            pastVirtualCh_func[u8Loop_j].u8AudLangNum++;
                                            pastVirtualCh_func[u8Loop_j].astSoundTrack[u8Loop_l].u8AudPidInPMT = FALSE;
                                        }
                                        if(pastVirtualCh_func[u8Loop_j].astSoundTrack[u8Loop_l].u16IsAudLangGetinPMT == 0)
                                        {
                                            pastVirtualCh_func[u8Loop_j].astSoundTrack[u8Loop_l].u8AudLangIdx = MApp_Dmx_GetISO639LangCode(&pu8Data[3]);
                                        }

                                        SETBIT(u16AudLangNumflag, u8Loop_l);
                                        #if (ENABLE_TVSCAN_DEBUGINFO)
                                         printf("Lang %d = %c%c%c, Idx = %d, %x\n", u8Loop_l, pu8Data[3], pu8Data[4], pu8Data[5], (U8)pastVirtualCh_func[u8Loop_j].astSoundTrack[u8Loop_l].u8AudLangIdx, u16AudLangNumflag);
                                        #endif
                                    }
                                }
                                break;

                                /*[5-3]private data ============================================*/
                                #if 0
                                 case ST_PRIVATE_DATA:
                                 {
                                     break;
                                 }
                                #endif

                                /*[5-4]otsher ===================================================*/
                                default:
                                {
                                    // default case
                                }
                                break;
                            } //~switch(pu8Data[0]) //stream type
                            pu8Data += 6; //jump to next element
                        } //~for(u8Loop_k = 0; u8Loop_k < u8NumOfElements; u8Loop_k++)
                    } //~if(pu8Descriptor != NULL)
#endif
                } //~if(u8Loop_j < MAX_VC_PER_PHYSICAL)
            } //~if(u16ProgramNumner != 0 && u16ProgramNumner != 0xFFFF)
        } //~if((pu8LoopPosition[22] << 8 | pu8LoopPosition[23]) == u16ActualTSid)
        /* goto next loop position */
        pu8LoopPosition = MApp_Dmx_FindNextLoop(pu8Section, pu8LoopPosition, u16TotalDescriptorLength, EN_TVCT);

        DMX_DBG(DMX_VCT, printf("---------------------------------------------------\r\n"));
    }

    DMX_DBG(DMX_VCT, printf("<<<<==============================================\r\n"));
}
/*****************************************************************************/
static void MApp_Dmx_VCT_CheckVersionChange(U8 *pu8Section)
{
    U8 buffIdx;
    //
    buffIdx = MApp_ChanProc_GetCurIdxMap2ChanBufIdx(MApp_ChanProc_GetCurProgIndex());
    pstVirtualCh = MApp_ChanProc_GetCurChannelPointer();

    // Get cur RF CH
    MS_RF_CHANNEL_new stCurRfCh;
    memset(&stCurRfCh, 0x00, sizeof(MS_RF_CHANNEL_new));
    MApp_ChanProc_GetRfChannelPointer(pstVirtualCh, &stCurRfCh);


    u8Version = (pu8Section[5] & 0x3f) >> 1;
#if (CHECK_TALBEFIELDS_BEFORE_VERCHANGE)
    U8 u8IsVCTFieldChange = 0;
#endif

    if (u8Version != stCurRfCh.u8VctVersion)
    {
//        DMX_VERSION_DBG(DMX_VCTCHECK_VERSION, printf("******** VCT_CheckVersionChange: %bx -> %bx\r\n", pstVirtualCh->u8PmtVersion, u8Version));
    //if //check other vct fields
#if (CHECK_TALBEFIELDS_BEFORE_VERCHANGE)
        {
            U8 u8NumOfChsInSection,u8Loop_i;
            U8 *pu8LoopPosition;
            U16 u16TotalDescriptorLength;
            u8NumOfChsInSection = pu8Section[9];
            BOOLEAN bHasInDB = FALSE;
            pu8LoopPosition = MApp_Dmx_FindFirstLoop(pu8Section, EN_TVCT);

            if(pu8Section[6] == pstVirtualCh->stVirtualChNum.u8VCTsctionNumber)
            {
                for(u8Loop_i = 0; u8Loop_i < u8NumOfChsInSection; u8Loop_i++)
                {
                    MS_VIRTUAL_CHANNEL stVirtualCh;
                    U16 u16Major_num;
                    U16 u16Minor_num;
                    u16TotalDescriptorLength = ((pu8LoopPosition[30] & 0x03) << 8) | pu8LoopPosition[31];
                    /* program number */
                    DMX_VERSION_DBG(DMX_VCTCHECK_VERSION, printf("[Loop%d]u16ProgramNumner = [old]%u --> [new]%u\n", u8Loop_i,pstVirtualCh->u16ProgramNumber, (pu8LoopPosition[24] << 8) | pu8LoopPosition[25]));
                    if(pstVirtualCh->u16ProgramNumber ==( (pu8LoopPosition[24] << 8) | pu8LoopPosition[25]))
                    {
                        bHasInDB = TRUE;
                        if((pu8LoopPosition[22] << 8 | pu8LoopPosition[23]) == pstVirtualCh->stVirtualChNum.u16ChannelTsid)
                        {
                            /*source id*/
                            DMX_VERSION_DBG(DMX_VCTCHECK_VERSION, printf("[Loop%d]source id        = [old]%u --> [new]%u\n", u8Loop_i, pstVirtualCh->u16SourceId, pu8LoopPosition[28] << 8 | pu8LoopPosition[29]));
                            if(pstVirtualCh->u16SourceId !=(pu8LoopPosition[28] << 8 | pu8LoopPosition[29]))
                            {
                                u8IsVCTFieldChange = 1;
                            }

                            DMX_VERSION_DBG(DMX_VCTCHECK_VERSION,printf("[Loop%d]service type     = [old]%u --> [new]%u\n", u8Loop_i, pstVirtualCh->u8ServiceType, pu8LoopPosition[27] & 0x3f));
                            /*sevice type*/
                            if(pstVirtualCh->u8ServiceType !=( pu8LoopPosition[27] & 0x3f))
                            {
                                u8IsVCTFieldChange = 1;
                            }
                            /*service name*/
                            MApp_Dmx_GetServiceName(&stVirtualCh, pu8LoopPosition, MAX_LENGTH_OF_SERVICE_NAME, MAX_LENGTH_OF_SERVICE_NAME-1);
                            DMX_VERSION_DBG(DMX_VCTCHECK_VERSION,printf("[Loop%d]service name     = [old]%s --> [new]%s\n", u8Loop_i, pstVirtualCh->acServiceName, stVirtualCh.acServiceName));
                            if(memcmp((char*)pstVirtualCh->acServiceName, (char*)stVirtualCh.acServiceName, sizeof(pstVirtualCh->acServiceName))!= 0)
                            {
                                //Update service name driectly no need to go to scan state
                                u8IsVCTFieldChange = 0;
                                memcpy((char*)pstVirtualCh->acServiceName, (char*)stVirtualCh.acServiceName, sizeof(pstVirtualCh->acServiceName));
                            }
                            /* major numner and minor number */
                            u16Major_num = ((pu8LoopPosition[14] & 0x0f) << 6) | (pu8LoopPosition[15] >> 2);
                            u16Minor_num = ((pu8LoopPosition[15] & 0x03) << 8) | pu8LoopPosition[16];
                            DMX_VERSION_DBG(DMX_VCTCHECK_VERSION,printf("[Loop%d]major/minor num  = [old]%u/%u --> [new]%u/%u\n", u8Loop_i,
                            pstVirtualCh->stVirtualChNum.major_num, pstVirtualCh->stVirtualChNum.minor_num,
                            u16Major_num, u16Minor_num));
                            if((pstVirtualCh->stVirtualChNum.major_num != u16Major_num)||(pstVirtualCh->stVirtualChNum.minor_num != u16Minor_num))
                            {
                                u8IsVCTFieldChange = 1;
                                printf(">>>>>VCT major and miror number change>>>>\n");
                                printf("[Loop%d]major/minor num  = [old]%u/%u --> [new]%u/%u\n", u8Loop_i,
                                pstVirtualCh->stVirtualChNum.major_num, pstVirtualCh->stVirtualChNum.minor_num,
                                u16Major_num, u16Minor_num);
                            }
                        }
                        else
                        {
                            printf("Programber is the same but Tsid changed!!\n");
                            u8IsVCTFieldChange = 1;
                        }
                    }
                    if(u8IsVCTFieldChange)
                    break;

                    pu8LoopPosition = MApp_Dmx_FindNextLoop(pu8Section, pu8LoopPosition, u16TotalDescriptorLength, EN_TVCT);
                }

                if(u8IsVCTFieldChange != 0)
                {
                    fTableVersionChanged =TRUE;

                    printf("(%d)(%s) fTableVersionChanged = TRUE~\n", __LINE__, __func__);
                }
                if(bHasInDB == FALSE)
                {
                    printf("Can't find in DB\n");
                    u8IsVCTFieldChange = 1;
                }
            }
        }
#else
    fTableVersionChanged = TRUE;
#endif
    }

    if(fTableVersionChanged)
    {
        printf(">>>>>>VCT VersionChange_%d>>>>>>>\n",__LINE__);
#if (ENABLE_ATSC_EPG_DB_2016)
        msAPI_AtscEpgDb_Delete_Event_By_RfNum(pstVirtualCh->u8RfNum);
#endif
        u8KeyCode = KEY_EXIT;
    }
    else
    {
        if (u8Version != stCurRfCh.u8VctVersion)
        {
           stCurRfCh.u8VctVersion = u8Version;
        }
    }

}

/*****************************************************************************/
void MApp_Dmx_VCT_Cb(U8 u8FID, DMX_EVENT enEvent)
{
    U32 u32ActualSize,u32RmnSize;
    MSAPI_DMX_FILTER_STATUS enStatus;
    enStatus=(MSAPI_DMX_FILTER_STATUS)enEvent;

    /*[1]check enStatus ====================================================*/
    DMX_DBG(DMX_VCT, printf("vct cb>> u8FID %d enStatus %d\n", u8FID, (U8)enStatus));

    switch(enStatus)
    {
        case MSAPI_DMX_FILTER_STATUS_SECAVAILABLE:
            {
                /* get section data */
                if(MApi_DMX_CopyData(u8FID, au8Section, MSAPI_DMX_SECTION_1K,&u32ActualSize,&u32RmnSize,NULL) == DMX_FILTER_STATUS_ERROR)
                {
                    DMX_DBG(DMX_VCT, printf("[FID=%d] VCT get section fail!! \r\n", u8FID));
                    break;
                }

                if(msAPI_DMX_CheckCRC32(au8Section) == FALSE)
                {
                    DMX_DBG(DMX_VCT, printf("[FID=%d] VCT get section check CRC error!! Case 1\n", u8FID));
                    enStatus = MSAPI_DMX_FILTER_STATUS_CRCINCORRECT;
                    au8CrcErrorCounter[u8FID]++;
                    break;
                }

                /* parsing table */
                if (!fEnableTableMonitor)
                {
                    MApp_Dmx_VCT_Parse(pastVirtualCh, au8Section);

                }
                else
                    MApp_Dmx_VCT_CheckVersionChange(au8Section);
                break;
            }

    #if (!ENABLE_NEW_DMX_INTERFACE)
        case MSAPI_DMX_FILTER_STATUS_CRCINCORRECT:
            {
                DMX_DBG(DMX_VCT, printf("[FID=%d] VCT get section check CRC error!! \r\n", u8FID));
                au8CrcErrorCounter[u8FID]++;
                break;
            }

        case MSAPI_DMX_FILTER_STATUS_TIMEOUT:
            {
                DMX_DBG(DMX_VCT, printf("[FID=%d] VCT get section timeout!! \r\n", u8FID));
                break;
            }

         case MSAPI_DMX_FILTER_STATUS_OVERFLOW:
            {
                DMX_DBG(DMX_VCT, printf("[FID=%d] VCT get section overflow!! \r\n", u8FID));
                break;
            }
    #endif

       default:
            {
                DMX_DBG(DMX_VCT, printf("[FID=%d] VCT get section unknow error!! \r\n", u8FID));
                break;
            }
    }

    if (!fEnableTableMonitor)
    {
        /*[02]finalize ==========================================================*/
        if(enStatus==MSAPI_DMX_FILTER_STATUS_CRCINCORRECT && au8CrcErrorCounter[u8FID]<=MAX_NUM_OF_CRC_ERROR)
        {
            DMX_DBG(DMX_VCT, printf("Restart VCT filter>> [FID=%d]\r\n", u8FID));
            msAPI_DMX_RestartFilter(u8FID);
        }
        else
        {
            msAPI_DMX_CloseFilter(u8FID);

            u8OpenedFltCounter--;
            au8CrcErrorCounter[u8FID] = 0;
        }
    }
    else
    {
        /*[02]finalize ==========================================================*/
        if(enStatus == MSAPI_DMX_FILTER_STATUS_SECAVAILABLE)
        {
            msAPI_DMX_CloseFilter(u8FID);
              u8VctFid = MSAPI_DMX_INVALID_FLT_ID;
        }
        else
        {
            (printf("Restart VCT filter>> [FID=%d]\r\n", u8FID));
            msAPI_DMX_RestartFilter(u8FID);
        }
    }
}
/*****************************************************************************/
void MApp_Dmx_VCT_Monitor(void)
{
    MS_DMX_SECTIONMONITOR_PARA   stSectionMonitor;

    if (fEnableVctMonitor || (msAPI_Timer_DiffTimeFromNow(u32MonitorVctTimer) > VCT_MONITOR_PERIOD))
    {
        if(u8VctFid == MSAPI_DMX_INVALID_FLT_ID)
        {
            memset(stSectionMonitor.au8MaskByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);
            memset(stSectionMonitor.au8NotMatchByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);

            stSectionMonitor.u16PID = PID_BASE;
            stSectionMonitor.u32SectionFltType = MSAPI_DMX_FILTER_TYPE_SECTION_1K;
            if(ANT_TYPE == ANT_AIR)
                stSectionMonitor.au8MatchByte[0] = TID_TVCS; //table id
            else
                stSectionMonitor.au8MatchByte[0] = TID_CVCS; //table id

            stSectionMonitor.au8MaskByte[0] = 0xFF;//0xFF

            MS_RF_CHANNEL_new stRfChTmp;
            memset(&stRfChTmp, 0x00, sizeof(MS_RF_CHANNEL_new));
            MApp_ChanProc_GetRfChannelPointer(pstVirtualCh, &stRfChTmp);
            stSectionMonitor.au8MatchByte[3] = (U8)(stRfChTmp.u16TsId >> 8); //TS ID
            stSectionMonitor.au8MatchByte[4] = (U8)(stRfChTmp.u16TsId); //TS ID

            stSectionMonitor.au8MatchByte[5] = 0x01;
            stSectionMonitor.au8MatchByte[8]    = 0x00;    // protocol_version
#if (ENABLE_VCT_TSID_MASK==1)
            stSectionMonitor.au8MaskByte[3] = 0xFF;
            stSectionMonitor.au8MaskByte[4] = 0xFF;
#else
            stSectionMonitor.au8MaskByte[3] = 0x00;
            stSectionMonitor.au8MaskByte[4] = 0x00;
#endif
            stSectionMonitor.au8MaskByte[5] = 0x01;
            stSectionMonitor.au8MaskByte[8]    = 0xFF;
            stSectionMonitor.pfNotify = MApp_Dmx_VCT_Cb;
            stSectionMonitor.u16TimeoutMilliSec = MSAPI_DMX_TIMEOUT_INFINITE;
            stSectionMonitor.pu8FID = &u8VctFid;
            stSectionMonitor.SectMode = DMX_SECT_MODE_ONESHOT|DMX_SECT_MODE_CRCCHK;

            if(msAPI_DMX_SectionMonitor(&stSectionMonitor, FALSE) == DMX_FILTER_STATUS_OK)
            {
                fEnableVctMonitor = FALSE;
                u32MonitorVctTimer = msAPI_Timer_GetTime0();
            }
        }
        else
        {
            fEnableVctMonitor = FALSE;
            u32MonitorVctTimer = msAPI_Timer_GetTime0();
        }
    }
}
#if 0
/*****************************************************************************/
EN_PARSER_STATUS MApp_Dmx_GetTable(_msAPI_Dmx_SectionMonitor_Para *pstSectionMonitor)
{
    /*[1]check error condition =============================================*/
    DMX_DBINFO(printf("<<<<Start of MApp_Dmx_GetTable: PID 0x%x TID 0x%xb!=========\r\n", pstSectionMonitor->u16PID, pstSectionMonitor->au8MatchByte[0]));

    /*
    if(msAPI_DMX_GetFree1KFilterNo() == 0)
    {
        DMX_DBINFO(printf("no section filter available!!\r\n"));
        return EN_PARSER_ERROR;
    }
    */

    /*[2]initialize variables ==============================================*/
    memset(au8CrcErrorCounter, 0x00, MSAPI_DMX_MAX_FILTER_NUMBER); //crc error counter = 0

    u8OpenedFltCounter = 0;
    u8ReceivedSecNum = 0;
    fGotFirstSection = FALSE;
    u8FirstSectionNo = 0;
    u8LastSectionNo = 0;

    /*[3-1]get first section ====================================================*/
    if(msAPI_DMX_SectionMonitor(pstSectionMonitor, FALSE) == MSAPI_DMX_FILTER_STATUS_OK)
    {
        u8OpenedFltCounter++;
        DMX_DBINFO(printf("monitoring section at Filter #%d \r\n", *pstSectionMonitor->pu8FID));
    }
    else
    {
        DMX_DBINFO(printf("monitor section fail!! \r\n"));
        return EN_PARSER_ERROR;
    }

    /* wait to get first section */
    while(msAPI_DMX_GetFilterState(*pstSectionMonitor->pu8FID) == MSAPI_DMX_FILTER_STATE_RUNNING && !fGotFirstSection)
    {
        MApi_DMX_Proc();
    }

    /*[3-2]get remainder section ================================================*/
    DMX_DBINFO(printf("u8FirstSectionNo %d u8LastSectionNo %d \r\n", u8FirstSectionNo, u8LastSectionNo));
    for(iu8Loop_i = 0; iu8Loop_i <= u8LastSectionNo; iu8Loop_i++)
    {
        /* skip this section (already got it) */
        if(iu8Loop_i == u8FirstSectionNo)
        {
            continue;
        }

        pstSectionMonitor->au8MatchByte[6] = iu8Loop_i; //section number
        pstSectionMonitor->au8MaskByte[6] = 0x00;
        while(msAPI_DMX_SectionMonitor(pstSectionMonitor, FALSE) == MSAPI_DMX_FILTER_STATUS_ERROR)
        {
            MApi_DMX_Proc();
        }

        DMX_DBINFO(printf("Monitoring sec# %d at Filter# %d \r\n", iu8Loop_i, *pstSectionMonitor->pu8FID));

        u8OpenedFltCounter++;
    }

    /*[4]finalize ===========================================================*/
    DMX_DBINFO(printf("Wait until u8OpenedFltCounter = %d to 0\n", u8OpenedFltCounter));
    while(u8OpenedFltCounter > 0) //wait until all openend filter is closed
    {
        MApi_DMX_Proc();
    }

    DMX_DBINFO(printf("<<<<End of MApp_Dmx_GetTable! ==================\r\n"));

    if(u8ReceivedSecNum > u8LastSectionNo)
        return EN_PARSER_NO_ERROR;
    else
        return EN_PARSER_ERROR;
}
#endif

/*****************************************************************************/

U8 MApp_Dmx_Eit_Get_EitTblIdx_By_FilterId(U8 u8FilterId)
{
    U8 u8EitTblIdx;

    if( u8FilterId == MSAPI_DMX_INVALID_FLT_ID )
        return 0xFF;

    for (u8EitTblIdx = 0; u8EitTblIdx < PSIP_EIT_TABLE_NUMBER; u8EitTblIdx++)
    {
        if (stEpgDBInfo.au8FID[u8EitTblIdx] == u8FilterId)
        {
            return u8EitTblIdx;
        }
    }

    return 0xFF;
}

U8 MApp_Dmx_Ett_Get_EttTblIdx_By_FilterId(U8 u8FilterId)
{
    U8 u8EttTblIdx;

    if( u8FilterId == MSAPI_DMX_INVALID_FLT_ID )
        return 0xFF;

    for (u8EttTblIdx = 0; u8EttTblIdx < PSIP_ETT_TABLE_NUMBER; u8EttTblIdx++)
    {
        if (stEpgDBInfo.au8EttFID[u8EttTblIdx] == u8FilterId)
        {
            return u8EttTblIdx;
        }
    }

    return 0xFF;
}

U8 MApp_Dmx_GetEitFreeFilter(void)
{
    U8 u8Loopi = 0;
    U8 u8EitUsingCount = 0;
    U8 u8EttUsingCount = 0;

#if (ENABLE_ATSC_EPG_DB_2016)
    for(u8Loopi=0; u8Loopi<NEW_MAX_TAB_NUM; u8Loopi++)
#else
    for(u8Loopi=0; u8Loopi<MAX_TBL_NUM; u8Loopi++)
#endif
    {
#if (ENABLE_ATSC_EPG_DB_2016)
        if(GETBIT(stEpgDBInfo.u8EitIsReceivingNew[(u8Loopi/8)],u8Loopi))
#else
        if(GETBIT(stEpgDBInfo.u8EitIsReceiving,u8Loopi))
#endif
        {
            u8EitUsingCount++;
        }

#if (ENABLE_ATSC_EPG_DB_2016)
        if(GETBIT(stEpgDBInfo.u8EttIsReceivingNew[(u8Loopi/8)],u8Loopi))
#else
        if(GETBIT(stEpgDBInfo.u8EttIsReceiving,u8Loopi))
#endif
        {
            u8EttUsingCount++;
        }


    }

    if((u8EitUsingCount+u8EttUsingCount) > FREE_FILTER_COUNT_EIT)
    {
        //printf("u8EitUsingCount+u8EttUsingCount = %d......overflow\n", u8EitUsingCount+u8EttUsingCount);
        return 0;
    }
    else
    {
        //printf("Free filter = %d\n", ((FREE_FILTER_COUNT_EIT)-(u8EitUsingCount+u8EttUsingCount)));
        return ((FREE_FILTER_COUNT_EIT)-(u8EitUsingCount+u8EttUsingCount));
    }
}

#if (ENABLE_ATSC_EPG_DB_2016)
U8 MApp_GetEttNumber(void)
{
    return u8EttNumber;
}


U8 MApp_IsAllEttReceived(void)
{
    U8 u8i = 0;
    U8 u8Ret = 1;
    for(u8i =0; u8i <u8EttNumber ; u8i++)
    {
        if(u8EttReceived[u8i] == 0)
            u8Ret = 0;
    }

    if(u8Ret)
        printf("EttNumber = %d, All Ett is received!\n", u8EttNumber);
    return u8Ret;
}

void MApp_PrintEttReceived(void)
{
    U8 u8i = 0;
    printf("-----------------------------------------------\n");
    for(u8i =0; u8i <u8EttNumber ; u8i++)
    {
        printf("%d  ", u8EttReceived[u8i]);
    }

    printf("-----------------------------------------------\n");
}



void MApp_Dmx_Eit_ResetSiDemux(void)
{
    memset(&stSiEpgSecMask, 0, sizeof(MS_SI_EPG_VCH_MASK)*ATSC_EPG_VIR_CH_NUM);
}

static BOOLEAN MApp_Dmx_Parse_Tag_CSD_New (U8 *pu8CSD, MS_EPG_EVENT_New *pEvent)
{
    U8  u8_number_of_services = 0;
    BOOLEAN bRet = FALSE;
    U8  *pu8CSDes;

    DBG_CSD(printf("\n[Parse_Tag_CSD]\n ");)

    pu8CSDes = pu8CSD;

    if(pu8CSDes != NULL)
    {
        u8_number_of_services  = (pu8CSDes[2] & 0x1F);
        DBG_CSD(printf("Caption service number = %bx\n", (U8)u8_number_of_services);)

        if (u8_number_of_services == 0)
        {
            pEvent->fHasCCInfo = FALSE;
            return FALSE;
        }

        if (u8_number_of_services > MAX_CAPTION_SERVICE_NUMBER)
        {
            u8_number_of_services = MAX_CAPTION_SERVICE_NUMBER;
            printf("caption service number invalid\n");
        }
		pEvent->stCaptionService.u8NumOfService = u8_number_of_services;
        for (iu8Loop_i = 0; iu8Loop_i < MAX_CAPTION_SERVICE_NUMBER ; iu8Loop_i++)
        {
            memset(&pEvent->stCaptionService.stCaptionServiceItem[iu8Loop_i], 0x00, sizeof(MS_EPG_Caption_Service_Item));
        }

        pu8CSDes += 3;
        pEvent->fHasCCInfo = TRUE;

        for (iu8Loop_i = 0; iu8Loop_i < u8_number_of_services; iu8Loop_i++)
        {
            memcpy(&pEvent->stCaptionService.stCaptionServiceItem[iu8Loop_i].au8Language[0], &pu8CSDes[0], 3);

            //4  u8CaptionSrvNum, bEasy_Reader and bWide_aspect_ratio are vaild only when bDigital_CC is true.
            pEvent->stCaptionService.stCaptionServiceItem[iu8Loop_i].bDigital_CC = GETBIT(pu8CSDes[3], 7);
            if (pEvent->stCaptionService.stCaptionServiceItem[iu8Loop_i].bDigital_CC)
            {
                /* Digital */
                pEvent->stCaptionService.stCaptionServiceItem[iu8Loop_i].u8CaptionSrvNum = (pu8CSDes[3] & 0x3F);
                pEvent->stCaptionService.stCaptionServiceItem[iu8Loop_i].bEasy_Reader = GETBIT(pu8CSDes[4], 7);
                pEvent->stCaptionService.stCaptionServiceItem[iu8Loop_i].bWide_aspect_ratio = GETBIT(pu8CSDes[4], 6);
            }
            else
            {
                /* Analog */
                pEvent->stCaptionService.stCaptionServiceItem[iu8Loop_i].bLin21_field = GETBIT(pu8CSDes[3], 0);
            }

            //next caption service
            pu8CSDes+= 6;

            DBG_CSD(printf ("===>[%bx] u8NumOfService=%d, bDigital_CC=%bx,  u8CaptionSrvNum=%bx, %bx, %bx, %bx, lang=%c%c%c\n", iu8Loop_i,
                pEvent->stCaptionService.u8NumOfService,
                (U8)pEvent->stCaptionService.stCaptionServiceItem[iu8Loop_i].bDigital_CC,
                (U8)pEvent->stCaptionService.stCaptionServiceItem[iu8Loop_i].u8CaptionSrvNum,
                (U8)pEvent->stCaptionService.stCaptionServiceItem[iu8Loop_i].bLin21_field,
                (U8)pEvent->stCaptionService.stCaptionServiceItem[iu8Loop_i].bEasy_Reader,
                (U8)pEvent->stCaptionService.stCaptionServiceItem[iu8Loop_i].bWide_aspect_ratio,
                pEvent->stCaptionService.stCaptionServiceItem[iu8Loop_i].au8Language[0], pEvent->stCaptionService.stCaptionServiceItem[iu8Loop_i].au8Language[1], pEvent->stCaptionService.stCaptionServiceItem[iu8Loop_i].au8Language[2]
                );)
        }

        bRet = TRUE;
    }

    return bRet;
}



void _MApp_EIT_SetBit(U8* pu8Temp, U8 u8SetBit)
{
    U8 u8SourceIndex = (u8SetBit)/8;
    U8 u8SetBitIndex =  (u8SetBit)%8;
    U8* u8TempAddr = (pu8Temp+u8SourceIndex);
    U8 u8TempData = *u8TempAddr;

    SETBIT(u8TempData, u8SetBitIndex);
    *(u8TempAddr) = u8TempData;
}

void _MApp_EIT_ClrBit(U8* pu8Temp, U8 u8ClrBit)
{
    U8 u8SourceIndex = (u8ClrBit)/8;
    U8 u8ClrBitIndex =  (u8ClrBit)%8;
    U8* u8TempAddr = (pu8Temp+u8SourceIndex);
    U8 u8TempData = *u8TempAddr;

    CLRBIT(u8TempData, u8ClrBitIndex);
    *(u8TempAddr) = u8TempData;
}



//All Received return 1 else return 0
U8 _MApp_Dmx_EIT_CheckEitAllReceived(void)
{
    U8 u8i = 0;
    U8 u8Ret = 1;
    for(u8i =0; u8i <NEW_EIT_RXOK_NUM ; u8i++)
    {
        if(stEpgDBInfo.u8EitRxOKNew[u8i] != 0xff)
           u8Ret = 0;
    }
    return u8Ret;
}

U8 _MApp_Dmx_EIT_CheckEttAllReceived(void)
{
    U8 u8i = 0;
    U8 u8Ret = 1;
    for(u8i =0; u8i <NEW_EIT_RXOK_NUM ; u8i++)
    {
        if(stEpgDBInfo.u8EttRxOKNew[u8i] != 0xff)
           u8Ret = 0;
    }

    return u8Ret;
}


void MApp_PrintEttRxOk(void)
{
    U8 u8i = 0;
    printf("----------------Ett Rx OK Value----------------\n");
    for(u8i =0; u8i <NEW_EIT_RXOK_NUM ; u8i++)
    {
        printf("0x%x  ", stEpgDBInfo.u8EttRxOKNew[u8i]);
    }

    printf("-----------------------------------------------\n");
}

#define DEBUG_ETT_PARSE(x)  //x
void MApp_Dmx_ETT_Parse_NewDB(U8 pu8Sec4K[])
{
    // Local variable declaration
    MS_EIT_PARSE_PARAM_ATSC      *pParse;
    MS_EPG_EVENT_New        stEvent;
    U16                     u16_text_length;
    U8                      *pu8LoopPosition;
    MS_EPG_EVENT_ETT_New    stEventETT;
    pstVirtualCh = MApp_ChanProc_GetCurChannelPointer();

    memset(&stEvent, 0, sizeof(MS_EPG_EVENT_New));

    pParse = &stEitParseParam;

    pu8LoopPosition = MApp_Dmx_FindFirstLoop(pu8Sec4K, EN_ETT);

    stEvent.event_id  = pParse->u16EventID;
    stEvent.u8RfNum   = pstVirtualCh->u8RfNum;
    stEvent.u16SrcId  = pParse->u16SrcID;

    DEBUG_ETT_PARSE(printf("Ett Parse: stEvent.event_id = 0x%x\n", stEvent.event_id););

    U16 u16EventIdx = msAPI_AtscEpgDb_Get_Event_By_CH_EventId(&stEvent);
    if( u16EventIdx == ATSC_EPG_INVALID_EVENT_IDX )
    {
        //this Ett no match event.....return
        //PRINT_CURRENT_LINE();
        return;
    }

    U16 u16Ettidx;
    msAPI_AtscEpgDb_Get_Event(u16EventIdx, &stEvent);
    if( stEvent.u16DbEttIdx != ATSC_EPG_INVALID_ETT_IDX )
    {
        u16Ettidx = stEvent.u16DbEttIdx;
    }
    else
    {
        // Get empty Ett solt
        u16Ettidx = msAPI_AtscEpgDb_Get_EmptyEttIdx();
        if( u16Ettidx == ATSC_EPG_INVALID_ETT_IDX )
        {
            // No empty ETT space
            //PRINT_CURRENT_LINE();
            return;
        }
    }

    u16_text_length = MApp_Dmx_Parse_MSS (pu8EpgString, pu8LoopPosition,sizeof(pu8EpgString), DISABLE)-2;
    stEventETT.bIsEttUTF16 = g_fIsUTF16;

#if 1
    msAPI_AtscEpgDb_Set_EttData( &stEventETT, pu8EpgString + 2, u16_text_length );

#else

    if( u16_text_length > (ATSC_EPG_ETT_DATA_SIZE-2) )
        u16_text_length = (ATSC_EPG_ETT_DATA_SIZE-2) ;

    stEventETT.u16EttDataLen = u16_text_length;

    memcpy(stEventETT.au8EttData, pu8EpgString + 2, u16_text_length);

    stEventETT.au8EttData[u16_text_length] = 0;
    stEventETT.au8EttData[u16_text_length+1] = 0;
#endif

    // Get current event
    if( FALSE == msAPI_AtscEpgDb_Get_Event(u16EventIdx, &stEvent) )
    {
        return;
    }

    if( FALSE == msAPI_AtscEpgDb_Set_Ett(u16Ettidx, &stEventETT) )
    {
        // Save Ett failed
        return;
    }

    //Save Ett Index into this event
    stEvent.u16DbEttIdx = u16Ettidx;

    DEBUG_ETT_PARSE(printf("Ett idx =%d, Eit index =%d\n", stEvent.u16DbEttIdx, u16EventIdx););
    // Save to current event
    msAPI_AtscEpgDb_Set_Event(u16EventIdx, &stEvent);

}

#define DEBUG_ETT_CHECK(x)  //x
#define MAX_NUM_REPEAT_ETT_SECTION 30
#define THE_BASE_ETT_SETCION_RECEIVED 5
BOOLEAN MApp_Dmx_ETT_All_Check_NewDB(MS_EIT_PARSE_PARAM_ATSC *pParse, U8 pu8Sec4K[])
{
    U8    u8_loop_i;

    pParse->u8TblID            = pu8Sec4K[0];
    pParse->u16EttTidExt    = (U16)(pu8Sec4K[3] << 8 | pu8Sec4K[4]);
    pParse->u8VerNum        = ((pu8Sec4K[5]>>1) & 0x1F);
    pParse->u8SecNum         = pu8Sec4K[6];
    pParse->u8LastSecNum    = pu8Sec4K[7];
    pParse->u8ProtocolVer    = pu8Sec4K[8];
    pParse->u16SrcID        = (U16)pu8Sec4K[9]  << 8 | (U16)pu8Sec4K[10];
    pParse->u16EventID        = (U16)pu8Sec4K[11] << 8 | (U16)pu8Sec4K[12];

    // Byte 2 - Verify preamble of section length
    if ((pu8Sec4K[1] & 0xC0) != 0xC0)
    {
        DEBUG_ETT_CHECK(printf("Wrong second Byte\n"););
        return FALSE;
    }

    // Byte 6 & 7 - Verify section_number and last_section_number
    //ATSC standard section number& last section number shall be 0x00 because Ett is only one section long
    if ((pParse->u8SecNum != 0) || (pParse->u8LastSecNum != 0))
    {
        DEBUG_ETT_CHECK(printf("Wrong SN = %bX, LSN = %bX\n", pParse->u8SecNum, pParse->u8LastSecNum););
        return FALSE;
    }

    // Byte 8 - Verify protocol_version
    if (pParse->u8ProtocolVer != 0)
    {
        DEBUG_ETT_CHECK(printf("Wrong PV = %bX\n", pParse->u8ProtocolVer););
        return FALSE;
    }

    stEpgDBInfo.au16CntEttRpt[pParse->u8Tbl]++;


    //Due to u8LastSecNum usually zero in real stream, we need define a basic section received by ourself.
    if(stEpgDBInfo.au16CntEttRpt[pParse->u8Tbl] >=THE_BASE_ETT_SETCION_RECEIVED)
    {
        u8EttReceived[pParse->u8Tbl] = 1;
        DEBUG_ETT_CHECK(printf("EPG >> ETT-%d Has received %d section....Set u8EttReceived[%d]=1\r\n", pParse->u8Tbl, THE_BASE_ETT_SETCION_RECEIVED, pParse->u8Tbl););

    }

    // ETT Overflow ?
    //if(stEpgDBInfo.au16CntEttRpt[pParse->u8Tbl] >= Max_NUM_OF_REPEAT_ETT)
    if (stEpgDBInfo.au16CntEttRpt[pParse->u8Tbl] >= MAX_NUM_REPEAT_ETT_SECTION)
    {
        _MApp_EIT_SetBit(&stEpgDBInfo.u8EttRxOKNew[0], pParse->u8Tbl);
        _MApp_EIT_ClrBit(&stEpgDBInfo.u8EttIsReceivingNew[0], pParse->u8Tbl);
        msAPI_DMX_CloseFilter(stEpgDBInfo.au8EttFID[pParse->u8Tbl]);
        stEpgDBInfo.au8EttFID[pParse->u8Tbl] = MSAPI_DMX_INVALID_FLT_ID;

        stEpgDBInfo.au16CntEttRpt[pParse->u8Tbl] = 0;
        DEBUG_ETT_CHECK(printf("EPG >> ETT Repeat overflow in table [%d], [%d]\r\n", pParse->u8Tbl, stEpgDBInfo.au16CntEttRpt[pParse->u8Tbl]););
        DEBUG_ETT_CHECK(printf("EPG >> ETT Close Ett-%d filer \r\n", pParse->u8Tbl););

        // Receive all ETT table ?
        if(_MApp_Dmx_EIT_CheckEttAllReceived()==1)
        {
            DEBUG_ETT_CHECK(printf("EPG >> Receive all ETT table\n"););
            stEpgDBInfo.u8EttCntFID = 0;
            for (iu8Loop_i = 0; iu8Loop_i < NEW_MAX_TAB_NUM; iu8Loop_i++)
            {
                stEpgDBInfo.au8EttFID[iu8Loop_i] = MSAPI_DMX_INVALID_FLT_ID;
            }
#if 0
            for (iu8Loop_i = 0; iu8Loop_i<stEpgDBInfo.u8CntSourceNum; iu8Loop_i++)
            {
                astEpgDbVchMask[iu8Loop_i].fIsInSDRAM = TRUE;
                stEpgDBInfo.u8EttIsReceiving = 0x00;
            }
#endif
        }
    }

    // Byte 9 & 10 - Verify ETM_id (source_id)
    for (u8_loop_i=0; u8_loop_i<stEpgDBInfo.u8CntSourceNum; u8_loop_i++)
    {
        if (pParse->u16SrcID == stEpgDBInfo.au16SrcID[u8_loop_i])
        {
            // Channel ETM_id ?
            if (pParse->u16EventID == 0x00)
            {
                DEBUG_ETT_CHECK(printf("Event ID = 0\n"););
                return FALSE;
            }
            else
            {
                pParse->u8SrcIdx = u8_loop_i;
                pParse->u16EventID = pParse->u16EventID >> 2;
                return TRUE;
            }
        }
    }

    DEBUG_ETT_CHECK(printf("End of ETT Check\n"););
    return FALSE;
}

void MApp_Dmx_EIT_ParseDescriptor_NewDB(U8 * pu8LoopPosition,MS_EPG_EVENT_New * pEvent)
{
    U16     u16TotalDescriptorLength;
    U16     u16DescriptorLength;
    U8      *pu8Descriptor;
    U8      u8_descriptor_counter;
    S16     s16TotalDescriptorLength;

    /* Total descriptor length */
    u16TotalDescriptorLength    = ((U16)pu8LoopPosition [(10 + pu8LoopPosition[9])] << 8) | (U16)pu8LoopPosition[(11 + pu8LoopPosition[9])];
    u16TotalDescriptorLength     &= 0x0FFF;

    /* Move to 1st descriptor tag position */
    pu8Descriptor = pu8LoopPosition + 12 + pu8LoopPosition[9];

    // Calculate next loop position
    //printf("111pu8LoopPosition = 0x%x\n", pu8LoopPosition);
    pu8LoopPosition = pu8Descriptor + u16TotalDescriptorLength;
    //printf("222pu8LoopPosition = 0x%x\n", pu8LoopPosition);

    // Set default value of CAD
    memset(&pEvent->stRating, 0x00, sizeof(MS_EPG_RATING));

    // To indicate that no TV rating has received from EPG
    pEvent->stRating.u8TVRatingForEntire = INVALID_TV_RATING_FOR_ENTIRE;

    // Set default value of CSD
    pEvent->fHasCCInfo = FALSE;

    s16TotalDescriptorLength = (S16)(u16TotalDescriptorLength);
    u8_descriptor_counter = 0;

    //printf ("s Total = %X\n", s16TotalDescriptorLength);

    // Parsing descriptor
    while(s16TotalDescriptorLength > 0)
    {
        switch(pu8Descriptor[0])    // Descriptor tag
        {
            case TAG_CAD_ATSC:
                MApp_Dmx_Parse_Tag_CAD(pu8Descriptor, &pEvent->stRating);
                break;

            case TAG_CSD_ATSC:
                MApp_Dmx_Parse_Tag_CSD_New(pu8Descriptor, pEvent);
                break;

            default:
                break;
        }

        /* Move to next descriptor */
        u16DescriptorLength         = pu8Descriptor[1] + 2;
        s16TotalDescriptorLength     -= (u16DescriptorLength);
        pu8Descriptor                 += (u16DescriptorLength);
        u8_descriptor_counter++;

        if (pu8Descriptor[1] > 0xFD)
        {
            //printf ("EIT >> Wrong Len = %d\n", pu8Descriptor[1]);
        }

        if (u8_descriptor_counter>100)
        {
            //printf ("EIT >> Loop Overflow\n");
            return;
        }
    }   // End of parsing descriptor


}

#define DEBUG_EIT_SETFLAG(x)  //x
void MApp_Dmx_EIT_Set_Flag_NewDB(MS_EIT_PARSE_PARAM_ATSC *pParse)
{

    // ===   Set EPG Database Status  ===
    // [1]    New section.    -> Save it to the EPG DB and set Sec bit mask in Seg
    SETBIT (stSiEpgSecMask[pParse->u8SrcIdx].au8SecMask[pParse->u8Tbl][pParse->u8SecNum/8], pParse->u8SecNum%8);
    stSiEpgSecMask[pParse->u8SrcIdx].u8CntSec[pParse->u8Tbl]++;
    DEBUG_EIT_SETFLAG(printf("Receive Eit-%d Sec-%d, Lase SecNum = %d\n", pParse->u8Tbl, pParse->u8SecNum, pParse->u8LastSecNum););
//
    // [2]    Receive all sections in table?
    if (stSiEpgSecMask[pParse->u8SrcIdx].u8CntSec[pParse->u8Tbl] >= pParse->u8LastSecNum)
    {
        stEpgDBInfo.au8CntSource[pParse->u8Tbl]++;
        SETBIT(stEpgDBInfo.au8SourceMask[pParse->u8Tbl], pParse->u8SrcIdx);

        // Receive all program source in this EIT-k instance ?
        if (stEpgDBInfo.au8CntSource[pParse->u8Tbl] >= stEpgDBInfo.u8CntSourceNum)
        {
            _MApp_EIT_SetBit(&stEpgDBInfo.u8EitRxOKNew[0], pParse->u8Tbl);
            _MApp_EIT_ClrBit(&stEpgDBInfo.u8EitIsReceivingNew[0], pParse->u8Tbl);

            msAPI_DMX_CloseFilter(stEpgDBInfo.au8FID[pParse->u8Tbl]);

#if (EIT_VN_CHANGE_FOR_RRT)
            //This function will keep Eit-0 alaways monitor
            if(pParse->u8Tbl == 0)
            {
                MApp_Dmx_EIT_For_RRT_Monitor();
            }
#endif

            DEBUG_EIT_SETFLAG(printf("Close Eit-%d filter, Free filter count=%d\n", pParse->u8Tbl, msAPI_DMX_Get_FreeSec4KFilterCount()););
            stEpgDBInfo.au8FID[pParse->u8Tbl] = MSAPI_DMX_INVALID_FLT_ID;

            // Receive all EIT table ?
            if (_MApp_Dmx_EIT_CheckEitAllReceived()==1)
            {
                DEBUG_EIT_SETFLAG(printf("EPG >> Receive all EIT table\n"););
                stEpgDBInfo.u8CntFID = 0;
                for (iu8Loop_i = 0; iu8Loop_i < NEW_MAX_TAB_NUM; iu8Loop_i++)
                {
                    stEpgDBInfo.au8FID[iu8Loop_i] = MSAPI_DMX_INVALID_FLT_ID;
                }

             }
          }
    }

}

MS_EPG_EVENT_New* MApp_Dmx_GetCurrentEvent(void)
{
    return &g_stCurrentEvent;
}

#define DEBUG_EIT_PARSE(x)  //x
void MApp_Dmx_EIT_Parse_NewDB(MS_EIT_PARSE_PARAM_ATSC *pParse, U8 pu8Sec4K[])
{
    // Local variable declaration
    U8   u8_loop_i;
    U8   u8_text_length;
    U16  u16TotalDescriptorLength;
    U8   *pu8LoopPosition, *pu8Descriptor;
    //U8   u8NumOfEvents = 0;

    MS_EPG_EVENT_New  *pEvent;
    //U8 buffIdx;

    //buffIdx = MApp_ChanProc_GetCurIdxMap2ChanBufIdx(MApp_ChanProc_GetCurProgIndex());
    pstVirtualCh = MApp_ChanProc_GetCurChannelPointer();

    // [1]    Goto first loop position
    pu8LoopPosition = MApp_Dmx_FindFirstLoop(pu8Sec4K, EN_EIT);

    if( NULL == pu8LoopPosition )
    {
        printf("\nWarning: pu8LoopPosition is NULL!\n");
        return;
    }

    //Print_Buffer(pu8LoopPosition, 64);

    // [2]    Event Loop
    DEBUG_EIT_PARSE( printf("pParse->u8NumOfEvents=%u\n", pParse->u8NumOfEvents); );

    for(u8_loop_i = 0; u8_loop_i < pParse->u8NumOfEvents; u8_loop_i++)
    {
        memset( &g_stRxEventNew, 0x00, sizeof(MS_EPG_EVENT_New) );

        //g_stRxEventNew.event_id = INVALID_EVENT_ID;

        pEvent = &g_stRxEventNew;

        pEvent->u8RfNum = pstVirtualCh->u8RfNum;
        pEvent->u16SrcId = pParse->u16SrcID;
        pEvent->u8EitTblNumber = pParse->u8Tbl;

        // Save event_id, start_time, length, u16DbTitlePos
        pEvent->event_id = (((U16)pu8LoopPosition[0] & 0x3F) << 8) | (U16)pu8LoopPosition[1];

        //memcpy(&pEvent->start_time, &pu8LoopPosition[2], 4);
        pEvent->start_time = pu8LoopPosition[2];
        pEvent->start_time <<= 8;
        pEvent->start_time |= pu8LoopPosition[3];
        pEvent->start_time <<= 8;
        pEvent->start_time |= pu8LoopPosition[4];
        pEvent->start_time <<= 8;
        pEvent->start_time |= pu8LoopPosition[5];

        //memcpy(&pEvent->length[0],  &pu8LoopPosition[6], 3);
    #if 1
        pEvent->u32TimeLen = ((pu8LoopPosition[6]&0x0F)<<16) + (pu8LoopPosition[7]<<8) + pu8LoopPosition[8];
        //printf(" 0x%X,0x%X,0x%X => 0x%X(%u)\n", pu8LoopPosition[6], pu8LoopPosition[7], pu8LoopPosition[8], pEvent->u32TimeLen);
    #else
        pEvent->length[0] = pu8LoopPosition[6];
        pEvent->length[1] = pu8LoopPosition[7];
        pEvent->length[2] = pu8LoopPosition[8];
    #endif


        u8_text_length = MApp_Dmx_Parse_MSS(pu8EpgString, &pu8LoopPosition[10],sizeof(pu8EpgString), DISABLE) - 2;
        pEvent->fIsEitUTF16 = g_fIsUTF16;

        // First 2 byte is length, so real title string is "u8_text_length-2"

        if( u8_text_length > (ATSC_EPG_TITLE_DATA_SIZE-2) )
            u8_text_length = (ATSC_EPG_TITLE_DATA_SIZE-2) ;

        pEvent->u8TitleLen = u8_text_length;
        memcpy(pEvent->au8Title, pu8EpgString + 2, u8_text_length);

        pEvent->au8Title[u8_text_length] = 0;
        pEvent->au8Title[u8_text_length+1] = 0;
        pEvent->u16DbEttIdx = ATSC_EPG_INVALID_ETT_IDX;
        //pEvent->au8Title[ATSC_EPG_TITLE_DATA_SIZE-1] = 0;
        //pEvent->au8Title[ATSC_EPG_TITLE_DATA_SIZE-2] = 0;


        DEBUG_EIT_PARSE( printf(" event_id=0x%X,", pEvent->event_id); );
        DEBUG_EIT_PARSE( printf(" u8TitleLen=%u,", pEvent->u8TitleLen ); );
        DEBUG_EIT_PARSE( printf(" Title=" ); );
        DEBUG_EIT_PARSE( msAPI_AtscEpgDb_PrintEventTitle(pEvent->au8Title, 30, pEvent->fIsEitUTF16); );
        DEBUG_EIT_PARSE( printf("\n" ); );


        MApp_Dmx_EIT_ParseDescriptor_NewDB(pu8LoopPosition, pEvent);

        u16TotalDescriptorLength = ((U16)pu8LoopPosition [(10 + pu8LoopPosition[9])] << 8) | (U16)pu8LoopPosition[(11 + pu8LoopPosition[9])];
        u16TotalDescriptorLength &= 0x0FFF;

        pu8Descriptor = pu8LoopPosition + 12 + pu8LoopPosition[9];
        pu8LoopPosition = pu8Descriptor + u16TotalDescriptorLength;

        if( msAPI_AtscEpgDb_Add_Event( pEvent) )
        {
            //printf("SaveEvent >> Index = %d, Eid = 0x%X, Start time = %u, len=%u\n", u16EventIdx,(U16)pEvent->event_id, pEvent->start_time, pEvent->u32TimeLen);
            //printf("  >> Len = %u\n", pEvent->u32TimeLen );

         #if 0   //Debug
            MS_EPG_EVENT_New TempEvent;
            msAPI_AtscEpgDb_Get_Event(u16EventIdx, &TempEvent);
            //printf("Load >> Index = %d, Eid = 0x%X, Start time = 0x%lX\n", u16EventIdx,(U16)TempEvent.event_id, TempEvent.start_time);
            //printf("Title = %s\n\n", TempEvent.au8Title);
         #endif
        }
        else
        {
        }

        // Check Current Event & Save it
        if((pParse->u8Tbl == 0)&&(pEvent->u16SrcId == pstVirtualCh->u16SourceId))
        {
            U32 u32StartTime = pEvent->start_time - DEFAULT_SYSTEM_TIME - u8GpsUtcOffset;
            U32 u32EndTime = u32StartTime + pEvent->u32TimeLen;
            if ((u32StartTime <= g_u32StreamTime) && (u32EndTime > g_u32StreamTime))
            {
                //Find Current Event....Set into Globar variable
                memcpy(&g_stCurrentEvent, pEvent, sizeof(MS_EPG_EVENT_New));
            }
        }

    }
}


#define DEBUG_EIT_SET_FILTER(x)  //x
void _MApp_Dmx_EIT_SetFilter_NewDB(U16 u16_pid, U8 u8_table_id)
{
    MS_DMX_SECTIONMONITOR_PARA   stSectionMonitor;

//printf("_MApp_Dmx_EIT_SetFilter_NewDB(u16_pid=0x%X, u8_table_id=%u)\n", u16_pid, u8_table_id);

    // Set all mask byte to 0xFF (Don't Care)
    memset(stSectionMonitor.au8MaskByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);
    memset(stSectionMonitor.au8NotMatchByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);

    // Set EIT table PID
    stSectionMonitor.u16PID             = u16_pid;      // Table PID
    stSectionMonitor.u32SectionFltType  = MSAPI_DMX_FILTER_TYPE_SECTION_4K;
    stSectionMonitor.au8MatchByte[0]    = u8_table_id;  // Table ID
    stSectionMonitor.au8MaskByte[0]     = 0xFF;
    stSectionMonitor.au8MatchByte[5]    = 0x01;         // reserved [7:6] + version_number [5:1] + current_next_indicator [0]
    stSectionMonitor.au8MaskByte[5]     = 0x01;
    stSectionMonitor.au8MatchByte[8]    = 0x00;         // protocol_version
    stSectionMonitor.au8MaskByte[8]     = 0xFF;
    stSectionMonitor.SectMode           = DMX_SECT_MODE_CONTI|DMX_SECT_MODE_CRCCHK;
    // Set Callback Function, Global Filter ID and Continuous mode
    stSectionMonitor.pfNotify           = MApp_Dmx_EIT_Cb;

    if(u8_table_id == TID_EIS)
    {
        #if 0   // Need refine....now no check source id
        //stSectionMonitor.au8MatchByte[3]    = HIGHBYTE(stEpgDBInfo.au16SrcID[0]);   // High byte of source_id
        //stSectionMonitor.au8MaskByte[3]     = 0xFF;
        //stSectionMonitor.au8MatchByte[4]    = LOWBYTE(stEpgDBInfo.au16SrcID[0]);    // Low byte of source_id
        //stSectionMonitor.au8MaskByte[4]     = 0xFF;
        #endif

        stSectionMonitor.pu8FID             = &stEpgDBInfo.au8FID[stEpgDBInfo.u8CntFID];
        if (stEpgDBInfo.u8CntFID == 0)
        {
            stSectionMonitor.u16TimeoutMilliSec = EIT_0_TIMEOUT;

        }
        else if (stEpgDBInfo.u8CntFID == 1)
        {
            stSectionMonitor.u16TimeoutMilliSec = EIT_1_TIMEOUT;
        }
        else
        {
            stSectionMonitor.u16TimeoutMilliSec = EIT_TIMEOUT;
        }

    }
    else
    {
#if 0   // Need refine....now no check source id
        stSectionMonitor.au8MatchByte[9]     = HIGHBYTE(stEpgDBInfo.au16SrcID[0]);
        stSectionMonitor.au8MaskByte[9]      = 0xFF;
        stSectionMonitor.au8MatchByte[10]    = LOWBYTE(stEpgDBInfo.au16SrcID[0]);
        stSectionMonitor.au8MaskByte[10]     = 0xFF;
#endif
        stSectionMonitor.pu8FID             = &stEpgDBInfo.au8EttFID[stEpgDBInfo.u8EttCntFID];
        stSectionMonitor.u16TimeoutMilliSec = ETT_TIMEOUT;
    }

    // Set filter
    if(msAPI_DMX_SectionMonitor(&stSectionMonitor, FALSE) == DMX_FILTER_STATUS_OK)
    {
        if (u8_table_id == TID_EIS)
        {
            if (_MApp_Dmx_EIT_CheckEitAllReceived()==0)
            {
                _MApp_EIT_SetBit(&stEpgDBInfo.u8EitIsReceivingNew[0], stEpgDBInfo.u8CntFID);
            }

            //au8EitFID2ItemIdx[(stEpgDBInfo.au8FID[stEpgDBInfo.u8CntFID])] = stEpgDBInfo.u8CntFID;
            stEpgDBInfo.u8CntFID++;
        }
        else if(u8_table_id == TID_ETS)
        {
            if (_MApp_Dmx_EIT_CheckEttAllReceived()==0)
            {
                _MApp_EIT_SetBit(&stEpgDBInfo.u8EttIsReceivingNew[0], stEpgDBInfo.u8EttCntFID);
            }

            //au8EttFID2ItemIdx[(stEpgDBInfo.au8EttFID[stEpgDBInfo.u8EttCntFID])] = stEpgDBInfo.u8EttCntFID;
            stEpgDBInfo.u8EttCntFID++;
        }
    }
    else
    {
        DEBUG_EIT_SET_FILTER(printf("EPG: monitor EIT fail!! \r\n"););
    }
}


void _MApp_Dmx_EIT_Set_Demux_NewDB(void)
{
    U16    u16_pid;
    U8    u8_table_id;

    // Check MGT or monitor EIT timer is timeout
    //printf("_MApp_Dmx_EIT_Set_Demux_NewDB\n");
    if(stMGT.version_number != INVALID_VERSION_NUM)
    {
        //Get free filter from demux
        //if(msAPI_DMX_GetFreeFilterCount() > 0)
        if((MApp_Dmx_GetEitFreeFilter() > 0 )&&(msAPI_DMX_Get_FreeSec4KFilterCount()>0))
        {
            //Set Eit 0 and Ett 0 first
            //after Eit-0 and Ett-0 is set, set Eit-i and Ett-i
            if(stEpgDBInfo.u8EttCntFID < stEpgDBInfo.u8CntFID)
            {
                //Eit-i filter is set and now set Ett-i filter
                u16_pid = stMGT.astEttItem[stEpgDBInfo.u8EttCntFID].table_type_PID;
                u8_table_id = TID_ETS;
                if (u16_pid == 0)
                {
                    //All Ett table is been set. set Rx ok bit 1
                    if(stEpgDBInfo.u8EttCntFID < NEW_MAX_TAB_NUM)
                    {
                        _MApp_EIT_SetBit(&stEpgDBInfo.u8EttRxOKNew[0], stEpgDBInfo.u8EttCntFID);
                    }
                }
                else
                {
                    DEBUG_EIT_SET_FILTER(printf("Set Ett-%d pid = 0x%x\n", stEpgDBInfo.u8EttCntFID, u16_pid););
                }
            }
            else
            {
                if(_MApp_Dmx_EIT_CheckEitAllReceived() == 0)
                {
                //set Eit-i filter
                u16_pid = stMGT.astEitItem[stEpgDBInfo.u8CntFID].table_type_PID;
                u8_table_id = TID_EIS;
                if (u16_pid == 0)
                {
                    if(stEpgDBInfo.u8CntFID < NEW_MAX_TAB_NUM)
                    {
                        _MApp_EIT_SetBit(&stEpgDBInfo.u8EitRxOKNew[0], stEpgDBInfo.u8CntFID);
                    }
                }
                else
                {
                    DEBUG_EIT_SET_FILTER(printf("Set Eit-%d u16_pid = %x\n", stEpgDBInfo.u8CntFID,u16_pid););
                }
            }
                else
                    return;
            }

            if(u8_table_id == TID_EIS)
            {
                if((u16_pid != 0)&&(stEpgDBInfo.au8FID[stEpgDBInfo.u8CntFID] == MSAPI_DMX_INVALID_FLT_ID))
                {
                    _MApp_Dmx_EIT_SetFilter_NewDB(u16_pid, u8_table_id);

                }
                else
                {
                    if(stEpgDBInfo.u8CntFID < (NEW_MAX_TAB_NUM-1))
                    {
                        stEpgDBInfo.u8CntFID++;
                    }
                }
            }
            else if(u8_table_id == TID_ETS)
            {
                if((u16_pid != 0)&&(stEpgDBInfo.au8EttFID[stEpgDBInfo.u8EttCntFID] == MSAPI_DMX_INVALID_FLT_ID))
                {
                    _MApp_Dmx_EIT_SetFilter_NewDB(u16_pid, u8_table_id);

                }
                else
                {
                    if(stEpgDBInfo.u8EttCntFID < (NEW_MAX_TAB_NUM-1))
                        stEpgDBInfo.u8EttCntFID++;
                }

            }
        }
        else
        {
            DEBUG_EIT_SET_FILTER(printf("Filter Full!\n"););
            return; //do nothing and wait free filter comes
        }


    }
}

void _MApp_Dmx_EIT_Monitor_NewDB(void)
{
    // Not set all filter ID to EIT

    if ((stEpgDBInfo.u8CntFID < NEW_MAX_TAB_NUM) ||(stEpgDBInfo.u8EttCntFID < NEW_MAX_TAB_NUM))
    {
        //if (stEpgDBInfo.u8EitRxOK == MAX_TBL_MASK)
        if(_MApp_Dmx_EIT_CheckEitAllReceived() == 1)
        {
            if(_MApp_Dmx_EIT_CheckEttAllReceived() == 1)
            {
                return;
            }
            else
            {
                _MApp_Dmx_EIT_Set_Demux_NewDB();
            }
        }
        else
        {
            _MApp_Dmx_EIT_Set_Demux_NewDB();
        }
    }
    else
    {
        //printf("stEpgDBInfo.u8CntFID = %d, %d\n", stEpgDBInfo.u8CntFID, stEpgDBInfo.u8EttCntFID);
    }

}

#endif

static BOOLEAN MApp_Dmx_EIT_Check(MS_EIT_PARSE_PARAM_ATSC *pParse, U8 pu8Sec4K[])
{
    U8 u8_loop_i=0;
    pParse->u8TblID            = pu8Sec4K[0];
    pParse->u16SrcID        = (U16)(pu8Sec4K[3] << 8 | pu8Sec4K[4]);
    pParse->u8VerNum        = ((pu8Sec4K[5]>>1) & 0x1F);
    pParse->u8SecNum         = pu8Sec4K[6];
    pParse->u8LastSecNum    = pu8Sec4K[7];
    pParse->u8ProtocolVer    = pu8Sec4K[8];
    pParse->u8NumOfEvents    = pu8Sec4K[9];

    EIT_DBG(EIT_CHECK, ("Eit-%d, TblID = %bX, SrcID = %X, VerNum = %d, SN = %d, LSN = %d, Num of Events = %d\n"
        , pParse->u8Tbl,pParse->u8TblID, pParse->u16SrcID, pParse->u8VerNum, pParse->u8SecNum, pParse->u8LastSecNum, pParse->u8NumOfEvents));

    // Byte 2 - preamble of section_length
    if ((pu8Sec4K[1] & 0xC0) != 0xC0)
    {
        EIT_DBG(EIT_CHECK, ("Wrong second Byte\n"));
        return FALSE;
    }

    // Byte 5 - Verify version_number
    if (pParse->u8VerNum != stMGT.astEitItem[pParse->u8Tbl].table_type_version_number)
    {
        #if (EIT_VN_CHANGE_FOR_RRT==TRUE)
        EIT_DBG(EIT_CHECK, ("New VN: EIT = %bX, MGT = %bX\n", pParse->u8VerNum, stMGT.astEitItem[pParse->u8Tbl].table_type_version_number));
        stMGT.astEitItem[pParse->u8Tbl].table_type_version_number   = pParse->u8VerNum;
        #else
        EIT_DBG(EIT_CHECK, ("Wrong VN: EIT = %bX, MGT = %bX\n", pParse->u8VerNum, stMGT.astEitItem[pParse->u8Tbl].table_type_version_number));
        return FALSE;
        #endif
    }

    // Byte 6 & 7 - Verify section_number
    if (pParse->u8SecNum > pParse->u8LastSecNum)
    {
        EIT_DBG(EIT_CHECK, ("Wrong SN = %bX, LSN = %bX\n", pParse->u8SecNum, pParse->u8LastSecNum));
        return FALSE;
    }

    // Byte 8 - Verify protocol_version
    if (pParse->u8ProtocolVer != 0)
    {
        EIT_DBG(EIT_CHECK, ("Wrong PV = %bX\n", pParse->u8ProtocolVer));
        return FALSE;
    }


#if (ENABLE_ATSC_EPG_DB_2016)
    u8_loop_i = 0;

  #if(ATSC_EPG_ONLY_CUR_CHANNEL)
    //check source id is the same as current channel
    pstVirtualCh = MApp_ChanProc_GetCurChannelPointer();
    if(pParse->u16SrcID == pstVirtualCh->u16SourceId)
    {
        return TRUE;
    }
    else
        return FALSE;
  #else

    // Byte 3 & 4 - Verify source_id
    for (u8_loop_i=0; u8_loop_i<stEpgDBInfo.u8CntSourceNum; u8_loop_i++)
    {
        if (pParse->u16SrcID == stEpgDBInfo.au16SrcID[u8_loop_i])
        {
            // Old source id
            if (GETBIT(stEpgDBInfo.au8SourceMask[pParse->u8Tbl], u8_loop_i) == TRUE)
            {
                EIT_DBG(EIT_CHECK, ("=== EPG: Old Source ID and Return ===\r\n"));
                return FALSE;
            }
            // New source id
            else
            {
                pParse->u8SrcIdx = u8_loop_i;
                // Old Section Number
                if (GETBIT (stSiEpgSecMask[pParse->u8SrcIdx].au8SecMask[pParse->u8Tbl][pParse->u8SecNum/8], pParse->u8SecNum%8))
                {
                    EIT_DBG(EIT_CHECK, ("=== New EPG: Old Section Number ===\r\n"));
                    return FALSE;
                }
                else
                {
                    EIT_DBG(EIT_CHECK, ("=== New EPG: Loop[%bx] Matched Source ID [%X] ===\r\n", u8_loop_i, stEpgDBInfo.au16SrcID[u8_loop_i]));
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
  #endif

#else
    // Byte 3 & 4 - Verify source_id
    for (u8_loop_i=0; u8_loop_i<stEpgDBInfo.u8CntSourceNum; u8_loop_i++)
    {
        if (pParse->u16SrcID == stEpgDBInfo.au16SrcID[u8_loop_i])
        {
            // Old source id
            if (GETBIT(stEpgDBInfo.au8SourceMask[pParse->u8Tbl], u8_loop_i) == TRUE)
            {
                EIT_DBG(EIT_CHECK, ("=== EPG: Old Source ID and Return ===\r\n"));
                return FALSE;
            }
            // New source id
            else
            {
                pParse->u8SrcIdx = u8_loop_i;

                // Old Section Number
                if (GETBIT (astEpgDbVchMask[pParse->u8SrcIdx].au8SecMask[pParse->u8Tbl][pParse->u8SecNum/8], pParse->u8SecNum%8))
                {
                    EIT_DBG(EIT_CHECK, ("=== EPG: Old Section Number ===\r\n"));
                    return FALSE;
                }
                else
                {
                    EIT_DBG(EIT_CHECK, ("=== EPG: Loop[%bx] Matched Source ID [%X] ===\r\n", u8_loop_i, stEpgDBInfo.au16SrcID[u8_loop_i]));
                    return TRUE;
                }
            }
        }
    }
#endif
    return FALSE;
}
/*****************************************************************************/
#if (!ENABLE_ATSC_EPG_DB_2016)
static void MApp_Dmx_EIT_Set_Flag(MS_EIT_PARSE_PARAM_ATSC *pParse)
{
    // ===   Set EPG Database Status  ===

    // [1]    New section.    -> Save it to the EPG DB and set Sec bit mask in Seg
    SETBIT (astEpgDbVchMask[pParse->u8SrcIdx].au8SecMask[pParse->u8Tbl][pParse->u8SecNum/8], pParse->u8SecNum%8);
    astEpgDbVchMask[pParse->u8SrcIdx].u8CntSec[pParse->u8Tbl]++;
    EIT_DBG(EIT_SETFLAG, ("u8SrcIdx = %d, SN = %d, pVch->u8CntSec[%d] = %d\n", pParse->u8SrcIdx, pParse->u8SecNum, pParse->u8Tbl, astEpgDbVchMask[pParse->u8SrcIdx].u8CntSec[pParse->u8Tbl]));
    // [2]    Receive all sections in table?
    if (astEpgDbVchMask[pParse->u8SrcIdx].u8CntSec[pParse->u8Tbl] >= pParse->u8LastSecNum)
    {
        // Set corresponding mask bit and increase the counter
        SETBIT(stEpgDBInfo.au8SourceMask[pParse->u8Tbl], pParse->u8SrcIdx);
        stEpgDBInfo.au8CntSource[pParse->u8Tbl]++;
        SETBIT(astEpgDbVchMask[pParse->u8SrcIdx].u8TblMask, pParse->u8Tbl);

        // Receive all program source in this EIT-k instance ?
        if (stEpgDBInfo.au8CntSource[pParse->u8Tbl] >= stEpgDBInfo.u8CntSourceNum)
        {
            SETBIT (stEpgDBInfo.u8EitRxOK, pParse->u8Tbl);
            CLRBIT (stEpgDBInfo.u8EitIsReceiving, stEitParseParam.u8Tbl);
            EIT_DBG(EIT_SETFLAG, ("EPG >> Receive all source in table [%d] stEpgDBInfo.u8EitRxOK = %d\r\n", pParse->u8Tbl, stEpgDBInfo.u8EitRxOK));

            msAPI_DMX_CloseFilter(stEpgDBInfo.au8FID[pParse->u8Tbl]);
            stEpgDBInfo.au8FID[pParse->u8Tbl] = MSAPI_DMX_INVALID_FLT_ID;

            // Receive all EIT table ?
            if (stEpgDBInfo.u8EitRxOK == MAX_TBL_MASK)
            {
                EIT_DBG(EIT_SETFLAG, ("EPG >> Receive all EIT table\n"));

                stEpgDBInfo.u8CntFID = 0;
                for (iu8Loop_i = 0; iu8Loop_i < MAX_TBL_NUM; iu8Loop_i++)
                {
                    stEpgDBInfo.au8FID[iu8Loop_i] = MSAPI_DMX_INVALID_FLT_ID;
                }

                for (iu8Loop_i = 0; iu8Loop_i<stEpgDBInfo.u8CntSourceNum; iu8Loop_i++)
                {
                    astEpgDbVchMask[iu8Loop_i].fIsInSDRAM = TRUE;
                    stEpgDBInfo.u8EitIsReceiving = 0x00;
                }
            }
            else
            {
                if(stEpgDBInfo.u8EitRxOK == BASIC_TBL_MASK)
                {
                    EIT_DBG(EIT_SETFLAG, ("EPG >> Receive Eit4 table\n"));
                    u8CheckEit0_3Received = 1;

                }
            }
        }
    }
}
#endif

#if (EIT_DROP_INSERT_EVENT)
static MAPI_PSIP_EIT_EVNET MApp_Dmx_EIT_InsertEventChecker(U8 u8VchSrcIdx, MS_EPG_VCH_BUF *pVch, MS_EPG_EVENT *pEvent, U8* pu8InsertTblIdx,U8* pu8InsertEvtIdx, U8* pu8NumOfEvents)
{
    U8 u8_loop_j=0;
    U8 u8_loop_k=0;
    U8 u8_loop_m=0;
    U8 u8_loop_n=0;
    MS_EPG_EVENT    stEventInfo;
    U32 u32EventStartTime;
    U32 u32EventEndTime;
    U32 u32CheckedEventEndTime;
    U8 u8_max_event_no;
    MAPI_PSIP_EIT_EVNET enRet = EN_PSIP_EIT_EVNET_NO_OP;
    U8 au8TitleTmpBuf[80];


    u32CheckedEventEndTime = pEvent->start_time + EPG_EVENT_LENGTH(pEvent->length[0], pEvent->length[1], pEvent->length[2]);
    for(u8_loop_j = 0; u8_loop_j <MAX_TBL_NUM;u8_loop_j++)
    {
        u8_max_event_no = MIN(pVch->au8CntEvent_InTbl[u8_loop_j], MAX_EVENT_IN_TBL);

        // Find current event in current service channel
        for(u8_loop_k = 0; u8_loop_k < u8_max_event_no; u8_loop_k++)
        {
            MApp_EpgDB_LoadEvent(u8VchSrcIdx, u8_loop_j, u8_loop_k, &stEventInfo);
            u32EventStartTime = stEventInfo.start_time;
            u32EventEndTime = u32EventStartTime + EPG_EVENT_LENGTH(stEventInfo.length[0], stEventInfo.length[1], stEventInfo.length[2]);
            //
            if ((u32EventStartTime <= pEvent->start_time) &&(u32EventEndTime < u32CheckedEventEndTime))
            {
                enRet = EN_PSIP_EIT_EVNET_INSERT;
                EIT_DBG(EIT_EVENT, ("insert the new coming event\n"));
                *pu8InsertEvtIdx = u8_loop_k;
                *pu8InsertTblIdx = u8_loop_j;

                //delete the overlapped event after insert index
                while(u32CheckedEventEndTime > u32EventEndTime)
                {
                    U16 u16TempDbTitlePos;
                    MApp_EpgDB_LoadEvent(u8VchSrcIdx, *pu8InsertTblIdx, *pu8InsertEvtIdx, &stEventInfo);
                    u16TempDbTitlePos = stEventInfo.u16DbTitlePos;
                    if(MApp_EpgDB_DeleteEvent(u8VchSrcIdx,*pu8InsertTblIdx, *pu8InsertEvtIdx))
                    {
                        MS_EPG_EVENT_TITILE stSrcEventTitle;
                        memset(&stSrcEventTitle, 0, sizeof(MS_EPG_EVENT_TITILE));

                        stSrcEventTitle.pu8Title_content = au8TitleTmpBuf;

                        MApp_EpgDB_LoadEvent(u8VchSrcIdx, *pu8InsertTblIdx, *pu8InsertEvtIdx, &stEventInfo);
                        u32EventStartTime = stEventInfo.start_time;
                        u32EventEndTime = u32EventStartTime + EPG_EVENT_LENGTH(stEventInfo.length[0], stEventInfo.length[1], stEventInfo.length[2]);

                        //Move event title location
                        MApp_EpgDB_LoadEventTitle(u8VchSrcIdx, stEventInfo.u16DbTitlePos, &stSrcEventTitle, sizeof(au8TitleTmpBuf) );
                        stEventInfo.u16DbTitlePos = u16TempDbTitlePos;
                        MApp_EpgDB_SaveEvent(u8VchSrcIdx, *pu8InsertTblIdx, *pu8InsertEvtIdx, &stEventInfo);
                        MApp_EpgDB_SaveEventTitle(u8VchSrcIdx, stEventInfo.u16DbTitlePos, &stSrcEventTitle);
                        (*pu8NumOfEvents)--;
                    }
                    else
                        break;

                }
                break;
            }
            else if((u32EventStartTime > pEvent->start_time) &&(u32EventEndTime < u32CheckedEventEndTime))
            {
                enRet = EN_PSIP_EIT_EVNET_INSERT;
                EIT_DBG(EIT_EVENT, ("insert the new coming event and need to delete prev events\n"));

                *pu8InsertEvtIdx = u8_loop_k;
                *pu8InsertTblIdx = u8_loop_j;
                //delete the overlapped event after insert index
                while(u32CheckedEventEndTime > u32EventEndTime)
                {
                    U16 u16TempDbTitlePos;
                    MApp_EpgDB_LoadEvent(u8VchSrcIdx, *pu8InsertTblIdx, *pu8InsertEvtIdx, &stEventInfo);
                    u16TempDbTitlePos = stEventInfo.u16DbTitlePos;
                    if(MApp_EpgDB_DeleteEvent(u8VchSrcIdx,*pu8InsertTblIdx, *pu8InsertEvtIdx))
                    {
                        MS_EPG_EVENT_TITILE stSrcEventTitle;
                        memset(&stSrcEventTitle, 0, sizeof(MS_EPG_EVENT_TITILE));

                        stSrcEventTitle.pu8Title_content = au8TitleTmpBuf;

                        MApp_EpgDB_LoadEvent(u8VchSrcIdx, *pu8InsertTblIdx, *pu8InsertEvtIdx, &stEventInfo, sizeof(au8TitleTmpBuf) );
                        u32EventStartTime = stEventInfo.start_time;
                        u32EventEndTime = u32EventStartTime + EPG_EVENT_LENGTH(stEventInfo.length[0], stEventInfo.length[1], stEventInfo.length[2]);

                        //Move event title location
                        MApp_EpgDB_LoadEventTitle(u8VchSrcIdx, stEventInfo.u16DbTitlePos, &stSrcEventTitle);
                        stEventInfo.u16DbTitlePos= u16TempDbTitlePos;
                        MApp_EpgDB_SaveEvent(u8VchSrcIdx, *pu8InsertTblIdx, *pu8InsertEvtIdx, &stEventInfo);
                        MApp_EpgDB_SaveEventTitle(u8VchSrcIdx, stEventInfo.u16DbTitlePos, &stSrcEventTitle);

                        (*pu8NumOfEvents)--;
                    }
                    else
                        break;
                }

                //delete the overlapped event before insert index
                for(u8_loop_m=0; u8_loop_m < (*pu8InsertEvtIdx); u8_loop_m++)
                {
                    MApp_EpgDB_LoadEvent(u8VchSrcIdx, *pu8InsertTblIdx, u8_loop_m, &stEventInfo);
                    u32EventStartTime = stEventInfo.start_time;
                    u32EventEndTime = u32EventStartTime + EPG_EVENT_LENGTH(stEventInfo.length[0], stEventInfo.length[1], stEventInfo.length[2]);

                    if(pEvent->start_time < u32EventEndTime)
                    {
                        break;
                    }
                }
                if(u8_loop_m < *pu8InsertEvtIdx)
                {
                    for(u8_loop_n= (*pu8InsertEvtIdx-1); u8_loop_n >=u8_loop_m ; u8_loop_n--)
                    {
                        MS_EPG_EVENT_TITILE stSrcEventTitle;
                        U16 u16TempDbTitlePos;
                        memset(&stSrcEventTitle, 0, sizeof(MS_EPG_EVENT_TITILE));

                        stSrcEventTitle.pu8Title_content = au8TitleTmpBuf;

                        MApp_EpgDB_LoadEvent(u8VchSrcIdx, *pu8InsertTblIdx, u8_loop_n, &stEventInfo);
                        u16TempDbTitlePos = stEventInfo.u16DbTitlePos;

                        MApp_EpgDB_DeleteEvent(u8VchSrcIdx,*pu8InsertTblIdx, u8_loop_n);

                        //Move event title location
                        MApp_EpgDB_LoadEventTitle(u8VchSrcIdx, stEventInfo.u16DbTitlePos, &stSrcEventTitle, sizeof(au8TitleTmpBuf));
                        stEventInfo.u16DbTitlePos= u16TempDbTitlePos;
                        MApp_EpgDB_SaveEvent(u8VchSrcIdx, *pu8InsertTblIdx, *pu8InsertEvtIdx, &stEventInfo);
                        MApp_EpgDB_SaveEventTitle(u8VchSrcIdx, stEventInfo.u16DbTitlePos, &stSrcEventTitle);
                        (*pu8NumOfEvents)--;
                    }
                }
                *pu8InsertEvtIdx = u8_loop_m;
                break;
            }
            else
            {
                enRet = EN_PSIP_EIT_EVNET_NO_OP;
            }

        }
    }


    return enRet;
}


static void MApp_Dmx_EIT_ParseDescriptor(U8 *pu8LoopPosition, MS_EPG_EVENT *pEvent)
{
    U16     u16TotalDescriptorLength;
    U16     u16DescriptorLength;
    U8      *pu8Descriptor;
    U8      u8_descriptor_counter;
    S16     s16TotalDescriptorLength;

    /* Total descriptor length */
    u16TotalDescriptorLength    = ((U16)pu8LoopPosition [(10 + pu8LoopPosition[9])] << 8) | (U16)pu8LoopPosition[(11 + pu8LoopPosition[9])];
    u16TotalDescriptorLength     &= 0x0FFF;

    /* Move to 1st descriptor tag position */
    pu8Descriptor = pu8LoopPosition + 12 + pu8LoopPosition[9];

    // Calculate next loop position
    //printf("111pu8LoopPosition = 0x%x\n", pu8LoopPosition);
    pu8LoopPosition = pu8Descriptor + u16TotalDescriptorLength;
    //printf("222pu8LoopPosition = 0x%x\n", pu8LoopPosition);

    // Set default value of CAD
    memset(&pEvent->stRating, 0x00, sizeof(MS_EPG_RATING));

    // To indicate that no TV rating has received from EPG
    pEvent->stRating.u8TVRatingForEntire = INVALID_TV_RATING_FOR_ENTIRE;

    // Set default value of CSD
    pEvent->fHasCCInfo = FALSE;

    s16TotalDescriptorLength = (S16)(u16TotalDescriptorLength);
    u8_descriptor_counter = 0;

    //printf ("s Total = %X\n", s16TotalDescriptorLength);

    // Parsing descriptor
    while(s16TotalDescriptorLength > 0)
    {
        switch(pu8Descriptor[0])    // Descriptor tag
        {
            case TAG_CAD:
                MApp_Dmx_Parse_Tag_CAD(pu8Descriptor, &pEvent->stRating);
                break;

            case TAG_CSD:
                MApp_Dmx_Parse_Tag_CSD(pu8Descriptor, pEvent);
                break;

            case TAG_AC3AD:
                break;
            default:
                break;
        }

        /* Move to next descriptor */
        u16DescriptorLength         = pu8Descriptor[1] + 2;
        s16TotalDescriptorLength     -= (u16DescriptorLength);
        pu8Descriptor                 += (u16DescriptorLength);
        u8_descriptor_counter++;

        if (pu8Descriptor[1] > 0xFD)
        {
            //printf ("EIT >> Wrong Len = %d\n", pu8Descriptor[1]);
        }

        if (u8_descriptor_counter>100)
        {
            //printf ("EIT >> Loop Overflow\n");
            return;
        }
    }   // End of parsing descriptor


}

/*****************************************************************************/
static void MApp_Dmx_EIT_Parse (MS_EIT_PARSE_PARAM_ATSC *pParse, U8 pu8Sec4K[])
{
    // Local variable declaration
    U8      u8_loop_i;
    U8      u8_text_length;
    U16     u16TotalDescriptorLength;
    U8      *pu8LoopPosition, *pu8Descriptor;
    U8      u8NumOfEvents = 0;
    MS_EPG_VCH_BUF  *pVch;
    MS_EPG_EVENT    *pEvent;
    MS_EPG_EVENT_TITILE pSrcEventTitle;

    MAPI_PSIP_EIT_EVNET enEitEvtOp;
    U8 u8InsertEvtIndex = 0;
    U8 u8InsertTblIndex = 0;


    pVch = &astEpgDbVchBuf[pParse->u8SrcIdx];
    pVch->u8SrcIdx = pParse->u8SrcIdx;

    // Save "Overflow","Null"to event Title string pool and event ETT string pool
    if (pVch->fIsFirstTime == FALSE)
    {
        MApp_EpgDB_ContentInit(pVch);
    }


    // ===    Parsing Events of the Section   ===
    // [1]    Goto first loop position
    pu8LoopPosition = MApp_Dmx_FindFirstLoop(pu8Sec4K, EN_EIT);
    // [2]    Event Loop
    for(u8_loop_i = 0; u8_loop_i < pParse->u8NumOfEvents; u8_loop_i++)
    {
        memset (&g_stRxEvent, 0x00, sizeof (MS_EPG_EVENT));
        g_stRxEvent.event_id = INVALID_EVENT_ID;
        pEvent = &g_stRxEvent;

        // Save event_id, start_time, length, u16DbTitlePos
        pEvent->event_id = (((U16)pu8LoopPosition[0] & 0x3F) << 8) | (U16)pu8LoopPosition[1];
        //memcpy(&pEvent->start_time, &pu8LoopPosition[2], 4);
        pEvent->start_time = pu8LoopPosition[2];
        pEvent->start_time <<= 8;
        pEvent->start_time |= pu8LoopPosition[3];
        pEvent->start_time <<= 8;
        pEvent->start_time |= pu8LoopPosition[4];
        pEvent->start_time <<= 8;
        pEvent->start_time |= pu8LoopPosition[5];
        //memcpy(&pEvent->length[0],  &pu8LoopPosition[6], 3);
        pEvent->length[0] = pu8LoopPosition[6];
        pEvent->length[1] = pu8LoopPosition[7];
        pEvent->length[2] = pu8LoopPosition[8];
        pEvent->u16DbTitlePos = pVch->u16DBOffset;

        EIT_DBG(EIT_EVENT, ("1 >> SrcID = %u, Event id = 0x%4X, Start Time = 0x%08lx\n", pParse->u16SrcID, pEvent->event_id, pEvent->start_time));
        EIT_DBG(EIT_EVENT, ("2 >> Length in seconds = 0x%lX\n", EPG_EVENT_LENGTH(pEvent->length[0], pEvent->length[1], pEvent->length[2])));
        EIT_DBG(EIT_EVENT, ("3 >> u16DbTitlePos = 0x%04X\n", pEvent->u16DbTitlePos));
        EIT_DBG(EIT_EVENT, ("4 >> u8SrcIdx = %d,  u8Tbl = %d\n", pParse->u8SrcIdx, pParse->u8Tbl);)
    #if 0
        printf ("1 >> SrcID = %u, Event id = 0x%4X, Start Time = 0x%08lx\n", pParse->u16SrcID, pEvent->event_id, pEvent->start_time);
        printf ("2 >> Length in seconds = 0x%lX\n", EPG_EVENT_LENGTH(pEvent->length[0], pEvent->length[1], pEvent->length[2]));
        printf ("3 >> u16DbTitlePos = 0x%04X\n", pEvent->u16DbTitlePos);
    #endif
        enEitEvtOp = MApp_Dmx_EIT_InsertEventChecker(pParse->u8SrcIdx, pVch, pEvent, &u8InsertTblIndex, &u8InsertEvtIndex, &u8NumOfEvents);
        if(enEitEvtOp ==EN_PSIP_EIT_EVNET_INSERT)
        {
            //insert the event
            MApp_EpgDB_InsertEvent(pParse->u8SrcIdx, u8InsertTblIndex, u8InsertEvtIndex, pEvent);

            //Move the EIT title location to match the
            u8_text_length = MApp_Dmx_Parse_MSS(pu8EpgString, &pu8LoopPosition[10],sizeof(pu8EpgString), DISABLE)-2;
            pEvent->fIsEitUTF16 = g_fIsUTF16;

            if(u8_text_length > 2)
            {
                pSrcEventTitle.u16Title_length = u8_text_length-2;
                pSrcEventTitle.pu8Title_content = &pu8EpgString[2];
                MApp_EpgDB_SaveEventTitle(pParse->u8SrcIdx, pVch->u16DBOffset, &pSrcEventTitle);
                pVch->u16DBOffset = (u8NumOfEvents+1)*((U16)EPG_EITTITLE_MAX_STR_LEN)+EPG_TITLE_START_OFFSET;
                EIT_DBG(EIT_EVENT, ("b =%s=\r\n", pSrcEventTitle.pu8Title_content));
            }
            else
            {  //show "Null" or "No Description Available"
#ifdef EPG_NO_DESCRIPTION_AVAILABLE
                pSrcEventTitle.u16Title_length = 26; // 24 characters + u16Title_length
                strcpy((char *)(&pu8EpgString[0]), "No Description Available");
                pSrcEventTitle.pu8Title_content = &pu8EpgString[0];
                MApp_EpgDB_SaveEventTitle(pParse->u8SrcIdx, pVch->u16DBOffset, &pSrcEventTitle);
                pVch->u16DBOffset = (u8NumOfEvents+1)*((U16)EPG_EITTITLE_MAX_STR_LEN)+EPG_TITLE_START_OFFSET; //u8_text_length;
#else
                //pSrcEventTitle.u16Title_length = 0x01; //0x04;
                //strcpy((char *)(&pu8EpgString[0]), " "); //"Null");
                pSrcEventTitle.u16Title_length = 6; // 4 characters + u16Title_length
                strcpy((char *)(&pu8EpgString[0]), "Null");
                pSrcEventTitle.pu8Title_content = &pu8EpgString[0];
                MApp_EpgDB_SaveEventTitle(pParse->u8SrcIdx, pVch->u16DBOffset, &pSrcEventTitle);
                pVch->u16DBOffset = (u8NumOfEvents+1)*((U16)EPG_EITTITLE_MAX_STR_LEN)+EPG_TITLE_START_OFFSET;//u8_text_length;
#endif
                EIT_DBG(EIT_EVENT, ("c =%s=\r\n", pSrcEventTitle.pu8Title_content));
            }
        }
        else if(enEitEvtOp == EN_PSIP_EIT_EVNET_NO_OP)
        {
            pVch->u32MinStartTime = MIN(pEvent->start_time, pVch->u32MinStartTime);
            pVch->u32MaxEndTime = MAX(pVch->u32MaxEndTime, pEvent->start_time + EPG_EVENT_LENGTH(pEvent->length[0], pEvent->length[1], pEvent->length[2]));
            // String pool is oveflow for this service buffer?
            if((pVch->u16DBOffset + pu8LoopPosition[9]) > MAX_EIT_TITLE_LEN_OF_STR_POOL)
            {
                pEvent->u16DbTitlePos = 0; //Show "Overflow"
                EIT_DBG(EIT_EVENT, ("=== EPG: Event Pool Overflow @ u8SrcIdx#%d ===\r\n", pVch->u8SrcIdx));
            }
            else
            {
                //u8_text_length = MApp_Dmx_Parse_MSS (pu8EpgString, &pu8LoopPosition[10]);
                u8_text_length = MApp_Dmx_Parse_MSS(pu8EpgString, &pu8LoopPosition[10],sizeof(pu8EpgString), DISABLE)-2;
                pEvent->fIsEitUTF16 = g_fIsUTF16;

                if(u8_text_length > 2)
                {
                    pSrcEventTitle.u16Title_length = u8_text_length-2;
                    pSrcEventTitle.pu8Title_content = &pu8EpgString[2];
                    MApp_EpgDB_SaveEventTitle(pParse->u8SrcIdx, pVch->u16DBOffset, &pSrcEventTitle);
                    pVch->u16DBOffset = (u8NumOfEvents+1)*((U16)EPG_EITTITLE_MAX_STR_LEN)+EPG_TITLE_START_OFFSET;
                    EIT_DBG(EIT_EVENT, ("\n @@@b =%s=\r\n", pSrcEventTitle.pu8Title_content));
                }
                else
                {  //show "Null" or "No Description Available"
            #ifdef EPG_NO_DESCRIPTION_AVAILABLE
                    pSrcEventTitle.u16Title_length = 26; // 24 characters + u16Title_length
                    strcpy((char *)(&pu8EpgString[0]), "No Description Available");
                    pSrcEventTitle.pu8Title_content = &pu8EpgString[0];
                    MApp_EpgDB_SaveEventTitle(pParse->u8SrcIdx, pVch->u16DBOffset, &pSrcEventTitle);
                    pVch->u16DBOffset = (u8NumOfEvents+1)*((U16)EPG_EITTITLE_MAX_STR_LEN)+EPG_TITLE_START_OFFSET;
            #else
                    //pSrcEventTitle.u16Title_length = 0x01; //0x04;
                    //strcpy((char *)(&pu8EpgString[0]), " "); //"Null");
                    pSrcEventTitle.u16Title_length = 6; // 4 characters + u16Title_length
                    strcpy((char *)(&pu8EpgString[0]), "Null");
                    pSrcEventTitle.pu8Title_content = &pu8EpgString[0];
                    MApp_EpgDB_SaveEventTitle(pParse->u8SrcIdx, pVch->u16DBOffset, &pSrcEventTitle);
                    pVch->u16DBOffset = (u8NumOfEvents+1)*((U16)EPG_EITTITLE_MAX_STR_LEN)+EPG_TITLE_START_OFFSET;
            #endif
                    EIT_DBG(EIT_EVENT, ("c =%s=\r\n", pSrcEventTitle.pu8Title_content));
                }
            }
        }

        MApp_Dmx_EIT_ParseDescriptor(pu8LoopPosition, pEvent);
        u16TotalDescriptorLength    = ((U16)pu8LoopPosition [(10 + pu8LoopPosition[9])] << 8) | (U16)pu8LoopPosition[(11 + pu8LoopPosition[9])];
        u16TotalDescriptorLength     &= 0x0FFF;
        pu8Descriptor = pu8LoopPosition + 12 + pu8LoopPosition[9];
        pu8LoopPosition = pu8Descriptor + u16TotalDescriptorLength;


        if(pParse->u8EitSaveIndex[pParse->u8Tbl] < MAX_EVENT_IN_TBL)
        {
            if(MApp_EpgDB_SaveEvent(pParse->u8SrcIdx, pParse->u8Tbl, (u8NumOfEvents + pParse->u8EitSaveIndex[pParse->u8Tbl]), pEvent))
            {
#if (EIT_DEBUG&EIT_EVENT)
                MApp_EpgDB_LoadEvent(pParse->u8SrcIdx, pParse->u8Tbl, ((u8NumOfEvents + pParse->u8EitSaveIndex[pParse->u8Tbl])), &g_stUiEvent);
                pSrcEventTitle.pu8Title_content = &pu8EpgString[0];
                MApp_EpgDB_LoadEventTitle(pParse->u8SrcIdx, g_stUiEvent.u16DbTitlePos, &pSrcEventTitle, sizeof(pu8EpgString) );
                EIT_DBG(EIT_EVENT, ("SaveEvent >> (x, y, z)= (%d, %d, %d)\r\n", pParse->u8SrcIdx, pParse->u8Tbl, (u8NumOfEvents + pParse->u8EitSaveIndex[pParse->u8Tbl])));
                EIT_DBG(EIT_EVENT, ("SaveEvent >> Eid = 0x%X, Start time = 0x%lX\n", (U16)g_stUiEvent.event_id, g_stUiEvent.start_time));
                EIT_DBG(EIT_EVENT, ("Title = %s\n", pSrcEventTitle.pu8Title_content));
                EIT_DBG(EIT_EVENT, ("Total Event in (%d)table = %d\n\n", pParse->u8Tbl, pVch->au8CntEvent_InTbl[pParse->u8Tbl]));
#endif
                u8NumOfEvents++;
                pVch->au8CntEvent_InTbl[pParse->u8Tbl]++;
            }
        }
        else
           printf("EIT-%d overflow!!\r\n", pParse->u8Tbl);

    }   // End of event loop

    pParse->u8EitSaveIndex[pParse->u8Tbl] += u8NumOfEvents;

}
#else
#if (!ENABLE_ATSC_EPG_DB_2016)
static void MApp_Dmx_EIT_Parse (MS_EIT_PARSE_PARAM_ATSC *pParse, U8 pu8Sec4K[])
{
    // Local variable declaration
    U8      u8_loop_i;
    U8      u8_descriptor_counter;
    U8      u8_text_length;
    U16     u16DescriptorLength;
    U8      *pu8LoopPosition, *pu8Descriptor;
    U16     u16TotalDescriptorLength;
    U8      u8NumOfEvents = 0;
    S16 s16TotalDescriptorLength;
    MS_EPG_VCH_BUF  *pVch;
    MS_EPG_EVENT    *pEvent;
    MS_EPG_EVENT_TITILE pSrcEventTitle;

    pVch = &astEpgDbVchBuf[pParse->u8SrcIdx];
    pVch->u8SrcIdx = pParse->u8SrcIdx;

    // Save "Overflow","Null"to event Title string pool and event ETT string pool
    if (pVch->fIsFirstTime == FALSE)
    {
        MApp_EpgDB_ContentInit(pVch);
    }


    // ===    Parsing Events of the Section   ===
    // [1]    Goto first loop position
    pu8LoopPosition = MApp_Dmx_FindFirstLoop(pu8Sec4K, EN_EIT);

    // [2]    Event Loop
    for(u8_loop_i = 0; u8_loop_i < pParse->u8NumOfEvents; u8_loop_i++)
    {
        memset (&g_stRxEvent, 0x00, sizeof (MS_EPG_EVENT));
        g_stRxEvent.event_id = INVALID_EVENT_ID;
        pEvent = &g_stRxEvent;

        // Save event_id, start_time, length, u16DbTitlePos
        pEvent->event_id = (((U16)pu8LoopPosition[0] & 0x3F) << 8) | (U16)pu8LoopPosition[1];
        //memcpy(&pEvent->start_time, &pu8LoopPosition[2], 4);
        pEvent->start_time = pu8LoopPosition[2];
        pEvent->start_time <<= 8;
        pEvent->start_time |= pu8LoopPosition[3];
        pEvent->start_time <<= 8;
        pEvent->start_time |= pu8LoopPosition[4];
        pEvent->start_time <<= 8;
        pEvent->start_time |= pu8LoopPosition[5];
        //memcpy(&pEvent->length[0],  &pu8LoopPosition[6], 3);
        pEvent->length[0] = pu8LoopPosition[6];
        pEvent->length[1] = pu8LoopPosition[7];
        pEvent->length[2] = pu8LoopPosition[8];
        pEvent->u16DbTitlePos = pVch->u16DBOffset;

        EIT_DBG(EIT_EVENT, ("1 >> SrcID = %u, Event id = 0x%4X, Start Time = 0x%08lx\n", pParse->u16SrcID, pEvent->event_id, pEvent->start_time));
        EIT_DBG(EIT_EVENT, ("2 >> Length in seconds = 0x%lX\n", EPG_EVENT_LENGTH(pEvent->length[0], pEvent->length[1], pEvent->length[2])));
        EIT_DBG(EIT_EVENT, ("3 >> u16DbTitlePos = 0x%04X\n", pEvent->u16DbTitlePos));

    #if 0
        printf ("1 >> SrcID = %u, Event id = 0x%4X, Start Time = 0x%08lx\n", pParse->u16SrcID, pEvent->event_id, pEvent->start_time);
        printf ("2 >> Length in seconds = 0x%lX\n", EPG_EVENT_LENGTH(pEvent->length[0], pEvent->length[1], pEvent->length[2]));
        printf ("3 >> u16DbTitlePos = 0x%04X\n", pEvent->u16DbTitlePos);
    #endif

        pVch->u32MinStartTime = MIN(pEvent->start_time, pVch->u32MinStartTime);
        pVch->u32MaxEndTime = MAX(pVch->u32MaxEndTime, pEvent->start_time + EPG_EVENT_LENGTH(pEvent->length[0], pEvent->length[1], pEvent->length[2]));

        // String pool is oveflow for this service buffer?
        if((pVch->u16DBOffset + pu8LoopPosition[9]) > MAX_EIT_TITLE_LEN_OF_STR_POOL)
        {
            pEvent->u16DbTitlePos = 0; //Show "Overflow"
            EIT_DBG(EIT_EVENT, ("=== EPG: Event Pool Overflow @ u8SrcIdx#%d ===\r\n", pVch->u8SrcIdx));
        }
        else
        {
            //u8_text_length = MApp_Dmx_Parse_MSS (pu8EpgString, &pu8LoopPosition[10]);
            u8_text_length = MApp_Dmx_Parse_MSS (pu8EpgString, &pu8LoopPosition[10],sizeof(pu8EpgString), DISABLE)-2;
            #if 0
            {
                U16 length;
                U16 i;
                length = (U16)pu8EpgString[0]<<8 | pu8EpgString[1];
                printf(" length is %d, %d \n",length, u8_text_length);

                printf("==>");
                for(i=2;i<length;i+=2)
                printf(" (%d,%d)",pu8EpgString[i],pu8EpgString[i+1]);
                printf("<== \n\n");

                printf("==>");
                for(i=2;i<length;i+=2)
                printf(" (%c,%c)",pu8EpgString[i],pu8EpgString[i+1]);
                printf("<== \n\n");

                printf("\n");
            }
            #endif

            pEvent->fIsEitUTF16 = g_fIsUTF16;

            if(u8_text_length > EPG_EITTITLE_MAX_STR_LEN)
            {
                pSrcEventTitle.u16Title_length = EPG_EITTITLE_MAX_STR_LEN;
                pSrcEventTitle.pu8Title_content = &pu8EpgString[2];
                MApp_EpgDB_SaveEventTitle(pParse->u8SrcIdx, pVch->u16DBOffset, &pSrcEventTitle);
                pVch->u16DBOffset += EPG_EITTITLE_MAX_STR_LEN;
                EIT_DBG(EIT_EVENT, ("a =%s=\r\n", pSrcEventTitle.pu8Title_content));
            }
            else if(u8_text_length > 2)
            {
                pSrcEventTitle.u16Title_length = u8_text_length-2;
                pSrcEventTitle.pu8Title_content = &pu8EpgString[2];
                MApp_EpgDB_SaveEventTitle(pParse->u8SrcIdx, pVch->u16DBOffset, &pSrcEventTitle);
                pVch->u16DBOffset += u8_text_length;
                EIT_DBG(EIT_EVENT, ("b =%s=\r\n", pSrcEventTitle.pu8Title_content));
            }
            else
            {  //show "Null" or "No Description Available"
                #ifdef EPG_NO_DESCRIPTION_AVAILABLE
                pSrcEventTitle.u16Title_length = 26; // 24 characters + u16Title_length
                strcpy((char *)(&pu8EpgString[0]), "No Description Available");
                pSrcEventTitle.pu8Title_content = &pu8EpgString[0];
                MApp_EpgDB_SaveEventTitle(pParse->u8SrcIdx, pVch->u16DBOffset, &pSrcEventTitle);
                pVch->u16DBOffset += pSrcEventTitle.u16Title_length; //u8_text_length;
                #else
                //pSrcEventTitle.u16Title_length = 0x01; //0x04;
                //strcpy((char *)(&pu8EpgString[0]), " "); //"Null");
                pSrcEventTitle.u16Title_length = 6; // 4 characters + u16Title_length
                strcpy((char *)(&pu8EpgString[0]), "Null");
                pSrcEventTitle.pu8Title_content = &pu8EpgString[0];
                MApp_EpgDB_SaveEventTitle(pParse->u8SrcIdx, pVch->u16DBOffset, &pSrcEventTitle);
                pVch->u16DBOffset += pSrcEventTitle.u16Title_length;//u8_text_length;
                #endif
                EIT_DBG(EIT_EVENT, ("c =%s=\r\n", pSrcEventTitle.pu8Title_content));
            }
        }

        /* Total descriptor length */
        u16TotalDescriptorLength    = ((U16)pu8LoopPosition [(10 + pu8LoopPosition[9])] << 8) | (U16)pu8LoopPosition[(11 + pu8LoopPosition[9])];
        u16TotalDescriptorLength     &= 0x0FFF;

        /* Move to 1st descriptor tag position */
        pu8Descriptor = pu8LoopPosition + 12 + pu8LoopPosition[9];

        // Calculate next loop position
        pu8LoopPosition = pu8Descriptor + u16TotalDescriptorLength;


        // Set default value of CAD
        memset(&pEvent->stRating, 0x00, sizeof(MS_EPG_RATING));

        // To indicate that no TV rating has received from EPG
        pEvent->stRating.u8TVRatingForEntire = INVALID_TV_RATING_FOR_ENTIRE;

        // Set default value of CSD
        pEvent->fHasCCInfo = FALSE;

        s16TotalDescriptorLength = (S16)(u16TotalDescriptorLength);
        u8_descriptor_counter = 0;

        //printf ("s Total = %X\n", s16TotalDescriptorLength);

        // Parsing descriptor
        while(s16TotalDescriptorLength > 0)
        {
            switch(pu8Descriptor[0])    // Descriptor tag
            {
                case TAG_CAD_ATSC:
                    MApp_Dmx_Parse_Tag_CAD(pu8Descriptor, &pEvent->stRating);
                    break;

                case TAG_CSD_ATSC:
                    MApp_Dmx_Parse_Tag_CSD(pu8Descriptor, pEvent);
                    break;

                case TAG_AC3AD:
                    break;
                default:
                    break;
            }

            /* Move to next descriptor */
            u16DescriptorLength         = pu8Descriptor[1] + 2;
            s16TotalDescriptorLength     -= (u16DescriptorLength);
            pu8Descriptor                 += (u16DescriptorLength);
            u8_descriptor_counter++;

            if (pu8Descriptor[1] > 0xFD)
            {
                //printf ("EIT >> Wrong Len = %d\n", pu8Descriptor[1]);
            }

            if (u8_descriptor_counter>100)
            {
                //printf ("EIT >> Loop Overflow\n");
                return;
            }
        }   // End of parsing descriptor
        if(MApp_EpgDB_SaveEvent(pParse->u8SrcIdx, pParse->u8Tbl, (u8NumOfEvents + pParse->u8EitSaveIndex[pParse->u8Tbl]), pEvent))
        {
#if (EIT_DEBUG&EIT_EVENT)
            MApp_EpgDB_LoadEvent(pParse->u8SrcIdx, pParse->u8Tbl, (u8NumOfEvents+ pParse->u8EitSaveIndex[pParse->u8Tbl]), &g_stUiEvent);

            pSrcEventTitle.pu8Title_content = &pu8EpgString[0];

            MApp_EpgDB_LoadEventTitle(pParse->u8SrcIdx, g_stUiEvent.u16DbTitlePos, &pSrcEventTitle, sizeof(pu8EpgString) );
            EIT_DBG(EIT_EVENT, ("SaveEvent >> (x, y, z)= (%d, %d, %d)\r\n", pParse->u8SrcIdx, pParse->u8Tbl, (u8NumOfEvents+ pParse->u8EitSaveIndex[pParse->u8Tbl])));
            EIT_DBG(EIT_EVENT, ("SaveEvent >> Eid = 0x%X, Start time = 0x%lX\n", (U16)g_stUiEvent.event_id, g_stUiEvent.start_time));
            EIT_DBG(EIT_EVENT, ("Title = %s\n\n", pSrcEventTitle.pu8Title_content));
#endif
            u8NumOfEvents++;
            pVch->au8CntEvent_InTbl[pParse->u8Tbl]++;
        }

    }   // End of event loop

    pParse->u8EitSaveIndex[pParse->u8Tbl] += u8NumOfEvents;

}
#endif

#endif
#if (MONITOR_ETT_ALL)
#if (!ENABLE_ATSC_EPG_DB_2016)
/*****************************************************************************/
static MS_EPG_EVENT *MApp_Dmx_ETT_All_Find_Match_Event (MS_EPG_VCH_BUF *pVch, U16 u16MatchEventId)
{
    U8 u8Tbl;
    U8 u8Event;
    U8 u8_max_event_no;
    MS_EPG_EVENT *pstEvent;

    for (u8Tbl = 0; u8Tbl < MAX_TBL_NUM; u8Tbl++)
    {
        u8_max_event_no = MIN(pVch->au8CntEvent_InTbl[u8Tbl], MAX_EVENT_IN_TBL);
        for (u8Event = 0; u8Event < u8_max_event_no; u8Event++)
        {
            MApp_EpgDB_LoadEvent(stEitParseParam.u8SrcIdx, u8Tbl, u8Event, &g_stRxEvent);
            pstEvent = &g_stRxEvent;
            EIT_DBG(ETT_PARSE, ("Find >> (Src, Tbl, Event) = (%d, %d, %d)\r\n", stEitParseParam.u8SrcIdx, u8Tbl, u8Event));
            if (pstEvent->event_id == u16MatchEventId)
            {
                EIT_DBG(ETT_PARSE, ("Find >> Match = 0x%X, Eid = 0x%X\n", u16MatchEventId, pstEvent->event_id));
                stEitParseParam.u8EventIdx = u8Event;

                stEitParseParam.u8Tbl = u8Tbl;
                return pstEvent;
            }
        }
    }
    return NULL;
}
/*****************************************************************************/
static BOOLEAN MApp_Dmx_ETT_All_Check(MS_EIT_PARSE_PARAM_ATSC *pParse, U8 pu8Sec4K[])
{
    U8    u8_loop_i;

    pParse->u8TblID            = pu8Sec4K[0];
    pParse->u16EttTidExt    = (U16)(pu8Sec4K[3] << 8 | pu8Sec4K[4]);
    pParse->u8VerNum        = ((pu8Sec4K[5]>>1) & 0x1F);
    pParse->u8SecNum         = pu8Sec4K[6];
    pParse->u8LastSecNum    = pu8Sec4K[7];
    pParse->u8ProtocolVer    = pu8Sec4K[8];
    pParse->u16SrcID        = (U16)pu8Sec4K[9]  << 8 | (U16)pu8Sec4K[10];
    pParse->u16EventID        = (U16)pu8Sec4K[11] << 8 | (U16)pu8Sec4K[12];
    EIT_DBG(ETT_CHECK, ("TblID = %bX, u8Tbl = %d, SrcID = %X, VerNum = %d, SN = %d, LSN = %d, Num of Events = %d\n"
        , pParse->u8TblID, pParse->u8Tbl, pParse->u16SrcID, pParse->u8VerNum, pParse->u8SecNum, pParse->u8LastSecNum, pParse->u8NumOfEvents));
#if 0
    printf ("TblID = %bX, u8Tbl = %d, SrcID = %X, VerNum = %d, SN = %d, LSN = %d, Num of Events = %d\n"
        , pParse->u8TblID, pParse->u8Tbl, pParse->u16SrcID, pParse->u8VerNum, pParse->u8SecNum, pParse->u8LastSecNum, pParse->u8NumOfEvents);
#endif

    // Byte 2 - Verify preamble of section length
    if ((pu8Sec4K[1] & 0xC0) != 0xC0)
    {
        EIT_DBG(ETT_CHECK,  ("Wrong second Byte\n"));
        return FALSE;
    }

#if 0    // comment out for non-standard stream
    // Byte 3 & 4 - Verify ETT_table_id_extension
    if (pParse->u16EttTidExt != 0)
    {
        EPG_DBG(PARSECHK, ("Wrong u16EttTidExt = %X\n", pParse->u16EttTidExt));
        return FALSE;
    }
#endif

#if 0    // comment out for non-standard stream
    // Byte 5 - Verify version_number
    if (pParse->u8VerNum != stMGT.astEttItem[pParse->u8Tbl].table_type_version_number)
    {
        EIT_DBG(ETT_CHECK,  ("Wrong VN = %bX\n", pParse->u8VerNum));
        return FALSE;
    }
#endif

    // Byte 6 & 7 - Verify section_number and last_section_number
    //ATSC standard section number& last section number shall be 0x00 because Ett is only one section long
    if ((pParse->u8SecNum != 0) || (pParse->u8LastSecNum != 0))
    {
        EIT_DBG(ETT_CHECK,  ("Wrong SN = %bX, LSN = %bX\n", pParse->u8SecNum, pParse->u8LastSecNum));
        return FALSE;
    }

    // Byte 8 - Verify protocol_version
    if (pParse->u8ProtocolVer != 0)
    {
        EIT_DBG(ETT_CHECK,  ("Wrong PV = %bX\n", pParse->u8ProtocolVer));
        return FALSE;
    }

    stEpgDBInfo.au16CntEttRpt[pParse->u8Tbl]++;
    // ETT Overflow ?
    if(stEpgDBInfo.au16CntEttRpt[pParse->u8Tbl] >= Max_NUM_OF_REPEAT_ETT)
    //if (stEpgDBInfo.au16CntEttRpt[pParse->u8Tbl] >= 20)
    {
        SETBIT (stEpgDBInfo.u8EttRxOK, stEpgDBInfo.u8EttCntFID);
        CLRBIT (stEpgDBInfo.u8EttIsReceiving, stEpgDBInfo.u8EttCntFID);
        msAPI_DMX_CloseFilter(stEpgDBInfo.au8EttFID[pParse->u8Tbl]);
        stEpgDBInfo.au8EttFID[pParse->u8Tbl] = MSAPI_DMX_INVALID_FLT_ID;
        stEpgDBInfo.au16CntEttRpt[pParse->u8Tbl] = 0;
        EIT_DBG(ETT_CHECK,  ("EPG >> ETT Repeat overflow in table [%d], [%d]\r\n", pParse->u8Tbl, stEpgDBInfo.u8CntFID));
        // Receive all ETT table ?
        if(stEpgDBInfo.u8EttRxOK == MAX_TBL_MASK)
        {
            EIT_DBG(ETT_CHECK,  ("EPG >> Receive all ETT table\n"));
            stEpgDBInfo.u8EttCntFID = 0;
            for (iu8Loop_i = 0; iu8Loop_i < MAX_TBL_NUM; iu8Loop_i++)
            {
                stEpgDBInfo.au8EttFID[iu8Loop_i] = MSAPI_DMX_INVALID_FLT_ID;
            }

            for (iu8Loop_i = 0; iu8Loop_i<stEpgDBInfo.u8CntSourceNum; iu8Loop_i++)
            {
                astEpgDbVchMask[iu8Loop_i].fIsInSDRAM = TRUE;
                stEpgDBInfo.u8EttIsReceiving = 0x00;
            }
        }
    }


    // Byte 9 & 10 - Verify ETM_id (source_id)
    for (u8_loop_i=0; u8_loop_i<stEpgDBInfo.u8CntSourceNum; u8_loop_i++)
    {
        if (pParse->u16SrcID == stEpgDBInfo.au16SrcID[u8_loop_i])
        {
            // Channel ETM_id ?
            if (pParse->u16EventID == 0x00)
            {
                EIT_DBG(ETT_CHECK,  ("Event ID = 0\n"));
                return FALSE;
            }
            else
            {
                pParse->u8SrcIdx = u8_loop_i;
                pParse->u16EventID = pParse->u16EventID >> 2;
                return TRUE;
            }
        }
    }

    EIT_DBG(ETT_CHECK,  ("End of ETT Check\n"));
    return FALSE;
}

/*****************************************************************************/
static void MApp_Dmx_ETT_All_Parse (U8 pu8Sec4K[])
{
    // Local variable declaration
    MS_EIT_PARSE_PARAM_ATSC      *pParse;
    MS_EPG_VCH_BUF          *pVch;
    MS_EPG_EVENT            *pEvent;
    U8                      *pu8LoopPosition;
    U16      				u16_text_length;
    MS_EPG_EVENT_ETT 		pSrcEventETT;

    pParse = &stEitParseParam;

    pVch = &astEpgDbVchBuf[pParse->u8SrcIdx];
    pVch->u8SrcIdx = pParse->u8SrcIdx;

    pu8LoopPosition = MApp_Dmx_FindFirstLoop(pu8Sec4K, EN_ETT);

    pEvent = MApp_Dmx_ETT_All_Find_Match_Event(pVch, pParse->u16EventID);

    // Find match event
    if (pEvent != NULL)
    {
        if (pEvent->u16DbEttPos == NULL)
        {
			u16_text_length= MApp_Dmx_Parse_MSS (pu8EpgString, pu8LoopPosition,sizeof(pu8EpgString), DISABLE)-2;

            pEvent->fIsEttUTF16 = g_fIsUTF16;
            // String pool is oveflow for this service buffer?
            if ((pVch->u16DBOffsetETT + u16_text_length) > MAX_ETT_LEN_OF_STR_POOL)
            {
                pEvent->u16DbEttPos = 0; //Show Overflow
                EIT_DBG(ETT_PARSE,  ("=== EPG: Event Pool Overflow @ u8SrcIdx#%d ===\r\n", pVch->u8SrcIdx));
            }
            else if(u16_text_length > 2)
            {
            	pSrcEventETT.u16ETT_length = u16_text_length -2;
                pEvent->u16DbEttPos = pVch->u16DBOffsetETT;
                pSrcEventETT.pu8ETT_content = &pu8EpgString[2];
                MApp_EpgDB_SaveEventETT(pParse->u8SrcIdx, pVch->u16DBOffsetETT, &pSrcEventETT);
                pVch->u16DBOffsetETT += u16_text_length ;
            }
            else
            {
            #if SUPPORT_LONG_ETT

                pEvent->u16DbEttPos = pVch->u16DBOffsetETT;
				pSrcEventETT.u16ETT_length = 0; //0x04;
				//strcpy((char *)(&pu8EpgString[0]), " "); //"Null");
				pSrcEventETT.pu8ETT_content = &pu8EpgString[0];
                MApp_EpgDB_SaveEventETT(pParse->u8SrcIdx, pVch->u16DBOffsetETT, &pSrcEventETT);
				pVch->u16DBOffsetETT += 2;//u16_text_length ;
            #else
				pSrcEventETT.u16ETT_length = 0x01; //0x04;
                pEvent->u16DbEttPos = pVch->u16DBOffsetETT;
				strcpy((char *)(&pu8EpgString[0]), " "); //"Null");
				pSrcEventETT.pu8ETT_content = &pu8EpgString[0];
                MApp_EpgDB_SaveEventETT(pParse->u8SrcIdx, pVch->u16DBOffsetETT, &pSrcEventETT);
				pVch->u16DBOffsetETT += u16_text_length ;
            #endif
            }

            MApp_EpgDB_SaveEvent(pParse->u8SrcIdx, pParse->u8Tbl, pParse->u8EventIdx, pEvent);

          #if (EIT_DEBUG&ETT_PARSE)
            MApp_EpgDB_LoadEvent(pParse->u8SrcIdx, pParse->u8Tbl, pParse->u8EventIdx, &g_stUiEvent);
            EIT_DBG(ETT_PARSE, ("\nETT LoadEvent >> (x, y, z)= (%d, %d, %d)\r\n", pParse->u8SrcIdx, pParse->u8Tbl, pParse->u8EventIdx));
            EIT_DBG(ETT_PARSE, ("ETT LoadEvent>> Eid = 0x%X, Start time = 0x%lX\n", (U16)g_stUiEvent.event_id, g_stUiEvent.start_time));

            pSrcEventETT.pu8ETT_content = au8EpgUiBuf;

            MApp_EpgDB_LoadEventETT(pParse->u8SrcIdx, g_stUiEvent.u16DbEttPos, &pSrcEventETT, sizeof(au8EpgUiBuf) );

            //au8EpgUiBuf[pSrcEventETT.u16ETT_length] = '\0';
            EIT_DBG(ETT_PARSE, ("ETT = \"%s\"\r\n\n", au8EpgUiBuf));
          #endif

        }
    }
}
#endif
#endif
/******************************************************************************/
void MApp_Dmx_EIT_Cb(U8 u8FID, DMX_EVENT enEvent)
{
    U32 u32ActualSize,u32RmnSize;
    //stEitParseParam.u8Tbl = au8FID2ItemIdx[u8FID];
    MSAPI_DMX_FILTER_STATUS enStatus;
    enStatus=(MSAPI_DMX_FILTER_STATUS)enEvent;


    // [1] Check enStatus
    switch(enStatus)
    {
        case MSAPI_DMX_FILTER_STATUS_SECAVAILABLE:
        {
            // Get Section Data
            if(MApi_DMX_CopyData(u8FID, au8Section, MSAPI_DMX_SECTION_4K,&u32ActualSize,&u32RmnSize,NULL) == DMX_FILTER_STATUS_OK)
            {
                EIT_DBG(EIT_CB, ("\r\n=== [ Filter ID = %d ]  [ Source ID = %u ] [ Tabld ID = %bX]  [stEitParseParam.u8Tbl = %d]===", u8FID, (U16)(au8Section[3]<<8 | au8Section[4]), au8Section[0],stEitParseParam.u8Tbl));
                EIT_DBG(EIT_CB, ("\nSN %3bu \tLSN %3bu \tPV %3bu \tNum_Events_In_Sec %3bu  ===\r\n", au8Section[6] , au8Section[7]    , au8Section[8], au8Section[9]));

                if(msAPI_DMX_CheckCRC32(au8Section) == FALSE)
                {
                    EIT_DBG(EIT_CB,  ("[FID=%d] EIT CB - get section check CRC error!! Case 1\n", u8FID));
                    enStatus = MSAPI_DMX_FILTER_STATUS_CRCINCORRECT;
                    break;
                }

                if (au8Section[0] == TID_EIS) // EIT
                {
                    //stEitParseParam.u8Tbl = au8EitFID2ItemIdx[u8FID];
                    stEitParseParam.u8Tbl = MApp_Dmx_Eit_Get_EitTblIdx_By_FilterId(u8FID);
                    if( stEitParseParam.u8Tbl >= PSIP_EIT_TABLE_NUMBER)
                    {
                        printf("\nError: Eit tbl idx invalid = %u , u8FID=%u\n", stEitParseParam.u8Tbl, u8FID);
                        break;
                    }

                    //printf ("\r\n=== [ Filter ID = %d ]  [ Source ID = %u ] [ Tabld ID = %bX] ===", u8FID, (U16)(au8Section[3]<<8 | au8Section[4]), au8Section[0]);
                    //printf ("\nSN %3bu \tLSN %3bu \tPV %3bu \tNum_Events_In_Sec %3bu  ===\r\n", au8Section[6] , au8Section[7]    , au8Section[8], au8Section[9]);

                    if (MApp_Dmx_EIT_Check(&stEitParseParam, au8Section) == TRUE)
                    {
                #if (ENABLE_ATSC_EPG_DB_2016)
                        MApp_Dmx_EIT_Parse_NewDB(&stEitParseParam, au8Section);
                        MApp_Dmx_EIT_Set_Flag_NewDB(&stEitParseParam);
                #else
                        MApp_Dmx_EIT_Parse(&stEitParseParam, au8Section);
                        MApp_Dmx_EIT_Set_Flag(&stEitParseParam);
                #endif
                    }

                }
                else if(au8Section[0] == TID_ETS) // ETT
                {
                #if (MONITOR_ETT_ALL)
                    //stEitParseParam.u8Tbl = au8EttFID2ItemIdx[u8FID];
                    stEitParseParam.u8Tbl = MApp_Dmx_Ett_Get_EttTblIdx_By_FilterId(u8FID);
                    if( stEitParseParam.u8Tbl >= PSIP_ETT_TABLE_NUMBER)
                    {
                        printf("\nError: Ett tbl idx invalid = %u , u8FID=%u\n", stEitParseParam.u8Tbl, u8FID);
                        break;
                    }

                    //printf ("\r\n=== [ Filter ID = %d ] [ Tabld ID = 0x%bX] ===", u8FID, au8Section[0]);
                    //printf ("\r\n=== [ ETM_id = %bx>> SrcID = 0x%04X, Eid = 0x%04X ===\r\n", (au8Section[9]<<24 | au8Section[10] << 16 | (au8Section[11]<<8 | au8Section[12])), (U16)(au8Section[9]<<8 | au8Section[10]), (U16)((au8Section[11]<<8 | au8Section[12])>>2));

                #if(ENABLE_ATSC_EPG_DB_2016)
                    if (MApp_Dmx_ETT_All_Check_NewDB(&stEitParseParam, au8Section) == TRUE)
                    {
                        //printf("Check ok!\n");
                        MApp_Dmx_ETT_Parse_NewDB(au8Section);
                    }

                    //MApp_PrintEttReceived();
                #else
                    if (MApp_Dmx_ETT_All_Check(&stEitParseParam, au8Section) == TRUE)
                    {
                        MApp_Dmx_ETT_All_Parse (au8Section);
                    }
                #endif

            #endif
                }
                else
                {
                    printf("\nWarning: au8Section[0]=0x%X is not EIT or ETT , u8FID=%u\n", au8Section[0], u8FID);
                    break;
                }

            }
            else
            {
                EIT_DBG(EIT_CB, ("[FID=%d] EIT CB - copy section fail!! \r\n", u8FID));
            }

            break;
        }

    #if (!ENABLE_NEW_DMX_INTERFACE)
        case MSAPI_DMX_FILTER_STATUS_OVERFLOW:
        {
            EIT_DBG(EIT_CB, ("[FID=%d] EIT CB - get section ring buffer is overflow !\r\n", u8FID));
            break;
        }
    #endif


#if(ENABLE_ATSC_EPG_DB_2016)
        //ATSC-050.trp stream Ett-0 will time out.... this stream Mgt have Ett-0 pid by no any callback of Ett-0
        case MSAPI_DMX_FILTER_STATUS_TIMEOUT:
        {
            U8 u8MatchByte0 = msAPI_DMX_GetMatchByte_ByFid(u8FID);
            printf("[FID=%d] time out\n", u8FID);
            if(u8MatchByte0 == TID_EIS)
            {
               stEitParseParam.u8Tbl = MApp_Dmx_Eit_Get_EitTblIdx_By_FilterId(u8FID);
               msAPI_DMX_CloseFilter(stEpgDBInfo.au8FID[stEitParseParam.u8Tbl]);
               stEpgDBInfo.au8FID[stEitParseParam.u8Tbl] = MSAPI_DMX_INVALID_FLT_ID;

               _MApp_EIT_SetBit(&stEpgDBInfo.u8EitRxOKNew[0], stEitParseParam.u8Tbl);
               _MApp_EIT_ClrBit(&stEpgDBInfo.u8EitIsReceivingNew[0], stEitParseParam.u8Tbl);
                printf("Timeout:::Close Eit-%d filter \n", stEitParseParam.u8Tbl);
            }
            else if(u8MatchByte0 == TID_ETS)
            {
                stEitParseParam.u8Tbl = MApp_Dmx_Ett_Get_EttTblIdx_By_FilterId(u8FID);
                msAPI_DMX_CloseFilter(stEpgDBInfo.au8EttFID[stEitParseParam.u8Tbl]);
                stEpgDBInfo.au8EttFID[stEitParseParam.u8Tbl] = MSAPI_DMX_INVALID_FLT_ID;
                _MApp_EIT_SetBit(&stEpgDBInfo.u8EttRxOKNew[0], stEitParseParam.u8Tbl);
                _MApp_EIT_ClrBit(&stEpgDBInfo.u8EttIsReceivingNew[0], stEitParseParam.u8Tbl);
                printf("Timeout:::Close Ett-%d filter \n", stEitParseParam.u8Tbl);
            }

            msAPI_DMX_Print_AllFilter();
        }
        break;
#endif

    // To Do: Need to modify and verify after, 2009/04/03
    #if (!ENABLE_NEW_DMX_INTERFACE)
        case MSAPI_DMX_FILTER_STATUS_TIMEOUT:
        {
            if (stEpgDBInfo.u8EitRxOK != MAX_TBL_MASK)        // EIT
            {
                SETBIT (stEpgDBInfo.u8EitRxOK, stEitParseParam.u8Tbl);
                CLRBIT (stEpgDBInfo.u8EitIsReceiving, stEitParseParam.u8Tbl);
            }
        #if (MONITOR_ETT_ALL)
            else                                    // ETT
            {
                SETBIT (stEpgDBInfo.u8EttRxOK, stEitParseParam.u8Tbl);
                CLRBIT (stEpgDBInfo.u8EttIsReceiving, stEitParseParam.u8Tbl);

                // Receive all EIT table ?
                if (stEpgDBInfo.u8EttRxOK == MAX_TBL_MASK)
                {
                    EIT_DBG(EIT_CB, ("EPG >> Receive all ETT table\n"));
                    stEpgDBInfo.u8CntFID = 0;

                    for (iu8Loop_i = 0; iu8Loop_i<stEpgDBInfo.u8CntSourceNum; iu8Loop_i++)
                    {
                        astEpgDbVchMask[iu8Loop_i].fIsInSDRAM = TRUE;
                        stEpgDBInfo.u8EttIsReceiving = 0x00;
                    }
                }
            }
        #endif
            msAPI_DMX_CloseFilter(stEpgDBInfo.au8FID[stEitParseParam.u8Tbl]);
            stEpgDBInfo.au8FID[stEitParseParam.u8Tbl] = MSAPI_DMX_INVALID_FLT_ID;
            EIT_DBG(EIT_CB, ("[FID=%d] EIT CB - get section timeout!!\r\n", u8FID));
            break;
        }

    #endif

    #if (!ENABLE_NEW_DMX_INTERFACE)
        case MSAPI_DMX_FILTER_STATUS_CRCINCORRECT:
        {
            EIT_DBG(EIT_CB, ("[FID=%d] EIT CB - get section check CRC error!! \r\n", u8FID));
            break;
        }
    #endif
        default:
        {
            EIT_DBG(EIT_CB, ("[FID=%d] EIT CB - get section unknow error, enStatus = %d!! \r\n", u8FID, (U8)enStatus));
            break;
        }
    }

    // [2] Condition handle
    if ((enStatus != MSAPI_DMX_FILTER_STATUS_SECAVAILABLE) && (enStatus != MSAPI_DMX_FILTER_STATUS_TIMEOUT))
    {
        msAPI_DMX_RestartFilter(u8FID);
        EIT_DBG(EIT_CB, ("=== EIT CB - Restart Filter %d ===\r\n", u8FID));
    }
}

#if (MONITOR_ETT_ALL)
#if(!ENABLE_ATSC_EPG_DB_2016)
void MApp_Dmx_EIT_Set_DemuxFilter(U16 u16_pid, U8 u8_table_id)
{
    MS_DMX_SECTIONMONITOR_PARA   stSectionMonitor;

    // Set all mask byte to 0xFF (Don't Care)
    memset(stSectionMonitor.au8MaskByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);
    memset(stSectionMonitor.au8NotMatchByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);

    // Set EIT table PID
    stSectionMonitor.u16PID             = u16_pid;      // Table PID
    stSectionMonitor.u32SectionFltType  = MSAPI_DMX_FILTER_TYPE_SECTION_4K;
    stSectionMonitor.au8MatchByte[0]    = u8_table_id;  // Table ID
    stSectionMonitor.au8MaskByte[0]     = 0xFF;
    stSectionMonitor.au8MatchByte[5]     = 0x01;         // reserved [7:6] + version_number [5:1] + current_next_indicator [0]
    stSectionMonitor.au8MaskByte[5]     = 0x01;
    stSectionMonitor.au8MatchByte[8]    = 0x00;         // protocol_version
    stSectionMonitor.au8MaskByte[8]     = 0xFF;
    stSectionMonitor.SectMode           = DMX_SECT_MODE_CONTI|DMX_SECT_MODE_CRCCHK;
    // Set Callback Function, Global Filter ID and Continuous mode
    stSectionMonitor.pfNotify           = MApp_Dmx_EIT_Cb;

    if (u8_table_id == TID_EIS)
    {
        stSectionMonitor.au8MatchByte[3]    = HIGHBYTE(stEpgDBInfo.au16SrcID[0]);   // High byte of source_id
        stSectionMonitor.au8MaskByte[3]     = 0xFF;
        stSectionMonitor.au8MatchByte[4]    = LOWBYTE(stEpgDBInfo.au16SrcID[0]);    // Low byte of source_id
        stSectionMonitor.au8MaskByte[4]     = 0xFF;
        stSectionMonitor.pu8FID             = &stEpgDBInfo.au8FID[stEpgDBInfo.u8CntFID];
        if (stEpgDBInfo.u8CntFID == 0)
        {
            stSectionMonitor.u16TimeoutMilliSec = EIT_0_TIMEOUT;

        }
        else if (stEpgDBInfo.u8CntFID == 1)
        {
            stSectionMonitor.u16TimeoutMilliSec = EIT_1_TIMEOUT;
        }
        else
        {
            stSectionMonitor.u16TimeoutMilliSec = EIT_TIMEOUT;
        }

        EIT_DBG(EIT_MONITOR, ("\nEPG: Set EIT Source ID to %u\n", stEpgDBInfo.au16SrcID[0]));
    }
    else
    {
        #if 0                                           // comment out for non-standard stream
        stSectionMonitor.au8MatchByte[3]    = 0x00;     // ETT_table_id_extension - should be 0x0000
        stSectionMonitor.au8MaskByte[3]     = 0x00;
        stSectionMonitor.au8MatchByte[4]    = 0x00;
        stSectionMonitor.au8MaskByte[4]     = 0x00;
        stSectionMonitor.au8MatchByte[6]    = 0x00;     // section_number
        stSectionMonitor.au8MaskByte[6]     = 0x00;
        stSectionMonitor.au8MatchByte[7]    = 0x00;     // last_section_number
        stSectionMonitor.au8MaskByte[7]     = 0x00;
        #endif
        stSectionMonitor.au8MatchByte[9]     = HIGHBYTE(stEpgDBInfo.au16SrcID[0]);
        stSectionMonitor.au8MaskByte[9]      = 0xFF;
        stSectionMonitor.au8MatchByte[10]    = LOWBYTE(stEpgDBInfo.au16SrcID[0]);
        stSectionMonitor.au8MaskByte[10]     = 0xFF;
        stSectionMonitor.pu8FID             = &stEpgDBInfo.au8EttFID[stEpgDBInfo.u8EttCntFID];
    }

    // Set filter
    if(msAPI_DMX_SectionMonitor(&stSectionMonitor, FALSE) == DMX_FILTER_STATUS_OK)
    {
        if (u8_table_id == TID_EIS)
        {
            if (stEpgDBInfo.u8EitRxOK != MAX_TBL_MASK)
            {
                SETBIT (stEpgDBInfo.u8EitIsReceiving, stEpgDBInfo.u8CntFID);
            }
            au8FID2ItemIdx[(stEpgDBInfo.au8FID[stEpgDBInfo.u8CntFID])] = stEpgDBInfo.u8CntFID;
            stEpgDBInfo.u8CntFID++;
        }
        else if(u8_table_id == TID_ETS)
        {
            if (stEpgDBInfo.u8EttRxOK != MAX_TBL_MASK)
            {
                SETBIT(stEpgDBInfo.u8EttIsReceiving, stEpgDBInfo.u8EttCntFID);
            }
            //au8EttFID2ItemIdx[(stEpgDBInfo.au8EttFID[stEpgDBInfo.u8EttCntFID])] = stEpgDBInfo.u8EttCntFID;
            stEpgDBInfo.u8EttCntFID++;
        }
    }
    else
    {
        EIT_DBG(EIT_MONITOR, ("EPG: monitor EIT fail!! \r\n"));
    }
}


/*****************************************************************************/
void MApp_Dmx_EIT_Set_Demux(void)
{
    U16    u16_pid;
    U8    u8_table_id;
    U8    u8i = 0;   //
    MS_DMX_SECTIONMONITOR_PARA   stSectionMonitor;

    // Check MGT or monitor EIT timer is timeout
    if(stMGT.version_number != INVALID_VERSION_NUM)
    {
        #if (!ENABLE_NEW_DMX_INTERFACE)
        // Is there a free 4K filter ID?
        if (msAPI_DMX_GetFree4KFilterNo())        // Got a free filter ID
        #endif
        {
            for(u8i=0; u8i< BASIC_TBL_NUM ;u8i++)
            {
                if(stEpgDBInfo.u8EitRxOK != MAX_TBL_MASK)
                {
                    u16_pid = stMGT.astEitItem[stEpgDBInfo.u8CntFID].table_type_PID;
                    u8_table_id = TID_EIS;
                    if (u16_pid == 0)
                    {
                        SETBIT (stEpgDBInfo.u8EitRxOK, stEpgDBInfo.u8CntFID);
                    }
                }
                else
                {
                    if(u8CheckEit0_3Received ==1)
                    {
                        stEpgDBInfo.u8CntFID = 0;
                        u8CheckEit0_3Received = 0;
                    }
                    u16_pid = stMGT.astEttItem[stEpgDBInfo.u8CntFID].table_type_PID;
                    u8_table_id = TID_ETS;
                }

                // Not set filter yet
                if((stEpgDBInfo.au8FID[stEpgDBInfo.u8CntFID] == MSAPI_DMX_INVALID_FLT_ID) && (u16_pid != 0))
                {
                    // Set all mask byte to 0xFF (Don't Care)
                    memset(stSectionMonitor.au8MaskByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);
                    memset(stSectionMonitor.au8NotMatchByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);

                    // Set EIT table PID
                    stSectionMonitor.u16PID             = u16_pid;      // Table PID
                    stSectionMonitor.u32SectionFltType     = MSAPI_DMX_FILTER_TYPE_SECTION_4K;
                    stSectionMonitor.au8MatchByte[0]     = u8_table_id;  // Table ID
                    stSectionMonitor.au8MaskByte[0]     = 0xFF;

                    if (u8_table_id == TID_EIS)
                    {
    //                    #if (EPG_THIS_CH == TRUE)                       // Source ID    - Don't care
                        stSectionMonitor.au8MatchByte[3]    = HIGHBYTE(stEpgDBInfo.au16SrcID[0]);   // High byte of source_id
                        stSectionMonitor.au8MaskByte[3]     = 0xFF;
                        stSectionMonitor.au8MatchByte[4]    = LOWBYTE(stEpgDBInfo.au16SrcID[0]);    // Low byte of source_id
                        stSectionMonitor.au8MaskByte[4]     = 0xFF;
                        EIT_DBG(EIT_MONITOR, ("\nEPG: Set EIT Source ID to %u\n", stEpgDBInfo.au16SrcID[0]));
    //                    #endif
                    }
                    else
                    {
    //                    #if (EPG_THIS_CH == TRUE)                       // Source ID    - Don't care
                        stSectionMonitor.au8MatchByte[9]     = HIGHBYTE(stEpgDBInfo.au16SrcID[0]);
                        stSectionMonitor.au8MaskByte[9]     = 0xFF;
                        stSectionMonitor.au8MatchByte[10]     = LOWBYTE(stEpgDBInfo.au16SrcID[0]);
                        stSectionMonitor.au8MaskByte[10]     = 0xFF;
                        EIT_DBG(EIT_MONITOR, ("\nEPG: Set ETT Source ID to %u\n", stEpgDBInfo.au16SrcID[0]));
    //            #endif
                    }

                    stSectionMonitor.au8MatchByte[5]     = 0x01;         // reserved [7:6] + version_number [5:1] + current_next_indicator [0]
                    stSectionMonitor.au8MaskByte[5]     = 0x01;
                    stSectionMonitor.au8MatchByte[8]    = 0x00;         // protocol_version
                    stSectionMonitor.au8MaskByte[8]     = 0xFF;


                    // Set Callback Function, Global Filter ID and Continuous mode
                    stSectionMonitor.pfNotify             = MApp_Dmx_EIT_Cb;
                    stSectionMonitor.pu8FID             = &stEpgDBInfo.au8FID[stEpgDBInfo.u8CntFID];
                    stSectionMonitor.SectMode           = DMX_SECT_MODE_CONTI|DMX_SECT_MODE_CRCCHK;

                    // Set Timeout
                    if (u8_table_id == TID_EIS)
                    {
                        if (stEpgDBInfo.u8CntFID == 0)
                        {
                            stSectionMonitor.u16TimeoutMilliSec = EIT_0_TIMEOUT;
                        }
                        else if (stEpgDBInfo.u8CntFID == 1)
                        {
                            stSectionMonitor.u16TimeoutMilliSec = EIT_1_TIMEOUT;
                        }
                        else
                        {
                            stSectionMonitor.u16TimeoutMilliSec = EIT_TIMEOUT;
                        }
                    }
                    else
                    {
                        stSectionMonitor.u16TimeoutMilliSec = ETT_TIMEOUT;
                    }

                    EIT_DBG(EIT_MONITOR, ("EPG: Set table ID [%bX], PID to %x, Filter ID Count = %d\n", u8_table_id, u16_pid, stEpgDBInfo.u8CntFID));

                    // Set filter
                    if(msAPI_DMX_SectionMonitor(&stSectionMonitor, FALSE) == DMX_FILTER_STATUS_OK)
                    {
                        EIT_DBG(EIT_MONITOR, ("EPG: Set EIT to Filter #%d \r\n", stEpgDBInfo.au8FID[stEpgDBInfo.u8CntFID]));

                        if (stEpgDBInfo.u8EitRxOK != MAX_TBL_MASK)
                        {
                            SETBIT (stEpgDBInfo.u8EitIsReceiving, stEpgDBInfo.u8CntFID);
                        }
                        else
                        {
                            SETBIT (stEpgDBInfo.u8EttIsReceiving, stEpgDBInfo.u8CntFID);
                        }

                        au8FID2ItemIdx[(stEpgDBInfo.au8FID[stEpgDBInfo.u8CntFID])] = stEpgDBInfo.u8CntFID;
                        stEpgDBInfo.u8CntFID++;
                    }
                    else
                    {
                        EIT_DBG(EIT_MONITOR, ("EPG: monitor EIT fail!! \r\n"));
                    }
                }
                else    // Already set filter
                {
                    EIT_DBG(EIT_MONITOR, ("EPG: monitoring EIT at Filter #%d, Pid=%x, Tbl_id-%bx \r\n", stEpgDBInfo.au8FID[stEpgDBInfo.u8CntFID], u16_pid, u8_table_id));

                    if (stEpgDBInfo.u8CntFID < (MAX_TBL_NUM-1))
                    {
                        stEpgDBInfo.u8CntFID++;
                    }
                }
            }
        }
    }
}
#endif

#endif
#if (EIT_VN_CHANGE_FOR_RRT==TRUE)
/*****************************************************************************/
static void MApp_Dmx_EIT_For_RRT_Parse(U8 *pu8Section)
{
    U8 version_number;

    version_number = (pu8Section[5]>>1)&0x1f;
    if(version_number != stMGT.astEitItem[0].table_type_version_number)
    {
        printf("EIT For RRT VN Change >> cur = 0x%X, old = 0x%X\n", version_number, stMGT.astEitItem[0].table_type_version_number);

        stMGT.astEitItem[0].table_type_version_number = version_number;

        MApp_EpgDB_Reset();

        MApp_EPG_Demux_Reset();

    #if (ENABLE_ATSC_EPG_DB_2016)
        //memset(&(stEitParseParam.u8EitSaveIndex[0]), 0, sizeof(U8)*NEW_MAX_TAB_NUM);
    #else
        memset(&(stEitParseParam.u8EitSaveIndex[0]), 0, sizeof(U8)*MAX_TBL_NUM);
    #endif

#if 1 // Move to MApp_EPG_Demux_Reset()
#if( ENABLE_ATSC_EPG_DB_2016 )
        //stEpgDBInfo.u8CntFID = 0;
        //stEpgDBInfo.u8EttCntFID = 0;
#else
    #if (MAX_TBL_NUM > BASIC_TBL_NUM)
        //initial fid count for eit monitor when eit version change
        //stEpgDBInfo.u8CntFID = 0;
        //stEpgDBInfo.u8EttCntFID = 0;
        for (iu8Loop_i = 0; iu8Loop_i<stEpgDBInfo.u8CntSourceNum; iu8Loop_i++)
        {
        #if( !ENABLE_ATSC_EPG_DB_2016 )
            astEpgDbVchMask[iu8Loop_i].fIsInSDRAM = TRUE;
        #endif
            stEpgDBInfo.u8EitIsReceiving = 0x00;
            stEpgDBInfo.u8EttIsReceiving = 0x00;
        }
    #endif
#endif
#endif
    }
}
/******************************************************************************/
void MApp_Dmx_EIT_For_RRT_Cb(U8 u8FID, DMX_EVENT enEvent)
{
    U32 u32ActualSize,u32RmnSize;
    MSAPI_DMX_FILTER_STATUS enStatus;
    enStatus=(MSAPI_DMX_FILTER_STATUS)enEvent;

    // [1] Check enStatus
    switch(enStatus)
    {
        case MSAPI_DMX_FILTER_STATUS_SECAVAILABLE:
        {
            // Get Section Data
            if(MApi_DMX_CopyData(u8FID, au8Section, MSAPI_DMX_SECTION_4K,&u32ActualSize,&u32RmnSize,NULL) == DMX_FILTER_STATUS_OK)
            {
                if(msAPI_DMX_CheckCRC32(au8Section) == TRUE)
                {
                    MApp_Dmx_EIT_For_RRT_Parse(au8Section);

                    break;
                }
            }
            msAPI_DMX_RestartFilter(u8FID);

            break;
        }

    #if (!ENABLE_NEW_DMX_INTERFACE)
        case MSAPI_DMX_FILTER_STATUS_TIMEOUT:
        {
            msAPI_DMX_CloseFilter(u8FID);
            stEpgDBInfo.u8FID_EitMonitorForRRT = MSAPI_DMX_INVALID_FLT_ID;
            printf ("[FID=%d] EIT CB - get section timeout!!\r\n", u8FID);
            break;
        }
    #endif
        default:
        {
            msAPI_DMX_RestartFilter(u8FID);
            printf ("[FID=%d] enStatus = %d EIT CB - Default - Restart Filter\r\n", u8FID, (U8)enStatus);
            break;
        }
    }
}
void MApp_Dmx_EIT_For_RRT_Monitor(void)
{
    U16 u16_pid;
    MS_DMX_SECTIONMONITOR_PARA   stSectionMonitor;

    if((MApp_Dmx_GetEitFreeFilter() > 0 )&&(msAPI_DMX_Get_FreeSec4KFilterCount()>0))
    {
        u16_pid     = stMGT.astEitItem[0].table_type_PID;

        // Not set filter yet
        if((stEpgDBInfo.u8FID_EitMonitorForRRT == MSAPI_DMX_INVALID_FLT_ID) && (u16_pid != 0))
        {
            // Set all mask byte to 0xFF (Don't Care)
            memset(stSectionMonitor.au8MaskByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);
            memset(stSectionMonitor.au8NotMatchByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);


            // Set EIT table PID
            stSectionMonitor.u16PID             = u16_pid;      // Table PID
            stSectionMonitor.u32SectionFltType   = MSAPI_DMX_FILTER_TYPE_SECTION_4K;
            stSectionMonitor.au8MatchByte[0]    = TID_EIS;  // Table ID
            stSectionMonitor.au8MaskByte[0]     = 0xFF;

//            #if (EPG_THIS_CH == TRUE)                       // Source ID    - Don't care
            stSectionMonitor.au8MatchByte[3]    = HIGHBYTE(stEpgDBInfo.au16SrcID[0]);   // High byte of source_id
            stSectionMonitor.au8MaskByte[3]     = 0xFF;
            stSectionMonitor.au8MatchByte[4]    = LOWBYTE(stEpgDBInfo.au16SrcID[0]);    // Low byte of source_id
            stSectionMonitor.au8MaskByte[4]     = 0xFF;
            EIT_DBG(EIT_MONITOR, ("\nEPG: Set EIT Source ID to %u\n", stEpgDBInfo.au16SrcID[0]));
//            #endif

            stSectionMonitor.au8MatchByte[5]    = 0x01;         // reserved [7:6] + version_number [5:1] + current_next_indicator [0]
            stSectionMonitor.au8MaskByte[5]     = 0x01;
            stSectionMonitor.au8MatchByte[8]    = 0x00;         // protocol_version
            stSectionMonitor.au8MaskByte[8]     = 0xFF;

            // Set Callback Function, Global Filter ID and Continuous mode
            stSectionMonitor.pfNotify           = MApp_Dmx_EIT_For_RRT_Cb;
            stSectionMonitor.pu8FID             = &stEpgDBInfo.u8FID_EitMonitorForRRT;
            stSectionMonitor.SectMode           = DMX_SECT_MODE_CONTI|DMX_SECT_MODE_CRCCHK;

            // Set Timeout
            stSectionMonitor.u16TimeoutMilliSec = EIT_0_TIMEOUT;
            EIT_DBG(EIT_MONITOR, ("EPG: Set EIT for RRT PID to %u\n", u16_pid));

            // Set filter
            if(msAPI_DMX_SectionMonitor(&stSectionMonitor, FALSE) == DMX_FILTER_STATUS_OK)
            {
                EIT_DBG(EIT_MONITOR, ("EPG: Set EIT for RRT to Filter #%d \r\n", stEpgDBInfo.au8FID[0]));
            }
            else
            {
                EIT_DBG(EIT_MONITOR, ("EPG: monitor EIT for RRT fail!! \r\n"));
            }
        }
        else    // Already set filter
        {
            //EIT_DBG(EIT_MONITOR, ("EPG: monitoring EIT for RRT at Filter #%d \r\n", stEpgDBInfo.au8FID[0]));
        }
    }
}

#endif

/*****************************************************************************/
void MApp_Dmx_EIT_Monitor(void)
{
    if (stMGT.version_number == INVALID_VERSION_NUM)
    {
        return;
    }

    // Check if there is MGT version change occurred
    if (stEpgDBInfo.u8MgtVersionNumber != stMGT.version_number)
    {
        MApp_EpgDB_Reset();
        MApp_EPG_Demux_Reset();

    #if (ENABLE_ATSC_EPG_DB_2016)
        //memset(&(stEitParseParam.u8EitSaveIndex[0]), 0, sizeof(U8)*NEW_MAX_TAB_NUM);
    #else
        memset(&(stEitParseParam.u8EitSaveIndex[0]), 0, sizeof(U8)*MAX_TBL_NUM);
    #endif
    }

#if (MONITOR_ETT_ALL)
#if (ENABLE_ATSC_EPG_DB_2016)
    _MApp_Dmx_EIT_Monitor_NewDB();

#else
    #if (EIT_VN_CHANGE_FOR_RRT)
        #if (MAX_TBL_NUM > BASIC_TBL_NUM)
        if ((stEpgDBInfo.u8EitRxOK & BASIC_TBL_MASK) == BASIC_TBL_MASK)
        {
            MApp_Dmx_EIT_For_RRT_Monitor();
        }
        #endif
    #endif

    // Not set all filter ID to EIT
    if ((stEpgDBInfo.u8CntFID < MAX_TBL_NUM) ||(stEpgDBInfo.u8EttCntFID < MAX_TBL_NUM))
    {
    #if (EIT_VN_CHANGE_FOR_RRT==FALSE)
        if ((stEpgDBInfo.u8EitRxOK == MAX_TBL_MASK) && (stEpgDBInfo.u8EttRxOK == MAX_TBL_MASK))
        {
            return;
        }
        else
        {
            MApp_Dmx_EIT_Set_Demux();
        }
    #else
        if (stEpgDBInfo.u8EitRxOK == MAX_TBL_MASK)
        {
        #if (MAX_TBL_NUM <= BASIC_TBL_NUM)
            MApp_Dmx_EIT_For_RRT_Monitor();
        #endif

            if (stEpgDBInfo.u8EttRxOK == MAX_TBL_MASK)
            {
                return;
            }
            else
            {
                MApp_Dmx_EIT_Set_Demux();
            }
        }
        else
        {
            MApp_Dmx_EIT_Set_Demux();
        }
    #endif

    }
#endif
#else

    // (Not set all filter ID to EIT) && (Not got all EIT)
    if ((stEpgDBInfo.u8CntFID < MAX_TBL_NUM) && (stEpgDBInfo.u8EitRxOK != MAX_TBL_MASK))
    {
        MS_DMX_SECTIONMONITOR_PARA   stSectionMonitor;

        // Check MGT or monitor EIT timer is timeout
        if(stMGT.version_number != INVALID_VERSION_NUM)
        {
            #if (!ENABLE_NEW_DMX_INTERFACE)
            // Is there a free 4K filter ID?
            if (msAPI_DMX_GetFree4KFilterNo())        // Got a free filter ID
            #endif
            {
                // Not set filter yet
                if((stEpgDBInfo.au8FID[stEpgDBInfo.u8CntFID] == MSAPI_DMX_INVALID_FLT_ID)
                && (stMGT.astEitItem[stEpgDBInfo.u8CntFID].table_type_PID != 0))
                {
                    // Set all mask byte to 0xFF (Don't Care)
                    memset(stSectionMonitor.au8MaskByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);
                    memset(stSectionMonitor.au8NotMatchByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);

                    // Set EIT table PID
                    stSectionMonitor.u16PID             = stMGT.astEitItem[stEpgDBInfo.u8CntFID].table_type_PID;
                    stSectionMonitor.enSectionFltType     = MSAPI_DMX_FILTER_TYPE_SECTION_4K;
                    stSectionMonitor.au8MatchByte[0]    = TID_EIS;  // table_id
                    stSectionMonitor.au8MaskByte[0]     = 0xFF;
//                #if (EPG_THIS_CH == TRUE)                           // Source ID    - Don't care
                    stSectionMonitor.au8MatchByte[3]    = HIGHBYTE(stEpgDBInfo.au16SrcID[0]);   // High byte of source_id
                    stSectionMonitor.au8MaskByte[3]     = 0xFF;
                    stSectionMonitor.au8MatchByte[4]    = LOWBYTE(stEpgDBInfo.au16SrcID[0]);    // Low byte of source_id
                    stSectionMonitor.au8MaskByte[4]     = 0xFF;
                    EIT_DBG(EIT_MONITOR, ("\nEPG: << Set EIT Source ID to %u >>\r\n", stEpgDBInfo.au16SrcID[0]));
//                #endif
                    stSectionMonitor.au8MatchByte[5]     = 0x01;     // reserved [7:6] + version_number [5:1] + current_next_indicator [0]
                    stSectionMonitor.au8MaskByte[5]     = 0x01;
                    stSectionMonitor.au8MatchByte[8]    = 0x00;     // protocol_version
                    stSectionMonitor.au8MaskByte[8]     = 0xFF;

                    // Set Callback Function, Global Filter ID and Continuous mode
                    stSectionMonitor.pfNotify             = MApp_Dmx_EIT_Cb;
                    stSectionMonitor.pu8FID             = &stEpgDBInfo.au8FID[stEpgDBInfo.u8CntFID];
                    stSectionMonitor.bOneShot             = FALSE;

                    // Set Timeout
                    if (stEpgDBInfo.u8CntFID == 0)
                    {
                        stSectionMonitor.u16TimeoutMilliSec = EIT_0_TIMEOUT;
                    }
                    else if (stEpgDBInfo.u8CntFID == 1)
                    {
                        stSectionMonitor.u16TimeoutMilliSec = EIT_1_TIMEOUT;
                    }
                    else
                    {
                        stSectionMonitor.u16TimeoutMilliSec = EIT_TIMEOUT;
                    }

                    EIT_DBG(EIT_MONITOR, ("EPG: Set EIT table PID to 0x%x, Filter ID Count = %d\n", stSectionMonitor.u16PID, stEpgDBInfo.u8CntFID));

                    // Set filter
                    if(msAPI_DMX_SectionMonitor(&stSectionMonitor, FALSE) == DMX_FILTER_STATUS_OK)
                    {
                       if(DecompressSetFilterDelay)
                          msAPI_Timer_Delayms(20); //Don't remove this!!for decompressed pgm info stable afte setting DMX filter. -paul
                       SETBIT(stEpgDBInfo.u8EitIsReceiving, stEpgDBInfo.u8CntFID);

                       au8FID2ItemIdx[(stEpgDBInfo.au8FID[stEpgDBInfo.u8CntFID])] = stEpgDBInfo.u8CntFID;
                       stEpgDBInfo.u8CntFID++;
                    }
                    else
                    {
                        printf("EPG: monitor EIT fail!! \r\n");
                    }
                }
                else    // Already set filter
                {
                    EIT_DBG(EIT_MONITOR, ("EPG: monitoring EIT at Filter #%d \r\n", stEpgDBInfo.au8FID[stEpgDBInfo.u8CntFID]));
                }
            }
        }
    }
#endif
}
/******************************************************************************/
#if(!ENABLE_ATSC_EPG_DB_2016)
static void MApp_Dmx_ETT_Parse(U8 pu8ETT[],  U8 pu8Sec4K[])
{
    // Local variable declaration
    MS_EIT_PARSE_PARAM_ATSC      *pParse;
    U8                      *pu8LoopPosition;
#if SUPPORT_LONG_ETT
    MS_EPG_VCH_BUF          *pVch;
#endif

    pParse                     = &stEitParseParam;
    pParse->u8TblID            = pu8Sec4K[0];
    pParse->u16SrcID        = ((U16)pu8Sec4K[9]  << 8 | (U16)pu8Sec4K[10]);
    pParse->u16EventID        = ((U16)pu8Sec4K[11] << 8 | (U16)pu8Sec4K[12]);

#if SUPPORT_LONG_ETT
    UNUSED(pu8ETT);
    pVch = &astEpgDbVchBuf[pParse->u8SrcIdx];
#endif


    msAPI_DMX_CloseFilter(stEpgETT.u8FID);
    stEpgETT.u8FID = MSAPI_DMX_INVALID_FLT_ID;

    pu8LoopPosition = MApp_Dmx_FindFirstLoop(pu8Sec4K, EN_ETT);
#if SUPPORT_LONG_ETT
	U16 u16_text_length= MApp_Dmx_Parse_MSS (pu8EpgString, pu8LoopPosition,sizeof(pu8EpgString), ENABLE)-2;

    g_bFastEttUTF16 = g_fIsUTF16;

    if(u16_text_length > 2)
    {
        g_bIsFastEtt = TRUE;

    #if( !ENABLE_ATSC_EPG_DB_2016 )
        MS_EPG_EVENT_ETT pSrcEventETT;
        pSrcEventETT.u16ETT_length = u16_text_length -2;
        pSrcEventETT.pu8ETT_content = &pu8EpgString[2];
        MApp_EpgDB_SaveEventETT(pParse->u8SrcIdx, pVch->u16DBOffsetETT, &pSrcEventETT);
    #endif

        pVch->u16DBOffsetETT += u16_text_length ;
    }
#else
    //   MApp_Dmx_Parse_MSS (pu8EpgString, pu8LoopPosition);
    MApp_Dmx_Parse_MSS (pu8EpgString, pu8LoopPosition, sizeof(pu8EpgString), DISABLE);
    memcpy(pu8ETT, &pu8EpgString[2], ((U16)pu8EpgString[0]<<8 | (U16)pu8EpgString[1]));
    pu8ETT[((U16)pu8EpgString[0]<<8 | (U16)pu8EpgString[1])] = '\0';

    EIT_DBG(ETT_PARSE, ("ETT >> compressed_strnig_bytes[] = \"%s\"\r\n", pu8ETT));
#endif
    stEpgDBInfo.fIsEttRxOk = TRUE;
}

/******************************************************************************/
void MApp_Dmx_ETT_Cb(U8 u8FID, DMX_EVENT enEvent)
{
    U32 u32ActualSize,u32RmnSize;
    stEitParseParam.u8Tbl = stEpgETT.u8Tbl;
    MSAPI_DMX_FILTER_STATUS enStatus;
    enStatus=(MSAPI_DMX_FILTER_STATUS)enEvent;
    // [1] Check enStatus
    switch(enStatus)
    {
        case MSAPI_DMX_FILTER_STATUS_SECAVAILABLE:
        {
            // (A)    Get Section Data
            if(MApi_DMX_CopyData(u8FID, au8Section, MSAPI_DMX_SECTION_4K,&u32ActualSize,&u32RmnSize,NULL) == DMX_FILTER_STATUS_OK)
            {
                if(msAPI_DMX_CheckCRC32(au8Section) == FALSE)
                {
                      EIT_DBG(ETT_PARSE, ("[FID=%d] ETT CB - get section check CRC error!! Case 1\n", u8FID));
                      enStatus = MSAPI_DMX_FILTER_STATUS_CRCINCORRECT;
                      break;
                }
                EIT_DBG(ETT_PARSE, ("=== [ Filter ID = %2bu ]  [ Source ID = %u ] [ Tabld ID = %bX] [ Event ID = %4X] ===\r\n", u8FID, (U16)(au8Section[9]<<8 | au8Section[10]), au8Section[0], (U16)(au8Section[11]<<8 | au8Section[12])));
            }
            else
            {
                EIT_DBG(ETT_PARSE, ("[FID=%d] EIT CB - copy section fail!! \r\n", u8FID));
                break;
            }
#if SUPPORT_LONG_ETT
            MApp_Dmx_ETT_Parse (NULL , au8Section);
#else
            MApp_Dmx_ETT_Parse (au8ETT , au8Section);
#endif
            break;
        }

    #if (!ENABLE_NEW_DMX_INTERFACE)
        case MSAPI_DMX_FILTER_STATUS_OVERFLOW:
        {
            EIT_DBG(ETT_PARSE, ("[FID=%d] EIT CB - get section ring buffer is overflow !\r\n", u8FID));
            break;
        }

        case MSAPI_DMX_FILTER_STATUS_TIMEOUT:
        {
            msAPI_DMX_CloseFilter(stEpgETT.u8FID);
            stEpgETT.u8FID = MSAPI_DMX_INVALID_FLT_ID;
            //stEpgDBInfo.fIsEttTimeout = TRUE;
            EIT_DBG(ETT_PARSE, ("Close Filter @ Tbl#%d\n", stEitParseParam.u8Tbl));
            EIT_DBG(ETT_PARSE, ("[FID=%d] EIT CB - get section timeout!!\r\n", u8FID));
            break;
        }

        case MSAPI_DMX_FILTER_STATUS_CRCINCORRECT:
        {
            EIT_DBG(ETT_PARSE, ("[FID=%d] EIT CB - get section check CRC error!! \r\n", u8FID));
            break;
        }
    #endif
        default:
        {
            EIT_DBG(ETT_PARSE, ("[FID=%d] EIT CB - get section unknow error, enStatus = %d!! \r\n", u8FID, (U8)enStatus));
            break;
        }
    }

    // [2] Condition handle
    if ((enStatus != MSAPI_DMX_FILTER_STATUS_SECAVAILABLE) && (enStatus != MSAPI_DMX_FILTER_STATUS_TIMEOUT))
    {
        msAPI_DMX_RestartFilter(stEpgETT.u8FID);
        EIT_DBG(ETT_PARSE, ("=== EIT CB - Restart Filter %d ===\r\n", u8FID));
    }
}
/******************************************************************************/
void MApp_Dmx_ETT_Monitor(MS_EPG_ETT* pstETT)
{
    MS_DMX_SECTIONMONITOR_PARA   stSectionMonitor;

    // EIT sub table receive is OK
    //if ((stEpgDBInfo.u8EitRxOK) == 0x0F)
        {
        // Check MGT or monitor EIT timer is timeout
        if(stMGT.version_number != INVALID_VERSION_NUM)
        {
            #if (!ENABLE_NEW_DMX_INTERFACE)
            // Is there a free 4K filter ID?
            if (msAPI_DMX_GetFree4KFilterNo())        // Got a free filter ID
            #endif
            {
                // Not set filter yet?
                if((pstETT->u8FID == MSAPI_DMX_INVALID_FLT_ID)
                && (stMGT.astEttItem[pstETT->u8Tbl].table_type_PID != 0))
                {
                    // Set all mask byte to 0xFF (Don't Care)
                    memset(stSectionMonitor.au8MaskByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);
                    memset(stSectionMonitor.au8NotMatchByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);


                    // Set EIT table PID
                    stSectionMonitor.u16PID             = stMGT.astEttItem[pstETT->u8Tbl].table_type_PID;
                    stSectionMonitor.u32SectionFltType     = MSAPI_DMX_FILTER_TYPE_SECTION_4K;


                    // [0]         Table ID
                    stSectionMonitor.au8MatchByte[0]     = TID_ETS;
                    stSectionMonitor.au8MaskByte[0]     = 0xFF;

                    // [5]         current_next_indicator
                    stSectionMonitor.au8MatchByte[5]     = 0x01;
                    stSectionMonitor.au8MaskByte[5]     = 0x01;

                    // [8]         protocol_version
                      stSectionMonitor.au8MatchByte[8]    = 0x00;
                    stSectionMonitor.au8MaskByte[8]     = 0xFF;

                    // [9-10]    Source ID
                    stSectionMonitor.au8MatchByte[9]     = HIGHBYTE(pstETT->u16SourceID);
                    stSectionMonitor.au8MaskByte[9]     = 0xFF;
                    stSectionMonitor.au8MatchByte[10]     = LOWBYTE(pstETT->u16SourceID);
                    stSectionMonitor.au8MaskByte[10]     = 0xFF;

                    // [11-12]    Event ID
                    stSectionMonitor.au8MatchByte[11]     = HIGHBYTE(pstETT->u16EventID);
                    stSectionMonitor.au8MaskByte[11]     = 0xFF;
                    stSectionMonitor.au8MatchByte[12]     = LOWBYTE(pstETT->u16EventID);
                    stSectionMonitor.au8MaskByte[12]     = 0xFF;

                    // Set Callback Function, Timeout, Global Filter ID and Continuous mode
                    stSectionMonitor.pfNotify           = MApp_Dmx_ETT_Cb;
                    stSectionMonitor.u16TimeoutMilliSec = ETT_TIMEOUT;
                    stSectionMonitor.pu8FID             = &pstETT->u8FID;
                    stSectionMonitor.SectMode           = DMX_SECT_MODE_ONESHOT|DMX_SECT_MODE_CRCCHK;

                    EIT_DBG(ETT_PARSE, ("EPG: Set ETT table PID to %X\n", stSectionMonitor.u16PID));
                    EIT_DBG(ETT_PARSE, ("Soruce ID = %0bX%0bX\t", stSectionMonitor.au8MatchByte[9], stSectionMonitor.au8MatchByte[10]));
                    EIT_DBG(ETT_PARSE, ("Event ID = %0bX%0bX\n", stSectionMonitor.au8MatchByte[11], stSectionMonitor.au8MatchByte[12]));

                    // Set filter
                    if(msAPI_DMX_SectionMonitor(&stSectionMonitor, FALSE) == DMX_FILTER_STATUS_OK)
                    {
                        EIT_DBG(ETT_PARSE, ("EPG: Set ETT to Filter #%d \r\n", stEpgETT.u8FID));
                    }
                    else
                    {
                        EIT_DBG(ETT_PARSE, ("EPG: monitor ETT fail!! \r\n"));
                    }
                }
                else    // Already set filter
                {
                    EIT_DBG(ETT_PARSE, ("EPG: monitoring ETT at Filter #%d \r\n", stEpgETT.u8FID));
                }
            }
        }
    }
}
#endif

#define ENABLE_ALWAYS_SKIP_FIRST_VALUE 1

/*****************************************************************************/
static void MApp_Dmx_RRT_Parse(MS_REGION5_RATING *pstMgt, U8 *pu8Section)
{
    U8 version_number, u8Grad_Scale;
    U8 u8Num_dimension, u8dimensionNameLen, u8Valuesdefined;
    U8 u8AbbrevLength, u8RatingValueLength;
    //U8* pu8TempRRTRatingDes = NULL;
    U8 au8TempRRTRatingDes[REGION5_RATING_DES_MAX_LENGTH+2] = {0};
    BOOLEAN bFirstNullStr = TRUE;

#if ENABLE_SKIP_RRT_NULL_MSS_VALUE
    U8 number_strings;
#endif


    //printf("MApp_Dmx_RRT_Parse(pstMgt=0x%X, pu8Section=0x%X)\n", (U32)pstMgt, (U32)pu8Section);
    //printf("au8TempRRTRatingDes=0x%X)\n", (U32)au8TempRRTRatingDes);



    /*[1]check error condition =============================================*/
    if( pstMgt == NULL )
    {
        PRINT_CURRENT_LINE();
        printf("\nError: pstMgt is NULL!\n");
        return;
    }
    if( pu8Section == NULL )
    {
        PRINT_CURRENT_LINE();
        printf("\nError: pu8Section is NULL!\n");
        return;
    }


#if (ENABLE_MEXICO_VCHIP)
    if ((u8RrtRegionNo < 5) || (u8CurrentRrtRegionNo < 5))
    {
        DMX_DBG( DMX_RRT, printf( "RRT region smaller than 5 [%bu, %bu]\n", u8RrtRegionNo, u8CurrentRrtRegionNo) );
        return;
    }
#endif

    /*[2]check version change ==============================================*/
    DMX_DBG( DMX_RRT, printf( "==============================================>>>>\r\n" ) );
    //pu8TempRRTRatingDes = msAPI_Memory_Allocate(REGION5_RATING_DES_MAX_LENGTH, BUF_ID_ATSC);

    version_number = ( pu8Section[5] >> 1 ) & 0x1f;

    DMX_DBG( DMX_RRT, printf( "\nparse RRT, version_number = [%d] -> [%d]\n", ( U8 ) pstMgt->u8VersionNo, version_number) );

#if(RRT_UPDATE_BY_VERSION_NUMBER_CHANGED)
#if (ENABLE_RRT5_UPDATE_BY_LATEST_VERSION)
    if ((version_number == pstMgt->u8VersionNo
        || (((version_number < pstMgt->u8VersionNo)
        && !(version_number==0 && pstMgt->u8VersionNo==31))
        && (INVALID_VERSION_NUM != pstMgt->u8VersionNo))) //skip old verison
    #if (ENABLE_MEXICO_VCHIP)
        && (!u8RrtRegionNoUpgrade)
    #endif
        )
#else
    if(version_number == pstMgt->u8VersionNo)
#endif
    {
        //same version
        //if (pu8TempRRTRatingDes != NULL)
        {
            //MSAPI_MEMORY_FREE(pu8TempRRTRatingDes,BUF_ID_ATSC);
        }
        DMX_DBG( DMX_RRT, printf( "\nParse RRT>> same version number %d", pstMgt->u8VersionNo ) );
        return;
    }
#endif
    /*[3]init variables ====================================================*/

    //memset( pstMgt, 0, sizeof( MS_REGION5_RATING ) );

    pstMgt->u8VersionNo = version_number;


#if (ENABLE_RRT5_UPDATE_BY_LATEST_VERSION && ENABLE_MEXICO_VCHIP)
    u8RrtRegionNoUpgrade = 0;
    stGenSettingVchipRegion5.u8LastUpdateRegion = u8LastRrtRegionNo;
#endif

    /*[4]get Region name items =========================================================*/
    //MApp_Dmx_Parse_MSS( ( U8 * ) pstMgt->u8Region5Name, &pu8Section[10] );
    MApp_Dmx_Parse_MSS( ( U8 * ) pstMgt->u8Region5Name, &pu8Section[10], sizeof(pstMgt->u8Region5Name), ENABLE);


    /*
     * There's a possibility that string length in pu8Section[10] is larger than the size of
     * u8Region5Name. Hot fix for this situation. To cure completely, MApp_Dmx_Parse_MSS needs
     * to be fixed!
     */
    //(pstMgt->u8Region5Name)[sizeof(pstMgt->u8Region5Name)-1] = '\0';

    if ( (pstMgt->u8Region5Name[0]  || pstMgt->u8Region5Name[1]))
    {
    #if 1 // Fix coverity: Overlapping buffer in memory copy (BUFFER_SIZE)
        memmove((char *)(pstMgt->u8Region5Name), (char *)(pstMgt->u8Region5Name + 2), REGION5_NAME_MAX_LEN-2);
    #else
        memcpy((char *)(pstMgt->u8Region5Name), (char *)(pstMgt->u8Region5Name + 2), REGION5_NAME_MAX_LEN-2);
    #endif
    }

    DMX_DBG( DMX_RRT, printf( "\nparse RRT, Region name = %s", pstMgt->u8Region5Name ) );

    u8Num_dimension = pu8Section[( 10 + pu8Section[9] )];
    DMX_DBG( DMX_RRT, printf( "\nparse RRT, Dimension_number = %d", u8Num_dimension ) );

    pu8Section += ( 10 + pu8Section[9] + 1 );
    /*[5]get dimensison =========================================================*/
    iu8Buffer_k = 0;
    for (iu16Loop_i = 0; (iu16Loop_i < u8Num_dimension) && (iu8Buffer_k < REGION5_DIMENSION_NUM); iu16Loop_i++)
    {
        U8  u8RatingValueStrLen=0, u8RatingValueLoop=0;

        //printf(" iu8Buffer_k=%u\n", iu8Buffer_k);

        u8dimensionNameLen = *pu8Section;
        //MApp_Dmx_Parse_MSS( ( U8 * ) pstMgt->stRegin5Dimension[iu16Loop_i].u8DimensionName, pu8Section + 1 );
        MApp_Dmx_Parse_MSS( ( U8 * ) pstMgt->stRegin5Dimension[iu8Buffer_k].u8DimensionName, pu8Section + 1 ,REGION5_DIMENSIONNAME_MAX_LENGTH, ENABLE);

        if (pstMgt->stRegin5Dimension[iu8Buffer_k].u8DimensionName[0] ||
            pstMgt->stRegin5Dimension[iu8Buffer_k].u8DimensionName[1] )
        {
    #if 1 // Fix coverity: Overlapping buffer in memory copy (BUFFER_SIZE)
            memmove((char *)(pstMgt->stRegin5Dimension[iu8Buffer_k].u8DimensionName), (char *)(pstMgt->stRegin5Dimension[iu8Buffer_k].u8DimensionName + 2 /*2 is actual length bytes*/), REGION5_DIMENSIONNAME_MAX_LENGTH-2);
    #else
            memcpy((char *)(pstMgt->stRegin5Dimension[iu8Buffer_k].u8DimensionName), (char *)(pstMgt->stRegin5Dimension[iu8Buffer_k].u8DimensionName + 2 /*2 is actual length bytes*/), REGION5_DIMENSIONNAME_MAX_LENGTH-2);
    #endif
        }
        DMX_DBG( DMX_RRT, printf( "\nparse RRT, Dimension name = %s", pstMgt->stRegin5Dimension[iu16Loop_i].u8DimensionName ) );
        pu8Section += u8dimensionNameLen + 1;

        /*[6]get graduated scale value =========================================================*/
        u8Grad_Scale = *pu8Section & 0x10;
        pstMgt->stRegin5Dimension[iu8Buffer_k].u16Graduated_Scale = u8Grad_Scale >> 4;
        DMX_DBG(DMX_RRT, printf("\nparse RRT, Graduated_Scale = %d", pstMgt->stRegin5Dimension[iu8Buffer_k].u16Graduated_Scale));

        /*[7]get ration values =========================================================*/
        u8Valuesdefined = *pu8Section & 0x0f;

        if (u8Valuesdefined>REGION5_MAX_RATING_OPTION)
            u8Valuesdefined = REGION5_MAX_RATING_OPTION;

        pu8Section++;
        DMX_DBG( DMX_RRT, printf( "\nparse RRT, values defined = %d", u8Valuesdefined ) );

        pstMgt->stRegin5Dimension[iu8Buffer_k].u8Values_Defined = u8Valuesdefined;
        bFirstNullStr = TRUE; // the 1st value string of each dimension will be NULL.
        for( iu8Loop_i = 0;iu8Loop_i < u8Valuesdefined;iu8Loop_i++ )
        {
            u8AbbrevLength = *pu8Section;
#if ENABLE_SKIP_RRT_NULL_MSS_VALUE
            number_strings = *(pu8Section + 1);
#endif
            //u8RatingValueStrLen=MApp_Dmx_Parse_MSS( ( U8 * ) &( pstMgt->stRegin5Dimension[iu16Loop_i].stRatingText[u8RatingValueLoop] ), pu8Section + 1 );
            u8RatingValueStrLen=MApp_Dmx_Parse_MSS( ( U8 * ) &( pstMgt->stRegin5Dimension[iu8Buffer_k].stRatingText[u8RatingValueLoop] ), pu8Section + 1 , REGION5_RATING_TEXT_MAX_LENGTH, ENABLE);

            if (pstMgt->stRegin5Dimension[iu8Buffer_k].stRatingText[u8RatingValueLoop][0] ||
                pstMgt->stRegin5Dimension[iu8Buffer_k].stRatingText[u8RatingValueLoop][1])
            {
#if 0
                strcpy((char *)(pstMgt->stRegin5Dimension[iu8Buffer_k].stRatingText[u8RatingValueLoop]), (char *)(pstMgt->stRegin5Dimension[iu8Buffer_k].stRatingText[u8RatingValueLoop]) + 1);
#else
                memcpy((char *)(pstMgt->stRegin5Dimension[iu8Buffer_k].stRatingText[u8RatingValueLoop]), (char *)(pstMgt->stRegin5Dimension[iu8Buffer_k].stRatingText[u8RatingValueLoop]) + 2 /*2 is Actual Length bytes*/, REGION5_RATING_TEXT_MAX_LENGTH-2);
#endif
            }

            DMX_DBG( DMX_RRT, printf( "\nparse RRT, Rating value = %s", &( pstMgt->stRegin5Dimension[iu8Buffer_k].stRatingText[u8RatingValueLoop] ) ) );
            pu8Section += ( u8AbbrevLength + 1 );
            u8RatingValueLength = *pu8Section;

#if ENABLE_SKIP_RRT_NULL_MSS_VALUE
            if (number_strings == 0)
            {
                bFirstNullStr = FALSE;
                pstMgt->stRegin5Dimension[iu8Buffer_k].u8Values_Defined -=1;
                pu8Section += (u8RatingValueLength + 1);
                continue;
            }
#endif

#if ENABLE_ALWAYS_SKIP_FIRST_VALUE
            if (bFirstNullStr == TRUE)// the first string is null
#else
            if ( (u8RatingValueStrLen<=2 ) && (bFirstNullStr == TRUE) )// the first string is null
#endif
            {
                pstMgt->stRegin5Dimension[iu8Buffer_k].u8Values_Defined-=1;
                pu8Section += ( u8RatingValueLength + 1 );
                bFirstNullStr = FALSE;
                continue;
            }

            //if(pu8TempRRTRatingDes)
            {
                // Clear tmp buf
                memset( au8TempRRTRatingDes, 0, sizeof(au8TempRRTRatingDes) );

                //u8RatingValueStrLen=MApp_Dmx_Parse_MSS( pu8TempRRTRatingDes, pu8Section + 1 );
                u8RatingValueStrLen = MApp_Dmx_Parse_MSS( au8TempRRTRatingDes, pu8Section + 1, sizeof(au8TempRRTRatingDes), ENABLE);

                //?? double check ATSC_FIX_C
                // Save to DB
            #if(ENABLE_DB_ATSC_RRT5_API)
                MApp_DB_ATSC_Save_RRT_Descriptor(iu16Loop_i, u8RatingValueLoop, au8TempRRTRatingDes+2, REGION5_RATING_DES_MAX_LENGTH );
            #else
                msAPI_MIU_Copy(_VA2PA((U32)au8TempRRTRatingDes)+2, _VA2PA(GET_RRT_DESCRIPTOR_ADDRESS((U8)iu16Loop_i, u8RatingValueLoop)), REGION5_RATING_DES_MAX_LENGTH, MIU_SDRAM2SDRAM);
            #endif
                //?? double check
            }
            /*else
            {
                __ASSERT(0);
                PRINT_CURRENT_LINE();
            }*/

            u8RatingValueLoop++;
            pu8Section += ( u8RatingValueLength + 1 );
        }

        // ignore dimensions that don't have any values defined
        if (pstMgt->stRegin5Dimension[iu8Buffer_k].u8Values_Defined > 0)
            iu8Buffer_k++;
    }

    pstMgt->u8NoDimension = iu8Buffer_k;

#if 0
    {
        BOOLEAN bSavedRRT = FALSE;
        U8 u8Loop1=0, u8Loop2=0;
        MS_EZ_REGION5_RATING stEZ_VchipRegion5;

        // Find if this RRT has been saved before........
        //for (u8Loop1=0; u8Loop1<stGenSetting.g_SysSetting.u8NoSavedRRT; u8Loop1++)
        printf("\n stGenSettingVchipRegion5.u8NoSavedRRT = %d\n", stGenSettingVchipRegion5.u8NoSavedRRT);
        for (u8Loop1=0; u8Loop1 < stGenSettingVchipRegion5.u8NoSavedRRT; u8Loop1++)
        {
            // Load from DB
        #if( ENABLE_DB_ATSC_RRT5_API )
            MApp_DB_ATSC_Load_RRT_EZ_REGION(u8Loop1, &stEZ_VchipRegion5 );
        #else
            msAPI_MIU_Copy( _VA2PA(GET_SAVED_RRT_SETTING_ADDRESS(u8Loop1)), _VA2PA((U32)&stEZ_VchipRegion5), (U32)sizeof(MS_EZ_REGION5_RATING), MIU_SDRAM2SDRAM);
        #endif


            printf("Loop%d Ez:  (%x)\n", u8Loop1, (U16)stEZ_VchipRegion5.stRegin5Dimension[0].u32CurrentOption);


#if (!ENABLE_RRT5_UPDATE_BY_LATEST_VERSION)
            if(strcmp((const char*)pstMgt->u8Region5Name, (const char*)stEZ_VchipRegion5.u8Region5Name)==0)
#endif
            {
#if (!ENABLE_RRT5_UPDATE_BY_LATEST_VERSION)
                if((pstMgt->u8NoDimension == stEZ_VchipRegion5.u8NoDimension)&&(pstMgt->u8VersionNo == stEZ_VchipRegion5.u8VersionNo))
#endif
                {// this RRT is already in the memory....
                    bSavedRRT = TRUE;
                    for(u8Loop2=0; u8Loop2<stEZ_VchipRegion5.u8NoDimension; u8Loop2++)
                    {
                        // Restore the rating settings........
                        pstMgt->stRegin5Dimension[u8Loop2].u32CurrentOption = stEZ_VchipRegion5.stRegin5Dimension[u8Loop2].u32CurrentOption;
                        printf("jj Loop%d Save Option: %x\n", u8Loop2,  pstMgt->stRegin5Dimension[u8Loop2].u32CurrentOption );
                    #if(ENABLE_ATSC_VCHIP)
                        MApp_VChip_Init();
                    #endif
                    }
                    break;
                }
            }
        }

        if (!bSavedRRT)
        {
            // fill the structure...
            stEZ_VchipRegion5.u8VersionNo = pstMgt->u8VersionNo;
            memcpy(stEZ_VchipRegion5.u8Region5Name, pstMgt->u8Region5Name, sizeof(stEZ_VchipRegion5.u8Region5Name));
            stEZ_VchipRegion5.u8NoDimension = pstMgt->u8NoDimension;
            for(u8Loop2=0; u8Loop2<stEZ_VchipRegion5.u8NoDimension; u8Loop2++)
            {
                stEZ_VchipRegion5.stRegin5Dimension[u8Loop2].u32CurrentOption = pstMgt->stRegin5Dimension[u8Loop2].u32CurrentOption;
                stEZ_VchipRegion5.stRegin5Dimension[u8Loop2].u16Graduated_Scale = pstMgt->stRegin5Dimension[u8Loop2].u16Graduated_Scale;
                stEZ_VchipRegion5.stRegin5Dimension[u8Loop2].u8Values_Defined = pstMgt->stRegin5Dimension[u8Loop2].u8Values_Defined;
            }

            //if (stGenSetting.g_SysSetting.u8NoSavedRRT == MAX_RRT_SAVED)
            if ( stGenSettingVchipRegion5.u8NoSavedRRT == MAX_RRT_SAVED )
            {
                //if (stGenSetting.g_SysSetting.u8IdxLastSavedRRT >= (MAX_RRT_SAVED-1))
                if (stGenSettingVchipRegion5.u8IdxLastSavedRRT >= (MAX_RRT_SAVED-1))
                {
                    //stGenSetting.g_SysSetting.u8IdxLastSavedRRT = 0;
                    stGenSettingVchipRegion5.u8IdxLastSavedRRT = 0;
                    //u8Loop1 = stGenSetting.g_SysSetting.u8IdxLastSavedRRT;
                    u8Loop1 = stGenSettingVchipRegion5.u8IdxLastSavedRRT;
                }
                else
                {
                    //stGenSetting.g_SysSetting.u8IdxLastSavedRRT++;
                    stGenSettingVchipRegion5.u8IdxLastSavedRRT++;
                    //u8Loop1 = stGenSetting.g_SysSetting.u8IdxLastSavedRRT;
                    u8Loop1 = stGenSettingVchipRegion5.u8IdxLastSavedRRT;
                }
            }
            else
            {
                //u8Loop1 = stGenSetting.g_SysSetting.u8IdxLastSavedRRT;
                u8Loop1 = stGenSettingVchipRegion5.u8IdxLastSavedRRT;

                //stGenSetting.g_SysSetting.u8NoSavedRRT++;
                stGenSettingVchipRegion5.u8NoSavedRRT++;

                //stGenSetting.g_SysSetting.u8IdxLastSavedRRT++;
                stGenSettingVchipRegion5.u8IdxLastSavedRRT++;
            }

            // Save to DB
        #if( ENABLE_DB_ATSC_RRT5_API )
            MApp_DB_ATSC_Save_RRT_EZ_REGION(u8Loop1, &stEZ_VchipRegion5 );
        #else
            msAPI_MIU_Copy(_VA2PA((U32)&stEZ_VchipRegion5), _VA2PA(GET_SAVED_RRT_SETTING_ADDRESS(u8Loop1)), sizeof(MS_EZ_REGION5_RATING), MIU_SDRAM2SDRAM);
        #endif
        }
    }
#endif

    DMX_DBG( DMX_RRT, printf( "\r\n==============================================>>>>\r\n" ) );
    //MSAPI_MEMORY_FREE(pu8TempRRTRatingDes,BUF_ID_ATSC);

}
/*****************************************************************************/
#if(!RRT_UPDATE_BY_VERSION_NUMBER_CHANGED)
static MS_BOOL MApp_Dmx_RRT_CheckVersionChange(const U8* const _pu8Section)
{
    //U32 u32Section[MSAPI_DMX_SECTION_4K/sizeof(U32)];	 //section data buffer
    U8* pu8Section = NULL;//((U8*)u32Section);
    U8* pu8Section_AllocStart = NULL;
    U8 u8AbbrevLength, u8RatingValueLength;
    U8 u8Grad_Scale;
    U8 u8Num_dimension, u8dimensionNameLen, u8Valuesdefined;
    U8 au8TempRRTRatingDes[REGION5_RATING_DES_MAX_LENGTH] = {0};
    BOOLEAN bFirstNullStr = TRUE;
    MS_REGION5_RATING * pstMS_REGION5_RATING_Tmp = NULL;
#if ENABLE_SKIP_RRT_NULL_MSS_VALUE
    U8 number_strings;
#endif


    //printf("MApp_Dmx_RRT_CheckVersionChange(_pu8Section=0x%X)\n", _pu8Section);

    pu8Section_AllocStart = pu8Section = msAPI_Memory_Allocate( MSAPI_DMX_SECTION_4K, BUF_ID_ATSC);
    if( pu8Section == NULL )
    {
        printf("\nError: memory alloc failed!\n");
        return FALSE;
    }

    //printf("  pu8Section=0x%X)\n", (U32)pu8Section);

    memcpy(pu8Section, _pu8Section, sizeof(MSAPI_DMX_SECTION_4K));


    /*[2]check version change ==============================================*/
    DMX_DBG( DMX_RRT, printf( "==============================================>>>>\r\n" ) );
    //pu8TempRRTRatingDes=msAPI_Memory_Allocate(REGION5_RATING_DES_MAX_LENGTH,BUF_ID_ATSC);

    //pstMgt.u8VersionNo = ( pu8Section[5] >> 1 ) & 0x1f;//version_number;
    U8 u8CurVersionNo = ( pu8Section[5] >> 1 ) & 0x1f;//version_number;

    if( u8CurVersionNo != stGenSettingVchipRegion5.u8VersionNo ) //check version change
    {
        DMX_DBG( DMX_RRT, printf("MApp_Dmx_RRT_CheckVersionChange => [VersionNo change]\r\n"));
        //MSAPI_MEMORY_FREE(pu8TempRRTRatingDes,BUF_ID_ATSC);
        MSAPI_MEMORY_FREE(pu8Section_AllocStart, BUF_ID_ATSC);
        return TRUE;
    }


    /*[3]init variables ====================================================*/

    pstMS_REGION5_RATING_Tmp = msAPI_Memory_Allocate( sizeof(MS_REGION5_RATING), BUF_ID_ATSC);
    if( pstMS_REGION5_RATING_Tmp == NULL )
    {
        printf("\nError: memory alloc failed!\n");
        MSAPI_MEMORY_FREE(pu8Section_AllocStart, BUF_ID_ATSC);
        return FALSE;
    }

    //printf("  pstMS_REGION5_RATING_Tmp=0x%X)\n", (U32)pstMS_REGION5_RATING_Tmp);

    memset( pstMS_REGION5_RATING_Tmp, 0, sizeof( MS_REGION5_RATING ) );

#define pstMgt (*pstMS_REGION5_RATING_Tmp)

    pstMgt.u8VersionNo = u8CurVersionNo;


    /*[4]get Region name items =========================================================*/
    //MApp_Dmx_Parse_MSS( ( U8 * ) pstMgt->u8Region5Name, &pu8Section[10] );
    MApp_Dmx_Parse_MSS( ( U8 * ) pstMgt.u8Region5Name, &pu8Section[10], sizeof(pstMgt.u8Region5Name),FALSE );

    if( (pstMgt.u8Region5Name[0] || pstMgt.u8Region5Name[1]) )
    {
    #if 1 // Fix coverity: Overlapping buffer in memory copy (BUFFER_SIZE)
        memmove((char *)(pstMgt.u8Region5Name), (char *)(pstMgt.u8Region5Name + 2), REGION5_NAME_MAX_LEN-2);
    #else
        memcpy((char *)(pstMgt.u8Region5Name), (char *)(pstMgt.u8Region5Name + 2), 34/*36-2*/);
    #endif
    }

    DMX_DBG( DMX_RRT, printf( "\nparse RRT, Region name = %s", pstMgt.u8Region5Name ) );

    u8Num_dimension = pu8Section[( 10 + pu8Section[9] )];
    DMX_DBG( DMX_RRT, printf( "\nparse RRT, Dimension_number = %d", u8Num_dimension ) );
    pu8Section += ( 10 + pu8Section[9] + 1 );

/*[5]get dimensison =========================================================*/
    iu8Buffer_k = 0;
    for (iu16Loop_i = 0; (iu16Loop_i < u8Num_dimension) && (iu8Buffer_k < REGION5_DIMENSION_NUM); iu16Loop_i++)
    {
        U8	u8RatingValueStrLen=0, u8RatingValueLoop=0;
        u8dimensionNameLen = *pu8Section;
        //MApp_Dmx_Parse_MSS( ( U8 * ) pstMgt->stRegin5Dimension[iu16Loop_i].u8DimensionName, pu8Section + 1 );
        MApp_Dmx_Parse_MSS( ( U8 * ) pstMgt.stRegin5Dimension[iu8Buffer_k].u8DimensionName, pu8Section + 1 ,REGION5_DIMENSIONNAME_MAX_LENGTH, ENABLE);

        if(pstMgt.stRegin5Dimension[iu8Buffer_k].u8DimensionName[0] ||
           pstMgt.stRegin5Dimension[iu8Buffer_k].u8DimensionName[1] )
        {
        #if 1 // Fix coverity: Overlapping buffer in memory copy (BUFFER_SIZE)
            memmove((char *)(pstMgt.stRegin5Dimension[iu8Buffer_k].u8DimensionName), (char *)(pstMgt.stRegin5Dimension[iu8Buffer_k].u8DimensionName + 2 /*2 is actual length bytes*/), REGION5_DIMENSIONNAME_MAX_LENGTH-2);
        #else
            memcpy((char *)(pstMgt.stRegin5Dimension[iu8Buffer_k].u8DimensionName), (char *)(pstMgt.stRegin5Dimension[iu8Buffer_k].u8DimensionName + 2 /*2 is actual length bytes*/), REGION5_DIMENSIONNAME_MAX_LENGTH-2);
        #endif
        }
        DMX_DBG( DMX_RRT, printf( "\nparse RRT, Dimension name = %s", pstMgt.stRegin5Dimension[iu16Loop_i].u8DimensionName ) );
        pu8Section += u8dimensionNameLen + 1;

        /*[6]get graduated scale value =========================================================*/
        u8Grad_Scale = *pu8Section & 0x10;
        pstMgt.stRegin5Dimension[iu8Buffer_k].u16Graduated_Scale = u8Grad_Scale >> 4;
        DMX_DBG(DMX_RRT, printf("\nparse RRT, Graduated_Scale = %d", pstMgt.stRegin5Dimension[iu8Buffer_k].u16Graduated_Scale));

        if(pstMgt.stRegin5Dimension[iu8Buffer_k].u16Graduated_Scale != stGenSettingVchipRegion5.stRegin5Dimension[iu8Buffer_k].u16Graduated_Scale)
        {
            DMX_DBG(DMX_RRT, printf("MApp_Dmx_RRT_CheckVersionChange => [Graduated_Scale change]\r\n"));
            //MSAPI_MEMORY_FREE(pu8TempRRTRatingDes,BUF_ID_ATSC);
            MSAPI_MEMORY_FREE(pstMS_REGION5_RATING_Tmp, BUF_ID_ATSC);
            MSAPI_MEMORY_FREE(pu8Section_AllocStart, BUF_ID_ATSC);
            return TRUE;
        }

        /*[7]get ration values =========================================================*/
        u8Valuesdefined = *pu8Section & 0x0f;

        if (u8Valuesdefined>REGION5_MAX_RATING_OPTION)
            u8Valuesdefined = REGION5_MAX_RATING_OPTION;

        pu8Section++;
        DMX_DBG( DMX_RRT, printf( "\nparse RRT, values defined = %d\r\n", u8Valuesdefined ) );

        pstMgt.stRegin5Dimension[iu8Buffer_k].u8Values_Defined = u8Valuesdefined;

        if(u8Valuesdefined-1 != stGenSettingVchipRegion5.stRegin5Dimension[iu8Buffer_k].u8Values_Defined)
        {
            DMX_DBG( DMX_RRT, printf("MApp_Dmx_RRT_CheckVersionChange => [Values_Defined change]\r\n"));
            //MSAPI_MEMORY_FREE(pu8TempRRTRatingDes,BUF_ID_ATSC);
            MSAPI_MEMORY_FREE(pstMS_REGION5_RATING_Tmp, BUF_ID_ATSC);
            MSAPI_MEMORY_FREE(pu8Section_AllocStart, BUF_ID_ATSC);
            return TRUE;
        }

        bFirstNullStr = TRUE; // the 1st value string of each dimension will be NULL.
        for( iu8Loop_i = 0;iu8Loop_i < u8Valuesdefined;iu8Loop_i++ )
        {
            u8AbbrevLength = *pu8Section;
#if ENABLE_SKIP_RRT_NULL_MSS_VALUE
            number_strings = *(pu8Section + 1);
#endif
            //u8RatingValueStrLen=MApp_Dmx_Parse_MSS( ( U8 * ) &( pstMgt->stRegin5Dimension[iu16Loop_i].stRatingText[u8RatingValueLoop] ), pu8Section + 1 );
            u8RatingValueStrLen=MApp_Dmx_Parse_MSS( ( U8 * ) &( pstMgt.stRegin5Dimension[iu8Buffer_k].stRatingText[u8RatingValueLoop] ), pu8Section + 1 , REGION5_RATING_TEXT_MAX_LENGTH, ENABLE);

            if (pstMgt.stRegin5Dimension[iu8Buffer_k].stRatingText[u8RatingValueLoop][0] ||
            pstMgt.stRegin5Dimension[iu8Buffer_k].stRatingText[u8RatingValueLoop][1])
            {
                memcpy((char *)(pstMgt.stRegin5Dimension[iu8Buffer_k].stRatingText[u8RatingValueLoop]), (char *)(pstMgt.stRegin5Dimension[iu8Buffer_k].stRatingText[u8RatingValueLoop]) + 2 /*2 is Actual Length bytes*/, REGION5_RATING_TEXT_MAX_LENGTH-2);
            }
            pu8Section += ( u8AbbrevLength + 1 );
            u8RatingValueLength = *pu8Section;

#if ENABLE_SKIP_RRT_NULL_MSS_VALUE
            if (number_strings == 0)
            {
                bFirstNullStr = FALSE;
                pstMgt.stRegin5Dimension[iu8Buffer_k].u8Values_Defined -=1;
                pu8Section += (u8RatingValueLength + 1);
                continue;
            }
#endif

#if ENABLE_ALWAYS_SKIP_FIRST_VALUE
            if (bFirstNullStr == TRUE)// the first string is null
#else
            if ( (u8RatingValueStrLen<=2 ) && (bFirstNullStr == TRUE) )// the first string is null
#endif
            {
                pstMgt.stRegin5Dimension[iu8Buffer_k].u8Values_Defined-=1;
                pu8Section += ( u8RatingValueLength + 1 );
                bFirstNullStr = FALSE;
                continue;
            }

            //if(pu8TempRRTRatingDes)
            {
                memset(au8TempRRTRatingDes, 0, REGION5_RATING_DES_MAX_LENGTH);
                //u8RatingValueStrLen=MApp_Dmx_Parse_MSS( pu8TempRRTRatingDes, pu8Section + 1 );
                u8RatingValueStrLen = MApp_Dmx_Parse_MSS( au8TempRRTRatingDes, pu8Section + 1, REGION5_RATING_DES_MAX_LENGTH,FALSE );

                //?? double check ATSC_FIX_C
                // Save to DB
            #if(ENABLE_DB_ATSC_RRT5_API)
                MApp_DB_ATSC_Save_RRT_Descriptor(iu16Loop_i, u8RatingValueLoop, au8TempRRTRatingDes, REGION5_RATING_DES_MAX_LENGTH );
            #else
                msAPI_MIU_Copy(_VA2PA((U32)au8TempRRTRatingDes)+2, _VA2PA(GET_RRT_DESCRIPTOR_ADDRESS((U8)iu16Loop_i, u8RatingValueLoop)), REGION5_RATING_DES_MAX_LENGTH, MIU_SDRAM2SDRAM);
            #endif
                //?? double check
            }
            /*else
            {
                __ASSERT(0);
            }*/

            u8RatingValueLoop++;
            pu8Section += ( u8RatingValueLength + 1 );
        }
        // ignore dimensions that don't have any values defined

        if (pstMgt.stRegin5Dimension[iu8Buffer_k].u8Values_Defined > 0)
        {
            iu8Buffer_k++;
            //printf(" iu8Buffer_k=%u\n", iu8Buffer_k);
        }
    }

    pstMgt.u8NoDimension = iu8Buffer_k;

    if( pstMgt.u8NoDimension != stGenSettingVchipRegion5.u8NoDimension )
    {
        DMX_DBG( DMX_RRT, printf("MApp_Dmx_RRT_CheckVersionChange => [NoDimension change]\r\n"));
        //MSAPI_MEMORY_FREE(pu8TempRRTRatingDes,BUF_ID_ATSC);
        MSAPI_MEMORY_FREE(pstMS_REGION5_RATING_Tmp, BUF_ID_ATSC);
        MSAPI_MEMORY_FREE(pu8Section_AllocStart, BUF_ID_ATSC);
        return TRUE;
    }

    DMX_DBG( DMX_RRT, printf( "\r\n==============================================>>>>\r\n" ) );
    //MSAPI_MEMORY_FREE(pu8TempRRTRatingDes,BUF_ID_ATSC);
    MSAPI_MEMORY_FREE(pstMS_REGION5_RATING_Tmp, BUF_ID_ATSC);
    MSAPI_MEMORY_FREE(pu8Section_AllocStart, BUF_ID_ATSC);

    return FALSE;

}
#endif

void MApp_Dmx_RRT_Cb(U8 u8FID, DMX_EVENT enEvent)
{
    U32 u32ActualSize,u32RmnSize;
    MSAPI_DMX_FILTER_STATUS enStatus;
    enStatus=(MSAPI_DMX_FILTER_STATUS)enEvent;

    /*[1]check enStatus ====================================================*/
    DMX_DBG(DMX_RRT, printf("\r\n RRT cb>> u8FID %d enStatus %d\n", u8FID, (U8)enStatus));

    switch(enStatus)
    {
        case MSAPI_DMX_FILTER_STATUS_SECAVAILABLE:
        {
            /* get section data */
            if(MApi_DMX_CopyData(u8FID, au8Section, MSAPI_DMX_SECTION_1K,&u32ActualSize,&u32RmnSize,NULL) == DMX_FILTER_STATUS_ERROR)
            {
                DMX_DBG(DMX_RRT, printf("[FID=%d] RRT get section fail!! \r\n", u8FID));
                break;
            }

            if(msAPI_DMX_CheckCRC32(au8Section) == FALSE)
            {
                EIT_DBG(DMX_RRT, ("[FID=%d] RRT CB - get section check CRC error!! Case 1\n", u8FID));
                enStatus = MSAPI_DMX_FILTER_STATUS_CRCINCORRECT;
                break;
            }

        //MApp_Dmx_DumpSectionData( ((au8Section[1]<<8)|au8Section[2])&0x0fff );

    #if(!RRT_UPDATE_BY_VERSION_NUMBER_CHANGED)
            if( MApp_Dmx_RRT_CheckVersionChange(au8Section) )
    #endif
            {
                /* parsing table */
                MApp_Dmx_RRT_Parse(&stGenSettingVchipRegion5, au8Section);
            }
            break;
        }

    #if (!ENABLE_NEW_DMX_INTERFACE)
        case MSAPI_DMX_FILTER_STATUS_CRCINCORRECT:
            {
                DMX_DBG(DMX_RRT, printf("[FID=%d] RRT get section check CRC error!! \r\n", u8FID));
                break;
            }

        case MSAPI_DMX_FILTER_STATUS_TIMEOUT:
            {
                DMX_DBG(DMX_RRT, printf("[FID=%d] RRT get section timeout!! \r\n", u8FID));
                break;
            }

        case MSAPI_DMX_FILTER_STATUS_OVERFLOW:
            {
                DMX_DBG(DMX_RRT, printf("[FID=%d] RRT get section overflow!! \r\n", u8FID));
                break;
            }
    #endif

        default:
            {
                DMX_DBG(DMX_RRT, printf("[FID=%d] RRT get section unknow error!! \r\n", u8FID));
                break;
            }
    }

    /*[02]finalize ==========================================================*/
    if(enStatus == MSAPI_DMX_FILTER_STATUS_SECAVAILABLE)
    {
        msAPI_DMX_CloseFilter(u8FID);
        u8RRTFid = MSAPI_DMX_INVALID_FLT_ID;
    }
    else
    {
        DMX_DBG(DMX_RRT, printf("Restart RRT filter>> [FID=%d]\r\n", u8FID));
        msAPI_DMX_RestartFilter(u8FID);
    }

}

/*****************************************************************************/
void MApp_Dmx_RRT_Monitor(void)
{
    MS_DMX_SECTIONMONITOR_PARA   stSectionMonitor;

#if (ENABLE_MEXICO_VCHIP)
    if ((u8RRTFid != MSAPI_DMX_INVALID_FLT_ID)
        && (u8CurrentRrtRegionNo >= 5)
        && (u8LastRrtRegionNo != u8CurrentRrtRegionNo))
    {
    #if (ENABLE_RRT5_UPDATE_BY_LATEST_VERSION)
        if ((u8CurrentRrtRegionNo > u8LastRrtRegionNo) && (u8CurrentRrtRegionNo > u8RrtRegionNo))
        {
            u8RrtRegionNoUpgrade = 1;
            u8RrtRegionNo = u8CurrentRrtRegionNo;
        }
        else
        {
            u8RrtRegionNoUpgrade = 0;
        }
    #else
        u8RrtRegionNo = u8CurrentRrtRegionNo;
    #endif
        u8LastRrtRegionNo = u8CurrentRrtRegionNo;
        msAPI_DMX_CloseFilter(u8RRTFid);
        u8RRTFid = MSAPI_DMX_INVALID_FLT_ID;
        fEnableRRTMonitor = TRUE;
        DMX_DBG(DMX_RRT, printf(" >>> [RRT monitor] u8CurrentRrtRegionNo=%bu, u8LastRrtRegionNo=%bu, u8RrtRegionNo=%bu\r\n", u8CurrentRrtRegionNo, u8LastRrtRegionNo, u8RrtRegionNo));
    }
#endif

    if(fEnableRRTMonitor || msAPI_Timer_DiffTimeFromNow(u32MonitorRRTTimer) > RRT_MONITOR_PERIOD)
    {
        if(u8RRTFid == MSAPI_DMX_INVALID_FLT_ID)
        {
            memset(stSectionMonitor.au8MaskByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);
            memset(stSectionMonitor.au8NotMatchByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);

            stSectionMonitor.u16PID = PID_BASE;
            stSectionMonitor.u32SectionFltType = MSAPI_DMX_FILTER_TYPE_SECTION_1K;
            stSectionMonitor.au8MatchByte[0] = TID_RRS; //table id
            stSectionMonitor.au8MaskByte[0] = 0xFF;

#if (ENABLE_MEXICO_VCHIP)
            DMX_DBG(DMX_RRT, printf(">>> Change to RRT [%bu] \r\n", (u8CurrentRrtRegionNo >= 5) ? u8CurrentRrtRegionNo:0));
            if (u8CurrentRrtRegionNo >= 5)
            {
                // specific rating region from CAD or MGT
                stSectionMonitor.au8MatchByte[4] = u8CurrentRrtRegionNo;
                stSectionMonitor.au8MaskByte[4] = 0xFF;
            }
            else
            {
                // all rating region
                stSectionMonitor.au8MatchByte[4] = 0x00;
                stSectionMonitor.au8MaskByte[4] = 0x00;
            }
#else
            stSectionMonitor.au8MatchByte[4] = 0x05;  // rating region 5
            stSectionMonitor.au8MaskByte[4] = 0xFF;
#endif

            stSectionMonitor.au8MatchByte[5] = 0x01;
            stSectionMonitor.au8MaskByte[5] = 0x01;
            stSectionMonitor.au8MatchByte[8] = 0x00;   // protocol_version
            stSectionMonitor.au8MaskByte[8]  = 0xFF;
            stSectionMonitor.pfNotify = MApp_Dmx_RRT_Cb;
            stSectionMonitor.u16TimeoutMilliSec = MSAPI_DMX_TIMEOUT_INFINITE;
            stSectionMonitor.pu8FID = &u8RRTFid;
            stSectionMonitor.SectMode           = DMX_SECT_MODE_ONESHOT|DMX_SECT_MODE_CRCCHK;

            if(msAPI_DMX_SectionMonitor(&stSectionMonitor, FALSE) == DMX_FILTER_STATUS_OK)
            {
               DMX_DBG(DMX_RRT, printf("\r\n monitoring RRT at Filter #%d \r\n", u8RRTFid));;

                fEnableRRTMonitor= FALSE;
                u32MonitorRRTTimer = msAPI_Timer_GetTime0();

            }
            else
            {
                DMX_DBG(DMX_RRT, printf("\r\n monitor RRT fail!! \r\n"));
            }
        }
        else
        {
            DMX_DBG(DMX_RRT, printf("\r\n monitoring RRT at Filter #%d , u8CurrentRrtRegionNo=%bu, u8RrtRegionNo=%bu\r\n", u8RRTFid, u8CurrentRrtRegionNo, u8RrtRegionNo));
            fEnableRRTMonitor = FALSE;
            u32MonitorRRTTimer = msAPI_Timer_GetTime0();
        }
    }
}

#if (ENABLE_MEXICO_VCHIP)
void MApp_Dmx_RRT_Reset(void)
{
    u8CurrentRrtRegionNo = stMGT.u8RrtRegionNo;
    u8LastRrtRegionNo = 0;
    u8RrtRegionNo = 0;

    #if (ENABLE_RRT5_UPDATE_BY_LATEST_VERSION)
    u8RrtRegionNoUpgrade = 0;
    #endif

    if (u8RRTFid != MSAPI_DMX_INVALID_FLT_ID)
    {
        msAPI_DMX_CloseFilter(u8RRTFid);
    }
    u8RRTFid = MSAPI_DMX_INVALID_FLT_ID;
    fEnableRRTMonitor = TRUE;
}
#endif

/*****************************************************************************/
EN_PARSER_STATUS MApp_Dmx_GetScanTables_ATSC(void)
{
    U16 u16SecLength;
    U32 u32SecCheckTime;
    MS_DMX_SECTIONGET_PARA stSectionGet;
    MS_DMX_SECTIONMONITOR_PARA stSectionMonitor;

    DMX_FILTER_STATUS enFilterStatus;
    BYTE bIsInvalidTSId=0;

    /*[1]check error condition =============================================*/
    DMX_DBG(DMX_SCAN, printf("<<<<Start of MApp_Dmx_GetScanTables_ATSC!===============\r\n"));

    /*
    if(msAPI_DMX_GetFree1KFilterNo() == 0)
    {
        DMX_DBG(DMX_SCAN, printf("no section filter available!!\r\n"));
        return EN_PARSER_ERROR;
    }
    */

    //fTableVersionChanged = FALSE;
    /*[2]initialize variables ==============================================*/
    memset(pastPATItem, 0x00, sizeof(MS_PAT_ITEM_ATSC) * MAX_VC_PER_PHYSICAL);
    memset(pastVirtualCh, 0x00, sizeof(MS_VIRTUAL_CHANNEL) * MAX_VC_PER_PHYSICAL);
    memset(pastVirtualCh_VCT, 0x00, sizeof(MS_VIRTUAL_VCT_CHANNEL) * MAX_VC_PER_PHYSICAL);
    memset(pastVirtualChInfo, 0x00, sizeof(MS_VIRTUAL_CHANNEL_INFO) * MAX_VC_PER_PHYSICAL);

    memset(au8CrcErrorCounter, 0x00, MSAPI_DMX_MAX_FILTER_NUMBER);
    memset(au8FID2ItemIdx, MSAPI_DMX_INVALID_FLT_ID, MSAPI_DMX_MAX_FILTER_NUMBER);
    //memset(au8EttFID2ItemIdx, MSAPI_DMX_INVALID_FLT_ID, MSAPI_DMX_MAX_FILTER_NUMBER);
    memset(au16PID2ItemIdx, 0x00, sizeof(au16PID2ItemIdx));

    u8OpenedFltCounter = 0;

    /*[3-1-1]get first PAT ==========================================================*/
    DMX_DBG(DMX_SCAN, printf("\033[45;37m\r\n<< PAT Start >>\033[0m\r\n"));

    u8NumOfPatItem = 0;
    u8TotalTableItem = 0;
    u8NumOfVCTItem = 0;
#if ENABLE_PAT_MUTISECTION
    u8CurSectionItemOfPat = 0;
    u8LastSectionNumOfPat = 0;
#endif
    memset(stSectionGet.au8MaskByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);
    memset(stSectionGet.au8NotMatchByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);

    stSectionGet.u16PID             = PID_PAT;
    stSectionGet.u32SectionFltType   = MSAPI_DMX_FILTER_TYPE_SECTION_1K;
    stSectionGet.au8MatchByte[0]    = TID_PAS;  // table id
    stSectionGet.au8MaskByte[0]     = 0xFF;
    stSectionGet.au8MatchByte[5]    = 0x01;
    stSectionGet.au8MaskByte[5]     = 0x01;
    stSectionGet.au8MatchByte[6]    = 0x00;     // section number
    stSectionGet.au8MaskByte[6]     = 0xFF;
    stSectionGet.pu8Section         = au8Section;
    stSectionGet.u16MaxSecSize      = MSAPI_DMX_SECTION_1K;
    stSectionGet.u16TimeoutMilliSec = PAT_SECTION_TIME_OUT_MS;
    stSectionGet.bCheckCrc          = CRC_CHECK;
    enFilterStatus                  = msAPI_DMX_SectionGet(&stSectionGet);

    u8ErrorCheckCount = 0;
    while((enFilterStatus > DMX_FILTER_STATUS_OK) && (u8ErrorCheckCount<=PAT_SECTION_GET_ERROR_CHECK_TIME))
    {
        #if (WATCH_DOG == ENABLE)
        msAPI_Timer_ResetWDT();
        #endif
        enFilterStatus = msAPI_DMX_SectionGet(&stSectionGet);
        u8ErrorCheckCount++;
    }

    switch(enFilterStatus)
    {
        case DMX_FILTER_STATUS_OK:
        {
            /* check section # */
            #if 0
            if( au8Section[7] > 0 ) //last section #
            {
                MX_DBINFO( printf( "Warning! No of PAT section > 1!!\r\n" ) );
            }
            #endif

#if ENABLE_PAT_MUTISECTION
            //Dump section data
            u16SecLength = (U16)(au8Section[1] & 0x0f) << 8 | ((U16)au8Section[2]);
            //MApp_Dmx_DumpSectionData(u16SecLength);

            /* parsing table */
            MApp_Dmx_PAT_Parse(pastPATItem, au8Section);

            u8NumOfPatItem = u8CurSectionItemOfPat;
            if(u8NumOfPatItem > MAX_VC_PER_PHYSICAL)
            {
                u8NumOfPatItem = MAX_VC_PER_PHYSICAL;
                DMX_DBG(DMX_SCAN, printf("Warning! u8NumOfPatItem > MAX_VC_PER_PHYSICAL !!\r\n"));
            }

            DMX_DBG(DMX_SCAN, printf("\033[31m  [%s][%d] current SN=%d, last SN=%d, u8NumOfPatItem=%d \033[0m\n",__FUNCTION__,__LINE__, au8Section[6], au8Section[7], u8NumOfPatItem));

          #if 0//(ENABLE_MAX_RRT_DIMENSION_NUMBER == 0)
            u8LastPatItemNo = u8NumOfPatItem;
          #endif

            u8TotalTableItem = u8NumOfPatItem;
#else
            /* get PAT items */
            u16SecLength = (U16)(au8Section[1] & 0x0f) << 8 | ((U16)au8Section[2]);
            u8NumOfPatItem = (u16SecLength - 9) / 4;
            #if 0   // should be remove after
            if ( (au8Section[0]!=0x00) || ( au8Section[7] > 0 ) || (u8NumOfPatItem > MAX_VC_PER_PHYSICAL))
            {
                printf( "<< Wrong PAT Section >>\r\n" );
                printf( "<< PAT Section >>\r\n" );
                MApp_Dmx_DumpSectionData( 29);
            }
            #endif

          #if 0//(ENABLE_MAX_RRT_DIMENSION_NUMBER == 0)
            u8LastPatItemNo = u8NumOfPatItem;
          #endif

            if(u8NumOfPatItem > MAX_VC_PER_PHYSICAL)
            {
                u8NumOfPatItem = MAX_VC_PER_PHYSICAL;
                DMX_DBG(DMX_SCAN, printf("Warning! u8NumOfPatItem > MAX_VC_PER_PHYSICAL !!\r\n"));
            }
            DMX_DBG(DMX_SCAN, printf("u8NumOfPatItem = %d\n", u8NumOfPatItem));
            u8TotalTableItem = u8NumOfPatItem;

            //MApp_Dmx_DumpSectionData( u16SecLength );

            /* parsing table */
            MApp_Dmx_PAT_Parse(pastPATItem, au8Section);
#endif
            break;
        }
        default:
        {
            DMX_DBG(DMX_SCAN, printf("get PAT error! enFilterStatus = %d\n", (U8)enFilterStatus));
            return EN_PARSER_ERROR;
        }
    }

#if ENABLE_PAT_MUTISECTION
    /*[3-1-2]get remind PAT ==========================================================*/
    if (u8LastSectionNumOfPat > 0)
    {
        DMX_DBG(DMX_SCAN, printf("\033[45;37m<< PAT Start : remind section>>\033[0m\r\n"));

        memset(stSectionMonitor.au8MaskByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);
        memset(stSectionMonitor.au8NotMatchByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);

        stSectionMonitor.u16PID             = PID_PAT;
        stSectionMonitor.u32SectionFltType   = MSAPI_DMX_FILTER_TYPE_SECTION_1K;
        stSectionMonitor.pfNotify = MApp_Dmx_PAT_Cb;
        stSectionMonitor.u16TimeoutMilliSec = PAT_SECTION_TIME_OUT_MS;
        stSectionMonitor.pu8FID = &u8MonitoringFID;
        stSectionMonitor.SectMode = DMX_SECT_MODE_ONESHOT|DMX_SECT_MODE_CRCCHK;
        stSectionMonitor.au8MatchByte[0]    = TID_PAS;  // table id
        stSectionMonitor.au8MaskByte[0]     = 0xFF;
        stSectionMonitor.au8MatchByte[5]    = 0x01;
        stSectionMonitor.au8MaskByte[5]     = 0x01;
        stSectionMonitor.au8MaskByte[6]     = 0xFF;

        for(iu8Loop_i = 1; iu8Loop_i <= u8LastSectionNumOfPat; iu8Loop_i++)
        {
            stSectionMonitor.au8MatchByte[6] = iu8Loop_i;//section number

            while(msAPI_DMX_SectionMonitor(&stSectionMonitor, FALSE) == DMX_FILTER_STATUS_ERROR)
            {
                msAPI_DMX_Proc(0xFF);
            }

            DMX_DBG(DMX_SCAN, printf("[PAT] Monitoring PAT sec# %d at Filter# %d \r\n", iu8Loop_i, u8MonitoringFID));
            u8OpenedFltCounter++;
        }

        DMX_DBG(DMX_SCAN, printf("[PAT] Wait until u8OpenedFltCounter = %d close to 0\n", u8OpenedFltCounter));

        while(u8OpenedFltCounter > 0) //wait until all openend filter is closed
        {
            msAPI_DMX_Proc(0xFF);
        }
    }
#endif

    /*[3-2]get multiple PMT =================================================*/
    if(u8NumOfPatItem > 0)
    {
        DMX_DBG(DMX_SCAN, printf("\033[45;37m<< PMT Start >>\033[0m\r\n"));

        memset(stSectionMonitor.au8MaskByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);
        memset(stSectionMonitor.au8NotMatchByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);

        stSectionMonitor.u32SectionFltType   = MSAPI_DMX_FILTER_TYPE_SECTION_1K;
        stSectionMonitor.pfNotify           = MApp_Dmx_PMT_Cb;
        stSectionMonitor.u16TimeoutMilliSec = SECTION_TIME_OUT_MS;
        stSectionMonitor.pu8FID             = &u8MonitoringFID;
        stSectionMonitor.SectMode           = DMX_SECT_MODE_ONESHOT|DMX_SECT_MODE_CRCCHK;
        stSectionMonitor.au8MaskByte[0]     = 0xFF;
        stSectionMonitor.au8MaskByte[3]     = 0xFF;
        stSectionMonitor.au8MaskByte[4]     = 0xFF;
        stSectionMonitor.au8MaskByte[5]     = 0x01;

        for(iu8Loop_i = 0; iu8Loop_i < u8NumOfPatItem; iu8Loop_i++)
        {
            u16ProgramNumberArray[iu8Loop_i] = pastPATItem[iu8Loop_i].u16ProgramNumber;

            /* skip Network PID (service id = 0) */
            if(pastPATItem[iu8Loop_i].u16ProgramNumber == 0)
            {
                continue;
            }

            //skip the duplicate program
            //spec ... the program number is the unique of one ts
            for(iu8Loop_j = 0; iu8Loop_j<iu8Loop_i; iu8Loop_j++)
            {
                if(u16ProgramNumberArray[iu8Loop_j] == pastPATItem[iu8Loop_i].u16ProgramNumber)
                {
                    continue;
                }

            }

            #if( WATCH_DOG == ENABLE )
            msAPI_Timer_ResetWDT();
            #endif

            stSectionMonitor.u16PID             = pastPATItem[iu8Loop_i].u16PID;
            stSectionMonitor.au8MatchByte[0]    = TID_PMS; //table id
            stSectionMonitor.au8MatchByte[3]    = HIGHBYTE(pastPATItem[iu8Loop_i].u16ProgramNumber); //subtable id
            stSectionMonitor.au8MatchByte[4]    = LOWBYTE(pastPATItem[iu8Loop_i].u16ProgramNumber);
            stSectionMonitor.au8MatchByte[5]    = 0x01;

            while(msAPI_DMX_SectionMonitor(&stSectionMonitor, FALSE) == DMX_FILTER_STATUS_ERROR)
            {
                msAPI_DMX_Proc(0xFF);
            }


            DMX_DBG(DMX_SCAN, printf("Monitoring PMT PID 0x%x, SID 0x%x at Filter# %d \r\n", pastPATItem[iu8Loop_i].u16PID, pastPATItem[iu8Loop_i].u16ProgramNumber, u8MonitoringFID));
            au8FID2ItemIdx[u8MonitoringFID] = iu8Loop_i;
            au16PID2ItemIdx[u8MonitoringFID] = pastPATItem[iu8Loop_i].u16PID;
            u8OpenedFltCounter++;
        }


        DMX_DBG(DMX_SCAN, printf("Wait until u8OpenedFltCounter = %d close to 0\n", u8OpenedFltCounter));
        while(u8OpenedFltCounter > 0) //wait until all openend filter is closed
        {
            msAPI_DMX_Proc(0xFF);
        }
    }

    /*[3-3]get first VCT ====================================================*/
    DMX_DBG(DMX_SCAN, printf("\033[45;37m<< VCT Start >>\033[0m\r\n"));

    u8LastSectionNo = 0;

    memset(stSectionGet.au8MaskByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);
    memset(stSectionGet.au8NotMatchByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);
    stSectionGet.u16PID             = PID_BASE;
    stSectionGet.u32SectionFltType  = MSAPI_DMX_FILTER_TYPE_SECTION_1K;
    stSectionGet.au8MatchByte[0]    = (ANT_TYPE == ANT_AIR) ? TID_TVCS : TID_CVCS;
    stSectionGet.au8MaskByte[0]     = 0xFE;
    stSectionGet.au8MatchByte[3]    = HIGHBYTE(u16ActualTSid); //subtable id
    stSectionGet.au8MatchByte[4]    = LOWBYTE(u16ActualTSid);
    stSectionGet.au8MatchByte[5]    = 0x01;
    stSectionGet.au8MatchByte[8]    = 0x00;

#if (ENABLE_VCT_TSID_MASK==1)
    stSectionGet.au8MaskByte[3]     = 0xFF;
    stSectionGet.au8MaskByte[4]     = 0xFF;
#else
    stSectionGet.au8MaskByte[3]     = 0x00;
    stSectionGet.au8MaskByte[4]     = 0x00;
#endif
    stSectionGet.au8MaskByte[5]     = 0x01;
    stSectionGet.au8MaskByte[8]     = 0xFF;

    stSectionGet.pu8Section         = au8Section;
    stSectionGet.u16MaxSecSize      = MSAPI_DMX_SECTION_1K;
    if(ANT_TYPE == ANT_AIR)
        stSectionGet.u16TimeoutMilliSec = TVCT_SECTION_TIME_OUT_MS; //
    else
        stSectionGet.u16TimeoutMilliSec = CVCT_SECTION_TIME_OUT_MS; //Max add for SEC NVH2 cable 90 do not get vct
    stSectionGet.bCheckCrc          = CRC_CHECK;
    enFilterStatus                  = msAPI_DMX_SectionGet(&stSectionGet);

    u8ErrorCheckCount = 0;
    u32SecCheckTime = msAPI_Timer_GetTime0();
    while((enFilterStatus > DMX_FILTER_STATUS_OK) && (u8ErrorCheckCount<=SECTION_GET_ERROR_CHECK_TIME))
    {
        if(msAPI_Timer_DiffTimeFromNow(u32SecCheckTime) > TVCT_SECTION_TIME_OUT_MS)
        {
            //printf("\r\n Check Section Timeout");
            break;
        }
        enFilterStatus = msAPI_DMX_SectionGet(&stSectionGet);
        u8ErrorCheckCount++;
    }

    switch(enFilterStatus)
    {
        case DMX_FILTER_STATUS_OK:
        {
        #if 0   // should be remove after
            if ( ( (au8Section[0]!=TID_TVCS) && (au8Section[0]!=TID_CVCS) )
              || ( au8Section[6] > au8Section[7] ) )
            {
                printf( "<< Wrong VCT Section >>\r\n" );
                MApp_Dmx_DumpSectionData( 29);
                while (1);
            }
        #endif


            /* get section range */
            u8FirstSectionNo = au8Section[6]; //get first section #
            u8LastSectionNo = au8Section[7];  //get last  section #

            DMX_DBG(DMX_SCAN, printf("VCT section #: %d/%d\n", u8FirstSectionNo, u8LastSectionNo));

            /* parsing table */
            MApp_Dmx_VCT_Parse(pastVirtualCh, au8Section);

            break;
        }
        case DMX_FILTER_STATUS_ERROR:
            stSectionGet.au8MaskByte[3] = 0x00;
            stSectionGet.au8MaskByte[4] = 0x00;
            enFilterStatus = msAPI_DMX_SectionGet(&stSectionGet);
            u8ErrorCheckCount = 0;
            u32SecCheckTime = msAPI_Timer_GetTime0();
            while((enFilterStatus > DMX_FILTER_STATUS_OK) && (u8ErrorCheckCount<=SECTION_GET_ERROR_CHECK_TIME))
            {
                if(msAPI_Timer_DiffTimeFromNow(u32SecCheckTime) > TVCT_SECTION_TIME_OUT_MS)
                {
                    //printf("\r\n Check Section Timeout 1");
                    break;
                }
                enFilterStatus = msAPI_DMX_SectionGet(&stSectionGet);
                u8ErrorCheckCount++;
            }

            if(enFilterStatus==DMX_FILTER_STATUS_OK)
            {
                u8FirstSectionNo = au8Section[6]; //get first section #
                u8LastSectionNo = au8Section[7];  //get last  section #
                DMX_DBG(DMX_SCAN, printf("Invalid TSId get ,VCT section #: %d/%d\n", u8FirstSectionNo, u8LastSectionNo));
                /* parsing table */
                MApp_Dmx_VCT_Parse(pastVirtualCh, au8Section);
                bIsInvalidTSId=1;
                break;
            }
            default:
            {
                DMX_DBG(DMX_SCAN, printf("get VCT error! enFilterStatus = %d\n", (U8)enFilterStatus));
            }
            break;
    }
    /*[3-4]get remainder VCT ================================================*/
    if(u8LastSectionNo > 0)
    {
        U16 u16Loop_i = 0;
        DMX_DBG(DMX_SCAN, printf("\033[45;37m<< VCT Start : remind section>>\033[0m\r\n"));

        memset(stSectionMonitor.au8MaskByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);
        memset(stSectionMonitor.au8NotMatchByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);
        stSectionMonitor.u16PID = PID_BASE;
        stSectionMonitor.u32SectionFltType = MSAPI_DMX_FILTER_TYPE_SECTION_1K;
        stSectionMonitor.pfNotify = MApp_Dmx_VCT_Cb;
        stSectionMonitor.u16TimeoutMilliSec = SECTION_TIME_OUT_MS;
        stSectionMonitor.pu8FID = &u8MonitoringFID;
        stSectionMonitor.SectMode = DMX_SECT_MODE_ONESHOT|DMX_SECT_MODE_CRCCHK;

        stSectionMonitor.au8MaskByte[0] = 0xFE;
        stSectionMonitor.au8MaskByte[3] = 0xFF;
        stSectionMonitor.au8MaskByte[4] = 0xFF;
        stSectionMonitor.au8MaskByte[5] = 0x3E;
        stSectionMonitor.au8MaskByte[6] = 0xFF;
        stSectionMonitor.au8MaskByte[8] = 0xFF;

        for(u16Loop_i = 0; u16Loop_i <= u8LastSectionNo; u16Loop_i++)
        {
            //skip this section (already got it) =============================//
            if(u16Loop_i == u8FirstSectionNo)
            {
                continue;
            }

            stSectionMonitor.au8MatchByte[0] = (ANT_TYPE == ANT_AIR) ? TID_TVCS : TID_CVCS;
            #if (!ENABLE_NEW_DMX_INTERFACE)
            if(bIsInvalidTSId)
            {
                stSectionMonitor.au8MatchByte[3] = 0xFF;
                stSectionMonitor.au8MatchByte[4] = 0xFF;
            }
            else
            {
                stSectionMonitor.au8MatchByte[3] = HIGHBYTE(u16ActualTSid); //subtable id
                stSectionMonitor.au8MatchByte[4] = LOWBYTE(u16ActualTSid);
            }
            #else
            if (bIsInvalidTSId == 0)
            {
                stSectionMonitor.au8MatchByte[3] = HIGHBYTE(u16ActualTSid); //subtable id
                stSectionMonitor.au8MatchByte[4] = LOWBYTE(u16ActualTSid);
            }
            #endif

            stSectionMonitor.au8MatchByte[5] = au8Section[5];
            stSectionMonitor.au8MatchByte[6] = u16Loop_i;//section number
            stSectionMonitor.au8MatchByte[8] = 0x00;

            while(msAPI_DMX_SectionMonitor(&stSectionMonitor, FALSE) == DMX_FILTER_STATUS_ERROR)
            {
                msAPI_DMX_Proc(0xFF);
            }

            DMX_DBG(DMX_SCAN, printf("Monitoring VCT sec# %d at Filter# %d \r\n", u16Loop_i, u8MonitoringFID));

            u8OpenedFltCounter++;
        }

        DMX_DBG(DMX_SCAN, printf("Wait until u8OpenedFltCounter = %d close to 0\n", u8OpenedFltCounter));
        while(u8OpenedFltCounter > 0) //wait until all openend filter is closed
        {
            msAPI_DMX_Proc(0xFF);
        }
    }
    /*[4]finalize ===========================================================*/
    DMX_DBG(DMX_SCAN, printf("<<<<End of MApp_Dmx_GetScanTables_ATSC! ==================\r\n"));

    return EN_PARSER_NO_ERROR;
}

BOOLEAN MApp_Dmx_CheckPATTimeout(void)
{
	return g_fPatTimeout;
}

/*****************************************************************************/
void MApp_Dmx_EnableTableMonitor_ATSC(void)
{
    MS_RF_CHANNEL_new stRfChTmp;

    // init version number if RF channel change
    MApp_ChanProc_GetRfChannelPointer(MApp_ChanProc_GetCurChannelPointer(), &stRfChTmp);

    if( !msAPI_Tuner_IsSameRfChannel_ATSC( &(stRfChTmp.stTPSetting)) )
    {
        stMGT.version_number = INVALID_VERSION_NUM;
        //    #if (EPG_THIS_CH != TRUE)
        //        MApp_EpgDB_Reset();
        //    #endif
    }


    MApp_EpgDB_Reset();
    MApp_EPG_Demux_Reset();

#if (ENABLE_ATSC_EPG_DB_2016)
    memset(&g_stCurrentEvent, 0, sizeof(MS_EPG_EVENT_New));
    g_stCurrentEvent.event_id= INVALID_EVENT_ID;

    #if(ATSC_EPG_ONLY_CUR_CHANNEL)
        msAPI_AtscEpgDb_ResetDB();
    #endif
#endif


#if (ENABLE_ATSC_EPG_DB_2016)
    //memset(&(stEitParseParam.u8EitSaveIndex[0]), 0, sizeof(U8)*NEW_MAX_TAB_NUM);
#else
    memset(&(stEitParseParam.u8EitSaveIndex[0]), 0, sizeof(U8)*MAX_TBL_NUM);
#endif

    //#endif

    /* force to monitor table once */
    fEnableSttMonitor = TRUE;
    fEnableMgtMonitor = TRUE;
    fEnableVctMonitor = TRUE;
    fEnablePatMonitor = TRUE;
    fEnableRRTMonitor = TRUE;
    fEnablePmtMonitor = TRUE;
#if ENABLE_OAD
    fEnablePmtOtherMonitor = TRUE;
#endif
    fEnableEasMonitor = TRUE;
    g_u32MonitorCADTimer = msAPI_Timer_GetTime0();

    fEnableTableMonitor = TRUE;
    fSearchRatingfromPMT = FALSE;
    fSearchEventTitlefromEIT = FALSE;

#if (ENABLE_MEXICO_VCHIP)
    u8CurrentRrtRegionNo = 0;
    if(u8LastRrtRegionNo == 0)
    {
        u8LastRrtRegionNo =stGenSettingVchipRegion5.u8LastUpdateRegion;
    }
    else
    {
        u8LastRrtRegionNo = 0;
    }
#endif

#if 0//(ENABLE_MAX_RRT_DIMENSION_NUMBER == 0)
    if (u8NumOfPatItem == 0)
    {
        u8LastPatItemNo = 0;
    }
#endif

    u8CurrentEitFilterUse = 0;

}
/*****************************************************************************/
void MApp_Dmx_DisableTableMonitor_ATSC(void)
{
    U16 u16Loop_i = 0;
    fEnableTableMonitor = FALSE;

    if (u8PatFid != MSAPI_DMX_INVALID_FLT_ID)
    {
        msAPI_DMX_Stop(u8PatFid);
        msAPI_DMX_Close(u8PatFid);
        u8PatFid = MSAPI_DMX_INVALID_FLT_ID;
    }

    if (u8PmtFid != MSAPI_DMX_INVALID_FLT_ID)
    {
        msAPI_DMX_Stop(u8PmtFid);
        msAPI_DMX_Close(u8PmtFid);
        u8PmtFid = MSAPI_DMX_INVALID_FLT_ID;
    }
#if ENABLE_OAD
    if (u8PmtOtherFid != MSAPI_DMX_INVALID_FLT_ID)
    {
        msAPI_DMX_Stop(u8PmtOtherFid);
        msAPI_DMX_Stop(u8PmtOtherFid);
        u8PmtOtherFid = MSAPI_DMX_INVALID_FLT_ID;
    }
#endif
    if (u8MgtFid != MSAPI_DMX_INVALID_FLT_ID)
    {
        msAPI_DMX_Stop(u8MgtFid);
        msAPI_DMX_Close(u8MgtFid);
        u8MgtFid = MSAPI_DMX_INVALID_FLT_ID;
    }

    if (u8EasFid != MSAPI_DMX_INVALID_FLT_ID)
    {
        msAPI_DMX_Stop(u8EasFid);
        msAPI_DMX_Close(u8EasFid);
        u8EasFid = MSAPI_DMX_INVALID_FLT_ID;
    }

    if (u8SttFid != MSAPI_DMX_INVALID_FLT_ID)
    {
        msAPI_DMX_Stop(u8SttFid);
        msAPI_DMX_Close(u8SttFid);
        u8SttFid = MSAPI_DMX_INVALID_FLT_ID;
    }

    if (u8VctFid != MSAPI_DMX_INVALID_FLT_ID)
    {
        msAPI_DMX_Stop(u8VctFid);
        msAPI_DMX_Close(u8VctFid);
        u8VctFid = MSAPI_DMX_INVALID_FLT_ID;
    }

    if (u8RRTFid != MSAPI_DMX_INVALID_FLT_ID)
    {
        msAPI_DMX_Stop(u8RRTFid);
        msAPI_DMX_Close(u8RRTFid);
        u8RRTFid = MSAPI_DMX_INVALID_FLT_ID;
    }

  #if (ENABLE_ATSC_EPG_DB_2016)
    for (u16Loop_i = 0; u16Loop_i < NEW_MAX_TAB_NUM; u16Loop_i++)
  #else
    for (u16Loop_i = 0; u16Loop_i < MAX_TBL_NUM; u16Loop_i++)
  #endif
    {
        if (stEpgDBInfo.au8FID[u16Loop_i] != MSAPI_DMX_INVALID_FLT_ID)
        {
            msAPI_DMX_CloseFilter(stEpgDBInfo.au8FID[u16Loop_i]);
            stEpgDBInfo.au8FID[u16Loop_i] = MSAPI_DMX_INVALID_FLT_ID;
        }

        if(stEpgDBInfo.au8EttFID[u16Loop_i] != MSAPI_DMX_INVALID_FLT_ID)
        {
            msAPI_DMX_CloseFilter(stEpgDBInfo.au8EttFID[u16Loop_i]);
            stEpgDBInfo.au8EttFID[u16Loop_i] = MSAPI_DMX_INVALID_FLT_ID;
        }
    }

#if (EIT_VN_CHANGE_FOR_RRT==TRUE)
    if (stEpgDBInfo.u8FID_EitMonitorForRRT != MSAPI_DMX_INVALID_FLT_ID)
    {
        msAPI_DMX_CloseFilter(stEpgDBInfo.u8FID_EitMonitorForRRT);
        stEpgDBInfo.u8FID_EitMonitorForRRT = MSAPI_DMX_INVALID_FLT_ID;
    }
#endif
}

/*****************************************************************************/
void MApp_Dmx_CloseAllFilters_ATSC(void)
{
    U8 i;

    /* release all filter */
    for(i = 0; i < MSAPI_DMX_MAX_FILTER_NUMBER; i++)
    {
        msAPI_DMX_CloseFilter(i);
    }

    u8PcrFid = MSAPI_DMX_INVALID_FLT_ID;
    u8AudFid = MSAPI_DMX_INVALID_FLT_ID;
#if (ENABLE_ATSC_AD_FUNC)
    u8AudFid2= MSAPI_DMX_INVALID_FLT_ID;
#endif
    u8VidFid = MSAPI_DMX_INVALID_FLT_ID;
    u8SttFid = MSAPI_DMX_INVALID_FLT_ID;
    u8MgtFid = MSAPI_DMX_INVALID_FLT_ID;
    u8VctFid = MSAPI_DMX_INVALID_FLT_ID;
    u8PatFid = MSAPI_DMX_INVALID_FLT_ID;
    u8PmtFid = MSAPI_DMX_INVALID_FLT_ID;
#if ENABLE_OAD
    u8PmtOtherFid = MSAPI_DMX_INVALID_FLT_ID;
#endif
    u8EasFid = MSAPI_DMX_INVALID_FLT_ID;
    u8RRTFid = MSAPI_DMX_INVALID_FLT_ID;

#if( !ENABLE_ATSC_EPG_DB_2016 )
    stEpgETT.u8FID = MSAPI_DMX_INVALID_FLT_ID;
#endif

    for (i = 0; i < PSIP_EIT_ETT_TABLE_NUMBER; i++)
    {
        stEpgDBInfo.au8FID[i] = MSAPI_DMX_INVALID_FLT_ID;
        stEpgDBInfo.au8EttFID[i] = MSAPI_DMX_INVALID_FLT_ID;
    }


#if (EIT_VN_CHANGE_FOR_RRT==TRUE)
    //if (stEpgDBInfo.u8FID_EitMonitorForRRT != MSAPI_DMX_INVALID_FLT_ID)
    {
        //msAPI_DMX_CloseFilter(stEpgDBInfo.u8FID_EitMonitorForRRT);
        stEpgDBInfo.u8FID_EitMonitorForRRT = MSAPI_DMX_INVALID_FLT_ID;
    }
#endif

}

const MS_PAT_ITEM_ATSC* MApp_PSIP_Get_PATItem(U8 u8PatItemIdx)
{
    if( u8PatItemIdx >= MAX_VC_PER_PHYSICAL )
        return NULL;

    return &(g_PSIP_astPATItem[u8PatItemIdx]);
}

void MApp_Psip_Print_EPGInfo(void)
{
    msAPI_DMX_Print_AllFilter();

    U8 u8TblIdx;

    printf("\nEit[%u]:\n", PSIP_EIT_TABLE_NUMBER);
    printf(" u8FID_EitMonitorForRRT=%u\n", stEpgDBInfo.u8FID_EitMonitorForRRT);

    for (u8TblIdx = 0; u8TblIdx < PSIP_EIT_TABLE_NUMBER; u8TblIdx++)
    {
        if( stEpgDBInfo.au8FID[u8TblIdx] != 255 )
        {
            printf(" Eit[%u]=>Fid=%u\n", u8TblIdx, stEpgDBInfo.au8FID[u8TblIdx]);
        }
    }

    printf("\nEtt[%u]:\n", PSIP_ETT_TABLE_NUMBER);
    for (u8TblIdx = 0; u8TblIdx < PSIP_ETT_TABLE_NUMBER; u8TblIdx++)
    {
        if( stEpgDBInfo.au8EttFID[u8TblIdx] != 255 )
        {
            printf(" Ett[%u]=>Fid=%u\n", u8TblIdx, stEpgDBInfo.au8EttFID[u8TblIdx]);
        }
    }
}


#undef MAPP_PSIP_C
