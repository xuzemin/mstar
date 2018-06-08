
#include "ZUI_MAIN_MENU_tables_c.inl"
#include "ZUI_MAIN_MENU_alphatable_c.inl"
#include "ZUI_SCREEN_SAVER_tables_c.inl"
#include "ZUI_SCREEN_SAVER_alphatable_c.inl"
#include "ZUI_CHANNEL_INFO_tables_c.inl"
#include "ZUI_CHANNEL_INFO_alphatable_c.inl"
#include "ZUI_PROGRAM_EDIT_tables_c.inl"
#include "ZUI_PROGRAM_EDIT_alphatable_c.inl"
//#include "ZUI_DTV_MANUAL_TUNING_tables_c.inl"
//#include "ZUI_DTV_MANUAL_TUNING_alphatable_c.inl"
#include "ZUI_ATV_MANUAL_TUNING_tables_c.inl"
#include "ZUI_ATV_MANUAL_TUNING_alphatable_c.inl"
#include "ZUI_AUTO_TUNING_tables_c.inl"
#include "ZUI_AUTO_TUNING_alphatable_c.inl"
#include "ZUI_INPUT_SOURCE_tables_c.inl"
#include "ZUI_INPUT_SOURCE_alphatable_c.inl"
#include "ZUI_CHANNEL_LIST_tables_c.inl"
#include "ZUI_CHANNEL_LIST_alphatable_c.inl"
#include "ZUI_AUDIO_LANGUAGE_tables_c.inl"
#include "ZUI_AUDIO_LANGUAGE_alphatable_c.inl"
#include "ZUI_SUBTITLE_LANGUAGE_tables_c.inl"
#include "ZUI_SUBTITLE_LANGUAGE_alphatable_c.inl"
#include "ZUI_INSTALL_GUIDE_tables_c.inl"
#include "ZUI_INSTALL_GUIDE_alphatable_c.inl"
#include "ZUI_AUDIO_VOLUME_tables_c.inl"
#include "ZUI_AUDIO_VOLUME_alphatable_c.inl"
#include "ZUI_HOTKEY_OPTION_tables_c.inl"
#include "ZUI_HOTKEY_OPTION_alphatable_c.inl"
#include "ZUI_MESSAGE_BOX_tables_c.inl"
#include "ZUI_MESSAGE_BOX_alphatable_c.inl"
//#include "ZUI_EPG_tables_c.inl"
//#include "ZUI_EPG_alphatable_c.inl"
#include "ZUI_TENKEY_NUMBER_tables_c.inl"
#include "ZUI_TENKEY_NUMBER_alphatable_c.inl"
#include "ZUI_FACTORY_MENU_tables_c.inl"
#include "ZUI_FACTORY_MENU_alphatable_c.inl"
//#include "ZUI_CIMMI_tables_c.inl"
//#include "ZUI_CIMMI_alphatable_c.inl"
//#include "ZUI_KTV_MAIN_tables_c.inl"
//#include "ZUI_KTV_MAIN_alphatable_c.inl"
//#include "ZUI_PVR_tables_c.inl"
//#include "ZUI_PVR_alphatable_c.inl"
//#include "ZUI_PVR_BROWSER_tables_c.inl"
//#include "ZUI_PVR_BROWSER_alphatable_c.inl"
//#include "ZUI_CADTV_MANUAL_TUNING_tables_c.inl"
//#include "ZUI_CADTV_MANUAL_TUNING_alphatable_c.inl"
//#include "ZUI_GAME_BROWSER_tables_c.inl"
//#include "ZUI_GAME_BROWSER_alphatable_c.inl"
#include "ZUI_EFFECT_SETTING_tables_c.inl"
#include "ZUI_EFFECT_SETTING_alphatable_c.inl"
//#include "ZUI_OAD_tables_c.inl"
//#include "ZUI_OAD_alphatable_c.inl"
#include "ZUI_DMP_tables_c.inl"
#include "ZUI_DMP_alphatable_c.inl"
#include "ZUI_EXPERT_MENU_tables_c.inl"
#include "ZUI_EXPERT_MENU_alphatable_c.inl"
#include "ZUI_DESIGN_MENU_tables_c.inl"
#include "ZUI_DESIGN_MENU_alphatable_c.inl"



OSDPAGETABLE code OsdTables [] =
{
    { 0, NULL,
         //NULL,
         NULL,
         NULL,
         0, 0, 0, 0, 0, TRUE, 0, TRUE,
         CLRKEY_LO_R, CLRKEY_LO_G, CLRKEY_LO_B, CLRKEY_HI_R, CLRKEY_HI_G, CLRKEY_HI_B,
         0 },
    {HWND_MAIN_MENU_MAX, _GUI_WindowList_Zui_Main_Menu,
         //_GUI_WindowsDrawStyleList_Zui_Main_Menu,
         _GUI_WindowsAlphaList_Zui_Main_Menu,
         NULL,
         E_OSD_GWIN0, ZUI_MAIN_MENU_XSTART, ZUI_MAIN_MENU_YSTART, ZUI_MAIN_MENU_WIDTH, ZUI_MAIN_MENU_HEIGHT, 0, 44, 1,
         CLRKEY_LO_R, CLRKEY_LO_G, CLRKEY_LO_B, CLRKEY_HI_R, CLRKEY_HI_G, CLRKEY_HI_B,
         0 },
    {HWND_SCREEN_SAVER_MAX, _GUI_WindowList_Zui_Screen_Saver,
         //_GUI_WindowsDrawStyleList_Zui_Screen_Saver,
         _GUI_WindowsAlphaList_Zui_Screen_Saver,
         NULL,
         E_OSD_GWIN0, ZUI_SCREEN_SAVER_XSTART, ZUI_SCREEN_SAVER_YSTART, ZUI_SCREEN_SAVER_WIDTH, ZUI_SCREEN_SAVER_HEIGHT, 0, 56, 1,
         CLRKEY_LO_R, CLRKEY_LO_G, CLRKEY_LO_B, CLRKEY_HI_R, CLRKEY_HI_G, CLRKEY_HI_B,
         0 },
    {HWND_CHANNEL_INFO_MAX, _GUI_WindowList_Zui_Channel_Info,
         //_GUI_WindowsDrawStyleList_Zui_Channel_Info,
         _GUI_WindowsAlphaList_Zui_Channel_Info,
         NULL,
         E_OSD_GWIN0, ZUI_CHANNEL_INFO_XSTART, ZUI_CHANNEL_INFO_YSTART, ZUI_CHANNEL_INFO_WIDTH, ZUI_CHANNEL_INFO_HEIGHT, 0, 56, 1,
         CLRKEY_LO_R, CLRKEY_LO_G, CLRKEY_LO_B, CLRKEY_HI_R, CLRKEY_HI_G, CLRKEY_HI_B,
         0 },
    {HWND_PROGRAM_EDIT_MAX, _GUI_WindowList_Zui_Program_Edit,
         //_GUI_WindowsDrawStyleList_Zui_Program_Edit,
         _GUI_WindowsAlphaList_Zui_Program_Edit,
         NULL,
         E_OSD_GWIN0, ZUI_PROGRAM_EDIT_XSTART, ZUI_PROGRAM_EDIT_YSTART, ZUI_PROGRAM_EDIT_WIDTH, ZUI_PROGRAM_EDIT_HEIGHT, 0, 56, 1,
         CLRKEY_LO_R, CLRKEY_LO_G, CLRKEY_LO_B, CLRKEY_HI_R, CLRKEY_HI_G, CLRKEY_HI_B,
         0 },
/*         
    {HWND_DTV_MANUAL_TUNING_MAX, _GUI_WindowList_Zui_Dtv_Manual_Tuning,
         //_GUI_WindowsDrawStyleList_Zui_Dtv_Manual_Tuning,
         _GUI_WindowsAlphaList_Zui_Dtv_Manual_Tuning,
         NULL,
         E_OSD_GWIN0, ZUI_DTV_MANUAL_TUNING_XSTART, ZUI_DTV_MANUAL_TUNING_YSTART, ZUI_DTV_MANUAL_TUNING_WIDTH, ZUI_DTV_MANUAL_TUNING_HEIGHT, 0, 56, 1,
         CLRKEY_LO_R, CLRKEY_LO_G, CLRKEY_LO_B, CLRKEY_HI_R, CLRKEY_HI_G, CLRKEY_HI_B,
         0 },
*/         
    {HWND_ATV_MANUAL_TUNING_MAX, _GUI_WindowList_Zui_Atv_Manual_Tuning,
         //_GUI_WindowsDrawStyleList_Zui_Atv_Manual_Tuning,
         _GUI_WindowsAlphaList_Zui_Atv_Manual_Tuning,
         NULL,
         E_OSD_GWIN0, ZUI_ATV_MANUAL_TUNING_XSTART, ZUI_ATV_MANUAL_TUNING_YSTART, ZUI_ATV_MANUAL_TUNING_WIDTH, ZUI_ATV_MANUAL_TUNING_HEIGHT, 0, 56, 1,
         CLRKEY_LO_R, CLRKEY_LO_G, CLRKEY_LO_B, CLRKEY_HI_R, CLRKEY_HI_G, CLRKEY_HI_B,
         0 },
    {HWND_AUTO_TUNING_MAX, _GUI_WindowList_Zui_Auto_Tuning,
         //_GUI_WindowsDrawStyleList_Zui_Auto_Tuning,
         _GUI_WindowsAlphaList_Zui_Auto_Tuning,
         NULL,
         E_OSD_GWIN0, ZUI_AUTO_TUNING_XSTART, ZUI_AUTO_TUNING_YSTART, ZUI_AUTO_TUNING_WIDTH, ZUI_AUTO_TUNING_HEIGHT, 0, 56, 1,
         CLRKEY_LO_R, CLRKEY_LO_G, CLRKEY_LO_B, CLRKEY_HI_R, CLRKEY_HI_G, CLRKEY_HI_B,
         0 },
    {HWND_INPUT_SOURCE_MAX, _GUI_WindowList_Zui_Input_Source,
         //_GUI_WindowsDrawStyleList_Zui_Input_Source,
         _GUI_WindowsAlphaList_Zui_Input_Source,
         NULL,
         E_OSD_GWIN0, ZUI_INPUT_SOURCE_XSTART, ZUI_INPUT_SOURCE_YSTART, ZUI_INPUT_SOURCE_WIDTH, ZUI_INPUT_SOURCE_HEIGHT, 0, 56, 1,
         CLRKEY_LO_R, CLRKEY_LO_G, CLRKEY_LO_B, CLRKEY_HI_R, CLRKEY_HI_G, CLRKEY_HI_B,
         0 },
    {HWND_CHANNEL_LIST_MAX, _GUI_WindowList_Zui_Channel_List,
         //_GUI_WindowsDrawStyleList_Zui_Channel_List,
         _GUI_WindowsAlphaList_Zui_Channel_List,
         NULL,
         E_OSD_GWIN0, ZUI_CHANNEL_LIST_XSTART, ZUI_CHANNEL_LIST_YSTART, ZUI_CHANNEL_LIST_WIDTH, ZUI_CHANNEL_LIST_HEIGHT, 0, 56, 1,
         CLRKEY_LO_R, CLRKEY_LO_G, CLRKEY_LO_B, CLRKEY_HI_R, CLRKEY_HI_G, CLRKEY_HI_B,
         0 },
    {HWND_AUDIO_LANGUAGE_MAX, _GUI_WindowList_Zui_Audio_Language,
         //_GUI_WindowsDrawStyleList_Zui_Audio_Language,
         _GUI_WindowsAlphaList_Zui_Audio_Language,
         NULL,
         E_OSD_GWIN0, ZUI_AUDIO_LANGUAGE_XSTART, ZUI_AUDIO_LANGUAGE_YSTART, ZUI_AUDIO_LANGUAGE_WIDTH, ZUI_AUDIO_LANGUAGE_HEIGHT, 0, 56, 1,
         CLRKEY_LO_R, CLRKEY_LO_G, CLRKEY_LO_B, CLRKEY_HI_R, CLRKEY_HI_G, CLRKEY_HI_B,
         0 },
    {HWND_SUBTITLE_LANGUAGE_MAX, _GUI_WindowList_Zui_Subtitle_Language,
         //_GUI_WindowsDrawStyleList_Zui_Subtitle_Language,
         _GUI_WindowsAlphaList_Zui_Subtitle_Language,
         NULL,
         E_OSD_GWIN0, ZUI_SUBTITLE_LANGUAGE_XSTART, ZUI_SUBTITLE_LANGUAGE_YSTART, ZUI_SUBTITLE_LANGUAGE_WIDTH, ZUI_SUBTITLE_LANGUAGE_HEIGHT, 0, 56, 1,
         CLRKEY_LO_R, CLRKEY_LO_G, CLRKEY_LO_B, CLRKEY_HI_R, CLRKEY_HI_G, CLRKEY_HI_B,
         0 },
    {HWND_INSTALL_GUIDE_MAX, _GUI_WindowList_Zui_Install_Guide,
         //_GUI_WindowsDrawStyleList_Zui_Install_Guide,
         _GUI_WindowsAlphaList_Zui_Install_Guide,
         NULL,
         E_OSD_GWIN0, ZUI_INSTALL_GUIDE_XSTART, ZUI_INSTALL_GUIDE_YSTART, ZUI_INSTALL_GUIDE_WIDTH, ZUI_INSTALL_GUIDE_HEIGHT, 0, 56, 1,
         CLRKEY_LO_R, CLRKEY_LO_G, CLRKEY_LO_B, CLRKEY_HI_R, CLRKEY_HI_G, CLRKEY_HI_B,
         0 },
    {HWND_AUDIO_VOLUME_MAX, _GUI_WindowList_Zui_Audio_Volume,
         //_GUI_WindowsDrawStyleList_Zui_Audio_Volume,
         _GUI_WindowsAlphaList_Zui_Audio_Volume,
         NULL,
         E_OSD_GWIN0, ZUI_AUDIO_VOLUME_XSTART, ZUI_AUDIO_VOLUME_YSTART, ZUI_AUDIO_VOLUME_WIDTH, ZUI_AUDIO_VOLUME_HEIGHT, 0, 56, 1,
         CLRKEY_LO_R, CLRKEY_LO_G, CLRKEY_LO_B, CLRKEY_HI_R, CLRKEY_HI_G, CLRKEY_HI_B,
         0 },
    {HWND_HOTKEY_OPTION_MAX, _GUI_WindowList_Zui_Hotkey_Option,
         //_GUI_WindowsDrawStyleList_Zui_Hotkey_Option,
         _GUI_WindowsAlphaList_Zui_Hotkey_Option,
         NULL,
         E_OSD_GWIN0, ZUI_HOTKEY_OPTION_XSTART, ZUI_HOTKEY_OPTION_YSTART, ZUI_HOTKEY_OPTION_WIDTH, ZUI_HOTKEY_OPTION_HEIGHT, 0, 56, 1,
         CLRKEY_LO_R, CLRKEY_LO_G, CLRKEY_LO_B, CLRKEY_HI_R, CLRKEY_HI_G, CLRKEY_HI_B,
         0 },
    {HWND_MESSAGE_BOX_MAX, _GUI_WindowList_Zui_Message_Box,
         //_GUI_WindowsDrawStyleList_Zui_Message_Box,
         _GUI_WindowsAlphaList_Zui_Message_Box,
         NULL,
         E_OSD_GWIN0, ZUI_MESSAGE_BOX_XSTART, ZUI_MESSAGE_BOX_YSTART, ZUI_MESSAGE_BOX_WIDTH, ZUI_MESSAGE_BOX_HEIGHT, 0, 56, 1,
         CLRKEY_LO_R, CLRKEY_LO_G, CLRKEY_LO_B, CLRKEY_HI_R, CLRKEY_HI_G, CLRKEY_HI_B,
         0 },
/*         
    {HWND_EPG_MAX, _GUI_WindowList_Zui_Epg,
         //_GUI_WindowsDrawStyleList_Zui_Epg,
         _GUI_WindowsAlphaList_Zui_Epg,
         NULL,
         E_OSD_GWIN0, ZUI_EPG_XSTART, ZUI_EPG_YSTART, ZUI_EPG_WIDTH, ZUI_EPG_HEIGHT, 0, 56, 1,
         CLRKEY_LO_R, CLRKEY_LO_G, CLRKEY_LO_B, CLRKEY_HI_R, CLRKEY_HI_G, CLRKEY_HI_B,
         0 },
*/        
    {HWND_TENKEY_NUMBER_MAX, _GUI_WindowList_Zui_Tenkey_Number,
         //_GUI_WindowsDrawStyleList_Zui_Tenkey_Number,
         _GUI_WindowsAlphaList_Zui_Tenkey_Number,
         NULL,
         E_OSD_GWIN0, ZUI_TENKEY_NUMBER_XSTART, ZUI_TENKEY_NUMBER_YSTART, ZUI_TENKEY_NUMBER_WIDTH, ZUI_TENKEY_NUMBER_HEIGHT, 0, 56, 1,
         CLRKEY_LO_R, CLRKEY_LO_G, CLRKEY_LO_B, CLRKEY_HI_R, CLRKEY_HI_G, CLRKEY_HI_B,
         0 },
    {HWND_FACTORY_MENU_MAX, _GUI_WindowList_Zui_Factory_Menu,
         //_GUI_WindowsDrawStyleList_Zui_Factory_Menu,
         _GUI_WindowsAlphaList_Zui_Factory_Menu,
         NULL,
         E_OSD_GWIN0, ZUI_FACTORY_MENU_XSTART, ZUI_FACTORY_MENU_YSTART, ZUI_FACTORY_MENU_WIDTH, ZUI_FACTORY_MENU_HEIGHT, 0, 56, 1,
         CLRKEY_LO_R, CLRKEY_LO_G, CLRKEY_LO_B, CLRKEY_HI_R, CLRKEY_HI_G, CLRKEY_HI_B,
         0 },
/*         
    {HWND_CIMMI_MAX, _GUI_WindowList_Zui_Cimmi,
         //_GUI_WindowsDrawStyleList_Zui_Cimmi,
         _GUI_WindowsAlphaList_Zui_Cimmi,
         NULL,
         E_OSD_GWIN0, ZUI_CIMMI_XSTART, ZUI_CIMMI_YSTART, ZUI_CIMMI_WIDTH, ZUI_CIMMI_HEIGHT, 0, 56, 1,
         CLRKEY_LO_R, CLRKEY_LO_G, CLRKEY_LO_B, CLRKEY_HI_R, CLRKEY_HI_G, CLRKEY_HI_B,
         0 },
    {HWND_KTV_MAIN_MAX, _GUI_WindowList_Zui_Ktv_Main,
         //_GUI_WindowsDrawStyleList_Zui_Ktv_Main,
         _GUI_WindowsAlphaList_Zui_Ktv_Main,
         NULL,
         E_OSD_GWIN0, ZUI_KTV_MAIN_XSTART, ZUI_KTV_MAIN_YSTART, ZUI_KTV_MAIN_WIDTH, ZUI_KTV_MAIN_HEIGHT, 0, 56, 1,
         CLRKEY_LO_R, CLRKEY_LO_G, CLRKEY_LO_B, CLRKEY_HI_R, CLRKEY_HI_G, CLRKEY_HI_B,
         0 },
    {HWND_PVR_MAX, _GUI_WindowList_Zui_Pvr,
         //_GUI_WindowsDrawStyleList_Zui_Pvr,
         _GUI_WindowsAlphaList_Zui_Pvr,
         NULL,
         E_OSD_GWIN0, ZUI_PVR_XSTART, ZUI_PVR_YSTART, ZUI_PVR_WIDTH, ZUI_PVR_HEIGHT, 0, 56, 1,
         CLRKEY_LO_R, CLRKEY_LO_G, CLRKEY_LO_B, CLRKEY_HI_R, CLRKEY_HI_G, CLRKEY_HI_B,
         0 },
    {HWND_PVR_BROWSER_MAX, _GUI_WindowList_Zui_Pvr_Browser,
         //_GUI_WindowsDrawStyleList_Zui_Pvr_Browser,
         _GUI_WindowsAlphaList_Zui_Pvr_Browser,
         NULL,
         E_OSD_GWIN0, ZUI_PVR_BROWSER_XSTART, ZUI_PVR_BROWSER_YSTART, ZUI_PVR_BROWSER_WIDTH, ZUI_PVR_BROWSER_HEIGHT, 0, 56, 1,
         CLRKEY_LO_R, CLRKEY_LO_G, CLRKEY_LO_B, CLRKEY_HI_R, CLRKEY_HI_G, CLRKEY_HI_B,
         0 },
    {HWND_CADTV_MANUAL_TUNING_MAX, _GUI_WindowList_Zui_Cadtv_Manual_Tuning,
         //_GUI_WindowsDrawStyleList_Zui_Cadtv_Manual_Tuning,
         _GUI_WindowsAlphaList_Zui_Cadtv_Manual_Tuning,
         NULL,
         E_OSD_GWIN0, ZUI_CADTV_MANUAL_TUNING_XSTART, ZUI_CADTV_MANUAL_TUNING_YSTART, ZUI_CADTV_MANUAL_TUNING_WIDTH, ZUI_CADTV_MANUAL_TUNING_HEIGHT, 0, 56, 1,
         CLRKEY_LO_R, CLRKEY_LO_G, CLRKEY_LO_B, CLRKEY_HI_R, CLRKEY_HI_G, CLRKEY_HI_B,
         0 },
    {HWND_GAME_BROWSER_MAX, _GUI_WindowList_Zui_Game_Browser,
         //_GUI_WindowsDrawStyleList_Zui_Game_Browser,
         _GUI_WindowsAlphaList_Zui_Game_Browser,
         NULL,
         E_OSD_GWIN0, ZUI_GAME_BROWSER_XSTART, ZUI_GAME_BROWSER_YSTART, ZUI_GAME_BROWSER_WIDTH, ZUI_GAME_BROWSER_HEIGHT, 0, 56, 1,
         CLRKEY_LO_R, CLRKEY_LO_G, CLRKEY_LO_B, CLRKEY_HI_R, CLRKEY_HI_G, CLRKEY_HI_B,
         0 },
*/         
    {HWND_EFFECT_SETTING_MAX, _GUI_WindowList_Zui_Effect_Setting,
         //_GUI_WindowsDrawStyleList_Zui_Effect_Setting,
         _GUI_WindowsAlphaList_Zui_Effect_Setting,
         NULL,
         E_OSD_GWIN0, ZUI_EFFECT_SETTING_XSTART, ZUI_EFFECT_SETTING_YSTART, ZUI_EFFECT_SETTING_WIDTH, ZUI_EFFECT_SETTING_HEIGHT, 0, 56, 1,
         CLRKEY_LO_R, CLRKEY_LO_G, CLRKEY_LO_B, CLRKEY_HI_R, CLRKEY_HI_G, CLRKEY_HI_B,
         0 },
/*         
    {HWND_OAD_MAX, _GUI_WindowList_Zui_Oad,
         //_GUI_WindowsDrawStyleList_Zui_Oad,
         _GUI_WindowsAlphaList_Zui_Oad,
         NULL,
         E_OSD_GWIN0, ZUI_OAD_XSTART, ZUI_OAD_YSTART, ZUI_OAD_WIDTH, ZUI_OAD_HEIGHT, 0, 63, 1,
         CLRKEY_LO_R, CLRKEY_LO_G, CLRKEY_LO_B, CLRKEY_HI_R, CLRKEY_HI_G, CLRKEY_HI_B,
         0 },
*/         
    {HWND_DMP_MAX, _GUI_WindowList_Zui_Dmp,
         //_GUI_WindowsDrawStyleList_Zui_Dmp,
         _GUI_WindowsAlphaList_Zui_Dmp,
         NULL,
         E_OSD_GWIN0, ZUI_DMP_XSTART, ZUI_DMP_YSTART, ZUI_DMP_WIDTH, ZUI_DMP_HEIGHT, 0, 44, 1,
         CLRKEY_LO_R, CLRKEY_LO_G, CLRKEY_LO_B, CLRKEY_HI_R, CLRKEY_HI_G, CLRKEY_HI_B,
         0 },
    {HWND_EXPERT_MENU_MAX, _GUI_WindowList_Zui_Expert_Menu,
         //_GUI_WindowsDrawStyleList_Zui_Expert_Menu,
         _GUI_WindowsAlphaList_Zui_Expert_Menu,
         NULL,
         E_OSD_GWIN0, ZUI_EXPERT_MENU_XSTART, ZUI_EXPERT_MENU_YSTART, ZUI_EXPERT_MENU_WIDTH, ZUI_EXPERT_MENU_HEIGHT, 0, 63, 1,
         CLRKEY_LO_R, CLRKEY_LO_G, CLRKEY_LO_B, CLRKEY_HI_R, CLRKEY_HI_G, CLRKEY_HI_B,
         0 },
    {HWND_DESIGN_MENU_MAX, _GUI_WindowList_Zui_Design_Menu,
         //_GUI_WindowsDrawStyleList_Zui_Design_Menu,
         _GUI_WindowsAlphaList_Zui_Design_Menu,
         NULL,
         E_OSD_GWIN0, ZUI_DESIGN_MENU_XSTART, ZUI_DESIGN_MENU_YSTART, ZUI_DESIGN_MENU_WIDTH, ZUI_DESIGN_MENU_HEIGHT, 0, 56, 1,
         CLRKEY_LO_R, CLRKEY_LO_G, CLRKEY_LO_B, CLRKEY_HI_R, CLRKEY_HI_G, CLRKEY_HI_B,
         0 },	 
};

OSDPAGE_TRANSEFF_TABLE code OsdTransEffTables [] =
{
    { 0,
         0 },
    { E_TRANSEFF_IN_FADE_IN,
         E_TRANSEFF_OUT_FADE_OUT },
    { E_TRANSEFF_IN_NONE,
         E_TRANSEFF_OUT_NONE },
    { E_TRANSEFF_IN_ENTER_DOWN,
         E_TRANSEFF_OUT_EXIT_DOWN },
    { E_TRANSEFF_IN_NONE,
         E_TRANSEFF_OUT_NONE },
    { E_TRANSEFF_IN_NONE,
         E_TRANSEFF_OUT_NONE },
    { E_TRANSEFF_IN_NONE,
         E_TRANSEFF_OUT_NONE },
    { E_TRANSEFF_IN_NONE,
         E_TRANSEFF_OUT_NONE },
    { E_TRANSEFF_IN_ENTER_RIGHT,
         E_TRANSEFF_OUT_EXIT_RIGHT },
    { E_TRANSEFF_IN_SPREAD_OUT,
         E_TRANSEFF_OUT_ROLL_UP },
    { E_TRANSEFF_IN_NONE,
         E_TRANSEFF_OUT_NONE },
    { E_TRANSEFF_IN_NONE,
         E_TRANSEFF_OUT_NONE },
    { E_TRANSEFF_IN_FADE_IN,
         E_TRANSEFF_OUT_FADE_OUT },
    { E_TRANSEFF_IN_NONE,
         E_TRANSEFF_OUT_NONE },
    { E_TRANSEFF_IN_NONE,
         E_TRANSEFF_OUT_NONE },
    { E_TRANSEFF_IN_NONE,
         E_TRANSEFF_OUT_NONE },
    { E_TRANSEFF_IN_NONE,
         E_TRANSEFF_OUT_NONE },
    { E_TRANSEFF_IN_NONE,
         E_TRANSEFF_OUT_NONE },
    { E_TRANSEFF_IN_NONE,
         E_TRANSEFF_OUT_NONE },
    { E_TRANSEFF_IN_NONE,
         E_TRANSEFF_OUT_NONE },
    { E_TRANSEFF_IN_NONE,
         E_TRANSEFF_OUT_NONE },
    { E_TRANSEFF_IN_NONE,
         E_TRANSEFF_OUT_NONE },
    { E_TRANSEFF_IN_NONE,
         E_TRANSEFF_OUT_NONE },
    { E_TRANSEFF_IN_NONE,
         E_TRANSEFF_OUT_NONE },
    { E_TRANSEFF_IN_NONE,
         E_TRANSEFF_OUT_NONE },
    { E_TRANSEFF_IN_NONE,
         E_TRANSEFF_OUT_NONE },
    { E_TRANSEFF_IN_NONE,
         E_TRANSEFF_OUT_NONE },
    { E_TRANSEFF_IN_NONE,
         E_TRANSEFF_OUT_NONE },
    { E_TRANSEFF_IN_NONE,
         E_TRANSEFF_OUT_NONE },
    { E_TRANSEFF_IN_NONE,
         E_TRANSEFF_OUT_NONE },	 
};
