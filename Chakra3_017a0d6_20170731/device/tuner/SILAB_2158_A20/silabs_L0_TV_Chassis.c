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
/*************************************************************************************************************/
/*                                  Silicon Laboratories                                                     */
/*                                  Broadcast Video Group                                                    */
/*                     Layer 0      Communication Functions                                                  */
/* FILE: Silabs_L0_TV_Chassis.c                                                                              */
/*-----------------------------------------------------------------------------------------------------------*/
/*   This source code contains all i2c functions to communicate with i2c components                          */
/*     All functions are declared in Silabs_L0_TV_Chassis.h                                                  */
/*************************************************************************************************************/
#include "silabs_L0_TV_Chassis.h"

// #include "x_stl_lib.h"
// #include "x_typedef.h"
#include "si2158_i2c_api.h"
// #include "PD_Def.h"
/************************************************************************************************************************
	NAME: L0_Init function
	DESCRIPTION:layer 0 initialization function
              Used to sets the layer 0 context parameters to startup values.
			  The I2C address of the Si2173 is set in the Si2170_L1_API_Init procedure.
              It is automatically called by the Layer 1 init function.
	Parameter:	Pointer to L0 (I2C) Context -
	Porting:	In most cases, no modifications should be required.
	Returns:    void
************************************************************************************************************************/
void   L0_Init  (L0_Context *pContext)
{
    (pContext)->address       = 0;
    return;
}
 /************************************************************************************************************************
  L0_SetAddress function
  Use:        function to set the device address
              Used to set the I2C address of the component.
              It must be called only once at startup per Layer 1 instance, as the addresses are not expected to change over time.
  Returns:    1 if OK, 0 otherwise
************************************************************************************************************************/
int     L0_SetAddress        (L0_Context* i2c, unsigned int add, int addSize)
{
  i2c->address   = add;
  i2c->indexSize = addSize;
  return 0;
}

/************************************************************************************************************************
  NAME: system_wait
  DESCRIPTION:	Delay for time_ms (milliseconds)
  Porting:		Replace with embedded system delay function
  Returns:		nothing
************************************************************************************************************************/
void system_wait(int time_ms)
{
    MsOS_DelayTask(time_ms);
    return;
}
/************************************************************************************************************************
  NAME: system_time
  DESCRIPTION:	Delay for time_ms (milliseconds)
  Porting:		Replace with embedded system delay function
  Returns:		nothing
************************************************************************************************************************/
 unsigned int system_time(void)
{
    return MsOS_GetSystemTime();
}

/************************************************************************************************************************
  L0_ReadBytes function
  Use:        lowest layer read function
              Used to read a given number of bytes from the Layer 1 instance.
  Parameters: i2c, a pointer to the Layer 0 context.
              iI2CIndex, the index of the first byte to read.
              iNbBytes, the number of bytes to read.
              *pbtDataBuffer, a pointer to a buffer used to store the bytes.
  Returns:    the number of bytes read.
************************************************************************************************************************/
int    L0_ReadBytes              (L0_Context* i2c, unsigned int iI2CIndex, int iNbBytes, unsigned char *pucDataBuffer)
{

    int i=0;

    iI2CIndex = iI2CIndex;

    if (SI215X_ucI2cReadOnly(i2c->address,pucDataBuffer,iNbBytes)!=0)
    {
        mcSHOW_HW_MSG(("[Silabs]:<= I2C Read Error\n"));
    }

    mcSHOW_DBG_MSG4(("SI215X_ucI2cReadOnly:i2c->address =%x;iNbBytes=%d\n",i2c->address,iNbBytes));
    for(i=0;i<iNbBytes;i++)
     {mcSHOW_DBG_MSG4(("pucDataBuffer[%x]\n",pucDataBuffer[i]));}

    return iNbBytes;
}

/************************************************************************************************************************
  L0_WriteBytes function
  Use:        lowest layer write function
              Used to write a given number of bytes from the Layer 1 instance.
  Parameters: i2c, a pointer to the Layer 0 context.
              iI2CIndex, the index of the first byte to write.
              iNbBytes, the number of bytes to write.
              *pbtDataBuffer, a pointer to a buffer containing the bytes to write.
  Returns:    the number of bytes read.
************************************************************************************************************************/
int      L0_WriteBytes             (L0_Context* i2c, unsigned int iI2CIndex, int iNbBytes, unsigned char *pucDataBuffer)
{
    int i=0;

    iI2CIndex = iI2CIndex;

    if (SI215X_ucI2cWriteOnly(i2c->address,pucDataBuffer,iNbBytes) !=0)
    {
        mcSHOW_HW_MSG(("[Silabs]:<= I2C Write Error\n"));
    }
    // ICtrlBus_I2cTunerWrite(0x100,i2c->address,pucDataBuffer,iNbBytes);
    mcSHOW_DBG_MSG4(("SI215X_ucI2cWriteOnly:i2c->address =%x;iI2CIndex=%x;iNbBytes=%d\n",i2c->address,iI2CIndex,iNbBytes));
    for(i=0;i<iNbBytes;i++)
        { mcSHOW_DBG_MSG4(("pucDataBuffer[%x]\n",pucDataBuffer[i]));}

    return iNbBytes;
}

/************************************************************************************************************************
  L0_ReadCommandBytes function
  Use:        'command mode' bytes reading function
              Used to read a given number of bytes from the Layer 1 instance in 'command mode'.
  Comment:    The 'command mode' is a specific mode where the indexSize is always 0 and the index is always 0x00
  Parameters: i2c, a pointer to the Layer 0 context.
              iNbBytes, the number of bytes to read.
              *pucDataBuffer, a pointer to a buffer used to store the bytes.
  Returns:    the number of bytes read.
************************************************************************************************************************/
 int     L0_ReadCommandBytes    (L0_Context* i2c, int iNbBytes, unsigned char *pucDataBuffer)
{ return L0_ReadBytes (i2c, 0x00, iNbBytes, pucDataBuffer); }

/************************************************************************************************************************
  L0_WriteCommandBytes function
  Use:        'command mode' bytes writing function
              Used to write a given number of bytes to the Layer 1 instance in 'command mode'.
  Comment:    The 'command mode' is a specific mode where the indexSize is always 0 and the index is always 0x00
  Parameters: i2c, a pointer to the Layer 0 context.
              iNbBytes, the number of bytes to write.
              *pucDataBuffer, a pointer to a buffer containing the bytes.
  Returns:    the number of bytes written.
************************************************************************************************************************/
 int      L0_WriteCommandBytes   (L0_Context* i2c, int iNbBytes, unsigned char *pucDataBuffer)
{ return L0_WriteBytes(i2c, 0x00, iNbBytes, pucDataBuffer); }


/************************************************************************************************************************/
