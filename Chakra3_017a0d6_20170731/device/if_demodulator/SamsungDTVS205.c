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
#define _SAMSUNGDTVS205_C_

/* ------------------------------------
    Header Files
   ------------------------------------ */
#include <stdio.h>
#include <string.h>
#include "drvIIC.h"
#include "SamsungDTVS205.h"
#include "RF_Tuner_ATSC.h"
#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"

#ifndef DEMOD_IIC_BUS
#define DEMOD_IIC_BUS    E_I2C_BUS_SYS
#endif
#define SAMSUNG_S5H1409_I2C_ADDR            (((U16) DEMOD_IIC_BUS << 8) | 0xF2)

#define INIT_1409_TABLE_NUMS 43//42
#define QAM_CHECK_LOCK_TIME_SLICE   100
#define QAM_WAIT_LOCK_TOTAL_TIME   400
#define QAM_CHECK_LOCK_COUNTER  QAM_WAIT_LOCK_TOTAL_TIME/QAM_CHECK_LOCK_TIME_SLICE
#define QAM_WAIT_AGC_LOCK_TOTAL_TIME   300
#define QAM_CHECK_AGC_LOCK_TIME_SLICE       50
#define QAM_CHECK_AGC_LOCK_COUNTER          QAM_WAIT_AGC_LOCK_TOTAL_TIME/QAM_CHECK_AGC_LOCK_TIME_SLICE

SamsungChipInit_t code tDTVS5H1409_Tbl[INIT_1409_TABLE_NUMS] =
{
    {0xFA, 0x0000},
    {0x1C, 0x001D},
    {0x1F, 0x002D},
    {0x20, 0x001D},
    {0x22, 0x0022},
    {0x23, 0x0020},
    {0x28, 0x1010},
    {0x29, 0x110F},
    {0x2A, 0x10B4},
    {0x2B, 0x10AE},
    {0x2C, 0x0031},
    {0x31, 0x010D},
    {0x32, 0x0100},
    {0x44, 0x0510},
    {0x54, 0x0104},
    {0x5D, 0x0370},
    {0x5E, 0x0296},
    {0x58, 0x2222},
    {0x59, 0x1162},
    {0x5A, 0x3211},
    {0x61, 0x0010}, // bubbling channel tuning_Init 1.4
    {0x63, 0x4A00},
    {0x65, 0x0800},
    {0x71, 0x0003},
    {0x72, 0x0470},
    {0x96, 0x000C}, // QAM PTL on mode  for 1.2
    {0x99, 0x0101},
    {0x9C, 0x2E37}, // QAM PTL on mode  for 1.2
    {0x9D, 0x2C37}, // QAM PTL on mode  for 1.2
    {0x9E, 0x2E37}, // QAM PTL on mode  for 1.2

#if 0//(CUS2S_MODEL_NAME==CUS2S_MODEL_CMO26C)
    {0x81, 0x0002},
#else
    {0x81, 0x0003},
#endif

    {0x82, 0x0600},
    {0x86, 0x0002},
    {0x8A, 0x2C38},
    {0x8B, 0x2A37},
    {0x92, 0x302F},
    {0x93, 0x3332},
    {0xAC, 0x1003},
    {0xAD, 0x103F},
    {0xB1, 0x000E},
    {0xE2, 0x0100},
    {0xF5, 0x0000},
    {0xF5, 0x0001},
};
//*************************************************************************
//Function name:    SamsungS5H1409_Init
//Description:      This function SamsungS5H1409_Init
//  [doxygen]
/// This function SamsungS5H1409_Init
/// @param NULL \b IN: NULL
///
/// @return - return
///         - TRUE : Success
///         - FALSE: Fail
//*************************************************************************
BOOLEAN SamsungS5H1409_Init(void)
{
    U8 i;
    BOOLEAN Result;

    for(i = 0 ; i < INIT_1409_TABLE_NUMS ; i++)
    {
        Result = MDrv_IIC_Write2Bytes(SAMSUNG_S5H1409_I2C_ADDR, tDTVS5H1409_Tbl[i].Reg, tDTVS5H1409_Tbl[i].Value);
    }

    return Result;
}

//*************************************************************************
//Function name:    SamsungS5H1409AlterMpegMode
//Description:      This function Demode TS Output
//  [doxygen]
/// This function Demode TS Output
/// @param mode \b IN: MPEG_MODE_PARAL or MPEG_MODE_SERIAL
///
/// @return - return
///         - TRUE : Success
///         - FALSE: Fail
//*************************************************************************
SamsungReturn_t SamsungS5H1409AlterMpegMode(SamsungMpegMode_t mode)
{
    SamsungReturn_t Result = Samsung_ERR_INIT;
    if(mode != Samsung_PARAL && mode != Samsung_SERIAL)
        return (SamsungReturn_t)(Samsung_ERR_PARAM|Samsung_ERR_ALTER_FUNC);

    if(mode == Samsung_PARAL)
    {
        if (MDrv_IIC_Write2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0xAB, 0x1001) == TRUE)
            Result = Samsung_ERR_NO;
    }
    else
    {
        if (MDrv_IIC_Write2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0xAB, 0x1101) == TRUE)
            Result = Samsung_ERR_NO;
    }

    return Result;
}

//*************************************************************************
//Function name:    SamsungS5H1409_MpegClk_InvertedSet
//Description:      This function Inverting output clk.(Default)
//  [doxygen]
/// This function Inverting output clk.(Default),
/// After this function is called,TS timing could be changed.
/// @param NULL \b IN: NULL
///         - Addr : 0xac
///         - Value: 0x0330
/// @return - return
///         - TRUE : Success
///         - FALSE: Fail
//*************************************************************************

BOOLEAN SamsungS5H1409_MpegClk_InvertedSet(void)
{
    return MDrv_IIC_Write2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0xAC,0x0330);
}

//*************************************************************************
//Function name:    SamsungS5H1409_MpegClk_Non_InvertedSet
//Description:      This function Non-inverting output clk.(Default)
//  [doxygen]
/// This function Non-inverting output clk.(Default),
/// After this function is called,TS timing could be changed.
/// @param NULL \b IN: NULL
///         - Addr : 0xac
///         - Value: 0x1330
/// @return - return
///         - TRUE : Success
///         - FALSE: Fail
//*************************************************************************
BOOLEAN SamsungS5H1409_MpegClk_Non_InvertedSet(void)
{
    return MDrv_IIC_Write2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0xAC,0x1330);
}

//*************************************************************************
//Function name:    SamsungS5H1409xRepeaterEnable
//Description:      This function enable bypass Demode
//  [doxygen]
/// This function enable bypass Demode
/// @param NULL \b IN: NULL
///         - Addr : 0xF3
///         - Value: 0x0001
/// @return - return
///         - TRUE : Success
///         - FALSE: Fail
//*************************************************************************
BOOLEAN SamsungS5H1409xRepeaterEnable(void)
{
    return MDrv_IIC_Write2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0xF3, 0x0001);
}

//*************************************************************************
//Function name:    SamsungS5H1409xRepeaterDisable
//Description:      This function disbale bypass Demode
//  [doxygen]
/// This function disable bypass Demode
/// @param NULL \b IN: NULL
///         - Addr : 0xF3
///         - Value: 0x0000
/// @return - return
///         - TRUE : Success
///         - FALSE: Fail
//*************************************************************************
BOOLEAN SamsungS5H1409xRepeaterDisable(void)
{
    return MDrv_IIC_Write2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0xF3, 0x0000);
}

//*************************************************************************
//Function name:    SamsungS5H1409xSleepOn
//Description:      This function let Demode Sleep on
//  [doxygen]
/// This function let Demode Sleep on
/// @param NULL \b IN: NULL
///         - Addr : 0xF2
///         - Value: 0x0001
/// @return - return
///         - TRUE : Success
///         - FALSE: Fail
//*************************************************************************
BOOLEAN SamsungS5H1409xSleepOn(void)
{
    return MDrv_IIC_Write2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0xF2, 0x0001);
}

//*************************************************************************
//Function name:    SamsungS5H1409xSleepOff
//Description:      This function let Demode Sleep off
//  [doxygen]
/// This function let Demode Sleep off
/// @param NULL \b IN: NULL
///         - Addr : 0xF2
///         - Value: 0x0000
/// @return - return
///         - TRUE : Success
///         - FALSE: Fail
//*************************************************************************
BOOLEAN SamsungS5H1409xSleepOff(void)
{
    BOOLEAN result;
    result = MDrv_IIC_Write2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0xF2, 0x0000);
    if(result!=FALSE)
        result=SamsungS5H1409_SoftReset();
    return result;
}

//*************************************************************************
//Function name:    SamsungS5H1409xCheckIsSleep
//Description:      This function Check Demode Sleep status
//  [doxygen]
/// This function Check Demode Sleep status
/// @param NULL \b IN: NULL
///         - Addr : 0xF2
///         - Value: 0x0001
/// @return - return
///         - TRUE : sleep
///         - FALSE: no sleep
//*************************************************************************
BOOLEAN SamsungS5H1409xCheckIsSleep(void)
{
    if(MDrv_IIC_Read2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0x00F2)==0x0001)
        return TRUE;
    else
        return FALSE;
}

//*************************************************************************
//Function name:    SamsungS5H1409_SoftReset
//Description:      This function let Demode Reset by Softwave
//  [doxygen]
/// This function let Demode Reset by Softwave
/// @param NULL \b IN: NULL
///         - Addr : 0xF5
///         - Value:
/// @return - return
///         - TRUE : succes
///         - FALSE: fail
//*************************************************************************
BOOLEAN SamsungS5H1409_SoftReset(void)
{
    BOOLEAN result;
    result=MDrv_IIC_Write2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0xF5, 0x0000);
    MsOS_DelayTask(5);
    result=MDrv_IIC_Write2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0xF5, 0x0001);
    return result;
}

#if 0
BOOLEAN SamsungS5H1409_SoftResetOn(void)
{
    return MDrv_IIC_Write2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0xF5, 0x0000);
}

BOOLEAN SamsungS5H1409_SoftResetOff(void)
{
    return MDrv_IIC_Write2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0xF5, 0x0001);
}
#endif
//*************************************************************************
//Function name:    SamsungS5H1409VsbMode
//Description:      This function Let demoe into VSB mode
//  [doxygen]
///  This function Let demoe into VSB mode
/// @param NULL \b IN: NULL
///         - Addr : 0xF4
///         - Value: 0x0000
/// @return - return
///         - TRUE : succes
///         - FALSE: fail
//*************************************************************************
BOOLEAN SamsungS5H1409VsbMode(void)
{
    BOOLEAN result;
    result = MDrv_IIC_Write2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0xF4, 0x0000);
    return result;
}

//*************************************************************************
//Function name:    SamsungS5H1409x64QamMode
//Description:      This function Let demoe into 64QAM mode
//  [doxygen]
///  This function Let demoe into 64QAM mode
/// @param NULL \b IN: NULL
///         - Addr :
///         - Value:
/// @return - return
///         - TRUE : succes
///         - FALSE: fail
//*************************************************************************
BOOLEAN SamsungS5H1409x64QamMode(void)
{
    BOOLEAN result;
    result = MDrv_IIC_Write2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0xF4,0x0001);
    result = MDrv_IIC_Write2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0x85,0x0100);
    return result;
}

//*************************************************************************
//Function name:    SamsungS5H1409x256QamMode
//Description:      This function Let demoe into 256QAM mode
//  [doxygen]
///  This function Let demoe into 256QAM mode
/// @param NULL \b IN: NULL
///         - Addr :
///         - Value:
/// @return - return
///         - TRUE : succes
///         - FALSE: fail
//*************************************************************************
BOOLEAN SamsungS5H1409x256QamMode(void)
{
    BOOLEAN result;
    result = MDrv_IIC_Write2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0xF4,0x0001);
    result = MDrv_IIC_Write2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0x85,0x0101);
    return result;
}

//*************************************************************************
//Function name:    SamsungS5H1409_Interleave_Parallel_ModeSet
//Description:      This function In the TOV state at low SNR, this driver can improve the performance.
//  [doxygen]
///  This function In the TOV state at low SNR, this driver can improve the performance.
///  There are two interleave mode set drivers depending on the TS type. Only in qam mode
/// @param NULL \b IN: NULL
///         - Addr : 0xab
///         - Value: 0x1000 -> manually write the interleaver mode.
/// @return - return
///         - TRUE : succes
///         - FALSE: fail
//*************************************************************************
void SamsungS5H1409_Interleave_Parallel_ModeSet()
{
    static U16 temp,temp1,temp2=0;
    static U16 qam_up = 0;

    temp = MDrv_IIC_Read2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0x00F1);
    temp1= MDrv_IIC_Read2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0x00B2);
    temp2= MDrv_IIC_Read2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0x00AD);

    if((temp>>15)&0x1) //  if (master lock)
    {
        if(qam_up!=2)
        {
            qam_up = 2;
            MDrv_IIC_Write2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0x96,0x0020);
            MDrv_IIC_Write2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0xAD,(((temp1&0xF000)>>4)|( temp2&0xF0FF )) );
            MDrv_IIC_Write2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0xAB,0x1000);
        }
    }
    else           //  if (unlock)
    {
        if(qam_up!=1)
        {
            qam_up = 1;
            MDrv_IIC_Write2Bytes (SAMSUNG_S5H1409_I2C_ADDR, 0x96, 0x0008);
            MDrv_IIC_Write2Bytes (SAMSUNG_S5H1409_I2C_ADDR, 0xAB, 0x1001);
        }
    }
}

//*************************************************************************
//Function name:    SamsungS5H1409_Interleave_Serial_ModeSet
//Description:
//  [doxygen]
/// @param NULL \b IN: NULL
///         - Addr :
///         - Value:
/// @return - return
///         - TRUE : succes
///         - FALSE: fail
//*************************************************************************
void SamsungS5H1409_Interleave_Serial_ModeSet()
{
    static U16 temp,temp1,temp2=0;
    static U16 qam_up = 0;

    temp = MDrv_IIC_Read2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0x00F1);
    temp1= MDrv_IIC_Read2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0x00B2);
    temp2= MDrv_IIC_Read2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0x00AD);

    if((temp>>15)&0x1) //  if (master lock)
    {
        if(qam_up!=2)
        {
            qam_up = 2;
            MDrv_IIC_Write2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0x96,0x0020);
            MDrv_IIC_Write2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0xAD,(((temp1&0xF000)>>4)|( temp2&0xF0FF )) );
            MDrv_IIC_Write2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0xAB,0x1100);
        }
    }
    else           //  if (unlock)
    {
        if(qam_up!=1)
        {
            qam_up = 1;
            MDrv_IIC_Write2Bytes (SAMSUNG_S5H1409_I2C_ADDR, 0x96, 0x0008);
            MDrv_IIC_Write2Bytes (SAMSUNG_S5H1409_I2C_ADDR, 0xAB, 0x1101);
        }
    }
}

//*************************************************************************
//Function name:    SamsungS5H1409AMHUM_SetDriver
//Description:
//  [doxygen]
/// @param NULL \b IN: NULL
///         - Addr :
///         - Value:
/// @return - return
///         - TRUE : succes
///         - FALSE: fail
//*************************************************************************

/*******************************************************************************************************************************
* S5H1409 QAM AM HUM set driver
* Conditions: Only in QAM mode
* Description: This function set the equalizer step size automatically while monitoring the equalizer output values.
* The AM_HUM performance gets better through this function. This function should be always set and work in
* 64/256QAM mode.
* Addr: 0x93, 0x9e
* Value: 0x93: 0x3332 (in normal condition), 0x3130(in the TOV state)
*        0x9e: 0x2c37 (in normal condition), 0x2836(in the TOV state)
*******************************************************************************************************************************/
void SamsungS5H1409AMHUM_SetDriver()
{
    U16 temp;

    temp = MDrv_IIC_Read2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0x00F0);
    if((temp>>13)&0x1) //EQ lock
    {
        MDrv_IIC_Write2Bytes (SAMSUNG_S5H1409_I2C_ADDR, 0x96, 0x000C);
        if((temp&0xff)<0x38 || ((temp&0xff)>0x68))
        {
            MDrv_IIC_Write2Bytes (SAMSUNG_S5H1409_I2C_ADDR, 0x93, 0x3332);
        }
        else if( ((temp&0xff)>0x40) && ((temp&0xff)<0x68) )
        {
            MDrv_IIC_Write2Bytes (SAMSUNG_S5H1409_I2C_ADDR, 0x93, 0x3130);
        }

        if((temp&0xff)<0x38 || ((temp&0xff)>0x68))
        {
            MDrv_IIC_Write2Bytes (SAMSUNG_S5H1409_I2C_ADDR, 0x9E, 0x2E37);
        }
        else if( ((temp&0xff)>0x40) && ((temp&0xff)<0x68) )
        {
            MDrv_IIC_Write2Bytes (SAMSUNG_S5H1409_I2C_ADDR, 0x9E, 0x2836);
        }
    }
    else//EQ unlock
    {
        MDrv_IIC_Write2Bytes (SAMSUNG_S5H1409_I2C_ADDR, 0x96, 0x0008);
        MDrv_IIC_Write2Bytes (SAMSUNG_S5H1409_I2C_ADDR, 0x93, 0x3332);
        MDrv_IIC_Write2Bytes (SAMSUNG_S5H1409_I2C_ADDR, 0x9E, 0x2E37);
    }
}

BOOLEAN SamsungS5H1409xVSBScanInit(void)
{
    BOOLEAN result;
    result = MDrv_IIC_Write2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0x3B,0x1000);
    result = MDrv_IIC_Write2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0x44,0x0500);
    return result;
}

BOOLEAN SamsungS5H1409xVSBScanEnd(void)
{
    BOOLEAN result;
    result = MDrv_IIC_Write2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0x3B,0x1010);
    result = MDrv_IIC_Write2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0x44,0x0510);
    return result;
}

/**************************************************************************
* S5H1409 VSB/QAM Master Lock Check Driver
*    Conditions:
*    Description :
*    This function is used to check whether the channel chip is lock
*    or not in VSB mode.
*    Addr : 0x40
*    Value:
*    0bit -> 1:Lock , 0:Unlock
***************************************************************************/
BOOLEAN SamsungS5H1409xVsb_Sync_Lock(void)
{
    U16 value;
    BOOLEAN result;

    value = MDrv_IIC_Read2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0x40);
    result = (BOOLEAN)(((U16)value) & 0x01);   // 1 -->Sync lock

    return (result);
}

BOOLEAN SamsungS5H1409xQAM_IsAGC_Lock(void)
{
    U16 value = 0;
    value = MDrv_IIC_Read2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0xA0);

    #if 1
    return TRUE;
    #else
    //if((value>0xF870)&&(value<0xFB00))
    if(value>0xF870)
    {
        return FALSE;       //AGC Unlock
    }
    else
    {
        return TRUE;
    }
    #endif
}

/**************************************************************************
* S5H1409 VSB/QAM Master Lock Check Driver
*    Conditions:
*    Description :
*    This function is used to check whether the channel chip is lock
*    or not in VSB mode.
*    Addr : 0xf1
*    Value:
*    15bit -> 1:Lock , 0:Unlock
***************************************************************************/
BOOLEAN SamsungS5H1409xVsb_QAM_Master_Lock(void)
{
    U16 value;
    BOOLEAN result;

    value = MDrv_IIC_Read2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0xF1);
    result = (BOOLEAN)(((U16)value >> 15) & 0x01);   // 1 -->Master lock
    return (result);
}

/**************************************************************************
* S5H1409 VSB FEC Lock Check Driver
*    Conditions:
*    Description :
*    This function is used to check whether the channel
*    chip is lock or not in VSB mode.
*    Addr : 0xf1
*    Value:
*    12bit -> 0:Lock , 1:Unlock
***************************************************************************/
BOOLEAN SamsungS5H1409xVsb_FEC_Lock(void)
{
    U16 value;
    BOOLEAN result;

    value = MDrv_IIC_Read2Bytes(SAMSUNG_S5H1409_I2C_ADDR, 0xF1);
    result = (BOOLEAN)(((U16)value >> 12) & 0x01);           // 1 --> FEC LOCK

    return (result);
}

void SamsungS5H1409xCheckSignalCondition(SamsungSignalCondition_t* pstatus)
{
    U16 value,value1,value2;
    double SnrValue = 0;


    value = MDrv_IIC_Read2Bytes( SAMSUNG_S5H1409_I2C_ADDR, 0xf4 ); //mode check
    if(value==0)//VSB mode
    {
        SnrValue=SamsungS5H1409xVsbSnrResultCheck();
        if(!SamsungS5H1409xVsb_FEC_Lock())
            SnrValue=0;
        if(SnrValue==0)
            *pstatus=Samsung_SIGNAL_NO;
        else if(SnrValue<18.4)
            *pstatus=Samsung_SIGNAL_WEAK;
        else if(SnrValue<21.8)
            *pstatus=Samsung_SIGNAL_MODERATE;
        else if(SnrValue<26.9)
            *pstatus=Samsung_SIGNAL_STRONG;
        else
            *pstatus=Samsung_SIGNAL_VERY_STRONG;
    }
    else//qam MODE
    {
        if(SamsungS5H1409xVsb_QAM_Master_Lock()==0)
        {
            *pstatus=Samsung_SIGNAL_NO;
            return;
        }
        SnrValue=SamsungS5H1409xQamSnrResultCheck();
        value1 = MDrv_IIC_Read2Bytes( SAMSUNG_S5H1409_I2C_ADDR, 0x85 );
        value2 = MDrv_IIC_Read2Bytes( SAMSUNG_S5H1409_I2C_ADDR, 0xf0 );
        value2 = ( ( unsigned int ) value2 >> 8 & 0x01 );

        if (( value1 == 0x110 && value2 == 1)||( value1 == 0x101 ))
        {
            if(SnrValue==0)
                *pstatus=Samsung_SIGNAL_NO;
            else if(SnrValue<31.2)
                *pstatus=Samsung_SIGNAL_WEAK;
            else if(SnrValue<32.4)
                *pstatus=Samsung_SIGNAL_MODERATE;
            else if(SnrValue<34.2)
                *pstatus=Samsung_SIGNAL_STRONG;
            else
                *pstatus=Samsung_SIGNAL_VERY_STRONG;
        }
        else if ( (value1 == 0x110 && value2 == 0 )||( value1 == 0x100 ))
        {
            if(SnrValue==0)
                *pstatus=Samsung_SIGNAL_NO;
            else if(SnrValue<25.4)
                *pstatus=Samsung_SIGNAL_WEAK;
            else if(SnrValue<27.8)
                *pstatus=Samsung_SIGNAL_MODERATE;
            else if(SnrValue<31.4)
                *pstatus=Samsung_SIGNAL_STRONG;
            else
                *pstatus=Samsung_SIGNAL_VERY_STRONG;
        }
        else
        {
            *pstatus=Samsung_SIGNAL_NO;
        }
    }
}

/**************************************************************************
* S5H1409 VSB SNR value(Signal Strength) Check Driver
*    Conditions:
*    Description :
*    This function lets the user's application software read a value
*    that is related to the SNR through the SNR Look Up Table in VSB mode.
*    Addr : 0xf1
*    Value: [9:0]
**************************************************************************/

double SnrLookUpTable ( int SnrRead )
{
    double SnrLookUP;
    if ( SnrRead == 1023 )
    {
        SnrLookUP = 77 ;
    }  // Something Wrong
    else if ( SnrRead > 923 )
    {
        SnrLookUP = 30 ;
    }
    else if ( SnrRead > 918 )
    {
        SnrLookUP = 29.5 ;
    }
    else if ( SnrRead > 915 )
    {
        SnrLookUP = 28.5 ;
    }
    else if ( SnrRead > 911 )
    {
        SnrLookUP = 28.5 ;
    }
    else if ( SnrRead > 906 )
    {
        SnrLookUP = 28.0 ;
    }
    else if ( SnrRead > 901 )
    {
        SnrLookUP = 27.5 ;
    }
    else if ( SnrRead > 896 )
    {
        SnrLookUP = 27.0 ;
    }
    else if ( SnrRead > 891 )
    {
        SnrLookUP = 26.5 ;
    }
    else if ( SnrRead > 885 )
    {
        SnrLookUP = 26.0 ;
    }
    else if ( SnrRead > 879 )
    {
        SnrLookUP = 25.5 ;
    }
    else if ( SnrRead > 873 )
    {
        SnrLookUP = 25.0 ;
    }
    else if ( SnrRead > 864 )
    {
        SnrLookUP = 24.5 ;
    }
    else if ( SnrRead > 858 )
    {
        SnrLookUP = 24.0 ;
    }
    else if ( SnrRead > 850 )
    {
        SnrLookUP = 23.5 ;
    }
    else if ( SnrRead > 841 )
    {
        SnrLookUP = 23.0 ;
    }
    else if ( SnrRead > 832 )
    {
        SnrLookUP = 22.5 ;
    }
    else if ( SnrRead > 823 )
    {
        SnrLookUP = 22.0 ;
    }
    else if ( SnrRead > 812 )
    {
        SnrLookUP = 21.5 ;
    }
    else if ( SnrRead > 802 )
    {
        SnrLookUP = 21.0 ;
    }
    else if ( SnrRead > 788 )
    {
        SnrLookUP = 20.5 ;
    }
    else if ( SnrRead > 778 )
    {
        SnrLookUP = 20.0 ;
    }
    else if ( SnrRead > 767 )
    {
        SnrLookUP = 19.5 ;
    }
    else if ( SnrRead > 753 )
    {
        SnrLookUP = 19.0 ;
    }
    else if ( SnrRead > 740 )
    {
        SnrLookUP = 18.5 ;
    }
    else if ( SnrRead > 725 )
    {
        SnrLookUP = 18.0 ;
    }
    else if ( SnrRead > 707 )
    {
        SnrLookUP = 17.5 ;
    }
    else if ( SnrRead > 689 )
    {
        SnrLookUP = 17.0 ;
    }
    else if ( SnrRead > 671 )
    {
        SnrLookUP = 16.5 ;
    }
    else if ( SnrRead > 656 )
    {
        SnrLookUP = 16.0 ;
    }
    else if ( SnrRead > 637 )
    {
        SnrLookUP = 15.5 ;
    }
    else if ( SnrRead > 616 )
    {
        SnrLookUP = 15.0 ;
    }
    else if ( SnrRead > 542 )
    {
        SnrLookUP = 14.5 ;
    }
    else if ( SnrRead > 519 )
    {
        SnrLookUP = 14.0 ;
    }
    else if ( SnrRead > 507 )
    {
        SnrLookUP = 13.5 ;
    }
    else if ( SnrRead > 497 )
    {
        SnrLookUP = 13.0 ;
    }
    else if ( SnrRead > 492 )
    {
        SnrLookUP = 12.5 ;
    }
    else if ( SnrRead > 474 )
    {
        SnrLookUP = 12.0 ;
    }
    else if ( SnrRead > 300 )
    {
        SnrLookUP = 1.11 ;
    }
    else
    {
        SnrLookUP = 0;
    }
    return SnrLookUP;
}


double SamsungS5H1409xVsbSnrResultCheck ( void )
{
    U16 value;
    double SnrValue;
    value = MDrv_IIC_Read2Bytes( SAMSUNG_S5H1409_I2C_ADDR, 0xf1 );
    value = ( value & 0x3ff );
    SnrValue = SnrLookUpTable( value );
    return SnrValue;
}

/**************************************************************************
* S5H1409 QAM SNR value(Signal Strength) Check Driver
*    Conditions:
*    Description:
*    This function lets the user's application software read a value
*    that is related to the SNR through the SNR Look Up Table in QAM mode.
*    Addr : 0xf0
*    Value: [13:0]
**************************************************************************/

double Qam64SnrLookUpTable ( int SnrRead )
{
    double SnrLookUP;
    if ( SnrRead < 12 )
    {
        SnrLookUP = 30    ;
    }
    else if ( SnrRead < 15 )
    {
        SnrLookUP = 29    ;
    }
    else if ( SnrRead < 18 )
    {
        SnrLookUP = 28    ;
    }
    else if ( SnrRead < 22 )
    {
        SnrLookUP = 27    ;
    }
    else if ( SnrRead < 23 )
    {
        SnrLookUP = 26.8    ;
    }
    else if ( SnrRead < 24 )
    {
        SnrLookUP = 26.6    ;
    }
    else if ( SnrRead < 25 )
    {
        SnrLookUP = 26.4    ;
    }
    else if ( SnrRead < 27 )
    {
        SnrLookUP = 26.2    ;
    }
    else if ( SnrRead < 28 )
    {
        SnrLookUP = 26        ;
    }
    else if ( SnrRead < 29 )
    {
        SnrLookUP = 25.8    ;
    }
    else if ( SnrRead < 30 )
    {
        SnrLookUP = 25.6    ;
    }
    else if ( SnrRead < 32 )
    {
        SnrLookUP = 25.4    ;
    }
    else if ( SnrRead < 33 )
    {
        SnrLookUP = 25.2    ;
    }
    else if ( SnrRead < 34 )
    {
        SnrLookUP = 25        ;
    }
    else if ( SnrRead < 35 )
    {
        SnrLookUP = 24.9    ;
    }
    else if ( SnrRead < 36 )
    {
        SnrLookUP = 24.8    ;
    }
    else if ( SnrRead < 37 )
    {
        SnrLookUP = 24.7    ;
    }
    else if ( SnrRead < 38 )
    {
        SnrLookUP = 24.6    ;
    }
    else if ( SnrRead < 39 )
    {
        SnrLookUP = 24.5    ;
    }
    else if ( SnrRead < 40 )
    {
        SnrLookUP = 24.4    ;
    }
    else if ( SnrRead < 41 )
    {
        SnrLookUP = 24.3    ;
    }
    else if ( SnrRead < 42 )
    {
        SnrLookUP = 24.1    ;
    }
    else if ( SnrRead < 43 )
    {
        SnrLookUP = 24        ;
    }
    else if ( SnrRead < 44 )
    {
        SnrLookUP = 23.9    ;
    }
    else if ( SnrRead < 45 )
    {
        SnrLookUP = 23.8    ;
    }
    else if ( SnrRead < 46 )
    {
        SnrLookUP = 23.7    ;
    }
    else if ( SnrRead < 47 )
    {
        SnrLookUP = 23.6    ;
    }
    else if ( SnrRead < 48 )
    {
        SnrLookUP = 23.5    ;
    }
    else if ( SnrRead < 49 )
    {
        SnrLookUP = 23.4    ;
    }
    else if ( SnrRead < 50 )
    {
        SnrLookUP = 23.3    ;
    }
    else if ( SnrRead < 51 )
    {
        SnrLookUP = 23.2    ;
    }
    else if ( SnrRead < 52 )
    {
        SnrLookUP = 23.1    ;
    }
    else if ( SnrRead < 53 )
    {
        SnrLookUP = 23        ;
    }
    else if ( SnrRead < 55 )
    {
        SnrLookUP = 22.9    ;
    }
    else if ( SnrRead < 56 )
    {
        SnrLookUP = 22.8    ;
    }
    else if ( SnrRead < 57 )
    {
        SnrLookUP = 22.7    ;
    }
    else if ( SnrRead < 58 )
    {
        SnrLookUP = 22.6    ;
    }
    else if ( SnrRead < 59 )
    {
        SnrLookUP = 22.5    ;
    }
    else if ( SnrRead < 60 )
    {
        SnrLookUP = 22.4    ;
    }
    else if ( SnrRead < 62 )
    {
        SnrLookUP = 22.3    ;
    }
    else if ( SnrRead < 63 )
    {
        SnrLookUP = 22.2    ;
    }
    else if ( SnrRead < 65 )
    {
        SnrLookUP = 22.1    ;
    }
    else if ( SnrRead < 66 )
    {
        SnrLookUP = 22        ;
    }
    else if ( SnrRead < 68 )
    {
        SnrLookUP = 21.9    ;
    }
    else if ( SnrRead < 69 )
    {
        SnrLookUP = 21.8    ;
    }
    else if ( SnrRead < 70 )
    {
        SnrLookUP = 21.7    ;
    }
    else if ( SnrRead < 72 )
    {
        SnrLookUP = 21.6    ;
    }
    else if ( SnrRead < 73 )
    {
        SnrLookUP = 21.5    ;
    }
    else if ( SnrRead < 75 )
    {
        SnrLookUP = 21.4    ;
    }
    else if ( SnrRead < 76 )
    {
        SnrLookUP = 21.3    ;
    }
    else if ( SnrRead < 78 )
    {
        SnrLookUP = 21.2    ;
    }
    else if ( SnrRead < 80 )
    {
        SnrLookUP = 21.1    ;
    }
    else if ( SnrRead < 81 )
    {
        SnrLookUP = 21        ;
    }
    else if ( SnrRead < 83 )
    {
        SnrLookUP = 20.9    ;
    }
    else if ( SnrRead < 84 )
    {
        SnrLookUP = 20.8    ;
    }
    else if ( SnrRead < 85 )
    {
        SnrLookUP = 20.7    ;
    }
    else if ( SnrRead < 87 )
    {
        SnrLookUP = 20.6    ;
    }
    else if ( SnrRead < 89 )
    {
        SnrLookUP = 20.5    ;
    }
    else if ( SnrRead < 91 )
    {
        SnrLookUP = 20.4    ;
    }
    else if ( SnrRead < 93 )
    {
        SnrLookUP = 20.3    ;
    }
    else if ( SnrRead < 95 )
    {
        SnrLookUP = 20.2    ;
    }
    else if ( SnrRead < 96 )
    {
        SnrLookUP = 20.1    ;
    }
    else if ( SnrRead < 104 )
    {
        SnrLookUP = 20        ;
    }
    else
    {
        SnrLookUP = 0;
    }
    return SnrLookUP;
}

double Qam256SnrLookUpTable ( int SnrRead )
{
    double SnrLookUP;
    if ( SnrRead < 12 )
    {
        SnrLookUP = 40    ;
    }
    else if ( SnrRead < 13 )
    {
        SnrLookUP = 39        ;
    }
    else if ( SnrRead < 15 )
    {
        SnrLookUP = 38        ;
    }
    else if ( SnrRead < 17 )
    {
        SnrLookUP = 37        ;
    }
    else if ( SnrRead < 19 )
    {
        SnrLookUP = 36        ;
    }
    else if ( SnrRead < 22 )
    {
        SnrLookUP = 35        ;
    }
    else if ( SnrRead < 23 )
    {
        SnrLookUP = 34.6    ;
    }
    else if ( SnrRead < 24 )
    {
        SnrLookUP = 34.4    ;
    }
    else if ( SnrRead < 25 )
    {
        SnrLookUP = 34.2    ;
    }
    else if ( SnrRead < 26 )
    {
        SnrLookUP = 34        ;
    }
    else if ( SnrRead < 27 )
    {
        SnrLookUP = 33.8    ;
    }
    //else if ( SnrRead < 27 )
    //{
    //    SnrLookUP = 33.6    ;
    //}
    else if ( SnrRead < 28 )
    {
        SnrLookUP = 33.4    ;
    }
    else if ( SnrRead < 29 )
    {
        SnrLookUP = 33.2    ;
    }
    else if ( SnrRead < 30 )
    {
        SnrLookUP = 33        ;
    }
    else if ( SnrRead < 31 )
    {
        SnrLookUP = 32.8    ;
    }
    else if ( SnrRead < 32 )
    {
        SnrLookUP = 32.6    ;
    }
    else if ( SnrRead < 33 )
    {
        SnrLookUP = 32.4    ;
    }
    else if ( SnrRead < 34 )
    {
        SnrLookUP = 32.2    ;
    }
    else if ( SnrRead < 35 )
    {
        SnrLookUP = 32        ;
    }
    else if ( SnrRead < 37 )
    {
        SnrLookUP = 31.8    ;
    }
    else if ( SnrRead < 39 )
    {
        SnrLookUP = 31.6    ;
    }
    else if ( SnrRead < 40 )
    {
        SnrLookUP = 31.4    ;
    }
    else if ( SnrRead < 41 )
    {
        SnrLookUP = 31.2    ;
    }
    else if ( SnrRead < 42 )
    {
        SnrLookUP = 31        ;
    }
    else if ( SnrRead < 43 )
    {
        SnrLookUP = 30.8    ;
    }
    else if ( SnrRead < 46 )
    {
        SnrLookUP = 30.6    ;
    }
    else if ( SnrRead < 47 )
    {
        SnrLookUP = 30.4    ;
    }
    else if ( SnrRead < 49 )
    {
        SnrLookUP = 30.2    ;
    }
    else if ( SnrRead < 51 )
    {
        SnrLookUP = 30        ;
    }
    else if ( SnrRead < 53 )
    {
        SnrLookUP = 29.8    ;
    }
    else if ( SnrRead < 54 )
    {
        SnrLookUP = 29.7    ;
    }
    else if ( SnrRead < 55 )
    {
        SnrLookUP = 29.6    ;
    }
    else if ( SnrRead < 56 )
    {
        SnrLookUP = 29.5    ;
    }
    else if ( SnrRead < 57 )
    {
        SnrLookUP = 29.4    ;
    }
    else if ( SnrRead < 59 )
    {
        SnrLookUP = 29.3    ;
    }
    else if ( SnrRead < 60 )
    {
        SnrLookUP = 29.2    ;
    }
    else if ( SnrRead < 61 )
    {
        SnrLookUP = 29.1    ;
    }
    else if ( SnrRead < 63 )
    {
        SnrLookUP = 29        ;
    }
    else if ( SnrRead < 64 )
    {
        SnrLookUP = 28.9    ;
    }
    else if ( SnrRead < 65 )
    {
        SnrLookUP = 28.8    ;
    }
    else if ( SnrRead < 66 )
    {
        SnrLookUP = 28.7    ;
    }
    else if ( SnrRead < 68 )
    {
        SnrLookUP = 28.6    ;
    }
    else if ( SnrRead < 69 )
    {
        SnrLookUP = 28.5    ;
    }
    else if ( SnrRead < 71 )
    {
        SnrLookUP = 28.4    ;
    }
    else if ( SnrRead < 72 )
    {
        SnrLookUP = 28.3    ;
    }
    else if ( SnrRead < 74 )
    {
        SnrLookUP = 28.2    ;
    }
    else if ( SnrRead < 75 )
    {
        SnrLookUP = 28.1    ;
    }
    else if ( SnrRead < 76 )
    {
        SnrLookUP = 28        ;
    }
    else if ( SnrRead < 77 )
    {
        SnrLookUP = 27.9    ;
    }
    else if ( SnrRead < 78 )
    {
        SnrLookUP = 27.8    ;
    }
    else if ( SnrRead < 81 )
    {
        SnrLookUP = 27.7    ;
    }
    else if ( SnrRead < 83 )
    {
        SnrLookUP = 27.6    ;
    }
    else if ( SnrRead < 84 )
    {
        SnrLookUP = 27.5    ;
    }
    else if ( SnrRead < 86 )
    {
        SnrLookUP = 27.4    ;
    }
    else if ( SnrRead < 87 )
    {
        SnrLookUP = 27.3    ;
    }
    else if ( SnrRead < 89 )
    {
        SnrLookUP = 27.2    ;
    }
    else if ( SnrRead < 90 )
    {
        SnrLookUP = 27.1    ;
    }
    else if ( SnrRead < 92 )
    {
        SnrLookUP = 27        ;
    }
    else if ( SnrRead < 93 )
    {
        SnrLookUP = 26.9    ;
    }
    else if ( SnrRead < 95 )
    {
        SnrLookUP = 26.8    ;
    }
    else if ( SnrRead < 96 )
    {
        SnrLookUP = 26.7    ;
    }
    else if ( SnrRead < 98 )
    {
        SnrLookUP = 26.6    ;
    }
    else if ( SnrRead < 100 )
    {
        SnrLookUP = 26.5    ;
    }
    else if ( SnrRead < 102 )
    {
        SnrLookUP = 26.4    ;
    }
    else if ( SnrRead < 104 )
    {
        SnrLookUP = 26.3    ;
    }
    else if ( SnrRead < 105 )
    {
        SnrLookUP = 26.2    ;
    }
    else if ( SnrRead < 106 )
    {
        SnrLookUP = 26.1    ;
    }
    else if ( SnrRead < 110 )
    {
        SnrLookUP = 26        ;
    }
    else
    {
        SnrLookUP = 0;
    }
    return SnrLookUP;
}

double SamsungS5H1409xQamSnrResultCheck ( void )
{
    U16 lvalue;
    U16 value;
    U16 value1;
    U16 value2;
    U16 result;
    double SnrValue = 0;

    value1 = MDrv_IIC_Read2Bytes( SAMSUNG_S5H1409_I2C_ADDR, 0x85 );
    value2 = MDrv_IIC_Read2Bytes( SAMSUNG_S5H1409_I2C_ADDR, 0xf0 );
    result = ( ( unsigned int ) value2 >> 8 & 0x01 );

    value = MDrv_IIC_Read2Bytes( SAMSUNG_S5H1409_I2C_ADDR, 0xf0 );
    lvalue = ( value & 0xff );

    if ( value1 == 0x110 && result == 1 )
    {
        SnrValue = Qam256SnrLookUpTable( lvalue );
    }
    else if ( value1 == 0x110 && result == 0 )
    {
        SnrValue = Qam64SnrLookUpTable( lvalue );
    }
    else if ( value1 == 0x100 )
    {
        SnrValue = Qam64SnrLookUpTable( lvalue );
    }
    else if ( value1 == 0x101 )
    {
        SnrValue = Qam256SnrLookUpTable( lvalue );
    }

    return ( SnrValue );
}

BOOLEAN SamsungS5H1409xQAMCheckLock(void)
{
    U8 Counter=0;
    while(1)
    {
        if(SamsungS5H1409xVsb_QAM_Master_Lock())
        {
            SamsungS5H1409AMHUM_SetDriver();
            #if TS_PARALLEL_OUTPUT
            SamsungS5H1409_Interleave_Parallel_ModeSet();
            #else
            SamsungS5H1409_Interleave_Serial_ModeSet();
            #endif
             return TRUE;
        }
        else if(Counter==QAM_CHECK_LOCK_COUNTER)
            return FALSE;

        if (!msAPI_Tuner_Wait(QAM_CHECK_LOCK_TIME_SLICE))
            return FALSE;

        Counter++;
    }
}

BOOLEAN SamsungS5H1409xAGCCheckLock(void)
{
    U8 Counter=0;
    while(1)
    {
        if(SamsungS5H1409xQAM_IsAGC_Lock())
            return TRUE;
        else if(Counter==QAM_CHECK_AGC_LOCK_COUNTER)
            return FALSE;

        if (!msAPI_Tuner_Wait(QAM_CHECK_AGC_LOCK_TIME_SLICE))
            return FALSE;

        Counter++;
    }
}

#undef _SAMSUNGDTVS205_C_
