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
// Copyright (c) 2006-2008 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (MStar Confidential Information!‥) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////




// copy from SEC_DTOS403IR121B
#ifndef MSTAR_AVATAR2_C
#define MSTAR_AVATAR2_C

#include <stdio.h>

#include "Board.h"
#include "datatype.h"
#include "drvIIC.h"
#include "COFDM_Demodulator.h"
#include "Tuner.h"
#include "msAPI_FreqTableATV.h"
#include "msAPI_Tuning.h"
#include "MApp_GlobalSettingSt.h"

#include "drvIIC.h"
#include "MApp_TopStateMachine.h"

#define DIVIDER_RATIO_31_25KHz  0x02
#define DIVIDER_RATIO_62_5KHz   0x06
#define DIVIDER_RATIO_166_7KHz  0x04
#define DIVIDER_RATIO_50KHz     0x00

#define USE_EXTERNAL_RF_AGC        1

#if (TN_FREQ_STEP == FREQ_STEP_31_25KHz)
#define DIVIDER_RATIO      DIVIDER_RATIO_31_25KHz
#elif (TN_FREQ_STEP == FREQ_STEP_50KHz)
#define DIVIDER_RATIO      DIVIDER_RATIO_50KHz
#elif (TN_FREQ_STEP == FREQ_STEP_62_5KHz)
#define DIVIDER_RATIO      DIVIDER_RATIO_62_5KHz
#endif

U8 aci_debug=3;

U16 avatar2_debug=BIT0|BIT9 ;
// BIT0: frequence
// BIT1: write register
// BIT2: write table
// BIT3: read table
// BIT4: VCO calibration
// BIT5: Avatar_Zion_ConfigIF2
// BIT6: tracking filter
// BIT7: n1, n2, p2 calculation
// BIT8: low/middle/high bands
// BIT9: Oracle(53)= 0xbe(DTV) or 3C(ATV)
// BIT10: print topstateMachine


#define DEBUG_AVATAR2 0

EN_TV_SIGNAL ucATV_DTV;   // 0: not init;   1: ATV;     2: DTV

#define DEBUG_PAL_TUNER   0

#define  PAL_DBG_MSG(x)  x

static FREQSTEP m_eFrequencyStep;

U8 ucStatus; // tuner status


#define SIZE_ORACLE (53)
#define SIZE_ZION (77)

U8 g_ucTunerID=_TUNER_I2C_ID_ORACLE;

void AvatarWriteByte(U8 u8Reg, U8 u8Val)
{
    U8 temp, temp2;
    U16 u16Temp=0x0200;

    u16Temp|=g_ucTunerID;
    temp=u8Reg;
    temp2=u8Val;

    MDrv_IIC_WriteBytes(u16Temp,  (U8)1, &temp, 1, &temp2);  // addr: i+1

#if DEBUG_AVATAR2
    if(g_ucTunerID==_TUNER_I2C_ID_ORACLE) printf("O:");
    else printf("Z:");
    printf(" W(%02x)=%02x \n",u8Reg, u8Val);

#endif

}

U8 AvatarReadByte(U8 u8Reg)
{
    U8 temp,  ret;
    U16 u16Temp=0x0200;

    u16Temp|=g_ucTunerID+1;
    temp=u8Reg;


#if DEBUG_AVATAR2
    if(g_ucTunerID==_TUNER_I2C_ID_ORACLE) printf("O:");
    else printf("Z:");
#endif

    MDrv_IIC_ReadBytes(u16Temp, 1, &temp, 1, &ret);
#if DEBUG_AVATAR2
    printf(" R(%02x)=%02x \n",u8Reg, ret);
#endif
    return ret;
}

void AvatarWriteByteMask(U8 u8Reg, U8 u8Val, U8 u8Msk)
{
    U8 ret;

    ret=AvatarReadByte(u8Reg);
    AvatarWriteByte(u8Reg,  (ret& (~u8Msk))|u8Val);
}

void OracleWriteByte(U8 u8Reg, U8 u8Val)
{
    g_ucTunerID=_TUNER_I2C_ID_ORACLE;
    AvatarWriteByte(u8Reg, u8Val);
}

U8 OracleReadByte(U8 u8Reg)
{
    U8  ret;

    g_ucTunerID=_TUNER_I2C_ID_ORACLE;
    ret= AvatarReadByte(u8Reg);
    return ret;
}

void OracleWriteByteMask(U8 u8Reg, U8 u8Val, U8 u8Msk)
{
    U8 ret;

    g_ucTunerID=_TUNER_I2C_ID_ORACLE;
    ret=OracleReadByte(u8Reg);
    OracleWriteByte(u8Reg,  (ret& (~u8Msk))|u8Val);
}

void ZionWriteByte(U8 u8Reg, U8 u8Val)
{
    g_ucTunerID=_TUNER_I2C_ID_ZION;
    AvatarWriteByte(u8Reg, u8Val);
}

U8 ZionReadByte(U8 u8Reg)
{
    U8  ret;

    g_ucTunerID=_TUNER_I2C_ID_ZION;
    ret= AvatarReadByte(u8Reg);
    return ret;
}

void ZionWriteByteMask(U8 u8Reg, U8 u8Val, U8 u8Msk)
{
    U8 ret;

    g_ucTunerID=_TUNER_I2C_ID_ZION;
    ret=ZionReadByte(u8Reg);
    ZionWriteByte(u8Reg,  (ret& (~u8Msk))|u8Val);
}


//XTAL=24
//IF2_SAW=38.9
//BEGIN
//INTERNAL
U8 oracle[][SIZE_ORACLE]=
{
	//0: POR
	{     0x0001,0x0020,0x0009,0x0000,0x0081,0x0008,0x004D,0x00F2,0x00FF,0x00FF,0x00FB,0x0017,0x0002,0x0089,0x00FF,0x0012,0x0008,0x00A9,0x00DF,0x0021,0x0000,0x0000,0x0040,0x0024,0x00E4,0x00CD,0x0014,0x0012,0x000A,0x00AE,0x0000,0x0066,0x000C,0x0030,0x001F,0x0000,0x000A,0x0000,0x0007,0x0000,0x0000,0x008F,0x0000,0x0000,0x0000,0x0008,0x0000,0x0000,0x0080,0x0095,0x0015,0x00AF,0x0002},

	// 1: 48.25
	{	0x0001,0x0020,0x0003,0x0014,0x0016,0x0002,0x0087,0x00F0,0x00FF,0x00FF,0x00FB,0x0027,0x0000,0x00A3,0x00F7,0x0044,0x0010,0x00AD,0x00DF,0x0021,0x0000,0x0000,0x0042,0x0024,0x00E4,0x00CC,0x0014,0x0012,0x000A,0x00AE,0x0008,0x0078,0x000C,0x0030,0x001F,0x0000,0x000A,0x0000,0x0007,0x0008,0x0000,0x001C,0x0000,0x0000,0x0000,0x0008,0x0000,0x0000,0x0048,0x0056,0x0016,0x003C,0x0000},

	// 2: 224.25
	{	0x0001,0x0020,0x0005,0x0011,0x0050,0x0002,0x0096,0x00F0,0x00FF,0x00FF,0x00FB,0x0027,0x0000,0x00E3,0x00F7,0x0044,0x0010,0x00A5,0x00DF,0x0021,0x0000,0x0000,0x0042,0x0024,0x00E4,0x00CC,0x0014,0x0012,0x000A,0x00AE,0x0008,0x0078,0x000C,0x0030,0x001F,0x0000,0x000A,0x0000,0x0007,0x0015,0x0000,0x0017,0x0000,0x0000,0x0000,0x0008,0x0000,0x0000,0x0048,0x0056,0x0016,0x003C,0x0000},

	// 3: DTV610
	{	0x0001,0x0020,0x0009,0x0009,0x0089,0x0002,0x00B6,0x00F0,0x00FF,0x00FF,0x00FB,0x0027,0x0000,0x00AC,0x00FF,0x0044,0x0021,0x00AE,0x00DF,0x0021,0x0000,0x0000,0x0042,0x0024,0x00FC,0x00CF,0x0014,0x0012,0x000A,0x00EE,0x0000,0x0066,0x000C,0x0030,0x001F,0x0000,0x000A,0x0000,0x0007,0x0002,0x0000,0x0039,0x0000,0x0000,0x0000,0x0008,0x0000,0x0000,0x0048,0x0056,0x0016,0x00BE,0x0002},

	// 4: DTV 858
	{	0x0001,0x0020,0x0009,0x0004,0x0080,0x0002,0x00CB,0x00F0,0x00FF,0x00FF,0x00FB,0x00A7,0x0080,0x00EC,0x00EF,0x0044,0x0021,0x00AE,0x00DF,0x0021,0x0000,0x0000,0x0042,0x0024,0x00FC,0x00CF,0x0014,0x0012,0x000A,0x00EE,0x0000,0x0066,0x000C,0x0030,0x001F,0x0000,0x000A,0x0000,0x0007,0x0014,0x0000,0x0015,0x0000,0x0000,0x0000,0x0008,0x0000,0x0000,0x0048,0x0056,0x0016,0x00BE,0x0002},

	// 5: DTV706
	{	0x0001,0x0020,0x0009,0x0009,0x0088,0x0002,0x00BE,0x00F0,0x00FF,0x00FF,0x00FB,0x0027,0x0000,0x00AC,0x00FF,0x0044,0x0021,0x00A6,0x00DF,0x0021,0x0000,0x0000,0x0042,0x0024,0x00FC,0x00CF,0x0014,0x0012,0x000A,0x00EE,0x0000,0x0066,0x000C,0x0030,0x001F,0x0000,0x000A,0x0000,0x0007,0x0003,0x0000,0x0017,0x0000,0x0000,0x0000,0x0008,0x0000,0x0000,0x0048,0x0056,0x0016,0x00BE,0x0002},

	// 6:DTV 554
	{	0x0001,0x0020,0x0009,0x0011,0x0091,0x0002,0x00B1,0x00F0,0x00FF,0x00FF,0x00FB,0x0027,0x0000,0x00AC,0x00FF,0x0044,0x0021,0x00A6,0x00DF,0x0021,0x0000,0x0000,0x0042,0x0024,0x00FC,0x00CF,0x0014,0x0012,0x000A,0x00EE,0x0000,0x0066,0x000C,0x0030,0x001F,0x0000,0x000A,0x0000,0x0007,0x000F,0x0000,0x001A,0x0000,0x0000,0x0000,0x0008,0x0000,0x0000,0x0048,0x0056,0x0016,0x00BE,0x0002},

    // 7:dvbc
    {   0x0001,0x0020,0x0009,0x0004,0x0080,0x0002,0x00CB,0x00F0,0x00FF,0x00FF,0x00FB,0x0027,0x0080,0x00AC,0x00FD,0x0044,0x0001,0x00A8,0x00DF,0x0021,0x0000,0x0000,0x0042,0x0024,0x00FC,0x00C9,0x0014,0x0012,0x000A,0x00EE,0x0000,0x0066,0x000C,0x0030,0x001F,0x0000,0x000A,0x0000,0x0007,0x0015,0x0000,0x0014,0x0000,0x0000,0x0000,0x0008,0x0000,0x0000,0x0048,0x007E,0x001E,0x00BE,0x0002},

};

U8 zion[][SIZE_ZION]=
{
	// 0:POR
	{	0x0001,0x0020,0x00E1,0x00D5,0x00DF,0x0041,0x006C,0x003B,0x0000,0x00FF,0x000F,0x001A,0x00B4,0x007A,0x0082,0x0042,0x0081,0x00A6,0x0024,0x0000,0x0000,0x0000,0x00AA,0x00D5,0x000A,0x003B,0x0003,0x0000,0x0060,0x006B,0x006B,0x0063,0x0063,0x0063,0x0063,0x0063,0x0003,0x0000,0x0000,0x005B,0x005B,0x005B,0x001B,0x00D6,0x0005,0x0000,0x0000,0x0000,0x0000,0x0002,0x004E,0x0049,0x0000,0x0000,0x0039,0x001C,0x005A,0x0002,0x0000,0x000C,0x000B,0x0000,0x0018,0x0018,0x0020,0x0018,0x0010,0x0004,0x0018,0x0000,0x0022,0x0021,0x0000,0x0040,0x0000,0x0002,0x004B},

	// 1:48.25
	{	0x0001,0x0020,0x00B1,0x007F,0x00BC,0x00E6,0x0066,0x002F,0x0000,0x00FF,0x000F,0x001A,0x009A,0x0076,0x008E,0x0073,0x0089,0x002E,0x0024,0x0001,0x0000,0x0000,0x002A,0x0015,0x000A,0x003B,0x0003,0x0008,0x006B,0x006B,0x006B,0x0063,0x0063,0x0063,0x0063,0x0063,0x0003,0x0000,0x0000,0x005B,0x005B,0x005B,0x001B,0x00D6,0x0005,0x0000,0x0000,0x0000,0x0000,0x0001,0x004E,0x0049,0x0000,0x0000,0x0039,0x001C,0x005A,0x0001,0x0000,0x000C,0x000B,0x0000,0x0018,0x0018,0x0020,0x0040,0x0016,0x0004,0x0018,0x0001,0x0022,0x0021,0x0000,0x0040,0x0000,0x0052,0x005C},

	// 2: 224.25
	{	0x0001,0x0020,0x00B1,0x0080,0x001C,0x0091,0x0011,0x002F,0x0000,0x00FF,0x000F,0x001A,0x009A,0x0076,0x008E,0x0073,0x0089,0x002E,0x0024,0x0001,0x0000,0x0000,0x002A,0x0015,0x000A,0x003B,0x0003,0x0008,0x006B,0x006B,0x006B,0x0063,0x0063,0x0063,0x0063,0x0063,0x0003,0x0000,0x0000,0x005B,0x005B,0x005B,0x001B,0x00D6,0x0005,0x0000,0x0000,0x0000,0x0000,0x0001,0x004E,0x0049,0x0000,0x0000,0x0039,0x001C,0x005A,0x0001,0x0000,0x000C,0x000B,0x0000,0x0018,0x0018,0x0020,0x0040,0x0016,0x0004,0x0018,0x0001,0x0022,0x0021,0x0000,0x0040,0x0000,0x0052,0x005C},

	// 3: DTV610
	{	0x0001,0x0020,0x00F9,0x0080,0x003C,0x0038,0x0051,0x0037,0x0000,0x00FF,0x000F,0x001A,0x00BA,0x007E,0x0082,0x0073,0x0089,0x00EE,0x0024,0x0001,0x0000,0x0000,0x002A,0x00D5,0x000A,0x003B,0x0003,0x0008,0x006C,0x006B,0x006B,0x0063,0x0063,0x0063,0x0063,0x0063,0x0003,0x0000,0x0000,0x005B,0x005B,0x005B,0x001B,0x00D6,0x0005,0x0000,0x0000,0x0000,0x0000,0x0001,0x004E,0x0049,0x0000,0x0000,0x0039,0x001C,0x005A,0x0001,0x0000,0x000C,0x000B,0x0000,0x0018,0x0018,0x0020,0x0048,0x0016,0x0004,0x0018,0x0000,0x0022,0x0021,0x0000,0x0040,0x0000,0x00D2,0x005F},

	// 4: DTV 858
	{	0x0001,0x0020,0x00F9,0x0080,0x007C,0x00B8,0x0051,0x0037,0x0000,0x00FF,0x000F,0x001A,0x00BA,0x007E,0x0082,0x0073,0x0089,0x00EE,0x0024,0x0001,0x0000,0x0000,0x002A,0x00D5,0x000A,0x003B,0x0003,0x0008,0x006C,0x006B,0x006B,0x0063,0x0063,0x0063,0x0063,0x0063,0x0003,0x0000,0x0000,0x005B,0x005B,0x005B,0x001B,0x00D6,0x0005,0x0000,0x0000,0x0000,0x0000,0x0001,0x004E,0x0049,0x0000,0x0000,0x0039,0x001C,0x005A,0x0001,0x0000,0x000C,0x000B,0x0000,0x0018,0x0018,0x0020,0x0040,0x0016,0x0004,0x0018,0x0000,0x0022,0x0021,0x0000,0x0040,0x0000,0x00C2,0x005F},

	// 5: DTV706
	{	0x0001,0x0020,0x00F9,0x0080,0x003C,0x0038,0x0051,0x0037,0x0000,0x00FF,0x000F,0x001A,0x00BA,0x007E,0x0082,0x0073,0x0089,0x00EE,0x0024,0x0001,0x0000,0x0000,0x002A,0x00D5,0x000A,0x003B,0x0003,0x0008,0x006C,0x006B,0x006B,0x0063,0x0063,0x0063,0x0063,0x0063,0x0003,0x0000,0x0000,0x005B,0x005B,0x005B,0x001B,0x00D6,0x0005,0x0000,0x0000,0x0000,0x0000,0x0001,0x004E,0x0049,0x0000,0x0000,0x0039,0x001C,0x005A,0x0001,0x0000,0x000C,0x000B,0x0000,0x0018,0x0018,0x0020,0x0040,0x0017,0x0004,0x0018,0x0000,0x0022,0x0021,0x0000,0x0040,0x0000,0x00D2,0x005F},

	// 6:DTV 554
	{	0x0001,0x0020,0x00F9,0x007F,0x00DC,0x008D,0x00A7,0x0037,0x0000,0x00FF,0x000F,0x001A,0x00BA,0x007E,0x0082,0x0073,0x0089,0x00EE,0x0024,0x0001,0x0000,0x0000,0x002A,0x00D5,0x000A,0x003B,0x0003,0x0008,0x006C,0x006B,0x006B,0x0063,0x0063,0x0063,0x0063,0x0063,0x0003,0x0000,0x0000,0x005B,0x005B,0x005B,0x001B,0x00D6,0x0005,0x0000,0x0000,0x0000,0x0000,0x0001,0x004E,0x0049,0x0000,0x0000,0x0039,0x001C,0x005A,0x0001,0x0000,0x000C,0x000B,0x0000,0x0018,0x0018,0x0020,0x0040,0x0016,0x0004,0x0018,0x0000,0x0022,0x0021,0x0000,0x0040,0x0000,0x00D2,0x005F},

        // 7:dvbc
//  {   0x0001,0x0020,0x00F9,0x0080,0x007C,0x00E2,0x00FC,0x0037,0x0000,0x00FF,0x000F,0x001A,0x00AA,0x007E,0x0082,0x0073,0x0089,0x00EE,0x0024,0x0001,0x0000,0x0000,0x002A,0x00D5,0x000A,0x003B,0x0003,0x0008,0x006C,0x006B,0x006B,0x0063,0x0063,0x0063,0x0063,0x0063,0x0003,0x0000,0x0000,0x005B,0x005B,0x005B,0x001B,0x00D6,0x0005,0x0000,0x0000,0x0000,0x0000,0x0001,0x004E,0x0049,0x0000,0x0000,0x0039,0x001C,0x005A,0x0001,0x0000,0x000C,0x000B,0x0000,0x0018,0x0018,0x0020,0x0040,0x0015,0x0004,0x0018,0x0000,0x0022,0x0021,0x0000,0x0040,0x0000,0x00D2,0x005F},
    {   0x0001,0x0020,0x00F9,0x0080,0x007C,0x00E2,0x00FC,0x0037,0x0000,0x00FF,0x000F,0x001A,0x009A,0x007a,0x0082,0x0073,0x0089,0x00EE,0x0024,0x0001,0x0000,0x0000,0x002A,0x00D5,0x000A,0x003B,0x0003,0x0008,0x006C,0x006B,0x006B,0x0063,0x0063,0x0063,0x0063,0x0063,0x0003,0x0000,0x0000,0x005B,0x005B,0x005B,0x001B,0x00D6,0x0005,0x0000,0x0000,0x0000,0x0000,0x0001,0x004E,0x0049,0x0000,0x0000,0x0039,0x001C,0x005A,0x0001,0x0000,0x000C,0x000B,0x0000,0x0018,0x0018,0x0020,0x0040,0x0015,0x0004,0x0018,0x0000,0x0022,0x0021,0x0000,0x0040,0x0000,0x00D2,0x005F},
                                                                                           // ^^^^^^^^^^^^
            };

void devTunerWriteOracle(U8 ucPara1)
{
	U8 i;
	U16 u16Temp=0x0200;

        u16Temp|=_TUNER_I2C_ID_ORACLE;

	if(avatar2_debug&BIT2) printf("\n");
	for(i=0;i<SIZE_ORACLE;i++)
	{
		U8 temp;
		temp=i+1;

	       MDrv_IIC_WriteBytes(u16Temp,  (U8)1, &temp, 1, &oracle[ucPara1][i]);  // addr: i+1
	    	if(avatar2_debug&BIT2) printf(" %02x", oracle[ucPara1][i]);
	    	if(i%16==7) if(avatar2_debug&BIT2) printf(" --");
		if(i%16==15) if(avatar2_debug&BIT2) printf("\n");

	}
	if(avatar2_debug&BIT2) printf("\n");
}

void	devTunerWriteZion(U8 ucPara1)
{
	U8 i;
       U16 u16Temp=0x0200;

       u16Temp|=_TUNER_I2C_ID_ZION;
	printf("\n");

	for(i=0;i<SIZE_ZION;i++)
	{
		U8 temp;
		temp=i+1;
	       MDrv_IIC_WriteBytes(u16Temp,  1,&temp, 1, &zion[ucPara1][i]);  // addr: i+1

		if(avatar2_debug&BIT2) printf(" %02x", zion[ucPara1][i]);
		if(i%16==7) if(avatar2_debug&BIT2) printf(" --");
		if(i%16==15) if(avatar2_debug&BIT2) printf("\n");
	}
	if(avatar2_debug&BIT2) printf("\n");

        ZionWriteByteMask(3, BIT6|BIT5, BIT6|BIT5|BIT4|BIT3);
}


void devTunerReadOracle(void)
{
    U8 i;
    U16 u16Temp=0x0200;

    u16Temp|=_TUNER_I2C_ID_ORACLE+1;
    if(avatar2_debug&BIT3) printf("\n");
    for(i=0;i<SIZE_ORACLE;i++)
    {
        U8 temp;
        U8 ret;
        temp=i+1;

        MDrv_IIC_ReadBytes(u16Temp, 1, &temp, 1, &ret);
        if(avatar2_debug&BIT3) printf(" %02x", ret);
        if(i%16==7) if(avatar2_debug&BIT3) printf(" --");
        if(i%16==15) if(avatar2_debug&BIT3) printf("\n");
    }
    if(avatar2_debug&BIT3) printf("\n");
}


void devTunerReadZion(void)
{
    U8 i;
    U16 u16Temp=0x0200;

    u16Temp|=_TUNER_I2C_ID_ZION+1;

    if(avatar2_debug&BIT3) printf("\n");
    for(i=0;i<SIZE_ZION;i++)
    {
        U8 temp;
        U8 ret;
        temp=i+1;

        MDrv_IIC_ReadBytes(u16Temp, 1, &temp, 1, &ret);
        if(avatar2_debug&BIT3) printf(" %02x", ret);
        if(i%16==7) if(avatar2_debug&BIT3) printf(" --");
        if(i%16==15) if(avatar2_debug&BIT3) printf("\n");
    }
    if(avatar2_debug&BIT3) printf("\n");
}

void Avatar_VCO_Calibration(void)
{
	U8 uMask;
	U8 uValue;

	U8 uOver;
	U8 uUnder;


//z05 [1:0] 0~3z61[2] 1=>0=>1

	g_ucTunerID=_TUNER_I2C_ID_ORACLE;

	//Trigger Oracle R37.1 = 1  -> 0  -> 1
	uMask = 0x02;

	uValue = 0x02;
//	HWIF_BUF_WriteBit(MainForm->Chip1.Handle, 37, &uValue, uMask);
	AvatarWriteByteMask(37, uValue, uMask);

	uValue = 0x00;
//    HWIF_BUF_WriteBit(MainForm->Chip1.Handle, 37, &uValue, uMask);
	AvatarWriteByteMask(37, uValue, uMask);

	uValue = 0x02;
//	HWIF_BUF_WriteBit(MainForm->Chip1.Handle, 37, &uValue, uMask);
	AvatarWriteByteMask(37, uValue, uMask);


	g_ucTunerID=_TUNER_I2C_ID_ZION;


	//Trigger Zion R5.0 = 1 -> 0
	uMask = 0x03;
	uValue = 0x01;
//	HWIF_BUF_WriteBit(MainForm->Chip2.Handle, 5, &uValue, uMask);
	AvatarWriteByteMask(5, uValue, uMask);


	//Trigger Zion R61.1 = 0 -> 1
	uMask = 0x02;
	uValue = 0x00;
//	HWIF_BUF_WriteBit(MainForm->Chip2.Handle, 61, &uValue, uMask);
	AvatarWriteByteMask(61, uValue, uMask);
	uValue = 0x02;
//	HWIF_BUF_WriteBit(MainForm->Chip2.Handle, 61, &uValue, uMask);
	AvatarWriteByteMask(61, uValue, uMask);


// ------------------------------------------------------------------
// Read Status

	g_ucTunerID=_TUNER_I2C_ID_ORACLE;

    //Check Oracle Vco1 Locked
//    HWIF_BUF_ReadReg(MainForm->Chip1.Handle,42, &uOver);
//    HWIF_BUF_ReadReg(MainForm->Chip1.Handle,43, &uUnder);
	uOver=AvatarReadByte(42);
	uUnder=AvatarReadByte(43);

      if(g_AVATAR_debug&BIT12) printf(" vco_bank=%x", uOver&0x0f );


	g_ucTunerID=_TUNER_I2C_ID_ZION;

    //Check Vco2 Locked
	uValue=AvatarReadByte(66);

    if(g_AVATAR_debug&BIT12) printf(" rvcobank=%x", ZionReadByte(67)&0x07);


    if(g_AVATAR_debug&BIT12)
    {
        if((uOver & 0x80)||(uUnder & 0x01))
            printf(" vco1: x");
        else
            printf(" vco1: o");
    }


    if(g_AVATAR_debug&BIT12)
    {
    //    HWIF_BUF_ReadReg(MainForm->Chip2.Handle,66, &uValue);
        if((uValue & 0x10)||(uValue & 0x20))
            printf(" vco2: x");
        else
            printf(" vco2: o");
    }

}


void devTunerSetFreqStep(FREQSTEP eFreqStep)
{
    switch(eFreqStep)
    {
    case FREQSTEP_31_25KHz:
    case FREQSTEP_62_5KHz:
    case FREQSTEP_50KHz:
        m_eFrequencyStep = eFreqStep;
        break;

    default:
        m_eFrequencyStep = FREQSTEP_31_25KHz;
        break;
    }
}

#define daniel_removez 0

typedef struct _Avatar_Parameter
{
    double RF_Freq;      //MHz
    double LO1_Freq;     //MHz
    double IF1_Freq;     //MHz
    double LO2_Freq;     //MHz
    double IF2_Freq;     //MHz
    double Xtal_Freq;    //MHz
    int   R1_Div;       //Divider_Oracle
    int   R2_Div;       //Divider_Zion
    int   PLL1_N1;      //Integer-N PLL
    int   PLL2_N2;      //Fractional-N PLL Integer part
    int   PLL2_P2;      //Fractional-N PLL Frac. part
//    int   LNA_Band;     //LAN BandSelect
}Avatar_Param_t;

Avatar_Param_t gAvatarParam;

void HWIF_BUF_WriteBit(U8 chip, U8 u8Reg, U8 u8Val, U8 u8Msk)
{
    U8 write_data;
    write_data=u8Val;
#if 0 // DEBUG_AVATAR2
    printf("\n chip=%x", chip);
    printf("\n u8Reg=%x", u8Reg);
    printf("\n u8Val=%x", u8Val);
    printf("\n u8Msk=%x", u8Msk);
#endif
    if(chip==Chip1)
    {
//    printf(" 111");
        OracleWriteByteMask(u8Reg, write_data, u8Msk);
    //printf(" 112");
    }
    else
    {
        //printf(" 113");

       ZionWriteByteMask(u8Reg,write_data, u8Msk);
           //printf(" 114");

    }
       // printf(" 115");

}

U8 HWIF_BUF_ReadReg(U8 chip, U8 u8Reg)
{
    U8 ret;
    if(chip==Chip1)
    {
        ret=OracleReadByte(u8Reg);
    }
    else
    {
       ret=ZionReadByte(u8Reg);
    }
    return ret;
}

void Avatar_Zion_ConfigIF2(int IsZeroIF)
{
    U8 uValue, uMask;
    if(IsZeroIF == 1)
    {
        //Zero IF
        //R8.2 = 0,  R8.3 =0, R8.4 =0, R8.6 =1, R8.7 =1
        //R9 = 0xFF
        //R10.0 =0, R10.1 =0
        uMask  = 0xDC; //11011100
        uValue = 0xC0; //11x000xx
        HWIF_BUF_WriteBit(Chip2, 8, uValue, uMask);

        uMask  = 0xFF;
        uValue = 0xFF;
        HWIF_BUF_WriteBit(Chip2, 9, uValue, uMask);

        uMask  = 0x03;
        uValue = 0x00;
        HWIF_BUF_WriteBit(Chip2, 10, uValue, uMask);
    }
    else
    {
        uMask  = 0xDC; //11011100
        uValue = (U8)~0xC0;
        HWIF_BUF_WriteBit(Chip2, 8, uValue, uMask);

        uMask  = 0xFF;
        uValue = (U8)~0xFF;
        HWIF_BUF_WriteBit(Chip2, 9, uValue, uMask);

        uMask  = 0x03;
        uValue = (U8)~0x00;
        HWIF_BUF_WriteBit(Chip2, 10, uValue, uMask);
    }

    uMask  = 0x18;

//    if((gAvatarParam.IF2_Freq==0) ||
    //    (gAvatarParam.IF2_Freq==36.17) ||
        //(gAvatarParam.IF2_Freq==44))
     if(ucATV_DTV==EN_DTV)
    {
        uValue = 0x10;//0,36.17,44-->Digital channel
        if(avatar2_debug&BIT5) printf(" IF2 DTV ");
    }
    else if(ucATV_DTV==EN_ATV)
    {
        uValue = 0x08;//33.9,38,38.9,45.75-->Analog channel
        if(avatar2_debug&BIT5) printf(" IF2 ATV ");
    }
    else
    {

        if(avatar2_debug&BIT5) printf("\n Abonormal!! \n");
        while(1);
    }

        HWIF_BUF_WriteBit(Chip2, 8,uValue, uMask);
}

//---------------------------------------------------------------------------

U8 Avatar_ReadTrackingFilterBandcode(void);

U8 Avatar_TrackingFilter_Calibration( U32 rf, U32 if2,U32 oracle_if, U32 r1)  //Avatar_Param_t *pAvatarParam)
{
    U8 uValue;
    U8 oracle_51_org;
    U8 calcnt;
//    U8 ret;

    // cliff
    OracleWriteByteMask(17, 0x01, 0x01); // need restore,   set 17[0]=1 for both ATV & DTV, restore to 0 after calibration for ATV
    OracleWriteByte(15, 0xff);  // no need to restore

#if daniel_removez
    double CurrentIF2;
    //Get Current IF2_SAW Value
    CurrentIF2=MainForm->IF2_SAW_ComboBox->Text.ToDouble();
#endif

    //Trig Zion_R74<3>=1
    uValue = 0x08;
          HWIF_BUF_WriteBit(Chip2, 76, uValue, 0x08);


        devTuner_SetFreq ( rf, 0, oracle_if, r1);
#if daniel_removez
    //Set ZIP mode
    MainForm->IF2_SAW_ComboBox->ItemIndex=0;
    MainForm->Avatar_RF_Frequency_Update();
#endif
    //CH Modified(980410, requested by Louis. It should not be modified when calibration)
    // Avatar_Zion_ConfigIF2(1);

    //Set Oracle_R23<1:0>=10
    uValue = 0x02;
    HWIF_BUF_WriteBit(Chip1, 23, uValue, 0x03);

//-----------------
    oracle_51_org=OracleReadByte(51);
    OracleWriteByteMask(51, 0x08, 0x1c);  // [4:2]=010

//-----------------

    //Set Oracle_R18<7>=1,Oracle_R18<5>=1
    uValue = 0xA0;
    HWIF_BUF_WriteBit(Chip1, 18, uValue, 0xA0);

    //Set Oracle_R16<6>=1
    uValue = 0x40;
    HWIF_BUF_WriteBit(Chip1, 16, uValue, 0x40);

#if 1

// cliff's code
       if(gAvatarParam.RF_Freq<85)         uValue = 0x0f;
       //else if(gAvatarParam.RF_Freq<170)   uValue = 0x06;
       else if(gAvatarParam.RF_Freq<175)   uValue = 0x06; // 990127 CH modified by Cliff's request
       else if(gAvatarParam.RF_Freq<250)   uValue = 0x11;
       else if(gAvatarParam.RF_Freq<370)   uValue = 0x0A;
       else if(gAvatarParam.RF_Freq<430)   uValue = 0x03;
       else if(gAvatarParam.RF_Freq<510)   uValue = 0x16;
       else if(gAvatarParam.RF_Freq<590)   uValue = 0x11;
       else if(gAvatarParam.RF_Freq<720)   uValue = 0x09;
       else uValue = 0x04;
#elif 0

       if(gAvatarParam.RF_Freq<85)         uValue = 0x14;
       else if(gAvatarParam.RF_Freq<175)   uValue = 0x06; // 990127 CH modified by Cliff's request
       else if(gAvatarParam.RF_Freq<255)   uValue = 0x11;
       else if(gAvatarParam.RF_Freq<375)   uValue = 0x0A;
       else if(gAvatarParam.RF_Freq<435)   uValue = 0x03;
       else if(gAvatarParam.RF_Freq<515)   uValue = 0x16;
       else if(gAvatarParam.RF_Freq<595)   uValue = 0x11;
       else if(gAvatarParam.RF_Freq<725)   uValue = 0x09;
       else uValue = 0x04;
#else
// ch's code
       if(gAvatarParam.RF_Freq<90)         uValue = 0x14;
       //else if(gAvatarParam.RF_Freq<170)   uValue = 0x06;
       else if(gAvatarParam.RF_Freq<175)   uValue = 0x06; // 990127 CH modified by Cliff's request
       else if(gAvatarParam.RF_Freq<250)   uValue = 0x11;
       else if(gAvatarParam.RF_Freq<370)   uValue = 0x0A;
       else if(gAvatarParam.RF_Freq<430)   uValue = 0x03;
       else if(gAvatarParam.RF_Freq<510)   uValue = 0x16;
       else if(gAvatarParam.RF_Freq<590)   uValue = 0x11;
       else if(gAvatarParam.RF_Freq<720)   uValue = 0x09;
       else uValue = 0x04;
#endif

    if(avatar2_debug&BIT6) printf(" init=%x ", uValue);

    HWIF_BUF_WriteBit(Chip1, 4, uValue, 0x1F);


    // --------------------------
    // 11 is automatic 00:manual. For calculation is by automatic method.
    // CH modified 990126
    // --------------------------
    //Set Oracle_R19<1:0>=00
    uValue = 0x00;
    HWIF_BUF_WriteBit(Chip1, 19, uValue, 0x03);
    //Set Oracle_R19<1:0>=11
    uValue = 0x03;
    HWIF_BUF_WriteBit(Chip1, 19, uValue, 0x03);

    calcnt=0;
    while(1)
    {
        calcnt++;
        if(OracleReadByte(19) & BIT4)
            break;
        if(avatar2_debug&BIT6) printf(".");
        if(g_AVATAR_debug & BIT4) MsOS_DelayTask(10);
        if(calcnt==50)          // 10*50=500ms
        {
            if(avatar2_debug&BIT6)  printf("\n Error: Avatar2 tracking fail, more than 500ms");
            break;
        }
    }

    // Wait some time to let the operation of calibration done.

    // CH modified 990126
//    Sleep(50);
    if(g_AVATAR_debug & BIT4) MsOS_DelayTask(200);

    //Trig Zion_R74<3>=0
    uValue = 0x00;
       HWIF_BUF_WriteBit(Chip2, 76, uValue, 0x08);

    // Restore Oracle 51
    OracleWriteByteMask(51, oracle_51_org, 0x1c);  // [4:2]=010

    // set 17[0]=1 for both ATV & DTV, restore to 0 after calibration for ATV
    if(if2==38900000)
    {
        OracleWriteByteMask(17, 0x00, 0x01);  // [4:2]=010
        if(avatar2_debug&BIT6)  printf("AA");
    }
    else
    {
        if(avatar2_debug&BIT6) printf("DD");
    }


    //Restore IF2_SAW Value
    devTuner_SetFreq ( rf, if2,oracle_if, r1);

#if daniel_removez
    MainForm->IF2_SAW_ComboBox->Text=CurrentIF2;
    MainForm->Avatar_RF_Frequency_Update();
#endif
    Avatar_Zion_ConfigIF2(0);

    return Avatar_ReadTrackingFilterBandcode();
}
//---------------------------------------------------------------------------
U8 Avatar_ReadTrackingFilterBandcode(void)
{
    U8 uValue;

    //LNA Band Code read out
    uValue=HWIF_BUF_ReadReg(Chip1, 5);
    uValue &= 0x1F;

//    printf("tracking=0x%x(%d)", uValue, uValue);
    if(avatar2_debug&BIT6) printf("tracking= %d (dec)",  uValue);
    return uValue;
}
//---------------------------------------------------------------------------
void Avatar_WriteTrackingFilterBandcode(U8 tf_band_code)
{
    U8 uValue;
    uValue = (U8)tf_band_code&0x00FF;
    HWIF_BUF_WriteBit(Chip1, 4, uValue, 0x1F);
}



//------------------------------------------------------------------------------------------
// oracle
// 5	5		7	6	MXINSEL3V<1:0>	1	0	2	h2	rw	High mid low band selection	Oracle		1				r0a0	White	Source Address	3.3	10		Victor
//  E	30		6	6	PLL1_VCO_HI_BAND	0	0	1	h0	rw	VCO high/low band selection. 1:high-band. 0:low-band.	Oracle		1				r0a0	White	Source Address	3.3	0		George

// zion
//5		7	5	PLL2_dsm_in<2:0>	2	0	3	h6	rw	DSM input	Zion		1				r0a0	White	Source Address	1.8	110		Sponge
//6		7	0	PLL2_dsm_in1<7:0>	7	0	8	h41	rw	DSM input	Zion		1				r0a0	White	Source Address	1.8	1000001		Sponge
//7		7	0	PLL2_dsm_in2<7:0>	7	0	8	h6c	rw	DSM input	Zion		1				r0a0	White	Source Address	1.8	1101100		Sponge
//有的，PLL2_dsm_in<2:0> & PLL2_dsm_in1<7:0> & PLL2_dsm_in2<7:0>，可以參考Application Note 第20頁，
//它的作用就是你之前問的問題，由於N1，N2是四捨五入後的結果，因此沒法非常精細，而P2就可以補足N2不夠精細的部份。

//------------------------------------------------------------------------------------------
//  atv
//  if2=38900000;
//  rf=u32RealFreq;

//  dtv
//  if2=36167000;
//  rf=(Freq )*1000000L; //u32RealFreq;



void devTuner_SetFreq ( U32 rf, U32 if2, U32 oracle_if, U32 r1 )
{
    U32 lo1,	if1,	lo2,fxtal;
//    U32 r1;
    U32 r2,fstep1,	fstep2,	n1,	n2,	p2;
//    U32 oracle_if;

    U16 u16LowBandMaxMHz=175;
    U16 u16MiddleBandMaxMHz=430;

    gAvatarParam.RF_Freq=1.0*rf/1000/1000;

#if 0
    if(ucATV_DTV==EN_DTV || if2==0)
        oracle_if=1575000000;	// 1.575G
    else
        oracle_if=1551000000;	// 1.575G
#endif

    fxtal=24000000;
//    r1=2;
    r2=1;

    fstep1=fxtal/r1;
    fstep2=fxtal/r2;

    n1=1.0*(oracle_if+rf)/fstep1+0.5;		// round()
//    printf("     n1*100=%d",  (1.0*(oracle_if+rf)/fstep1+0.5)*100);
    //printf("     n1=%d",  1.0*(oracle_if+rf)/fstep1);
    //printf("     n1+0.5=%d ",  1.0*(oracle_if+rf)/fstep1+0.5);


    lo1=fstep1*n1;
    if1=lo1-rf;
    lo2=if1-if2;
    n2=(lo2*2)/fstep2;			// int()

    p2=(1.0*524288L*(1.0*lo2/fstep2*2-n2));		// int

// if(avatar2_debug&BIT7)

if(g_AVATAR_debug&BIT9)

{
    printf("     p2x  =%lx   ", (1.0*lo2/fstep2*2-n2)*10000);
    printf("     p2x  =%lx   ", (1.0*lo2/fstep2*2-n2)*524288L);

    printf("\n  oracle_if=%lu", oracle_if);
    printf("\n  if2=%lu", if2);
    printf("\n  fxtal=%lu", fxtal);
    printf("\n  r1=%lu", r1);
    printf("\n  r2=%lu", r2);
    printf("\n  fstep1=%lu", fstep1);
    printf("\n  fstep2=%lu", fstep2);
    printf("\n  rf=%lu", rf);
    printf("\n  n1=%lu", n1);
    printf("\n  lo1=%lu", lo1);
    printf("\n  if1=%lu", if1);
    printf("\n  lo2=%lu", lo2);
    printf("\n  n2=%lu", n2);
    printf("\n  p2=%lu", p2);
    printf("\n p2=%lx", p2);
    printf(" \n ");
}

// 0429
if(g_AVATAR_debug&BIT11)
{
    printf("if1=%lu ", if1);
    printf("if2=%lu ", if2);
}

	{
//		printf("\n>>>%d MHz", rf/1000/10);  // 2 digital
		 g_ucTunerID=_TUNER_I2C_ID_ORACLE;
		AvatarWriteByte(0x07,n1);
		AvatarWriteByteMask(0x08,n1>>8,0x0f);
		AvatarWriteByteMask(0x06,r1,0x01f);

		if(rf/1000/1000 <  u16LowBandMaxMHz)
		{
                     if(avatar2_debug&BIT8)  printf("low band \n");
			AvatarWriteByteMask(0x03,BIT1, BIT3|BIT2|BIT1); // CC_BAND
			AvatarWriteByteMask(0x05,0<<6, BIT7|BIT6);		// MXINSEL3V
			AvatarWriteByteMask(0x1E,0<<6, BIT6);		// PLL1_VCO_HI_BAND
		}
		else if(rf/1000/1000 <  u16MiddleBandMaxMHz)
		{
			if(avatar2_debug&BIT8)  printf("middle band \n");
			AvatarWriteByteMask(0x03,BIT2, BIT3|BIT2|BIT1);
			AvatarWriteByteMask(0x05,1<<6, BIT7|BIT6);		// MXINSEL3V
			AvatarWriteByteMask(0x1E,0<<6, BIT6);		// PLL1_VCO_HI_BAND
		}
		else
		{
			if(avatar2_debug&BIT8)  printf("high band \n");
			AvatarWriteByteMask(0x03,BIT3, BIT3|BIT2|BIT1);
			AvatarWriteByteMask(0x05,2<<6, BIT7|BIT6);		// MXINSEL3V
			AvatarWriteByteMask(0x1E,1<<6, BIT6);		// PLL1_VCO_HI_BAND
		}

		 g_ucTunerID=_TUNER_I2C_ID_ZION;
		AvatarWriteByte(0x04,n2);

		AvatarWriteByteMask(0x05,((p2>>16)&0x07)<<5,BIT7| BIT6|BIT5 );
		AvatarWriteByte(0x06,(p2>>8)&0xff);
		AvatarWriteByte(0x07,(p2)&0xff);

//        	printf("  p2=%x", ((p2>>16)&0x07));
    //    	printf("  -%x", ((p2>>8)&0xff));
        //	printf("  -%x", p2&0xff);

       }
}


void bugu01(void)
{
        OracleWriteByte(52, 0xbe);  // 1011-1110
//        ZionWriteByte(77, 0x5f);
        ZionWriteByte(77, 0x27);

}

U8 devTuner_SetFreq2 ( U32 rf, U32 if2)
{
//    U8 i;
    U8 u8AgcState;
    U8 u8AgcState2;
    U8 u8AgcState3;
    U8 u8AgcState4;

    U32 r1, oracle_if;


// ----------------------------------------------
// r1, oracle_if move outside for patch N+1, N-1
    r1=2;
    if(ucATV_DTV==EN_DTV || if2==0)
        oracle_if=1575000000;	// 1.575G
    else
        oracle_if=1551000000;	// 1.575G

/*
1.       chip2 Reg16 0x74
2.       chip2 Reg17 0x21
3.       chip1 Reg17 bit<3:5>=011
4.       chip1 Reg18 bit<0:2>=111
*/

// cliff remove it 2009/4/29

    if(g_AVATAR_debug&BIT8)
    {
        ZionWriteByte(16, 0x74);
        ZionWriteByte(17, 0x21);
        OracleWriteByteMask(17, BIT5|BIT4 , BIT5|BIT4|BIT3);
        OracleWriteByteMask(18, BIT2|BIT1|BIT0, BIT2|BIT1|BIT0);
    }

    if(avatar2_debug&BIT0)
    {
        printf("\n** %d MHz** ", rf/1000/10);  // 2 digital
    }

     if(ucATV_DTV==EN_DTV)
    {
//        if(avatar2_debug&BIT9)   printf("O(52,be)");
//        OracleWriteByte(53, 0xbe);  // 1011-1110

#if 0
        OracleWriteByte(52, 0xbe);  // 1011-1110
        ZionWriteByte(77, 0x5f);
#else
        bugu01();
#endif
    }
    else
    {
//        if(avatar2_debug&BIT9)  printf("O(52,3C)");
//        OracleWriteByte(53, 0x3C); // 0011-1100
        OracleWriteByte(52, 0x3C); // 0011-1100
        ZionWriteByte(77, 0x5C);

    }
    if(avatar2_debug&BIT9) printf("RO[52]=%x ",  OracleReadByte(52));

//------------------------------------------------------------------------
// 1st calculate N1 N2 R2

// tune specific freq with if2=38.9
    devTuner_SetFreq ( rf, if2, oracle_if, r1);
    if(g_AVATAR_debug & BIT4) MsOS_DelayTask(100);
    Avatar_VCO_Calibration();
    if(g_AVATAR_debug & BIT4) MsOS_DelayTask(100);


// disable while auto search()

//EN_TOP_STATE ret;
//char *str;
//ret=MApp_TopStateMachine_GetTopState();
//str=MApp_TopStateMachine_GetTopStateName();
//    if(avatar2_debug&BIT10)  printf("ret=%d",ret);
//    if(avatar2_debug&BIT10)  printf("str=%s",str);

//if(g_AVATAR_debug==0x1)

//if(     (ret==STATE_TOP_DTV_SCAN) ||
    ///     (ret==STATE_TOP_ATV_SCAN) ||
        // (ret==STATE_TOP_DTV_MANUAL_TUNING) ||
         //(ret==STATE_TOP_ATV_MANUAL_TUNING)
        // )

if(g_AVATAR_debug & BIT0)
    {
    // tune specific freq with if2=0
//        devTuner_SetFreq ( rf, 0);

        Avatar_TrackingFilter_Calibration(rf, if2,oracle_if, r1);
        if(g_AVATAR_debug & BIT4) MsOS_DelayTask(10);


    // tune specific freq with if2=38.9
//        devTuner_SetFreq ( rf, if2);
        if(g_AVATAR_debug & BIT4) MsOS_DelayTask(10);
        Avatar_VCO_Calibration();
        if(g_AVATAR_debug & BIT4) MsOS_DelayTask(10);
    }
    else
    {
//            MsOS_DelayTask(200);

    }
    if(g_AVATAR_debug & BIT4) MsOS_DelayTask(200);
    if(avatar2_debug&BIT10) printf("\n");

    MsOS_DelayTask(1);  // wait for agc_state ready
    u8AgcState=(ZionReadByte(76) & BIT4)? 1: 0;

    if(g_AVATAR_debug & BIT6) printf("agc_state=%d ", u8AgcState);



if(ucATV_DTV==EN_DTV)
{
U8 o17,o18, o25, o26;
U8 z13, z14, z15, z16, z18, z23, z24, z76;

    o17=OracleReadByte(17);
    o18=OracleReadByte(18);
    o25=OracleReadByte(25);
    o26=OracleReadByte(26);

    z13=ZionReadByte(13);
    z14=ZionReadByte(14);
    z15=ZionReadByte(15);
    z16=ZionReadByte(16);
    z18=ZionReadByte(18);
    z23=ZionReadByte(23);
    z24=ZionReadByte(24);
    z76=ZionReadByte(76);

    //-----------------------------------------------------
    // use N+1 table if u8AgcState=0

    if((g_AVATAR_debug&BIT7 )&& (aci_debug>=1))
    {
        if(!u8AgcState)
        {
            printf("<N+1> ");

            oracle_if=1551000000;
            r1=4;
            devTuner_SetFreq ( rf, if2, oracle_if, r1);

//            OracleWriteByte(13, 0x00);  // round2 add
            OracleWriteByte(17, 0x21);
            OracleWriteByte(18, 0xA6);
            OracleWriteByte(25, 0xE4);
            OracleWriteByte(26, 0xCD);   // round2 add, org CF

            ZionWriteByte(13, 0x9A);    // round2 change 0x8a to 0x9a
//            ZionWriteByte(14, 0x6E); // round2 remove
            ZionWriteByte(15, 0x8E); // round2 add
            ZionWriteByte(16, 0x52); // round to change from 0x52 to 0x62
            ZionWriteByte(18, 0xAE); // round2 add
            ZionWriteByte(23, 0xAA);
            ZionWriteByte(24, 0x15);
            ZionWriteByte(76, 0x42);

            if(g_AVATAR_debug&BIT10) Avatar_VCO_Calibration();
            OracleWriteByteMask(19, 0, BIT0);
            OracleWriteByteMask(19, 1, BIT0);
            bugu01();

            MsOS_DelayTask(1);  // wait for agc_state ready
            u8AgcState2=(ZionReadByte(76) & BIT4)? 1: 0;
            if(g_AVATAR_debug & BIT6) printf("agc_state2=%d ", u8AgcState2);

        }
    }


    //-----------------------------------------------------
    // use N-1 table if u8AgcState=0

    if((g_AVATAR_debug&BIT7 )&& (aci_debug>=2))
    {
        if(!u8AgcState2)
        {
            printf("<N-1> ");

            oracle_if=1599000000;	// 1.575G
            r1=2;
            devTuner_SetFreq ( rf, if2, oracle_if, r1);

//            OracleWriteByte(26, 0xCD); // round2 remove
//            OracleWriteByte(13, 0x80);   // round2 change from 0x9a to 0x80

//            ZionWriteByte(13, 0x9A);     // round2 remove
            ZionWriteByte(14, 0x6E);     // round2 add
            ZionWriteByte(16, 0x63);
            ZionWriteByte(18, 0xEE);    // round2 add
            ZionWriteByte(24, 0x15);    // round2 add

            if(g_AVATAR_debug&BIT10) Avatar_VCO_Calibration();
            OracleWriteByteMask(19, 0, BIT0);
            OracleWriteByteMask(19, 1, BIT0);
            bugu01();
             MsOS_DelayTask(1);  // wait for agc_state ready
            u8AgcState3=(ZionReadByte(76) & BIT4)? 1: 0;
            if(g_AVATAR_debug & BIT6) printf("agc_state3=%d ", u8AgcState3);
        }
    }

    //-----------------------------------------------------
    // use N table if u8AgcState3=0

    if((g_AVATAR_debug&BIT7 )&& (aci_debug>=3))
    {
        if(!u8AgcState3)
        {
            printf("<N> ");

            oracle_if=1575000000;	// 1.575G
            r1=2;
            devTuner_SetFreq ( rf, if2, oracle_if, r1);



//-------------------------------------------------------------------------
#if 1
            OracleWriteByte(17,o17);
            OracleWriteByte(18,o18);
            OracleWriteByte(25,o25);
            OracleWriteByte(26,o26);

            ZionWriteByte(13,z13);
            ZionWriteByte(14,z14);
            ZionWriteByte(15,z15);
            ZionWriteByte(16,z16);
            ZionWriteByte(18,z18);
            ZionWriteByte(23,z23);
            ZionWriteByte(24,z24);
            ZionWriteByte(76,z76);
#else
            OracleWriteByte(17, 0x31);
            OracleWriteByte(18, 0xa7);
            OracleWriteByte(25, 0xFC);
            OracleWriteByte(26, 0xCF);

            ZionWriteByte(13, 0xBA);
            ZionWriteByte(14, 0x7E);
            ZionWriteByte(16, 0x73);
            ZionWriteByte(23, 0x2A);
            ZionWriteByte(24, 0xD5);
            ZionWriteByte(76, 0xD2);
#endif
            OracleWriteByteMask(19, 0, BIT0);
            OracleWriteByteMask(19, 1, BIT0);
            bugu01();
            MsOS_DelayTask(1);  // wait for agc_state ready
            u8AgcState4=(ZionReadByte(76) & BIT4)? 1: 0;
            if(g_AVATAR_debug & BIT6) printf("agc_state4=%d ", u8AgcState4);
        }
    }
    MsOS_DelayTask(10);  // wait for agc_state ready

}

    return u8AgcState;

}

void devTunerSetPLLData(WORD wPLLData, RFBAND eBand)
{

    U32	rf,	if2;

    eBand=eBand;
    if(ucATV_DTV!=EN_ATV)
    {
        ucATV_DTV=EN_ATV;
        devTunerWriteOracle(0x01);
        devTunerWriteZion(0x01);
        printf("\n ***********************************");
        printf("\n ** ATV ****************************");
        printf("\n ***********************************\n");
//        ZionWriteByteMask(8, BIT3, BIT4|BIT3);
    }

//    printf("\n devTunerSetPLLData %x, %x ", wPLLData, eBand);
    if2=38900000;

#if( TN_FREQ_STEP==   FREQ_STEP_50KHz )
//    printf("\n wPLLData*50 =  %ld ", 1L*wPLLData*50000);
    rf=1L*wPLLData*50000 - TUNER_IF_FREQ_KHz*1000;
//    printf("\n wPLLData*50 - IF freq =  %ld ", rf);
//    printf("\n (wPLLData*50 - IF freq)/1000 =  %ld ", rf/1000);
#endif

    devTuner_SetFreq2 ( rf, if2);

}

void devTunerInit(void)
{


    printf("\n avatar2: devTunerInit()");
    devTunerWriteOracle(0x01);
    devTunerWriteZion(0x01);
}


#define DIGITAL_TUNER_IF    36.167

void devDigitalTuner_Init()
{
    printf("\n avatar2:devDigitalTuner_Init()");
    devTunerWriteOracle(0x03);
    devTunerWriteZion(0x03);
    gAvatarParam.IF2_Freq=36.17;
}

void devDigitalTuner_SetFreq ( double Freq, RF_CHANNEL_BANDWIDTH eBandWidth)
{
    U32	rf,	if2;
    eBandWidth=eBandWidth;

    if(ucATV_DTV!=EN_DTV)
    {

#if(ENABLE_DVBC)       // change some gain
    #define DTV_table  0x07
#else
    #define DTV_table  0x03
#endif

        ucATV_DTV=EN_DTV;
        devTunerWriteOracle(DTV_table);
        devTunerWriteZion(DTV_table);

        printf("\n ***********************************");
        printf("\n ** DTV ****************************");
        printf("\n ***********************************\n");

//        ZionWriteByteMask(8, BIT3, BIT4|BIT3);

    }


#if 0
    printf(" \nDIGITAL_TUNER_IF=%d",(U8)( 1000*DIGITAL_TUNER_IF));
    printf(" \nFreq(f)=%f", Freq);
    printf(" \nFreq=%d", Freq);
#endif

    if2=36167000;
    rf=(Freq )*1000000L;

    devTuner_SetFreq2( rf, if2);




}

#undef MSTAR_AVATAR2_C
#endif


