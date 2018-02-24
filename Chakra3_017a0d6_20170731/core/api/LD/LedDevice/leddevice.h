#ifndef _LED_DEVICE_H_
#define _LED_DEVICE_H_

#include "Board.h"

#if (LD_ENABLE)

#define LED_DEVICE_NONE                     0x00
#define LED_DEVICE_LG_65INCH_DIRECT_120     0x01
#define LED_DEVICE_INX_40INCH_DIRECT_60     0x02
#define LED_DEVICE_SHARP_70INCH_DIRECT_120  0x03
#define LED_DEVICE_CSOT_49INCH_DIRECT_60    0x04
#define LED_DEVICE_CSOT_55INCH_DIRECT_60    0x05
#define LED_DEVICE_AUO_49INCH_DIRECT_60     0x06
#define LED_DEVICE_INX_50INCH_DIRECT_60     0x07
#define LED_DEVICE_INX_50INCH_TB_12         0x08
#define LED_DEVICE_INX_50INCH_TB_16         0x09
#define LED_DEVICE_LGE_INX_65INCH_DIRECT_120 0x0A
#define LED_DEVICE_INX_65INCH_16X1          0x0B
#define LED_DEVICE_INX_65INCH_2X8           0x0C
#define LED_DEVICE_INX_65INCH_2X16          0x0D
#define LED_DEVICE_INX_75INCH_24X1          0x0E
#define LED_DEVICE_LGE_INX_50INCH_DIRECT_60 0x0F
#define LED_DEVICE_LGE_INX_58INCH_DIRECT_60 0x10
#define LED_DEVICE_SKY_50INCH_DIRECT_180    0x11
#define LED_DEVICE_AS3820_2X7               0x12


#include "mdrv_mfc_spi.h"
#include "mdrv_ldm_dma.h"

#include "mdrv_ldalgo.h"


//===========================================================================

typedef enum
{
    LD_SPI_STAGE = 0,
    LD_PQ_STAGE = 1
} EnuLD_DEVELOPE_STAGE;

typedef struct
{
    EnuLD_DEVELOPE_STAGE eStage;

    // PANEL
    U16 u16PanelWidth, u16PanelHeight; // Panel width & height

    // Real Led number
    U8 u8LEDNumW, u8LEDNumH;

    U8 u8DMAWidth, u8DMAHeight; // DMA width & height (number of SPI data)
    U32 u32BaseAddr; // DRAM base address for LD

    // SPI (LD)
    BOOL bBacklightGlobeMode; // DMA output data non-8bit enable
    U8 u8BacklightGlobeGain;  // DMA output data gain
    U8 u8BacklightGlobeAlign; // DMA output data 0:16b  1:12b  2:4b  3:10b

    // SPI (LDM/MSPI)
    EnuMSPI_CLOCK_GEN eMSPIClockGen;
    EnuMSPI_CLOCK_DIV eMSPIClockDiv;
    U8 u8ClockPolarity; // 0 or 1
    U8 u8ClockPhase;    // 0 or 1
    U8 u8Time_FromTriggerToFirstClock;  // The time from "reg_mspi_trigger" to first SPI clock.     0 => Delay 1 MSPI clock
    U8 u8Time_LastClockToDone;    // The time from last SPI clock to "reg_mspi_done_flag"     0 => Delay 1 MSPI clock
    U8 u8Time_BetweenByteToByte;  // The time between byte to byte transfer       0 => Delay 0 MSPI clock
    U8 u8Time_FromWriteToRead;    // The time between last write and first read   0 => Delay 0 MSPI clock
    U8 u8SpiTime_VSyncWidth; // Unit is us
    U8 u8SpiTime_VSync_To_FirstClock; // Unit is us
    U8 u8LdDmaSpiPort;
    U8 u8SpiCmdLen;
    U8 u8SpiDataBit;
    U16 au16SpiCmd[LDM_MAX_SPI_CMD_NUM];
    U8 u8CheckSumMode;
    U8 u8LdmDmaTransferBits;

} StuDrvLdInfo;


typedef struct
{
    EnuLD_LED_TYPE eLEDType;

    // PANEL
    U8 u8LDFWidth, u8LDFHeight; // Statistic width & height  MAX=32*32
    // Algo cal block number
    U8 u8LEDWidth, u8LEDHeight; // LED width & height  MAX=W*H=64 if Edge2d enable, MAX=128*72 otherwise
    U8 u8LSFWidth, u8LSFHeight; // LSF width & height  MAX=128*72
    BOOL bCompensationEn; // Compensation enable
    const U8* pu8CompTable; // Compensation table  SIZE=256x2
    const U8* pu8CompLowTable; // Compensation table  SIZE=256x2
    BOOL bEdge2DEn; // Edge2D enable
    EnuLD_COEF_ENCODING eEnc; // Edge2D encoding scheme
    const U8* pu8Edge2DTable; // Edge2D table  SIZE=(u8LEDWidth*u8LEDHeight)*(u8LDFWidth*u8LDFHeight)

    // PQ HW
    U32 u32LsfInitialPhase_H, u32LsfInitialPhase_V;
    U8 u8DCMaxAlpha; // statistics : higher -> prefer max, lower -> prefer average
    U8 u8CompensationBlend; // pixel compensation tuner : higher -> prefer compensated pixel, lower -> prefer original pixel

    // PQ SW
    U8 u8GDStrength; // global dimming strength
    U8 u8LDStrength; // local dimming strength
    EnuLD_TEMPORAL_FILTER_STYLE eTFStyle;
    U8 u8TFStrengthUp; // temporal filter strength up
    U8 u8TFStrengthDn; // temporal filter strength down
    U8 u8TFLowThreshold; // temporal filter low threshold
    U8 u8TFHightThreshold; // temporal filter high threshold
    U8 u8TFMaxSpeed; // temporal filter max speed
    EnuLD_SPATIAL_FILTER_STYLE eSFStyle;
    U8 u8SFStrength1; // spatial filter strength 1
    U8 u8SFStrength2; // spatial filter strength 2
    U8 u8SFStrength3; // spatial filter strength 3
    U8 u8SFStrength4; // spatial filter strength 4
    U8 u8SFStrength5; // spatial filter strength 5
    U8 u8InGamma; // gamma at SW begin
    U8 u8OutGamma; // gamma at SW end
    U8 u8BLMinValue; // min clamp value
    U8 u8NRStrength; // de-noise strength

} StuDrvLdPQInfo;


typedef struct
{
    U8     PWM_CH;
    U16    CurSysOutVFreqX10;
    U16    SyncRstCnt;
}t_LD_Signal;


typedef void (*tLED_CONFIG_OUTPUT)(U16,BOOL);
typedef U16 (*tLED_GET_VFREQ)(U8);
typedef U16 (*tLED_GET_SYNCRSTCNT)(U8);
typedef void (*tLED_SET_OUTPUTSPI)(const U16*);

typedef struct
{
    StuDrvLdInfo            * p_sDrvLdInfo;
    StuDrvLdPQInfo          * p_sDrvLdPQInfo;
    tLED_CONFIG_OUTPUT      LED_DEVICE_Config_OutputSignal_To_LED;
    tLED_GET_VFREQ          LED_DEVICE_Get_OutputVFreq;
    tLED_GET_SYNCRSTCNT     LED_DEVICE_Get_SyncRstCnt;
    tLED_SET_OUTPUTSPI      LED_DEVICE_SET_OutputSPI;

}t_sDrvLdCusPtrMap;


extern U8* Tbl_LD_Gamma[16];
extern U8* Tbl_LD_Remap[16];

///////////////////////////////////////////////
// Enable function
///////////////////////////////////////////////

BOOL LedDev_Set_CurDevice(U8 u8LedDevId);
t_sDrvLdCusPtrMap* LedDev_Get_CurPtrMap(void);

U8 LedDev_Get_PQ_LedWidth(void);
U8 LedDev_Get_PQ_LedHeight(void);

void LedDev_Config_OutputSignal_To_LED( U16 u16OutVFreqX10, BOOL is3D );
void LedDev_Set_OutputSPI(const U16* pu16LedData);


extern BOOLEAN LedDev_Init(void);


///////////////////////////////////////////////

///////////////////////////////////////////////

#endif

#endif
