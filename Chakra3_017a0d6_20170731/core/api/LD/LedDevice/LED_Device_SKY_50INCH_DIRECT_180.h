#ifndef _LED_Device_SKY_50INCH_DIRECT_180_H_
#define _LED_Device_SKY_50INCH_DIRECT_180_H_


#ifdef _LED_Device_SKY_50INCH_DIRECT_180_C_
    #define _LED_Device_SKY_50INCH_DIRECT_180_DEC_
#else
    #define _LED_Device_SKY_50INCH_DIRECT_180_DEC_  extern
#endif


#include "datatype.h"
#include "leddevice.h"


// div 2
//duty 80.88
//shift 290.86

#if 1

    #define LD_SKY50_VSYNC_PWM_CH_SEL       PWM_CH5
	#define LD_SKY50_CS_PWM_CH_SEL            PWM_CH0


//========  2D Timing  ========
	#define LD_SKY50_PERIOD_2D_SCLK_TO_VSYNC     (0x20)
	
//2D 50Hz
	#define LD_SKY50_VSYNC_2D50Hz_PWM_DUTYx100	 (0x20)
	#define LD_SKY50_VSYNC_2D50Hz_PWM_SHIFTx100  (0x8B00)
	#define LD_SKY50_VSYNC_2D50Hz_PWM_DIV		 (12)
	#define LD_SKY50_VSYNC_2D50Hz_PWM_POLARITY	 (0)

	#define LD_SKY50_CS_2D50Hz_PWM_DUTYx100 	 (0x304)
	#define LD_SKY50_CS_2D50Hz_PWM_SHIFTx100	 (0x83D3)
	#define LD_SKY50_CS_2D50Hz_PWM_DIV			 (12)
	#define LD_SKY50_CS_2D50Hz_PWM_POLARITY 	 (0)

//2D 60Hz
	#define LD_SKY50_VSYNC_2D60Hz_PWM_DUTYx100	 (0x20)
	#define LD_SKY50_VSYNC_2D60Hz_PWM_SHIFTx100  (0x8B00)
	#define LD_SKY50_VSYNC_2D60Hz_PWM_DIV		 (12)
	#define LD_SKY50_VSYNC_2D60Hz_PWM_POLARITY	 (0)

	#define LD_SKY50_CS_2D60Hz_PWM_DUTYx100 	 (0x304)//(0x346)
	#define LD_SKY50_CS_2D60Hz_PWM_SHIFTx100	 (0x83D3)//(0x17)
	#define LD_SKY50_CS_2D60Hz_PWM_DIV			 (12)
	#define LD_SKY50_CS_2D60Hz_PWM_POLARITY 	 (0) 


//========  3D Timing  ========
    #define LD_SKY50_PERIOD_3D_SCLK_TO_VSYNC     (0x80)

	#define LD_SKY50_VSYNC_3D_PWM_DUTYx100		 (5009)
	#define LD_SKY50_VSYNC_3D_PWM_SHIFTx100 	 (12621)
	#define LD_SKY50_VSYNC_3D_PWM_DIV			 12
	#define LD_SKY50_VSYNC_3D_PWM_POLARITY		 0

	#define LD_SKY50_CS_3D_PWM_DUTYx100 		 (0x194)
	#define LD_SKY50_CS_3D_PWM_SHIFTx100		 (0x32)
	#define LD_SKY50_CS_3D_PWM_DIV				 12
	#define LD_SKY50_CS_3D_PWM_POLARITY 		 0

#endif

extern  t_sDrvLdCusPtrMap sCusPtrMap_LED_SKY50;

_LED_Device_SKY_50INCH_DIRECT_180_DEC_ void _LED_SKY50_Set_OutputVFreq(U16 u16OutVFreqX10, BOOL Is3D);
_LED_Device_SKY_50INCH_DIRECT_180_DEC_ void _LED_SKY50_Set_SpiClk_Delay_FromVsync(U16 u16OutVFreqX10, BOOL Is3D);
_LED_Device_SKY_50INCH_DIRECT_180_DEC_ void  _LED_SKY50_Set_OutputPWMData(U8 ch, t_LD_Signal OutputSignal);

_LED_Device_SKY_50INCH_DIRECT_180_DEC_ U16  LED_SKY50_Get_OutputVFreq(U8 ch);
_LED_Device_SKY_50INCH_DIRECT_180_DEC_ U16  LED_SKY50_Get_SyncRstCnt(U8 ch);

_LED_Device_SKY_50INCH_DIRECT_180_DEC_ void LED_SKY50_Config_OutputSignal_To_LED(U16 u16OutVFreqX10, BOOL Is3D);
_LED_Device_SKY_50INCH_DIRECT_180_DEC_ void  LED_SKY50_Set_OutputSPI_Signal(const U16* SPI_blocks);
_LED_Device_SKY_50INCH_DIRECT_180_DEC_ void LED_UIchange_smooth_flag(BOOL smooth_flag_en);

#endif // #ifndef _LED_Device_INX_40INCH_DIRECT_60_H_


