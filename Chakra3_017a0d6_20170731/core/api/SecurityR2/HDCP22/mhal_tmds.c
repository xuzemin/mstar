///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// file    mhal_tmds.c
/// @author MStar Semiconductor Inc.
/// @brief  TMDS driver Function
///////////////////////////////////////////////////////////////////////////////////////////////////

//#ifndef _MHAL_TMDS_C_
//#define _MHAL_TMDS_C_

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
#include "Board.h"

#if( ENABLE_SECURITY_R2_HDCP22 )

#include <string.h>

#include "datatype.h"
#include "MsOS.h"
#include "debug.h"

#include "msReg.h"
#include "drvGlobal.h"

#include "mhal_tmds.h"
#include "mapi_tmds.h"
//#include "msEread.h"

#include "msAPI_Global.h"



#define TMDS_DEBUG    0
#if ENABLE_MSTV_UART_DEBUG && TMDS_DEBUG
#define TMDS_PRINT(format, ...)     printf(format, ##__VA_ARGS__)
#else
#define TMDS_PRINT(format, ...)
#endif

#if 0
static WORD wPreviousTiming = 0;
static BYTE bPreviousPort = MSCombo_TMDS_PORT_MAX + 1; //make sure even port 0 will setting EQ for first time ISR
static BYTE bCurrentPort = MSCombo_TMDS_PORT_2;
static Bool bOver3GFlag[MSCombo_TMDS_PORT_MAX];
static Bool bSplitterDone[MSCombo_TMDS_PORT_MAX];
static BYTE bAutoEQRetry[MSCombo_TMDS_PORT_MAX];
static Bool bAutoEQCntRst[MSCombo_TMDS_PORT_MAX];
static Bool bAutoEQDone[MSCombo_TMDS_PORT_MAX];
static Bool bMHLCable[MSCombo_TMDS_PORT_MAX];
BYTE ucEfuseValuePort2Lane0 = 0;
BYTE ucEfuseValuePort2Lane1 = 0;
BYTE ucEfuseValuePort2Lane2 = 0;
BYTE ucEfuseValuePort3Lane0 = 0;
BYTE ucEfuseValuePort3Lane1 = 0;
BYTE ucEfuseValuePort3Lane2 = 0;
#endif

#if 0
//**************************************************************************
//  [Function Name]:
//                  _mhal_tmds_phy_offset()
//  [Description]:
//                  use to get combo_phy_top offset
//  [Arguments]:
//                  enInputPort : combo port
//  [Return]:
//                  combo_phy_top bank offset
//**************************************************************************
WORD _mhal_tmds_phy_offset(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    WORD wOffset;

    switch(enInputPort)
    {
        default:
        case MSCombo_TMDS_PORT_0:
            wOffset = 0x0000;
            break;
        case MSCombo_TMDS_PORT_1:
            wOffset = 0x0200;
            break;
        case MSCombo_TMDS_PORT_2:
        case MSCombo_TMDS_PORT_3:
            wOffset = 0x0400;
            break;
    }

    return wOffset;

}

//**************************************************************************
//  [Function Name]:
//                  _mhal_tmds_UpdateCTSNValue()
//  [Description]:
//                  update CTS/N value and configure its limit value to setup upper/lower bound
//  [Arguments]:
//                  MSCombo_TMDS_PORT_INDEX enInputPort
//  [Return]:
//                  none
//**************************************************************************
void _mhal_tmds_UpdateCTSNValue(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    if(enInputPort == MSCombo_TMDS_PORT_0)
    {
        //load current CTS/N value first
        msWrite2ByteMask(REG_160524, 0xFFFF, 0xFFFF);
        msWrite2ByteMask(REG_160526, 0xFFFF, 0xFFFF);
        MDrv_WriteByteMask(REG_160528, 0xFF, 0xFF);

        //update CTS value
        MDrv_Write2Byte(REG_160514, MDrv_Read2Byte(REG_160524)); //CTS0, [15..0]
        MDrv_WriteByteMask(REG_160513, (MDrv_ReadByte(REG_160528) & 0x0F), 0x0F); //CTS1, b[11..8]

        //update N value
        MDrv_Write2Byte(REG_160516 , MDrv_Read2Byte(REG_160526)); //N0, [15..0]
        MDrv_WriteByteMask(REG_160513, (MDrv_ReadByte(REG_160528) & 0xF0), 0xF0); //N1, b[11..8]

        //disable CTS/N filter
        MDrv_WriteByteMask(REG_16050F , 0x00, 0x40);

        //setup CTS/N range
        MDrv_Write2Byte(REG_160518, 0x1414 ); //[15:8]: N range, [7:0]: CTS range

        //upload new CTS/N value
        MDrv_WriteByteMask(REG_16050F, 0x80, 0x80);

        //enable CTS/N filter
        MDrv_WriteByteMask(REG_16050F, 0x40, 0x40);
    }
    else if(enInputPort == MSCombo_TMDS_PORT_1)
    {
        //load current CTS/N value first
        msWrite2ByteMask(REG_160A24, 0xFFFF, 0xFFFF);
        msWrite2ByteMask(REG_160A26, 0xFFFF, 0xFFFF);
        MDrv_WriteByteMask(REG_160A28, 0xFF, 0xFF);

        //update CTS value
        MDrv_Write2Byte(REG_160A14, MDrv_Read2Byte(REG_160A24)); //CTS0, [15..0]
        MDrv_WriteByteMask(REG_160A13, (MDrv_ReadByte(REG_160A28) & 0x0F), 0x0F); //CTS1, b[11..8]

        //update N value
        MDrv_Write2Byte(REG_160A16 , MDrv_Read2Byte(REG_160A26)); //N0, [15..0]
        MDrv_WriteByteMask(REG_160A13, (MDrv_ReadByte(REG_160A28) & 0xF0), 0xF0); //N1, b[11..8]

        //disable CTS/N filter
        MDrv_WriteByteMask(REG_160A0F , 0x00, 0x40);

        //setup CTS/N range
        MDrv_Write2Byte(REG_160A18, 0x1414 ); //[15:8]: N range, [7:0]: CTS range

        //upload new CTS/N value
        MDrv_WriteByteMask(REG_160A0F, 0x80, 0x80);

        //enable CTS/N filter
        MDrv_WriteByteMask(REG_160A0F, 0x40, 0x40);
    }
    else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
    {
        //load current CTS/N value first
        msWrite2ByteMask(REG_161124, 0xFFFF, 0xFFFF);
        msWrite2ByteMask(REG_161126, 0xFFFF, 0xFFFF);
        MDrv_WriteByteMask(REG_161128, 0xFF, 0xFF);

        //update CTS value
        MDrv_Write2Byte(REG_161114, MDrv_Read2Byte(REG_161124)); //CTS0, [15..0]
        MDrv_WriteByteMask(REG_161113, (MDrv_ReadByte(REG_161128) & 0x0F), 0x0F); //CTS1, b[11..8]

        //update N value
        MDrv_Write2Byte(REG_161116 , MDrv_Read2Byte(REG_161126)); //N0, [15..0]
        MDrv_WriteByteMask(REG_161113, (MDrv_ReadByte(REG_161128) & 0xF0), 0xF0); //N1, b[11..8]

        //disable CTS/N filter
        MDrv_WriteByteMask(REG_16110F , 0x00, 0x40);

        //setup CTS/N range
        MDrv_Write2Byte(REG_161118, 0x1414 ); //[15:8]: N range, [7:0]: CTS range

        //upload new CTS/N value
        MDrv_WriteByteMask(REG_16110F, 0x80, 0x80);

        //enable CTS/N filter
        MDrv_WriteByteMask(REG_16110F, 0x40, 0x40);
    }


}

//**************************************************************************
//  [Function Name]:
//                  _mhal_tmds_SetCbusPullDown100K()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void _mhal_tmds_SetCbusPullDown100K(MSCombo_TMDS_PORT_INDEX enPortSelect, Bool bSetFlag)
{
    switch(enPortSelect)
    {
        case MSCombo_TMDS_PORT_0:
            MDrv_WriteByteMask(REG_002F40, bSetFlag? BIT7: 0, BIT7); // REG_PM_MHL_CBUS0_20[7], Cbus pull down 100K port0
            break;

        case MSCombo_TMDS_PORT_1:
            MDrv_WriteByteMask(REG_003140, bSetFlag? BIT7: 0, BIT7); // REG_PM_MHL_CBUS1_20[7], Cbus pull down 100K port1
            break;

        case MSCombo_TMDS_PORT_2:
            MDrv_WriteByteMask(REG_003340, bSetFlag? BIT7: 0, BIT7); // REG_PM_MHL_CBUS2_20[7], Cbus pull down 100K port2
            break;

        case MSCombo_TMDS_PORT_3:
            MDrv_WriteByteMask(REG_003540, bSetFlag? BIT7: 0, BIT7); // REG_PM_MHL_CBUS3_20[7], Cbus pull down 100K port3
            break;

        default:

            break;
    };
}

//**************************************************************************
//  [Function Name]:
//                  _mhal_tmds_AutoEQDoneInterrupt()
//  [Description]:
//                  use to check autoEQ done or not
//  [Arguments]:
//                  enInputPort : combo port
//  [Return]:
//                  TRUE : done
//                  FALSE : no done
//**************************************************************************
Bool _mhal_tmds_AutoEQDoneInterrupt(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
    {
        if(MDrv_ReadByte(REG_112580) & 0x80) // autoEQ done
        {
            MDrv_WriteByte(REG_112583, 0x80); //clr
            MDrv_WriteByte(REG_112583, 0x00);
            MDrv_WriteByte(REG_112583, 0x00);
            return TRUE;
        }
        else
            return FALSE;
    }
    else
        return FALSE;
}

//**************************************************************************
//  [Function Name]:
//                  _mhal_tmds_GetEfuseSettingValue()
//  [Description]:
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void _mhal_tmds_GetEfuseSettingValue(void)
{
    ucEfuseValuePort2Lane0 = msEread_GetDataFromEfuse(EFUSE_0, TMDS_PHY_EFUSE_ADDRESS0);
    ucEfuseValuePort2Lane1 = msEread_GetDataFromEfuse(EFUSE_0, TMDS_PHY_EFUSE_ADDRESS1);
    ucEfuseValuePort2Lane2 = msEread_GetDataFromEfuse(EFUSE_0, TMDS_PHY_EFUSE_ADDRESS2);
    ucEfuseValuePort3Lane0 = msEread_GetDataFromEfuse(EFUSE_0, TMDS_PHY_EFUSE_ADDRESS3);
    ucEfuseValuePort3Lane1 = msEread_GetDataFromEfuse(EFUSE_0, TMDS_PHY_EFUSE_ADDRESS4);
    ucEfuseValuePort3Lane2 = msEread_GetDataFromEfuse(EFUSE_0, TMDS_PHY_EFUSE_ADDRESS5);
}

//**************************************************************************
//  [Function Name]:
//                  _mhal_tmds_SetEfuseSettingValue()
//  [Description]:
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void _mhal_tmds_SetEfuseSettingValue(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bHDMI20Flag)
{
    switch(enInputPort)
    {
        case MSCombo_TMDS_PORT_2:
            if(ucEfuseValuePort2Lane0 &BIT7)
            {
                MDrv_WriteByteMask(REG_1124C0, bHDMI20Flag? 0: BIT7, BIT7); // REG_COMBO_PHY4_60[7]
                MDrv_WriteByteMask(REG_1124C2, bHDMI20Flag? 0: BIT7, BIT7); // REG_COMBO_PHY4_61[7]
                MDrv_WriteByteMask(REG_1124C3, bHDMI20Flag? 0: BIT7, BIT7); // REG_COMBO_PHY4_62[7]
                msWrite2ByteMask(REG_1124FC, bHDMI20Flag? 0: (WORD)((ucEfuseValuePort2Lane1 << 6)| ucEfuseValuePort2Lane0), BITMASK(11:0)); // REG_COMBO_PHY4_7E[11:6][5:0]
                MDrv_WriteByteMask(REG_1124FD, bHDMI20Flag? 0: (ucEfuseValuePort2Lane2 << 4), BITMASK(7:4)); // REG_COMBO_PHY4_7E[15:12]
                MDrv_WriteByteMask(REG_1124FE, bHDMI20Flag? 0: ucEfuseValuePort2Lane2, BITMASK(1:0)); // REG_COMBO_PHY4_7F[1:0]
            }

            break;

        case MSCombo_TMDS_PORT_3:
            if(ucEfuseValuePort3Lane0 &BIT7)
            {
                MDrv_WriteByteMask(REG_1124C0, bHDMI20Flag? 0: BIT7, BIT7); // REG_COMBO_PHY4_60[7]
                MDrv_WriteByteMask(REG_1124C2, bHDMI20Flag? 0: BIT7, BIT7); // REG_COMBO_PHY4_61[7]
                MDrv_WriteByteMask(REG_1124C3, bHDMI20Flag? 0: BIT7, BIT7); // REG_COMBO_PHY4_62[7]
                msWrite2ByteMask(REG_1124FC, bHDMI20Flag? 0: (WORD)((ucEfuseValuePort3Lane1 << 6)| ucEfuseValuePort3Lane0), BITMASK(11:0)); // REG_COMBO_PHY4_7E[11:6][5:0]
                MDrv_WriteByteMask(REG_1124FD, bHDMI20Flag? 0: (ucEfuseValuePort3Lane2 << 4), BITMASK(7:4)); // REG_COMBO_PHY4_7E[15:12]
                MDrv_WriteByteMask(REG_1124FE, bHDMI20Flag? 0: ucEfuseValuePort3Lane2, BITMASK(1:0)); // REG_COMBO_PHY4_7F[1:0]
            }

            break;

        default:

            break;
    };
}

//**************************************************************************
//  [Function Name]:
//                  _mhal_tmds_SetNoInputInterrupt()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void _mhal_tmds_SetNoInputInterrupt(MSCombo_TMDS_PORT_INDEX enPortSelect, Bool bEnable)
{
    switch(enPortSelect)
    {
        case MSCombo_TMDS_PORT_0:
            MDrv_WriteByteMask(REG_112181, bEnable? 0: BIT3, BIT3); // REG_COMBO_PHY1_40[11], No input mask port0
            MDrv_WriteByteMask(REG_112183, BIT3, BIT3); // REG_COMBO_PHY1_41[13], No input clear port0
            MDrv_WriteByteMask(REG_112183, 0, BIT3); // REG_COMBO_PHY1_41[13], No input clear port0
            break;

        case MSCombo_TMDS_PORT_1:
            MDrv_WriteByteMask(REG_112381, bEnable? 0: BIT3, BIT3); // REG_COMBO_PHY3_40[11], No input mask port1
            MDrv_WriteByteMask(REG_112383, BIT3, BIT3); // REG_COMBO_PHY3_41[11], No input clear port1
            MDrv_WriteByteMask(REG_112383, 0, BIT3); // REG_COMBO_PHY3_41[11], No input clear port1
            break;

        case MSCombo_TMDS_PORT_2:
        case MSCombo_TMDS_PORT_3:
            MDrv_WriteByteMask(REG_112581, bEnable? 0: BIT3, BIT3); // REG_COMBO_PHY5_40[11], No input mask port2&3
            MDrv_WriteByteMask(REG_112583, BIT3, BIT3); // REG_COMBO_PHY5_41[11], No input clear port2&3
            MDrv_WriteByteMask(REG_112583, 0, BIT3); // REG_COMBO_PHY5_41[11], No input clear port2&3
            break;

        default:

            break;
    };
}

//**************************************************************************
//  [Function Name]:
//                  _mhal_tmds_SetClockValidInterrupt()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void _mhal_tmds_SetClockValidInterrupt(MSCombo_TMDS_PORT_INDEX enPortSelect, Bool bEnable)
{
    switch(enPortSelect)
    {
        case MSCombo_TMDS_PORT_0:
            MDrv_WriteByteMask(REG_112181, bEnable? 0: BIT1, BIT1); // REG_COMBO_PHY1_40[1], No input mask port0
            MDrv_WriteByteMask(REG_112183, BIT1, BIT1); // REG_COMBO_PHY1_41[9], No input clear port0
            MDrv_WriteByteMask(REG_112183, 0, BIT1); // REG_COMBO_PHY1_41[9], No input clear port0
            break;

        case MSCombo_TMDS_PORT_1:
            MDrv_WriteByteMask(REG_112381, bEnable? 0: BIT1, BIT1); // REG_COMBO_PHY3_40[1], No input mask port1
            MDrv_WriteByteMask(REG_112383, BIT1, BIT1); // REG_COMBO_PHY3_41[9], No input clear port1
            MDrv_WriteByteMask(REG_112383, 0, BIT1); // REG_COMBO_PHY3_41[9], No input clear port1
            break;

        case MSCombo_TMDS_PORT_2:
        case MSCombo_TMDS_PORT_3:
            MDrv_WriteByteMask(REG_112581, bEnable? 0: BIT1, BIT1); // REG_COMBO_PHY5_40[1], No input mask port2&3
            MDrv_WriteByteMask(REG_112583, BIT1, BIT1); // REG_COMBO_PHY5_41[9], No input clear port2&3
            MDrv_WriteByteMask(REG_112583, 0, BIT1); // REG_COMBO_PHY5_41[9], No input clear port2&3
            break;

        default:

            break;
    };
}

#if 0 // this is new merged one, register bank is not checked
//**************************************************************************
//  [Function Name]:
//                  _mhal_tmds_ResetHDMI20VersionFlag()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void _mhal_tmds_ResetHDMI20VersionFlag(MSCombo_TMDS_PORT_INDEX enPortSelect)
{
    switch(enPortSelect)
    {
        case MSCombo_TMDS_PORT_0:

            break;

        case MSCombo_TMDS_PORT_1:

            break;

        case MSCombo_TMDS_PORT_2:
        case MSCombo_TMDS_PORT_3:
            msWriteByteMask(REG_001818, MASKBIT(3:2), MASKBIT(3:2)); // REG_PM_SCDC_0C[3:2]
            msWriteByteMask(REG_001818, 0, MASKBIT(3:2)); // REG_PM_SCDC_0C[3:2]
            break;

        default:

            break;
    };
}

//**************************************************************************
//  [Function Name]:
//                  _mhal_tmds_ClearSCDCStatusFlag()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void _mhal_tmds_ClearSCDCStatusFlag(MSCombo_TMDS_PORT_INDEX enPortSelect, BYTE ucStatusMask)
{
    switch(enPortSelect)
    {
        case MSCombo_TMDS_PORT_0:

            break;

        case MSCombo_TMDS_PORT_1:

            break;

        case MSCombo_TMDS_PORT_2:
        case MSCombo_TMDS_PORT_3:
            msWriteByteMask(REG_00180F, ucStatusMask, ucStatusMask); // REG_PM_SCDC_07[15:8]
            msWriteByteMask(REG_00180F, 0, ucStatusMask); // REG_PM_SCDC_07[15:8]
            break;

        default:

            break;
    };
}
#endif // this is new merged one, register bank is not checked

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_CheckAudioErrorStatus()
//  [Description]:
//                  Checking current Audio fading/mute event status bit, after store, then clear it
//                  #define ERR_HDMI_CTSN_OVERRANGE     _BIT0
//                  #define ERR_HDMI_CLK_BIG_CHANGE     _BIT1
//                  #define ERR_HDMI_AVMUTE             _BIT2
//                  #define ERR_HDMI_NO_INPUT_CLK       _BIT3
//                  #define ERR_HDMI_AUD_SMP_FLAT       _BIT4
//                  #define ERR_HDMI_AUD_CH_ST_CHANGE   _BIT5
//                  #define ERR_HDMI_AUD_FIFO_ERR       _BIT6
//                  #define ERR_HDMI_AUD_SMP_ERR     _BIT7
//  [Arguments]:
//                  MSCombo_TMDS_PORT_INDEX enInputPort
//  [Return]:
//                  none
//**************************************************************************
BYTE mhal_tmds_CheckAudioErrorStatus(MSCombo_TMDS_PORT_INDEX enInputPort, BOOL bClrAVMute)
{
    BYTE bAudioErrorStatus = 0;
#if (ENABLE_AUDIO_AUTO_FADING == 1)
    static BYTE bPreAudioErrorStatus = 0;
#endif

    #if (ENABLE_AUDIO_AUTO_FADING == 1)
        bAudioErrorStatus |= MDrv_ReadByte(REG_100E8E);
    #endif
    #if (ENABLE_AUDIO_AUTO_MUTE == 1)
        bAudioErrorStatus |= MDrv_ReadByte(REG_100E8B);
    #endif

    // CTS/N over range
    if (bAudioErrorStatus & ERR_HDMI_CTSN_OVERRANGE)
    {
        if(enInputPort == MSCombo_TMDS_PORT_0)
        {
             if (MDrv_ReadByte(REG_160504) & BIT6) //[6]: CTS N over range
             {
                 _mhal_tmds_UpdateCTSNValue(enInputPort);
                 MDrv_WriteByteMask(REG_160504, 0x40, 0x40); // clear CTS/N over range
             }
             else
                 bAudioErrorStatus &= (~ERR_HDMI_CTSN_OVERRANGE);
        }
        else if(enInputPort == MSCombo_TMDS_PORT_1)
        {
             if (MDrv_ReadByte(REG_160A04) & BIT6) //[6]: CTS N over range
             {
                 _mhal_tmds_UpdateCTSNValue(enInputPort);
                 MDrv_WriteByteMask(REG_160A04, 0x40, 0x40); // clear CTS/N over range
             }
             else
                 bAudioErrorStatus &= (~ERR_HDMI_CTSN_OVERRANGE);
        }
        else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
        {
             if (MDrv_ReadByte(REG_161104) & BIT6) //[6]: CTS N over range
             {
                 _mhal_tmds_UpdateCTSNValue(enInputPort);
                 MDrv_WriteByteMask(REG_161104, 0x40, 0x40); // clear CTS/N over range
             }
             else
                 bAudioErrorStatus &= (~ERR_HDMI_CTSN_OVERRANGE);
        }

    }

    //Clock Big Change
    if (bAudioErrorStatus & ERR_HDMI_CLK_BIG_CHANGE)
    {
        if(enInputPort == MSCombo_TMDS_PORT_0)
        {
             if (MDrv_ReadByte(REG_160504) & BIT7) // [7]: Clock  big change
             {
                 MDrv_WriteByteMask(REG_160504, 0x80, 0x80); // clear clk big change status
             }
             else
                 bAudioErrorStatus &= (~ERR_HDMI_CLK_BIG_CHANGE);
        }
        else if(enInputPort == MSCombo_TMDS_PORT_1)
        {
             if (MDrv_ReadByte(REG_160A04) & BIT7) // [7]: Clock  big change
             {
                 MDrv_WriteByteMask(REG_160A04, 0x80, 0x80); // clear clk big change status
             }
             else
                 bAudioErrorStatus &= (~ERR_HDMI_CLK_BIG_CHANGE);
        }
        else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
        {
             if (MDrv_ReadByte(REG_161104) & BIT7) // [7]: Clock  big change
             {
                 MDrv_WriteByteMask(REG_161104, 0x80, 0x80); // clear clk big change status
             }
             else
                bAudioErrorStatus &= (~ERR_HDMI_CLK_BIG_CHANGE);
        }
    }

    //AV mute
    if (bAudioErrorStatus & ERR_HDMI_AVMUTE)
    {
        if(enInputPort == MSCombo_TMDS_PORT_0)
        {
            if (bClrAVMute)
            {
                MDrv_WriteByteMask(REG_1605C4, 0x01, 0x01); // raise clear AV mute status
                MDrv_WriteByteMask(REG_1605BF, 0x01, 0x01); // clear AV mute
                MDrv_WriteByteMask(REG_1605BF, 0x00, 0x01); // clear AV mute
                bAudioErrorStatus &= (~ERR_HDMI_AVMUTE);
            }
        }
        else if(enInputPort == MSCombo_TMDS_PORT_1)
        {
            if (bClrAVMute)
            {
                MDrv_WriteByteMask(REG_160AC4, 0x01, 0x01); // raise clear AV mute status
                MDrv_WriteByteMask(REG_160ABF, 0x01, 0x01); // clear AV mute
                MDrv_WriteByteMask(REG_160ABF, 0x00, 0x01); // clear AV mute
                bAudioErrorStatus &= (~ERR_HDMI_AVMUTE);
            }
        }
        else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
        {
            if (bClrAVMute)
            {
                MDrv_WriteByteMask(REG_1611C4, 0x01, 0x01); // raise clear AV mute status
                MDrv_WriteByteMask(REG_1611BF, 0x01, 0x01); // clear AV mute
                MDrv_WriteByteMask(REG_1611BF, 0x00, 0x01); // clear AV mute
                bAudioErrorStatus &= (~ERR_HDMI_AVMUTE);
            }
        }

    }

    //No Input Clock
    if (bAudioErrorStatus & ERR_HDMI_NO_INPUT_CLK)
    {
        if (!(MDrv_ReadByte(REG_162F33) & BIT7)) //[7]: CTS N synthesizer input detect
            //NOTE: this status will auto clear
            bAudioErrorStatus &= (~ERR_HDMI_NO_INPUT_CLK);
    }

    //Audio Sample Flat
    if (bAudioErrorStatus & ERR_HDMI_AUD_SMP_FLAT)
    {
        if (MDrv_ReadByte(REG_100EB0) & BIT7) //[7]: ch1~ ch8 flat bit
        {
            MDrv_WriteByteMask(REG_100EB0, BIT7, BIT7);
        }
        else
            bAudioErrorStatus &= (~ERR_HDMI_AUD_SMP_FLAT);
    }

    //Audio Channel Status Change
    if (bAudioErrorStatus & ERR_HDMI_AUD_CH_ST_CHANGE)
    {
        if (MDrv_ReadByte(REG_100EB0) & BIT2) // [2]: audio ch status change
        {
            MDrv_WriteByteMask(REG_100EB0, BIT2, BIT2);
        }
        else
            bAudioErrorStatus &= (~ERR_HDMI_AUD_CH_ST_CHANGE);
    }

    //Audio FIFO Error (underflow / overflow)
    if (bAudioErrorStatus & ERR_HDMI_AUD_FIFO_ERR)
    {
        if (MDrv_ReadByte(REG_100EB1) & (BIT1 | BIT0)) // [1]: ch1/ch2 over run, [0]: ch1/ch2 under run
        {
            //MDrv_WriteByteMask(REG_100E69, 0x80, 0x80); // [7] : reset audio module
            //MDrv_WriteByteMask(REG_100E69, 0x00, 0x80);
            MDrv_WriteByteMask(REG_100EB1, (BIT1 | BIT0), (BIT1 | BIT0));
        }
        else
            bAudioErrorStatus &= (~ERR_HDMI_AUD_FIFO_ERR);
    }

    //Audio Sample Error (sample error / polarity error)
    if (bAudioErrorStatus & ERR_HDMI_AUD_SMP_ERR)
    {
        if (MDrv_ReadByte(REG_100EB0) & (BIT1 | BIT0)) //[1]: audio parity error, [0]:audio sample error
        {
            MDrv_WriteByteMask(REG_100EB0, (BIT1 | BIT0), (BIT1 | BIT0));
        }
        else
            bAudioErrorStatus &= (~ERR_HDMI_AUD_SMP_ERR);
    }

    // Audio fading patch due to non zero crossing audio pattern
#if (ENABLE_AUDIO_AUTO_FADING == 1)
    if((bPreAudioErrorStatus !=0) && (bAudioErrorStatus == 0)) // Has been happened audio error then becomes normal now
    {
        if((MDrv_ReadByte(REG_100E8F) & BIT0) == 0) // if fading status is still fading out due to some DC offset audio pattern, force to fading in
        {
            MDrv_WriteByteMask(REG_100EA0, BIT0, BIT0); // trigger to fading in
            //ForceDelay1ms(1);
            MDrv_WriteByteMask(REG_100EA0, 0, BIT0);
            TMDS_PRINT("\r\n@@ AudioFaing Patch\r\n");
        }
    }
    bPreAudioErrorStatus = bAudioErrorStatus;
#endif

    return bAudioErrorStatus;

}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_ConfigAudioPort()
//  [Description]:
//                  Configurate all audio setting which is relative to specific port.
//                  Call flow:
//                      1. mhal_tmds_HDMIInitialAudio()
//                  After decided which port is going to be actived, then call
//                      2. mhal_tmds_ConfigAudioPort()
//                          -> mhal_tmds_ConfigAudioSource()
//                          -> mhal_tmds_ConfigAudioFadingEvent()
//  [Arguments]:
//                  none
//  [Return]:
//                  none
//**************************************************************************
void mhal_tmds_ConfigAudioPort(MSCombo_TMDS_PORT_INDEX enInputPort)
{

    _mhal_tmds_UpdateCTSNValue(enInputPort);

    if(enInputPort == MSCombo_TMDS_PORT_0)
    {
        MDrv_WriteByteMask(REG_160504, 0x40, 0x40); // clear CTS/N over range

        msWrite2ByteMask(REG_100EB0, 0x3FF, 0x3FF); // clear all status;
        MDrv_WriteByteMask(REG_1605BF, 0x01, 0x01); // clear AV mute
        MDrv_WriteByteMask(REG_1605BF, 0x00, 0x01); // clear AV mute
    }
    else if(enInputPort == MSCombo_TMDS_PORT_1)
    {
        MDrv_WriteByteMask(REG_160A04, 0x40, 0x40); // clear CTS/N over range

        msWrite2ByteMask(REG_100EB0, 0x3FF, 0x3FF); // clear all status;
        MDrv_WriteByteMask(REG_160ABF, 0x01, 0x01); // clear AV mute
        MDrv_WriteByteMask(REG_160ABF, 0x00, 0x01); // clear AV mute
    }
    else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
    {
        MDrv_WriteByteMask(REG_161104, 0x40, 0x40); // clear CTS/N over range

        msWrite2ByteMask(REG_100EB0, 0x3FF, 0x3FF); // clear all status;
        MDrv_WriteByteMask(REG_1611BF, 0x01, 0x01); // clear AV mute
        MDrv_WriteByteMask(REG_1611BF, 0x00, 0x01); // clear AV mute
    }
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_EnableAudioMute()
//  [Description]:
//                  Enable/Disable Global Mute function
//  [Arguments]:
//                  EnableMute: if TRUE then trigger global mute, otherwise turn off global mute
//  [Return]:
//                  None
//**************************************************************************
void mhal_tmds_EnableAudioMute(Bool EnableMute)
{
    if (EnableMute) //trigger global mute
        MDrv_WriteByteMask(REG_100E88, BIT4, BIT4);
    else
        MDrv_WriteByteMask(REG_100E88, 0, BIT4);
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_HDMI20_MUX()
//  [Description]:
//                  mhl3_atop selection
//  [Arguments]:
//                  enInputPort : combo port
//  [Return]:
//                  None
//**************************************************************************
void mhal_tmds_HDMI20_MUX(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    if(enInputPort == MSCombo_TMDS_PORT_2)
    {
        bCurrentPort = MSCombo_TMDS_PORT_2;
        MDrv_WriteByteMask(REG_11251C, 0x00, 0x01); // [0]:mhl3_atop selection :0 (mhl3_atop_0)
        MDrv_WriteByteMask(REG_000461, 0x80, 0x80); // [15]: HDCP & SCDC I2C port selection :1 (PAD_GPIOX13/GPIOX14)
    }
    else if (enInputPort == MSCombo_TMDS_PORT_3)
    {
        bCurrentPort = MSCombo_TMDS_PORT_3;
        MDrv_WriteByteMask(REG_11251C, 0x01, 0x01); // [0]: mhl3_atop selection :1 (mhl3_atop_1)
        MDrv_WriteByteMask(REG_000461, 0x00, 0x80); // [15]: HDCP & SCDC I2C port selection:0 (PAD_GPIOX23/GPIOX24)
    }
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_Initial()
//  [Description]:
//                  initital setting for each combo port,
//                  if enInputPort is dual link port, also config the sub-link
//  [Arguments]:
//                  enInputPort : combo port
//                  bDual : dual link port or not
//  [Return]:
//                  None
//**************************************************************************
void mhal_tmds_Initial(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bDual)
{
    static Bool bReadEfuse = FALSE;
    WORD wOffset;

    wPreviousTiming = 0;
    bPreviousPort = MSCombo_TMDS_PORT_MAX + 1; //make sure even port 0 will setting EQ for first time ISR
    bOver3GFlag[enInputPort] = FALSE;
    bSplitterDone[enInputPort] = FALSE;
    bAutoEQRetry[enInputPort] = 0;
    bAutoEQCntRst[enInputPort] = FALSE;
    bAutoEQDone[enInputPort] = FALSE;
    bMHLCable[enInputPort] = FALSE;

    wOffset = _mhal_tmds_phy_offset(enInputPort);
    //eq 3tage setting
    MDrv_WriteByteMask(REG_1120BE + wOffset, BIT6|BIT5, BIT6|BIT5); //lane0 always turn on 3 stage.
    MDrv_WriteByteMask(REG_1120C0 + wOffset, BIT6|BIT5, BIT6|BIT5); //lane1 always turn on 3 stage.
    MDrv_WriteByteMask(REG_1120C2 + wOffset, BIT6|BIT5, BIT6|BIT5); //lane2 always turn on 3 stage.
    MDrv_WriteByteMask(REG_1120C4 + wOffset, BIT6|BIT5, BIT6|BIT5); //lane3 always turn on 3 stage.

    msWrite2ByteMask(REG_100E62, 0, 0x0001); //  PD_CLKXTAL
  //  MDrv_Write2Byte(REG_1120DE + wOffset, 0x0F00);// overwrite
    if((enInputPort== MSCombo_TMDS_PORT_0) || (enInputPort== MSCombo_TMDS_PORT_1))
    {
        MDrv_Write2Byte(REG_1120D6 + wOffset, 0x0702); // [1]: reg_atop_en_clko_pix=1
        MDrv_Write2Byte(REG_112014 + wOffset, 0x0040); // [6]: reg_af_ls_20out_sel=1
        MDrv_Write2Byte(REG_1120B4 + wOffset, 0x0000); // [2]: disable reg_atop_en_clko_tmds2x

    }
    else if((enInputPort== MSCombo_TMDS_PORT_2) || (enInputPort== MSCombo_TMDS_PORT_3))
    {
        MDrv_Write2Byte(REG_1120D6 + wOffset, 0x0706); // [1]: reg_atop_en_clko_pix=1
        MDrv_Write2Byte(REG_112014 + wOffset, 0x0040); // [6]: reg_af_ls_20out_sel=1
        MDrv_Write2Byte(REG_1120B4 + wOffset, 0x0004); // [2]: disable reg_atop_en_clko_tmds2x
        msWrite2ByteMask(REG_100E62, 0, 0xFFFF); // enable P2 all clock power
        MDrv_WriteByteMask(REG_100E60, 0x05, 0x0D); // [2]: reg_pix_clk_div2_en_p2; [0]: reg_tmds_clk_div2_en_p2
        MDrv_WriteByteMask(REG_1612A8, 0x02, 0x03); // [1:0]: reg_avg_ctrl_case
    }

    if(enInputPort == MSCombo_TMDS_PORT_0)
    {
        msWrite2ByteMask(REG_100E22, 0, 0xFFFF); // enable P0 all clock power
        MDrv_WriteByteMask(REG_001724, 0, 0x40); // REG_PD_CLKIN_OFFL = 0
        MDrv_WriteByteMask(REG_112107, 0, 0x07); // [10:8]: Power on P0 data r-term
        MDrv_WriteByteMask(REG_001724, 0, 0xFF); // [7]: Power on P0 clock r-term
        MDrv_WriteByteMask(REG_001725, 0x01, 0x01); // reg_p0_pd_cmos_sw =1

    }
    else if(enInputPort == MSCombo_TMDS_PORT_1)
    {
       msWrite2ByteMask(REG_100E42, 0, 0xFFFF); // enable P1 all clock power
       MDrv_WriteByteMask(REG_001726, 0, 0x40); // REG_PD_CLKIN_OFFL = 0
       MDrv_WriteByteMask(REG_112307, 0, 0x07); // [10:8]: Power on P1 data r-term
       MDrv_WriteByteMask(REG_001726, 0, 0xFF); // [7]: Power on P1 clock r-term
       MDrv_WriteByteMask(REG_001727, 0x01, 0x01); // reg_p1_pd_cmos_sw =1
    }
    else if(enInputPort == MSCombo_TMDS_PORT_2)
    {
        MDrv_WriteByteMask(REG_001720, 0, 0x0F); // [3:1]: Power on Port2 data r-term
        MDrv_WriteByteMask(REG_001720, 0, 0x10); // [4]: Power on Port2 clock r-term
    }
    else if(enInputPort == MSCombo_TMDS_PORT_3)
    {
        MDrv_WriteByteMask(REG_001722, 0, 0x0F); // [3:1]: Power on Port3 data r-term
        MDrv_WriteByteMask(REG_001722, 0, 0x10); // [4]: Power on Port3 clock r-term
    }

    MDrv_WriteByteMask(REG_112500, 0x00, 0x0F); //[2:0]: reg_atop_pd_oscreg_atop_pd_osc; [3]: power down internal LDO
    MDrv_WriteByteMask(REG_112000 + wOffset, 0x80, 0x80); //[7]: Main link function select: HDMI/MHL0
    MDrv_Write2Byte(REG_1120AE + wOffset, 0x010C); // [8]: enable mhl fullrate mode; [7:0]: Set Xtal freq
    MDrv_Write2Byte(REG_112016 + wOffset, 0xFFFF); // RX Phy Clock enable
    MDrv_Write2Byte(REG_112018 + wOffset, 0x3FFF); // RX Phy Clock enable
    MDrv_Write2Byte(REG_1120B6 + wOffset, 0x0000); // [13]: reg_atop_pd_bg; [12]: reg_atop_pd_clkin; [11:8]: reg_atop_pd_phdac_ov; [3:0]: reg_atop_pd_lane
    MDrv_WriteByteMask(REG_1120F4 + wOffset, 0x00, 0x0F); // [3:0]: reg_atop_pd_pll
    // [0]: REG_EN_SQH ; [1]: reg_pd_clkin; [3:2]: reg_test_sqh; [7:4]: reg_sq_vth;
    // [11:8]: reg_pd_rt; [13:12]: reg_test_clkin; [14]: reg_dato_sqh;[15]: reg_clk_xtali_div2_en
    MDrv_Write2Byte(REG_112068 + wOffset, 0x0040);
    MDrv_Write2Byte(REG_11206A + wOffset, 0x0480); // [10]: reg_hdmi2_acdr_mode = 1
    MDrv_Write2Byte(REG_112090 + wOffset, 0x0702); // [15:8]: reg_mainlink_crlose_thr; [15:8]: reg_mainlink_crlose_thr


#if 1 // HDMI default mode
    MDrv_WriteByteMask(REG_112020 + wOffset, 0x10, 0x10); //[4]: SWAP_DCDR_UPDN_POLITY
    MDrv_WriteByteMask(REG_112029 + wOffset, 0x00, 0x10); //[4]: PHFSM0_FAST_EN
    MDrv_WriteByteMask(REG_11202B + wOffset, 0x00, 0x10); //[4]: PHFSM1_FAST_EN
    MDrv_WriteByteMask(REG_11202D + wOffset, 0x00, 0x10); //[4]: PHFSM2_FAST_EN

#if 0
    //feedback divider for MHL mode
    MDrv_WriteByteMask(REG_1120DA + wOffset, 0, 0x10); //Disable Lane0 overwrite
    MDrv_WriteByteMask(REG_1120E1 + wOffset, 0, 0x03); //Divsel_MHL_L0 value
    MDrv_WriteByteMask(REG_1120DA + wOffset, 0, 0x20); //Disable Lane1 overwrite
    MDrv_WriteByteMask(REG_1120E1 + wOffset, 0, 0x0C); //Divsel_MHL_L1 value
    MDrv_WriteByteMask(REG_1120DA + wOffset, 0, 0x40); //Disable Lane2 overwrite
    MDrv_WriteByteMask(REG_1120E1 + wOffset, 0, 0x30); //Divsel_MHL_L2 value
    MDrv_WriteByteMask(REG_1120DA + wOffset, 0, 0x80); //Disable Lane3 overwrite
    MDrv_WriteByteMask(REG_1120E1 + wOffset, 0, 0xC0); //Divsel_MHL_L3 value
    //disable DP full rate mode
    MDrv_WriteByteMask(REG_1120DC + wOffset, 0, 0x02); //[1]: disable overwrite
    MDrv_WriteByteMask(REG_1120E5 + wOffset, 0, 0x04); //[2]: acdr_fullrate_ov

    //disable LA of each lane
    MDrv_WriteByteMask(REG_1120DC + wOffset, 0, 0x3C); //[5:2]: disable overwrite
    MDrv_WriteByteMask(REG_1120E5 + wOffset, 0, 0x78);

    //enable PHD feedback mode for HDMI new mode
    MDrv_WriteByteMask(REG_1120DD + wOffset, 0, 0x0F); //[3:0]: disable overwrite
#endif

    //R-term value over write
    MDrv_WriteByteMask(REG_1120B3 + wOffset, 0, 0x01); //[0]: overwtite
    MDrv_WriteByteMask(REG_1120B7 + wOffset, 0, 0xF0); //[7:4]: R-term value

#endif
    //CLK valid boundary
    msWrite2ByteMask(REG_112076 + wOffset, 0x1F00, 0x1FFF); // [12:0]: reg_clk_valid_u
    //CR Lock Mode
    msWrite2ByteMask(REG_11208A + wOffset, 0x1F83, 0x7FFF); // [14:8]: reg_dig_lock_time; [7]: reg_dig_lock_mode; [3:0]: reg_dig_lck_cnt_power


    //xtal divider setting, default value is ok, we don't modify here
    //MDrv_WriteByte(REG_112062 + wOffset, 0x3F);//clock_xtal_divider_HBR

    //CR lock/unlock threshold, setting default value currently
    //MDrv_Write2Byte(0x112090 + wOffset, 0x0702); //MAINLINK_CRLOCK_THR[7:0], MAINLINK_CRLOSE_THR[8:15];

    //CR lock filter, setting default value currently
    //MDrv_WriteByteMask(0x11205D + wOffset, 0x06, 0x1F); //CR_LOCK_TH[4:0]


    //HDMI_MHL divider threshold
    if((enInputPort== MSCombo_TMDS_PORT_0) || (enInputPort== MSCombo_TMDS_PORT_1))
    {
        MDrv_Write2Byte(REG_112092 + wOffset, 0x0B43); // reg_hdmi_clk_thr4, the value of cr_lock_cnt in 270Mhz
        MDrv_Write2Byte(REG_112094 + wOffset, 0x0715); // reg_hdmi_clk_thr3, the value of cr_lock_cnt in 170Mhz
        MDrv_Write2Byte(REG_112096 + wOffset, 0x038B); // reg_hdmi_clk_thr2 , the value of cr_lock_cnt in 85Mhz
        MDrv_Write2Byte(REG_112098 + wOffset, 0x01C6); // reg_hdmi_clk_thr2 , the value of cr_lock_cnt in 42.5Mhz
        MDrv_Write2Byte(REG_11209A + wOffset, 0x0716); // reg_hdmi2_clk_thr3, the value of cr_lock_cnt in 170Mhz
        MDrv_Write2Byte(REG_11209C + wOffset, 0x01C6); // reg_hdmi2_clk_thr2, the value of cr_lock_cnt in 42.5Mhz
        MDrv_Write2Byte(REG_11209E + wOffset, 0x012E); //r eg_hdmi2_clk_thr1, the value of cr_lock_cnt in 28.33Mhz
    }
    else if((enInputPort== MSCombo_TMDS_PORT_2) || (enInputPort== MSCombo_TMDS_PORT_3))
    {
        MDrv_Write2Byte(REG_112092 + wOffset, 0x0A6B); // reg_hdmi_clk_thr4, the value of cr_lock_cnt in 250Mhz
        MDrv_Write2Byte(REG_112094 + wOffset, 0x0715); // reg_hdmi_clk_thr3, the value of cr_lock_cnt in 170Mhz
        MDrv_Write2Byte(REG_112096 + wOffset, 0x038B); // reg_hdmi_clk_thr2 , the value of cr_lock_cnt in 85Mhz
        MDrv_Write2Byte(REG_112098 + wOffset, 0x01C5); // reg_hdmi_clk_thr2 , the value of cr_lock_cnt in 42.5Mhz
        MDrv_Write2Byte(REG_11209A + wOffset, 0x0320); // reg_hdmi2_clk_thr3, the value of cr_lock_cnt in 75Mhz
        MDrv_Write2Byte(REG_11209C + wOffset, 0x0190); // reg_hdmi2_clk_thr2, the value of cr_lock_cnt in 37.5Mhz
        MDrv_Write2Byte(REG_11209E + wOffset, 0x0215); //r eg_hdmi2_clk_thr1, the value of cr_lock_cnt in 50Mhz
    }

    // EQ setting initialize
    MDrv_Write2Byte(REG_11204A + wOffset, 0x0AC8);
    MDrv_Write2Byte(REG_112056 + wOffset, 0x0018);
    MDrv_Write2Byte(REG_112058 + wOffset, 0x0004);
    MDrv_Write2Byte(REG_112050 + wOffset, 0x3A83);
    MDrv_Write2Byte(REG_11204C + wOffset, 0x080A); // [5:0]: reg_phase_check_time; [13:8]: reg_eq_fine_tune_time

    // PHASE
    msWrite2ByteMask(REG_112022 + wOffset, 0x0000, 0x1FFF); // [12]: reg_dvi_ovch0; [11:0]: reg_dvi_ch0_ph
    msWrite2ByteMask(REG_112024 + wOffset, 0x0000, 0x1FFF); // [12]: reg_dvi_ovch1; [11:0]: reg_dvi_ch1_ph
    msWrite2ByteMask(REG_112026 + wOffset, 0x0000, 0x1FFF); // [12]: reg_dvi_ovch2; [11:0]: reg_dvi_ch2_ph

    MDrv_Write2Byte(REG_1120B8 + wOffset, 0x0000); // [3:0]: reg_atop_sel_phdclk
    MDrv_WriteByteMask(REG_112020 + wOffset, 0x18, 0x18); // [4]: reg_swap_dcdr_updn_polity; [3]: reg_enable_phase_step

    // HDMI Auto Detect
    msWrite2ByteMask(REG_112160 + wOffset, 0x0026, 0x013F); // [5]: reg_hdmi_auto_det_eq_en; [2]: reg_hdmi_auto_det_en; [1]: reg_do_auto_det_hdmi; [0]: reg_tmds_bit_valid
    MDrv_Write2Byte(REG_112170 + wOffset, 0x00FF); // reg_hdmi_symbol_det_times
    MDrv_Write2Byte(REG_112194 + wOffset, 0x003A); // reg_hdmi_pat_det_times1
    MDrv_Write2Byte(REG_112196 + wOffset, 0x0055); // reg_hdmi_pat_det_times2
    MDrv_Write2Byte(REG_112198 + wOffset, 0x001A); // reg_hdmi_under_th
    MDrv_WriteByte(REG_11216E + wOffset, 0x1F); // [7:4]: reg_hdmi_auto_det_times; [3:0]: reg_hdmi_eq_sweep_times
    MDrv_Write2Byte(REG_112166 + wOffset, 0x001F); // reg_hdmi_symbol_det_duration

    if((enInputPort== MSCombo_TMDS_PORT_0) || (enInputPort== MSCombo_TMDS_PORT_1))
    {
        // PD initialize
        msWrite2ByteMask(REG_112104 + wOffset, 0x0000, 0x7777);
        msWrite2ByteMask(REG_112106 + wOffset, 0x0000, 0x0777);

        // DPLPH0/1/2 initialize
         msWrite2ByteMask(REG_112022 + wOffset, 0x000A, 0x1FFF); // [12]: reg_dvi_ovch0; [11:0]: reg_dvi_ch0_ph
         msWrite2ByteMask(REG_112024 + wOffset, 0x000A, 0x1FFF); // [12]: reg_dvi_ovch1; [11:0]: reg_dvi_ch1_ph
         msWrite2ByteMask(REG_112026 + wOffset, 0x000A, 0x1FFF); // [12]: reg_dvi_ovch2; [11:0]: reg_dvi_ch2_ph
         msWrite2ByteMask(REG_112160 + wOffset, 0x0000, 0x013F);
         msWrite2ByteMask(REG_11206A + wOffset, 0x0280, 0x17FF);
    }

    //auto clear enz for hit coundary
    MDrv_WriteByteMask(REG_11203B + wOffset, 0x00, 0x01);

    //digital lock part
    //MDrv_WriteByteMask(0x11208A + wOffset, 0x03, 0x0F); //DIG_LCK_CNT_PWR[3:0]
    //MDrv_WriteByte(0x11208E + wOffset, 0xE1); //DIG_LOSE_RANGE[7:4], DIG_LCK_RANGE[3:0]
    //MDrv_WriteByteMask(0x11208B + wOffset, 0x1F, 0x7F); //DIG_LOCK_TIME[6:0]


    // MDrv_WriteByteMask(REG_1606A3 + wOffset, 0x80, 0x80); //word boundary detect unlock check
    MDrv_Write2Byte(0x1630EE, 0x1FFF); //clk to scaler

    if(enInputPort == MSCombo_TMDS_PORT_0)
    {
        MDrv_WriteByteMask(REG_10062F, BIT5, BIT5);// patch for HDCP issue, reset HDCP FSM when no input clock
        MDrv_WriteByteMask(REG_16050D, 0x0C, 0x0C); // [3] : enable video mute, [2] : blanking when AVmute is active.
        MDrv_WriteByteMask(REG_16050E, 0x03, 0x03); // [1] : auto reset deep color FIFO, [0] : enable deep color mode.
        MDrv_WriteByteMask(REG_160640, 0x00, 0x00); // [1] : disable force 422 to 444.
        MDrv_Write2Byte(REG_1605C0, 0xFFFF); // HDMI pkt irq mask
        MDrv_WriteByteMask(REG_10062A, 0xFF, 0xFF); // HDCP pkt irq mask
        MDrv_WriteByteMask(REG_160247, 0x00, 0xFF); // word boundary unlock threshold
        MDrv_WriteByteMask(REG_120FDE, 0x01, 0x01); // [0] force clk_combo_0_rep_en
        MDrv_WriteByteMask(REG_1605C8, 0x80, 0xF0); // [7] Frame repetition manual mode
        MDrv_WriteByteMask(REG_112120, 0x07, 0x07); // eq overwrite enable
        msWrite2ByteMask(REG_112122, (TMDS_HDMI14_R_CHANNEL_EQ<<8)|(TMDS_HDMI14_G_CHANNEL_EQ<<4)|TMDS_HDMI14_B_CHANNEL_EQ, 0x0FFF);
    }
    else if(enInputPort == MSCombo_TMDS_PORT_1)
    {
        MDrv_WriteByteMask(REG_100B2F, BIT5, BIT5);// patch for HDCP issue, reset HDCP FSM when no input clock
        MDrv_WriteByteMask(REG_160A0D, 0x0C, 0x0C); // [3] : enable video mute, [2] : blanking when AVmute is active.
        MDrv_WriteByteMask(REG_160A0E, 0x03, 0x03); // [1] : auto reset deep color FIFO, [0] : enable deep color mode.
        MDrv_WriteByteMask(REG_160B40, 0x00, 0x00); // [1] : disable force 422 to 444.
        MDrv_Write2Byte(REG_160AC0, 0xFFFF); // HDMI pkt irq mask
        MDrv_WriteByteMask(REG_100B2A, 0xFF, 0xFF); // HDCP pkt irq mask
        MDrv_WriteByteMask(REG_160747, 0x00, 0xFF); // word boundary unlock threshold
        MDrv_WriteByteMask(REG_120FDE, 0x02, 0x02); // [1] force clk_combo_1_rep_en
        MDrv_WriteByteMask(REG_160AC8, 0x80, 0xF0); // [7] Frame repetition manual mode
        MDrv_WriteByteMask(REG_112320, 0x07, 0x07); // eq overwrite enable
        msWrite2ByteMask(REG_112322, (TMDS_HDMI14_R_CHANNEL_EQ<<8)|(TMDS_HDMI14_G_CHANNEL_EQ<<4)|TMDS_HDMI14_B_CHANNEL_EQ, 0x0FFF);
    }
    else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
    {
        MDrv_WriteByteMask(REG_16102F, BIT5, BIT5); // patch for HDCP issue, reset HDCP FSM when no input clock
        MDrv_WriteByteMask(REG_16110D, 0x0C, 0x0C); // [3] : enable video mute, [2] : blanking when AVmute is active.
        MDrv_WriteByteMask(REG_16110E, 0x03, 0x03); // [1] : auto reset deep color FIFO, [0] : enable deep color mode.
        MDrv_WriteByteMask(REG_161240, 0x00, 0x00); // [1] : disable force 422 to 444.
        MDrv_Write2Byte(REG_1611C0, 0xFFFF); // HDMI pkt irq mask
        MDrv_WriteByteMask(REG_16102B, 0xFF, 0xFF); // HDCP pkt irq mask
        MDrv_WriteByteMask(REG_120FDE, 0x04, 0x04); // [2] force clk_combo_2_rep_en
        MDrv_WriteByteMask(REG_1611C8, 0x80, 0xF0); // [7] Frame repetition manual mode
        MDrv_WriteByteMask(REG_1611CF, 0x01, 0x01); // [8]: reg_cts_div2_en
        MDrv_WriteByteMask(REG_11257C, 0x04, 0x04); // [2]: SCDC bypass clock tmds ratio

        MDrv_WriteByteMask(REG_1124DC, 0xF0, 0xF0); // eq overwrite enable
        msWrite2ByteMask(REG_1124E6, (TMDS_HDMI20_G_CHANNEL_EQ<<8)|TMDS_HDMI20_B_CHANNEL_EQ, 0x1F1F);
        msWrite2ByteMask(REG_1124E8, (TMDS_HDMI20_CLK_CHANNEL_EQ<<8)|TMDS_HDMI20_R_CHANNEL_EQ, 0x1F1F);

        MDrv_WriteByteMask(REG_11242B, 0x00, 0x80); // Bypass symbol lock detect in coarse tune state
        MDrv_WriteByteMask(REG_11258A, 0x00, 0x1F); // The limit of the auto EQ start value (coarse tune min value)
        MDrv_WriteByteMask(REG_11258B, 0x1F, 0x1F); // The limit of the auto EQ end value (coarse tune max value)
        MDrv_WriteByteMask(REG_112467, 0x12, 0x3F); // Start EQ strength for auto EQ scan (coarse tune start value)
        msWrite2ByteMask(REG_112584, 0x00FF, 0xFFFF); // coarse tune symbol detect times
        msWrite2ByteMask(REG_112594, 0x0050, 0xFFFF); // coarse tune symbol aaba number
        MDrv_WriteByteMask(REG_112588, 0x01, 0x01); // enable coarse symbol lock
        msWrite2ByteMask(REG_112596, 0x1FFF, 0xFFFF); // fine tune aaba number
        msWrite2ByteMask(REG_112598, 0x05FF, 0xFFFF); // fine tune under threshold
        MDrv_WriteByteMask(REG_112592, 0x00, 0x20); // enable fine tune symbol lock mode
        MDrv_WriteByteMask(REG_112451, 0x00, 0x04); // disable timer mode in fine tune
        MDrv_WriteByteMask(REG_112466, 0x08, 0x08); // enable tmds trigger
        msWrite2ByteMask(REG_112452, 0x0100, 0xFFFF); // coarse tune each step time
        MDrv_WriteByteMask(REG_11244D, 0x0A, 0x3F); // fine tune settel times
    }




    //mask interrupt
   // MDrv_WriteByte(REG_112181 + wOffset, 0xFF); //combo irq mask wOffset!!!!!!





    //word boundary by RD suggest
   // MDrv_WriteByteMask(REG_16051D + wOffset, 0xFF, 0xFF);
   // MDrv_WriteByteMask(REG_160521 + wOffset, 0xFF, 0xFF);
   // MDrv_WriteByteMask(REG_160525 + wOffset, 0xFF, 0xFF);
   // MDrv_WriteByteMask(REG_160529 + wOffset, 0xFF, 0xFF);

    if(bDual)
    {
        switch (enInputPort)
        {
            case MSCombo_TMDS_PORT_0:
                mhal_tmds_Initial( (MSCombo_TMDS_PORT_INDEX)(enInputPort+1), FALSE);
                mhal_tmds_MaskComboIRQ((MSCombo_TMDS_PORT_INDEX)(enInputPort+1), FALSE);
                MDrv_WriteByteMask(REG_160764, 0x04, 0x04); // [2]: small DE
                MDrv_WriteByteMask(REG_160A0D, 0x00, 0x0C); // [11] : enable video mute = 0; [10] : blanking when AVmute is active = 0
                #if 0   //for HDCP main/sub signal sync setting
                    MDrv_WriteByteMask(REG_160633 + wOffset, 0, BIT7); //sub lane setting

                    wOffset = _mhal_tmds_bank_offset(enInputPort);
                    MDrv_WriteByteMask(REG_160633 + wOffset, 0, BIT7); //main land setting
                #endif
            break;
            case MSCombo_TMDS_PORT_1:
                mhal_tmds_Initial( (MSCombo_TMDS_PORT_INDEX)(enInputPort-1), FALSE);
                mhal_tmds_MaskComboIRQ((MSCombo_TMDS_PORT_INDEX)(enInputPort-1), FALSE);
                MDrv_WriteByteMask(REG_160264, 0x04, 0x04); // [2]: small DE
                MDrv_WriteByteMask(REG_16050D, 0x00, 0x0C); // [3] : enable video mute = 0; [2] : blanking when AVmute is active = 0
                #if 0   //for HDCP main/sub signal sync setting
                    MDrv_WriteByteMask(REG_160633 + wOffset, 0, BIT7); //sub lane setting

                    wOffset = _mhal_tmds_bank_offset(enInputPort);
                    MDrv_WriteByteMask(REG_160633 + wOffset, 0, BIT7); //main lane setting
                #endif
            break;
            default:
                //invalid port index, return to prevent the code from accessing illegal register address
                //return;
            break;
        }
    }


    //switch to hdmi old mode
    #if 0
    MDrv_WriteByte(0x112020 + wOffset, 0x0000); //SWAP_DCDR_UPDN_POLITY; old mode=0, default = 1;

    MDrv_WriteByteMask(0x112029 + wOffset, 0x10, 0x10); //PHFSM0_FST_EN
    MDrv_WriteByte(0x112028 + wOffset, 0x80); //PHFSM0_FAST_INTERVAL
    MDrv_WriteByteMask(0x11202B + wOffset, 0x10, 0x10); //PHFSM1_FST_EN
    MDrv_WriteByte(0x11202A + wOffset, 0x80); //PHFSM1_FAST_INTERVAL
    MDrv_WriteByteMask(0x11202D + wOffset, 0x10, 0x10); //PHFSM2_FST_EN
    MDrv_WriteByte(0x11202C + wOffset, 0x80); //PHFSM2_FAST_INTERVAL

    MDrv_WriteByteMask(0x1120DF + wOffset, 0x0F, 0x0F); //gc_en_phd_fb_ov
    MDrv_WriteByteMask(0x1120EB + wOffset, 0x00, 0x78); //gc_phd_fb_ov
    MDrv_WriteByteMask(0x1120B8 + wOffset, 0x0F, 0x0F); //REG_SEL_PHDCLK
    #endif

    //enable new DCDR low pass filter
    //for U02:
    wOffset = _mhal_tmds_phy_offset(enInputPort);
    MDrv_WriteByteMask(REG_11205D + wOffset, 0x3E, 0x3E);  //CR lock success threshold time, to avoid CLK_Valid interrupt assert by accident.


    MDrv_WriteByte(REG_112020 + wOffset, 0x1D);
    MDrv_WriteByte(REG_112021 + wOffset, 0x00);    //[0]               reg_ph_update_timer_dis
                                                //[1]               reg_dp_dcdr_eco_en
                                                //[2]               reg_early_late_no_vote
                                                //[3]               reg_enable_phase_step
                                                //[4]               reg_swap_dcdr_updn_polity

    // upper_boundary ? filter depth, larger => PHDAC code change slow
    MDrv_WriteByte(REG_112030 + wOffset, 0xFF);
    MDrv_WriteByte(REG_112031 + wOffset, 0x00);

    // lower_boundary ? inverse of upper boundary
    MDrv_WriteByte(REG_112032 + wOffset, 0x00);
    MDrv_WriteByte(REG_112033 + wOffset, 0xFF);

    // Set Cbus pull down 100K
    _mhal_tmds_SetCbusPullDown100K(enInputPort, TRUE);

    // Disable SCDC clear status bit
    _mhal_tmds_ClearSCDCStatusFlag(enInputPort, TMDS_SCDC_ACCESS_ADDERSS_A8);

    if(!bReadEfuse)
    {
        _mhal_tmds_GetEfuseSettingValue();

        bReadEfuse = TRUE;
    }
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_EnableIRQ()
//  [Description]:
//                  enable certain port's IRQ
//  [Arguments]:
//                  enInputPort : combo port
//  [Return]:
//                  void
//
//**************************************************************************
void mhal_tmds_EnableIRQ(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    if((enInputPort == MSCombo_TMDS_PORT_0) || (enInputPort == MSCombo_TMDS_PORT_1))
        MDrv_WriteByteMask(REG_100E71, (1 << (enInputPort + 1)), (1 << (enInputPort + 1))); //eanble ISR
    else if ((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
        MDrv_WriteByteMask(REG_100E71, (1 << 3), (1 << 3)); //eanble ISR
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_MaskComboIRQ()
//  [Description]:
//                  mask combo_TMDS IRQ
//  [Arguments]:
//                  enInputPort : combo port, bFlag : True to enable clock stable irq, False to disable.
//  [Return]:
//                  void
// combo_rx_top (1606)_2e -> combo_phy_1 (1121)_40[15:8]
//**************************************************************************
void mhal_tmds_MaskComboIRQ(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bFlag)
{
    _mhal_tmds_SetClockValidInterrupt(enInputPort, bFlag);
    //_mhal_tmds_SetNoInputInterrupt(enInputPort, bFlag);
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_HDMIGetPktStatus()
//  [Description]:
//                  use to get HDMI received packet status
//  [Arguments]:
//                  enInputPort : combo port
//  [Return]:
//                  [0] : mpeg infoframe
//                  [1] : audio infoframe
//                  [2] : SPD
//                  [3] : AVI infoframe
//                  [4] : GC packet
//                  [5] : Audio sample packet
//                  [6] : ACR packet
//                  [7] : Vendor specific infoframe
//                  [8] : null packet
//                  [9] : ISRC2
//                  [A] : ISRC
//                  [B] : ACP
//                  [C] : DSD
//                  [D] : Gamut metadata packet
//                  [E] : HBR
//**************************************************************************
WORD mhal_tmds_HDMIGetPktStatus(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    WORD temp = 0;

    if(enInputPort == MSCombo_TMDS_PORT_0)
    {
        temp = MDrv_Read2Byte(REG_160502);
        MDrv_Write2Byte(REG_160502, 0xFFFF);
    }
    else if(enInputPort == MSCombo_TMDS_PORT_1)
    {
        temp = MDrv_Read2Byte(REG_160A02);
        MDrv_Write2Byte(REG_160A02, 0xFFFF);
    }
    else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
    {
        temp = MDrv_Read2Byte(REG_161102);
        MDrv_Write2Byte(REG_161102, 0xFFFF);
    }

    return temp;
}


//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_HDMIGetErrorStatus()
//  [Description]:
//                  use to return HDMI error status
//  [Arguments]:
//                  enInputPort : combo port
//  [Return]:
//                  [0] : BCH error (corrected)
//                  [1] : BCH error
//                  [2] : Checksum error
//                  [3] : Unsupported packet received
//                  [4] : Audio sample error
//                  [5] : Audio sample parity bit error
//                  [6] : Deep color FIFO overflow
//                  [7] : Deep color FIFO underflow
//**************************************************************************
BYTE mhal_tmds_HDMIGetErrorStatus(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    BYTE temp = 0;

    if(enInputPort == MSCombo_TMDS_PORT_0)
    {
        temp = MDrv_ReadByte(REG_160508);
        MDrv_WriteByteMask(REG_160508, 0xFF, 0xFF);
    }
    else if(enInputPort == MSCombo_TMDS_PORT_1)
    {
        temp = MDrv_Read2Byte(REG_160A08);
        MDrv_WriteByteMask(REG_160A08, 0xFF, 0xFF);
    }
    else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
    {
        temp = MDrv_Read2Byte(REG_161108);
        MDrv_WriteByteMask(REG_161108, 0xFF, 0xFF);
    }

    return temp;
}


//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_DE_Stable()
//  [Description]:
//                  check input timing is stable or not
//  [Arguments]:
//                  enInputPort : combo port
//  [Return]:
//                  TRUE : Stable
//                  FALSE : Unstable
//**************************************************************************
Bool mhal_tmds_DE_Stable(MSCombo_TMDS_PORT_INDEX enInputPort)
{
   if(enInputPort == MSCombo_TMDS_PORT_0)
   {
       if(MDrv_ReadByte(REG_160262) & 0x40)
           return TRUE;
       else
           return FALSE;
   }
   else if(enInputPort == MSCombo_TMDS_PORT_1)
   {
       if(MDrv_ReadByte(REG_160762) & 0x40)
           return TRUE;
       else
           return FALSE;
   }
   else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
   {
       if(MDrv_ReadByte(REG_160C62) & 0x40)
           return TRUE;
       else
           return FALSE;
   }
   else
       return FALSE;
}


//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_Clock_Stable()
//  [Description]:
//                  check input clock is stable or not
//  [Arguments]:
//                  enInputPort : combo port
//  [Return]:
//                  TRUE : Stable
//                  FALSE : Unstable
//**************************************************************************
Bool mhal_tmds_Clock_Stable(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    WORD wOffset;

    wOffset = _mhal_tmds_phy_offset(enInputPort);

    if(MDrv_Read2Byte(REG_112064 + wOffset) & 0x8888)
        return TRUE;
    else
        return FALSE;
}


//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_GetInputType()
//  [Description]:
//                  check input is DVI or HDMI
//  [Arguments]:
//                  enInputPort : combo port
//  [Return]:
//                  TRUE : HDMI
//                  FALSE : DVI
//**************************************************************************
BYTE mhal_tmds_GetInputType(MSCombo_TMDS_PORT_INDEX enInputPort)
{
   if(enInputPort == MSCombo_TMDS_PORT_0)
   {
       if(MDrv_ReadByte(REG_100602) & 0x01)
           return 1;
       else
           return 0;
   }
   else if(enInputPort == MSCombo_TMDS_PORT_1)
   {
       if(MDrv_ReadByte(REG_100B02) & 0x01)
           return 1;
       else
           return 0;
   }
   else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
   {
       if(MDrv_ReadByte(REG_161002) & 0x01)
           return 1;
       else
           return 0;
   }
   else
       return 0;
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_SubDEChangeReset()
//  [Description]:
//                  reset DE change for sub link
//  [Arguments]:
//                  enInputPort : combo port
//  [Return]:
//
//**************************************************************************
void mhal_tmds_SubDEChangeReset(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    if(enInputPort == MSCombo_TMDS_PORT_0)
    {
        MDrv_WriteByteMask(REG_160762, 0x02, 0x02); // reset P1
        MDrv_WriteByteMask(REG_160762, 0x00, 0x02);
    }
    else if(enInputPort == MSCombo_TMDS_PORT_1)
    {
        MDrv_WriteByteMask(REG_160262, 0x02, 0x02); // reset P0
        MDrv_WriteByteMask(REG_160262, 0x00, 0x02);
    }
    else
    {
        TMDS_PRINT("Port: 0x%x, no need\r\n", enInputPort);
    }
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_IsDualLink()
//  [Description]:
//                  check input is "Dual" or "Single" by small DE status of the sub lane.
//  [Arguments]:
//                  enInputPort : combo port
//  [Return]:
//                  TRUE : Dual link
//                  FALSE : Single link
//**************************************************************************
Bool mhal_tmds_IsDualLink(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    WORD wTmpValue = 0;
    BYTE i, debounceCnt = 10;
    Bool isDual = TRUE;

    //solution for dual link cable coupling issue;
    for ( i=0; i < debounceCnt; i++ )
    {
        if(enInputPort == MSCombo_TMDS_PORT_0)
        {
            wTmpValue = MDrv_ReadByte(REG_160762);
        }
        else if(enInputPort == MSCombo_TMDS_PORT_1)
        {
            wTmpValue = MDrv_ReadByte(REG_160262);
        }

        if (!(wTmpValue & 0x40))
        {
            isDual = FALSE;
            break;
        }
        else isDual = TRUE;
    }
    return isDual;

}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_MainDEChangeReset()
//  [Description]:
//                  reset DE change for main link
//  [Arguments]:
//                  enInputPort : combo port
//  [Return]:
//
//**************************************************************************
void mhal_tmds_MainDEChangeReset(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    if(enInputPort == MSCombo_TMDS_PORT_0)
    {
        MDrv_WriteByteMask(REG_160262, 0x02, 0x02); // reset P0
        MDrv_WriteByteMask(REG_160262, 0x00, 0x02);
    }
    else if(enInputPort == MSCombo_TMDS_PORT_1)
    {
        MDrv_WriteByteMask(REG_160762, 0x02, 0x02); // reset P1
        MDrv_WriteByteMask(REG_160762, 0x00, 0x02);
    }
    else
    {
        TMDS_PRINT("Port: 0x%x, no need\r\n", enInputPort);
    }
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_IsMainLinkStable()
//  [Description]:
//                  check if DE stable for main link of dual DVI
//  [Arguments]:
//                  enInputPort : combo port
//  [Return]:
//                  TRUE : DE of main link is stable
//                  FALSE : DE of main link is unstable
//**************************************************************************
Bool mhal_tmds_IsMainLinkStable(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    WORD wTmpValue = 0;
    BYTE i, debounceCnt = 10;
    Bool isStable= TRUE;

    //solution for dual link cable coupling issue;
    for ( i=0; i < debounceCnt; i++ )
    {
        if(enInputPort == MSCombo_TMDS_PORT_0)
        {
            wTmpValue = MDrv_Read2Byte(REG_160262);
        }
        else if(enInputPort == MSCombo_TMDS_PORT_1)
        {
            wTmpValue = MDrv_Read2Byte(REG_160762);
        }

        if (!(wTmpValue & 0x40))
        {
            isStable = FALSE;
            break;
        }
        else isStable = TRUE;
    }

    return isStable;

}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_DualLink_ComboMuxClk()
//  [Description]:
//                  TBD:
//  [Arguments]:
//                  enInputPort : combo port
//                  enInputPortSwitch: combo port
//  [Return]:
//                  void
//
//**************************************************************************
void mhal_tmds_DualLink_ComboMuxClk(MSCombo_TMDS_PORT_INDEX enInputPort, MSCombo_TMDS_PORT_INDEX enInputPortSwitch)
{
    BYTE u8InputPort, SCDetWin=0;
    BYTE u8ComboMux = (BYTE)enInputPortSwitch;
    BYTE u8ComboCLK = (BYTE)enInputPortSwitch;
    WORD u16SCMask;

    for( u8InputPort=First_Input_Port; u8InputPort < Input_Nums; u8InputPort++ )
    {
        if((MSCombo_TMDS_PORT_INDEX)(g_InputPort[u8InputPort].eIPMux-1) == enInputPort)
        {
            SCDetWin = 0;
            u16SCMask = MapPort2ScMask(u8InputPort);
            while( u16SCMask )
            {
                if( u16SCMask & BIT0 )
                {
                    //Combo Mux Select
                    switch(SCDetWin)
                    {
                        case SCL0_SUB:
                            MDrv_WriteByteMask(REG_100EE8, u8ComboMux << 4, 0xF0);
                            MDrv_WriteByteMask(REG_100EF0, u8ComboCLK << 4, 0xF0);
                            MDrv_WriteByteMask(REG_120F33, u8ComboCLK, 0x0F);
                            break;
                        case SCL0_MAIN:
                            MDrv_WriteByteMask(REG_100EE8, u8ComboMux, 0x0F);
                            MDrv_WriteByteMask(REG_100EF0, u8ComboCLK, 0x0F);
                            MDrv_WriteByteMask(REG_120F40, u8ComboCLK, 0x0F);
                            break;
                        case SCR0_SUB:
                            MDrv_WriteByteMask(REG_100EEB, u8ComboMux, 0x0F);
                            MDrv_WriteByteMask(REG_100EF3, u8ComboCLK, 0x0F);
                            MDrv_WriteByteMask(REG_120F43, u8ComboCLK, 0x0F);
                            break;
                        case SCR0_MAIN:
                            MDrv_WriteByteMask(REG_100EEA, u8ComboMux << 4, 0xF0);
                            MDrv_WriteByteMask(REG_100EF2, u8ComboCLK << 4, 0xF0);
                            MDrv_WriteByteMask(REG_120F44, u8ComboCLK, 0x0F);
                            break;
                        case SCL0_OFFLINE:
                            MDrv_WriteByteMask(REG_100EE9, u8ComboMux, 0x0F);
                            MDrv_WriteByteMask(REG_100EF1, u8ComboCLK, 0x0F);
                            MDrv_WriteByteMask(REG_120F32, u8ComboCLK, 0x0F);
                            break;
                    }
                }

                u16SCMask >>= 1;
                SCDetWin++;
            }
        }
    }
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_DualLink_Setting()
//  [Description]:
//                  use to config DVI dual link setting
//  [Arguments]:
//                  enInputPort : combo port
//                  bFlag :
//                  1 : enable dual link setting
//                  0 : disable dual link setting
//  [Return]:
//                  None
//
//**************************************************************************
void mhal_tmds_DualLink_Setting(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bFlag)
{
    WORD wOffset;
    Bool bIsSwapped;
  //  wOffset = _mhal_tmds_phy_offset(enInputPort);

    switch (enInputPort)
    {
        case MSCombo_TMDS_PORT_0:
            MDrv_WriteByteMask(REG_162F34, bFlag?0x02:0x00, 0x03);
            bIsSwapped = FALSE;
        break;
        case MSCombo_TMDS_PORT_1:
            MDrv_WriteByteMask(REG_162F34, bFlag?0x02:0x00, 0x03);
            bIsSwapped = TRUE;
        break;
        default:
            //invalid port index, return to prevent the code from accessing illegal register address
            return;
        break;
    }

  //  if(MDrv_ReadByte(REG_112160) & 0x08)
  //  {
      //  MDrv_Write2Byte(REG_1120D6 + wOffset, bFlag ? 0x0707 : 0x0702); //Main:[0]: Enable dual clk; [2]: 2x Pixel clk
      //  MDrv_Write2Byte(REG_112014 + wOffset, 0x0040); // [6]: reg_af_ls_20out_sel=1
      //  MDrv_Write2Byte(REG_1120B4 + wOffset, 0x0000); // [2]: disable reg_atop_en_clko_tmds2x
      //  MDrv_Write2Byte(REG_112108 + wOffset, bFlag ? 0x0001 : 0x0000); // [0]: reg_atop_en_clkpix2x
  //  }
  //  else
  //  {
  //      MDrv_Write2Byte(REG_1120D6, bFlag ? 0x0706 : 0x0702); //Main:[0]: Enable dual clk; [2]: 2x Pixel clk
 //       MDrv_Write2Byte(REG_112014, 0x0040); // [6]: reg_af_ls_20out_sel=1
 //       MDrv_Write2Byte(REG_1120B4, 0x0004); // [2]: disable reg_atop_en_clko_tmds2x
 //   }

    //main port is 0
    if ( !bIsSwapped )
    {
        // main port 0
        wOffset = _mhal_tmds_phy_offset(enInputPort);

        MDrv_Write2Byte(REG_1120D6 + wOffset, bFlag ? 0x0707 : 0x0702); //Main:[0]: Enable dual clk; [2]: 2x Pixel clk
        MDrv_Write2Byte(REG_112014 + wOffset, 0x0040); // [6]: reg_af_ls_20out_sel=1
        MDrv_Write2Byte(REG_1120B4 + wOffset, 0x0000); // [2]: disable reg_atop_en_clko_tmds2x
        MDrv_Write2Byte(REG_112108 + wOffset, bFlag ? 0x0001 : 0x0000); // [0]: reg_atop_en_clkpix2x

        // sub port 1
        wOffset = _mhal_tmds_phy_offset((MSCombo_TMDS_PORT_INDEX)(enInputPort + 1));

        MDrv_Write2Byte(REG_1120D6 + wOffset, bFlag ? 0x0706 : 0x0000); //Main:[0]: Enable dual clk; [2]: 2x Pixel clk
        MDrv_Write2Byte(REG_112014 + wOffset, 0x0040); // [6]: reg_af_ls_20out_sel=1
        MDrv_Write2Byte(REG_1120B4 + wOffset, 0x0002); // [2]: disable reg_atop_en_clko_tmds2x
        MDrv_Write2Byte(REG_112108 + wOffset, bFlag ? 0x0001 : 0x0000); // [0]: reg_atop_en_clkpix2x

        MDrv_WriteByteMask(REG_100E21, bFlag ? 0x00 : 0, 0x20); // Select main port0
        MDrv_WriteByteMask(REG_100E41, bFlag ? 0x20 : 0, 0x20);
        MDrv_WriteByteMask(REG_160256, bFlag ? 0x02 : 0, 0x0F); // Select cycle align port0
        MDrv_WriteByteMask(REG_160756, bFlag ? 0x00 : 0, 0x0F);
        MDrv_WriteByteMask(REG_100E66, bFlag ? 0x01 : 0, 0x03); // Select ddc main port0 and x76 for port1
        MDrv_WriteByteMask(REG_100606, bFlag ? 0x00 : 0, 0x80);
        MDrv_WriteByteMask(REG_100B06, bFlag ? 0x80 : 0, 0x80);
        MDrv_WriteByteMask(REG_1606C0, bFlag ? 0x01 : 0, 0x01); // Select output port0
        MDrv_WriteByteMask(REG_160756, bFlag ? 0x01 : 0, 0x01); // Switch dvi decoder data input / hdcp ctrl2_0 from dual-link sub-channel
#if 0
        // Set Port0
        MDrv_WriteByteMask(REG_1120D6,0x07, 0x07); // [0]: reg_atop_en_clko_dvidual; [1]: reg_atop_en_clk_pix; [2]: reg_atop_en_clk_pix_2x
        MDrv_WriteByteMask(REG_112014,0x40, 0x40); // [6]: reg_af_ls_20out_sel

        // Set Port1
        MDrv_WriteByteMask(REG_1122D6,0x06, 0x07); // [0]: reg_atop_en_clko_dvidual; [1]: reg_atop_en_clk_pix; [2]: reg_atop_en_clk_pix_2x
        MDrv_WriteByteMask(REG_112214,0x40, 0x40); // [6]: reg_af_ls_20out_sel
        MDrv_WriteByteMask(REG_1122B4,0x02, 0x02); // [1]: reg_atop_en_clki_dvidual
#endif
#if 0
        //[Main Port] Settings
        wOffset = _mhal_tmds_bank_offset(enInputPort);

        //if Odin2
        //MDrv_WriteByteMask(REG_160513 + wOffset, bFlag ? 0x00 : 0, (BIT4|BIT5)); //BK:TOP, main enable dual link data in
        //else
        MDrv_WriteByteMask(REG_160513 + wOffset, bFlag ? 0x20 : 0, 0x20); //BK:TOP, main enable dual link data in
        MDrv_WriteByteMask(REG_160633 + wOffset, bFlag ? 0x40 : 0, 0x40); //main, dual fifo
        MDrv_WriteByteMask(REG_160632 + wOffset, bFlag ? 0x10 : 0, 0x10); //enable of dual out FIFO

        //[Sub Port] Settings
        wOffset = _mhal_tmds_bank_offset((MSCombo_TMDS_PORT_INDEX)(enInputPort + 1));

        MDrv_WriteByteMask(REG_160633 + wOffset, 0x20, 0x20);
        MDrv_WriteByteMask(REG_160513 + wOffset, bFlag ? 0x10 : 0, 0x30); //BK: TOP, sub: enable dual link data out

        //[Index Relative] Settings
        // 3: start from BIT2, and ((Sub Port Index) = (Main Port Index) + 1), so index should be (Main Port Index + 1).
        MDrv_WriteByteMask(REG_100EF7, bFlag ? (1 << (enInputPort + 3)): 0, 0xFC); // according to "SUB" port, switch lane clock
        //MDrv_WriteByteMask(REG_162F34, (1 << (enInputPort + 1)), 0x1F);

        mhal_tmds_DualLink_ComboMuxClk(enInputPort, enInputPort);
#endif
#if 0
        //adding for Odin 2
        MDrv_WriteByteMask(REG_100EE8, bFlag ? enInputPort + 1 : enInputPort, 0x0F); //sc0_src_sel: sub port index.
        MDrv_WriteByteMask(REG_100EF0, bFlag ? enInputPort + 1 : enInputPort, 0x0F); //reg_combo2sc_clk_sel_0: sub port index
        //2: start from BIT2;
        //MDrv_WriteByteMask(REG_100EF7, bFlag ? (1 << (enInputPort + 2)) : 0, 0xFC); //main port index;

        MDrv_WriteByteMask(REG_160632 + wOffset, bFlag ? BIT4 : 0, BIT4);
        MDrv_WriteByteMask(REG_160633 + wOffset, bFlag ? (BIT4|BIT5) : BIT5, (BIT4|BIT5|BIT6|BIT7));
        //msWrite2ByteMask(REG_160632 + wOffset, 0x7310, 0x7310);
        //msWrite2ByteMask(REG_160632 + wOffset, bFlag ? 0x7310 : 0x6380, 0xFFFF);
#endif
    }
    //main port is 1
    else
    {
        // main port 1
        wOffset = _mhal_tmds_phy_offset(enInputPort);

        MDrv_Write2Byte(REG_1120D6 + wOffset, bFlag ? 0x0707 : 0x0702); //Main:[0]: Enable dual clk; [2]: 2x Pixel clk
        MDrv_Write2Byte(REG_112014 + wOffset, 0x0040); // [6]: reg_af_ls_20out_sel=1
        MDrv_Write2Byte(REG_1120B4 + wOffset, 0x0000); // [2]: disable reg_atop_en_clko_tmds2x
        MDrv_Write2Byte(REG_112108 + wOffset, bFlag ? 0x0001 : 0x0000); // [0]: reg_atop_en_clkpix2x

        // sub port 0
        wOffset = _mhal_tmds_phy_offset((MSCombo_TMDS_PORT_INDEX)(enInputPort - 1));

        MDrv_Write2Byte(REG_1120D6 + wOffset, bFlag ? 0x0706 : 0x0000); //Main:[0]: Enable dual clk; [2]: 2x Pixel clk
        MDrv_Write2Byte(REG_112014 + wOffset, 0x0040); // [6]: reg_af_ls_20out_sel=1
        MDrv_Write2Byte(REG_1120B4 + wOffset, 0x0002); // [2]: disable reg_atop_en_clko_tmds2x
        MDrv_Write2Byte(REG_112108 + wOffset, bFlag ? 0x0001 : 0x0000); // [0]: reg_atop_en_clkpix2x

        MDrv_WriteByteMask(REG_100E21, bFlag ? 0x20 : 0, 0x20); // Select main port1
        MDrv_WriteByteMask(REG_100E41, bFlag ? 0x00 : 0, 0x20);
        MDrv_WriteByteMask(REG_160256, bFlag ? 0x00 : 0, 0x0F); // Select cycle align port1
        MDrv_WriteByteMask(REG_160756, bFlag ? 0x02 : 0, 0x0F);
        MDrv_WriteByteMask(REG_100E66, bFlag ? 0x02 : 0, 0x03); // Select ddc main port1 and x76 for port0
        MDrv_WriteByteMask(REG_100606, bFlag ? 0x80 : 0, 0x80);
        MDrv_WriteByteMask(REG_100B06, bFlag ? 0x00 : 0, 0x80);
        MDrv_WriteByteMask(REG_160BC0, bFlag ? 0x01 : 0, 0x01); // Select output port1
        MDrv_WriteByteMask(REG_160256, bFlag ? 0x01 : 0, 0x01); // Switch dvi decoder data input / hdcp ctrl2_0 from dual-link sub-channel
#if 0
        // Set Port1
        MDrv_WriteByteMask(REG_1122D6,0x07, 0x07); // [0]: reg_atop_en_clko_dvidual; [1]: reg_atop_en_clk_pix; [2]: reg_atop_en_clk_pix_2x
        MDrv_WriteByteMask(REG_112214,0x40, 0x40); // [6]: reg_af_ls_20out_sel

        // Set Port0
        MDrv_WriteByteMask(REG_1120D6,0x06, 0x07); // [0]: reg_atop_en_clko_dvidual; [1]: reg_atop_en_clk_pix; [2]: reg_atop_en_clk_pix_2x
        MDrv_WriteByteMask(REG_112014,0x40, 0x40); // [6]: reg_af_ls_20out_sel
        MDrv_WriteByteMask(REG_1120B4,0x02, 0x02); // [1]: reg_atop_en_clki_dvidual
#endif
#if 0
        //[Main Port] Settings
        wOffset = _mhal_tmds_bank_offset(enInputPort);

        //if Odin2
        MDrv_WriteByteMask(REG_160513 + wOffset, bFlag ? 0x20 : 0, (BIT4|BIT5)); //BK:TOP, main enable dual link data in
        //else
        //MDrv_WriteByteMask(REG_160513 + wOffset, bFlag ? 0x20 : 0, 0x20); //BK:TOP, main enable dual link data in
        MDrv_WriteByteMask(REG_160633 + wOffset, bFlag ? 0x40 : 0, 0x40); //main, dual fifo
        MDrv_WriteByteMask(REG_160632 + wOffset, bFlag ? 0x10 : 0, 0x10); //enable of dual out FIFO

        //[Sub Port] Settings
        wOffset = _mhal_tmds_bank_offset((MSCombo_TMDS_PORT_INDEX)(enInputPort - 1));

        MDrv_WriteByteMask(REG_160633 + wOffset, 0x20, 0x20);
        MDrv_WriteByteMask(REG_160513 + wOffset, bFlag ? 0x10 : 0, 0x30); //BK: TOP, sub: enable dual link data out

        //[Index Relative] Settings
        // 3: start from BIT2, and ((Sub Port Index) = (Main Port Index) - 1), so index should be (Main Port Index - 1).
        //MDrv_WriteByteMask(REG_100EF7, bFlag ? (1 << (enInputPort + 1)): 0, 0xFC); // according to "SUB" port, switch lane clock
        //MDrv_WriteByteMask(REG_162F34, (1 << (enInputPort)), 0x1F);

        //adding for Odin 2
        if(bFlag)
            mhal_tmds_DualLink_ComboMuxClk(enInputPort, (MSCombo_TMDS_PORT_INDEX)(enInputPort - 1));
        else
            mhal_tmds_DualLink_ComboMuxClk(enInputPort, enInputPort);

        //2: start from BIT2;
        MDrv_WriteByteMask(REG_100EF7, bFlag ? (1 << (enInputPort + 2)) : 0, 0xFC); //main port index;

        MDrv_WriteByteMask(REG_160632 + wOffset, bFlag ? BIT4 : 0, BIT4);
        MDrv_WriteByteMask(REG_160633 + wOffset, bFlag ? (BIT4|BIT5) : BIT5, (BIT4|BIT5|BIT6|BIT7));
        //msWrite2ByteMask(REG_160632 + wOffset, 0x7310, 0x7310);
        //msWrite2ByteMask(REG_160632 + wOffset, bFlag ? 0x7310 : 0x6380, 0xFFFF);
#endif
    }
}

Bool mhal_tmds_Link_LockCheck(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bFlag)
{
    if(enInputPort!=0 && bFlag!=0){}
#if 0
    BYTE i;
    WORD wOffset;
    WORD wTmpValue;

    wOffset = _mhal_tmds_bank_offset(enInputPort);
    for(i=0;i<5;i++)
    {
        wTmpValue = MDrv_Read2Byte(REG_1607C4 + wOffset);
        if(wTmpValue & BIT7)
            break;
        else
        {
            switch (enInputPort)
            {
                case MSCombo_TMDS_PORT_0:
                    MDrv_WriteByteMask(REG_162F34, 0x00, 0x03);
                    MDrv_WriteByteMask(REG_162F34, 0x02, 0x03);
                break;
                case MSCombo_TMDS_PORT_2:
                    MDrv_WriteByteMask(REG_162F34, 0x00, 0x0C);
                    MDrv_WriteByteMask(REG_162F34, 0x08, 0x0C);
                break;
                case MSCombo_TMDS_PORT_1:
                    MDrv_WriteByteMask(REG_162F34, 0x00, 0x03);
                    MDrv_WriteByteMask(REG_162F34, 0x02, 0x03);
                break;
                case MSCombo_TMDS_PORT_3:
                    MDrv_WriteByteMask(REG_162F34, 0x00, 0x0C);
                    MDrv_WriteByteMask(REG_162F34, 0x08, 0x0C);
                break;
                default:
                    //invalid port index, return to prevent the code from accessing illegal register address
                    return;
                break;
            }

        }
    }
#endif
    return TRUE;
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_PowerControl()
//  [Description]:
//                  use to control TMDS clock and Data R-term
//  [Arguments]:
//                  enInputPort : combo port
//                  bFlag :
//                  1 : power on
//                  0 : power down R-term
//  [Return]:
//                  None
//**************************************************************************
void mhal_tmds_PowerControl(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bFlag)
{
    if(enInputPort == MSCombo_TMDS_PORT_0)
    {
        MDrv_WriteByteMask(REG_112107, bFlag ? 0:0x07, 0x07); // [10:8]: Power on P0 data r-term
        MDrv_WriteByteMask(REG_001724, bFlag ? 0:0x80, 0xFF); // [7]: Power on P0 clock r-term
        MDrv_WriteByteMask(REG_001725, 0x01, 0x01); // reg_p0_pd_cmos_sw =1
    }
    else if(enInputPort == MSCombo_TMDS_PORT_1)
    {
        MDrv_WriteByteMask(REG_112307, bFlag ? 0:0x07, 0x07); // [10:8]: Power on P1 data r-term
        MDrv_WriteByteMask(REG_001726, bFlag ? 0:0x80, 0xFF); // [7]: Power on P1 clock r-term
        MDrv_WriteByteMask(REG_001727, 0x01, 0x01); // reg_p1_pd_cmos_sw =1
    }
    else if(enInputPort == MSCombo_TMDS_PORT_2)
    {
        MDrv_WriteByteMask(REG_001720, bFlag ? 0:0x0E, 0x0E); // [3:1]: Power on P2 data r-term
        MDrv_WriteByteMask(REG_001720, bFlag ? 0:0x10, 0x10);  // [4]: Power on Port2 clock r-term
    }
    else if(enInputPort == MSCombo_TMDS_PORT_3)
    {
        MDrv_WriteByteMask(REG_001722, bFlag ? 0:0x0E, 0x0E); // [3:1]: Power on P2 data r-term
        MDrv_WriteByteMask(REG_001722, bFlag ? 0:0x10, 0x10);  // [4]: Power on Port2 clock r-term
    }
}


//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_Set_HPD()
//  [Description]:
//                  use to control Hot Plug pin
//  [Arguments]:
//                  enInputPort : combo port
//                  bSetHPD :
//                  1 : keep high
//                  0 : pull low
//  [Return]:
//                  None
//**************************************************************************
void mhal_tmds_Set_HPD(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bSetHPD)
{
    if(bSetHPD)
    {
        if(enInputPort == MSCombo_TMDS_PORT_0) // combo_0
        {
            hw_Set_HdcpHpd();
        }
        else if(enInputPort == MSCombo_TMDS_PORT_1) // combo_1
        {
            hw_Set_HdcpHpd1();
        }
        else if(enInputPort == MSCombo_TMDS_PORT_2) // combo_2
        {
            hw_Set_HdcpHpd2();
        }
        else if(enInputPort == MSCombo_TMDS_PORT_3) // combo_3
        {
            hw_Set_HdcpHpd3();
        }
    }
    else
    {
        if(enInputPort == MSCombo_TMDS_PORT_0) // combo_0
        {
            hw_Clr_HdcpHpd();
        }
        else if(enInputPort == MSCombo_TMDS_PORT_1) // combo_1
        {
            hw_Clr_HdcpHpd1();
        }
        else if(enInputPort == MSCombo_TMDS_PORT_2) // combo_2
        {
            hw_Clr_HdcpHpd2();
        }
        else if(enInputPort == MSCombo_TMDS_PORT_3) // combo_3
        {
            hw_Clr_HdcpHpd3();
        }

        _mhal_tmds_ResetHDMI20VersionFlag(enInputPort);
    }

}


//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_reset_status()
//  [Description]:
//                  use to reset packet content and packet status
//  [Arguments]:
//                  enInputPort : combo port
//                  bFlag : to reset packet content
//                  ucReset :
//                  [0] : reset AV mute
//                  [1] : reset color format in AVI (need clock)
//                  [2] : reset pixel repetition in AVI
//                  [3] : reset frame repetition ?
//                  [4] : reset pixel packing phase and color depth in GC packet
//                  [5] : reset deep color FIFO
//                  [6] : reserved
//                  [7] : reset packet received status
//  [Return]:
//                  None
//**************************************************************************
void mhal_tmds_reset_status(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bFlag, BYTE ucReset)
{
    if(enInputPort == MSCombo_TMDS_PORT_0)
    {
        if(bFlag)
        {
            MDrv_WriteByteMask(REG_1605BF, 0x80, 0x80); //reset packet content
            MDrv_WriteByteMask(REG_1605BF, 0x00, 0x80);
        }
        MDrv_WriteByteMask(REG_1605BF, ucReset, 0xFF); //reset packet status
        MDrv_WriteByteMask(REG_1605BF, 0, 0xFF);
    }
    else if(enInputPort == MSCombo_TMDS_PORT_1)
    {
        if(bFlag)
        {
            MDrv_WriteByteMask(REG_160ABF, 0x80, 0x80); //reset packet content
            MDrv_WriteByteMask(REG_160ABF, 0x00, 0x80);
        }
        MDrv_WriteByteMask(REG_160ABF, ucReset, 0xFF); //reset packet status
        MDrv_WriteByteMask(REG_160ABF, 0, 0xFF);
    }
    else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
    {
        if(bFlag)
        {
            MDrv_WriteByteMask(REG_1611BF, 0x80, 0x80); //reset packet content
            MDrv_WriteByteMask(REG_1611BF, 0x00, 0x80);
        }
        MDrv_WriteByteMask(REG_1611BF, ucReset, 0xFF); //reset packet status
        MDrv_WriteByteMask(REG_1611BF, 0, 0xFF);
    }
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_NoInputClk()
//  [Description]:
//                  use to check input clock status
//  [Arguments]:
//                  enInputPort : combo port
//  [Return]:
//                  TRUE : no input clock
//                  FALSE : have input clock
//**************************************************************************
Bool mhal_tmds_NoInputClk(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    WORD wOffset;

    wOffset = _mhal_tmds_phy_offset(enInputPort);

    if(MDrv_ReadByte(REG_112180 + wOffset) & 0x08) // no input clock
    {
       // printf("no input ohohohohohohohohohohoh\n");

       // MDrv_WriteByteMask(REG_112183 + wOffset, 0x08, 0x08); //clr
        MDrv_WriteByte(REG_112183 + wOffset, 0x08); //clr

       // MDrv_WriteByteMask(REG_112183 + wOffset, 0x00, 0x08);
        MDrv_WriteByte(REG_112183 + wOffset, 0x00);

       // MDrv_WriteByteMask(REG_112183 + wOffset, 0x00, 0x08);
        MDrv_WriteByte(REG_112183 + wOffset, 0x00);

        return 1;
    }
    else
        return 0;
}
//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_TimingChg()
//  [Description]:
//                  use to check timing chg
//  [Arguments]:
//                  enInputPort : combo port
//  [Return]:
//                  TRUE : chg
//                  FALSE : no chg
//**************************************************************************

Bool mhal_tmds_TimingChg(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    WORD wOffset;

    wOffset = _mhal_tmds_phy_offset(enInputPort);

    if(MDrv_ReadByte(REG_112180 + wOffset) & 0x40) // clock big change
    {
      //  MDrv_WriteByteMask(REG_112183 + wOffset, 0x40, 0x40); //clr
        MDrv_WriteByte(REG_112183 + wOffset, 0x40); //clr

      //  MDrv_WriteByteMask(REG_112183 + wOffset, 0x00, 0x40);
        MDrv_WriteByte(REG_112183 + wOffset, 0x00);

      //  MDrv_WriteByteMask(REG_112183 + wOffset, 0x00, 0x40);
        MDrv_WriteByte(REG_112183 + wOffset, 0x00);
        return TRUE;
    }
    else
        return FALSE;
}


//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_GetColor()
//  [Description]:
//                  use to check input color format from AVI packet content info
//  [Arguments]:
//                  enInputPort : combo port
//  [Return]:
//
//                  typedef struct
//                  {
//                      EN_COLOR_FORMAT_TYPE    ucColorType;
//                      EN_COLOR_RANGE_TYPE     ucColorRange;
//                      EN_COLORIMETRY_TYPE     ucColorimetry;
//                      EN_YPBPR_COLORIMETRY_TYPE   ucYuvColorimetry;
//                   } ST_COMBO_COLOR_FORMAT;
//
//**************************************************************************
//BYTE mhal_tmds_GetColor(MSCombo_TMDS_PORT_INDEX enInputPort)
ST_COMBO_COLOR_FORMAT mhal_tmds_GetColor(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    BYTE Y_value = 0;
    BYTE C_value = 0;
    BYTE Q_value = 0;

    //assign initial value
    ST_COMBO_COLOR_FORMAT ColorInfo = {COMBO_COLOR_FORMAT_DEFAULT, COMBO_COLOR_RANGE_DEFAULT, COMBO_COLORIMETRY_NONE, COMBO_YUV_COLORIMETRY_ITU601};

    //parsing AVI info frame packet
    if(enInputPort == MSCombo_TMDS_PORT_0)
    {
        Y_value = ((MDrv_ReadByte(REG_160580) & (BIT6|BIT5)) >> 5 ); // [6:5]: RGB or YCbCr
        C_value = ((MDrv_ReadByte(REG_160581) & (BIT7|BIT6)) >> 6 ); // [7:6]: Colorimetry
    }
    else if(enInputPort == MSCombo_TMDS_PORT_1)
    {
        Y_value = ((MDrv_ReadByte(REG_160A80) & (BIT6|BIT5)) >> 5 ); // [6:5]: RGB or YCbCr
        C_value = ((MDrv_ReadByte(REG_160A81) & (BIT7|BIT6)) >> 6 ); // [7:6]: Colorimetry
    }
    else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
    {
        Y_value = ((MDrv_ReadByte(REG_161180) & (BIT6|BIT5)) >> 5 ); // [6:5]: RGB or YCbCr
        C_value = ((MDrv_ReadByte(REG_161181) & (BIT7|BIT6)) >> 6 ); // [7:6]: Colorimetry
    }

    switch (Y_value)
    {
        case 0:
            ColorInfo.ucColorType = COMBO_COLOR_FORMAT_RGB;
        break;
        case 1:
            ColorInfo.ucColorType = COMBO_COLOR_FORMAT_YUV_422;
        break;
        case 2:
            ColorInfo.ucColorType = COMBO_COLOR_FORMAT_YUV_444;
        break;
        case 3:
            ColorInfo.ucColorType = COMBO_COLOR_FORMAT_YUV_420;
        break;
        default:
            ColorInfo.ucColorType = COMBO_COLOR_FORMAT_DEFAULT;
        break;
    }

    if((Y_value == 1) || (Y_value == 2)|| (Y_value == 3))
    {
        // [7:6]: Full or limit (for YCC)
        if(enInputPort == MSCombo_TMDS_PORT_0)
            Q_value = ((MDrv_ReadByte(REG_160584) & (BIT7|BIT6)) >> 6 );

        else if(enInputPort == MSCombo_TMDS_PORT_1)
            Q_value = ((MDrv_ReadByte(REG_160A84) & (BIT7|BIT6)) >> 6 );

        else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
            Q_value = ((MDrv_ReadByte(REG_161184) & (BIT7|BIT6)) >> 6 );

        switch (Q_value)
        {
            case 0:
                ColorInfo.ucColorRange = COMBO_COLOR_RANGE_LIMIT;
            break;
            case 1:
                ColorInfo.ucColorRange = COMBO_COLOR_RANGE_FULL;
            break;
            case 2:
                ColorInfo.ucColorRange = COMBO_COLOR_RANGE_RESERVED;
            break;
            default:
                ColorInfo.ucColorRange = COMBO_COLOR_RANGE_RESERVED;
            break;
        }
    }
    else
    {
        // [3:2]: Full or limit (for RGB)
        if(enInputPort == MSCombo_TMDS_PORT_0)
            Q_value = ((MDrv_ReadByte(REG_160582) & (BIT3|BIT2)) >> 2 );

        else if(enInputPort == MSCombo_TMDS_PORT_1)
            Q_value = ((MDrv_ReadByte(REG_160A82) & (BIT3|BIT2)) >> 2 );

        else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
            Q_value = ((MDrv_ReadByte(REG_161182) & (BIT3|BIT2)) >> 2 );

        switch (Q_value)
        {
            case 0:
                ColorInfo.ucColorRange = COMBO_COLOR_RANGE_DEFAULT;
            break;
            case 1:
                ColorInfo.ucColorRange = COMBO_COLOR_RANGE_LIMIT;
            break;
            case 2:
                ColorInfo.ucColorRange = COMBO_COLOR_RANGE_FULL;
            break;
            default:
                ColorInfo.ucColorRange = COMBO_COLOR_RANGE_RESERVED;
            break;
        }
    }

    // [5:4] extended colorimetry
    if (C_value == 0x03)
    {
        BYTE EC_value = 0;

        if(enInputPort == MSCombo_TMDS_PORT_0)
            Q_value = ((MDrv_ReadByte(REG_160582) & (BIT5|BIT4)) >> 4  );

        else if(enInputPort == MSCombo_TMDS_PORT_1)
            Q_value = ((MDrv_ReadByte(REG_160A82) & (BIT5|BIT4)) >> 4  );

        else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
            Q_value = ((MDrv_ReadByte(REG_161182) & (BIT5|BIT4)) >> 4  );

        switch (EC_value)
        {
            case 0:
                ColorInfo.ucColorimetry = COMBO_COLORIMETRY_xvYCC601;
            break;
            case 1:
                ColorInfo.ucColorimetry = COMBO_COLORIMETRY_xvYCC709;
            break;
            case 2:
                ColorInfo.ucColorimetry = COMBO_COLORIMETRY_sYCC601;
            break;
            case 3:
                ColorInfo.ucColorimetry = COMBO_COLORIMETRY_ADOBEYCC601;
            break;
            default:
                ColorInfo.ucColorimetry = COMBO_COLORIMETRY_NONE;
            break;
        }
    }

    switch(C_value)
    {
        case 0:
            ColorInfo.ucYuvColorimetry = COMBO_YUV_COLORIMETRY_NoData;
            break;
        case 1:
            ColorInfo.ucYuvColorimetry = COMBO_YUV_COLORIMETRY_ITU601;
            break;
        case 2:
            ColorInfo.ucYuvColorimetry = COMBO_YUV_COLORIMETRY_ITU709;
            break;
    }

    return ColorInfo;
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_GetITContent()
//  [Description]:
//                  use to obtain AVI packet IT content
//  [Arguments]:
//                  enInputPort : combo port
//  [Return]:
//                  none
//
//**************************************************************************
Bool mhal_tmds_GetITContent(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    if(enInputPort == MSCombo_TMDS_PORT_0)
    {
        if(MDrv_ReadByte(REG_160582) & BIT7)
            return 1;
        else
            return 0;
    }
    else if(enInputPort == MSCombo_TMDS_PORT_1)
    {
        if(MDrv_ReadByte(REG_160A82) & BIT7)
            return 1;
        else
            return 0;
    }
    else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
    {
        if(MDrv_ReadByte(REG_161182) & BIT7)
            return 1;
        else
            return 0;
    }
    else
        return 0;
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_GetScaling_Info()
//  [Description]:
//                  use to obtain AVI packet picture scaling info.
//  [Arguments]:
//                  enInputPort : combo port
//  [Return]:
//                  none
//
//**************************************************************************
BYTE mhal_tmds_GetScaling_Info(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    if(enInputPort == MSCombo_TMDS_PORT_0)
        return (MDrv_ReadByte(REG_160580) & (BIT1|BIT0));

    else if(enInputPort == MSCombo_TMDS_PORT_1)
        return (MDrv_ReadByte(REG_160A80) & (BIT1|BIT0));

    else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
        return (MDrv_ReadByte(REG_161180) & (BIT1|BIT0));

    return 0;
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_GetPacketContent()
//  [Description]:
//                  use to obtain HDMI packet contents
//  [Arguments]:
//                  enInputPort : combo port
//                  ucPacketType: indicate the type of the packet which is going to be extracted
//                  ucPacketLength: the total length to be extracted (byte unit)
//                  pPacketData: pointer, address which store return content
//  [Return]:
//                  none
//
//**************************************************************************
void mhal_tmds_GetPacketContent(MSCombo_TMDS_PORT_INDEX enInputPort, EN_PACKET_DEFINE_TYPE ucPacketType, BYTE ucPacketLength, BYTE *pPacketData)
{
    BYTE i;
    BYTE DataArray[ucPacketLength];
    BYTE MaxCntLength = 0;

    //initial value 0
    for (i=0; i < ucPacketLength; i++)
    {
        //*(pPacketData + i) = 0;
        DataArray[i] = 0;
    }

    switch (ucPacketType)
    {
        case COMBO_PACKET_NULL:
        break;

        case COMBO_PACKET_AUDIO_CLOCK_REGENERATION:
            //Hardware already extract packet content, we restore it back to packet format here;
            {
                BYTE SB[7] = {0, 0, 0, 0, 0, 0, 0};

                if(enInputPort == MSCombo_TMDS_PORT_0)
                {
                    SB[1] = MDrv_ReadByte(REG_160513) & 0x0F; // CTS[19:16]
                    SB[2] = MDrv_ReadByte(REG_160514); // CTS[15:8]
                    SB[3] = MDrv_ReadByte(REG_160515); // CTS[7:0]
                    SB[4] = (MDrv_ReadByte(REG_160513) & 0xF0) >> 4; // N[19:16]
                    SB[5] = MDrv_ReadByte(REG_160516); // N[15:8]
                    SB[6] = MDrv_ReadByte(REG_160517); // N[7:0]
                }
                else if(enInputPort == MSCombo_TMDS_PORT_1)
                {
                    SB[1] = MDrv_ReadByte(REG_160A13) & 0x0F; // CTS[19:16]
                    SB[2] = MDrv_ReadByte(REG_160A14); // CTS[15:8]
                    SB[3] = MDrv_ReadByte(REG_160A15); // CTS[7:0]
                    SB[4] = (MDrv_ReadByte(REG_160A13) & 0xF0) >> 4; // N[19:16]
                    SB[5] = MDrv_ReadByte(REG_160A16); // N[15:8]
                    SB[6] = MDrv_ReadByte(REG_160A17); // N[7:0]
                }
                else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
                {
                    SB[1] = MDrv_ReadByte(REG_161113) & 0x0F; // CTS[19:16]
                    SB[2] = MDrv_ReadByte(REG_161114); // CTS[15:8]
                    SB[3] = MDrv_ReadByte(REG_161115); // CTS[7:0]
                    SB[4] = (MDrv_ReadByte(REG_161113) & 0xF0) >> 4; // N[19:16]
                    SB[5] = MDrv_ReadByte(REG_161116); // N[15:8]
                    SB[6] = MDrv_ReadByte(REG_161117); // N[7:0]
                }

                MaxCntLength = (ucPacketLength > 7 ? 7 : ucPacketLength);

                for ( i=0; i < MaxCntLength; i++ )
                {
                    DataArray[i] = SB[i];
                }
            }
        break;

        case COMBO_PACKET_AUDIO_SAMPLE:
        break;

        case COMBO_PACKET_GENERAL_CONTROL:
            MaxCntLength = (ucPacketLength > 2 ? 2 : ucPacketLength);

            if(enInputPort == MSCombo_TMDS_PORT_0)
            {
                for ( i=0; i < MaxCntLength; i++ )
                {
                    DataArray[i] = MDrv_ReadByte(REG_16052A + i);
                }
            }
            else if(enInputPort == MSCombo_TMDS_PORT_1)
            {
                for ( i=0; i < MaxCntLength; i++ )
                {
                    DataArray[i] = MDrv_ReadByte(REG_160A2A + i);
                }
            }
            else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
            {
                for ( i=0; i < MaxCntLength; i++ )
                {
                    DataArray[i] = MDrv_ReadByte(REG_16112A + i);
                }
            }
        break;

        case COMBO_PACKET_ACP_PACKET:
            MaxCntLength = (ucPacketLength > 16 ? 16 : ucPacketLength);

            if(enInputPort == MSCombo_TMDS_PORT_0)
            {
                for ( i=0; i < MaxCntLength; i++ )
                {
                    DataArray[i] = MDrv_ReadByte(REG_16052E + i);
                }
            }
            else if(enInputPort == MSCombo_TMDS_PORT_1)
            {
                for ( i=0; i < MaxCntLength; i++ )
                {
                    DataArray[i] = MDrv_ReadByte(REG_160A2E + i);
                }
            }
            else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
            {
                for ( i=0; i < MaxCntLength; i++ )
                {
                    DataArray[i] = MDrv_ReadByte(REG_16112E + i);
                }
            }
         break;

        //isrc1: byte0~15; isrc2: byte 16~31
        case COMBO_PACKET_ISRC1_PACKET:
            MaxCntLength = (ucPacketLength > 16 ? 16 : ucPacketLength);

            if(enInputPort == MSCombo_TMDS_PORT_0)
            {
                MDrv_WriteByteMask(REG_16050F, 0x00, 0x20); // [13]: Original ISRC packet = 0
                for ( i=0; i < MaxCntLength; i++ )
                {
                    DataArray[i] = MDrv_ReadByte(REG_160540 + i);
                }
            }
            else if(enInputPort == MSCombo_TMDS_PORT_1)
            {
                MDrv_WriteByteMask(REG_160A0F, 0x00, 0x20);
                for ( i=0; i < MaxCntLength; i++ )
                {
                    DataArray[i] = MDrv_ReadByte(REG_160A40 + i);
                }
            }
            else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
            {
                MDrv_WriteByteMask(REG_16110F, 0x00, 0x20);
                for ( i=0; i < MaxCntLength; i++ )
                {
                    DataArray[i] = MDrv_ReadByte(REG_161140 + i);
                }
            }
        break;

        case COMBO_PACKET_ISRC2_PACKET:
            MaxCntLength = (ucPacketLength > 16 ? 16 : ucPacketLength);

            if(enInputPort == MSCombo_TMDS_PORT_0)
            {
                for ( i=0; i < MaxCntLength; i++ )
                {
                    DataArray[i] = MDrv_ReadByte(REG_160550 + i);
                }
            }
            else if(enInputPort == MSCombo_TMDS_PORT_1)
            {
                for ( i=0; i < MaxCntLength; i++ )
                {
                    DataArray[i] = MDrv_ReadByte(REG_160A50 + i);
                }
            }
            else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
            {
                for ( i=0; i < MaxCntLength; i++ )
                {
                    DataArray[i] = MDrv_ReadByte(REG_161150 + i);
                }
            }
        break;

        case COMBO_PACKET_ONE_BIT_AUDIO_SAMPLE:
        break;
        case COMBO_PACKET_DST_AUDIO:
        break;
        case COMBO_PACKET_HBR_AUDIO_STREAM:
        break;

        case COMBO_PACKET_GAMUT_METADATA:
            MaxCntLength = (ucPacketLength > 21 ? 21 : ucPacketLength);

            if(enInputPort == MSCombo_TMDS_PORT_0)
            {
                MDrv_WriteByteMask(REG_16050F, 0x30, 0x30); // [13]: GM packet = 1; [12]: output current affected GM packet to GMP register
                for ( i=0; i < MaxCntLength; i++ )
                {
                    DataArray[i] = MDrv_ReadByte(REG_160540 + i);
                }
            }
            else if(enInputPort == MSCombo_TMDS_PORT_1)
            {
                 MDrv_WriteByteMask(REG_160A0F, 0x30, 0x30);
                for ( i=0; i < MaxCntLength; i++ )
                {
                    DataArray[i] = MDrv_ReadByte(REG_160A40 + i);
                }
            }
            else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
            {
                 MDrv_WriteByteMask(REG_16110F, 0x30, 0x30);
                for ( i=0; i < MaxCntLength; i++ )
                {
                    DataArray[i] = MDrv_ReadByte(REG_161140 + i);
                }
            }

        break;

        case COMBO_PACKET_VS_INFOFRAME:
            MaxCntLength = (ucPacketLength > 29 ? 29 : ucPacketLength);

            if(enInputPort == MSCombo_TMDS_PORT_0)
            {
                for ( i=0; i < MaxCntLength; i++ )
                {
                    DataArray[i] = MDrv_ReadByte(REG_160560 + i);
                }
            }
            else if(enInputPort == MSCombo_TMDS_PORT_1)
            {
                for ( i=0; i < MaxCntLength; i++ )
                {
                    DataArray[i] = MDrv_ReadByte(REG_160A60 + i);
                }
            }
            else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
            {
                for ( i=0; i < MaxCntLength; i++ )
                {
                    DataArray[i] = MDrv_ReadByte(REG_161160 + i);
                }
            }
        break;

        case COMBO_PACKET_AVI_INFOFRAME:
            MaxCntLength = (ucPacketLength > 13 ? 13 : ucPacketLength);

            if(enInputPort == MSCombo_TMDS_PORT_0)
            {
                for ( i=0; i < MaxCntLength; i++ )
                {
                    DataArray[i] = MDrv_ReadByte(REG_160580 + i);
                }
            }
            else if(enInputPort == MSCombo_TMDS_PORT_1)
            {
                for ( i=0; i < MaxCntLength; i++ )
                {
                    DataArray[i] = MDrv_ReadByte(REG_160A80 + i);
                }
            }
            else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
            {
                for ( i=0; i < MaxCntLength; i++ )
                {
                    DataArray[i] = MDrv_ReadByte(REG_161180 + i);
                }
            }
        break;

        case COMBO_PACKET_SPD_INFOFRAME:
            MaxCntLength = (ucPacketLength > 25 ? 25 : ucPacketLength);

            if(enInputPort == MSCombo_TMDS_PORT_0)
            {
                for ( i=0; i < MaxCntLength; i++ )
                {
                    DataArray[i] = MDrv_ReadByte(REG_16058E + i);
                }
            }
            else if(enInputPort == MSCombo_TMDS_PORT_1)
            {
                for ( i=0; i < MaxCntLength; i++ )
                {
                    DataArray[i] = MDrv_ReadByte(REG_160A8E + i);
                }
            }
            else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
            {
                for ( i=0; i < MaxCntLength; i++ )
                {
                    DataArray[i] = MDrv_ReadByte(REG_16118E + i);
                }
            }
        break;

        case COMBO_PACKET_AUD_INFOFRAME:
            MaxCntLength = (ucPacketLength > 5 ? 5 : ucPacketLength);

            if(enInputPort == MSCombo_TMDS_PORT_0)
            {
                for ( i=0; i < MaxCntLength; i++ )
                {
                    DataArray[i] = MDrv_ReadByte(REG_1605A8 + i);
                }
            }
            else if(enInputPort == MSCombo_TMDS_PORT_1)
            {
                for ( i=0; i < MaxCntLength; i++ )
                {
                    DataArray[i] = MDrv_ReadByte(REG_160AA8 + i);
                }
            }
            else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
            {
                for ( i=0; i < MaxCntLength; i++ )
                {
                    DataArray[i] = MDrv_ReadByte(REG_1611A8 + i);
                }
            }
        break;

        case COMBO_PACKET_MPEG_INFOFRAME:
            MaxCntLength = (ucPacketLength > 5 ? 5 : ucPacketLength);

            if(enInputPort == MSCombo_TMDS_PORT_0)
            {
                for ( i=0; i < MaxCntLength; i++ )
                {
                    DataArray[i] = MDrv_ReadByte(REG_1605AE + i);
                }
            }
            else if(enInputPort == MSCombo_TMDS_PORT_1)
            {
                for ( i=0; i < MaxCntLength; i++ )
                {
                    DataArray[i] = MDrv_ReadByte(REG_160AAE + i);
                }
            }
            else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
            {
                for ( i=0; i < MaxCntLength; i++ )
                {
                    DataArray[i] = MDrv_ReadByte(REG_1611AE + i);
                }
            }
        break;

        case COMBO_PACKET_DP_MISC:
        break;
        default:
        break;
    }

    memcpy(pPacketData, DataArray, MaxCntLength);

}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_DetectCablePlug()
//  [Description]:
//                  detect if HDMI/DVI cable is attached.
//  [Arguments]:
//                  ucInputPort
//                  bFlag : TRUE -> SAR detect, FALSE -> GPIO detect
//  [Return]:
//                  Bool
//
//**************************************************************************
BYTE mhal_tmds_DetectCablePlug(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bFlag)
{
    Bool bCable5VDetect = FALSE;
    BYTE ucCableDetect = TMDS_CABLE_DETECT_NO_INPUT;
    BYTE ucCableSARDetect = 0;

    switch(enInputPort)
    {
        case MSCombo_TMDS_PORT_0:
            if(bFlag)
            {
                ucCableSARDetect = TMDS_CABLE_SAR_DETECT_PORT0;
            }
                else
            {
                bCable5VDetect = TMDS_CABLE_5V_DETECT_PORT0;
            }

            break;

        case MSCombo_TMDS_PORT_1:
            if(bFlag)
            {
                ucCableSARDetect = TMDS_CABLE_SAR_DETECT_PORT1;
            }
                else
            {
                bCable5VDetect = TMDS_CABLE_5V_DETECT_PORT1;
            }

            break;

        case MSCombo_TMDS_PORT_2:
            if(bFlag)
            {
                ucCableSARDetect = TMDS_CABLE_SAR_DETECT_PORT2;
            }
                else
            {
                bCable5VDetect = TMDS_CABLE_5V_DETECT_PORT2;
            }

            break;

        case MSCombo_TMDS_PORT_3:
            if(bFlag)
            {
                ucCableSARDetect = TMDS_CABLE_SAR_DETECT_PORT3;
            }
                else
            {
                bCable5VDetect = TMDS_CABLE_5V_DETECT_PORT3;
            }

            break;
    };

    if(bFlag)
    {
        if(ucCableSARDetect < 0x0A)
        {
            ucCableDetect = TMDS_CABLE_DETECT_HDMI;    // 10 * 3.3 / 255 = 0.13v
        }
        else if(ucCableSARDetect > 0xA0)
        {
            ucCableDetect = TMDS_CABLE_DETECT_MHL;
        }
    }
    else
    {
        if(bCable5VDetect)
        {
            ucCableDetect = TMDS_CABLE_DETECT_HDMI;
        }
}

    return ucCableDetect;
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_GetAudioFreq()
//  [Description]:
//                  calculate current HDMI audio frequence by CTS/N value;
//                  formula:
//                      freq = (F_tmds * N) / (128 * CTS);
//  [Arguments]:
//                  enInputPort
//  [Return]:
//                  MScombo_TMDS_AUDFREQ_INDEX
//
//**************************************************************************
MScombo_TMDS_AUD_FREQ_INDEX mhal_tmds_GetAudioFreq(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    WORD wOffset;
    DWORD dwCTSValue = 0, dwNValue = 0, dwTMDSClkValCnt;
    DWORD dwAudFreqValue = MScombo_TMDS_AUD_FREQ_ERROR;

    wOffset = _mhal_tmds_phy_offset(enInputPort);

    //Get current TMDS clock rate
    dwTMDSClkValCnt = mhal_tmds_GetClockRate(enInputPort) * 1000;

    if(enInputPort == MSCombo_TMDS_PORT_0)
    {
        //load current CTS/N value first
        msWrite2ByteMask(REG_160524, 0xFFFF, 0xFFFF);
        msWrite2ByteMask(REG_160526, 0xFFFF, 0xFFFF);
        MDrv_WriteByteMask(REG_160528, 0xFF, 0xFF);

        dwNValue = (MDrv_Read2Byte(REG_160526)) | (((MDrv_ReadByte(REG_160528) & 0xF0) >> 4) << 16);
        dwCTSValue = (MDrv_Read2Byte(REG_160524)) | ((MDrv_ReadByte(REG_160528) & 0x0F) << 16);
    }
    else if(enInputPort == MSCombo_TMDS_PORT_1)
    {
        //load current CTS/N value first
        msWrite2ByteMask(REG_160A24, 0xFFFF, 0xFFFF);
        msWrite2ByteMask(REG_160A26, 0xFFFF, 0xFFFF);
        MDrv_WriteByteMask(REG_160A28, 0xFF, 0xFF);

        dwNValue = (MDrv_Read2Byte(REG_160A26)) | (((MDrv_ReadByte(REG_160A28) & 0xF0) >> 4) << 16);
        dwCTSValue = (MDrv_Read2Byte(REG_160A24)) | ((MDrv_ReadByte(REG_160A28) & 0x0F) << 16);
    }
    else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
    {
        //load current CTS/N value first
        msWrite2ByteMask(REG_161124, 0xFFFF, 0xFFFF);
        msWrite2ByteMask(REG_161126, 0xFFFF, 0xFFFF);
        MDrv_WriteByteMask(REG_161128, 0xFF, 0xFF);

        dwNValue = (MDrv_Read2Byte(REG_161126)) | (((MDrv_ReadByte(REG_161128) & 0xF0) >> 4) << 16);

        if(mhal_tmds_InputIsHDMI2(enInputPort))
        {
            dwCTSValue = ((MDrv_Read2Byte(REG_161124)) | ((MDrv_ReadByte(REG_161128) & 0x0F) << 16)) / 2;
        }
        else
        {
            dwCTSValue = ((MDrv_Read2Byte(REG_161124)) | ((MDrv_ReadByte(REG_161128) & 0x0F) << 16)) * 2;
        }

    }

    if ((dwNValue < 0x10) || (dwCTSValue < 0x10))
        return MScombo_TMDS_AUD_FREQ_ERROR;   //error

    dwAudFreqValue = ((dwTMDSClkValCnt / 128) * dwNValue) / dwCTSValue;

    if (abs(dwAudFreqValue - 32) < 3)
        dwAudFreqValue = MScombo_TMDS_AUD_FREQ_32K;

    else if (abs(dwAudFreqValue - 44) < 3)
        dwAudFreqValue = MScombo_TMDS_AUD_FREQ_44K;

    else if (abs(dwAudFreqValue - 48) < 3)
        dwAudFreqValue = MScombo_TMDS_AUD_FREQ_48K;

    else if (abs(dwAudFreqValue - 88) < 4)
        dwAudFreqValue = MScombo_TMDS_AUD_FREQ_88K;

    else if (abs(dwAudFreqValue - 96) < 4)
        dwAudFreqValue = MScombo_TMDS_AUD_FREQ_96K;

    else if (abs(dwAudFreqValue - 176) < 5)
        dwAudFreqValue = MScombo_TMDS_AUD_FREQ_176K;

    else if (abs(dwAudFreqValue - 192) < 5)
        dwAudFreqValue = MScombo_TMDS_AUD_FREQ_192K;

    else
        dwAudFreqValue = MScombo_TMDS_AUD_FREQ_ERROR; //error

    #if 0
    {
        static WORD printcnt = 0;
        if ((printcnt % 10000 == 0) && (printcnt != 0))
        {
            printf("[HDMI] tmds clk = %d\n", dwTMDSClkValCnt);
            printf("[HDMI] N value = %d\n", dwNValue);
            printf("[HDMI] CTS value = %d\n", dwCTSValue);
            printf("[HDMI] audio freq = %d\n", dwAudFreqValue);
            printcnt -= 10000;
        }
        else
            printcnt++;
    }
    #endif

    return (MScombo_TMDS_AUD_FREQ_INDEX)dwAudFreqValue;

}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_IsAudioFmtPCM()
//  [Description]:
//                  check audio format information, is it PCM or non-PCM?
//  [Arguments]:
//                  enInputPort
//  [Return]:
//                  MSCombo_TMDS_AUDIO_FORMAT:
//                      MSCombo_AUDIO_FMT_NON_PCM   = 0,
//                      MSCombo_AUDIO_FMT_PCM       = 1,
//                      MSCombo_AUDIO_FMT_UNKNOWN   = 2,
//
//**************************************************************************
MSCombo_TMDS_AUDIO_FORMAT mhal_tmds_IsAudioFmtPCM(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    MSCombo_TMDS_AUDIO_FORMAT enAudFmt;

    if(enInputPort == MSCombo_TMDS_PORT_0)
    {
        if ( MDrv_ReadByte(REG_1605B4) & _BIT6 )
            enAudFmt = MSCombo_AUDIO_FMT_NON_PCM;
        else
            enAudFmt = MSCombo_AUDIO_FMT_PCM;
    }
    else if(enInputPort == MSCombo_TMDS_PORT_1)
    {
        if ( MDrv_ReadByte(REG_160AB4) & _BIT6 )
            enAudFmt = MSCombo_AUDIO_FMT_NON_PCM;
        else
            enAudFmt = MSCombo_AUDIO_FMT_PCM;
    }
    else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
    {
        if ( MDrv_ReadByte(REG_1611B4) & _BIT6 )
            enAudFmt = MSCombo_AUDIO_FMT_NON_PCM;
        else
            enAudFmt = MSCombo_AUDIO_FMT_PCM;
    }
    else
        enAudFmt = MSCombo_AUDIO_FMT_PCM;

    return enAudFmt;
}

//**************************************************************************
//  [Function Name]:
//                  _mhal_tmds_CheckClockValid()
//  [Description]:
//                  check "clock valid" status
//  [Arguments]:
//                  enInputPort
//  [Return]:
//                  Bool
//**************************************************************************
Bool mhal_tmds_CheckClockValid(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    WORD wOffset;

    wOffset = _mhal_tmds_phy_offset(enInputPort);

    if(MDrv_ReadByte(REG_112180 + wOffset) & 0x02) // clock stable
    {
       // printf("clock stable ohohohohohohohohohohoh\n");
        //MDrv_Write2Byte(REG_100FD6, 0xF000);
        return TRUE;
    }

    else
        return FALSE;
}

//**************************************************************************
//  [Function Name]:
//                  _mhal_tmds_CheckClockLock()
//  [Description]:
//                  check "Interskew align lose lock" status
//  [Arguments]:
//                  enInputPort
//  [Return]:
//                  Bool
//**************************************************************************
Bool mhal_tmds_CheckClockLock(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    WORD wOffset;

    wOffset = _mhal_tmds_phy_offset(enInputPort);

    if(MDrv_ReadByte(REG_112180 + wOffset) & 0x40) // clock big change
    {
       // MDrv_WriteByteMask(REG_112183 + wOffset, 0x40, 0x40); //clr
        MDrv_WriteByte(REG_112183 + wOffset, 0x40); //clr

      //  MDrv_WriteByteMask(REG_112183 + wOffset, 0x00, 0x40);
        MDrv_WriteByte(REG_112183 + wOffset, 0x00);

       // MDrv_WriteByteMask(REG_112183 + wOffset, 0x00, 0x40);
        MDrv_WriteByte(REG_112183 + wOffset, 0x00);
        return TRUE;
    }
    else
        return FALSE;

}

//**************************************************************************
//  [Function Name]:
//                  _mhal_tmds_ClearClockStatus()
//  [Description]:
//                  clear "Interskew align lose lock" and "clock valid" status
//  [Arguments]:
//                  enInputPort
//  [Return]:
//                  void
//**************************************************************************
void mhal_tmds_ClearClockStatus(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    //clear clock valid and clock big change status
    WORD wOffset;

    wOffset = _mhal_tmds_phy_offset(enInputPort);

   // MDrv_WriteByteMask(REG_112183 + wOffset, 0x02, 0x02); //clear clock valid
    MDrv_WriteByte(REG_112183 + wOffset, 0x02); //clear clock valid

   // MDrv_WriteByteMask(REG_112183 + wOffset, 0x00, 0x02);
    MDrv_WriteByte(REG_112183 + wOffset, 0x00);

   // MDrv_WriteByteMask(REG_112183 + wOffset, 0x00, 0x02);
    MDrv_WriteByte(REG_112183 + wOffset, 0x00);

    TMDS_PRINT("clear clock status\r\n");
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_GetColorDepthInfo()
//  [Description]:
//                  return color depth information, ex: 8bit, 10bit, or 12 bit by parsing GCP packet content
//  [Arguments]:
//                  enInputPort
//  [Return]:
//                  MSCombo_TMDS_COLOR_DEPTH_FORMAT
//              8_BIT  = 0,
//              10_BIT = 1,
//              12_BIT = 2,
//              16_BIT = 3,
//              UNKNOWN = 4,
//**************************************************************************
MSCombo_TMDS_COLOR_DEPTH_FORMAT mhal_tmds_GetColorDepthInfo(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    BYTE ucTmpValue = 0;

    //GCP packeting phase bit
    if(enInputPort == MSCombo_TMDS_PORT_0)
        ucTmpValue = (MDrv_ReadByte(REG_16052B) & 0x0F);

    else if(enInputPort == MSCombo_TMDS_PORT_1)
        ucTmpValue = (MDrv_ReadByte(REG_160A2B) & 0x0F);

    else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
        ucTmpValue = (MDrv_ReadByte(REG_16112B) & 0x0F);

    switch (ucTmpValue)
    {
        case 0:
        case 4:
            return MSCombo_TMDS_COLOR_DEPTH_8_BIT;
        break;
        case 5:
            return MSCombo_TMDS_COLOR_DEPTH_10_BIT;
        break;
        case 6:
            return MSCombo_TMDS_COLOR_DEPTH_12_BIT;
        break;
        case 7:
            return MSCombo_TMDS_COLOR_DEPTH_16_BIT;
        break;
        default:
            return MSCombo_TMDS_COLOR_DEPTH_UNKNOWN;
        break;
    }

}


//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_GetPixelRepetitionInfo()
//  [Description]:
//                  return pxiel repetition info
//  [Arguments]:
//                  enInputPort
//  [Return]:
//                  MSCombo_TMDS_PIXEL_REPETITION
//              no = 0,
//              2x = 1,
//              3x = 2,
//              4x = 3,
//              5x = 4,
//              6x = 5,
//              7x = 6,
//              8x = 7,
//              9x = 8,
//             10x = 9,
//**************************************************************************
MSCombo_TMDS_PIXEL_REPETITION mhal_tmds_GetPixelRepetitionInfo(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    BYTE ucTmpValue = 0;

    // [3:0]: Pixel repetition
    if(enInputPort == MSCombo_TMDS_PORT_0)
        ucTmpValue = (MDrv_ReadByte(REG_160584) & 0x0F);

    else if(enInputPort == MSCombo_TMDS_PORT_1)
        ucTmpValue = (MDrv_ReadByte(REG_160A84) & 0x0F);

    else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
        ucTmpValue = (MDrv_ReadByte(REG_161184) & 0x0F);

    switch (ucTmpValue)
    {
        case 0:
            return MSCombo_TMDS_N0_PIX_REP;
        break;
        case 1:
            return MSCombo_TMDS_2x_PIX_REP;
        break;
        case 2:
            return MSCombo_TMDS_3x_PIX_REP;
        break;
        case 3:
            return MSCombo_TMDS_4x_PIX_REP;
        break;
        case 4:
            return MSCombo_TMDS_5x_PIX_REP;
        break;
        case 5:
            return MSCombo_TMDS_6x_PIX_REP;
        break;
        case 6:
            return MSCombo_TMDS_7x_PIX_REP;
        break;
        case 7:
            return MSCombo_TMDS_8x_PIX_REP;
        break;
        case 8:
            return MSCombo_TMDS_9x_PIX_REP;
        break;
        case 9:
            return MSCombo_TMDS_10x_PIX_REP;
        break;
        default:
            return MSCombo_TMDS_RESERVED_PIX_REP;
        break;
    }

}


//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_GetClockRate()
//  [Description]:
//                  return clcok rate
//  [Arguments]:
//                  enInputPort
//  [Return]:
//
//**************************************************************************
WORD mhal_tmds_GetClockRate(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    WORD wOffset, dwTMDSClkValCnt;

    if(mhal_tmds_Clock_Stable(enInputPort))
    {
        wOffset = _mhal_tmds_phy_offset(enInputPort);

        //Get current TMDS clock rate
        dwTMDSClkValCnt = MDrv_Read2Byte(REG_112078 + wOffset)* 12 / 128;

        //MHL PP mode: we have to double TMDS clock value;
        if(enInputPort == MSCombo_TMDS_PORT_0)
        {
            if (MDrv_ReadByte(REG_16024E + wOffset) & BIT1) //[1]: MHL PP mode enable
                dwTMDSClkValCnt = dwTMDSClkValCnt << 1;
        }
        else if(enInputPort == MSCombo_TMDS_PORT_1)
        {
            if (MDrv_ReadByte(REG_16074E + wOffset) & BIT1) //[1]: MHL PP mode enable
                dwTMDSClkValCnt = dwTMDSClkValCnt << 1;
        }
        else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
        {
             if (MDrv_ReadByte(REG_160C4E + wOffset) & BIT1) //[1]: MHL PP mode enable
                dwTMDSClkValCnt = dwTMDSClkValCnt << 1;
        }
        return dwTMDSClkValCnt;
    }
    else
        return 0;
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_GetIsOver3G()
//  [Description]:
//                  over/under 3.4G determined in mhal_tmds_ISR()
//  [Arguments]:
//                  [MSCombo_TMDS_PORT_INDEX]PortIdx
//  [Return]:
//                  TRUE: Over 3.4G
//                  FALSE: Under 3.4G
//**************************************************************************
Bool mhal_tmds_GetIsOver3G(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    return bOver3GFlag[enInputPort];
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_SetIsOver3G()
//  [Description]:
//                  over/under 3.4G determined in mhal_tmds_ISR()
//  [Arguments]:
//                  [MSCombo_TMDS_PORT_INDEX]PortIdx
//  [Return]:
//                  TRUE: Over 3.4G
//                  FALSE: Under 3.4G
//**************************************************************************
void mhal_tmds_SetIsOver3G(MSCombo_TMDS_PORT_INDEX enInputPort, Bool Flag)
{
    bOver3GFlag[enInputPort] = Flag;
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_GetIsSplitterDone()
//  [Description]:
//                  Splitter setting done or not
//  [Arguments]:
//                  [MSCombo_TMDS_PORT_INDEX]PortIdx
//  [Return]:
//                  TRUE: Splitter Setting Done
//                  FALSE: Splitter not setting done
//**************************************************************************
Bool mhal_tmds_GetIsSplitterDone(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    return bSplitterDone[enInputPort];
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_SetIsSplitterDone()
//  [Description]:
//                  Splitter setting done or not
//  [Arguments]:
//                  [MSCombo_TMDS_PORT_INDEX]PortIdx
//  [Return]:
//                  TRUE: Splitter Setting Done
//                  FALSE: Splitter not setting done
//**************************************************************************
void mhal_tmds_SetIsSplitterDone(MSCombo_TMDS_PORT_INDEX enInputPort, Bool Flag)
{
    bSplitterDone[enInputPort] = Flag;
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_GetAutoEQCntRst()
//  [Description]:
//                  AutoEQ count reset or not
//  [Arguments]:
//                  [MSCombo_TMDS_PORT_INDEX]PortIdx
//  [Return]:
//                  TRUE: do autoEQ count reset
//                  FALSE: not do autoEQ count reset
//**************************************************************************
Bool mhal_tmds_GetAutoEQCntRst(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    return bAutoEQCntRst[enInputPort];
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_SetAutoEQCntRst()
//  [Description]:
//                  AutoEQ count reset or not
//  [Arguments]:
//                  [MSCombo_TMDS_PORT_INDEX]PortIdx
//  [Return]:
//                  TRUE: do autoEQ count reset
//                  FALSE: not do autoEQ count reset
//**************************************************************************
void mhal_tmds_SetAutoEQCntRst(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bFlag)
{
    bAutoEQCntRst[enInputPort] = bFlag;
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_AutoEQDone()
//  [Description]:
//                  AutoEQ done or not
//  [Arguments]:
//                  [MSCombo_TMDS_PORT_INDEX]PortIdx
//  [Return]:
//                  TRUE: autoEQ done
//                  FALSE: autoEQ not done
//**************************************************************************
Bool mhal_tmds_AutoEQDone(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    return bAutoEQDone[enInputPort];
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_TriggerAutoEQ()
//  [Description]:
//                  Do autoEQ or not
//  [Arguments]:
//                  [MSCombo_TMDS_PORT_INDEX]PortIdx
//                  bEnable: TRUE: do autoEQ, FALSE: not do autoEQ
//  [Return]:
//
//**************************************************************************
void mhal_tmds_TriggerAutoEQ(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bEnable)
{
    WORD wCount = 500;
    if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
    {
        if(bEnable)
        {
            MDrv_WriteByteMask(REG_1124DC, 0x00, 0xF0); // eq overwrite disable
            MDrv_WriteByteMask(REG_11244A, 0x04, 0x04); // enable autoEQ
            MDrv_WriteByteMask(REG_112466, 0x04, 0x04); // sw trigger autoEQ
            while(wCount > 0)
            {
                wCount--;
                //_nop_();
            }
            MDrv_WriteByteMask(REG_112466, 0x00, 0x04); // sw trigger autoEQ
        }
        else
        {
            MDrv_WriteByteMask(REG_1124DC, 0xF0, 0xF0); // eq overwrite enable
            MDrv_WriteByteMask(REG_11244A, 0x00, 0x04); // disable autoEQ
        }
    }
    else
    {
        TMDS_PRINT("Port: 0x%x, no need\r\n", enInputPort);
    }
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_CheckAutoEQ()
//  [Description]:
//                  check AutoEQ flow
//  [Arguments]:
//                  [MSCombo_TMDS_PORT_INDEX]PortIdx
//                  bFlag: true -> no timeout, false -> timeout
//  [Return]:
//**************************************************************************
void mhal_tmds_CheckAutoEQ(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bFlag)
{
    BYTE i;
    BYTE ucDEStableCnt = 5;

    if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
    {
        if(bAutoEQRetry[enInputPort] < 5)
        {
            if(bFlag)
            {
                if(_mhal_tmds_AutoEQDoneInterrupt(enInputPort))
                {
                   // printf("_mhal_tmds_AutoEQDoneInterrupt\n");
                    for(i = 0; i < ucDEStableCnt; i++)
                    {
                        if(!mhal_tmds_DE_Stable(enInputPort))
                        {
                            mhal_tmds_TriggerAutoEQ(enInputPort,TRUE);
                            bAutoEQCntRst[enInputPort] = TRUE;
                            bAutoEQRetry[enInputPort]++;
                           // printf("port = %d, bAutoEQRetry = %d, i = %d\n", enInputPort, bAutoEQRetry[enInputPort], i);
                            break;
                        }
                    }
                    if(i == 5)
                    {
                        bAutoEQDone[enInputPort] = TRUE;
                       // printf("autoEQ done!!!\n");
                    }

                }
                else
                {
                    mhal_tmds_TriggerAutoEQ(enInputPort,TRUE);
                    bAutoEQCntRst[enInputPort] = TRUE;
                    bAutoEQRetry[enInputPort] = 0;
                   // printf("timeout!!!\n");
                }
            }
        }
        else
        {
            bAutoEQDone[enInputPort] = TRUE;
           // printf("retry finish!!!\n");
        }
    }
    else
    {
        TMDS_PRINT("Port: 0x%x, no need\r\n", enInputPort);
    }
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_ISR()
//  [Description]:
//                  interrupt handler for tmds CLK_STABLE
//  [Arguments]:
//                  [MSCombo_TMDS_PORT_INDEX]PortIdx
//  [Return]:
//                  void
// (Odin)combo_rx_top(1606)_2b -> (Leona)combo_phy1(1121)_40
//**************************************************************************
void mhal_tmds_ISR(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bMHLSupport)
{
    WORD wOffset = 0;
    WORD wTMDSClkRate = 0;
    Bool bOver3G = FALSE;

    wOffset = _mhal_tmds_phy_offset(enInputPort);

    if((enInputPort == MSCombo_TMDS_PORT_0) || (enInputPort == MSCombo_TMDS_PORT_1))
    {
        // turn on mask
        //MDrv_WriteByte(REG_112181 + wOffset, 0xFF); // combo irq mask

        if (MDrv_ReadByte(REG_112180 + wOffset) & 0x02) // [1]: clock stable
        {
            msWrite2ByteMask(REG_112064 + wOffset, 0x4444, 0x4444); // clear combo_phy0 clock big change

            MDrv_WriteByte(REG_112183 + wOffset, 0x02); // clear clock stable
            MDrv_WriteByte(REG_112183 + wOffset, 0x00);
            MDrv_WriteByte(REG_112183 + wOffset, 0x00);

            wTMDSClkRate = (MDrv_Read2Byte(REG_112078 + wOffset)* 12 / 128);

            if ((wPreviousTiming == wTMDSClkRate) && (bPreviousPort == enInputPort))
            {
                //MDrv_Write2Byte(REG_112181 + wOffset, 0xFD); //combo irq mask
                return; //no timing change or DC on/off
            }
            wPreviousTiming = wTMDSClkRate;
            bPreviousPort = enInputPort;

            if((!bMHLSupport) || (mhal_tmds_DetectCablePlug(enInputPort, bMHLSupport) <= 1)) //HDMI cable
            {
                if(bMHLCable[enInputPort] == TRUE)
                {
                    bMHLCable[enInputPort] = FALSE;
                    MDrv_WriteByteMask(REG_11203B + wOffset, BIT0, BIT0); // REG_COMBO_PHY0_1D[8]:Auto clear phase
                    MDrv_WriteByteMask(REG_11203B + wOffset, 0, BIT0); // REG_COMBO_PHY0_1D[8]:Auto clear phase
                }
            }
            else
            {
                bMHLCable[enInputPort] = TRUE;
            }
        }

        // turn off mask
        //MDrv_Write2Byte(REG_112181 + wOffset, 0xFD); //combo irq mask
    }

    else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
    {
        if (enInputPort == bCurrentPort)
        {
            // turn on mask
            //MDrv_WriteByte(REG_112181 + wOffset, 0xFF); // combo irq mask

            if (MDrv_ReadByte(REG_112180 + wOffset) & 0x02) // [1]: clock stable
            {
                bSplitterDone[enInputPort] = FALSE;
                msWrite2ByteMask(REG_112064 + wOffset, 0x4444, 0x4444); // clear combo_phy0 clock big change

                MDrv_WriteByte(REG_112183 + wOffset, 0x02); // clear clock stable
                MDrv_WriteByte(REG_112183 + wOffset, 0x00);
                MDrv_WriteByte(REG_112183 + wOffset, 0x00);

                MDrv_WriteByte(REG_161104, 0x20); // clear DE pixel change

                wTMDSClkRate = (MDrv_Read2Byte(REG_112078 + wOffset)* 12 / 128);
                bOver3G = ((MDrv_ReadByte(REG_112560) &BIT3)? TRUE: FALSE);

                if ((wPreviousTiming == wTMDSClkRate) && (bPreviousPort == enInputPort)
                 && (bOver3GFlag[enInputPort] == bOver3G))
                {
                    //MDrv_Write2Byte(REG_112181 + wOffset, 0xFD); //combo irq mask
                    return; //no timing change or DC on/off
                }

                wPreviousTiming = wTMDSClkRate;
                bPreviousPort = enInputPort;

                if((!bMHLSupport) || (mhal_tmds_DetectCablePlug(enInputPort, bMHLSupport) <= 1)) //HDMI cable
                {
                    if (wTMDSClkRate >= 250)
                    {
                        //printMsg("eq= 12");
                        MDrv_WriteByteMask(REG_1124DC, 0xF0, 0xF0); // eq overwrite enable
                        msWrite2ByteMask(REG_1124E6, (COMBO_HDMI_250_340MHZ_EQ_VALUE<<8)|COMBO_HDMI_250_340MHZ_EQ_VALUE, 0x1F1F);
                        msWrite2ByteMask(REG_1124E8, (COMBO_HDMI_250_340MHZ_EQ_VALUE<<8)|COMBO_HDMI_250_340MHZ_EQ_VALUE, 0x1F1F);

                        //enable DIVSEL_IN DIVSEL_POST overwrite
                        MDrv_WriteByteMask(REG_1124DA, 0x0F, 0x0F);
                        MDrv_WriteByteMask(REG_1124DB, 0xF0, 0xF0);
                        MDrv_WriteByteMask(REG_1124E0, 0x00, 0xFF);
                        MDrv_WriteByteMask(REG_1124E3, 0x10, 0xF0);
                        MDrv_WriteByteMask(REG_1124E4, 0x49, 0xFF);

                        //phase step
                        MDrv_WriteByteMask(REG_112420, 0x00, 0x08);

                        // patch for HDMI1.4 jitter issue on 3G
                        MDrv_WriteByteMask(REG_1124DF, 0x08, 0x08); // ictrl pfd overwrite enable
                        MDrv_WriteByteMask(REG_1124D7, 0x08, 0x0F); // ictrl pfd value

                        // patch for QFP 3G
                        MDrv_WriteByteMask(REG_1124C0, 0x70, 0x70);
                        MDrv_WriteByteMask(REG_1124C1, 0x0F, 0x0F);
                        MDrv_WriteByteMask(REG_1124C2, 0x70, 0x70);
                        MDrv_WriteByteMask(REG_1124C3, 0x0F, 0x0F);
                        MDrv_WriteByteMask(REG_1124C4, 0x70, 0x70);
                        MDrv_WriteByteMask(REG_1124C5, 0x0F, 0x0F);
                        MDrv_WriteByteMask(REG_112506, 0x02, 0x02);
                        MDrv_WriteByteMask(REG_112509, 0x00, 0xFF);
                    }
                    else
                    {
                        //printMsg("eq= 24");
                        MDrv_WriteByteMask(REG_1124DC, 0xF0, 0xF0); // eq overwrite enable
                        msWrite2ByteMask(REG_1124E6, (COMBO_HDMI_25_250MHZ_EQ_VALUE<<8)|COMBO_HDMI_25_250MHZ_EQ_VALUE, 0x1F1F);
                        msWrite2ByteMask(REG_1124E8, (COMBO_HDMI_25_250MHZ_EQ_VALUE<<8)|COMBO_HDMI_25_250MHZ_EQ_VALUE, 0x1F1F);

                        //enable DIVSEL_IN DIVSEL_POST overwrite
                        MDrv_WriteByteMask(REG_1124DA, 0x00, 0x0F);
                        MDrv_WriteByteMask(REG_1124DB, 0x00, 0xF0);

                        //phase step
                        MDrv_WriteByteMask(REG_112420, 0x08, 0x08);

                        // patch for HDMI1.4 jitter issue on 3G
                        MDrv_WriteByteMask(REG_1124DF, 0x08, 0x08); // ictrl pfd overwrite enable
                        MDrv_WriteByteMask(REG_1124D7, 0x04, 0x0F); // ictrl pfd value
                        MDrv_WriteByteMask(REG_1124DF, 0x00, 0x08); // ictrl pfd overwrite enable

                        MDrv_WriteByteMask(REG_1124C0, 0x60, 0x70);
                        MDrv_WriteByteMask(REG_1124C1, 0x00, 0x0F);
                        MDrv_WriteByteMask(REG_1124C2, 0x60, 0x70);
                        MDrv_WriteByteMask(REG_1124C3, 0x00, 0x0F);
                        MDrv_WriteByteMask(REG_1124C4, 0x60, 0x70);
                        MDrv_WriteByteMask(REG_1124C5, 0x00, 0x0F);
                        MDrv_WriteByteMask(REG_112506, 0x00, 0x02);
                        MDrv_WriteByteMask(REG_112509, 0x00, 0xFF);
                    }

                    bOver3GFlag[enInputPort] = ((MDrv_ReadByte(REG_112560) &BIT3)? TRUE: FALSE);

                    mhal_tmds_HDMI20Setting(enInputPort, bOver3GFlag[enInputPort]);
                }
            }

            // turn off mask
            //MDrv_Write2Byte(REG_112181 + wOffset, 0xFD); //combo irq mask
        }
    }
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_GetNoInputFlag()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
Bool mhal_tmds_GetNoInputFlag(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    Bool bNoInputFlag = FALSE;

    switch(enInputPort)
    {
        case MSCombo_TMDS_PORT_0:
            bNoInputFlag = ((MDrv_ReadByte(REG_112180) &BIT3)? TRUE: FALSE); // REG_COMBO_PHY1_40[3], No input status port0

            if(bNoInputFlag)
            {
                MDrv_WriteByteMask(REG_112183, BIT3, BIT3); // REG_COMBO_PHY1_41[13], No input clear port0
                MDrv_WriteByteMask(REG_112183, 0, BIT3); // REG_COMBO_PHY1_41[13], No input clear port0
            }

            break;

        case MSCombo_TMDS_PORT_1:
            bNoInputFlag = ((MDrv_ReadByte(REG_112380) &BIT3)? TRUE: FALSE); // REG_COMBO_PHY3_40[3], No input status port1

            if(bNoInputFlag)
            {
                MDrv_WriteByteMask(REG_112383, BIT3, BIT3); // REG_COMBO_PHY3_41[11], No input clear port1
                MDrv_WriteByteMask(REG_112383, 0, BIT3); // REG_COMBO_PHY3_41[11], No input clear port1
            }

            break;

        case MSCombo_TMDS_PORT_2:
        case MSCombo_TMDS_PORT_3:
            if(enInputPort == bCurrentPort)
            {
                bNoInputFlag = ((MDrv_ReadByte(REG_112580) &BIT3)? TRUE: FALSE); // REG_COMBO_PHY5_40[3], No input status port2&3

                if(bNoInputFlag)
                {
                    MDrv_WriteByteMask(REG_112583, BIT3, BIT3); // REG_COMBO_PHY5_41[11], No input clear port2&3
                    MDrv_WriteByteMask(REG_112583, 0, BIT3); // REG_COMBO_PHY5_41[11], No input clear port2&3
                }
            }

            break;

        default:

            break;
    };

    return bNoInputFlag;
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_Over3G_420Setting()
//  [Description]:
//                  4k2k@60Hz 420 deep color setting
//  [Arguments]:
//                  [MSCombo_TMDS_PORT_INDEX]PortIdx
//  [Return]:
//
//**************************************************************************
void mhal_tmds_Over3G_420Setting(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
    {
        if (enInputPort == bCurrentPort)
        {
           // printf("C. mhal_tmds_Over3G_420Setting =============== 1p\n");
            MDrv_WriteByteMask(REG_1124D6, 0x06, 0x06); // [2]: enable clko_pix 2x; [1]: reg_atop_en_clko_pix=1
            MDrv_WriteByteMask(REG_100E60, 0x04, 0x0D); // [2]: reg_pix_clk_div2_en_p2; [0]: reg_tmds_clk_div2_en_p2
            MDrv_WriteByteMask(REG_1612A8, 0x02, 0x03); // [1:0]: reg_avg_ctrl_case
        }
    }
    else
    {
        TMDS_PRINT("Port: 0x%x, no need\r\n", enInputPort);
    }
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_HDE_value()
//  [Description]:
//                  Get HDE value
//  [Arguments]:
//                  [MSCombo_TMDS_PORT_INDEX]PortIdx
//  [Return]:
//                  HDE_value
//**************************************************************************
WORD mhal_tmds_HDE_value(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    WORD HDE_value = 0;
    if(enInputPort == MSCombo_TMDS_PORT_0)
    {
        HDE_value = MDrv_Read2Byte(REG_1605CA) & 0x3FFF;
    }
    else if(enInputPort == MSCombo_TMDS_PORT_1)
    {
        HDE_value = MDrv_Read2Byte(REG_160ACA) & 0x3FFF;
    }
    else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
    {
        HDE_value = MDrv_Read2Byte(REG_1611CA) & 0x3FFF;
    }
    else
    {
        TMDS_PRINT("Port: 0x%x, no need\r\n", enInputPort);
    }
    return HDE_value;
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_HDMI20Setting()
//  [Description]:
//                  2p/1p setting
//  [Arguments]:
//                  [MSCombo_TMDS_PORT_INDEX]PortIdx
//                  bFlag : TRUE -> 2p, FALSE -> 1p
//  [Return]:
//
//**************************************************************************
void mhal_tmds_HDMI20Setting(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bFlag)
{
    if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
    {
        if (enInputPort == bCurrentPort)
        {
            if(bFlag) // over 3.4G
            {
               // printf("if(MDrv_ReadByte(REG_112560 ) & 0x08) =============== over 3.4G\n");
                MDrv_WriteByteMask(REG_160C63, 0x05, 0x0F); // [15:8]: De filter length

                MDrv_WriteByteMask(REG_1124D6, 0x02, 0x06); // [2]: enable clko_pix 2x; [1]: reg_atop_en_clko_pix=1
                MDrv_WriteByteMask(REG_112414, 0x40, 0x40); // [6]: reg_af_ls_20out_sel=1
                MDrv_WriteByteMask(REG_1124B4, 0x00, 0x04); // [2]: disable reg_atop_en_clko_tmds2x
                msWrite2ByteMask(REG_100E62, 0, 0xFFFF); // enable P2 all clock power
                MDrv_WriteByteMask(REG_100E60, 0x00, 0x0D); // [0]: reg_tmds_clk_div2_en_p2
                MDrv_WriteByteMask(REG_1612A8, 0x00, 0x03); // [1:0]: reg_avg_ctrl_case

                mhal_tmds_TriggerAutoEQ(enInputPort, TRUE);
                bAutoEQRetry[enInputPort] = 0;
                bAutoEQCntRst[enInputPort] = TRUE;
                bAutoEQDone[enInputPort] = FALSE;
            }
            else
            {
               // printf("else(MDrv_ReadByte(REG_112560 ) & 0x08) =============== under 3.4G\n");
                MDrv_WriteByteMask(REG_160C63, 0x0C, 0x0F); // [15:8]: De filter length

                MDrv_WriteByteMask(REG_1124D6, 0x06, 0x06); // [2]: enable clko_pix 2x; [1]: reg_atop_en_clko_pix=1
                MDrv_WriteByteMask(REG_112414, 0x40, 0x40); // [6]: reg_af_ls_20out_sel=1
                MDrv_WriteByteMask(REG_1124B4, 0x04, 0x04); // [2]: disable reg_atop_en_clko_tmds2x
                msWrite2ByteMask(REG_100E62, 0, 0xFFFF); // enable P2 all clock power
                MDrv_WriteByteMask(REG_100E60, 0x05, 0x0D); // [2]: reg_pix_clk_div2_en_p2; [0]: reg_tmds_clk_div2_en_p2
                MDrv_WriteByteMask(REG_1612A8, 0x02, 0x03); // [1:0]: reg_avg_ctrl_case

                mhal_tmds_TriggerAutoEQ(enInputPort, FALSE);
            }

            _mhal_tmds_SetEfuseSettingValue(enInputPort, bFlag);
        }
    }
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_SetMonochromeMode()
//  [Description]:
//                  used for DVI mono mode setting
//  [Arguments]:
//                  enInputPort
//                  bEnable : True -> enable mono mode, False -> disable mono mode and change to dual link setting for next timing detect
//                  bFlag : True ->  dual link mode. False -> single mode.
//                  ucBits : mono bit
//  [Return]:
//                  None
//**************************************************************************
void mhal_tmds_SetMonochromeMode(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bEnable, Bool bFlag, MSCombo_TMDS_MONO_BIT ucBits)
{
    if(bEnable)
    {
        if(enInputPort == MSCombo_TMDS_PORT_0)
        {
            MDrv_WriteByteMask(REG_1606C0, bFlag ? 0x01 : 0x00, 0x31); //[0]: enable of dual link FIFO, [5:4]: deep color define
            switch(ucBits)
            {
                case MSCombo_TMDS_MONO_8_BIT:
                    MDrv_WriteByteMask(REG_1606C1, 0x00, 0x0F); //mono type select
                break;
                case MSCombo_TMDS_MONO_10_BIT:
                    MDrv_WriteByteMask(REG_1606C1, 0x04, 0x0F); //mono type select
                break;
                case MSCombo_TMDS_MONO_12_BIT:
                    MDrv_WriteByteMask(REG_1606C1, 0x08, 0x0F); //mono type select
                break;
                default:
                    MDrv_WriteByteMask(REG_1606C1, 0x0C, 0x0F); //default value
                break;
            }
        }
        else if(enInputPort == MSCombo_TMDS_PORT_1)
        {
            MDrv_WriteByteMask(REG_160BC0, bFlag ? 0x01 : 0x00, 0x31); //[0]: enable of dual link FIFO, [5:4]: deep color define
            switch(ucBits)
            {
                case MSCombo_TMDS_MONO_8_BIT:
                    MDrv_WriteByteMask(REG_160BC1, 0x00, 0x0F); //mono type select
                break;
                case MSCombo_TMDS_MONO_10_BIT:
                    MDrv_WriteByteMask(REG_160BC1, 0x04, 0x0F); //mono type select
                break;
                case MSCombo_TMDS_MONO_12_BIT:
                    MDrv_WriteByteMask(REG_160BC1, 0x08, 0x0F); //mono type select
                break;
                default:
                    MDrv_WriteByteMask(REG_160BC1, 0x0C, 0x0F); //default value
                break;
            }
        }
        else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
        {
            MDrv_WriteByteMask(REG_1612C0, bFlag ? 0x01 : 0x00, 0x31); //[0]: enable of dual link FIFO, [5:4]: deep color define
            switch(ucBits)
            {
                case MSCombo_TMDS_MONO_8_BIT:
                    MDrv_WriteByteMask(REG_1612C1, 0x00, 0x0F); //mono type select
                break;
                case MSCombo_TMDS_MONO_10_BIT:
                    MDrv_WriteByteMask(REG_1612C1, 0x04, 0x0F); //mono type select
                break;
                case MSCombo_TMDS_MONO_12_BIT:
                    MDrv_WriteByteMask(REG_1612C1, 0x08, 0x0F); //mono type select
                break;
                default:
                    MDrv_WriteByteMask(REG_1612C1, 0x0C, 0x0F); //default value
                break;
            }
        }
    }
    else
    {
        if(enInputPort == MSCombo_TMDS_PORT_0)
        {
            MDrv_WriteByteMask(REG_1606C0, 0x01, 0x31); //[0]: enable of dual link FIFO, [5:4]: deep color define
            MDrv_WriteByteMask(REG_1606C1, 0x0C, 0x0F); //default value
        }
        else if(enInputPort == MSCombo_TMDS_PORT_1)
        {
            MDrv_WriteByteMask(REG_160BC0, 0x01, 0x31); //[0]: enable of dual link FIFO, [5:4]: deep color define
            MDrv_WriteByteMask(REG_160BC1, 0x0C, 0x0F); //default value
        }
        else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
        {
            MDrv_WriteByteMask(REG_1612C0, 0x01, 0x31); //[0]: enable of dual link FIFO, [5:4]: deep color define
            MDrv_WriteByteMask(REG_1612C1, 0x0C, 0x0F); //default value
        }
    }
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_DVIDeepColorSetting()
//  [Description]:
//                  used for DVI deep color mode setting
//  [Arguments]:
//                  enInputPort
//                  bEnable : True : enable deep color mode, False : disable deep color mode and change to dual link setting for next timing detect
//                  ucBits : color depth
//  [Return]:
//                  None
//**************************************************************************
void mhal_tmds_DVIDeepColorSetting(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bEnable, MSCombo_TMDS_DVI_DEEP_COLOR ucBits)
{
    WORD wOffset;

    if(bEnable)
    {
        if(enInputPort == MSCombo_TMDS_PORT_0)
        {
            switch(ucBits)
            {
                case MSCombo_TMDS_DVI_DEEP_COLOR_8_BIT:
                    MDrv_WriteByteMask(REG_1606C0, 0x00, 0x31);
                break;
                case MSCombo_TMDS_DVI_DEEP_COLOR_10_BIT:
                    MDrv_WriteByteMask(REG_1606C0, 0x11, 0x31);
                break;
                case MSCombo_TMDS_DVI_DEEP_COLOR_12_BIT:
                    MDrv_WriteByteMask(REG_1606C0, 0x21, 0x31);
                break;
                default:
                    MDrv_WriteByteMask(REG_1606C0, 0x01, 0x31);
                break;
            }
        }
        else if(enInputPort == MSCombo_TMDS_PORT_1)
        {
            switch(ucBits)
            {
                case MSCombo_TMDS_DVI_DEEP_COLOR_8_BIT:
                    MDrv_WriteByteMask(REG_160BC0, 0x00, 0x31);
                break;
                case MSCombo_TMDS_DVI_DEEP_COLOR_10_BIT:
                    MDrv_WriteByteMask(REG_160BC0, 0x11, 0x31);
                break;
                case MSCombo_TMDS_DVI_DEEP_COLOR_12_BIT:
                    MDrv_WriteByteMask(REG_160BC0, 0x21, 0x31);
                break;
                default:
                    MDrv_WriteByteMask(REG_160BC0, 0x01, 0x31);
                break;
            }
        }
        else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
        {
            switch(ucBits)
            {
                case MSCombo_TMDS_DVI_DEEP_COLOR_8_BIT:
                    MDrv_WriteByteMask(REG_1612C0, 0x00, 0x31);
                break;
                case MSCombo_TMDS_DVI_DEEP_COLOR_10_BIT:
                    MDrv_WriteByteMask(REG_1612C0, 0x11, 0x31);
                break;
                case MSCombo_TMDS_DVI_DEEP_COLOR_12_BIT:
                    MDrv_WriteByteMask(REG_1612C0, 0x21, 0x31);
                break;
                default:
                    MDrv_WriteByteMask(REG_1612C0, 0x01, 0x31);
                break;
            }
        }

        wOffset = _mhal_tmds_phy_offset(enInputPort);
        if(ucBits>MSCombo_TMDS_DVI_DEEP_COLOR_8_BIT)
            MDrv_WriteByteMask(REG_1120D6 + wOffset, 0x01, 0x05); //Main:[0]: Enable dual clk; [2]: 2x Pixel clk
        else
            MDrv_WriteByteMask(REG_1120D6 + wOffset, 0x05, 0x05); //Main:[0]: Enable dual clk; [2]: 2x Pixel clk
    }
    else
    {
        if(enInputPort == MSCombo_TMDS_PORT_0)
            MDrv_WriteByteMask(REG_1606C0, 0x01, 0x31);

        else if(enInputPort == MSCombo_TMDS_PORT_1)
             MDrv_WriteByteMask(REG_160BC0, 0x01, 0x31);

        else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
            MDrv_WriteByteMask(REG_1612C0, 0x01, 0x31);

        wOffset = _mhal_tmds_phy_offset(enInputPort);
        MDrv_WriteByteMask(REG_1120D6 + wOffset, 0x05, 0x05);
    }
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_InputIsHDMI2()
//  [Description]:
//                  return input signal is HDMI 2.0 or not
//  [Arguments]:
//                  enInputPort
//  [Return]:
//                  True: 2.0, False: 1.4
//**************************************************************************
BOOL mhal_tmds_InputIsHDMI2(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
    {
        if(MDrv_ReadByte(REG_112560) & BIT3)
            return TRUE;
        else
            return FALSE;
    }
    else
        return FALSE;
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_SetSplitter()
//  [Description]:
//                  Splitter setting
//  [Arguments]:
//                  enInputPort
//  [Return]:
//
//**************************************************************************
void mhal_tmds_SetSplitter(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bFlag)
{
    WORD wRealWidth = 0;
    if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
    {
        // Scaler
        if(bFlag == TRUE)
        {
            wRealWidth = MDrv_Read2Byte(REG_1611CA) & 0x3FFF;
            msWrite2ByteMask(REG_162DEA, 0x2320, 0xFFF0); // Combo2sc IPMUX  (SPT_0, SPT_1, SPT_2)
            msWrite2ByteMask(REG_162DEC, 0x0003, 0x000F); // Combo2sc IPMUX  (SPT_3)
        }
        else
        {
            wRealWidth = (MDrv_Read2Byte(REG_1611CA)  & 0x3FFF )* 2;
            msWrite2ByteMask(REG_162DEA, 0x2220, 0xFFF0); // Combo2sc IPMUX  (SPT_0, SPT_1, SPT_2)
            msWrite2ByteMask(REG_162DEC, 0x0002, 0x000F); // Combo2sc IPMUX  (SPT_3)
        }

        msWrite2ByteMask(REG_162DEE, 0x01E0, 0x01E0); // [8:5]: reg_clk_combo2sc_spt_en

        msWrite2ByteMask(REG_162DF2, 0x2220, 0xFFF0); // Combo2spt CLKMUX (SPT_0, SPT_1, SPT_2)
        msWrite2ByteMask(REG_162DF4, 0x0002, 0x000F); // Combo2sc CLKMUX (SPT_3)

        // Splitter
        MDrv_Write2Byte(REG_162CDE, 0x0001); // [0] reg_spt4k_com_en

        msWrite2ByteMask(REG_162D06, bFlag?0x0000:0x0001, 0x0001); // [0]: reg_spt_420_en
        MDrv_Write2Byte(REG_162D08, 0x0000); // [9] [8] [7] [6] [3:2] [1] [0]
        MDrv_Write2Byte(REG_162D60, 0x0003); // [1] reg_de_only; [0] reg_mode_det_en
        MDrv_Write2Byte(REG_162D10, wRealWidth / 2); // [12:0] reg_spt_in_de_size
        MDrv_Write2Byte(REG_162D16, DFT_HBR2_GUARDBAND); // [12:0] reg_spt_out_gb_size = 0
        MDrv_Write2Byte(REG_162D14, (wRealWidth / 2) + DFT_HBR2_GUARDBAND); // [12:0] reg_spt_out_de_size_with_gb (real_width/2 + reg_spt_out_gb_size)

        MDrv_Write2Byte(REG_162D40, 0x0000); // [12:0] reg_spt_ra_st0 = 0
        MDrv_Write2Byte(REG_162D42, ((wRealWidth / 4) / 2) - 1 + (DFT_HBR2_GUARDBAND/4)); // [12:0] reg_spt_ra_end0
        MDrv_Write2Byte(REG_162D44, (wRealWidth / 4) / 2 - (DFT_HBR2_GUARDBAND/4)); // [12:0] reg_spt_ra_st1 = 1
        MDrv_Write2Byte(REG_162D46, (wRealWidth / 4) - 1); // [12:0] reg_spt_ra_end1
        MDrv_Write2Byte(REG_162D48, 0x0000); // [12:0] reg_spt_wa_st0
        MDrv_Write2Byte(REG_162D4A, ((wRealWidth / 4) - 2)); // [12:0] reg_spt_wa_end0
        MDrv_Write2Byte(REG_162D4C, 0x0001); // [12:0] reg_spt_wa_st1
        MDrv_Write2Byte(REG_162D4E, (wRealWidth / 4) - 1); // [12:0] reg_spt_wa_end0
    }
    else
    {
        TMDS_PRINT("Port: 0x%x, no need\r\n", enInputPort);
    }
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_CheckAVMuteINT()
//  [Description]:
//                  check if GCP AV Mute INT status is set
//  [Arguments]:
//                  enInputPort
//                  bClr : True to clr INT status, false to polling status
//  [Return]:
//                  BOOL
//**************************************************************************
BOOL mhal_tmds_CheckAVMuteINT(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bClr)
{
    if(!bClr)
    {
        if(enInputPort == MSCombo_TMDS_PORT_0)
        {
            if ((MDrv_ReadByte(REG_1605C2) & BIT0) || (MDrv_ReadByte(REG_1605C4) & BIT0))
                return TRUE;
            else
                return FALSE;
        }
        else if(enInputPort == MSCombo_TMDS_PORT_1)
        {
            if ((MDrv_ReadByte(REG_160AC2) & BIT0) || (MDrv_ReadByte(REG_160AC4) & BIT0))
                return TRUE;
            else
                return FALSE;
        }
        else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
        {
            if ((MDrv_ReadByte(REG_1611C2) & BIT0) || (MDrv_ReadByte(REG_1611C4) & BIT0))
                return TRUE;
            else
                return FALSE;
        }
        else
            return FALSE;
    }
    else
    {
        if(enInputPort == MSCombo_TMDS_PORT_0)
        {
            MDrv_WriteByteMask(REG_1605C4,0x00,0x01);
            MDrv_WriteByteMask(REG_1605C6,0x01,0x01); //[0]: clear GC pkt content chg status
            MDrv_WriteByteMask(REG_1605C6,0x00,0x01);
            return FALSE;
        }
        else if(enInputPort == MSCombo_TMDS_PORT_1)
        {
            MDrv_WriteByteMask(REG_160AC4,0x00,0x01);
            MDrv_WriteByteMask(REG_160AC6,0x01,0x01); //[0]: clear GC pkt content chg status
            MDrv_WriteByteMask(REG_160AC6,0x00,0x01);
            return FALSE;
        }
        else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
        {
            MDrv_WriteByteMask(REG_1611C4,0x00,0x01);
            MDrv_WriteByteMask(REG_1611C6,0x01,0x01); //[0]: clear GC pkt content chg status
            MDrv_WriteByteMask(REG_1611C6,0x00,0x01);
            return FALSE;
        }
        else
            return FALSE;
    }
}


//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_CheckAVMute()
//  [Description]:
//                  check if GCP AV Mute bit is set
//  [Arguments]:
//                  enInputPort
//  [Return]:
//                  BOOL
//**************************************************************************
BOOL mhal_tmds_CheckAVMute(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    if(enInputPort == MSCombo_TMDS_PORT_0)
    {
        if (MDrv_ReadByte(REG_16052A) & BIT0)
            return TRUE;
        else
            return FALSE;
    }
    else if(enInputPort == MSCombo_TMDS_PORT_1)
    {
        if (MDrv_ReadByte(REG_160A2A) & BIT0)
            return TRUE;
        else
            return FALSE;
    }
    else if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
    {
        if (MDrv_ReadByte(REG_16112A) & BIT0)
            return TRUE;
        else
            return FALSE;
    }
    else
        return FALSE;
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_AUPLL_Setting()
//  [Description]:
//                  do aupll setting for different audio sample rate
//  [Arguments]:
//                  bFlag : True > 100 khz, false <= 100khz
//  [Return]:
//
//**************************************************************************
void mhal_tmds_AUPLL_Setting(MScombo_TMDS_AUD_FREQ_INDEX enAudFreq)
{
    MDrv_WriteByteMask(REG_162F13, 0x00, 0x60); //KN
    switch(enAudFreq)
    {
        case MScombo_TMDS_AUD_FREQ_176K:
            MDrv_WriteByteMask(REG_162F12, 0x11, 0xFF); //[7:4]:KM, [3:0]:KP
            MDrv_WriteByteMask(REG_162F15, 0x02, 0x0F); //DDIV
            MDrv_WriteByteMask(REG_162F15, 0x60,0xF0); //FBDIV
            MDrv_WriteByteMask(REG_162F0C, 0x00,0x40); //[6]:reg_aupll_enindiv1
        break;
        case MScombo_TMDS_AUD_FREQ_88K:
            MDrv_WriteByteMask(REG_162F12, 0x22, 0xFF); //[7:4]:KM, [3:0]:KP
            MDrv_WriteByteMask(REG_162F15, 0x01, 0x0F); //DDIV
            MDrv_WriteByteMask(REG_162F15, 0x30,0xF0); //FBDIV
            MDrv_WriteByteMask(REG_162F0C, 0x40,0x40); //[6]:reg_aupll_enindiv1
        break;
        case MScombo_TMDS_AUD_FREQ_32K:
            MDrv_WriteByteMask(REG_162F12, 0x33, 0xFF); //[7:4]:KM, [3:0]:KP
            MDrv_WriteByteMask(REG_162F15, 0x01, 0x0F); //DDIV
            MDrv_WriteByteMask(REG_162F15, 0x30,0xF0); //FBDIV
            MDrv_WriteByteMask(REG_162F0C, 0x40,0x40); //[6]:reg_aupll_enindiv1
        break;
        default:
            MDrv_WriteByteMask(REG_162F12, 0x33, 0xFF); //[7:4]:KM, [3:0]:KP
            MDrv_WriteByteMask(REG_162F15, 0x01, 0x0F); //DDIV
            MDrv_WriteByteMask(REG_162F15, 0x30,0xF0); //FBDIV
            MDrv_WriteByteMask(REG_162F0C, 0x40,0x40); //[6]:reg_aupll_enindiv1
        break;
    }
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_HDCPFrameClear()
//  [Description]:
//                  HDCP frame clear
//  [Arguments]:
//                  [MSCombo_TMDS_PORT_INDEX]PortIdx
//                  [Bool]bFlag: TRUE: DVI mode; FALSE: HDMI mode
//  [Return]:
//
//**************************************************************************
void mhal_tmds_HDCPFrameClear(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bFlag)
{
    if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
    {
        MDrv_WriteByteMask(REG_160C32, bFlag?0x08:0x00, 0x08); // [3]: reg_dbg_tst
    }
    else
    {
        TMDS_PRINT("Port: 0x%x, no need\r\n", enInputPort);
    }
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_DeepColorFIFOReset()
//  [Description]:
//                  deep color FIFO reset when DE pixel change
//  [Arguments]:
//                  [MSCombo_TMDS_PORT_INDEX]PortIdx
//  [Return]:
//
//**************************************************************************
void mhal_tmds_DeepColorFIFOReset(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    if((enInputPort == MSCombo_TMDS_PORT_2) || (enInputPort == MSCombo_TMDS_PORT_3))
    {
        if(MDrv_ReadByte(REG_161104) & 0x20) // [5]: DE pixel change
        {
            MDrv_WriteByte(REG_1611BF, 0x20); // reset deep color FIFO
            MDrv_WriteByte(REG_1611BF, 0x00); // reset deep color FIFO
            MDrv_WriteByte(REG_161104, 0x20); // clear DE pixel change
        }
    }
    else
    {
        TMDS_PRINT("Port: 0x%x, no need\r\n", enInputPort);
    }
}

#if 0 // this is new merged one, register bank is not checked
//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_GetSCDCStatusFlag()
//  [Description]:
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
Bool mhal_tmds_GetSCDCStatusFlag(MSCombo_TMDS_PORT_INDEX enInputPort, BYTE ucStatusMask)
{
    Bool bStatusFlag = FALSE;

    switch(enInputPort)
    {
        case MSCombo_TMDS_PORT_0:

            break;

        case MSCombo_TMDS_PORT_1:

            break;

        case MSCombo_TMDS_PORT_2:
        case MSCombo_TMDS_PORT_3:
            if(enInputPort == bCurrentPort)
            {
                bStatusFlag = ((msReadByte(REG_00180E) &ucStatusMask) ?TRUE: FALSE); // REG_PM_SCDC_07
            }

            break;

        default:

            break;
    };

    if(bStatusFlag)
    {
        _mhal_tmds_ClearSCDCStatusFlag(enInputPort, ucStatusMask);
    }

    return bStatusFlag;
}
#endif
#endif

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_HDCP2WriteDone()
//  [Description]:
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
BOOL mhal_tmds_HDCP2CheckWriteDone(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    // wirte IRQ done
    if(enInputPort == MSCombo_TMDS_PORT_0)
    {
        if(MDrv_ReadByte(REG_1006CC) & BIT2)     // IRQ status: 66
        {
            MDrv_WriteByteMask(REG_1006CC, 0x04, 0x04); //clear wirte done status
            MDrv_WriteByteMask(REG_1006CC, 0x10, 0x10); //clear write start status

            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
#if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA) )
    else if(enInputPort == MSCombo_TMDS_PORT_1)
    {
        if(MDrv_ReadByte(REG_1006CC + 0x300) & BIT2)     // IRQ status: 66
        {
            MDrv_WriteByteMask(REG_1006CC + 0x300, 0x04, 0x04); //clear wirte done status
            MDrv_WriteByteMask(REG_1006CC + 0x300, 0x10, 0x10); //clear write start status

            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else if(enInputPort == MSCombo_TMDS_PORT_2)
    {
        if(MDrv_ReadByte(REG_1006CC + 0x600) & BIT2)     // IRQ status: 66
        {
            MDrv_WriteByteMask(REG_1006CC + 0x600, 0x04, 0x04); //clear wirte done status
            MDrv_WriteByteMask(REG_1006CC + 0x600, 0x10, 0x10); //clear write start status

            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else if(enInputPort == MSCombo_TMDS_PORT_3)
    {
        if(MDrv_ReadByte(REG_1006CC + 0x900) & BIT2)     // IRQ status: 66
        {
            MDrv_WriteByteMask(REG_1006CC + 0x900, 0x04, 0x04); //clear wirte done status
            MDrv_WriteByteMask(REG_1006CC + 0x900, 0x10, 0x10); //clear write start status

            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
#else
    else if(enInputPort == MSCombo_TMDS_PORT_1)
    {
        if(MDrv_ReadByte(REG_100BCC) & BIT2)     // IRQ status: 66
        {
            MDrv_WriteByteMask(REG_100BCC, 0x04, 0x04); //clear wirte done status
            MDrv_WriteByteMask(REG_100BCC, 0x10, 0x10); //clear write start status

            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
#endif
    else
        return FALSE;
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_HDCP2GetDataInfo()
//  [Description]:
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mhal_tmds_HDCP2GetDataInfo(MSCombo_TMDS_PORT_INDEX enInputPort, WORD ucDataSize, BYTE *pHDCPRxData)
{
    WORD i = 0;

//printf("ucDataSize=%d \n", ucDataSize);
#if ((CHIP_FAMILY_TYPE==CHIP_FAMILY_MAYA)||(CHIP_FAMILY_TYPE==CHIP_FAMILY_MAZDA))
    MDrv_WriteByteMask(REG_100E80, 0x03, 0x07); //enable XIU read
#else
	// whisky@
	//MDrv_WriteRegBit(0x110ac0+0x19*2, BIT1, BIT1); //enable xiu  [0]
	//MDrv_WriteRegBit(0x110ac0+0x00*2, BIT1,  BIT1); //enable xiu  [1]
	//MDrv_WriteRegBit(0x110ac0+0x19*2+1, 0, BIT7); //enable xiu  [2]
      	//MDrv_WriteByteMask(0x110af2, BIT1, BIT1); //enable xiu  [0]
	//MDrv_WriteByteMask(0x110ac0, BIT1,  BIT1); //enable xiu  [1]
	//MDrv_WriteByteMask(0x110af3, 0, BIT7); //enable xiu  [2]

#if 0
	MDrv_Write2Byte(0x110af2, 0x0802);
	MDrv_Write2Byte(0x110ac0, 0x0022);
	//MDrv_Write2Byte(0x123a00, 0x0000);
#endif

	MDrv_WriteByteMask(REG_10012D, 0xEE, 0xFF); // Set twa: Cindy (Set twa = 0x1001_16[15:8] = 8'hee)
#endif
    switch(enInputPort)
    {
        case MSCombo_TMDS_PORT_0:
            RIU[REG_101508] = 0x0000; // xiu to memory access address: 04
            for ( i = 0; i < ucDataSize; i++ )
            {
                pHDCPRxData[i] = MDrv_ReadByte(REG_10151C); // memory to xiu read data (port0): 0e
            }
        break;

        case MSCombo_TMDS_PORT_1:
            RIU[REG_10150C] = 0x0000; // xiu to memory access address: 06
            for ( i = 0; i < ucDataSize; i++ )
            {
                pHDCPRxData[i] = MDrv_ReadByte(REG_10151E); // memory to xiu read data (port1): 0f
            }
        break;
  #if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA) )
        case MSCombo_TMDS_PORT_2:
            RIU[REG_101510] = 0x0000; // xiu to memory access address: 08
            for ( i = 0; i < ucDataSize; i++ )
            {
                pHDCPRxData[i] = MDrv_ReadByte(REG_101520); // memory to xiu read data (port1): 0f
            }
        break;
        case MSCombo_TMDS_PORT_3:
            RIU[REG_101514] = 0x0000; // xiu to memory access address: 0a
            for ( i = 0; i < ucDataSize; i++ )
            {
                pHDCPRxData[i] = MDrv_ReadByte(REG_101522); // memory to xiu read data (port1): 0f
            }
        break;
  #endif
        default:
            break;
    }
#if ((CHIP_FAMILY_TYPE==CHIP_FAMILY_MAYA)||(CHIP_FAMILY_TYPE==CHIP_FAMILY_MAZDA))
#else
	MDrv_WriteByteMask(REG_10012D, 0x00, 0xFF); // Release twa: Cindy (Release twa = 0x1001_16[15:8] = 8'h00)
#endif

    printf("[r:%d %d]\n", *pHDCPRxData, MsOS_GetSystemTime());

}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_HDCP2GetRxData()
//  [Description]:
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mhal_tmds_HDCP2GetRxData(MSCombo_TMDS_PORT_INDEX enInputPort, BYTE *pHDCPRxData)
{
    if(enInputPort == MSCombo_TMDS_PORT_0)
        mhal_tmds_HDCP2GetDataInfo(enInputPort, MDrv_Read2Byte(REG_1006C8) & 0x03FF, pHDCPRxData);  // message length receive: 64
#if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA) )
    else if(enInputPort == MSCombo_TMDS_PORT_1)
        mhal_tmds_HDCP2GetDataInfo(enInputPort, MDrv_Read2Byte(REG_1006C8 + 0x300) & 0x03FF, pHDCPRxData);  // message length receive: 64
    else if(enInputPort == MSCombo_TMDS_PORT_2)
        mhal_tmds_HDCP2GetDataInfo(enInputPort, MDrv_Read2Byte(REG_1006C8 + 0x600) & 0x03FF, pHDCPRxData);  // message length receive: 64
    else if(enInputPort == MSCombo_TMDS_PORT_3)
        mhal_tmds_HDCP2GetDataInfo(enInputPort, MDrv_Read2Byte(REG_1006C8 + 0x900) & 0x03FF, pHDCPRxData);  // message length receive: 64
#else
    else if(enInputPort == MSCombo_TMDS_PORT_1)
        mhal_tmds_HDCP2GetDataInfo(enInputPort, MDrv_Read2Byte(REG_100BC8) & 0x03FF, pHDCPRxData);  // message length receive: 64
#endif
    else
    {
        TMDS_PRINT("Port: 0x%x, no need\r\n", enInputPort);
    }
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_HDCP2WriteStart()
//  [Description]:
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
BOOL mhal_tmds_HDCP2CheckWriteStart(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    // write IRQ start
    if(enInputPort == MSCombo_TMDS_PORT_0)
    {
        if(MDrv_ReadByte(REG_1006CC) & BIT4)     // IRQ status: 66
        {
            MDrv_WriteByteMask(REG_1006CC, 0x10, 0x10);    // IRQ write start clear: 66
            MDrv_WriteByteMask(REG_1006CC, 0x00, 0x10);

            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
#if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA) )
    else if(enInputPort == MSCombo_TMDS_PORT_1)
    {
        if(MDrv_ReadByte(REG_1006CC + 0x300) & BIT4)     // IRQ status: 66
        {
            MDrv_WriteByteMask(REG_1006CC + 0x300, 0x10, 0x10);    // IRQ write start clear: 66
            MDrv_WriteByteMask(REG_1006CC + 0x300, 0x00, 0x10);

            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else if(enInputPort == MSCombo_TMDS_PORT_2)
    {
        if(MDrv_ReadByte(REG_1006CC + 0x600) & BIT4)     // IRQ status: 66
        {
            MDrv_WriteByteMask(REG_1006CC + 0x600, 0x10, 0x10);    // IRQ write start clear: 66
            MDrv_WriteByteMask(REG_1006CC + 0x600, 0x00, 0x10);

            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else if(enInputPort == MSCombo_TMDS_PORT_3)
    {
        if(MDrv_ReadByte(REG_1006CC + 0x900) & BIT4)     // IRQ status: 66
        {
            MDrv_WriteByteMask(REG_1006CC + 0x900, 0x10, 0x10);    // IRQ write start clear: 66
            MDrv_WriteByteMask(REG_1006CC + 0x900, 0x00, 0x10);

            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
#else
    else if(enInputPort == MSCombo_TMDS_PORT_1)
    {
        if(MDrv_ReadByte(REG_100BCC) & BIT4)     // IRQ status: 66
        {
            MDrv_WriteByteMask(REG_100BCC, 0x10, 0x10);    // IRQ write start clear: 66
            MDrv_WriteByteMask(REG_100BCC, 0x00, 0x10);

            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
#endif
    else
        return FALSE;
}

//U8 msMemReadByte(U32 addr);

U8 msMemReadByte(U32 addr)
{
    U8 ret;
   // addr|=BIT31;
    ret=MDrv_ReadByte(addr);

    return ret;

}
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
#if ( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA) )
void mhal_tmds_HDCP2SetDataInfo_mazda(MSCombo_TMDS_PORT_INDEX enInputPort, BYTE MessageID, BYTE DataSize, BYTE *pHDCPTxData, BYTE *pHDCPTxData_CertRx)
{
    WORD i = 0;
    WORD u16RdOffset = 130;
    printf("[t:%d %d]\n", MessageID, MsOS_GetSystemTime());
    MDrv_WriteByteMask(REG_100E80, 0x05, 0x07); //enable xiu write

    switch(enInputPort)
    {
        case MSCombo_TMDS_PORT_0:
        {
            RIU[REG_101508] = u16RdOffset;  // xiu to memory access address: 04

            if(MessageID == TMDS_HDCP2_MSG_ID_AKE_SEND_CERT)
            {
                MDrv_WriteByte(REG_10150A, MessageID);  // xiu to memory wirte data: 05
                for ( i = 0; i < (522 + DataSize); i++ )
                {
                    RIU[REG_101508] = u16RdOffset + i + 1; //set address

                    if (i < 522)
                    {
                        MDrv_WriteByte(REG_10150A, *(BYTE*)(((ULONG)pHDCPTxData_CertRx + i)));
                        RIU[REG_101508] = u16RdOffset + i + 1; //set address
                        while (MDrv_ReadByte(REG_10151C) != *(BYTE*)(((ULONG)pHDCPTxData_CertRx + i)))
                        {
                            RIU[REG_101508] = u16RdOffset + i + 1;
                            MDrv_WriteByte(REG_10150A, *(BYTE*)(((ULONG)pHDCPTxData_CertRx + i)));
                            RIU[REG_101508] = u16RdOffset + i + 1;
                        }
                    }
                    else
                    {
                        MDrv_WriteByte(REG_10150A, *(BYTE*)(((ULONG)pHDCPTxData + i - 522)));
                        RIU[REG_101508] = u16RdOffset + i + 1; //set address
                        while (MDrv_ReadByte(REG_10151C) != *(BYTE*)(((ULONG)pHDCPTxData + i - 522)))
                        {
                            RIU[REG_101508] = u16RdOffset + i + 1;
                            MDrv_WriteByte(REG_10150A, *(BYTE*)(((ULONG)pHDCPTxData + i - 522)));
                            RIU[REG_101508] = u16RdOffset + i + 1;
                        }
                    }
                }
                MDrv_Write2Byte(REG_1006C6, 0x216);     // write length
                MDrv_WriteByteMask(REG_1006C9, 0x80, 0x80); // mdssage data length update pulse (sink)
            }
            else
            {

                MDrv_WriteByte(REG_10150A, MessageID);  // xiu to memory wirte data: 05
                for(i = 0; i< DataSize; i++)
                {
                    RIU[REG_101508] = u16RdOffset + i + 1; //set address
                    MDrv_WriteByte(REG_10150A, *(BYTE*)(((ULONG)pHDCPTxData + i)));
                    RIU[REG_101508] = u16RdOffset + i + 1; //set address
                    while (MDrv_ReadByte(REG_10151C) != *(BYTE*)(((ULONG)pHDCPTxData + i)))
                    {
                        printf("+");
                        RIU[REG_101508] = u16RdOffset + i + 1;
                        MDrv_WriteByte(REG_10150A, *(BYTE*)(((ULONG)pHDCPTxData + i)));
                        RIU[REG_101508] = u16RdOffset + i + 1;
                    }
                }
                MDrv_Write2Byte(REG_1006C6, 1 + DataSize);  //  message datalength wrote by sink: 63 (1 + DataSize)
                MDrv_WriteByteMask(REG_1006C9, 0x80, 0x80); // mdssage data length update pulse (sink)
            }
        }
        break;
        case MSCombo_TMDS_PORT_1:
        {
            RIU[REG_10150C] = u16RdOffset;  // xiu to memory access address: 04

            if(MessageID == TMDS_HDCP2_MSG_ID_AKE_SEND_CERT)
            {
                MDrv_WriteByte(REG_10150E, MessageID);  // xiu to memory wirte data: 05
                for ( i = 0; i < (522 + DataSize); i++ )
                {
                    RIU[REG_10150C] = u16RdOffset + i + 1; //set address

                    if (i < 522)
                    {
                        MDrv_WriteByte(REG_10150E, *(BYTE*)(((ULONG)pHDCPTxData_CertRx + i)));
                        RIU[REG_10150C] = u16RdOffset + i + 1; //set address
                        while (MDrv_ReadByte(REG_10151E) != *(BYTE*)(((ULONG)pHDCPTxData_CertRx + i)))
                        {
                            RIU[REG_10150C] = u16RdOffset + i + 1;
                            MDrv_WriteByte(REG_10150E, *(BYTE*)(((ULONG)pHDCPTxData_CertRx + i)));
                            RIU[REG_10150C] = u16RdOffset + i + 1;
                        }
                    }
                    else
                    {
                        MDrv_WriteByte(REG_10150E, *(BYTE*)(((ULONG)pHDCPTxData + i - 522)));
                        RIU[REG_10150C] = u16RdOffset + i + 1; //set address
                        while (MDrv_ReadByte(REG_10151E) != *(BYTE*)(((ULONG)pHDCPTxData + i - 522)))
                        {
                            RIU[REG_10150C] = u16RdOffset + i + 1;
                            MDrv_WriteByte(REG_10150E, *(BYTE*)(((ULONG)pHDCPTxData + i - 522)));
                            RIU[REG_10150C] = u16RdOffset + i + 1;
                        }
                    }
                }
                MDrv_Write2Byte(REG_1006C6 + 0x300, 0x216);
                MDrv_WriteByteMask(REG_1006C9 + 0x300, 0x80, 0x80); // mdssage data length update pulse (sink)
            }
            else
            {

                MDrv_WriteByte(REG_10150E, MessageID);  // xiu to memory wirte data: 05
                for(i = 0; i< DataSize; i++)
                {
                    RIU[REG_10150C] = u16RdOffset + i + 1; //set address
                    MDrv_WriteByte(REG_10150E, *(BYTE*)(((ULONG)pHDCPTxData + i)));
                    RIU[REG_10150C] = u16RdOffset + i + 1; //set address

                    while (MDrv_ReadByte(REG_10151E) != *(BYTE*)(((ULONG)pHDCPTxData + i)))
                    {
                        printf("+");
                        RIU[REG_10150C] = u16RdOffset + i + 1;
                        MDrv_WriteByte(REG_10150E, *(BYTE*)(((ULONG)pHDCPTxData + i)));
                        RIU[REG_10150C] = u16RdOffset + i + 1;

                    }
                }
                MDrv_Write2Byte(REG_1006C6 + 0x300, 1 + DataSize);  //  message datalength wrote by sink: 63 (1 + DataSize)
                MDrv_WriteByteMask(REG_1006C9 + 0x300, 0x80, 0x80); // mdssage data length update pulse (sink)
            }
        }
        break;
        case MSCombo_TMDS_PORT_2:
        {
            RIU[REG_101510] = u16RdOffset;  // xiu to memory access address: 04

            if(MessageID == TMDS_HDCP2_MSG_ID_AKE_SEND_CERT)
            {
                MDrv_WriteByte(REG_101512, MessageID);  // xiu to memory wirte data: 05
                for ( i = 0; i < (522 + DataSize); i++ )
                {
                    RIU[REG_101510] = u16RdOffset + i + 1; //set address
                    if (i < 522)
                    {
                        MDrv_WriteByte(REG_101512, *(BYTE*)(((ULONG)pHDCPTxData_CertRx + i)));
                        RIU[REG_101510] = u16RdOffset + i + 1; //set address
                        while (MDrv_ReadByte(REG_101520) != *(BYTE*)(((ULONG)pHDCPTxData_CertRx + i)))
                        {
                            RIU[REG_101510] = u16RdOffset + i + 1;
                            MDrv_WriteByte(REG_101512, *(BYTE*)(((ULONG)pHDCPTxData_CertRx + i)));
                            RIU[REG_101510] = u16RdOffset + i + 1;
                        }
                    }
                    else
                    {
                        MDrv_WriteByte(REG_101512, *(BYTE*)(((ULONG)pHDCPTxData + i - 522)));
                        RIU[REG_101510] = u16RdOffset + i + 1; //set address
                        while (MDrv_ReadByte(REG_101520) != *(BYTE*)(((ULONG)pHDCPTxData + i - 522)))
                        {
                            RIU[REG_101510] = u16RdOffset + i + 1;
                            MDrv_WriteByte(REG_101512, *(BYTE*)(((ULONG)pHDCPTxData + i - 522)));
                            RIU[REG_101510] = u16RdOffset + i + 1;
                        }
                    }
                }
                MDrv_Write2Byte(REG_1006C6 + 0x600, 0x216);
                MDrv_WriteByteMask(REG_1006C9 + 0x600, 0x80, 0x80); // mdssage data length update pulse (sink)
            }
            else
            {

                MDrv_WriteByte(REG_101512, MessageID);  // xiu to memory wirte data: 05
                for(i = 0; i< DataSize; i++)
                {
                    RIU[REG_101510] = u16RdOffset + i + 1; //set address
                    MDrv_WriteByte(REG_101512, *(BYTE*)(((ULONG)pHDCPTxData + i)));
                    RIU[REG_101510] = u16RdOffset + i + 1; //set address

                    while (MDrv_ReadByte(REG_101520) != *(BYTE*)(((ULONG)pHDCPTxData + i)))
                    {
                        printf("+");
                        RIU[REG_101510] = u16RdOffset + i + 1;
                        MDrv_WriteByte(REG_101512, *(BYTE*)(((ULONG)pHDCPTxData + i)));
                        RIU[REG_101510] = u16RdOffset + i + 1;
                    }
                }
                MDrv_Write2Byte(REG_1006C6 + 0x600, 1 + DataSize);  //  message datalength wrote by sink: 63 (1 + DataSize)
                MDrv_WriteByteMask(REG_1006C9 + 0x600, 0x80, 0x80); // mdssage data length update pulse (sink)
            }
        }
        break;
        case MSCombo_TMDS_PORT_3:
        {
            RIU[REG_101514] = u16RdOffset;  // xiu to memory access address: 04

            if(MessageID == TMDS_HDCP2_MSG_ID_AKE_SEND_CERT)
            {
                MDrv_WriteByte(REG_101516, MessageID);  // xiu to memory wirte data: 05
                for ( i = 0; i < (522 + DataSize); i++ )
                {
                    RIU[REG_101514] = u16RdOffset + i + 1; //set address

                    if (i < 522)
                    {
                        MDrv_WriteByte(REG_101516, *(BYTE*)(((ULONG)pHDCPTxData_CertRx + i)));
                        RIU[REG_101514] = u16RdOffset + i + 1; //set address
                        while (MDrv_ReadByte(REG_101522) != *(BYTE*)(((ULONG)pHDCPTxData_CertRx + i)))
                        {
                            RIU[REG_101514] = u16RdOffset + i + 1;
                            MDrv_WriteByte(REG_101516, *(BYTE*)(((ULONG)pHDCPTxData_CertRx + i)));
                            RIU[REG_101514] = u16RdOffset + i + 1;
                        }
                    }
                    else
                    {
                        MDrv_WriteByte(REG_101516, *(BYTE*)(((ULONG)pHDCPTxData + i - 522)));
                        RIU[REG_101514] = u16RdOffset + i + 1; //set address

                        while (MDrv_ReadByte(REG_101522) != *(BYTE*)(((ULONG)pHDCPTxData + i - 522)))
                        {
                            RIU[REG_101514] = u16RdOffset + i + 1;
                            MDrv_WriteByte(REG_101516, *(BYTE*)(((ULONG)pHDCPTxData + i - 522)));
                            RIU[REG_101514] = u16RdOffset + i + 1;
                        }
                    }
                }
                MDrv_Write2Byte(REG_1006C6 + 0x900, 0x216);
                MDrv_WriteByteMask(REG_1006C9 + 0x900, 0x80, 0x80); // mdssage data length update pulse (sink)
            }
            else
            {

                MDrv_WriteByte(REG_101516, MessageID);  // xiu to memory wirte data: 05
                for(i = 0; i< DataSize; i++)
                {
                    RIU[REG_101514] = u16RdOffset + i + 1; //set address
                    MDrv_WriteByte(REG_101516, *(BYTE*)(((ULONG)pHDCPTxData + i)));
                    RIU[REG_101514] = u16RdOffset + i + 1; //set address

                    while (MDrv_ReadByte(REG_101522) != *(BYTE*)(((ULONG)pHDCPTxData + i)))
                    {
                        printf("+");
                        RIU[REG_101514] = u16RdOffset + i + 1;
                        MDrv_WriteByte(REG_101516, *(BYTE*)(((ULONG)pHDCPTxData + i)));
                        RIU[REG_101514] = u16RdOffset + i + 1;

                    }
                }
                MDrv_Write2Byte(REG_1006C6 + 0x900, 1 + DataSize);  //  message datalength wrote by sink: 63 (1 + DataSize)
                MDrv_WriteByteMask(REG_1006C9 + 0x900, 0x80, 0x80); // mdssage data length update pulse (sink)
            }
        }
        break;
        default:
        break;
    }
}
#endif
////////////////////////////////////////////////////////////////////////////
//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_HDCP2SetTxData()
//  [Description]:
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mhal_tmds_HDCP2SetDataInfo(MSCombo_TMDS_PORT_INDEX enInputPort, BYTE MessageID, BYTE DataSize, BYTE *pHDCPTxData, BYTE *pHDCPTxData_CertRx)
{
    WORD i = 0;
    WORD u16RdOffset = 130;

    printf("[t:%d %d]\n", MessageID, MsOS_GetSystemTime());

#if ((CHIP_FAMILY_TYPE==CHIP_FAMILY_MAYA)||(CHIP_FAMILY_TYPE==CHIP_FAMILY_MAZDA))
    MDrv_WriteByteMask(REG_100E80, 0x05, 0x07); //enable xiu write
#else
    // whisky@
#if 1
	MDrv_WriteRegBit(0x110ac0+0x19*2, BIT1, BIT1); //enable xiu  [0]
	MDrv_WriteRegBit(0x110ac0+0x00*2, 0, BIT1); //enable xiu  [1]
	MDrv_WriteRegBit(0x110ac0+0x19*2+1, BIT7, BIT7); //enable xiu  [2]
#endif
	MDrv_WriteByteMask(REG_10012D, 0xEE, 0xFF); // Set twa: Cindy (Set twa = 0x1001_16[15:8] = 8'hee)
 //   msWriteByteMask(REG_163080, 0x05, 0x07); //enable xiu write
#endif

    switch(enInputPort)
    {
        case MSCombo_TMDS_PORT_0:
        {
            RIU[REG_101508] = u16RdOffset;  // xiu to memory access address: 04

            if(MessageID == TMDS_HDCP2_MSG_ID_AKE_SEND_CERT)
            {
                MDrv_WriteByte(REG_10150A, MessageID);  // xiu to memory wirte data: 05
                for ( i = 0; i < (522 + DataSize); i++ )
                {
//                    U8 u8data;
                    RIU[REG_101508] = u16RdOffset + i + 1; //set address

                    if (i < 522)
                    {
                        //MDrv_WriteByte(REG_10150A, msMemReadByte((ULONG)pHDCPTxData_CertRx + i));
                        MDrv_WriteByte(REG_10150A, *(BYTE*)(BIT31|((ULONG)pHDCPTxData_CertRx + i)));
                        RIU[REG_101508] = u16RdOffset + i + 1; //set address


#if 0
u8data=*(BYTE*)(BIT31|((ULONG)pHDCPTxData_CertRx + i));
printf("%x ", u8data);
if(i%16==7) printf("  ");
if(i%16==15) printf("\n");
#endif
//printf("debug...\n");
//while(1);

                        //while (MDrv_ReadByte(REG_10151C) != msMemReadByte((ULONG)pHDCPTxData_CertRx + i))
                        while (MDrv_ReadByte(REG_10151C) != *(BYTE*)(BIT31|((ULONG)pHDCPTxData_CertRx + i)))
                        {
                            RIU[REG_101508] = u16RdOffset + i + 1;
                            //MDrv_WriteByte(REG_10150A, msMemReadByte((ULONG)pHDCPTxData_CertRx + i));
                            MDrv_WriteByte(REG_10150A, *(BYTE*)(BIT31|((ULONG)pHDCPTxData_CertRx + i)));
                            RIU[REG_101508] = u16RdOffset + i + 1;
                        }
                    }
                    else
                    {
                        MDrv_WriteByte(REG_10150A, *(BYTE*)(BIT31|((ULONG)pHDCPTxData + i - 522)));
                        RIU[REG_101508] = u16RdOffset + i + 1; //set address

                        while (MDrv_ReadByte(REG_10151C) != *(BYTE*)(BIT31|((ULONG)pHDCPTxData + i - 522)))
                        {
                            RIU[REG_101508] = u16RdOffset + i + 1;
                            MDrv_WriteByte(REG_10150A, *(BYTE*)(BIT31|((ULONG)pHDCPTxData + i - 522)));
                            RIU[REG_101508] = u16RdOffset + i + 1;
                        }
                    }
                }
#if ((CHIP_FAMILY_TYPE==CHIP_FAMILY_MAYA)||(CHIP_FAMILY_TYPE==CHIP_FAMILY_MAZDA))
                MDrv_Write2Byte(REG_1006C6, 0x216);
                MDrv_WriteByteMask(REG_1006C9, 0x80, 0x80); // mdssage data length update pulse (sink)
#else
                //polling read status
                //while (MDrv_ReadByte(REG_100633) & BIT2);

                //MDrv_WriteByte(REG_1006C6, 0x16);
                //MDrv_WriteByteMask(REG_1006C7, 0x2, 0x03);
                //MDrv_WriteByteMask(REG_1006C7, 0x80, 0x80); // mdssage data length update pulse (sink)

                MDrv_Write2Byte(REG_1006C6, 0x8216); // 534);
#endif

            }
            else
            {

                MDrv_WriteByte(REG_10150A, MessageID);  // xiu to memory wirte data: 05
                for(i = 0; i< DataSize; i++)
                {
                    RIU[REG_101508] = u16RdOffset + i + 1; //set address
                    MDrv_WriteByte(REG_10150A, *(BYTE*)(BIT31|((ULONG)pHDCPTxData + i)));
                    RIU[REG_101508] = u16RdOffset + i + 1; //set address

                    while (MDrv_ReadByte(REG_10151C) != *(BYTE*)(BIT31|((ULONG)pHDCPTxData + i)))
                    {
                        printf("+");
                        RIU[REG_101508] = u16RdOffset + i + 1;
                        MDrv_WriteByte(REG_10150A, *(BYTE*)(BIT31|((ULONG)pHDCPTxData + i)));
                        RIU[REG_101508] = u16RdOffset + i + 1;

                    }
//                    printf("%x " , *(BYTE*)(pHDCPTxData + i)  ) ;

                }

#if ((CHIP_FAMILY_TYPE==CHIP_FAMILY_MAYA)||(CHIP_FAMILY_TYPE==CHIP_FAMILY_MAZDA))
                MDrv_Write2Byte(REG_1006C6, 1 + DataSize);  //  message datalength wrote by sink: 63 (1 + DataSize)
                MDrv_WriteByteMask(REG_1006C9, 0x80, 0x80); // mdssage data length update pulse (sink)
#else
                //MDrv_Write2Byte(REG_1006C6, 1 + DataSize);  //  message datalength wrote by sink: 63 (1 + DataSize)
                //MDrv_WriteByteMask(REG_1006C7, 0x80, 0x80); // mdssage data length update pulse (sink)

                MDrv_Write2Byte(REG_1006C6, BIT15 | (1+DataSize)); // 534);
                //printf("@@ datasize=%d\n", DataSize);
#endif
            }
        }
        break;
#if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA) )
        case MSCombo_TMDS_PORT_1:
        {
            RIU[REG_10150C] = u16RdOffset;  // xiu to memory access address: 04

            if(MessageID == TMDS_HDCP2_MSG_ID_AKE_SEND_CERT)
            {
                MDrv_WriteByte(REG_10150E, MessageID);  // xiu to memory wirte data: 05
                for ( i = 0; i < (522 + DataSize); i++ )
                {
//                    U8 u8data;
                    RIU[REG_10150C] = u16RdOffset + i + 1; //set address

                    if (i < 522)
                    {
                        //MDrv_WriteByte(REG_10150A, msMemReadByte((ULONG)pHDCPTxData_CertRx + i));
                        MDrv_WriteByte(REG_10150E, *(BYTE*)(BIT31|((ULONG)pHDCPTxData_CertRx + i)));
                        RIU[REG_10150C] = u16RdOffset + i + 1; //set address


#if 0
u8data=*(BYTE*)(BIT31|((ULONG)pHDCPTxData_CertRx + i));
printf("%x ", u8data);
if(i%16==7) printf("  ");
if(i%16==15) printf("\n");
#endif
//printf("debug...\n");
//while(1);

                        //while (MDrv_ReadByte(REG_10151C) != msMemReadByte((ULONG)pHDCPTxData_CertRx + i))
                        while (MDrv_ReadByte(REG_10151E) != *(BYTE*)(BIT31|((ULONG)pHDCPTxData_CertRx + i)))
                        {
                            RIU[REG_10150C] = u16RdOffset + i + 1;
                            //MDrv_WriteByte(REG_10150A, msMemReadByte((ULONG)pHDCPTxData_CertRx + i));
                            MDrv_WriteByte(REG_10150E, *(BYTE*)(BIT31|((ULONG)pHDCPTxData_CertRx + i)));
                            RIU[REG_10150C] = u16RdOffset + i + 1;
                        }
                    }
                    else
                    {
                        MDrv_WriteByte(REG_10150E, *(BYTE*)(BIT31|((ULONG)pHDCPTxData + i - 522)));
                        RIU[REG_10150C] = u16RdOffset + i + 1; //set address

                        while (MDrv_ReadByte(REG_10151E) != *(BYTE*)(BIT31|((ULONG)pHDCPTxData + i - 522)))
                        {
                            RIU[REG_10150C] = u16RdOffset + i + 1;
                            MDrv_WriteByte(REG_10150E, *(BYTE*)(BIT31|((ULONG)pHDCPTxData + i - 522)));
                            RIU[REG_10150C] = u16RdOffset + i + 1;
                        }
                    }
                }
                MDrv_Write2Byte(REG_1006C6 + 0x300, 0x216);
                MDrv_WriteByteMask(REG_1006C9 + 0x300, 0x80, 0x80); // mdssage data length update pulse (sink)
            }
            else
            {

                MDrv_WriteByte(REG_10150E, MessageID);  // xiu to memory wirte data: 05
                for(i = 0; i< DataSize; i++)
                {
                    RIU[REG_10150C] = u16RdOffset + i + 1; //set address
                    MDrv_WriteByte(REG_10150E, *(BYTE*)(BIT31|((ULONG)pHDCPTxData + i)));
                    RIU[REG_10150C] = u16RdOffset + i + 1; //set address

                    while (MDrv_ReadByte(REG_10151E) != *(BYTE*)(BIT31|((ULONG)pHDCPTxData + i)))
                    {
                        printf("+");
                        RIU[REG_10150C] = u16RdOffset + i + 1;
                        MDrv_WriteByte(REG_10150E, *(BYTE*)(BIT31|((ULONG)pHDCPTxData + i)));
                        RIU[REG_10150C] = u16RdOffset + i + 1;

                    }
//                    printf("%x " , *(BYTE*)(pHDCPTxData + i)  ) ;

                }
                MDrv_Write2Byte(REG_1006C6 + 0x300, 1 + DataSize);  //  message datalength wrote by sink: 63 (1 + DataSize)
                MDrv_WriteByteMask(REG_1006C9 + 0x300, 0x80, 0x80); // mdssage data length update pulse (sink)
            }
        }
        break;
        case MSCombo_TMDS_PORT_2:
        {
            RIU[REG_101510] = u16RdOffset;  // xiu to memory access address: 04

            if(MessageID == TMDS_HDCP2_MSG_ID_AKE_SEND_CERT)
            {
                MDrv_WriteByte(REG_101512, MessageID);  // xiu to memory wirte data: 05
                for ( i = 0; i < (522 + DataSize); i++ )
                {
//                    U8 u8data;
                    RIU[REG_101510] = u16RdOffset + i + 1; //set address

                    if (i < 522)
                    {
                        //MDrv_WriteByte(REG_10150A, msMemReadByte((ULONG)pHDCPTxData_CertRx + i));
                        MDrv_WriteByte(REG_101512, *(BYTE*)(BIT31|((ULONG)pHDCPTxData_CertRx + i)));
                        RIU[REG_101510] = u16RdOffset + i + 1; //set address


#if 0
u8data=*(BYTE*)(BIT31|((ULONG)pHDCPTxData_CertRx + i));
printf("%x ", u8data);
if(i%16==7) printf("  ");
if(i%16==15) printf("\n");
#endif
//printf("debug...\n");
//while(1);

                        //while (MDrv_ReadByte(REG_10151C) != msMemReadByte((ULONG)pHDCPTxData_CertRx + i))
                        while (MDrv_ReadByte(REG_101520) != *(BYTE*)(BIT31|((ULONG)pHDCPTxData_CertRx + i)))
                        {
                            RIU[REG_101510] = u16RdOffset + i + 1;
                            //MDrv_WriteByte(REG_10150A, msMemReadByte((ULONG)pHDCPTxData_CertRx + i));
                            MDrv_WriteByte(REG_101512, *(BYTE*)(BIT31|((ULONG)pHDCPTxData_CertRx + i)));
                            RIU[REG_101510] = u16RdOffset + i + 1;
                        }
                    }
                    else
                    {
                        MDrv_WriteByte(REG_101512, *(BYTE*)(BIT31|((ULONG)pHDCPTxData + i - 522)));
                        RIU[REG_101510] = u16RdOffset + i + 1; //set address

                        while (MDrv_ReadByte(REG_101520) != *(BYTE*)(BIT31|((ULONG)pHDCPTxData + i - 522)))
                        {
                            RIU[REG_101510] = u16RdOffset + i + 1;
                            MDrv_WriteByte(REG_101512, *(BYTE*)(BIT31|((ULONG)pHDCPTxData + i - 522)));
                            RIU[REG_101510] = u16RdOffset + i + 1;
                        }
                    }
                }
                MDrv_Write2Byte(REG_1006C6 + 0x600, 0x216);
                MDrv_WriteByteMask(REG_1006C9 + 0x600, 0x80, 0x80); // mdssage data length update pulse (sink)
            }
            else
            {

                MDrv_WriteByte(REG_101512, MessageID);  // xiu to memory wirte data: 05
                for(i = 0; i< DataSize; i++)
                {
                    RIU[REG_101510] = u16RdOffset + i + 1; //set address
                    MDrv_WriteByte(REG_101512, *(BYTE*)(BIT31|((ULONG)pHDCPTxData + i)));
                    RIU[REG_101510] = u16RdOffset + i + 1; //set address

                    while (MDrv_ReadByte(REG_101520) != *(BYTE*)(BIT31|((ULONG)pHDCPTxData + i)))
                    {
                        printf("+");
                        RIU[REG_101510] = u16RdOffset + i + 1;
                        MDrv_WriteByte(REG_101512, *(BYTE*)(BIT31|((ULONG)pHDCPTxData + i)));
                        RIU[REG_101510] = u16RdOffset + i + 1;

                    }
//                    printf("%x " , *(BYTE*)(pHDCPTxData + i)  ) ;

                }
                MDrv_Write2Byte(REG_1006C6 + 0x600, 1 + DataSize);  //  message datalength wrote by sink: 63 (1 + DataSize)
                MDrv_WriteByteMask(REG_1006C9 + 0x600, 0x80, 0x80); // mdssage data length update pulse (sink)
            }
        }
        break;
        case MSCombo_TMDS_PORT_3:
        {
            RIU[REG_101514] = u16RdOffset;  // xiu to memory access address: 04

            if(MessageID == TMDS_HDCP2_MSG_ID_AKE_SEND_CERT)
            {
                MDrv_WriteByte(REG_101516, MessageID);  // xiu to memory wirte data: 05
                for ( i = 0; i < (522 + DataSize); i++ )
                {
//                    U8 u8data;
                    RIU[REG_101514] = u16RdOffset + i + 1; //set address

                    if (i < 522)
                    {
                        //MDrv_WriteByte(REG_10150A, msMemReadByte((ULONG)pHDCPTxData_CertRx + i));
                        MDrv_WriteByte(REG_101516, *(BYTE*)(BIT31|((ULONG)pHDCPTxData_CertRx + i)));
                        RIU[REG_101514] = u16RdOffset + i + 1; //set address


#if 0
u8data=*(BYTE*)(BIT31|((ULONG)pHDCPTxData_CertRx + i));
printf("%x ", u8data);
if(i%16==7) printf("  ");
if(i%16==15) printf("\n");
#endif
//printf("debug...\n");
//while(1);

                        //while (MDrv_ReadByte(REG_10151C) != msMemReadByte((ULONG)pHDCPTxData_CertRx + i))
                        while (MDrv_ReadByte(REG_101522) != *(BYTE*)(BIT31|((ULONG)pHDCPTxData_CertRx + i)))
                        {
                            RIU[REG_101514] = u16RdOffset + i + 1;
                            //MDrv_WriteByte(REG_10150A, msMemReadByte((ULONG)pHDCPTxData_CertRx + i));
                            MDrv_WriteByte(REG_101516, *(BYTE*)(BIT31|((ULONG)pHDCPTxData_CertRx + i)));
                            RIU[REG_101514] = u16RdOffset + i + 1;
                        }
                    }
                    else
                    {
                        MDrv_WriteByte(REG_101516, *(BYTE*)(BIT31|((ULONG)pHDCPTxData + i - 522)));
                        RIU[REG_101514] = u16RdOffset + i + 1; //set address

                        while (MDrv_ReadByte(REG_101522) != *(BYTE*)(BIT31|((ULONG)pHDCPTxData + i - 522)))
                        {
                            RIU[REG_101514] = u16RdOffset + i + 1;
                            MDrv_WriteByte(REG_101516, *(BYTE*)(BIT31|((ULONG)pHDCPTxData + i - 522)));
                            RIU[REG_101514] = u16RdOffset + i + 1;
                        }
                    }
                }
                MDrv_Write2Byte(REG_1006C6 + 0x900, 0x216);
                MDrv_WriteByteMask(REG_1006C9 + 0x900, 0x80, 0x80); // mdssage data length update pulse (sink)
            }
            else
            {

                MDrv_WriteByte(REG_101516, MessageID);  // xiu to memory wirte data: 05
                for(i = 0; i< DataSize; i++)
                {
                    RIU[REG_101514] = u16RdOffset + i + 1; //set address
                    MDrv_WriteByte(REG_101516, *(BYTE*)(BIT31|((ULONG)pHDCPTxData + i)));
                    RIU[REG_101514] = u16RdOffset + i + 1; //set address

                    while (MDrv_ReadByte(REG_101522) != *(BYTE*)(BIT31|((ULONG)pHDCPTxData + i)))
                    {
                        printf("+");
                        RIU[REG_101514] = u16RdOffset + i + 1;
                        MDrv_WriteByte(REG_101516, *(BYTE*)(BIT31|((ULONG)pHDCPTxData + i)));
                        RIU[REG_101514] = u16RdOffset + i + 1;

                    }
//                    printf("%x " , *(BYTE*)(pHDCPTxData + i)  ) ;

                }
                MDrv_Write2Byte(REG_1006C6 + 0x900, 1 + DataSize);  //  message datalength wrote by sink: 63 (1 + DataSize)
                MDrv_WriteByteMask(REG_1006C9 + 0x900, 0x80, 0x80); // mdssage data length update pulse (sink)
            }
        }
        break;
#else
        case MSCombo_TMDS_PORT_1:

            RIU[REG_10150C] = 0x0000;  // xiu to memory access address: 06

            if(MessageID == TMDS_HDCP2_MSG_ID_AKE_SEND_CERT)
            {
                MDrv_WriteByte(REG_10150E, MessageID);  // xiu to memory wirte data: 07
                for(i = 0; i< 522; i++)
                {
                    MDrv_WriteByte(REG_10150E, MIU8((ULONG)pHDCPTxData_CertRx + i));  // xiu to memory wirte data: 07
                }
                for(i = 0; i< DataSize; i++)
                {
                    MDrv_WriteByte(REG_10150E, *(BYTE*)(pHDCPTxData + i));  // xiu to memory wirte data: 07
                }
                MDrv_Write2Byte(REG_100BC6, 0x216);
                MDrv_WriteByteMask(REG_100BC9, 0x80, 0x80); // mdssage data length update pulse (sink)
            }
            else
            {
                MDrv_WriteByte(REG_10150E, MessageID);  // xiu to memory wirte data: 07
                for(i = 0; i< DataSize; i++)
                {
                    MDrv_WriteByte(REG_10150E, *(BYTE*)(pHDCPTxData + i));  // xiu to memory wirte data: 07
                }
                MDrv_Write2Byte(REG_100BC6, 1 + DataSize);  //  message datalength wrote by sink: 63 (1 + DataSize)
                MDrv_WriteByteMask(REG_100BC9, 0x80, 0x80); // mdssage data length update pulse (sink)
            }
        break;
#endif
        default:
        break;
    }
#if ((CHIP_FAMILY_TYPE==CHIP_FAMILY_MAYA)||(CHIP_FAMILY_TYPE==CHIP_FAMILY_MAZDA))
#else
	MDrv_WriteByteMask(REG_10012D, 0x00, 0xFF); // Set twa: Cindy (Release twa = 0x1001_16[15:8] = 8'h00)
#endif
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_HDCP2SetTxData()
//  [Description]:
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mhal_tmds_HDCP2SetTxData(MSCombo_TMDS_PORT_INDEX enInputPort, BYTE MessageID, BYTE DataSize, BYTE *pHDCPTxData, BYTE *pHDCPTxData_CertRx)
{
#if ( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA) )
    mhal_tmds_HDCP2SetDataInfo_mazda(enInputPort, MessageID, DataSize, pHDCPTxData, pHDCPTxData_CertRx);
#else
    mhal_tmds_HDCP2SetDataInfo(enInputPort, MessageID, DataSize, pHDCPTxData, pHDCPTxData_CertRx);
#endif
}

#endif // ENABLE_SECURITY_R2_HDCP22

//#endif // _MHAL_TMDS_C_

