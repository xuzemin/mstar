/*
  Copyright (C) 2010 NXP B.V., All Rights Reserved.
  This source code and any compilation or derivative thereof is the proprietary
  information of NXP B.V. and is confidential in nature. Under no circumstances
  is this software to be  exposed to or placed under an Open Source License of
  any type without the expressed written permission of NXP B.V.
 *
 * \file          tmbslTDA182I4.h
 *
 * \date          %modify_time%
 *
 * \author        David LEGENDRE
 *                Michael VANNIER
 *
 * \brief         Describe briefly the purpose of this file.
 *
 * REFERENCE DOCUMENTS :
 *                TDA182I4_Driver_User_Guide.pdf
 *
 * TVFE SW Arch V4 Template: Author Christophe CAZETTES
 *
 * \section info Change Information
 *
*/

#ifndef _TMBSL_TDA182I4_H
#define _TMBSL_TDA182I4_H

#ifdef __cplusplus
extern "C"
{
#endif

/*============================================================================*/
/* TDA182I4 Error Codes                                                       */
/*============================================================================*/

#define TDA182I4_ERR_BASE                       (CID_COMP_TUNER | CID_LAYER_BSL)
#define TDA182I4_ERR_COMP                       (CID_COMP_TUNER | CID_LAYER_BSL | TM_ERR_COMP_UNIQUE_START)

#define TDA182I4_ERR_BAD_UNIT_NUMBER            (TDA182I4_ERR_BASE + TM_ERR_BAD_UNIT_NUMBER)
#define TDA182I4_ERR_ERR_NO_INSTANCES           (TDA182I4_ERR_BASE + TM_ERR_NO_INSTANCES)
#define TDA182I4_ERR_NOT_INITIALIZED            (TDA182I4_ERR_BASE + TM_ERR_NOT_INITIALIZED)
#define TDA182I4_ERR_ALREADY_SETUP              (TDA182I4_ERR_BASE + TM_ERR_ALREADY_SETUP)
#define TDA182I4_ERR_INIT_FAILED                (TDA182I4_ERR_BASE + TM_ERR_INIT_FAILED)
#define TDA182I4_ERR_BAD_PARAMETER              (TDA182I4_ERR_BASE + TM_ERR_BAD_PARAMETER)
#define TDA182I4_ERR_NOT_SUPPORTED              (TDA182I4_ERR_BASE + TM_ERR_NOT_SUPPORTED)
#define TDA182I4_ERR_NULL_CONTROLFUNC           (TDA182I4_ERR_BASE + TM_ERR_NULL_CONTROLFUNC)
#define TDA182I4_ERR_HW_FAILED                  (TDA182I4_ERR_COMP + 0x0001)
#define TDA182I4_ERR_NOT_READY                  (TDA182I4_ERR_COMP + 0x0002)
#define TDA182I4_ERR_BAD_VERSION                (TDA182I4_ERR_COMP + 0x0003)
#define TDA182I4_ERR_STD_NOT_SET                (TDA182I4_ERR_COMP + 0x0004)
#define TDA182I4_ERR_RF_NOT_SET                 (TDA182I4_ERR_COMP + 0x0005)

/*============================================================================*/
/* Types and defines:                                                         */
/*============================================================================*/

typedef enum _TDA182I4PowerState_t {
    TDA182I4_PowerNormalMode = 0,                                 /* Device normal mode */
    TDA182I4_PowerStandbyWithXtalOn,                              /* Device standby mode with Xtal Output */
    TDA182I4_PowerStandbyWithLtOnWithXtalOn,                      /* Device standby mode with LT on and with Xtal Output */
    TDA182I4_PowerStandbyWithPllOnWithXtalOn,                     /* Device standby mode with PLL on and with Xtal Output */
    TDA182I4_PowerStandbyWithLtOnWithPllOnWithXtalOn,             /* Device standby mode with LT on with PLL on and with Xtal Output */
    TDA182I4_PowerMax
} TDA182I4PowerState_t, *pTDA182I4PowerState_t;

typedef enum _TDA182I4StandardMode_t {
    TDA182I4_StandardMode_Unknown = 0,                  /* Unknown standard */
    TDA182I4_QAM_6MHz,                                  /* Digital TV QAM 6MHz */
    TDA182I4_QAM_8MHz,                                  /* Digital TV QAM 8MHz */
    TDA182I4_ATSC_6MHz,                                 /* Digital TV ATSC 6MHz */
    TDA182I4_ISDBT_6MHz,                                /* Digital TV ISDBT 6MHz */
    TDA182I4_DVBT_1_7MHz,                               /* Digital TV DVB-T/T2 6MHz */
    TDA182I4_DVBT_6MHz,                                 /* Digital TV DVB-T/T2 6MHz */
    TDA182I4_DVBT_7MHz,                                 /* Digital TV DVB-T/T2 7MHz */
    TDA182I4_DVBT_8MHz,                                 /* Digital TV DVB-T/T2 8MHz */
    TDA182I4_DVBT_10MHz,                                /* Digital TV DVB-T/T2 10MHz */     
    TDA182I4_DMBT_6MHz, 								/* Digital TV DMB-T 6MHz */
    TDA182I4_DMBT_8MHz,                                 /* Digital TV DMB-T 8MHz */
    TDA182I4_FM_Radio,                                  /* Analog FM Radio */
    TDA182I4_ANLG_MN,                                   /* Analog TV M/N */
    TDA182I4_ANLG_B,                                    /* Analog TV B */
    TDA182I4_ANLG_GH,                                   /* Analog TV G/H */
    TDA182I4_ANLG_I,                                    /* Analog TV I */
    TDA182I4_ANLG_DK,                                   /* Analog TV D/K */
    TDA182I4_ANLG_L,                                    /* Analog TV L */
    TDA182I4_ANLG_LL,                                   /* Analog TV L' */
    TDA182I4_Scanning,                                  /* Analog Preset Blind Scanning */
    TDA182I4_ScanXpress,                                /* ScanXpress */
    TDA182I4_StandardMode_Max
} TDA182I4StandardMode_t, *pTDA182I4StandardMode_t;


#define isTDA182I4_DGTL_STD(_CURSTD) ( (((_CURSTD)>=TDA182I4_QAM_6MHz) && ((_CURSTD)<=TDA182I4_DMBT_8MHz)) || ((_CURSTD)==TDA182I4_ScanXpress) )
#define isTDA182I4_ANLG_STD(_CURSTD) ( ((_CURSTD)>=TDA182I4_FM_Radio) && ((_CURSTD)<=TDA182I4_Scanning) )


/* Register Bit-Field Definition */
typedef struct _TDA182I4_BitField_t
{
    UInt8   Address;
    UInt8   PositionInBits;
    UInt8   WidthInBits;
    UInt8   Attributes;
}
TDA182I4_BitField_t, *pTDA182I4_BitField_t;

/*============================================================================*/
/* Exported functions:                                                        */
/*============================================================================*/

tmErrorCode_t
tmbslTDA182I4_Open(
    tmUnitSelect_t              tUnit,      /*  I: Unit number */
    tmbslFrontEndDependency_t*  psSrvFunc   /*  I: setup parameters */
);

tmErrorCode_t
tmbslTDA182I4_Close(
    tmUnitSelect_t  tUnit   /*  I: Unit number */
);

tmErrorCode_t
tmbslTDA182I4_GetSWVersion(
    ptmSWVersion_t  pSWVersion  /*  I: Receives SW Version */
);

tmErrorCode_t
tmbslTDA182I4_GetSWSettingsVersion(
    ptmSWSettingsVersion_t pSWSettingsVersion   /* O: Receives SW Settings Version */
);

tmErrorCode_t
tmbslTDA182I4_CheckHWVersion(
    tmUnitSelect_t tUnit    /* I: Unit number */
);

tmErrorCode_t
tmbslTDA182I4_SetPowerState(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    tmPowerState_t  powerState  /* I: Power state */
);

tmErrorCode_t
tmbslTDA182I4_GetPowerState(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    tmPowerState_t* pPowerState /* O: Power state */
);

tmErrorCode_t
tmbslTDA182I4_SetLLPowerState(
    tmUnitSelect_t          tUnit,      /* I: Unit number */
    TDA182I4PowerState_t  powerState  /* I: Power state of TDA182I4 */
);

tmErrorCode_t
tmbslTDA182I4_GetLLPowerState(
    tmUnitSelect_t          tUnit,      /* I: Unit number */
    TDA182I4PowerState_t* pPowerState /* O: Power state of TDA182I4 */
);

tmErrorCode_t
tmbslTDA182I4_SetStandardMode(
    tmUnitSelect_t              tUnit,          /*  I: Unit number */
    TDA182I4StandardMode_t    StandardMode    /*  I: Standard mode of this device */
);

tmErrorCode_t
tmbslTDA182I4_GetStandardMode(
    tmUnitSelect_t              tUnit,          /*  I: Unit number */
    TDA182I4StandardMode_t    *pStandardMode  /*  O: Standard mode of this device */
);

tmErrorCode_t
tmbslTDA182I4_SetRF(
    tmUnitSelect_t  tUnit,  /*  I: Unit number */
    UInt32          uRF     /*  I: RF frequency in hertz */
);

tmErrorCode_t
tmbslTDA182I4_GetRF(
    tmUnitSelect_t  tUnit,  /*  I: Unit number */
    UInt32*         pRF     /*  O: RF frequency in hertz */
);

tmErrorCode_t
tmbslTDA182I4_HwInit(
    tmUnitSelect_t tUnit    /* I: Unit number */
);

tmErrorCode_t
tmbslTDA182I4_GetIF(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt32*         puIF    /* O: IF Frequency in hertz */
);

tmErrorCode_t
tmbslTDA182I4_GetCF_Offset(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    UInt32*         puOffset    /* O: Center frequency offset in hertz */
);

tmErrorCode_t
tmbslTDA182I4_GetLockStatus(
    tmUnitSelect_t          tUnit,      /* I: Unit number */
    tmbslFrontEndState_t*   pLockStatus /* O: PLL Lock status */
);

tmErrorCode_t
tmbslTDA182I4_GetAgcStatus(
    tmUnitSelect_t          tUnit,       /* I: Unit number */
    Bool*                   pbAgcLock,   /* O: AGC Lock status */
    Bool*                   pbAgcMax     /* O: AGC Max status */
);

tmErrorCode_t
tmbslTDA182I4_SetGpio(
    tmUnitSelect_t          tUnit,           /* I: Unit number */
    UInt8                   bNumber,         /* I: Number of the GPIO to set */
    Bool                    bActive          /* I: GPIO enabled/disabled */
);

tmErrorCode_t
tmbslTDA182I4_GetPowerLevel(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    UInt8*          pPowerLevel /* O: Power Level in 1/2 steps dBµV */
);

tmErrorCode_t
tmbslTDA182I4_SetInternalVsync(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    Bool            bEnabled    /* I: Enable of disable the internal VSYNC */
);

tmErrorCode_t
tmbslTDA182I4_GetInternalVsync(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    Bool*           pbEnabled   /* O: current status of the internal VSYNC */
);

tmErrorCode_t
tmbslTDA182I4_SetPllManual(
    tmUnitSelect_t  tUnit,         /* I: Unit number */
    Bool            bOverridePLL   /* I: Determine if we need to put PLL in manual mode in SetRF */
);

tmErrorCode_t
tmbslTDA182I4_GetPllManual(
    tmUnitSelect_t  tUnit,         /* I: Unit number */
    Bool*           pbOverridePLL  /* O: Determine if we need to put PLL in manual mode in SetRF */
);

tmErrorCode_t
tmbslTDA182I4_GetIRQ(
    tmUnitSelect_t  tUnit  /* I: Unit number */,
    Bool*           pbIRQ  /* O: IRQ triggered */
);

tmErrorCode_t
tmbslTDA182I4_WaitIRQ(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    UInt32          timeOut,    /* I: timeOut for IRQ wait */
    UInt32          waitStep,   /* I: wait step */
    UInt8           irqStatus   /* I: IRQs to wait */
);

tmErrorCode_t
tmbslTDA182I4_GetXtalCal_End(
    tmUnitSelect_t  tUnit           /* I: Unit number */,
    Bool*           pbXtalCal_End   /* O: XtalCal_End triggered */
);

/* You can only add one step (-1 or +1) at a time along -125 KHz <-> -62.5 KHz <-> 0 <-> 62.5 KHz <-> 125 KHz */
/* After calling tmbslTDA182I4_SetRF, step is reset at 0 */
tmErrorCode_t
tmbslTDA182I4_SetFineRF(
    tmUnitSelect_t tUnit,      /* I: Unit number */
    Int8           step        /* I: step (-1, +1) */
);

tmErrorCode_t
tmbslTDA182I4_Write(
    tmUnitSelect_t              tUnit,      /* I: Unit number */
    const TDA182I4_BitField_t*  pBitField,  /* I: Bitfield structure */
    UInt8                       uData,      /* I: Data to write */
    tmbslFrontEndBusAccess_t    eBusAccess  /* I: Access to bus */
);

tmErrorCode_t
tmbslTDA182I4_Read(
    tmUnitSelect_t              tUnit,      /* I: Unit number */
    const TDA182I4_BitField_t*  pBitField,  /* I: Bitfield structure */
    UInt8*                      puData,     /* I: Data to read */
    tmbslFrontEndBusAccess_t    eBusAccess  /* I: Access to bus */
);

tmErrorCode_t
tmbslTDA182I4_SetFEF(
    tmUnitSelect_t              tUnit,      /* I: Unit number */
    Bool bFefEnable                         /* Activate/desactivate FEF settings for DVB-T/T2 */
);

tmErrorCode_t
tmbslTDA182I4_GetFEF(
    tmUnitSelect_t              tUnit,      /* I: Unit number */
    Bool* bFefEnable                        /* get FEF settings for DVB-T/T2 status*/
);
/*============================================================================*/
/* Legacy compatibility:                                                      */
/*============================================================================*/

#ifndef tmbslTDA182I4Init
 #define tmbslTDA182I4Init tmbslTDA182I4_Open
#endif

#ifndef tmbslTDA182I4DeInit
 #define tmbslTDA182I4DeInit tmbslTDA182I4_Close
#endif

#ifndef tmbslTDA182I4GetSWVersion
 #define tmbslTDA182I4GetSWVersion tmbslTDA182I4_GetSWVersion
#endif

#ifndef tmbslTDA182I4GetSWSettingsVersion
 #define tmbslTDA182I4GetSWSettingsVersion tmbslTDA182I4_GetSWSettingsVersion
#endif

#ifndef tmbslTDA182I4CheckHWVersion
 #define tmbslTDA182I4CheckHWVersion tmbslTDA182I4_CheckHWVersion
#endif

#ifndef tmbslTDA182I4SetPowerState
 #define tmbslTDA182I4SetPowerState tmbslTDA182I4_SetLLPowerState
#endif

#ifndef tmbslTDA182I4GetPowerState
 #define tmbslTDA182I4GetPowerState tmbslTDA182I4_GetLLPowerState
#endif

#ifndef tmbslTDA182I4SetLLPowerState
 #define tmbslTDA182I4SetLLPowerState tmbslTDA182I4_SetLLPowerState
#endif

#ifndef tmbslTDA182I4GetLLPowerState
 #define tmbslTDA182I4GetLLPowerState tmbslTDA182I4_GetLLPowerState
#endif

#ifndef tmbslTDA182I4SetStandardMode
 #define tmbslTDA182I4SetStandardMode tmbslTDA182I4_SetStandardMode
#endif

#ifndef tmbslTDA182I4GetStandardMode
 #define tmbslTDA182I4GetStandardMode tmbslTDA182I4_GetStandardMode
#endif

#ifndef tmbslTDA182I4SetRf
 #define tmbslTDA182I4SetRf tmbslTDA182I4_SetRF
#endif

#ifndef tmbslTDA182I4GetRf
 #define tmbslTDA182I4GetRf tmbslTDA182I4_GetRF
#endif

#ifndef tmbslTDA182I4Reset
 #define tmbslTDA182I4Reset tmbslTDA182I4_HwInit
#endif

#ifndef tmbslTDA182I4GetIF
 #define tmbslTDA182I4GetIF tmbslTDA182I4_GetIF
#endif

#ifndef tmbslTDA182I4GetCF_Offset
 #define tmbslTDA182I4GetCF_Offset tmbslTDA182I4_GetCF_Offset
#endif

#ifndef tmbslTDA182I4GetLockStatus
 #define tmbslTDA182I4GetLockStatus tmbslTDA182I4_GetLockStatus
#endif

#ifndef tmbslTDA182I4GetPowerLevel
 #define tmbslTDA182I4GetPowerLevel tmbslTDA182I4_GetPowerLevel
#endif

#ifndef tmbslTDA182I4GetRSSI
 #define tmbslTDA182I4GetRSSI tmbslTDA182I4_GetRSSI
#endif

#ifndef tmbslTDA182I4SetIRQWait
 #define tmbslTDA182I4SetIRQWait tmbslTDA182I4_SetIRQWait
#endif

#ifndef tmbslTDA182I4GetIRQWait
 #define tmbslTDA182I4GetIRQWait tmbslTDA182I4_GetIRQWait
#endif

#ifndef tmbslTDA182I4SetIRQWaitHwInit
 #define tmbslTDA182I4SetIRQWaitHwInit tmbslTDA182I4_SetIRQWaitHwInit
#endif

#ifndef tmbslTDA182I4GetIRQWaitHwInit
 #define tmbslTDA182I4GetIRQWaitHwInit tmbslTDA182I4_GetIRQWaitHwInit
#endif

#ifndef tmbslTDA182I4GetIRQ
 #define tmbslTDA182I4GetIRQ tmbslTDA182I4_GetIRQ
#endif

#ifndef tmbslTDA182I4WaitIRQ
 #define tmbslTDA182I4WaitIRQ tmbslTDA182I4_WaitIRQ
#endif

#ifndef tmbslTDA182I4GetXtalCal_End
 #define tmbslTDA182I4GetXtalCal_End tmbslTDA182I4_GetXtalCal_End
#endif

#ifndef tmbslTDA182I4RFFineTuning
 #define tmbslTDA182I4RFFineTuning tmbslTDA182I4_SetFineRF
#endif

#ifndef tmbslTDA182I4Write
 #define tmbslTDA182I4Write tmbslTDA182I4_Write
#endif

#ifndef tmbslTDA182I4Read
 #define tmbslTDA182I4Read tmbslTDA182I4_Read
#endif

#define tmTDA182I4PowerState_t TDA182I4PowerState_t
#define tmTDA182I4_PowerNormalMode TDA182I4_PowerNormalMode
#define tmTDA182I4_PowerStandbyWithXtalOn TDA182I4_PowerStandbyWithXtalOn
#define tmTDA182I4_PowerStandby TDA182I4_PowerStandby
#define tmTDA182I4_PowerMax TDA182I4_PowerMax

#define tmTDA182I4StandardMode_t TDA182I4StandardMode_t
#define tmTDA182I4_QAM_6MHz TDA182I4_QAM_6MHz
#define tmTDA182I4_QAM_8MHz TDA182I4_QAM_8MHz
#define tmTDA182I4_ATSC_6MHz TDA182I4_ATSC_6MHz
#define tmTDA182I4_ISDBT_6MHz TDA182I4_ISDBT_6MHz
#define tmTDA182I4_DVBT_1_7MHz TDA182I4_DVBT_1_7MHz
#define tmTDA182I4_DVBT_6MHz TDA182I4_DVBT_6MHz
#define tmTDA182I4_DVBT_7MHz TDA182I4_DVBT_7MHz
#define tmTDA182I4_DVBT_8MHz TDA182I4_DVBT_8MHz
#define tmTDA182I4_DVBT_10MHz TDA182I4_DVBT_10MHz
#define tmTDA182I4_DMBT_6MHz TDA182I4_DMBT_6MHz
#define tmTDA182I4_DMBT_8MHz TDA182I4_DMBT_8MHz
#define tmTDA182I4_FM_Radio TDA182I4_FM_Radio
#define tmTDA182I4_ANLG_MN TDA182I4_ANLG_MN
#define tmTDA182I4_ANLG_B TDA182I4_ANLG_B
#define tmTDA182I4_ANLG_GH TDA182I4_ANLG_GH
#define tmTDA182I4_ANLG_I TDA182I4_ANLG_I
#define tmTDA182I4_ANLG_DK TDA182I4_ANLG_DK
#define tmTDA182I4_ANLG_L TDA182I4_ANLG_L
#define tmTDA182I4_ANLG_LL TDA182I4_ANLG_LL
#define tmTDA182I4_Scanning TDA182I4_Scanning
#define tmTDA182I4_ScanXpress TDA182I4_ScanXpress
#define tmTDA182I4_StandardMode_Max TDA182I4_StandardMode_Max



#ifdef __cplusplus
}
#endif

#endif /* _TMBSL_TDA182I4_H */

