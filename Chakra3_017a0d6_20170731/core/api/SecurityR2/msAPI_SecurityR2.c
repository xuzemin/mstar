//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (��MStar Confidential Information��) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
/// @file   drvdma.c
/// @brief  DRAM BDMA control driver
/// @author MStar Semiconductor Inc.
///
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Include List
////////////////////////////////////////////////////////////////////////////////
#include "Board.h"

#if( ENABLE_SECURITY_R2 )

#define _MSAPI_SECURITYR2_C_

#include "msAPI_SecurityR2.h"
#include "mapi_combo.h"

#include "drvGlobal.h"

#include "SW_Config.h"
#include "default_option_define.h"
#include "SysInit.h"
#include "debug.h"

#include "SecurityR2_Init.h"

#include "msAPI_DrvInit.h"
#include "msAPI_BDMA.h"
#include "ms_decompress.h"
#include "MsCommon.h"

#include "drvMIU.h"

#include "drvCPU.h"

#if 0//def MSOS_TYPE_LINUX
#include <stdlib.h>
#endif

#include <stdlib.h>

#include "sysinfo.h"

#if (ENABLE_FRC_R2)
#include "msAPI_Flash.h"
#endif

#include "msAPI_Timer.h"
#include "msAPI_MIU.h"


#include "MApp_GlobalFunction.h"

#include "drvHDCPMbx.h"
#include "msReg.h"
#include "drvHDCPRx.h"

#include "mdrv_combo.h"   // for #define MASKBIT(a)                          (_BIT((1?a) +1) -_BIT((0?a)))
#include "drvISR.h"
#include "Utl.h"
#include "string.h"


#define DEBUG_SEC_R2(x) //x


////////////////////////////////////////////////////////////////////////////////
// Local defines & local structures
////////////////////////////////////////////////////////////////////////////////

//extern MS_BOOL _bOSD_On;

////////////////////////////////////////////////////////////////////////////////
// Local Global Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// External Funciton
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Global Funciton
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_COPRO_Init()
/// @brief \b Function \b Description : Co-Processor initial
/// @param <IN>        \b None        :
/// @param <OUT>       \b pBinInfo    : Get Bin Information
/// @param <RET>       \b BOOL     : Success or Fail
/// @param <GLOBAL>    \b None        :
////////////////////////////////////////////////////////////////////////////////

// Check Secu_R2 addr...
#if((CHIP_FAMILY_TYPE==CHIP_FAMILY_MAYA))

  #if( LD_ENABLE )
    #include "secu_r2_LD_bin_128.h"
  #else
    #include "secu_r2_bin_128.h"
  #endif

    #if( SECURITY_R2_ADR != SEC_R2_CPU_ADDR )
        #error "SECURITY_R2_ADR != SEC_R2_CPU_ADDR"

    #endif

#elif( CHIP_FAMILY_TYPE==CHIP_FAMILY_WHISKY )
  #if (MEMORY_MAP == MMAP_64MB)
    #include "secu_r2_bin_64.h"
  #endif
#elif(CHIP_FAMILY_TYPE==CHIP_FAMILY_MAZDA)
    #include "secu_r2_bin_256.h"

#endif


static U32 sg_u32BinLength = 0;
void msAPI_SECU_R2_LoadBin(MS_U16 u16BinID, MS_U32 u32_ADR, MS_U32 u32_LEN)
{
    BININFO BinInfo;
    U32 bin_addr = 0;
    BOOLEAN bResult;

    // Fix warning
    u32_LEN=u32_LEN;

#if(HDCP22_PATCH_IN_MAYA)
//    U8 u8MIUProtectSecuR2_LoadBin_ID[2] = { MIU_CLIENT_BDMA_RW, 0xFF};
    // Refine this for SECU R2 Refine
//    U8 u8MIUProtectSecuR2_Run_ID[3] = { MIU_CLIENT_SECURE_R2_RW, MIU_CLIENT_AESDMA_RW, 0xFF};
#else
    U8 u8MIUProtectSecuR2_LoadBin_ID[2] = { MIU_CLIENT_BDMA, 0xFF};
    // Refine this for SECU R2 Refine
    U8 u8MIUProtectSecuR2_Run_ID[3] = { MIU_CLIENT_SECURE_R2, MIU_CLIENT_AESDMA_TOP_RW, 0xFF};
#endif

    if( u16BinID == 0 )
    {
        printf("\nError: SECU_R2 Bin ID Error!");
        return;
    }

    BinInfo.B_ID = u16BinID;
    MDrv_Sys_Get_BinInfo(&BinInfo, &bResult);
    if ( bResult == PASS )
    {
        bin_addr = BinInfo.B_FAddr;
    }
    else
    {
        printf("\n !!ERROR!! [%s] %d\n",__FILE__,__LINE__);
        return;
    }

    DEBUG_SEC_R2( printf("%s(u16BinID=0x%X, u32_ADR=0x%X, u32_LEN=0x%X)\n", __func__, u16BinID, u32_ADR, u32_LEN); );
    DEBUG_SEC_R2( printf("BinInfo.B_FAddr= 0x%X\n",BinInfo.B_FAddr); );
    DEBUG_SEC_R2( printf("BinInfo.B_Len= 0x%X\n",BinInfo.B_Len); );
    DEBUG_SEC_R2( printf("BinInfo.B_IsComp= 0x%X\n",BinInfo.B_IsComp); );


    //fill necessary information for Secu ROM booting
    // FRC_R2 will cleat the MBX, this value should be set before reset Secr R2
    //MDrv_Write4Byte(HDCPMBX_START_ADDR + 0x08, BinInfo.B_Len-8);
    sg_u32BinLength = BinInfo.B_Len-8;


    //MDrv_COPRO_Init_Front();

#if(!HDCP22_PATCH_IN_MAYA)

    // temp solution, after refine HDCP code, remove this condition
    if (Mdrv_MIU_GetSystemMiuSel() == TRUE)
    {
        MDrv_MIU_Set_Protect(MIU1, MIU_PROTECT_GROUP3, &u8MIUProtectSecuR2_LoadBin_ID[0], u32_ADR, (u32_ADR + u32_LEN-1), ENABLE);
    }
    else
    {
        MDrv_MIU_Set_Protect(MIU0, MIU_PROTECT_GROUP3, &u8MIUProtectSecuR2_LoadBin_ID[0], u32_ADR, (u32_ADR + u32_LEN-1), ENABLE);
    }
#endif
    //printf("%s : %s : %u URANIA_TODO: Use OSD buffer instead of POOL_BUFFER, need confirm\n", __FILE__, __FUNCTION__, __LINE__);

//    if( !MDrv_DMA_LoadBin(&BinInfo, _PA2VA(u32_ADR), _PA2VA((POOL_BUFFER_MEMORY_TYPE & MIU1 ?POOL_BUFFER_ADR | MIU_INTERVAL: POOL_BUFFER_ADR)), _PA2VA((POOL_BUFFER_MEMORY_TYPE & MIU1 ? POOL_BUFFER_ADR | MIU_INTERVAL: POOL_BUFFER_ADR)+BUF_FOR_DECOMPRESS_OFFSET1)) )
    if( !MDrv_DMA_LoadBin(&BinInfo, _PA2VA(u32_ADR), _PA2VA(POOL_BUFFER_ADR), _PA2VA( POOL_BUFFER_ADR)+BUF_FOR_DECOMPRESS_OFFSET1) )
    {
        printf("\n!!ERROR!! !Load Bin Fail!\n");
        return;
    }

#if(!HDCP22_PATCH_IN_MAYA)
    // temp solution, after refine HDCP code, remove this condition
    if (Mdrv_MIU_GetSystemMiuSel() == TRUE)
    {
        MDrv_MIU_Set_Protect(MIU1, MIU_PROTECT_GROUP3, &u8MIUProtectSecuR2_Run_ID[0], u32_ADR, (u32_ADR + u32_LEN-1), ENABLE);
    }
    else
    {
        MDrv_MIU_Set_Protect(MIU0, MIU_PROTECT_GROUP3, &u8MIUProtectSecuR2_Run_ID[0], u32_ADR, (u32_ADR + u32_LEN-1), ENABLE);
    }
#endif
}

// maya mmap name
static void msAPI_SecurityR2_LoadBin(void)
{
    msAPI_SECU_R2_LoadBin(BIN_ID_CODE_SECU_R2, SECURITY_R2_ADR, SECURITY_R2_LEN);
}

typedef enum
{
    EN_R2_CPU_CLOCK_RESERVE,
    EN_R2_CPU_CLOCK_320=1,
    EN_R2_CPU_CLOCK_288=2,   // 010
    EN_R2_CPU_CLOCK_240=3,   // 011
    EN_R2_CPU_CLOCK_216=4,   // 100
    EN_R2_CPU_CLOCK_192=5,   // 101
    EN_R2_CPU_CLOCK_144=6,   // 110
    EN_R2_CPU_CLOCK_108=7,   // 111
    EN_R2_CPU_CLOCK_MAX,
} EN_R2_CPU_CLOCK;


EN_R2_CPU_CLOCK msAPI_SecurityR2_ChangeCpuSpeed(EN_R2_CPU_CLOCK clock)
{

#if 0
//h0070	h0070	4	0	reg_ckg_r2_secure
//h0070	h0070	5	5	reg_sw_r2_secure_clk

[4:2]: Select clock source

000 reserved
001 320 MHz
010 288 MHz
011 240 MHz
100 216 MHz
101 192 MHz
110 144 MHz
111 108 MHz
#endif

// Security CPU speed


	// range checking
	if(clock>EN_R2_CPU_CLOCK_MAX)
	{
		clock=EN_R2_CPU_CLOCK_108;
	}

    MDrv_WriteRegBit (0x100BE0, 0, BIT5);   // CPU=12MHz
    MDrv_WriteByteMask(0x100BE0, (clock<<2), MASKBIT(4:2));
    MDrv_WriteRegBit (0x100BE0, 1, BIT5);    // CPU=clock_mux
    return clock;
}


static U32 su32SecureR2InitTime;

#if ENABLE_SECURITY_R2_HDCP22
#if HDCP22_CHECK_KEY_SIGN
static U8 su8Hdcp22KeyMagicStringCorrect=0;
#endif
#endif

void msAPI_SecurityR2_Start(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    U16 u16DramSize=0;
    U8 u8Ret;
    U8 u8DebugMode;
    E_SecR2_Satus status;

    U32 u32ConfirmAdr;
    U32 u32ConfirmLen;

    CHECK_MIU_PROTECT_LOG_AND_CLEAR();

    su32SecureR2InitTime = msAPI_Timer_GetTime0();

#if SKIP_HDCP22
    return;
#endif

    u8Ret=99;
    u8DebugMode=EN_SPU_DEBUG_MODE;

#if (ENABLE_SECURITY_R2_HDCP22)
    g_u16HdcpDedicatedTimeMs=0;
#endif

    // Clear 0x1033C0~DF
#if 1   //clear HDCP mbx
    {
        U8 i;
        for( i = 0; i < 32; i += 2 )
        {
            MDrv_Write2Byte(0x1033C0 + i, 0);
        }
    }
#endif

    msAPI_SecurityR2_LoadBin();     // daniel@


    #if (MEMORY_MAP == MMAP_64MB)
        u16DramSize=64;
    #elif (MEMORY_MAP == MMAP_128MB)   // ( MEMORY_MAP undefined )
        u16DramSize=128;
    #elif (MEMORY_MAP == MMAP_256MB)   // ( MEMORY_MAP undefined )
        u16DramSize=256;
    #endif

    //printf(HDCP22_ANSI_COLOR_OK);
#if 0
bank:0x100E
16bits
doyle.huang(Doyle Huang (¶?¨ó·ì)) 17:18:45
­n°O±o ©¹¥k shift 16bit
>>16
0x5A*2
#endif


#if  (DEBUG_SECURIT_R2_BY_2ND_UART)
//Maya 222B  PAD_GPIO8/PAD_GPIO9  connect I2S_OUT_BCK/I2S_OUT_MCK for Audio output
#if ( (MS_BOARD_TYPE_SEL != BD_MST222B_D01A_S) || (MS_BOARD_TYPE_SEL != BD_MST222F_D01A_S) )
    MDrv_WriteByteMask(0x101E05, (BIT2), (BIT3|BIT2));  // 3nd uart output to 1st selection
    MDrv_WriteByte(0x101EA7, 0x06);  // uart switch to secureR2 uart
#endif
#endif

#if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA) )
    MDrv_WriteByte(0x100a32, 0x00);  // ckg_aes=172MHz
    MDrv_WriteByte(0x10337A, 0xC0);  // ckg_aes=172MHz
#else
    DEBUG_SEC_R2( printf("0x103332=%x\n", MDrv_ReadByte(0x103332)); );
    MDrv_WriteByte(0x103332, 0x00);  // ckg_aes=172MHz
    DEBUG_SEC_R2( printf("0x103332 after=%x\n", MDrv_ReadByte(0x103332)); );
#endif

#if ENABLE_SECURITY_R2_HDCP22
    msAPI_HDCP22_SendKeyToSecurityR2();
#endif

    // alex magic number
    // MDrv_Write2Byte(0x1033BE, 0x3697);
    //@@ MDrv_UART_SetIsPrint(FALSE);

    status=SecurityR2_Init(u16DramSize, SECURITY_R2_ADR, SECURITY_R2_DRAM_CODE_SIZE, SECURITY_R2_ADR, SECURITY_R2_LEN, EN_SPU_DEBUG_MODE);

    DEBUG_SEC_R2( printf("status=%d %s %s\n", status, __DATE__, __TIME__); );

    // alex magic number
    MDrv_WriteByte(0x1033C1, MDrv_ReadByte(0x001ECC));

#if (DEBUG_SECURIT_R2_BY_1ST_UART_DEBUG_PORT)
    MDrv_WriteByte(0x101EA6, 0x06);  // uart switch to secureR2 uart
#endif
    DEBUG_SEC_R2( printf("0x001ECC=%x\n" , MDrv_ReadByte(0x001ECC)); );

    DEBUG_SEC_R2( printf("MMAP.h SECURITY_R2_ADR=0x%x, SECURITY_R2_LEN=0x%X\n", SECURITY_R2_ADR, SECURITY_R2_LEN ); );

    u32ConfirmAdr = MDrv_Read4Byte(HDCP22_MBX_CONFIRM_ADR);
    u32ConfirmLen = MDrv_Read4Byte(HDCP22_MBX_CONFIRM_LEN);

    DEBUG_SEC_R2( printf("SecurityR2.bin: u32ConfirmAdr=0x%x, u32ConfirmLen=0x%x\n", u32ConfirmAdr, u32ConfirmLen); );

    if((SECURITY_R2_ADR!=u32ConfirmAdr) || (SECURITY_R2_LEN!=u32ConfirmLen))
    {//if cpu is ARM,security R2 can't keep up with ARM,let this waring message showing
        printf("\nError: u32ConfirmAdr=0x%X, u32ConfirmLen=0x%X\n", u32ConfirmAdr, u32ConfirmLen);
#if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA) )
        printf("MMAP.h SECURITY_R2_ADR/Len is not match with SecurityR2.bin\n");
#else
        MApp_Fatal_Error("MMAP.h SECURITY_R2_ADR/Len is not match with SecurityR2.bin\n", __FUNCTION__);
#endif
    }

#if 0   // please do not review "disabled codes"; i keep it here for debug
    while(1)
    {
        MsOS_DelayTask(2000);
        printf("adr=%x\n" , MDrv_Read4Byte(HDCP22_MBX_CONFIRM_ADR));
        printf("len=%x\n" ,MDrv_Read4Byte(HDCP22_MBX_CONFIRM_LEN));
    }
#endif

    DEBUG_SEC_R2( printf(ANSI_COLOR_RESET); );

    //D msAPI_Timer_Delayms(2000);

    //msAPI_SecurityR2_ChangeCpuSpeed(EN_R2_CPU_CLOCK_108);
                                    // doyle@
                                    // Maya
                                    // 1. set DRAM size (128MB or 64MB)
                                    // 2. set 80KB start address & length
                                    // 3. set Secure Range start address & length (code area + data area) (64KB+64KB+2MB)
                                    // 4. Mail message infor
                                    // 5. DRAM OBF
                                    // 6. RC clock
                                    // 7. release reset signal of SPU(Security Processor Unit)

                                    // design for debug
                                    //
                                    // U8 msAPI_SecureityR2RomInit(U16 u16DramSize, U32 u32CodeStart, U32 u32CodeLen, U32 u32SecRangeStart, U32 u32SecRangeLen, U8 u8DebugMode);
                                    // u8DebugMode  0: retail mode, 1: debug mode (the function will blocking until finish & more message)
                                    // print time()

                                    // U8 msAPI_SecureityR2RomCheck();  0: pass, 1: NG1, 2:NG2....




#if 0  // Doyle@ will enable this
    u8Ret=msAPI_SecureityR2RomInit( u16DramSize,                    // 64 or 128
                                    SECURITY_R2_ADR,                // u32CodeStart
                                    SECURITY_R2_DRAM_CODE_SIZE,     // u32CodeLen
                                    SECURITY_R2_ADR,                // u32SecRangeStart
                                    SECURITY_R2_LEN,                // u32SecRangeLen
                                    EN_SPU_DEBUG_MODE);             // u8DebugMode

    switch(u8Ret)
    {
        case 0:
            printf("Security CPU is running\n");
            break;

        case 1:
        default:
            printf("Security CPU NG\n");
            break;
    }

    if(u8DebugMode==EN_SPU_RETAIL_MODE)
    {
        printf("Delay 300ms for bringup\n");
        MsOS_DelayTask(300);
    }

#endif
    //enable read/write offset
    MDrv_Write2Byte(REG_1006D0, 0x8000 | (DEF_HDCP2_EKPUBKM_SIZE + 2)); //i2c offset addr

    CHECK_MIU_PROTECT_LOG_AND_CLEAR();
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

#if DEBUG_SECURITY_R2_STOP
void msAPI_SecurityR2_StopSecurityR2(U16 u16Second)
{
    U32 u32ms;
    static U32 u8SecurityStop=0;

    if(u8SecurityStop) return;

    u32ms=u16Second*1000;
    if(msAPI_Timer_GetTime0 ()>u32ms) // 30 seconds
    {
        MDrv_WriteRegBit (0x100BE0, 1, BIT0);   // stop securityR2 clock
        MApp_Fatal_Error("[HDCP22] Intentional to stop security R2.\n", __FUNCTION__);
        u8SecurityStop=1;
    }
}
#endif
void msAPI_SecurityR2_MISCInit(void)
{
    U32 u32CurrentTime;
    u32CurrentTime=msAPI_Timer_GetTime0();
    printf(HDCP22_ANSI_COLOR_STAGE);
    printf("[HDCP22] Handler start at %d ms\n", u32CurrentTime-su32SecureR2InitTime);
    printf("[HDCP22] u32CurrentTime %d ms\n", u32CurrentTime);
    printf("[HDCP22] su32SecureR2InitTimet %d ms\n", su32SecureR2InitTime);
    //printf(HDCP22_ANSI_COLOR_OK);
    //printf(ANSI_COLOR_RESET);
    msDebug_ANSI_AllAttrOffText();
#if ENABLE_SECURITY_R2_HDCP22
    #if HDCP22_CHECK_KEY_SIGN
    if(su8Hdcp22KeyMagicStringCorrect)
    #endif
    {
        drv_HDCPMBX_Init();
        mdrv_combo_HDCP2Initial();
    }
#endif
}

void msAPI_SecurityR2_Handler(void)
{
    U32 u32CurrentTime;
    static U32 u32RunOnce=0;  // use Static U32 for speedup

#if DEBUG_SECURITY_R2_STOP
    msAPI_SecurityR2_StopSecurityR2(30);
#endif

    if(u32RunOnce==0)
    {
        u32RunOnce=1;
        u32CurrentTime=msAPI_Timer_GetTime0();

        printf(HDCP22_ANSI_COLOR_STAGE);
        printf("[HDCP22] Handler start at %d ms\n", u32CurrentTime-su32SecureR2InitTime);
        printf("[HDCP22] u32CurrentTime %d ms\n", u32CurrentTime);
        printf("[HDCP22] su32SecureR2InitTimet %d ms\n", su32SecureR2InitTime);
        //printf(HDCP22_ANSI_COLOR_OK);
        //printf(ANSI_COLOR_RESET);
        msDebug_ANSI_AllAttrOffText();
    }

#if SKIP_HDCP22
    return;
#endif

#if ENABLE_SECURITY_R2_HDCP22
#if HDCP22_CHECK_KEY_SIGN
    if(su8Hdcp22KeyMagicStringCorrect)
#endif
    {
        msAPI_combo_IPHandler();

        // when DVD submit "locality check packet", block CPU for 20ms*3= 60ms
        while(g_u16HdcpDedicatedTimeMs)
        {
            msAPI_combo_IPHandler();
        }
    }
#endif
}


// profile the timing of HDCP2.2 packets

ST_HDCP_LOG ST_HDCP_LOG_ARRAY[ST_HDCP_LOG_MAX];
static U16 u16HdcpLogcnt=0;

void msAPI_HDCP22_log(EN_HDCP_LOG_DIR enHdcpLogDir,  U8 u8MsgID)
{

    if(u16HdcpLogcnt<ST_HDCP_LOG_MAX)
    {
        ST_HDCP_LOG_ARRAY[u16HdcpLogcnt].enHdcpLogDirection=enHdcpLogDir;
        ST_HDCP_LOG_ARRAY[u16HdcpLogcnt].u8MsgID=u8MsgID;
        ST_HDCP_LOG_ARRAY[u16HdcpLogcnt].u32Time=gTimerCount0;

        u16HdcpLogcnt++;
    }
}

void msAPI_HDCP22_log_reset()
{
    u16HdcpLogcnt=0;
}

void msAPI_HDCP22_log_print(void)
{
    U16 i;

    for(i=0;i<u16HdcpLogcnt;i++)
    {
        printf("t=%d ",  ST_HDCP_LOG_ARRAY[i].u32Time);
        printf("id=0x%x ",  ST_HDCP_LOG_ARRAY[i].u8MsgID);
        if(i>1 && i<(u16HdcpLogcnt-1))
        {
            printf ("delta=%d ", ST_HDCP_LOG_ARRAY[i+1].u32Time-ST_HDCP_LOG_ARRAY[i].u32Time );
        }
        printf("type=%d \n",  ST_HDCP_LOG_ARRAY[i].enHdcpLogDirection);
    }
}

#if ENABLE_SECURITY_R2_HDCP22
static U8 su8UseEfuseKey=0;

#define SECURE_STORE_MAGIC_STRING_START_ADDR (32)
#define SECURE_STORE_MAGIC_STRING_SIZE (32)
const  char *magic_string="MSTAR_SECURE_STORE_FILE_MAGIC_ID";

void msAPI_HDCP22_SendKeyToSecurityR2(void)
{
    U8 * pU8KeyBuf;
    U32 i;

#if HDCP22_CHECK_KEY_SIGN
    if(memcmp((U8 *)magic_string, (U8 *)&_u8Hdcp22Key[SECURE_STORE_MAGIC_STRING_START_ADDR], SECURE_STORE_MAGIC_STRING_SIZE)==0)
    {  // pass
        printf(HDCP22_ANSI_COLOR_STAGE);
        printf("[HDCP22] Encrypted-KEY format correct -- Mstar SecureStorm encrypted key.\n");
        //printf(HDCP22_ANSI_COLOR_OK);
        msDebug_ANSI_AllAttrOffText();
        su8Hdcp22KeyMagicStringCorrect=1;
    }
    else
    {  // NG
        MApp_Fatal_Error("[HDCP22] Encrypted-KEY format error -- not encrypt by Mstar SecureStorm.\n", __FUNCTION__);
        return;
    }
#endif

    // force clear DRAM 16+1044+1 bytes
    pU8KeyBuf = (U8*) MsOS_PA2KSEG1(HDCP_KEY_BUFFER_ADR + 0x8000);
    memset(pU8KeyBuf, 0x00, HDCP22_AES_KEY_SIZE+HDCP22_KEY_SIZE+1);  // extra one byte to inform security R2 use internal efuse key or not

    // put AES key to DDR
    for(i=0;i<HDCP22_AES_KEY_SIZE;i++)
    {
        *(pU8KeyBuf+i)=_u8AesKey[i];
    }

    // put Encrypted-HDCP key to DDR
    for(i=0;i<HDCP22_KEY_SIZE;i++)
    {
        *(pU8KeyBuf+i+HDCP22_AES_KEY_SIZE)=_u8Hdcp22Key[i];
    }

    // last byte
    *(pU8KeyBuf+HDCP22_AES_KEY_SIZE+HDCP22_AES_KEY_SIZE)=su8UseEfuseKey;

    MsOS_FlushMemory();

#if 0//(SEC_R2_HDCP22_CHECK_CRC)
    printf("HDCP Key CRC=0x%X\n", msAPI_CRC_Cal(pkey, HDCP22_AES_KEY_SIZE+HDCP22_KEY_SIZE+1) );
#endif


#if DEBUG_HDCP22_KEY_IN_DDR
    printf("[HDCP22] Final stage \n");
    for(i=0; i<HDCP22_AES_KEY_SIZE; i++)
    {
        printf("%x ", *(pU8KeyBuf+i));
        if(i%16==15) printf("\n");
    }

    printf("\n");
    for(i=0; i<HDCP22_KEY_SIZE; i++)
    {
        printf("%x ", *(pU8KeyBuf+i+HDCP22_AES_KEY_SIZE));
        if(i%16==15) printf("\n");
    }
//while(1);
    printf("\n");
#endif

#if DEBUG_HDCP22_KEY_IN_DB
    printf("[HDCP22] Final stage \n");
    for(i=0; i<HDCP22_AES_KEY_SIZE; i++)
    {
        printf("%x ", _u8AesKey[i]);
        if(i%16==15) printf("\n");
    }

    printf("\n");
    for(i=0; i<HDCP22_KEY_SIZE; i++)
    {
        printf("%x ", _u8Hdcp22Key[i]);
        if(i%16==15) printf("\n");
    }

    printf("su8UseEfuseKey=%x ", *(pU8KeyBuf+HDCP22_AES_KEY_SIZE+HDCP22_AES_KEY_SIZE));

    printf("\n");
#endif
}

void msAPI_HDCP22_UseEfuseKey(void)
{
    su8UseEfuseKey=1;
}
#endif




//******************************************************************************

#endif // #if( ENABLE_SECURITY_R2 )

