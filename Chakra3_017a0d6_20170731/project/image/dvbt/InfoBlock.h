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

#ifndef _INFOBLOCK_H_
#define _INFOBLOCK_H_

#include "Board.h"

#include "Panel.h"

#include "BinInfo.h"
#include "datatype.h"



////////////////////////////////////////////////////////////////////////////////
///@file InfoBlock.h
///@version rev.00 00000
///@author MStarSemi Inc.
///@brief System Information Block Data
///
///@endcode
////////////////////////////////////////////////////////////////////////////////
#ifdef _INFOBLOCK_C_
#define INTERFACE
#else
#define INTERFACE extern
#endif

// Utility define
#define PlaceU32(x) x&0xFF, (x>>8)&0xFF, (x>>16)&0xFF, (x>>24)&0xFF
#define PlaceU16(y) y&0xFF, (y>>8)&0xFF
#define PlaceU32_(x) ((x)>>24)&0xFF, ((x)>>16)&0xFF, ((x)>>8)&0xFF, (x)&0xFF
#define PlaceU16_(y) ((y)>>8)&0xFF, (y)&0xFF
#define PlaceU8_(z) z

//------------------------------------------------------------------------------
// Functions
//------------------------------------------------------------------------------
INTERFACE BOOLEAN Get_BinInfo(BININFO *pBinInfo);
INTERFACE void Get_BinaryInfoBlock(U32 *u32Addr, U32 *u32Size);
INTERFACE void Get_BinInfoBlock(BININFO *Fmt, U8 *u8Addr);

U32 InfoBlock_Get_MergeBinSize(void);

#ifdef SUPPORT_AP_BIN_IN_FLASH_2
BOOL InfoBlock_Flash_2_Bin_Init(void);
void InfoBlock_DumpBinInfo(void);
BOOL InfoBlock_Flash_2_Checking_Start(BININFO *pBinInfo);
BOOL InfoBlock_Flash_2_Checking_End(BININFO *pBinInfo);
#endif

//============================================================================
// Power on logo
    #define BIN_ID_JPEG_BOOT_LOGO       BIN_ID_JPEG_BOOT_LOGO_DVB
// Power on music
    #define BIN_ID_MELODY_ON            BIN_ID_MELODY_ON_DVB
// Power on video?
#if(ENABLE_POWERON_VIDEO)
    #define BIN_ID_VIDEO_ON             BIN_ID_VIDEO_ON_DVB
#endif
// Game music
    #define BIN_ID_GAME_MUSIC           BIN_ID_MELODY_ON_DVB

//============================================================================
#if( (UI_SKIN_SEL==UI_SKIN_960X540X565 || UI_SKIN_SEL==UI_SKIN_960X540XI8)||(CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA))
    #define BIN_ID_FONT_SIMP_CH     BIN_ID_FONT_SIMP_CH_18x18
#else
  #if (ENABLE_UYGHUR_OSD)
      #define BIN_ID_FONT_SIMP_CH     BIN_ID_FONT_SIMP_CH_UYGH
  #else
      #define BIN_ID_FONT_SIMP_CH     BIN_ID_FONT_SIMP_CH_24x24
  #endif
#endif

#if ENABLE_LANGUAGE_KOREA
    #define BIN_ID_FONT_KOREA     BIN_ID_FONT_KOREA_20
#endif
    #define FONT_BIG5_I2                BIN_ID_FONT_BIG5_CH
    #define FONT_CHINESE_I2             BIN_ID_FONT_SIMP_CH
    #define FONT_MSTAR_UNICODE_MVF      BIN_ID_FONT_MSTAR_MVF

#if (BRAZIL_CC)
    #define BIN_ID_FONT_CS0                 BIN_ID_FONT_DTVCC//for Brazil CC,SWF 960*540
    #define BIN_ID_FONT_CS1                 BIN_ID_FONT_ATVCC
    //#define BIN_ID_FONT_CS2                 BIN_ID_FONT_CS2_NK

#elif (ATSC_CC)


#if( (UI_SKIN_SEL ==  UI_SKIN_1366X768X4444)    \
   ||(UI_SKIN_SEL ==  UI_SKIN_1366X768X565)     \
   ||(UI_SKIN_SEL ==  UI_SKIN_1366X768X8888)    )
    #if KOREAN_CC_ENABLE
        #define BIN_ID_FONT_CS0       BIN_ID_FONT_CS0_KOREAN
        #define BIN_ID_FONT_CS1       BIN_ID_FONT_CS1_KOREAN
        #define BIN_ID_FONT_CS2       BIN_ID_FONT_CS2_KOREAN
        #define BIN_ID_FONT_CS3       BIN_ID_FONT_CS3_KOREAN
        #define BIN_ID_FONT_CS4       BIN_ID_FONT_CS4_KOREAN
        #define BIN_ID_FONT_CS5       BIN_ID_FONT_CS5_KOREAN
    #elif ((MEMORY_MAP == MMAP_32MB) && (ENABLE_32M_H264 == ENABLE))
        #define BIN_ID_FONT_CS0       BIN_ID_FONT_CS0_NK_960
        #define BIN_ID_FONT_CS1       BIN_ID_FONT_CS1_NK_960
        #define BIN_ID_FONT_CS2       BIN_ID_FONT_CS2_NK_960
        #define BIN_ID_FONT_CS3       BIN_ID_FONT_CS3_NK_960
        #define BIN_ID_FONT_CS4       BIN_ID_FONT_CS4_NK_960
        #define BIN_ID_FONT_CS5       BIN_ID_FONT_CS5_NK_960
    #else
        #define BIN_ID_FONT_CS0     BIN_ID_FONT_CS0_NK
        #define BIN_ID_FONT_CS1     BIN_ID_FONT_CS1_NK
        #define BIN_ID_FONT_CS2     BIN_ID_FONT_CS2_NK
        #define BIN_ID_FONT_CS3     BIN_ID_FONT_CS3_NK
        #define BIN_ID_FONT_CS4     BIN_ID_FONT_CS4_NK
        #define BIN_ID_FONT_CS5     BIN_ID_FONT_CS5_NK
    #endif

#elif(UI_SKIN_SEL ==  UI_SKIN_1920X1080X565)
    #if KOREAN_CC_ENABLE
        #define BIN_ID_FONT_CS0       BIN_ID_FONT_CS0_KOREAN_FHD
        #define BIN_ID_FONT_CS1       BIN_ID_FONT_CS1_KOREAN_FHD
        #define BIN_ID_FONT_CS2       BIN_ID_FONT_CS2_KOREAN_FHD
        #define BIN_ID_FONT_CS3       BIN_ID_FONT_CS3_KOREAN_FHD
        #define BIN_ID_FONT_CS4       BIN_ID_FONT_CS4_KOREAN_FHD
        #define BIN_ID_FONT_CS5       BIN_ID_FONT_CS5_KOREAN_FHD
    #else
        #define BIN_ID_FONT_CS0       BIN_ID_FONT_CS0_NK_FHD
        #define BIN_ID_FONT_CS1       BIN_ID_FONT_CS1_NK_FHD
        #define BIN_ID_FONT_CS2       BIN_ID_FONT_CS2_NK_FHD
        #define BIN_ID_FONT_CS3       BIN_ID_FONT_CS3_NK_FHD
        #define BIN_ID_FONT_CS4       BIN_ID_FONT_CS4_NK_FHD
        #define BIN_ID_FONT_CS5       BIN_ID_FONT_CS5_NK_FHD
    #endif

#elif(UI_SKIN_SEL ==  UI_SKIN_960X540X565)
    #define BIN_ID_FONT_CS0       BIN_ID_FONT_CS0_NK_960
    #define BIN_ID_FONT_CS1       BIN_ID_FONT_CS1_NK_960
    #define BIN_ID_FONT_CS2       BIN_ID_FONT_CS2_NK_960
    #define BIN_ID_FONT_CS3       BIN_ID_FONT_CS3_NK_960
    #define BIN_ID_FONT_CS4       BIN_ID_FONT_CS4_NK_960
    #define BIN_ID_FONT_CS5       BIN_ID_FONT_CS5_NK_960

#endif // UI_SKIN_SEL == ?

#endif // CC type ==?

//============================================================================

#if (UI_SKIN_SEL == UI_SKIN_960X540XI8)
    #define BIN_ID_OSDCP_BMP            BIN_ID_OSDCP_BMP_960x540xI8_SW_LOAD

#elif (UI_SKIN_SEL==UI_SKIN_960X540X565)

  #if(SW_LOAD_BMP_ON_DEMAND)
    #if(ENABLE_BMP_REDUCE)
        #define BIN_ID_OSDCP_BMP        BIN_ID_OSDCP_BMP_960x540x565_SW_LOAD_SMALL
    #else
        #define BIN_ID_OSDCP_BMP        BIN_ID_OSDCP_BMP_960x540x565_SW_LOAD
    #endif
  #else
    #define BIN_ID_OSDCP_BMP            BIN_ID_OSDCP_BMP_960x540x565
  #endif

#elif (UI_SKIN_SEL==UI_SKIN_1920X1080X565)

  #if(SW_LOAD_BMP_ON_DEMAND)
    #define BIN_ID_OSDCP_BMP            BIN_ID_OSDCP_BMP_1920x1080x565_SW_LOAD
  #else
    #define BIN_ID_OSDCP_BMP            BIN_ID_OSDCP_BMP_1920x1080x565
  #endif

#elif(UI_SKIN_SEL == UI_SKIN_1366X768X565)

  #if(SW_LOAD_BMP_ON_DEMAND)
   #if(ENABLE_BMP_REDUCE)
       #define BIN_ID_OSDCP_BMP            BIN_ID_OSDCP_BMP_1366x768x565_SW_LOAD_SMALL
   #else
       #define BIN_ID_OSDCP_BMP            BIN_ID_OSDCP_BMP_1366x768x565_SW_LOAD
   #endif
  #else
    #define BIN_ID_OSDCP_BMP            BIN_ID_OSDCP_BMP_1366x768x565
  #endif

#else

    #error "Unsupported UI size"

#endif

//============================================================================

#if (UI_SKIN_SEL==UI_SKIN_960X540XI8)
    #define BIN_ID_OSDCP_TEXT       BIN_ID_OSDCP_TEXT_960x540xI8

#elif (UI_SKIN_SEL==UI_SKIN_960X540X565)
    #define BIN_ID_OSDCP_TEXT       BIN_ID_OSDCP_TEXT_960x540x565

#elif (UI_SKIN_SEL==UI_SKIN_1920X1080X565)
    #define BIN_ID_OSDCP_TEXT       BIN_ID_OSDCP_TEXT_1920x1080x565

#elif(UI_SKIN_SEL == UI_SKIN_1366X768X565)
    #define BIN_ID_OSDCP_TEXT       BIN_ID_OSDCP_TEXT_1366x768x565

#else
    #error "Unsupported UI size"

#endif

//============================================================================

#if (ENABLE_DTMB)
    #define BIN_ID_CODE_MHEG5           BIN_ID_CODE_MHEG5_BIG5
#else
    #define BIN_ID_CODE_MHEG5           BIN_ID_CODE_MHEG5_A
#endif

#if (VD_PLAYER_IS_IN_CROP_CPU)
    #if (MEMORY_MAP <= MMAP_32MB)
      #define BIN_ID_CODE_VDPLAYER        BIN_ID_CODE_AEON_VDPLAYER_32M
    #elif ((MEMORY_MAP == MMAP_64MB) && (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON))
      #define BIN_ID_CODE_VDPLAYER        BIN_ID_CODE_AEON_VDPLAYER_64M
    #elif((CHIP_FAMILY_TYPE == CHIP_FAMILY_WHISKY)&&(MM_PHOTO_MUSIC_ONLY))
      #define BIN_ID_CODE_VDPLAYER        BIN_ID_CODE_AEON_PHOTOPLAYER
    #else
      #define BIN_ID_CODE_VDPLAYER        BIN_ID_CODE_AEON_VDPLAYER
    #endif
#endif

//#ifdef BIN_ID_CODE_AEON_BENCHMARK_HK_MIPS_NOS
//    #define BIN_ID_CODE_AEON_BENCHMARK  BIN_ID_CODE_AEON_BENCHMARK_HK_MIPS_NOS
//#endif

//============================================================================

#if (ENABLE_TTX)
    #define TTX_USING_MSTAR_FONT_BIN
    #define BIN_ID_FONT_TTX             BIN_ID_TTFONT_34_30
#endif //end of ENABLE_TTX

#if (ENABLE_TEST_PATTERN)
#define BIN_ID_BMP_TestPattern_0    BIN_ID_PATTERN_1_FHD
#define BIN_ID_BMP_TestPattern_1    BIN_ID_PATTERN_2_FHD
#endif

//============================================================================

#if( ENABLE_AUDIO_DEC_R2_BIN )
    #if( ENABLE_AUDIO_DEC_R2_BIN_COMPRESS )
        #if ((MEMORY_MAP == MMAP_32MB)&&(CHIP_FAMILY_TYPE==CHIP_FAMILY_WHISKY))
        #define BIN_ID_CODE_AUDIO_DEC_R2    BIN_ID_CODE_AUDIO_DEC_R2_COMP_LITE
        #elif(ENABLE_AUDIO_R2_LITE)
        #define BIN_ID_CODE_AUDIO_DEC_R2    BIN_ID_CODE_AUDIO_DEC_R2_64M_COMP_LITE
        #else
        #define BIN_ID_CODE_AUDIO_DEC_R2    BIN_ID_CODE_AUDIO_DEC_R2_COMP
        #endif
    #else
        #if ((MEMORY_MAP == MMAP_32MB)&&(CHIP_FAMILY_TYPE==CHIP_FAMILY_WHISKY))
        #define BIN_ID_CODE_AUDIO_DEC_R2    BIN_ID_CODE_AUDIO_DEC_R2_NO_COMP_LITE
        #elif(ENABLE_AUDIO_R2_LITE)
        #define BIN_ID_CODE_AUDIO_DEC_R2    BIN_ID_CODE_AUDIO_DEC_R2_64M_NO_COMP_LITE
        #else
        #define BIN_ID_CODE_AUDIO_DEC_R2    BIN_ID_CODE_AUDIO_DEC_R2_NO_COMP
        #endif
    #endif
#endif

    // Audio and R2
#if( ENABLE_AUDIO_2ND_R2 )
    #if( ENABLE_AUDIO_DEC_R2_BIN_COMPRESS )
        #define BIN_ID_CODE_AUDIO_2ND_R2    BIN_ID_CODE_AUDIO_DEC_R2_2_COMP
    #else
        #define BIN_ID_CODE_AUDIO_2ND_R2    BIN_ID_CODE_AUDIO_DEC_R2_2_NO_COMP
    #endif
#endif


#if (FLASH_SIZE >= FLASH_SIZE_8MB) //8MB use no compress bin file to speed up channel change
    #if((CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN) || (CHIP_FAMILY_TYPE==CHIP_FAMILY_WHISKY))
        #define BIN_ID_CODE_AEON_H264   BIN_ID_MM_HVD
    #else
        #define BIN_ID_CODE_AEON_H264   BIN_ID_CODE_AEON_H264_NO_COMPRESS
    #endif

    #if( MAYA_LITE )
        #define BIN_ID_CODE_VDEC_FW_VPU BIN_ID_CODE_VDEC_FWVPU_COMPRESS
    #else
        #define BIN_ID_CODE_VDEC_FW_VPU BIN_ID_CODE_VDEC_FWVPU_NO_COMPRESS
    #endif

#else
    #if((CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN) || (CHIP_FAMILY_TYPE==CHIP_FAMILY_WHISKY))
        #define BIN_ID_CODE_AEON_H264   BIN_ID_MM_HVD
    #else
        #define BIN_ID_CODE_AEON_H264   BIN_ID_CODE_AEON_H264_COMPRESS
    #endif
    #define BIN_ID_CODE_VDEC_FW_VPU BIN_ID_CODE_VDEC_FWVPU_COMPRESS
#endif

#if ENABLE_PANEL_BIN
    #define BIN_ID_PANEL_BIN            BIN_ID_PANEL
#endif

//==========================================================================
#if (ENABLE_SECURITY_R2)
  #if (MEMORY_MAP == MMAP_64MB)
    #define BIN_ID_CODE_SECU_R2     BIN_ID_CODE_SECU_R2_64
  #else
   #if( LD_ENABLE&&LD_ALGO_RUN_IN_CROP )
    #define BIN_ID_CODE_SECU_R2     BIN_ID_CODE_SECU_R2_128_LD
   #else
        #if(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA)
        #define BIN_ID_CODE_SECU_R2     BIN_ID_CODE_SECU_R2_256
        #else
            #if(HDCP22_ALL_R2_TASK_ENABLE)
                #define BIN_ID_CODE_SECU_R2     BIN_ID_CODE_SECU_R2_128_NEW
            #else
                #define BIN_ID_CODE_SECU_R2     BIN_ID_CODE_SECU_R2_128
            #endif
        #endif
   #endif
  #endif
#endif


/*************************************************************************************************************/
#undef INTERFACE
#endif // _INFOBLOCK_H_

