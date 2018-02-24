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

#define MAPP_SI_UTIL_C
/******************************************************************************/
/*                       Header Files                                         */
/******************************************************************************/
#include "Board.h"
#if(ENABLE_DTV)

// C Library
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

// Global Layer
#include "datatype.h"

#include "apiAUDIO.h"

#include "msAPI_Timer.h"
#include "msAPI_Memory.h"
#include "msAPI_MIU.h"
#include "msAPI_DTVSystem.h"
#include "msAPI_audio.h"


#if (ENABLE_SBTVD_SI || ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
#include "msAPI_FreqTableDTV.h"
#endif
#include "mapp_demux.h"
#include "mapp_si.h"
#if (ENABLE_DTV_EPG)
#include "mapp_eit.h"
#endif
#include "msAPI_Tuner.h"
#include "msAPI_Global.h"
#include "debug.h"

#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"
// MW Layer
#include "mw_debug.h"
#include "mapp_si_if.h"
#include "MApp_GlobalSettingSt.h"
#include "msAPI_FreqTableDTV.h"
#include "MApp_CharTable.h"

MEMBER_SERVICETYPE msAPI_SI_ToCM_Service_Type(MEMBER_SI_SERVICETYPE btype)
{
    switch(btype)
    {
        case E_TYPE_RADIO:
            return E_SERVICETYPE_RADIO;
        case E_TYPE_DATA:
            return E_SERVICETYPE_DATA;
        default:
        case E_TYPE_DTV:
            return E_SERVICETYPE_DTV;
    }
}

MEMBER_SI_SERVICETYPE msAPI_SI_ToSI_Service_Type(MEMBER_SERVICETYPE btype)
{
    switch(btype)
    {
        case E_SERVICETYPE_RADIO:
            return E_TYPE_RADIO;
        case E_SERVICETYPE_DATA:
            return E_TYPE_DATA;
        default:
        case E_SERVICETYPE_DTV:
            return E_TYPE_DTV;
    }
}
U8 msAPI_SI_ToCM_Audio_Mode(U8 btype)
{
    switch(btype)
    {
        case E_SI_AUDIOMODE_STEREO:
            return 0;
        case E_SI_AUDIOMODE_RR:
            return 1;
        default:
        case E_SI_AUDIOMODE_LL:
            return 2;
    }
}

U8 msAPI_SI_ToCM_Audio_Type(U8 btype)
{
    switch(btype)
    {
        case E_SI_AUDIOSTREAM_AC3:
            return E_AUDIOSTREAM_AC3;
        case E_SI_AUDIOSTREAM_MPEG4:
            return E_AUDIOSTREAM_MPEG4;
        case E_SI_AUDIOSTREAM_AAC:
            return E_AUDIOSTREAM_AAC;
        case E_SI_AUDIOSTREAM_AC3P:
            return E_AUDIOSTREAM_AC3P;
        case E_SI_AUDIOSTREAM_MPEG:
            return E_AUDIOSTREAM_MPEG;
        case E_SI_AUDIOSTREAM_DRA:
            return E_AUDIOSTREAM_DRA;
        default:
        case E_SI_AUDIOSTREAM_INVALID:
            return E_AUDIOSTREAM_INVALID;

    }
}

U8 msAPI_SI_ToCM_Video_Type(U8 btype)
{
    switch(btype)
    {
        case E_SI_VIDEOTYPE_H264:
            return E_VIDEOTYPE_H264;

        case E_SI_VIDEOTYPE_H265:
            return E_VIDEOTYPE_H265;

        case E_SI_VIDEOTYPE_AVS:
            return E_VIDEOTYPE_AVS;
        case E_SI_VIDEOTYPE_VC1:
            return E_VIDEOTYPE_VC1;
        default:
        case E_SI_VIDEOTYPE_MPEG:
            return E_VIDEOTYPE_MPEG;
    }
}

U8 msAPI_SI_ToCM_Service_Priority(U8 bPriority)
{
    switch(bPriority)
    {
        case E_SI_SERVICETYPE_PRIORITY_HIGH:
            return E_SERVICETYPE_PRIORITY_HIGH;
        case E_SI_SERVICETYPE_PRIORITY_MIDDLE:
            return E_SERVICETYPE_PRIORITY_MIDDLE;
        case E_SI_SERVICETYPE_PRIORITY_LOW:
            return E_SERVICETYPE_PRIORITY_LOW;
        default:
        case E_SI_SERVICETYPE_PRIORITY_NONE:
            return E_SERVICETYPE_PRIORITY_NONE;
    }
}

EN_DELIVERY_SYS_TYPE msAPI_SI_ToCM_Delivery_Type(EN_SI_DELIVERY_SYS_TYPE btype)
{
    switch(btype)
    {
        case E_SI_DELIVERY_SYS_SDSD:
            return E_DELIVERY_SYS_SDSD;
        case E_SI_DELIVERY_SYS_TDSD:
            return E_DELIVERY_SYS_TDSD;
        case E_SI_DELIVERY_SYS_CDSD:
            return E_DELIVERY_SYS_CDSD;
        default:
            return E_DELIVERY_SYS_NONE;
    }
}

E_CM_PROFILE_AND_LEVEL msAPI_SI_ToCM_ProfileAndLevel(U8 u8SIProfileAndLevel)
{
    switch(u8SIProfileAndLevel)
    {
        case AAC_LEVEL1:
            return E_CM_PROFILE_AAC_LEVEL1;

        case AAC_LEVEL2:
            return E_CM_PROFILE_AAC_LEVEL2;

        case AAC_LEVEL4:
            return E_CM_PROFILE_AAC_LEVEL4;

        case AAC_LEVEL5:
            return E_CM_PROFILE_AAC_LEVEL5;

        case HE_AAC_LEVEL2:
        case HE_AAC_V2_LEVEL2:
            return E_CM_PROFILE_HE_AAC_LEVEL2;

        case HE_AAC_LEVEL3:
        case HE_AAC_V2_LEVEL3:
            return E_CM_PROFILE_HE_AAC_LEVEL3;

        case HE_AAC_LEVEL4:
        case HE_AAC_V2_LEVEL4:
            return E_CM_PROFILE_HE_AAC_LEVEL4;

        case HE_AAC_LEVEL5:
        case HE_AAC_V2_LEVEL5:
            return E_CM_PROFILE_HE_AAC_LEVEL5;

        default:
            break;
    }

    return E_CM_PROFILE_NONE;
}

void msAPI_SI_Copy_SI_AudInfo_To_CM_AudInfo(SI_AUD_INFO* pstSI_AudInfo, AUD_INFO* pstCM_AudInfo, U8 u8Count)
{
    U8 u8Aud_ISOLang_MinNum = (MAX_AUD_ISOLANG_NUM > SI_MAX_AUD_ISOLANG_NUM) ? SI_MAX_AUD_ISOLANG_NUM : MAX_AUD_ISOLANG_NUM;
    U8 i;
    U8 j;

    for( i = 0; i < u8Count; ++ i)
    {
        //DTVProgramData.stAudInfo[i].wAudType = msAPI_SI_ToCM_Audio_Type(pSIDTVProgramData->stAudInfo[i].wAudType);
        pstCM_AudInfo[i].eSIAudType = (SI_AUDIOSTREAM_TYPE)pstSI_AudInfo[i].wAudType;

        pstCM_AudInfo[i].wAudPID = pstSI_AudInfo[i].wAudPID;

        //printf("%u PID=0x%X, Typ=%u\n", i, pstSI_AudInfo[i].wAudPID, pstSI_AudInfo[i].wAudType);

        pstCM_AudInfo[i].eProfileAndLevel = msAPI_SI_ToCM_ProfileAndLevel(pstSI_AudInfo[i].u8ProfileAndLevel);
        //pstCM_AudInfo[i].u8Component_AAC_Type = pstSI_AudInfo[i].u8Component_AAC_Type;

        for(j=0; j<u8Aud_ISOLang_MinNum; ++ j )
        {
            pstCM_AudInfo[i].aISOLangInfo[j].bISOLangIndex = pstSI_AudInfo[i].aISOLangInfo[j].bISOLangIndex;
            pstCM_AudInfo[i].aISOLangInfo[j].bISOLanguageInfo = msAPI_SI_ToCM_Audio_Mode(pstSI_AudInfo[i].aISOLangInfo[j].bISOLanguageInfo);
            pstCM_AudInfo[i].aISOLangInfo[j].bAudType = pstSI_AudInfo[i].aISOLangInfo[j].bAudType;
            pstCM_AudInfo[i].aISOLangInfo[j].bIsValid = pstSI_AudInfo[i].aISOLangInfo[j].bIsValid;
            pstCM_AudInfo[i].aISOLangInfo[j].bBroadcastMixedAD = pstSI_AudInfo[i].aISOLangInfo[j].bBroadcastMixedAD;
            pstCM_AudInfo[i].aISOLangInfo[j].bReserved = pstSI_AudInfo[i].aISOLangInfo[j].bReserved;
        }
    }
}


#endif//#if(ENABLE_DTV)
#undef MAPP_SI_UTIL_C

