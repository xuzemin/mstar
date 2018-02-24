////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////


//*******************************************************************************
//  FOR FQD1136 ONLY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//*******************************************************************************


#define SI2176_C
#include "debug.h"
#include "msAPI_Tuning.h"

#include "COFDM_Demodulator.h"
#include "drvIIC.h"
#include "SAMSUNG_Si2176.h"
#ifdef DEBUG_IFDEMODULATOR
    #define debugIFDemodulatorPrint(a,b)    debugPrint(a,b)
#else
    #define debugIFDemodulatorPrint(a,b)
#endif

// Automatic frequency contrl

static IF_FREQ m_eIF_Freq;

void MDrv_IFDM_Init(void)
{

}

AFC MDrv_IFDM_GetFreqDev(void)
{
    S32 s32frequencyoffset;

    s32frequencyoffset= devTunerGetFreqOffset();
    // printf("Brian Tuner frequency offset %d\r\n",s32frequencyoffset);

    if((187.5<s32frequencyoffset)  && (s32frequencyoffset<=1000))
    {
        return E_AFC_BELOW_MINUS_187p5KHz;
    }
    else if((162.5<s32frequencyoffset)  && (s32frequencyoffset<=187.5))
    {
        return E_AFC_MINUS_162p5KHz;
    }
    else if((137.5<s32frequencyoffset)  && (s32frequencyoffset<=162.5))
    {
        return E_AFC_MINUS_137p5KHz;
    }
    else if((112.5<s32frequencyoffset)  && (s32frequencyoffset<=137.5))
    {
        return E_AFC_MINUS_112p5KHz;
    }
    else if((87.5<s32frequencyoffset)  && (s32frequencyoffset<=112.5))
    {
        return E_AFC_MINUS_87p5KHz;
    }
    else if((62.5<s32frequencyoffset)  && (s32frequencyoffset<=87.5))
    {
        return E_AFC_MINUS_62p5KHz;
    }
    else if((37.5<s32frequencyoffset)  && (s32frequencyoffset<=62.5))
    {
        return E_AFC_MINUS_37p5KHz;
    }
    else if((12.5<s32frequencyoffset)  && (s32frequencyoffset<=37.5))
    {
        return E_AFC_MINUS_12p5KHz;
    }
    else if((0<s32frequencyoffset)  && (s32frequencyoffset<=12.5))
    {
        return E_AFC_MINUS_12p5KHz;
    }
    else if((-12.5<s32frequencyoffset)  && (s32frequencyoffset<=0))
    {
        return E_AFC_PLUS_12p5KHz;
    }
    else if((-37.5<s32frequencyoffset)  && (s32frequencyoffset<=-12.5))
    {
        return E_AFC_PLUS_12p5KHz;
    }
    else if((-62.5<s32frequencyoffset)  && (s32frequencyoffset<=-37.5))
    {
        return E_AFC_PLUS_37p5KHz;
    }
    else if((-87.5<s32frequencyoffset)  && (s32frequencyoffset<=-62.5))
    {
        return E_AFC_PLUS_62p5KHz;
    }
    else if((-112.5<s32frequencyoffset)  && (s32frequencyoffset<=-87.5))
    {
        return E_AFC_PLUS_87p5KHz;
    }
    else if((-137.5<s32frequencyoffset)  && (s32frequencyoffset<=-112.5))
    {
        return E_AFC_PLUS_112p5KHz;
    }
    else if((-162.5<s32frequencyoffset)  && (s32frequencyoffset<=-137.5))
    {
        return E_AFC_PLUS_137p5KHz;
    }
    else if((-187.5<s32frequencyoffset)  && (s32frequencyoffset<=-162.5))
    {
        return E_AFC_PLUS_162p5KHz;
    }
    else if((-1000<s32frequencyoffset)  && (s32frequencyoffset<=-187.5))
    {
       return E_AFC_ABOVE_PLUS_187p5KHz;
    }
    else
    {
        return E_AFC_OUT_OF_AFCWIN;
    }
}

BOOLEAN MDrv_IFDM_IsAFCInWindow(void)
{
   #if 0
    BYTE cValue;

    devCOFDM_PassThroughI2C_ReadBytes(_IF_DEM_I2C_ID, 0, NULL, 1, &cValue);

#if(FRONTEND_TUNER_TYPE == NXP_FQD1136_TUNER)
    if( (cValue & _MASK_OF_AFC) < E_AFC_BELOW_MINUS_125pKHz )
#endif
    {
        return TRUE;
    }
   #endif
    return FALSE;
}

void MDrv_IFDM_SetIF(IF_FREQ eIF_Freq)
{
     //printf("MDrv_IFDM_SetIF(eIF_Freq=%u)\n", eIF_Freq);

     m_eIF_Freq = eIF_Freq;

     devTunerSetIF(eIF_Freq);
     //printf("Brian %s %d %d \r \n", __FUNCTION__,__LINE__,m_eIF_Freq);
}

void MDrv_IFDM_CVBSOff(void)
{

}

IF_FREQ MDrv_IFDM_GetIF(void)
{
    //printf("Brian %s %d %d \r \n", __FUNCTION__,__LINE__,m_eIF_Freq);
    return m_eIF_Freq;
}

#undef SI2176_C
