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
#define DEVICE_TUNER_SONY_SUT_PE232_C
#if 0
#include <unistd.h>
#include "debug.h"
#include "device_tuner_sony_sut_pe232.h"
#include "mapi_i2c.h"
#include "mapi_i2c_devTable.h"
#include "mapi_interface.h"
#include "mapi_gpio.h"
#include "mapi_gpio_devTable.h"
#include "mapi_vif.h"
#include "mapi_audio.h"

#include "MsTypes.h"
#endif

#include <math.h>
#include "MsCommon.h"
#include "drvIIC.h"
// #include "Board.h"

#include "device_tuner_sony_sut_pe232.h"
#include "sony_sut_pe232/sut_pe232_sat_v010.c"

#if 0
#include "MsOS.h"
#include "mapi_tuner_datatype.h"
#endif
#define TUNER_DEBUG 0

#if  TUNER_DEBUG
#define PRINTE(p) printf p
#else
#define PRINTE(p)
#endif

typedef struct
{
    float    LvdBm;
    MS_U16 u16_if_agc;
}S_RSSI_TABLE;

static S_RSSI_TABLE ssi_sony_pe232[]=
{
{-95.0,0xFB00},
{-90.0,0xF8AC},
{-85.0,0xF443},
{-80.0,0xEE40},
{-75.0,0xE79A},
{-70.0,0xE097},
{-65.0,0xDC3C},
{-60.0,0xD557},
{-55.0,0xCF2E},
{-50.0,0xCBD1},
{-45.0,0xC53C},
{-40.0,0xBFEC},
{-35.0,0xBA8D},
{-30.0,0xB306},
{-25.0,0xAE69},
{-20.0,0xA996},
{-15.0,0xA538},
{-10.0,0x9F4C},
{- 5.0,0x994E},
{- 0.0,0x9303},
};

void ms_delay(MS_U32 ms);
MS_U8  hw_rst_control(MS_U8 en);
BOOL MDrv_tuner_IIC_Write(MS_U8 u8slaveID, MS_U8 *pu8Addr,MS_U8 u8AddrSize, MS_U8 *pu8Data, MS_U16 u16Size );
BOOL MDrv_tuner_IIC_Read(MS_U8 u8slaveID, MS_U8 *pu8Addr,MS_U8 u8AddrSize, MS_U8 *pu8Data,  MS_U16 u16Size );
BOOL device_tuner_sony_sutpe232_Init(void);
BOOL device_tuner_sony_sutpe232_DTV_SetTune(MS_U16 FreqMHz, MS_U32 u32SymbolRate_kHz);
BOOL device_tuner_sony_sutpe232_DTV_GetLockStatus(void);

void ms_delay(MS_U32 ms)
{
    PRINTE(("%s(),%d\n", __func__, __LINE__));
    MsOS_DelayTask(ms);
}

MS_U8  hw_rst_control(MS_U8 en)
{
    UNUSED(en);
    PRINTE(("%s(),%d\n", __func__, __LINE__));
    return TRUE;
}

BOOL MDrv_tuner_IIC_Write(MS_U8 u8slaveID, MS_U8 *pu8Addr,MS_U8 u8AddrSize,
                             MS_U8 *pu8Data,  MS_U16 u16Size )
{
    /* Variable declarations */
    UINT8 bRet = 1;
    
    if(MDrv_IIC_WriteBytes((MS_U16)((((MS_U16)DVBS_TUNER_IIC_BUS)<<8)|u8slaveID), u8AddrSize, pu8Addr, u16Size, pu8Data) == FALSE)
    {
        bRet = 0;
        printf("\nTuner_IIC write  fail\n");
    }        
    return (bRet==1)?TRUE:FALSE;
}

BOOL MDrv_tuner_IIC_Read(MS_U8 u8slaveID, MS_U8 *pu8Addr,MS_U8 u8AddrSize,
                             MS_U8 *pu8Data,  MS_U16 u16Size )
{
    /* Variable declarations */
    UINT8 bRet = 1;
    
    if(MDrv_IIC_ReadBytes((MS_U16)((((MS_U16)DVBS_TUNER_IIC_BUS)<<8)|u8slaveID), u8AddrSize, pu8Addr, u16Size, pu8Data) == FALSE)
    {
        bRet = 0;
        printf("\nTuner_IIC read  fail\n");
    }        
    return (bRet==1)?TRUE:FALSE;

}

BOOL device_tuner_sony_sutpe232_Init(void)
{
    PRINTE(("%s(),%d\n", __func__, __LINE__));
    MS_U8 bRet = 1;

    S_SUT_RE23x_dependency_func SUT_RE23x_dependency_func_obj;

    /* Low layer struct set-up to link with user written functions */
    SUT_RE23x_dependency_func_obj.i2c_read  = MDrv_tuner_IIC_Read;
    SUT_RE23x_dependency_func_obj.i2c_write = MDrv_tuner_IIC_Write;
    SUT_RE23x_dependency_func_obj.MAPI_delay = ms_delay;
    SUT_RE23x_dependency_func_obj.hw_rst_control=hw_rst_control;

    // platform dependency api registration.
    bRet &= mdev_Tunerfunc_SUT(&SUT_RE23x_dependency_func_obj);
    PRINTE(("device_tuner_sony_sutpe232_Init-%02x, %d\n", bRet, __LINE__));

    bRet &= mdev_TunerInit_SUT();
    PRINTE(("device_tuner_sony_sutpe232_Init-%02x, %d\n", bRet, __LINE__));
    
    return (bRet==1)?TRUE:FALSE;
}

BOOL device_tuner_sony_sutpe232_DTV_SetTune(MS_U16 FreqMHz, MS_U32 u32SymbolRate_kHz)
{
    PRINTE(("%s(),%d\n", __func__, __LINE__));
    MS_U8 bRet = 0;  

    //tuner_param.m_uiFrequency_100kHz = (MS_U16)(FreqMHz*10.0);
    //tuner_param.m_uiLPF_100kHz = u32SymbolRate_kHz/100;//200; // 40M

    bRet = mdev_TunerDigitalSetFreq_SUT(FreqMHz, u32SymbolRate_kHz);

    PRINTE(("%s()-%02x, %d\n", __func__, bRet, __LINE__));

    return (bRet == 0)?TRUE:FALSE;
}

BOOL device_tuner_sony_sutpe232_DTV_GetLockStatus(void)
{
    
    //BOOL bRet = true;    
    return TRUE;//bRet;
}

BOOL MDrv_DVBS_Tuner_SetFreq(MS_U16 u16CenterFreq_MHz, MS_U32 u32SymbolRate_Ks)
{
    return device_tuner_sony_sutpe232_DTV_SetTune(u16CenterFreq_MHz,u32SymbolRate_Ks);
}

BOOL MDrv_DVBS_Tuner_Initial(void)
{
    return device_tuner_sony_sutpe232_Init();
}

BOOL MDrv_DVBS_Tuner_CheckLock(void)
{   
    return TRUE;
}

// input IF_AGC,
// return dBm.
float MDrv_DVBS_Tuner_Get_RSSI(MS_U16 u16_gain)
{
    MS_U8 indx = 0;
    MS_U8 arry_size = 0;
    float rf_dbm = 0.0;
    arry_size = sizeof(ssi_sony_pe232)/sizeof(S_RSSI_TABLE);

    // printf("array_size = %d, gain=0x%x\n",arry_size,u16_gain);
     
    if (u16_gain > ssi_sony_pe232[0].u16_if_agc)
    {
        rf_dbm = (float)(u16_gain - ssi_sony_pe232[1].u16_if_agc)/(float)(ssi_sony_pe232[0].u16_if_agc - ssi_sony_pe232[1].u16_if_agc)*(ssi_sony_pe232[0].LvdBm - ssi_sony_pe232[1].LvdBm)+ssi_sony_pe232[1].LvdBm;
    }
    else if (u16_gain < ssi_sony_pe232[arry_size-1].u16_if_agc)
    {
        rf_dbm = (float)(u16_gain - ssi_sony_pe232[arry_size-2].u16_if_agc)/(float)(ssi_sony_pe232[arry_size-1].u16_if_agc - ssi_sony_pe232[arry_size-2].u16_if_agc)*(ssi_sony_pe232[arry_size-1].LvdBm - ssi_sony_pe232[arry_size-2].LvdBm)+ssi_sony_pe232[arry_size-2].LvdBm;
    }
    else
    {
        for(indx = 0;indx<arry_size;indx++)
        {
            if (u16_gain > ssi_sony_pe232[indx].u16_if_agc) break;
        }
        rf_dbm = (float)(u16_gain - ssi_sony_pe232[indx].u16_if_agc)/(float)(ssi_sony_pe232[indx-1].u16_if_agc - ssi_sony_pe232[indx].u16_if_agc)*(ssi_sony_pe232[indx-1].LvdBm - ssi_sony_pe232[indx].LvdBm)+ssi_sony_pe232[indx].LvdBm;
    }

    // printf("gain=0x%x,rf_dbm=%f, indx=%d, arry_size=%d\n",u16_gain,rf_dbm,indx,arry_size);
    
    return rf_dbm;
}

#undef DEVICE_TUNER_SONY_SUT_PE232_C
