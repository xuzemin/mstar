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
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// @file
// @brief
// @author MStarSemi Inc.
//
//-
//-
//
////////////////////////////////////////////////////////////////////////////////

#define FS_UTIL_C
#include <stdlib.h>

#include "datatype.h"
#include "msAPI_FSCommon.h"
#include "FSUtil.h"

//[For LL_LongDivU32()
#undef  LENGTH_OF_U32_TYPE
#define LENGTH_OF_U32_TYPE  (8*sizeof(U32))
#define HALF_OF_LENGTH     ( LENGTH_OF_U32_TYPE >> 1 )
#define NOT_HALF_OF_LENGTH ( ~((~0) << HALF_OF_LENGTH) )
//]

/***************************************************************************************/
U8 FS_strlen_U(U16 *pu16String)
{

    U8 count=0;
    while(count<255)
    {
        if(pu16String[count]==0)
        {
            return count;
        }
        count++;
    }
    return 0;
}

/***************************************************************************************/
void FS_ByteSwapCopy(U8 *pu8DesBuffer, U8 *pu8SrcBuffer, U16 TotalByte)
{
    U16 ByteNo;

    for(ByteNo=0; ByteNo<TotalByte; ByteNo++)
    {
        pu8DesBuffer[ByteNo]=pu8SrcBuffer[TotalByte-ByteNo-1];
    }
}

/***************************************************************************************/
void FS_strupr2(U8 *pu8Str,U8 len)                        //convert to upper case
{
    U8 count=0;
    while((*pu8Str != '\0')&&(count<len))
    {
        if((*pu8Str >= 'a') && (*pu8Str <= 'z'))
        {
            *pu8Str -= 'a' - 'A';
        }
        pu8Str++;
        count++;
    }
}


/***************************************************************************************/
void FS_Unicode2ASCII(U16 *pu16FileName)
{

    U8 len=0;
    U8 i=0;

    for(i=0;i<255;i++)
    {
        if(pu16FileName[i]==0)
        {
            len=i;
            break;
        }
    }

    for(i=0;i<len;i++)
    {
        ((U8*)pu16FileName)[i]=(U8)pu16FileName[i];
    }

    if(len>0)
    {
        ((U8*)pu16FileName)[len]=0;
    }
}

/***************************************************************************************/
void FS_ASCII2Unicode(U8 *pu8FileName)
{
    U8 len=0;
    U8 i=0;

    for(i=0;i<255;i++)
    {
        if(pu8FileName[i]==0)
        {
            len=i;
            break;
        }
    }

    for(i=0;i<len;i++)
    {
        //((U16*)pu8FileName)[len-1-i]=pu8FileName[len-1-i];
        pu8FileName[(len-1-i)*2]=pu8FileName[len-1-i];
        pu8FileName[(len-1-i)*2+1]=0;
    }

    if(len>0)
    {
        //((U16*)pu8FileName)[len]=0;
        pu8FileName[len*2]=0;
        pu8FileName[len*2+1]=0;
    }
}

/***************************************************************************************/


BOOLEAN FS_strequal_U(U16 *pu16LongName1, U16 *pu16LongName2)
{
    U16 guard=0;
    while(TRUE)
    {
        if(*pu16LongName1==0&&*pu16LongName2==0)
        {
            return TRUE;
        }

        if(*pu16LongName1 != *pu16LongName2)
        {
            return FALSE;
        }

        pu16LongName1 ++;
        pu16LongName2 ++;

        guard++;
        if(guard==0xFFFF)
        {
            return FALSE;
        }
    }
}

void LL_assign(LongLong* pX,U32 val)
{
    pX->Hi=0;
    pX->Lo=val;
}

BOOLEAN FS_IsPowerOf2(U32 num)
{
    U32 n=1;
    U8 i=0;
    if(num==0)
    {
        return FALSE;
    }

    for(i=0;i<32;i++)
    {
        n=(1L<<i);

        if((num&n) >0 && (num & (~n))==0)
        {
            return TRUE;
        }

    }
    return FALSE;
}

S32 FS_Log2( S32 val )
{
     register S32 ret = 0;

     while (val >> ++ret);

     if ((1 << --ret) < val)
          ret++;

     return ret;
}

LongLong LL_add(LongLong* pLongLong,U32 val)
{
    LongLong l;
    U32 lo;

    l=*pLongLong;

    lo=l.Lo;
    l.Lo+=val;
    if(lo>l.Lo)
    {
        l.Hi+=1;
    }
    return l;


}

LongLong LL_add_signed(LongLong* pLongLong,S32 val)
{
    if(val<0)
    {
        return LL_subtract(pLongLong,(U32)abs(val));
    }
    else
    {
        return LL_add(pLongLong,(U32)val);
    }
}

LongLong LL_addLong(LongLong* pX,LongLong* pY)
{
    LongLong l;
    U32 lo;

    l=*pX;

    lo=l.Lo;
    l.Lo+=pY->Lo;
    l.Hi+=pY->Hi;
    if(lo>l.Lo)
    {
        l.Hi+=1;
    }
    return l;


}

LongLong LL_subtract(LongLong* pLongLong,U32 val)
{
    LongLong l;
    U32 lo;
    l=*pLongLong;
    lo=l.Lo;
    l.Lo-=val;
    if(lo<l.Lo)
    {
        l.Hi-=1;
    }
    return l;
}

LongLong LL_subtractLong(LongLong *pX, LongLong *pY)
{
    LongLong l ;
    l= *pX;
    l.Lo -= pY->Lo;
    l.Hi -= pY->Hi;
    if(l.Lo > pX->Lo)
        -- l.Hi;
    return l;
}


BOOLEAN LL_iszero(LongLong *pX)
{

    return ((pX->Hi | pX->Lo) == 0);
}

BOOLEAN LL_equal(LongLong* pX,LongLong* pY)
{
    return (pX->Lo==pY->Lo) && (pX->Hi==pY->Hi);
}

BOOLEAN LL_greater(LongLong* pX,LongLong* pY)
{
    if(pX->Hi == pY->Hi)
        return (pX->Lo > pY->Lo);
    else
        return (pX->Hi > pY->Hi);
}

BOOLEAN LL_greater_or_equal(LongLong* pX,LongLong* pY)
{
    if(pX->Hi == pY->Hi)
        return (pX->Lo >= pY->Lo);
    else
        return (pX->Hi > pY->Hi);
}


LongLong LL_rshift(LongLong* pX,U8 count)
{
    LongLong result;

    if(count==0)
    {
        result.Hi=pX->Hi;
        result.Lo=pX->Lo;
    }
    else if(count<32)
    {
        result.Hi = (pX->Hi>>count);
        result.Lo = (pX->Lo>>count)|((((1<<count)-1)&pX->Hi)<<(32-count));

    }
    else
    {
        result.Hi=0;
        result.Lo=(pX->Hi>>(count-32));
    }
    return result;
}

LongLong LL_multU32(U32 x, U32 y){
    LongLong retval;
    U32 mid;            // middle two words
    U32 ad, bc;

    // generate partial products
    retval.Hi = (U32)((x>>16) * (y>>16));                // ac
    ad  = (U32)((x>>16) * ((y<<16)>>16));               // ad
    bc  = (U32)( ((x<<16)>>16) * (y>>16));              // bc
    retval.Lo = (U32)(((x<<16)>>16) * ((y<<16)>>16));    // bd

    mid = ad +  (retval.Lo>>16) ;        // ad, high half of bd
    if(mid < ad)                  // if carry,
        retval.Hi += 1;           // bump high word
    mid += bc;                   // all of bc
    if(mid < bc)                  // if carry,
        retval.Hi += 0x00010000;// bump high word

    // results into place
    retval.Hi = retval.Hi + (mid>>16);        // mid.hi to hi.lo
    retval.Lo = ((retval.Lo<<16)>>16) + (mid<<16);            // mid.lo to lo.hi
    return retval;
}

LongLong LL_LongMultU32(LongLong *pLongLong, U32 y){
    LongLong retval, lLo;

    lLo = LL_multU32(pLongLong->Lo, y);
    retval = LL_multU32(pLongLong->Hi, y);
    retval.Hi = retval.Lo + lLo.Hi;
    retval.Lo = lLo.Lo;
    return retval;
}

#if 0
LongLong LL_mult(LongLong *pX, U32 val)
{
    LongLong retval;
    LongLong ac;
    LongLong bc;
    ac = LL_multU32(pX->Hi,val);
    bc = LL_multU32(pX->Lo,val);
    retval.Lo = bc.Lo;
    retval.Hi = ac.Lo+bc.Hi;
    return retval;
}
#endif

LongLong LL_LongDivU32(LongLong* x, U32 y)
{
    LongLong result;

    U32 k = x->Hi % y;
    result.Hi = x->Hi / y;

    if (k > 0)
    {
        U32 q = (y>>1);
        U32 sh = 1;

        while (q > 0)
        {
            sh = sh + 1;
            q = q>>1;
        }

        if (sh > HALF_OF_LENGTH)
        {
            U32 sh2 = 1;
            LongLong  T,N;

            N.Hi = k;
            N.Lo = x->Lo;
            for (q = (k>>1); q > 0; q >>= 1)
                sh2 = sh2 + 1;

            sh = sh - (sh2 - 1);
            T.Hi = y >> sh;

            sh = LENGTH_OF_U32_TYPE - sh;
            T.Lo = (y << sh);
            result.Lo = (1 << sh);
            N = LL_subtractLong(&N, &T);
            q = result.Lo;

            while (LL_greater_or_equal(&N, &T))
            {
                N = LL_subtractLong(&N, &T);
                result.Lo = result.Lo + q;
            }

            while (N.Hi > 0)
            {
                q >>= 1;
                T = LL_rshift(&T, 1);
                if (LL_greater_or_equal(&N, &T))
                {
                    N = LL_subtractLong(&N, &T);
                    result.Lo |= q;
                }
            }
        result.Lo = result.Lo + (N.Lo / y);
        }
        else
        {
            k = (k << HALF_OF_LENGTH) | (x->Lo >> HALF_OF_LENGTH);
            q = ((k/y) << HALF_OF_LENGTH);
            k = ((k%y) << HALF_OF_LENGTH);
            k |= (x->Lo & NOT_HALF_OF_LENGTH );
            result.Lo = (q | (k/y));
        }
    }
    else
    {
        result.Lo = x->Lo / y;
    }

    return result;
}

