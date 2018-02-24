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
/// @file MSB1210.c
/// @brief MSB1210 DVBT, VIF Controller Interface
/// @author MStar Semiconductor, Inc.
//
////////////////////////////////////////////////////////////////////////////////

#define _MSB1210_C_
#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"

#include "MsTypes.h"
#include "drvBDMA.h"
#include "drvIIC.h"
#include "msAPI_Tuner.h"
#include "msAPI_MIU.h"
#include "BinInfo.h"
#include "halVif.h"
#include "msAPI_Memory.h"

#if (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)
#include "MsVIF_MSB1210.h"
#endif
#include "MSB1210.h"
#ifdef SUPPORT_AP_BIN_IN_FLASH_2
#include "InfoBlock.h"
#endif
//#define MSB1210_USE_HW_I2C

#define DBG_MSB(x)        //  x
#define DBG_GET_SIGNAL(x)  // x
#define DBG_DUMP_LOAD_DSP_TIME 0

//-----------------------------------------------------------------------
#define BIN_ID_MSB1210_DEMOD BIN_ID_MSB1210

//-----------------------------------------------------------------------
#ifdef MSB1210_USE_HW_I2C
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
U8 gCalIdacCh0, gCalIdacCh1;
S_CMDPKTREG gsCmdPacket;

#ifdef MSB1210_LOAD_FW_FROM_CODE_MEMORY
code U8 MSB1210_table[] = {
    #include "MSB1210_demod.dat"
};
#endif
U8 gu8DemoDynamicI2cAddress=0x32;//Default
static BOOL     FECLock;
#if (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)
extern U8  gMSB1210ATVMode;
#endif
extern BOOL IIC_Start(void);
extern void IIC_Stop(void);

extern void * msAPI_Memory_Allocate(U16 u16Number_of_bytes,EN_BUFFER_ID enBufID);
extern U8 msAPI_Memory_Free(void *pFree, EN_BUFFER_ID enBufID);


/***********************************************************************************
  Subject:    Delay
  Function:   MSB1210_Delayms
  Parmeter:   delay_ms : millisecs for delay
  Return:     NONE
  Remark:
************************************************************************************/
static void    MSB1210_Delayms(U32 delay_ms)
{
    MsOS_DelayTask(delay_ms);
}

#if 0
//---------------------IIC Master Function --------------------------------------------------------------------
/***********************************************************************************
  Subject:    IIC Master Start
  Function:   MSB1210_IIC_Start
  Parmeter:   NONE
  Return:     NONE
  Remark:
************************************************************************************/
void MSB1210_IIC_Start()
{
    MSB1210_WriteReg(MSB1210_IIC_CONTROL, 0xC0);
}
/***********************************************************************************
  Subject:    IIC Master Stop
  Function:   MSB1210_IIC_Stop
  Parmeter:   NONE
  Return:     NONE
  Remark:
************************************************************************************/
void MSB1210_IIC_Stop()
{
    MSB1210_WriteReg(MSB1210_IIC_CONTROL, 0xA0);
}
/***********************************************************************************
  Subject:    IIC Master NoAck
  Function:   MSB1210_IIC_NoAck
  Parmeter:   NONE
  Return:     NONE
  Remark:
************************************************************************************/
void MSB1210_IIC_NoAck(void)
{
    MSB1210_WriteReg(MSB1210_IIC_CONTROL, 0x90);
}
/***********************************************************************************
  Subject:    IIC Master SendByte function
  Function:   MSB1210_IIC_SendByte
  Parmeter:   value
  Return:     NONE
  Remark:
************************************************************************************/
BOOLEAN MSB1210_IIC_SendByte(char value)
{
    U8 status;
    U8 i;

    MSB1210_WriteReg(MSB1210_IIC_WRITE_DATA, value);

    for ( i = 0; i < 5 ; i++)
    {
        MSB1210_ReadReg(MSB1210_IIC_STATUS, &status);
        if (status & 0x08)
        {
            // clear int bit
            MSB1210_WriteReg(MSB1210_IIC_STATUS, 0x04);

            //status = Read8_demod(MSB1210_IIC_CONTROL);
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
  Function:   MSB1210_IIC_GetByte
  Parmeter:   pu8data : pointer for return data
  Return:     NONE
  Remark:
************************************************************************************/
BOOLEAN MSB1210_IIC_GetByte(U8* pu8data)    // Auto generate ACK
{
    U8 u8read;
    U8 i;
    // trigger read
    MSB1210_ReadReg(MSB1210_IIC_READ_DATA, &u8read);

    for(i=0;i<3;i++)
    {
        MSB1210_ReadReg(MSB1210_IIC_STATUS, &u8read);
        if(u8read&0x8)
        {
            MSB1210_ReadReg(MSB1210_IIC_WRITE_DATA, pu8data);
            MSB1210_WriteReg(MSB1210_IIC_STATUS, 0x04);
            return TRUE;
        }
    }

    return FALSE;

}
/***********************************************************************************
  Subject:    IIC Master Write multi-bytes function
  Function:   MSB1210_IIC_WriteBytes
  Parmeter:
              u8SlaveID : slave address
              u8addrcount : Address counts
              pu8addr : pointer of array of address
              u16size : size of data
              pu8data : pointer for writing data.
  Return:     BOOLEAN
  Remark:
************************************************************************************/
BOOLEAN MSB1210_IIC_WriteBytes(U8 u8SlaveID, U8 u8addrcount, U8* pu8addr, U16 u16size, U8* pu8data)
{
    U16 i;

    MSB1210_IIC_Start();

    if(MSB1210_IIC_SendByte(u8SlaveID&0xFE)==FALSE)
        return FALSE;

    if(u8addrcount > 0)
    {
        for(i=0;i<u8addrcount;i++)
        {
            if(MSB1210_IIC_SendByte(pu8addr[i])==FALSE)
                return FALSE;
        }
    }

    for(i=0;i<u16size;i++)
    {

        if(MSB1210_IIC_SendByte(pu8data[i])==FALSE)
            return FALSE;
        //printf("Table[%d] = %x\n",(int)i, (int)pu8data[i]);

    }

    MSB1210_IIC_Stop();

    return TRUE;
}
/***********************************************************************************
  Subject:    IIC Master Read multi-bytes function
  Function:   MSB1210_IIC_ReadBytes
  Parmeter:
              u8SlaveID : slave address
              u8AddrNum : Address counts
              pu8addr : pointer of array of address
              u16size : size of data
              pu8data : pointer for return data.
  Return:     BOOLEAN
  Remark:
************************************************************************************/
BOOLEAN MSB1210_IIC_ReadBytes(U8 u8SlaveID, U8 u8AddrNum, U8* paddr, U16 u16size, U8* pu8data)
{
    U16 i;

    MSB1210_IIC_Start();

    if(MSB1210_IIC_SendByte(u8SlaveID&0xFE)==FALSE)
        return FALSE;

    if(u8AddrNum>0)
    {
        for(i=0;i<u8AddrNum;i++)
        {
            if(MSB1210_IIC_SendByte(*(paddr+i))==FALSE)
                return FALSE;
        }
    }

    if(u16size > 0)
    {
        MSB1210_IIC_Start();

        if(MSB1210_IIC_SendByte(u8SlaveID|0x1)==FALSE)
            return FALSE;

        for(i=0;i<u16size;i++)
        {
            if(i==(u16size-1))
                MSB1210_IIC_NoAck();

            if(MSB1210_IIC_GetByte(pu8data++)==FALSE)
            {
                return FALSE;
            }
        }
    }
    MSB1210_IIC_Stop();

    return TRUE;

}
#endif


/***********************************************************************************
  Subject:    Command Packet Interface
  Function:   MSB1210_Cmd_Packet_Send
  Parmeter:
  Return:     BOOLEAN
  Remark:
************************************************************************************/
BOOLEAN MSB1210_Cmd_Packet_Send(S_CMDPKTREG* pCmdPacket, U8 param_cnt)
{
    U8             status = true, indx;
    U8             reg_val, timeout = 0;

    // ==== Command Phase ===================
                DBG_MSB(printf("--->MSB1210 (cmd=0x%x)(0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,) \n",pCmdPacket->cmd_code
                    ,pCmdPacket->param[0],pCmdPacket->param[1]
                   ,pCmdPacket->param[2],pCmdPacket->param[3],pCmdPacket->param[4],pCmdPacket->param[5] ));
#if (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)
    if (gMSB1210ATVMode == 0)
        if (pCmdPacket->cmd_code == CMD_VIF_CTRL)
        {
            DBG_MSB(printf("MSB1210 ---> Skip VIF Command during DTV Mode \n"));
            return false;
        }
#endif
    // wait _BIT_END clear
    do {
        status &= MSB1210_ReadReg(REG_CMD_CTRL, &reg_val);

        if((reg_val & _BIT_END) != _BIT_END)
            break;

             MsOS_DelayTask(5);

        if (timeout++ > 200)
        {
                DBG_MSB(printf("---> MSB1210_Cmd_Packet_Send fail on 'wait _BIT_END clear' \n"));
            return false;
            }

    } while (1);

    // set cmd_3:0 and _BIT_START
    status &= MSB1210_ReadReg(REG_CMD_CTRL, &reg_val);
    reg_val = (reg_val & 0x0f)|(pCmdPacket->cmd_code << 4)|_BIT_START;
    status &= MSB1210_WriteReg(REG_CMD_CTRL, reg_val);

    //DBG_MSB(printf("demod_config: cmd_code = %bx\n", pCmdPacket->cmd_code));


    // wait _BIT_START clear
    do {
        status &= MSB1210_ReadReg(REG_CMD_CTRL, &reg_val);

        if((reg_val & _BIT_START) != _BIT_START)
            break;

             MsOS_DelayTask(5);

        if (timeout++ > 200)
        {
                DBG_MSB(printf("---> MSB1210_Cmd_Packet_Send fail on 'wait _BIT_START clear' \n"));
            return false;
            }

    } while (1);

    // ==== Data Phase ======================

    status &= MSB1210_WriteReg(REG_CMD_ADDR, 0x00);

    for (indx = 0; indx < param_cnt; indx++)
    {
        status &= MSB1210_ReadReg(REG_CMD_ADDR, &reg_val);
        //DBG_MSB(printf("demod_config: param[%bd] = %bx\n", reg_val, pCmdPacket->param[indx]));

        // set param[indx] and _BIT_DRQ
        status &= MSB1210_WriteReg(REG_CMD_DATA, pCmdPacket->param[indx]);
        status &= MSB1210_ReadReg(REG_DTA_CTRL, &reg_val);
        status &= MSB1210_WriteReg(REG_DTA_CTRL, reg_val|_BIT_DRQ);

        // wait _BIT_DRQ clear
        do {
            status &= MSB1210_ReadReg(REG_DTA_CTRL, &reg_val);

            if ((reg_val & _BIT_DRQ) != _BIT_DRQ)
                break;

                   MsOS_DelayTask(5);

            if (timeout++ > 200)
              {
                        DBG_MSB(printf("---> MSB1210_Cmd_Packet_Send fail on 'wait _BIT_DRQ clear' \n"));
                return false;
                  }
        } while (1);
    }

    // ==== End Phase =======================

    // set _BIT_END to finish command
    status &= MSB1210_ReadReg(REG_CMD_CTRL, &reg_val);
    status &= MSB1210_WriteReg(REG_CMD_CTRL, reg_val|_BIT_END);

    return status;
}


/***********************************************************************************
  Subject:    Command Packet Interface
  Function:   MSB1210_Cmd_Packet_Exe_Check
  Parmeter:
  Return:     BOOLEAN
  Remark:
************************************************************************************/
BOOLEAN MSB1210_Cmd_Packet_Exe_Check(BOOL* cmd_done)
{
    U8             status = true;
    U8             reg_val;
    U16            timeout = 0;

    // wait _BIT_END clear
    do {
        status &= MSB1210_ReadReg(REG_CMD_CTRL, &reg_val);

        if((reg_val & _BIT_END) != _BIT_END)
            break;

        if (timeout++ > 200)
        {
            *cmd_done = false;
            return status;
        }
        MSB1210_Delayms(10);
    } while (1);

    DBG_MSB(printf("Exe duration: %d\n", (int)timeout));

    *cmd_done = true;
    return status;
}

/***********************************************************************************
  Subject:    Reset
  Function:   MSB1210_Reset
  Parmeter:
  Return:     BOOLEAN
  Remark:
************************************************************************************/
BOOLEAN MSB1210_Reset ( void )
{
    DBG_MSB(printf(" @msb1210_reset\n"));

    MSB1210_WriteReg(0x8232, 0x01);
    MSB1210_WriteReg(0x8220, 0x01);
    MSB1210_Delayms(5);
    MSB1210_WriteReg(0x8220, 0x00);
    MSB1210_WriteReg(0x8232, 0x00);
    FECLock = FALSE;
    return TRUE;
}


/***********************************************************************************
  Subject:    Load DSP code to chip
  Function:   MSB1210_LoadDSPCode
  Parmeter:
  Return:     BOOLEAN
  Remark:
************************************************************************************/
static BOOLEAN MSB1210_LoadDSPCode(void)
{
    U16 i;
    BOOLEAN bResult;
#if (DBG_DUMP_LOAD_DSP_TIME==1)
    U32 u32Time;
#endif

    //U32 u32GEAddr;
    U8 *pu8DataBuffer = NULL;
    U32 u32Old_I2C_Speed;

#ifndef MSB1210_LOAD_FW_FROM_CODE_MEMORY
    BININFO BinInfo;
    U8 Data;
    S8 op;
    U32 srcaddr;
    U32 len;
    U32 SizeBy4K;
    U32 j;
    U16 u16Counter=0;
    U8 *pU8Data;
#endif

    if (MSB1210_WriteReg(0x8232,0x01) == FALSE)        // MCU SW reset
        return FALSE;

    if (MSB1210_WriteReg(0x8230,0x03) == FALSE)     // Enable read SRAM from I2CS
        return FALSE;

    if (MSB1210_WriteReg(0x8210,0x55) == FALSE)
        return FALSE;

    if (MSB1210_WriteReg(0x8211,0xAA) == FALSE)
        return FALSE;

    u8MsbData[0] = DEMOD_RAM_CONTROL;
    u8MsbData[1] = 0x01;
    if (MDrv_IIC_WriteBytes(gu8DemoDynamicI2cAddress, 0, NULL, 2, u8MsbData) == FALSE)// Enable SRAM write
        return FALSE;

    // load table

    IIC_Start();

    if(IIC_SendByte(gu8DemoDynamicI2cAddress&0xFE)==FALSE)
        return FALSE;

    u8MsbData[0] = DEMOD_ADDR_H;
    u8MsbData[1] = 0;
    u8MsbData[2] = 0;

    for(i=0;i<3;i++)
    {
        if(IIC_SendByte(u8MsbData[i])==FALSE)
            return FALSE;
    }
#ifdef MSB1210_LOAD_FW_FROM_CODE_MEMORY
    for(i=0;i<sizeof(MSB1210_table);i++)
    {
        if(IIC_SendByte(MSB1210_table[i])==FALSE)
            return FALSE;
    }
#else

    BinInfo.B_ID = BIN_ID_MSB1210_DEMOD;
      msAPI_MIU_Get_BinInfo(&BinInfo, &bResult);
    if ( bResult != PASS )
    {
        return FALSE;
    }
    //printf("\t GE_FRAMEBUFFER_ADR  =%08LX\n", ((GE_FRAMEBUFFER_MEMORY_TYPE & MIU1) ? (GE_FRAMEBUFFER_ADR | MIU_INTERVAL) : (GE_FRAMEBUFFER_ADR)));

#ifdef SUPPORT_AP_BIN_IN_FLASH_2
    InfoBlock_Flash_2_Checking_Start(&BinInfo);

#endif

    //MApi_BDMA_CopyFromResource(BinInfo.B_FAddr,_PA2VA((GE_FRAMEBUFFER_MEMORY_TYPE & MIU1) ? (GE_FRAMEBUFFER_ADR | MIU_INTERVAL) : (GE_FRAMEBUFFER_ADR)), MemAlign(BinInfo.B_Len, 8));
    //msAPI_MIU_Copy(BinInfo.B_FAddr, ((GE_FRAMEBUFFER_MEMORY_TYPE & MIU1) ? (GE_FRAMEBUFFER_ADR | MIU_INTERVAL) : (GE_FRAMEBUFFER_ADR)), MemAlign(BinInfo.B_Len, 8), MIU_FLASH2SDRAM);

    pu8DataBuffer = (U8 *)msAPI_Memory_Allocate((U16)(28*1024), BUF_ID_MSB1210_DOWNLOAD);

    if (pu8DataBuffer == NULL)
    {
        __ASSERT(0);
        printf("????MSB1210 allocate memory Fail...\n");
        return FALSE;
    }
    else
    {
        MApi_BDMA_CopyFromResource(BinInfo.B_FAddr, (U32)pu8DataBuffer, MemAlign(BinInfo.B_Len, 8));
    }

#ifdef SUPPORT_AP_BIN_IN_FLASH_2
    InfoBlock_Flash_2_Checking_End(&BinInfo);

#endif


    //W1BaseAddr = MDrv_Sys_GetXdataWindow1Base();
    SizeBy4K=BinInfo.B_Len/0x1000;
    //printf("\t RRR: SizeBy4K  =%08LX(L=0x%lx)\n", SizeBy4K,BinInfo.B_Len);


    u32Old_I2C_Speed = MDrv_IIC_Speed_Setting(E_I2C_BUS_SYS,I2C_SPEED_MAPPING_400K);

#if (DBG_DUMP_LOAD_DSP_TIME==1)
    u32Time = msAPI_Timer_GetTime0();
#endif

    //u32GEAddr = _PA2VA(((GE_FRAMEBUFFER_MEMORY_TYPE & MIU1) ? (GE_FRAMEBUFFER_ADR | MIU_INTERVAL) : (GE_FRAMEBUFFER_ADR)));

    for (j=0;j<=SizeBy4K;j++)
    {
        if(j==SizeBy4K)
        len=BinInfo.B_Len%0x1000;
        else
        len=0x1000;

        //srcaddr = u32GEAddr+(0x1000*j);
        srcaddr=(U32)pu8DataBuffer+(0x1000*j);
        //printf("\t j = %08LX\n", j);
        //printf("\t len = %08LX\n", len);
        op = 1;
        u16Counter = 0 ;
     //   printf("\t (B=0x%bx)(Src=0x%x)Data =",j,srcaddr);
        while(len--)
        {
            u16Counter ++ ;
            //printf("file: %s, line: %d\n", __FILE__, __LINE__);
            //pU8Data = (U8 *)(srcaddr|0x80000000);
            #ifdef MSOS_TYPE_LINUX
            pU8Data = (U8 *)(srcaddr);
            #else
            pU8Data = (U8 *)(srcaddr|0x80000000);
            #endif
            Data  = *pU8Data;

#if 0
            if(u16Counter < 0x100)
              printf("0x%bx,", Data);
#endif
            if(IIC_SendByte(Data)==FALSE)
            {
                printf("????IIC_SendByte Fail... \n");
                if(!msAPI_Memory_Free((void *)pu8DataBuffer,BUF_ID_MSB1210_DOWNLOAD))
                    printf("????MSB1210 free memory Fail...\n");
                return FALSE;
            }
            srcaddr += op;
        }
     //   printf("\n\n\n");
    }

#endif
    IIC_Stop();

    MDrv_IIC_Speed_Setting(E_I2C_BUS_SYS,u32Old_I2C_Speed);

    if(!msAPI_Memory_Free((void *)pu8DataBuffer,BUF_ID_MSB1210_DOWNLOAD))
        printf("????MSB1210 free memory Fail...\n");

#if (DBG_DUMP_LOAD_DSP_TIME==1)
             printf("------> MSB1210 Load DSP Time:  (%lu)\n", msAPI_Timer_DiffTimeFromNow(u32Time)) ;
#endif


    u8MsbData[0] = DEMOD_RAM_CONTROL;
    u8MsbData[1] = 0x00;
    if (MDrv_IIC_WriteBytes(gu8DemoDynamicI2cAddress, 0, NULL, 2, u8MsbData) == FALSE) // Disable Ram write
        return FALSE;

    if (MSB1210_WriteReg(0x8230,0x00) == FALSE)// Disable download from I2CS
        return FALSE;

#ifdef  MSB1210_VERIFY_TABLE   // Verify table
    MSB1210_Delayms(100);
    if (MSB1210_WriteReg(0x8230, 0x02) == FALSE)     // Enable read SRAM from I2CS
        return FALSE;

    u8MsbData[0] = DEMOD_ADDR_H;
    u8MsbData[1] = 0;
    u8MsbData[2] = 0;

    if (MDrv_IIC_WriteBytes(gu8DemoDynamicI2cAddress, 0, 0, 3, u8MsbData) == FALSE)
    {
        return FALSE;
    }
#ifdef MSB1210_USE_HW_I2C

    IIC_Start();

    if(IIC_SendByte(gu8DemoDynamicI2cAddress)==FALSE)
        return FALSE;

    if(IIC_SendByte(DEMOD_READ_REG)==FALSE)
        return FALSE;

    IIC_Start();

    if(IIC_SendByte(gu8DemoDynamicI2cAddress|0x1)==FALSE)
        return FALSE;


    for(i=0;i<sizeof(MSB1210_table);i++)
    {
        if(i==(sizeof(MSB1210_table)-1))
            IIC_NoAck();

        if(IIC_GetByte(u8MsbData)==FALSE)
            return FALSE;

        if (u8MsbData[0] != MSB1210_table[i])
        {
            DBG_MSB(printf("Verify error[%d] %bx, %bx\n",i,u8MsbData[0], MSB1210_table[i]));
            break;
        }

    }

    IIC_Stop();
#else

    if (IIC_AccessStart(gu8DemoDynamicI2cAddress, 1) == FALSE)
        return FALSE;

    if (IIC_SendByte( DEMOD_READ_REG ) == FALSE)
        return FALSE;

    if (IIC_AccessStart(gu8DemoDynamicI2cAddress, 0) == FALSE)
        return FALSE;

    for(i=0;i<sizeof(MSB1210_table);i++)
    {
        if(i==(sizeof(MSB1210_table)-1))
            u8MsbData[0] = IIC_GetByte(0);
        else
            u8MsbData[0] = IIC_GetByte(1);

        if (u8MsbData[0] != MSB1210_table[i])
        {
            DBG_MSB(printf("Verify error[%d] %bx, %bx\n",i,u8MsbData[0], MSB1210_table[i]));
            break;
        }
    }

    IIC_Stop();

#endif

    if (MSB1210_WriteReg(0x8230,0x0) == FALSE) // Disable read SRAM from I2CS
        return FALSE;
#endif

    if (MSB1210_WriteReg(0x8232,0x00) == FALSE)// MCU SW reset
        return FALSE;

    return TRUE;


}


/***********************************************************************************
  Subject:    I2C Address Polling
  Function:   MSB1210_I2C_Address_Polling
  Parmeter:
  Return:     BOOLEAN
  Remark:    ** The address of Gemini is 0x32, 0x72, 0xB2, 0xF2.
                 ** Read REG_CHIP_VERSION  0x8000 ~ 0x8001 [15:0] = 0x0008
************************************************************************************/
BOOLEAN MSB1210_I2C_Address_Polling ( void )
{
   U8 u8I2C_Add[4]={DEMOD_DYNAMIC_SLAVE_ID_MSB_1210_1, DEMOD_DYNAMIC_SLAVE_ID_MSB_1210_2, DEMOD_DYNAMIC_SLAVE_ID_MSB_1210_3, DEMOD_DYNAMIC_SLAVE_ID_MSB_1210_4};
   U8 u8Data,i;

    gu8DemoDynamicI2cAddress = u8I2C_Add[0];

    for (i=0;i<4;i++)
    {
        u8MsbData[0] = DEMOD_ADDR_H;
        u8MsbData[1] = 0x80;
        u8MsbData[2] = 0x00;

        if (MDrv_IIC_WriteBytes(u8I2C_Add[i], 0, 0, 3, u8MsbData) == FALSE)
        {//Fail
            DBG_MSB(printf("read write fail-1\n"));
        }
        else
        {//Success
            u8MsbData[0] = DEMOD_READ_REG;
            if (MDrv_IIC_ReadBytes(u8I2C_Add[i], 1, u8MsbData, 1, &u8Data)==FALSE)
            {//Fail
                DBG_MSB(printf("read write fail2\n"));
            }else
            {//Success Case
                if (u8Data == 0x08)//Check Revision ID
                {   //Success
                    gu8DemoDynamicI2cAddress = u8I2C_Add[i];
                    //printf("MSB1210:MSB1210_I2C_Address_Polling OK (0x%bx)\n",u8I2C_Add[i]);
                    return (TRUE);
                }else
                {
                    DBG_MSB(printf("read write fail-3(u8Data= 0x%bx)\n",u8Data));
                }
            }
        }
    };


    printf("MSB1210:MSB1210_I2C_Address_Polling Fail \n");

    return FALSE;

}




/***********************************************************************************
  Subject:    Power on initialized function
  Function:   MSB1210_Power_On_Initialization
  Parmeter:
  Return:     BOOLEAN
  Remark:
************************************************************************************/

BOOLEAN MSB1210_Power_On_Initialization ( void )
{
    U8            status = true;
    U8            cal_done;



    //Polling I2C Address
    if (MSB1210_I2C_Address_Polling()==FALSE)
    {
        printf("?????:MSB1210 I2C Address Polling Fail...\n");
        return FALSE;
    }


    //// Firmware download //////////
    DBG_MSB(printf("MSB1210 Load DSP...\n"));
    MsOS_DelayTask(100);
    if (MSB1210_LoadDSPCode() == FALSE)
    {
        DBG_MSB(printf("Fail\n"));
        return FALSE;
    }
    else
    {
        DBG_MSB(printf("OK\n"));
    }

    //// MCU Reset //////////
    DBG_MSB(printf("MSB1210 Reset...\n"));
    if (MSB1210_Reset() == FALSE)
    {
        DBG_MSB(printf("Fail\n"));
        return FALSE;
    }
    else
    {
        DBG_MSB(printf("OK\n"));
    }

    MSB1210_ReadReg(0x8000, &gu8ChipRevId);
    DBG_MSB(printf("Gemini RevID:%bx\n", gu8ChipRevId));

    //// DAC calibration //////////
    DBG_MSB(printf("MSB1210 Cal DAC...\n"));

    gsCmdPacket.cmd_code = CMD_DAC_CALI;
    gsCmdPacket.param[dac_op_code] = DAC_RUN_CALI;
    status &= MSB1210_Cmd_Packet_Send(&gsCmdPacket, 1);
    status &= MSB1210_Cmd_Packet_Exe_Check(&cal_done);
    if (cal_done == true)
    {
        DBG_MSB(printf("OK\n"));
        status &= MSB1210_ReadReg(0x81A8, &gCalIdacCh0);
        status &= MSB1210_ReadReg(0x81A9, &gCalIdacCh1);
    }
    else
    {
        gCalIdacCh0 = gCalIdacCh1 = 0;
        DBG_MSB(printf("FAIL\n"));
    }

    return status;
}
/************************************************************************************************
  Subject:    Driving control
  Function:   MSB1210_Driving_Control
  Parmeter:   bInversionEnable : TRUE For High
  Return:      void
  Remark:
*************************************************************************************************/
void MSB1210_Driving_Control(BOOLEAN bEnable)
{
    U8    u8Temp;

    MSB1210_ReadReg(0x8056, &u8Temp);

    if (bEnable)
    {
       u8Temp = u8Temp | 0x02;
    }
    else
    {
       u8Temp = u8Temp & (~0x02);
    }

    DBG_MSB(printf("---> MSB1210_Driving_Control(Bit5) = 0x%bx \n",u8Temp));
    MSB1210_WriteReg(0x8056, u8Temp);

}
/************************************************************************************************
  Subject:    Clk Inversion control
  Function:   MSB1210_Clk_Inversion_Control
  Parmeter:   bInversionEnable : TRUE For Inversion Action
  Return:      void
  Remark:
*************************************************************************************************/
void MSB1210_Clk_Inversion_Control(BOOLEAN bInversionEnable)
{
    U8    u8Temp;

    MSB1210_ReadReg(MSB1210_REG_INVERSION, &u8Temp);

    if (bInversionEnable)
    {
       u8Temp = u8Temp | 0x20;
    }
    else
    {
       u8Temp = u8Temp & (~0x20);
    }

    DBG_MSB(printf("---> Inversion(Bit5) = 0x%bx \n",u8Temp));
    MSB1210_WriteReg(MSB1210_REG_INVERSION, u8Temp);

}
/************************************************************************************************
  Subject:    Transport stream serial/parallel control
  Function:   MSB1210_Serial_Control
  Parmeter:   bEnable : TRUE For serial
  Return:     BOOLEAN :
  Remark:
*************************************************************************************************/
BOOLEAN MSB1210_Serial_Control(BOOLEAN bEnable)
{
    U8            status = true;

    DBG_MSB(printf(" @msb1210_ts... "));

    if (bEnable)    //Serial mode for TS pad
    {
        //// MSB1210 TS Control: Serial //////////
        gsCmdPacket.cmd_code = CMD_TS_CTRL;

        gsCmdPacket.param[0] = TS_SERIAL;
#if(MSB1210_TS_SERIAL_INVERSION == 0)
        gsCmdPacket.param[1] = 0;//TS_CLK_NO_INV;
#else
        gsCmdPacket.param[1] = 1;//TS_CLK_INVERSE;
#endif


        status &= MSB1210_Cmd_Packet_Send(&gsCmdPacket, 2);
    }
    else
    {
        //// MSB1210 TS Control: Parallel //////////
        gsCmdPacket.cmd_code = CMD_TS_CTRL;

        gsCmdPacket.param[0] = TS_PARALLEL;
#if(MSB1210_TS_PARALLEL_INVERSION == 0)
        gsCmdPacket.param[1] = 0;//TS_CLK_NO_INV;
#else
        gsCmdPacket.param[1] = 1;//TS_CLK_INVERSE;
#endif

        status &= MSB1210_Cmd_Packet_Send(&gsCmdPacket, 2);
    }
DBG_MSB(printf("---> Inversion(Bit5) = 0x%bx \n",gsCmdPacket.param[1] ));

     MSB1210_Driving_Control(MSB1210_DTV_DRIVING_LEVEL);


    return status;
}


/************************************************************************************************
  Subject:    channel change config
  Function:   MSB1210_Config
  Parmeter:   BW: bandwidth
  Return:     BOOLEAN :
  Remark:
*************************************************************************************************/
BOOLEAN MSB1210_Config ( RF_CHANNEL_BANDWIDTH BW, BOOLEAN bSerialTS, BOOLEAN bPalBG, BOOLEAN bLPSel)
{
    U16             fc;
    U8                 bandwidth;
    U8                status = true;

    DBG_MSB(printf(" @msb1210_config\n"));

    fc = 45473 - 36167;

    switch(BW)
    {
        /*    no provided
        case E_RF_CH_BAND_5MHz:
            bandwidth = 0;
            break;
        */
        case E_RF_CH_BAND_6MHz:
            bandwidth = 1;
            break;
        case E_RF_CH_BAND_7MHz:
            bandwidth = 2;
            break;
        case E_RF_CH_BAND_8MHz:
        default:
            bandwidth = 3;
            break;
    }

    status &= MSB1210_Reset();

//// MSB1210 system init: DVB-T //////////
    gsCmdPacket.cmd_code = CMD_SYSTEM_INIT;

    gsCmdPacket.param[0] = E_SYS_DVBT;
    status &= MSB1210_Cmd_Packet_Send(&gsCmdPacket, 1);

//// DVB-T configurate ///////////////////
    gsCmdPacket.cmd_code = CMD_DVBT_CONFIG;

    gsCmdPacket.param[p_opmode_rfagc_en]          = 0;
    gsCmdPacket.param[p_opmode_humdet_en]          = 0;
    gsCmdPacket.param[p_opmode_dcr_en]              = 1;
    gsCmdPacket.param[p_opmode_iqb_en]              = 0;
    gsCmdPacket.param[p_opmode_auto_iq_swap]      = 1;
    gsCmdPacket.param[p_opmode_auto_fsa_left]     = 1;
    gsCmdPacket.param[p_opmode_auto_rfmax]          = 0;
    gsCmdPacket.param[p_opmode_mode_forced]     = 0;
    gsCmdPacket.param[p_opmode_cp_forced]          = 0;
    gsCmdPacket.param[pc_config_rssi]             = 0;
    gsCmdPacket.param[pc_config_zif]             = 0;
    gsCmdPacket.param[pc_config_fc_l]             = 0x5a;
    gsCmdPacket.param[pc_config_fc_h]             = 0x24;
    gsCmdPacket.param[pc_config_fs_l]             = 0xa1;
    gsCmdPacket.param[pc_config_fs_h]             = 0xb1;
    gsCmdPacket.param[pc_config_bw]             = bandwidth;
    gsCmdPacket.param[pc_config_fsa_left]        = 0;
    gsCmdPacket.param[pc_config_rfmax]             = 1;
    gsCmdPacket.param[pc_config_lp_sel]         = bLPSel?1:0;
    gsCmdPacket.param[pc_config_cp]             = 3;
    gsCmdPacket.param[pc_config_mode]             = 1;
    gsCmdPacket.param[pc_config_iq_swap]         = 0;
    gsCmdPacket.param[pc_config_atv_system]      = bPalBG? 0:1;
    gsCmdPacket.param[pc_config_serial_ts]        = bSerialTS;

       if (bSerialTS)
       {
        #if(MSB1210_TS_SERIAL_INVERSION == 0)
        gsCmdPacket.param[pc_config_ts_out_inv]        = false;
        #else
    gsCmdPacket.param[pc_config_ts_out_inv]        = true;
        #endif
       }
       else
       {
        #if(MSB1210_TS_PARALLEL_INVERSION == 0)
        gsCmdPacket.param[pc_config_ts_out_inv]        = false;
#else
        gsCmdPacket.param[pc_config_ts_out_inv]        = true;
#endif
       }
    status &= MSB1210_Cmd_Packet_Send(&gsCmdPacket, DVBT_PARAM_LEN);

    return status;
}
/************************************************************************************************
  Subject:    enable hw to lock channel
  Function:   MSB1210_Active
  Parmeter:   bEnable
  Return:     BOOLEAN
  Remark:
*************************************************************************************************/
BOOLEAN MSB1210_Active(BOOLEAN bEnable)
{
    U8            status = true;

    DBG_MSB(printf(" @msb1210_active\n"));

    //// MSB1210 Finite State Machine on/off //////////
    gsCmdPacket.cmd_code = CMD_FSM_CTRL;

    gsCmdPacket.param[0] = (U8)bEnable;
    status &= MSB1210_Cmd_Packet_Send(&gsCmdPacket, 1);

    return status;
}
/************************************************************************************************
  Subject:    Return lock status
  Function:   MSB1210_Lock
  Parmeter:   eStatus :
  Return:     BOOLEAN
  Remark:
*************************************************************************************************/
BOOLEAN MSB1210_Lock( COFDM_LOCK_STATUS eStatus )
{
    U16 u16Address;
    BYTE cData;
    BYTE cBitMask;

    static U32      u32FecLockTime;

    switch( eStatus )
    {
    case COFDM_FEC_LOCK:
        MSB1210_ReadReg(0x87E0, &cData);
        if (cData == 0x0B)
        {
            u32FecLockTime = msAPI_Timer_GetTime0();
            FECLock = TRUE;
            return TRUE;
        }
        else
        {
            if (FECLock == TRUE)
            {
                if ( ( msAPI_Timer_GetTime0() - u32FecLockTime ) < 3000 )
                    return TRUE;
            }
            FECLock = FALSE;
            return FALSE;      // continuously un-lock
        }
        break;

    case COFDM_PSYNC_LOCK:
        u16Address =  0x872C; //FEC: P-sync Lock,
        cBitMask = BIT1;
        break;

    case COFDM_TPS_LOCK:
        u16Address =  0x8622; //TPS Lock,
        cBitMask = BIT1;
        break;

    case COFDM_DCR_LOCK:
        u16Address =  0x8545; //DCR Lock,
        cBitMask = BIT0;
        break;

    case COFDM_AGC_LOCK:
        u16Address =  0x852F; //AGC Lock,
        cBitMask = BIT0;
        break;

    case COFDM_MODE_DET:
        u16Address =  0x88CF; //Mode CP Detect,
        cBitMask = BIT4;
        break;

    default:
        return FALSE;
    }

    if (MSB1210_ReadReg(u16Address, &cData) == FALSE)
        return FALSE;

    if ((cData & cBitMask) == cBitMask)
    {
        return TRUE;
    }

    return FALSE;

}

/****************************************************************************
  Subject:    To get the Post viterbi BER
  Function:   MSB1210_GetPostViterbiBer
  Parmeter:  Quility
  Return:       E_RESULT_SUCCESS
                   E_RESULT_FAILURE =>Read I2C fail, MSB1210_VIT_STATUS_NG
  Remark:     For the Performance issue, here we just return the Post Value.(Not BER)
                   We will not read the Period, and have the "/256/8"
*****************************************************************************/
BOOLEAN MSB1210_GetPostViterbiBer(float *ber)
{
    U8            status = true;
    U8            reg, reg_frz;
    U16            BitErrPeriod;
    U32            BitErr;
    U16            PktErr;

    /////////// Post-Viterbi BER /////////////

    // bank 7 0x32 [7] reg_bit_err_num_freeze
    status &= MSB1210_ReadReg(0x8732, &reg_frz);
    status &= MSB1210_WriteReg(0x8732, reg_frz|0x80);

    // bank 7 0x30 [7:0] reg_bit_err_sblprd_7_0
    //               [15:8] reg_bit_err_sblprd_15_8
    status &= MSB1210_ReadReg(0x8731, &reg);
    BitErrPeriod = reg;

    status &= MSB1210_ReadReg(0x8730, &reg);
    BitErrPeriod = (BitErrPeriod << 8)|reg;

    // bank 7 0x3a [7:0] reg_bit_err_num_7_0
    //               [15:8] reg_bit_err_num_15_8
    // bank 7 0x3c [7:0] reg_bit_err_num_23_16
    //               [15:8] reg_bit_err_num_31_24

    status &= MSB1210_ReadReg(0x873D, &reg);
    BitErr = reg;

    status &= MSB1210_ReadReg(0x873C, &reg);
    BitErr = (BitErr << 8)|reg;

    status &= MSB1210_ReadReg(0x873B, &reg);
    BitErr = (BitErr << 8)|reg;

    status &= MSB1210_ReadReg(0x873A, &reg);
    BitErr = (BitErr << 8)|reg;

    // bank 7 0x3e [7:0] reg_uncrt_pkt_num_7_0
    //               [15:8] reg_uncrt_pkt_num_15_8
    status &= MSB1210_ReadReg(0x873F, &reg);
    PktErr = reg;

    status &= MSB1210_ReadReg(0x873E, &reg);
    PktErr = (PktErr << 8)|reg;

    // bank 7 0x32 [7] reg_bit_err_num_freeze
    status &= MSB1210_WriteReg(0x8732, reg_frz);

    if (BitErrPeriod == 0 )    //protect 0
        BitErrPeriod = 1;

    if (BitErr <=0 )
      *ber = 0.5 / ((float)BitErrPeriod*128*188*8);
    else
      *ber = (float)BitErr / ((float)BitErrPeriod*128*188*8);


   DBG_GET_SIGNAL(printf("MSB1210 PostVitBER = %8.3e \n ", *ber));
   DBG_GET_SIGNAL(printf("MSB1210 PktErr = %d \n ", (int)PktErr));


    return status;
}

/************************************************************************************************
  Subject:    Write data to tuner
  Function:   MSB1210_Tuner_Programming
  Parmeter:   pu8Data : pointer for writing data
  Return:     BOOLEAN
  Remark:
*************************************************************************************************/
/*GEM_REV
BOOLEAN MSB1210_Tuner_Programming(U8 *pu8Data)
{

#if 0
    if (MSB1210_IIC_WriteBytes(*pu8Data, 0, 0, 4, pu8Data+1) == FALSE)
    {
        DBG_MSB(printf("Write Tuner Fail\n"));
    }
    return TRUE;

    *pu8Data = *pu8Data;
    return TRUE;
}
*/


/****************************************************************************
  Subject:    Function providing approx. result of Log10(X)
  Function:   Log10Approx
  Parmeter:   Operand X in float
  Return:     Approx. value of Log10(X) in float
  Remark:      Ouput range from 0.0, 0.3 to 9.6 (input 1 to 2^32)
*****************************************************************************/
float Log10Approx(float flt_x)
{
    U32        u32_temp = 1;
    U8        indx = 0;

    do {
        u32_temp = u32_temp << 1;
        if (flt_x < (float)u32_temp)
            break;
    }while (++indx < 32);

    // 10*log10(X) ~= 0.3*N, when X ~= 2^N
    return (float)0.3 * indx;
}

/****************************************************************************
  Subject:    Read the signal to noise ratio (SNR)
  Function:   MSB1210_GetSNR
  Parmeter:   None
  Return:     -1 mean I2C fail, otherwise I2C success then return SNR value
  Remark:
*****************************************************************************/
float MSB1210_GetSNR (void)
{
    U8            status = true;
    U8            reg, reg_frz;
    U32            noise_power;
    float        snr;

    // bank 6 0xfe [0] reg_fdp_freeze
    status &= MSB1210_ReadReg(0x86fe, &reg_frz);
    status &= MSB1210_WriteReg(0x86fe, reg_frz|0x01);

    // bank 6 0x4a [26:0] reg_snr_accu <27,1>
    status &= MSB1210_ReadReg(0x864d, &reg);
    noise_power = reg & 0x07;

    status &= MSB1210_ReadReg(0x864c, &reg);
    noise_power = (noise_power << 8)|reg;

    status &= MSB1210_ReadReg(0x864b, &reg);
    noise_power = (noise_power << 8)|reg;

    status &= MSB1210_ReadReg(0x864a, &reg);
    noise_power = (noise_power << 8)|reg;

    noise_power = noise_power/2;

    // bank 6 0x26 [5:4] reg_transmission_mode
    status &= MSB1210_ReadReg(0x8626, &reg);

    // bank 6 0xfe [0] reg_fdp_freeze
    status &= MSB1210_WriteReg(0x86fe, reg_frz);

    if ((reg&0x03)==0x00)     //2K
    {
      if (noise_power<1512)
        snr = 0;
      else
        snr = 10*Log10Approx((float)noise_power/1512);
    }
    //else if ((reg&0x03)==0x01)//8K
    else
    {
      if (noise_power<6048)
        snr = 0;
      else
        snr = 10*Log10Approx((float)noise_power/6048);
    }
    /* ignore 4K
    else                       //4K
    {
      if (noise_power<3024)
        snr = 0;
      else
        snr = 10*Log10Approx(noise_power/3024);
    }
    */

    if (status == true)
        return snr;
    else
        return -1;

}

FUNCTION_RESULT MSB1210_GetSignalStrength(WORD *strength)
{
    *strength = 80;
    return E_RESULT_SUCCESS;
}

/****************************************************************************
  Subject:    To get the DVT Signal quility
  Function:   MSB1210_GetSignalQuality
  Parmeter:  Quility
  Return:      E_RESULT_SUCCESS
                   E_RESULT_FAILURE
  Remark:    Here we have 4 level range
                  <1>.First Range => Quility =100  (You can define it by MSB1210_SIGNAL_BASE_100)
                  <2>.2th Range => 60 < Quility < 100 (You can define it by MSB1210_SIGNAL_BASE_60)
                  <3>.3th Range => 10 < Quility < 60  (You can define it by MSB1210_SIGNAL_BASE_10)
                  <4>.4th Range => Quility <10
*****************************************************************************/
FUNCTION_RESULT MSB1210_GetSignalQuality(WORD *quality)
{
    float         fber;
    float         log_ber;

    if (TRUE == MSB1210_Lock(COFDM_PSYNC_LOCK) )
    {
        if (MSB1210_GetPostViterbiBer(&fber) == FALSE)
        {
            DBG_MSB(printf("GetPostViterbiBer Fail!\n"));
            return E_RESULT_FAILURE;
        }

        log_ber = (-1)*Log10Approx(1/fber);    // Log10Approx() provide 1~2^32 input range only

        DBG_GET_SIGNAL(printf("Log(BER) = %f\n",log_ber));

        if ( log_ber <= (-7.0) )            // PostVit BER < 1e-7
        {
            *quality = 100;
        }
        else  if ( log_ber < (-3.7) )        // PostVit BER < 2e-4
        {
            *quality = 60 + (((-3.7) - log_ber) / ((-3.7)-(-7.0)) * (100-60));
        }
        else  if ( log_ber < (-2.7) )        // PostVit BER < 2e-3
        {
            *quality = 10 + (((-2.7) - log_ber) / ((-2.7)-(-3.7)) * (60-10));
        }
        else
        {
            *quality = 10;
        }

    }
    else
    {
        *quality = 0;
    }

    DBG_GET_SIGNAL(printf("Signal Quility = %d\n", (int)*quality));

    return E_RESULT_SUCCESS;

}


/****************************************************************************
  Subject:    To get the DVBT Carrier Freq Offset
  Function:   MSB1210_Get_FreqOffset
  Parmeter:   Frequency offset (in KHz), bandwidth
  Return:     E_RESULT_SUCCESS
              E_RESULT_FAILURE
  Remark:
*****************************************************************************/
FUNCTION_RESULT MSB1210_Get_FreqOffset(float *pFreqOff, U8 u8BW)
{
      float         N, FreqB;
      float         FreqCfoTd, FreqCfoFd, FreqIcfo;
    U32            RegCfoTd, RegCfoFd, RegIcfo;
    U8            reg_frz, reg;
    U8            status;

    FreqB = (float)u8BW * 8 / 7;

    status = MSB1210_ReadReg(0x8504+1, &reg_frz);

    status &= MSB1210_WriteReg(0x8504+1, reg_frz|0x80);

    status &= MSB1210_ReadReg(0x88c6+2, &reg);
    RegCfoTd = reg;

    status &= MSB1210_ReadReg(0x88c6+1, &reg);
    RegCfoTd = (RegCfoTd << 8)|reg;

    status &= MSB1210_ReadReg(0x88c6, &reg);
    RegCfoTd = (RegCfoTd << 8)|reg;

    FreqCfoTd = (float)RegCfoTd;

    if (RegCfoTd & 0x800000)
        FreqCfoTd = FreqCfoTd - (float)0x1000000;

    FreqCfoTd = FreqCfoTd * FreqB * 0.00011642;

    status &= MSB1210_WriteReg(0x8504+1, reg_frz&(~0x80));

    status &= MSB1210_ReadReg(0x86fe, &reg_frz);
    status &= MSB1210_WriteReg(0x86fe, reg_frz|0x01);

    //status &= MSB1210_WriteReg(0x86fe+1, 0x01);
    status &= MSB1210_WriteReg(0x86ff, 0x01);

    status &= MSB1210_ReadReg(0x8630+3, &reg);
    RegCfoFd = reg;

    status &= MSB1210_ReadReg(0x8630+2, &reg);
    RegCfoFd = (RegCfoFd << 8)|reg;

    status &= MSB1210_ReadReg(0x8630+1, &reg);
    RegCfoFd = (RegCfoFd << 8)|reg;

    FreqCfoFd = (float)RegCfoFd;

    if (RegCfoFd & 0x800000)
        FreqCfoFd = FreqCfoFd - (float)0x1000000;

    FreqCfoFd = FreqCfoFd * FreqB * 0.00011642;

    status &= MSB1210_ReadReg(0x8618+1, &reg);
    RegIcfo = reg & 0x07;

    status &= MSB1210_ReadReg(0x8618, &reg);
    RegIcfo = (RegIcfo << 8)|reg;

    FreqIcfo = (float)RegIcfo;

    if (RegIcfo & 0x400)
        FreqIcfo = FreqIcfo - (float)0x800;

    status &= MSB1210_ReadReg(0x8626, &reg);
    reg = reg & 0x30;

    switch (reg)
    {
        case 0x00:    N = 2048;  break;
        case 0x20:  N = 4096;  break;
        case 0x10:
        default:    N = 8192;  break;
    }

    FreqIcfo = FreqIcfo * FreqB / N * 1000;         //unit: kHz
    status &= MSB1210_WriteReg(0x86fe, reg_frz&(~0x01));
    //status &= MSB1210_WriteReg(0x86fe+1, 0x01);
    status &= MSB1210_WriteReg(0x86ff, 0x01);
    *pFreqOff = FreqIcfo + (FreqCfoFd + FreqCfoTd)/1000;

    // DBG_GET_SIGNAL(printf("FCFO = %f\n", FreqCfoFd));
    // DBG_GET_SIGNAL(printf("TCFO = %f\n", FreqCfoTd));
    // DBG_GET_SIGNAL(printf("ICFO = %f\n", FreqIcfo));
    DBG_GET_SIGNAL(printf("CFOE = %f\n", *pFreqOff));

    if (status == TRUE)
        return E_RESULT_SUCCESS;
    else
        return E_RESULT_FAILURE;
}


void MSB1210_Power_ON_OFF(U8 bPowerOn)
{

    bPowerOn = bPowerOn;
}

BOOLEAN MSB1210_Power_Save(void)
{

    return TRUE;
}

/****************************************************************************
  Subject:    To get the DVBT constellation parameter
  Function:   MSB1210_Get_TPS_Parameter_Const
  Parmeter:   point to return parameter(0: QPSK, 1:16QAM, 2:64QAM)
  Return:     TRUE
              FALSE
  Remark:      The TPS parameters will be available after TPS lock
*****************************************************************************/
BOOLEAN MSB1210_Get_TPS_Parameter_Const( WORD * TPS_parameter)
{
    U8 tps_param;

    if ( MSB1210_ReadReg(0x8624, &tps_param) == FALSE )
        return FALSE;

    *TPS_parameter = tps_param & (BIT0|BIT1) ;
    return TRUE;
}

/****************************************************************************
  Subject:    To get the DVBT parameter
  Function:   MSB1210_GetTpsInfo
  Parmeter:   point to return parameter
              Constellation (b1 ~ b0)  : 0~2 => QPSK, 16QAM, 64QAM
              Hierarchy (b4 ~ b2))     : 0~3 => None, Aplha1, Aplha2, Aplha4
              LP Code Rate (b7 ~ b5)   : 0~4 => 1/2, 2/3, 3/4, 5/6, 7/8
              HP Code Rate (b10 ~ b8)  : 0~4 => 1/2, 2/3, 3/4, 5/6, 7/8
              GI (b12 ~ b11)           : 0~3 => 1/32, 1/16, 1/8, 1/4
              FFT (b14 ~ b13)          : 0~2 => 2K, 8K, 4K
  Return:     TRUE
              FALSE
  Remark:	  The TPS parameters will be available after TPS lock
*****************************************************************************/
BOOLEAN MSB1210_GetTpsInfo( WORD * TPS_parameter)
{
	U8 u8Temp;

    if (MSB1210_ReadReg(0x8622, &u8Temp) == FALSE)
        return FALSE;

	if ((u8Temp & 0x02) != 0x02)
	{
	    return FALSE; //TPS unlock
	}
	else
	{
    	if ( MSB1210_ReadReg(0x8624, &u8Temp) == FALSE )
    		return FALSE;

        *TPS_parameter = u8Temp & 0x03;         //Constellation (b1 ~ b0)
        *TPS_parameter |= (u8Temp & 0x70) >> 2; //Hierarchy (b4 ~ b2)

    	if ( MSB1210_ReadReg(0x8625, &u8Temp) == FALSE )
    		return FALSE;

        *TPS_parameter |= (WORD)(u8Temp & 0x07) << 5; //LP Code Rate (b7 ~ b5)
        *TPS_parameter |= (WORD)(u8Temp & 0x70) << 4; //HP Code Rate (b10 ~ b8)

    	if ( MSB1210_ReadReg(0x8626, &u8Temp) == FALSE )
    		return FALSE;

        *TPS_parameter |= (WORD)(u8Temp & 0x03) << 11; //GI (b12 ~ b11)
        *TPS_parameter |= (WORD)(u8Temp & 0x30) << 9;  //FFT (b14 ~ b13)
    }
	return TRUE;
}
/****************************************************************************
  Subject:    To check if Hierarchy on
  Function:   MSB1210_Is_HierarchyOn
  Parmeter:
  Return:     BOOLEAN
*****************************************************************************/
BOOLEAN MSB1210_Is_HierarchyOn( void)
{
    WORD u16_tmp;

    if(MSB1210_GetTpsInfo(&u16_tmp) == FALSE)
        return FALSE;
    if(u16_tmp&0x1c)
    {
        return TRUE;
    }
    return FALSE;
}
/***********************************************************************************
  Subject:    read register
  Function:   MDrv_1210_IIC_Bypass_Mode
  Parmeter:
  Return:
  Remark:
************************************************************************************/
void MDrv_1210_IIC_Bypass_Mode(BOOLEAN enable)
{
    if (enable)
        MSB1210_WriteReg(0x8010, 0x10);        // IIC by-pass mode on
    else
            MSB1210_WriteReg(0x8010, 0x00);        // IIC by-pass mode off
}

