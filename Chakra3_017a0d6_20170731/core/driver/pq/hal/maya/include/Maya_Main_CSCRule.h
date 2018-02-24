#define PQ_CSCRule_ID_Main 4
#define PQ_CSCRule_IP_NUM_Main 2
#define PQ_CSCRule_NUM_Main 12


typedef enum
{
PQ_CSCRule_Video_RGB_SD_0_255_Main,
PQ_CSCRule_Video_RGB_SD_16_235_Main,
PQ_CSCRule_Video_RGB_HD_0_255_Main,
PQ_CSCRule_Video_RGB_HD_16_235_Main,
PQ_CSCRule_Video_YUV_SD_Main,
PQ_CSCRule_Video_YUV_HD_Main,
PQ_CSCRule_PC_RGB_SD_0_255_Main,
PQ_CSCRule_PC_RGB_SD_16_235_Main,
PQ_CSCRule_PC_RGB_HD_0_255_Main,
PQ_CSCRule_PC_RGB_HD_16_235_Main,
PQ_CSCRule_PC_YUV_SD_Main,
PQ_CSCRule_PC_YUV_HD_Main,
}
MST_CSCRule_Index_Main;
extern code U8 MST_CSCRule_IP_Index_Main[PQ_CSCRule_IP_NUM_Main];
extern code U8 MST_CSCRule_Array_Main[PQ_CSCRule_NUM_Main][PQ_CSCRule_IP_NUM_Main];

