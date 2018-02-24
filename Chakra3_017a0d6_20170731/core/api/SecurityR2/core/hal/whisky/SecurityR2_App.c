
#include "drvGlobal.h"
#include "Board.h"
#include "SW_Config.h"
#include "default_option_define.h"
#include "SysInit.h"

#include "SecurityR2_App.h"

#include "mbx_reg_tbl.h"
#include "secure_reg_tbl.h"
#include "msAPI_Timer.h"

#include "debug.h"

//====================================================
//====================================================
//================== general function =======================
//====================================================
//====================================================

static E_SecR2_ROM_Mode Check_SecureR2_ROM_Init_Supervisor(void)
{
	U16 u16Val = MDrv_Read2Byte(CHECK_Init_Supervisor);
	if (u16Val ==R_Check_Not_Ready)
		return E_SECR2_ROM_NOT_READY;

	if (u16Val != R_Check_OK)
		return 	E_SECR2_ROM_INIT_ERROR;

	return E_SECR2_ROM_RUN_DRAM_SUCCESS;
}

static E_SecR2_ROM_Mode Check_SecureR2_ROM_Init_Cache(void)
{
	U16 u16Val = MDrv_Read2Byte(CHECK_Init_Cache);
	if (u16Val ==R_Check_Not_Ready)
		return E_SECR2_ROM_NOT_READY;

	if (u16Val != R_Check_OK)
		return 	E_SECR2_ROM_INIT_ERROR;

	return E_SECR2_ROM_RUN_DRAM_SUCCESS;
}

static E_SecR2_ROM_Mode Check_SecureR2_ROM_Jump_Start(void)
{
	U16 u16Val = MDrv_Read2Byte(CHECK_Jump_Start);
	if (u16Val ==R_Check_Not_Ready)
		return E_SECR2_ROM_NOT_READY;

	if (u16Val != R_Check_OK)
		return 	E_SECR2_ROM_JUMP_START_ERROR;

	return E_SECR2_ROM_RUN_DRAM_SUCCESS;
}

static E_SecR2_ROM_Mode Check_SecureR2_ROM_MBX_Head(void)
{
	U16 u16Val = MDrv_Read2Byte(CHECK_Mailbox_Head);
	if (u16Val ==R_Check_Not_Ready)
		return E_SECR2_ROM_NOT_READY;

	if (u16Val != R_Check_OK)
		return 	E_SECR2_ROM_MBX_HEAD_ERROR;

	return E_SECR2_ROM_RUN_DRAM_SUCCESS;
}

static E_SecR2_ROM_Mode Check_SecureR2_ROM_DRAMOBF(void)
{
	U16 u16Val = MDrv_Read2Byte(CHECK_DRAMOBF_DONE);
	if (u16Val ==R_Check_Not_Ready)
		return E_SECR2_ROM_NOT_READY;

	if (u16Val != R_Check_OK)
		return 	E_SECR2_ROM_DRAMOBF_ERROR;

	return E_SECR2_ROM_RUN_DRAM_SUCCESS;
}

static E_SecR2_ROM_Mode Check_SecureR2_ROM_RC(void)
{
	U16 u16Val = MDrv_Read2Byte(CHECK_RC_LOCK);
	if (u16Val ==R_Check_Not_Ready)
		return E_SECR2_ROM_NOT_READY;

	if (u16Val == R_Check_SEC_RC_CLOCK_ENABLE_ERROR)
		return 	E_SECR2_ROM_RC_CLOCK_ENABLE_ERROR;
	else if (u16Val == R_Check_SEC_RC_LOCK_ERROR)
		return E_SECR2_ROM_RC_LOCK_ERROR;

	return E_SECR2_ROM_RUN_DRAM_SUCCESS;
}

static E_SecR2_ROM_Mode Check_SecureR2_ROM_DRAM_SIZE(void)
{
	U16 u16Val = MDrv_Read2Byte(CHECK_DRAM_SIZE);
	if (u16Val ==R_Check_Not_Ready)
		return E_SECR2_ROM_NOT_READY;

	if (u16Val == R_Check_SEC_DRAMSIZE_LOCK_ERROR)
		return 	E_SECR2_ROM_DRAMSIZE_LOCK_ERROR;
	else if (u16Val == R_Check_SEC_DRAMSIZE_COMP_ERROR)
		return E_SECR2_ROM_DRAMSIZE_COMP_ERROR;

	return E_SECR2_ROM_RUN_DRAM_SUCCESS;
}

static E_SecR2_ROM_Mode Check_SecureR2_ROM_SecureRange(void)
{
	U16 u16Val = MDrv_Read2Byte(CHECK_SecureRange);
	if (u16Val ==R_Check_Not_Ready)
		return E_SECR2_ROM_NOT_READY;

	if (u16Val == R_Check_SEC_STAR_ADDR_ERROR)
		return 	E_SECR2_ROM_STAR_ADDR_ERROR;
	else if (u16Val == R_Check_SEC_END_ADDR_ERROR)
		return E_SECR2_ROM_END_ADDR_ERROR;

	return E_SECR2_ROM_RUN_DRAM_SUCCESS;
}

static E_SecR2_ROM_Mode Check_SecureR2_ROM_Init_RSA(void)
{
	U16 u16Val = MDrv_Read2Byte(CHECK_Init_RSA);
	if (u16Val ==R_Check_Not_Ready)
		return E_SECR2_ROM_NOT_READY;

	if (u16Val != R_Check_OK)
		return 	E_SECR2_ROM_RSA_BUSY;

	return E_SECR2_ROM_RUN_DRAM_SUCCESS;
}

static E_SecR2_ROM_Mode Check_SecureR2_ROM_Init_SHA_Calculate(void)
{
	U16 u16Val = MDrv_Read2Byte(CHECK_SHA_Calculate);
	if (u16Val ==R_Check_Not_Ready)
		return E_SECR2_ROM_NOT_READY;

	if (u16Val != R_Check_OK)
		return 	E_SECR2_ROM_SHA_ERROR;

	return E_SECR2_ROM_RUN_DRAM_SUCCESS;
}

static E_SecR2_ROM_Mode Check_SecureR2_ROM_Init_RSA_Calculate(void)
{
	U16 u16Val = MDrv_Read2Byte(CHECK_RSA_Calculate);
	if (u16Val ==R_Check_Not_Ready)
		return E_SECR2_ROM_NOT_READY;

	if (u16Val != R_Check_OK)
		return 	E_SECR2_ROM_RSA_ERROR;

	return E_SECR2_ROM_RUN_DRAM_SUCCESS;
}

static E_SecR2_ROM_Mode Check_SecureR2_ROM_Init_RSA_SHA_Result(void)
{
	U16 u16Val = MDrv_Read2Byte(CHECK_RSA_SHA_Result);
	if (u16Val ==R_Check_Not_Ready)
		return E_SECR2_ROM_NOT_READY;

	if (u16Val != R_Check_OK)
		return 	E_SECR2_ROM_SHA_RSA_COMP_ERROR;

	return E_SECR2_ROM_RUN_DRAM_SUCCESS;
}

static E_SecR2_ROM_Mode Check_SecureR2_ROM_Init_Jump_DRAM(void)
{
	U16 u16Val = MDrv_Read2Byte(CHECK_Jump_DRAM);
	if (u16Val ==R_Check_Not_Ready)
		return E_SECR2_ROM_NOT_READY;

	if (u16Val != R_Check_OK)
		return 	E_SECR2_ROM_NOT_READY;

	return E_SECR2_ROM_RUN_DRAM_SUCCESS;
}

//====================================================
//====================================================
//====================================================
//====================================================
//====================================================



typedef E_SecR2_ROM_Mode (*ms_check_func)(void);

const ms_check_func  Check_Step_Flow_Tbl[] =
{
	Check_SecureR2_ROM_Init_Supervisor,
	Check_SecureR2_ROM_Init_Cache,
	Check_SecureR2_ROM_Jump_Start,
	Check_SecureR2_ROM_MBX_Head,
	Check_SecureR2_ROM_DRAMOBF,
	Check_SecureR2_ROM_RC,
	Check_SecureR2_ROM_DRAM_SIZE,
	Check_SecureR2_ROM_SecureRange,
	Check_SecureR2_ROM_Init_RSA,
	Check_SecureR2_ROM_Init_SHA_Calculate,
	Check_SecureR2_ROM_Init_RSA_Calculate,
	Check_SecureR2_ROM_Init_RSA_SHA_Result,
	Check_SecureR2_ROM_Init_Jump_DRAM,
	NULL //end
};


E_SecR2_ROM_Mode SecureR2_Query_ROM_State(void)
{
	int step = 0;
	E_SecR2_ROM_Mode bRet;

	while (Check_Step_Flow_Tbl[step] != NULL)
	{
		bRet = Check_Step_Flow_Tbl[step]();

		if (bRet != E_SECR2_ROM_RUN_DRAM_SUCCESS)
		{
            printf(" %s[%d], step:%d error, ret=%d\n", __FUNCTION__, __LINE__, step, bRet);
            msAPI_Timer_Delayms(5);
            return bRet;
		}
		step++;
	}

	return E_SECR2_ROM_RUN_DRAM_SUCCESS;
}


