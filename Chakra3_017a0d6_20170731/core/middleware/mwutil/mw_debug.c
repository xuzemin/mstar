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
#define _MW_DEBUG_C_
////////////////////////////////////////////////////////////////////////////////
///
/// @file mw_debug.c
/// @author MStar Semiconductor Inc.
/// @brief MW Debug Related Functions
///
////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*                              Header Files                                  */
/******************************************************************************/
// C Library
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

// Global
#include "datatype.h"
#include "sysinfo.h"
//...
#include "debug.h"

// Driver Layer
//...

// API Layer
//...

// MW Layer
#include "mw_debug.h"


//------------------------------------------------------------------------------
/// MW Debug message
/// @param u32Module \b IN: Module type
/// @param u32Level \b IN: Level type
/// @param fmt \b IN: debug message string
/// @param ... \b IN: variable parameter
/// @return None
//------------------------------------------------------------------------------
void MWDBGprintf(U32 u32Module, U32 u32Level, char* fmt, ...)
{
    va_list arg_ptr;
    U32 u32Var[6];

    // For auto test. except MWDBGLVL_AUTO_TEST, other messages should be ignored
    if(u32MWDebugLevelMask & MWDBGLVL_AUTO_TEST)
        u32Level &= MWDBGLVL_AUTO_TEST;

    if((u32Module & u32MWDebugModuleMask) &&
       (u32Level & u32MWDebugLevelMask))
    {
        va_start(arg_ptr, fmt);

        u32Var[0] = va_arg(arg_ptr, U32);
        u32Var[1] = va_arg(arg_ptr, U32);
        u32Var[2] = va_arg(arg_ptr, U32);
        u32Var[3] = va_arg(arg_ptr, U32);
        u32Var[4] = va_arg(arg_ptr, U32);
        u32Var[5] = va_arg(arg_ptr, U32);

        MS_DEBUG_MSG(printf(fmt, u32Var[0], u32Var[1], u32Var[2], u32Var[3], u32Var[4], u32Var[5]));
        va_end(arg_ptr);
    }
    else
    {
        // No Message!
    }
}

//------------------------------------------------------------------------------
/// MW Debug Initial
/// @param  None
/// @return None
//------------------------------------------------------------------------------
void MWDebugInitial(void)
{
    u32MWDebugModuleMask = MWDBG_ERR + MWDBG_TEST;
    u32MWDebugLevelMask = MWDBGLVL_TEST;
}

//------------------------------------------------------------------------------
/// MW Debug Get Module switch enable flag
/// @param  None
/// @return U32 Module switch enable flag
//------------------------------------------------------------------------------
U32 MWDebugGetModuleValue (void)
{
    return u32MWDebugModuleMask;
}

//------------------------------------------------------------------------------
/// MW Debug Set Module switch enable flag
/// @param u32value \b IN: Set Module switch enable flag
/// @return None
//------------------------------------------------------------------------------
void MWDebugSetModuleValue (U32 u32value)
{
    u32MWDebugModuleMask = u32value;
}

//------------------------------------------------------------------------------
/// MW Debug Get Level switch enable flag
/// @param  None
/// @return U32 Level switch enable flag
//------------------------------------------------------------------------------
U32 MWDebugGetLevelValue (void)
{
    return u32MWDebugLevelMask;
}

//------------------------------------------------------------------------------
/// MW Debug Set Level switch enable flag
/// @param u32value \b IN: Set Level switch enable flag
/// @return None
//------------------------------------------------------------------------------
void MWDebugSetLevelValue (U32 u32value)
{
    u32MWDebugLevelMask = u32value;
}


//------------------------------------------------------------------------------
/// MW Debug Show Version String
/// @param *string \b IN: string pointer
/// @return None
//------------------------------------------------------------------------------
void MWDebugShowVerString(U8 *string)
{
    U8 indexS, indexD, x;
    U8 temp[2];
    U8 MWVer[40];

    memset(&MWVer[0], 0x00, sizeof(MWVer));
    memcpy(&MWVer[0], &string[0], MWVER_HEADER_LENGTH);
    indexS = MWVER_HEADER_LENGTH;
    indexD = MWVER_HEADER_LENGTH;

    for(indexS=MWVER_MS_ID_OFFSET; indexS<(MWVER_MS_ID_OFFSET+MWVER_MS_ID_LENGTH); indexS++)
    {
        temp[0] = (string[indexS] >> 4) & 0x0F;
        temp[1] = string[indexS] & 0x0F;
        for(x=0; x<sizeof(temp); x++)
        {
            if(temp[x]<=0x09)
            {
                MWVer[indexD++] = temp[x]+'0';
            }
            else
            {
                MWVer[indexD++] = temp[x]+'A'-0x0A;
            }
        }
    }

    memcpy(&MWVer[indexD], &string[indexS], MWVER_LIBINFO_LENGTH);

    MS_DEBUG_MSG(printf("Ver:%s\n", &MWVer[0]));
}

