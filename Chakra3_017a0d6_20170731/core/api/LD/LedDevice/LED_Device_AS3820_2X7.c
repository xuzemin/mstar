#ifndef _LED_Device_AS3820_2X7_C_
#define _LED_Device_AS3820_2X7_C_

#include "MsCommon.h"

#include "debug.h"

//#include "msReg.h"
//#include "drvGlobal.h"

#include "mdrv_mfc_spi.h"
#include "mdrv_ld.h"


//#include "drvPWM.h"
#include "msAPI_LD_PWM.h"

#include "LED_Device_AS3820_2X7.h"

#include "pq/LED_PQ_AS3820_2X7.c"

#include "msAPI_LD.h"



extern t_sDrvLdCusPtrMap sCusPtrMap;

//extern U16 LD_Phase[16];// = {0x4F03, 0xB003, 0x1100, 0x7200, 0xD300, 0x3401, 0x9501, 0xF601, 0x4F03, 0xB003, 0x1100, 0x7200, 0xD300, 0x3401, 0x9501, 0xF601};
//extern U16 LD_Duty[32];// = {0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403};
//extern U16 LD_Phase_2D[16];// = {0x4F03, 0xB003, 0x1100, 0x7200, 0xD300, 0x3401, 0x9501, 0xF601, 0x4F03, 0xB003, 0x1100, 0x7200, 0xD300, 0x3401, 0x9501, 0xF601};
//extern U16 LD_Duty_2D[32];// = {0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403};
//extern BOOL g_bLD_Duty_Force;// = FALSE;
//extern BOOL g_ld_2D_scanning;


#define PHY_LED_WIDTH   2
#define PHY_LED_HIGH    7
#define PHY_LED_NUM     (PHY_LED_WIDTH*PHY_LED_HIGH)


U16 g_LedDev_au16PhyLedData[PHY_LED_NUM];


StuDrvLdInfo s_DrvLdInfo_AS3820_2X7 =
{
    /* System Basic */
    LD_PQ_STAGE, // EnuLD_DEVELOPE_STAGE eStage;

    // PANEL
    PANEL_WIDTH_NORMAL, PANEL_HEIGHT_NORMAL, // U16 u16PanelWidth, u16PanelHeight; // Panel width & height
    //for 2x7 LEDs
    PHY_LED_WIDTH, PHY_LED_HIGH,
    8, 5, // U8 u8DMAWidth, u8DMAHeight; // DMA width & height

    ((LOCAL_DIMMING_MEMORY_TYPE & MIU1) ?(LOCAL_DIMMING_ADR|MIU_INTERVAL) : LOCAL_DIMMING_ADR), // U32 u32BaseAddr; // DRAM base address for LD

    // SPI
    FALSE, //BOOL bBacklightGlobeMode; // DMA output data non-8bit enable
    0x10, //U8 u8BacklightGlobeGain;  // DMA output data gain
    0, //U8 u8BacklightGlobeAlign; // DMA output data 0:16b  1:12b  2:4b  3:10b
    MSPI_CLK_SPD_72M,
    MSPI_CLK_SPD__DIV_8, // eMSPIClockSpeed
    0,//1, // u8SpiClockPolarity
    0, // u8SpiClockPhase
    0, // u8Time_FromTriggerToFirstClock;  // The time from "reg_mspi_trigger" to first SPI clock.     0 => Delay 1 MSPI clock
    0, // u8Time_LastClockToDone;    // The time from last SPI clock to "reg_mspi_done_flag"     0 => Delay 1 MSPI clock
    0, // u8Time_BetweenByteToByte;  // The time between byte to byte transfer       0 => Delay 0 MSPI clock
    0, // u8Time_FromWriteToRead;    // The time between last write and first read   0 => Delay 0 MSPI clock
    0, // u8SpiTime_VSyncWidth
    0, // u8SpiTime_VSync_To_FirstClock
    MSPI_PORT_NUM,
    0, // SPI Command length
    8, //u8SpiDataBit
    {NULL}, // SPI Command
    0, // u8CheckSumMode
    16, //LDM DMA transfer bit per one pack

    /* PQ Basic */

};

t_sDrvLdCusPtrMap sCusPtrMap_LED_AS3820_2X7=
{
    &s_DrvLdInfo_AS3820_2X7,
    &s_DrvLdPQInfo_AS3820_2X7,
    LED_AS3820_2X7_Config_OutputSignal_To_LED,
    NULL,
    NULL,
    LED_AS3820_2X7_Set_OutputSPI_Signal,
};

#if (LED_MULTI_SUPPORT_ENABLE == 0)
t_sDrvLdCusPtrMap * psLEDCusPtrMap = &sCusPtrMap_LED_AS3820_2X7;
#endif

//t_LD_Signal ld_pwm_AS3820_2X7[(U8)PWM_NUMS]={{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};

//extern void MDv_MFC_SetPWM5(U16 u16OutVFreqX10);
void _LED_AS3820_2X7_Set_OutputCS(U16 u16OutVFreqX10, BOOL Is3D)
{
#if 1
    u16OutVFreqX10=u16OutVFreqX10;
    Is3D=Is3D;

#else
    t_LD_Signal OutputSignal;

    if(Is3D)
    {
        if (u16OutVFreqX10 < 1300) // 3D 120Hz output, FHD 120Hz FI input
        {
        MDrv_MFC_PWM_waveform_maker(LD_TPV6688_2X7_CS_PWM_CH_SEL, u16OutVFreqX10, LD_TPV6688_2X7_CS_3D_120Hz_PWM_DUTYx100,
                                    LD_TPV6688_2X7_CS_3D_120Hz_PWM_SHIFTx100, LD_TPV6688_2X7_CS_3D_120Hz_PWM_DIV, 0,
                                    Vsync_DoubleBF, PWM_RST_CTRL__VSYNC, LD_TPV6688_2X7_CS_3D_120Hz_PWM_POLARITY);
        }
        else // 3D 240Hz output
        {
            MDrv_MFC_PWM_waveform_maker(LD_TPV6688_2X7_CS_PWM_CH_SEL, u16OutVFreqX10, LD_TPV6688_2X7_CS_3D_240Hz_PWM_DUTYx100,
                                        LD_TPV6688_2X7_CS_3D_240Hz_PWM_SHIFTx100, LD_TPV6688_2X7_CS_3D_240Hz_PWM_DIV, 0,
                                        Vsync_DoubleBF, PWM_RST_CTRL__VSYNC, LD_TPV6688_2X7_CS_3D_240Hz_PWM_POLARITY);
        }
    }
    else
    {
        if (u16OutVFreqX10 <= 1100) // 2D 100Hz output
        {
            MDrv_MFC_PWM_waveform_maker(LD_TPV6688_2X7_CS_PWM_CH_SEL, u16OutVFreqX10, LD_TPV6688_2X7_CS_2D100Hz_PWM_DUTYx100,
                                        LD_TPV6688_2X7_CS_2D100Hz_PWM_SHIFTx100, LD_TPV6688_2X7_CS_2D100Hz_PWM_DIV, 0,
                                        Vsync_DoubleBF, PWM_RST_CTRL__VSYNC, LD_TPV6688_2X7_CS_2D100Hz_PWM_POLARITY);
        }
        else if ((u16OutVFreqX10 > 1100) && (u16OutVFreqX10 <= 1300)) // 2D 120Hz output
        {
            MDrv_MFC_PWM_waveform_maker(LD_TPV6688_2X7_CS_PWM_CH_SEL, u16OutVFreqX10, LD_TPV6688_2X7_CS_2D120Hz_PWM_DUTYx100,
                                        LD_TPV6688_2X7_CS_2D120Hz_PWM_SHIFTx100, LD_TPV6688_2X7_CS_2D120Hz_PWM_DIV, 0,
                                        Vsync_DoubleBF, PWM_RST_CTRL__VSYNC, LD_TPV6688_2X7_CS_2D120Hz_PWM_POLARITY);
        }
        else //if (u16OutVFreqX10 > 1300) // 2D 240Hz output
        {
            MDrv_MFC_PWM_waveform_maker(LD_TPV6688_2X7_CS_PWM_CH_SEL, u16OutVFreqX10, LD_TPV6688_2X7_CS_2D240Hz_PWM_DUTYx100,
                                        LD_TPV6688_2X7_CS_2D240Hz_PWM_SHIFTx100, LD_TPV6688_2X7_CS_2D240Hz_PWM_DIV, 0,
                                        Vsync_DoubleBF, PWM_RST_CTRL__VSYNC, LD_TPV6688_2X7_CS_2D240Hz_PWM_POLARITY);
        }
    }

    MHal_PWM_WaveformResetEnable(LD_TPV6688_2X7_CS_PWM_CH_SEL, ENABLE);

    MHal_PWM_OutputEn(LD_TPV6688_2X7_CS_PWM_CH_SEL, ENABLE);

    MDrv_PWM_Set_PadEn( LD_TPV6688_2X7_CS_PWM_CH_SEL, ENABLE );

    OutputSignal.PWM_CH = (U8) LD_TPV6688_2X7_CS_PWM_CH_SEL;
    OutputSignal.CurSysOutVFreqX10 = u16OutVFreqX10;
    OutputSignal.SyncRstCnt = 0 ;
    _LED_TPV6688_2X7_Set_OutputPWMData(OutputSignal.PWM_CH, OutputSignal);

#endif
}

/*
void  _LED_AS3820_2X7_Set_OutputPWMData(U8 ch, t_LD_Signal OutputSignal)
{
    if(ch >= (U8)PWM_NUMS)
    {
        printf("%sLED  error : %s() ; ln%d%s\n",KRED,__FUNCTION__,__LINE__,KNRM);
        return ;
    }

    ld_pwm_AS3820_2X7[ch].PWM_CH = OutputSignal.PWM_CH;
    ld_pwm_AS3820_2X7[ch].CurSysOutVFreqX10 = OutputSignal.CurSysOutVFreqX10;
    ld_pwm_AS3820_2X7[ch].SyncRstCnt = OutputSignal.SyncRstCnt;
}
*/

/*
void _LED_AS3820_2X7_Set_SpiClk_Delay_FromVsync(U16 u16OutVFreqX10, BOOL Is3D)
{
    UNUSED(u16OutVFreqX10);
    if(Is3D)
    {
        MDrv_LD_SetSpiClkDelayFromVsync(LD_AS3820_2X7_PERIOD_3D_SCLK_TO_VSYNC);//hardcode refine 20150310
    }
    else
    {
        MDrv_LD_SetSpiClkDelayFromVsync(LD_AS3820_2X7_PERIOD_2D_SCLK_TO_VSYNC);//hardcode refine 20150310
    }
}*/

void LED_AS3820_2X7_Config_OutputSignal_To_LED(U16 u16OutVFreqX10, BOOL Is3D)
{
#if 1
    u16OutVFreqX10=u16OutVFreqX10;
    Is3D=Is3D;

    //MDrv_LDM_DMA_Set_TrigDelay(LD_AS3820_2X7_PERIOD_2D_SCLK_TO_VSYNC);

#else
 //   _LED_DEVICE_Set_OutputVFreq(u16OutVFreqX10,Is3D);
    _LED_TPV6688_2X7_Set_OutputCS(u16OutVFreqX10,Is3D);
    _LED_TPV6688_2X7_Set_SpiClk_Delay_FromVsync(u16OutVFreqX10,Is3D);
#endif
}

void LED_AS3820_2X7_Set_OutputSPI_Signal(const U16* SPI_blocks)
{
    //U16 PHY_blocks[LD_MAX_BLOCK_SIZE];

    //const int vir_to_phy_LED_ratio_H = 1;
    //const int vir_to_phy_LED_ratio_V = 1;

    //U16 SPI_idx = 0, PHY_idx = 0, i = 0, j = 0;


    // Re-arrange virtual LED blocks into physical LED blocks
    //U16 led_width = psDrvLdInfo->u8LEDNumW;
    //U16 led_height = MHal_LD_Get_LED_BacklightHeight();

    //U16 phy_width = led_width * vir_to_phy_LED_ratio_H;
    //U16 phy_height = led_height * vir_to_phy_LED_ratio_V;
    //U16 n_phys = phy_width * phy_height;



// Comment by Daniel
  /*
    if(gSysConfig.u8MirrorMode == MIRROR_H_MODE)
    {
        for (PHY_idx = 0; PHY_idx < n_phys; PHY_idx++)
        {
            j = PHY_idx / phy_width;
            i = PHY_idx % phy_width;
            SPI_idx = ((led_width-1)-(i/vir_to_phy_LED_ratio_H)) + (j/vir_to_phy_LED_ratio_V)*led_width;
            PHY_blocks[PHY_idx] = SPI_blocks[SPI_idx];
        }
    }
    else */

#if 0
    {
        for (PHY_idx = 0; PHY_idx < n_phys; PHY_idx++)
        {
            j = PHY_idx / phy_width;
            i = PHY_idx % phy_width;
            SPI_idx = (i/vir_to_phy_LED_ratio_H) + (j/vir_to_phy_LED_ratio_V)*led_width;
            PHY_blocks[PHY_idx] = SPI_blocks[SPI_idx];
        }
    }
#endif


    U16 u16AlgoLedNum = LedDev_Get_PQ_LedWidth()*LedDev_Get_PQ_LedHeight();
    //printf("u16AlgoLedNum=%u\n", u16AlgoLedNum);

    LedDev_ConvertLedData_Algo_To_Phy(SPI_blocks, u16AlgoLedNum, g_LedDev_au16PhyLedData, PHY_LED_NUM );

    /* DO NOT MODIFY THE CODE BELOW!! */
    LedDev_PhyLed_Adj(g_LedDev_au16PhyLedData, PHY_LED_NUM);


    /* PACK PHY_blocks INTO DRAM on your own!! */

    #if 1

        U16 header_data1 = 0x00BF;
        U16 header_data2 = PHY_LED_NUM*2; //14*2=28=0x1C
        U16 header_data3 = 0x0037;
        U16 data_array[3+(PHY_LED_NUM*2)]={0};

        data_array[0]= header_data1;
        data_array[1]= header_data2;
        data_array[2]= header_data3;
        U8 array_idx =3;

        U16 u16LedIdx;
        for(u16LedIdx = 0; u16LedIdx < PHY_LED_NUM; u16LedIdx ++ )
        {
            //printf(" LD value = %x \n",PHY_blocks[i]);
            data_array[array_idx]=((g_LedDev_au16PhyLedData[u16LedIdx]&0x0ff0)>>4); //12 bit
            array_idx++;

            data_array[array_idx]=((g_LedDev_au16PhyLedData[u16LedIdx]&0xf000)>>12);//12 bit
            array_idx++;
        }


        // Set menuload number
        MDrv_LDM_DMA_SetMenuloadNumber(array_idx);

        //
        MDrv_LDM_DMA_Set_DMA0_Datas( array_idx, data_array, FALSE, FALSE);

        // Trigger
        MDrv_LDM_DMA_SetSpiTriggerMode(E_LDM_SPI_TRIGER_EVERY_V_SYNC);

    #endif

}

#if 0 //from Funai
typedef struct
{
    U8 u8DevIdx:3;    // 1~n
    U8 u8PwmChIdx:5;  // 1~16
}LED_ASSIGNMENT;
typedef enum
{
    EN_AS3820_STATE_WAIT,
    EN_AS3820_STATE_UNLOCK,
    EN_AS3820_STATE_INIT1,
    EN_AS3820_STATE_INIT2,
    EN_AS3820_STATE_LOCK,
    EN_AS3820_STATE_RUNNING,
}EN_AS3820_STATE;

code LED_ASSIGNMENT LED_ARRAY_49W[] =
{
    {1,1},{1,9},  {2,9}, {2,1},
    {1,2},{1,10}, {2,10},{2,2},
    {1,3},{1,11}, {2,11},{2,3},
    {1,4},{1,12}, {2,12},{2,4},
    {1,5},{1,13}, {2,13},{2,5},
};

code LED_ASSIGNMENT LED_ARRAY_55W[] =
{
    {1,1},{1,9},  {2,9}, {2,1},
    {1,2},{1,10}, {2,10},{2,2},
    {1,3},{1,11}, {2,11},{2,3},
    {1,4},{1,12}, {2,12},{2,4},
    {1,5},{1,13}, {2,13},{2,5},
    {1,6},{1,14}, {2,14},{2,6},
};

code LED_ASSIGNMENT LED_ARRAY_FULL[] =
{
    {1,1},{1,9},  {2,9}, {2,1},
    {1,2},{1,10}, {2,10},{2,2},
    {1,3},{1,11}, {2,11},{2,3},
    {1,4},{1,12}, {2,12},{2,4},
    {1,5},{1,13}, {2,13},{2,5},
    {1,6},{1,14}, {2,14},{2,6},
    {1,7},{1,15}, {2,15},{2,7},
    {1,8},{1,16}, {2,16},{2,8},
};


EN_AS3820_STATE eAS3820State = EN_AS3820_STATE_WAIT;
extern BOOLEAN g_bIsLdRunning;

void MSPI_WriteFrame(U8 ucDataNum, U8 *pusData)
{
    U8  i;
    U8 u8Temp;

    DRV_MSPI_ChipSelect(true);

#ifdef DeMorgonWoModify
    MDrv_gpio_set_low(111);
#endif

    //write Indicators.
    for(i=0; i<ucDataNum; i++)
    {
        u8Temp = pusData[i];
        DRV_MSPI_Write(&u8Temp,1);
    }

#ifdef DeMorgonWoModify
    MDrv_gpio_set_high(111);
#endif

    DRV_MSPI_ChipSelect(false);
}

static void MSPI_LD_Write_State(void)
{
    switch (eAS3820State)
    {
        case EN_AS3820_STATE_WAIT:
            if (MDrv_TIMER_GetTime0() > 800)//Defect #30643: About the timing to which AS3820 setting data is sent.
            {
                eAS3820State = EN_AS3820_STATE_UNLOCK;
            }
            break;
        case EN_AS3820_STATE_UNLOCK:
            AS3820Unlock();
            eAS3820State = EN_AS3820_STATE_INIT1;
            break;
        case EN_AS3820_STATE_INIT1:
            AS3820Init();
            eAS3820State = EN_AS3820_STATE_INIT2;
            break;
        case EN_AS3820_STATE_INIT2:
            AS3820Init2();
            eAS3820State = EN_AS3820_STATE_LOCK;
            break;
        case EN_AS3820_STATE_LOCK:
            AS3820Lock();
            eAS3820State = EN_AS3820_STATE_RUNNING;
            break;
        default:
        case EN_AS3820_STATE_RUNNING:
            if (g_bIsLdRunning)
            {
                AS3820WritePWM(spi_data);
                g_bIsLdRunning = FALSE;
            }
            break;
    }
}

void MSPI_PWM_Interupt_ForVsync(void)
{
    U16 u16IntStatus ;

    u16IntStatus = Read2Byte(PWM5_INTERRUPT_STATUS);

    if( u16IntStatus & BIT11||  u16IntStatus & BIT13)
    {
        MSPI_LD_Write_State();
        if(u16IntStatus & BIT11)
            Write2Byte(PWM5_INTERRUPT_STATUS, BIT11); //clear (Write 1; auto clear)
        else if(u16IntStatus & BIT13)
            Write2Byte(PWM5_INTERRUPT_STATUS, BIT13); //clear (Write 1; auto clear)
    }
}
#endif

void AS3820Unlock(void)
{
    U16 au16Buffer[] = {0x00C0, 0x0036, 0x00CA};

    MDrv_LDM_DMA_Set_DMA0_Datas( sizeof(au16Buffer)/2, au16Buffer, TRUE, TRUE);
}

void AS3820Lock(void)
{
    U16 u16Buffer[] = {0x00C0, 0x0036, 0x00AC};

    MDrv_LDM_DMA_Set_DMA0_Datas( sizeof(u16Buffer)/2, u16Buffer, TRUE, TRUE);
}

#define PWMPeriod   0x0FFF

void AS3820Init(void)
{
    U16 au16Buffer[] =
    {
        0x0080,0x0035,0x0001,
        // CUR_ON_1
        0x00FF,0x00FF,0x00BF,0x0024,0x0000,0x00FF,0x0020,0x0000,0x0000,0x0000,0x0000, //0x01~0x0B
        0x0073,0x0001,0x00FF,0x00FF,0x0000,0x0000,0x0005,0x0003, (PWMPeriod&0x00FF),(PWMPeriod>>8), //0x0C~0x15

        // PWM1delLSB
        0x0054,0x0001,0x0048,0x0003,0x003C,0x0005,0x0030,0x0007,0x0024,0x0009,0x0018,0x000B,0x000C,0x000D,0x0000,0x00DF,

        // PWM9delLSB
        0x0054,0x0001,0x0048,0x0003,0x003C,0x0005,0x0030,0x0007,0x0024,0x0009,0x0018,0x000B,0x000C,0x000D,0x0000,0x00DF,
    };

    MDrv_LDM_DMA_Set_DMA0_Datas(sizeof(au16Buffer)/2, au16Buffer, TRUE, TRUE);
}

void AS3820Init2(void)
{
    U16 au16Buffer[] =
    {
        0x0080,0x002A,0x0037,
        // PWM1htLSB
        0x00AA,0x0005,0x00AA,0x0005,0x00AA,0x0005,0x00AA,0x0005,0x00AA,0x0005,0x00AA,0x0005,0x00AA,0x0005,0x00AA,0x0005,
        0x00AA,0x0005,0x00AA,0x0005,0x00AA,0x0005,0x00AA,0x0005,0x00AA,0x0005,0x00AA,0x0005,0x00AA,0x0005,0x00AA,0x0005,
        // ASICIDLSB
        0x00A0,0x0020,
        // 0x59~0x5F not used
        0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
        // STATUS
        0x0000,0x0000,0x0000,0x0002,0x00FF,0x0013,
    };

    MDrv_LDM_DMA_Set_DMA0_Datas(sizeof(au16Buffer)/2, au16Buffer, TRUE, TRUE);
}

BOOLEAN LedDev_Init(void)
{
//    PRINT_CURRENT_LINE();
    MDrv_LDM_DMA_Set_TrigDelay(LD_AS3820_2X7_PERIOD_2D_SCLK_TO_VSYNC);

    AS3820Unlock();

    AS3820Init();

    AS3820Init2();

    AS3820Lock();

    return TRUE;
}

#endif
