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

#if !defined(__IF_SI2176_H__)
#define __IF_SI2176_H__

#ifdef SI2176_C
#define INTERFACE
#else
#define INTERFACE extern
#endif


//****************************************************************************
// Public attributes.
//****************************************************************************
#define _IF_DEM_I2C_ID            0xC0   // 0x86, 0x84, 0x96, 0x94

typedef enum
{
    E_AFC_BELOW_MINUS_187p5KHz      = 0x07,
    E_AFC_MINUS_162p5KHz            = 0x06,
    E_AFC_MINUS_137p5KHz            = 0x05,
    E_AFC_MINUS_112p5KHz            = 0x04,
    E_AFC_MINUS_87p5KHz             = 0x03,
    E_AFC_MINUS_62p5KHz             = 0x02,
    E_AFC_MINUS_37p5KHz             = 0x01,
    E_AFC_MINUS_12p5KHz             = 0x00,
    E_AFC_PLUS_12p5KHz              = 0x0F,
    E_AFC_PLUS_37p5KHz              = 0x0E,
    E_AFC_PLUS_62p5KHz              = 0x0D,
    E_AFC_PLUS_87p5KHz              = 0x0C,
    E_AFC_PLUS_112p5KHz             = 0x0B,
    E_AFC_PLUS_137p5KHz             = 0x0A,
    E_AFC_PLUS_162p5KHz             = 0x09,
    E_AFC_ABOVE_PLUS_187p5KHz       = 0x08,
    E_AFC_OUT_OF_AFCWIN             = 0x10,
} AFC;

//****************************************************************************
// Public functions.
//****************************************************************************
INTERFACE void MDrv_IFDM_Init(void);
INTERFACE AFC MDrv_IFDM_GetFreqDev(void);
INTERFACE BOOLEAN MDrv_IFDM_IsAFCInWindow(void);
INTERFACE void MDrv_IFDM_SetIF(IF_FREQ eIF_Freq);
INTERFACE void MDrv_IFDM_CVBSOff(void);
INTERFACE IF_FREQ MDrv_IFDM_GetIF(void);

#undef INTERFACE
#endif
