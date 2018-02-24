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

#define IOUTIL

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "datatype.h"
#include "IOUtil.h"

#undef IOUTIL

/***************************************************************************************/

/*###############################################################################################*/
/*///////////////////////////////// Utilities API - String //////////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
///
/// @param -
/// @return -
/***************************************************************************************/
void ByteSwapCopy(U8 *pu8DesBuffer, U8 *pu8SrcBuffer, U16 TotalByte)
{
    U16 ByteNo;

    for(ByteNo = 0; ByteNo < TotalByte; ByteNo++)
    {
        pu8DesBuffer[ByteNo] = pu8SrcBuffer[TotalByte-ByteNo-1];
    }
}

/***************************************************************************************/
///
/// @param -
/// @return -
/***************************************************************************************/
void ByteCopy(U8 *pu8DesBuffer, U8 *pu8SrcBuffer, U16 TotalByte)
{
    U16 ByteNo;

    for(ByteNo = 0; ByteNo < TotalByte; ByteNo++)
    {
        pu8DesBuffer[ByteNo] = pu8SrcBuffer[ByteNo];
    }
}

/***************************************************************************************/
///
/// @param -
/// @return -
/***************************************************************************************/
S8 ByteComp(U8 *pu8DesBuffer, U8 *pu8SrcBuffer, U16 TotalByte)
{
    U16 ByteNo;

    for(ByteNo = 0; ByteNo < TotalByte; ByteNo++)
    {
        if(pu8DesBuffer[ByteNo] != pu8SrcBuffer[ByteNo])
        {
            return -1;
        }
    }
    return 0;
}

/***************************************************************************************/
///
/// @param -
/// @return -
/***************************************************************************************/
char *msStrcat(char *pDst, const char *pSrc)
{
    U16 i, j;

    for(i=0; pDst[i]; i++);
    for(j=0; pSrc[j]; j++)
    {
        pDst[i+j] = pSrc[j];
    }
    return pDst;
}

/***************************************************************************************/
///
/// @param -
/// @return -
/***************************************************************************************/
char *msStrncpy(char *pDst, const char *pSrc, U16 u16Len)
{
    U16 i;

    for(i=0; i<u16Len; i++)
    {
        pDst[i] = pSrc[i];
    }
    pDst[i] = '\0';
    return pDst;
}

/***************************************************************************************/

/*###############################################################################################*/
/*////////////////////////////////// Utilities API - Path ///////////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
///
/// @param -
/// @return -
/***************************************************************************************/
void SplitPath(S8 *ps8PathName, S8 *ps8DirName, S8 *ps8FileName)
{
    S8 *ps8DirStart, *ps8DirEnd;

    /*[01]initial =====================================================================*/
    *ps8DirName  = '\0';
    *ps8FileName = '\0';
    ps8DirStart  = ps8PathName;
    ps8DirEnd    = ps8PathName;

    /*[02]get dir name ================================================================*/
    /*[02-1]go to last '\\' to get DirEnd =============================================*/
    while((ps8DirEnd = (S8 *)strchr((const char *)ps8PathName, '\\')) != NULL)    //Find '\\' in the PathName
    {
        ps8PathName = (ps8DirEnd + 1);
    }

    /*[02-2]get DirName ===============================================================*/
    memcpy(ps8DirName, ps8DirStart, ps8PathName - ps8DirStart);
    ps8DirName[ps8PathName - ps8DirStart] = '\0';

    /*[03]get file name ===============================================================*/
    while(*ps8PathName != '\0')
    {
        *ps8FileName++ = *ps8PathName++;
    }
    *ps8FileName = '\0';
}

/***************************************************************************************/
///
/// @param -
/// @return -
/***************************************************************************************/
U8 IsFullPath(S8 *ps8PathName)
{
    if(*ps8PathName == '\\')
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/***************************************************************************************/
/*###############################################################################################*/
/*/////////////////////////////////// Unicode API - Path ////////////////////////////////////////*/
/*###############################################################################################*/
/***************************************************************************************/
U8 UnicodeCmp(S8 *ps8LongName1, S8 *ps8LongName2)
{
    while(TRUE)
    {
        if(((*ps8LongName1 == '\0') && (*(ps8LongName1+1) == '\0')) &&
           ((*ps8LongName2 == '\0') && (*(ps8LongName2+1) == '\0')))
        {
            return TRUE;
        }

        if((*ps8LongName1 != *ps8LongName2) || (*(ps8LongName1+1) != *(ps8LongName2+1)))
        {
            return FALSE;
        }

        ps8LongName1 += 2;
        ps8LongName2 += 2;
    }
}

/***************************************************************************************/
void UnicodeCat(S8 *ps8DesName, S8 *ps8SrcName)
{
    /*[01]move to end of string =======================================================*/
    while(TRUE)
    {
        if((*ps8DesName == '\0') && (*(ps8DesName + 1) == '\0'))
        {
            break;
        }
        ps8DesName += 2;
    }

    /*[02]catenate two string =========================================================*/
    while(TRUE)
    {
        if((*ps8SrcName == '\0') && (*(ps8SrcName + 1) == '\0'))
        {
            break;
        }
        *ps8DesName++ = *ps8SrcName++;
        *ps8DesName++ = *ps8SrcName++;
    }
    *ps8DesName++ = '\0';
    *ps8DesName++ = '\0';
}

void UnicodeCat2(S8 *ps8DesName, S8 *ps8SrcName, U8 u8NameLength)
{
    U8 i=0;
    /*[01]move to end of string =======================================================*/
    while(TRUE)
    {
        if((*ps8DesName == '\0') && (*(ps8DesName + 1) == '\0'))
        {
            break;
        }
        ps8DesName += 2;
    }

    /*[02]catenate two string =========================================================*/
    while(TRUE)
    {
        if((*ps8SrcName == '\0') && (*(ps8SrcName + 1) == '\0'))
        {
            break;
        }
        *ps8DesName++ = *ps8SrcName++;
        *ps8DesName++ = *ps8SrcName++;

        i++;
        if (i > u8NameLength)
        {
            break;
        }
    }
    *ps8DesName++ = '\0';
    *ps8DesName++ = '\0';
}

/***************************************************************************************/
U8 UnicodeLen(S8 *ps8PathName)
{
    U8 u8StringLength = 0;

    while(TRUE)
    {
        if((*ps8PathName == '\0') && (*(ps8PathName+1) == '\0'))
        {
            break;
        }
        ps8PathName += 2;
        u8StringLength++;
    }
    return u8StringLength;
}

/***************************************************************************************/
S8 *UnicodeChr(S8 *ps8PathName, S8 s8Chr)
{
    while(TRUE)
    {
        if((*ps8PathName == '\0') && (*(ps8PathName+1) == '\0'))
        {
            return NULL;
        }
        else if((*ps8PathName == '\0') && (*(ps8PathName+1) == s8Chr))
        {
            return ps8PathName;
        }
        ps8PathName += 2;
    }
}

/***************************************************************************************/
void UnicodeCpy(S8 *ps8DesName, S8 *ps8SrcName)
{
    while(TRUE)
    {
        if((*ps8SrcName == '\0') && (*(ps8SrcName + 1) == '\0'))
        {
            break;
        }
        *ps8DesName++ = *ps8SrcName++;
        *ps8DesName++ = *ps8SrcName++;
    }
    *ps8DesName++ = '\0';
    *ps8DesName++ = '\0';
}

void UnicodeCpy2(S8 *ps8DesName, S8 *ps8SrcName, U8 u8NameLength)
{
    U8 i=0;
    while(TRUE)
    {
        if((*ps8SrcName == '\0') && (*(ps8SrcName + 1) == '\0'))
        {
            break;
        }
        *ps8DesName++ = *ps8SrcName++;
        *ps8DesName++ = *ps8SrcName++;

        i++;
        if (i > u8NameLength - 1)
        {
            break;
        }
    }
    *ps8DesName++ = '\0';
    *ps8DesName++ = '\0';
}

/***************************************************************************************/
void UnicodeSplitPath(S8 *ps8PathName, S8 *ps8DirName, S8 *ps8FileName)
{
    S8 *ps8DirStart, *ps8DirEnd;

    /*[01]initial =====================================================================*/
    *ps8DirName  = '\0';
    *ps8FileName = '\0';
    ps8DirStart  = ps8PathName;
    ps8DirEnd    = ps8PathName;

    /*[02]get dir name ================================================================*/
    /*[02-1]go to last '\\' to get DirEnd =============================================*/
    while(TRUE)
    {
        if((*ps8DirEnd == '\0') && (*(ps8DirEnd + 1) == '\0'))
        {
            break;
        }

        if((*ps8DirEnd == '\0') && (*(ps8DirEnd + 1) == '\\'))
        {
            ps8PathName = ps8DirEnd + 2;
        }
        ps8DirEnd += 2;
    }

    /*[02-2]get DirName ===============================================================*/
    memcpy(ps8DirName, ps8DirStart, ps8PathName - ps8DirStart);
    ps8DirName[ps8PathName - ps8DirStart] = '\0';
    ps8DirName[ps8PathName - ps8DirStart + 1] = '\0';

    /*[03]get file name ===============================================================*/
    while(TRUE)
    {
        if((*ps8PathName == '\0') && (*(ps8PathName + 1) == '\0'))
        {
            break;
        }
        *ps8FileName++ = *ps8PathName++;
        *ps8FileName++ = *ps8PathName++;
    }
    *ps8FileName++ = '\0';
    *ps8FileName++ = '\0';
}

/***************************************************************************************/
U8 UnicodeIsFullPath(S8 *ps8PathName)
{
    if((*ps8PathName == '\0') && (*(ps8PathName + 1) == '\\'))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/***************************************************************************************/
void UnicodetoASCII(S8 *ps8FileName)
{
    S8 *ps8String = ps8FileName;

    while(TRUE)
    {
        if((*ps8String == '\0') && (*(ps8String + 1) == '\0'))
        {
            *ps8FileName = '\0';
            ps8FileName++;
            return;
        }
        else if(*ps8String == '\0')
        {
            *ps8FileName = *(ps8String + 1);
            ps8FileName++;
        }
        else
        {
            *ps8FileName = *ps8String;
            ps8FileName++;
            *ps8FileName = *(ps8String + 1);
            ps8FileName++;
        }
        ps8String += 2;
    }
}

/***************************************************************************************/
void ASCIItoUnicode(S8 *ps8FileName)
{
    U8 u8FileLength;

    u8FileLength = strlen((const char *)ps8FileName);
    *(ps8FileName+(u8FileLength*2)+1) = '\0';
    *(ps8FileName+(u8FileLength*2)) = '\0';
    u8FileLength--;

    for(; (S8)u8FileLength >= 0; u8FileLength--)
    {
        *(ps8FileName+(u8FileLength*2)+1) = *(ps8FileName+u8FileLength);
        *(ps8FileName+(u8FileLength*2)) = '\0';
    }

    return;
}

void ASCIItoUnicode2(S8 *ps8FileName,U8 len)
{
    S16 s16FileLength;

    s16FileLength=(S16)(len-1);

    for(; s16FileLength >= 0; s16FileLength--)
    {
        *(ps8FileName+(s16FileLength*2)) = *(ps8FileName+s16FileLength);
        *(ps8FileName+(s16FileLength*2)+1) = '\0';
    }

    return;
}


void strupr2(U8 *pu8Str,U8 len)                        //convert to upper case
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

