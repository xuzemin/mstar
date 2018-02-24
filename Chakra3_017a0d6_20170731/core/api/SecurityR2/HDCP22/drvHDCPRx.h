#ifndef DRV_HDCPRX_H
#define DRV_HDCPRX_H

#include "combo_config.h"

/*********************************************************************/
/*                                                                                                                     */
/*                                                      Defines                                                    */
/*                                                                                                                     */
/*********************************************************************/
#define HDCP_IP_SUPPORT_0PORT           0
#define HDCP_IP_SUPPORT_1PORT           1
#define HDCP_IP_SUPPORT_2PORT           2
#define HDCP_IP_SUPPORT_3PORT           3
#define HDCP_IP_SUPPORT_4PORT           4
#define HDCP_IP_SUPPORT_5PORT           5
#define HDCP_IP_SUPPORT_6PORT           6

#define HDCP_IP_SUPPORT_TYPE            COMBO_IP_SUPPORT_TYPE

enum HDCP_INPUT_SELECT_TYPE
{
    HDCP_INPUT_SELECT_PORT0 = 0,
#if(HDCP_IP_SUPPORT_TYPE == HDCP_IP_SUPPORT_1PORT)
    HDCP_INPUT_SELECT_PORT_END,
#endif
    HDCP_INPUT_SELECT_PORT1,
#if(HDCP_IP_SUPPORT_TYPE == HDCP_IP_SUPPORT_2PORT)
    HDCP_INPUT_SELECT_PORT_END,
#endif
    HDCP_INPUT_SELECT_PORT2,
#if(HDCP_IP_SUPPORT_TYPE == HDCP_IP_SUPPORT_3PORT)
    HDCP_INPUT_SELECT_PORT_END,
#endif
    HDCP_INPUT_SELECT_PORT3,
#if(HDCP_IP_SUPPORT_TYPE == HDCP_IP_SUPPORT_4PORT)
    HDCP_INPUT_SELECT_PORT_END,
#endif
    HDCP_INPUT_SELECT_PORT4,
#if(HDCP_IP_SUPPORT_TYPE == HDCP_IP_SUPPORT_5PORT)
    HDCP_INPUT_SELECT_PORT_END,
#endif
    HDCP_INPUT_SELECT_PORT5,
#if(HDCP_IP_SUPPORT_TYPE == HDCP_IP_SUPPORT_6PORT)
    HDCP_INPUT_SELECT_PORT_END,
#endif
    HDCP_INPUT_SELECT_MASK = HDCP_INPUT_SELECT_PORT_END,
    HDCP_INPUT_SELECT_NONE = HDCP_INPUT_SELECT_MASK,
};
#if ( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA) )
#define DEV_NUM           4 //  HDCP_INPUT_SELECT_MASK
#else
#define DEV_NUM           1 //  HDCP_INPUT_SELECT_MASK
#endif
#define AUTH_CMD_NUM        21
#define SUPPORT_REPEATER    0

//message pool usage
#define ORDER_IDX       0
#define MSGID_IDX       (ORDER_IDX + 1)
#define MSGARG_IDX      (MSGID_IDX + 1)

#define RTX_SIZE        8
#define RXCAPS_SIZE     3
#define RRX_SIZE        8
#define TXCAPS_SIZE     3
#define CERTRX_SIZE     522
#define EKPUBKM_SIZE    128
#define EKHKM_SIZE      16
#define M_SIZE          16
#define H_SIZE          32
#define RN_SIZE         8
#define LPRIME_SIZE     32
#define EDKEYKS_SIZE    16
#define RIV_SIZE        8
#define ENCODE_KEY_SIZE 1044

#define KPUBRX_P  64   //512 bits
#define KPUBRX_Q  64   // 512 bits
#define KPUBRX_dP  64   // 512 bits
#define KPUBRX_dQ  64   // 512 bits
#define KPUBRX_qInv  64   // 512 bits

#define SHA256_DIGEST_SIZE  32
#define MASTERKEY_SIZE 16 // 128 bits

#define RX_HDCP_AUTH_BLOCK_CPU_TIME     0   //600

#if (RX_HDCP_AUTH_BLOCK_CPU_TIME==0)
#define RX_AKE_SEND_CERT    50  //HDCP spec not define for RX, total handshaking defined as 100ms  
#define RX_AKE_SEND_H_PRIME_STORED_KM     140     //HDCP spec define 200ms
#define RX_AKE_SEND_H_PRIME_NO_STORED_KM     400     //HDCP spec not define for RX, total handshaking defined as 1000ms  
#else
#define RX_AKE_SEND_CERT    0
#define RX_AKE_SEND_H_PRIME_STORED_KM     0
#define RX_AKE_SEND_H_PRIME_NO_STORED_KM     0
#endif
/*********************************************************************/
/*                                                                                                                     */
/*                                                      Structure                                                  */
/*                                                                                                                     */
/*********************************************************************/

typedef struct {
    BYTE P[KPUBRX_P];
    BYTE Q[KPUBRX_Q];
    BYTE dP[KPUBRX_dP];
    BYTE dQ[KPUBRX_dQ];
    BYTE Qinv[KPUBRX_qInv];
} PRIVATE_KEY_RX;

enum enHDCP_PORT_IDX
{
    HDCP_PORT_0 = 0,
    //HDCP_PORT_1 = 1,
    //HDCP_PORT_2 = 2,
    //HDCP_PORT_3 = 3,
    //HDCP_PORT_4 = 4,
    HDCP_PORT_MAX,
    HDCP_PORT_ALL = 0xF
}; //enHDCP_PORT_IDX;

typedef enum
{
    StateZero = 0,
    Null_Msg = 1,
    AKE_Init = 2,
    AKE_Send_Cert = 3,
    AKE_No_Stored_km = 4,
    AKE_Stored_km = 5,
    AKE_Send_rrx = 6,
    AKE_Send_H_Prime = 7,
    AKE_Send_Pairing_Info = 8,
    LC_Init = 9,
    LC_Send_L_Prime = 10,
    SKE_Send_Eks = 11,
    RepeaterAuth_Send_ReceiverID_List = 12,
    RTT_Ready = 13,
    RTT_Challenge = 14,
    RepeaterAuth_Send_Ack = 15,
    RepeaterAuth_Stream_Manage = 16,
    RepeaterAuth_Strem_Ready = 17,
    Receiver_AuthStatus = 18,
    AKE_Transmitter_Info = 19,
    AKE_Receiver_Info = 20,
} enHDCP_Msg_List;

typedef enum
{
    HDCP_ERR_NONE = 0,
    HDCP_UNKNOWN_STATE,
    HDCP_INVALID_ARG,
    HDCP_PROCESS_FAIL,

} enHDCP_Err_Status;

typedef enum
{
    RxState_B0 = 0,
    RxState_B1,
    RxState_B2,
    RxState_B3,
    RxState_B4,
} enHDCP_RxState_List;

typedef struct
{
    BYTE rtx[RTX_SIZE];
    BYTE TxCaps[TXCAPS_SIZE];
} stArg_AKE_Init;

typedef struct
{
    BYTE certrx[CERTRX_SIZE];
    BYTE rrx[RRX_SIZE];
    BYTE RxCaps[RXCAPS_SIZE];
} stArg_AKE_Send_Cert;

typedef struct
{
    BYTE Ekpubkm[EKPUBKM_SIZE];
} stArg_AKE_No_Stored_km;

typedef struct
{
    BYTE Ekhkm[EKPUBKM_SIZE];
    BYTE m[M_SIZE];
} stArg_AKE_Stored_km;

typedef struct
{
    BYTE H[H_SIZE];
} stArg_AKE_Send_H_Prime;

typedef struct
{
    BYTE Ekhkm[EKHKM_SIZE];
} stArg_AKE_Send_Pairing_Info;

typedef struct
{
    BYTE rn[RN_SIZE];
} stArg_LC_Init;

typedef struct
{
    BYTE LPrime[LPRIME_SIZE];
} stArg_LC_Send_L_Prime;

typedef struct
{
    BYTE Edkeyks[EDKEYKS_SIZE];
    BYTE riv[RIV_SIZE];
} stArg_SKE_Send_Eks;

typedef struct
{
    BYTE MsgID;
    union {
        stArg_AKE_Init              ArgAKEInit;
        stArg_AKE_Send_Cert         ArgAKESendCert;
        stArg_AKE_No_Stored_km      ArgAKENoStoredKm;
        stArg_AKE_Stored_km         ArgAKEStoredKm;
        stArg_AKE_Send_H_Prime      ArgAKESendHPrime;
        stArg_AKE_Send_Pairing_Info ArgAKESendPairingInfo;
        stArg_LC_Init               ArgLCInit;
        stArg_LC_Send_L_Prime       ArgLCSendLPrime;
        stArg_SKE_Send_Eks          ArgSKESendEks;
    } MsgArg;
} stHDCP_MSG;

//typedef bool (* HDCP_RECV_FUNC) (stHDCP_MSG*);
typedef void ( *HDCP_SEND_FUNC)(BYTE, BYTE, BYTE, BYTE*); //PortIdx, MsgID, size, data pointer

typedef struct
{
    //stHDCP_MSG              Msg;
    enHDCP_RxState_List     MainState;
    enHDCP_Msg_List         SubState;
    bool                    bStoredkm;
    bool                    AuthDone;
    bool                    Polling;    //TRUE if process is waiting SEC R2 response
    //HDCP_RECV_FUNC          RecvFunc;
    HDCP_SEND_FUNC          SendFunc;
    BYTE                    rtx[RTX_SIZE];
    BYTE                    txCaps[TXCAPS_SIZE];
    BYTE                    rrx[RRX_SIZE];
    BYTE                    rxCaps[RXCAPS_SIZE];
    #if 0
    BYTE                    Ekpub_km[EKPUBKM_SIZE];
    BYTE                    Ekh_km[EKHKM_SIZE];
    BYTE                    m[M_SIZE];
    BYTE                    Hprime[H_SIZE];
    BYTE                    rn[RN_SIZE];
    BYTE                    Lprime[LPRIME_SIZE];
    BYTE                    Edkey_ks[EDKEYKS_SIZE];
    BYTE                    riv[RIV_SIZE];
    #endif
} stHDCPContent;


/*********************************************************************/
/*                                                                                                                     */
/*                                       Function Proto Type                                                  */
/*                                                                                                                     */
/*********************************************************************/
ULONG drv_HDCPRx_GetTxBufAddr(void);
void drv_HDCPRx_SetTxBufAddr(U32 u32Address);
void drv_HDCPRx_SetR2EventFlag(void);
Bool drv_HDCPRx_GetR2EventFlag(void);
void drv_HDCPRx_InitCBFunction(BYTE ucPortIdx, HDCP_SEND_FUNC pCBFunc);
void drv_HDCPRx_Init(BYTE enPortIdx);
void drv_HDCPRx_DecodeKey(BYTE *pCertRxTable);
enHDCP_Err_Status drv_HDCPRx_MsgParser(BYTE ucPortIdx, BYTE *pucMsg);
void drv_HDCPRx_Handler(void);

void drv_HDCPRx_InitBySystem(void);
#endif

