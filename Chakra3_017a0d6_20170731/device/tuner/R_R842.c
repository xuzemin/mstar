//*****************************************************************************
// File:    device_tuner_R842.cpp
// Owner:   Smart-core
// Author:  Steven wang
// Date:    2013-07-08
//*****************************************************************************


/*@ <Include> @*/

#include "datatype.h"
#include "drvIIC.h"
#include "msAPI_Timer.h"
#include "debug.h"
#include "Utl.h"
#include "MApp_GlobalSettingSt_Common.h"

#include "R842/R842.c"
#include "R842/R842.h"


#define DBG_TUNER(x)  //x

// ------------------------------------------------------------
// Other Define
// ------------------------------------------------------------
#define DIVIDER_RATIO_50KHz         0x05
#define DIVIDER_RATIO_31_25KHz      0x04
#define DIVIDER_RATIO_62_5KHz       0x03
#define DIVIDER_RATIO_125KHz        0x02
#define DIVIDER_RATIO_142_85KHz     0x01
#define DIVIDER_RATIO_166_7KHz      0x00

// #define TN_FREQ_STEP                E_FREQ_STEP_62_5KHz
#define DIVIDER_RATIO               DIVIDER_RATIO_50KHz

#define _TUNER_I2C_ID               0xF6
#define MIN_FREQ_SUPPORT_KHz        40000
#define MAX_FREQ_SUPPORT_KHz        880000

#define TUNER_DTV_IQ_SWAP           1// iq swap
#define TUNER_VHF_LOWMIN_FREQ       46250L
#define TUNER_VHF_LOWMAX_FREQ       142000L
#define TUNER_VHF_HIGHMIN_FREQ      149000L
#define TUNER_VHF_HIGHMAX_FREQ      426000L
#define TUNER_UHF_MIN_FREQ_UK       470000L
#define TUNER_UHF_MIN_FREQ          434000L
#define TUNER_UHF_MAX_FREQ          863250L

#define DIVIDER_166K                0
#define DIVIDER_142K                1
#define DIVIDER_80K                 2
#define DIVIDER_62K                 3
#define DIVIDER_31K                 4
#define DIVIDER_50K                 5

#define TN_FREQ_SS_INVERSE_625      16      // 1/0.0625
#define TN_RSA_RSB_625              0x06
#define TN_RSA_RSB_50               0x05
#define TN_FREQ_SS_625              62.5    // kHz
#define TN_FREQ_SS_50               50      // kHz
#define TN_FREQ_SS_INVERSE_50       20      // 1/0.05
#define TN_FREQ_SS                  TN_FREQ_SS_625

#define TN_LOW_BAND                 0x01
#define TN_MID_BAND                 0x02
#define TN_HIGH_BAND                0x04

#define IF_OUT_LEVEL_114            0
#define IF_OUT_LEVEL_112            (1<<3)
#define IF_OUT_LEVEL_110            (2<<3)
#define IF_OUT_LEVEL_108            (3<<3)
#define IF_OUT_LEVEL_106            (4<<3)
#define IF_OUT_LEVEL_104            (5<<3)
#define IF_OUT_LEVEL_105            (6<<3)
#define IF_OUT_LEVEL_Disable        (7<<3)

#define DIGITAL_IF_AGC_ON           0x00
#define DIGITAL_IF_AGC_OFF          0x08

#define CHARGE_PUMP_1               (1<<6)
#define CHARGE_PUMP_2               (2<<6)

#define CHARGE_PUMP_3               (1<<1)

#define ANALOG_IF_OUT               0x04
#define DIGITAL_IF_OUT              0x00

#define FAST_LOCK                   0x20

#define BAND_SWITCH_UHF             0x04
#define BAND_SWITCH_VHF_HIGH        0x02
#define BAND_SWITCH_VHF_LOW         0x01

#define TUNER_HIBYTE(w)             ((U8) (((U16) (w) >> 8) & 0xFF))
#define TUNER_LOBYTE(w)             ((U8) (w & 0xFF))

#define R842_ADDRESSADDR (((UINT16)TUNER_IIC_BUS<<8)|_TUNER_I2C_ID )

#define DTMB_SYSTEM_ENABLE 0

// VideoIF = 6.8M
const U16 VIF_A1_A2_SOS11_SOS12_B_Stereo_A2[16]=
{
 0x03C6,0x0628,0x0412,
 0x03CB,0x0628,0x040C,
 0x015E,0x0628,0x0200,0x0694,0x0200,
 0x03C6,0x0628,0x0200,0x0412,0x0200
};

// VideoIF = 6.8M
const U16 VIF_A1_A2_SOS11_SOS12_B_Mono_NICAM[16]=
{
 0x03C6,0x0628,0x0412,
 0x03CE,0x0628,0x040A,
 0x015E,0x0628,0x0200,0x0694,0x0200,
 0x03C6,0x0628,0x0200,0x0412,0x0200
};

// VideoIF = 7.75M
const U16 VIF_A1_A2_SOS11_SOS12_GH_Stereo_A2[16]=
{
 0x038F,0x063C,0x0436,
 0x039A,0x063C,0x042B,
 0x004D,0x063C,0x0200,0x07AE,0x0200,
 0x038F,0x063C,0x0200,0x0436,0x0200
};

// VideoIF = 7.75M
const U16 VIF_A1_A2_SOS11_SOS12_GH_Mono_NICAM[16]=
{
 0x038F,0x063C,0x0436,
 0x039E,0x063C,0x0427,
 0x004D,0x063C,0x0200,0x07AE,0x0200,
 0x038F,0x063C,0x0200,0x0436,0x0200
};

// VideoIF = 7.75M
const U16 VIF_A1_A2_SOS11_SOS12_DK1_Stereo_A2[16]=
{
 0x03B3,0x063C,0x0411,
 0x03AC,0x063C,0x0418,
 0x00D7,0x063C,0x0200,0x071B,0x0200,
 0x03B3,0x063C,0x0200,0x0411,0x0200
};

// VideoIF = 7.75M
const U16 VIF_A1_A2_SOS11_SOS12_DK2_Stereo_A2[16]=
{
 0x03B3,0x063C,0x0411,
 0x03B3,0x063C,0x040B,
 0x00D7,0x063C,0x0200,0x071B,0x0200,
 0x03B3,0x063C,0x0200,0x0411,0x0200
};

// VideoIF = 7.75M
const U16 VIF_A1_A2_SOS11_SOS12_DK3_Stereo_A2[16]=
{
 0x03B3,0x063C,0x0411,
 0x039A,0x063C,0x042B,
 0x00D7,0x063C,0x0200,0x071B,0x0200,
 0x03B3,0x063C,0x0200,0x0411,0x0200
};

// VideoIF = 7.75M
const U16 VIF_A1_A2_SOS11_SOS12_DK_Mono_NICAM[16]=
{
 0x03B3,0x063C,0x0411,
 0x039E,0x063C,0x0427,
 0x00D7,0x063C,0x0200,0x071B,0x0200,
 0x03B3,0x063C,0x0200,0x0411,0x0200
};

// VideoIF = 7.75M
const U16 VIF_A1_A2_SOS11_SOS12_I[16]=
{
 0x03A4,0x063C,0x0421,
 0x03B4,0x063C,0x0410,
 0x0092,0x063C,0x0200,0x0764,0x0200,
 0x03A4,0x063C,0x0200,0x0421,0x0200
};

// VideoIF = 5.8M
const U16 VIF_A1_A2_SOS11_SOS12_MN[16]=
{
 0x03C6,0x0628,0x0412,
 0x03CB,0x0628,0x040D,
 0x01DF,0x0628,0x0200,0x060D,0x0200,
 0x03C6,0x0628,0x0200,0x0412,0x0200
};

// VideoIF = 7.75M
const U16 VIF_A1_A2_SOS11_SOS12_L[16]=
{
 0x03B3,0x063C,0x0411,
 0x039E,0x063C,0x0427,
 0x00D7,0x063C,0x0200,0x071B,0x0200,
 0x03B3,0x063C,0x0200,0x0411,0x0200
};

// VideoIF = 2.25M
const U16 VIF_A1_A2_SOS11_SOS12_LP[16]=
{
 0x011B,0x063C,0x06D3,
 0x0170,0x063C,0x0678,
 0x03BD,0x063C,0x0200,0x0406,0x0200,
 0x011B,0x063C,0x0200,0x06D3,0x0200
};


/*@ </Definitions> @*/


static U8 bInit_Rafael = 0;
U32 sg_u32_rf_freq = 0;
R842_Standard_Type sg_cur_std = R842_STD_SIZE;

static EN_TUNER_MODE m_eMode = E_TUNER_DTV_DVB_T_MODE;//E_TUNER_INVALID;
static AUDIOSTANDARD_TYPE_ m_OtherMode = E_AUDIOSTANDARD_NOTSTANDARD_;

extern IF_FREQ MDrv_IFDM_GetIF(void);

//*--------------------------------------------------------------------------------------
//* Prototype of function to be provided by customer
//*--------------------------------------------------------------------------------------
BOOL   UserWrittenI2CRead(U32 AddrSize, U8* pAddr,U32 ReadLen, U8* pData);
BOOL   UserWrittenI2CWrite (U32 AddrSize, U8* pAddr,U32 WriteLen, U8* pData);

//*--------------------------------------------------------------------------------------
//* Function Name       :   UserWrittenI2CRead
//* Object              :
//* Input Parameters    :   U32 AddrSize,
//*                         U8* pAddr,
//*                         U32 ReadLen,
//*                         U8* pData
//* Output Parameters   :   BOOL.
//*--------------------------------------------------------------------------------------
BOOL UserWrittenI2CRead(U32 AddrSize, U8* pAddr,
                                U32 ReadLen, U8* pData)
{
    if (MDrv_IIC_ReadBytes(R842_ADDRESSADDR, (MS_U8)AddrSize, pAddr, (MS_U16)ReadLen, pData)==FALSE)
    {
        printf("\nR842 Tuner_IIC read fail\n");
        return FALSE;
    }
    return TRUE;
}

//*--------------------------------------------------------------------------------------
//* Function Name       : UserWrittenI2CWrite
//* Object              :
//* Input Parameters    :   U32 AddrSize,
//*                         U8* pAddr,
//*                         U32 WriteLen,
//*                         U8* pData
//* Output Parameters   :   BOOL.
//*--------------------------------------------------------------------------------------
BOOL UserWrittenI2CWrite (U32 AddrSize, U8* pAddr,
                                    U32 WriteLen, U8* pData)
{
    if(MDrv_IIC_WriteBytes(R842_ADDRESSADDR, (MS_U8)AddrSize, pAddr, (MS_U16)WriteLen, pData)==FALSE)
    {
        printf("\nR842 Tuner_IIC write fail\n");
        return FALSE;
    }
    return TRUE;
}


BOOL ATV_SetTune( U32 u32FreqKHz,RFBAND eBand, EN_TUNER_MODE eMode,U8 u8OtherMode )
{
    R842_Set_Info stR842_Info;
    R842_Standard_Type StandardMode;

    UNUSED(eBand);

    if(!bInit_Rafael) //double check lock
    {
        if(!bInit_Rafael)
        {
            if (R842_Init()==R842_Fail)
            {
                printf("R842 init fail....\n");
            }
            else
            {
                bInit_Rafael = 1;
            }
        }
    }

    if(eMode == E_TUNER_ATV_SECAM_L_PRIME_MODE)
    {
        StandardMode = R842_SECAM_L1_CIF_5M;
    }
    else if(eMode == E_TUNER_ATV_NTSC_MODE)
    {
    #if DTMB_SYSTEM_ENABLE
        StandardMode = R842_MN_5800;
    #else
        StandardMode = R842_MN_5800;
    #endif
    }
    else
    {
        //printf("OtherMode[%d]\r\n",u8OtherMode);
        if(u8OtherMode == 0xff)
        {
        #if DTMB_SYSTEM_ENABLE
            StandardMode = R842_PAL_DK_CIF_5M;
        #else
            StandardMode = R842_PAL_DK_CIF_5M;
        #endif
        }
        else
        {
            switch((AUDIOSTANDARD_TYPE_)u8OtherMode)
            {
                case E_AUDIOSTANDARD_BG_:
                case E_AUDIOSTANDARD_BG_A2_:
                case E_AUDIOSTANDARD_BG_NICAM_:
                #if DTMB_SYSTEM_ENABLE
                    StandardMode = R842_PAL_BGH_8M_CIF_5M;
                #else
                    StandardMode = R842_PAL_BGH_8M_CIF_5M;
                #endif
                break;

                case E_AUDIOSTANDARD_I_:
                #if DTMB_SYSTEM_ENABLE
                    StandardMode = R842_PAL_I_CIF_5M;
                #else
                    StandardMode = R842_PAL_I_CIF_5M;
                #endif
                break;

                case E_AUDIOSTANDARD_DK_:
                case E_AUDIOSTANDARD_DK1_A2_:
                case E_AUDIOSTANDARD_DK2_A2_:
                case E_AUDIOSTANDARD_DK3_A2_:
                case E_AUDIOSTANDARD_DK_NICAM_:
                #if DTMB_SYSTEM_ENABLE
                    StandardMode = R842_PAL_DK_CIF_5M;
                #else
                    StandardMode = R842_PAL_DK_CIF_5M;
                #endif
                break;

                case E_AUDIOSTANDARD_L_:
                #if DTMB_SYSTEM_ENABLE
                    StandardMode = R842_SECAM_L_CIF_5M;
                #else
                    StandardMode = R842_SECAM_L_CIF_5M;
                #endif
                break;

                case E_AUDIOSTANDARD_M_:
                case E_AUDIOSTANDARD_M_BTSC_:
                case E_AUDIOSTANDARD_M_A2_:
                case E_AUDIOSTANDARD_M_EIA_J_:
                #if DTMB_SYSTEM_ENABLE
                    StandardMode = R842_MN_5800;
                #else
                    StandardMode = R842_MN_5800;
                #endif
                break;

                default:
                #if DTMB_SYSTEM_ENABLE
                    StandardMode = R842_PAL_DK_CIF_5M;
                #else
                    StandardMode = R842_PAL_DK_CIF_5M;
                #endif
                break;
            }
        }

    }

    memset(&stR842_Info, 0, sizeof(stR842_Info));
    stR842_Info.R842_Standard =StandardMode;
    stR842_Info.RF_KHz = u32FreqKHz;

    R842_SetPllData(stR842_Info);

    sg_u32_rf_freq = stR842_Info.RF_KHz;
    sg_cur_std = stR842_Info.R842_Standard;

    return TRUE;
}

BOOL DTV_SetTune(double Freq, RF_CHANNEL_BANDWIDTH eBandWidth, EN_TUNER_MODE eMode)
{
    R842_Set_Info stR842_Info;
    R842_Standard_Type StandardMode;


    if(!bInit_Rafael) //double check lock
    {
        if(!bInit_Rafael)
        {
            if (R842_Init()==R842_Fail)
            {
                printf("R842 init fail....\n");
            }
            else
            {
                bInit_Rafael = 1;
            }
        }
    }

    switch(eMode)
    {
        case E_TUNER_DTV_ATSC_MODE:
            StandardMode = R842_ATSC_IF_5M;
        break;
        case E_TUNER_DTV_DTMB_MODE:
            StandardMode = R842_DTMB_8M_IF_5M;
        break;
        case E_TUNER_DTV_DVB_C_MODE:
            if(eBandWidth == E_RF_CH_BAND_6MHz)
            {
                StandardMode = R842_DVB_C_6M_IF_5M;
            }
            else
            {
                StandardMode = R842_DVB_C_8M_IF_5M;
            }
        break;
        case E_TUNER_DTV_DVB_T_MODE:
            if(eBandWidth == E_RF_CH_BAND_6MHz)
            {
                StandardMode = R842_DVB_T_6M_IF_5M;
            }
            else if(eBandWidth == E_RF_CH_BAND_7MHz)
            {
                StandardMode = R842_DVB_T_7M_IF_5M;
            }
            else
            {
                StandardMode = R842_DVB_T_8M_IF_5M;
            }
        break;
        case E_TUNER_DTV_DVB_T2_MODE:
            if(eBandWidth == E_RF_CH_BAND_6MHz)
            {
                StandardMode = R842_DVB_T2_6M_IF_5M;
            }
            else if(eBandWidth == E_RF_CH_BAND_7MHz)
            {
                StandardMode = R842_DVB_T2_7M_IF_5M;
            }
            else
            {
                StandardMode = R842_DVB_T2_8M_IF_5M;
            }
        break;
        case E_TUNER_DTV_ISDB_MODE:
            StandardMode = R842_ISDB_T_IF_5M;
        break;

        default:
            StandardMode = R842_DTMB_8M_IF_5M;
            // TODO: error happened
        break;
    }

    memset(&stR842_Info, 0, sizeof(stR842_Info));
    stR842_Info.R842_Standard = StandardMode;
    stR842_Info.R842_IfAgc_Select = R842_IF_AGC1;   // Select IF AGC1
    if(eMode == E_TUNER_DTV_ATSC_MODE)
        stR842_Info.RF_KHz = Freq;
    else
        stR842_Info.RF_KHz = Freq * 1000L;
    R842_SetPllData(stR842_Info);
    sg_u32_rf_freq = stR842_Info.RF_KHz;
    sg_cur_std = stR842_Info.R842_Standard;

    return TRUE;
}

#if 0
BOOL ExtendCommand(U8 u8SubCmd, U32 u32Param1, U32 u32Param2, void* pvoidParam3)
{
    switch(u8SubCmd)
    {
        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_FREQ_STEP:
            {
                EN_FREQ_STEP *eFreqStep = (EN_FREQ_STEP*)pvoidParam3;
                *eFreqStep = TN_FREQ_STEP;
            }
        break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_IF_FREQ:
            {
                U16 *u16IFFreq = (U16 *)pvoidParam3;
                *u16IFFreq = TUNER_IF_FREQ_KHz;
            }
        break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_L_PRIME_IF_FREQ:
            {
                U16 *u16IFFreq = (U16 *)pvoidParam3;
                *u16IFFreq = TUNER_L_PRIME_IF_FREQ_KHz;
            }
        break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_VHF_LOWMIN_FREQ:
            {
                U32 *u32Freq = (U32 *)pvoidParam3;
                *u32Freq = TUNER_VHF_LOWMIN_FREQ;
            }
        break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_VHF_LOWMAX_FREQ:
            {
                U32 *u32Freq = (U32 *)pvoidParam3;
                *u32Freq = TUNER_VHF_LOWMAX_FREQ;
            }
        break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_VHF_HIGHMIN_FREQ:
            {
                U32 *u32Freq = (U32 *)pvoidParam3;
                *u32Freq = TUNER_VHF_HIGHMIN_FREQ;
            }
        break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_VHF_HIGHMAX_FREQ:
            {
                U32 *u32Freq = (U32 *)pvoidParam3;
                *u32Freq = TUNER_VHF_HIGHMAX_FREQ;
            }
        break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_UHF_MIN_FREQ:
            {
                U32 *u32Freq = (U32 *)pvoidParam3;
                *u32Freq = TUNER_UHF_MIN_FREQ;
            }
        break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_UHF_MAX_FREQ:
            {
                U32 *u32Freq = (U32 *)pvoidParam3;
                *u32Freq = TUNER_UHF_MAX_FREQ;
            }
        break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_VIF_TUNER_TYPE:
        {
            U8 *u8VifTunerType = (U8 *)pvoidParam3;
            *u8VifTunerType = VIF_TUNER_TYPE;
        }
        break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_VIF_PARA:
        {
            mapi_vif_datatype::stVIFInitialIn *p_stVIFInitialIn = (mapi_vif_datatype::stVIFInitialIn *)pvoidParam3;

            p_stVIFInitialIn->VifCrRate_B = VIF_CR_RATE_B;
            p_stVIFInitialIn->VifCrInvert_B = VIF_CR_INVERT_B;
            p_stVIFInitialIn->VifCrRate_GH = VIF_CR_RATE_GH;
            p_stVIFInitialIn->VifCrInvert_GH = VIF_CR_INVERT_GH;
            p_stVIFInitialIn->VifCrRate_DK = VIF_CR_RATE_DK;
            p_stVIFInitialIn->VifCrInvert_DK = VIF_CR_INVERT_DK;
            p_stVIFInitialIn->VifCrRate_I = VIF_CR_RATE_I;
            p_stVIFInitialIn->VifCrInvert_I = VIF_CR_INVERT_I;
            p_stVIFInitialIn->VifCrRate_L = VIF_CR_RATE_L;
            p_stVIFInitialIn->VifCrInvert_L = VIF_CR_INVERT_L;
            p_stVIFInitialIn->VifCrRate_LL = VIF_CR_RATE_LL;
            p_stVIFInitialIn->VifCrInvert_LL = VIF_CR_INVERT_LL;
            p_stVIFInitialIn->VifCrRate_MN = VIF_CR_RATE_MN;
            p_stVIFInitialIn->VifCrInvert_MN = VIF_CR_INVERT_MN;
        }
            break;
        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_VIF_NOTCH_SOSFILTER:
        {
            U16 *pu16_vif_notch_coef = NULL;
            U16 *pu16_list = (U16*)pvoidParam3;
            U8 indx = 0;

            switch((mapi_vif_datatype::EN_VIF_SOUND_SYSTEM)u32Param1)
            {
                case mapi_vif_datatype::E_VIF_SOUND_B_STEREO_A2:
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_B_Stereo_A2;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_B_MONO_NICAM:
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_B_Mono_NICAM;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_GH_STEREO_A2:
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_GH_Stereo_A2;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_GH_MONO_NICAM:
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_GH_Mono_NICAM;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_I:
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_I;
                    break;
                case mapi_vif_datatype::E_VIF_SOUND_DK1_STEREO_A2:
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_DK1_Stereo_A2;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_DK2_STEREO_A2:
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_DK2_Stereo_A2;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_DK3_STEREO_A2:
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_DK3_Stereo_A2;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_DK_MONO_NICAM:
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_DK_Mono_NICAM;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_L:
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_L;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_LL:
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_LP;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_MN:
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_MN;
                    break;
                default:
                    printf("Error:%s(),%d\n",__func__,__LINE__);
                    return FALSE;
                    break;
            }

            if (pu16_vif_notch_coef == NULL) return FALSE;

            for (indx = 0;indx < 16;indx++)
            {
                *(pu16_list+indx) = *(pu16_vif_notch_coef+indx);
            }

        }
            break;


        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_DTV_IF_FREQ:
        {
            switch (u32Param1) // demod mode
            {
                case E_TUNER_DTV_DVB_T_MODE:
                case E_TUNER_DTV_DVB_T2_MODE:
                case E_TUNER_DTV_DTMB_MODE:
                    *((U32 *)pvoidParam3)=5000L;
                break;
                case E_TUNER_DTV_DVB_C_MODE:
                    *((U32 *)pvoidParam3)=5000L;
                break;
                case E_TUNER_DTV_ATSC_MODE:
                    *((U32 *)pvoidParam3)=5000L;
                break;
                case E_TUNER_DTV_ISDB_MODE:
                    *((U32 *)pvoidParam3)=5000L;
                break;

                default:
                    printf("Error:%s(),%d\n",__func__,__LINE__);
                    return FALSE;
                break;
            }
        }
        break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_IQ_SWAP:
        {
            U8 *u8IqSwap = (U8 *)pvoidParam3;
            *u8IqSwap = TUNER_DTV_IQ_SWAP;
            if ( u32Param1 )
            {
                *u8IqSwap ^= 0x01;
            }
        }
        break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_RF_TABLE:
        {
            (*(DMD_SSI_TABLE **)pvoidParam3)=NULL; // if not used, should return NULL;
            return FALSE;
        }
        break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_RF_LEVEL:
        {
            INT32 s32_rssi_dbm = 0;
            if (R842_GetTotalRssi2(sg_u32_rf_freq, sg_cur_std, &s32_rssi_dbm) == R842_Fail)
            {
                printf("[Error]R842_GetTotalRssi fail\n");
                s32_rssi_dbm = -10;
            }
            *((float *)pvoidParam3)=(float)s32_rssi_dbm/10.0;
        }
        break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_DEMOD_CONFIG:
        {
            switch (u32Param1) // demod mode
            {
                case E_TUNER_DTV_DVB_T_MODE:
                    *((MS_U8 **)pvoidParam3)=NULL;
                break;
                case E_TUNER_DTV_DVB_C_MODE:
                    *((MS_U8 **)pvoidParam3)=NULL;
                break;
                default:
                    printf("Error:%s(),%d\n",__func__,__LINE__);
                    return FALSE;
                break;
            }
        }
        break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_PEAKING_PARAMETER:
        {
            mapi_vif_datatype::stVIFUserFilter *VIF_UserFilter = (mapi_vif_datatype::stVIFUserFilter *)pvoidParam3;
            ASSERT(VIF_UserFilter);
            switch (u32Param1)
            {
                case E_RFBAND_VHF_LOW:
                    if((u32Param2==(U32)mapi_demodulator_datatype::IF_FREQ_B)||(u32Param2==(U32)mapi_demodulator_datatype::IF_FREQ_G))
                    {
                        VIF_UserFilter->VifSos21FilterC0  = VIF_SOS_21_FILTER_C0;
                        VIF_UserFilter->VifSos21FilterC1  = VIF_SOS_21_FILTER_C1;
                        VIF_UserFilter->VifSos21FilterC2  = VIF_SOS_21_FILTER_C2;
                        VIF_UserFilter->VifSos21FilterC3  = VIF_SOS_21_FILTER_C3;
                        VIF_UserFilter->VifSos21FilterC4  = VIF_SOS_21_FILTER_C4;

                        VIF_UserFilter->VifSos22FilterC0  = VIF_SOS_22_FILTER_C0;
                        VIF_UserFilter->VifSos22FilterC1  = VIF_SOS_22_FILTER_C1;
                        VIF_UserFilter->VifSos22FilterC2  = VIF_SOS_22_FILTER_C2;
                        VIF_UserFilter->VifSos22FilterC3  = VIF_SOS_22_FILTER_C3;
                        VIF_UserFilter->VifSos22FilterC4  = VIF_SOS_22_FILTER_C4;

                        VIF_UserFilter->VifSos31FilterC0  = VIF_SOS_31_FILTER_C0;
                        VIF_UserFilter->VifSos31FilterC1  = VIF_SOS_31_FILTER_C1;
                        VIF_UserFilter->VifSos31FilterC2  = VIF_SOS_31_FILTER_C2;
                        VIF_UserFilter->VifSos31FilterC3  = VIF_SOS_31_FILTER_C3;
                        VIF_UserFilter->VifSos31FilterC4  = VIF_SOS_31_FILTER_C4;
                        VIF_UserFilter->VifSos32FilterC0  = VIF_SOS_32_FILTER_C0;
                        VIF_UserFilter->VifSos32FilterC1  = VIF_SOS_32_FILTER_C1;
                        VIF_UserFilter->VifSos32FilterC2  = VIF_SOS_32_FILTER_C2;
                        VIF_UserFilter->VifSos32FilterC3  = VIF_SOS_32_FILTER_C3;
                        VIF_UserFilter->VifSos32FilterC4  = VIF_SOS_32_FILTER_C4;
                    }
                    else if(u32Param2==(U32)mapi_demodulator_datatype::IF_FREQ_DK)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = VIF_SOS_21_FILTER_C0;
                        VIF_UserFilter->VifSos21FilterC1  = VIF_SOS_21_FILTER_C1;
                        VIF_UserFilter->VifSos21FilterC2  = VIF_SOS_21_FILTER_C2;
                        VIF_UserFilter->VifSos21FilterC3  = VIF_SOS_21_FILTER_C3;
                        VIF_UserFilter->VifSos21FilterC4  = VIF_SOS_21_FILTER_C4;

                        VIF_UserFilter->VifSos22FilterC0  = VIF_SOS_22_FILTER_C0;
                        VIF_UserFilter->VifSos22FilterC1  = VIF_SOS_22_FILTER_C1;
                        VIF_UserFilter->VifSos22FilterC2  = VIF_SOS_22_FILTER_C2;
                        VIF_UserFilter->VifSos22FilterC3  = VIF_SOS_22_FILTER_C3;
                        VIF_UserFilter->VifSos22FilterC4  = VIF_SOS_22_FILTER_C4;

                        VIF_UserFilter->VifSos31FilterC0  = VIF_SOS_31_FILTER_C0;
                        VIF_UserFilter->VifSos31FilterC1  = VIF_SOS_31_FILTER_C1;
                        VIF_UserFilter->VifSos31FilterC2  = VIF_SOS_31_FILTER_C2;
                        VIF_UserFilter->VifSos31FilterC3  = VIF_SOS_31_FILTER_C3;
                        VIF_UserFilter->VifSos31FilterC4  = VIF_SOS_31_FILTER_C4;
                        VIF_UserFilter->VifSos32FilterC0  = VIF_SOS_32_FILTER_C0;
                        VIF_UserFilter->VifSos32FilterC1  = VIF_SOS_32_FILTER_C1;
                        VIF_UserFilter->VifSos32FilterC2  = VIF_SOS_32_FILTER_C2;
                        VIF_UserFilter->VifSos32FilterC3  = VIF_SOS_32_FILTER_C3;
                        VIF_UserFilter->VifSos32FilterC4  = VIF_SOS_32_FILTER_C4;
                    }
                    else if(u32Param2==(U32)mapi_demodulator_datatype::IF_FREQ_I)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = VIF_SOS_21_FILTER_C0;
                        VIF_UserFilter->VifSos21FilterC1  = VIF_SOS_21_FILTER_C1;
                        VIF_UserFilter->VifSos21FilterC2  = VIF_SOS_21_FILTER_C2;
                        VIF_UserFilter->VifSos21FilterC3  = VIF_SOS_21_FILTER_C3;
                        VIF_UserFilter->VifSos21FilterC4  = VIF_SOS_21_FILTER_C4;

                        VIF_UserFilter->VifSos22FilterC0  = VIF_SOS_22_FILTER_C0;
                        VIF_UserFilter->VifSos22FilterC1  = VIF_SOS_22_FILTER_C1;
                        VIF_UserFilter->VifSos22FilterC2  = VIF_SOS_22_FILTER_C2;
                        VIF_UserFilter->VifSos22FilterC3  = VIF_SOS_22_FILTER_C3;
                        VIF_UserFilter->VifSos22FilterC4  = VIF_SOS_22_FILTER_C4;

                        VIF_UserFilter->VifSos31FilterC0  = VIF_SOS_31_FILTER_C0;
                        VIF_UserFilter->VifSos31FilterC1  = VIF_SOS_31_FILTER_C1;
                        VIF_UserFilter->VifSos31FilterC2  = VIF_SOS_31_FILTER_C2;
                        VIF_UserFilter->VifSos31FilterC3  = VIF_SOS_31_FILTER_C3;
                        VIF_UserFilter->VifSos31FilterC4  = VIF_SOS_31_FILTER_C4;
                        VIF_UserFilter->VifSos32FilterC0  = VIF_SOS_32_FILTER_C0;
                        VIF_UserFilter->VifSos32FilterC1  = VIF_SOS_32_FILTER_C1;
                        VIF_UserFilter->VifSos32FilterC2  = VIF_SOS_32_FILTER_C2;
                        VIF_UserFilter->VifSos32FilterC3  = VIF_SOS_32_FILTER_C3;
                        VIF_UserFilter->VifSos32FilterC4  = VIF_SOS_32_FILTER_C4;
                    }
                    else if(u32Param2 == (U32)mapi_demodulator_datatype::IF_FREQ_L)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = VIF_SOS_21_FILTER_C0;
                        VIF_UserFilter->VifSos21FilterC1  = VIF_SOS_21_FILTER_C1;
                        VIF_UserFilter->VifSos21FilterC2  = VIF_SOS_21_FILTER_C2;
                        VIF_UserFilter->VifSos21FilterC3  = VIF_SOS_21_FILTER_C3;
                        VIF_UserFilter->VifSos21FilterC4  = VIF_SOS_21_FILTER_C4;

                        VIF_UserFilter->VifSos22FilterC0  = VIF_SOS_22_FILTER_C0;
                        VIF_UserFilter->VifSos22FilterC1  = VIF_SOS_22_FILTER_C1;
                        VIF_UserFilter->VifSos22FilterC2  = VIF_SOS_22_FILTER_C2;
                        VIF_UserFilter->VifSos22FilterC3  = VIF_SOS_22_FILTER_C3;
                        VIF_UserFilter->VifSos22FilterC4  = VIF_SOS_22_FILTER_C4;

                        VIF_UserFilter->VifSos31FilterC0  = VIF_SOS_31_FILTER_C0;
                        VIF_UserFilter->VifSos31FilterC1  = VIF_SOS_31_FILTER_C1;
                        VIF_UserFilter->VifSos31FilterC2  = VIF_SOS_31_FILTER_C2;
                        VIF_UserFilter->VifSos31FilterC3  = VIF_SOS_31_FILTER_C3;
                        VIF_UserFilter->VifSos31FilterC4  = VIF_SOS_31_FILTER_C4;
                        VIF_UserFilter->VifSos32FilterC0  = VIF_SOS_32_FILTER_C0;
                        VIF_UserFilter->VifSos32FilterC1  = VIF_SOS_32_FILTER_C1;
                        VIF_UserFilter->VifSos32FilterC2  = VIF_SOS_32_FILTER_C2;
                        VIF_UserFilter->VifSos32FilterC3  = VIF_SOS_32_FILTER_C3;
                        VIF_UserFilter->VifSos32FilterC4  = VIF_SOS_32_FILTER_C4;
                    }
                    else if(u32Param2 == (U32)mapi_demodulator_datatype::IF_FREQ_L_PRIME)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = VIF_SOS_21_FILTER_C0;
                        VIF_UserFilter->VifSos21FilterC1  = VIF_SOS_21_FILTER_C1;
                        VIF_UserFilter->VifSos21FilterC2  = VIF_SOS_21_FILTER_C2;
                        VIF_UserFilter->VifSos21FilterC3  = VIF_SOS_21_FILTER_C3;
                        VIF_UserFilter->VifSos21FilterC4  = VIF_SOS_21_FILTER_C4;

                        VIF_UserFilter->VifSos22FilterC0  = VIF_SOS_22_FILTER_C0;
                        VIF_UserFilter->VifSos22FilterC1  = VIF_SOS_22_FILTER_C1;
                        VIF_UserFilter->VifSos22FilterC2  = VIF_SOS_22_FILTER_C2;
                        VIF_UserFilter->VifSos22FilterC3  = VIF_SOS_22_FILTER_C3;
                        VIF_UserFilter->VifSos22FilterC4  = VIF_SOS_22_FILTER_C4;

                        VIF_UserFilter->VifSos31FilterC0  = VIF_SOS_31_FILTER_C0;
                        VIF_UserFilter->VifSos31FilterC1  = VIF_SOS_31_FILTER_C1;
                        VIF_UserFilter->VifSos31FilterC2  = VIF_SOS_31_FILTER_C2;
                        VIF_UserFilter->VifSos31FilterC3  = VIF_SOS_31_FILTER_C3;
                        VIF_UserFilter->VifSos31FilterC4  = VIF_SOS_31_FILTER_C4;
                        VIF_UserFilter->VifSos32FilterC0  = VIF_SOS_32_FILTER_C0;
                        VIF_UserFilter->VifSos32FilterC1  = VIF_SOS_32_FILTER_C1;
                        VIF_UserFilter->VifSos32FilterC2  = VIF_SOS_32_FILTER_C2;
                        VIF_UserFilter->VifSos32FilterC3  = VIF_SOS_32_FILTER_C3;
                        VIF_UserFilter->VifSos32FilterC4  = VIF_SOS_32_FILTER_C4;
                    }
                    else
                    {
                        printf("Error:%s(),%d\n",__func__,__LINE__);
                        return FALSE;
                    }
                break;
                case E_RFBAND_VHF_HIGH:
                    if((u32Param2 == (U32)mapi_demodulator_datatype::IF_FREQ_B) || (u32Param2 == (U32)mapi_demodulator_datatype::IF_FREQ_G))
                    {
                        VIF_UserFilter->VifSos21FilterC0  = VIF_SOS_21_FILTER_C0;
                        VIF_UserFilter->VifSos21FilterC1  = VIF_SOS_21_FILTER_C1;
                        VIF_UserFilter->VifSos21FilterC2  = VIF_SOS_21_FILTER_C2;
                        VIF_UserFilter->VifSos21FilterC3  = VIF_SOS_21_FILTER_C3;
                        VIF_UserFilter->VifSos21FilterC4  = VIF_SOS_21_FILTER_C4;

                        VIF_UserFilter->VifSos22FilterC0  = VIF_SOS_22_FILTER_C0;
                        VIF_UserFilter->VifSos22FilterC1  = VIF_SOS_22_FILTER_C1;
                        VIF_UserFilter->VifSos22FilterC2  = VIF_SOS_22_FILTER_C2;
                        VIF_UserFilter->VifSos22FilterC3  = VIF_SOS_22_FILTER_C3;
                        VIF_UserFilter->VifSos22FilterC4  = VIF_SOS_22_FILTER_C4;

                        VIF_UserFilter->VifSos31FilterC0  = VIF_SOS_31_FILTER_C0;
                        VIF_UserFilter->VifSos31FilterC1  = VIF_SOS_31_FILTER_C1;
                        VIF_UserFilter->VifSos31FilterC2  = VIF_SOS_31_FILTER_C2;
                        VIF_UserFilter->VifSos31FilterC3  = VIF_SOS_31_FILTER_C3;
                        VIF_UserFilter->VifSos31FilterC4  = VIF_SOS_31_FILTER_C4;
                        VIF_UserFilter->VifSos32FilterC0  = VIF_SOS_32_FILTER_C0;
                        VIF_UserFilter->VifSos32FilterC1  = VIF_SOS_32_FILTER_C1;
                        VIF_UserFilter->VifSos32FilterC2  = VIF_SOS_32_FILTER_C2;
                        VIF_UserFilter->VifSos32FilterC3  = VIF_SOS_32_FILTER_C3;
                        VIF_UserFilter->VifSos32FilterC4  = VIF_SOS_32_FILTER_C4;
                    }
                    else if(u32Param2 == (U32)mapi_demodulator_datatype::IF_FREQ_DK)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = VIF_SOS_21_FILTER_C0;
                        VIF_UserFilter->VifSos21FilterC1  = VIF_SOS_21_FILTER_C1;
                        VIF_UserFilter->VifSos21FilterC2  = VIF_SOS_21_FILTER_C2;
                        VIF_UserFilter->VifSos21FilterC3  = VIF_SOS_21_FILTER_C3;
                        VIF_UserFilter->VifSos21FilterC4  = VIF_SOS_21_FILTER_C4;

                        VIF_UserFilter->VifSos22FilterC0  = VIF_SOS_22_FILTER_C0;
                        VIF_UserFilter->VifSos22FilterC1  = VIF_SOS_22_FILTER_C1;
                        VIF_UserFilter->VifSos22FilterC2  = VIF_SOS_22_FILTER_C2;
                        VIF_UserFilter->VifSos22FilterC3  = VIF_SOS_22_FILTER_C3;
                        VIF_UserFilter->VifSos22FilterC4  = VIF_SOS_22_FILTER_C4;

                        VIF_UserFilter->VifSos31FilterC0  = VIF_SOS_31_FILTER_C0;
                        VIF_UserFilter->VifSos31FilterC1  = VIF_SOS_31_FILTER_C1;
                        VIF_UserFilter->VifSos31FilterC2  = VIF_SOS_31_FILTER_C2;
                        VIF_UserFilter->VifSos31FilterC3  = VIF_SOS_31_FILTER_C3;
                        VIF_UserFilter->VifSos31FilterC4  = VIF_SOS_31_FILTER_C4;
                        VIF_UserFilter->VifSos32FilterC0  = VIF_SOS_32_FILTER_C0;
                        VIF_UserFilter->VifSos32FilterC1  = VIF_SOS_32_FILTER_C1;
                        VIF_UserFilter->VifSos32FilterC2  = VIF_SOS_32_FILTER_C2;
                        VIF_UserFilter->VifSos32FilterC3  = VIF_SOS_32_FILTER_C3;
                        VIF_UserFilter->VifSos32FilterC4  = VIF_SOS_32_FILTER_C4;
                    }
                    else if(u32Param2 == (U32)mapi_demodulator_datatype::IF_FREQ_I)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = VIF_SOS_21_FILTER_C0;
                        VIF_UserFilter->VifSos21FilterC1  = VIF_SOS_21_FILTER_C1;
                        VIF_UserFilter->VifSos21FilterC2  = VIF_SOS_21_FILTER_C2;
                        VIF_UserFilter->VifSos21FilterC3  = VIF_SOS_21_FILTER_C3;
                        VIF_UserFilter->VifSos21FilterC4  = VIF_SOS_21_FILTER_C4;

                        VIF_UserFilter->VifSos22FilterC0  = VIF_SOS_22_FILTER_C0;
                        VIF_UserFilter->VifSos22FilterC1  = VIF_SOS_22_FILTER_C1;
                        VIF_UserFilter->VifSos22FilterC2  = VIF_SOS_22_FILTER_C2;
                        VIF_UserFilter->VifSos22FilterC3  = VIF_SOS_22_FILTER_C3;
                        VIF_UserFilter->VifSos22FilterC4  = VIF_SOS_22_FILTER_C4;

                        VIF_UserFilter->VifSos31FilterC0  = VIF_SOS_31_FILTER_C0;
                        VIF_UserFilter->VifSos31FilterC1  = VIF_SOS_31_FILTER_C1;
                        VIF_UserFilter->VifSos31FilterC2  = VIF_SOS_31_FILTER_C2;
                        VIF_UserFilter->VifSos31FilterC3  = VIF_SOS_31_FILTER_C3;
                        VIF_UserFilter->VifSos31FilterC4  = VIF_SOS_31_FILTER_C4;
                        VIF_UserFilter->VifSos32FilterC0  = VIF_SOS_32_FILTER_C0;
                        VIF_UserFilter->VifSos32FilterC1  = VIF_SOS_32_FILTER_C1;
                        VIF_UserFilter->VifSos32FilterC2  = VIF_SOS_32_FILTER_C2;
                        VIF_UserFilter->VifSos32FilterC3  = VIF_SOS_32_FILTER_C3;
                        VIF_UserFilter->VifSos32FilterC4  = VIF_SOS_32_FILTER_C4;
                    }
                    else if(u32Param2 == (U32)mapi_demodulator_datatype::IF_FREQ_L)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = VIF_SOS_21_FILTER_C0;
                        VIF_UserFilter->VifSos21FilterC1  = VIF_SOS_21_FILTER_C1;
                        VIF_UserFilter->VifSos21FilterC2  = VIF_SOS_21_FILTER_C2;
                        VIF_UserFilter->VifSos21FilterC3  = VIF_SOS_21_FILTER_C3;
                        VIF_UserFilter->VifSos21FilterC4  = VIF_SOS_21_FILTER_C4;

                        VIF_UserFilter->VifSos22FilterC0  = VIF_SOS_22_FILTER_C0;
                        VIF_UserFilter->VifSos22FilterC1  = VIF_SOS_22_FILTER_C1;
                        VIF_UserFilter->VifSos22FilterC2  = VIF_SOS_22_FILTER_C2;
                        VIF_UserFilter->VifSos22FilterC3  = VIF_SOS_22_FILTER_C3;
                        VIF_UserFilter->VifSos22FilterC4  = VIF_SOS_22_FILTER_C4;

                        VIF_UserFilter->VifSos31FilterC0  = VIF_SOS_31_FILTER_C0;
                        VIF_UserFilter->VifSos31FilterC1  = VIF_SOS_31_FILTER_C1;
                        VIF_UserFilter->VifSos31FilterC2  = VIF_SOS_31_FILTER_C2;
                        VIF_UserFilter->VifSos31FilterC3  = VIF_SOS_31_FILTER_C3;
                        VIF_UserFilter->VifSos31FilterC4  = VIF_SOS_31_FILTER_C4;
                        VIF_UserFilter->VifSos32FilterC0  = VIF_SOS_32_FILTER_C0;
                        VIF_UserFilter->VifSos32FilterC1  = VIF_SOS_32_FILTER_C1;
                        VIF_UserFilter->VifSos32FilterC2  = VIF_SOS_32_FILTER_C2;
                        VIF_UserFilter->VifSos32FilterC3  = VIF_SOS_32_FILTER_C3;
                        VIF_UserFilter->VifSos32FilterC4  = VIF_SOS_32_FILTER_C4;
                    }
                    else if(u32Param2 == (U32)mapi_demodulator_datatype::IF_FREQ_L_PRIME)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = VIF_SOS_21_FILTER_C0;
                        VIF_UserFilter->VifSos21FilterC1  = VIF_SOS_21_FILTER_C1;
                        VIF_UserFilter->VifSos21FilterC2  = VIF_SOS_21_FILTER_C2;
                        VIF_UserFilter->VifSos21FilterC3  = VIF_SOS_21_FILTER_C3;
                        VIF_UserFilter->VifSos21FilterC4  = VIF_SOS_21_FILTER_C4;

                        VIF_UserFilter->VifSos22FilterC0  = VIF_SOS_22_FILTER_C0;
                        VIF_UserFilter->VifSos22FilterC1  = VIF_SOS_22_FILTER_C1;
                        VIF_UserFilter->VifSos22FilterC2  = VIF_SOS_22_FILTER_C2;
                        VIF_UserFilter->VifSos22FilterC3  = VIF_SOS_22_FILTER_C3;
                        VIF_UserFilter->VifSos22FilterC4  = VIF_SOS_22_FILTER_C4;

                        VIF_UserFilter->VifSos31FilterC0  = VIF_SOS_31_FILTER_C0;
                        VIF_UserFilter->VifSos31FilterC1  = VIF_SOS_31_FILTER_C1;
                        VIF_UserFilter->VifSos31FilterC2  = VIF_SOS_31_FILTER_C2;
                        VIF_UserFilter->VifSos31FilterC3  = VIF_SOS_31_FILTER_C3;
                        VIF_UserFilter->VifSos31FilterC4  = VIF_SOS_31_FILTER_C4;
                        VIF_UserFilter->VifSos32FilterC0  = VIF_SOS_32_FILTER_C0;
                        VIF_UserFilter->VifSos32FilterC1  = VIF_SOS_32_FILTER_C1;
                        VIF_UserFilter->VifSos32FilterC2  = VIF_SOS_32_FILTER_C2;
                        VIF_UserFilter->VifSos32FilterC3  = VIF_SOS_32_FILTER_C3;
                        VIF_UserFilter->VifSos32FilterC4  = VIF_SOS_32_FILTER_C4;
                    }
                    else
                    {
                        printf("Error:%s(),%d\n",__func__,__LINE__);
                        return FALSE;
                    }
                break;
                case E_RFBAND_UHF:
                    if((u32Param2 == (U32)mapi_demodulator_datatype::IF_FREQ_B) || (u32Param2 == (U32)mapi_demodulator_datatype::IF_FREQ_G))
                    {
                        VIF_UserFilter->VifSos21FilterC0  = VIF_SOS_21_FILTER_C0;
                        VIF_UserFilter->VifSos21FilterC1  = VIF_SOS_21_FILTER_C1;
                        VIF_UserFilter->VifSos21FilterC2  = VIF_SOS_21_FILTER_C2;
                        VIF_UserFilter->VifSos21FilterC3  = VIF_SOS_21_FILTER_C3;
                        VIF_UserFilter->VifSos21FilterC4  = VIF_SOS_21_FILTER_C4;

                        VIF_UserFilter->VifSos22FilterC0  = VIF_SOS_22_FILTER_C0;
                        VIF_UserFilter->VifSos22FilterC1  = VIF_SOS_22_FILTER_C1;
                        VIF_UserFilter->VifSos22FilterC2  = VIF_SOS_22_FILTER_C2;
                        VIF_UserFilter->VifSos22FilterC3  = VIF_SOS_22_FILTER_C3;
                        VIF_UserFilter->VifSos22FilterC4  = VIF_SOS_22_FILTER_C4;

                        VIF_UserFilter->VifSos31FilterC0  = VIF_SOS_31_FILTER_C0;
                        VIF_UserFilter->VifSos31FilterC1  = VIF_SOS_31_FILTER_C1;
                        VIF_UserFilter->VifSos31FilterC2  = VIF_SOS_31_FILTER_C2;
                        VIF_UserFilter->VifSos31FilterC3  = VIF_SOS_31_FILTER_C3;
                        VIF_UserFilter->VifSos31FilterC4  = VIF_SOS_31_FILTER_C4;
                        VIF_UserFilter->VifSos32FilterC0  = VIF_SOS_32_FILTER_C0;
                        VIF_UserFilter->VifSos32FilterC1  = VIF_SOS_32_FILTER_C1;
                        VIF_UserFilter->VifSos32FilterC2  = VIF_SOS_32_FILTER_C2;
                        VIF_UserFilter->VifSos32FilterC3  = VIF_SOS_32_FILTER_C3;
                        VIF_UserFilter->VifSos32FilterC4  = VIF_SOS_32_FILTER_C4;
                    }
                    else if(u32Param2 == (U32)mapi_demodulator_datatype::IF_FREQ_DK)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = VIF_SOS_21_FILTER_C0;
                        VIF_UserFilter->VifSos21FilterC1  = VIF_SOS_21_FILTER_C1;
                        VIF_UserFilter->VifSos21FilterC2  = VIF_SOS_21_FILTER_C2;
                        VIF_UserFilter->VifSos21FilterC3  = VIF_SOS_21_FILTER_C3;
                        VIF_UserFilter->VifSos21FilterC4  = VIF_SOS_21_FILTER_C4;

                        VIF_UserFilter->VifSos22FilterC0  = VIF_SOS_22_FILTER_C0;
                        VIF_UserFilter->VifSos22FilterC1  = VIF_SOS_22_FILTER_C1;
                        VIF_UserFilter->VifSos22FilterC2  = VIF_SOS_22_FILTER_C2;
                        VIF_UserFilter->VifSos22FilterC3  = VIF_SOS_22_FILTER_C3;
                        VIF_UserFilter->VifSos22FilterC4  = VIF_SOS_22_FILTER_C4;

                        VIF_UserFilter->VifSos31FilterC0  = VIF_SOS_31_FILTER_C0;
                        VIF_UserFilter->VifSos31FilterC1  = VIF_SOS_31_FILTER_C1;
                        VIF_UserFilter->VifSos31FilterC2  = VIF_SOS_31_FILTER_C2;
                        VIF_UserFilter->VifSos31FilterC3  = VIF_SOS_31_FILTER_C3;
                        VIF_UserFilter->VifSos31FilterC4  = VIF_SOS_31_FILTER_C4;
                        VIF_UserFilter->VifSos32FilterC0  = VIF_SOS_32_FILTER_C0;
                        VIF_UserFilter->VifSos32FilterC1  = VIF_SOS_32_FILTER_C1;
                        VIF_UserFilter->VifSos32FilterC2  = VIF_SOS_32_FILTER_C2;
                        VIF_UserFilter->VifSos32FilterC3  = VIF_SOS_32_FILTER_C3;
                        VIF_UserFilter->VifSos32FilterC4  = VIF_SOS_32_FILTER_C4;
                    }
                    else if(u32Param2 == (U32)mapi_demodulator_datatype::IF_FREQ_I)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = VIF_SOS_21_FILTER_C0;
                        VIF_UserFilter->VifSos21FilterC1  = VIF_SOS_21_FILTER_C1;
                        VIF_UserFilter->VifSos21FilterC2  = VIF_SOS_21_FILTER_C2;
                        VIF_UserFilter->VifSos21FilterC3  = VIF_SOS_21_FILTER_C3;
                        VIF_UserFilter->VifSos21FilterC4  = VIF_SOS_21_FILTER_C4;

                        VIF_UserFilter->VifSos22FilterC0  = VIF_SOS_22_FILTER_C0;
                        VIF_UserFilter->VifSos22FilterC1  = VIF_SOS_22_FILTER_C1;
                        VIF_UserFilter->VifSos22FilterC2  = VIF_SOS_22_FILTER_C2;
                        VIF_UserFilter->VifSos22FilterC3  = VIF_SOS_22_FILTER_C3;
                        VIF_UserFilter->VifSos22FilterC4  = VIF_SOS_22_FILTER_C4;

                        VIF_UserFilter->VifSos31FilterC0  = VIF_SOS_31_FILTER_C0;
                        VIF_UserFilter->VifSos31FilterC1  = VIF_SOS_31_FILTER_C1;
                        VIF_UserFilter->VifSos31FilterC2  = VIF_SOS_31_FILTER_C2;
                        VIF_UserFilter->VifSos31FilterC3  = VIF_SOS_31_FILTER_C3;
                        VIF_UserFilter->VifSos31FilterC4  = VIF_SOS_31_FILTER_C4;
                        VIF_UserFilter->VifSos32FilterC0  = VIF_SOS_32_FILTER_C0;
                        VIF_UserFilter->VifSos32FilterC1  = VIF_SOS_32_FILTER_C1;
                        VIF_UserFilter->VifSos32FilterC2  = VIF_SOS_32_FILTER_C2;
                        VIF_UserFilter->VifSos32FilterC3  = VIF_SOS_32_FILTER_C3;
                        VIF_UserFilter->VifSos32FilterC4  = VIF_SOS_32_FILTER_C4;
                    }
                    else if(u32Param2 == (U32)mapi_demodulator_datatype::IF_FREQ_L)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = VIF_SOS_21_FILTER_C0;
                        VIF_UserFilter->VifSos21FilterC1  = VIF_SOS_21_FILTER_C1;
                        VIF_UserFilter->VifSos21FilterC2  = VIF_SOS_21_FILTER_C2;
                        VIF_UserFilter->VifSos21FilterC3  = VIF_SOS_21_FILTER_C3;
                        VIF_UserFilter->VifSos21FilterC4  = VIF_SOS_21_FILTER_C4;

                        VIF_UserFilter->VifSos22FilterC0  = VIF_SOS_22_FILTER_C0;
                        VIF_UserFilter->VifSos22FilterC1  = VIF_SOS_22_FILTER_C1;
                        VIF_UserFilter->VifSos22FilterC2  = VIF_SOS_22_FILTER_C2;
                        VIF_UserFilter->VifSos22FilterC3  = VIF_SOS_22_FILTER_C3;
                        VIF_UserFilter->VifSos22FilterC4  = VIF_SOS_22_FILTER_C4;

                        VIF_UserFilter->VifSos31FilterC0  = VIF_SOS_31_FILTER_C0;
                        VIF_UserFilter->VifSos31FilterC1  = VIF_SOS_31_FILTER_C1;
                        VIF_UserFilter->VifSos31FilterC2  = VIF_SOS_31_FILTER_C2;
                        VIF_UserFilter->VifSos31FilterC3  = VIF_SOS_31_FILTER_C3;
                        VIF_UserFilter->VifSos31FilterC4  = VIF_SOS_31_FILTER_C4;
                        VIF_UserFilter->VifSos32FilterC0  = VIF_SOS_32_FILTER_C0;
                        VIF_UserFilter->VifSos32FilterC1  = VIF_SOS_32_FILTER_C1;
                        VIF_UserFilter->VifSos32FilterC2  = VIF_SOS_32_FILTER_C2;
                        VIF_UserFilter->VifSos32FilterC3  = VIF_SOS_32_FILTER_C3;
                        VIF_UserFilter->VifSos32FilterC4  = VIF_SOS_32_FILTER_C4;
                    }
                    else if(u32Param2 == (U32)mapi_demodulator_datatype::IF_FREQ_L_PRIME)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = VIF_SOS_21_FILTER_C0;
                        VIF_UserFilter->VifSos21FilterC1  = VIF_SOS_21_FILTER_C1;
                        VIF_UserFilter->VifSos21FilterC2  = VIF_SOS_21_FILTER_C2;
                        VIF_UserFilter->VifSos21FilterC3  = VIF_SOS_21_FILTER_C3;
                        VIF_UserFilter->VifSos21FilterC4  = VIF_SOS_21_FILTER_C4;

                        VIF_UserFilter->VifSos22FilterC0  = VIF_SOS_22_FILTER_C0;
                        VIF_UserFilter->VifSos22FilterC1  = VIF_SOS_22_FILTER_C1;
                        VIF_UserFilter->VifSos22FilterC2  = VIF_SOS_22_FILTER_C2;
                        VIF_UserFilter->VifSos22FilterC3  = VIF_SOS_22_FILTER_C3;
                        VIF_UserFilter->VifSos22FilterC4  = VIF_SOS_22_FILTER_C4;

                        VIF_UserFilter->VifSos31FilterC0  = VIF_SOS_31_FILTER_C0;
                        VIF_UserFilter->VifSos31FilterC1  = VIF_SOS_31_FILTER_C1;
                        VIF_UserFilter->VifSos31FilterC2  = VIF_SOS_31_FILTER_C2;
                        VIF_UserFilter->VifSos31FilterC3  = VIF_SOS_31_FILTER_C3;
                        VIF_UserFilter->VifSos31FilterC4  = VIF_SOS_31_FILTER_C4;
                        VIF_UserFilter->VifSos32FilterC0  = VIF_SOS_32_FILTER_C0;
                        VIF_UserFilter->VifSos32FilterC1  = VIF_SOS_32_FILTER_C1;
                        VIF_UserFilter->VifSos32FilterC2  = VIF_SOS_32_FILTER_C2;
                        VIF_UserFilter->VifSos32FilterC3  = VIF_SOS_32_FILTER_C3;
                        VIF_UserFilter->VifSos32FilterC4  = VIF_SOS_32_FILTER_C4;
                    }
                    else
                    {
                        printf("Error:%s(),%d\n",__func__,__LINE__);
                        return FALSE;
                    }
                break;
                default:
                    printf("Error:%s(),%d\n",__func__,__LINE__);
                    return FALSE;
                break;
            }
        }
        break;

        default:
            UNUSED(u8SubCmd);
            UNUSED(u32Param1);
            UNUSED(u32Param2);
            UNUSED(pvoidParam3);
            return FALSE;
        break;
    }

    return TRUE;
}
#endif

BOOL device_tuner_R842_init(void)
{

    printf("Tuner Init Thread, R842\n");

    if(!bInit_Rafael) //double checklock
    {
        if(!bInit_Rafael)
        {
            if (R842_Init()==R842_Fail)
            {
                printf("R842 init fail....\n");
            }
            else
            {
                bInit_Rafael = 1;
            }
        }
    }
    return TRUE;
}

BOOL ConfigAGCMode(EN_TUNER_MODE eMode)
{
    UNUSED(eMode);
    return TRUE;
}


BOOL SetTunerInScanMode(BOOL bScan)
{
    UNUSED(bScan);
    return TRUE;
}


BOOL SetTunerInFinetuneMode(BOOL bFinetune)
{
    UNUSED(bFinetune);
    return TRUE;
}

BOOL SetTunerStandbyMode(BOOL enable)
{
    if (enable==TRUE)
    {
        if (R842_Standby()!= R842_Success)
        {
            printf("[%s,%d]standby mode active fail...\n",__func__,__LINE__);
            return FALSE;
        }
    }
    else
    {
        if (R842_WakeUp()!= R842_Success)
        {
            printf("[%s,%d]wake up fail...\n",__func__,__LINE__);
            return FALSE;
        }
    }
    return TRUE;
}

void devTunerInit(void)
{
    device_tuner_R842_init();
}

void devDigitalTuner_Init()
{
    device_tuner_R842_init();
}

void devTunerSetFreq(U32 u32Freq)
{
    BOOLEAN retb = TRUE;

    if (bInit_Rafael == FALSE)
    {
        printf("[Error]%s,%d\n",__FILE__,__LINE__);
        return;
    }
    IF_FREQ CurrentStandard = MDrv_IFDM_GetIF();

    //printf("[CurrentStandard],%d\n",CurrentStandard);
    if(CurrentStandard==IF_FREQ_B)
    {
        m_eMode = E_TUNER_ATV_PAL_MODE;
        m_OtherMode = E_AUDIOSTANDARD_BG_;
    }
    else if  (CurrentStandard==IF_FREQ_G)
    {
        m_eMode = E_TUNER_ATV_PAL_MODE;
        m_OtherMode = E_AUDIOSTANDARD_BG_;
    }
    else if  (CurrentStandard==IF_FREQ_I)
    {
        m_eMode = E_TUNER_ATV_PAL_MODE;
        m_OtherMode = E_AUDIOSTANDARD_I_;
    }
    else if  (CurrentStandard==IF_FREQ_DK)
    {
        m_eMode = E_TUNER_ATV_PAL_MODE;
        m_OtherMode = E_AUDIOSTANDARD_DK_;
    }
    else if  (CurrentStandard==IF_FREQ_L)
    {
        m_eMode = E_TUNER_ATV_SECAM_L_MODE;
        m_OtherMode = E_AUDIOSTANDARD_L_;
    }
    else if  (CurrentStandard==IF_FREQ_L_PRIME)
    {
        m_eMode = E_TUNER_ATV_SECAM_L_PRIME_MODE;
        m_OtherMode = E_AUDIOSTANDARD_L_;
    }
    else if  (CurrentStandard==IF_FREQ_MN)
    {
        m_eMode = E_TUNER_ATV_NTSC_MODE;
        m_OtherMode = E_AUDIOSTANDARD_M_;
    }
    else
    {
        m_eMode = E_TUNER_ATV_PAL_MODE;
        m_OtherMode = E_AUDIOSTANDARD_BG_;
    }

    DBG_TUNER(printf("[devTunerSetFreq]%s, %d,  m_OtherMode=%d, u32Freq=%ld, CurrentStandard=%d\n",__FILE__,__LINE__,m_OtherMode,u32Freq,CurrentStandard);)

    retb &= ATV_SetTune(u32Freq/1000,(RFBAND)0, m_eMode,(U8)m_OtherMode);

    if (retb == FALSE)
        printf("[Error]%s,%d\n",__FILE__,__LINE__);

    return;
}
void devDigitalTuner_SetFreq( double Freq,  RF_CHANNEL_BANDWIDTH eBandWidth)
{
    BOOLEAN bRet = TRUE;

    DBG_TUNER(printf("[devDigitalTuner_SetFreq]Freq=%d, eBandWidth=%d, m_eMode=%d\n",(UINT16)Freq,(U8)eBandWidth,(U8)m_eMode);)

    if (bInit_Rafael == FALSE)
    {
        printf("[Error]%s,%d\n",__FILE__,__LINE__);
        return;
    }

    // Freq (MHz)
    bRet &= DTV_SetTune(Freq, eBandWidth, m_eMode);

    if (bRet == FALSE)
        printf("[Error]%s,%d\n",__FILE__,__LINE__);

    return;

}

BOOLEAN devTuner_Std_set(EN_TUNER_MODE eMode, AUDIOSTANDARD_TYPE_ OtherMode)
{
    BOOLEAN bRet = TRUE;
    m_eMode = eMode;
    m_OtherMode = OtherMode;

    DBG_TUNER(printf("devTuner_Std_set, eMode=%d, OtherMode=%d\n",eMode,OtherMode);)

    return bRet;
}

// return dBm....
BOOLEAN mdev_GetSignalStrength(float* f_strength)
{
    INT32 s32_rssi_dbm = 0;

    if (R842_GetTotalRssi2(sg_u32_rf_freq, sg_cur_std, &s32_rssi_dbm) == R842_Fail)
    {
        printf("[Error]R842_GetTotalRssi fail\n");
        s32_rssi_dbm = -10;
        return FALSE;
    }
    *f_strength=(float)s32_rssi_dbm/10.0;
    return TRUE;
}
