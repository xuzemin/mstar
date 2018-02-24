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
// (MStar Confidential Information!�L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MDEV_COFDM_DEMODULATOR_C_
#define _MDEV_COFDM_DEMODULATOR_C_

//******************************************************************************

#include "Board.h"


#if (ENABLE_DVB_T2)
#include "apiDMX.h"
#include "drvPCMCIA.h"
#include "drvSYS.h"
//#include "INTERN_T2_cofdm_demodulator.h"
#include "demodulator_T2.h"

#include "drvIIC.h"
#include "debug.h"
#include "MApp_Scan.h"
#include "msAPI_Memory.h"
//#include "MMAP_DTVMM_MILAN_128_MIPS_CI_T2.h"
#ifdef HW_PROFILE
#include "profile_helper/ProfileHelper.h"
#endif

/*
#if USE_UTOPIA
#include "drvDMD_INTERN_DVBT.h"
#include "drvDMD_INTERN_DVBC.h"
#else
#include "INTERN_DVBT.h"
#include "INTERN_DVBC.h"
#endif
*/
#include "drvDMD_INTERN_DVBT2.h"
#include "drvDMD_VD_MBX.h"
#include "mapp_si.h"

#if 0//FAST_TURN_ON
#include "ICE_latest.h"
#endif

//******************************************************************************

#define DVBT_TPS_timeout    700
#define DVBT_FEC_timeout    6000
#define FRONTEND_DEMOD_IQ_SWAP      0
#define FRONTEND_DEMOD_IQ_TYPE      0


#define INTERNAL_DVBT2_MEM_START    DEMOD_DVBT2_BUF_ADR

#if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) \
   ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA) \
   )
    #define INTERNAL_DVBT2_TDI_ADR      (INTERNAL_DVBT2_MEM_START)
    #define INTERNAL_DVBT2_TDI_SIZE     (5448*1024) // 5448k

    #define INTERNAL_DVBT2_EQ_ADR       (INTERNAL_DVBT2_TDI_ADR + INTERNAL_DVBT2_TDI_SIZE)
    #define INTERNAL_DVBT2_EQ_SIZE      (600*1024) // 600K

    #define INTERNAL_DVBT2_DJB_ADR      (INTERNAL_DVBT2_EQ_ADR + INTERNAL_DVBT2_EQ_SIZE)
    #define INTERNAL_DVBT2_DJB_SIZE     (768*1024) // 768k

    //#define INTERNAL_DVBT2_FW_ADR       ALIGNED_VALUE(INTERNAL_DVBT2_DJB_ADR, 0x8000)
    #define INTERNAL_DVBT2_FW_ADR       (INTERNAL_DVBT2_DJB_ADR + INTERNAL_DVBT2_DJB_SIZE)
    #define INTERNAL_DVBT2_FW_SIZE      (32*1024) // 32k

    #define INTERNAL_DVBT2_MEM_END      (INTERNAL_DVBT2_FW_ADR+INTERNAL_DVBT2_FW_SIZE)

// FW code mem address must be 0x8000
#if( (INTERNAL_DVBT2_FW_ADR&0xFFFF) != 0x8000 )
    #error "T2 Demod FW mem addr must be 0x8000!"
#endif

#elif( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) \
    )

    #define INTERNAL_DVBT2_TDI_ADR      (INTERNAL_DVBT2_MEM_START)
    #define INTERNAL_DVBT2_TDI_SIZE     (3200*1024) // 3200k

    #define INTERNAL_DVBT2_EQ_ADR       (INTERNAL_DVBT2_TDI_ADR + INTERNAL_DVBT2_TDI_SIZE)
    #define INTERNAL_DVBT2_EQ_SIZE      (600*1024) // 600K

    #define INTERNAL_DVBT2_GAP_ADR      (INTERNAL_DVBT2_EQ_ADR + INTERNAL_DVBT2_EQ_SIZE)
    #define INTERNAL_DVBT2_GAP_SIZE     (60*1024) // 60k

    #define INTERNAL_DVBT2_FW_ADR       (INTERNAL_DVBT2_GAP_ADR + INTERNAL_DVBT2_GAP_SIZE)
    #define INTERNAL_DVBT2_FW_SIZE      (64*1024) // 64k

    #define INTERNAL_DVBT2_DJB_ADR      (INTERNAL_DVBT2_FW_ADR + INTERNAL_DVBT2_FW_SIZE)
    #define INTERNAL_DVBT2_DJB_SIZE     (600*1024) // 600k

    #define INTERNAL_DVBT2_MEM_END      (INTERNAL_DVBT2_DJB_ADR+INTERNAL_DVBT2_DJB_SIZE)

// FW code mem address must be 0x5000
#if( (INTERNAL_DVBT2_FW_ADR&0xFFFF) != 0x5000 )
    #error "T2 Demod FW mem addr must be 0x5000!"
#endif
#endif


// Check Demod total  mem size
#if( (INTERNAL_DVBT2_MEM_END-INTERNAL_DVBT2_MEM_START) > DEMOD_DVBT2_BUF_LEN)
    #error "T2 Demod mem usage is over range!"
#endif

// TDI mem addr must align to 64K
#if( (INTERNAL_DVBT2_TDI_ADR&0xFFFF) != 0 )
    #error "T2 Demod TDI mem addr must align to 64K!"
#endif

// EQ mem addr must align to 4K
#if( (INTERNAL_DVBT2_EQ_ADR&0xFFF) != 0 )
    #error "T2 Demod EQ mem addr must align to 4K!"
#endif

// DJB mem addr must align to 4K
#if( (INTERNAL_DVBT2_DJB_ADR&0xFFF) != 0 )
    #error "T2 Demod DJB mem addr must align to 4K!"
#endif


//******************************************************************************

//static CUR_COFDM_CFG eCurCofdmCfg = E_COFDM_INVALID;
static MS_BOOL bDemodDTVInitOK = FALSE;
static MS_BOOL bTunerInitOK = FALSE;
//static ST_MAPI_DEMODULATOR_FUN *pstDvbt2Drv;
static MS_BOOL bDvbt2DemodExist = FALSE;
static MS_U8 g_plp_id   = 0xff;
static MS_U8 g_group_id = 0xff;

#define ATV_PAL_I                   FALSE
#define ATV_PAL_BG                  TRUE
#define DEFAULT_CCI_ATV_SYSTEM      ATV_PAL_BG

#if 0//FAST_TURN_ON
extern ICE_LatestSwParams ice_last_sw_params;
#endif
//extern ST_MAPI_DEMODULATOR_FUN* DeviceDemodCreate(void);

//******************************************************************************
//#define _DEBUG_V
#ifndef _DEBUG_V
//#define printf(...)         ((void)0)
#endif

#define COFDM_DBG(x)        //x

/*static MAPI_BOOL DeviceDemodCreate(void)
{
    return MAPI_TRUE;
}

static MAPI_BOOL Connect(void)
{
    return MAPI_TRUE;
}
static MAPI_BOOL Disconnect(void)
{
    return MAPI_TRUE;
}
static void Reset(void)
{

}
*/

/*MAPI_BOOL Set_PowerOn(void)
{
    return TRUE;
}*/

/*MAPI_BOOL Set_PowerOff(void)
{
    return TRUE;
}*/


/***************************************************************************************/
#if 1
//#define COFDMDMD_MUTEX_TIMEOUT       (2000)
//static MS_BOOL KritiDMD_Init = FALSE;
//static MS_S32 _s32MutexId = -1;
//static EN_DEMOD_TYPE eCurDemodType = E_DEMOD_TYPE_T;
#if (FRONTEND_TUNER_TYPE == SILAB_2151_TUNER)
#define IF_FREQUENCY  5000//KHz for demod restart&init
#else
#define IF_FREQUENCY  5000//KHz for demod restart&init
#endif
#define FS_FREQUENCY 24000
#define usleep(x)                   MsOS_DelayTask(x/1000)

MS_S32 _u32LockTimeMax;
//DEMOD_MS_INIT_PARAM Kriti_DVBT_INIT_PARAM;
static DMD_RFAGC_SSI TUNER_RfagcSsi[] =
{
    {0,    0xff},
    {0,    0xff},

};

/*static DMD_IFAGC_SSI TUNER_IfagcSsi_LoRef[] =
{
//current agc ref setting:150
    {10.0,     0x00},  //default setting
    {10.0,     0x00},  //default setting
    {-00.0,    0x31},
    {-05.0,    0x42},
    {-10.0,    0x57},
    {-15.0,    0x6e},
    {-20.0,    0x80},
    {-25.0,    0x87},
    {-30.0,    0x8d},
    {-35.0,    0x93},
    {-40.0,    0x98},
    {-45.0,    0x9d},
    {-50.0,    0xa3},
    {-55.0,    0xa8},
    {-60.0,    0xad},
    {-65.0,    0xb2},
    {-70.0,    0xb7},
    {-75.0,    0xbc},
    {-80.0,    0xc1},
    {-85.0,    0xc6},
    {-90.0,    0xff}, //end setting
};*/

/*static DMD_IFAGC_SSI TUNER_IfagcSsi_HiRef[] =
{
    { -48,   0x3A},
    { -49,   0x3B},
    { -50,   0x3C},
    { -51,   0x3E},
    { -52,   0x40},
    { -53,   0x43},
    { -54,   0x45},
    { -55,   0x47},
    { -56,   0x49},
    { -57,   0x4C},
    { -58,   0x4f},
    { -59,   0x51},
    { -60,   0x54},
    { -61,   0x56},
    { -62,   0x59},
    { -63,   0x5C},
    { -64,   0x5F},
    { -65,   0x62},
    { -66,   0x65},
    { -67,   0x69},
    { -68,   0x6E},
    { -69,   0x73},
    { -70,   0x78},
    { -71,   0x7F},
    { -72,   0x85},
    { -73,   0x8b},
    { -74,   0x9c},
    { -85,   0xc0},
    { -99,   0xFF},
};*/

static DMD_IFAGC_ERR TUNER_IfagcErr_LoRef[] =
{
    {0.00,        0x0A},
    {0.00,        0xFF},

};

static DMD_IFAGC_ERR TUNER_IfagcErr_HiRef[] =
{
    {0.00,        0x2D},
    {0.00,        0xFF},        // stopper
};
#if 0
static DMD_SQI_CN_NORDIGP1 DvbtSqiCnNordigP1[] =
{
    {_QPSK,  _CR1Y2, 5.1 },
    {_QPSK,  _CR2Y3, 6.9 },
    {_QPSK,  _CR3Y4, 7.9 },
    {_QPSK,  _CR5Y6, 8.9 },
    {_QPSK,  _CR7Y8, 9.7 },

    {_16QAM, _CR1Y2, 10.8},
    {_16QAM, _CR2Y3, 13.1},
    {_16QAM, _CR3Y4, 12.2},
    {_16QAM, _CR5Y6, 15.6},
    {_16QAM, _CR7Y8, 16.0},

    {_64QAM, _CR1Y2, 16.5},
    {_64QAM, _CR2Y3, 16.3},
    {_64QAM, _CR3Y4, 17.8},
    {_64QAM, _CR3Y4, 21.2},
    {_64QAM, _CR5Y6, 21.6},
    {_64QAM, _CR7Y8, 22.5},
};

#endif
static DMD_T2_SQI_CN_NORDIGP1 Dvbt2SqiCnNordigP1[] =
{
    {_T2_QPSK, _T2_CR1Y2, 3.5},
    {_T2_QPSK, _T2_CR3Y5, 4.7},
    {_T2_QPSK, _T2_CR2Y3, 5.6},
    {_T2_QPSK, _T2_CR3Y4, 6.6},
    {_T2_QPSK, _T2_CR4Y5, 7.2},
    {_T2_QPSK, _T2_CR5Y6, 7.7},

    {_T2_16QAM, _T2_CR1Y2, 8.7},
    {_T2_16QAM, _T2_CR3Y5, 10.1},
    {_T2_16QAM, _T2_CR2Y3, 11.4},
    {_T2_16QAM, _T2_CR3Y4, 12.5},
    {_T2_16QAM, _T2_CR4Y5, 13.3},
    {_T2_16QAM, _T2_CR5Y6, 13.8},

    {_T2_64QAM, _T2_CR1Y2, 13.0},
    {_T2_64QAM, _T2_CR3Y5, 14.8},
    {_T2_64QAM, _T2_CR2Y3, 16.2},
    {_T2_64QAM, _T2_CR3Y4, 17.7},
    {_T2_64QAM, _T2_CR4Y5, 18.7},
    {_T2_64QAM, _T2_CR5Y6, 19.4},

    {_T2_256QAM, _T2_CR1Y2, 17.0},
    {_T2_256QAM, _T2_CR3Y5, 19.4},
    {_T2_256QAM, _T2_CR2Y3, 20.8},
    {_T2_256QAM, _T2_CR3Y4, 22.9},
    {_T2_256QAM, _T2_CR4Y5, 24.3},
    {_T2_256QAM, _T2_CR5Y6, 25.1},
};
/*
static MS_U8 u8DMD_DVBT_InitExt[]={ 4, // version
                                        0, // reserved
                                        0x15, // TS_CLK
                                        1 , // RFAGC tristate control default value, 1:trisate 0:non-tristate,never modify unless you know the meaning
                                        (MS_U8)(IF_FREQUENCY>>24), // IF Frequency
                                        (MS_U8)(IF_FREQUENCY>>16),
                                        (MS_U8)(IF_FREQUENCY>>8),
                                        (MS_U8)(IF_FREQUENCY>>0),
                                        (MS_U8)(24000>>24), // FS Frequency
                                        (MS_U8)(24000>>16),
                                        (MS_U8)(24000>>8),
                                        (MS_U8)(24000>>0),
                                        FRONTEND_DEMOD_IQ_SWAP, // IQ Swap
                                        FRONTEND_DEMOD_IQ_TYPE, // u8ADCIQMode : 0=I path, 1=Q path, 2=both IQ
                                        0, // u8PadSel : 0=Normal, 1=analog pad
                                        0, // bPGAEnable : 0=disable, 1=enable
                                        5, // u8PGAGain : default 5
                                        (MS_U8)(DVBT_TPS_timeout>>8), // TPS timeout 700ms~
                                        (MS_U8)(DVBT_TPS_timeout>>0),
                                        (MS_U8)(DVBT_FEC_timeout>>8), // FEC timeout 6000ms~
                                        (MS_U8)(DVBT_FEC_timeout>>0),
                                  };

static MS_U8 u8DMD_DVBT_DSPRegInitExt[]={ 1, // version, should be matched with library
                                                0, // reserved

                                                E_DMD_DVBT_CFG_FC_L,    // Addr_L
                                                E_DMD_DVBT_CFG_FC_L>>8, // Addr_H
                                                0xFF, // Mask
                                                0x88,
                                                E_DMD_DVBT_CFG_FC_H,    // Addr_L
                                                E_DMD_DVBT_CFG_FC_H>>8, // Addr_H
                                                0xFF, // Mask
                                                0x13,
                                                E_DMD_DVBT_CFG_IQ_SWAP,    // Addr_L
                                                E_DMD_DVBT_CFG_IQ_SWAP>>8, // Addr_H
                                                0xFF, // Mask
                                                0x01, // 0x00=I path, 0x01=Q path
}; // Value
*/
static MS_U8 u8DMD_DVBT2_InitExt[]={ 3, // version
                                        0, // reserved
                                        0x15, // TS_CLK
                                        1 , // RFAGC tristate control default value, 1:trisate 0:non-tristate,never modify unless you know the meaning
                                        (MS_U8)(IF_FREQUENCY>>24), // IF Frequency
                                        (MS_U8)(IF_FREQUENCY>>16),
                                        (MS_U8)(IF_FREQUENCY>>8),
                                        (MS_U8)(IF_FREQUENCY>>0),
                                        (MS_U8)(24000>>24), // FS Frequency
                                        (MS_U8)(24000>>16),
                                        (MS_U8)(24000>>8),
                                        (MS_U8)(24000>>0),
                                        FRONTEND_DEMOD_IQ_TYPE, // u8ADCIQMode : 0=I path, 1=Q path, 2=both IQ
                                        0, // u8PadSel : 0=Normal, 1=analog pad
                                        0, // bPGAEnable : 0=disable, 1=enable
                                        5, // u8PGAGain : default 5
                                        (MS_U8)(DVBT_TPS_timeout>>8), // P1 timeout 700ms~
                                        (MS_U8)(DVBT_TPS_timeout>>0),
                                        (MS_U8)(DVBT_FEC_timeout>>8), // FEC timeout 6000ms~
                                        (MS_U8)(DVBT_FEC_timeout>>0),
                                  };
#if (FRONTEND_TUNER_TYPE == SILAB_2151_TUNER)
static MS_U8 u8DMD_DVBT2_DSPRegInitExt[]={ 1, // version, should be matched with library
                                                0, // reserved

                                                E_DMD_T2_FC_L,    // Addr_L
                                                E_DMD_T2_FC_L>>8, // Addr_H
                                                0xFF, // Mask
                                                0x88,
                                                E_DMD_T2_FC_H,    // Addr_L
                                                E_DMD_T2_FC_H>>8, // Addr_H
                                                0xFF, // Mask
                                                0x13,
                                                E_DMD_T2_AGC_REF,	//brown agc_ref
                                                E_DMD_T2_AGC_REF>>8,
                                                0xFF,
                                                0x70,

}; // Value
#else
static MS_U8 u8DMD_DVBT2_DSPRegInitExt[]={ 1, // version, should be matched with library
                                                0, // reserved

                                                E_DMD_T2_FC_L,    // Addr_L
                                                E_DMD_T2_FC_L>>8, // Addr_H
                                                0xFF, // Mask
                                                0x88,
                                                E_DMD_T2_FC_H,    // Addr_L
                                                E_DMD_T2_FC_H>>8, // Addr_H
                                                0xFF, // Mask
                                                0x13,
}; // Value
#endif
#endif
#if 0
CUR_COFDM_CFG mdev_Get_Current_DEMOD_TYPE(void)
{
    return eCurCofdmCfg;
}

void mdev_Set_Current_DEMOD_TYPE(CUR_COFDM_CFG sDemodType)
{
    printf("\r\nmdev_Set_Current_DEMOD_TYPE=0x%x\n", sDemodType);
    eCurCofdmCfg=sDemodType;
}
#endif

MS_BOOL mdev_Cofdm_MSB123X_Ready(void)
{
     return TRUE;//bDvbt2DemodExist;
}

MS_BOOL mdev_Cofdm_MSB123X_TriState(MS_BOOL bSetHiZ)
{
#if 1
    bSetHiZ = bSetHiZ;
    return TRUE;

#else
    MS_BOOL bRet=TRUE;

    if((pstDvbt2Drv->bMSB123X_Ready)==FALSE && mdev_Cofdm_MSB123X_Ready())
    {
        pstDvbt2Drv->Connect(E_DEVICE_DEMOD_DVB_T2);
        bRet = pstDvbt2Drv->Power_On_Initialization();
    }

    if((pstDvbt2Drv->bMSB123X_Ready)==TRUE)
    {
        if(bSetHiZ==TRUE)
        {
            bRet &= pstDvbt2Drv->ExtendCmd(0x80, FALSE, 0, NULL);//Turn off extend demod IF AGC
            bRet &= pstDvbt2Drv->ExtendCmd(0x81, FALSE, 0, NULL);//Turn off extend demod TS out
        }
        else
        {
            bRet &= pstDvbt2Drv->ExtendCmd(0x80, TRUE, 0, NULL);//Turn on extend demod IF AGC
            bRet &= pstDvbt2Drv->ExtendCmd(0x81, TRUE, 0, NULL);//Turn on extend demod TS out
        }
    }
    return bRet;
#endif
}

MS_BOOL  mdev_CofdmDeviceQuery( void )
{
#if 1
    return TRUE;

#else
    MS_U8 u8Data;

    if (MDrv_IIC_ReadByte(DEMOD_SLAVE_ID, 0, &u8Data) == FALSE)
    {//Fail
        printf("MSB1231 NO exist\n");
        return FALSE;
    }
    else
    {//Success
        printf("MSB1231 exist \n");
        return TRUE;
    }
#endif
}

void mdev_CofdmHWireReset(void)
{
    // hard-wire reset pin
    //Demodulator_OFF();
    //OS_DELAY_TASK(10);
    //Demodulator_ON();
}

static BOOL s_Intern_T2_InitDone = 0;

void mdev_CofdmInit(void)
{
#if 0
    MS_BOOL ret = FALSE;

    if (_s32MutexId < 0)
    {
        _s32MutexId = MsOS_CreateMutex(E_MSOS_FIFO, "OfDmd_Mutex", MSOS_PROCESS_SHARED);

        if (_s32MutexId < 0)
        {
            GEN_EXCEP;
            return FALSE;
        }

    }

    //if(NULL == pParam)
    //    return FALSE;

    //Kriti_DVBT_INIT_PARAM.pstTunertab = pParam->pstTunertab;
    MDrv_SYS_DMD_VD_MBX_Init();


    MDrv_SAR_Kpd_Init();


    if(mdev_Get_Current_DEMOD_TYPE() == E_COFDM_INTERNAL_DVBT2)
    {
        ret = _InitInternalDVBT2();
    }
    else if(mdev_Get_Current_DEMOD_TYPE() == E_COFDM_INTERNAL_DVBT)
    {
        ret = _InitInternalDVBT();
    }

    if(ret == TRUE)
    {
//        KritiDMD_Init = TRUE;
    }
     //DMD_DBG(("Kriti Internal DMD init OK\n"));
    return ret;
#else


    printf(" mdev_CofdmInit()\n");

    mdev_CofdmHWireReset();

    //pstDvbt2Drv = DeviceDemodCreate();
    //eCurCofdmCfg = E_COFDM_INVALID;
    bDvbt2DemodExist = mdev_CofdmDeviceQuery(); //check MSB1231 I2C first and once

#endif

    s_Intern_T2_InitDone = TRUE;
}

/*
void mdev_Write_Demod_Imux(void)
{
}
*/

static MS_BOOL mdev_CofdmPowerOnInitialization(CUR_COFDM_CFG eSetCofdmCfg)
{

#if 1

    MS_BOOL bret = TRUE;
    DMD_DVBT2_InitData sDMD_DVBT2_InitData;
    eSetCofdmCfg = eSetCofdmCfg;

    printf("mdev_CofdmPowerOnInitialization()\n");

    // tuner parameter
    sDMD_DVBT2_InitData.u8SarChannel=0xFF; // 0xFF means un-connected //alex_tung###//==>To fix latch
    sDMD_DVBT2_InitData.pTuner_RfagcSsi=TUNER_RfagcSsi;
    sDMD_DVBT2_InitData.u16Tuner_RfagcSsi_Size=sizeof(TUNER_RfagcSsi)/sizeof(DMD_RFAGC_SSI);
    sDMD_DVBT2_InitData.pTuner_IfagcSsi_LoRef=NULL; // TUNER_IfagcSsi_LoRef;
    sDMD_DVBT2_InitData.u16Tuner_IfagcSsi_LoRef_Size=NULL; // sizeof(TUNER_IfagcSsi_LoRef)/sizeof(DMD_IFAGC_SSI);
    sDMD_DVBT2_InitData.pTuner_IfagcSsi_HiRef=NULL; // TUNER_IfagcSsi_HiRef;
    sDMD_DVBT2_InitData.u16Tuner_IfagcSsi_HiRef_Size=NULL; // sizeof(TUNER_IfagcSsi_HiRef)/sizeof(DMD_IFAGC_SSI);
    sDMD_DVBT2_InitData.pTuner_IfagcErr_LoRef=TUNER_IfagcErr_LoRef;
    sDMD_DVBT2_InitData.u16Tuner_IfagcErr_LoRef_Size=sizeof(TUNER_IfagcErr_LoRef)/sizeof(DMD_IFAGC_SSI);
    sDMD_DVBT2_InitData.pTuner_IfagcErr_HiRef=TUNER_IfagcErr_HiRef;
    sDMD_DVBT2_InitData.u16Tuner_IfagcErr_HiRef_Size=sizeof(TUNER_IfagcErr_HiRef)/sizeof(DMD_IFAGC_SSI);
    sDMD_DVBT2_InitData.pSqiCnNordigP1=Dvbt2SqiCnNordigP1;
    sDMD_DVBT2_InitData.u16SqiCnNordigP1_Size=sizeof(Dvbt2SqiCnNordigP1)/sizeof(DMD_SQI_CN_NORDIGP1);

    // register init
    sDMD_DVBT2_InitData.u8DMD_DVBT2_DSPRegInitExt=u8DMD_DVBT2_DSPRegInitExt; // TODO use system variable type
    sDMD_DVBT2_InitData.u8DMD_DVBT2_DSPRegInitSize=(sizeof(u8DMD_DVBT2_DSPRegInitExt)-2)/4;
    sDMD_DVBT2_InitData.u8DMD_DVBT2_InitExt=u8DMD_DVBT2_InitExt; // TODO use system variable type
    sDMD_DVBT2_InitData.u32EqStartAddr = (MS_U32)INTERNAL_DVBT2_EQ_ADR;
    sDMD_DVBT2_InitData.u32TdiStartAddr= (MS_U32)INTERNAL_DVBT2_TDI_ADR;
    sDMD_DVBT2_InitData.u32DjbStartAddr= (MS_U32)INTERNAL_DVBT2_DJB_ADR;
    sDMD_DVBT2_InitData.u32FwStartAddr= (MS_U32)INTERNAL_DVBT2_FW_ADR;

    MDrv_SYS_DMD_VD_MBX_Init();

    bret &= MDrv_DMD_DVBT2_Init(&sDMD_DVBT2_InitData, sizeof(sDMD_DVBT2_InitData));
//	mdev_CofdmSetPlpGroupID(0,0);

    return bret;

#else
    MS_BOOL bRet = TRUE;

    UNUSED(eSetCofdmCfg);

    printf("\r\nmdev_CofdmPowerOnInitialization");

    if(eCurCofdmCfg!=E_COFDM_EXTERNAL_DVBT2)
    {
        eCurCofdmCfg=E_COFDM_EXTERNAL_DVBT2;
		pstDvbt2Drv->Connect(E_DEVICE_DEMOD_DVB_T2);

        if((pstDvbt2Drv->bMSB123X_Ready)==FALSE && mdev_Cofdm_MSB123X_Ready())
        {
            bRet = pstDvbt2Drv->Power_On_Initialization();
        }
    }

    return bRet;
#endif
}

void INTERN_T2_PowerOnInit(void)
{
    if( s_Intern_T2_InitDone == FALSE )
    {
        mdev_CofdmInit();
    }

    mdev_CofdmPowerOnInitialization(E_COFDM_EXTERNAL_DVBT2);
}

void mdev_CofdmControlPowerOnOff(BOOLEAN bPowerOn)
{
    //MS_BOOL bPowerOnGood = TRUE;

    if(bTunerInitOK==FALSE)
    {
        devDigitalTuner_Init();
        bTunerInitOK = TRUE;
    }

    if( s_Intern_T2_InitDone == FALSE )
    {
        mdev_CofdmInit();
    }

    if(bPowerOn)
    {
        MDrv_SYS_SetAGCPadMux(E_SYS_DTV_AGC_PAD_SET);
        //bPowerOnGood = mdev_CofdmPowerOnInitialization(E_COFDM_EXTERNAL_DVBT2);
        bDemodDTVInitOK = TRUE;
    }
    else
    {
        MDrv_DMD_DVBT2_Exit();
        //eCurCofdmCfg = E_COFDM_INVALID;
        bDemodDTVInitOK = FALSE;
    }

/*
    if(bPowerOnGood != TRUE)
    {
        printf("mdev_CofdmControlPowerOnOff FAIL\n");
    }
    */
}

MS_BOOL mdev_CofdmPowerSave(void)
{
    MS_BOOL temp=FALSE;

    COFDM_DBG(printf("---------------------mdev_CofdmPowerSave\n"));

    return temp;
}

void mdev_CofdmTunerProgramming(MS_U8 *cTunerData)
{
    COFDM_DBG(printf("---------------------mdev_CofdmTunerProgramming\n"));

    *cTunerData=*cTunerData;
}

void mdev_CofdmSetFrequency(const ICE_TuneToParams* params, RF_CHANNEL_BANDWIDTH bandWith)
{
    MS_U32 dwFrequency;
    RF_CHANNEL_BANDWIDTH eBandWidth = E_RF_CH_BAND_INVALID;
    Network_Type eNetworktype;
    DMD_DVBT2_RF_CHANNEL_BANDWIDTH eInternDvbT2Bw = E_DMD_T2_RF_BAND_INVALID;

    COFDM_DBG(printf("---------------------mdev_CofdmSetFrequency\n"));

    //mdev_Set_Current_DEMOD_TYPE(E_COFDM_EXTERNAL_DVBT2);
    dwFrequency = (MS_U32)params->channel_frequency_khz;
    eBandWidth = bandWith;

    if(params->network_type==ICE_network_dvbc)
    {
        eBandWidth =  E_RF_CH_BAND_8MHz;
    }

    switch(params->network_type)
    {
        case ICE_network_dvbt2 :
            eNetworktype = E_Network_Type_DVBT2;
            break;
        case ICE_network_dvbt :
            eNetworktype = E_Network_Type_DVBT;
            break;
        case ICE_network_dvbc :
            eNetworktype = E_Network_Type_DVBC;
            break;
        case ICE_network_analog :
            eNetworktype = E_Network_Type_Analog_T;
            break;
        default :
            printf("Warning not supported network %u\n",params->network_type);
            eNetworktype = E_Network_Type_DVBT;
    }
    eNetworktype = E_Network_Type_DVBT2;
  #if ( (FRONTEND_TUNER_TYPE == SILAB_2158_TUNER)     \
     || (FRONTEND_TUNER_TYPE == LG_G230D_TUNER)       \
     || (FRONTEND_TUNER_TYPE == SONY_SUT_RE231_TUNER) \
     || (FRONTEND_TUNER_TYPE == SONY_SUT_PEx41_TUNER) \
     )
    devTuner_Std_set(E_TUNER_DTV_DVB_T2_MODE, E_AUDIOSTANDARD_NOTSTANDARD_);
  #else
    devTuner_Std_set(E_TUNER_DTV_DVB_T2_MODE, E_AUDIOSTANDARD_NOTSTANDARD_);
  #endif


    // Save tuner freq for debug
    g_Debug_u32LastTunerFreq = dwFrequency;

    devDigitalTuner_SetFreq((double)(dwFrequency/1000.0), eBandWidth);

#if (IS_MXL_TUNER)
    OS_DELAY_TASK(120); //waiting for tuner write
#else
    OS_DELAY_TASK(10); //waiting for tuner write
#endif

    switch(eBandWidth)
    {
        case E_RF_CH_BAND_6MHz:
            eInternDvbT2Bw = E_DMD_T2_RF_BAND_6MHz;
            break;
        case E_RF_CH_BAND_7MHz:
            eInternDvbT2Bw = E_DMD_T2_RF_BAND_7MHz;
            break;
        case E_RF_CH_BAND_8MHz:
        default:
            eInternDvbT2Bw = E_DMD_T2_RF_BAND_8MHz;
            break;
    }
    MDrv_DMD_DVBT2_SetConfig(eInternDvbT2Bw, 0, g_plp_id);
	MDrv_DMD_DVBT2_SetActive(ENABLE);
}
#if 0
COFDM_LOCK_STATUS_123X _mdev_CofdmLockStatusConversion_DVBT2(COFDM_LOCK_STATUS eStatus)
{
    COFDM_LOCK_STATUS_123X eLockStatus;

    switch(eStatus)
    {
        default:
        case COFDM_FEC_LOCK:
            eLockStatus = COFDM_FEC_LOCK_T2_123X;
            break;
        case COFDM_TPS_LOCK:
            eLockStatus = COFDM_P1_LOCK_HISTORY_123X;
            break;
    }
    return eLockStatus;
}
#endif
MS_BOOL mdev_CofdmGetLockStatus(COFDM_LOCK_STATUS_123X eStatus)
{
    #if 1
    DMD_T2_LOCK_STATUS eLockStatus;
    DMD_DVBT2_GETLOCK_TYPE eGetLockType = E_DMD_DVBT2_GETLOCK;
//    eStatus = eStatus;
    if(eStatus == COFDM_FEC_LOCK_T2_123X)
    {
        eGetLockType = E_DMD_DVBT2_FEC_LOCK;
    }
    else if(eStatus == COFDM_P1_LOCK_HISTORY_123X)
    {
        eGetLockType = E_DMD_DVBT2_P1_EVER_LOCK;
    }
    else
    {
        eGetLockType = E_DMD_DVBT2_GETLOCK;
    }

    if(MDrv_DMD_DVBT2_GetLock(eGetLockType, &eLockStatus)==TRUE)
    {
        if(eLockStatus == E_DMD_T2_LOCK)
            return TRUE;
    }
    return FALSE;
    #else
    return pstDvbt2Drv->DTV_GetLock(eStatus);
    #endif
}

MS_U16 mdev_CofdmGetPacketErr(void)
{
    MS_U16 u16Err=0;

    //DTV_GetPacketErr(&u16Err);
    MDrv_DMD_DVBT2_GetPacketErr(&u16Err);


    return u16Err;
}
#if 0
MS_U8 mdev_CofdmGetSignalToNoiseRatio(void)
{
    MS_U8 temp = 0;
    float *fSNR = 0;

    printf("---------------------mdev_CofdmGetSignalToNoiseRatio\n");

    temp = pstDvbt2Drv->DTV_GetSNR_F(fSNR);

    return temp;
}

void mdev_CofdmPassThroughI2c(MS_BOOL bEnable)
{
    printf("---------------------mdev_CofdmPassThroughI2c:%u\n",bEnable);

    pstDvbt2Drv->IIC_Bypass_Mode(bEnable);
}

void mdev_CofdmDisableTSPAD(void)
{
    printf("---------------------mdev_CofdmDisableTSPAD:NULL FUNCTION\n");

    //INTERN_DVBT_Disable_TS_PAD();//Not for A1
}


void mdev_CofdmSwitchTransportSteamInferface(TS_INTERFACE interface)
{
    MS_BOOL bEnable;

    printf("---------------------mdev_CofdmSwitchTransportSteamInferface\n");

    if ( interface == E_SERIAL_INTERFACE )
    {
        bEnable = TRUE;
    }
    else
    {
        bEnable = FALSE;
    }

    pstDvbt2Drv->DTV_Serial_Control(bEnable);
}
void mdev_CofdmBootSwitchTSInferface(TS_INTERFACE interface)
{
    MS_BOOL bEnable;

    printf("---------------------mdev_CofdmBootSwitchTSInferface\n");

    if ( interface == E_SERIAL_INTERFACE )
    {
        bEnable = TRUE;
    }
    else
    {
        bEnable = FALSE;
    }
}
#endif
MS_BOOL mdev_CofdmGetSignalStrength(MS_U16 *strength)
	{
#if(FRONTEND_TUNER_TYPE == NUTUNE_FK1602_TUNER || FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER)
		{
			tmUnitSelect_t	  sysUnit= 0;
			UInt32 u32RFLevelDbm=0;
			float fRFLevelDbm;
			tmsysOM3912GetSignalStrength(sysUnit, &u32RFLevelDbm);
			fRFLevelDbm = (float)u32RFLevelDbm;
			MDrv_DMD_DVBT2_GetSignalStrengthWithRFPower(strength, fRFLevelDbm);
			return E_RESULT_SUCCESS;
		}
#elif((FRONTEND_TUNER_TYPE == SILAB_2158_TUNER) || (FRONTEND_TUNER_TYPE == LG_G230D_TUNER))
		{
			mdev_ATV_GetSignalStrength_Si2158(strength);
			return E_RESULT_SUCCESS;
		}
#elif( (FRONTEND_TUNER_TYPE == SONY_SUT_RE231_TUNER)\
      || (FRONTEND_TUNER_TYPE == NXP_TDA18275_TUNER)\
      || (FRONTEND_TUNER_TYPE == SILAB_2190_TUNER)  \
      || (FRONTEND_TUNER_TYPE == SILAB_2157_TUNER)  \
      || (FRONTEND_TUNER_TYPE == MxL_601SI_TUNER)   \
      || (FRONTEND_TUNER_TYPE == MxL_661SI_TUNER)   \
      || (FRONTEND_TUNER_TYPE == SILAB_2151_TUNER)  \
      || (FRONTEND_TUNER_TYPE == NXP_TDA182I5a_TUNER)  \
      || (FRONTEND_TUNER_TYPE == RAFAEL_R842_TUNER)  \
			)
		{
			float	rf_level_dbm = 0.0;
			MS_BOOL bRet = TRUE;
			bRet &= mdev_GetSignalStrength(&rf_level_dbm);
			bRet &= MDrv_DMD_DVBT2_GetSignalStrengthWithRFPower(strength, rf_level_dbm);
			return (bRet == TRUE)?E_RESULT_SUCCESS:E_RESULT_FAILURE;
		}
#elif (FRONTEND_TUNER_TYPE == RAFAEL_R840_TUNER || FRONTEND_TUNER_TYPE == RAFAEL_R842_TUNER)
		{
			float	rf_level_dbm = 0.0;
			MS_BOOL bRet = TRUE;
            //<<-- smc 20151223 for rf840 842
            #if 0
			MS_U16	 tmp = 0;
			MS_U16	 if_agc_gain = 0;

			S_RSSI_TABLE ssi_r840[]=
			{
				{-82.0,0x7a72},
				{-81.0,0x788a},
				{-80.0,0x7700},
				{-79.0,0x75b2},
				{-78.0,0x74b0},
				{-77.0,0x73b9},
				{-76.0,0x72ea},
				{-75.0,0x71fe},
				{-74.0,0x7130},
				{-73.0,0x707b},
				{-72.0,0x6fba},
				{-71.0,0x6f2b},
				{-70.0,0x6e90},
				{-69.0,0x6e04},
				{-68.0,0x6d85},
				{-67.0,0x6cfe},
				{-66.0,0x6c80},
				{-65.0,0x6bf1},
				{-64.0,0x6b78},
				{-63.0,0x6af1},
				{-62.0,0x6a70},
				{-61.0,0x69f0},
				{-60.0,0x695a},
				{-59.0,0x68a4},
				{-58.0,0x67e3},
				{-57.0,0x670f},
				{-56.0,0x6630},
				{-55.0,0x6530},
				{-54.0,0x642c},
				{-53.0,0x633d},
				{-52.0,0x6273},
				{-51.0,0x61a0},
				{-00.0,0xFFFF},// add for table end
			};

	#if((CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)\
        ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON))
				tmp = devCOFDM_DVBT_ReadReg(0x2800 + 0x08*2);
				bRet &= devCOFDM_DVBT_WriteReg(0x2800 + 0x08*2, tmp|0x80);

				tmp = devCOFDM_DVBT_ReadReg(0x2800 + 0x13*2);
				bRet &= devCOFDM_DVBT_WriteReg(0x2800 + 0x13*2, (tmp&0xF0)|0x03);

				tmp = devCOFDM_DVBT_ReadReg(0x2800 + 0x14*2 + 1);
				if_agc_gain = tmp;
				tmp = devCOFDM_DVBT_ReadReg(0x2800 + 0x14*2);
				if_agc_gain = (if_agc_gain<<8)|tmp;

				tmp = devCOFDM_DVBT_ReadReg(0x2800 + 0x08*2);
				bRet &= devCOFDM_DVBT_WriteReg(0x2800 + 0x08*2, tmp&~(0x80));
	#else
			tmp = devCOFDM_ReadReg(0x2700 + 0x02*2);
			bRet &= devCOFDM_WriteReg(0x2700 + 0x02*2, tmp|0x80);

			tmp = devCOFDM_ReadReg(0x2700 + 0x0b*2);
			bRet &= devCOFDM_WriteReg(0x2700 + 0x0b*2, (tmp&0xF0)|0x03);

			tmp = devCOFDM_ReadReg(0x2700 + 0x0c*2 + 1);
			if_agc_gain = tmp;
			tmp = devCOFDM_ReadReg(0x2700 + 0x0c*2);
			if_agc_gain = (if_agc_gain<<8)|tmp;

			tmp = devCOFDM_ReadReg(0x2700 + 0x02*2);
			bRet &= devCOFDM_WriteReg(0x2700 + 0x02*2, tmp&~(0x80));
	#endif
    #endif
		//smc 20151223 for rf840 842 -->>
		bRet &= mdev_GetSignalStrength(&rf_level_dbm);
			//bRet &= mdev_GetSignalStrength(ssi_r840, if_agc_gain, &rf_level_dbm);
			bRet &= MDrv_DMD_DVBT2_GetSignalStrengthWithRFPower(strength, rf_level_dbm);

			return (bRet == TRUE)?E_RESULT_SUCCESS:E_RESULT_FAILURE;
		}
#else
		{
			MS_BOOL bRet=FALSE;
			bRet=MDrv_DMD_DVBT2_GetSignalStrengthWithRFPower(strength, 200.0f);
			return (bRet) ? E_RESULT_SUCCESS : E_RESULT_FAILURE;
		}

#endif
	}

#if 0
MS_BOOL mdev_CofdmGetCellid(MS_U16 *wCell_id)
{
    MS_BOOL temp = FALSE;

    printf("---------------------mdev_CofdmGetCellid\n");

    *wCell_id = *wCell_id;
    temp = TRUE;

    return temp;
}
#endif
MS_BOOL mdev_CofdmGetSignalQuality(MS_U16 *quality)//ok
{
    MS_BOOL temp = FALSE;
    #if 1
    temp = MDrv_DMD_DVBT2_GetSignalQuality(quality);
    #else
    *quality = pstDvbt2Drv->MDrv_DMD_DVBT2_GetSignalQuality();
    temp = TRUE;
    #endif
    return temp;
}
#if 0
MS_BOOL mdev_CofdmGetTpsInfo(MS_U16 *TPS_Info)
{
    MS_BOOL temp = FALSE;

    printf("---------------------mdev_CofdmGetTpsInfo\n");

    TPS_Info = NULL;

    return temp;
}

MS_BOOL mdev_CofdmGetTpsInfo_T2(MS_U64 *TPS_Info)
{
    MS_BOOL temp = FALSE;

    printf("---------------------mdev_CofdmGetTpsInfo_T2\n");

    temp = pstDvbt2Drv->DTV_DVB_T2_GetSignalTpsInfo(TPS_Info);

    return temp;
}
#endif
MS_BOOL mdev_CofdmPassThroughI2cReadBytes(MS_U8 u8SlaveID, MS_U8 u8AddrNum, MS_U8* paddr, MS_U16 u16size, MS_U8* pu8data)//ok
{
    MS_BOOL bRet = TRUE;

    u8SlaveID = u8SlaveID;
    u8AddrNum = u8AddrNum;
    paddr = NULL;
    u16size = u16size;
    pu8data = NULL;

    return bRet;
}

MS_BOOL mdev_CofdmPassThroughI2cWriteBytes(MS_U8 u8SlaveID, MS_U8 u8AddrNum, MS_U8* paddr, MS_U16 u16size, MS_U8* pu8data)//ok
{
    MS_BOOL bRet = TRUE;

    u8SlaveID = u8SlaveID;
    u8AddrNum = u8AddrNum;
    paddr = NULL;
    u16size = u16size;
    pu8data = NULL;

    return bRet;
}

MS_BOOL mdev_CofdmReadReg(MS_U16 u16Addr, MS_U8 *pu8Data)//ok
{
    MS_BOOL bRet = FALSE;

    bRet = MDrv_DMD_DVBT2_GetReg(u16Addr, pu8Data);
    /*
    switch (eCurCofdmCfg)
    {
        case E_COFDM_INTERNAL_DVBT:
          #if USE_UTOPIA
            bRet = MDrv_DMD_DVBT_GetReg(u16Addr, pu8Data);
          #else
            bRet = INTERN_DVBT_ReadReg(u16Addr, pu8Data);
          #endif
            break;
      #if ENABLE_DVBC
        case E_COFDM_INTERNAL_DVBC:
          #if USE_UTOPIA
            bRet = MDrv_DMD_DVBC_GetReg(u16Addr, pu8Data);
          #else
            bRet = INTERN_DVBC_ReadReg(u16Addr, pu8Data);
          #endif
            break;
      #endif

        case E_COFDM_INTERNAL_DVBT2:
            bRet = MDrv_DMD_DVBT2_GetReg(u16Addr, pu8Data);
            break;

        case E_COFDM_EXTERNAL_DVBT2:
        default:
            bRet = ReadReg(u16Addr, pu8Data);
            break;

    }
    */
    return bRet;
}

MS_BOOL mdev_CofdmWriteReg(MS_U16 RegAddr, MS_U16 RegData)//ok
{
    //printf("---------------------mdev_CofdmWriteReg\n");
    return MDrv_DMD_DVBT2_SetReg( RegAddr,(U8) RegData);
    /*
  #if USE_UTOPIA
    return MDrv_DMD_DVBT_SetReg( RegAddr,(U8) RegData);
  #else
    return INTERN_DVBT_WriteReg( RegAddr,(U8) RegData);
  #endif
*/
}

extern void *memset(void * s, int c, size_t count);
MS_U8 u8PlpIDList[32];
MS_U8 mdev_CofdmGetPlpIDList(void)
{
    MS_BOOL bRet;
	MS_BOOL bUsed;
	MS_U8 u8CurrentPlpID;
	MS_U8 u8PlpBitMap[32];
	MS_U8 PlpIDList[32];
    int i,j,k;
    memset(u8PlpBitMap, 0, 32);
    memset(PlpIDList, 0, 32);
    memset(u8PlpIDList, INVALID_PLPID, 32);
    k = 0;
    bRet = MDrv_DMD_DVBT2_GetPlpBitMap(u8PlpBitMap);
	mdev_CofdmGetCurrentPlpID(&u8CurrentPlpID);

    if (bRet == FALSE)
    {
        printf("\r\n mdev_CofdmGetPlpIDList FAIL\n");
        return 0;
    }
    for(i = 0; i < 32; i++)
    {
        for(j = 0; j < 8; j++)
        {
            if((u8PlpBitMap[i] >> j) & 1)
            {
            	PlpIDList[k]= 0x00;
                PlpIDList[k]=(i * 8 + j);
				u8PlpIDList[k] = PlpIDList[k];
				if(u8CurrentPlpID == PlpIDList[k])
				{
					bUsed = 1;//already used
				}
				else
				{
					bUsed = 0;//new
				}
				MApp_SI_AddT2DelSysDesc(PlpIDList[k],bUsed);
                k++;
            }
        }
    }
    return k;
}

MS_BOOL mdev_CofdmGetPlpGroupID(MS_U8 u8PlpID, MS_U8* u8GroupID)//ok
{
    MS_BOOL bRet;

    //bRet = pstDvbt2Drv->MDrv_DMD_DVBT2_GetPlpGroupID(u8PlpID, u8GroupID);
    bRet = MDrv_DMD_DVBT2_GetPlpGroupID(u8PlpID, u8GroupID);

    printf("%u mdev_CofdmGetPlpGroupID PlpID:%u GrpID:%u\n",bRet,u8PlpID,u8GroupID);

    return bRet;
}

MS_BOOL mdev_CofdmSetPlpGroupID(MS_U8 u8PlpID, MS_U8 u8GroupID)//ok
{
    MS_BOOL bRet;

    g_plp_id = u8PlpID;
    g_group_id = u8GroupID;
    bRet = MDrv_DMD_DVBT2_SetPlpID(u8PlpID, u8GroupID);
    return bRet;
}

MS_BOOL mdev_CofdmGetCurrentPlpID(MS_U8 *pu8PlpID)
{
    MS_BOOL bRet = TRUE;
    MS_U8   reg;

    bRet &= MDrv_SYS_DMD_VD_MBX_ReadDSPReg(E_DMD_T2_PLP_ID, &reg);
    *pu8PlpID = reg;

    return bRet;
}

MS_BOOL mdev_CofdmIsInitOK( void )
{
    printf(" << mdev_CofdmIsInitOK(%d) \n", bDemodDTVInitOK);

    return bDemodDTVInitOK;
}

void mdev_ControlTSOutput(BOOLEAN bEnable)
{
    bEnable = bEnable;
    //DTV_ControlTsOutput(bEnable);
}

void mdev_ControlAGCOutput(BOOLEAN bEnable)
{
    bEnable = bEnable;
    //DTV_ControlAGCOutput(bEnable);
}
/***************************************************************************************/
#endif // #if (ENABLE_DVB_T2)

/***************************************************************************************/
#endif  // #ifndef _MDEV_COFDM_DEMODULATOR_C_


