
#include "Board.h"

#if 0//( ENABLE_SECURITY_R2 )

#include "drvGlobal.h"

#include "SW_Config.h"
#include "default_option_define.h"
#include "SysInit.h"
#include "SecurityR2_App.h"
#include "secu_mbx_reg_tbl.h"
#include "debug.h"
#include "drvMBX.h"
#include "SecurityR2_Mbx.h"
#include "drvGlobal.h"



//******************************************************************************


static BOOL g_bMBXInit = FALSE;
static BOOL g_bMBXRecvTrigger = FALSE;

void SecureR2_MBX_RecvCb( MBX_Msg *pMsg, MS_BOOL *pbAddToQueue)
{
	g_bMBXRecvTrigger = TRUE;
	*pbAddToQueue = FALSE;
}


enHDCPMBX_MSG_STATE SecureR2_MBX_RecvMsg(stHDCPMBX_HANDLER *pMsg, enMBX_MSG_TYPE enMsgType)
{
	if (g_bMBXRecvTrigger = FALSE)
		return MBXMSG_STATE_WAIT;

	//HDCP MBX protocol ==
	pMsg->MsgID   = MDrv_ReadByte(MBX_HDCP_MSGID );
	pMsg->Status  = MDrv_ReadByte(MBX_HDCP_STATUS);
	pMsg->ErrCode = MDrv_ReadByte(MBX_HDCP_ERRCODE );
	//pMsg->ArgAddr = MDrv_Read4Byte(MBX_HDCP_ARGADDR,);
	//pMsg->ArgSize = MDrv_Read4Byte(MBX_HDCP_ARGSIZE );


	g_bMBXRecvTrigger = FALSE;
	return MBXMSG_STATE_DONE;
}


enHDCPMBX_MSG_STATE SecureR2_MBX_SendMsg(stHDCPMBX_HANDLER *pMsg, enMBX_MSG_TYPE enMsgType)
{
	MBX_Msg sMsg;
	MBX_Result bRet;
	MBX_Msg *pTMsg = &sMsg;

	pTMsg->eRoleID = E_MBX_CPU_MIPS_VPE1;
	pTMsg->u8MsgClass = E_MBX_CLASS_SECURE_NOWAIT;

    pTMsg->u8Ctrl = pTMsg->u8S0 = pTMsg->u8S1 = 0x0;


	//HDCP MBX protocol ==
	MDrv_WriteByte(MBX_HDCP_MSGID, pMsg->MsgID );
	MDrv_WriteByte(MBX_HDCP_STATUS, pMsg->Status );
	MDrv_WriteByte(MBX_HDCP_ERRCODE, pMsg->ErrCode );
	MDrv_Write4Byte(MBX_HDCP_ARGADDR, pMsg->ArgAddr );
	MDrv_Write4Byte(MBX_HDCP_ARGSIZE, pMsg->ArgSize );

	bRet= MDrv_MBX_SendMsg(pTMsg);

	if (bRet != E_MBX_SUCCESS)
	{
		return MBXMSG_STATE_HALT;
	}
	return MBXMSG_STATE_DONE;

}


enHDCPMBX_MSG_STATE SecureR2_MBX_Init(void)
{
	if (g_bMBXInit == FALSE)
	{
		MDrv_MBX_Init(E_MBX_CPU_MIPS, E_MBX_ROLE_HK, 10000);
		MDrv_MBX_RegisterMSGWithCallBack(E_MBX_CLASS_SECURE_NOWAIT, 5, SecureR2_MBX_RecvCb);
		MDrv_MBX_Enable(TRUE);
	}
	g_bMBXInit = TRUE;

	return MBXMSG_STATE_DONE;
}




//******************************************************************************

#endif // #if( ENABLE_SECURITY_R2 )
