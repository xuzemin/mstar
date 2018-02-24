#define PQ_GRULE_NR_ENABLE 1
#define PQ_GRULE_DEFINE_AUTO_GEN 1
#if (PQ_GRULE_NR_ENABLE)
typedef enum
{
#if PQ_GRULE_NR_ENABLE
    PQ_GRule_NR_Main_Color,
#endif

}
MST_GRule_Index_Main_Color;
#endif

#if PQ_GRULE_NR_ENABLE
typedef enum
{
    PQ_GRule_NR_Off_Main_Color,
    PQ_GRule_NR_Low_Main_Color,
    PQ_GRule_NR_Middle_Main_Color,
    PQ_GRule_NR_High_Main_Color,
    PQ_GRule_NR_Low_3D_Main_Color,
    PQ_GRule_NR_Middle_3D_Main_Color,
    PQ_GRule_NR_High_3D_Main_Color,
    PQ_GRule_NR_Auto_Low_L_Main_Color,
    PQ_GRule_NR_Auto_Low_M_Main_Color,
    PQ_GRule_NR_Auto_Low_H_Main_Color,
    PQ_GRule_NR_Auto_Middle_L_Main_Color,
    PQ_GRule_NR_Auto_Middle_M_Main_Color,
    PQ_GRule_NR_Auto_Middle_H_Main_Color,
    PQ_GRule_NR_Auto_High_L_Main_Color,
    PQ_GRule_NR_Auto_High_M_Main_Color,
    PQ_GRule_NR_Auto_High_H_Main_Color,
    PQ_GRule_NR_Low_PIP_Main_Color,
    PQ_GRule_NR_Middle_PIP_Main_Color,
    PQ_GRule_NR_High_PIP_Main_Color,
}
MST_GRule_NR_Index_Main_Color;
#endif

#if PQ_GRULE_NR_ENABLE
typedef enum
{
    PQ_GRule_Lvl_NR_Off_Main_Color,
    PQ_GRule_Lvl_NR_Low_Main_Color,
    PQ_GRule_Lvl_NR_Middle_Main_Color,
    PQ_GRule_Lvl_NR_High_Main_Color,
    PQ_GRule_Lvl_NR_Low_3D_Main_Color,
    PQ_GRule_Lvl_NR_Middle_3D_Main_Color,
    PQ_GRule_Lvl_NR_High_3D_Main_Color,
    PQ_GRule_Lvl_NR_Auto_Low_L_Main_Color,
    PQ_GRule_Lvl_NR_Auto_Low_M_Main_Color,
    PQ_GRule_Lvl_NR_Auto_Low_H_Main_Color,
    PQ_GRule_Lvl_NR_Auto_Middle_L_Main_Color,
    PQ_GRule_Lvl_NR_Auto_Middle_M_Main_Color,
    PQ_GRule_Lvl_NR_Auto_Middle_H_Main_Color,
    PQ_GRule_Lvl_NR_Auto_High_L_Main_Color,
    PQ_GRule_Lvl_NR_Auto_High_M_Main_Color,
    PQ_GRule_Lvl_NR_Auto_High_H_Main_Color,
}
MST_GRule_NR_LvL_Index_Main_Color;
#endif


#define PQ_GRULE_RULE_NUM_Main_Color 1

#if PQ_GRULE_NR_ENABLE
#define PQ_GRULE_NR_IP_NUM_Main_Color 2
#define PQ_GRULE_NR_NUM_Main_Color 19
#define PQ_GRULE_NR_LVL_NUM_Main_Color 16
#endif

#if PQ_GRULE_NR_ENABLE
extern code U8 MST_GRule_NR_IP_Index_Main_Color[PQ_GRULE_NR_IP_NUM_Main_Color];
extern code U8 MST_GRule_NR_Main_Color[QM_INPUTTYPE_NUM_Main_Color][PQ_GRULE_NR_NUM_Main_Color][PQ_GRULE_NR_IP_NUM_Main_Color];
#endif

#if PQ_GRULE_NR_ENABLE
extern code U8 MST_GRule_1920_NR_Main_Color[PQ_GRULE_NR_LVL_NUM_Main_Color];
#endif

