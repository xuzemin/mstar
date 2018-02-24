
code U8 MST_HSDRule_IP_Index_Main[PQ_HSDRule_IP_NUM_Main]=
{
    PQ_IP_HSD_Y_Main,
    PQ_IP_HSD_C_Main,
};


code U8 MST_HSDRule_Array_Main[PQ_HSDRule_NUM_Main][PQ_HSDRule_IP_NUM_Main]=
{
    {//PreV_ScalingDown_Interlace, 0
        PQ_IP_NULL, PQ_IP_NULL, 
    },
    {//PreV_ScalingDown_Progressive, 1
        PQ_IP_NULL, PQ_IP_NULL, 
    },
    {//ScalingDown_00x_YUV, 2
        PQ_IP_HSD_Y_CB_Main, PQ_IP_HSD_C_CB_Main, 
    },
    {//ScalingDown_00x_RGB, 3
        PQ_IP_HSD_Y_CB_Main, PQ_IP_HSD_C_CB_Main, 
    },
    {//ScalingDown_01x_YUV, 4
        PQ_IP_HSD_Y_CB_Main, PQ_IP_HSD_C_CB_Main, 
    },
    {//ScalingDown_01x_RGB, 5
        PQ_IP_HSD_Y_CB_Main, PQ_IP_HSD_C_CB_Main, 
    },
    {//ScalingDown_02x_YUV, 6
        PQ_IP_HSD_Y_CB_Main, PQ_IP_HSD_C_CB_Main, 
    },
    {//ScalingDown_02x_RGB, 7
        PQ_IP_HSD_Y_CB_Main, PQ_IP_HSD_C_CB_Main, 
    },
    {//ScalingDown_03x_YUV, 8
        PQ_IP_HSD_Y_CB_Main, PQ_IP_HSD_C_CB_Main, 
    },
    {//ScalingDown_03x_RGB, 9
        PQ_IP_HSD_Y_CB_Main, PQ_IP_HSD_C_CB_Main, 
    },
    {//ScalingDown_04x_YUV, 10
        PQ_IP_HSD_Y_LpfFc40Ap0As40_Main, PQ_IP_HSD_C_LpfFc15Ap0As45_Main, 
    },
    {//ScalingDown_04x_RGB, 11
        PQ_IP_HSD_Y_CB_Main, PQ_IP_HSD_C_CB_Main, 
    },
    {//ScalingDown_05x_YUV, 12
        PQ_IP_HSD_Y_LpfFc80Ap0As35_Main, PQ_IP_HSD_C_LpfFc15Ap0As45_Main, 
    },
    {//ScalingDown_05x_RGB, 13
        PQ_IP_HSD_Y_CB_Main, PQ_IP_HSD_C_CB_Main, 
    },
    {//ScalingDown_06x_YUV, 14
        PQ_IP_HSD_Y_LpfFc60Ap0As35_Main, PQ_IP_HSD_C_LpfFc15Ap0As45_Main, 
    },
    {//ScalingDown_06x_RGB, 15
        PQ_IP_HSD_Y_CB_Main, PQ_IP_HSD_C_CB_Main, 
    },
    {//ScalingDown_07x_YUV, 16
        PQ_IP_HSD_Y_LpfFc70Ap0As35_Main, PQ_IP_HSD_C_LpfFc15Ap0As45_Main, 
    },
    {//ScalingDown_07x_RGB, 17
        PQ_IP_HSD_Y_CB_Main, PQ_IP_HSD_C_CB_Main, 
    },
    {//ScalingDown_08x_YUV, 18
        PQ_IP_HSD_Y_LpfFc80Ap0As35_Main, PQ_IP_HSD_C_LpfFc15Ap0As45_Main, 
    },
    {//ScalingDown_08x_RGB, 19
        PQ_IP_HSD_Y_CB_Main, PQ_IP_HSD_C_CB_Main, 
    },
    {//ScalingDown_09x_YUV, 20
        PQ_IP_HSD_Y_LpfFc90Ap0As35_Main, PQ_IP_HSD_C_LpfFc15Ap0As45_Main, 
    },
    {//ScalingDown_09x_RGB, 21
        PQ_IP_HSD_Y_CB_Main, PQ_IP_HSD_C_CB_Main, 
    },
    {//ScalingDown_10x_YUV, 22
        PQ_IP_HSD_Y_ALLPASS1X_Main, PQ_IP_HSD_C_ALLPASS1X_Main, 
    },
    {//ScalingDown_10x_RGB, 23
        PQ_IP_HSD_Y_ALLPASS1X_Main, PQ_IP_HSD_C_ALLPASS1X_Main, 
    },
};
