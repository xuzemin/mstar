//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and EXTERNational treaties.
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
//    and in conformity with any EXTERNational standard.  You agree to waive any
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
/**********************************************************************
Copyright (c) 2006-2009 MStar Semiconductor, Inc.
All rights reserved.
Unless otherwise stipulated in writing, any and all information contained
herein regardless in any format shall remain the sole proprietary of
MStar Semiconductor Inc. and be kept in strict confidence
(MStar Confidential Information) by the recipient.
Any unauthorized act including without limitation unauthorized disclosure,
copying, use, reproduction, sale, distribution, modification, disassembling,
reverse engineering and compiling of the contents of MStar Confidential
Information is unlawful and strictly prohibited. MStar hereby reserves the
rights to any and all damages, losses, costs and expenses resulting therefrom.
 **********************************************************************/
#define _EXTERN_ISDBT_C_

#include <math.h>
#include "Tuner.h"
#include "MsOS.h"
#include "debug.h"

#include "drvIIC.h"
#include "drvDMD_common.h"
#include "drvDMD_ISDBT.h"       //matt add for integrate DTMB utopia driver
#include "drvDMD_VD_MBX.h"

#define DEMOD_AMAZOM_SLAVE_ID       0xD2

#define ERR_DEMOD_MSB(x)            //  x
#define DBG_DOMOD_MSB(x)            //   x
#define DBG_DEMOD_CHECK_LOCK(x)     // x
#define DBG_DEMOD_INFO(x)           // x
#define DBG_SSI(x)                  //  x
#define DBG_SQI(x)                  //  x


//#if( (FRONTEND_TUNER_TYPE == MxL_601SI_TUNER) || (FRONTEND_TUNER_TYPE == SILAB_2158_TUNER))
#if ((FRONTEND_TUNER_TYPE == MxL_601SI_TUNER) || (FRONTEND_TUNER_TYPE == MxL_661SI_TUNER))
#define ISDBT_TUNER_IF              5000
#elif (FRONTEND_TUNER_TYPE == RAFAEL_R828_TUNER)
#define ISDBT_TUNER_IF              4063
#elif (FRONTEND_TUNER_TYPE == RDA5158_TUNER)
#define ISDBT_TUNER_IF              5000
#elif (FRONTEND_TUNER_TYPE == SILAB_2158_TUNER)
#define ISDBT_TUNER_IF              6000
#else
#define ISDBT_TUNER_IF              3250
#endif
#define usleep(x)                   MsOS_DelayTask(x/1000)

#if TS_PARALLEL_ISDBT_OUTPUT
#define ISDBT_TS_SERIAL         0x00
#else
#define ISDBT_TS_SERIAL         0x01
#endif

// Division number of TS clock rate
// Formula: TS Clk Rate= 216 MHz/reg_isdbt_ts_clk_divnum
// Ex: ISDBT_TS_CLK_DIVNUM = 31 => TS Clk = 216/31= 6.967 MHz
#define ISDBT_TS_CLK_DIVNUM_SERIAL_MODE     4
#define ISDBT_TS_CLK_DIVNUM_PARALLEL_MODE   31

#if (ISDBT_TS_SERIAL)
#define ISDBT_TS_CLK_DIVNUM     ISDBT_TS_CLK_DIVNUM_SERIAL_MODE
#else
#define ISDBT_TS_CLK_DIVNUM     ISDBT_TS_CLK_DIVNUM_PARALLEL_MODE
#endif

#define ISDBT_TS_DATA_SWAP      0x00  // TS data inversion
#define ISDBT_TS_CLK_INV        1  // TS clock inverseion //this define will depend on hw main board
#if ((FRONTEND_TUNER_TYPE == MxL_601SI_TUNER) || (FRONTEND_TUNER_TYPE == MxL_661SI_TUNER))
#define ISDBT_IQ_SWAP           0x01          // IQ Swap  //this define will depend on tuner
#else
#define ISDBT_IQ_SWAP           0x00          // IQ Swap  //this define will depend on tuner
#endif
#define ISDBT_IFAGC_REF         0x3C              //this define will depend on tuner
#define ISDBT_TDI_START_ADDR    (DMD_ISDBT_ADR/16)   // System must allocate a 7MB memory space starting from this (128-bit)address
//static BOOL s_bI2C_FastMode = false;

float EXTERN_ISDBT_GetSNR(void);

MAPI_BOOL DeviceDemodCreate(void)
{
    return MAPI_TRUE;
}

MAPI_BOOL Connect(void)
{
    return MAPI_TRUE;
}
MAPI_BOOL Disconnect(void)
{
    return MAPI_TRUE;
}
void Reset(void)
{

}

MAPI_BOOL Set_PowerOn(void)
{
    return TRUE;
}

MAPI_BOOL Set_PowerOff(void)
{
    return TRUE;
}

BOOLEAN EXTERN_ISDBT_Power_On_Initialization(void)
{
    BOOLEAN   bResult = true;
    DMD_ISDBT_InitData sDMD_ISDBT_InitData;
    static MS_U8 u8DMD_ISDBT_InitExt[]={1}; // RFAGC tristate control default value, 1:trisate 0:non-tristate,never modify unless you know the meaning

    printf("EXTERN_ISDBT_Power_On_Initialization\n");


    MDrv_DMD_PreInit();

    // copy tuner config
    //mapi_interface::Get_mapi_pcb()->GetIsdbTuner(0)->ExtendCommand(mapi_tuner_datatype::E_TUNER_SUBCMD_GET_IQ_SWAP, E_TUNER_DTV_ISDB_MODE, NULL, &u8IqSwap);
    //mapi_interface::Get_mapi_pcb()->GetIsdbTuner(0)->ExtendCommand(mapi_tuner_datatype::E_TUNER_SUBCMD_GET_DTV_IF_FREQ, E_TUNER_DTV_ISDB_MODE, NULL, &u16DtvIFFreqKHz);
    sDMD_ISDBT_InitData.u16IF_KHZ = ISDBT_TUNER_IF;//u16DtvIFFreqKHz;
    sDMD_ISDBT_InitData.bIQSwap = ISDBT_IQ_SWAP;
    sDMD_ISDBT_InitData.u16AgcReferenceValue = ISDBT_IFAGC_REF;
    //sDMD_ISDBT_InitData.u32TdiStartAddr= ISDBT_TDI_START_ADDR;
    sDMD_ISDBT_InitData.u16ISDBTFECLockCheckTime = 2000;
    sDMD_ISDBT_InitData.u16ISDBTIcfoChExistCheckTime = 300;
    sDMD_ISDBT_InitData.u8DMD_ISDBT_InitExt = u8DMD_ISDBT_InitExt;

    //TS[begin]
    //Parallel mode
    //sDMD_ISDBT_InitData.u5TsConfigByte_DivNum = ISDBT_TS_CLK_DIVNUM;
    //sDMD_ISDBT_InitData.u1TsConfigByte_ClockInv = ISDBT_TS_CLK_INV;
    //sDMD_ISDBT_InitData.u1TsConfigByte_DataSwap = 0;
    //sDMD_ISDBT_InitData.u1TsConfigByte_SerialMode = ISDBT_TS_SERIAL;
    //Serial mode
    sDMD_ISDBT_InitData.u5TsConfigByte_DivNum = ISDBT_TS_CLK_DIVNUM;
    sDMD_ISDBT_InitData.u1TsConfigByte_ClockInv = ISDBT_TS_CLK_INV;
    sDMD_ISDBT_InitData.u1TsConfigByte_DataSwap = ISDBT_TS_DATA_SWAP;
    sDMD_ISDBT_InitData.u1TsConfigByte_SerialMode = ISDBT_TS_SERIAL;

    //TS[end]
    sDMD_ISDBT_InitData.bIsUseSspiLoadCode=0;
    sDMD_ISDBT_InitData.bIsSspiUseTsPin=0;
    sDMD_ISDBT_InitData.bIsExtDemod = TRUE;
    MDrv_SYS_DMD_VD_MBX_Init();

    //IIC Addr
    sDMD_ISDBT_InitData.u8I2CSlaveAddr = DEMOD_AMAZOM_SLAVE_ID;
    sDMD_ISDBT_InitData.u8I2CSlaveBus = TUNER_IIC_BUS;
    sDMD_ISDBT_InitData.bIsExtDemod = TRUE;
    sDMD_ISDBT_InitData.I2C_WriteBytes = MDrv_IIC_WriteBytes;
    sDMD_ISDBT_InitData.I2C_ReadBytes = MDrv_IIC_ReadBytes;
    MDrv_DMD_ISDBT_Initial_Hal_Interface();
    MDrv_DMD_ISDBT_Init(&sDMD_ISDBT_InitData, sizeof(sDMD_ISDBT_InitData));


    return bResult;
}

BOOLEAN EXTERN_ISDBT_Lock(COFDM_LOCK_STATUS eStatus)
{
    DMD_ISDBT_LOCK_STATUS eLockStatus = DMD_ISDBT_UNLOCK;
    BOOLEAN ret_lock = FALSE;

    //printf("dan COFDM_LOCK_STATUS = %d\n", (MS_U8)eStatus);

    if(eStatus == COFDM_ICFO_CH_EXIST_FLAG)
        eLockStatus = MDrv_DMD_ISDBT_GetLock(DMD_ISDBT_GETLOCK_ICFO_CH_EXIST_LOCK);
    else if(eStatus == COFDM_FEC_LOCK)
    {
        eLockStatus = MDrv_DMD_ISDBT_GetLock(DMD_ISDBT_GETLOCK_FEC_LOCK);
        //printf("[Mstar]FEC lock\n");
        /*
        if(eLockStatus == DMD_ISDBT_LOCK)
        {
            EXTERN_ISDBT_GetSNR();
            printf("FEC lock\n");
        }
        */
    }

    if(eLockStatus == DMD_ISDBT_LOCK)
        ret_lock = TRUE;
    /*
    eLockStatus = MDrv_DMD_ISDBT_GetLock(DMD_ISDBT_GETLOCK);
    switch (eLockStatus) // _UTOPIA
    {
        case DMD_ISDBT_LOCK:
            ret_lock = TRUE;
            printf("FEC lock\n");
            break;
        case DMD_ISDBT_CHECKING:
            ret_lock = FALSE;
            break;
        case DMD_ISDBT_CHECKEND:
            ret_lock = FALSE;
            break;
        case DMD_ISDBT_UNLOCK:
            ret_lock = FALSE;
            break;
        default:
            printf("ISDBTT_GetLockStatus error\n");
            break;
    }
    */
    return ret_lock;
}
BOOLEAN EXTERN_ISDBT_Config(RF_CHANNEL_BANDWIDTH BW, BOOLEAN bSerialTS, BOOLEAN bPalBG, BOOLEAN bLPSel)
{
    BW = BW;
    bSerialTS = bSerialTS;
    bPalBG = bPalBG;
    bLPSel = bLPSel;
    return true;
}

BOOLEAN EXTERN_ISDBT_Active(BOOLEAN bEnable)
{
    return MDrv_DMD_ISDBT_SetConfig(bEnable);
}

BOOLEAN EXTERN_ISDBT_Serial_Control(BOOLEAN bEnable)
{
    MS_U8  u8TsConfigData;

    u8TsConfigData = 0;
    //printf("dan enter MSB1400_Serial_Control\n");
    if(bEnable == TRUE)  //serial mode
    {
        u8TsConfigData |= 0x01;
        u8TsConfigData |= ISDBT_TS_CLK_DIVNUM_SERIAL_MODE << 3;  //0x04
    }
    else
    {
        u8TsConfigData &= ~0x01;
        u8TsConfigData |= ISDBT_TS_CLK_DIVNUM_PARALLEL_MODE << 3; //0x31
    }

    u8TsConfigData |= ISDBT_TS_DATA_SWAP << 1;
    u8TsConfigData |= ISDBT_TS_CLK_INV << 2;

    return MDrv_DMD_ISDBT_SetSerialControl(u8TsConfigData);
}

float EXTERN_ISDBT_GetSNR(void)
{
    float  f_snr;

    MDrv_DMD_ISDBT_GetSNR(&f_snr);
    printf("SNR value = %f\n", f_snr);
    return f_snr;
}

FUNCTION_RESULT EXTERN_ISDBT_GetSignalStrength(WORD *strength)
{
    FUNCTION_RESULT ret = E_RESULT_SUCCESS;
    MS_U16  u16Strength;

    MDrv_DMD_ISDBT_GetSignalStrength(&u16Strength);
    *strength = u16Strength;
    if ( *strength > 100 )
        ret = E_RESULT_FAILURE;
    return ret;
}
FUNCTION_RESULT EXTERN_ISDBT_GetSignalQuality(WORD *quality)
{
    FUNCTION_RESULT ret = E_RESULT_SUCCESS;

    *quality = MDrv_DMD_ISDBT_GetSignalQuality();
    //printf("EXTERN_ISDBT_GetSignalQuality = %ld\n",  *quality);
    if ( *quality > 100 )
        ret = E_RESULT_FAILURE;
    return ret;
}
BOOLEAN EXTERN_ISDBT_WriteReg(MS_U16 RegAddr, MS_U8 u8Data)
{
    return MDrv_DMD_ISDBT_SetReg(RegAddr, u8Data);
}
BOOLEAN EXTERN_ISDBT_ReadReg(MS_U16 RegAddr, MS_U8* pu8Data)
{
    return MDrv_DMD_ISDBT_GetReg(RegAddr, pu8Data);
}

BOOLEAN EXTERN_ISDBT_Exit ( void )
{
    return MDrv_DMD_ISDBT_Exit();
}

void EXTERN_ISDBT_Power_ON_OFF(MS_U8 bPowerOn)
{
    bPowerOn = bPowerOn;
}

BOOLEAN EXTERN_ISDBT_Power_Save(void)
{

    return TRUE;
}

/************************************************************************************************
  Subject:    TS1 output control
  Function:   EXTERN_DVBT_PAD_TS1_Enable
  Parmeter:   flag : TRUE For Turn on TS1, FALSE For Turn off TS1
  Return:     void
  Remark:
*************************************************************************************************/
void EXTERN_ISDBT_PAD_TS1_Enable(BOOLEAN flag)
{
    printf(" @EXTERN_ISDBT_PAD_TS1_Enable... \n");
    if(flag) // PAD_TS1 Enable TS CLK PAD
    {

    }
    else // PAD_TS1 Disable TS CLK PAD
    {

    }
}

#undef _EXTERN_ISDBT_C_


