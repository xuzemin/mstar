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

#define MAPP_ZUI_APISTRINGS_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


#include <stdlib.h>
#include <string.h>
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "MApp_ZUI_APItables.h"
#include "MApp_ZUI_ACTglobal.h"
#include "MApp_GlobalVar.h"

#include "OSDcp_readbin.h" //for OSDcp_readbin_string_ptr()
#include "MApp_GlobalSettingSt.h" //for GET_OSD_MENU_LANGUAGE()
#include "MApp_GlobalFunction.h" //for MApp_GetMenuLanguage()
#include "MApp_RestoreToDefault.h"
#include "OSDcp_String_EnumIndex.h" //for LANG_PAGE_MAX

/*/ ZUI: use MApp_ZUI_API_Strlen()
///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_U16StringCopy
///  get a string pointer from a U16 integer
///  NOTE: assume input string is located in XDATA!
///
///  @param [in]        str LPTSTR   source string buffer
///
///  @return U16  string length
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
U16 MApp_ZUI_API_U16StringLength (LPTSTR str)
{
    U16 len = 0;
    while (str[len])
    {
        len++;
    }
    return len;
}*/

/*/ ZUI: use MApp_ZUI_API_Strcpy()
///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_U16StringCopy
///  get a string pointer from a U16 integer
///  NOTE: assume input string is located in XDATA!
///
///  @param [out]       dest LPTSTR   dest string buffer
///  @param [in]        src LPTSTR   source string buffer
///
///  @return U16  string length
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
U16 MApp_ZUI_API_U16StringCopy (LPTSTR dest, LPTSTR src)
{
    U16 len = 0;
    while (src[len])
    {
        dest[len] = src[len];
        len++;
    }
    dest[len] = 0;
    return len;
}*/

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_StringBuffU8toU16
///  Transform U8 string to U16 string. Mainly for ZUI OSD display.
///    (always return CHAR_BUFFER[])
///  NOTE: assume input string is located in XDATA!
///
///  @param [in]       pStrDest U16*  => Destination of string
///  @param [in]       pStrSource U8*  => content of string
///  @param [in]       u16Length U16  => length of string
///
///  @return LPTSTR   pStrDest
///
///  @author MStarSemi @date 2008/3/6
///////////////////////////////////////////////////////////////////////////////
LPTSTR MApp_ZUI_API_StringBuffU8toU16(LPTSTR pStrDest, U8* pStrSource, U16 u16Length)
{
    {
        U16 i;
        for (i = 0; i<=u16Length; i++)
        {
            (pStrDest)[i] = pStrSource[i];
            if((pStrDest)[i]==0)
                break;
        }
    }
    return pStrDest;
}



///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_GetString
///  get a string pointer from string ID, used for localization data.
///    (always return CHAR_BUFFER[])
///
///  @param [in]       id U16     string ID
///
///  @return LPTSTR string content
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
LPTSTR MApp_ZUI_API_GetString(U16 id)
{
    U8 u8Language = GET_OSD_MENU_LANGUAGE();

    if (id >= E_ZUI_STR_MAX) //check numbers of strings
        id = 0;

    OSDcp_readbin_string_ptr(u8Language, id, (U16*)CHAR_BUFFER);

    return CHAR_BUFFER;
}


///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_GetStringSpecificLanguage
///  get a string pointer from string ID with specific language, used for localization data.
///    (always return CHAR_BUFFER[])
///
///  @param [in]       id U16     string ID
///  @param [in]       u8Language U8     language ID
///
///  @return LPTSTR string content
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
LPTSTR MApp_ZUI_API_GetStringSpecificLanguage(U16 id, U8 u8Language)
{

    if (u8Language >= LANG_PAGE_MAX) //check numbers of language
        u8Language = 0;
    if (id >= E_ZUI_STR_MAX) //check numbers of strings
        id = 0;

    OSDcp_readbin_string_ptr(u8Language, id, (U16*)CHAR_BUFFER);

    return CHAR_BUFFER;
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_LoadString
///  get a string pointer from string ID, used for localization data
///   (load to user private string location)
///
///  @param [in]       id U16     string ID
///  @param [out]      str LPTSTR   string buffer
///
///  @return no return value
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
void MApp_ZUI_API_LoadString(U16 id, LPTSTR str)
{
    U8 u8Language = GET_OSD_MENU_LANGUAGE();

    if (u8Language >= LANG_PAGE_MAX) //check numbers of language
        u8Language = 0;
    if (id >= E_ZUI_STR_MAX) //check numbers of strings
        id = 0;

    OSDcp_readbin_string_ptr(u8Language, id, (U16*)str);
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_GetU16String
///  get a string pointer from a U16 integer
///
///  @param [in]       value U16     integer
///
///  @return LPTSTR string content
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
LPTSTR MApp_ZUI_API_GetU16String (U16 value)
{
    MApp_UlongToU16String(value, (U16*)CHAR_BUFFER, MApp_GetNoOfDigit(value));
    return CHAR_BUFFER;
}
///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_GetU16String
///  get a hex string pointer from a U16 integer
///
///  @param [in]       value U16     integer
///
///  @return LPTSTR string content
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
LPTSTR MApp_ZUI_API_GetU16HexString(U16 value)
{
    MApp_HexUlongToU16String((U32)value, (U16*)CHAR_BUFFER, (S8)MApp_GetNoOfHexDigit((U32)value));
    return CHAR_BUFFER;
}



///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_GetS16SignString
///  get a sign string pointer from a S16 integer
///
///  @param [in]       value S16     integer
///
///  @return LPTSTR string content
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
LPTSTR MApp_ZUI_API_GetS16SignString (S16 value)
{
    LPTSTR str = CHAR_BUFFER;
    if (value < 0)
    {
        str[0] = '-';
        MApp_UlongToU16String(-value, str+1, MApp_GetNoOfDigit(-value));
    }
    else if (value > 0)
    {
        str[0] = '+';
        MApp_UlongToU16String(value, str+1, MApp_GetNoOfDigit(value));
    }
    else //if (value == 0)
    {
        str[0] = '0';
        str[1] = 0;
    }
    return CHAR_BUFFER;
}

#if(ENABLE_ATSC)
U16 MApp_ZUI_API_StringBufferUTF16toU16(U16* DstStr, U8* SrcStr, U16 length)
{
    //The length is equal CHAR_BUFFER length
    U16 i;

    for(i=0; i<length; i++)
    {
#if 1//ENABLE_LANGUAGE_KOREA
        // Ray, 03302012
        if( SrcStr[2*i] =='\0' && SrcStr[2*i+1] =='\0')
            break;

#else
        if( SrcStr[2*i+1] =='\0' )
            break;
#endif
        DstStr[i] = ((U16)SrcStr[2*i] << 8 | (U16)SrcStr[2*i+1]);
    }
    DstStr[i] ='\0';

    return i;
}
#endif
/*
void MApp_ZUI_API_ConvertStringU8ToU16(U16 * pu16Str, U8 * pu8Str)
{
    while( *pu8Str )
    {
        *pu16Str++ = *pu8Str++;
    }
    *pu16Str = 0;

}
*/

#if 0
static U8 CHAR_BUFFER[256];
//static U16 _GUI_StringLangPage = LANG_ENGLISH;

static U16* p_copy_string_buffer = (U16*) CHAR_BUFFER2;

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_GetString
///  get a string pointer from string ID, used for localization data
///
///  @param [in]       idx STRING_ID_ENUM     string ID
///
///  @return LPTSTR string content
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
LPTSTR MApp_ZUI_API_GetString(U16 id)
{
    /*if (idx < STR_MAX)
        return _GUI_StringTable[_GUI_StringLangPage][idx];

    PRINT("MApp_ZUI_API_GetString(): illegal idx (%d) !\n", idx);
    ABORT();
    return "";*/
    U8 *u8String;

    //PRINT("\n[GetString] langid = %d, string id = %d", _GUI_StringLangPage, id);
    CHAR_BUFFER[0] = 0; //TODO: OSDcp_readbin_string_ptr(MENU_LANGUAGE, id, (U16*)CHAR_BUFFER);
    //PRINT("\n[GetString] get string %s", (char *)CHAR_BUFFER);
    u8String = MApp_Menu_Strcpy(CHAR_BUFFER, CHAR_IDX_2BYTE);
    //PRINT("\n[GetString] %d", (U16)(*u8String));
    //PRINT("\n[GetString] %d", (U16)*(u8String+1));
    //PRINT("\n[GetString] %d", (U16)*(u8String+2));
    //PRINT("\n[GetString] %d", (U16)*(u8String+3));

    return u8String;

    //return (U8*)CHAR_BUFFER;
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_SetStringLangPage
///  change string code page to a specific language
///
///  @param [in]       idx LANG_PAGE_ENUM     language ID
///
///  @return BOOL TRUE for success, FALSE for fail
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_ZUI_API_SetStringLangPage(U16 idx)
{
    /*if (idx < LANG_MAX && idx != _GUI_StringLangPage)
    {
        _GUI_StringLangPage = idx;
        return TRUE; //ok!
    }*/

    //TODO: MENU_LANGUAGE = idx;
    return TRUE;

    /*PRINT("MApp_ZUI_API_SetStringLangPage(): illegal lang!\n");
    ABORT();
    return FALSE;*/
}

#endif

#undef MAPP_ZUI_APISTRINGS_C
