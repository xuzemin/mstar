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
#define _INFOBLOCK_C_
///////////////////////////////////////////////////////////////////////////////
///@file InfoBlock.c
///@version rev.00 00000
///@author MStarSemi Inc.
///@brief System Information block
///
///@endcode
///////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>
#include "Board.h"
#include "datatype.h"
#include "hwreg.h"
#include "sysinfo.h"
#include "InfoBlock.h"
#include "msAPI_MMap.h"
#include "MsTypes.h"
#include "drvBDMA.h"
#include "msIR.h"
#include "BinInfo.h"
#include "debug.h"

#include "drvPQ_Define.h"
#include "MApp_FlashMap.h"

#ifdef SUPPORT_AP_BIN_IN_FLASH_2
#include "msAPI_MIU.h"
#include "msAPI_Flash.h"
#endif

#if ENABLE_CI_PLUS
    #include "msAPI_OpCache.h"
#endif

#include "msAPI_Font.h"

#if (ENABLE_ATSC_TTS)
#include "msAPI_TTS_Sys.h"
#endif


//------------------------------------------------------------------------------
// Local Defines
//------------------------------------------------------------------------------
#define INFOERROR_DBG(x)   MS_DEBUG_MSG(x)
#define INFOBLOCK_DBG(x)
#ifdef SUPPORT_AP_BIN_IN_FLASH_2
#define FLASH_2_ERROR_DBG(x)   x
#define FLASH_2_DBG(x)        // x
#define FLASH2_BIN_PACKAGE_HEADER_ID0   0x69335809
#define FLASH_2_BIN_COUNTER_ADD         5
#define FLASH_2_BIN_INFO_START_ADD      7
#define FLASH_2_BIN_FILE_MAX_NUM        10
#define FLASH_2_BIN_INFO_SIZE           11
#endif

#define NULL_DATA   0xCCCCCCCC
//jing fixme plz
#define BinItem(id) PlaceU16_(id), PlaceU32_(NULL_DATA), PlaceU32_(NULL_DATA), PlaceU8_(0xCC)
// Special bin item for bootloader
#define BL_BinItemStart(id, adr) PlaceU16_(id), PlaceU32_(adr), PlaceU32_(NULL_DATA), PlaceU8_(0xCC)

//------------------------------------------------------------------------------
// Table
//------------------------------------------------------------------------------
#ifdef SUPPORT_AP_BIN_IN_FLASH_2
volatile U8 BinaryInfoBlock[] __attribute__((__section__ (".img_info"))) =
#else
volatile U8 const BinaryInfoBlock[] __attribute__((__section__ (".img_info"))) =
#endif
#if (BLOADER) //Bootloader
{
    //--------------------------------------------------------------------------
    // Binary Package
    //--------------------------------------------------------------------------
    // Header ID Code
    PlaceU32_(BIN_PACKAGE_HEADER_ID0), PlaceU32_(BIN_PACKAGE_HEADER_ID1),

    // Check reserved FLASH SIZE
    // Use flash map define
    PlaceU32_( (FMAP_TOTAL_USE_BANK_END)*FLASH_BLOCK_SIZE),


    // Binary Number: Filled by external tool
    PlaceU16_(0),

    ////////////////////////////////////////////////////////////////////////////
    // Bin List
    ////////////////////////////////////////////////////////////////////////////
#if(ENABLE_DTV)
    // DEMUX, ID, Address, Size
    BinItem(BIN_ID_CODE_DEMUX_COMPRESS),
#endif


    // Demod DSP Code
    #if ENABLE_ATSC

    #endif

    #if ENABLE_DVBT
        #if(FRONTEND_DEMOD_DVBT_TYPE == EMBEDDED_DVBT_DEMOD)
            //#ifndef INTERN_DVBT_LOAD_FW_FROM_CODE_MEMORY
            #if( INTERN_DVBT_LOAD_CODE_FROM_SEL == INTERN_DVBT_LOAD_CODE_FROM_BIN )
            BinItem(BIN_ID_INTERN_DVBT),
            #endif
        #endif
    #endif
    #if ENABLE_DVBC
        #if(FRONTEND_DEMOD_DVBC_TYPE == EMBEDDED_DVBC_DEMOD)
            //#ifndef INTERN_DVBC_LOAD_FW_FROM_CODE_MEMORY
            #if( INTERN_DVBC_LOAD_CODE_FROM_SEL == INTERN_DVBC_LOAD_CODE_FROM_BIN )
            BinItem(BIN_ID_INTERN_DVBC),
            #endif
        #endif
    #endif



#if (BLOADER && ENABLE_BL_UI)
    BinItem(BIN_ID_FONT_BL_ENG_50),
#endif //(BLOADER && ENABLE_BL_UI)

    //=====================================================================
    // Put the following ID 0xF000 at the end of this file.
    // It will be verified by bootloader for integrity check.
    BinItem(BIN_ID_MAGIC_55AAABCD)
};
#else //(!BLOADER) main AP
{
    //--------------------------------------------------------------------------
    // Binary Package
    //--------------------------------------------------------------------------
    // Header ID Code
    PlaceU32_(BIN_PACKAGE_HEADER_ID0), PlaceU32_(BIN_PACKAGE_HEADER_ID1),

    // Check reserved FLASH SIZE
    // Use flash map define
    PlaceU32_( (FMAP_TOTAL_USE_BANK_END)*FLASH_BLOCK_SIZE),

    // Binary Number: Filled by external tool
    PlaceU16_(0),

    ////////////////////////////////////////////////////////////////////////////
    // Bin List
    ////////////////////////////////////////////////////////////////////////////

#if 0//(MAZDA_TMP_PATCH)
    BinItem(BIN_ID_JPEG_BOOT_LOGO),
#else

    // Audio DSP bin
#if( ENABLE_AUDIO_DSP_BIN )
    BinItem(BIN_ID_CODE_AUDIO_DSP),
#endif

#if( ENABLE_AUDIO_DEC_R2_BIN)
    BinItem(BIN_ID_CODE_AUDIO_DEC_R2),
#endif

#if( ENABLE_AUDIO_2ND_R2 )
    BinItem(BIN_ID_CODE_AUDIO_2ND_R2),
#endif


#if (ENABLE_ATSC_TTS)
 #if(FLASH_SIZE <=FLASH_SIZE_4MB)
    BinItem(BIN_ID_TTS_ENG_PROSODY_COMPRESS),
    BinItem(BIN_ID_TTS_ENG_VOICE_COMPRESS),
 #else
    BinItem(BIN_ID_TTS_ENG_PROSODY),
    BinItem(BIN_ID_TTS_ENG_VOICE),
 #endif
  #if(ENABLE_TTS_LANG_ENGLISH_NLP)
    BinItem(BIN_ID_TTS_ENG_NLP),
  #endif

  #if(ENABLE_TTS_LANG_ES_MX)
    BinItem(BIN_ID_TTS_MX_PROSODY),
    BinItem(BIN_ID_TTS_MX_VOICE),
  #endif

  #if(ENABLE_TTS_LANG_FRANCH)
    BinItem(BIN_ID_TTS_FR_PROSODY),
    BinItem(BIN_ID_TTS_FR_VOICE),
  #endif

  #if(ENABLE_TTS_LANG_KO)
    BinItem(BIN_ID_TTS_KR_PROSODY),
    BinItem(BIN_ID_TTS_KR_VOICE),
  #endif
#endif

#if ENABLE_KEY_TO_SPEECH
    BinItem(BIN_ID_KTS_POWER_ON),
    BinItem(BIN_ID_KTS_POWER_OFF),
    BinItem(BIN_ID_KTS_CHANNEL_UP),
    BinItem(BIN_ID_KTS_CHANNEL_DOWN),
    BinItem(BIN_ID_KTS_VOLUME_UP),
    BinItem(BIN_ID_KTS_VOLUME_DOWN),
    BinItem(BIN_ID_KTS_MUTE_ON),
    BinItem(BIN_ID_KTS_MUTE_OFF),
    BinItem(BIN_ID_KTS_MENU),
    BinItem(BIN_ID_KTS_SOURCE),
#endif

 #if (ENABLE_DTV)
    // DEMUX, ID, Address, Size
   #if(FLASH_SIZE <=FLASH_SIZE_4MB)
     BinItem(BIN_ID_CODE_DEMUX_COMPRESS),
   #else
    BinItem(BIN_ID_CODE_DEMUX),
   #endif
 #endif


#if (MHEG5_ENABLE)
    // MHEG5, ID, Address, Size
    BinItem(BIN_ID_CODE_MHEG5),

   #ifdef MHEG5_BIG5_FONT_ENABLE
    BinItem(BIN_ID_AEON_M5FONT_24LE),
    BinItem(BIN_ID_AEON_M5FONT_26LE),
    BinItem(BIN_ID_AEON_M5FONT_31LE),
    BinItem(BIN_ID_AEON_M5FONT_36LE),
    BinItem(BIN_ID_AEON_M5FONT_RM),
   #endif

#endif

#if 0//ENABLE_DMP
  #if (ENABLE_CAPE ==1)
    BinItem(BIN_ID_CODE_AEON_CAPE),
  #endif
#endif



#if( ENABLE_SBOOT_LOAD_BIN )
    BinItem(BIN_ID_CODE_AEON_JOBA),
#endif


#if ENABLE_AUTOTEST
  #ifdef BIN_ID_CODE_AEON_BENCHMARK
    BinItem(BIN_ID_CODE_AEON_BENCHMARK),
  #endif
#endif


    // MVF code, ID, Address, Size
#if VECTOR_FONT_ENABLE
    //BinItem(BIN_ID_CODE_AEON_FONT),
#endif //VECTOR_FONT_ENABLE


    // MVF Font, ID, Address, Size
#if VECTOR_FONT_ENABLE
    BinItem(BIN_ID_FONT_MSTAR_MVF),

  #if(COPRO_MVF_ENABLE)
    BinItem(BIN_ID_CODE_AEON_MVF),
  #endif

  #if (ENABLE_ARABIC_OSD)
   // BinItem(BIN_ID_FONT_ARABIC_26),//ID:0x0112
    //BinItem(BIN_ID_FONT_ARABIC_30),//ID:0x0113
    BinItem(BIN_ID_FONT_ARABIC_35),//ID:0x0114
    //BinItem(BIN_ID_FONT_ARABIC_50),//ID:0x0115
  #endif

  #if (ENABLE_THAI_OSD)
    BinItem(BIN_ID_FONT_THAI_26),//ID:0x0116
    //BinItem(BIN_ID_FONT_THAI_30),//ID:0x0117
    //BinItem(BIN_ID_FONT_THAI_35),//ID:0x0118
    //BinItem(BIN_ID_FONT_THAI_50),//ID:0x0119
  #endif

#else

  #if (ENABLE_DVB_TAIWAN_APP || CHINESE_BIG5_FONT_ENABLE)
    BinItem(BIN_ID_FONT_BIG5_CH),
  #elif (ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP||CHINESE_SIMP_FONT_ENABLE)
    BinItem(BIN_ID_FONT_SIMP_CH),
  #elif (ENABLE_LANGUAGE_KOREA)
    BinItem(BIN_ID_FONT_KOREA),
  #else
    BinItem(BIN_ID_FONT_SIMP_CH),
  #endif

#endif // #if VECTOR_FONT_ENABLE


#if (ENABLE_TTX)
#ifdef TTX_USING_MSTAR_FONT_BIN
    BinItem(BIN_ID_FONT_TTX),
#endif
#endif


#if (ENABLE_SECURITY_R2)
    BinItem(BIN_ID_CODE_SECU_R2),
#endif


#if (BRAZIL_CC)
    // CC, ID, Address, Size
    BinItem(BIN_ID_FONT_DTVCC),
    BinItem(BIN_ID_FONT_ATVCC),
    //BinItem(BIN_ID_FONT_CS1 ),
    //BinItem(BIN_ID_FONT_CS2 ),
#endif // #if (BRAZIL_CC)

#if(ATSC_CC == DTV_CC)
#if KOREAN_CC_ENABLE
    BinItem(BIN_ID_WANSUNGCODE_TABLE),
    BinItem(BIN_ID_FONT_CS0),
    BinItem(BIN_ID_FONT_CS1),
    BinItem(BIN_ID_FONT_CS2),
    BinItem(BIN_ID_FONT_CS3 ),
    BinItem(BIN_ID_FONT_CS4 ),
    BinItem(BIN_ID_FONT_CS5 ),
#elif (((MEMORY_MAP == MMAP_32MB) && (ENABLE_32M_H264 == ENABLE)) \
        || (UI_SKIN_SEL ==  UI_SKIN_960X540XI8)\
        || (UI_SKIN_SEL ==  UI_SKIN_960X540X565))
    BinItem(BIN_ID_FONT_CS0 ),
    BinItem(BIN_ID_FONT_CS1 ),
    BinItem(BIN_ID_FONT_CS2 ),
    BinItem(BIN_ID_FONT_CS3 ),
    BinItem(BIN_ID_FONT_CS4 ),
    BinItem(BIN_ID_FONT_CS5 ),
    BinItem(BIN_ID_FONT_CS6_960),
    BinItem(BIN_ID_FONT_CS7_960 ),
    BinItem(BIN_ID_FONT_CS8_960 ),
    BinItem(BIN_ID_FONT_CS9_960 ),
    BinItem(BIN_ID_FONT_CS10_960),
    BinItem(BIN_ID_FONT_CS11_960),
    BinItem(BIN_ID_FONT_CS12_960),
    BinItem(BIN_ID_FONT_CS13_960),
    BinItem(BIN_ID_FONT_CS14_960),
    BinItem(BIN_ID_FONT_CS15_960),
    BinItem(BIN_ID_FONT_CS16_960),
    BinItem(BIN_ID_FONT_CS17_960),
    BinItem(BIN_ID_FONT_CS18_960),
    BinItem(BIN_ID_FONT_CS19_960),
    BinItem(BIN_ID_FONT_CS20_960),
    BinItem(BIN_ID_FONT_CS21_960),
    BinItem(BIN_ID_FONT_CS22_960),
    BinItem(BIN_ID_FONT_CS23_960),
#else
#if((UI_SKIN_SEL ==  UI_SKIN_1366X768X565) \
        ||(UI_SKIN_SEL ==  UI_SKIN_1366X768X4444) \
        ||(UI_SKIN_SEL ==  UI_SKIN_1366X768X565) \
        ||(UI_SKIN_SEL ==  UI_SKIN_1366X768X8888))
    BinItem(BIN_ID_FONT_CS0 ),
    BinItem(BIN_ID_FONT_CS1 ),
    BinItem(BIN_ID_FONT_CS2 ),
    BinItem(BIN_ID_FONT_CS3 ),
    BinItem(BIN_ID_FONT_CS4 ),
    BinItem(BIN_ID_FONT_CS5 ),
    BinItem(BIN_ID_FONT_CS6 ),
    BinItem(BIN_ID_FONT_CS7 ),
    BinItem(BIN_ID_FONT_CS8 ),
    BinItem(BIN_ID_FONT_CS9 ),
    BinItem(BIN_ID_FONT_CS10),
    BinItem(BIN_ID_FONT_CS11),
    BinItem(BIN_ID_FONT_CS12),
    BinItem(BIN_ID_FONT_CS13),
    BinItem(BIN_ID_FONT_CS14),
    BinItem(BIN_ID_FONT_CS15),
    BinItem(BIN_ID_FONT_CS16),
    BinItem(BIN_ID_FONT_CS17),
    BinItem(BIN_ID_FONT_CS18),
    BinItem(BIN_ID_FONT_CS19),
    BinItem(BIN_ID_FONT_CS20),
    BinItem(BIN_ID_FONT_CS21),
    BinItem(BIN_ID_FONT_CS22),
    BinItem(BIN_ID_FONT_CS23),
 #elif(UI_SKIN_SEL ==  UI_SKIN_1920X1080X565)
    BinItem(BIN_ID_FONT_CS0 ),
    BinItem(BIN_ID_FONT_CS1 ),
    BinItem(BIN_ID_FONT_CS2 ),
    BinItem(BIN_ID_FONT_CS3 ),
    BinItem(BIN_ID_FONT_CS4 ),
    BinItem(BIN_ID_FONT_CS5 ),
    BinItem(BIN_ID_FONT_CS6_FHD),
    BinItem(BIN_ID_FONT_CS7_FHD ),
    BinItem(BIN_ID_FONT_CS8_FHD ),
    BinItem(BIN_ID_FONT_CS9_FHD ),
    BinItem(BIN_ID_FONT_CS10_FHD),
    BinItem(BIN_ID_FONT_CS11_FHD),
    BinItem(BIN_ID_FONT_CS12_FHD),
    BinItem(BIN_ID_FONT_CS13_FHD),
    BinItem(BIN_ID_FONT_CS14_FHD),
    BinItem(BIN_ID_FONT_CS15_FHD),
    BinItem(BIN_ID_FONT_CS16_FHD),
    BinItem(BIN_ID_FONT_CS17_FHD),
    BinItem(BIN_ID_FONT_CS18_FHD),
    BinItem(BIN_ID_FONT_CS19_FHD),
    BinItem(BIN_ID_FONT_CS20_FHD),
    BinItem(BIN_ID_FONT_CS21_FHD),
    BinItem(BIN_ID_FONT_CS22_FHD),
    BinItem(BIN_ID_FONT_CS23_FHD),

 #endif
#endif



#elif (ATSC_CC == ATV_CC)
    BinItem(BIN_ID_FONT_CS0),
#endif // #if (ATSC_CC == ATV_CC)

#if (DISPLAY_LOGO == 1)
    BinItem(BIN_ID_JPEG_BOOT_LOGO),
#endif

#if ((ENABLE_DMP) && (ENABLE_POWERON_MUSIC))
    BinItem(BIN_ID_MELODY_ON),
#endif

#if ((ENABLE_DMP) && (ENABLE_GAME_BG_MUSIC))
    BinItem(BIN_ID_GAME_MUSIC),
#endif

#if ENABLE_PANEL_BIN
    BinItem(BIN_ID_PANEL_BIN),
#endif

#if ENABLE_IR_BIN
    BinItem(BIN_ID_IR_MSTAR),
#endif

#if (ENABLE_POWERON_VIDEO == 1)
        BinItem(BIN_ID_VIDEO_ON),
#endif

    // LZSS, ID, Address, Size
    //BinItem(BIN_ID_CODE_LZ),

    // BMP, ID, Address, Size
    BinItem(BIN_ID_OSDCP_BMP),

#if(UI_SKIN_SEL == UI_SKIN_960X540XI8 )
    BinItem(BIN_ID_OSDCP_PALETTE),
#endif

#if ENABLE_SOUNDTEST_MUSIC_LOOP && ENABLE_EWS
    BinItem(BIN_ID_EWS_MP3),
#endif


    // TEXT, ID, Address, Size
    BinItem(BIN_ID_OSDCP_TEXT),


#if ENABLE_PQ_BIN
    BinItem(BIN_ID_PQ_MAIN),
    BinItem(BIN_ID_PQ_MAIN_TEXT),
    BinItem(BIN_ID_PQ_MAIN_EX),
#endif

#if( ENABLE_TCON_2014)
    BinItem(BIN_ID_TCON),
#endif
#if( ENABLE_OVERDRIVE)
    BinItem(BIN_ID_OVERDRIVE),
#endif


#if(ENABLE_DTV) //ndef ENABLE_ATV_MM

 #if( VDEC_BIN_IS_FW_VPU )

    BinItem(BIN_ID_CODE_VDEC_FW_VPU),

 #else // VDEC_BIN_IS_FW_VPU

      #if ENABLE_DYNAMIC_H264_FW_LOADING
        #if(!((CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN) || (CHIP_FAMILY_TYPE==CHIP_FAMILY_WHISKY) || (CHIP_FAMILY_TYPE==CHIP_FAMILY_MELODY)))//// Don't pack BIN_ID_CODE_AEON_H264  // same as BIN_ID_MM_HVD
         BinItem(BIN_ID_CODE_AEON_H264),
        #endif
        #if( (CHIP_FAMILY_TYPE==CHIP_FAMILY_NASA)&& (CHIP_SUPPORT_HEVC)) //IMPLEMENT_DTV_H265
         BinItem(BIN_ID_CODE_AEON_H265),
        #endif
      #endif

     #if ENABLE_DYNAMIC_MVD_FW_LOADING
       #if ((CHIP_FAMILY_TYPE==CHIP_FAMILY_NASA)||(CHIP_FAMILY_TYPE==CHIP_FAMILY_EDEN)||(CHIP_FAMILY_TYPE==CHIP_FAMILY_EULER))
         BinItem(BIN_ID_CODE_AEON_MVD),
       #endif
     #endif

  #endif // VDEC_BIN_IS_FW_VPU

#endif // ENABLE_DTV


#if(ENABLE_FRC_R2)
    BinItem(BIN_ID_CODE_AEON_FRC),
#endif

//---------------------------------------------------------------------------
#if( ENABLE_DMP && ENABLE_HK_LOAD_MM_VDEC )

 #if ( (MEMORY_MAP <= MMAP_32MB) )

    BinItem(BIN_ID_MM_HVD),
    BinItem(BIN_ID_MM_HVD_VLC),
    BinItem(BIN_ID_MM_MVD),
    BinItem(BIN_ID_MM_EVD),

 #else

    #if(VDEC_BIN_IS_FW_VPU)//(ENABLE_VDEC_2_0)
      #if( (BIN_ID_MM_VPU != BIN_ID_CODE_VDEC_FW_VPU)||(!ENABLE_DTV) )
        BinItem(BIN_ID_MM_VPU),
      #endif
        BinItem(BIN_ID_MM_VPU_VLC),

    #elif (MM_PHOTO_MUSIC_ONLY)
        BinItem(BIN_ID_MM_MVD),        //PHOTO_ONLY

    #else
        BinItem(BIN_ID_MM_HVD),
        BinItem(BIN_ID_MM_MVD),
        BinItem(BIN_ID_MM_HVD_VLC),
       #if (ENABLE_H265)
        BinItem(BIN_ID_MM_EVD),
       #endif
    #endif

 #endif

#endif // ENABLE_DMP && ENABLE_HK_LOAD_MM_VDEC

//---------------------------------------------------------------------------

#if (ENABLE_TTF_FONT)
    BinItem(BIN_ID_FONT_UI_TTF_TAMIL),
    BinItem(BIN_ID_FONT_UI_TTF_MYMR),
    BinItem(BIN_ID_FONT_UI_TTF_KHMER),
    BinItem(BIN_ID_FONT_UI_TTF_LAO),

    #if ( ENABLE_INDIA_OSD )
      BinItem(BIN_ID_FONT_UI_TTF_HINDI),
    #endif

#endif


#if (ENABLE_TEST_PATTERN&&ENABLE_BMP_TEST_PATTERN)
	BinItem(BIN_ID_BMP_TestPattern_0),
	BinItem(BIN_ID_BMP_TestPattern_1),
#endif


    // MM source :  MM-Aeon vdplayer.bin
#if( ENABLE_DMP && VD_PLAYER_IS_IN_CROP_CPU )
  #if(!MAYA_LITE)
    BinItem(BIN_ID_CODE_VDPLAYER),
  #endif
#endif

#endif

#if (SUPPORT_BIN_MANAGER)
    BinItem(BIN_ID_BINMANAGER_KEY),
#endif

    //=====================================================================
    // Put the following ID 0xF000 at the end of this file.
    // It will be verified by bootloader for integrity check.
    BinItem(BIN_ID_MAGIC_55AAABCD)
};
#endif //(!BLOADER)

BOOLEAN Get_BinInfo(BININFO *pBinInfo)
{
    BININFO Fmt;
    U16 i, Count;
    U8 const *p;

    Count = (U16)(BinaryInfoBlock[BIN_PACKAGE_NUMBER_ADDR]<<8) + BinaryInfoBlock[BIN_PACKAGE_NUMBER_ADDR+1];
    INFOBLOCK_DBG(printf("Get_BinInfo: Count=%u\n", Count));

    // get the whole header content
    for ( i = 0; i < Count; i++ )
    {
    #ifdef SUPPORT_AP_BIN_IN_FLASH_2
        p = (U8 *)&BinaryInfoBlock[BIN_PACKAGE_BINFO_ADDR+i*BIN_PACKAGE_BINFO_SIZE];
    #else
        p = (U8 const *)&BinaryInfoBlock[BIN_PACKAGE_BINFO_ADDR+i*BIN_PACKAGE_BINFO_SIZE];
    #endif

        Fmt.B_ID = ReadU16BE(p + 0);
        Fmt.B_FAddr = ReadU32BE(p + 2);
        Fmt.B_Len = ReadU32BE(p + 6);
        Fmt.B_IsComp = p[10];

        //printf("ID = 0x%04X : IsComp = 0x%02X \n", Fmt.B_ID, Fmt.B_IsComp);

        INFOBLOCK_DBG(printf("Search ID:%04X:Addr:0x%08X, Len:0x%08X\n", Fmt.B_ID, Fmt.B_FAddr, Fmt.B_Len));
        if ( Fmt.B_ID == pBinInfo->B_ID )
        {
            pBinInfo->B_FAddr  = Fmt.B_FAddr + 0;//MDrv_MIU_SPI_GetOffset();
            pBinInfo->B_Len    = (Fmt.B_Len + 7) & ~7;
            pBinInfo->B_IsComp = Fmt.B_IsComp;
            INFOBLOCK_DBG(printf("Success ID:%04X:Addr:0x%08X, Len:0x%08X\n", pBinInfo->B_ID, pBinInfo->B_FAddr, pBinInfo->B_Len));
            return TRUE;
        }
    }

    INFOERROR_DBG(printf("Get_BinInfo::Fail ID:%04X:Addr:0x%08lX, Len:0x%08lX\n", pBinInfo->B_ID, pBinInfo->B_FAddr, pBinInfo->B_Len));

    return FALSE;
}


#ifdef SUPPORT_AP_BIN_IN_FLASH_2

void InfoBlock_DumpBinInfo(void)
{
    BININFO Fmt;
    U16 i, Count;
    U8 *p;

    Count = (U16)(BinaryInfoBlock[BIN_PACKAGE_NUMBER_ADDR]<<8) + BinaryInfoBlock[BIN_PACKAGE_NUMBER_ADDR+1];

    FLASH_2_DBG(printf("++++++++++++++ Dump All Bin Info +++++++++++++++++++\n", Count));
    FLASH_2_DBG(printf("+++:Get_BinInfo: Count=%u\n", Count));

    // get the whole header content
    for ( i = 0; i < Count; i++ )
    {
        p = (U8 *)&BinaryInfoBlock[BIN_PACKAGE_BINFO_ADDR+i*BIN_PACKAGE_BINFO_SIZE];

        Fmt.B_ID = ReadU16BE(p + 0);
        Fmt.B_FAddr = ReadU32BE(p + 2);
        Fmt.B_Len = ReadU32BE(p + 6);
        Fmt.B_IsComp = p[10];

        FLASH_2_DBG(printf("+++ %d:(ID=0x%x)Addr:0x%08X, Len:0x%08X (Comp=0x%bx)\n"
            ,i, Fmt.B_ID,Fmt.B_FAddr,Fmt.B_Len,  Fmt.B_IsComp));

    }

    FLASH_2_DBG(printf("++++++++++++++++++++++++++++++++++++++++++++++\n", Count));

    return ;
}


BOOL InfoBlock_UpdateBinInfo(BININFO *pBinInfo)
{
    BININFO Fmt;
    U16 i, Count;
    U8 *p;

    Count = (U16)(BinaryInfoBlock[BIN_PACKAGE_NUMBER_ADDR]<<8) + BinaryInfoBlock[BIN_PACKAGE_NUMBER_ADDR+1];

    FLASH_2_DBG(printf(">>>:Get_BinInfo: Count=%u\n", Count));
    // get the whole header content
    for ( i = 0; i < Count; i++ )
    {
        p = (U8 *)&BinaryInfoBlock[BIN_PACKAGE_BINFO_ADDR+i*BIN_PACKAGE_BINFO_SIZE];

        Fmt.B_ID = ReadU16BE(p + 0);
        Fmt.B_FAddr = ReadU32BE(p + 2);
        Fmt.B_Len = ReadU32BE(p + 6);
        Fmt.B_IsComp = p[10];

        if ( Fmt.B_ID == pBinInfo->B_ID )
        {//Update Bin info
            FLASH_2_DBG(printf(">>>:Found it, Before update:(ID=0x%x)Addr:0x%lx, Len:0x%lx (Comp=0x%bx)\n"
                , Fmt.B_ID,Fmt.B_FAddr,Fmt.B_Len,  Fmt.B_IsComp));
            //Update add
            *(p + 2) = (U8)((pBinInfo->B_FAddr)>>24);
            *(p + 3) = (U8)((pBinInfo->B_FAddr)>>16);
            *(p + 4) = (U8)((pBinInfo->B_FAddr)>>8);
            *(p + 5) = (U8)((pBinInfo->B_FAddr));
            //Update Len
            *(p + 6) = (U8)((pBinInfo->B_Len)>>24);
            *(p + 7) = (U8)((pBinInfo->B_Len)>>16);
            *(p + 8) = (U8)((pBinInfo->B_Len)>>8);
            *(p + 9) = (U8)((pBinInfo->B_Len));
            //Update IsComp
            *(p + 10) = *(p + 10)|0x80; //To enable Flash_2 flag

            Fmt.B_ID = ReadU16BE(p + 0);
            Fmt.B_FAddr = ReadU32BE(p + 2);
            Fmt.B_Len = ReadU32BE(p + 6);
            Fmt.B_IsComp = p[10];
            FLASH_2_DBG(printf(">>>:After update:(ID=0x%x)Addr:0x%lx, Len:0x%lx (Comp=0x%bx)\n"
                , Fmt.B_ID,Fmt.B_FAddr,Fmt.B_Len,  Fmt.B_IsComp));

            return TRUE;
        }
    }

    FLASH_2_ERROR_DBG(printf(">>> Can't find this ID = 0x%x\n",pBinInfo->B_ID));

    return FALSE;
}

BOOL InfoBlock_Flash_2_Bin_Init(void)
{
    U8  *pu8Temp_1;
    U8  i;
    U16 u16BinCount;
    U32 *pu32Temp;
    BININFO Fmt;

    FLASH_2_DBG(printf(" ++++++++++ Flash_2_Bin_Init +++++++++++++\n"));

    msFlash_ChipSelect(FLASH_2_NUM);
    #if 1//(CHIP_FAMILY_TYPE != CHIP_FAMILY_MAYA)
    pu8Temp_1 = (U8 *)((SUBTITLE_MEMORY_TYPE & MIU1) ? (SUBTITLE_ADR | MIU_INTERVAL) : (SUBTITLE_ADR));
    msAPI_MIU_Copy((U32)0x0000, (U32)((SUBTITLE_MEMORY_TYPE & MIU1) ? (SUBTITLE_ADR | MIU_INTERVAL) : (SUBTITLE_ADR)), 160, MIU_FLASH2SDRAM);
    #else
    pu8Temp_1 = (U8 *)((DEMUX_FILTER_TYPE & MIU1) ? (SUBTITLE_MM_VIDEO_ADR | MIU_INTERVAL) : (SUBTITLE_MM_VIDEO_ADR));
    msAPI_MIU_Copy((U32)0x0000, (U32)((DEMUX_FILTER_TYPE & MIU1) ? (SUBTITLE_MM_VIDEO_ADR | MIU_INTERVAL) : (SUBTITLE_MM_VIDEO_ADR)), 160, MIU_FLASH2SDRAM);
    #endif

    msFlash_ChipSelect(FLASH_ID0);

//<1>.To parse head file
    pu32Temp = (U32 *)((SUBTITLE_MEMORY_TYPE & MIU1) ? (SUBTITLE_ADR | MIU_INTERVAL) : (SUBTITLE_ADR));

    if (*pu32Temp == FLASH2_BIN_PACKAGE_HEADER_ID0)
    {
        FLASH_2_DBG(printf("---> Flash-2 Magic Number = PASS\n"));

        u16BinCount = *(pu8Temp_1+FLASH_2_BIN_COUNTER_ADD);
        u16BinCount = (u16BinCount<<8) + *(pu8Temp_1+FLASH_2_BIN_COUNTER_ADD+1);

        if (u16BinCount > FLASH_2_BIN_FILE_MAX_NUM)
        {
            FLASH_2_ERROR_DBG(printf("---> Flash-2: Bin counter(0x%bx)(0x%bx) > Max => FAIL \n",*(pu8Temp_1+5),*(pu8Temp_1+6)));
            return FALSE;
        }
    }
    else
    {
        FLASH_2_ERROR_DBG(printf("---> Flash-2 Magic Number = FAIL\n"));
        return FALSE;
    }

//<2>.To parse Bin file
    FLASH_2_DBG(printf("---> Flash-2: Count = 0x%x\n",u16BinCount));

    pu8Temp_1 = (U8 *)((SUBTITLE_MEMORY_TYPE & MIU1) ? (SUBTITLE_ADR | MIU_INTERVAL) : (SUBTITLE_ADR)) + FLASH_2_BIN_INFO_START_ADD;
    for (i=0;i<u16BinCount;i++)
    {
        Fmt.B_ID     = ReadU16BE(pu8Temp_1 + 0);
        Fmt.B_FAddr  = ReadU32BE(pu8Temp_1 + 2);
        Fmt.B_Len    = ReadU32BE(pu8Temp_1 + 6);
        FLASH_2_DBG(printf("---> Flash-2,Update Info: Bin-%d (ID=0x%x,Add=0x%lx,Size=0x%lx) \n"
            ,i,Fmt.B_ID,Fmt.B_FAddr,Fmt.B_Len));

        InfoBlock_UpdateBinInfo(&Fmt);
        pu8Temp_1 +=FLASH_2_BIN_INFO_SIZE;
    }

    return TRUE;
}

BOOL InfoBlock_Flash_2_Checking_Start(BININFO *pBinInfo)
{
    if ((pBinInfo->B_IsComp & 0x80)>0)
    {
        FLASH_2_DBG(printf("!!! Bin file(0x%x) in Flash_2, switch to Flash_2 \n",pBinInfo->B_ID));

        msFlash_ChipSelect(FLASH_2_NUM);

        return TRUE;
    }

    return FALSE;
}

BOOL InfoBlock_Flash_2_Checking_End(BININFO *pBinInfo)
{
    if ((pBinInfo->B_IsComp & 0x80)>0)
    {
        FLASH_2_DBG(printf("!!! After read Bin file, switch to Flash_1 \n",pBinInfo->B_ID));

        msFlash_ChipSelect(FLASH_ID0);

        return TRUE;
    }

    return FALSE;
}
#endif // #ifdef SUPPORT_AP_BIN_IN_FLASH_2





#undef _INFOBLOCK_C_

