#define PQ_GRULE_NR_ENABLE 1
#define PQ_GRULE_OSD_BW_ENABLE 1
#define PQ_GRULE_MPEG_NR_ENABLE 1
#define PQ_GRULE_FILM_MODE_ENABLE 1
#define PQ_GRULE_DYNAMIC_CONTRAST_ENABLE 1
#define PQ_GRULE_COLOR_FOR_VIVID_ENABLE 1
#define PQ_GRULE_PTP_ENABLE 1
#define PQ_GRULE_DEFINE_AUTO_GEN 1
#if (PQ_GRULE_NR_ENABLE) || (PQ_GRULE_OSD_BW_ENABLE) || (PQ_GRULE_MPEG_NR_ENABLE) || (PQ_GRULE_FILM_MODE_ENABLE) || (PQ_GRULE_DYNAMIC_CONTRAST_ENABLE) || (PQ_GRULE_COLOR_FOR_VIVID_ENABLE) || (PQ_GRULE_PTP_ENABLE)
typedef enum
{
#if PQ_GRULE_NR_ENABLE
    PQ_GRule_NR_Main,
#endif

#if PQ_GRULE_OSD_BW_ENABLE
    PQ_GRule_OSD_BW_Main,
#endif

#if PQ_GRULE_MPEG_NR_ENABLE
    PQ_GRule_MPEG_NR_Main,
#endif

#if PQ_GRULE_FILM_MODE_ENABLE
    PQ_GRule_FILM_MODE_Main,
#endif

#if PQ_GRULE_DYNAMIC_CONTRAST_ENABLE
    PQ_GRule_DYNAMIC_CONTRAST_Main,
#endif

#if PQ_GRULE_COLOR_FOR_VIVID_ENABLE
    PQ_GRule_COLOR_FOR_VIVID_Main,
#endif

#if PQ_GRULE_PTP_ENABLE
    PQ_GRule_PTP_Main,
#endif

}
MST_GRule_Index_Main;
#endif

#if PQ_GRULE_NR_ENABLE
typedef enum
{
    PQ_GRule_NR_Off_Main,
    PQ_GRule_NR_Low_Main,
    PQ_GRule_NR_Middle_Main,
    PQ_GRule_NR_High_Main,
    PQ_GRule_NR_Auto_Low_L_Main,
    PQ_GRule_NR_Auto_Low_M_Main,
    PQ_GRule_NR_Auto_Low_H_Main,
    PQ_GRule_NR_Auto_Middle_L_Main,
    PQ_GRule_NR_Auto_Middle_M_Main,
    PQ_GRule_NR_Auto_Middle_H_Main,
    PQ_GRule_NR_Auto_High_L_Main,
    PQ_GRule_NR_Auto_High_M_Main,
    PQ_GRule_NR_Auto_High_H_Main,
    PQ_GRule_NR_Low_4K2K_Main,
    PQ_GRule_NR_Middle_4K2K_Main,
    PQ_GRule_NR_High_4K2K_Main,
}
MST_GRule_NR_Index_Main;
#endif

#if PQ_GRULE_OSD_BW_ENABLE
typedef enum
{
    PQ_GRule_OSD_BW_1920_On_Main,
    PQ_GRule_OSD_BW_1366_On_Main,
    PQ_GRule_OSD_BW_4K2K_On_Main,
}
MST_GRule_OSD_BW_Index_Main;
#endif

#if PQ_GRULE_MPEG_NR_ENABLE
typedef enum
{
    PQ_GRule_MPEG_NR_Off_Main,
    PQ_GRule_MPEG_NR_Low_Main,
    PQ_GRule_MPEG_NR_Middle_Main,
    PQ_GRule_MPEG_NR_High_Main,
}
MST_GRule_MPEG_NR_Index_Main;
#endif

#if PQ_GRULE_FILM_MODE_ENABLE
typedef enum
{
    PQ_GRule_FILM_MODE_Off_Main,
    PQ_GRule_FILM_MODE_On_Main,
}
MST_GRule_FILM_MODE_Index_Main;
#endif

#if PQ_GRULE_DYNAMIC_CONTRAST_ENABLE
typedef enum
{
    PQ_GRule_DYNAMIC_CONTRAST_Off_Main,
    PQ_GRule_DYNAMIC_CONTRAST_On_Main,
}
MST_GRule_DYNAMIC_CONTRAST_Index_Main;
#endif

#if PQ_GRULE_COLOR_FOR_VIVID_ENABLE
typedef enum
{
    PQ_GRule_COLOR_FOR_VIVID_On_Main,
}
MST_GRule_COLOR_FOR_VIVID_Index_Main;
#endif

#if PQ_GRULE_PTP_ENABLE
typedef enum
{
    PQ_GRule_PTP_On_PTP_Main,
}
MST_GRule_PTP_Index_Main;
#endif

#if PQ_GRULE_NR_ENABLE
typedef enum
{
    PQ_GRule_Lvl_NR_Off_Main,
    PQ_GRule_Lvl_NR_Low_Main,
    PQ_GRule_Lvl_NR_Middle_Main,
    PQ_GRule_Lvl_NR_High_Main,
    PQ_GRule_Lvl_NR_Auto_Low_L_Main,
    PQ_GRule_Lvl_NR_Auto_Low_M_Main,
    PQ_GRule_Lvl_NR_Auto_Low_H_Main,
    PQ_GRule_Lvl_NR_Auto_Middle_L_Main,
    PQ_GRule_Lvl_NR_Auto_Middle_M_Main,
    PQ_GRule_Lvl_NR_Auto_Middle_H_Main,
    PQ_GRule_Lvl_NR_Auto_High_L_Main,
    PQ_GRule_Lvl_NR_Auto_High_M_Main,
    PQ_GRule_Lvl_NR_Auto_High_H_Main,
}
MST_GRule_NR_LvL_Index_Main;
#endif

#if PQ_GRULE_OSD_BW_ENABLE
typedef enum
{
    PQ_GRule_Lvl_OSD_BW_On_Main,
}
MST_GRule_OSD_BW_LvL_Index_Main;
#endif

#if PQ_GRULE_MPEG_NR_ENABLE
typedef enum
{
    PQ_GRule_Lvl_MPEG_NR_Off_Main,
    PQ_GRule_Lvl_MPEG_NR_Low_Main,
    PQ_GRule_Lvl_MPEG_NR_Middle_Main,
    PQ_GRule_Lvl_MPEG_NR_High_Main,
}
MST_GRule_MPEG_NR_LvL_Index_Main;
#endif

#if PQ_GRULE_FILM_MODE_ENABLE
typedef enum
{
    PQ_GRule_Lvl_FILM_MODE_Off_Main,
    PQ_GRule_Lvl_FILM_MODE_On_Main,
}
MST_GRule_FILM_MODE_LvL_Index_Main;
#endif

#if PQ_GRULE_DYNAMIC_CONTRAST_ENABLE
typedef enum
{
    PQ_GRule_Lvl_DYNAMIC_CONTRAST_Off_Main,
    PQ_GRule_Lvl_DYNAMIC_CONTRAST_On_Main,
}
MST_GRule_DYNAMIC_CONTRAST_LvL_Index_Main;
#endif

#if PQ_GRULE_COLOR_FOR_VIVID_ENABLE
typedef enum
{
    PQ_GRule_Lvl_COLOR_FOR_VIVID_On_Main,
}
MST_GRule_COLOR_FOR_VIVID_LvL_Index_Main;
#endif

#if PQ_GRULE_PTP_ENABLE
typedef enum
{
    PQ_GRule_Lvl_PTP_On_Main,
}
MST_GRule_PTP_LvL_Index_Main;
#endif


#define PQ_GRULE_RULE_NUM_Main 7

#if PQ_GRULE_NR_ENABLE
#define PQ_GRULE_NR_IP_NUM_Main 9
#define PQ_GRULE_NR_NUM_Main 16
#define PQ_GRULE_NR_LVL_NUM_Main 13
#endif

#if PQ_GRULE_OSD_BW_ENABLE
#define PQ_GRULE_OSD_BW_IP_NUM_Main 3
#define PQ_GRULE_OSD_BW_NUM_Main 3
#define PQ_GRULE_OSD_BW_LVL_NUM_Main 1
#endif

#if PQ_GRULE_MPEG_NR_ENABLE
#define PQ_GRULE_MPEG_NR_IP_NUM_Main 6
#define PQ_GRULE_MPEG_NR_NUM_Main 4
#define PQ_GRULE_MPEG_NR_LVL_NUM_Main 4
#endif

#if PQ_GRULE_FILM_MODE_ENABLE
#define PQ_GRULE_FILM_MODE_IP_NUM_Main 4
#define PQ_GRULE_FILM_MODE_NUM_Main 2
#define PQ_GRULE_FILM_MODE_LVL_NUM_Main 2
#endif

#if PQ_GRULE_DYNAMIC_CONTRAST_ENABLE
#define PQ_GRULE_DYNAMIC_CONTRAST_IP_NUM_Main 1
#define PQ_GRULE_DYNAMIC_CONTRAST_NUM_Main 2
#define PQ_GRULE_DYNAMIC_CONTRAST_LVL_NUM_Main 2
#endif

#if PQ_GRULE_COLOR_FOR_VIVID_ENABLE
#define PQ_GRULE_COLOR_FOR_VIVID_IP_NUM_Main 6
#define PQ_GRULE_COLOR_FOR_VIVID_NUM_Main 1
#define PQ_GRULE_COLOR_FOR_VIVID_LVL_NUM_Main 1
#endif

#if PQ_GRULE_PTP_ENABLE
#define PQ_GRULE_PTP_IP_NUM_Main 2
#define PQ_GRULE_PTP_NUM_Main 1
#define PQ_GRULE_PTP_LVL_NUM_Main 1
#endif

#if PQ_GRULE_NR_ENABLE
extern code U8 MST_GRule_NR_IP_Index_Main[PQ_GRULE_NR_IP_NUM_Main];
extern code U8 MST_GRule_NR_Main[QM_INPUTTYPE_NUM_Main][PQ_GRULE_NR_NUM_Main][PQ_GRULE_NR_IP_NUM_Main];
#endif

#if PQ_GRULE_OSD_BW_ENABLE
extern code U8 MST_GRule_OSD_BW_IP_Index_Main[PQ_GRULE_OSD_BW_IP_NUM_Main];
extern code U8 MST_GRule_OSD_BW_Main[QM_INPUTTYPE_NUM_Main][PQ_GRULE_OSD_BW_NUM_Main][PQ_GRULE_OSD_BW_IP_NUM_Main];
#endif

#if PQ_GRULE_MPEG_NR_ENABLE
extern code U8 MST_GRule_MPEG_NR_IP_Index_Main[PQ_GRULE_MPEG_NR_IP_NUM_Main];
extern code U8 MST_GRule_MPEG_NR_Main[QM_INPUTTYPE_NUM_Main][PQ_GRULE_MPEG_NR_NUM_Main][PQ_GRULE_MPEG_NR_IP_NUM_Main];
#endif

#if PQ_GRULE_FILM_MODE_ENABLE
extern code U8 MST_GRule_FILM_MODE_IP_Index_Main[PQ_GRULE_FILM_MODE_IP_NUM_Main];
extern code U8 MST_GRule_FILM_MODE_Main[QM_INPUTTYPE_NUM_Main][PQ_GRULE_FILM_MODE_NUM_Main][PQ_GRULE_FILM_MODE_IP_NUM_Main];
#endif

#if PQ_GRULE_DYNAMIC_CONTRAST_ENABLE
extern code U8 MST_GRule_DYNAMIC_CONTRAST_IP_Index_Main[PQ_GRULE_DYNAMIC_CONTRAST_IP_NUM_Main];
extern code U8 MST_GRule_DYNAMIC_CONTRAST_Main[QM_INPUTTYPE_NUM_Main][PQ_GRULE_DYNAMIC_CONTRAST_NUM_Main][PQ_GRULE_DYNAMIC_CONTRAST_IP_NUM_Main];
#endif

#if PQ_GRULE_COLOR_FOR_VIVID_ENABLE
extern code U8 MST_GRule_COLOR_FOR_VIVID_IP_Index_Main[PQ_GRULE_COLOR_FOR_VIVID_IP_NUM_Main];
extern code U8 MST_GRule_COLOR_FOR_VIVID_Main[QM_INPUTTYPE_NUM_Main][PQ_GRULE_COLOR_FOR_VIVID_NUM_Main][PQ_GRULE_COLOR_FOR_VIVID_IP_NUM_Main];
#endif

#if PQ_GRULE_PTP_ENABLE
extern code U8 MST_GRule_PTP_IP_Index_Main[PQ_GRULE_PTP_IP_NUM_Main];
extern code U8 MST_GRule_PTP_Main[QM_INPUTTYPE_NUM_Main][PQ_GRULE_PTP_NUM_Main][PQ_GRULE_PTP_IP_NUM_Main];
#endif

#if PQ_GRULE_NR_ENABLE
extern code U8 MST_GRule_1920_NR_Main[PQ_GRULE_NR_LVL_NUM_Main];
#endif
#if PQ_GRULE_OSD_BW_ENABLE
extern code U8 MST_GRule_1920_OSD_BW_Main[PQ_GRULE_OSD_BW_LVL_NUM_Main];
#endif
#if PQ_GRULE_MPEG_NR_ENABLE
extern code U8 MST_GRule_1920_MPEG_NR_Main[PQ_GRULE_MPEG_NR_LVL_NUM_Main];
#endif
#if PQ_GRULE_FILM_MODE_ENABLE
extern code U8 MST_GRule_1920_FILM_MODE_Main[PQ_GRULE_FILM_MODE_LVL_NUM_Main];
#endif
#if PQ_GRULE_DYNAMIC_CONTRAST_ENABLE
extern code U8 MST_GRule_1920_DYNAMIC_CONTRAST_Main[PQ_GRULE_DYNAMIC_CONTRAST_LVL_NUM_Main];
#endif
#if PQ_GRULE_COLOR_FOR_VIVID_ENABLE
extern code U8 MST_GRule_1920_COLOR_FOR_VIVID_Main[PQ_GRULE_COLOR_FOR_VIVID_LVL_NUM_Main];
#endif
#if PQ_GRULE_PTP_ENABLE
extern code U8 MST_GRule_1920_PTP_Main[PQ_GRULE_PTP_LVL_NUM_Main];
#endif

#if PQ_GRULE_NR_ENABLE
extern code U8 MST_GRule_1366_NR_Main[PQ_GRULE_NR_LVL_NUM_Main];
#endif
#if PQ_GRULE_OSD_BW_ENABLE
extern code U8 MST_GRule_1366_OSD_BW_Main[PQ_GRULE_OSD_BW_LVL_NUM_Main];
#endif
#if PQ_GRULE_MPEG_NR_ENABLE
extern code U8 MST_GRule_1366_MPEG_NR_Main[PQ_GRULE_MPEG_NR_LVL_NUM_Main];
#endif
#if PQ_GRULE_FILM_MODE_ENABLE
extern code U8 MST_GRule_1366_FILM_MODE_Main[PQ_GRULE_FILM_MODE_LVL_NUM_Main];
#endif
#if PQ_GRULE_DYNAMIC_CONTRAST_ENABLE
extern code U8 MST_GRule_1366_DYNAMIC_CONTRAST_Main[PQ_GRULE_DYNAMIC_CONTRAST_LVL_NUM_Main];
#endif
#if PQ_GRULE_COLOR_FOR_VIVID_ENABLE
extern code U8 MST_GRule_1366_COLOR_FOR_VIVID_Main[PQ_GRULE_COLOR_FOR_VIVID_LVL_NUM_Main];
#endif
#if PQ_GRULE_PTP_ENABLE
extern code U8 MST_GRule_1366_PTP_Main[PQ_GRULE_PTP_LVL_NUM_Main];
#endif

#if PQ_GRULE_NR_ENABLE
extern code U8 MST_GRule_4K2K_NR_Main[PQ_GRULE_NR_LVL_NUM_Main];
#endif
#if PQ_GRULE_OSD_BW_ENABLE
extern code U8 MST_GRule_4K2K_OSD_BW_Main[PQ_GRULE_OSD_BW_LVL_NUM_Main];
#endif
#if PQ_GRULE_MPEG_NR_ENABLE
extern code U8 MST_GRule_4K2K_MPEG_NR_Main[PQ_GRULE_MPEG_NR_LVL_NUM_Main];
#endif
#if PQ_GRULE_FILM_MODE_ENABLE
extern code U8 MST_GRule_4K2K_FILM_MODE_Main[PQ_GRULE_FILM_MODE_LVL_NUM_Main];
#endif
#if PQ_GRULE_DYNAMIC_CONTRAST_ENABLE
extern code U8 MST_GRule_4K2K_DYNAMIC_CONTRAST_Main[PQ_GRULE_DYNAMIC_CONTRAST_LVL_NUM_Main];
#endif
#if PQ_GRULE_COLOR_FOR_VIVID_ENABLE
extern code U8 MST_GRule_4K2K_COLOR_FOR_VIVID_Main[PQ_GRULE_COLOR_FOR_VIVID_LVL_NUM_Main];
#endif
#if PQ_GRULE_PTP_ENABLE
extern code U8 MST_GRule_4K2K_PTP_Main[PQ_GRULE_PTP_LVL_NUM_Main];
#endif

