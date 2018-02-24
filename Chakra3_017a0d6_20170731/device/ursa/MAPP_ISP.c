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
/******************************************************************************
 Copyright (c) 2005 MStar Semiconductor, Inc.
 All rights reserved.

 [Module Name]:
 [Date]:
 [Comment]:
 [Reversion History]:
*******************************************************************************/
#define _FLASHWR_C_
// System

// Common
#include <string.h>
#include "Board.h"
#include "datatype.h"

// External
#include "msAPI_Timer.h"
#include "drvSYS.h"

// Internal
#include "MApp_Isp.h"
#include "Panel.h"
#include "msAPI_BDMA.h"
#include "SysInit.h"
#include "msAPI_Timer.h"
#include "msAPI_MIU.h"
#include "drvIIC.h"

#define   ENABLE_URSA_ISP   1
#define   ENABLE_WATCH_DOG  1

#if (ENABLE_URSA_ISP)
//------------------------------------------------------------------------------
#define SPI_WRITE           0x10
#define SPI_READ            0x11
#define SPI_STOP            0x12

#define SLAVEADDR          0x94//0x98
#define SERIALDEBUGADDR   0xB8//0xB4
//slave: 0x98 / 0xB4
//mster 0x94 //0xB8
#define cCmdDataWrite 0x10

#define BANKSIZE    0x10000
#define BLOCKNUM  0xff
#define BLOCKSIZE 0x100

#define ENTER_ISP_ERROR_MAX     20
#define GET_ID_ERROR_MAX        10

//------------------------------------------------------------------------------
typedef enum _FlashType
{
    Flash_PMC512,//PMC
    Flash_PMC010,
    Flash_PMC020,
    Flash_PMC040,
    Flash_EN25P10,//EON
    Flash_EN25P20,
    Flash_EN25P40,
    Flash_EN25P80,
    Flash_EN25F40,
    Flash_EN25F80,
    Flash_EN25F16,
    Flash_EN25P16,
    Flash_EN25B20,
    Flash_EN25B40,
    Flash_EN25B40T,
    Flash_EN25B16,
    Flash_EN25B16T,
    Flash_EN25B32,
    Flash_S25FL004A,//SPANSION
    Flash_S25FL016A,
    Flash_S25FL040A,
    Flash_NX25P16,//Winbond & NX
    Flash_W25X10,//not test
    Flash_W25X20,//not test
    Flash_W25X40,//not test
    Flash_W25P20,//not test
    Flash_W25P40,
    Flash_W25X16,
    Flash_W25X32,
    Flash_W25X64,
    Flash_SST25VF016B,//SST
    Flash_SST25VF040B,//not test
    Flash_MX25L4005A,//MX
    Flash_MX25L8005,//MX
    Flash_MX25L2005,//not test
    Flash_MX25L1605,
    Flash_MX25L3205,
    Flash_MX25L6405,
    Flash_QB25F160S,//intel QB25F160S33B8
    Flash_QB25F320S,//intel QB25F320S33B8
    Flash_QB25F640S,//intel QB25F640S33B8
    Flash_A25L40P,//AMIC A25L40P
    Flash_A25L040P,//AMIC A25L40P
    Flash_NUMS,
} FlashType;

typedef struct
{
    DWORD size;				// 1-4
    BYTE manufacturer_id;	// 5
    BYTE device_id;			// 6

    // command
    BYTE WREN;				// 7
    BYTE WRDI;				// 8
    BYTE RDSR;				// 9
    BYTE WRSR;				// 10
    BYTE READS;				// 11
    BYTE FAST_READ;			// 12
    BYTE PG_PROG;			// 13
    BYTE SECTOR_ERASE;		// 14
    BYTE BLOCK_ERASE;		// 15
    BYTE CHIP_ERASE;		// 16
    BYTE RDID;				// 17
    BYTE LOCK;              // 18
    WORD ChipEraseMaxTime;  // 19-20//Unit:100ms
} SFlashType;

BYTE g_ucFlashType;
BYTE g_ucBankNumber;
SFlashType sFlash;

U8 g_u8CurPercent;
U32 g_u32ISPSrcAddr;
U32 g_u32ISPCodeSize;
FlashProgErrorType ErrorFlag;
FlashProgStateType g_eFlashProgramState;

//------------------------------------------------------------------------------
#define FlashDebug
#ifdef 	FlashDebug
#define FLashPutstr(str)      printf(str)
#define FLashPrintf(str,para) printf(str,para)
#else
#define FLashPutstr(str)
#define FLashPrintf(str,para)
#endif

//------------------------------------------------------------------------------
code SFlashType SupportSFlash[Flash_NUMS]=
{
// 1-4:size ,5:manufacturer_id,6:device_id,7:WREN,8:WRDI,9:RDSR,10:WRSR,11:READ,12:FAST_READ,
// 13:PG_PROG,14:SECTOR_ERASE,15:BLOCK_ERASE,16:CHIP_ERASE,17:RDID,18:LOCK,19-20: ChipEraseMaxTime

//                    1-4    ,5   ,6   ,7   ,8   ,9   ,10  ,11  ,12  ,13  ,14  ,15  ,16  ,17  ,18  ,19-20
//PMC
{/*"PMC25LV512A", */  0x20000,0x9D,0x7B,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD7,0xD8,0xC7,0xAB,0x0C,40  },
{/*" PMC25LV010", */  0x20000,0x9D,0x7C,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD7,0xD8,0xC7,0xAB,0x0C,40  },
{/*" PMC25LV020", */  0x40000,0x9D,0x7D,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD7,0xD8,0xC7,0xAB,0x0C,40  },
{/*" PMC25LV040", */  0x80000,0x9D,0x7E,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD7,0xD8,0xC7,0xAB,0x1C,40  },
//EON
{/*"    EN25P10", */  0x20000,0x1C,0x10,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x0C,80  },
{/*"    EN25P20", */  0x40000,0x1C,0x11,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x0C,80  },
{/*"    EN25P40", */  0x80000,0x1C,0x12,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,80  },
{/*"    EN25P80", */  0x100000,0x1C,0x13,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,80  },
{/*"    EN25F40", */  0x80000,0x1C,0x12,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,80  },
{/*"    EN25F80", */  0x100000,0x1C,0x13,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,220  },
{/*"    EN25F16", */  0x200000,0x1C,0x14,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,440  },
{/*"    EN25P16", */  0x80000,0x1C,0x14,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,220 },
{/*"    EN25B20", */  0x40000,0x1C,0x41,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x0C,80  },
{/*"    EN25B40", */  0x80000,0x1C,0x42,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,80  },
{/*"   EN25B40T", */  0x80000,0x1C,0x42,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,80  },
{/*"    EN25B16", */  0x80000,0x1C,0x34,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,220 },
{/*"   EN25B16T", */  0x80000,0x1C,0x34,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,220 },
{/*"    EN25B32", */  0x80000,0x1C,0x35,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,440 },
//                    1-4    ,5   ,6   ,7   ,8   ,9   ,10  ,11  ,12  ,13  ,14  ,15  ,16  ,17  ,18  ,19-20
//SPANSION
{/*"  S25FL004A", */  0x80000,0x01,0x12,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,260 },
{/*"  S25FL016A", */0x1000000,0x01,0x14,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,1000},
{/*"  S25FL040A", */  0x80000,0x01,0x25,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,260 },
//Winbond & NX
{/*"    NX25P16", */0x1000000,0xEF,0x15,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,250 },
{/*"     W25X10", */  0x20000,0xEF,0x10,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x0C,70  },
{/*"     W25X20", */  0x40000,0xEF,0x51,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,250 },
{/*"     W25X40", */  0x80000,0xEF,0x52,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,250 },
{/*"     W25P20", */  0x40000,0xEF,0x11,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,250 },
{/*"     W25P40", */  0x80000,0xEF,0x12,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,250 },
{/*"     W25X16", */  0x20000,0xEF,0x14,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x0C,256  },
{/*"     W25X32", */  0x40000,0xEF,0x15,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,512 },
{/*"     W25X64", */  0x80000,0xEF,0x16,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,1000 },
//SST
{/*"SST25VF016B", */0x1000000,0xBF,0x41,0x06,0x04,0x05,0x01,0x03,NULL,0xAD,0xD8,0xD8,0xC7,0xAB,0x1C,40  },
{/*"SST25VF040B", */  0x80000,0xBF,0x8D,0x06,0x04,0x05,0x01,0x03,NULL,0xAD,0xD8,0xD8,0xC7,0xAB,0x1C,40  },
//MX
{/*" MX25L4005A", */  0x80000,0xC2,0x12,0x06,0x04,0x05,0x01,0x03,0x0B,0x02,0x20,0xD8,0xC7,0xAB,0x1C,80  },
{/*" MX25L8005", */  0x100000,0xC2,0x13,0x06,0x04,0x05,0x01,0x03,0x0B,0x02,0x20,0xD8,0xC7,0xAB,0x1C,160  },
{/*"  MX25L2005", */  0x40000,0xC2,0x11,0x06,0x04,0x05,0x01,0x03,0x0B,0x02,0x20,0xD8,0xC7,0xAB,0x1C,50  },
{/*"  MX25L1605", */0x1000000,0xC2,0x14,0x06,0x04,0x05,0x01,0x03,0x0B,0x02,0x20,0xD8,0xC7,0xAB,0x1C,550 },
{/*"  MX25L3205", */0x1000000,0xC2,0x15,0x06,0x04,0x05,0x01,0x03,0x0B,0x02,0x20,0xD8,0xC7,0xAB,0x1C,750 },
{/*"  MX25L6405", */0x1000000,0xC2,0x16,0x06,0x04,0x05,0x01,0x03,0x0B,0x02,0x20,0xD8,0xC7,0xAB,0x1C,1000 },
//INTEL
{/*"QB25F160S33B8", */  0x20000,0x89,0x11,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD7,0xD8,0xC7,0xAB,0x0C,128  },
{/*"QB25F320S33B8", */  0x40000,0x89,0x12,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD7,0xD8,0xC7,0xAB,0x0C,256  },
{/*"QB25F640S33B8", */  0x80000,0x89,0x13,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD7,0xD8,0xC7,0xAB,0x1C,512  },
//AMIC
{/*" A25L40P", */  0x80000,0x37,0x13,0x06,0x04,0x05,0x01,0x03,0x0B,0x02,0x20,0xD8,0xC7,0xAB,0x1C,128  },
};

//------------------------------------------------------------------------------
#define  SW_IIC_READ             0
#define  SW_IIC_WRITE            1

//------------------------------------------------------------------------------
void I2cReadDatas(BYTE * paddr, BYTE addrSize, BYTE * pdatabuf, BYTE dataSize)
{
    BYTE k;
    MApi_SWI2C_UseBus(URSA_I2C_BUS_SEL);

    if(MApi_SWI2C_AccessStart(SLAVEADDR, SW_IIC_WRITE)==FALSE)
    {
    	FLashPutstr("\n6M30->I2cReadDatas->IIC_AccessStart Error");
    }

    for(k=0;k<addrSize;k++)
    {
       if(MApi_SWI2C_SendByte(paddr[k])==FALSE)
	{
    		FLashPutstr("\n6M30->I2cReadDatas paddr Error");
    	}
    }

    if(MApi_SWI2C_AccessStart(SLAVEADDR, SW_IIC_READ)==FALSE)
    {
	    FLashPutstr("\n6M30->I2cReadDatas->IIC_AccessReStart Error");
    }

    for(k=0;k<dataSize-1;k++)
    {
       pdatabuf[k]=MApi_SWI2C_GetByte(1);
    }
    //last byte
    pdatabuf[k]=MApi_SWI2C_GetByte(0);

    MApi_SWI2C_Stop();
}

void I2cWriteDatas(BYTE * paddr, BYTE addrSize, BYTE * pdatabuf, BYTE dataSize)
{
    BYTE k;
    MApi_SWI2C_UseBus(URSA_I2C_BUS_SEL);

    if(MApi_SWI2C_AccessStart(SLAVEADDR, SW_IIC_WRITE)==FALSE)
	{
    	FLashPutstr("\n6M30->I2cWriteDatas->IIC_AccessStart Error");
	}

    for(k=0;k<addrSize;k++)
	{
        if(MApi_SWI2C_SendByte(paddr[k])==FALSE)
		{
    		FLashPutstr("\n6M30->paddr Error");
    	}

	}

    for(k=0;k<dataSize;k++)
    {
        if(MApi_SWI2C_SendByte(pdatabuf[k])==FALSE)
    	{
    		FLashPutstr("\n6M30->pdatabuf Error");
    	}
    }

    MApi_SWI2C_Stop();
}

void I2cWriteStop(void)
{
    MApi_SWI2C_UseBus(URSA_I2C_BUS_SEL);

    if(MApi_SWI2C_AccessStart(SLAVEADDR, SW_IIC_WRITE)==FALSE)
	{
	   FLashPutstr("\n6M30->I2cWriteStop->IIC_AccessStart Error");
	}
    if(MApi_SWI2C_SendByte(SPI_STOP)==FALSE)
	{
	   FLashPutstr("\n6M30->I2cWriteStop-> Error");
	}
    MApi_SWI2C_Stop();
}

void I2cCommondRead(void)
{
    MApi_SWI2C_UseBus(URSA_I2C_BUS_SEL);

    if(MApi_SWI2C_AccessStart(SLAVEADDR, SW_IIC_WRITE)==FALSE)
	{
	 FLashPutstr("\n6M30->I2cCommondRead Error");
    }
    if(MApi_SWI2C_SendByte(SPI_READ)==FALSE)
	{
	FLashPutstr("\n6M30->I2cCommondRead-> SPI_READ");
	}
}

BYTE ReadChipID(void)
{
    code BYTE ReadIDCommand[]={SPI_WRITE,0xAB,0x00,0x00,0x00};
    BYTE buf;

    I2cWriteDatas(ReadIDCommand,sizeof(ReadIDCommand),NULL,0);

    buf=SPI_READ; //Manufacture ID
    I2cReadDatas(&buf,1,&buf,1);

    buf=SPI_READ; //Device ID1
    I2cReadDatas(&buf,1,&buf,1);

    buf=SPI_READ; //Device ID2
    I2cReadDatas(&buf,1,&buf,1);

    I2cWriteStop();
    return buf;
}

BYTE ReadChipIDBuffer(BYTE *ReadIDBuf)
{
    code BYTE ReadIDCommand[]={SPI_WRITE,0xAB,0x00,0x00,0x00};
    BYTE buf;

    I2cWriteDatas(ReadIDCommand,sizeof(ReadIDCommand),NULL,0);

    buf=SPI_READ; //Manufacture ID
    I2cReadDatas(&buf,1,&ReadIDBuf[0],1);

    buf=SPI_READ; //Device ID1
    I2cReadDatas(&buf,1,&ReadIDBuf[1],1);

    buf=SPI_READ; //Device ID2
    I2cReadDatas(&buf,1,&ReadIDBuf[2],1);

    I2cWriteStop();
    return buf;
}

BYTE ReadChipJEDEC_ID(BYTE *ReadIDBuf)
{
    code BYTE ReadIDCommand[]={SPI_WRITE,0x9f};

    BYTE buf;

    I2cWriteDatas(ReadIDCommand,sizeof(ReadIDCommand),NULL,0);

    buf=SPI_READ; //Manufacture ID
    I2cReadDatas(&buf,1,&ReadIDBuf[0],1);

    buf=SPI_READ; //Device ID1
    I2cReadDatas(&buf,1,&ReadIDBuf[1],1);

    buf=SPI_READ; //Device ID2
    I2cReadDatas(&buf,1,&ReadIDBuf[2],1);

    I2cWriteStop();
    return buf;
}

BOOLEAN GetsFlashType(void)
{
    BYTE temp;
    BYTE ucTmpBuf[4]={0};

    ReadChipJEDEC_ID(ucTmpBuf);
    FLashPrintf("\n***ReadChipJEDEC_ID[%x]",ucTmpBuf[0]);
    switch(ucTmpBuf[0])
    {
        case 0x37:
            FLashPutstr("\n  AL or AMIC");
            temp=ReadChipID();
            FLashPrintf("\n  AL or AMIC ChipID=%x",temp);
            if (temp == 0x12)
            {
                g_ucFlashType=Flash_A25L40P;
                g_ucBankNumber=8;
                printf("\n   A25L40P");
            }
            else
            {
                return FALSE;
            }
            break;
    ///////////////////////////////////////////////

        //PMC
        case 0x7F:
            FLashPutstr("\n  PMC or AMIC");
            temp=ReadChipID();
            FLashPrintf("\n  PMC or AMIC ChipID=%x",temp);
            if (temp == 0x7C)
            {
                g_ucFlashType=Flash_PMC010;
                g_ucBankNumber=2;
            }
            else if (temp == 0x7D)
            {
                g_ucFlashType=Flash_PMC020;
                g_ucBankNumber=4;
            }
            else if (temp == 0x7E)
            {
                g_ucFlashType=Flash_PMC040;
                g_ucBankNumber=8;
            }
            else if (temp == 0x12)
            {
                g_ucFlashType=Flash_A25L40P;
                g_ucBankNumber=8;
                FLashPutstr("\n   A25L40P");
            }
            else
            {
                return FALSE;
            }
            break;
        //EON
        case 0x1C:
            FLashPutstr("\n  EON");
            temp=ReadChipID();
            FLashPrintf("\n  EON ChipID=%x",temp);
            if (ucTmpBuf[2] == 0x20)
            {
                if (ucTmpBuf[1] == 0x11 && temp == 0x10)
                {
                    g_ucFlashType = Flash_EN25P10;
                    g_ucBankNumber=2;
                    FLashPutstr("\n   EN25P10");
                }
                else if (ucTmpBuf[1] == 0x12 && temp == 0x11)
                {
                    g_ucFlashType = Flash_EN25P20;
                    g_ucBankNumber=4;
                    FLashPutstr("\n   EN25P20");
                }
                else if (ucTmpBuf[1] == 0x13 && temp == 0x12)
                {
                    g_ucFlashType = Flash_EN25P40;
                    g_ucBankNumber=8;
                    FLashPutstr("\n   EN25P40");
                }
                else if (ucTmpBuf[1] == 0x14 && temp == 0x13)
                {
                    g_ucFlashType = Flash_EN25P80;
                    g_ucBankNumber=16;
                    FLashPutstr("\n   EN25P80");
                }
                else if (ucTmpBuf[1] == 0x12 && temp == 0x41)
                {
                    g_ucFlashType = Flash_EN25B20;
                    g_ucBankNumber=4;
                    FLashPutstr("\n   EN25B20");
                }
                else if (ucTmpBuf[1] == 0x13 && temp == 0x32)
                {
                    g_ucFlashType = Flash_EN25B40;
                    g_ucBankNumber=8;
                    FLashPutstr("\n   EN25B40");
                }
                else if (ucTmpBuf[1] == 0x13 && temp == 0x42)
                {
                    g_ucFlashType = Flash_EN25B40T;
                    g_ucBankNumber=8;
                    FLashPutstr("\n   EN25B40T");
                }
                else if (ucTmpBuf[1] == 0x15 && temp == 0x14)
                {
                    g_ucFlashType = Flash_EN25P16;
                    g_ucBankNumber = 32;
                    FLashPutstr("\n   EN25P16");
                }
                else if (ucTmpBuf[1] == 0x15 && temp == 0x34)
                {
                    g_ucFlashType = Flash_EN25B16;
                    g_ucBankNumber = 32;
                    FLashPutstr("\n   EN25B16");
                }
                else if (ucTmpBuf[1] == 0x15 && temp == 0x44)
                {
                    g_ucFlashType = Flash_EN25B16T;
                    g_ucBankNumber = 32;
                    FLashPutstr("\n   EN25B16T");
                }
                else if (ucTmpBuf[1] == 0x16 && temp == 0x35)
                {
                    g_ucFlashType = Flash_EN25B32;
                    g_ucBankNumber = 64;
                    FLashPutstr("\n   EN25B32");
                }
                else
                {
                    return FALSE;
                }
            }
            else if (ucTmpBuf[2] == 0x31)
            {
                if (ucTmpBuf[1] == 0x13 && temp == 0x12)
                {
                    g_ucFlashType = Flash_EN25F40;
                    g_ucBankNumber=8;
                    FLashPutstr("\n   EN25F40");
                }
                else if (ucTmpBuf[1] == 0x14 && temp == 0x13)
                {
                    g_ucFlashType = Flash_EN25F80;
                    g_ucBankNumber=16;
                    FLashPutstr("\n   EN25F80");
                }
                else if (ucTmpBuf[1] == 0x15 && temp == 0x14)
                {
                    g_ucFlashType = Flash_EN25F16;
                    g_ucBankNumber=32;
                    FLashPutstr("\n   EN25F16");
                }
            }
            else
            {
                return FALSE;
            }
            break;
        case 0x01:
            FLashPutstr("\n  SPANSION");
            FLashPrintf("\n   chip ID=%x",ucTmpBuf[1]);
            if (ucTmpBuf[1] == 0x14)
            {
                g_ucFlashType = Flash_S25FL016A;
                g_ucBankNumber = 32;
                FLashPutstr("\n   S25FL016A");
            }
            else if (ucTmpBuf[1] == 0x12)
            {
                g_ucFlashType = Flash_S25FL004A;
                g_ucBankNumber = 8;
                FLashPutstr("\n   S25FL004A");
            }
            else if (ucTmpBuf[1] == 0x25)
            {
                g_ucFlashType = Flash_S25FL040A;
                g_ucBankNumber = 8;
                FLashPutstr("\n   S25FL040A");
            }
            else
            {
                return FALSE;
            }
            break;
        case 0xEF:
            FLashPutstr("\n  WINBOND & NX");
            if (ucTmpBuf[1] == 0x15 && ucTmpBuf[2] == 0x20)
            {
                g_ucFlashType = Flash_NX25P16;
                g_ucBankNumber = 32;
                FLashPutstr("\n   NX25P16 or W25P16");
            }
            else if (ucTmpBuf[1] == 0x11 && ucTmpBuf[2] == 0x30)
            {
                g_ucFlashType = Flash_W25X10;
                g_ucBankNumber = 2;
                FLashPutstr("\n   W25X10");
            }
            else if (ucTmpBuf[1] == 0x12 && ucTmpBuf[2] == 0x30)
            {
                g_ucFlashType = Flash_W25X20;
                g_ucBankNumber = 4;
                FLashPutstr("\n   W25X20");
            }
            else if (ucTmpBuf[1] == 0x13 && ucTmpBuf[2] == 0x30)
            {
                g_ucFlashType = Flash_W25X40;
                g_ucBankNumber = 8;
                FLashPutstr("\n   W25X40");
            }
            else if (ucTmpBuf[1] == 0x15 && ucTmpBuf[2] == 0x00)
            {
                g_ucFlashType = Flash_W25X16;
                g_ucBankNumber = 32;
                FLashPutstr("\n   W25X16");
            }
            else if (ucTmpBuf[1] == 0x16 && ucTmpBuf[2] == 0x00)
            {
                g_ucFlashType = Flash_W25X32;
                g_ucBankNumber = 64;
                FLashPutstr("\n   W25X32");
            }
            else if (ucTmpBuf[1] == 0x17 && ucTmpBuf[2] == 0x00)
            {
                g_ucFlashType = Flash_W25X64;
                g_ucBankNumber = 128;
                FLashPutstr("\n   W25X64");
            }
            else
            {
                temp=ReadChipID();
                FLashPrintf("\n ID 2:%x",temp);
                if (temp == 0x51)
                {//because some W25X20 have no ucTmpBuf[2](=0x00)
                    g_ucFlashType = Flash_W25X20;
                    g_ucBankNumber = 4;
                    FLashPutstr("\n   W25X20-0");
                }
                else if(temp == 0x10)
                {
                    g_ucFlashType = Flash_W25X10;
                    g_ucBankNumber = 2;
                    FLashPutstr("\n   W25X10-0");
                }
                else if(temp == 0x52)
                {//because some W25X40 have no ucTmpBuf[2](=0x00)
                    g_ucFlashType = Flash_W25X40;
                    g_ucBankNumber = 8;
                    FLashPutstr("\n   W25X40-0");
                }
                else if(temp == 0x11)
                {//because some W25X40 have no ucTmpBuf[2](=0x00)
                    g_ucFlashType = Flash_W25P20;
                    g_ucBankNumber = 4;
                    FLashPutstr("\n   W25P20");
                }
                else if(temp == 0x12)
                {//because some W25X40 have no ucTmpBuf[2](=0x00)
                    g_ucFlashType = Flash_W25P40;
                    g_ucBankNumber = 8;
                    FLashPutstr("\n   W25P40");
                }
                else if(temp == 0x14)
                {
                    g_ucFlashType = Flash_NX25P16;
                    g_ucBankNumber = 32;
                    FLashPutstr("\n   W25P16");
                }
                else
                {
                    return FALSE;
                }
            }
            break;
        case 0xBF:
            FLashPutstr("\n  SST");
            if ((ucTmpBuf[1] == 0x41) & (ucTmpBuf[2] == 0x25))
            {
                g_ucFlashType = Flash_SST25VF016B;
                g_ucBankNumber = 32;
                FLashPutstr("\n   SST25VF016B");
            }
            else if ((ucTmpBuf[1] == 0x8D) & (ucTmpBuf[2] == 0x25))
            {
                g_ucFlashType = Flash_SST25VF040B;
                g_ucBankNumber = 8;
                FLashPutstr("\n   SST25VF040B");
            }
            else
            {
                return FALSE;
            }
            break;
        case 0xC2:
            FLashPutstr("\n MX");

            FLashPrintf("\n JEDEC_ID1 0:%x",ucTmpBuf[0]);
            FLashPrintf("\n JEDEC_ID1 1:%x",ucTmpBuf[1]);
            FLashPrintf("\n JEDEC_ID1 2:%x",ucTmpBuf[2]);

            if ((ucTmpBuf[1] == 0x13) & (ucTmpBuf[2] == 0x20))
            {
                g_ucFlashType = Flash_MX25L4005A;
                g_ucBankNumber = 8;
                FLashPutstr("\n   MX25L4005A");
            }
            else if ((ucTmpBuf[1] == 0x14) & (ucTmpBuf[2] == 0x20))
            {
                g_ucFlashType = Flash_MX25L8005;
                g_ucBankNumber = 16;
                FLashPutstr("\n   MX25L8005");
            }
            else if ((ucTmpBuf[1] == 0x12) & (ucTmpBuf[2] == 0x20))
            {
                g_ucFlashType = Flash_MX25L2005;
                g_ucBankNumber = 4;
                FLashPutstr("\n   MX25L2005");
            }
            else if((ucTmpBuf[1] == 0x15) & (ucTmpBuf[2] == 0x20))
            {
                g_ucFlashType = Flash_MX25L1605;
                g_ucBankNumber = 32;
                FLashPutstr("\n   MX25L1605");
            }
            else if((ucTmpBuf[1] == 0x16) & (ucTmpBuf[2] == 0x20))
            {
                g_ucFlashType = Flash_MX25L3205;
                g_ucBankNumber = 32;
                FLashPutstr("\n   MX25L3205");
            }
            else if((ucTmpBuf[1] == 0x17) & (ucTmpBuf[2] == 0x20))
            {
                g_ucFlashType = Flash_MX25L6405;
                g_ucBankNumber = 128;
                FLashPutstr("\n   MX25L6405");
            }
            else
            {
                return FALSE;
            }
            break;
        //intel
        case 0x89:
            FLashPutstr("\n  INTEL");
            temp=ReadChipID();
            FLashPrintf("\n  INTEL ChipID=%x",temp);
            if (ucTmpBuf[1] == 0x11)
            {
                g_ucFlashType=Flash_QB25F160S;
                g_ucBankNumber=32;
                FLashPutstr("\n   INTS33_16");
            }
            else if (ucTmpBuf[1] == 0x12)
            {
                g_ucFlashType=Flash_QB25F320S;
                g_ucBankNumber=64;
                FLashPutstr("\n   INTS33_32");
            }
            else if (ucTmpBuf[1] == 0x13)
            {
                g_ucFlashType=Flash_QB25F640S;
                g_ucBankNumber=128;
                FLashPutstr("\n   INTS33_64");
            }
            else
            {
                return FALSE;
            }
            break;
        default:
            FLashPrintf("\n JEDEC_ID 0:%x",ucTmpBuf[0]);
            FLashPrintf("\n JEDEC_ID 1:%x",ucTmpBuf[1]);
            FLashPrintf("\n JEDEC_ID 2:%x",ucTmpBuf[2]);
            ReadChipIDBuffer(ucTmpBuf);
            FLashPrintf("\n RDID 0:%x",ucTmpBuf[0]);
            FLashPrintf("\n RDID 1:%x",ucTmpBuf[1]);
            FLashPrintf("\n RDID 2:%x",ucTmpBuf[2]);
            if ((ucTmpBuf[0] == 0x9D) && (ucTmpBuf[1] == 0x7F) && (ucTmpBuf[2] == 0x7B))
            {
                FLashPutstr("\n  PMC-RDID");
                FLashPutstr("\n   PM25LV512A/PM25LV512");
                g_ucFlashType=Flash_PMC512;
                g_ucBankNumber=1;
            }
            else
            {
                return FALSE;
            }
            break;
    }
    ReadChipIDBuffer(ucTmpBuf);
    FLashPrintf("\n RDID1 0:%x",ucTmpBuf[0]);
    FLashPrintf("\n RDID1 1:%x",ucTmpBuf[1]);
    FLashPrintf("\n RDID1 2:%x",ucTmpBuf[2]);
    return TRUE;
}

BOOLEAN EnterIspMode(void)
{
    // 0x4D,0x53,0x54,0x41,0x52
    BYTE enterISPdata[]="MSTAR";
    BYTE addr=0x20;

    // enter isp mode

    I2cWriteDatas(enterISPdata,sizeof(enterISPdata)-1,NULL,0);
    I2cReadDatas(&addr,1,&addr,1);

	if(addr==0xC0)
	{
        FLashPutstr("\nEnterIspMode->OK");
        return TRUE; // enter ok
	}
    else
	{
        FLashPutstr("\nEnterIspMode->fail");
        return FALSE; // enter fail
    }
}

void ExitIspMode(void)
{
    BYTE tdata=0x24;

    // exit isp mode
    FLashPutstr("\n1.ExitIspMode");
    I2cWriteDatas(&tdata,1,NULL,0);
    FLashPutstr("\n2.ExitIspMode");

}

U8 SrcReadFlash(U16 pcount , BYTE BankNum)
{
    U8 u8Data;

    memcpy(&u8Data,(void *)_PA2VA(g_u32ISPSrcAddr+(U32)pcount + (U32)BankNum*0x10000), 1);
    return u8Data;
}

BYTE SFlashRdsr(void)
{
    BYTE buffer[2];

    buffer[0]=SPI_WRITE;
    buffer[1]=sFlash.RDSR;
    I2cWriteDatas(buffer,2,NULL,0);

    buffer[0]=SPI_READ;
    I2cReadDatas(buffer,1,&buffer[1],1);

    I2cWriteStop();

    return buffer[1];
}

BOOLEAN SFlashChecksr(void)
{
    BYTE ucdelay = 10;
    DWORD count=1000;

    while(count--)
    {
        if((SFlashRdsr()&0x01)==0x00)
            return TRUE;
        while(ucdelay--);
    }
    return FALSE;
}

void SFlashWrsr(BYTE tdata)
{
    BYTE buffer[3];

    SFlashChecksr();

    // for sst sflash (sst manufacturer id=0xBF )
    if(sFlash.manufacturer_id==0xBF)
    {
        buffer[0]=SPI_WRITE;
        buffer[1]=0x50;
        I2cWriteDatas(buffer,2,NULL,0);

        I2cWriteStop();
    }

    buffer[0]=SPI_WRITE;
    buffer[1]=sFlash.WRSR;
    buffer[2]=tdata;
    I2cWriteDatas(buffer,sizeof(buffer),NULL,0);

    I2cWriteStop();
}

void SFlashWren(void)
{
    BYTE buffer[2];

    buffer[0]=SPI_WRITE;
    buffer[1]=sFlash.WREN;

    SFlashChecksr();
    I2cWriteDatas(buffer,2,NULL,0);

    I2cWriteStop();
}

/*
void SFlashWrdi(void)
{
    BYTE buffer[2];

    buffer[0]=SPI_WRITE;
    buffer[1]=sFlash.WRDI;

    SFlashChecksr();
    I2cWriteDatas(buffer,2,NULL,0);

    I2cWriteStop();
}
*/

void SFlashWrdi(void)
{
    BYTE buffer[2];

    buffer[0]=SPI_WRITE;
    buffer[1]=sFlash.WRDI;

    SFlashChecksr();
    I2cWriteDatas(buffer,2,NULL,0);

    buffer[0]=SPI_STOP;
    I2cWriteDatas(buffer,1,NULL,0);
}

BOOLEAN I2cReadBlank(DWORD dataSize)
{
    DWORD count;
    BYTE  tdata;

    I2cCommondRead();

    MApi_SWI2C_UseBus(URSA_I2C_BUS_SEL);
    MApi_SWI2C_AccessStart(SLAVEADDR, SW_IIC_READ);

    for(count=0;count<dataSize-1;count++)
    {
        tdata=MApi_SWI2C_GetByte(1);
        if(tdata!=0xFF)
        {
            return FALSE;
        }
    }
    //last BYTE
    {
        tdata=MApi_SWI2C_GetByte(0);
        if(tdata!=0xFF)
        {
            return FALSE;
        }
    }

    MApi_SWI2C_Stop();

    return TRUE;
}

BOOLEAN VerifyPMC64K(BYTE BankNum)
{
    BYTE tdata[]={SPI_WRITE,0x03,0x00,0x00,0x00};
    BOOLEAN VerifyOk=TRUE;
    WORD PcCounter=0;
    BYTE FlashReadData;

    tdata[1]=sFlash.READS;
    tdata[2]=BankNum;
    tdata[3]=0;
    tdata[4]=0;

    I2cWriteDatas(tdata,sizeof(tdata),NULL,0);
    msAPI_Timer_Delayms(60);
    {
        I2cCommondRead();
        msAPI_Timer_Delayms(60);
        MApi_SWI2C_UseBus(URSA_I2C_BUS_SEL);

	 if(MApi_SWI2C_AccessStart(SLAVEADDR, SW_IIC_READ)==FALSE)
        {
	        FLashPutstr("\n6M30->VerifyPMC64K Error");
        }

        for(PcCounter=0;PcCounter<=BANKSIZE-2;PcCounter++)
        {
            FlashReadData=MApi_SWI2C_GetByte(1);
            if(FlashReadData!=SrcReadFlash(PcCounter,BankNum))
            {
                VerifyOk=FALSE;
                printf("\n flash read date error[%x],[%x],[%x]",PcCounter,FlashReadData,SrcReadFlash(PcCounter,BankNum));
                break;
            }
        }

        //last byte
        {
            FlashReadData=MApi_SWI2C_GetByte(0);
            //PcCounter++;

            if(FlashReadData!=SrcReadFlash(PcCounter,BankNum))
                VerifyOk=FALSE;
        }

        // 1 bank program end
        MApi_SWI2C_Stop();
    }

    I2cWriteStop();

    return VerifyOk;
}

void ProgPMC64K(BYTE BankNum)
{
    BYTE k;
    WORD i;
    BYTE tdata[5];
    BYTE count;
    WORD PcCounter=0;

    SFlashWrsr(0x00);

    for(i=0;i<=BLOCKNUM;i++)
    {
        SFlashWren();
        SFlashChecksr();

        count=BLOCKSIZE-1;

        tdata[0]=SPI_WRITE;
        tdata[1]=sFlash.PG_PROG;
        tdata[2]=BankNum;
        tdata[3]=i;
        tdata[4]=0;


        MApi_SWI2C_UseBus(URSA_I2C_BUS_SEL);
        MApi_SWI2C_AccessStart(SLAVEADDR, SW_IIC_WRITE);

        for(k=0;k<sizeof(tdata);k++)
            MApi_SWI2C_SendByte(tdata[k]);

        while(count--)
        {
            MApi_SWI2C_SendByte(SrcReadFlash(PcCounter,BankNum));

            PcCounter++;
        }

        // 1 byte more
        MApi_SWI2C_SendByte(SrcReadFlash(PcCounter,BankNum));
        PcCounter++;

        //block program end
        I2cWriteStop();
        printf("*");
    }

    I2cWriteDatas(tdata,2,NULL,0);
    SFlashWrdi();
    SFlashChecksr();
}

void ProgSST64K(BYTE BankNum)
{
    BYTE k;
    BYTE tdata[7];
    WORD PcCounter=0;

    SFlashWrsr(0x00);

    SFlashWren();
    SFlashChecksr();

    //AAI send the address
    tdata[0]=SPI_WRITE;
    tdata[1]=sFlash.PG_PROG;
    tdata[2]=BankNum;
    tdata[3]=0;
    tdata[4]=0;
    tdata[5]=SrcReadFlash(PcCounter,BankNum);
    PcCounter++;
    tdata[6]=SrcReadFlash(PcCounter,BankNum);
    PcCounter++;

    MApi_SWI2C_UseBus(URSA_I2C_BUS_SEL);
    MApi_SWI2C_AccessStart(SLAVEADDR, SW_IIC_WRITE);

    for(k=0;k<sizeof(tdata);k++)
        MApi_SWI2C_SendByte(tdata[k]);
    I2cWriteStop();
    SFlashChecksr();

    //AAI send the datas
    tdata[0]=SPI_WRITE;
    tdata[1]=sFlash.PG_PROG;
    for (;PcCounter<0xFFFE;)
    {
        tdata[2]=SrcReadFlash(PcCounter,BankNum);
        PcCounter++;
        tdata[3]=SrcReadFlash(PcCounter,BankNum);
        PcCounter++;

        MApi_SWI2C_UseBus(URSA_I2C_BUS_SEL);
        MApi_SWI2C_AccessStart(SLAVEADDR, SW_IIC_WRITE);
        for(k=0;k<4;k++)
            MApi_SWI2C_SendByte(tdata[k]);
        I2cWriteStop();
        //SFlashChecksr();
    }
    //AAI send the remain 2 bytes
    tdata[2]=SrcReadFlash(PcCounter,BankNum);
    PcCounter++;
    tdata[3]=SrcReadFlash(PcCounter,BankNum);

    MApi_SWI2C_UseBus(URSA_I2C_BUS_SEL);
    MApi_SWI2C_AccessStart(SLAVEADDR, SW_IIC_WRITE);
    for(k=0;k<4;k++)
        MApi_SWI2C_SendByte(tdata[k]);
    I2cWriteStop();
    SFlashChecksr();
    //AAI stop
    SFlashWrdi();
    SFlashChecksr();
}

void SFlashChip_Erase(void)
{
    //BYTE tdata[5]={SPI_WRITE,0x00,0x00,0x00,0x00};
    BYTE addr[2];

    SFlashWrsr(0x00);
    SFlashWren();
    SFlashChecksr();

    addr[0]=SPI_WRITE;
    addr[1]=sFlash.CHIP_ERASE;
    I2cWriteDatas(addr,2,NULL,0);

    I2cWriteStop();

    SFlashChecksr();//Vick Add
}

BOOLEAN SFlashBlanking(DWORD address,DWORD count)
{
    BYTE tdata[]={SPI_WRITE,0x03,0x00,0x00,0x00};
    BOOLEAN Flag;

    SFlashChecksr();//Vick wait the erase finished

    tdata[2]=address>>16;
    tdata[3]=address>>8;
    tdata[4]=address;

    tdata[1]=sFlash.READS;
    I2cWriteDatas(tdata,sizeof(tdata),NULL,0);
    Flag=I2cReadBlank(count);

    I2cWriteStop();

    return Flag;
}

void SFlashProgram(void)
{
    WORD    num;
    BYTE    BankTmp;

    BankTmp = g_ucBankNumber;
    for(num=0;num<BankTmp;num++)
    {
        FLashPrintf("\n Write Bank %x",num);
        if (g_ucFlashType==Flash_SST25VF016B||g_ucFlashType==Flash_SST25VF040B)
            ProgSST64K(num);
        else
            ProgPMC64K(num);
    }
}

BOOLEAN SFlashVerify(void)
{
    BYTE    num;
    BYTE    BankTmp;

    BankTmp = g_ucBankNumber;
    for(num=0;num<BankTmp;num++)
    {
        FLashPrintf("\n Verify Bank %x",num);
        if(VerifyPMC64K(num)==FALSE)
            return FALSE;
    }
    return TRUE;
}

//-----------------------------------------------------------
void I2cWriteDatas2(BYTE * paddr, BYTE addrSize, BYTE * pdatabuf, BYTE dataSize)
{
    BYTE k;

    MApi_SWI2C_UseBus(URSA_I2C_BUS_SEL);
    MApi_SWI2C_AccessStart(SERIALDEBUGADDR, SW_IIC_WRITE);

    for(k=0;k<addrSize;k++)
        MApi_SWI2C_SendByte(paddr[k]);

    for(k=0;k<dataSize;k++)
    {
        MApi_SWI2C_SendByte(pdatabuf[k]);
    }

    MApi_SWI2C_Stop();
}

void SerialFlash_WriteReg(BYTE bBank, BYTE bAddr, BYTE bData)
{
    BYTE bWriteData[4];

    bWriteData[0] = cCmdDataWrite;
    bWriteData[1] = bBank;
    bWriteData[2] = bAddr;
    bWriteData[3] = bData;

    I2cWriteDatas2(bWriteData, sizeof(bWriteData),NULL,0);
}

void SerialFlash_EnterSerialDebug(void)
{
    code BYTE EnterSerialDebug[]={0x53, 0x45, 0x52, 0x44, 0x42};

    I2cWriteDatas2(EnterSerialDebug,sizeof(EnterSerialDebug),NULL,0);
}

void SerialFlash_EnterSingleStep(void)
{
    code BYTE EnterSingleStep[]={cCmdDataWrite, 0xC0, 0xC1, 0x53};

    I2cWriteDatas2(EnterSingleStep,sizeof(EnterSingleStep),NULL,0);
}

void SerialFlash_ExitSingleStep(void)
{
    code BYTE ExitSingleStep[]={cCmdDataWrite, 0xC0, 0xC1, 0xFF};

    I2cWriteDatas2(ExitSingleStep,sizeof(ExitSingleStep),NULL,0);
}

void SerialFlash_ExitSerialDebug(void)
{
    code BYTE ExitSerialDebug[]={0x45};

    I2cWriteDatas2(ExitSerialDebug,sizeof(ExitSerialDebug),NULL,0);
}

void SerialFlash_WP_PullHigh(void)
{
    SerialFlash_EnterSerialDebug();
    SerialFlash_EnterSingleStep();

    // Set chip to power up for register setting
    SerialFlash_WriteReg(0x00, 0, 0);
    SerialFlash_WriteReg(0x00, 0xF0, 0x02);

    // Only for GIPO P2.4
    SerialFlash_WriteReg(0x00, 0x00, 0x01);    // BK1_50[7] = 1
    SerialFlash_WriteReg(0x00, 0x50, 0x80);    // Enable register clock for gaultier

    SerialFlash_WriteReg(0x00, 0x00, 0x00);
    SerialFlash_WriteReg(0x00, 0x63, 0x3D);    // Adjust P2.4 and P2.7
                                               // TSUM chip p2.4 at 0x63[4], p2.7 at 0x63[3]
                                               // TSUMO chip p2.4 at 0x63[5],p2.7 at 0x63[2]
    SerialFlash_WriteReg(0x00, 0xc5, 0xFF);    // PWM 1 set to high (P2.7)
    SerialFlash_WriteReg(0x00, 0xc7, 0xFF);    // PWM 2 set to high (P2.4)

    // Paulo series chip
    // MCU config pin PWM0~3 default resistor setting = 1001
    SerialFlash_WriteReg(0x00, 0x00, 0x0A);
    SerialFlash_WriteReg(0x00, 0xED, 0x3F);    // PWM1 pin set to PWM BK0A_ED[7:6]=00
                                               // the other pin set to input mode
    // Lopez series chip
    // MCU config pin PWM2
    SerialFlash_WriteReg(0x1E, 0xE5, 0xC8);
    SerialFlash_WriteReg(0x1E, 0x8A, 0xC0);

    SerialFlash_ExitSingleStep();
    SerialFlash_ExitSerialDebug();
}

void MApp_MFC_ISP_Init(U32 u32Addr, U32 u32Size)
{
    ErrorFlag = FlashProgOK;
    g_eFlashProgramState = FlashProgStateInit;
    g_u32ISPSrcAddr = u32Addr;
    g_u32ISPCodeSize = u32Size;
}

U8 MApp_MFC_ISP_Program(void)
{
    WORD wErrCounter;

    if (ErrorFlag != FlashProgOK)
    {
        return (0xF0+ErrorFlag);
    }

    switch (g_eFlashProgramState)
    {
        case FlashProgStateInit:
            FLashPutstr("\n0:ISP Init,Disable WTD\n");
            MDrv_Sys_DisableWatchDog();
            g_u8CurPercent = 100;
            g_eFlashProgramState = FlashProgStateEnterIsp;
            break;

        case FlashProgStateEnterIsp:
            FLashPutstr("\n1:ISP Enter\n");
            EnterIspMode();
            msAPI_Timer_Delayms(500);
            msAPI_Timer_Delayms(500);
            ExitIspMode();
            msAPI_Timer_Delayms(500);
            msAPI_Timer_Delayms(500);

            for(wErrCounter = 0;wErrCounter<ENTER_ISP_ERROR_MAX;)
            {//for arcing
                SerialFlash_WP_PullHigh();
                if (!EnterIspMode())
                {
                    wErrCounter++;
                    msAPI_Timer_Delayms(10);
                    ExitIspMode();//Vick add
                    msAPI_Timer_Delayms(80);
                }
                else
                    break;
            }

            if (wErrCounter>=ENTER_ISP_ERROR_MAX)
            {
                ErrorFlag=FlashEnterIspModeErr;
                FLashPutstr("\nCan not enter ISP\n");
                goto ProgEnd;
            }
            else
            {
                printf("\nEnter ISP Successful[%x]\n",wErrCounter);
            }
            msAPI_Timer_Delayms(500);//Wait the Protect pin to hight.
            //------------------------
            for(wErrCounter=0;wErrCounter<GET_ID_ERROR_MAX;)
            {
                if (!GetsFlashType())
                {
                    wErrCounter++;
                    msAPI_Timer_Delayms(5);
                }
                else
                    break;
            }

            if (wErrCounter>=GET_ID_ERROR_MAX)
            {
                FLashPutstr("\n Detect SPI Flash Failed");
                g_ucFlashType=Flash_A25L40P;
                g_ucBankNumber=8;
            }
            sFlash=SupportSFlash[g_ucFlashType];

            FLashPrintf("\n Bank Number=%d",g_ucBankNumber);
            //-------------------------
            g_ucBankNumber = (g_u32ISPCodeSize/0x10000)+1;
            //-------------------------
            FLashPrintf("\n Program Banks=%d",g_ucBankNumber);

            //------------------------
            //Tony20060104 disable write protect and set status 0x00
            SFlashWren();
            SFlashWrsr(0x00);
            g_u8CurPercent = 80;
            g_eFlashProgramState = FlashProgStateErase;
            break;

        case FlashProgStateErase:
            //Step2:Chip Erase
            FLashPutstr("\n2:Chip Erase");
            SFlashChip_Erase();

            //wait the flash erase finished.
            for (wErrCounter = 0;wErrCounter<sFlash.ChipEraseMaxTime;wErrCounter++)
            {
                if (SFlashRdsr()&0x01)
                {
                    if (sFlash.ChipEraseMaxTime <= (WORD)40)
                    {// 0.1s
                        msAPI_Timer_Delayms(100);
                    }
                    else if (sFlash.ChipEraseMaxTime <= (WORD)200)
                    {// 0.2s
                        msAPI_Timer_Delayms(100);
                        wErrCounter++;
                        msAPI_Timer_Delayms(100);
                    }
                    else if (sFlash.ChipEraseMaxTime <= (WORD)600)
                    {// 0.5s
                        msAPI_Timer_Delayms(100);
                        wErrCounter++;
                        msAPI_Timer_Delayms(100);
                        wErrCounter++;
                        msAPI_Timer_Delayms(100);
                        wErrCounter++;
                        msAPI_Timer_Delayms(100);
                        wErrCounter++;
                        msAPI_Timer_Delayms(100);
                    }
                    else
                    {// 1s
                        msAPI_Timer_Delayms(100);
                        wErrCounter++;
                        msAPI_Timer_Delayms(100);
                        wErrCounter++;
                        msAPI_Timer_Delayms(100);
                        wErrCounter++;
                        msAPI_Timer_Delayms(100);
                        wErrCounter++;
                        msAPI_Timer_Delayms(100);
                        wErrCounter++;
                        msAPI_Timer_Delayms(100);
                        wErrCounter++;
                        msAPI_Timer_Delayms(100);
                        wErrCounter++;
                        msAPI_Timer_Delayms(100);
                        wErrCounter++;
                        msAPI_Timer_Delayms(100);
                        wErrCounter++;
                        msAPI_Timer_Delayms(100);
                    }
                }
                else
                    break;
            }
            FLashPrintf("\n Wait Count:%d",wErrCounter);
            g_u8CurPercent = 60;
            g_eFlashProgramState = FlashProgStateBlank;
            break;

        case FlashProgStateBlank:
            #if 0
                //Step3:Blanking Check
                FLashPutstr("\n3:Blanking");
                if(!SFlashBlanking(0,sFlash.size))
                {
                    ErrorFlag=FlashBlankingErr;
                    goto ProgEnd;
                }
            #endif
            g_u8CurPercent = 40;
            g_eFlashProgramState = FlashProgStateProgram;
            break;

        case FlashProgStateProgram:
            //Step4:Prog Flash
            FLashPutstr("\n4:Prog... ");
            SFlashProgram();
            g_u8CurPercent = 20;
            g_eFlashProgramState = FlashProgStateVerify;
            break;

        case FlashProgStateVerify:
            //Step5:Verify
            FLashPutstr("\n5:Verify");
            //Tony20060104
            SFlashWren();
            SFlashWrsr(sFlash.LOCK);
            SFlashWrdi();

            if(!SFlashVerify())
            {
                ErrorFlag=FlashVerifyErr;
                goto ProgEnd;
            }
            FLashPutstr("\nVerify->OK!");
            g_u8CurPercent = 10;
            g_eFlashProgramState = FlashProgStateExit;
            break;

        case FlashProgStateExit:
            //Step6:Exit ISP
            FLashPutstr("\n6:Exit ISP");
            ExitIspMode();
        #if (ENABLE_WATCH_DOG == ENABLE)
            MDrv_Sys_EnableWatchDog();
        #endif
            g_u8CurPercent = 0;
            g_eFlashProgramState = FlashProgStateIdle;
            break;

        case FlashProgStateIdle:
            break;
    }

ProgEnd:
    if (ErrorFlag != FlashProgOK)
    {
        ExitIspMode();
    #if (ENABLE_WATCH_DOG == ENABLE)
        MDrv_Sys_EnableWatchDog();
    #endif
        return (0xF0+ErrorFlag);
    }
    else
    {
        return g_u8CurPercent;
    }
}
#else
 U8 code ucDumyData[1] = {0xFF};
#endif
