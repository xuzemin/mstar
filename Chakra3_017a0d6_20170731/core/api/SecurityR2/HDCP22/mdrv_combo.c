///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   Mdrv_combo.c
/// @author MStar Semiconductor Inc.
/// @brief  MHL driver Function
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _MDRV_COMBO_C_
#define _MDRV_COMBO_C_

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
//#include "Global.h"
#include "Board.h"

#if( ENABLE_SECURITY_R2 )


#include "msReg.h"
#include "datatype.h"
#include "default_option_define.h"

#include "mapi_combo.h"
#include "mdrv_combo.h"
#include "mhal_combo.h"

#if (ENABLE_SECU_R2 == 1) && (ENABLE_HDCP22 == 1)
#include "drvHDCPMbx.h"
#include "drvHDCPRx.h"
#endif


//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
#define COMBO_DRV_DEBUG_MESSAGE         1

#if(COMBO_DEBUG_MESSAGE & COMBO_DRV_DEBUG_MESSAGE)
#define COMBO_DRV_DPUTSTR(str)          printf(str)
#define COMBO_DRV_DPRINTF(str, x)       printf(str, x)
#else
#define COMBO_DRV_DPUTSTR(str)
#define COMBO_DRV_DPRINTF(str, x)
#endif
//-------------------------------------------------------------------------------------------------
//  Local Structures
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------
BYTE ucComboEDIDEnableIndex = 0;
BYTE ucComboHDCPEnableIndex = 0;
BYTE ucComboDPEnableIndex = 0;
BYTE ucKeyEncodeString[COMBO_HDCP2_ENCODE_KEY_CHECK_SIZE] = {0x4D, 0x53, 0x54, 0x41, 0x52, 0x5F, 0x53, 0x45, 0x43, 0x55, 0x52, 0x45, 0x5F, 0x53, 0x54, 0x4F,\
                                                             0x52, 0x45, 0x5F, 0x46, 0x49, 0x4C, 0x45, 0x5F, 0x4D, 0x41, 0x47, 0x49, 0x43, 0x5F, 0x49, 0x44};

//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Global Functions
//-------------------------------------------------------------------------------------------------
#if 0
//**************************************************************************
//  [Function Name]:
//                  mdrv_combo_SetConfiguration()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_combo_SetConfiguration(BYTE ucEDIDEnableIndex, BYTE ucHDCPEnableIndex, BYTE ucDPEnableIndex)
{
    ucComboEDIDEnableIndex = ucEDIDEnableIndex;
    ucComboHDCPEnableIndex = ucHDCPEnableIndex;
    ucComboDPEnableIndex = ucDPEnableIndex;
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_combo_LoadEDID()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_combo_LoadEDID(BYTE *pEDIDSize, BYTE **pComboEDID)
{
    BYTE ucPortSelect = COMBO_INPUT_SELECT_PORT0;
    BYTE ucEDIDAddr = 1;

    //if(GET_COMBO_EDID_ENABLE_VGA())
    {
        mhal_combo_LoadEDID(COMBO_INPUT_SELECT_VGA, FALSE, pEDIDSize[COMBO_INPUT_SELECT_VGA], ucEDIDAddr, pComboEDID[COMBO_INPUT_SELECT_VGA]);
    }

    for(ucPortSelect = COMBO_INPUT_SELECT_PORT0; ucPortSelect < COMBO_INPUT_SELECT_MASK; ucPortSelect++)
    {
        if(GET_COMBO_EDID_ENABLE_PORT(ucPortSelect))
        {
            mhal_combo_LoadEDID(ucPortSelect, GET_COMBO_DP_ENABLE_PORT(ucPortSelect), pEDIDSize[ucPortSelect], ucEDIDAddr, pComboEDID[ucPortSelect]);

            ucEDIDAddr = ucEDIDAddr + pEDIDSize[ucPortSelect];
        }
    }
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_combo_LoadEDIDPort()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_combo_LoadEDIDPort(BYTE ucPortSelect, BYTE *pEDIDSize, BYTE **pComboEDID)
{
    BYTE ucInputSelect = COMBO_INPUT_SELECT_PORT0;
    BYTE ucEDIDAddr = 1;

    if(ucPortSelect == COMBO_INPUT_SELECT_VGA)
    {
        mhal_combo_LoadEDID(COMBO_INPUT_SELECT_VGA, FALSE, pEDIDSize[COMBO_INPUT_SELECT_VGA], ucEDIDAddr, pComboEDID[COMBO_INPUT_SELECT_VGA]);
    }
    else
    {
        for(ucInputSelect = COMBO_INPUT_SELECT_PORT0; ucInputSelect < COMBO_INPUT_SELECT_MASK; ucInputSelect++)
        {
            if(GET_COMBO_EDID_ENABLE_PORT(ucPortSelect))
            {
                if(ucInputSelect == ucPortSelect)
                {
                    mhal_combo_LoadEDID(ucPortSelect, GET_COMBO_DP_ENABLE_PORT(ucPortSelect), pEDIDSize[ucPortSelect], ucEDIDAddr, pComboEDID[ucPortSelect]);

                    break;
                }


                ucEDIDAddr = ucEDIDAddr + pEDIDSize[ucInputSelect];
            }
        }
    }
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_combo_LoadHDCPKey()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_combo_LoadHDCPKey(BYTE ucPortSelect, BYTE ucBcaps, BYTE *pHDCPKey, BYTE *pBKSV)
{
    mhal_combo_LoadHDCPKey(ucPortSelect, GET_COMBO_DP_ENABLE_PORT(ucPortSelect), ucBcaps, pHDCPKey, pBKSV);
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_combo_ClockEnable()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_combo_ClockEnable(BYTE ucComboEnableIndex)
{
    Bool bMainSwitch = TRUE;
    BYTE ucInputSelect = 0;

    if(ucComboEnableIndex > 0)
    {
        for(ucInputSelect = COMBO_INPUT_SELECT_PORT0; ucInputSelect < COMBO_INPUT_SELECT_MASK; ucInputSelect++)
        {
            if(ucComboEnableIndex &_BIT(ucInputSelect))
            {
                mhal_combo_ClockEnable(ucInputSelect, bMainSwitch);

                if(bMainSwitch)
                {
                    bMainSwitch = FALSE;
                }
            }
        }
    }
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_combo_AudioInitial()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_combo_AudioInitial(void)
{
    mhal_combo_AudioInitial();
    mhal_combo_ConfigGlobalMute(TRUE);
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_combo_ClockRtermControl()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_combo_ClockRtermControl(BYTE ucPortSelect, Bool bRtermEnable)
{
    mhal_combo_ClockRtermControl(ucPortSelect, bRtermEnable);
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_combo_DataRtermControl()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_combo_DataRtermControl(BYTE ucPortSelect, Bool bRtermEnable)
{
    mhal_combo_DataRtermControl(ucPortSelect, bRtermEnable);
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_combo_DoSWReset()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_combo_DoSWReset(BYTE ucPortSelect, DWORD ulSWResetValue)
{
    if((ulSWResetValue & COMBO_SW_RESET_ALL) == COMBO_SW_RESET_ALL)
    {
        ulSWResetValue = COMBO_SW_RESET_ALL;
    }

    mhal_combo_DoSWReset(ucPortSelect, ulSWResetValue);
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_combo_CreateTMDSAudioPath()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_combo_CreateTMDSAudioPath(BYTE ucPortSelect)
{
    mhal_combo_ConfigAudioSource(TRUE, ucPortSelect, 0);
    mhal_combo_ConfigAPLLSynthesizer(TRUE, ucPortSelect, 0);

    //config fading/mute event
    #if (ENABLE_AUDIO_AUTO_MUTE)
        mhal_combo_ConfigMuteEvent(TRUE, 0xAF);
    #else
        mhal_combo_ConfigMuteEvent(FALSE, 0x00);
    #endif

    #if (ENABLE_AUDIO_AUTO_FADING)
        mhal_combo_ConfigFadingEvent(TRUE, 0xAF);
    #else
        mhal_combo_ConfigFadingEvent(FALSE, 0x00);
    #endif
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_combo_CreateDPAudioPath()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_combo_CreateDPAudioPath(BYTE ucPortSelect, BYTE ucHBR2Select)
{
    mhal_combo_ConfigAudioSource(FALSE, ucPortSelect, ucHBR2Select);
    mhal_combo_ConfigAPLLSynthesizer(FALSE, ucPortSelect, ucHBR2Select);

    //config fading/mute event
   // mhal_combo_ConfigMuteEvent(FALSE, 0x00);

    mhal_combo_ConfigMuteEvent(TRUE, 0xFF);
    mhal_combo_ConfigFadingEvent(TRUE, 0xFF);
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_combo_ConfigGlobalMute()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_combo_ConfigGlobalMute(Bool bEnable)
{
    mhal_combo_ConfigGlobalMute(bEnable);
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_combo_GetDVIDualMainPort()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
BYTE mdrv_combo_GetDVIDualMainPort(BYTE ucPortSelect)
{
    return mhal_combo_GetDVIDualMainPort(ucPortSelect);
}
#endif

#if(COMBO_HDCP2_FUNCTION_SUPPORT)
//**************************************************************************
//  [Function Name]:
//                  mdrv_combo_SetHDCP2TxCallBackFunction()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_combo_SetHDCP2CallBackFunction(BYTE ucPortSelect, COMBO_HDCP2_CALL_BACK_FUNC pHDCP2TxFunc)
{
	if(pHDCP2TxFunc != NULL)
    {
        drv_HDCPRx_InitCBFunction(ucPortSelect, pHDCP2TxFunc);
    }
    else
    {
        COMBO_DRV_DPUTSTR("[Err] HDCP2 CB func init failed!!!\r\n");
    }
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_combo_HDCP2RxEventProc()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_combo_HDCP2RxEventProc(BYTE ucPortSelect, BYTE *pMessage)
{
    //COMBO_DRV_DPRINTF("** Combo HDCP2 Rx event!! port %d", ucPortSelect);
    //COMBO_DRV_DPRINTF("** Combo HDCP2 Rx event!! Message %d", pMessage[0]);

	//start parsing message and store to mbx handler
    drv_HDCPRx_MsgParser(ucPortSelect, pMessage);
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_combo_HDCP2RomCodeDone()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
Bool mdrv_combo_HDCP2RomCodeDone(void)
{
    static Bool bRamCodeDone = FALSE;
    Bool bFirstDoneFlag = FALSE;

    if(!bRamCodeDone)
    {
        if(drv_HDCPRx_GetR2EventFlag())
        {
            bRamCodeDone = TRUE;
            bFirstDoneFlag = TRUE;

            COMBO_DRV_DPUTSTR("**Combo check HDCP22 rom code done\r\n");
        }
    }

    return bFirstDoneFlag;
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_combo_HDCP2KeyDecodeDone()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
Bool mdrv_combo_HDCP2KeyDecodeDone(void)
{
    static Bool bKeyDecodeDone = FALSE;
    Bool bSecondDoneFlag = FALSE;

    if(!bKeyDecodeDone)
    {
        if(drv_HDCPRx_GetR2EventFlag())
        {
            bKeyDecodeDone = TRUE;
            bSecondDoneFlag = TRUE;

            COMBO_DRV_DPUTSTR("**Combo check HDCP22 key decode done\r\n");
        }
    }

    return bSecondDoneFlag;
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_combo_HDCP2CheckEncodeKeyValid()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
Bool mdrv_combo_HDCP2CheckEncodeKeyValid(BYTE *pKeyTable)
{
    Bool bKeyValidFlag = TRUE;
    BYTE uctemp = 0;

    for(uctemp = 0; uctemp < COMBO_HDCP2_ENCODE_KEY_CHECK_SIZE; uctemp++)
    {
        if(pKeyTable[uctemp] != ucKeyEncodeString[uctemp])
        {
            bKeyValidFlag = FALSE;
            //printf("Index: 0x%X, 0x%X is not matched\n", uctemp, pKeyTable[uctemp]);

            break;
        }
    }

    return bKeyValidFlag;
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_combo_HDCP2Initial()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_combo_HDCP2Initial(void)
{
	mhal_combo_HDCP2Initial();
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_combo_HDCP2Handler()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_combo_HDCP2Handler(void)
{
	//start process
	drv_HDCPRx_Handler();
}

#endif

#endif // ENABLE_SECURITY_R2

#endif // _MDRV_COMBO_C_

