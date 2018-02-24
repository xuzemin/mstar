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
// (!¡±MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
///@file drvMmsCfgChipDBG_CMD.c
///@brief System functions:
//
///////////////////////////////////////////////////////////////////////////////


#include "MsCommon.h"
#include "drvUartDebug.h"
#if ( ENABLE_MMS)
#include "drvMmsCfg_if.h"
#include "drvMmsCfgChip_if.h"
#include "drvMmsDisp_if.h"

#include "drvGlobal.h"
#include "drvIIC.h"

#define MAX_MSG_LEN 512
#define MAX_INPUT_VAR_NUM 12

typedef struct
{
    unsigned char varnum;
    unsigned short var[MAX_INPUT_VAR_NUM];
    //pid_t pid;
}ST_DEBUG_COMMAND_;

ST_DEBUG_COMMAND_ st_dbg_cmd_;


void MDrv_Cfg_ChipRead_Reg(void)
{
    if(MDrv_GetPara(1))
    {
        unsigned short data;
        st_dbg_cmd_.var[0] = para[0];
        data = MDrv_ReadByte(st_dbg_cmd_.var[0]);
        printf("read register 0x%x,data 0x%x\n",st_dbg_cmd_.var[0],data);
    }
    MDrv_ClearParaTbl();
}

void MDrv_Cfg_ChipRead_RegEntry(void)
{
    cfg_level = READ_REG;
    dynLevel = 1;
    MDrv_Cfg_ChipMenuPrint();
}

void MDrv_Cfg_ChipRead_RegPrint(void)
{
    printf("Execute READ_REG action. Ex.000 -0x33D0(addr)\n");
}

void MDrv_Cfg_ChipRead_RegEntryPrint(void)
{
    printf("Enter READ_REG page\n");
}

void MDrv_Cfg_ChipRead_RegInit(void)
{
    //(1)main page list
    MDrv_Cfg_Act(CHIP, CHIP_MAIN, MDrv_Cfg_ChipRead_RegEntry, MDrv_Cfg_ChipRead_RegEntryPrint);

    //(2)Action function(s)
    MDrv_Cfg_Act(CHIP, READ_REG, MDrv_Cfg_ChipRead_Reg, MDrv_Cfg_ChipRead_RegPrint);

    //(3)jump to CHIP main page
    MDrv_Cfg_Act(CHIP, READ_REG, MDrv_CfgGotoChipMainPage, MDrv_CfgGotoChipMainPagePrint);

    //(4)jump to config system main page
    MDrv_Cfg_Act(CHIP, READ_REG, MDrv_CfgGotoCfgMainPage, MDrv_CfgGotoCfgMainPagePrint);
}

void MDrv_Cfg_ChipWrite_Reg(void)
{
   if(MDrv_GetPara(2))
   {
       unsigned short addr,i;
        i=1;
        st_dbg_cmd_.var[0] = para[0];
        st_dbg_cmd_.varnum = para[1];

        addr=st_dbg_cmd_.var[0];
        while(i <= st_dbg_cmd_.varnum)
        {
            st_dbg_cmd_.var[i] = para[i+1];
            printf("write register 0x%x,data 0x%x\n",addr,st_dbg_cmd_.var[i]);
            MDrv_WriteByte(addr,st_dbg_cmd_.var[i]);
            addr++;i++;
        }
    }
   MDrv_ClearParaTbl();
}

void MDrv_Cfg_ChipWrite_RegEntry(void)
{
    cfg_level = WRITE_REG;
    dynLevel = 1;
    MDrv_Cfg_ChipMenuPrint();
}

void MDrv_Cfg_ChipWrite_RegPrint(void)
{
    printf("Execute Write_REG action. Ex. 000 -0x33D0(addr) 2(# of write data) 10(data1) 20(data2)\n");
}

void MDrv_Cfg_ChipWrite_RegEntryPrint(void)
{
  printf("Enter WRITE_REG page\n");
}

void MDrv_Cfg_ChipWrite_RegInit(void)
{
    //(1)main page list
    MDrv_Cfg_Act(CHIP, CHIP_MAIN, MDrv_Cfg_ChipWrite_RegEntry, MDrv_Cfg_ChipWrite_RegEntryPrint);

    //(2)Action function(s)
    MDrv_Cfg_Act(CHIP, WRITE_REG, MDrv_Cfg_ChipWrite_Reg, MDrv_Cfg_ChipWrite_RegPrint);

    //(3)jump to CHIP main page
    MDrv_Cfg_Act(CHIP, WRITE_REG, MDrv_CfgGotoChipMainPage, MDrv_CfgGotoChipMainPagePrint);

    //(4)jump to config system main page
    MDrv_Cfg_Act(CHIP, WRITE_REG, MDrv_CfgGotoCfgMainPage, MDrv_CfgGotoCfgMainPagePrint);
}


void MDrv_Cfg_ChipRead_Reg_I2C(void)
{
    if(MDrv_GetPara(2))
    {
        unsigned short addr;
        unsigned char u8AddrLen,ret;
        unsigned short subaddr;

        st_dbg_cmd_.var[0] = para[0];
        st_dbg_cmd_.var[1] = para[1];

        addr=st_dbg_cmd_.var[0];
        if(st_dbg_cmd_.var[1]==0xffff)
        {
            u8AddrLen=0;
            subaddr=0;
        }
        else if(st_dbg_cmd_.var[1]>0xff)
        {
            u8AddrLen=2;
            subaddr=st_dbg_cmd_.var[1];
        }
        else
        {
            u8AddrLen=1;
            subaddr=st_dbg_cmd_.var[1];
        }

        MDrv_IIC_ReadBytes(addr, u8AddrLen, (U8 *)&subaddr, 1, &ret);

        printf("read device addr 0x%x, sub addr 0x%x, data 0x%x\n",addr,subaddr,ret);
    }
    MDrv_ClearParaTbl();
}

void MDrv_Cfg_ChipRead_Reg_I2CEntry(void)
{
    cfg_level = READ_REG_I2C;
    dynLevel = 1;
    MDrv_Cfg_ChipMenuPrint();
}

void MDrv_Cfg_ChipRead_Reg_I2CPrint(void)
{
    printf("Execute Read_Reg_I2C action. Ex. 000 -0x80(addr) 0x2(subaddr)\n");
}

void MDrv_Cfg_ChipRead_Reg_I2CEntryPrint(void)
{
  printf("Enter Read_Reg_I2C page\n");
}

void MDrv_Cfg_ChipRead_Reg_I2CInit(void)
{
    //(1)main page list
    MDrv_Cfg_Act(CHIP, CHIP_MAIN, MDrv_Cfg_ChipRead_Reg_I2CEntry, MDrv_Cfg_ChipRead_Reg_I2CEntryPrint);

    //(2)Action function(s)
    MDrv_Cfg_Act(CHIP, READ_REG_I2C, MDrv_Cfg_ChipRead_Reg_I2C, MDrv_Cfg_ChipRead_Reg_I2CPrint);

    //(3)jump to CHIP main page
    MDrv_Cfg_Act(CHIP, READ_REG_I2C, MDrv_CfgGotoChipMainPage, MDrv_CfgGotoChipMainPagePrint);

    //(4)jump to config system main page
    MDrv_Cfg_Act(CHIP, READ_REG_I2C, MDrv_CfgGotoCfgMainPage, MDrv_CfgGotoCfgMainPagePrint);
}


void MDrv_Cfg_ChipWrite_Reg_I2C(void)
{
    if(MDrv_GetPara(3))
    {
        unsigned short addr;
        unsigned char u8AddrLen,d;
        unsigned short subaddr;

        st_dbg_cmd_.var[0] = para[0];
        st_dbg_cmd_.var[1] = para[1];
        st_dbg_cmd_.var[2] = para[2];

        addr=st_dbg_cmd_.var[0];
        if(st_dbg_cmd_.var[1]==0xffff)
        {
            u8AddrLen=0;
            subaddr=0;
        }
        else if(st_dbg_cmd_.var[1]>0xff)
        {
            u8AddrLen=2;
            subaddr=st_dbg_cmd_.var[1];
        }
        else
        {
            u8AddrLen=1;
            subaddr=st_dbg_cmd_.var[1];
        }

        d=st_dbg_cmd_.var[2];

        MDrv_IIC_WriteBytes(addr, u8AddrLen, (U8 *)&subaddr, 1, &d);

        printf("write device addr 0x%x, sub addr 0x%x, data 0x%x\n",addr,subaddr,d);
    }
    MDrv_ClearParaTbl();
}

void MDrv_Cfg_ChipWrite_Reg_I2CEntry(void)
{
    cfg_level = WRITE_REG_I2C;
    dynLevel = 1;
    MDrv_Cfg_ChipMenuPrint();
}

void MDrv_Cfg_ChipWrite_Reg_I2CPrint(void)
{
    printf("Execute Write_Reg_I2C action. Ex. 000 -0x80(addr) 0x2(subaddr) 66(data)\n");
}

void MDrv_Cfg_ChipWrite_Reg_I2CEntryPrint(void)
{
  printf("Enter Write_Reg_I2C page\n");
}

void MDrv_Cfg_ChipWrite_Reg_I2CInit(void)
{
    //(1)main page list
    MDrv_Cfg_Act(CHIP, CHIP_MAIN, MDrv_Cfg_ChipWrite_Reg_I2CEntry, MDrv_Cfg_ChipWrite_Reg_I2CEntryPrint);

    //(2)Action function(s)
    MDrv_Cfg_Act(CHIP, WRITE_REG_I2C, MDrv_Cfg_ChipWrite_Reg_I2C, MDrv_Cfg_ChipWrite_Reg_I2CPrint);

    //(3)jump to CHIP main page
    MDrv_Cfg_Act(CHIP, WRITE_REG_I2C, MDrv_CfgGotoChipMainPage, MDrv_CfgGotoChipMainPagePrint);

    //(4)jump to config system main page
    MDrv_Cfg_Act(CHIP, WRITE_REG_I2C, MDrv_CfgGotoCfgMainPage, MDrv_CfgGotoCfgMainPagePrint);
}


void MDrv_Cfg_ChipRead_Multi_Reg_I2C(void)
{
    if(MDrv_GetPara(3) )
    {
        unsigned short addr,i;
        unsigned char u8AddrLen,ret[MAX_MSG_LEN];
        unsigned short subaddr;

        st_dbg_cmd_.var[0] = para[0];
        st_dbg_cmd_.var[1] = para[1];
        st_dbg_cmd_.var[2] = para[2];

        addr=st_dbg_cmd_.var[0];
        if(st_dbg_cmd_.var[1]==0xffff)
        {
            u8AddrLen=0;
            subaddr=0;
        }
        else if(st_dbg_cmd_.var[1]>0xff)
        {
            u8AddrLen=2;
            subaddr=st_dbg_cmd_.var[1];
        }
        else
        {
            u8AddrLen=1;
            subaddr=st_dbg_cmd_.var[1];
        }

        MDrv_IIC_ReadBytes(addr, u8AddrLen, (U8 *)&subaddr, st_dbg_cmd_.var[2], ret);

        printf("read device addr 0x%x\n",addr);
        for(i=0;i<st_dbg_cmd_.var[2];i++)
            printf("sub addr 0x%x, data 0x%x\n",subaddr+i,ret[i]);
    }
    MDrv_ClearParaTbl();
}

void MDrv_Cfg_ChipRead_Multi_Reg_I2CEntry(void)
{
    cfg_level = READ_MULTI_REG_I2C;
    dynLevel = 1;
    MDrv_Cfg_ChipMenuPrint();
}

void MDrv_Cfg_ChipRead_Multi_Reg_I2CPrint(void)
{
    printf("Execute Read_Multi_Reg_I2C action. Ex. 000 -0x80(addr) 0x02(subaddr) 15(read length)\n");
}

void MDrv_Cfg_ChipRead_Multi_Reg_I2CEntryPrint(void)
{
  printf("Enter Read_Multi_Reg_I2C page\n");
}

void MDrv_Cfg_ChipRead_Multi_Reg_I2CInit(void)
{
    //(1)main page list
    MDrv_Cfg_Act(CHIP, CHIP_MAIN, MDrv_Cfg_ChipRead_Multi_Reg_I2CEntry, MDrv_Cfg_ChipRead_Multi_Reg_I2CEntryPrint);

    //(2)Action function(s)
    MDrv_Cfg_Act(CHIP, READ_MULTI_REG_I2C, MDrv_Cfg_ChipRead_Multi_Reg_I2C, MDrv_Cfg_ChipRead_Multi_Reg_I2CPrint);

    //(3)jump to CHIP main page
    MDrv_Cfg_Act(CHIP, READ_MULTI_REG_I2C, MDrv_CfgGotoChipMainPage, MDrv_CfgGotoChipMainPagePrint);

    //(4)jump to config system main page
    MDrv_Cfg_Act(CHIP, READ_MULTI_REG_I2C, MDrv_CfgGotoCfgMainPage, MDrv_CfgGotoCfgMainPagePrint);
}

void MDrv_Cfg_ChipWrite_Mulit_Reg_I2C(void)
{
    if(MDrv_GetPara(3))
    {
        unsigned short addr,i;
        unsigned char u8AddrLen,d[MAX_MSG_LEN];
        unsigned short subaddr;

        st_dbg_cmd_.var[0] = para[0];
        st_dbg_cmd_.var[1] = para[1];
        st_dbg_cmd_.varnum = para[2];

        addr=st_dbg_cmd_.var[0];
        if(st_dbg_cmd_.var[1]==0xffff)
        {
            u8AddrLen=0;
            subaddr=0;
        }
        else if(st_dbg_cmd_.var[1]>0xff)
        {
            u8AddrLen=2;
            subaddr=st_dbg_cmd_.var[1];
        }
        else
        {
            u8AddrLen=1;
            subaddr=st_dbg_cmd_.var[1];
        }

        for(i=0;i<st_dbg_cmd_.varnum;i++)
        {
            st_dbg_cmd_.var[i+2] = para[i+3];
            d[i]=st_dbg_cmd_.var[i+2];
        }
        MDrv_IIC_WriteBytes(addr, u8AddrLen, (U8 *)&subaddr, st_dbg_cmd_.varnum-2, d);

        printf("write device addr 0x%x\n",addr);

        for(i=0;i<st_dbg_cmd_.varnum;i++)
            printf("sub addr 0x%x, data 0x%x\n",subaddr+i,d[i]);
    }
    MDrv_ClearParaTbl();
}

void MDrv_Cfg_ChipWrite_Mulit_Reg_I2CEntry(void)
{
    cfg_level = WRITE_MULTI_REG_I2C;
    dynLevel = 1;
    MDrv_Cfg_ChipMenuPrint();
}

void MDrv_Cfg_ChipWrite_Mulit_Reg_I2CPrint(void)
{
    printf("Execute Write_Mulit_Reg_I2C action. Ex. 000 -0x80(addr) 0x2(subaddr) 2(num) 70(data1) 80(data2)\n");
}

void MDrv_Cfg_ChipWrite_Mulit_Reg_I2CEntryPrint(void)
{
  printf("Enter Write_Mulit_Reg_I2C page\n");
}

void MDrv_Cfg_ChipWrite_Mulit_Reg_I2CInit(void)
{
    //(1)main page list
    MDrv_Cfg_Act(CHIP, CHIP_MAIN, MDrv_Cfg_ChipWrite_Mulit_Reg_I2CEntry, MDrv_Cfg_ChipWrite_Mulit_Reg_I2CEntryPrint);

    //(2)Action function(s)
    MDrv_Cfg_Act(CHIP, WRITE_MULTI_REG_I2C, MDrv_Cfg_ChipWrite_Mulit_Reg_I2C, MDrv_Cfg_ChipWrite_Mulit_Reg_I2CPrint);

    //(3)jump to CHIP main page
    MDrv_Cfg_Act(CHIP, WRITE_MULTI_REG_I2C, MDrv_CfgGotoChipMainPage, MDrv_CfgGotoChipMainPagePrint);

    //(4)jump to config system main page
    MDrv_Cfg_Act(CHIP, WRITE_MULTI_REG_I2C, MDrv_CfgGotoCfgMainPage, MDrv_CfgGotoCfgMainPagePrint);
}

void MDrv_Cfg_ChipMap_Bank(void)
{
    if(MDrv_GetPara(1) )
    {
        unsigned short addr,data,i;
        char bankmap[17][60]={
        "r/c  00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f\n",
        "00   ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n",
        "01   ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n",
        "02   ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n",
        "03   ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n",
        "04   ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n",
        "05   ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n",
        "06   ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n",
        "07   ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n",
        "08   ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n",
        "09   ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n",
        "0a   ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n",
        "0b   ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n",
        "0c   ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n",
        "0d   ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n",
        "0e   ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n",
        "0f   ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n"};
        unsigned char buf[256],j,k;

        st_dbg_cmd_.var[0] = para[0];
        if(para[1] != 0)
        {
            st_dbg_cmd_.varnum = 1;
        }
        st_dbg_cmd_.var[1] = para[1];

        if(st_dbg_cmd_.var[0]>0xff)
            printf("bank error\n");
        else
            printf("read bank 0x%x\n",st_dbg_cmd_.var[0]);

        addr=st_dbg_cmd_.var[0]<<8;

        if(st_dbg_cmd_.varnum>0)
        {
            data=st_dbg_cmd_.var[1]; //sub bank
            MDrv_WriteByte(addr,data);
        }
        for(i=0;i<256;i++)
        {
            buf[i]=MDrv_ReadByte(addr+i);
            DEBUG_INFO(printf("read add 0x%04x,data 0x%02x\n",addr+i,buf[i]));
        }

        for(i=1;i<17;i++)
            for(j=0;j<16;j++)
            {
               k=(buf[(i-1)*16+j]>>4)&0x0f;
               bankmap[i][j*3+5]=(k>=10)?(k-10+'a'):(k+'0');
               k=buf[(i-1)*16+j]&0x0f;
               bankmap[i][j*3+6]=(k>=10)?(k-10+'a'):(k+'0');
            }

        for(i=0;i<17;i++)
            printf("%s",bankmap[i]);
    }
    MDrv_ClearParaTbl();
}

void MDrv_Cfg_ChipMap_BankEntry(void)
{
    cfg_level = MAP_BANK;
    dynLevel = 1;
    MDrv_Cfg_ChipMenuPrint();
}

void MDrv_Cfg_ChipMap_BankPrint(void)
{
    printf("Execute Map_Bank action. Ex. 000 -0x33(bank) 0x55(subbank data)\n");
}

void MDrv_Cfg_ChipMap_BankEntryPrint(void)
{
  printf("Enter Map_Bank page\n");
}

void MDrv_Cfg_ChipMap_BankInit(void)
{
    //(1)main page list
    MDrv_Cfg_Act(CHIP, CHIP_MAIN, MDrv_Cfg_ChipMap_BankEntry, MDrv_Cfg_ChipMap_BankEntryPrint);

    //(2)Action function(s)
    MDrv_Cfg_Act(CHIP, MAP_BANK, MDrv_Cfg_ChipMap_Bank, MDrv_Cfg_ChipMap_BankPrint);

    //(3)jump to CHIP main page
    MDrv_Cfg_Act(CHIP, MAP_BANK, MDrv_CfgGotoChipMainPage, MDrv_CfgGotoChipMainPagePrint);

    //(4)jump to config system main page
    MDrv_Cfg_Act(CHIP, MAP_BANK, MDrv_CfgGotoCfgMainPage, MDrv_CfgGotoCfgMainPagePrint);
}

#endif //ENABLE_MSTV_UART_DEBUG
