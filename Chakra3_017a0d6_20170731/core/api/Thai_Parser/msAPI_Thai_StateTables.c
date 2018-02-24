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
//---------------------------------------------------------------------------
// ICU License - ICU 1.8.1 and later
//
// COPYRIGHT AND PERMISSION NOTICE
//
// Copyright (c) 1995-2008 International Business Machines Corporation and others
//
// All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, provided that
// the above copyright notice(s) and this permission notice appear in all copies of
// the Software and that both the above copyright notice(s) and this permission
// notice appear in supporting documentation.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS. IN NO EVENT SHALL
// THE COPYRIGHT HOLDER OR HOLDERS INCLUDED IN THIS NOTICE BE LIABLE FOR ANY CLAIM,
// OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER
// RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
// NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE
// OR PERFORMANCE OF THIS SOFTWARE.
//
// Except as contained in this notice, the name of a copyright holder shall not be
// used in advertising or otherwise to promote the sale, use or other dealings in
// this Software without prior written authorization of the copyright holder.
//
// All trademarks and registered trademarks mentioned herein are the property of
// their respective owners.
//---------------------------------------------------------------------------


#include "LETypes.h"
#include "msAPI_Thai_Shaping.h"

le_uint8 classTable[] = {
    //       0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
    //       -------------------------------------------------------------------------------
    /*0E00*/ NON, CON, CON, CON, CON, CON, CON, CON, CON, CON, CON, CON, CON, COD, COD, COD,
    /*0E10*/ COD, CON, CON, CON, CON, CON, CON, CON, CON, CON, CON, COA, CON, COA, CON, COA,
    /*0E20*/ CON, CON, CON, CON, FV3, CON, FV3, CON, CON, CON, CON, CON, CON, CON, CON, NON,
    /*0E30*/ FV1, AV2, FV1, FV1, AV1, AV3, AV2, AV3, BV1, BV2, BDI, NON, NON, NON, NON, NON,
    /*0E40*/ LVO, LVO, LVO, LVO, LVO, FV2, NON, AD2, TON, TON, TON, TON, AD1, NIK, AD3, NON,
    /*0E50*/ NON, NON, NON, NON, NON, NON, NON, NON, NON, NON, NON, NON
};

StateTransition thaiStateTable[256][classCount] = {   //coverity 160465
    //+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
    //|         N         C         C         C         L         F         F         F         B         B         B         T         A         A         A         N         A         A         A    |
    //|         O         O         O         O         V         V         V         V         V         V         D         O         D         D         D         I         V         V         V    |
    //|         N         N         A         D         O         1         2         3         1         2         I         N         1         2         3         K         1         2         3    |
    //+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
    /*00*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tS}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*01*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tA}, { 0, tS}, { 0, tA}, { 2, tC}, { 6, tC}, { 0, tC}, { 8, tE}, { 0, tE}, { 0, tE}, { 0, tC}, { 9, tE}, {11, tC}, {14, tC}, {16, tC}},
    /*02*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tS}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, { 3, tE}, { 0, tE}, { 0, tR}, { 0, tR}, { 4, tE}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*03*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tA}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*04*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tS}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, { 5, tC}, { 0, tC}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*05*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tA}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*06*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tS}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, { 7, tE}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*07*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tA}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*08*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tA}, { 0, tA}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*09*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tS}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, {10, tC}, { 0, tC}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*10*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tA}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*11*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tS}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, {12, tC}, { 0, tC}, { 0, tR}, { 0, tR}, {13, tC}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*12*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tA}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*13*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tS}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*14*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tS}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, {15, tC}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*15*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tA}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*16*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tS}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, {17, tC}, { 0, tR}, { 0, tC}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*17*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tA}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*18*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tA}, { 0, tS}, { 0, tA}, {19, tC}, {23, tC}, { 0, tC}, {25, tF}, { 0, tF}, { 0, tF}, { 0, tD}, {26, tF}, {28, tD}, {31, tD}, {33, tD}},
    /*19*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tS}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, {20, tF}, { 0, tF}, { 0, tR}, { 0, tR}, {21, tF}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*20*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tA}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*21*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tS}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, {22, tC}, { 0, tC}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*22*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tA}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*23*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tS}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, {24, tF}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*24*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tA}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*25*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tA}, { 0, tA}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*26*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tS}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, {27, tG}, { 0, tG}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*27*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tA}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*28*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tS}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, {29, tG}, { 0, tG}, { 0, tR}, { 0, tR}, {30, tG}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*29*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tA}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*30*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tS}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*31*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tS}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, {32, tG}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*32*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tA}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*33*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tS}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, {34, tG}, { 0, tR}, { 0, tG}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*34*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tA}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*35*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tA}, { 0, tS}, { 0, tA}, {36, tH}, {40, tH}, { 0, tH}, {42, tE}, { 0, tE}, { 0, tE}, { 0, tC}, {43, tE}, {45, tC}, {48, tC}, {50, tC}},
    /*36*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tS}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, {37, tE}, { 0, tE}, { 0, tR}, { 0, tR}, {38, tE}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*37*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tA}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*38*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tS}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, {39, tC}, { 0, tC}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*39*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tA}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*40*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tS}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, {41, tE}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*41*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tA}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*42*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tA}, { 0, tA}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*43*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tS}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, {44, tC}, { 0, tC}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*44*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tA}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*45*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tS}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, {46, tC}, { 0, tC}, { 0, tR}, { 0, tR}, {47, tC}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*46*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tA}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*47*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tS}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*48*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tS}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, {49, tC}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*49*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tA}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*50*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tS}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, {51, tC}, { 0, tR}, { 0, tC}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}},
    /*51*/ {{ 0, tA}, { 1, tA}, {18, tA}, {35, tA}, { 0, tA}, { 0, tS}, { 0, tA}, { 0, tA}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}, { 0, tR}}
};

StateTransition getTransition(le_uint8 state, le_uint8 currClass)
{
    return thaiStateTable[state][currClass];
}
