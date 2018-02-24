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

////////////////////////////////////////////////////////////////////////////////
//
/// @file msAPI_IR.h
/// This file includes MStar application interface for IR process
/// @brief API for Irda Control
/// @author MStar Semiconductor, Inc.
//
////////////////////////////////////////////////////////////////////////////////

#define MSAPI_IR_C

#include <string.h>
#include "MsCommon.h"
#include "MsTypes.h"

#include "debug.h"
#include "sysinfo.h"

#include "MsOS.h"
#include "GPIO.h"

#include "msIR.h"
#include "msKeypad.h"

#include "drvBDMA.h"
#include "drvpower_if.h"
#include "drvPM.h"

#include "SysInit.h"
#include "drvCPU.h"
#include "drvIR.h"
#include "drvSAR.h"

#include "msAPI_IR.h"
#include "msAPI_DrvInit.h"

#if ENABLE_HOTEL_MODE_FUNCTION
#include "MApp_GlobalSettingSt.h"
#endif


//******************************************************************************

#define MAIN_LOOP_TIMING_MEASURE    0

static BOOLEAN bMailBoxIR=FALSE;

static MS_U8 u8IRUpdKey=0xFF;
static MS_U8 u8IRUpdRepeat=0;
static MS_U8 u8KpdUpdKey=0xFF;
static MS_U8 u8KpdUpdRepeat=0;

//******************************************************************************

#define MSAPI_IR_DBG(x)             //x
#define MSAPI_KEYPAD_DBG(x)         //x

//******************************************************************************

void msAPI_IR_Callback(MS_U8 u8Key, MS_U8 u8Repeat)
{
    MSAPI_IR_DBG(printf("[MApp_IR_Callback]: u8Key=0x%02X u8Repeat=0x%02X\n",u8Key,u8Repeat));

    u8IRUpdKey = u8Key;
    u8IRUpdRepeat = u8Repeat;
}

BOOLEAN msAPI_IR_Initialize(void)
{
#if (PM_RUNS_IN == PM_RUNS_IN_FLASH)
    {
        return MSRET_OK;
    }
#elif (PM_RUNS_IN == PM_RUNS_IN_CACHE )
    return MSRET_OK;
#else

    IR_RegCfg tIRRegCfg =
    {
        .u8Ctrl0 = IR_LEADER_CODE_CHECKING_OPTION,
        .u8Ctrl1 = 0x01,
        .u8Clk_mhz = MST_XTAL_CLOCK_MHZ,
        .u8HdrCode0 = IR_HEADER_CODE0,
        .u8HdrCode1 = IR_HEADER_CODE1,
        .u8CCodeBytes = 2,
        .u8CodeBits = 32,  //(32bits==4bytes)
    };

    IR_TimeBnd tIRTimeBnd =
    {
        .tHdr={
            .s16Time = IR_HEADER_CODE_TIME,
            .s8UpBnd = IR_HEADER_CODE_TIME_UB,
            .s8LoBnd = IR_HEADER_CODE_TIME_LB},
        .tOff={
            .s16Time = IR_OFF_CODE_TIME,
            .s8UpBnd = IR_OFF_CODE_TIME_UB,
            .s8LoBnd = IR_OFF_CODE_TIME_LB},
        .tOffRpt={
            .s16Time = IR_OFF_CODE_RP_TIME,
            .s8UpBnd = IR_OFF_CODE_RP_TIME_UB,
            .s8LoBnd = IR_OFF_CODE_RP_TIME_LB},
        .tLg01Hg={
            .s16Time = IR_LOGI_01H_TIME,
            .s8UpBnd = IR_LOGI_01H_TIME_UB,
            .s8LoBnd = IR_LOGI_01H_TIME_LB},
        .tLg0={
            .s16Time = IR_LOGI_0_TIME,
            .s8UpBnd = IR_LOGI_0_TIME_UB,
            .s8LoBnd = IR_LOGI_0_TIME_LB},
        .tLg1={
            .s16Time = IR_LOGI_1_TIME,
            .s8UpBnd = IR_LOGI_1_TIME_UB,
            .s8LoBnd = IR_LOGI_1_TIME_LB}
    };

 #ifdef MSOS_TYPE_LINUX
    #define PA_PM_Buffer    0x0007DC0000
    IR_RegCfg* pirRegCfg = (IR_RegCfg*)_PA2VA(PA_PM_Buffer);
    IR_TimeBnd* pirTimeBnd = (IR_TimeBnd*)_PA2VA(PA_PM_Buffer);
 #else
  #ifdef  __AEONR2__
    #define PA_PM_Buffer    PM51_MEM_ADR
  #else//MIPS_CHAKRA
    #define PA_PM_Buffer    ((PM51_MEM_MEMORY_TYPE & MIU1) ? (PM51_MEM_ADR | MIU_INTERVAL): PM51_MEM_ADR)
  #endif
    IR_RegCfg* pirRegCfg=(IR_RegCfg*)_PA2VA(PA_PM_Buffer);
    IR_TimeBnd* pirTimeBnd=(IR_TimeBnd*)_PA2VA(PA_PM_Buffer);
 #endif

    // no need to do IR Initialize in PM 2.0
    if ( !MDrv_PM_Check_Version(TRUE) )
    {
        return MSRET_OK;
    }

    MSAPI_IR_DBG(printf("\r\n >> msAPI_IR_Initialize \n"));

    //(0) For debugging
    //printf("MDrv_IR_SetDbgLevel\n");
    //MDrv_IR_SetDbgLevel(E_IR_DBGLVL_INFO);

    //(1) Initialization
  #ifdef MSOS_TYPE_LINUX
    memcpy((void*)pirRegCfg,(void*)&tIRRegCfg,sizeof(IR_RegCfg));
  #else
    memcpy((void*)pirRegCfg,(void*)&tIRRegCfg,sizeof(IR_RegCfg));
    MsOS_Dcache_Flush((MS_U32)pirRegCfg, sizeof(IR_RegCfg));
  #endif

    if ( MDrv_IR_Init((IR_RegCfg*)PA_PM_Buffer) == E_IR_FAIL )
    {
        MSAPI_IR_DBG(printf("MDrv_IR_Init fails...\n"));
        return MSRET_ERROR;
    }

    //(2) Configure Time Bounds
  #ifdef MSOS_TYPE_LINUX
    memcpy((void*)pirTimeBnd,(void*)&tIRTimeBnd,sizeof(IR_TimeBnd));
  #else
    memcpy((void*)pirTimeBnd,(void*)&tIRTimeBnd,sizeof(IR_TimeBnd));
    MsOS_Dcache_Flush((MS_U32)pirTimeBnd, sizeof(IR_TimeBnd));
  #endif

    if ( MDrv_IR_Config((IR_TimeBnd*)PA_PM_Buffer) == E_IR_FAIL )
    {
        MSAPI_IR_DBG(printf("MDrv_IR_Config fails...\n"));
        return MSRET_ERROR;
    }

    //(3) Install callback function to get key
    if ( MDrv_IR_SetCallback(msAPI_IR_Callback) == E_IR_FAIL )
    {
        MSAPI_IR_DBG(printf("MDrv_IR_SetCallback fails...\n"));
        return MSRET_ERROR;
    }

  #if 0
    //(4) Enable IR to receive key
    if(MDrv_IR_Enable(TRUE)==E_IR_FAIL)
    {
        printf("MDrv_IR_Enable fails\n");
        return MSRET_ERROR;
    }
  #endif

  #if 0//For test
    {
        const IR_DrvInfo* pIrDrvInfo;
      #ifdef MSOS_TYPE_LINUX
        pIrDrvInfo = (IR_DrvInfo*)_PA2VA((MS_U32)MDrv_IR_GetInfo());
      #else
        pIrDrvInfo = MDrv_IR_GetInfo();
      #endif
        printf("### pIrDrvInfo->u8IsDecodeEn=%d\n",pIrDrvInfo->u8IsDecodeEn);
        printf("### pIrDrvInfo->u8CodeBits=%d\n",pIrDrvInfo->u8CodeBits);
        printf("### pIrDrvInfo->u8CCodeBytes=%d\n",pIrDrvInfo->u8CCodeBytes);
        printf("### pIrDrvInfo->u8FifoDepth=%d\n",pIrDrvInfo->u8FifoDepth);
    }
  #endif

    return MSRET_OK;

#endif
}

void msAPI_KeyPad_Callback(MS_U8 u8Key, MS_U8 u8Repeat)
{
    MSAPI_KEYPAD_DBG(printf("[msAPI_Keypad_Callback]: u8Key=0x%02X u8Repeat=0x%02X\n",u8Key,u8Repeat));

    u8KpdUpdKey = u8Key;
    u8KpdUpdRepeat = u8Repeat;
}

BOOLEAN msAPI_KeyPad_Initialize(void)
{
#if (PM_RUNS_IN == PM_RUNS_IN_FLASH)//No PM51 but runs in SPI flash
        {
            return MSRET_OK;
        }
#elif (PM_RUNS_IN == PM_RUNS_IN_CACHE)//No PM51 but runs in MIPS L1 cache
        {
            return MSRET_OK;
        }
#else

 #ifdef MSOS_TYPE_LINUX
    #define PA_PM_Buffer    0x0007DC0000
    SAR_RegCfg* psarRegCfgCh = (SAR_RegCfg*)_PA2VA(PA_PM_Buffer);
 #else
  #ifdef  __AEONR2__
    #define PA_PM_Buffer    PM51_MEM_ADR
  #else//MIPS_CHAKRA
    #define PA_PM_Buffer    ((PM51_MEM_MEMORY_TYPE & MIU1) ? (PM51_MEM_ADR | MIU_INTERVAL): PM51_MEM_ADR)
  #endif
    SAR_RegCfg* psarRegCfgCh=(SAR_RegCfg*)_PA2VA(PA_PM_Buffer);
 #endif
    MS_U8 u8ChEnb[KEYPAD_CHANNEL_SUPPORT]={ENABLE_KPDCHAN_1,ENABLE_KPDCHAN_2,ENABLE_KPDCHAN_3,ENABLE_KPDCHAN_4};
    MS_U8 u8UpBnd[KEYPAD_CHANNEL_SUPPORT]={KEYPAD_CH1_UB,KEYPAD_CH2_UB,KEYPAD_CH3_UB,KEYPAD_CH4_UB};
    MS_U8 u8LoBnd[KEYPAD_CHANNEL_SUPPORT]={KEYPAD_CH1_LB,KEYPAD_CH2_LB,KEYPAD_CH3_LB,KEYPAD_CH4_LB};
    MS_U8 u8ChLvls[KEYPAD_CHANNEL_SUPPORT]={ADC_CH1_LEVELS,ADC_CH2_LEVELS,ADC_CH3_LEVELS,ADC_CH4_LEVELS};
    MS_U8 u8ChThrs[ADC_KEY_CHANNEL_NUM][8]={
      {ADC_KEY_1_L0,ADC_KEY_1_L1,ADC_KEY_1_L2,ADC_KEY_1_L3,ADC_KEY_1_L4,ADC_KEY_1_L5,ADC_KEY_1_L6,ADC_KEY_1_L7},
      {ADC_KEY_2_L0,ADC_KEY_2_L1,ADC_KEY_2_L2,ADC_KEY_2_L3,ADC_KEY_2_L4,ADC_KEY_2_L5,ADC_KEY_2_L6,ADC_KEY_2_L7}
    };
    MS_U8 u8ChKey[ADC_KEY_CHANNEL_NUM][8]={
      {ADC_KEY_1_L0_FLAG,ADC_KEY_1_L1_FLAG,ADC_KEY_1_L2_FLAG,ADC_KEY_1_L3_FLAG,ADC_KEY_1_L4_FLAG,ADC_KEY_1_L5_FLAG,ADC_KEY_1_L6_FLAG,ADC_KEY_1_L7_FLAG},
      {ADC_KEY_2_L0_FLAG,ADC_KEY_2_L1_FLAG,ADC_KEY_2_L2_FLAG,ADC_KEY_2_L3_FLAG,ADC_KEY_2_L4_FLAG,ADC_KEY_2_L5_FLAG,ADC_KEY_2_L6_FLAG,ADC_KEY_2_L7_FLAG}
    };
    MS_U8 j,k,u8Idx;

    MSAPI_KEYPAD_DBG(printf("\r\n >> msAPI_KeyPad_Initialize \n"));

    //(0) For debugging
    //printf("MDrv_SAR_SetDbgLevel...!\n");
    //MDrv_SAR_SetDbgLevel(E_SAR_DBGLVL_INFO);

    //(1) Initialization
    if ( MDrv_SAR_Init() == E_SAR_FAIL )
    {
        MSAPI_KEYPAD_DBG(printf("MDrv_SAR_Init fails\n"));
        return MSRET_ERROR;
    }

    //(2) Configure parameters
    for (u8Idx=0,k=0; k<KEYPAD_CHANNEL_SUPPORT; k++)
    {
        if (u8ChEnb[k]==ENABLE)
        {
            psarRegCfgCh->u8SARChID = k;
            psarRegCfgCh->u8UpBnd = u8UpBnd[k];
            psarRegCfgCh->u8LoBnd = u8LoBnd[k];
            psarRegCfgCh->u8KeyLevelNum = u8ChLvls[k];

            for(j=0;j<u8ChLvls[k];j++)
            {
                psarRegCfgCh->u8KeyThreshold[j] = u8ChThrs[u8Idx][j];
                psarRegCfgCh->u8KeyCode[j] = u8ChKey[u8Idx][j];
            }

            // configure keypad channel
            MsOS_Dcache_Flush((MS_U32)psarRegCfgCh, sizeof(SAR_RegCfg));
            MsOS_FlushMemory();

            if ( MDrv_SAR_Config((SAR_RegCfg*)PA_PM_Buffer) == E_SAR_FAIL )
            {
                MSAPI_KEYPAD_DBG(printf("MDrv_SAR_Config fails\n"));
                return MSRET_ERROR;
            }

            if ( (++u8Idx) >= ADC_KEY_CHANNEL_NUM )
            {
                break;
            }
        }
    }

    //(3) Install callback function to get key
    if ( MDrv_PM_Check_Version(TRUE) )
    {
        if ( MDrv_SAR_SetCallback(msAPI_KeyPad_Callback) == E_SAR_FAIL )
        {
            MSAPI_KEYPAD_DBG(printf("MDrv_SAR_SetCallback fails\n"));
            return MSRET_ERROR;
        }
    }

    //(4) Enable SAR to receive key
    if ( MDrv_SAR_Enable(TRUE) == E_SAR_FAIL )
    {
        MSAPI_KEYPAD_DBG(printf("MDrv_SAR_Enable fails\n"));
        return MSRET_ERROR;
    }

    return MSRET_OK;

#endif
}

/******************************************************************************/
/// API for Get Irda Key:
/// Get Irda Key value and Status
/// @param *u8key \b IN: Pointer to Irda Key Mapping value for return
/// @param *u8Repstatus \b IN: Pointer to Irda Repeat and FIFO status for return
/// @return BOOLEAN: Success or not
/// - TRUE: Success
/// - FALSE: Fail
/******************************************************************************/
BOOLEAN msAPI_GetIRKey(U8 *u8key,U8 *u8Repstatus)
{
    BOOLEAN bOkNG = msIR_GetIRKeyCode(u8key, u8Repstatus);

    if(MDrv_IR_IsIRkeyEnabled(*u8key) == FALSE)
        bOkNG = MSRET_ERROR; // Do NOT process IR key.

    return bOkNG;
}

/******************************************************************************/
/// API for clear IR FIFO:
/// Called by application init or preparation
/******************************************************************************/
void msAPI_ClearIRFIFO(void)
{
    msIR_Clear_FIFO();
}

/******************************************************************************/
/// API for Get Keypad Key:
/// Get Keypad Key value and Status
/// @param *u8key \b IN: Pointer to Keypad Key Mapping value for return
/// @param *u8Repstatus \b IN: Pointer to Keypad Repeat and FIFO status for return
/// @return BOOLEAN:
/// - TRUE: Success
/// - FALSE: FAIL
/******************************************************************************/
BOOLEAN msAPI_GetKeyPad(U8 *u8key,U8 *u8Repstatus)
{
#if ENABLE_HOTEL_MODE_FUNCTION
    if(stGenSetting.g_stHotelModeSetting.u8KB_Lock && IS_HOTEL_LOCK_ON)
        return FALSE;
    else
#endif
	return FALSE; //gchen @ 20180203 //remove getkeypad function
      return msKeypad_GetKey(u8key, u8Repstatus);
}

/******************************************************************************/
/// API for Power Down:
/// Execute Power sequence, be called after press Power Button to Power OFF
/// @param u8Mode \b IN: Power down Mode
/******************************************************************************/
void msAPI_Key_PowerDown_Mode(U8 u8Mode)
{
#if POWER_DOWN_SEQ
    MDrv_Power_Set_PDMode(u8Mode);

    switch(u8Mode)
    {
        case POWERMODE_S1:
            //MDrv_MIU_SetFrequency(MIU_BOOTUP_CLOCK_MHZ);
            break;

        case POWERMODE_S2:
        case POWERMODE_S3:
        case POWERMODE_S4:
            msAPI_Power_PowerDown_EXEC();
            break;
        default:
            break;
    }
#endif
}


void msAPI_EnableMBIR(BOOLEAN useMBIR)
{
    bMailBoxIR=useMBIR;

#if ((IR_MODE_SEL == IR_TYPE_SWDECODE_MODE)||(IR_MODE_SEL == IR_TYPE_SWDECODE_KON_MODE)||(IR_MODE_SEL == IR_TYPE_SWDECODE_RC5_MODE)\
     ||(IR_MODE_SEL == IR_TYPE_SWDECODE_SHA_MODE)||(IR_MODE_SEL == IR_TYPE_SWDECODE_TOSHIBA_MODE)\
     ||(IR_MODE_SEL == IR_TYPE_SWDECODE_RCA_MODE)||(IR_MODE_SEL == IR_TYPE_SWDECODE_SKY_MODE))
    if(bMailBoxIR)
    {
        MsOS_DisableInterrupt(E_INT_FIQ_IR);;
        printf("Enable MBIR!!\n");
    }
    else
    {
        MsOS_EnableInterrupt(E_INT_FIQ_IR);
        printf("Disable MBIR!!\n");
    }
#endif
}

BOOLEAN msAPI_IsMBIREnabled(void)
{
    return bMailBoxIR;
}



//******************************************************************************

#undef MSAPI_IR_C

