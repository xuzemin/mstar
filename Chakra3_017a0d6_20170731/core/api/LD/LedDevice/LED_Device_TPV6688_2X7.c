#ifndef _LED_Device_TPV6688_2X7_C_
#define _LED_Device_TPV6688_2X7_C_

#include "mdrv_mfc_spi.h"
#include "mdrv_ld.h"
#include "drvGlobal.h"
#include "msReg.h"
//#include "drvPWM.h"
#include "msAPI_LD_PWM.h"
#include "MsCommon.h"
#include "LED_Device_TPV6688_2X7.h"
#include "debug.h"
#include "pq/LED_PQ_TPV6688_2X7.c"

#include "msAPI_LD.h"



extern t_sDrvLdCusPtrMap sCusPtrMap;

//#include "mdrv_mfc_3d.h"
//#include "System.h"
//#include "mapp_customer.h"

extern U16 LD_Phase[16];// = {0x4F03, 0xB003, 0x1100, 0x7200, 0xD300, 0x3401, 0x9501, 0xF601, 0x4F03, 0xB003, 0x1100, 0x7200, 0xD300, 0x3401, 0x9501, 0xF601};
extern U16 LD_Duty[32];// = {0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403};

extern U16 LD_Phase_2D[16];// = {0x4F03, 0xB003, 0x1100, 0x7200, 0xD300, 0x3401, 0x9501, 0xF601, 0x4F03, 0xB003, 0x1100, 0x7200, 0xD300, 0x3401, 0x9501, 0xF601};
extern U16 LD_Duty_2D[32];// = {0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403};
extern BOOL g_bLD_Duty_Force;// = FALSE;
extern BOOL g_ld_2D_scanning;

StuDrvLdInfo s_DrvLdInfo_TPV6688_2X7 =
{
    /* System Basic */
    LD_PQ_STAGE, // EnuLD_DEVELOPE_STAGE eStage;

    // PANEL
    PANEL_WIDTH_NORMAL, PANEL_HEIGHT_NORMAL, // U16 u16PanelWidth, u16PanelHeight; // Panel width & height
    //for 2x7 LEDs
    2, 7,
    8, 3, // U8 u8DMAWidth, u8DMAHeight; // DMA width & height

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
    {0x00}, // SPI Command
    0, // u8CheckSumMode
    16, //LDM DMA transfer bit per one pack

    /* PQ Basic */

};

t_sDrvLdCusPtrMap sCusPtrMap_LED_TPV6688_2X7=
{
    &s_DrvLdInfo_TPV6688_2X7,
    &s_DrvLdPQInfo_TPV6688_2X7,
    LED_TPV6688_2X7_Config_OutputSignal_To_LED,
    NULL,
    NULL,
    LED_TPV6688_2X7_Set_OutputSPI_Signal,
};

#if (LED_MULTI_SUPPORT_ENABLE == 0)
t_sDrvLdCusPtrMap * psLEDCusPtrMap = &sCusPtrMap_LED_TPV6688_2X7;
#endif

t_LD_Signal ld_pwm_TPV6688_2X7[(U8)PWM_NUMS]={{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};

//extern void MDv_MFC_SetPWM5(U16 u16OutVFreqX10);
void _LED_TPV6688_2X7_Set_OutputCS(U16 u16OutVFreqX10, BOOL Is3D)
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

void  _LED_TPV6688_2X7_Set_OutputPWMData(U8 ch, t_LD_Signal OutputSignal)
{
    if(ch >= (U8)PWM_NUMS)
    {
        printf("%sLED  error : %s() ; ln%d%s\n",KRED,__FUNCTION__,__LINE__,KNRM);
        return ;
    }

    ld_pwm_TPV6688_2X7[ch].PWM_CH = OutputSignal.PWM_CH;
    ld_pwm_TPV6688_2X7[ch].CurSysOutVFreqX10 = OutputSignal.CurSysOutVFreqX10;
    ld_pwm_TPV6688_2X7[ch].SyncRstCnt = OutputSignal.SyncRstCnt;
}

void _LED_TPV6688_2X7_Set_SpiClk_Delay_FromVsync(U16 u16OutVFreqX10, BOOL Is3D)
{
    UNUSED(u16OutVFreqX10);
    if(Is3D)
    {
        MDrv_LD_SetSpiClkDelayFromVsync(LD_TPV6688_2X7_PERIOD_3D_SCLK_TO_VSYNC);//hardcode refine 20150310
    }
    else
    {
        MDrv_LD_SetSpiClkDelayFromVsync(LD_TPV6688_2X7_PERIOD_2D_SCLK_TO_VSYNC);//hardcode refine 20150310
    }
}

void LED_TPV6688_2X7_Config_OutputSignal_To_LED(U16 u16OutVFreqX10, BOOL Is3D)
{
#if 1
    u16OutVFreqX10=u16OutVFreqX10;
    Is3D=Is3D;

#else
 //   _LED_DEVICE_Set_OutputVFreq(u16OutVFreqX10,Is3D);
    _LED_TPV6688_2X7_Set_OutputCS(u16OutVFreqX10,Is3D);
    _LED_TPV6688_2X7_Set_SpiClk_Delay_FromVsync(u16OutVFreqX10,Is3D);
#endif
}

U8 LED_TPV6688_2X7_Get_LDLedNum(void)
{
#if 1 // Daniel
    return 14;
#else
    return gCusInxVar.enLDLedNum;
#endif
}

#define DEBUG_SPI(x)    //x

void  LED_TPV6688_2X7_Set_OutputSPI_Signal(const U16* SPI_blocks)
{
    U16 PHY_blocks[LD_MAX_BLOCK_SIZE];
    const int vir_to_phy_LED_ratio_H = 1;
    const int vir_to_phy_LED_ratio_V = 1;

    U16 SPI_idx = 0, PHY_idx = 0, i = 0, j = 0;
    //U32 addr_base = MHal_LD_Get_SPI_BufBaseAddr();

    // Re-arrange virtual LED blocks into physical LED blocks
    U16 led_width = psDrvLdInfo->u8LEDNumW;
    U16 led_height = MHal_LD_Get_LED_BacklightHeight();
    U16 phy_width = led_width * vir_to_phy_LED_ratio_H;
    U16 phy_height = led_height * vir_to_phy_LED_ratio_V;
    U16 n_phys = phy_width * phy_height;

#if 0
    for (PHY_idx = 0; PHY_idx < n_phys; PHY_idx++)
    {
        j = PHY_idx / phy_width;
        i = PHY_idx % phy_width;
        SPI_idx = (i/vir_to_phy_LED_ratio_H) + (j/vir_to_phy_LED_ratio_V)*led_width;
        PHY_blocks[PHY_idx] = SPI_blocks[SPI_idx];
    }
#else

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


    /* DO NOT MODIFY THE CODE BELOW!! */

    // Debug mode for physical LED blocks
    U8 led_mod = MHal_LD_Get_SW_PulseMode();
    U16 led_id = MHal_LD_Get_SW_PulseId();
    U16 led_str = MHal_LD_Get_SW_PulseLEDIntensity();
    U16 ldb_str = MHal_LD_Get_SW_PulseLDBIntensity();
    if (led_mod == 0x7)     // 22[15:12]=4'b0111  real backlight (physical LED)
    {
        if (led_id == 0xfff)
        {
            for (PHY_idx = 0; PHY_idx < n_phys; PHY_idx++)
                PHY_blocks[PHY_idx] = 0xffff;
        }
        else if (led_id < n_phys)
        {
            for (PHY_idx = 0; PHY_idx < n_phys; PHY_idx++)
                PHY_blocks[PHY_idx] = 0;
            PHY_blocks[led_id] = 0xffff;
        }
    }
    else if (led_mod == 0x5)      // 22[15:12]=4'b0101 tunable real backlight (physical LED)
    {
        if (led_id == 0xfff)
        {
            for (PHY_idx = 0; PHY_idx < n_phys; PHY_idx++)
                PHY_blocks[PHY_idx] = (led_str << 8) | ldb_str;
        }
        else if (led_id < n_phys)
        {
            for (PHY_idx = 0; PHY_idx < n_phys; PHY_idx++)
                PHY_blocks[PHY_idx] = 0;
            PHY_blocks[led_id] = (led_str << 8) | ldb_str;
        }
    }

    if(gu8LDEnable==0)
        {
            for (PHY_idx = 0; PHY_idx < n_phys; PHY_idx++)
                PHY_blocks[PHY_idx] = 0xFFFF;
        }


    /* PACK PHY_blocks INTO DRAM on your own!! */

    #if 0
    U16 DMA_idx = 0;
    BOOL is3D = IS3DMODE();
    DMA_idx = 0;
    for (j = 0; j < 2; j++)
    {
        for (i = 0; i < 8; i++)
        {
            PHY_idx = i + j*phy_width;
            if (is3D)
                MDrv_LD_MIUWrite2Bytes(addr_base, DMA_idx + 2*i, LD_Duty[0]);
            else if (g_bLD_Duty_Force)
                MDrv_LD_MIUWrite2Bytes(addr_base, DMA_idx + 2*i, LD_Duty[PHY_idx]);
            else
                MDrv_LD_MIUWrite2Bytes(addr_base, DMA_idx + 2*i, PHY_blocks[PHY_idx] >> 4);
        }
        DMA_idx += pack_length; // 16-bit
    }
    for (i = 0; i < 8; i++)
        MDrv_LD_MIUWrite2Bytes(addr_base, DMA_idx + 2*i, LD_Phase[i]);


    #else
        #define LD_DMA_LINE_SIZE 32
        //U16 * pSPIout= (U16 *)( addr_base+0x80000000);
        //U16 duty_data = 0x8000;
        //U16 doublebytes[2];
        U16 header_data1 = 0x00BF;
        U16 header_data2 = 0x001C;
        U16 header_data3 = 0x0037;
        U16 data_array[3+(14*2)]={0};

        data_array[0]= header_data1;
        data_array[1]= header_data2;
        data_array[2]= header_data3;
        U8 array_idx =3;

        for(i=0;i<(s_DrvLdInfo_TPV6688_2X7.u8LEDNumW)*(s_DrvLdInfo_TPV6688_2X7.u8LEDNumH);i++)
        {
            DEBUG_SPI( printf(" LD value = %x \n",PHY_blocks[i]); );

            data_array[array_idx]=((PHY_blocks[i]&0x0ff0)>>4);
            array_idx++;
            data_array[array_idx]=((PHY_blocks[i]&0xf000)>>12);
            array_idx++;
        }

#if 0 //debug
        int k;
        for(k=0;k<array_idx;k++)
        {
            printf("\nconvert_data[%d]=0x%x\n",k,data_array[k]);
        }
#endif

    #if 1

        // Set menuload number
        MDrv_LDM_DMA_SetMenuloadNumber(array_idx);

        //
        MDrv_LDM_DMA_Set_DMA0_Datas( array_idx, data_array, FALSE, FALSE);

        // Trigger
        MDrv_LDM_DMA_SetSpiTriggerMode(E_LDM_SPI_TRIGER_EVERY_V_SYNC);


    #else

        for(i=0;i<array_idx;i++)
        {
            MDrv_LDM_DMA_Set_DMA0_Data(i,data_array[i]);

            if(i>=LD_MAX_BLOCK_SIZE)
            {
                printf("%s[%s][%d]PHY_blocks index %d is out of range%s\n", KRED, __FUNCTION__, __LINE__, i, KNRM);
                return;
            }
        }
    #endif


#if 0 //evie
        j = 0;
        for(;i<(s_DrvLdInfo_TPV6688_2X7.u8DMAWidth)*(s_DrvLdInfo_TPV6688_2X7.u8DMAHeight);i++)
        {
            if((i%s_DrvLdInfo_TPV6688_2X7.u8DMAWidth)==0)
            {
                pSPIout = (U16 *)(addr_base+LD_DMA_LINE_SIZE*(i/s_DrvLdInfo_TPV6688_2X7.u8DMAWidth)+0x80000000) ;
            }
            else
            {
                pSPIout++;
            }

            if(j>=LD_MAX_BLOCK_SIZE)
            {
                printf("%s[%s][%d]LD_Phase index %d is out of range%s\n", KRED, __FUNCTION__, __LINE__, i, KNRM);
                return;
            }
            *(pSPIout) = LD_Phase[j];
            j++;
        }

#endif
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
    U16 u16Buffer[] = {0x00C0, 0x0036, 0x00CA, 0x0000};

#if 1
    MDrv_LDM_DMA_Set_DMA0_Datas( sizeof(u16Buffer)/2, u16Buffer, TRUE, TRUE);
#else
    U16 i;

    for(i=0;i<4;i++)
    {
        MDrv_LDM_DMA_Set_DMA0_Data(i,u16Buffer[i]);
    }
#endif
}
void AS3820Lock(void)
{
    U16 u16Buffer[] = {0x00C0, 0x0036, 0x00AC, 0x0000};

#if 1
    MDrv_LDM_DMA_Set_DMA0_Datas( sizeof(u16Buffer)/2, u16Buffer, TRUE, TRUE);
#else

    U16 i;
    for(i=0;i<4;i++)
    {
        MDrv_LDM_DMA_Set_DMA0_Data(i,u16Buffer[i]);
    }
#endif
}

#define PWMPeriod   0x03FC

void AS3820Init(void)
{
/*
    U8 u8Buffer[] =
    {
        0x80,0x35,0x01,
        // CUR_ON_1
        0x3F,0x3F,0xBF,0x24,0x00,0xFF,0x20,0x00,0x00,0x00,0x00,
        0x92,0x00,0x3F,0x3F,0x00,0x00,0x05,0x03,(PWMPeriod&0xFF),(PWMPeriod>>8),
        // PWM1delLSB
        0x54,0x01,0xFC,0x03,0xA4,0x06,0x4C,0x09,0xF4,0x0B,0x9C,0x0E,0x00,0x00,0x00,0x00,
        // PWM9delLSB
        0x54,0x01,0xFC,0x03,0xA4,0x06,0x4C,0x09,0xF4,0x0B,0x9C,0x0E,0x00,0x00,0x00,0x00,
        0x00,
    };
*/
    U16 u16Buffer[] =
    {
        0x0080,0x0035,0x0001,
        // CUR_ON_1
        0x003F,0x003F,0x00BF,0x0024,0x0000,0x00FF,0x0020,0x0000,0x0000,0x0000,0x0000,//0x01~0x0B
        0x0092,0x0000,0x003F,0x003F,0x0000,0x0000,0x0005,0x0003,(PWMPeriod&0x00FF),(PWMPeriod>>8),//0x0C~0x15
        // PWM1delLSB
        0x0054,0x0001,0x00FC,0x0003,0x00A4,0x0006,0x004C,0x0009,0x00F4,0x000B,0x009C,0x000E,0x0000,0x0000,0x0000,0x0000,
        // PWM9delLSB
        0x0054,0x0001,0x00FC,0x0003,0x00A4,0x0006,0x004C,0x0009,0x00F4,0x000B,0x009C,0x000E,0x0000,0x0000,0x0000,0x0000,
        0x0000,
    };

#if 1
    MDrv_LDM_DMA_Set_DMA0_Datas(sizeof(u16Buffer)/2, u16Buffer, TRUE, TRUE);
#else

    U16 i;
    for(i=0;i<sizeof(u16Buffer)/sizeof(u16Buffer[0]);i++)
    {
        MDrv_LDM_DMA_Set_DMA0_Data(i,u16Buffer[i]);
    }
#endif
}

void AS3820Init2(void)
{
// according to Funai_AS3820 register map
/*
    U8 u8Buffer[] =
    {
        0x80,0x2F,0x37,
        // PWM1htLSB
        0xFF,0x0F,0xFF,0x0F,0xFF,0x0F,0xFF,0x0F,0xFF,0x0F,0xFF,0x0F,0x00,0x00,0x00,0x00,
        0xFF,0x0F,0xFF,0x0F,0xFF,0x0F,0xFF,0x0F,0xFF,0x0F,0xFF,0x0F,0x00,0x00,0x00,0x00,
        // ASICIDLSB
        0xA0,0x20,
        // 0x59~0x5F not used
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        // STATUS
        0x00,0x00,0x00,0x02,0xFF,0x13,
        0x00,
    };
*/
    U16 u16Buffer[] =
    {
        0x0080,0x002F,0x0037,
        // PWM1htLSB
        0x00FF,0x000F,0x00FF,0x000F,0x00FF,0x000F,0x00FF,0x000F,0x00FF,0x000F,0x00FF,0x000F,0x0000,0x0000,0x0000,0x0000,
        0x00FF,0x000F,0x00FF,0x000F,0x00FF,0x000F,0x00FF,0x000F,0x00FF,0x000F,0x00FF,0x000F,0x0000,0x0000,0x0000,0x0000,
        // ASICIDLSB
        0x00A0,0x0020,
        // 0x59~0x5F not used
        0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
        // STATUS
        0x0000,0x0000,0x0000,0x0002,0x00FF,0x0013,
        0x0000,
    };

#if 1
    MDrv_LDM_DMA_Set_DMA0_Datas(sizeof(u16Buffer)/2, u16Buffer, TRUE, TRUE);
#else

    U16 i;

    for(i=0;i<sizeof(u16Buffer)/sizeof(u16Buffer[0]);i++)
    {
        MDrv_LDM_DMA_Set_DMA0_Data(i,u16Buffer[i]);
    }
#endif
}

BOOLEAN LedDev_Init(void)
{
    PRINT_CURRENT_LINE();

    AS3820Unlock();

#if 1
    AS3820Init();

    AS3820Init2();

    AS3820Lock();
#endif

    return TRUE;
}

#endif
