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
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (!¡±MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
///@file drvMmsDbg.c
///@brief System functions:Menu mode System debug mode related functions
//
///////////////////////////////////////////////////////////////////////////////


//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
#include "MsCommon.h"
#include "drvUartDebug.h"
#if ( ENABLE_MMS)
#include "drvMmsDisp_if.h"
#include "drvMmsCfg_if.h"

#include "drvMmsCfgBoard_if.h"
#include "drvMmsCfgChip_if.h"
#include "drvMmsCfgSw_if.h"

#define MMS_DEBUG(x)    //x
//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
//config level status declare
U16 Cfg0ActIndex;
U16 Cfg1ActIndex;
U16 Cfg2ActIndex;
U16 Cfg3ActIndex;
U16 Cfg4ActIndex;
U16 Cfg5ActIndex;
U16 Cfg6ActIndex;
U16 Cfg7ActIndex;
U16 Cfg8ActIndex;

void (* CfgLevel0Action[CFG_FUN_MAX])(void);
void (* CfgLevel1Action[CFG_FUN_MAX])(void);
void (* CfgLevel2Action[CFG_FUN_MAX])(void);
void (* CfgLevel3Action[CFG_FUN_MAX])(void);
void (* CfgLevel4Action[CFG_FUN_MAX])(void);
void (* CfgLevel5Action[CFG_FUN_MAX])(void);
void (* CfgLevel6Action[CFG_FUN_MAX])(void);
void (* CfgLevel7Action[CFG_FUN_MAX])(void);
void (* CfgLevel8Action[CFG_FUN_MAX])(void);

//-------------------------------------------------------------------------------------------------
//  Local Structurs
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------
U16 BoardIndex[CFG_LEVEL_MAX];
U16 ChipIndex[CFG_LEVEL_MAX];
U16 SWIndex[CFG_LEVEL_MAX];


//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------
U16 cfg_type = 0;
U16 cfg_level =0;


//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------
//$ Action fucntion declare
void (* CfgSetEnv[CFG_LEVEL_MAX][CFG_FUN_MAX])(void);
void (* CfgSetFlag[CFG_LEVEL_MAX][CFG_FUN_MAX])(void);
void (* CfgShowInfo[CFG_LEVEL_MAX][CFG_FUN_MAX])(void);

//$ Print fucntion
void (* CfgBoardPrint[CFG_LEVEL_MAX][CFG_FUN_MAX])(void);
void (* CfgChipPrint[CFG_LEVEL_MAX][CFG_FUN_MAX])(void);
void (* CfgSWPrint[CFG_LEVEL_MAX][CFG_FUN_MAX])(void);

//$ each level printf page func.
void (* CfgPrintMenu[CFG_LEVEL_MAX])(void) = {
     //page 0            //page 1
    NULL, MDrv_CfgMainPagePrint,
};



//$ Attach function.
void MDrv_Cfg_LevelAct(U8 level, void (*func)(void))
{
    switch(level)
    {
    case CFG_LEVEL_0:
       if( GET_LEVLEL0_CFG_ACT_INDEX < CFG_FUN_MAX ) {
           CfgLevel0Action[GET_LEVLEL0_CFG_ACT_INDEX]= func ;
           GET_LEVLEL0_CFG_ACT_INDEX++;
       } else
           printf("Exceed max func index\n");

       break;

    case CFG_LEVEL_1:
        if( GET_LEVLEL1_CFG_ACT_INDEX < CFG_FUN_MAX ) {
           CfgLevel1Action[GET_LEVLEL1_CFG_ACT_INDEX]= func ;
           GET_LEVLEL1_CFG_ACT_INDEX++;
       } else
           printf("Exceed max func index\n");

       break;

    case CFG_LEVEL_2:
       if( GET_LEVLEL2_CFG_ACT_INDEX < CFG_FUN_MAX ) {
           CfgLevel2Action[GET_LEVLEL2_CFG_ACT_INDEX]= func ;
           GET_LEVLEL2_CFG_ACT_INDEX++;
       } else
           printf("Exceed max func index\n");

       break;
    case CFG_LEVEL_3:
        if( GET_LEVLEL3_CFG_ACT_INDEX < CFG_FUN_MAX ) {
           CfgLevel3Action[GET_LEVLEL3_CFG_ACT_INDEX]= func ;
           GET_LEVLEL2_CFG_ACT_INDEX++;
       } else
           printf("Exceed max func index\n");

       break;

    case CFG_LEVEL_4:
        if( GET_LEVLEL4_CFG_ACT_INDEX < CFG_FUN_MAX ) {
           CfgLevel4Action[GET_LEVLEL4_CFG_ACT_INDEX]= func ;
           GET_LEVLEL4_CFG_ACT_INDEX++;
       } else
           printf("Exceed max func index\n");

       break;

    case CFG_LEVEL_5:
        if( GET_LEVLEL5_CFG_ACT_INDEX < CFG_FUN_MAX ) {
           CfgLevel5Action[GET_LEVLEL5_CFG_ACT_INDEX]= func ;
           GET_LEVLEL5_CFG_ACT_INDEX++;
       } else
           printf("Exceed max func index\n");

       break;

    case CFG_LEVEL_6:
        if( GET_LEVLEL6_CFG_ACT_INDEX < CFG_FUN_MAX ) {
           CfgLevel6Action[GET_LEVLEL6_CFG_ACT_INDEX]= func ;
           GET_LEVLEL6_CFG_ACT_INDEX++;
       } else
           printf("Exceed max func index\n");

       break;

    case CFG_LEVEL_7:
        if( GET_LEVLEL7_CFG_ACT_INDEX < CFG_FUN_MAX ) {
           CfgLevel7Action[GET_LEVLEL7_CFG_ACT_INDEX]= func ;
           GET_LEVLEL7_CFG_ACT_INDEX++;
       } else
           printf("Exceed max func index\n");

       break;

    case CFG_LEVEL_8:
        if( GET_LEVLEL8_CFG_ACT_INDEX < CFG_FUN_MAX ) {
           CfgLevel8Action[GET_LEVLEL8_CFG_ACT_INDEX]= func ;
           GET_LEVLEL8_CFG_ACT_INDEX++;
       } else
           printf("Exceed max func index\n");

       break;

    default:
       printf("Exceed max level number\n");
       break;
    }
}


void MDrv_Cfg_Board_Act(U8 level, void (*func)(void), void (*help)(void))
{
    //$ Exception
    if (level >= CFG_LEVEL_MAX)
    {
        printf("Exceed level max\n");
        return;
    }

    if (BoardIndex[level] >= CFG_FUN_MAX )
    {
        printf("Exceed func max\n");
        return;
    }

    //$ set callback fucntion
    // level = ip_index
    CfgSetEnv[level][BoardIndex[level]] = func;
    CfgBoardPrint[level][BoardIndex[level]]  = help;


    //$ Increase the action index
    BoardIndex[level]++;

}


void MDrv_Cfg_Chip_Act(U8 level, void (*func)(void), void (*help)(void))
{

    //$ Exception
    if (level >= CFG_LEVEL_MAX)
    {
        printf("Exceed level max\n");
        return;
    }

    if (ChipIndex[level] >= CFG_FUN_MAX)
    {
        printf("Exceed func max\n");
        return;
    }

    //$ Execute.
    CfgSetFlag[level][ChipIndex[level]] = func;
    CfgChipPrint[level][ChipIndex[level]] = help;

    //$
    ChipIndex[level]++;
}


void MDrv_Cfg_SW_Act(U8 level, void (*func)(void), void (*help)(void))
{

    //$ Exception
    if (level >= CFG_LEVEL_MAX)
    {
        printf("Exceed level max\n");
        return;
    }

    if (SWIndex[level] >= CFG_FUN_MAX)
    {
        printf("Exceed func max\n");
        return;
    }

    //$ Execute.
    CfgShowInfo[level][SWIndex[level]] = func;
    CfgSWPrint[level][SWIndex[level]] = help;

    SWIndex[level]++;
}


void MDrv_Cfg_Act(CFG_TYPE_T type, U8 level, void (*func)(void), void (*help)(void) )
{
    if (type == BOARD)
        MDrv_Cfg_Board_Act(level, func, help);
    else if (type == CHIP)
        MDrv_Cfg_Chip_Act(level,  func, help);
    else if (type == SW)
        MDrv_Cfg_SW_Act(level, func, help);
}


void MDrv_Cfg_BoardMenuPrint(void)
{
    U16 i;
    printf("\n");
    printf("************************************************************* \n");
    for(i = 0 ; i < BoardIndex[cfg_level]; i++)
        if( CfgBoardPrint[cfg_level][i])
        {
            if (i < 9)
                printf(" -Press '00%d' ", i);
            else if (i < 99)
                printf(" -Press '0%d' ", i);
            else if (i < 999)
                printf(" -Press '%d' ", i);

            CfgBoardPrint[cfg_level][i]();
        }
     printf(" -Press <FF>  return to pre-page\n");
     printf(" -Press <ESC> exit uart debug system\n");
     printf("************************************************************* \n");
     printf(":\\M\\cfg\\board>");
}

void MDrv_Cfg_ChipMenuPrint(void)
{
    U16 i;
    printf("\n");
    printf("************************************************************* \n");
    for(i = 0 ; i < ChipIndex[cfg_level]; i++)
        if( CfgChipPrint[cfg_level][i])
        {
            if (i < 9)
                printf(" -Press '00%d' ", i);
            else if (i < 99)
                printf(" -Press '0%d' ", i);
            else if (i < 999)
                printf(" -Press '%d' ", i);

            CfgChipPrint[cfg_level][i]();
        }
    printf(" -Press <FF>  return to pre-page\n");
    printf(" -Press <ESC> exit uart debug system\n");
    printf("************************************************************* \n");
    printf(":\\M\\cfg\\chip>");
}

void MDrv_Cfg_SWMenuPrint(void)
{
    U16 i;
    printf("\n");
    printf("************************************************************* \n");
    for(i = 0 ; i < SWIndex[cfg_level]; i++)
        if( CfgSWPrint[cfg_level][i])
        {
            if (i < 9)
                printf(" -Press '00%d' ", i);
            else if (i < 99)
                printf(" -Press '0%d' ", i);
            else if (i < 999)
                printf(" -Press '%d' ", i);

            CfgSWPrint[cfg_level][i]();
        }
     printf(" -Press <FF>  return to pre-page\n");
     printf(" -Press <ESC> exit uart debug system\n");
     printf("************************************************************* \n");
     printf(":\\M\\cfg\\SW>");
}


void MCfg_BoardDbgDecode(void)
{
    // jump to next menu level (for old design)
    CfgMenuLevel = 2;

    // set type as driver
    MDrv_Cfg_SetType(BOARD);

    // print each item
    MDrv_Cfg_BoardMenuPrint();
}
void MCfg_ChipDbgDecode(void)
{
    CfgMenuLevel = 2;
    MDrv_Cfg_SetType(CHIP);
    MDrv_Cfg_ChipMenuPrint();
}

void MCfg_SWDbgDecode(void)
{
    CfgMenuLevel = 2;
    MDrv_Cfg_SetType(SW);
    MDrv_Cfg_SWMenuPrint();
}

void MCfg_BoardDbg2Level0Page(void)
{
   CfgMenuLevel = 0;

   CfgPrintMenu[CfgMenuLevel]();
}

void MDrv_CfgGotoPrePage(void)
{
    if (cfg_level > 0)
        cfg_level--;
    else
        printf("Exceed the min level\n");
}

void MDrv_CfgGotoSWMainPage(void)
{
   cfg_level = 0;
   MDrv_Cfg_SWMenuPrint();
}

void MDrv_CfgGotoSWMainPagePrint(void)
{
    printf("Goto SW main Page\n");
}

void MDrv_CfgGotoChipMainPage(void)
{
   cfg_level = 0;
   MDrv_Cfg_ChipMenuPrint();
}

void MDrv_CfgGotoChipMainPagePrint(void)
{
    printf("Goto Chip main Page\n");
}

void MDrv_CfgGotoBoardMainPage(void)
{
   cfg_level = 0;
   MDrv_Cfg_BoardMenuPrint();
}

void MDrv_CfgGotoBoardMainPagePrint(void)
{
    printf("Goto Board main Page\n");
}

void MDrv_CfgGotoCfgMainPage(void)
{
   cfg_type  = 0;
   cfg_level = 0;

   CfgMenuLevel--;
}


void MDrv_CfgGotoCfgMainPagePrint(void)
{
   printf("Goto main page Page\n");
}


void MDrv_CfgGotoPrePagePrint(void)
{
   printf("Goto previous page Page\n");
}


void MDrv_Cfg_ActInit(void)
{
    //$ level 0
    MDrv_Cfg_LevelAct(CFG_LEVEL_0, CfgLevel0Decode);
    MDrv_Cfg_LevelAct(CFG_LEVEL_0, CfgLevel1Decode);
    MDrv_Cfg_LevelAct(CFG_LEVEL_0, CfgLevel2Decode); //new design

    MDrv_Cfg_LevelAct(CFG_LEVEL_1, MCfg_BoardDbgDecode);   //press '000'
    MDrv_Cfg_LevelAct(CFG_LEVEL_1, MCfg_ChipDbgDecode);   //press '001'
    MDrv_Cfg_LevelAct(CFG_LEVEL_1, MCfg_SWDbgDecode);    //press '002'
}

void MDrv_Cfg_UserActInit(void)
{
    /*** level 2 <-- user use. **/
    //BOARD
    MDrv_Cfg_BoardPanelInit();

    //CHIP
    MDrv_Cfg_ChipWDTInit();
#if (OBA2)
    MDrv_Cfg_ChipRead_RegInit();
    MDrv_Cfg_ChipWrite_RegInit();
    MDrv_Cfg_ChipRead_Reg_I2CInit();
    MDrv_Cfg_ChipWrite_Reg_I2CInit();
    MDrv_Cfg_ChipRead_Multi_Reg_I2CInit();
    MDrv_Cfg_ChipWrite_Mulit_Reg_I2CInit();
    MDrv_Cfg_ChipMap_BankInit();
#endif
    //SW
    MDrv_Cfg_SWUSBInit();
    MDrv_Cfg_SWIRInit();
    MDrv_Cfg_SWUARTInit();
}

void CfgLevel0Decode(void)
{
    if( (( UART_MENU_CMD0  == 'c') && ( UART_MENU_CMD1  == 'f') && ( UART_MENU_CMD2  == 'g') ) ||
        (( UART_MENU_CMD0  == 'C') && ( UART_MENU_CMD1  == 'F') && ( UART_MENU_CMD2  == 'G')))
    {
       // set level
       CfgMenuLevel = 1;
       CfgPrintMenu[CfgMenuLevel]();

       MDrv_MMS_ClearCmd();
   }
}

void CfgLevel1Decode(void)
{
    U16 index = (UART_MENU_CMD0-48) << 2 |
                (UART_MENU_CMD1-48) << 1 |
                (UART_MENU_CMD2-48);

    if ((index >= CFG_FUN_MAX) )
    {
        printf("\nInput is invalid\n");
        if(CfgPrintMenu[CfgMenuLevel])
            CfgPrintMenu[CfgMenuLevel]();
    }
    else if (CfgLevel1Action[index])
    {
        CfgLevel1Action[index]();
    }
    else if(CfgPrintMenu[CfgMenuLevel])
    {
        printf("\nInput is invalid\n");
        CfgPrintMenu[CfgMenuLevel]();
    }
}

void MDrv_Cfg_SetType(CFG_TYPE_T type)
{
    if (type == BOARD)
        cfg_type = BOARD;
    else if (type == CHIP)
        cfg_type = CHIP;
    else if (type == SW)
        cfg_type =SW;
}

void CfgLevel2Decode(void)
{
    //$ get user input data.
    U16 cmd_index = (UART_MENU_CMD0-48) << 2 |
                            (UART_MENU_CMD1-48) << 1 |
                            (UART_MENU_CMD2-48);

    //$ Exception handler
    if (cmd_index >= CFG_FUN_MAX)
    {
        printf("\nInput is invalid\n");
        if (cfg_type == BOARD)
        {
            MDrv_Cfg_BoardMenuPrint();
        } else if (cfg_type == CHIP)
        {
            MDrv_Cfg_ChipMenuPrint();
        } else if (cfg_type == SW)
        {
            MDrv_Cfg_SWMenuPrint();
        }

        return;
    }


    MMS_DEBUG(printf("level2 decode:: cfg_level= %d cfg_type =%d, cmd_index = %d\n", cfg_level, cfg_type, cmd_index));


    if (cfg_type == BOARD)
    {
        if (CfgSetEnv[cfg_level][cmd_index])
            CfgSetEnv[cfg_level][cmd_index]();
    }
    else if (cfg_type == CHIP)
    {
        if (CfgSetFlag[cfg_level][cmd_index])
            CfgSetFlag[cfg_level][cmd_index]();

    }
    else if (cfg_type == SW)
    {
        if (CfgShowInfo[cfg_level][cmd_index])
            CfgShowInfo[cfg_level][cmd_index]();
    }
    else if (cfg_type == 0)
    {
        if(CfgPrintMenu[CfgMenuLevel])
            CfgPrintMenu[CfgMenuLevel]();
    }

}


void CfgLevel3Decode(void)
{
    U16 index = (UART_MENU_CMD0-48) << 2 |
                (UART_MENU_CMD1-48) << 1 |
                (UART_MENU_CMD2-48);

    if (index >= CFG_FUN_MAX) {
     printf("\nInput is invalid\n");
     if(CfgPrintMenu[CfgMenuLevel])
        CfgPrintMenu[CfgMenuLevel]();
    } else if(CfgLevel3Action[index])
        CfgLevel3Action[index]();
    else if(CfgPrintMenu[CfgMenuLevel])
      CfgPrintMenu[CfgMenuLevel]();
}


void CfgLevel4Decode(void)
{
    U16 index = (UART_MENU_CMD0-48) << 2 |
                (UART_MENU_CMD1-48) << 1 |
                (UART_MENU_CMD2-48);

    if (index >= CFG_FUN_MAX) {
        printf("\nInput is invalid\n");
        if(CfgPrintMenu[CfgMenuLevel])
            CfgPrintMenu[CfgMenuLevel]();
    } else if(CfgLevel4Action[index])
        CfgLevel4Action[index]();
    else if(CfgPrintMenu[CfgMenuLevel])
        CfgPrintMenu[CfgMenuLevel]();
}


void Cfgevel5Decode(void)
{
    U16 index = (UART_MENU_CMD0-48) << 2 |
                (UART_MENU_CMD1-48) << 1 |
                (UART_MENU_CMD2-48);

    if (index >= CFG_FUN_MAX) {
        printf("\nInput is invalid\n");
        if(CfgPrintMenu[CfgMenuLevel])
            CfgPrintMenu[CfgMenuLevel]();
    } else if(CfgLevel5Action[index])
        CfgLevel5Action[index]();
    else if(CfgPrintMenu[CfgMenuLevel])
        CfgPrintMenu[CfgMenuLevel]();
}


void MCfg_BoardDbg2PrePage(void)
{
   if(CfgMenuLevel > 0)
       CfgMenuLevel--;
   else
       printf("This the top page\n");

   if (CfgPrintMenu[CfgMenuLevel])
       CfgPrintMenu[CfgMenuLevel]();
}


void MDrv_CfgMainPagePrint(void)
{
    printf("\n");
    printf("************************************************************* \n");
    printf(" -Press '000' board\n");
    printf(" -Press '001' enter CHIP relative setting\n");
    printf(" -Press '002' enter SW relative setting\n");
    printf(" -Press <FF>  return to pre-page\n");
    printf(" -Press <ESC> exit uart debug system\n");
    printf("************************************************************* \n");
    printf(":\\M\\CFG>");
}

#endif // ENABLE_MMS

