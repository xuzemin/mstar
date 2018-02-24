///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   Mdrv_combo.h
/// @author MStar Semiconductor Inc.
/// @brief  MHL driver Function
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _MDRV_COMBO_H_
#define _MDRV_COMBO_H_

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
//#define _BIT(a)                             (BIT0 << (a))
#define MASKBIT(a)                          (_BIT((1?a) +1) -_BIT((0?a)))

enum COMBO_FUNCTION_ENABLE_TYPE
{
    COMBO_FUNCTION_ENABLE_PORT0_FLAG = BIT0,
    COMBO_FUNCTION_ENABLE_PORT1_FLAG = BIT1,
    COMBO_FUNCTION_ENABLE_PORT2_FLAG = BIT2,
    COMBO_FUNCTION_ENABLE_PORT3_FLAG = BIT3,
    COMBO_FUNCTION_ENABLE_PORT4_FLAG = BIT4,
    COMBO_FUNCTION_ENABLE_PORT5_FLAG = BIT5,
    COMBO_FUNCTION_ENABLE_VGA_FLAG = BIT6,
};

#define COMBO_HDCP2_ENCODE_KEY_CHECK_SIZE   32

//-------------------------------------------------------------------------------------------------
//  Macro define
//-------------------------------------------------------------------------------------------------
typedef void (*COMBO_HDCP2_CALL_BACK_FUNC)(BYTE, BYTE, BYTE, BYTE*);

#define GET_COMBO_EDID_ENABLE_PORT0()       (Bool)((ucComboEDIDEnableIndex & COMBO_FUNCTION_ENABLE_PORT0_FLAG) ?TRUE :FALSE)
#define GET_COMBO_EDID_ENABLE_PORT1()       (Bool)((ucComboEDIDEnableIndex & COMBO_FUNCTION_ENABLE_PORT1_FLAG) ?TRUE :FALSE)
#define GET_COMBO_EDID_ENABLE_PORT2()       (Bool)((ucComboEDIDEnableIndex & COMBO_FUNCTION_ENABLE_PORT2_FLAG) ?TRUE :FALSE)
#define GET_COMBO_EDID_ENABLE_PORT3()       (Bool)((ucComboEDIDEnableIndex & COMBO_FUNCTION_ENABLE_PORT3_FLAG) ?TRUE :FALSE)
#define GET_COMBO_EDID_ENABLE_PORT4()       (Bool)((ucComboEDIDEnableIndex & COMBO_FUNCTION_ENABLE_PORT4_FLAG) ?TRUE :FALSE)
#define GET_COMBO_EDID_ENABLE_PORT5()       (Bool)((ucComboEDIDEnableIndex & COMBO_FUNCTION_ENABLE_PORT5_FLAG) ?TRUE :FALSE)
#define GET_COMBO_EDID_ENABLE_VGA()         (Bool)((ucComboEDIDEnableIndex & COMBO_FUNCTION_ENABLE_VGA_FLAG) ?TRUE :FALSE)

#define GET_COMBO_EDID_ENABLE_PORT(a)       (Bool)((ucComboEDIDEnableIndex & _BIT(a)) ?TRUE :FALSE)

#define GET_COMBO_HDCP_ENABLE_PORT0()       (Bool)((ucComboHDCPEnableIndex & COMBO_FUNCTION_ENABLE_PORT0_FLAG) ?TRUE :FALSE)
#define GET_COMBO_HDCP_ENABLE_PORT1()       (Bool)((ucComboHDCPEnableIndex & COMBO_FUNCTION_ENABLE_PORT1_FLAG) ?TRUE :FALSE)
#define GET_COMBO_HDCP_ENABLE_PORT2()       (Bool)((ucComboHDCPEnableIndex & COMBO_FUNCTION_ENABLE_PORT2_FLAG) ?TRUE :FALSE)
#define GET_COMBO_HDCP_ENABLE_PORT3()       (Bool)((ucComboHDCPEnableIndex & COMBO_FUNCTION_ENABLE_PORT3_FLAG) ?TRUE :FALSE)
#define GET_COMBO_HDCP_ENABLE_PORT4()       (Bool)((ucComboHDCPEnableIndex & COMBO_FUNCTION_ENABLE_PORT4_FLAG) ?TRUE :FALSE)
#define GET_COMBO_HDCP_ENABLE_PORT5()       (Bool)((ucComboHDCPEnableIndex & COMBO_FUNCTION_ENABLE_PORT5_FLAG) ?TRUE :FALSE)

#define GET_COMBO_HDCP_ENABLE_PORT(a)       (Bool)((ucComboHDCPEnableIndex & _BIT(a)) ?TRUE :FALSE)

#define GET_COMBO_DP_ENABLE_PORT0()         (Bool)((ucComboDPEnableIndex & COMBO_FUNCTION_ENABLE_PORT0_FLAG) ?TRUE :FALSE)
#define GET_COMBO_DP_ENABLE_PORT1()         (Bool)((ucComboDPEnableIndex & COMBO_FUNCTION_ENABLE_PORT1_FLAG) ?TRUE :FALSE)
#define GET_COMBO_DP_ENABLE_PORT2()         (Bool)((ucComboDPEnableIndex & COMBO_FUNCTION_ENABLE_PORT2_FLAG) ?TRUE :FALSE)
#define GET_COMBO_DP_ENABLE_PORT3()         (Bool)((ucComboDPEnableIndex & COMBO_FUNCTION_ENABLE_PORT3_FLAG) ?TRUE :FALSE)
#define GET_COMBO_DP_ENABLE_PORT4()         (Bool)((ucComboDPEnableIndex & COMBO_FUNCTION_ENABLE_PORT4_FLAG) ?TRUE :FALSE)
#define GET_COMBO_DP_ENABLE_PORT5()         (Bool)((ucComboDPEnableIndex & COMBO_FUNCTION_ENABLE_PORT5_FLAG) ?TRUE :FALSE)

#define GET_COMBO_DP_ENABLE_PORT(a)         (Bool)((ucComboDPEnableIndex & _BIT(a)) ?TRUE :FALSE)

//-------------------------------------------------------------------------------------------------
//  Function Prototype
//-------------------------------------------------------------------------------------------------
extern BYTE ucComboEDIDEnableIndex;
extern BYTE ucComboHDCPEnableIndex;
extern BYTE ucComboDPEnableIndex;

void mdrv_combo_SetConfiguration(BYTE ucEDIDEnableIndex, BYTE ucHDCPEnableIndex, BYTE ucDPEnableIndex);
void mdrv_combo_LoadEDID(BYTE *pEDIDSize, BYTE **pComboEDID);
void mdrv_combo_LoadEDIDPort(BYTE ucPortSelect, BYTE *pEDIDSize, BYTE **pComboEDID);
void mdrv_combo_LoadHDCPKey(BYTE ucPortSelect, BYTE ucBcaps, BYTE *pHDCPKey, BYTE *pBKSV);
void mdrv_combo_ClockEnable(BYTE ucComboEnableIndex);
void mdrv_combo_AudioInitial(void);
void mdrv_combo_ClockRtermControl(BYTE ucPortSelect, Bool bRtermEnable);
void mdrv_combo_DataRtermControl(BYTE ucPortSelect, Bool bRtermEnable);
void mdrv_combo_DoSWReset(BYTE ucPortSelect, DWORD ulSWResetValue);
void mdrv_combo_CreateTMDSAudioPath(BYTE ucPortSelect);
void mdrv_combo_CreateDPAudioPath(BYTE ucPortSelect, BYTE ucHBR2Select);
void mdrv_combo_ConfigGlobalMute(Bool bEnable);
BYTE mdrv_combo_GetDVIDualMainPort(BYTE ucPortSelect);

void mdrv_combo_HDCP2RxEventProc(BYTE ucPortSelect, BYTE *pMessage);

#if(COMBO_HDCP2_FUNCTION_SUPPORT)
void mdrv_combo_SetHDCP2CallBackFunction(BYTE ucPortSelect, COMBO_HDCP2_CALL_BACK_FUNC pHDCP2TxFunc);
void mdrv_combo_SetHDCP2RxEvent(BYTE ucPortSelect, BYTE *pMessage);
Bool mdrv_combo_HDCP2RomCodeDone(void);
Bool mdrv_combo_HDCP2KeyDecodeDone(void);
Bool mdrv_combo_HDCP2CheckEncodeKeyValid(BYTE *pKeyTable);
void mdrv_combo_HDCP2Initial(void);
void mdrv_combo_HDCP2Handler(void);
#endif

#endif


