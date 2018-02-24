#ifndef _LED_Device_SKY_50INCH_DIRECT_180_C_
#define _LED_Device_SKY_50INCH_DIRECT_180_C_

#include "mdrv_mfc_spi.h"
#include "mdrv_ld.h"
#include "drvGlobal.h"
#include "msReg.h"
#include "drvPWM.h"
#include "MsCommon.h"
#include "LED_Device_SKY_50INCH_DIRECT_180.h"

#include "pq/LED_PQ_SKY50inch_Direct180.c"

extern t_sDrvLdCusPtrMap sCusPtrMap;


StuDrvLdInfo s_DrvLdInfo_SKY50 =
{
    LD_PQ_STAGE,//LD_PQ_STAGE, // EnuLD_DEVELOPE_STAGE eStage;

    // PANEL
    PANEL_WIDTH_NORMAL, PANEL_HEIGHT_NORMAL, // U16 u16PanelWidth, u16PanelHeight; // Panel width & height
    18, 10, // U8 u8LEDNumW, u8LEDNumH; // LED
    14, 8, // U8 u8DMAWidth, u8DMAHeight; // DMA width & height
    (LOCAL_DIMMING_MEMORY_TYPE & MIU1) ? (LOCAL_DIMMING_ADR | MIU_INTERVAL) : (LOCAL_DIMMING_ADR), // U32 u32BaseAddr; // DRAM base address for LD, // U32 u32BaseAddr; // DRAM base address for LD

    // SPI (LD)
    FALSE, //BOOL bBacklightGlobeMode; // DMA output data non-8bit enable
    0x10, //U8 u8BacklightGlobeGain;  // DMA output data gain
    0, //U8 u8BacklightGlobeAlign; // DMA output data 0:16b  1:12b  2:4b  3:10b

    // SPI (LDM/MSPI)
    MSPI_CLK_SPD_36M,
    MSPI_CLK_SPD__DIV_32, // eMSPIClockSpeed
    0,//0, // u8SpiClockPolarity
    0, // u8SpiClockPhase //0: Date is sampled when the SCK leaves the idle state.// 1: Date is sampled when the SCK returns to idle state.
    0, // u8Time_FromTriggerToFirstClock;  // The time from "reg_mspi_trigger" to first SPI clock.     0 => Delay 1 MSPI clock
    0, // u8Time_LastClockToDone;    // The time from last SPI clock to "reg_mspi_done_flag"     0 => Delay 1 MSPI clock
    0, // u8Time_BetweenByteToByte;  // The time between byte to byte transfer       0 => Delay 0 MSPI clock
    0, // u8Time_FromWriteToRead;    // The time between last write and first read   0 => Delay 0 MSPI clock
    0, // u8SpiTime_VSyncWidth
    0, // u8SpiTime_VSync_To_FirstClock
    MSPI_PORT_NUM,
    3, // SPI Command length
    8, //u8SpiDataBit
    {0x00,0xff,0x01}, // SPI Command
    0, // u8CheckSumMode
    8, //LDM DMA transfer bit per one pack
};

t_sDrvLdCusPtrMap sCusPtrMap_LED_SKY50=
{
    &s_DrvLdInfo_SKY50,
    &s_DrvLdPQInfo_SKY50,
    LED_SKY50_Config_OutputSignal_To_LED,
    LED_SKY50_Get_OutputVFreq,
    LED_SKY50_Get_SyncRstCnt,
    LED_SKY50_Set_OutputSPI_Signal,
};

#if (LED_MULTI_SUPPORT_ENABLE == 0)
t_sDrvLdCusPtrMap * psLEDCusPtrMap = &sCusPtrMap_LED_SKY50;
#endif


t_LD_Signal ld_pwm_SKY50[(U8)PWM_NUMS]={{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};

void _LED_SKY50_Set_OutputVFreq(U16 u16OutVFreqX10, BOOL Is3D)
{
    t_LD_Signal OutputSignal;

    if(Is3D)
    {
            OutputSignal.CurSysOutVFreqX10 =u16OutVFreqX10;
            OutputSignal.SyncRstCnt  =0;

            MDrv_MFC_PWM_waveform_maker(LD_SKY50_VSYNC_PWM_CH_SEL, OutputSignal.CurSysOutVFreqX10, LD_SKY50_VSYNC_3D_PWM_DUTYx100,
                                        LD_SKY50_VSYNC_3D_PWM_SHIFTx100, LD_SKY50_VSYNC_3D_PWM_DIV, OutputSignal.SyncRstCnt,
                                        Vsync_DoubleBF, PWM_RST_CTRL__VSYNC, LD_SKY50_VSYNC_3D_PWM_POLARITY);

    }
    else
    {
            OutputSignal.CurSysOutVFreqX10 =u16OutVFreqX10;
            OutputSignal.SyncRstCnt  =0;

            if(u16OutVFreqX10 < 1100)// 100Hz , 2D 50Hz input
            {
                MDrv_MFC_PWM_waveform_maker(LD_SKY50_VSYNC_PWM_CH_SEL, OutputSignal.CurSysOutVFreqX10, LD_SKY50_VSYNC_2D50Hz_PWM_DUTYx100,
                                            LD_SKY50_VSYNC_2D50Hz_PWM_SHIFTx100, LD_SKY50_VSYNC_2D50Hz_PWM_DIV, OutputSignal.SyncRstCnt,
                                            Vsync_DoubleBF, PWM_RST_CTRL__VSYNC, LD_SKY50_VSYNC_2D50Hz_PWM_POLARITY);

            }
            else
            {
                MDrv_MFC_PWM_waveform_maker(LD_SKY50_VSYNC_PWM_CH_SEL, OutputSignal.CurSysOutVFreqX10, LD_SKY50_VSYNC_2D60Hz_PWM_DUTYx100,
                                            LD_SKY50_VSYNC_2D60Hz_PWM_SHIFTx100, LD_SKY50_VSYNC_2D60Hz_PWM_DIV, OutputSignal.SyncRstCnt,
                                            Vsync_DoubleBF, PWM_RST_CTRL__VSYNC, LD_SKY50_VSYNC_2D60Hz_PWM_POLARITY);

        }
    }

    MHal_PWM_WaveformResetEnable(LD_SKY50_VSYNC_PWM_CH_SEL, ENABLE);

    MHal_PWM_OutputEn(LD_SKY50_VSYNC_PWM_CH_SEL, ENABLE);

    MDrv_PWM_Set_PadEn( LD_SKY50_VSYNC_PWM_CH_SEL, ENABLE );

    OutputSignal.PWM_CH = (U8) LD_SKY50_VSYNC_PWM_CH_SEL;
    _LED_SKY50_Set_OutputPWMData(OutputSignal.PWM_CH, OutputSignal);
}

void _LED_SKY50_Set_OutputCS(U16 u16OutVFreqX10, BOOL Is3D)
{
    t_LD_Signal OutputSignal ;

    if(Is3D)
    {
        MDrv_MFC_PWM_waveform_maker(LD_SKY50_CS_PWM_CH_SEL, u16OutVFreqX10, LD_SKY50_CS_3D_PWM_DUTYx100,
                                    LD_SKY50_CS_3D_PWM_SHIFTx100, LD_SKY50_CS_3D_PWM_DIV, 0,
                                    Vsync_DoubleBF, PWM_RST_CTRL__VSYNC, LD_SKY50_CS_3D_PWM_POLARITY);
    }
    else
    {
        if(u16OutVFreqX10 < 1100)// 200Hz , 2D 50Hz input 
        {
            printf("[weicheng] _LED_AMT55_Set_OutputCS => not 3D  ,< 2200\n"); // this one
            MDrv_MFC_PWM_waveform_maker(LD_SKY50_CS_PWM_CH_SEL, u16OutVFreqX10, LD_SKY50_CS_2D50Hz_PWM_DUTYx100,
                                        LD_SKY50_CS_2D50Hz_PWM_SHIFTx100, LD_SKY50_CS_2D50Hz_PWM_DIV, 0,
                                        Vsync_DoubleBF, PWM_RST_CTRL__VSYNC, LD_SKY50_CS_2D50Hz_PWM_POLARITY);

        }
        else
        {
            MDrv_MFC_PWM_waveform_maker(LD_SKY50_CS_PWM_CH_SEL, u16OutVFreqX10, LD_SKY50_CS_2D60Hz_PWM_DUTYx100,
                                        LD_SKY50_CS_2D60Hz_PWM_SHIFTx100, LD_SKY50_CS_2D60Hz_PWM_DIV, 0,
                                        Vsync_DoubleBF, PWM_RST_CTRL__VSYNC, LD_SKY50_CS_2D60Hz_PWM_POLARITY);
        }

    }

    MHal_PWM_WaveformResetEnable(LD_SKY50_CS_PWM_CH_SEL, ENABLE);

    MHal_PWM_OutputEn(LD_SKY50_CS_PWM_CH_SEL, ENABLE);

    MDrv_PWM_Set_PadEn( LD_SKY50_CS_PWM_CH_SEL, ENABLE );


    OutputSignal.PWM_CH = (U8) LD_SKY50_CS_PWM_CH_SEL;
    OutputSignal.CurSysOutVFreqX10 = u16OutVFreqX10;
    OutputSignal.SyncRstCnt = 0 ;
    _LED_SKY50_Set_OutputPWMData(OutputSignal.PWM_CH, OutputSignal);

}

void _LED_SKY50_Set_SpiClk_Delay_FromVsync(U16 u16OutVFreqX10, BOOL Is3D)
{
    u16OutVFreqX10 = u16OutVFreqX10;
    if(Is3D)
    {
        MDrv_LD_SetSpiClkDelayFromVsync(LD_SKY50_PERIOD_3D_SCLK_TO_VSYNC);//hardcode refine 20150310
    }
    else
    {
        MDrv_LD_SetSpiClkDelayFromVsync(LD_SKY50_PERIOD_2D_SCLK_TO_VSYNC);//hardcode refine 20150310
    }
}

void  _LED_SKY50_Set_OutputPWMData(U8 ch, t_LD_Signal OutputSignal)
{
    if(ch >= (U8)PWM_NUMS)
    {
        printf("LED  error : %s() ; ln%d\n",__FUNCTION__,__LINE__);
        return ;
    }

    ld_pwm_SKY50[ch].PWM_CH = OutputSignal.PWM_CH;
    ld_pwm_SKY50[ch].CurSysOutVFreqX10 = OutputSignal.CurSysOutVFreqX10;
    ld_pwm_SKY50[ch].SyncRstCnt = OutputSignal.SyncRstCnt;

}


U16  LED_SKY50_Get_OutputVFreq(U8 ch)
{
        //printf("test-- %s() ; ln%d\n",__FUNCTION__,__LINE__);
    if(ch >= (U8)PWM_NUMS )
    {
        printf("LED  error : %s() ; ln%d\n",__FUNCTION__,__LINE__);
        return 0xFFFF;
    }

    return ld_pwm_SKY50[ch].CurSysOutVFreqX10 ;
}

U16  LED_SKY50_Get_SyncRstCnt(U8 ch)
{
        //printf("test-- %s() ; ln%d\n",__FUNCTION__,__LINE__);
    if(ch >= (U8)PWM_NUMS )
    {
        printf("LED  error : %s() ; ln%d\n",__FUNCTION__,__LINE__);
        return 0xFFFF;
    }

    return ld_pwm_SKY50[ch].SyncRstCnt ;
}

void LED_SKY50_Config_OutputSignal_To_LED(U16 u16OutVFreqX10, BOOL Is3D)
{
        //printf("test-- %s() ; ln%d\n",__FUNCTION__,__LINE__);
    _LED_SKY50_Set_OutputVFreq(u16OutVFreqX10,Is3D);
	_LED_SKY50_Set_OutputCS(u16OutVFreqX10,Is3D);
    _LED_SKY50_Set_SpiClk_Delay_FromVsync(u16OutVFreqX10,Is3D);
}

void  LED_SKY50_Set_OutputSPI_Signal(const U16* SPI_blocks)
{
    /* TRANSLATE SPI_blocks TO PHY_blocks on your own!!           */
    /* SPI_blocks contains 16-bit data, ranging from 0 to 0xFFFF. */

    // 1 virtual LED = 2x2 physical LED
    U16 PHY_blocks[LD_MAX_BLOCK_SIZE];
    const int vir_to_phy_LED_ratio_H = 1; // <---- CHECK HERE !!!!
    const int vir_to_phy_LED_ratio_V = 1; // <---- CHECK HERE !!!!

    U16 led_width = MHal_LD_Get_LED_BacklightWidth();
    U16 led_height = MHal_LD_Get_LED_BacklightHeight();
    U16 SPI_idx = 0, PHY_idx = 0, i = 0, j = 0;
    U32 addr_base = MHal_LD_Get_SPI_BufBaseAddr();
    U8 u8Size =0;


    // Re-arrange virtual LED blocks into physical LED blocks
    U16 phy_width = led_width * vir_to_phy_LED_ratio_H; // <---- CHECK HERE !!!!
    U16 phy_height = led_height * vir_to_phy_LED_ratio_V; // <---- CHECK HERE !!!!
    U16 n_phys = phy_width * phy_height;

    U16 au16SPI_blocks2[LD_MAX_BLOCK_SIZE];

    // parameter for LD smooth behavior when UI change

    for (u8Size =0; u8Size < n_phys; u8Size++)
    {
        au16SPI_blocks2[u8Size] = SPI_blocks[u8Size];
    }


     // Re-arrange virtual LED blocks into physical LED blocks
    for (PHY_idx = 0; PHY_idx < n_phys; PHY_idx++)
    {
        j = PHY_idx / phy_width;
        i = PHY_idx % phy_width;
        SPI_idx = (i/vir_to_phy_LED_ratio_H) + (j/vir_to_phy_LED_ratio_V)*led_width; // <---- CHECK HERE !!!!
        PHY_blocks[PHY_idx] = au16SPI_blocks2[SPI_idx];
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

    U16 dma_width = MHal_LD_Get_DMA_BacklightWidth();
    //U16 dma_height = MHal_LD_Get_DMA_BacklightHeight();
	U16 SwitchData = 0;
	 U8 CmdData,CheckSum1=0,Data;
	 U16 pack_length = 0;
	 if (dma_width > 0)
		 pack_length = (((dma_width - 1) >> 5) + 1) << 5 ;
	 
	 U16 * pSPIout= 0;//(U16 *) (addr_base+0x80000000);
	 pSPIout= (U16 *) (addr_base+0x80000000); //
	 i = 0;
	 for (PHY_idx = 0; PHY_idx < n_phys/2; PHY_idx ++)
	 {
		SwitchData = PHY_blocks[PHY_idx];
		PHY_blocks[PHY_idx] = PHY_blocks[n_phys - PHY_idx - 1];
		PHY_blocks[n_phys - PHY_idx - 1] = SwitchData;
	 }
	 CmdData		 = 0x01;
	 CheckSum1 = CheckSum1 ^ CmdData;
	 for (PHY_idx = 0; PHY_idx < n_phys; PHY_idx ++)
	 {
	 	if((PHY_idx < 18) || (PHY_idx >= 90))
 		{
			 Data = 4;//= PHY_blocks[PHY_idx] >> 8;
 		}
		else 
		{
			if(PHY_blocks[PHY_idx] > PHY_blocks[PHY_idx+1])
				Data = PHY_blocks[PHY_idx] >> 8;
			else
				Data = PHY_blocks[PHY_idx+1] >> 8;
			 Data= 4;
			PHY_idx++;
		}
		*(pSPIout+i++) = (Data&0x00ff);
		CheckSum1 = CheckSum1 ^ Data;
	 }
	 *(pSPIout+i++) = (CheckSum1&0x00ff);
	 Data = 0xff;
	 *(pSPIout+i++) = (CheckSum1&0x00ff);
	 Data = 0xff;
	 *(pSPIout+i++) = (CheckSum1&0x00ff);
	 
}

#endif

