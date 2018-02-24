#ifndef _SW_CONFIG_DEFAULT_DVBS_H_
#define _SW_CONFIG_DEFAULT_DVBS_H_


//******************************************************************************
// DTV option...

#if ENABLE_S2
#define ENABLE_S2_CHCHANGE_NOT_SAVE_DTAR        DISABLE
#define ENABLE_S2_WORD                          ENABLE
#define ENABLE_S2_PROGRAM_PREPARE               DISABLE//ENABLE
#define SUPPORT_UNICABLE                        DISABLE
#define ENABLE_S2_CH_SWITCH                     ENABLE
#define ENABLE_S2_CH_CHANGE_TO_SEARCHPOSITION   ENABLE
#define ENABLE_S2_CHANNEL_FAV_NEWSTYLE          DISABLE
#define ENABLE_S2_FIND_PROGRAM_BYNAME           ENABLE
#define ENABLE_S2_PREDIT_RENAME                 ENABLE
#define ENABLE_S2_DATABASE_DBM                  DISABLE
#define ENABLE_S2_8M_FLASH                      ENABLE
#define ENABLE_COMPRESS_DATA                    DISABLE //ENABLE
#define ENABLE_S2_LCN_STYLE_AFTERSORT           DISABLE
#define ENABLE_S2_PREDIT_SWITCH_LIST            ENABLE
#define ENABLE_DELETE_SCREMBAL_PROGRAM          ENABLE
#define MOVE_DMP_TO_SOURCE_FROM_MENU            DISABLE
#define ENABLE_S2_SOURCE                        ENABLE
#if(ENABLE_CI)
#define ENABLE_S2_CI                            ENABLE
#else
#define ENABLE_S2_CI                            DISABLE
#endif
#define ENABLE_S2_QUALITY_DISPLAY_PERCENT       ENABLE
#define ENABLE_GOTO_DISH_SETUP_INPUT_PASSWORD   DISABLE
#define ENABLE_S2_EPG_REMINDER                  ENABLE
#define ENABLE_EPG_MUX                          ENABLE
#else
#define ENABLE_S2_CHCHANGE_NOT_SAVE_DTAR        DISABLE
#define ENABLE_S2_WORD                          DISABLE
#define ENABLE_S2_PROGRAM_PREPARE               DISABLE
#define SUPPORT_UNICABLE                        DISABLE
#define ENABLE_S2_CH_SWITCH                     DISABLE
#define ENABLE_S2_CH_CHANGE_TO_SEARCHPOSITION   DISABLE
#define ENABLE_S2_CHANNEL_FAV_NEWSTYLE          DISABLE
#define ENABLE_S2_FIND_PROGRAM_BYNAME           DISABLE
#define ENABLE_S2_PREDIT_RENAME                 DISABLE
#define ENABLE_S2_DATABASE_DBM                  DISABLE
#define ENABLE_S2_8M_FLASH                      DISABLE
#define ENABLE_COMPRESS_DATA                    DISABLE
#define ENABLE_S2_LCN_STYLE_AFTERSORT           DISABLE
#define ENABLE_S2_PREDIT_SWITCH_LIST            DISABLE
#define ENABLE_DELETE_SCREMBAL_PROGRAM          DISABLE
#define MOVE_DMP_TO_SOURCE_FROM_MENU            DISABLE
#define ENABLE_S2_SOURCE                        DISABLE
#define ENABLE_S2_CI                            DISABLE
#define ENABLE_S2_QUALITY_DISPLAY_PERCENT       DISABLE
#define ENABLE_GOTO_DISH_SETUP_INPUT_PASSWORD   DISABLE
#define ENABLE_S2_EPG_REMINDER                  DISABLE
#endif


//----------------------------------------------------------------------------

#endif // _SW_CONFIG_DEFAULT_DVBS_H_

