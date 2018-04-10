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

#ifndef _MAPP_ZUI_APICOMMON_H
  #define _MAPP_ZUI_APICOMMON_H

#include "datatype.h"
#if ENABLE_DMP
#include "MApp_UiMediaPlayer_Define.h"
#endif



    /**
     * \defgroup handles ZUI data types
     * @{
     */


/**
 * \var typedef unsigned int HWND
 * \brief Handle to main window or control. (16 bits, maximum 65535)
 */
typedef U16 HWND;


/**
 * \var typedef unsigned int WPARAM
 * \brief A type definition for the first message paramter. (32 bits)
 */
typedef U32    WPARAM;

/**
 * \var typedef unsigned long WPARAM
 * \brief A type definition for the second message paramter.
 */
//typedef U32   LPARAM;


/**
 * \var LPCTSTR
 * \brief 8/16 bits Character indepentdent: constant string pointer
 *
*/
/**
 * \var LPTSTR
 * \brief 8/16 bits Character indepentdent: string pointer
 *
*/
/**
 * \var TCHAR
 * \brief 8/16 bits Character indepentdent: character type
 *
*/
typedef U16              TCHAR;
typedef const TCHAR *      LPCTSTR;
typedef TCHAR *            LPTSTR;
#define SIZEOF_TCHAR        2

/////////////////////////////////////////
// Event Prototypes....
// note: don't use function pointer anymore...
//typedef void (*CALLBACK_ACTION_EXEC)(HWND sender);
//typedef void (*CALLBACK_SEL_CHANGED)(HWND sender, U16 sel_index);


/**
 * Size structure of a 2-dimension object.
 */
typedef struct _SIZE
{
    /**
     * the extent in x coordinate of a 2D object.
     */
    S16 cx;
    /**
     * the extent in y coordinate of a 2D object.
     */
    S16 cy;
} SIZE;

/**
 * \def VIRTUAL_KEY_CODE
 * \brief system independent key code (maximum 63)
 *
*/
typedef enum
{
    VK_NULL = 0,
	
    VK_TV_RADIO,
    VK_CHANNEL_LIST,
    VK_CHANNEL_FAV_LIST,
    VK_CHANNEL_RETURN,
    VK_CHANNEL_PLUS,
    VK_CHANNEL_MINUS,

    VK_AUDIO,
    VK_IMAGE,
    VK_VIDEO,
    VK_DVD,
    VK_SETUP,

    VK_VOLUME_PLUS,
    VK_VOLUME_MINUS,
    VK_UP,
    VK_POWER,
    VK_EXIT,
    VK_MENU,
    VK_DOWN,
    VK_LEFT,
    VK_SELECT,
    VK_RIGHT,

	VK_KEYSTONE_PLUS,     //xzm @20171228 
    VK_KEYSTONE_MINUS,		//xzm @20171228 
	VK_HOME,
    VK_NUM_0,
    VK_NUM_1,
    VK_NUM_2,
    VK_NUM_3,
    VK_NUM_4,
    VK_NUM_5,
    VK_NUM_6,
    VK_NUM_7,
    VK_NUM_8,
    VK_NUM_9,

    VK_MUTE,
    VK_PAGE_UP,
    VK_PAGE_DOWN,
    VK_CLOCK,

    VK_INPUT_SOURCE,

    VK_EPG,
    VK_INFO,
    VK_BACK,
    VK_MTS,
    VK_TTX,

    VK_RED,
    VK_GREEN,
    VK_YELLOW,
    VK_BLUE,

    VK_PICTURE,
    VK_CC,
    VK_ZOOM,
    VK_FREEZE,
    VK_INDEX,

    VK_SLEEP,

    VK_DSC_KEY_ARC4X3,
    VK_DSC_KEY_ARC16X9,
    VK_DSC_KEY_ARCZOOM,

    VK_PLAY,
    VK_PAUSE,
    VK_STOP,
    VK_NEXT,
    VK_PREVIOUS,
    VK_FF,
    VK_REWIND,
    VK_RECORD,

    VK_SUBTITLE,
    VK_UPDATE,
    VK_EPGTIMER_COUNTDOWN,

    VK_DASH,

    VK_PIP,
#if 1
     VK_TEMP_DET,
#endif
    VK_BAT_LOW,//wht141014_8
    VK_MAX ,   //xzm @20171228 keystone   VK_MAX = 69
} VIRTUAL_KEY_CODE;

/**
 * \def TABLESIZE(table)
 * \brief A macro returns the number of elements in a \a table.
 */
#define TABLESIZE(table)    (sizeof(table)/sizeof(table[0]))

/* MAX/MIN/ABS macors */
/**
 * \def MAX(x, y)
 * \brief A macro returns the maximum of \a x and \a y.
 */
#ifndef MAX
#define MAX(x, y)           (((x) > (y))?(x):(y))
#endif
/**
 * \def MIN(x, y)
 * \brief A macro returns the minimum of \a x and \a y.
 */
#ifndef MIN
#define MIN(x, y)           (((x) < (y))?(x):(y))
#endif
/**
 * \def ABS(x)
 * \brief A macro returns the absolute value of \a x.

#ifndef ABS
#define ABS(x)              (((x)<0) ? -(x) : (x))
#endif*/


/*#ifndef PATH_MAX
    #define PATH_MAX    256
#endif

#ifndef NAME_MAX
    #define NAME_MAX    64
#endif*/


/**
 * \def MAX_PATH
 * \brief The possible maximal length of a path name.
 * \note This definition is an alias of PATH_MAX
 */
//#define MAX_PATH        PATH_MAX
/**
 * \def MAX_NAME
 * \brief The possible maximal length of a file name.
 * \note This definition is an alias of NAME_MAX
 */
//#define MAX_NAME        NAME_MAX

    /** @} end of misc_macros */

    /** @} end of macros_types */


#endif /* _MAPP_ZUI_APICOMMON_H */


