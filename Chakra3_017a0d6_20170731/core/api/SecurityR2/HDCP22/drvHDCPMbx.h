#ifndef HAL_MBX_H
#define HAL_MBX_H

/*********************************************************************/
/*                                                                                                                     */
/*                                                      Defines                                                    */
/*                                                                                                                     */
/*********************************************************************/

#define EN_FPGA_MBX_DEBUG       0

#define HDCPMBX_MEM_ADDR  0xA00000 //TBD; temp solution
#define HDCPMBX_DATASLOT_SIZE  512 //TBD; temp solution

//TBD
#define MBX_MAX_SLOT            0x01
#define HDCPMBX_SLOT_SIZE       0x10
#define HDCPMBX_BUF_SIZE        150 //undercheck
#define MBX_INVALID_SLOT_IDX    0xFFFF

#define MBX_MSGID_IDX           0
#define MBX_STATUS_IDX          MBX_MSGID_IDX + 1
#define MBX_ERRCODE_IDX         MBX_STATUS_IDX + 1
#define MBX_ARGADDR_IDX         MBX_ERRCODE_IDX + 1
#define MBX_ARGSIZE_IDX         MBX_ARGADDR_IDX + 4

#define HDCPMBX_START_ADDR REG_1033C0 // 0x0E00

/*********************************************************************/
/*                                                                                                                     */
/*                                                      Structure                                                  */
/*                                                                                                                     */
/*********************************************************************/
#if 0
typedef enum
{
    MBX_FLAG_NONE = 0x0000,
    MBX_FLAG_GET_MSG = 0x0001,
} EN_MBX_FLAG;
#endif

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

#if 0//(EN_FPGA_MBX_DEBUG == 1)
    //temp
    MSG_TEST_SHA1 = 13,
    MSG_TEST_SHA256 = 14,
    MSG_TEST_SHA1_HMAC = 15,
    MSG_TEST_SHA256_HMAC = 16,
    MSG_TEST_SHA1_WB = 17,
    MSG_TEST_SHA256_WB = 18,
    MSG_TEST_SHA1_HMAC_WB = 19,
    MSG_TEST_SHA256_HMAC_WB = 20,
    MSG_TEST_AES_CTR = 21,
    MSG_TEST_AES_CBC = 22,
    MSG_TEST_AES_ECB = 23,
    MSG_TEST_AES_CTR_WB = 24,
    MSG_TEST_AES_CBC_WB = 25,
    MSG_TEST_AES_ECB_WB = 26,
    MSG_TEST_RSA256 = 27,
    MSG_TEST_RSA2048 = 28,

    MSG_TEST_AES_CBC_DE = 29,
    MSG_TEST_AES_ECB_DE = 30,
    MSG_TEST_AES_CBC_DE_WB = 31,
    MSG_TEST_AES_ECB_DE_WB = 32,

    MSG_TEST_SEC_RANGE = 33,
    MSG_TEST_VERIFY_SIGN = 34,
#endif

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

typedef struct
{
    BYTE    MsgID;         //port_status(bit 7) | msg_id(bit 6..0)
    BYTE    Status;         //msg host CPU(bit 7) | HaveArg(bit 6) | state(2..0)
    BYTE    ErrCode;
    ULONG    ArgAddr;
    ULONG    ArgSize;
} stHDCPMBX_HANDLER;

/*********************************************************************/
/*                                                                                                                     */
/*                                       Function Proto Type                                                  */
/*                                                                                                                     */
/*********************************************************************/
enHDCPMBX_ERROR_CODE _drv_HDCPMBX_ClrMsgSlot(BYTE ucSlotIdx);
void drv_HDCPMBX_ClearActiveBit(BYTE ucIdx);
enHDCPMBX_ERROR_CODE drv_HDCPMBX_Init(void);
enHDCPMBX_ERROR_CODE drv_HDCPMBX_UpdateState(BYTE ucSlotIdx, enHDCPMBX_MSG_STATE enState);
enHDCPMBX_ERROR_CODE drv_HDCPMBX_SetMsg(BYTE ucSlotIdx, BYTE ucMsgID, enHDCPMBX_CPU_LIST enHost, enHDCPMBX_MSG_ARG_ATTR enArgAttribute, enHDCPMBX_MSG_STATE enStatus, enHDCPMBX_ERROR_CODE enErrCode, ULONG dwArgAddr, ULONG dwArgSize);
enHDCPMBX_ERROR_CODE drv_HDCPMBX_GetMsg(enHDCPMBX_CPU_LIST enClient, stHDCPMBX_HANDLER* pMBXHnadler);
enHDCPMBX_MSG_STATE drv_HDCPMBX_CheckMsgState(BYTE ucSlotIdx);
enHDCPMBX_ERROR_CODE drv_HDCPMBX_SetKeyMessage(BYTE ucMsgID, enHDCPMBX_CPU_LIST enHost, enHDCPMBX_MSG_ARG_ATTR enArgAttribute, enHDCPMBX_MSG_STATE enStatus, enHDCPMBX_ERROR_CODE enErrCode, ULONG dwArgAddr, ULONG dwArgSize);

#endif
