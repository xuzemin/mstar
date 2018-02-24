#ifndef _LED_Device_INNO_50INCH_TB_12_H_
#define _LED_Device_INNO_50INCH_TB_12_H_


#ifdef _LED_Device_INNO_50INCH_TB_12_C_
    #define _LED_Device_INNO_50INCH_TB_12_DEC_
#else
    #define _LED_Device_INNO_50INCH_TB_12_DEC_  extern
#endif


#include "datatype.h"
#include "leddevice.h"


#if 1//(LD_ENABLE) //75inch 240Hz

    #define LD_INNO50_TB_12_3D_VSYNC_DIV2_ENABLE     1

//    #define LD_VSYNC_PWM_CH_SEL       PWM_CH5
    #define LD_INNO50_TB_12_CS_PWM_CH_SEL            PWM_CH4


//========  2D Timing  ========
    #define LD_INNO50_TB_12_PERIOD_2D_SCLK_TO_VSYNC     (0x1665)

    //2D 50Hz

    #define LD_INNO50_TB_12_CS_2D50Hz_PWM_DUTYx100      (0x0)
    #define LD_INNO50_TB_12_CS_2D50Hz_PWM_SHIFTx100     (0x370)
    #define LD_INNO50_TB_12_CS_2D50Hz_PWM_DIV           (12)
    #define LD_INNO50_TB_12_CS_2D50Hz_PWM_POLARITY      (0)

    //2D 60Hz

    #define LD_INNO50_TB_12_CS_2D60Hz_PWM_DUTYx100      (0x0)
    #define LD_INNO50_TB_12_CS_2D60Hz_PWM_SHIFTx100     (0x420)
    #define LD_INNO50_TB_12_CS_2D60Hz_PWM_DIV           (12)
    #define LD_INNO50_TB_12_CS_2D60Hz_PWM_POLARITY      (0)

    //D 100Hz
    #define LD_INNO50_TB_12_CS_2D100Hz_PWM_DUTYx100      (0x0)
    #define LD_INNO50_TB_12_CS_2D100Hz_PWM_SHIFTx100     (0x6E0)
    #define LD_INNO50_TB_12_CS_2D100Hz_PWM_DIV           (12)
    #define LD_INNO50_TB_12_CS_2D100Hz_PWM_POLARITY      (0)

    //D 120Hz
    #define LD_INNO50_TB_12_CS_2D120Hz_PWM_DUTYx100      (0x0)
    #define LD_INNO50_TB_12_CS_2D120Hz_PWM_SHIFTx100     (0x840)
    #define LD_INNO50_TB_12_CS_2D120Hz_PWM_DIV           (12)
    #define LD_INNO50_TB_12_CS_2D120Hz_PWM_POLARITY      (0)
//========  3D Timing  ========
    #define LD_INNO50_TB_12_PERIOD_3D_SCLK_TO_VSYNC     (0x1665)

    #define LD_INNO50_TB_12_VSYNC_3D_PWM_DUTYx100       (0x0A)
    #define LD_INNO50_TB_12_VSYNC_3D_PWM_SHIFTx100      0
    #define LD_INNO50_TB_12_VSYNC_3D_PWM_DIV            2//12
    #define LD_INNO50_TB_12_VSYNC_3D_PWM_POLARITY       0

    //100hz
    #define LD_INNO50_TB_12_CS_3D_100Hz_PWM_DUTYx100          (0x0)
    #define LD_INNO50_TB_12_CS_3D_100Hz_PWM_SHIFTx100         (0x16E0)
    #define LD_INNO50_TB_12_CS_3D_100Hz_PWM_DIV               (12)
    #define LD_INNO50_TB_12_CS_3D_100Hz_PWM_POLARITY          (0)

    //120hz
    #define LD_INNO50_TB_12_CS_3D_120Hz_PWM_DUTYx100          (0x0)
    #define LD_INNO50_TB_12_CS_3D_120Hz_PWM_SHIFTx100         (0x1860)
    #define LD_INNO50_TB_12_CS_3D_120Hz_PWM_DIV               (12)
    #define LD_INNO50_TB_12_CS_3D_120Hz_PWM_POLARITY          (0)


#endif

#define LD_GAMMA_TABLE_NUM_MAX    16
#define LD_GAMMA_TABLE_SIZE_MAX   256
extern t_sDrvLdCusPtrMap sCusPtrMap_LED_INNO50_TB_12;

//_LED_Device_INNO_50INCH_DIRECT_60_DEC_  U8* Tbl_LD_Gamma[LD_GAMMA_TABLE_NUM_MAX] ;

_LED_Device_INNO_50INCH_TB_12_DEC_ void _LED_INNO50_TB_12_Set_OutputCS(U16 u16OutVFreqX10, BOOL Is3D);
_LED_Device_INNO_50INCH_TB_12_DEC_ void _LED_INNO50_TB_12_Set_SpiClk_Delay_FromVsync(U16 u16OutVFreqX10, BOOL Is3D);

_LED_Device_INNO_50INCH_TB_12_DEC_ U16  LED_INNO50_TB_12_get_OutputVFreq(void);
_LED_Device_INNO_50INCH_TB_12_DEC_ U16  LED_INNO50_TB_12_get_SyncRstCnt(void);

_LED_Device_INNO_50INCH_TB_12_DEC_ void LED_INNO50_TB_12_Config_OutputSignal_To_LED(U16 u16OutVFreqX10, BOOL Is3D);
_LED_Device_INNO_50INCH_TB_12_DEC_ void  _LED_INNO50_TB_12_Set_OutputPWMData(U8 ch, t_LD_Signal OutputSignal);
_LED_Device_INNO_50INCH_TB_12_DEC_ void LED_INNO50_TB_12_Set_OutputSPI_Signal(const U16 * SPI_blocks);
_LED_Device_INNO_50INCH_TB_12_DEC_ U8 LED_INNO50_TB_12_Get_LDLedNum(void);

#endif // #ifndef _LED_Device_INNO_50INCH_DIRECT_60_H_


