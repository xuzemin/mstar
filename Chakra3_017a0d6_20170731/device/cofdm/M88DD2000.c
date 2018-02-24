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
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define _M88DD2000_C_

/* ------------------------------------
    Header Files
   ------------------------------------ */
#include "datatype.h"
#include "drvIIC.h"
#include "M88DD2000.h"
#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"
/* ------------------------------------
    Macro Definitions
   ------------------------------------ */
#define SIMAP_AUTO_ENABLE                   TRUE      /*    enable SI Map auto detect                    */
#define SIMAP_AUTO_EXTEND                   FALSE     /*                                                */
#define ERR_PIN_ENABLE                      FALSE     /*    enable it_lock pin as m_err pin                */

/*    DEMODULATOR ID            */
#define MT_FE_DMD_ID_DD2K                    1
#define MT_FE_DMD_ID_DD2001                    2

#define MT_FE_DMD_CURRENT_ID                MT_FE_DMD_ID_DD2K
/* ------------------------------------
    Type Definitions
   ------------------------------------ */


/* ------------------------------------
    Variables Definitions
   ------------------------------------ */


#define M88DD2000_DBG(x)   //x

typedef struct
{
    U8    cAddress;
    U8    cData;
} INIT_DATA_COFDM_DEM;

static code INIT_DATA_COFDM_DEM m_InitDataCOFDM[] =
{
    { 0x1A,    0x8C },
    { 0x1A,    0xCC },
    { 0x1D,    0xA0 },
    { 0x07,    0x03 },
    { 0x20,    0x02 },
    { 0x30,    0x4F },
    { 0x31,    0xCC },
    { 0x32,    0xCC },
    { 0x33,    0x90 },
    { 0x34,    0x08 },
    { 0x35,    0x0F },
    { 0x36,    0x0F },
    { 0x37,    0x10 },
    { 0x38,    0xFF },
    { 0x39,    0x10 },
    { 0x3A,    0xFF },
    { 0x3B,    0x30 },
    { 0x3C,    0xD0 },
    { 0x3D,    0x70 },
    { 0x3E,    0x70 },
    { 0x3F,    0x00 },
    { 0x5F,    0x50 },
    { 0x65,    0x65 },
    { 0x6C,    0xFF },
    { 0xC2,    0x1F },
    { 0xC3,    0x25 },
    { 0x66,    0x0A },
    { 0x80,    0xC2 },
    { 0x8D,    0x93 },
    { 0x7F,    0x02 },
    { 0x8B,    0x3A },
    { 0x91,    0x3F },
    { 0x49,    0x08 },
    { 0x4C,    0x06 },
    { 0x4A,    0x03 },
    { 0x53,    0x32 },
    { 0x54,    0x33 },
    { 0x55,    0x33 },
    { 0xD2,    0x30 },
    { 0xD3,    0x10 },
    { 0xD4,    0x20 },
    { 0xD5,    0x26 },
    { 0xDC,    0x13 },
    { 0xAC,    0x03 },
    { 0xAE,    0x15 },
    { 0xBD,    0x80 },


    { 0xE1,    0xC0 },
    { 0xE2,    0x00 },
    { 0xE3,    0x00 },
    { 0xE4,    0x10 },
    { 0xE5,    0x10 },
    { 0xE6,    0x10 }
};

#if (SIMAP_AUTO_EXTEND != 0)

/*============================================================
**    Sat Aug 02 11:59:59 2008
**    converted from file :    maver_fpga_v20b.rom
==========================================================*/


const U8 m88dd2k_fm[] =
{
    0x20, 0x30,        /*    0 */
    0x84, 0x00,        /*    1 */
    0x77, 0x30,        /*    2 */
    0x08, 0x20,        /*    3 */
    0xc7, 0x2a,        /*    4 */
    0x04, 0x06,        /*    5 */
    0x80, 0x01,        /*    6 */
    0x84, 0x0a,        /*    7 */
    0x04, 0x06,        /*    8 */
    0x03, 0x1d,        /*    9 */
    0x05, 0x28,        /*   10 */
    0x64, 0x00,        /*   11 */
    0x00, 0x34,        /*   12 */
    0x00, 0x00,        /*   13 */
    0x00, 0x00,        /*   14 */
    0x00, 0x00,        /*   15 */
    0x00, 0x00,        /*   16 */
    0x00, 0x00,        /*   17 */
    0x00, 0x00,        /*   18 */
    0x00, 0x00,        /*   19 */
    0x00, 0x00,        /*   20 */
    0x00, 0x00,        /*   21 */
    0x00, 0x00,        /*   22 */
    0x00, 0x00,        /*   23 */
    0x00, 0x00,        /*   24 */
    0x00, 0x00,        /*   25 */
    0x00, 0x00,        /*   26 */
    0x00, 0x00,        /*   27 */
    0x00, 0x00,        /*   28 */
    0x00, 0x00,        /*   29 */
    0x00, 0x00,        /*   30 */
    0x00, 0x00,        /*   31 */
    0x00, 0x00,        /*   32 */
    0x00, 0x00,        /*   33 */
    0x00, 0x00,        /*   34 */
    0x00, 0x00,        /*   35 */
    0x00, 0x00,        /*   36 */
    0x00, 0x00,        /*   37 */
    0x00, 0x00,        /*   38 */
    0x00, 0x00,        /*   39 */
    0x00, 0x00,        /*   40 */
    0x00, 0x00,        /*   41 */
    0x00, 0x00,        /*   42 */
    0x00, 0x00,        /*   43 */
    0x00, 0x00,        /*   44 */
    0x00, 0x00,        /*   45 */
    0x00, 0x00,        /*   46 */
    0x00, 0x00,        /*   47 */
    0x00, 0x00,        /*   48 */
    0x00, 0x00,        /*   49 */
    0x00, 0x00,        /*   50 */
    0x00, 0x00,        /*   51 */
    0x00, 0x00,        /*   52 */
    0x00, 0x00,        /*   53 */
    0x00, 0x00,        /*   54 */
    0x00, 0x00,        /*   55 */
    0x00, 0x00,        /*   56 */
    0x00, 0x00,        /*   57 */
    0x00, 0x00,        /*   58 */
    0x00, 0x00,        /*   59 */
    0x00, 0x00,        /*   60 */
    0x00, 0x00,        /*   61 */
    0x00, 0x00,        /*   62 */
    0x00, 0x00,        /*   63 */
    0x00, 0x00,        /*   64 */
    0x00, 0x00,        /*   65 */
    0x00, 0x00,        /*   66 */
    0x00, 0x00,        /*   67 */
    0x00, 0x00,        /*   68 */
    0x00, 0x00,        /*   69 */
    0x00, 0x00,        /*   70 */
    0x00, 0x00,        /*   71 */
    0x00, 0x00,        /*   72 */
    0x00, 0x00,        /*   73 */
    0x00, 0x00,        /*   74 */
    0x00, 0x00,        /*   75 */
    0x00, 0x00,        /*   76 */
    0x00, 0x00,        /*   77 */
    0x00, 0x00,        /*   78 */
    0x00, 0x00,        /*   79 */
    0x00, 0x00,        /*   80 */
    0x00, 0x00,        /*   81 */
    0x00, 0x00,        /*   82 */
    0x00, 0x00,        /*   83 */
    0x00, 0x00,        /*   84 */
    0x00, 0x00,        /*   85 */
    0x00, 0x00,        /*   86 */
    0x00, 0x00,        /*   87 */
    0x00, 0x00,        /*   88 */
    0x00, 0x00,        /*   89 */
    0x00, 0x00,        /*   90 */
    0x00, 0x00,        /*   91 */
    0x00, 0x00,        /*   92 */
    0x00, 0x00,        /*   93 */
    0x00, 0x00,        /*   94 */
    0x00, 0x00,        /*   95 */
    0x00, 0x00,        /*   96 */
    0x00, 0x00,        /*   97 */
    0x00, 0x00,        /*   98 */
    0x00, 0x00,        /*   99 */
    0x00, 0x00,        /*  100 */
    0x00, 0x00,        /*  101 */
    0x00, 0x00,        /*  102 */
    0x00, 0x00,        /*  103 */
    0x00, 0x00,        /*  104 */
    0x00, 0x00,        /*  105 */
    0x00, 0x00,        /*  106 */
    0x00, 0x00,        /*  107 */
    0x00, 0x00,        /*  108 */
    0x00, 0x00,        /*  109 */
    0x00, 0x00,        /*  110 */
    0x00, 0x00,        /*  111 */
    0x00, 0x00,        /*  112 */
    0x00, 0x00,        /*  113 */
    0x00, 0x00,        /*  114 */
    0x00, 0x00,        /*  115 */
    0x00, 0x00,        /*  116 */
    0x00, 0x00,        /*  117 */
    0x00, 0x00,        /*  118 */
    0x00, 0x00,        /*  119 */
    0x00, 0x00,        /*  120 */
    0x00, 0x00,        /*  121 */
    0x00, 0x00,        /*  122 */
    0x00, 0x00,        /*  123 */
    0x00, 0x00,        /*  124 */
    0x00, 0x00,        /*  125 */
    0x00, 0x00,        /*  126 */
    0x00, 0x00,        /*  127 */
    0x00, 0x00,        /*  128 */
    0x00, 0x00,        /*  129 */
    0x00, 0x00,        /*  130 */
    0x00, 0x00,        /*  131 */
    0x00, 0x00,        /*  132 */
    0x00, 0x00,        /*  133 */
    0x00, 0x00,        /*  134 */
    0x00, 0x00,        /*  135 */
    0x00, 0x00,        /*  136 */
    0x00, 0x00,        /*  137 */
    0x00, 0x00,        /*  138 */
    0x00, 0x00,        /*  139 */
    0x00, 0x00,        /*  140 */
    0x00, 0x00,        /*  141 */
    0x00, 0x00,        /*  142 */
    0x00, 0x00,        /*  143 */
    0x00, 0x00,        /*  144 */
    0x00, 0x00,        /*  145 */
    0x00, 0x00,        /*  146 */
    0x00, 0x00,        /*  147 */
    0x00, 0x00,        /*  148 */
    0x00, 0x00,        /*  149 */
    0x00, 0x00,        /*  150 */
    0x00, 0x00,        /*  151 */
    0x00, 0x00,        /*  152 */
    0x00, 0x00,        /*  153 */
    0x00, 0x00,        /*  154 */
    0x00, 0x00,        /*  155 */
    0x00, 0x00,        /*  156 */
    0x00, 0x00,        /*  157 */
    0x00, 0x00,        /*  158 */
    0x00, 0x00,        /*  159 */
    0x00, 0x00,        /*  160 */
    0x00, 0x00,        /*  161 */
    0x00, 0x00,        /*  162 */
    0x00, 0x00,        /*  163 */
    0x00, 0x00,        /*  164 */
    0x00, 0x00,        /*  165 */
    0x00, 0x00,        /*  166 */
    0x00, 0x00,        /*  167 */
    0x00, 0x00,        /*  168 */
    0x00, 0x00,        /*  169 */
    0x00, 0x00,        /*  170 */
    0x00, 0x00,        /*  171 */
    0x00, 0x00,        /*  172 */
    0x00, 0x00,        /*  173 */
    0x00, 0x00,        /*  174 */
    0x00, 0x00,        /*  175 */
    0x00, 0x00,        /*  176 */
    0x00, 0x00,        /*  177 */
    0x00, 0x00,        /*  178 */
    0x00, 0x00,        /*  179 */
    0x00, 0x00,        /*  180 */
    0x00, 0x00,        /*  181 */
    0x00, 0x00,        /*  182 */
    0x00, 0x00,        /*  183 */
    0x00, 0x00,        /*  184 */
    0x00, 0x00,        /*  185 */
    0x00, 0x00,        /*  186 */
    0x00, 0x00,        /*  187 */
    0x00, 0x00,        /*  188 */
    0x00, 0x00,        /*  189 */
    0x00, 0x00,        /*  190 */
    0x00, 0x00,        /*  191 */
    0x00, 0x00,        /*  192 */
    0x00, 0x00,        /*  193 */
    0x00, 0x00,        /*  194 */
    0x00, 0x00,        /*  195 */
    0x00, 0x00,        /*  196 */
    0x00, 0x00,        /*  197 */
    0x00, 0x00,        /*  198 */
    0x00, 0x00,        /*  199 */
    0x00, 0x00,        /*  200 */
    0x00, 0x00,        /*  201 */
    0x00, 0x00,        /*  202 */
    0x00, 0x00,        /*  203 */
    0x00, 0x00,        /*  204 */
    0x00, 0x00,        /*  205 */
    0x00, 0x00,        /*  206 */
    0x00, 0x00,        /*  207 */
    0x00, 0x00,        /*  208 */
    0x00, 0x00,        /*  209 */
    0x00, 0x00,        /*  210 */
    0x00, 0x00,        /*  211 */
    0x00, 0x00,        /*  212 */
    0x00, 0x00,        /*  213 */
    0x00, 0x00,        /*  214 */
    0x00, 0x00,        /*  215 */
    0x00, 0x00,        /*  216 */
    0x00, 0x00,        /*  217 */
    0x00, 0x00,        /*  218 */
    0x00, 0x00,        /*  219 */
    0x00, 0x00,        /*  220 */
    0x00, 0x00,        /*  221 */
    0x00, 0x00,        /*  222 */
    0x00, 0x00,        /*  223 */
    0x00, 0x00,        /*  224 */
    0x00, 0x00,        /*  225 */
    0x00, 0x00,        /*  226 */
    0x00, 0x00,        /*  227 */
    0x00, 0x00,        /*  228 */
    0x00, 0x00,        /*  229 */
    0x00, 0x00,        /*  230 */
    0x00, 0x00,        /*  231 */
    0x00, 0x00,        /*  232 */
    0x00, 0x00,        /*  233 */
    0x00, 0x00,        /*  234 */
    0x00, 0x00,        /*  235 */
    0x00, 0x00,        /*  236 */
    0x00, 0x00,        /*  237 */
    0x00, 0x00,        /*  238 */
    0x00, 0x00,        /*  239 */
    0x00, 0x00,        /*  240 */
    0x00, 0x00,        /*  241 */
    0x00, 0x00,        /*  242 */
    0x00, 0x00,        /*  243 */
    0x00, 0x00,        /*  244 */
    0x00, 0x00,        /*  245 */
    0x00, 0x00,        /*  246 */
    0x00, 0x00,        /*  247 */
    0x00, 0x00,        /*  248 */
    0x00, 0x00,        /*  249 */
    0x00, 0x00,        /*  250 */
    0x00, 0x00,        /*  251 */
    0x00, 0x00,        /*  252 */
    0x00, 0x00,        /*  253 */
    0x00, 0x00,        /*  254 */
    0x00, 0x00,        /*  255 */
    0x00, 0x00,        /*  256 */
    0x00, 0x00,        /*  257 */
    0x00, 0x00,        /*  258 */
    0x00, 0x00,        /*  259 */
    0x00, 0x00,        /*  260 */
    0x00, 0x00,        /*  261 */
    0x00, 0x00,        /*  262 */
    0x00, 0x00,        /*  263 */
    0x00, 0x00,        /*  264 */
    0x00, 0x00,        /*  265 */
    0x00, 0x00,        /*  266 */
    0x00, 0x00,        /*  267 */
    0x00, 0x00,        /*  268 */
    0x00, 0x00,        /*  269 */
    0x00, 0x00,        /*  270 */
    0x00, 0x00,        /*  271 */
    0x00, 0x00,        /*  272 */
    0x00, 0x00,        /*  273 */
    0x00, 0x00,        /*  274 */
    0x00, 0x00,        /*  275 */
    0x00, 0x00,        /*  276 */
    0x00, 0x00,        /*  277 */
    0x00, 0x00,        /*  278 */
    0x00, 0x00,        /*  279 */
    0x00, 0x00,        /*  280 */
    0x00, 0x00,        /*  281 */
    0x00, 0x00,        /*  282 */
    0x00, 0x00,        /*  283 */
    0x00, 0x00,        /*  284 */
    0x00, 0x00,        /*  285 */
    0x00, 0x00,        /*  286 */
    0x00, 0x00,        /*  287 */
    0x00, 0x00,        /*  288 */
    0x00, 0x00,        /*  289 */
    0x00, 0x00,        /*  290 */
    0x00, 0x00,        /*  291 */
    0x00, 0x00,        /*  292 */
    0x00, 0x00,        /*  293 */
    0x00, 0x00,        /*  294 */
    0x00, 0x00,        /*  295 */
    0x00, 0x00,        /*  296 */
    0x00, 0x00,        /*  297 */
    0x00, 0x00,        /*  298 */
    0x00, 0x00,        /*  299 */
    0x00, 0x00,        /*  300 */
    0x00, 0x00,        /*  301 */
    0x00, 0x00,        /*  302 */
    0x00, 0x00,        /*  303 */
    0x00, 0x00,        /*  304 */
    0x00, 0x00,        /*  305 */
    0x00, 0x00,        /*  306 */
    0x00, 0x00,        /*  307 */
    0x00, 0x00,        /*  308 */
    0x00, 0x00,        /*  309 */
    0x00, 0x00,        /*  310 */
    0x00, 0x00,        /*  311 */
    0x00, 0x00,        /*  312 */
    0x00, 0x00,        /*  313 */
    0x00, 0x00,        /*  314 */
    0x00, 0x00,        /*  315 */
    0x00, 0x00,        /*  316 */
    0x00, 0x00,        /*  317 */
    0x00, 0x00,        /*  318 */
    0x00, 0x00,        /*  319 */
    0x00, 0x00,        /*  320 */
    0x00, 0x00,        /*  321 */
    0x00, 0x00,        /*  322 */
    0x83, 0x01,        /*  323 */
    0xb5, 0x00,        /*  324 */
    0x9c, 0x00,        /*  325 */
    0x34, 0x08,        /*  326 */
    0x9e, 0x00,        /*  327 */
    0x08, 0x00,        /*  328 */
    0x83, 0x01,        /*  329 */
    0xf5, 0x00,        /*  330 */
    0x9c, 0x00,        /*  331 */
    0x01, 0x30,        /*  332 */
    0x9e, 0x00,        /*  333 */
    0x9e, 0x01,        /*  334 */
    0x08, 0x00,        /*  335 */
    0x83, 0x01,        /*  336 */
    0xf5, 0x00,        /*  337 */
    0x9c, 0x00,        /*  338 */
    0x00, 0x00,        /*  339 */
    0x00, 0x00,        /*  340 */
    0x1d, 0x08,        /*  341 */
    0xf6, 0x00,        /*  342 */
    0x08, 0x00,        /*  343 */
    0xfa, 0x00,        /*  344 */
    0x00, 0x30,        /*  345 */
    0x7b, 0x18,        /*  346 */
    0x7a, 0x07,        /*  347 */
    0x03, 0x10,        /*  348 */
    0xfa, 0x0d,        /*  349 */
    0x03, 0x10,        /*  350 */
    0xfb, 0x0c,        /*  351 */
    0xfb, 0x08,        /*  352 */
    0x03, 0x19,        /*  353 */
    0x08, 0x00,        /*  354 */
    0x5a, 0x29,        /*  355 */
    0x83, 0x01,        /*  356 */
    0xf5, 0x00,        /*  357 */
    0x9c, 0x00,        /*  358 */
    0x00, 0x00,        /*  359 */
    0x00, 0x00,        /*  360 */
    0x20, 0x10,        /*  361 */
    0x1d, 0x18,        /*  362 */
    0x20, 0x14,        /*  363 */
    0x03, 0x10,        /*  364 */
    0x20, 0x18,        /*  365 */
    0x03, 0x14,        /*  366 */
    0x08, 0x00,        /*  367 */
    0x83, 0x01,        /*  368 */
    0xb2, 0x00,        /*  369 */
    0xb3, 0x01,        /*  370 */
    0x7b, 0x29,        /*  371 */
    0x01, 0x30,        /*  372 */
    0x64, 0x21,        /*  373 */
    0x03, 0x1c,        /*  374 */
    0x7b, 0x29,        /*  375 */
    0x01, 0x30,        /*  376 */
    0x49, 0x21,        /*  377 */
    0xb3, 0x0a,        /*  378 */
    0x32, 0x08,        /*  379 */
    0x33, 0x02,        /*  380 */
    0x03, 0x18,        /*  381 */
    0x08, 0x00,        /*  382 */
    0x74, 0x29,        /*  383 */
    0x83, 0x01,        /*  384 */
    0xb4, 0x00,        /*  385 */
    0x32, 0x08,        /*  386 */
    0xfb, 0x00,        /*  387 */
    0x34, 0x08,        /*  388 */
    0x58, 0x21,        /*  389 */
    0xb3, 0x00,        /*  390 */
    0x32, 0x08,        /*  391 */
    0xfc, 0x00,        /*  392 */
    0xfd, 0x01,        /*  393 */
    0x34, 0x08,        /*  394 */
    0xfa, 0x00,        /*  395 */
    0xfb, 0x01,        /*  396 */
    0x94, 0x21,        /*  397 */
    0x7e, 0x08,        /*  398 */
    0xb5, 0x00,        /*  399 */
    0x7f, 0x08,        /*  400 */
    0xb6, 0x00,        /*  401 */
    0xb4, 0x00,        /*  402 */
    0x08, 0x00,        /*  403 */
    0xfe, 0x01,        /*  404 */
    0xff, 0x01,        /*  405 */
    0x03, 0x10,        /*  406 */
    0xfd, 0x0c,        /*  407 */
    0xfc, 0x0c,        /*  408 */
    0x03, 0x1c,        /*  409 */
    0xa2, 0x29,        /*  410 */
    0x7a, 0x08,        /*  411 */
    0xfe, 0x07,        /*  412 */
    0x7b, 0x08,        /*  413 */
    0x03, 0x18,        /*  414 */
    0x7b, 0x0a,        /*  415 */
    0xff, 0x07,        /*  416 */
    0x03, 0x10,        /*  417 */
    0xfa, 0x0d,        /*  418 */
    0xfb, 0x0d,        /*  419 */
    0x7c, 0x08,        /*  420 */
    0x7d, 0x04,        /*  421 */
    0x03, 0x19,        /*  422 */
    0x00, 0x34,        /*  423 */
    0x96, 0x29,        /*  424 */
    0x63, 0x30,        /*  425 */
    0x64, 0x21,        /*  426 */
    0x22, 0x10,        /*  427 */
    0x03, 0x18,        /*  428 */
    0x22, 0x14,        /*  429 */
    0x41, 0x30,        /*  430 */
    0x50, 0x21,        /*  431 */
    0xb2, 0x00,        /*  432 */
    0x42, 0x30,        /*  433 */
    0x50, 0x21,        /*  434 */
    0x03, 0x3a,        /*  435 */
    0x03, 0x1d,        /*  436 */
    0xba, 0x29,        /*  437 */
    0xb4, 0x01,        /*  438 */
    0x44, 0x30,        /*  439 */
    0x43, 0x21,        /*  440 */
    0xcf, 0x29,        /*  441 */
    0x32, 0x1f,        /*  442 */
    0xd6, 0x29,        /*  443 */
    0x22, 0x18,        /*  444 */
    0xc0, 0x29,        /*  445 */
    0x02, 0x30,        /*  446 */
    0xc1, 0x29,        /*  447 */
    0x03, 0x30,        /*  448 */
    0xb3, 0x00,        /*  449 */
    0xb4, 0x00,        /*  450 */
    0x44, 0x30,        /*  451 */
    0x43, 0x21,        /*  452 */
    0x62, 0x30,        /*  453 */
    0x50, 0x21,        /*  454 */
    0x0f, 0x39,        /*  455 */
    0xb3, 0x00,        /*  456 */
    0x22, 0x1c,        /*  457 */
    0xd2, 0x29,        /*  458 */
    0x33, 0x08,        /*  459 */
    0x0c, 0x3a,        /*  460 */
    0x03, 0x1d,        /*  461 */
    0xd2, 0x29,        /*  462 */
    0xb4, 0x01,        /*  463 */
    0xb4, 0x0a,        /*  464 */
    0xd4, 0x29,        /*  465 */
    0x03, 0x30,        /*  466 */
    0xb4, 0x00,        /*  467 */
    0x43, 0x30,        /*  468 */
    0x43, 0x29,        /*  469 */
    0x43, 0x30,        /*  470 */
    0x50, 0x21,        /*  471 */
    0xb3, 0x00,        /*  472 */
    0xb4, 0x00,        /*  473 */
    0x43, 0x30,        /*  474 */
    0x43, 0x21,        /*  475 */
    0x44, 0x30,        /*  476 */
    0x50, 0x21,        /*  477 */
    0xb3, 0x00,        /*  478 */
    0xb4, 0x00,        /*  479 */
    0x44, 0x30,        /*  480 */
    0x43, 0x29,        /*  481 */
    0x83, 0x01,        /*  482 */
    0x23, 0x1e,        /*  483 */
    0xe7, 0x29,        /*  484 */
    0xa1, 0x17,        /*  485 */
    0xe8, 0x29,        /*  486 */
    0xa1, 0x13,        /*  487 */
    0x23, 0x08,        /*  488 */
    0x0f, 0x39,        /*  489 */
    0xb2, 0x00,        /*  490 */
    0x22, 0x1a,        /*  491 */
    0xf7, 0x29,        /*  492 */
    0xa5, 0x01,        /*  493 */
    0xb2, 0x08,        /*  494 */
    0x03, 0x1d,        /*  495 */
    0x1b, 0x2a,        /*  496 */
    0x22, 0x16,        /*  497 */
    0xa2, 0x15,        /*  498 */
    0xa1, 0x1b,        /*  499 */
    0xa2, 0x11,        /*  500 */
    0xa4, 0x01,        /*  501 */
    0x1b, 0x2a,        /*  502 */
    0x25, 0x08,        /*  503 */
    0x03, 0x3a,        /*  504 */
    0x03, 0x19,        /*  505 */
    0xfd, 0x29,        /*  506 */
    0x22, 0x16,        /*  507 */
    0xfe, 0x29,        /*  508 */
    0x22, 0x12,        /*  509 */
    0x24, 0x08,        /*  510 */
    0x26, 0x06,        /*  511 */
    0x03, 0x1d,        /*  512 */
    0x1a, 0x2a,        /*  513 */
    0xa4, 0x01,        /*  514 */
    0xb2, 0x08,        /*  515 */
    0x03, 0x1d,        /*  516 */
    0x16, 0x2a,        /*  517 */
    0xa2, 0x1d,        /*  518 */
    0x0a, 0x2a,        /*  519 */
    0x01, 0x30,        /*  520 */
    0x0b, 0x2a,        /*  521 */
    0x00, 0x30,        /*  522 */
    0xfa, 0x00,        /*  523 */
    0xa1, 0x1f,        /*  524 */
    0x10, 0x2a,        /*  525 */
    0x01, 0x30,        /*  526 */
    0x11, 0x2a,        /*  527 */
    0x00, 0x30,        /*  528 */
    0xfa, 0x06,        /*  529 */
    0x03, 0x1d,        /*  530 */
    0x16, 0x2a,        /*  531 */
    0xa5, 0x01,        /*  532 */
    0x17, 0x2a,        /*  533 */
    0xa5, 0x0a,        /*  534 */
    0x08, 0x30,        /*  535 */
    0xa2, 0x06,        /*  536 */
    0x1b, 0x2a,        /*  537 */
    0xa4, 0x0a,        /*  538 */
    0x07, 0x30,        /*  539 */
    0x49, 0x21,        /*  540 */
    0x24, 0x08,        /*  541 */
    0x26, 0x06,        /*  542 */
    0x03, 0x1d,        /*  543 */
    0x24, 0x2a,        /*  544 */
    0x02, 0x30,        /*  545 */
    0xb3, 0x00,        /*  546 */
    0x25, 0x2a,        /*  547 */
    0xb3, 0x01,        /*  548 */
    0xa2, 0x19,        /*  549 */
    0x33, 0x14,        /*  550 */
    0x33, 0x08,        /*  551 */
    0xb4, 0x00,        /*  552 */
    0x1b, 0x30,        /*  553 */
    0x43, 0x29,        /*  554 */
    0x3b, 0x30,        /*  555 */
    0x50, 0x21,        /*  556 */
    0xb2, 0x00,        /*  557 */
    0x03, 0x10,        /*  558 */
    0xb2, 0x0d,        /*  559 */
    0x03, 0x10,        /*  560 */
    0xb2, 0x0d,        /*  561 */
    0x03, 0x10,        /*  562 */
    0xb2, 0x0d,        /*  563 */
    0xa4, 0x01,        /*  564 */
    0xb4, 0x01,        /*  565 */
    0x34, 0x08,        /*  566 */
    0x35, 0x3e,        /*  567 */
    0x84, 0x00,        /*  568 */
    0x83, 0x13,        /*  569 */
    0x80, 0x01,        /*  570 */
    0x34, 0x08,        /*  571 */
    0x35, 0x3e,        /*  572 */
    0x84, 0x00,        /*  573 */
    0x83, 0x13,        /*  574 */
    0x00, 0x08,        /*  575 */
    0x87, 0x00,        /*  576 */
    0xb4, 0x0a,        /*  577 */
    0x40, 0x30,        /*  578 */
    0x34, 0x02,        /*  579 */
    0x03, 0x1c,        /*  580 */
    0x36, 0x2a,        /*  581 */
    0xb4, 0x01,        /*  582 */
    0xb3, 0x01,        /*  583 */
    0x8f, 0x2a,        /*  584 */
    0x08, 0x30,        /*  585 */
    0x64, 0x21,        /*  586 */
    0x03, 0x1c,        /*  587 */
    0x8f, 0x2a,        /*  588 */
    0x08, 0x30,        /*  589 */
    0x49, 0x21,        /*  590 */
    0x6b, 0x30,        /*  591 */
    0x64, 0x21,        /*  592 */
    0xa2, 0x10,        /*  593 */
    0x03, 0x18,        /*  594 */
    0xa2, 0x14,        /*  595 */
    0x6c, 0x30,        /*  596 */
    0x64, 0x21,        /*  597 */
    0x22, 0x11,        /*  598 */
    0x03, 0x18,        /*  599 */
    0x22, 0x15,        /*  600 */
    0x6e, 0x30,        /*  601 */
    0x50, 0x21,        /*  602 */
    0xa3, 0x00,        /*  603 */
    0xa2, 0x1c,        /*  604 */
    0x60, 0x2a,        /*  605 */
    0xb4, 0x0a,        /*  606 */
    0x61, 0x2a,        /*  607 */
    0xb3, 0x0a,        /*  608 */
    0x22, 0x1d,        /*  609 */
    0x65, 0x2a,        /*  610 */
    0xa3, 0x16,        /*  611 */
    0x66, 0x2a,        /*  612 */
    0xa3, 0x12,        /*  613 */
    0x33, 0x08,        /*  614 */
    0x87, 0x00,        /*  615 */
    0x23, 0x08,        /*  616 */
    0x35, 0x3e,        /*  617 */
    0x84, 0x00,        /*  618 */
    0x83, 0x13,        /*  619 */
    0x00, 0x0a,        /*  620 */
    0x03, 0x19,        /*  621 */
    0x73, 0x2a,        /*  622 */
    0x23, 0x08,        /*  623 */
    0x35, 0x3e,        /*  624 */
    0x84, 0x00,        /*  625 */
    0x80, 0x0a,        /*  626 */
    0x23, 0x08,        /*  627 */
    0x35, 0x3e,        /*  628 */
    0x84, 0x00,        /*  629 */
    0x00, 0x08,        /*  630 */
    0x14, 0x3a,        /*  631 */
    0x03, 0x19,        /*  632 */
    0x96, 0x2a,        /*  633 */
    0x23, 0x08,        /*  634 */
    0x35, 0x3e,        /*  635 */
    0x84, 0x00,        /*  636 */
    0x0a, 0x30,        /*  637 */
    0x00, 0x02,        /*  638 */
    0x03, 0x1c,        /*  639 */
    0x85, 0x2a,        /*  640 */
    0x0f, 0x30,        /*  641 */
    0x24, 0x02,        /*  642 */
    0x03, 0x1c,        /*  643 */
    0x96, 0x2a,        /*  644 */
    0x23, 0x08,        /*  645 */
    0x35, 0x3e,        /*  646 */
    0x84, 0x00,        /*  647 */
    0x00, 0x08,        /*  648 */
    0x03, 0x3a,        /*  649 */
    0x03, 0x19,        /*  650 */
    0xb2, 0x08,        /*  651 */
    0x03, 0x19,        /*  652 */
    0x96, 0x2a,        /*  653 */
    0xa4, 0x0a,        /*  654 */
    0xa4, 0x08,        /*  655 */
    0x03, 0x19,        /*  656 */
    0x49, 0x2a,        /*  657 */
    0x80, 0x30,        /*  658 */
    0x24, 0x02,        /*  659 */
    0x03, 0x1c,        /*  660 */
    0x49, 0x2a,        /*  661 */
    0x34, 0x08,        /*  662 */
    0x33, 0x02,        /*  663 */
    0x03, 0x18,        /*  664 */
    0x9c, 0x2a,        /*  665 */
    0xa2, 0x14,        /*  666 */
    0x9d, 0x2a,        /*  667 */
    0xa2, 0x10,        /*  668 */
    0x83, 0x12,        /*  669 */
    0x03, 0x13,        /*  670 */
    0xb4, 0x01,        /*  671 */
    0x34, 0x08,        /*  672 */
    0x35, 0x3e,        /*  673 */
    0x84, 0x00,        /*  674 */
    0x83, 0x13,        /*  675 */
    0x00, 0x08,        /*  676 */
    0x87, 0x00,        /*  677 */
    0xb4, 0x0a,        /*  678 */
    0x40, 0x30,        /*  679 */
    0x34, 0x02,        /*  680 */
    0x03, 0x1c,        /*  681 */
    0xa0, 0x2a,        /*  682 */
    0x35, 0x08,        /*  683 */
    0xb3, 0x00,        /*  684 */
    0xa3, 0x01,        /*  685 */
    0xb4, 0x01,        /*  686 */
    0xb4, 0x0a,        /*  687 */
    0x34, 0x08,        /*  688 */
    0x35, 0x3e,        /*  689 */
    0x84, 0x00,        /*  690 */
    0x83, 0x13,        /*  691 */
    0x00, 0x08,        /*  692 */
    0x33, 0x02,        /*  693 */
    0x03, 0x18,        /*  694 */
    0xbf, 0x2a,        /*  695 */
    0x34, 0x08,        /*  696 */
    0x35, 0x3e,        /*  697 */
    0x84, 0x00,        /*  698 */
    0x00, 0x08,        /*  699 */
    0xb3, 0x00,        /*  700 */
    0x34, 0x08,        /*  701 */
    0xa3, 0x00,        /*  702 */
    0xb4, 0x0a,        /*  703 */
    0x40, 0x30,        /*  704 */
    0x34, 0x02,        /*  705 */
    0x03, 0x1c,        /*  706 */
    0xb0, 0x2a,        /*  707 */
    0xa2, 0x18,        /*  708 */
    0x01, 0x34,        /*  709 */
    0x00, 0x34,        /*  710 */
    0x20, 0x30,        /*  711 */
    0x83, 0x12,        /*  712 */
    0x03, 0x13,        /*  713 */
    0x86, 0x00,        /*  714 */
    0xac, 0x01,        /*  715 */
    0x21, 0x12,        /*  716 */
    0x41, 0x30,        /*  717 */
    0x50, 0x21,        /*  718 */
    0xad, 0x00,        /*  719 */
    0xa1, 0x12,        /*  720 */
    0x43, 0x30,        /*  721 */
    0x50, 0x21,        /*  722 */
    0xad, 0x00,        /*  723 */
    0xb4, 0x00,        /*  724 */
    0x43, 0x30,        /*  725 */
    0x43, 0x21,        /*  726 */
    0x44, 0x30,        /*  727 */
    0x50, 0x21,        /*  728 */
    0xab, 0x00,        /*  729 */
    0xb4, 0x00,        /*  730 */
    0x44, 0x30,        /*  731 */
    0x43, 0x21,        /*  732 */
    0x3a, 0x30,        /*  733 */
    0x50, 0x21,        /*  734 */
    0xa8, 0x00,        /*  735 */
    0x31, 0x30,        /*  736 */
    0x64, 0x21,        /*  737 */
    0x20, 0x11,        /*  738 */
    0x03, 0x18,        /*  739 */
    0x20, 0x15,        /*  740 */
    0x32, 0x30,        /*  741 */
    0x64, 0x21,        /*  742 */
    0x20, 0x12,        /*  743 */
    0x03, 0x18,        /*  744 */
    0x20, 0x16,        /*  745 */
    0x33, 0x30,        /*  746 */
    0x64, 0x21,        /*  747 */
    0xa0, 0x12,        /*  748 */
    0x03, 0x18,        /*  749 */
    0xa0, 0x16,        /*  750 */
    0x37, 0x30,        /*  751 */
    0x64, 0x21,        /*  752 */
    0x20, 0x13,        /*  753 */
    0x03, 0x18,        /*  754 */
    0x20, 0x17,        /*  755 */
    0x38, 0x30,        /*  756 */
    0x64, 0x21,        /*  757 */
    0x21, 0x13,        /*  758 */
    0x03, 0x18,        /*  759 */
    0x21, 0x17,        /*  760 */
    0x34, 0x30,        /*  761 */
    0x64, 0x21,        /*  762 */
    0xa1, 0x11,        /*  763 */
    0x03, 0x18,        /*  764 */
    0xa1, 0x15,        /*  765 */
    0x39, 0x30,        /*  766 */
    0x50, 0x21,        /*  767 */
    0xa7, 0x00,        /*  768 */
    0xa1, 0x2f,        /*  769 */
    0x22, 0x12,        /*  770 */
    0xae, 0x01,        /*  771 */
    0xaf, 0x01,        /*  772 */
    0xa5, 0x01,        /*  773 */
    0xb4, 0x01,        /*  774 */
    0x61, 0x30,        /*  775 */
    0x43, 0x21,        /*  776 */
    0xb4, 0x01,        /*  777 */
    0x0a, 0x30,        /*  778 */
    0x43, 0x21,        /*  779 */
    0xb4, 0x01,        /*  780 */
    0x0b, 0x30,        /*  781 */
    0x43, 0x21,        /*  782 */
    0x02, 0x30,        /*  783 */
    0xb4, 0x00,        /*  784 */
    0x60, 0x30,        /*  785 */
    0x43, 0x21,        /*  786 */
    0xb4, 0x01,        /*  787 */
    0x0c, 0x30,        /*  788 */
    0x43, 0x21,        /*  789 */
    0xb4, 0x01,        /*  790 */
    0x0d, 0x30,        /*  791 */
    0x43, 0x21,        /*  792 */
    0xb4, 0x01,        /*  793 */
    0x0e, 0x30,        /*  794 */
    0x43, 0x21,        /*  795 */
    0xb4, 0x01,        /*  796 */
    0x0f, 0x30,        /*  797 */
    0x43, 0x21,        /*  798 */
    0xb4, 0x01,        /*  799 */
    0x10, 0x30,        /*  800 */
    0x43, 0x21,        /*  801 */
    0xb4, 0x01,        /*  802 */
    0x12, 0x30,        /*  803 */
    0x43, 0x21,        /*  804 */
    0xb4, 0x01,        /*  805 */
    0x13, 0x30,        /*  806 */
    0x43, 0x21,        /*  807 */
    0xb4, 0x01,        /*  808 */
    0x14, 0x30,        /*  809 */
    0x43, 0x21,        /*  810 */
    0xb4, 0x01,        /*  811 */
    0x11, 0x30,        /*  812 */
    0x43, 0x21,        /*  813 */
    0xb4, 0x01,        /*  814 */
    0x63, 0x30,        /*  815 */
    0x43, 0x21,        /*  816 */
    0xb4, 0x01,        /*  817 */
    0x16, 0x30,        /*  818 */
    0x43, 0x21,        /*  819 */
    0xb4, 0x01,        /*  820 */
    0x64, 0x30,        /*  821 */
    0x43, 0x21,        /*  822 */
    0x15, 0x30,        /*  823 */
    0x49, 0x21,        /*  824 */
    0x18, 0x30,        /*  825 */
    0x49, 0x21,        /*  826 */
    0x17, 0x30,        /*  827 */
    0x49, 0x21,        /*  828 */
    0x06, 0x30,        /*  829 */
    0x49, 0x21,        /*  830 */
    0x00, 0x30,        /*  831 */
    0x49, 0x21,        /*  832 */
    0x02, 0x30,        /*  833 */
    0x49, 0x21,        /*  834 */
    0x03, 0x30,        /*  835 */
    0x49, 0x21,        /*  836 */
    0x04, 0x30,        /*  837 */
    0x49, 0x21,        /*  838 */
    0x06, 0x30,        /*  839 */
    0x49, 0x21,        /*  840 */
    0x07, 0x30,        /*  841 */
    0x49, 0x21,        /*  842 */
    0x08, 0x30,        /*  843 */
    0x49, 0x21,        /*  844 */
    0x09, 0x30,        /*  845 */
    0x49, 0x21,        /*  846 */
    0x05, 0x30,        /*  847 */
    0x49, 0x21,        /*  848 */
    0xb0, 0x01,        /*  849 */
    0xb1, 0x01,        /*  850 */
    0xa9, 0x01,        /*  851 */
    0xaa, 0x01,        /*  852 */
    0xac, 0x01,        /*  853 */
    0xac, 0x0a,        /*  854 */
    0xa1, 0x2f,        /*  855 */
    0x20, 0x30,        /*  856 */
    0x64, 0x21,        /*  857 */
    0xa0, 0x10,        /*  858 */
    0x03, 0x18,        /*  859 */
    0xa0, 0x14,        /*  860 */
    0xa0, 0x1c,        /*  861 */
    0xa1, 0x2f,        /*  862 */
    0x18, 0x30,        /*  863 */
    0x49, 0x21,        /*  864 */
    0x17, 0x30,        /*  865 */
    0x49, 0x21,        /*  866 */
    0xb4, 0x01,        /*  867 */
    0x14, 0x30,        /*  868 */
    0x43, 0x21,        /*  869 */
    0xb4, 0x01,        /*  870 */
    0x11, 0x30,        /*  871 */
    0x43, 0x21,        /*  872 */
    0xb4, 0x01,        /*  873 */
    0x10, 0x30,        /*  874 */
    0x43, 0x21,        /*  875 */
    0x20, 0x1d,        /*  876 */
    0x72, 0x2b,        /*  877 */
    0x28, 0x08,        /*  878 */
    0xb4, 0x00,        /*  879 */
    0x61, 0x30,        /*  880 */
    0x43, 0x21,        /*  881 */
    0x35, 0x30,        /*  882 */
    0x64, 0x21,        /*  883 */
    0x02, 0x30,        /*  884 */
    0x03, 0x1c,        /*  885 */
    0x82, 0x2b,        /*  886 */
    0x70, 0x21,        /*  887 */
    0x03, 0x30,        /*  888 */
    0xb4, 0x00,        /*  889 */
    0x60, 0x30,        /*  890 */
    0x43, 0x21,        /*  891 */
    0xb4, 0x01,        /*  892 */
    0xb4, 0x0a,        /*  893 */
    0x0e, 0x30,        /*  894 */
    0x43, 0x21,        /*  895 */
    0x02, 0x30,        /*  896 */
    0x5c, 0x2f,        /*  897 */
    0xb4, 0x00,        /*  898 */
    0x60, 0x30,        /*  899 */
    0x43, 0x21,        /*  900 */
    0x0a, 0x30,        /*  901 */
    0x49, 0x21,        /*  902 */
    0x20, 0x19,        /*  903 */
    0xb9, 0x2b,        /*  904 */
    0xbb, 0x2b,        /*  905 */
    0x00, 0x30,        /*  906 */
    0x64, 0x21,        /*  907 */
    0x03, 0x1c,        /*  908 */
    0xa1, 0x2f,        /*  909 */
    0xb4, 0x01,        /*  910 */
    0x0e, 0x30,        /*  911 */
    0x43, 0x21,        /*  912 */
    0x02, 0x30,        /*  913 */
    0xb4, 0x00,        /*  914 */
    0x60, 0x30,        /*  915 */
    0x43, 0x21,        /*  916 */
    0x01, 0x30,        /*  917 */
    0x49, 0x21,        /*  918 */
    0x00, 0x30,        /*  919 */
    0x49, 0x21,        /*  920 */
    0x03, 0x30,        /*  921 */
    0x5c, 0x2f,        /*  922 */
    0x01, 0x30,        /*  923 */
    0x64, 0x21,        /*  924 */
    0x03, 0x1c,        /*  925 */
    0xa1, 0x2f,        /*  926 */
    0x01, 0x30,        /*  927 */
    0x49, 0x21,        /*  928 */
    0x04, 0x30,        /*  929 */
    0x5c, 0x2f,        /*  930 */
    0x01, 0x30,        /*  931 */
    0x64, 0x21,        /*  932 */
    0x03, 0x1c,        /*  933 */
    0xa1, 0x2f,        /*  934 */
    0x20, 0x1d,        /*  935 */
    0xad, 0x2b,        /*  936 */
    0x28, 0x08,        /*  937 */
    0xb4, 0x00,        /*  938 */
    0x61, 0x30,        /*  939 */
    0x43, 0x21,        /*  940 */
    0x02, 0x30,        /*  941 */
    0xb4, 0x00,        /*  942 */
    0x60, 0x30,        /*  943 */
    0x43, 0x21,        /*  944 */
    0x0a, 0x30,        /*  945 */
    0x49, 0x21,        /*  946 */
    0x20, 0x1d,        /*  947 */
    0xbb, 0x2b,        /*  948 */
    0x28, 0x08,        /*  949 */
    0x02, 0x3a,        /*  950 */
    0x03, 0x19,        /*  951 */
    0x3f, 0x2c,        /*  952 */
    0x05, 0x30,        /*  953 */
    0x5c, 0x2f,        /*  954 */
    0x07, 0x30,        /*  955 */
    0x5c, 0x2f,        /*  956 */
    0x02, 0x30,        /*  957 */
    0x64, 0x21,        /*  958 */
    0x03, 0x1c,        /*  959 */
    0xa1, 0x2f,        /*  960 */
    0xb4, 0x01,        /*  961 */
    0xb4, 0x0a,        /*  962 */
    0x60, 0x30,        /*  963 */
    0x43, 0x21,        /*  964 */
    0x0b, 0x30,        /*  965 */
    0x49, 0x21,        /*  966 */
    0x02, 0x30,        /*  967 */
    0x4e, 0x2c,        /*  968 */
    0x03, 0x30,        /*  969 */
    0x64, 0x21,        /*  970 */
    0x03, 0x1c,        /*  971 */
    0xa1, 0x2f,        /*  972 */
    0x03, 0x30,        /*  973 */
    0x49, 0x21,        /*  974 */
    0x02, 0x30,        /*  975 */
    0xb4, 0x00,        /*  976 */
    0x60, 0x30,        /*  977 */
    0x43, 0x21,        /*  978 */
    0x69, 0x30,        /*  979 */
    0x64, 0x21,        /*  980 */
    0x03, 0x1c,        /*  981 */
    0x41, 0x2c,        /*  982 */
    0x61, 0x30,        /*  983 */
    0x50, 0x21,        /*  984 */
    0xad, 0x00,        /*  985 */
    0x20, 0x19,        /*  986 */
    0xe5, 0x2b,        /*  987 */
    0xad, 0x08,        /*  988 */
    0x03, 0x1d,        /*  989 */
    0xe2, 0x2b,        /*  990 */
    0xb4, 0x01,        /*  991 */
    0xb4, 0x0a,        /*  992 */
    0xe3, 0x2b,        /*  993 */
    0xb4, 0x01,        /*  994 */
    0x61, 0x30,        /*  995 */
    0x43, 0x21,        /*  996 */
    0x0a, 0x30,        /*  997 */
    0x49, 0x21,        /*  998 */
    0x20, 0x19,        /*  999 */
    0xeb, 0x2b,        /* 1000 */
    0x05, 0x30,        /* 1001 */
    0xf1, 0x2b,        /* 1002 */
    0xad, 0x08,        /* 1003 */
    0x03, 0x1d,        /* 1004 */
    0xf0, 0x2b,        /* 1005 */
    0x09, 0x30,        /* 1006 */
    0xf1, 0x2b,        /* 1007 */
    0x07, 0x30,        /* 1008 */
    0xac, 0x00,        /* 1009 */
    0xaa, 0x0a,        /* 1010 */
    0x0f, 0x30,        /* 1011 */
    0x2a, 0x02,        /* 1012 */
    0x03, 0x1c,        /* 1013 */
    0xa1, 0x2f,        /* 1014 */
    0xff, 0x30,        /* 1015 */
    0x5c, 0x2f,        /* 1016 */
    0x02, 0x30,        /* 1017 */
    0x64, 0x21,        /* 1018 */
    0x03, 0x1c,        /* 1019 */
    0xa1, 0x2f,        /* 1020 */
    0x02, 0x30,        /* 1021 */
    0x49, 0x21,        /* 1022 */
    0xb4, 0x01,        /* 1023 */
    0xb4, 0x0a,        /* 1024 */
    0x60, 0x30,        /* 1025 */
    0x43, 0x21,        /* 1026 */
    0x0b, 0x30,        /* 1027 */
    0x49, 0x21,        /* 1028 */
    0x08, 0x30,        /* 1029 */
    0x5c, 0x2f,        /* 1030 */
    0x03, 0x30,        /* 1031 */
    0x64, 0x21,        /* 1032 */
    0x03, 0x1c,        /* 1033 */
    0xa1, 0x2f,        /* 1034 */
    0x03, 0x30,        /* 1035 */
    0x49, 0x21,        /* 1036 */
    0x02, 0x30,        /* 1037 */
    0xb4, 0x00,        /* 1038 */
    0x60, 0x30,        /* 1039 */
    0x43, 0x21,        /* 1040 */
    0x69, 0x30,        /* 1041 */
    0x64, 0x21,        /* 1042 */
    0x03, 0x1c,        /* 1043 */
    0x41, 0x2c,        /* 1044 */
    0xb4, 0x01,        /* 1045 */
    0xb4, 0x0a,        /* 1046 */
    0x61, 0x30,        /* 1047 */
    0x43, 0x21,        /* 1048 */
    0x0a, 0x30,        /* 1049 */
    0x49, 0x21,        /* 1050 */
    0x09, 0x30,        /* 1051 */
    0x5c, 0x2f,        /* 1052 */
    0x02, 0x30,        /* 1053 */
    0x64, 0x21,        /* 1054 */
    0x03, 0x1c,        /* 1055 */
    0xa1, 0x2f,        /* 1056 */
    0x02, 0x30,        /* 1057 */
    0x49, 0x21,        /* 1058 */
    0xb4, 0x01,        /* 1059 */
    0xb4, 0x0a,        /* 1060 */
    0x60, 0x30,        /* 1061 */
    0x43, 0x21,        /* 1062 */
    0x0b, 0x30,        /* 1063 */
    0x49, 0x21,        /* 1064 */
    0x0a, 0x30,        /* 1065 */
    0x5c, 0x2f,        /* 1066 */
    0x03, 0x30,        /* 1067 */
    0x64, 0x21,        /* 1068 */
    0x03, 0x1c,        /* 1069 */
    0xa1, 0x2f,        /* 1070 */
    0x03, 0x30,        /* 1071 */
    0x49, 0x21,        /* 1072 */
    0x02, 0x30,        /* 1073 */
    0xb4, 0x00,        /* 1074 */
    0x60, 0x30,        /* 1075 */
    0x43, 0x21,        /* 1076 */
    0x69, 0x30,        /* 1077 */
    0x64, 0x21,        /* 1078 */
    0x03, 0x1c,        /* 1079 */
    0x41, 0x2c,        /* 1080 */
    0x02, 0x30,        /* 1081 */
    0xb4, 0x00,        /* 1082 */
    0x61, 0x30,        /* 1083 */
    0x43, 0x21,        /* 1084 */
    0x0a, 0x30,        /* 1085 */
    0x49, 0x21,        /* 1086 */
    0x0b, 0x30,        /* 1087 */
    0x5c, 0x2f,        /* 1088 */
    0x0c, 0x30,        /* 1089 */
    0x5c, 0x2f,        /* 1090 */
    0x02, 0x30,        /* 1091 */
    0x64, 0x21,        /* 1092 */
    0x03, 0x1c,        /* 1093 */
    0xa1, 0x2f,        /* 1094 */
    0x02, 0x30,        /* 1095 */
    0x49, 0x21,        /* 1096 */
    0xb4, 0x01,        /* 1097 */
    0xb4, 0x0a,        /* 1098 */
    0x60, 0x30,        /* 1099 */
    0x43, 0x21,        /* 1100 */
    0x0b, 0x30,        /* 1101 */
    0x49, 0x21,        /* 1102 */
    0x06, 0x30,        /* 1103 */
    0x5c, 0x2f,        /* 1104 */
    0xaa, 0x01,        /* 1105 */
    0x02, 0x30,        /* 1106 */
    0xb4, 0x00,        /* 1107 */
    0x60, 0x30,        /* 1108 */
    0x43, 0x21,        /* 1109 */
    0xb4, 0x01,        /* 1110 */
    0xb4, 0x0a,        /* 1111 */
    0x0c, 0x30,        /* 1112 */
    0x43, 0x21,        /* 1113 */
    0x23, 0x30,        /* 1114 */
    0x64, 0x21,        /* 1115 */
    0x03, 0x1c,        /* 1116 */
    0x5a, 0x2c,        /* 1117 */
    0xb4, 0x01,        /* 1118 */
    0x0c, 0x30,        /* 1119 */
    0x43, 0x21,        /* 1120 */
    0xb4, 0x01,        /* 1121 */
    0x60, 0x30,        /* 1122 */
    0x43, 0x21,        /* 1123 */
    0x0d, 0x30,        /* 1124 */
    0x5c, 0x2f,        /* 1125 */
    0x04, 0x30,        /* 1126 */
    0x64, 0x21,        /* 1127 */
    0x03, 0x1c,        /* 1128 */
    0xa1, 0x2f,        /* 1129 */
    0x04, 0x30,        /* 1130 */
    0x49, 0x21,        /* 1131 */
    0x6a, 0x30,        /* 1132 */
    0x64, 0x21,        /* 1133 */
    0x03, 0x1c,        /* 1134 */
    0x7d, 0x2c,        /* 1135 */
    0x02, 0x30,        /* 1136 */
    0xb4, 0x00,        /* 1137 */
    0x60, 0x30,        /* 1138 */
    0x43, 0x21,        /* 1139 */
    0xac, 0x01,        /* 1140 */
    0xac, 0x0a,        /* 1141 */
    0xaa, 0x0a,        /* 1142 */
    0x10, 0x30,        /* 1143 */
    0x2a, 0x02,        /* 1144 */
    0x03, 0x1c,        /* 1145 */
    0xa1, 0x2f,        /* 1146 */
    0xfe, 0x30,        /* 1147 */
    0x5c, 0x2f,        /* 1148 */
    0x03, 0x30,        /* 1149 */
    0xb4, 0x00,        /* 1150 */
    0x60, 0x30,        /* 1151 */
    0x43, 0x21,        /* 1152 */
    0xb4, 0x01,        /* 1153 */
    0xb4, 0x0a,        /* 1154 */
    0x0d, 0x30,        /* 1155 */
    0x43, 0x21,        /* 1156 */
    0x0e, 0x30,        /* 1157 */
    0x5c, 0x2f,        /* 1158 */
    0x05, 0x30,        /* 1159 */
    0x64, 0x21,        /* 1160 */
    0x03, 0x1c,        /* 1161 */
    0xa1, 0x2f,        /* 1162 */
    0xb4, 0x01,        /* 1163 */
    0x0d, 0x30,        /* 1164 */
    0x43, 0x21,        /* 1165 */
    0x03, 0x30,        /* 1166 */
    0xb4, 0x00,        /* 1167 */
    0x60, 0x30,        /* 1168 */
    0x43, 0x21,        /* 1169 */
    0x05, 0x30,        /* 1170 */
    0x49, 0x21,        /* 1171 */
    0x01, 0x30,        /* 1172 */
    0x49, 0x21,        /* 1173 */
    0x10, 0x30,        /* 1174 */
    0x5c, 0x2f,        /* 1175 */
    0x01, 0x30,        /* 1176 */
    0x64, 0x21,        /* 1177 */
    0x03, 0x1c,        /* 1178 */
    0xa1, 0x2f,        /* 1179 */
    0x01, 0x30,        /* 1180 */
    0x49, 0x21,        /* 1181 */
    0x11, 0x30,        /* 1182 */
    0x5c, 0x2f,        /* 1183 */
    0x01, 0x30,        /* 1184 */
    0x64, 0x21,        /* 1185 */
    0x03, 0x1c,        /* 1186 */
    0xa1, 0x2f,        /* 1187 */
    0xb4, 0x01,        /* 1188 */
    0xb4, 0x0a,        /* 1189 */
    0x0f, 0x30,        /* 1190 */
    0x43, 0x21,        /* 1191 */
    0x12, 0x30,        /* 1192 */
    0x5c, 0x2f,        /* 1193 */
    0x06, 0x30,        /* 1194 */
    0x64, 0x21,        /* 1195 */
    0x03, 0x1c,        /* 1196 */
    0xa1, 0x2f,        /* 1197 */
    0xb4, 0x01,        /* 1198 */
    0x0f, 0x30,        /* 1199 */
    0x43, 0x21,        /* 1200 */
    0x06, 0x30,        /* 1201 */
    0x49, 0x21,        /* 1202 */
    0xb4, 0x01,        /* 1203 */
    0xb4, 0x0a,        /* 1204 */
    0x10, 0x30,        /* 1205 */
    0x43, 0x21,        /* 1206 */
    0x01, 0x30,        /* 1207 */
    0x49, 0x21,        /* 1208 */
    0x13, 0x30,        /* 1209 */
    0x5c, 0x2f,        /* 1210 */
    0x24, 0x30,        /* 1211 */
    0x49, 0x21,        /* 1212 */
    0xad, 0x01,        /* 1213 */
    0x2d, 0x08,        /* 1214 */
    0x03, 0x3a,        /* 1215 */
    0x03, 0x19,        /* 1216 */
    0xe9, 0x2c,        /* 1217 */
    0xad, 0x08,        /* 1218 */
    0x03, 0x1d,        /* 1219 */
    0xc7, 0x2c,        /* 1220 */
    0x3e, 0x30,        /* 1221 */
    0xd0, 0x2c,        /* 1222 */
    0x2d, 0x0b,        /* 1223 */
    0xcb, 0x2c,        /* 1224 */
    0x3f, 0x30,        /* 1225 */
    0xd0, 0x2c,        /* 1226 */
    0x2d, 0x08,        /* 1227 */
    0x02, 0x3a,        /* 1228 */
    0x03, 0x1d,        /* 1229 */
    0xd2, 0x2c,        /* 1230 */
    0x40, 0x30,        /* 1231 */
    0x50, 0x21,        /* 1232 */
    0xab, 0x00,        /* 1233 */
    0xaa, 0x01,        /* 1234 */
    0xf0, 0x30,        /* 1235 */
    0xab, 0x05,        /* 1236 */
    0x03, 0x10,        /* 1237 */
    0xab, 0x0c,        /* 1238 */
    0x2b, 0x08,        /* 1239 */
    0x2a, 0x02,        /* 1240 */
    0x03, 0x18,        /* 1241 */
    0xe3, 0x2c,        /* 1242 */
    0x24, 0x30,        /* 1243 */
    0x64, 0x21,        /* 1244 */
    0x03, 0x1c,        /* 1245 */
    0xd7, 0x2c,        /* 1246 */
    0x24, 0x30,        /* 1247 */
    0x49, 0x21,        /* 1248 */
    0xaa, 0x0a,        /* 1249 */
    0xd7, 0x2c,        /* 1250 */
    0x1a, 0x30,        /* 1251 */
    0x49, 0x21,        /* 1252 */
    0xad, 0x0a,        /* 1253 */
    0x2d, 0x08,        /* 1254 */
    0x87, 0x00,        /* 1255 */
    0xbe, 0x2c,        /* 1256 */
    0x16, 0x30,        /* 1257 */
    0x5c, 0x2f,        /* 1258 */
    0x01, 0x30,        /* 1259 */
    0x64, 0x21,        /* 1260 */
    0x03, 0x1c,        /* 1261 */
    0xa1, 0x2f,        /* 1262 */
    0x01, 0x30,        /* 1263 */
    0x49, 0x21,        /* 1264 */
    0xb4, 0x01,        /* 1265 */
    0x14, 0x30,        /* 1266 */
    0x43, 0x21,        /* 1267 */
    0xb4, 0x01,        /* 1268 */
    0x12, 0x30,        /* 1269 */
    0x43, 0x21,        /* 1270 */
    0x15, 0x30,        /* 1271 */
    0x5c, 0x2f,        /* 1272 */
    0x01, 0x30,        /* 1273 */
    0x64, 0x21,        /* 1274 */
    0x03, 0x1c,        /* 1275 */
    0xa1, 0x2f,        /* 1276 */
    0x01, 0x30,        /* 1277 */
    0x49, 0x21,        /* 1278 */
    0xb4, 0x01,        /* 1279 */
    0xb4, 0x0a,        /* 1280 */
    0x14, 0x30,        /* 1281 */
    0x43, 0x21,        /* 1282 */
    0x17, 0x30,        /* 1283 */
    0x5c, 0x2f,        /* 1284 */
    0xb4, 0x01,        /* 1285 */
    0xb4, 0x0a,        /* 1286 */
    0x11, 0x30,        /* 1287 */
    0x43, 0x21,        /* 1288 */
    0x22, 0x30,        /* 1289 */
    0x64, 0x21,        /* 1290 */
    0x03, 0x1c,        /* 1291 */
    0xa1, 0x2f,        /* 1292 */
    0xb4, 0x01,        /* 1293 */
    0x11, 0x30,        /* 1294 */
    0x43, 0x21,        /* 1295 */
    0x14, 0x30,        /* 1296 */
    0x5c, 0x2f,        /* 1297 */
    0x25, 0x30,        /* 1298 */
    0x49, 0x21,        /* 1299 */
    0xad, 0x01,        /* 1300 */
    0x2d, 0x08,        /* 1301 */
    0x03, 0x3a,        /* 1302 */
    0x03, 0x19,        /* 1303 */
    0x44, 0x2d,        /* 1304 */
    0xad, 0x08,        /* 1305 */
    0x03, 0x1d,        /* 1306 */
    0x1e, 0x2d,        /* 1307 */
    0x3e, 0x30,        /* 1308 */
    0x27, 0x2d,        /* 1309 */
    0x2d, 0x0b,        /* 1310 */
    0x22, 0x2d,        /* 1311 */
    0x3f, 0x30,        /* 1312 */
    0x27, 0x2d,        /* 1313 */
    0x2d, 0x08,        /* 1314 */
    0x02, 0x3a,        /* 1315 */
    0x03, 0x1d,        /* 1316 */
    0x29, 0x2d,        /* 1317 */
    0x40, 0x30,        /* 1318 */
    0x50, 0x21,        /* 1319 */
    0xab, 0x00,        /* 1320 */
    0xaa, 0x01,        /* 1321 */
    0x0f, 0x30,        /* 1322 */
    0xab, 0x05,        /* 1323 */
    0x03, 0x10,        /* 1324 */
    0xab, 0x0d,        /* 1325 */
    0x03, 0x10,        /* 1326 */
    0xab, 0x0d,        /* 1327 */
    0x03, 0x10,        /* 1328 */
    0xab, 0x0d,        /* 1329 */
    0x2b, 0x08,        /* 1330 */
    0x2a, 0x02,        /* 1331 */
    0x03, 0x18,        /* 1332 */
    0x3e, 0x2d,        /* 1333 */
    0x25, 0x30,        /* 1334 */
    0x64, 0x21,        /* 1335 */
    0x03, 0x1c,        /* 1336 */
    0x32, 0x2d,        /* 1337 */
    0x25, 0x30,        /* 1338 */
    0x49, 0x21,        /* 1339 */
    0xaa, 0x0a,        /* 1340 */
    0x32, 0x2d,        /* 1341 */
    0x19, 0x30,        /* 1342 */
    0x49, 0x21,        /* 1343 */
    0xad, 0x0a,        /* 1344 */
    0x2d, 0x08,        /* 1345 */
    0x87, 0x00,        /* 1346 */
    0x15, 0x2d,        /* 1347 */
    0x61, 0x30,        /* 1348 */
    0x50, 0x21,        /* 1349 */
    0xad, 0x00,        /* 1350 */
    0x03, 0x30,        /* 1351 */
    0xad, 0x05,        /* 1352 */
    0x2d, 0x08,        /* 1353 */
    0x02, 0x3a,        /* 1354 */
    0x03, 0x19,        /* 1355 */
    0x51, 0x2d,        /* 1356 */
    0x2d, 0x08,        /* 1357 */
    0x03, 0x3a,        /* 1358 */
    0x03, 0x1d,        /* 1359 */
    0x53, 0x2d,        /* 1360 */
    0xd7, 0x30,        /* 1361 */
    0x58, 0x2d,        /* 1362 */
    0x2d, 0x0b,        /* 1363 */
    0x57, 0x2d,        /* 1364 */
    0xc7, 0x30,        /* 1365 */
    0x58, 0x2d,        /* 1366 */
    0xe0, 0x30,        /* 1367 */
    0xa6, 0x00,        /* 1368 */
    0xb4, 0x01,        /* 1369 */
    0xb4, 0x0a,        /* 1370 */
    0x12, 0x30,        /* 1371 */
    0x43, 0x21,        /* 1372 */
    0x1a, 0x30,        /* 1373 */
    0x5c, 0x2f,        /* 1374 */
    0xb4, 0x01,        /* 1375 */
    0xb4, 0x0a,        /* 1376 */
    0x13, 0x30,        /* 1377 */
    0x43, 0x21,        /* 1378 */
    0xaa, 0x01,        /* 1379 */
    0x20, 0x1a,        /* 1380 */
    0xa1, 0x1d,        /* 1381 */
    0x89, 0x2d,        /* 1382 */
    0x00, 0x30,        /* 1383 */
    0x20, 0x1b,        /* 1384 */
    0x01, 0x30,        /* 1385 */
    0xb4, 0x00,        /* 1386 */
    0x63, 0x30,        /* 1387 */
    0x43, 0x21,        /* 1388 */
    0x27, 0x08,        /* 1389 */
    0xb4, 0x00,        /* 1390 */
    0x62, 0x30,        /* 1391 */
    0x43, 0x21,        /* 1392 */
    0xa0, 0x13,        /* 1393 */
    0x20, 0x1b,        /* 1394 */
    0xa0, 0x17,        /* 1395 */
    0xa0, 0x1e,        /* 1396 */
    0x82, 0x2d,        /* 1397 */
    0x00, 0x30,        /* 1398 */
    0x21, 0x1b,        /* 1399 */
    0x01, 0x30,        /* 1400 */
    0xb4, 0x00,        /* 1401 */
    0x64, 0x30,        /* 1402 */
    0x43, 0x21,        /* 1403 */
    0x21, 0x10,        /* 1404 */
    0x21, 0x1b,        /* 1405 */
    0x21, 0x14,        /* 1406 */
    0x17, 0x30,        /* 1407 */
    0x49, 0x21,        /* 1408 */
    0xba, 0x2d,        /* 1409 */
    0x20, 0x1f,        /* 1410 */
    0xbe, 0x2d,        /* 1411 */
    0x1c, 0x30,        /* 1412 */
    0xac, 0x00,        /* 1413 */
    0x17, 0x30,        /* 1414 */
    0x49, 0x21,        /* 1415 */
    0xbe, 0x2d,        /* 1416 */
    0x87, 0x01,        /* 1417 */
    0x2b, 0x22,        /* 1418 */
    0xad, 0x00,        /* 1419 */
    0x20, 0x1a,        /* 1420 */
    0x93, 0x2d,        /* 1421 */
    0xad, 0x08,        /* 1422 */
    0x03, 0x1d,        /* 1423 */
    0x96, 0x2d,        /* 1424 */
    0xa0, 0x13,        /* 1425 */
    0x97, 0x2d,        /* 1426 */
    0xa0, 0x13,        /* 1427 */
    0x20, 0x1f,        /* 1428 */
    0x97, 0x2d,        /* 1429 */
    0xa0, 0x17,        /* 1430 */
    0xa0, 0x1a,        /* 1431 */
    0x9d, 0x2d,        /* 1432 */
    0xa3, 0x1a,        /* 1433 */
    0xa0, 0x2d,        /* 1434 */
    0x21, 0x10,        /* 1435 */
    0xa1, 0x2d,        /* 1436 */
    0x21, 0x10,        /* 1437 */
    0x21, 0x1f,        /* 1438 */
    0xa1, 0x2d,        /* 1439 */
    0x21, 0x14,        /* 1440 */
    0x27, 0x08,        /* 1441 */
    0xa1, 0x19,        /* 1442 */
    0xa3, 0x00,        /* 1443 */
    0x00, 0x30,        /* 1444 */
    0xa0, 0x1b,        /* 1445 */
    0x01, 0x30,        /* 1446 */
    0xb4, 0x00,        /* 1447 */
    0x63, 0x30,        /* 1448 */
    0x43, 0x21,        /* 1449 */
    0x00, 0x30,        /* 1450 */
    0x21, 0x18,        /* 1451 */
    0x01, 0x30,        /* 1452 */
    0xb4, 0x00,        /* 1453 */
    0x64, 0x30,        /* 1454 */
    0x43, 0x21,        /* 1455 */
    0x23, 0x08,        /* 1456 */
    0xb4, 0x00,        /* 1457 */
    0x62, 0x30,        /* 1458 */
    0x43, 0x21,        /* 1459 */
    0x17, 0x30,        /* 1460 */
    0x49, 0x21,        /* 1461 */
    0xa0, 0x1f,        /* 1462 */
    0xba, 0x2d,        /* 1463 */
    0xa0, 0x1e,        /* 1464 */
    0xbc, 0x2d,        /* 1465 */
    0x1d, 0x30,        /* 1466 */
    0xbd, 0x2d,        /* 1467 */
    0x1c, 0x30,        /* 1468 */
    0xac, 0x00,        /* 1469 */
    0xb4, 0x01,        /* 1470 */
    0x13, 0x30,        /* 1471 */
    0x43, 0x21,        /* 1472 */
    0xa9, 0x21,        /* 1473 */
    0x41, 0x30,        /* 1474 */
    0x50, 0x21,        /* 1475 */
    0xfa, 0x00,        /* 1476 */
    0x7a, 0x18,        /* 1477 */
    0x21, 0x1a,        /* 1478 */
    0xa1, 0x2f,        /* 1479 */
    0x08, 0x30,        /* 1480 */
    0x70, 0x21,        /* 1481 */
    0xad, 0x01,        /* 1482 */
    0xb0, 0x01,        /* 1483 */
    0xb1, 0x01,        /* 1484 */
    0xad, 0x01,        /* 1485 */
    0x02, 0x30,        /* 1486 */
    0x70, 0x21,        /* 1487 */
    0xb4, 0x01,        /* 1488 */
    0xb4, 0x0a,        /* 1489 */
    0x1c, 0x30,        /* 1490 */
    0x43, 0x21,        /* 1491 */
    0xcf, 0x30,        /* 1492 */
    0x50, 0x21,        /* 1493 */
    0xab, 0x00,        /* 1494 */
    0xb4, 0x01,        /* 1495 */
    0x1c, 0x30,        /* 1496 */
    0x43, 0x21,        /* 1497 */
    0x2b, 0x08,        /* 1498 */
    0xb0, 0x07,        /* 1499 */
    0x03, 0x18,        /* 1500 */
    0xb1, 0x0a,        /* 1501 */
    0xad, 0x0a,        /* 1502 */
    0x10, 0x30,        /* 1503 */
    0x2d, 0x02,        /* 1504 */
    0x03, 0x1c,        /* 1505 */
    0xce, 0x2d,        /* 1506 */
    0x03, 0x10,        /* 1507 */
    0xb1, 0x0c,        /* 1508 */
    0xb0, 0x0c,        /* 1509 */
    0x03, 0x10,        /* 1510 */
    0xb1, 0x0c,        /* 1511 */
    0xb0, 0x0c,        /* 1512 */
    0x03, 0x10,        /* 1513 */
    0xb1, 0x0c,        /* 1514 */
    0xb0, 0x0c,        /* 1515 */
    0x61, 0x30,        /* 1516 */
    0x50, 0x21,        /* 1517 */
    0xad, 0x00,        /* 1518 */
    0xad, 0x1c,        /* 1519 */
    0xf7, 0x2d,        /* 1520 */
    0xa0, 0x1b,        /* 1521 */
    0xf5, 0x2d,        /* 1522 */
    0x96, 0x30,        /* 1523 */
    0xfc, 0x2d,        /* 1524 */
    0x9c, 0x30,        /* 1525 */
    0xfc, 0x2d,        /* 1526 */
    0xa0, 0x1b,        /* 1527 */
    0xfb, 0x2d,        /* 1528 */
    0xd4, 0x30,        /* 1529 */
    0xfc, 0x2d,        /* 1530 */
    0xdd, 0x30,        /* 1531 */
    0xab, 0x00,        /* 1532 */
    0x30, 0x08,        /* 1533 */
    0xad, 0x00,        /* 1534 */
    0x2b, 0x08,        /* 1535 */
    0xb2, 0x00,        /* 1536 */
    0x2d, 0x08,        /* 1537 */
    0x80, 0x21,        /* 1538 */
    0xad, 0x00,        /* 1539 */
    0x87, 0x00,        /* 1540 */
    0x2d, 0x08,        /* 1541 */
    0xf8, 0x39,        /* 1542 */
    0x2d, 0x19,        /* 1543 */
    0x08, 0x3e,        /* 1544 */
    0xab, 0x00,        /* 1545 */
    0x87, 0x00,        /* 1546 */
    0x61, 0x30,        /* 1547 */
    0x50, 0x21,        /* 1548 */
    0xad, 0x00,        /* 1549 */
    0x47, 0x2e,        /* 1550 */
    0xad, 0x08,        /* 1551 */
    0x03, 0x1d,        /* 1552 */
    0x14, 0x2e,        /* 1553 */
    0x06, 0x30,        /* 1554 */
    0x45, 0x2e,        /* 1555 */
    0x2d, 0x0b,        /* 1556 */
    0x18, 0x2e,        /* 1557 */
    0x08, 0x30,        /* 1558 */
    0x45, 0x2e,        /* 1559 */
    0x0a, 0x30,        /* 1560 */
    0x45, 0x2e,        /* 1561 */
    0xad, 0x08,        /* 1562 */
    0x03, 0x1d,        /* 1563 */
    0x1f, 0x2e,        /* 1564 */
    0xab, 0x01,        /* 1565 */
    0x72, 0x2e,        /* 1566 */
    0x2d, 0x0b,        /* 1567 */
    0x23, 0x2e,        /* 1568 */
    0x02, 0x30,        /* 1569 */
    0x45, 0x2e,        /* 1570 */
    0x04, 0x30,        /* 1571 */
    0x45, 0x2e,        /* 1572 */
    0xad, 0x08,        /* 1573 */
    0x03, 0x1d,        /* 1574 */
    0x2a, 0x2e,        /* 1575 */
    0x0c, 0x30,        /* 1576 */
    0x45, 0x2e,        /* 1577 */
    0x2d, 0x0b,        /* 1578 */
    0x2e, 0x2e,        /* 1579 */
    0x0e, 0x30,        /* 1580 */
    0x45, 0x2e,        /* 1581 */
    0x10, 0x30,        /* 1582 */
    0x45, 0x2e,        /* 1583 */
    0xad, 0x08,        /* 1584 */
    0x03, 0x1d,        /* 1585 */
    0x35, 0x2e,        /* 1586 */
    0x12, 0x30,        /* 1587 */
    0x45, 0x2e,        /* 1588 */
    0x2d, 0x0b,        /* 1589 */
    0x39, 0x2e,        /* 1590 */
    0x14, 0x30,        /* 1591 */
    0x45, 0x2e,        /* 1592 */
    0x16, 0x30,        /* 1593 */
    0x45, 0x2e,        /* 1594 */
    0xad, 0x08,        /* 1595 */
    0x03, 0x1d,        /* 1596 */
    0x40, 0x2e,        /* 1597 */
    0x18, 0x30,        /* 1598 */
    0x45, 0x2e,        /* 1599 */
    0x2d, 0x0b,        /* 1600 */
    0x44, 0x2e,        /* 1601 */
    0x1a, 0x30,        /* 1602 */
    0x45, 0x2e,        /* 1603 */
    0x1c, 0x30,        /* 1604 */
    0xab, 0x00,        /* 1605 */
    0x72, 0x2e,        /* 1606 */
    0x23, 0x08,        /* 1607 */
    0x0f, 0x39,        /* 1608 */
    0xfc, 0x00,        /* 1609 */
    0xfd, 0x01,        /* 1610 */
    0x6f, 0x2e,        /* 1611 */
    0x7c, 0x08,        /* 1612 */
    0x01, 0x3a,        /* 1613 */
    0x03, 0x19,        /* 1614 */
    0x0f, 0x2e,        /* 1615 */
    0x03, 0x3a,        /* 1616 */
    0x03, 0x19,        /* 1617 */
    0x0f, 0x2e,        /* 1618 */
    0x01, 0x3a,        /* 1619 */
    0x03, 0x19,        /* 1620 */
    0x0f, 0x2e,        /* 1621 */
    0x04, 0x3a,        /* 1622 */
    0x03, 0x19,        /* 1623 */
    0x1a, 0x2e,        /* 1624 */
    0x0e, 0x3a,        /* 1625 */
    0x03, 0x19,        /* 1626 */
    0x25, 0x2e,        /* 1627 */
    0x03, 0x3a,        /* 1628 */
    0x03, 0x19,        /* 1629 */
    0x25, 0x2e,        /* 1630 */
    0x01, 0x3a,        /* 1631 */
    0x03, 0x19,        /* 1632 */
    0x25, 0x2e,        /* 1633 */
    0x07, 0x3a,        /* 1634 */
    0x03, 0x19,        /* 1635 */
    0x30, 0x2e,        /* 1636 */
    0x01, 0x3a,        /* 1637 */
    0x03, 0x19,        /* 1638 */
    0x3b, 0x2e,        /* 1639 */
    0x03, 0x3a,        /* 1640 */
    0x03, 0x19,        /* 1641 */
    0x3b, 0x2e,        /* 1642 */
    0x01, 0x3a,        /* 1643 */
    0x03, 0x19,        /* 1644 */
    0x3b, 0x2e,        /* 1645 */
    0x72, 0x2e,        /* 1646 */
    0x7d, 0x08,        /* 1647 */
    0x03, 0x19,        /* 1648 */
    0x4c, 0x2e,        /* 1649 */
    0xa0, 0x1f,        /* 1650 */
    0x75, 0x2e,        /* 1651 */
    0x2b, 0x14,        /* 1652 */
    0xb4, 0x01,        /* 1653 */
    0xb4, 0x0a,        /* 1654 */
    0x1c, 0x30,        /* 1655 */
    0x43, 0x21,        /* 1656 */
    0x2b, 0x08,        /* 1657 */
    0xb4, 0x00,        /* 1658 */
    0xcb, 0x30,        /* 1659 */
    0x43, 0x21,        /* 1660 */
    0x07, 0x08,        /* 1661 */
    0xb4, 0x00,        /* 1662 */
    0xcc, 0x30,        /* 1663 */
    0x43, 0x21,        /* 1664 */
    0xb4, 0x01,        /* 1665 */
    0x1c, 0x30,        /* 1666 */
    0x45, 0x2f,        /* 1667 */
    0xb4, 0x01,        /* 1668 */
    0x13, 0x30,        /* 1669 */
    0x43, 0x21,        /* 1670 */
    0x64, 0x30,        /* 1671 */
    0x64, 0x21,        /* 1672 */
    0xa1, 0x10,        /* 1673 */
    0x03, 0x18,        /* 1674 */
    0xa1, 0x14,        /* 1675 */
    0x36, 0x30,        /* 1676 */
    0x64, 0x21,        /* 1677 */
    0x21, 0x11,        /* 1678 */
    0x03, 0x18,        /* 1679 */
    0x21, 0x15,        /* 1680 */
    0x62, 0x30,        /* 1681 */
    0x50, 0x21,        /* 1682 */
    0x0f, 0x39,        /* 1683 */
    0xad, 0x00,        /* 1684 */
    0x07, 0x3a,        /* 1685 */
    0x03, 0x19,        /* 1686 */
    0x21, 0x1d,        /* 1687 */
    0xb7, 0x2e,        /* 1688 */
    0xb4, 0x01,        /* 1689 */
    0xb4, 0x0a,        /* 1690 */
    0x16, 0x30,        /* 1691 */
    0x43, 0x21,        /* 1692 */
    0x09, 0x30,        /* 1693 */
    0x64, 0x21,        /* 1694 */
    0x03, 0x18,        /* 1695 */
    0xaa, 0x2e,        /* 1696 */
    0x07, 0x30,        /* 1697 */
    0x64, 0x21,        /* 1698 */
    0x03, 0x1c,        /* 1699 */
    0x9d, 0x2e,        /* 1700 */
    0x6e, 0x30,        /* 1701 */
    0x50, 0x21,        /* 1702 */
    0xa3, 0x00,        /* 1703 */
    0xe2, 0x21,        /* 1704 */
    0x9d, 0x2e,        /* 1705 */
    0xb4, 0x01,        /* 1706 */
    0x16, 0x30,        /* 1707 */
    0x43, 0x21,        /* 1708 */
    0x09, 0x30,        /* 1709 */
    0x49, 0x21,        /* 1710 */
    0xa0, 0x15,        /* 1711 */
    0xa1, 0x18,        /* 1712 */
    0xa0, 0x11,        /* 1713 */
    0x6d, 0x30,        /* 1714 */
    0x64, 0x21,        /* 1715 */
    0x03, 0x1c,        /* 1716 */
    0xe2, 0x2e,        /* 1717 */
    0xdc, 0x2e,        /* 1718 */
    0xb0, 0x01,        /* 1719 */
    0xb1, 0x01,        /* 1720 */
    0x01, 0x30,        /* 1721 */
    0x49, 0x21,        /* 1722 */
    0xcd, 0x2e,        /* 1723 */
    0x07, 0x30,        /* 1724 */
    0x64, 0x21,        /* 1725 */
    0x03, 0x1c,        /* 1726 */
    0xc4, 0x2e,        /* 1727 */
    0x6e, 0x30,        /* 1728 */
    0x50, 0x21,        /* 1729 */
    0xa3, 0x00,        /* 1730 */
    0xe2, 0x21,        /* 1731 */
    0x01, 0x30,        /* 1732 */
    0x64, 0x21,        /* 1733 */
    0x03, 0x1c,        /* 1734 */
    0xbc, 0x2e,        /* 1735 */
    0x01, 0x30,        /* 1736 */
    0x49, 0x21,        /* 1737 */
    0xb0, 0x0a,        /* 1738 */
    0x03, 0x19,        /* 1739 */
    0xb1, 0x0a,        /* 1740 */
    0x05, 0x30,        /* 1741 */
    0x31, 0x02,        /* 1742 */
    0x00, 0x30,        /* 1743 */
    0x03, 0x19,        /* 1744 */
    0x30, 0x02,        /* 1745 */
    0x03, 0x1c,        /* 1746 */
    0xc4, 0x2e,        /* 1747 */
    0x21, 0x30,        /* 1748 */
    0x64, 0x21,        /* 1749 */
    0x03, 0x18,        /* 1750 */
    0x5b, 0x2f,        /* 1751 */
    0xa0, 0x15,        /* 1752 */
    0xa1, 0x1c,        /* 1753 */
    0xdc, 0x2e,        /* 1754 */
    0xa0, 0x11,        /* 1755 */
    0x00, 0x30,        /* 1756 */
    0xa0, 0x19,        /* 1757 */
    0x01, 0x30,        /* 1758 */
    0xb4, 0x00,        /* 1759 */
    0x64, 0x30,        /* 1760 */
    0x43, 0x21,        /* 1761 */
    0x1d, 0x30,        /* 1762 */
    0x5c, 0x2f,        /* 1763 */
    0xb4, 0x01,        /* 1764 */
    0x13, 0x30,        /* 1765 */
    0x43, 0x21,        /* 1766 */
    0xb0, 0x01,        /* 1767 */
    0xb1, 0x01,        /* 1768 */
    0xae, 0x01,        /* 1769 */
    0xaf, 0x01,        /* 1770 */
    0x01, 0x30,        /* 1771 */
    0x49, 0x21,        /* 1772 */
    0x31, 0x08,        /* 1773 */
    0x05, 0x3a,        /* 1774 */
    0x30, 0x04,        /* 1775 */
    0x03, 0x19,        /* 1776 */
    0x25, 0x2f,        /* 1777 */
    0x01, 0x30,        /* 1778 */
    0x64, 0x21,        /* 1779 */
    0x03, 0x1c,        /* 1780 */
    0xfd, 0x2e,        /* 1781 */
    0x01, 0x30,        /* 1782 */
    0x49, 0x21,        /* 1783 */
    0xb0, 0x0a,        /* 1784 */
    0x03, 0x19,        /* 1785 */
    0xb1, 0x0a,        /* 1786 */
    0xae, 0x01,        /* 1787 */
    0xaf, 0x01,        /* 1788 */
    0x07, 0x30,        /* 1789 */
    0x64, 0x21,        /* 1790 */
    0x03, 0x1c,        /* 1791 */
    0x05, 0x2f,        /* 1792 */
    0x6e, 0x30,        /* 1793 */
    0x50, 0x21,        /* 1794 */
    0xa3, 0x00,        /* 1795 */
    0xe2, 0x21,        /* 1796 */
    0xae, 0x0a,        /* 1797 */
    0x03, 0x19,        /* 1798 */
    0xaf, 0x0a,        /* 1799 */
    0x2e, 0x0a,        /* 1800 */
    0x3f, 0x30,        /* 1801 */
    0x03, 0x19,        /* 1802 */
    0x2f, 0x06,        /* 1803 */
    0x03, 0x1d,        /* 1804 */
    0x10, 0x2f,        /* 1805 */
    0xac, 0x01,        /* 1806 */
    0x25, 0x2f,        /* 1807 */
    0x42, 0x30,        /* 1808 */
    0x50, 0x21,        /* 1809 */
    0x03, 0x3a,        /* 1810 */
    0x03, 0x1d,        /* 1811 */
    0x1c, 0x2f,        /* 1812 */
    0xb4, 0x01,        /* 1813 */
    0x44, 0x30,        /* 1814 */
    0x43, 0x21,        /* 1815 */
    0xb4, 0x01,        /* 1816 */
    0xb4, 0x0a,        /* 1817 */
    0x43, 0x30,        /* 1818 */
    0x43, 0x21,        /* 1819 */
    0x21, 0x30,        /* 1820 */
    0x64, 0x21,        /* 1821 */
    0x03, 0x18,        /* 1822 */
    0x25, 0x2f,        /* 1823 */
    0x31, 0x08,        /* 1824 */
    0xad, 0x00,        /* 1825 */
    0x05, 0x3a,        /* 1826 */
    0x03, 0x1d,        /* 1827 */
    0xed, 0x2e,        /* 1828 */
    0x2e, 0x0a,        /* 1829 */
    0x3f, 0x30,        /* 1830 */
    0x03, 0x19,        /* 1831 */
    0x2f, 0x06,        /* 1832 */
    0x03, 0x19,        /* 1833 */
    0xa0, 0x2f,        /* 1834 */
    0x21, 0x30,        /* 1835 */
    0x64, 0x21,        /* 1836 */
    0x03, 0x18,        /* 1837 */
    0x5b, 0x2f,        /* 1838 */
    0x21, 0x1a,        /* 1839 */
    0x33, 0x2f,        /* 1840 */
    0xa1, 0x1e,        /* 1841 */
    0x39, 0x2f,        /* 1842 */
    0x02, 0x30,        /* 1843 */
    0x29, 0x02,        /* 1844 */
    0x03, 0x18,        /* 1845 */
    0xa0, 0x2f,        /* 1846 */
    0xa9, 0x0a,        /* 1847 */
    0xa1, 0x2f,        /* 1848 */
    0xa9, 0x08,        /* 1849 */
    0x03, 0x19,        /* 1850 */
    0xa0, 0x1f,        /* 1851 */
    0x47, 0x2f,        /* 1852 */
    0x1c, 0x30,        /* 1853 */
    0xac, 0x00,        /* 1854 */
    0xa9, 0x0a,        /* 1855 */
    0x00, 0x30,        /* 1856 */
    0xa1, 0x18,        /* 1857 */
    0x01, 0x30,        /* 1858 */
    0xb4, 0x00,        /* 1859 */
    0x64, 0x30,        /* 1860 */
    0x43, 0x21,        /* 1861 */
    0xa1, 0x2f,        /* 1862 */
    0xf0, 0x30,        /* 1863 */
    0x5c, 0x2f,        /* 1864 */
    0x21, 0x1a,        /* 1865 */
    0xa0, 0x2f,        /* 1866 */
    0xa1, 0x1e,        /* 1867 */
    0xa1, 0x2f,        /* 1868 */
    0xa0, 0x2f,        /* 1869 */
    0xa9, 0x21,        /* 1870 */
    0x07, 0x30,        /* 1871 */
    0x64, 0x21,        /* 1872 */
    0x03, 0x1c,        /* 1873 */
    0x57, 0x2f,        /* 1874 */
    0x6e, 0x30,        /* 1875 */
    0x50, 0x21,        /* 1876 */
    0xa3, 0x00,        /* 1877 */
    0xe2, 0x21,        /* 1878 */
    0x21, 0x30,        /* 1879 */
    0x64, 0x21,        /* 1880 */
    0x03, 0x1c,        /* 1881 */
    0xa1, 0x2f,        /* 1882 */
    0x20, 0x30,        /* 1883 */
    0xac, 0x00,        /* 1884 */
    0xa1, 0x2f,        /* 1885 */
    0xb0, 0x01,        /* 1886 */
    0xb1, 0x01,        /* 1887 */
    0x01, 0x30,        /* 1888 */
    0x49, 0x21,        /* 1889 */
    0x02, 0x30,        /* 1890 */
    0x31, 0x02,        /* 1891 */
    0x00, 0x30,        /* 1892 */
    0x03, 0x19,        /* 1893 */
    0x30, 0x02,        /* 1894 */
    0x03, 0x18,        /* 1895 */
    0x86, 0x2f,        /* 1896 */
    0x01, 0x30,        /* 1897 */
    0x64, 0x21,        /* 1898 */
    0x03, 0x1c,        /* 1899 */
    0x7c, 0x2f,        /* 1900 */
    0x01, 0x30,        /* 1901 */
    0x49, 0x21,        /* 1902 */
    0x21, 0x30,        /* 1903 */
    0x64, 0x21,        /* 1904 */
    0xa0, 0x11,        /* 1905 */
    0x03, 0x18,        /* 1906 */
    0xa0, 0x15,        /* 1907 */
    0xa0, 0x1d,        /* 1908 */
    0x79, 0x2f,        /* 1909 */
    0xb0, 0x01,        /* 1910 */
    0xb1, 0x01,        /* 1911 */
    0x7c, 0x2f,        /* 1912 */
    0xb0, 0x0a,        /* 1913 */
    0x03, 0x19,        /* 1914 */
    0xb1, 0x0a,        /* 1915 */
    0x07, 0x30,        /* 1916 */
    0x64, 0x21,        /* 1917 */
    0x03, 0x1c,        /* 1918 */
    0x84, 0x2f,        /* 1919 */
    0x6e, 0x30,        /* 1920 */
    0x50, 0x21,        /* 1921 */
    0xa3, 0x00,        /* 1922 */
    0xe2, 0x21,        /* 1923 */
    0xa9, 0x21,        /* 1924 */
    0x62, 0x2f,        /* 1925 */
    0x41, 0x30,        /* 1926 */
    0x50, 0x21,        /* 1927 */
    0xad, 0x00,        /* 1928 */
    0xad, 0x1f,        /* 1929 */
    0x9d, 0x2f,        /* 1930 */
    0x21, 0x16,        /* 1931 */
    0x20, 0x16,        /* 1932 */
    0x63, 0x30,        /* 1933 */
    0x64, 0x21,        /* 1934 */
    0x20, 0x13,        /* 1935 */
    0x03, 0x18,        /* 1936 */
    0x20, 0x17,        /* 1937 */
    0xa0, 0x16,        /* 1938 */
    0xa1, 0x15,        /* 1939 */
    0x62, 0x30,        /* 1940 */
    0x50, 0x21,        /* 1941 */
    0xa7, 0x00,        /* 1942 */
    0x64, 0x30,        /* 1943 */
    0x64, 0x21,        /* 1944 */
    0x21, 0x13,        /* 1945 */
    0x03, 0x18,        /* 1946 */
    0x21, 0x17,        /* 1947 */
    0xa0, 0x2f,        /* 1948 */
    0xad, 0x1e,        /* 1949 */
    0xa1, 0x2f,        /* 1950 */
    0xa1, 0x16,        /* 1951 */
    0xac, 0x01,        /* 1952 */
    0x2c, 0x08,        /* 1953 */
    0xb4, 0x00,        /* 1954 */
    0x30, 0x30,        /* 1955 */
    0x43, 0x21,        /* 1956 */
    0x2c, 0x08,        /* 1957 */
    0x03, 0x19,        /* 1958 */
    0x02, 0x2b,        /* 1959 */
    0x01, 0x3a,        /* 1960 */
    0x03, 0x19,        /* 1961 */
    0x58, 0x2b,        /* 1962 */
    0x03, 0x3a,        /* 1963 */
    0x03, 0x19,        /* 1964 */
    0x8a, 0x2b,        /* 1965 */
    0x01, 0x3a,        /* 1966 */
    0x03, 0x19,        /* 1967 */
    0x9b, 0x2b,        /* 1968 */
    0x07, 0x3a,        /* 1969 */
    0x03, 0x19,        /* 1970 */
    0xa3, 0x2b,        /* 1971 */
    0x01, 0x3a,        /* 1972 */
    0x03, 0x19,        /* 1973 */
    0xbd, 0x2b,        /* 1974 */
    0x03, 0x3a,        /* 1975 */
    0x03, 0x19,        /* 1976 */
    0xc9, 0x2b,        /* 1977 */
    0x01, 0x3a,        /* 1978 */
    0x03, 0x19,        /* 1979 */
    0xf9, 0x2b,        /* 1980 */
    0x0f, 0x3a,        /* 1981 */
    0x03, 0x19,        /* 1982 */
    0x07, 0x2c,        /* 1983 */
    0x01, 0x3a,        /* 1984 */
    0x03, 0x19,        /* 1985 */
    0x1d, 0x2c,        /* 1986 */
    0x03, 0x3a,        /* 1987 */
    0x03, 0x19,        /* 1988 */
    0x2b, 0x2c,        /* 1989 */
    0x01, 0x3a,        /* 1990 */
    0x03, 0x19,        /* 1991 */
    0x43, 0x2c,        /* 1992 */
    0x07, 0x3a,        /* 1993 */
    0x03, 0x19,        /* 1994 */
    0x51, 0x2c,        /* 1995 */
    0x01, 0x3a,        /* 1996 */
    0x03, 0x19,        /* 1997 */
    0x66, 0x2c,        /* 1998 */
    0x03, 0x3a,        /* 1999 */
    0x03, 0x19,        /* 2000 */
    0x87, 0x2c,        /* 2001 */
    0x1e, 0x3a,        /* 2002 */
    0x03, 0x19,        /* 2003 */
    0x98, 0x2c,        /* 2004 */
    0x01, 0x3a,        /* 2005 */
    0x03, 0x19,        /* 2006 */
    0xa0, 0x2c,        /* 2007 */
    0x03, 0x3a,        /* 2008 */
    0x03, 0x19,        /* 2009 */
    0xaa, 0x2c,        /* 2010 */
    0x01, 0x3a,        /* 2011 */
    0x03, 0x19,        /* 2012 */
    0xbb, 0x2c,        /* 2013 */
    0x07, 0x3a,        /* 2014 */
    0x03, 0x19,        /* 2015 */
    0xeb, 0x2c,        /* 2016 */
    0x01, 0x3a,        /* 2017 */
    0x03, 0x19,        /* 2018 */
    0xf9, 0x2c,        /* 2019 */
    0x03, 0x3a,        /* 2020 */
    0x03, 0x19,        /* 2021 */
    0x05, 0x2d,        /* 2022 */
    0x01, 0x3a,        /* 2023 */
    0x03, 0x19,        /* 2024 */
    0x12, 0x2d,        /* 2025 */
    0x0d, 0x3a,        /* 2026 */
    0x03, 0x19,        /* 2027 */
    0x5f, 0x2d,        /* 2028 */
    0x06, 0x3a,        /* 2029 */
    0x03, 0x19,        /* 2030 */
    0x84, 0x2e,        /* 2031 */
    0x01, 0x3a,        /* 2032 */
    0x03, 0x19,        /* 2033 */
    0xe4, 0x2e,        /* 2034 */
    0x3d, 0x3a,        /* 2035 */
    0x03, 0x19,        /* 2036 */
    0x5e, 0x2f,        /* 2037 */
    0xd0, 0x3a,        /* 2038 */
    0x03, 0x19,        /* 2039 */
    0x4e, 0x2f,        /* 2040 */
    0x0e, 0x3a,        /* 2041 */
    0x03, 0x19,        /* 2042 */
    0x49, 0x2f,        /* 2043 */
    0x01, 0x3a,        /* 2044 */
    0x03, 0x19,        /* 2045 */
    0x49, 0x2f,        /* 2046 */
    0xa1, 0x2f,        /* 2047 */
};
#elif 1
/*============================================================
**    Thu Jun 19 15:08:19 2008
**    converted from file :    maver_fpga_v19.rom
==========================================================*/
const U8 m88dd2k_fm[] =
{
    0x83, 0x01,        /*    0 */
    0x00, 0x30,        /*    1 */
    0x8a, 0x00,        /*    2 */
    0x04, 0x28,        /*    3 */
    0x23, 0x30,        /*    4 */
    0x84, 0x00,        /*    5 */
    0x7d, 0x30,        /*    6 */
    0x13, 0x20,        /*    7 */
    0x20, 0x30,        /*    8 */
    0x84, 0x00,        /*    9 */
    0x23, 0x30,        /*   10 */
    0x13, 0x20,        /*   11 */
    0x83, 0x01,        /*   12 */
    0x0a, 0x12,        /*   13 */
    0x8a, 0x11,        /*   14 */
    0xa3, 0x2a,        /*   15 */
    0x04, 0x06,        /*   16 */
    0x80, 0x01,        /*   17 */
    0x84, 0x0a,        /*   18 */
    0x04, 0x06,        /*   19 */
    0x03, 0x1d,        /*   20 */
    0x10, 0x28,        /*   21 */
    0x00, 0x34,        /*   22 */
    0x00, 0x00,        /*   23 */
    0x00, 0x00,        /*   24 */
    0x00, 0x00,        /*   25 */
    0x00, 0x00,        /*   26 */
    0x00, 0x00,        /*   27 */
    0x00, 0x00,        /*   28 */
    0x00, 0x00,        /*   29 */
    0x00, 0x00,        /*   30 */
    0x00, 0x00,        /*   31 */
    0x00, 0x00,        /*   32 */
    0x00, 0x00,        /*   33 */
    0x00, 0x00,        /*   34 */
    0x00, 0x00,        /*   35 */
    0x00, 0x00,        /*   36 */
    0x00, 0x00,        /*   37 */
    0x00, 0x00,        /*   38 */
    0x00, 0x00,        /*   39 */
    0x00, 0x00,        /*   40 */
    0x00, 0x00,        /*   41 */
    0x00, 0x00,        /*   42 */
    0x00, 0x00,        /*   43 */
    0x00, 0x00,        /*   44 */
    0x00, 0x00,        /*   45 */
    0x00, 0x00,        /*   46 */
    0x00, 0x00,        /*   47 */
    0x00, 0x00,        /*   48 */
    0x00, 0x00,        /*   49 */
    0x00, 0x00,        /*   50 */
    0x00, 0x00,        /*   51 */
    0x00, 0x00,        /*   52 */
    0x00, 0x00,        /*   53 */
    0x00, 0x00,        /*   54 */
    0x00, 0x00,        /*   55 */
    0x00, 0x00,        /*   56 */
    0x00, 0x00,        /*   57 */
    0x00, 0x00,        /*   58 */
    0x00, 0x00,        /*   59 */
    0x00, 0x00,        /*   60 */
    0x00, 0x00,        /*   61 */
    0x00, 0x00,        /*   62 */
    0x00, 0x00,        /*   63 */
    0x00, 0x00,        /*   64 */
    0x00, 0x00,        /*   65 */
    0x00, 0x00,        /*   66 */
    0x00, 0x00,        /*   67 */
    0x00, 0x00,        /*   68 */
    0x00, 0x00,        /*   69 */
    0x00, 0x00,        /*   70 */
    0x00, 0x00,        /*   71 */
    0x00, 0x00,        /*   72 */
    0x00, 0x00,        /*   73 */
    0x00, 0x00,        /*   74 */
    0x00, 0x00,        /*   75 */
    0x00, 0x00,        /*   76 */
    0x00, 0x00,        /*   77 */
    0x00, 0x00,        /*   78 */
    0x00, 0x00,        /*   79 */
    0x00, 0x00,        /*   80 */
    0x00, 0x00,        /*   81 */
    0x00, 0x00,        /*   82 */
    0x00, 0x00,        /*   83 */
    0x00, 0x00,        /*   84 */
    0x00, 0x00,        /*   85 */
    0x00, 0x00,        /*   86 */
    0x00, 0x00,        /*   87 */
    0x00, 0x00,        /*   88 */
    0x00, 0x00,        /*   89 */
    0x00, 0x00,        /*   90 */
    0x00, 0x00,        /*   91 */
    0x00, 0x00,        /*   92 */
    0x00, 0x00,        /*   93 */
    0x00, 0x00,        /*   94 */
    0x00, 0x00,        /*   95 */
    0x00, 0x00,        /*   96 */
    0x00, 0x00,        /*   97 */
    0x00, 0x00,        /*   98 */
    0x00, 0x00,        /*   99 */
    0x00, 0x00,        /*  100 */
    0x00, 0x00,        /*  101 */
    0x00, 0x00,        /*  102 */
    0x00, 0x00,        /*  103 */
    0x00, 0x00,        /*  104 */
    0x00, 0x00,        /*  105 */
    0x00, 0x00,        /*  106 */
    0x00, 0x00,        /*  107 */
    0x00, 0x00,        /*  108 */
    0x00, 0x00,        /*  109 */
    0x00, 0x00,        /*  110 */
    0x00, 0x00,        /*  111 */
    0x00, 0x00,        /*  112 */
    0x00, 0x00,        /*  113 */
    0x00, 0x00,        /*  114 */
    0x00, 0x00,        /*  115 */
    0x00, 0x00,        /*  116 */
    0x00, 0x00,        /*  117 */
    0x00, 0x00,        /*  118 */
    0x00, 0x00,        /*  119 */
    0x00, 0x00,        /*  120 */
    0x00, 0x00,        /*  121 */
    0x00, 0x00,        /*  122 */
    0x00, 0x00,        /*  123 */
    0x00, 0x00,        /*  124 */
    0x00, 0x00,        /*  125 */
    0x00, 0x00,        /*  126 */
    0x00, 0x00,        /*  127 */
    0x00, 0x00,        /*  128 */
    0x00, 0x00,        /*  129 */
    0x00, 0x00,        /*  130 */
    0x00, 0x00,        /*  131 */
    0x00, 0x00,        /*  132 */
    0x00, 0x00,        /*  133 */
    0x00, 0x00,        /*  134 */
    0x00, 0x00,        /*  135 */
    0x00, 0x00,        /*  136 */
    0x00, 0x00,        /*  137 */
    0x00, 0x00,        /*  138 */
    0x00, 0x00,        /*  139 */
    0x00, 0x00,        /*  140 */
    0x00, 0x00,        /*  141 */
    0x00, 0x00,        /*  142 */
    0x00, 0x00,        /*  143 */
    0x00, 0x00,        /*  144 */
    0x00, 0x00,        /*  145 */
    0x00, 0x00,        /*  146 */
    0x00, 0x00,        /*  147 */
    0x00, 0x00,        /*  148 */
    0x00, 0x00,        /*  149 */
    0x00, 0x00,        /*  150 */
    0x00, 0x00,        /*  151 */
    0x00, 0x00,        /*  152 */
    0x00, 0x00,        /*  153 */
    0x00, 0x00,        /*  154 */
    0x00, 0x00,        /*  155 */
    0x00, 0x00,        /*  156 */
    0x00, 0x00,        /*  157 */
    0x00, 0x00,        /*  158 */
    0x00, 0x00,        /*  159 */
    0x00, 0x00,        /*  160 */
    0x00, 0x00,        /*  161 */
    0x00, 0x00,        /*  162 */
    0x00, 0x00,        /*  163 */
    0x00, 0x00,        /*  164 */
    0x00, 0x00,        /*  165 */
    0x00, 0x00,        /*  166 */
    0x00, 0x00,        /*  167 */
    0x00, 0x00,        /*  168 */
    0x00, 0x00,        /*  169 */
    0x00, 0x00,        /*  170 */
    0x00, 0x00,        /*  171 */
    0x00, 0x00,        /*  172 */
    0x00, 0x00,        /*  173 */
    0x00, 0x00,        /*  174 */
    0x00, 0x00,        /*  175 */
    0x00, 0x00,        /*  176 */
    0x00, 0x00,        /*  177 */
    0x00, 0x00,        /*  178 */
    0x00, 0x00,        /*  179 */
    0x00, 0x00,        /*  180 */
    0x00, 0x00,        /*  181 */
    0x00, 0x00,        /*  182 */
    0x00, 0x00,        /*  183 */
    0x00, 0x00,        /*  184 */
    0x00, 0x00,        /*  185 */
    0x00, 0x00,        /*  186 */
    0x00, 0x00,        /*  187 */
    0x00, 0x00,        /*  188 */
    0x00, 0x00,        /*  189 */
    0x00, 0x00,        /*  190 */
    0x00, 0x00,        /*  191 */
    0x00, 0x00,        /*  192 */
    0x00, 0x00,        /*  193 */
    0x00, 0x00,        /*  194 */
    0x00, 0x00,        /*  195 */
    0x00, 0x00,        /*  196 */
    0x00, 0x00,        /*  197 */
    0x00, 0x00,        /*  198 */
    0x00, 0x00,        /*  199 */
    0x00, 0x00,        /*  200 */
    0x00, 0x00,        /*  201 */
    0x00, 0x00,        /*  202 */
    0x00, 0x00,        /*  203 */
    0x00, 0x00,        /*  204 */
    0x00, 0x00,        /*  205 */
    0x00, 0x00,        /*  206 */
    0x00, 0x00,        /*  207 */
    0x00, 0x00,        /*  208 */
    0x00, 0x00,        /*  209 */
    0x00, 0x00,        /*  210 */
    0x00, 0x00,        /*  211 */
    0x00, 0x00,        /*  212 */
    0x00, 0x00,        /*  213 */
    0x00, 0x00,        /*  214 */
    0x00, 0x00,        /*  215 */
    0x00, 0x00,        /*  216 */
    0x00, 0x00,        /*  217 */
    0x00, 0x00,        /*  218 */
    0x00, 0x00,        /*  219 */
    0x00, 0x00,        /*  220 */
    0x00, 0x00,        /*  221 */
    0x00, 0x00,        /*  222 */
    0x00, 0x00,        /*  223 */
    0x00, 0x00,        /*  224 */
    0x00, 0x00,        /*  225 */
    0x00, 0x00,        /*  226 */
    0x00, 0x00,        /*  227 */
    0x00, 0x00,        /*  228 */
    0x00, 0x00,        /*  229 */
    0x00, 0x00,        /*  230 */
    0x00, 0x00,        /*  231 */
    0x00, 0x00,        /*  232 */
    0x00, 0x00,        /*  233 */
    0x00, 0x00,        /*  234 */
    0x00, 0x00,        /*  235 */
    0x00, 0x00,        /*  236 */
    0x00, 0x00,        /*  237 */
    0x00, 0x00,        /*  238 */
    0x00, 0x00,        /*  239 */
    0x00, 0x00,        /*  240 */
    0x00, 0x00,        /*  241 */
    0x00, 0x00,        /*  242 */
    0x00, 0x00,        /*  243 */
    0x00, 0x00,        /*  244 */
    0x00, 0x00,        /*  245 */
    0x00, 0x00,        /*  246 */
    0x00, 0x00,        /*  247 */
    0x00, 0x00,        /*  248 */
    0x00, 0x00,        /*  249 */
    0x00, 0x00,        /*  250 */
    0x00, 0x00,        /*  251 */
    0x00, 0x00,        /*  252 */
    0x00, 0x00,        /*  253 */
    0x00, 0x00,        /*  254 */
    0x00, 0x00,        /*  255 */
    0x00, 0x00,        /*  256 */
    0x00, 0x00,        /*  257 */
    0x00, 0x00,        /*  258 */
    0x00, 0x00,        /*  259 */
    0x00, 0x00,        /*  260 */
    0x00, 0x00,        /*  261 */
    0x00, 0x00,        /*  262 */
    0x00, 0x00,        /*  263 */
    0x00, 0x00,        /*  264 */
    0x00, 0x00,        /*  265 */
    0x00, 0x00,        /*  266 */
    0x00, 0x00,        /*  267 */
    0x00, 0x00,        /*  268 */
    0x00, 0x00,        /*  269 */
    0x00, 0x00,        /*  270 */
    0x00, 0x00,        /*  271 */
    0x00, 0x00,        /*  272 */
    0x00, 0x00,        /*  273 */
    0x00, 0x00,        /*  274 */
    0x00, 0x00,        /*  275 */
    0x00, 0x00,        /*  276 */
    0x00, 0x00,        /*  277 */
    0x00, 0x00,        /*  278 */
    0x00, 0x00,        /*  279 */
    0x00, 0x00,        /*  280 */
    0x00, 0x00,        /*  281 */
    0x00, 0x00,        /*  282 */
    0x00, 0x00,        /*  283 */
    0x00, 0x00,        /*  284 */
    0x00, 0x00,        /*  285 */
    0x00, 0x00,        /*  286 */
    0x00, 0x00,        /*  287 */
    0x00, 0x00,        /*  288 */
    0x00, 0x00,        /*  289 */
    0x00, 0x00,        /*  290 */
    0x00, 0x00,        /*  291 */
    0x00, 0x00,        /*  292 */
    0x00, 0x00,        /*  293 */
    0x00, 0x00,        /*  294 */
    0x00, 0x00,        /*  295 */
    0x00, 0x00,        /*  296 */
    0x00, 0x00,        /*  297 */
    0x00, 0x00,        /*  298 */
    0x00, 0x00,        /*  299 */
    0x00, 0x00,        /*  300 */
    0x00, 0x00,        /*  301 */
    0x00, 0x00,        /*  302 */
    0x00, 0x00,        /*  303 */
    0x00, 0x00,        /*  304 */
    0x00, 0x00,        /*  305 */
    0x00, 0x00,        /*  306 */
    0x00, 0x00,        /*  307 */
    0x00, 0x00,        /*  308 */
    0x00, 0x00,        /*  309 */
    0x00, 0x00,        /*  310 */
    0x00, 0x00,        /*  311 */
    0x00, 0x00,        /*  312 */
    0x00, 0x00,        /*  313 */
    0x00, 0x00,        /*  314 */
    0x00, 0x00,        /*  315 */
    0x00, 0x00,        /*  316 */
    0x00, 0x00,        /*  317 */
    0x00, 0x00,        /*  318 */
    0x00, 0x00,        /*  319 */
    0x00, 0x00,        /*  320 */
    0x00, 0x00,        /*  321 */
    0x00, 0x00,        /*  322 */
    0x00, 0x00,        /*  323 */
    0x00, 0x00,        /*  324 */
    0x00, 0x00,        /*  325 */
    0x00, 0x00,        /*  326 */
    0x00, 0x00,        /*  327 */
    0x00, 0x00,        /*  328 */
    0x00, 0x00,        /*  329 */
    0x00, 0x00,        /*  330 */
    0x00, 0x00,        /*  331 */
    0x00, 0x00,        /*  332 */
    0x00, 0x00,        /*  333 */
    0x00, 0x00,        /*  334 */
    0x00, 0x00,        /*  335 */
    0x00, 0x00,        /*  336 */
    0x00, 0x00,        /*  337 */
    0x00, 0x00,        /*  338 */
    0x00, 0x00,        /*  339 */
    0x00, 0x00,        /*  340 */
    0x00, 0x00,        /*  341 */
    0x00, 0x00,        /*  342 */
    0x00, 0x00,        /*  343 */
    0x00, 0x00,        /*  344 */
    0x00, 0x00,        /*  345 */
    0x00, 0x00,        /*  346 */
    0x00, 0x00,        /*  347 */
    0x00, 0x00,        /*  348 */
    0x00, 0x00,        /*  349 */
    0x00, 0x00,        /*  350 */
    0x00, 0x00,        /*  351 */
    0x00, 0x00,        /*  352 */
    0x00, 0x00,        /*  353 */
    0x00, 0x00,        /*  354 */
    0x00, 0x00,        /*  355 */
    0x00, 0x00,        /*  356 */
    0x00, 0x00,        /*  357 */
    0x00, 0x00,        /*  358 */
    0x00, 0x00,        /*  359 */
    0x00, 0x00,        /*  360 */
    0x00, 0x00,        /*  361 */
    0x00, 0x00,        /*  362 */
    0x00, 0x00,        /*  363 */
    0x00, 0x00,        /*  364 */
    0x00, 0x00,        /*  365 */
    0x00, 0x00,        /*  366 */
    0x00, 0x00,        /*  367 */
    0x00, 0x00,        /*  368 */
    0x00, 0x00,        /*  369 */
    0x00, 0x00,        /*  370 */
    0x00, 0x00,        /*  371 */
    0x00, 0x00,        /*  372 */
    0x00, 0x00,        /*  373 */
    0x00, 0x00,        /*  374 */
    0x00, 0x00,        /*  375 */
    0x00, 0x00,        /*  376 */
    0x00, 0x00,        /*  377 */
    0x00, 0x00,        /*  378 */
    0x00, 0x00,        /*  379 */
    0x00, 0x00,        /*  380 */
    0x00, 0x00,        /*  381 */
    0x00, 0x00,        /*  382 */
    0x00, 0x00,        /*  383 */
    0x00, 0x00,        /*  384 */
    0x00, 0x00,        /*  385 */
    0x00, 0x00,        /*  386 */
    0x00, 0x00,        /*  387 */
    0x00, 0x00,        /*  388 */
    0x00, 0x00,        /*  389 */
    0x00, 0x00,        /*  390 */
    0x00, 0x00,        /*  391 */
    0x00, 0x00,        /*  392 */
    0x00, 0x00,        /*  393 */
    0x00, 0x00,        /*  394 */
    0x00, 0x00,        /*  395 */
    0x00, 0x00,        /*  396 */
    0x00, 0x00,        /*  397 */
    0x00, 0x00,        /*  398 */
    0x00, 0x00,        /*  399 */
    0x00, 0x00,        /*  400 */
    0x00, 0x00,        /*  401 */
    0x00, 0x00,        /*  402 */
    0x00, 0x00,        /*  403 */
    0x00, 0x00,        /*  404 */
    0x00, 0x00,        /*  405 */
    0x00, 0x00,        /*  406 */
    0x00, 0x00,        /*  407 */
    0x00, 0x00,        /*  408 */
    0x00, 0x00,        /*  409 */
    0x00, 0x00,        /*  410 */
    0x00, 0x00,        /*  411 */
    0x00, 0x00,        /*  412 */
    0x00, 0x00,        /*  413 */
    0x00, 0x00,        /*  414 */
    0x00, 0x00,        /*  415 */
    0x00, 0x00,        /*  416 */
    0x00, 0x00,        /*  417 */
    0x00, 0x00,        /*  418 */
    0x00, 0x00,        /*  419 */
    0x00, 0x00,        /*  420 */
    0x00, 0x00,        /*  421 */
    0x00, 0x00,        /*  422 */
    0x00, 0x00,        /*  423 */
    0x00, 0x00,        /*  424 */
    0x00, 0x00,        /*  425 */
    0x00, 0x00,        /*  426 */
    0x00, 0x00,        /*  427 */
    0x00, 0x00,        /*  428 */
    0x00, 0x00,        /*  429 */
    0x00, 0x00,        /*  430 */
    0x00, 0x00,        /*  431 */
    0x00, 0x00,        /*  432 */
    0x00, 0x00,        /*  433 */
    0x00, 0x00,        /*  434 */
    0x00, 0x00,        /*  435 */
    0x00, 0x00,        /*  436 */
    0x00, 0x00,        /*  437 */
    0x00, 0x00,        /*  438 */
    0x00, 0x00,        /*  439 */
    0x00, 0x00,        /*  440 */
    0x00, 0x00,        /*  441 */
    0x00, 0x00,        /*  442 */
    0x00, 0x00,        /*  443 */
    0x00, 0x00,        /*  444 */
    0x00, 0x00,        /*  445 */
    0x00, 0x00,        /*  446 */
    0x00, 0x00,        /*  447 */
    0x00, 0x00,        /*  448 */
    0x00, 0x00,        /*  449 */
    0x00, 0x00,        /*  450 */
    0x00, 0x00,        /*  451 */
    0x00, 0x00,        /*  452 */
    0x00, 0x00,        /*  453 */
    0x00, 0x00,        /*  454 */
    0x00, 0x00,        /*  455 */
    0x00, 0x00,        /*  456 */
    0x00, 0x00,        /*  457 */
    0x00, 0x00,        /*  458 */
    0x00, 0x00,        /*  459 */
    0x00, 0x00,        /*  460 */
    0x00, 0x00,        /*  461 */
    0x00, 0x00,        /*  462 */
    0x00, 0x00,        /*  463 */
    0x00, 0x00,        /*  464 */
    0x00, 0x00,        /*  465 */
    0x00, 0x00,        /*  466 */
    0x00, 0x00,        /*  467 */
    0x00, 0x00,        /*  468 */
    0x00, 0x00,        /*  469 */
    0x00, 0x00,        /*  470 */
    0x00, 0x00,        /*  471 */
    0x00, 0x00,        /*  472 */
    0x00, 0x00,        /*  473 */
    0x00, 0x00,        /*  474 */
    0x00, 0x00,        /*  475 */
    0x00, 0x00,        /*  476 */
    0x00, 0x00,        /*  477 */
    0x00, 0x00,        /*  478 */
    0x00, 0x00,        /*  479 */
    0x00, 0x00,        /*  480 */
    0x00, 0x00,        /*  481 */
    0x00, 0x00,        /*  482 */
    0x00, 0x00,        /*  483 */
    0x00, 0x00,        /*  484 */
    0x00, 0x00,        /*  485 */
    0x00, 0x00,        /*  486 */
    0x00, 0x00,        /*  487 */
    0x00, 0x00,        /*  488 */
    0x00, 0x00,        /*  489 */
    0x00, 0x00,        /*  490 */
    0x00, 0x00,        /*  491 */
    0x00, 0x00,        /*  492 */
    0x00, 0x00,        /*  493 */
    0x00, 0x00,        /*  494 */
    0x00, 0x00,        /*  495 */
    0x00, 0x00,        /*  496 */
    0x00, 0x00,        /*  497 */
    0x00, 0x00,        /*  498 */
    0x00, 0x00,        /*  499 */
    0x00, 0x00,        /*  500 */
    0x00, 0x00,        /*  501 */
    0x00, 0x00,        /*  502 */
    0x00, 0x00,        /*  503 */
    0x00, 0x00,        /*  504 */
    0x00, 0x00,        /*  505 */
    0x00, 0x00,        /*  506 */
    0x00, 0x00,        /*  507 */
    0x00, 0x00,        /*  508 */
    0x00, 0x00,        /*  509 */
    0x00, 0x00,        /*  510 */
    0x00, 0x00,        /*  511 */
    0x00, 0x00,        /*  512 */
    0x00, 0x00,        /*  513 */
    0x00, 0x00,        /*  514 */
    0x00, 0x00,        /*  515 */
    0x00, 0x00,        /*  516 */
    0x00, 0x00,        /*  517 */
    0x00, 0x00,        /*  518 */
    0x00, 0x00,        /*  519 */
    0x00, 0x00,        /*  520 */
    0x00, 0x00,        /*  521 */
    0x00, 0x00,        /*  522 */
    0x00, 0x00,        /*  523 */
    0x00, 0x00,        /*  524 */
    0x00, 0x00,        /*  525 */
    0x00, 0x00,        /*  526 */
    0x00, 0x00,        /*  527 */
    0x00, 0x00,        /*  528 */
    0x00, 0x00,        /*  529 */
    0x00, 0x00,        /*  530 */
    0x00, 0x00,        /*  531 */
    0x00, 0x00,        /*  532 */
    0x00, 0x00,        /*  533 */
    0x00, 0x00,        /*  534 */
    0x00, 0x00,        /*  535 */
    0x00, 0x00,        /*  536 */
    0x00, 0x00,        /*  537 */
    0x00, 0x00,        /*  538 */
    0x00, 0x00,        /*  539 */
    0x00, 0x00,        /*  540 */
    0x00, 0x00,        /*  541 */
    0x00, 0x00,        /*  542 */
    0x00, 0x00,        /*  543 */
    0x00, 0x00,        /*  544 */
    0x00, 0x00,        /*  545 */
    0x00, 0x00,        /*  546 */
    0x83, 0x01,        /*  547 */
    0xfb, 0x00,        /*  548 */
    0x9c, 0x00,        /*  549 */
    0x01, 0x30,        /*  550 */
    0x9e, 0x00,        /*  551 */
    0x9e, 0x01,        /*  552 */
    0x08, 0x00,        /*  553 */
    0x83, 0x01,        /*  554 */
    0x23, 0x1e,        /*  555 */
    0x2f, 0x2a,        /*  556 */
    0xa1, 0x17,        /*  557 */
    0x30, 0x2a,        /*  558 */
    0xa1, 0x13,        /*  559 */
    0x83, 0x12,        /*  560 */
    0x03, 0x13,        /*  561 */
    0x23, 0x08,        /*  562 */
    0x0f, 0x39,        /*  563 */
    0xf9, 0x00,        /*  564 */
    0xa2, 0x18,        /*  565 */
    0x41, 0x2a,        /*  566 */
    0xa5, 0x01,        /*  567 */
    0xf9, 0x08,        /*  568 */
    0x03, 0x1d,        /*  569 */
    0x65, 0x2a,        /*  570 */
    0xa2, 0x14,        /*  571 */
    0x22, 0x14,        /*  572 */
    0xa1, 0x1b,        /*  573 */
    0x22, 0x10,        /*  574 */
    0xa4, 0x01,        /*  575 */
    0x65, 0x2a,        /*  576 */
    0x25, 0x08,        /*  577 */
    0x03, 0x3a,        /*  578 */
    0x03, 0x19,        /*  579 */
    0x47, 0x2a,        /*  580 */
    0xa2, 0x14,        /*  581 */
    0x48, 0x2a,        /*  582 */
    0xa2, 0x10,        /*  583 */
    0x24, 0x08,        /*  584 */
    0x26, 0x06,        /*  585 */
    0x03, 0x1d,        /*  586 */
    0x64, 0x2a,        /*  587 */
    0xa4, 0x01,        /*  588 */
    0xf9, 0x08,        /*  589 */
    0x03, 0x1d,        /*  590 */
    0x60, 0x2a,        /*  591 */
    0x22, 0x1c,        /*  592 */
    0x54, 0x2a,        /*  593 */
    0x01, 0x30,        /*  594 */
    0x55, 0x2a,        /*  595 */
    0x00, 0x30,        /*  596 */
    0xfd, 0x00,        /*  597 */
    0xa1, 0x1f,        /*  598 */
    0x5a, 0x2a,        /*  599 */
    0x01, 0x30,        /*  600 */
    0x5b, 0x2a,        /*  601 */
    0x00, 0x30,        /*  602 */
    0xfd, 0x06,        /*  603 */
    0x03, 0x1d,        /*  604 */
    0x60, 0x2a,        /*  605 */
    0xa5, 0x01,        /*  606 */
    0x61, 0x2a,        /*  607 */
    0xa5, 0x0a,        /*  608 */
    0x01, 0x30,        /*  609 */
    0xa2, 0x06,        /*  610 */
    0x65, 0x2a,        /*  611 */
    0xa4, 0x0a,        /*  612 */
    0x07, 0x30,        /*  613 */
    0x23, 0x22,        /*  614 */
    0x24, 0x08,        /*  615 */
    0x26, 0x06,        /*  616 */
    0x03, 0x1d,        /*  617 */
    0x6e, 0x2a,        /*  618 */
    0x02, 0x30,        /*  619 */
    0xfa, 0x00,        /*  620 */
    0x6f, 0x2a,        /*  621 */
    0xfa, 0x01,        /*  622 */
    0x22, 0x18,        /*  623 */
    0x7a, 0x14,        /*  624 */
    0x7a, 0x08,        /*  625 */
    0xfb, 0x00,        /*  626 */
    0x1b, 0x30,        /*  627 */
    0x75, 0x2a,        /*  628 */
    0x83, 0x01,        /*  629 */
    0xfc, 0x00,        /*  630 */
    0x9c, 0x00,        /*  631 */
    0x7b, 0x08,        /*  632 */
    0x9e, 0x00,        /*  633 */
    0x08, 0x00,        /*  634 */
    0x83, 0x01,        /*  635 */
    0xfb, 0x00,        /*  636 */
    0x9c, 0x00,        /*  637 */
    0x00, 0x00,        /*  638 */
    0x00, 0x00,        /*  639 */
    0x20, 0x10,        /*  640 */
    0x1d, 0x18,        /*  641 */
    0x20, 0x14,        /*  642 */
    0x03, 0x10,        /*  643 */
    0x83, 0x12,        /*  644 */
    0x03, 0x13,        /*  645 */
    0x20, 0x18,        /*  646 */
    0x03, 0x14,        /*  647 */
    0x08, 0x00,        /*  648 */
    0x83, 0x01,        /*  649 */
    0xf9, 0x00,        /*  650 */
    0xfa, 0x01,        /*  651 */
    0x96, 0x2a,        /*  652 */
    0x01, 0x30,        /*  653 */
    0x7b, 0x22,        /*  654 */
    0x03, 0x1c,        /*  655 */
    0x96, 0x2a,        /*  656 */
    0xfb, 0x01,        /*  657 */
    0xfb, 0x0a,        /*  658 */
    0x01, 0x30,        /*  659 */
    0x75, 0x22,        /*  660 */
    0xfa, 0x0a,        /*  661 */
    0x79, 0x08,        /*  662 */
    0x7a, 0x02,        /*  663 */
    0x03, 0x18,        /*  664 */
    0x08, 0x00,        /*  665 */
    0x8d, 0x2a,        /*  666 */
    0x83, 0x01,        /*  667 */
    0xf9, 0x00,        /*  668 */
    0x9c, 0x00,        /*  669 */
    0x00, 0x00,        /*  670 */
    0x00, 0x00,        /*  671 */
    0x1d, 0x08,        /*  672 */
    0xfa, 0x00,        /*  673 */
    0x08, 0x00,        /*  674 */
    0x19, 0x30,        /*  675 */
    0x83, 0x12,        /*  676 */
    0x03, 0x13,        /*  677 */
    0x86, 0x00,        /*  678 */
    0xb4, 0x01,        /*  679 */
    0xa1, 0x12,        /*  680 */
    0x41, 0x30,        /*  681 */
    0x9b, 0x22,        /*  682 */
    0xb3, 0x00,        /*  683 */
    0x21, 0x13,        /*  684 */
    0x43, 0x30,        /*  685 */
    0x9b, 0x22,        /*  686 */
    0xa7, 0x00,        /*  687 */
    0xfb, 0x00,        /*  688 */
    0x43, 0x30,        /*  689 */
    0x75, 0x22,        /*  690 */
    0x44, 0x30,        /*  691 */
    0x9b, 0x22,        /*  692 */
    0xb0, 0x00,        /*  693 */
    0xfb, 0x00,        /*  694 */
    0x44, 0x30,        /*  695 */
    0x75, 0x22,        /*  696 */
    0x3a, 0x30,        /*  697 */
    0x9b, 0x22,        /*  698 */
    0xa9, 0x00,        /*  699 */
    0x31, 0x30,        /*  700 */
    0x7b, 0x22,        /*  701 */
    0xa0, 0x11,        /*  702 */
    0x03, 0x18,        /*  703 */
    0xa0, 0x15,        /*  704 */
    0x32, 0x30,        /*  705 */
    0x7b, 0x22,        /*  706 */
    0xa0, 0x12,        /*  707 */
    0x03, 0x18,        /*  708 */
    0xa0, 0x16,        /*  709 */
    0x33, 0x30,        /*  710 */
    0x7b, 0x22,        /*  711 */
    0x20, 0x13,        /*  712 */
    0x03, 0x18,        /*  713 */
    0x20, 0x17,        /*  714 */
    0x37, 0x30,        /*  715 */
    0x7b, 0x22,        /*  716 */
    0xa0, 0x13,        /*  717 */
    0x03, 0x18,        /*  718 */
    0xa0, 0x17,        /*  719 */
    0x38, 0x30,        /*  720 */
    0x7b, 0x22,        /*  721 */
    0xa0, 0x10,        /*  722 */
    0x03, 0x18,        /*  723 */
    0xa0, 0x14,        /*  724 */
    0x34, 0x30,        /*  725 */
    0x7b, 0x22,        /*  726 */
    0x21, 0x12,        /*  727 */
    0x03, 0x18,        /*  728 */
    0x21, 0x16,        /*  729 */
    0x39, 0x30,        /*  730 */
    0x9b, 0x22,        /*  731 */
    0xac, 0x00,        /*  732 */
    0xa1, 0x2f,        /*  733 */
    0xa2, 0x10,        /*  734 */
    0xb5, 0x01,        /*  735 */
    0xb6, 0x01,        /*  736 */
    0xa5, 0x01,        /*  737 */
    0xfb, 0x01,        /*  738 */
    0x61, 0x30,        /*  739 */
    0x75, 0x22,        /*  740 */
    0xfb, 0x01,        /*  741 */
    0x0a, 0x30,        /*  742 */
    0x75, 0x22,        /*  743 */
    0xfb, 0x01,        /*  744 */
    0x0b, 0x30,        /*  745 */
    0x75, 0x22,        /*  746 */
    0x02, 0x30,        /*  747 */
    0xfb, 0x00,        /*  748 */
    0x60, 0x30,        /*  749 */
    0x75, 0x22,        /*  750 */
    0xfb, 0x01,        /*  751 */
    0x0c, 0x30,        /*  752 */
    0x75, 0x22,        /*  753 */
    0xfb, 0x01,        /*  754 */
    0x0d, 0x30,        /*  755 */
    0x75, 0x22,        /*  756 */
    0xfb, 0x01,        /*  757 */
    0x0e, 0x30,        /*  758 */
    0x75, 0x22,        /*  759 */
    0xfb, 0x01,        /*  760 */
    0x0f, 0x30,        /*  761 */
    0x75, 0x22,        /*  762 */
    0xfb, 0x01,        /*  763 */
    0x10, 0x30,        /*  764 */
    0x75, 0x22,        /*  765 */
    0xfb, 0x01,        /*  766 */
    0x12, 0x30,        /*  767 */
    0x75, 0x22,        /*  768 */
    0xfb, 0x01,        /*  769 */
    0x13, 0x30,        /*  770 */
    0x75, 0x22,        /*  771 */
    0xfb, 0x01,        /*  772 */
    0x14, 0x30,        /*  773 */
    0x75, 0x22,        /*  774 */
    0xfb, 0x01,        /*  775 */
    0x11, 0x30,        /*  776 */
    0x75, 0x22,        /*  777 */
    0xfb, 0x01,        /*  778 */
    0x63, 0x30,        /*  779 */
    0x75, 0x22,        /*  780 */
    0xfb, 0x01,        /*  781 */
    0x16, 0x30,        /*  782 */
    0x75, 0x22,        /*  783 */
    0xfb, 0x01,        /*  784 */
    0x64, 0x30,        /*  785 */
    0x75, 0x22,        /*  786 */
    0x15, 0x30,        /*  787 */
    0x23, 0x22,        /*  788 */
    0x18, 0x30,        /*  789 */
    0x23, 0x22,        /*  790 */
    0x17, 0x30,        /*  791 */
    0x23, 0x22,        /*  792 */
    0x06, 0x30,        /*  793 */
    0x23, 0x22,        /*  794 */
    0x00, 0x30,        /*  795 */
    0x23, 0x22,        /*  796 */
    0x02, 0x30,        /*  797 */
    0x23, 0x22,        /*  798 */
    0x03, 0x30,        /*  799 */
    0x23, 0x22,        /*  800 */
    0x04, 0x30,        /*  801 */
    0x23, 0x22,        /*  802 */
    0x06, 0x30,        /*  803 */
    0x23, 0x22,        /*  804 */
    0x07, 0x30,        /*  805 */
    0x23, 0x22,        /*  806 */
    0x08, 0x30,        /*  807 */
    0x23, 0x22,        /*  808 */
    0x09, 0x30,        /*  809 */
    0x23, 0x22,        /*  810 */
    0x05, 0x30,        /*  811 */
    0x23, 0x22,        /*  812 */
    0xb7, 0x01,        /*  813 */
    0xb8, 0x01,        /*  814 */
    0xa8, 0x01,        /*  815 */
    0xae, 0x01,        /*  816 */
    0xab, 0x01,        /*  817 */
    0xaa, 0x01,        /*  818 */
    0xb1, 0x01,        /*  819 */
    0xb3, 0x01,        /*  820 */
    0x33, 0x08,        /*  821 */
    0x39, 0x3e,        /*  822 */
    0x84, 0x00,        /*  823 */
    0x83, 0x13,        /*  824 */
    0x80, 0x01,        /*  825 */
    0xb3, 0x0a,        /*  826 */
    0x40, 0x30,        /*  827 */
    0x33, 0x02,        /*  828 */
    0x03, 0x1c,        /*  829 */
    0x35, 0x2b,        /*  830 */
    0xb4, 0x01,        /*  831 */
    0xb4, 0x0a,        /*  832 */
    0xa1, 0x2f,        /*  833 */
    0x20, 0x30,        /*  834 */
    0x7b, 0x22,        /*  835 */
    0x20, 0x11,        /*  836 */
    0x03, 0x18,        /*  837 */
    0x20, 0x15,        /*  838 */
    0x83, 0x12,        /*  839 */
    0x03, 0x13,        /*  840 */
    0x20, 0x1d,        /*  841 */
    0xa1, 0x2f,        /*  842 */
    0x18, 0x30,        /*  843 */
    0x23, 0x22,        /*  844 */
    0x17, 0x30,        /*  845 */
    0x23, 0x22,        /*  846 */
    0xfb, 0x01,        /*  847 */
    0x14, 0x30,        /*  848 */
    0x75, 0x22,        /*  849 */
    0xfb, 0x01,        /*  850 */
    0x11, 0x30,        /*  851 */
    0x75, 0x22,        /*  852 */
    0xfb, 0x01,        /*  853 */
    0x10, 0x30,        /*  854 */
    0x75, 0x22,        /*  855 */
    0xa0, 0x1d,        /*  856 */
    0x5e, 0x2b,        /*  857 */
    0x29, 0x08,        /*  858 */
    0xfb, 0x00,        /*  859 */
    0x61, 0x30,        /*  860 */
    0x75, 0x22,        /*  861 */
    0x35, 0x30,        /*  862 */
    0x7b, 0x22,        /*  863 */
    0x02, 0x30,        /*  864 */
    0x03, 0x1c,        /*  865 */
    0x6e, 0x2b,        /*  866 */
    0x89, 0x22,        /*  867 */
    0x03, 0x30,        /*  868 */
    0xfb, 0x00,        /*  869 */
    0x60, 0x30,        /*  870 */
    0x75, 0x22,        /*  871 */
    0xfb, 0x01,        /*  872 */
    0xfb, 0x0a,        /*  873 */
    0x0e, 0x30,        /*  874 */
    0x75, 0x22,        /*  875 */
    0x02, 0x30,        /*  876 */
    0x41, 0x2f,        /*  877 */
    0xfb, 0x00,        /*  878 */
    0x60, 0x30,        /*  879 */
    0x75, 0x22,        /*  880 */
    0x0a, 0x30,        /*  881 */
    0x23, 0x22,        /*  882 */
    0xa0, 0x19,        /*  883 */
    0xa5, 0x2b,        /*  884 */
    0xa7, 0x2b,        /*  885 */
    0x00, 0x30,        /*  886 */
    0x7b, 0x22,        /*  887 */
    0x03, 0x1c,        /*  888 */
    0xa1, 0x2f,        /*  889 */
    0xfb, 0x01,        /*  890 */
    0x0e, 0x30,        /*  891 */
    0x75, 0x22,        /*  892 */
    0x02, 0x30,        /*  893 */
    0xfb, 0x00,        /*  894 */
    0x60, 0x30,        /*  895 */
    0x75, 0x22,        /*  896 */
    0x01, 0x30,        /*  897 */
    0x23, 0x22,        /*  898 */
    0x00, 0x30,        /*  899 */
    0x23, 0x22,        /*  900 */
    0x03, 0x30,        /*  901 */
    0x41, 0x2f,        /*  902 */
    0x01, 0x30,        /*  903 */
    0x7b, 0x22,        /*  904 */
    0x03, 0x1c,        /*  905 */
    0xa1, 0x2f,        /*  906 */
    0x01, 0x30,        /*  907 */
    0x23, 0x22,        /*  908 */
    0x04, 0x30,        /*  909 */
    0x41, 0x2f,        /*  910 */
    0x01, 0x30,        /*  911 */
    0x7b, 0x22,        /*  912 */
    0x03, 0x1c,        /*  913 */
    0xa1, 0x2f,        /*  914 */
    0xa0, 0x1d,        /*  915 */
    0x99, 0x2b,        /*  916 */
    0x29, 0x08,        /*  917 */
    0xfb, 0x00,        /*  918 */
    0x61, 0x30,        /*  919 */
    0x75, 0x22,        /*  920 */
    0x02, 0x30,        /*  921 */
    0xfb, 0x00,        /*  922 */
    0x60, 0x30,        /*  923 */
    0x75, 0x22,        /*  924 */
    0x0a, 0x30,        /*  925 */
    0x23, 0x22,        /*  926 */
    0xa0, 0x1d,        /*  927 */
    0xa7, 0x2b,        /*  928 */
    0x29, 0x08,        /*  929 */
    0x02, 0x3a,        /*  930 */
    0x03, 0x19,        /*  931 */
    0x2b, 0x2c,        /*  932 */
    0x05, 0x30,        /*  933 */
    0x41, 0x2f,        /*  934 */
    0x07, 0x30,        /*  935 */
    0x41, 0x2f,        /*  936 */
    0x02, 0x30,        /*  937 */
    0x7b, 0x22,        /*  938 */
    0x03, 0x1c,        /*  939 */
    0xa1, 0x2f,        /*  940 */
    0xfb, 0x01,        /*  941 */
    0xfb, 0x0a,        /*  942 */
    0x60, 0x30,        /*  943 */
    0x75, 0x22,        /*  944 */
    0x0b, 0x30,        /*  945 */
    0x23, 0x22,        /*  946 */
    0x02, 0x30,        /*  947 */
    0x3a, 0x2c,        /*  948 */
    0x03, 0x30,        /*  949 */
    0x7b, 0x22,        /*  950 */
    0x03, 0x1c,        /*  951 */
    0xa1, 0x2f,        /*  952 */
    0x03, 0x30,        /*  953 */
    0x23, 0x22,        /*  954 */
    0x02, 0x30,        /*  955 */
    0xfb, 0x00,        /*  956 */
    0x60, 0x30,        /*  957 */
    0x75, 0x22,        /*  958 */
    0x69, 0x30,        /*  959 */
    0x7b, 0x22,        /*  960 */
    0x03, 0x1c,        /*  961 */
    0x2d, 0x2c,        /*  962 */
    0x61, 0x30,        /*  963 */
    0x9b, 0x22,        /*  964 */
    0xb3, 0x00,        /*  965 */
    0xa0, 0x19,        /*  966 */
    0xd1, 0x2b,        /*  967 */
    0xb3, 0x08,        /*  968 */
    0x03, 0x1d,        /*  969 */
    0xce, 0x2b,        /*  970 */
    0xfb, 0x01,        /*  971 */
    0xfb, 0x0a,        /*  972 */
    0xcf, 0x2b,        /*  973 */
    0xfb, 0x01,        /*  974 */
    0x61, 0x30,        /*  975 */
    0x75, 0x22,        /*  976 */
    0x0a, 0x30,        /*  977 */
    0x23, 0x22,        /*  978 */
    0xa0, 0x19,        /*  979 */
    0xd7, 0x2b,        /*  980 */
    0x05, 0x30,        /*  981 */
    0xdd, 0x2b,        /*  982 */
    0xb3, 0x08,        /*  983 */
    0x03, 0x1d,        /*  984 */
    0xdc, 0x2b,        /*  985 */
    0x09, 0x30,        /*  986 */
    0xdd, 0x2b,        /*  987 */
    0x07, 0x30,        /*  988 */
    0xb4, 0x00,        /*  989 */
    0xb1, 0x0a,        /*  990 */
    0x0f, 0x30,        /*  991 */
    0x31, 0x02,        /*  992 */
    0x03, 0x1c,        /*  993 */
    0xa1, 0x2f,        /*  994 */
    0xff, 0x30,        /*  995 */
    0x41, 0x2f,        /*  996 */
    0x02, 0x30,        /*  997 */
    0x7b, 0x22,        /*  998 */
    0x03, 0x1c,        /*  999 */
    0xa1, 0x2f,        /* 1000 */
    0x02, 0x30,        /* 1001 */
    0x23, 0x22,        /* 1002 */
    0xfb, 0x01,        /* 1003 */
    0xfb, 0x0a,        /* 1004 */
    0x60, 0x30,        /* 1005 */
    0x75, 0x22,        /* 1006 */
    0x0b, 0x30,        /* 1007 */
    0x23, 0x22,        /* 1008 */
    0x08, 0x30,        /* 1009 */
    0x41, 0x2f,        /* 1010 */
    0x03, 0x30,        /* 1011 */
    0x7b, 0x22,        /* 1012 */
    0x03, 0x1c,        /* 1013 */
    0xa1, 0x2f,        /* 1014 */
    0x03, 0x30,        /* 1015 */
    0x23, 0x22,        /* 1016 */
    0x02, 0x30,        /* 1017 */
    0xfb, 0x00,        /* 1018 */
    0x60, 0x30,        /* 1019 */
    0x75, 0x22,        /* 1020 */
    0x69, 0x30,        /* 1021 */
    0x7b, 0x22,        /* 1022 */
    0x03, 0x1c,        /* 1023 */
    0x2d, 0x2c,        /* 1024 */
    0xfb, 0x01,        /* 1025 */
    0xfb, 0x0a,        /* 1026 */
    0x61, 0x30,        /* 1027 */
    0x75, 0x22,        /* 1028 */
    0x0a, 0x30,        /* 1029 */
    0x23, 0x22,        /* 1030 */
    0x09, 0x30,        /* 1031 */
    0x41, 0x2f,        /* 1032 */
    0x02, 0x30,        /* 1033 */
    0x7b, 0x22,        /* 1034 */
    0x03, 0x1c,        /* 1035 */
    0xa1, 0x2f,        /* 1036 */
    0x02, 0x30,        /* 1037 */
    0x23, 0x22,        /* 1038 */
    0xfb, 0x01,        /* 1039 */
    0xfb, 0x0a,        /* 1040 */
    0x60, 0x30,        /* 1041 */
    0x75, 0x22,        /* 1042 */
    0x0b, 0x30,        /* 1043 */
    0x23, 0x22,        /* 1044 */
    0x0a, 0x30,        /* 1045 */
    0x41, 0x2f,        /* 1046 */
    0x03, 0x30,        /* 1047 */
    0x7b, 0x22,        /* 1048 */
    0x03, 0x1c,        /* 1049 */
    0xa1, 0x2f,        /* 1050 */
    0x03, 0x30,        /* 1051 */
    0x23, 0x22,        /* 1052 */
    0x02, 0x30,        /* 1053 */
    0xfb, 0x00,        /* 1054 */
    0x60, 0x30,        /* 1055 */
    0x75, 0x22,        /* 1056 */
    0x69, 0x30,        /* 1057 */
    0x7b, 0x22,        /* 1058 */
    0x03, 0x1c,        /* 1059 */
    0x2d, 0x2c,        /* 1060 */
    0x02, 0x30,        /* 1061 */
    0xfb, 0x00,        /* 1062 */
    0x61, 0x30,        /* 1063 */
    0x75, 0x22,        /* 1064 */
    0x0a, 0x30,        /* 1065 */
    0x23, 0x22,        /* 1066 */
    0x0b, 0x30,        /* 1067 */
    0x41, 0x2f,        /* 1068 */
    0x0c, 0x30,        /* 1069 */
    0x41, 0x2f,        /* 1070 */
    0x02, 0x30,        /* 1071 */
    0x7b, 0x22,        /* 1072 */
    0x03, 0x1c,        /* 1073 */
    0xa1, 0x2f,        /* 1074 */
    0x02, 0x30,        /* 1075 */
    0x23, 0x22,        /* 1076 */
    0xfb, 0x01,        /* 1077 */
    0xfb, 0x0a,        /* 1078 */
    0x60, 0x30,        /* 1079 */
    0x75, 0x22,        /* 1080 */
    0x0b, 0x30,        /* 1081 */
    0x23, 0x22,        /* 1082 */
    0x06, 0x30,        /* 1083 */
    0x41, 0x2f,        /* 1084 */
    0x02, 0x30,        /* 1085 */
    0xfb, 0x00,        /* 1086 */
    0x60, 0x30,        /* 1087 */
    0x75, 0x22,        /* 1088 */
    0xfb, 0x01,        /* 1089 */
    0xfb, 0x0a,        /* 1090 */
    0x0c, 0x30,        /* 1091 */
    0x75, 0x22,        /* 1092 */
    0x23, 0x30,        /* 1093 */
    0x7b, 0x22,        /* 1094 */
    0x03, 0x1c,        /* 1095 */
    0x45, 0x2c,        /* 1096 */
    0xfb, 0x01,        /* 1097 */
    0x0c, 0x30,        /* 1098 */
    0x75, 0x22,        /* 1099 */
    0xfb, 0x01,        /* 1100 */
    0x60, 0x30,        /* 1101 */
    0x75, 0x22,        /* 1102 */
    0x0d, 0x30,        /* 1103 */
    0x41, 0x2f,        /* 1104 */
    0x04, 0x30,        /* 1105 */
    0x7b, 0x22,        /* 1106 */
    0x03, 0x1c,        /* 1107 */
    0xa1, 0x2f,        /* 1108 */
    0x04, 0x30,        /* 1109 */
    0x23, 0x22,        /* 1110 */
    0x6a, 0x30,        /* 1111 */
    0x7b, 0x22,        /* 1112 */
    0x03, 0x1c,        /* 1113 */
    0x68, 0x2c,        /* 1114 */
    0x02, 0x30,        /* 1115 */
    0xfb, 0x00,        /* 1116 */
    0x60, 0x30,        /* 1117 */
    0x75, 0x22,        /* 1118 */
    0xb4, 0x01,        /* 1119 */
    0xb4, 0x0a,        /* 1120 */
    0xa8, 0x0a,        /* 1121 */
    0x04, 0x30,        /* 1122 */
    0x28, 0x02,        /* 1123 */
    0x03, 0x1c,        /* 1124 */
    0xa1, 0x2f,        /* 1125 */
    0xfe, 0x30,        /* 1126 */
    0x41, 0x2f,        /* 1127 */
    0x03, 0x30,        /* 1128 */
    0xfb, 0x00,        /* 1129 */
    0x60, 0x30,        /* 1130 */
    0x75, 0x22,        /* 1131 */
    0xfb, 0x01,        /* 1132 */
    0xfb, 0x0a,        /* 1133 */
    0x0d, 0x30,        /* 1134 */
    0x75, 0x22,        /* 1135 */
    0x0e, 0x30,        /* 1136 */
    0x41, 0x2f,        /* 1137 */
    0x05, 0x30,        /* 1138 */
    0x7b, 0x22,        /* 1139 */
    0x03, 0x1c,        /* 1140 */
    0xa1, 0x2f,        /* 1141 */
    0xfb, 0x01,        /* 1142 */
    0x0d, 0x30,        /* 1143 */
    0x75, 0x22,        /* 1144 */
    0x03, 0x30,        /* 1145 */
    0xfb, 0x00,        /* 1146 */
    0x60, 0x30,        /* 1147 */
    0x75, 0x22,        /* 1148 */
    0x05, 0x30,        /* 1149 */
    0x23, 0x22,        /* 1150 */
    0x01, 0x30,        /* 1151 */
    0x23, 0x22,        /* 1152 */
    0x10, 0x30,        /* 1153 */
    0x41, 0x2f,        /* 1154 */
    0x01, 0x30,        /* 1155 */
    0x7b, 0x22,        /* 1156 */
    0x03, 0x1c,        /* 1157 */
    0xa1, 0x2f,        /* 1158 */
    0x01, 0x30,        /* 1159 */
    0x23, 0x22,        /* 1160 */
    0x11, 0x30,        /* 1161 */
    0x41, 0x2f,        /* 1162 */
    0x01, 0x30,        /* 1163 */
    0x7b, 0x22,        /* 1164 */
    0x03, 0x1c,        /* 1165 */
    0xa1, 0x2f,        /* 1166 */
    0xfb, 0x01,        /* 1167 */
    0xfb, 0x0a,        /* 1168 */
    0x0f, 0x30,        /* 1169 */
    0x75, 0x22,        /* 1170 */
    0x12, 0x30,        /* 1171 */
    0x41, 0x2f,        /* 1172 */
    0x06, 0x30,        /* 1173 */
    0x7b, 0x22,        /* 1174 */
    0x03, 0x1c,        /* 1175 */
    0xa1, 0x2f,        /* 1176 */
    0xfb, 0x01,        /* 1177 */
    0x0f, 0x30,        /* 1178 */
    0x75, 0x22,        /* 1179 */
    0x06, 0x30,        /* 1180 */
    0x23, 0x22,        /* 1181 */
    0xfb, 0x01,        /* 1182 */
    0xfb, 0x0a,        /* 1183 */
    0x10, 0x30,        /* 1184 */
    0x75, 0x22,        /* 1185 */
    0x01, 0x30,        /* 1186 */
    0x23, 0x22,        /* 1187 */
    0x13, 0x30,        /* 1188 */
    0x41, 0x2f,        /* 1189 */
    0x24, 0x30,        /* 1190 */
    0x23, 0x22,        /* 1191 */
    0xb3, 0x01,        /* 1192 */
    0x33, 0x08,        /* 1193 */
    0x03, 0x3a,        /* 1194 */
    0x03, 0x19,        /* 1195 */
    0xd4, 0x2c,        /* 1196 */
    0xb3, 0x08,        /* 1197 */
    0x03, 0x1d,        /* 1198 */
    0xb2, 0x2c,        /* 1199 */
    0x3e, 0x30,        /* 1200 */
    0xbb, 0x2c,        /* 1201 */
    0x33, 0x0b,        /* 1202 */
    0xb6, 0x2c,        /* 1203 */
    0x3f, 0x30,        /* 1204 */
    0xbb, 0x2c,        /* 1205 */
    0x33, 0x08,        /* 1206 */
    0x02, 0x3a,        /* 1207 */
    0x03, 0x1d,        /* 1208 */
    0xbd, 0x2c,        /* 1209 */
    0x40, 0x30,        /* 1210 */
    0x9b, 0x22,        /* 1211 */
    0xb2, 0x00,        /* 1212 */
    0xb1, 0x01,        /* 1213 */
    0xf0, 0x30,        /* 1214 */
    0xb2, 0x05,        /* 1215 */
    0x03, 0x10,        /* 1216 */
    0xb2, 0x0c,        /* 1217 */
    0x32, 0x08,        /* 1218 */
    0x31, 0x02,        /* 1219 */
    0x03, 0x18,        /* 1220 */
    0xce, 0x2c,        /* 1221 */
    0x24, 0x30,        /* 1222 */
    0x7b, 0x22,        /* 1223 */
    0x03, 0x1c,        /* 1224 */
    0xc2, 0x2c,        /* 1225 */
    0x24, 0x30,        /* 1226 */
    0x23, 0x22,        /* 1227 */
    0xb1, 0x0a,        /* 1228 */
    0xc2, 0x2c,        /* 1229 */
    0x1a, 0x30,        /* 1230 */
    0x23, 0x22,        /* 1231 */
    0xb3, 0x0a,        /* 1232 */
    0x33, 0x08,        /* 1233 */
    0x87, 0x00,        /* 1234 */
    0xa9, 0x2c,        /* 1235 */
    0x16, 0x30,        /* 1236 */
    0x41, 0x2f,        /* 1237 */
    0x01, 0x30,        /* 1238 */
    0x7b, 0x22,        /* 1239 */
    0x03, 0x1c,        /* 1240 */
    0xa1, 0x2f,        /* 1241 */
    0x01, 0x30,        /* 1242 */
    0x23, 0x22,        /* 1243 */
    0xfb, 0x01,        /* 1244 */
    0x14, 0x30,        /* 1245 */
    0x75, 0x22,        /* 1246 */
    0xfb, 0x01,        /* 1247 */
    0x12, 0x30,        /* 1248 */
    0x75, 0x22,        /* 1249 */
    0x15, 0x30,        /* 1250 */
    0x41, 0x2f,        /* 1251 */
    0x01, 0x30,        /* 1252 */
    0x7b, 0x22,        /* 1253 */
    0x03, 0x1c,        /* 1254 */
    0xa1, 0x2f,        /* 1255 */
    0x01, 0x30,        /* 1256 */
    0x23, 0x22,        /* 1257 */
    0xfb, 0x01,        /* 1258 */
    0xfb, 0x0a,        /* 1259 */
    0x14, 0x30,        /* 1260 */
    0x75, 0x22,        /* 1261 */
    0x17, 0x30,        /* 1262 */
    0x41, 0x2f,        /* 1263 */
    0xfb, 0x01,        /* 1264 */
    0xfb, 0x0a,        /* 1265 */
    0x11, 0x30,        /* 1266 */
    0x75, 0x22,        /* 1267 */
    0x22, 0x30,        /* 1268 */
    0x7b, 0x22,        /* 1269 */
    0x03, 0x1c,        /* 1270 */
    0xa1, 0x2f,        /* 1271 */
    0xfb, 0x01,        /* 1272 */
    0x11, 0x30,        /* 1273 */
    0x75, 0x22,        /* 1274 */
    0x14, 0x30,        /* 1275 */
    0x41, 0x2f,        /* 1276 */
    0x25, 0x30,        /* 1277 */
    0x23, 0x22,        /* 1278 */
    0xb3, 0x01,        /* 1279 */
    0x33, 0x08,        /* 1280 */
    0x03, 0x3a,        /* 1281 */
    0x03, 0x19,        /* 1282 */
    0x2f, 0x2d,        /* 1283 */
    0xb3, 0x08,        /* 1284 */
    0x03, 0x1d,        /* 1285 */
    0x09, 0x2d,        /* 1286 */
    0x3e, 0x30,        /* 1287 */
    0x12, 0x2d,        /* 1288 */
    0x33, 0x0b,        /* 1289 */
    0x0d, 0x2d,        /* 1290 */
    0x3f, 0x30,        /* 1291 */
    0x12, 0x2d,        /* 1292 */
    0x33, 0x08,        /* 1293 */
    0x02, 0x3a,        /* 1294 */
    0x03, 0x1d,        /* 1295 */
    0x14, 0x2d,        /* 1296 */
    0x40, 0x30,        /* 1297 */
    0x9b, 0x22,        /* 1298 */
    0xb2, 0x00,        /* 1299 */
    0xb1, 0x01,        /* 1300 */
    0x0f, 0x30,        /* 1301 */
    0xb2, 0x05,        /* 1302 */
    0x03, 0x10,        /* 1303 */
    0xb2, 0x0d,        /* 1304 */
    0x03, 0x10,        /* 1305 */
    0xb2, 0x0d,        /* 1306 */
    0x03, 0x10,        /* 1307 */
    0xb2, 0x0d,        /* 1308 */
    0x32, 0x08,        /* 1309 */
    0x31, 0x02,        /* 1310 */
    0x03, 0x18,        /* 1311 */
    0x29, 0x2d,        /* 1312 */
    0x25, 0x30,        /* 1313 */
    0x7b, 0x22,        /* 1314 */
    0x03, 0x1c,        /* 1315 */
    0x1d, 0x2d,        /* 1316 */
    0x25, 0x30,        /* 1317 */
    0x23, 0x22,        /* 1318 */
    0xb1, 0x0a,        /* 1319 */
    0x1d, 0x2d,        /* 1320 */
    0x19, 0x30,        /* 1321 */
    0x23, 0x22,        /* 1322 */
    0xb3, 0x0a,        /* 1323 */
    0x33, 0x08,        /* 1324 */
    0x87, 0x00,        /* 1325 */
    0x00, 0x2d,        /* 1326 */
    0x61, 0x30,        /* 1327 */
    0x9b, 0x22,        /* 1328 */
    0xad, 0x00,        /* 1329 */
    0x03, 0x30,        /* 1330 */
    0xad, 0x05,        /* 1331 */
    0x2d, 0x08,        /* 1332 */
    0x02, 0x3a,        /* 1333 */
    0x03, 0x19,        /* 1334 */
    0x3c, 0x2d,        /* 1335 */
    0x2d, 0x08,        /* 1336 */
    0x03, 0x3a,        /* 1337 */
    0x03, 0x1d,        /* 1338 */
    0x3e, 0x2d,        /* 1339 */
    0xd7, 0x30,        /* 1340 */
    0x43, 0x2d,        /* 1341 */
    0x2d, 0x0b,        /* 1342 */
    0x42, 0x2d,        /* 1343 */
    0xc7, 0x30,        /* 1344 */
    0x43, 0x2d,        /* 1345 */
    0xe0, 0x30,        /* 1346 */
    0xa6, 0x00,        /* 1347 */
    0xfb, 0x01,        /* 1348 */
    0xfb, 0x0a,        /* 1349 */
    0x12, 0x30,        /* 1350 */
    0x75, 0x22,        /* 1351 */
    0x1a, 0x30,        /* 1352 */
    0x41, 0x2f,        /* 1353 */
    0xfb, 0x01,        /* 1354 */
    0xfb, 0x0a,        /* 1355 */
    0x13, 0x30,        /* 1356 */
    0x75, 0x22,        /* 1357 */
    0x3b, 0x30,        /* 1358 */
    0x9b, 0x22,        /* 1359 */
    0xb3, 0x00,        /* 1360 */
    0x03, 0x10,        /* 1361 */
    0xb3, 0x0d,        /* 1362 */
    0x03, 0x10,        /* 1363 */
    0xb3, 0x0d,        /* 1364 */
    0x03, 0x10,        /* 1365 */
    0xb3, 0x0d,        /* 1366 */
    0xb1, 0x01,        /* 1367 */
    0xa0, 0x1a,        /* 1368 */
    0x21, 0x1e,        /* 1369 */
    0x83, 0x2d,        /* 1370 */
    0x00, 0x30,        /* 1371 */
    0xa0, 0x1b,        /* 1372 */
    0x01, 0x30,        /* 1373 */
    0xfb, 0x00,        /* 1374 */
    0x63, 0x30,        /* 1375 */
    0x75, 0x22,        /* 1376 */
    0x2c, 0x08,        /* 1377 */
    0xfb, 0x00,        /* 1378 */
    0x6e, 0x30,        /* 1379 */
    0x75, 0x22,        /* 1380 */
    0x2c, 0x08,        /* 1381 */
    0xaf, 0x00,        /* 1382 */
    0x21, 0x10,        /* 1383 */
    0xa0, 0x1b,        /* 1384 */
    0x21, 0x14,        /* 1385 */
    0x83, 0x12,        /* 1386 */
    0x03, 0x13,        /* 1387 */
    0x20, 0x1f,        /* 1388 */
    0x7c, 0x2d,        /* 1389 */
    0x00, 0x30,        /* 1390 */
    0xa0, 0x18,        /* 1391 */
    0x01, 0x30,        /* 1392 */
    0xfb, 0x00,        /* 1393 */
    0x64, 0x30,        /* 1394 */
    0x75, 0x22,        /* 1395 */
    0xa1, 0x10,        /* 1396 */
    0xa0, 0x18,        /* 1397 */
    0xa1, 0x14,        /* 1398 */
    0x17, 0x30,        /* 1399 */
    0x23, 0x22,        /* 1400 */
    0x1d, 0x30,        /* 1401 */
    0xb4, 0x00,        /* 1402 */
    0x1b, 0x2e,        /* 1403 */
    0xa0, 0x1f,        /* 1404 */
    0x1b, 0x2e,        /* 1405 */
    0x1c, 0x30,        /* 1406 */
    0xb4, 0x00,        /* 1407 */
    0x17, 0x30,        /* 1408 */
    0x23, 0x22,        /* 1409 */
    0x1b, 0x2e,        /* 1410 */
    0x87, 0x01,        /* 1411 */
    0xc1, 0x2d,        /* 1412 */
    0x08, 0x30,        /* 1413 */
    0x7b, 0x22,        /* 1414 */
    0x03, 0x1c,        /* 1415 */
    0xc1, 0x2d,        /* 1416 */
    0x08, 0x30,        /* 1417 */
    0x23, 0x22,        /* 1418 */
    0x6b, 0x30,        /* 1419 */
    0x7b, 0x22,        /* 1420 */
    0x21, 0x10,        /* 1421 */
    0x03, 0x18,        /* 1422 */
    0x21, 0x14,        /* 1423 */
    0x6c, 0x30,        /* 1424 */
    0x7b, 0x22,        /* 1425 */
    0xa1, 0x10,        /* 1426 */
    0x03, 0x18,        /* 1427 */
    0xa1, 0x14,        /* 1428 */
    0x6e, 0x30,        /* 1429 */
    0x9b, 0x22,        /* 1430 */
    0xa3, 0x00,        /* 1431 */
    0x21, 0x1c,        /* 1432 */
    0x9c, 0x2d,        /* 1433 */
    0xab, 0x0a,        /* 1434 */
    0x9d, 0x2d,        /* 1435 */
    0xaa, 0x0a,        /* 1436 */
    0xa1, 0x1c,        /* 1437 */
    0xa1, 0x2d,        /* 1438 */
    0xa3, 0x16,        /* 1439 */
    0xa2, 0x2d,        /* 1440 */
    0xa3, 0x12,        /* 1441 */
    0x23, 0x08,        /* 1442 */
    0x39, 0x3e,        /* 1443 */
    0x84, 0x00,        /* 1444 */
    0x83, 0x13,        /* 1445 */
    0x00, 0x0a,        /* 1446 */
    0x03, 0x19,        /* 1447 */
    0xad, 0x2d,        /* 1448 */
    0x23, 0x08,        /* 1449 */
    0x39, 0x3e,        /* 1450 */
    0x84, 0x00,        /* 1451 */
    0x80, 0x0a,        /* 1452 */
    0x23, 0x08,        /* 1453 */
    0x39, 0x3e,        /* 1454 */
    0x84, 0x00,        /* 1455 */
    0x83, 0x13,        /* 1456 */
    0x00, 0x08,        /* 1457 */
    0x14, 0x3a,        /* 1458 */
    0x03, 0x19,        /* 1459 */
    0xc8, 0x2d,        /* 1460 */
    0x23, 0x08,        /* 1461 */
    0x39, 0x3e,        /* 1462 */
    0x84, 0x00,        /* 1463 */
    0x0a, 0x30,        /* 1464 */
    0x00, 0x02,        /* 1465 */
    0x03, 0x1c,        /* 1466 */
    0xc0, 0x2d,        /* 1467 */
    0x0f, 0x30,        /* 1468 */
    0x31, 0x02,        /* 1469 */
    0x03, 0x1c,        /* 1470 */
    0xc8, 0x2d,        /* 1471 */
    0xb1, 0x0a,        /* 1472 */
    0xb1, 0x08,        /* 1473 */
    0x03, 0x19,        /* 1474 */
    0x85, 0x2d,        /* 1475 */
    0x31, 0x08,        /* 1476 */
    0x33, 0x02,        /* 1477 */
    0x03, 0x18,        /* 1478 */
    0x85, 0x2d,        /* 1479 */
    0x39, 0x08,        /* 1480 */
    0xb2, 0x00,        /* 1481 */
    0xa3, 0x01,        /* 1482 */
    0xb3, 0x01,        /* 1483 */
    0xb3, 0x0a,        /* 1484 */
    0x33, 0x08,        /* 1485 */
    0x39, 0x3e,        /* 1486 */
    0x84, 0x00,        /* 1487 */
    0x83, 0x13,        /* 1488 */
    0x00, 0x08,        /* 1489 */
    0x32, 0x02,        /* 1490 */
    0x03, 0x18,        /* 1491 */
    0xdc, 0x2d,        /* 1492 */
    0x33, 0x08,        /* 1493 */
    0x39, 0x3e,        /* 1494 */
    0x84, 0x00,        /* 1495 */
    0x00, 0x08,        /* 1496 */
    0xb2, 0x00,        /* 1497 */
    0x33, 0x08,        /* 1498 */
    0xa3, 0x00,        /* 1499 */
    0xb3, 0x0a,        /* 1500 */
    0x40, 0x30,        /* 1501 */
    0x33, 0x02,        /* 1502 */
    0x03, 0x1c,        /* 1503 */
    0xcd, 0x2d,        /* 1504 */
    0xa0, 0x1a,        /* 1505 */
    0xe9, 0x2d,        /* 1506 */
    0x2b, 0x08,        /* 1507 */
    0x2a, 0x02,        /* 1508 */
    0x03, 0x1c,        /* 1509 */
    0xec, 0x2d,        /* 1510 */
    0x21, 0x10,        /* 1511 */
    0xed, 0x2d,        /* 1512 */
    0x21, 0x10,        /* 1513 */
    0xa0, 0x1f,        /* 1514 */
    0xed, 0x2d,        /* 1515 */
    0x21, 0x14,        /* 1516 */
    0x83, 0x12,        /* 1517 */
    0x03, 0x13,        /* 1518 */
    0x20, 0x1b,        /* 1519 */
    0xf5, 0x2d,        /* 1520 */
    0xa3, 0x1a,        /* 1521 */
    0xf8, 0x2d,        /* 1522 */
    0xa1, 0x10,        /* 1523 */
    0xf9, 0x2d,        /* 1524 */
    0xa1, 0x10,        /* 1525 */
    0xa0, 0x1c,        /* 1526 */
    0xf9, 0x2d,        /* 1527 */
    0xa1, 0x14,        /* 1528 */
    0x2c, 0x08,        /* 1529 */
    0x21, 0x1a,        /* 1530 */
    0xa3, 0x00,        /* 1531 */
    0x23, 0x08,        /* 1532 */
    0xaf, 0x00,        /* 1533 */
    0x00, 0x30,        /* 1534 */
    0x21, 0x18,        /* 1535 */
    0x01, 0x30,        /* 1536 */
    0xfb, 0x00,        /* 1537 */
    0x63, 0x30,        /* 1538 */
    0x75, 0x22,        /* 1539 */
    0x00, 0x30,        /* 1540 */
    0xa1, 0x18,        /* 1541 */
    0x01, 0x30,        /* 1542 */
    0xfb, 0x00,        /* 1543 */
    0x64, 0x30,        /* 1544 */
    0x75, 0x22,        /* 1545 */
    0x2f, 0x08,        /* 1546 */
    0xfb, 0x00,        /* 1547 */
    0x62, 0x30,        /* 1548 */
    0x75, 0x22,        /* 1549 */
    0x17, 0x30,        /* 1550 */
    0x23, 0x22,        /* 1551 */
    0x21, 0x1c,        /* 1552 */
    0x14, 0x2e,        /* 1553 */
    0x20, 0x1f,        /* 1554 */
    0x16, 0x2e,        /* 1555 */
    0x1d, 0x30,        /* 1556 */
    0x17, 0x2e,        /* 1557 */
    0x1c, 0x30,        /* 1558 */
    0xb4, 0x00,        /* 1559 */
    0xfb, 0x01,        /* 1560 */
    0x13, 0x30,        /* 1561 */
    0x75, 0x22,        /* 1562 */
    0x41, 0x30,        /* 1563 */
    0x9b, 0x22,        /* 1564 */
    0xb3, 0x00,        /* 1565 */
    0x42, 0x30,        /* 1566 */
    0x9b, 0x22,        /* 1567 */
    0x03, 0x3a,        /* 1568 */
    0x03, 0x1d,        /* 1569 */
    0x2c, 0x2e,        /* 1570 */
    0xfb, 0x01,        /* 1571 */
    0x44, 0x30,        /* 1572 */
    0x75, 0x22,        /* 1573 */
    0xfb, 0x01,        /* 1574 */
    0xfb, 0x0a,        /* 1575 */
    0x43, 0x30,        /* 1576 */
    0x75, 0x22,        /* 1577 */
    0xb0, 0x01,        /* 1578 */
    0xa1, 0x2f,        /* 1579 */
    0x33, 0x1f,        /* 1580 */
    0xa1, 0x2f,        /* 1581 */
    0x21, 0x18,        /* 1582 */
    0x32, 0x2e,        /* 1583 */
    0x02, 0x30,        /* 1584 */
    0x33, 0x2e,        /* 1585 */
    0x03, 0x30,        /* 1586 */
    0x83, 0x12,        /* 1587 */
    0x03, 0x13,        /* 1588 */
    0xb0, 0x00,        /* 1589 */
    0x2f, 0x08,        /* 1590 */
    0x0f, 0x39,        /* 1591 */
    0xb2, 0x00,        /* 1592 */
    0x21, 0x1c,        /* 1593 */
    0x42, 0x2e,        /* 1594 */
    0x32, 0x08,        /* 1595 */
    0x0c, 0x3a,        /* 1596 */
    0x03, 0x1d,        /* 1597 */
    0x42, 0x2e,        /* 1598 */
    0xfb, 0x01,        /* 1599 */
    0xfb, 0x0a,        /* 1600 */
    0x44, 0x2e,        /* 1601 */
    0x03, 0x30,        /* 1602 */
    0xfb, 0x00,        /* 1603 */
    0x43, 0x30,        /* 1604 */
    0x75, 0x22,        /* 1605 */
    0x30, 0x08,        /* 1606 */
    0xfb, 0x00,        /* 1607 */
    0x44, 0x30,        /* 1608 */
    0x19, 0x2f,        /* 1609 */
    0xfb, 0x01,        /* 1610 */
    0x13, 0x30,        /* 1611 */
    0x75, 0x22,        /* 1612 */
    0x62, 0x30,        /* 1613 */
    0x9b, 0x22,        /* 1614 */
    0xaf, 0x00,        /* 1615 */
    0x64, 0x30,        /* 1616 */
    0x7b, 0x22,        /* 1617 */
    0x21, 0x11,        /* 1618 */
    0x03, 0x18,        /* 1619 */
    0x21, 0x15,        /* 1620 */
    0x36, 0x30,        /* 1621 */
    0x7b, 0x22,        /* 1622 */
    0xa1, 0x11,        /* 1623 */
    0x03, 0x18,        /* 1624 */
    0xa1, 0x15,        /* 1625 */
    0x83, 0x12,        /* 1626 */
    0x03, 0x13,        /* 1627 */
    0x2f, 0x08,        /* 1628 */
    0x0f, 0x39,        /* 1629 */
    0xb3, 0x00,        /* 1630 */
    0x07, 0x3a,        /* 1631 */
    0x03, 0x19,        /* 1632 */
    0xa1, 0x1d,        /* 1633 */
    0x84, 0x2e,        /* 1634 */
    0xfb, 0x01,        /* 1635 */
    0xfb, 0x0a,        /* 1636 */
    0x16, 0x30,        /* 1637 */
    0x75, 0x22,        /* 1638 */
    0x09, 0x30,        /* 1639 */
    0x7b, 0x22,        /* 1640 */
    0x03, 0x18,        /* 1641 */
    0x76, 0x2e,        /* 1642 */
    0x07, 0x30,        /* 1643 */
    0x7b, 0x22,        /* 1644 */
    0x03, 0x1c,        /* 1645 */
    0x67, 0x2e,        /* 1646 */
    0x6e, 0x30,        /* 1647 */
    0x9b, 0x22,        /* 1648 */
    0xa3, 0x00,        /* 1649 */
    0x2a, 0x22,        /* 1650 */
    0x0a, 0x12,        /* 1651 */
    0x8a, 0x11,        /* 1652 */
    0x67, 0x2e,        /* 1653 */
    0xfb, 0x01,        /* 1654 */
    0x16, 0x30,        /* 1655 */
    0x75, 0x22,        /* 1656 */
    0x09, 0x30,        /* 1657 */
    0x23, 0x22,        /* 1658 */
    0x20, 0x16,        /* 1659 */
    0x21, 0x19,        /* 1660 */
    0x20, 0x12,        /* 1661 */
    0x6d, 0x30,        /* 1662 */
    0x7b, 0x22,        /* 1663 */
    0x03, 0x1c,        /* 1664 */
    0xb3, 0x2e,        /* 1665 */
    0x00, 0x30,        /* 1666 */
    0xae, 0x2e,        /* 1667 */
    0xb7, 0x01,        /* 1668 */
    0xb8, 0x01,        /* 1669 */
    0x01, 0x30,        /* 1670 */
    0x23, 0x22,        /* 1671 */
    0x9c, 0x2e,        /* 1672 */
    0x07, 0x30,        /* 1673 */
    0x7b, 0x22,        /* 1674 */
    0x03, 0x1c,        /* 1675 */
    0x93, 0x2e,        /* 1676 */
    0x6e, 0x30,        /* 1677 */
    0x9b, 0x22,        /* 1678 */
    0xa3, 0x00,        /* 1679 */
    0x2a, 0x22,        /* 1680 */
    0x0a, 0x12,        /* 1681 */
    0x8a, 0x11,        /* 1682 */
    0x01, 0x30,        /* 1683 */
    0x7b, 0x22,        /* 1684 */
    0x03, 0x1c,        /* 1685 */
    0x89, 0x2e,        /* 1686 */
    0x01, 0x30,        /* 1687 */
    0x23, 0x22,        /* 1688 */
    0xb7, 0x0a,        /* 1689 */
    0x03, 0x19,        /* 1690 */
    0xb8, 0x0a,        /* 1691 */
    0x05, 0x30,        /* 1692 */
    0x38, 0x02,        /* 1693 */
    0x00, 0x30,        /* 1694 */
    0x03, 0x19,        /* 1695 */
    0x37, 0x02,        /* 1696 */
    0x03, 0x1c,        /* 1697 */
    0x93, 0x2e,        /* 1698 */
    0x21, 0x30,        /* 1699 */
    0x7b, 0x22,        /* 1700 */
    0x03, 0x18,        /* 1701 */
    0x40, 0x2f,        /* 1702 */
    0x20, 0x16,        /* 1703 */
    0x21, 0x1d,        /* 1704 */
    0xab, 0x2e,        /* 1705 */
    0x20, 0x12,        /* 1706 */
    0x00, 0x30,        /* 1707 */
    0x83, 0x12,        /* 1708 */
    0x03, 0x13,        /* 1709 */
    0x20, 0x1a,        /* 1710 */
    0x01, 0x30,        /* 1711 */
    0xfb, 0x00,        /* 1712 */
    0x64, 0x30,        /* 1713 */
    0x75, 0x22,        /* 1714 */
    0x1d, 0x30,        /* 1715 */
    0x41, 0x2f,        /* 1716 */
    0xfb, 0x01,        /* 1717 */
    0x13, 0x30,        /* 1718 */
    0x75, 0x22,        /* 1719 */
    0xb7, 0x01,        /* 1720 */
    0xb8, 0x01,        /* 1721 */
    0xb5, 0x01,        /* 1722 */
    0xb6, 0x01,        /* 1723 */
    0x01, 0x30,        /* 1724 */
    0x23, 0x22,        /* 1725 */
    0x38, 0x08,        /* 1726 */
    0x05, 0x3a,        /* 1727 */
    0x37, 0x04,        /* 1728 */
    0x03, 0x19,        /* 1729 */
    0xf9, 0x2e,        /* 1730 */
    0x01, 0x30,        /* 1731 */
    0x7b, 0x22,        /* 1732 */
    0x03, 0x1c,        /* 1733 */
    0xce, 0x2e,        /* 1734 */
    0x01, 0x30,        /* 1735 */
    0x23, 0x22,        /* 1736 */
    0xb7, 0x0a,        /* 1737 */
    0x03, 0x19,        /* 1738 */
    0xb8, 0x0a,        /* 1739 */
    0xb5, 0x01,        /* 1740 */
    0xb6, 0x01,        /* 1741 */
    0x07, 0x30,        /* 1742 */
    0x7b, 0x22,        /* 1743 */
    0x03, 0x1c,        /* 1744 */
    0xd8, 0x2e,        /* 1745 */
    0x6e, 0x30,        /* 1746 */
    0x9b, 0x22,        /* 1747 */
    0xa3, 0x00,        /* 1748 */
    0x2a, 0x22,        /* 1749 */
    0x0a, 0x12,        /* 1750 */
    0x8a, 0x11,        /* 1751 */
    0xb5, 0x0a,        /* 1752 */
    0x03, 0x19,        /* 1753 */
    0xb6, 0x0a,        /* 1754 */
    0x35, 0x0a,        /* 1755 */
    0x3f, 0x30,        /* 1756 */
    0x03, 0x19,        /* 1757 */
    0x36, 0x06,        /* 1758 */
    0x03, 0x1d,        /* 1759 */
    0xe3, 0x2e,        /* 1760 */
    0xb4, 0x01,        /* 1761 */
    0xf9, 0x2e,        /* 1762 */
    0x42, 0x30,        /* 1763 */
    0x9b, 0x22,        /* 1764 */
    0x03, 0x3a,        /* 1765 */
    0x03, 0x1d,        /* 1766 */
    0xf0, 0x2e,        /* 1767 */
    0xfb, 0x01,        /* 1768 */
    0x44, 0x30,        /* 1769 */
    0x75, 0x22,        /* 1770 */
    0xfb, 0x01,        /* 1771 */
    0xfb, 0x0a,        /* 1772 */
    0x43, 0x30,        /* 1773 */
    0x75, 0x22,        /* 1774 */
    0xb0, 0x01,        /* 1775 */
    0x21, 0x30,        /* 1776 */
    0x7b, 0x22,        /* 1777 */
    0x03, 0x18,        /* 1778 */
    0xf9, 0x2e,        /* 1779 */
    0x38, 0x08,        /* 1780 */
    0xb3, 0x00,        /* 1781 */
    0x05, 0x3a,        /* 1782 */
    0x03, 0x1d,        /* 1783 */
    0xbe, 0x2e,        /* 1784 */
    0x35, 0x0a,        /* 1785 */
    0x3f, 0x30,        /* 1786 */
    0x03, 0x19,        /* 1787 */
    0x36, 0x06,        /* 1788 */
    0x03, 0x19,        /* 1789 */
    0xa0, 0x2f,        /* 1790 */
    0x21, 0x30,        /* 1791 */
    0x7b, 0x22,        /* 1792 */
    0x03, 0x18,        /* 1793 */
    0x40, 0x2f,        /* 1794 */
    0xa1, 0x1a,        /* 1795 */
    0x07, 0x2f,        /* 1796 */
    0x21, 0x1f,        /* 1797 */
    0x0d, 0x2f,        /* 1798 */
    0x02, 0x30,        /* 1799 */
    0x2e, 0x02,        /* 1800 */
    0x03, 0x18,        /* 1801 */
    0xa0, 0x2f,        /* 1802 */
    0xae, 0x0a,        /* 1803 */
    0xa1, 0x2f,        /* 1804 */
    0xae, 0x08,        /* 1805 */
    0x03, 0x19,        /* 1806 */
    0x21, 0x1c,        /* 1807 */
    0x1b, 0x2f,        /* 1808 */
    0x1c, 0x30,        /* 1809 */
    0xb4, 0x00,        /* 1810 */
    0xae, 0x0a,        /* 1811 */
    0x00, 0x30,        /* 1812 */
    0x21, 0x19,        /* 1813 */
    0x01, 0x30,        /* 1814 */
    0xfb, 0x00,        /* 1815 */
    0x64, 0x30,        /* 1816 */
    0x75, 0x22,        /* 1817 */
    0xa1, 0x2f,        /* 1818 */
    0xf0, 0x30,        /* 1819 */
    0x41, 0x2f,        /* 1820 */
    0xa1, 0x1a,        /* 1821 */
    0xa0, 0x2f,        /* 1822 */
    0x21, 0x1f,        /* 1823 */
    0xa1, 0x2f,        /* 1824 */
    0xa0, 0x2f,        /* 1825 */
    0x41, 0x30,        /* 1826 */
    0x9b, 0x22,        /* 1827 */
    0xb3, 0x00,        /* 1828 */
    0x42, 0x30,        /* 1829 */
    0x9b, 0x22,        /* 1830 */
    0x03, 0x3a,        /* 1831 */
    0x03, 0x1d,        /* 1832 */
    0x32, 0x2f,        /* 1833 */
    0xfb, 0x01,        /* 1834 */
    0x44, 0x30,        /* 1835 */
    0x75, 0x22,        /* 1836 */
    0xfb, 0x01,        /* 1837 */
    0xfb, 0x0a,        /* 1838 */
    0x43, 0x30,        /* 1839 */
    0x75, 0x22,        /* 1840 */
    0xb0, 0x01,        /* 1841 */
    0x07, 0x30,        /* 1842 */
    0x7b, 0x22,        /* 1843 */
    0x03, 0x1c,        /* 1844 */
    0x3c, 0x2f,        /* 1845 */
    0x6e, 0x30,        /* 1846 */
    0x9b, 0x22,        /* 1847 */
    0xa3, 0x00,        /* 1848 */
    0x2a, 0x22,        /* 1849 */
    0x0a, 0x12,        /* 1850 */
    0x8a, 0x11,        /* 1851 */
    0x21, 0x30,        /* 1852 */
    0x7b, 0x22,        /* 1853 */
    0x03, 0x1c,        /* 1854 */
    0xa1, 0x2f,        /* 1855 */
    0x20, 0x30,        /* 1856 */
    0xb4, 0x00,        /* 1857 */
    0xa1, 0x2f,        /* 1858 */
    0xb7, 0x01,        /* 1859 */
    0xb8, 0x01,        /* 1860 */
    0x01, 0x30,        /* 1861 */
    0x23, 0x22,        /* 1862 */
    0x7c, 0x2f,        /* 1863 */
    0x07, 0x30,        /* 1864 */
    0x7b, 0x22,        /* 1865 */
    0x20, 0x12,        /* 1866 */
    0x03, 0x18,        /* 1867 */
    0x20, 0x16,        /* 1868 */
    0x83, 0x12,        /* 1869 */
    0x03, 0x13,        /* 1870 */
    0x20, 0x1e,        /* 1871 */
    0x57, 0x2f,        /* 1872 */
    0x6e, 0x30,        /* 1873 */
    0x9b, 0x22,        /* 1874 */
    0xa3, 0x00,        /* 1875 */
    0x2a, 0x22,        /* 1876 */
    0x0a, 0x12,        /* 1877 */
    0x8a, 0x11,        /* 1878 */
    0x01, 0x30,        /* 1879 */
    0x7b, 0x22,        /* 1880 */
    0x03, 0x1c,        /* 1881 */
    0x48, 0x2f,        /* 1882 */
    0x01, 0x30,        /* 1883 */
    0x23, 0x22,        /* 1884 */
    0x21, 0x30,        /* 1885 */
    0x7b, 0x22,        /* 1886 */
    0x20, 0x12,        /* 1887 */
    0x03, 0x18,        /* 1888 */
    0x20, 0x16,        /* 1889 */
    0x83, 0x12,        /* 1890 */
    0x03, 0x13,        /* 1891 */
    0x20, 0x1e,        /* 1892 */
    0x69, 0x2f,        /* 1893 */
    0xb7, 0x01,        /* 1894 */
    0xb8, 0x01,        /* 1895 */
    0x6c, 0x2f,        /* 1896 */
    0xb7, 0x0a,        /* 1897 */
    0x03, 0x19,        /* 1898 */
    0xb8, 0x0a,        /* 1899 */
    0x41, 0x30,        /* 1900 */
    0x9b, 0x22,        /* 1901 */
    0xb3, 0x00,        /* 1902 */
    0x42, 0x30,        /* 1903 */
    0x9b, 0x22,        /* 1904 */
    0x03, 0x3a,        /* 1905 */
    0x03, 0x1d,        /* 1906 */
    0x7c, 0x2f,        /* 1907 */
    0xfb, 0x01,        /* 1908 */
    0x44, 0x30,        /* 1909 */
    0x75, 0x22,        /* 1910 */
    0xfb, 0x01,        /* 1911 */
    0xfb, 0x0a,        /* 1912 */
    0x43, 0x30,        /* 1913 */
    0x75, 0x22,        /* 1914 */
    0xb0, 0x01,        /* 1915 */
    0x02, 0x30,        /* 1916 */
    0x38, 0x02,        /* 1917 */
    0x00, 0x30,        /* 1918 */
    0x03, 0x19,        /* 1919 */
    0x37, 0x02,        /* 1920 */
    0x03, 0x1c,        /* 1921 */
    0x57, 0x2f,        /* 1922 */
    0x41, 0x30,        /* 1923 */
    0x9b, 0x22,        /* 1924 */
    0xb3, 0x00,        /* 1925 */
    0xb3, 0x1f,        /* 1926 */
    0x9d, 0x2f,        /* 1927 */
    0xa1, 0x16,        /* 1928 */
    0xa0, 0x16,        /* 1929 */
    0x63, 0x30,        /* 1930 */
    0x7b, 0x22,        /* 1931 */
    0xa0, 0x13,        /* 1932 */
    0x03, 0x18,        /* 1933 */
    0xa0, 0x17,        /* 1934 */
    0x83, 0x12,        /* 1935 */
    0x03, 0x13,        /* 1936 */
    0x20, 0x17,        /* 1937 */
    0x21, 0x16,        /* 1938 */
    0x2f, 0x08,        /* 1939 */
    0xac, 0x00,        /* 1940 */
    0x64, 0x30,        /* 1941 */
    0x7b, 0x22,        /* 1942 */
    0xa0, 0x10,        /* 1943 */
    0x03, 0x18,        /* 1944 */
    0xa0, 0x14,        /* 1945 */
    0x83, 0x12,        /* 1946 */
    0x03, 0x13,        /* 1947 */
    0xa0, 0x2f,        /* 1948 */
    0xb3, 0x1e,        /* 1949 */
    0xa1, 0x2f,        /* 1950 */
    0x21, 0x17,        /* 1951 */
    0xb4, 0x01,        /* 1952 */
    0x34, 0x08,        /* 1953 */
    0xfb, 0x00,        /* 1954 */
    0x30, 0x30,        /* 1955 */
    0x75, 0x22,        /* 1956 */
    0x34, 0x08,        /* 1957 */
    0x03, 0x19,        /* 1958 */
    0xde, 0x2a,        /* 1959 */
    0x01, 0x3a,        /* 1960 */
    0x03, 0x19,        /* 1961 */
    0x42, 0x2b,        /* 1962 */
    0x03, 0x3a,        /* 1963 */
    0x03, 0x19,        /* 1964 */
    0x76, 0x2b,        /* 1965 */
    0x01, 0x3a,        /* 1966 */
    0x03, 0x19,        /* 1967 */
    0x87, 0x2b,        /* 1968 */
    0x07, 0x3a,        /* 1969 */
    0x03, 0x19,        /* 1970 */
    0x8f, 0x2b,        /* 1971 */
    0x01, 0x3a,        /* 1972 */
    0x03, 0x19,        /* 1973 */
    0xa9, 0x2b,        /* 1974 */
    0x03, 0x3a,        /* 1975 */
    0x03, 0x19,        /* 1976 */
    0xb5, 0x2b,        /* 1977 */
    0x01, 0x3a,        /* 1978 */
    0x03, 0x19,        /* 1979 */
    0xe5, 0x2b,        /* 1980 */
    0x0f, 0x3a,        /* 1981 */
    0x03, 0x19,        /* 1982 */
    0xf3, 0x2b,        /* 1983 */
    0x01, 0x3a,        /* 1984 */
    0x03, 0x19,        /* 1985 */
    0x09, 0x2c,        /* 1986 */
    0x03, 0x3a,        /* 1987 */
    0x03, 0x19,        /* 1988 */
    0x17, 0x2c,        /* 1989 */
    0x01, 0x3a,        /* 1990 */
    0x03, 0x19,        /* 1991 */
    0x2f, 0x2c,        /* 1992 */
    0x07, 0x3a,        /* 1993 */
    0x03, 0x19,        /* 1994 */
    0x3d, 0x2c,        /* 1995 */
    0x01, 0x3a,        /* 1996 */
    0x03, 0x19,        /* 1997 */
    0x51, 0x2c,        /* 1998 */
    0x03, 0x3a,        /* 1999 */
    0x03, 0x19,        /* 2000 */
    0x72, 0x2c,        /* 2001 */
    0x1e, 0x3a,        /* 2002 */
    0x03, 0x19,        /* 2003 */
    0x83, 0x2c,        /* 2004 */
    0x01, 0x3a,        /* 2005 */
    0x03, 0x19,        /* 2006 */
    0x8b, 0x2c,        /* 2007 */
    0x03, 0x3a,        /* 2008 */
    0x03, 0x19,        /* 2009 */
    0x95, 0x2c,        /* 2010 */
    0x01, 0x3a,        /* 2011 */
    0x03, 0x19,        /* 2012 */
    0xa6, 0x2c,        /* 2013 */
    0x07, 0x3a,        /* 2014 */
    0x03, 0x19,        /* 2015 */
    0xd6, 0x2c,        /* 2016 */
    0x01, 0x3a,        /* 2017 */
    0x03, 0x19,        /* 2018 */
    0xe4, 0x2c,        /* 2019 */
    0x03, 0x3a,        /* 2020 */
    0x03, 0x19,        /* 2021 */
    0xf0, 0x2c,        /* 2022 */
    0x01, 0x3a,        /* 2023 */
    0x03, 0x19,        /* 2024 */
    0xfd, 0x2c,        /* 2025 */
    0x0d, 0x3a,        /* 2026 */
    0x03, 0x19,        /* 2027 */
    0x4a, 0x2d,        /* 2028 */
    0x06, 0x3a,        /* 2029 */
    0x03, 0x19,        /* 2030 */
    0x4a, 0x2e,        /* 2031 */
    0x01, 0x3a,        /* 2032 */
    0x03, 0x19,        /* 2033 */
    0xb5, 0x2e,        /* 2034 */
    0x3d, 0x3a,        /* 2035 */
    0x03, 0x19,        /* 2036 */
    0x43, 0x2f,        /* 2037 */
    0xd0, 0x3a,        /* 2038 */
    0x03, 0x19,        /* 2039 */
    0x22, 0x2f,        /* 2040 */
    0x0e, 0x3a,        /* 2041 */
    0x03, 0x19,        /* 2042 */
    0x1d, 0x2f,        /* 2043 */
    0x01, 0x3a,        /* 2044 */
    0x03, 0x19,        /* 2045 */
    0x1d, 0x2f,        /* 2046 */
    0xa1, 0x2f,        /* 2047 */
};
#endif

static BOOLEAN _bIsSearching;
static MT_FE_MOBILE_MODE _eMobileMode = MtFeMobileMode_Auto;
#if (SIMAP_AUTO_ENABLE == 0)
static MT_FE_SI_MAP_MODE _eCurrentSiMap = MtFeSiMapMode_1;
static MT_FE_SI_MAP_MODE _eLastSiMap = MtFeSiMapMode_1;
#endif

/* ------------------------------------
    Function Prototypes
   ------------------------------------ */
#define QAM_CODE_RATE_MASK          0x0000000f    /*    bit0 ~ bit 3    */
#define QAM_CODE_RATE_POS           0
#define INTERLEACING_DEPTH_MASK     0x00000001    /*    bit 4            */
#define INTERLEACING_DEPTH_POS      4
#define FRAME_MODE_MASK             0x00000003    /*    bit5 ~ bit 6    */
#define FRAME_MODE_POS              5
#define SPEC_INVC_MASK              0x00000001    /*    bit7            */
#define SPEC_INVC_POS               7
#define CARRIER_MODE_MASK           0x00000001    /*    bit8            */
#define CARRIER_MODE_POS            8
#define SI_MAP_MODE_MASK            0x00000003    /*    bit9 ~ bit10    */
#define SI_MAP_MODE_POS             9
#define VERIFICATION_MASK           0x0000ffff    /*    bit16 ~ bit31    */
#define VERIFICATION_POS            16
#define VERIFICATION_CODE           0x00001234

#define SET_QAM_CODE_RATE(code, value)        code = (code & (~(QAM_CODE_RATE_MASK << QAM_CODE_RATE_POS)))\
                                                | (((value) & QAM_CODE_RATE_MASK) << QAM_CODE_RATE_POS)
#define SET_INTERLEACING_DEPTH(code, value)    code = (code & (~(INTERLEACING_DEPTH_MASK << INTERLEACING_DEPTH_POS)))\
                                                | (((value) & INTERLEACING_DEPTH_MASK) << INTERLEACING_DEPTH_POS)
#define SET_FRAME_MODE(code, value)            code = (code & ((~FRAME_MODE_MASK << FRAME_MODE_POS)))\
                                                | (((value) & FRAME_MODE_MASK) << FRAME_MODE_POS)
#define SET_SPEC_INVC(code, value)            code = (code & ((~SPEC_INVC_MASK << SPEC_INVC_POS)))\
                                                | (((value) & SPEC_INVC_MASK) << SPEC_INVC_POS)
#define SET_CARRIER_MODE(code, value)        code = (code & ((~CARRIER_MODE_MASK << CARRIER_MODE_POS)))\
                                                | (((value) & CARRIER_MODE_MASK) << CARRIER_MODE_POS)
#define SET_SI_MAP_MODE(code, value)        code = (code & ((~(SI_MAP_MODE_MASK << SI_MAP_MODE_POS))))\
                                                | (((value) & SI_MAP_MODE_MASK) << SI_MAP_MODE_POS)
#define SET_VERIFICATION_CODE(code, value)    code = (code & (~VERIFICATION_MASK << VERIFICATION_POS))\
                                                | (((value) & VERIFICATION_MASK) << VERIFICATION_POS)

#define GET_QAM_CODE_RATE(code)                ((code >> QAM_CODE_RATE_POS     ) & QAM_CODE_RATE_MASK     )
#define GET_INTERLEACING_DEPTH(code)        ((code >> INTERLEACING_DEPTH_POS) & INTERLEACING_DEPTH_MASK)
#define GET_FRAME_MODE(code)                ((code >> FRAME_MODE_POS        ) & FRAME_MODE_MASK        )
#define GET_SPEC_INVC(code)                    ((code >> SPEC_INVC_POS         ) & SPEC_INVC_MASK         )
#define GET_CARRIER_MODE(code)                ((code >> CARRIER_MODE_POS      ) & CARRIER_MODE_MASK      )
#define GET_SI_MAP_MODE(code)                ((code >> SI_MAP_MODE_POS       ) & SI_MAP_MODE_MASK       )
#define GET_VERIFICATION_CODE(code)            ((code >> VERIFICATION_POS      ) & VERIFICATION_MASK      )

/***********************************************************************************
  Subject:    Power on initialized function
  Function:   M88DC2800_Initialize
  Parmeter:
  Return:     BOOLEAN
  Remark:
************************************************************************************/
void M88DD2000_Initialize( void )
{
    _bIsSearching  = 0;
    _eMobileMode   = MtFeMobileMode_Auto;

#if (SIMAP_AUTO_ENABLE == 0)
    _eCurrentSiMap = MtFeSiMapMode_1;
    _eLastSiMap    = MtFeSiMapMode_1;
#endif

    M88DD2000_InitRegister();
    M88DD2000_LoadFw(m88dd2k_fm);
    M88DD2000_SetMobileMode(MtFeMobileMode_Auto);
#if TS_PARALLEL_OUTPUT
    M88DD2000_Serial_Control(FALSE);
#else
    M88DD2000_Serial_Control(TRUE);
#endif
}

BOOLEAN M88DD2000_InitRegister(void)
{
    U8 cAddress;
    U8 cData;
    U8 i;

#if (ERR_PIN_ENABLE != 0)
    if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0x04, 0x84 ) == FALSE )
         return FAIL;
#else
    if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0x04, 0x04 ) == FALSE )
         return FAIL;
#endif


    for ( i = 0; i < ( sizeof( m_InitDataCOFDM ) / sizeof( INIT_DATA_COFDM_DEM ) ); i++ )
    {
        cAddress = m_InitDataCOFDM[i].cAddress;
        cData = m_InitDataCOFDM[i].cData;

        if ( FALSE == MDrv_IIC_WriteByte( M88DD2000_devAddr, cAddress, cData ) )
        {
            M88DD2000_DBG( printf( "I2C Error!!! cofdmInit \n" ) );
            return FAIL;
        }

    }

#if (MT_FE_DMD_CURRENT_ID == MT_FE_DMD_ID_DD2001)
    if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xC6, 0x0A ) == FALSE )
         return FAIL;
#endif



#if (SIMAP_AUTO_ENABLE != 0)

    #if (SIMAP_AUTO_EXTEND != 0)
    if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xBD, 0x81 ) == FALSE )
         return FAIL;
    #endif
    if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCB, 0x80 ) == FALSE )
         return FAIL;
#else
    if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xBD, 0x80 ) == FALSE )
         return FAIL;
#endif

    return PASS;
}

void M88DD2000_Config(void)
{
    MT_FE_CHAN_INFO    si_desc;

    M88DD2000_ChannelInfoCodeParse(0, &si_desc);
    M88DD2000_PresetChannelInfo(&si_desc);


    #if (SIMAP_AUTO_ENABLE == 0)
    if (si_desc.si_map_mode == MtFeSiMapMode_Undef)
        _eCurrentSiMap = _eLastSiMap;
    else
        _eCurrentSiMap = si_desc.si_map_mode;

    M88DD2000_SetSiMapMode(_eCurrentSiMap);
    #endif

    M88DD2000_SoftReset();
}

BOOLEAN M88DD2000_LoadFw(const U8* p_fw)
{
    U16 i;
    U8 u8DD2KData[3];

    if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xB7, 0x01 ) == FALSE )
         goto LoadFwFail;

    MsOS_DelayTask( 1 );

    u8DD2KData[0] = 0xB5;
    for (i = 0; i < 2048; i++)
    {
        u8DD2KData[1] = *(p_fw++);
        u8DD2KData[2] = *(p_fw++);

        if (MDrv_IIC_WriteBytes(M88DD2000_devAddr, 0, NULL, 3, u8DD2KData) == FALSE)
            goto LoadFwFail;
    }

    if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xB7, 0x00 ) == FALSE )
         goto LoadFwFail;


    return PASS;

    LoadFwFail:
        M88DD2000_DBG( printf( "I2C Error!!! M88DD2K LOAD FW \n" ) );
        return FAIL;

}

BOOLEAN M88DD2000_SetMobileMode(MT_FE_MOBILE_MODE eMode)
{
    U32 u32ChanInfoCode;
    MT_FE_CHAN_INFO    chan_info;
    U8 u8Temp;

    M88DD2000_GetChannelInfoCode(&u32ChanInfoCode);
    M88DD2000_ChannelInfoCodeParse(u32ChanInfoCode, &chan_info);

    switch (eMode)
    {
        case MtFeMobileMode_Auto:
            if( MDrv_IIC_ReadByte( M88DD2000_devAddr, 0x8D, &u8Temp ) == FALSE )
                return FAIL;
            u8Temp |= 0x80;
            if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0x8D, u8Temp ) == FALSE )
                return FAIL;

            if( MDrv_IIC_ReadByte( M88DD2000_devAddr, 0xBD, &u8Temp ) == FALSE )
                return FAIL;
            u8Temp |= 0x40;
            if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xBD, u8Temp ) == FALSE )
                return FAIL;

            if( MDrv_IIC_ReadByte( M88DD2000_devAddr, 0x8B, &u8Temp ) == FALSE )
                return FAIL;
            u8Temp &= ~0x40;
            if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0x8B, u8Temp ) == FALSE )
                return FAIL;

            if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0x8C, 0xDE ) == FALSE )
                return FAIL;
            break;

        case MtFeMobileMode_Off:
            if( MDrv_IIC_ReadByte( M88DD2000_devAddr, 0x8D, &u8Temp ) == FALSE )
                return FAIL;
            u8Temp &= ~0x80;
            if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0x8D, u8Temp ) == FALSE )
                return FAIL;

            if( MDrv_IIC_ReadByte( M88DD2000_devAddr, 0xBD, &u8Temp ) == FALSE )
                return FAIL;
            u8Temp |= 0x40;
            if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xBD, u8Temp ) == FALSE )
                return FAIL;


            if( MDrv_IIC_ReadByte( M88DD2000_devAddr, 0x8B, &u8Temp ) == FALSE )
                return FAIL;
            u8Temp |= 0x40;
            if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0x8B, u8Temp ) == FALSE )
                return FAIL;

            if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0x8C, 0x1E ) == FALSE )
                return FAIL;
            break;

        case MtFeMobileMode_On:
            if( MDrv_IIC_ReadByte( M88DD2000_devAddr, 0x8D, &u8Temp ) == FALSE )
                return FAIL;
            u8Temp &= ~0x80;
            if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0x8D, u8Temp ) == FALSE )
                return FAIL;

            if( MDrv_IIC_ReadByte( M88DD2000_devAddr, 0xBD, &u8Temp ) == FALSE )
                return FAIL;
            u8Temp &= ~0x40;
            if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xBD, u8Temp ) == FALSE )
                return FAIL;

            if( MDrv_IIC_ReadByte( M88DD2000_devAddr, 0x8B, &u8Temp ) == FALSE )
                return FAIL;
            u8Temp &= ~0x40;
            if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0x8B, u8Temp ) == FALSE )
                return FAIL;

            if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0x8C, 0xDE ) == FALSE )
                return FAIL;

            if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0x7F, 0x00 ) == FALSE )
                return FAIL;

            if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0x80, 0xA2 ) == FALSE )
                return FAIL;
            break;

        default:
            break;
    }

    _eMobileMode = eMode;

    return PASS;
}

BOOLEAN M88DD2000_GetChannelInfoCode(U32 *pChanInfo)
{
    U8 u8SiCode, u8ScMode;
    U32    u32InfoCode = 0;

    SET_VERIFICATION_CODE(u32InfoCode, VERIFICATION_CODE);

    if( MDrv_IIC_ReadByte( M88DD2000_devAddr, 0xC2, &u8ScMode ) == FALSE )
        return FAIL;
    if( MDrv_IIC_ReadByte( M88DD2000_devAddr, 0xC4, &u8SiCode ) == FALSE )
        return FAIL;

    M88DD2000_DBG( printf("M88DD2000:    0xC2      = 0x%2x\n", u8ScMode) );
    M88DD2000_DBG( printf("M88DD2000:    0xC4      = 0x%2x\n", u8SiCode) );

    if ((u8ScMode & 0x20) == 0)
        SET_CARRIER_MODE(u32InfoCode, 0);    /*    Multicarrier    */
    else
        SET_CARRIER_MODE(u32InfoCode, 1);    /*    Single carrier    */


    if ((u8SiCode & 0x80) == 0)
        SET_SPEC_INVC(u32InfoCode, 0);
    else
        SET_SPEC_INVC(u32InfoCode, 1);


    if ((u8SiCode & 0x60) == 0x00)
        SET_FRAME_MODE(u32InfoCode, 0);
    else if ((u8SiCode & 0x60) == 0x20)
        SET_FRAME_MODE(u32InfoCode, 1);
    else if ((u8SiCode & 0x60) == 0x40)
        SET_FRAME_MODE(u32InfoCode, 2);


    if ((u8SiCode & 0x10) == 0)
        SET_INTERLEACING_DEPTH(u32InfoCode, 0);
    else
        SET_INTERLEACING_DEPTH(u32InfoCode, 1);


    SET_QAM_CODE_RATE(u32InfoCode, u8SiCode & 0x0f);

#if (SIMAP_AUTO_ENABLE == 0)
    if (_eCurrentSiMap == MtFeSiMapMode_1)
        SET_SI_MAP_MODE(u32InfoCode, 1);
    else if (_eCurrentSiMap == MtFeSiMapMode_2)
        SET_SI_MAP_MODE(u32InfoCode, 2);
#endif

    *pChanInfo = u32InfoCode;

    return PASS;
}

void M88DD2000_ChannelInfoCodeParse(U32 chan_info_code, MT_FE_CHAN_INFO* p_info)
{
    if (GET_VERIFICATION_CODE(chan_info_code) != VERIFICATION_CODE)
    {
        p_info->carrier_mode          = MtFeCrrierMode_Undef;
        p_info->spectrum_mode         = MtFeSpectrum_Undef;
        p_info->frame_mode            = MtFeFrameMode_Undef;
        p_info->interleaving_depth    = MtFeInterleavingDepth_Undef;
        p_info->constellation_pattern = MtFeConstellationPattern_Undef;
        p_info->fec_code_rate         = MtFeFecCodeRate_Undef;
        p_info->si_map_mode           = MtFeSiMapMode_Undef;

        return;
    }


#if (SIMAP_AUTO_ENABLE == 0)
    if (GET_SI_MAP_MODE(chan_info_code) == 0)
        p_info->si_map_mode = MtFeSiMapMode_Undef;
    else if (GET_SI_MAP_MODE(chan_info_code) == 1)
        p_info->si_map_mode = MtFeSiMapMode_1;
    else if (GET_SI_MAP_MODE(chan_info_code) == 2)
        p_info->si_map_mode = MtFeSiMapMode_2;
#endif


    if (GET_CARRIER_MODE(chan_info_code) == 0)
        p_info->carrier_mode = MtFeCrrierMode_Multicarrier;
    else
        p_info->carrier_mode = MtFeCrrierMode_SingleCarrier;



    if (GET_SPEC_INVC(chan_info_code) == 0)
        p_info->spectrum_mode = MtFeSpectrum_NoInversion;
    else
        p_info->spectrum_mode = MtFeSpectrum_Inversion;



    if (GET_FRAME_MODE(chan_info_code) == 0x00)
        p_info->frame_mode = MtFeFrameMode_Pn420;
    else if (GET_FRAME_MODE(chan_info_code) == 0x01)
        p_info->frame_mode = MtFeFrameMode_Pn945;
    else if (GET_FRAME_MODE(chan_info_code) == 0x02)
        p_info->frame_mode = MtFeFrameMode_Pn595;
    else
        p_info->frame_mode = MtFeFrameMode_Undef;



    if (GET_INTERLEACING_DEPTH(chan_info_code) == 0)
        p_info->interleaving_depth = MtFeInterleavingDepth_240;
    else
        p_info->interleaving_depth = MtFeInterleavingDepth_720;



    switch (GET_QAM_CODE_RATE(chan_info_code))
    {
    case 0x01:    /*    4QAM, 0.4        */
        p_info->constellation_pattern = MtFeConstellationPattern_4Qam;
        p_info->fec_code_rate         = MtFeFecCodeRate_0p4;
        break;
    case 0x02:    /*    4QAM, 0.6        */
        p_info->constellation_pattern = MtFeConstellationPattern_4Qam;
        p_info->fec_code_rate         = MtFeFecCodeRate_0p6;
        break;
    case 0x03:    /*    4QAM, 0.8        */
        p_info->constellation_pattern = MtFeConstellationPattern_4Qam;
        p_info->fec_code_rate         = MtFeFecCodeRate_0p8;
        break;
    case 0x07:    /*    4QAM-NR, 0.8    */
        p_info->constellation_pattern = MtFeConstellationPattern_4QamNr;
        p_info->fec_code_rate         = MtFeFecCodeRate_0p8;
        break;
    case 0x09:    /*    16QAM, 0.4        */
        p_info->constellation_pattern = MtFeConstellationPattern_16Qam;
        p_info->fec_code_rate         = MtFeFecCodeRate_0p4;
        break;
    case 0x0a:    /*    16QAM, 0.6        */
        p_info->constellation_pattern = MtFeConstellationPattern_16Qam;
        p_info->fec_code_rate         = MtFeFecCodeRate_0p6;
        break;
    case 0x0b:    /*    16QAM, 0.8        */
        p_info->constellation_pattern = MtFeConstellationPattern_16Qam;
        p_info->fec_code_rate         = MtFeFecCodeRate_0p8;
        break;
    case 0x0c:    /*    32QAM, 0.8        */
        p_info->constellation_pattern = MtFeConstellationPattern_32Qam;
        p_info->fec_code_rate         = MtFeFecCodeRate_0p8;
        break;
    case 0x0d:    /*    64QAM, 0.4        */
        p_info->constellation_pattern = MtFeConstellationPattern_64Qam;
        p_info->fec_code_rate         = MtFeFecCodeRate_0p4;
        break;
    case 0x0e:    /*    64QAM, 0.6        */
        p_info->constellation_pattern = MtFeConstellationPattern_64Qam;
        p_info->fec_code_rate         = MtFeFecCodeRate_0p6;
        break;
    case 0x0f:    /*    64QAM, 0.8        */
        p_info->constellation_pattern = MtFeConstellationPattern_64Qam;
        p_info->fec_code_rate         = MtFeFecCodeRate_0p8;
        break;
    default:
        p_info->constellation_pattern = MtFeConstellationPattern_Undef;
        p_info->fec_code_rate         = MtFeFecCodeRate_Undef;
        break;
    }

    M88DD2000_DBG( printf("M88DD2000:    **    CHAN INFO    **\n") );
    M88DD2000_DBG( printf("M88DD2000:    carrier_mode          = %d\n", p_info->carrier_mode) );
    M88DD2000_DBG( printf("M88DD2000:    constellation_pattern = %d\n", p_info->constellation_pattern) );
    M88DD2000_DBG( printf("M88DD2000:    fec_code_rate         = %d\n", p_info->fec_code_rate) );
    M88DD2000_DBG( printf("M88DD2000:    frame_mode            = %d\n", p_info->frame_mode) );
    M88DD2000_DBG( printf("M88DD2000:    interleaving_depth    = %d\n", p_info->interleaving_depth) );
    M88DD2000_DBG( printf("M88DD2000:    spectrum_mode         = %d\n", p_info->spectrum_mode) );
    M88DD2000_DBG( printf("M88DD2000:    si_map_mode           = %d\n", p_info->si_map_mode) );

    return;
}

BOOLEAN M88DD2000_PresetChannelInfo(MT_FE_CHAN_INFO* p_info)
{
    U8 RegC0H;
    U8 RegC1H;

    RegC0H = 0x00;
    RegC1H = 0x81;

    if (p_info == NULL)
    {
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xC0, RegC0H ) == FALSE )
             return FAIL;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xC1, RegC1H ) == FALSE )
             return FAIL;

        return 0;
    }

    if (p_info->carrier_mode == MtFeCrrierMode_SingleCarrier)
        RegC0H |= 0x48;
    else if (p_info->carrier_mode == MtFeCrrierMode_Multicarrier)
        RegC0H |= 0x40;


    if (p_info->spectrum_mode == MtFeSpectrum_NoInversion)
        RegC0H |= 0x20;
    else if (p_info->spectrum_mode == MtFeSpectrum_Inversion)
        RegC0H |= 0x24;

    if (p_info->interleaving_depth != MtFeInterleavingDepth_Undef
        && p_info->constellation_pattern != MtFeConstellationPattern_Undef
        && p_info->fec_code_rate != MtFeFecCodeRate_Undef)
    {
        RegC0H |= 0x10;

        if (p_info->interleaving_depth != MtFeInterleavingDepth_240)
        RegC1H |= 0x10;


        if (p_info->constellation_pattern == MtFeConstellationPattern_4Qam)
        {
            if (p_info->fec_code_rate == MtFeFecCodeRate_0p4)
                RegC1H |= 0x01;
            else if (p_info->fec_code_rate == MtFeFecCodeRate_0p6)
                RegC1H |= 0x02;
            else if (p_info->fec_code_rate == MtFeFecCodeRate_0p8)
                RegC1H |= 0x03;
        }
        else if (p_info->constellation_pattern == MtFeConstellationPattern_4QamNr)
        {
            RegC1H |= 0x07;
        }
        else if (p_info->constellation_pattern == MtFeConstellationPattern_16Qam)
        {
            if (p_info->fec_code_rate == MtFeFecCodeRate_0p4)
                RegC1H |= 0x09;
            else if (p_info->fec_code_rate == MtFeFecCodeRate_0p6)
                RegC1H |= 0x0a;
            else if (p_info->fec_code_rate == MtFeFecCodeRate_0p8)
                RegC1H |= 0x0b;
        }
        else if (p_info->constellation_pattern == MtFeConstellationPattern_32Qam)
        {
            RegC1H |= 0x0c;
        }
        else if (p_info->constellation_pattern == MtFeConstellationPattern_64Qam)
        {
            if (p_info->fec_code_rate == MtFeFecCodeRate_0p4)
                RegC1H |= 0x0d;
            else if (p_info->fec_code_rate == MtFeFecCodeRate_0p6)
                RegC1H |= 0x0e;
            else if (p_info->fec_code_rate == MtFeFecCodeRate_0p8)
                RegC1H |= 0x0f;
        }
    }

    if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xC0, RegC0H ) == FALSE )
         return FAIL;
    if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xC1, RegC1H ) == FALSE )
         return FAIL;

    M88DD2000_DBG( printf("M88DD2000:    preset_chan_info [0xc0 = 0x%2x][0xc1 = 0x%2x]\n",RegC0H,RegC1H) );

    return 0;
}

BOOLEAN M88DD2000_SetSiMapMode(MT_FE_SI_MAP_MODE mode)
{
    if (mode == MtFeSiMapMode_2)
    {
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCB, 0x0C ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCC, 0x48 ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCB, 0x0D ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCC, 0x48 ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCB, 0x0E ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCC, 0x48 ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCB, 0x0F ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCC, 0x48 ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCB, 0x10 ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCC, 0x48 ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCB, 0x11 ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCC, 0x48 ) == FALSE ) goto WriteFail;

        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCB, 0x18 ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCC, 0x48 ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCB, 0x19 ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCC, 0x48 ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCB, 0x1A ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCC, 0x48 ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCB, 0x1B ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCC, 0x48 ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCB, 0x1C ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCC, 0x48 ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCB, 0x1D ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCC, 0x48 ) == FALSE ) goto WriteFail;
    }
    else
    {
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCB, 0x0C ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCC, 0x60 ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCB, 0x0D ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCC, 0x60 ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCB, 0x0E ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCC, 0x60 ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCB, 0x0F ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCC, 0x60 ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCB, 0x10 ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCC, 0x60 ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCB, 0x11 ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCC, 0x60 ) == FALSE ) goto WriteFail;

        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCB, 0x18 ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCC, 0x70 ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCB, 0x19 ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCC, 0x70 ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCB, 0x1A ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCC, 0x70 ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCB, 0x1B ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCC, 0x70 ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCB, 0x1C ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCC, 0x70 ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCB, 0x1D ) == FALSE ) goto WriteFail;
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xCC, 0x70 ) == FALSE ) goto WriteFail;
    }


    return PASS;

    WriteFail:
        return FAIL;
}

BOOLEAN M88DD2000_EnhancePerformance(U32 chan_info_code)
{
    MT_FE_CHAN_INFO chan_info;


    M88DD2000_ChannelInfoCodeParse(chan_info_code, &chan_info);


    if (chan_info.carrier_mode == MtFeCrrierMode_Multicarrier)
    {
        if (_eMobileMode == MtFeMobileMode_On)
        {
            if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0x80, 0xC2 ) == FALSE )
                return FAIL;
        }
    }
    else if (chan_info.carrier_mode == MtFeCrrierMode_SingleCarrier)
    {
        if (_eMobileMode == MtFeMobileMode_On)
        {
            if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0x80, 0xA2 ) == FALSE )
                return FAIL;
        }
    }


    return PASS;
}

/***********************************************
   Set the type of MPEG/TS interface
   type: 1, serial format; 0, parallel format
************************************************/
BOOLEAN M88DD2000_Serial_Control(BOOLEAN bEnable)
{
    U8 u8Temp;

    if( MDrv_IIC_ReadByte( M88DD2000_devAddr, 0xB1, &u8Temp ) == FALSE )
        return FAIL;

    if(bEnable)
        u8Temp |= 0x04;
    else
        u8Temp &= ~0x04;

    if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xB1, u8Temp ) == FALSE )
         return FAIL;

    return 0;
}

BOOLEAN M88DD2000_SoftReset(void)
{
    _bIsSearching = 1;

    if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xB7, 0x01 ) == FALSE )
        return FAIL;
    if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0x05, 0x40 ) == FALSE )
        return FAIL;
    if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0x00, 0x01 ) == FALSE )
        return FAIL;
    if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0x00, 0x00 ) == FALSE )
        return FAIL;
    if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0x05, 0x00 ) == FALSE )
        return FAIL;
    if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0xB7, 0x00 ) == FALSE )
        return FAIL;

    MsOS_DelayTask( 100 );

    return 0;
}

BOOLEAN M88DD2000_WriteBytesRepeat(U8 u8SlaveID, U8 u8AddrNum, U8* paddr, U16 u16size, U8* pu8data)
{
    U8 u8Temp;

    if( MDrv_IIC_ReadByte( M88DD2000_devAddr, 0x03, &u8Temp ) == FALSE )
        return FAIL;

    if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0x03, 0x11 ) == FALSE )
        return FAIL;

    MDrv_IIC_WriteBytes(u8SlaveID, u8AddrNum, paddr, u16size, pu8data);

    if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0x03, u8Temp ) == FALSE )
        return FAIL;

    return 0;
}

BOOLEAN M88DD2000_ReadBytesRepeat(U8 u8SlaveID, U8 u8AddrNum, U8* paddr, U16 u16size, U8* pu8data)
{
    U8 u8Temp;

    if( MDrv_IIC_ReadByte( M88DD2000_devAddr, 0x03, &u8Temp ) == FALSE )
        return FAIL;

    if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0x03, 0x11 ) == FALSE )
        return FAIL;

    MDrv_IIC_ReadBytes(u8SlaveID, u8AddrNum, paddr, u16size, pu8data);

    if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0x03, u8Temp ) == FALSE )
        return FAIL;

    return 0;

}

BOOLEAN M88DD2000_GetLock(void)
{
    U8    u8Temp;
    U32    chan_info_code;
    static U8 last_lock_state = 0;
    static U8 last_0xc8_reg = 0;

    if (_bIsSearching == 1)
    {
        last_lock_state = 0;

        if( MDrv_IIC_ReadByte( M88DD2000_devAddr, 0xB8, &u8Temp ) == FALSE ) goto IIC_FAIL;

        M88DD2000_DBG( printf("M88DD2000:    0xB8 = 0x%2x\n", u8Temp) );

        if (u8Temp != 0xf0
            && u8Temp != 0x00
            && u8Temp != 0x20
            && u8Temp != 0x01
            && u8Temp != 0xff
            && u8Temp != 0xfe)
            return FALSE;


        _bIsSearching = 0;



    #if (SIMAP_AUTO_ENABLE == 0)

        M88DD2000_GetChannelInfoCode(&chan_info_code);
        M88DD2000_EnhancePerformance(chan_info_code);


        MsOS_DelayTask( 100 );

        if( MDrv_IIC_ReadByte( M88DD2000_devAddr, 0xC2, &u8Temp ) == FALSE ) goto IIC_FAIL;

        if ((u8Temp & 0x40) == 0)
        {/*    Unlock    */
            if (_eCurrentSiMap == MtFeSiMapMode_2)
                _eCurrentSiMap = MtFeSiMapMode_1;
            else
                _eCurrentSiMap = MtFeSiMapMode_2;


            M88DD2000_SetSiMapMode(_eCurrentSiMap);

            return FALSE;
        }

    #endif
    }

    if( MDrv_IIC_ReadByte( M88DD2000_devAddr, 0xC2, &u8Temp ) == FALSE ) goto IIC_FAIL;

    if ((u8Temp & 0x40) == 0)
    {/*    Unlock    */
        last_lock_state = 0;
        M88DD2000_DBG( printf("M88DD2000:    FEC Unlock!!  [0xc2 = 0x%x]\n", u8Temp) );
        return FALSE;
    }

    if (last_lock_state == 0)
    {/*    First time locked    */
        M88DD2000_GetChannelInfoCode(&chan_info_code);
        M88DD2000_EnhancePerformance(chan_info_code);
        last_lock_state = 1;
    }

    if (_eMobileMode == MtFeMobileMode_Auto)
    {
        if( MDrv_IIC_ReadByte( M88DD2000_devAddr, 0xC8, &u8Temp ) == FALSE ) goto IIC_FAIL;

        if ((last_0xc8_reg & 0x0F) != (u8Temp & 0x0F))
        {
            last_0xc8_reg = u8Temp;

            if( MDrv_IIC_ReadByte( M88DD2000_devAddr, 0x8B, &u8Temp ) == FALSE ) goto IIC_FAIL;

            if ((last_0xc8_reg & 0x0F) == 0)
                u8Temp &= ~0x40;
            else
                u8Temp |= 0x40;

            if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0x8B, u8Temp ) == FALSE ) goto IIC_FAIL;
        }
    }

#if (SIMAP_AUTO_ENABLE == 0)
    _eLastSiMap = _eCurrentSiMap;
#endif

    M88DD2000_DBG( printf("M88DD2000:    FEC lock!!  [0xc2 = 0x%x]\n", u8Temp) );

    return TRUE;

    IIC_FAIL:
        return FALSE;
}

/***********************************************
   TS output Enable
   flag = 1, enable ts output ; 0 disable ts output
************************************************/
BOOLEAN M88DD2000_TSOut_Control(BOOLEAN bEnable)
{
    if(bEnable)
    {
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0x07, 0x03 ) == FALSE )
            return FAIL;
    }
    else
    {
        if( MDrv_IIC_WriteByte( M88DD2000_devAddr, 0x07, 0x01 ) == FALSE )
            return FAIL;
    }

    return PASS;
}

#undef _M88DD2000_C_
