/*****************************************************************************
Copyright 2012-2020, AltoBeam Inc. All rights reserved.

File Name: atbm886x.h
******************************************************************************/
#ifndef ATBM887X_H
#define ATBM887X_H

/*Common data type redefine for atbm886x.h/c*/
typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;


#ifndef PI
#define PI (3.1415927)
#endif


#define ATMB_DBG_OUTPUT   1



/**********************************************************************************************************************************
*struct MPEG_TS_mode_t
*@ui8TSTransferType: TS stream transfer type, can be set to parallel(8 bit data bus) or serial(1 bit data bus) mode
*@Demod output edge: demod will output TS data on this edge of TS stream clock
*@ui8SPIClockConstantOutput: TS stream clock can be set outputting all the time or only during TS data valid (188 bytes)
**********************************************************************************************************************************/
/*****************ui8TSTransferType Option Value***************************/
#define TS_PARALLEL_MODE             1
#define TS_SERIAL_MODE               0
/**********************ui8OutputEdge Option Value***************************/
#define TS_OUTPUT_FALLING_EDGE       1
#define TS_OUTPUT_RISING_EDGE        0
/**********************ui8TSSPIMSBSelection Option Value******************/
#define TS_SPI_MSB_ON_DATA_BIT7      1
#define TS_SPI_MSB_ON_DATA_BIT0      0
/**********************ui8TSSSIOutputSelection Option Value***************/
#define TS_SSI_OUTPUT_ON_DATA_BIT7   1
#define TS_SSI_OUTPUT_ON_DATA_BIT0   0
/**********************ui8SPIClockConstantOutput Option Value*************/
#define TS_CLOCK_CONST_OUTPUT        1
#define TS_CLOCK_VALID_OUTPUT        0
typedef struct MPEG_TS_mode_t
{
    uint8 ui8TSTransferType;
    uint8 ui8OutputEdge;
    uint8 ui8TSSPIMSBSelection;
    uint8 ui8TSSSIOutputSelection;
    uint8 ui8SPIClockConstantOutput;
}MPEG_TS_mode_t;

/**********************************************************************************************************************************
*struct DVBC_Params_t
*i32SymbolRate: typically use 6875K
*ui8InputMode : for DVBC parameter config
**********************************************************************************************************************************/
/**********************ui8InputMode Option Value****************************/
#define DVBC_IF_INPUT                0
#define DVBC_IQ_INPUT                1
typedef struct DVBC_Params_t
{
    uint8 ui8InputMode;
    int      i32SymbolRate;
}DVBC_Params_t;

/**********************************************************************************************************************************
*struct tuner_config_t
*@dbIFFrequency: tuner IF frequency output in MHz.  Most CAN Tuners' are 36M, 36.166M
*@or 36.125 MHz (Typical IF used by DVB-C tuners)
*@ui8IQmode: demod needs to know if IQ is swapped or not on hardware board
**********************************************************************************************************************************/
/**********************ui8IQmode Option Value*******************************/
#define SWAP_IQ                      0
#define NO_SWAP_IQ                   1
typedef struct tuner_config_t
{
    uint8  ui8IQmode;
    uint8  ui8DTMBBandwithMHz;/**/
    double dbIFFrequency;
}tuner_config_t;

/**********************************************************************************************************************************
* struct     custom_config_t
*@tuner_config: struct of tuner configuration
*@stTsMode: struct of TS mode
*@ui8CrystalOrOscillator: demod can use crystal or oscillator
*@dbSampleClkFrequency: crystal or oscillator frequency on hardware board for demod
*@ui8DtmbDvbcMode:select receiving mode DTMB or DVB-C for ATBM886x
*@stDvbcParams: DVB-C parameters
**********************************************************************************************************************************/
/**********************ui8CrystalOrOscillator Option Value*****************/
#define CRYSTAL                      0
#define OSCILLATOR                   1
/**********************ui8DtmbDvbcMode Option Value************************/
#define ATBM_DTMB_MODE               1
#define ATBM_DVBC_MODE               0
typedef struct custom_config_t
{
    uint8          ui8CrystalOrOscillator;
    uint8          ui8DtmbDvbcMode;
    tuner_config_t stTunerConfig;
    MPEG_TS_mode_t stTsMode;
    double         dbSampleClkFrequency;
    DVBC_Params_t  stDvbcParams;
}custom_config_t;

typedef enum _ATBM_I2CREADWRITE_STATUS
{
    ATBM_I2CREADWRITE_OK    =0,
    ATBM_I2CREADWRITE_ERROR
}ATBM_I2CREADWRITE_STATUS;



typedef enum _DTMB_QAM_INDEX
{
    DTMB_QAM_UNKNOWN = 0,
    DTMB_QAM_4QAM_NR,
    DTMB_QAM_4QAM,
    DTMB_QAM_16QAM,
    DTMB_QAM_32QAM,
    DTMB_QAM_64QAM
}DTMB_QAM_INDEX;

// Code rate
typedef enum _DTMB_CODE_RATE
{
    DTMB_CODE_RATE_UNKNOWN = 0,
    DTMB_CODE_RATE_0_DOT_4,
    DTMB_CODE_RATE_0_DOT_6,
    DTMB_CODE_RATE_0_DOT_8
}DTMB_CODE_RATE;

// Time interleaving
typedef enum _DTMB_TIME_INTERLEAVE
{
    DTMB_TIME_INTERLEAVER_UNKNOWN = 0,
    DTMB_TIME_INTERLEAVER_240,
    DTMB_TIME_INTERLEAVER_720
}DTMB_TIME_INTERLEAVE;

//Single carrier or Multi-Carrier
typedef enum _DTMB_CARRIER_MODE
{
    DTMB_CARRIER_UNKNOWN = 0,
    DTMB_SINGLE_CARRIER,
    DTMB_MULTI_CARRIER
}DTMB_CARRIER_MODE;

typedef enum _DTMB_GUARD_INTERVAL
{
    GI_UNKNOWN = 0,
    GI_420,
    GI_595,
    GI_945
}DTMB_GUARD_INTERVAL;

typedef struct STRU_DTMB_SIGNAL_PARAMS
{
    DTMB_CARRIER_MODE dtmb_carrier_mode;
    DTMB_QAM_INDEX dtmb_qam_index;
    DTMB_CODE_RATE dtmb_code_rate;
    DTMB_TIME_INTERLEAVE dtmb_time_interleave;
    DTMB_GUARD_INTERVAL dtmb_guard_interval;
}DTMB_SIGNAL_PARAMS;


/********DTMB and DVB-C common API functions******************************/
int    ATBMPowerOnInit(void);
uint8  ATBMChipID(void);
void   ATBMI2CByPassOn(void);
void   ATBMI2CByPassOff(void);
int    ATBMLockedFlag(void);
int    ATBMChannelLockCheck(void);
int    ATBMChannelLockCheckForManual(void);
void   ATBMHoldDSP(void);
void   ATBMStartDSP(void);
void   ATBMStandby(void);
void   ATBMStandbyWakeUp(void);
void   ATBMSuspend(void);

/****DTMB API Functions***************************************************/
void   ATBMSetDTMBMode(void);
int    ATBMSignalStrength(void);
double ATBMSignalNoiseRatio(void);
int    ATBMSignalQuality(void);
double ATBMFrameErrorRatio(void);
double ATBMPreBCHBlockErrorRatio(void);
double ATBMBER_Calc(void);
int    ATBM_PPM_Test(void);
double ATBMCarrierOffset(void);

/****DVBC API Macro define************************************************/
#define ATBM_DEBUG_DVBC                           0      /*default no debug output*/
#define CMS0022_COARSE_CARRIER_ACQ_SWEEP_STEP    (0.05)
#define DVBC_SAMPLE_RATE_ADDR                     0x210
#define DVBC_SAMPLE_RATE_RECIP_ADDR               0x214
#define DVBC_OUTPUT_SHIFT_ADDR                    0x128
#define DVBC_DECIMATION_FACTOR_ADDR               0x124
#define DVBC_SLOW_CONTROL_TC_ADDR                 0x3BC
#define DVBC_CARRIER_LOCK_ACQUIRE_TIMEOUT_ADDR    0x348
#define DVBC_PL_CARRIER_FREQUENCY_RANGE_ADDR      0x38C
#define DVBC_PL_CARRIER_STEP_FREQUENCY_ADDR       0x388
#define DVBC_COARSE_FREQUENCY_OFFSET_ADDR         0x118
#define DVBC_SEARCH_STEP_ADDR                     0x3B0
#define DVBC_SEARCH_RANGE_ADDR                    0x3B4
#define DVBC_BITSYNC_DETECT_TIMEOUT_ADDR          0x364
#define DVBC_AUTO_EQU_SEARCH_ADDR                 0x3CC
/****DVB-C API Functions*************************************************/
void   ATBMSetDVBCMode(void);// this function may be changed later
double ATBMDVBCSNR(void);
double ATBMDVBCBER(int *i32pBerExponent);
double ATBMDVBCUncorrectablePER(int *i32pPktsExponent);
uint8  ATBMDVBCGetQAM(void);
int    ATBMDVBCSignalStrength(void);
double ATBMDVBCGetSymbolRate(void);
double ATBMDVBCCarrierOffset(void);

/*************DVB-C internal functions************************/
void   ATBMDVBCInit( custom_config_t stCustomConfig);
void   ATBMDVBCSetSymbolRate(double dbOSCFreq, double dbSymbolRateM);
void   ATBMDVBCSetCarrier(double dbOSCFreq,double dbSymbolRateM);
void   ATBMDVBCSetQAM(void);

/******************Demodulator Internal functions***********************/
void   ATBMSetConfigParas(custom_config_t stCustomConfigp);
void   ATBMInit(void);
void   ATBMConfig( custom_config_t stCustomConfig);
void   ATBMSetTSMode( MPEG_TS_mode_t stTSMode);   /*Default SPI , it can be configured to Serial mode*/
int    ATBMSetOSC( tuner_config_t stTunerConfig, double dbSampleClkFrequency);
uint8  ATBMGetTPS(void);
void   ATBMDebugRegister(void);
/****DTMB I2C interface functions****************************************/
void   ATBMWriteRegArray(uint8 *ui8ARegTable, int i32TableLen);
void   ATBMDebugRegArray(uint8 *ui8ARegTable, int i32TableLen);
ATBM_I2CREADWRITE_STATUS  ATBMRead(uint8 ui8BaseAddr, uint8 ui8RegisterAddr,uint8 *ui8pValue);
ATBM_I2CREADWRITE_STATUS  ATBMWrite(uint8 ui8BaseAddr, uint8 ui8RegisterAddr, uint8 ui8Data);
/****DVB-C I2C interface functions***************************************/
ATBM_I2CREADWRITE_STATUS  ATBMTransRead(uint8 ui8BaseAddr, uint8 ui8RegisterAddr,uint8 *ui8pValue);
ATBM_I2CREADWRITE_STATUS  ATBMTransWrite(uint8 ui8BaseAddr, uint8 ui8RegisterAddr, uint8 ui8Data);
ATBM_I2CREADWRITE_STATUS  ATBMDVBCWrite(uint32 ui32AAddress,uint32 ui32Data);
ATBM_I2CREADWRITE_STATUS  ATBMDVBCRead(uint32 ui32AAddress,uint32 *ui32pValue);

/****General interface functions*****************************************/
double ATBMPreBCHBlockErrorRatio(void);
void   ATBM_GPO_I2CINT_Output(uint8 ui8Level);
void   ATBM_GPO_PWM1_Output(uint8 ui8Level);
void   ATBM_GPO_TestIO23_Output(uint8 ui8Level);
void   ATBM_TestIO23_Indicate_TS_Lock(void);
void   ATBM_TestIO23_Indicate_FEC_No_Error(void);
void   ATBM_GPO_TestIO20_Output(uint8 ui8Level);
void   ATBM_TestIO20_Indicate_FEC_Error(void);
void   ATBM_TestIO20_Indicate_TS_Unlock(void);
void   ATBMErrorOnDurationMillisecond(int i32MS);
void   ATBMLockOffDurationMillisecond(int i32MS);


//API of Getting DTMB signal parameters
DTMB_GUARD_INTERVAL   ATBM_GetGuradInterval(void);
DTMB_QAM_INDEX        ATBM_GetQamIndex(void);
DTMB_CODE_RATE        ATBM_GetCodeRate(void);
DTMB_TIME_INTERLEAVE  ATBM_GetInterleavingMode(void);
DTMB_CARRIER_MODE     ATBM_GetCarrierMode(void);
void                  ATBMGetSignalParameters(DTMB_SIGNAL_PARAMS *singal_params);


/****extern interface functions******************************************/
extern void Delayms (int i32MS);
extern void DemodHardwareReset(void);
extern ATBM_I2CREADWRITE_STATUS  I2CWrite(uint8 ui8I2CSlaveAddr, uint8 *ui8pData, int i32Length);
extern ATBM_I2CREADWRITE_STATUS  I2CRead(uint8 I2CSlaveAddr, uint16 addr_length, uint8 *addr_dat,  uint16 data_length, uint8 *reg_dat);




#define DVBCWriteValue(BaseAddr,RegAddr,WriteValue) {\
   ATBM_I2CREADWRITE_STATUS enumStatus;\
   enumStatus =ATBMTransWrite(BaseAddr,RegAddr,WriteValue);\
   if(ATBM_I2CREADWRITE_OK != enumStatus)\
   {\
       return enumStatus;\
   }\
}

#define DVBCReadValue(BaseAddr,RegAddr,ReadValue) {\
    ATBM_I2CREADWRITE_STATUS enumStatus;\
    enumStatus =ATBMTransRead(BaseAddr,RegAddr,ReadValue);\
    if(ATBM_I2CREADWRITE_OK != enumStatus)\
{\
    return enumStatus;\
}\
}



#endif
