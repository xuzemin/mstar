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
// @file   utl.c
// @author MStar Semiconductor Inc.
// @brief  utilities including memory, printf, string functions, etc..
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include <stdarg.h>
#include <stdio.h>
#include "datatype.h"
#include "Utl.h"
#if defined (MSOS_TYPE_ECOS)
#include "MsCommon.h"
#include "asmCPU.h"
#endif


//-------------------------------------------------------------------------------------------------
// Local Defines
//-------------------------------------------------------------------------------------------------
#define PRINTF_CHAR_MAX         256  //max # of characters for UTL_printf
#define SPRINTF_CHAR_MAX        1024 //max # of characters for UTL_sprintf
#define SPRINTF_FIELD_MAX       256
#define MEM_DEBUG  0

//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Global Variables
//-------------------------------------------------------------------------------------------------
#if defined(__mips__)||defined(__arm__)
extern void   MAsm_CPU_Sync(void);
#endif
//-------------------------------------------------------------------------------------------------
// Local Variables
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Local Function Prototypes
//-------------------------------------------------------------------------------------------------

#if !(defined (MSOS_TYPE_LINUX))
//-------------------------------------------------------------------------------------------------
/// Fill memory area with a constant byte
/// @param  d   \b IN: destination address ptr
/// @param  c   \b IN: constant byte value
/// @param  n   \b IN: # of bytes
/// @return    destination address ptr
//-------------------------------------------------------------------------------------------------
void *UTL_memset( void *d, int c, size_t n )
{
    U8 *pu8Dst = d;
    register U32 u32Cnt = n;
    register U32 u32Val;
    register U32 *pu32Dst;
    register void *vTempD;

    //ASSERT( UTL_CheckDataPtr(pu8Dst) );
    //ASSERT( UTL_CheckDataPtr(pu8Dst+u32Cnt-1) );

    if( n <= 0 )
    {
        return d;
    }

    c &= 0xff;

    while (((U32)pu8Dst & 3)&&(u32Cnt>0))
    {
        *pu8Dst++ = (U8)c;
        u32Cnt--;
    }

    vTempD = pu8Dst;
    pu32Dst = (U32 *)(vTempD);
    u32Val = (c << 24) | (c << 16) | (c << 8) | c;
    while (u32Cnt >= 16)
    {
        *pu32Dst++ = u32Val;
        *pu32Dst++ = u32Val;
        *pu32Dst++ = u32Val;
        *pu32Dst++ = u32Val;
        u32Cnt -= 16;
    }

    while (u32Cnt >= 4)
    {
        *pu32Dst++ = u32Val;
        u32Cnt -= 4;
    }

    pu8Dst = (U8 *)pu32Dst;
    while (u32Cnt)
    {
        *pu8Dst++ = (U8)c;
        u32Cnt--;
    }

    //flush EC's write FIFO
    //__asm__("l.msync");
#if defined (__aeon__)
  #ifdef __AEONR2__
    asm volatile ("l.syncwritebuffer");
  #else
    asm volatile ("l.msync");
  #endif

#elif defined(__mips__)

    MAsm_CPU_Sync();

#elif defined(__arm__)

    MAsm_CPU_Sync();

#endif

    return d;
}

//-------------------------------------------------------------------------------------------------
/// Copy memory areas
/// @param  d   \b IN: destination address ptr
/// @param  s   \b IN: source address ptr
/// @param  n   \b IN: # of bytes
/// @return    destination address ptr
/// @note   d & s had better be 4-byte aligned for performance issue.
//-------------------------------------------------------------------------------------------------
void *UTL_memcpy(void *d, const void *s, size_t n)
{
#if 0//MEM_DEBUG
    int retryTimes;
#endif

    register U8 *pu8Dst = d;
    register const U8 *pu8Src = s;
    register U32 u32Cnt = n;
    register void *vTempD;
    register const void *vTempS;

    //ASSERT( UTL_CheckDataPtr(pu8Dst) );
    //ASSERT( UTL_CheckDataPtr(pu8Src) );
    //ASSERT( UTL_CheckDataPtr(pu8Src+u32Cnt-1) );
    //ASSERT( UTL_CheckDataPtr(pu8Dst+u32Cnt-1) );

    if( n <= 0 )
    {
        return d;
    }

    U32 u32DstAlign = (U32)pu8Dst & 3;
    U32 u32SrcAlign = (U32)pu8Src & 3;

    if ( u32DstAlign == u32SrcAlign )
    {
        //while (u32DstAlign-- && u32Cnt)
        while (  ((U32)pu8Dst & 3) && (u32Cnt>0) )
        {
            *pu8Dst++ = *pu8Src++;
            u32Cnt --;
#if 0//#if MEM_DEBUG
/* Need to re-write debug content. */

            if(((volatile U8 *)u32Dst)[u32I] != ((volatile U8 *)pSrc)[u32I])
            {
                printf("UTL_memcpy err dest=>%x src=>%x\n",((volatile U8 *)u32Dst)[u32I],((volatile U8 *)pSrc)[u32I]);
                for(retryTimes =0; retryTimes < 10; retryTimes++)
                {
                    ((volatile U8 *)u32Dst)[u32I] = ((volatile U8 *)pSrc)[u32I];
                    if(((volatile U8 *)u32Dst)[u32I] == ((volatile U8 *)pSrc)[u32I])
                        break;
                }
                if(retryTimes >= 10)
                    printf("UTL_memcpy retry failed dest=>%x src=>%x\n",((volatile U8 *)u32Dst)[u32I],((volatile U8 *)pSrc)[u32I]);
            }
#endif
        }
    }

    u32DstAlign = (U32)pu8Dst & 3;
    u32SrcAlign = (U32)pu8Src & 3;

    if ( u32DstAlign == 0 && u32SrcAlign == 0)
    {
        register U32 *pu32Dst;
        register const U32 *pu32Src;

        vTempD = pu8Dst;
        vTempS = pu8Src;
        pu32Dst = (U32 *)vTempD;
        pu32Src = (const U32 *)vTempS;

        while (u32Cnt >= 16)
        {
            *pu32Dst++ = *pu32Src++;
            *pu32Dst++ = *pu32Src++;
            *pu32Dst++ = *pu32Src++;
            *pu32Dst++ = *pu32Src++;
            u32Cnt -= 16;
        }

        while (u32Cnt >= 4)
        {
            *pu32Dst++ = *pu32Src++;
            u32Cnt -= 4;
        }

        pu8Dst = (U8*)pu32Dst;
        pu8Src = (const U8*)pu32Src;
        while (u32Cnt--)
        {
            *pu8Dst++ = *pu8Src++;
        }
    }
    else if ( (u32DstAlign == 2 && u32SrcAlign == 0) || (u32DstAlign == 0 && u32SrcAlign == 2) )
    {
        register U16 *pu16Dst;
        register const U16 *pu16Src;

        vTempD = pu8Dst;
        vTempS = pu8Src;
        pu16Dst = (U16 *)vTempD;
        pu16Src = (const U16 *)vTempS;

        while (u32Cnt >= 2)
        {
            *pu16Dst++ = *pu16Src++;
            u32Cnt -= 2;
        }

        pu8Dst = (U8*)pu16Dst;
        pu8Src = (const U8*)pu16Src;
        while (u32Cnt--)
        {
            *pu8Dst++ = *pu8Src++;
        }
    }
    else
    {
        while (u32Cnt--)
        {
            *pu8Dst++ = *pu8Src++;
        }
    }

    //flush EC's write FIFO
#if defined (__aeon__)
#ifdef __AEONR2__
    __asm__("l.syncwritebuffer");
#else
    __asm__("l.msync");
#endif
#else
    MAsm_CPU_Sync();
#endif

    return d;
}

#if 0
//-------------------------------------------------------------------------------------------------
/// Copy memory areas
/// @param  pDst    \b IN: destination address ptr
/// @param  pSrc    \b IN: source address ptr
/// @param  u32Cnt  \b IN: # of bytes
/// @return    destination address ptr
//-------------------------------------------------------------------------------------------------
void *UTL_memcpy_swap(void *pDst, const void *pSrc, U32 u32Cnt)
{
#if MEM_DEBUG
    int retryTimes;
#endif
    register U32 u32I;
    register U32 u32Dst = (U32)pDst;

    //ASSERT( UTL_CheckDataPtr(pDst) );
    //ASSERT( UTL_CheckDataPtr(pSrc) );
    //ASSERT( UTL_CheckDataPtr(pDst+u32Cnt-1) );
    //ASSERT( UTL_CheckDataPtr(pSrc+u32Cnt-1) );

    //note: DMA is used for non-cacheable area only & needs a mutex for hardware resource
    for( u32I=0; u32I<u32Cnt/4; u32I++)
    {
        ((volatile U32 *)u32Dst)[u32I] = CYG_SWAP32(((volatile U32 *)pSrc)[u32I]);
#if MEM_DEBUG
        if(((volatile U32 *)u32Dst)[u32I] != CYG_SWAP32(((volatile U32 *)pSrc)[u32I]))
        {
            printf("UTL_memcpy_swap err dest=>%x src=> %x\n",((volatile U32 *)u32Dst)[u32I],CYG_SWAP32(((volatile U32 *)pSrc)[u32I]));
            for(retryTimes =0; retryTimes < 10; retryTimes++)
            {
                ((volatile U32 *)u32Dst)[u32I] = CYG_SWAP32(((volatile U32 *)pSrc)[u32I]);
                if(((volatile U32 *)u32Dst)[u32I] == CYG_SWAP32(((volatile U32 *)pSrc)[u32I]))
                    break;
            }
            if(retryTimes >= 10)
                printf("UTL_memcpy_swap retry failed dest=>%x => src=> %x\n",((volatile U32 *)u32Dst)[u32I],CYG_SWAP32(((volatile U32 *)pSrc)[u32I]));
        }
#endif
    }
    u32Dst += u32I*4;
    pSrc = (void *)((U32)pSrc + u32I*4);

    for( u32I=0; u32I<u32Cnt%4; u32I++)
    {
        ((volatile U8 *)u32Dst)[u32I] = ((volatile U8 *)pSrc)[u32I];
#if MEM_DEBUG
        if(((volatile U8 *)u32Dst)[u32I] != ((volatile U8 *)pSrc)[u32I])
        {
            printf("UTL_memcpy_swap err dest=> %x src=> %x\n",((volatile U8 *)u32Dst)[u32I],((volatile U8 *)pSrc)[u32I]);
            for(retryTimes =0; retryTimes < 10; retryTimes++)
            {
                ((volatile U8 *)u32Dst)[u32I] = ((volatile U8 *)pSrc)[u32I];
                if(((volatile U8 *)u32Dst)[u32I] == ((volatile U8 *)pSrc)[u32I])
                    break;
            }
            if(retryTimes >= 10)
                printf("UTL_memcpy_swap retry failed dest=>%x src=> %x\n",((volatile U8 *)u32Dst)[u32I],((volatile U8 *)pSrc)[u32I]);
        }
#endif
    }

    return pDst;

}
#endif

//-------------------------------------------------------------------------------------------------
/// Appends source string to destination string
/// @param  pStrDst    \b IN: destination string
/// @param  pStrSrc    \b IN: source string
/// @return destination string
//-------------------------------------------------------------------------------------------------
char* UTL_strcat(char *pStrDst, const char *pStrSrc)
{
    char *pStr = (char *)pStrDst;
    while(*pStr != '\0')
    {
        pStr++;
    }

    UTL_strcpy (pStr, pStrSrc);
    return pStrDst;
}

char *UTL_strchr(const char *string,int chr)
{
    const char *pStr = string;

    while(*pStr)
    {
        if(*pStr == chr)
        {
            return (char *)(pStr);
        }
        pStr++;
    }
    return 0;
}

U16 *UTL_wcschr(const U16 *string,int chr)
{
    U16 *pStr = (U16 *)string;

    while(*pStr)
    {
        if(*pStr == chr)
        {
            return (pStr);
        }
        pStr++;
    }
    return 0;
}

char *UTL_strrchr(const char *string,int chr)
{
    char *start = (char *)string;

    while(*string++)
    ;

    while (--string != start && *string != chr)
    ;

    if(*string == chr)
        return((char *)string);

    return (NULL);
}

U16 *UTL_wcsrchr (const U16 *string,U16 ch)
{
    U16 *start = (U16 *)string;

    while (*string++)
    ;

    while (--string != start && *string != (U16)ch)
    ;

    if (*string == (U16)ch)
        return( (U16 *)string );

    return(NULL);
}

int UTL_strcmp(const char *string1, const char *string2)
{
    int iRet, i;

    i = 0;
    while(string1[i] || string2[i])
    {
        iRet = string1[i] - string2[i];
        if(iRet)
        {
            return iRet;
        }
        i++;
    }
    return 0;
}

int UTL_wcscmp(const U16 *string1, const U16 *string2)
{
    int iRet, i;

    i = 0;
    while(string1[i] || string2[i])
    {
        iRet = string1[i] - string2[i];
        if(iRet)
        {
            return iRet;
        }
        i++;
    }
    return 0;
}

int UTL_strncmp( const char *string1, const char *string2, size_t count )
{
    int iRet, i;

    for(i=0;i<(int)count;i++)
    {
        iRet = string1[i] - string2[i];
        if(iRet)
        {
            return iRet;
        }
    }
    return 0;
}

int UTL_wcsncmp( const U16 *string1, const U16 *string2, int count )
{
    int iRet, i;

    for(i=0;i<count;i++)
    {
        iRet = string1[i] - string2[i];
        if(iRet)
        {
            return iRet;
        }
    }
    return 0;
}

int UTL_isprint(int c)
{
    if(c >= ' ' && c <= '~')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int UTL_isspace(int c)
{
    if((c >= 0x09 && c <= 0x0d) || (c == ' '))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

char *UTL_skipspace(const char *pInStr)
{
    char *p = (char*)pInStr;

    while(UTL_isspace(p[0]))
    {
        p++;
    }
    return p;
}

int UTL_isalnum(int c)
{
    if((c >= '0' && c<= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int UTL_isdigit(int c)
{
    if(c >= '0' && c<= '9')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int UTL_isxdigit(int c)
{
    if( (c >= '0' && c<= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f') )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int UTL_tolower(int c)
{
    if( c >= 'A' && c <= 'Z' )
    {
        c = 'a' + (c - 'A');
    }
    return c;
}

int UTL_toupper(int c)
{
    if( c >= 'a' && c <= 'z' )
    {
        c = 'A' + (c - 'a');
    }
    return c;
}


char *UTL_strcpy(char *strDst, const char *strSrc)
{
    int i;

    for(i=0;strSrc[i];i++)
    {
        strDst[i] = strSrc[i];
    }
    strDst[i] = '\0';
    return strDst;
}

#if 0 //FIX ME!!
U16 *UTL_wcscpy(U16 *strDst, const U16 *strSrc)
{
    int i;

    for(i=0;strSrc[i];i++)
    {
        strDst[i] = strSrc[i];
    }
    strDst[i] = '\0';
    return strDst;
}
#endif

size_t UTL_strlen(const char *pStr)
{
    size_t i=0;

    while(pStr[i])
    {
        i++;
    }
    return i;
}

int UTL_wcslen(const U16 *pStr)
{
    int i=0;

    while(pStr[i])
    {
        i++;
    }
    return i;
}

char *UTL_strncpy( char *strDest, const char *strSource, size_t count )
{
    size_t i;

    for(i=0;i<count;i++)
    {
        strDest[i] = strSource[i];
    }
    return strDest;
}

U16 *UTL_wcsncpy( U16 *strDest, const U16 *strSource, int count )
{
    int i;

    for(i=0;i<count;i++)
    {
        strDest[i] = strSource[i];
    }
    return strDest;
}


char *UTL_strupr(char *string)
{
    int i=0;

    while(string[i])
    {
        if(string[i] >= 'a' && string[i] <= 'z')
        {
            string[i] += ('A' - 'a');
        }
        i++;
    }
    return (string);
}

U16 *UTL_wcsupr(U16 *string)
{
    int i=0;

    while(string[i])
    {
        if(string[i] >= 'a' && string[i] <= 'z')
        {
            string[i] += ('A' - 'a');
        }
        i++;
    }
    return (string);
}


//-------------------------------------------------------------------------------------------------
/// Scan a variable argument list from a string
/// @param  pInStr  \b IN: input string
/// @param  pFmt    \b IN: format string
/// @param  ap     \b IN: ...
/// @return # of input items assigned
//-------------------------------------------------------------------------------------------------
int UTL_vsscanf(const char *pInStr, const char *pFmt, va_list ap)
{
    char *pStrCur = (char*)pInStr;
    char *pFmtCur = (char*)pFmt;
    char cChar;
    enumStdFuncState eState = E_STD_NORMAL;
    U32 u32Val ;
    BOOL bMinus;
    char *pVal;
    int iFieldWidth = SPRINTF_FIELD_MAX;
    int iFieldScanned=0;

    while((eState != E_STD_ERROR) && ((cChar = pFmtCur[0]) || (eState != E_STD_NORMAL)))
    {
        switch(eState)
        {
        case E_STD_NORMAL:
            if(cChar == '%')
            {
                eState = E_STD_FROMAT;
                pFmtCur++;
            }
            else if(UTL_isspace(cChar))
            {
                pFmtCur = UTL_skipspace(pFmtCur);
                pStrCur = UTL_skipspace(pStrCur);
            }
            else
            {
                if(cChar == pStrCur[0])
                {
                    pStrCur++;
                    pFmtCur++;
                }
                else
                {
                    eState = E_STD_ERROR;
                }
            }
            break;

        case E_STD_FROMAT:
            if(UTL_isdigit(cChar))  // Process the field width.
            {
                iFieldWidth = 0;
                while(UTL_isdigit(pFmtCur[0]))
                {
                    iFieldWidth  = iFieldWidth*10 + UTL_charToInt(pFmtCur[0]);
                    pFmtCur++;
                }
            }
            else
            {
                iFieldWidth = SPRINTF_FIELD_MAX;    // Set a large number for free run.
            }
            switch(pFmtCur[0])
            {
            case 'x':
            case 'X':
                eState = E_STD_HEX;
                pFmtCur++;
                break;
            case 'd':
                eState = E_STD_DEC;
                pFmtCur++;
                break;
            case 's':
                eState = E_STD_STRING;
                pFmtCur++;
                break;
            default:
                eState = E_STD_ERROR;
                break;
            }
            break;

        case E_STD_HEX:
            u32Val = 0;
            pStrCur = UTL_skipspace(pStrCur);
            while(UTL_isalnum(pStrCur[0]) && (iFieldWidth > 0))
            {
                u32Val  = u32Val*16 + UTL_charToInt(pStrCur[0]);
                pStrCur++;
                iFieldWidth--;
            }
            *va_arg(ap, U32 *) = (U32)u32Val;
            iFieldScanned++;
            eState = E_STD_NORMAL;
            break;

        case E_STD_DEC:
            u32Val = 0;
            pStrCur = UTL_skipspace(pStrCur);
            bMinus = false;
            if(pStrCur[0] == '-')
            {
                bMinus = true;
                pStrCur++;
            }
            while(UTL_isdigit(pStrCur[0]) && (iFieldWidth > 0))
            {
                u32Val  = u32Val*10 + UTL_charToInt(pStrCur[0]);
                pStrCur++;
                iFieldWidth--;
            }
            if(bMinus)
            {
                *va_arg(ap, int *) = -((int)u32Val);
            }
            else
            {
                *va_arg(ap, int *) = (int)u32Val;
            }
            iFieldScanned++;
            eState = E_STD_NORMAL;
            break;

        case E_STD_STRING:
            pVal = va_arg(ap, char *);
            pStrCur = UTL_skipspace(pStrCur);
            while(!UTL_isspace(pStrCur[0]) && (iFieldWidth > 0) && pStrCur[0])
            {
                pVal[0] = pStrCur[0];
                pVal++;
                pStrCur++;
                iFieldWidth--;
            }
            pVal[0] = '\0';
            iFieldScanned++;
            eState = E_STD_NORMAL;
            break;

        default:
            eState = E_STD_ERROR;
            break;
        }
    }

    return iFieldScanned;
}


//-------------------------------------------------------------------------------------------------
/// Scan input string according to the format
/// @param  pInStr  \b IN: input string
/// @param  pFmt    \b IN: format string
/// @param  ...     \b IN: ...
/// @return # of input items assigned
//-------------------------------------------------------------------------------------------------
int UTL_sscanf(const char *pInStr, const char *pFmt, ...)
{
    int ir;
    va_list ap;

    va_start(ap, pFmt);
    ir = UTL_vsscanf(pInStr, pFmt, ap);
    va_end(ap);
    return ir;
}

#endif //MSOS_TYPE_LINUX

int UTL_charToInt(char c)
{
    if(c >= '0' && c<= '9')
    {
        return (c - '0');
    }
    else if(c >= 'A' && c <= 'F')
    {
        return (10 + (c - 'A'));
    }
    else if(c >= 'a' && c <= 'f')
    {
        return (10 + (c - 'a'));
    }
    return -1;
}

int UTL_U32ToHexStr(U32 u32Val, char *pOutStr)
{
    #define MASK_4BIT   0xf0000000
    int i;
    U32 u32OneDigit;
    int iOutStrCnt=0;
    BOOL bBegin=false;

    if(u32Val == 0)
    {
        pOutStr[0] = '0';
        pOutStr[1] = '\0';
        iOutStrCnt = 1;
    }
    else
    {
        for(i=0;i<8;i++)
        {
            u32OneDigit = (u32Val & (MASK_4BIT>>(i*4))) >> (28 - (i * 4));
            if(u32OneDigit)
            {
                bBegin = true;
            }
            if(bBegin)
            {
                if(u32OneDigit <= 9)
                {
                    pOutStr[iOutStrCnt++] = (char)('0' + u32OneDigit);
                }
                else
                {
                    pOutStr[iOutStrCnt++] = (char)('A' + (u32OneDigit - 10));
                }
            }
        }
    }

    return iOutStrCnt;
}

int UTL_IntToDecStr(int iVal, char *pOutStr)
{
    int i;
    int iOutStrCnt=0;
    U32 u32Val;
    U32 uTmp;
    char strTmp[16];
    int iStrTmpIdx;

    if(iVal == 0)
    {
        pOutStr[0] = '0';
        pOutStr[1] = '\0';
        iOutStrCnt = 1;
    }
    else
    {
        if(iVal < 0)
        {
            pOutStr[iOutStrCnt++] = '-';
            u32Val = (U32)-iVal;
        }
        else
        {
            u32Val = (U32)iVal;
        }

        uTmp = u32Val;
        iStrTmpIdx = 0;
        while(uTmp)
        {
            strTmp[iStrTmpIdx++] = (char)('0' + (uTmp % 10));
            uTmp /= 10;
        }
        // Reorder the output.
        for(i=0;i<iStrTmpIdx;i++)
        {
            pOutStr[iOutStrCnt++] = strTmp[iStrTmpIdx-i-1];
        }
    }

    return iOutStrCnt;
}

U16 *UTL_wcscpy(U16 *strDst, const U16 *strSrc)
{
    int i;

    for(i=0;strSrc[i];i++)
    {
        strDst[i] = strSrc[i];
    }
    strDst[i] = '\0';
    return strDst;
}
