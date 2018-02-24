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

#define _MSB1200_C_

#include "MsTypes.h"
#include "drvBDMA.h"
#include "MSB1200.h"
#include "drviic.h"
#include "msAPI_Tuner.h"
#include "msAPI_miu.h"
#include "msAPI_CI.h"
#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"

#define MSB1200_USE_HW_I2C
//#define MSB1200_VERIFY_TABLE
//#define MSB1200_LOAD_FW_FROM_CODE_MEMORY

#define DBG_MSB(x)          //x
#define DBG_GET_SIGNAL(x)     //     x
//#define MSB1200_CALIBRATE_ADC
//-----------------------------------------------------------------------

#if (FRONTEND_TUNER_TYPE == MSTAR_MSR1200_TUNER)
#define BIN_ID_MSB1200_DEMOD BIN_ID_MSB1200_MSR_2L
#elif  (FRONTEND_TUNER_TYPE == PHILIPS_FQD1216_TUNER)
#define BIN_ID_MSB1200_DEMOD BIN_ID_MSB1200_FQD
#elif  (FRONTEND_TUNER_TYPE == THOMSON_DTT75407_TUNER)
#define BIN_ID_MSB1200_DEMOD BIN_ID_MSB1200_THM
#else
#define BIN_ID_MSB1200_DEMOD BIN_ID_MSB1200_COM
#endif

#define MSB1200_PRE_VIT_PERIOD          (200000)
#define MSB1200_POST_VIT_PERIOD         ((1<<17)-1)

#define  GetU16(l_byte,h_byte)  (l_byte + (((U16)h_byte) << 8))
//-----------------------------------------------------------------------

typedef struct{
    U16 u16Addr;
    U8  u8Data;
}MSB1200_REG;
//-----------------------------------------------------------------------

#ifdef MSB1200_USE_HW_I2C
extern BOOLEAN IIC_GetByte(U8* pu8data);
extern BOOLEAN IIC_SendByte(U8 u8dat);
extern void IIC_NoAck(void);
#else
extern U8 IIC_GetByte (U16  bAck);
extern BOOLEAN IIC_SendByte(U8 u8dat);
extern BOOLEAN IIC_AccessStart(U8 ucSlaveAdr, U8 trans_t);
#endif
//-----------------------------------------------------------------------
static U8 u8MsbData[6];
static U8 gu8ChipRevId;
#ifdef MSB1200_LOAD_FW_FROM_CODE_MEMORY
code U8 MSB1200_table[] = {
    #include "MSB1200_demod.dat"
};
#endif

//extern unsigned char bCardAInside;
extern unsigned char bSETANTA;
extern unsigned char bNEOTNT;
//-----------------------------------------------------------------------
EN_TPS_HIERARCHY eHierarchy; // // kk 0320-1 0329
EN_TPS_CONSTELLATION eConstellation;
EN_TPS_HP_CODE eHPCodeRate;
EN_TPS_LP_CODE eLPCodeRate;
EN_TPS_MODEDET eTransMode;
EN_TPS_GUARD_INTV eGuardIntv;


/***********************************************************************************
  Subject:    Delay
  Function:   MSB1200_Delayms
  Parmeter:   delay_ms : millisecs for delay
  Return:     NONE
  Remark:
************************************************************************************/
static void    MSB1200_Delayms(U32 delay_ms)
{
    MsOS_DelayTask(delay_ms);
}
/***********************************************************************************
  Subject:    Write register
  Function:   MSB1200_WriteReg
  Parmeter:   u16Addr:   Register address
              u8Data:    Data to write
  Return:     BOOLEAN
  Remark:
************************************************************************************/
static BOOLEAN MSB1200_WriteReg(U16 u16Addr, U8 u8Data)
{
    u8MsbData[0] = DEMOD_ADDR_H;
    u8MsbData[1] = (u16Addr >> 8) & 0xff;
    u8MsbData[2] = u16Addr & 0xff;
    u8MsbData[3] = u8Data;
    return MDrv_IIC_WriteBytes(DEMOD_SLAVE_ID, 0, 0, 4, u8MsbData);
}
/***********************************************************************************
  Subject:    read register
  Function:   MSB1200_WriteReg
  Parmeter:   u16Addr:   Register address
              pu8Data:   pointer for return data
  Return:     BOOLEAN
  Remark:
************************************************************************************/
static BOOLEAN MSB1200_ReadReg(U16 u16Addr, U8 *pu8Data)
{
    u8MsbData[0] = DEMOD_ADDR_H;
    u8MsbData[1] = (u16Addr >> 8) & 0xff;
    u8MsbData[2] = u16Addr & 0xff;

    if (MDrv_IIC_WriteBytes(DEMOD_SLAVE_ID, 0, 0, 3, u8MsbData) == FALSE)
    {
        printf("read write fail----%x\n",DEMOD_SLAVE_ID);
        return FALSE;
    }

    u8MsbData[0] = DEMOD_READ_REG;

    return MDrv_IIC_ReadBytes(DEMOD_SLAVE_ID, 1, u8MsbData, 1, pu8Data);
}

static BOOLEAN MSB1200_WriteRaptor(U16 u16Addr, U8 u8Data)
{
    U8 u8Value;

    u8MsbData[0] = DEMOD_ADDR_H;
    u8MsbData[1] = 0x80;
    u8MsbData[2] = 0x28;
    u8MsbData[3] = (U8)(u16Addr>>8);
    u8MsbData[4] = (U8)(u16Addr&0xFF);
    u8MsbData[5] = u8Data;

    if(MDrv_IIC_WriteBytes(DEMOD_SLAVE_ID, 0, 0, 6, u8MsbData)==FALSE)
        return FALSE;

    if (MSB1200_ReadReg(0x802E, &u8Value)== FALSE)
        return FALSE;

    if (MSB1200_WriteReg(0x802E, u8Value|BIT3)== FALSE)
        return FALSE;

    MSB1200_Delayms(1);

    return TRUE;
}

static BOOLEAN MSB1200_ReadRaptor(U16 u16Addr, U8 *pu8Data)
{
    U8 u8Value;

    u8MsbData[0] = DEMOD_ADDR_H;
    u8MsbData[1] = 0x80;
    u8MsbData[2] = 0x28;
    u8MsbData[3] = (U8)(u16Addr>>8);
    u8MsbData[4] = (U8)(u16Addr&0xFF);

    if(MDrv_IIC_WriteBytes(DEMOD_SLAVE_ID, 0, 0, 5, u8MsbData)==FALSE)
        return FALSE;

    if (MSB1200_ReadReg(0x802E, &u8Value)== FALSE)
        return FALSE;

    if (MSB1200_WriteReg(0x802E, u8Value|BIT7)== FALSE)
        return FALSE;

    MSB1200_Delayms(1);

    if (MSB1200_ReadReg(0x802A, pu8Data)== FALSE)
        return FALSE;

    return TRUE;
}
//---------------------IIC Master Function --------------------------------------------------------------------
/***********************************************************************************
  Subject:    IIC Master Start
  Function:   MSB1200_IIC_Start
  Parmeter:   NONE
  Return:     NONE
  Remark:
************************************************************************************/
void MSB1200_IIC_Start()
{
    MSB1200_WriteReg(MSB1200_IIC_CONTROL, 0xC0);
}
/***********************************************************************************
  Subject:    IIC Master Stop
  Function:   MSB1200_IIC_Stop
  Parmeter:   NONE
  Return:     NONE
  Remark:
************************************************************************************/
void MSB1200_IIC_Stop()
{
    MSB1200_WriteReg(MSB1200_IIC_CONTROL, 0xA0);
}
/***********************************************************************************
  Subject:    IIC Master NoAck
  Function:   MSB1200_IIC_NoAck
  Parmeter:   NONE
  Return:     NONE
  Remark:
************************************************************************************/
void MSB1200_IIC_NoAck(void)
{
    MSB1200_WriteReg(MSB1200_IIC_CONTROL, 0x90);
}
/***********************************************************************************
  Subject:    IIC Master SendByte function
  Function:   MSB1200_IIC_SendByte
  Parmeter:   value
  Return:     NONE
  Remark:
************************************************************************************/
BOOLEAN MSB1200_IIC_SendByte(char value)
{
    U8 status;
    U8 i;

    MSB1200_WriteReg(MSB1200_IIC_WRITE_DATA, value);

    for ( i = 0; i < 5 ; i++)
    {
        MSB1200_ReadReg(MSB1200_IIC_STATUS, &status);
        if (status & 0x08)
        {
            // clear int bit
            MSB1200_WriteReg(MSB1200_IIC_STATUS, 0x04);

            //status = Read8_demod(MSB1200_IIC_CONTROL);
            /*
            if (status & 0x08)
            {
                return TRUE;
            }
            else
            {
                return FALSE;
            }
            */
            return TRUE;
        }
    }
    return FALSE;
}
/***********************************************************************************
  Subject:    IIC Master GetByte function
  Function:   MSB1200_IIC_GetByte
  Parmeter:   pu8data : pointer for return data
  Return:     NONE
  Remark:
************************************************************************************/
BOOLEAN MSB1200_IIC_GetByte(U8* pu8data)    // Auto generate ACK
{
    U8 u8read;
    U8 i;
    // trigger read
    MSB1200_ReadReg(MSB1200_IIC_READ_DATA, &u8read);

    for(i=0;i<3;i++)
    {
        MSB1200_ReadReg(MSB1200_IIC_STATUS, &u8read);
        if(u8read&0x8)
        {
            MSB1200_ReadReg(MSB1200_IIC_WRITE_DATA, pu8data);
            MSB1200_WriteReg(MSB1200_IIC_STATUS, 0x04);
            return TRUE;
        }
    }

    return FALSE;

}
/***********************************************************************************
  Subject:    IIC Master Write multi-bytes function
  Function:   MSB1200_IIC_WriteBytes
  Parmeter:
              u8SlaveID : slave address
              u8addrcount : Address counts
              pu8addr : pointer of array of address
              u16size : size of data
              pu8data : pointer for writing data.
  Return:     BOOLEAN
  Remark:
************************************************************************************/
BOOLEAN MSB1200_IIC_WriteBytes(U8 u8SlaveID, U8 u8addrcount, U8* pu8addr, U16 u16size, U8* pu8data)
{
    U16 i;

    MSB1200_IIC_Start();

    if(MSB1200_IIC_SendByte(u8SlaveID&0xFE)==FALSE)
        return FALSE;

    if(u8addrcount > 0)
    {
        for(i=0;i<u8addrcount;i++)
        {
            if(MSB1200_IIC_SendByte(pu8addr[i])==FALSE)
                return FALSE;
        }
    }

    for(i=0;i<u16size;i++)
    {

        if(MSB1200_IIC_SendByte(pu8data[i])==FALSE)
            return FALSE;
        //printf("Table[%d] = %x\n",(int)i, (int)pu8data[i]);

    }

    MSB1200_IIC_Stop();

    return TRUE;
}
/***********************************************************************************
  Subject:    IIC Master Read multi-bytes function
  Function:   MSB1200_IIC_ReadBytes
  Parmeter:
              u8SlaveID : slave address
              u8AddrNum : Address counts
              pu8addr : pointer of array of address
              u16size : size of data
              pu8data : pointer for return data.
  Return:     BOOLEAN
  Remark:
************************************************************************************/
BOOLEAN MSB1200_IIC_ReadBytes(U8 u8SlaveID, U8 u8AddrNum, U8* paddr, U16 u16size, U8* pu8data)
{
    U16 i;

    MSB1200_IIC_Start();

    if(MSB1200_IIC_SendByte(u8SlaveID&0xFE)==FALSE)
        return FALSE;

    if(u8AddrNum>0)
    {
        for(i=0;i<u8AddrNum;i++)
        {
            if(MSB1200_IIC_SendByte(*(paddr+i))==FALSE)
                return FALSE;
        }
    }

    if(u16size > 0)
    {
        MSB1200_IIC_Start();

        if(MSB1200_IIC_SendByte(u8SlaveID|0x1)==FALSE)
            return FALSE;

        for(i=0;i<u16size;i++)
        {
            if(i==(u16size-1))
                MSB1200_IIC_NoAck();

            if(MSB1200_IIC_GetByte(pu8data++)==FALSE)
            {
                return FALSE;
            }
        }
    }
    MSB1200_IIC_Stop();

    return TRUE;

}
code MSB1200_REG MSB1200_demod[] =
{
    {0xC408, 0xFF},// Interrupt enable
#if (FRONTEND_TUNER_TYPE == THOMSON_DTT75407_TUNER)
    {0xC430, 0x80},// ITB Freq IF=36MHz
    {0xC434, 0x30},// ITB Freq
#else
    {0xC430, 0x05},// ITB Freq IF=36.167MHz
    {0xC434, 0x31},// ITB Freq
#endif
    {0xC464, 0x30},// 256 FFT
    {0xC420, 0x28},// AGC target
    {0xC48C, 0x51},// Manual mean pilot
#if 0
#if 1 //For Reference
    {0x8526, 0x03},
    {0x8522, 0x00},
#else //For Production
    {0x8526, 0x04},
    {0x8522, 0x30},
#endif
#endif
    {0x802E, 0x20},// do simple FSM, if (REG_BASE[0xCC04] & 0x3) != 0x3) or ber > 2E-2 in 600ms, do demod reset
};

/***********************************************************************************
  Subject:    Reset
  Function:   MSB1200_Reset
  Parmeter:
  Return:     BOOLEAN
  Remark:
************************************************************************************/
BOOLEAN MSB1200_Reset ( void )
{

    MSB1200_WriteReg(0x8081, 0x01);
    MSB1200_WriteReg(0xCF0C, (gu8ChipRevId==0x04)?0x03:0x01);
    MSB1200_Delayms(3);
    MSB1200_WriteReg(0xCF0C, 0x00);
    MSB1200_WriteReg(0x8081, 0x00);

    return TRUE;
}
void WinMsGetByte(U32 addr, U8* dat)
{
    MDrv_Sys_SetXdataWindow1Base(addr>>12);
    *dat = XBYTE[0xF000+(addr&0x0FFF)];
}

/***********************************************************************************
  Subject:    Load DSP code to chip
  Function:   MSB1200_LoadDSPCode
  Parmeter:
  Return:     BOOLEAN
  Remark:
************************************************************************************/
static BOOLEAN MSB1200_LoadDSPCode(void)
{
    U16 i;
    BOOLEAN bResult;
#ifndef MSB1200_LOAD_FW_FROM_CODE_MEMORY
    BININFO BinInfo;
    U8 Data;
    S8 op;
    U16 W1BaseAddr;
    U32 srcaddr;
    U32 len;
    U32 SizeBy4K;
    U32 j;
#endif

    if (MSB1200_WriteReg(0x8081,0x1) == FALSE)// MCU SW reset
        return FALSE;

    if (MSB1200_WriteReg(0x8080,0x1) == FALSE)// Enable download from I2CS
        return FALSE;

    u8MsbData[0] = DEMOD_RAM_CONTROL;
    u8MsbData[1] = 0x01;
    if (MDrv_IIC_WriteBytes(DEMOD_SLAVE_ID, 0, NULL, 2, u8MsbData) == FALSE)// Enable SRAM write
        return FALSE;

    // load table

    IIC_Start();

    if(IIC_SendByte(DEMOD_SLAVE_ID&0xFE)==FALSE)
        return FALSE;

    u8MsbData[0] = DEMOD_ADDR_H;
    u8MsbData[1] = 0;
    u8MsbData[2] = 0;

    for(i=0;i<3;i++)
    {
        if(IIC_SendByte(u8MsbData[i])==FALSE)
            return FALSE;
    }
#ifdef MSB1200_LOAD_FW_FROM_CODE_MEMORY
    for(i=0;i<sizeof(MSB1200_table);i++)
    {
        if(IIC_SendByte(MSB1200_table[i])==FALSE)
            return FALSE;
    }
#else

    BinInfo.B_ID = BIN_ID_MSB1200_DEMOD;
      msAPI_MIU_Get_BinInfo(&BinInfo, &bResult);
    if ( bResult != PASS )
    {
        return FALSE;
    }
    //printf("\t GE_FRAMEBUFFER_ADR  =%08LX\n", ((GE_FRAMEBUFFER_MEMORY_TYPE & MIU1) ? (GE_FRAMEBUFFER_ADR | MIU_INTERVAL) : (GE_FRAMEBUFFER_ADR)));
    msAPI_MIU_Copy(BinInfo.B_FAddr, ((GE_FRAMEBUFFER_MEMORY_TYPE & MIU1) ? (GE_FRAMEBUFFER_ADR | MIU_INTERVAL) : (GE_FRAMEBUFFER_ADR)), MemAlign(BinInfo.B_Len, 8), MIU_FLASH2SDRAM);

    W1BaseAddr = MDrv_Sys_GetXdataWindow1Base();
    SizeBy4K=BinInfo.B_Len/0x1000;
   // printf("\t SizeBy4K  =%08LX\n", SizeBy4K);
    for (j=0;j<=SizeBy4K;j++)
    {
        if(j==SizeBy4K)
        len=BinInfo.B_Len%0x1000;
        else
        len=0x1000;

        srcaddr=((GE_FRAMEBUFFER_MEMORY_TYPE & MIU1) ? (GE_FRAMEBUFFER_ADR | MIU_INTERVAL) : (GE_FRAMEBUFFER_ADR))+(0x1000*j);
        //printf("\t j = %08LX\n", j);
        //printf("\t len = %08LX\n", len);
        op = 1;


        #if 0
        while(len--)
        {
            WinMsGetByte(srcaddr, &Data);
            //if(len<0x100)
            //printf("\t Data = %04X\n", Data);
            if(IIC_SendByte(Data)==FALSE)
            return FALSE;
            srcaddr += op;
        }
        #else
         MDrv_Sys_SetXdataWindow1Base(srcaddr>>12);
         while(len--)
         {
            Data = XBYTE[0xF000+(srcaddr&0x0FFF)];
            if(IIC_SendByte(Data)==FALSE)
            return FALSE;
            srcaddr += op;
            if ( (srcaddr & 0x0fff) == 0x0000 )
               MDrv_Sys_SetXdataWindow1Base(srcaddr>>12);
         }
        #endif
    }
    // Restore Window 1 Base Address
    MDrv_Sys_SetXdataWindow1Base(W1BaseAddr);
#endif
    IIC_Stop();

    u8MsbData[0] = DEMOD_RAM_CONTROL;
    u8MsbData[1] = 0x00;
    if (MDrv_IIC_WriteBytes(DEMOD_SLAVE_ID, 0, NULL, 2, u8MsbData) == FALSE) // Disable Ram write
        return FALSE;

    if (MSB1200_WriteReg(0x8080,0x0) == FALSE)// Disable download from I2CS
        return FALSE;

#ifdef  MSB1200_VERIFY_TABLE   // Verify table
    MSB1200_Delayms(100);
    if (MSB1200_WriteReg(0x8080, 0x02) == FALSE)     // Enable read SRAM from I2CS
        return FALSE;

    u8MsbData[0] = DEMOD_ADDR_H;
    u8MsbData[1] = 0;
    u8MsbData[2] = 0;

    if (MDrv_IIC_WriteBytes(DEMOD_SLAVE_ID, 0, 0, 3, u8MsbData) == FALSE)
    {
        return FALSE;
    }
#ifdef MSB1200_USE_HW_I2C

    IIC_Start();

    if(IIC_SendByte(DEMOD_SLAVE_ID)==FALSE)
        return FALSE;

    if(IIC_SendByte(DEMOD_READ_REG)==FALSE)
        return FALSE;

    IIC_Start();

    if(IIC_SendByte(DEMOD_SLAVE_ID|0x1)==FALSE)
        return FALSE;


    for(i=0;i<sizeof(MSB1200_table);i++)
    {
        if(i==(sizeof(MSB1200_table)-1))
            IIC_NoAck();

        if(IIC_GetByte(u8MsbData)==FALSE)
            return FALSE;

        if (u8MsbData[0] != MSB1200_table[i])
        {
            DBG_MSB(printf("Verify error[%d] %bx, %bx\n",i,u8MsbData[0], MSB1200_table[i]));
            break;
        }

    }

    IIC_Stop();
#else

    if (IIC_AccessStart(DEMOD_SLAVE_ID, 1) == FALSE)
        return FALSE;

    if (IIC_SendByte( DEMOD_READ_REG ) == FALSE)
        return FALSE;

    if (IIC_AccessStart(DEMOD_SLAVE_ID, 0) == FALSE)
        return FALSE;

    for(i=0;i<sizeof(MSB1200_table);i++)
    {
        if(i==(sizeof(MSB1200_table)-1))
            u8MsbData[0] = IIC_GetByte(0);
        else
            u8MsbData[0] = IIC_GetByte(1);

        if (u8MsbData[0] != MSB1200_table[i])
        {
            DBG_MSB(printf("Verify error[%d] %bx, %bx\n",i,u8MsbData[0], MSB1200_table[i]));
            break;
        }
    }

    IIC_Stop();
#endif

    if (MSB1200_WriteReg(0x8080,0x0) == FALSE) // Disable read SRAM from I2CS
        return FALSE;
#endif
    if (MSB1200_WriteReg(0x8081,0x0) == FALSE)// MCU SW reset
        return FALSE;

    return TRUE;


}
/***********************************************************************************
  Subject:    Power on initialized function
  Function:   MSB1200_Power_On_Initialization
  Parmeter:
  Return:     BOOLEAN
  Remark:
************************************************************************************/

BOOLEAN MSB1200_Power_On_Initialization ( void )
{

#if 1
    if (MSB1200_LoadDSPCode() == FALSE)
    {
        DBG_MSB(printf("MSB1200 Load DSP code fail\n"));
        return FALSE;
    }
    #if 1
    {
        U8 cData;
        MSB1200_ReadReg(0x8030, &cData);
        printf("\n%x ", (int)cData);
        MSB1200_ReadReg(0x8031, &cData);
        printf("%x\n", (int)cData);

    }
    #endif

    MSB1200_ReadReg(0x8000, &gu8ChipRevId);
    //printf("Phoenix RevID:%bx\n", gu8ChipRevId);

    //printf("\n>>MSB1200 ADC calibration\n");

    if(gu8ChipRevId == 0x04) //U05
        MSB1200_WriteReg(0x8526, 0x83);
    else
        MSB1200_WriteReg(0x8526, 0x03);

    MSB1200_WriteReg(0x8522, 0x00);

    MSB1200_WriteReg(0x802E, 0x10); //do ADC offset calibration
#endif

    return TRUE;
}

/************************************************************************************************
  Subject:    Bandwidth Programming
  Function:   MSB1200_BW_Programming
  Parmeter:   BW
          0 --> 6MHz Bandwidth
          1 --> 7MHz Bandwidth
          2 --> 8MHz Bandwidth
  Return:     BOOLEAN :
  Remark:
*************************************************************************************************/
BOOLEAN MSB1200_BW_Programming ( U8 BW )
{
    if (BW == E_RF_CH_BAND_6MHz )
    {
        if ( MSB1200_WriteReg(0xC46C,  0xB7) == FALSE )
        {
            return FALSE;
        }

        if ( MSB1200_WriteReg(0xC470,  0x55) == FALSE )
        {
            return FALSE;
        }
    }
    else if (BW == E_RF_CH_BAND_7MHz)
    {
        if ( MSB1200_WriteReg(0xC46C,  0x00) == FALSE )
        {
            return FALSE;
        }

        if ( MSB1200_WriteReg(0xC470,  0x64) == FALSE )
        {
            return FALSE;
        }
    }
    else if (BW == E_RF_CH_BAND_8MHz)
    {
        if ( MSB1200_WriteReg(0xC46C,  0x49) == FALSE )
        {
            return FALSE;
        }

        if ( MSB1200_WriteReg(0xC470,  0x72) == FALSE )
        {
            return FALSE;
        }
    }
    else
    {
        return FALSE;
    }

    DBG_MSB(printf("BW = %dMHz\n",(int) (BW+5)));

    return TRUE;
}
/************************************************************************************************
  Subject:    Transport stream serial/parallel control
  Function:   MSB1200_Serial_Control
  Parmeter:   bEnable : TRUE For serial
  Return:     BOOLEAN :
  Remark:
*************************************************************************************************/
BOOLEAN MSB1200_Serial_Control(BOOLEAN bEnable)
{
    U8 u8Reg;

#if TS_CLK_INV
    u8Reg = 0x02;
#else
    u8Reg = 0;
#endif

    if (bEnable)
    {
        u8Reg |= 0x01;
    }

    MSB1200_WriteReg(0xCF00,u8Reg);

    return TRUE;


}
/************************************************************************************************
  Subject:    channel change config
  Function:   MSB1200_Config
  Parmeter:   BW: bandwidth
  Return:     BOOLEAN :
  Remark:
*************************************************************************************************/
BOOLEAN MSB1200_Config ( U8 BW )
{
    U8 i;
    MSB1200_Reset();
    MSB1200_BW_Programming(BW);
    for ( i = 0 ; i < sizeof(MSB1200_demod)/sizeof(MSB1200_REG) ; i++)
    {
        if (MSB1200_WriteReg(MSB1200_demod[i].u16Addr,MSB1200_demod[i].u8Data) == FALSE)
        {
            DBG_MSB(printf("Init Fail: %d\n",i));
            return FALSE;
        }
    }

    return TRUE;
}
/************************************************************************************************
  Subject:    enable hw to lock channel
  Function:   MSB1200_Active
  Parmeter:   bEnable
  Return:     BOOLEAN
  Remark:
*************************************************************************************************/
BOOLEAN MSB1200_Active(BOOLEAN bEnable)
{
    U8 u8Reg;

    u8Reg = 0;
    if (bEnable)
    {
        u8Reg = 0x20;
    }
    MSB1200_WriteReg(0xC400, u8Reg);
    return TRUE;
}
/************************************************************************************************
  Subject:    Return lock status
  Function:   MSB1200_Lock
  Parmeter:   eStatus :
  Return:     BOOLEAN
  Remark:
*************************************************************************************************/
BOOLEAN MSB1200_Lock( COFDM_LOCK_STATUS eStatus )
{
    U16 u16Address;
    BYTE cData;
    BYTE cBitMask;
    U8  u8Temp;

    if(msAPI_CI_CardDetect()&& (EN_SMARTCARD_TYPE_SETANTA == msAPI_CI_GetCardType()))
    {
        MSB1200_WriteReg(0xCF0D, 0x22);
    }
    else if(msAPI_CI_CardDetect()&& (EN_SMARTCARD_TYPE_NEOTNT == msAPI_CI_GetCardType()))
    {

        MSB1200_WriteReg(0x8012, 0x02);//only 188 bytes

        if (MSB1200_ReadRaptor(MSB1200_TPS_RCVD_3_ADDR, &u8Temp) == FALSE)
        { return FALSE; }

        switch (u8Temp & 0x07)
        {
            case 0x03:  //5Y6
                MSB1200_WriteReg(0xCF0D, 0x89); //clock freq = 4.31MHz
                break;
            case 0x04:  //7Y8
                MSB1200_WriteReg(0xCF0D, 0x88); //clock freq = 4.55MHz ;  0x87: clock freq = 4.82MHz
                break;
            default:
                MSB1200_WriteReg(0xCF0D, 0x8A); //clock freq = 4.10MHz
        }
    }
    else
    {
        MSB1200_WriteReg(0x8012, 0x00);
        MSB1200_WriteReg(0xCF0D, 0x02);
    }

#if 0
    MSB1200_ReadReg(0xCC04, &cData);
    printf("0xCC04 = %x\n", (int)cData);
    MSB1200_ReadReg(0xC404, &cData);
    printf("0xC404 = %x\n", (int)cData);
#endif
    switch( eStatus )
    {
    case COFDM_FEC_LOCK:
        u16Address =  0xCC04; //FEC: DS Lock, sync Lock,
        cBitMask = BIT0 | BIT1;
        break;

    case COFDM_TPS_LOCK:
    #if 1
        u16Address =  0xCC64;
        cBitMask = BIT0;
    #else
        u16Address =  0xC404; // CHC tracking, TPS Locked, SYR Locked, AGC Locked
        cBitMask = BIT6;
    #endif
        break;

    case COFDM_SYMBOL_TIMING_LOCK:
        u16Address =  0xC404;
        cBitMask = BIT6;
        break;

    case COFDM_AGC_LOCK:
        u16Address =  0xC404;
        cBitMask = BIT4;
        break;

    case COFDM_DESCRAMBLER_LOCK:
        u16Address =  0xC404;
        cBitMask = BIT5;
        break;

    case COFDM_BYTE_ALIGNER_LOCK:
        u16Address =  0xC404;
        cBitMask = BIT7;
        break;

    default:
        return FALSE;
    }

    //if (MSB1200_ReadReg(u16Address, &cData) == FALSE)
    if (MSB1200_ReadRaptor(u16Address, &cData) == FALSE)
        return FALSE;

    if ((cData & cBitMask) == cBitMask)
    {
        return TRUE;
    }

    return FALSE;

}
#if 0

BOOLEAN MSB1200_GetPostViterbiBer(float *ber)
{
    U8 u8Temp;
    U16 u16Value;

    if (MSB1200_ReadReg(MSB1200_RS_FEC_INSTAT, &u8Temp) == FALSE)
    {
        return FALSE;
    }

    if (!(u8Temp & MSB1200_RS_INT_BER))
    {
        // still counting
        return FALSE;
    }

    if (MSB1200_ReadReg(MSB1200_RS_FEC_ERROR_ACC_H, &u8Temp) == FALSE)
    {
        return FALSE;
    }

    u16Value = ((U16)u8Temp)<<8;

    if (MSB1200_ReadReg(MSB1200_RS_FEC_ERROR_ACC_L, &u8Temp) == FALSE)
        return FALSE;

    if (MSB1200_WriteReg(MSB1200_RS_FEC_INSTAT, MSB1200_RS_INT_BER) == FALSE)
        return FALSE;

    u16Value += (U16)u8Temp;

    *ber = (float)u16Value/(MSB1200_POST_VIT_PERIOD*256);

    return TRUE;

}

BOOLEAN MSB1200_EnablePostViterbiBer(U8 flag)
{
    U8 u8Temp;
    if (flag)
    {
        if (MSB1200_WriteReg(MSB1200_RS_FEC_PERIOD_H, ((MSB1200_POST_VIT_PERIOD/8)>> 8)&0xff ) == FALSE)
            return FALSE;

        if (MSB1200_WriteReg(MSB1200_RS_FEC_PERIOD_L, (MSB1200_POST_VIT_PERIOD/8) & 0xff) == FALSE)
            return FALSE;

        if (MSB1200_WriteReg(MSB1200_RS_FEC_STAT, BIT3) == FALSE)
            return FALSE;

        if (MSB1200_ReadReg(MSB1200_RS_FEC_CTL, &u8Temp) == FALSE)
            return FALSE;

        if (MSB1200_WriteReg(MSB1200_RS_FEC_CTL, u8Temp|BIT5) == FALSE)
            return FALSE;

    }
    else
    {
        if (MSB1200_ReadReg(MSB1200_RS_FEC_CTL, &u8Temp) == FALSE)
            return FALSE;

        if (MSB1200_WriteReg(MSB1200_RS_FEC_CTL, u8Temp & ~BIT5) == FALSE)
            return FALSE;

    }
    return TRUE;

}
#else
/****************************************************************************
  Subject:    To get the Post viterbi BER
  Function:   MSB1200_GetPostViterbiBer
  Parmeter:  Quility
  Return:       E_RESULT_SUCCESS
                   E_RESULT_FAILURE =>Read I2C fail, MSB1200_VIT_STATUS_NG
  Remark:     For the Performance issue, here we just return the Post Value.(Not BER)
                   We will not read the Period, and have the "/256/8"
*****************************************************************************/
BOOLEAN MSB1200_GetPostViterbiBer(float *ber)
{
    static float fPreviousPostValue=0;

    U8  u8Temp;
    U16 u16Value;
    float fTemp1;

    //Read Post Status
    if (MSB1200_ReadRaptor(MSB1200_POST_VIT_STATUS_REG, &u8Temp) == FALSE)
    {
        printf("Fail:Return from MSB1200_ReadRaptor() function...\n ");
        return FALSE;
    }

    DBG_GET_SIGNAL(printf("MSB1200_GetPostViterbiBer(),Status = %d \n " , (int)u8Temp));

    if ((u8Temp == MSB1200_VIT_STATUS_BUSY)||(u8Temp == MSB1200_VIT_STATUS_NG))
    {
        //Return the previous value
           *ber = fPreviousPostValue;
    }
    else
    {
        // return the current value
        //Resd Post Value
        if (MSB1200_ReadRaptor(MSB1200_POST_VIT_VALUE_REG_BYTE1, &u8Temp) == FALSE)
        {
            printf("Fail:Return from MSB1200_ReadRaptor() function...\n ");
            return FALSE;
         }
        u16Value = u8Temp;
        if (MSB1200_ReadRaptor(MSB1200_POST_VIT_VALUE_REG_BYTE0, &u8Temp) == FALSE)
        {
            printf("Fail:Return from MSB1200_ReadRaptor() function...\n ");
            return FALSE;
         }

        u16Value = (u16Value<<8) | u8Temp;
        fTemp1 = (float)u16Value;

        //Update static pre-value
        fPreviousPostValue = fTemp1;
        //Update result
        *ber = fTemp1;
    }

    DBG_GET_SIGNAL(printf("MSB1200_GetPostViterbiBer(),PostViterbiBer Value = %f \n ",fTemp1));

    return TRUE;
}

FUNCTION_RESULT MSB1200_GetSignal_AGC( WORD *AgcifGain ) // kk 0320-1 0403
{
    BYTE    cData;
    WORD    wAgcValue;

    if ( FALSE == MSB1200_ReadRaptor( 0x28,  &cData ) )
    {
        DBG_MSB( printf( "I2C Error!!! AGC Check - Address 0x28\n" ) );
        return E_RESULT_FAILURE;
    }
    wAgcValue = cData & 0x03;
    wAgcValue = wAgcValue << 8;

    if ( FALSE == MSB1200_ReadRaptor( 0x24,  &cData ) )
    {
        DBG_MSB( printf( "I2C Error!!! AGC Check - Address 0x24\n" ) );
        return E_RESULT_FAILURE;
    }
    wAgcValue += cData;

    *AgcifGain = ( WORD )( wAgcValue);

    return E_RESULT_SUCCESS;
}


/****************************************************************************
  Subject:    To get the Post viterbi BER
  Function:   MSB1200_GetPostViterbiBer
  Parmeter:  Quility
  Return:       TRUE
                   FALSE =>Read I2C fail, MSB1200_VIT_STATUS_NG
  Remark:
*****************************************************************************/
BOOLEAN MSB1200_GetPostViterbiBer_BK(float *ber) // kk 0320-1 0329
{
    static float fPreviousPostValue=0;
    U8  u8Temp;
    U16 u16Value;
    float fTemp1;
    U32 u32Value;
    float fTemp2;

    //Read Post Status
    if (MSB1200_ReadRaptor(MSB1200_POST_VIT_STATUS_REG, &u8Temp) == FALSE)
    {
        DBG_GET_SIGNAL(printf("Fail:Return from MSB1200_ReadRaptor() function...\n "));
        return FALSE;
     }

    DBG_GET_SIGNAL(printf("MSB1200_GetPostViterbiBer(),Status = %d \n " , (int)u8Temp));

    if ((u8Temp == MSB1200_VIT_STATUS_BUSY)|(u8Temp == MSB1200_VIT_STATUS_NG))
    {//Return the previous value
       *ber = fPreviousPostValue;
    }
    else
    {// return the current value
        //Read Post Value
        if (MSB1200_ReadRaptor(MSB1200_POST_VIT_VALUE_REG_BYTE1, &u8Temp) == FALSE)
        {
            DBG_GET_SIGNAL(printf("Fail:Return from MSB1200_ReadRaptor() function...\n "));
            return FALSE;
         }
        u16Value = u8Temp;
        if (MSB1200_ReadRaptor(MSB1200_POST_VIT_VALUE_REG_BYTE0, &u8Temp) == FALSE)
        {
            DBG_GET_SIGNAL(printf("Fail:Return from MSB1200_ReadRaptor() function...\n "));
            return FALSE;
         }
        u16Value = (u16Value<<8) | u8Temp;
        fTemp1 = (float)u16Value;

        //Read Post-Vit Count Period
        if (MSB1200_ReadRaptor(MSB1200_POST_VIT_PERIOD_REG_BYTE2, &u8Temp) == FALSE)
        {
            DBG_GET_SIGNAL(printf("Fail:Return from MSB1200_ReadRaptor() function...\n "));
            return FALSE;
        }
        u32Value = (U32)u8Temp<<16;

        if (MSB1200_ReadRaptor(MSB1200_POST_VIT_PERIOD_REG_BYTE1, &u8Temp) == FALSE)
        {
            DBG_GET_SIGNAL(printf("Fail:Return from MSB1200_ReadRaptor() function...\n "));
            return FALSE;
         }
        u32Value |= (U32)u8Temp<<8;

        if (MSB1200_ReadRaptor(MSB1200_POST_VIT_PERIOD_REG_BYTE0, &u8Temp) == FALSE)
        {
            DBG_GET_SIGNAL(printf("Fail:Return from MSB1200_ReadRaptor() function...\n "));
            return FALSE;
        }
        u32Value |= (U32)u8Temp;
        fTemp2 = (float)u32Value;

        //Update static pre-value
        fPreviousPostValue = (fTemp1/fTemp2)/2048;
        //Update result
        *ber = fPreviousPostValue;
    }

    DBG_GET_SIGNAL(printf("MSB1200_GetPostViterbiBer(),PostViterbiBer Value = %f \n ",fTemp1));

    return TRUE;
}

#endif

/************************************************************************************************
  Subject:    Write data to tuner
  Function:   MSB1200_Tuner_Programming
  Parmeter:   pu8Data : pointer for writing data
  Return:     BOOLEAN
  Remark:
*************************************************************************************************/
BOOLEAN MSB1200_Tuner_Programming(U8 *pu8Data)
{
#if 0
    if (MSB1200_IIC_WriteBytes(*pu8Data, 0, 0, 4, pu8Data+1) == FALSE)
    {
        DBG_MSB(printf("Write Tuner Fail\n"));
    }
    return TRUE;
#else
    //programming register 0x8028,0x8029,0x802A,0x802B,0x802C

    DBG_MSB(printf("Tuner go:0x%bx",*pu8Data));
    MSB1200_WriteReg(0x8028, *pu8Data++);
    DBG_MSB(printf(",0x%bx",*pu8Data));
    MSB1200_WriteReg(0x8029, *pu8Data++);
    DBG_MSB(printf(",0x%bx",*pu8Data));
    MSB1200_WriteReg(0x802A, *pu8Data++);
    DBG_MSB(printf(",0x%bx",*pu8Data));
    MSB1200_WriteReg(0x802B, *pu8Data++);
    DBG_MSB(printf(",0x%bx",*pu8Data));
    MSB1200_WriteReg(0x802C, *pu8Data++);
    DBG_MSB(printf("\n"));


    // Tuner go
    MSB1200_WriteReg(0x802E, 0x01);
    MSB1200_Delayms(5);

    return TRUE;
#endif
}

/************************************************************************************************
  Subject:    Write data to tuner for 5 bytes
  Function:   MSB1200_Tuner_Programming
  Parmeter:   pu8Data : pointer for writing data
  Return:     BOOLEAN
  Remark:
*************************************************************************************************/
BOOLEAN MSB1200_Tuner_Programming5Bytes(U8 *pu8Data)
{
#if 0
    if (MSB1200_IIC_WriteBytes(*pu8Data, 0, 0, 4, pu8Data+1) == FALSE)
    {
        DBG_MSB(printf("Write Tuner Fail\n"));
    }
    return TRUE;
#else
    //programming register 0x8028,0x8029,0x802A,0x802B,0x802C

    DBG_MSB(printf("Tuner go:0x%bx",*pu8Data));
    MSB1200_WriteReg(0x8028, *pu8Data++);
    DBG_MSB(printf(",0x%bx",*pu8Data));
    MSB1200_WriteReg(0x8029, *pu8Data++);
    DBG_MSB(printf(",0x%bx",*pu8Data));
    MSB1200_WriteReg(0x802A, *pu8Data++);
    DBG_MSB(printf(",0x%bx",*pu8Data));
    MSB1200_WriteReg(0x802B, *pu8Data++);
    DBG_MSB(printf(",0x%bx",*pu8Data));
    MSB1200_WriteReg(0x802C, *pu8Data++);
    DBG_MSB(printf(",0x%bx",*pu8Data));
    MSB1200_WriteReg(0x802D, *pu8Data++);
    DBG_MSB(printf("\n"));


    // Tuner go
    MSB1200_WriteReg(0x802E, 0x03);
    MSB1200_Delayms(5);

    return TRUE;
#endif
}
/****************************************************************************
  Subject:    Read the signal to noise ratio (SNR)
  Function:   MSB1200_GetSNR
  Parmeter:   None
  Return:     -1 mean I2C fail, otherwise I2C success then return SNR value
  Remark:
*****************************************************************************/
float MSB1200_GetSNR (void)
{
    U8 RegSNR;

    if ( MSB1200_ReadRaptor(0xC490, &RegSNR) == FALSE )
    {
        return -1;
    }
    //*snr = ( float ) RegSNR * 0.125;//RegSNR/255 * 100 (%)
    return ( float ) RegSNR * 0.125;
}

U8 MSB1200_Tuner_ReadBytes(U8 u8SlaveID, U8 u8Addr)
{
    U8 value;
    MSB1200_WriteReg(0x8028, u8SlaveID);
    MSB1200_WriteReg(0x8029, u8Addr);
    MSB1200_WriteReg(0x802E, BIT6);
    MSB1200_Delayms(100);

    MSB1200_ReadReg(0x802B, &value);

    return value;

}

FUNCTION_RESULT MSB1200_GetSignalStrength(WORD *strength) // kk 0320-1 0403
{
    WORD    wagc;
    WORD    wArrangedStrength;

    if ( E_RESULT_FAILURE == MSB1200_GetSignal_AGC( &wagc ) )
    {
        DBG_MSB( printf( "\n[SignalStrength] Check Error!!\n" ) );
        return E_RESULT_FAILURE;
    }
    else
    {
        if ( TRUE == MSB1200_Lock( COFDM_FEC_LOCK ) )
        {
            if ( wagc < 500 )  // -7dbm  100
            {
                wArrangedStrength = 100;
            }
            else if ( wagc < 600 )  // -52dbm  90 ~ 99
            {
                wArrangedStrength = 99 - ( ( wagc - 500 ) / 10 );
            }
            else if ( wagc < 700 )  // -61dbm   70 ~ 89
            {
                wArrangedStrength = 89 - ( ( wagc - 600 ) / 10 );
            }
            else if ( wagc < 800 )  // -72dbm  30 ~ 69
            {
                wArrangedStrength = 69 - ( ( wagc - 700 ) / 5 );
            }
            else if ( wagc < 950 )  // -74dbm  10 ~  29
            {
                wArrangedStrength = 39 - ( ( wagc - 800 ) / 5 );
            }
            else
            {
                wArrangedStrength = 10;
            }
        }
        else
        {
            wArrangedStrength = 0;
            DBG_MSB( printf( " FEC Lock Fail!! \n" ) );
        }
        DBG_MSB( printf( "[cofdmGetSignalStrength] AGC:0x%x \n", wagc ) );

        *strength = wArrangedStrength;
    }

    return E_RESULT_SUCCESS;
}

/****************************************************************************
  Subject:    To get the DVT Signal quility
  Function:   MSB1200_GetSignalQuality
  Parmeter:  Quility
  Return:      E_RESULT_SUCCESS
                   E_RESULT_FAILURE
  Remark:    Here we have 4 level range
                  <1>.First Range => Quility =100  (You can define it by MSB1200_SIGNAL_BASE_100)
                  <2>.2th Range => 60 < Quility < 100 (You can define it by MSB1200_SIGNAL_BASE_60)
                  <3>.3th Range => 10 < Quility < 60  (You can define it by MSB1200_SIGNAL_BASE_10)
                  <4>.4th Range => Quility <10
*****************************************************************************/
FUNCTION_RESULT MSB1200_GetSignalQuality(WORD *quality)
{
    float fber, fTemp;
    U16 u16Cal_Quality;
    U8 u8ArrangedQuality;

    if (TRUE == MSB1200_Lock(COFDM_FEC_LOCK) )
    {
        if (MSB1200_GetPostViterbiBer(&fber)==FALSE)
        {
            printf("Fail:Return from MSB1200_ReadRaptor() function...\n ");
            return E_RESULT_FAILURE;
        }

        //Just use the high byte
        u16Cal_Quality = (U16)fber;
        DBG_GET_SIGNAL(printf("Get PostViterbi Ber Value = 0x%x \n ",u16Cal_Quality));
        u16Cal_Quality = u16Cal_Quality >> 8;

        if (u16Cal_Quality <= MSB1200_SIGNAL_BASE_100 ) // 100
        {
            u8ArrangedQuality = 100;
        }
        else  if ( u16Cal_Quality < MSB1200_SIGNAL_BASE_60 ) // 30 ~ 99
                {
                    fTemp = (MSB1200_SIGNAL_BASE_60-u16Cal_Quality);
                    fTemp/=(MSB1200_SIGNAL_BASE_60-MSB1200_SIGNAL_BASE_100);
                    u8ArrangedQuality = 60 + (fTemp * (100-60));
                }
                else  if ( u16Cal_Quality < MSB1200_SIGNAL_BASE_10 )   // 10 ~ 30
                        {
                            fTemp = (MSB1200_SIGNAL_BASE_10-u16Cal_Quality);
                            fTemp/=(MSB1200_SIGNAL_BASE_10-MSB1200_SIGNAL_BASE_60);
                            u8ArrangedQuality = 10+ (fTemp * (60-10));
                        }
                        else
                        {
                            u8ArrangedQuality = 10;
                        }

        *quality=u8ArrangedQuality;
        DBG_GET_SIGNAL(printf("Gignal Quility = %d \n ", (int)u8ArrangedQuality));
        return E_RESULT_SUCCESS;
    }
    else
    {
        *quality=0;
        //fPreviousPostValue=0;
        DBG_GET_SIGNAL(printf("MSB1200 unlock, Signal Quility = 0 \n "));
        return E_RESULT_SUCCESS;
    }
}

#if (FRONTEND_TUNER_TYPE == MSTAR_MSR1200_TUNER)
void MSB1200_SetFreq(U32 freq)
{
    unsigned char CONFIG[6];

    CONFIG[0] = 0x00;    //dummy byte
    CONFIG[1] = (U8) (freq >> 24);
    CONFIG[2] = (U8) (freq >> 16);
    CONFIG[3] = (U8) (freq >> 8);
    CONFIG[4] = (U8) freq;

    //programming register 0x8028,0x8029,0x802A,0x802B,0x802C

    DBG_MSB(printf("msb1200 freq:0x%bx", CONFIG[0]));
    MSB1200_WriteReg(0x8028, CONFIG[0]);
    DBG_MSB(printf(",0x%bx", CONFIG[1]));
    MSB1200_WriteReg(0x8029, CONFIG[1]);
    DBG_MSB(printf(",0x%bx", CONFIG[2]));
    MSB1200_WriteReg(0x802A, CONFIG[2]);
    DBG_MSB(printf(",0x%bx", CONFIG[3]));
    MSB1200_WriteReg(0x802B, CONFIG[3]);
    DBG_MSB(printf(",0x%bx", CONFIG[4]));
    MSB1200_WriteReg(0x802C, CONFIG[4]);
    DBG_MSB(printf("\n"));

    // Tuner go
    MSB1200_WriteReg(0x802E, 0x01);
    MSB1200_Delayms(5);

}
#endif

void MSB1200_Power_ON_OFF(bPowerOn)
{
    if (bPowerOn)
    {
        MSB1200_WriteReg(0x8C1B, 0);// auto AGC
    }
    else
    {
        MSB1200_WriteReg(0x8C1A, 0);
        MSB1200_WriteReg(0x8C19, 0x80);
        MSB1200_WriteReg(0x8C1B, 2);

        MSB1200_WriteReg(0x802E, 0);
    }
}

BOOLEAN MSB1200_TSTurnOff()
{
    U8 temp;
    MSB1200_ReadReg(0x803F,&temp);
    temp=temp & 0x7F;
    MSB1200_WriteReg(0x803F,temp);
    return 1 ;
}


BOOLEAN MSB1200_TSTurnOn()
{
    U8 temp;
    MSB1200_ReadReg(0x803F,&temp);
    temp=temp | 0x80;
    MSB1200_WriteReg(0x803F,temp);
    return 1;
}




BOOLEAN MSB1200_Power_Save(void)
{
//    U8 value, i = 0;

//    MSB1200_WriteReg(0x8042, 0x00);
//    do {
//        MSB1200_ReadReg(0x801b, &value);
//    }while ((i++ < 128) && (value != 0x01));
//    if (value != 0x01)
//        return FALSE;
    MSB1200_WriteReg(0x8801, 0x01);
    MSB1200_WriteReg(0x8710, 0x07);
    MSB1200_WriteReg(0x8711, 0x10);
    MSB1200_WriteReg(0x8700, 0xAF);
    MSB1200_WriteReg(0x8701, 0xFF);
    MSB1200_WriteReg(0x8702, 0x84);
    MSB1200_WriteReg(0x8703, 0x00);
    MSB1200_WriteReg(0x872A, 0x00);
    MSB1200_WriteReg(0x872B, 0x40);
    MSB1200_WriteReg(0x801a, 0x01);
    MSB1200_WriteReg(0x8043, 0x8E);
    MSB1200_WriteReg(0x8044, 0x9f);
    MSB1200_WriteReg(0x8016, 0x00);
    MSB1200_WriteReg(0x8527, 0x60);
    MSB1200_WriteReg(0x8503, 0x04);
    MSB1200_WriteReg(0x8507, 0x04);
    MSB1200_WriteReg(0x8520, 0x70);
    MSB1200_WriteReg(0x852A, 0x08);
    MSB1200_WriteReg(0x8013, 0x15);
    MSB1200_WriteReg(0x8040, 0x01);
    return TRUE;
}

BOOLEAN MSB1200_GetTpsInfo(void) // kk 0320-1 0329
{
    U8  u8Temp;

    if (MSB1200_ReadRaptor(MSB1200_COR_STAT_ADDR, &u8Temp) == FALSE)
    { return FALSE; }

    if ((u8Temp&0x40) != 0x40)
    {    //TPS unlock
        eHierarchy = INVALID_HIER;
        eConstellation = INVALID_CNSL;
        eHPCodeRate = INVALID_HP;
        eLPCodeRate = INVALID_LP;
        eTransMode = INVALID_MODE;
        eGuardIntv = INVALID_GI;
    }
    else
    {
        if (MSB1200_ReadRaptor(MSB1200_TPS_RCVD_2_ADDR, &u8Temp) == FALSE)
        { return FALSE; }

        switch (u8Temp & 0x03)
        {
            case 0x00:
                eConstellation = QPSK;         break;
            case 0x01:
                eConstellation = QAM_16;     break;
            case 0x02:
                eConstellation = QAM_64;     break;
            default:
                eConstellation = INVALID_CNSL;
        }

        switch (u8Temp & 0x70)
        {
            case 0x00:
                eHierarchy = NON_HIER;        break;
            case 0x10:
                eHierarchy = ALPHA_1;        break;
            case 0x20:
                eHierarchy = ALPHA_2;        break;
            case 0x30:
                eHierarchy = ALPHA_4;        break;
            default:
                eHierarchy = INVALID_HIER;
        }

        if (MSB1200_ReadRaptor(MSB1200_TPS_RCVD_3_ADDR, &u8Temp) == FALSE)
        { return FALSE; }

        switch (u8Temp & 0x07)
        {
            case 0x00:
                eHPCodeRate = HP_1Y2;        break;
            case 0x01:
                eHPCodeRate = HP_2Y3;        break;
            case 0x02:
                eHPCodeRate = HP_3Y4;        break;
            case 0x03:
                eHPCodeRate = HP_5Y6;        break;
            case 0x04:
                eHPCodeRate = HP_7Y8;        break;
            default:
                eHPCodeRate = INVALID_HP;
        }

        switch (u8Temp & 0x70)
        {
            case 0x00:
                eLPCodeRate = LP_1Y2;        break;
            case 0x10:
                eLPCodeRate = LP_2Y3;        break;
            case 0x20:
                eLPCodeRate = LP_3Y4;        break;
            case 0x30:
                eLPCodeRate = LP_5Y6;        break;
            case 0x40:
                eLPCodeRate = LP_7Y8;        break;
            default:
                eLPCodeRate = INVALID_LP;
        }

        if (MSB1200_ReadRaptor(MSB1200_TPS_RCVD_4_ADDR, &u8Temp) == FALSE)
        { return FALSE; }

        switch (u8Temp & 0x03)
        {
            case 0x00:
                eTransMode = MODE_2K;        break;
            case 0x01:
                eTransMode = MODE_8K;        break;
            default:
                eTransMode = INVALID_MODE;
        }

        switch (u8Temp & 0x30)
        {
            case 0x00:
                eGuardIntv = GI_1Y32;        break;
            case 0x10:
                eGuardIntv = GI_1Y16;        break;
            case 0x20:
                eGuardIntv = GI_1Y8;        break;
            case 0x30:
                eGuardIntv = GI_1Y4;        break;
            default:
                eGuardIntv = INVALID_GI;
        }
    }

    return TRUE;
}

/****************************************************************************
  Subject:    To get the DVB-T TPS Cell ID
  Function:   MSB1200_Get_CELL_ID
  Parmeter:   cell_id
  Return:     BOOLEAN
  Remark:
*****************************************************************************/
BOOLEAN MSB1200_Get_CELL_ID(WORD *cell_id)
{
    U8 value1, value2;

    if (MSB1200_ReadReg(0xC518, &value1) == FALSE) //TPS Cell ID [15:8]
        return FALSE;
    if (MSB1200_ReadReg(0xC514, &value2) == FALSE) //TPS Cell ID [7:0]
        return FALSE;

    *cell_id = ((WORD)value1<<8)|value2;

    return TRUE;
}

BOOLEAN MSB1200_GetFrequencyOffset(float *pFreqOff, U8 u8BW)
{
    U8 u8Mode;
    //U8 u8BW; //8MHz=>8, 7MHz=7, 6MHz=6
    U8 u8Temp;
    S32 s32FreqOff;

    // frozon register
    MSB1200_WriteReg(0xC4D0, 0x01);

    MSB1200_ReadReg(0xC488, &u8Temp);
    s32FreqOff = u8Temp;
    s32FreqOff <<= 8;
    MSB1200_ReadReg(0xC484, &u8Temp);
    s32FreqOff += u8Temp;
    s32FreqOff <<= 8;
    MSB1200_ReadReg(0xC480, &u8Temp);
    s32FreqOff += u8Temp;

    // un-frozon register
    MSB1200_WriteReg(0xC4D0, 0x00);

    //Process 24-bit two's complement number
    if(s32FreqOff >= 0x800000)
        s32FreqOff = s32FreqOff - 0x1000000;

    // Read Mode
    MSB1200_ReadReg(0xC4A8, &u8Mode);
    u8Mode &= 0x03; //2K:0, 8K: 1

    // Calculate frequency offset in KHz
    *pFreqOff = ((float)s32FreqOff*64000*(float)u8BW)/16384/7/2048/(1+(3*u8Mode))/8;

    DBG_MSB(printf("Freq offset=%.2f\n", *pFreqOff));

    // Read Tuner offset
    MSB1200_ReadRaptor(0xCC60, &u8Temp);
    DBG_MSB(printf("Tuner offset=%bd\n", (S8)u8Temp));

    if(u8Temp!=0)
        *pFreqOff -= (S8)u8Temp*166.67;

    DBG_MSB(printf("Total Frequency offset=%.2f KHz\n", *pFreqOff));

    return TRUE;
}

//For check if MSB1200's 51 is still alive
BOOLEAN MSB1200_IsAlive(void)
{
    U8 u8Value;

    u8MsbData[0] = DEMOD_ADDR_H;
    u8MsbData[1] = 0x80;
    u8MsbData[2] = 0x28;
    u8MsbData[3] = 0xC4; //0x8028
    u8MsbData[4] = 0x00; //0x8029
    u8MsbData[5] = 0xFF; //0x802A

    if(MDrv_IIC_WriteBytes(DEMOD_SLAVE_ID, 0, 0, 5, u8MsbData)==FALSE)
        return FALSE;

    if (MSB1200_ReadReg(0x802E, &u8Value)== FALSE)
        return FALSE;

    if (MSB1200_WriteReg(0x802E, u8Value|BIT7)== FALSE)
        return FALSE;

    MSB1200_Delayms(1);

    if (MSB1200_ReadReg(0x802A, &u8Value)== FALSE)
        return FALSE;


    if(u8Value != 0xFF)
        return TRUE;
    else
        return FALSE;
}

#if 1 //for debug purpose
void MSB1200_DumpReg(void)
{
    U8  i;
    U8  u8RegValue;
    U16 j;
    U16 u16RegAddr;

    U16 u16Bank[] = {0x8000, 0x8200, 0x8400, 0x8500,
                     0x8600, 0x8700, 0x8800, 0x8A00,
                     0x8B00, 0x8C00, 0x8D00, 0xC000,
                     0xC400, 0xC800, 0xCC00, 0xCF00};

    for(i=0; i<sizeof(u16Bank)/sizeof(U16); i++)
    {
        printf("---0x%X---\n", u16Bank[i]);

        printf("    ");
        for(j=0; j<16; j++)
            printf("%02X ", j);

        for(j=0; j<256; j++)
        {
            if((u16Bank[i]>=0xC000) && (u16Bank[i]<0xCF00))
                u16RegAddr = u16Bank[i] + j*4;
            else
                u16RegAddr = u16Bank[i] + j;

            MSB1200_ReadReg(u16RegAddr, &u8RegValue);

            if((j%16)==0)
                printf("\n%02X: ", (j&0xF0));

            printf("%02bX ", u8RegValue);
        }
        printf("\n");
        MDrv_Sys_ClearWatchDog();
    }

}
#endif

#undef _MSB1200_C_

