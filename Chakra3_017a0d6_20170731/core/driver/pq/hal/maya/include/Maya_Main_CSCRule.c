
code U8 MST_CSCRule_IP_Index_Main[PQ_CSCRule_IP_NUM_Main]=
{
    PQ_IP_CSC_Main,
    PQ_IP_VIP_CSC_Main,
};


code U8 MST_CSCRule_Array_Main[PQ_CSCRule_NUM_Main][PQ_CSCRule_IP_NUM_Main]=
{
    {//Video_RGB_SD_0_255, 0
        PQ_IP_CSC_F_RGB2YCC_SD_Main, PQ_IP_VIP_CSC_OFF_Main, 
    },
    {//Video_RGB_SD_16_235, 1
        PQ_IP_CSC_L_RGB2YCC_SD_Main, PQ_IP_VIP_CSC_OFF_Main, 
    },
    {//Video_RGB_HD_0_255, 2
        PQ_IP_CSC_F_RGB2YCC_HD_Main, PQ_IP_VIP_CSC_709_YCC2YCC_601_Main, 
    },
    {//Video_RGB_HD_16_235, 3
        PQ_IP_CSC_L_RGB2YCC_HD_Main, PQ_IP_VIP_CSC_709_YCC2YCC_601_Main, 
    },
    {//Video_YUV_SD, 4
        PQ_IP_CSC_OFF_Main, PQ_IP_VIP_CSC_OFF_Main, 
    },
    {//Video_YUV_HD, 5
        PQ_IP_CSC_OFF_Main, PQ_IP_VIP_CSC_709_YCC2YCC_601_Main, 
    },
    {//PC_RGB_SD_0_255, 6
        PQ_IP_CSC_OFF_Main, PQ_IP_VIP_CSC_F_RGB2YCC_SD_Main, 
    },
    {//PC_RGB_SD_16_235, 7
        PQ_IP_CSC_OFF_Main, PQ_IP_VIP_CSC_L_RGB2YCC_SD_Main, 
    },
    {//PC_RGB_HD_0_255, 8
        PQ_IP_CSC_OFF_Main, PQ_IP_VIP_CSC_F_RGB2YCC_HD_Main, 
    },
    {//PC_RGB_HD_16_235, 9
        PQ_IP_CSC_OFF_Main, PQ_IP_VIP_CSC_L_RGB2YCC_HD_Main, 
    },
    {//PC_YUV_SD, 10
        PQ_IP_CSC_OFF_Main, PQ_IP_VIP_CSC_OFF_Main, 
    },
    {//PC_YUV_HD, 11
        PQ_IP_CSC_OFF_Main, PQ_IP_VIP_CSC_709_YCC2YCC_601_Main, 
    },
};
