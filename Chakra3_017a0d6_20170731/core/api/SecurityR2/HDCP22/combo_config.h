///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   Combo_config.h
/// @author MStar Semiconductor Inc.
/// @brief  MHL driver Function
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _COMBO_CONFIG_H_
#define _COMBO_CONFIG_H_

//-------------------------------------------------------------------------------------------------
// This chip support 5 digital input
//-------------------------------------------------------------------------------------------------
// Port 0: DVI/ HDMI 1.4/ MHL 2.0
// Port 1: DVI/ HDMI 1.4/ MHL 2.0
// Port 2: HDMI 2.0/ MHL 3.0
// Port 3: HDMI 2.0/ MHL 3.0
// Port 4: DP 1.2(HBR2)
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
#define COMBO_IP_SUPPORT_0PORT          0
#define COMBO_IP_SUPPORT_1PORT          1
#define COMBO_IP_SUPPORT_2PORT          2
#define COMBO_IP_SUPPORT_3PORT          3
#define COMBO_IP_SUPPORT_4PORT          4
#define COMBO_IP_SUPPORT_5PORT          5
#define COMBO_IP_SUPPORT_6PORT          6

// U11 only has 2 HDMI 2.0 ports
#if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA) )
#define COMBO_IP_SUPPORT_TYPE           COMBO_IP_SUPPORT_4PORT//COMBO_IP_SUPPORT_4PORT
#else
#define COMBO_IP_SUPPORT_TYPE           COMBO_IP_SUPPORT_1PORT//COMBO_IP_SUPPORT_5PORT
#endif
// Just for chip bring to force disable some block function
#define COMBO_EDID_BLOCK_ENABLE         1
#define COMBO_HDCP14_BLOCK_ENABLE       1
#define COMBO_AUDIO_BLOCK_ENABLE        1
#define COMBO_ADC_BLOCK_ENABLE          1
#define COMBO_TMDS_BLOCK_ENABLE         1
#define COMBO_MHL_BLOCK_ENABLE          1
#define COMBO_DP_BLOCK_ENABLE           1

// MHL part
#define COMBO_MHL_SUPPORT_PORT0         1
#define COMBO_MHL_SUPPORT_PORT1         1
#define COMBO_MHL_SUPPORT_PORT2         1
#define COMBO_MHL_SUPPORT_PORT3         1
#define COMBO_MHL_SUPPORT_PORT4         0
#define COMBO_MHL_SUPPORT_PORT5         0

#define COMBO_MHL3_SUPPORT_PORT0        0
#define COMBO_MHL3_SUPPORT_PORT1        0
#define COMBO_MHL3_SUPPORT_PORT2        1
#define COMBO_MHL3_SUPPORT_PORT3        1
#define COMBO_MHL3_SUPPORT_PORT4        0
#define COMBO_MHL3_SUPPORT_PORT5        0

#define COMBO_MHL_CTS_MODE_ENABLE       0

// HDCP 2.2
#if (ENABLE_SECU_R2 == 1) && (ENABLE_HDCP22 == 1)
#define COMBO_HDCP2_FUNCTION_SUPPORT    1
//HDCP22 ToDo: Check this
#define COMBO_HDCP2_DECODE_KEY          1//0
#else
#define COMBO_HDCP2_FUNCTION_SUPPORT    0
#endif

#if 0// no DP in U11
// Daisy chain
#define COMBO_DP_DAISY_CHAIN_SUPPORT    ENABLE_DAISY_CHAIN
#define COMBO_DAISY_CHAIN_PORT_SELECT   4

#define COMBO_DP_DC_SUPPORT_PORT0       0
#define COMBO_DP_DC_SUPPORT_PORT1       1
#define COMBO_DP_DC_SUPPORT_PORT2       0
#define COMBO_DP_DC_SUPPORT_PORT3       0
#define COMBO_DP_DC_SUPPORT_PORT4       0
#define COMBO_DP_DC_SUPPORT_PORT5       0
#endif

// HDCP key load from efuse
#define ENABLE_LOAD_KEY_VIA_EFUSE       0

// TMDS use internal EDID
#define COMBO_TMDS_USE_INTERNAL_EDID    0

// EQ
#define COMBO_HDMI14_EQ_VALUE           3
#define COMBO_HDMI_250_340MHZ_EQ_VALUE  0x10
#define COMBO_HDMI_25_250MHZ_EQ_VALUE   0x0C
#define COMBO_HDMI_EQ_VALUE             COMBO_HDMI_25_250MHZ_EQ_VALUE

#define COMBO_DP_EQ_VALUE               3

#define COMBO_HDMI14_CLK_CHANNEL_EQ     COMBO_HDMI14_EQ_VALUE
#define COMBO_HDMI14_B_CHANNEL_EQ       COMBO_HDMI14_EQ_VALUE
#define COMBO_HDMI14_G_CHANNEL_EQ       COMBO_HDMI14_EQ_VALUE
#define COMBO_HDMI14_R_CHANNEL_EQ       COMBO_HDMI14_EQ_VALUE

#define COMBO_HDMI20_CLK_CHANNEL_EQ     COMBO_HDMI_EQ_VALUE
#define COMBO_HDMI20_B_CHANNEL_EQ       COMBO_HDMI_EQ_VALUE
#define COMBO_HDMI20_G_CHANNEL_EQ       COMBO_HDMI_EQ_VALUE
#define COMBO_HDMI20_R_CHANNEL_EQ       COMBO_HDMI_EQ_VALUE

#define COMBO_DP_LANE0_EQ               COMBO_DP_EQ_VALUE
#define COMBO_DP_LANE1_EQ               COMBO_DP_EQ_VALUE
#define COMBO_DP_LANE2_EQ               COMBO_DP_EQ_VALUE
#define COMBO_DP_LANE3_EQ               COMBO_DP_EQ_VALUE

#endif


