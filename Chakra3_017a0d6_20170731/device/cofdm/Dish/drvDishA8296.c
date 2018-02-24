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

#include "Board.h"
#include "MsCommon.h"
#include "HbCommon.h"
#include "drvDish.h"
#include "drvDemod.h"
#include "drvIIC.h"
#if(FRONTEND_DEMOD_TYPE == DEMOD_MSB131X)
#include "device_demodulator_msb131x.h"
#endif
#if(DISH_TYPE == DISH_A8296) //CUS_MICO

#define A8296_SLAVE_ADDR_R   0x11
#define A8296_SLAVE_ADDR   0x10

//   A8296  control register  
/*
bit7 bit6 bit5 bit4
0000 //unused

bit3
0: Disable LNB Output
1: Enable LNB Output

bit2 bit1 bit0
VSEL2 VSEL1 VSEL0 LNB (V)
0x0//0 0 0 			13.333
0x1//0 0 1 			13.667
0x2//0 1 0 			14.000
0x3//0 1 1 			14.333
0x4//1 0 0 			18.667
0x5//1 0 1 			19.000
0x6//1 1 0 			19.667
0x7//1 1 1 			20.000
*/
//bit2 bit1 bit0
#define DATA_POWER_13V     0x1  //13.667
#define DATA_POWER_18V     0x4  //18.667

//bit3  0: Disable LNB Output  1: Enable LNB Output
#define BIT_LNB_OFF           (0x0 << 3)
#define BIT_LNB_ON            (0x1 << 3)
/**************************************************************/
//A8296 Status Register
/*
0 DIS 		The DIS bit is set to 1 when the A8296 is disabled, (ENB = 0) or there is a fault: UVLO, OCP, CPOK, or TSD.
1 CPOK		If this bit is set low, the internal charge pump is not operating correctly (VCP). If the charge pump voltage is
			too low, the LNB output is disabled and the DIS bit is set.
2 OCP 		This bit will be set to a 1 if the LNB output current exceeds the overcurrent threshold (IOUT(MAX)) for more than
			the overcurrent disable time (tDIS). If the OCP bit is set to 1, then the DIS bit is also set to 1.
3 TRIMS 	Factory use only.
4 PNG		Set to 1 when the A8296 is enabled and the LNB output voltage is either too low or too high (nominally ¡À9%
			from the LNB DAC setting). Set to 0 when the A8296 is enabled and the LNB voltage is within the acceptable
			range (nominally ¡À5% from the LNB DAC setting).
5 ¨C 		Not used.
6 TSD 		The TSD bit is set to 1 if the A8296 has detected an overtemperature condition. If the TSD bit is set to 1, then
			the DIS bit is also set to 1.
7 UVLO 		The UVLO bit is set to 1 if either the voltage at the VIN pin or the voltage at the VREG pin is too low. If the
			UVLO bit is set to 1, then the DIS bit is also set to 1.
*/

#define LNB_OUTPUT_DISABLED    (0x1<<0)
#define CPOK            	   (0x1<<1)
#define OVERCURRENT            (0x1<<2)
#define POWER_NOT_GOOG         (0x1<<4)
#define THERMAL_SHUTDONW       (0x1<<6)
#define UNDERVOLTAGE           (0x1<<7)


#define DATA_LNBPOWER_OFF       	  (DATA_POWER_13V | BIT_LNB_OFF)					
#define DATA_13V_OUT                  (DATA_POWER_13V | BIT_LNB_ON)
#define DATA_18V_OUT                  (DATA_POWER_18V | BIT_LNB_ON)

 static MS_U8 u8PowerData = DATA_LNBPOWER_OFF;
/************************************************************************************/
MS_BOOL MDrv_Dish_Init(void)
{
    MS_U8 u8Data=0;

	MS_U8 u8BuffTemp[2];
	u8BuffTemp[0]=0x00;
	//note: before write need to read first when init
	MDrv_IIC_SetReadMode(E_HWI2C_READ_MODE_DIRECT);

	if(!MDrv_IIC_ReadBytes(FRONTEND_TUNER_PORT,A8296_SLAVE_ADDR_R, 0, NULL, 1, &u8Data))
	{
		printf("\n MDrv_Dish_Init failed-1-ReadBytes fail!");
	}	
	u8Data = DATA_13V_OUT; 
	u8BuffTemp[1]=u8Data;
	if(!MDrv_IIC_WriteBytes(FRONTEND_TUNER_PORT, A8296_SLAVE_ADDR, 0, NULL, 2, &u8BuffTemp[0]))
	{
		printf("\n MDrv_Dish_Init failed-2-WriteBytes fail!");
		return FALSE;
	}
	if(!MDrv_IIC_ReadBytes(FRONTEND_TUNER_PORT,A8296_SLAVE_ADDR_R, 0, NULL, 1, &u8Data))
	{
		printf("\n MDrv_Dish_Init failed-3-ReadBytes fail!");
	}

    return TRUE;
}
/************************************************************************************/
MS_BOOL MDrv_Dish_SetTone(EN_TONEBURST_TYPE enToneType)
{
 
      switch(enToneType)
      {
           case EN_TONEBURST_TYPE_0:
               return MDrv_DiSEqC_SetTone(FALSE);
               break;
           case EN_TONEBURST_TYPE_1:
               return MDrv_DiSEqC_SetTone(TRUE);
               break;
           default:
               printf("----%s error type %d----",__FUNCTION__,enToneType);
               break;
      }
      return FALSE;
}
/************************************************************************************/
MS_BOOL MDrv_Dish_SetLNBPower(DISH_LNBPWR_TYPE enLNBPwr)
{
	MS_U8 u8Data = 0;//DATA_22K_ON;
	MS_BOOL b8result=0;
	MS_U8 u8BuffTemp[2];
	u8BuffTemp[0]=0x00;

      switch(enLNBPwr)
      {
           case EN_LNBPWR_TYPE_OFF:
               u8Data= DATA_LNBPOWER_OFF;
               break;
           case EN_LNBPWR_TYPE_13V:
               u8Data = DATA_13V_OUT;
               break;
           case EN_LNBPWR_TYPE_18V:
               u8Data = DATA_18V_OUT;
               break;
           default:
 		       u8Data = DATA_13V_OUT;
               printf("----%s error type %d ----",__FUNCTION__,enLNBPwr);
               return FALSE;
      }

		u8BuffTemp[1]=u8Data;
		u8PowerData=u8Data;
	  	b8result=MDrv_IIC_WriteBytes(FRONTEND_TUNER_PORT, A8296_SLAVE_ADDR, 0, NULL, 2, &u8BuffTemp[0]);
		if(0==b8result)
		{
			 printf("\n MDrv_Dish_SetLNBPower failed-!");
		}

		return b8result;
	  
}
/************************************************************************************/
MS_BOOL MDrv_Dish_Set22k(DISH_LNB22K_TYPE enLNB22k)
{
      switch(enLNB22k)
      {
           case EN_LNB22K_TYPE_OFF:
               return MDrv_DiSEqC_Set22kOnOff(FALSE);
               break;
           case EN_LNB22K_TYPE_ON:
               return MDrv_DiSEqC_Set22kOnOff(TRUE);
               break;  
           default:
               printf("----%s error type %d----",__FUNCTION__,enLNB22k);
               return FALSE;
      }
       return FALSE;
}
/************************************************************************************/
MS_BOOL MDrv_Dish_SendCmd(MS_U8* pCmd,MS_U8 u8CmdSize)
{ 
     return MDrv_DiSEqC_SendCmd(pCmd,u8CmdSize);
}
/************************************************************************************/
MS_BOOL MDrv_Dish_IsOverCurrent(void)
{
    MS_U8 u8Status;
	MS_U8 u8BuffTemp[2];
	u8BuffTemp[0]=0x00;
	u8BuffTemp[1]=u8PowerData;
	//note: before read need to write first 
	MDrv_IIC_WriteBytes(FRONTEND_TUNER_PORT, A8296_SLAVE_ADDR, 0, NULL, 2, &u8BuffTemp[0]);
    if(MDrv_IIC_ReadBytes(FRONTEND_TUNER_PORT, A8296_SLAVE_ADDR_R, 0, NULL, 1, &u8Status))
    {
         if(u8Status&OVERCURRENT)
         {
             printf("\n----MDrv_Dish_IsOverCurrent=0x%x ----",u8Status);
             return TRUE;
         }
    }
    return FALSE;
}
#endif 

