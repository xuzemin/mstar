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
#define _APP_GAMMAADJUST_C_
//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
// Common Definition
#include <string.h>
#include "MsCommon.h"
#include "Board.h"
#if ENABLE_GAMMA_ADJUST
// Common Definition
#include "MsCommon.h"
#include "apiXC.h"
// Driver
#include "drvPQ.h"
// API
#include "apiXC_Sys.h"
// APP
#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalFunction.h"
#include "MApp_GammaAdjust.h"
#include "MApp_XC_PQ.h"
#if (XC_BRINGUP == 1)
#include "color_reg.h"
#endif

#if FIXED_3D_SWITCH_PIC_MODE_GARBAGE
#include "MApp_GlobalVar.h"
#endif

#define DEBUG_GAMMA_ADJ(x) //x

extern BYTE *tAllGammaTab[3];
U16 NewGammaTab[3][Total_Entry]; 

void MApp_CaluculateNewGammaValue(EN_CAL_TYPE Cal_Type,U8 u8Channel, U8 GammaAdj ,U8 osdvalue)
{
  U8 u8Adj_Entry1,u8Adj_Entry2,u8Adj_Entry3;
  U16 u16Y1,u16Y2,u16Y3,u16Value;
  u16Value=u16Y1=u16Y2=u16Y3=0;
  switch(GammaAdj)                           //Entry1: min point to adjust                                              
  {                                          //Entry2: determine which point to adjust
                                             //Entry3: max point to adjust  
      case MS_GAMMAADJUST_5://5%
          u8Adj_Entry1=1-1;                                   //0%               
          u8Adj_Entry2=0.05*Total_Entry-1;                    //5%
          u8Adj_Entry3=((GammaAdj+1)*10/100.0)*Total_Entry-1; //10%
          break;
      case MS_GAMMAADJUST_10://10%              
          u8Adj_Entry1=0.05*Total_Entry-1;                    //5%                          
          u8Adj_Entry2=((GammaAdj*10)/100.0)*Total_Entry-1;   //10%
          u8Adj_Entry3=((GammaAdj+1)*10/100.0)*Total_Entry-1; //20%
          break;
      case MS_GAMMAADJUST_100://100%
          u8Adj_Entry1=((GammaAdj-1)*10/100.0)*Total_Entry-1;
          u8Adj_Entry2=((GammaAdj*10)/100.0)*Total_Entry-1;
          u8Adj_Entry3=((GammaAdj*10)/100.0)*Total_Entry-1;
          break;
      default:
          u8Adj_Entry1=((GammaAdj-1)*10/100.0)*Total_Entry-1;
          u8Adj_Entry2=((GammaAdj*10)/100.0)*Total_Entry-1;
          u8Adj_Entry3=((GammaAdj+1)*10/100.0)*Total_Entry-1;
          break;
  }
  
          DEBUG_GAMMA_ADJ(printf("\ru8Adj_Entry1=%d\n",u8Adj_Entry1));
          DEBUG_GAMMA_ADJ(printf("\ru8Adj_Entry2=%d\n",u8Adj_Entry2));
          DEBUG_GAMMA_ADJ(printf("\ru8Adj_Entry3=%d\n",u8Adj_Entry3));
          
    if(Cal_Type==EN_UI_ADJUST)
    {
      u16Y1=NewGammaTab[u8Channel][u8Adj_Entry1];
      u16Y3=NewGammaTab[u8Channel][u8Adj_Entry3];

      if(osdvalue==50) 
      {
             u16Y2=MApp_Get_ValueFromGammaTab(u8Channel,MApp_Get_EntryIdx(u8Adj_Entry2+1));
         if((stGenSetting.g_GammaSetting.u8Gain==MS_GAMMAADJUST_MIN)||
            (stGenSetting.g_GammaSetting.GammaAdjOSDValue[u8Channel][stGenSetting.g_GammaSetting.u8Gain-1]==50))
         {
            MApp_RestoreToDefaultGammaCurve(u8Channel,u8Adj_Entry1,u8Adj_Entry2);
         }
         if(stGenSetting.g_GammaSetting.GammaAdjOSDValue[u8Channel][stGenSetting.g_GammaSetting.u8Gain+1]==50)
         {
            MApp_RestoreToDefaultGammaCurve(u8Channel,u8Adj_Entry2,u8Adj_Entry3);
         }
      }
      else
      {
         u16Value=MApp_Get_ValueFromGammaTab(u8Channel,MApp_Get_EntryIdx(u8Adj_Entry2+1));
         u16Y2=MApp_CalculateAdjSteps(osdvalue,u16Value); //calculate new value after adjustment
         MApp_CalculateNewGammaCurve(u8Channel,u8Adj_Entry1,u16Y1,u8Adj_Entry2,u16Y2);
         if(stGenSetting.g_GammaSetting.u8Gain!=MS_GAMMAADJUST_MAX)
         {
            MApp_CalculateNewGammaCurve(u8Channel,u8Adj_Entry2,u16Y2,u8Adj_Entry3,u16Y3);
         }
      }      
        MApi_XC_Gamma_Set_Value(u8Channel,u8Adj_Entry2,u16Y2); //load (X2,Y2)
        NewGammaTab[u8Channel][u8Adj_Entry2]= u16Y2;           //save (X2,Y2)
        
    }//EN_UI_ADJUST
    else if(Cal_Type==EN_INIT)
    {
      if(osdvalue==50) 
      {
        if(GammaAdj==MS_GAMMAADJUST_MIN)
        {
           //do nothing
        }
        else
        {
           if(stGenSetting.g_GammaSetting.GammaAdjOSDValue[u8Channel][GammaAdj-1]==50) //check pre-GammaAdj osd value
           {
              //do nothing
           }
           else
           {
              u16Y1=NewGammaTab[u8Channel][u8Adj_Entry1]; 
              u16Y2=NewGammaTab[u8Channel][u8Adj_Entry2];
              MApp_CalculateNewGammaCurve(u8Channel,u8Adj_Entry1,u16Y1,u8Adj_Entry2,u16Y2);
           }
        }
      }
      else
      {   
          u16Y1=NewGammaTab[u8Channel][u8Adj_Entry1]; 
          u16Value=NewGammaTab[u8Channel][u8Adj_Entry2];
          u16Y2=MApp_CalculateAdjSteps(osdvalue,u16Value); //calculate new value after adjustment
          NewGammaTab[u8Channel][u8Adj_Entry2]=u16Y2;              //save (X2,Y2)
          MApi_XC_Gamma_Set_Value(u8Channel,u8Adj_Entry2,u16Y2); //load (X2,Y2)
          MApp_CalculateNewGammaCurve(u8Channel,u8Adj_Entry1,u16Y1,u8Adj_Entry2,u16Y2);
      }
    }//Cal_Type

    DEBUG_GAMMA_ADJ(printf("\r[Gamma_Debug](%d,0x%x),(%d,0x%x),(%d,0x%x)\n",u8Adj_Entry1,u16Y1,u8Adj_Entry2,u16Y2,u8Adj_Entry3,u16Y3));

}

//==============================================================
//get the index of entry in gamma table
//==============================================================
U16 MApp_Get_EntryIdx(U16 u16Adj_Entry) 
{
  U16 u16Entry_Idx;
  
  if(u16Adj_Entry%2!=0)
  {
    u16Entry_Idx=(u16Adj_Entry/2+1)*3-2;
  }
  else
  {
    u16Entry_Idx=(u16Adj_Entry/2)*3-1;
  }

  return u16Entry_Idx;
}

//==============================================================
//get gamma value from default gamma table
//==============================================================
U16 MApp_Get_ValueFromGammaTab(U8 channel,U16 u16Entry_Idx)
{
    U16 u16Value=0;
    if(u16Entry_Idx%3==1)
    {
        u16Value=(tAllGammaTab[channel][u16Entry_Idx]<<4)|(tAllGammaTab[channel][u16Entry_Idx-1]&0x0f);
    }
    else if((u16Entry_Idx%3==2))
    {
        u16Value=(tAllGammaTab[channel][u16Entry_Idx]<<4)|(tAllGammaTab[channel][u16Entry_Idx-2]>>4);
    }
    DEBUG_GAMMA_ADJ(printf("\rGamma Value=0x%x\n",u16Value));
    return u16Value;
}

//==============================================================
//calculate new gamma value after UI adjustment
//==============================================================
U16 MApp_CalculateAdjSteps(U8 osdvalue,U16 u16Value) 
{
    U16 u16NewGamma;
    if(osdvalue>50)
    {
        u16NewGamma = (u16Value)+(Gamma_Step*16*(osdvalue-50));
        if(u16NewGamma>0xFFF)
        {
           u16NewGamma = 0xFFF;
        }
    }
    else
    {
       if((Gamma_Step*16*(50-osdvalue))>u16Value)
       {
          u16NewGamma = u16Value;
       }
       else
       {
          u16NewGamma = (u16Value)-(Gamma_Step*16*(50-osdvalue));
       }
    }
    DEBUG_GAMMA_ADJ(printf("\r[UI_Adjust]u16NewGamma=0x%x\n",u16NewGamma));
    return u16NewGamma;
}

void MApp_LoadNewGammaTable(void)
{
    U8 i,gamma_adj;
    U16 entry;
    for(i=0;i<3;i++) //copy old gamma table to new table
    {   
        for(entry=1;entry<=Total_Entry;entry++)
        {
            NewGammaTab[i][entry-1]=MApp_Get_ValueFromGammaTab(i,MApp_Get_EntryIdx(entry));
        }   
    }

    for(i=0;i<3;i++) //load new gamma curve by UI setting
    {
        for(gamma_adj=0;gamma_adj<GAMMA_ADJUST_NUM;gamma_adj++)
        {
            MApp_CaluculateNewGammaValue(EN_INIT,i,gamma_adj,stGenSetting.g_GammaSetting.GammaAdjOSDValue[i][gamma_adj]);
        }
    }

/*debug*/
#if 0
    int a;
    for(a=0;a<256;a++)
    {
        if(a==0)
        printf("[");
        if(a%9==0)
        printf("\n");   
        printf("0x%02x ",NewGammaTab[0][a]);
        if(a==255)
        printf("]\n");
    }
#endif
}

//==============================================================
//calculate new gamma curve and load new gamma curve
//==============================================================
void MApp_CalculateNewGammaCurve(U8 channel,U16 X1,U16 Y1,U16 X2,U16 Y2) 
{
    U8 i;
    U16 NewGammaValue;
    for(i=X1+1;i<X2;i++) //calculate (X1,Y1)to(X2,Y2) by linear interpolation formula
    {
        NewGammaValue=(((float)(i-X2)*(float)(Y1/16.0)/(float)(X1-X2))+((float)(i-X1)*(float)(Y2/16.0)/(float)(X2-X1)))*16;
        DEBUG_GAMMA_ADJ(printf("\r[%d]NewGammaValue=0x%x\n",i,NewGammaValue));
        
        MApi_XC_Gamma_Set_Value(channel, i, NewGammaValue); //load (X1,Y1)to(X2,Y2)new gamma curve
        NewGammaTab[channel][i]= NewGammaValue;             //save (X1,Y1)to(X2,Y2)
    }
}

void MApp_RestoreToDefaultGammaCurve(U8 channel,U16 X1,U16 X2)
{
    U8 i;
    for(i=X1+1;i<X2;i++)
    {
      NewGammaTab[channel][i]=MApp_Get_ValueFromGammaTab(channel,MApp_Get_EntryIdx(i+1));
      MApi_XC_Gamma_Set_Value(channel,i,NewGammaTab[channel][i]);
    }
}

#endif
#undef _APP_GAMMAADJUST_C_

