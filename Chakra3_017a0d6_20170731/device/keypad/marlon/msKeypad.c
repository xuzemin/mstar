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

#define CheckWakeupKeyPad(x) ((x == IRKEY_POWER) ||             \
                              (x == IRKEY_CHANNEL_MINUS) ||     \
                              (x == IRKEY_CHANNEL_PLUS) ||      \
                              (x == IRKEY_INPUT_SOURCE))


#if KEYPAD_USE_ISR
#include "MApp_Key.h"

static MS_S32 u32Mutex_Keypad = 0;
static MS_BOOL bBlockKeypadIsr = FALSE;
#define msKeypad_InitLock()     {\
                            u32Mutex_Keypad = OS_CREATE_MUTEX(KEYPAD);\
                            if(u32Mutex_Keypad<0) printf("!!!Acquire Send Mutex for Keypad Failed!\n");\
                            }
#define msKeypad_DeInitLock()   OS_DELETE_MUTEX(u32Mutex_Keypad)
#define msKeypad_Lock()         OS_OBTAIN_MUTEX(u32Mutex_Keypad, MSOS_WAIT_FOREVER)
#define msKeypad_UnLock()       OS_RELEASE_MUTEX(u32Mutex_Keypad)

static U8 g_u8KeypadKey = 0xFF;
static U8 g_u8KeypadRpt = 0;
static BOOLEAN g_u8KeypadRes=MSRET_ERROR;
static void MDrv_Keypad_Isr(MHAL_SavedRegisters *pHalReg, U32 u32Data);
static BOOLEAN msKeypad_CH_GetKey(U8 Channel, U8 *pkey, U8* pflag);
#endif

static U16 KeyPadCheckCount;
static U8 PreviousCMD, PressKey;
static U32 KeyPadTimePeriod;
extern U32 volatile g100msTimeCount;

extern U32 volatile g100msTimeCount;

static U8 Keypad_SAR0;
static U8 Keypad_SAR1;

#if( POWER_KEY_PAD_BY_INTERRUPT )
static U8 u8PwrKeypadIntFlag;
#endif

//Currently Only Support 2 Channel Keypad
static U8 Keypad_Channel[ADC_KEY_CHANNEL_NUM];
static U8 const tADCKeyLevel[ADC_KEY_CHANNEL_NUM][8] =
{
    {   ADC_KEY_1_L0,
        ADC_KEY_1_L1,
        ADC_KEY_1_L2,
        ADC_KEY_1_L3,
        ADC_KEY_1_L4,
        ADC_KEY_1_L5,
        ADC_KEY_1_L6,
        ADC_KEY_1_L7
    },

  #if (ADC_KEY_CHANNEL_NUM > 1)
    {
        ADC_KEY_2_L0,
        ADC_KEY_2_L1,
        ADC_KEY_2_L2,
        ADC_KEY_2_L3,
        ADC_KEY_2_L4,
        ADC_KEY_2_L5,
        ADC_KEY_2_L6,
        ADC_KEY_2_L7
    }
  #endif
};

static U8 const tADCKeyFlag[ADC_KEY_CHANNEL_NUM][8] =
{
    {
        ADC_KEY_1_L0_FLAG,
        ADC_KEY_1_L1_FLAG,
        ADC_KEY_1_L2_FLAG,
        ADC_KEY_1_L3_FLAG,
        ADC_KEY_1_L4_FLAG,
        ADC_KEY_1_L5_FLAG,
        ADC_KEY_1_L6_FLAG,
        ADC_KEY_1_L7_FLAG
    },

  #if (ADC_KEY_CHANNEL_NUM > 1)
    {
        ADC_KEY_2_L0_FLAG,
        ADC_KEY_2_L1_FLAG,
        ADC_KEY_2_L2_FLAG,
        ADC_KEY_2_L3_FLAG,
        ADC_KEY_2_L4_FLAG,
        ADC_KEY_2_L5_FLAG,
        ADC_KEY_2_L6_FLAG,
        ADC_KEY_2_L7_FLAG
    }
  #endif
};

static BOOLEAN msKeypad_AllocChan(U8 u8KpdCh)
{
    static U8 u8KpdChIdx=0;

    if(u8KpdChIdx>=ADC_KEY_CHANNEL_NUM)
    {
        printf("[msKeypad_Init]: Allocated channel number > %d !!!\n",ADC_KEY_CHANNEL_NUM);
        return MSRET_ERROR;
    }
    Keypad_Channel[u8KpdChIdx++]=u8KpdCh;
    return MSRET_OK;
}

static U8 msKeypad_GetChanIndex(U8 u8KpdCh)
{
    U8 k;

    for(k=0;k<ADC_KEY_CHANNEL_NUM;k++)
    {
        if(Keypad_Channel[k]==u8KpdCh)
            return k;
    }
    return 0xFF;
}

void msKeypad_Init(void)
{
    Keypad_SAR0 = 0xFF;
    Keypad_SAR1 = 0xFF;

  #if(ENABLE_KPDCHAN_1==ENABLE)//channel 1
    MDrv_Write2Byte(REG_SAR1_UPB, KEYPAD_CH1_UB<<2);
    MDrv_Write2Byte(REG_SAR1_LOB, KEYPAD_CH1_LB<<2);
    msKeypad_AllocChan(KEYPAD_ADC_CHANNEL_1);
  #endif

  #if(ENABLE_KPDCHAN_2==ENABLE)//channel 2
    MDrv_Write2Byte(REG_SAR2_UPB, KEYPAD_CH2_UB<<2);
    MDrv_Write2Byte(REG_SAR2_LOB, KEYPAD_CH2_LB<<2);
    msKeypad_AllocChan(KEYPAD_ADC_CHANNEL_2);
  #endif

  #if(ENABLE_KPDCHAN_3==ENABLE)//channel 3
    MDrv_Write2Byte(REG_SAR3_UPB, KEYPAD_CH3_UB<<2);
    MDrv_Write2Byte(REG_SAR3_LOB, KEYPAD_CH3_LB<<2);
    msKeypad_AllocChan(KEYPAD_ADC_CHANNEL_3);
  #endif

  #if(ENABLE_KPDCHAN_4==ENABLE)//channel 4
    MDrv_Write2Byte(REG_SAR4_UPB, KEYPAD_CH4_UB<<2);
    MDrv_Write2Byte(REG_SAR4_LOB, KEYPAD_CH4_LB<<2);
    msKeypad_AllocChan(KEYPAD_ADC_CHANNEL_4);
  #endif

    MDrv_WriteByte(REG_SAR_CTRL0, (SAR_MODE_FREERUN|SAR_SIGNAL_CH));
    MDrv_WriteByte(REG_SAR_CTRL0, MDrv_ReadByte(REG_SAR_CTRL0)&(~SAR_DIGITAL_PWRDN));
    MDrv_WriteByte(REG_SAR_CTRL1, MDrv_ReadByte(REG_SAR_CTRL1)&(~SAR_ADC_PWRDN));
    MDrv_WriteByte(REG_SAR_CTRL1, MDrv_ReadByte(REG_SAR_CTRL1)|(SAR_ADC_FREERUN));
    MDrv_WriteByte(REG_SAR_SELCH, MDrv_ReadByte(REG_SAR_SELCH)|(SAR_NCH_EN));
    MDrv_WriteByte(REG_SAR_CKSAMP_PRD, 0x05);   //sample period

    //(1) select pad as analog input
    MDrv_WriteRegBit(REG_SAR_AISEL, (ENABLE_KPDCHAN_1==ENABLE)? ENABLE : DISABLE, (ENABLE_KPDCHAN_1==ENABLE)? SAR_AISEL_CH0 : 0);
    MDrv_WriteRegBit(REG_SAR_AISEL, (ENABLE_KPDCHAN_2==ENABLE)? ENABLE : DISABLE, (ENABLE_KPDCHAN_2==ENABLE)? SAR_AISEL_CH1 : 0);
    MDrv_WriteRegBit(REG_SAR_AISEL, (ENABLE_KPDCHAN_3==ENABLE)? ENABLE : DISABLE, (ENABLE_KPDCHAN_3==ENABLE)? SAR_AISEL_CH2 : 0);
    MDrv_WriteRegBit(REG_SAR_AISEL, (ENABLE_KPDCHAN_4==ENABLE)? ENABLE : DISABLE, (ENABLE_KPDCHAN_4==ENABLE)? SAR_AISEL_CH3 : 0);
    //(2) select pad direction as input mode
    MDrv_WriteRegBit(REG_SAR_GPIOOEN, (ENABLE_KPDCHAN_1==ENABLE)? ENABLE : DISABLE, (ENABLE_KPDCHAN_1==ENABLE)? SAR_GPIOOEN_CH0 : 0);
    MDrv_WriteRegBit(REG_SAR_GPIOOEN, (ENABLE_KPDCHAN_2==ENABLE)? ENABLE : DISABLE, (ENABLE_KPDCHAN_2==ENABLE)? SAR_GPIOOEN_CH1 : 0);
    MDrv_WriteRegBit(REG_SAR_GPIOOEN, (ENABLE_KPDCHAN_3==ENABLE)? ENABLE : DISABLE, (ENABLE_KPDCHAN_3==ENABLE)? SAR_GPIOOEN_CH2 : 0);
    MDrv_WriteRegBit(REG_SAR_GPIOOEN, (ENABLE_KPDCHAN_4==ENABLE)? ENABLE : DISABLE, (ENABLE_KPDCHAN_4==ENABLE)? SAR_GPIOOEN_CH3 : 0);
    //(3) un-mask sar interrupt mask
    MDrv_WriteRegBit(REG_SAR_CH_INT_MASK, (ENABLE_KPDCHAN_1==ENABLE)? DISABLE : ENABLE, SAR_INT_MSK_CH0);
    MDrv_WriteRegBit(REG_SAR_CH_INT_MASK, (ENABLE_KPDCHAN_2==ENABLE)? DISABLE : ENABLE, SAR_INT_MSK_CH1);
    MDrv_WriteRegBit(REG_SAR_CH_INT_MASK, (ENABLE_KPDCHAN_3==ENABLE)? DISABLE : ENABLE, SAR_INT_MSK_CH2);
    MDrv_WriteRegBit(REG_SAR_CH_INT_MASK, (ENABLE_KPDCHAN_4==ENABLE)? DISABLE : ENABLE, SAR_INT_MSK_CH3);
    //(4) enable/diable high channel
    //MDrv_WriteRegBit(REG_SAR_SELCH, ENABLE, SAR_NCH_EN);

  #if KEYPAD_USE_ISR
    //hook isr for pm_sleep
    MsOS_AttachInterrupt(E_INT_IRQ_PMSLEEP, (InterruptCb)MDrv_Keypad_Isr);
    //enable interrupt
    MsOS_EnableInterrupt(E_INT_IRQ_PMSLEEP);
    //un-mask sar wakeup event for pm_sleep
    MDrv_WriteRegBit(REG_PM_WK_IRQ_MSK, DISABLE, PM_WK_IRQ_SAR);
    //clear interrupt
    MDrv_WriteRegBit(REG_SAR_INT_CLR, ENABLE, SAR_INT_CLR_ALL);
    MDrv_WriteRegBit(REG_SAR_INT_CLR, DISABLE, SAR_INT_CLR_ALL);
    //sw pack for new irq structure //IMPORTANT!!!
    MDrv_WriteRegBit(REG_SAR_SW_PACK, ENABLE, SAR_IRQ_CTRL);
    //create mutex
    if(u32Mutex_Keypad<=0)
    {
        msKeypad_InitLock();
    }
  #endif

    printf("\nKeypad Initialize OK\n");
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

    MDrv_WriteRegBit(REG_SAR_CTRL1, 1, SAR_LOAD_EN);
    switch ( Channel )
    {
        case KEYPAD_ADC_CHANNEL_1:
            *pvalue = (MDrv_Read2Byte(REG_SAR_ADCOUT1) & MASK_SAR_ADCOUT)>>2;
            break;
        case KEYPAD_ADC_CHANNEL_2:
            *pvalue = (MDrv_Read2Byte(REG_SAR_ADCOUT2) & MASK_SAR_ADCOUT)>>2;
            break;
        case KEYPAD_ADC_CHANNEL_3:
            *pvalue = (MDrv_Read2Byte(REG_SAR_ADCOUT3) & MASK_SAR_ADCOUT)>>2;
            break;
        case KEYPAD_ADC_CHANNEL_4:
            *pvalue = (MDrv_Read2Byte(REG_SAR_ADCOUT4) & MASK_SAR_ADCOUT)>>2;
             break;
        case KEYPAD_ADC_CHANNEL_5:
            *pvalue = (MDrv_Read2Byte(REG_SAR_ADCOUT5) & MASK_SAR_ADCOUT)>>2;
            break;
        case KEYPAD_ADC_CHANNEL_6:
            *pvalue = (MDrv_Read2Byte(REG_SAR_ADCOUT6) & MASK_SAR_ADCOUT)>>2;
            break;
        case KEYPAD_ADC_CHANNEL_7:
            *pvalue = (MDrv_Read2Byte(REG_SAR_ADCOUT7) & MASK_SAR_ADCOUT)>>2;
            break;
        case KEYPAD_ADC_CHANNEL_8:
            *pvalue = (MDrv_Read2Byte(REG_SAR_ADCOUT8) & MASK_SAR_ADCOUT)>>2;
             break;
        default:
            u8Status = 1;
            *pvalue = 0xFF;
            break;
    }

    return u8Status;
}

#if KEYPAD_USE_ISR
#define KEYPAD_STABLE_MULTIPLE          50
#define KEYPAD_DELAY_PARAM              200//100 //This parameter is very important for timing!!!
#define KEYPAD_ISR_STABLE_NUM           (KEYPAD_STABLE_NUM * KEYPAD_STABLE_MULTIPLE)
#define KEYPAD_ISR_STABLE_NUM_MIN       (KEYPAD_STABLE_NUM_MIN * KEYPAD_STABLE_MULTIPLE)
#define KEYPAD_ISR_KEY_VALIDATION       (KEYPAD_KEY_VALIDATION + 500)
#define KEYPAD_ISR_REPEAT_KEY_CHECK     (KEYPAD_ISR_KEY_VALIDATION + 2)
#define KEYPAD_ISR_REPEAT_KEY_CHECK_1   (KEYPAD_ISR_KEY_VALIDATION + 3)
#define KEYPAD_ISR_REPEAT_PERIOD        (KEYPAD_REPEAT_PERIOD)
#define KEYPAD_ISR_REPEAT_PERIOD_1      (KEYPAD_REPEAT_PERIOD_1)

static BOOLEAN msKeypad_GetKeyCodeISR(U8 *pkey, U8 *pflag)
{
    U8 u8KeypadRes;
    U8 Channel;

    for (Channel=0; Channel<KEYPAD_CHANNEL_SUPPORT; Channel++)
    {
        u8KeypadRes = msKeypad_CH_GetKey(Channel, pkey, pflag);
        if (u8KeypadRes != MSRET_ERROR)
        {
            return u8KeypadRes;
        }
    }
    return MSRET_ERROR;
}

static void MDrv_Keypad_Isr(MHAL_SavedRegisters *pHalReg, U32 u32Data)
{
    MS_U8 u8KeypadKey=0xFF;
    MS_U8 u8KeypadRpt=0;
    BOOLEAN u8KeypadRes=MSRET_ERROR;

    UNUSED(pHalReg);
    UNUSED(u32Data);

    //printf("MDrv_Keypad_Isr>>> IN\n");
    //##########################
    //
    // Processing current interrupt
    // Get keypad key code + repeat status
    //
    if(bBlockKeypadIsr == FALSE)
    {
    u8KeypadRes = msKeypad_GetKeyCodeISR(&u8KeypadKey,&u8KeypadRpt);
        msKeypad_Lock();    //No effect in non-os, replace by bBlockKeypadIsr flag
    //if(u8KeypadRes==MSRET_OK)
    if(u8KeypadRes!=MSRET_ERROR)
    {
        g_u8KeypadKey = (u8KeypadRes)? u8KeypadKey : 0xFF;
        g_u8KeypadRpt = (u8KeypadRes)? u8KeypadRpt : 0;
        g_u8KeypadRes = u8KeypadRes;
    }
    else
    {
        g_u8KeypadRes = u8KeypadRes;
    }
        msKeypad_UnLock();    //No effect in non-os, replace by bBlockKeypadIsr flag
    }
    //else
    //{
    //    printf("\n\rBlocked!");
    //}

    //##########################
    //
    // Processing next interrupt
    //
    if(u8KeypadRes!=MSRET_ERROR)
    {
        //enable interrupt after get key routine if  result<>MSRET_ERROR
        //Not to clear interrupt to let SAR generate continuous interrupts
        #if 0
        if(u8KeypadRes==MSRET_OK)
            printf("MDrv_Keypad_Isr>>> OK\n");
        else
            printf("MDrv_Keypad_Isr>>> OTHER\n");
        #endif
    }
    else
    {
        //enable interrupt
        MsOS_EnableInterrupt(E_INT_IRQ_PMSLEEP);
        //clear interrupt
        MDrv_WriteRegBit(REG_SAR_INT_CLR, ENABLE, SAR_INT_CLR_ALL);
        MDrv_WriteRegBit(REG_SAR_INT_CLR, DISABLE, SAR_INT_CLR_ALL);
        #if 0
        printf("MDrv_Keypad_Isr>>> ERROR\n");
        #endif
    }

}

static void msKeypad_DelayTime(U32 u32Us)
{
    // volatile is necessary to avoid optimization
    MS_U32 volatile u32Dummy = 0;
    //MS_U32 u32Loop;
    MS_U32 volatile u32Loop;

    u32Loop = (MS_U32)(50 * u32Us);
    while (u32Loop-- > 0)
    {
        u32Dummy++;
    }
}

static BOOLEAN msKeypad_CH_GetKey(U8 Channel, U8 *pkey, U8* pflag)
{
    U16 i, KEY_LV[ADC_KEY_LEVEL];
    U8 j, Key_Value, *Keymapping=NULL;
    U8 u8ChIdx=0;
    U8 u8CHLVLs[KEYPAD_CHANNEL_SUPPORT]={ADC_CH1_LEVELS,ADC_CH2_LEVELS,ADC_CH3_LEVELS,ADC_CH4_LEVELS};

    *pkey = 0xFF;
    *pflag = 0;

    msKeypad_DelayTime(KEYPAD_DELAY_PARAM); //IMPORTANT!!!

#if( POWER_KEY_PAD_BY_INTERRUPT )
    if (u8PwrKeypadIntFlag){
        u8PwrKeypadIntFlag = FALSE;
        *pkey = IRKEY_POWER;
        return MSRET_OK;
    }
#endif

    for(i=0; i<ADC_KEY_LEVEL; i++)
        KEY_LV[i] = 0;

    u8ChIdx = msKeypad_GetChanIndex(Channel);
    if(u8ChIdx<ADC_KEY_CHANNEL_NUM)
        Keymapping = (U8*)tADCKeyFlag[u8ChIdx];
    else
        return MSRET_ERROR;
    for ( i = 0; i < (KEYPAD_ISR_STABLE_NUM); i++ )
    {
        msKeypad_Get_ADC_Channel(Channel,&Key_Value);
        for (j=0;j<u8CHLVLs[Channel];j++)
        {
            if (Key_Value < tADCKeyLevel[u8ChIdx][j])
            {
                KEY_LV[j]++;
                break;
            }
        }
    }

    for(i=0; i<u8CHLVLs[Channel]; i++)
    {
        if(KEY_LV[i] >= (KEYPAD_STABLE_NUM_MIN*KEYPAD_STABLE_MULTIPLE))
        {
            PressKey = TRUE;
            *pkey = *(Keymapping+i);
            //printf("CH[%d]=%02X\n",Channel,*pkey);
//Only First press and repeat key are regarded as valid key
//First key: The first time when [No key to some key] or [A key to B key]
//Repeat key: Keep pressing some key and keep for >=KEYPAD_REPEAT_PERIOD
//
//At first, we count times to decide enter repeat key detecting mode or not
//After entering repeat key detecting mode, we check duration KEYPAD_REPEAT_PERIOD
//to send first repeat key, and in the following every 100ms
//will send one valid repeat key to upper layer
//
//KEYPAD_ISR_KEY_VALIDATION: Start to calculate time for checking repeat key
//For single key case, running sequence is CASE 0->A
//For repeat key case, running sequence is CASE 0->A->B->C->D->E->E->E->E->E

            if (PreviousCMD != *pkey)   //Key change detected
            {   //CASE 0
                PreviousCMD = *pkey;
                KeyPadCheckCount = 0;
                KeyPadTimePeriod = g100msTimeCount;
                return MSRET_OK;
            }
            else    //Keep same key period
            {
                if (KeyPadCheckCount < KEYPAD_ISR_KEY_VALIDATION)
                {
                    //CASE A
                    KeyPadCheckCount++;
                    return MSRET_OTHER;
                }
                else if (KeyPadCheckCount == KEYPAD_ISR_KEY_VALIDATION)
                {
                    //CASE B    Enter repeat key detecting mode
                    KeyPadCheckCount++;
                    KeyPadTimePeriod = g100msTimeCount;
                    //*pflag = 0x01;
                    return MSRET_OTHER;
                }

                if (KeyPadCheckCount == KEYPAD_ISR_REPEAT_KEY_CHECK)    //3+2
                {
                    //CASE D    First repeat key, long period from first key
                    if (g100msTimeCount > KeyPadTimePeriod + KEYPAD_ISR_REPEAT_PERIOD_1)
                    {
                        KeyPadTimePeriod = g100msTimeCount;
                        KeyPadCheckCount = KEYPAD_ISR_REPEAT_KEY_CHECK_1;
                        *pflag = 0x01;
                        return MSRET_OK;
                    }
                    else
                    {
                        *pkey = 0xFF;
                        *pflag = 0x01;
                        return MSRET_OTHER;
                    }
                    //return MSRET_OK;
                }
                else if (KeyPadCheckCount == KEYPAD_ISR_REPEAT_KEY_CHECK_1) //3+3
                {
                    //CASE E    Second and following repeat key, 100ms from previous repeat key
                    if (g100msTimeCount > KeyPadTimePeriod)
                    {
                        KeyPadTimePeriod = g100msTimeCount;
                        KeyPadCheckCount = KEYPAD_ISR_REPEAT_KEY_CHECK_1;
                        *pflag = 0x01;
                        return MSRET_OK;
                    }
                    else
                    {
                        *pkey = 0xFF;
                        *pflag = 0x01;
                        return MSRET_OTHER;
                    }
                    //return MSRET_OK;
                }

                if (g100msTimeCount > KeyPadTimePeriod + KEYPAD_ISR_REPEAT_PERIOD)  //if 700ms
                {
                    //CASE C
                    KeyPadTimePeriod = g100msTimeCount;
                    KeyPadCheckCount = KEYPAD_ISR_REPEAT_KEY_CHECK; //3+2
                    *pflag = 0x01;
                    return MSRET_OK;
                }
                else
                {
                    return MSRET_OTHER;
                }
            }
        }
    }

    if(u8ChIdx == ADC_KEY_LAST_CHANNEL)
    {
        PreviousCMD = 0xFF;
    }
    return MSRET_ERROR;

}
#else
static BOOLEAN msKeypad_CH_GetKey(U8 Channel, U8 *pkey, U8* pflag)
{
    U16 i, KEY_LV[ADC_KEY_LEVEL];
    U8 j, Key_Value, *Keymapping=NULL;
    U8 u8ChIdx=0;
    U8 u8CHLVLs[KEYPAD_CHANNEL_SUPPORT]={ADC_CH1_LEVELS,ADC_CH2_LEVELS,ADC_CH3_LEVELS,ADC_CH4_LEVELS};

    *pkey = 0xFF;
    *pflag = 0;

#if( POWER_KEY_PAD_BY_INTERRUPT )
    if (u8PwrKeypadIntFlag){
        u8PwrKeypadIntFlag = FALSE;
        *pkey = IRKEY_POWER;
        return MSRET_OK;
    }
#endif

    for(i=0; i<ADC_KEY_LEVEL; i++)
        KEY_LV[i] = 0;

    u8ChIdx = msKeypad_GetChanIndex(Channel);
    if(u8ChIdx<ADC_KEY_CHANNEL_NUM)
        Keymapping = (U8*)tADCKeyFlag[u8ChIdx];
    else
        return MSRET_ERROR;
    for ( i = 0; i < KEYPAD_STABLE_NUM; i++ )
    {
        msKeypad_Get_ADC_Channel(Channel,&Key_Value);
        for (j=0;j<u8CHLVLs[Channel];j++)
        {
            if (Key_Value < tADCKeyLevel[u8ChIdx][j])
            {
                KEY_LV[j]++;
                break;
            }
        }
    }

    for(i=0; i<u8CHLVLs[Channel]; i++)
    {
        if(KEY_LV[i] >= KEYPAD_STABLE_NUM_MIN)
        {
            PressKey = TRUE;
            *pkey = *(Keymapping+i);
            //printf("CH[%d]=%02X\n",Channel,*pkey);
            if (PreviousCMD != *pkey)
            {
                PreviousCMD = *pkey;
                KeyPadCheckCount = 0;
            }
            else
            {
                if (KeyPadCheckCount < KEYPAD_KEY_VALIDATION)
                {
                    KeyPadCheckCount++;
                    return MSRET_ERROR;
                }
                else if (KeyPadCheckCount == KEYPAD_KEY_VALIDATION)
                {
                    KeyPadCheckCount++;
                    KeyPadTimePeriod = g100msTimeCount;
                    return MSRET_OK;
                }

                if (KeyPadCheckCount == KEYPAD_REPEAT_KEY_CHECK)    //3+2
                {
                    if (g100msTimeCount > KeyPadTimePeriod + KEYPAD_REPEAT_PERIOD_1)
                    {
                        KeyPadTimePeriod = g100msTimeCount;
                        KeyPadCheckCount = KEYPAD_REPEAT_KEY_CHECK_1;
                        *pflag = 0x01;
                    }
                    else
                    {
                        *pkey = 0xFF;
                        *pflag = 0x01;
                    }
                    return MSRET_OK;
                }
                else if (KeyPadCheckCount == KEYPAD_REPEAT_KEY_CHECK_1) //3+3
                {
                    if (g100msTimeCount > KeyPadTimePeriod)
                    {
                        KeyPadTimePeriod = g100msTimeCount;
                        KeyPadCheckCount = KEYPAD_REPEAT_KEY_CHECK_1;
                        *pflag = 0x01;
                    }
                    else
                    {
                        *pkey = 0xFF;
                        *pflag = 0x01;
                    }
                    return MSRET_OK;
                }

                if (g100msTimeCount > KeyPadTimePeriod + KEYPAD_REPEAT_PERIOD)  //if 700ms
                {
                    KeyPadTimePeriod = g100msTimeCount;
                    KeyPadCheckCount = KEYPAD_REPEAT_KEY_CHECK; //3+2
                    *pflag = 0x01;
                    return MSRET_OK;
                }
                else
                {
                    return MSRET_ERROR;
                }
            }
        }
    }

    if(u8ChIdx == ADC_KEY_LAST_CHANNEL)
    {
        if (PressKey)
            PressKey = FALSE;
        else
            PreviousCMD = 0xFF;
    }
    return MSRET_ERROR;

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
    BOOLEAN u8KeypadRes=MSRET_ERROR;

    //##########################
    //
    // Get key code in Multitask routine
    //
    msKeypad_Lock();    //No effect in non-os, replace by following flag

    bBlockKeypadIsr = TRUE;

    *pkey = g_u8KeypadKey;
    *pflag = g_u8KeypadRpt;  //repeat
    u8KeypadRes = g_u8KeypadRes;
    g_u8KeypadKey = 0xFF;
    g_u8KeypadRpt = 0;
    g_u8KeypadRes = MSRET_ERROR;

    bBlockKeypadIsr = FALSE;

    msKeypad_UnLock();    //No effect in non-os, replace by following flag

    //##########################
    //
    // Enable SAR to generate next interrupt
    //
    if(u8KeypadRes!=MSRET_ERROR)
    {
        //enable interrupt
        MsOS_EnableInterrupt(E_INT_IRQ_PMSLEEP);
    }
    return u8KeypadRes;
#else
    U8 Channel;

    for (Channel=0; Channel<KEYPAD_CHANNEL_SUPPORT; Channel++)
    {
        if (msKeypad_CH_GetKey(Channel, pkey, pflag))
        {
            return MSRET_OK;
        }
    }
    return MSRET_ERROR;
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
        if (KeypadCHValue <= ADC_KEY_1_L0)
            KeypadCount++;
    }
    if(CheckWakeupKeyPad(ADC_KEY_1_L1_FLAG))
    {
        if ((KeypadCHValue > ADC_KEY_1_L0) &&
            (KeypadCHValue <= ADC_KEY_1_L1))
            KeypadCount++;
    }
    if(CheckWakeupKeyPad(ADC_KEY_1_L2_FLAG))
    {
        if ((KeypadCHValue > ADC_KEY_1_L1) &&
            (KeypadCHValue <= ADC_KEY_1_L2))
            KeypadCount++;
    }
    if(CheckWakeupKeyPad(ADC_KEY_1_L3_FLAG))
    {
        if ((KeypadCHValue > ADC_KEY_1_L2) &&
            (KeypadCHValue <= ADC_KEY_1_L3))
            KeypadCount++;
    }

    KeypadCHValue = MDrv_ReadByte(REG_SAR_ADCOUT2);

    if(CheckWakeupKeyPad(ADC_KEY_2_L0_FLAG))
    {
        if (KeypadCHValue <= ADC_KEY_2_L0)
            KeypadCount++;
    }
    if(CheckWakeupKeyPad(ADC_KEY_2_L1_FLAG))
    {
        if ((KeypadCHValue > ADC_KEY_2_L0) &&
            (KeypadCHValue <= ADC_KEY_2_L1))
            KeypadCount++;
    }
    if(CheckWakeupKeyPad(ADC_KEY_2_L2_FLAG))
    {
        if ((KeypadCHValue > ADC_KEY_2_L1) &&
            (KeypadCHValue <= ADC_KEY_2_L2))
            KeypadCount++;
    }
    if(CheckWakeupKeyPad(ADC_KEY_2_L3_FLAG))
    {
        if ((KeypadCHValue > ADC_KEY_2_L2) &&
            (KeypadCHValue <= ADC_KEY_2_L3))
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
