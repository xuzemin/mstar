#define _LED_DEVICE_C_

#include "Board.h"

#if (LD_ENABLE)

#include "sysinfo.h"

#include "drvGlobal.h"

#include "Utl.h"

#include "leddevice.h"

#include "mhal_ld.h"

#include "msAPI_LD.h"

#include "msAPI_LD_PWM.h"

#include "msAPI_Timer.h"


//================================================================================
// todo: Need refine
#define PANEL_WIDTH_NORMAL                  3840//1920
#define PANEL_HEIGHT_NORMAL                 2160//1080

//================================================================================

void LedDev_ConvertLedData_Algo_To_Phy(const U16* au16AlgoLedData, U16 u16AlgoLedNum, U16* au16PhyLedData, U16 u16PhyLedNum)
{
    if( u16AlgoLedNum != u16PhyLedNum )
    {
        // todo
        printf("\nWarning: u16AlgoLedNum != u16PhyLedNum!\n(%u, %u)\n", u16AlgoLedNum, u16PhyLedNum);
        /*
        for (PHY_idx = 0; PHY_idx < n_phys; PHY_idx++)
        {
            j = PHY_idx / phy_width;
            i = PHY_idx % phy_width;
            SPI_idx = (i/vir_to_phy_LED_ratio_H) + (j/vir_to_phy_LED_ratio_V)*led_width;
            PHY_blocks[PHY_idx] = SPI_blocks[SPI_idx];
        } */
    }
    else
    {
    #if 1
        memcpy( au16PhyLedData, au16AlgoLedData, u16PhyLedNum*2);

    #else
        U16 u16AlgoLedIdx = 0;
        U16 u16PhyLedIdx = 0;

        while ( u16PhyLedIdx < u16PhyLedNum)
        {
            au16PhyLedData[u16PhyLedIdx] = au16AlgoLedData[u16PhyLedIdx];

            u16AlgoLedIdx += 1;
            u16PhyLedIdx += 1;
        }
    #endif
    }

#if 0
    U8 i;
    printf("au16PhyLedData[]=");
    for( i = 0; i < u16PhyLedNum; ++ i )
    {
        printf("%X,", au16PhyLedData[i]);
    }
    printf("\n");
#endif

}

void LedDev_PhyLed_Adj(U16* au16PhyLedData, U16 u16PhyLedNum)
{
    // Debug mode for physical LED blocks
    U8 led_mod = MHal_LD_Get_SW_PulseMode();
    U16 led_id = MHal_LD_Get_SW_PulseId();
    U16 led_str = MHal_LD_Get_SW_PulseLEDIntensity();
    U16 ldb_str = MHal_LD_Get_SW_PulseLDBIntensity();

    U16 PHY_idx;


    if (led_mod == 0x7)     // 22[15:12]=4'b0111  real backlight (physical LED)
    {
        if (led_id == 0xfff)
        {
            for (PHY_idx = 0; PHY_idx < u16PhyLedNum; PHY_idx++)
                au16PhyLedData[PHY_idx] = 0xffff;
        }
        else if (led_id < u16PhyLedNum)
        {
            for (PHY_idx = 0; PHY_idx < u16PhyLedNum; PHY_idx++)
                au16PhyLedData[PHY_idx] = 0;
            au16PhyLedData[led_id] = 0xffff;
        }
    }
    else if (led_mod == 0x5)      // 22[15:12]=4'b0101 tunable real backlight (physical LED)
    {
        if (led_id == 0xfff)
        {
            for (PHY_idx = 0; PHY_idx < u16PhyLedNum; PHY_idx++)
                au16PhyLedData[PHY_idx] = (led_str << 8) | ldb_str;
        }
        else if (led_id < u16PhyLedNum)
        {
            for (PHY_idx = 0; PHY_idx < u16PhyLedNum; PHY_idx++)
                au16PhyLedData[PHY_idx] = 0;
            au16PhyLedData[led_id] = (led_str << 8) | ldb_str;
        }
    }
    /*
    else
    {
        if( MApi_LD_GetLDEnable() == FALSE )
        {
            for (PHY_idx = 0; PHY_idx < u16PhyLedNum; PHY_idx++)
                au16PhyLedData[PHY_idx] = 0xFFFF;
        }
    }*/
}


#if 0 //(LED_MULTI_SUPPORT_ENABLE)
    //Add LED_Device_XXX.c you want to support for multiple LED case
    #if(CustomerType == CustomerType_CMI_Ultrasonic)
    #include "LED_Device_INNO_65INCH_16X1.c"
    #include "LED_Device_INNO_65INCH_2X8.c"
    #include "LED_Device_INNO_65INCH_2X16.c"
    #include "LED_Device_INNO_75INCH_24X1.c"
    #elif(CustomerType == CustomerType_INX_Ubike)
    #include "LED_Device_INNO_50INCH_DIRECT_60.c"
    #include "LED_Device_INNO_50INCH_TB_12.c"
    #include "LED_Device_INNO_50INCH_TB_16.c"
    #elif(CustomerType == CustomerType_LG_Unicorn)
    #if((MS_BOARD_TYPE_SEL == BD_EAX65XX_URSA11_LGE_LM15_120)||(MS_BOARD_TYPE_SEL == BD_EAX65XX_URSA11_LGE_LM14A_120)||(MS_BOARD_TYPE_SEL == BD_EAX65XX_URSA11_LGE_M1A_120)||(MS_BOARD_TYPE_SEL == BD_EAX65XX_URSA11_LGE_LM14A_120_OLED))
    #include "LED_Device_LGE_INX_65INCH_DIRECT_120.c"
    #include "LED_Device_SHARP_70INCH_DIRECT_120.c"
   #elif ((MS_BOARD_TYPE_SEL == BD_EAX65XX_URSA11_LGE_M1A_60)||(MS_BOARD_TYPE_SEL ==BD_EAX65XX_URSA11_LGE_LM14A_60)||(MS_BOARD_TYPE_SEL == BD_EAX65XX_URSA11_LGE_LM15_60))
    //#include "LED_Device_LGE_INX_65INCH_DIRECT_120.c"
    //#include "LED_Device_SHARP_70INCH_DIRECT_120.c"
    #include "LED_Device_INX_40INCH_DIRECT_60.c"
    #include "LED_Device_CSOT_49INCH_DIRECT_60.c"
    #include "LED_Device_CSOT_55INCH_DIRECT_60.c"
    #include "LED_Device_AUO_49INCH_DIRECT_60.c"
    #include "LED_Device_LGE_INX_50INCH_DIRECT_60.c"
    #include "LED_Device_LGE_INX_58INCH_DIRECT_60.c"
    #endif
    #endif
#else

    #if(LED_DEVICE_SEL == LED_DEVICE_LG_65INCH_DIRECT_120)
        #include "LED_Device_LG_65INCH_DIRECT_120.c"
    #elif(LED_DEVICE_SEL == LED_DEVICE_SHARP_70INCH_DIRECT_120)
        #include "LED_Device_SHARP_70INCH_DIRECT_120.c"
    #elif(LED_DEVICE_SEL == LED_DEVICE_LGE_INX_65INCH_DIRECT_120)
        #include "LED_Device_LGE_INX_65INCH_DIRECT_120.c"
    #elif(LED_DEVICE_SEL == LED_DEVICE_INX_40INCH_DIRECT_60)
        #include "LED_Device_INX_40INCH_DIRECT_60.c"
    #elif(LED_DEVICE_SEL == LED_DEVICE_CSOT_49INCH_DIRECT_60)
        #include "LED_Device_CSOT_49INCH_DIRECT_60.c"
    #elif(LED_DEVICE_SEL == LED_DEVICE_CSOT_55INCH_DIRECT_60)
        #include "LED_Device_CSOT_55INCH_DIRECT_60.c"
    #elif(LED_DEVICE_SEL == LED_DEVICE_AUO_49INCH_DIRECT_60)
        #include "LED_Device_AUO_49INCH_DIRECT_60.c"
    #elif(LED_DEVICE_SEL == LED_DEVICE_INX_50INCH_DIRECT_60)
        #include "LED_Device_INNO_50INCH_DIRECT_60.c"
    #elif(LED_DEVICE_SEL == LED_DEVICE_INX_50INCH_TB_12)
        #include "LED_Device_INNO_50INCH_TB_12.c"
    #elif(LED_DEVICE_SEL == LED_DEVICE_INX_50INCH_TB_16)
        #include "LED_Device_INNO_50INCH_TB_16.c"
    #elif(LED_DEVICE_SEL == LED_DEVICE_INX_65INCH_16X1)
        #include "LED_Device_INNO_65INCH_16X1.c"
    #elif(LED_DEVICE_SEL == LED_DEVICE_INX_65INCH_2X8)
        #include "LED_Device_INNO_65INCH_2X8.c"
    #elif(LED_DEVICE_SEL == LED_DEVICE_INX_65INCH_2X16)
        #include "LED_Device_INNO_65INCH_2X16.c"
    #elif(LED_DEVICE_SEL == LED_DEVICE_INX_75INCH_24X1)
        #include "LED_Device_INNO_75INCH_24X1.c"
    #elif(LED_DEVICE_SEL == LED_DEVICE_LGE_INX_50INCH_DIRECT_60)
        #include "LED_Device_LGE_INX_50INCH_DIRECT_60.c"
    #elif(LED_DEVICE_SEL == LED_DEVICE_LGE_INX_58INCH_DIRECT_60)
        #include "LED_Device_LGE_INX_58INCH_DIRECT_60.c"
	#elif(LED_DEVICE_SEL == LED_DEVICE_SKY_50INCH_DIRECT_180)
		#include "LED_Device_SKY_50INCH_DIRECT_180.c"
    #elif(LED_DEVICE_SEL == LED_DEVICE_AS3820_2X7)
        #include "LED_Device_AS3820_2X7.c"
    #endif

#endif


t_sDrvLdCusPtrMap* g_LedDev_pstCurPtrMap = NULL;

t_sDrvLdCusPtrMap* LedDev_Get_CurPtrMap(void)
{
    if( g_LedDev_pstCurPtrMap == NULL )
    {
        printf("\nError: g_LedDev_pstCurPtrMap is NULL!\n");
    }

    return g_LedDev_pstCurPtrMap;
}

BOOL LedDev_Set_CurDevice(U8 u8LedDevId)
{
    PRINT_CURRENT_LINE();

    printf("LedDev_Set_CurDevice(u8LedDevId=0x%X)\n", u8LedDevId);

    u8LedDevId=u8LedDevId;

#if(LED_MULTI_SUPPORT_ENABLE)

??;
    switch(u8LedDevId)
    {
        default:
            break;
    }

#else

    g_LedDev_pstCurPtrMap = psLEDCusPtrMap ;

#endif

    return TRUE;
}

U8 LedDev_Get_PQ_LedWidth(void)
{
    if( g_LedDev_pstCurPtrMap == NULL )
    {
        return 0;
    }

    return g_LedDev_pstCurPtrMap->p_sDrvLdPQInfo->u8LEDWidth;
}

U8 LedDev_Get_PQ_LedHeight(void)
{
    if( g_LedDev_pstCurPtrMap == NULL )
    {
        return 0;
    }

    return g_LedDev_pstCurPtrMap->p_sDrvLdPQInfo->u8LEDHeight;
}

void LedDev_Config_OutputSignal_To_LED( U16 u16OutVFreqX10, BOOL is3D )
{
    PRINT_CURRENT_LINE();
    if( g_LedDev_pstCurPtrMap == NULL )
    {
        printf("\nError: g_LedDev_pstCurPtrMap is NULL!");
        return ;
    }

    g_LedDev_pstCurPtrMap->LED_DEVICE_Config_OutputSignal_To_LED( u16OutVFreqX10, is3D );

    //MDv_MFC_SetPWM5(u16OutVFreqX10);
}

void LedDev_Set_OutputSPI(const U16* pu16LedData)
{
    if( g_LedDev_pstCurPtrMap == NULL )
    {
        return;
    }

    g_LedDev_pstCurPtrMap->LED_DEVICE_SET_OutputSPI(pu16LedData);
}


#endif // LD_ENABLE

#undef _LED_DEVICE_C_

