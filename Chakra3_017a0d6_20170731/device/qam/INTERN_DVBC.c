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
// (MStar Confidential Information) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
/// @file INTERN_DVBC.c
/// @brief INTERN_DVBC DVBC
/// @author MStar Semiconductor, Inc.
//
////////////////////////////////////////////////////////////////////////////////

#define _INTERN_DVBC_C_
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

#include "INTERN_DVBC.h"
#include "INTERN_DVBC_Private.h"
#ifdef SUPPORT_AP_BIN_IN_FLASH_2
#include "InfoBlock.h"
#endif

#include "drvMMIO.h"
#include "drvAVD.h"

#define TEST_EMBEDED_DEMOD 1
#define EMBEDED_DEMOD_DELAY_TIME 0xff

#if DTV_LOW_IF_FREQ
#if(FRONTEND_TUNER_TYPE==NXP_TDA18272_TUNER|| FRONTEND_TUNER_TYPE==NUTUNE_FK1602_TUNER||FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER)
#define DTV_IF_8M_FREQ  5000L
#define DTV_IF_7M_FREQ  3500L
#define DTV_IF_6M_FREQ  3000L
#else
#define DTV_IF_8M_FREQ  4000L
#define DTV_IF_7M_FREQ  3500L
#define DTV_IF_6M_FREQ  3000L
#endif
#else
#define DTV_IF_8M_FREQ  36167L
#endif
//U8 load_data_variable=1;
//-----------------------------------------------------------------------
#define BIN_ID_INTERN_DVBC_DEMOD BIN_ID_INTERN_DVBC



#define DBG_INTERN_DVBC(x) x
#define DBG_GET_SIGNAL(x)  //x
#define DBG_DUMP_LOAD_DSP_TIME 0
#define INTERN_DVBC_USE_SAR_3_ENABLE 0
#define SIGNAL_LEVEL_OFFSET 	0.00
#define TAKEOVERPOINT 			 -60.0
#define TAKEOVERRANGE 				0.5
#define TDP_REG_BASE  0x2100

static S_INTERN_DVBC_RFAGC_SSI MSTAR_RfagcSsi_INTERN_DVBC[] =
{
    {-15.00,    0x02},
    {-25.00,    0x04},
    {-26.00,    0x04},
    {-27.00,    0x05},
    {-28.00,    0x05},
    {-29.00,    0x05},
    {-30.00,    0x06},
    {-31.00,    0x07},
    {-32.00,    0x07},
    {-33.00,    0x08},
    {-34.00,    0x09},
    {-35.00,    0x09},
    {-36.00,    0x09},
    {-37.00,    0x0A},
    {-38.00,    0x0A},
    {-39.00,    0x0B},
    {-40.00,    0x0B},
    {-41.00,    0x0B},
    {-42.00,    0x0B},
    {-43.00,    0x0C},
    {-44.00,    0x0C},
    {-45.00,    0x0C},
    {-47.00,    0x0D},
    {-48.00,    0x0E},
    {-49.00,    0x0E},
    {-50.00,    0x0F},
    {-51.00,    0x0F},
    {-52.00,    0x10},
    {-53.00,    0x11},
    {-55.00,    0x11},
    {-56.00,    0x12},
    {-57.00,    0x13},
    {-57.50,    0x14},
    {-58.00,    0x17},
    {-58.50,    0x18},
    {-59.00,    0x1A},
    {-59.20,    0x1B},
    {-59.40,    0x1C},
    {-59.60,    0x1D},
    {-59.80,    0x1D},
    {-60.00,    0x1D},
    {-62.00,    0x1D},
    {-62.00,    0xFF},
};

static S_INTERN_DVBC_IFAGC_SSI MSTAR_IfagcSsi_INTERN_DVBC[] =
{
	{-57.00,    0x57},
 //   {-58.00,    0x57},
 //   {-59.00,    0x58},
    {-60.00,    0x58},
//    {-61.00,    0x59},
//    {-62.00,    0x61},
    {-63.00,    0x59},
//    {-64.00,    0x63},
//    {-65.00,    0x61},
    {-66.00,    0x60},
//    {-67.00,    0x62},
//    {-68.00,    0x67},
    {-69.00,    0x61},
//    {-70.00,    0x68},
//    {-71.00,    0x64},
    {-72.00,    0x62},
//    {-73.00,    0x6B},
//    {-74.00,    0x6C},
    {-75.00,    0x63},
//    {-76.00,    0x6E},
//    {-77.00,    0x6F},
    {-78.00,    0x64},
//    {-79.00,    0x71},
    {-80.00,    0x65},
    {-100.00,    0xFF},
};


//-----------------------------------------------------------------------
/****************************************************************
*Local Variables                                                *
****************************************************************/
//static U8 *RIUBase=NULL;
//static U32 RIUSize=0;
//static BOOL FECLock=0;
static U8 FECUnlockCnt;


//Global Variables
static S_CMDPKTREG gsCmdPacket;
//U8 gCalIdacCh0, gCalIdacCh1;

#define TS_SER_C		0x00	//0: parallel 1:serial

#if (INTERN_DVBC_TS_SERIAL_INVERSION)
#define TS_INV_C		0x01
#else
#define TS_INV_C		0x00
#endif
#define DVBC_FS         24000
#define FC_L_C			        (U8)(0xB1A2-DTV_IF_8M_FREQ)// 0x5B  // 9394, Fc = Fs - IF = 45474 - 36167 = 9307
#define FC_H_C			        (U8)((0xB1A2-DTV_IF_8M_FREQ)>>8)//  0x24
#define FS_H_C			0xB1	// 45473, Fs = 45.4738MHz
#define FS_L_C			0xA1
#define AUTO_SCAN_C		0x01	// Auto Scan - 0:channel change, 1:auto-scan
#define AUTO_SR 		0x01 //0x01
#define AUTO_QAM		0x01 //0x01
#define IQ_SWAP_C		0x00
#define PAL_I_C			0x00	// PAL_I: 0: Non-Pal-I CCI, 1: Pal-I CCI (for UK)
#define SR0_H			0x1A	// Symbol Rate: 6875 = 0x1ADB
#define SR0_L			0xDB
#define SR1_H			0x1A	// Symbol Rate: 6900 = 0x1AF4
#define SR1_L			0xF4
//#define SR2_H			0x10	// Symbol Rate: 4200 = 0x1068
//#define SR2_L			0x68
//#define SR3_H			0x14	// Symbol Rate: 5200 = 0x1450
//#define SR3_L			0x50
#define SR2_H			0x1c //0x14	// Symbol Rate: 5200 = 0x1450
#define SR2_L			0x20 //0x50
#define SR3_H			0x0f //0x10	// Symbol Rate: 4200 = 0x1068
#define SR3_L			0xa0 //0x68
#define QAM				0x02	// QAM: 0:16, 1:32, 2:64, 3:128, 4:256

#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7)
#define FC_H        0x8D    // 36167 -> 0323 update
#define FC_L        0x47   // 0323 jason
#define FS_H        0x5D    // 24MHz
#define FS_L        0xC0    // andy 2009-8-18 ?? 10:22:29 0x9E
#define SET_ZIF     0x00
#define IQB_EN		0x00
#else
#define FC_H        0x24    // 40474, Fc = Fs - IF = 45474 - 5000 = 40474 -> 0323 update
#define FC_L        0x5B    // 0323 jason
#define FS_H        0xB1    // 45471, Fs = 45.4738MHz
#define FS_L        0xA2    // andy 2009-8-18 ?? 10:22:29 0x9E
#define SET_ZIF     0x00
#define IQB_EN		0x00
#endif

#if(FRONTEND_TUNER_TYPE==NUTUNE_FK1602_TUNER || FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER)
#define TUNER_LOWIF    0x01  //for LOW IF tuner
#define LOWIF_Fif_L      0x88 //0x88//0xa0  //for LOW IF tuner
#define LOWIF_Fif_H      0x13 //0x13//0x0f //for LOW IF tuner
#else
#define TUNER_LOWIF    0x00
#define LOWIF_Fif_L      0x00
#define LOWIF_Fif_H      0x00
#endif

#define ATV_DET_EN        1

U8 INTERN_DVBC_DSPREG[] =
{   0x00, 0x00, 0x01, IQB_EN, 0x01, 0x00, 0x01, AUTO_SCAN_C,				// 00h ~ 07h
    AUTO_SR, AUTO_QAM, ATV_DET_EN, 0x00, 0x00, 0x00, 0x00, 0x00, 				// 08h ~ 0fh
    0x00, SET_ZIF, 0x00, FC_L, FC_H, FS_L, FS_H, SR0_L,			// 10h ~ 17h
    SR0_H, SR1_L, SR1_H, SR2_L, SR2_H, SR3_L, SR3_H, 0x00,				// 18h ~ 1fh
    0x00, QAM, IQ_SWAP_C, PAL_I_C, TS_SER_C, 0x00, TS_INV_C, 0x00,		// 20h ~ 27h
    TUNER_LOWIF, LOWIF_Fif_L, LOWIF_Fif_H,									// 28h ~ 2Ah
};
extern U8 LoadDspStatus;
extern U8 u8AutoSRTemp;
extern U8 u8AutoQAMTemp;


#if 0
static void INTERN_DVBC_InitRegBase(void)
{
    MDrv_MMIO_GetBASE((MS_U32*)(void *)RIUBase, &RIUSize, MS_MODULE_MIU);
    printf("address:%lx %lx\n",(MS_U32)RIUBase, RIUSize);
}
#endif
/***********************************************************************************
  Subject:    Delay
  Function:   INTERN_DVBC_Delayms
  Parmeter:   delay_ms : millisecs for delay
  Return:     NONE
  Remark:
************************************************************************************/
static void    INTERN_DVBC_Delayms(U32 delay_ms)
{
    MsOS_DelayTask(delay_ms);
}


BOOLEAN INTERN_DVBC_ReadReg(U16 u16Addr, U8 *pu8Data)
{
    U16     u8WaitCnt=0;

//   UNUSED(pu8Data);
    if (MDrv_ReadByte(MBRegBase + 0x00))
    {
       printf(">> MB Busy!\n");
       return FALSE;
    }

    MDrv_WriteByte(MBRegBase + 0x02, (U8)(u16Addr >> 8));   // ADDR_H
    MDrv_WriteByte(MBRegBase + 0x01, (U8)u16Addr);          // ADDR_L
    MDrv_WriteByte(MBRegBase + 0x00, 0x01);                 // MB_CNTL set read mode

    MDrv_WriteByte(DMDMcuBase + 0x03, 0x02);                // assert interrupt to DMD MCU51 //mick
    MDrv_WriteByte(DMDMcuBase + 0x03, 0x00);                // de-assert interrupt to DMD MCU51

    while(MDrv_ReadByte(MBRegBase + 0x00)!= 0xFF)           // wait MB_CNTL set done
    {
#if TEST_EMBEDED_DEMOD
        INTERN_DVBC_Delayms(1);  // << Ken 20090629
#endif
        if (u8WaitCnt++ >= 0xFF)
        {
            printf(">> DVBC ReadReg Fail!\n");
            return FALSE;
        }
    }

    *pu8Data = MDrv_ReadByte(MBRegBase + 0x03);             // REG_DATA get
    MDrv_WriteByte(MBRegBase + 0x00, 0x00);                 // MB_CNTL clear

    return TRUE;
}

U8 INTERN_DVBC_Version(U16 *ver)
{

    U8 status = true;
    U8 tmp = 0;
    U16 u16_INTERN_DVBC_Version;

    status &= INTERN_DVBC_ReadReg(TOP_REG_BASE + 0xC1, &tmp);
    u16_INTERN_DVBC_Version = tmp;
    status &= INTERN_DVBC_ReadReg(TOP_REG_BASE + 0xC2, &tmp);
    u16_INTERN_DVBC_Version = u16_INTERN_DVBC_Version<<8|tmp;
    *ver = u16_INTERN_DVBC_Version;

    return status;
}


BOOLEAN INTERN_DVBC_WriteReg(U32 u16Addr, U8 u8Data)
{
    U16     u8WaitCnt=0;

    MDrv_WriteByte(MBRegBase + 0x02, (U8)(u16Addr >> 8));   // ADDR_H
    MDrv_WriteByte(MBRegBase + 0x01, (U8)u16Addr);          // ADDR_L
    MDrv_WriteByte(MBRegBase + 0x03, u8Data);               // REG_DATA
    MDrv_WriteByte(MBRegBase + 0x00, 0x02);                 // MB_CNTL set write mode

    MDrv_WriteByte(DMDMcuBase + 0x03, 0x02);                // assert interrupt to VD MCU51 //mick
    MDrv_WriteByte(DMDMcuBase + 0x03, 0x00);                // de-assert interrupt to VD MCU51

    while(MDrv_ReadByte(MBRegBase + 0x00) != 0xFF)          // wait done flag
    {
#if TEST_EMBEDED_DEMOD
        INTERN_DVBC_Delayms(1);   // <<< Ken 20090629
#endif
        if (u8WaitCnt++ >= 0xFF)
        {
            printf(">> DVBC WriteReg Fail!\n");
            return FALSE;
        }
    }

    MDrv_WriteByte(MBRegBase + 0x00, 0x00);                 // MB_CNTL clear

    return TRUE;
}
//#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S8 )
BOOLEAN INTERN_DVBC_ReadDspReg(U16 u16Addr, U8 *pu8Data)
{
    U16     u8WaitCnt = 0;

    if (MDrv_ReadByte(MBRegBase + 0x00))
    {
       printf(">> MB Busy!\n");
       return FALSE;
    }

    MDrv_WriteByte(MBRegBase + 0x02, (U8)(u16Addr >> 8));   // ADDR_H
    MDrv_WriteByte(MBRegBase + 0x01, (U8)u16Addr);          // ADDR_L
    MDrv_WriteByte(MBRegBase + 0x00, 0x03);                 // MB_CNTL set read dsp mode

    MDrv_WriteByte(DMDMcuBase + 0x3, 0x02);                         // assert interrupt to VD MCU51
    MDrv_WriteByte(DMDMcuBase + 0x3, 0x00);                         // de-assert interrupt to VD MCU51

    while(MDrv_ReadByte(MBRegBase + 0x00)!= 0xFF)           // wait MB_CNTL set done
    {
#if TEST_EMBEDED_DEMOD
        INTERN_DVBC_Delayms(1);  // << Ken 20090629
#endif
        if (u8WaitCnt++ >= 0xFF)
        {
            printf(">> DVBC ReadDspReg Fail!\n");
            return FALSE;
        }
    }

    *pu8Data = MDrv_ReadByte(MBRegBase + 0x03);             // REG_DATA get
    MDrv_WriteByte(MBRegBase + 0x00, 0x00);                 // MB_CNTL clear

    return TRUE;
}

BOOLEAN INTERN_DVBC_WriteDspReg(U32 u16Addr, U8 u8Data)
{
    U16     u8WaitCnt = 0;

    MDrv_WriteByte(MBRegBase + 0x02, (U8)(u16Addr >> 8));   // ADDR_H
    MDrv_WriteByte(MBRegBase + 0x01, (U8)u16Addr);          // ADDR_L
    MDrv_WriteByte(MBRegBase + 0x03, u8Data);               // REG_DATA
    MDrv_WriteByte(MBRegBase + 0x00, 0x04);                 // MB_CNTL set write dsp mode

    MDrv_WriteByte(DMDMcuBase + 0x3, 0x02);                         // assert interrupt to VD MCU51
    MDrv_WriteByte(DMDMcuBase + 0x3, 0x00);                         // de-assert interrupt to VD MCU51

    while(MDrv_ReadByte(MBRegBase + 0x00) != 0xFF)          // wait done flag
    {
#if TEST_EMBEDED_DEMOD
        INTERN_DVBC_Delayms(1);   // <<< Ken 20090629
#endif
        if (u8WaitCnt++ >= 0xFF)
        {
            printf(">> DVBC WriteDspReg Fail!\n");
            return FALSE;
        }
    }

    MDrv_WriteByte(MBRegBase + 0x00, 0x00);                 // MB_CNTL clear

    return TRUE;
}


void DumpQAMRegisters(void)
{
    U16 addr;
    U8 reg_value;
    for (addr =0;addr<=0x2D;addr++)
    {
        if (INTERN_DVBC_ReadDspReg(addr,&reg_value)==TRUE)
        {
            printf("addr=%d val=%d \n",addr,reg_value);
        }
    }
}

U16 INTERN_DVBC_DSPReg_Init( void )
{
    U8		idx = 0;
    U8		status = TRUE;

	DBG_INTERN_DVBC(printf("DVBC DspReg_init\n"));

    for (idx = 0; idx<sizeof(INTERN_DVBC_DSPREG); idx++)
    	status &= INTERN_DVBC_WriteDspReg(idx, INTERN_DVBC_DSPREG[idx]);

    return status;
}
//#endif
/***********************************************************************************
  Subject:    Command Packet Interface
  Function:   INTERN_DVBC_Cmd_Packet_Send
  Parmeter:
  Return:     BOOLEAN
  Remark:
************************************************************************************/
BOOLEAN INTERN_DVBC_Cmd_Packet_Send(S_CMDPKTREG* pCmdPacket, U8 param_cnt)
{
	pCmdPacket = Null;
	param_cnt = param_cnt;
#if 0
    U8             status = true, indx;
    U8             reg_val, timeout = 0;

    // ==== Command Phase ===================
    DBG_INTERN_DVBC(printf("--->INTERN_DVBC (cmd=0x%x)(0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,) \n",pCmdPacket->cmd_code,
            pCmdPacket->param[0],pCmdPacket->param[1],
            pCmdPacket->param[2],pCmdPacket->param[3],
            pCmdPacket->param[4],pCmdPacket->param[5] ));

    // wait _BIT_END clear
    do
    {
#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) 		//T3
        status &= INTERN_DVBC_ReadReg(REG_CMD_CTRL, &reg_val);

#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD ) 	//T4
        reg_val = MDrv_ReadByte(MBRegBase + 0x1C);

#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_A7 ) 	//A7
        reg_val = MDrv_ReadByte(MBRegBase + 0x1C);

#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S8)	//T8
	reg_val = INTERN_DVBC_Read_MBX_Byte(REG_CMD_CTRL);

#endif
        if((reg_val & _BIT_END) != _BIT_END)
        {
            break;
        }
        MsOS_DelayTask(1);
        if (timeout++ > 200) //200
        {
            printf("---> INTERN_DVBC_Cmd_Packet_Send fail on 'wait _BIT_END clear' \n");
            return false;
        }
    } while (1);

    // set cmd_3:0 and _BIT_START
#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) 		//T3
    status &= INTERN_DVBC_ReadReg(REG_CMD_CTRL, &reg_val);
    reg_val = (reg_val & 0x0f)|(pCmdPacket->cmd_code << 4)|_BIT_START;
    status &= INTERN_DVBC_WriteReg(REG_CMD_CTRL, reg_val);

#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD ) 	//T4
    reg_val = MDrv_ReadByte(MBRegBase + 0x1C);
    reg_val = (reg_val & 0x0f)|(pCmdPacket->cmd_code << 4)|_BIT_START;
    MDrv_WriteByte(MBRegBase + 0x1C, reg_val);

#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_A7 ) 	//A7
    reg_val = MDrv_ReadByte(MBRegBase + 0x1C);
    reg_val = (reg_val & 0x0f)|(pCmdPacket->cmd_code << 4)|_BIT_START;
    MDrv_WriteByte(MBRegBase + 0x1C, reg_val);

#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S8)		//T8

	reg_val = INTERN_DVBC_Read_MBX_Byte(REG_CMD_CTRL);
	reg_val = (reg_val & 0x0f)|(pCmdPacket->cmd_code << 4)|_BIT_START;
	INTERN_DVBC_Write_MBX_Byte(REG_CMD_CTRL, reg_val);

#endif

    //DBG_INTERN_DVBC(printf("demod_config: cmd_code = %bx\n", pCmdPacket->cmd_code));
    // wait _BIT_START clear
    do
    {
#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) 		//T3
        status &= INTERN_DVBC_ReadReg(REG_CMD_CTRL, &reg_val);

#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD ) 	//T4
        reg_val = MDrv_ReadByte(MBRegBase + 0x1C);

#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_A7 ) 	//A7
        reg_val = MDrv_ReadByte(MBRegBase + 0x1C);

#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S8)		//T8
		reg_val = INTERN_DVBC_Read_MBX_Byte(REG_CMD_CTRL);
#endif
        if((reg_val & _BIT_START) != _BIT_START)
        {
            break;
        }
         MsOS_DelayTask(10);
        if (timeout++ > 200)
        {
            printf("---> INTERN_DVBC_Cmd_Packet_Send fail on 'wait _BIT_START clear' \n");
            return false;
        }
    } while (1);

    // ==== Data Phase ======================

#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) 		//T3
    status &= INTERN_DVBC_WriteReg(REG_CMD_ADDR, 0x00);

#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD ) 	//T4
    MDrv_WriteByte(MBRegBase + 0x1E, 0x00);

#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_A7 ) 	//A7
    MDrv_WriteByte(MBRegBase + 0x1E, 0x00);

#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S8)		//T8
	INTERN_DVBC_Write_MBX_Byte(REG_CMD_ADDR, 0x00);

#endif

    for (indx = 0; indx < param_cnt; indx++)
    {
#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) 		//T3
        status &= INTERN_DVBC_ReadReg(REG_CMD_ADDR, &reg_val);

#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD )	//T4
        reg_val = MDrv_ReadByte(MBRegBase + 0x1E);

#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_A7 )	//A7
        reg_val = MDrv_ReadByte(MBRegBase + 0x1E);

#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S8)		//T8
		reg_val = INTERN_DVBC_Read_MBX_Byte(REG_CMD_ADDR);
#endif
        //DBG_INTERN_DVBC(printf("demod_config: param[%bd] = %bx\n", reg_val, pCmdPacket->param[indx]));

        // set param[indx] and _BIT_DRQ
#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) 		//T3
        status &= INTERN_DVBC_WriteReg(REG_CMD_DATA, pCmdPacket->param[indx]);
        status &= INTERN_DVBC_ReadReg(REG_DTA_CTRL, &reg_val);
        status &= INTERN_DVBC_WriteReg(REG_DTA_CTRL, reg_val|_BIT_DRQ);

#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD ) 	//T4
        MDrv_WriteByte(MBRegBase + 0x1F, pCmdPacket->param[indx]);
        //printf("param_cnt**************[%d]=%x \n" ,indx ,pCmdPacket->param[indx]); //mick
        reg_val = MDrv_ReadByte(MBRegBase + 0x1D);
        MDrv_WriteByte(MBRegBase + 0x1D, reg_val|_BIT_DRQ);

#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_A7 ) 	//A7
        MDrv_WriteByte(MBRegBase + 0x1F, pCmdPacket->param[indx]);
        //printf("param_cnt**************[%d]=%x \n" ,indx ,pCmdPacket->param[indx]); //mick
        reg_val = MDrv_ReadByte(MBRegBase + 0x1D);
        MDrv_WriteByte(MBRegBase + 0x1D, reg_val|_BIT_DRQ);

#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S8)		//T8
		INTERN_DVBC_Write_MBX_Byte(REG_CMD_DATA, pCmdPacket->param[indx]);
        reg_val = INTERN_DVBC_Read_MBX_Byte(REG_DTA_CTRL);
        INTERN_DVBC_Write_MBX_Byte(REG_DTA_CTRL, reg_val|_BIT_DRQ);

#endif
        // wait _BIT_DRQ clear
        do
        {
#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) 		//T3
            status &= INTERN_DVBC_ReadReg(REG_DTA_CTRL, &reg_val);

#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD ) 	//T4
            reg_val = MDrv_ReadByte(MBRegBase + 0x1D);

#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_A7 ) 	//A7
            reg_val = MDrv_ReadByte(MBRegBase + 0x1D);

#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S8)		//T8
			reg_val = INTERN_DVBC_Read_MBX_Byte(REG_DTA_CTRL);
#endif
            if ((reg_val & _BIT_DRQ) != _BIT_DRQ)
            {
                break;
            }
            MsOS_DelayTask(1);
            if (timeout++ > 200)
            {
                printf("---> INTERN_DVBC_Cmd_Packet_Send fail on 'wait _BIT_DRQ clear' \n");
                return false;
            }
        } while (1);
    }

    // ==== End Phase =======================

    // set _BIT_END to finish command
#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) 		//T3
    status &= INTERN_DVBC_ReadReg(REG_CMD_CTRL, &reg_val);
    status &= INTERN_DVBC_WriteReg(REG_CMD_CTRL, reg_val|_BIT_END);

#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD ) 	//T4
     reg_val = MDrv_ReadByte(MBRegBase + 0x1C);
     MDrv_WriteByte(MBRegBase + 0x1C, reg_val|_BIT_END);

#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_A7 ) 	//A7
     reg_val = MDrv_ReadByte(MBRegBase + 0x1C);
     MDrv_WriteByte(MBRegBase + 0x1C, reg_val|_BIT_END);

#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S8)		//T8
	 reg_val = INTERN_DVBC_Read_MBX_Byte(REG_CMD_CTRL);
     INTERN_DVBC_Write_MBX_Byte(REG_CMD_CTRL, reg_val|_BIT_END);

#endif
#endif
    return TRUE;
}


/***********************************************************************************
  Subject:    Command Packet Interface
  Function:   INTERN_DVBC_Cmd_Packet_Exe_Check
  Parmeter:
  Return:     BOOLEAN
  Remark:
************************************************************************************/
BOOLEAN INTERN_DVBC_Cmd_Packet_Exe_Check(BOOL* cmd_done)
{
  cmd_done = NULL;
#if 0
    U8             status = true;
    U8             reg_val;
    U16            timeout = 0;

    // wait _BIT_END clear
    do {
        status &= INTERN_DVBC_ReadReg(REG_CMD_CTRL, &reg_val);

        if((reg_val & _BIT_END) != _BIT_END)
            break;

        if (timeout++ > 200)
        {
            *cmd_done = false;
            return status;
        }
        INTERN_DVBC_Delayms(10);
    } while (1);

    DBG_INTERN_DVBC(printf("Exe duration: %d\n", (int)timeout));

    *cmd_done = true;
    return status;
#endif
    return TRUE;
}

/***********************************************************************************
  Subject:    SoftStop
  Function:   INTERN_DVBC_SoftStop
  Parmeter:
  Return:     BOOLEAN
  Remark:
************************************************************************************/
BOOLEAN INTERN_DVBC_SoftStop ( void )
{
#if 0
#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) //T3
    U16     u8WaitCnt=0;

    if (MDrv_ReadByte(MBRegBase + 0x00))
    {
        printf(">> MB Busy!\n");
        return FALSE;
    }

    MDrv_WriteByte(MBRegBase + 0x00, 0xA5);                 // MB_CNTL set read mode

    MDrv_WriteByte(DMDMcuBase + 0x03, 0x02);                // assert interrupt to VD MCU51
    MDrv_WriteByte(DMDMcuBase + 0x03, 0x00);                // de-assert interrupt to VD MCU51

    while(MDrv_ReadByte(MBRegBase + 0x00)!= 0x5A)           // wait MB_CNTL set done
    {
#if TEST_EMBEDED_DEMOD
        INTERN_DVBC_Delayms(1);  // << Ken 20090629
#endif
        if (u8WaitCnt++ >= 0xFF)
        {
            printf(">> DVBC SoftStop Fail!\n");
            return FALSE;
        }
    }

    //MDrv_WriteByte(MBRegBase + 0x00, 0x01);                       // reset VD_MCU
    MDrv_WriteByte(MBRegBase + 0x00, 0x00);                 // MB_CNTL clear

#endif
#endif

    return TRUE;
}

/***********************************************************************************
  Subject:    Reset
  Function:   INTERN_DVBC_Reset
  Parmeter:
  Return:     BOOLEAN
  Remark:
************************************************************************************/
BOOLEAN INTERN_DVBC_Reset ( void )
{
    DBG_INTERN_DVBC(printf(" @INTERN_DVBC_reset\n"));

    INTERN_DVBC_SoftStop();

    MDrv_WriteByte(DMDMcuBase + 0x00, 0x01);    // reset DMD_MCU
//    INTERN_DVBC_WriteReg(0x2002, 0x72);       // reset DVB-C
    INTERN_DVBC_Delayms(5);
//    INTERN_DVBC_WriteReg(0x2002, 0x52);
    MDrv_WriteByte(DMDMcuBase + 0x00, 0x00);
    INTERN_DVBC_Delayms(5);
    //FECLock = FALSE;
    FECUnlockCnt = 0;
    return TRUE;
}


/***********************************************************************************
  Subject:    Exit
  Function:   INTERN_DVBC_Exit
  Parmeter:
  Return:     BOOLEAN
  Remark:
************************************************************************************/
BOOLEAN INTERN_DVBC_Exit ( void )
{
    INTERN_DVBC_SoftStop();

    //diable clk gen
    MDrv_WriteByte(0x10330a, 0x01);   // reg_ckg_atsc_adcd_sync@0x05[3:0] : ADCCLK
    MDrv_WriteByte(0x10330b, 0x00);

    MDrv_WriteByte(0x10330c, 0x01);   // reg_ckg_dvbtc_inner1x@0x06[3:0] : MPLLDIV10/4=21.5MHz
    MDrv_WriteByte(0x10330d, 0x01);   // reg_ckg_dvbtc_inner2x@0x06[11:8]: MPLLDIV10/2=43.2MHz

    MDrv_WriteByte(0x10330e, 0x01);   // reg_ckg_dvbtc_inner4x@0x07[3:0] : MPLLDIV10=86.4MHz
    MDrv_WriteByte(0x10330f, 0x00);

    MDrv_WriteByte(0x103310, 0x01);   // reg_ckg_dvbtc_outer1x@0x08[3:0] : MPLLDIV10/2=43.2MHz
    MDrv_WriteByte(0x103311, 0x01);   // reg_ckg_dvbtc_outer2x@0x08[11:8]: MPLLDIV10=86.4MHz

    MDrv_WriteByte(0x103312, 0x05);   // dvbt_t:0x0000, dvb_c: 0x0004
    MDrv_WriteByte(0x103313, 0x00);

    MDrv_WriteByte(0x103314, 0x01);   // reg_ckg_dvbtc_adc@0x0a[3:0] : ADC_CLK
    MDrv_WriteByte(0x103315, 0x01);   // reg_ckg_dvbtc_innc@0x0a[11:8]

    MDrv_WriteByte(0x103316, 0x01);   // reg_ckg_dvbtc_eq8x@0x0b[3:0] : MPLLDIV3/2=144MHz
    MDrv_WriteByte(0x103317, 0x01);   // reg_ckg_dvbtc_eq@0x0b[11:8] : MPLLDIV3/16=18MHz

    MDrv_WriteByte(0x103318, 0x11);   // reg_ckg_dvbtc_sram0~3@0x0c[13:0]
    MDrv_WriteByte(0x103319, 0x11);

    MDrv_WriteByte(0x103308, 0x01);   // parallel mode:0x0001 / serial mode: 0x0401
    MDrv_WriteByte(0x103309, 0x05);   // reg_ckg_dvbtc_ts@0x04

#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_A7 ) //T3
        MDrv_WriteByte(0x101E3E, 0x00);     // DVBC = BIT2 clear
#endif

    return TRUE;
}

/***********************************************************************************
  Subject:    Load DSP code to chip
  Function:   INTERN_DVBC_LoadDSPCode
  Parmeter:
  Return:     BOOLEAN
  Remark:
************************************************************************************/
static BOOLEAN INTERN_DVBC_LoadDSPCode(void)
{
    U8  udata = 0x00;
    U16 i;
    U16 fail_cnt=0;

#if (DBG_DUMP_LOAD_DSP_TIME==1)
    U32 u32Time;
#endif

//#ifndef INTERN_DVBC_LOAD_FW_FROM_CODE_MEMORY
#if( INTERN_DVBC_LOAD_CODE_FROM_SEL == INTERN_DVBC_LOAD_CODE_FROM_BIN )
    BININFO BinInfo;
    BOOLEAN bResult;
    U32 u32GEAddr;
    U8 Data;
    S8 op;
    U32 srcaddr;
    U32 len;
    U32 SizeBy4K;
    U16 u16Counter=0;
    U8 *pU8Data;
#endif

#if 0
    if(MDrv_ReadByte(0x101E3E))
    {
        printf("Warring! Reg[0x101E3E]=%d\n", MDrv_ReadByte(0x101E3E));
        return FALSE;
    }
#endif

		if (LoadDspStatus == 0x02) //1: DVBT, 2:DVBC, 3:ATSC, 0xff: Null
		{
        // printf("Warning! LoadDspStatus=%d\n", LoadDspStatus);
			  return TRUE;
	  }
	  else
	  {
			  LoadDspStatus = 0xff; //1: DVBT, 2:DVBC, 3:ATSC, 0xff: Null
		}

    MDrv_Sys_DisableWatchDog();

    MDrv_WriteByte(DMDMcuBase + 0x00,  0x01);        // reset VD_MCU
    MDrv_WriteByte(DMDMcuBase + 0x01,  0x00);        // disable SRAM
    MDrv_WriteByte(DMDMcuBase + 0x03,  0x50);        // enable "vdmcu51_if"
    MDrv_WriteByte(DMDMcuBase + 0x03,  0x51);        // enable auto-increase
    MDrv_WriteByte(DMDMcuBase + 0x04,  0x00);        // sram address low byte
    MDrv_WriteByte(DMDMcuBase + 0x05,  0x00);        // sram address high byte

    ////  Load code thru VDMCU_IF ////
    DBG_INTERN_DVBC(printf(">Load Code...\n"));

#if 0//def INTERN_DVBC_LOAD_FW_FROM_CODE_MEMORY
    for ( i = 0; i < sizeof(INTERN_DVBC_table); i++)
    {
        MDrv_WriteByte(DMDMcuBase + 0x0C, INTERN_DVBC_table[i]); // write data to VD MCU 51 code sram
    }
#else
    BinInfo.B_ID = BIN_ID_INTERN_DVBC_DEMOD;
    msAPI_MIU_Get_BinInfo(&BinInfo, &bResult);
    if ( bResult != PASS )
    {
        return FALSE;
    }
    //printf("\t DEMOD_MEM_ADR  =%08LX\n", ((DEMOD_MEM_ADR & MIU1) ? (DEMOD_MEM_ADR | MIU_INTERVAL) : (DEMOD_MEM_ADR)));

  #ifdef SUPPORT_AP_BIN_IN_FLASH_2
    InfoBlock_Flash_2_Checking_Start(&BinInfo);
  #endif

    msAPI_MIU_Copy(BinInfo.B_FAddr, ((DEMOD_MEM_MEMORY_TYPE & MIU1) ? (DEMOD_MEM_ADR | MIU_INTERVAL) : (DEMOD_MEM_ADR)), MemAlign(BinInfo.B_Len, 8), MIU_FLASH2SDRAM);

  #ifdef SUPPORT_AP_BIN_IN_FLASH_2
    InfoBlock_Flash_2_Checking_End(&BinInfo);
  #endif

    //W1BaseAddr = MDrv_Sys_GetXdataWindow1Base();
    SizeBy4K=BinInfo.B_Len/0x1000;
    //printf("\t RRR: SizeBy4K=%d (L=%d)\n", SizeBy4K,BinInfo.B_Len);

  #if (DBG_DUMP_LOAD_DSP_TIME==1)
    u32Time = msAPI_Timer_GetTime0();
  #endif

    u32GEAddr = _PA2VA(((DEMOD_MEM_MEMORY_TYPE & MIU1) ? (DEMOD_MEM_ADR | MIU_INTERVAL) : (DEMOD_MEM_ADR)));

    for (i=0;i<=SizeBy4K;i++)
    {
        if(i==SizeBy4K)
            len=BinInfo.B_Len%0x1000;
        else
            len=0x1000;

        srcaddr = u32GEAddr+(0x1000*i);
        //printf("\t i = %08X\n", i);
        //printf("\t len = %08X\n", len);
        op = 1;
        u16Counter = 0 ;
        //printf("\t (B=0x%x)(Src=0x%x)Data =",i,srcaddr);
        while(len--)
        {
            u16Counter ++ ;
            //printf("file: %s, line: %d\n", __FILE__, __LINE__);
            //pU8Data = (U8 *)(srcaddr|0x80000000);
            pU8Data = (U8 *)(srcaddr|0x80000000);
            Data  = *pU8Data;

          #if 0
            if(u16Counter < 0x100)
                printf("0x%bx,", Data);
          #endif
            MDrv_WriteByte(DMDMcuBase + 0x0C, Data); // write data to VD MCU 51 code sram

            srcaddr += op;
        }
        //printf("\n\n\n");
    }

  #if (DBG_DUMP_LOAD_DSP_TIME==1)
    printf("------> INTERN_DVBC Load DSP Time:  (%lu)\n", msAPI_Timer_DiffTimeFromNow(u32Time)) ;
  #endif

#endif

    ////  Content verification ////
    DBG_INTERN_DVBC(printf(">Verify Code...\n"));

    MDrv_WriteByte(DMDMcuBase + 0x04, 0x00);         // sram address low byte
    MDrv_WriteByte(DMDMcuBase + 0x05, 0x00);         // sram address high byte

#if 0//def INTERN_DVBC_LOAD_FW_FROM_CODE_MEMORY
    for ( i = 0; i < sizeof(INTERN_DVBC_table); i++)
    {
        udata = MDrv_ReadByte(DMDMcuBase + 0x10);    // read sram data
        if (udata != INTERN_DVBC_table[i])
        {
            printf(">fail add = 0x%x\n", i);
            printf(">code = 0x%x\n", INTERN_DVBC_table[i]);
            printf(">data = 0x%x\n", udata);

            if (fail_cnt++ > 10)
            {
                printf(">DVB-C DSP Loadcode fail!");
                return false;
            }
        }
    }
#else
    for (i=0;i<=SizeBy4K;i++)
    {
        if(i==SizeBy4K)
            len=BinInfo.B_Len%0x1000;
        else
            len=0x1000;

        srcaddr = u32GEAddr+(0x1000*i);
        //printf("\t i = %08LX\n", i);
        //printf("\t len = %08LX\n", len);
        op = 1;
        u16Counter = 0 ;
        //printf("\t (B=0x%bx)(Src=0x%x)Data =",i,srcaddr);
        while(len--)
        {
            u16Counter ++ ;
            //printf("file: %s, line: %d\n", __FILE__, __LINE__);
            //pU8Data = (U8 *)(srcaddr|0x80000000);
            pU8Data = (U8 *)(srcaddr|0x80000000);
            Data  = *pU8Data;

          #if 0
            if(u16Counter < 0x100)
                printf("0x%bx,", Data);
          #endif
            udata = MDrv_ReadByte(DMDMcuBase + 0x10);    // read sram data
            if (udata != Data)
            {
                printf(">fail add = 0x%lx\n", (U32)((i*0x1000)+(0x1000-len)));
                printf(">code = 0x%x\n", Data);
                printf(">data = 0x%x\n", udata);

                if (fail_cnt++ > 10)
                {
                    printf(">DVB-C DSP Loadcode fail!");
                    return false;
                }
            }

            srcaddr += op;
        }
     //   printf("\n\n\n");
    }
#endif

    MDrv_WriteByte(DMDMcuBase + 0x03, 0x50);     // diable auto-increase
    MDrv_WriteByte(DMDMcuBase + 0x03, 0x00);     // disable "vdmcu51_if"
    MDrv_WriteByte(DMDMcuBase + 0x01, 0x01);     // enable SRAM
    MDrv_WriteByte(DMDMcuBase + 0x00, 0x00);     // release VD_MCU

    DBG_INTERN_DVBC(printf(">DSP Loadcode done."));
    //while(load_data_variable);
#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_A7 )
    MDrv_WriteByte(0x101E3E, 0x04);     // DVBC = BIT2 -> 0x04
#endif

		LoadDspStatus = 0x02; //1: DVBT, 2:DVBC, 3:ATSC, 0xff: Null
    return TRUE;
}

/***********************************************************************************
  Subject:    DVB-C CLKGEN initialized function
  Function:   INTERN_DVBC_Power_On_Initialization
  Parmeter:
  Return:     BOOLEAN
  Remark:
************************************************************************************/
void INTERN_DVBC_InitClkgen(void)
{
#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) //T3
    //<<CLK_GEN1_DVB_t >>
    if ( MDrv_ReadByte( 0x001ecf) == 0x00 )
    	MDrv_WriteByte(0x100b42, 0x10);   // reg_ckg_vdmcu@0x21[4:0]        (bank_CLKGEN0) //108MHz
    else  //after t3_u02
       	MDrv_WriteByte(0x100b42, 0x0D);   // reg_ckg_vdmcu@0x21[4:0]        (bank_CLKGEN0) //108MHz
    MDrv_WriteByte(0x100b43, 0x01);   // reg_ckg_vd200@0x21[11:8]

    MDrv_WriteByte(0x100b44, 0x00);   // enable mail-box clock          (bank_CLKGEN0)
    MDrv_WriteByte(0x100b45, 0x00);   // enable mail-box clock

    MDrv_WriteByte(0x103314, 0x00);   // reg_ckg_dvbtc_adc@0x0a[3:0] : ADC_CLK
    MDrv_WriteByte(0x103315, 0x01);   // reg_ckg_dvbtc_innc@0x0a[11:8]

    MDrv_WriteByte(0x10330a, 0x00);   // reg_ckg_atsc_adcd_sync@0x05[3:0] : ADCCLK
    MDrv_WriteByte(0x10330b, 0x00);

    MDrv_WriteByte(0x10330c, 0x00);   // reg_ckg_dvbtc_inner1x@0x06[3:0] : MPLLDIV10/4=21.5MHz
    MDrv_WriteByte(0x10330d, 0x00);   // reg_ckg_dvbtc_inner2x@0x06[11:8]: MPLLDIV10/2=43.2MHz

    MDrv_WriteByte(0x10330e, 0x00);   // reg_ckg_dvbtc_inner4x@0x07[3:0] : MPLLDIV10=86.4MHz
    MDrv_WriteByte(0x10330f, 0x00);

    MDrv_WriteByte(0x103310, 0x00);   // reg_ckg_dvbtc_outer1x@0x08[3:0] : MPLLDIV10/2=43.2MHz
    MDrv_WriteByte(0x103311, 0x00);   // reg_ckg_dvbtc_outer2x@0x08[11:8]: MPLLDIV10=86.4MHz

    MDrv_WriteByte(0x103312, 0x04);   // dvbt_t:0x0000, dvb_c: 0x0004
    MDrv_WriteByte(0x103313, 0x00);

    MDrv_WriteByte(0x103314, 0x00);   // reg_ckg_dvbtc_adc@0x0a[3:0] : ADC_CLK
    MDrv_WriteByte(0x103315, 0x00);   // reg_ckg_dvbtc_innc@0x0a[11:8]

    MDrv_WriteByte(0x103316, 0x00);   // reg_ckg_dvbtc_eq8x@0x0b[3:0] : MPLLDIV3/2=144MHz
    MDrv_WriteByte(0x103317, 0x00);   // reg_ckg_dvbtc_eq@0x0b[11:8] : MPLLDIV3/16=18MHz

    MDrv_WriteByte(0x103318, 0x00);   // reg_ckg_dvbtc_sram0~3@0x0c[13:0]
    MDrv_WriteByte(0x103319, 0x00);
#if 0 //parallel
    MDrv_WriteByte(0x103308, 0x01);   // parallel mode:0x0001 / serial mode: 0x0401
    MDrv_WriteByte(0x103309, 0x00);   // reg_ckg_dvbtc_ts@0x04

    MDrv_WriteByte(0x103300, 0x11);   // parallel mode: 0x0511 /serial mode 0x0400
#if(INTERN_DVBT_TS_PARALLEL_INVERSION == 0)
    MDrv_WriteByte(0x103301, 0x05);   // reg_ckg_dvbtmk_ts_out_mode@0x00
#else
    MDrv_WriteByte(0x103301, 0x07);   // reg_ckg_dvbtmk_ts_out_mode@0x00
#endif
#else // serial
    MDrv_WriteByte(0x103308, 0x01);   // parallel mode:0x0001 / serial mode: 0x0401
    MDrv_WriteByte(0x103309, 0x04);   // reg_ckg_dvbtc_ts@0x04

    MDrv_WriteByte(0x103300, 0x00);   // parallel mode: 0x0511 /serial mode 0x0400
#if(INTERN_DVBT_TS_SERIAL_INVERSION == 0)
    MDrv_WriteByte(0x103301, 0x04);   // reg_ckg_dvbtmk_ts_out_mode@0x00
#else
    MDrv_WriteByte(0x103301, 0x06);   // reg_ckg_dvbtmk_ts_out_mode@0x00
#endif
#endif
    //MDrv_WriteByte(0x101e22, 0x02);   // internal TS connect to TS0:0x0002; to TS1:0x0200
    //MDrv_WriteByte(0x101e23, 0x00);   // reg_ts0~1_mux@0x11         (bank_CHIP)

    //MDrv_WriteByte(0x100b50, 0x08);   // internal TS0:0x0108;   internal TS1:0x0801
    //MDrv_WriteByte(0x100b51, 0x08);   // reg_ckg_ts0~1@0x28         (bank_CLKGEN0) << Ken 20090629

    MDrv_WriteByte(0x101e04, 0x00);   // reg_if_agc_pad_oen@0x02    (bank_CHIP)
    MDrv_WriteByte(0x101e05, 0x00);

//----------------------------------------------------------------------------------------
#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD ) //T4
    //<<CLK_GEN1_DVB_t >>
    MDrv_WriteByte(0x10331e, 0x10);   		// reg_ckg_dmdmcu@0x21[4:0]        (bank_CLKGEN0) //108MHz
    MDrv_WriteByte(0x103480, 0x00);			// release dmdmcu_rst

    MDrv_WriteByte(0x103314, 0x00);   		// reg_ckg_dvbtc_adc@0x0a[3:0] : ADC_CLK
    MDrv_WriteByte(0x103315, 0x01);   		// reg_ckg_dvbtc_innc@0x0a[11:8]

    MDrv_WriteByte(0x10330a, 0x00);   		// reg_ckg_atsc_adcd_sync@0x05[3:0] : ADCCLK
    MDrv_WriteByte(0x10330b, 0x00);

    MDrv_WriteByte(0x10330c, 0x00);   		// reg_ckg_dvbtc_inner1x@0x06[3:0] : MPLLDIV10/4=21.5MHz
    MDrv_WriteByte(0x10330d, 0x00);   		// reg_ckg_dvbtc_inner2x@0x06[11:8]: MPLLDIV10/2=43.2MHz

    MDrv_WriteByte(0x10330e, 0x00);   		// reg_ckg_dvbtc_inner4x@0x07[3:0] : MPLLDIV10=86.4MHz
    MDrv_WriteByte(0x10330f, 0x00);

    MDrv_WriteByte(0x103310, 0x00);   		// reg_ckg_dvbtc_outer1x@0x08[3:0] : MPLLDIV10/2=43.2MHz
    MDrv_WriteByte(0x103311, 0x00);   		// reg_ckg_dvbtc_outer2x@0x08[11:8]: MPLLDIV10=86.4MHz

    MDrv_WriteByte(0x103312, 0x00);   		// dvbt_t:0x0000, dvb_c: 0x0004
    MDrv_WriteByte(0x103313, 0x00);

    MDrv_WriteByte(0x103314, 0x00);   		// reg_ckg_dvbtc_adc@0x0a[3:0] : ADC_CLK
    MDrv_WriteByte(0x103315, 0x00);   		// reg_ckg_dvbtc_innc@0x0a[11:8]

    MDrv_WriteByte(0x103316, 0x00);   		// reg_ckg_dvbtc_eq8x@0x0b[3:0] : MPLLDIV3/2=144MHz
    MDrv_WriteByte(0x103317, 0x00);   		// reg_ckg_dvbtc_eq@0x0b[11:8] : MPLLDIV3/16=18MHz

    MDrv_WriteByte(0x103318, 0x00);   		// reg_ckg_dvbtc_sram0~3@0x0c[13:0]
    MDrv_WriteByte(0x103319, 0x00);
/* Define from "config" function
#if 0 //parallel
    MDrv_WriteByte(0x103308, 0x01);   		// parallel mode:0x0001 / serial mode: 0x0401
    MDrv_WriteByte(0x103309, 0x00);   		// reg_ckg_dvbtc_ts@0x04

    MDrv_WriteByte(0x103300, 0x11);   		// parallel mode: 0x0511 /serial mode 0x0400

	#if(INTERN_DVBT_TS_PARALLEL_INVERSION == 0)
    	MDrv_WriteByte(0x103301, 0x05);   	// reg_ckg_dvbtmk_ts_out_mode@0x00
	#else
    	MDrv_WriteByte(0x103301, 0x07);   	// reg_ckg_dvbtmk_ts_out_mode@0x00
	#endif
#else // serial
    MDrv_WriteByte(0x103308, 0x01);   		// parallel mode:0x0001 / serial mode: 0x0401
    MDrv_WriteByte(0x103309, 0x04);   		// reg_ckg_dvbtc_ts@0x04

    MDrv_WriteByte(0x103300, 0x00);   		// parallel mode: 0x0511 /serial mode 0x0400
	#if(INTERN_DVBT_TS_SERIAL_INVERSION == 0)
    	MDrv_WriteByte(0x103301, 0x04); 	// reg_ckg_dvbtmk_ts_out_mode@0x00
	#else
    	MDrv_WriteByte(0x103301, 0x06); 	// reg_ckg_dvbtmk_ts_out_mode@0x00
	#endif
#endif
*/
// !!! mick TS0-->TS1
    //MDrv_WriteByte(0x101e22, 0x02);   		// internal TS connect to TS0:0x0002; to TS1:0x0200
    //MDrv_WriteByte(0x101e23, 0x00);   		// reg_ts0~1_mux@0x11         (bank_CHIP)

    //MDrv_WriteByte(0x100b50, 0x08);   		// internal TS0:0x0108;   internal TS1:0x0801
    //MDrv_WriteByte(0x100b51, 0x01);   		// reg_ckg_ts0~1@0x28         (bank_CLKGEN0) << Ken 20090629
    //reg_tagc_pwr@0x11286c[2]=0(off ATV gain control)
    //reg_if_agc_pad_oen@0x101e05[4]=0 (on, DTV gain control is by IF_AGC ,off, at this case)
    //reg_rf_agc_pad_oen@0x101e05[5]=1 (off, at this case)
// !!! mick
//Case-1 default
	MDrv_WriteByte(0x11286c, 0x00);			// wreg vdbank_DMD_ANA_MISC+0x20 0x0000
	MDrv_WriteByte(0x101e04, 0x00);   		// reg_if_agc_pad_oen@0x02    (bank_CHIP)
	MDrv_WriteByte(0x101e05, 0x00);
//Case-2
//	MDrv_WriteByte(0x11286c, 0x00);			// wreg vdbank_DMD_ANA_MISC+0x20 0x0000
//	MDrv_WriteByte(0x101e05, MDrv_ReadByte(0x101e05) & 0xCF);   // clear bit 12, 13
//----------------------------------------
//For T4 Add
//At Chip Top
	MDrv_WriteByte(0x101e9e, MDrv_ReadByte(0x101e9e) & 0x3F);   // Bit6,7 Clean=0
//  MDrv_WriteByte(0x101e9e, 0x00);   		// reg_agcgctrl
//  MDrv_WriteByte(0x101e9f, 0x00);
//mick
	//MDrv_WriteByte(0x101e05, MDrv_ReadByte(0x101e05) | 0x20);   // 0x101e04 Bit13 set=1
	//MDrv_WriteByte(0x101e05, MDrv_ReadByte(0x101e05) & 0xEF);   // 0x1010e4 Bit12 Clean=0
//mick	MDrv_WriteByte(0x101e05, MDrv_ReadByte(0x101e05) & 0xDF);   // Bit12 Clean=0
//	MDrv_WriteByte(0x101e04, 0x00);   		// reg_if_agc_pad_oen
//	MDrv_WriteByte(0x101e05, 0x00);

	MDrv_WriteByte(0x101eA1, MDrv_ReadByte(0x101eA1) & 0x7F);   // Bit15 Clean=0
//	MDrv_WriteByte(0x101eA0, 0x00);   		// reg_allpad_in
//	MDrv_WriteByte(0x101eA1, 0x00);
// ---------------------------------------
	MDrv_WriteByte(0x112002, 0x52);			// wreg vdbank_DEMOD_0+0x01 0052
	MDrv_WriteByte(0x112003, 0x00);			// Release Ana misc resest

	MDrv_WriteByte(0x112060, 0x00);			// ADC sign bit
	MDrv_WriteByte(0x112061, 0x00);

	MDrv_WriteByte(0x112064, 0x00);			// ADC I channel offset // wreg vdbank_DEMOD_0+0x32 0c00
	MDrv_WriteByte(0x112065, 0x0c);

	MDrv_WriteByte(0x112066, 0x00);			// ADC Q channel offset
	MDrv_WriteByte(0x112067, 0x0c);
// ---------------------------------------
// Enable DVBC demod (MailBox=0x1020)
	MDrv_WriteByte(0x112818, 0x03);			// Set enable ADC clock [ANA_PWDN_ADCI]
	MDrv_WriteByte(0x112819, 0x00);			// wreg vdbank_DMD_ANA_MISC+0x0c 0x0000
	INTERN_DVBC_Delayms(2);

	MDrv_WriteByte(0x11286a, 0x86);			// wreg vdbank_DMD_ANA_MISC+0x35 0x1e04
	MDrv_WriteByte(0x11286b, 0x1e);			// [ANA_MPLL_ICTRL]
	INTERN_DVBC_Delayms(2);
//L4 For Debug
//For MPLL Division Frequency
	MDrv_WriteByte(0x112860, 0x00);			// (24M*9*4)/19-->fixed to /18
	MDrv_WriteByte(0x112861, 0x12);
	INTERN_DVBC_Delayms(2);

// ---------------------------------------------------------------------
// DVBT , DVBC Clock Setting
// ---------------------------------------------------------------------
	MDrv_WriteByte(0x11286a, 0x06);			// Reset MPLL
	MDrv_WriteByte(0x11286b, 0x1e);			// wreg vdbank_DMD_ANA_MISC+0x35 0x1e04
	INTERN_DVBC_Delayms(2);

	MDrv_WriteByte(0x11286a, 0x06);			// Disable MPLL reset
	MDrv_WriteByte(0x11286b, 0x06);			// wreg vdbank_DMD_ANA_MISC+0x35 0x0604
	INTERN_DVBC_Delayms(2);

	MDrv_WriteByte(0x112866, 0x02);			// Set MPLL_LOOP_DIV_FIRST and SECOND
	MDrv_WriteByte(0x112867, 0x09);			// [ANA_MPLL_LOOP_DIV_FIRST]

	MDrv_WriteByte(0x112860, 0x00);			// Set MPLL_ADC_DIV_SEL [ANA_MPLL_CLK_DP_PD]
	MDrv_WriteByte(0x112861, 0x13);			// wreg vdbank_DMD_ANA_MISC+0x30 0x1300

	MDrv_WriteByte(0x112802, 0x40);			// Set IMUXS QMUXS [ANA_ADC_PWDNI]
    #if (VIF_SAW_ARCH!=4)
    MDrv_WriteByte(0x112803, 0x04);
    #else
    MDrv_WriteByte(0x112803, 0x12);
    #endif
	MDrv_WriteByte(0x112818, 0x00);			// Set enable ADC clock [ANA_PWDN_ADCI]
	MDrv_WriteByte(0x112819, 0x00);			// wreg vdbank_DMD_ANA_MISC+0x0c 0x0000

	MDrv_WriteByte(0x112840, 0x86);			// Disable PWDN_REF [ANA_VCLP]
	MDrv_WriteByte(0x112841, 0x1e);			// wreg vdbank_DMD_ANA_MISC+0x20 0x0000

	MDrv_WriteByte(0x100B28, MDrv_ReadByte(0x100B28) & 0xEE);   // CLKGEN0 Bit8,0 Clean=0 ,mick

	/************************************************************************
	 * T4 U02 ONLY.mick
	 * for T4 U02 and after, this bit0 is mux for DMD muc and HK,
	 * 0x101E39, bit0
	 * bit0: 0:HK can rw bank 0x1120, 1: DMD mcu can rw bank 0x1120;
	 ************************************************************************/
	MDrv_WriteByte(0x101E39, 0x01); //mux from HK to DMD MCU
	//printf("T4 CLK Gen Setting OK-----------------------------------------------\n");

#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_A7 ) //A7

    U8  	udatatemp = 0x00;

	MDrv_WriteByte(0x101E39, 0x00); //mux from DMD MCU to HK.
	// ----------------------------------------------
	//  start demod CLKGEN setting
	// ----------------------------------------------
	// *** Set register at CLKGEN1
	// enable DMD MCU clock "bit[0] set 0"
	// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h0f, 2'b11, 16'h001c);
	// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h0f, 2'b11, 16'h001c);
	MDrv_WriteByte(0x10331f,0x00);
	MDrv_WriteByte(0x10331e,0x10);

	// set parallet ts clock
	// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h00, 2'b11, 16'h0511);
	// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h00, 2'b11, 16'h0511);
	MDrv_WriteByte(0x103301,0x06);//06
	MDrv_WriteByte(0x103300,0x0b);//19

	// enable atsc, DVBTC ts clock
	// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h04, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h04, 2'b11, 16'h0000);
	MDrv_WriteByte(0x103309,0x00);
	MDrv_WriteByte(0x103308,0x00);

	// enable dvbc adc clock
	// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h0a, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h0a, 2'b11, 16'h0000);
	MDrv_WriteByte(0x103315,0x00);
	MDrv_WriteByte(0x103314,0x00);

	// enable vif DAC clock
	// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h0d, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h0d, 2'b11, 16'h0000);
	MDrv_WriteByte(0x10331b,0x00);
	MDrv_WriteByte(0x10331a,0x00);

	// *** Set register at CLKGEN_DMD
	// enable atsc clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h01, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h01, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f03,0x00);
	MDrv_WriteByte(0x111f02,0x00);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h02, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h02, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f05,0x00);
	MDrv_WriteByte(0x111f04,0x00);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h03, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h03, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f07,0x00);
	MDrv_WriteByte(0x111f06,0x00);

	// enable clk_atsc_adcd_sync
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h05, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h05, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f0b,0x00);
	MDrv_WriteByte(0x111f0a,0x00);

	// enable dvbt inner clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h06, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h06, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f0d,0x00);
	MDrv_WriteByte(0x111f0c,0x00);

	// enable dvbt inner clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h07, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h07, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f0f,0x00);
	MDrv_WriteByte(0x111f0e,0x00);

	// enable dvbt inner clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h08, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h08, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f11,0x00);
	MDrv_WriteByte(0x111f10,0x00);

	// enable dvbc outer clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h09, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h09, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f13,0x00);
	MDrv_WriteByte(0x111f12,0x00);

	// enable dvbc inner-c clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0a, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0a, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f15,0x00);
	MDrv_WriteByte(0x111f14,0x00);

	// enable dvbc eq clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0b, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0b, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f17,0x00);
	MDrv_WriteByte(0x111f16,0x00);

	// enable sram clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f19,0x00);
	MDrv_WriteByte(0x111f18,0x00);

	// enable vif clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0e, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0e, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f1d,0x00);
	MDrv_WriteByte(0x111f1c,0x00);

	// enable DEMODE-DMA clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h10, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h10, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f21,0x00);
	MDrv_WriteByte(0x111f20,0x00);

	// select clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h11, 2'b11, 16'h0444);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h11, 2'b11, 16'h0444);
	MDrv_WriteByte(0x111f23,0x00);
	MDrv_WriteByte(0x111f22,0x00);

	// Enable SAWLESS clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h12, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h12, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f25,0x00);
	MDrv_WriteByte(0x111f24,0x00);

#if 0
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h1111);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h1111);
	MDrv_WriteByte(0x111f19,0x11);
	MDrv_WriteByte(0x111f18,0x11);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h2222);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h2222);
	MDrv_WriteByte(0x111f19,0x22);
	MDrv_WriteByte(0x111f18,0x22);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h3333);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h3333);
	MDrv_WriteByte(0x111f19,0x33);
	MDrv_WriteByte(0x111f18,0x33);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f19,0x00);
	MDrv_WriteByte(0x111f18,0x00);

	// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h21, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h21, 2'b11, 16'h0000);
	MDrv_WriteByte(0x100b43,0x00);
	MDrv_WriteByte(0x100b42,0x00);

	MDrv_WriteByte(0x1120A0, 0x00);
	MDrv_WriteByte(0x1120A1, 0x00);

	// ----------------------------------------------
	//  start demod CLKGEN setting
	// ----------------------------------------------

	// reg_allpad_in=0
	// `RIU_W((`RIUBASE_CHIP>>1)+7'h50, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CHIP>>1)+7'h50, 2'b11, 16'h0000);
	MDrv_WriteByte(0x101ea1,0x00);
	MDrv_WriteByte(0x101ea0,0x00);
#endif

	// reg_ts1config=2
	// `RIU_W((`RIUBASE_CHIP>>1)+7'h57, 2'b11, 16'h1000);
	// `RIU_W((`RIUBASE_CHIP>>1)+7'h57, 2'b11, 16'h1000);
	//MDrv_WriteByte(0x101eaf,0x10);
	//MDrv_WriteByte(0x101eae,0x00);

	//  select DMD MCU
	// `RIU_W((`RIUBASE_CHIP>>1)+7'h1c, 2'b10, 16'h0300);
	// `RIU_W((`RIUBASE_CHIP>>1)+7'h1c, 2'b10, 16'h0300);
	MDrv_WriteByte(0x101e39,0x03);

#if 0
	// ----------------------------------------------
	//  Turn TSP
	// ----------------------------------------------

	// turn on ts0_config
	// `RIU_W((`RIUBASE_CHIP>>1)+7'h57   , 2'b11, 16'h0100);
	// `RIU_W((`RIUBASE_CHIP>>1)+7'h57   , 2'b11, 16'h0100);
	//MDrv_WriteByte(0x101eaf,0x01);
	//MDrv_WriteByte(0x101eae,0x00);

	// turn on tsp_clk
	// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h2a, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h2a, 2'b11, 16'h0000);
	MDrv_WriteByte(0x100b55,0x00);
	MDrv_WriteByte(0x100b54,0x00);

	// turn on ts1_clk, ts0_clk
	// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h28, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h28, 2'b11, 16'h0000);
	MDrv_WriteByte(0x100b51,0x00);
	MDrv_WriteByte(0x100b50,0x00);

	// turn on 2_clk
	// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h29, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h29, 2'b11, 16'h0000);
	MDrv_WriteByte(0x100b53,0x00);
	MDrv_WriteByte(0x100b52,0x00);

	// if the next line is not marked, the data is from demod, else is from ts0 pad
	// set the ts0 input from demod
	// `RIU_W((`RIUBASE_CHIP>>1)+7'h11   , 2'b11, 16'h0002);
	// `RIU_W((`RIUBASE_CHIP>>1)+7'h11   , 2'b11, 16'h0002);
	MDrv_WriteByte(0x101e23,0x00);
	MDrv_WriteByte(0x101e22,0x02);

	// set the ts0_clk from demod
	// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h28 , 2'b11, 16'h000c);
	// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h28 , 2'b11, 16'h000c);
	MDrv_WriteByte(0x100b51,0x00);
	MDrv_WriteByte(0x100b50,0x0c);
#endif

	// stream2miu_en, activate rst_wadr
	// `RIU_W((`RIUBASE_TSP0 >>1) + `REG16_HW_CONFIG8, 2'b11, 16'h0012);

	// stream2miu_en, turn off rst_wadr
	// `RIU_W((`RIUBASE_TSP0 >>1) + `REG16_HW_CONFIG8, 2'b11, 16'h0102);
	MDrv_WriteByte(0x103c0e,0x01);

	//MDrv_WriteByte(0x000e13,0x01);
    udatatemp = MDrv_ReadByte(0x000e13);
    MDrv_WriteByte(0x000e13, udatatemp&0xFB);//Set 0e12,Bit10=0,

#else

//#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S8 )
#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S8 )
	U8 tmp;

	INTERN_DVBC_Write_VD_DMD_Byte(0x101E39, 0x00); //mux from DMD MCU to HK.

    //------------------- initial by DMD START---------------------------
     INTERN_DVBC_Write_VD_DMD_Byte(0x112002, 0x52);                            // wreg vdbank_DEMOD_0+0x01 0052
     INTERN_DVBC_Write_VD_DMD_Byte(0x112003, 0x00);                            // Release Ana misc resest
     INTERN_DVBC_Write_VD_DMD_Byte(0x112060, 0x00);                            // ADC sign bit
     INTERN_DVBC_Write_VD_DMD_Byte(0x112061, 0x00);
     INTERN_DVBC_Write_VD_DMD_Byte(0x112064, 0x00);                            // ADC I channel offset // wreg vdbank_DEMOD_0+0x32 0c00
     INTERN_DVBC_Write_VD_DMD_Byte(0x112065, 0x0c);
     INTERN_DVBC_Write_VD_DMD_Byte(0x112066, 0x00);                            // ADC Q channel offset
     INTERN_DVBC_Write_VD_DMD_Byte(0x112067, 0x0c);
     // ---------------------------------------
     INTERN_DVBC_Write_VD_DMD_Byte(0x112818, 0x03);                            // wreg vdbank_DMD_ANA_MISC+0x35 0x1e04

     INTERN_DVBC_Write_VD_DMD_Byte(0x112868, 0x00);                            // Set enable ADC clock [ANA_PWDN_ADCI]
     INTERN_DVBC_Write_VD_DMD_Byte(0x112869, 0x00);                            // wreg vdbank_DMD_ANA_MISC+0x0c 0x0000

     // enable ADC related parameter.
     INTERN_DVBC_Write_VD_DMD_Byte(0x11286a, 0x04);                            // wreg vdbank_DMD_ANA_MISC+0x35 0x1e04
     INTERN_DVBC_Write_VD_DMD_Byte(0x11286b, 0x06);                            // [ANA_MPLL_ICTRL]
     INTERN_DVBC_Delayms(2);

     // ---------------------------------------------------------------------
     // DVBT , DVBC Clock Setting
     // ---------------------------------------------------------------------
     INTERN_DVBC_Write_VD_DMD_Byte(0x112866, 0x00);                            // Set MPLL_LOOP_DIV_FIRST and SECOND
     INTERN_DVBC_Write_VD_DMD_Byte(0x112867, 0x24);                            // [ANA_MPLL_LOOP_DIV_FIRST]
     INTERN_DVBC_Write_VD_DMD_Byte(0x112860, 0x01);                            // Set MPLL_ADC_DIV_SEL [ANA_MPLL_CLK_DP_PD]
     INTERN_DVBC_Write_VD_DMD_Byte(0x112861, 0x13);                            // wreg vdbank_DMD_ANA_MISC+0x30 0x1300

     INTERN_DVBC_Write_VD_DMD_Byte(0x112802, 0x40);                            // Set IMUXS QMUXS [ANA_ADC_PWDNI]
     #if (VIF_SAW_ARCH!=4)
     MDrv_WriteByte(0x112803, 0x04);
     #else
     MDrv_WriteByte(0x112803, 0x12);
     #endif
/*
#if(FRONTEND_TUNER_TYPE!=MSTAR_AVATAR2)
     INTERN_DVBC_Write_VD_DMD_Byte(0x112816, 0x05);                            // Set enable ADC clock [ANA_PWDN_ADCI]
#endif
*/

	 INTERN_DVBC_Write_VD_DMD_Byte(0x112816, 0x05);
     INTERN_DVBC_Write_VD_DMD_Byte(0x112817, 0x05);                            // wreg vdbank_DMD_ANA_MISC+0x0c 0x0000

     // wreg vdbank_DMD_ANA_MISC+0x0c 0x0000

     //INTERN_DVBC_Write_VD_DMD_Byte(0x112818, 0x03);                            // Disable PWDN_REF [ANA_VCLP]
     INTERN_DVBC_Write_VD_DMD_Byte(0x112818, 0x00);                        // wreg vdbank_DMD_ANA_MISC+0x20 0x0000
     INTERN_DVBC_Write_VD_DMD_Byte(0x112819, 0x00);                        // wreg vdbank_DMD_ANA_MISC+0x20 0x0000
     INTERN_DVBC_Delayms(2);
     INTERN_DVBC_Write_VD_DMD_Byte(0x112840, 0x00);                        // wreg vdbank_DMD_ANA_MISC+0x20 0x0000
     INTERN_DVBC_Write_VD_DMD_Byte(0x112841, 0x00);                        // wreg vdbank_DMD_ANA_MISC+0x20 0x0000
     INTERN_DVBC_Write_VD_DMD_Byte(0x11286c, 0x00);                        // wreg vdbank_DMD_ANA_MISC+0x20 0x0000
     INTERN_DVBC_Write_VD_DMD_Byte(0x1120A0, 0x00);
     INTERN_DVBC_Write_VD_DMD_Byte(0x1120A1, 0x00);

     //------------------- initial by DMD END-----------------------------

     MDrv_WriteByte(0x10331E, 0x10); 		// reg_ckg_vdmcu@0x21[4:0]        (bank_CLKGEN0) //108MHz
     // reg_ckg_dvbtc_adc@0x0a[3:0] (Enable clk_adcd_p at adcd_sync module)
     MDrv_WriteByte(0x103314, 0x00);
     // reg_ckg_atsc_adcd_sync@0x05[3:0] Enable clk_atsc_adcd_sync(adcd_sync module) =ADC Clock.
     MDrv_WriteByte(0x111f0a, 0x00);
     MDrv_WriteByte(0x111f0B, 0x00);
     // reg_ckg_atsc200_ph3@0x01[11:8] „³ 24*29/2/2=174MHz
	 // reg_ckg_atsc200_ph1@0x01[3:0]   „³ 24*29/2/2=174MHz + 900 shift
	 MDrv_WriteByte(0x111f02, 0x01);
     MDrv_WriteByte(0x111f03, 0x01);
     // reg_ckg_atsc25@0x02[11:8] „³ 24*29/2/7/2=24.85MHz
	 // reg_ckg_atsc50@0x02[3:0] „³ 24*29/2/7=49.7MHz
	 MDrv_WriteByte(0x111f04, 0x01);
     MDrv_WriteByte(0x111f05, 0x01);
     // reg_ckg_atsc_ce25@0x03[11:8] „³ 24*29/2/16=21.75MHz
	 // reg_ckg_atsc_eq25@0x03[3:0] „³ 24*29/2/2/8=21.75MHz
	 MDrv_WriteByte(0x111f06, 0x01);
     MDrv_WriteByte(0x111f07, 0x01);
     // reg_ckg_dvbtc_inner2x@0x06[11:8] (DVBT Only !)
	 // reg_ckg_dvbtc_inner1x@0x06[3:0] (DVBT Only !)
	 MDrv_WriteByte(0x111f0c, 0x00);
     MDrv_WriteByte(0x111f0D, 0x00);
     // reg_ckg_dvbtc_inner4x@0x07[3:0] (DVBT Only !)
     MDrv_WriteByte(0x111f0E, 0x00);
     // reg_ckg_dvbtc_outer2x@0x08[11:8] (DVBT Only !)
	 // reg_ckg_dvbtc_outer1x@0x08[3:0] (DVBT Only!)
	 MDrv_WriteByte(0x111f10, 0x01);
     MDrv_WriteByte(0x111f11, 0x01);
     // reg_ckg_dvbtc_outer2x_c@0x09[3:0]
     MDrv_WriteByte(0x111f12, 0x00);
     // reg_ckg_dvbtc_innc@0x0a[11:8] (DVBC only !)
     MDrv_WriteByte(0x111f15, 0x00);
     // reg_ckg_dvbtc_eq8x@0x0b[11:8]  (DVBC only!)
	 // reg_ckg_dvbtc_eq@0x0b[3:0] (DVBC Only !)
	 MDrv_WriteByte(0x111f16, 0x00);
	 MDrv_WriteByte(0x111f17, 0x00);
	 // reg_ckg_dvbtc_sram3@0x0c[13:12]
	 // reg_ckg_dvbtc_sram2@0x0c[9:8]
	 // reg_ckg_dvbtc_sram1@0x0c[5:4]
	 // reg_ckg_dvbtc_sram0@0x0c[1:0]
	 MDrv_WriteByte(0x111f18, 0x11);
	 MDrv_WriteByte(0x111f19, 0x11);
	 // reg_ckg_demod_test_in_en@0x00[11]
	 // reg_ckg_dvbtm_ts_out_mode@0x00[10] „³ set 1¡¦b1 use Non-gating clock.
	 // reg_ckg_atsc_dvbtc_ts_inv@0x00[9] -> Invert PAD_TS1_CLK polarity !
	 // reg_ckg_atsc_dvb_div_sel@0x00[8]
	 //   -> clk_atsc_dvb_div= 0: MPLLDIV2(24*29/2=348MHz), 1:MPLLDIV3(24*29/3=232MHz)
	 // reg_ckg_dvbtm_ts_divnum@0x00[4:0]
	 //   -> clk_atsc_dvb_div (MHz) / ((reg_ckg_dvbtm_ts_divnum+1)*2)
	 MDrv_WriteByte(0x103300, 0x11);
	 MDrv_WriteByte(0x103301, 0x05);
	 // reg_ckg_dvbtc_ts@0x04[11:8]
	 // reg_ckg_atsc_ts@0x04[3:0]
#if(INTERN_DVBC_TS_SERIAL_INVERSION == 0)
	//`RIU_W((`RIUBASE_CLKGEN1>>1)+7'h04, 2'b11, 16'h0100);// ts clock= ts_div_clk(parallel-TS Mode)
    INTERN_DVBC_Write_VD_DMD_Byte(0x103308, 0x01);
    INTERN_DVBC_Write_VD_DMD_Byte(0x103309, 0x00);
#else
	//`RIU_W((`RIUBASE_CLKGEN1>>1)+7'h04, 2'b11, 16'h????);// ts clock= 62MHz(Series-TS Mode)
    INTERN_DVBC_Write_VD_DMD_Byte(0x103308, 0x01);
    INTERN_DVBC_Write_VD_DMD_Byte(0x103309, 0x04);
#endif
	// reg_ckg_vifdbb_144m@0x0e[11:8] „³ 144MHz
 	// reg_ckg_vifdbb_43m@0x0e[3:0] „³ 43.2MHz
 	MDrv_WriteByte(0x111f1C, 0x01);
 	MDrv_WriteByte(0x111f1D, 0x01);
 	 // reg_ckg_vifdbb_vdac@0x0d[11:8] „³ 43.2MHz
	 // reg_ckg_vifdbb_dac@0x0d[3:0] „³ 43.2MHz
	MDrv_WriteByte(0x111f1A, 0x01);
	MDrv_WriteByte(0x111f1B, 0x01);
	//-------------------------------------------------------------------
	// Enable TS PAD
	//-------------------------------------------------------------------

	// Set reg_ts1config@0x57[13:11]-reg_CHIPTOP = 3¡¦bx10, DMD will output Transport stream to PAD_TS1_XX
	// wriu 0x101eaf 8'bxxx1_0xxx
    tmp = 0x10;
    INTERN_DVBC_Write_VD_DMD_Byte(0x101e9e, 0x00);
    INTERN_DVBC_Write_VD_DMD_Byte(0x101eaf, tmp);
//-------------------------------------------------------------------
// Enable RF_AGC, IF_AGC PAD
//-------------------------------------------------------------------

// reg_agcgctrl = 2¡¦d2 „³ PAD_RF_AGC(up_agc) , PAD_IF_AGC(dn_agc) is for Demod control Tuner. by up/dn AGC mode
// reg_agcgctrl = 2¡¦d1 „³ PAD_TGPIO0(up_agc) , PAD_TGPIO1(dn_agc) is for Demod control Tuner by up/dn AGC mode.
// reg_agcgctrl = 2¡¦d0 „³ PAD_RF_AGC , PAD_IF_AGC is for Demod control Tuner. by PWM AGC mode
// reg_if_agc_pad_oen@reg_CHIPTOP-0x02[12]  set 1¡¦b0 to enable PAD_IF_AGC
// reg_rf_agc_pad_oen@reg-CHIPTOP-0x02[13] set 1¡¦b0 to enable PAD_RF_AGC.
// wriu 0x101e05 8'bxx00_xxxxtmp = INTERN_DVBT_Read_VD_DMD_Byte(0x101e05);
	tmp = INTERN_DVBC_Read_VD_DMD_Byte(0x101e05);
	tmp &= ~0x30;
	INTERN_DVBC_Write_VD_DMD_Byte(0x101e05, tmp);

	INTERN_DVBC_Write_VD_DMD_Byte(0x101ea0, 0x00);
	INTERN_DVBC_Write_VD_DMD_Byte(0x101ea1, 0x00);

	INTERN_DVBC_Write_VD_DMD_Byte(0x101E39, 0x03); //mux from HK to DMD MCU.
#endif

#endif
}
/***********************************************************************************
  Subject:    Power on initialized function
  Function:   INTERN_DVBC_Power_On_Initialization
  Parmeter:
  Return:     BOOLEAN
  Remark:
************************************************************************************/

BOOLEAN INTERN_DVBC_Power_On_Initialization ( void )
{
    U8            status = true;
    U8            cal_done = 0;
    U16  tmpValue1;
    msAPI_Tuner_ResetDemodMode();
    UNUSED(cal_done);
    //INTERN_DVBC_InitRegBase();
	  LoadDspStatus = 0xff; //1: DVBT, 2:DVBC, 3:ATSC, 0xff: Null

    INTERN_DVBC_InitClkgen();

    //// Firmware download //////////
    DBG_INTERN_DVBC(printf("INTERN_DVBC Load DSP...\n"));
//    MsOS_DelayTask(100);

#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) //T3
    if (MDrv_ReadByte(0x101E3E) != 0x04) // DVBC = BIT2 -> 0x04
    {
        if (INTERN_DVBC_LoadDSPCode() == FALSE)
        {
            printf("T3 DVB-C Load DSP Code Fail\n");
            return FALSE;
        }
        else
        {
            printf("T3 DVB-C Load DSP Code OK\n");
        }
    }
#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD ) //T4
				if (INTERN_DVBC_LoadDSPCode() == FALSE)
				{
				    printf("T4 DVB-C Load DSP Code Fail\n");
				    return FALSE;
				}
				else
				{
				    printf("T4 DVB-C Load DSP Code OK\n");
				}
#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_A7 ) //A7
				if (INTERN_DVBC_LoadDSPCode() == FALSE)
				{
				    printf("A7 DVB-C Load DSP Code Fail\n");
				    return FALSE;
				}
				else
				{
				    printf("A7 DVB-C Load DSP Code OK\n");
				}
#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S8 ) //T8
				if (INTERN_DVBC_LoadDSPCode() == FALSE)
				{
				    printf("T8 DVB-C Load DSP Code Fail\n");
				    return FALSE;
				}
				else
				{
				    printf("T8 DVB-C Load DSP Code OK\n");
				}
#endif

#if 1
    //// MCU Reset //////////
    DBG_INTERN_DVBC(printf("INTERN_DVBC Reset...\n"));
    if (INTERN_DVBC_Reset() == FALSE)
    {
        DBG_INTERN_DVBC(printf("Fail\n"));
        return FALSE;
    }
    else
    {
        DBG_INTERN_DVBC(printf("OK\n"));
    }
#endif
	//// Init DVBC DSP Register //////////
#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_S8)
	status &= INTERN_DVBC_DSPReg_Init();
#endif

    //status &= INTERN_DVBC_Reset();

    status &= INTERN_DVBC_DSPReg_Init();

//    INTERN_DVBC_ReadReg(0x8000, &gu8ChipRevId);
//    DBG_INTERN_DVBC(printf("DVB-C RevID:%bx\n", gu8ChipRevId));

    //// DAC calibration //////////
//    DBG_INTERN_DVBC(printf("INTERN_DVBC Cal DAC...\n"));
//
//    gsCmdPacket.cmd_code = CMD_DAC_CALI;
//    gsCmdPacket.param[dac_op_code] = DAC_RUN_CALI;
//    status &= INTERN_DVBC_Cmd_Packet_Send(&gsCmdPacket, 1);
//    status &= INTERN_DVBC_Cmd_Packet_Exe_Check(&cal_done);
//    if (cal_done == true)
//    {
//        DBG_INTERN_DVBC(printf("OK\n"));
//        status &= INTERN_DVBC_ReadReg(0x81A8, &gCalIdacCh0);
//        status &= INTERN_DVBC_ReadReg(0x81A9, &gCalIdacCh1);
//    }
//    else
//    {
//        gCalIdacCh0 = gCalIdacCh1 = 0;
//        DBG_INTERN_DVBC(printf("FAIL\n"));
//    }

	////////////////print INTERN_DVBC_Version/////////////////////////
       INTERN_DVBC_Version(&tmpValue1);
        printf("@@@@(1)Demod DSP FW Version number = R%d.%d\n",(tmpValue1>>8), (tmpValue1&0x000f));
	////////////////////////////////////////////////////////////////

    return status;
}

/************************************************************************************************
  Subject:    Driving control
  Function:   INTERN_DVBC_Driving_Control
  Parmeter:   bInversionEnable : TRUE For High
  Return:      void
  Remark:
*************************************************************************************************/
void INTERN_DVBC_Driving_Control(BOOLEAN bEnable)
{
    U8    u8Temp;

    u8Temp = MDrv_ReadByte(0x101E10);

    if (bEnable)
    {
       u8Temp = u8Temp | 0x01; //bit0: clk, bit1~8:data , bit9: sync, bit10:valid
    }
    else
    {
       u8Temp = u8Temp & (~0x01);
    }

    DBG_INTERN_DVBC(printf("---> INTERN_DVBC_Driving_Control(Bit0) = 0x%bx \n",u8Temp));
    MDrv_WriteByte(0x101E10, u8Temp);
}
/************************************************************************************************
  Subject:    Clk Inversion control
  Function:   INTERN_DVBC_Clk_Inversion_Control
  Parmeter:   bInversionEnable : TRUE For Inversion Action
  Return:      void
  Remark:
*************************************************************************************************/
void INTERN_DVBC_Clk_Inversion_Control(BOOLEAN bInversionEnable)
{
    U8    u8Temp;

    u8Temp = MDrv_ReadByte(0x103301);

    if (bInversionEnable)
    {
       u8Temp = u8Temp | 0x02; //bit 9: clk inv
    }
    else
    {
       u8Temp = u8Temp & (~0x02);
    }

    DBG_INTERN_DVBC(printf("---> Inversion(Bit9) = 0x%bx \n",u8Temp));
    MDrv_WriteByte(0x103301, u8Temp);
}
/************************************************************************************************
  Subject:    Transport stream serial/parallel control
  Function:   INTERN_DVBC_Serial_Control
  Parmeter:   bEnable : TRUE For serial
  Return:     BOOLEAN :
  Remark:
*************************************************************************************************/
BOOLEAN INTERN_DVBC_Serial_Control(BOOLEAN bEnable)
{
    U8            status = true;

    DBG_INTERN_DVBC(printf(" @INTERN_DVBC_ts... \n"));

    if (bEnable)    //Serial mode for TS pad
    {
        // serial
        MDrv_WriteByte(0x103308, 0x01);   // serial mode: 0x0401
        MDrv_WriteByte(0x103309, 0x04);   // reg_ckg_dvbtc_ts@0x04

        MDrv_WriteByte(0x103300, 0x00);   // serial mode 0x0400
#if(INTERN_DVBC_TS_SERIAL_INVERSION == 0)
        MDrv_WriteByte(0x103301, 0x04);   // reg_ckg_dvbtmk_ts_out_mode@0x00
#else
        MDrv_WriteByte(0x103301, 0x06);   // reg_ckg_dvbtmk_ts_out_mode@0x00
#endif

        MDrv_WriteByte(0x101EA5, MDrv_ReadByte(0x101EA5)&0xEF);   // PAD_TS1 is used as output

#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S8 )
        //// INTERN_DVBC TS Control: Serial //////////

        status &= INTERN_DVBC_WriteDspReg(0x24, TS_SERIAL);

#if(INTERN_DVBC_TS_SERIAL_INVERSION == 0)
        status &= INTERN_DVBC_WriteDspReg(0x26, 0);
#else
        status &= INTERN_DVBC_WriteDspReg(0x26, 1);
#endif
#endif

        //// INTERN_DVBC TS Control: Serial //////////
        gsCmdPacket.cmd_code = CMD_TS_CTRL;

        gsCmdPacket.param[0] = TS_SERIAL;
#if(INTERN_DVBT_TS_SERIAL_INVERSION == 0)
        gsCmdPacket.param[1] = 0;//TS_CLK_NO_INV;
#else
        gsCmdPacket.param[1] = 1;//TS_CLK_INVERSE;
#endif
        status &= INTERN_DVBC_Cmd_Packet_Send(&gsCmdPacket, 2);
    }
    else
    {
        //parallel
        MDrv_WriteByte(0x103308, 0x01);   // parallel mode:0x0001
        MDrv_WriteByte(0x103309, 0x00);   // reg_ckg_dvbtc_ts@0x04

#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7)

        MDrv_WriteByte(0x103300, 0x0b);   // parallel mode: 0x0513 => ts_clk=288/(2*(0x13+1))=7.2MHz
#if(INTERN_DVBC_TS_PARALLEL_INVERSION == 0)
        MDrv_WriteByte(0x103301, 0x06);   // reg_ckg_dvbtmk_ts_out_mode@0x00
#else
        MDrv_WriteByte(0x103301, 0x06);   // reg_ckg_dvbtmk_ts_out_mode@0x00
#endif
#else
        //MDrv_WriteByte(0x103300, 0x11);   // parallel mode: 0x0511 => ts_clk=288/(2*(0x11+1))=8MHz
        MDrv_WriteByte(0x103300, 0x13);   // parallel mode: 0x0513 => ts_clk=288/(2*(0x13+1))=7.2MHz
#if(INTERN_DVBC_TS_PARALLEL_INVERSION == 0)
        MDrv_WriteByte(0x103301, 0x05);   // reg_ckg_dvbtmk_ts_out_mode@0x00
#else
        MDrv_WriteByte(0x103301, 0x07);   // reg_ckg_dvbtmk_ts_out_mode@0x00
#endif

#endif

        //MDrv_WriteByte(0x101EA5, MDrv_ReadByte(0x101EA5)|0x10);   // PAD_TS1 is used as output

#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S8 )
        //// INTERN_DVBC TS Control: Parallel //////////

        status &= INTERN_DVBC_WriteDspReg(0x24, TS_PARALLEL);

    #if(INTERN_DVBT_TS_SERIAL_INVERSION == 0)
        status &= INTERN_DVBC_WriteDspReg(0x26, 0);
#else
        status &= INTERN_DVBC_WriteDspReg(0x26, 1);
#endif
#endif

        //// INTERN_DVBC TS Control: Parallel //////////
        status &= INTERN_DVBC_WriteDspReg(0x24, TS_PARALLEL);

#if(INTERN_DVBT_TS_SERIAL_INVERSION == 0)
        status &= INTERN_DVBC_WriteDspReg(0x26, 0);
#else
        status &= INTERN_DVBC_WriteDspReg(0x26, 1);
#endif
        //// INTERN_DVBC TS Control: Parallel //////////
        gsCmdPacket.cmd_code = CMD_TS_CTRL;

        gsCmdPacket.param[0] = TS_PARALLEL;
#if(INTERN_DVBT_TS_PARALLEL_INVERSION == 0)
        gsCmdPacket.param[1] = 0;//TS_CLK_NO_INV;
#else
        gsCmdPacket.param[1] = 1;//TS_CLK_INVERSE;
#endif
        status &= INTERN_DVBC_Cmd_Packet_Send(&gsCmdPacket, 2);
    }

    DBG_INTERN_DVBC(printf("---> Inversion(Bit5) = 0x%bx \n",gsCmdPacket.param[1] ));

    INTERN_DVBC_Driving_Control(INTERN_DVBT_DTV_DRIVING_LEVEL);

    return status;
}


/************************************************************************************************
  Subject:    channel change config
  Function:   INTERN_DVBC_Config
  Parmeter:   u8QamMode: 0:16, 1:32, 2:64, 3:128, 4:256
  Return:     BOOLEAN :
  Remark:
*************************************************************************************************/
BOOLEAN INTERN_DVBC_Config (U16 u16SymbolRate, U8 u8QamMode, U32 u32IFFreq, BOOLEAN bSpecInv, BOOLEAN bSerialTS, U8 u8AutoSR, U8 u8AutoQAM)
{
    U8              status = TRUE;
    U8              reg_symrate_l;
    U8              reg_symrate_h;
    //U16             u16Fs = 45473; //45470 , mick
    //U16             u16Fc = 0;

    DBG_INTERN_DVBC(printf(" @INTERN_DVBC_config\n"));

    DBG_INTERN_DVBC(printf(" Config : Symbol Rate %d SpecInv %d SerialTS %d \n",u16SymbolRate,bSpecInv,bSerialTS));
    DBG_INTERN_DVBC(printf("u8QamMode = %d\n", (int)u8QamMode));
    DBG_INTERN_DVBC(printf(" u32IFFreq=%ld",u32IFFreq));
    DBG_INTERN_DVBC(printf("AutoSR = %d\n", u8AutoSR));
    DBG_INTERN_DVBC(printf("AutoQAM = %d\n", u8AutoQAM));

    status &= INTERN_DVBC_Reset();

    reg_symrate_l = (U8) (u16SymbolRate & 0xff);
    reg_symrate_h = (U8) (u16SymbolRate >> 8);

//#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S8 )
    status &= INTERN_DVBC_WriteDspReg(0x17, reg_symrate_l);
    status &= INTERN_DVBC_WriteDspReg(0x18, reg_symrate_h);
   	// QAM mode
    status &= INTERN_DVBC_WriteDspReg(0x21, u8QamMode);
    // TS mode
    status &= INTERN_DVBC_WriteDspReg(0x24, bSerialTS? 0x01:0x00);

    // IQ Swap
    status &= INTERN_DVBC_WriteDspReg(0x22, bSpecInv? 0x01:0x00);
//#endif

    // Fc
    status &= INTERN_DVBC_WriteDspReg(0x13, (abs(DVBC_FS-u32IFFreq))&0xff);
    status &= INTERN_DVBC_WriteDspReg(0x14, (abs((DVBC_FS-u32IFFreq))>>8)&0xff);
    // Lif
    status &= INTERN_DVBC_WriteDspReg(0x28, (u32IFFreq < 10000) ? 1 : 0);
    // Fif
    status &= INTERN_DVBC_WriteDspReg(0x29, (u32IFFreq)&0xff);
    status &= INTERN_DVBC_WriteDspReg(0x2a, (u32IFFreq>>8)&0xff);

#if 0
    switch(u32IFFreq)
    {
        case 36125:
        case 36167:
        case 36000:
        case 6000:
        case 4560:
            u16Fc = u16Fs - (U16)u32IFFreq;
            DBG_INTERN_DVBC(printf("Fc freq = %d\n", (int)u16Fc));
            break;
        case 44000:
        default:
            printf("IF frequency not supported\n");
            break;
    }
#endif

    //status &= INTERN_DVBC_Reset();

//// INTERN_DVBC system init: DVB-C //////////
//    gsCmdPacket.cmd_code = CMD_SYSTEM_INIT;

//    gsCmdPacket.param[0] = E_SYS_DVBC;
//    status &= INTERN_DVBC_Cmd_Packet_Send(&gsCmdPacket, 1);

//// DVB-C configurate ///////////////////
    gsCmdPacket.cmd_code = CMD_DVBC_CONFIG;

#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) //T3

    gsCmdPacket.param[p_opmode_rfagc_en]        	= 0;
    gsCmdPacket.param[p_opmode_humdet_en]       	= 0;
    gsCmdPacket.param[p_opmode_dcr_en]          	= 0;
    gsCmdPacket.param[p_opmode_iqb_en]          	= 0;
    gsCmdPacket.param[p_opmode_auto_iq_swap]    	= 1;
    gsCmdPacket.param[p_opmode_auto_fsa_left]   	= 1;
    gsCmdPacket.param[p_opmode_auto_rfmax]      	= 0;
    gsCmdPacket.param[p_opmode_mode_forced]     	= 0;
    gsCmdPacket.param[p_opmode_cp_forced]       	= 0;
    gsCmdPacket.param[pc_config_rssi]           	= 0;
    gsCmdPacket.param[pc_config_zif]            	= 0;
    gsCmdPacket.param[pc_config_fc_l]           	= (U8)(u16Fc & 0xff);
    gsCmdPacket.param[pc_config_fc_h]           	= (U8)(u16Fc >> 8);
    gsCmdPacket.param[pc_config_fs_l]           	= (U8)(u16Fs & 0xff);
    gsCmdPacket.param[pc_config_fs_h]           	= (U8)(u16Fs >> 8);
    gsCmdPacket.param[pc_config_bw]             	= reg_symrate_l; //0xdb;    // Bandwidth-L
    gsCmdPacket.param[pc_config_fsa_left]       	= reg_symrate_h; //0x1A;    // Bandwidth-H
    gsCmdPacket.param[pc_config_rfmax]          	= 1;
    gsCmdPacket.param[pc_config_lp_sel]         	= u8QamMode; 	 // QAM- 0:16, 1:32, 2:64, 3:128, 4:256
    gsCmdPacket.param[pc_config_cp]             	= 3;
    gsCmdPacket.param[pc_config_mode]           	= 1;
    gsCmdPacket.param[pc_config_iq_swap]        	= bSpecInv;
    gsCmdPacket.param[pc_config_atv_system]     	= 1; 			//bPalBG? 0:1;
    gsCmdPacket.param[pc_config_serial_ts]      	= bSerialTS;

#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD ) //T4

    gsCmdPacket.param[p_opmode_rfagc_en]        	= 0;
    gsCmdPacket.param[p_opmode_humdet_en]       	= 0;
    gsCmdPacket.param[p_opmode_dcr_en]          	= 0;
    gsCmdPacket.param[p_opmode_iqb_en]          	= 0;
    gsCmdPacket.param[p_opmode_auto_iq]    			= 1;
    gsCmdPacket.param[p_opmode_auto_rfmax]      	= 0;

    gsCmdPacket.param[p_opmode_auto_aci]     		= 1;
    gsCmdPacket.param[p_opmode_auto_scan]       	= 1;
/*mick
    if(g_enScanType == SCAN_TYPE_MANUAL)
    {
        gsCmdPacket.param[p_opmode_auto_scan_sym_rate] 	= 0;
        gsCmdPacket.param[p_opmode_auto_scan_qam] 		= 0;
    }
    else
    {
        gsCmdPacket.param[p_opmode_auto_scan_sym_rate] 	= 1;
        gsCmdPacket.param[p_opmode_auto_scan_qam] 		= 1;
    }
*/
		u8AutoSRTemp = u8AutoSR;
		u8AutoQAMTemp = u8AutoQAM;

		gsCmdPacket.param[p_opmode_auto_scan_sym_rate] 	= u8AutoSRTemp;
    gsCmdPacket.param[p_opmode_auto_scan_qam] 		= u8AutoQAMTemp;

    gsCmdPacket.param[p_opmode_rsv_0x0A] 			= 0; 	//e_opmode_atv_detector_en

 		// if agc gain
    gsCmdPacket.param[p_opmode_rsv_0x0B] 			= 0x00;	//e_opmode_no_ch_if_agc_l
    gsCmdPacket.param[p_opmode_rsv_0x0C] 			= 0x66; //0x66;	//e_opmode_no_ch_if_agc_h
    // if gac error
    gsCmdPacket.param[p_opmode_rsv_0x0D] 			= 0x00;	//e_opmode_no_ch_err_agc_l
    gsCmdPacket.param[p_opmode_rsv_0x0E] 			= 0x02;	//e_opmode_no_ch_err_agc_h

		// if agc and if agc error's decision threshold
    gsCmdPacket.param[p_opmode_rsv_0x0F] 			= 0x01;

		// DAGC gain threshold about ACI FIR
    gsCmdPacket.param[pc_config_post_dagc_gain_diff_th] = 35; //40;
    gsCmdPacket.param[pc_config_pre_dagc_gain_diff_th] = 30; //35;

		// Config Params
    gsCmdPacket.param[pc_config_rssi]           	= 0;
    gsCmdPacket.param[pc_config_zif]            	= 0;
    gsCmdPacket.param[pc_config_freq] 				= 0;

    gsCmdPacket.param[pc_config_fc_l]           	= (U8)(u16Fc & 0xff); 			//0x5a	,9306
    gsCmdPacket.param[pc_config_fc_h]           	= (U8)(u16Fc >> 8); 			//0x24
    gsCmdPacket.param[pc_config_fs_l]           	= (U8)(u16Fs & 0xff); 			//0xa1	,45473
    gsCmdPacket.param[pc_config_fs_h]           	= (U8)(u16Fs >> 8); 			//0xb1
    gsCmdPacket.param[pc_config_bw_l] 				= reg_symrate_l;				// 0xdb;
    gsCmdPacket.param[pc_config_bw_h] 				= reg_symrate_h;				// 0x1a; //6875=0x1adb

    gsCmdPacket.param[pc_config_bw1_l] 				= 0x58; // 7000
    gsCmdPacket.param[pc_config_bw1_h] 				= 0x1b;
    gsCmdPacket.param[pc_config_bw2_l] 				= 0x70; // 6000
    gsCmdPacket.param[pc_config_bw2_h] 				= 0x17;
    gsCmdPacket.param[pc_config_bw3_l] 				= 0xa0; // 4000
    gsCmdPacket.param[pc_config_bw3_h] 				= 0x0f;

    gsCmdPacket.param[pc_config_rsv_0x1F] 			= 0;
    gsCmdPacket.param[pc_config_rfmax]          	= 0;
    gsCmdPacket.param[pc_config_qam]         		= u8QamMode;  		// QAM- 0:16, 1:32, 2:64, 3:128, 4:256
    gsCmdPacket.param[pc_config_iq_swap]        	= bSpecInv;			// ,0
    gsCmdPacket.param[pc_config_cci] 				= 0;
    gsCmdPacket.param[pc_config_ts_serial] 			= bSerialTS;		// ,0
    gsCmdPacket.param[pc_config_ts_clk_rate] 		= 0;
    gsCmdPacket.param[pc_config_ts_out_inv] 		= 1;
    gsCmdPacket.param[pc_config_ts_data_swap] 		= 0;

#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_A7 ) //A7

    gsCmdPacket.param[p_opmode_rfagc_en]        	= 0;
    gsCmdPacket.param[p_opmode_humdet_en]       	= 0;
    gsCmdPacket.param[p_opmode_dcr_en]          	= 1;
    gsCmdPacket.param[p_opmode_iqb_en]          	= 0;
    gsCmdPacket.param[p_opmode_auto_iq]    			= 1; //0x04
    gsCmdPacket.param[p_opmode_auto_rfmax]      	= 0;

    gsCmdPacket.param[p_opmode_auto_aci]     		= 1;
    gsCmdPacket.param[p_opmode_auto_scan]       	= 1;
/*mick
    if(g_enScanType == SCAN_TYPE_MANUAL)
    {
        gsCmdPacket.param[p_opmode_auto_scan_sym_rate] 	= 0;
        gsCmdPacket.param[p_opmode_auto_scan_qam] 		= 0;
    }
    else
    {
        gsCmdPacket.param[p_opmode_auto_scan_sym_rate] 	= 1;
        gsCmdPacket.param[p_opmode_auto_scan_qam] 		= 1;
    }
*/
		u8AutoSRTemp = u8AutoSR;
		u8AutoQAMTemp = u8AutoQAM;

		gsCmdPacket.param[p_opmode_auto_scan_sym_rate] 	= u8AutoSRTemp;
    gsCmdPacket.param[p_opmode_auto_scan_qam] 		= u8AutoQAMTemp;

    gsCmdPacket.param[p_opmode_rsv_0x0A] 			= 1; 	//e_opmode_atv_detector_en

 		// if agc gain
    gsCmdPacket.param[p_opmode_rsv_0x0B] 			= 0x00;	//e_opmode_no_ch_if_agc_l
    gsCmdPacket.param[p_opmode_rsv_0x0C] 			= 0x00; //0x66;	//e_opmode_no_ch_if_agc_h
    // if gac error
    gsCmdPacket.param[p_opmode_rsv_0x0D] 			= 0x00;	//e_opmode_no_ch_err_agc_l
    gsCmdPacket.param[p_opmode_rsv_0x0E] 			= 0x00;	//e_opmode_no_ch_err_agc_h

		// if agc and if agc error's decision threshold
    gsCmdPacket.param[p_opmode_rsv_0x0F] 			= 0x00;

		// DAGC gain threshold about ACI FIR
   //gsCmdPacket.param[pc_config_post_dagc_gain_diff_th] = 35; //40;
   // gsCmdPacket.param[pc_config_pre_dagc_gain_diff_th] = 30; //35;

		// Config Params
    gsCmdPacket.param[pc_config_rssi]           	= 0;
    gsCmdPacket.param[pc_config_zif]            	= 0;
    gsCmdPacket.param[pc_config_freq] 				= 0;

    gsCmdPacket.param[pc_config_fc_l]           	= 0x38; //0x38; //0x20; //0x47; //(U8)(u16Fc & 0xff); 			//0x5a	,9306
    gsCmdPacket.param[pc_config_fc_h]           	= 0x4A; //0x4a; //0x4e; //0x8d; //(U8)(u16Fc >> 8); 			//0x24
    gsCmdPacket.param[pc_config_fs_l]           	= 0xc0; //(U8)(u16Fs & 0xff); 			//0xa1	,45473
    gsCmdPacket.param[pc_config_fs_h]           	= 0x5d; //(U8)(u16Fs >> 8); 			//0xb1
    gsCmdPacket.param[pc_config_bw_l] 				= reg_symrate_l;				// 0xdb;
    gsCmdPacket.param[pc_config_bw_h] 				= reg_symrate_h;				// 0x1a; //6875=0x1adb

    gsCmdPacket.param[pc_config_bw1_l] 				= 0xf4; //0x58; // 7000
    gsCmdPacket.param[pc_config_bw1_h] 				= 0x1a; //0x1b;
    gsCmdPacket.param[pc_config_bw2_l] 				= 0x20; //0x50; //0x70; // 6000
    gsCmdPacket.param[pc_config_bw2_h] 				= 0x1c; //0x14;
    gsCmdPacket.param[pc_config_bw3_l] 				= 0xa0; //0x68; //0xa0; // 4000
    gsCmdPacket.param[pc_config_bw3_h] 				= 0x0f; //0x10; //;

    gsCmdPacket.param[pc_config_rsv_0x1F] 			= 0;
    gsCmdPacket.param[pc_config_rfmax]          	= 0;
    gsCmdPacket.param[pc_config_qam]         		= u8QamMode;  		// QAM- 0:16, 1:32, 2:64, 3:128, 4:256
    gsCmdPacket.param[pc_config_iq_swap]        	= bSpecInv;			// ,0  //0x22
    gsCmdPacket.param[pc_config_cci] 				= 0;
    gsCmdPacket.param[pc_config_ts_serial] 			= bSerialTS;		// ,0
    gsCmdPacket.param[pc_config_ts_clk_rate] 		= 0;
    gsCmdPacket.param[pc_config_ts_out_inv] 		= 0; // 1;
    gsCmdPacket.param[pc_config_ts_data_swap] 		= 0;
    gsCmdPacket.param[pc_config_lif] 		= 1;   //0x28
    gsCmdPacket.param[pc_config_Fif_L] 		= 0x88; //0x88; //0xa0; //0x29
    gsCmdPacket.param[pc_config_Fif_H] 		= 0x13; //0x13; //0x0f;	 //0x2a
#endif
//------------------------------------------------------------
#if 0
    if (bSerialTS)
    {
#if(INTERN_DVBC_TS_SERIAL_INVERSION == 0)
        gsCmdPacket.param[pc_config_ts_out_inv] = false;
#else
        gsCmdPacket.param[pc_config_ts_out_inv] = true;
#endif
    }
    else
    {
#if(INTERN_DVBC_TS_PARALLEL_INVERSION == 0)
        gsCmdPacket.param[pc_config_ts_out_inv] = false;
#else
        gsCmdPacket.param[pc_config_ts_out_inv] = true;
#endif
    }
    gsCmdPacket.param[pc_config_ts_data_swap]   = FALSE;

    status &= INTERN_DVBC_Cmd_Packet_Send(&gsCmdPacket, DVBC_PARAM_LEN);
#endif

    if(bSerialTS)
    {
        // serial
        MDrv_WriteByte(0x103308, 0x01);   // parallel mode:0x0001 / serial mode: 0x0401
        MDrv_WriteByte(0x103309, 0x04);   // reg_ckg_dvbtc_ts@0x04

        MDrv_WriteByte(0x103300, 0x00);   // parallel mode: 0x0511 /serial mode 0x0400
    #if(INTERN_DVBC_TS_SERIAL_INVERSION == 0)
        MDrv_WriteByte(0x103301, 0x04);   // reg_ckg_dvbtmk_ts_out_mode@0x00
    #else
        MDrv_WriteByte(0x103301, 0x06);   // reg_ckg_dvbtmk_ts_out_mode@0x00
    #endif
    }
    else
    {
        //parallel
        MDrv_WriteByte(0x103308, 0x01);   // parallel mode:0x0001 / serial mode: 0x0401
        MDrv_WriteByte(0x103309, 0x00);   // reg_ckg_dvbtc_ts@0x04

        MDrv_WriteByte(0x103300, 0x11);   // parallel mode: 0x0511 => ts_clk=288/(2*(0x11+1))=8MHz
        //MDrv_WriteByte(0x103300, 0x13);   // parallel mode: 0x0513 => ts_clk=288/(2*(0x13+1))=7.2MHz
    #if(INTERN_DVBC_TS_PARALLEL_INVERSION == 0)
        MDrv_WriteByte(0x103301, 0x05);   // reg_ckg_dvbtmk_ts_out_mode@0x00
    #else
        MDrv_WriteByte(0x103301, 0x06);   // reg_ckg_dvbtmk_ts_out_mode@0x00
    #endif
    }

    DBG_INTERN_DVBC(printf("u8QamMode = %d\n", (int)u8QamMode));
    DBG_INTERN_DVBC(printf("Symbol rate = %d\n", u16SymbolRate));
    DBG_INTERN_DVBC(printf("AutoSR = %d\n", u8AutoSRTemp));
    DBG_INTERN_DVBC(printf("AutoQAM = %d\n", u8AutoQAMTemp));

    return status;
}
/************************************************************************************************
  Subject:    enable hw to lock channel
  Function:   INTERN_DVBC_Active
  Parmeter:   bEnable
  Return:     BOOLEAN
  Remark:
*************************************************************************************************/
BOOLEAN INTERN_DVBC_Active(BOOLEAN bEnable)
{
    U8            status = true;

    DBG_INTERN_DVBC(printf(" @INTERN_DVBC_active\n"));

    //// INTERN_DVBC Finite State Machine on/off //////////
#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7)
    UNUSED(bEnable);
    MDrv_WriteByte(0x112600 + (0x0e)*2, 0x01);   // FSM_EN
#else
    gsCmdPacket.cmd_code = CMD_FSM_CTRL;

    gsCmdPacket.param[0] = (U8)bEnable;
    status &= INTERN_DVBC_Cmd_Packet_Send(&gsCmdPacket, 1);
#endif
    return status;
}

/****************************************************************************
  Subject:    To get the IF AGC Gain and Error
  Function:   INTERN_DVBC_GetAgcInfomation
  Parmeter:   agcGain : if agc gain
 						  agcError : if agc error
  Return:     E_RESULT_SUCCESS
              E_RESULT_FAILURE =>Read I2C fail, INTERN_DVBC_VIT_STATUS_NG
  Remark:     No Channel Detection usage
*****************************************************************************/
BOOLEAN INTERN_DVBC_GetAgcInfomation(U16 *agcGain, U16 *agcError)
{
	 U8            	status = true;
   U8            	reg;
	 U16						if_agc_gain, if_agc_error;

	 // IFAGC gain
	 // Debug selection
   status &= INTERN_DVBC_ReadReg(0x2122, &reg);
   status &= INTERN_DVBC_WriteReg(0x2122, (reg&0xF0)|0x03);
   // Freeze
   status &= INTERN_DVBC_ReadReg(0x2105, &reg);
   status &= INTERN_DVBC_WriteReg(0x2105, reg|0x80);
//	 INTERN_DVBC_Delayms(1);

	 // Read If Agc Gain
   status &= INTERN_DVBC_ReadReg(0x2125, &reg);
   if_agc_gain = reg;
   status &= INTERN_DVBC_ReadReg(0x2124, &reg);
   if_agc_gain = (if_agc_gain << 8) | reg;
 	 *agcGain = if_agc_gain;

   // Unfreeze
   status &= INTERN_DVBC_ReadReg(0x2105, &reg);
   status &= INTERN_DVBC_WriteReg(0x2105, reg&(~0x80));

	 // IFAGC error
	 // Debug selection
   status &= INTERN_DVBC_ReadReg(0x2122, &reg);
   status &= INTERN_DVBC_WriteReg(0x2122, (reg&0xF0)|0x00);

   // Freeze
   status &= INTERN_DVBC_ReadReg(0x2105, &reg);
   status &= INTERN_DVBC_WriteReg(0x2105, reg|0x80);
//	 INTERN_DVBC_Delayms(1);

	 // Read If Agc Error
   status &= INTERN_DVBC_ReadReg(0x2125, &reg);
   if_agc_error = reg;
   status &= INTERN_DVBC_ReadReg(0x2124, &reg);
   if_agc_error = ((if_agc_error&0x03) << 8) | reg;

	 if (if_agc_error > 0x200)
	 {
	 	 if_agc_error = 0x400 - if_agc_error;
	 }
   *agcError = if_agc_error;
   // Unfreeze
   status &= INTERN_DVBC_ReadReg(0x2105, &reg);
   status &= INTERN_DVBC_WriteReg(0x2105, reg&(~0x80));

   return status;
}


/************************************************************************************************
  Subject:    Return lock status
  Function:   INTERN_DVBC_Lock
  Parmeter:   eStatus :
  Return:     BOOLEAN
  Remark:
*************************************************************************************************/
BOOLEAN INTERN_DVBC_Lock( QAM_LOCK_STATUS eStatus )
{
    U16 u16Address;
    BYTE cData;
    BYTE cBitMask;

    //U8 u8Data;
    //static U32      u32FecLockTime;


#if 0
	U8 tmpData, tmpData1;
	U16 agcGain, agcError;
#endif

    switch( eStatus )
    {
    case QAM_FEC_LOCK:
#if 1
        INTERN_DVBC_ReadReg(0x23E0, &cData);
        //printf("---------------------------------------> cData = 0x%bx \n", cData);

#if 0
        INTERN_DVBC_ReadReg(0x2075, &tmpData);
        INTERN_DVBC_ReadReg(0x2076, &tmpData1);
        printf("FW Code's Version = 0x%x%x \n", tmpData, tmpData1);

		INTERN_DVBC_GetAgcInfomation(&agcGain, &agcError);
        printf("[Debug]AGC GAIN = 0x%x, 0x%x \n", (agcGain>>8)&0xFF, agcGain&0xFF);
        printf("[Debug]AGC Err = 0x%x, 0x%x \n", (agcError>>8)&0xFF, agcError&0xFF);
#endif

        if (cData == 0x0C)
        {
            FECUnlockCnt = 64;
            return TRUE;
        }
        else if (FECUnlockCnt)
        {
            FECUnlockCnt--;
            return TRUE;
        }
        else
        {
            return FALSE;
        }

      break;
#else
        INTERN_DVBC_ReadReg(0x23E0, &cData);
        if (cData == 0x0B)
        {
            u32FecLockTime = MsOS_GetSystemTime();
            FECLock = TRUE;
            //printf("dmd_lock\n");

            return TRUE;
        }
        else
        {
            if (FECLock == TRUE)
            {
                if ( ( MsOS_GetSystemTime() - u32FecLockTime ) < 3000 )
                    return TRUE;
            }
            FECLock = FALSE;
            //printf("dmd_unlock\n");
            return FALSE;      // continuously un-lock
        }
        break;
#endif

    case QAM_PSYNC_LOCK:
        u16Address =  0x232C; //FEC: P-sync Lock,
        cBitMask = BIT1;
        break;

    case QAM_NO_CHANNEL: //QAM_TPS_LOCK:
        u16Address =  0x20c3; //0x2222; //TPS Lock,
        cBitMask = BIT2|BIT3|BIT4;//BIT1;
        break;

    case QAM_DCR_LOCK:
        u16Address =  0x2145; //DCR Lock,
        cBitMask = BIT0;
        break;

    case QAM_AGC_LOCK:
        u16Address =  0x212F; //AGC Lock,
        cBitMask = BIT0;
        break;

    case QAM_ATV_DETECT: //QAM_MODE_DET:
        u16Address =  0x20c4; //0x24CF; //Mode CP Detect,
        cBitMask = BIT1|BIT2; //BIT4;
        break;

    case QAM_TR_LOCK:
        u16Address =  0x2750; //0x24CF; //Mode CP Detect,
        cBitMask = BIT0; //BIT4;
        break;


    default:
        return FALSE;
    }

    if (INTERN_DVBC_ReadReg(u16Address, &cData) == FALSE)
        return FALSE;

    if ((cData & cBitMask) == cBitMask)
    {
        return TRUE;
    }


    return FALSE;

}

/****************************************************************************
  Subject:    To get the Post viterbi BER
  Function:   INTERN_DVBC_GetPostViterbiBer
  Parmeter:  Quility
  Return:       E_RESULT_SUCCESS
                   E_RESULT_FAILURE =>Read I2C fail, INTERN_DVBC_VIT_STATUS_NG
  Remark:     For the Performance issue, here we just return the Post Value.(Not BER)
                   We will not read the Period, and have the "/256/8"
*****************************************************************************/
BOOLEAN INTERN_DVBC_GetPostViterbiBer(float *ber)
{
    U8            	status = true;
    U8            	reg, reg_frz;
    U16				BitErrPeriod;
    U32           	BitErr;
    U16            	PktErr;

    /////////// Post-Viterbi BER /////////////

    // bank 7 0x32 [7] reg_bit_err_num_freeze
    status &= INTERN_DVBC_ReadReg(0x2332, &reg_frz);
    status &= INTERN_DVBC_WriteReg(0x2332, reg_frz|0x80);

    // bank 7 0x30 [7:0] reg_bit_err_sblprd_7_0
    //               [15:8] reg_bit_err_sblprd_15_8
    status &= INTERN_DVBC_ReadReg(0x2331, &reg);
    BitErrPeriod = reg;

    status &= INTERN_DVBC_ReadReg(0x2330, &reg);
    BitErrPeriod = (BitErrPeriod << 8)|reg;

    // bank 7 0x3a [7:0] reg_bit_err_num_7_0
    //               [15:8] reg_bit_err_num_15_8
    // bank 7 0x3c [7:0] reg_bit_err_num_23_16
    //               [15:8] reg_bit_err_num_31_24

    status &= INTERN_DVBC_ReadReg(0x233D, &reg);
    BitErr = reg;

    status &= INTERN_DVBC_ReadReg(0x233C, &reg);
    BitErr = (BitErr << 8)|reg;

    status &= INTERN_DVBC_ReadReg(0x233B, &reg);
    BitErr = (BitErr << 8)|reg;

    status &= INTERN_DVBC_ReadReg(0x233A, &reg);
    BitErr = (BitErr << 8)|reg;

    // bank 7 0x3e [7:0] reg_uncrt_pkt_num_7_0
    //               [15:8] reg_uncrt_pkt_num_15_8
    status &= INTERN_DVBC_ReadReg(0x233F, &reg);
    PktErr = reg;

    status &= INTERN_DVBC_ReadReg(0x233E, &reg);
    PktErr = (PktErr << 8)|reg;

    // bank 7 0x32 [7] reg_bit_err_num_freeze
    status &= INTERN_DVBC_WriteReg(0x2332, reg_frz);

    if (BitErrPeriod == 0 )    //protect 0
        BitErrPeriod = 1;

    if (BitErr <=0 )
        *ber = 0.5 / ((float)BitErrPeriod*128*188*8);
    else
        *ber = (float)BitErr / ((float)BitErrPeriod*128*188*8);


   DBG_GET_SIGNAL(printf("INTERN_DVBC PostVitBER = %8.3e \n ", *ber));
   DBG_GET_SIGNAL(printf("INTERN_DVBC PktErr = %d \n ", (int)PktErr));


    return status;
}

/****************************************************************************
  Subject:    Function providing approx. result of Log10(X)
  Function:   Log10Approx
  Parmeter:   Operand X in float
  Return:     Approx. value of Log10(X) in float
  Remark:      Ouput range from 0.0, 0.3 to 9.6 (input 1 to 2^32)
*****************************************************************************/
static float Log10Approx(float flt_x)
{
    U32       u32_temp = 1;
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
  Function:   INTERN_DVBC_GetSNR
  Parmeter:   None
  Return:     -1 mean I2C fail, otherwise I2C success then return SNR value
  Remark:
*****************************************************************************/
float INTERN_DVBC_GetSNR (void)
{
    U8            status = true;
    U8            reg, reg_frz;
    U32           noise_power;
    float         snr;

    // bank 6 0xfe [0] reg_fdp_freeze
    status &= INTERN_DVBC_ReadReg(0x22fe, &reg_frz);
    status &= INTERN_DVBC_WriteReg(0x22fe, reg_frz|0x01);

    // bank 6 0xff [0] reg_fdp_load
    status &= INTERN_DVBC_ReadReg(0x22ff, &reg);

    // bank 6 0x4a [26:0] reg_snr_accu <27,1>
    status &= INTERN_DVBC_ReadReg(0x224d, &reg);
    noise_power = reg & 0x07;

    status &= INTERN_DVBC_ReadReg(0x224c, &reg);
    noise_power = (noise_power << 8)|reg;

    status &= INTERN_DVBC_ReadReg(0x224b, &reg);
    noise_power = (noise_power << 8)|reg;

    status &= INTERN_DVBC_ReadReg(0x224a, &reg);
    noise_power = (noise_power << 8)|reg;

    noise_power = noise_power/2;

    // bank 6 0x26 [5:4] reg_transmission_mode
    status &= INTERN_DVBC_ReadReg(0x2226, &reg);

    // bank 6 0xfe [0] reg_fdp_freeze
    status &= INTERN_DVBC_WriteReg(0x22fe, reg_frz);

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

/*
FUNCTION_RESULT INTERN_DVBC_GetSignalStrength(WORD *strength)
{
    *strength = 80;
    return E_RESULT_SUCCESS;
}
*/

FUNCTION_RESULT INTERN_DVBC_GetSignalStrength(U16 *strength)
{
    U8                status = true;
    U8                reg_tmp, rf_agc_val,if_agc_val,i;//reg_tmp2, reg_frz,rf_agc_val,if_agc_val,i;
    U8                ssi_tbl_len;	//, err_tbl_len;
//	  U16               if_agc_err, tps_info;
    float             ch_power_db;
    float			        ch_power_rf=0;
    float			        ch_power_if=0;
//    float			        ch_power_ref=0;
//    float             ch_power_rel;
    S_INTERN_DVBC_IFAGC_SSI        *ifagc_ssi;
//    S_INTERN_DVBT_IFAGC_ERR        *ifagc_err;

    // if (INTERN_DVBT_Lock(COFDM_TPS_LOCK))
		//if (INTERN_DVBT_Lock(COFDM_AGC_LOCK))
		/* Actually, it's more reasonable, that signal level depended on cable input power level
		 * thougth the signal isn't dvb-c signal.
		 */
    {
#if 0
        status &= INTERN_DVBC_ReadReg(TDP_REG_BASE + 0x13, &reg_tmp);

        DBG_GET_SIGNAL(printf("AGC_REF = %d\n", (U16)reg_tmp));

        if (reg_tmp > 200)
        {
            ifagc_ssi = MSTAR_IfagcSsi_HiRef_INTERN_DVBC;
            ssi_tbl_len = sizeof(MSTAR_IfagcSsi_HiRef_INTERN_DVBC)/sizeof(S_INTERN_DVBC_IFAGC_SSI);
#if 0
            ifagc_err = MSTAR_IfagcErr_HiRef_INTERN_DVBT;
            err_tbl_len = sizeof(MSTAR_IfagcErr_HiRef_INTERN_DVBT)/sizeof(S_INTERN_DVBT_IFAGC_ERR);
#endif
        }
        else
        {
            ifagc_ssi = MSTAR_IfagcSsi_LoRef_INTERN_DVBC;
            ssi_tbl_len = sizeof(MSTAR_IfagcSsi_LoRef_INTERN_DVBC)/sizeof(S_INTERN_DVBC_IFAGC_SSI);
#if 0
            ifagc_err = MSTAR_IfagcErr_LoRef_INTERN_DVBT;
            err_tbl_len = sizeof(MSTAR_IfagcErr_LoRef_INTERN_DVBT)/sizeof(S_INTERN_DVBT_IFAGC_ERR);
#endif
        }
#endif

        ifagc_ssi = MSTAR_IfagcSsi_INTERN_DVBC;
        ssi_tbl_len = sizeof(MSTAR_IfagcSsi_INTERN_DVBC)/sizeof(S_INTERN_DVBC_IFAGC_SSI);

        ///////// RF/IF-AGC Gain Out /////////////
#if (INTERN_DVBC_USE_SAR_3_ENABLE == 1)
				// msKeypad_Get_ADC_Channel(KEYPAD_ADC_CHANNEL_4, &rf_agc_val);
				msKeypad_Get_ADC_Channel(3, &rf_agc_val);
				// printf(">>SAR_4, 0x%x\n",rf_agc_val);
#else
        rf_agc_val = 0x1D; // max value
#endif
        // select IF output value to read. assign 0x03 0x22,
        status &= INTERN_DVBC_ReadReg(TDP_REG_BASE + 0x22, &reg_tmp);
        status &= INTERN_DVBC_WriteReg(TDP_REG_BASE + 0x22, (reg_tmp&0xf0)|0x03);
        // use only high byte value

        status &= INTERN_DVBC_ReadReg(TDP_REG_BASE + 0x25, &reg_tmp);
        if_agc_val = reg_tmp;

        DBG_GET_SIGNAL(printf("SSI_RFAGC (SAR-4) = 0x%x\n", rf_agc_val));
        DBG_GET_SIGNAL(printf("SSI_IFAGC_H = 0x%x\n", if_agc_val));


        for(i = 0; i < sizeof(MSTAR_RfagcSsi_INTERN_DVBC)/sizeof(S_INTERN_DVBC_RFAGC_SSI); i++)
        {
            if (rf_agc_val <= MSTAR_RfagcSsi_INTERN_DVBC[i].sar3_val)
            {
                ch_power_rf = MSTAR_RfagcSsi_INTERN_DVBC[i].power_db;
                break;
            }
        }

        for(i = 0; i < ssi_tbl_len; i++)
        {
            if (if_agc_val <= ifagc_ssi[i].agc_val)
            {
                ch_power_if = ifagc_ssi[i].power_db;
                break;
            }
        }

        DBG_GET_SIGNAL(printf("ch_power_rf = %d\n", (S16)ch_power_rf*100));
        DBG_GET_SIGNAL(printf("ch_power_if = %d\n", (S16)ch_power_if*100));

        // ch_power_db = (ch_power_rf > ch_power_if)? ch_power_rf : ch_power_if;

				if(ch_power_rf > (TAKEOVERPOINT + TAKEOVERRANGE))
				{
					ch_power_db = ch_power_rf;
				}
				else if(ch_power_if < (TAKEOVERPOINT - TAKEOVERRANGE))
				{
					ch_power_db = ch_power_if;
				}
				else
				{
					ch_power_db = (ch_power_if + ch_power_rf)/2;
				}

				// ch_power_db = (ch_power_rf > ch_power_if)? ch_power_if : ch_power_rf;

#if 0
        ///////// IF-AGC Error for Add. Attnuation /////////////
				if(if_agc_val == 0xff)
				{

        	status &= INTERN_DVBT_ReadReg(TDP_REG_BASE + 0x22, &reg_tmp);
        	status &= INTERN_DVBT_WriteReg(TDP_REG_BASE + 0x22, (reg_tmp&0xf0));

					// bank 5 0x04 [15] reg_tdp_lat
					status &= INTERN_DVBT_ReadReg(TDP_REG_BASE + 0x05, &reg_frz);
					status &= INTERN_DVBT_WriteReg(TDP_REG_BASE + 0x05, reg_frz|0x80);

					// bank 5 0x2c [9:0] reg_agc_error
					status &= INTERN_DVBT_ReadReg(TDP_REG_BASE + 0x25, &reg_tmp);
					// if_agc_err = reg_tmp & 0x03;
					status &= INTERN_DVBT_ReadReg(TDP_REG_BASE + 0x24, &reg_tmp2);
					// if_agc_err = (if_agc_err << 6)|(reg_tmp >> 2);


					if(reg_tmp&0x2)
					{
						if_agc_err = ((((~reg_tmp)&0x03)<<8)|((~reg_tmp2)&0xff)) + 1;
					}
					else
					{
						if_agc_err = reg_tmp<<8|reg_tmp2;
					}

					// release latch
					status &= INTERN_DVBT_WriteReg(TDP_REG_BASE + 0x05, reg_frz);

					for(i = 0; i < err_tbl_len; i++)
					{
							if ( if_agc_err <= ifagc_err[i].agc_err )        // signed char comparison
							{
									ch_power_db += ifagc_err[i].attn_db;
									break;
							}
					}
					DBG_GET_SIGNAL(printf("if_agc_err = 0x%x\n", if_agc_err));
				}
#endif

				ch_power_db += SIGNAL_LEVEL_OFFSET;
    }

		DBG_GET_SIGNAL(printf(">>> SSI_CH_PWR(dB) beginning = %d\n", (S16)(ch_power_db*100)));
/*
			if(ch_power_db < -87)
		{
			*strength = 0;
		}
		else if(ch_power_db > -37)
		{
			*strength = 100;
		}
		else
		{
			*strength = (ch_power_db + 87) * 2;
		}
*/
  	if(ch_power_db <= -90.0)
  	{*strength = 0;}
    else if(ch_power_db <= -85.0)
    {*strength = 10;}
    else if (ch_power_db <= -80.0)
    {*strength = 10 + (ch_power_db+85.0)*20.0/5;}
    else if (ch_power_db <= -75.0)
    {*strength = 30 + (ch_power_db+80.0)*30.0/5;}
    else if (ch_power_db <= -70.0)
    {*strength = 60 + (ch_power_db+75.0)*10.0/5;}
    else if (ch_power_db <= -60.0)
    {*strength = 70 + (ch_power_db+70.0)*20.0/10;}
    else if (ch_power_db <= -50.0)
    {*strength = 90 + (ch_power_db+60.0)*10.0/10;}
    else
    {*strength = 100;}

		DBG_GET_SIGNAL(printf(">>> SSI_CH_PWR(dB) = %d , Score = %d<<<\n", (S16)(ch_power_db*100), *strength));
    return E_RESULT_SUCCESS;
}

/****************************************************************************
  Subject:    To get the DVT Signal quility
  Function:   INTERN_DVBC_GetSignalQuality
  Parmeter:  Quility
  Return:      E_RESULT_SUCCESS
                   E_RESULT_FAILURE
  Remark:    Here we have 4 level range
                  <1>.First Range => Quility =100  (You can define it by INTERN_DVBC_SIGNAL_BASE_100)
                  <2>.2th Range => 60 < Quality < 100 (You can define it by INTERN_DVBC_SIGNAL_BASE_60)
                  <3>.3th Range => 10 < Quality < 60  (You can define it by INTERN_DVBC_SIGNAL_BASE_10)
                  <4>.4th Range => Quality <10
*****************************************************************************/
FUNCTION_RESULT INTERN_DVBC_GetSignalQuality(WORD *quality)
{
    float         fber;
    float         log_ber;

    if (TRUE == INTERN_DVBC_Lock(QAM_FEC_LOCK) )
    {
        if (INTERN_DVBC_GetPostViterbiBer(&fber) == FALSE)
        {
            DBG_INTERN_DVBC(printf("GetPostViterbiBer Fail!\n"));
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
  Subject:    To get the DVBC Carrier Freq Offset
  Function:   INTERN_DVBC_Get_FreqOffset
  Parmeter:   Frequency offset (in KHz), bandwidth
  Return:     E_RESULT_SUCCESS
              E_RESULT_FAILURE
  Remark:
*****************************************************************************/
FUNCTION_RESULT INTERN_DVBC_Get_FreqOffset(float *pFreqOff, U8 u8BW)
{
    float         N, FreqB;
    float         FreqCfoTd, FreqCfoFd, FreqIcfo;
    U32           RegCfoTd, RegCfoFd, RegIcfo;
    U8            reg_frz, reg;
    U8            status;

    FreqB = (float)u8BW * 8 / 7;

    status = INTERN_DVBC_ReadReg(0x2104+1, &reg_frz);

    status &= INTERN_DVBC_WriteReg(0x2104+1, reg_frz|0x80);

    status &= INTERN_DVBC_ReadReg(0x24c6+2, &reg);
    RegCfoTd = reg;

    status &= INTERN_DVBC_ReadReg(0x24c6+1, &reg);
    RegCfoTd = (RegCfoTd << 8)|reg;

    status &= INTERN_DVBC_ReadReg(0x24c6, &reg);
    RegCfoTd = (RegCfoTd << 8)|reg;

    FreqCfoTd = (float)RegCfoTd;

    if (RegCfoTd & 0x800000)
        FreqCfoTd = FreqCfoTd - (float)0x1000000;

    FreqCfoTd = FreqCfoTd * FreqB * 0.00011642;

    status &= INTERN_DVBC_WriteReg(0x2104+1, reg_frz&(~0x80));

    status &= INTERN_DVBC_ReadReg(0x22fe, &reg_frz);
    status &= INTERN_DVBC_WriteReg(0x22fe, reg_frz|0x01);

    //status &= INTERN_DVBC_WriteReg(0x22fe+1, 0x01);
    status &= INTERN_DVBC_WriteReg(0x22ff, 0x01);

    status &= INTERN_DVBC_ReadReg(0x2230+3, &reg);
    RegCfoFd = reg;

    status &= INTERN_DVBC_ReadReg(0x2230+2, &reg);
    RegCfoFd = (RegCfoFd << 8)|reg;

    status &= INTERN_DVBC_ReadReg(0x2230+1, &reg);
    RegCfoFd = (RegCfoFd << 8)|reg;

    FreqCfoFd = (float)RegCfoFd;

    if (RegCfoFd & 0x800000)
        FreqCfoFd = FreqCfoFd - (float)0x1000000;

    FreqCfoFd = FreqCfoFd * FreqB * 0.00011642;

    status &= INTERN_DVBC_ReadReg(0x2218+1, &reg);
    RegIcfo = reg & 0x07;

    status &= INTERN_DVBC_ReadReg(0x2218, &reg);
    RegIcfo = (RegIcfo << 8)|reg;

    FreqIcfo = (float)RegIcfo;

    if (RegIcfo & 0x400)
        FreqIcfo = FreqIcfo - (float)0x800;

    status &= INTERN_DVBC_ReadReg(0x2226, &reg);
    reg = reg & 0x30;

    switch (reg)
    {
        case 0x00:  N = 2048;  break;
        case 0x20:  N = 4096;  break;
        case 0x10:
        default:    N = 8192;  break;
    }

    FreqIcfo = FreqIcfo * FreqB / N * 1000;         //unit: kHz
    status &= INTERN_DVBC_WriteReg(0x22fe, reg_frz&(~0x01));
    //status &= INTERN_DVBC_WriteReg(0x22fe+1, 0x01);
    status &= INTERN_DVBC_WriteReg(0x22ff, 0x01);
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


void INTERN_DVBC_Power_ON_OFF(U8 bPowerOn)
{

    bPowerOn = bPowerOn;
}

BOOLEAN INTERN_DVBC_Power_Save(void)
{

    return TRUE;
}

/************************************************************************************************
  Subject:    TS1 output control
  Function:   INTERN_DVBC_PAD_TS1_Enable
  Parmeter:   flag : TRUE For Turn on TS1, FALSE For Turn off TS1
  Return:     void
  Remark:
*************************************************************************************************/
void INTERN_DVBC_PAD_TS1_Enable(BOOLEAN flag)
{
	DBG_INTERN_DVBC(printf(" @INTERN_DVBT_TS1_Enable... \n"));
	if(flag) // PAD_TS1 Enable TS CLK PAD
	{
		#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) //T3
    	MDrv_WriteByte(0x101EA5, MDrv_ReadByte(0x101EA5)|0x10);   //For T3
    	#elif (( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD ) || \
               (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7L)) //T4
    	MDrv_WriteByte(0x101EAF, MDrv_ReadByte(0x101EAF)|0x18);   //For T4
       	#elif (CHIP_FAMILY_TYPE == CHIP_FAMILY_S8)
    	INTERN_DVBC_Write_VD_DMD_Byte(0x101EAF, INTERN_DVBC_Read_MBX_Byte(0x101EAF)|0x11);   //For T8
    	#elif (CHIP_FAMILY_TYPE == CHIP_FAMILY_A1) || \
              (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7)
        INTERN_DVBC_Write_VD_DMD_Byte(0x101EA3, ((INTERN_DVBC_Read_MBX_Byte(0x101EA3) & 0xC3) | 0x14));
    	#endif

  	}
  	else // PAD_TS1 Disable TS CLK PAD
  	{
  		#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) //T3
		MDrv_WriteByte(0x101EA5, MDrv_ReadByte(0x101EA5)&0xEF);   //For T3
		#elif (( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD ) || \
               (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7L)) //T4
    	MDrv_WriteByte(0x101EAF, MDrv_ReadByte(0x101EAF)&0xE3);   //For T4
    	#elif (CHIP_FAMILY_TYPE == CHIP_FAMILY_S8)
    	INTERN_DVBC_Write_VD_DMD_Byte(0x101EAF, INTERN_DVBC_Read_MBX_Byte(0x101EAF)&0xC0);   //For T8
    	#elif (CHIP_FAMILY_TYPE == CHIP_FAMILY_A1) || \
              (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7)
        INTERN_DVBC_Write_VD_DMD_Byte(0x101EA3, (INTERN_DVBC_Read_MBX_Byte(0x101EA3) & 0xC3));
    	#endif
  	}
}

/****************************************************************************
  Subject:    To get the DVBC constellation parameter
  Function:   INTERN_DVBC_Get_TPS_Parameter_Const
  Parmeter:   point to return parameter(0: QPSK, 1:16QAM, 2:64QAM)
  Return:     TRUE
              FALSE
  Remark:      The TPS parameters will be available after TPS lock
*****************************************************************************/
BOOLEAN INTERN_DVBC_Get_TPS_Parameter_Const( WORD * TPS_parameter)
{
    U8 tps_param;

    if ( INTERN_DVBC_ReadReg(0x2224, &tps_param) == FALSE )
        return FALSE;

    *TPS_parameter = tps_param & (BIT0|BIT1) ;
    return TRUE;
}



/****************************************************************************
  Subject:    To get the current symbol rate at the DVB-C Demod
  Function:   INTERN_DVBC_GetCurrentSymbolRate
  Parmeter:   pointer pData for return Symbolrate

  Return:     TRUE
              FALSE
  Remark:
*****************************************************************************/
BOOLEAN INTERN_DVBC_GetCurrentSymbolRate(U16 *pData)
{
	U8  u8Data;
    U32 u32Data;
    float floData;

    INTERN_DVBC_ReadReg(TDP_REG_BASE + 0x50, &u8Data);
    u32Data = u8Data;
    INTERN_DVBC_ReadReg(TDP_REG_BASE + 0x51, &u8Data);
    u32Data = u32Data|(((U32)u8Data)<<8);
    INTERN_DVBC_ReadReg(TDP_REG_BASE + 0x52, &u8Data);
    u32Data = u32Data|(((U32)u8Data)<<16);
    INTERN_DVBC_ReadReg(TDP_REG_BASE + 0x53, &u8Data);
    u32Data = u32Data|(((U32)u8Data)<<24);

    floData = (float)u32Data / 1024.0;          //don't change
    floData = (floData*45473.0)/131072.0;   	//don't change
	u32Data = (floData + 0.5);					//don't change

    *pData = u32Data;
	 return TRUE;
}
#if 0
/****************************************************************************
  Subject:    To get the current modulation type at the DVB-C Demod
  Function:   INTERN_DVBC_GetCurrentModulationType
  Parmeter:   pointer for return QAM type

  Return:     TRUE
              FALSE
  Remark:
*****************************************************************************/
BOOLEAN INTERN_DVBC_GetCurrentModulationType(QAM_MODE_TYPE *pQAMMode)
{
    U8 u8Data;
    INTERN_DVBC_ReadReg(FDP_REG_BASE + 0x02, &u8Data);

    switch(u8Data%5)
    {
	  	case 4:
	        *pQAMMode = QAM_MODE_16QAM;
	        return TRUE;
	        break;
	  	case 0:
	        *pQAMMode = QAM_MODE_32QAM;
	        return TRUE;
	        break;
	  	case 1:
	        *pQAMMode = QAM_MODE_64QAM;
	        return TRUE;
	        break;
	  	case 2:
	        *pQAMMode = QAM_MODE_128QAM;
	        return TRUE;
	        break;
	  	case 3:
	        *pQAMMode = QAM_MODE_256QAM;
	        return TRUE;
	        break;
	    default:
	        *pQAMMode = QAM_MODE_INVALID;
	        return FALSE;
    }
}
#endif
/***********************************************************************************
  Subject:    read register
  Function:   MDrv_1210_IIC_Bypass_Mode
  Parmeter:
  Return:
  Remark:
************************************************************************************/
//void MDrv_1210_IIC_Bypass_Mode(BOOLEAN enable)
//{
//    UNUSED(enable);
//    if (enable)
//        INTERN_DVBC_WriteReg(0x8010, 0x10);        // IIC by-pass mode on
//    else
//        INTERN_DVBC_WriteReg(0x8010, 0x00);        // IIC by-pass mode off
//}
