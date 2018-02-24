
#ifndef _SW_CONFIG_TRUNK_ATSC_H_
#define _SW_CONFIG_TRUNK_ATSC_H_



//-------------------------------------------------------------------------------
// ATSC System
//-------------------------------------------------------------------------------

#if (MEMORY_MAP > MMAP_32MB)
#ifndef ENABLE_HVD_MMVIDEO
#define ENABLE_HVD_MMVIDEO                   ENABLE
#endif
#endif

#define ENABLE_TVSCANSTEPTIME           DISABLE
#define ENABLE_TVSCANQAMTIME            DISABLE
#define ENABLE_TVSCAN_DEBUGINFO         ENABLE
#define ENABLE_CPU_BENCHMARK_TEST       DISABLE

#if ENABLE_ATSC_KOR

#define ENABLE_EASMONITOR               DISABLE
#define KOR_HIDE_3D_CHANNEL             ENABLE

#else

#define ENABLE_EASMONITOR               ENABLE
#define KOR_HIDE_3D_CHANNEL             DISABLE

#endif

#ifndef ENABLE_LANGUAGE_KOREA
#define ENABLE_LANGUAGE_KOREA           DISABLE
#endif

#define ENABLE_DTV_MPEG_AUDIO           ENABLE
#define ENABLE_AC3P_AUDIO               ENABLE



//----Super Password-------------------------------------------------------------
#define SUPER_PASSWORD                  99999


//----Scaling & PQ---------------------------------------------------------------
#define ENABLE_NON_LINEAR_SCALING       ENABLE

//----SCAN SERIVCE TYPE ---------------------------------------------------------
#define FTA_ONLY                        0
#define FTA_AND_SCRAMBLE                1
#define FTA_AND_HIDE_SCRAMBLE           3

//----UI Function Define---------------------------------------------------------
#define ENABLE_DIGITAL_KEY_EXCEPT_ANYTV                 ENABLE//enable message box display timing
#define ENABLE_SCALEMODE_BY_SOURCE                      DISABLE// Seperate scaler mode Setting by Source.
#define COUNTDOWN_OSD_ENABLE                            ENABLE
#define MTS_MONITOR_BY_HOUSEKEEPING                     DISABLE //for mts auto monitor
#define ENABLE_AUDIO_LANGUAGE_HOT_KEY                   DISABLE    //enable audio language hotkey
#define ENABLE_MESSAGE_BOX_DISPLAY_TIMING               DISABLE//enable message box display timing
#define CLEAR_MUTE_ICON_BY_SPECIAL_KEY                  DISABLE
#define ENABLE_EXTERN_DTV_MAX_MINOR_NO                  ENABLE
#define ENABLE_COLOR_TYPE_FOLLOW_PIC_MODE               DISABLE
#define ENABLE_DISPLIST_FAVLIST_MENU_DIRECT_SWITCH      ENABLE//DISABLE
#define POWER_COUNTER_DOWN_OSD_OFFSET                   0ul
#define ENABLE_VOLUME_PROGRESSBAR_CHANGE_COLOR          DISABLE
#define ENABLE_NONDUPLICATE_PROGRAM_NAME                DISABLE
#define ENABLE_ADD_FAKECHANNEL_WITH_NO_SERVICES         ENABLE
#define ENABLE_DATACHECK                                DISABLE//
#define ENABLE_COLORSETTING_BY_SOURCE                   ENABLE//DISABLE
#define ENABLE_VOL_INC_DEC_UNCHAIN_AMP_MUTE             ENABLE//enable message box display timing
#define SCALE_MODE_KEEP_NORMAL_ITSELF                   ENABLE
#define USER_DLC_MODE                                   ENABLE
#define ENABLE_GAMMA                                    ENABLE
#define ENABLE_RRT5_UPDATE_BY_LATEST_VERSION            ENABLE //rrt table updated by newer version and keep current option when version change
#define RRT_UPDATE_BY_VERSION_NUMBER_CHANGED	        DISABLE //rrt table updated by version number changed. disable this define will compare other rrt field, if be changed will be updated.

//#define COLOR_TEMP_DISPLAY100                           DISABLE

//------------------------------SW Feature MACROS-----------------------------------
#define STORE_RD_CH_ENABLE                  ENABLE   //0=TV only , 1=TV + RD
#define STORE_CH_TYPE                       FTA_ONLY //FTA_AND_HIDE_SCRAMBLE //FTA_ONLY
#define SHOW_CHANNEL_SCRAMBLE_INFO          ENABLE
#define SCAN_NTSC_SIGNAL_ONLY               ENABLE //DISABLE
#define ENABLE_8VSBSCAN_IN_CABLE            DISABLE
#define ASSIGN_NTSC_PROGRAM_AS_DEFAULT_CH   DISABLE
//1. ATV force NTSC 2. Refine Audio spdif mute  3. Move Channel change to TV state 4. Do not save database during CH change
#define ENABLE_ATV_CHANNEL_CHANGE_FINETUNING  ENABLE

#define ENABLE_WIZARD_MODE                  ENABLE
#define KEEP_MUTE_ICON                      DISABLE
#define STORE_RD_CH_ENABLE                  ENABLE   //0=TV only , 1=TV + RD

#define NTSC_FREQ_OFFSET_LEFT               -2100   //KHz
#define NTSC_FREQ_OFFSET_RIGHT              2000    //KHz
#define NTSC_FREQ_OFFSET_RIGHT_CH5CH6       2300    //KHz
#define VD_FREQ_OFFSET_LEFT_RANGE           500     //KHz
#define VD_FREQ_OFFSET_RIGHT_RANGE          500    //KHz, 1500
#define VIF_COVERAGE_BOUNDRY_LEFT           -550 //KHz
#define VIF_COVERAGE_BOUNDRY_RIGHT          550 //KHz

#define PARSING_CC_FONTEDGE                 ENABLE    // 1 for adding Font EDGE functions and menu
#define TS_THROUGH_LVDS                     DISABLE
#define ENABLE_UNRATED_LOCK                 ENABLE
#define ONE_PART_CHNO                       ENABLE

#define ENABLE_AUDIO_ONLY_FULL_FEATURE      DISABLE
#define ENABLE_AUDIO_ONLY_CUSTOMERMODE      ENABLE
#define EN_INPUT_LABEL_EDIT                 ENABLE   //DISABLE // if Enable EN_INPUT_LABLE_EDIT, Plese Enable ENABLE_AUDIO_ONLY_CUSTOMERMODE first.
#define EN_INPUT_LABEL_CUSTOM_EDIT          DISABLE  //enable custom input label
#define OSD_TRANSPARENCY_PER25              ENABLE
#define ENABLE_PARENTAL_BLOCK_MASK_KEY      DISABLE
#define POWER_KEY_PAD_BY_INTERRUPT          DISABLE
#define ENABLE_DCR                          DISABLE
#ifndef SEARCH_CABLE_ATV_DTV_TOGETHER
#define SEARCH_CABLE_ATV_DTV_TOGETHER       ENABLE   //scan ATV and DTV both at every RF channel when auto scan
#endif
#define SEARCH_DTV_ATV_TOGETHER_DTV_FIRST       DISABLE
#define ENABLE_VCHIP_ALL_AS_AGEBASED            DISABLE
#define ENABLE_AUDIOBYPASS                      DISABLE

#define NEW_VCHIP
#define ENABLE_MEXICO_VCHIP                     ENABLE
#define ENABLE_PARSE_SAME_DIMENSION_IN_RRT5_CAD ENABLE


#ifndef ENABLE_ATSC_EPG_DB_2016
#define ENABLE_ATSC_EPG_DB_2016      0
#endif

#if( ENABLE_ATSC_EPG_DB_2016 )
    #define ENABLE_MAX_RRT_DIMENSION_NUMBER     DISABLE
#elif ((MEMORY_MAP < MMAP_64MB))
    #define ENABLE_MAX_RRT_DIMENSION_NUMBER     DISABLE
#else
    #define ENABLE_MAX_RRT_DIMENSION_NUMBER     ENABLE
#endif

//#define ENABLE_HW_INTERNAL_ADC_CALIBRATION      DISABLE
#define ENABLE_DTV_NOSIGNAL_THRESHOLD           DISABLE
#define ENABLE_VDEC_AVSYNC_REPEAT               ENABLE //enable slow motion when video freeze and av sync not ready after channel channel
#define ENABLE_DTV_ZIGZAG                       ENABLE   //dtv auto search between std/irc/hrc
#define ENABLE_NEW_QAM_SCAN                     DISABLE //when qam lock at one freq, keep the same settings to all the other freq

#if ((MEMORY_MAP >= MMAP_64MB) && (FLASH_SIZE >= FLASH_SIZE_4MB))
#define ENABLE_PAT_MUTISECTION      ENABLE //PAT muti-sections
#else
#define ENABLE_PAT_MUTISECTION      DISABLE //PAT muti-sections
#endif

#ifndef KOREAN_CC_ENABLE
#define KOREAN_CC_ENABLE            DISABLE
#endif


#define CUSTOMER_FOR_UI_CC_708_608_APPEARING DISABLE

  // for play card
#define TS_FROM_PLAYCARD                    DISABLE

// for OSD rotate effect
//#define ENABLE_MAINPAGE_EFFECT              DISABLE

// ---- HDMI 4K*2K ---------------------------------------------------------------------
  //-----MMS----------
//#define ENABLE_MMS                  DISABLE
//-----UART-----


//NeedCheck, if these compile option have to open or not?
#define ENABLE_QUICK_DATABASE                    DISABLE
#define ASSIGN_NTSC_PROGRAM_AS_DEFAULT_CH        DISABLE
#define ENABLE_NEW_QAM_SCAN                      DISABLE
//----SCAN SERIVCE TYPE ---------------------------------------------------------
#define FTA_ONLY                                0
#define FTA_AND_SCRAMBLE                        1
#define FTA_AND_HIDE_SCRAMBLE                   3

#define STORE_CH_TYPE                               FTA_ONLY //FTA_AND_HIDE_SCRAMBLE //FTA_ONLY
#define ENABLE_TVSCANSTEPTIME                       DISABLE
#define SEARCH_DTV_ATV_TOGETHER_DTV_FIRST           DISABLE
#define ENABLE_8VSBSCAN_IN_CABLE                    DISABLE
#define ENABLE_TVSCANSTEPTIME                       DISABLE
#define TS_THROUGH_LVDS                             DISABLE
//#define ENABLE_ADD_FAKECHANNEL_WITH_NO_SERVICES     DISABLE


#define ENABLE_ATSC_1000_CHANNEL                    0//ENABLE

//*************************************** Merge ATSC UI ***************************************//
#define ENABLE_ATSC_EPG_UI                      ENABLE
#define ENABLE_ATSC_MENU_UI                     ENABLE
#define ENABLE_ATSC_INSTALLGUIDE                ENABLE
#define ENABLE_ATSC_SCAN_NEW_MODE               DISABLE//AutoTuning:AirDTV->AirATV->CableDTV->CableATV ManuTuning:Add UI
#if ENABLE_ATSC_SCAN_NEW_MODE
#define ENABLE_ATSC_CHLIST_DISP_TOGETHER        ENABLE//Air/Cable Display in One ChannelList
#else
#define ENABLE_ATSC_CHLIST_DISP_TOGETHER        DISABLE
#endif

#if ENABLE_ATSC_MENU_UI
#define ENABLE_ATSC_MAIN_MENU_CHANNEL_PAGE      ENABLE
#define ENABLE_ATSC_MAIN_MENU_PICTURE_PAGE      ENABLE
#define ENABLE_ATSC_MAIN_MENU_SOUND_PAGE        ENABLE
#define ENABLE_ATSC_MAIN_MENU_TIME_PAGE         ENABLE
#define ENABLE_ATSC_MENU_LOCK_UI                ENABLE
#define ENABLE_ATSC_MENU_OPTION_UI              ENABLE

#else
#define ENABLE_ATSC_MAIN_MENU_CHANNEL_PAGE      DISABLE
#define ENABLE_ATSC_MAIN_MENU_PICTURE_PAGE      DISABLE
#define ENABLE_ATSC_MAIN_MENU_SOUND_PAGE        DISABLE
#define ENABLE_ATSC_MENU_LOCK_UI                DISABLE
#define ENABLE_ATSC_MENU_OPTION_UI              DISABLE

#endif

#define ENABLE_UI_SPDIF_SETTING                 ENABLE

#ifndef ENABLE_LANGUAGE_KOREA
#define ENABLE_LANGUAGE_KOREA                   DISABLE
#endif

#define ENABLE_INPUT_LOCK                       ENABLE

#define ENABLE_TTSTEST_FROM_USB                 DISABLE //DISABLE //ENABLE

#define ENABLE_VCHIP_REGION5                    ENABLE
#define CHECK_KEY_WHILE_SCAN                    DISABLE


#if(ENABLE_ATSC_EPG_DB_2016)

  #ifndef ATSC_EPG_ONLY_CUR_CHANNEL
    #define ATSC_EPG_ONLY_CUR_CHANNEL   ENABLE
  #endif

  #ifndef NEW_MAX_TAB_NUM
    #define NEW_MAX_TAB_NUM             8 // 8 Eit table per one day
  #endif

#else

    #undef ATSC_EPG_ONLY_CUR_CHANNEL
    #define ATSC_EPG_ONLY_CUR_CHANNEL   ENABLE

#endif // ENABLE_ATSC_EPG_DB_2016

//===========================================================================

#define ENABLE_ATSC_VIDEO_DESC      1

//===========================================================================
#endif //_SW_CONFIG_TRUNK_ATSC_H_

