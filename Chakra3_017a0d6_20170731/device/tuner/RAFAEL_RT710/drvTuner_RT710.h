
//***********************************************
//RT710 software update: 2015/04/22
//file: header file
//version: v3.6
//***********************************************

//#include "..\stdafx.h"

#ifndef  _RT710_H_ 
#define _RT710_H_

#define UINT8 unsigned char
#define UINT16 unsigned int
#define UINT32 unsigned long


#define VERSION   "RT710(720)_GUI_v3.6"
#define RT710_DEVICE_ADDRESS 0xF4
#define RT710_Reg_Num 16

#define RT710_Xtal 27000
#define RT720_Xtal 24000
//#define RT710_Xtal	16000

#define RT710_0DBM_SETTING 	FALSE   
//#define RT710_0DBM_SETTING 	TRUE  
#define RT710_MIN_INPUT_FREQ 850 //Mhz
#define RT710_MAX_INPUT_FREQ 2300
#define RT710_MUTEX_TIMEOUT  (2000)

typedef enum _RT710_Err_Type
{
	RT_Success = TRUE,
	RT_Fail    = FALSE
}RT710_Err_Type;

typedef enum _RT710_LoopThrough_Type
{
	LOOP_THROUGH = TRUE,
	SIGLE_IN     = FALSE
}RT710_LoopThrough_Type;

typedef enum _RT710_ClockOut_Type
{
	ClockOutOn = TRUE,
	ClockOutOff= FALSE
}RT710_ClockOut_Type;

typedef enum _RT710_OutputSignal_Type
{
	DifferentialOut = TRUE,
	SingleOut     = FALSE
}RT710_OutputSignal_Type;

typedef enum _RT710_AGC_Type
{
	AGC_Negative = TRUE,
	AGC_Positive = FALSE
}RT710_AGC_Type;

typedef enum _RT710_AttenVga_Type
{
	ATTENVGAON = TRUE,
	ATTENVGAOFF= FALSE
}RT710_AttenVga_Type;

typedef enum _R710_FineGain_Type
{
	FINEGAIN_3DB = 0,
	FINEGAIN_2DB,
	FINEGAIN_1DB,
	FINEGAIN_0DB
}R710_FineGain_Type;

typedef enum _RT710_RollOff_Type
{
	ROLL_OFF_0_15 = 0,	//roll-off = 0.15
	ROLL_OFF_0_20,		//roll-off = 0.2
	ROLL_OFF_0_25,		//roll-off = 0.25
	ROLL_OFF_0_30,		//roll-off = 0.3
	ROLL_OFF_0_35,		//roll-off = 0.35
	ROLL_OFF_0_40,		//roll-off = 0.4
}RT710_RollOff_Type;


typedef enum _RT710_Scan_Type
{
    RT710_AUTO_SCAN = TRUE,	//Blind Scan 
    RT710_MANUAL_SCAN= FALSE	//Normal(Default)
}RT710_Scan_Type;

typedef struct _RT710_RF_Gain_Info
{
	UINT8   RF_gain;

}RT710_RF_Gain_Info;

typedef struct _RT710_INFO_Type
{
    unsigned long RF_KHz;
    unsigned long SymbolRate_KHz;
    RT710_RollOff_Type RT710_RollOff_Mode;
    RT710_LoopThrough_Type RT710_LoopThrough_Mode;
    RT710_ClockOut_Type RT710_ClockOut_Mode;
    RT710_OutputSignal_Type RT710_OutputSignal_Mode;
    RT710_AGC_Type RT710_AGC_Mode;
    RT710_AttenVga_Type RT710_AttenVga_Mode;
    R710_FineGain_Type R710_FineGain;
    RT710_Scan_Type RT710_Scan_Mode;
}RT710_INFO_Type;

typedef enum _TUNER_NUM
{
    RT710_TUNER_1 = 0,
    RT710_TUNER_2,
    RT710_TUNER_3,
    RT710_TUNER_4,
    MAX_TUNER_NUM
}RT710_TUNER_NUM_TYPE;

typedef struct _RT710_Handle
{
   MS_S32 RT710_Mutex;
   MS_U8 I2C_SalveID;
   MS_U8 Initial_done_flag;
   MS_U8 Chip_type_Is_RT710;
   MS_U32 satellite_bw;
   MS_U32 pre_satellite_bw;
   RT710_INFO_Type Info_Msg;
   unsigned char Reg_Arry[RT710_Reg_Num];
}RT710_Handle;

//----------------------------------------------------------//
//                   RT710 Function                         //
//----------------------------------------------------------//
RT710_Err_Type RT710_Setting(MS_U8 u8TunerIndex);
RT710_Err_Type RT710_GetRfGain(MS_U8 u8TunerIndex,RT710_RF_Gain_Info *RT710_rf_gain);
RT710_Err_Type RT710_GetRfRssi(MS_U8 u8TunerIndex,unsigned long RF_Freq_Khz, int *RfLevelDbm, UINT8 *fgRfGainflag);
RT710_Err_Type RT710_Standby(MS_U8 u8TunerIndex,RT710_LoopThrough_Type RT710_LTSel,RT710_ClockOut_Type RT710_CLKSel);
MS_BOOL RT710_PLL_Lock(MS_U8 u8TunerIndex);


typedef struct _I2C_LEN_TYPE
{
	UINT8 RegAddr;
	UINT8 Data[50];
	UINT8 Len;
}I2C_LEN_TYPE;

typedef struct _I2C_TYPE
{
	UINT8 RegAddr;
	UINT8 Data;
}I2C_TYPE;

MS_BOOL I2C_Write_Len(MS_U8 u8TunerIndex, I2C_LEN_TYPE *I2C_Info);
MS_BOOL I2C_Read_Len(MS_U8 u8TunerIndex,I2C_LEN_TYPE *I2C_Info);
int RT710_Convert(int InvertNum);

//----------------------------------------------------------//
//                   RT710 Public Function                       //
//----------------------------------------------------------//
#define RT710_Delay_MS MsOS_DelayTask

//MS_BOOL MDrv_Tuner_SetFreq(MS_U16 u16CenterFreq, MS_U32 u32SymbolRate_Hz);
//MS_BOOL MDrv_Tuner_Initial(void);
#endif


