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
#define _MSB1501_C_

/* ------------------------------------
    Header Files
   ------------------------------------ */
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "MSB1501.h"
#include "msAPI_Timer.h"
#include "MApp_IR.h"
#include "MApp_Key.h"
#include "MApp_GlobalVar.h"



#define MSB1501_DBINFO(y) //y

#define MSTAR_MSB1501_I2C_ADDR     (((U16) I2C_DEV_DATABASE << 8) | 0xF2)
#define MSB1501_ADDR_H         0x00
#define MSB1501_READ_REG       0x04
#define MSB1501_RAM_CONTROL    0x05

#define MSB1501_OUTER_STATE    0x80

#define MSB1501_VSB_TRAIN_SNR_LIMIT   0xBE//14.5dB
#define MSB1501_FEC_ENABLE     0x1F//

#define QAM_CHECK_LOCK_TIME_SLICE     50
#define QAM_WAIT_AGC_LOCK_TIME        250
#define QAM_WAIT_PRE_LOCK_TIME        700
#define QAM_WAIT_LOCK_TOTAL_TIME      2000
#define QAM_CHECK_AGC_LOCK_COUNTER    QAM_WAIT_AGC_LOCK_TIME/QAM_CHECK_LOCK_TIME_SLICE
#define QAM_CHECK_PRE_LOCK_COUNTER    QAM_WAIT_PRE_LOCK_TIME/QAM_CHECK_LOCK_TIME_SLICE
#define QAM_CHECK_LOCK_COUNTER        QAM_WAIT_LOCK_TOTAL_TIME/QAM_CHECK_LOCK_TIME_SLICE

#define MSB1501_VSB_CHECK_TIME      69//60
#define MSB1501_PRE_LOCK_CHECK_TIME   9//7
#define MSB1501_AGC_LOCK_CHECK_TIME   2

code U8 MSB1501_table[] = {
 #include "MSB1501_demod.dat"
};

U32 Scan_Time_Start;
U8 CheckAGCLockCount,CheckPreLockCount,CheckLockCount;
EN_DEMOD_RESULT DEMODEVSB_STATUS,DEMODEQAM_STATUS;
/***********************************************************************************
************************************************************************************/

void MSB1501_StatusINIT(void)
{
    DEMODEVSB_STATUS=DEMOD_INIT;
    DEMODEQAM_STATUS=DEMOD_INIT;
}

BOOLEAN MSB1501_WriteReg(U16 u16Addr, U8 u8Data)
{
    U8 u8MsbData[3];
    u8MsbData[0] = MSB1501_ADDR_H;
    u8MsbData[1] = (u16Addr >> 8) & 0xff;
    u8MsbData[2] = u16Addr & 0xff;
    return MDrv_IIC_WriteBytes(MSTAR_MSB1501_I2C_ADDR, 3, u8MsbData, 1, &u8Data);
}
/***********************************************************************************
************************************************************************************/
static BOOLEAN MSB1501_RAMCTL(U8 u8Data)
{
    U8 u8MsbData[1];
    u8MsbData[0] = MSB1501_RAM_CONTROL;
    return MDrv_IIC_WriteByte(MSTAR_MSB1501_I2C_ADDR, u8MsbData[0], u8Data);
}
/***********************************************************************************
************************************************************************************/
BOOLEAN  MSB1501_ReadReg(U16 u16Addr, U8* u8Data)
{
    U8 u8MsbData[3];
    u8MsbData[0] = MSB1501_ADDR_H;
    u8MsbData[1] = (u16Addr >> 8) & 0xff;
    u8MsbData[2] = u16Addr & 0xff;
    MDrv_IIC_WriteBytes(MSTAR_MSB1501_I2C_ADDR, 3, u8MsbData, 0, u8Data);
    u8MsbData[0] = MSB1501_READ_REG;
    return MDrv_IIC_ReadByte(MSTAR_MSB1501_I2C_ADDR, u8MsbData[0], u8Data);
}

/***********************************************************************************
************************************************************************************/
BOOLEAN MSB1501_Init(void)
{
    U8 u8MsbData[3];
    U8 data1;

#if ((FRONTEND_TUNER_TYPE == NXP_FQD1136_TUNER) )

    U8 Demod_Flow_register[27] =

        {0x80, 0x55, 0x0A, 0x21, 0x3D, 0x55, 0xCB, 0x32, 0x5E, 0x52,

         0x72, 0x52, 0x72, 0x5C, 0x5C, 0xA3, 0xfd, 0xea, 0x05, 0x74,

         0x1E, 0x34, 0x3A, 0x07, 0xE8, 0xE8, 0x10};

#elif (( FRONTEND_TUNER_TYPE == NXP_TD1136_TUNER) )

    U8 Demod_Flow_register[27] =

        {0x80, 0x55, 0x0A, 0x21, 0x3D, 0x55, 0xCB, 0x32, 0x5E, 0x52,

         0x72, 0x52, 0x72, 0x5C, 0x5C, 0xA3, 0xfd, 0xea, 0x05, 0x74,

         0x1E, 0x34, 0x3A, 0x07, 0xE8, 0xE8, 0x00};

#else

    U8 Demod_Flow_register[27] =

        {0x80, 0x55, 0x0A, 0x21, 0x3D, 0x55, 0xCB, 0x32, 0x5E, 0x52,

         0x72, 0x52, 0x72, 0x5E, 0x5C, 0xA3, 0xfd, 0xea, 0x05, 0x74,

         0x1F, 0x34, 0x3A, 0x08, 0xE8, 0xC4, 0x00};

#endif

        #if TS_PARALLEL_OUTPUT
            MSB1501_WriteReg(0x809d,0x00);
        #else
            MSB1501_WriteReg(0x809d,0x20);
        #endif

        if(MSB1501_WriteReg(0x8081, 0x01)==FALSE)
          return FALSE;
        if(MSB1501_WriteReg(0x8080, 0x03)==FALSE)
          return FALSE;
        if(MSB1501_WriteReg(0x8030, 0x55)==FALSE)
          return FALSE;
        if(MSB1501_WriteReg(0x8031, 0xAA)==FALSE)
          return FALSE;
        if(MSB1501_RAMCTL(1)==FALSE)
          return FALSE;

        u8MsbData[0] = MSB1501_ADDR_H;
        u8MsbData[1] = 0;
        u8MsbData[2] = 0;
        if(!MSB1501_Download(u8MsbData, sizeof(MSB1501_table), MSB1501_table))
          printf("\n 1 Download NG");

        u8MsbData[1] = 0x58;
        u8MsbData[2] = 0x00;
        if(!MSB1501_Download(u8MsbData, sizeof(Demod_Flow_register), Demod_Flow_register))
          printf("\n 2 Download NG");

        if(MSB1501_WriteReg(0x8080, 0x00)==FALSE)
            return FALSE;
        if(MSB1501_WriteReg(0x8081, 0x00)==FALSE)
            return FALSE;

        MSB1501_DBINFO(MSB1501_FWVERSION());

        msAPI_Timer_Delayms(50);
        if( MSB1501_RAMCTL(0) )
        {
            MSB1501_ReadReg(0x8012, &data1);
            if(MSB1501_WriteReg(0x8012, data1|0x80)==FALSE)
                return FALSE;
            else
                return TRUE;
        }
        else
            return FALSE;

}
/***********************************************************************************
************************************************************************************/
BOOLEAN MSB1501_Download(U8* MSB1501_Download_Address, U16 MSB1501_Download_Size, U8* MSB1501_Download_Table)
{
    U16 i;

#if (!USE_SW_I2C)

    HW_IIC_Reset();
    HW_IIC_Start();
    if(HW_SendByte(MSTAR_MSB1501_I2C_ADDR&0xFE)==FALSE) return FALSE;
    for(i=0;i<3;i++)
    {
      if(HW_SendByte(*(MSB1501_Download_Address+i))==FALSE) return FALSE;
    }
    for(i=0;i<MSB1501_Download_Size;i++)
    {
      if(HW_SendByte(*(MSB1501_Download_Table+i))==FALSE) return FALSE;
    }
    HW_IIC_Stop();

#else

    if (IIC_AccessStart((MSTAR_MSB1501_I2C_ADDR&0xFE), 1) == FALSE)
    {
//      continue;
      MSB1501_DBINFO(printf("\n MSB1501_I2C_ADDR&0xFE NG"));
      return FALSE;
    }
    for(i=0;i<3;i++)
    {
     if(IIC_SendByte(*(MSB1501_Download_Address+i))==FALSE) return FALSE;
    }
    for(i=0;i<MSB1501_Download_Size;i++)
    {
      if(IIC_SendByte(*(MSB1501_Download_Table+i))==FALSE) return FALSE;
    }
    IIC_Stop();

#endif
    return TRUE;
}
/***********************************************************************************
************************************************************************************/
BOOLEAN MSB1501_SoftReset(void)
{
    if (!MSB1501_WriteReg(0x8091, 0x00))
        return FALSE;

    if (!MSB1501_WriteReg(0x8081, 0x04))
        return FALSE;
    return MSB1501_WriteReg(0x8081, 0x00);



}
/***********************************************************************************
************************************************************************************/
BOOLEAN MSB1501_VsbMode(void)
{
    return MSB1501_WriteReg(0x8091, 0x08);
}
/***********************************************************************************
************************************************************************************/
BOOLEAN MSB1501_64QamMode(void)
{
    if(MSB1501_WriteReg(0x8094, 0x00)==FALSE) return FALSE;
    return MSB1501_WriteReg(0x8091, 0x04);
}
/***********************************************************************************
************************************************************************************/
BOOLEAN MSB1501_256QamMode(void)
{
    if(MSB1501_WriteReg(0x8094, 0x01)==FALSE) return FALSE;
    return MSB1501_WriteReg(0x8091, 0x04);
}
/***********************************************************************************
************************************************************************************/
BOOLEAN MSB1501_RepeaterEnable(void)
{
    return MSB1501_WriteReg(0x8010, 0x0A);
}
/***********************************************************************************
************************************************************************************/
BOOLEAN MSB1501_RepeaterDisable(void)
{
    return MSB1501_WriteReg(0x8010, 0x00);
}

/**************************************************************************
***************************************************************************/
BOOLEAN MSB1501_Vsb_QAM_AGCLock(void)
{
  U8 data1;

  MSB1501_ReadReg(0x853A, &data1);//AGC_LOCK
  if(data1&0x01)
    return TRUE;
  else
    return FALSE;
}
/**************************************************************************
***************************************************************************/
BOOLEAN MSB1501_Vsb_PreLock(void)
{
    U8 data1;

    MSB1501_ReadReg(0x8093, &data1);//<0>TR_LOCK, <1>PTK_LOCK
  if((data1&0x02)==0x02)
    return TRUE;
  else
    return FALSE;
}
/**************************************************************************
***************************************************************************/
BOOLEAN MSB1501_QAM_PreLock(void)
{
  U8 data1;

  MSB1501_ReadReg(0x8521, &data1);//TR_LOCK
  if((data1&0x01)==0x01)
    return TRUE;
  else
    return FALSE;
}

/**************************************************************************
* MSB1501 QAM Main Lock Check Driver
* Conditions:
* Description :
* This function is used to check whether the channel chip is lock
* or not in VSB mode.
* Addr :
* Value:
* 15bit -> 1:Lock , 0:Unlock
***************************************************************************/
BOOLEAN MSB1501_QAM_Main_Lock(void)
{
  U8 data1, data2, data3, data4, data5, data6;

  MSB1501_ReadReg(0x8624, &data2);//RS_UNCOR_INTNUM1
  MSB1501_ReadReg(0x8622, &data3);//RS_UNCOR_PKTNUM1
  MSB1501_ReadReg(0x8618, &data4);//boundary detected
  MSB1501_ReadReg(0x8601, &data5);//FEC_EN_CTL
  MSB1501_ReadReg(0x8521, &data6);//TR_LOCK
  MSB1501_ReadReg(0x8092, &data1);

  if(data1==MSB1501_OUTER_STATE && data3<=data2 && (data4&0x01)==0x01
       && data5==MSB1501_FEC_ENABLE && (data6&0x01)==0x01)
    return TRUE;
  else
    return FALSE;
}
/**************************************************************************
* MSB1501 VSB CE Lock Driver
* Conditions:
* Description :
* This function is used to check whether the channel
* chip is lock or not in VSB mode.
* Addr :
* Value:
* 12bit -> 0: , 1:
***************************************************************************/
BOOLEAN MSB1501_Vsb_CE_Lock(void)
{
  U8 data1;

  MSB1501_ReadReg(0x8093, &data1);//<4>1:CE Search Fail

  if((data1&0x10)==0)
    return TRUE;
  else
    return FALSE;
}

/**************************************************************************
* MSB1501 VSB FEC Lock Check Driver
* Conditions:
* Description :
* This function is used to check whether the channel
* chip is lock or not in VSB mode.
* Addr :
* Value:
* 12bit -> 0:Lock , 1:Unlock
***************************************************************************/
BOOLEAN MSB1501_Vsb_FEC_Lock(void)
{
  U8 data1, data2, data3, data4, data5, data6;
  MSB1501_ReadReg(0x8624, &data2);//RS_UNCOR_INTNUM1
  MSB1501_ReadReg(0x8622, &data3);//RS_UNCOR_PKTNUM1
  MSB1501_ReadReg(0x8092, &data1);
  MSB1501_ReadReg(0x8717, &data4);//AD_NOISE_PWR_TRAIN1
  MSB1501_ReadReg(0x8093, &data5);//<0>TR_LOCK, <1>PTK_LOCK
  MSB1501_ReadReg(0x8601, &data6);//FEC_EN_CTL

  if(data1==MSB1501_OUTER_STATE && data3<=data2 && data4<=MSB1501_VSB_TRAIN_SNR_LIMIT
       && (data5&0x03)==0x03 && data6==MSB1501_FEC_ENABLE)
    return TRUE;
  else
    return FALSE;
}

EN_SCAN_RESULT MSB1501_VSBCheckLock(void)
{
    EN_SCAN_RESULT VSB_SCAN=CHECKING;

    printf("DEMODEVSB_STATUS=%x",DEMODEVSB_STATUS);
    switch (DEMODEVSB_STATUS)
    {
        case DEMOD_INIT:
            CheckAGCLockCount = MSB1501_AGC_LOCK_CHECK_TIME;
            CheckPreLockCount = MSB1501_PRE_LOCK_CHECK_TIME;
            CheckLockCount = MSB1501_VSB_CHECK_TIME;
            DEMODEVSB_STATUS = DEMOD_CKING;
            Scan_Time_Start = msAPI_Timer_GetTime0();
            break;
       case DEMOD_CKING:
            if(CheckLockCount>0 && msAPI_Timer_DiffTimeFromNow(Scan_Time_Start) > QAM_CHECK_LOCK_TIME_SLICE )
            {
                Scan_Time_Start = msAPI_Timer_GetTime0();
                --CheckLockCount;
                if(MSB1501_Vsb_QAM_AGCLock())
                {
                    if(MSB1501_Vsb_PreLock())
                    {
                        if(MSB1501_Vsb_CE_Lock()==FALSE)
                        {
                            MSB1501_DBINFO(printf("MSB1501_Vsb_CE_Lock()==FALSE\r\n"));
                            MSB1501_DBINFO(printf("MSB1501_Vsb_FEC_Lock()==FALSE\r\n"));
                            VSB_SCAN=UNLOCK;
                        }
                        if(MSB1501_Vsb_FEC_Lock())
                        {
                            MSB1501_DBINFO(printf("MSB1501_Vsb_CE_Lock()==TRUE\r\n"));
                            MSB1501_DBINFO(printf("MSB1501_Vsb_FEC_Lock()==TRUE\r\n"));
                            VSB_SCAN=LOCK;
                        }
                    }
                    else
                    {
                         --CheckPreLockCount;
                        if( !CheckPreLockCount)
                        {
                            MSB1501_DBINFO(printf("MSB1501_PRELOCK_Lock()==FALSE\r\n"));
                            VSB_SCAN=UNLOCK;
                        }

                    }
                }
                else
                    --CheckAGCLockCount;

                if( !CheckAGCLockCount || !CheckLockCount )
                {
                    MSB1501_DBINFO(printf("MSB1501_AGC_Lock()==FALSE\r\n"));
                    VSB_SCAN=UNLOCK;
                }

            }
            else if( !CheckLockCount )
                VSB_SCAN=CHECKEND;

            if( VSB_SCAN != CHECKING )
                DEMODEVSB_STATUS = DEMOD_INIT;

            break;
        default:
            VSB_SCAN=CHECKEND;
            DEMODEVSB_STATUS = DEMOD_INIT;
            break;
    }
    printf("VSB_SCAN=%x\r\n",VSB_SCAN);
    return VSB_SCAN;


}

/***********************************************************************************
************************************************************************************/

EN_SCAN_RESULT MSB1501_QAMCheckLock(void)
{

    EN_SCAN_RESULT QAM_SCAN=CHECKING;

    switch (DEMODEQAM_STATUS)
    {
        case DEMOD_INIT:
            CheckAGCLockCount = QAM_CHECK_AGC_LOCK_COUNTER;
            CheckPreLockCount = QAM_CHECK_PRE_LOCK_COUNTER+QAM_CHECK_AGC_LOCK_COUNTER;
            CheckLockCount=QAM_CHECK_LOCK_COUNTER+QAM_CHECK_PRE_LOCK_COUNTER+QAM_CHECK_AGC_LOCK_COUNTER;
            DEMODEQAM_STATUS = DEMOD_CKING;
            Scan_Time_Start = msAPI_Timer_GetTime0();
            break;
       case DEMOD_CKING:
            if(CheckLockCount>0 && msAPI_Timer_DiffTimeFromNow(Scan_Time_Start) > QAM_CHECK_LOCK_TIME_SLICE )
            {
                Scan_Time_Start = msAPI_Timer_GetTime0();
                --CheckLockCount;
                if(MSB1501_Vsb_QAM_AGCLock())
                {
                    MSB1501_DBINFO(printf("MSB1501_QAM_AGCLock()==TRUE\r\n"));
                    if( MSB1501_QAM_PreLock() )
                    {
                        if(MSB1501_QAM_Main_Lock())
                        {
                            MSB1501_DBINFO(printf("MSB1501_QAM_Sync_Lock()==TRUE\r\n"));
                            QAM_SCAN =LOCK;
                        }
                    }
                    else
                    {
                        --CheckPreLockCount;
                        if(!CheckPreLockCount)
                        {
                            MSB1501_DBINFO(printf("MSB1501_QAM_PreLock()==FALSE\r\n"));
                            QAM_SCAN =UNLOCK;
                        }
                    }

                }
                else
                    --CheckAGCLockCount;

                if( !CheckAGCLockCount || !CheckLockCount)
                {
                    MSB1501_DBINFO(printf("MSB1501_QAM_AGCLock()==FALSE\r\n"));
                    QAM_SCAN =UNLOCK;
                }

            }
            else if( !CheckLockCount )
                QAM_SCAN=CHECKEND;

             if( QAM_SCAN != CHECKING )
                DEMODEQAM_STATUS = DEMOD_INIT;

            break;
            default:
            QAM_SCAN =CHECKEND;
            DEMODEQAM_STATUS = DEMOD_INIT;
            break;
    }

    return QAM_SCAN;

    //MSB1501_DBINFO(printf("MSB1501_QAM_Sync_Lock()==FALSE\r\n"));

}

/***********************************************************************************
************************************************************************************/


U8 MSB1501_Check8VSB64_256QAM(void)
{
    U8 mode;

    MSB1501_ReadReg(0x8500, &mode);//mode check

     if( (mode&VSB_1501) == VSB_1501 )
        return VSB;
     else  if( (mode & QAM256_1501) ==QAM256_1501)
        return QAM256;
     else
        return QAM64;


}
void MSB1501_CheckSignalCondition(MSB1501SignalCondition_t* pstatus)
{
    U8 mode;
    U8  u8NoisePowerH;
    static U8 u8NoisePowerH_Last=0xff;
    mode = MSB1501_Check8VSB64_256QAM();

    MSB1501_ReadReg(0x8715, &u8NoisePowerH);//
    if( mode == VSB )//VSB mode//SNR=10*log10((1344<<10)/noisepower)
    {
        if(!MSB1501_Vsb_FEC_Lock())
          u8NoisePowerH=0xFF;
        else if( abs(u8NoisePowerH_Last-u8NoisePowerH)> 5)
            u8NoisePowerH_Last = u8NoisePowerH;
        else
            u8NoisePowerH = u8NoisePowerH_Last;

        if(u8NoisePowerH>0xBE)//SNR<14.5
            *pstatus=MSB1501_SIGNAL_NO;
        else if(u8NoisePowerH>0x4D)//SNR<18.4
            *pstatus=MSB1501_SIGNAL_WEAK;
        else if(u8NoisePowerH>0x23)//SNR<21.8
            *pstatus=MSB1501_SIGNAL_MODERATE;
        else if(u8NoisePowerH>0x0A)//SNR<26.9
            *pstatus=MSB1501_SIGNAL_STRONG;
        else
            *pstatus=MSB1501_SIGNAL_VERY_STRONG;
    }
    else//QAM MODE
    {
        if(!MSB1501_QAM_Main_Lock())
            u8NoisePowerH=0xFF;
        else if( abs(u8NoisePowerH_Last-u8NoisePowerH)> 5)
            u8NoisePowerH_Last = u8NoisePowerH;
        else
            u8NoisePowerH = u8NoisePowerH_Last;

      if( mode == QAM256 )//256QAM//SNR=10*log10((2720<<10)/noisepower)
      {
            if(u8NoisePowerH>0x13)//SNR<27.5
                *pstatus=MSB1501_SIGNAL_NO;
            else if(u8NoisePowerH>0x08)//SNR<31.2
                *pstatus=MSB1501_SIGNAL_WEAK;
            else if(u8NoisePowerH>0x06)//SNR<32.4
                *pstatus=MSB1501_SIGNAL_MODERATE;
            else if(u8NoisePowerH>0x04)//SNR<34.2
                *pstatus=MSB1501_SIGNAL_STRONG;
            else
                *pstatus=MSB1501_SIGNAL_VERY_STRONG;
      }
      else //if(mode&0x02==0x00)//64QAM//SNR=10*log10((2688<<10)/noisepower)
      {
            if(u8NoisePowerH>0x4C)//SNR<21.5
                *pstatus=MSB1501_SIGNAL_NO;
            else if(u8NoisePowerH>0x1F)//SNR<25.4
                *pstatus=MSB1501_SIGNAL_WEAK;
            else if(u8NoisePowerH>0x11)//SNR<27.8
                *pstatus=MSB1501_SIGNAL_MODERATE;
            else if(u8NoisePowerH>0x07)//SNR<31.4
                *pstatus=MSB1501_SIGNAL_STRONG;
            else
                *pstatus=MSB1501_SIGNAL_VERY_STRONG;
      }
    }
}
/***********************************************************************************
************************************************************************************/
U8 MSB1501_ReadSNRPercentage(void)
{
//#define MAX_SNR  40
    U8 mode;
    U8 u8NoisePowerH, u8NoisePowerL;
    U16 u16NoisePower;
//    float SNR;

    mode = MSB1501_Check8VSB64_256QAM();
//    if(MSB1501_WriteReg(0x873E, 0x01)==FALSE) return 0;// set freeze
    MSB1501_ReadReg(0x8714, &u8NoisePowerL);//
    MSB1501_ReadReg(0x8715, &u8NoisePowerH);//
//    if(MSB1501_WriteReg(0x873E, 0x00)==FALSE) return 0;// release freeze
    u16NoisePower=u8NoisePowerH<<8|u8NoisePowerL;

    if( mode == VSB )//VSB mode//SNR=10*log10((1344<<10)/noisepower)
    {
        if(!MSB1501_Vsb_FEC_Lock())
          return 0;//SNR=0;
        else if (u16NoisePower<=0x008A)//SNR>=40dB
          return 100;//SNR=MAX_SNR;
        else if (u16NoisePower<=0x0097)//SNR>=39.6dB
          return 99;//
        else if (u16NoisePower<=0x00A5)//SNR>=39.2dB
          return 98;//
        else if (u16NoisePower<=0x00B5)//SNR>=38.8dB
          return 97;//
        else if (u16NoisePower<=0x00C7)//SNR>=38.4dB
          return 96;//
        else if (u16NoisePower<=0x00DA)//SNR>=38.0dB
          return 95;//
        else if (u16NoisePower<=0x00EF)//SNR>=37.6dB
          return 94;//
        else if (u16NoisePower<=0x0106)//SNR>=37.2dB
          return 93;//
        else if (u16NoisePower<=0x0120)//SNR>=36.8dB
          return 92;//
        else if (u16NoisePower<=0x013B)//SNR>=36.4dB
          return 91;//
        else if (u16NoisePower<=0x015A)//SNR>=36.0dB
          return 90;//
        else if (u16NoisePower<=0x017B)//SNR>=35.6dB
          return 89;//
        else if (u16NoisePower<=0x01A0)//SNR>=35.2dB
          return 88;//
        else if (u16NoisePower<=0x01C8)//SNR>=34.8dB
          return 87;//
        else if (u16NoisePower<=0x01F4)//SNR>=34.4dB
          return 86;//
        else if (u16NoisePower<=0x0224)//SNR>=34.0dB
          return 85;//
        else if (u16NoisePower<=0x0259)//SNR>=33.6dB
          return 84;//
        else if (u16NoisePower<=0x0293)//SNR>=33.2dB
          return 83;//
        else if (u16NoisePower<=0x02D2)//SNR>=32.8dB
          return 82;//
        else if (u16NoisePower<=0x0318)//SNR>=32.4dB
          return 81;//
        else if (u16NoisePower<=0x0364)//SNR>=32.0dB
          return 80;//
        else if (u16NoisePower<=0x03B8)//SNR>=31.6dB
          return 79;//
        else if (u16NoisePower<=0x0414)//SNR>=31.2dB
          return 78;//
        else if (u16NoisePower<=0x0479)//SNR>=30.8dB
          return 77;//
        else if (u16NoisePower<=0x04E7)//SNR>=30.4dB
          return 76;//
        else if (u16NoisePower<=0x0560)//SNR>=30.0dB
          return 75;//
        else if (u16NoisePower<=0x05E5)//SNR>=29.6dB
          return 74;//
        else if (u16NoisePower<=0x0677)//SNR>=29.2dB
          return 73;//
        else if (u16NoisePower<=0x0716)//SNR>=28.8dB
          return 72;//
        else if (u16NoisePower<=0x07C5)//SNR>=28.4dB
          return 71;//
        else if (u16NoisePower<=0x0885)//SNR>=28.0dB
          return 70;//
        else if (u16NoisePower<=0x0958)//SNR>=27.6dB
          return 69;//
        else if (u16NoisePower<=0x0A3E)//SNR>=27.2dB
          return 68;//
        else if (u16NoisePower<=0x0B3B)//SNR>=26.8dB
          return 67;//
        else if (u16NoisePower<=0x0C51)//SNR>=26.4dB
          return 66;//
        else if (u16NoisePower<=0x0D81)//SNR>=26.0dB
          return 65;//
        else if (u16NoisePower<=0x0ECF)//SNR>=25.6dB
          return 64;//
        else if (u16NoisePower<=0x103C)//SNR>=25.2dB
          return 63;//
        else if (u16NoisePower<=0x11CD)//SNR>=24.8dB
          return 62;//
        else if (u16NoisePower<=0x1385)//SNR>=24.4dB
          return 61;//
        else if (u16NoisePower<=0x1567)//SNR>=24.0dB
          return 60;//
        else if (u16NoisePower<=0x1778)//SNR>=23.6dB
          return 59;//
        else if (u16NoisePower<=0x19BB)//SNR>=23.2dB
          return 58;//
        else if (u16NoisePower<=0x1C37)//SNR>=22.8dB
          return 57;//
        else if (u16NoisePower<=0x1EF0)//SNR>=22.4dB
          return 56;//
        else if (u16NoisePower<=0x21EC)//SNR>=22.0dB
          return 55;//
        else if (u16NoisePower<=0x2531)//SNR>=21.6dB
          return 54;//
        else if (u16NoisePower<=0x28C8)//SNR>=21.2dB
          return 53;//
        else if (u16NoisePower<=0x2CB7)//SNR>=20.8dB
          return 52;//
        else if (u16NoisePower<=0x3108)//SNR>=20.4dB
          return 51;//
        else if (u16NoisePower<=0x35C3)//SNR>=20.0dB
          return 50;//
        else if (u16NoisePower<=0x3AF2)//SNR>=19.6dB
          return 49;//
        else if (u16NoisePower<=0x40A2)//SNR>=19.2dB
          return 48;//
        else if (u16NoisePower<=0x46DF)//SNR>=18.8dB
          return 47;//
        else if (u16NoisePower<=0x4DB5)//SNR>=18.4dB
          return 46;//
        else if (u16NoisePower<=0x5534)//SNR>=18.0dB
          return 45;//
        else if (u16NoisePower<=0x5D6D)//SNR>=17.6dB
          return 44;//
        else if (u16NoisePower<=0x6670)//SNR>=17.2dB
          return 43;//
        else if (u16NoisePower<=0x7052)//SNR>=16.8dB
          return 42;//
        else if (u16NoisePower<=0x7B28)//SNR>=16.4dB
          return 41;//
        else if (u16NoisePower<=0x870A)//SNR>=16.0dB
          return 40;//
        else if (u16NoisePower<=0x9411)//SNR>=15.6dB
          return 39;//
        else if (u16NoisePower<=0xA25A)//SNR>=15.2dB
          return 38;//
        else if (u16NoisePower<=0xB204)//SNR>=14.8dB
          return 37;//
        else if (u16NoisePower<=0xC331)//SNR>=14.4dB
          return 36;//
        else if (u16NoisePower<=0xD606)//SNR>=14.0dB
          return 35;//
        else if (u16NoisePower<=0xEAAC)//SNR>=13.6dB
          return 34;//
        else// if (u16NoisePower>=0xEAAC)//SNR<13.6dB
          return 33;//
    }
    else//QAM MODE
    {
          if( mode == QAM256 )//256QAM//SNR=10*log10((2720<<10)/noisepower)
        {
            if(!MSB1501_QAM_Main_Lock())
              return 0;//SNR=0;
            else if (u16NoisePower<=0x0117)//SNR>=40dB
              return 100;//
            else if (u16NoisePower<=0x0131)//SNR>=39.6dB
              return 99;//
            else if (u16NoisePower<=0x014F)//SNR>=39.2dB
              return 98;//
            else if (u16NoisePower<=0x016F)//SNR>=38.8dB
              return 97;//
            else if (u16NoisePower<=0x0193)//SNR>=38.4dB
              return 96;//
            else if (u16NoisePower<=0x01B9)//SNR>=38.0dB
              return 95;//
            else if (u16NoisePower<=0x01E4)//SNR>=37.6dB
              return 94;//
            else if (u16NoisePower<=0x0213)//SNR>=37.2dB
              return 93;//
            else if (u16NoisePower<=0x0246)//SNR>=36.8dB
              return 92;//
            else if (u16NoisePower<=0x027E)//SNR>=36.4dB
              return 91;//
            else if (u16NoisePower<=0x02BC)//SNR>=36.0dB
              return 90;//
            else if (u16NoisePower<=0x02FF)//SNR>=35.6dB
              return 89;//
            else if (u16NoisePower<=0x0349)//SNR>=35.2dB
              return 88;//
            else if (u16NoisePower<=0x039A)//SNR>=34.8dB
              return 87;//
            else if (u16NoisePower<=0x03F3)//SNR>=34.4dB
              return 86;//
            else if (u16NoisePower<=0x0455)//SNR>=34.0dB
              return 85;//
            else if (u16NoisePower<=0x04C0)//SNR>=33.6dB
              return 84;//
            else if (u16NoisePower<=0x0535)//SNR>=33.2dB
              return 83;//
            else if (u16NoisePower<=0x05B6)//SNR>=32.8dB
              return 82;//
            else if (u16NoisePower<=0x0643)//SNR>=32.4dB
              return 81;//
            else if (u16NoisePower<=0x06DD)//SNR>=32.0dB
              return 80;//
            else if (u16NoisePower<=0x0787)//SNR>=31.6dB
              return 79;//
            else if (u16NoisePower<=0x0841)//SNR>=31.2dB
              return 78;//
            else if (u16NoisePower<=0x090D)//SNR>=30.8dB
              return 77;//
            else if (u16NoisePower<=0x09EC)//SNR>=30.4dB
              return 76;//
            else if (u16NoisePower<=0x0AE1)//SNR>=30.0dB
              return 75;//
            else if (u16NoisePower<=0x0BEE)//SNR>=29.6dB
              return 74;//
            else if (u16NoisePower<=0x0D15)//SNR>=29.2dB
              return 73;//
            else if (u16NoisePower<=0x0E58)//SNR>=28.8dB
              return 72;//
            else if (u16NoisePower<=0x0FBA)//SNR>=28.4dB
              return 71;//
            else if (u16NoisePower<=0x113E)//SNR>=28.0dB
              return 70;//
            else if (u16NoisePower<=0x12E8)//SNR>=27.6dB
              return 69;//
            else if (u16NoisePower<=0x14BB)//SNR>=27.2dB
              return 68;//
            else if (u16NoisePower<=0x16BB)//SNR>=26.8dB
              return 67;//
            else if (u16NoisePower<=0x18ED)//SNR>=26.4dB
              return 66;//
            else if (u16NoisePower<=0x1B54)//SNR>=26.0dB
              return 65;//
            else if (u16NoisePower<=0x1DF7)//SNR>=25.6dB
              return 64;//
            else if (u16NoisePower<=0x20DB)//SNR>=25.2dB
              return 63;//
            else if (u16NoisePower<=0x2407)//SNR>=24.8dB
              return 62;//
            else if (u16NoisePower<=0x2781)//SNR>=24.4dB
              return 61;//
            else if (u16NoisePower<=0x2B50)//SNR>=24.0dB
              return 60;//
            else if (u16NoisePower<=0x2F7E)//SNR>=23.6dB
              return 59;//
            else if (u16NoisePower<=0x3413)//SNR>=23.2dB
              return 58;//
            else if (u16NoisePower<=0x3919)//SNR>=22.8dB
              return 57;//
            else if (u16NoisePower<=0x3E9C)//SNR>=22.4dB
              return 56;//
            else if (u16NoisePower<=0x44A6)//SNR>=22.0dB
              return 55;//
            else if (u16NoisePower<=0x4B45)//SNR>=21.6dB
              return 54;//
            else if (u16NoisePower<=0x5289)//SNR>=21.2dB
              return 53;//
            else if (u16NoisePower<=0x5A7F)//SNR>=20.8dB
              return 52;//
            else if (u16NoisePower<=0x633A)//SNR>=20.4dB
              return 51;//
            else if (u16NoisePower<=0x6CCD)//SNR>=20.0dB
              return 50;//
            else if (u16NoisePower<=0x774C)//SNR>=19.6dB
              return 49;//
            else if (u16NoisePower<=0x82CE)//SNR>=19.2dB
              return 48;//
            else if (u16NoisePower<=0x8F6D)//SNR>=18.8dB
              return 47;//
            else if (u16NoisePower<=0x9D44)//SNR>=18.4dB
              return 46;//
            else if (u16NoisePower<=0xAC70)//SNR>=18.0dB
              return 45;//
            else if (u16NoisePower<=0xBD13)//SNR>=17.6dB
              return 44;//
            else if (u16NoisePower<=0xCF50)//SNR>=17.2dB
              return 43;//
            else if (u16NoisePower<=0xE351)//SNR>=16.8dB
              return 42;//
            else if (u16NoisePower<=0xF93F)//SNR>=16.4dB
              return 41;//
            else// if (u16NoisePower>=0xF93F)//SNR<16.4dB
              return 40;//
        }
        else //if(mode&0x02==0x00)//64QAM//SNR=10*log10((2688<<10)/noisepower)
        {
            if(!MSB1501_QAM_Main_Lock())
              return 0;//SNR=0;
            else if (u16NoisePower<=0x0113)//SNR>=40dB
              return 100;//
            else if (u16NoisePower<=0x012E)//SNR>=39.6dB
              return 99;//
            else if (u16NoisePower<=0x014B)//SNR>=39.2dB
              return 98;//
            else if (u16NoisePower<=0x016B)//SNR>=38.8dB
              return 97;//
            else if (u16NoisePower<=0x018E)//SNR>=38.4dB
              return 96;//
            else if (u16NoisePower<=0x01B4)//SNR>=38.0dB
              return 95;//
            else if (u16NoisePower<=0x01DE)//SNR>=37.6dB
              return 94;//
            else if (u16NoisePower<=0x020C)//SNR>=37.2dB
              return 93;//
            else if (u16NoisePower<=0x023F)//SNR>=36.8dB
              return 92;//
            else if (u16NoisePower<=0x0277)//SNR>=36.4dB
              return 91;//
            else if (u16NoisePower<=0x02B3)//SNR>=36.0dB
              return 90;//
            else if (u16NoisePower<=0x02F6)//SNR>=35.6dB
              return 89;//
            else if (u16NoisePower<=0x033F)//SNR>=35.2dB
              return 88;//
            else if (u16NoisePower<=0x038F)//SNR>=34.8dB
              return 87;//
            else if (u16NoisePower<=0x03E7)//SNR>=34.4dB
              return 86;//
            else if (u16NoisePower<=0x0448)//SNR>=34.0dB
              return 85;//
            else if (u16NoisePower<=0x04B2)//SNR>=33.6dB
              return 84;//
            else if (u16NoisePower<=0x0525)//SNR>=33.2dB
              return 83;//
            else if (u16NoisePower<=0x05A5)//SNR>=32.8dB
              return 82;//
            else if (u16NoisePower<=0x0630)//SNR>=32.4dB
              return 81;//
            else if (u16NoisePower<=0x06C9)//SNR>=32.0dB
              return 80;//
            else if (u16NoisePower<=0x0770)//SNR>=31.6dB
              return 79;//
            else if (u16NoisePower<=0x0828)//SNR>=31.2dB
              return 78;//
            else if (u16NoisePower<=0x08F1)//SNR>=30.8dB
              return 77;//
            else if (u16NoisePower<=0x09CE)//SNR>=30.4dB
              return 76;//
            else if (u16NoisePower<=0x0AC1)//SNR>=30.0dB
              return 75;//
            else if (u16NoisePower<=0x0BCA)//SNR>=29.6dB
              return 74;//
            else if (u16NoisePower<=0x0CED)//SNR>=29.2dB
              return 73;//
            else if (u16NoisePower<=0x0E2D)//SNR>=28.8dB
              return 72;//
            else if (u16NoisePower<=0x0F8B)//SNR>=28.4dB
              return 71;//
            else if (u16NoisePower<=0x110A)//SNR>=28.0dB
              return 70;//
            else if (u16NoisePower<=0x12AF)//SNR>=27.6dB
              return 69;//
            else if (u16NoisePower<=0x147D)//SNR>=27.2dB
              return 68;//
            else if (u16NoisePower<=0x1677)//SNR>=26.8dB
              return 67;//
            else if (u16NoisePower<=0x18A2)//SNR>=26.4dB
              return 66;//
            else if (u16NoisePower<=0x1B02)//SNR>=26.0dB
              return 65;//
            else if (u16NoisePower<=0x1D9D)//SNR>=25.6dB
              return 64;//
            else if (u16NoisePower<=0x2078)//SNR>=25.2dB
              return 63;//
            else if (u16NoisePower<=0x239A)//SNR>=24.8dB
              return 62;//
            else if (u16NoisePower<=0x270A)//SNR>=24.4dB
              return 61;//
            else if (u16NoisePower<=0x2ACE)//SNR>=24.0dB
              return 60;//
            else if (u16NoisePower<=0x2EEF)//SNR>=23.6dB
              return 59;//
            else if (u16NoisePower<=0x3376)//SNR>=23.2dB
              return 58;//
            else if (u16NoisePower<=0x386D)//SNR>=22.8dB
              return 57;//
            else if (u16NoisePower<=0x3DDF)//SNR>=22.4dB
              return 56;//
            else if (u16NoisePower<=0x43D7)//SNR>=22.0dB
              return 55;//
            else if (u16NoisePower<=0x4A63)//SNR>=21.6dB
              return 54;//
            else if (u16NoisePower<=0x5190)//SNR>=21.2dB
              return 53;//
            else if (u16NoisePower<=0x596E)//SNR>=20.8dB
              return 52;//
            else if (u16NoisePower<=0x620F)//SNR>=20.4dB
              return 51;//
            else if (u16NoisePower<=0x6B85)//SNR>=20.0dB
              return 50;//
            else if (u16NoisePower<=0x75E5)//SNR>=19.6dB
              return 49;//
            else if (u16NoisePower<=0x8144)//SNR>=19.2dB
              return 48;//
            else if (u16NoisePower<=0x8DBD)//SNR>=18.8dB
              return 47;//
            else if (u16NoisePower<=0x9B6A)//SNR>=18.4dB
              return 46;//
            else if (u16NoisePower<=0xAA68)//SNR>=18.0dB
              return 45;//
            else if (u16NoisePower<=0xBAD9)//SNR>=17.6dB
              return 44;//
            else if (u16NoisePower<=0xCCE0)//SNR>=17.2dB
              return 43;//
            else if (u16NoisePower<=0xE0A4)//SNR>=16.8dB
              return 42;//
            else if (u16NoisePower<=0xF650)//SNR>=16.4dB
              return 41;//
            else// if (u16NoisePower>=0xF650)//SNR<16.4dB
              return 40;//
        }
    }
}
/***********************************************************************************
************************************************************************************/
S16 MSB1501_ReadFrequencyOffset(void)
{
    U8 mode;
    U8 u8PTK_LOOP_FF_R3, u8PTK_LOOP_FF_R2;
    U8 u8PTK_RATE_2;
    U8 u8AD_CRL_LOOP_VALUE0, u8AD_CRL_LOOP_VALUE1;
    U8 u8MIX_RATE_0, u8MIX_RATE_1, u8MIX_RATE_2;
    S16 PTK_LOOP_FF;
    S16 AD_CRL_LOOP_VALUE;
    S16 MIX_RATE;
    S16 FreqOffset;//kHz

    mode = MSB1501_Check8VSB64_256QAM();
//    MSB1501_ReadReg(0x8715, &u8NoisePowerH);//
//    if(MSB1501_WriteReg(0x873E, 0x00)==FALSE) return 0;// release freeze

    if( mode == VSB )//VSB mode//
    {
//        if(MSB1501_WriteReg(0x85E6, 0x01)==FALSE) return 0;// set freeze
        MSB1501_ReadReg(0x85A2, &u8PTK_LOOP_FF_R2);//
        MSB1501_ReadReg(0x85A3, &u8PTK_LOOP_FF_R3);//
//        if(MSB1501_WriteReg(0x85E6, 0x00)==FALSE) return 0;// release freeze
        PTK_LOOP_FF=u8PTK_LOOP_FF_R3<<8 | u8PTK_LOOP_FF_R2;
        FreqOffset=(float)-PTK_LOOP_FF*0.04768;
        MSB1501_ReadReg(0x8582, &u8PTK_RATE_2);//
        if (u8PTK_RATE_2==0x07)
          FreqOffset=FreqOffset-100;
        else if (u8PTK_RATE_2==0x08)
          FreqOffset=FreqOffset-500;
    }
    else//QAM MODE
    {
//        if(MSB1501_WriteReg(0x873E, 0x01)==FALSE) return 0;// set freeze
        MSB1501_ReadReg(0x8704, &u8AD_CRL_LOOP_VALUE0);//
        MSB1501_ReadReg(0x8705, &u8AD_CRL_LOOP_VALUE1);//
//        if(MSB1501_WriteReg(0x873E, 0x00)==FALSE) return 0;// release freeze
        AD_CRL_LOOP_VALUE=u8AD_CRL_LOOP_VALUE1<<8 | u8AD_CRL_LOOP_VALUE0;
        MSB1501_ReadReg(0x8502, &u8MIX_RATE_0);//
        MSB1501_ReadReg(0x8503, &u8MIX_RATE_1);//
        MSB1501_ReadReg(0x8504, &u8MIX_RATE_2);//
        MIX_RATE=u8MIX_RATE_2<<12|u8MIX_RATE_1<<4|u8MIX_RATE_0>>4;
          if( mode == QAM256 )//256QAM//
        {
          FreqOffset=(float)AD_CRL_LOOP_VALUE*0.0025561;//5.360537E6/2^21*1000
        }
        else //if(mode&0x02==0x00)//64QAM//
        {
          FreqOffset=(float)AD_CRL_LOOP_VALUE*0.00241134;//5.056941E6/2^21*1000
        }
        FreqOffset=FreqOffset+(float)(MIX_RATE-0x3D70)/2.62144;//(0.001/25*2^20/16)
    }
    return FreqOffset;
}


void MSB1501_FWVERSION(void)
{
   U8 data1;

   MSB1501_ReadReg(0x8095, &data1);
   MSB1501_DBINFO(printf("MSB1501FW_VERSION:%bd\n",data1));
}


/***********************************************************************************
************************************************************************************/
#undef _MSB1501_C_
