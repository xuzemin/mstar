#ifndef RAFAEL_840_842_H
#define RAFAEL_840_842_H
#define ENABLE_SMC_TUNER_IF_5M    1


#define UINT8  unsigned char
#define UINT16 unsigned short
#define UINT32 unsigned long
#define INT8   signed char
#define INT16  signed short
#define INT32  signed int
#define TRUE   1
#define FALSE 0


#ifdef RAFAEL_840_842_C
#define R840_842_INTERFACE
#else
#define R840_842_INTERFACE extern
#endif

#ifdef VIF_TUNER_TYPE
#undef VIF_TUNER_TYPE
#endif
#ifdef VIF_CR_RATE_B
#undef VIF_CR_RATE_B
#endif
#ifdef VIF_CR_INVERT_B
#undef VIF_CR_INVERT_B
#endif
#ifdef VIF_CR_RATE_GH
#undef VIF_CR_RATE_GH
#endif
#ifdef VIF_CR_INVERT_GH
#undef VIF_CR_INVERT_GH
#endif
#ifdef VIF_CR_RATE_DK
#undef VIF_CR_RATE_DK
#endif
#ifdef VIF_CR_INVERT_DK
#undef VIF_CR_INVERT_DK
#endif
#ifdef VIF_CR_RATE_I
#undef VIF_CR_RATE_I
#endif
#ifdef VIF_CR_INVERT_I
#undef VIF_CR_INVERT_I
#endif
#ifdef VIF_CR_RATE_L
#undef VIF_CR_RATE_L
#endif
#ifdef VIF_CR_INVERT_L
#undef VIF_CR_INVERT_L
#endif
#ifdef VIF_CR_RATE_LL
#undef VIF_CR_RATE_LL
#endif
#ifdef VIF_CR_INVERT_LL
#undef VIF_CR_INVERT_LL
#endif
#ifdef VIF_CR_RATE_MN
#undef VIF_CR_RATE_MN
#endif
#ifdef VIF_CR_INVERT_MN
#undef VIF_CR_INVERT_MN
#endif

#ifdef  D_DMD_IF_DVBT_8M
#undef D_DMD_IF_DVBT_8M
#endif
#ifdef  D_DMD_IF_DVBT_7M
#undef D_DMD_IF_DVBT_7M
#endif
#ifdef  D_DMD_IF_DVBT_6M
#undef D_DMD_IF_DVBT_6M
#endif
#ifdef  D_DMD_IF_DVBC_8M
#undef D_DMD_IF_DVBC_8M
#endif
#ifdef  D_DMD_IF_DVBC_7M
#undef D_DMD_IF_DVBC_7M
#endif
#ifdef  D_DMD_IF_DVBC_6M
#undef D_DMD_IF_DVBC_6M
#endif
#ifdef  D_DMD_IF_DVBT2_8M
#undef D_DMD_IF_DVBT2_8M
#endif
#ifdef  D_DMD_IF_DVBT2_7M
#undef D_DMD_IF_DVBT2_7M
#endif
#ifdef  D_DMD_IF_DVBT2_6M
#undef D_DMD_IF_DVBT2_6M
#endif
#ifdef  D_DMD_TUNER_IQSWAP
#undef D_DMD_TUNER_IQSWAP
#endif

// R840.c
// Digital IF
#define QAM_6M     5000L
#define QAM_8M     5000L
#define ATSC_6M    5000L
#define ISDBT_6M   5000L
#define DVBT_1p7M  5000L
#define DVBT_6M    5000L 
#define DVBT_7M    5000L
#define DVBT_8M    5000L
#define DVBT_10M   5000L
#define DTMB_8M    5000L

// Analog picture carrier
#define ATV_VC_MN  6750L
#define ATV_VC_B   7250L
#define ATV_VC_GH  7750L
#define ATV_VC_I   7750L
#define ATV_VC_DK  7750L
#define ATV_VC_L   7750L
#define ATV_VC_LL  2250L


// [21:0], CR_RATE for Video_Carrier_BBB KHz, HEX((Video_Carrier_BBB/43200.0) * (2^22))
#define VIF_TUNER_TYPE                  1                   // 0: RF Tuner; 1: Silicon Tuner
#define VIF_CR_RATE_B                   (MS_U32)(ATV_VC_B*4194304.0/43200.0+0.5)
#define VIF_CR_INVERT_B                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_GH                  (MS_U32)(ATV_VC_GH*4194304.0/43200.0+0.5)
#define VIF_CR_INVERT_GH                0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_DK                  (MS_U32)(ATV_VC_DK*4194304.0/43200.0+0.5)
#define VIF_CR_INVERT_DK                0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_I                   (MS_U32)(ATV_VC_I*4194304.0/43200.0+0.5)
#define VIF_CR_INVERT_I                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_L                   (MS_U32)(ATV_VC_L*4194304.0/43200.0+0.5)
#define VIF_CR_INVERT_L                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_LL                  (MS_U32)(ATV_VC_LL*4194304.0/43200.0+0.5)
#define VIF_CR_INVERT_LL                1                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_MN                  (MS_U32)(ATV_VC_MN*4194304.0/43200.0+0.5)
#define VIF_CR_INVERT_MN                0                   // Video carrier position; 0: high side; 1:low side


#define D_DMD_IF_DVBT_8M  DVBT_8M
#define D_DMD_IF_DVBT_7M  DVBT_7M
#define D_DMD_IF_DVBT_6M  DVBT_6M
#define D_DMD_IF_DVBC_8M  QAM_8M
#define D_DMD_IF_DVBC_7M  QAM_8M
#define D_DMD_IF_DVBC_6M  QAM_8M
#define D_DMD_IF_DVBT2_8M  DVBT_8M
#define D_DMD_IF_DVBT2_7M  DVBT_7M
#define D_DMD_IF_DVBT2_6M  DVBT_6M
#define D_DMD_TUNER_IQSWAP 1

/// the tuner mode
typedef enum
{
    /// DTV, DVBT
    E_TUNER_DTV_DVB_T_MODE = 0x00,
    /// DTV, DVBC
    E_TUNER_DTV_DVB_C_MODE ,
    /// DTV, DVBS
    E_TUNER_DTV_DVB_S_MODE ,
    /// DTV, DTMB
    E_TUNER_DTV_DTMB_MODE ,
    /// DTV, ATSC
    E_TUNER_DTV_ATSC_MODE ,
    /// ATV, PAL
    E_TUNER_ATV_PAL_MODE ,
    /// ATV, SECAM-L'
    E_TUNER_ATV_SECAM_L_PRIME_MODE ,
    /// ATV, NTSC
    E_TUNER_ATV_NTSC_MODE ,
    /// DTV, ISDB
    E_TUNER_DTV_ISDB_MODE ,
    /// DTV, DVBT2
    E_TUNER_DTV_DVB_T2_MODE,
    /// ATV, SECAM-L
    E_TUNER_ATV_SECAM_L_MODE ,
    /// ATV, SECAM-L
    E_TUNER_DTV_QAM_US_MODE ,
    /// invalid
    E_TUNER_INVALID
} EN_TUNER_MODE;

/// Audio SIF Standard Type
typedef enum
{
    ///< Audio standard BG
    E_AUDIOSTANDARD_BG_                     = 0x00,
    ///< Audio standard BG A2
    E_AUDIOSTANDARD_BG_A2_                  = 0x01,
    ///< Audio standard BG NICAM
    E_AUDIOSTANDARD_BG_NICAM_               = 0x02,
    ///< Audio standard I
    E_AUDIOSTANDARD_I_                      = 0x03,
    ///< Audio standard DK
    E_AUDIOSTANDARD_DK_                     = 0x04,
    ///< Audio standard DK1 A2
    E_AUDIOSTANDARD_DK1_A2_                 = 0x05,
    ///< Audio standard DK2 A2
    E_AUDIOSTANDARD_DK2_A2_                 = 0x06,
    ///< Audio standard DK3 A2
    E_AUDIOSTANDARD_DK3_A2_                 = 0x07,
    ///< Audio standard DK NICAM
    E_AUDIOSTANDARD_DK_NICAM_               = 0x08,
    ///< Audio standard L
    E_AUDIOSTANDARD_L_                      = 0x09,
    ///< Audio standard M
    E_AUDIOSTANDARD_M_                      = 0x0A,
    ///< Audio standard M BTSC
    E_AUDIOSTANDARD_M_BTSC_                 = 0x0B,
    ///< Audio standard M A2
    E_AUDIOSTANDARD_M_A2_                   = 0x0C,
    ///< Audio standard M EIA J
    E_AUDIOSTANDARD_M_EIA_J_                = 0x0D,
    ///< Not Audio standard
    E_AUDIOSTANDARD_NOTSTANDARD_            = 0x0F
} AUDIOSTANDARD_TYPE_;

/*@ <Definitions> @*/




typedef struct _I2C_LEN_TYPE
{
    MS_U8 RegAddr;
    MS_U8 Data[50];
    MS_U8 Len;
}I2C_LEN_TYPE;

typedef struct _I2C_TYPE
{
    MS_U8 RegAddr;
    MS_U8 Data;
}I2C_TYPE;
/*
typedef enum
{
    DEMOD_ATSC_MODE_NTSC,
    DEMOD_ATSC_MODE_256QAM,
    DEMOD_ATSC_MODE_64QAM,
    DEMOD_ATSC_MODE_8VSB,
    DEMOD_ATSC_MODE_NUM
} EN_DEMOD_ATSC_MODE;
*/

//***********No used for Silicon tuner,but for API*******************************
#define VHF_LOWMIN_FREQ                 46250L     // KHz
#define VHF_LOWMAX_FREQ                 142000L    // KHz
#define VHF_HIGHMIN_FREQ                149000L    // KHz
#define VHF_HIGHMAX_FREQ                426000L    // KHz
#define UHF_MIN_FREQ_UK                 470000L    //470000L    // KHz for UK
#define UHF_MIN_FREQ                    434000L    // KHz
#define UHF_MAX_FREQ                    863250L    // KHz
#define TUNER_IF_FREQ_KHz               38900L     // KHz
#define TUNER_L_PRIME_IF_FREQ_KHz       33900L     // KHz
//*********************end*************************************************
// void devTunerInit(void);
// void devTunerSetAtvStandard(IF_FREQ enIF_Freq);
// void devTunerSetPLLData(WORD wPLLData, RFBAND eBand);
R840_842_INTERFACE BOOLEAN devTunerInit(void);
R840_842_INTERFACE void devDigitalTuner_Init(void);
R840_842_INTERFACE void devTunerSetFreq(U32 u32Freq);
R840_842_INTERFACE void devDigitalTuner_SetFreq( double Freq,  RF_CHANNEL_BANDWIDTH eBandWidth);
R840_842_INTERFACE BOOLEAN devTuner_Std_set(EN_TUNER_MODE eMode, AUDIOSTANDARD_TYPE_ OtherMode);
R840_842_INTERFACE BOOLEAN mdev_GetSignalStrength(float* f_strength);
#undef R840_842_INTERFACE

#endif /*R_840_H*/
