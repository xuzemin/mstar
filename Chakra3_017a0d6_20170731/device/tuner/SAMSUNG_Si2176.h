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


#ifndef _SAMSUNG_SI2176_H_
#define _SAMSUNG_SI2176_H_


#ifdef _SAMSUNG_SI2176_S
#define INTERFACE
#else
#define INTERFACE extern
#endif

#define TN_FREQ_STEP                FREQ_STEP_62_5KHz//FREQ_STEP_50KHz//FREQ_STEP_62_5KHz//FREQ_STEP_50KHz//FREQ_STEP_31_25KHz

#define _TUNER_I2C_ID        0xC0

//***********No used for Silicon tuner,but for API*******************************
#define VHF_LOWMIN_FREQ        46250L    // KHz
#define VHF_LOWMAX_FREQ        142000L    // KHz
#define VHF_HIGHMIN_FREQ    149000L    // KHz
#define VHF_HIGHMAX_FREQ    426000L    // KHz
#define UHF_MIN_FREQ        434000L    // KHz
#define UHF_MAX_FREQ        863250L    // KHz
#define TUNER_IF_FREQ_KHz            0L//38900L    // KHz
#define TUNER_L_PRIME_IF_FREQ_KHz   0L// 33950L    // KHz
//*********************end*************************************************

//****************************************************************************
// Public functions.
//****************************************************************************

#define NXP18273_I2C_ADDR (((U16)TUNER_IIC_BUS<<8)| _TUNER_I2C_ID)

INTERFACE void devTunerInit(void);
INTERFACE void devTunerSetFreqStep(FREQSTEP eFreqStep);
INTERFACE void devTunerSetPLLData(WORD wPLLData, RFBAND eBand);
INTERFACE void devDigitalTuner_ExtendCommand (MS_U8 u8SubCmd, MS_U32 u32Param1, MS_U32 u32Param2, void* pvoidParam3);
INTERFACE S32 devTunerGetFreqOffset(void);
INTERFACE void devTunerSetIF(IF_FREQ eCurrentstandard);

BOOL devTunerGetVIFLockStatus(void);


#undef INTERFACE
#endif


