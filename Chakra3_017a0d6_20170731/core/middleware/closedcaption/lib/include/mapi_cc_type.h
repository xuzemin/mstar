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
#ifndef MAPI_CC_TYPE_H
#define MAPI_CC_TYPE_H

/***************************************************************************************/
/*                 Header Files                                                        */
/***************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

#ifndef UNUSED
#define UNUSED(var) (void)((var) = (var))
#endif

/// data type unsigned char, data length 1 byte
typedef unsigned char               CC_U8;                              // 1 byte
/// data type unsigned short, data length 2 byte
typedef unsigned short              CC_U16;                             // 2 bytes
/// data type unsigned int, data length 4 byte
#ifdef UTOPIA64
typedef unsigned int               CC_U32;                             // 4 bytes
#else
typedef unsigned long               CC_U32;                             // 4 bytes
#endif
/// data type unsigned int, data length 8 byte
typedef unsigned long long          CC_U64;                             // 8 bytes
/// data type signed char, data length 1 byte
typedef signed char                 CC_S8;                              // 1 byte
/// data type signed short, data length 2 byte
typedef signed short                CC_S16;                             // 2 bytes
/// data type signed int, data length 4 byte
#ifdef UTOPIA64
typedef signed int                 CC_S32;                             // 4 bytes
#else
typedef signed long                 CC_S32;                             // 4 bytes
#endif
/// data type signed int, data length 8 byte
typedef signed long long            CC_S64;                             // 8 bytes
/// data type float, data length 4 byte
typedef float                       CC_FLOAT;                           // 4 bytes
/// definition for CC_BOOL
typedef unsigned char               CC_BOOL;

typedef signed char CC_FONTHANDLE;


#if !defined(TRUE) && !defined(FALSE)
/// definition for TRUE
#define TRUE                        1
/// definition for FALSE
#define FALSE                       0
#endif


/// data type null pointer
#ifdef NULL
#undef NULL
#endif
#define NULL                        0
#define VALID                      1
#define INVALID                  0
#define NA                           0xFF
#define ZERO                       0


#define MBIT0                0x00000001
#define MBIT1                0x00000002
#define MBIT2                0x00000004
#define MBIT3                0x00000008
#define MBIT4                0x00000010
#define MBIT5                0x00000020
#define MBIT6                0x00000040
#define MBIT7                0x00000080
#define MBIT8                0x00000100
#define MBIT9                0x00000200
#define MBIT10               0x00000400
#define MBIT11               0x00000800
#define MBIT12               0x00001000
#define MBIT13               0x00002000
#define MBIT14               0x00004000
#define MBIT15               0x00008000
#define MBIT16               0x00010000
#define MBIT17               0x00020000
#define MBIT18               0x00040000
#define MBIT19               0x00080000
#define MBIT20               0x00100000
#define MBIT21               0x00200000
#define MBIT22               0x00400000
#define MBIT23               0x00800000
#define MBIT24               0x01000000
#define MBIT25               0x02000000
#define MBIT26               0x04000000
#define MBIT27               0x08000000
#define MBIT28               0x10000000
#define MBIT29               0x20000000
#define MBIT30               0x40000000
#define MBIT31               0x80000000

 // Git version
#ifndef GIT_VERSION_CHAR1
#define GIT_VERSION_CHAR1  '-'
#endif //

#ifndef GIT_VERSION_CHAR2
#define GIT_VERSION_CHAR2  '-'
#endif //

#ifndef GIT_VERSION_CHAR3
#define GIT_VERSION_CHAR3  '-'
#endif //

#ifndef GIT_VERSION_CHAR4
#define GIT_VERSION_CHAR4  '-'
#endif //

#ifndef GIT_VERSION_CHAR5
#define GIT_VERSION_CHAR5  '-'
#endif //

#ifndef GIT_VERSION_CHAR6
#define GIT_VERSION_CHAR6  '-'
#endif //

#ifndef GIT_VERSION_CHAR7
#define GIT_VERSION_CHAR7  '-'
#endif //

#ifndef GIT_VERSION_CHAR8
#define GIT_VERSION_CHAR8  '-'
#endif //


#ifdef __cplusplus
  }
#endif
#endif
///*** please do not remove change list tag ***///
///***$Change: 1262619 $***///
