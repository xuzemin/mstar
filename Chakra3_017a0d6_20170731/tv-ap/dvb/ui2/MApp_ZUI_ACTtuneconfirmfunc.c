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

#define MAPP_ZUI_ACTTUNECONFIRMFUNC_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "ZUI_tables_h.inl"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_ACTmainpage.h"
#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_APIdraw.h"
#include "MApp_ZUI_ACTglobal.h"
#include "OSDcp_String_EnumIndex.h"
#include "ZUI_exefunc.h"

#include "MApp_GlobalFunction.h"
#include "MApp_UiMenuDef.h"
#include "MApp_RestoreToDefault.h"
#include "MApp_ChannelChange.h"
#if ENABLE_DVBC
#include "MApp_Scan.h"
#endif
#if 0//ENABLE_T_C_COMBO
#include "MApp_ZUI_ACTcadtvmanualtuning.h"
#endif
////////////////////////////////////////////////////
//NOTE: when we are selecting country, don't modify the real one!!
static EN_OSD_COUNTRY_SETTING _eTuningCountry;
#if(DVBC_CERTIFICATION_AUTOSCAN_ENABLE)
static EN_OSD_CERTIFICATION_SETTING _eTuningCertification;
static EN_OSD_UNITYMEDIA_COUNTRY_SETTING _eTuningUnityMediaCountry;
static EN_OSD_ZIGGO_COUNTRY_SETTING _eTuningZiggoCountry;
#endif
extern EN_OSD_TUNE_TYPE_SETTING eTuneType;

#if ENABLE_AUTOTEST
extern BOOLEAN g_bAutobuildDebug;
extern U16 tempcheck2;
// 7
U16 Country =0;

#endif

BOOLEAN bOriginalSrcIsDvbc = FALSE; //original source is DVBC when do auto scan(ATV+DTV)

// the country list for installation and auto tuning
ST_OSD_SELECTION_STRING_MAPPING_LIST _ZUI_TBLSEG stAutoTuningCountryList[] =
{
#if ENABLE_EWS
#if(ENABLE_SOUTHEAST_ASIA_CERTIFICATION)
    {OSD_COUNTRY_INDONESIA, en_str_Indonesia},
#endif
    {OSD_COUNTRY_MALAYSIA, en_str_Malaysia},
#endif
    {OSD_COUNTRY_AUSTRALIA, en_str_Australia},
    {OSD_COUNTRY_AUSTRIA, en_str_Austria},
    {OSD_COUNTRY_BELGIUM, en_str_Belgium},
    {OSD_COUNTRY_BULGARIA, en_str_Bulgaria},
    {OSD_COUNTRY_CROATIA, en_str_Croatia},
    {OSD_COUNTRY_CZECH, en_str_Czech},
    {OSD_COUNTRY_DENMARK, en_str_Denmark},
    {OSD_COUNTRY_FINLAND, en_str_Finland},
    {OSD_COUNTRY_FRANCE, en_str_France},
    {OSD_COUNTRY_GERMANY, en_str_Germany},
    {OSD_COUNTRY_GREECE, en_str_Greece},
    {OSD_COUNTRY_HUNGARY, en_str_Hungary},
    {OSD_COUNTRY_ITALY, en_str_Italy},
    {OSD_COUNTRY_IRELAND, en_str_Ireland},
    {OSD_COUNTRY_LUXEMBOURG, en_str_Luxembourg},
    {OSD_COUNTRY_NETHERLANDS, en_str_Netherlands},
    {OSD_COUNTRY_NORWAY, en_str_Norway},
    {OSD_COUNTRY_POLAND, en_str_Poland},
    {OSD_COUNTRY_PORTUGAL, en_str_Portugal},
    {OSD_COUNTRY_ROMANIA, en_str_Rumania},
    {OSD_COUNTRY_RUSSIA, en_str_Russian},
    {OSD_COUNTRY_SERBIA, en_str_Serbia},
    {OSD_COUNTRY_SLOVENIA, en_str_Slovenia},
    {OSD_COUNTRY_SPAIN, en_str_Spain},
    {OSD_COUNTRY_SWEDEN, en_str_Sweden},
    {OSD_COUNTRY_SWITZERLAND, en_str_Switzerland},
    {OSD_COUNTRY_UK, en_str_UK},
    {OSD_COUNTRY_UNITED_ARAB_EMIRATES, en_str_United_Arab_Emirates},
    {OSD_COUNTRY_NEWZEALAND, en_str_NewZealand},
    {OSD_COUNTRY_CHINA, en_str_China},
    {OSD_COUNTRY_ESTONIA, en_str_Estonia},
    {OSD_COUNTRY_TURKEY, en_str_Turkey},
    {OSD_COUNTRY_MOROCCO, en_str_Morocco},
    {OSD_COUNTRY_TUNIS, en_str_Tunis},
    {OSD_COUNTRY_ALGERIA, en_str_Algeria},
    {OSD_COUNTRY_EGYPT, en_str_Egypt},
    {OSD_COUNTRY_SOUTH_AFRICA, en_str_South_Africa},
    {OSD_COUNTRY_ISRAEL, en_str_Israel},
    {OSD_COUNTRY_IRAN, en_str_Iran},
    {OSD_COUNTRY_SLOVAKIA, en_str_Slovak},
    {OSD_COUNTRY_KUWAIT, en_str_Kuwait},
    {OSD_COUNTRY_OMAN, en_str_Oman},
    {OSD_COUNTRY_QATAR, en_str_Qatar},
    {OSD_COUNTRY_SAUDI_ARABIA, en_str_Saudi_Arabia},
    {OSD_COUNTRY_BAHRAIN, en_str_Bahrain},
    {OSD_COUNTRY_THAILAND, en_str_Thailand},
#if(ENABLE_COUNTRY_SINGAPORE)
    {OSD_COUNTRY_SINGAPORE, en_str_Singapore},
#endif

#if(ENABLE_COUNTRY_VIETNAM)
    {OSD_COUNTRY_VIETNAM, en_str_Vietnam},
#endif

#if(ENABLE_COUNTRY_KENYA)
    {OSD_COUNTRY_KENYA, en_str_Kenya},
#endif

#if(ENABLE_COUNTRY_MYANMAR)
    {OSD_COUNTRY_MYANMAR, en_str_Myanmar},
#endif

#if(ENABLE_COUNTRY_GHANA)
    {OSD_COUNTRY_GHANA, en_str_Ghana},
#endif

#if (ENABLE_DVB_TAIWAN_APP)
    {OSD_COUNTRY_TAIWAN, en_str_Taiwan},
#endif

#if 0//((ENABLE_SBTVD_DTV_SYSTEM)||(ENABLE_SBTVD_ATV_SYSTEM))
    {OSD_COUNTRY_BRAZIL, en_str_Brazil},
#endif

};


#ifdef MENU_LANGUAGE_LITE // for Melody UI_SKIN_960X540X565

U16 _ZUI_TBLSEG stOsdLanguageList[] =
{
#if (ENABLE_DTMB_CHINA_APP          \
    || ENABLE_ATV_CHINA_APP         \
    || ENABLE_DVBC_PLUS_DTMB_CHINA_APP  \
    ||CHINESE_SIMP_FONT_ENABLE      \
    ||ENABLE_DVB_TAIWAN_APP         \
    ||CHINESE_BIG5_FONT_ENABLE)
	LANGUAGE_ENGLISH,
    LANGUAGE_CHINESE_TRAD,
	LANGUAGE_CHINESE,
#else
    LANGUAGE_ENGLISH,
#endif  //ENABLE_DTMB_CHINA_APP
};

U16 _ZUI_TBLSEG stOsdAudLangList[] =
{
	LANGUAGE_ENGLISH,
    LANGUAGE_CHINESE_TRAD,
	LANGUAGE_CHINESE,

	LANGUAGE_CZECH,
	LANGUAGE_DANISH,
	LANGUAGE_GERMAN,
	LANGUAGE_SPANISH,
	LANGUAGE_GREEK,
    LANGUAGE_FRENCH,
    LANGUAGE_CROATIAN,
    LANGUAGE_ITALIAN,
    LANGUAGE_HUNGARIAN,
    LANGUAGE_DUTCH,
    LANGUAGE_NORWEGIAN,
    LANGUAGE_POLISH,
    LANGUAGE_PORTUGUESE,
#if(ENABLE_UI_LANGUAGE_RUSSIAN)
    LANGUAGE_RUSSIAN,
#endif//ENABLE_UI_LANGUAGE_RUSSIAN
    LANGUAGE_ROMANIAN,
    LANGUAGE_SLOVENIAN,
    LANGUAGE_SERBIAN,
    LANGUAGE_FINNISH,
    LANGUAGE_SWEDISH,
    LANGUAGE_BULGARIAN,
    LANGUAGE_SLOVAK,
    LANGUAGE_GAELIC,
    LANGUAGE_AKAN,
    LANGUAGE_EWE,
    LANGUAGE_TWI,
    LANGUAGE_NZEMA,
    LANGUAGE_HAUSA,
    LANGUAGE_KASEM,
    LANGUAGE_WELSH,
    LANGUAGE_IRISH,
};

U16 _ZUI_TBLSEG stNzOsdAudLangList[] =
{
	LANGUAGE_ENGLISH,
    LANGUAGE_CHINESE_TRAD,
	LANGUAGE_CHINESE,

	LANGUAGE_CZECH,
	LANGUAGE_DANISH,
	LANGUAGE_GERMAN,
	LANGUAGE_SPANISH,
	LANGUAGE_GREEK,
    LANGUAGE_FRENCH,
    LANGUAGE_CROATIAN,
    LANGUAGE_ITALIAN,
    LANGUAGE_HUNGARIAN,
    LANGUAGE_DUTCH,
    LANGUAGE_NORWEGIAN,
    LANGUAGE_POLISH,
    LANGUAGE_PORTUGUESE,
#if(ENABLE_UI_LANGUAGE_RUSSIAN)
    LANGUAGE_RUSSIAN,
#endif//ENABLE_UI_LANGUAGE_RUSSIAN
    LANGUAGE_ROMANIAN,
    LANGUAGE_SLOVENIAN,
    LANGUAGE_SERBIAN,
    LANGUAGE_FINNISH,
    LANGUAGE_SWEDISH,
    LANGUAGE_BULGARIAN,
    LANGUAGE_SLOVAK,
    LANGUAGE_GAELIC,
    LANGUAGE_AKAN,
    LANGUAGE_EWE,
    LANGUAGE_TWI,
    LANGUAGE_NZEMA,
    LANGUAGE_HAUSA,
    LANGUAGE_KASEM,
    LANGUAGE_WELSH,
    LANGUAGE_IRISH,
    LANGUAGE_KOREAN,
    LANGUAGE_JAPAN,
#if(ENABLE_UYGHUR_OSD)
    LANGUAGE_UYGHUR,
#endif
#if (ENABLE_TTF_FONT)

  #if(ENABLE_INDIA_OSD)
    LANGUAGE_HINDI,
  #endif

  #if(ENABLE_KHMER_OSD)
    LANGUAGE_KHMER,
  #endif

  #if(ENABLE_LAO_OSD)
    LANGUAGE_LAO,
  #endif

  #if(ENABLE_MYANMAR_OSD)
    LANGUAGE_MYANMAR,
  #endif

#endif
    LANGUAGE_MAORI,
    LANGUAGE_MANDARIN,
    LANGUAGE_CANTONESE,
};

#else   //!MENU_LANGUAGE_LITE
U16 _ZUI_TBLSEG stOsdLanguageList[] =
{
    LANGUAGE_CZECH,
    LANGUAGE_DANISH,
    LANGUAGE_GERMAN,
    LANGUAGE_ENGLISH,
    LANGUAGE_SPANISH,
    LANGUAGE_GREEK,
    LANGUAGE_FRENCH,
#if ENABLE_LANGUAGE_KOREA
    LANGUAGE_KOREA,
#endif  //ENABLE_LANGUAGE_KOREA
    LANGUAGE_CROATIAN,
    LANGUAGE_ITALIAN,
    LANGUAGE_HUNGARIAN,
    LANGUAGE_DUTCH,
    LANGUAGE_NORWEGIAN,
    LANGUAGE_POLISH,
    LANGUAGE_PORTUGUESE,
#if(ENABLE_UI_LANGUAGE_RUSSIAN)
    LANGUAGE_RUSSIAN,
#endif//ENABLE_UI_LANGUAGE_RUSSIAN
    LANGUAGE_ROMANIAN,
    LANGUAGE_SLOVENIAN,
    LANGUAGE_SERBIAN,
    LANGUAGE_FINNISH,
    LANGUAGE_SWEDISH,
    LANGUAGE_BULGARIAN,
    LANGUAGE_SLOVAK,
    LANGUAGE_TURKISH,
    LANGUAGE_THAI,
#if ( ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP || CHINESE_SIMP_FONT_ENABLE )
    LANGUAGE_CHINESE,
#endif  //ENABLE_DTMB_CHINA_APP
#if ( ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP || ENABLE_DVB_TAIWAN_APP || CHINESE_BIG5_FONT_ENABLE )
    LANGUAGE_CHINESE_TRAD,
#endif  //ENABLE_DTMB_CHINA_APP
#if(ENABLE_SOUTHEAST_ASIA_CERTIFICATION)
    LANGUAGE_INDONESIA,
    LANGUAGE_MALAYSIA,
    LANGUAGE_ARABIC,
#endif  //ENABLE_SOUTHEAST_ASIA_CERTIFICATION
#if(ENABLE_COUNTRY_VIETNAM)
    LANGUAGE_VIETNAM,
#endif  //ENABLE_COUNTRY_VIETNAM
#if(ENABLE_COUNTRY_GHANA)
    LANGUAGE_GHANA,
#endif  //ENABLE_COUNTRY_GHANA
#if(ENABLE_COUNTRY_KENYA)
    LANGUAGE_SWAHILI,
#endif  //ENABLE_COUNTRY_KENYA
#if(ENABLE_COUNTRY_MYANMAR)
    LANGUAGE_MYANMAR,
#endif  //ENABLE_COUNTRY_MYANMAR
#if(ENABLE_COUNTRY_ICELANDIC)
    LANGUAGE_ICELANDIC,
    LANGUAGE_SAMI,
#endif  //ENABLE_COUNTRY_ICELANDIC

#if(ENABLE_UYGHUR_OSD)
    LANGUAGE_UYGHUR,
#endif
#if (ENABLE_TTF_FONT)

  #if(ENABLE_INDIA_OSD)
    LANGUAGE_HINDI,
    LANGUAGE_URDU,
    LANGUAGE_TELUGU,
    LANGUAGE_TAMIL,
    LANGUAGE_MARATHI,
    LANGUAGE_BENGALI,
    LANGUAGE_ASSAMESE,
    LANGUAGE_GUJARATI,
    LANGUAGE_KANNADA,
    LANGUAGE_MALAYALAM,
    LANGUAGE_PUNJABI,
  #endif

  #if(ENABLE_KHMER_OSD)
    LANGUAGE_KHMER,
  #endif

  #if(ENABLE_LAO_OSD)
    LANGUAGE_LAO,
  #endif

  #if(ENABLE_MYANMAR_OSD)
    LANGUAGE_MYANMAR,
  #endif

#endif
};

EN_LANGUAGE _ZUI_TBLSEG stOsdAudLangList[] =
{
    LANGUAGE_CZECH,
    LANGUAGE_DANISH,
    LANGUAGE_GERMAN,
    LANGUAGE_ENGLISH,
    LANGUAGE_SPANISH,
    LANGUAGE_GREEK,
    LANGUAGE_FRENCH,
#if ENABLE_LANGUAGE_KOREA
    LANGUAGE_KOREA,
#endif  //ENABLE_LANGUAGE_KOREA
    LANGUAGE_CROATIAN,
    LANGUAGE_ITALIAN,
    LANGUAGE_HUNGARIAN,
    LANGUAGE_DUTCH,
    LANGUAGE_NORWEGIAN,
    LANGUAGE_POLISH,
    LANGUAGE_PORTUGUESE,
#if(ENABLE_UI_LANGUAGE_RUSSIAN)
    LANGUAGE_RUSSIAN,
#endif//ENABLE_UI_LANGUAGE_RUSSIAN
    LANGUAGE_ROMANIAN,
    LANGUAGE_SLOVENIAN,
    LANGUAGE_SERBIAN,
    LANGUAGE_FINNISH,
    LANGUAGE_SWEDISH,
    LANGUAGE_BULGARIAN,
    LANGUAGE_SLOVAK,
    LANGUAGE_TURKISH,
    LANGUAGE_THAI,
#if ( ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP || CHINESE_SIMP_FONT_ENABLE )
    LANGUAGE_CHINESE,
#endif  //ENABLE_DTMB_CHINA_APP
#if ( ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP || ENABLE_DVB_TAIWAN_APP || CHINESE_BIG5_FONT_ENABLE )
    LANGUAGE_CHINESE_TRAD,
#endif  //ENABLE_DTMB_CHINA_APP
#if(ENABLE_SOUTHEAST_ASIA_CERTIFICATION)
    LANGUAGE_INDONESIA,
    LANGUAGE_MALAYSIA,
    LANGUAGE_ARABIC,
#endif  //ENABLE_SOUTHEAST_ASIA_CERTIFICATION
#if(ENABLE_COUNTRY_VIETNAM)
    LANGUAGE_VIETNAM,
#endif  //ENABLE_COUNTRY_VIETNAM
#if(ENABLE_COUNTRY_GHANA)
    LANGUAGE_GHANA,
#endif  //ENABLE_COUNTRY_GHANA
#if(ENABLE_COUNTRY_KENYA)
    LANGUAGE_SWAHILI,
#endif  //ENABLE_COUNTRY_KENYA
#if(ENABLE_COUNTRY_MYANMAR)
    LANGUAGE_MYANMAR,
#endif  //ENABLE_COUNTRY_MYANMAR
    LANGUAGE_URDU,
    LANGUAGE_TELUGU,
    LANGUAGE_TAMIL,
    LANGUAGE_MARATHI,
    LANGUAGE_BENGALI,
    LANGUAGE_ASSAMESE,
    LANGUAGE_GUJARATI,
    LANGUAGE_KANNADA,
    LANGUAGE_MALAYALAM,
    LANGUAGE_PUNJABI,
#if(ENABLE_UYGHUR_OSD)
    LANGUAGE_UYGHUR,
#endif
#if (ENABLE_TTF_FONT)

  #if(ENABLE_INDIA_OSD)
    LANGUAGE_HINDI,
  #endif

  #if(ENABLE_KHMER_OSD)
    LANGUAGE_KHMER,
  #endif

  #if(ENABLE_LAO_OSD)
    LANGUAGE_LAO,
  #endif

  #if(ENABLE_MYANMAR_OSD)
    LANGUAGE_MYANMAR,
  #endif

#endif
    LANGUAGE_GAELIC,
    LANGUAGE_AKAN,
    LANGUAGE_EWE,
    LANGUAGE_TWI,
    LANGUAGE_NZEMA,
    LANGUAGE_HAUSA,
    LANGUAGE_KASEM,
    LANGUAGE_WELSH,
    LANGUAGE_IRISH,
};

EN_LANGUAGE _ZUI_TBLSEG stNzOsdAudLangList[] =
{
    LANGUAGE_CZECH,
    LANGUAGE_DANISH,
    LANGUAGE_GERMAN,
    LANGUAGE_ENGLISH,
    LANGUAGE_SPANISH,
    LANGUAGE_GREEK,
    LANGUAGE_FRENCH,
#if ENABLE_LANGUAGE_KOREA
    LANGUAGE_KOREA,
#endif  //ENABLE_LANGUAGE_KOREA
    LANGUAGE_CROATIAN,
    LANGUAGE_ITALIAN,
    LANGUAGE_HUNGARIAN,
    LANGUAGE_DUTCH,
    LANGUAGE_NORWEGIAN,
    LANGUAGE_POLISH,
    LANGUAGE_PORTUGUESE,
#if(ENABLE_UI_LANGUAGE_RUSSIAN)
    LANGUAGE_RUSSIAN,
#endif//ENABLE_UI_LANGUAGE_RUSSIAN
    LANGUAGE_ROMANIAN,
    LANGUAGE_SLOVENIAN,
    LANGUAGE_SERBIAN,
    LANGUAGE_FINNISH,
    LANGUAGE_SWEDISH,
    LANGUAGE_BULGARIAN,
    LANGUAGE_SLOVAK,
    LANGUAGE_TURKISH,
    LANGUAGE_THAI,
#if ( ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP || CHINESE_SIMP_FONT_ENABLE )
    LANGUAGE_CHINESE,
#endif  //ENABLE_DTMB_CHINA_APP
#if ( ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP || ENABLE_DVB_TAIWAN_APP || CHINESE_BIG5_FONT_ENABLE )
    LANGUAGE_CHINESE_TRAD,
#endif  //ENABLE_DTMB_CHINA_APP
#if(ENABLE_SOUTHEAST_ASIA_CERTIFICATION)
    LANGUAGE_INDONESIA,
    LANGUAGE_MALAYSIA,
    LANGUAGE_ARABIC,
#endif  //ENABLE_SOUTHEAST_ASIA_CERTIFICATION
#if(ENABLE_COUNTRY_VIETNAM)
    LANGUAGE_VIETNAM,
#endif  //ENABLE_COUNTRY_VIETNAM
#if(ENABLE_COUNTRY_GHANA)
    LANGUAGE_GHANA,
#endif  //ENABLE_COUNTRY_GHANA
#if(ENABLE_COUNTRY_KENYA)
    LANGUAGE_SWAHILI,
#endif  //ENABLE_COUNTRY_KENYA
#if(ENABLE_COUNTRY_MYANMAR)
    LANGUAGE_MYANMAR,
#endif  //ENABLE_COUNTRY_MYANMAR
    LANGUAGE_URDU,
    LANGUAGE_TELUGU,
    LANGUAGE_TAMIL,
    LANGUAGE_MARATHI,
    LANGUAGE_BENGALI,
    LANGUAGE_ASSAMESE,
    LANGUAGE_GUJARATI,
    LANGUAGE_KANNADA,
    LANGUAGE_MALAYALAM,
    LANGUAGE_PUNJABI,
#if(ENABLE_UYGHUR_OSD)
    LANGUAGE_UYGHUR,
#endif
#if (ENABLE_TTF_FONT)

  #if(ENABLE_INDIA_OSD)
    LANGUAGE_HINDI,
  #endif

  #if(ENABLE_KHMER_OSD)
    LANGUAGE_KHMER,
  #endif

  #if(ENABLE_LAO_OSD)
    LANGUAGE_LAO,
  #endif

  #if(ENABLE_MYANMAR_OSD)
    LANGUAGE_MYANMAR,
  #endif

#endif
    LANGUAGE_GAELIC,
    LANGUAGE_AKAN,
    LANGUAGE_EWE,
    LANGUAGE_TWI,
    LANGUAGE_NZEMA,
    LANGUAGE_HAUSA,
    LANGUAGE_KASEM,
    LANGUAGE_WELSH,
    LANGUAGE_IRISH,

#if !ENABLE_LANGUAGE_KOREA
    LANGUAGE_KOREAN,
#endif  //ENABLE_LANGUAGE_KOREA
    LANGUAGE_JAPAN,
    LANGUAGE_MAORI,
    LANGUAGE_MANDARIN,
    LANGUAGE_CANTONESE,
};

#if ENABLE_COUNTRY_SINGAPORE
EN_LANGUAGE _ZUI_TBLSEG stSgpOsdAudLangList[] =
{
    LANGUAGE_CZECH,
    LANGUAGE_DANISH,
    LANGUAGE_GERMAN,
    LANGUAGE_ENGLISH,
    LANGUAGE_SPANISH,
    LANGUAGE_GREEK,
    LANGUAGE_FRENCH,
#if ENABLE_LANGUAGE_KOREA
    LANGUAGE_KOREA,
#endif  //ENABLE_LANGUAGE_KOREA
    LANGUAGE_CROATIAN,
    LANGUAGE_ITALIAN,
    LANGUAGE_HUNGARIAN,
    LANGUAGE_DUTCH,
    LANGUAGE_NORWEGIAN,
    LANGUAGE_POLISH,
    LANGUAGE_PORTUGUESE,
#if(ENABLE_UI_LANGUAGE_RUSSIAN)
    LANGUAGE_RUSSIAN,
#endif//ENABLE_UI_LANGUAGE_RUSSIAN
    LANGUAGE_ROMANIAN,
    LANGUAGE_SLOVENIAN,
    LANGUAGE_SERBIAN,
    LANGUAGE_FINNISH,
    LANGUAGE_SWEDISH,
    LANGUAGE_BULGARIAN,
    LANGUAGE_SLOVAK,
    LANGUAGE_TURKISH,
    LANGUAGE_THAI,
#if ( ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP || CHINESE_SIMP_FONT_ENABLE )
    LANGUAGE_CHINESE,
#endif  //ENABLE_DTMB_CHINA_APP
#if ( ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP || ENABLE_DVB_TAIWAN_APP || CHINESE_BIG5_FONT_ENABLE )
    LANGUAGE_CHINESE_TRAD,
#endif  //ENABLE_DTMB_CHINA_APP
#if(ENABLE_SOUTHEAST_ASIA_CERTIFICATION)
    LANGUAGE_INDONESIA,
    LANGUAGE_MALAYSIA,
    LANGUAGE_ARABIC,
#endif  //ENABLE_SOUTHEAST_ASIA_CERTIFICATION
#if(ENABLE_COUNTRY_VIETNAM)
    LANGUAGE_VIETNAM,
#endif  //ENABLE_COUNTRY_VIETNAM
#if(ENABLE_COUNTRY_GHANA)
    LANGUAGE_GHANA,
#endif  //ENABLE_COUNTRY_GHANA
#if(ENABLE_COUNTRY_KENYA)
    LANGUAGE_SWAHILI,
#endif  //ENABLE_COUNTRY_KENYA
#if(ENABLE_COUNTRY_MYANMAR)
    LANGUAGE_MYANMAR,
#endif  //ENABLE_COUNTRY_MYANMAR
    LANGUAGE_URDU,
    LANGUAGE_TELUGU,
    LANGUAGE_TAMIL,
    LANGUAGE_MARATHI,
    LANGUAGE_BENGALI,
    LANGUAGE_ASSAMESE,
    LANGUAGE_GUJARATI,
    LANGUAGE_KANNADA,
    LANGUAGE_MALAYALAM,
    LANGUAGE_PUNJABI,
#if(ENABLE_UYGHUR_OSD)
    LANGUAGE_UYGHUR,
#endif
#if (ENABLE_TTF_FONT)

  #if(ENABLE_INDIA_OSD)
    LANGUAGE_HINDI,
  #endif

  #if(ENABLE_KHMER_OSD)
    LANGUAGE_KHMER,
  #endif

  #if(ENABLE_LAO_OSD)
    LANGUAGE_LAO,
  #endif

  #if(ENABLE_MYANMAR_OSD)
    LANGUAGE_MYANMAR,
  #endif

#endif
    LANGUAGE_GAELIC,
    LANGUAGE_AKAN,
    LANGUAGE_EWE,
    LANGUAGE_TWI,
    LANGUAGE_NZEMA,
    LANGUAGE_HAUSA,
    LANGUAGE_KASEM,
    LANGUAGE_WELSH,
    LANGUAGE_IRISH,

    LANGUAGE_QAA,
    LANGUAGE_QAB,
    LANGUAGE_QAC,
};
#endif  //ENABLE_COUNTRY_SINGAPORE

#endif  //MENU_LANGUAGE_LITE


#if(DVBC_CERTIFICATION_AUTOSCAN_ENABLE)
ST_OSD_SELECTION_STRING_MAPPING_LIST _ZUI_TBLSEG stAutoTuningCertificationList[] =
{
    {OSD_CERTIFICATION_OTHER, en_str_Other},
    {OSD_CERTIFICATION_UNITYMEDIA, en_str_Unitymedia},
    {OSD_CERTIFICATION_ZIGGO,en_str_Ziggo},
};

ST_OSD_SELECTION_STRING_MAPPING_LIST _ZUI_TBLSEG stAutoTuningUnityMediaCountryList[] =
{
    {OSD_UNITYMEDIA_COUNTRY_GERMANY, en_str_Germany},
};

ST_OSD_SELECTION_STRING_MAPPING_LIST _ZUI_TBLSEG stAutoTuningZiggoCountryList[] =
{
    {OSD_ZIGGO_COUNTRY_NETHERLANDS, en_str_Netherlands},
};

#endif

BOOLEAN MApp_ZUI_ACT_ExecuteTuningConfirmDialogAction(U16 act)
{
    switch(act)
    {
        case EN_EXE_CLOSE_TUNING_CONFIRM:
            MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_TUNE_CONFIRM, SW_HIDE);
          #if 0//ENABLE_T_C_COMBO
            extern EN_DVB_TYPE MApp_DVBType_GetCurrentType(void);
            if(MApp_DVBType_GetCurrentType() == EN_DVB_T_TYPE)
            {
                MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_DVB_SELECT_MENU, SW_SHOW);
                MApp_ZUI_API_SetFocus(HWND_SELECTED_DVBT_BG);
            }
            else
                MApp_ZUI_ACT_ShowDVBCScanPage();

          #else
            MApp_ZUI_ACT_ShowMainMenuBackground(HWND_MENU_BOTTOM_BALL_FOCUS_CHANNEL);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_PAGE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_MENU_CHANNEL_AUTOTUNE);
          #endif
            //MApp_ZUI_API_PostMessage(HWND_MENU_DLG_TUNE_CONFIRM, MSG_EFFECT_ROLLUP, 0);
            return TRUE;

        #if(DVBC_CERTIFICATION_AUTOSCAN_ENABLE)
        case EN_EXE_CLOSE_CERTIFICATION_TUNING_CONFIRM:
        {
            MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_TUNE_CERTIFICATION_CONFIRM, SW_HIDE);
            #if 0//ENABLE_T_C_COMBO
            extern EN_DVB_TYPE MApp_DVBType_GetCurrentType(void);
            if(MApp_DVBType_GetCurrentType() == EN_DVB_T_TYPE)
            {
                MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_DVB_SELECT_MENU, SW_SHOW);
                MApp_ZUI_API_SetFocus(HWND_SELECTED_DVBT_BG);
            }
            else
                MApp_ZUI_ACT_ShowDVBCScanPage();

          #else
            MApp_ZUI_ACT_ShowMainMenuBackground(HWND_MENU_BOTTOM_BALL_FOCUS_CHANNEL);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_PAGE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_MENU_CHANNEL_AUTOTUNE);
          #endif
            //MApp_ZUI_API_PostMessage(HWND_MENU_DLG_TUNE_CONFIRM, MSG_EFFECT_ROLLUP, 0);
            return TRUE;
        }
        #endif

    #if 0//ENABLE_T_C_COMBO
        case EN_EXE_CLOSE_DVB_SELECT:
            MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_DVB_SELECT_MENU, SW_HIDE);
            MApp_ZUI_ACT_ShowMainMenuBackground(HWND_MENU_BOTTOM_BALL_FOCUS_CHANNEL);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_PAGE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_MENU_CHANNEL_AUTOTUNE);
            if(IsDTVInUse())
            {
                MApp_DVBType_SetCurrentType(MApp_DVBType_GetPrevType());
                switch (MApp_DVBType_GetPrevType())
                {
                    case EN_DVB_T_TYPE:
                    {
                        if(msAPI_Tuner_GetDspStatus() != 0x01)//1: DVBT, 2:DVBC, 3:ATSC, 0xff: Null
                        {
                            MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);
                            msAPI_Tuner_SwitchSource((EN_DVB_TYPE)stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType, TRUE);
                            MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
                            //Cancel Freeze
                            if(MApp_IsImageFrozen())
                            {
                                MApp_SetImageFrozen(FALSE);
                                MApi_XC_FreezeImg(FALSE, MAIN_WINDOW);
                            }
                        }
                        break;
                   }
                    case EN_DVB_C_TYPE:
                    {
                        if(msAPI_Tuner_GetDspStatus() != 0x02)//1: DVBT, 2:DVBC, 3:ATSC, 0xff: Null
                        {
                            MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);
                            msAPI_Tuner_SwitchSource((EN_DVB_TYPE)stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType, TRUE);
                            MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
                            //Cancel Freeze
                            if(MApp_IsImageFrozen())
                            {
                                MApp_SetImageFrozen(FALSE);
                                MApi_XC_FreezeImg(FALSE, MAIN_WINDOW);
                            }
                        }
                        break;
                   }

                   default:
                    break;
                }
            }
            return TRUE;
    #endif

        /*case EN_EXE_DEC_TEMP_COUNTRY:
        case EN_EXE_INC_TEMP_COUNTRY:
            //from case MAPP_UIMENUFUNC_ADJUSTE2COUNTRY:
            _eTuningCountry = (EN_OSD_COUNTRY_SETTING)MApp_ZUI_ACT_DecIncValue_Cycle(
                act==EN_EXE_INC_TEMP_COUNTRY,
                _eTuningCountry, OSD_COUNTRY_AUSTRALIA, OSD_COUNTRY_NUMS-1, 1);

            MApp_ZUI_API_InvalidateWindow(HWND_MENU_DLG_TUNE_CONFIRM_COUNTRY_GRID);
            return TRUE;*/
        case EN_EXE_DEC_TUNE_TYPE:
        case EN_EXE_INC_TUNE_TYPE:
            //from case MAPP_UIMENUFUNC_ADJUSTE2COUNTRY:
            #if (ENABLE_SBTVD_DTV_SYSTEM)
                if(msAPI_SRC_IS_SBTVD_InUse())
                {
                    eTuneType = OSD_TUNE_TYPE_DTV_PLUS_ATV;
                }
                else
            #endif
                {
              #if (ENABLE_ATSC == DISABLE)
                {
                    eTuneType = (EN_OSD_TUNE_TYPE_SETTING)MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_TUNE_TYPE,
                    eTuneType, OSD_TUNE_TYPE_DTV_PLUS_ATV, OSD_TUNE_TYPE_NUMS-1, 1);
                }
                if(IsDVBCInUse())
                {
                   if(eTuneType==OSD_TUNE_TYPE_DTV_PLUS_ATV)
                   {
                      bOriginalSrcIsDvbc= TRUE;
                   }
                   else
                   {
                      bOriginalSrcIsDvbc= FALSE;
                   }
                }

              #endif
                }
            MApp_ZUI_API_InvalidateWindow(HWND_MENU_DLG_TUNE_CONFIRM_TUNE_TYPE_OPTION);
            return TRUE;
        #if(DVBC_CERTIFICATION_AUTOSCAN_ENABLE)
        case EN_EXE_DEC_CERTIFICATION_TUNE_TYPE:
        case EN_EXE_INC_CERTIFICATION_TUNE_TYPE:
        {
            eTuneType = (EN_OSD_TUNE_TYPE_SETTING)MApp_ZUI_ACT_DecIncValue_Cycle(
            act==EN_EXE_INC_CERTIFICATION_TUNE_TYPE,
            eTuneType, OSD_TUNE_TYPE_DTV_PLUS_ATV, OSD_TUNE_TYPE_NUMS-1, 1);
            MApp_ZUI_API_InvalidateWindow(HWND_MENU_DLG_TUNE_CONFIRM_TUNE_CERTIFICATION_TYPE_OPTION);
            return TRUE;
        }
        #endif
        default:
            ZUI_DBG_FAIL(printf("[ZUI]CLOCKACT\n"));
            ABORT();
    }

    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
LPTSTR MApp_ZUI_ACT_GetTuningConfirmDynamicText(HWND hwnd)
{
    U16 u16TempID = Empty;

    switch(hwnd)
    {
        case HWND_MENU_DLG_TUNE_CONFIRM_TUNE_TYPE_OPTION:
        #if(DVBC_CERTIFICATION_AUTOSCAN_ENABLE)
        case HWND_MENU_DLG_TUNE_CONFIRM_TUNE_CERTIFICATION_TYPE_OPTION:
        #endif

            #if (ENABLE_SBTVD_DTV_SYSTEM)
                if(msAPI_SRC_IS_SBTVD_InUse())
                    u16TempID = en_str_Air_plus_Cable;
                else
            #endif
            {
                switch(eTuneType)
                {
                    case OSD_TUNE_TYPE_DTV_PLUS_ATV:
                        u16TempID = en_str_DTV_plus_ATV;
                        break;
                    case OSD_TUNE_TYPE_DTV_ONLY:
                        u16TempID = en_str_DTV;
                        break;
                    case OSD_TUNE_TYPE_ATV_ONLY:
                        u16TempID = en_str_ATV;
                        break;

  #if ENABLE_DVBC
                    /*case OSD_TUNE_TYPE_CADTV_ONLY:
                        u16TempID = en_str_CADTV;
                        break;*/
  #endif

                    default :
                        u16TempID = en_str_DTV_plus_ATV;
                        break;
                 }
            }
            break;
    }

    if (u16TempID != Empty)
        return MApp_ZUI_API_GetString(u16TempID);

    return 0; //for empty string....
}

EN_OSD_COUNTRY_SETTING MApp_ZUI_ACT_GetTuningCountry(void)
{
    return _eTuningCountry;
}

void MApp_ZUI_ACT_SetTuningCountry(EN_OSD_COUNTRY_SETTING TuningCountry)
{
    _eTuningCountry = TuningCountry;
}

void MApp_ZUI_ACT_SetTuningCountryIndex(U8 u8Index)
{
    #if(DVBC_CERTIFICATION_AUTOSCAN_ENABLE)
        if(IsDVBCInUse())
        {
            switch(OSD_CERTIFICATION_SETTING)
            {
                case OSD_CERTIFICATION_OTHER:
                {
                    if (stAutoTuningCountryList[u8Index].u16SelectionItem >= OSD_COUNTRY_NUMS)
                    {
                        MS_DEBUG_MSG(printf("Set Country Overflow: %u\n", (U16)stAutoTuningCountryList[u8Index].u16SelectionItem));
                        _eTuningCountry = DEFAULT_TUNING_COUNTRY;
                    }
                    else
                    {
                        _eTuningCountry = (EN_OSD_COUNTRY_SETTING)stAutoTuningCountryList[u8Index].u16SelectionItem;
                    }
                    break;
                }
                case OSD_CERTIFICATION_UNITYMEDIA:
                {
                    if ((EN_OSD_UNITYMEDIA_COUNTRY_SETTING)stAutoTuningUnityMediaCountryList[u8Index].u16SelectionItem >= OSD_UNITYMEDIA_COUNTRY_NUMS)
                    {
                        _eTuningUnityMediaCountry = DEFAULT_TUNING_UNITYMEDIA_COUNTRY;
                    }
                    else
                    {
                        _eTuningUnityMediaCountry = (EN_OSD_UNITYMEDIA_COUNTRY_SETTING)stAutoTuningUnityMediaCountryList[u8Index].u16SelectionItem;
                    }
                    break;
                }
                case OSD_CERTIFICATION_ZIGGO:
                {
                    if ((EN_OSD_ZIGGO_COUNTRY_SETTING)stAutoTuningZiggoCountryList[u8Index].u16SelectionItem >= OSD_ZIGGO_COUNTRY_NUMS)
                    {
                        _eTuningZiggoCountry = DEFAULT_TUNING_ZIGGO_COUNTRY;
                    }
                    else
                    {
                        _eTuningZiggoCountry = (EN_OSD_ZIGGO_COUNTRY_SETTING)stAutoTuningZiggoCountryList[u8Index].u16SelectionItem;
                    }
                    break;
                }
                default:
                    break;
            }
        }
        else
    #endif
        {
            if (stAutoTuningCountryList[u8Index].u16SelectionItem >= OSD_COUNTRY_NUMS)
            {
                MS_DEBUG_MSG(printf("Set Country Overflow: %u\n", (U16)stAutoTuningCountryList[u8Index].u16SelectionItem));
                _eTuningCountry = DEFAULT_TUNING_COUNTRY;
            }
            else
            {
                _eTuningCountry = (EN_OSD_COUNTRY_SETTING)stAutoTuningCountryList[u8Index].u16SelectionItem;
            }
        }
    MApp_ZUI_API_InvalidateWindow(HWND_MENU_DLG_TUNE_CONFIRM);
}

U8 MApp_ZUI_ACT_GetTuningCountryIndexMax(void)
{
    #if(DVBC_CERTIFICATION_AUTOSCAN_ENABLE)
        if(IsDVBCInUse())
        {
            switch(OSD_CERTIFICATION_SETTING)
            {
                case OSD_CERTIFICATION_OTHER:
                {
                    return (U8)(sizeof(stAutoTuningCountryList)/sizeof(stAutoTuningCountryList[0])) - 1;
                }
                case OSD_CERTIFICATION_UNITYMEDIA:
                {
                    return (U8)(sizeof(stAutoTuningUnityMediaCountryList)/sizeof(stAutoTuningUnityMediaCountryList[0])) - 1;
                }
                case OSD_CERTIFICATION_ZIGGO:
                {
                    return (U8)(sizeof(stAutoTuningZiggoCountryList)/sizeof(stAutoTuningZiggoCountryList[0])) - 1;
                }
                default:
                    break;
            }
        }
    #endif
    return (U8)(sizeof(stAutoTuningCountryList)/sizeof(stAutoTuningCountryList[0])) - 1;
}

U8 MApp_ZUI_ACT_GetTuningCountryIndex(void)
{
    U8 u8Index = 0;
    for (u8Index = 0; u8Index <= MApp_ZUI_ACT_GetTuningCountryIndexMax(); u8Index++)
    {
        #if(DVBC_CERTIFICATION_AUTOSCAN_ENABLE)
        if(IsDVBCInUse())
        {
            switch(OSD_CERTIFICATION_SETTING)
            {
                case OSD_CERTIFICATION_OTHER:
                {
                    if (_eTuningCountry == (EN_OSD_COUNTRY_SETTING)stAutoTuningCountryList[u8Index].u16SelectionItem)
                    {
                        return u8Index;
                    }
                    break;
                }
                case OSD_CERTIFICATION_UNITYMEDIA:
                {
                    if (_eTuningUnityMediaCountry == (EN_OSD_UNITYMEDIA_COUNTRY_SETTING)stAutoTuningUnityMediaCountryList[u8Index].u16SelectionItem)
                    {
                        return u8Index;
                    }
                    break;
                }
                case OSD_CERTIFICATION_ZIGGO:
                {
                    if (_eTuningZiggoCountry == (EN_OSD_ZIGGO_COUNTRY_SETTING)stAutoTuningZiggoCountryList[u8Index].u16SelectionItem)
                    {
                        return u8Index;
                    }
                    break;
                }
                default:
                    break;
            }
        }
        else
        #endif
        if (_eTuningCountry == (EN_OSD_COUNTRY_SETTING)stAutoTuningCountryList[u8Index].u16SelectionItem)
        {
            return u8Index;
        }
    }
    return 0;
}

#if(DVBC_CERTIFICATION_AUTOSCAN_ENABLE)
EN_OSD_CERTIFICATION_SETTING MApp_ZUI_ACT_GetTuningCertification(void)
{
    return _eTuningCertification;
}

EN_OSD_UNITYMEDIA_COUNTRY_SETTING MApp_ZUI_ACT_GetTuningUnityMediaCountry(void)
{
    return _eTuningUnityMediaCountry;
}

EN_OSD_ZIGGO_COUNTRY_SETTING MApp_ZUI_ACT_GetTuningZiggoCountry(void)
{
    return _eTuningZiggoCountry;
}

void MApp_ZUI_ACT_SetTuningCertification(EN_OSD_CERTIFICATION_SETTING TuningCertification)
{
    _eTuningCertification = TuningCertification;
}

void MApp_ZUI_ACT_SetTuningUnityMediaCountry(EN_OSD_UNITYMEDIA_COUNTRY_SETTING TuningUnityMediaCountry)
{
    _eTuningUnityMediaCountry = TuningUnityMediaCountry;
}

void MApp_ZUI_ACT_SetTuningZiggoCountry(EN_OSD_ZIGGO_COUNTRY_SETTING TuningZiggoCountry)
{
    _eTuningZiggoCountry = TuningZiggoCountry;
}

void MApp_ZUI_ACT_SetTuningCertificationIndex(U8 u8Index)
{
    if (stAutoTuningCertificationList[u8Index].u16SelectionItem >= OSD_CERTIFICATION_NUMS)
    {
        MS_DEBUG_MSG(printf("Set Certification Overflow: %u\n", (U16)stAutoTuningCertificationList[u8Index].u16SelectionItem));
        _eTuningCertification = DEFAULT_TUNING_CERTIFICATION;
    }
    else
    {
        _eTuningCertification = (EN_OSD_CERTIFICATION_SETTING)stAutoTuningCertificationList[u8Index].u16SelectionItem;
    }
    MApp_ZUI_API_InvalidateWindow(HWND_MENU_DLG_TUNE_CERTIFICATION_CONFIRM);
}

U8 MApp_ZUI_ACT_GetTuningCertificationIndexMax(void)
{

   return (U8)(sizeof(stAutoTuningCertificationList)/sizeof(stAutoTuningCertificationList[0])) - 1;
}

U8 MApp_ZUI_ACT_GetTuningCertificationIndex(void)
{
    U8 u8Index = 0;
    for (u8Index = 0; u8Index <= MApp_ZUI_ACT_GetTuningCertificationIndexMax(); u8Index++)
    {
        if (_eTuningCertification == (EN_OSD_CERTIFICATION_SETTING)stAutoTuningCertificationList[u8Index].u16SelectionItem)
        {
            return u8Index;
        }
    }
    return 0;
}
LPTSTR MApp_ZUI_ACT_GetCertificationStringByIndex(U8 u8Index)
{
    U16 u16TempID = Empty;
    if (u8Index > MApp_ZUI_ACT_GetTuningCertificationIndexMax())
    {
        return 0;   //exceed Certification list count
    }

    u16TempID = stAutoTuningCertificationList[u8Index].u16StringIndex;
    if (u16TempID != Empty)
        return MApp_ZUI_API_GetString(u16TempID);

    return 0; //for empty string....
}

#endif


U16 MApp_ZUI_ACT_GetCountryStringID(EN_OSD_COUNTRY_SETTING country)
{
    U16 u16TempID = Empty;
    U8 u8Index = 0;
    for (u8Index = 0; u8Index <= MApp_ZUI_ACT_GetTuningCountryIndexMax(); u8Index++)
    {
        if (country == (EN_OSD_COUNTRY_SETTING)stAutoTuningCountryList[u8Index].u16SelectionItem)
        {
            u16TempID = stAutoTuningCountryList[u8Index].u16StringIndex;
        }
    }

  #if ENABLE_AUTOTEST
    if(g_bAutobuildDebug)
    {
        switch(tempcheck2)
        {
            case HWND_MENU_OPTION_COUNTRY_OPTION:
                if(Country != u16TempID)
                {
                    printf("73_Country\n");
                }
                Country = u16TempID;
                break;
            default:

                break;
        }
    }
  #endif
    return u16TempID;
}

LPTSTR MApp_ZUI_ACT_GetCountryStringByIndex(U8 u8Index)
{
    U16 u16TempID = Empty;
    if (u8Index > MApp_ZUI_ACT_GetTuningCountryIndexMax())
    {
        return 0;   //exceed country list count
    }
    #if(DVBC_CERTIFICATION_AUTOSCAN_ENABLE)
        if(IsDVBCInUse())
        {
            switch(OSD_CERTIFICATION_SETTING)
            {
                case OSD_CERTIFICATION_OTHER:
                {
                    u16TempID = stAutoTuningCountryList[u8Index].u16StringIndex;
                    break;
                }
                case OSD_CERTIFICATION_UNITYMEDIA:
                {
                    u16TempID = stAutoTuningUnityMediaCountryList[u8Index].u16StringIndex;
                    break;
                }
                case OSD_CERTIFICATION_ZIGGO:
                {
                    u16TempID = stAutoTuningZiggoCountryList[u8Index].u16StringIndex;
                    break;
                }
                default:
                    break;
            }
        }
        else
    #endif
    u16TempID = stAutoTuningCountryList[u8Index].u16StringIndex;
    if (u16TempID != Empty)
        return MApp_ZUI_API_GetString(u16TempID);

    return 0; //for empty string....
}

extern LPTSTR MApp_ZUI_ACT_GetMenuLanguageStringByIndex(U8 u8Index);

U8 MApp_ZUI_ACT_GetOsdLanguageIndexMax(void)
{
    return (U8)(sizeof(stOsdLanguageList)/sizeof(stOsdLanguageList[0])) - 1;
}

U8 MApp_ZUI_ACT_GetOsdLanguageListIndex(EN_LANGUAGE enCurLang)
{
    U8 u8Index;
    U8 u8IdxMax = MApp_ZUI_ACT_GetOsdLanguageIndexMax();

    for(u8Index = 0; u8Index <= u8IdxMax; u8Index++)
    {
        if(stOsdLanguageList[u8Index] == enCurLang)
            return u8Index;
    }
    return 0;
}

LPTSTR MApp_ZUI_ACT_GetOsdLanguageListString(U8 u8Index)
{
    if (u8Index > MApp_ZUI_ACT_GetOsdLanguageIndexMax())
    {
        return 0;   //exceed country list count
    }
    return MApp_ZUI_ACT_GetMenuLanguageStringByIndex(stOsdLanguageList[u8Index]);
}

U8 MApp_ZUI_ACT_GetOsdAudLangIndexMax(void)
{
    if(OSD_COUNTRY_SETTING == E_NEWZEALAND)
    {
        return (U8)(sizeof(stNzOsdAudLangList)/sizeof(stNzOsdAudLangList[0])) - 1;
    }
#if ENABLE_COUNTRY_SINGAPORE
    else if(OSD_COUNTRY_SETTING == E_SINGAPORE)
    {
        return (U8)(sizeof(stSgpOsdAudLangList)/sizeof(stSgpOsdAudLangList[0])) - 1;
    }
#endif
    else
    {
        return (U8)(sizeof(stOsdAudLangList)/sizeof(stOsdAudLangList[0])) - 1;
    }
}

U8 MApp_ZUI_ACT_GetOsdAudLangListIndex(EN_LANGUAGE enCurLang)
{
    U8 u8Index;
    U8 u8IdxMax = MApp_ZUI_ACT_GetOsdAudLangIndexMax();
    /*U16*/EN_LANGUAGE *u16List;

    if(OSD_COUNTRY_SETTING == E_NEWZEALAND)
    {
        u16List = stNzOsdAudLangList;
    }
#if ENABLE_COUNTRY_SINGAPORE
    else if(OSD_COUNTRY_SETTING == E_SINGAPORE)
    {
        u16List = stSgpOsdAudLangList;
    }
#endif
    else
    {
        u16List = stOsdAudLangList;
    }

    for(u8Index = 0; u8Index <= u8IdxMax; u8Index++)
    {
        if(u16List[u8Index] == enCurLang)
            return u8Index;
    }
    return 0;
}

LPTSTR MApp_ZUI_ACT_GetOsdAudLangListString(U8 u8Index)
{
    if (u8Index > MApp_ZUI_ACT_GetOsdAudLangIndexMax())
    {
        return 0;   //exceed country list count
    }

    if(OSD_COUNTRY_SETTING == E_NEWZEALAND)
    {
        return MApp_ZUI_ACT_GetMenuLanguageStringByIndex(stNzOsdAudLangList[u8Index]);
    }
#if ENABLE_COUNTRY_SINGAPORE
    else if(OSD_COUNTRY_SETTING == E_SINGAPORE)
    {
        return MApp_ZUI_ACT_GetMenuLanguageStringByIndex(stSgpOsdAudLangList[u8Index]);
    }
#endif
    else
    {
        return MApp_ZUI_ACT_GetMenuLanguageStringByIndex(stOsdAudLangList[u8Index]);
    }
}

EN_LANGUAGE MApp_ZUI_ACT_GetOsdAudLangByListIndex(U8 u8Index)
{
    if (u8Index > MApp_ZUI_ACT_GetOsdAudLangIndexMax())
    {
        return LANGUAGE_DEFAULT;
    }

    if(OSD_COUNTRY_SETTING == E_NEWZEALAND)
    {
        return (EN_LANGUAGE)stNzOsdAudLangList[u8Index];
    }
#if ENABLE_COUNTRY_SINGAPORE
    else if(OSD_COUNTRY_SETTING == E_SINGAPORE)
    {
        return (EN_LANGUAGE)stSgpOsdAudLangList[u8Index];
    }
#endif
    else
    {
        return (EN_LANGUAGE)stOsdAudLangList[u8Index];
    }
}

#define stOsdSubLangList    stOsdAudLangList
#define stNzOsdSubLangList  stNzOsdAudLangList


U8 MApp_ZUI_ACT_GetOsdSubtitleIndexMax(void)
{
    if(OSD_COUNTRY_SETTING == E_NEWZEALAND)
    {
        return (U8)(sizeof(stNzOsdSubLangList)/sizeof(stNzOsdSubLangList[0])) - 1;
    }
    else
    {
        return (U8)(sizeof(stOsdSubLangList)/sizeof(stOsdSubLangList[0])) - 1;
    }
}

U8 MApp_ZUI_ACT_GetOsdSubtitleListIndex(EN_LANGUAGE enCurLang)
{
    U8 u8Index;
    U8 u8IdxMax = MApp_ZUI_ACT_GetOsdSubtitleIndexMax();
    /*U16*/EN_LANGUAGE *u16List;

    if(OSD_COUNTRY_SETTING == E_NEWZEALAND)
    {
        u16List = stNzOsdSubLangList;
    }
    else
    {
        u16List = stOsdSubLangList;
    }

    for(u8Index = 0; u8Index <= u8IdxMax; u8Index++)
    {
        if(u16List[u8Index] == enCurLang)
            return u8Index;
    }
    return 0;
}

LPTSTR MApp_ZUI_ACT_GetOsdSubtitleListString(U8 u8Index)
{
    if (u8Index > MApp_ZUI_ACT_GetOsdSubtitleIndexMax())
    {
        return 0;   //exceed country list count
    }

    if(OSD_COUNTRY_SETTING == E_NEWZEALAND)
    {
        return MApp_ZUI_ACT_GetMenuLanguageStringByIndex(stNzOsdSubLangList[u8Index]);
    }
    else
    {
        return MApp_ZUI_ACT_GetMenuLanguageStringByIndex(stOsdSubLangList[u8Index]);
    }
}

EN_LANGUAGE MApp_ZUI_ACT_GetOsdSubtitleByListIndex(U8 u8Index)
{
    if (u8Index > MApp_ZUI_ACT_GetOsdSubtitleIndexMax())
    {
        return LANGUAGE_DEFAULT;
    }

    if(OSD_COUNTRY_SETTING == E_NEWZEALAND)
    {
        return (EN_LANGUAGE)stNzOsdSubLangList[u8Index];
    }
    else
    {
        return (EN_LANGUAGE)stOsdSubLangList[u8Index];
    }
}

#undef MAPP_ZUI_ACTTUNECONFIRMFUNC_C

