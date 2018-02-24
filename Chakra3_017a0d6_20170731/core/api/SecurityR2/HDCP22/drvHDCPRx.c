///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// file    drvHDCPRx.c
/// @author MStar Semiconductor Inc.
/// @brief  HDCP22 driver Function
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef DRV_HDCPRX_C
#define DRV_HDCPRX_C

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------

#include "msReg.h"

#include <string.h>
#include "datatype.h"
#include "MsTypes.h"
#include "MsOS.h"
#include "drvGlobal.h"
#include "default_option_define.h"

//#include "Global.h"
//#include "Common.h"
#include "drvHDCPRx.h"
#include "drvHDCPMbx.h"
#include "mhal_combo.h"
#include "drvISR.h"
#include "msAPI_SecurityR2.h"
#include "msAPI_Timer.h"
#include "MApp_GlobalFunction.h"
#include "mhal_tmds.h"
#include "msAPI_Global.h"
#if ((ENABLE_SECU_R2 == 1) && (ENABLE_HDCP22 == 1))

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
#define HDCP_DRV_DEBUG_MESSAGE          0
#define HDCP_DRV_PARSER_MESSAGE         0

#if(ENABLE_MSTV_UART_DEBUG & HDCP_DRV_DEBUG_MESSAGE)
#define HDCP_DRV_DPUTSTR(str)           printf(str)
#define HDCP_DRV_DPRINTF(str, x)        printf(str, x)
#else
#define HDCP_DRV_DPUTSTR(str)
#define HDCP_DRV_DPRINTF(str, x)
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
//length = 1 byte(msgID) + argument length
const WORD gMsgArgLen[AUTH_CMD_NUM] =
{
    0,      //na
    0,      //NULL_MESSAGE = 1,
    12,     //AKE_INIT = 2,
    534,    //AKE_SEND_CERT = 3,
    129,    //AKE_NO_STORED_KM = 4,
    33,     //AKE_STORED_KM = 5,
    0,      //AKE_SEND_RRX = 6,
    33,     //AKE_SEND_H_PRIME = 7,
    17,     //AKE_SEND_PAIRING_INFO = 8,
    9,      //LC_INIT = 9,
    33,     //LC_SEND_L_PRIME =10,
    25,     //SKE_SEND_EKS = 11,
    0,      //5 to (5+DeviceCount*5); REPEATERAUTH_SEND_RECEIVERID_LIST = 12,
    0,      //RTT_READY = 13,
    0,     //RTT_CHALLENGE = 14,
    0,     //REPEATERAUTH_SEND_ACK = 15,
    0,      //REPEATERAUTH_STREAM_MANAGE = 16,
    0,     //REPEATERAUTH_STREAM_READY = 17,
    0,      //RECEIVER_AUTHSTATUS = 18,
    0,      //AKE_TRANSMITTER_INFO = 19,
    0,      //AKE_RECEIVER_INFO = 20,
};

static stHDCPContent volatile HdcpHandler[DEV_NUM];

//BYTE volatile gHdcpMbx_TxBuf[DEV_NUM][32 + 16]; //*2 for Sec world and HK world //__attribute__((aligned(16))); //H'(32) + Ekh(km) (16)
// gHdcpMbx_TxBuf should not be in HK-R2 or SECU-R2 area, which are protected by MIU protect
volatile BYTE (*gHdcpMbx_TxBuf)[32 + 16];
BYTE volatile gHdcpMbx_RxBuf[DEV_NUM][130]; //__attribute__((aligned(16))); //idx 1+1+128 = portIdx + msgID + msgArg
BYTE ucSecR2EventFlag = 0;

//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------
void __HDCP_MsgPool_Relative_Func__(void){}

//**************************************************************************
//  [Function Name]:
//                  _drv_HDCPRx_MsgPoolGetMax()
//  [Description]:
//
//  [Arguments]:
//
//  [Return]:
//
//
//**************************************************************************
BYTE _drv_HDCPRx_MsgPoolGetMax(void)
{
    BYTE uctemp = 0;
    BYTE MaxPriority = 0;

    for(uctemp = 0; uctemp < DEV_NUM; uctemp++ )
    {
        if(gHdcpMbx_RxBuf[uctemp][0] > MaxPriority)
        {
            MaxPriority = gHdcpMbx_RxBuf[uctemp][0];
        }
    }

    return MaxPriority;
}

//**************************************************************************
//  [Function Name]:
//                  _drv_HDCPRx_MsgPoolGetMin()
//  [Description]:
//
//  [Arguments]:
//
//  [Return]:
//
//
//**************************************************************************
BYTE _drv_HDCPRx_MsgPoolGetMin(void)
{
    BYTE uctemp = 0;
    BYTE MinPriority = DEV_NUM;

    for(uctemp = 0; uctemp < DEV_NUM; uctemp++)
    {
        if((gHdcpMbx_RxBuf[uctemp][0] < MinPriority) && (gHdcpMbx_RxBuf[uctemp][0] != 0))
        {
            MinPriority = gHdcpMbx_RxBuf[uctemp][0];
        }
    }

    return MinPriority;
}

//**************************************************************************
//  [Function Name]:
//                  _drv_HDCPRx_MsgPoolFetchMsgIdx()
//  [Description]:
//
//  [Arguments]:
//
//  [Return]:
//
//
//**************************************************************************
BYTE _drv_HDCPRx_MsgPoolFetchMsgIdx(void)
{
    BYTE uctemp = 0;
    BYTE MaxPriority = 0;
    BYTE MsgIdx = 0;

    for(uctemp = 0; uctemp < DEV_NUM; uctemp++)
    {
        if(gHdcpMbx_RxBuf[uctemp][0] > MaxPriority)
        {
            MaxPriority = gHdcpMbx_RxBuf[uctemp][0];
            MsgIdx = uctemp;
        }
    }

    if (MaxPriority != 0)
    {
        return MsgIdx;
    }
    else
    {
        return (DEV_NUM + 1); //no msg received
    }
}

//**************************************************************************
//  [Function Name]:
//                  _drv_HDCPRx_MsgPoolFillPriority()
//  [Description]:
//
//  [Arguments]:
//
//  [Return]:
//
//
//**************************************************************************
void _drv_HDCPRx_MsgPoolFillPriority(BYTE ucPortIdx)
{
    BYTE uctemp = 0;
    BYTE ucCurMax = 0;
    BYTE ucCurMin = 0;

    ucCurMax = _drv_HDCPRx_MsgPoolGetMax();

    if(ucCurMax == 0)
    {
        gHdcpMbx_RxBuf[ucPortIdx][0] = 1; //first msg
    }
    else
    {
        ucCurMin = _drv_HDCPRx_MsgPoolGetMin();

        if(ucCurMin != (DEV_NUM + 1))
        {
            for(uctemp = 0; uctemp < DEV_NUM; uctemp++) // Increase priority 1 in all active process
            {
                if((gHdcpMbx_RxBuf[uctemp][0] != 0) && (gHdcpMbx_RxBuf[uctemp][0] <= DEV_NUM))
                {
                    gHdcpMbx_RxBuf[uctemp][0]++;
                }
            }

            gHdcpMbx_RxBuf[ucPortIdx][0] = ucCurMin;
        }
        else
        {
            gHdcpMbx_RxBuf[ucPortIdx][0] = 1; //should not entering this condition
        }
    }
}

//pesudo function
void __HDCP_Relative_Func__(void){}
//**************************************************************************
//  [Function Name]:
//                  _drv_HDCPRx_FlushCache()
//  [Description]:
//
//  [Arguments]:
//
//  [Return]:
//
//
//**************************************************************************
void _drv_HDCPRx_FlushCache(ULONG dwBufAddr, ULONG dwsize)
{
    ULONG ultemp = 0;
#if( CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA )
    U8* pu8BufAddr_NonCache = (U8*)msOS_CacheToNonCache((U32)dwBufAddr);
#endif
    for(ultemp = 0; ultemp < dwsize; ultemp++)
    {
#if( CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA )
        *(BYTE*)(pu8BufAddr_NonCache + ultemp) = *(BYTE*)(dwBufAddr + ultemp);
#else
        *(BYTE*)((dwBufAddr | 0x80000000) + ultemp) = *(BYTE*)(dwBufAddr + ultemp);
#endif
    }
}

//**************************************************************************
//  [Function Name]:
//                  _drv_HDCPRx_UpdateFromDRAM()
//  [Description]:
//
//  [Arguments]:
//
//  [Return]:
//
//
//**************************************************************************
void _drv_HDCPRx_UpdateFromDRAM(ULONG dwBufAddr, ULONG dwsize)
{
    ULONG ultemp = 0;
    for(ultemp = 0; ultemp < dwsize; ultemp++)
    {
    //*(BYTE*)(dwBufAddr + i) = (BYTE*)((dwBufAddr | 0x80000000) + i);
        *(BYTE*)(dwBufAddr + ultemp) = MIU8(dwBufAddr + ultemp);
    }
}

//**************************************************************************
//  [Function Name]:
//                  _drv_HDCPRx_MsgPoolAssignPriority()
//  [Description]:
//
//  [Arguments]:
//
//  [Return]:
//
//
//**************************************************************************
void _drv_HDCPRx_MsgPoolAssignPriority(BYTE ucPortIdx, BYTE ucPriority)
{
    gHdcpMbx_RxBuf[ucPortIdx][0] = ucPriority;

    _drv_HDCPRx_FlushCache((ULONG)&(gHdcpMbx_RxBuf[ucPortIdx][0]), 1);
}


//**************************************************************************
//  [Function Name]:
//                  _drv_HDCPRx_CheckWaitingProcess()
//  [Description]:
//                  check if there is any port waiting security module process
//  [Arguments]:
//                  void
//  [Return]:
//                  [enHDCP_PORT_IDX]
//
//**************************************************************************
BYTE _drv_HDCPRx_CheckWaitingProcess(void)
{
    BYTE uctemp = 0;

    for(uctemp = HDCP_PORT_0; uctemp < HDCP_PORT_MAX; uctemp++)
    {
        if(HdcpHandler[uctemp].Polling == TRUE)
        {
            return uctemp;
        }
    }

    return HDCP_PORT_ALL;
}

//**************************************************************************
//  [Function Name]:
//                  _drv_HDCPRx_ClrMbxBuf()
//  [Description]:
//
//  [Arguments]:
//
//  [Return]:
//                  void
//
//**************************************************************************
void _drv_HDCPRx_ClrMbxRxBuf(BYTE ucPortIdx)
{
    BYTE uctemp = 0;

    for(uctemp = 0; uctemp < (gMsgArgLen[AKE_No_Stored_km] + 1); uctemp++)
    {
        gHdcpMbx_RxBuf[ucPortIdx][uctemp] = 0;
    }
}

//**************************************************************************
//  [Function Name]:
//                  _drv_HDCPRx_ParserMessage()
//  [Description]:
//
//  [Arguments]:
//
//  [Return]:
//                  void
//
//**************************************************************************
void _drv_HDCPRx_ParserMessage(BYTE ucPortIndex, WORD usLength)
{
#if (HDCP_DRV_PARSER_MESSAGE)
    WORD ustemp = 0;

    for(ustemp = 0; ustemp < usLength; ustemp++)
    {
        HDCP_DRV_DPRINTF("0x%02X, ", gHdcpMbx_RxBuf[ucPortIndex][MSGID_IDX + ustemp]);

        if((ustemp +1) %16 == 0)
        {
            HDCP_DRV_DPUTSTR("\r\n");
        }
    }

    HDCP_DRV_DPUTSTR("\r\n");

#endif

    ucPortIndex = usLength;
}

//**************************************************************************
//  [Function Name]:
//                  _drv_HDCPRx_AKEInit()
//  [Description]:
//                  Pass rtx, TxCaps, rrx, and RxCaps to Security R2
//  [Arguments]:
//                  [enHDCP_PORT_IDX] enPortIdx,
//                  [stHDCPContent]* pstHandler
//  [Return]:
//                  [enHDCP_Err_Status]
//
//**************************************************************************
enHDCP_Err_Status _drv_HDCPRx_AKEInit(BYTE enPortIdx, stHDCPContent *pstHandler)
{
    enHDCPMBX_ERROR_CODE MbxErrCode = MBX_ERR_NONE;

    MbxErrCode = drv_HDCPMBX_SetMsg(enPortIdx, MSG_HDCP22_AKE_INIT, MBX_HKR2, MBXMSG_WITH_ARG, MBXMSG_STATE_WAIT, \
                                    MBX_ERR_NONE, (ULONG)&gHdcpMbx_RxBuf[enPortIdx][MSGARG_IDX], (RTX_SIZE + TXCAPS_SIZE));

    if(MbxErrCode == MBX_ERR_NONE)
    {
    	//polling random number
    	pstHandler->Polling = TRUE;

	//update priority
	_drv_HDCPRx_MsgPoolAssignPriority(enPortIdx, (gHdcpMbx_RxBuf[enPortIdx][0] + DEV_NUM));

        return HDCP_ERR_NONE;
    }
    else
    {
        return HDCP_PROCESS_FAIL;
    }
}

//**************************************************************************
//  [Function Name]:
//                  _drv_HDCPRx_AKESendCert()
//  [Description]:
//
//  [Arguments]:
//                  [enHDCP_PORT_IDX] enPortIdx,
//                  [stHDCPContent]* pstHandler
//  [Return]:
//                  [enHDCP_Err_Status]
//
//**************************************************************************
enHDCP_Err_Status _drv_HDCPRx_AKESendCert(BYTE enPortIdx, stHDCPContent* pstHandler)
{
    pstHandler->SubState = AKE_Send_Cert;

    //command IP to send message; update from DRAM
    _drv_HDCPRx_UpdateFromDRAM((ULONG)(&gHdcpMbx_TxBuf[enPortIdx][0]), (RRX_SIZE + RXCAPS_SIZE));   //mdrv_tmds_HDCP2TxEventProc

    pstHandler->SendFunc(enPortIdx, AKE_Send_Cert, (RRX_SIZE + RXCAPS_SIZE), (BYTE*)&gHdcpMbx_TxBuf[enPortIdx][0]);

    return HDCP_ERR_NONE;
}

//**************************************************************************
//  [Function Name]:
//                  _drv_HDCPRx_AKENoStoredKm()
//  [Description]:
//
//  [Arguments]:
//                  [BYTE] ucIdx: port index
//  [Return]:
//                  [bool]: TRUE if the message is done, and FALSE for halt
//
//**************************************************************************
enHDCP_Err_Status _drv_HDCPRx_AKENoStoredKm(BYTE enPortIdx, stHDCPContent* pstHandler)
{
    enHDCPMBX_ERROR_CODE MbxErrCode = MBX_ERR_NONE;

    MbxErrCode = drv_HDCPMBX_SetMsg(enPortIdx, MSG_HDCP22_AKE_NO_STORED_KM, MBX_HKR2, MBXMSG_WITH_ARG, MBXMSG_STATE_WAIT,\
                                    MBX_ERR_NONE, (ULONG)&gHdcpMbx_RxBuf[enPortIdx][MSGARG_IDX], EKPUBKM_SIZE);

    if (MbxErrCode == MBX_ERR_NONE)
    {
        pstHandler->Polling = TRUE;

        //update priority
		_drv_HDCPRx_MsgPoolAssignPriority(enPortIdx, (gHdcpMbx_RxBuf[enPortIdx][0] + DEV_NUM));

        return HDCP_ERR_NONE;
    }
    else
    {
        return HDCP_PROCESS_FAIL;
    }
}

//**************************************************************************
//  [Function Name]:
//                  _drv_HDCPRx_AKEStoredKm()
//  [Description]:
//
//  [Arguments]:
//                  [BYTE] ucIdx: port index
//  [Return]:
//                  [bool]: TRUE if the message is done, and FALSE for halt
//
//**************************************************************************
enHDCP_Err_Status _drv_HDCPRx_AKEStoredKm(BYTE enPortIdx, stHDCPContent* pstHandler)
{
    enHDCPMBX_ERROR_CODE MbxErrCode = MBX_ERR_NONE;

	MbxErrCode = drv_HDCPMBX_SetMsg(enPortIdx, MSG_HDCP22_AKE_STORED_KM, MBX_HKR2, MBXMSG_WITH_ARG, MBXMSG_STATE_WAIT,\
                                    MBX_ERR_NONE, (ULONG)&gHdcpMbx_RxBuf[enPortIdx][MSGARG_IDX], (EKHKM_SIZE + M_SIZE));

    if (MbxErrCode == MBX_ERR_NONE)
    {
        pstHandler->Polling = TRUE;

        //update priority
		_drv_HDCPRx_MsgPoolAssignPriority(enPortIdx, (gHdcpMbx_RxBuf[enPortIdx][0] + DEV_NUM));

        return HDCP_ERR_NONE;
    }
    else
    {
        return HDCP_PROCESS_FAIL;
    }
}

//**************************************************************************
//  [Function Name]:
//                  _drv_HDCPRx_AKESendHPrime()
//  [Description]:
//
//  [Arguments]:
//                  [BYTE] ucIdx: port index
//  [Return]:
//                  [bool]: TRUE if the message is done, and FALSE for halt
//
//**************************************************************************
enHDCP_Err_Status _drv_HDCPRx_AKESendHPrime(BYTE enPortIdx, stHDCPContent* pstHandler)
{
    //[NOTE] The Security R2 Will Calculate H' and Pairing Info at Same Time,
    //So the Return Data Will be the Combination of 2 Variables ( H' + Ekh(km))

	_drv_HDCPRx_UpdateFromDRAM((ULONG)(&gHdcpMbx_TxBuf[enPortIdx][0]), H_SIZE + EKHKM_SIZE);

	pstHandler->SendFunc(enPortIdx, AKE_Send_H_Prime, H_SIZE, (BYTE*)&gHdcpMbx_TxBuf[enPortIdx][0]);

    return HDCP_ERR_NONE;

}

//**************************************************************************
//  [Function Name]:
//                  _drv_HDCPRx_AKESendPairingInfo()
//  [Description]:
//
//  [Arguments]:
//                  [BYTE] ucIdx: port index
//  [Return]:
//                  [bool]: TRUE if the message is done, and FALSE for halt
//
//**************************************************************************
enHDCP_Err_Status _drv_HDCPRx_AKESendPairingInfo(BYTE enPortIdx, stHDCPContent* pstHandler)
{
//    U8 i;

    pstHandler->SubState = AKE_Send_Pairing_Info;

    //[NOTE] The Security R2 Will Calculate H' and Pairing Info at Same Time,
    //So the Return Data Will be the Combination of 2 Variables ( H' + Ekh(km))

	pstHandler->SendFunc(enPortIdx, AKE_Send_Pairing_Info, EKHKM_SIZE, (BYTE*)&gHdcpMbx_TxBuf[enPortIdx][H_SIZE]);
#if 0

   printf("enPortIdx=%d\n", enPortIdx);

    for(i=H_SIZE;i<EKHKM_SIZE; i++)
    {
        printf("%x ", gHdcpMbx_TxBuf[enPortIdx][i]);

    }
    printf("\n");
#endif

	//pstHandler->SendFunc(enPortIdx, AKE_Send_Pairing_Info, EKHKM_SIZE, (BYTE*)&gHdcpMbx_TxBuf[enPortIdx][0]);

    return HDCP_ERR_NONE;
}

//**************************************************************************
//  [Function Name]:
//                  _drv_HDCPRx_LCInit()
//  [Description]:
//
//  [Arguments]:
//                  [BYTE] ucIdx: port index
//  [Return]:
//                  [bool]: TRUE if the message is done, and FALSE for halt
//
//**************************************************************************
enHDCP_Err_Status _drv_HDCPRx_LCInit(BYTE enPortIdx, stHDCPContent* pstHandler)
{
    enHDCPMBX_ERROR_CODE MbxErrCode = MBX_ERR_NONE;

	MbxErrCode = drv_HDCPMBX_SetMsg(enPortIdx, MSG_HDCP22_LC_INIT, MBX_HKR2, MBXMSG_WITH_ARG, MBXMSG_STATE_WAIT,\
                                    MBX_ERR_NONE, (ULONG)&gHdcpMbx_RxBuf[enPortIdx][MSGARG_IDX], RN_SIZE);

    if (MbxErrCode == MBX_ERR_NONE)
    {
        pstHandler->Polling = TRUE;

        //update priority
		_drv_HDCPRx_MsgPoolAssignPriority(enPortIdx, (gHdcpMbx_RxBuf[enPortIdx][0] + DEV_NUM));

        return HDCP_ERR_NONE;
    }
    else
    {
        return HDCP_PROCESS_FAIL;
    }
}

//**************************************************************************
//  [Function Name]:
//                  _drv_HDCPRx_LCSendLPrime()
//  [Description]:
//
//  [Arguments]:
//                  [BYTE] ucIdx: port index
//  [Return]:
//                  [bool]: TRUE if the message is done, and FALSE for halt
//
//**************************************************************************
enHDCP_Err_Status _drv_HDCPRx_LCSendLPrime(BYTE enPortIdx, stHDCPContent* pstHandler)
{
    //update substate
    pstHandler->SubState = LC_Send_L_Prime;

	_drv_HDCPRx_UpdateFromDRAM((ULONG)(&gHdcpMbx_TxBuf[enPortIdx][0]), LPRIME_SIZE);

	pstHandler->SendFunc(enPortIdx, LC_Send_L_Prime, LPRIME_SIZE, (BYTE*)&gHdcpMbx_TxBuf[enPortIdx][0]);

    return HDCP_ERR_NONE;
}

//**************************************************************************
//  [Function Name]:
//                  _drv_HDCPRx_SKESendEks()
//  [Description]:
//
//  [Arguments]:
//                  [BYTE] ucIdx: port index
//  [Return]:
//                  [bool]: TRUE if the message is done, and FALSE for halt
//
//**************************************************************************
static U32 u32AkeTime;
static U32 u32LcInitime;
static U32 u32LcSendLPrime;
static U32 u32SkeTime;


enHDCP_Err_Status _drv_HDCPRx_SKESendEks(BYTE enPortIdx, stHDCPContent* pstHandler)
{
    enHDCPMBX_ERROR_CODE MbxErrCode = MBX_ERR_NONE;

    static U32 u32Cnt;
    u32Cnt++;

    // since we don't use time value for function.
    // we don't handle 32-bit overflow here.
    u32SkeTime=msAPI_Timer_GetTime0();
    printf(HDCP22_ANSI_COLOR_STAGE);
    printf("[HDCP22] Pass. %d times.  timestamp=%d time=%d lc=%d\r\n", u32Cnt, u32SkeTime, u32SkeTime-u32AkeTime , u32LcSendLPrime-u32LcInitime);
    //printf(HDCP22_ANSI_COLOR_OK);
    msDebug_ANSI_AllAttrOffText();

    //printf("send ske message=%d\r\n", u32Cnt);

    if(u8PrintHdcp22DebugInfo)
    {
        msAPI_HDCP22_log_print();
        msAPI_HDCP22_log_reset();
    }

    msAPI_HDCP22_log(EN_HDCP22_ACK,   EN_SKE_MSG);

    MbxErrCode = drv_HDCPMBX_SetMsg(enPortIdx, MSG_HDCP22_SKE_SEND_EKS, MBX_HKR2, MBXMSG_WITH_ARG, MBXMSG_STATE_WAIT,\
                            MBX_ERR_NONE, (ULONG)&gHdcpMbx_RxBuf[enPortIdx][MSGARG_IDX], (EDKEYKS_SIZE + RIV_SIZE));



    //TBD: start cipher
    if(MbxErrCode == MBX_ERR_NONE)
    {
        pstHandler->Polling = TRUE; //FALSE;

        //update priority
        _drv_HDCPRx_MsgPoolAssignPriority(enPortIdx, (gHdcpMbx_RxBuf[enPortIdx][0] + DEV_NUM));
        //_drv_HDCPRx_MsgPoolAssignPriority(enPortIdx, 0x00);

        return HDCP_ERR_NONE;
    }
    else
    {
        return HDCP_PROCESS_FAIL;
    }
}

void _Drv_HDCP_SET_BLOCKCPUTime(U16 u16Blocktime)
{
    if(u16Blocktime != 0)
    {
        g_u16HdcpDedicatedTimeMs = u16Blocktime;
    }
}

//**************************************************************************
//  [Function Name]:
//                  _drv_HDCPRx_FSM()
//  [Description]:
//
//  [Arguments]:
//                  [BYTE] ucIdx: port index
//  [Return]:
//                  [bool]: TRUE if the message is done, and FALSE for halt
//
//**************************************************************************
//extern BYTE Sec2HKFlag;
enHDCP_Err_Status _drv_HDCPRx_FSM(BYTE enPortIdx)
{
    enHDCP_Err_Status enErrCode = HDCP_ERR_NONE;
    enHDCPMBX_MSG_STATE enMessageState = MBXMSG_STATE_IDLE;

#if 1 // debug message
    static enHDCP_RxState_List s_enPreMainState = RxState_B4;
    static enHDCP_Msg_List s_enPreSubState = AKE_Receiver_Info;

    if ((s_enPreMainState!=HdcpHandler[enPortIdx].MainState) || (s_enPreSubState != HdcpHandler[enPortIdx].SubState))
    {
        // ToDo: add delay for nomal work, FIX IT!!!!
        //MsOS_DelayTask(2);
        //printf("%s, %u, %u, %u, %u, %u\n", __func__, __LINE__, HdcpHandler[enPortIdx].MainState, s_enPreMainState, HdcpHandler[enPortIdx].SubState, s_enPreSubState);
        s_enPreMainState = HdcpHandler[enPortIdx].MainState;
        s_enPreSubState = HdcpHandler[enPortIdx].SubState;
    }

    if ((s_enPreMainState!=HdcpHandler[enPortIdx].MainState) == RxState_B3)
    {
        //printf("%s, %u\n", __func__, __LINE__);
        // ToDo: add delay for nomal work, FIX IT!!!!
        //MsOS_DelayTask(2);
    }
#endif

    switch(HdcpHandler[enPortIdx].MainState)
    {
        case RxState_B0:
            switch(HdcpHandler[enPortIdx].SubState)
            {
                case StateZero:
                    //waiting msg
                    break;

                case AKE_Init:
                    enMessageState = drv_HDCPMBX_CheckMsgState(enPortIdx);

                    //check if security r2 process is halt or done;
                    if((enMessageState != MBXMSG_STATE_IDLE) && (enMessageState != MBXMSG_STATE_DONE) && (enMessageState != MBXMSG_STATE_HALT))
                    {
                        HDCP_DRV_DPUTSTR("ake init return\r\n");

                        return HDCP_ERR_NONE;
                    }

                    _drv_HDCPRx_AKEInit(enPortIdx, (stHDCPContent*)&HdcpHandler[enPortIdx]);

                    //update state
                    HdcpHandler[enPortIdx].MainState = RxState_B1;
                    HdcpHandler[enPortIdx].SubState = StateZero;

                    //Move from SECU R2, because SECU R2 cannot access FSC bridge
                    if (enPortIdx==0)
                    {
                        MDrv_WriteByteMask(REG_10069C, 0x00, BIT0); //clear SKE successful
                    }
#if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA) )
                    else if(enPortIdx==1)
                    {
                        MDrv_WriteByteMask(REG_10069C + 0x300, 0x00, BIT0);
                    }
                    else if(enPortIdx==2)
                    {
                        MDrv_WriteByteMask(REG_10069C + 0x600, 0x00, BIT0);
                    }
                    else if(enPortIdx==3)
                    {
                        MDrv_WriteByteMask(REG_10069C + 0x900, 0x00, BIT0);
                    }
#endif
/*
                    else
                    {
                        MDrv_WriteByteMask(0x100B9C, 0x00, BIT0);
                    }
*/
                    //goto RecvAKEInit;
                    break;

                default:
                    enErrCode = HDCP_UNKNOWN_STATE;
                    break;
            };

            break;

        case RxState_B1:
            switch(HdcpHandler[enPortIdx].SubState)
            {
                case StateZero:
                    //AKE_Send_Cert
                    if(drv_HDCPRx_GetR2EventFlag())
                    {
                        gHdcpMbx_RxBuf[enPortIdx][0] = 0; //msg done //update priority
                        drv_HDCPMBX_ClearActiveBit(enPortIdx); //clear active bit

                        HdcpHandler[enPortIdx].Polling = FALSE; //clear polling status

                        _drv_HDCPRx_AKESendCert(enPortIdx, (stHDCPContent*)&HdcpHandler[enPortIdx]);
                        _Drv_HDCP_SET_BLOCKCPUTime(RX_AKE_SEND_CERT);
                    }

                    break;

                case AKE_No_Stored_km:
			_drv_HDCPRx_AKENoStoredKm(enPortIdx, (stHDCPContent*)&HdcpHandler[enPortIdx]);
                    HdcpHandler[enPortIdx].bStoredkm = FALSE;
			HdcpHandler[enPortIdx].SubState = AKE_Send_H_Prime;
                    _Drv_HDCP_SET_BLOCKCPUTime(RX_AKE_SEND_H_PRIME_NO_STORED_KM);
                    break;

                case AKE_Stored_km:
			_drv_HDCPRx_AKEStoredKm(enPortIdx, (stHDCPContent*)&HdcpHandler[enPortIdx]);
                    HdcpHandler[enPortIdx].bStoredkm = TRUE;
			HdcpHandler[enPortIdx].SubState = AKE_Send_H_Prime;
                    _Drv_HDCP_SET_BLOCKCPUTime(RX_AKE_SEND_H_PRIME_STORED_KM);
                    break;

                case AKE_Send_H_Prime:
                    if(drv_HDCPRx_GetR2EventFlag()) // got ISR from SEC R2, means calculation is done
                    {
                        //clear polling status
                        HdcpHandler[enPortIdx].Polling = FALSE;

                        if(HdcpHandler[enPortIdx].bStoredkm == FALSE)
                        {
                            HdcpHandler[enPortIdx].SubState = AKE_Send_Pairing_Info;
                            //drv_HDCPRx_AKEComputePairingInfo(enPortIdx, (stHDCPContent*)&HdcpHandler[enPortIdx]);
                        }
                        else
                        {
                            gHdcpMbx_RxBuf[enPortIdx][0] = 0; //clear priority if stored km, cuz AKE is finished
                            drv_HDCPMBX_ClearActiveBit(enPortIdx); //clear active bit
                        }

                        _drv_HDCPRx_AKESendHPrime(enPortIdx, (stHDCPContent*)&HdcpHandler[enPortIdx]);

                    }

                    break;

                case AKE_Send_Pairing_Info:
                    //make sure TX read data done
                    if(mhal_combo_HDCP2GetReadDownFlag(enPortIdx))
                    {
                        gHdcpMbx_RxBuf[enPortIdx][0] = 0; //clear priority, cuz AKE is finished
                        drv_HDCPMBX_ClearActiveBit(enPortIdx); //clear active bit

                        _drv_HDCPRx_AKESendPairingInfo(enPortIdx, (stHDCPContent*)&HdcpHandler[enPortIdx]);

                        //clear polling status
                        //HdcpHandler[enPortIdx].Polling = FALSE;
                    }

                    break;

                case LC_Init:
			_drv_HDCPRx_LCInit(enPortIdx, (stHDCPContent*)&HdcpHandler[enPortIdx]);
			HdcpHandler[enPortIdx].MainState = RxState_B2;
                    HdcpHandler[enPortIdx].SubState = StateZero;
                    break;

                default:
                    enErrCode = HDCP_UNKNOWN_STATE;
                    break;
            };

            break;

        case RxState_B2:
            switch(HdcpHandler[enPortIdx].SubState)
            {
                case StateZero:
                    if(drv_HDCPRx_GetR2EventFlag())
                    {
                        gHdcpMbx_RxBuf[enPortIdx][0] = 0; //clear priority, cuz LC is finished
                        drv_HDCPMBX_ClearActiveBit(enPortIdx); //clear active bit

                        HdcpHandler[enPortIdx].Polling = FALSE;  //clear polling status

                        _drv_HDCPRx_LCSendLPrime(enPortIdx, (stHDCPContent*)&HdcpHandler[enPortIdx]);
                        u32LcSendLPrime=msAPI_Timer_GetTime0();

                    }

                    break;

                case LC_Init:
                    _drv_HDCPRx_LCInit(enPortIdx, (stHDCPContent*)&HdcpHandler[enPortIdx]);

                    HdcpHandler[enPortIdx].SubState = StateZero; //retry
                    break;

                case SKE_Send_Eks:
                    _drv_HDCPRx_SKESendEks(enPortIdx, (stHDCPContent*)&HdcpHandler[enPortIdx]);

                    HdcpHandler[enPortIdx].MainState = RxState_B3;
                    HdcpHandler[enPortIdx].SubState = StateZero;
                    //goto RecvSKESendEks;
                    break;

                default:
                    enErrCode = HDCP_UNKNOWN_STATE;
                    break;
            };

            break;

        case RxState_B3:
            //compute ks
            if(drv_HDCPRx_GetR2EventFlag())
            {
                gHdcpMbx_RxBuf[enPortIdx][0] = 0; //clear priority
                drv_HDCPMBX_ClearActiveBit(enPortIdx); //clear active bit

                //clear polling status
                HdcpHandler[enPortIdx].Polling = FALSE;

                HdcpHandler[enPortIdx].MainState = RxState_B4;
            }
            // If break, state machine cannot enter B4.
            //break;

        case RxState_B4:
            //authenticated
            HdcpHandler[enPortIdx].AuthDone = TRUE;
            printf("[HDCP]g_u16HdcpDedicatedTimeMs reset\n");
            g_u16HdcpDedicatedTimeMs = 0;
            drv_HDCPMBX_UpdateState(enPortIdx, MBXMSG_STATE_IDLE);

            //Move from SECU R2, because SECU R2 cannot access FSC bridge
            if (enPortIdx==0)
            {
                MDrv_WriteByteMask(REG_10069C, BIT0, BIT0); //set SKE successful
            }
#if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA) )
            else if(enPortIdx==1)
            {
                MDrv_WriteByteMask(REG_10069C + 0x300, BIT0, BIT0);
            }
            else if(enPortIdx==2)
            {
                MDrv_WriteByteMask(REG_10069C + 0x600, BIT0, BIT0);
            }
            else if(enPortIdx==3)
            {
                MDrv_WriteByteMask(REG_10069C + 0x900, BIT0, BIT0);
            }
#endif
            break;

        default:
            enErrCode = HDCP_UNKNOWN_STATE;
            break;
    }; //end of state switch case

    return enErrCode;
}

//**************************************************************************
//  [Function Name]:
//                  _drv_HDCPRx_AKEComputePairingInfo()
//  [Description]:
//
//  [Arguments]:
//                  [BYTE] ucIdx: port index
//  [Return]:
//
//
//**************************************************************************
enHDCP_Err_Status _drv_HDCPRx_AKEComputePairingInfo(BYTE enPortIdx, stHDCPContent* pstHandler)
{
	enHDCPMBX_ERROR_CODE MbxErrCode = MBX_ERR_NONE;

	MbxErrCode = drv_HDCPMBX_SetMsg(enPortIdx, MSG_HDCP22_AKE_SEND_PARING_INFO, MBX_HKR2, MBXMSG_WITHOUT_ARG, MBXMSG_STATE_WAIT,\
									MBX_ERR_NONE, 0x00, 0x00);

	if (MbxErrCode == MBX_ERR_NONE)
	{
		pstHandler->Polling = TRUE;

		//update priority
		_drv_HDCPRx_MsgPoolAssignPriority(enPortIdx, (gHdcpMbx_RxBuf[enPortIdx][0] + DEV_NUM));

		return HDCP_ERR_NONE;
	}
	else
    {
        return HDCP_PROCESS_FAIL;
    }
}

//-------------------------------------------------------------------------------------------------
//  Global Functions
//-------------------------------------------------------------------------------------------------

//**************************************************************************
//  [Function Name]:
//                  drv_HDCPRx_GetTxBufAddr()
//  [Description]:
//
//  [Arguments]:
//
//  [Return]:
//
//
//**************************************************************************
ULONG drv_HDCPRx_GetTxBufAddr(void)
{
    return (ULONG)(&gHdcpMbx_TxBuf[0][0]);
}

//**************************************************************************
//  [Function Name]:
//                  drv_HDCPRx_SetTxBufAddr()
//  [Description]:
//                  initialize variables
//  [Arguments]:
//                  [BYTE] u32Address
//  [Return]:
//                  void
//
//**************************************************************************
void drv_HDCPRx_SetTxBufAddr(U32 u32Address)
{
#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA )
    gHdcpMbx_TxBuf = (volatile BYTE(*)[])MsOS_PA2KSEG0(u32Address);
#else
    gHdcpMbx_TxBuf = (volatile BYTE(*)[])u32Address;
#endif

    printf("Addr of gHdcpMbx_TxBuf = 0x%X\n", (U32)gHdcpMbx_TxBuf);
}

//**************************************************************************
//  [Function Name]:
//                  drv_HDCPRx_SetR2EventFlag()
//  [Description]:
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void drv_HDCPRx_SetR2EventFlag(void)
{

    //printf("***** recevie Security R2 interrupt *****\n");
//    PRINT_SECURITY("***** recevie Security R2 interrupt *****\n");

    ucSecR2EventFlag = 1;
}

//**************************************************************************
//  [Function Name]:
//                  drv_HDCPRx_GetR2EventFlag()
//  [Description]:
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
Bool drv_HDCPRx_GetR2EventFlag(void)
{
    Bool bR2EventFlag = FALSE;


#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA )
    if(MDrv_ReadByte(0x1033CE) == 0xBB)
    {
        MDrv_WriteByte(0x1033CE, 0x00);
        bR2EventFlag = TRUE;
        ucSecR2EventFlag = 0;
    }
#else
    if(ucSecR2EventFlag > 0)
    {
//PRINT_SECURITY("got interrupt");

        bR2EventFlag = TRUE;
        ucSecR2EventFlag = 0;
    }
#endif
    return bR2EventFlag;
}

//**************************************************************************
//  [Function Name]:
//                  drv_HDCPRx_InitCBFunction()
//  [Description]:
//                  initialize variables
//  [Arguments]:
//                  [BYTE] ucPortIdx
//                  [HDCP_SEND_FUNC] pCBFunc: function pointer
//  [Return]:
//                  void
//
//**************************************************************************
void drv_HDCPRx_InitCBFunction(BYTE ucPortIdx, HDCP_SEND_FUNC pCBFunc)
{
    HdcpHandler[ucPortIdx].SendFunc = pCBFunc;
}

void drv_HDCPRx_InitBySystem(void)
{
    U8 uctemp=0; // we have only one HDCP engine in NOS chip
    HdcpHandler[uctemp].MainState = RxState_B0;
    HdcpHandler[uctemp].SubState = StateZero;

    drv_HDCPRx_GetR2EventFlag();
    mhal_tmds_HDCP2CheckWriteStart((MSCombo_TMDS_PORT_INDEX)0);

// mdrv_combo_SetHDCP2CallBackFunction(0x00, mapi_tmds_HDCP2TxEventProc);
// MDrv_Write2Byte(REG_1006C6, 0x8216); // 534);
// MDrv_Write2Byte(REG_1006C6, 0x8000); // 534);

}
//**************************************************************************
//  [Function Name]:
//                  drv_HDCPRx_Init()
//  [Description]:
//                  initialize variables
//  [Arguments]:
//                  [BYTE] ucPortIdx
//  [Return]:
//                  void
//
//**************************************************************************
void drv_HDCPRx_Init(BYTE enPortIdx)
{
    BYTE uctemp = 0;

    if(enPortIdx == HDCP_PORT_ALL)
    {
        for(uctemp = 0; uctemp < DEV_NUM; uctemp++)
        {
            memset((void*)&HdcpHandler[uctemp], 0x00, sizeof(stHDCPContent));

            HdcpHandler[uctemp].bStoredkm = FALSE;
            HdcpHandler[uctemp].MainState = RxState_B0;
            HdcpHandler[uctemp].SubState = StateZero;
            HdcpHandler[uctemp].AuthDone = FALSE;

#if(SUPPORT_REPEATER == 1)
            HdcpHandler[uctemp].rxCaps[0] = 0x02;
            HdcpHandler[uctemp].rxCaps[1] = 0x00;
            HdcpHandler[uctemp].rxCaps[2] = 0x01;

#else
            HdcpHandler[uctemp].rxCaps[0] = 0x02;
            HdcpHandler[uctemp].rxCaps[1] = 0x00;
            HdcpHandler[uctemp].rxCaps[2] = 0x00;

#endif

            HdcpHandler[uctemp].rrx[7] = 0xe1;
            HdcpHandler[uctemp].rrx[6] = 0x7a;
            HdcpHandler[uctemp].rrx[5] = 0xb0;
            HdcpHandler[uctemp].rrx[4] = 0xfd;
            HdcpHandler[uctemp].rrx[3] = 0x0f;
            HdcpHandler[uctemp].rrx[2] = 0x54;
            HdcpHandler[uctemp].rrx[1] = 0x40;
            HdcpHandler[uctemp].rrx[0] = 0x52;
        }
    }
    else
    {
        if( enPortIdx >= DEV_NUM )
        {
            return;
        }

        memset((void*)&HdcpHandler[enPortIdx], 0x00, sizeof(stHDCPContent));

        HdcpHandler[enPortIdx].bStoredkm = FALSE;
        HdcpHandler[enPortIdx].MainState = RxState_B0;
        HdcpHandler[enPortIdx].SubState = StateZero;
        HdcpHandler[enPortIdx].AuthDone = FALSE;

#if(SUPPORT_REPEATER == 1)
        HdcpHandler[enPortIdx].rxCaps[0] = 0x02;
        HdcpHandler[enPortIdx].rxCaps[1] = 0x00;
        HdcpHandler[enPortIdx].rxCaps[2] = 0x01;

#else
        HdcpHandler[enPortIdx].rxCaps[0] = 0x02;
        HdcpHandler[enPortIdx].rxCaps[1] = 0x00;
        HdcpHandler[enPortIdx].rxCaps[2] = 0x00;

#endif

        HdcpHandler[enPortIdx].rrx[7] = 0xe1;
        HdcpHandler[enPortIdx].rrx[6] = 0x7a;
        HdcpHandler[enPortIdx].rrx[5] = 0xb0;
        HdcpHandler[enPortIdx].rrx[4] = 0xfd;
        HdcpHandler[enPortIdx].rrx[3] = 0x0f;
        HdcpHandler[enPortIdx].rrx[2] = 0x54;
        HdcpHandler[enPortIdx].rrx[1] = 0x40;
        HdcpHandler[enPortIdx].rrx[0] = 0x52;
    }
}

//**************************************************************************
//  [Function Name]:
//                  drv_HDCPRx_DecodeKey()
//  [Description]:
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void drv_HDCPRx_DecodeKey(BYTE *pCertRxTable)
{
    enHDCPMBX_ERROR_CODE MbxErrCode = MBX_ERR_NONE;

    MbxErrCode = drv_HDCPMBX_SetKeyMessage(MSG_HDCP22_DECODE_KEY, MBX_HKR2, MBXMSG_WITH_ARG, MBXMSG_STATE_WAIT, \
                                    MBX_ERR_NONE, (ULONG)pCertRxTable, (1 + ENCODE_KEY_SIZE));
}

//**************************************************************************
//  [Function Name]:
//                  drv_HDCPRx_MsgParser()
//  [Description]:
//                  Fetch Message Arguments into HDCP Message Pool
//  [Arguments]:
//                  [BYTE] ucPortIdx
//                  [BYTE] *pucMsg
//  [Return]:
//                  [enHDCP_Err_Status]
//
//**************************************************************************
enHDCP_Err_Status drv_HDCPRx_MsgParser(BYTE ucPortIdx, BYTE *pucMsg)
{
    ULONG dwArgAddr = 0;
    U8 u8MsgID=*(BYTE*)pucMsg;

    dwArgAddr = (ULONG)(&gHdcpMbx_RxBuf[ucPortIdx][MSGID_IDX]);

    msAPI_HDCP22_log(EN_HDCP22_RECEIVE,  u8MsgID);

    switch(*(BYTE*)pucMsg) // first byte, msgID
    {
        case AKE_Init:
            u32AkeTime=msAPI_Timer_GetTime0();
            printf(HDCP22_ANSI_COLOR_STAGE);
            printf("[HDCP22] start authe..... time=%d \n", u32AkeTime);
            //printf(HDCP22_ANSI_COLOR_OK);
            msDebug_ANSI_AllAttrOffText();

            //printf("AKE_INIT %d\n", __LINE__);

            //check if there is other operation on going
            if((HdcpHandler[ucPortIdx].Polling == TRUE))// || (drv_HDCPMBX_CheckMsgState(ucPortIdx)!= MBXMSG_STATE_IDLE))
            {
                HDCP_DRV_DPRINTF("ake init int!! port %d\r\n", ucPortIdx);
                HdcpHandler[ucPortIdx].Polling = FALSE;
                drv_HDCPMBX_UpdateState(ucPortIdx, MBXMSG_STATE_INIT);
            }
            else
            {
                _drv_HDCPMBX_ClrMsgSlot(ucPortIdx);
                drv_HDCPMBX_UpdateState(ucPortIdx, MBXMSG_STATE_IDLE);
            }

            //init
            _drv_HDCPRx_ClrMbxRxBuf(ucPortIdx);

            //update FSM
            HdcpHandler[ucPortIdx].MainState = RxState_B0;
            HdcpHandler[ucPortIdx].SubState = AKE_Init;

            //fetch msg
            memcpy((void*)dwArgAddr, pucMsg, (RTX_SIZE + TXCAPS_SIZE + 1));
            //flush cache
            _drv_HDCPRx_FlushCache(dwArgAddr, gMsgArgLen[AKE_Init]);

		//assign first priority
            _drv_HDCPRx_MsgPoolAssignPriority(ucPortIdx, (DEV_NUM*2 + 1));

            _drv_HDCPRx_ParserMessage(ucPortIdx, gMsgArgLen[AKE_Init]);
            //g_u16HdcpDedicatedTimeMs used for block CPU for HDCP auth,after finished g_u16HdcpDedicatedTimeMs =0
            _Drv_HDCP_SET_BLOCKCPUTime(RX_HDCP_AUTH_BLOCK_CPU_TIME);

            HDCP_DRV_DPRINTF("** HDCP22 receive AKE init port %d \r\n", ucPortIdx);

            break;

        case AKE_No_Stored_km:
            //update FSM
            HdcpHandler[ucPortIdx].SubState = AKE_No_Stored_km;

            //if (gHdcpMbx_RxBuf[ucPortIdx][0] != 0) //already got message
            if(gHdcpMbx_RxBuf[ucPortIdx][0] != 0) //already got message
            {
                return HDCP_PROCESS_FAIL;
            }

            //init
            _drv_HDCPRx_ClrMbxRxBuf(ucPortIdx);

            //fetch msg
            memcpy((void*)dwArgAddr, pucMsg, EKPUBKM_SIZE + 1);

            //flush cache
            _drv_HDCPRx_FlushCache(dwArgAddr, gMsgArgLen[AKE_No_Stored_km]);

            _drv_HDCPRx_MsgPoolFillPriority(ucPortIdx);

            _drv_HDCPRx_ParserMessage(ucPortIdx, gMsgArgLen[AKE_No_Stored_km]);

            HDCP_DRV_DPRINTF("** HDCP22 receive No stored km port %d \r\n", ucPortIdx);

            break;

        case AKE_Stored_km:
            //update FSM
            HdcpHandler[ucPortIdx].SubState = AKE_Stored_km;

            if(gHdcpMbx_RxBuf[ucPortIdx][0] != 0) //already got message
            {
                return HDCP_PROCESS_FAIL;
            }

            //init
            _drv_HDCPRx_ClrMbxRxBuf(ucPortIdx);

            //fetch msg
            memcpy((void*)dwArgAddr, pucMsg, (EKHKM_SIZE + M_SIZE + 1));

            //flush cache
            _drv_HDCPRx_FlushCache(dwArgAddr, gMsgArgLen[AKE_Stored_km]);

            _drv_HDCPRx_MsgPoolFillPriority(ucPortIdx);

            _drv_HDCPRx_ParserMessage(ucPortIdx, gMsgArgLen[AKE_Stored_km]);

            HDCP_DRV_DPRINTF("** HDCP22 receive Stored km port %d \r\n", ucPortIdx);

            break;

        case LC_Init:
            u32LcInitime=msAPI_Timer_GetTime0();

            g_u16HdcpDedicatedTimeMs=(20*3);  // HDCP2.2 spec. 20ms
            msAPI_HDCP22_log(EN_HDCP22_RECEIVE,  EN_LC_INIT_MSG);


            //update FSM
            HdcpHandler[ucPortIdx].SubState = LC_Init;

            if(gHdcpMbx_RxBuf[ucPortIdx][0] != 0) //already got message
            {
                return HDCP_PROCESS_FAIL;
            }

            //init
            _drv_HDCPRx_ClrMbxRxBuf(ucPortIdx);

            //fetch msg
            memcpy((void*)dwArgAddr, pucMsg, RN_SIZE + 1);

            //flush cache
            _drv_HDCPRx_FlushCache(dwArgAddr, gMsgArgLen[LC_Init]);

            _drv_HDCPRx_MsgPoolFillPriority(ucPortIdx);

            _drv_HDCPRx_ParserMessage(ucPortIdx, gMsgArgLen[LC_Init]);

            HDCP_DRV_DPRINTF("** HDCP22 receive LC init port %d \r\n", ucPortIdx);

            break;

        case SKE_Send_Eks:
            //update FSM
            HdcpHandler[ucPortIdx].SubState = SKE_Send_Eks;

            if(gHdcpMbx_RxBuf[ucPortIdx][0] != 0) //already got message
            {
                return HDCP_PROCESS_FAIL;
            }

            //init
            _drv_HDCPRx_ClrMbxRxBuf(ucPortIdx);

            //fetch msg
            memcpy((void*)dwArgAddr, pucMsg, (EDKEYKS_SIZE + RIV_SIZE + 1));

            //flush cache
            _drv_HDCPRx_FlushCache(dwArgAddr, gMsgArgLen[SKE_Send_Eks]);

            _drv_HDCPRx_MsgPoolFillPriority(ucPortIdx);

            _drv_HDCPRx_ParserMessage(ucPortIdx, gMsgArgLen[SKE_Send_Eks]);

            HDCP_DRV_DPRINTF("** HDCP22 receive Send EKS port %d \r\n", ucPortIdx);

            break;

        default:
            return HDCP_UNKNOWN_STATE;
            break;
    }

    return HDCP_ERR_NONE;
}

//**************************************************************************
//  [Function Name]:
//                  drv_HDCP_Handler()
//  [Description]:
//                  HDCP task handler
//  [Arguments]:
//                  void
//  [Return]:
//                  void
//**************************************************************************
void drv_HDCPRx_Handler(void)
{
    BYTE ucIndex = 0;

    //fetch first priority
    ucIndex = _drv_HDCPRx_MsgPoolFetchMsgIdx();

    //printf("priority = %d\r\n", gHdcpMbx_RxBuf[0][0]);

    if(ucIndex != (DEV_NUM + 1))
    {
        _drv_HDCPRx_FSM(ucIndex);
    }
}

#endif // #if (ENABLE_SECU_R2 == 1) && (ENABLE_HDCP22 == 1)

#endif

