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

#ifndef _SW_CONFIG_TRUNK_NASA_64_DTMB_H_
#define _SW_CONFIG_TRUNK_NASA_64_DTMB_H_


#define SW_CONFIG_NAME              "SW_CONFIG_TRUNK_NASA_64_DTMB"

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

#define DTV_SYSTEM_SEL                  DTV_SYSTEM_DTMB

//-------------------------------------------------------------------------------
// DVB System
//-------------------------------------------------------------------------------
#define DVB_SYSTEM

#if (DTV_SYSTEM_SEL== DTV_SYSTEM_DVBC || DTV_SYSTEM_SEL== DTV_SYSTEM_DVBT_Plus_DVBC)
#define DVB_C_ENABLE                    ENABLE
#else
#define DVB_C_ENABLE                    DISABLE
#endif
*/
#include "SW_Config_Default_DTV_SYSTEM.h"

#define DVB_T_C_DIFF_DB                 DISABLE //ENABLE // DVB-T and C use different two DB

#define ENABLE_T_C_CHANNEL_MIX      DISABLE

//-------------------------------------------------------------------------------
// HW IP configuration for SW part
//-------------------------------------------------------------------------------
#define MCU_AEON_ENABLE             ENABLE


//-------------------------------------------------------------------------------
// Common DVB System
//-------------------------------------------------------------------------------
#define TV_SYSTEM                   TV_PAL
#define AUDIO_SYSTEM_SEL            AUDIO_SYSTEM_A2
#define ENABLE_HDTV                 ENABLE


#define ENABLE_6M40_4KX2K_PROCESS       DISABLE// 6M40  Controll
#define ENABLE_6M50_4KX2K_PROCESS       DISABLE// 6M50  Controll ,ENBALE 6M50,MUST ENBALE 6M40,because use same driver.
#define ENABLE_UI_3D_PROCESS            DISABLE

#define ENABLE_MM_DIVX                  DISABLE

#if(MS_SW_CUS_SEL == SW_CONFIG_TRUNK_NASA_64M_DTMB_SZ)
    #if(ENABLE_UI_3D_PROCESS)
    #define ENABLE_MM_HD_FB 		DISABLE	// HD MM FB
    #elif(ENABLE_MM_DIVX)
    #define ENABLE_MM_HD_FB 		DISABLE // HD MM FB
	#else
    #define ENABLE_MM_HD_FB         ENABLE  // HD MM FB
    #endif

    #define DTV_USE_FBL             DISABLE // DTV FB
    #define ENABLE_PVR              DISABLE // PVR Closed

#else

    #define ENABLE_MM_HD_FB         DISABLE
    #define DTV_USE_FBL             ENABLE

    // For speed up boot time, disable PVR
    #define ENABLE_PVR              DISABLE//ENABLE
#endif

//-------------------------------------------------------------------------------

#define MSB123x_T2MI_DJB_RST_EN     DISABLE
#define ENABLE_DVB_T2               DISABLE


//--------- ZUI, related with Panel resolution ----------------------------------
#ifdef ENABLE_TCON_OVERDRIVE
#define UI_SKIN_SEL                 UI_SKIN_960X540XI8
#define ENABLE_OVERDRIVE            1
#else
#define UI_SKIN_SEL                 UI_SKIN_1366X768X565
#endif


//----Zoom-----------------------------------------------------------------------
#define ENABLE_USERARC_WITH_AFD         DISABLE//ENABLE
#define PANEL_16_10                     DISABLE // Special panel 16:10(1440x900 or 1680x1050) not 16:9(1920x1080 or 1366x768)

//----Port-----------------------------------------------------------------------
#define INPUT_SCART_USE_SV2             DISABLE

//----HDMI-----------------------------------------------------------------------
#define ENABLE_HDMI                     ENABLE
#define ENABLE_HDMI_AUDIO_APP           ENABLE
#define ENABLE_HDMI_AR_CHECK            ENABLE
#define HDCP_KEY_TYPE                   HDCP_KEY_IN_CODE  //HDCP_KEY_IN_CODE
#ifdef ENABLE_SW_CEC_WAKEUP
#undef ENABLE_SW_CEC_WAKEUP
#endif

#define ENABLE_CEC                      ENABLE //DISABLE

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
//#define ENABLE_VE                       ENABLE   // remove to xx.mk
#define ENABLE_VOP_DUPLICATE            ENABLE   // DTV VOP duplicate for VE, MHEG5 and Subtitle use it

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
#define ENABLE_N51FS                     ENABLE
#define ENABLE_JPEGSHOW                 DISABLE
#define ENABLE_MP3                      DISABLE
//------Storage Devices----------------------------------------------------
#define ENABLE_CARDREADER               DISABLE

#define ENABLE_USB                      ENABLE
#define ENABLE_USB_2                    ENABLE

#define ENABLE_NAND                     DISABLE

//----OAD------------------------------------------------------------------------
#if (ENABLE_DTV)
    #define ENABLE_OAD                      DISABLE
#else
    #define ENABLE_OAD                      DISABLE
#endif

//----MENU Config Reset----------------------------------------------------------
#define DAILEO_RESET_MANU_CONFIG      ENABLE//DISABLE

//----SW Upgrade-----------------------------------------------------------------
#define ENABLE_SW_UPGRADE               ENABLE

//---- Autotest ----------------------------------------------------------------

#define ENABLE_BOOTTIME             DISABLE
#define ENABLE_CHCHANGETIME         DISABLE
#define ENABLE_CPU_BENCHMARK_TEST  DISABLE


//------DMP Application----------------------------------------------------------
#if ENABLE_DMP

    #define ENABLE_MPLAYER_PHOTO            ENABLE
    #define ENABLE_MPLAYER_MUSIC            ENABLE
    #define ENABLE_MPLAYER_MOVIE            ENABLE
    #define ENABLE_MPLAYER_TEXT             ENABLE

    #define ENABLE_MPEG2                    ENABLE
    #define ENABLE_TS                       ENABLE
    #define ENABLE_VDPLAYER                 ENABLE
    #define EN_STYLE_STANDARD               0
    #define EN_STYLE_DYNAMIC                1  // dynamic display the menu item ,need enable COMPOSER_BMP_LOADER
    #define CHANNEL_ADD_AND_MERGE_FUNC      DISABLE
    #define DISABLE_HD_BMPSUB               DISABLE // enable it to no display HD bitmap subtitle
    #define ENABLE_MPLAYER_CAPTURE_LOGO     DISABLE //enable it to store logo
    #define ENABLE_MPLAYER_CAPTURE_MUSIC    DISABLE //enable it to store music
    #define ENABLE_MPLAYER_CAPTURE_MOVIE    DISABLE //enable it to store Movie
    #define AUDIO_DSP_CODE_SEL              AUDIO_DSP_CODE_DVB
    #define ENABLE_AUDIO_NR                 ENABLE
    #define ENABLE_BGM                      ENABLE //enable it to allow playing background music when photo slide show
    #define ENABLE_COPY_PASTE               DISABLE //enable it to allow copy&paste media file
    #define ENABLE_POWERON_MUSIC            ENABLE // after T3 checking ok, turn on it again //enable it to play music when system boot up
    #define POWERON_MUSIC_MIN_HOLD_ON_TIME  3000   //When ENABLE_POWERON_MUSIC==1, music should play at least xx ms until cancelled
    #define DISPLAY_LOGO                    ENABLE  // after T3 checking ok, turn on it again //enable it to display LOGO when system boot up
#if ENABLE_MPLAYER_MOVIE
    #define ENABLE_SUBTITLE_DMP             ENABLE  //enable it to support MM subtitle
#else
    #define ENABLE_SUBTITLE_DMP             DISABLE  //enable it to support MM subtitle
#endif
  #if (ENABLE_SUBTITLE_DMP)
    #if(ENABLE_MM_HD_FB)
    #define ENABLE_INTERNAL_TS_SUBTITLE     DISABLE//enable it need enough memory layout for subtitle decoder.(internal bmp subtitle must be enabled for TS subtitle)
    #define ENABLE_INTERNAL_BMP_SUBTITLE    ENABLE //enable it to support internal bmp subtitle
    #define ENABLE_INTERNAL_TEXT_SUBTITLE   ENABLE //enable it to support internal text subtitle
    #define ENABLE_EXTERNAL_BMP_SUBTITLE    ENABLE //enable it to support external bmp subtitle
    #else
    #define ENABLE_INTERNAL_TS_SUBTITLE     DISABLE //enable it need enough memory layout for subtitle decoder.(internal bmp subtitle must be enabled for TS subtitle)
    #define ENABLE_INTERNAL_BMP_SUBTITLE    ENABLE //enable it to support internal bmp subtitle
    #define ENABLE_INTERNAL_TEXT_SUBTITLE   ENABLE //enable it to support internal text subtitle
    #define ENABLE_EXTERNAL_BMP_SUBTITLE    ENABLE //enable it to support external bmp subtitle
    #endif
  #else
    #define ENABLE_INTERNAL_TS_SUBTITLE     DISABLE //enable it need enough memory layout for subtitle decoder.
    #define ENABLE_INTERNAL_BMP_SUBTITLE    DISABLE //enable it to support internal bmp subtitle
    #define ENABLE_INTERNAL_TEXT_SUBTITLE   DISABLE //enable it to support internal text subtitle
    #define ENABLE_EXTERNAL_BMP_SUBTITLE    DISABLE //enable it to support external bmp subtitle
  #endif
    #define HVD_BW_TUNING_SETTING           (0x03001446)  //for HVD BW tuning, need to fine-tine it for each project
    #define ENABLE_DIGITAL_MEDIA_API        DISABLE

    //LastMemory
    #define ENABLE_LAST_MEMORY                              ENABLE
    #define ENABLE_LAST_MEMORY_STORAGE_SAVE                 DISABLE // save to flash/eeprom for suddently power off
    #define LAST_MEMORY_FILENUMBER                          1// 8 // number of LastMemory file to be recorded

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

    //LastMemory
    #define ENABLE_LAST_MEMORY              DISABLE

#endif

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
#define PM_MODE_SELECT                          PM_MODE_STANBY//PM_MODE_DEEPSLEEP

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
#if (EEPROM_DB_STORAGE == EEPROM_SAVE_NONE)
#define  CM_DATABASE_FLASH_SIZE    FLASH_BLOCK_SIZE * 4
#elif (EEPROM_DB_STORAGE == EEPROM_SAVE_WITHOUT_CH_DB)
#define  CM_DATABASE_FLASH_SIZE    FLASH_BLOCK_SIZE * 2
#elif (EEPROM_DB_STORAGE == EEPROM_SAVE_ALL)
#define  CM_DATABASE_FLASH_SIZE    0
#endif

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
#define ENABLE_ATV_CHINA_APP            DISABLE
#define ENABLE_DTMB_CHINA_APP           ENABLE
#define ENABLE_DVBC_PLUS_DTMB_CHINA_APP DISABLE
#define ENABLE_DVB_TAIWAN_APP           DISABLE
#define ENABLE_SBTVD_BRAZIL_APP         DISABLE
#define ENABLE_SBTVD_BRAZIL_CM_APP      DISABLE

#define ENABLE_DTMB_ADD_FREQUENCY       TRUE     // add 570 578 586 594 602

#define MHEG5_ENABLE                    DISABLE

#if ( ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP)
#define CHINESE_SIMP_FONT_ENABLE     ENABLE
#define CHINESE_BIG5_FONT_ENABLE     DISABLE
#else
#define CHINESE_SIMP_FONT_ENABLE     DISABLE
#define CHINESE_BIG5_FONT_ENABLE     0//ENABLE
#endif


#define MHEG5_IN_HK                     DISABLE  // MHEG5 rnning in the CP:ENABLE/HK:DISABLE
#define NORDIG_FUNC                     DISABLE//for Nordig Spec v2.0

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
#if (ENABLE_DTV)
    #ifdef ENABLE_MHEG5 // def it by project in FILES_xxxx.mk
    #ifdef  MHEG5_ENABLE
    #undef  MHEG5_ENABLE
    #endif
    #define MHEG5_ENABLE                    DISABLE
    //#define MHEG5_BIG5_FONT_ENABLE
    #endif
#endif  //#if (ENABLE_DTV)


#if ((ENABLE_DTV) && (!BLOADER))
#define ENABLE_CI                       DISABLE//ENABLE
#define ENABLE_CI_PLUS                  DISABLE//ENABLE
#else // #if (ENABLE_DTV)
#define ENABLE_CI                       DISABLE
#define ENABLE_CI_PLUS                  DISABLE
#endif

#undef NORDIG_FUNC
#define NORDIG_FUNC                     ENABLE//for Nordig Spec v2.0
#endif

#endif  //#ifdef DVB_SYSTEM


#ifdef DISABLE_SUBTITLE
    #define ENABLE_SUBTITLE DISABLE
#else
 #if (ENABLE_DVB)
    #define ENABLE_SUBTITLE ENABLE
 #else
    #define ENABLE_SUBTITLE DISABLE
 #endif
#endif

#define ENABLE_SAVE_MULTILINGUAL_SERVICE_NAME     ENABLE

//------------------------------VECTOR FONT-------------------------------------
#if ( ENABLE_DTMB_CHINA_APP || ENABLE_DVB_TAIWAN_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP ||CHINESE_BIG5_FONT_ENABLE||CHINESE_SIMP_FONT_ENABLE)
#define VECTOR_FONT_ENABLE              DISABLE
#else
#define VECTOR_FONT_ENABLE              ENABLE
#endif

#if (VECTOR_FONT_ENABLE)
    #define ENABLE_ARABIC_OSD   DISABLE
    #define ENABLE_THAI_OSD     DISABLE
#endif

#ifndef ENABLE_ARABIC_OSD
#define ENABLE_ARABIC_OSD DISABLE
#define ENABLE_THAI_OSD DISABLE
#endif

#define ENABLE_INDIA_OSD                    DISABLE

//------------------------------VECTOR FONT-------------------------------------
#if (VECTOR_FONT_ENABLE && !MCU_AEON_ENABLE)
    #error "Vector Font functions depends on AEON mailbox"
#endif

//----MS FONT--------------------------------------------------------------------
#define MS_FONT_SIZE_TYPE               MS_FONT_NORMAL

#if (ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_SBTVD_BRAZIL_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP)
    #define ENABLE_TTX                  DISABLE
#else
    #define ENABLE_TTX                  DISABLE
#endif

#if ENABLE_TTX
    #define ENABLE_TTX_ACI              DISABLE
#else
    #define ENABLE_TTX_ACI              DISABLE
#endif

//----EPG------------------------------------------------------------------------
#if (ENABLE_DTV)
#define ENABLE_DTV_EPG                      ENABLE
#else
#define ENABLE_DTV_EPG                      DISABLE
#endif

#define ENABLE_SCHE_EXT                     FALSE //TRUE    // enable Extended Info in EPG
#define SUPPORT_PVR_CRID                    FALSE // enable PVR DTG functions

#define ENABLE_HIERARCHY                    DISABLE

#define ENABLE_RIKS_TV                  DISABLE     //for Riks TV test

//---- SI -----------------------------------------------------------------------

#define ENABLE_UPDATE_MULTIPLEX_VIA_NIT     DISABLE
#define NTV_FUNCTION_ENABLE                 DISABLE

#define ENABLE_SDT_OTHER_MONITOR            DISABLE
#define ENABLE_NZ_EIT_TIME_DISPLAY          DISABLE
//------------------------------------------------------------------------------

#define ENABLE_DCC                          DISABLE
#define DTV_SCAN_AUTO_FINE_TUNE_ENABLE      DISABLE
//---- Mis -----------------------------------------------------------------------
#define POWER_KEY_PAD_BY_INTERRUPT          DISABLE
#define ENABLE_ADC_BY_SOURCE                DISABLE  // Enable different ADC setting for different source, there are some issues

#define GE_BITMAP_FORMAT MPLAYER_BITMAP_FORMAT

// ----  PROGRAM EDITOR  -----------------------------------------------------------------------
#define PRG_EDIT_INPUT_LCN_MOVE         ENABLE
//-----------------------------------------------------------------------------------------------------------

//Config for APEngine
//** cowork with TV have to be exclusive from MHEG5.
//** AP co-existing with TTX and subtitle is not supported yet.
#ifdef AP_COWORK
#define AP_WITH_OSD     1
#define AP_WITH_TTX     0
#endif


#ifdef ENABLE_KTV
#if (CHINESE_SIMP_FONT_ENABLE ||CHINESE_BIG5_FONT_ENABLE)
#define DYNAMIC_VECTOR_FONT_ENABLE              0
#else
#define DYNAMIC_VECTOR_FONT_ENABLE              1
#endif
#else
#define DYNAMIC_VECTOR_FONT_ENABLE  0
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

#define FLASH_2_NUM       FLASH_ID2
#endif


//#define H264_SETMAXTICK
#ifdef AP_COWORK
//#define ENABLE_LOAD_APP_FROM_USB
#endif


//Config for GOP OSD use
//#define OSD_USE_GOP1            // for ONE GOP Chip
#ifdef OSD_USE_GOP1
    #define E_GOP_SLV       0   // MUTE
    #define E_GOP_APP       0   // Subtitle/MHEG5
    #define E_GOP_OSD       0
    #define E_GOP_CAP       0
#else
    #define E_GOP_SLV       0   // MUTE
    #define E_GOP_APP       1   // Subtitle/MHEG5
    #define E_GOP_OSD       0
    #define E_GOP_CAP       2
#endif


#define ENABLE_DYNAMIC_NR   1

/////////////////////////////////////////////////////////////////////////////////////////
#define FLASH_SIZE_1MB          0x100000
#define FLASH_SIZE_2MB          0x200000
#define FLASH_SIZE_4MB          0x400000
#define FLASH_SIZE_8MB          0x800000
#define FLASH_SIZE_16MB         0x1000000

#define ENABLE_DUAL_DATABASE            1

#define SATURN_FLASH_TYPE               FLASH_TYPE_SERIAL
#define SATURN_FLASH_IC                 FLASH_IC_MX25L6405D
#ifdef MHEG5_BIG5_FONT_ENABLE
#define FLASH_SIZE                      FLASH_SIZE_16MB
#elif CHINESE_BIG5_FONT_ENABLE
#define FLASH_SIZE                      FLASH_SIZE_8MB
#else
#define FLASH_SIZE                      FLASH_SIZE_8MB
#endif
#if ((EEPROM_DB_STORAGE==EEPROM_SAVE_NONE) && (FLASH_SIZE >= FLASH_SIZE_8MB))
#define ENABLE_DVBT_1000_LCN            DISABLE
#else
#define ENABLE_DVBT_1000_LCN            DISABLE
#endif
#if(ENABLE_DVBT_1000_LCN == ENABLE)
#define DVB_T_C_DIFF_DB                 DISABLE  //DISABLE // DVB-T and C use different two DB
#else
#define DVB_T_C_DIFF_DB                 DISABLE //DISABLE // DVB-T and C use different two DB
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
#define ENABLE_SOUND_NONLINEAR_CURVE        ENABLE
#define ENABLE_PICTURE_NONLINEAR_CURVE      ENABLE
#define ENABLE_NONLINEAR_CURVE              ENABLE

#define ENABLE_SZ_FACTORY_OVER_SCAN_FUNCTION    DISABLE //factory overscan adjust enable usefull
#define ENABLE_SZ_DESIGN_OVER_SCAN_FUNCTION     DISABLE //design overscan adjust enable usefull
#define ENABLE_VD_PACH_IN_CHINA                      ENABLE // DISABLE
#define ENABLE_SHOW_PHASE_FACTORY         ENABLE
#define ENABLE_SHOW_PHASE_DESIGN         ENABLE
#define ENABLE_SZ_FACTORY_USB_SAVE_DATABASE_FUNCTION    DISABLE
#define ENABLE_SZ_DESIGN_USB_SAVE_DATABASE_FUNCTION    DISABLE
#define ENABLE_FACTORY_POWER_ON_MODE           DISABLE// ENABLE//DISABLE//ENABLE
#define ENABLE_DESIGN_POWER_ON_MODE           DISABLE// ENABLE//DISABLE//ENABLE


//-----MMS----------
#define ENABLE_KOREA_APP                DISABLE
//-----UART-----
#define ENABLE_SELECT_UART      ENABLE
#define SELECT_UART_PORT            1           //0: OFF, 1: HK, 2:COPROC, 3: VDEC

// If you want turn on this, you need
// 1.Update the  ZUI_bitmap_SW_LOAD.bin
// 2.Confirm the BMP_TMP_BUFFER_OFFSET / BMP_TMP_BUFFER_SIZE  / BMP_TMP_LZMA_TEMP_BUFFER_SIZE  3 parameters
#define SW_LOAD_BMP_ON_DEMAND       1

#if (BLOADER)
#undef ENABLE_SUBTITLE
#define ENABLE_SUBTITLE                       DISABLE
#undef ENABLE_TTX
#define ENABLE_TTX                            DISABLE
#define ENABLE_BL_UI                          ENABLE
#define ENABLE_BL_OAD_SCAN                    DISABLE //ENABLE
#endif //(BLOADER)


#define ENABLE_3D_PROCESS                               DISABLE
#define ENABLE_MFC_6M20                                 0
#define ENABLE_MFC_6M30                                 0
#define ENABLE_E_POP                                    DISABLE

#define ENABLE_MAINPAGE_EFFECT                          DISABLE
#define ENABLE_MPO_SUPPORT                              1
#define SCART_ID1_SAR_CHAN                              KEYPAD_ADC_CHANNEL_8 //set invalid channel
#define SCART_ID2_SAR_CHAN                              0xFF //set invalid channel
#define ENABLE_LCN_CONFLICT                             DISABLE//ENABLE
#define ENABLE_TARGET_REGION                            DISABLE
#define ENABLE_UPGRADE_CIPLUSKEY_BY_USB                 DISABLE
#define ENABLE_UPGRADE_HDCPKEY_BY_USB                   DISABLE
#define ENABLE_EPGTIMER_RECORDER_TURNOFFPANEL           DISABLE
#define SUBTITLE_DIFF_MHEG5                             DISABLE

#define ENABLE_OD_BIN           1

//#define ENABLE_OVERDRIVE        0

#define ENABLE_KEY_LOGGER                   DISABLE //Disable key logger function because Nasa code size is already tight

#define ENABLE_AUDIO_SURROUND_VDS       DISABLE //ENABLE
#define ENABLE_AUDIO_SURROUND_VSPK      DISABLE  // ENABLE
#define ENABLE_AUDIO_SURROUND_SRS       ENABLE
#define ENABLE_AUDIO_SURROUND_BBE       DISABLE //ENABLE
#define ENABLE_AUDIO_SURROUND_ADVANCE   (ENABLE_AUDIO_SURROUND_VSPK== ENABLE || ENABLE_AUDIO_SURROUND_SRS==ENABLE || ENABLE_AUDIO_SURROUND_BBE==ENABLE )

#endif // _SW_CONFIG_TRUNK_DVBT_H_
