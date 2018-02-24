/*
  Copyright (C) 2010 NXP B.V., All Rights Reserved.
  This source code and any compilation or derivative thereof is the proprietary
  information of NXP B.V. and is confidential in nature. Under no circumstances
  is this software to be  exposed to or placed under an Open Source License of
  any type without the expressed written permission of NXP B.V.
 *
 * \file          tmbslTDA182I4.c
 *
 *                %version: CFR_FEAP#39 %
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
/*****************ES2 *****************/

/*============================================================================*/
/* Standard include files:                                                    */
/*============================================================================*/
#include "tmNxTypes.h"
#include "tmCompId.h"
#include "tmFrontEnd.h"
#include "tmbslFrontEndTypes.h"

/*============================================================================*/
/* Project include files:                                                     */
/*============================================================================*/
#include "tmbslTDA182I4.h"

#include "tmbslTDA182I4_RegDef.h"
#include "tmbslTDA182I4_Local.h"
#include "tmbslTDA182I4_Instance.h"
#include "tmbslTDA182I4_InstanceCustom.h"


/*============================================================================*/
/* Static internal functions:                                                 */
/*============================================================================*/
static tmErrorCode_t
iTDA182I4_SetLLPowerState(pTDA182I4Object_t pObj, TDA182I4PowerState_t powerState);

static tmErrorCode_t
iTDA182I4_OverrideBandsplit(pTDA182I4Object_t pObj);

static tmErrorCode_t
iTDA182I4_OverrideICP(pTDA182I4Object_t pObj, UInt32 freq);

static tmErrorCode_t
iTDA182I4_OverrideWireless(pTDA182I4Object_t pObj);

tmErrorCode_t
iTDA182I4_CalculatePostDivAndPrescaler(UInt32 LO, Bool growingOrder, UInt8* PostDiv, UInt8* Prescaler);

static tmErrorCode_t
iTDA182I4_FindPostDivAndPrescalerWithBetterMargin(UInt32 LO, UInt8* PostDiv, UInt8* Prescaler);

tmErrorCode_t
iTDA182I4_CalculateNIntKInt(UInt32 LO, UInt8 PostDiv, UInt8 Prescaler, UInt32* NInt, UInt32* KInt);

static tmErrorCode_t
iTDA182I4_SetPLL(pTDA182I4Object_t pObj);

tmErrorCode_t
iTDA182I4_GetRSSI(
    pTDA182I4Object_t   pObj,   /* I: Driver object */
    UInt8*              puValue /* O: RSSI value */
);

tmErrorCode_t
iTDA182I4_SetIRcal(pTDA182I4Object_t pObj);


/*============================================================================*/
/* Static variables:                                                          */
/*============================================================================*/
typedef struct _TDA182I4_PostDivPrescalerTableDef_
{
    UInt32 LO_max;
    UInt32 LO_min;
    UInt8 Prescaler;
    UInt8 PostDiv;
} TDA182I4_PostDivPrescalerTableDef;

/* Table that maps LO vs Prescaler & PostDiv values */
static TDA182I4_PostDivPrescalerTableDef PostDivPrescalerTable[35] =
{
    /* PostDiv 1 */
    {1080000, 882000, 7, 1},
    {882001, 771750, 8, 1},
    {784000, 686000, 9, 1},
    {705600, 617400, 10, 1},
    {641454, 561272, 11, 1},
    {587999, 514499, 12, 1},
    {542768, 474922, 13, 1},
    /* PostDiv 2 */
    {503998, 440998, 7, 2},
    {440999, 385873, 8, 2},
    {391998, 342998, 9, 2},
    {352798, 308698, 10, 2},
    {320725, 280634, 11, 2},
    {293997, 257247, 12, 2},
    {271381, 237458, 13, 2},
    /* PostDiv 4 */   
    {251996, 220496, 7, 4},
    {220497, 192934, 8, 4},
    {195996, 171496, 9, 4},
    {176396, 154346, 10, 4},
    {160360, 140315, 11, 4},
    {146996, 128621, 12, 4},
    {135688, 118727, 13, 4},
    /* PostDiv 8 */
    {125996, 110246, 7, 8},
    {110247, 96465, 8, 8},
    {97996, 85746, 9, 8},
    {88196, 77171, 10, 8},
    {80178, 70155, 11, 8},
    {73496, 64309, 12, 8},
    {67842, 59361, 13, 8},
    /* PostDiv 16 */
    {62996, 55121, 7, 16},
    {55122, 48230, 8, 16},
    {48996, 42871, 9, 16},
    {44096, 38584, 10, 16},
    {40087, 35076, 11, 16},
    {36746, 32152, 12, 16},
    {33919, 29679, 13, 16}
};

typedef struct _TDA182I4_PldFreqCorrectionTableDef_
{
    UInt16 Freq;  /* Mhz * 10  */
    Int16 Correction;  /* in 1/2 dB * 10 */
} TDA182I4_PldFreqCorrectionTableDef;

#define PldRfCorrection_length  126
static  TDA182I4_PldFreqCorrectionTableDef PldRFCorrection[PldRfCorrection_length] = { \
        /* format { from freq, correction 1/2 step} */
    { 0, 0 }, \
    { 430, 102 }, \
    { 602, 96 }, \
    { 773, 92 }, \
    { 945, 88 }, \
    { 1117, 82 }, \
    { 1288, 78 }, \
    { 1460, 84 }, \
    { 1504, 88 }, \
    { 1549, 94 }, \
    { 1593, 98 }, \
    { 1637, 102 }, \
    { 1682, 106 }, \
    { 1726, 86 }, \
    { 1934, 82 }, \
    { 2143, 76 }, \
    { 2351, 82 }, \
    { 2382, 88 }, \
    { 2412, 92 }, \
    { 2443, 90 }, \
    { 2522, 94 }, \
    { 2600, 100 }, \
    { 2679, 104 }, \
    { 2757, 108 }, \
    { 2836, 114 }, \
    { 2914, 90 }, \
    { 3200, 104 }, \
    { 3508, 98 }, \
    { 3590, 94 }, \
    { 3672, 96 }, \
    { 3692, 90 }, \
    { 3713, 86 }, \
    { 3733, 80 }, \
    { 3753, 56 }, \
    { 3845, 62 }, \
    { 3937, 66 }, \
    { 4030, 72 }, \
    { 4122, 76 }, \
    { 4214, 80 }, \
    { 4306, 102 }, \
    { 4399, 106 }, \
    { 4491, 84 }, \
    { 4573, 90 }, \
    { 4654, 94 }, \
    { 4736, 78 }, \
    { 5351, 82 }, \
    { 5415, 86 }, \
    { 5479, 90 }, \
    { 5543, 96 }, \
    { 5607, 76 }, \
    { 5627, 56 }, \
    { 5699, 54 }, \
    { 5771, 44 }, \
    { 6007, 40 }, \
    { 6242, 52 }, \
    { 6483, 48 }, \
    { 6723, 42 }, \
    { 6964, 38 }, \
    { 7204, 66 }, \
    { 7450, 52 }, \
    { 7691, 56 }, \
    { 7931, 30 }, \
    { 8113, 26 }, \
    { 8295, 22 }, \
    { 8476, 18 }, \
    { 8685, 22 }, \
    { 8712, 28 }, \
    { 8738, 32 }, \
    { 8765, 38 }, \
    { 8792, 50 }, \
    { 8818, 46 }, \
    { 8844, 40 }, \
    { 8870, 36 }, \
    { 8896, 32 }, \
    { 8923, 28 }, \
    { 8949, 22 }, \
    { 8975, 18 }, \
    { 9001, 14 }, \
    { 9027, 22 }, \
    { 9043, 18 }, \
    { 9060, 12 }, \
    { 9076, 8 }, \
    { 9093, 4 }, \
    { 9109, -2 }, \
    { 9125, -6 }, \
    { 9142, -12 }, \
    { 9158, -16 }, \
    { 9175, -20 }, \
    { 9191, -26 }, \
    { 9207, -30 }, \
    { 9224, -36 }, \
    { 9240, -40 }, \
    { 9257, -44 }, \
    { 9273, -54 }, \
    { 9293, -58 }, \
    { 9313, -62 }, \
    { 9333, -68 }, \
    { 9353, -72 }, \
    { 9373, -78 }, \
    { 9393, -82 }, \
    { 9413, -88 }, \
    { 9433, -92 }, \
    { 9453, -98 }, \
    { 9473, -102 }, \
    { 9493, -108 }, \
    { 9513, -112 }, \
    { 9533, -116 }, \
    { 9553, -122 }, \
    { 9573, -126 }, \
    { 9593, -132 }, \
    { 9613, -136 }, \
    { 9633, -142 }, \
    { 9653, -146 }, \
    { 9673, -152 }, \
    { 9693, -158 }, \
    { 9723, -162 }, \
    { 9752, -168 }, \
    { 9782, -172 }, \
    { 9812, -178 }, \
    { 9842, -182 }, \
    { 9871, -188 }, \
    { 9901, -192 }, \
    { 9931, -198 }, \
    { 9961, -202 }, \
    { 9990, -208 }, \
    { 10020, -210 } \
    };
typedef struct _TDA182I4_PldRfAgcCorrectionTableDef_
{
    UInt16 RfAgc;  /* 0 ... 511  */
    Int8 Correction_22;  /* in 1/2 dB * 10 */
    Int8 Correction_no22;  /* in 1/2 dB * 10 */
} TDA182I4_PldRfAgcCorrectionTableDef;

#define PldRfAgcCorrection_length  54
static  TDA182I4_PldRfAgcCorrectionTableDef PldRfAgcCorrection[PldRfAgcCorrection_length] = { \
        /* format { from RfAgc, 1/2 step  correction AGC1 = 22dB,1/2 step Correction AGC1 not 22dB } */
    { 0, -36 , -50  }, \
    { 115, -38 , -48  }, \
    { 120, -36 , -46  }, \
    { 125, -36 , -42  }, \
    { 130, -32 , -40  }, \
    { 135, -30 , -40  }, \
    { 140, -28 , -38  }, \
    { 150, -26 , -38  }, \
    { 155, -26 , -40  }, \
    { 165, -24 , -38  }, \
    { 170, -22 , -38  }, \
    { 180, -20 , -38  }, \
    { 190, -18 , -38  }, \
    { 195, -18 , -36  }, \
    { 200, -18 , -34  }, \
    { 205, -16 , -34  }, \
    { 210, -16 , -30  }, \
    { 215, -14 , -26  }, \
    { 220, -14 , -22  }, \
    { 225, -14 , -18  }, \
    { 230, -12 , -18  }, \
    { 235, -12 , -16  }, \
    { 240, -10 , -14  }, \
    { 245, -8 , -10  }, \
    { 250, -6 , -6  }, \
    { 255, -4 , -4  }, \
    { 260, 0 , -2  }, \
    { 265, 2 , -2  }, \
    { 270, 4 , 2  }, \
    { 275, 6 , 4  }, \
    { 280, 8 , 6  }, \
    { 285, 10 , 8  }, \
    { 295, 12 , 10  }, \
    { 305, 14 , 12  }, \
    { 310, 12 , 12  }, \
    { 320, 10 , 10  }, \
    { 325, 8 , 10  }, \
    { 335, 8 , 8  }, \
    { 365, 10 , 8  }, \
    { 370, 10 , 10  }, \
    { 385, 8 , 10  }, \
    { 390, 8 , 8  }, \
    { 400, 6 , 6  }, \
    { 405, 4 , 4  }, \
    { 410, 2 , 2  }, \
    { 420, 2 , 0  }, \
    { 425, 0 , 0  }, \
    { 430, 2 , 2  }, \
    { 440, 0 , 0  }, \
    { 450, -2 , -2  }, \
    { 460, 0 , 0  }, \
    { 470, -2 , -2  }, \
    { 480, 0 , 0  }, \
    { 495, 2 , 0  }, \
    };

/* Middle of VCO frequency excursion : VCOmin + (VCOmax - VCOmin)/2 in KHz */
#define TDA182I4_MIDDLE_FVCO_RANGE ((705600 - 617400) / 2 + 617400)

/*============================================================================*/
/* Exported functions:                                                        */
/*============================================================================*/

/*============================================================================*/
/* FUNCTION:    tmbslTDA182I4_Open:                                           */
/*                                                                            */
/* DESCRIPTION: Opens driver setup environment.                               */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA182I4_Open(
    tmUnitSelect_t              tUnit,      /* I: FrontEnd unit number */
    tmbslFrontEndDependency_t*  psSrvFunc   /* I: setup parameters */
)
{
    pTDA182I4Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Test parameter(s) */
    if(psSrvFunc == Null)
    {
        err = TDA182I4_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        /* Get a driver instance */
        err = iTDA182I4_GetInstance(tUnit, &pObj);
    }

    /* Check driver instance state */
    if(err == TM_OK || err == TDA182I4_ERR_ERR_NO_INSTANCES)
    {
        if(P_OBJ_VALID && pObj->init == True)
        {
            err = TDA182I4_ERR_ALREADY_SETUP;
        }
        else 
        {
            if(P_OBJ_VALID == False)
            {
                /* Try to allocate an instance of the driver */
                err = iTDA182I4_AllocInstance(tUnit, &pObj);
                if(err != TM_OK || pObj == Null)
                {
                    err = TDA182I4_ERR_ERR_NO_INSTANCES;
                }
            }

            if(err == TM_OK)
            {
                /* Initialize the Object by default values */
                P_SIO = P_FUNC_SIO(psSrvFunc);
                P_STIME = P_FUNC_STIME(psSrvFunc);
                P_SDEBUG = P_FUNC_SDEBUG(psSrvFunc);

#ifdef _TVFE_IMPLEMENT_MUTEX
                if(    P_FUNC_SMUTEX_OPEN_VALID(psSrvFunc)
                    && P_FUNC_SMUTEX_CLOSE_VALID(psSrvFunc)
                    && P_FUNC_SMUTEX_ACQUIRE_VALID(psSrvFunc)
                    && P_FUNC_SMUTEX_RELEASE_VALID(psSrvFunc) )
                {
                    P_SMUTEX = psSrvFunc->sMutex;

                    err = P_SMUTEX_OPEN(&P_MUTEX);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "Mutex_Open(0x%08X) failed.", tUnit));
                }
#endif

                tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA182I4_Open(0x%08X)", tUnit);

                if(err == TM_OK)
                {
                    pObj->init = True;
                }
            }
        }
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA182I4_Close:                                          */
/*                                                                            */
/* DESCRIPTION: Closes driver setup environment.                              */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA182I4_Close(
    tmUnitSelect_t  tUnit   /* I: FrontEnd unit number */
)
{
    pTDA182I4Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA182I4_GetInstance(tUnit, &pObj);

    if(err == TM_OK)
    {
#ifdef _TVFE_IMPLEMENT_MUTEX
        /* Try to acquire driver mutex */
        err = iTDA182I4_MutexAcquire(pObj, TDA182I4_MUTEX_TIMEOUT);

        if(err == TM_OK)
        {
#endif
            tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA182I4_Close(0x%08X)", tUnit);

#ifdef _TVFE_IMPLEMENT_MUTEX
            P_SMUTEX_ACQUIRE = Null;

            /* Release driver mutex */
            (void)iTDA182I4_MutexRelease(pObj);

            if(P_SMUTEX_CLOSE_VALID && P_MUTEX_VALID)
            {
                err = P_SMUTEX_CLOSE(P_MUTEX);
            }

            P_SMUTEX_OPEN = Null;
            P_SMUTEX_CLOSE = Null;
            P_SMUTEX_RELEASE = Null;

            P_MUTEX = Null;
        }
#endif

        err = iTDA182I4_DeAllocInstance(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA182I4_GetSWVersion:                                   */
/*                                                                            */
/* DESCRIPTION: Gets the versions of the driver.                              */
/*                                                                            */
/* RETURN:      TM_OK                                                         */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA182I4_GetSWVersion(
    ptmSWVersion_t  pSWVersion  /* I: Receives SW Version */
)
{
    pSWVersion->compatibilityNr = TDA182I4_COMP_NUM;
    pSWVersion->majorVersionNr  = TDA182I4_MAJOR_VER;
    pSWVersion->minorVersionNr  = TDA182I4_MINOR_VER;

    return TM_OK;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA182I4_GetSWSettingsVersion:                           */
/*                                                                            */
/* DESCRIPTION: Returns the version of the driver settings.                   */
/*                                                                            */
/* RETURN:      TM_OK                                                         */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA182I4_GetSWSettingsVersion(
    ptmSWSettingsVersion_t pSWSettingsVersion   /* O: Receives SW Settings Version */
)
{
    pSWSettingsVersion->customerNr      = TDA182I4_SETTINGS_CUSTOMER_NUM;
    pSWSettingsVersion->projectNr       = TDA182I4_SETTINGS_PROJECT_NUM;
    pSWSettingsVersion->majorVersionNr  = TDA182I4_SETTINGS_MAJOR_VER;
    pSWSettingsVersion->minorVersionNr  = TDA182I4_SETTINGS_MINOR_VER;

    return TM_OK;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA182I4_CheckHWVersion:                                 */
/*                                                                            */
/* DESCRIPTION: Checks TDA182I4 HW Version.                                   */
/*                                                                            */
/* RETURN:      TM_OK                                                         */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA182I4_CheckHWVersion(
    tmUnitSelect_t tUnit    /* I: Unit number */
)
{
    pTDA182I4Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;
    UInt16              uIdentity = 0;
    UInt8               ID_byte_1 = 0;
    UInt8               ID_byte_2 = 0;
    UInt8               majorRevision = 0;
    UInt8               minorRevision = 0;

    /* Get a driver instance */
    err = iTDA182I4_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA182I4)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA182I4_CheckHWVersion(0x%08X)", tUnit);

    err = iTDA182I4_ReadRegMap(pObj, gTDA182I4_Reg_ID_byte_1.Address, TDA182I4_REG_DATA_LEN(gTDA182I4_Reg_ID_byte_1__Ident_1, gTDA182I4_Reg_ID_byte_3));
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_ReadRegMap(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_ID_byte_1__Ident_1, &ID_byte_1, Bus_None);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Read(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_ID_byte_2__Ident_2, &ID_byte_2, Bus_None);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Read(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        /* Construct Identity */
        uIdentity = (ID_byte_1 << 8) | ID_byte_2;

        if ((uIdentity == 18274) || (uIdentity == 18214))
        {
            /* TDA182I4 found. Check Major & Minor Revision */
            err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_ID_byte_3__Major_rev, &majorRevision, Bus_None);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Read(0x%08X) failed.", tUnit));

            err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_ID_byte_3__Minor_rev, &minorRevision, Bus_None);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Read(0x%08X) failed.", tUnit));

        }
        else
        {
            err = TDA182I4_ERR_BAD_VERSION;
        }
    }

    _MUTEX_RELEASE(TDA182I4)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA182I4_SetPowerState                                   */
/*                                                                            */
/* DESCRIPTION: Sets the power state.                                         */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA182I4_SetPowerState(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    tmPowerState_t  powerState  /* I: Power state */
 )
{
    pTDA182I4Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA182I4_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA182I4)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA182I4_SetPowerState(0x%08X)", tUnit);

    if(powerState>=tmPowerMax)
    {
        err = TDA182I4_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        if(pObj->mapLLPowerState[powerState] != pObj->curLLPowerState)
        {
            err = iTDA182I4_SetLLPowerState(pObj, pObj->mapLLPowerState[powerState]);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_SetLLPowerState(0x%08X, %d) failed.", tUnit, (int)pObj->mapLLPowerState[powerState]));

            if(err == TM_OK)
            {
                /* Store power state in driver instance */
                pObj->curPowerState = powerState;
            }
        }
    }

    _MUTEX_RELEASE(TDA182I4)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA182I4_GetPowerState:                                  */
/*                                                                            */
/* DESCRIPTION: Gets the power state.                                         */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA182I4_GetPowerState(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    tmPowerState_t* pPowerState /* O: Power state */
)
{
    pTDA182I4Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA182I4_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA182I4)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA182I4_GetPowerState(0x%08X)", tUnit);

    /* Test parameter(s) */
    if(pPowerState == Null)
    {
        err = TDA182I4_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        *pPowerState = pObj->curPowerState;
    }

    _MUTEX_RELEASE(TDA182I4)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA182I4_SetLLPowerState                                 */
/*                                                                            */
/* DESCRIPTION: Sets the power state.                                         */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA182I4_SetLLPowerState(
    tmUnitSelect_t          tUnit,      /* I: Unit number */
    TDA182I4PowerState_t    powerState  /* I: Power state of TDA182I4 */
 )
{
    pTDA182I4Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA182I4_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA182I4)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA182I4_SetLLPowerState(0x%08X)", tUnit);

    pObj->curPowerState = tmPowerMax;

    err = iTDA182I4_SetLLPowerState(pObj, powerState);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_SetLLPowerState(0x%08X, %d) failed.", tUnit, (int)powerState));

    _MUTEX_RELEASE(TDA182I4)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA182I4_GetLLPowerState                                 */
/*                                                                            */
/* DESCRIPTION: Gets the power state.                                         */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA182I4_GetLLPowerState(
    tmUnitSelect_t          tUnit,      /* I: Unit number */
    TDA182I4PowerState_t*   pPowerState /* O: Power state of TDA182I4 */
)
{
    pTDA182I4Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;
    UInt8               uValue = 0;


    /* Get a driver instance */
    err = iTDA182I4_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA182I4)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA182I4_GetLLPowerState(0x%08X)", tUnit);

    /* Test parameter(s) */
    if(pPowerState == Null)
    {
        err = TDA182I4_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_Power_state_byte_2__power_state_mode, &uValue, Bus_RW);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Read(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
		switch (uValue)
		{
			case TDA182I4_power_state_mode_NORMAL_MODE_VALUE_0:
				*pPowerState = TDA182I4_PowerNormalMode;
				break;
			case TDA182I4_power_state_mode_STDBY_PLUS16M_VALUE_1:
				*pPowerState = TDA182I4_PowerStandbyWithXtalOn;
				break;
			case TDA182I4_power_state_mode_STDBY_PLUS16M_PLUS_LT_VALUE_2:
				*pPowerState = TDA182I4_PowerStandbyWithLtOnWithXtalOn;
				break;
			case TDA182I4_power_state_mode_STDBY_PLUS16M_PLUS_PLL_VALUE_3:
				*pPowerState = TDA182I4_PowerStandbyWithPllOnWithXtalOn;
				break;
			case TDA182I4_power_state_mode_STDBY_PLUS_16M_PLUS_LT_PLUS_PLL_VALUE_4:
				*pPowerState = TDA182I4_PowerStandbyWithLtOnWithPllOnWithXtalOn;
				break;
			default :
				err = TDA182I4_ERR_NOT_SUPPORTED;
				break;
		}

    }

    _MUTEX_RELEASE(TDA182I4)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA182I4_SetGpio                                         */
/*                                                                            */
/* DESCRIPTION: Sets the GPIOs.                                               */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA182I4_SetGpio(
    tmUnitSelect_t          tUnit,           /* I: Unit number */
    UInt8                   bNumber,         /* I: Number of the GPIO to set */
    Bool                    bActive          /* I: GPIO enabled/disabled */
)
{
    pTDA182I4Object_t           pObj = Null;
    tmErrorCode_t               err = TM_OK;

    /* Get a driver instance */
    err = iTDA182I4_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA182I4)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA182I4_SetGpio(0x%08X)", tUnit);

    if(err == TM_OK)
    {
        switch (bNumber)
        {
            case 1:
                /* Set GPIO n°1 */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Gpio_ctrl_byte__GPIO1, (bActive==True)?1:0, Bus_RW);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
                break;

            case 2:
                /* Set GPIO n°2 */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Gpio_ctrl_byte__GPIO2, (bActive==True)?1:0, Bus_RW);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
                break;

            default:
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA182I4_SetGpio(0x%08X) invalid GPIO number.", tUnit));
                break;
        }
    }

    _MUTEX_RELEASE(TDA182I4)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA182I4_SetStandardMode                                 */
/*                                                                            */
/* DESCRIPTION: Sets the standard mode.                                       */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA182I4_SetStandardMode(
    tmUnitSelect_t          tUnit,          /* I: Unit number */
    TDA182I4StandardMode_t  StandardMode    /* I: Standard mode of this device */
)
{
    pTDA182I4Object_t           pObj = Null;
    tmErrorCode_t               err = TM_OK;
    pTDA182I4StdCoefficients    prevPStandard = Null;

    /* Get a driver instance */
    err = iTDA182I4_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA182I4)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA182I4_SetStandardMode(0x%08X)", tUnit);

    /* Check if Hw is ready to operate */
    err = iTDA182I4_CheckHwState(pObj, TDA182I4_HwStateCaller_SetStd);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_CheckHwState(0x%08X) failed.", pObj->tUnitW));

    if(err == TM_OK)
    {
        /* Store standard mode */
        pObj->StandardMode = StandardMode;

        /* Reset standard map pointer */
        prevPStandard = pObj->pStandard;
        pObj->pStandard = Null;

        if(pObj->StandardMode>TDA182I4_StandardMode_Unknown && pObj->StandardMode<TDA182I4_StandardMode_Max)
        {
             pObj->pStandard = &pObj->Std_Array[pObj->StandardMode - 1];

            /****************************************************************/
            /* DVB-T/T2 FEF Settings                                          */
            /****************************************************************/
            if (( pObj->StandardMode >= TDA182I4_DVBT_1_7MHz ) && ( pObj->StandardMode <= TDA182I4_DVBT_10MHz ) && (pObj->bFefEnable) )
            {
                /* Set AGCs_Up_step */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC2_byte_1__AGCs_Up_step, 0x01, Bus_None);
                /* Set PD_Ovld */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Vsync_Mgt_byte__PD_Ovld, 0x01, Bus_None);
                /* Set PD_Ovld_RF */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Vsync_Mgt_byte__PD_Ovld_RF, 0x01, Bus_None);
            }
            else
            {
                /* Set AGCs_Up_step */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC2_byte_1__AGCs_Up_step, 0x03, Bus_None);
                /* Set PD_Ovld */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Vsync_Mgt_byte__PD_Ovld, 0x00, Bus_None);
                
				/******************************************************************/
				/* For all SECAM standards, enable PD Overload RF (register 0x2A) */
				/******************************************************************/
				if ( pObj->bCenelecMargin &&
                    (
					(pObj->StandardMode == TDA182I4_ANLG_DK) ||
					(pObj->StandardMode == TDA182I4_ANLG_L) ||
					(pObj->StandardMode == TDA182I4_ANLG_LL)
				   ) )
				{
					/* Set PD_Ovld_RF */
					err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Vsync_Mgt_byte__PD_Ovld_RF, 0x01, Bus_None);
				}
				else
				{
					/* Set PD_Ovld_RF */
					err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Vsync_Mgt_byte__PD_Ovld_RF, 0x00, Bus_None);
				}
            }

            /****************************************************************/
            /* IF SELECTIVITY Settings                                      */
            /****************************************************************/

            /* Set LPFc */
            err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_IF_Byte_1__LP_Fc, pObj->pStandard->LPF, Bus_None);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));

            /* Set LPFc Offset */
            err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_IF_Byte_1__IF_LPF_Offset,(UInt8)(pObj->pStandard->LPF_Offset >>4), Bus_None);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));

            /* Set sign */
            err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_IF_Byte_1__IF_LPF_sign, (UInt8)(pObj->pStandard->LPF_Offset & 0x0f), Bus_None);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));



            if(err == TM_OK)
            {
                /* Enable/disable HPF */
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_IF_Byte_2__IF_HP_Enable,(UInt8)(pObj->pStandard->HPF & 0x0f), Bus_None);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));

                    /* Set IF HPF */
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_IF_Byte_2__IF_HP_Fc, (UInt8)(pObj->pStandard->HPF >> 4), Bus_None);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
            }

            /* Set HPFc Offset */
            if(err == TM_OK)
            {
				/* Set offset */
				err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_IF_Byte_2__IF_HPF_Offset, (UInt8)(pObj->pStandard->HPF_Offset >>4), Bus_None);
				tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));

				/* Set sign */
				err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_IF_Byte_2__IF_HPF_sign, (UInt8)(pObj->pStandard->HPF_Offset & 0x0f), Bus_None);
				tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Set IF notch to RSSI */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_IF_AGC_byte__IFnotchToRSSI, pObj->pStandard->IFnotchToRSSI, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
            }
            if(err == TM_OK)
            {
                /* Set IF Notch */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_IF_Byte_3__IF_Notch_Enable, pObj->pStandard->IF_Notch_Enable, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
            }
            /* Set IF_Notch_Freq */
            if(err == TM_OK)
            {
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_IF_Byte_3__IF_Notch_Freq, pObj->pStandard->IF_Notch_Freq, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
			}

			/* Set IF_Notch Offset */
            if(err == TM_OK)
            {
                /* Set offset */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_IF_Byte_3__IF_Notch_Offset, (UInt8)(pObj->pStandard->IF_Notch_Offset >>4), Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));

                /* Set sign */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_IF_Byte_3__IF_Notch_sign, (UInt8)(pObj->pStandard->IF_Notch_Offset & 0x0f), Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
            }
            /****************************************************************/
            /* AGC TOP Settings                                             */
            /****************************************************************/

            if(err == TM_OK)
            {
                /* Set AGC1 TOP I2C DN/UP */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_1__AGC1_Top, pObj->pStandard->AGC1_TOP_I2C_DN_UP, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
            }
            
            if(err == TM_OK)
            {
                /* Set AGC1_Top_Strategy */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_1__AGC1_Top_Strategy, pObj->pStandard->AGC1_TOP_STRATEGY, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
            }
            if(err == TM_OK)
            {
                /* Set LNA_zin */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_2__LNA_Zin, pObj->pStandard->LNA_Zin, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
            }
			if(err == TM_OK)
            {
                /* Set RFAGC_Peak_Val */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_RF_AGC_byte_2__RFAGC_Peak_Val, pObj->pStandard->RFAGC_Peak_Val, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
            }
			if(err == TM_OK)
            {
                /* SetRFAGC_Adapt_TOP_ovld */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_RF_AGC_byte_2__RFAGC_Adapt_TOP_ovld, pObj->pStandard->RFAGC_Adapt_TOP_ovld, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
			}    
			if(err == TM_OK)
            {
                /* Set RFAGC_det_mode */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_RF_AGC_byte_2__RFAGC_det_mode, pObj->pStandard->RFAGC_det_mode, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
			}    
            if(err == TM_OK)
            {
                /* Set AGC3 RF AGC Top */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_RF_AGC_byte_1__RFAGC_Top, pObj->pStandard->AGC3_TOP_I2C, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Set AGC3 Adapt TOP */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_RF_AGC_byte_1__RFAGC_Adapt_TOP, pObj->pStandard->AGC3_Adapt_TOP, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Set AGC4 TOP DN/UP */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_IR_Mixer_byte_1__IR_Mixer_Top, pObj->pStandard->AGC4_TOP_DN_UP, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
            }
            if(err == TM_OK)
            {
                /* Set DC_Notch_IF_PPF */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_IR_Mixer_byte_2__DC_Notch, pObj->pStandard->DC_Notch_IF_PPF, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Set AGC5 TOP DN/UP */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC5_byte_1__AGC5_TOP, pObj->pStandard->AGC5_TOP_DN_UP, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Set RSSI HP FC */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC5_byte_1__RSSI_HP_Fc, pObj->pStandard->RSSI_HP_FC, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Set AGC5 HP FC */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC5_byte_1__AGC5_HP_Fc, pObj->pStandard->AGC5_HP_FC, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Set AGC3_Top_Adapt_Algorithm */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_RF_AGC_byte_1__PD_AGC_Adapt35, ((pObj->pStandard->AGC3_Top_Adapt_Algorithm) >> 1) & 0x1, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));

                if(err == TM_OK)
                {
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_RF_AGC_byte_1__PD_AGC_Adapt34, (pObj->pStandard->AGC3_Top_Adapt_Algorithm) & 0x1, Bus_None);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
                }
            }

            if(err == TM_OK)
            {
                /* Set AGC Overload TOP */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Vsync_Mgt_byte__AGC_Ovld_TOP, pObj->pStandard->AGC_Overload_TOP, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Set RF atten 3dB */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_W_Filter_byte__RF_Atten_3dB, pObj->pStandard->RF_Atten_3dB, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Set IF Output Level */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_IF_AGC_byte__IF_level, pObj->pStandard->IF_Output_Level, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Set S2D gain */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_IR_Mixer_byte_1__S2D_Gain, pObj->pStandard->S2D_Gain, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Set Negative modulation */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Vsync_byte__Neg_Modulation, pObj->pStandard->Negative_Modulation, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
            }

            /****************************************************************/
            /* GSK Settings                                                 */
            /****************************************************************/

            if(err == TM_OK)
            {
                /* Set AGCK Time Constant */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGCK_byte_1__AGCK_Mode, pObj->pStandard->AGCK_Time_Constant, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
            }

            /****************************************************************/
            /* H3H5 Settings                                                */
            /****************************************************************/

            if(err == TM_OK)
            {
                /* Set VHF_III_Mode */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_W_Filter_byte__VHF_III_mode, pObj->pStandard->VHF_III_Mode, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
            }

            /****************************************************************/
            /* IF Settings                                                  */
            /****************************************************************/

            if(err == TM_OK)
            {
                /* Set IF */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_IF_Frequency_byte__IF_Freq, (UInt8)((pObj->pStandard->IF - pObj->pStandard->CF_Offset)/50000), Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
            }
			if(err == TM_OK)
			{
				err = iTDA182I4_PowerSavingMode(pObj, pObj->pStandard->PowerSavingMode);
			}

			/* Blocks final writting */
            if(err == TM_OK)
            {
                /* Write AGC1_byte_1 (0x0D) to IF_Frequency_byte (0x1C) Registers */
                err = iTDA182I4_WriteRegMap(pObj, gTDA182I4_Reg_AGC1_byte_1.Address, TDA182I4_REG_DATA_LEN(gTDA182I4_Reg_AGC1_byte_1, gTDA182I4_Reg_IF_Frequency_byte));
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_WriteRegMap(0x%08X) failed.", pObj->tUnitW));
            }
            if(err == TM_OK)
            {
                /* Write gTDA182I4_Reg_Adapt_Top_byte (0x28) to gTDA182I4_Reg_IR_Mixer_byte_2 (0x2B) Registers */
                err = iTDA182I4_WriteRegMap(pObj, gTDA182I4_Reg_Adapt_Top_byte.Address, TDA182I4_REG_DATA_LEN(gTDA182I4_Reg_Adapt_Top_byte, gTDA182I4_Reg_IR_Mixer_byte_2));
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_WriteRegMap(0x%08X) failed.", pObj->tUnitW));
            }
            if(err == TM_OK)
            {
                /* Set RSSI_Cap_Val */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_RSSI_byte_2__RSSI_Cap_Val, pObj->pStandard->RSSI_Cap_Val, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
            }
            if(err == TM_OK)
            {
                /* Set RSSI_Cap_Val */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_RSSI_byte_2__RSSI_Ck_Speed, pObj->pStandard->RSSI_Ck_Speed, Bus_NoRead);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
            }

        }

        /* Update driver state machine */
        pObj->eHwState = TDA182I4_HwState_SetStdDone;
    }

    _MUTEX_RELEASE(TDA182I4)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA182I4_GetStandardMode                                 */
/*                                                                            */
/* DESCRIPTION: Gets the standard mode.                                       */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA182I4_GetStandardMode(
    tmUnitSelect_t          tUnit,          /* I: Unit number */
    TDA182I4StandardMode_t  *pStandardMode  /* O: Standard mode of this device */
)
{
    pTDA182I4Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA182I4_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA182I4)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA182I4_GetStandardMode(0x%08X)", tUnit);

    if(pStandardMode == Null)
    {
        err = TDA182I4_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        /* Get standard mode */
        *pStandardMode = pObj->StandardMode;
    }

    _MUTEX_RELEASE(TDA182I4)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA182I4_SetRF:                                          */
/*                                                                            */
/* DESCRIPTION: Tunes to a RF.                                                */
/*                                                                            */
/* RETURN:      TM_OK                                                         */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA182I4_SetRF(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt32          uRF     /* I: RF frequency in hertz */
)
{
    pTDA182I4Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA182I4_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA182I4)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA182I4_SetRF(0x%08X)", tUnit);

    /* Test parameter(s) */
    if(   pObj->StandardMode<=TDA182I4_StandardMode_Unknown
       || pObj->StandardMode>=TDA182I4_StandardMode_Max
       || pObj->pStandard == Null)
    {
        err = TDA182I4_ERR_STD_NOT_SET;
    }

    if(err == TM_OK)
    {
        /* Check if Hw is ready to operate */
        err = iTDA182I4_CheckHwState(pObj, TDA182I4_HwStateCaller_SetRF);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_CheckHwState(0x%08X) failed.", pObj->tUnitW));
    }
    if(err == TM_OK)
    {
        pObj->uRF = uRF;
        pObj->uProgRF = pObj->uRF + pObj->pStandard->CF_Offset;

        err = iTDA182I4_SetRF(pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_SetRF(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Update driver state machine */
            pObj->eHwState = TDA182I4_HwState_SetRFDone;
        }
    }

    _MUTEX_RELEASE(TDA182I4)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA182I4_GetRF:                                          */
/*                                                                            */
/* DESCRIPTION: Gets tuned RF.                                                */
/*                                                                            */
/* RETURN:      TM_OK                                                         */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA182I4_GetRF(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt32*         puRF    /* O: RF frequency in hertz */
)
{
    pTDA182I4Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA182I4_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA182I4)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA182I4_GetRF(0x%08X)", tUnit);

    if(puRF == Null)
    {
        err = TDA182I4_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        /* Get RF */
        *puRF = pObj->uRF;
    }

    _MUTEX_RELEASE(TDA182I4)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA182I4_HwInit:                                         */
/*                                                                            */
/* DESCRIPTION: Initializes TDA182I4 Hardware.                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA182I4_HwInit(
    tmUnitSelect_t  tUnit   /* I: Unit number */
)
{
    pTDA182I4Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;
	UInt8 uVal;
    UInt32 counter = 10; /* Wait I2C ready */

    /* Get a driver instance */
    err = iTDA182I4_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA182I4)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA182I4_HwInit(0x%08X)", tUnit);

    /* Reset standard mode & Hw State */
    pObj->StandardMode = TDA182I4_StandardMode_Max;
    pObj->eHwState = TDA182I4_HwState_InitNotDone;

    while(counter > 0)
    {
        /* Read all bytes */
        err = iTDA182I4_ReadRegMap(pObj, 0x00, TDA182I4_REG_MAP_NB_BYTES);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_ReadRegMap(0x%08X) failed.", tUnit));

        if(err==TM_OK)
        {
            /* IC I2C responds */
            break;
        }

        if(counter)
        {
            /* Decrease the counter */
            counter--;

            /* Wait for a step of  1ms */
            err = iTDA182I4_Wait(pObj, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Wait(0x%08X) failed.", pObj->tUnitW));
        }
	}
    if(err == TM_OK)
    {
        err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_Reference_Byte__Xtout_Amp, &uVal, Bus_None);
        if(uVal!=pObj->curXTOutAmp)
        {
            /* XTOUT Amplitude */
            err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Reference_Byte__Xtout_Amp, pObj->curXTOutAmp, Bus_NoRead);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
        }
    }

    /****************************************************/
    /* Change POR values                                */
    /****************************************************/
    if(err == TM_OK)
    {
        err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_AGC1_byte_2__LNA_Range, &uVal, Bus_None);
        /* LNA gain range */
        if(uVal!=pObj->curLNA_Range)
        {
            err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_2__LNA_Range, pObj->curLNA_Range, Bus_NoRead);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
        }
    }
	if(err == TM_OK)
    {   /* Ovld_Tcst -> 0.2ms */
        err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_RF_AGC_byte_3__RFAGC_Ovld_Tcst, 0x01, Bus_None);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
    }
	if(err == TM_OK)
    {   /*  nber_up -> 0 nber_do -> 8 */
        err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_RF_AGC_byte_3__RFAGC_Ovld_nb, 0x03, Bus_NoRead);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
    }
    if(err == TM_OK)
    {
		/* smooth_cc  -> 0 ( Tuner in single, STO not used ) else 1 (Tuner in dual, STO used ) */
		uVal = (pObj->TunerModeInUse & TDA182I4_Mode_STO_Used ) ? 1: 0;
		err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_smooth_cc_byte_1__smooth_cc, uVal, Bus_None);
		tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
	}
    if(err == TM_OK)
    {
		/* switch_smooth_t_cst */
		err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_smooth_cc_byte_1__switch_smooth_t_cst, 0x05, Bus_NoRead);
		tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
	}
	if(err == TM_OK)
	{
		/* PD_RF_BUF_LTO  -> 1 ( Tuner in single, STO not used ) else 0 (Tuner in dual, STO used ) */
		uVal = (pObj->TunerModeInUse & TDA182I4_Mode_STO_Used || pObj->TunerModeInUse & TDA182I4_Mode_LTO_Used ) ? 0: 1;
		err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_LT_byte_1__PD_RF_BUF_LTO, uVal, Bus_None);
		tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
	}
	if(err == TM_OK)
	{
		/* PD_LT  -> TDA18274 or TDA1814 slave : 1  else 0  */
		uVal = (pObj->TunerModeInUse & TDA182I4_Mode_LTO_Used ) ? 0: 1;
		err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_LT_byte_1__PD_LT, uVal, Bus_NoRead);
    }
    if(err == TM_OK)
    {
        /* AGC1_Do_step -> 2.044 ms */
        err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_3__AGC1_Do_step, 0x01, Bus_None);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
    }
    if(err == TM_OK)
    {
		/* activate AGC1_rst_do_enable  */
        err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_4__AGC1_rst_do_enable, 0x01, Bus_None);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
    }
    if(err == TM_OK)
    {
        /* Write AGC1_byte_3 (0x2E) & AGC1_byte_4 (0x2F) Registers */
        err = iTDA182I4_WriteRegMap(pObj, gTDA182I4_Reg_AGC1_byte_3.Address, 0x02);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_WriteRegMap(0x%08X) failed.", pObj->tUnitW));
    }
    /* all Cprog to code 1  */
	if(err == TM_OK)
    {
        /* RF_Cal_byte_1  */
        err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_RF_Cal_byte_1, 0x55, Bus_None);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
        /* RF_Cal_byte_2  */
        err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_RF_Cal_byte_3, 0x55, Bus_None);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
        /* RF_Cal_byte_3  */
        err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_RF_Cal_byte_2, 0x55, Bus_None);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
	}
    if(err == TM_OK)
    {
        /* Write RF_Cal_byte_1 (0x33) to gTDA182I4_Reg_RF_Cal_byte_3 (0x35) Registers */
        err = iTDA182I4_WriteRegMap(pObj, gTDA182I4_Reg_RF_Cal_byte_1.Address, TDA182I4_REG_DATA_LEN(gTDA182I4_Reg_RF_Cal_byte_1, gTDA182I4_Reg_RF_Cal_byte_3));
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_WriteRegMap(0x%08X) failed.", pObj->tUnitW));
    }
	if(err == TM_OK)
	{
		/* PD_Udld -> 1 for LTE  */
		err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Vsync_Mgt_byte__PD_Udld, 0x01, Bus_NoRead);
		tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
	}
	if(err == TM_OK)
    { /* Set PLL calc in auto */
        err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Sigma_delta_byte_5__N_K_correct_manual, 0x00, Bus_None);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
    }
    if(err == TM_OK)
    {
        err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Sigma_delta_byte_5__LO_Calc_Disable, 0x00, Bus_None);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
    }
	if(err == TM_OK)
    {
        /* LOSetAll =2 --> synchronisation with register only. */
        err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Sigma_delta_byte_5__LO_SetAll, 0x02, Bus_NoRead);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
    }
	if(err == TM_OK)
	{
		err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Charge_pump_byte__ICP, 0x02, Bus_NoRead);
		tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));		
	}
	if(err == TM_OK)
	{
		err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_RC_Cal_byte_1__RC_Cal_Offset, TDA182I4_RC_Cal_Offset, Bus_NoRead);
		tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));		
	}

    /* wake-up tuner  */
	if(err == TM_OK)
	{
		err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Power_state_byte_2__power_state_mode, TDA182I4_PowerNormalMode, Bus_NoRead);
		tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
	}

    if(err == TM_OK)
    {
        pObj->curPowerState = tmPowerOn;

	     if(err == TM_OK)
	    {
			/* Set IRQ_clear */
			err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_IRQ_clear, TDA182I4_IRQ_Global|TDA182I4_IRQ_HwInit, Bus_NoRead);
			tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
		}       
	    /* Launch tuner calibration */

        /* Set state machine and Launch it */
        if(err == TM_OK)
        {
            err = iTDA182I4_SetMSM(pObj, TDA182I4_MSM_HwInit, True);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_SetMSM(0x%08X, TDA182I4_MSM_HwInit) failed.", pObj->tUnitW));
        }

        /* Inform that init phase has started */
        if(err == TM_OK)
        {
            pObj->eHwState = TDA182I4_HwState_InitPending;
        }

        if(err == TM_OK)
        {
            /* State reached after 600 ms max */
            err = iTDA182I4_WaitIRQ(pObj, 600, 10, TDA182I4_IRQ_HwInit);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_WaitIRQ(0x%08X) failed.", tUnit));
        }

        /* Run Software IRcal : copy Mid IRcal ti High IRcal */
		if(err == TM_OK)
		{
            err = iTDA182I4_SetIRcal(pObj);
        }
        
        if(err == TM_OK && pObj->eHwState == TDA182I4_HwState_InitPending)
        {
            pObj->eHwState = TDA182I4_HwState_InitDone;
        }
		else
		{
			pObj->eHwState = TDA182I4_HwState_InitNotDone;
		}
        /* put Tuner in stand-by */
		if(err == TM_OK)
		{
		    /* Set digital clock mode to 16 Mhz before entering standby */
		    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Reference_Byte__Dig_Clock, 0x02, Bus_NoRead);
		    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
        }
		if(err == TM_OK)
		{
            if ( pObj->TunerModeInUse & TDA182I4_Mode_STO_Used )
            {
		        /* Set power state to stdby default 16Mhz ( XTOUT on , LT/LNA on  , PLL off) */
		        err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Power_state_byte_2__power_state_mode, TDA182I4_PowerStandbyWithLtOnWithXtalOn, Bus_NoRead);
		        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
		        if(err == TM_OK)
		        {
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_2__AGC1_FastStbyLT_Enable, 0x00, Bus_NoRead);
			        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
                }
                if(err == TM_OK)
                {
                    /* Disable PD_LNA  */
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_1__PD_LNA, 0x00, Bus_NoRead);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
                }
            }
            else
            {
		        /* Set power state to stdby default 16Mhz ( XTOUT on , LT/LNA off , PLL off) */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Power_state_byte_2__power_state_mode, TDA182I4_PowerStandbyWithXtalOn, Bus_NoRead);
		        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
            }
         
		}
		if(err == TM_OK)
		{
            pObj->curPowerState = tmPowerStandby;
		}

    }

    _MUTEX_RELEASE(TDA182I4)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA182I4_GetIF:                                          */
/*                                                                            */
/* DESCRIPTION: Gets programmed IF.                                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA182I4_GetIF(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt32*         puIF    /* O: IF Frequency in hertz */
)
{
    pTDA182I4Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA182I4_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA182I4)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA182I4_GetIF(0x%08X)", tUnit);

    /* Test parameter(s) */
    if(   pObj->StandardMode<=TDA182I4_StandardMode_Unknown
        || pObj->StandardMode>=TDA182I4_StandardMode_Max
        || pObj->pStandard == Null
        || puIF == Null)
    {
        err = TDA182I4_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        *puIF = pObj->pStandard->IF - pObj->pStandard->CF_Offset;
    }

    _MUTEX_RELEASE(TDA182I4)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA182I4_GetCF_Offset:                                   */
/*                                                                            */
/* DESCRIPTION: Gets CF Offset.                                               */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA182I4_GetCF_Offset(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    UInt32*         puOffset    /* O: Center frequency offset in hertz */
)
{
    pTDA182I4Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA182I4_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA182I4)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA182I4_GetCF_Offset(0x%08X)", tUnit);

    /* Test parameter(s) */
    if(   pObj->StandardMode<=TDA182I4_StandardMode_Unknown
        || pObj->StandardMode>=TDA182I4_StandardMode_Max
        || pObj->pStandard == Null
        || puOffset == Null)
    {
        err = TDA182I4_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        *puOffset = pObj->pStandard->CF_Offset;
    }

    _MUTEX_RELEASE(TDA182I4)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA182I4_GetLockStatus:                                  */
/*                                                                            */
/* DESCRIPTION: Gets PLL Lock Status.                                         */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA182I4_GetLockStatus(
    tmUnitSelect_t          tUnit,      /* I: Unit number */
    tmbslFrontEndState_t*   pLockStatus /* O: PLL Lock status */
)
{
    pTDA182I4Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;
    UInt8               uValue = 0, uValueLO = 0;

    /* Get a driver instance */
    err = iTDA182I4_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA182I4)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA182I4_GetLockStatus(0x%08X)", tUnit);

    if( pLockStatus == Null )
    {
        err = TDA182I4_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_Power_state_byte_1__LO_Lock, &uValueLO, Bus_RW);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Read(0x%08X) failed.", pObj->tUnitW));

        if(err == TM_OK)
        {
            err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_IRQ_status__IRQ_status, &uValue, Bus_RW);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Read(0x%08X) failed.", pObj->tUnitW));
        }

        if(err == TM_OK)
        {
            uValue = uValue & uValueLO;

            *pLockStatus =  (uValue)? tmbslFrontEndStateLocked : tmbslFrontEndStateNotLocked;
        }
        else
        {
            *pLockStatus = tmbslFrontEndStateUnknown;
        }
    }

    _MUTEX_RELEASE(TDA182I4)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA182I4_GetAgcStatus:                                   */
/*                                                                            */
/* DESCRIPTION: Gets AGC Status. (Lock and/or set to Max)                     */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA182I4_GetAgcStatus(
    tmUnitSelect_t          tUnit,       /* I: Unit number */
    Bool*                   pbAgcLock,   /* O: AGC Lock status */
    Bool*                   pbAgcMax     /* O: AGC Max status */
)
{
    pTDA182I4Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;
    UInt8               uAgcMax = 0, uAgcLock = 0;

    /* Get a driver instance */
    err = iTDA182I4_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA182I4)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA182I4_GetAgcStatus(0x%08X)", tUnit);

    if( (pbAgcLock == Null) || (pbAgcMax == Null) )
    {
        err = TDA182I4_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_Power_state_byte_1__AGCs_Max, &uAgcMax, Bus_RW);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Read(0x%08X) failed.", pObj->tUnitW));

        if(err == TM_OK)
        {
            err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_Power_state_byte_1__AGCs_Lock, &uAgcLock, Bus_None);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Read(0x%08X) failed.", pObj->tUnitW));
        }

        if(err == TM_OK)
        {
            *pbAgcMax =  (uAgcMax)? True : False;
            *pbAgcLock =  (uAgcLock)? True : False;
        }
        else
        {
            *pbAgcMax = *pbAgcLock = False;
        }
    }

    _MUTEX_RELEASE(TDA182I4)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA182I4_GetPowerLevel:                                  */
/*                                                                            */
/* DESCRIPTION: Gets HW Power Level.   1/2 steps dBµV                         */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA182I4_GetPowerLevel
(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    UInt8*          pPowerLevel /* O: Power Level in 1/2 steps dBµV */
)
{
    pTDA182I4Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;
    UInt8 index = 0;
    Int16 PldErr = 0;
    Int16 PldErrRound = 0;
    UInt16  uProgRF = 0; /* Mhz * 10 */
    UInt16 uRfAgc = 0;
    UInt8 uAGC1 = 0;

    /* Get a driver instance */
    err = iTDA182I4_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA182I4)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA182I4_GetPowerLevel(0x%08X)", tUnit);

    /* Test parameter(s) */
    if( pPowerLevel == Null ||
        pObj->StandardMode<=TDA182I4_StandardMode_Unknown ||
        pObj->StandardMode>=TDA182I4_StandardMode_Max ||
        pObj->pStandard == Null)
    {
        err = TDA182I4_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        *pPowerLevel = 0;

        /* Read Power Level */
        err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_Power_Level_byte_1__Power_Level_, pPowerLevel, Bus_RW);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Read(0x%08X) failed.", tUnit));
    }
    if (err == TM_OK)
    {  
        uProgRF = (UInt16) (pObj->uProgRF / 100000); /* from Hz to Mhz*10 */
        index = PldRfCorrection_length;
        /* retreive correction fct( RF) */
        do {
            index = index -1;
        } while ( uProgRF < PldRFCorrection[index].Freq ) ;
        PldErr = PldRFCorrection[index].Correction;
    }
    if (err == TM_OK)
    {  
        /* retreive correction fct( RfAgc, AGC1) */
        err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_RFAGCs_Gain_byte_5__RFAGC_Read_K_8, &index, Bus_RW);
        uRfAgc = uRfAgc + ( index << 8);
    }
    if (err == TM_OK)
    {  
        err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_RFAGCs_Gain_byte_6__RFAGC_Read_K, &index, Bus_RW);
        uRfAgc = uRfAgc + index;
    }
    if (err == TM_OK)
    {  
        err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_RFAGCs_Gain_byte_3__AGC1_Gain_Read, &uAGC1, Bus_RW);
    }

    if (err == TM_OK)
    {  
        index = PldRfAgcCorrection_length;
        do {
            index = index -1;
        } while ( uRfAgc < PldRfAgcCorrection[index].RfAgc ) ;
        PldErr = PldErr + ( uAGC1 == 11 ? PldRfAgcCorrection[index].Correction_22: PldRfAgcCorrection[index].Correction_no22 ) ; 
    }

    /* -0.3 dB offset correction due to modulation */
    PldErr = PldErr - 6;

    /* from PldErr in 1/2 step *10  convert and round to 1/2 step */
    PldErrRound =  PldErr / 10;
    if (PldErr > 0)
    {
        PldErrRound = ((PldErr - (PldErrRound * 10) > 5) ? PldErrRound +1 : PldErrRound) ;
    }
    else
    {
        PldErrRound = (((PldErrRound * 10) - PldErr  > 5) ? PldErrRound -1 : PldErrRound) ;
    }

    *pPowerLevel = *pPowerLevel - (Int8) PldErrRound;

    _MUTEX_RELEASE(TDA182I4)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA182I4_SetInternalVsync:                               */
/*                                                                            */
/* DESCRIPTION: Enables or disable the internal VSYNC                         */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA182I4_SetInternalVsync(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    Bool            bEnabled    /* I: Enable of disable the internal VSYNC */
)
{
    pTDA182I4Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA182I4_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA182I4)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA182I4_SetInternalVsync(0x%08X)", tUnit);

    if(err == TM_OK)
    {
        err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Vsync_byte__vsync_Int, ((bEnabled == True) ? 1 : 0), Bus_RW);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", tUnit));
    }

    _MUTEX_RELEASE(TDA182I4)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA182I4_GetInternalVsync:                               */
/*                                                                            */
/* DESCRIPTION: Get the current status of the internal VSYNC                  */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA182I4_GetInternalVsync(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    Bool*           pbEnabled   /* O: current status of the internal VSYNC */
)
{
    pTDA182I4Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;
    UInt8               uValue;

    /* Get a driver instance */
    err = iTDA182I4_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA182I4)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA182I4_SetInternalVsync(0x%08X)", tUnit);

    if(pbEnabled == Null)
    {
        err = TDA182I4_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_Vsync_byte__vsync_Int, &uValue, Bus_RW);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Read(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        if (uValue == 1)
        {
            *pbEnabled = True;
        }
        else
        {
            *pbEnabled = False;
        }
    }

    _MUTEX_RELEASE(TDA182I4)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA182I4_SetPllManual:                                   */
/*                                                                            */
/* DESCRIPTION: Sets bOverridePLL flag.                                       */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA182I4_SetPllManual(
    tmUnitSelect_t  tUnit,         /* I: Unit number */
    Bool            bOverridePLL   /* I: Determine if we need to put PLL in manual mode in SetRF */
)
{
    pTDA182I4Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA182I4_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA182I4)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA182I4_SetPllManual(0x%08X)", tUnit);

    pObj->bOverridePLL = bOverridePLL;

    _MUTEX_RELEASE(TDA182I4)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA182I4_GetPllManual:                                   */
/*                                                                            */
/* DESCRIPTION: Gets bOverridePLL flag.                                       */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA182I4_GetPllManual(
    tmUnitSelect_t  tUnit,         /* I: Unit number */
    Bool*           pbOverridePLL  /* O: Determine if we need to put PLL in manual mode in SetRF */
)
{
    pTDA182I4Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA182I4_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA182I4)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA182I4_GetPllManual(0x%08X)", tUnit);

    if(pbOverridePLL == Null)
    {
        err = TDA182I4_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        *pbOverridePLL = pObj->bOverridePLL;
    }

    _MUTEX_RELEASE(TDA182I4)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA182I4_GetIRQ:                                         */
/*                                                                            */
/* DESCRIPTION: Gets IRQ status.                                              */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA182I4_GetIRQ(
    tmUnitSelect_t  tUnit   /* I: Unit number */,
    Bool*           pbIRQ   /* O: IRQ triggered */
)
{
    pTDA182I4Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;
    UInt8               uValue = 0;

    /* Get a driver instance */
    err = iTDA182I4_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA182I4)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA182I4_GetIRQ(0x%08X)", tUnit);

    if(pbIRQ == Null)
    {
        err = TDA182I4_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        *pbIRQ = 0;

        err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_IRQ_status__IRQ_status, &uValue, Bus_RW);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Read(0x%08X) failed.", pObj->tUnitW));

        if(err == TM_OK)
        {
            *pbIRQ = uValue;
        }
    }

    _MUTEX_RELEASE(TDA182I4)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA182I4_WaitIRQ:                                        */
/*                                                                            */
/* DESCRIPTION: Waits for the IRQ to raise.                                   */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA182I4_WaitIRQ(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    UInt32          timeOut,    /* I: timeOut for IRQ wait */
    UInt32          waitStep,   /* I: wait step */
    UInt8           irqStatus   /* I: IRQs to wait */
)
{
    pTDA182I4Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA182I4_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA182I4)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA182I4_WaitIRQ(0x%08X)", tUnit);

    err = iTDA182I4_WaitIRQ(pObj, timeOut, waitStep, irqStatus);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_WaitIRQ(0x%08X) failed.", tUnit));

    _MUTEX_RELEASE(TDA182I4)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA182I4_GetXtalCal_End:                                 */
/*                                                                            */
/* DESCRIPTION: Gets XtalCal_End status.                                      */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA182I4_GetXtalCal_End(
    tmUnitSelect_t  tUnit           /* I: Unit number */,
    Bool*           pbXtalCal_End   /* O: XtalCal_End triggered */
)
{
    pTDA182I4Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;
    UInt8               uValue = 0;

    /* Get a driver instance */
    err = iTDA182I4_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA182I4)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA182I4_GetXtalCal_End(0x%08X)", tUnit);

    if(pbXtalCal_End == Null)
    {
        err = TDA182I4_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        *pbXtalCal_End = 0;

        err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_IRQ_status__XtalCal_End, &uValue, Bus_RW);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Read(0x%08X) failed.", pObj->tUnitW));

        if(err == TM_OK)
        {
            *pbXtalCal_End = uValue;
        }
    }

    _MUTEX_RELEASE(TDA182I4)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA182I4_SetFineRF:                                      */
/*                                                                            */
/* DESCRIPTION: Fine tunes RF with given step.                                */
/*              (tmbslTDA182I4_SetRF must be called before calling this API)  */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA182I4_SetFineRF(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    Int8            step    /* I: step (-1, +1) */
)
{
    pTDA182I4Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* LO wanted = RF wanted + IF in KHz */
    UInt32 LO = 0;

    /* PostDiv */
    UInt8 PostDiv = 0;
    UInt8 LOPostDiv = 0;

    /* Prescaler */
    UInt8 Prescaler = 0;

    /* Algorithm that calculates N, K */
    UInt32 N_int = 0;
    UInt32 K_int = 0;

    UInt8 i = 0;

    /* Get a driver instance */
    err = iTDA182I4_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA182I4)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA182I4_SetFineRF(0x%08X)", tUnit);

    /* Test parameter(s) */
    if(   pObj->StandardMode<=TDA182I4_StandardMode_Unknown
        || pObj->StandardMode>=TDA182I4_StandardMode_Max
        || pObj->pStandard == Null)
    {
        err = TDA182I4_ERR_STD_NOT_SET;
    }

    if(err == TM_OK)
    {
        /* Check if Hw is ready to operate */
        err = iTDA182I4_CheckHwState(pObj, TDA182I4_HwStateCaller_SetFineRF);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_CheckHwState(0x%08X) failed.", pObj->tUnitW));
    }

    if(err == TM_OK)
    {
        /* Write the offset into 4 equal steps of 15.625 KHz = 62.5 KHz*/
        for (i=0; i < 4; i++)
        {
            /* Calculate wanted LO = RF + IF */
            pObj->uRF += step*15625;
            pObj->uProgRF += step*15625;
            LO = (pObj->uRF + pObj->pStandard->IF)/1000;

            /* Don't touch on Prescaler and PostDiv programmed during setRF */
            err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_Main_Post_Divider_byte__LOPostDiv, &LOPostDiv, Bus_RW);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Read(0x%08X) failed.", pObj->tUnitW));

            if(err == TM_OK)
            {
                err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_Main_Post_Divider_byte__LOPresc, &Prescaler, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Read(0x%08X) failed.", pObj->tUnitW));
            }

            if (err == TM_OK)
            {
                /* Decode PostDiv */
                switch(LOPostDiv)
                {
                    case 1:
                        PostDiv = 1;
                        break;
                    case 2:
                        PostDiv = 2;
                        break;
                    case 3:
                        PostDiv = 4;
                        break;
                    case 4:
                        PostDiv = 8;
                        break;
                    case 5:
                        PostDiv = 16;
                        break;
                    default:
                        err = TDA182I4_ERR_BAD_PARAMETER;
                        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA182I4_SetFineRF(0x%08X) LO_PostDiv value is wrong.", tUnit));
                        break;
                }

                /* Calculate N & K values of the PLL */
                err = iTDA182I4_CalculateNIntKInt(LO, PostDiv, Prescaler, &N_int, &K_int);

                /* Affect registers */
                if(err == TM_OK)
                {
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Sigma_delta_byte_4__LO_Frac_0, (UInt8)(K_int & 0xFF), Bus_None);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
                }

                if(err == TM_OK)
                {
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Sigma_delta_byte_3__LO_Frac_1, (UInt8)((K_int >> 8) & 0xFF), Bus_None);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
                }

                if(err == TM_OK)
                {
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Sigma_delta_byte_2__LO_Frac_2, (UInt8)((K_int >> 16) & 0xFF), Bus_None);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
                }

                if(err == TM_OK)
                {
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Sigma_delta_byte_1__LO_Int, (UInt8)(N_int & 0xFF), Bus_None);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
                }

                if(err == TM_OK)
                {
                    /* Force manual selection mode : 0x7 at @0x56 */
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Sigma_delta_byte_5__N_K_correct_manual, 0x01, Bus_None);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));

                    if(err == TM_OK)
                    {
                        /* Force manual selection mode : 0x7 at @0x56 */
                        err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Sigma_delta_byte_5__LO_Calc_Disable, 0x01, Bus_None);
                        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
                    }
                }

                /* Set the new PLL values */
                if(err == TM_OK)
                {
                    /* Write bytes Sigma_delta_byte_1 (0x52) to Sigma_delta_byte_5 (0x56) */
                    err = iTDA182I4_WriteRegMap(pObj, gTDA182I4_Reg_Sigma_delta_byte_1.Address, TDA182I4_REG_DATA_LEN(gTDA182I4_Reg_Sigma_delta_byte_1, gTDA182I4_Reg_Sigma_delta_byte_5));
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
                }
            }
        }

        /* Update driver state machine */
        pObj->eHwState = TDA182I4_HwState_SetFineRFDone;
    }

    _MUTEX_RELEASE(TDA182I4)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA182I4_Write                                           */
/*                                                                            */
/* DESCRIPTION: Writes in TDA182I4 hardware                                   */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA182I4_Write(
    tmUnitSelect_t              tUnit,      /* I: Unit number */
    const TDA182I4_BitField_t*  pBitField,  /* I: Bitfield structure */
    UInt8                       uData,      /* I: Data to write */
    tmbslFrontEndBusAccess_t                eBusAccess  /* I: Access to bus */
)
{
    pTDA182I4Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA182I4_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA182I4)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA182I4_Write(0x%08X)", tUnit);

    err = iTDA182I4_Write(pObj, pBitField, uData, eBusAccess);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));

    _MUTEX_RELEASE(TDA182I4)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA182I4_Read                                            */
/*                                                                            */
/* DESCRIPTION: Reads in TDA182I4 hardware                                    */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA182I4_Read(
    tmUnitSelect_t              tUnit,      /* I: Unit number */
    const TDA182I4_BitField_t*  pBitField,  /* I: Bitfield structure */
    UInt8*                      puData,     /* I: Data to read */
    tmbslFrontEndBusAccess_t                eBusAccess  /* I: Access to bus */
)
{
    pTDA182I4Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA182I4_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA182I4)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA182I4_Read(0x%08X)", tUnit);

    err = iTDA182I4_Read(pObj, pBitField, puData, eBusAccess);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Read(0x%08X) failed.", pObj->tUnitW));

    _MUTEX_RELEASE(TDA182I4)

    return err;
}
/*============================================================================*/
/* FUNCTION:    tmbslTDA182I4_SetFEF                                          */
/*                                                                            */
/* DESCRIPTION: Activate/desactive FEF settings DVB-T2 in                     */  
/*                       tmbslTDA182I4_SetStandard() API                      */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA182I4_SetFEF(
    tmUnitSelect_t              tUnit,      /* I: Unit number */
    Bool bFefEnable                         /* Activate/desactivate FEF settings for DVB-T/T2 */
)
{
    pTDA182I4Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA182I4_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA182I4)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA182I4_SetFEF(0x%08X)", tUnit);

    pObj->bFefEnable = bFefEnable;

    _MUTEX_RELEASE(TDA182I4)

    return err;
}
/*============================================================================*/
/* FUNCTION:    tmbslTDA182I4_GetFEF                                          */
/*                                                                            */
/* DESCRIPTION: get status Activate/desactive FEF settings DVB-T2 in          */  
/*                       tmbslTDA182I4_SetStandard() API                      */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA182I4_GetFEF(
    tmUnitSelect_t              tUnit,      /* I: Unit number */
    Bool* bFefEnable                        /* get FEF settings for DVB-T/T2 status*/
)
{
    pTDA182I4Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA182I4_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA182I4)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA182I4_GetFEF(0x%08X)", tUnit);

    *bFefEnable = pObj->bFefEnable;

    _MUTEX_RELEASE(TDA182I4)

    return err;
}
/*============================================================================*/
/* Internal functions:                                                        */
/*============================================================================*/

/*============================================================================*/
/* FUNCTION:    iTDA182I4_CheckHwState                                        */
/*                                                                            */
/* DESCRIPTION: Checks if Hw is ready to operate.                             */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
iTDA182I4_CheckHwState(
    pTDA182I4Object_t       pObj,   /* I: Driver object */
    TDA182I4HwStateCaller_t caller  /* I: Caller API */
)
{
    tmErrorCode_t   err = TM_OK;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA182I4_CheckHwState(0x%08X)", pObj->tUnitW);

    switch(pObj->eHwState)
    {
        case TDA182I4_HwState_InitNotDone:
            switch(caller)
            {
                case TDA182I4_HwStateCaller_SetPower:
                    break;

                default:
                    err = TDA182I4_ERR_NOT_INITIALIZED;
                    break;
            }
            break;

        case TDA182I4_HwState_InitDone:
            switch(caller)
            {
                case TDA182I4_HwStateCaller_SetRF:
                case TDA182I4_HwStateCaller_SetFineRF:
                    /* SetStandardMode API must be called before calling SetRF and SetFineRF */
                    err = TDA182I4_ERR_STD_NOT_SET;
                    break;

                default:
                    break;
            }
            break;

        case TDA182I4_HwState_SetStdDone:
            switch(caller)
            {
                case TDA182I4_HwStateCaller_SetFineRF:
                    /* SetRF API must be called before calling SetFineRF */
                    err = TDA182I4_ERR_RF_NOT_SET;
                    break;

                default:
                    break;
            }
            break;

        case TDA182I4_HwState_SetRFDone:
        case TDA182I4_HwState_SetFineRFDone:
            break;

        case TDA182I4_HwState_InitPending:
            err = TDA182I4_ERR_NOT_READY;
            break;            
        default:
            err = TDA182I4_ERR_NOT_READY;
            break;
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA182I4_CheckCalcPLL                                        */
/*                                                                            */
/* DESCRIPTION: Checks if CalcPLL Algo is enabled. Enable it if not.          */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
iTDA182I4_CheckCalcPLL(
    pTDA182I4Object_t   pObj    /* I: Driver object */
)
{
    tmErrorCode_t   err = TM_OK;
    UInt8           uValue = 0;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA182I4_CheckCalcPLL(0x%08X)", pObj->tUnitW);

    /* Check if Calc_PLL algorithm is in automatic mode */
    err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_Sigma_delta_byte_5__LO_Calc_Disable, &uValue, Bus_None);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Read(0x%08X) failed.", pObj->tUnitW));

    if(err == TM_OK && uValue != 0x00)
    {
        /* Enable Calc_PLL algorithm by putting PLL in automatic mode */
        err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Sigma_delta_byte_5__N_K_correct_manual, 0x00, Bus_None);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));

        if(err == TM_OK)
        {
            err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Sigma_delta_byte_5__LO_Calc_Disable, 0x00, Bus_NoRead);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
        }
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA182I4_SetLLPowerState                                     */
/*                                                                            */
/* DESCRIPTION: Sets the power state.                                         */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
static tmErrorCode_t
iTDA182I4_SetLLPowerState(
    pTDA182I4Object_t       pObj,       /* I: Driver object */
    TDA182I4PowerState_t    powerState  /* I: Power state of TDA182I4 */
)
{
    tmErrorCode_t   err = TM_OK;
    UInt8           uValue = 0;
    UInt8           counter =0;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA182I4_SetLLPowerState(0x%08X)", pObj->tUnitW);

    if(err == TM_OK)
    {
        /* Check if Hw is ready to operate */
        err = iTDA182I4_CheckHwState(pObj, TDA182I4_HwStateCaller_SetPower);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_CheckHwState(0x%08X) failed.", pObj->tUnitW));
    }

    if(err == TM_OK)
    {
        switch(powerState)
        {
            case TDA182I4_PowerNormalMode:
                if(err == TM_OK)
                {
                    /*LT_smooth_t_cst  ->  6 */
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_LT_byte_2__LT_smooth_t_cst, 0x06, Bus_None);
                    /*LT_smooth_t__fast  -> 1 */
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_LT_byte_2__LT_smooth_t_cst_fast, 0x01, Bus_NoRead);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
                }
	            if(err == TM_OK)
                {
		            /* AGC1_smooth_t_cst  ->  6   */
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_4__AGC1_smooth_t_cst, 0x06, Bus_None);
		            /* AGC1_smooth_t_cst_fast -> 1  */
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_4__AGC1_smooth_t_cst_fast, 0x01, Bus_NoRead);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
                }
				if(err == TM_OK)
				{
					err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Power_state_byte_2__power_state_mode, powerState, Bus_NoRead);
					tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
				}
                if(err == TM_OK)
				{
					err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_AGC1_byte_1__PD_LNA, &uValue, Bus_None);
                    if (uValue==1)
                    {
                        err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_1__PD_LNA, 0x00, Bus_NoRead); 
					    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
                    }
                }
                if (pObj->TunerModeInUse & TDA182I4_Mode_STO_Used )
                {
				    if(err == TM_OK)
				    {
                        err = iTDA182I4_Wait(pObj, 100);
                    }
				    if(err == TM_OK)
				    {
					    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Power_Down_byte_1__PD_VCO, 0x00, Bus_NoRead);
					    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
				    }
				    if(err == TM_OK)
				    {
                        err = iTDA182I4_Wait(pObj, 100);
                    }
				    if(err == TM_OK)
				    {
					    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Power_Down_byte_1__PD_Synthe, 0x00, Bus_NoRead);
					    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
				    }
					if(err == TM_OK)
				    {
                        err = iTDA182I4_Wait(pObj, 100);
                    }
					if(err == TM_OK)
				    {
					    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Power_Down_byte_2__PDRF_filter, 0x00, Bus_NoRead);
					    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
				    }
					if(err == TM_OK)
				    {
                        err = iTDA182I4_Wait(pObj, 100);
                    }
					if(err == TM_OK)
				    {
					    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Power_Down_byte_2__PD_STOB_IF, 0x00, Bus_NoRead);
					    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
				    }
				    if(err == TM_OK)
				    {
                        err = iTDA182I4_Wait(pObj, 100);
                    }
                }
                if(err == TM_OK)
                {
                    /* Set digital clock mode to sub-LO if normal mode is entered */
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Reference_Byte__Dig_Clock, 0x03, Bus_NoRead);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
                }
				if(err == TM_OK)
				{
					err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_2__AGC1_FastStbyLT_Enable, 0x00, Bus_NoRead);
					tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
				}

				break;				
			case TDA182I4_PowerStandbyWithXtalOn:
			case TDA182I4_PowerStandbyWithPllOnWithXtalOn:
				if(err == TM_OK)
				{
                    /* AGC1_smooth_t_cst  ->  0   */
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_4__AGC1_smooth_t_cst, 0x00, Bus_None);
		            /* AGC1_smooth_t_cst_fast -> 0  */
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_4__AGC1_smooth_t_cst_fast, 0x00, Bus_NoRead);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
                }
				if(err == TM_OK)
				{
		            /* LT_smooth_t_cst  ->  0   */
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_LT_byte_2__LT_smooth_t_cst, 0x00, Bus_None);
		            /* LT_smooth_t_cst_fast -> 0  */
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_LT_byte_2__LT_smooth_t_cst_fast, 0x00, Bus_NoRead);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
                }
				if(err == TM_OK)
				{
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_3__AGC1_loop_off, 0x01, Bus_NoRead);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
                }
                counter = 10;
                while(counter > 0)
                {
                    err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_AGC1_Top_byte__AGC1_Smooth_Transition_ON, &uValue, Bus_RW);
					tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Read(0x%08X) failed.", pObj->tUnitW));
                    if(err == TM_OK)
                    {
                        if (uValue==0) break;
                    }
				    if(err == TM_OK)
				    {
                        err = iTDA182I4_Wait(pObj, 10);
                    }
                    counter  = counter -1;
                }
				if(err == TM_OK)
				{
                    /* remove Glitch Antenna leakage : Force LNA to -11dB before PD_LNA acitvation*/
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_3__AGC1_Gain, 0x00, Bus_None); /* -11dB */
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_3__Force_AGC1_gain, 0x01, Bus_NoRead); /* Force LNA */
					tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
				}
				if(err == TM_OK)
				{
				    /* Set digital clock mode to 16 Mhz before entering standby */
				    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Reference_Byte__Dig_Clock, 0x02, Bus_NoRead);
				    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
                }
                if(err == TM_OK)
				{
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_1__PD_LNA, 0x01, Bus_NoRead); /* power off  LNA */
					tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));                    
                }
				if(err == TM_OK)
				{
					err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Power_state_byte_2__power_state_mode, powerState, Bus_NoRead);
					tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
				}
				if(err == TM_OK) /* AGC1 gain init to improve antenna leakage */
				{   /* save LNA_gain range */
					err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_AGC1_byte_2__LNA_Range, &uValue, Bus_None);
					tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
                }
				if(err == TM_OK)
				{
					/* write dummy value 3 */
					err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_2__LNA_Range, 0x03, Bus_None);
					tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));

                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_2__AGC1_FastStbyLT_Enable, 0x01, Bus_NoRead);
					tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
                }
				if(err == TM_OK)
				{   /* restore LNA_gain range */
					err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_2__LNA_Range, uValue, Bus_NoRead);
					tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
				}
				if(err == TM_OK)
				{
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_3__AGC1_loop_off, 0x00, Bus_None);
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_3__Force_AGC1_gain, 0x00, Bus_NoRead); /* Free LNA */
					tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
				}
				if(err == TM_OK)
				{
					err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_Power_Down_byte_1__PD_VCO, &uValue, Bus_None);
                    if (uValue==1)
                    {
					    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Power_Down_byte_1__PD_VCO, 0x00, Bus_None);
					    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Power_Down_byte_1__PD_Synthe, 0x00, Bus_NoRead);
					    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
                    }
                }

                break;
			case TDA182I4_PowerStandbyWithLtOnWithXtalOn:
                if(err == TM_OK)
                {
                    /*LT_smooth_t_cst  ->  6 */
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_LT_byte_2__LT_smooth_t_cst, 0x06, Bus_None);
                    /*LT_smooth_t__fast  -> 1 */
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_LT_byte_2__LT_smooth_t_cst_fast, 0x01, Bus_NoRead);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
                }
	            if(err == TM_OK)
                {
		            /* AGC1_smooth_t_cst  ->  6   */
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_4__AGC1_smooth_t_cst, 0x06, Bus_None);
		            /* AGC1_smooth_t_cst_fast -> 1  */
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_4__AGC1_smooth_t_cst_fast, 0x01, Bus_NoRead);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
                }
				if(err == TM_OK)
				{
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_3__Force_AGC1_gain, 0x00, Bus_NoRead); /* Free LNA */
					tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
				}
                if (pObj->TunerModeInUse & TDA182I4_Mode_STO_Used )
                {
				    if(err == TM_OK)
				    {
					    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Power_Down_byte_2__PD_STOB_IF, 0x01, Bus_NoRead);
					    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
				    }
				    if(err == TM_OK)
				    {
                        err = iTDA182I4_Wait(pObj, 100);
                    }
				    if(err == TM_OK)
				    {
					    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Power_Down_byte_2__PDRF_filter, 0x01, Bus_NoRead);
					    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
				    }
				    if(err == TM_OK)
				    {
                        err = iTDA182I4_Wait(pObj, 100);
                    }
                }
				if(err == TM_OK)
				{
				    /* Set digital clock mode to 16 Mhz before entering standby */
				    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Reference_Byte__Dig_Clock, 0x02, Bus_RW);
				    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
                }
                if (pObj->TunerModeInUse & TDA182I4_Mode_STO_Used )
                {
				    if(err == TM_OK)
				    {
                        err = iTDA182I4_Wait(pObj, 100);
                    }
				    if(err == TM_OK)
				    {
					    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Power_Down_byte_1__PD_VCO, 0x01, Bus_NoRead);
					    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
				    }
				    if(err == TM_OK)
				    {
                        err = iTDA182I4_Wait(pObj, 100);
                    }
				    if(err == TM_OK)
				    {
					    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Power_Down_byte_1__PD_Synthe, 0x01, Bus_NoRead);
					    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
				    }
				    if(err == TM_OK)
				    {
                        err = iTDA182I4_Wait(pObj, 100);
                    }
                }
				if(err == TM_OK)
				{
					err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Power_state_byte_2__power_state_mode, powerState, Bus_RW);
					tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
				}
				if(err == TM_OK)
				{
					err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_2__AGC1_FastStbyLT_Enable, 0x00, Bus_RW);
					tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
				}
                if(err == TM_OK)
				{
					err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_AGC1_byte_1__PD_LNA, &uValue, Bus_None);
                    if (uValue==1)
                    {
                        err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_1__PD_LNA, 0x00, Bus_NoRead); /* power on  LNA */
					    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
                    }
                }
                break;
			case TDA182I4_PowerStandbyWithLtOnWithPllOnWithXtalOn:
                if(err == TM_OK)
                {
                    /*LT_smooth_t_cst  ->  6 */
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_LT_byte_2__LT_smooth_t_cst, 0x06, Bus_None);
                    /*LT_smooth_t__fast  -> 1 */
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_LT_byte_2__LT_smooth_t_cst_fast, 0x01, Bus_NoRead);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
                }
	            if(err == TM_OK)
                {
		            /* AGC1_smooth_t_cst  ->  6   */
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_4__AGC1_smooth_t_cst, 0x06, Bus_None);
		            /* AGC1_smooth_t_cst_fast -> 1  */
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_4__AGC1_smooth_t_cst_fast, 0x01, Bus_NoRead);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
                }
				if(err == TM_OK)
				{
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_3__Force_AGC1_gain, 0x00, Bus_NoRead); /* Free LNA */
					tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
				}
                if (pObj->TunerModeInUse & TDA182I4_Mode_STO_Used )
                {
                    if(err == TM_OK)
				    {
					    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Power_Down_byte_2__PD_STOB_IF, 0x01, Bus_NoRead);
					    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
				    }
				    if(err == TM_OK)
				    {
                        err = iTDA182I4_Wait(pObj, 100);
                    }
				    if(err == TM_OK)
				    {
					    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Power_Down_byte_2__PDRF_filter, 0x01, Bus_NoRead);
					    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
				    }
				    if(err == TM_OK)
				    {
                        err = iTDA182I4_Wait(pObj, 100);
                    }
				    if(err == TM_OK)
				    {
				        /* Set digital clock mode to 16 Mhz before entering standby */
				        err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Reference_Byte__Dig_Clock, 0x02, Bus_NoRead);
				        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
                    }
				    if(err == TM_OK)
				    {
                        err = iTDA182I4_Wait(pObj, 100);
                    }
				    if(err == TM_OK)
				    {
					    err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_Power_Down_byte_1__PD_VCO, &uValue, Bus_None);
                        if (uValue==1)
                        {
					        err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Power_Down_byte_1__PD_VCO, 0x00, Bus_None);
					        err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Power_Down_byte_1__PD_Synthe, 0x00, Bus_NoRead);
					        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
                        }
                    }
                }
                else
                {
				    if(err == TM_OK)
				    {
				        /* Set digital clock mode to 16 Mhz before entering standby */
				        err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Reference_Byte__Dig_Clock, 0x02, Bus_NoRead);
				        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
                    }
                }
				if(err == TM_OK)
				{
					err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Power_state_byte_2__power_state_mode, powerState, Bus_NoRead);
					tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
				}
				if(err == TM_OK)
				{
					err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_2__AGC1_FastStbyLT_Enable, 0x00, Bus_NoRead);
					tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
				}
                if(err == TM_OK)
				{
					err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_AGC1_byte_1__PD_LNA, &uValue, Bus_None);
                    if (uValue==1)
                    {
                        err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_1__PD_LNA, 0x00, Bus_NoRead); /* power on  LNA */
					    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
                    }
                }
                break;


            default:
				err = TM_ERR_BAD_PARAMETER;
                break;
        }

        if(err == TM_OK)
        {
            /* Store low-level power state in driver instance */
            pObj->curLLPowerState = powerState;
        }
    }

    return err;
}


/*============================================================================*/
/* FUNCTION:    iTDA182I4_SetRF:                                              */
/*                                                                            */
/* DESCRIPTION: Tunes to a RF.                                                */
/*                                                                            */
/* RETURN:      TM_OK                                                         */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
iTDA182I4_SetRF(
    pTDA182I4Object_t   pObj    /* I: Driver object */
)
{
    tmErrorCode_t   err = TM_OK;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA182I4_SetRF(0x%08X)", pObj->tUnitW);

    if(pObj->curPowerState != tmPowerOn)
    {
        /* Set power state ON */
        err = iTDA182I4_SetLLPowerState(pObj, TDA182I4_PowerNormalMode);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_SetLLPowerState(0x%08X, PowerNormalMode) failed.", pObj->tUnitW));
    }

    if(err == TM_OK)
    {
        pObj->curPowerState = tmPowerOn;

        /* Setting Bandsplit parameters */
        err = iTDA182I4_OverrideBandsplit(pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_OverrideBandsplit(0x%08X) failed.", pObj->tUnitW));
    }

    if ((pObj->bCenelecMargin) &&
	/******************************/
	/* Optimization of CENELEC    */
	/******************************/
	/* Check if we are set in one of the analog standards */
	(
		(pObj->StandardMode == TDA182I4_ANLG_MN) ||
		(pObj->StandardMode == TDA182I4_ANLG_B) ||
		(pObj->StandardMode == TDA182I4_ANLG_GH) ||
		(pObj->StandardMode == TDA182I4_ANLG_I) ||
		(pObj->StandardMode == TDA182I4_ANLG_DK) ||
		(pObj->StandardMode == TDA182I4_ANLG_L) ||
		(pObj->StandardMode == TDA182I4_ANLG_LL)	   
	   ))
	{
	    /* Set AGC3 RF AGC Top */
	    if(err == TM_OK)
	    {
		    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_RF_AGC_byte_1__RFAGC_Top, TDA182I4_AGC3_TOP_I2C_96dBuV, Bus_None);
		    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
	    }

	    /* Set AGC3 Adapt TOP to step_0 */
	    if(err == TM_OK)
	    {
		    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_RF_AGC_byte_1__RFAGC_Adapt_TOP, TDA182I4_AGC3_Adapt_TOP_0_Step, Bus_None);
		    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
	    }
	    if(err == TM_OK)
	    {
            if (pObj->uRF <= 480768000)
            {
	            /* Set AGC1_Top_Strategy */
	            err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_1__AGC1_Top_Strategy, TDA182I4_AGC1_TOP_STRATEGY_1, Bus_None);
	            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));

	            /* Set AGC1 TOP I2C DN/UP */
	            if(err == TM_OK)
	            {
		            err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_1__AGC1_Top, TDA182I4_AGC1_TOP_I2C_DN_UP_d95_u89dBuV, Bus_NoRead);
		            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
	            }
            }
	        else if (pObj->uRF <= 866000000)
	        {
		        /* Set AGC1_Top_Strategy */
		        err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_1__AGC1_Top_Strategy, TDA182I4_AGC1_TOP_STRATEGY_2, Bus_None);
		        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));

		        /* Set AGC1 TOP I2C DN/UP */
		        if(err == TM_OK)
		        {
			        err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_1__AGC1_Top, TDA182I4_AGC1_TOP_I2C_DN_UP_d90_u84wdBuV, Bus_NoRead);
			        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
		        }
            }
        }
	}

	/******************************/
	/* End                        */
	/******************************/

    if(err == TM_OK)
    {
        /* Set RF frequency */
        err = iTDA182I4_SetRF_Freq(pObj, pObj->uProgRF);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_SetRF_Freq(0x%08X) failed.", pObj->tUnitW));
    }

    /* Bypass ROM settings for wireless filters */
    if(err == TM_OK)
    {
        err = iTDA182I4_OverrideWireless(pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_OverrideWireless(0x%08X) failed.", pObj->tUnitW));
    }

	if ((pObj->bHalfRfImmunity) &&
	/******************************/
	/* Optimization of 1/2 & 2 RF */
	/******************************/
	/* Check if we are set in one of the analog standards */
	(
        (pObj->StandardMode == TDA182I4_ANLG_MN) ||
        (pObj->StandardMode == TDA182I4_ANLG_B) ||
        (pObj->StandardMode == TDA182I4_ANLG_GH) ||
        (pObj->StandardMode == TDA182I4_ANLG_I) ||
        (pObj->StandardMode == TDA182I4_ANLG_DK) ||
        (pObj->StandardMode == TDA182I4_ANLG_L) ||
        (pObj->StandardMode == TDA182I4_ANLG_LL)	   
       ))
	{
		/* Wait for 300ms so that AGCs are well settled */
		err = iTDA182I4_Wait(pObj,300); /* 200 fast AGC1 + 100 AGC3 convergence */
		tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Wait(0x%08X) failed.", pObj->tUnitW));

		if(err == TM_OK)
		{	
			UInt8 agc1GainRead; 
			UInt16 agc3GainRead;

			/* Read AGC1 & AGC3 gain */
			err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_RFAGCs_Gain_byte_3__AGC1_Gain_Read, &agc1GainRead, Bus_NoWrite);
			tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Read(0x%08X) failed.", pObj->tUnitW));

			if(err == TM_OK)
			{
				UInt8 uValue1, uValue2;

				err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_RFAGCs_Gain_byte_5__RFAGC_Read_K_8, &uValue1, Bus_NoWrite);
				tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Read(0x%08X) failed.", pObj->tUnitW));

				if(err == TM_OK)
				{
					err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_RFAGCs_Gain_byte_6__RFAGC_Read_K, &uValue2, Bus_NoWrite);
					tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Read(0x%08X) failed.", pObj->tUnitW));

					if(err == TM_OK)
					{
						agc3GainRead = ((uValue1 << 8) & 0xFF00) | uValue2;
					}
				}
			}	

			if(err == TM_OK)
			{
				if (
					/* AGC3 Gain max */
					(agc3GainRead >= 170) &&
					/* AGC1 Gain below 13dB */
					(agc1GainRead <= 8)
				   )
				{
					/* Set AGC1 TOP to 85/79 */
					err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_AGC1_byte_1__AGC1_Top, TDA182I4_AGC1_TOP_I2C_DN_UP_d85_u79dBuV, Bus_RW);
					tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
				}
			}
		}
    }

	/******************************/
	/* End                        */
	/******************************/

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA182I4_SetRF_Freq                                          */
/*                                                                            */
/* DESCRIPTION: Sets Tuner Frequency registers.                               */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
iTDA182I4_SetRF_Freq(
    pTDA182I4Object_t   pObj,   /* I: Driver object */
    UInt32              uRF     /* I: Wanted frequency */
)
{
    tmErrorCode_t   err = TM_OK;
    UInt32          uRFLocal = 0;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA182I4_SetRF_Freq(0x%08X)", pObj->tUnitW);

    /* Set RF */
    uRFLocal = (uRF + 500) / 1000;

    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_RF_Frequency_byte_1__RF_Freq_1, (UInt8)((uRFLocal & 0x00FF0000) >> 16), Bus_None);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));

	if(err == TM_OK)
    {
        err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_RF_Frequency_byte_2__RF_Freq_2, (UInt8)((uRFLocal & 0x0000FF00) >> 8), Bus_None);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
    }
    if(err == TM_OK)
    {
        err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_RF_Frequency_byte_3__RF_Freq_3, (UInt8)(uRFLocal & 0x000000FF), Bus_None);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
    }
    if(err == TM_OK)
    {
        err = iTDA182I4_WriteRegMap(pObj, gTDA182I4_Reg_RF_Frequency_byte_1.Address, TDA182I4_REG_DATA_LEN(gTDA182I4_Reg_RF_Frequency_byte_1, gTDA182I4_Reg_RF_Frequency_byte_3));
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_WriteRegMap(0x%08X) failed.", pObj->tUnitW));
    }
    if(err == TM_OK)
    {
		/* Set IRQ_clear */
		err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_IRQ_clear, TDA182I4_IRQ_Global|TDA182I4_IRQ_SetRF, Bus_NoRead);
		tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
	}
	if(err == TM_OK)  /* <> value max ? */
	{
       /* Set ICP to Max*/
        err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Charge_pump_byte__ICP, 0x00, Bus_NoRead);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
	}
    if(err == TM_OK )
    {
		if  (pObj->bOverridePLL) /* or standard dependant */
		{
			/* Override the calculated PLL to get the best margin in case fine tuning is used */
			/* which means set the PLL in manuel mode that provides the best occurence of LO tuning (+-2 MHz) */
			/* without touching PostDiv and Prescaler */

			if(err == TM_OK)
			{
				err = iTDA182I4_SetPLL(pObj);
				tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_SetPLL failed.", pObj->tUnitW));
			}
			if(err == TM_OK)
			{
				err = iTDA182I4_Wait(pObj, 0x03); /* PLL convergence */
				tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Wait failed.", pObj->tUnitW));
			}
			if(err == TM_OK)
			{
				err = iTDA182I4_SetMSM(pObj, TDA182I4_MSM_RF_CAL_AV, True);
				tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_SetMSM(0x%08X, TDA182I4_MSM_RF_CAL_AV) failed.", pObj->tUnitW));
				if(err == TM_OK)
				{
					/* Wait for IRQ to trigger */
					err = iTDA182I4_WaitIRQ(pObj, 500, 10, TDA182I4_IRQ_MSM_RFCal);
					tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_WaitIRQ(0x%08X, 50, 5, TDA182I4_IRQ_SetRF) failed.", pObj->tUnitW));
				}
			}
		}
		else
		{
			err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Sigma_delta_byte_5__N_K_correct_manual, 0x00, Bus_None);
			tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
			err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Sigma_delta_byte_5__LO_Calc_Disable, 0x00, Bus_NoRead);
			tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));			
			if(err == TM_OK)
			{
				err = iTDA182I4_SetMSM(pObj, TDA182I4_MSM_SetRF, True);
				tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_SetMSM(0x%08X, TDA182I4_MSM_SetRF) failed.", pObj->tUnitW));
			}
			if(err == TM_OK)
			{
				/* Wait for IRQ to trigger */
				err = iTDA182I4_WaitIRQ(pObj, 500, 10, TDA182I4_IRQ_SetRF);
				tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_WaitIRQ(0x%08X, 50, 5, TDA182I4_IRQ_SetRF) failed.", pObj->tUnitW));
			}        
		}
    }
    if(err == TM_OK)
    {
		err = iTDA182I4_Wait(pObj, 0x03);  /* ensure PLL convergence with ICP max*/
	}	
    if(err == TM_OK)
    {
        /* Override ICP */
        err = iTDA182I4_OverrideICP(pObj, pObj->uProgRF);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_OverrideICP(0x%08X) failed.", pObj->tUnitW));
    }


    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA182I4_OverrideICP                                         */
/*                                                                            */
/* DESCRIPTION: Overrides ICP.                                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
static tmErrorCode_t
iTDA182I4_OverrideICP(
    pTDA182I4Object_t   pObj,   /* I: Driver object */
    UInt32              uRF     /* I: Wanted frequency */
)
{
    tmErrorCode_t   err = TM_OK;
    UInt32          uIF = 0;
    UInt8           ProgIF = 0;
    UInt8           LOPostdiv = 0;
    UInt8           LOPrescaler = 0;
    UInt32          FVCO = 0;
    UInt8           ICP = 0;
    UInt8           uPrevICP = 0;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA182I4_OverrideICP(0x%08X)", pObj->tUnitW);

    /*
    if fvco<6552 MHz ==> icp = 150µ (register = 01b)
    if fvco<6860 MHz ==> icp = 300µ (register = 10b)
    500µA elsewhere (register 00b)



    Reminder : fvco = postdiv*presc*(RFfreq+IFfreq) 
    */

    /* Read PostDiv et Prescaler */
    err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_Main_Post_Divider_byte, &LOPostdiv, Bus_RW);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Read(0x%08X) failed.", pObj->tUnitW));

    if(err == TM_OK)
    {
        /* PostDiv */
        err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_Main_Post_Divider_byte__LOPostDiv, &LOPostdiv, Bus_NoRead);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Read(0x%08X) failed.", pObj->tUnitW));

        if(err == TM_OK)
        {
            /* Prescaler */
            err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_Main_Post_Divider_byte__LOPresc, &LOPrescaler, Bus_NoRead);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Read(0x%08X) failed.", pObj->tUnitW));
        }

        if(err == TM_OK)
        {
            /* IF */
            err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_IF_Frequency_byte__IF_Freq, &ProgIF, Bus_NoRead);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Read(0x%08X) failed.", pObj->tUnitW));
        }

        if(err == TM_OK)
        {
            /* Decode IF */
            uIF = ProgIF*50000;
            
            /* Decode PostDiv */
            switch(LOPostdiv)
            {
                case 1:
                    LOPostdiv = 1;
                    break;
                case 2:
                    LOPostdiv = 2;
                    break;
                case 3:
                    LOPostdiv = 4;
                    break;
                case 4:
                    LOPostdiv = 8;
                    break;
                case 5:
                    LOPostdiv = 16;
                    break;
                default:
                    err = TDA182I4_ERR_BAD_PARAMETER;
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_OverrideICP(0x%08X) LOPostDiv value is wrong.", pObj->tUnitW));
                    break;
            }
        }
        if(err == TM_OK)
        {
            /* Calculate FVCO in MHz*/
            FVCO = LOPostdiv * LOPrescaler * ((uRF + uIF) / 1000000);

            /* Set correct ICP */

            if(FVCO < 6552)
            {
                /* Set ICP to 01 (= 150)*/
                ICP = 0x01;
            }
            else if(FVCO < 6860)
            {
                /* Set ICP to 10 (= 300)*/
                ICP = 0x02;
            }
            else
            {
                /* Set ICP to 00 (= 500)*/
                ICP = 0x00;
            }

            if(err == TM_OK)
            {
                /* Get ICP */
                err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_Charge_pump_byte__ICP, &uPrevICP, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Read(0x%08X) failed.", pObj->tUnitW));
            }

            if(uPrevICP != ICP )
            {
                /* Set ICP new value */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Charge_pump_byte__ICP, ICP, Bus_NoRead);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
            }
        }
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA182I4_OverrideBandsplit                                   */
/*                                                                            */
/* DESCRIPTION: Overrides Bandsplit settings.                                 */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
static tmErrorCode_t
iTDA182I4_OverrideBandsplit(
    pTDA182I4Object_t   pObj    /* I: Driver object */
)
{
    tmErrorCode_t   err = TM_OK;
    UInt8           Bandsplit = 0;
    UInt8           uPrevPSM_Bandsplit_Filter = 0;
    UInt8           PSM_Bandsplit_Filter = 0;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA182I4_OverrideBandsplit(0x%08X)", pObj->tUnitW);

    /* Setting PSM bandsplit at -3.9 mA for some RF frequencies */

    err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_Bandsplit_Filter_byte__IM2_Filter_SubBand, &Bandsplit, Bus_None);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Read(0x%08X) failed.", pObj->tUnitW));

    if(err == TM_OK)
    {
        err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_PowerSavingMode_byte_1__PSM_IM2_Filter, &uPrevPSM_Bandsplit_Filter, Bus_None);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Read(0x%08X) failed.", pObj->tUnitW));
    }

    if(err == TM_OK)
    {
        switch(Bandsplit)
        {
        default:
        case 0:
            /* LPF0 135.7MHz/LPF1 210.4MHz/HPF0 431.6MHz*/
            if(pObj->uProgRF < 135700000)
            {
                /* Set PSM bandsplit at -3.9 mA */
                PSM_Bandsplit_Filter = 0x03;
            }
            else
            {
                /* Set PSM bandsplit at nominal */
                PSM_Bandsplit_Filter = 0x02;
            }
            break;

        case 1:
            /* LPF0 141.8MHz/LPF1 222.7MHz/HPF0 456.2MHz */
            if(pObj->uProgRF < 141800000)
            {
                /* Set PSM bandsplit at -3.9 mA */
                PSM_Bandsplit_Filter = 0x03;
            }
            else
            {
                /* Set PSM bandsplit at nominal */
                PSM_Bandsplit_Filter = 0x02;
            }
            break;

        case 2:
            /* LPF0 148.0MHz/LPF1 235.0MHz/HPF0 480.8MHz */
            if(pObj->uProgRF < 148000000)
            {
                /* Set PSM bandsplit at -3.9 mA */
                PSM_Bandsplit_Filter = 0x03;
            }
            else
            {
                /* Set PSM bandsplit at nominal */
                PSM_Bandsplit_Filter = 0x02;
            }
            break;

        case 3:
            /* LPF0 154.1MHz/LPF1 247.3MHz/HPF0 505.3MHz */
            if(pObj->uProgRF < 154100000)
            {
                /* Set PSM bandsplit at -3.9 mA */
                PSM_Bandsplit_Filter = 0x03;
            }
            else
            {
                /* Set PSM bandsplit at nominal */
                PSM_Bandsplit_Filter = 0x02;
            }
            break;
        }

        if(uPrevPSM_Bandsplit_Filter != PSM_Bandsplit_Filter)
        {
            /* Write PSM bandsplit */
            err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_PowerSavingMode_byte_1__PSM_IM2_Filter, PSM_Bandsplit_Filter, Bus_NoRead);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
        }
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA182I4_OverrideWireless                                    */
/*                                                                            */
/* DESCRIPTION: Overrides Wireless settings.                                  */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
static tmErrorCode_t
iTDA182I4_OverrideWireless(
    pTDA182I4Object_t   pObj    /* I: Driver object */
)
{
    tmErrorCode_t   err = TM_OK;
    UInt8           uPrevW_Filter_byte = 0;
    UInt8           uW_Filter_byte = 0;
    UInt8           W_Filter = 0;
    UInt8           W_Filter_Bypass = 0;
    UInt8           W_Filter_Offset = 0;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA182I4_OverrideWireless(0x%08X)", pObj->tUnitW);

    /* Bypass ROM for wireless filters */
    /* WF7 = 1.7GHz - 1.98GHz */
    /* WF8 = 1.98GHz - 2.1GHz */
    /* WF9 = 2.1GHz - 2.4GHz */
    /* For all frequencies requiring WF7 and WF8, add -8% shift */
    /* For all frequencies requiring WF9, change to WF8 and add +4% shift */

    /* Check for filter WF9 */
    if(
        ((pObj->uProgRF > 474000000) && (pObj->uProgRF < 536000000)) ||
        ((pObj->uProgRF > 794000000) && (pObj->uProgRF < 866000000))
        )
    {
        /* ROM is selecting WF9 */

        /* Bypass to WF8 */
        W_Filter_Bypass = 0x01;
        W_Filter = 0x01;

        /* Apply +4% shift */
        W_Filter_Offset = 0x00;
    }
    else
    {
        /* Let ROM do the job */
        W_Filter_Bypass = 0x00;
        W_Filter = 0x00;

        /* Check for filter WF7 & WF8 */
        if(
            ((pObj->uProgRF > 336000000) && (pObj->uProgRF < 431000000)) ||
            ((pObj->uProgRF > 563500000) && (pObj->uProgRF < 721000000))
            )
        {
            /* ROM is selecting WF7 or WF8 */

            /* Apply -8% shift */
            W_Filter_Offset = 0x03;
        }
        else
        {
            /* Nominal */
            W_Filter_Offset = 0x01;
        }
    }

    /* Read current W_Filter_byte */
    err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_W_Filter_byte, &uPrevW_Filter_byte, Bus_None);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Read(0x%08X) failed.", pObj->tUnitW));

    if(err == TM_OK)
    {
        /* Set Wireless Filter Bypass */
        err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_W_Filter_byte__W_Filter_Bypass, W_Filter_Bypass, Bus_None);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));

        if(err == TM_OK)
        {
            /* Set Wireless Filter */
            err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_W_Filter_byte__W_Filter, W_Filter, Bus_None);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
        }

        if(err == TM_OK)
        {
            /* Set Wireless Filter Offset */
            err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_W_Filter_byte__W_Filter_Offset, W_Filter_Offset, Bus_None);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
        }

        if(err == TM_OK)
        {
            /* Set Wireless filters ON */
            err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_W_Filter_byte__W_Filter_Enable, 0x01, Bus_None);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
        }

        if(err == TM_OK)
        {
            /* Read above-modified W_Filter_byte */
            err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_W_Filter_byte, &uW_Filter_byte, Bus_None);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Read(0x%08X) failed.", pObj->tUnitW));
        }

        if(err == TM_OK && uPrevW_Filter_byte != uW_Filter_byte)
        {
            /* W_Filter_byte changed: Update it */
            err = iTDA182I4_WriteRegMap(pObj, gTDA182I4_Reg_W_Filter_byte.Address, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_WriteRegMap(0x%08X) failed.", pObj->tUnitW));
        }
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA182I4_SetPLL                                              */
/*                                                                            */
/* DESCRIPTION: Set the PLL in manual mode                                    */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
static tmErrorCode_t
iTDA182I4_SetPLL(
    pTDA182I4Object_t   pObj    /* I: Driver object */
)
{
    tmErrorCode_t err = TM_OK;

    /* LO wanted = RF wanted + IF in KHz */
    UInt32 LO = 0;
	UInt8 uProgIF = 0;

    /* Algorithm that calculates PostDiv */
    UInt8 PostDiv = 0; /* absolute value */
    UInt8 LOPostDiv = 0; /* register value */

    /* Algorithm that calculates Prescaler */
    UInt8 Prescaler = 0;

    /* Algorithm that calculates N, K */
    UInt32 N_int = 0;
    UInt32 K_int = 0;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA182I4_SetPLL(0x%08X)", pObj->tUnitW);

    /* Calculate wanted LO = RF + IF in Hz */
	err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_IF_Frequency_byte__IF_Freq, &uProgIF, Bus_None);
    LO = (pObj->uProgRF /1000) + (uProgIF*50);

    /* Calculate the best PostDiv and Prescaler : the ones that provide the best margin */
    /* in case of fine tuning +-2 MHz */
    err = iTDA182I4_FindPostDivAndPrescalerWithBetterMargin(LO, &PostDiv, &Prescaler);

    if (err == TM_OK)
    {
        /* Program the PLL only if valid values are found, in that case err == TM_OK */

        /* Decode PostDiv */
        switch(PostDiv)
        {
            case 1:
                LOPostDiv = 1;
                break;
            case 2:
                LOPostDiv = 2;
                break;
            case 4:
                LOPostDiv = 3;
                break;
            case 8:
                LOPostDiv = 4;
                break;
            case 16:
                LOPostDiv = 5;
                break;
            default:
                err = TDA182I4_ERR_BAD_PARAMETER;
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_SetPLL(0x%08X) *PostDiv value is wrong.", pObj->tUnitW));
                break;
        }

        /* Affect register map without writing into IC */
        if(err == TM_OK)
        {
            err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Main_Post_Divider_byte__LOPostDiv, LOPostDiv, Bus_None);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
        }

        if(err == TM_OK)
        {
            err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Main_Post_Divider_byte__LOPresc, Prescaler, Bus_None);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
        }

        if(err == TM_OK)
        {
            /* Calculate N & K values of the PLL */
            err = iTDA182I4_CalculateNIntKInt(LO, PostDiv, Prescaler, &N_int, &K_int);

            /* Affect registers map without writing to IC */
            if(err == TM_OK)
            {
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Sigma_delta_byte_4__LO_Frac_0, (UInt8)(K_int & 0xFF), Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Sigma_delta_byte_3__LO_Frac_1, (UInt8)((K_int >> 8) & 0xFF), Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Sigma_delta_byte_2__LO_Frac_2, (UInt8)((K_int >> 16) & 0xFF), Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Sigma_delta_byte_1__LO_Int, (UInt8)(N_int & 0xFF), Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Force manual selection mode : 0x3 at @0x56 */
                err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Sigma_delta_byte_5__N_K_correct_manual, 0x01, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));

                if(err == TM_OK)
                {
                    /* Force manual selection mode : 0x3 at @0x56 */
                    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_Sigma_delta_byte_5__LO_Calc_Disable, 0x01, Bus_None);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
                }
            }

            if(err == TM_OK)
            {
                /* Write bytes Main_Post_Divider_byte (0x51) to Sigma_delta_byte_5 (0x56) */
                err = iTDA182I4_WriteRegMap(pObj, gTDA182I4_Reg_Main_Post_Divider_byte.Address, TDA182I4_REG_DATA_LEN(gTDA182I4_Reg_Main_Post_Divider_byte, gTDA182I4_Reg_Sigma_delta_byte_5));
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
            }
        }
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA182I4_CalculatePostDivAndPrescaler                        */
/*                                                                            */
/* DESCRIPTION: Calculate PostDiv and Prescaler by starting from lowest value */
/*              of LO or not                                                  */
/*              LO must be passed in Hz                                       */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
static tmErrorCode_t
iTDA182I4_FindPostDivAndPrescalerWithBetterMargin(
    UInt32 LO,          /* In kHz */
    UInt8* PostDiv,     /* Directly the value to set in the register  */
    UInt8* Prescaler    /* Directly the value to set in the register  */
)
{
    /* Initialize to error in case no valuable values are found */
    tmErrorCode_t err = TM_OK;

    UInt8 PostDivGrowing;
    UInt8 PrescalerGrowing;
    UInt8 PostDivDecreasing;
    UInt8 PrescalerDecreasing;
    UInt32 FCVOGrowing = 0;
    UInt32 DistanceFCVOGrowing = 0;
    UInt32 FVCODecreasing = 0;
    UInt32 DistanceFVCODecreasing = 0;

    /* Get the 2 possible values for PostDiv & Prescaler to find the one
    which provides the better margin on LO */
    err = iTDA182I4_CalculatePostDivAndPrescaler(LO, True, &PostDivGrowing, &PrescalerGrowing);
    if (err == TM_OK)
    {
        /* Calculate corresponding FVCO value in kHz */
        FCVOGrowing = LO * PrescalerGrowing * PostDivGrowing;
    }

    err = iTDA182I4_CalculatePostDivAndPrescaler(LO, False, &PostDivDecreasing, &PrescalerDecreasing);
    if (err == TM_OK)
    {
        /* Calculate corresponding FVCO value in kHz */
        FVCODecreasing = LO * PrescalerDecreasing * PostDivDecreasing;
    }

    /* Now take the values that are providing the better margin, the goal is +-2 MHz on LO */
    /* So take the point that is the nearest of (FVCOmax - FVCOmin)/2 = 6391,875 MHz */
    if (FCVOGrowing != 0)
    {
        if (FCVOGrowing >= TDA182I4_MIDDLE_FVCO_RANGE)
        {
            DistanceFCVOGrowing = FCVOGrowing - TDA182I4_MIDDLE_FVCO_RANGE;
        }
        else
        {
            DistanceFCVOGrowing = TDA182I4_MIDDLE_FVCO_RANGE - FCVOGrowing;
        }
    }

    if (FVCODecreasing != 0)
    {
        if (FVCODecreasing >= TDA182I4_MIDDLE_FVCO_RANGE)
        {
            DistanceFVCODecreasing = FVCODecreasing - TDA182I4_MIDDLE_FVCO_RANGE;
        }
        else
        {
            DistanceFVCODecreasing = TDA182I4_MIDDLE_FVCO_RANGE - FVCODecreasing;
        }
    }

    if (FCVOGrowing == 0)
    {
        if (FVCODecreasing == 0)
        {
            /* No value at all are found */
            err = TDA182I4_ERR_BAD_PARAMETER;
        }
        else
        {
            /* No value in growing mode, so take the decreasing ones */
            *PostDiv = PostDivDecreasing;
            *Prescaler = PrescalerDecreasing;
        }
    }
    else
    {
        if (FVCODecreasing == 0)
        {
            /* No value in decreasing mode, so take the growing ones */
            *PostDiv = PostDivGrowing;
            *Prescaler = PrescalerGrowing;
        }
        else
        {
            /* Find the value which are the nearest of the middle of VCO range */
            if (DistanceFCVOGrowing <= DistanceFVCODecreasing)
            {
                *PostDiv = PostDivGrowing;
                *Prescaler = PrescalerGrowing;
            }
            else
            {
                *PostDiv = PostDivDecreasing;
                *Prescaler = PrescalerDecreasing;
            }
        }
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA182I4_CalculateNIntKInt                                   */
/*                                                                            */
/* DESCRIPTION: Calculate PLL N & K values                                    */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
iTDA182I4_CalculateNIntKInt(
    UInt32 LO, 
    UInt8 PostDiv, 
    UInt8 Prescaler, 
    UInt32* NInt, 
    UInt32* KInt
)
{
    tmErrorCode_t err = TM_OK;

    /* Algorithm that calculates N_K */
    UInt32 FVCO = 0;
    UInt32 N_K_prog = 0;

    /* Algorithm that calculates N, K corrected */
    UInt32 Nprime = 0;
    UInt32 KforceK0_1 = 0;
    UInt32 K2msb = 0;
    UInt32 N0 = 0;
    UInt32 Nm1 = 0;

    /* Calculate N_K_Prog */
    FVCO = LO * Prescaler * PostDiv;
    N_K_prog = (FVCO * 128) / 125;

    /* Calculate N & K corrected values */
    Nprime = N_K_prog & 0xFF0000;

    /* Force LSB to 1 */
    KforceK0_1 = 2*(((N_K_prog - Nprime) << 7) / 2) + 1;

    /* Check MSB bit around 2 */
    K2msb = KforceK0_1 >> 21;
    if (K2msb < 1)
    {
        N0 = 1;
    }
    else
    {
        if (K2msb >= 3)
        {
            N0 = 1;
        }
        else
        {
            N0 = 0;
        }
    }
    if (K2msb < 1)
    {
        Nm1 = 1;
    }
    else
    {
        Nm1 = 0;
    }

    /* Calculate N */
    *NInt = (2 * ((Nprime >> 16) - Nm1) + N0) - 128;

    /* Calculate K */
    if (K2msb < 1)
    {
        *KInt = KforceK0_1 + (2 << 21);
    }
    else
    {
        if (K2msb >= 3)
        {
            *KInt = KforceK0_1 - (2 << 21);
        }
        else
        {
            *KInt = KforceK0_1;
        }
    }

    /* Force last 7 bits of K_int to 0x5D, as the IC is doing for spurs optimization */
    *KInt &= 0xFFFFFF80;
    *KInt |= 0x5D;

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA182I4_CalculatePostDivAndPrescaler                        */
/*                                                                            */
/* DESCRIPTION: Calculate PostDiv and Prescaler by starting from lowest value */
/*              of LO or not                                                  */
/*              LO must be passed in Hz                                       */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
iTDA182I4_CalculatePostDivAndPrescaler(
    UInt32 LO,         /* In Hz */
    Bool growingOrder, /* Start from LO = 32 MHz or LO = 1008 MHz */
    UInt8* PostDiv,    /* Absolute value */
    UInt8* Prescaler   /* Absolute value  */
)
{
    tmErrorCode_t err = TM_OK;
    Int8 index;
    Int8 sizeTable = sizeof(PostDivPrescalerTable) / sizeof(TDA182I4_PostDivPrescalerTableDef);

    if (growingOrder == True)
    {
        /* Start from LO = 32 MHz */
        for (index = (sizeTable - 1); index >= 0; index--)
        {
            if (
                (LO > PostDivPrescalerTable[index].LO_min) &&
                (LO < PostDivPrescalerTable[index].LO_max)
               )
            {
                /* We are at correct index in the table */
                break;
            }
        }
    }
    else
    {
        /* Start from LO = 1008000 KHz */
        for (index = 0; index < sizeTable; index++)
        {
            if (
                (LO > PostDivPrescalerTable[index].LO_min) &&
                (LO < PostDivPrescalerTable[index].LO_max)
               )
            {
                /* We are at correct index in the table */
                break;
            }
        }
    }

    if ((index == -1) || (index == sizeTable))
    {
        err = TDA182I4_ERR_BAD_PARAMETER;
    }
    else
    {
        /* Write Prescaler */
        *Prescaler = PostDivPrescalerTable[index].Prescaler;

        /* Decode PostDiv */
        *PostDiv = PostDivPrescalerTable[index].PostDiv;
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA182I4_SetMSM                                              */
/*                                                                            */
/* DESCRIPTION: Set the MSM bit(s).                                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
iTDA182I4_SetMSM(
    pTDA182I4Object_t   pObj,   /* I: Driver object */
    UInt8               uValue, /* I: Item value */
    Bool                bLaunch /* I: Launch MSM */
)
{
    tmErrorCode_t   err = TM_OK;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA182I4_SetMSM(0x%08X)", pObj->tUnitW);

    /* Set state machine and Launch it */
    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_MSM_byte_1, uValue, Bus_None);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));

    if(err == TM_OK && bLaunch)
    {
        err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_MSM_byte_2__MSM_Launch, 0x01, Bus_None);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
    }

    if(err == TM_OK)
    {
        err = iTDA182I4_WriteRegMap(pObj, gTDA182I4_Reg_MSM_byte_1.Address, bLaunch?0x02:0x01);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_WriteRegMap(0x%08X) failed.", pObj->tUnitW));
    }

    if(err == TM_OK && bLaunch)
    {
        err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_MSM_byte_2__MSM_Launch, 0x00, Bus_None);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA182I4_WaitIRQ                                             */
/*                                                                            */
/* DESCRIPTION: Wait the IRQ to trigger                                       */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
iTDA182I4_WaitIRQ(
    pTDA182I4Object_t   pObj,       /* I: Driver object */
    UInt32              timeOut,    /* I: timeout */
    UInt32              waitStep,   /* I: wait step */
    UInt8               irqStatus   /* I: IRQs to wait */
)
{
    tmErrorCode_t   err = TM_OK;
    UInt32          counter = timeOut/waitStep; /* Wait max timeOut/waitStep ms */
    UInt8           uIRQ = 0;
    UInt8           uIRQStatus = 0;
    Bool            bIRQTriggered = False;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA182I4_WaitIRQ(0x%08X)", pObj->tUnitW);

    while(err == TM_OK && (counter--)>0)
    {
        err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_IRQ_status__IRQ_status, &uIRQ, Bus_RW);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Read(0x%08X) failed.", pObj->tUnitW));

        if(err == TM_OK && uIRQ == 1)
        {
            bIRQTriggered = True;
        }

        if(bIRQTriggered)
        {
            /* IRQ triggered => Exit */
            break;
        }

        if(err == TM_OK && irqStatus != 0x00)
        {
            err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_IRQ_status, &uIRQStatus, Bus_None);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Read(0x%08X) failed.", pObj->tUnitW));

            if(irqStatus == uIRQStatus)
            {
                bIRQTriggered = True;
            }
        }

        if(counter)
        {
            err = iTDA182I4_Wait(pObj, waitStep);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Wait(0x%08X) failed.", pObj->tUnitW));
        }
    }

    if(err == TM_OK && bIRQTriggered == False)
    {
        err = TDA182I4_ERR_NOT_READY;
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA182I4_Write                                               */
/*                                                                            */
/* DESCRIPTION: Writes in TDA182I4 hardware                                   */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
iTDA182I4_Write(
    pTDA182I4Object_t           pObj,       /* I: Driver object */
    const TDA182I4_BitField_t*  pBitField, /* I: Bitfield structure */
    UInt8                       uData,      /* I: Data to write */
    tmbslFrontEndBusAccess_t                eBusAccess  /* I: Access to bus */
)
{
    tmErrorCode_t   err = TM_OK;
    UInt8           RegAddr = 0;
    UInt32          DataLen = 1;
    UInt8           RegData = 0;
    pUInt8          pRegData = Null;
    UInt32          RegMask = 0;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA182I4_Write(0x%08X)", pObj->tUnitW);

    if(pBitField == Null)
    {
        err = TDA182I4_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        /* Set Register Address */
        RegAddr = pBitField->Address;

        if(RegAddr < TDA182I4_REG_MAP_NB_BYTES)
        {
            pRegData = (UInt8 *)(&(pObj->RegMap)) + RegAddr;
        }
        else
        {
            pRegData = &RegData;
        }

        if( (eBusAccess&Bus_NoRead) == False && P_SIO_READ_VALID)
        {
            /* Read data from TDA182I4 */
            err = P_SIO_READ(pObj->tUnitW, TDA182I4_REG_ADD_SZ, &RegAddr, DataLen, pRegData);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "IO_Read(0x%08X, 1, 0x%02X, %d) failed.", pObj->tUnitW, RegAddr, DataLen));
        }

        if(err == TM_OK)
        {
            RegMask = ( (1 << pBitField->WidthInBits) - 1);
            /* Limit uData to WidthInBits */
            uData &= RegMask;

            /* Set Data */
            RegMask = RegMask << pBitField->PositionInBits;
            *pRegData &= (UInt8)(~RegMask);
            *pRegData |= uData << pBitField->PositionInBits;

            if( (eBusAccess&Bus_NoWrite) == False && P_SIO_WRITE_VALID)
            {
                /* Write data to TDA182I4 */
                err = P_SIO_WRITE(pObj->tUnitW, TDA182I4_REG_ADD_SZ, &RegAddr, DataLen, pRegData);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "IO_Write(0x%08X, 1, 0x%02X, %d) failed.", pObj->tUnitW, RegAddr, DataLen));
            }
        }
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA182I4_Read                                                */
/*                                                                            */
/* DESCRIPTION: Reads in TDA182I4 hardware                                    */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
iTDA182I4_Read(
    pTDA182I4Object_t           pObj,       /* I: Driver object */
    const TDA182I4_BitField_t*  pBitField, /* I: Bitfield structure */
    UInt8*                      puData,     /* I: Data to read */
    tmbslFrontEndBusAccess_t                eBusAccess  /* I: Access to bus */
)
{
    tmErrorCode_t   err = TM_OK;
    UInt8           RegAddr = 0;
    UInt32          DataLen = 1;
    UInt8           RegData = 0;
    pUInt8          pRegData = Null;
    UInt32          RegMask = 0;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA182I4_Read(0x%08X)", pObj->tUnitW);

    if(pBitField == Null)
    {
        err = TDA182I4_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        /* Set Register Address */
        RegAddr = pBitField->Address;

        if(RegAddr < TDA182I4_REG_MAP_NB_BYTES)
        {
            pRegData = (UInt8 *)(&(pObj->RegMap)) + RegAddr;
        }
        else
        {
            pRegData = &RegData;
        }

        if( (eBusAccess&Bus_NoRead) == False && P_SIO_READ_VALID)
        {
            /* Read data from TDA182I4 */
            err = P_SIO_READ(pObj->tUnitW, TDA182I4_REG_ADD_SZ, &RegAddr, DataLen, pRegData);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "IO_Read(0x%08X, 1, 0x%02X, %d) failed.", pObj->tUnitW, RegAddr, DataLen));
        }

        if(err == TM_OK && puData != Null)
        {
            /* Copy Raw Data */
            *puData = *pRegData;

            /* Get Data */
            RegMask = ( (1 << pBitField->WidthInBits) - 1) << pBitField->PositionInBits;
            *puData &= (UInt8)RegMask;
            *puData = (*puData) >> pBitField->PositionInBits;
        }
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA182I4_WriteRegMap                                         */
/*                                                                            */
/* DESCRIPTION: Writes driver RegMap cached data to TDA182I4 hardware.        */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
iTDA182I4_WriteRegMap(
    pTDA182I4Object_t   pObj,       /* I: Driver object */
    UInt8               uAddress,   /* I: Data to write */
    UInt32              uWriteLen   /* I: Number of data to write */
)
{
    tmErrorCode_t   err = TM_OK;
    pUInt8          pRegData = Null;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA182I4_WriteRegMap(0x%08X)", pObj->tUnitW);

    if( uAddress < TDA182I4_REG_MAP_NB_BYTES &&
        (uAddress + uWriteLen) <= TDA182I4_REG_MAP_NB_BYTES )
    {
        pRegData = (UInt8 *)(&(pObj->RegMap)) + uAddress;
    }
    else
    {
        err = TDA182I4_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK && P_SIO_WRITE_VALID)
    {
        /* Write data to TDA182I4 */
        err = P_SIO_WRITE(pObj->tUnitW, TDA182I4_REG_ADD_SZ, &uAddress, uWriteLen, pRegData);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "IO_Write(0x%08X, 1, 0x%02X, %d) failed.", pObj->tUnitW, uAddress, uWriteLen));
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA182I4_ReadRegMap                                          */
/*                                                                            */
/* DESCRIPTION: Reads driver RegMap cached data from TDA182I4 hardware.       */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
iTDA182I4_ReadRegMap(
    pTDA182I4Object_t   pObj,       /* I: Driver object */
    UInt8               uAddress,   /* I: Data to read */
    UInt32              uReadLen    /* I: Number of data to read */
)
{
    tmErrorCode_t   err = TM_OK;
    pUInt8          pRegData = Null;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA182I4_ReadRegMap(0x%08X)", pObj->tUnitW);

    if( uAddress < TDA182I4_REG_MAP_NB_BYTES &&
       (uAddress + uReadLen) <= TDA182I4_REG_MAP_NB_BYTES )
    {
        pRegData = (UInt8 *)(&(pObj->RegMap)) + uAddress;
    }
    else
    {
        err = TDA182I4_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK && P_SIO_READ_VALID)
    {
        /* Read data from TDA182I4 */
        err = P_SIO_READ(pObj->tUnitW, TDA182I4_REG_ADD_SZ, &uAddress, uReadLen, pRegData);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "IO_Read(0x%08X, 1, 0x%02X, %d) failed.", pObj->tUnitW, uAddress, uReadLen));
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA182I4_Wait                                                */
/*                                                                            */
/* DESCRIPTION: Waits for requested time.                                     */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t 
iTDA182I4_Wait(
    pTDA182I4Object_t   pObj,   /* I: Driver object */
    UInt32              Time    /* I: time to wait for */
)
{
    tmErrorCode_t   err = TDA182I4_ERR_NULL_CONTROLFUNC;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA182I4_Wait(0x%08X)", pObj->tUnitW);

    if(P_STIME_WAIT_VALID)
    {
        /* Wait Time ms */
        err = P_STIME_WAIT(pObj->tUnitW, Time);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TIME_Wait(0x%08X, %d) failed.", pObj->tUnitW, Time));
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA182I4_PowerSavingMode                                     */
/*                                                                            */
/* DESCRIPTION: set registers according  the  PowerSavingMode                 */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t 
iTDA182I4_PowerSavingMode(
    pTDA182I4Object_t   pObj,   /* I: Driver object */
    TDA182I4PowerSavingMode_t  PowerSavingMode    /* I: time to wait for */
)
{
    tmErrorCode_t   err = TDA182I4_ERR_NULL_CONTROLFUNC;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA182I4_Wait(0x%08X)", pObj->tUnitW);

	if (PowerSavingMode == TDA182I4PowerSavingMode_normal )
	{
		/* PowerSavingMode nominal */
		err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_PowerSavingMode_byte_1, 0x7C, Bus_None);
		err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_PowerSavingMode_byte_2, 0x94, Bus_None);
		err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_PowerSavingMode_byte_3, 0x55, Bus_None);
	}
	else
	{
		/* PowerSavingMode low */
		err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_PowerSavingMode_byte_1, 0x3C, Bus_None);
		err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_PowerSavingMode_byte_2, 0xBF, Bus_None);
		err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_PowerSavingMode_byte_3, 0xA9, Bus_None);
	}
    if(err == TM_OK)
    {
        /* Write gTDA182I4_Reg_PowerSavingMode_byte_1 (0x23) to gTDA182I4_Reg_PowerSavingMode_byte_4 (0x26) Registers */
        err = iTDA182I4_WriteRegMap(pObj, gTDA182I4_Reg_PowerSavingMode_byte_1.Address, TDA182I4_REG_DATA_LEN(gTDA182I4_Reg_PowerSavingMode_byte_1, gTDA182I4_Reg_PowerSavingMode_byte_4));
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_WriteRegMap(0x%08X) failed.", pObj->tUnitW));
    }
    if(err == TM_OK)
    {
        pObj->curPowerSavingMode = PowerSavingMode;
    }


	return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA182I4_GetRSSI                                             */
/*                                                                            */
/* DESCRIPTION: Reads RSSI.                                                   */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
iTDA182I4_GetRSSI(
    pTDA182I4Object_t   pObj,   /* I: Driver object */
    UInt8*              puValue /* O: RSSI value */
)
{
    tmErrorCode_t   err = TM_OK;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA182I4_GetRSSI(0x%08X)", pObj->tUnitW);

    *puValue = 0;

    /* Set IRQ_clear*/
    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_IRQ_clear, TDA182I4_IRQ_Global|TDA182I4_IRQ_GetPowerLevel, Bus_NoRead);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Write(0x%08X) failed.", pObj->tUnitW));

    if(err == TM_OK)
    {
        /* Set state machine and Launch it */
        err = iTDA182I4_SetMSM(pObj, TDA182I4_MSM_GetPowerLevel, True);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_SetMSM(0x%08X, TDA182I4_MSM_GetPowerLevel) failed.", pObj->tUnitW));
    }

    if(err == TM_OK)
    {
        err = iTDA182I4_WaitIRQ(pObj, 700, 1, TDA182I4_IRQ_GetPowerLevel);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_WaitIRQ(0x%08X) failed.", pObj->tUnitW));
    }

    if(err == TM_OK)
    {
        /* Read Power_Level_byte */
        err = iTDA182I4_Read(pObj, &gTDA182I4_Reg_RSSI_byte_1__RSSI, puValue, Bus_RW);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA182I4_Read(0x%08X) failed.", pObj->tUnitW));

        if(err != TM_OK)
        {
            err = TDA182I4_ERR_HW_FAILED;
        }
    }

    return err;
}
/*============================================================================*/
/* FUNCTION:    iTDA182I4_SetIRcal                                            */
/*                                                                            */
/* DESCRIPTION: owerwrite IRcal High with Mid IRcal                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
iTDA182I4_SetIRcal(
    pTDA182I4Object_t   pObj   /* I: Driver object */
)
{
    tmErrorCode_t   err = TM_OK;
    UInt8 IR_Mixer_Gain_loop, IR_RxPtr_loop, uRx_Read;
    UInt8 RegAddr = 0x6B;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA182I4_SetIRcal(0x%08X)", pObj->tUnitW);

    err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_IR_Cal_byte_5__Mixer_Gain_Bypass, 0X01 , Bus_None);

    for (IR_Mixer_Gain_loop = 0; IR_Mixer_Gain_loop <5;IR_Mixer_Gain_loop++ )
    {
        for (IR_RxPtr_loop = 0; IR_RxPtr_loop <4; IR_RxPtr_loop++ )
        {
            if(err == TM_OK)
            {
                 err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_IR_Cal_byte_5__IR_Mixer_Gain, IR_Mixer_Gain_loop , Bus_None);
            }
            if(err == TM_OK)
            {
                 err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_IR_Cal_byte_5__IR_RxPtr, IR_RxPtr_loop , Bus_None);
            }
            if(err == TM_OK)
            {
                 err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_IR_Cal_byte_5__IR_FreqPtr, 0x2 , Bus_NoRead); /* Mid value */
            }
            if(err == TM_OK)
            {
                err = P_SIO_READ(pObj->tUnitW, 0x01, &RegAddr, 1, &uRx_Read); /* read 0x6D */
            }
            if(err == TM_OK)
            {
                 err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_IR_Cal_byte_5__IR_FreqPtr, 0x3 , Bus_NoRead); /* High value */
            }
            if(err == TM_OK)
            {
                 err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_IR_Cal_byte_6__Rx_Force, 0x01 , Bus_None);
            }
            if(err == TM_OK)
            {
                 err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_IR_Cal_byte_6__Rx_bp, uRx_Read , Bus_NoRead);
            }
            if(err == TM_OK)
            {
                 err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_IR_Cal_byte_6__Rx_Force, 0x00 , Bus_NoRead);
            }
        }
    }
    if(err == TM_OK)
    {
        err = iTDA182I4_Write(pObj, &gTDA182I4_Reg_IR_Cal_byte_5__Mixer_Gain_Bypass, 0X00 , Bus_NoRead);
    }
 
    return err;
}
#ifdef _TVFE_IMPLEMENT_MUTEX

/*============================================================================*/
/* FUNCTION:    iTDA182I4_MutexAcquire:                                       */
/*                                                                            */
/* DESCRIPTION: Acquires driver mutex.                                        */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*============================================================================*/
tmErrorCode_t
iTDA182I4_MutexAcquire(
    pTDA182I4Object_t   pObj,
    UInt32              timeOut
)
{
    tmErrorCode_t   err = TDA182I4_ERR_NULL_CONTROLFUNC;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA182I4_MutexAcquire(0x%08X)", pObj->tUnitW);

    if(P_SMUTEX_ACQUIRE_VALID && P_MUTEX_VALID)
    {
        err = P_SMUTEX_ACQUIRE(P_MUTEX, timeOut);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "Mutex_Acquire(0x%08X, %d) failed.", pObj->tUnitW, timeOut));
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA182I4_MutexRelease:                                       */
/*                                                                            */
/* DESCRIPTION: Releases driver mutex.                                        */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*============================================================================*/
tmErrorCode_t
iTDA182I4_MutexRelease(
    pTDA182I4Object_t   pObj
)
{
    tmErrorCode_t   err = TDA182I4_ERR_NULL_CONTROLFUNC;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA182I4_MutexRelease(0x%08X)", pObj->tUnitW);

    if(P_SMUTEX_RELEASE_VALID && P_MUTEX_VALID)
    {
        err = P_SMUTEX_RELEASE(P_MUTEX);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "Mutex_Release(0x%08X) failed.", pObj->tUnitW));
    }

    return err;
}
#endif




