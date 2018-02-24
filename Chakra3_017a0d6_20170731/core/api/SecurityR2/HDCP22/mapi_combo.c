///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   Mapi_combo.c
/// @author MStar Semiconductor Inc.
/// @brief  MHL driver Function
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _MAPI_COMBO_C_
#define _MAPI_COMBO_C_

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------

#include "msReg.h"
#include "msAPI_SecurityR2.h"


//#include "Global.h"
#include "datatype.h"
//#include "System.h"

#include "mapi_combo.h"
#include "mdrv_combo.h"
#include "mhal_combo.h"
//#include "drvADC.h"
//#include "mapi_mhl.h"
#include "mapi_tmds.h"
#include "drvHDCPMbx.h"
//#include "mdrv_combo.c"
#include "drvHDCPRx.h"
#include "mdrv_tmds.h"
//#include "drvDPRxComboApp.h"
//#if(ENABLE_LOAD_KEY_VIA_EFUSE)
//#include "msEread.h"
//#endif
#include "MsOS.h"
#include "drvBDMA.h"
#include "sysinfo.h"
//#include "mapp_customer.h"
//#include "combo_table.h"
#include "Utl.h"
#include "msAPI_MIU.h"
#include "MApp_GlobalFunction.h"


//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
#define COMBO_API_DEBUG_MESSAGE         0

#if (COMBO_DEBUG_MESSAGE & COMBO_API_DEBUG_MESSAGE)
#define COMBO_API_DPUTSTR(str)          puts(str)
#define COMBO_API_DPRINTF(str, x)       printf(str, x)
#else
#define COMBO_API_DPUTSTR(str)
#define COMBO_API_DPRINTF(str, x)
#endif

//-------------------------------------------------------------------------------------------------
//  Local Structures
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Combo EDID table
//-------------------------------------------------------------------------------------------------
#if 0
BYTE tMHL_EDID_SIZE_PORT[] =
{
#if(COMBO_IP_SUPPORT_TYPE >= COMBO_IP_SUPPORT_1PORT)
    COMBO_EDID_SIZE_PORT0,
#endif
#if(COMBO_IP_SUPPORT_TYPE >= COMBO_IP_SUPPORT_2PORT)
    COMBO_EDID_SIZE_PORT1,
#endif
#if(COMBO_IP_SUPPORT_TYPE >= COMBO_IP_SUPPORT_3PORT)
    COMBO_EDID_SIZE_PORT2,
#endif
#if(COMBO_IP_SUPPORT_TYPE >= COMBO_IP_SUPPORT_4PORT)
    COMBO_EDID_SIZE_PORT3,
#endif
#if(COMBO_IP_SUPPORT_TYPE >= COMBO_IP_SUPPORT_5PORT)
    COMBO_EDID_SIZE_PORT4,
#endif
#if(COMBO_IP_SUPPORT_TYPE >= COMBO_IP_SUPPORT_6PORT)
    COMBO_EDID_SIZE_PORT5,
#endif
    COMBO_EDID_SIZE_VGA,
};

BYTE *tCOMBO_EDID_TALBE_PORT[] =
{
#if(COMBO_IP_SUPPORT_TYPE >= COMBO_IP_SUPPORT_1PORT)
    tEDID_TABLE_COMBO_PORT0,
#endif
#if(COMBO_IP_SUPPORT_TYPE >= COMBO_IP_SUPPORT_2PORT)
    tEDID_TABLE_COMBO_PORT1,
#endif
#if(COMBO_IP_SUPPORT_TYPE >= COMBO_IP_SUPPORT_3PORT)
    tEDID_TABLE_COMBO_PORT2,
#endif
#if(COMBO_IP_SUPPORT_TYPE >= COMBO_IP_SUPPORT_4PORT)
    tEDID_TABLE_COMBO_PORT3,
#endif
#if(COMBO_IP_SUPPORT_TYPE >= COMBO_IP_SUPPORT_5PORT)
    tEDID_TABLE_COMBO_PORT4,
#endif
#if(COMBO_IP_SUPPORT_TYPE >= COMBO_IP_SUPPORT_6PORT)
    tEDID_TABLE_COMBO_PORT5,
#endif
    tEDID_TABLE_COMBO_VGA,
};

BYTE *tMHL_EDID_TALBE_PORT[] =
{
#if(COMBO_IP_SUPPORT_TYPE >= COMBO_IP_SUPPORT_1PORT)
    tEDID_TABLE_COMBO_PORT0,
#endif
#if(COMBO_IP_SUPPORT_TYPE >= COMBO_IP_SUPPORT_2PORT)
    tEDID_TABLE_COMBO_PORT1,
#endif
#if(COMBO_IP_SUPPORT_TYPE >= COMBO_IP_SUPPORT_3PORT)
    tEDID_TABLE_COMBO_PORT2,
#endif
#if(COMBO_IP_SUPPORT_TYPE >= COMBO_IP_SUPPORT_4PORT)
    tEDID_TABLE_COMBO_PORT3,
#endif
#if(COMBO_IP_SUPPORT_TYPE >= COMBO_IP_SUPPORT_5PORT)
    tEDID_TABLE_COMBO_PORT4,
#endif
#if(COMBO_IP_SUPPORT_TYPE >= COMBO_IP_SUPPORT_6PORT)
    tEDID_TABLE_COMBO_PORT5,
#endif
    tEDID_TABLE_COMBO_VGA,
};
#endif

//-------------------------------------------------------------------------------------------------
//  Combo HDCP key
//-------------------------------------------------------------------------------------------------
#if 0
BYTE tCOMBO_HDCP_BKSV[COMBO_HDCP_BKSV_SIZE] =
{
    0x89, 0x38, 0xae, 0x0d, 0xed,
};

BYTE tCOMBO_HDCP_KEY_TABLE[COMBO_HDCP_KEY_SIZE] =
{
    0x00, 0xE6, 0xD2, 0xD0, 0xA4, 0x0A, 0xF9, 0xAB, 0x2F, 0x9A, 0x2D, 0x3A,
    0xB5, 0xFF, 0x9D, 0x37, 0xB3, 0x63, 0x23, 0x6E, 0xA3, 0x4E, 0x58, 0xEF,
    0xD2, 0x78, 0x6D, 0x3B, 0xDE, 0xFD, 0x7E, 0x4D, 0xAA, 0xB6, 0x0C, 0x59,
    0x4F, 0x74, 0x3C, 0xF8, 0xDA, 0x65, 0x6E, 0x2F, 0xB4, 0xAB, 0xAD, 0x7F,
    0x89, 0xA1, 0x92, 0x25, 0x1A, 0xCD, 0x50, 0x93, 0x50, 0x00, 0x63, 0x88,
    0x7B, 0xD0, 0xD8, 0x4D, 0x46, 0x95, 0xA8, 0xFC, 0x9B, 0x0D, 0xD1, 0x08,
    0x06, 0xB2, 0x67, 0xBE, 0xA2, 0x90, 0xA7, 0x84, 0x2A, 0x4B, 0x28, 0xC8,
    0xDD, 0x8F, 0xC9, 0x48, 0xA3, 0x0A, 0x7D, 0xCA, 0xDA, 0xBC, 0xCE, 0xFA,
    0x9B, 0x9F, 0x61, 0x90, 0x9E, 0x46, 0x24, 0x2B, 0xA6, 0x7B, 0xB1, 0x6F,
    0xC4, 0x4C, 0x63, 0xAF, 0x44, 0xE1, 0x3A, 0xDD, 0x0D, 0xED, 0xF4, 0x45,
    0x36, 0x47, 0x0B, 0x48, 0x0A, 0xB1, 0xE6, 0xE9, 0xB6, 0xED, 0x78, 0x37,
    0xDC, 0xB0, 0x07, 0x72, 0x83, 0xDC, 0x73, 0x26, 0x31, 0x49, 0x03, 0x52,
    0x7C, 0xE6, 0xC6, 0xE8, 0x3C, 0xD1, 0x62, 0xFE, 0xF0, 0x01, 0x73, 0x23,
    0x90, 0x70, 0xA9, 0x52, 0x8C, 0x75, 0x1C, 0xE5, 0x63, 0x7C, 0xA9, 0x98,
    0x5F, 0xD9, 0x7C, 0x62, 0x25, 0x6C, 0x61, 0x6C, 0xB5, 0xF9, 0xDB, 0xD8,
    0x91, 0x2F, 0x25, 0xF6, 0x3E, 0x37, 0xBE, 0xE2, 0x92, 0x08, 0x07, 0x3C,
    0xE6, 0xC9, 0xE3, 0xB0, 0x4D, 0xF6, 0xAD, 0x54, 0x3C, 0xED, 0x92, 0x5A,
    0x97, 0x93, 0xC0, 0x48, 0xEA, 0x23, 0x6C, 0xDD, 0x9A, 0x00, 0xBA, 0xF1,
    0xB4, 0xE7, 0x7E, 0x84, 0x9A, 0xB5, 0xD5, 0xF4, 0xB0, 0x42, 0x49, 0x5E,
    0x15, 0x5A, 0x43, 0x2D, 0xA9, 0xB0, 0x0A, 0x1C, 0x75, 0xDE, 0x2E, 0x08,
    0xF7, 0xDF, 0x38, 0x03, 0xEB, 0x6A, 0x75, 0xEB, 0xDA, 0x1C, 0xA0, 0xC9,
    0x2F, 0x2A, 0x69, 0x3F, 0x13, 0xFB, 0xA4, 0x23, 0x0A, 0xE5, 0x0A, 0xA5,
    0xEF, 0xCC, 0x8D, 0xB6, 0x5E, 0x6C, 0xB6, 0xE8, 0x84, 0xEF, 0x03, 0xDC,
    0xC5, 0x8A, 0xA3, 0x4B, 0xEF, 0x44, 0x12, 0x7F,
};
#endif

#if(COMBO_HDCP2_FUNCTION_SUPPORT)
//HDCP22 ToDo:check this arrary, is it the bin gererated by security storm
static U8 *sg_pu8HDCP22Data;
#define HDCP22_DATA_SIZE (COMBO_HDCP2_ENCODE_KEY_SIZE + COMBO_HDCP2_EXTERNAL_KEY_ENABLE_SIZE)
#define HDCP22_RECEIVER_ID_SIZE     5
#define HDCP22_WAIT_FOR_INITKEY_DONE    10
BOOL g_bAESKeyInitDone = FALSE;
//BYTE tCOMBO_HDCP2_CERTRX_TABLE[COMBO_HDCP2_ENCODE_KEY_SIZE] = {0};
//static BYTE sg_aU8SecureStormKey[COMBO_HDCP2_SECURE_STORM_KEY] = {0};
#endif

//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------
#if 0
ST_COMBO_IP_PARAMETER stComboIPParameter = {FALSE, FALSE, FALSE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
#endif

//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------
#if 0
//**************************************************************************
//  [Function Name]:
//                  mapi_combo_GetComboMask()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
BYTE mapi_combo_GetComboMask(EN_COMBO_IP_SELECT ucComboSelect)
{
    BYTE ucComboMask = 0;

    switch(ucComboSelect)
    {
        case COMBO_IP_SELECT_PORT0:
            ucComboMask = COMBO_IP_MASK_PORT0;
            break;

        case COMBO_IP_SELECT_PORT1:
            ucComboMask = COMBO_IP_MASK_PORT1;
            break;

        case COMBO_IP_SELECT_PORT2:
            ucComboMask = COMBO_IP_MASK_PORT2;
            break;

        case COMBO_IP_SELECT_PORT3:
            ucComboMask = COMBO_IP_MASK_PORT3;
            break;

        case COMBO_IP_SELECT_PORT4:
            ucComboMask = COMBO_IP_MASK_PORT4;
            break;

        case COMBO_IP_SELECT_PORT5:
            ucComboMask = COMBO_IP_MASK_PORT5;
            break;

        case COMBO_IP_SELECT_VGA:
            ucComboMask = COMBO_IP_MASK_VGA;
            break;

        default:

            break;
    };

    return ucComboMask;
}

//**************************************************************************
//  [Function Name]:
//                  mapi_combo_GetComboType()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
EN_COMBO_IP_TYPE mapi_combo_GetComboType(EN_COMBO_IP_SELECT ucComboSelect)
{
    BYTE ucComboMask = mapi_combo_GetComboMask(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = COMBO_IP_TYPE_HDMI;

    if(stComboIPParameter.ucMHLEnableIndex & ucComboMask)
    {
        ucComboIPType = COMBO_IP_TYPE_MHL;
    }
    else if(stComboIPParameter.ucHDMIEnableIndex & ucComboMask)
    {
        ucComboIPType = COMBO_IP_TYPE_HDMI;
    }
    else if(stComboIPParameter.ucDPEnableIndex & ucComboMask)
    {
        ucComboIPType = COMBO_IP_TYPE_DP;
    }
    else if(stComboIPParameter.ucDualEnableIndex & ucComboMask)
    {
        ucComboIPType = COMBO_IP_TYPE_DUAL;
    }
    else if(stComboIPParameter.ucDVIEnableIndex & ucComboMask)
    {
        ucComboIPType = COMBO_IP_TYPE_DVI;
    }
    else
    {
        ucComboIPType = COMBO_IP_TYPE_VGA;
    }

    return ucComboIPType;
}

//**************************************************************************
//  [Function Name]:
//                  mapi_combo_GetComboEnableIndex()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
BYTE mapi_combo_GetComboEnableIndex(void)
{
    BYTE ucComboEnable = stComboIPParameter.ucHDMIEnableIndex;

    ucComboEnable |= stComboIPParameter.ucDVIEnableIndex;
    ucComboEnable |= stComboIPParameter.ucDualEnableIndex;
    ucComboEnable |= stComboIPParameter.ucDPEnableIndex;

    return ucComboEnable;
}
#endif

//**************************************************************************
//  [Function Name]:
//                  mapi_combo_GetComboInputPort()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
BYTE mapi_combo_GetComboInputPort(EN_COMBO_IP_SELECT ucComboSelect)
{
    BYTE ucInputPort = COMBO_INPUT_SELECT_PORT0;

    switch(ucComboSelect)
    {
        case COMBO_IP_SELECT_PORT0:
            ucInputPort = COMBO_INPUT_SELECT_PORT0;
            break;

        case COMBO_IP_SELECT_PORT1:
            ucInputPort = COMBO_INPUT_SELECT_PORT1;
            break;

        case COMBO_IP_SELECT_PORT2:
            ucInputPort = COMBO_INPUT_SELECT_PORT2;
            break;

        case COMBO_IP_SELECT_PORT3:
            ucInputPort = COMBO_INPUT_SELECT_PORT3;
            break;

        case COMBO_IP_SELECT_PORT4:
            ucInputPort = COMBO_INPUT_SELECT_PORT4;
            break;

        case COMBO_IP_SELECT_PORT5:
            ucInputPort = COMBO_INPUT_SELECT_PORT5;
            break;

        case COMBO_IP_SELECT_VGA:
            ucInputPort = COMBO_INPUT_SELECT_VGA;
            break;

        default:

            break;
    };

    return ucInputPort;
}

#if 0
//**************************************************************************
//  [Function Name]:
//                  mapi_combo_SetConfiguration()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mapi_combo_SetConfiguration(void)
{
    BYTE ucEDIDEnableIndex = stComboIPParameter.ucDPEnableIndex;
    BYTE ucHDCPEnableIndex = stComboIPParameter.ucDPEnableIndex;

    if(stComboIPParameter.bVGAEnableIndex)
    {
        ucEDIDEnableIndex |= COMBO_IP_MASK_VGA;
    }

    ucHDCPEnableIndex |= stComboIPParameter.ucDVIEnableIndex;
    ucHDCPEnableIndex |= stComboIPParameter.ucDualEnableIndex;
    ucHDCPEnableIndex |= stComboIPParameter.ucHDMIEnableIndex;

#if(COMBO_TMDS_USE_INTERNAL_EDID)
    ucEDIDEnableIndex |= ucHDCPEnableIndex;
#endif

    mdrv_combo_SetConfiguration(ucEDIDEnableIndex, ucHDCPEnableIndex, stComboIPParameter.ucDPEnableIndex);
}

//**************************************************************************
//  [Function Name]:
//                  mapi_combo_LoadHDCPKey()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mapi_combo_LoadHDCPKey(BYTE *pHDCPKey, BYTE *pBKSV)
{
    EN_COMBO_IP_SELECT ucComboSelect = COMBO_IP_SELECT_PORT0;
	BYTE ucInputPort = COMBO_INPUT_SELECT_PORT0;
    EN_COMBO_IP_TYPE  ucComboIPType = COMBO_IP_TYPE_HDMI;

    for(ucComboSelect = COMBO_IP_SELECT_PORT0; ucComboSelect < COMBO_IP_SELECT_MASK; ucComboSelect++)
    {
        ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
		ucComboIPType = mapi_combo_GetComboType(ucComboSelect);

        switch(ucComboIPType)
        {
            case COMBO_IP_TYPE_DVI:
                mdrv_combo_LoadHDCPKey(ucInputPort, 0x00, pHDCPKey, pBKSV);
                break;

            case COMBO_IP_TYPE_DUAL:
                mdrv_combo_LoadHDCPKey(ucInputPort, 0x00, pHDCPKey, pBKSV);
                mdrv_combo_LoadHDCPKey(mdrv_combo_GetDVIDualMainPort(ucInputPort), 0x00, pHDCPKey, pBKSV);
                break;

            case COMBO_IP_TYPE_HDMI:
            case COMBO_IP_TYPE_MHL:
                mdrv_combo_LoadHDCPKey(ucInputPort, 0x80, pHDCPKey, pBKSV);
                break;

            case COMBO_IP_TYPE_DP:
                mdrv_combo_LoadHDCPKey(ucInputPort, 0x00, pHDCPKey, pBKSV);
                break;

            default:

                break;
        }
    }
}

//**************************************************************************
//  [Function Name]:
//                  mapi_combo_PowerConfiguration()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mapi_combo_PowerConfiguration(void)
{
    static BYTE ucDisplayEnableIndex = 0;
    BYTE ucComboMask = 0;
    BYTE ucRtermEnableIndex = 0;
    BYTE ucRtermDisableIndex = 0;
    BYTE ucInputPort = COMBO_INPUT_SELECT_PORT0;
    EN_COMBO_IP_SELECT ucComboSelect = COMBO_IP_SELECT_PORT0;

    if(ucDisplayEnableIndex != stComboIPParameter.ucDisplayEnableIndex)
    {
        // Display change
        ucRtermDisableIndex = ucDisplayEnableIndex ^stComboIPParameter.ucDisplayEnableIndex;
        // Rtern enable
        ucRtermEnableIndex = ucRtermDisableIndex &stComboIPParameter.ucDisplayEnableIndex;
        // Rtern disable
        ucRtermDisableIndex = ucRtermDisableIndex &ucDisplayEnableIndex;

        for(ucComboSelect = COMBO_IP_SELECT_VGA; ucComboSelect < COMBO_IP_SELECT_MASK; ucComboSelect++)
        {
            ucComboMask = mapi_combo_GetComboMask(ucComboSelect);
            ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);

            if(ucRtermEnableIndex & ucComboMask)
            {
                switch(mapi_combo_GetComboType(ucComboSelect))
                {
                    case COMBO_IP_TYPE_VGA:
                        COMBO_API_DPRINTF("** Combo power on VGA!! %x", ucRtermEnableIndex);
                        break;

                    case COMBO_IP_TYPE_DVI:
                    case COMBO_IP_TYPE_HDMI:
                    case COMBO_IP_TYPE_MHL:
                        //mdrv_combo_ClockRtermControl(ucInputPort, TRUE);

                        if(!mapi_mhl_GetCableDetectPort(ucInputPort))
                        {
                            mdrv_combo_DataRtermControl(ucInputPort, TRUE);
                        }

                        mapi_tmds_PowerOnPort(ucInputPort);

                        break;

                    case COMBO_IP_TYPE_DUAL:
                        //mdrv_combo_ClockRtermControl(ucInputPort, TRUE);
                        //mdrv_combo_ClockRtermControl(ucInputPort +1, TRUE);
                        mdrv_combo_DataRtermControl(ucInputPort, TRUE);
                        mdrv_combo_DataRtermControl(mdrv_combo_GetDVIDualMainPort(ucInputPort), TRUE);

                        mapi_tmds_PowerOnPort(ucInputPort);

                        break;

                    case COMBO_IP_TYPE_DP:
                        mdrv_combo_ClockRtermControl(ucInputPort, TRUE);
                        mdrv_combo_DataRtermControl(ucInputPort, TRUE);
                        break;

                    default:

                        break;
                };
            }
            else if(ucRtermDisableIndex & ucComboMask)
            {
                switch(mapi_combo_GetComboType(ucComboSelect))
                {
                    case COMBO_IP_TYPE_VGA:
                        COMBO_API_DPRINTF("** Combo power down VGA!! %x", ucRtermDisableIndex);
                        break;

                    case COMBO_IP_TYPE_DVI:
                    case COMBO_IP_TYPE_HDMI:
                    case COMBO_IP_TYPE_MHL:
                        //mdrv_combo_ClockRtermControl(ucInputPort, FALSE);

                        if(!mapi_mhl_GetCableDetectPort(ucInputPort))
                        {
                            //mdrv_combo_DataRtermControl(ucComboSelect, FALSE);
                        }

                        mapi_tmds_PowerDownPort(ucInputPort);

                        break;

                    case COMBO_IP_TYPE_DUAL:
                        //mdrv_combo_ClockRtermControl(ucInputPort, FALSE);
                        //mdrv_combo_ClockRtermControl(ucInputPort +1, FALSE);
                        //mdrv_combo_DataRtermControl(ucInputPort, FALSE);
                        //mdrv_combo_DataRtermControl(ucInputPort +1, FALSE);

                        mapi_tmds_PowerDownPort(ucInputPort);

                        break;

                    case COMBO_IP_TYPE_DP:
                        //mdrv_combo_ClockRtermControl(ucInputPort, FALSE);
                        //mdrv_combo_DataRtermControl(ucInputPort, FALSE);
                        break;

                    default:

                        break;
                };
            }
        }

        ucDisplayEnableIndex = stComboIPParameter.ucDisplayEnableIndex;
    }
}

//**************************************************************************
//  [Function Name]:
//                  mapi_combo_GetDaisyChainType()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
Bool mapi_combo_GetDaisyChainType(EN_COMBO_IP_SELECT ucComboSelect)
{
    Bool bDaisyChainFlag = FALSE;
    BYTE ucComboMask = mapi_combo_GetComboMask(ucComboSelect);

    if(stComboIPParameter.ucDaisyEnableIndex & ucComboMask)
    {
        bDaisyChainFlag = TRUE;
    }

    return bDaisyChainFlag;
}
#endif

#if(COMBO_HDCP2_FUNCTION_SUPPORT)
//**************************************************************************
//  [Function Name]:
//                  mapi_combo_HDCP2Initial()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
//ToDo Refine these code!!!
void mapi_combo_HDCP2Initial(void)
{
    EN_COMBO_IP_SELECT ucComboSelect = COMBO_IP_SELECT_PORT0;
    BYTE ucInputPort = COMBO_INPUT_SELECT_PORT0;
    EN_COMBO_IP_TYPE  ucComboIPType = COMBO_IP_TYPE_HDMI;

//    sg_pu8HDCP22Data = ((U8*)((HDCP_KEY_BUFFER_MEMORY_TYPE & MIU1) ? (HDCP_KEY_BUFFER_ADR | MIU_INTERVAL) : (HDCP_KEY_BUFFER_ADR)));

#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA )
    sg_pu8HDCP22Data = (U8*)MsOS_PA2KSEG1(HDCP_KEY_BUFFER_ADR+0x2000+0x8000);
#else
    sg_pu8HDCP22Data = (U8 *)HDCP_KEY_BUFFER_ADR+0x2000+0x8000;
#endif

    drv_HDCPMBX_Init();
    mdrv_combo_HDCP2Initial();
    drv_HDCPRx_Init(HDCP_PORT_ALL);

    for(ucComboSelect = COMBO_IP_SELECT_PORT0; ucComboSelect < COMBO_IP_SELECT_MASK; ucComboSelect++)
    {
        ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
        //ucComboIPType = mapi_combo_GetComboType(ucComboSelect);
        // U11 only has HDMI port
        ucComboIPType = COMBO_IP_TYPE_HDMI;

        switch(ucComboIPType)
        {
            //case COMBO_IP_TYPE_DVI:
            //case COMBO_IP_TYPE_DUAL:
            case COMBO_IP_TYPE_HDMI:
            //case COMBO_IP_TYPE_MHL:
                mdrv_combo_SetHDCP2CallBackFunction(ucInputPort, mapi_tmds_HDCP2TxEventProc);
                break;

          #if 0
            case COMBO_IP_TYPE_DP:
                mdrv_combo_SetHDCP2CallBackFunction(ucInputPort, mapi_DP_HDCP2TxEventProc);
                break;
          #endif

            default:

                break;
        }
    }
}

//ToDo Refine these code!!!
#if(COMBO_HDCP2_DECODE_KEY)
void mapi_combo_KeyInitial(void)
{
    //sg_pu8HDCP22Data = ((U8*)((HDCP_KEY_BUFFER_MEMORY_TYPE & MIU1) ? (HDCP_KEY_BUFFER_ADR | MIU_INTERVAL) : (HDCP_KEY_BUFFER_ADR)));

  #if 0//(CustomerType == CustomerType_LG_Unicorn)
    if (!msAPI_combo_IPInsertHDCP22Key(TRUE, (U8*)0x10018))
  #else
    //if (!msAPI_combo_IPInsertHDCP22Key(TRUE, tCOMBO_HDCP2_CERTRX_TABLE, sg_aU8SecureStormKey))
    if (!msAPI_combo_IPInsertHDCP22Key(FALSE, NULL))
  #endif
    {
        printf("Initial Insert HDCP Key Fail\n");
        return;
    }
    drv_HDCPRx_DecodeKey(sg_pu8HDCP22Data);
}
#endif

#endif

//-------------------------------------------------------------------------------------------------
//  Global Functions
//-------------------------------------------------------------------------------------------------
#if 0
//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPSetPowerStatus()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msAPI_combo_IPSetPowerStatus(EN_COMBO_POWER_STATUS ucComboPowerStatus)
{
    if((ucComboPowerStatus == COMBO_IP_POWER_DC_ON) || (ucComboPowerStatus == COMBO_IP_POWER_PS_ON))
    {
        stComboIPParameter.bComboPowerIgnore = TRUE;
    }

    mapi_mhl_SetPowerStatus((BYTE)ucComboPowerStatus);
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPConfiguration()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msAPI_combo_IPConfiguration(Bool bDisplayEnable, EN_COMBO_IP_SELECT ucComboSelect, EN_INPUTPORT_TYPE ucComboType)
{
    BYTE ucComboMask = mapi_combo_GetComboMask(ucComboSelect);

    if(!stComboIPParameter.bConfigFinish)
    {
        if(ucComboType &TYPE_ANALOG)
        {
            stComboIPParameter.bVGAEnableIndex = TRUE;
        }

        if(ucComboType &TYPE_DVI_SINGLE)
        {
            SET_COMBO_IP_PARAMETER(stComboIPParameter.ucDVIEnableIndex, ucComboMask);
        }

        if(ucComboType &TYPE_DVI_DUAL)
        {
            SET_COMBO_IP_PARAMETER(stComboIPParameter.ucDualEnableIndex, ucComboMask);
        }

        if(ucComboType &TYPE_HDMI)
        {
            SET_COMBO_IP_PARAMETER(stComboIPParameter.ucHDMIEnableIndex, ucComboMask);
        }

        if(ucComboType &TYPE_HDMI_2_0)
        {
            SET_COMBO_IP_PARAMETER(stComboIPParameter.ucHDMI2EnableIndex, ucComboMask);
        }

        if(ucComboType &TYPE_MHL)
        {
            SET_COMBO_IP_PARAMETER(stComboIPParameter.ucMHLEnableIndex, ucComboMask);
        }

        if(ucComboType &TYPE_DP)
        {
            SET_COMBO_IP_PARAMETER(stComboIPParameter.ucDPEnableIndex, ucComboMask);
        }

        if(ucComboType &TYPE_HBR2_0)
        {
            SET_COMBO_IP_PARAMETER(stComboIPParameter.ucHBR20EnableIndex, ucComboMask);
        }

        if(ucComboType &TYPE_HBR2_1)
        {
            SET_COMBO_IP_PARAMETER(stComboIPParameter.ucHBR21EnableIndex, ucComboMask);
        }

#if(COMBO_DP_DAISY_CHAIN_SUPPORT)
        stComboIPParameter.ucDaisyEnableIndex = COMBO_DP_DC_SUPPORT_INDEX;
#endif
    }

    if(bDisplayEnable)
    {
        SET_COMBO_IP_PARAMETER(stComboIPParameter.ucDisplayEnableIndex, ucComboMask);
    }
    else
    {
        CLR_COMBO_IP_PARAMETER(stComboIPParameter.ucDisplayEnableIndex, ucComboMask);
    }

    mapi_combo_SetConfiguration();

#if ENABLE_VGA_INPUT
    if(ucComboType &TYPE_ANALOG)
    {
        msADC_SetConfiguration(stComboIPParameter.ucDisplayEnableIndex);
    }
#endif

    mapi_tmds_SetConfiguration(stComboIPParameter.ucDVIEnableIndex, stComboIPParameter.ucDualEnableIndex, stComboIPParameter.ucHDMIEnableIndex, stComboIPParameter.ucHDMI2EnableIndex, stComboIPParameter.ucMHLEnableIndex, stComboIPParameter.ucDisplayEnableIndex);

    mapi_DP_SetConfiguration(stComboIPParameter.ucHBR20EnableIndex, stComboIPParameter.ucHBR21EnableIndex,stComboIPParameter.ucDPEnableIndex,stComboIPParameter.ucDisplayEnableIndex);

    mapi_mhl_SetConfiguration(stComboIPParameter.ucMHLEnableIndex, stComboIPParameter.ucDisplayEnableIndex);
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPPMIsrHandler()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msAPI_combo_IPPMIsrHandler(void)
{
#if(COMBO_MHL_BLOCK_ENABLE)
    mapi_mhl_IsrHandler(E_INT_IRQ_PM_IRQ_OUT);
#endif

#if(COMBO_DP_BLOCK_ENABLE)
    mapi_DP_PMIsrHandler(E_INT_IRQ_PM_IRQ_OUT);
#endif
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPIsrHandler()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msAPI_combo_IPIsrHandler(InterruptNum eIntNum)
{
    UNUSED(eIntNum);

#if(COMBO_DP_BLOCK_ENABLE)
    mapi_DP_IsrHandler();
#endif

#if(COMBO_TMDS_BLOCK_ENABLE)
    mapi_tmds_ISR();
#endif

    MsOS_EnableInterrupt(E_INT_IRQ_COMB);
}
#endif

#if 0
//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPInitial()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msAPI_combo_IPInitial(void)
{
    stComboIPParameter.bConfigFinish = TRUE;

    if(!stComboIPParameter.bComboPowerIgnore)
    {
#if(COMBO_EDID_BLOCK_ENABLE)
        mdrv_combo_LoadEDID(tMHL_EDID_SIZE_PORT, tCOMBO_EDID_TALBE_PORT);
#endif

        stComboIPParameter.bComboPowerIgnore = FALSE;
    }

    mapi_combo_PowerConfiguration();

#if(COMBO_ADC_BLOCK_ENABLE && ENABLE_VGA_INPUT)
    msADC_init();
#endif


#if(COMBO_HDCP2_FUNCTION_SUPPORT)
	/*********************************************************************
		[NOTE]: HDCP22 init code is moved to msAPI_combo_IPHandler();
		this is due to HDCP init process needs polling security R2 ROM code done before init process start.
	**********************************************************************/
    //mapi_combo_HDCP2Initial();
    //mapi_tmds_SetHDCP2CallBackFunction(mdrv_combo_HDCP2RxEventProc, tCOMBO_HDCP2_CERTRX_TABLE);
    //mapi_DP_SetHDCP2CallBackFunction(mdrv_combo_HDCP2RxEventProc, tCOMBO_HDCP2_CERTRX_TABLE);
#endif

    mdrv_combo_ClockEnable(mapi_combo_GetComboEnableIndex());

#if(COMBO_TMDS_BLOCK_ENABLE)
    mapi_tmds_Initial();
#endif

#if(COMBO_DP_BLOCK_ENABLE)
    mapi_DP_Initial();
#endif

#if(COMBO_MHL_BLOCK_ENABLE)
    mapi_mhl_Initial(tMHL_EDID_TALBE_PORT);
    //mapi_mhl_SetSystemControlFlag(MHL_SYSTEM_FORCE_DISPLAY_ENABLE);

#if(COMBO_MHL_CTS_MODE_ENABLE) //For CTS 4.3.17.2
    mapi_mhl_SetSystemControlFlag(MHL_SYSTEM_FORCE_SEND_MSG_ENABLE);
#endif

#endif

#if(COMBO_AUDIO_BLOCK_ENABLE)
    mdrv_combo_AudioInitial();
#endif

#if(ENABLE_LOAD_KEY_VIA_EFUSE)
    msEread_LoadKeyViaEfuse(tCOMBO_HDCP_KEY_TABLE, tCOMBO_HDCP_BKSV, EFUSE_0);
#endif

#if(COMBO_HDCP14_BLOCK_ENABLE)
    mapi_combo_LoadHDCPKey(tCOMBO_HDCP_KEY_TABLE, tCOMBO_HDCP_BKSV);
#endif

    MsOS_AttachInterrupt(E_INT_IRQ_COMB, msAPI_combo_IPIsrHandler);
    MsOS_EnableInterrupt(E_INT_IRQ_COMB);
}
#endif

#if(COMBO_HDCP2_FUNCTION_SUPPORT)
//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPHandler()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************

#define HDCP22_INTERNAL_CEERTRX_KEY 0
#define DEBUG_CERT_KEY  0
//#define CERTRX_SIZE     (522)
#define KEY_BANK_OFFSET (-0x20000)
#define KEY_BANK__CERT_OFFSET (KEY_BANK_OFFSET+0x2000+0x8000)
#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA )
void msAPI_WaitSecuR2InitKeyDone(void)
{
#define SECU_R2_INITKEY_DONE_FLAG   0x5A
#define CLEAR_SECU_R2_INITKEY_DONE_FLAG MDrv_WriteByte(0x1033CE, 0x00)

    U32 u32CheckSecuInitKeyTimer = MsOS_GetSystemTime();
    while(MDrv_ReadByte(0x1033CE) != SECU_R2_INITKEY_DONE_FLAG)
    {
        if(MsOS_Timer_DiffTimeFromNow(u32CheckSecuInitKeyTimer) > 1000)
        {
            MApp_Fatal_Error("Time out for SECU_R2 InitKey fail\n",__FUNCTION__);
            break;
        }
    }
    CLEAR_SECU_R2_INITKEY_DONE_FLAG;
}
#endif
void msAPI_combo_GetHDCPRevID(U8* u8Buf)
{
    U32 u32Addr_VA=0;
    U16 i = 0;
    u32Addr_VA = MsOS_PA2KSEG1(SECURITY_R2_ADR + KEY_BANK__CERT_OFFSET);
    for ( i = 0; i < HDCP22_RECEIVER_ID_SIZE; i++ )
    {
        u8Buf[i] = *((U8 *)(u32Addr_VA+i));
    }
}
void msAPI_combo_IPLoadKey(void)
{
#if HDCP22_INTERNAL_CEERTRX_KEY // get key from DRAM(descrypted by SecurityR2)
  MS_U8 au8certDat[CERTRX_SIZE] =
    {
#if 1    // org
    0xD2, 0x35, 0xF5, 0xC0, 0x9A, 0xAC, 0xF5, 0xCA, 0x10, 0xB4, 0xE0, 0x38, 0x0A, 0x3F, 0xA8, 0x09,
    0x9B, 0xCF, 0x0D, 0x31, 0x63, 0x5E, 0x1B, 0x6F, 0x93, 0xAA, 0x87, 0x7D, 0x36, 0x4C, 0x12, 0x6E,
    0xFE, 0xB1, 0x02, 0xEF, 0x7D, 0xD3, 0x32, 0x86, 0x0C, 0x93, 0x8C, 0x9F, 0x6B, 0x12, 0x4B, 0x58,
    0x3C, 0xE8, 0x0F, 0x42, 0xE7, 0xEE, 0x8B, 0x6B, 0xBD, 0xB6, 0xB3, 0x6D, 0xEE, 0x55, 0x68, 0x30,
    0xA1, 0x8F, 0xB9, 0x0E, 0x9E, 0x69, 0x13, 0xC8, 0xF6, 0xDA, 0xB8, 0x5C, 0xE0, 0x53, 0xA5, 0xFD,
    0x0F, 0x0D, 0x0C, 0xD8, 0x76, 0xF3, 0xE3, 0x2B, 0xC2, 0xEB, 0x5D, 0xE5, 0xA1, 0x0B, 0x16, 0x05,
    0xA4, 0xAE, 0x67, 0xF1, 0xC9, 0x8C, 0xE8, 0x4B, 0xB2, 0x96, 0x26, 0xCB, 0x75, 0xDB, 0xAC, 0x50,
    0x5D, 0xE7, 0x2B, 0x58, 0xB8, 0x30, 0xDA, 0x9C, 0x73, 0xE5, 0xAE, 0x6A, 0xF0, 0x58, 0x46, 0x1D,
    0xF1, 0xA2, 0xD3, 0xBB, 0xAF, 0x01, 0x00, 0x01, 0x00, 0x00, 0x9B, 0xE4, 0x8C, 0xC1, 0xB4, 0x5B,
    0x76, 0x05, 0xEB, 0x21, 0x35, 0xCE, 0x4A, 0xC5, 0x13, 0x12, 0x70, 0xB8, 0xA1, 0x4D, 0x0E, 0x6C,
    0x84, 0x8B, 0x29, 0xF1, 0xDA, 0x8B, 0xCC, 0x50, 0xF4, 0x3F, 0x2B, 0xFF, 0x92, 0x31, 0xE4, 0x21,
    0x77, 0x32, 0xF7, 0xE4, 0xD5, 0xD4, 0x5B, 0xD2, 0x5E, 0xF5, 0x8E, 0xEF, 0x4A, 0xBA, 0xD0, 0x35,
    0x16, 0xB4, 0xFA, 0x38, 0xE0, 0xD1, 0x29, 0xB2, 0x58, 0xC2, 0x1B, 0x38, 0x7D, 0xD5, 0x84, 0x50,
    0x29, 0xA0, 0xDC, 0x41, 0x28, 0x8D, 0x69, 0x61, 0xFF, 0x86, 0x01, 0x72, 0x06, 0xB6, 0x25, 0x22,
    0x42, 0xFD, 0x15, 0xEA, 0xDE, 0x85, 0x89, 0x65, 0x97, 0xA1, 0x14, 0x89, 0x21, 0x1C, 0x85, 0x1C,
    0x7D, 0xC0, 0xEB, 0xF8, 0xED, 0x64, 0xD1, 0x61, 0xF6, 0xD9, 0xF5, 0x13, 0x18, 0x74, 0x9F, 0x4A,
    0x44, 0x9B, 0xC8, 0xF0, 0x6A, 0xCC, 0xCB, 0x02, 0x62, 0xCF, 0xFF, 0xF3, 0x9F, 0xB8, 0x6D, 0xCE,
    0x04, 0x80, 0x89, 0x06, 0xDB, 0xE5, 0xC7, 0x48, 0x63, 0xC2, 0x8C, 0xAD, 0x0A, 0xE4, 0xF0, 0x0D,
    0x66, 0x98, 0x82, 0x81, 0x35, 0x0F, 0x57, 0x51, 0x1B, 0x76, 0xF2, 0xA1, 0xD2, 0x39, 0xCB, 0x95,
    0xD9, 0x36, 0x86, 0x57, 0xE2, 0x54, 0x28, 0x1F, 0xEB, 0xAD, 0xCC, 0xF7, 0xD0, 0x2B, 0xD3, 0x0C,
    0x12, 0x97, 0xBB, 0xBA, 0xF1, 0x83, 0x6D, 0x0E, 0xA4, 0x47, 0x89, 0x55, 0x9C, 0x75, 0x36, 0x87,
    0x2B, 0x31, 0xCF, 0x3F, 0x20, 0x48, 0x2E, 0x47, 0x38, 0x57, 0xD1, 0xC5, 0x29, 0x99, 0x08, 0x29,
    0x1D, 0x7D, 0x39, 0x8E, 0xCB, 0x57, 0x65, 0xF4, 0x3F, 0x9C, 0x2C, 0xBE, 0xA9, 0x56, 0xAF, 0x4B,
    0x39, 0xA0, 0x21, 0x51, 0x7C, 0x7B, 0x36, 0x6E, 0xFF, 0x37, 0x58, 0x9B, 0x2F, 0x00, 0x50, 0xCE,
    0x34, 0xBC, 0xB1, 0x8B, 0xF6, 0x2C, 0xB2, 0xE5, 0x32, 0x7C, 0xC2, 0xD3, 0x94, 0x76, 0x49, 0x81,
    0xA7, 0x76, 0xD8, 0xCB, 0xBA, 0xFF, 0x80, 0xEB, 0x78, 0x1B, 0x8C, 0x34, 0xAA, 0x70, 0xF3, 0x9D,
    0xDC, 0xB2, 0x11, 0x55, 0xD1, 0x48, 0x43, 0xCA, 0xE5, 0x38, 0xFE, 0x4A, 0xD9, 0x4E, 0x3C, 0x57,
    0xBD, 0x27, 0x8B, 0x3E, 0xB9, 0x9B, 0x52, 0x19, 0xDE, 0xA0, 0x75, 0xF5, 0x17, 0x25, 0xD5, 0xDA,
    0xA6, 0x10, 0xEC, 0xBE, 0xD8, 0x41, 0x17, 0x6D, 0xDB, 0x7E, 0xAC, 0xA1, 0x69, 0x00, 0x9F, 0x2C,
    0x5B, 0x15, 0xEF, 0x23, 0xFF, 0x48, 0x70, 0xFE, 0x99, 0x06, 0x4E, 0xDC, 0x25, 0x3B, 0x2C, 0xE5,
    0xBE, 0x76, 0xB3, 0x70, 0xFF, 0x20, 0x7E, 0x2C, 0x09, 0x09, 0x24, 0xFF, 0xA6, 0xCB, 0x42, 0x55,
    0x29, 0xF8, 0x17, 0xCE, 0x0E, 0x91, 0x1F, 0x53, 0x86, 0xCA, 0x67, 0xCB, 0xD3, 0x51, 0x8F, 0xE6,
    0x8C, 0x6E, 0x26, 0xD3, 0xC7, 0x7F, 0x26, 0x0A, 0x01, 0xDD
#else  // plan
    0x0C, 0x5F, 0x87, 0x96, 0x63, 0xA8, 0x23, 0x98,
    0x56, 0x48, 0x4C, 0x50, 0x45, 0xEA, 0x7C, 0x2C,  0x17, 0x16, 0x9D, 0x03, 0xEE, 0x15, 0x65, 0x28,
    0x6A, 0xBD, 0x10, 0x66, 0x22, 0x60, 0xC2, 0x89,  0x32, 0x22, 0xB7, 0xA8, 0x6B, 0xD3, 0x9F, 0x48,
    0x72, 0x7D, 0x51, 0x19, 0xF7, 0x2C, 0xEA, 0x48,  0x22, 0xCC, 0x11, 0x57, 0xCF, 0x03, 0x4E, 0x7E,
    0xAD, 0x22, 0x5C, 0x05, 0x9B, 0x2D, 0x98, 0xFF,  0x0A, 0xD5, 0x5F, 0x4C, 0x4E, 0xF9, 0x45, 0x99,
    0xB6, 0xC5, 0x38, 0xD0, 0x62, 0xF2, 0x06, 0xB4,  0xF2, 0x3D, 0xF6, 0xA8, 0x38, 0xB5, 0xE5, 0x4E,
    0xD7, 0x50, 0x60, 0xEC, 0xB8, 0xD3, 0xA8, 0xC4,  0x7C, 0xE5, 0xC1, 0xE8, 0xB9, 0x6F, 0x1C, 0x18,
    0x6D, 0x9D, 0x20, 0xE4, 0x99, 0x4C, 0x0D, 0x04,  0x67, 0x46, 0x93, 0x36, 0x4F, 0x31, 0x57, 0xBC,
    0xA0, 0xC4, 0x71, 0xB8, 0x79, 0x61, 0x75, 0x6D,  0x0B, 0xF4, 0x6E, 0xB7, 0x5F, 0x01, 0x00, 0x01,
    0x10, 0x00, 0x16, 0x11, 0xFB, 0x74, 0x6D, 0xD5,  0x39, 0x3F, 0xFB, 0x23, 0x1A, 0xD6, 0x46, 0xE4,
    0xD8, 0x34, 0x42, 0xBA, 0x4A, 0x99, 0xA4, 0xF4,  0x31, 0xA0, 0x16, 0x0B, 0x82, 0x2F, 0x36, 0xC4,
    0x45, 0x21, 0xD2, 0xCF, 0x0D, 0x44, 0x44, 0x12,  0x94, 0xD4, 0x94, 0x48, 0x3D, 0x9B, 0x7D, 0x76,
    0x89, 0xC3, 0x02, 0xA2, 0x21, 0x6D, 0x55, 0x31,  0xBA, 0x27, 0xFC, 0xA5, 0xED, 0x61, 0x45, 0x27,
    0x66, 0xFD, 0xEC, 0xDC, 0x93, 0x5A, 0x55, 0x44,  0xFB, 0x1E, 0x6E, 0x7D, 0xD7, 0x8A, 0xCD, 0xC3,
    0xE4, 0x49, 0x54, 0xB1, 0x4D, 0x91, 0x07, 0xC0,  0x04, 0x39, 0x74, 0x23, 0xC8, 0x95, 0xED, 0xA7,
    0x3F, 0x3C, 0x85, 0xBA, 0xCE, 0x0C, 0x8F, 0x8F,  0x4C, 0xF6, 0xA9, 0x54, 0x42, 0x5F, 0x17, 0xEE,
    0x5F, 0x6E, 0xCC, 0x58, 0xEA, 0x51, 0x9E, 0xCB,  0xC8, 0x7E, 0xE4, 0x32, 0xF4, 0x0B, 0xE7, 0x6E,
    0xFB, 0xE8, 0x17, 0xEB, 0x57, 0x2A, 0xEF, 0x9C,  0xA1, 0x90, 0xC1, 0x2F, 0x9B, 0x5B, 0xD2, 0xD7,
    0x40, 0xA2, 0xF1, 0x35, 0x84, 0xB7, 0x0B, 0x2D,  0xF3, 0x68, 0xFC, 0xE5, 0x05, 0xD2, 0xF5, 0xEF,
    0x0A, 0xDC, 0x53, 0x72, 0xCB, 0xD2, 0x3D, 0xB3,  0x5C, 0x63, 0x46, 0x2B, 0x14, 0xD4, 0x76, 0x5B,
    0x7C, 0x1D, 0xC6, 0x7B, 0x0C, 0xAE, 0x58, 0xE7,  0xFF, 0xC7, 0x20, 0x86, 0xAC, 0xB2, 0x35, 0xE3,
    0x7A, 0x4F, 0x52, 0xF3, 0x61, 0x15, 0xED, 0xCF,  0xEC, 0xAF, 0x10, 0x66, 0xC5, 0x9E, 0x07, 0xE9,
    0x60, 0x28, 0xC3, 0xCD, 0x64, 0x4C, 0x1C, 0xE2,  0xF0, 0xF6, 0xC6, 0x9B, 0x0D, 0x43, 0x14, 0xE6,
    0x8B, 0x34, 0xAB, 0x22, 0x15, 0x54, 0x00, 0x50,  0x51, 0xD5, 0x9A, 0xC9, 0x29, 0x8F, 0xCA, 0x72,
    0xA0, 0xC1, 0x54, 0x23, 0x4B, 0x97, 0x83, 0x1F,  0x33, 0x48, 0x3A, 0xF6, 0x37, 0x40, 0x4E, 0x06,
    0xA0, 0x0B, 0x6C, 0xCA, 0x38, 0x08, 0xB6, 0xEC,  0x06, 0x0B, 0x7B, 0x54, 0x31, 0xB2, 0x61, 0xCC,
    0xED, 0xA5, 0x7E, 0x4D, 0x57, 0xAE, 0x28, 0xB4,  0xFB, 0x39, 0x3E, 0x0D, 0x7F, 0x4D, 0xB7, 0x9C,
    0x1E, 0x45, 0x2A, 0xD9, 0xD9, 0xBD, 0x28, 0x35,  0x20, 0xCB, 0xE0, 0x83, 0xF5, 0x1F, 0xAE, 0xA2,
    0x5D, 0x56, 0xA4, 0x3E, 0x61, 0x6A, 0x1D, 0xB1,  0xF0, 0x1F, 0xDA, 0x89, 0x16, 0x41, 0xD3, 0x65,
    0x64, 0x91, 0xB6, 0xE9, 0x08, 0x62, 0x1B, 0x6A,  0x35, 0x3B, 0xB2, 0xEB, 0xB5, 0x65, 0xA9, 0xB0,
    0x1C, 0xB0, 0x10, 0x16, 0x19, 0x03, 0x79, 0x98,  0x15, 0x9F, 0x82, 0x2C, 0x1D, 0x3B, 0xE8, 0xEA,
    0xFA, 0x24, 0x0F, 0x24, 0x79, 0xDD, 0x38, 0x5B,  0x63, 0x46, 0xD7, 0x92, 0x06, 0xF6, 0xA0, 0xD7,
    0xAA, 0xC5, 0xD5, 0x78, 0x6A, 0x1E, 0xA4, 0x59,  0x23, 0x3E, 0x8D, 0x50, 0x6F, 0xAF, 0x72, 0x11,
    0xA6, 0xA3
#endif
    };
#endif

    U32 u32CertKeyAddr_VA=0;

#if DEBUG_CERT_KEY
    U16 u16i;
#endif
#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA )
    U32 u32CertKeyAddr_PA = SECURITY_R2_ADR + KEY_BANK__CERT_OFFSET;
#else
#define _BIT31 (1L<<31)
    U32 u32CertKeyAddr_PA = SECURITY_R2_ADR + KEY_BANK__CERT_OFFSET + _BIT31;
#endif
    //memcpy( au8certDat, (U8 *)u32CertKeyAddr, sizeof(au8certDat));

    u32CertKeyAddr_VA = MsOS_PA2KSEG1(u32CertKeyAddr_PA);

#if DEBUG_CERT_KEY
    printf("u32CertKeyAddr_PA=%x\n", u32CertKeyAddr_PA);
    printf("u32CertKeyAddr_VA=%x\n", u32CertKeyAddr_VA);
    //printf("sg_pu8HDCP22Data=%x\n", sg_pu8HDCP22Data);
#endif

    mapi_combo_HDCP2Initial();
#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA )
    msAPI_WaitSecuR2InitKeyDone();
#endif
//Print_Buffer(sg_pu8HDCP22Data, 32);
#if DEBUG_CERT_KEY
    printf("sg_pu8HDCP22Data=%x\n", sg_pu8HDCP22Data);
#endif

    //drv_HDCPMBX_SetKeyMessage(MSG_HDCP22_LG_DECRPT, MBX_HKR2, MBXMSG_WITH_ARG, MBXMSG_STATE_WAIT,
    //     MBX_ERR_NONE, ((HDCP_DECRYPT_BUFFER_MEMORY_TYPE & MIU1) ? (HDCP_DECRYPT_BUFFER_ADR | MIU_INTERVAL) : (HDCP_DECRYPT_BUFFER_ADR)), NULL);

    mapi_tmds_SetHDCP2CallBackFunction(mdrv_combo_HDCP2RxEventProc, sg_pu8HDCP22Data);


#if HDCP22_INTERNAL_CEERTRX_KEY // get key from DRAM(descrypted by SecurityR2)
    msAPI_MIU_ReadMemBytes(u32CertKeyAddr_PA, au8certDat, CERTRX_SIZE );
    memcpy(sg_pu8HDCP22Data, au8certDat, CERTRX_SIZE);
    memcpy((void *)((ULONG)sg_pu8HDCP22Data|BIT31), au8certDat, CERTRX_SIZE);
#else
    msAPI_MIU_ReadMemBytes(u32CertKeyAddr_PA, sg_pu8HDCP22Data, CERTRX_SIZE );
//    msAPI_MIU_ReadMemBytes(u32CertKeyAddr, _BIT31+sg_pu8HDCP22Data, CERTRX_SIZE );

//    memcpy(sg_pu8HDCP22Data, u32CertKeyAddr, CERTRX_SIZE);
//    memcpy((void *)((ULONG)sg_pu8HDCP22Data|BIT31), u32CertKeyAddr, CERTRX_SIZE);

#endif

#if DEBUG_CERT_KEY
    printf("\r\n == RxCertData  sg_pu8HDCP22Data== \r\n");
    for ( u16i = 0; u16i < CERTRX_SIZE; u16i++ )
    {
        printf("0x%02X ", sg_pu8HDCP22Data[u16i]);
        if ( (u16i+1)%16 == 0)
            printf("\r\n");
    }
    printf("\r\n");

    printf("\r\n == RxCertData  u32CertKeyAddr  == \r\n");
    for ( u16i = 0; u16i < CERTRX_SIZE; u16i++ )
    {
        printf("0x%02X ", * ((U8 *)(u32CertKeyAddr_VA+u16i)));
        if ( (u16i+1)%16 == 0)
            printf("\r\n");
    }
    printf("\r\n");
#endif
    mapi_tmds_SetHDCP2CallBackFunction(mdrv_combo_HDCP2RxEventProc, sg_pu8HDCP22Data);
}
#if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA) )
U8 msApi_combo_HDMI_Covert_InputPortToHdmiIdx(E_MUX_INPUTPORT enInputPortType)
{
    U8 u8HdmiIdx = 0;


    switch(enInputPortType)
    {
        default:
        case INPUT_PORT_DVI0:
            u8HdmiIdx = 0;
            break;

        case INPUT_PORT_DVI1:
            u8HdmiIdx = 1;
            break;

        case INPUT_PORT_DVI2:
            u8HdmiIdx = 2;
            break;

        case INPUT_PORT_DVI3:
            u8HdmiIdx = 3;
            break;

    }

    return u8HdmiIdx;
}
#endif
void msAPI_combo_IPHandler(void)
{

    static U8 u8WaitForAesKey = 0;
    static U8 u8KeyInitOnce;
    if(!u8KeyInitOnce)  //for init HDCP key
    {
        u8KeyInitOnce=TRUE;
        msAPI_combo_IPLoadKey();
    }
    if(u8WaitForAesKey < HDCP22_WAIT_FOR_INITKEY_DONE)
    {
        u8WaitForAesKey = u8WaitForAesKey + 1;
    }
    else
    {
        g_bAESKeyInitDone = TRUE;
    }

// Send HDCP22 bin from HK R2 to Security R2
#if 0//(COMBO_HDCP2_DECODE_KEY)

    if (s_bHDCP_Initial_Done == TRUE)
    {
        if(mdrv_combo_HDCP2KeyDecodeDone())
        {
            WORD i = 0;
            //update from DRAM
        	for ( i = 0; i < HDCP22_DATA_SIZE; i++ )
        	{
        		sg_pu8HDCP22Data[i] = MIU8((ULONG)sg_pu8HDCP22Data + i);
        		#if 0
        		printf("0x%02X ", tCOMBO_HDCP2_CERTRX_TABLE[i]);
        		if ((i+1) % 16 == 0)
        			printf("\r\n");
        		#endif
        	}
        	//printf("\r\n");
        	//printf("\n****************HDCP2KeyDecodeDone\n");
        }
    }

#endif
#if ( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA) ) //mazda have 3 HDMI ports,need check which port working 
    if(IsSrcTypeHDMI(stSystemInfo[MAIN_WINDOW].enInputSourceType) == FALSE)
        return;
    U8 u8SySPortIdx = 0;
    U8 u8DVIPort = 0;
    u8SySPortIdx = MApi_XC_Mux_GetHDMIPort(stSystemInfo[MAIN_WINDOW].enInputSourceType);
    u8DVIPort = msApi_combo_HDMI_Covert_InputPortToHdmiIdx((E_MUX_INPUTPORT)u8SySPortIdx);
#endif
    mdrv_combo_HDCP2Handler();

    //if ((tmds_port[i].port_type == MsCombo_TMDS_TYPE_HDMI) && (tmds_port[i].port_power == MsCombo_TMDS_POWER_ON))
    //if (gmfcSysInfo.enInputSourceType == INPUT_SOURCE_HDMI)
    {

#if(MAYA_HDCP)
    #if ( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA) )
        mdrv_tmds_HDCP2Handler((MSCombo_TMDS_PORT_INDEX)u8DVIPort);
    #else
        mdrv_tmds_HDCP2Handler((MSCombo_TMDS_PORT_INDEX)0);
    #endif
#else
        mdrv_tmds_HDCP2Handler((MSCombo_TMDS_PORT_INDEX)(gmfcSysInfo.enInputHdmiPort));
#endif

    }
}
#endif

#if 0
//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPTimerIsrHandler()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msAPI_combo_IPTimerIsrHandler(void)
{
#if(COMBO_MHL_BLOCK_ENABLE)
    mapi_mhl_TimerInterrupt();
#endif

#if(COMBO_TMDS_BLOCK_ENABLE)
    mapi_tmds_TimerInterrupt();
#endif

#if(COMBO_DP_BLOCK_ENABLE)
    mapi_DP_TimerInterrupt();
#endif
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPGetColorFormat()
//  [Description]
//
//  [Arguments]:
//
//  [Return]: 0 = RGB, 1 = YCbCr422, 2 = YCbCr 444
//
//**************************************************************************
ST_COMBO_COLOR_FORMAT msAPI_combo_IPGetColorFormat(EN_COMBO_IP_SELECT ucComboSelect)
{
    ST_COMBO_COLOR_FORMAT ucColorFormat = {COMBO_COLOR_FORMAT_DEFAULT, COMBO_COLOR_RANGE_DEFAULT, COMBO_COLORIMETRY_NONE, COMBO_YUV_COLORIMETRY_ITU601};
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:
        case COMBO_IP_TYPE_DUAL:

            break;

        case COMBO_IP_TYPE_HDMI:
        case COMBO_IP_TYPE_MHL:
            ucColorFormat = mapi_tmds_Get_Color_Format(ucInputPort);
            break;

        case COMBO_IP_TYPE_DP:
            ucColorFormat = mapi_DP_GetColorFormate(ucInputPort);
            break;

        default:

            break;
    };

    return ucColorFormat;
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPGetColorDepth()
//  [Description]
//
//  [Arguments]:
//
//  [Return]: 0 = 6bit,1 = 8bit, 2 = 10bit, 3 = 12bit, 4 = 16bit, 5 = unknow
//
//**************************************************************************
EN_COLOR_DEPTH_TYPE msAPI_combo_IPGetColorDepth(EN_COMBO_IP_SELECT ucComboSelect)
{
    EN_COLOR_DEPTH_TYPE ucColorDepth = COMBO_COLOR_DEPTH_8BIT;
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:
        case COMBO_IP_TYPE_DUAL:
            ucColorDepth = (EN_COLOR_DEPTH_TYPE)mapi_tmds_GetColorDepthInfo(ucInputPort);
            break;

        case COMBO_IP_TYPE_HDMI:
        case COMBO_IP_TYPE_MHL:
            ucColorDepth = (EN_COLOR_DEPTH_TYPE)mapi_tmds_GetColorDepthInfo(ucInputPort);
            break;

        case COMBO_IP_TYPE_DP:
            ucColorDepth = (EN_COLOR_DEPTH_TYPE)mapi_DP_GetColorDepthInfo(ucInputPort);
            break;

        default:

            break;
    };

    return ucColorDepth;
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPGetPacketContent()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msAPI_combo_IPGetPacketContent(EN_COMBO_IP_SELECT ucComboSelect, EN_PACKET_DEFINE_TYPE ucPacketType, BYTE ucPacketLength, BYTE *pPacketData)
{
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);

    if(ucPacketLength > 0)
    {
        switch(ucComboIPType)
        {
            case COMBO_IP_TYPE_DVI:
            case COMBO_IP_TYPE_DUAL:

                break;

            case COMBO_IP_TYPE_HDMI:
            case COMBO_IP_TYPE_MHL:
                mapi_tmds_GetPacketContent(ucInputPort, ucPacketType, ucPacketLength, pPacketData);
                break;

            case COMBO_IP_TYPE_DP:
                if(ucPacketType == COMBO_PACKET_DP_MISC)
                {
                    mapi_DP_Get_Misc(ucInputPort , pPacketData);
                }

                break;

            default:

                break;
        };
    }
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPGetCableDetect()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
EN_COMBO_IP_CABLE msAPI_combo_IPGetCableDetect(EN_COMBO_IP_SELECT ucComboSelect)
{
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);
    EN_COMBO_IP_CABLE ucComboIPCableDetect = COMBO_IP_CABLE_NONE;

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:
        case COMBO_IP_TYPE_DUAL:
            if(mapi_tmds_DetectCablePlug(ucInputPort)) // GPIO detect
            {
                ucComboIPCableDetect = COMBO_IP_CABLE_DVI;
            }

            break;

        case COMBO_IP_TYPE_HDMI:
            if(mapi_tmds_DetectCablePlug(ucInputPort)) // GPIO detect
            {
                ucComboIPCableDetect = COMBO_IP_CABLE_HDMI;
            }

            break;

        case COMBO_IP_TYPE_MHL:
            if(mapi_mhl_GetCableDetectPort(ucInputPort))
            {
                ucComboIPCableDetect = COMBO_IP_CABLE_MHL;
            }
            else if(mapi_tmds_DetectCablePlug(ucInputPort)) // SAR detect
            {
                ucComboIPCableDetect = COMBO_IP_CABLE_HDMI;
            }

            break;

        case COMBO_IP_TYPE_DP:
            if(mapi_DP_GetCableDetectPort(ucInputPort))
            {
                ucComboIPCableDetect = COMBO_IP_CABLE_DP;
            }

            break;

        default:

            break;
    };

    return ucComboIPCableDetect;
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPCheckSourceAlive()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
Bool msAPI_combo_IPCheckSourceAlive(EN_COMBO_IP_SELECT ucComboSelect)
{
    Bool bSourceAlive = FALSE;
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:
        case COMBO_IP_TYPE_DUAL:
        case COMBO_IP_TYPE_HDMI:
            bSourceAlive = mapi_tmds_Clock_Stable(ucInputPort);
            break;

        case COMBO_IP_TYPE_MHL:
            if(mapi_mhl_GetCableDetectPort(ucInputPort))
            {
                bSourceAlive = mapi_mhl_GetCbusConnectPort(ucInputPort);
            }
            else if(mapi_tmds_DetectCablePlug(ucInputPort))
            {
                bSourceAlive = mapi_tmds_Clock_Stable(ucInputPort);
            }

            break;

        case COMBO_IP_TYPE_DP:
            bSourceAlive = mapi_DP_CheckSourceLock(ucInputPort);
            break;

        default:

            break;
    };

    return bSourceAlive;
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPControlHPD()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msAPI_combo_IPControlHPD(EN_COMBO_IP_SELECT ucComboSelect, Bool bSetHPD)
{
    Bool bDaisyChainFlag = mapi_combo_GetDaisyChainType(ucComboSelect);
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:
        case COMBO_IP_TYPE_DUAL:
        case COMBO_IP_TYPE_HDMI:
            mapi_tmds_Set_HPD(ucInputPort, bSetHPD);
			break;

        case COMBO_IP_TYPE_MHL:
            if(!mapi_mhl_GetCableDetectPort(ucInputPort))
            {
                mapi_tmds_Set_HPD(ucInputPort, bSetHPD);
            }

            break;

        case COMBO_IP_TYPE_DP:
			if(bDaisyChainFlag) // Epona path
            {

            }
			else
			{
				mapi_DP_Set_HPD(ucInputPort, bSetHPD);
			}

            break;

        default:

            break;
    };
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPCreateAudioPath()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msAPI_combo_IPCreateAudioPath(EN_COMBO_IP_SELECT ucComboSelect)
{
    static BYTE ucCurrentAudioPath = COMBO_INPUT_SELECT_MASK;
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);

    if(ucCurrentAudioPath != ucInputPort)
    {
        // When VGA or DVI must disable audio function
        mapi_tmds_ConfigAudioPort(ucInputPort, FALSE);
        mapi_DP_ConfigAudioPort(ucInputPort, FALSE);

        switch(ucComboIPType)
        {
            case COMBO_IP_TYPE_DVI:
            case COMBO_IP_TYPE_DUAL:

                break;

            case COMBO_IP_TYPE_HDMI:
            case COMBO_IP_TYPE_MHL:
                mapi_tmds_ConfigAudioPort(ucInputPort, TRUE); //for setting tmds driver global structure
                mdrv_combo_CreateTMDSAudioPath(ucInputPort);

                break;

            case COMBO_IP_TYPE_DP:
                mdrv_combo_CreateDPAudioPath(ucInputPort, mapi_DP_ComboConvertHBR2(ucInputPort));
                mapi_DP_ConfigAudioPort(ucInputPort, TRUE);

                break;

            default:

                break;
        };

        ucCurrentAudioPath = ucInputPort;
    }
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_ConfigGlobalMute()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msAPI_combo_IPConfigGlobalMute(Bool bEnable)
{
    mdrv_combo_ConfigGlobalMute(bEnable);
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPClockControl()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msAPI_combo_IPClockControl(EN_COMBO_IP_SELECT ucComboSelect, Bool bClockHigh)
{
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:
        case COMBO_IP_TYPE_DUAL:
        case COMBO_IP_TYPE_HDMI:
            mdrv_combo_ClockRtermControl(ucInputPort, bClockHigh);

            if(!bClockHigh)
            {
                mdrv_combo_DoSWReset(ucInputPort, COMBO_SW_RESET_HDCP |COMBO_SW_RESET_HDMI);
            }

            break;

        case COMBO_IP_TYPE_MHL:
            if(!mapi_mhl_GetCableDetectPort(ucInputPort))
            {
                mdrv_combo_ClockRtermControl(ucInputPort, bClockHigh);

                if(!bClockHigh)
                {
                    mdrv_combo_DoSWReset(ucInputPort, COMBO_SW_RESET_HDCP |COMBO_SW_RESET_HDMI);
                }
            }

            break;

        case COMBO_IP_TYPE_DP:

            break;

        default:

            break;
    };
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPPowerOn()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msAPI_combo_IPPowerOn(void)
{
    BYTE ucInputPort = COMBO_INPUT_SELECT_PORT0;
    EN_COMBO_IP_SELECT ucComboSelect = COMBO_IP_SELECT_PORT0;

    for(ucComboSelect = COMBO_IP_SELECT_PORT0; ucComboSelect < COMBO_IP_SELECT_MASK; ucComboSelect++)
    {
        ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);

        switch(mapi_combo_GetComboType(ucComboSelect))
        {
            case COMBO_IP_TYPE_DVI:
            case COMBO_IP_TYPE_DUAL:

                break;

            case COMBO_IP_TYPE_HDMI:
            case COMBO_IP_TYPE_MHL:

                break;

            case COMBO_IP_TYPE_DP:

                break;

            default:

                break;
        };
    }
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPPowerDown()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msAPI_combo_IPPowerDown(void)
{
    BYTE ucInputPort = COMBO_INPUT_SELECT_PORT0;
    EN_COMBO_IP_SELECT ucComboSelect = COMBO_IP_SELECT_PORT0;

    for(ucComboSelect = COMBO_IP_SELECT_PORT0; ucComboSelect < COMBO_IP_SELECT_MASK; ucComboSelect++)
    {
        ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);

        switch(mapi_combo_GetComboType(ucComboSelect))
        {
            case COMBO_IP_TYPE_DVI:
            case COMBO_IP_TYPE_DUAL:

                break;

            case COMBO_IP_TYPE_HDMI:
            case COMBO_IP_TYPE_MHL:
                mapi_mhl_PowerControl((BYTE)COMBO_IP_POWER_DC_OFF);
                break;

            case COMBO_IP_TYPE_DP:

                break;

            default:

                break;
        };
    }
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPPowerSaving()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msAPI_combo_IPPowerSaving(void)
{
    BYTE ucInputPort = COMBO_INPUT_SELECT_PORT0;
    EN_COMBO_IP_SELECT ucComboSelect = COMBO_IP_SELECT_PORT0;

    for(ucComboSelect = COMBO_IP_SELECT_PORT0; ucComboSelect < COMBO_IP_SELECT_MASK; ucComboSelect++)
    {
        ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);

        switch(mapi_combo_GetComboType(ucComboSelect))
        {
            case COMBO_IP_TYPE_DVI:
            case COMBO_IP_TYPE_DUAL:

                break;

            case COMBO_IP_TYPE_HDMI:
            case COMBO_IP_TYPE_MHL:
                mapi_mhl_PowerControl((BYTE)COMBO_IP_POWER_POWER_SAVING);
                break;

            case COMBO_IP_TYPE_DP:

                break;

            default:

                break;
        };
    }
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPGetSplitFlag()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
Bool msAPI_combo_IPGetSplitFlag(EN_COMBO_IP_SELECT ucComboSelect)
{
    Bool bSplitFlag = FALSE;
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:
        case COMBO_IP_TYPE_DUAL:

            break;

        case COMBO_IP_TYPE_HDMI:
        case COMBO_IP_TYPE_MHL:
            bSplitFlag = mapi_tmds_GetSplitFlag(ucInputPort);
            break;

        case COMBO_IP_TYPE_DP:
            bSplitFlag = mapi_DP_GetSplitFlag(ucInputPort);
            break;

        default:

            break;
    }

    return bSplitFlag;
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPCheckAudioStatus()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
Bool msAPI_combo_IPCheckAudioStatus(EN_COMBO_IP_SELECT ucComboSelect)
{
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);
    Bool bAudPktReceived = FALSE;

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:
        case COMBO_IP_TYPE_DUAL:

            break;

        case COMBO_IP_TYPE_HDMI:
        case COMBO_IP_TYPE_MHL:
            bAudPktReceived = mapi_tmds_CheckAudioStatus(ucInputPort);
            break;

        case COMBO_IP_TYPE_DP:
            bAudPktReceived = mapi_DP_CheckAudioStatus(ucInputPort);
            break;

        default:

            break;
    }

    return bAudPktReceived;
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPLoadEDIDPort()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msAPI_combo_IPLoadEDIDPort(EN_COMBO_IP_SELECT ucComboSelect)
{
    Bool bDaisyChainFlag = mapi_combo_GetDaisyChainType(ucComboSelect);
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_HDMI:
        case COMBO_IP_TYPE_MHL:
            mapi_mhl_LoadEDIDPort(ucInputPort, tMHL_EDID_TALBE_PORT);
        case COMBO_IP_TYPE_DVI:
        case COMBO_IP_TYPE_DUAL:
        case COMBO_IP_TYPE_DP:
        case COMBO_IP_TYPE_VGA:
            if(bDaisyChainFlag) // Epona path
            {

            }
            else
            {
                mdrv_combo_LoadEDIDPort(ucInputPort, tMHL_EDID_SIZE_PORT, tCOMBO_EDID_TALBE_PORT);
            }

            break;

        default:

            break;
    }
}
#endif

#if(COMBO_HDCP2_FUNCTION_SUPPORT)
//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPInsertHDCP22Key()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
//ToDo Refine these code!!!
Bool msAPI_combo_IPInsertHDCP22Key(Bool bExternalKey, BYTE *pu8SecureStormData)
{
    //U16 u16Cnt = 0;

    if (sg_pu8HDCP22Data == NULL)
    {
        COMBO_API_DPRINTF("** Combo HDCP22 Data Pointer is NULL!! %d", 0);
        return FALSE;
    }

    if(bExternalKey == DISABLE)
    {
        sg_pu8HDCP22Data[COMBO_HDCP2_ENCODE_KEY_SIZE] = 0; //0x00: using external Key
        return TRUE;
    }

    if (pu8SecureStormData == NULL)
    {
        COMBO_API_DPRINTF("** Combo Secure Storm Data Pointer is NULL!! %d", 0);
        return FALSE;
    }

  #if 0//(CustomerType == CustomerType_LG_Unicorn)
    // HDCP22 Data from Flash
    if (!MDrv_BDMA_Copy_Flash2Dram(0x10018, (U32)sg_pu8HDCP22Data, COMBO_HDCP2_ENCODE_KEY_SIZE)) // Refine source size define
    {
        COMBO_API_DPRINTF("** Combo Loading Secure Storm Data Fail!! %d", 0);
        return FALSE;
    }

  #else
    // HDCP22 Data In code
#if !MAYA_HDCP
    if (!MDrv_BDMA_Copy_Dram2Dram((U32)pu8SecureStormData, (U32)sg_pu8HDCP22Data, COMBO_HDCP2_ENCODE_KEY_SIZE))
    {
        COMBO_API_DPRINTF("** Combo Loading Secure Storm Data Fail!! %d", 0);
        return FALSE;
    }
#endif
  #endif

  #if 0
    printf("\n===HDCP22_DATA\n");
    printf("ADDR 0x%X\n", (U32)sg_pu8HDCP22Data);
    for (u16Cnt=0; u16Cnt<COMBO_HDCP2_ENCODE_KEY_SIZE; u16Cnt++)
    {
        if ((u16Cnt&0x0F)==0)
            printf("\n");

        printf("0x%02X, ", sg_pu8HDCP22Data[u16Cnt]);
    }
    printf("\n");
  #endif

#if !MAYA_HDCP
    if(!mdrv_combo_HDCP2CheckEncodeKeyValid(&sg_pu8HDCP22Data[32])) // Refine the size 32 definition
    {
        COMBO_API_DPRINTF("** Combo Secure Storm Data is invalid!! %d", 0);
        return FALSE;
    }
#endif
    sg_pu8HDCP22Data[COMBO_HDCP2_ENCODE_KEY_SIZE] = 1; //0x01: using external Key

    return TRUE;
}
#endif

#if 0
//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPGetTmdsModeInfo()
//  [Description]
//
//  [Arguments]:
//
//  [Return]: 0 =  DVI mode; 1 = HDMI mode
//
//**************************************************************************
BYTE msAPI_combo_IPGetTmdsModeInfo(EN_COMBO_IP_SELECT ucComboSelect)
{
    BYTE ucTmdsInfo = 0;
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:
        case COMBO_IP_TYPE_DUAL:

            break;

        case COMBO_IP_TYPE_HDMI:
        case COMBO_IP_TYPE_MHL:
            ucTmdsInfo = mapi_tmds_Input_Is_HDMI(ucInputPort);
            break;

        case COMBO_IP_TYPE_DP:

            break;

        default:

            break;
    };

    return ucTmdsInfo;
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPGetTmdsClkStable()
//  [Description]
//
//  [Arguments]:
//
//  [Return]: 0 =  clk unstable; 1 = clk stable
//
//**************************************************************************
BYTE msAPI_combo_IPGetTmdsClkStable(EN_COMBO_IP_SELECT ucComboSelect)
{
    BYTE ucTmdsClkStable = 0;
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:
        case COMBO_IP_TYPE_DUAL:
        case COMBO_IP_TYPE_HDMI:
        case COMBO_IP_TYPE_MHL:
            ucTmdsClkStable = mapi_tmds_Clock_Stable(ucInputPort);
            break;

        case COMBO_IP_TYPE_DP:
            break;

        default:

            break;
    };

    return ucTmdsClkStable;
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPGetTmdsAudioFreq()
//  [Description]
//
//  [Arguments]:
//
//  [Return]: EN_TMDS_AUD_FREQ_INDEX
//
//**************************************************************************
EN_TMDS_AUD_FREQ_INDEX msAPI_combo_IPGetTmdsAudioFreq(EN_COMBO_IP_SELECT ucComboSelect)
{
    EN_TMDS_AUD_FREQ_INDEX ucTmdsAudioFreq = COMBO_TMDS_AUD_FREQ_ERROR;
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:
        case COMBO_IP_TYPE_DUAL:
            break;

        case COMBO_IP_TYPE_HDMI:
        case COMBO_IP_TYPE_MHL:
            ucTmdsAudioFreq = (EN_TMDS_AUD_FREQ_INDEX)mapi_tmds_GetAudioFreq(ucInputPort);
            break;

        case COMBO_IP_TYPE_DP:
            break;

        default:

            break;
    };

    return ucTmdsAudioFreq;
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPGetTmdsIsAudioFmtPCM()
//  [Description]:
//
//  [Arguments]:
//
//  [Return]:
//                  EN_TMDS_AUDIO_FORMAT:
//                      COMBO_AUDIO_FMT_NON_PCM   = 0,
//                      COMBO_AUDIO_FMT_PCM       = 1,
//                      MCOMBO_AUDIO_FMT_UNKNOWN  = 2,
//
//**************************************************************************
EN_TMDS_AUDIO_FORMAT msAPI_combo_IPGetTmdsIsAudioFmtPCM(EN_COMBO_IP_SELECT ucComboSelect)
{
    EN_TMDS_AUDIO_FORMAT ucTmdsIsAudioFmtPCM = COMBO_AUDIO_FMT_UNKNOWN;
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:
        case COMBO_IP_TYPE_DUAL:
            break;

        case COMBO_IP_TYPE_HDMI:
        case COMBO_IP_TYPE_MHL:
            ucTmdsIsAudioFmtPCM = (EN_TMDS_AUDIO_FORMAT)mapi_tmds_IsAudioFmtPCM(ucInputPort);
            break;

        case COMBO_IP_TYPE_DP:
            break;

        default:

            break;
    };

    return ucTmdsIsAudioFmtPCM;
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPGetPixelRepetitionInfo()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
EN_TMDS_PIXEL_REPETITION msAPI_combo_IPGetPixelRepetitionInfo(EN_COMBO_IP_SELECT ucComboSelect)
{
    EN_TMDS_PIXEL_REPETITION enPixelRepInfo = COMBO_TMDS_RESERVED_PIX_REP;
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:
        case COMBO_IP_TYPE_DUAL:
            break;

        case COMBO_IP_TYPE_HDMI:
        case COMBO_IP_TYPE_MHL:
            enPixelRepInfo = (EN_TMDS_PIXEL_REPETITION)mapi_tmds_GetPixelRepetitionInfo(ucInputPort);
            break;

        case COMBO_IP_TYPE_DP:

            break;

        default:

            break;
    };

    return enPixelRepInfo;
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPGetTmdsClockRate()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
WORD msAPI_combo_IPGetTmdsClockRate(EN_COMBO_IP_SELECT ucComboSelect)
{
    WORD ucTmdsClockRate = 0;
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:
        case COMBO_IP_TYPE_DUAL:
        case COMBO_IP_TYPE_HDMI:
        case COMBO_IP_TYPE_MHL:
            ucTmdsClockRate = mapi_tmds_GetClockRate(ucInputPort);
            break;

        case COMBO_IP_TYPE_DP:
            break;

        default:

            break;
    };

      return ucTmdsClockRate;
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPSetTmdsMonochromeMode()
//  [Description]:
//
//  [Arguments]:
//
//  [Return]:  None
//
//**************************************************************************
void msAPI_combo_IPSetTmdsMonochromeMode(EN_COMBO_IP_SELECT ucComboSelect, Bool bEnable, Bool bFlag, EN_TMDS_MONO_BIT ucBits)
{
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:
        case COMBO_IP_TYPE_DUAL:
            mapi_tmds_SetMonochromeMode(ucInputPort, bEnable, bFlag, (MSCombo_TMDS_MONO_BIT)ucBits);
            break;

        case COMBO_IP_TYPE_HDMI:
            break;

        case COMBO_IP_TYPE_MHL:
            break;

        case COMBO_IP_TYPE_DP:
            break;

        default:

            break;
    };

}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPSetTmdsDVIDeepColorSetting()
//  [Description]:
//
//  [Arguments]:
//
//  [Return]:  None
//
//**************************************************************************
void msAPI_combo_IPSetTmdsDVIDeepColorSetting(EN_COMBO_IP_SELECT ucComboSelect, Bool bEnable, EN_TMDS_DVI_DEEP_COLOR ucBits)
{
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:
            mapi_tmds_DVIDeepColorSetting(ucInputPort, bEnable, (MSCombo_TMDS_DVI_DEEP_COLOR)ucBits);
            break;

        case COMBO_IP_TYPE_DUAL:
            break;

        case COMBO_IP_TYPE_HDMI:
            break;

        case COMBO_IP_TYPE_MHL:
            break;

        case COMBO_IP_TYPE_DP:
            break;

        default:

            break;
    };

}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPCheckAVMuteINT()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
BOOL msAPI_combo_IPCheckAVMuteINT(EN_COMBO_IP_SELECT ucComboSelect, Bool bClr)
{
    BOOL IsAVMute = 0;
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:
        case COMBO_IP_TYPE_DUAL:
            break;

        case COMBO_IP_TYPE_HDMI:
        case COMBO_IP_TYPE_MHL:
            IsAVMute = mapi_tmds_CheckAVMuteINT(ucInputPort, bClr);
            break;

        case COMBO_IP_TYPE_DP:
            break;

        default:
            break;
    };

    return IsAVMute;
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPGetScalingInfo()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
BYTE msAPI_combo_IPGetScalingInfo(EN_COMBO_IP_SELECT ucComboSelect)
{
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);
    BYTE ucScalingInfo = 0;

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:
        case COMBO_IP_TYPE_DUAL:
            break;

        case COMBO_IP_TYPE_HDMI:
        case COMBO_IP_TYPE_MHL:
            ucScalingInfo = mapi_tmds_GetScaling_Info(ucInputPort);
            break;

        case COMBO_IP_TYPE_DP:
            break;

        default:

            break;
    }

    return ucScalingInfo;
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPGetITContent()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
Bool msAPI_combo_IPGetITContent(EN_COMBO_IP_SELECT ucComboSelect)
{
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);
    Bool bITContent = 0;

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:
        case COMBO_IP_TYPE_DUAL:
            break;

        case COMBO_IP_TYPE_HDMI:
        case COMBO_IP_TYPE_MHL:
            bITContent = mapi_tmds_GetITContent(ucInputPort);
            break;

        case COMBO_IP_TYPE_DP:
            break;

        default:

            break;
    }

    return bITContent;
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPGetTmdsIsDVIDualLink()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
Bool msAPI_combo_IPGetTmdsIsDVIDualLink(EN_COMBO_IP_SELECT ucComboSelect)
{
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);
    Bool bIsDualLink = FALSE;

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:
            break;

        case COMBO_IP_TYPE_DUAL:
            bIsDualLink = mapi_tmds_IsDVIDualLink(ucInputPort);
            break;

        case COMBO_IP_TYPE_HDMI:
        case COMBO_IP_TYPE_MHL:
        case COMBO_IP_TYPE_DP:
            break;

        default:

            break;
    }

    return bIsDualLink;
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPGetTMDSAudioOutputState()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
EN_TMDS_AUD_STATUS msAPI_combo_IPGetTMDSAudioOutputState(EN_COMBO_IP_SELECT ucComboSelect)
{
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);
    EN_TMDS_AUD_STATUS ucAudioOutputState = COMBO_TMDS_AUDIO_STATE_OFF;

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:
        case COMBO_IP_TYPE_DUAL:
            break;

        case COMBO_IP_TYPE_HDMI:
        case COMBO_IP_TYPE_MHL:
            ucAudioOutputState = (EN_TMDS_AUD_STATUS)mapi_tmds_GetAudioOutputState(ucInputPort);
            break;

        case COMBO_IP_TYPE_DP:
            break;

        default:

            break;
    }

    return ucAudioOutputState;
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPGetHDMISourceVersion()
//  [Description]:
//
//  [Arguments]:
//
//  [Return]:  None
//
//**************************************************************************
EN_HDMI_VERSION_TYPE msAPI_combo_IPGetHDMISourceVersion(EN_COMBO_IP_SELECT ucComboSelect)
{
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);
    EN_HDMI_VERSION_TYPE enHDMISourceVersion = COMBO_HDMI_VERSION_NOT_SURE;

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:

            break;

        case COMBO_IP_TYPE_DUAL:

            break;

        case COMBO_IP_TYPE_HDMI:
            enHDMISourceVersion = (EN_HDMI_VERSION_TYPE)mapi_tmds_GetSourceVersionType(ucInputPort);
            break;

        case COMBO_IP_TYPE_MHL:

            break;

        case COMBO_IP_TYPE_DP:

            break;

        default:

            break;
    };

    return enHDMISourceVersion;
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPGetCbusMSGKeyEvent()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
BYTE msAPI_combo_IPGetCbusMSGKeyEvent(EN_COMBO_IP_SELECT ucComboSelect)
{
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);
    BYTE ucKeyEvent = MHL_MSC_MSG_KEY_EVENT_NONE;

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:
        case COMBO_IP_TYPE_DUAL:

            break;

        case COMBO_IP_TYPE_HDMI:
        case COMBO_IP_TYPE_MHL:
            ucKeyEvent = mapi_mhl_GetMSGKeyEvent(ucInputPort);
            break;

        case COMBO_IP_TYPE_DP:

            break;

        default:

            break;
    };

    return ucKeyEvent;
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPCbusSendRCPCommand()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
Bool msAPI_combo_IPCbusSendRCPCommand(EN_COMBO_IP_SELECT ucComboSelect, BYTE ucKeyCode)
{
    Bool bSendFinish = FALSE;
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:
        case COMBO_IP_TYPE_DUAL:

            break;

        case COMBO_IP_TYPE_HDMI:
        case COMBO_IP_TYPE_MHL:
            bSendFinish = mapi_mhl_SendRCPCommand(ucInputPort, ucKeyCode);
            break;

        case COMBO_IP_TYPE_DP:

            break;

        default:

            break;
    };

    return bSendFinish;
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPSetDPGuardBand()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msAPI_combo_IPSetDPGuardBand(EN_COMBO_IP_SELECT ucComboSelect, WORD usGuardBandValue)
{
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:
        case COMBO_IP_TYPE_DUAL:

            break;

        case COMBO_IP_TYPE_HDMI:
        case COMBO_IP_TYPE_MHL:

            break;

        case COMBO_IP_TYPE_DP:
            mapi_DP_SetGuardBand(ucInputPort, usGuardBandValue);
            break;

        default:

            break;
    }
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPGetDPHVInformation()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msAPI_combo_IPGetDPHVInformation(EN_COMBO_IP_SELECT ucComboSelect, WORD *usHTotalValue, WORD *usVTotalValue)
{
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:
        case COMBO_IP_TYPE_DUAL:

            break;

        case COMBO_IP_TYPE_HDMI:
        case COMBO_IP_TYPE_MHL:

            break;

        case COMBO_IP_TYPE_DP:
            mapi_DP_GetHVInformation(ucInputPort, usHTotalValue, usVTotalValue);
            break;

        default:

            break;
    }
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPGetDPInterlaceFlag()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
Bool msAPI_combo_IPGetDPInterlaceFlag(EN_COMBO_IP_SELECT ucComboSelect)
{
    BYTE ucDPVBIDValue = 0;
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:
        case COMBO_IP_TYPE_DUAL:

            break;

        case COMBO_IP_TYPE_HDMI:
        case COMBO_IP_TYPE_MHL:

            break;

        case COMBO_IP_TYPE_DP:
            ucDPVBIDValue = mapi_DP_GetInterlaceFlag(ucInputPort);
            break;

        default:

            break;
    }

    return ucDPVBIDValue;
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPGetDPAstorPTGInterlacePatch()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
Bool msAPI_combo_IPGetDPAstorPTGInterlacePatch(EN_COMBO_IP_SELECT ucComboSelect)
{
    BYTE ucDPVBIDValue = 0;
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:
        case COMBO_IP_TYPE_DUAL:

            break;

        case COMBO_IP_TYPE_HDMI:
        case COMBO_IP_TYPE_MHL:

            break;

        case COMBO_IP_TYPE_DP:
            ucDPVBIDValue = mapi_DP_GetAstorPTGInterlacePatch(ucInputPort);
            break;

        default:

            break;
    }

    return ucDPVBIDValue;
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPDPCheckIgnoreDPMS()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
Bool msAPI_combo_IPDPCheckIgnoreDPMS(EN_COMBO_IP_SELECT ucComboSelect)
{
    Bool bDPMSFlag = FALSE;
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:
        case COMBO_IP_TYPE_DUAL:

            break;

        case COMBO_IP_TYPE_HDMI:
        case COMBO_IP_TYPE_MHL:

            break;

        case COMBO_IP_TYPE_DP:
            bDPMSFlag = mapi_DP_CheckIgnoreDPMS(ucInputPort);
            break;

        default:

            break;
    }

    return bDPMSFlag;
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPSetDPVersion()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msAPI_combo_IPSetDPVersion(EN_COMBO_IP_SELECT ucComboSelect, EN_DP_VERSION ucVersion)
{
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:
        case COMBO_IP_TYPE_DUAL:

            break;

        case COMBO_IP_TYPE_HDMI:
        case COMBO_IP_TYPE_MHL:

            break;

        case COMBO_IP_TYPE_DP:
            mapi_DP_Set_Version(ucInputPort, ucVersion);
            break;

        default:

            break;
    }
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPGetDPDRRFlag()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
Bool msAPI_combo_IPGetDPDRRFlag(EN_COMBO_IP_SELECT ucComboSelect)
{
    BYTE ucDPDRREnable = FALSE;
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:
        case COMBO_IP_TYPE_DUAL:

            break;

        case COMBO_IP_TYPE_HDMI:
        case COMBO_IP_TYPE_MHL:

            break;

        case COMBO_IP_TYPE_DP:
                ucDPDRREnable = mapi_DP_GetDRRFlag(ucInputPort);
            break;

        default:

            break;
    }

    return ucDPDRREnable;
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPSetDPDRRFunction()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msAPI_combo_IPSetDPDRRFunction(EN_COMBO_IP_SELECT ucComboSelect, Bool bEnable)
{
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:
        case COMBO_IP_TYPE_DUAL:

            break;

        case COMBO_IP_TYPE_HDMI:
        case COMBO_IP_TYPE_MHL:

            break;

        case COMBO_IP_TYPE_DP:
			    mapi_DP_EnableDRRFunction(ucInputPort, bEnable);
            break;

        default:

            break;
    }
}

//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPGetDPPixelClock()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
WORD msAPI_combo_IPGetDPPixelClock(EN_COMBO_IP_SELECT ucComboSelect)
{
    WORD uwDPPixelClock = 0;
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:
        case COMBO_IP_TYPE_DUAL:

            break;

        case COMBO_IP_TYPE_HDMI:
        case COMBO_IP_TYPE_MHL:

            break;

        case COMBO_IP_TYPE_DP:
                uwDPPixelClock = mapi_DP_GetPixelClock(ucInputPort);
            break;

        default:

            break;
    }

    return uwDPPixelClock;
}
//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPDPCheckMSAChg()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
Bool msAPI_combo_IPDPCheckMSAChg(EN_COMBO_IP_SELECT ucComboSelect)
{
    Bool bMSAChgFlag = FALSE;
    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:
        case COMBO_IP_TYPE_DUAL:

            break;

        case COMBO_IP_TYPE_HDMI:
        case COMBO_IP_TYPE_MHL:

            break;

        case COMBO_IP_TYPE_DP:
            bMSAChgFlag = mapi_DP_GetMSAChgFlag(ucInputPort);
            break;

        default:

            break;
    }

    return bMSAChgFlag;
}
//**************************************************************************
//  [Function Name]:
//                  msAPI_combo_IPDPClrMSAChg()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msAPI_combo_IPDPClrMSAChg(EN_COMBO_IP_SELECT ucComboSelect)
{

    BYTE ucInputPort = mapi_combo_GetComboInputPort(ucComboSelect);
    EN_COMBO_IP_TYPE ucComboIPType = mapi_combo_GetComboType(ucComboSelect);

    switch(ucComboIPType)
    {
        case COMBO_IP_TYPE_DVI:
        case COMBO_IP_TYPE_DUAL:

            break;

        case COMBO_IP_TYPE_HDMI:
        case COMBO_IP_TYPE_MHL:

            break;

        case COMBO_IP_TYPE_DP:
           		mapi_DP_ClrMSAChgFlag(ucInputPort);
            break;

        default:

            break;
    }
}
#endif
#endif

