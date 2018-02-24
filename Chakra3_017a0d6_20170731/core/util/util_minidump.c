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
#include <stdio.h>
#include <string.h>
#include "sysinfo.h"
#include "drvISR.h"
#include "hwreg.h"
#include "MsTypes.h"
#include "drvBDMA.h"
#include "SysInit.h"
#include "Board.h"
#include "debug.h"
#include "msAPI_MSDCtrl.h"
#include "msAPI_FCtrl.h"
#include "imginfo.h"
#include "msAPI_Timer.h"
#include "util_minidump.h"
#if defined(__aeon__)
#include "risc32_spr.h"
#endif
#include "MsOS.h"


#ifdef ENABLE_MINI_DUMP

extern void MApp_BlueScreen_Init(void);
extern void MApp_BlueScreen_ShowString(U16 sX, U16 sY,U32 sColor, U8 * pString);

void   MiniDump_MountDrive(void)
{
    U8 portChanged;
    U8 i;
    U8 deviceCount;
    static U32 lstCheckDriveTime = 0;

    if(msAPI_Timer_DiffTimeFromNow(lstCheckDriveTime) < 3000)
    {
         return;
    }

    lstCheckDriveTime = msAPI_Timer_GetTime0();
    deviceCount=msAPI_MSDCtrl_GetTotalDeviceCount();
    portChanged = 0;

    msAPI_MSDCtrl_DevicesChangeStatusCheck();//check if any port's connection status changed

#if (ENABLE_USB)
    if(msAPI_MSDCtrl_IsPortChanged(MSD_PORT_1))
    {
        //if port 1 changed, reflesh port1(USB0) device list
        MS_DEBUG_MSG(printf("USB port1 connect status changed\n"));
        msAPI_MSDCtrl_CheckDevicesOnPort(MSD_PORT_1);

        // Marked by coverity_0428
        //printf("...done, %bd\n", msAPI_MSDCtrl_GetDeviceStatus(MSD_PORT_1));

        portChanged = 1;
    }
#endif
#if (ENABLE_USB_2)
    if(msAPI_MSDCtrl_IsPortChanged(MSD_PORT_2))
    {
        //if port 2 changed, reflesh port2(USB1) device list
        MS_DEBUG_MSG(printf("USB port2 connect status changed\n"));
        msAPI_MSDCtrl_CheckDevicesOnPort(MSD_PORT_2);
        portChanged = 1;
    }
#endif

   if(portChanged)
    {
        for(i=0;i<deviceCount;i++)
        {
            if(msAPI_MSDCtrl_GetDeviceStatus(i) == MSD_STATUS_INSERTED)
            {
                // Marked by coverity_0429
                //printf("Active device %bd\n", i);
                if (msAPI_FCtrl_ActiveDevice(i))//active new inserted device, mount file system. THis function will maintain the drive list;
                {
                    msAPI_MSDCtrl_SetDeviceStatus(i, MSD_STATUS_IDLE);
                }
            }
         }
    }
}

U8   MiniDump_FindAvailableDriveId(void)
{
     U8 i=0;
     MSDCtrl_Drive stDriveInfo;
     memset(&stDriveInfo,0,sizeof(MSDCtrl_Drive));

     for( i=0; i<STORAGE_DRIVE_NUM; i++)
     {
         if(msAPI_FCtrl_GetDriveByIndex(i, &stDriveInfo)
                    && stDriveInfo.FileSystemType==FILE_SYSTEM_TYPE_FAT ) //return true if this drive exists, else return false
         {
            break;
         }
     }
     return i;
}

const char tbl_hex2char[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
static  U32 MDrv_Sys_DumpBank(U8 mainBank, U8 subBank, BYTE *pDst, U16 dumpLen)
{
    U8 val;
    U16  i;
    U32 len = 0;


    if(subBank !=0xFF)
    {
        U32 _u32reg = 0;
        _u32reg = ((U32)mainBank)<<8;
        MDrv_WriteByte(_u32reg, subBank);
    }
    for( i=0; i<dumpLen; i++)
    {
        val = MDrv_ReadByte((((U16)mainBank)<<8)+i);
        pDst[0] = tbl_hex2char[val>>4];
        pDst[1] = tbl_hex2char[val&0x0f];
        pDst[2] = ',';
        pDst += 3;
        len += 3;
        if( (i&0x1F) == 0x1F)
        {
            pDst[0] = '\n';
            pDst++;
            len++;
        }
    }
    pDst[0] = '\n';
    len++;
    return len;
}
#define FILL_DUMP_REG32(pDSTBuf,  val)  \
do{     \
         (pDSTBuf)[0] = tbl_hex2char[(val>>28)&0x0f];   \
         (pDSTBuf)[1] = tbl_hex2char[(val>>24)&0x0f];   \
         (pDSTBuf)[2] = tbl_hex2char[(val>>20)&0x0f];   \
         (pDSTBuf)[3] = tbl_hex2char[(val>>16)&0x0f];   \
         (pDSTBuf)[4] = tbl_hex2char[(val>>12)&0x0f];    \
         (pDSTBuf)[5] = tbl_hex2char[(val>>8)&0x0f];      \
         (pDSTBuf)[6] = tbl_hex2char[(val>>4)&0x0f];     \
         (pDSTBuf)[7] = tbl_hex2char[(val>>0)&0x0f];     \
}while(0)

#define FILL_DUMP_REG16(pDSTBuf,  val)  \
do{     \
         (pDSTBuf)[0] = tbl_hex2char[(val>>12)&0x0f];    \
         (pDSTBuf)[1] = tbl_hex2char[(val>>8)&0x0f];      \
         (pDSTBuf)[2] = tbl_hex2char[(val>>4)&0x0f];     \
         (pDSTBuf)[3] = tbl_hex2char[(val>>0)&0x0f];     \
}while(0)
static U32 FILL_DUMP_STRING(BYTE *pDSTBuf, const char *pstr)
{
    U32 len = 0;
    while(pstr[len])
    {
         pDSTBuf[len] = pstr[len];
         len++;
    }
    return len;
}
static U32 FILL_DUMP_HEX(BYTE *pDSTBuf, U32 val, U32 targetLen)
{
    U32 len = 0;
    U32 shiftCnt = 0;

    while(val>>shiftCnt)
        shiftCnt += 4;
    if(shiftCnt< targetLen*4)
        shiftCnt = targetLen*4;

    while(shiftCnt)
    {
         shiftCnt -= 4;
         pDSTBuf[len++] = tbl_hex2char[(val>>shiftCnt)&0x0f];
    }
    return len;
}
static U32 FILL_DUMP_DEC(BYTE *pDSTBuf, U32 val, U32 targetLen)
{
    U32 len = 0;
    U32 divVal = 1;
    U32 realLen = 1;

    while(val >= divVal*10)
        divVal *= 10, realLen++;
    while(realLen < targetLen)
        divVal *= 10, realLen++;

    while(divVal)
    {
         pDSTBuf[len++] = '0'+val/divVal;
         val %= divVal;
         divVal /= 10;
    }
    return len;
}
extern char g_strTrapFileLineName[];
#if defined (__mips__) || defined(__x86_64__)
U32 MDrv_Sys_DumpCPUContext(MHAL_SavedRegisters *pHalReg, BYTE *pDst, U32 vector, U8 u8Reason)
{
    U16  i, j;

    BYTE *pOrg = pDst;

    char tmp[256];
    memset(tmp,0,256);

    pDst += FILL_DUMP_STRING(pDst, "DuMP FOR RISC32 VECTOR: ");
    pDst += FILL_DUMP_DEC(pDst, vector, 2);
    pDst += FILL_DUMP_STRING(pDst, "\nReason for Dump: ");

    switch(u8Reason)
    {
        case MINI_DUMP_FOR_WDT:
            snprintf(tmp, 21, "Reason for Dump: WDT\n");
            MApp_BlueScreen_ShowString(10, 20, 0xFFFFFFFF, (U8 *)tmp);

            pDst += FILL_DUMP_STRING(pDst, "WDT\n");


          break;
         case MINI_DUMP_FOR_MIU_PROT:
            snprintf(tmp, 35, "Reason for Dump: MIU WR PROTECTION\n");
            MApp_BlueScreen_ShowString(10, 20, 0xFFFFFFFF, (U8 *)tmp);

           pDst += FILL_DUMP_STRING(pDst, "MIU WR PROTECTION\n");
           pDst += FILL_DUMP_STRING(pDst, "    PROTECT REGION0: 0x");
           pDst += FILL_DUMP_HEX(pDst, ((U32)MDrv_Read2Byte(MIU_PROTECT0_START_ADDR_H))<<10, 8);
           pDst += FILL_DUMP_STRING(pDst, "--0x");
           pDst += FILL_DUMP_HEX(pDst, ((U32)MDrv_Read2Byte(MIU_PROTECT0_END_ADDR_H))<<10, 8);
           pDst += FILL_DUMP_STRING(pDst, "\n");
           pDst += FILL_DUMP_STRING(pDst, "    PROTECT REGION1: 0x");
           pDst += FILL_DUMP_HEX(pDst, ((U32)MDrv_Read2Byte(MIU_PROTECT1_START_ADDR_H))<<10, 8);
           pDst += FILL_DUMP_STRING(pDst, "--0x");
           pDst += FILL_DUMP_HEX(pDst, ((U32)MDrv_Read2Byte(MIU_PROTECT1_END_ADDR_H))<<10, 8);
           pDst += FILL_DUMP_STRING(pDst, "\n");
           pDst += FILL_DUMP_STRING(pDst, "    PROTECT REGION2: 0x");
           pDst += FILL_DUMP_HEX(pDst, ((U32)MDrv_Read2Byte(MIU_PROTECT2_START_ADDR_H))<<10, 8);
           pDst += FILL_DUMP_STRING(pDst, "--0x");
           pDst += FILL_DUMP_HEX(pDst, ((U32)MDrv_Read2Byte(MIU_PROTECT2_END_ADDR_H))<<10, 8);
           pDst += FILL_DUMP_STRING(pDst, "\n");
           pDst += FILL_DUMP_STRING(pDst, "    PROTECT REGION3: 0x");
           pDst += FILL_DUMP_HEX(pDst, ((U32)MDrv_Read2Byte(MIU_PROTECT3_START_ADDR_H))<<10, 8);
           pDst += FILL_DUMP_STRING(pDst, "--0x");
           pDst += FILL_DUMP_HEX(pDst, ((U32)MDrv_Read2Byte(MIU_PROTECT3_END_ADDR_H))<<10, 8);
           pDst += FILL_DUMP_STRING(pDst, "\n");
           pDst += FILL_DUMP_STRING(pDst, "    HIT REGION ID:");
           pDst += FILL_DUMP_DEC(pDst, MDrv_ReadByte(0x12DF)>>6, 1);
           pDst += FILL_DUMP_STRING(pDst, "    CLIENT ID:");
           pDst += FILL_DUMP_HEX(pDst, MDrv_ReadByte(0x12DF)&0x3f, 2);
           pDst += FILL_DUMP_STRING(pDst, "\n");
          break;
         case MINI_DUMP_FOR_SYS_TRAP:
            snprintf(tmp, 29, "Reason for Dump: SYSTEM TRAP\n");
            MApp_BlueScreen_ShowString(10, 20, 0xFFFFFFFF, (U8 *)tmp);

           pDst += FILL_DUMP_STRING(pDst, "SYSTEM TRAP\n");
           pDst += FILL_DUMP_STRING(pDst, "   Trap Position:");
           pDst += FILL_DUMP_STRING(pDst, g_strTrapFileLineName);
           pDst += FILL_DUMP_STRING(pDst, "\n");
           break;
         default:
            snprintf(tmp, 24, "Reason for Dump: UNKNOW\n");
            MApp_BlueScreen_ShowString(10, 20, 0xFFFFFFFF, (U8 *)tmp);

            pDst += FILL_DUMP_STRING(pDst, "UNKNOW\n");
          break;
    }

    MS_DEBUG_MSG(printf("reg structure base is %08lx\n", (U32)pHalReg));
    snprintf(tmp, 31, "reg structure base is %08lx\n",(U32)pHalReg);
    MApp_BlueScreen_ShowString(10, 60, 0xFFFFFFFF, (U8 *)tmp);

    for( i=0; i<8; i++)
    {
        for( j = 0; j <4; j++)
        {
            //printf("r%02lu = %08lx\t", (U32)j+i*4, (U32)pHalReg->d[j+i*4]);
            snprintf(tmp, 14, "r%02lu = %08lx", (U32)j+i*4, (U32)pHalReg->d[j+i*4]);
            MApp_BlueScreen_ShowString(10+ j*200,80 + i*20, 0xFFFFFFFF, (U8 *)tmp);
        }
        //printf("\n");
    }

    //printf("sr: %08lX   pc: %08lX  cause : %08lX  badvr : %08lX\n\n", pHalReg->sr, pHalReg->pc, pHalReg->cause, pHalReg->badvr);
    snprintf(tmp, 69, "sr = %08lX   pc = %08lX  cause = %08lX  badvr = %08lX\n\n", pHalReg->sr, pHalReg->pc, pHalReg->cause, pHalReg->badvr);
    MApp_BlueScreen_ShowString(10, 80+i*20, 0xFFFFFFFF, (U8 *)tmp);


    for( i=0; i<32; i++)
    {
        pDst[0] = 'R';
        pDst[1] = '0'+i/10;
        pDst[2] = '0'+i%10;
        pDst[3] = '=';
        FILL_DUMP_REG32(pDst+4,  pHalReg->d[i]);
        pDst[12] = '\n';
        pDst += 13;
    }

    pDst[0] = 'P';
    pDst[1] = 'C';
    pDst[2] = '=';
    FILL_DUMP_REG32(pDst+3,  pHalReg->pc);
    pDst[11] = '\n';
    pDst += 12;

    pDst[0] = 'H';
    pDst[1] = 'I';
    pDst[2] = '=';
    FILL_DUMP_REG32(pDst+3,  pHalReg->hi);
    pDst[11] = '\n';
    pDst += 12;

    pDst[0] = 'L';
    pDst[1] = 'O';
    pDst[2] = '=';
    FILL_DUMP_REG32(pDst+3, pHalReg->lo);
    pDst[11] = '\n';
    pDst += 12;

    pDst[0] = 'S';
    pDst[1] = 'R';
    pDst[2] = '=';
    FILL_DUMP_REG32(pDst+3, pHalReg->lo);
    pDst[11] = '\n';
    pDst += 12;

    pDst[0] = 'C';
    pDst[1] = 'A';
    pDst[2] = 'U';
    pDst[3] = 'S';
    pDst[4] = 'E';
    pDst[5] = '=';
    FILL_DUMP_REG32(pDst+6, pHalReg->cause);
    pDst[14] = '\n';
    pDst += 15;

    pDst[0] = 'B';
    pDst[1] = 'A';
    pDst[2] = 'D';
    pDst[3] = 'V';
    pDst[4] = 'R';
    pDst[5] = '=';
    FILL_DUMP_REG32(pDst+6, pHalReg->badvr);
    pDst[14] = '\n';
    pDst += 15;

    pDst[0] = '\n';
    pDst++;

    return pDst-pOrg;
}
#else
U32 MDrv_Sys_DumpCPUContext(MHAL_SavedRegisters *pHalReg, BYTE *pDst, U32 vector, U8 u8Reason)
{
    U16  i;

    BYTE *pOrg = pDst;

    pDst += FILL_DUMP_STRING(pDst, "DUMP FOR MIPS VECTOR: ");
    pDst += FILL_DUMP_DEC(pDst, vector, 2);
    pDst += FILL_DUMP_STRING(pDst, "\nReason for Dump: ");

    switch(u8Reason)
    {
        case MINI_DUMP_FOR_WDT:
           pDst += FILL_DUMP_STRING(pDst, "WDT\n");

          break;
         case MINI_DUMP_FOR_MIU_PROT:
           pDst += FILL_DUMP_STRING(pDst, "MIU WR PROTECTION\n");
           pDst += FILL_DUMP_STRING(pDst, "    PROTECT REGION0: 0x");
           pDst += FILL_DUMP_HEX(pDst, ((U32)MDrv_Read2Byte(MIU_PROTECT0_START_ADDR_H))<<10, 8);
           pDst += FILL_DUMP_STRING(pDst, "--0x");
           pDst += FILL_DUMP_HEX(pDst, ((U32)MDrv_Read2Byte(MIU_PROTECT0_END_ADDR_H))<<10, 8);
           pDst += FILL_DUMP_STRING(pDst, "\n");
           pDst += FILL_DUMP_STRING(pDst, "    PROTECT REGION1: 0x");
           pDst += FILL_DUMP_HEX(pDst, ((U32)MDrv_Read2Byte(MIU_PROTECT1_START_ADDR_H))<<10, 8);
           pDst += FILL_DUMP_STRING(pDst, "--0x");
           pDst += FILL_DUMP_HEX(pDst, ((U32)MDrv_Read2Byte(MIU_PROTECT1_END_ADDR_H))<<10, 8);
           pDst += FILL_DUMP_STRING(pDst, "\n");
           pDst += FILL_DUMP_STRING(pDst, "    PROTECT REGION2: 0x");
           pDst += FILL_DUMP_HEX(pDst, ((U32)MDrv_Read2Byte(MIU_PROTECT2_START_ADDR_H))<<10, 8);
           pDst += FILL_DUMP_STRING(pDst, "--0x");
           pDst += FILL_DUMP_HEX(pDst, ((U32)MDrv_Read2Byte(MIU_PROTECT2_END_ADDR_H))<<10, 8);
           pDst += FILL_DUMP_STRING(pDst, "\n");
           pDst += FILL_DUMP_STRING(pDst, "    PROTECT REGION3: 0x");
           pDst += FILL_DUMP_HEX(pDst, ((U32)MDrv_Read2Byte(MIU_PROTECT3_START_ADDR_H))<<10, 8);
           pDst += FILL_DUMP_STRING(pDst, "--0x");
           pDst += FILL_DUMP_HEX(pDst, ((U32)MDrv_Read2Byte(MIU_PROTECT3_END_ADDR_H))<<10, 8);
           pDst += FILL_DUMP_STRING(pDst, "\n");
           pDst += FILL_DUMP_STRING(pDst, "    HIT REGION ID:");
           pDst += FILL_DUMP_DEC(pDst, MDrv_ReadByte(0x12DF)>>6, 1);
           pDst += FILL_DUMP_STRING(pDst, "    CLIENT ID:");
           pDst += FILL_DUMP_HEX(pDst, MDrv_ReadByte(0x12DF)&0x3f, 2);
           pDst += FILL_DUMP_STRING(pDst, "\n");
          break;
         case MINI_DUMP_FOR_SYS_TRAP:
           pDst += FILL_DUMP_STRING(pDst, "SYSTEM TRAP\n");
           pDst += FILL_DUMP_STRING(pDst, "   Trap Position:");
           pDst += FILL_DUMP_STRING(pDst, g_strTrapFileLineName);
           pDst += FILL_DUMP_STRING(pDst, "\n");
           break;
         default:
          pDst += FILL_DUMP_STRING(pDst, "UNKNOW\n");
          break;
    }

    printf(" reg structure base is %08lx\n", (U32)pHalReg);
    for( i=0; i<32; i++)
    {
       printf("r%02lu = %08lx\n", (U32)i, (U32)pHalReg->r[i]);
    }



    for( i=0; i<32; i++)
    {
        pDst[0] = 'R';
        pDst[1] = '0'+i/10;
        pDst[2] = '0'+i%10;
        pDst[3] = '=';
        FILL_DUMP_REG32(pDst+4,  pHalReg->r[i]);
        pDst[12] = '\n';
        pDst += 13;
    }
    pDst[0] = 'P';
    pDst[1] = 'C';
    pDst[2] = '=';
    FILL_DUMP_REG32(pDst+3,  pHalReg->pc);
    pDst[11] = '\n';
    pDst += 12;

    pDst[0] = 'M';
    pDst[1] = 'A';
    pDst[2] = 'C';
    pDst[3] = 'H';
    pDst[4] = 'I';
    pDst[5] = '=';
    FILL_DUMP_REG32(pDst+6,  pHalReg->machi);
    pDst[14] = '\n';
    pDst += 15;

    pDst[0] = 'M';
    pDst[1] = 'A';
    pDst[2] = 'C';
    pDst[3] = 'L';
    pDst[4] = 'O';
    pDst[5] = '=';

    FILL_DUMP_REG32(pDst+6, pHalReg->maclo);
    pDst[14] = '\n';
    pDst += 15;

    pDst[0] = 'S';
    pDst[1] = 'R';
    pDst[2] = '=';


    FILL_DUMP_REG32(pDst+3, pHalReg->maclo);
    pDst[11] = '\n';
    pDst += 12;

    pDst[0] = 'E';
    pDst[1] = 'E';
    pDst[2] = 'A';
    pDst[3] = 'R';
    pDst[4] = '=';

    FILL_DUMP_REG32(pDst+5, pHalReg->eear);
    pDst[13] = '\n';
    pDst += 14;

    pDst[0] = '\n';
    pDst++;

    return pDst-pOrg;
}
#endif

extern MS_IMG_INFO  g_ImgInfo;
U32  MiniDump_DumpModel(BYTE *pDst)
{
    U32 retlen = 0, fillLen;

    fillLen = FILL_DUMP_STRING(pDst, "MODEL_NAME = ");
    retlen += fillLen;
    pDst += fillLen;
    fillLen = FILL_DUMP_STRING(pDst, (const char*)g_ImgInfo.u8ModelName);
    retlen += fillLen;
    pDst += fillLen;
    pDst[0] = '\n';
    retlen ++;
    pDst++;

    fillLen = FILL_DUMP_STRING(pDst, "PANEL_NAME = ");
    retlen += fillLen;
    pDst += fillLen;
    fillLen = FILL_DUMP_STRING(pDst,  (const char*)g_ImgInfo.u8PanelName);
    retlen += fillLen;
    pDst += fillLen;
    pDst[0] = '\n';
    retlen ++;
    pDst++;

    fillLen = FILL_DUMP_STRING(pDst, "BOARD_TYPE = ");
    retlen += fillLen;
    pDst += fillLen;

    FILL_DUMP_REG16(pDst, g_ImgInfo.u16BoardType);
    pDst[4] = '\n';
    retlen += 5;
    pDst += 5;

    fillLen = FILL_DUMP_STRING(pDst, "CHIP_VERSION = ");
    retlen += fillLen;
    pDst += fillLen;

    FILL_DUMP_REG16(pDst, CHIP_VERSION);
    pDst[4] = '\n';
    retlen += 5;
    pDst += 5;

    fillLen = FILL_DUMP_STRING(pDst, "CHIP_REVISION = ");
    retlen += fillLen;
    pDst += fillLen;

    FILL_DUMP_REG16(pDst, CHIP_REVISION);
    pDst[4] = '\n';
    retlen += 5;
    pDst += 5;

    fillLen = FILL_DUMP_STRING(pDst, "HW_MODEL = ");
    retlen += fillLen;
    pDst += fillLen;

    FILL_DUMP_REG16(pDst, g_ImgInfo.u16HW_Model);
    pDst[4] = '\n';
    retlen += 5;
    pDst += 5;

    fillLen = FILL_DUMP_STRING(pDst, "HW_VERSION = ");
    retlen += fillLen;
    pDst += fillLen;

    FILL_DUMP_REG16(pDst, g_ImgInfo.u16HW_Version);
    pDst[4] = '\n';
    retlen += 5;
    pDst += 5;

    fillLen = FILL_DUMP_STRING(pDst, "SW_MODEL = ");
    retlen += fillLen;
    pDst += fillLen;

    FILL_DUMP_REG16(pDst, g_ImgInfo.u16SW_Model);
    pDst[4] = '\n';
    retlen += 5;
    pDst += 5;

    fillLen = FILL_DUMP_STRING(pDst, "SW_VERSION = ");
    retlen += fillLen;
    pDst += fillLen;

    FILL_DUMP_REG16(pDst, g_ImgInfo.u16SW_Version);
    pDst[4] = '\n';
    pDst[5] = '\n';
    retlen += 6;
    pDst += 6;

    return retlen;

}


static U16 u16wdt_tmpbuf[16] = {0x0044, 0x0055, 0x004D, 0x0050, 0x0030, 0x0030, 0x0030, 0x0030,
                                0x002E, 0x0044, 0x0041, 0x0054, 0x0000 ,0x0000, 0x0000, 0x0000};

static U16 u16memoryDump_FN[16] = {0x0044, 0x0055, 0x004D, 0x0050, 0x0030, 0x0030, 0x0030, 0x0030,
                                0x002E, 0x004D, 0x0045, 0x004D, 0x0000 ,0x0000, 0x0000, 0x0000};

static U8  *wdt_tmpbuf = (U8 *)&u16wdt_tmpbuf[0];
static U8  *memoryDump_FN = (U8 *)&u16memoryDump_FN[0];


void MDrv_Sys_MiniDump( MHAL_SavedRegisters *pHalReg, U32 vector, U8 u8Reason)
{
    U8  driveID;
    U8  bank, subbank;
    U8   *pAddr;
   // static U32 tickCnt;
    U8  envID;
    U8  handleDump = INVALID_FILE_HANDLE;
#if defined(__aeon__)
    U32 srval = mfspr(SPR_SR);
#endif
    U32 uStrLen;
    U16 dumpFileIndex;
    U32 u32FreeSpaceInKB;
    BOOL bDumpMemory;

#if defined(__aeon__)
    printf("enter mini dump..., SR=%08lx\n ", srval);
#endif
    MDrv_Sys_DisableWatchDog();

    MApp_BlueScreen_Init();

    driveID = MiniDump_FindAvailableDriveId();
    if( driveID >= STORAGE_DRIVE_NUM)
    {
            char str[100]={"NO FAT USB drive available, please insert FAT USB drive."};
            MApp_BlueScreen_ShowString(10, 40, 0xFFFFFFFF, (U8 *)str);

            MS_DEBUG_MSG(printf("NO FAT USB drive available, please insert FAT USB drive.\n"));
            MDrv_Sys_ClearWatchDog();
            MDrv_Sys_EnableWatchDog();
            return;
    }
    u32FreeSpaceInKB = msAPI_FCtrl_GetUnusedSizeInKB_ByDriveIndex(driveID);

    //will reserve 16M for other usage
    if(u32FreeSpaceInKB-0x1000000 < MIU_DRAM_LEN/1024)
    {
        bDumpMemory = FALSE;
        char str[100] = {"Not enough drive space, will not dump Memory"};
        MApp_BlueScreen_ShowString(10, 40, 0xFFFFFFFF, (U8 *)str);
        MS_DEBUG_MSG(printf("Not enough drive space, will not dump Memory\n"));
    }
    else
    {
        bDumpMemory = TRUE;
    }

    envID = msAPI_FSEnv_Register(driveID );
    if(envID == 0xFF)
    {
         // Marked by coverity_0430
         //printf("Failed to register FSEnv on Drive %bd\n", driveID);
       goto RESET_SYS;
    }


    pAddr = (U8*)(FONT_START_AVAILABLE | NONCACHE_MASK);

    dumpFileIndex = 0;
    while(1)
    {
       FileEntry stFileEntry;
       U16 tmp = dumpFileIndex;
       dumpFileIndex++;
       wdt_tmpbuf[8] = '0'+tmp/1000;
       tmp %= 1000;
       wdt_tmpbuf[10] = '0'+tmp/100;
       tmp %= 100;
        wdt_tmpbuf[12] = '0'+tmp/10;
       tmp %= 10;
        wdt_tmpbuf[14] = '0'+tmp;
       if(msAPI_FCtrl_EntrySearchByName(envID,  (U16*)&u16wdt_tmpbuf[0], 12, &stFileEntry) == FALSE)
           break;
    }

    handleDump = msAPI_FCtrl_FileCreate( envID , (U16*)&u16wdt_tmpbuf[0], 12,  CREATE_MODE_NEW_FORCE ) ;
    if(handleDump == INVALID_FILE_HANDLE)
    {
        goto RESET_SYS;
    }
    MS_DEBUG_MSG(printf("finish create dump file\n"));

    MS_DEBUG_MSG(printf("  start dump CPU context...\n"));
    uStrLen = MDrv_Sys_DumpCPUContext(pHalReg, pAddr, vector, u8Reason);
    msAPI_FCtrl_FileWrite(handleDump, _VA2PA(FONT_START_AVAILABLE | NONCACHE_MASK), uStrLen);

    MS_DEBUG_MSG(printf(" start dump general information...\n"));
    uStrLen = MiniDump_DumpModel(pAddr);
    msAPI_FCtrl_FileWrite(handleDump, _VA2PA(FONT_START_AVAILABLE | NONCACHE_MASK), uStrLen);


    MS_DEBUG_MSG(printf("   start dump registers....\n"));
    memcpy(wdt_tmpbuf, "dump bank 00\n", 14);
    for(bank=0; bank<=0x1E; bank++)
    {
        // Marked by coverity_0431
       //printf(".....dump bank%bx\n", bank);
       wdt_tmpbuf[10] = tbl_hex2char[bank>>4];
       wdt_tmpbuf[11] = tbl_hex2char[bank&0x0f];
       msAPI_FCtrl_FileWrite(handleDump, _VA2PA((U32)wdt_tmpbuf), 13);
       uStrLen = MDrv_Sys_DumpBank(bank, 0xFF, pAddr, 0x100UL);
       msAPI_FCtrl_FileWrite(handleDump, _VA2PA(FONT_START_AVAILABLE | NONCACHE_MASK), uStrLen);
    }

    bank = 0x1F;
    memcpy(wdt_tmpbuf, "The  bank 1F, subbank 00\n", 26);
    for(subbank=0; subbank<=5; subbank++)
    {
       // Marked by coverity_0432
       //printf(".....dump bank1F subbank%bx\n", subbank);
       wdt_tmpbuf[22] = tbl_hex2char[subbank>>4];
       wdt_tmpbuf[23] = tbl_hex2char[subbank&0x0f];
       msAPI_FCtrl_FileWrite(handleDump, _VA2PA((U32)wdt_tmpbuf), 25);
       uStrLen = MDrv_Sys_DumpBank(bank, subbank, pAddr, 0x100UL);
       msAPI_FCtrl_FileWrite(handleDump, _VA2PA(FONT_START_AVAILABLE | NONCACHE_MASK), uStrLen);
    }
    memcpy(wdt_tmpbuf, "dump bank 00\n", 14);
    for(bank=0x21; bank<=0x21; bank++)
    {
       // Marked by coverity_0432
       //printf(".....dump bank%bx\n", bank);
       wdt_tmpbuf[10] = tbl_hex2char[bank>>4];
       wdt_tmpbuf[11] = tbl_hex2char[bank&0x0f];
       msAPI_FCtrl_FileWrite(handleDump, _VA2PA((U32)wdt_tmpbuf), 13);
       uStrLen = MDrv_Sys_DumpBank(bank, 0xFF, pAddr, 0x100UL);
       msAPI_FCtrl_FileWrite(handleDump, _VA2PA(FONT_START_AVAILABLE | NONCACHE_MASK), uStrLen);
    }

    for(bank=0x24; bank<=0x2D; bank++)
    {
        // Marked by coverity_0432
       //printf(".....dump bank%bx\n", bank);
       wdt_tmpbuf[10] = tbl_hex2char[bank>>4];
       wdt_tmpbuf[11] = tbl_hex2char[bank&0x0f];
       msAPI_FCtrl_FileWrite(handleDump, _VA2PA((U32)wdt_tmpbuf), 13);
       uStrLen = MDrv_Sys_DumpBank(bank, 0xFF, pAddr, 0x100UL);
       msAPI_FCtrl_FileWrite(handleDump, _VA2PA(FONT_START_AVAILABLE | NONCACHE_MASK), uStrLen);
    }

    bank = 0x2F;
    memcpy(wdt_tmpbuf, "The  bank 2F, subbank 00\n", 26);
    for(subbank=0x00; subbank<=0x1D; subbank++)
    {
        // Marked by coverity_0432
       //printf(".....dump bank1F subbank%bx\n", subbank);
       wdt_tmpbuf[22] = tbl_hex2char[subbank>>4];
       wdt_tmpbuf[23] = tbl_hex2char[subbank&0x0f];
       msAPI_FCtrl_FileWrite(handleDump, _VA2PA((U32)wdt_tmpbuf), 25);
       uStrLen = MDrv_Sys_DumpBank(bank, subbank, pAddr, 0x100UL);
       msAPI_FCtrl_FileWrite(handleDump, _VA2PA(FONT_START_AVAILABLE | NONCACHE_MASK), uStrLen);
    }

   memcpy(wdt_tmpbuf, "dump bank 00\n", 14);
    for(bank=0x30; bank<=0x3F; bank++)
    {
        // Marked by coverity_0432
       //printf(".....dump bank%bx\n", bank);
       wdt_tmpbuf[10] = tbl_hex2char[bank>>4];
       wdt_tmpbuf[11] = tbl_hex2char[bank&0x0f];
       msAPI_FCtrl_FileWrite(handleDump, _VA2PA((U32)wdt_tmpbuf), 13);
       uStrLen = MDrv_Sys_DumpBank(bank, 0xFF, pAddr, 0x100UL);
       msAPI_FCtrl_FileWrite(handleDump, _VA2PA(FONT_START_AVAILABLE | NONCACHE_MASK), uStrLen);
    }
    msAPI_FCtrl_FileClose(handleDump);
    MS_DEBUG_MSG(printf("Mini Dump finished\n"));

    if(bDumpMemory)
    {
         U32 baseAddr = 0|NONCACHE_MASK;
         U32 remainLen = MIU_DRAM_LEN;
         U32 writeLen;

         MS_DEBUG_MSG(printf("\n\nStart Dump Memory:"));
         while(1)
         {
                FileEntry stFileEntry;
                U16 tmp = dumpFileIndex;
                dumpFileIndex++;
                memoryDump_FN[8] = '0'+tmp/1000;
                tmp %= 1000;
                memoryDump_FN[10] = '0'+tmp/100;
                tmp %= 100;
                memoryDump_FN[12] = '0'+tmp/10;
                tmp %= 10;
                memoryDump_FN[14] = '0'+tmp;
                if(msAPI_FCtrl_EntrySearchByName(envID,  (U16*)&u16memoryDump_FN[0], 12, &stFileEntry) == FALSE)
                       break;
         }
        handleDump = msAPI_FCtrl_FileCreate( envID , (U16*)&u16memoryDump_FN[0], 12,  CREATE_MODE_NEW_FORCE ) ;
        if(handleDump == INVALID_FILE_HANDLE)
        {
             goto RESET_SYS;
        }
        MS_DEBUG_MSG(printf("finish create memory dump file\n"));

        MS_DEBUG_MSG(printf("Start dump system memory:\n"));

        while(remainLen)
        {
             writeLen = (remainLen>=0x10000?0x10000:remainLen);
             remainLen -= writeLen;
             msAPI_FCtrl_FileWrite(handleDump, _VA2PA(baseAddr), writeLen);
             baseAddr += writeLen;
             MS_DEBUG_MSG(printf("*"));
        }

       msAPI_FCtrl_FileClose(handleDump);
       MS_DEBUG_MSG(printf("\nFinish dump system memory.\n"));

    }


RESET_SYS:


    if(envID != 0xFF)
    {
        msAPI_FSEnv_UnRegister(envID);
    }
    MsOS_DisableInterrupt(E_INT_FIQ_WDT);
    MDrv_Sys_SetWatchDogTimer( 1 );  //set 10 second

    if(u8Reason != MINI_DUMP_FOR_SYS_TRAP)
    {
         MS_DEBUG_MSG(printf("Reset System...\n"));
         MDrv_Sys_EnableWatchDog();
    }
    else
    {
         MS_DEBUG_MSG(printf("Hang up system\n"));
    }
    while(1);//loop to wait reboot

}



void ProcessWDTIsr(MHAL_SavedRegisters *pHalReg, U32 vector)
{
    MDrv_Sys_MiniDump(pHalReg, vector, MINI_DUMP_FOR_WDT);
}

void ProcessMIUIsr(MHAL_SavedRegisters *pHalReg, U32 vector)
{
    UNUSED(pHalReg);
    UNUSED(vector);

    MDrv_Sys_MiniDump(pHalReg, vector, MINI_DUMP_FOR_MIU_PROT);
}

#endif


