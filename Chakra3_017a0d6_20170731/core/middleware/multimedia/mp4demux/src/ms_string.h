////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2009-2012 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////


#ifndef MS_STRING_H
#define MS_STRING_H

#if defined(_MSC_VER)

#include <string.h>
#include <stdio.h>
#define ms_strnicmp(a, b, n)    _strnicmp(a, b, n)
#define ms_snprintf             _snprintf

#elif defined(__RTK_OS__)

#include <stdio.h>
#define NEED_STRNCASECMP
int ms_strnicmp(const char *pszStr1, const char *pszStr2, int n);
#define ms_snprintf             snprintf

#elif defined(ECOS) || defined(__CHAKRA__)

#include <string.h>
#define ms_strnicmp(a, b, n)    strncasecmp(a, b, n)
#define ms_snprintf             snprintf

#else

#include <strings.h>
#define ms_strnicmp(a, b, n)    strncasecmp(a, b, n)
#define ms_snprintf             snprintf

#endif

#endif /* MS_STRING_H */
