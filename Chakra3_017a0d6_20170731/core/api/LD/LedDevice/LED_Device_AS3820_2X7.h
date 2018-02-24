#ifndef _LED_Device_AS3820_2X7_H_
#define _LED_Device_AS3820_2X7_H_


#ifdef _LED_Device_AS3820_2X7_C_
    #define _LED_Device_AS3820_2X7_DEC_
#else
    #define _LED_Device_AS3820_2X7_DEC_  extern
#endif


#include "datatype.h"
#include "leddevice.h"


#if 1//(LD_ENABLE) //75inch 240Hz

    //#define LD_AS3820_2X7_3D_VSYNC_DIV2_ENABLE     1

//    #define LD_VSYNC_PWM_CH_SEL       PWM_CH1
    //#define LD_AS3820_2X7_CS_PWM_CH_SEL            PWM_CH3


//========  2D Timing  ========
    #define LD_AS3820_2X7_PERIOD_2D_SCLK_TO_VSYNC       0x800//(0x50)

    // 2D 100Hz
    #define LD_AS3820_2X7_CS_2D100Hz_PWM_DUTYx100      (0x0)
    #define LD_AS3820_2X7_CS_2D100Hz_PWM_SHIFTx100     (0x6E0)
    #define LD_AS3820_2X7_CS_2D100Hz_PWM_DIV           (12)
    #define LD_AS3820_2X7_CS_2D100Hz_PWM_POLARITY      (0)

    // 2D 120Hz
    #define LD_AS3820_2X7_CS_2D120Hz_PWM_DUTYx100      (0x0)
    #define LD_AS3820_2X7_CS_2D120Hz_PWM_SHIFTx100     (0x840)
    #define LD_AS3820_2X7_CS_2D120Hz_PWM_DIV           (12)
    #define LD_AS3820_2X7_CS_2D120Hz_PWM_POLARITY      (0)

//========  3D Timing  ========
    //#define LD_AS3820_2X7_PERIOD_3D_SCLK_TO_VSYNC     (0)

    #define LD_AS3820_2X7_VSYNC_3D_PWM_DUTYx100       (0x0A)
    #define LD_AS3820_2X7_VSYNC_3D_PWM_SHIFTx100      0
    #define LD_AS3820_2X7_VSYNC_3D_PWM_DIV            2//12
    #define LD_AS3820_2X7_VSYNC_3D_PWM_POLARITY       0

    //120hz
    #define LD_AS3820_2X7_CS_3D_120Hz_PWM_DUTYx100          (0x0)
    #define LD_AS3820_2X7_CS_3D_120Hz_PWM_SHIFTx100         (0x860)
    #define LD_AS3820_2X7_CS_3D_120Hz_PWM_DIV               (12)
    #define LD_AS3820_2X7_CS_3D_120Hz_PWM_POLARITY          (0)


#endif

#define LD_GAMMA_TABLE_NUM_MAX    16
#define LD_GAMMA_TABLE_SIZE_MAX   256

//extern t_sDrvLdCusPtrMap sCusPtrMap_LED_AS3820_2X7;

//_LED_Device_INNO_50INCH_DIRECT_60_DEC_  U8* Tbl_LD_Gamma[LD_GAMMA_TABLE_NUM_MAX] ;

_LED_Device_AS3820_2X7_DEC_ void _LED_AS3820_2X7_Set_OutputCS(U16 u16OutVFreqX10, BOOL Is3D);
_LED_Device_AS3820_2X7_DEC_ void _LED_AS3820_2X7_Set_SpiClk_Delay_FromVsync(U16 u16OutVFreqX10, BOOL Is3D);

_LED_Device_AS3820_2X7_DEC_ U16  LED_AS3820_2X7_get_OutputVFreq(void);
_LED_Device_AS3820_2X7_DEC_ U16  LED_AS3820_2X7_get_SyncRstCnt(void);

_LED_Device_AS3820_2X7_DEC_ void LED_AS3820_2X7_Config_OutputSignal_To_LED(U16 u16OutVFreqX10, BOOL Is3D);
//_LED_Device_AS3820_2X7_DEC_ void  _LED_AS3820_2X7_Set_OutputPWMData(U8 ch, t_LD_Signal OutputSignal);
_LED_Device_AS3820_2X7_DEC_ void LED_AS3820_2X7_Set_OutputSPI_Signal(const U16 * SPI_blocks);

_LED_Device_AS3820_2X7_DEC_ void AS3820Unlock(void);
_LED_Device_AS3820_2X7_DEC_ void AS3820Lock(void);
_LED_Device_AS3820_2X7_DEC_ void AS3820Init(void);
_LED_Device_AS3820_2X7_DEC_ void AS3820Init2(void);


#endif // #ifndef _LED_Device_INNO_50INCH_DIRECT_60_H_


