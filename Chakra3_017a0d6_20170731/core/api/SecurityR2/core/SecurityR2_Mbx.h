#ifndef __SECU_MBX__
#define __SECU_MBX__

#include "Board.h"

#if 0//( ENABLE_SECURITY_R2 )



typedef enum
{
//MStar Vendor Specific
    //TBD
    MSG_INIT_CODEBASE_ADDR = 0,
    MSG_SET_DRAM_SEC_RANGE = 1,
    MSG_INIT_MAILBOX_MEMORY = 12,
//AKE
    MSG_HDCP22_AKE_INIT = 2,
    MSG_HDCP22_AKE_SEND_CERT = 3,
    MSG_HDCP22_AKE_NO_STORED_KM = 4,
    MSG_HDCP22_AKE_STORED_KM = 5,
    MSG_HDCP22_AKE_SEND_H_PRIME = 7,
    MSG_HDCP22_AKE_SEND_PARING_INFO = 8,
//LC
    MSG_HDCP22_LC_INIT = 9,
    MSG_HDCP22_LC_SEND_L_PRIME = 10,
//SKE
    MSG_HDCP22_SKE_SEND_EKS = 11,

//special case
    MSG_HDCP22_RESET_HW = 13,
    MSG_HDCP22_RESET_PORTINFO = 14,
    MSG_HDCP22_DECODE_KEY = 15,
    MSG_HDCP22_LG_DECRPT = 16, //LG only

} enHDCPMBX_MSG_LIST; //ENUM_SECR2_MSG_ID;

typedef enum
{
    MBX_ERR_NONE = 0,

    MBX_ERR_MSG_SEND_FAIL,
    MBX_ERR_MSG_RECEIVE_FAIL,

    MBX_ERR_INVALID_PORTIDX,
    MBX_ERR_INVALID_MSGID,
    MBX_ERR_INVALID_ARG_ADDR,
    MBX_ERR_INVALID_ARG_SIZE,
} enHDCPMBX_ERROR_CODE;

typedef enum
{
    MBX_HKR2 = 0,
    MBX_SECR2 = 1,
} enHDCPMBX_CPU_LIST;

typedef enum
{
    MBX_Port_Inactive = 0,
    MBX_Port_Active = BIT7,
} enHDCPMBX_PORT_STATUS;

typedef enum
{
    MBXMSG_WITHOUT_ARG = 0,
    MBXMSG_WITH_ARG = 1,
} enHDCPMBX_MSG_ARG_ATTR;

typedef enum
{
	MBXMSG_STATE_INIT = 0,
    MBXMSG_STATE_IDLE,
    MBXMSG_STATE_WAIT,
    MBXMSG_STATE_PROCESSING,
    MBXMSG_STATE_HALT,         // when error occurs
    MBXMSG_STATE_DONE,
} enHDCPMBX_MSG_STATE;


typedef enum
{
	MBXMSG_TYPE_HDCP = 0,
	MBXMSG_TYPE_TTS = 1,
} enMBX_MSG_TYPE;


typedef struct
{
    BYTE    MsgID;         //port_status(bit 7) | msg_id(bit 6..0)
    BYTE    Status;         //msg host CPU(bit 7) | HaveArg(bit 6) | state(2..0)
    BYTE    ErrCode;
    ULONG    ArgAddr;
    ULONG    ArgSize;
} stHDCPMBX_HANDLER;





enHDCPMBX_MSG_STATE SecureR2_MBX_RecvMsg(stHDCPMBX_HANDLER *pMsg, enMBX_MSG_TYPE enMsgType);
enHDCPMBX_MSG_STATE SecureR2_MBX_SendMsg(stHDCPMBX_HANDLER *pMsg, enMBX_MSG_TYPE enMsgType);
enHDCPMBX_MSG_STATE SecureR2_MBX_Init(void);

#endif

#endif // __SECU_MBX__

