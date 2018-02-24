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
///////////////////////////////////////////////////////////////////////////////////////////////////
/// @file   utl.h
/// @author MStar Semiconductor Inc.
/// @brief  utilities including memory, printf, string functions, etc..
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MS_UTL_H
#define MS_UTL_H

#include <stdarg.h>
#include "datatype.h"


typedef enum _tag_enumStdFuncState
{
    E_STD_NORMAL,
    E_STD_FROMAT,
    E_STD_HEX,
    E_STD_DEC,
    E_STD_STRING,
    E_STD_ERROR
} enumStdFuncState;


///////////////////////////////////////////////////////////////////////////////
// standard memory functions ( make sure to redirect to UTL_* )
///////////////////////////////////////////////////////////////////////////////
#ifndef MSOS_TYPE_LINUX

void *UTL_memset( void *d, int c, size_t n );
#define memset      UTL_memset

void *UTL_memcpy(void *d, const void *s, size_t n);
#define memcpy      UTL_memcpy

void *UTL_memcpy_swap(void *pDest, const void *pSrc, U32 u32Cnt);
#define memcpy_swap      UTL_memcpy_swap
///////////////////////////////////////////////////////////////////////////////
// standard string functions ( make sure to redirect to UTL_* )
///////////////////////////////////////////////////////////////////////////////
char *UTL_strcpy(char *strDst, const char *strSrc);
#define strcpy              UTL_strcpy

char *UTL_strchr(const char *string,int chr);
#ifndef __arm__
#define strchr              UTL_strchr
#endif

U16 *UTL_wcschr(const U16 *string,int chr);
#define wcschr              UTL_wcschr

char *UTL_strrchr(const char *string,int chr);
#define strrchr             UTL_strrchr

U16 *UTL_wcsrchr (const U16 *string,U16 ch);
#define wcsrchr             UTL_wcsrchr

int UTL_strcmp(const char *string1, const char *string2);
#ifndef __arm__
#define strcmp              UTL_strcmp
#endif

int UTL_wcscmp(const U16 *string1, const U16 *string2);
#define wcscmp              UTL_wcscmp

int UTL_strncmp( const char *string1, const char *string2, size_t count );
#ifndef __arm__
#define strncmp             UTL_strncmp
#endif

int UTL_wcsncmp( const U16 *string1, const U16 *string2, int count );
#define wcsncmp             UTL_wcsncmp

U16 *UTL_wcscpy(U16 *strDst, const U16 *strSrc);
#define wcscpy              UTL_wcscpy

size_t UTL_strlen(const char *pStr);
#define strlen              UTL_strlen

int UTL_wcslen(const U16 *pStr);
#define wcslen              UTL_wcslen

char *UTL_strncpy( char *strDest, const char *strSource, size_t count );
#ifndef __arm__
#define strncpy             UTL_strncpy
#endif

U16 *UTL_wcsncpy( U16 *strDest, const U16 *strSource, int count );
#define wcsncpy             UTL_wcsncpy

U16 *UTL_wcsupr(U16 *string);
#define wcsupr              UTL_wcsupr

char *UTL_strupr(char *string);
#define strupr              UTL_strupr

char* UTL_strcat(char *strDst, const char *strSrc);
#define strcat              UTL_strcat

int UTL_isprint(int c);
#define isprint             UTL_isprint

int UTL_isspace(int c);
#define isspace             UTL_isspace

char *UTL_skipspace(const char *pInStr);
#define skipspace             UTL_skipspace

int UTL_isalnum(int c);
#define isalnum             UTL_isalnum

int UTL_isdigit(int c);
#define isdigit             UTL_isdigit

int UTL_isxdigit(int c);
#define isxdigit            UTL_isxdigit

int UTL_tolower(int c);
#define tolower             UTL_tolower

int UTL_toupper(int c);
#define toupper             UTL_toupper

#else
//Fix me!!
U16 *UTL_wcscpy(U16 *strDst, const U16 *strSrc);
#endif



///////////////////////////////////////////////////////////////////////////////
// proprietary string functions
///////////////////////////////////////////////////////////////////////////////
int UTL_charToInt(char c);
int UTL_U32ToHexStr(U32 u32Val, char *pOutStr);
int UTL_IntToDecStr(int iVal, char *pOutStr);

#endif

