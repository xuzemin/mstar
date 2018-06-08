
#include "ZUI_wndproc_h.inl"
#include "ZUI_MAIN_MENU_tables_h.inl"
#include "ZUI_SCREEN_SAVER_tables_h.inl"
#include "ZUI_CHANNEL_INFO_ATSC_tables_h.inl"
#include "ZUI_CHANNEL_INFO_tables_h.inl"
#include "ZUI_PROGRAM_EDIT_tables_h.inl"
#include "ZUI_DTV_MANUAL_TUNING_tables_h.inl"
#include "ZUI_ATV_MANUAL_TUNING_tables_h.inl"
#include "ZUI_AUTO_TUNING_tables_h.inl"
#include "ZUI_INPUT_SOURCE_tables_h.inl"
#include "ZUI_CHANNEL_LIST_tables_h.inl"
#include "ZUI_AUDIO_LANGUAGE_tables_h.inl"
#include "ZUI_SUBTITLE_LANGUAGE_tables_h.inl"
#include "ZUI_INSTALL_GUIDE_ATSC_tables_h.inl"
#include "ZUI_INSTALL_GUIDE_tables_h.inl"
#include "ZUI_AUDIO_VOLUME_tables_h.inl"
#include "ZUI_HOTKEY_OPTION_tables_h.inl"
#include "ZUI_MESSAGE_BOX_tables_h.inl"
#include "ZUI_EPG_tables_h.inl"
#include "ZUI_TENKEY_NUMBER_tables_h.inl"
#include "ZUI_FACTORY_MENU_tables_h.inl"
#include "ZUI_CIMMI_tables_h.inl"
#include "ZUI_PVR_tables_h.inl"
#include "ZUI_PVR_BROWSER_tables_h.inl"
#include "ZUI_CADTV_MANUAL_TUNING_tables_h.inl"
#include "ZUI_EFFECT_SETTING_tables_h.inl"
#include "ZUI_OAD_tables_h.inl"
#include "ZUI_DMP_tables_h.inl"
#include "ZUI_EXPERT_MENU_tables_h.inl"
#include "ZUI_UPGRADE_tables_h.inl"
#include "ZUI_MENU_DISHSETUP_tables_h.inl"
#include "ZUI_EPOP_tables_h.inl"
#include "ZUI_DESIGN_MENU_tables_h.inl"


typedef enum
{

    E_OSD_EMPTY,
    E_OSD_MAIN_MENU,
    E_OSD_SCREEN_SAVER,
    E_OSD_CHANNEL_INFO_ATSC,
    E_OSD_CHANNEL_INFO,
    E_OSD_PROGRAM_EDIT,
    E_OSD_DTV_MANUAL_TUNING,
    E_OSD_ATV_MANUAL_TUNING,
    E_OSD_AUTO_TUNING,
    E_OSD_INPUT_SOURCE,
    E_OSD_CHANNEL_LIST,
    E_OSD_AUDIO_LANGUAGE,
    E_OSD_SUBTITLE_LANGUAGE,
    E_OSD_INSTALL_GUIDE_ATSC,
    E_OSD_INSTALL_GUIDE,
    E_OSD_AUDIO_VOLUME,
    E_OSD_HOTKEY_OPTION,
    E_OSD_MESSAGE_BOX,
    E_OSD_EPG,
    E_OSD_TENKEY_NUMBER,
    E_OSD_FACTORY_MENU,
    E_OSD_CIMMI,
    E_OSD_PVR,
    E_OSD_PVR_BROWSER,
    E_OSD_CADTV_MANUAL_TUNING,
    E_OSD_EFFECT_SETTING,
    E_OSD_OAD,
    E_OSD_DMP,
    E_OSD_EXPERT_MENU,
    E_OSD_UPGRADE,
    E_OSD_MENU_DISHSETUP,
    E_OSD_EPOP,
    E_OSD_DESIGN_MENU,
    E_OSD_MAX,

} E_OSD_ID;

typedef enum
{

    E_TRANSEFF_IN_NONE,
    E_TRANSEFF_IN_SPREAD_OUT,
    E_TRANSEFF_IN_FADE_IN,
    E_TRANSEFF_IN_ENTER_UP,
    E_TRANSEFF_IN_ENTER_DOWN,
    E_TRANSEFF_IN_ENTER_LEFT,
    E_TRANSEFF_IN_ENTER_RIGHT,
    E_TRANSEFF_IN_ZOOM_IN,
    E_TRANSEFF_IN_MAX,

} E_TRANSEFF_IN_ID;

typedef enum
{

    E_TRANSEFF_OUT_NONE,
    E_TRANSEFF_OUT_ROLL_UP,
    E_TRANSEFF_OUT_FADE_OUT,
    E_TRANSEFF_OUT_EXIT_UP,
    E_TRANSEFF_OUT_EXIT_DOWN,
    E_TRANSEFF_OUT_EXIT_LEFT,
    E_TRANSEFF_OUT_EXIT_RIGHT,
    E_TRANSEFF_OUT_ZOOM_OUT,
    E_TRANSEFF_OUT_MAX,

} E_TRANSEFF_OUT_ID;


#define THUMBCTRL_NUM 0

#define CARDCTRL_NUM 0

#define SLIDESHOWCTRL_NUM 0

#define PLAYLISTCTRL_NUM 0

#define CLOCKCTRL_NUM 0

#define AUTOHIDECTRL_NUM 0

