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

#include "Board.h"
#include "drvGlobal.h"
#include "drvISR.h"

#if (KEYPAD_TYPE_SEL != KEYPAD_TYPE_NONE) && \
    (KEYPAD_TYPE_SEL != KEYPAD_TYPE_BOARDDEP)

#define _MSKEYPAD_C_

#include "hwreg.h"
#include "msIR.h"
#include "msKeypad.h"
#include "msAPI_Timer.h"
#include "MsTypes.h"
#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"
#include "drvPM.h"
#include "SysInit.h"

#if( POWER_KEY_PAD_BY_INTERRUPT )

#endif

#define CheckWakeupKeyPad(x) ((x == IRKEY_POWER) ||             \
                              (x == IRKEY_CHANNEL_MINUS) ||     \
                              (x == IRKEY_CHANNEL_PLUS) ||      \
                              (x == IRKEY_INPUT_SOURCE))


//#define KeypadUnPressedTimerCount 7
//static U8 KeyPadCheckCount, PreviousCMD, PressKey;

#if KEYPAD_USE_ISR
//static U32 KeypadSuccessTime; //100 ms based
//BOOLEAN KeypadRepeatStart;
static U8 PreviousCMD;
#else
//static U8  PressKey;
extern U32 volatile g100msTimeCount;
#endif

extern U32 volatile g100msTimeCount;

static U8 Keypad_SAR0;
static U8 Keypad_SAR1;

#if( POWER_KEY_PAD_BY_INTERRUPT )
static U8 u8PwrKeypadIntFlag;
#endif

static U8 const tADCKeyLevel[] =
{
    ADC_KEY_L0,
    ADC_KEY_L1,
    ADC_KEY_L2,
    ADC_KEY_L3,
};


static U8 const tADCKey1Flag[] =
{
    ADC_KEY_1_L0_FLAG,
    ADC_KEY_1_L1_FLAG,
    ADC_KEY_1_L2_FLAG,
    ADC_KEY_1_L3_FLAG,
};

static U8 const tADCKey2Flag[] =
{
    ADC_KEY_2_L0_FLAG,
    ADC_KEY_2_L1_FLAG,
    ADC_KEY_2_L2_FLAG,
    ADC_KEY_2_L3_FLAG,
};

static PM_SarRegCfg   tSarRegCfg = \
{
    {LK_KEYPAD_CH1_UB, LK_KEYPAD_CH1_LB},
    {LK_KEYPAD_CH2_UB, LK_KEYPAD_CH2_LB},
    {LK_KEYPAD_CH3_UB, LK_KEYPAD_CH3_LB},
    {LK_KEYPAD_CH4_UB, LK_KEYPAD_CH4_LB}
};

static PM_SarParamCfg   tSarParamCfg = \
{
    {LK_CH_MINUS_UB, LK_CH_MINUS_LB},
    {LK_CH_PLUS_UB, LK_CH_PLUS_LB},
    {LK_INPUT_UB, LK_INPUT_LB},
    {LK_MENU_UB, LK_MENU_LB},
    {LK_OK_UB, LK_OK_LB},
    {LK_POWER_UB, LK_POWER_LB},
    {LK_VOL_MINUS_UB, LK_VOL_MINUS_LB},
    {LK_VOL_PLUS_UB, LK_VOL_PLUS_LB}
};

static void msKeypad_Isr(MHAL_SavedRegisters *pHalReg, U32 u32Data)
{
    UNUSED(pHalReg);
    UNUSED(u32Data);

    Keypad_SAR0 = MDrv_ReadByte(PM_SLEEP_REG_BASE+0x28);    // mailbox2
    Keypad_SAR1 = MDrv_ReadByte(PM_SLEEP_REG_BASE+0x29);    // mailbox2
}

void msKeypad_Init(void)
{
    Keypad_SAR0 = 0xFF;
    Keypad_SAR1 = 0xFF;

    // init PM_SLEEP local keypad
    MDrv_PM_KeypadInit(&tSarRegCfg, &tSarParamCfg);
    MDrv_PM_IrqAttach(E_PM_IRQ_SAR, (PM_IsrCb_Type)msKeypad_Isr, 0);
    MDrv_PM_IrqUnmask(E_PM_IRQ_SAR);
    //fix compile warning
    //PressKey = PressKey;
}

#if( POWER_KEY_PAD_BY_INTERRUPT )
U8 msKeypad_Get_PwrKey_IntFlag(void)
{
    return u8PwrKeypadIntFlag;
}

void msKeypad_Set_PwrKey_IntFlag(U8 u8Val)
{
    u8PwrKeypadIntFlag = u8Val;
}
#endif

/******************************************************************************/
///Keypad get ADC Channel value
///@param pkey \b IN ADC Channel
///@param pflag \b IN Pointer to the ADC Channel value
/******************************************************************************/
U8 msKeypad_Get_ADC_Channel(U8 Channel, U8 *pvalue)
{
    U8 u8Status = 0;

    switch ( Channel )
    {
        case KEYPAD_ADC_CHANNEL_1:
            *pvalue = MDrv_ReadByte(REG_SAR_ADCOUT1) & MASK_SAR_ADCOUT;
            break;
        case KEYPAD_ADC_CHANNEL_2:
            *pvalue = MDrv_ReadByte(REG_SAR_ADCOUT2) & MASK_SAR_ADCOUT;
            break;
        case KEYPAD_ADC_CHANNEL_3:
            *pvalue = MDrv_ReadByte(REG_SAR_ADCOUT3) & MASK_SAR_ADCOUT;
            break;
        case KEYPAD_ADC_CHANNEL_4:
            *pvalue = MDrv_ReadByte(REG_SAR_ADCOUT4) & MASK_SAR_ADCOUT;
             break;
        default:
            u8Status = 1;
            *pvalue = 0xFF;
            break;
    }

    return u8Status;
}

#if KEYPAD_USE_ISR
//this function will not check if key is pressed
static BOOLEAN msKeypad_IsKeyRepeat(U8 channelIdx)
{
    return (KEYPAD_LV_COUNT_CHANNEL[channelIdx]>KEYPAD_LV_STABLE_COUNT);
}

//modified by using ISR
BOOLEAN msKeypad_CH_GetKey(U8 *pkey, U8* pflag)
{
    U8  *Keymapping;
    U8 Channel;
    *pkey = 0xFF;
    *pflag = 0;



    //check if key pressed
    for (Channel=0; Channel<ADC_KEY_CHANNEL_NUM; Channel++)
    {
         if(KEYPAD_LV_CHANNEL[Channel]>0){
             break;
         }
    }


    if(Channel<ADC_KEY_CHANNEL_NUM)//Key pressed
    {
        //decide key map
        switch(Channel)
        {
            case KEYPAD_ADC_CHANNEL_1:
                Keymapping = tADCKey1Flag;
                break;
            case KEYPAD_ADC_CHANNEL_2:
                Keymapping = tADCKey2Flag;
                break;
            default:
                break;
        }

        //process key
        *pkey = *(Keymapping+(KEYPAD_LV_CHANNEL[Channel]-1));
        *pflag=msKeypad_IsKeyRepeat(Channel);
        KEYPAD_LV_CHANNEL[Channel]=0;//reset the buffer

        /*
        if(*pflag&&(g100msTimeCount-KeypadSuccessTime)<=KeypadRepeatTimerCount)
        {
            return FALSE;
        }

        KeypadSuccessTime=g100msTimeCount;
        */

        return TRUE;

    }
    else
    {
        return FALSE;
    }

}
#else

BOOLEAN msKeypad_CH_GetKey(U8 Channel, U8 *pkey, U8* pflag)
{
    #define Normal_KEYPAD_REPEAT_COUNT  250;
                               //           menu
    U16 KEYPAD_REPEAT_COUNT_CH1[6]={300,    500,    300,    300,    300,    300};
                               //           source
    U16 KEYPAD_REPEAT_COUNT_CH2[6]={300,    400,    300,    300,    300,    300};
    static U8 u8PreKeymapping;
    static U32 u32KeypadRepeatTimer;
    const U8 *Keymapping;

    U8 i,Key_Value,
    PressKey = FALSE;
    *pkey = 0xFF;
    *pflag = 0;

    switch(Channel)
    {
        case KEYPAD_ADC_CHANNEL_1:
            Key_Value = Keypad_SAR0;
            Keypad_SAR0 = 0xFF;
            Keymapping = tADCKey1Flag;
            break;

        case KEYPAD_ADC_CHANNEL_2:
            Key_Value = Keypad_SAR1;
            Keypad_SAR1 = 0xFF;
            Keymapping = tADCKey2Flag;
            break;

        default:
            return FALSE;
    }

    if(MsOS_GetSystemTime() > u32KeypadRepeatTimer)
    {
        u8PreKeymapping = 0xFF;
    }

    for(i=0; i<ADC_KEY_LEVEL; i++)
    {
        if(Key_Value < tADCKeyLevel[i])
        {
            PressKey = TRUE;
            *pkey = *(Keymapping + i);

            u32KeypadRepeatTimer = MsOS_GetSystemTime();

            if(u8PreKeymapping == *pkey)
            {
                *pflag = TRUE;
                u32KeypadRepeatTimer += Normal_KEYPAD_REPEAT_COUNT;
            }
            else
            {
                if(Channel == KEYPAD_ADC_CHANNEL_1)
                    u32KeypadRepeatTimer += KEYPAD_REPEAT_COUNT_CH1[i];
                else if(Channel == KEYPAD_ADC_CHANNEL_2)
                    u32KeypadRepeatTimer += KEYPAD_REPEAT_COUNT_CH2[i];
            }
            u8PreKeymapping = *pkey;

            return TRUE;
        }
    }
    return FALSE;
}

#endif

/******************************************************************************/
///Keypad get key value and repeat flag
///@param pkey \b IN return the key value(The same as Irda key value)
///@param pflag \b IN return the repeat flag(1:Repeat)
/******************************************************************************/
BOOLEAN msKeypad_GetKey(U8 *pkey, U8 *pflag)
{
    #if KEYPAD_USE_ISR

    // check PAD_WAKEUP / PAD_INT status
    if (!(MDrv_ReadByte(PM_PD) & (POWER_KEY_SEL == POWER_KEY_PAD_INT ? 0x20 : 0x10)))
    {
        *pkey = IRKEY_POWER;
        *pflag = 0;
        return TRUE;
    }

    return msKeypad_CH_GetKey(pkey, pflag);

    #else
             U8 Channel;

    // check PAD_WAKEUP / PAD_INT status
    /*if (!(MDrv_ReadByte(PM_PD) & (POWER_KEY_SEL == POWER_KEY_PAD_INT ? 0x20 : 0x10)))
    {
        *pkey = IRKEY_POWER;
        *pflag = 0;
        return TRUE;
    }*/
    for (Channel=0; Channel<ADC_KEY_CHANNEL_NUM; Channel++)
    {
            if (msKeypad_CH_GetKey(Channel, pkey, pflag))
           {
                 return TRUE;
           }
    }
           return FALSE;

    #endif

}



BOOLEAN msKeypad_CheckFactoryModeKey(void)
{
    U8 Channel,u8TwoKeyPressed=0;
    U8 u8Key,u8Flag;
    U8 u8Temp[2];

    for (Channel=0; Channel<ADC_KEY_CHANNEL_NUM; Channel++)
    {
        if (msKeypad_CH_GetKey(Channel, &u8Key, &u8Flag))
        {
            u8TwoKeyPressed++;
            u8Temp[Channel]=u8Key;

        }
    }
    if(u8TwoKeyPressed==2)
    {
        if(u8Temp[0]==IRKEY_UP&&u8Temp[1]==IRKEY_RIGHT)
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }

    }
    else
    {
        return FALSE;
    }
}



extern U8 KeypadCount, KeypadSamplePeriod;
BOOLEAN MDrv_Power_CheckPowerOnKeyPad(void)
{
    U8 KeypadCHValue;

 #if( POWER_KEY_PAD_BY_INTERRUPT )
    if(msKeypad_Get_PwrKey_IntFlag())
    {
        msKeypad_Set_PwrKey_IntFlag(FALSE);
        return TRUE;
    }
#endif

    KeypadSamplePeriod++;

    if(KeypadSamplePeriod > 20)
    {
        KeypadSamplePeriod = 0;
        KeypadCount = 0;
    }
    KeypadCHValue = MDrv_ReadByte(REG_SAR_ADCOUT1);

    if(CheckWakeupKeyPad(ADC_KEY_1_L0_FLAG))
    {
        if (KeypadCHValue <= ADC_KEY_L0)
            KeypadCount++;
    }
    if(CheckWakeupKeyPad(ADC_KEY_1_L1_FLAG))
    {
        if ((KeypadCHValue > ADC_KEY_L0) &&
            (KeypadCHValue <= ADC_KEY_L1))
            KeypadCount++;
    }
    if(CheckWakeupKeyPad(ADC_KEY_1_L2_FLAG))
    {
        if ((KeypadCHValue > ADC_KEY_L1) &&
            (KeypadCHValue <= ADC_KEY_L2))
            KeypadCount++;
    }
    if(CheckWakeupKeyPad(ADC_KEY_1_L3_FLAG))
    {
        if ((KeypadCHValue > ADC_KEY_L2) &&
            (KeypadCHValue <= ADC_KEY_L3))
            KeypadCount++;
    }

    KeypadCHValue = MDrv_ReadByte(REG_SAR_ADCOUT2);

    if(CheckWakeupKeyPad(ADC_KEY_2_L0_FLAG))
    {
        if (KeypadCHValue <= ADC_KEY_L0)
            KeypadCount++;
    }
    if(CheckWakeupKeyPad(ADC_KEY_2_L1_FLAG))
    {
        if ((KeypadCHValue > ADC_KEY_L0) &&
            (KeypadCHValue <= ADC_KEY_L1))
            KeypadCount++;
    }
    if(CheckWakeupKeyPad(ADC_KEY_2_L2_FLAG))
    {
        if ((KeypadCHValue > ADC_KEY_L1) &&
            (KeypadCHValue <= ADC_KEY_L2))
            KeypadCount++;
    }
    if(CheckWakeupKeyPad(ADC_KEY_2_L3_FLAG))
    {
        if ((KeypadCHValue > ADC_KEY_L2) &&
            (KeypadCHValue <= ADC_KEY_L3))
            KeypadCount++;
    }

    if(KeypadCount > 10)
        return TRUE;
    else
        return FALSE;
}

void msKeypad_ClearBuffer()
{
    U8 i;
    for(i=0;i<sizeof(KEYPAD_LV_CHANNEL);i++)
    {
        KEYPAD_LV_CHANNEL[i]=0;
    }
}

#undef _MSKEYPAD_C_

#else
static unsigned char u8Dummy; // keep ?CO?MSKEYPAD
#endif
