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



#include "MsCommon.h"
#include "drvUartDebug.h"
#if ( ENABLE_MMS)
#include "drvMmsDisp_if.h"
#include "drvMmsDbg_if.h"
#include "drvMmsDbgDrv_if.h"
#include "drvMmsDbgMw_if.h"
#include "drvMmsDbgAp_if.h"


//$
U16 dbg_type = 0;
U16 dbg_level =0;

//$ each level printf page func.
void (* DbgPrintMenu[DBG_LEVEL_MAX])(void) = {
     //page 0            //page 1                 //page2
    NULL, MDrv_DbgMainPagePrint,
};

//$ Debug level status declare
U16 Dbg0ActIndex;
U16 Dbg1ActIndex;
U16 Dbg2ActIndex;
U16 Dbg3ActIndex;
U16 Dbg4ActIndex;
U16 Dbg5ActIndex;
//
DBG_LEVEL_ACT_DECLARE(0, DBG_FUN_MAX);
DBG_LEVEL_ACT_DECLARE(1, DBG_FUN_MAX);
DBG_LEVEL_ACT_DECLARE(2, DBG_FUN_MAX);
DBG_LEVEL_ACT_DECLARE(3, DBG_FUN_MAX);
DBG_LEVEL_ACT_DECLARE(4, DBG_FUN_MAX);
DBG_LEVEL_ACT_DECLARE(5, DBG_FUN_MAX);

extern int CatMenuLevel;
extern int CfgMenuLevel;
extern int UntMenuLevel;

//$
U16 DbgDrvActIndex   = 0;
U16 DbgMwActIndex    = 0;
U16 DbgApActIndex    = 0;


//$ Action fucntion declare
void (* DbgDrvAction[DBG_LEVEL_MAX][DBG_FUN_MAX])(void);
void (* DbgDrv1Action[DBG_LEVEL_MAX][DBG_FUN_MAX])(void);
void (* DbgMwAction[DBG_LEVEL_MAX][DBG_FUN_MAX])(void);
void (* DbgApAction[DBG_LEVEL_MAX][DBG_FUN_MAX])(void);

//$ Print fucntion
//Driver
void (* DbgDrvPrint[DBG_LEVEL_MAX][DBG_FUN_MAX])(void);
void (* DbgDrv1Print[DBG_LEVEL_MAX][DBG_FUN_MAX])(void);

void (* DbgMwPrint[DBG_LEVEL_MAX][DBG_FUN_MAX])(void);
void (* DbgApPrint[DBG_LEVEL_MAX][DBG_FUN_MAX])(void);



//$
//DRV
U16 DrvActIndex[DBG_LEVEL_MAX];
U16 Drv1ActIndex[DBG_LEVEL_MAX];
U16 MwActIndex[DBG_LEVEL_MAX];
U16 ApActIndex[DBG_LEVEL_MAX];





//$ Attach function.
void MDrv_Dbg_LevelAct(U8 level, void (*func)(void))
{
    switch(level)
    {
    case DBG_LEVEL_0:
       if( GET_LEVLEL0_DBG_ACT_INDEX < DBG_FUN_MAX ) {
           DbgLevel0Action[GET_LEVLEL0_DBG_ACT_INDEX]= func ;
           GET_LEVLEL0_DBG_ACT_INDEX++;
       } else
           printf("Exceed max func index\n");

       break;

    case DBG_LEVEL_1:
        if( GET_LEVLEL1_DBG_ACT_INDEX < DBG_FUN_MAX ) {
           DbgLevel1Action[GET_LEVLEL1_DBG_ACT_INDEX]= func ;
           GET_LEVLEL1_DBG_ACT_INDEX++;
       } else
           printf("Exceed max func index\n");

       break;

    case DBG_LEVEL_2:
       if( GET_LEVLEL2_DBG_ACT_INDEX < DBG_FUN_MAX ) {
           DbgLevel2Action[GET_LEVLEL2_DBG_ACT_INDEX]= func ;
           GET_LEVLEL2_DBG_ACT_INDEX++;
       } else
           printf("Exceed max func index\n");

       break;
    case DBG_LEVEL_3:
        if( GET_LEVLEL3_DBG_ACT_INDEX < DBG_FUN_MAX ) {
           DbgLevel3Action[GET_LEVLEL3_DBG_ACT_INDEX]= func ;
           GET_LEVLEL2_DBG_ACT_INDEX++;
       } else
           printf("Exceed max func index\n");

       break;

    case DBG_LEVEL_4:
        if( GET_LEVLEL4_DBG_ACT_INDEX < DBG_FUN_MAX ) {
           DbgLevel4Action[GET_LEVLEL4_DBG_ACT_INDEX]= func ;
           GET_LEVLEL4_DBG_ACT_INDEX++;
       } else
           printf("Exceed max func index\n");

       break;

    case DBG_LEVEL_5:
        if( GET_LEVLEL5_DBG_ACT_INDEX < DBG_FUN_MAX ) {
           DbgLevel5Action[GET_LEVLEL5_DBG_ACT_INDEX]= func ;
           GET_LEVLEL5_DBG_ACT_INDEX++;
       } else
           printf("Exceed max func index\n");

       break;

    default:
       printf("Exceed max level number\n");
       break;
    }
}



#if 0
void DbgDrvSetFunc(U8 level, void (*func)(void), void (*help)(void) )
{
     //$ set callback fucntion
    DbgDrvAction[level][DrvActIndex[level]] = func;
    DbgDrvPrint[level][DrvActIndex[level]]  = help;
    //$ Increase the action index
    DrvActIndex[level]++;
}

void DbgDrv1SetFunc(U8 level, void (*func)(void), void (*help)(void) )
{
     //$ set callback fucntion
    DbgDrv1Action[level][Drv1ActIndex[level]] = func;
    DbgDrv1Print[level][Drv1ActIndex[level]]  = help;
    //$ Increase the action index
    Drv1ActIndex[level]++;
}


//$
void (* DbgDisp[20])(U8 level, void (*func)(void), void (*help)(void) ) = {
    DbgDrvSetFunc, DbgDrv1SetFunc

};
#endif



//$
void MDrv_Dbg_Drv_Act(U8 level, void (*func)(void), void (*help)(void))
{
    //$ Exception
    if (level >= DBG_LEVEL_MAX)
    {
        printf("Exceed level max\n");
        return;
    }

    if (DrvActIndex[level] >= DBG_FUN_MAX )
    {
        printf("Exceed func max\n");
        return;
    }

    //$ set callback fucntion
    // level = ip_index
    DbgDrvAction[level][DrvActIndex[level]] = func;
    DbgDrvPrint[level][DrvActIndex[level]]  = help;


    //$ Increase the action index
    DrvActIndex[level]++;

}



//$
void MDrv_Dbg_Mw_Act(U8 level, void (*func)(void), void (*help)(void))
{

    //$ Exception
    if (level >= DBG_LEVEL_MAX)
    {
        printf("Exceed level max\n");
        return;
    }

    if (MwActIndex[level] >= DBG_FUN_MAX)
    {
        printf("Exceed func max\n");
        return;
    }

    //$ Excute.
    DbgMwAction[level][MwActIndex[level]] = func;
    DbgMwPrint[level][MwActIndex[level]] = help;

    //$
    MwActIndex[level]++;
}


//$
void MDrv_Dbg_Ap_Act(U8 level, void (*func)(void), void (*help)(void))
{

    //$ Exception
    if (level >= DBG_LEVEL_MAX)
    {
        printf("Exceed level max\n");
        return;
    }

    if (ApActIndex[level] >= DBG_FUN_MAX)
    {
        printf("Exceed func max\n");
        return;
    }

    //$ Excute.
    DbgApAction[level][ApActIndex[level]] = func;
    DbgApPrint[level][ApActIndex[level]] = help;

    //
    ApActIndex[level]++;
}



//$
void MDrv_Dbg_Act(DBG_TYPE_T type,
                  U8 level,
                  void (*func)(void),
                  void (*help)(void)
                  )
{
    //$
    if (type == DRV)
        MDrv_Dbg_Drv_Act(level, func, help);
    else if (type == MW)
        MDrv_Dbg_Mw_Act(level,  func, help);
    else if (type == AP)
        MDrv_Dbg_Ap_Act(level,  func, help);
}


//$
void MDrv_Dbg_DrvMenuPrint(void)
{
    U16 i;
    printf("\n");
    printf("************************************************************* \n");
    for(i = 0 ; i < DrvActIndex[dbg_level]; i++)
        if( DbgDrvPrint[dbg_level][i])
        {
            if (i < 9)
                printf(" -Press '00%d' ", i);
            else if (i < 99)
                printf(" -Press '0%d' ", i);
            else if (i < 999)
                printf(" -Press '%d' ", i);

            DbgDrvPrint[dbg_level][i]();
        }
    printf(" -Press <FF>  return to pre-page\n");
    printf(" -Press <ESC> exit uart debug system\n");
    printf("************************************************************* \n");
    printf(":\\M\\DBG\\Drv>");
}

void MDrv_Dbg_MwMenuPrint(void)
{
    U16 i;
    printf("\n");
    printf("************************************************************* \n");
    for(i = 0 ; i < MwActIndex[dbg_level]; i++)
        if( DbgMwPrint[dbg_level][i])
        {
            if (i < 9)
                printf(" -Press '00%d' ", i);
            else if (i < 99)
                printf(" -Press '0%d' ", i);
            else if (i < 999)
                printf(" -Press '%d' ", i);

            DbgMwPrint[dbg_level][i]();
        }
     printf(" -Press <FF>  return to pre-page\n");
     printf(" -Press <ESC> exit uart debug system\n");
     printf("************************************************************* \n");
     printf(":\\M\\DBG\\Mw>");
}
void MDrv_Dbg_ApMenuPrint(void)
{
    U16 i;
    printf("\n");
    printf("************************************************************* \n");
    for(i = 0 ; i < ApActIndex[dbg_level]; i++)
        if( DbgApPrint[dbg_level][i])
        {
            if (i < 9)
                printf(" -Press '00%d' ", i);
            else if (i < 99)
                printf(" -Press '0%d' ", i);
            else if (i < 999)
                printf(" -Press '%d' ", i);

            DbgApPrint[dbg_level][i]();
        }
    printf(" -Press <FF>  return to pre-page\n");
    printf(" -Press <ESC> exit uart debug system\n");
    printf("************************************************************* \n");
    printf(":\\M\\DBG\\Ap>");
}



//$
#if 0
void MDrv_DrvAddNewPage(void)
{
     // jump to next menu level
     MDrv_DrvDgb2NextPage();

     //$ print nextpage info
     MDrv_Dbg_DrvMenuPrint();

}
#endif

void MDrv_Dbg_DrvGe(void)
{
   int i;
   printf("do someting(GE)....\n");

   for(i=0; i<10;i++) printf(".");
   printf("\n");
}

void MDrv_Dbg_DrvGePrint(void)
{
  printf("Execute GE action\n");
}



void MDrv_Dbg_DrvTsp(void)
{
   int i;
   printf("do someting(TSP)....\n");

   for(i=0; i<10;i++) printf("*");
   printf("\n");
}

void MDrv_Dbg_DrvTspPrint(void)
{
  printf("Execute TSP action\n");
}

void MDrv_Dbg_MwEpg(void)
{
     int i;
   printf("do someting(EPG)....\n");

   for(i=0; i<10;i++) printf("@");
   printf("\n");
}

void MDrv_Dbg_MwEpgPrint(void)
{
  printf("Execute epg action\n");
}


void MDrv_Dbg_MwEpgEntry(void)
{
   dbg_level = EPG;

    //
    MDrv_Dbg_MwMenuPrint();
}

void MDrv_Dbg_MwEpgEntryPrint(void)
{
  printf("Enter EPG page\n");
}





void MDrv_Dbg_MwTtx(void)
{
     int i;
   printf("do someting(TTX)....\n");

   for(i=0; i<10;i++) printf("@");
   printf("\n");
}

void MDrv_Dbg_MwTtxPrint(void)
{
  printf("Execute TTx action\n");
}

void MDrv_Dbg_MwTtxEntry(void)
{
   dbg_level = TTX;

    //
    MDrv_Dbg_MwMenuPrint();
}

void MDrv_Dbg_MwTtxEntryPrint(void)
{
  printf("Enter TTX page\n");
}





void MDrv_Dbg_ApOsd(void)
{
   int i;
   printf("do someting(OSD)....\n");

   for(i=0; i<10;i++) printf("@");
   printf("\n");
}



void MDrv_Dbg_ApOsdPrint(void)
{
  printf("Execute osd action\n");
}




void MDrv_Dbg_SetType(DBG_TYPE_T type);

void MDrv_DrvDbgDecode(void)
{
    // jump to next menu level (for old design)
    DbgMenuLevel = 2;

    // set type as driver
    MDrv_Dbg_SetType(DRV);

    // print each item
    MDrv_Dbg_DrvMenuPrint();
}
void MDrv_MidDbgDecode(void)
{
    // jump to next menu level (for old design)
    DbgMenuLevel = 2;

    // set type as driver
    MDrv_Dbg_SetType(MW);

    // print each item
    MDrv_Dbg_MwMenuPrint();
}

void MDrv_APDbgDecode(void)
{
    // jump to next menu level (for old design)
    DbgMenuLevel = 2;

    // set type as driver
    MDrv_Dbg_SetType(AP);

    // print each item
    MDrv_Dbg_ApMenuPrint();
}

void MDrv_DrvDgb2Level0Page(void)
{
   DbgMenuLevel = 0;

   DbgPrintMenu[DbgMenuLevel]();
}

void MDrv_DbgGotoNextPage(void)
{
   //$
   if (dbg_level < DBG_LEVEL_MAX)
       dbg_level++;
   else {
      printf("Exceed the max level\n");
      return;
   }
}

void MDrv_DbgJump2Page(void)
{
   //$
   if (dbg_level < DBG_LEVEL_MAX && dbg_level+2 <DBG_LEVEL_MAX)
       dbg_level+=2;
   else {
      printf("Exceed the max level\n");
      return;
   }
}


void MDrv_DbgGotoPrePage(void)
{
   //$
   if (dbg_level > 0)
       dbg_level--;
   else {
      printf("Exceed the min level\n");
      return;
   }
}


void MDrv_DbgGotoDrvMainPage(void)
{
   //$
   dbg_level = 0;

   //$
   MDrv_Dbg_DrvMenuPrint();
}

void MDrv_DbgGotoDrvMainPagePrint(void)
{
    printf("Goto DRV main Page\n");
}


void MDrv_DbgGotoDbgMainPage(void)
{
   //$
   dbg_type  = 0;

   dbg_level = 0;


    DbgMenuLevel--;

 //  printf("dbg_type= %d\n", dbg_type);
}


void MDrv_DbgGotoDbgMainPagePrint(void)
{
   printf("Goto main page Page\n");
}


void MDrv_DbgGotoNextPagePrint(void)
{
    printf("Goto Next page Page\n");
}

void MDrv_DbgJump2PagePrint(void)
{
    printf("Goto jump 2Page\n");
}

void MDrv_DbgGotoPrePagePrint(void)
{
   printf("Goto previous page Page\n");
}


void MDrv_Dbg_ActInit(void)
{
    //$ level 0
    MDrv_Dbg_LevelAct(DBG_LEVEL_0, DbgLevel0Decode);
    MDrv_Dbg_LevelAct(DBG_LEVEL_0, DbgLevel1Decode);
    MDrv_Dbg_LevelAct(DBG_LEVEL_0, DbgLevel2Decode); //new design

    //$ level 1  MDrv_ApEntryFunc
    MDrv_Dbg_LevelAct(DBG_LEVEL_1, MDrv_DrvDbgDecode);   //press '000'
    MDrv_Dbg_LevelAct(DBG_LEVEL_1, MDrv_MidDbgDecode);   //press '001'
    MDrv_Dbg_LevelAct(DBG_LEVEL_1, MDrv_APDbgDecode);    //press '002'
    //MDrv_Dbg_LevelAct(DBG_LEVEL_1, MDrv_DrvDgb2PrePage);
    //MDrv_Dbg_LevelAct(DBG_LEVEL_1, MDrv_DrvDgb2Level0Page);
}




void MDrv_Dbg_UserActInit(void)
{
    /*** level 2 <-- user use. **/
    //$ (1) DRV
    //main page - Entry function - IP list

#if 0
    //Execution functoin. (indepent page)
    MDrv_Dbg_Act(DRV, TSP, MDrv_Dbg_DrvTsp, MDrv_Dbg_DrvTspPrint);
    MDrv_Dbg_Act(DRV, GE, MDrv_Dbg_DrvGe, MDrv_Dbg_DrvGePrint);


    //$ (2) MW
    MDrv_Dbg_Act(MW,  MW_MAIN, MDrv_Dbg_MwEpgEntry, MDrv_Dbg_MwEpgEntryPrint);
    MDrv_Dbg_Act(MW,  MW_MAIN, MDrv_Dbg_MwTtxEntry, MDrv_Dbg_MwTtxEntryPrint);

    MDrv_Dbg_Act(MW,  EPG, MDrv_Dbg_MwEpg, MDrv_Dbg_MwEpgPrint);
    MDrv_Dbg_Act(MW,  TTX, MDrv_Dbg_MwTtx, MDrv_Dbg_MwTtxPrint);

    //$ (3) AP
    MDrv_Dbg_Act(AP,  AP_MAIN, MDrv_Dbg_ApOsd, MDrv_Dbg_ApOsdPrint);
#endif
    //$ Example -call MVD initial fucntion
    MDrv_Dbg_DrvMvdInit();
    MDrv_Dbg_DrvAeonInit();

}



void DbgLevel0Decode(void)
{
   if( (( UART_MENU_CMD0  == 'd') && ( UART_MENU_CMD1  == 'b') && ( UART_MENU_CMD2  == 'g')) ||
        (( UART_MENU_CMD0  == 'D') && ( UART_MENU_CMD1  == 'B') && ( UART_MENU_CMD2  == 'G')))
   {
       // set level
       DbgMenuLevel = 1;
       DbgPrintMenu[DbgMenuLevel]();
       MDrv_MMS_ClearCmd();
   }
}


void DbgLevel1Decode(void)
{
    U16 index = (UART_MENU_CMD0-48) << 2 |
                (UART_MENU_CMD1-48) << 1 |
                (UART_MENU_CMD2-48);

    if ((index >= DBG_FUN_MAX) ) {
        if(DbgPrintMenu[DbgMenuLevel])
            DbgPrintMenu[DbgMenuLevel]();
    } else if (DbgLevel1Action[index])
        DbgLevel1Action[index]();
    else if(DbgPrintMenu[DbgMenuLevel])
            DbgPrintMenu[DbgMenuLevel]();
}



void MDrv_Dbg_SetType(DBG_TYPE_T type)
{
    if (type == DRV)
        dbg_type = DRV;
    else if (type == MW)
        dbg_type = MW;
    else if (type == AP)
        dbg_type = AP;
}


//$
void MDrv_DrvEntryFunc(void)
{
    // jump to next menu level
    // MDrv_DrvDgb2NextPage();
    // set action
    MDrv_Dbg_SetType(DRV);
    //
    MDrv_Dbg_DrvMenuPrint();
}


void MDrv_MwEntryFunc(void)
{
    // jump to next menu level
    //MDrv_DrvDgb2NextPage();
    // set action
    MDrv_Dbg_SetType(MW);
    //
    MDrv_Dbg_MwMenuPrint();
}


void MDrv_ApEntryFunc(void)
{
    // jump to next menu level
    //MDrv_DrvDgb2NextPage();
    // set action
    MDrv_Dbg_SetType(AP);
    //
    MDrv_Dbg_ApMenuPrint();
}


#if 0
void DbgLevel2Decode(void)
{
    U16 index = (UART_MENU_CMD0-48) << 2 |
                (UART_MENU_CMD1-48) << 1 |
                (UART_MENU_CMD2-48);

    if (index >= DBG_FUN_MAX) {
        if(DbgPrintMenu[DbgMenuLevel])
            DbgPrintMenu[DbgMenuLevel]();
    } else if(DbgLevel2Action[index])
        DbgLevel2Action[index]();
    else if(DbgPrintMenu[DbgMenuLevel])
         DbgPrintMenu[DbgMenuLevel]();
}
#else
void DbgLevel2Decode(void)
{
    //$ get user input data.
    U16 cmd_index = (UART_MENU_CMD0-48) << 2 |
                    (UART_MENU_CMD1-48) << 1 |
                    (UART_MENU_CMD2-48);

    //$ Exception handler
    if (cmd_index >= DBG_FUN_MAX)
    {
        if (dbg_type == DRV)
        {
            MDrv_Dbg_DrvMenuPrint();
        } else if (dbg_type == MW)
        {
            MDrv_Dbg_MwMenuPrint();
        } else if (dbg_type == AP)
        {
            MDrv_Dbg_ApMenuPrint();
        }

        return;
    }


  // printf("level2 decode:: dbg_level= %d dbg_type =%d, cmd_index = %d\n",
    //    dbg_level, dbg_type, cmd_index);


    //$ Excute
    //Driver
    if (dbg_type == DRV)
    {
        if (DbgDrvAction[dbg_level][cmd_index])
            DbgDrvAction[dbg_level][cmd_index]();
    }

    //MW
    else if (dbg_type == MW)
    {
        if (DbgMwAction[dbg_level][cmd_index])
            DbgMwAction[dbg_level][cmd_index]();

    }

    //AP
    else if (dbg_type == AP)
    {
        if (DbgApAction[dbg_level][cmd_index])
            DbgApAction[dbg_level][cmd_index]();

     //   printf("ap done !!!\n");
    }


    //$
    if (dbg_type == 0)
    {
        if(DbgPrintMenu[DbgMenuLevel])
            DbgPrintMenu[DbgMenuLevel]();
    }

}
#endif



void DbgLevel3Decode(void)
{
    U16 index = (UART_MENU_CMD0-48) << 2 |
                (UART_MENU_CMD1-48) << 1 |
                (UART_MENU_CMD2-48);

    if (index >= DBG_FUN_MAX) {
     if(DbgPrintMenu[DbgMenuLevel])
        DbgPrintMenu[DbgMenuLevel]();
    } else if(DbgLevel3Action[index])
        DbgLevel3Action[index]();
    else if(DbgPrintMenu[DbgMenuLevel])
      DbgPrintMenu[DbgMenuLevel]();
}


void DbgLevel4Decode(void)
{
    U16 index = (UART_MENU_CMD0-48) << 2 |
                (UART_MENU_CMD1-48) << 1 |
                (UART_MENU_CMD2-48);

    if (index >= DBG_FUN_MAX) {
        if(DbgPrintMenu[DbgMenuLevel])
            DbgPrintMenu[DbgMenuLevel]();
    } else if(DbgLevel4Action[index])
        DbgLevel4Action[index]();
    else if(DbgPrintMenu[DbgMenuLevel])
        DbgPrintMenu[DbgMenuLevel]();
}


void DbgLevel5Decode(void)
{
    U16 index = (UART_MENU_CMD0-48) << 2 |
                (UART_MENU_CMD1-48) << 1 |
                (UART_MENU_CMD2-48);

    if (index >= DBG_FUN_MAX) {
        if(DbgPrintMenu[DbgMenuLevel])
            DbgPrintMenu[DbgMenuLevel]();
    } else if(DbgLevel5Action[index])
        DbgLevel5Action[index]();
    else if(DbgPrintMenu[DbgMenuLevel])
        DbgPrintMenu[DbgMenuLevel]();
}


void MDrv_DrvDgb2PrePage(void)
{
   if(DbgMenuLevel > 0)
       DbgMenuLevel--;
   else
       printf("This the top page\n");

   if (DbgPrintMenu[DbgMenuLevel])
       DbgPrintMenu[DbgMenuLevel]();
}



void MDrv_DrvDgbGE(void)
{
   printf("\nSet GE debug level ...\n");

   MDrv_DrvDgb2NextPage();


#if 0 // parameter usage ref.
   //dump parameter table
   MDrv_DumpParaTbl();
   MDrv_GetPara();
   printf("parm0 =%d\n", *parmtbl.para0);
   printf("parm0-1 =%d\n", *(parmtbl.para0+1));
   printf("parm0-2 =%d\n", *(parmtbl.para0+2));

   printf("parm1 =%d\n", *parmtbl.para1);
   printf("parm1-1 =%d\n", *(parmtbl.para1+1));
   printf("parm1-2 =%d\n", *(parmtbl.para1+2));
   MDrv_ClearParaTbl();
#endif

}


void MDrv_DrvDgbGE2(void)
{
   printf("\nSet GE2 debug level ...\n");
}


void MDrv_DrvDgbEpg(void)
{
   printf("\nSet Epg debug level ...\n");
}

void MDrv_DrvDgbSvd(void)
{
    printf("\nSet Svd debug level ...\n");
}



void MDrv_DbgMainPagePrint(void)
{
    printf("\n");
     printf("************************************************************* \n");
    printf(" -Press '000' goto driver debug page\n");
    printf(" -Press '001' goto middle debug page\n");
    printf(" -Press '002' goto AP debug page\n");
    printf(" -Press <FF>  return to pre-page\n");
    printf(" -Press <ESC> exit uart debug system\n");
     printf("************************************************************* \n");
    printf(":\\M\\DBG>");
}



void MDrv_DrvMainPagePrint(void)
{
    // print main menu
    printf("\n");
    printf("************************************************************* \n");
    printf(" -Press '000' goto GE  page\n");
    printf(" -Press '001' goto EPG page\n");
    printf(" -Press '002' goto SVD page\n");
    printf(" -Press <FF>  return to pre-page\n");
    printf(" -Press <ESC> exit uart debug system\n");
    printf("************************************************************* \n");
    printf(":\\M\\DBG\\DRV>");
}


void MDrv_GePagePrint(void)
{
    printf("\n");
    printf("************************************************************* \n");
    printf(" -Press '000' execute GE2 test function \n");
    printf(" -Press <ESC> exit uart debug system\n");
    printf("************************************************************* \n");
    printf(":\\M\\DBG\\DRV\\GE>");
}


#endif //ENABLE_MSTV_UART_DEBUG

