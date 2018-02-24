#ifndef _LED_Device_INNO_50INCH_DIRECT_60_C_
#define _LED_Device_INNO_50INCH_DIRECT_60_C_

#include "mdrv_mfc_spi.h"
#include "mdrv_ld.h"
#include "drvGlobal.h"
#include "msReg.h"
#include "drvPWM.h"
#include "MsCommon.h"
#include "debug.h"
#include "LED_Device_INNO_50INCH_DIRECT_60.h"

#include "pq/LED_PQ_INNO50inch_Direct60.c"
extern t_sDrvLdCusPtrMap sCusPtrMap;

#include "mdrv_mfc_3d.h"
#include "System.h"
#include "mapp_customer.h"

extern U16 LD_Phase[8];// = {0x4F03, 0xB003, 0x1100, 0x7200, 0xD300, 0x3401, 0x9501, 0xF601};
extern U16 LD_Duty[16];// = {0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, };

extern U16 LD_Phase_2D[8];// = {0x4F03, 0xB003, 0x1100, 0x7200, 0xD300, 0x3401, 0x9501, 0xF601};
extern U16 LD_Duty_2D[16];// = {0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, 0x3403, };
extern BOOL g_bLD_Duty_Force;// = FALSE;
extern BOOL g_ld_2D_scanning;

StuDrvLdInfo s_DrvLdInfo_INNO50 =
{
    /* System Basic */
    LD_PQ_STAGE, // EnuLD_DEVELOPE_STAGE eStage;

    // PANEL
    PANEL_WIDTH_NORMAL, PANEL_HEIGHT_NORMAL, // U16 u16PanelWidth, u16PanelHeight; // Panel width & height
    1,8,
    16, 2, // U8 u8DMAWidth, u8DMAHeight; // DMA width & height
    (LOCAL_DIMMING_MEMORY_TYPE & MIU1) ? (LOCAL_DIMMING_ADR | MIU_INTERVAL) : (LOCAL_DIMMING_ADR), // U32 u32BaseAddr; // DRAM base address for LD, // U32 u32BaseAddr; // DRAM base address for LD

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
    8, //u8SpiDataBit
    {0xEB,0x14}, // SPI Command
    0, // u8CheckSumMode
    16, //LDM DMA transfer bit per one pack

    /* PQ Basic */


};

t_sDrvLdCusPtrMap sCusPtrMap_LED_INNO50=
{
    &s_DrvLdInfo_INNO50,
    &s_DrvLdPQInfo_INNO50,
    LED_INNO50_Config_OutputSignal_To_LED,
    NULL,
    NULL,
    LED_INNO50_Set_OutputSPI_Signal,
};

#if (LED_MULTI_SUPPORT_ENABLE == 0)
t_sDrvLdCusPtrMap * psLEDCusPtrMap = &sCusPtrMap_LED_INNO50;
#endif

t_LD_Signal ld_pwm_INNO50[(U8)PWM_NUMS]={{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};


void _LED_INNO50_Set_OutputCS(U16 u16OutVFreqX10, BOOL Is3D)
{
    t_LD_Signal OutputSignal;

    if(Is3D)
    {
        if (u16OutVFreqX10 < 1020) //240Hz , 2D 60Hz input
        {
        MDrv_MFC_PWM_waveform_maker(LD_INNO50_CS_PWM_CH_SEL, u16OutVFreqX10, LD_INNO50_CS_3D_100Hz_PWM_DUTYx100,
                                    LD_INNO50_CS_3D_100Hz_PWM_SHIFTx100, LD_INNO50_CS_3D_100Hz_PWM_DIV, 0,
                                    Vsync_DoubleBF, PWM_RST_CTRL__VSYNC, LD_INNO50_CS_3D_100Hz_PWM_POLARITY);
        }
        else //480Hz , 2D 120Hz input
        {
            MDrv_MFC_PWM_waveform_maker(LD_INNO50_CS_PWM_CH_SEL, u16OutVFreqX10, LD_INNO50_CS_3D_120Hz_PWM_DUTYx100,
                                        LD_INNO50_CS_3D_120Hz_PWM_SHIFTx100, LD_INNO50_CS_3D_120Hz_PWM_DIV, 0,
                                        Vsync_DoubleBF, PWM_RST_CTRL__VSYNC, LD_INNO50_CS_3D_120Hz_PWM_POLARITY);
    }
    }
    else
    {
        if(u16OutVFreqX10 < 520)// 200Hz , 2D 50Hz input
        {
            MDrv_MFC_PWM_waveform_maker(LD_INNO50_CS_PWM_CH_SEL, u16OutVFreqX10, LD_INNO50_CS_2D50Hz_PWM_DUTYx100,
                                        LD_INNO50_CS_2D50Hz_PWM_SHIFTx100, LD_INNO50_CS_2D50Hz_PWM_DIV, 0,
                                        Vsync_DoubleBF, PWM_RST_CTRL__VSYNC, LD_INNO50_CS_2D50Hz_PWM_POLARITY);

        }
        else if (u16OutVFreqX10 < 620 && u16OutVFreqX10 >= 520) //240Hz , 2D 60Hz input
        {
            MDrv_MFC_PWM_waveform_maker(LD_INNO50_CS_PWM_CH_SEL, u16OutVFreqX10, LD_INNO50_CS_2D60Hz_PWM_DUTYx100,
                                        LD_INNO50_CS_2D60Hz_PWM_SHIFTx100, LD_INNO50_CS_2D60Hz_PWM_DIV, 0,
                                        Vsync_DoubleBF, PWM_RST_CTRL__VSYNC, LD_INNO50_CS_2D60Hz_PWM_POLARITY);
        }

        else if (u16OutVFreqX10 < 1020 && u16OutVFreqX10 >= 620) //400Hz , 2D 100Hz input
        {
            MDrv_MFC_PWM_waveform_maker(LD_INNO50_CS_PWM_CH_SEL, u16OutVFreqX10, LD_INNO50_CS_2D100Hz_PWM_DUTYx100,
                                        LD_INNO50_CS_2D100Hz_PWM_SHIFTx100, LD_INNO50_CS_2D100Hz_PWM_DIV, 0,
                                        Vsync_DoubleBF, PWM_RST_CTRL__VSYNC, LD_INNO50_CS_2D100Hz_PWM_POLARITY);
        }

        else if (u16OutVFreqX10 >= 1020) //480Hz , 2D 120Hz input
        {
            MDrv_MFC_PWM_waveform_maker(LD_INNO50_CS_PWM_CH_SEL, u16OutVFreqX10, LD_INNO50_CS_2D120Hz_PWM_DUTYx100,
                                        LD_INNO50_CS_2D120Hz_PWM_SHIFTx100, LD_INNO50_CS_2D120Hz_PWM_DIV, 0,
                                        Vsync_DoubleBF, PWM_RST_CTRL__VSYNC, LD_INNO50_CS_2D120Hz_PWM_POLARITY);
        }

    }

    MHal_PWM_WaveformResetEnable(LD_INNO50_CS_PWM_CH_SEL, ENABLE);

    MHal_PWM_OutputEn(LD_INNO50_CS_PWM_CH_SEL, ENABLE);

    MDrv_PWM_Set_PadEn( LD_INNO50_CS_PWM_CH_SEL, ENABLE );

    OutputSignal.PWM_CH = (U8) LD_INNO50_CS_PWM_CH_SEL;
    OutputSignal.CurSysOutVFreqX10 = u16OutVFreqX10;
    OutputSignal.SyncRstCnt = 0 ;
    _LED_INNO50_Set_OutputPWMData(OutputSignal.PWM_CH, OutputSignal);

}

void  _LED_INNO50_Set_OutputPWMData(U8 ch, t_LD_Signal OutputSignal)
{
    if(ch >= (U8)PWM_NUMS)
    {
        printf("%sLED  error : %s() ; ln%d%s\n",KRED,__FUNCTION__,__LINE__,KNRM);
        return ;
    }

    ld_pwm_INNO50[ch].PWM_CH = OutputSignal.PWM_CH;
    ld_pwm_INNO50[ch].CurSysOutVFreqX10 = OutputSignal.CurSysOutVFreqX10;
    ld_pwm_INNO50[ch].SyncRstCnt = OutputSignal.SyncRstCnt;

}

void _LED_INNO50_Set_SpiClk_Delay_FromVsync(U16 u16OutVFreqX10, BOOL Is3D)
{
    UNUSED(u16OutVFreqX10);
    if(Is3D)
    {
        MDrv_LD_SetSpiClkDelayFromVsync(LD_INNO50_PERIOD_3D_SCLK_TO_VSYNC);//hardcode refine 20150310
    }
    else
    {
        MDrv_LD_SetSpiClkDelayFromVsync(LD_INNO50_PERIOD_2D_SCLK_TO_VSYNC);//hardcode refine 20150310
    }
}



void LED_INNO50_Config_OutputSignal_To_LED(U16 u16OutVFreqX10, BOOL Is3D)
{
 //   _LED_DEVICE_Set_OutputVFreq(u16OutVFreqX10,Is3D);
    _LED_INNO50_Set_OutputCS(u16OutVFreqX10,Is3D);
    _LED_INNO50_Set_SpiClk_Delay_FromVsync(u16OutVFreqX10,Is3D);
}

U8 LED_INNO50_Get_LDLedNum(void)
{
    return gCusInxVar.enLDLedNum;
}

void  LED_INNO50_Set_OutputSPI_Signal(const U16* SPI_blocks)
{
    /* TRANSLATE SPI_blocks TO PHY_blocks on your own!!           */
    /* SPI_blocks contains 16-bit data, ranging from 0 to 0xFFFF. */

    // 1 virtual LED = 2x2 physical LED
    U16 PHY_blocks[LD_MAX_BLOCK_SIZE];
    const int vir_to_phy_LED_ratio_H = 1; // <---- CHECK HERE !!!!
    const int vir_to_phy_LED_ratio_V = 1; // <---- CHECK HERE !!!!

    U16 led_width = MHal_LD_Get_LED_BacklightWidth();
    U16 led_height = MHal_LD_Get_LED_BacklightHeight();
    U16 SPI_idx = 0, PHY_idx = 0,  i = 0, j = 0;
    U32 addr_base = MHal_LD_Get_SPI_BufBaseAddr();

    // Re-arrange virtual LED blocks into physical LED blocks
    U16 phy_width = led_width * vir_to_phy_LED_ratio_H; // <---- CHECK HERE !!!!
    U16 phy_height = led_height * vir_to_phy_LED_ratio_V; // <---- CHECK HERE !!!!
    U16 n_phys = phy_width * phy_height;
    for (PHY_idx = 0; PHY_idx < n_phys; PHY_idx++)
    {
        j = PHY_idx / phy_width;
        i = PHY_idx % phy_width;
        SPI_idx = (i/vir_to_phy_LED_ratio_H) + (j/vir_to_phy_LED_ratio_V)*led_width; // <---- CHECK HERE !!!!
        PHY_blocks[PHY_idx] = SPI_blocks[SPI_idx];
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

    U16 dma_width = MHal_LD_Get_DMA_BacklightWidth();
    //U16 dma_height = MHal_LD_Get_DMA_BacklightHeight();
    U16 pack_length = 0;
    if (dma_width > 0)
        pack_length = (((dma_width - 1) >> 4) + 1) << 4 ;


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


    #elif 0
        U16 * pSPIout= (U16 *)( addr_base+0x80000000);
        U16 duty_data = 0x8000;
        U16 doublebytes[2];
        if (MDrv_3D_Is_3d_Not_Lonly_MODE())
        {
            *(pSPIout+0) = LD_Duty[0];
            *(pSPIout+1) = LD_Duty[0];
            *(pSPIout+2) = LD_Duty[0];
            *(pSPIout+3) = LD_Duty[0];
            *(pSPIout+4) = LD_Duty[0];
            *(pSPIout+5) = LD_Duty[0];
            *(pSPIout+6) = LD_Duty[0];
            *(pSPIout+7) = LD_Duty[0];

            pSPIout = (U16 *)(addr_base+16*1+0x80000000) ;
            if(gCusInxVar.enLDLedNum == LD_LED_NUMBER_2X8)
            {
                *(pSPIout+0) = LD_Duty[0];
                *(pSPIout+1) = LD_Duty[0];
                *(pSPIout+2) = LD_Duty[0];
                *(pSPIout+3) = LD_Duty[0];
                *(pSPIout+4) = LD_Duty[0];
                *(pSPIout+5) = LD_Duty[0];
                *(pSPIout+6) = LD_Duty[0];
                *(pSPIout+7) = LD_Duty[0];
                pSPIout = (U16 *)(addr_base+16*2+0x80000000) ;
            }
            for(i=0;i<8;i++)
            {
                *(pSPIout+i) = LD_Phase[i];
            }
        }
        else if (g_bLD_Duty_Force)
        {
            *(pSPIout+0) = LD_Duty[0];
            *(pSPIout+1) = LD_Duty[1];
            *(pSPIout+2) = LD_Duty[2];
            *(pSPIout+3) = LD_Duty[3];
            *(pSPIout+4) = LD_Duty[4];
            *(pSPIout+5) = LD_Duty[5];
            *(pSPIout+6) = LD_Duty[6];
            *(pSPIout+7) = LD_Duty[7];

            pSPIout = (U16 *)(addr_base+16*1+0x80000000) ;

            if(gCusInxVar.enLDLedNum == LD_LED_NUMBER_2X8)
            {
                *(pSPIout+0) = LD_Duty[8];
                *(pSPIout+1) = LD_Duty[9];
                *(pSPIout+2) = LD_Duty[10];
                *(pSPIout+3) = LD_Duty[11];
                *(pSPIout+4) = LD_Duty[12];
                *(pSPIout+5) = LD_Duty[13];
                *(pSPIout+6) = LD_Duty[14];
                *(pSPIout+7) = LD_Duty[15];
                pSPIout = (U16 *)(addr_base+16*2+0x80000000) ;
            }

            for(i=0;i<8;i++)
            {
                *(pSPIout+i) = LD_Phase[i];
            }

        }

        else
        {
            if (g_ld_2D_scanning)
            {
                #if 0
                *(pSPIout+0) = LD_Duty_2D[0];
                *(pSPIout+1) = LD_Duty_2D[1];
                *(pSPIout+2) = LD_Duty_2D[2];
                *(pSPIout+3) = LD_Duty_2D[3];
                *(pSPIout+4) = LD_Duty_2D[4];
                *(pSPIout+5) = LD_Duty_2D[5];
                *(pSPIout+6) = LD_Duty_2D[6];
                *(pSPIout+7) = LD_Duty_2D[7];

                pSPIout = (U16 *)(addr_base+16*1) ;

                 if(gCusInxVar.enLDLedNum == LD_LED_NUMBER_8X2)
                 {
                    *(pSPIout+0) = LD_Duty_2D[8];
                    *(pSPIout+1) = LD_Duty_2D[9];
                    *(pSPIout+2) = LD_Duty_2D[10];
                    *(pSPIout+3) = LD_Duty_2D[11];
                    *(pSPIout+4) = LD_Duty_2D[12];
                    *(pSPIout+5) = LD_Duty_2D[13];
                    *(pSPIout+6) = LD_Duty_2D[14];
                    *(pSPIout+7) = LD_Duty_2D[15];
                    pSPIout = (U16 *)(addr_base+16*2) ;
                }
                #else
                if(gCusInxVar.enLDLedNum == LD_LED_NUMBER_2X8)
                {
                    for(i=0;i<8;i++)
                    {
                        doublebytes[0]=(U16)((U32)PHY_blocks[i]* ((LD_Duty_2D[i])/4095));
                        duty_data=((doublebytes[0]<<4)&0xff00)|((doublebytes[0]>>12)&0x00ff);
                        *(pSPIout+i) = duty_data;
                    }
                    pSPIout = (U16 *)(addr_base+16*1+0x80000000) ;
                    for(i=0;i<8;i++)
                    {
                        doublebytes[0]=(U16)((U32)PHY_blocks[i+8]* ((LD_Duty_2D[i+8])/4095));
                        duty_data=((doublebytes[0]<<4)&0xff00)|((doublebytes[0]>>12)&0x00ff);
                        *(pSPIout+i) = duty_data;
                    }
                    pSPIout = (U16 *)(addr_base+16*2+0x80000000) ;
                }
                else
                {

                    U16 duty_data_tmp ;

                    for(i=0;i<8;i++)
                    {
                        doublebytes[0]=(U16)((U32)PHY_blocks[i*2]* ((LD_Duty_2D[i])/4095));
                        doublebytes[1]=(U16)((U32)PHY_blocks[i*2+1]* ((LD_Duty_2D[i])/4095));
                        duty_data_tmp=(MAX(doublebytes[0],doublebytes[1]));
                        duty_data=((duty_data_tmp<<4)&0xff00)|((duty_data_tmp>>12)&0x00ff);
                        *(pSPIout+i) = duty_data;
                    }
                    pSPIout = (U16 *)(addr_base+16*1+0x80000000) ;
                }
                #endif


                 for(i=0;i<8;i++)
                 {
                    *(pSPIout+i) = LD_Phase_2D[i];
                 }

            }

            else
                {
                    if(gCusInxVar.enLDLedNum == LD_LED_NUMBER_2X8)
                    {
                        for(i=0;i<8;i++)
                        {
                            doublebytes[0]=PHY_blocks[i];
                            duty_data=((doublebytes[0]<<4)&0xff00)|((doublebytes[0]>>12)&0x00ff);
                            *(pSPIout+i) = duty_data;
                        }

                        pSPIout = (U16 *)(addr_base+16*1+0x80000000) ;

                        for(i=0;i<8;i++)
                        {
                            doublebytes[0]=PHY_blocks[i+8];
                            duty_data=((doublebytes[0]<<4)&0xff00)|((doublebytes[0]>>12)&0x00ff);
                            *(pSPIout+i) = duty_data;
                        }
                        pSPIout = (U16 *)(addr_base+16*2+0x80000000) ;
                    }
                    else
                    {

                        U16 duty_data_tmp ;

                        for(i=0;i<8;i++)
                        {
                            doublebytes[0]=PHY_blocks[i*2];
                            doublebytes[1]=PHY_blocks[i*2+1];

                            //bytes[0]=MDrv_ReadByte(REG_1EF2);
                            //bytes[1]=MDrv_ReadByte(REG_1EF3);

                            duty_data_tmp=(MAX(doublebytes[0],doublebytes[1]));

                            duty_data=((duty_data_tmp<<4)&0xff00)|((duty_data_tmp>>12)&0x00ff);
                            *(pSPIout+i) = duty_data;
                        }
                        pSPIout = (U16 *)(addr_base+16*1+0x80000000) ;
                    }


                    for(i=0;i<8;i++)
                    {
                        *(pSPIout+i) = LD_Phase[i];
                    }
                }

        }



        #else
                    U8 tem_duty1;
                    U8 tem_duty2;
                    U8 tem_phase1;
                    U8 tem_phase2;
                    for(i=0;i<8;i++)
                    {
                        //tem_duty1 = PHY_blocks[i]>>12&0xff;
                        //tem_duty2 = PHY_blocks[i]>>4&0xff;
                        if(0)//((gSysConfig.u8MirrorMode==MIRROR_H_MODE)||(gSysConfig.u8MirrorMode==MIRROR_HV_MODE))
                        {
                            tem_duty1 = (PHY_blocks[7-i]>>12)&0xff;
                            tem_duty2 = (PHY_blocks[7-i]>>4)&0xff;
                        }
                        else
                        {
                            tem_duty1 = (PHY_blocks[i]>>12)&0xff;
                            tem_duty2 = (PHY_blocks[i]>>4)&0xff;
                        }
                        MDrv_LD_MIUWriteByte(addr_base+i*4, 0, tem_duty1);
                        MDrv_LD_MIUWriteByte(addr_base+2+i*4, 0, tem_duty2);
                    }

                    addr_base = addr_base + 32;

                    for(i=0;i<8;i++)
                    {
                        tem_phase1 = (LD_Phase[i]>>12)&0xff;
                        tem_phase2 = (LD_Phase[i]>>4)&0xff;

                        MDrv_LD_MIUWriteByte(addr_base+i*4, 0, tem_phase1);
                        MDrv_LD_MIUWriteByte(addr_base+2+i*4, 0, tem_phase2);
                    }

       #endif


}
#endif
