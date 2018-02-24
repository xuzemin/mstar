#ifndef _LED_Device_INNO_65INCH_16X1_C_
#define _LED_Device_INNO_65INCH_16X1_C_

#include "mdrv_mfc_spi.h"
#include "mdrv_ld.h"
#include "drvGlobal.h"
#include "msReg.h"
#include "drvPWM.h"
#include "MsCommon.h"
#include "LED_Device_INNO_65INCH_16X1.h"
#include "debug.h"
#include "pq/LED_PQ_INNO65inch_16X1.c"
extern t_sDrvLdCusPtrMap sCusPtrMap;

#include "mdrv_mfc_3d.h"
#include "System.h"
#include "mapp_customer.h"

extern U16 LD_Phase[16];// = {0x4F03, 0xB003, 0x1100, 0x7200, 0xD300, 0x3401, 0x9501, 0xF601, 0x4F03, 0xB003, 0x1100, 0x7200, 0xD300, 0x3401, 0x9501, 0xF601};
extern U16 LD_Duty[32];// = {0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403};

extern U16 LD_Phase_2D[16];// = {0x4F03, 0xB003, 0x1100, 0x7200, 0xD300, 0x3401, 0x9501, 0xF601, 0x4F03, 0xB003, 0x1100, 0x7200, 0xD300, 0x3401, 0x9501, 0xF601};
extern U16 LD_Duty_2D[32];// = {0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403};
extern BOOL g_bLD_Duty_Force;// = FALSE;
extern BOOL g_ld_2D_scanning;

StuDrvLdInfo s_DrvLdInfo_INNO65_16X1 =
{
    /* System Basic */
    LD_PQ_STAGE, // EnuLD_DEVELOPE_STAGE eStage;

    // PANEL
    PANEL_WIDTH_NORMAL, PANEL_HEIGHT_NORMAL, // U16 u16PanelWidth, u16PanelHeight; // Panel width & height
    //for 16X1 LEDs
    16, 1,
    1, 17, // U8 u8DMAWidth, u8DMAHeight; // DMA width & height

    ((LOCAL_DIMMING_MEMORY_TYPE & MIU1) ?(LOCAL_DIMMING_ADR|MIU_INTERVAL) : LOCAL_DIMMING_ADR), // U32 u32BaseAddr; // DRAM base address for LD

    // SPI
    FALSE, //BOOL bBacklightGlobeMode; // DMA output data non-8bit enable
    0x10, //U8 u8BacklightGlobeGain;  // DMA output data gain
    0, //U8 u8BacklightGlobeAlign; // DMA output data 0:16b  1:12b  2:4b  3:10b
    MSPI_CLK_SPD_36M,
    MSPI_CLK_SPD__DIV_32, // eMSPIClockSpeed
    1, // u8SpiClockPolarity
    1, // u8SpiClockPhase
    0, // u8Time_FromTriggerToFirstClock;  // The time from "reg_mspi_trigger" to first SPI clock.     0 => Delay 1 MSPI clock
    0, // u8Time_LastClockToDone;    // The time from last SPI clock to "reg_mspi_done_flag"     0 => Delay 1 MSPI clock
    0, // u8Time_BetweenByteToByte;  // The time between byte to byte transfer       0 => Delay 0 MSPI clock
    0, // u8Time_FromWriteToRead;    // The time between last write and first read   0 => Delay 0 MSPI clock
    0, // u8SpiTime_VSyncWidth
    0, // u8SpiTime_VSync_To_FirstClock
    MSPI_PORT_NUM,
    2, // SPI Command length
    16, //u8SpiDataBit
    {0xEB,0x14}, // SPI Command
    0, // u8CheckSumMode
    16, //LDM DMA transfer bit per one pack

    /* PQ Basic */


};

t_sDrvLdCusPtrMap sCusPtrMap_LED_INNO65_16X1=
{
    &s_DrvLdInfo_INNO65_16X1,
    &s_DrvLdPQInfo_INNO65_16X1,
    LED_INNO65_16X1_Config_OutputSignal_To_LED,
    NULL,
    NULL,
    LED_INNO65_16X1_Set_OutputSPI_Signal,
};

#if (LED_MULTI_SUPPORT_ENABLE == 0)
t_sDrvLdCusPtrMap * psLEDCusPtrMap = &sCusPtrMap_LED_INNO65_16X1;
#endif

t_LD_Signal ld_pwm_INNO65_16X1[(U8)PWM_NUMS]={{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};


void _LED_INNO65_16X1_Set_OutputCS(U16 u16OutVFreqX10, BOOL Is3D)
{
    t_LD_Signal OutputSignal;

    if(Is3D)
    {
        if (u16OutVFreqX10 < 1300) // 3D 120Hz output, FHD 120Hz FI input
        {
        MDrv_MFC_PWM_waveform_maker(LD_INNO65_16X1_CS_PWM_CH_SEL, u16OutVFreqX10, LD_INNO65_16X1_CS_3D_120Hz_PWM_DUTYx100,
                                    LD_INNO65_16X1_CS_3D_120Hz_PWM_SHIFTx100, LD_INNO65_16X1_CS_3D_120Hz_PWM_DIV, 0,
                                    Vsync_DoubleBF, PWM_RST_CTRL__VSYNC, LD_INNO65_16X1_CS_3D_120Hz_PWM_POLARITY);
        }
        else // 3D 240Hz output
        {
            MDrv_MFC_PWM_waveform_maker(LD_INNO65_16X1_CS_PWM_CH_SEL, u16OutVFreqX10, LD_INNO65_16X1_CS_3D_240Hz_PWM_DUTYx100,
                                        LD_INNO65_16X1_CS_3D_240Hz_PWM_SHIFTx100, LD_INNO65_16X1_CS_3D_240Hz_PWM_DIV, 0,
                                        Vsync_DoubleBF, PWM_RST_CTRL__VSYNC, LD_INNO65_16X1_CS_3D_240Hz_PWM_POLARITY);
        }
    }
    else
    {
        if (u16OutVFreqX10 <= 1100) // 2D 100Hz output
        {
            MDrv_MFC_PWM_waveform_maker(LD_INNO65_16X1_CS_PWM_CH_SEL, u16OutVFreqX10, LD_INNO65_16X1_CS_2D100Hz_PWM_DUTYx100,
                                        LD_INNO65_16X1_CS_2D100Hz_PWM_SHIFTx100, LD_INNO65_16X1_CS_2D100Hz_PWM_DIV, 0,
                                        Vsync_DoubleBF, PWM_RST_CTRL__VSYNC, LD_INNO65_16X1_CS_2D100Hz_PWM_POLARITY);
        }
        else if ((u16OutVFreqX10 > 1100) && (u16OutVFreqX10 <= 1300)) // 2D 120Hz output
        {
            MDrv_MFC_PWM_waveform_maker(LD_INNO65_16X1_CS_PWM_CH_SEL, u16OutVFreqX10, LD_INNO65_16X1_CS_2D120Hz_PWM_DUTYx100,
                                        LD_INNO65_16X1_CS_2D120Hz_PWM_SHIFTx100, LD_INNO65_16X1_CS_2D120Hz_PWM_DIV, 0,
                                        Vsync_DoubleBF, PWM_RST_CTRL__VSYNC, LD_INNO65_16X1_CS_2D120Hz_PWM_POLARITY);
        }
        else //if (u16OutVFreqX10 > 1300) // 2D 240Hz output
        {
            MDrv_MFC_PWM_waveform_maker(LD_INNO65_16X1_CS_PWM_CH_SEL, u16OutVFreqX10, LD_INNO65_16X1_CS_2D240Hz_PWM_DUTYx100,
                                        LD_INNO65_16X1_CS_2D240Hz_PWM_SHIFTx100, LD_INNO65_16X1_CS_2D240Hz_PWM_DIV, 0,
                                        Vsync_DoubleBF, PWM_RST_CTRL__VSYNC, LD_INNO65_16X1_CS_2D240Hz_PWM_POLARITY);
        }
    }

    MHal_PWM_WaveformResetEnable(LD_INNO65_16X1_CS_PWM_CH_SEL, ENABLE);

    MHal_PWM_OutputEn(LD_INNO65_16X1_CS_PWM_CH_SEL, ENABLE);

    MDrv_PWM_Set_PadEn( LD_INNO65_16X1_CS_PWM_CH_SEL, ENABLE );

    OutputSignal.PWM_CH = (U8) LD_INNO65_16X1_CS_PWM_CH_SEL;
    OutputSignal.CurSysOutVFreqX10 = u16OutVFreqX10;
    OutputSignal.SyncRstCnt = 0 ;
    _LED_INNO65_16X1_Set_OutputPWMData(OutputSignal.PWM_CH, OutputSignal);

}

void  _LED_INNO65_16X1_Set_OutputPWMData(U8 ch, t_LD_Signal OutputSignal)
{
    if(ch >= (U8)PWM_NUMS)
    {
        printf("%sLED  error : %s() ; ln%d%s\n",KRED,__FUNCTION__,__LINE__,KNRM);
        return ;
    }

    ld_pwm_INNO65_16X1[ch].PWM_CH = OutputSignal.PWM_CH;
    ld_pwm_INNO65_16X1[ch].CurSysOutVFreqX10 = OutputSignal.CurSysOutVFreqX10;
    ld_pwm_INNO65_16X1[ch].SyncRstCnt = OutputSignal.SyncRstCnt;

}

void _LED_INNO65_16X1_Set_SpiClk_Delay_FromVsync(U16 u16OutVFreqX10, BOOL Is3D)
{
    UNUSED(u16OutVFreqX10);
    if(Is3D)
    {
        MDrv_LD_SetSpiClkDelayFromVsync(LD_INNO65_16X1_PERIOD_3D_SCLK_TO_VSYNC);//hardcode refine 20150310
    }
    else
    {
        MDrv_LD_SetSpiClkDelayFromVsync(LD_INNO65_16X1_PERIOD_2D_SCLK_TO_VSYNC);//hardcode refine 20150310
    }
}



void LED_INNO65_16X1_Config_OutputSignal_To_LED(U16 u16OutVFreqX10, BOOL Is3D)
{
 //   _LED_DEVICE_Set_OutputVFreq(u16OutVFreqX10,Is3D);
    _LED_INNO65_16X1_Set_OutputCS(u16OutVFreqX10,Is3D);
    _LED_INNO65_16X1_Set_SpiClk_Delay_FromVsync(u16OutVFreqX10,Is3D);
}

U8 LED_INNO65_16X1_Get_LDLedNum(void)
{
    return gCusInxVar.enLDLedNum;
}

void  LED_INNO65_16X1_Set_OutputSPI_Signal(const U16* SPI_blocks)
{
    U16 PHY_blocks[LD_MAX_BLOCK_SIZE];
    const int vir_to_phy_LED_ratio_H = 1;
    const int vir_to_phy_LED_ratio_V = 1;

    U16 SPI_idx = 0, PHY_idx = 0, i = 0, j = 0;
    U32 addr_base = MHal_LD_Get_SPI_BufBaseAddr();

    // Re-arrange virtual LED blocks into physical LED blocks
    U16 led_width = psDrvLdInfo->u8LEDNumW;
    U16 led_height = MHal_LD_Get_LED_BacklightHeight();
    U16 phy_width = led_width * vir_to_phy_LED_ratio_H;
    U16 phy_height = led_height * vir_to_phy_LED_ratio_V;
    U16 n_phys = phy_width * phy_height;

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
    else
    {
        for (PHY_idx = 0; PHY_idx < n_phys; PHY_idx++)
        {
            j = PHY_idx / phy_width;
            i = PHY_idx % phy_width;
            SPI_idx = (i/vir_to_phy_LED_ratio_H) + (j/vir_to_phy_LED_ratio_V)*led_width;
            PHY_blocks[PHY_idx] = SPI_blocks[SPI_idx];
        }
    }

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
        U16 * pSPIout= (U16 *)( addr_base+0x80000000);
        U16 duty_data = 0x8000;
        U16 doublebytes[2];

        for(i=0;i<(s_DrvLdInfo_INNO65_16X1.u8LEDNumW)*(s_DrvLdInfo_INNO65_16X1.u8LEDNumH);i++)
        {
            if((i%s_DrvLdInfo_INNO65_16X1.u8DMAWidth)==0)
            {
                pSPIout = (U16 *)(addr_base+LD_DMA_LINE_SIZE*(i/s_DrvLdInfo_INNO65_16X1.u8DMAWidth)+0x80000000) ;
            }
            else
            {
                pSPIout++;
            }

            if(i>=LD_MAX_BLOCK_SIZE)
            {
                printf("%s[%s][%d]PHY_blocks index %d is out of range%s\n", KRED, __FUNCTION__, __LINE__, i, KNRM);
                return;
            }
            doublebytes[0]=PHY_blocks[i];
            //printf("LD value = %x \n",PHY_blocks[i]);
            duty_data=((doublebytes[0]<<4)&0xff00)|((doublebytes[0]>>12)&0x00ff);
            *(pSPIout) = duty_data;
        }
        j = 0;
        for(;i<(s_DrvLdInfo_INNO65_16X1.u8DMAWidth)*(s_DrvLdInfo_INNO65_16X1.u8DMAHeight);i++)
        {
            if((i%s_DrvLdInfo_INNO65_16X1.u8DMAWidth)==0)
            {
                pSPIout = (U16 *)(addr_base+LD_DMA_LINE_SIZE*(i/s_DrvLdInfo_INNO65_16X1.u8DMAWidth)+0x80000000) ;
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


}
#endif
