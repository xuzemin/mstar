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
#define IF_TOSHIBA_TC90512XBG_C
#include "msAPI_Tuning.h"

#include "COFDM_Demodulator.h"
#include "drvIIC.h"

#define IF_TC90512_DBG(x)   //x

//****************************************************************************
// Private attributes of this file.
//****************************************************************************



static IF_FREQ m_eIF_Freq;
//****************************************************************************
// Private functions of this file.
//****************************************************************************



//****************************************************************************
// Start of public implementation
//****************************************************************************

/**
 FUNCTION    : void MDrv_IFDM_Init(void)

 USAGE    : To initialize IF-demodulator.

 INPUT    : None

 OUTPUT    : None

 GLOBALS: None

*/
void MDrv_IFDM_Init(void)
{
    m_eIF_Freq = IF_FREQ_INVALID;

    MDrv_IFDM_SetIF(IF_FREQ_B);
}

/**
 FUNCTION    : AFC MDrv_IFDM_GetFreqDev(void)

 USAGE    : To get frequency deviation.

 INPUT    : None

 OUTPUT    :

 GLOBALS: None

*/
U8 gBruceTest=0;
//extern BYTE GetSarAdcLevel(U16 u16SarID);
AFC MDrv_IFDM_GetFreqDev(void)
{
    BYTE cValue;
    U8 u8Add;

    u8Add = 0;

    //return E_AFC_MINUS_12p5KHz;
    devCOFDM_PassThroughI2C_ReadBytes(0xc2, 1, &u8Add, 1, &cValue);
    IF_TC90512_DBG(printf("IF_TC90512:Get VIF Value: %bx\n ", cValue));

    //Check Lock Flag
    if ((cValue & 0x40)==0)
       return  E_AFC_OUT_OF_AFCWIN;

    //Use Tuner-AFT to check it
    //Check AFT status
    cValue &= 0x07;
    switch (cValue)
    {
        case 0x04: //A2,A1,A0 = 1,0,0
                return  E_AFC_MINUS_112p5KHz;//E_AFC_OUT_OF_AFCWIN;
        break;
        case 0x03:
                return  E_AFC_MINUS_87p5KHz;//E_AFC_MINUS_62p5KHz;
        break;

        case 0x02:
                return  E_AFC_MINUS_62p5KHz;//E_AFC_MINUS_12p5KHz;
        break;

        case 0x01:
                return  E_AFC_MINUS_37p5KHz;//E_AFC_PLUS_62p5KHz;
        break;

        case 0x00:
                return  E_AFC_MINUS_12p5KHz;//;E_AFC_PLUS_62p5KHz;
        break;

    }

    //To get ADC Value from Sar
#if 0
            {
                U8 u8Data;

                u8Data = GetSarAdcLevel(PAD_SAR3);
                IF_TC90512_DBG(printf("---> GetSarAdcLevel = 0x%bx \n",u8Data));
            }
#endif

  return  E_AFC_OUT_OF_AFCWIN;


}

/**
 FUNCTION    : void MDrv_IFDM_SetIF(IF_FREQ eIF_Freq)

 USAGE    : To Set IF.

 INPUT    :

 OUTPUT    : None

 GLOBALS: None

*/
void MDrv_IFDM_SetIF(IF_FREQ eIF_Freq)
{
   // From Sharp Tuner Spec, we can't see any register setting about this IF
   // So, we support that we can't adjust these registers.

    m_eIF_Freq = eIF_Freq;
    IF_TC90512_DBG(printf("IF_TC90512: Sklip to set IF ...\n"));



}

void MDrv_IFDM_CVBSOff(void)
{
      // Not Implement for this IF
      IF_TC90512_DBG(printf("IF_TC90512: MDrv_IFDM_CVBSOff not implement\n"));


}

IF_FREQ MDrv_IFDM_GetIF(void)
{
    return m_eIF_Freq;
}
#undef IF_TOSHIBA_TC90512XBG_C
