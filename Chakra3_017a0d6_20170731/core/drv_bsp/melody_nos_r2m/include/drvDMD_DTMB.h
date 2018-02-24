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
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   drvDMD_DTMB.h
/// @brief  DTMB Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_DTMB_H_
#define _DRV_DTMB_H_

//-------------------------------------------------------------------------------------------------
//  Driver Capability
//-------------------------------------------------------------------------------------------------

#define DMD_DTMB_UTOPIA_EN                  1
#define DMD_DTMB_UTOPIA2_EN                 0

#define DMD_DTMB_STR_EN                     0
#define DMD_DTMB_MULTI_THREAD_SAFE          0
#define DMD_DTMB_MULTI_DMD_EN               1

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------

#include "MsTypes.h"
#if DMD_DTMB_UTOPIA_EN || DMD_DTMB_UTOPIA2_EN
#include "MsCommon.h"
#endif
#if DMD_DTMB_UTOPIA2_EN || DMD_DTMB_STR_EN
#include "utopia.h"
#endif

//-------------------------------------------------------------------------------------------------
//  Driver Capability
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------

#ifndef DLL_PUBLIC 
#define DLL_PUBLIC 
#endif

#if DMD_DTMB_MULTI_DMD_EN
#define DMD_DTMB_MAX_DEMOD_NUM          2
#else
#define DMD_DTMB_MAX_DEMOD_NUM          1
#endif

#if DMD_DTMB_UTOPIA_EN || DMD_DTMB_UTOPIA2_EN
#define MSIF_DMD_DTMB_LIB_CODE          {'D','M','D','_','D','T', 'M','B','_'} //Lib code
#define MSIF_DMD_DTMB_LIBVER            {'0','0'}                              //LIB version
#define MSIF_DMD_DTMB_BUILDNUM          {'0','0' }                             //Build Number
#define MSIF_DMD_DTMB_CHANGELIST        {'0','0','0','0','0','0','0','0'}      //P4 ChangeList Number

#define DMD_DTMB_VER                    /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_DMD_DTMB_LIB_CODE,             /* IP__                                             */  \
    MSIF_DMD_DTMB_LIBVER,               /* 0.0 ~ Z.Z                                        */  \
    MSIF_DMD_DTMB_BUILDNUM,             /* 00 ~ 99                                          */  \
    MSIF_DMD_DTMB_CHANGELIST,           /* CL#                                              */  \
    MSIF_OS
#endif // #if DMD_DTMB_UTOPIA_EN || DMD_DTMB_UTOPIA2_EN

#ifndef BIT_
#define BIT_(n)                                 (1 << (n))
#endif

#define DMD_DTMB_LOCK_DTMB_PNP_LOCK             BIT_(0)
#define DMD_DTMB_LOCK_DTMB_FEC_LOCK             BIT_(1)

#define DMD_DTMB_LOCK_DVBC_AGC_LOCK             BIT_(8)
#define DMD_DTMB_LOCK_DVBC_PRE_LOCK             BIT_(9)
#define DMD_DTMB_LOCK_DVBC_MAIN_LOCK            BIT_(10)

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------

typedef enum
{
    DMD_DTMB_HAL_CMD_Exit = 0,
    DMD_DTMB_HAL_CMD_InitClk,
    DMD_DTMB_HAL_CMD_Download,
    DMD_DTMB_HAL_CMD_FWVERSION,
    DMD_DTMB_HAL_CMD_SoftReset,
    DMD_DTMB_HAL_CMD_SetACICoef,
    DMD_DTMB_HAL_CMD_SetDTMBMode,
    DMD_DTMB_HAL_CMD_SetModeClean,
    DMD_DTMB_HAL_CMD_Set_QAM_SR,
    DMD_DTMB_HAL_CMD_Active,
    DMD_DTMB_HAL_CMD_AGCLock,
    DMD_DTMB_HAL_CMD_DTMB_PNP_Lock,
    DMD_DTMB_HAL_CMD_DTMB_FEC_Lock,
    DMD_DTMB_HAL_CMD_DVBC_PreLock,
    DMD_DTMB_HAL_CMD_DVBC_Main_Lock,
    DMD_DTMB_HAL_CMD_GetModulation,
    DMD_DTMB_HAL_CMD_ReadIFAGC,
    DMD_DTMB_HAL_CMD_ReadFrequencyOffset,
    DMD_DTMB_HAL_CMD_ReadSNRPercentage,
    DMD_DTMB_HAL_CMD_GetPreLdpcBer,
    DMD_DTMB_HAL_CMD_GetPreViterbiBer,
    DMD_DTMB_HAL_CMD_GetPostViterbiBer,
    DMD_DTMB_HAL_CMD_GetSNR,
    DMD_DTMB_HAL_CMD_TS_INTERFACE_CONFIG,
    DMD_DTMB_HAL_CMD_IIC_Bypass_Mode,
    DMD_DTMB_HAL_CMD_SSPI_TO_GPIO,
    DMD_DTMB_HAL_CMD_GPIO_GET_LEVEL,
    DMD_DTMB_HAL_CMD_GPIO_SET_LEVEL,
    DMD_DTMB_HAL_CMD_GPIO_OUT_ENABLE,
    DMD_DTMB_HAL_CMD_GET_REG,
    DMD_DTMB_HAL_CMD_SET_REG,
    DMD_DTMB_HAL_CMD_DoIQSwap
} DMD_DTMB_HAL_COMMAND;

typedef enum
{
    DMD_DTMB_DEMOD_DTMB,
    DMD_DTMB_DEMOD_DTMB_7M,
    DMD_DTMB_DEMOD_DTMB_6M,
    DMD_DTMB_DEMOD_DTMB_5M,
    DMD_DTMB_DEMOD_DVBC_64QAM,
    DMD_DTMB_DEMOD_DVBC_256QAM,
    DMD_DTMB_DEMOD_DVBC_16QAM,
    DMD_DTMB_DEMOD_DVBC_32QAM,
    DMD_DTMB_DEMOD_DVBC_128QAM,
    DMD_DTMB_DEMOD_MAX,
    DMD_DTMB_DEMOD_NULL = DMD_DTMB_DEMOD_MAX,
} DMD_DTMB_DEMOD_TYPE;

typedef struct
{
    union
    {
        float fSiCodeRate; //0.4, 0.6, 0.8
        float fDvbcSymRateL;
    };
    union
    {
        MS_U16 u8SiInterLeaver; //240, 720
        MS_U16 u8DvbcSymRateH;
    };
    union
    {
        MS_U8 u8SiQamMode; //4QAM, 16QAM, 32QAM, 64QAM
        MS_U8 u8DvbcQamMode;
    };
    MS_U8 u8SiNR;
    MS_U8 u8SiCarrierMode; //0: multiple carrier, 1:single carrier
    MS_U16 u16PNM; //420, 595, 945
    MS_U8  u8PNC; //0: variable, 1: constant
    DMD_DTMB_DEMOD_TYPE eDemodType; //DTMB or DVBC
} DMD_DTMB_MODULATION_INFO;

typedef struct
{
    MS_U8 u8Pin;
    union
    {
        MS_BOOL bLevel;
        MS_BOOL bIsOut;
    };
} DMD_DTMB_GPIO_PIN_DATA;

typedef struct
{
    MS_U16 u16Addr;
    MS_U8  u8Data;
} DMD_DTMB_REG_DATA;

typedef enum
{
    DMD_DTMB_DBGLV_NONE,    // disable all the debug message
    DMD_DTMB_DBGLV_INFO,    // information
    DMD_DTMB_DBGLV_NOTICE,  // normal but significant condition
    DMD_DTMB_DBGLV_WARNING, // warning conditions
    DMD_DTMB_DBGLV_ERR,     // error conditions
    DMD_DTMB_DBGLV_CRIT,    // critical conditions
    DMD_DTMB_DBGLV_ALERT,   // action must be taken immediately
    DMD_DTMB_DBGLV_EMERG,   // system is unusable
    DMD_DTMB_DBGLV_DEBUG,   // debug-level messages
} DMD_DTMB_DbgLv;

typedef enum
{
    DMD_DTMB_GETLOCK,
    DMD_DTMB_GETLOCK_DTMB_AGCLOCK,
    DMD_DTMB_GETLOCK_DTMB_PNPLOCK,
    DMD_DTMB_GETLOCK_DTMB_FECLOCK,
    DMD_DTMB_GETLOCK_DVBC_AGCLOCK,
    DMD_DTMB_GETLOCK_DVBC_PRELOCK,
    DMD_DTMB_GETLOCK_DVBC_MAINLOCK,
} DMD_DTMB_GETLOCK_TYPE;

typedef enum
{
    DMD_DTMB_LOCK,
    DMD_DTMB_CHECKING,
    DMD_DTMB_CHECKEND,
    DMD_DTMB_UNLOCK,
    DMD_DTMB_NULL,
} DMD_DTMB_LOCK_STATUS;

/// For demod init
typedef struct
{
    // init
    MS_U16 u16DTMBAGCLockCheckTime;//50
    MS_U16 u16DTMBPreLockCheckTime;//300
    MS_U16 u16DTMBPNMLockCheckTime;//1200
    MS_U16 u16DTMBFECLockCheckTime;//5000

    MS_U16 u16QAMAGCLockCheckTime;//50
    MS_U16 u16QAMPreLockCheckTime;//1000
    MS_U16 u16QAMMainLockCheckTime;//3000

    // register init
    MS_U8 *u8DMD_DTMB_DSPRegInitExt; // TODO use system variable type
    MS_U8 u8DMD_DTMB_DSPRegInitSize;
    MS_U8 *u8DMD_DTMB_InitExt; // TODO use system variable type

    //By Tuners:
    MS_U16  u16IF_KHZ;//By Tuners
    MS_BOOL bIQSwap;//0
    MS_U16  u16AGC_REFERENCE;//0
    MS_BOOL bTunerGainInvert;//0

    //By IC:
    MS_U8   u8IS_DUAL;//0
    MS_BOOL bIsExtDemod;//0

    //By TS (Only for MCP or ext demod):
    MS_U8 u1TsConfigByte_SerialMode : 1;
    MS_U8 u1TsConfigByte_DataSwap   : 1;
    MS_U8 u1TsConfigByte_ClockInv   : 1;
    MS_U8 u5TsConfigByte_DivNum     : 5;

    //By SYS I2C (Only for MCP or ext demod):
    MS_U8 u8I2CSlaveAddr;
    MS_U8 u8I2CSlaveBus;
    MS_BOOL (*I2C_WriteBytes)(MS_U16 u16BusNumSlaveID, MS_U8 u8addrcount, MS_U8* pu8addr, MS_U16 u16size, MS_U8* pu8data);
    MS_BOOL (*I2C_ReadBytes)(MS_U16 u16BusNumSlaveID, MS_U8 u8AddrNum, MS_U8* paddr, MS_U16 u16size, MS_U8* pu8data); 
    
    //By SYS MSPI (Only for MCP or ext demod):
    MS_BOOL bIsUseSspiLoadCode;
    MS_BOOL bIsSspiUseTsPin;
    
    //By SYS memory mapping (Only for int demod):
    MS_U32 u32TdiStartAddr;
    
    #if !DMD_DTMB_UTOPIA_EN && !DMD_DTMB_UTOPIA2_EN
    MS_U32  (*GetSystemTimeMS)(void);      // Get sys time (unit: ms)
    void    (*DelayMS)(MS_U32 ms);         // Delay time (unit: ms)
    MS_BOOL (*CreateMutex)(MS_BOOL enable); // Create&Delete mutex
    void    (*LockDMD)(MS_BOOL enable);    // Enter&Leave mutex
    #endif
} DMD_DTMB_InitData;

typedef struct
{
    MS_BOOL bInit;
    MS_BOOL bDownloaded;
    MS_BOOL bIsQPad;

    #if DMD_DTMB_STR_EN
    MS_BOOL             bIsDTV;
    EN_POWER_MODE       eLastState;
    #endif
    DMD_DTMB_DEMOD_TYPE eLastType;
    MS_U16              u16SymRate;
    
    MS_BOOL (*HAL_DMD_DTMB_IOCTL_CMD)(DMD_DTMB_HAL_COMMAND eCmd, void *pPara);
} DMD_DTMB_PriData;

typedef struct
{
    MS_U8  u8Version;
    MS_U32 u32DTMBScanTimeStart;
    MS_U32 u32DTMBFECLockTime;
    MS_U32 u32DTMBLockStatus;
} DMD_DTMB_Info;

typedef struct
{
    DMD_DTMB_InitData  sDMD_DTMB_InitData;
    DMD_DTMB_PriData   sDMD_DTMB_PriData;
    DMD_DTMB_Info      sDMD_DTMB_Info;
} DMD_DTMB_ResData;

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif

//-------------------------------------------------------------------------------------------------
/// Set detailed level of DTMB driver debug message
/// u8DbgLevel : debug level for Parallel Flash driver\n
/// AVD_DBGLV_NONE,    ///< disable all the debug message\n
/// AVD_DBGLV_INFO,    ///< information\n
/// AVD_DBGLV_NOTICE,  ///< normal but significant condition\n
/// AVD_DBGLV_WARNING, ///< warning conditions\n
/// AVD_DBGLV_ERR,     ///< error conditions\n
/// AVD_DBGLV_CRIT,    ///< critical conditions\n
/// AVD_DBGLV_ALERT,   ///< action must be taken immediately\n
/// AVD_DBGLV_EMERG,   ///< system is unusable\n
/// AVD_DBGLV_DEBUG,   ///< debug-level messages\n
/// @return TRUE : succeed
/// @return FALSE : failed to set the debug level
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_SetDbgLevel(DMD_DTMB_DbgLv u8DbgLevel);
//-------------------------------------------------------------------------------------------------
/// Get the information of DTMB driver\n
/// @return the pointer to the driver information
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC extern DMD_DTMB_Info* MDrv_DMD_DTMB_GetInfo(void);
//-------------------------------------------------------------------------------------------------
/// Get DTMB driver version
/// when get ok, return the pointer to the driver version
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_GetLibVer(const MSIF_Version **ppVersion);

////////////////////////////////////////////////////////////////////////////////
/// Should be called once when power on init
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_Initial_Hal_Interface(void);

////////////////////////////////////////////////////////////////////////////////
///                            SINGLE DEMOD API                              ///
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// Should be called every time when enter DTV input source
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_Init(DMD_DTMB_InitData *pDMD_DTMB_InitData, MS_U32 u32InitDataLen);
////////////////////////////////////////////////////////////////////////////////
/// Should be called every time when exit DTV input source
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_Exit(void);
////////////////////////////////////////////////////////////////////////////////
/// Set demod mode and enable demod (only for DTMB)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_SetConfig(DMD_DTMB_DEMOD_TYPE eType, MS_BOOL bEnable);
////////////////////////////////////////////////////////////////////////////////
/// DTMB reset (no use)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_SetReset(void);
////////////////////////////////////////////////////////////////////////////////
/// Set demod mode and enable demod (only for DVBC)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_Set_QAM_SR(DMD_DTMB_DEMOD_TYPE eType, MS_U16 symbol_rate);
////////////////////////////////////////////////////////////////////////////////
/// Active demod (not use)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_SetActive(MS_BOOL bEnable);
////////////////////////////////////////////////////////////////////////////////
/// Set demod power state for STR
////////////////////////////////////////////////////////////////////////////////
#if DMD_DTMB_STR_EN
DLL_PUBLIC extern MS_U32 MDrv_DMD_DTMB_SetPowerState(EN_POWER_MODE u16PowerState);
#endif
////////////////////////////////////////////////////////////////////////////////
/// Get demod lock status
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern DMD_DTMB_LOCK_STATUS MDrv_DMD_DTMB_GetLock(DMD_DTMB_GETLOCK_TYPE eType);
////////////////////////////////////////////////////////////////////////////////
/// Get demod modulation mode
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_GetModulationMode(DMD_DTMB_MODULATION_INFO *sDtmbModulationMode);
////////////////////////////////////////////////////////////////////////////////
/// Get demod signal strength (IF AGC gain)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_GetSignalStrength(MS_U16 *u16Strength);
////////////////////////////////////////////////////////////////////////////////
/// Get demod frequency offset
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_ReadFrequencyOffset(MS_S16 *cfo);
////////////////////////////////////////////////////////////////////////////////
/// Get demod SNR percentage (MAX SNR 30dB)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_U8 MDrv_DMD_DTMB_GetSignalQuality(void);
////////////////////////////////////////////////////////////////////////////////
/// Get demod pre LDPC BER
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_GetPreLdpcBer(float *pber);
////////////////////////////////////////////////////////////////////////////////
/// Get demod pre Viterbi BER (only for DVBC)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_GetPreViterbiBer(float *ber);
////////////////////////////////////////////////////////////////////////////////
/// Get demod post Viterbi BER (only for DVBC)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_GetPostViterbiBer(float *ber);
////////////////////////////////////////////////////////////////////////////////
/// Get demod SNR 
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_GetSNR(float *snr);
////////////////////////////////////////////////////////////////////////////////
/// Set TS output mode (only for external demod)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_SetSerialControl(MS_U8 u8TsConfigData);
////////////////////////////////////////////////////////////////////////////////
/// Enable I2C bypass mode (only for external demod)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_IIC_BYPASS_MODE(MS_BOOL bEnable);
////////////////////////////////////////////////////////////////////////////////
/// Switch pin to SSPI or GPIO (only for external demod)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_SWITCH_SSPI_GPIO(MS_BOOL bEnable);
////////////////////////////////////////////////////////////////////////////////
/// Get GPIO pin high or low (only for external demod)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_GPIO_GET_LEVEL(MS_U8 u8Pin, MS_BOOL *bLevel);
////////////////////////////////////////////////////////////////////////////////
/// Set GPIO pin high or low (only for external demod)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_GPIO_SET_LEVEL(MS_U8 u8Pin, MS_BOOL bLevel);
////////////////////////////////////////////////////////////////////////////////
/// Set GPIO pin output or input (only for external demod)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_GPIO_OUT_ENABLE(MS_U8 u8Pin, MS_BOOL bEnableOut);

////////////////////////////////////////////////////////////////////////////////
/// To get DTMB's register  value, only for special purpose.\n
/// u16Addr       : the address of DTMB's register\n
/// pu8Data       : the value to be gotten\n
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_GetReg(MS_U16 u16Addr, MS_U8 *pu8Data);
////////////////////////////////////////////////////////////////////////////////
/// To set DTMB's register value, only for special purpose.\n
/// u16Addr       : the address of DTMB's register\n
/// u8Value       : the value to be set\n
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_SetReg(MS_U16 u16Addr, MS_U8 u8Data);

////////////////////////////////////////////////////////////////////////////////
/// Swap ADC input (usually for external demod)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_DoIQSwap(MS_BOOL bIsQPad);

////////////////////////////////////////////////////////////////////////////////
///                            MULTI DEMOD API                               ///
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// Should be called every time when enter DTV input source
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_MD_Init(MS_U8 id, DMD_DTMB_InitData *pDMD_DTMB_InitData, MS_U32 u32InitDataLen);
////////////////////////////////////////////////////////////////////////////////
/// Should be called every time when exit DTV input source
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_MD_Exit(MS_U8 id);
////////////////////////////////////////////////////////////////////////////////
/// Set demod mode and enable demod (only for DTMB)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_MD_SetConfig(MS_U8 id, DMD_DTMB_DEMOD_TYPE eType, MS_BOOL bEnable);
////////////////////////////////////////////////////////////////////////////////
/// Set demod mode and enable demod (only for DVBC)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_MD_Set_QAM_SR(MS_U8 id, DMD_DTMB_DEMOD_TYPE eType, MS_U16 symbol_rate);
////////////////////////////////////////////////////////////////////////////////
/// Active demod (not use)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_MD_SetActive(MS_U8 id, MS_BOOL bEnable);
////////////////////////////////////////////////////////////////////////////////
/// Set demod power state for STR
////////////////////////////////////////////////////////////////////////////////
#if DMD_DTMB_STR_EN
DLL_PUBLIC extern MS_U32 MDrv_DMD_DTMB_MD_SetPowerState(MS_U8 id, EN_POWER_MODE u16PowerState);
#endif
////////////////////////////////////////////////////////////////////////////////
/// Get demod lock status
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern DMD_DTMB_LOCK_STATUS MDrv_DMD_DTMB_MD_GetLock(MS_U8 id, DMD_DTMB_GETLOCK_TYPE eType);
////////////////////////////////////////////////////////////////////////////////
/// Get demod modulation mode
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_MD_GetModulationMode(MS_U8 id, DMD_DTMB_MODULATION_INFO *sDtmbModulationMode);
////////////////////////////////////////////////////////////////////////////////
/// Get demod signal strength (IF AGC gain)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_MD_GetSignalStrength(MS_U8 id, MS_U16 *u16Strength);
////////////////////////////////////////////////////////////////////////////////
/// Get demod frequency offset
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_MD_ReadFrequencyOffset(MS_U8 id, MS_S16 *cfo);
////////////////////////////////////////////////////////////////////////////////
/// Get demod SNR percentage (MAX SNR 30dB)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_U8 MDrv_DMD_DTMB_MD_GetSignalQuality(MS_U8 id);
////////////////////////////////////////////////////////////////////////////////
/// Get demod pre LDPC BER
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_MD_GetPreLdpcBer(MS_U8 id, float *pber);
////////////////////////////////////////////////////////////////////////////////
/// Get demod pre Viterbi BER
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_MD_GetPreViterbiBer(MS_U8 id, float *ber);
////////////////////////////////////////////////////////////////////////////////
/// Get demod post Viterbi BER
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_MD_GetPostViterbiBer(MS_U8 id, float *ber);
////////////////////////////////////////////////////////////////////////////////
/// Get demod SNR
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_MD_GetSNR(MS_U8 id, float *snr);
////////////////////////////////////////////////////////////////////////////////
/// Set TS output mode (only for external demod)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_MD_SetSerialControl(MS_U8 id, MS_U8 u8TsConfigData);
////////////////////////////////////////////////////////////////////////////////
/// Enable I2C bypass mode (only for external demod)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_MD_IIC_BYPASS_MODE(MS_U8 id, MS_BOOL bEnable);
////////////////////////////////////////////////////////////////////////////////
/// Switch pin to SSPI or GPIO (only for external demod)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_MD_SWITCH_SSPI_GPIO(MS_U8 id, MS_BOOL bEnable);
////////////////////////////////////////////////////////////////////////////////
/// Get GPIO pin high or low (only for external demod)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_MD_GPIO_GET_LEVEL(MS_U8 id, MS_U8 u8Pin, MS_BOOL *bLevel);
////////////////////////////////////////////////////////////////////////////////
/// Set GPIO pin high or low (only for external demod)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_MD_GPIO_SET_LEVEL(MS_U8 id, MS_U8 u8Pin, MS_BOOL bLevel);
////////////////////////////////////////////////////////////////////////////////
/// Set GPIO pin output or input (only for external demod)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_MD_GPIO_OUT_ENABLE(MS_U8 id, MS_U8 u8Pin, MS_BOOL bEnableOut);

////////////////////////////////////////////////////////////////////////////////
/// To get DTMB's register  value, only for special purpose.\n
/// u16Addr       : the address of DTMB's register\n
/// pu8Data       : the value to be gotten\n
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_MD_GetReg(MS_U8 id, MS_U16 u16Addr, MS_U8 *pu8Data);
////////////////////////////////////////////////////////////////////////////////
/// To set DTMB's register value, only for special purpose.\n
/// u16Addr       : the address of DTMB's register\n
/// u8Value       : the value to be set\n
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_MD_SetReg(MS_U8 id, MS_U16 u16Addr, MS_U8 u8Data);

////////////////////////////////////////////////////////////////////////////////
/// Swap ADC input (usually for external demod)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_DTMB_MD_DoIQSwap(MS_U8 id, MS_BOOL bIsQPad);

#ifdef __cplusplus
}
#endif


#endif // _DRV_DTMB_H_

