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
// (��MStar Confidential Information��) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
// File Name: SW_Config_Trunk_Dvbt.h
// Description: Customization and Specialization for default board!
// Revision History:
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _SW_CONFIG_TRUNK_MAYA_128M_H_
#define _SW_CONFIG_TRUNK_MAYA_128M_H_


#define SW_CONFIG_NAME              "TRUNK_MAYA_128M"

#ifndef ENABLE
#define ENABLE                      1
#endif

#ifndef DISABLE
#define DISABLE                     0
#endif

//-------------------------------------------------------------------------------
// Bootloader System
//-------------------------------------------------------------------------------



//-------------------------------------------------------------------------------
// DTV System
//-------------------------------------------------------------------------------
/*
#define DTV_SYSTEM_NONE                 0
#define DTV_SYSTEM_DVBT                 1
#define DTV_SYSTEM_DVBC                 2
#define DTV_SYSTEM_DVBT_Plus_DVBC       3
#define DTV_SYSTEM_DTMB                 4
#define DTV_SYSTEM_DVBC_Plus_DTMB       5
#define DTV_SYSTEM_SBTVD                6
#define DTV_SYSTEM_ATSC                 7

#ifndef DTV_SYSTEM_SEL
#define DTV_SYSTEM_SEL                  DTV_SYSTEM_DVBT_Plus_DVBC
#endif
*/

#include "SW_Config_Default_DTV_SYSTEM.h"

//-------------------------------------------------------------------------------
// DVB System
//-------------------------------------------------------------------------------
/*
#if( DTV_SYSTEM_SEL != DTV_SYSTEM_ATSC )
#define DVB_SYSTEM
#endif

#if( DTV_SYSTEM_SEL == DTV_SYSTEM_DTMB )
    #define ENABLE_DVB_T2               DISABLE
#else
    #define ENABLE_DVB_T2               ENABLE
#endif
*/

#if( ENABLE_DVBT )
    #define ENABLE_DVB_T2       1
#endif

#if( ENABLE_DVBT && ENABLE_DVBC )
    #define DVB_T_C_DIFF_DB     1
#endif


//-------------------------------------------------------------------------------
// HW IP configuration for SW part
//-------------------------------------------------------------------------------
#define MCU_AEON_ENABLE             ENABLE
#define ENABLE_AUDIO_DEC_R2_BIN             ENABLE
#define ENABLE_AUDIO_DEC_R2_BIN_COMPRESS    ENABLE

//------------------------------------------------------------------------
//
#if(BLOADER)
    #define ENABLE_SECURITY_R2_HDCP22   0
    #define ENABLE_ATSC_TTS             DISABLE
#else
    #define ENABLE_SECURITY_R2_HDCP22   1

  #ifndef ENABLE_ATSC_TTS
    #if(MAYA_LITE)
        #define ENABLE_ATSC_TTS     DISABLE
    #elif( defined(CHAKRA3_AUTO_TEST) && (CHAKRA3_AUTO_TEST) )
        #define ENABLE_ATSC_TTS     DISABLE
    #elif(ENABLE_ATSC)
      #if(ENABLE_DVBS)
        #define ENABLE_ATSC_TTS     DISABLE
	  #elif(ENABLE_ATSC_KOR)
	    #define ENABLE_ATSC_TTS     DISABLE
      #else
        #define ENABLE_ATSC_TTS     ENABLE
      #endif
    #endif
  #endif
#endif // #if(!BLOADER)

// Upgrade HDCP key by U disk
#define ENABLE_USB_DOWNLOAD_HDCPKEY22_BIN   DISABLE

//-------------------------------------------------------------------------------
// Common DVB System
//-------------------------------------------------------------------------------

#if ( ENABLE_ATSC || ENABLE_ISDBT )
    #define TV_SYSTEM                   TV_NTSC
#else
    #define TV_SYSTEM                   TV_PAL
#endif

#if (TV_SYSTEM == TV_NTSC)
  #if(ENABLE_ATSC_KOR)
    #define AUDIO_SYSTEM_SEL            AUDIO_SYSTEM_A2
  #else
    #define AUDIO_SYSTEM_SEL            AUDIO_SYSTEM_BTSC
  #endif
#else
    #define AUDIO_SYSTEM_SEL            AUDIO_SYSTEM_A2
#endif

#define ENABLE_HDTV                     ENABLE          // Euro HDTV Spec

#if( BLOADER )
    #define ENABLE_PVR                  DISABLE
#elif (ENABLE_DTV)
  #if ENABLE_ISDBT
    #define ENABLE_PVR                  ENABLE
  #else
    #define ENABLE_PVR                  DISABLE
  #endif
#else
    #define ENABLE_PVR                  DISABLE
#endif

//-------------------------------------------------------------------------------
#define MSB123x_T2MI_DJB_RST_EN         DISABLE
#if(ENABLE_ATSC_KOR)
#ifndef KOREAN_CC_ENABLE
#define KOREAN_CC_ENABLE       ENABLE
#endif

#ifndef ENABLE_LANGUAGE_KOREA
#define ENABLE_LANGUAGE_KOREA          ENABLE
#endif
#endif


//--------- ZUI, related with Panel resolution ----------------------------------
#define UI_SKIN_SEL                     UI_SKIN_1920X1080X565//UI_SKIN_1920X1080X565

//----Zoom-----------------------------------------------------------------------
#define ENABLE_USERARC_WITH_AFD         DISABLE
#define PANEL_16_10                     DISABLE // Special panel 16:10(1440x900 or 1680x1050) not 16:9(1920x1080 or 1366x768)

//----Port-----------------------------------------------------------------------
#define INPUT_SCART_USE_SV2             DISABLE

//----HDMI-----------------------------------------------------------------------
#define ENABLE_HDMI                     ENABLE
#define ENABLE_HDMI_AUDIO_APP           ENABLE
#define ENABLE_HDMI_AR_CHECK            ENABLE
#define HDCP_KEY_TYPE                   HDCP_KEY_IN_CODE
#define HDCP22_KEY_TYPE                 HDCP22_KEY_IN_CODE            // 1044 bytes(encrypted keys)
#define HDCP22_AES_KEY_TYPE             HDCP22_AES_KEY_IN_CODE        // 16 byte(128-bit)
#define HDCP22_ALL_R2_TASK_ENABLE       ENABLE

#ifdef ENABLE_SW_CEC_WAKEUP
#undef ENABLE_SW_CEC_WAKEUP
#endif

#if defined(MIPS_CHAKRA) || defined(ARM_CHAKRA)
#define ENABLE_CEC                      ENABLE //DISABLE
#else
#define ENABLE_CEC                      ENABLE //DISABLE
#endif

#if ENABLE_CEC
#define ENABLE_CEC_INT                  ENABLE
#define ENABLE_CUST01_CEC               ENABLE
#define ENABLE_SW_CEC_WAKEUP            ENABLE
#define ENABLE_WAIT_CEC_READY           ENABLE
#else
#define ENABLE_CEC_INT                  DISABLE
#define ENABLE_CUST01_CEC               DISABLE
#define ENABLE_SW_CEC_WAKEUP            DISABLE
#define ENABLE_WAIT_CEC_READY           DISABLE
#endif

#define ENABLE_DDCCI                    ENABLE

//----EUROPEAN HDTV--------------------------------------------------------------
#if (ENABLE_HDTV == 1)
#define SUPPORT_EURO_HDTV               ENABLE
#else
#define SUPPORT_EURO_HDTV               DISABLE
#endif

//----VE-------------------------------------------------------------------------
#define ENABLE_VE                       0//ENABLE
#define ENABLE_VOP_DUPLICATE            0//ENABLE   // DTV VOP duplicate for VE, MHEG5 and Subtitle use it

// ---- Mirror ---------------------------------------------------------------------
#define MirrorEnable                    ENABLE

//----AUDIO----------------------------------------------------------------------
#define S4_AUDIO_PATH_SETTING

#ifdef S4_AUDIO_PATH_SETTING
#define Prescale_0dB                    0x6F

#define Prescale_MainSpeaker_DTV        Prescale_0dB-9
#define Prescale_LineOut_DTV            Prescale_0dB-9
#define Prescale_SifOut_DTV             Prescale_0dB-9  // Output DTV
#define Prescale_SpdifOut_DTV           0x00

#define Prescale_MainSpeaker_ATV        Prescale_0dB-5
#define Prescale_LineOut_ATV            Prescale_0dB-5
#define Prescale_SifOut_ATV             Prescale_0dB-5  // Output ATV
#define Prescale_SpdifOut_ATV           0x00

#define Prescale_MainSpeaker_AV         Prescale_0dB
#define Prescale_LineOut_AV             Prescale_0dB
#define Prescale_SifOut_AV              Prescale_0dB-5  // Output ATV
#define Prescale_SpdifOut_AV            0x00

#define Prescale_MainSpeaker_PC         Prescale_0dB
#define Prescale_LineOut_PC             Prescale_0dB
#define Prescale_SifOut_PC              Prescale_0dB-5  // Output ATV
#define Prescale_SpdifOut_PC            0x00

#define Prescale_MainSpeaker_HDMI       Prescale_0dB-9
#define Prescale_LineOut_HDMI           Prescale_0dB-9
#define Prescale_SifOut_HDMI            Prescale_0dB-5  // Output ATV
#define Prescale_SpdifOut_HDMI          0x00
#endif

#define ENABLE_AUDIO_SURROUND_DBX      DISABLE
//------Video Firmware code ---------------------------------
#if (ENABLE_HDTV == ENABLE)
    #define VIDEO_FIRMWARE_CODE         VIDEO_FIRMWARE_CODE_HD
#else
    #define VIDEO_FIRMWARE_CODE         VIDEO_FIRMWARE_CODE_SD
#endif

#define ENABLE_DYNAMIC_H264_FW_LOADING           1
#define ENABLE_DYNAMIC_MVD_FW_LOADING            1

//------Storage Applications-----------------------------------------------------
#define ENABLE_FILESYSTEM               ENABLE
#define ENABLE_N51FS                    ENABLE
#define ENABLE_JPEGSHOW                 DISABLE
#define ENABLE_MP3                      DISABLE

//------Storage Devices----------------------------------------------------
#define ENABLE_CARDREADER               DISABLE

#define ENABLE_USB                      ENABLE
#define ENABLE_USB_2                    ENABLE

#define ENABLE_NAND                     DISABLE

//----OAD------------------------------------------------------------------------
#if (ENABLE_DVB)
    #define ENABLE_OAD                  ENABLE
#else
    #define ENABLE_OAD                  DISABLE
#endif

//----MENU Config Reset----------------------------------------------------------
#define DAILEO_RESET_MANU_CONFIG        ENABLE//DISABLE

//----SW Upgrade-----------------------------------------------------------------
#define ENABLE_SW_UPGRADE               ENABLE

//---- Autotest ----------------------------------------------------------------
#if( BLOADER )
    #define ENABLE_BOOTTIME             0
#else
    #define ENABLE_BOOTTIME             0
#endif

#define ENABLE_CHCHANGETIME         DISABLE
#define ENABLE_CPU_BENCHMARK_TEST   DISABLE


//------DMP Application----------------------------------------------------------
#if ENABLE_DMP

    #define ENABLE_MPLAYER_PHOTO            ENABLE
    #define ENABLE_MPLAYER_MUSIC            ENABLE
#if(MAYA_LITE)
    #define ENABLE_MPLAYER_MOVIE            DISABLE
    #define ENABLE_MPLAYER_TEXT             DISABLE
#else
    #define ENABLE_MPLAYER_MOVIE            ENABLE
    #define ENABLE_MPLAYER_TEXT             ENABLE
#endif
#define ENABLE_MPEG2                        ENABLE
#define ENABLE_TS                           ENABLE
#define ENABLE_VDPLAYER                     ENABLE
#define ENABLE_HK_LOAD_MM_VDEC              ENABLE
#define EN_STYLE_STANDARD                   0
#define EN_STYLE_DYNAMIC                    1  // dynamic display the menu item ,need enable COMPOSER_BMP_LOADER
#define CHANNEL_ADD_AND_MERGE_FUNC          DISABLE
#define DISABLE_HD_BMPSUB                   DISABLE  // enable it to no display HD bitmap subtitle
    #define ENABLE_MPLAYER_CAPTURE_LOGO     DISABLE //enable it to store logo
    #define ENABLE_MPLAYER_CAPTURE_MUSIC    DISABLE //enable it to store music
    #define ENABLE_MPLAYER_CAPTURE_MOVIE    DISABLE //enable it to store Movie
//#define AUDIO_DSP_CODE_SEL                  AUDIO_DSP_CODE_DVB
#define ENABLE_AUDIO_NR                     ENABLE
#define ENABLE_BGM                          ENABLE //enable it to allow playing background music when photo slide show
#define ENABLE_COPY_PASTE                   DISABLE //enable it to allow copy&paste media file
#define ENABLE_POWERON_MUSIC                ENABLE // after T3 checking ok, turn on it again //enable it to play music when system boot up
#define POWERON_MUSIC_MIN_HOLD_ON_TIME      3000   //When ENABLE_POWERON_MUSIC==1, music should play at least xx ms until cancelled
#define DISPLAY_LOGO                        ENABLE  // after T3 checking ok, turn on it again //enable it to display LOGO when system boot up
#if ENABLE_MPLAYER_MOVIE
    #define ENABLE_SUBTITLE_DMP             ENABLE  //enable it to support MM subtitle
#else
    #define ENABLE_SUBTITLE_DMP             DISABLE  //enable it to support MM subtitle
#endif

  #if (ENABLE_SUBTITLE_DMP)
    #define ENABLE_INTERNAL_TS_SUBTITLE     ENABLE  //enable it need enough memory layout for subtitle decoder.(internal bmp subtitle must be enabled for TS subtitle)
    #define ENABLE_INTERNAL_BMP_SUBTITLE    ENABLE //enable it to support internal bmp subtitle
    #define ENABLE_INTERNAL_TEXT_SUBTITLE   ENABLE //enable it to support internal text subtitle
    #define ENABLE_EXTERNAL_BMP_SUBTITLE    ENABLE //enable it to support external bmp subtitle
  #else
    #define ENABLE_INTERNAL_TS_SUBTITLE     DISABLE  //enable it need enough memory layout for subtitle decoder.
    #define ENABLE_INTERNAL_BMP_SUBTITLE    DISABLE //enable it to support internal bmp subtitle
    #define ENABLE_INTERNAL_TEXT_SUBTITLE   DISABLE //enable it to support internal text subtitle
    #define ENABLE_EXTERNAL_BMP_SUBTITLE    DISABLE //enable it to support external bmp subtitle
  #endif
    #define HVD_BW_TUNING_SETTING           (0x03001446)  //for HVD BW tuning, need to fine-tine it for each project
    #define ENABLE_DIGITAL_MEDIA_API        DISABLE

    #define ENABLE_LAST_MEMORY              ENABLE
    #define ENABLE_LAST_MEMORY_STORAGE_SAVE DISABLE // save to flash/eeprom for suddently power off
    #define LAST_MEMORY_FILENUMBER          1// 8 // number of LastMemory file to be recorded

#else
    #define ENABLE_MPLAYER_PHOTO            DISABLE
    #define ENABLE_MPLAYER_MUSIC            DISABLE
    #define ENABLE_MPLAYER_MOVIE            DISABLE
    #define ENABLE_MPLAYER_TEXT             DISABLE

    #define COMPOSER_BMP_LOADER             DISABLE  //--->need to define in board_type.h
    #define CHANNEL_ADD_AND_MERGE_FUNC      DISABLE
    #define ENABLE_BGM                      DISABLE //enable it to allow playing background music when photo slide show
    #define ENABLE_POWERON_MUSIC            DISABLE //enable it to play music when system boot up
    #define DISPLAY_LOGO                    DISABLE //enable it to display LOGO when system boot up
    #define ENABLE_SUBTITLE_DMP             DISABLE  //enable it to support MM subtitle
    #define ENABLE_INTERNAL_TS_SUBTITLE     DISABLE  //enable it need enough memory layout for subtitle decoder.
    #define ENABLE_INTERNAL_BMP_SUBTITLE    DISABLE //enable it to support internal bmp subtitle
    #define ENABLE_INTERNAL_TEXT_SUBTITLE   DISABLE //enable it to support internal text subtitle
    #define ENABLE_EXTERNAL_BMP_SUBTITLE    DISABLE //enable it to support external bmp subtitle
    #define HVD_BW_TUNING_SETTING           (0)  //for HVD BW tuning, need to fine-tine it for each project
    #define ENABLE_DIGITAL_MEDIA_API        DISABLE

    #define ENABLE_LAST_MEMORY              DISABLE

#endif // #if ENABLE_DMP

//----Signal Check---------------------------------------------------------------
#define ENABLE_OFFLINE_SIGNAL_DETECTION DISABLE  // S7 has sub window but offline detect will enable source IP2F2_02[7] = 0, sub win will over-write memory

//----Enable Post Color Temp Flag------------------------------------------------
#define ENABLE_NEW_COLORTEMP_METHOD     ENABLE

//----Enable Precise Brightness Flag for Color Temp------------------------------
#define ENABLE_PRECISE_RGBBRIGHTNESS    ENABLE

//----Enable FBL Aspect Ratio Support--------------------------------------------
#define ENABLE_FBL_ASPECT_RATIO_BY_MVOP DISABLE

//----Control Backlight Function-------------------------------------------------
#define ENABLE_DLC                      ENABLE
#define ENABLE_DLC_ISR              DISABLE//ENABLE
#define ENABLE_DLC_ISR_DEBUG DISABLE

#define ENABLE_DBC                      DISABLE//ENABLE

#define MWE_FUNCTION                    ENABLE
#define ISCANENABLE                     ENABLE  // for CRT

#if ENABLE_DBC
#define DBC_YC_GAIN_CONTROL             1
#endif

#if ENABLE_DLC
#define DLC_C_GAIN_CONTROL              1
#endif

//----PM_MODE-------------------------------------------------------------------
#define PM_MODE_SELECT                  PM_MODE_DEFAULT

//----CheckSum-------------------------------------------------------------------
#define SWCHECKSUM_SWITCH               DISABLE // 0: Disable SW CheckSum, 1:Enable SW CheckSum

//----Auto ASP-------------------------------------------------------------------
#define AUTO_ASPECT_RATIO               ENABLE

//------ DataBase in NAND -----------------------------------------------------
#define DB_IN_NAND                      DISABLE

//------ DataBase in EEPROM -----------------------------------------------------
#define EEPROM_SAVE_NONE                0
#define EEPROM_SAVE_WITHOUT_CH_DB       1
#define EEPROM_SAVE_ALL                 3

#if (DB_IN_NAND)
#define EEPROM_DB_STORAGE               EEPROM_SAVE_NONE//EEPROM_SAVE_WITHOUT_CH_DB
#else
#define EEPROM_DB_STORAGE               EEPROM_SAVE_NONE//EEPROM_SAVE_WITHOUT_CH_DB
#endif

#if (EEPROM_DB_STORAGE==EEPROM_SAVE_NONE)
#define STANDBY_EEPROM_ACCESS           DISABLE
#else
#define STANDBY_EEPROM_ACCESS           ENABLE
#endif


//------ FLASH DataBase size ------------------------------------------------------
/*
#if (EEPROM_DB_STORAGE == EEPROM_SAVE_NONE)
#define  CM_DATABASE_FLASH_SIZE    FLASH_BLOCK_SIZE * 4
#elif (EEPROM_DB_STORAGE == EEPROM_SAVE_WITHOUT_CH_DB)
#define  CM_DATABASE_FLASH_SIZE    FLASH_BLOCK_SIZE * 2
#elif (EEPROM_DB_STORAGE == EEPROM_SAVE_ALL)
#define  CM_DATABASE_FLASH_SIZE    0
#endif
*/

//----EEPROM Write Protection----------------------------------------------------
#define EEPROM512_WP_ENABLE             DISABLE

//----Power Control--------------------------------------------------------------
#define POWER_CONTROL                   ENABLE

//----WatchDog-------------------------------------------------------------------
#define WATCH_DOG                       DISABLE

//----ADC GAIN CAL---------------------------------------------------------------
#define ADC_AUTO_GAIN_CABLICATION_WITHOUT_EXT_SIGNAL        ENABLE

//----MIU Protection-------------------------------------------------------------
#define MIU_PROTECT                     DISABLE

//---------ENABLE_ROBUST_FUNCTION------------------------------------------------
#define ENABLE_ROBUST_FUNCTION          DISABLE

#if (ENABLE_ROBUST_FUNCTION == ENABLE)
#define ENABLE_MVDMONITOR               ENABLE
#define ENABLE_DMXMONITOR               ENABLE
#define ENABLE_VOUTMONITOR              ENABLE
#else
#define ENABLE_MVDMONITOR               DISABLE
#define ENABLE_DMXMONITOR               DISABLE
#define ENABLE_VOUTMONITOR              DISABLE
#endif

#define ENABLE_MADMONITOR               ENABLE

//-------------------------------------------------------------------------------
// DVB Only System
//-------------------------------------------------------------------------------
#if(ENABLE_DTMB)
#define ENABLE_DTMB_CHINA_APP           ENABLE
#else
#define ENABLE_DTMB_CHINA_APP           DISABLE
#endif

#if (ENABLE_DTMB_CHINA_APP)
#define ENABLE_DTMB_ADD_FREQUENCY       TRUE     // add dtmb  570 578 586 594 602
#endif

#define ENABLE_DVBC_PLUS_DTMB_CHINA_APP DISABLE
#define ENABLE_DVB_TAIWAN_APP           DISABLE
#if ENABLE_ISDBT
#define ENABLE_SBTVD_BRAZIL_APP         ENABLE
#define ENABLE_SBTVD_BRAZIL_CM_APP      ENABLE
#else
#define ENABLE_SBTVD_BRAZIL_APP         DISABLE
#define ENABLE_SBTVD_BRAZIL_CM_APP      DISABLE
#endif

#if (ENABLE_DTV)
#define ENABLE_ATV_CHINA_APP            DISABLE
#else
#define ENABLE_ATV_CHINA_APP            ENABLE
#endif

#if( ENABLE_DVBT )
    #define MHEG5_ENABLE                DISABLE//ENABLE
#endif

#define CHINESE_SIMP_FONT_ENABLE        DISABLE

#define CHINESE_BIG5_FONT_ENABLE        DISABLE


#define MHEG5_IN_HK                     DISABLE  // MHEG5 rnning in the CP:ENABLE/HK:DISABLE
//#define NORDIG_FUNC                     DISABLE//for Nordig Spec v2.0


#if (ENABLE_DVBT || ENABLE_DVBC || ENABLE_DTMB || ENABLE_ISDBT || ENABLE_ATV_CHINA_APP) //#ifdef DVB_SYSTEM
 #ifdef AUSTRALIA
    #define ENABLE_CI                       DISABLE
    #define ENABLE_CI_PLUS                  DISABLE
 #elif ENABLE_SBTVD_BRAZIL_APP
    #define ENABLE_CI                       DISABLE
    #define ENABLE_CI_PLUS                  DISABLE
#elif ( ENABLE_DTMB_CHINA_APP || ENABLE_DVB_TAIWAN_APP || ENABLE_ATV_CHINA_APP)
    #define ENABLE_CI                       DISABLE
    #define ENABLE_CI_PLUS                  DISABLE
 #elif ENABLE_DVBC_PLUS_DTMB_CHINA_APP
    #define ENABLE_CI                       ENABLE
    #define ENABLE_CI_PLUS                  ENABLE
 #else
 //------------------------------MHEG CONFIG-------------------------------------
 #if ((ENABLE_DTV) && (!BLOADER))
    #define ENABLE_CI                   DISABLE
    #define ENABLE_CI_PLUS              DISABLE
 #else // #if (ENABLE_DTV)
    #define ENABLE_CI                   DISABLE
    #define ENABLE_CI_PLUS              DISABLE
 #endif

    //#undef NORDIG_FUNC
    //#define NORDIG_FUNC                 DISABLE//for Nordig Spec v2.0
 #endif
#else
    #define ENABLE_CI                   DISABLE
    #define ENABLE_CI_PLUS              DISABLE
#endif  //#ifdef DVB_SYSTEM


#ifdef DISABLE_SUBTITLE
    #define ENABLE_SUBTITLE         DISABLE
#else
  #if ( ENABLE_DVBT || ENABLE_DVBS || ENABLE_DVBC || ENABLE_DTMB)//Mantis fixed
    #define ENABLE_SUBTITLE         ENABLE
  #else
    #define ENABLE_SUBTITLE         DISABLE
  #endif
#endif


//------------------------------VECTOR FONT-------------------------------------
#if (  ENABLE_DTMB_CHINA_APP            \
    || ENABLE_DVB_TAIWAN_APP            \
    || ENABLE_ATV_CHINA_APP             \
    || ENABLE_DVBC_PLUS_DTMB_CHINA_APP  \
    || CHINESE_BIG5_FONT_ENABLE         \
    || CHINESE_SIMP_FONT_ENABLE         \
    || ENABLE_ATSC_KOR                  \
    )
    #define VECTOR_FONT_ENABLE              DISABLE
#else
    #define VECTOR_FONT_ENABLE              ENABLE
#endif

#if (VECTOR_FONT_ENABLE)
    #define ENABLE_ARABIC_OSD   DISABLE
    #define ENABLE_THAI_OSD     DISABLE
#endif

#ifndef ENABLE_ARABIC_OSD
#define ENABLE_ARABIC_OSD       DISABLE
#define ENABLE_THAI_OSD         DISABLE
#endif

#define ENABLE_INDIA_OSD                    DISABLE

//------------------------------VECTOR FONT-------------------------------------
#if (VECTOR_FONT_ENABLE && !MCU_AEON_ENABLE)
    #error "Vector Font functions depends on AEON mailbox"
#endif

//----MS FONT--------------------------------------------------------------------
#define MS_FONT_SIZE_TYPE           MS_FONT_NORMAL

#define HDMITX_4030_ENABLE   DISABLE

#define ENABLE_TTX                  DISABLE   //1 Needcheck

#if ENABLE_TTX
    #define ENABLE_TTX_ACI          DISABLE
#else
    #define ENABLE_TTX_ACI          DISABLE
#endif

//----EPG------------------------------------------------------------------------
#if(ENABLE_DVB)// (ENABLE_DTV)
#define ENABLE_DTV_EPG                      ENABLE
#else
#define ENABLE_DTV_EPG                      DISABLE
#endif

#define ENABLE_SCHE_EXT                     TRUE    // enable Extended Info in EPG
#define SUPPORT_PVR_CRID                    TRUE    // enable PVR DTG functions

#define ENABLE_HIERARCHY                    DISABLE

#define ENABLE_RIKS_TV                      DISABLE //for Riks TV test

#if ENABLE_DVBT
    #define ENABLE_NZ_FREEVIEW              ENABLE //for NZ Freeview DTG Test
#else
    #define ENABLE_NZ_FREEVIEW              DISABLE //for NZ Freeview DTG Test
#endif
//---- SI -----------------------------------------------------------------------
#if ENABLE_NZ_FREEVIEW
#define ENABLE_UPDATE_MULTIPLEX_VIA_NIT     ENABLE
#else
#define ENABLE_UPDATE_MULTIPLEX_VIA_NIT     DISABLE
#endif
#define ENABLE_SDT_OTHER_MONITOR            ENABLE
#define NTV_FUNCTION_ENABLE                 DISABLE
#define ENABLE_NZ_EIT_TIME_DISPLAY          ENABLE

//------------------------------------------------------------------------------
#define ENABLE_DCC                          DISABLE
#define DTV_SCAN_AUTO_FINE_TUNE_ENABLE      DISABLE

//---- Mis -----------------------------------------------------------------------
#define POWER_KEY_PAD_BY_INTERRUPT          DISABLE
#define ENABLE_ADC_BY_SOURCE                DISABLE  // Enable different ADC setting for different source, there are some issues

#define GE_BITMAP_FORMAT                    MPLAYER_BITMAP_FORMAT

// ----  PROGRAM EDITOR  -----------------------------------------------------------------------
#define PRG_EDIT_INPUT_LCN_MOVE             ENABLE
//-----------------------------------------------------------------------------------------------------------

//Config for APEngine
//** cowork with TV have to be exclusive from MHEG5.
//** AP co-existing with TTX and subtitle is not supported yet.
#if 0//def AP_COWORK
    #define AP_WITH_OSD         ENABLE
    #define AP_WITH_TTX         DISABLE
#endif


#if 0//def ENABLE_KTV
  #if (CHINESE_SIMP_FONT_ENABLE ||CHINESE_BIG5_FONT_ENABLE)
    #define DYNAMIC_VECTOR_FONT_ENABLE          DISABLE
  #else
    #define DYNAMIC_VECTOR_FONT_ENABLE          ENABLE
  #endif
#else
    #define DYNAMIC_VECTOR_FONT_ENABLE          DISABLE
#endif


//#define SUPPORT_AP_BIN_IN_FLASH_2
#ifdef SUPPORT_AP_BIN_IN_FLASH_2
//=== About SUPPORT_AP_BIN_IN_FLASH_2 Flag
//** Feature:
//   -- You can put some bin file to secondary Flash
//   -- If you only modify some bin file in flash_2, you can only update the flash_2
//   -- First bin file name = MERGE.bin Secondary = MERGE2.bin
//
//** How to enable:
//   --Step1: Enable this flag "SUPPORT_AP_BIN_IN_FLASH_2"
//   --Step2: choice the Secondary flash name "#define FLASH_2_NUM       FLASH_ID2" in the board define
//   --Step3: To set the Bin file to Flash-2 , add "-2" to BinInfo.h
//     Example: #define BIN_ID_MSB1210                  0x837   //~24KB
//              //@..\..\..\core\bin\demodulator\demod_msb1210.bin -2
//   --Step4: To add function call before Bin copy "InfoBlock_Flash_2_Checking_Start(&BinInfo);"
//   --Step5: To add function call after Bin copy " InfoBlock_Flash_2_Checking_End(&BinInfo);"

#define FLASH_2_NUM         FLASH_ID2
#endif

#define DTV_USE_FBL         DISABLE


//Config for GOP OSD use
//#define OSD_USE_GOP1            // for ONE GOP Chip
#ifdef OSD_USE_GOP1
    #define E_GOP_SLV       0   // MUTE
    #define E_GOP_APP       1   // Subtitle/MHEG5
    #define E_GOP_OSD       0
    #define E_GOP_CAP       2
#else
    #define E_GOP_SLV       0   // MUTE
    #define E_GOP_APP       1   // Subtitle/MHEG5
    #define E_GOP_OSD       0
    #define E_GOP_CAP       2
#endif


#define ENABLE_DYNAMIC_NR       ENABLE


/////////////////////////////////////////////////////////////////////////////////////////
//------------------------------FLASH_SIZE--------------------------------------
#define FLASH_SIZE_1MB              0x100000
#define FLASH_SIZE_2MB              0x200000
#define FLASH_SIZE_4MB              0x400000
#define FLASH_SIZE_8MB              0x800000
#define FLASH_SIZE_16MB             0x1000000

#define SATURN_FLASH_TYPE                   FLASH_TYPE_SERIAL
//#define SATURN_FLASH_IC                     FLASH_IC_MX25L6405D

#if(MAYA_LITE )
    #define FLASH_SIZE                      FLASH_SIZE_4MB
#else
#ifdef MHEG5_BIG5_FONT_ENABLE
    #define FLASH_SIZE                      FLASH_SIZE_16MB
#elif CHINESE_BIG5_FONT_ENABLE
    #define FLASH_SIZE                      FLASH_SIZE_8MB
#else
    #define FLASH_SIZE                      FLASH_SIZE_8MB
#endif
#endif

#if ((EEPROM_DB_STORAGE==EEPROM_SAVE_NONE) && (FLASH_SIZE >= FLASH_SIZE_8MB))
    #define ENABLE_DVBT_1000_LCN            DISABLE //ENABLE
#else
    #define ENABLE_DVBT_1000_LCN            DISABLE
#endif


/////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------
// miscellany
//-------------------------------------------------------------------------------
#define KEEP_UNUSED_FUNC            DISABLE
#define EAR_PHONE_POLLING           DISABLE
#define CM_MULTI_FAVORITE           DISABLE
#define RM_SIZE_BOOTLOADER_INIT     (0x80)

#define ENABLE_BABAO_PLAYER         DISABLE      //babao ap player interface code

// for play card
#define TS_FROM_PLAYCARD            DISABLE//ENABLE

//------Factory enable define------------------------------------------------------------------
#define ENABLE_SOUND_NONLINEAR_CURVE        0
#define ENABLE_PICTURE_NONLINEAR_CURVE      1
#define ENABLE_NONLINEAR_CURVE              1

#define ENABLE_SZ_FACTORY_OVER_SCAN_FUNCTION            ENABLE//factory overscan adjust enable usefull  //enable for DTG AFD test
#define ENABLE_SZ_DESIGN_OVER_SCAN_FUNCTION             DISABLE//design overscan adjust enable usefull
#define ENABLE_VD_PACH_IN_CHINA                         ENABLE
#define ENABLE_SHOW_PHASE_FACTORY                       ENABLE
#define ENABLE_SHOW_PHASE_DESIGN                        ENABLE
#define ENABLE_SZ_FACTORY_USB_SAVE_DATABASE_FUNCTION    DISABLE
#define ENABLE_SZ_DESIGN_USB_SAVE_DATABASE_FUNCTION     DISABLE




//-----MMS----------
#define ENABLE_KOREA_APP                DISABLE

//-----UART-----
#define ENABLE_SELECT_UART              ENABLE
#define SELECT_UART_PORT                1           //0: OFF, 1: HK, 2:COPROC, 3: VDEC

// If you want turn on this, you need
// 1.Update the  ZUI_bitmap_SW_LOAD.bin
// 2.Confirm the BMP_TMP_BUFFER_OFFSET / BMP_TMP_BUFFER_SIZE  / BMP_TMP_LZMA_TEMP_BUFFER_SIZE  3 parameters
#define SW_LOAD_BMP_ON_DEMAND           ENABLE//DISABLE

#if (BLOADER)
    #undef ENABLE_SUBTITLE
    #define ENABLE_SUBTITLE             DISABLE

    #undef ENABLE_TTX
    #define ENABLE_TTX                  DISABLE

    #define ENABLE_BL_UI                ENABLE
    #define ENABLE_BL_OAD_SCAN          ENABLE

#else

#endif //(BLOADER)

#if( MAYA_LITE || BLOADER)
    #define ENABLE_3D_PROCESS           DISABLE
#else
    #define ENABLE_3D_PROCESS           ENABLE
#endif


//#define DEFAULT_3D_BEHAVIOR_SEL     _EN_3D_BEHAVIOR_IDX_IN8903_Simple_//EN_3D_BEHAVIOR_IDX_IN8903_Simple
//#define ENABLE_TCON_IN8903_PROCESS           ENABLE
#define ENABLE_MFC_6M20                             DISABLE
#define ENABLE_MFC_6M30                             DISABLE
#define CONFIG_3D_HWLVDSLRFLAG                      DISABLE
#define ENABLE_E_POP                                DISABLE

#define ENABLE_PANEL_3D_ONOFF_CTRLBY6M30            DISABLE

#define ENABLE_UI_3D_PROCESS                        DISABLE
#define ENABLE_MAINPAGE_EFFECT                      DISABLE
#define ENABLE_MPO_SUPPORT                          DISABLE

#define ENABLE_LCN_CONFLICT                         ENABLE
#define ENABLE_TARGET_REGION                        ENABLE

#define ENABLE_UPGRADE_CIPLUSKEY_BY_USB             DISABLE
#define ENABLE_UPGRADE_HDCPKEY_BY_USB               DISABLE

#if(ENABLE_DTV_EPG)
#define ENABLE_EPGTIMER_RECORDER_TURNOFFPANEL       ENABLE
#endif

#define SUBTITLE_DIFF_MHEG5                         ENABLE




#define ENABLE_KEY_LOGGER               ENABLE

#define ENABLE_DESIGN_POWER_ON_MODE     ENABLE
#define ENABLE_FACTORY_POWER_ON_MODE    ENABLE

#define ENABLE_AUDIO_SURROUND_VDS       DISABLE //ENABLE
#define ENABLE_AUDIO_SURROUND_VSPK      DISABLE  // ENABLE
#define ENABLE_AUDIO_SURROUND_SRS       ENABLE
#define ENABLE_AUDIO_SURROUND_BBE       DISABLE //ENABLE
#define ENABLE_AUDIO_SURROUND_ADVANCE   (ENABLE_AUDIO_SURROUND_VSPK== ENABLE || ENABLE_AUDIO_SURROUND_SRS==ENABLE || ENABLE_AUDIO_SURROUND_BBE==ENABLE )

//******************************************************************************

#if (ENABLE_ATSC)

#define ENABLE_ATSC_EPG_DB_2016         1
#if(ENABLE_ATSC_EPG_DB_2016)

  #if 0 // multi channel , 7 day
    #define NEW_MAX_TAB_NUM     56
    #define ATSC_EPG_ONLY_CUR_CHANNEL   DISABLE
  #else // one channel one day
    #define NEW_MAX_TAB_NUM     8
    #define ATSC_EPG_ONLY_CUR_CHANNEL   ENABLE
  #endif
#endif

#include "SW_Config_Trunk_Atsc.h"

#endif

#if ENABLE_SBTVD_BRAZIL_APP
  #ifdef CUSTOMER_FOR_UI_CC_708_608_APPEARING
    #undef  CUSTOMER_FOR_UI_CC_708_608_APPEARING
    #define CUSTOMER_FOR_UI_CC_708_608_APPEARING    DISABLE
  #else
    #define CUSTOMER_FOR_UI_CC_708_608_APPEARING    DISABLE
  #endif
#endif


//======================================================================

#ifndef LD_DEMO
    #define LD_DEMO  0
#endif

#if( LD_DEMO )
    #define LD_ENABLE   1
#else
    #define LD_ENABLE   0
#endif

#if(LD_ENABLE)
    #define LED_DEVICE_SEL  LED_DEVICE_AS3820_2X7//LED_DEVICE_INX_65INCH_2X8

    #if(ENABLE_ATSC_TTS)
        #undef ENABLE_ATSC_TTS
        #define ENABLE_ATSC_TTS 0
    #endif
#endif


//******************************************************************************

#define ENABLE_PQ_TABTYPE_XVYCC DISABLE

#endif // #ifndef _SW_CONFIG_TRUNK_MILAN_128M_DVBT_PLUS_DVBC_H_

