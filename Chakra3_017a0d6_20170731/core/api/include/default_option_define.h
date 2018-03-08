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

#ifndef _DEFAULT_OPTION_DEFINE_H_
#define _DEFAULT_OPTION_DEFINE_H_

//******************************************************************************

#ifndef DEBUG_AUDIO_DETECT_TIME
    #define DEBUG_AUDIO_DETECT_TIME                         0
#endif

#ifndef DTV_SCAN_AUTO_FINE_TUNE_ENABLE
    #define DTV_SCAN_AUTO_FINE_TUNE_ENABLE                  0
#endif

#ifndef SPEEDUP_BRAZIL_ATV_SCAN
#define SPEEDUP_BRAZIL_ATV_SCAN             DISABLE
#endif

#ifndef CVBSOUT1_ALWAYS_OUTPUT_ATV
#define CVBSOUT1_ALWAYS_OUTPUT_ATV  0
#endif

#ifndef  Audio_ScartOut1_Mute_Control_by_APP
#define Audio_ScartOut1_Mute_Control_by_APP                 CVBSOUT1_ALWAYS_OUTPUT_ATV
#endif

/*
    This function is that user can input any frequency point when DTV manual scan
*/
#ifndef ENABLE_SZ_DTV_OFFSET_FUNCTION
    #define ENABLE_SZ_DTV_OFFSET_FUNCTION                   0
#endif

/*
    This function is that user can input any frequency point when DTV manual scan
*/
#ifndef ENABLE_SZ_DTV_ADDCH_SCAN_FUNCTION
    #define ENABLE_SZ_DTV_ADDCH_SCAN_FUNCTION               0
#endif

#ifndef ENABLE_SZ_FACTORY_PICTURE_CURVE_FUNCTION
    #define ENABLE_SZ_FACTORY_PICTURE_CURVE_FUNCTION        0
#endif

#ifndef ENABLE_SZ_FACTORY_SOUND_CURVE_FUNCTION
    #define ENABLE_SZ_FACTORY_SOUND_CURVE_FUNCTION          0
#endif

#ifndef ENABLE_SZ_FACTORY_OVER_SCAN_FUNCTION
#define ENABLE_SZ_FACTORY_OVER_SCAN_FUNCTION           0// 1
#endif

#ifndef ENABLE_SZ_NEW_FACTORY_MEMU_FUNCTION
    #define ENABLE_SZ_NEW_FACTORY_MEMU_FUNCTION             0
#endif

#ifndef ENABLE_SZ_FACTORY_SOUND_MODE_FUNCTION
    #define ENABLE_SZ_FACTORY_SOUND_MODE_FUNCTION           0
#endif

#ifndef ENABLE_SZ_FACTORY_WB_ADJUST_FUNCTION
    #define ENABLE_SZ_FACTORY_WB_ADJUST_FUNCTION            0
#endif

#ifndef ENABLE_SZ_FACTORY_OTHER_SETTING_FUNCTION
    #define ENABLE_SZ_FACTORY_OTHER_SETTING_FUNCTION        0
#endif

#ifndef ENABLE_SZ_FACTORY_USB_SAVE_DATABASE_FUNCTION
    #define ENABLE_SZ_FACTORY_USB_SAVE_DATABASE_FUNCTION    0
#endif

#ifndef ENABLE_SZ_FACTORY_OSD_BLENDING_FUNCTION
    #define ENABLE_SZ_FACTORY_OSD_BLENDING_FUNCTION         0
#endif

#ifndef ENABLE_SZ_FACTORY_SOFTWARE_UPDATE_FUNCTION
    #define ENABLE_SZ_FACTORY_SOFTWARE_UPDATE_FUNCTION      0
#endif

#ifndef ENABLE_SZ_FACTORY_EQ_BAND_FUNCTION
    #define ENABLE_SZ_FACTORY_EQ_BAND_FUNCTION              0
#endif

#ifndef ENABLE_SZ_FACTORY_YPBPR_PHASE_FUNCTION
    #define ENABLE_SZ_FACTORY_YPBPR_PHASE_FUNCTION          0
#endif

#ifndef ENABLE_SZ_HDMI_AVMUTE_TEST_FUNCTION
    #define ENABLE_SZ_HDMI_AVMUTE_TEST_FUNCTION             0
#endif

// When AspectRatio==PTP, Can't adjust sharpness
#ifndef DISABLE_ADJ_SHARPNESS_WHEN_PTP
    #define DISABLE_ADJ_SHARPNESS_WHEN_PTP                  0
#endif


#ifndef PANEL_SWAP_LVDS_POL
    #define PANEL_SWAP_LVDS_POL                             0
#endif


#ifndef ENABLE_HOTEL_MODE_FUNCTION
    #define  ENABLE_HOTEL_MODE_FUNCTION                     0
#endif

#ifndef ENABLE_SZ_BLUESCREEN_FUNCTION
    #define ENABLE_SZ_BLUESCREEN_FUNCTION                   0
#endif

#ifndef ENABLE_HIS_AMP
    #define ENABLE_HIS_AMP                                  0
#endif

// What meaning?
#ifndef ADC_AUTO_GAIN_CABLICATION_WITHOUT_EXT_SIGNAL
    #define ADC_AUTO_GAIN_CABLICATION_WITHOUT_EXT_SIGNAL    0
#endif

#ifndef ENABLE_HW_INTERNAL_ADC_CALIBRATION
    #define ENABLE_HW_INTERNAL_ADC_CALIBRATION              DISABLE
#endif

#ifndef ENABLE_CH_VOLUME_COMP
    #define ENABLE_CH_VOLUME_COMP                           0
#endif

#ifndef ENABLE_SW_CH_FREEZE_SCREEN
    #define ENABLE_SW_CH_FREEZE_SCREEN                      0
#endif

#ifndef ENABLE_CH_FORCEVIDEOSTANDARD
     #define  ENABLE_CH_FORCEVIDEOSTANDARD                  1
#endif

#ifndef ENABLE_VGA_EIA_TIMING
#define ENABLE_VGA_EIA_TIMING             1
#endif

#ifndef ENABLE_ATV_CHANGE_CHANNEL_USE_VD_FORCE_MODE
#define ENABLE_ATV_CHANGE_CHANNEL_USE_VD_FORCE_MODE 1
#endif

//=================================================================================
// -----------ATSC CC -------------//
#define NO_CC                               0   // No Closedcaption for CC608 and CC708
#define DTV_CC                              1   // CC608 and CC708
#define ATV_CC                              2   // Only CC608 on DVB
#define BRA_CC                              3  // Brazil CC have CC608 and Brazil CC

#ifndef ATSC_CC
    #define ATSC_CC                             NO_CC
#endif

#if (ATSC_CC == NO_CC)

#elif (ATSC_CC == DTV_CC)

#elif(ATSC_CC == ATV_CC)

#if ENABLE_TTX
    #define TTX_ATV_DISABLE
#endif

#elif(ATSC_CC == BRA_CC) // -----------BRAZIL CC -------------//

//#if (ENABLE_SBTVD_BRAZIL_APP)
    //#define BRAZIL_CC                           ENABLE//DISABLE
    #if ENABLE_PVR
    //#undef BRAZIL_PVR_CC
        #define BRAZIL_PVR_CC      ENABLE
    #endif

//#else
    //#define BRAZIL_CC                           DISABLE
//#endif // #if (ENABLE_SBTVD_BRAZIL_APP)

// -----------BRAZIL CC -------------//
#endif // #if (ATSC_CC == NO_CC)

//--------------------------------------------------------------
#define BRAZIL_CC   (ATSC_CC==BRA_CC)

#define ENABLE_ISDB_ATV_VCHIP  0 // not ready (ATSC_CC==BRA_CC)

#if 0//ndef BRAZIL_CC
    #define BRAZIL_CC                           DISABLE
#endif

#ifndef BRAZIL_PVR_CC
    #define BRAZIL_PVR_CC           DISABLE
#endif

//--------------------------------------------------------------
#ifndef KOREAN_CC_ENABLE
    #define KOREAN_CC_ENABLE        DISABLE
#endif

#ifndef SUPPORT_KOREAN_CC
    #define SUPPORT_KOREAN_CC       0
#endif
//--------------------------------------------------------------
#ifndef SUPPORT_INSERT_CC_TO_VE
    #define SUPPORT_INSERT_CC_TO_VE         0
#endif

//=================================================================================

#ifndef ENABLE_OFFLINE_SIGNAL_DETECTION
    #define ENABLE_OFFLINE_SIGNAL_DETECTION     0
#endif

#ifndef ENABLE_NEW_COLORTEMP_METHOD
    #define ENABLE_NEW_COLORTEMP_METHOD         0
#endif

//---------------------------------------------------------------------------------------------
#ifndef ENABLE_CEC
    #define ENABLE_CEC                          0
#endif

#ifndef ENABLE_CEC_INT
    // Already defined in apiCEC.h
    //#define ENABLE_CEC_INT                      0
#endif

#ifndef ENABLE_CUST01_CEC
    // Already defined in apiCEC.h
    //#define ENABLE_CUST01_CEC                   0
#endif

#ifndef ENABLE_SW_CEC_WAKEUP
    // Already defined in apiCEC.h
    //#define ENABLE_SW_CEC_WAKEUP                0
#endif

#ifndef ENABLE_WAKEUP_BY_CEC
  #if(ENABLE_CEC)
    #define ENABLE_WAKEUP_BY_CEC            1
  #else
    #define ENABLE_WAKEUP_BY_CEC            0
  #endif
#endif

//---------------------------------------------------------------------------------------------

//Macro comments: all below MACOR must be controlled by ENABLE_VE, it is the head gate.
//    ENABLE_MM_VE_OUTPUT---Enable MM video play output by VE
//    FORCE_ALL_OUTPUT_THROUGH_VE---Enable all input source output through VE, including AV/ATV.
//    ENABLE_OP2_TO_VE---Relative to IP to VE, this output type will output all the mainwindow display to VE, including OSD
#ifndef ENABLE_MM_VE_OUTPUT
    #define ENABLE_MM_VE_OUTPUT                 DISABLE
#endif

#ifndef FORCE_ALL_OUTPUT_THROUGH_VE
 #if ((CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON))
    #if (ENABLE_VE)
        #define FORCE_ALL_OUTPUT_THROUGH_VE     ENABLE
    #else
        #define FORCE_ALL_OUTPUT_THROUGH_VE     DISABLE
    #endif
 #else
        #define FORCE_ALL_OUTPUT_THROUGH_VE     DISABLE
 #endif
#endif //(FORCE_ALL_OUTPUT_THROUGH_VE)

#ifndef ENABLE_OP2_TO_VE
    #define ENABLE_OP2_TO_VE                    DISABLE
#endif


#ifndef ENABLE_PRECISE_RGBBRIGHTNESS
    #define ENABLE_PRECISE_RGBBRIGHTNESS        DISABLE//ENABLE
#endif

#ifndef ENABLE_FBL_ASPECT_RATIO_BY_MVOP
    #define ENABLE_FBL_ASPECT_RATIO_BY_MVOP     DISABLE//ENABLE
#endif

#ifndef ENABLE_BACKLIGHT_ADJUST
    #define ENABLE_BACKLIGHT_ADJUST             1
#endif

#ifndef BACKLIGHT_INVERSE
    #define BACKLIGHT_INVERSE               0
#endif


//------ PANEL RELATED ---------------------------------------------------------
#ifndef PANEL_PDP_10BIT
    #define PANEL_PDP_10BIT                     0
#endif

#ifndef LVDS_PN_SWAP_L
    #define LVDS_PN_SWAP_L                      0x00
#endif

#ifndef LVDS_PN_SWAP_H
    #define LVDS_PN_SWAP_H                      0x00
#endif

#ifndef PANEL_SWAP_LVDS_CH
    #define PANEL_SWAP_LVDS_CH                  0x00
#endif

#ifndef BD_LVDS_CONNECT_TYPE
    #define BD_LVDS_CONNECT_TYPE                0x00
#endif

#ifndef ENABLE_PANEL_H_MIRROR
    #define ENABLE_PANEL_H_MIRROR               0
#endif

//------ HDMI RELATED ---------------------------------------------------------
#ifndef HDCP_HPD_INVERSE
    #define HDCP_HPD_INVERSE                    ENABLE
#endif

//------ PACKAGE RELATED ---------------------------------------------------------
#ifndef SHARE_GND
    #define SHARE_GND                           ENABLE//DISABLE
#endif

//------  Board Related -----------------------------------------------------------
#ifndef SCART_ID_SEL
    #define SCART_ID_SEL                        0
#endif

#ifndef SCART2_ID_SEL
    #define SCART2_ID_SEL                       0
#endif

// ------ Demo Fine tune -----------------------------------------------------------
#ifndef ENABLE_DEMO_FINE_TUNE
    #define ENABLE_DEMO_FINE_TUNE               0
#endif

#ifndef HDMITX_4030_ENABLE
    #define HDMITX_4030_ENABLE   DISABLE
#endif
// ------ Flash control -----------------------------------------------------

#ifndef FLASH_WP_PIN_CONTROL
    #define FLASH_WP_PIN_CONTROL                DISABLE
#endif

// ATV vtotal change patch
#ifndef PATCH_FOR_V_RANGE
    #define PATCH_FOR_V_RANGE                   DISABLE
#endif

#ifndef ENABLE_ATV_MODE_SHOW_NO_SIGNAL
    #define ENABLE_ATV_MODE_SHOW_NO_SIGNAL     0
#endif

#ifndef ENABLE_TTX_SHOW_OFF_SIGNAL
    #define ENABLE_TTX_SHOW_OFF_SIGNAL            0
#endif

#ifndef ENABLE_EPGTIMER_RECORDER_TURNOFFPANEL
    #define ENABLE_EPGTIMER_RECORDER_TURNOFFPANEL            0
#endif

#ifndef ENABLE_SCART_YC_INPUT
    #define ENABLE_SCART_YC_INPUT               0
#endif

#ifndef MPEG_HD_PRE_SCAL_DOWN
     #define MPEG_HD_PRE_SCAL_DOWN    DISABLE
#endif

#ifndef ENABLE_PIU_UART1
     #define ENABLE_PIU_UART1    DISABLE
#endif

#ifndef ENABLE_FRANCE_DTV
     #define ENABLE_FRANCE_DTV         DISABLE
#endif

#ifndef ENABLE_SMOOTH_PANEL_OUTPUT
     #define ENABLE_SMOOTH_PANEL_OUTPUT    DISABLE
#endif

#ifndef ENABLE_BACKLIGHT_PWM_SYNC_WITH_FRAMERATE
     #define ENABLE_BACKLIGHT_PWM_SYNC_WITH_FRAMERATE DISABLE
#endif

#ifndef DTV_LOW_IF_FREQ
#define DTV_LOW_IF_FREQ DISABLE
#endif

#define RATIO_OF_BACKLIGHT_FREQ_OVER_FRAMERATE 2

#ifndef ENABLE_3D_PROCESS
#define ENABLE_3D_PROCESS       DISABLE
#endif

#ifndef ENABLE_UI_3D_PROCESS
#define ENABLE_UI_3D_PROCESS   DISABLE
#endif

#ifndef TXTFONT_ZOOM2X
#define TXTFONT_ZOOM2X         ENABLE
#endif

#ifndef ENABLE_NEW_AUTO_NR
#define ENABLE_NEW_AUTO_NR     ENABLE
#endif

#ifndef ENABLE_DYNAMIC_EDID
    #define ENABLE_DYNAMIC_EDID     DISABLE
#endif

#ifndef ENABLE_BIG5_TO_UNICODE
    #define ENABLE_BIG5_TO_UNICODE     DISABLE
#endif

//patch:  [Boxer].DNK/776 services 'AVCSD1', 'AVCSD2', and 'AVCSD6','AVCSD3', 'AVCSD4', and 'AVCSD5'
//Boundary line with arrows should be visible without any cut.
#ifndef ENABLE_BOXER_OVERSCAN_PATCH
  #ifndef ENABLE_RIKS_TV
        #define ENABLE_BOXER_OVERSCAN_PATCH     DISABLE//ENABLE when boxer test
  #else
    #if ENABLE_RIKS_TV
        #define ENABLE_BOXER_OVERSCAN_PATCH     ENABLE
    #else
        #define ENABLE_BOXER_OVERSCAN_PATCH     DISABLE
    #endif
  #endif
#endif

#ifndef ENABLE_ATV_AUDIOCHECK_IN_OTHER_SRC
#define ENABLE_ATV_AUDIOCHECK_IN_OTHER_SRC     ENABLE
#endif

//------------------For subtitle dispatch--------------------------------------------
#ifndef ENABLE_ZUI_BACKGROUND_PINK_SUBTITLE_PATCH
#define ENABLE_ZUI_BACKGROUND_PINK_SUBTITLE_PATCH     DISABLE//issue: subtitle not blending in mm
#endif

#ifndef ENABLE_ZUI_BACKGROUND_PINK_PATCH
#define ENABLE_ZUI_BACKGROUND_PINK_PATCH     DISABLE//issue: some OSD pictures have one pixel high pink frames
#endif



#ifndef FIXED_POWER_ON_EARPHONE_POP
    #define FIXED_POWER_ON_EARPHONE_POP     ENABLE
#endif

#ifndef ARC_SUPPORT_PORT
    #define ARC_SUPPORT_PORT                0
#endif

//MHL
#ifndef ENABLE_MHL
    #define ENABLE_MHL                      DISABLE
#endif

#if (ENABLE_MHL == ENABLE)
// To check Is MHL port defined or not. Ifndef, then show messages.
#ifndef HDMI_PORT_FOR_MHL
    #error "HDMI_PORT_FOR_MHL is not defined. Please define MHL port in your board definition."
#endif
#endif

//fixed DTV PLAY 480I@50HZ CVBS OUT has garbage in bottom.
#ifndef FIXED_480I_50HZ_CVBS_OUT_GARBAGE
  #if(ENABLE_ATSC)
    #define FIXED_480I_50HZ_CVBS_OUT_GARBAGE    DISABLE
  #else
    #define FIXED_480I_50HZ_CVBS_OUT_GARBAGE    ENABLE
  #endif
#endif

//When Work in DTV ,and scart out,switch AspectRatio,it will has garbage on sub tv.mantis 0265289
#ifndef FIXED_SCART_OUT_GARBAGE_SWITCH_AR
    #define FIXED_SCART_OUT_GARBAGE_SWITCH_AR    ENABLE
#endif

#ifndef HDMI_DVI_AUDIO_MODE_CONFIG
    #define HDMI_DVI_AUDIO_MODE_CONFIG    DISABLE
#endif
#ifndef PVR_AND_TTX_DIFF_WITH_MHEG5
    #define PVR_AND_TTX_DIFF_WITH_MHEG5    DISABLE
#endif
//When Work in 3D,switch Pic mode,it will has garbage on  tv.mantis 0267527
#ifndef FIXED_3D_SWITCH_PIC_MODE_GARBAGE
    #define FIXED_3D_SWITCH_PIC_MODE_GARBAGE    ENABLE
#endif
//Brazil project function,Skip ATV which its program num is same to DTV LCN,Avoid another project build warning
#ifndef ENABLE_SKIP_ATV_PROGRAMS_SAME_TO_DTV_LCN
    #define ENABLE_SKIP_ATV_PROGRAMS_SAME_TO_DTV_LCN    DISABLE
#endif


///COLOR RANGE AUTO SETTING
#define ENABLE_COLOR_RANGE_AUTO_SETTING                 ENABLE


// Upgrade HDCP key by U disk
#ifndef ENABLE_USB_DOWNLOAD_HDCPKEY22_BIN
    #define ENABLE_USB_DOWNLOAD_HDCPKEY22_BIN           DISABLE
#endif

#ifndef FIXED_MIRROR_HD_PANEL_UI_LOSE
//when use mirror HD PANEL and UI tranparent color do not use black,when show UI,it will lose some pixed in right
    #define FIXED_MIRROR_HD_PANEL_UI_LOSE               DISABLE
#endif

#ifndef ENABLE_MM_DIVX
    #define ENABLE_MM_DIVX          				    DISABLE
#endif

#ifndef ENABLE_POST_INIT
    #define ENABLE_POST_INIT                            DISABLE
#endif

#if(FRONTEND_TUNER_TYPE == SILAB_2158_TUNER)
    #define FIXED_SI2158_FINE_TUNE_GARBAGE              ENABLE
#else
    #define FIXED_SI2158_FINE_TUNE_GARBAGE              DISABLE
#endif

#ifndef DTV_COUNT_DOWN_TIMER_PATCH
    #define DTV_COUNT_DOWN_TIMER_PATCH                  DISABLE
#endif

#if(MEMORY_MAP <= MMAP_64MB)
    #define ENABLE_TIMESHIT                             DISABLE
    #define ENABLE_OSD_SUBTITLE_EXCLUSIVE               ENABLE
#else
    #define ENABLE_TIMESHIT                             ENABLE
    #define ENABLE_OSD_SUBTITLE_EXCLUSIVE               DISABLE
#endif

#ifndef ENABLE_UI_LANGUAGE_RUSSIAN
    #define ENABLE_UI_LANGUAGE_RUSSIAN                     DISABLE
#endif

#ifndef PIP_SIZE_WITH_BLACKSCREEN
    #define PIP_SIZE_WITH_BLACKSCREEN                   ENABLE
#endif

#ifndef ENABLE_DTV_CHCEK_USB_DELAY_2S
    #define ENABLE_DTV_CHCEK_USB_DELAY_2S               DISABLE
#endif

#ifndef CHLIST_DISABLE_SI_AUTO_UPDATA
    #define CHLIST_DISABLE_SI_AUTO_UPDATA               DISABLE
#endif

#ifndef ENABLE_ISDB_DOUBLE_RF_INPUT
    #define ENABLE_ISDB_DOUBLE_RF_INPUT                 DISABLE
#endif


#ifndef ENABLE_MSTAR_MAIN_FUNCTION_STATE_MACHINE
 // #if (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD)
    #define ENABLE_MSTAR_MAIN_FUNCTION_STATE_MACHINE    ENABLE
 // #else
 //   #define ENABLE_MSTAR_MAIN_FUNCTION_STATE_MACHINE    DISABLE
 // #endif
#endif


#ifndef ENABLE_SUPPORT_MM_PHOTO_4K_2K
    #define ENABLE_SUPPORT_MM_PHOTO_4K_2K       DISABLE
#endif

#ifndef ENABLE_FileIn_PMTMonitor
	#define ENABLE_FileIn_PMTMonitor  DISABLE
#endif



#ifndef ENABLE_CHECK_SPDIF_MUTE_STATUS
    #define ENABLE_CHECK_SPDIF_MUTE_STATUS FALSE
#endif

#ifndef ENABLE_SAVE_SQI
#define ENABLE_SAVE_SQI                 TRUE
#endif


//-------------------------------------------------------------------------


#ifndef ENABLE_KEY_LOGGER
    #define ENABLE_KEY_LOGGER       DISABLE
#endif


//-------------------------------------------------------------------------
#ifndef ENABLE_ATSC_AD_FUNC
#if ((CHIP_FAMILY_TYPE == CHIP_FAMILY_WHISKY) &&(MEMORY_MAP >= MMAP_64MB))
    #define ENABLE_ATSC_AD_FUNC DISABLE
#else
    #define ENABLE_ATSC_AD_FUNC ENABLE
#endif
#endif

//-------------------------------------------------------------------------
#ifndef ENABLE_AD_DISABLE_MAINAUDIO
#define ENABLE_AD_DISABLE_MAINAUDIO DISABLE
#endif


#ifndef ENABLE_DECOMP7_USE_HK_MEMORY
  #if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)  \
     ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) \
     ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN)   \
     ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA)   \
     ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_WHISKY) \
     ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MELODY) \
     ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA) \
     )
    #define ENABLE_DECOMP7_USE_HK_MEMORY    TRUE
  #else
    #define ENABLE_DECOMP7_USE_HK_MEMORY    FALSE
  #endif
#endif

//-------------------------------------------------------------------------
#ifndef ENABLE_OAD_DATA_SAVE_TO_DB_CH
  #if(( CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN ) \
      ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) \
     )
    #define ENABLE_OAD_DATA_SAVE_TO_DB_CH   FALSE//TRUE
  #else
    #define ENABLE_OAD_DATA_SAVE_TO_DB_CH   FALSE
  #endif
#endif

#ifndef DB_PC_MODE_SAVE_TO_DB_GEN
    #if(( CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN )   \
        ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON)  \
        )
        #define DB_PC_MODE_SAVE_TO_DB_GEN      1
    #else
        #define DB_PC_MODE_SAVE_TO_DB_GEN      0
    #endif
#endif


#ifndef ENABLE_MHL_NO_OVERSCAN
    #define ENABLE_MHL_NO_OVERSCAN  ENABLE
#endif

//-------------------------------------------------------------------------
// Certification
//-------------------------------------------------------------------------
#ifndef ENABLE_EWS
    #define ENABLE_EWS                              DISABLE
#endif

#ifndef ENABLE_SOUTHEAST_ASIA_CERTIFICATION
    #define ENABLE_SOUTHEAST_ASIA_CERTIFICATION     DISABLE
#endif


//-------------------------------------------------------------------------
#ifndef FRONTEND_SECOND_DEMOD_TYPE
#define FRONTEND_SECOND_DEMOD_TYPE      MSTAR_NONE_DEMOD
#endif
//-------------------------------------------------------------------------

#ifndef ENABLE_DTMB_ADD_FREQUENCY
#define ENABLE_DTMB_ADD_FREQUENCY    FALSE
#endif


#ifndef DEFAULT_3D_BEHAVIOR_SEL
    #define DEFAULT_3D_BEHAVIOR_SEL     _EN_3D_BEHAVIOR_IDX_All_Passive_
#endif

#ifndef ENABLE_EXTERN_DTV_MAX_MINOR_NO
    #define ENABLE_EXTERN_DTV_MAX_MINOR_NO      0
#endif

#ifndef ENABLE_COUNTRY_GHANA
    #define ENABLE_COUNTRY_GHANA DISABLE
#endif

#ifndef ENABLE_COUNTRY_SINGAPORE
    #define ENABLE_COUNTRY_SINGAPORE DISABLE
#endif

#ifndef ENABLE_COUNTRY_VIETNAM
    #define ENABLE_COUNTRY_VIETNAM DISABLE
#endif

#ifndef ENABLE_COUNTRY_KENYA
    #define ENABLE_COUNTRY_KENYA DISABLE
#endif

#ifndef ENABLE_COUNTRY_MYANMAR
    #define ENABLE_COUNTRY_MYANMAR DISABLE
#endif

#ifndef ENABLE_COUNTRY_ICELANDIC
    #define ENABLE_COUNTRY_ICELANDIC DISABLE
#endif  //ENABLE_COUNTRY_ICELANDIC

#ifndef ENABLE_FORCE_PRESET_PASSWORD
    #define ENABLE_FORCE_PRESET_PASSWORD DISABLE
#endif  //ENABLE_FORCE_PRESET_PASSWORD

#ifndef ENABLE_CANAL_READY_CIPLUS_AUTH
    #define ENABLE_CANAL_READY_CIPLUS_AUTH DISABLE
#endif

#ifndef ENABLE_RIKS_TV_IRD_SETTING
    #define ENABLE_RIKS_TV_IRD_SETTING DISABLE
#endif

#ifndef ENABLE_UNITY_MEDIA_SETTING
    #define ENABLE_UNITY_MEDIA_SETTING DISABLE
#endif

#ifndef ENABLE_CABLE_READY_SETTING
    #define ENABLE_CABLE_READY_SETTING DISABLE
#endif

#ifndef ENABLE_GAME_BG_MUSIC
    #define ENABLE_GAME_BG_MUSIC DISABLE
#endif

#ifndef ENABLE_SOUNDTEST_MUSIC_LOOP
    #define ENABLE_SOUNDTEST_MUSIC_LOOP              DISABLE//DISABLE
#endif

#ifndef ENABLE_SCART_SVIDEO
    #define ENABLE_SCART_SVIDEO     DISABLE
#endif

#ifndef ENABLE_AUDIO_SURROUND_DBX
    #define ENABLE_AUDIO_SURROUND_DBX     DISABLE
#endif

#ifndef ENABLE_EASMONITOR
    #define ENABLE_EASMONITOR     DISABLE
#endif

//When Plug out  SCART connecter, next source is preious source//manits 0975584
#ifndef ENABLE_SCARTIN_PRESOURCE
    #define ENABLE_SCARTIN_PRESOURCE     DISABLE
#endif


#ifndef ENABLE_32M_H264
#define ENABLE_32M_H264     DISABLE
#endif

#ifndef ENABLE_WAIT_CEC_READY
    #define ENABLE_WAIT_CEC_READY           DISABLE
#endif

//******************************************************************************

#ifndef ENABLE_STANDBY_STATE_MACHINE
    #define ENABLE_STANDBY_STATE_MACHINE    ENABLE
#endif

//******************************************************************************

#ifndef AV_SYNC_ADJUST
    #define AV_SYNC_ADJUST    DISABLE//DISABLE//ENABLE
#endif

#ifndef ENABLE_FM_RADIO
    #define ENABLE_FM_RADIO DISABLE
#endif

#ifndef ENABLE_MxL661_GPO
#define ENABLE_MxL661_GPO   DISABLE
#endif

//******************************************************************************

#ifndef ENABLE_IR_BIN
#define ENABLE_IR_BIN                   DISABLE
#endif

///////////////////////////////////////////////
// CustomerType
///////////////////////////////////////////////
//Mst
//#define CustomerType_Mst_Urania             0x01 //
//#define CustomerType_Mst_Ubike              0xB0
//#define CustomerType                        CustomerType_Mst_Ubike

#define LD_CUSTOMER_MSTAR   0
#define LD_CUSTOMER_SEL     LD_CUSTOMER_MSTAR


#ifndef LD_ENABLE
    #define LD_ENABLE                       0
#endif

#ifndef LED_MULTI_SUPPORT_ENABLE
    #define LED_MULTI_SUPPORT_ENABLE        0
#endif

#ifndef ENABLE_TWO_SPI
    #define ENABLE_TWO_SPI                  0
#endif

#ifndef ENABLE_FOUR_SPI
    #define ENABLE_FOUR_SPI                 0
#endif

#ifndef ENABLE_LDMA_MSPI_DONE_INT
    #define ENABLE_LDMA_MSPI_DONE_INT       0
#endif

#ifndef ENABLE_SSPI_DRIVER
    #define ENABLE_SSPI_DRIVER              DISABLE
#endif

#ifndef LED_DEVICE_SEL
    #define LED_DEVICE_SEL          LED_DEVICE_NONE
#endif

#define CUR_CPU_IS_SEC_R2       0
#define LD_ALGO_RUN_IN_CROP     1
#define LD_ALGO_ENABLE          (!LD_ALGO_RUN_IN_CROP)
//================================================================

#ifndef ENABLE_ATSC_ATV_ONLY_NTSC
    #define ENABLE_ATSC_ATV_ONLY_NTSC   (ENABLE_ATSC)
#endif
//================================================================

#ifndef ENABLE_BOOT_SPEED_UP
    #define ENABLE_BOOT_SPEED_UP    0
#endif

//================================================================

#ifndef ENABLE_MPLAYER_CAPTURE_LOGO
    #define ENABLE_MPLAYER_CAPTURE_LOGO     DISABLE
#endif

//================================================================

#ifndef ENABLE_POWER_SAVING_DPMS_DVI
#define ENABLE_POWER_SAVING_DPMS_DVI    0
#endif

#ifndef GAME_BOXMAN
#define GAME_BOXMAN    DISABLE
#endif

#ifndef GAME_GOBANG
#define GAME_GOBANG    DISABLE
#endif

#ifndef GAME_SNAKE
#define GAME_SNAKE    DISABLE
#endif

#ifndef GAME_SUDOKU
#define GAME_SUDOKU    DISABLE
#endif

#ifndef GAME_TETRIS
#define GAME_TETRIS    DISABLE
#endif

#ifndef GAME_MINES
#define GAME_MINES    DISABLE
#endif

#ifndef GAME_SHOT
#define GAME_SHOT      DISABLE
#endif

#ifndef GAME_ENABLE
#define GAME_ENABLE     (GAME_BOXMAN|GAME_GOBANG|GAME_SNAKE|GAME_SUDOKU|GAME_TETRIS|GAME_MINES|GAME_SHOT)
#endif

//============================================================================

#ifndef ENABLE_KEY_TO_SPEECH
#define ENABLE_KEY_TO_SPEECH   DISABLE // for melody only // support 960x540xI8 and 1366x768x565
#endif

//============================================================================

#ifndef ENABLE_CONSOLE_CMD
    #define ENABLE_CONSOLE_CMD  0
#endif

//support BinManager Tool
#ifndef SUPPORT_BIN_MANAGER
#define SUPPORT_BIN_MANAGER    DISABLE 
#endif


//******************************************************************************
//
#endif //#ifndef _DEFAULT_OPTION_DEFINE_H_

