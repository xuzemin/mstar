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
#define _INTERN_DTMB_C_

#include <math.h>
#include "Tuner.h"
#include "MsOS.h"
#include "debug.h"

#include "drvIIC.h"
#include "drvDMD_common.h"
#include "drvDMD_DTMB.h"       //matt add for integrate DTMB utopia driver
#include "drvDMD_VD_MBX.h"


#define ERR_DEMOD_MSB(x)  			//  x
#define DBG_DOMOD_MSB(x)  			//   x
#define DBG_DEMOD_CHECK_LOCK(x)   // x
#define DBG_DEMOD_INFO(x)   // x
#define DBG_SSI(x)        //  x
#define DBG_SQI(x)        //  x

#define DTMB_CASHMERE_SLAVE_ID  0xD2  //0xF2

//#if( (FRONTEND_TUNER_TYPE == MxL_601SI_TUNER) || (FRONTEND_TUNER_TYPE == SILAB_2158_TUNER))
#if ((FRONTEND_TUNER_TYPE == MxL_601SI_TUNER) || (FRONTEND_TUNER_TYPE == MxL_661SI_TUNER))
#define DTMB_TUNER_IF      		DTMB_TUNER_IF_FREQ_KHz
#elif (FRONTEND_TUNER_TYPE == RAFAEL_R828_TUNER)
#define DTMB_TUNER_IF      		4063
#elif (FRONTEND_TUNER_TYPE == SILAB_2158_TUNER)
#define DTMB_TUNER_IF      		6000
#else
#define DTMB_TUNER_IF      		5000
#endif
#define usleep(x) 					MsOS_DelayTask(x/1000)

#if TS_PARALLEL_DTMB_OUTPUT
#define DTMB_TS_SERIAL		  0x00
#else
#define DTMB_TS_SERIAL		  0x01
#endif
// Division number of TS clock rate
// Formula: TS Clk Rate= 216 MHz/reg_dtmb_ts_clk_divnum
// Ex: DTMB_TS_CLK_DIVNUM = 31 => TS Clk = 216/31= 6.967 MHz
#define DTMB_TS_CLK_DIVNUM_SERIAL_MODE   4
#define DTMB_TS_CLK_DIVNUM_PARALLEL_MODE  31

#if (DTMB_TS_SERIAL)
#define DTMB_TS_CLK_DIVNUM	  DTMB_TS_CLK_DIVNUM_SERIAL_MODE
#else
#define DTMB_TS_CLK_DIVNUM	  DTMB_TS_CLK_DIVNUM_PARALLEL_MODE
#endif

#define DTMB_TS_DATA_SWAP  0x00  // TS data inversion
#define DTMB_TS_CLK_INV      TS_CLK_INV  // TS clock inverseion //this define will depend on hw main board
#if( (FRONTEND_TUNER_TYPE == NXP_TDA18275_TUNER)     \
    || (FRONTEND_TUNER_TYPE == RAFAEL_R840_TUNER)    \
    || (FRONTEND_TUNER_TYPE == RAFAEL_R842_TUNER)    \
    || (FRONTEND_TUNER_TYPE == NXP_TDA182I5a_TUNER)  \
    )
#define DTMB_IQ_SWAP   0x01          
#else
#define DTMB_IQ_SWAP   0x00          // IQ Swap  //this define will depend on tuner
#endif
#define DTMB_IFAGC_REF 0x500              //this define will depend on tuner

#if( CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA )
    #define DTMB_TDI_START_ADDR (DMD_DTMB_ADR/8)   // System must allocate a 7MB memory space starting from this (128-bit)address
#else
    #define DTMB_TDI_START_ADDR (DMD_DTMB_ADR/16)   // System must allocate a 7MB memory space starting from this (128-bit)address
#endif

//static BOOL s_bI2C_FastMode = false;

float INTERN_DTMB_GetSNR(void);

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

BOOLEAN INTERN_DTMB_Power_On_Initialization(void)
{
    BOOLEAN   bResult = true;
    DMD_DTMB_InitData sDMD_DTMB_InitData;
    static MS_U8 u8DMD_DTMB_InitExt[]={1}; // RFAGC tristate control default value, 1:trisate 0:non-tristate,never modify unless you know the meaning

    printf("INTERN_DTMB_Power_On_Initialization\n");

    MDrv_DMD_PreInit();

    // copy tuner config
    //mapi_interface::Get_mapi_pcb()->GetIsdbTuner(0)->ExtendCommand(mapi_tuner_datatype::E_TUNER_SUBCMD_GET_IQ_SWAP, E_TUNER_DTV_ISDB_MODE, NULL, &u8IqSwap);
    //mapi_interface::Get_mapi_pcb()->GetIsdbTuner(0)->ExtendCommand(mapi_tuner_datatype::E_TUNER_SUBCMD_GET_DTV_IF_FREQ, E_TUNER_DTV_ISDB_MODE, NULL, &u16DtvIFFreqKHz);
    sDMD_DTMB_InitData.u16IF_KHZ = DTMB_TUNER_IF;//u16DtvIFFreqKHz;
    sDMD_DTMB_InitData.bIQSwap = DTMB_IQ_SWAP;
    sDMD_DTMB_InitData.u16DTMBAGCLockCheckTime = 50;
    sDMD_DTMB_InitData.u16DTMBPreLockCheckTime = 300;
    sDMD_DTMB_InitData.u16DTMBPNMLockCheckTime = 550;  //7/24 ohya++
    sDMD_DTMB_InitData.u16DTMBFECLockCheckTime = 5000;
    sDMD_DTMB_InitData.u32TdiStartAddr = DTMB_TDI_START_ADDR;

    // 7/24++
    sDMD_DTMB_InitData.u8IS_DUAL=0;//0
    sDMD_DTMB_InitData.bIsExtDemod=0;//0


    sDMD_DTMB_InitData.u16QAMAGCLockCheckTime = 50;
    sDMD_DTMB_InitData.u16QAMPreLockCheckTime = 1000;
    sDMD_DTMB_InitData.u16QAMMainLockCheckTime = 3000;

    sDMD_DTMB_InitData.u8DMD_DTMB_InitExt = u8DMD_DTMB_InitExt;

    //TS[begin]
    //Parallel mode
    //sDMD_DTMB_InitData.u5TsConfigByte_DivNum = DTMB_TS_CLK_DIVNUM;
    //sDMD_DTMB_InitData.u1TsConfigByte_ClockInv = DTMB_TS_CLK_INV;
    //sDMD_DTMB_InitData.u1TsConfigByte_DataSwap = 0;
    //sDMD_DTMB_InitData.u1TsConfigByte_SerialMode = DTMB_TS_SERIAL;
    //Serial mode
    sDMD_DTMB_InitData.u5TsConfigByte_DivNum = DTMB_TS_CLK_DIVNUM;
    sDMD_DTMB_InitData.u1TsConfigByte_ClockInv = DTMB_TS_CLK_INV;
    sDMD_DTMB_InitData.u1TsConfigByte_DataSwap = DTMB_TS_DATA_SWAP;
    sDMD_DTMB_InitData.u1TsConfigByte_SerialMode = DTMB_TS_SERIAL;

    //TS[end]

    //I2C[begin]
    sDMD_DTMB_InitData.u8I2CSlaveAddr = DTMB_CASHMERE_SLAVE_ID;
    sDMD_DTMB_InitData.u8I2CSlaveBus = TUNER_IIC_BUS;
    //sDMD_DTMB_InitData.bIsExtDemod = TRUE;
    sDMD_DTMB_InitData.I2C_WriteBytes = MDrv_IIC_WriteBytes;
    sDMD_DTMB_InitData.I2C_ReadBytes = MDrv_IIC_ReadBytes;
    //I2C[end]


    MDrv_SYS_DMD_VD_MBX_Init();
	MDrv_DMD_DTMB_Initial_Hal_Interface();
    MDrv_DMD_DTMB_Init(&sDMD_DTMB_InitData, sizeof(sDMD_DTMB_InitData));
    return bResult;
}
#if 0
void INTERN_DTMB_Init (void)
{
    DMD_DTMB_InitData sDMD_DTMB_InitData;
    static MS_U8 u8DMD_DTMB_InitExt[]={1}; // RFAGC tristate control default value, 1:trisate 0:non-tristate,never modify unless you know the meaning

    printf("INTERN_DTMB_Init\n");

    MDrv_DMD_PreInit();

    // copy tuner config
    //mapi_interface::Get_mapi_pcb()->GetIsdbTuner(0)->ExtendCommand(mapi_tuner_datatype::E_TUNER_SUBCMD_GET_IQ_SWAP, E_TUNER_DTV_ISDB_MODE, NULL, &u8IqSwap);
    //mapi_interface::Get_mapi_pcb()->GetIsdbTuner(0)->ExtendCommand(mapi_tuner_datatype::E_TUNER_SUBCMD_GET_DTV_IF_FREQ, E_TUNER_DTV_ISDB_MODE, NULL, &u16DtvIFFreqKHz);
    sDMD_DTMB_InitData.u16IF_KHZ = DTMB_TUNER_IF;//u16DtvIFFreqKHz;
    sDMD_DTMB_InitData.bIQSwap = DTMB_IQ_SWAP;
    sDMD_DTMB_InitData.u16DTMBAGCLockCheckTime = 50;
    sDMD_DTMB_InitData.u16DTMBPreLockCheckTime = 300;
    sDMD_DTMB_InitData.u16DTMBPNMLockCheckTime = 550;  //7/24 ohya++
    sDMD_DTMB_InitData.u16DTMBFECLockCheckTime = 5000;
    sDMD_DTMB_InitData.u32TdiStartAddr = DTMB_TDI_START_ADDR;

    // 7/24++
    sDMD_DTMB_InitData.u8IS_DUAL=0;//0
    sDMD_DTMB_InitData.bIsExtDemod=0;//0


    sDMD_DTMB_InitData.u16QAMAGCLockCheckTime = 50;
    sDMD_DTMB_InitData.u16QAMPreLockCheckTime = 1000;
    sDMD_DTMB_InitData.u16QAMMainLockCheckTime = 3000;

    sDMD_DTMB_InitData.u8DMD_DTMB_InitExt = u8DMD_DTMB_InitExt;

    //TS[begin]
    //Parallel mode
    //sDMD_DTMB_InitData.u5TsConfigByte_DivNum = DTMB_TS_CLK_DIVNUM;
    //sDMD_DTMB_InitData.u1TsConfigByte_ClockInv = DTMB_TS_CLK_INV;
    //sDMD_DTMB_InitData.u1TsConfigByte_DataSwap = 0;
    //sDMD_DTMB_InitData.u1TsConfigByte_SerialMode = DTMB_TS_SERIAL;
    //Serial mode
    sDMD_DTMB_InitData.u5TsConfigByte_DivNum = DTMB_TS_CLK_DIVNUM;
    sDMD_DTMB_InitData.u1TsConfigByte_ClockInv = DTMB_TS_CLK_INV;
    sDMD_DTMB_InitData.u1TsConfigByte_DataSwap = DTMB_TS_DATA_SWAP;
    sDMD_DTMB_InitData.u1TsConfigByte_SerialMode = DTMB_TS_SERIAL;

    //TS[end]

    //I2C[begin]
    sDMD_DTMB_InitData.u8I2CSlaveAddr = DTMB_CASHMERE_SLAVE_ID;
    sDMD_DTMB_InitData.u8I2CSlaveBus = TUNER_IIC_BUS;
    //sDMD_DTMB_InitData.bIsExtDemod = TRUE;
    sDMD_DTMB_InitData.I2C_WriteBytes = MDrv_IIC_WriteBytes;
    sDMD_DTMB_InitData.I2C_ReadBytes = MDrv_IIC_ReadBytes;
    //I2C[end]

    MDrv_DMD_DTMB_Init(&sDMD_DTMB_InitData, sizeof(sDMD_DTMB_InitData));
}
#endif

BOOLEAN INTERN_DTMB_Lock(COFDM_LOCK_STATUS eStatus)
{
    DMD_DTMB_LOCK_STATUS eLockStatus = DMD_DTMB_UNLOCK;
    BOOLEAN ret_lock = FALSE;

  //  printf("dan COFDM_LOCK_STATUS = %d\n", (MS_U8)eStatus);


    if(eStatus == COFDM_PSYNC_LOCK)
        eLockStatus = MDrv_DMD_DTMB_GetLock(DMD_DTMB_GETLOCK_DTMB_PNPLOCK);//VT
    else if(eStatus == COFDM_FEC_LOCK)
    {
        eLockStatus = MDrv_DMD_DTMB_GetLock(DMD_DTMB_GETLOCK);
      /*  if(eLockStatus == DMD_DTMB_LOCK)
        {
            INTERN_DTMB_GetSNR();
            printf("FEC lock\n");
        }
        */
    }

    if(eLockStatus == DMD_DTMB_LOCK)
        ret_lock = TRUE;
    /*
    eLockStatus = MDrv_DMD_DTMB_GetLock(DMD_DTMB_GETLOCK);
    switch (eLockStatus) // _UTOPIA
    {
        case DMD_DTMB_LOCK:
            ret_lock = TRUE;
            printf("FEC lock\n");
            break;
        case DMD_DTMB_CHECKING:
            ret_lock = FALSE;
            break;
        case DMD_DTMB_CHECKEND:
            ret_lock = FALSE;
            break;
        case DMD_DTMB_UNLOCK:
            ret_lock = FALSE;
            break;
        default:
            printf("DTMB_GetLockStatus error\n");
            break;
    }
    */
    return ret_lock;
}
BOOLEAN INTERN_DTMB_Config(RF_CHANNEL_BANDWIDTH BW, BOOLEAN bSerialTS, BOOLEAN bPalBG, BOOLEAN bLPSel)
{
    BW = BW;
    bSerialTS = bSerialTS;
    bPalBG = bPalBG;
    bLPSel = bLPSel;
    return true;
}

BOOLEAN INTERN_DTMB_Active(BOOLEAN bEnable)
{
    return MDrv_DMD_DTMB_SetConfig(DMD_DTMB_DEMOD_DTMB,bEnable);
}

BOOLEAN INTERN_DTMB_Serial_Control(BOOLEAN bEnable)
{
    MS_U8  u8TsConfigData;

    u8TsConfigData = 0;
    //printf("dan enter MSB1400_Serial_Control\n");
    if(bEnable == TRUE)  //serial mode
    {
        u8TsConfigData |= 0x01;
        u8TsConfigData |= DTMB_TS_CLK_DIVNUM_SERIAL_MODE << 3;  //0x04
    }
    else
    {
        u8TsConfigData &= ~0x01;
        u8TsConfigData |= DTMB_TS_CLK_DIVNUM_PARALLEL_MODE << 3; //0x31
    }

    u8TsConfigData |= DTMB_TS_DATA_SWAP << 1;
    u8TsConfigData |= DTMB_TS_CLK_INV << 2;

    return MDrv_DMD_DTMB_SetSerialControl(u8TsConfigData);
}

float INTERN_DTMB_GetSNR(void)
{
    float  f_snr;

    f_snr = 0;
    //MDrv_DMD_DTMB_GetSNR(&f_snr);
    printf("SNR value = %f\n", f_snr);
    return f_snr;
}

FUNCTION_RESULT INTERN_DTMB_GetSignalStrength(WORD *strength)
{
    FUNCTION_RESULT ret = E_RESULT_SUCCESS;
    MS_U16  u16Strength;

    MDrv_DMD_DTMB_GetSignalStrength(&u16Strength);
    *strength = u16Strength;
    if ( *strength > 100 )
        ret = E_RESULT_FAILURE;
    return ret;
}
FUNCTION_RESULT INTERN_DTMB_GetSignalQuality(WORD *quality)
{
    FUNCTION_RESULT ret = E_RESULT_SUCCESS;

    *quality = MDrv_DMD_DTMB_GetSignalQuality();
    //printf("INTERN_DTMB_GetSignalQuality = %ld\n",  *quality);
    if ( *quality > 100 )
        ret = E_RESULT_FAILURE;
    return ret;
}
BOOLEAN INTERN_DTMB_WriteReg(MS_U16 RegAddr, MS_U8 u8Data)
{
    return MDrv_DMD_DTMB_SetReg(RegAddr, u8Data);
}
BOOLEAN INTERN_DTMB_ReadReg(MS_U16 RegAddr, MS_U8* pu8Data)
{
    return MDrv_DMD_DTMB_GetReg(RegAddr, pu8Data);
}

BOOLEAN INTERN_DTMB_Exit ( void )
{
    return MDrv_DMD_DTMB_Exit();
}

void INTERN_DTMB_Power_ON_OFF(MS_U8 bPowerOn)
{
    bPowerOn = bPowerOn;
}

BOOLEAN INTERN_DTMB_Power_Save(void)
{

    return TRUE;
}

/************************************************************************************************
  Subject:    TS1 output control
  Function:   INTERN_DTMB_PAD_TS1_Enable
  Parmeter:   flag : TRUE For Turn on TS1, FALSE For Turn off TS1
  Return:     void
  Remark:
*************************************************************************************************/
void INTERN_DTMB_PAD_TS1_Enable(BOOLEAN flag)
{
    printf(" @INTERN_DTMB_PAD_TS1_Enable... \n");
    if(flag) // PAD_TS1 Enable TS CLK PAD
    {

    }
    else // PAD_TS1 Disable TS CLK PAD
    {

    }
}


#undef _INTERN_DTMB_C_


