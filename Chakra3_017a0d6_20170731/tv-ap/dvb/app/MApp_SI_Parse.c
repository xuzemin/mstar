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
#define MAPP_SI_PARSE_C


//------------------------------------------------------------------------------
//                    Header Files
//------------------------------------------------------------------------------
#include <string.h>
#include <stdio.h>

#include "Board.h"
#include "debug.h"
#include "datatype.h"
#include "msAPI_Global.h"
#include "apiXC.h"
#include "apiXC_Adc.h"

#include "msAPI_audio.h"
#include "msAPI_Timer.h"
#include "msAPI_MIU.h"
#include "msAPI_Memory.h"        //PAT/PMT Parsing when ch change
#include "msAPI_DTVSystem.h"
#if ENABLE_CI
#include "msAPI_CI.h"
#endif
#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalVar.h"
#include "MApp_GlobalFunction.h"
#include "mapp_si.h"
#include "MApp_Subtitle.h"
#if (ENABLE_TTX)
#include "msAPI_TTX.h"
#include "mapp_ttx.h"
#endif
#include "mapp_eit.h"
#include "mapp_si.h"
#include "MApp_ZUI_Main.h"
#include "ZUI_tables_h.inl"
#include "MApp_UiMenuDef.h"
#include "MApp_ChannelChange.h"
#include "MApp_Audio.h"
#if ENABLE_OAD
#include "MApp_OAD.h"
#include "imginfo.h"
#endif
#if (ENABLE_CI_PLUS)
#include "mapp_demux.h"
#include "MApp_CIMMI.h"
#endif
#if(ENABLE_DTV)
//#if (ENABLE_SBTVD_BRAZIL_APP == 0)
#if ENABLE_SUBTITLE
#include "MApp_TV.h"
#endif
//#endif
#endif

/********************************************************************************/
/*                     Macro                    */
/********************************************************************************/


/********************************************************************************/
//                     Local
/*********************************************************************************/
#if (ENABLE_DTV_EPG)

#if(ENABLE_DVB_NOISDB)
static void _MApp_SI_Parse_Reset_Component(void);
static void _MApp_SI_Parse_Update_Component(E_COMPONENT_TYPE eType, BYTE *lang);
static BOOL _MApp_SI_Parse_Restart_Component(void);
static U16 _u16TempValidAudioIndex=0;
static U32 _u32TempValidSubtitleIndex=0;
#endif

BOOL MApp_SI_Parse_EIT(U8 *pu8Section)
{
    U16 u16TotalDescriptorLength;
    U8  *pu8Descriptor;
    U8  *pu8LoopPosition;
    S16 s16TotalDescriptorLength;

    U8 u8PreDescTag=0;
    E_COMPONENT_TYPE ePreComponentType=E_COMPONENT_UNSUPPORT;

#if(!ENABLE_DVB_NOISDB)
    UNUSED(u8PreDescTag);
    UNUSED(ePreComponentType);
#endif

    #if(ENABLE_SBTVD_SI)
        if(!msAPI_SRC_IS_SBTVD_InUse())
    #endif
        {
        #if(ENABLE_DVB_NOISDB)
            if( (pu8Section[6]==0))
            {
                _MApp_SI_Parse_Reset_Component();
            }
        #endif
        }

    // [2] goto first loop position
    pu8LoopPosition = MApp_SI_FindLoopHead(pu8Section,EN_EIT,EN_FIRSTLOOP);
    // [3]  Event Loop
    while (pu8LoopPosition != NULL)
    {
        // (3)  Calculate total descriptor length, descriptor tag position,
        u16TotalDescriptorLength = ((pu8LoopPosition[10] & 0x0f) << 8) | pu8LoopPosition[11];
        s16TotalDescriptorLength = (S16)u16TotalDescriptorLength;
        pu8Descriptor            = pu8LoopPosition + 12;

        while (s16TotalDescriptorLength > 0)
        {
            #if (ENABLE_SBTVD_SI)
            //descriptor tag
            switch (pu8Descriptor[0])
            {

                case TAG_ACD:
                    if((pu8Section[0] == TID_EIS_ACTUAL_PF && pu8Section[6] == 0) &&
                        MApp_SI_Get_PSISIVersion(E_VER_PMT) != INVALID_VERSION_NUM)
                    {
                        SI_LANG_ISO639 stISOLangInfo;

                        stISOLangInfo.bISOLangIndex = (U8)msAPI_SI_GetLanguageByISO639LangCode(&pu8Descriptor[8]);
                        if(stISOLangInfo.bISOLangIndex != SI_LANGUAGE_NONE &&
                           stISOLangInfo.bISOLangIndex != SI_LANGUAGE_UNKNOWN)
                        {
                            //Refer to ABNT NBR 15603-2:2007 Table 49 - Audio component descriptor
                            switch(pu8Descriptor[3])
                            {
                                case 0x41:
                                case 0x46:
                                case 0xA0:
                                    stISOLangInfo.bAudType = 2; //Hearing Imparied
                                    break;
                                case 0x40:
                                case 0x42:
                                case 0x45:
                                case 0x47:
                                case 0x9F:
                                case 0xA1:
                                    stISOLangInfo.bAudType = 3; //Visual Imparied
                                    break;
                                default:
                                    stISOLangInfo.bAudType = 0; //Undefined
                                    break;
                            }

                            stISOLangInfo.bISOLanguageInfo = 0; //stereo

                            MApp_SI_Update_Audio(pu8Descriptor[4], &stISOLangInfo, 1);//20090806
                        }
                    }
                    break;
                 default:
                    break;
            }
            #endif

            #if(ENABLE_SBTVD_SI)
                if(!msAPI_SRC_IS_SBTVD_InUse())
            #endif
            {
                #if(ENABLE_DVB_NOISDB)
                switch (pu8Descriptor[0])
                {
                    case TAG_MCD:
                    {
                        if((0 == pu8Section[6]) && (u8PreDescTag==TAG_CpD || u8PreDescTag==TAG_MCD) && (ePreComponentType!=E_COMPONENT_UNSUPPORT))
                        {
                            U8 text_description_length;
                            S16 s16TotalDesLength;
                            U8  *pu8Desc;
                            s16TotalDesLength=pu8Descriptor[1];
                            s16TotalDesLength-=1;
                            pu8Desc=pu8Descriptor+3;
                            while(s16TotalDesLength>0)
                            {
                                _MApp_SI_Parse_Update_Component(ePreComponentType,pu8Desc);
                                s16TotalDesLength-=4;
                                pu8Desc+=3;
                                text_description_length=pu8Desc[0];
                                pu8Desc+=(text_description_length+1);
                                s16TotalDesLength-=text_description_length;

                            }

                        }
                        break;
                    }
                    case TAG_CpD:
                    {
                        if((0 == pu8Section[6]))
                        {
                            ePreComponentType=E_COMPONENT_UNSUPPORT;
                            if((pu8Descriptor[2]&0x0f) == 0x02/*mpeg*/)
                            {
                                _MApp_SI_Parse_Update_Component(E_COMPONENT_MPEG_AUDIO,&pu8Descriptor[5]);
                                ePreComponentType=E_COMPONENT_MPEG_AUDIO;
                            }
                            else if((pu8Descriptor[2]&0x0f) == 0x04/*AC3*/)
                            {
                                _MApp_SI_Parse_Update_Component(E_COMPONENT_AC3_AUDIO,&pu8Descriptor[5]);
                                ePreComponentType=E_COMPONENT_AC3_AUDIO;
                            }
                            else if((pu8Descriptor[2]&0x0f) == 0x06/*HE-AAC*/)
                            {
                                _MApp_SI_Parse_Update_Component(E_COMPONENT_AAC_AUDIO,&pu8Descriptor[5]);
                                ePreComponentType=E_COMPONENT_AAC_AUDIO;
                            }
                            else if((pu8Descriptor[2]&0x0f) == 0x03/*teletext and subtitle*/)
                            {

                                if(pu8Descriptor[3] == 0x01)//gor EBU subtitle
                                {
                                    _MApp_SI_Parse_Update_Component(E_COMPONENT_EBU_SUBTITLE,&pu8Descriptor[5]);
                                    ePreComponentType=E_COMPONENT_EBU_SUBTITLE;
                                }
                                else if((pu8Descriptor[3]>=0x10 && pu8Descriptor[3] <=0x14)
                                    ||(pu8Descriptor[3]>=0x20 && pu8Descriptor[3] <=0x24))
                                {

                                    _MApp_SI_Parse_Update_Component(E_COMPONENT_DVB_SUBTITLE,&pu8Descriptor[5]);
                                    ePreComponentType=E_COMPONENT_DVB_SUBTITLE;
                                }
                            }
                        }
                        break;
                    }
                    default:
                        break;
                }
                #endif
            }
            #if(ENABLE_SBTVD_SI)
            if(!msAPI_SRC_IS_SBTVD_InUse())
            #endif
            {
#if(ENABLE_DVB_NOISDB)
                u8PreDescTag=pu8Descriptor[0];
#endif
            }

            s16TotalDescriptorLength -= (pu8Descriptor[1]+2);
            pu8Descriptor += (pu8Descriptor[1]+2);
        }
        /* move to descriptor position to find extended event descriptor */
        pu8Descriptor = pu8LoopPosition + 12;
        s16TotalDescriptorLength = (S16)u16TotalDescriptorLength;

        // (5) goto next loop position
        pu8LoopPosition = MApp_SI_FindNextLoop(pu8Section, pu8LoopPosition, u16TotalDescriptorLength, EN_EIT);

    }


#if(ENABLE_SBTVD_SI)
    if(!msAPI_SRC_IS_SBTVD_InUse())
#endif
    {
#if(ENABLE_DVB_NOISDB)
        if((0 == pu8Section[6]))
        {
            return _MApp_SI_Parse_Restart_Component();
        }
#endif
    }
    return TRUE;

}

#if(ENABLE_DVB_NOISDB)
static void _MApp_SI_Parse_Reset_Component(void)
{
    _u16TempValidAudioIndex=0;
    _u32TempValidSubtitleIndex=0;

}
static void _MApp_SI_Parse_Update_Component(E_COMPONENT_TYPE eType, BYTE *lang)
{
    MEMBER_SERVICETYPE bServiceType;
    WORD wCurrentPosition;
    BYTE bISOLangIndex=msAPI_SI_GetLanguageByISO639LangCode(lang);
    bServiceType = msAPI_CM_GetCurrentServiceType();
    wCurrentPosition = msAPI_CM_GetCurrentPosition(bServiceType);

    if(eType == E_COMPONENT_MPEG_AUDIO)
    {
        msAPI_CM_SetAudioStreamValidIndex(bServiceType,wCurrentPosition,E_AUDIOSTREAM_MPEG,bISOLangIndex,&_u16TempValidAudioIndex);
        if(bISOLangIndex == SI_LANGUAGE_ENGLISH)
        {
            msAPI_CM_SetAudioStreamValidIndex(bServiceType,wCurrentPosition,E_AUDIOSTREAM_MPEG,SI_LANGUAGE_UND,&_u16TempValidAudioIndex);
        }
    }
    else if(eType == E_COMPONENT_AC3_AUDIO)
    {
        msAPI_CM_SetAudioStreamValidIndex(bServiceType,wCurrentPosition,E_AUDIOSTREAM_AC3,bISOLangIndex,&_u16TempValidAudioIndex);
        msAPI_CM_SetAudioStreamValidIndex(bServiceType,wCurrentPosition,E_AUDIOSTREAM_AC3P,bISOLangIndex,&_u16TempValidAudioIndex);
        if(bISOLangIndex == SI_LANGUAGE_ENGLISH)
        {
            msAPI_CM_SetAudioStreamValidIndex(bServiceType,wCurrentPosition,E_AUDIOSTREAM_AC3,SI_LANGUAGE_UND,&_u16TempValidAudioIndex);
            msAPI_CM_SetAudioStreamValidIndex(bServiceType,wCurrentPosition,E_AUDIOSTREAM_AC3P,SI_LANGUAGE_UND,&_u16TempValidAudioIndex);
        }
    }
    else if(eType == E_COMPONENT_AAC_AUDIO)
    {
        msAPI_CM_SetAudioStreamValidIndex(bServiceType,wCurrentPosition,E_AUDIOSTREAM_AAC,bISOLangIndex,&_u16TempValidAudioIndex);
        msAPI_CM_SetAudioStreamValidIndex(bServiceType,wCurrentPosition,E_AUDIOSTREAM_MPEG4,bISOLangIndex,&_u16TempValidAudioIndex);
        if(bISOLangIndex == SI_LANGUAGE_ENGLISH)
        {
            msAPI_CM_SetAudioStreamValidIndex(bServiceType,wCurrentPosition,E_AUDIOSTREAM_AAC,SI_LANGUAGE_UND,&_u16TempValidAudioIndex);
            msAPI_CM_SetAudioStreamValidIndex(bServiceType,wCurrentPosition,E_AUDIOSTREAM_MPEG4,SI_LANGUAGE_UND,&_u16TempValidAudioIndex);
        }
    }
#if ENABLE_SUBTITLE
    else if(eType == E_COMPONENT_EBU_SUBTITLE)
    {
        MApp_Subtitle_SetValidIndex(SUBTITLING_TYPE_TELETEXT,lang,&_u32TempValidSubtitleIndex);
        MApp_Subtitle_SetValidIndex(SUBTITLING_TYPE_TELETEXT_HOH,lang,&_u32TempValidSubtitleIndex);
    }
    else if(eType == E_COMPONENT_DVB_SUBTITLE)
    {
        MApp_Subtitle_SetValidIndex(SUBTITLING_TYPE_NORMAL_NO,lang,&_u32TempValidSubtitleIndex);
    }
#endif
}
static BOOL _MApp_SI_Parse_Restart_Component(void)
{
    MEMBER_SERVICETYPE bServiceType=E_SERVICETYPE_DTV;
    WORD wCurrentPosition=0,wAudioPID,wONID;
    BOOL bSuccess=TRUE;
    bServiceType = msAPI_CM_GetCurrentServiceType();
    wCurrentPosition = msAPI_CM_GetCurrentPosition(bServiceType);
    wONID = msAPI_CM_GetON_ID(bServiceType,wCurrentPosition);

#if (ENABLE_SUBTITLE)
    if( _u32TempValidSubtitleIndex && (_u32TempValidSubtitleIndex != gCurValidSubtitleIndex) && u8SubtitleMenuNum && (OSD_COUNTRY_SETTING == OSD_COUNTRY_NEWZEALAND) )
    {
        U8 preSutitleItemSelIdx=u8SubtitleItemSelIdx;
        if(E_OSD_SUBTITLE_LANGUAGE == MApp_ZUI_GetActiveOSD())
        {
            bSuccess=FALSE;
        }
        else
        {
            bServiceType = msAPI_CM_GetCurrentServiceType();
            wCurrentPosition = msAPI_CM_GetCurrentPosition(bServiceType);
            wONID = msAPI_CM_GetON_ID(bServiceType,wCurrentPosition);
            if(((wONID == 0x222A) || (wONID == 0x233A)))
            {
                u8SubtitleItemSelIdx=MApp_Subtitle_ReArrange(_u32TempValidSubtitleIndex,u8SubtitleItemSelIdx);
                if(preSutitleItemSelIdx && (0==u8SubtitleItemSelIdx))
                {
#if ENABLE_TTX
                    if( (MApp_TTX_GetControlMode()==TTX_MODE_SUBTITLE))
                    {
                        MApp_TTX_TeletextCommand(TTX_TV);

                    }
#endif
                    UI_Hotkey_Subtitle=FALSE;
                }
            }
        }
    }
#endif

    if( IS_EIT_COMPONENT_COUNTRY(OSD_COUNTRY_SETTING) &&_u16TempValidAudioIndex && (msAPI_CM_Get_AudioValidIndex() != _u16TempValidAudioIndex))
    {
        BOOLEAN bNeedUpdate=TRUE;
        BYTE AudioNum,i;
        AUD_INFO aAudioStreamInfo;
#if (BLOADER)
        if(1);
#else
        if(E_OSD_AUDIO_LANGUAGE == MApp_ZUI_GetActiveOSD())
        {
            bSuccess=FALSE;
        }
#endif
        else
        {
            wONID = msAPI_CM_GetON_ID(bServiceType,wCurrentPosition);

            if(((wONID == 0x222A) || (wONID == 0x233A)))
            {
                U16 oldValidIndex=msAPI_CM_Get_AudioValidIndex();
                BYTE bISOLangIndex;
                msAPI_CM_Reset_AudioValidIndex();
                AudioNum = msAPI_CM_GetAudioStreamCount(bServiceType, wCurrentPosition);
                msAPI_CM_Update_AudioValidInfo(oldValidIndex);

                if((AudioNum <= 1))
                {
                    bNeedUpdate=FALSE;
                }
                if(bNeedUpdate && TRUE == msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &aAudioStreamInfo, g_u8AudLangSelected))
                {
                    wAudioPID = aAudioStreamInfo.wAudPID;
                    bISOLangIndex=aAudioStreamInfo.aISOLangInfo[0].bISOLangIndex;
                    msAPI_CM_ArrangeAudioStreamInfo(bServiceType,wCurrentPosition,_u16TempValidAudioIndex);
                    AudioNum = msAPI_CM_GetAudioStreamCount(bServiceType, wCurrentPosition);
                   if(AudioNum == 0)
                    {
                        msAPI_CM_Reset_AudioValidIndex();
                        AudioNum = msAPI_CM_GetAudioStreamCount(bServiceType, wCurrentPosition);
                    }
                    for(i=0;i<AudioNum;i++)
                    {
                        if(TRUE == msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &aAudioStreamInfo, i))
                        {
                            if(aAudioStreamInfo.wAudPID == wAudioPID && bISOLangIndex == aAudioStreamInfo.aISOLangInfo[0].bISOLangIndex)
                            {
                                break;
                            }
                        }
                    }
                    if(i >= AudioNum)
                    {
					#if (!BLOADER)
					#if (ENABLE_CI_PLUS)
						if(TRUE == MApp_CI_IsOpMode())
						{
							MApp_ChannelChange_SearchDefaultOPAudioLang();
						}
						else
						{
							MApp_ChannelChange_SearchDefaultAudioLang();
						}
					#else
						MApp_ChannelChange_SearchDefaultAudioLang();
					#endif
                        MApp_Audio_SetAudioLanguage(g_u8AudLangSelected);
					#endif
                    }
                    else
                    {
                        if(g_u8AudLangSelected != i)
                        {
                            AudioNum = msAPI_CM_GetAudioStreamCount(bServiceType, wCurrentPosition);
                            for(i=0;i<AudioNum;i++)
                            {
                                msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &aAudioStreamInfo, i);
                                if(aAudioStreamInfo.wAudPID == wAudioPID && bISOLangIndex == aAudioStreamInfo.aISOLangInfo[0].bISOLangIndex)
                                {
                                    g_u8AudLangSelected=i;
                                    break;
                                }
                            }
                        }
                    }
                }

            }
        }
    }
    return bSuccess;
}
#endif
#endif //ENABLE_SBTVD_BRAZIL_APP

#if(ENABLE_DTV)
void MApp_SI_Parse_PMT(U8 *pu8Section)
{
#if ENABLE_CI
    // Neotion NP4 transcode issue
    #define CIINFO_LENGTH 24
    U8 manufacturer[CIINFO_LENGTH];
    U8 product[CIINFO_LENGTH];
    U8 Info1[CIINFO_LENGTH];
#endif
    U8 u8Tag;


    U8 SubtitleCnt=0;
#if((!ENABLE_DVB_NOISDB)||(!ENABLE_SUBTITLE))
    UNUSED(SubtitleCnt);
#endif

    U16 u16DescriptorLength,u16TotalParseLength;
    U16       u16TotalDescriptorLength;
    U8                       *pu8LoopPosition;
    U8                       *pu8Descriptor;
    WORD wSubtitlePid = MSAPI_DMX_INVALID_PID;
    U16 u16CurService_ID;
    MEMBER_SERVICETYPE bServiceType;
    U16 u16DSMCC_PID = MSAPI_DMX_INVALID_PID;
    #if ENABLE_TTX
    U8 u8Length;
    U8* pu8Data;
    MS_TELETEXT_INFO stTtx;
    U8 u8EBUSubtitleNumber=0;
    #endif
    U16 u16Service_ID;
#if ENABLE_TTX
    BOOL bGotDefaultTTX=FALSE;
#endif
    u16Service_ID = TSGetU16(&pu8Section[3]);
    bServiceType = msAPI_CM_GetCurrentServiceType();
    u16CurService_ID=msAPI_CM_GetService_ID(bServiceType,msAPI_CM_GetCurrentPosition(bServiceType));

//printf("u16Service_ID %x %x %d\n",u16Service_ID,u16CurService_ID,MApp_Dmx_GetOADScanMode());
    if((u16Service_ID == u16CurService_ID) && !MApp_Dmx_GetOADScanMode())
    {
#if ENABLE_TTX
      gstTtxInfo.u8NumTTXType=0;
#endif

#if(ENABLE_SBTVD_SI)
    if(!msAPI_SRC_IS_SBTVD_InUse())
#endif
    {
#if(ENABLE_DVB_NOISDB)
    #if ENABLE_SUBTITLE
        MApp_Subtitle_Clear_ServiceData(FALSE);
    #endif
#endif
    }


    pu8LoopPosition = MApp_SI_FindLoopHead(pu8Section,EN_PMT,EN_SECONDLOOP);
    while(pu8LoopPosition != NULL)
    {
        u16TotalDescriptorLength = TSGetBitsFromU16(&pu8LoopPosition[3], 0, 0x0fff);
        // Go through the descriptors part.
        pu8Descriptor = pu8LoopPosition + 5;
        u16TotalParseLength = 0;

        switch(pu8LoopPosition[0]) //stream type
        {

            /*[5-3]private data ============================================*/
            case ST_PRIVATE_DATA:
            {
                // Go through the descriptors part.
                pu8Descriptor = pu8LoopPosition + 5;

                while(u16TotalParseLength<u16TotalDescriptorLength)
                {
                    u8Tag= pu8Descriptor[0];   //descripter Tag
                    switch(u8Tag)
                    {
#if ENABLE_TTX
                        case TAG_TtD:
                        {
                            U8* pu8Descp=pu8Descriptor;
                            #define TTXInfo stTtx.stTTXInfo[stTtx.u8NumTTXType]
                            memset(&stTtx,0,sizeof(MS_TELETEXT_INFO));
                            u8Length = 0;
                            pu8Data = &pu8Descp[2];
                            stTtx.u8NumTTXType = 0;
                            while(u8Length < pu8Descp[1])
                            {
                                //TTXInfo.eLangIdx = MApp_SI_GetISO639LangCode(pu8Data);
                                memcpy(TTXInfo.u8lanuage_code,pu8Data,3);
                                TTXInfo.u8TTXType = TSGetBitsFromU8(&pu8Data[3], 3, 0x1f);
                                TTXInfo.u8TTXMagNum = TSGetBitsFromU8(&pu8Data[3], 0, 0x07);
                                TTXInfo.u8TTXPageNum = pu8Data[4];
                                /*
                                printf("TTx Lan :%bu, Type %bu, MagNum %bu, PageNum %bu\n",
                                       TTXInfo.eLangIdx,TTXInfo.u8TTXType,TTXInfo.u8TTXMagNum,TTXInfo.u8TTXPageNum);
                                */
                                if ( ++stTtx.u8NumTTXType == MAX_TTXINFO_NUM )
                                {
                                    break;
                                 }
                                u8Length += 5;
                                pu8Data += 5;
                            }
                            #undef TTXInfo
                        }

                        {
                            if(u16CurService_ID ==  TSGetU16(&pu8Section[3]))
                            {
                                U8 u8NumOfTTX = 0;
                                U16 u16TTXPid = 0;

                                if(!bGotDefaultTTX || (gstTtxInfo.u16TTX_Pid == TSGetBitsFromU16(&pu8LoopPosition[1],0,0x1fff)))
                                {
                                    EN_LANGUAGE eMenuLanguage=MApp_GetMenuLanguage();
                                    BOOLEAN bGotInitPage=FALSE;
                                    BOOLEAN bSameLanguageTTX=FALSE;
                                    MS_TELETEXT_INFO TTXInfo;
                                    if(gstTtxInfo.u16TTX_Pid != TSGetBitsFromU16(&pu8LoopPosition[1],0,0x1fff))
                                    {
                                        U8 u8index;
                                        for(u8index=gstTtxInfo.u8NumTTXType;u8index<stTtx.u8NumTTXType;u8index++)
                                        {
                                            if((stTtx.stTTXInfo[u8index].u8TTXType == EN_TTX_INIT_TTX)
                                                && (eMenuLanguage == MApp_GetLanguageBySILanguage(msAPI_SI_GetLanguageByISO639LangCode(stTtx.stTTXInfo[u8index].u8lanuage_code))))
                                            {
                                                bSameLanguageTTX=TRUE;
                                            }
                                            //printf("ccccc %d %d type %d lang %.*s\n",eMenuLanguage,MApp_GetLanguageBySILanguage(MApp_SI_GetISO639LangCode(stTtx.stTTXInfo[u8index].u8lanuage_code)),
                                                //stTtx.stTTXInfo[u8index].u8TTXType,3,stTtx.stTTXInfo[u8index].u8lanuage_code);
                                        }
                                        gstTtxInfo.u8NumTTXType=0;
                                    }
                                    u8NumOfTTX = MIN(MAX_TTXINFO_NUM - gstTtxInfo.u8NumTTXType,stTtx.u8NumTTXType);
                                    memcpy(&gstTtxInfo.stTTXInfo[gstTtxInfo.u8NumTTXType],stTtx.stTTXInfo,sizeof(TELETEXT_Info)*u8NumOfTTX);
                                    // Could it possible have multiple PES private data contain ttx?
                                    // If so, to do.
                                    gstTtxInfo.u16TTX_Pid = MApp_TTX_GetDefaultTTX_PID();
                                    TTXInfo.u16TTX_Pid=gstTtxInfo.u16TTX_Pid;
                                    TTXInfo.u8NumTTXType=gstTtxInfo.u8NumTTXType;
                                    memcpy(TTXInfo.stTTXInfo,gstTtxInfo.stTTXInfo,sizeof(TELETEXT_Info)*MAX_TTXINFO_NUM);

                                    #if(ENABLE_SBTVD_SI)
                                    if(!msAPI_SRC_IS_SBTVD_InUse())
                                    #endif
                                    {
                                    #if((ENABLE_DVB_NOISDB)&&(ENABLE_SUBTITLE))
                                        u8EBUSubtitleNumber=MApp_TTX_Subtitle_ParsePMT(&TTXInfo, TSGetBitsFromU16(&pu8LoopPosition[1],0,0x1fff),u8NumOfTTX,&bGotInitPage);
                                    #else
                                        u8EBUSubtitleNumber=0;
                                    #endif
                                    }

                                    gstTtxInfo.u8NumTTXType += u8NumOfTTX;


                                    if((bGotInitPage) || (gstTtxInfo.u16TTX_Pid == MSAPI_DMX_INVALID_PID))
                                    {
                                        gstTtxInfo.u16TTX_Pid = TSGetBitsFromU16(&pu8LoopPosition[1],0,0x1fff);
                                    }
                                    if(bSameLanguageTTX)//got language match ttx
                                    {
                                        bGotDefaultTTX=TRUE;
                                    }

#if ENABLE_TTX
                                    msAPI_DMX_Pid(*MApp_Dmx_GetFid(EN_TTX_FID),&u16TTXPid,FALSE);
                                    // In UK DVB, there's no TTX, only MHEG5
                                    if(!msAPI_TTX_Get_VBIAcquireEnableStatus() || (msAPI_TTX_Get_VBIAcquireEnableStatus() && u16TTXPid != gstTtxInfo.u16TTX_Pid ))
                                    {
                                        MApp_TTX_TeletextCommand(TTX_TV);   // exit TTX
                                        MApp_TTX_SetDefaultTTX_PID(gstTtxInfo.u16TTX_Pid);
                                        MApp_TTX_SetDTV_TTXSystem(gstTtxInfo.u16TTX_Pid, FALSE);
                                    }
                                    MApp_TTX_NotifyPMTTTXInfoChanged();
#else
                                UNUSED(u16TTXPid);
#endif
                                }
                                else // Monitor part
                                {
                                    BOOLEAN bGotInitPage=FALSE;
                                    MS_TELETEXT_INFO TTXInfo;
                                    TTXInfo.u8NumTTXType=0;
                                    u8NumOfTTX = MIN(MAX_TTXINFO_NUM - TTXInfo.u8NumTTXType,stTtx.u8NumTTXType);
                                    memcpy(&TTXInfo.stTTXInfo[TTXInfo.u8NumTTXType],stTtx.stTTXInfo,sizeof(TELETEXT_Info)*u8NumOfTTX);

                                    #if(ENABLE_SBTVD_SI)
                                    if(!msAPI_SRC_IS_SBTVD_InUse())
                                    #endif
                                    {
                                    #if((ENABLE_DVB_NOISDB)&&(ENABLE_SUBTITLE))
                                        u8EBUSubtitleNumber=MApp_TTX_Subtitle_ParsePMT(&TTXInfo, TSGetBitsFromU16(&pu8LoopPosition[1],0,0x1fff),u8NumOfTTX,&bGotInitPage);
                                    #else
                                        u8EBUSubtitleNumber=0;
                                    #endif
                                    }
                                }
                            }
                        }
                        break;
#endif
                        case TAG_SbD:
                        {
                            //printf("Subtitle pid 0x%x:0x%x\n",pSIInfo->stPmtMonInfo.wSubtitlePid,TSGetBitsFromU16(&pu8LoopPosition[1],0,0x1fff));
                            if(wSubtitlePid != TSGetBitsFromU16(&pu8LoopPosition[1],0,0x1fff))
                            {
                                #if(ENABLE_SBTVD_SI)
                                if(!msAPI_SRC_IS_SBTVD_InUse())
                                #endif
                                {
                                    #if((ENABLE_DVB_NOISDB)&&(ENABLE_SUBTITLE))
                                    pu8SubtitleDescriptor = pu8Descriptor;//ustDesc.stSubTitle.pu8SubTitleData;
                                    pu8ElementaryPID = pu8LoopPosition +1;
                                    //add by jason peng
                                    SubtitleCnt++;
                                    SubtitleSamePIDCnt=SubtitleCnt;
                                    MApp_Subtitle_ParsePMT();
                                    #endif
                                }

                                wSubtitlePid = TSGetBitsFromU16(&pu8LoopPosition[1],0,0x1fff);
                            }
                        }
                        break;
                        default: break;
                    }
                    /* move to next descriptor */
                    u16DescriptorLength = pu8Descriptor[1] + 2;
                    u16TotalParseLength += u16DescriptorLength;
                    pu8Descriptor += u16DescriptorLength;
                }
                break;
            }
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
                            #define DATA_BC_ID_SSU          0x000A // DVB-SSU
                            #define DATA_BC_ID_UK_EC        0x0111 // UK Engineering Channel
                            if(((pu8Descriptor[1] - 2) >0) && TSGetU16(&pu8Descriptor[2]) == DATA_BC_ID_SSU)
                            {
                                WORD wONId;

                                wONId = msAPI_CM_GetON_ID(msAPI_CM_GetCurrentServiceType(),msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()));
                                // Send OAD info & Update Status to OAD module.
                                if((IS_NORDIC_COUNTRY(OSD_COUNTRY_SETTING)== FALSE)
                                    ||((wONId == 0x2242 && OSD_COUNTRY_SETTING==OSD_COUNTRY_NORWAY)
                                        ||(wONId == 0x20D0 && OSD_COUNTRY_SETTING==OSD_COUNTRY_DENMARK)
                                        ||(wONId == 0x22F1 && OSD_COUNTRY_SETTING==OSD_COUNTRY_SWEDEN)
                                        ||(wONId == 0x20F6 && OSD_COUNTRY_SETTING==OSD_COUNTRY_FINLAND)
                                        ||(wONId == 0x2174 && OSD_COUNTRY_SETTING==OSD_COUNTRY_IRELAND)))
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


#if(ENABLE_SBTVD_SI)
    if(!msAPI_SRC_IS_SBTVD_InUse())
#endif
    {
    #if((ENABLE_DVB_NOISDB)&&(ENABLE_SUBTITLE))
        if (!UI_Hotkey_Subtitle)
        {
#if ENABLE_COUNTRY_SINGAPORE
            if(u8SubtitleMenuNum != 0)
                stGenSetting.g_SysSetting.fEnableSubTitle = TRUE;
#endif
            MApp_TV_SelectSubtileLang(); // remark it to avoid become auto select after version change
        }
    #endif
    }


#if ENABLE_TTX
    if(u8EBUSubtitleNumber == 0 && MApp_TTX_GetControlMode()==TTX_MODE_SUBTITLE)
    {
        MApp_TTX_TeletextCommand(TTX_TV);
    }
#endif
#if ENABLE_CI
    // Neotion NP4 transcode issue
    // Don't send PMT if it is neotion and content is clear.
    {
        U8 u8ManufacturerLen = CIINFO_LENGTH;
        U8 u8ProductLen = CIINFO_LENGTH;
        U8 u8Info1Len = CIINFO_LENGTH;

        u32ChkTry2ChgMpeg2Time = msAPI_Timer_GetTime0();
        msAPI_CI_GetCIS( manufacturer, &u8ManufacturerLen, product, &u8ProductLen, Info1, &u8Info1Len );
        if(msAPI_CI_GetCardType()               == EN_SMARTCARD_TYPE_NEOTNT &&
           strcmp((char*)manufacturer,"NEOTION")== 0                        &&
           strcmp((char*)product,"NP4")         == 0)
        {
            if(MApp_SI_CheckCurProgScramble() == TRUE)
            {
                //printf("Send PMT\n");
            msAPI_CI_NotifyCurrentPMTUpdate(pu8Section,(3 + TSGetBitsFromU16(&pu8Section[1], 0, 0x0FFF)));
            }
        }
        else
        {
            msAPI_CI_NotifyCurrentPMTUpdate(pu8Section,(3 + TSGetBitsFromU16(&pu8Section[1], 0, 0x0FFF)));
        }
    }
#endif
    }
#if ENABLE_OAD
    else
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

									if( (IS_NORDIC_COUNTRY(OSD_COUNTRY_SETTING)== FALSE)
                                      ||( (wONId == 0x2242 && OSD_COUNTRY_SETTING==OSD_COUNTRY_NORWAY)
                                        ||(wONId == 0x20D0 && OSD_COUNTRY_SETTING==OSD_COUNTRY_DENMARK)
                                        ||(wONId == 0x22F1 && OSD_COUNTRY_SETTING==OSD_COUNTRY_SWEDEN)
                                        ||(wONId == 0x20F6 && OSD_COUNTRY_SETTING==OSD_COUNTRY_FINLAND)
                                        ||(wONId == 0x2174 && OSD_COUNTRY_SETTING==OSD_COUNTRY_IRELAND)
                                        )
									  ||(wONId == 0xFFFF)

                                    #if 0 // Sync code from CL1472861(Mantis-1014137)
									  ||((ouiData==CUSTOMER_OUI) || (ouiData==DVB_OUI && updateType==SSU_UPDATETYPE_STANDARD))
									#endif
                                      )
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
		if(TRUE == MApp_Dmx_Get_IsAllPmtReady())
		{
			MApp_OAD_Set_PMT_Ready(TRUE);
			MApp_Dmx_ResetAllPmtReady();
		}
    }
#endif
#if ENABLE_CI
#if (ENABLE_CI_PLUS)
    if ((MApp_Dmx_GetMonitorStatus(EN_MONITOR_CI_TUNE) && (u16Service_ID == MApp_Dmx_GetCITuneServiceId()))&& (!MApp_Dmx_GetOADScanMode()))
    {
        msAPI_CI_NotifyCurrentPMTUpdate(pu8Section, (3 + TSGetBitsFromU16(&pu8Section[1], 0, 0x0FFF)));
    }
    else if (((FALSE == MApp_Dmx_GetMonitorStatus(EN_MONITOR_CI_TUNE)) && (u16Service_ID != u16CurService_ID)) && (!MApp_Dmx_GetOADScanMode()))
    {
        msAPI_CI_NotifyOtherPMTUpdate(pu8Section, (3 + TSGetBitsFromU16(&pu8Section[1], 0, 0x0FFF)));
    }
#else
    if ((u16Service_ID != u16CurService_ID)&& (!MApp_Dmx_GetOADScanMode()))
    {
        msAPI_CI_NotifyOtherPMTUpdate(pu8Section, (3 + TSGetBitsFromU16(&pu8Section[1], 0, 0x0FFF)));
    }
#endif
#endif
}

void MApp_SI_FileIn_Parse_PMT(U8 *pu8Section)
{
    U8 u8Tag;

    U8 SubtitleCnt=0;

//#if((ENABLE_DVB_NOISDB)&&(ENABLE_SUBTITLE))


#if((!ENABLE_DVB_NOISDB)||(!ENABLE_SUBTITLE))
    UNUSED(SubtitleCnt);
#endif

    U16 u16DescriptorLength,u16TotalParseLength;
    U16       u16TotalDescriptorLength;
    U8                       *pu8LoopPosition;
    U8                       *pu8Descriptor;
    WORD wSubtitlePid = MSAPI_DMX_INVALID_PID;
    U16 u16FileInService_ID;
    //MEMBER_SERVICETYPE bServiceType;
    //U16 u16DSMCC_PID = MSAPI_DMX_INVALID_PID;
    #if ENABLE_TTX
    U8 u8Length;
    U8* pu8Data;
    MS_TELETEXT_INFO stTtx;
    U8 u8EBUSubtitleNumber=0;
    #endif
    U16 u16Service_ID;
    u16Service_ID = TSGetU16(&pu8Section[3]);
    u16FileInService_ID = MApp_SI_GetFileInServiceID();

//printf("u16Service_ID %x %x %d\n",u16Service_ID,u16CurService_ID,MApp_Dmx_GetOADScanMode());
#if (ENABLE_CI_PLUS)
	if((INVALID_PID != MApp_SI_GetFileIn_PMT_PID()) || (u16Service_ID == u16FileInService_ID))
#else
	if((u16Service_ID == u16FileInService_ID))
#endif
    {
#if ENABLE_TTX
      gstTtxInfo.u8NumTTXType=0;
#endif

#if(ENABLE_SBTVD_SI)
    if(!msAPI_SRC_IS_SBTVD_InUse())
#endif
    {
#if(ENABLE_DVB_NOISDB)
    #if ENABLE_SUBTITLE
        MApp_Subtitle_Clear_ServiceData(FALSE);
    #endif
#endif
    }

    pu8LoopPosition = MApp_SI_FindLoopHead(pu8Section,EN_PMT,EN_SECONDLOOP);
    while(pu8LoopPosition != NULL)
    {
        u16TotalDescriptorLength = TSGetBitsFromU16(&pu8LoopPosition[3], 0, 0x0fff);
        // Go through the descriptors part.
        pu8Descriptor = pu8LoopPosition + 5;
        u16TotalParseLength = 0;

        switch(pu8LoopPosition[0]) //stream type
        {

            /*[5-3]private data ============================================*/
            case ST_PRIVATE_DATA:
            {
                // Go through the descriptors part.
                pu8Descriptor = pu8LoopPosition + 5;

                while(u16TotalParseLength<u16TotalDescriptorLength)
                {
                    u8Tag= pu8Descriptor[0];   //descripter Tag
                    switch(u8Tag)
                    {
#if ENABLE_TTX
                        case TAG_TtD:
                        {
                            U8* pu8Descp=pu8Descriptor;
                            #define TTXInfo stTtx.stTTXInfo[stTtx.u8NumTTXType]
                            memset(&stTtx,0,sizeof(MS_TELETEXT_INFO));
                            u8Length = 0;
                            pu8Data = &pu8Descp[2];
                            stTtx.u8NumTTXType = 0;
                            while(u8Length < pu8Descp[1])
                            {
                                //TTXInfo.eLangIdx = MApp_SI_GetISO639LangCode(pu8Data);
                                memcpy(TTXInfo.u8lanuage_code,pu8Data,3);
                                TTXInfo.u8TTXType = TSGetBitsFromU8(&pu8Data[3], 3, 0x1f);
                                TTXInfo.u8TTXMagNum = TSGetBitsFromU8(&pu8Data[3], 0, 0x07);
                                TTXInfo.u8TTXPageNum = pu8Data[4];
                                /*
                                printf("TTx Lan :%bu, Type %bu, MagNum %bu, PageNum %bu\n",
                                       TTXInfo.eLangIdx,TTXInfo.u8TTXType,TTXInfo.u8TTXMagNum,TTXInfo.u8TTXPageNum);
                                */
                                if ( ++stTtx.u8NumTTXType == MAX_TTXINFO_NUM )
                                {
                                    break;
                                 }
                                u8Length += 5;
                                pu8Data += 5;
                            }
                            #undef TTXInfo
                        }

                        {
                            if(u16FileInService_ID ==  TSGetU16(&pu8Section[3]))
                            {
                                U8 u8NumOfTTX = 0;
                                U16 u16TTXPid = 0;

                                if(1/*!bTTXExist*/)
                                {
                                    BOOLEAN bGotInitPage=FALSE;;
                                    MS_TELETEXT_INFO TTXInfo;
                                    u8NumOfTTX = MIN(MAX_TTXINFO_NUM - gstTtxInfo.u8NumTTXType,stTtx.u8NumTTXType);
                                    memcpy(&gstTtxInfo.stTTXInfo[gstTtxInfo.u8NumTTXType],stTtx.stTTXInfo,sizeof(TELETEXT_Info)*u8NumOfTTX);
                                    // Could it possible have multiple PES private data contain ttx?
                                    // If so, to do.
                                    gstTtxInfo.u16TTX_Pid = MApp_TTX_GetDefaultTTX_PID();
                                    TTXInfo.u16TTX_Pid=gstTtxInfo.u16TTX_Pid;
                                    TTXInfo.u8NumTTXType=gstTtxInfo.u8NumTTXType;
                                    memcpy(TTXInfo.stTTXInfo,gstTtxInfo.stTTXInfo,sizeof(TELETEXT_Info)*MAX_TTXINFO_NUM);
                                    #if(ENABLE_SBTVD_SI)
                                    if(!msAPI_SRC_IS_SBTVD_InUse())
                                    #endif
                                    {
                                    #if((ENABLE_DVB_NOISDB)&&(ENABLE_SUBTITLE))
                                        u8EBUSubtitleNumber=MApp_TTX_Subtitle_ParsePMT(&TTXInfo, TSGetBitsFromU16(&pu8LoopPosition[1],0,0x1fff),u8NumOfTTX,&bGotInitPage);
                                    #else
                                        u8EBUSubtitleNumber=0;
                                    #endif
                                    }
                                    gstTtxInfo.u8NumTTXType += u8NumOfTTX;

                                    if((bGotInitPage) || (gstTtxInfo.u16TTX_Pid == MSAPI_DMX_INVALID_PID))
                                    {
                                        gstTtxInfo.u16TTX_Pid = TSGetBitsFromU16(&pu8LoopPosition[1],0,0x1fff);
                                    }
#if ENABLE_TTX
                                    msAPI_DMX_Pid(*MApp_Dmx_GetFid(EN_TTX_FID),&u16TTXPid,FALSE);
                                    // In UK DVB, there's no TTX, only MHEG5
                                    if(!msAPI_TTX_Get_VBIAcquireEnableStatus() || (msAPI_TTX_Get_VBIAcquireEnableStatus() && u16TTXPid != gstTtxInfo.u16TTX_Pid ))
                                    {
                                        MApp_TTX_TeletextCommand(TTX_TV);   // exit TTX
                                        MApp_TTX_SetDefaultTTX_PID(gstTtxInfo.u16TTX_Pid);
                                        MApp_TTX_SetDTV_TTXSystem(gstTtxInfo.u16TTX_Pid, FALSE);
                                    }
                                    MApp_TTX_NotifyPMTTTXInfoChanged();
#else
                                UNUSED(u16TTXPid);
#endif
                                }
                                else // Monitor part
                                {
                                    // To do.
                                }
                            }
                        }
                        break;
#endif
                        case TAG_SbD:
                        {
                            printf("##### Subtitle Descriptor #####\n");
                            //printf("Subtitle pid 0x%x:0x%x\n",pSIInfo->stPmtMonInfo.wSubtitlePid,TSGetBitsFromU16(&pu8LoopPosition[1],0,0x1fff));
                            if(wSubtitlePid != TSGetBitsFromU16(&pu8LoopPosition[1],0,0x1fff))
                            {
                                #if(ENABLE_SBTVD_SI)
                                if(!msAPI_SRC_IS_SBTVD_InUse())
                                #endif
                                {
                                    #if((ENABLE_DVB_NOISDB)&&(ENABLE_SUBTITLE))
                                    pu8SubtitleDescriptor = pu8Descriptor;//ustDesc.stSubTitle.pu8SubTitleData;
                                    pu8ElementaryPID = pu8LoopPosition +1;
                                    //add by jason peng
                                    SubtitleCnt++;
                                    SubtitleSamePIDCnt=SubtitleCnt;
                                    MApp_Subtitle_ParsePMT();
                                    #endif
                                }
                                wSubtitlePid = TSGetBitsFromU16(&pu8LoopPosition[1],0,0x1fff);
                            }
                        }
                        break;
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

#if(ENABLE_SBTVD_SI)
    if(!msAPI_SRC_IS_SBTVD_InUse())
#endif
    {
    #if((ENABLE_DVB_NOISDB)&&(ENABLE_SUBTITLE))
        if (!UI_Hotkey_Subtitle)
        {
            printf(" >>>>> MApp_TV_SelectSubtileLang\n");
            MApp_TV_SelectSubtileLang(); // remark it to avoid become auto select after version change
        }
    #endif
    }


#if ENABLE_TTX
    if(u8EBUSubtitleNumber == 0 && MApp_TTX_GetControlMode()==TTX_MODE_SUBTITLE)
    {
        MApp_TTX_TeletextCommand(TTX_TV);
    }
#endif
    }

 }
void MApp_SI_Parse_NIT(U8 *pu8Section)
{
    U16 u16DescriptorLength;
    U16 u16TotalParseLength;
    U16       u16TotalDescriptorLength;
    U8 u8Tag;
    U8                       *pu8Descriptor;
#if ENABLE_OAD
	U8 u8Version;
	WORD  wCurNITVersion;

	//WORD	wTSId,wONId,wServiceId;
	u8Version = TSGetBitsFromU8(&pu8Section[5], 1, 0x1f);
	wCurNITVersion = msAPI_CM_GetPSISIVersion(msAPI_CM_GetCurrentServiceType(),msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()),E_VERSION_NIT);
	if(wCurNITVersion != u8Version)
	{
		wCurNITVersion = u8Version;
	}
	else
	{
	}
	//printf("bSkipSignalOTA  %bu\n",bSkipSignalOTA);
	MApp_OAD_Set_NIT_Ready(FALSE);
#endif
    pu8Descriptor = MApp_SI_FindLoopHead(pu8Section,EN_NIT,EN_FIRSTLOOP);
    if(pu8Descriptor != NULL)
    {
        /* get total descriptor length */
        u16TotalDescriptorLength = TSGetBitsFromU16(&pu8Section[8], 0, 0x0FFF);
        u16TotalParseLength = 0;
        while(u16TotalParseLength<u16TotalDescriptorLength)
        {
            u8Tag= pu8Descriptor[0];   //descripter Tag
            switch( u8Tag)
            {
                case TAG_LD:
                {
                    if((pu8Descriptor[1] - 7) > 0)
                    {
                        #if ENABLE_OAD
                        WORD  wTSId,wONId,wServiceId;

                        if(pu8Descriptor[8] == 0x09)
                        {
                            wTSId = TSGetU16(&pu8Descriptor[2]);
                            wONId = TSGetU16(&pu8Descriptor[4]);
                            wServiceId = TSGetU16(&pu8Descriptor[6]);
                            if(((IS_NORDIC_COUNTRY(OSD_COUNTRY_SETTING)== FALSE)
                                ||((wONId == 0x2242 && OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY)
                                    ||(wONId == 0x20D0 && OSD_COUNTRY_SETTING == OSD_COUNTRY_DENMARK)
                                    ||(wONId == 0x22F1 && OSD_COUNTRY_SETTING == OSD_COUNTRY_SWEDEN)
                                    ||(wONId == 0x20F6 && OSD_COUNTRY_SETTING == OSD_COUNTRY_FINLAND)
                                    ||(wONId == 0x2174 && OSD_COUNTRY_SETTING == OSD_COUNTRY_IRELAND))))
                            {
                                //bNITSignalSSU = FALSE;
                            MApp_OAD_SetNitSignal(wTSId, wONId, wServiceId, &pu8Descriptor[9] );
                        }
                        }
                        #endif
                    }
                }
                break;

                default: break;
            }
            /* move to next descriptor */
            u16DescriptorLength = pu8Descriptor[1] + 2;
            u16TotalParseLength += u16DescriptorLength;
            pu8Descriptor += u16DescriptorLength;
        }
    }
#if ENABLE_OAD
	MApp_OAD_Set_NIT_Ready(TRUE);
#endif
}

void MApp_SI_Parse_SDT(U8 *pu8Section)
{
    U16 u16TransportStreamID,u16ServiceID,u16DescriptorLength,u16TotalParseLength;
    U8 u8Tag;
    MEMBER_SERVICETYPE bServiceType;
    U16 u16CurService_ID;
    U16       u16TotalDescriptorLength;
    U8                       *pu8LoopPosition;
    U8                       *pu8Descriptor;
#if ENABLE_CI_PLUS
    BOOLEAN bCI_Protection_Descriptor = FALSE;
#endif

    bServiceType = msAPI_CM_GetCurrentServiceType();
    u16CurService_ID = msAPI_CM_GetService_ID(bServiceType,msAPI_CM_GetCurrentPosition(bServiceType));
    /*[2]goto first loop position ==========================================*/
    u16TransportStreamID = TSGetU16(&pu8Section[3]);
    u16ServiceID = 0;
    pu8LoopPosition = MApp_SI_FindLoopHead(pu8Section,EN_SDT,EN_FIRSTLOOP);
#if ENABLE_CI_PLUS
    if(MApp_Dmx_GetMonitorStatus(EN_MONITOR_CI_TUNE))
    {
        //printf("msAPI_CI_NotifyCurrentServiceInfo :> u16TransportStreamID 0x%x, 0x%x\n",u16TransportStreamID,MApp_Dmx_GetCITuneServiceId());
        msAPI_CI_NotifyCurrentServiceInfo(u16TransportStreamID, MApp_Dmx_GetCITuneServiceId());
    }
#endif

    while(pu8LoopPosition != NULL)
    {
#if ENABLE_CI_PLUS
        bCI_Protection_Descriptor = FALSE;
#endif
        /* service id */
        u16ServiceID = TSGetU16(&pu8LoopPosition[0]);
        /* skip the Network PID (service id = 0) */
        /* total descriptor length */
        u16TotalDescriptorLength = ((pu8LoopPosition[3] & 0x0f) << 8) | pu8LoopPosition[4];

#if 1
       if(u16ServiceID && ( (u16ServiceID == u16CurService_ID)||(msAPI_Demod_Get_CurTSPathCase()==E_DEMOD_TSP_PATH_CASE_NORMAL))  )
#else
    #if (TS_SERIAL_OUTPUT_IF_CI_REMOVED)
        if(u16ServiceID && ((u16ServiceID == u16CurService_ID)||(!msAPI_Tuner_IsParallelMode())))
    #else
        if(u16ServiceID && ((u16ServiceID == u16CurService_ID)|| msAPI_Tuner_IsByPassMode() ))
    #endif
#endif
        {
            /* move to descriptor position */
            pu8Descriptor = pu8LoopPosition + 5;
            u16TotalParseLength=0;
            while(u16TotalParseLength<u16TotalDescriptorLength)
            {
                u8Tag= pu8Descriptor[0];   //descripter Tag
                switch(u8Tag)
                {
#if ENABLE_CI
                    case TAG_CIPD:   //CI Protection Descriptor
                        #if ENABLE_CI_PLUS
                        bCI_Protection_Descriptor = TRUE;
                        msAPI_CI_HSS_Set(pu8Descriptor, pu8Descriptor[1] + 2,u16TransportStreamID,u16ServiceID);
                        #endif
                        break;
#endif
                    default: break;
                }
                /* move to next descriptor */
                u16DescriptorLength = pu8Descriptor[1] + 2;
                u16TotalParseLength += u16DescriptorLength;
                pu8Descriptor += u16DescriptorLength;
            }
#if ENABLE_CI_PLUS
            if (FALSE == bCI_Protection_Descriptor)
                msAPI_CI_HSS_Set(NULL, 0,u16TransportStreamID,u16ServiceID);
#endif

        }
        pu8LoopPosition = MApp_SI_FindNextLoop(pu8Section, pu8LoopPosition, u16TotalDescriptorLength, EN_SDT);
    }

#if ENABLE_CI_PLUS
    if (msAPI_CI_CardDetect())
    {
        msAPI_CI_HSS_Check();
    }
#endif
}
#endif
#undef  MAPP_SI_PARSE_C

