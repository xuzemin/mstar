//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all 
// or part of MStar Software is expressly prohibited, unless prior written 
// permission has been granted by MStar. 
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.  
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software. 
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s 
//    confidential information in strictest confidence and not disclose to any
//    third party.  
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.  
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or 
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.  
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
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

#define _M88DC2800_C_

/* ------------------------------------
    Header Files
   ------------------------------------ */
#include "datatype.h"
#include "drvIIC.h"
#include "M88DC2800.h"
#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"
/* ------------------------------------
    Macro Definitions
   ------------------------------------ */

/* ------------------------------------
    Type Definitions
   ------------------------------------ */


/* ------------------------------------
    Variables Definitions
   ------------------------------------ */


#define M88DC2800_DBG(x)   x

typedef struct
{
    U8    cAddress;
    U8    cData;
} INIT_DATA_COFDM_DEM;

#if (FRONTEND_TUNER_TYPE == ALPS_TDQG9_601A_TUNER)
//This table is for TDQE3 tuner
static code INIT_DATA_COFDM_DEM m_InitDataCOFDM1[] =
{
    { _QAM_SEL,             0x48 }, // 64 QAM
    { _BLIND_STEP1,         0x09 },
    { _BLIND_STEP2,         0x0A },
    { _BLIND_STEP3,         0x0B },
    { _LMS_STEP1,           0x0B },
    { 0x03,                 0x18 },
    { _LMS_STEP2,           0x0D },
    { _AGC_FREZ,            0x80 },
    { _AAGC_ACQ_CLR,        0x40 },
    { _SYMB_RATE_1,         0x7A },
    { _SYMB_RATE_2,         0xD9 },
    { _SYMB_RATE_3,         0xDF },
    { _SYMB_RATE_4,         0x39 },
    { _STL_CTRL0,           0x00 },
    { _SYMB_RATE_INV1,      0x71 },
    { _SYMB_RATE_INV2,      0x23 },
    { _INT_LCK_SRC,         0x40 },
    { 0xF9,                 0x08 },
    { _CRL_SWP_SEL,         0x40 },
    { 0x62,                 0x0A },
    { _GPPWM_CORN_RAT_LO,   0xCD },
    { _GPPWM_CORN_RAT_HI,   0xFF },
    { _SYNC_0,              0x06 },
    { _DESC_MD,             0x00 },
    { _RS_BER_0,            0x03 },
    { _CNT_HLD_CLR,         0x81 },
    { 0xFA,                 0x40 },
    { _ADC_CRL_0,           0x10 },
    { _BLIND_DUR_HI,        0x40 },
    { _LMS_DUR_HI,          0x9C },
    { _LMS_DUR_LO,          0x40 }
};

static code INIT_DATA_COFDM_DEM m_InitDataCOFDM2[] =
{
    { 0xF6,                 0x4E },
    { 0xF7,                 0x20 },
    { 0x89,                 0x02 },
    { 0x14,                 0x08 },
    { 0x6F,                 0x0D },
    { 0x10,                 0xFF },
    { _DERO_INIT_FREQ,      0x00 },
    { _DERO_FREQ_STEP,      0x30 },
    { _DERO_FREQ_LIM,       0x23 },
    { _CRL_SWP_INI_0,       0x00 },
    { _CRL_EQ_CAP6,         0x00 },
    { _CRL_CTRL,            0x03 },
    { _ADC_TM_COEF,         0x0C },
    { 0x4D,                 0xF7 },
    { 0xE0,                 0x75 },
    { _SLEEP_MD,            0x06 },
    { 0x8D,                 0x29 },
    { 0x8B,                 0x5B },
    { 0x4E,                 0xD8 },
    { _REG_VGACFM,          0x9D },
    { _GRST_FMT,            0x6C },
    { _FMT_0,               0x43 },
    { _AGC_POL_INV,         0x80 },
    { _STL_GN_1,            0x79 },
    { _STL_DIR_GN,          0x03 },
    { _STL_GN_2,            0x30 },
    { 0x5E,                 0x02 },
    { 0x5F,                 0x0F },
    { _DAGC_LCK_THR_HI,     0x03 },
    { _DAGC_LP_GN1,         0x12 },
    { _DAGC_LP_GN2,         0x12 }
};

static code INIT_DATA_COFDM_DEM m_InitDataCOFDM_Condition1[] =
{
    { _AGCIF_MAX,           0xFF },
    { 0x31,                 0x20 },
    { _AGCRF_MAX,           0x00 },
    { 0x33,                 0x00 },
    { _AGCIF_THR,           0x43 },
    { _AGC_REF_LO,          0x00 },
    { _AGC_REF_HI,          0x10 },
    { _BLIND_DUR_LO,        0x02 },
    { 0xF4,                 0x04 },
    { 0xF5,                 0x00 },
    { _AAGC_LCK_DUR,        0x14 },
    { 0xE1,                 0x25 }
};

static code INIT_DATA_COFDM_DEM m_InitDataCOFDM_Condition2[] =
{
    { _AGCIF_MAX,           0xFF },
    { 0x31,                 0x20 },
    { _AGCRF_MAX,           0x00 },
    { 0x33,                 0x00 },
    { _AGCIF_THR,           0x43 },
    { _AGCRF_MIN,           0x00 },
    { _AGCIF_MIN,           0x20 },
    { _AGC_REF_LO,          0x00 },
    { _AGC_REF_HI,          0x10 },
    { _BLIND_DUR_LO,        0x00 },
    { 0xF4,                 0x00 },
    { 0xF5,                 0x40 },
    { _AAGC_LCK_DUR,        0x14 },
    { 0xE1,                 0x25 }
};

static code INIT_DATA_COFDM_DEM m_InitDataCOFDM_Condition3[] =
{
    { _AGCIF_MAX,           0xFF },
    { 0x31,                 0x20 },
    { _AGCRF_MAX,           0x00 },
    { 0x33,                 0x00 },
    { _AGCIF_THR,           0x43 },
    { _AGCRF_MIN,           0x00 },
    { _AGCIF_MIN,           0x20 },
    { _BLIND_DUR_LO,        0x00 },
    { 0xF4,                 0x00 },
    { 0xF5,                 0x40 },
    { _AAGC_LCK_DUR,        0x24 },
    { 0xE1,                 0x25 },

    { 0x92,                 0x7F },
    { 0x93,                 0x91 },
    { 0x95,                 0x00 },
    { 0x2B,                 0x33 },
    { _AGCRF_MAX_STEP,      0x2A },
    { 0x2E,                 0x80 },
    { 0x25,                 0x25 },
    { 0x2D,                 0xFF },
    { 0x26,                 0xFF },
    { 0x27,                 0x00 },
    { 0x24,                 0x25 },
    { 0xA4,                 0xFF },
    { 0xA3,                 0x0D }
};

static code INIT_DATA_COFDM_DEM m_InitDataCOFDM_Condition4[] =
{
    { _AGCIF_MAX,           0xFF },
    { 0x31,                 0x20 },
    { _AGCRF_MAX,           0x00 },
    { 0x33,                 0x00 },
    { _AGCIF_THR,           0x43 },
    { _AGCRF_MIN,           0x00 },
    { _AGCIF_MIN,           0x20 },
    { _BLIND_DUR_LO,        0x00 },
    { 0xF4,                 0x00 },
    { 0xF5,                 0x40 },
    { _AAGC_LCK_DUR,        0x24 },
    { 0xE1,                 0x27 },

    { 0x92,                 0x7F },
    { 0x93,                 0x91 },
    { 0x95,                 0x00 },
    { 0x2B,                 0x33 },
    { _AGCRF_MAX_STEP,      0x2A },
    { 0x2E,                 0x80 },
    { 0x25,                 0x25 },
    { 0x2D,                 0xFF },
    { 0x26,                 0xFF },
    { 0x27,                 0x00 },
    { 0x24,                 0x25 },
    { 0xA4,                 0xFF },
    { 0xA3,                 0x10 }
};
#endif


static U32 _u32SymbolRate;
static U16 _u16QamSelect;
static U8 _u8Inverted;

/* ------------------------------------
    Function Prototypes
   ------------------------------------ */

/***********************************************************************************
  Subject:    Power on initialized function
  Function:   M88DC2800_Initialize
  Parmeter:
  Return:     BOOLEAN
  Remark:
************************************************************************************/
void M88DC2800_Initialize( void )
{
    _u32SymbolRate = 6875;
    _u16QamSelect = 64;
    _u8Inverted = 0;
}

void M88DC2800_InitRegister(void)
{
    U8 RegE3H, RegE4H;
    U8 cAddress;
    U8 cData;
    U8 i;

    for ( i = 0; i < ( sizeof( m_InitDataCOFDM1 ) / sizeof( INIT_DATA_COFDM_DEM ) ); i++ )
    {
        cAddress = m_InitDataCOFDM1[i].cAddress;
        cData = m_InitDataCOFDM1[i].cData;

        if ( FALSE == MDrv_IIC_WriteByte( M88DC2800_devAddr, cAddress, cData ) )
        {
            M88DC2800_DBG( printf( "I2C Error!!! cofdmInit \n" ) );
            return;
        }

    }

    if ( FALSE == MDrv_IIC_ReadByte( M88DC2800_devAddr, 0xE3, &RegE3H ) )
    {
        M88DC2800_DBG( printf( "I2C Error!!! read reg 0xE3 \n" ) );
        return;
    }

    if ( FALSE == MDrv_IIC_ReadByte( M88DC2800_devAddr, 0xE4, &RegE4H ) )
    {
        M88DC2800_DBG( printf( "I2C Error!!! read reg 0xE4 \n" ) );
        return;
    }

    if (((RegE3H & 0xC0) == 0x00) && ((RegE4H & 0xC0) == 0x00))
    {
        for ( i = 0; i < ( sizeof( m_InitDataCOFDM_Condition1 ) / sizeof( INIT_DATA_COFDM_DEM ) ); i++ )
        {
            cAddress = m_InitDataCOFDM_Condition1[i].cAddress;
            cData = m_InitDataCOFDM_Condition1[i].cData;

            if ( FALSE == MDrv_IIC_WriteByte( M88DC2800_devAddr, cAddress, cData ) )
            {
                M88DC2800_DBG( printf( "I2C Error!!! cofdmInit \n" ) );
                return;
            }

        }
    }
    else if (((RegE3H & 0xC0) == 0x80) && ((RegE4H & 0xC0) == 0x40))
    {
        for ( i = 0; i < ( sizeof( m_InitDataCOFDM_Condition2 ) / sizeof( INIT_DATA_COFDM_DEM ) ); i++ )
        {
            cAddress = m_InitDataCOFDM_Condition2[i].cAddress;
            cData = m_InitDataCOFDM_Condition2[i].cData;

            if ( FALSE == MDrv_IIC_WriteByte( M88DC2800_devAddr, cAddress, cData ) )
            {
                M88DC2800_DBG( printf( "I2C Error!!! cofdmInit \n" ) );
                return;
            }

        }
    }
    else if ((RegE3H == 0x80 || RegE3H == 0x81) && (RegE4H == 0x80 || RegE4H == 0x81))
    {
        for ( i = 0; i < ( sizeof( m_InitDataCOFDM_Condition3 ) / sizeof( INIT_DATA_COFDM_DEM ) ); i++ )
        {
            cAddress = m_InitDataCOFDM_Condition3[i].cAddress;
            cData = m_InitDataCOFDM_Condition3[i].cData;

            if ( FALSE == MDrv_IIC_WriteByte( M88DC2800_devAddr, cAddress, cData ) )
            {
                M88DC2800_DBG( printf( "I2C Error!!! cofdmInit \n" ) );
                return;
            }

        }
    }
    else
    {
        for ( i = 0; i < ( sizeof( m_InitDataCOFDM_Condition4 ) / sizeof( INIT_DATA_COFDM_DEM ) ); i++ )
        {
            cAddress = m_InitDataCOFDM_Condition4[i].cAddress;
            cData = m_InitDataCOFDM_Condition4[i].cData;

            if ( FALSE == MDrv_IIC_WriteByte( M88DC2800_devAddr, cAddress, cData ) )
            {
                M88DC2800_DBG( printf( "I2C Error!!! cofdmInit \n" ) );
                return;
            }

        }
    }

    for ( i = 0; i < ( sizeof( m_InitDataCOFDM2 ) / sizeof( INIT_DATA_COFDM_DEM ) ); i++ )
    {
        cAddress = m_InitDataCOFDM2[i].cAddress;
        cData = m_InitDataCOFDM2[i].cData;

        if ( FALSE == MDrv_IIC_WriteByte( M88DC2800_devAddr, cAddress, cData ) )
        {
            M88DC2800_DBG( printf( "I2C Error!!! cofdmInit \n" ) );
            return;
        }

    }
}

void M88DC2800_Config(void)
{
    U32 sym, xtal;
    S32 waiting_time;
    U16 qam;
    U8 inverted;
    U8 RegE3H, RegE4H;

    sym = _u32SymbolRate;
    qam = _u16QamSelect;
    inverted = _u8Inverted;
    xtal = (U32)(FREQ_XTAL/1000);

    M88DC2800_InitRegister();

    M88DC2800_SetSym(sym, xtal);

    M88DC2800_SetQAM(qam);

    M88DC2800_SetTxMode(inverted, 0);      /*    J83A                    */

    #if TS_PARALLEL_OUTPUT
    M88DC2800_Serial_Control(FALSE);
    #else
    M88DC2800_Serial_Control(TRUE);
    #endif

    M88DC2800_SoftReset();

    if ( FALSE == MDrv_IIC_ReadByte( M88DC2800_devAddr, 0xE3, &RegE3H ) )
        return;
    if ( FALSE == MDrv_IIC_ReadByte( M88DC2800_devAddr, 0xE4, &RegE4H ) )
        return;

    if (((RegE3H & 0x80) == 0x80) && ((RegE4H & 0x80) == 0x80))
        waiting_time = 800;
    else
        waiting_time = 500;

    while (waiting_time > 0)
    {
        MsOS_DelayTask( 50 );
        waiting_time -= 50;
        if (M88DC2800_GetLock())
            return;
    }

    #if 1

    if (inverted != 0)
        inverted = 0;
    else
        inverted = 1;


    M88DC2800_SetTxMode(inverted, 0);    /*    J83A                    */
    M88DC2800_SoftReset();

    if ( FALSE == MDrv_IIC_ReadByte( M88DC2800_devAddr, 0xE3, &RegE3H ) )
        return;
    if ( FALSE == MDrv_IIC_ReadByte( M88DC2800_devAddr, 0xE4, &RegE4H ) )
        return;

    if (((RegE3H & 0x80) == 0x80) && ((RegE4H & 0x80) == 0x80))
        waiting_time = 800;
    else
        waiting_time = 500;

    while (waiting_time > 0)
    {
        MsOS_DelayTask( 50 );
        waiting_time -= 50;
        if (M88DC2800_GetLock())
            return;
    }

    #endif
}

/***********************************************
   Set spectrum inversion and J83
   Inverted: 1, inverted; 0, not inverted
   J83: 0, J83A; 1, J83C
 ***********************************************/
BOOLEAN M88DC2800_SetTxMode(U8 inverted,U8 j83)
{
    U8 u8Temp;

    u8Temp = 0;

    if(inverted)
        u8Temp |= BIT3;
    else
        u8Temp &= ~BIT3;

    if(j83)
        u8Temp |= BIT0;
    else
        u8Temp &= ~BIT0;

    if( MDrv_IIC_WriteByte( M88DC2800_devAddr, _J83C_SPEC_INV, u8Temp ) == FALSE )
         return FAIL;

    return 0;
}

/***********************************************
   Set        symbol rate
   sym:        symbol rate, unit: KBaud
   xtal:    unit, KHz
************************************************/
BOOLEAN M88DC2800_SetSym(U32 sym, U32 xtal)
{
    U8    value;
    U8    reg6FH, reg12H;
    float fValue;
    U32    dwValue;
    U8    regE3H, regE4H;


    fValue  = 4294967296.0 * (sym + 10) / xtal;
    dwValue = (U32)fValue;
    if( MDrv_IIC_WriteByte( M88DC2800_devAddr, _SYMB_RATE_4, ((dwValue >> 24) & 0xFF) ) == FALSE )
         return FAIL;
    if( MDrv_IIC_WriteByte( M88DC2800_devAddr, _SYMB_RATE_3, ((dwValue >> 16) & 0xFF) ) == FALSE )
         return FAIL;
    if( MDrv_IIC_WriteByte( M88DC2800_devAddr, _SYMB_RATE_2, ((dwValue >> 8) & 0xFF) ) == FALSE )
         return FAIL;
    if( MDrv_IIC_WriteByte( M88DC2800_devAddr, _SYMB_RATE_1, ((dwValue >> 0) & 0xFF) ) == FALSE )
         return FAIL;



    fValue = 2048.0 * xtal / sym;
    dwValue = (U32)fValue;
    if( MDrv_IIC_WriteByte( M88DC2800_devAddr, _SYMB_RATE_INV2, ((dwValue >> 8) & 0xFF) ) == FALSE )
         return FAIL;
    if( MDrv_IIC_WriteByte( M88DC2800_devAddr, _SYMB_RATE_INV1, ((dwValue >> 0) & 0xFF) ) == FALSE )
         return FAIL;



    if ( MDrv_IIC_ReadByte( M88DC2800_devAddr, _STL_CTRL0, &value ) == FALSE )
    {
        return FAIL;
    }
    if (((dwValue >> 16) & 0x0001) == 0)
        value &= ~BIT7;
    else
        value |= BIT7;
    if( MDrv_IIC_WriteByte( M88DC2800_devAddr, _STL_CTRL0, value ) == FALSE )
         return FAIL;



    if ( MDrv_IIC_ReadByte( M88DC2800_devAddr, 0x89, &value ) == FALSE )
    {
        return FAIL;
    }
    if (sym <= 1800)
        value |= BIT0;
    else
        value &= ~BIT0;
    if( MDrv_IIC_WriteByte( M88DC2800_devAddr, 0x89, value ) == FALSE )
         return FAIL;



    if (sym >= 6700)
    {
        reg6FH = 0x0D;
        reg12H = 0x30;
    }
    else if (sym >= 4000)
    {
        fValue = 22 * 4096 / sym;
        reg6FH = (U8)fValue;
        reg12H = 0x30;
    }
    else if (sym >= 2000)
    {
        fValue = 14 * 4096 / sym;
        reg6FH = (U8)fValue;
        reg12H = 0x20;
    }
    else
    {
        fValue = 7 * 4096 / sym;
        reg6FH = (U8)fValue;
        reg12H = 0x10;
    }

    if( MDrv_IIC_WriteByte( M88DC2800_devAddr, 0x6F, reg6FH ) == FALSE )
         return FAIL;
    if( MDrv_IIC_WriteByte( M88DC2800_devAddr, _DERO_FREQ_STEP, reg12H ) == FALSE )
         return FAIL;



    if ( FALSE == MDrv_IIC_ReadByte( M88DC2800_devAddr, 0xE3, &regE3H ) )
    {
        return FAIL;
    }
    if ( FALSE == MDrv_IIC_ReadByte( M88DC2800_devAddr, 0xE4, &regE4H ) )
    {
        return FAIL;
    }
    if (((regE3H & 0x80) == 0x80) && ((regE4H & 0x80) == 0x80))
    {
        if(sym < 3000)
        {
            if( MDrv_IIC_WriteByte( M88DC2800_devAddr, 0x6C, 0x16 ) == FALSE )
                 return FAIL;
            if( MDrv_IIC_WriteByte( M88DC2800_devAddr, 0x6D, 0x10 ) == FALSE )
                 return FAIL;
            if( MDrv_IIC_WriteByte( M88DC2800_devAddr, 0x6E, 0x18 ) == FALSE )
                 return FAIL;
        }
        else
        {
            if( MDrv_IIC_WriteByte( M88DC2800_devAddr, 0x6C, 0x14 ) == FALSE )
                 return FAIL;
            if( MDrv_IIC_WriteByte( M88DC2800_devAddr, 0x6D, 0x0E ) == FALSE )
                 return FAIL;
            if( MDrv_IIC_WriteByte( M88DC2800_devAddr, 0x6E, 0x36 ) == FALSE )
                 return FAIL;
        }
    }
    else
    {
        if( MDrv_IIC_WriteByte( M88DC2800_devAddr, 0x6C, 0x16 ) == FALSE )
             return FAIL;
        if( MDrv_IIC_WriteByte( M88DC2800_devAddr, 0x6D, 0x10 ) == FALSE )
             return FAIL;
        if( MDrv_IIC_WriteByte( M88DC2800_devAddr, 0x6E, 0x18 ) == FALSE )
             return FAIL;
    }

    return 0;
}

/***********************************************
   Set QAM mode
   Qam: QAM mode, 16, 32, 64, 128, 256
************************************************/
BOOLEAN M88DC2800_SetQAM(U16 qam)
{
    U8 reg00H, reg4AH, reg84H, regC2H, reg44H, reg4CH, reg74H, reg80H, value;

    switch(qam)
    {
        case 16:    // 16 QAM
            reg00H = 0x08;
            reg4AH = 0x0F;
            reg84H = 0x6C;
            regC2H = 0x02;
            reg44H = 0xAA;
            reg4CH = 0x0C;
            reg74H = 0x0E;
            break;
        case 32:    // 32 QAM
            reg00H = 0x18;
            reg4AH = 0xFB;
            reg84H = 0x6C;
            regC2H = 0x02;
            reg44H = 0xAA;
            reg4CH = 0x0C;
            reg74H = 0x0E;
            break;
        case 64:    // 64 QAM
            reg00H = 0x48;
            reg4AH = 0xCD;
            reg84H = 0x6C;
            regC2H = 0x02;
            reg44H = 0xAA;
            reg4CH = 0x0C;
            reg74H = 0x0E;
            break;
        case 128:    // 128 QAM
            reg00H = 0x28;
            reg4AH = 0xF9;
            reg84H = 0x6C;
            regC2H = 0x02;
            reg44H = 0xAA;
            reg4CH = 0x0C;
            reg74H = 0x0E;
            break;
        case 256:    // 256 QAM
            reg00H = 0x38;
            reg4AH = 0xCD;
            reg84H = 0x6C;
            regC2H = 0x01;
            reg44H = 0xAA;
            reg4CH = 0x0E;
            if ( FALSE == MDrv_IIC_ReadByte( M88DC2800_devAddr, _VER_SRST, &reg80H ) )
            {
                return FAIL;
            }
            if(reg80H < 0x06)
            {
                reg74H = 0x0E;
            }
            else
            {
                reg74H = 0x12;
            }
            break;
        default:    // 64 QAM
            reg00H = 0x48;
            reg4AH = 0xCD;
            reg84H = 0x6C;
            regC2H = 0x02;
            reg44H = 0xAA;
            reg4CH = 0x0C;
            reg74H = 0x0E;
            break;
    }
    if( MDrv_IIC_WriteByte( M88DC2800_devAddr, _QAM_SEL, reg00H ) == FALSE )
         return FAIL;

    if ( FALSE == MDrv_IIC_ReadByte( M88DC2800_devAddr, _AGC_POL_INV, &value ) )
    {
        return FAIL;
    }
    value |= BIT3;
    if( MDrv_IIC_WriteByte( M88DC2800_devAddr, _AGC_POL_INV, value ) == FALSE )
         return FAIL;
    if( MDrv_IIC_WriteByte( M88DC2800_devAddr, _GPPWM_CORN_RAT_HI, 0xFF ) == FALSE )
         return FAIL;
    if( MDrv_IIC_WriteByte( M88DC2800_devAddr, _GPPWM_CORN_RAT_LO, reg4AH ) == FALSE )
         return FAIL;
    value &= 0xF7;
    if( MDrv_IIC_WriteByte( M88DC2800_devAddr, _AGC_POL_INV, value ) == FALSE )
         return FAIL;

    if( MDrv_IIC_WriteByte( M88DC2800_devAddr, _GRST_FMT, reg84H ) == FALSE )
         return FAIL;
    if( MDrv_IIC_WriteByte( M88DC2800_devAddr, _FMT_2, regC2H ) == FALSE )
         return FAIL;
    if( MDrv_IIC_WriteByte( M88DC2800_devAddr, _AAGC_GN, reg44H ) == FALSE )
         return FAIL;
    if( MDrv_IIC_WriteByte( M88DC2800_devAddr, _ADC_TM_COEF, reg4CH ) == FALSE )
         return FAIL;
    if( MDrv_IIC_WriteByte( M88DC2800_devAddr, _DAGC_LP_GN3, reg74H ) == FALSE )
         return FAIL;

    return 0;
}

/***********************************************
 Soft reset M88DC2000
 Reset the internal status of each funtion block,
 not reset the registers.
************************************************/
BOOLEAN M88DC2800_SoftReset(void)
{
    if( MDrv_IIC_WriteByte( M88DC2800_devAddr, _VER_SRST, 0x01 ) == FALSE )
         return FAIL;
    if( MDrv_IIC_WriteByte( M88DC2800_devAddr, _LCK, 0x00 ) == FALSE )
         return FAIL;
    MsOS_DelayTask( 1 );
    if( MDrv_IIC_WriteByte( M88DC2800_devAddr, _VER_SRST, 0x00 ) == FALSE )
         return FAIL;

    return 0;
}

BOOLEAN M88DC2800_RepeatControl ( BOOLEAN bEnable )
{
    U8 u8Temp;

    if( MDrv_IIC_ReadByte( M88DC2800_devAddr, _INT_LCK_SRC, &u8Temp ) == FALSE )
    {
        return FAIL;
    }

    if(bEnable)
    {
        if( MDrv_IIC_WriteByte( M88DC2800_devAddr, _INT_LCK_SRC, u8Temp | 0x80 ) == FALSE )
            return FAIL;
    }
    else
    {
        if( MDrv_IIC_WriteByte( M88DC2800_devAddr, _INT_LCK_SRC, u8Temp & 0x7F ) == FALSE )
            return FAIL;
    }

    return PASS;
}

/***********************************************
   Set the type of MPEG/TS interface
   type: 1, serial format; 0, parallel format
************************************************/
BOOLEAN M88DC2800_Serial_Control(BOOLEAN bEnable)
{
    if(bEnable)
    {
        if( MDrv_IIC_WriteByte( M88DC2800_devAddr, _GRST_FMT, 0x6A ) == FALSE )
             return FAIL;
        if( MDrv_IIC_WriteByte( M88DC2800_devAddr, _FMT_0, 0x47 ) == FALSE )    //Serial Output
             return FAIL;
        if( MDrv_IIC_WriteByte( M88DC2800_devAddr, _SLEEP_MD, 0x02 ) == FALSE )
             return FAIL;
    }
    else
    {
        if( MDrv_IIC_WriteByte( M88DC2800_devAddr, _GRST_FMT, 0x6C ) == FALSE )
             return FAIL;
        if( MDrv_IIC_WriteByte( M88DC2800_devAddr, _FMT_0, 0x43 ) == FALSE )    //Parallel Output
             return FAIL;
        if( MDrv_IIC_WriteByte( M88DC2800_devAddr, _SLEEP_MD, 0x06 ) == FALSE )
             return FAIL;
    }

    return 0;
}

/***********************************************
   Get AGC lock status
   returned 1 when locked;0 when unlocked
************************************************/
U8 M88DC2800_GetAgcLock(void)
{
    U8 u8Temp;

    if( MDrv_IIC_ReadByte( M88DC2800_devAddr, _AAGC_ACQ_CLR, &u8Temp ) == FALSE )
    {
        return FAIL;
    }

    if ((u8Temp&0x08)==0x08)
        return TRUE;
    else
        return FALSE;
}

/***********************************************
   Get lock status
   returned 1 when locked;0 when unlocked
************************************************/
BOOLEAN M88DC2800_GetLock(void)
{
    U8 u8Temp;

    if( MDrv_IIC_ReadByte( M88DC2800_devAddr, _VER_SRST, &u8Temp ) == FALSE )
    {
        return FAIL;
    }

    if (u8Temp < 0x06)
    {
        if( MDrv_IIC_ReadByte( M88DC2800_devAddr, _CNT_HLD_CLR, &u8Temp ) == FALSE )
        {
            return FAIL;
        }
        if((u8Temp&0x80) != 0x80)
            return FALSE;

        if( MDrv_IIC_ReadByte( M88DC2800_devAddr, _SYNC_1, &u8Temp ) == FALSE )
        {
            return FAIL;
        }
        if((u8Temp&0x23) != 0x03)
            return FALSE;

        if( MDrv_IIC_ReadByte( M88DC2800_devAddr, _AAGC_ACQ_CLR, &u8Temp ) == FALSE )
        {
            return FAIL;
        }
        if((u8Temp&0x08) != 0x08)
            return FALSE;

        return TRUE;
    }
    else
    {
        if( MDrv_IIC_ReadByte( M88DC2800_devAddr, _INT, &u8Temp ) == FALSE )
        {
            return FAIL;
        }
        if((u8Temp&0x08) == 0x08)
            return TRUE;
        else
            return FALSE;
    }
}

/***********************************************
   Get SNR (signal noise ratio)
************************************************/
U8 M88DC2800_GetSNR(void)
{
    const U32 mes_log[] =
    {
        0,        3010,    4771,    6021,     6990,    7781,    8451,    9031,    9542,    10000,
        10414,    10792,    11139,    11461,    11761,    12041,    12304,    12553,    12788,    13010,
        13222,    13424,    13617,    13802,    13979,    14150,    14314,    14472,    14624,    14771,
        14914,    15052,    15185,    15315,    15441,    15563,    15682,    15798,    15911,    16021,
        16128,    16232,    16335,    16435,    16532,    16628,    16721,    16812,    16902,    16990,
        17076,    17160,    17243,    17324,    17404,    17482,    17559,    17634,    17709,    17782,
        17853,    17924,    17993,    18062,    18129,    18195,    18261,    18325,    18388,    18451,
        18513,    18573,    18633,    18692,    18751,    18808,    18865,    18921,    18976,    19031
    };
    U32    snr;
    U8    i;
    U32    mse;
    U8 u8Temp,u8Temp2;

    if( MDrv_IIC_ReadByte( M88DC2800_devAddr, _SYNC_1, &u8Temp ) == FALSE )
    {
        return FAIL;
    }
    if((u8Temp&0x23) != 0x03)
        return FALSE;

    mse = 0;
    for (i=0; i<30; i++)
    {
        if( MDrv_IIC_ReadByte( M88DC2800_devAddr, _MSE_HI, &u8Temp ) == FALSE )
        {
            return FAIL;
        }
        if( MDrv_IIC_ReadByte( M88DC2800_devAddr, _MSE_LO, &u8Temp2 ) == FALSE )
        {
            return FAIL;
        }
        mse += (u8Temp << 8) + u8Temp2;
    }
    mse /= 30;
    if (mse > 80)
        mse = 80;



    switch (_u16QamSelect)
    {
        case 16:    snr = 34080;    break;    /*    16QAM                */
        case 32:    snr = 37600;    break;    /*    32QAM                */
        case 64:    snr = 40310;    break;    /*    64QAM                */
        case 128:    snr = 43720;    break;    /*    128QAM                */
        case 256:    snr = 46390;    break;    /*    256QAM                */
        default:    snr = 40310;    break;
    }


    snr -= mes_log[mse-1];                    /*    C - 10*log10(MSE)    */
    snr /= 1000;
    if (snr > 0xff)
        snr = 0xff;


    return (U8)snr;
}

/***********************************************
   Get signal strength
************************************************/
FUNCTION_RESULT M88DC2800_GetSignalStrength(WORD *strength)
{
    U8    SignalStrength = 0;
    U8 u8Temp,u8Temp2;

    if( MDrv_IIC_ReadByte( M88DC2800_devAddr, _AAGC_ACQ_CLR, &u8Temp ) == FALSE )
    {
        return E_RESULT_FAILURE;
    }
    if ((u8Temp&0x08) == 0x08)
    {
        if( MDrv_IIC_ReadByte( M88DC2800_devAddr, 0xE3, &u8Temp ) == FALSE )
        {
            return E_RESULT_FAILURE;
        }
        if( MDrv_IIC_ReadByte( M88DC2800_devAddr, 0xE4, &u8Temp2 ) == FALSE )
        {
            return E_RESULT_FAILURE;
        }

        if (((u8Temp & 0xC0) == 0x00) && ((u8Temp2 & 0xC0) == 0x00))
        {
            if( MDrv_IIC_ReadByte( M88DC2800_devAddr, _SYMB_RATE_1, &u8Temp ) == FALSE )
            {
                return E_RESULT_FAILURE;
            }
            if( MDrv_IIC_ReadByte( M88DC2800_devAddr, _SYMB_RATE_2, &u8Temp2 ) == FALSE )
            {
                return E_RESULT_FAILURE;
            }
            SignalStrength = 255 - ((u8Temp >> 1) + (u8Temp2 >> 1));
        }
        else
        {
            if( MDrv_IIC_ReadByte( M88DC2800_devAddr, _AGCRF_CUR, &u8Temp ) == FALSE )
            {
                return E_RESULT_FAILURE;
            }
            if( MDrv_IIC_ReadByte( M88DC2800_devAddr, _AGCIF_CUR, &u8Temp2 ) == FALSE )
            {
                return E_RESULT_FAILURE;
            }
            SignalStrength = 255 - ((u8Temp >> 1) + (u8Temp2 >> 1));
        }

    }

    *strength = SignalStrength;

    return E_RESULT_SUCCESS;
}

/***********************************************
   TS output Enable
   flag = 1, enable ts output ; 0 disable ts output
************************************************/
BOOLEAN M88DC2800_TSOut_Control(BOOLEAN bEnable)
{
    U8 Reg84H;

    if ( FALSE == MDrv_IIC_ReadByte( M88DC2800_devAddr, _GRST_FMT, &Reg84H ) )
        return FAIL;

    if(bEnable)
        Reg84H &= ~BIT4;
    else
        Reg84H |= BIT4;

    if( MDrv_IIC_WriteByte( M88DC2800_devAddr, _GRST_FMT, Reg84H ) == FALSE )
         return FAIL;

    return PASS;
}

#undef _M88DC2800_C_
