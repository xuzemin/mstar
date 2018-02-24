///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   Mhal_combo.c
/// @author MStar Semiconductor Inc.
/// @brief  MHL driver Function
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _MHAL_COMBO_C_
#define _MHAL_COMBO_C_

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
//#include "Global.h"
#include "msAPI_SecurityR2.h"
#include "datatype.h"
#include "drvGlobal.h"
#include "msReg.h"
#include "apiXC.h"
#include "mapi_combo.h"
#include "mdrv_combo.h"
#include "mhal_combo.h"
#if (CHIP_FAMILY_TYPE==CHIP_FAMILY_MAZDA)
#include "apiXC_Hdmi.h"
#endif
//#include "msEread.h"

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
#define MHALCOMBO_DEBUG    1
#if ENABLE_MSTV_UART_DEBUG && MHALCOMBO_DEBUG
#define MHALCOMBO_PRINT(format, ...)     printf(format, ##__VA_ARGS__)
#else
#define MHALCOMBO_PRINT(format, ...)
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
#if 0
BYTE ucComboVersionIndex = 0;
WORD usComboIDIndex = 0;
#endif

//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------
#if 0
//**************************************************************************
//  [Function Name]:
//                  _mhal_combo_bank_offset()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
WORD _mhal_combo_bank_offset(BYTE ucPortSelect)
{
    WORD wOffset = 0;

    switch(ucPortSelect)
    {
        case COMBO_INPUT_SELECT_PORT0:
		    wOffset = 0x0000;
			break;

        case COMBO_INPUT_SELECT_PORT1:
		    wOffset = 0x0600;
			break;

        case COMBO_INPUT_SELECT_PORT2:
		    wOffset = 0x0E00;
			break;

        case COMBO_INPUT_SELECT_PORT3:
		    wOffset = 0x1600;
			break;

        case COMBO_INPUT_SELECT_PORT4:
		    wOffset = 0x1E00;
			break;

        default:

            break;
    };

	return wOffset;
}

//**************************************************************************
//  [Function Name]:
//                  _mhal_combo_phy_offset()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
WORD _mhal_combo_phy_offset(BYTE ucPortSelect)
{
    WORD wOffset = 0;

    switch(ucPortSelect)
    {
        case COMBO_INPUT_SELECT_PORT0:
		    wOffset = 0x0000;
			break;

        case COMBO_INPUT_SELECT_PORT1:
		    wOffset = 0x0100;
			break;

        case COMBO_INPUT_SELECT_PORT2:
		    wOffset = 0x0200;
			break;

        case COMBO_INPUT_SELECT_PORT3:
		    wOffset = 0x0300;
			break;

        case COMBO_INPUT_SELECT_PORT4:
		    wOffset = 0x0400;
			break;

        default:

            break;
    };

	return wOffset;
}

//**************************************************************************
//  [Function Name]:
//                  _mhal_combo_InsertEDIDData()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void _mhal_combo_InsertEDIDData(BYTE ucAddress, BYTE ucData)
{
    MDrv_WriteByte(REG_003E4B, ucAddress); // REG_DDC_BANK_25[14:8]: DDC address port for CPU read/write
    MDrv_WriteByte(REG_003E4C, ucData); // REG_DDC_BANK_26[7:0]: DDC Data Port for cpu write
    MDrv_WriteByteMask(REG_003E43, BIT5, BIT5); // REG_DDC_BANK_21[13]: ADC sram write data pulse gen when cpu write

    while(MDrv_ReadByte(REG_003E7B) & BIT5); // REG_DDC_BANK_3D[13]: ADC_0 cpu wr busy status (wr for ADC sram)
}

//**************************************************************************
//  [Function Name]:
//                  mhal_combo_LoadEDID()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mhal_combo_LoadEDID(BYTE ucPortSelect, Bool bDPInput, BYTE ucEDIDSize, BYTE ucEDIDAddr, BYTE *pComboEDID)
{
    BYTE uctemp = 0;
    BYTE ucSizeCount = 0;

    if((ucEDIDSize != 0) && (pComboEDID != NULL))
    {
        if(ucPortSelect == COMBO_INPUT_SELECT_VGA)
        {
            MDrv_WriteByteMask(REG_003EEB, 0, MASKBIT(4:0)); // REG_DDC_BANK_75[12:8]: Select EDID sram base address for cpu read/write

            for(uctemp = 0; uctemp < COMBO_EDID_BLOCK_SIZE; uctemp++)
            {
                _mhal_combo_InsertEDIDData(uctemp, pComboEDID[uctemp]);
            }

            MDrv_WriteByteMask(REG_003EFA, 0, MASKBIT(4:0)); // REG_DDC_BANK_7D[4:0]: Select A0 EDID sram base address
        }
        else
        {
            for(ucSizeCount = 0; ucSizeCount < ucEDIDSize; ucSizeCount++)
            {
                MDrv_WriteByteMask(REG_003EEB, ucEDIDAddr +ucSizeCount, MASKBIT(4:0)); // REG_DDC_BANK_75[12:8]: Select EDID sram base address for cpu read/write

                for(uctemp = 0; uctemp < COMBO_EDID_BLOCK_SIZE; uctemp++)
                {
                    _mhal_combo_InsertEDIDData(uctemp, pComboEDID[uctemp +ucSizeCount *COMBO_EDID_BLOCK_SIZE]);
                }
            }

            switch(ucPortSelect)
            {
                case COMBO_INPUT_SELECT_PORT0:
                    MDrv_WriteByteMask(REG_003EEC, ucEDIDAddr, MASKBIT(4:0)); // REG_DDC_BANK_76[4:0]: Select D0 EDID sram base address
        			break;

                case COMBO_INPUT_SELECT_PORT1:
                    MDrv_WriteByteMask(REG_003EED, ucEDIDAddr, MASKBIT(4:0)); // REG_DDC_BANK_76[12:8]: Select D1 EDID sram base address
        			break;

                case COMBO_INPUT_SELECT_PORT2:
                    MDrv_WriteByteMask(REG_003EF6, ucEDIDAddr, MASKBIT(4:0)); // REG_DDC_BANK_7B[4:0]: Select D2 EDID sram base address
        			break;

                case COMBO_INPUT_SELECT_PORT3:
                    MDrv_WriteByteMask(REG_003EF7, ucEDIDAddr, MASKBIT(4:0)); // REG_DDC_BANK_7B[12:8]: Select D3 EDID sram base address
        			break;

                case COMBO_INPUT_SELECT_PORT4:
                    MDrv_WriteByteMask(REG_003EF8, ucEDIDAddr, MASKBIT(4:0)); // REG_DDC_BANK_7C[4:0]: Select DP_AUX EDID sram base address
        			break;

                default:

                    break;
            };
        }
    }

    if(bDPInput) // Use to avoid compiler warning, must remove this temp condition when use this flag
    {

    }
}

//**************************************************************************
//  [Function Name]:
//                  mhal_combo_LoadHDCPKey()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mhal_combo_LoadHDCPKey(BYTE ucPortSelect, Bool bDPInput, BYTE ucBcaps, BYTE *pHDCPKey, BYTE *pBKSV)
{
    static Bool bKeyFlag = FALSE;
    static Bool bP2LoadKey = FALSE;
    WORD ustemp = 0;

    // Load HDCP key
    if(!bKeyFlag)
    {
        if(pHDCPKey != NULL)
        {
#if(COMBO_LOAD_HDCP_USE_RIU)
            MDrv_WriteByteMask(REG_163080, 0x0C, 0x0C); //enable CPU write SRAM
            MDrv_WriteByteMask(REG_163082, 0x00, 0xFF); //key address
            MDrv_WriteByteMask(REG_163083, 0x00, 0x03); //key address
            MDrv_WriteByteMask(REG_163080, 0x10, 0x10); //load address

            for(ustemp = 0; ustemp < COMBO_HDCP_BKSV_SIZE; ustemp++)
            {
                MDrv_WriteByteMask(REG_163084, pBKSV[ustemp], 0xFF); // bksv
                MDrv_WriteByteMask(REG_163080, 0x10, 0x10); // write data pulse

                while(MDrv_ReadByte(REG_10062E + wOffset) & 0x10);
            }

            for(ustemp = 0; ustemp < COMBO_HDCP_KEY_SIZE; ustemp++)
            {
                MDrv_WriteByteMask(REG_163084, pHDCPKey[ustemp], 0xFF); // bksv
                MDrv_WriteByteMask(REG_163080, 0x10, 0x10); // write data pulse

                while(MDrv_ReadByte(REG_10062E + wOffset) & 0x10);
            }

            MDrv_WriteByteMask(REG_163080, 0x00, 0x0C); //disable CPU write

#else //XIU
            MDrv_WriteByteMask(REG_163080, MASKBIT(3:2)| BIT0, MASKBIT(3:2)| BIT0); // REG_COMBO_GP_40[0][2][3]: enable CPU write SRAM by XIU

            //MDrv_Write2ByteMask(REG_162E00, 0, MASKBIT(9:0)); // REG_COMBO_HDCP_00[9:0]: address

            for(ustemp = 0; ustemp < COMBO_HDCP_BKSV_SIZE; ustemp++)
            {
                MDrv_WriteByteMask(REG_162E02, pBKSV[ustemp], 0xFF); // REG_COMBO_HDCP_01[7:0]: the data for CPU write into HDCP KEY SRAM through XIU
            }

            for(ustemp = 0; ustemp < COMBO_HDCP_KEY_SIZE; ustemp++)
            {
                MDrv_WriteByteMask(REG_162E02, pHDCPKey[ustemp], 0xFF); // REG_COMBO_HDCP_01[7:0]: the data for CPU write into HDCP KEY SRAM through XIU
            }

            MDrv_WriteByteMask(REG_163080, 0x00, MASKBIT(3:2) |BIT0); // REG_COMBO_GP_40[0][2][3]: disable CPU write SRAM by XIU

#endif

            bKeyFlag = TRUE;
        }
    }

    // Load Bksv and Bcaps
    if(pBKSV != NULL)
    {
        switch(ucPortSelect)
        {
            case COMBO_INPUT_SELECT_PORT0:
                MDrv_WriteByteMask(REG_10062F, BIT2, BIT2); // REG_COMBO_DVI_HDCP_P0_17[10]: HDCP enable for DDC
                // 74 write enable
                MDrv_WriteByteMask(REG_100633, BIT7, MASKBIT(7:6)); // REG_COMBO_DVI_HDCP_P0_19[14][15]

                for(ustemp = 0; ustemp < COMBO_HDCP_BKSV_SIZE; ustemp++)
                {
                    // 74 address: 0x00
                    MDrv_Write2ByteMask(REG_10062E, ustemp, MASKBIT(9:0)); // REG_COMBO_DVI_HDCP_P0_17[9:0]: CPU r/w address (for hdcp_key_sram/74reg)
                    // bksv
                    MDrv_WriteByte(REG_100630, pBKSV[ustemp]); // REG_COMBO_DVI_HDCP_P0_18[7:0]:CPU write data port (for hdcp_key_sram/74reg)
                    MDrv_WriteByteMask(REG_100632, BIT5, BIT5); // REG_COMBO_DVI_HDCP_P0_19[5]: HDCP address load pulse generate
            	    MDrv_WriteByteMask(REG_100632, BIT4, BIT4); // REG_COMBO_DVI_HDCP_P0_19[4]: HDCP data write port pulse generate
                }
                // 74 address: 0x40
                MDrv_Write2ByteMask(REG_10062E, 0x40, MASKBIT(9:0)); // REG_COMBO_DVI_HDCP_P0_17[9:0]: CPU r/w address (for hdcp_key_sram/74reg)
                // bcaps
                MDrv_WriteByte(REG_100630, ucBcaps); // REG_COMBO_DVI_HDCP_P0_18[7:0]:CPU write data port (for hdcp_key_sram/74reg)
                MDrv_WriteByteMask(REG_100632, BIT5, BIT5); // REG_COMBO_DVI_HDCP_P0_19[5]: HDCP address load pulse generate
            	MDrv_WriteByteMask(REG_100632, BIT4, BIT4); // REG_COMBO_DVI_HDCP_P0_19[4]: HDCP data write port pulse generate

                // 74 write disable
                MDrv_WriteByteMask(REG_100633, 0, MASKBIT(7:6)); // REG_COMBO_DVI_HDCP_P0_19[14][15]
                //enable HDCP
                MDrv_Write2Byte(REG_100600, 0x0721); // REG_COMBO_DVI_HDCP_P0_00[5]: enable HDCP
    			break;

            case COMBO_INPUT_SELECT_PORT1:
                MDrv_WriteByteMask(REG_100B2F, BIT2, BIT2); // REG_COMBO_DVI_HDCP_P1_17[10]: HDCP enable for DDC
                // 74 write enable
                MDrv_WriteByteMask(REG_100B33, BIT7, MASKBIT(7:6)); // REG_COMBO_DVI_HDCP_P1_19[14][15]

                for(ustemp = 0; ustemp < COMBO_HDCP_BKSV_SIZE; ustemp++)
                {
                    // 74 address: 0x00
                    MDrv_Write2ByteMask(REG_100B2E, ustemp, MASKBIT(9:0)); // REG_COMBO_DVI_HDCP_P1_17[9:0]: CPU r/w address (for hdcp_key_sram/74reg)
                    // bksv
                    MDrv_WriteByte(REG_100B30, pBKSV[ustemp]); // REG_COMBO_DVI_HDCP_P1_18[7:0]:CPU write data port (for hdcp_key_sram/74reg)
                    MDrv_WriteByteMask(REG_100B32, BIT5, BIT5); // REG_COMBO_DVI_HDCP_P1_19[5]: HDCP address load pulse generate
            	    MDrv_WriteByteMask(REG_100B32, BIT4, BIT4); // REG_COMBO_DVI_HDCP_P1_19[4]: HDCP data write port pulse generate
                }
                // 74 address: 0x40
                MDrv_Write2ByteMask(REG_100B2E, 0x40, MASKBIT(9:0)); // REG_COMBO_DVI_HDCP_P1_17[9:0]: CPU r/w address (for hdcp_key_sram/74reg)
                // bcaps
                MDrv_WriteByte(REG_100B30, ucBcaps); // REG_COMBO_DVI_HDCP_P1_18[7:0]:CPU write data port (for hdcp_key_sram/74reg)
                MDrv_WriteByteMask(REG_100B32, BIT5, BIT5); // REG_COMBO_DVI_HDCP_P1_19[5]: HDCP address load pulse generate
            	MDrv_WriteByteMask(REG_100B32, BIT4, BIT4); // REG_COMBO_DVI_HDCP_P1_19[4]: HDCP data write port pulse generate

                // 74 write disable
                MDrv_WriteByteMask(REG_100B33, 0, MASKBIT(7:6)); // REG_COMBO_DVI_HDCP_P1_19[14][15]
                //enable HDCP
                MDrv_Write2Byte(REG_100B00, 0x0721); // REG_COMBO_DVI_HDCP_P1_00[5]: enable HDCP
    			break;

            case COMBO_INPUT_SELECT_PORT2:
            case COMBO_INPUT_SELECT_PORT3:
                if(bP2LoadKey == FALSE)
                {
                    MDrv_WriteByteMask(REG_16102F, BIT2, BIT2); // REG_COMBO_DVI_HDCP_DUAL_17[10]: HDCP enable for DDC
                    // 74 write enable
                    MDrv_WriteByteMask(REG_161033, BIT7, MASKBIT(7:6)); // REG_COMBO_DVI_HDCP_DUAL_19[14][15]

                    for(ustemp = 0; ustemp < COMBO_HDCP_BKSV_SIZE; ustemp++)
                    {
                        // 74 address: 0x00
                        MDrv_Write2ByteMask(REG_16102E, ustemp, MASKBIT(9:0)); // REG_COMBO_DVI_HDCP_DUAL_17[9:0]: CPU r/w address (for hdcp_key_sram/74reg)
                        // bksv
                        MDrv_WriteByte(REG_161030, pBKSV[ustemp]); // REG_COMBO_DVI_HDCP_DUAL_18[7:0]:CPU write data port (for hdcp_key_sram/74reg)
                        MDrv_WriteByteMask(REG_161032, BIT5, BIT5); // REG_COMBO_DVI_HDCP_DUAL_19[5]: HDCP address load pulse generate
            	        MDrv_WriteByteMask(REG_161032, BIT4, BIT4); // REG_COMBO_DVI_HDCP_DUAL_19[4]: HDCP data write port pulse generate
                    }
                    // 74 address: 0x40
                    MDrv_Write2ByteMask(REG_16102E, 0x40, MASKBIT(9:0)); // REG_COMBO_DVI_HDCP_DUAL_17[9:0]: CPU r/w address (for hdcp_key_sram/74reg)
                    // bcaps
                    MDrv_WriteByte(REG_161030, ucBcaps); // REG_COMBO_DVI_HDCP_DUAL_18[7:0]:CPU write data port (for hdcp_key_sram/74reg)
                    MDrv_WriteByteMask(REG_161032, BIT5, BIT5); // REG_COMBO_DVI_HDCP_DUAL_19[5]: HDCP address load pulse generate
            	    MDrv_WriteByteMask(REG_161032, BIT4, BIT4); // REG_COMBO_DVI_HDCP_DUAL_19[4]: HDCP data write port pulse generate

                    // 74 write disable
                    MDrv_WriteByteMask(REG_161033, 0, MASKBIT(7:6)); // REG_COMBO_DVI_HDCP_DUAL_19[14][15]
                    //enable HDCP
                    MDrv_Write2Byte(REG_161000, 0x0721); // REG_COMBO_DVI_HDCP_DUAL_00[5]: enable HDCP
                    bP2LoadKey = TRUE;
                }

                break;

            case COMBO_INPUT_SELECT_PORT4:
                if(bDPInput)
                {
            		MDrv_WriteByteMask(REG_163080, MASKBIT(3:2), MASKBIT(3:2)); // REG_COMBO_GP_40[2][3]:

            		for(ustemp = 0; ustemp < COMBO_HDCP_BKSV_SIZE; ustemp++)
            		{
            			MDrv_Write2ByteMask(REG_163082, ustemp, MASKBIT(9:0)); // REG_COMBO_GP_41[9:0]: CPU r/w address (for hdcp_key_sram/74reg)
            			MDrv_WriteByte(REG_163084, pBKSV[ustemp]); // REG_COMBO_GP_42[7:0]: CPU write data port (for hdcp_key_sram/74reg)
                        // Aux PM
            			MDrv_WriteByte(REG_0011A0, pBKSV[ustemp]);
            			Delay1ms(5);
            			MDrv_WriteByteMask(REG_163080, BIT4, BIT4); // REG_COMBO_GP_40[4]: HDCP address load pulse generate
            			Delay1ms(5);
            			MDrv_WriteByteMask(REG_163080, BIT5, BIT5); // REG_COMBO_GP_40[5]: HDCP data read port pulse generate
            			Delay1ms(5);
            		}

                    MDrv_WriteByteMask(REG_163080, 0, MASKBIT(3:2)); // REG_COMBO_GP_40[2][3]:
                }

    			break;

            default:

                break;
        };
    }
}

//**************************************************************************
//  [Function Name]:
//                  mhal_combo_ClockEnable()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mhal_combo_ClockEnable(BYTE ucPortSelect, Bool bMainSwitch)
{
    if(bMainSwitch)
    {
        MDrv_Write2Byte(REG_163006, 0xFFFF); // REG_COMBO_GP_TOP_03[15:0]: Misc clock enable
    	MDrv_Write2Byte(REG_163008, 0x3FFF); // REG_COMBO_GP_TOP_04[13:0]: Misc clock enable

        MDrv_Write2Byte(REG_100EEE, 0x1FF); // REG_COMBO_GP_TOP_77[8:0]: Clk to scaler

        msEread_Init(&usComboIDIndex, &ucComboVersionIndex);
    }

    switch(ucPortSelect)
    {
        case COMBO_INPUT_SELECT_PORT0:
            MDrv_Write2Byte(REG_163022, 0xFFFF); // REG_COMBO_GP_TOP_11[15:0]: Clock enable port0
			break;

        case COMBO_INPUT_SELECT_PORT1:
		    MDrv_Write2Byte(REG_163042, 0xFFFF); // REG_COMBO_GP_TOP_21[15:0]: Clock enable port1
			break;

        case COMBO_INPUT_SELECT_PORT2:
        case COMBO_INPUT_SELECT_PORT3:
		    MDrv_Write2Byte(REG_163062, 0xFFFF); // REG_COMBO_GP_TOP_31[15:0]: Clock enable port2
			break;

        default:

            break;
    }
}

//**************************************************************************
//  [Function Name]:
//                  mhal_combo_AudioInitial()
//  [Description]
//                  initial audio common settings
//  [Arguments]:
//                  none
//  [Return]:
//                  none
//**************************************************************************
void mhal_combo_AudioInitial(void)
{
    MDrv_WriteByteMask(REG_1630B2, 0x00, 0x3F); // REG_COMBO_GP_TOP_59[3:0]: i2s 0~7 out OEN, [4]:spdif out OEN, [5]: i2s out mute OEN

    //I2S setting
    MDrv_WriteByteMask(REG_163002, 0x10, 0x10); // [4]: reg_i2s_mclk_192fs_sel: 192f2(MHL/HDMI only)
    MDrv_WriteByteMask(REG_1630A1, BIT2, BIT3|BIT2); // 01: 24 bits
    MDrv_WriteByteMask(REG_1630A4, 0, BIT2); // I2S-Justified
    MDrv_WriteByteMask(REG_16300B, BIT7, BIT7); //  [15]: i2s bck inv

    // Gain
    MDrv_WriteByte(REG_1630A5, 0xC0); // REG_COMBO_GP_TOP_52[15:8]: 0xC0 is 0 dB, default 0x00 is mute will cause i2s out data fade out

    // Formula:  ( 12Mhz * 2^km * fbdiv ) / (2^kn * 2^kp * ddiv)
    MDrv_WriteByte(REG_162F12, 0x22); // REG_COMBO_PLL_TOP_09[7:4]: reg_apll_km_reg, [3:0]:reg_apll_divkp_reg
    MDrv_WriteByteMask(REG_162F13, 0x00, 0x60); // REG_COMBO_PLL_TOP_09[14:13]: reg_apll_kn_reg
    MDrv_WriteByte(REG_162F15, 0x62); // REG_COMBO_PLL_TOP_0A[11:8]:reg_aupll_ddiv, [7:4]:reg_aupll_fbdiv
    MDrv_WriteByteMask(REG_162F07, 0x00, 0x01); // REG_COMBO_PLL_TOP_03[8]: turn off power down
    MDrv_WriteByte(REG_162F0E, 0x50); // REG_COMBO_PLL_TOP_07[15:0]: makes apll lock

    // Setting for HDMI CTS
    MDrv_WriteByteMask(REG_162F30, BIT7, BIT7); // REG_COMBO_PLL_TOP_18[7]: enable Audio HDMI CTS-N synthesizer
    MDrv_WriteByteMask(REG_162F40, 0, MASKBIT(1:0)); // REG_COMBO_PLL_TOP_20[0]: APLL synthesizer DIN, FBIN input select, [1]: APLL input control and clock source select

    // Setting for DP only
    MDrv_WriteByteMask(REG_162F06, 0, BIT0); // REG_COMBO_PLL_TOP_03[0]: APLL input divider select from synthesizer

    // Fading setting
#if ENABLE_AUDIO_AUTO_FADING
    MDrv_WriteByteMask(REG_1630A0, 0x08, 0x0C); // REG_COMBO_GP_TOP_50[3:2]: reg_fading_mode, 10: automatic fading mode
#endif
    MDrv_WriteByteMask(REG_163093, 0x0C, 0x0C); // REG_COMBO_GP_TOP_49[11:10]: reg_fad_speed_sel, lfading speed select, 11: 8X
    MDrv_Write2Byte(REG_16308C, 0xFFFF); // REG_COMBO_GP_TOP_46[15:0]: zero-crossing threshold
}

//**************************************************************************
//  [Function Name]:
//                  mhal_combo_ClockRtermControl()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mhal_combo_ClockRtermControl(BYTE ucPortSelect, Bool bRtermEnable)
{
    if(ucComboVersionIndex > 0)
    {
        switch(ucPortSelect)
        {
            case COMBO_INPUT_SELECT_PORT0:
                MDrv_WriteByteMask(REG_001724, bRtermEnable? 0: BIT7, BIT7); // REG_PM_BANK_12[7]: Power control P0 clock r-term
    			break;

            case COMBO_INPUT_SELECT_PORT1:
    		    MDrv_WriteByteMask(REG_001726, bRtermEnable? 0: BIT7, BIT7); // REG_PM_BANK_13[7]: Power control P1 clock r-term
    			break;

            case COMBO_INPUT_SELECT_PORT2:
    		    MDrv_WriteByteMask(REG_001720, bRtermEnable? 0: BIT3, BIT3); // REG_PM_BANK_10[3]: Power control P2 clock r-term
    			break;

            case COMBO_INPUT_SELECT_PORT3:
    		    MDrv_WriteByteMask(REG_001722, bRtermEnable? 0: BIT3, BIT3); // REG_PM_BANK_11[3]: Power control P3 clock r-term
    			break;

            case COMBO_INPUT_SELECT_PORT4:
    		    //MDrv_WriteByteMask(REG_001781, bRtermEnable? 0: BIT4, BIT4); // REG_PM_BANK_40[12]: Power control P1 clock r-term
    			break;

            default:

                break;
        };
    }
    else
    {
        switch(ucPortSelect)
        {
            case COMBO_INPUT_SELECT_PORT0:
                MDrv_WriteByteMask(REG_001724, bRtermEnable? 0: BIT7, BIT7); // REG_PM_BANK_12[7]: Power control P0 clock r-term
    			break;

            case COMBO_INPUT_SELECT_PORT1:
    		    MDrv_WriteByteMask(REG_001726, bRtermEnable? 0: BIT7, BIT7); // REG_PM_BANK_13[7]: Power control P1 clock r-term
    			break;

            case COMBO_INPUT_SELECT_PORT2:
    		    MDrv_WriteByteMask(REG_001720, bRtermEnable? 0: BIT0, BIT0); // REG_PM_BANK_10[0]: Power control P2 clock r-term
    			break;

            case COMBO_INPUT_SELECT_PORT3:
    		    MDrv_WriteByteMask(REG_001722, bRtermEnable? 0: BIT0, BIT0); // REG_PM_BANK_11[0]: Power control P3 clock r-term
    			break;

            case COMBO_INPUT_SELECT_PORT4:
    		    //MDrv_WriteByteMask(REG_001781, bRtermEnable? 0: BIT4, BIT4); // REG_PM_BANK_40[12]: Power control P1 clock r-term
    			break;

            default:

                break;
        };
    }
}

//**************************************************************************
//  [Function Name]:
//                  mhal_combo_DataRtermControl()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mhal_combo_DataRtermControl(BYTE ucPortSelect, Bool bRtermEnable)
{
    if(ucComboVersionIndex > 0)
    {
        switch(ucPortSelect)
        {
            case COMBO_INPUT_SELECT_PORT0:
                MDrv_WriteByteMask(REG_112107, bRtermEnable? 0: MASKBIT(2:1), MASKBIT(2:1)); // REG_COMBO_PHY1_03[10:9], Power on port0 data rterm.
                MDrv_WriteByteMask(REG_001724, bRtermEnable? 0: BIT4, BIT4); // REG_PM_BANK_12[4]: Power control P0 data rterm
    			break;

            case COMBO_INPUT_SELECT_PORT1:
                MDrv_WriteByteMask(REG_112307, bRtermEnable? 0: MASKBIT(2:1), MASKBIT(2:1)); // REG_COMBO_PHY3_03[10:9], Power on port1 data rterm.
                MDrv_WriteByteMask(REG_001726, bRtermEnable? 0: BIT4, BIT4); // REG_PM_BANK_13[4]: Power control P1 data rterm
    			break;

            case COMBO_INPUT_SELECT_PORT2:
                MDrv_WriteByteMask(REG_001720, bRtermEnable? 0: MASKBIT(2:0), MASKBIT(2:0)); // REG_PM_BANK_10[2:0], Power control port2 data rterm.
    			break;

            case COMBO_INPUT_SELECT_PORT3:
                MDrv_WriteByteMask(REG_001722, bRtermEnable? 0: MASKBIT(2:0), MASKBIT(2:0)); // REG_PM_BANK_11[2:0], Power control port3 data rterm.
    			break;

            case COMBO_INPUT_SELECT_PORT4:
                //MDrv_WriteByteMask(REG_0017A2, bRtermEnable? 0: MASKBIT(7:4), MASKBIT(7:4)); // REG_PM_BANK_51[7:4], Power control port4 data rterm.
    			break;

            default:

                break;
        };
    }
    else
    {
        switch(ucPortSelect)
        {
            case COMBO_INPUT_SELECT_PORT0:
                MDrv_WriteByteMask(REG_112107, bRtermEnable? 0: MASKBIT(2:0), MASKBIT(2:0)); // REG_COMBO_PHY1_03[10:8], Power on port0 rterm.
                break;

            case COMBO_INPUT_SELECT_PORT1:
                MDrv_WriteByteMask(REG_112307, bRtermEnable? 0: MASKBIT(2:0), MASKBIT(2:0)); // REG_COMBO_PHY3_03[10:8], Power on port1 rterm.
                break;

            case COMBO_INPUT_SELECT_PORT2:
                MDrv_WriteByteMask(REG_001720, bRtermEnable? 0: MASKBIT(2:0), MASKBIT(2:0)); // REG_PM_BANK_10[2:0], Power control port2 data rterm.
    			break;

            case COMBO_INPUT_SELECT_PORT3:
                MDrv_WriteByteMask(REG_001722, bRtermEnable? 0: MASKBIT(2:0), MASKBIT(2:0)); // REG_PM_BANK_11[2:0], Power control port3 data rterm.
    			break;

            case COMBO_INPUT_SELECT_PORT4:
                //MDrv_WriteByteMask(REG_0017A2, bRtermEnable? 0: MASKBIT(7:4), MASKBIT(7:4)); // REG_PM_BANK_51[7:4], Power control port4 data rterm.
    			break;

            default:

                break;
        };
    }
}

//**************************************************************************
//  [Function Name]:
//                  mhal_combo_DoSWReset()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mhal_combo_DoSWReset(BYTE ucPortSelect, DWORD ulSWResetValue)
{
    WORD usSWResetValueL = ulSWResetValue;
    WORD usSWResetValueH = (ulSWResetValue >> 16);

    switch(ucPortSelect)
    {
        case COMBO_INPUT_SELECT_PORT0:
            if(usSWResetValueL > 0)
            {
                MDrv_Write2Byte(REG_11201C, usSWResetValueL); // REG_COMBO_PHY0_0E[15:0]: SW reset
                MDrv_Write2Byte(REG_11201C, 0); // REG_COMBO_PHY0_0E[15:0]: SW reset
            }

            if(usSWResetValueH > 0)
            {
                MDrv_WriteByteMask(REG_11201E, usSWResetValueH, MASKBIT(1:0)); // REG_COMBO_PHY0_0F[1:0]: SW reset
                MDrv_WriteByteMask(REG_11201E, 0, MASKBIT(1:0)); // REG_COMBO_PHY0_0F[1:0]: SW reset
            }

			break;

        case COMBO_INPUT_SELECT_PORT1:
            if(usSWResetValueL > 0)
            {
                MDrv_Write2Byte(REG_11221C, usSWResetValueL); // REG_COMBO_PHY2_0E[15:0]: SW reset
                MDrv_Write2Byte(REG_11221C, 0); // REG_COMBO_PHY2_0E[15:0]: SW reset
            }

            if(usSWResetValueH > 0)
            {
                MDrv_WriteByteMask(REG_11221E, usSWResetValueH, MASKBIT(1:0)); // REG_COMBO_PHY2_0F[1:0]: SW reset
                MDrv_WriteByteMask(REG_11221E, 0, MASKBIT(1:0)); // REG_COMBO_PHY2_0F[1:0]: SW reset
            }

			break;

        case COMBO_INPUT_SELECT_PORT2:
        case COMBO_INPUT_SELECT_PORT3:
            if(usSWResetValueL > 0)
            {
                MDrv_Write2Byte(REG_11241C, usSWResetValueL); // REG_COMBO_PHY4_0E[15:0]: SW reset
                MDrv_Write2Byte(REG_11241C, 0); // REG_COMBO_PHY4_0E[15:0]: SW reset
            }

            if(usSWResetValueH > 0)
            {
                MDrv_WriteByteMask(REG_11241E, usSWResetValueH, MASKBIT(1:0)); // REG_COMBO_PHY4_0F[1:0]: SW reset
                MDrv_WriteByteMask(REG_11241E, 0, MASKBIT(1:0)); // REG_COMBO_PHY4_0F[1:0]: SW reset
            }

			break;

        case COMBO_INPUT_SELECT_PORT4:
            if(usSWResetValueL > 0)
            {
                //MDrv_Write2Byte(REG_162452, usSWResetValueL); // REG_COMBO_ATOP4_29[15:0]: SW reset
                //MDrv_Write2Byte(REG_162452, 0); // REG_COMBO_ATOP4_29[15:0]: SW reset
            }

            if(usSWResetValueH > 0)
            {
                //MDrv_WriteByteMask(REG_162454, usSWResetValueH, MASKBIT(1:0)); // REG_COMBO_ATOP4_2A[1:0]: SW reset
                //MDrv_WriteByteMask(REG_162454, 0, MASKBIT(1:0)); // REG_COMBO_ATOP4_2A[1:0]: SW reset
            }

			break;

        default:

            break;
    };
}

//**************************************************************************
//  [Function Name]:
//                  mhal_combo_ConfigAudioSource()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mhal_combo_ConfigAudioSource(Bool bIsTMDS, BYTE ucPortSelect, BYTE ucHBR2Select)
{
    BYTE ucClockSelect = 0;
    BYTE ucSourceSelect = 0;

    switch(ucPortSelect)
    {
        case COMBO_INPUT_SELECT_PORT0:
            ucClockSelect = 0;
            ucSourceSelect = 0;
			break;

        case COMBO_INPUT_SELECT_PORT1:
            ucClockSelect = 1;
            ucSourceSelect = 1;
			break;

        case COMBO_INPUT_SELECT_PORT2:
        case COMBO_INPUT_SELECT_PORT3:
            ucClockSelect = 2;
            ucSourceSelect = 2;
			break;

        case COMBO_INPUT_SELECT_PORT4:
            ucClockSelect = 4;
            ucSourceSelect = 12;
			break;

        default:

            break;
    };

    // Audio clock select
    MDrv_WriteByteMask(REG_163004, (ucClockSelect <<4), MASKBIT(6:4)); // REG_COMBO_GP_TOP_02[6:4]: audio engine clock select

    // Audio source select
    MDrv_WriteByteMask(REG_163088, ucSourceSelect, 0x0F); // REG_COMBO_GP_TOP_44[3:0]: audio engine source select

    if(bIsTMDS)
    {
        ucHBR2Select = 0;
    }
}

//**************************************************************************
//  [Function Name]:
//                  mhal_combo_ConfigAPLLSynthesizer()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mhal_combo_ConfigAPLLSynthesizer(Bool bIsTMDS, BYTE ucPortSelect, BYTE ucHBR2Select)
{
    BYTE ucSourceSelect = 0;

    if(bIsTMDS == TRUE)
    {
        MDrv_WriteByteMask(REG_162F41, 0, BIT0); // REG_COMBO_PLL_TOP_20[8]: disable APLL VCO frequency x2
        MDrv_WriteByteMask(REG_162F40, 0, BIT0| BIT1); // REG_COMBO_PLL_TOP_20[1:0]: APLL synthesizer DIN and FBIN input select, APLL input control and clock source select
        MDrv_WriteByteMask(REG_162F22, 0, BIT5); // REG_COMBO_PLL_TOP_11[5]: Step override enable
    }
    else //DP
    {
        if(ucHBR2Select != COMBO_DP_HBR2_ENGINE_NONE)
        {

        }

        MDrv_WriteByteMask(REG_162F40, BIT0| BIT1, BIT0| BIT1); // REG_COMBO_PLL_TOP_20[1:0]: APLL synthesizer DIN and FBIN input select, APLL input control and clock source select
    }

    switch(ucPortSelect)
    {
        case COMBO_INPUT_SELECT_PORT0:
            ucSourceSelect = 0;
			break;

        case COMBO_INPUT_SELECT_PORT1:
            ucSourceSelect = 1;
			break;

        case COMBO_INPUT_SELECT_PORT2:
        case COMBO_INPUT_SELECT_PORT3:
            ucSourceSelect = 2;
			break;

        case COMBO_INPUT_SELECT_PORT4:
            ucSourceSelect = 14;
			break;

        default:

            break;
    };

    MDrv_WriteByteMask(REG_162F40, (ucSourceSelect <<4), 0xF0); // REG_COMBO_PLL_TOP_20[7:4]: APLL clock source select
}

//**************************************************************************
//  [Function Name]:
//                  mhal_combo_ConfigFadingEvent()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mhal_combo_ConfigFadingEvent(Bool bEnable, BYTE ucEvents)
{
    MDrv_WriteByte(REG_16308E, bEnable? ucEvents: 0); // REG_COMBO_GP_TOP_47[7:0]: Enable HDMI/DP mute events to trigger fading out
    //[0]: HDMI CTS/N over range / DP audio sample error
    //[1]: HDMI TMDS clock big change / DP audio sample parity error
    //[2]: HDMI AVMUTE / DP non-PCM
    //[3]: HDMI no input clock / DP audio mute (VB_ID[4])
    //[5]: HDMI audio channel status change / DP no input recovery clock
    //[7]: HDMI audio sample error / DP audio FIFO error
}

//**************************************************************************
//  [Function Name]:
//                  mhal_combo_ConfigMuteEvent()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mhal_combo_ConfigMuteEvent(Bool bEnable, BYTE ucEvents)
{
    MDrv_WriteByte(REG_16308B, bEnable? ucEvents: 0); // REG_COMBO_GP_TOP_45[7:0]: Audio mute pin mute event enable
    //[0]: HDMI CTS/N over range / DP audio sample error
    //[1]: HDMI TMDS clock big change / DP audio sample parity error
    //[2]: HDMI AVMUTE / DP non-PCM
    //[3]: HDMI no input clock / DP audio mute (VB_ID[4])
    //[5]: HDMI audio channel status change / DP no input recovery clock
    //[7]: HDMI audio sample error / DP audio FIFO error
}

//**************************************************************************
//  [Function Name]:
//                  mhal_combo_ConfigGlobalMute()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mhal_combo_ConfigGlobalMute(Bool bEnable)
{
    MDrv_WriteByteMask(REG_163088, bEnable? BIT4: 0, BIT4); // REG_COMBO_GP_TOP_44[4]: Audio global mute
}

//**************************************************************************
//  [Function Name]:
//                  mhal_combo_GetDVIDualMainPort()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
BYTE mhal_combo_GetDVIDualMainPort(BYTE ucPortSelect)
{
    if(ucPortSelect %2) // Port 1/3/5
    {
        ucPortSelect = ucPortSelect -1;
    }
    else // Port 0/2/4
    {
        ucPortSelect = ucPortSelect +1;
    }

    return ucPortSelect;
}
#endif

#if(COMBO_HDCP2_FUNCTION_SUPPORT)
void Hal_HDCP22_PortInitial(U8 u8PortIdx)
{
    MS_U32 dwBKOffset = 0x300 * u8PortIdx;

    printf("[HDCP22] PortInit(), port idx = %d\r\n", u8PortIdx);

    //MDrv_WriteByteMask(REG_COMBO_GP_TOP_40_L, 0x05, 0x07); // [2]: Enable CPU write; [1]: disable SRAM read; [0]: enable xiu2hdcpkey

    //wirte 74Ram for HDCP22 version
    MDrv_WriteByteMask(REG_10062F + dwBKOffset, BIT2, BIT2); //HDCP enalbe for DDC
    MDrv_WriteByteMask(REG_100633 + dwBKOffset, BIT7, BMASK(7:6)); //write enable

    MDrv_Write2ByteMask(REG_10062E + dwBKOffset, 0x50, BMASK(9:0)); //CPU r/w address
    MDrv_WriteByteMask(REG_100632 + dwBKOffset, BIT5, BIT5); //HDCP load address pulse

    MDrv_WriteByte(REG_100630 + dwBKOffset, 0x04); //bit2: HDCP22 version
    MDrv_WriteByteMask(REG_100632 + dwBKOffset, BIT4, BIT4); //HDCP data write port pulse generate

    //clear RxStatus
    MDrv_WriteByte(REG_1006C6 + dwBKOffset, 0x00);
    MDrv_WriteByteMask(REG_1006C9 + dwBKOffset, BIT7, BIT7);
    //HDCP 2.2 or HDCP 1.4
    //[1] Enable auto-clear SKE status when receiving ake_init
    //[2] Enable auto-clear SKE status when no hdcp22 capability
    MDrv_WriteByteMask(REG_10069C + dwBKOffset, 0x06, 0x06);     //this code is not include in macan utpa

    //clear hdcp_enable cipher bit
    //W2BYTEMSK(REG_HDCP_DUAL_P0_4E_L + dwBKOffset, 0, BIT(0)); //macan driver layer disable this code

    //clear xiu status
    //MDrv_Write2Byte(REG_1006CC + dwBKOffset, 0x3D); //  ck3 flow have something differend
    //MDrv_Write2Byte(REG_1006CC + dwBKOffset, 0x00); //  ck3 flow have something differend

    //Enable write offset   //macan driver layer disable this code
    //MDrv_Write2ByteMask(REG_1006D0 +dwBKOffset, BIT(15)| (130), BIT15| BMASK(9:0)); //b'[0..9]offset; b'[15]: enable bit
}
//**************************************************************************
//  [Function Name]:
//                  mhal_combo_HDCP2Initial()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mhal_combo_HDCP2Initial(void)
{
    static MS_BOOL bInitDone = FALSE;

    if ( bInitDone == FALSE)  // daniel@ temp solution
    {
        bInitDone = TRUE;
        //printf("wilson test  xxx\r\n");
        MDrv_WriteByteMask(REG_100E62, 0x00, 0xFF); //enable clk    //for mazda , don't know what is this
#if ((CHIP_FAMILY_TYPE==CHIP_FAMILY_MAYA)||(CHIP_FAMILY_TYPE==CHIP_FAMILY_MAZDA))
        MDrv_WriteByteMask(REG_100E80, 0x05, 0x07); //enable xiu
#else
        // whisky@
        //MDrv_WriteRegBit(0x110ac0+0x19*2, BIT1, BIT1); //enable xiu  [0]
        //MDrv_WriteRegBit(0x110ac0+0x00*2, 0, BIT1); //enable xiu  [1]
        //MDrv_WriteRegBit(0x110ac0+0x19*2+1, BIT7, BIT7); //enable xiu  [2]

        //0x1739   0x40 bit[2]  1iA3¡Li  0x110a    0x19  bit[15]
        MDrv_Write2Byte(0x110af2, 0x8802);
        MDrv_Write2Byte(0x110ac0, 0x0020);
#endif
#if (CHIP_FAMILY_TYPE==CHIP_FAMILY_MAZDA)
        Hal_HDCP22_PortInitial(0);     //HDMI p0
        Hal_HDCP22_PortInitial(1);     //HDMI p1
        Hal_HDCP22_PortInitial(2);     //HDMI p2
        Hal_HDCP22_PortInitial(3);     //HDMI p3
#else
        // HDMI 2.0 Port0
        //tmp: wilson test; write 74ram for HDCP22 version
        MDrv_WriteByteMask(REG_10062F, BIT2, BIT2); //HDCP enable for DDC
        MDrv_WriteByteMask(REG_100633, BIT7, MASKBIT(7:6)); //write enable


        MDrv_Write2ByteMask(REG_10062E, 0x50, MASKBIT(9:0)); //CPU r/w address (for hdcp_key_sram/74reg)
        MDrv_WriteByteMask(REG_100632, BIT5, BIT5); //HDCP address load pulse generate

        printf("@@@ %x \n", MDrv_ReadByte(REG_100630));
        MDrv_WriteByte(REG_100630, 0x04); //bit2: HDCP22 version
        printf("@@@ %x \n", MDrv_ReadByte(REG_100630));
        MDrv_WriteByteMask(REG_100632, BIT4, BIT4); // REG_COMBO_DVI_HDCP_DUAL_19[4]: HDCP data write port pulse generate

        //clear RxStatus wirte msg length
        MDrv_WriteByte(REG_1006C6, 0x00);//RIU[REG_1006C6] = 0x00;
        MDrv_WriteByteMask(REG_1006C9, BIT7, BIT7);

        //HDCP 2.2 or HDCP 1.4
        //[1] Enable auto-clear SKE status when receiving ake_init
        //[2] Enable auto-clear SKE status when no hdcp22 capability
        MDrv_WriteByteMask(REG_10069C, 0x06, 0x06);
#endif
    }
}

//**************************************************************************
//  [Function Name]:
//                  mhal_combo_HDCP2GetReadDownFlag()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
Bool mhal_combo_HDCP2GetReadDownFlag(BYTE ucPortSelect)
{
    Bool bReadDownFlag = FALSE;

    switch(ucPortSelect)
    {
        case COMBO_INPUT_SELECT_PORT0:
            bReadDownFlag = ((MDrv_ReadByte(REG_1006CC) & BIT3) ? TRUE : FALSE); // REG_HDCP_P0_66[3]: Read down flag

            if(bReadDownFlag)
            {
                MDrv_WriteByteMask(REG_1006CC, BIT3, BIT3); // REG_HDCP_P0_66[3]: Clear read down flag
            }

            break;

        case COMBO_INPUT_SELECT_PORT1:
            bReadDownFlag = ((MDrv_ReadByte(REG_1006CC + 0x300) & BIT3) ? TRUE : FALSE); // REG_HDCP_P1_66[3]: Read down flag

            if(bReadDownFlag)
            {
                MDrv_WriteByteMask(REG_1006CC + 0x300, BIT3, BIT3);
            }

            break;
        case COMBO_INPUT_SELECT_PORT2:
            bReadDownFlag = ((MDrv_ReadByte(REG_1006CC + 0x600) & BIT3) ? TRUE : FALSE); // REG_HDCP_P1_66[3]: Read down flag

            if(bReadDownFlag)
            {
                MDrv_WriteByteMask(REG_1006CC + 0x600, BIT3, BIT3);
            }

            break;
        case COMBO_INPUT_SELECT_PORT3:
            bReadDownFlag = ((MDrv_ReadByte(REG_1006CC + 0x900) & BIT3) ? TRUE : FALSE); // REG_HDCP_P1_66[3]: Read down flag

            if(bReadDownFlag)
            {
                MDrv_WriteByteMask(REG_1006CC + 0x900, BIT3, BIT3);
            }

            break;
        default:

            break;
    };

    return bReadDownFlag;
}

#endif

#endif


