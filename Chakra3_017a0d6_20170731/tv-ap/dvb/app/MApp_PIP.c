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
/*
++++++++++++++++++++++++++++++++++???????????????++++++++++++++++++++++++++++++++++++++++++??????????????????????++++++++++++++++++++++++++++++++++++++++=++????
++++++++++++++++++++++++++++++++++IIIIIIIIIIIIII????????????????????????????????????????????IIIIIIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++++++++++++++++++++++++++++++++IIIIIIIIIIII????????????????????????????????????????????????IIIIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++++=+IIIIIIIIIII+++++++++++++++?$$$$$$$$$77II??????????I???????????????????????????????????IIIIIIIIIIIIIII?III??????????????????????????????????????????IIIII
+++++++DMMMMMMMMMMMZI++++++++++++=NMMMMMMMMMMMZ$?I77$$$$$$I?????????????????????????????????????IIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++++=8MMMMMMMMMMMMD7=+++++++++IMMMMMMMMMMMMM8OZZ$7I???????????????????????????????????????????IIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++++=8MMMMMMMMMMMMM8++++++++++DMMMMMMMMMMMMMD8$I?????????????????III???????????????????????????IIIIIIIIIIII?III??????????????????????????????????????????IIIII
+++=+?=8MMMMMMMMMMMMMMZZ++++++?DMMMMMMMMMMMMMMZZ???????????????IIIIIIIIIII????????????????????????IIIIIIIIIII?III??????????????????????????????????????????IIIII
+++++I=DMMMMMMMMMMMMMMMN?=++++8MMMMMMMMMMMMMMMZ$??????????????IIIIIIIIIIIIII??????????????????????IIIIIIIIIII?III??????????????????????????????????????????IIIII
+++++I+8MMMMMMMMMMMMMMMMD?=+IDMMMMMMMMMMMMMMMM$$?????????????IIIIIIIIIIIIIIII????????????????????IIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++?I+8MMMMMMMMMMMMMMMMMOI~OMMMMMMMMMMMMMMMMM$$?????????????IIIIIIIIIIIIIIIII????????????IIIIIIIIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++II+8MMMMMMMMMMMNNMMNMND8MMNNMMNNMMMMMMMMMMZ$????????????IZZ8888OZ7IIIIIIIIIIIIIIIIIIIIIIZD7IIIIIIIIIIIIII?IIIIIIIIIII???????????????????????IIIIIIIIIIIIIIII
++++II+8MMMMMMMMMMII????????OOOOOOZ8MMMMMMMMMMZ$??????????ZDMMMMMDDDNND87IIIIIIIIIIIIIII?Z8MMDIIIIIIIIIIIIIII?IIIIIIIIIII???????????????????????IIIIIIIIIIIIIIII
+++III+8MMMMMMMMMMI++++++7$ZZZZZZZOOMMMMMMMMMMZ$??????IINMMMMMMD+IIII7I7DMMIIIIIIII?I8NMMMMMMD?IIIIIIIIIIIIII?IIIIIIIIIII???????????????????????IIIIIIIIIIIIIIII
+++III+8MMMMMMMMMMI+++++I$ZZZZZZZZ$ZMMMMMMMMMMZ$??????IMMMMMMMMMI??????IIO87IIIIII?DMMMMMMMMMD?IIIIIIIIIIIIII?IIIIIIIIIII???????????????????????IIIIIIIIIIIIIIII
++?III+8MMMMMMMMMMI++=$$ZZZZZZZZZIIZMMMMMMMMMMZ$??????MMMMMMMMMMMZ??????????????IIIMMMMMMMMMMD$ZZZZIIIIIIIIII+Z8DDNMMMDDDOO$I?????????????IIIII$ZZZ7IIII7O8887II
+?IIII+8MMMMMMMMMMI++7ZZZZZZZZZZI+IZMMMMMMMMMMZ$????7ZMMMMMMMMMMMM$????????????OMMMMMMMMMMMMMMMMMMNIIIIIIIII8MMMD888DMMMMMMMND$?????????8MMMMMMMMMMOII78MMMMM8?I
+?IIII+8MMMMMMMMMMI?7ZZZZZZZZZZ?++IZMMMMMMMMMMZ$????7ZMMMMMMMMMMMMMM8??????????+++?MMMMMMMMMM8IIIIIIIIIIIZMMM77IIIIIII8MMMMMMMMND?II????8MMMMMMMMMMOODNZII7Z8I7I
?IIIII+8MMMMMMMMMMZZZZZZZZZZZZI+++IZMMMMMMMMMMZ$??????NMMMMMMMMMMMMMMDII??????????IMMMMMMMMMM8IIIIIIIIIIIO8ZI?IIIIIIIIZDMMMMMMMMMD??????8MMMMMMMMMMN8D7IIIIIIIII
?IIIII+8MMMMMMMMMNZZZZZZZZZZZZ++++?ZMMMMMMMMMMZ$??????ZMMMMMMMMMMMMMMMMN7?????????IMMMMMMMMMM8IIIIIIIIIIIIIII?IIIIIIIIZDMMMMMMMMMMI?????8MMMMMMMMMM8IIIIIIIIIIII
?IIIII+8MMMMMMMMN8ZZZZZZZZZZZ?++++?ZMMMMMMMMMMZ$??????I8MMMMMMMMMMMMMMMM8?????????IMMMMMMMMMMO?IIIIIIIIIIIII7I7777777IODMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMMNZZZZZZZZZZZZ7+++++?ZMMMMMMMMMMZ$????????8MMMMMMMMMMMMMMMMDD???????IMMMMMMMMMMO??IIIIIIIII7DMMMMMMMDDMDDNMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMNZZZZZZZZZZZZ$++++++?ZMMMMMMMMMMZ$I????????7NMMMMMMMMMMMMMMMMDI?????IMMMMMMMMMMO????IIIIIZ8MMMMMMMM7III7ONMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMNOZZZZZZZZZZZ7++++++?ZMMMMMMMMMMZ$III??????+IMMMMMMMMMMMMMMMMN$+????IMMMMMMMMMMO????IIII?NMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMMMMNOZZZZZZZZ?++++++?ZMMMMMMMMMMZ$IIII????????ZMMMMMMMMMMMMMMMO?????IMMMMMMMMMMZ?????III$MMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMMMMM?$ZZZZZZ$+++++++?ZMMMMMMMMMMZ$IIIIIIIIII???ZMMMMMMMMMMMMMMDZ????IMMMMMMMMMMZ?????IIIZMMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII=DMMMMMMMMMM?++7ZZZ7?+++++++IZMMMMMMMMMMZ$IIIIIIIIIIIIII7OMMMMMMMMMMMM8?????IMMMMMMMMMMZ????IIIIZMMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?II?II+8MMMMMMMMMMI++?ZOZ7?+++++++?ZMMMMMMMMMMZ$IIII7OZIIIIIIIII8MMMMMMMMMMMZ?????IMMMMMMMMMM$???OOD7IIMMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIMMMMMMMMMMMMMMNNNN8O$I++++?NMNNMMMMMMMMMMMMMMD8I77NM8IIIIIIIIOMMMMMMMMMO??????+8MMMMMMMMMZ??$MM$?IIZMMMMMMMMM?IIIZNMMMMMMMMMMMZ?????8MMMMMMMMMMOIIIIIIIIIIII
?II?MMMMMMMMMMMMMMMMMM88??++++?MMMMMMMMMMMMMMMMMMD8II7IDMMOIIIIIIOMMMMMMMDOIIII??I??NMMMMMMMMMO8MZ$?IIIIZMMMMMMMMZIZ8MDMMMMMMMMMMMO?????8MMMMMMMMMMOIIIIIIIIIIII
?II?DDDDDDDDDDDDDDD8DDZ$++++++?D8D8DDDDDDDDDDDDDDOZIIIIII?7ODMMMMMMMNDZ7?IIIIIII??????ZDMMMMN8Z7??I?IIIIIIIZ8MMMMN8Z??7$ZZZZZZZZZZZ+????IZZZZZZZZZZ7IIIIIIIIIIII
?IIIII++++++++++++++++=+++++++++++IIIIIIIIIIIIIIIIII???I?????I77ZZ77IIIIIIIIIIIII????I???II??????????IIIIIIII?777IIIIIIII???????????????????????IIIIIIIIIIIIIIII
*/
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define MAPP_PIP_C

#include "datatype.h"
#include "Board.h"
#include "msAPI_Global.h"
#include "apiXC.h"
#include "apiXC_Sys.h"
#include "drvXC_HDMI_if.h"
#include "apiXC_Hdmi.h"
#include "apiAUDIO.h"
#include "drvAVD.h"
#include "drvAUDIO.h"
#include "apiXC_Adc.h"
#include "drvPQ.h"
#include "apiXC_Sys.h"

#include "msAPI_audio.h"

#if ENABLE_TTX
#include "mapp_ttx.h"
#endif
#if (MWE_FUNCTION)
#include "apiXC_Ace.h"
#endif
#if MHEG5_ENABLE
#include "MApp_MHEG5_Main.h"
#endif
#include "MApp_Scaler.h"



#include "MApp_PCMode.h"
#include "MApp_XC_PQ.h"
#include "MApp_InputSource.h"
#include "MApp_ChannelChange.h"

#include "MApp_PIP.h"

#include "MApp_UiMenuDef.h"
#include "ZUI_tables_h.inl"

#if ENABLE_DMP
#include "mapp_videoplayer.h"
#include "MApp_DMP_Main.h"
#endif

#if ENABLE_PIP
MS_WINDOW_TYPE m_stMainDispWin ={0,0,0,0};
MS_WINDOW_TYPE m_stSubDispWin ={0,0,0,0};
#define PIP_INPUT_SOURCE_NUM 9
#if 0
static U8 _u8PipTable[PIP_INPUT_SOURCE_NUM][PIP_INPUT_SOURCE_NUM] =
{
/*              DTV, ATV, CVBS, SCART, SV, COMPONENT, VGA, HDMI   storage */
/* DTV */       {0, 0, 0, 0, 0, 1, 1, 1,0,},
/* ATV */       {0, 0, 0, 0, 0, 1, 1, 1,0,},
/* CVBS */      {0, 0, 0, 0, 0, 1, 1, 1,0,},
/* SCART */     {0, 0, 0, 0, 0, 0, 0, 1,0,},
/* SV */        {0, 0, 0, 0, 0, 0, 0, 1,0,},
/* COMPONENT */ {1, 1, 1, 0, 0, 0, 0, 1,0,},
/* VGA */       {1, 1, 1, 0, 0, 0, 0, 1,0,},
/* HDMI */      {1, 1, 1, 1, 1, 1, 1, 0,0,},
/* storage */   {0, 0, 0, 0, 0, 1, 1, 1,0,},
};
#else

/*** DTV *****/
#ifndef PIP_DTVMAIN_DTVSUB_SUPPORT
#define PIP_DTVMAIN_DTVSUB_SUPPORT                      0
#endif


#ifndef PIP_DTVMAIN_ATVSUB_SUPPORT
#define PIP_DTVMAIN_ATVSUB_SUPPORT                      0
#endif


#ifndef PIP_DTVMAIN_CVBSSUB_SUPPORT
#define PIP_DTVMAIN_CVBSSUB_SUPPORT                     0
#endif

#ifndef PIP_DTVMAIN_SCARTSUB_SUPPORT
#define PIP_DTVMAIN_SCARTSUB_SUPPORT                    0
#endif

#ifndef PIP_DTVMAIN_SVSUB_SUPPORT
#define PIP_DTVMAIN_SVSUB_SUPPORT                       0
#endif

#ifndef PIP_DTVMAIN_COMPONENTSUB_SUPPORT
#define PIP_DTVMAIN_COMPONENTSUB_SUPPORT                1
#endif

#ifndef PIP_DTVMAIN_VGASUB_SUPPORT
#define PIP_DTVMAIN_VGASUB_SUPPORT                      1
#endif

#ifndef PIP_DTVMAIN_HDMISUB_SUPPORT
#define PIP_DTVMAIN_HDMISUB_SUPPORT                     1
#endif


#ifndef PIP_DTVMAIN_DMPSUB_SUPPORT
#define PIP_DTVMAIN_DMPSUB_SUPPORT                      0
#endif


/*** ATV ****/
#ifndef PIP_ATVMAIN_DTVSUB_SUPPORT
#define PIP_ATVMAIN_DTVSUB_SUPPORT                      0
#endif


#ifndef PIP_ATVMAIN_ATVSUB_SUPPORT
#define PIP_ATVMAIN_ATVSUB_SUPPORT                      0
#endif


#ifndef PIP_ATVMAIN_CVBSSUB_SUPPORT
#define PIP_ATVMAIN_CVBSSUB_SUPPORT                     0
#endif

#ifndef PIP_ATVMAIN_SCARTSUB_SUPPORT
#define PIP_ATVMAIN_SCARTSUB_SUPPORT                    0
#endif

#ifndef PIP_ATVMAIN_SVSUB_SUPPORT
#define PIP_ATVMAIN_SVSUB_SUPPORT                       0
#endif

#ifndef PIP_ATVMAIN_COMPONENTSUB_SUPPORT
#define PIP_ATVMAIN_COMPONENTSUB_SUPPORT                1
#endif

#ifndef PIP_ATVMAIN_VGASUB_SUPPORT
#define PIP_ATVMAIN_VGASUB_SUPPORT                      1
#endif

#ifndef PIP_ATVMAIN_HDMISUB_SUPPORT
#define PIP_ATVMAIN_HDMISUB_SUPPORT                     1
#endif

#ifndef PIP_ATVMAIN_DMPSUB_SUPPORT
#define PIP_ATVMAIN_DMPSUB_SUPPORT                      0
#endif

/*** CVBS ****/
#ifndef PIP_CVBSMAIN_DTVSUB_SUPPORT
#define PIP_CVBSMAIN_DTVSUB_SUPPORT                     0
#endif


#ifndef PIP_CVBSMAIN_ATVSUB_SUPPORT
#define PIP_CVBSMAIN_ATVSUB_SUPPORT                     0
#endif


#ifndef PIP_CVBSMAIN_CVBSSUB_SUPPORT
#define PIP_CVBSMAIN_CVBSSUB_SUPPORT                    0
#endif

#ifndef PIP_CVBSMAIN_SCARTSUB_SUPPORT
#define PIP_CVBSMAIN_SCARTSUB_SUPPORT                   0
#endif

#ifndef PIP_CVBSMAIN_SVSUB_SUPPORT
#define PIP_CVBSMAIN_SVSUB_SUPPORT                      0
#endif

#ifndef PIP_CVBSMAIN_COMPONENTSUB_SUPPORT
#define PIP_CVBSMAIN_COMPONENTSUB_SUPPORT               1
#endif

#ifndef PIP_CVBSMAIN_VGASUB_SUPPORT
#define PIP_CVBSMAIN_VGASUB_SUPPORT                     1
#endif

#ifndef PIP_CVBSMAIN_HDMISUB_SUPPORT
#define PIP_CVBSMAIN_HDMISUB_SUPPORT                    1
#endif

#ifndef PIP_CVBSMAIN_DMPSUB_SUPPORT
#define PIP_CVBSMAIN_DMPSUB_SUPPORT                     0
#endif


/*** SCART ****/
#ifndef PIP_SCARTMAIN_DTVSUB_SUPPORT
#define PIP_SCARTMAIN_DTVSUB_SUPPORT                    0
#endif


#ifndef PIP_SCARTMAIN_ATVSUB_SUPPORT
#define PIP_SCARTMAIN_ATVSUB_SUPPORT                    0
#endif


#ifndef PIP_SCARTMAIN_CVBSSUB_SUPPORT
#define PIP_SCARTMAIN_CVBSSUB_SUPPORT                   0
#endif

#ifndef PIP_SCARTMAIN_SCARTSUB_SUPPORT
#define PIP_SCARTMAIN_SCARTSUB_SUPPORT                  0
#endif

#ifndef PIP_SCARTMAIN_SVSUB_SUPPORT
#define PIP_SCARTMAIN_SVSUB_SUPPORT                     0
#endif

#ifndef PIP_SCARTMAIN_COMPONENTSUB_SUPPORT
#define PIP_SCARTMAIN_COMPONENTSUB_SUPPORT              0
#endif

#ifndef PIP_SCARTMAIN_VGASUB_SUPPORT
#define PIP_SCARTMAIN_VGASUB_SUPPORT                    0
#endif

#ifndef PIP_SCARTMAIN_HDMISUB_SUPPORT
#define PIP_SCARTMAIN_HDMISUB_SUPPORT                   1
#endif

#ifndef PIP_SCARTMAIN_DMPSUB_SUPPORT
#define PIP_SCARTMAIN_DMPSUB_SUPPORT                    0
#endif


/*** SV ****/
#ifndef PIP_SVMAIN_DTVSUB_SUPPORT
#define PIP_SVMAIN_DTVSUB_SUPPORT                       0
#endif


#ifndef PIP_SVMAIN_ATVSUB_SUPPORT
#define PIP_SVMAIN_ATVSUB_SUPPORT                       0
#endif


#ifndef PIP_SVMAIN_CVBSSUB_SUPPORT
#define PIP_SVMAIN_CVBSSUB_SUPPORT                      0
#endif

#ifndef PIP_SVMAIN_SCARTSUB_SUPPORT
#define PIP_SVMAIN_SCARTSUB_SUPPORT                     0
#endif

#ifndef PIP_SVMAIN_SVSUB_SUPPORT
#define PIP_SVMAIN_SVSUB_SUPPORT                        0
#endif

#ifndef PIP_SVMAIN_COMPONENTSUB_SUPPORT
#define PIP_SVMAIN_COMPONENTSUB_SUPPORT                 0
#endif

#ifndef PIP_SVMAIN_VGASUB_SUPPORT
#define PIP_SVMAIN_VGASUB_SUPPORT                       0
#endif

#ifndef PIP_SVMAIN_HDMISUB_SUPPORT
#define PIP_SVMAIN_HDMISUB_SUPPORT                      1
#endif

#ifndef PIP_SVMAIN_DMPSUB_SUPPORT
#define PIP_SVMAIN_DMPSUB_SUPPORT                       0
#endif


/*** COMPONENT ****/
#ifndef PIP_COMPONENTMAIN_DTVSUB_SUPPORT
#define PIP_COMPONENTMAIN_DTVSUB_SUPPORT                1
#endif


#ifndef PIP_COMPONENTMAIN_ATVSUB_SUPPORT
#define PIP_COMPONENTMAIN_ATVSUB_SUPPORT                1
#endif


#ifndef PIP_COMPONENTMAIN_CVBSSUB_SUPPORT
#define PIP_COMPONENTMAIN_CVBSSUB_SUPPORT               1
#endif

#ifndef PIP_COMPONENTMAIN_SCARTSUB_SUPPORT
#define PIP_COMPONENTMAIN_SCARTSUB_SUPPORT              0
#endif

#ifndef PIP_COMPONENTMAIN_SVSUB_SUPPORT
#define PIP_COMPONENTMAIN_SVSUB_SUPPORT                 0
#endif

#ifndef PIP_COMPONENTMAIN_COMPONENTSUB_SUPPORT
#define PIP_COMPONENTMAIN_COMPONENTSUB_SUPPORT          0
#endif

#ifndef PIP_COMPONENTMAIN_VGASUB_SUPPORT
#define PIP_COMPONENTMAIN_VGASUB_SUPPORT                0
#endif

#ifndef PIP_COMPONENTMAIN_HDMISUB_SUPPORT
#define PIP_COMPONENTMAIN_HDMISUB_SUPPORT               1
#endif

#ifndef PIP_COMPONENTMAIN_DMPSUB_SUPPORT
#define PIP_COMPONENTMAIN_DMPSUB_SUPPORT                0
#endif


/*** VGA ****/
#ifndef PIP_VGAMAIN_DTVSUB_SUPPORT
#define PIP_VGAMAIN_DTVSUB_SUPPORT                      1
#endif


#ifndef PIP_VGAMAIN_ATVSUB_SUPPORT
#define PIP_VGAMAIN_ATVSUB_SUPPORT                      1
#endif


#ifndef PIP_VGAMAIN_CVBSSUB_SUPPORT
#define PIP_VGAMAIN_CVBSSUB_SUPPORT                     1
#endif

#ifndef PIP_VGAMAIN_SCARTSUB_SUPPORT
#define PIP_VGAMAIN_SCARTSUB_SUPPORT                    0
#endif

#ifndef PIP_VGAMAIN_SVSUB_SUPPORT
#define PIP_VGAMAIN_SVSUB_SUPPORT                       0
#endif

#ifndef PIP_VGAMAIN_COMPONENTSUB_SUPPORT
#define PIP_VGAMAIN_COMPONENTSUB_SUPPORT                0
#endif

#ifndef PIP_VGAMAIN_VGASUB_SUPPORT
#define PIP_VGAMAIN_VGASUB_SUPPORT                      0
#endif

#ifndef PIP_VGAMAIN_HDMISUB_SUPPORT
#define PIP_VGAMAIN_HDMISUB_SUPPORT                     1
#endif

#ifndef PIP_VGAMAIN_DMPSUB_SUPPORT
#define PIP_VGAMAIN_DMPSUB_SUPPORT                      0
#endif


/*** HDMI ****/
#ifndef PIP_HDMIMAIN_DTVSUB_SUPPORT
#define PIP_HDMIMAIN_DTVSUB_SUPPORT                     1
#endif


#ifndef PIP_HDMIMAIN_ATVSUB_SUPPORT
#define PIP_HDMIMAIN_ATVSUB_SUPPORT                     1
#endif


#ifndef PIP_HDMIMAIN_CVBSSUB_SUPPORT
#define PIP_HDMIMAIN_CVBSSUB_SUPPORT                    1
#endif

#ifndef PIP_HDMIMAIN_SCARTSUB_SUPPORT
#define PIP_HDMIMAIN_SCARTSUB_SUPPORT                   1
#endif

#ifndef PIP_HDMIMAIN_SVSUB_SUPPORT
#define PIP_HDMIMAIN_SVSUB_SUPPORT                      1
#endif

#ifndef PIP_HDMIMAIN_COMPONENTSUB_SUPPORT
#define PIP_HDMIMAIN_COMPONENTSUB_SUPPORT               1
#endif

#ifndef PIP_HDMIMAIN_VGASUB_SUPPORT
#define PIP_HDMIMAIN_VGASUB_SUPPORT                     1
#endif

#ifndef PIP_HDMIMAIN_HDMISUB_SUPPORT
#define PIP_HDMIMAIN_HDMISUB_SUPPORT                    0
#endif

#ifndef PIP_HDMIMAIN_DMPSUB_SUPPORT
#define PIP_HDMIMAIN_DMPSUB_SUPPORT                     0
#endif


/*** DMP ****/
#ifndef PIP_DMPMAIN_DTVSUB_SUPPORT
#define PIP_DMPMAIN_DTVSUB_SUPPORT                      0
#endif


#ifndef PIP_DMPMAIN_ATVSUB_SUPPORT
#define PIP_DMPMAIN_ATVSUB_SUPPORT                      0
#endif


#ifndef PIP_DMPMAIN_CVBSSUB_SUPPORT
#define PIP_DMPMAIN_CVBSSUB_SUPPORT                     0
#endif

#ifndef PIP_DMPMAIN_SCARTSUB_SUPPORT
#define PIP_DMPMAIN_SCARTSUB_SUPPORT                    0
#endif

#ifndef PIP_DMPMAIN_SVSUB_SUPPORT
#define PIP_DMPMAIN_SVSUB_SUPPORT                       0
#endif

#ifndef PIP_DMPMAIN_COMPONENTSUB_SUPPORT
#define PIP_DMPMAIN_COMPONENTSUB_SUPPORT                1
#endif

#ifndef PIP_DMPMAIN_VGASUB_SUPPORT
#define PIP_DMPMAIN_VGASUB_SUPPORT                      1
#endif

#ifndef PIP_DMPMAIN_HDMISUB_SUPPORT
#define PIP_DMPMAIN_HDMISUB_SUPPORT                     1
#endif

#ifndef PIP_DMPMAIN_DMPSUB_SUPPORT
#define PIP_DMPMAIN_DMPSUB_SUPPORT                      0
#endif

static U8 _u8PipTable[PIP_INPUT_SOURCE_NUM][PIP_INPUT_SOURCE_NUM] =
{
    /* DTV */
    {
        PIP_DTVMAIN_DTVSUB_SUPPORT,       /* DTV */
        PIP_DTVMAIN_ATVSUB_SUPPORT,       /* ATV */
        PIP_DTVMAIN_CVBSSUB_SUPPORT,      /* CVBS */
        PIP_DTVMAIN_SCARTSUB_SUPPORT,     /* SCART */
        PIP_DTVMAIN_SVSUB_SUPPORT,        /* SV */
        PIP_DTVMAIN_COMPONENTSUB_SUPPORT, /* COMPONENT */
        PIP_DTVMAIN_VGASUB_SUPPORT,       /* VGA */
        PIP_DTVMAIN_HDMISUB_SUPPORT,      /* HDMI */
        PIP_DTVMAIN_DMPSUB_SUPPORT,       /* storage */
    },

    /* ATV */
    {
        PIP_ATVMAIN_DTVSUB_SUPPORT,       /* DTV */
        PIP_ATVMAIN_ATVSUB_SUPPORT,       /* ATV */
        PIP_ATVMAIN_CVBSSUB_SUPPORT,      /* CVBS */
        PIP_ATVMAIN_SCARTSUB_SUPPORT,     /* SCART */
        PIP_ATVMAIN_SVSUB_SUPPORT,        /* SV */
        PIP_ATVMAIN_COMPONENTSUB_SUPPORT, /* COMPONENT */
        PIP_ATVMAIN_VGASUB_SUPPORT,       /* VGA */
        PIP_ATVMAIN_HDMISUB_SUPPORT,      /* HDMI */
        PIP_ATVMAIN_DMPSUB_SUPPORT,       /* storage */
    },

    /* CVBS */
    {
        PIP_CVBSMAIN_DTVSUB_SUPPORT,       /* DTV */
        PIP_CVBSMAIN_ATVSUB_SUPPORT,       /* ATV */
        PIP_CVBSMAIN_CVBSSUB_SUPPORT,      /* CVBS */
        PIP_CVBSMAIN_SCARTSUB_SUPPORT,     /* SCART */
        PIP_CVBSMAIN_SVSUB_SUPPORT,        /* SV */
        PIP_CVBSMAIN_COMPONENTSUB_SUPPORT, /* COMPONENT */
        PIP_CVBSMAIN_VGASUB_SUPPORT,       /* VGA */
        PIP_CVBSMAIN_HDMISUB_SUPPORT,      /* HDMI */
        PIP_CVBSMAIN_DMPSUB_SUPPORT,       /* storage */
    },
    /* SCART */
    {
        PIP_SCARTMAIN_DTVSUB_SUPPORT,       /* DTV */
        PIP_SCARTMAIN_ATVSUB_SUPPORT,       /* ATV */
        PIP_SCARTMAIN_CVBSSUB_SUPPORT,      /* CVBS */
        PIP_SCARTMAIN_SCARTSUB_SUPPORT,     /* SCART */
        PIP_SCARTMAIN_SVSUB_SUPPORT,        /* SV */
        PIP_SCARTMAIN_COMPONENTSUB_SUPPORT, /* COMPONENT */
        PIP_SCARTMAIN_VGASUB_SUPPORT,       /* VGA */
        PIP_SCARTMAIN_HDMISUB_SUPPORT,      /* HDMI */
        PIP_SCARTMAIN_DMPSUB_SUPPORT,       /* storage */
    },
    /* SV */
    {
        PIP_SVMAIN_DTVSUB_SUPPORT,          /* DTV */
        PIP_SVMAIN_ATVSUB_SUPPORT,          /* ATV */
        PIP_SVMAIN_CVBSSUB_SUPPORT,         /* CVBS */
        PIP_SVMAIN_SCARTSUB_SUPPORT,        /* SCART */
        PIP_SVMAIN_SVSUB_SUPPORT,           /* SV */
        PIP_SVMAIN_COMPONENTSUB_SUPPORT,    /* COMPONENT */
        PIP_SVMAIN_VGASUB_SUPPORT,          /* VGA */
        PIP_SVMAIN_HDMISUB_SUPPORT,         /* HDMI */
        PIP_SVMAIN_DMPSUB_SUPPORT,          /* storage */
    },
    /* COMPONENT */
    {
        PIP_COMPONENTMAIN_DTVSUB_SUPPORT,       /* DTV */
        PIP_COMPONENTMAIN_ATVSUB_SUPPORT,       /* ATV */
        PIP_COMPONENTMAIN_CVBSSUB_SUPPORT,      /* CVBS */
        PIP_COMPONENTMAIN_SCARTSUB_SUPPORT,     /* SCART */
        PIP_COMPONENTMAIN_SVSUB_SUPPORT,        /* SV */
        PIP_COMPONENTMAIN_COMPONENTSUB_SUPPORT, /* COMPONENT */
        PIP_COMPONENTMAIN_VGASUB_SUPPORT,        /* VGA */
        PIP_COMPONENTMAIN_HDMISUB_SUPPORT,       /* HDMI */
        PIP_COMPONENTMAIN_DMPSUB_SUPPORT,        /* storage */
    },
    /* VGA */
    {
        PIP_VGAMAIN_DTVSUB_SUPPORT,              /* DTV */
        PIP_VGAMAIN_ATVSUB_SUPPORT,              /* ATV */
        PIP_VGAMAIN_CVBSSUB_SUPPORT,             /* CVBS */
        PIP_VGAMAIN_SCARTSUB_SUPPORT,            /* SCART */
        PIP_VGAMAIN_SVSUB_SUPPORT,               /* SV */
        PIP_VGAMAIN_COMPONENTSUB_SUPPORT,        /* COMPONENT */
        PIP_VGAMAIN_VGASUB_SUPPORT,              /* VGA */
        PIP_VGAMAIN_HDMISUB_SUPPORT,             /* HDMI */
        PIP_VGAMAIN_DMPSUB_SUPPORT,              /* storage */
    },
    /* HDMI */
    {
        PIP_HDMIMAIN_DTVSUB_SUPPORT,             /* DTV */
        PIP_HDMIMAIN_ATVSUB_SUPPORT,             /* ATV */
        PIP_HDMIMAIN_CVBSSUB_SUPPORT,            /* CVBS */
        PIP_HDMIMAIN_SCARTSUB_SUPPORT,           /* SCART */
        PIP_HDMIMAIN_SVSUB_SUPPORT,              /* SV */
        PIP_HDMIMAIN_COMPONENTSUB_SUPPORT,       /* COMPONENT */
        PIP_HDMIMAIN_VGASUB_SUPPORT,             /* VGA */
        PIP_HDMIMAIN_HDMISUB_SUPPORT,            /* HDMI */
        PIP_HDMIMAIN_HDMISUB_SUPPORT,            /* storage */
    },
    /* storage */
    {
        PIP_DMPMAIN_DTVSUB_SUPPORT,              /* DTV */
        PIP_DMPMAIN_ATVSUB_SUPPORT,              /* ATV */
        PIP_DMPMAIN_CVBSSUB_SUPPORT,             /* CVBS */
        PIP_DMPMAIN_SCARTSUB_SUPPORT,            /* SCART */
        PIP_DMPMAIN_SVSUB_SUPPORT,               /* SV */
        PIP_DMPMAIN_COMPONENTSUB_SUPPORT,        /* COMPONENT */
        PIP_DMPMAIN_VGASUB_SUPPORT,              /* VGA */
        PIP_DMPMAIN_HDMISUB_SUPPORT,             /* HDMI */
        PIP_DMPMAIN_DMPSUB_SUPPORT,              /* storage */
    },
};
#endif

BOOLEAN MApp_InputSource_PIP_Swap(void)
{
    E_UI_INPUT_SOURCE preMainUIInputSrc = UI_INPUT_SOURCE_TYPE;
    E_UI_INPUT_SOURCE preSubUIInputSrc = UI_SUB_INPUT_SOURCE_TYPE;

    if(!IsPIPSupported())
    {
        printf("MApp_InputSource_PIP_Swap: This chip do not support PIP!\n");
        return FALSE;
    }
    if(stGenSetting.g_stPipSetting.enSubInputSourceType == UI_INPUT_SOURCE_NONE)
    {
        printf("[SWAP] Please check UI input source = NONE!\n");
        return FALSE;
    }
    // 1. empty main & sub window
    UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_NONE;
    MApp_InputSource_ChangeInputSource(SUB_WINDOW);
    UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_NONE;
    MApp_InputSource_ChangeInputSource(MAIN_WINDOW);
    // 2. create sub window with prev. main input source
    UI_INPUT_SOURCE_TYPE = preSubUIInputSrc;
    MApp_InputSource_ChangeInputSource(MAIN_WINDOW);
    if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) || IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
    {
        MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
    }
    // 3. switch main -> sub
    UI_SUB_INPUT_SOURCE_TYPE = preMainUIInputSrc;
    MApp_InputSource_ChangeInputSource(SUB_WINDOW);
     if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) || IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
    {
        MApp_ChannelChange_EnableChannel(SUB_WINDOW);
    }
     return TRUE;
}

static U8 _MApp_InputSource_PIP_GetCompatibleNum(INPUT_SOURCE_TYPE_t enSrc)
{
    U8 u8Value = 0xFF;

    switch(enSrc)
    {
        case INPUT_SOURCE_VGA:
            u8Value = 6;
            break;
        case INPUT_SOURCE_TV:
            u8Value = 1;
            break;
        case INPUT_SOURCE_CVBS:
        case INPUT_SOURCE_CVBS2:
        case INPUT_SOURCE_CVBS3:
        case INPUT_SOURCE_CVBS4:
        case INPUT_SOURCE_CVBS5:
        case INPUT_SOURCE_CVBS6:
        case INPUT_SOURCE_CVBS7:
        case INPUT_SOURCE_CVBS8:
            u8Value = 2;
            break;
        case INPUT_SOURCE_SVIDEO:
        case INPUT_SOURCE_SVIDEO2:
        case INPUT_SOURCE_SVIDEO3:
        case INPUT_SOURCE_SVIDEO4:
            u8Value = 4;
            break;
        case INPUT_SOURCE_YPBPR:
        case INPUT_SOURCE_YPBPR2:
        case INPUT_SOURCE_YPBPR3:
            u8Value = 5;
            break;
        case INPUT_SOURCE_SCART:
        case INPUT_SOURCE_SCART2:
            u8Value = 3;
            break;
        case INPUT_SOURCE_HDMI:
        case INPUT_SOURCE_HDMI2:
        case INPUT_SOURCE_HDMI3:
        case INPUT_SOURCE_HDMI4:
            u8Value = 7;
            break;
        case INPUT_SOURCE_DTV:
            u8Value = 0;
            break;
        case INPUT_SOURCE_STORAGE:
        case INPUT_SOURCE_STORAGE2:
            u8Value = 8;
            break;
        default:
            break;
    }
    return u8Value;
}

BOOLEAN MApp_InputSource_PIP_IsSrcCompatible(INPUT_SOURCE_TYPE_t enSrcMain, INPUT_SOURCE_TYPE_t enSrcSub)
{
    U8 u8Main = _MApp_InputSource_PIP_GetCompatibleNum(enSrcMain);
    U8 u8Sub = _MApp_InputSource_PIP_GetCompatibleNum(enSrcSub);

    if(u8Main >= PIP_INPUT_SOURCE_NUM || u8Sub >= PIP_INPUT_SOURCE_NUM)
    {
        return FALSE;
    }

    return (BOOLEAN)_u8PipTable[u8Main][u8Sub];
}

INPUT_SOURCE_TYPE_t MApp_InputSource_PIP_Get1stCompatibleSrc(INPUT_SOURCE_TYPE_t enSrc)
{
    U8 u8Num = _MApp_InputSource_PIP_GetCompatibleNum(enSrc);
    U8 i = 0;

    for(i = 0; i < PIP_INPUT_SOURCE_NUM; i++)
    {
        if(_u8PipTable[u8Num][i] != 0)
        {
            //Found!
            break;
        }
    }

    switch(i)
    {
        case 0:
            return INPUT_SOURCE_DTV;
        case 1:
            return INPUT_SOURCE_TV;
        case 2:
            return INPUT_SOURCE_CVBS;
        case 3:
            return INPUT_SOURCE_SCART;
        case 4:
            return INPUT_SOURCE_SVIDEO;
        case 5:
            return INPUT_SOURCE_YPBPR;
        case 6:
            return INPUT_SOURCE_VGA;
        case 7:
            return INPUT_SOURCE_HDMI;

        case 8:
             return INPUT_SOURCE_STORAGE;
        default:
            printf("Not found! Compatible list error\n");
            break;
    }

    return INPUT_SOURCE_NONE;
}

BOOLEAN MApp_InputSource_PIP_ChangeAudioSource( SCALER_WIN eWindow )
{
    if(UI_IS_AUDIO_SOURCE_IN(eWindow))
    {
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE_DURING_LIMITED_TIME, 80, E_AUDIOMUTESOURCE_ACTIVESOURCE);
        MApp_InputSource_ChangeAudioSource( stSystemInfo[eWindow].enInputSourceType,UI_INPUT_SOURCE_NONE );
        if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(eWindow)) || IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(eWindow)))
        {
             MApp_ChannelChange_PIP_ChangeAudioSource2TV (eWindow);
        }
        else if( IsSrcTypeHDMI(SYS_INPUT_SOURCE_TYPE(eWindow)))
        {
            MAPP_PCMode_PIP_ChangeAudioSource2HDMI(eWindow);
        }
    }
    return TRUE;
}


BOOLEAN _MApp_Set_DisplayWinInfo(SCALER_WIN eWindow, MS_WINDOW_TYPE *pstDispWin)
{
   MS_WINDOW_TYPE tTempSubWin;
    U8 u8TempPIP_Offset = 3;
    //First calculate the large sub window width and height
    U16 u16TempPIP_Width = (PANEL_WIDTH - SCREEN_SAVER_FRAME_WIDTH)/2 - u8TempPIP_Offset;
    U16 u16TempPIP_Height = u16TempPIP_Width*PANEL_HEIGHT/PANEL_WIDTH;

    if(pstDispWin == NULL)
    {
        if(IsPIPSupported())
        {
            tTempSubWin.x = 0;
            tTempSubWin.y = 0;
            tTempSubWin.width = u16TempPIP_Width;
            tTempSubWin.height = u16TempPIP_Height;
        }

        if(MApp_Get_PIPMode() == EN_PIP_MODE_PIP)
        {
            if(eWindow == SUB_WINDOW)
            {
                switch(stGenSetting.g_stPipSetting.enPipSize)
                {
                    default:
                    case EN_PIP_SIZE_LARGE: //125%
                        tTempSubWin.width = u16TempPIP_Width;
                        tTempSubWin.height = u16TempPIP_Height;
                        break;
                    case EN_PIP_SIZE_MEDIUM: //100%
                        tTempSubWin.width = u16TempPIP_Width/5*4;
                        tTempSubWin.height = tTempSubWin.width*PANEL_HEIGHT/PANEL_WIDTH;
                        break;
                    case EN_PIP_SIZE_SMALL: //75%
                        tTempSubWin.width = u16TempPIP_Width/5*3;
                        tTempSubWin.height = tTempSubWin.width*PANEL_HEIGHT/PANEL_WIDTH;
                        break;
                }
                switch(stGenSetting.g_stPipSetting.enPipPosition)
                {
                    default:
                    case EN_PIP_POSITION_LEFT_TOP:
                        tTempSubWin.x = 0;
                        tTempSubWin.y = 0;
                        break;
                    case EN_PIP_POSITION_RIGHT_TOP:
                        tTempSubWin.x = (PANEL_WIDTH - tTempSubWin.width);
                        tTempSubWin.y = 0;
                        break;
                    case EN_PIP_POSITION_LEFT_BOTTOM:
                        tTempSubWin.x = 0;
                        tTempSubWin.y = (PANEL_HEIGHT - tTempSubWin.height);
                        break;
                    case EN_PIP_POSITION_RIGHT_BOTTOM:
                        tTempSubWin.x = (PANEL_WIDTH - tTempSubWin.width);
                        tTempSubWin.y = (PANEL_HEIGHT - tTempSubWin.height);
                        break;
                }
                m_stSubDispWin.x = tTempSubWin.x;
                m_stSubDispWin.y = tTempSubWin.y;
                m_stSubDispWin.width= tTempSubWin.width;
                m_stSubDispWin.height= tTempSubWin.height;
                return TRUE;
            }
            else
            {
                m_stMainDispWin.x = 0;
                m_stMainDispWin.y  = 0;
                m_stMainDispWin.width = PANEL_WIDTH;
                m_stMainDispWin.height = PANEL_HEIGHT;
                return TRUE;
            }
        }
        else if(MApp_Get_PIPMode() == EN_PIP_MODE_POP_FULL)
        {
            if(eWindow == SUB_WINDOW)
            {
                m_stSubDispWin.width = PANEL_WIDTH/2;
                m_stSubDispWin.height = PANEL_HEIGHT;
                m_stSubDispWin.x = PANEL_WIDTH/2;
                m_stSubDispWin.y = 0;
                return TRUE;
            }
            else
            {
                m_stMainDispWin.x = 0;
                m_stMainDispWin.y = 0;
                m_stMainDispWin.width = PANEL_WIDTH/2;
                m_stMainDispWin.height = PANEL_HEIGHT;
                return TRUE;
            }

        }
        else if(MApp_Get_PIPMode() == EN_PIP_MODE_POP)
        {
            if(eWindow == SUB_WINDOW)
            {
                m_stSubDispWin.width = PANEL_WIDTH/2;
                m_stSubDispWin.height = (PANEL_WIDTH/2) * PANEL_HEIGHT / PANEL_WIDTH;
                m_stSubDispWin.y = PANEL_HEIGHT/2-m_stSubDispWin.height/2;
                m_stSubDispWin.x = PANEL_WIDTH/2;
                return TRUE;
            }
            else
            {
                m_stMainDispWin.width = PANEL_WIDTH/2;
                m_stMainDispWin.height = m_stMainDispWin.width * PANEL_HEIGHT / PANEL_WIDTH;
                m_stMainDispWin.x = 0;
                m_stMainDispWin.y = PANEL_HEIGHT/2-(m_stMainDispWin.height/2);
                return TRUE;
            }
        }
    }
    else
    {
        if(eWindow == SUB_WINDOW)
        {
            memcpy(&m_stSubDispWin,pstDispWin,sizeof(MS_WINDOW_TYPE));
            return TRUE;
        }
        else
        {
            memcpy(&m_stMainDispWin,pstDispWin,sizeof(MS_WINDOW_TYPE));
            return TRUE;
        }
    }
    return FALSE;
}


BOOLEAN MApp_Check_PIPMode_Supported(EN_PIP_MODE enPIPMode)
{
    if(!IsPIPSupported())
    {
        return FALSE;
    }

    if(((MApp_DMP_GetDmpUiState() == DMP_UI_STATE_DRIVE_SELECT)
        ||(MApp_DMP_GetDmpUiState() == DMP_UI_STATE_FILE_SELECT)
        ||(MApp_DMP_GetDmpUiState() == DMP_UI_STATE_LOADING)
        ||(MApp_DMP_GetDmpUiState() == DMP_UI_STATE_PLAYING_STAGE))
        && (MApp_MPlayer_QueryCurrentMediaType() != E_MPLAYER_TYPE_MOVIE))
    {
        return FALSE;
    }

    if(IsStorageInUse())
    {
      if(MApp_MPlayer_IsMoviePlaying() == FALSE)
      {
        if((enPIPMode == EN_PIP_MODE_POP_FULL)
           ||(enPIPMode == EN_PIP_MODE_POP))
           {
                return FALSE;
           }
      }
    }
    return TRUE;
}




BOOLEAN MApp_Set_PIPMode(EN_PIP_MODE enPIPMode , MS_WINDOW_TYPE *pstMainwindow, MS_WINDOW_TYPE *pstSubwindow)
{
    BOOLEAN  bEnBlackScreen[MAX_WINDOW] = {FALSE,FALSE};
    EN_PIP_MODE enPreMode = stGenSetting.g_stPipSetting.enPipMode;


    if(MApp_Check_PIPMode_Supported(enPIPMode) == FALSE)
    {
        return FALSE;
    }

    stGenSetting.g_stPipSetting.enPipMode= enPIPMode;

    if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
    {
        //Close TTX, TTX Subtitle
        #if (ENABLE_TTX)
        if(MApp_TTX_IsTeletextOn())
        {
            MApp_TTX_TeletextCommand(TTX_TV);
        }
        #endif

        #if MHEG5_ENABLE
        if(MApp_MHEG5_CheckGoMHEG5Process())
        {
            MApi_MHEG5_Disable(EN_MHEG5_DM_DISABLE_WITH_AUTOBOOT_LATER);
        }
        #endif
        //Disable MWE
        #if (MWE_FUNCTION)
        if(MApi_XC_ACE_MWEStatus())
        {
               MApi_XC_ACE_EnableMWE(FALSE);
        }
        #endif
    }


    {
        PQ_DISPLAY_TYPE enDisplaType = PQ_DISPLAY_ONE;

        switch(MApp_Get_PIPMode())
        {
            case EN_PIP_MODE_PIP:
                enDisplaType = PQ_DISPLAY_PIP;
            break;
            case EN_PIP_MODE_POP_FULL:
            case EN_PIP_MODE_POP:
                enDisplaType = PQ_DISPLAY_POP;
            break;
            default:
            case EN_PIP_MODE_OFF:
                enDisplaType = PQ_DISPLAY_ONE;
            break;
        }
        MDrv_PQ_Set_DisplayType(g_IPanel.Width(), enDisplaType);
    }

    bEnBlackScreen[MAIN_WINDOW] = MApi_XC_IsBlackVideoEnable(MAIN_WINDOW);
    bEnBlackScreen[SUB_WINDOW] = MApi_XC_IsBlackVideoEnable(SUB_WINDOW);
    if( bEnBlackScreen[MAIN_WINDOW] == FALSE)
    {
        msAPI_Scaler_SetBlueScreen( ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
    }
    if(enPreMode != EN_PIP_MODE_OFF)
    {
        if(bEnBlackScreen[SUB_WINDOW] == FALSE)
        {
            msAPI_Scaler_SetBlueScreen( ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, SUB_WINDOW);
        }
    }

    if(enPreMode == EN_PIP_MODE_OFF)
    {
        //Check sub src compatible with main src,
        // if not compatible, find src for sub win.
        if(!MApp_InputSource_PIP_IsSrcCompatible(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),
                    MApp_InputSource_GetInputSourceType(UI_SUB_INPUT_SOURCE_TYPE)))
        {
            stGenSetting.g_stPipSetting.enSubInputSourceType = MApp_InputSource_GetUIInputSourceType(MApp_InputSource_PIP_Get1stCompatibleSrc(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)));
        }

        MApp_InputSource_ChangeInputSource(SUB_WINDOW);
        if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) || IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
        {
            //tuner handle
            MApp_ChannelChange_EnableChannel(SUB_WINDOW);
        }
    }
    else if(enPreMode == EN_PIP_MODE_PIP)
    {
        MApi_XC_EnableBorder(DISABLE, SUB_WINDOW);
    }

    if(MApp_Get_PIPMode() == EN_PIP_MODE_OFF)
    {
        //Audio Source Switch
        if(stGenSetting.g_stPipSetting.enPipSoundSrc==EN_PIP_SOUND_SRC_SUB)
        {
            stGenSetting.g_stPipSetting.enPipSoundSrc=EN_PIP_SOUND_SRC_MAIN;
            MApp_InputSource_PIP_ChangeAudioSource(MAIN_WINDOW);
        }
        MApp_ZUI_API_InvalidateWindow(HWND_MENU_PIP_SOUND_SRC_OPTION);
        E_UI_INPUT_SOURCE ePreSrc = UI_SUB_INPUT_SOURCE_TYPE;
        UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_NONE;
        MApp_InputSource_ChangeInputSource(SUB_WINDOW);
        UI_SUB_INPUT_SOURCE_TYPE = ePreSrc;
    }

    //sub window info : x, y, width, height for scaler
    if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
    {
        if(IsStorageInUse())
        {
           if(MApp_Get_PIPMode() == EN_PIP_MODE_PIP)
           {
                if(MApp_MPlayer_IsMoviePlaying() || (MApp_MPlayer_QueryPreviewState(E_MPLAYER_TYPE_MOVIE) == E_MOVIE_PREVIEW_RUNNING))
                {
                    MAPP_VDPlayer_SetPIPDisplayWindow(MAIN_WINDOW,NULL);
                }
                else
                {
                    MApp_Scaler_SetWindow(
                        NULL,
                        NULL,
                        NULL,
                        stSystemInfo[MAIN_WINDOW].enAspectRatio,
                        SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),
                        MAIN_WINDOW);
                }
            }
            else
            {
                if(_MApp_Set_DisplayWinInfo(MAIN_WINDOW, pstMainwindow) == TRUE)
                {
                    MApp_Scaler_SetWindow(
                    NULL,
                    NULL,
                    &m_stMainDispWin,
                    stSystemInfo[MAIN_WINDOW].enAspectRatio,
                    SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),
                    MAIN_WINDOW);
                }
                else
                {
                    MApp_Scaler_SetWindow(
                        NULL,
                        NULL,
                        NULL,
                        stSystemInfo[MAIN_WINDOW].enAspectRatio,
                        SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),
                        MAIN_WINDOW);
                }
            }
        }
        else
        {
            if(_MApp_Set_DisplayWinInfo(MAIN_WINDOW, pstMainwindow) == TRUE)
            {
                MApp_Scaler_SetWindow(
                NULL,
                NULL,
                &m_stMainDispWin,
                stSystemInfo[MAIN_WINDOW].enAspectRatio,
                SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),
                MAIN_WINDOW);
            }
            else
            {
                MApp_Scaler_SetWindow(
                    NULL,
                    NULL,
                    NULL,
                    stSystemInfo[MAIN_WINDOW].enAspectRatio,
                    SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),
                    MAIN_WINDOW);
            }
        }
        MApp_Picture_Setting_SetColor(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);

        if (IsSrcTypeHDMI(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
        {
            //we need do Mode Detect here for SUB to confirm HDMI/DVI
            //reason: the sub-win monitor thread will be started after this routine for previous MApp_InputSource_ChangeInputSource
            MApi_XC_HDMI_CheckModeChanged(TRUE, SUB_WINDOW);
        }

        if(_MApp_Set_DisplayWinInfo(SUB_WINDOW, pstSubwindow) == TRUE)
        {
            MApp_Scaler_SetWindow(
                    NULL,
                    NULL,
                    &m_stSubDispWin,
                    stSystemInfo[MAIN_WINDOW].enAspectRatio,
                    SYS_INPUT_SOURCE_TYPE(SUB_WINDOW),
                    SUB_WINDOW);
        }
        else // close pip/pop function
        {
            if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
            {
                MApp_ClosePIPSubWindowSource();
            }
        }
        MApp_Picture_Setting_SetColor(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW), SUB_WINDOW);
        MApi_XC_EnableBorder(stGenSetting.g_stPipSetting.bBolderEnable, SUB_WINDOW);
    }
    else
    {
            if(IsStorageInUse())
            {
                if(MApp_MPlayer_IsMoviePlaying() || (MApp_MPlayer_QueryPreviewState(E_MPLAYER_TYPE_MOVIE) == E_MOVIE_PREVIEW_RUNNING))
                {
                    MAPP_VDPlayer_SetPIPDisplayWindow(MAIN_WINDOW, NULL);
                }
                else
                {
                    MApp_Scaler_SetWindow(
                        NULL,
                        NULL,
                        NULL,
                        stSystemInfo[MAIN_WINDOW].enAspectRatio,
                        SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),
                        MAIN_WINDOW);
                }
            }
            else
            {
                MApp_Scaler_SetWindow(
                    NULL,
                    NULL,
                    NULL,
                    stSystemInfo[MAIN_WINDOW].enAspectRatio,
                    SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),
                    MAIN_WINDOW);
            }
        MApp_Picture_Setting_SetColor(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
        SYS_SCREEN_SAVER_TYPE(SUB_WINDOW) = EN_SCREENSAVER_NULL; //pip off, set sub-win SS status as NULL
    }
    if(bEnBlackScreen[MAIN_WINDOW] == FALSE)
    {
        msAPI_Scaler_SetBlueScreen( DISABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
    }
    // Wait timing stable.
    if(enPreMode != EN_PIP_MODE_OFF)
    {
        if(bEnBlackScreen[SUB_WINDOW] == FALSE)
        {
            msAPI_Scaler_SetBlueScreen( DISABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, SUB_WINDOW);
        }
    }
    return TRUE;
}


EN_PIP_MODE MApp_Get_PIPMode(void)
{
    if(IsPIPSupported())
    {
        return stGenSetting.g_stPipSetting.enPipMode;
    }
    else
    {
       return EN_PIP_MODE_OFF;
    }
}

BOOLEAN MApp_InputSource_PIP_ChangeSource(E_UI_INPUT_SOURCE enSrcSub)
{
    if(!IsPIPSupported())
    {
        return FALSE;
    }

    if(MApp_InputSource_PIP_IsSrcCompatible(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),
        MApp_InputSource_GetInputSourceType(enSrcSub)))
    {
        stGenSetting.g_stPipSetting.enSubInputSourceType = enSrcSub;
    }
    else
    {
        stGenSetting.g_stPipSetting.enSubInputSourceType = UI_INPUT_SOURCE_NONE;
    }
    //printf("\n[PIP] src = %d\n", stGenSetting.g_stPipSetting.enSubInputSourceType);
    MApp_InputSource_ChangeInputSource(SUB_WINDOW);
    if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) || IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
    {
        MApp_ChannelChange_EnableChannel(SUB_WINDOW);
    }

    return TRUE;
}

BOOLEAN MApp_Set_PIPPosition(EN_PIP_POSITION  enPipPosition, MS_WINDOW_TYPE *pstSubwindow)
{
    if(!IsPIPSupported())
    {
        return FALSE;
    }

    stGenSetting.g_stPipSetting.enPipPosition = enPipPosition;
    if(_MApp_Set_DisplayWinInfo(SUB_WINDOW,pstSubwindow) == TRUE)
    {
        MApp_Scaler_SetWindow(NULL, NULL, &m_stSubDispWin,
            stSystemInfo[MAIN_WINDOW].enAspectRatio,
            SYS_INPUT_SOURCE_TYPE(SUB_WINDOW),
            SUB_WINDOW);
    }
    else
    {
        if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
        {
            MApp_ClosePIPSubWindowSource();
        }
    }

    return TRUE;
}



BOOLEAN MApp_Set_PIPSize(EN_PIP_SIZE enPipSize ,MS_WINDOW_TYPE *pstSubwindow)
{
    #if(PIP_SIZE_WITH_BLACKSCREEN == ENABLE)
    BOOLEAN  bEnBlackScreen = FALSE;
    #endif

    if(!IsPIPSupported())
    {
        return FALSE;
    }

    stGenSetting.g_stPipSetting.enPipSize =enPipSize;


#if(PIP_SIZE_WITH_BLACKSCREEN == ENABLE)
    bEnBlackScreen= MApi_XC_IsBlackVideoEnable(SUB_WINDOW);
    if( bEnBlackScreen == FALSE)
    {
        msAPI_Scaler_SetBlueScreen( ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, SUB_WINDOW);
    }
#endif
    if(_MApp_Set_DisplayWinInfo(SUB_WINDOW,pstSubwindow) == TRUE)
    {
        MApp_Scaler_SetWindow(NULL, NULL, &m_stSubDispWin,
            stSystemInfo[MAIN_WINDOW].enAspectRatio,
            SYS_INPUT_SOURCE_TYPE(SUB_WINDOW),
            SUB_WINDOW);
    }
    else
    {
        if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
        {
            MApp_ClosePIPSubWindowSource();
        }
    }

#if(PIP_SIZE_WITH_BLACKSCREEN == ENABLE)
    if( bEnBlackScreen == FALSE)
    {
        msAPI_Scaler_SetBlueScreen( DISABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, SUB_WINDOW);
    }
#endif

    return TRUE;
}


BOOLEAN MApp_ClosePIPSubWindowSource(void)
{
    if(stGenSetting.g_stPipSetting.enPipSoundSrc != EN_PIP_SOUND_SRC_MAIN)
    {
        stGenSetting.g_stPipSetting.enPipSoundSrc=EN_PIP_SOUND_SRC_MAIN;
        MApp_InputSource_PIP_ChangeAudioSource(MAIN_WINDOW);
    }
    //stGenSetting.g_stPipSetting.enSubInputSourceType = enUISrc;
    if(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW) != INPUT_SOURCE_NONE)
    {
        UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_NONE;
        MApp_InputSource_ChangeInputSource(SUB_WINDOW);
    }
    stGenSetting.g_stPipSetting.enPipMode = EN_PIP_MODE_OFF;
    UI_SUB_INPUT_SOURCE_TYPE = MApp_InputSource_GetUIInputSourceType(MApp_InputSource_PIP_Get1stCompatibleSrc(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)));

     return TRUE;
}



BOOLEAN MApp_InputSource_PIP_GetMainWinRect(MS_WINDOW_TYPE *stWinRect)
{
    if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
    {
        if(m_stMainDispWin.width != 0 ||m_stMainDispWin.height != 0 )
        {
            stWinRect->x = m_stMainDispWin.x;
            stWinRect->y = m_stMainDispWin.y;
            stWinRect->width = m_stMainDispWin.width;
            stWinRect->height = m_stMainDispWin.height;
            return TRUE;
        }

        else
        {
            if(_MApp_Set_DisplayWinInfo(MAIN_WINDOW,NULL) == TRUE)
            {
                stWinRect->x = m_stMainDispWin.x;
                stWinRect->y = m_stMainDispWin.y;
                stWinRect->width = m_stMainDispWin.width;
                stWinRect->height = m_stMainDispWin.height;
                return TRUE;
            }
        }
    }
    return FALSE;
}


BOOLEAN MApp_InputSource_PIP_GetSubWinRect(MS_WINDOW_TYPE *stWinRect)
{
    if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
    {
        if(m_stSubDispWin.width != 0 ||m_stSubDispWin.height != 0 )
        {
            stWinRect->x = m_stSubDispWin.x;
            stWinRect->y = m_stSubDispWin.y;
            stWinRect->width = m_stSubDispWin.width;
            stWinRect->height = m_stSubDispWin.height;
            return TRUE;
        }
        else
        {
            if(_MApp_Set_DisplayWinInfo(SUB_WINDOW,NULL) == TRUE)
            {
                stWinRect->x = m_stSubDispWin.x;
                stWinRect->y = m_stSubDispWin.y;
                stWinRect->width = m_stSubDispWin.width;
                stWinRect->height = m_stSubDispWin.height;
                return TRUE;
            }
        }
    }
    return FALSE;
}



#endif//ENABLE_PIP


#undef MAPP_PIP_C

