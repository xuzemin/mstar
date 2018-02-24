#ifndef  _R842_H_ 
#define _R842_H_

#include "R840_842.h"

#define R842_VERSION     "R842_v1.9E4"
#define R842_VER_NUM     9
#define R842_CHIP_ID     0x97
#define R842_ATV_CIF_5M  TRUE//FALSE     //by CTMR
//----------------------------------------------------------//
//                   Type Define                                    //
//----------------------------------------------------------//
#define UINT8  unsigned char
#define UINT16 unsigned short
#define UINT32 unsigned long
#define INT8   signed char
#define INT16  signed short
#define INT32  signed int

#define TRUE   1
#define FALSE 0
//----------------------------------------------------------//
//                   Define                                            //
//----------------------------------------------------------//
#define R842_REG_NUM          48  //R0~R7: read only
#define R842_TF_HIGH_NUM      8  
#define R842_TF_MID_NUM       11
#define R842_TF_LOW_NUM       9
#define R842_RING_POWER_FREQ  115000
//#define R842_IMR_IF           5300         
#define R842_IMR_TRIAL        9
#define R842_IMR_GAIN_REG     20
#define R842_IMR_PHASE_REG    21
#define R842_IMR_IQCAP_REG    19
#define R842_IMR_POINT_NUM    8
//----------------------------------------------------------//
//                   Internal Structure                            //
//----------------------------------------------------------//
typedef struct _R842_Sys_Info_Type
{
	UINT16      IF_KHz;            
	UINT16      FILT_CAL_IF; 
	UINT8       BW;
	UINT8       HPF_COR;
	UINT8       FILT_EXT_ENA;
	UINT8       FILT_EXT_POINT;
	UINT8       HPF_EXT_SEL;      
	UINT8		HPF_NOTCH;    
	UINT8       DET_LPF_AUTO;  
	UINT8       LPF_CUR; 
	UINT8		FILT3_COMP; 
	UINT8		FILT5_FORCEQ;   
	UINT8		FILT5_AUTO_COMP;   
	UINT8       FILT5_MAN_COMP;  
	UINT8		RF_LTE_PSG;  
	UINT8       RFAGC_CTRL;  
	UINT8		NA_PWR_DET;      
	UINT8       POLY_CUR; 
}R842_Sys_Info_Type;

typedef struct _R842_Freq_Info_Type
{
	UINT8		RF_POLY;
	UINT8		LNA_BAND;
	UINT8		LPF_CAP;
	UINT8		LPF_NOTCH;
	UINT8		IMR_MEM_NOR;
	UINT8		IMR_MEM_REV;
	UINT8       BYP_LPF;
	UINT8       TEMP;    
}R842_Freq_Info_Type;

typedef struct _R842_SysFreq_Info_Type
{
	UINT8		LNA_TOP;
	UINT8		LNA_VTL_H;
	UINT8       RF_TOP;
	UINT8       RF_VTL_H;
	UINT8       RF_GAIN_LIMIT;
	UINT8       NRB_TOP;
	UINT8       NRB_BW_HPF;
	UINT8       NRB_BW_LPF;
	UINT8		MIXER_TOP;
	UINT8		MIXER_VTH;
	UINT8		MIXER_VTL;
	UINT8       MIXER_GAIN_LIMIT; //
	UINT8       FILTER_TOP;
	UINT8       FILTER_VTH;
	UINT8       FILTER_VTL;
	UINT8       LNA_RF_DIS_MODE; 
	UINT8       LNA_RF_DIS_CURR;   
	UINT8       LNA_DIS_SLOW_FAST; 
	UINT8       LNA_RF_CHARGE; 
	UINT8       RF_DIS_SLOW_FAST;   //20
	UINT8       BB_DET_MODE;
	UINT8       BB_DIS_CURR;
	UINT8       MIXER_FILTER_DIS;
	UINT8       IMG_NRB_ADDER;
	UINT8       ENB_POLYG;    //L
	UINT8       VGA_PIN_LVL; //L
	UINT8       VGA_PIN_DEL; //L
	UINT8       VGA_OUT_ATT; //L
	UINT8       FILT3_GAIN_MAN; //L
	UINT8	    TF_MODE;  //30
	UINT8       HYS_MIXTOP;
	UINT8       Q_CTRL;
	UINT8       HPF_COMP;         
	UINT8       FB1_RES;     
	UINT8	    MIXER_AMP_LPF;  
	UINT8       DET_BW_LPF;
	UINT8       ENB_ATT;
	UINT8       TEMP;
}R842_SysFreq_Info_Type;

typedef struct _R842_Cal_Info_Type
{
	UINT8		FILTER_6DB;   //no use
	UINT8       TF_PATH;
	UINT8		MIXER_AMP_GAIN;
	UINT8		MIXER_BUFFER_GAIN;
	UINT8		LNA_GAIN;
	UINT8		LNA_POWER;
	UINT8		RFBUF_POWER;
	UINT8		RFBUF_OUT;
}R842_Cal_Info_Type;

typedef struct _R842_Sect_Type
{
	UINT8   Phase_Y;
	UINT8   Gain_X;
	UINT8   Iqcap;
	UINT8   Value;
}R842_Sect_Type;

typedef struct _R842_TF_Result
{
	UINT8   TF_Set;
	UINT8   TF_Value;
}R842_TF_Result;

typedef enum _R842_TF_Type
{	
	R842_TF_270N_39N = 0,  //270n/39n   (DTV Terr) 
	R842_TF_BEAD_68N,      //Bead/68n   (China DVB-C, DTMB, ATV) 
	R842_TF_270N_27N,
	R842_TF_BEAD_27N,
	R842_TF_390N_27N,
	R842_TF_390N_39N,        //only for LGIT
	R842_TF_SIZE
}R842_TF_Type;

typedef enum _R842_UL_TF_Type
{
	R842_UL_USING_BEAD = 0,            
    R842_UL_USING_270NH,                      
	R842_UL_USING_390NH,  
}R842_UL_TF_Type;

typedef enum _R842_MID_TF_Type
{
	R842_MID_USING_27NH = 0,            
	R842_MID_USING_39NH,      //39n
	R842_MID_USING_68NH,      //68n
}R842_MID_TF_Type;

typedef enum _R842_Cal_Type
{
	R842_IMR_CAL = 0,
	R842_IMR_LNA_CAL,
	R842_TF_MID_LNA_CAL,
	R842_TF_LNA_CAL,
	R842_LPF_CAL,
	R842_LPF_LNA_CAL
}R842_Cal_Type;

typedef enum _R842_Xtal_Pwr_Type
{
	//lowest, 1.5 (0)
	//lowest, 2.0 (1)
	//low, 1.5 (2)
    //low, 2.0 (3)
	//high, 1.5 (4)
	//high, 2.0 (5)
	//highest, 1.5 (6)
	//highest, 2.0 (7)
    R842_XTAL_HIGHEST = 7,
	R842_XTAL_CHECK_SIZE = 8
}R842_Xtal_Pwr_Type;

typedef enum _R842_Share_Xtal_Type
{
	R842_NO_SHARE_XTAL = 0,                     //normal 
	R842_MASTER_TO_SLAVE_XTAL_IN,     //power max, cap min     
    R842_MASTER_TO_SLAVE_XTAL_OUT,  //power max, cap min
    R842_SLAVE_XTAL_OUT,                         //xtal_gm off (R32[4:3]=2'b11), cap min
    R842_SLAVE_XTAL_IN,                            //no use. power max? cap?
}R842_Share_Xtal_Type;

typedef enum _R842_IMR_Type  
{
	R842_IMR_NOR=0,
	R842_IMR_REV,
}R842_IMR_Type;

typedef enum _R842_TF_Mode_Type  
{
	R842_TF_AUTO=0,
	R842_TF_PLAIN,
	R842_TF_SHARP,
}R842_TF_Mode_Type;

typedef enum _R842_Chip_Type  //Don't modify chip list
{
	R842_MP=0,
	R842_MT,
	//R842_MT1,   //not release
}R842_Chip_Type;

typedef enum _R842_Poly_Type  
{
	R842_Poly_0=0,
	R842_Poly_3,
	R842_Poly_5,	
}R842_Poly_Type;
//----------------------------------------------------------//
//                   R842 Public Parameter                     //
//----------------------------------------------------------//
typedef enum _R842_ErrCode
{
	R842_Success = TRUE,
	R842_Fail = FALSE
}R842_ErrCode;

typedef enum _R842_Standard_Type  //Don't remove standand list!!
{
	//ATV normal IF (prefer to use)
	R842_MN_5100 = 0,              //for NTSC_MN, PAL_M (VIF=5.1M)
	R842_MN_5800,                  //for NTSC_MN, PAL_M (VIF=5.8M)
	R842_PAL_I,                    //for PAL-I          (VIF=7.3M)
	R842_PAL_DK,                   //for PAL DK         (VIF=7.3M)
	R842_PAL_B_7M,                 //for PAL-B 7M       (VIF=6.6M)
#if(R842_ATV_CIF_5M==TRUE)
	R842_PAL_B_7M_6800,            //for PAL-B 7M       (VIF=6.8M)
#endif
	R842_PAL_BGH_8M,               //for PAL G/H 8M     (VIF=6.6M)
	R842_SECAM_L,                  //for SECAM L        (VIF=7.3M)
	R842_SECAM_L1,                 //for SECAM L'       (VIF=2.25M)
	R842_SECAM_L1_INV,             //for SECAM L'       (VIF=7.3M)
#if(R842_ATV_CIF_5M==TRUE)
	//ATV CIF=5M, (not prefer to use) 
	R842_MN_CIF_5M,                //for NTSC_MN, PLA_M (CIF=5M, VIF=6.75M)
	R842_PAL_I_CIF_5M,             //for PAL-I          (CIF=5M, VIF=7.75M)
	R842_PAL_DK_CIF_5M,            //for PAL DK         (CIF=5M, VIF=7.75M)
	R842_PAL_B_7M_CIF_5M,          //for PAL-B 7M       (CIF=5M, VIF=7.25M)
	R842_PAL_BGH_8M_CIF_5M,        //for PAL G/H 8M     (CIF=5M, VIF=7.75M)
	R842_SECAM_L_CIF_5M,           //for SECAM L        (CIF=5M, VIF=7.75M)
	R842_SECAM_L1_CIF_5M,          //for SECAM L'       (CIF=5M, VIF=2.25M)
	R842_SECAM_L1_INV_CIF_5M,      //for SECAM L'       (CIF=5M, VIF=7.75M)
#endif
	R842_ATV_SIZE,
	//DTV
	R842_DVB_T_6M = R842_ATV_SIZE,  
	R842_DVB_T_7M,
	R842_DVB_T_8M, 
    R842_DVB_T2_6M,       //IF=4.57M
	R842_DVB_T2_7M,       //IF=4.57M
	R842_DVB_T2_8M,       //IF=4.57M
	R842_DVB_T2_1_7M,
	R842_DVB_T2_10M,
	R842_DVB_C_8M,
	R842_DVB_C_6M, 
	R842_J83B,
	R842_ISDB_T_4063,       //IF=4.063M
	R842_ISDB_T_4570,       //IF=4.57M
	R842_DTMB_8M_4570,      //IF=4.57M
	R842_DTMB_6M_4500,      //IF=4.5M, BW=6M
	R842_ATSC,  
	//DTV IF=5M
	R842_DVB_T_6M_IF_5M,
	R842_DVB_T_7M_IF_5M,
	R842_DVB_T_8M_IF_5M,
	R842_DVB_T2_6M_IF_5M,
	R842_DVB_T2_7M_IF_5M,
	R842_DVB_T2_8M_IF_5M,
	R842_DVB_T2_1_7M_IF_5M,
	R842_DVB_C_8M_IF_5M,
	R842_DVB_C_6M_IF_5M, 
	R842_J83B_IF_5M,
	R842_ISDB_T_IF_5M,            
	R842_DTMB_8M_IF_5M,     
	R842_DTMB_6M_IF_5M,     
	R842_ATSC_IF_5M,  
	R842_FM,
	R842_STD_SIZE,
}R842_Standard_Type;


typedef enum _R842_RF_Gain_Type
{
	
	R842_RF_AUTO = 0,
	R842_RF_MANUAL
}R842_RF_Gain_Type;

typedef enum _R842_Xtal_Div_Type
{
	R842_XTAL_DIV1_11 = 0,
	R842_XTAL_DIV2_12,
	R842_XTAL_DIV2_21,
	R842_XTAL_DIV4_22
}R842_Xtal_Div_Type;

typedef enum _R842_IfAgc_Type
{
	R842_IF_AGC1 = 0,
	R842_IF_AGC2
}R842_IfAgc_Type;

typedef struct _R842_Set_Info
{
	UINT32                 RF_KHz;
	R842_Standard_Type     R842_Standard;
	R842_IfAgc_Type        R842_IfAgc_Select; 
}R842_Set_Info;

typedef struct _R842_RF_Gain_Info
{
	UINT16  RF_gain_comb;
	UINT8   RF_gain1;
	UINT8   RF_gain2;
	UINT8   RF_gain3;
	UINT8   RF_gain4;
}R842_RF_Gain_Info;

typedef enum _R842_TuneMode_Type
{
	R842_AUTO_SCAN = 0,
	R842_CHANNEL_CHANGE
}R842_TuneMode_Type;

typedef enum _R842_ATV_IF_Type  
{
	R842_NORMAL = 0,
	R842_8296,
}R842_ATV_IF_Type;
//----------------------------------------------------------//
//                   R842 Public Function                       //
//----------------------------------------------------------//
#define R842_Delay_MS	msAPI_Timer_Delayms 

R842_ErrCode R842_Init(void);
R842_ErrCode R842_SetPllData(R842_Set_Info R842_INFO);               //old set frequency function, replaced by below function
R842_ErrCode R842_SetPllData_Mode(R842_Set_Info R842_INFO, R842_TuneMode_Type R842_TuningMode);  //New tuning function that can specify Channel_Change or Auto_Scan by R842_TuningMode
R842_ErrCode R842_Standby(void);
R842_ErrCode R842_WakeUp(void);
R842_ErrCode R842_GetTotalRssi(UINT32 RF_Freq_Khz, R842_Standard_Type RT_Standard, INT32 *RssiDbm);   //*RssiDbm is dBm*1
R842_ErrCode R842_GetTotalRssi2(UINT32 RF_Freq_Khz, R842_Standard_Type RT_Standard, INT32 *RssiDbm);  //*RssiDbm is dBm*10
R842_ErrCode R842_SetXtalCap(UINT8 u8XtalCap); 
UINT8 R842_PLL_Lock(void);
R842_ErrCode R842_AGC_Slow(void);
//--------------------for GUI test--------------------------//
R842_ErrCode R842_GetRfGain(R842_RF_Gain_Info *pR842_rf_gain);
R842_ErrCode R842_RfGainMode(R842_RF_Gain_Type R842_RfGainType);
R842_ErrCode R842_SetIfFreq(UINT16 IF_KHz, UINT32 RF_KHz, R842_Standard_Type u1SystemStd);
R842_ErrCode R842_SetLpfBw(UINT8 LPF_BW);
R842_ErrCode R842_SetLpfOffset(UINT8 LPF_Offset);
R842_ErrCode R842_SetHpfOffset(UINT8 HPF_Offset);
R842_ErrCode R842_SetIfLpf(UINT32 LPF_Cor_Freq);
R842_ErrCode R842_CheckMaxGain(void);
//--------------------Test function-----------------------//
R842_ErrCode R842_Dump_Data(void);
R842_ErrCode R842_RfGainCtrl(R842_RF_Gain_Type R842_RfGainType, UINT8 LnaGain, UINT8 RfGain, UINT8 MixerGain, UINT8 FilterGain);

extern UINT8 R842_IC_Check(void);
extern UINT8 R842_Gain_Check(void);
extern UINT8 R842_UL_TF_Check(void);
extern UINT8 R842_I2C_Check(void);
extern UINT8 R842_IMR_Check(void);

R842_ErrCode R842_GetIfRssi(UINT32 *VgaGain);
R842_ErrCode R842_GetRfRssi(UINT32 RF_Freq_Khz, R842_Standard_Type RT_Standard, INT32 *RfGain);
//For GUI initial use. When initial, set these two flags to FALSE and call R842_Init()
extern UINT8   R842_Initial_done_flag;
extern UINT8   R842_IMR_done_flag;

//<<SMC jayden.chen add for R842 20150616
//---------------I2C--------------------------
UINT8 R842_Chip_Detect(void);
bool R842_I2C_Write_Len(I2C_LEN_TYPE *I2C_Info);
bool R842_I2C_Read_Len(I2C_LEN_TYPE *I2C_Info);
bool R842_I2C_Write(I2C_TYPE *I2C_Info);
int R842_Convert(int InvertNum);
BOOLEAN R842_devTunerInit(void);
//----------------------------------------------------------------------------------------
//>>SMC jayden.chen add for R842 20150616
#endif
