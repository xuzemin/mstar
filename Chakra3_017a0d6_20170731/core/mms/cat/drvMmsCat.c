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
extern int CatMenuLevel;
#define    CAT_FUN_MAX   20
#define    CAT_LEVEL_MAX 6


//$  decode func
void CatLevel0Decode(void);
void CatLevel1Decode(void);
void CatLevel2Decode(void);
//$  action func
void CatMainPagePrint(void);
void CatPwPagePrint(void);
void CatSigPagePrint(void);
void MDrv_CatPwDecode(void);
void MDrv_CatPwbAC(void);
void MDrv_CatPwbDC(void);
void MDrv_Cat2PrePage(void);
void MDrv_Cat2Level0Page(void);

extern int DbgMenuLevel;



void CatEyelogprint(void)
{
    printf("                                                                     ,        \n");
    printf("       ]ch                                                         j 0        \n");
    printf("       #& Q,                                                     _0'p0&       \n");
    printf("      ]00&^0g                                                   j0#_000       \n");
    printf("      #000,M00g                                                #00 0000f      \n");
    printf("      00000 Q00&               ____,________,__              _000fj0000#      \n");
    printf("      00000& 0000,     __ppg000000000000000000000Mgpg,_     p000#,000000      \n");
    printf("     ]000000&`00M~ _gg00000000000000000000000000000000000p,_~M00 0000000f     \n");
    printf("     #0000000g^_g00000000000000000000000000000000000000000000g,`j0000000&     \n");
    printf("     #0000000000000000000000000000000000000000000000000000000000000000000     \n");
    printf("     00000000000000000000000000000000000000000000000000000000000000000000     \n");
    printf("     00000000000000000000000000000000000000000000000000000000000000000000c    \n");
    printf("     00000000000000000000000000000000000000000000000000000000000000000000f    \n");
    printf("    ]00000000000000000000000000000000000000000000000000000000000000000000f    \n");
    printf("    ]00000000000000000000000000000000000000000000000000000000000000000000$    \n");
    printf("   _00000~~7MM00000000000000000000000000000000000000000000000000MMM~~00000,   \n");
    printf("   000000&      ~MM0000000000000000000000000000000000000000M~~      #000000c  \n");
    printf("  #00000000,       _~M00000000000000000000000000000000000$,       ,000000000  \n");
    printf("  0000000000g     #BMQEM000000000000000000000000000000MBMQM0     p00000000001 \n");
    printf(" ]00000000000#,  ]#QN0#f M00000000000000000000000000F ]N&0NM&  ,#00000000000& \n");
    printf(" ]0000000000000&,]0M#&Bf  ~000000000000000000000000'   MNQ00!_N0000000000000# \n");
    printf(" ]0000000000000000&00N~     M00000000000000000000P     `#M#Q0000000000000000! \n");
    printf("  #00000000000000000Mgg_     M000000000000000000P    __ggM000000000000000000  \n");
    printf("  `00000000000000000000000ggg,j0000000~~Q000000&ygpN00000000000000000000000F  \n");
    printf("    000000000000000000000000000000000 #0 000000000000000000000000000000000X   \n");
    printf("    ^0MM0M00000000000000000000000000 g00& 00000000000000000M00MMMMM~~~~~M&,___\n");
    printf(" ```~` *ggpggpggg,,_~~~MM0000000000^p0000& 00000000MF~~,gggggM00N0M0000^      \n");
    printf("        `M000000000000000Ng0000000# 000000fj0000000M000#MM0MM0M000M00~        \n");
    printf("     aw***MMmggggggggggg__j00000000gpg, pgg00000000&gggg00000N00Nm*~~M!**     \n");
    printf("             ~MM00MMM00MMM00000000MM00' 000M0000000@~ ~~~~~~~M0               \n");
    printf("        __,e**@MM-*m0MN0MNM0000000#g_,g&,_,#00000000000000M~^~~~~~**m,        \n");
    printf("                     ~~000000000000000000000000000000MM~^                     \n");
    printf("                           `~~MMMMM0000000000MMM~~`                           \n");
    printf("                                                                              \n");
    printf("                                                                              \n");
    printf("                                                                              \n");
    printf("                                                                              \n");
    printf("   ,p00#0MN(     #NE#f  [QM0QN#MMMV    00#MMMMMM!  B#&    y0Mf  ##B#NNMNN^    \n");
    printf("  jM#M~~~~^     ]&000#   ^~~#0#~ ~^    0MF~ ~~^^    0M&  ,0MF   MM ~~^~~~     \n");
    printf(" ,0#'           #0' #01     00&        RM1______     M0&pB0@    0N,__ ___     \n");
    printf(" #M$           q##  *0N     &NS        0#N0NNMMN      Q0QNP     0QM0M0QBM     \n");
    printf(" 4KR          ,M00WQN0Q$    0&9        #0!``  `        0M8      0N```````     \n");
    printf("  #B0g______  0#M#R@NM0M    #MS        MBg__,_,_,      NM1      #M,______,    \n");
    printf("   7N0M#000S y0#      7#0   0N$        N&QD#00#0f      Q&f      0N&#MNNNM     \n");
    printf("     `~^^`~  ~``       `    ```        ``` `^ ^        '``      ````` ~~`     \n");

}


void CatMainPagePrint(void)
{
    CatEyelogprint();
    printf("\n");
    printf("************************************************************* \n");
    printf(" level = %d\n", CatMenuLevel);
    printf(" -Press '000' goto power  page\n");
    printf(" -Press '001' goto signal page\n");
    printf(" -Press '002' goto channel change page\n");
    printf(" -Press '003' goto program edit page\n");
    printf(" -Press '004' Return to pre-page\n");
    printf(" -Press '005' Return to uart debug main page\n");
    printf(" -Press <ESC> exit uart debug system\n");
    printf("************************************************************* \n");
    printf(":\\M\\Cat>");
}

void CatPwPagePrint(void)
{
    printf("\n");
   printf("************************************************************* \n");
    printf(" level = %d\n", CatMenuLevel);
    printf(" -Press '000' goto ac page\n");
    printf(" -Press '001' goto dc page\n");
    printf(" -Press '002' Return to pre-page\n");
    printf(" -Press '003' Return to uart debug main page\n");
    printf(" -Press <ESC> exit uart debug system\n");
    printf("************************************************************* \n");

    printf(":\\M\\Cat\\PW>");
}


void CatSigPagePrint(void)
{
    printf("\n");
    printf("************************************************************* \n");
    printf(" level = %d\n", CatMenuLevel);
    printf(" -Press '000' Return to pre-page\n");
    printf(" -Press '001' Return to uart debug main page\n");
    printf(" -Press <ESC> exit uart debug system\n");
    printf("************************************************************* \n");

    printf(":\\M\\Cat\\PW>");
}


void (* CatLevel0Action[CAT_FUN_MAX])(void) = {
     CatLevel0Decode, CatLevel1Decode, CatLevel2Decode
};

static void (* CatLevel1Action[CAT_FUN_MAX])(void) = {
    MDrv_CatPwDecode,
};

void (* Catlevel2Action[CAT_FUN_MAX])(void)= {
    MDrv_CatPwbAC, MDrv_CatPwbDC, MDrv_Cat2PrePage,MDrv_Cat2Level0Page
};


void (* CatPrintMenu[CAT_FUN_MAX])(void) = {
    NULL, CatMainPagePrint, CatPwPagePrint, CatSigPagePrint,
};



void MDrv_CatPwbAC(void)
{
    printf("\nEnter MDrv_CatPwbAC\n");
}

void MDrv_CatPwbDC(void)
{
    printf("\nEnter MDrv_CatPwbDC\n");
}



void MDrv_CatPwDecode(void)
{
   // jump to next menu level
   CatMenuLevel ++; // 2
   //
   CatPrintMenu[CatMenuLevel]();
}

void MDrv_Cat2PrePage(void)
{
   CatMenuLevel--;

   CatPrintMenu[DbgMenuLevel]();
}

void MDrv_Cat2Level0Page(void)
{
   CatMenuLevel = 0;

   CatPrintMenu[CatMenuLevel]();
}





void CatLevel0Decode(void)
{
   if((( UART_MENU_CMD0  == 'c') && ( UART_MENU_CMD1  == 'a') && ( UART_MENU_CMD2  == 't')) &&
        (( UART_MENU_CMD0  == 'C') && ( UART_MENU_CMD1  == 'A') && ( UART_MENU_CMD2  == 'T')))
   {
       // set level
       CatMenuLevel = 1;
       //
       if (CatPrintMenu[CatMenuLevel])
           CatPrintMenu[CatMenuLevel]();
       MDrv_MMS_ClearCmd();
   }
}

void CatLevel1Decode(void)
{
    U16 index = (UART_MENU_CMD0-48) << 2 |
                (UART_MENU_CMD1-48) << 1 |
                (UART_MENU_CMD2-48);

    if (index >= CAT_FUN_MAX) {
        if (CatPrintMenu[CatMenuLevel])
            CatPrintMenu[CatMenuLevel]();
    }
    else if (CatLevel1Action[index])
        CatLevel1Action[index]();
    else if (CatPrintMenu[CatMenuLevel])
       CatPrintMenu[CatMenuLevel]();
}


void CatLevel2Decode(void)
{
    U16 index = (UART_MENU_CMD0-48) << 2 |
                (UART_MENU_CMD1-48) << 1 |
                (UART_MENU_CMD2-48);

    if (index >= CAT_FUN_MAX) {
        if (CatPrintMenu[CatMenuLevel])
            CatPrintMenu[CatMenuLevel]();
    } else if (Catlevel2Action[index])
        Catlevel2Action[index]();
    else if (CatPrintMenu[CatMenuLevel])
      CatPrintMenu[CatMenuLevel]();
    }

#endif //ENABLE_MSTV_UART_DEBUG

