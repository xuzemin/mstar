#define PQ_VSDRule_ID_Main 1
#define PQ_VSDRule_IP_NUM_Main 2
#define PQ_VSDRule_NUM_Main 24


typedef enum
{
PQ_VSDRule_PreV_ScalingDown_Interlace_Main,
PQ_VSDRule_PreV_ScalingDown_Progressive_Main,
PQ_VSDRule_ScalingDown_00x_YUV_Main,
PQ_VSDRule_ScalingDown_00x_RGB_Main,
PQ_VSDRule_ScalingDown_01x_YUV_Main,
PQ_VSDRule_ScalingDown_01x_RGB_Main,
PQ_VSDRule_ScalingDown_02x_YUV_Main,
PQ_VSDRule_ScalingDown_02x_RGB_Main,
PQ_VSDRule_ScalingDown_03x_YUV_Main,
PQ_VSDRule_ScalingDown_03x_RGB_Main,
PQ_VSDRule_ScalingDown_04x_YUV_Main,
PQ_VSDRule_ScalingDown_04x_RGB_Main,
PQ_VSDRule_ScalingDown_05x_YUV_Main,
PQ_VSDRule_ScalingDown_05x_RGB_Main,
PQ_VSDRule_ScalingDown_06x_YUV_Main,
PQ_VSDRule_ScalingDown_06x_RGB_Main,
PQ_VSDRule_ScalingDown_07x_YUV_Main,
PQ_VSDRule_ScalingDown_07x_RGB_Main,
PQ_VSDRule_ScalingDown_08x_YUV_Main,
PQ_VSDRule_ScalingDown_08x_RGB_Main,
PQ_VSDRule_ScalingDown_09x_YUV_Main,
PQ_VSDRule_ScalingDown_09x_RGB_Main,
PQ_VSDRule_ScalingDown_10x_YUV_Main,
PQ_VSDRule_ScalingDown_10x_RGB_Main,
}
MST_VSDRule_Index_Main;
extern code U8 MST_VSDRule_IP_Index_Main[PQ_VSDRule_IP_NUM_Main];
extern code U8 MST_VSDRule_Array_Main[PQ_VSDRule_NUM_Main][PQ_VSDRule_IP_NUM_Main];

