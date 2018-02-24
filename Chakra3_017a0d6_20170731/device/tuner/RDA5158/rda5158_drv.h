/*

version 1.0 2014.3.31
 Draft version

version 1.1 2014.4.18
 * 添加Sleep，CSSI功能函数 [Lina]

 version 1.1 2014.07.04
* 添加ATSC_MODe  Get/Set 函数 [Lina]


*/

//----------------------------------------------------------//
//                   Type Define                                    //
//----------------------------------------------------------//
#define MAPI_U16 MS_U16
#define MAPI_U32 MS_U32
#define MAPI_U8 MS_U8

/*
#define MAPI_U8 MS_U8
#define MAPI_U16 MS_U16
#define MAPI_U32 MS_U32
#define MAPI_BOOL MS_BOOL
#define MAPI_S16 MS_S16
*/


#ifndef	_RDA5158_H
#define	_RDA5158_H

#define RDA5880DM_PRODUCT_ID   0x5176

#define RDA5880DM_CHIP_ID_0    0x62
#define RDA5880DM_CHIP_ID_1    0x61

#define	RDATV_XTAL              (24)    //(Mhz)

//DTV
#define RDATV_IF_FREQ           (5000)
#define TUNER_NAME              "RDA5158"

#define TN_FREQ_SS_INVERSE_625          16   // 1/0.0625
#define TN_RSA_RSB_625                  0x06
#define TN_FREQ_SS_625                  62.5  // kHz

#define TN_FREQ_SS_50                  	50  // kHz
#define TN_FREQ_SS_INVERSE_50         	20   // 1/0.05
#define TN_RSA_RSB_50                  	0
#define PAGE_AFE_SDM 0x010
#define PAGE_AGC_TUNER 0x014
#define PAGE_DEMOD_SCU 0x008
//#define RDA_DELAY_MS(cnt) RDA_DELAY_MS();


typedef struct
{
    MAPI_U32 add;
    MAPI_U16 wdata;
    MAPI_U16 delay;
}RDA_TVM_REG;

typedef enum
{
    FREQ_LO_INDEX_2 = 0,
    FREQ_LO_INDEX_4,
    FREQ_LO_INDEX_8,
    FREQ_LO_INDEX_16,
    FREQ_LO_INDEX_32,
    FREQ_LO_INDEX_QTY
}RDA_TV_FREQ_LO_INDEX;

typedef enum
{
    XTAL_SOLO_MODE,
    XTAL_MDLL_MODE
}XTAL_MODE_T;

typedef enum
{
    RDA_DK = 0,
    RDA_I,    // 1
    RDA_GH,
    RDA_B,
    RDA_N,
    RDA_M,
    RDA_L,
    RDA_L1,
    RDA_DTV_6M,    //8
    RDA_DTV_7M,
    RDA_DTV_8M,
    RDA_TV_MODE_QTY=11
}RDA_TV_MODE;

typedef enum
{
    mauto=0,
    manual
}RDA_TV_IFOUT_MODE;

typedef enum
{
    ADC_162=0,
    ADC_172,
    ADC_182
}RDA_TV_ADC_INDEX;

/************************************************************
ATV/DTMB/ATSC
|   -
DVB_T/DVB_T2/ISBT

DVB_C
************************************************************/
typedef enum
{
    LNA_SEL_L1,    //LNA_SEL_900_480
    LNA_SEL_L2,    //LNA_SEL_480_270
    LNA_SEL_L3,    //LNA_SEL_270_124
    LNA_SEL_L4      //LNA_SEL_124_27
}RDA_TV_LNA_SELECT;

typedef enum
{
    X,
    MSB3393,
}RDA_TV_DEMOD_MACH;

typedef enum
{
    TUNER_CHIP_MODE_IFOUT,
    TUNER_CHIP_MODE_CVBS,
    TUNER_CHIP_MODE_FM
}RDA_TUNER_CHIP_MODE;

typedef enum
{
    LNA_ATSC_MODE,
    LNA_DTMB_MODE,
    LNA_ATV_MODE,
    LNA_DVBT_MODE,
    LNA_ISDBT_MODE,
    LNA_DVBC_MODE,
}RDA_TV_LNA_MODE;

typedef enum
{
	LNA_ATSC_CABLE = 0,
	LNA_ATSC_AIR,
}RDA_TV_ATSC_MODE;


struct rda_tuner_cfg
{
    XTAL_MODE_T xtal_mode;
    RDA_TV_FREQ_LO_INDEX freq_lo_index;
    RDA_TV_ADC_INDEX freq_adc_index;
    RDA_TUNER_CHIP_MODE chip_mode;    
    RDA_TV_MODE tv_mode_index;
    MAPI_U8 lna_index;
    RDA_TV_DEMOD_MACH demod_mach;
    RDA_TV_LNA_MODE lna_mode;
    RDA_TV_ATSC_MODE atsc_mode;
		
    MAPI_U16 lna_cap;
    MAPI_U16 xtal;
    MAPI_U16 i2vth_dtvh;
    MAPI_U16 i2vth_dtvl;
    MAPI_U16 i2vth_atvh;
    MAPI_U16 i2vth_atvl;
    MAPI_U32 freq;
    MAPI_U32 freq_lo;
    MAPI_U32 freq_vco_core;
    MAPI_U32 mdll_n;
    MAPI_U32 freq_if_out;
};

typedef struct rda_tuner_cfg  *RDA_TUNER_CFG;

typedef struct
{
    MAPI_U32 freq;
    MAPI_U16 delta;
    RDA_TV_ADC_INDEX adc;
}RDA_TV_ADC_BY_FRE;


typedef struct _RDA5158_func
{
    BOOLEAN (*WriteBytes)(U8,U8*,U16,U8*);
    BOOLEAN (*ReadBytes)(U8,U8*,U16,U8*);
}S_RDA5158_func, *pS_RDA5158_func;

BOOLEAN rdaTVInitial(void);
MS_BOOL rdaTVTunerOpen(RDA_TUNER_CFG tuner_cfg);
void rdaTVAGC(void);
void rdaTVIQSwap(MAPI_U8 flag);
void rdaDTVSETTING(RDA_TUNER_CFG tuner_cfg);
void rdaATVSETTING(RDA_TUNER_CFG tuner_cfg);
void rdaTVXtalSet(RDA_TUNER_CFG tuner_cfg);
void rdaTVSetFreq_tune(MAPI_U32 freq,MAPI_U32 bw,RDA_TUNER_CFG tuner_cfg);
void rdaTVFreqloIndexSet(RDA_TUNER_CFG tuner_cfg);
void rdaTVModeIndexSet(RDA_TUNER_CFG tuner_cfg,RDA_TV_MODE mode);
MAPI_U32 rdaTVMulDivCompensate(MAPI_U32 par1,MAPI_U32 par2,MAPI_U32 par3);
RDA_TV_ADC_INDEX rdaTVGetAdcByFreq(MAPI_U32 freq);
void rdaTVDtvFreqTuneSet(MAPI_U32 freq,MAPI_U16 eBand, MAPI_U8 mATSC_Mode);
void rdaTVAtvFreqTuneSet(MAPI_U32 freq, RDA_TV_MODE tv_mode);
MAPI_U32 rdaTVGetFreq_lo(void);
MAPI_U16 rdaTVLNACapGet(RDA_TUNER_CFG tuner_cfg);
MAPI_U32 rdaTVDetected(void);
void rdaTVLNAIndexGet(RDA_TUNER_CFG tuner_cfg);
void rdaTVPllCalSet(RDA_TUNER_CFG tuner_cfg);
void rdaTVRFPLLSDMSet(RDA_TUNER_CFG tuner_cfg);
void rdaTVTunerModeSet(RDA_TUNER_CFG tuner_cfg);
void rdaTVRfBpset(RDA_TUNER_CFG tuner_cfg,MAPI_U8 s_value);
void rdaTVIfOutSet(RDA_TUNER_CFG tuner_cfg);
void rdaTVI2vTh(RDA_TUNER_CFG tuner_cfg);
void rdaTVBBPLLSDMSet(RDA_TUNER_CFG tuner_cfg);
MS_BOOL i2c0SendData(MAPI_U8 addr, MAPI_U16 wdata);
void rdaDemodFirmwareDL(void);
void rdaTVSleepnoloop(void);
void rdaTVSleepwithloop(void);
MAPI_U16 rdaTVSingalStrength(void);
void rdaTV8051Init(void);
void rdaTV8051Start(void);
void rdaTV8051Stop(void);
void rdaDemodFirmwareDL(void);
MAPI_U16 i2c0GetData(MAPI_U8 addr);
MS_BOOL i2c1SendData(MAPI_U16 page, MAPI_U32 offset, MAPI_U16 wdata);
MAPI_U16 i2c1GetData(MAPI_U16 page, MAPI_U32 offset);
MS_BOOL i2c1SendDataA(MAPI_U32 addr, MAPI_U16 wdata);
void RDA_DELAY_MS(MAPI_U32 cnt);

//void rdaTVSetATSCMode(MAPI_U16 mATSC_Mode);


#endif



