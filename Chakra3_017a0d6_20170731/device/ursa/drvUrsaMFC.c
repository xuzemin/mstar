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
// Copyright (c) 2008 MStar Semiconductor, Inc.
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
// File Name: drvUrsaMFC.c
// Description: Comunication to URSA module
// Revision History:
//
////////////////////////////////////////////////////////////////////////////////
#define DRV_URSAMFC_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Board.h"
#include "string.h"

#include "hwreg.h"
//#include "datatype.h"
#include "drvGPIO.h"
#include "GPIO_macro.h"
#include "MApp_GlobalVar.h"
#include "msAPI_Timer.h"

#include "MApp_ZUI_Main.h"
#include "ZUI_tables_h.inl"

#if(ENABLE_MFC_6M20)
#include "drvUrsaMFC.h"
#include "drvUrsaMFCAPI.h"
#include "MApp_Isp.h"

//================================================================================
#define URSA_6M30_IIC_MODE_ADDR                     0xB8
static URSA_REGMAP              sm_sRegImageU;
static U8 Mst6m20isBlackScreen;
extern BOOLEAN IIC_SendByte(U8 u8dat);
extern BYTE IIC_GetByte (U16  bAck);
extern BOOLEAN  MDrv_IIC_WriteBytes(U16 u16BusNumSlaveID, U8 AddrCnt, U8* pu8addr, U16 u16size, U8* pBuf);
extern BOOLEAN  MDrv_IIC_ReadBytes(U16 u16BusNumSlaveID, U8 ucSubAdr, U8* paddr, U16 ucBufLen, U8* pBuf);
extern BOOL IIC_AccessStart(BYTE ucSlaveAdr, BYTE trans_t);
extern void MApi_SWI2C_UseBus( U8 u8BusChn );
#define TAS_I2C_ACCESS_DUMMY_TIME        3
//================================================================================
extern void MstarToolsDebug6MxxStart(void);
extern void MstarToolsDebug6MxxEnd(void);

static BOOLEAN MDrv_URSA_IIC_WriteBytes(U16 u16addr, BOOLEAN bHigh, U8 u8Buf)
{
    U8 u8Databuf[5] = {0, 0, 0, 0, 0};

    u8Databuf[0] = 0x10;
    u8Databuf[3] = u8Buf;

    if(bHigh == FALSE)
    {
        //e.g. address 0x29 11 --> 0x29 22,then we send 0x2922 to 6M10...
        u8Databuf[1] = (U8)(u16addr >> 8);   //the high byte need not move left 1 bit
        u8Databuf[2] = (U8)((u16addr << 1));//the low byte moves left 1 bit, reset bit0 means data low byte
    }
    else
    {
        u8Databuf[1] = (U8)(u16addr >> 8);  //the high byte need not move left 1 bit
        u8Databuf[2] = (U8)((u16addr << 1) | 0x01);//the low byte moves left 1 bit, set bit0 means data high byte
    }

    return (MDrv_IIC_WriteBytes(URSA_6M30_IIC_MODE_ADDR, 0, NULL, 4, u8Databuf));

}

static BOOLEAN MDrv_URSA_IIC_ReadBytes(U16 u16addr, BOOLEAN bHigh, U8* pBuf)
{
    BOOLEAN bResult;
    U8 u8Databuf[4]={0, 0, 0, 0};

    u8Databuf[0] = 0x10;

    if(bHigh == FALSE)
    {
        u8Databuf[1] = (U8)(u16addr >> 8);//the high byte need not move left 1 bit
        u8Databuf[2] = (U8)(u16addr << 1);//the low byte moves left 1 bit, reset bit0 means data low byte
    }
    else
    {
        u8Databuf[1] = (U8)(u16addr >> 8);//the high byte need not move left 1 bit
        u8Databuf[2] = (U8)((u16addr << 1) | 0x01);//the low byte moves left 1 bit, set bit0 means data high byte
    }

    bResult = MDrv_IIC_WriteBytes(URSA_6M30_IIC_MODE_ADDR, 0, NULL, 3, u8Databuf);
    bResult = MDrv_IIC_ReadBytes((URSA_6M30_IIC_MODE_ADDR+1), 0, NULL, 1, pBuf);

    return bResult;
}

static BOOLEAN MDrv_Ursa_GetValue(void)
{
    BOOLEAN bResult;
    bResult = MDrv_URSA_IIC_ReadBytes(sm_sRegImageU.uwAddr,sm_sRegImageU.bHigh,&sm_sRegImageU.ucData);
    if(bResult == FALSE)
    {
        printf("\n MDrv_Ursa_GetValue Error!!!\n");
    }

    return  bResult;
}

static BOOLEAN MDrv_Ursa_SetValue(void)
{
    BOOLEAN bResult;
    bResult = MDrv_URSA_IIC_WriteBytes(sm_sRegImageU.uwAddr,sm_sRegImageU.bHigh,sm_sRegImageU.ucData);
    if(bResult == FALSE)
    {
        printf("\n MDrv_Ursa_SetValue Error!!!\n");
    }
    return bResult;
}

#if  (NEW_URSA_SERIAL_DEBUG_MODE==0)
static BOOLEAN MDrv_Ursa_EnterSerialDebugMode(BOOLEAN bEnable)
{
    U8 u8DataBuf[6];
    BOOLEAN bResult = FALSE;

    if (bEnable)
    {
        u8DataBuf[0] = 0x53;
        u8DataBuf[1] = 0x45;
        u8DataBuf[2] = 0x52;
        u8DataBuf[3] = 0x44;
        u8DataBuf[4] = 0x42;

        bResult =  (MDrv_IIC_WriteBytes(URSA_6M30_IIC_MODE_ADDR, 0, NULL, 5, u8DataBuf));
    }
    else
    {
        u8DataBuf[0] = 0x45;
        bResult = (MDrv_IIC_WriteBytes(URSA_6M30_IIC_MODE_ADDR, 0, NULL, 1, u8DataBuf));
    }

    if(bResult == FALSE)
    {
        printf("\n MDrv_Ursa_EnterSerialDebugMode Error[%x]\n",bEnable);
    }

    return bResult;
}
static BOOLEAN MDrv_Ursa_CpuWait(BOOLEAN bEnable)
{
    U8 u8DataBuf;
    BOOLEAN bResult = FALSE;

    if(bEnable)
        u8DataBuf = 0x37;
    else
        u8DataBuf = 0x36;
     bResult=MDrv_IIC_WriteBytes(URSA_6M30_IIC_MODE_ADDR, 0, NULL, 1, &u8DataBuf);
     if(bResult == FALSE)
     {
        printf("\n MDrv_Ursa_CpuWait Error!!!\n");
     }
     return bResult;
}

static BOOLEAN MDrv_Ursa_IICUseBus(BOOLEAN bEnable)
{
    U8 u8DataBuf;
    BOOLEAN bResult = FALSE;

    if(bEnable)
        u8DataBuf = 0x35;
    else
        u8DataBuf = 0x34;
    bResult=MDrv_IIC_WriteBytes(URSA_6M30_IIC_MODE_ADDR, 0, NULL, 1, &u8DataBuf);
     if(bResult == FALSE)
     {
        printf("\n MDrv_Ursa_IICUseBus!!!\n");
     }
     return bResult;
}
#else //(NEW_URSA_SERIAL_DEBUG_MODE==0)
typedef enum
{
    MFC_I2cUseBusN       = 0x34,
    MFC_I2cUseBus        = 0x35,
    MFC_CpuWaitN         = 0x36,
    MFC_CpuWait          = 0x37,
    MFC_SerialDebugEnter = 0x44,
    MFC_SerialDebugExit  = 0x45,
    MFC_SetAddrFmt2Byte  = 0x51,
    MFC_DisableNewCfg    = 0x7E,
    MFC_EnableNewCfg     = 0x7F,
    MFC_ChNumBit0Disable = 0x80,
    MFC_ChNumBit0Enable  = 0x81,
    MFC_ChNumBit1Disable = 0x82,
    MFC_ChNumBit1Enable  = 0x83,
    MFC_ChNumBit2Disable = 0x84,
    MFC_ChNumBit2Enable  = 0x85,
} MFC_SERIAL_DEBUG_CMD_e;

BOOLEAN MDrv_MFC_SetSerialDebugMode(MFC_SERIAL_DEBUG_CMD_e cmd)
{
    U32  u32Addr;
    U8   u8Data[5];
    BOOLEAN ret;

    u32Addr = 0;

    if (cmd == MFC_SerialDebugEnter)
    {
        u8Data[0] = 0x53;
        u8Data[1] = 0x45;
        u8Data[2] = 0x52;
        u8Data[3] = 0x44;
        u8Data[4] = 0x42;
        ret = MDrv_IIC_WriteBytes(URSA_6M30_IIC_MODE_ADDR, 0, NULL, 5, u8Data);
        if (!ret)
        {
    //       dbgprint("MFC_SerialDebugEnter %d   %s\n",__LINE__,__FILE__);
    //      dbgprint("MFC_SerialDebugEnter=============cmd = 0x%x===================\n", cmd);
            return FALSE;
        }
    }
    else
    {
        u8Data[0] = cmd;
        ret = (MDrv_IIC_WriteBytes(URSA_6M30_IIC_MODE_ADDR, 0, NULL, 1, u8Data));
        if (!ret)
        {
            if(cmd != MFC_SerialDebugExit)
            {
                return FALSE;
            }
        }
    }
    return TRUE;
}

static BOOLEAN isI2cOpen=FALSE;
#define MST6Mxx_I2C_USE_CH2   1
void MDrv_MFC_SetSerialDebug(BOOL bOpen)
{
    if(bOpen)
    {
        if(isI2cOpen==FALSE)
        {
            MDrv_MFC_SetSerialDebugMode(MFC_SerialDebugEnter);
            #if MST6Mxx_I2C_USE_CH2
            MDrv_MFC_SetSerialDebugMode(MFC_ChNumBit0Disable);
            MDrv_MFC_SetSerialDebugMode(MFC_ChNumBit1Enable);
            MDrv_MFC_SetSerialDebugMode(MFC_ChNumBit2Disable);  //Switch to Ch2
            MDrv_MFC_SetSerialDebugMode(MFC_SetAddrFmt2Byte);
            MDrv_MFC_SetSerialDebugMode(MFC_EnableNewCfg);
            #else
            MDrv_MFC_SetSerialDebugMode(MFC_CpuWait);
            #endif
            MDrv_MFC_SetSerialDebugMode(MFC_I2cUseBus);
            isI2cOpen=TRUE;
        }
    }
    else
    {
        if(isI2cOpen)
        {
            MDrv_MFC_SetSerialDebugMode(MFC_I2cUseBusN);
            #if MST6Mxx_I2C_USE_CH2
            MDrv_MFC_SetSerialDebugMode(MFC_ChNumBit0Disable);
            MDrv_MFC_SetSerialDebugMode(MFC_ChNumBit1Disable);
            MDrv_MFC_SetSerialDebugMode(MFC_ChNumBit2Disable);
            MDrv_MFC_SetSerialDebugMode(MFC_SetAddrFmt2Byte);
            MDrv_MFC_SetSerialDebugMode(MFC_DisableNewCfg);
            #else
            MDrv_MFC_SetSerialDebugMode(MFC_CpuWaitN);
            #endif
            MDrv_MFC_SetSerialDebugMode(MFC_SerialDebugExit);
            isI2cOpen=FALSE;
        }
    }

}
#endif //(NEW_URSA_SERIAL_DEBUG_MODE==0)

void MDrv_Ursa_DemoLine_Show(BOOLEAN bEnable, BOOLEAN bVEnable)
{
    U16 u16Data_2F0C, u16Data_2F10;

    MstarToolsDebug6MxxStart();

    sm_sRegImageU.uwAddr = reg_3050MFC;
    sm_sRegImageU.bHigh = TRUE;
    sm_sRegImageU.ucData = 0;
    MDrv_Ursa_SetValue();

    sm_sRegImageU.uwAddr = reg_2F0CMFC;
    sm_sRegImageU.bHigh = TRUE;
    MDrv_Ursa_GetValue();
    u16Data_2F0C = sm_sRegImageU.ucData;
    u16Data_2F0C = (u16Data_2F0C<<8);
    u16Data_2F0C = u16Data_2F0C& 0xFF00;

    sm_sRegImageU.uwAddr = reg_2F0CMFC;
    sm_sRegImageU.bHigh = FALSE;
    MDrv_Ursa_GetValue();
    u16Data_2F0C |= sm_sRegImageU.ucData;


    sm_sRegImageU.uwAddr = reg_2F10MFC;
    sm_sRegImageU.bHigh = TRUE;
    MDrv_Ursa_GetValue();
    u16Data_2F10 = sm_sRegImageU.ucData;
    u16Data_2F10 = (u16Data_2F10<<8);
    u16Data_2F10 = u16Data_2F10& 0xFF00;

    sm_sRegImageU.uwAddr = reg_2F10MFC;
    sm_sRegImageU.bHigh = FALSE;
    MDrv_Ursa_GetValue();
    u16Data_2F10 |= sm_sRegImageU.ucData;

    if(bVEnable==TRUE)
    {
        sm_sRegImageU.uwAddr = reg_2F2BMFC;
        sm_sRegImageU.bHigh = TRUE;
        MDrv_Ursa_GetValue();
        sm_sRegImageU.ucData = (bEnable == TRUE?(sm_sRegImageU.ucData|BIT7):(sm_sRegImageU.ucData&(~BIT7)));
        sm_sRegImageU.ucData = sm_sRegImageU.ucData&(~BIT5);
        sm_sRegImageU.ucData = (bVEnable == FALSE?(sm_sRegImageU.ucData|BIT6):(sm_sRegImageU.ucData&(~BIT6)));
        MDrv_Ursa_SetValue();

        sm_sRegImageU.uwAddr = reg_2F2BMFC;
        sm_sRegImageU.bHigh = FALSE;
        sm_sRegImageU.ucData = 0;
        MDrv_Ursa_SetValue();
    }
    else
    {
         if( u16Data_2F0C > u16Data_2F10 )
         {
            sm_sRegImageU.uwAddr = reg_2F2BMFC;
            sm_sRegImageU.bHigh = TRUE;
            MDrv_Ursa_GetValue();
            sm_sRegImageU.ucData = (bEnable == TRUE?(sm_sRegImageU.ucData|BIT7):(sm_sRegImageU.ucData&(~BIT7)));
            sm_sRegImageU.ucData = sm_sRegImageU.ucData&(~BIT5);
            sm_sRegImageU.ucData = (bVEnable == FALSE?(sm_sRegImageU.ucData|BIT6):(sm_sRegImageU.ucData&(~BIT6)));
            MDrv_Ursa_SetValue();

            sm_sRegImageU.uwAddr = reg_2F2BMFC;
            sm_sRegImageU.bHigh = FALSE;
            sm_sRegImageU.ucData = (u16Data_2F0C - u16Data_2F10)/2 + u16Data_2F10/2;
            MDrv_Ursa_SetValue();
         }
       else
         {
             sm_sRegImageU.uwAddr = reg_2F2BMFC;
             sm_sRegImageU.bHigh = TRUE;
             MDrv_Ursa_GetValue();
             sm_sRegImageU.ucData = (bEnable == TRUE?(sm_sRegImageU.ucData|BIT7):(sm_sRegImageU.ucData&(~BIT7)));
             sm_sRegImageU.ucData = sm_sRegImageU.ucData|BIT5;
             sm_sRegImageU.ucData = (bVEnable == FALSE?(sm_sRegImageU.ucData|BIT6):(sm_sRegImageU.ucData&(~BIT6)));
             MDrv_Ursa_SetValue();

            sm_sRegImageU.uwAddr = reg_2F2BMFC;
            sm_sRegImageU.bHigh = FALSE;
            sm_sRegImageU.ucData = abs((u16Data_2F10 - u16Data_2F0C)/2 + u16Data_2F10/2);
            MDrv_Ursa_SetValue();
         }
    }

        MstarToolsDebug6MxxEnd();
}
BOOLEAN MDrv_Ursa_Demo_Cmd(EN_MFC_DEMO enMFCDemo)
{
    BOOL bEnableMFC = FALSE;

     if(enMFCDemo < EN_MFC_Demo_Off)
         bEnableMFC = TRUE;
     else
         bEnableMFC = FALSE;

     switch(enMFCDemo)
     {
          case EN_MFC_Demo_On:
                  MDrv_Ursa_Cmd(EN_URSA_CMD_DEMO_POS_X, FALSE);
                  MDrv_Ursa_Cmd(EN_URSA_CMD_DEMO_POS_Y, FALSE);
                  MDrv_Ursa_DemoLine_Show(FALSE, FALSE);
                  //MDrv_Ursa_Cmd(EN_URSA_CMD_DEMO_POS_LINE, FALSE);
                  MDrv_Ursa_Cmd(EN_URSA_CMD_ENABLE_MFC_ALL, bEnableMFC);
           break;
          case EN_MFC_Demo_Top:
                  MDrv_Ursa_Cmd(EN_URSA_CMD_DEMO_POS_INV, FALSE);
                  MDrv_Ursa_Cmd(EN_URSA_CMD_DEMO_POS_Y, FALSE);
                  MDrv_Ursa_Cmd(EN_URSA_CMD_ENABLE_MFC_ALL, bEnableMFC);
                  MDrv_Ursa_DemoLine_Show(bEnableMFC, TRUE);
                  //MDrv_Ursa_Cmd(EN_URSA_CMD_DEMO_POS_LINE, bEnableMFC);
                  MDrv_Ursa_Cmd(EN_URSA_CMD_DEMO_POS_X, bEnableMFC);
           break;
          case EN_MFC_Demo_Right:
                  MDrv_Ursa_Cmd(EN_URSA_CMD_DEMO_POS_X, FALSE);
                  MDrv_Ursa_Cmd(EN_URSA_CMD_DEMO_POS_Y, bEnableMFC);
                  //MDrv_Ursa_Cmd(EN_URSA_CMD_ENABLE_MFC_ALL, bEnableMFC);
                  MDrv_Ursa_DemoLine_Show(bEnableMFC, FALSE);
                  //MDrv_Ursa_Cmd(EN_URSA_CMD_DEMO_POS_LINE, bEnableMFC);
                  MDrv_Ursa_Cmd(EN_URSA_CMD_DEMO_POS_INV, bEnableMFC);
           break;
          case EN_MFC_Demo_Left:
                  MDrv_Ursa_Cmd(EN_URSA_CMD_DEMO_POS_INV, FALSE);
                  MDrv_Ursa_Cmd(EN_URSA_CMD_DEMO_POS_X, FALSE);
                  MDrv_Ursa_Cmd(EN_URSA_CMD_ENABLE_MFC_ALL, bEnableMFC);
                  MDrv_Ursa_DemoLine_Show(bEnableMFC, FALSE);
                  //MDrv_Ursa_Cmd(EN_URSA_CMD_DEMO_POS_LINE, bEnableMFC);
                  MDrv_Ursa_Cmd(EN_URSA_CMD_DEMO_POS_Y, bEnableMFC);
           break;
          case EN_MFC_Demo_Down:
                  MDrv_Ursa_Cmd(EN_URSA_CMD_DEMO_POS_Y, FALSE);
                  MDrv_Ursa_Cmd(EN_URSA_CMD_ENABLE_MFC_ALL, bEnableMFC);
                  MDrv_Ursa_DemoLine_Show(bEnableMFC, TRUE);
                  //MDrv_Ursa_Cmd(EN_URSA_CMD_DEMO_POS_LINE, bEnableMFC);
                  MDrv_Ursa_Cmd(EN_URSA_CMD_DEMO_POS_X, bEnableMFC);
                  MDrv_Ursa_Cmd(EN_URSA_CMD_DEMO_POS_INV, bEnableMFC);
           break;
          case EN_MFC_Demo_Off:
                  MDrv_Ursa_DemoLine_Show(FALSE, FALSE);
                  MDrv_Ursa_Cmd(EN_URSA_CMD_ENABLE_MFC_ALL, bEnableMFC);
           break;
            default:
           break;
     }
     return TRUE;
}
BOOLEAN MDrv_Ursa_Cmd(EN_URSA_CMD_INDEX CmdIndex, BOOLEAN bEnable)
{
    BOOLEAN bResult;
    MstarToolsDebug6MxxStart();

    switch(CmdIndex)
    {
        case EN_URSA_CMD_ENABLE_MFC:
            sm_sRegImageU.uwAddr = reg_2907MFC;//0x320B;
            sm_sRegImageU.bHigh = TRUE;
            bResult = MDrv_Ursa_GetValue();
            //if(bResult)
                sm_sRegImageU.ucData = ((bEnable == TRUE)?(sm_sRegImageU.ucData|BIT1):(sm_sRegImageU.ucData&~BIT1));
            bResult = MDrv_Ursa_SetValue();
            break;
        case EN_URSA_CMD_ENABLE_FILM22:
            sm_sRegImageU.uwAddr = reg_2907MFC;
            sm_sRegImageU.bHigh = FALSE;
            bResult = MDrv_Ursa_GetValue();
            if(bResult)
                sm_sRegImageU.ucData = (bEnable == TRUE?(sm_sRegImageU.ucData|BIT2):(sm_sRegImageU.ucData&~BIT2));
            bResult = MDrv_Ursa_SetValue();
            break;
        case EN_URSA_CMD_ENABLE_FILM32:
            sm_sRegImageU.uwAddr = reg_2907MFC;
            sm_sRegImageU.bHigh = FALSE;
            bResult = MDrv_Ursa_GetValue();
            if(bResult)
                sm_sRegImageU.ucData = (bEnable == TRUE?(sm_sRegImageU.ucData|BIT3):(sm_sRegImageU.ucData&~BIT3));
            bResult = MDrv_Ursa_SetValue();
            break;
        case EN_URSA_CMD_DEMO_POS_INV:
            sm_sRegImageU.uwAddr = reg_2940MFC;
            sm_sRegImageU.bHigh = TRUE;
            bResult = MDrv_Ursa_GetValue();
            if(bResult)
                sm_sRegImageU.ucData = (bEnable == TRUE?(sm_sRegImageU.ucData|BIT7):(sm_sRegImageU.ucData&~BIT7));
            bResult = MDrv_Ursa_SetValue();
            break;
        /*case EN_URSA_CMD_DEMO_POS_LINE:
            sm_sRegImageU.uwAddr = reg_2940MFC;
            sm_sRegImageU.bHigh = TRUE;
            bResult = MDrv_Ursa_GetValue();
            if(bResult)
                sm_sRegImageU.ucData = (bEnable == TRUE?(sm_sRegImageU.ucData|BIT6):(sm_sRegImageU.ucData&~BIT6));
            bResult = MDrv_Ursa_SetValue();
            break;*/
        case EN_URSA_CMD_DEMO_POS_X:
            sm_sRegImageU.uwAddr = reg_2940MFC;
            sm_sRegImageU.bHigh = TRUE;
            bResult = MDrv_Ursa_GetValue();
            if(bResult)
                sm_sRegImageU.ucData = (bEnable == TRUE?(sm_sRegImageU.ucData|BIT5):(sm_sRegImageU.ucData&~BIT5));
            bResult = MDrv_Ursa_SetValue();
            break;
        case EN_URSA_CMD_DEMO_POS_Y:
            sm_sRegImageU.uwAddr = reg_2940MFC;
            sm_sRegImageU.bHigh = TRUE;
            bResult = MDrv_Ursa_GetValue();
            if(bResult)
                sm_sRegImageU.ucData = (bEnable == TRUE?(sm_sRegImageU.ucData|BIT4):(sm_sRegImageU.ucData&~BIT4));
            bResult = MDrv_Ursa_SetValue();
            break;
        case EN_URSA_CMD_ENABLE_MFC_ALL:
            sm_sRegImageU.uwAddr = reg_2907MFC;
            sm_sRegImageU.bHigh = FALSE;
            bResult = MDrv_Ursa_GetValue();
            if(bResult)
                sm_sRegImageU.ucData = ((bEnable == TRUE)?(sm_sRegImageU.ucData|0x0E):(sm_sRegImageU.ucData&~0x0E));
            bResult = MDrv_Ursa_SetValue();
            break;

        case EN_URSA_CMD_DEMO_STATUS:
            sm_sRegImageU.uwAddr = reg_2905MFC;
            sm_sRegImageU.bHigh = FALSE;
            bResult = MDrv_Ursa_GetValue();
            if(bResult)
                sm_sRegImageU.ucData = ((bEnable == TRUE)?(sm_sRegImageU.ucData|BIT1):(sm_sRegImageU.ucData&~BIT1));
            bResult = MDrv_Ursa_SetValue();
            break;

        case EN_URSA_CMD_ENABLE_BLACKSCREEN:
            if(bEnable)
            {
                sm_sRegImageU.uwAddr = reg_3015MFC;
                sm_sRegImageU.bHigh = FALSE;
                sm_sRegImageU.ucData = 0x00;
                bResult = MDrv_Ursa_SetValue();
                sm_sRegImageU.uwAddr = 0x3015;
                sm_sRegImageU.bHigh = TRUE;
                sm_sRegImageU.ucData = 0x00;
                bResult = MDrv_Ursa_SetValue();

                sm_sRegImageU.uwAddr = reg_3016MFC;
                sm_sRegImageU.bHigh = FALSE;
                sm_sRegImageU.ucData = 0x00;
                bResult = MDrv_Ursa_SetValue();
                sm_sRegImageU.uwAddr = reg_3016MFC;
                sm_sRegImageU.bHigh = TRUE;
                sm_sRegImageU.ucData = 0x02;
                bResult = MDrv_Ursa_SetValue();

                sm_sRegImageU.uwAddr = reg_3017MFC;
                sm_sRegImageU.bHigh = FALSE;
                sm_sRegImageU.ucData = 0x00;
                bResult = MDrv_Ursa_SetValue();

                sm_sRegImageU.uwAddr = reg_3017MFC;
                sm_sRegImageU.bHigh = TRUE;
                sm_sRegImageU.ucData = 0x02;
                bResult = MDrv_Ursa_SetValue();

                sm_sRegImageU.uwAddr = reg_300BMFC;
                sm_sRegImageU.bHigh = TRUE;
                bResult = MDrv_Ursa_GetValue();
                if(bResult)
                {
                    sm_sRegImageU.ucData = ((bEnable == TRUE)?(sm_sRegImageU.ucData|BIT2):(sm_sRegImageU.ucData&~BIT2));
                }
                bResult = MDrv_Ursa_SetValue();
            }
            else
            {
                sm_sRegImageU.uwAddr = reg_300BMFC;
                sm_sRegImageU.bHigh = TRUE;
                bResult = MDrv_Ursa_GetValue();
                if(bResult)
                {
                    sm_sRegImageU.ucData = ((bEnable == TRUE)?(sm_sRegImageU.ucData|BIT2):(sm_sRegImageU.ucData&~BIT2));
                }
                bResult = MDrv_Ursa_SetValue();

                sm_sRegImageU.uwAddr = reg_3015MFC;
                sm_sRegImageU.bHigh = FALSE;
                sm_sRegImageU.ucData = 0x00;
                bResult = MDrv_Ursa_SetValue();
                sm_sRegImageU.uwAddr = reg_3015MFC;
                sm_sRegImageU.bHigh = TRUE;
                sm_sRegImageU.ucData = 0x01;
                bResult = MDrv_Ursa_SetValue();

                sm_sRegImageU.uwAddr = reg_3016MFC;
                sm_sRegImageU.bHigh = FALSE;
                sm_sRegImageU.ucData = 0xFF;
                bResult = MDrv_Ursa_SetValue();
                sm_sRegImageU.uwAddr = reg_3016MFC;
                sm_sRegImageU.bHigh = TRUE;
                sm_sRegImageU.ucData = 0x01;
                bResult = MDrv_Ursa_SetValue();

                sm_sRegImageU.uwAddr = reg_3017MFC;
                sm_sRegImageU.bHigh = FALSE;
                sm_sRegImageU.ucData = 0xFF;
                bResult = MDrv_Ursa_SetValue();
                sm_sRegImageU.uwAddr = reg_3017MFC;
                sm_sRegImageU.bHigh = TRUE;
                sm_sRegImageU.ucData = 0x01;
                bResult = MDrv_Ursa_SetValue();

            }
         break;

        default:

            return TRUE;
    }


    MstarToolsDebug6MxxEnd();

    return bResult;
}

void MDrv_Ursa_MemcLevelSetting(U8 u8Level)
{
    BOOLEAN bResult;

    MstarToolsDebug6MxxStart();

    sm_sRegImageU.uwAddr = reg_MFCLevel;
    sm_sRegImageU.bHigh = false;
    bResult = MDrv_Ursa_GetValue();
    sm_sRegImageU.ucData = (sm_sRegImageU.ucData & 0xF0) | u8Level;
    bResult = MDrv_Ursa_SetValue();
    //printf("MDrv_Ursa_MemcLevelSetting=%x\n",(U16)sm_sRegImageU.ucData);

    MstarToolsDebug6MxxEnd();

    if(EN_URSA_MEMC_LEVEL_OFF==u8Level)
        MDrv_Ursa_Cmd(EN_URSA_CMD_ENABLE_MFC_ALL,0);
    else
        MDrv_Ursa_Cmd(EN_URSA_CMD_ENABLE_MFC_ALL,1);

    //printf("\nMDrv_Ursa_MemcLevelSetting[%d]",u8Level);
}

//////////////////////////////////////////////////////////////////////////////////
// Black Screen Switch Function.
//
// Parameters:
//              u8Enable:
//                          0 => Disable
//                          1 => Enable
// Return:
//              None.
// Author:
//////////////////////////////////////////////////////////////////////////////////
void MDrv_Ursa_BlackScreen(void)
{
       if (!Mst6m20isBlackScreen)
       {
           MDrv_Ursa_Cmd(EN_URSA_CMD_ENABLE_BLACKSCREEN,TRUE);
           Mst6m20isBlackScreen = 1;
       }
}
void MDrv_Ursa_InputFormatChangeNotify(void)
{
    if (Mst6m20isBlackScreen)
    {
       MDrv_Ursa_Cmd(EN_URSA_CMD_ENABLE_BLACKSCREEN,FALSE);
       Mst6m20isBlackScreen = 0;
    }
}

 U16 code aAddr[4] = {reg_OSDX0,reg_OSDX1,reg_OSDY0,reg_OSDY1};
 void MDrv_Ursa_DisableOsdArea(BOOLEAN bEnable)
{
     BOOLEAN bResult;
    MstarToolsDebug6MxxStart();

    sm_sRegImageU.uwAddr = reg_2420MFC;
    sm_sRegImageU.bHigh = FALSE;
    bResult = MDrv_Ursa_GetValue();
    //if(bResult)
        sm_sRegImageU.ucData = ((bEnable==TRUE)?(sm_sRegImageU.ucData|BIT4|BIT0):(sm_sRegImageU.ucData&~(BIT4|BIT0)));
    bResult = MDrv_Ursa_SetValue();

    sm_sRegImageU.uwAddr = reg_2436MFC;
    sm_sRegImageU.bHigh = FALSE;
    bResult = MDrv_Ursa_GetValue();
    //if(bResult)
        sm_sRegImageU.ucData = ((bEnable==TRUE)?(sm_sRegImageU.ucData|BIT0):(sm_sRegImageU.ucData&~BIT0));
    bResult = MDrv_Ursa_SetValue();

    sm_sRegImageU.uwAddr = reg_2613MFC;
    sm_sRegImageU.bHigh = FALSE;
    bResult = MDrv_Ursa_GetValue();
    //if(bResult)
        sm_sRegImageU.ucData = ((bEnable==TRUE)?(sm_sRegImageU.ucData|BIT0):(sm_sRegImageU.ucData&~BIT0));
    bResult = MDrv_Ursa_SetValue();

    MstarToolsDebug6MxxEnd();

 }

BOOLEAN MDrv_Ursa_SetOsdArea(U16 u16StartX,U16 u16StartY, U16 u16Width, U16 u16Height)
{
    BOOLEAN bResult;
    U8 i;
    U16 aData[4];

    MstarToolsDebug6MxxStart();

     sm_sRegImageU.uwAddr = reg_2420MFC;
    sm_sRegImageU.bHigh = FALSE;
    bResult = MDrv_Ursa_GetValue();
    //if(bResult)
        sm_sRegImageU.ucData = (sm_sRegImageU.ucData|BIT4|BIT0);
    bResult = MDrv_Ursa_SetValue();

    sm_sRegImageU.uwAddr = reg_2436MFC;
    sm_sRegImageU.bHigh = FALSE;
    bResult = MDrv_Ursa_GetValue();
    //if(bResult)
        sm_sRegImageU.ucData = (sm_sRegImageU.ucData|BIT0);
    bResult = MDrv_Ursa_SetValue();

    sm_sRegImageU.uwAddr = reg_2613MFC;
    sm_sRegImageU.bHigh = FALSE;
    bResult = MDrv_Ursa_GetValue();
    //if(bResult)
        sm_sRegImageU.ucData = (sm_sRegImageU.ucData|BIT0);
    bResult = MDrv_Ursa_SetValue();

    aData[0] = u16StartX;
    aData[1] = u16StartX + u16Width;
    aData[2] = u16StartY;
    aData[3] = u16StartY+u16Height;

     printf("x0[0x%x] x1[0x%x] y0[0x%x] y1[0x%x]",u16StartX,u16Width,u16StartY,u16Height);

    for(i=0;i<4;i++)
    {
        sm_sRegImageU.uwAddr = aAddr[i];
        sm_sRegImageU.bHigh = TRUE;
        sm_sRegImageU.ucData = HIGHBYTE(aData[i]);
        bResult = MDrv_Ursa_SetValue();

        sm_sRegImageU.uwAddr = aAddr[i];
        sm_sRegImageU.bHigh = FALSE;
        sm_sRegImageU.ucData = LOWBYTE(aData[i]);
        bResult = MDrv_Ursa_SetValue();
    }
    MstarToolsDebug6MxxEnd();

    return bResult;
}

BOOLEAN MDrv_Ursa_Set_Value(U16 u16addr, BOOLEAN bHigh, U8 u8Buf)
{
    BOOLEAN bRet = FALSE;
    U8 u8Databuf[5] = {0, 0, 0, 0, 0};
    MstarToolsDebug6MxxStart();
    UNUSED(bHigh);
    u8Databuf[0] = 0x10;
    u8Databuf[3] = u8Buf;

    //e.g. address 0x29 11 --> 0x29 11,then we send 0x2911 to 6M10...
    u8Databuf[1] = (U8)(u16addr >> 8);   //the high byte need not move left 1 bit
    u8Databuf[2] = (U8)(u16addr);//the low byte moves left 1 bit, reset bit0 means data low byte
    bRet = MDrv_IIC_WriteBytes(URSA_6M30_IIC_MODE_ADDR, 0, NULL, 4, u8Databuf);

    MstarToolsDebug6MxxEnd();
    return bRet;
}

U8 MDrv_Ursa_Get_Value_8BitMode(U16 U16Addr, BOOLEAN bHigh)
{
    U8 u8Data, u8Databuf[4]={0, 0, 0, 0};

    MstarToolsDebug6MxxStart();

    u8Databuf[0] = 0x10;

    if(bHigh == FALSE)
    {
        u8Databuf[1] = (U8)(U16Addr >> 8);//the high byte need not move left 1 bit
        u8Databuf[2] = (U8)(U16Addr);//the low byte moves left 1 bit, reset bit0 means data low byte
    }
    else
    {
        u8Databuf[1] = (U8)(U16Addr >> 8);//the high byte need not move left 1 bit
        u8Databuf[2] = (U8)(U16Addr | 0x01);//the low byte moves left 1 bit, set bit0 means data high byte
    }

    MDrv_IIC_WriteBytes(URSA_6M30_IIC_MODE_ADDR, 0, NULL, 3, u8Databuf);
    MDrv_IIC_ReadBytes((URSA_6M30_IIC_MODE_ADDR+1), 0, NULL, 1, &u8Data);

    MstarToolsDebug6MxxEnd();

    return u8Data;
}

U8 MDrv_Ursa_Get_Value_16BitMode(U16 U16Addr, BOOLEAN bHigh)
{
    U8 u8Data, u8Databuf[4]={0, 0, 0, 0};

    MstarToolsDebug6MxxStart();

    u8Databuf[0] = 0x10;

    if(bHigh == FALSE)
    {
        u8Databuf[1] = (U8)(U16Addr >> 8);//the high byte need not move left 1 bit
        u8Databuf[2] = (U8)(U16Addr << 1);//the low byte moves left 1 bit, reset bit0 means data low byte
    }
    else
    {
        u8Databuf[1] = (U8)(U16Addr >> 8);//the high byte need not move left 1 bit
        u8Databuf[2] = (U8)((U16Addr << 1) | 0x01);//the low byte moves left 1 bit, set bit0 means data high byte
    }

    MDrv_IIC_WriteBytes(URSA_6M30_IIC_MODE_ADDR, 0, NULL, 3, u8Databuf);
    MDrv_IIC_ReadBytes((URSA_6M30_IIC_MODE_ADDR+1), 0, NULL, 1, &u8Data);

    MstarToolsDebug6MxxEnd();

    return u8Data;
}

void MDrv_Ursa_Init(void)//(BOOLEAN bEnable)
{
    //bEnable = bEnable;
    Mst6m20isBlackScreen = 0;
}

U8 MDrv_Ursa_GetOsdIndex(U8 PageIdx)
{
    switch(PageIdx)
    {
        default:
            return 0;
    };
}

typedef struct
{
    U16   u16Hstart;
    U16   u16Vstart;
    U16   u16Hsize;
    U16   u16Vsize;
} MenuOsdProtectType;

MenuOsdProtectType code MainMenu_Protect           ={0x00,0x00,0x780,0x438};//{0x259,0x150,0x515,0x310};
MenuOsdProtectType code SubAdjustMenu_Protect   ={0x00,0x350,0x200,0x430};
MenuOsdProtectType code SourceMenu_Protect        ={0x00,0x00,0x780,0x438};//{0x580,0x280,0x15e,0x406};
MenuOsdProtectType code PictureMode_Protect        ={0x1EF,0x36C,0x13D,0x5C};//{0x280,0x500,0x390,0x420};
MenuOsdProtectType code VolumnBarMenu_Protect  ={0x00,0x00,0x780,0x438};//{0x1EF,0x36C,0x3A2,0x8A};//{0x210,0x40,0x570,0x100};
MenuOsdProtectType code InfoMenu_Protect            ={0x6A0,0x370,0x100,0x100};
MenuOsdProtectType code DemoMenu_Protect          ={0x02fc,0x0190,0x01d0,0x00b8};
MenuOsdProtectType code EPGMenu_Protect            ={0x00,0x00,0x780,0x438};//{0x00E0,0x06C0,0x00C0,0x03A0};
MenuOsdProtectType code MuteMenu_Protect            ={0x10,0x10,0x100,0x100};
MenuOsdProtectType code PVR_Record_Protect            ={0x00,0x00,0x780,0x438};//{0x630,0x7a0,0x350,0x500};
MenuOsdProtectType code PVR_Protect            ={0xff,0x5D0,0x350,0x500};
MenuOsdProtectType code ATV_MANUAL_SCAN={0x2E0,0x4AF,0xE0,0x330};
MenuOsdProtectType code MENU_MEDIA_PLAYER_Protect           ={0x00,0x00,0x780,0x438};
 void MDrv_Ursa_OsdWinHandler(BOOLEAN flag)
{
    U16 wHstart,wVstart,wHsize,wVsize;

    if (flag)
    {
        switch (MApp_ZUI_GetActiveOSD())
        {
            case E_OSD_MAIN_MENU:
            {
                wHstart=MainMenu_Protect.u16Hstart;
                wVstart=MainMenu_Protect.u16Vstart;
                wHsize=MainMenu_Protect.u16Hsize;
                wVsize=MainMenu_Protect.u16Vsize;
            }
            break;

            default:
            {
                wHstart=0;
                wVstart=0;
                wHsize=0;
                wVsize=0;
            }
            break;
        }
         MDrv_Ursa_SetOsdArea(wHstart,wVstart,wHsize,wVsize);
     }
    else
    {
        wHstart=0;
        wVstart=0;
        wHsize=0;
        wVsize=0;
        MDrv_Ursa_DisableOsdArea(FALSE);
    }
}
void MDrv_Ursa_Ctrl(BOOLEAN bCtrl)
{
    BOOLEAN bResult;
    MstarToolsDebug6MxxStart();

    sm_sRegImageU.uwAddr = reg_290EMFC;
    sm_sRegImageU.bHigh = FALSE;
    if(bCtrl)
          sm_sRegImageU.ucData =0x2F;
   else
            sm_sRegImageU.ucData =0x00;
   bResult = MDrv_Ursa_SetValue();
   MstarToolsDebug6MxxEnd();
}
void MstarToolsDebug6MxxStart(void)
{
    #if (NEW_URSA_SERIAL_DEBUG_MODE==0)
        MDrv_Ursa_EnterSerialDebugMode(TRUE);
        MDrv_Ursa_CpuWait(TRUE);
        MDrv_Ursa_IICUseBus(TRUE);
    #else
        MDrv_MFC_SetSerialDebug(TRUE);
    #endif
}
void MstarToolsDebug6MxxEnd(void)
{
    #if (NEW_URSA_SERIAL_DEBUG_MODE==0)
    MDrv_Ursa_IICUseBus(FALSE);
    MDrv_Ursa_CpuWait(FALSE);
    MDrv_Ursa_EnterSerialDebugMode(FALSE);
    #else
    MDrv_MFC_SetSerialDebug(FALSE);
    #endif
}
void  MDrv_Ursa_LVDS_Output(BOOLEAN bEnable )
{
    BOOLEAN bResult;// U8 u8Data;
    MstarToolsDebug6MxxStart();
    {//Open 6M20
        sm_sRegImageU.uwAddr = reg_3250MFC;
        sm_sRegImageU.bHigh = FALSE;
        bResult = MDrv_Ursa_GetValue();
        sm_sRegImageU.ucData = ( ( bEnable == TRUE ) ?  ( sm_sRegImageU.ucData & (~BIT0) ) :( sm_sRegImageU.ucData | BIT0 ));
        bResult = MDrv_Ursa_SetValue();
    }

    MstarToolsDebug6MxxEnd();
 }
extern void MDrv_Scaler_SetPanelVCC(BOOLEAN bEnable);
void MDrv_Ursa_Reset_LVDS(void)
{
        BOOLEAN bResult;
        U32 u32Mst6m10InitTimer0, u32Mst6m10InitTimer1;

    #if (MST6M10_RESET_MODE == 3)
        printf("\n6M10Init[HW]: {[%ld]->", gTimerCount0);
        //MST6M10_RESET_ON();
        msAPI_Timer_Delayms(50);
        //MST6M10_RESET_OFF();
    #else
        MstarToolsDebug6MxxStart();
        sm_sRegImageU.uwAddr = reg_207DMFC;
        sm_sRegImageU.bHigh = FALSE;
        sm_sRegImageU.ucData =0x01;//0x01
        bResult = MDrv_Ursa_SetValue();
        MstarToolsDebug6MxxEnd();
    #endif

        u32Mst6m10InitTimer0 = msAPI_Timer_GetTime0();
        u32Mst6m10InitTimer1 = u32Mst6m10InitTimer0;
        while(msAPI_Timer_DiffTimeFromNow(u32Mst6m10InitTimer1) < 1200)
        {
            if (msAPI_Timer_DiffTimeFromNow(u32Mst6m10InitTimer1) > 800)
            {
                if (msAPI_Timer_DiffTimeFromNow(u32Mst6m10InitTimer0) > 100)
                {
                    MstarToolsDebug6MxxStart();
                    sm_sRegImageU.uwAddr = reg_207DMFC;
                    sm_sRegImageU.bHigh = FALSE;
                    bResult = MDrv_Ursa_GetValue();
                    MstarToolsDebug6MxxEnd();

                    u32Mst6m10InitTimer0 = msAPI_Timer_GetTime0();
                    if (sm_sRegImageU.ucData == MST6M10_SW_VERSION)
                    {
                        break;
                    }
                }
            }
        }
        printf("u32Mst6m10InitTimer1=%lx\n",msAPI_Timer_DiffTimeFromNow(u32Mst6m10InitTimer1));
    }
//================================================================================
#if 0
void MDrv_Ursa_SetFrameLock(BOOLEAN flag)
{
    BYTE Value;
        MstarToolsDebug6MxxStart();

    sm_sRegImageU.uwAddr = reg_2A18MFC;
    sm_sRegImageU.bHigh = FALSE;
    Value = MDrv_Ursa_GetValue();
    if (flag)
        Value = (Value & 0xF7)|0x08;
    else
        Value = (Value & 0xF7);
    sm_sRegImageU.ucData = Value;
    MDrv_Ursa_SetValue();

        MstarToolsDebug6MxxEnd();

    #if 0

    BYTE Value;
    Value = MDrv_Ursa_Get_Value_8BitMode(reg_2A18,FALSE);
    if (flag)
        Value = (Value & 0xF7)|0x08;
    else
        Value = (Value & 0xF7);
    MDrv_Ursa_Set_Value(reg_2A18,FALSE,Value);
    #endif
}
#endif

U16 MDrv_Ursa_GetVersion(void)
{
        BOOLEAN bResult;// U8 u8Data;
        U16 wVersion=0xFF;
        MstarToolsDebug6MxxStart();

        if(1)
        {//Open 6M20
            U8 Reg207C_Low,Reg207C_High;
            sm_sRegImageU.uwAddr = reg_207CMFC;
            sm_sRegImageU.bHigh = FALSE;
            bResult = MDrv_Ursa_GetValue();
            Reg207C_Low=sm_sRegImageU.ucData;

            sm_sRegImageU.uwAddr = reg_207CMFC;
            sm_sRegImageU.bHigh = TRUE;
            bResult = MDrv_Ursa_GetValue();
            Reg207C_High=sm_sRegImageU.ucData;
            wVersion=(Reg207C_Low<<8)+Reg207C_High;
        }
        MstarToolsDebug6MxxEnd();
        return wVersion;

}

#else
U8 code aNoUse[1] = {0x00};
#endif // #if (ENABLE_URSA_MFC)

#undef DRV_URSAMFC_C

