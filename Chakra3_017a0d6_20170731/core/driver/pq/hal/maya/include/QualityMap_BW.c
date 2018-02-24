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

///// Table Utility
#define REG_TABLE_END 0xFFFF

#define BW_REG(reg) ((reg>>8)&0xFF), (reg&0xFF)
#define REG(reg)                ((reg>>8)&0xFF), (reg&0xFF)

#define REG_ADDR_SIZE   2
#define REG_MASK_SIZE   1
#define REG_BANK_SIZE   1

///// Table
#include "Maya_Bandwidth_RegTable.h"
#include "Maya_Bandwidth_RegTable.c"
///// Dumper
///// Different dumper for different table
static void _MDrv_BW_DumpTable(TAB_Info* ptab_Info)
{

    MS_U16 u16Addr;
    MS_U8 u8Bank;
    MS_U8 u8Mask;
    MS_U8 u8Value;
    MS_U8 u8BankGOP_Bak;

    if (ptab_Info->pIPTable == NULL){
        return;
    }

    if (ptab_Info->u8TabIdx >= ptab_Info->u8TabNums){
        MS_ASSERT(0);
        return;
    }

    u8BankGOP_Bak = MApi_XC_ReadByte(REG_GOP_BANK) & 0x0F;

    while (1)
    {

        u16Addr = (ptab_Info->pIPTable[0]<<8) + ptab_Info->pIPTable[1];
        u8Bank    = ptab_Info->pIPTable[2];
        u8Mask    = ptab_Info->pIPTable[3];
        u8Value = ptab_Info->pIPTable[REG_ADDR_SIZE+REG_BANK_SIZE+REG_MASK_SIZE+ptab_Info->u8TabIdx];

        if (u16Addr == _END_OF_TBL_) // check end of table
            break;

        if ((u16Addr >> 8 ) == 0x1F)     // GOP
        {
            if (( MApi_XC_ReadByte(REG_GOP_BANK) & 0x0F) != u8Bank)
            {
                MApi_XC_WriteByteMask(REG_GOP_BANK,u8Bank,0x0F);
            }
        }

        if ((u16Addr >> 8) == 0x2F)  // Scaler
        {
            if (u16Addr % 2) // Odd address
            {
                MApi_XC_W2BYTEMSK( ( (MS_U16)u8Bank << 8 ) | ( (u16Addr & 0x00FF) - 1 ) ,(MS_U16)u8Value << 8 ,(MS_U16)u8Mask << 8);
            }
            else
            {
                MApi_XC_W2BYTEMSK( ( (MS_U16)u8Bank << 8 ) | ( (u16Addr & 0x00FF) ) ,(MS_U16)u8Value ,(MS_U16)u8Mask );
            }
        }
        else //Others
        {
        	if (u8Bank == 0x16)
        	{
        	    MApi_XC_WriteByteMask( (MS_U32)(u8Bank<<16 | u16Addr) ,u8Value,u8Mask);
        	}
		    else
		    {
            	MApi_XC_WriteByteMask( (MS_U32)u16Addr + 0x100000 ,u8Value,u8Mask);
		    }
        }

        //BW_DBG(printk("[addr=%06x, bank=%02x, msk=%04x, val=%04x]\n", u16Addr, u8Bank, u8Mask, u8Value));
        //print("[addr=%06x, bank=%02x, msk=%04x, val=%04x]\n", u16Addr, u8Bank, u8Mask, u8Value);

        ptab_Info->pIPTable+=(REG_ADDR_SIZE+REG_BANK_SIZE+REG_MASK_SIZE+ptab_Info->u8TabNums); // next
    }

    MApi_XC_WriteByteMask(REG_GOP_BANK,u8BankGOP_Bak,0x0F);

}
