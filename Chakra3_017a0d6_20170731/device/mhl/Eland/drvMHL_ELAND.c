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
///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// file    mdrv_mhl.c
/// @author MStar Semiconductor Inc.
/// @brief  MHL driver Function
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_MHL_ELAND_C_
#define _DRV_MHL_ELAND_C_

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
// Common Definition
#include "MsCommon.h"
#include "MsVersion.h"
#ifdef MSOS_TYPE_LINUX_KERNEL
#include <linux/string.h>
#else
#include <string.h>
#endif

#include "drvMHL_ELAND_st.h"
#include "drvMHL_ELAND.h"
#include "halMHL_ELAND.h"


MS_BOOL g_bIsMHLCableDetect = TRUE;

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------

#define msg_mhl(x) x

//-------------------------------------------------------------------------------------------------
//  Local Structures
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------
#if 1
static MS_U8 MhlDevCap_tbl[16] =
{
    0x00,    //DEV_STATE
    0x12,    //MHL_VERSION, 1.2
    0x11,    //DEV_CAT, [4]:POW, [3:0]:DEV_TYPE
    (DMHL_ADOPTER_ID>>8),    // ADOPTER_ID_H, Mstar adopter ID 715(0x2CB)
    (DMHL_ADOPTER_ID&0xFF),    // ADOPTER_ID_L
#if DMHL_CTS // not support packed-pixel mode
    0x37,    // VID_LINK_MODE, [5]:SUPP_VGA, [4]:ISLANDS, [3]:PPIXEL, [2]:YUV422, [1]:YUV444, [0]:RGB444
#else
    0x3F,    // VID_LINK_MODE, [5]:SUPP_VGA, [4]:ISLANDS, [3]:PPIXEL, [2]:YUV422, [1]:YUV444, [0]:RGB444
#endif
    0x01,    // AUD_LINK_MODE, [1]:AUD_8CH, [0]:AUD_2CH
    0x00,    // VIDEO_TYPE, [7]: SUPP_VT, [3]:GAME, [2]:CINEMA, [1]: PHOTO, [0]:GRAPHICS
    0x01,    // LOG_DEV_MAP, [0]:LD_DISPLAY
    0x0F,    // BANDWIDTH, 15*5MHz = 75MHz
    0x07,    // FEATURE_FLAG, [2]:Scratchpad, [1]:RAP, [0]:RCP
    (DMHL_DEVICE_ID>>8),    // DEVICE_ID_H, ? CHIP_ID
    (DMHL_DEVICE_ID&0xFF),    // DEVICE_ID_L, ? CHIP_ID
    //0x10,    // SCRATCHPAD_SIZE, 16 bytes
    MHL_MSC_SCRATCHPAD_SIZE,    // SCRATCHPAD_SIZE, 16 bytes
    0x33,    // INT_STAT_SIZE, [7:4]:Status 4 bytes, [3:0]:Interrupt 4 bytes
    0x00,    // Reserved
};
#endif

//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Global Functions
//-------------------------------------------------------------------------------------------------

//**************************************************************************
//  [Function Name]:
//                  mdrv_mhl_MHLSupportPath()
//  [Description]
//                  MHL support path
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_mhl_MHLSupportPath(MS_U8 ucSelect)
{
    mhal_mhl_MHLSupportPath(ucSelect);
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_mhl_init()
//  [Description]
//                  MHL init
//  [Arguments]:
//                  *edid: MHL EDID data
//                  *devcap: MHL device capability
//  [Return]:
//
//**************************************************************************
void mdrv_mhl_init(MS_U8 *edid, MS_U8 *DevCap)
{
    MS_U8 uctemp = 0;

    mhal_mhl_init(edid, DevCap);

    for(uctemp = 0; uctemp < MHL_DEVICE_CAPABILITY_SIZE; uctemp++)
    {
        MhlDevCap_tbl[uctemp] = DevCap[uctemp];
    }
}

void mdrv_mhl_LoadDevCap(MS_U8 *u8devcap)
{
    mhal_mhl_LoadDevCap(u8devcap);
}

#if 1
//extern void mhal_mhl_Set_IIC_16BMode(void);
void mdrv_mhl_Set_IIC_16BMode(void)
{
    mhal_mhl_Set_IIC_16BMode();
}
#endif

//**************************************************************************
//  [Function Name]:
//                  mdrv_mhl_CableDetect()
//  [Description]
//                  MHL cable detection
//  [Arguments]:
//
//  [Return]:
//                  TRUE: MHL cable plugged
//                  FALSE: MHL cable unplugged
//**************************************************************************
MS_BOOL mdrv_mhl_CableDetect(void)
{
    return mhal_mhl_CableDetect();
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_mhl_CbusIsMscMsgReceived()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//                  TRUE:
//                  FALSE:
//**************************************************************************
MS_BOOL mdrv_mhl_CbusIsMscMsgReceived(void)
{
    return mhal_mhl_CbusIsMscMsgReceived();
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_mhl_DriverControl()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_mhl_CbusIntCB(CbusReq_S *preq, MS_BOOL *bflag)
{
    mhal_mhl_CbusIntCB(&(preq->rcState), &(preq->cmd), &(preq->msgData[0]), &(preq->len), bflag);
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_mhl_GetDevCap
//  [Description]
//                  ucIndex: 0~15
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************

//Aldrich ToDo
MS_U8 mdrv_mhl_GetDevCap(MS_U8 ucIndex)
{
    //return mhal_mhl_GetDevCap(ucIndex);

    return (MhlDevCap_tbl[ucIndex]);
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_mhl_GetDDCErrorCode
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
MS_U8 mdrv_mhl_GetDDCErrorCode(void)
{
    return (mhal_mhl_GetDDCErrorCode());
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_mhl_CbusStatus()
//  [Description]:
//                  MHL Cbus status
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
MS_U16 mdrv_mhl_CbusStatus(void)
{
    return (mhal_mhl_CbusStatus());
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_mhl_Cbus_SetPathEn()
//  [Description]:
//                  MHL Cbus status
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_mhl_Cbus_SetPathEn(MS_BOOL bFlag)
{
    mhal_mhl_Cbus_SetPathEn(bFlag);
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_mhl_DriverControl()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_mhl_DriverControl(MS_U8 ucState)
{
    switch(ucState)
    {
        case MHL_CABLE_PLUGGED:
            mhal_mhl_LoadMhl24bitsModeTbl();
            //mhal_mhl_MHLForceToStandby();
            //SET_MHL_PS_CTRL_LO(); // set VBUS to high
            mhal_mhl_RxRtermControl(RX_RTERM_OFF);

#if(DMHL_LG_PRADA_PATCH)
            mhal_mhl_AdjustCommonModeResistor(TRUE);
#endif

            break;

        case MHL_CABLE_UNPLUGGED:
            //mhal_mhl_MHLForceToStandby();
            //SET_MHL_PS_CTRL_HI(); // set VBUS to low
            mhal_mhl_LoadHdmiBypassTbl();
            mhal_mhl_RxRtermControl(RX_HDMI_RTERM);

            break;

        case MHL_CBUS_UNCONNECTION:
            //mhal_mhl_MHLForceToStandby();
            //SET_MHL_PS_CTRL_HI(); // set VBUS to low
            mhal_mhl_RxRtermControl(RX_RTERM_OFF);

#if(DMHL_LG_PRADA_PATCH)
            mhal_mhl_AdjustCommonModeResistor(TRUE);
#endif
            break;

        case MHL_CBUS_CONNECTION:
            //SET_MHL_PS_CTRL_LO(); // set VBUS to high
            mhal_mhl_RxRtermControl(RX_MHL_RTERM);
            //mhal_mhl_LoadMhl24bitsModeTbl();

#if(DMHL_LG_PRADA_PATCH)
            mhal_mhl_AdjustCommonModeResistor(FALSE);
#endif

            break;

        case MHL_CBUS_PM_MODE:
#if(DMHL_WAKE_UP_PULSE_INT)
            mhal_mhl_MHLForceToStandby();
            mhal_mhl_ClearWakeupIntFlag();
#endif

            break;

        case MHL_CBUS_NORMAL_24BIT_MODE:
            mhal_mhl_LoadMhl24bitsModeTbl();
            break;

        case MHL_CBUS_PACKET_PIXEL_MODE:
            mhal_mhl_LoadMhlPackedPixelModeTbl();
            break;

#if(DMHL_TEST_SIGNAL_SUPPORT)
        case MHL_CBUS_TEST_RASING:
            mhal_mhl_TestSignal(FALSE);
            break;

        case MHL_CBUS_TEST_FALLING:
            mhal_mhl_TestSignal(TRUE);
            break;

#endif

        default:

            break;
    }
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_mhl_CbusSetPacket(BYTE ucHeader, Bool bControl, BYTE ucContent)
//  [Description]
//                  MHL Cbus Packet setting
//  [Arguments]:
//                  ucHeader: Packet header type
//                  bControl: Packet control bit type
//                  ucContent: Packet payload
//  [Return]:
//                  Packet word for register write
//**************************************************************************
MS_U16 _mdrv_mhl_CbusSetPacket(MS_U8 ucHeader, MS_BOOL bControl, MS_U8 ucContent)
{
    MS_BOOL bParity = 0;
    MS_U16 usPacket = (ucHeader <<9) |(bControl <<8) |ucContent;

    do
    {
        bParity ^= (usPacket & BIT(0));
        usPacket = usPacket >>1;
    }
    while(usPacket);

    usPacket = (bParity <<11) |(ucHeader <<9) |(bControl <<8) |ucContent;

    return (usPacket |BIT(15));
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_mhl_CbusReply
//  [Description]
//                  MHL Cbus Response
//  [Arguments]:
//                  ctrlpky: ACK / NACK / ABORT
//                  bflag: TRUE means ACK with Tx required data. Use in "MSC_READ_DEVCAP", "MSC_GET_STATE" and "MSC_GET_VENDOR_ID"
//                  databuf: Tx required data
//  [Return]:
//                  TRUE: success
//                  FALSE: fail
//**************************************************************************
MS_BOOL mdrv_mhl_CbusReply (MS_U8 ctrlpky, MS_BOOL bflag, MS_U8 databuf)
{
    MS_BOOL bIndex = TRUE;
    mhalCbusFifo_S pCbusFifo;

    switch(ctrlpky)
    {
        case MSC_ACK:
            pCbusFifo.lens = bflag ? 2 : 1;
            pCbusFifo.databuf[0] = _mdrv_mhl_CbusSetPacket(MSC_HEADER, CBUS_CONTROL, MSC_ACK);

            if(bflag)
            {
                pCbusFifo.databuf[1] = _mdrv_mhl_CbusSetPacket(MSC_HEADER, CBUS_DATA, databuf);
            }

            break;

        case MSC_NACK:
            pCbusFifo.lens = 1;
            pCbusFifo.databuf[0] = _mdrv_mhl_CbusSetPacket(MSC_HEADER, CBUS_CONTROL, MSC_NACK);

            break;

        case MSC_ABORT:
            pCbusFifo.lens = 1;
            pCbusFifo.databuf[0] = _mdrv_mhl_CbusSetPacket(MSC_HEADER, CBUS_CONTROL, MSC_ABORT);

            break;

        case MSC_GET_STATE:
        case MSC_GET_VENDOR_ID:
        case MSC_GET_DDC_ERRORCODE:
        case MSC_GET_MSC_ERRORCODE:
            pCbusFifo.lens = 1;
            pCbusFifo.databuf[0] = _mdrv_mhl_CbusSetPacket(MSC_HEADER, CBUS_DATA, databuf);

            break;

        default:
            bIndex = FALSE;
            break;
    }

    if(!mhal_mhl_CBusWrite(&pCbusFifo))
    {
        msg_mhl(printf("@@Cbus Tx is busy = 0x%x", ctrlpky));
        return FALSE;
    }

    return bIndex;
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_mhl_CBusWriteCmd()
//  [Description]:
//                  MHL Cbus send command
//  [Arguments]:
//
//  [Return]:
//                  TRUE: Cbus command send successfully
//                  FALSE: Cbus command send fail
//**************************************************************************
MS_BOOL mdrv_mhl_CBusWriteCmd(CbusReq_S *pReq)
{
    MS_BOOL bIndex = TRUE;
    MS_U8 uctemp = 0;
    mhalCbusFifo_S pCbusFifo;

    pCbusFifo.databuf[0] = _mdrv_mhl_CbusSetPacket(MSC_HEADER, CBUS_CONTROL, pReq->cmd);

    switch (pReq->cmd)
    {
        case MSC_ACK:
            pCbusFifo.lens = pReq->len;
            //pCbusFifo.databuf[0] = _mdrv_mhl_CbusSetPacket(MSC_HEADER, CBUS_CONTROL, MSC_ACK);

            if(pReq->len == 2)
            {
                // payload 2
                pCbusFifo.databuf[1] = _mdrv_mhl_CbusSetPacket(MSC_HEADER, CBUS_DATA, pReq->msgData[0]);
            }
            break;

        case MSC_NACK:
            pCbusFifo.lens = 1;
            //pCbusFifo.databuf[0] = _mdrv_mhl_CbusSetPacket(MSC_HEADER, CBUS_CONTROL, MSC_NACK);
            break;

        case MSC_ABORT:
            pCbusFifo.lens = 1;
            //pCbusFifo.databuf[0] = _mdrv_mhl_CbusSetPacket(MSC_HEADER, CBUS_CONTROL, MSC_ABORT);
            break;

        case MSC_WRITE_STAT_OR_SET_INT:   // 0x60
            // payload 1
            //pCbusFifo.databuf[0] = _mdrv_mhl_CbusSetPacket(MSC_HEADER, CBUS_CONTROL, MSC_WRITE_STAT_OR_SET_INT);
            // payload 2
            pCbusFifo.databuf[1] = _mdrv_mhl_CbusSetPacket(MSC_HEADER, CBUS_DATA, pReq->msgData[0]);
            // payload 3
            pCbusFifo.databuf[2] = _mdrv_mhl_CbusSetPacket(MSC_HEADER, CBUS_DATA, pReq->msgData[1]);
            // message length
            pCbusFifo.lens = 3;
            break;

        case MSC_READ_DEVCAP:   // 0x61
            // payload 1
            //pCbusFifo.databuf[0] = _mdrv_mhl_CbusSetPacket(MSC_HEADER, CBUS_CONTROL, MSC_READ_DEVCAP);
            // payload 2
            pCbusFifo.databuf[1] = _mdrv_mhl_CbusSetPacket(MSC_HEADER, CBUS_DATA, pReq->msgData[0]);
            // message length
            pCbusFifo.lens = 2;
            break;

        case MSC_GET_STATE:          // 0x62
        case MSC_GET_VENDOR_ID:      // 0x63
        case MSC_SET_HPD:            // 0x64
        case MSC_CLR_HPD:            // 0x65
        case MSC_GET_SC1_ERRORCODE:      // 0x69 - Get channel 1 command error code
        case MSC_GET_DDC_ERRORCODE:      // 0x6A - Get DDC channel command error code.
        case MSC_GET_MSC_ERRORCODE:      // 0x6B - Get MSC command error code.
        case MSC_GET_SC3_ERRORCODE:      // 0x6D - Get channel 3 command error code.
            // payload 1
            //pCbusFifo.databuf[0] = _mdrv_mhl_CbusSetPacket(MSC_HEADER, CBUS_CONTROL, pReq->cmd);
            // message length
            pCbusFifo.lens = 1;
            break;

        case MSC_MSC_MSG: // 0x68
            // payload 1
            //pCbusFifo.databuf[0] = _mdrv_mhl_CbusSetPacket(MSC_HEADER, CBUS_CONTROL, MSC_MSC_MSG);
            // payload 2
            pCbusFifo.databuf[1] = _mdrv_mhl_CbusSetPacket(MSC_HEADER, CBUS_DATA, pReq->msgData[0]);
            // payload 3
            pCbusFifo.databuf[2] = _mdrv_mhl_CbusSetPacket(MSC_HEADER, CBUS_DATA, pReq->msgData[1]);
            // message length
            pCbusFifo.lens = 3;
            break;

        case MSC_WRITE_BURST: // 0x6C
            // payload 1
            //pCbusFifo.databuf[0] = _mdrv_mhl_CbusSetPacket(MSC_HEADER, CBUS_CONTROL, MSC_WRITE_BURST);
            // payload 2 ~ 17
            for(uctemp =0; uctemp <pReq->len; uctemp++) // offset packet + the maxi 16 packets
            {
                pCbusFifo.databuf[uctemp +1] = _mdrv_mhl_CbusSetPacket(MSC_HEADER, CBUS_DATA, pReq->msgData[uctemp]);
            }
            // EOF
            pCbusFifo.databuf[pReq->len +1] = _mdrv_mhl_CbusSetPacket(MSC_HEADER, CBUS_CONTROL, MSC_EOF);
            // message length
            pCbusFifo.lens = pReq->len +2;
            break;

        default:
            bIndex = FALSE;
            break;
    }

    if(bIndex)
    {
        if(!mhal_mhl_CBusWrite(&pCbusFifo))
        {
            //msg_mhl(printf("@@Cbus Tx is busy = 0x%x\r\n", pReq->cmd));
            return FALSE;
        }
        //gMHLInfo.MhlCbusInfo.timeout = CBUS_COMMAND_TIMEOUT_SECS*1000/DEM_POLLING_DELAY; // timeout reset.
    }

    return bIndex;
}

//**************************************************************************
//  [Function Name]:
//                  _mdrv_mhl_CBusClockModeSwitch()
//  [Description]:
//                  MHL Cbus clock mode select
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_mhl_CBusClockModeSwitch(MS_U8 ucSelect)
{
    switch(ucSelect)
    {
        case CBUS_CLOCK_PACKET_PIXEL:
            mdrv_mhl_DriverControl(MHL_CBUS_PACKET_PIXEL_MODE);
            break;

        case CBUS_CLOCK_NORMAL_24BIT:
            mdrv_mhl_DriverControl(MHL_CBUS_NORMAL_24BIT_MODE);
            break;

        default:

            break;
    };
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_mhl_CBusCheckBCHError()
//  [Description]:
//                  MHL Cbus check BCH error
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
MS_BOOL mdrv_mhl_CBusStablePolling(MS_BOOL bFlag)
{
    if(mhal_mhl_CDRModeMonitor(bFlag))
    {
        bFlag = mhal_mhl_CBusCheckBCHError();
    }
    else
    {
        bFlag = FALSE;
    }

    return bFlag;
}

// config HPD in combo(MHL/HDMI) port C
void mdrv_mhl_SetHPD(MS_BOOL bflag)
{
    mhal_mhl_SetHPD(bflag);
}

// MHL power control
//E_MHL_POWER_ON
void mdrv_mhl_PowerOn(void)
{
    mhal_mhl_RxRtermControl(RX_HDMI_RTERM);
    mhal_mhl_LoadPowerOnTbl();
}

//E_MHL_POWER_STANDBY
void mdrv_mhl_PowerStandby(MS_BOOL bFlag)
{
    mhal_mhl_MHLForceToStandby();
    mhal_mhl_RxRtermControl(bFlag ? RX_RTERM_OFF: RX_MHL_RTERM);
    mhal_mhl_LoadPowerStandbyTbl();
}

//E_MHL_POWER_DOWN
void mdrv_mhl_PowerDown(void)
{
    mhal_mhl_MHLForceToStandby();
    mhal_mhl_RxRtermControl(RX_RTERM_OFF);
    mhal_mhl_LoadPowerDownTbl();
}

MS_BOOL mdrv_mhl_WakeupDetect(void)
{
    if(mdrv_mhl_CableDetect()) // MHL
    {
        return (((mhal_mhl_CbusStatus() & 0x03) == 0x03) ? TRUE : FALSE);
    }
    else // HDMI
    {
        return ((mhal_mhl_GetTMDSClk() >= 0x30) ? TRUE : FALSE);
    }
}

void mdrv_mhl_SetPsCtrl(MS_U8 u8Ctrl)
{
    mhal_mhl_SetPsCtrl(u8Ctrl);
}

void mdrv_mhl_SetPsCtrl_HDMImode(MS_U8 u8Ctrl)
{
    mhal_mhl_SetPsCtrl_HDMImode(u8Ctrl);
}

void mdrv_mhl_LoadHdmiBypassTbl(void)
{
    mhal_mhl_LoadHdmiBypassTbl();
}

void mdrv_mhl_LoadMhl24bitsModeTbl(void)
{
    mhal_mhl_LoadMhl24bitsModeTbl();
}

void mdrv_mhl_LoadMhlPackedPixelModeTbl(void)
{
    mhal_mhl_LoadMhlPackedPixelModeTbl();
}

void mdrv_mhl_CbusIsolate(MS_BOOL bFlag)
{
    mhal_mhl_CbusIsolate(bFlag);
}

void mdrv_mhl_CbusFloating(MS_BOOL bFlag)
{
    mhal_mhl_CbusFloating(bFlag);
}

void mdrv_mhl_RxRtermControl(RXRtermControl_T rctrl)
{
    mhal_mhl_RxRtermControl(rctrl);
}

void mdrv_mhl_RxRtermIsolate(void)
{
    mhal_mhl_RxRtermControl(RX_RTERM_OFF);
}

void mdrv_mhl_RegisterCallBackFunctions(link_mhl_reg_i_func_b pfnRead, link_mhl_reg_o_func_b pfnWrite)
{
    mhal_mhl_RegisterCallBackFunctions(pfnRead, pfnWrite);
}

void mdrv_mhl_I2C_Channel_Settings(MS_U16 u16Channel, MS_U8 u8CommonID, MS_U8 u8ConfigID)
{
    mhal_mhl_I2C_Channel_Settings(u16Channel, u8CommonID, u8ConfigID);
}

void mdrv_mhl_TxSwap_Settings(MS_BOOL bTxSwapEnable)
{
    mhal_mhl_TxSwap_Settings(bTxSwapEnable);
}

void mdrv_mhl_Write2bytes(MS_U16 reg, MS_U16 val)
{
    msWriteWord(reg,val);
}
MS_U16 mdrv_mhl_Read2bytes(MS_U16 reg)
{
    return msReadWord(reg);
}

#endif // _DRV_MHL_ELAND_C_

