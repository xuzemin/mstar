/***************************************************************************/
/*                                                                         */
/*  ftstdlib.h                                                             */
/*                                                                         */
/*    ANSI-specific library and header configuration file (specification   */
/*    only).                                                               */
/*                                                                         */
/*  Copyright 2002-2007, 2009, 2011-2012 by                                */
/*  David Turner, Robert Wilhelm, and Werner Lemberg.                      */
/*                                                                         */
/*  This file is part of the FreeType project, and may only be used,       */
/*  modified, and distributed under the terms of the FreeType project      */
/*  license, LICENSE.TXT.  By continuing to use, modify, or distribute     */
/*  this file you indicate that you have read the license and              */
/*  understand and accept it fully.                                        */
/*                                                                         */
/***************************************************************************/
/*  MStar Semiconductor, Inc. hereby chooses to receive license on the     */
/*  FreeType 2 font engine under the FreeType License, found in the file   */
/*  'FTL.TXT'                                                              */
/***************************************************************************/


  /*************************************************************************/
  /*                                                                       */
  /* This file is used to group all #includes to the ANSI C library that   */
  /* FreeType normally requires.  It also defines macros to rename the     */
  /* standard functions within the FreeType source code.                   */
  /*                                                                       */
  /* Load a file which defines __FTSTDLIB_H__ before this one to override  */
  /* it.                                                                   */
  /*                                                                       */
  /*************************************************************************/


#ifndef __FTSTDLIB_H__
#define __FTSTDLIB_H__

#include "datatype.h"
///#include "msAPI_Memory.h"
//#include "sys_MsWrapper_cus_os_mem.h"

#if !defined (__SDK_SIMULATION__)
//#include "mdl_vfs_file.ho"
#endif

#if defined (__SDK_SIMULATION__)
#include "vm_types.ht"
#else
#include <stddef.h>
#endif

extern U32 ftHmemCacheHandle;

#define ft_ptrdiff_t  ptrdiff_t


  /**********************************************************************/
  /*                                                                    */
  /*                           integer limits                           */
  /*                                                                    */
  /* UINT_MAX and ULONG_MAX are used to automatically compute the size  */
  /* of `int' and `long' in bytes at compile-time.  So far, this works  */
  /* for all platforms the library has been tested on.                  */
  /*                                                                    */
  /* Note that on the extremely rare platforms that do not provide      */
  /* integer types that are _exactly_ 16 and 32 bits wide (e.g. some    */
  /* old Crays where `int' is 36 bits), we do not make any guarantee    */
  /* about the correct behaviour of FT2 with all fonts.                 */
  /*                                                                    */
  /* In these case, `ftconfig.h' will refuse to compile anyway with a   */
  /* message like `couldn't find 32-bit type' or something similar.     */
  /*                                                                    */
  /**********************************************************************/


#include <limits.h>

#define FT_CHAR_BIT   CHAR_BIT
#define FT_USHORT_MAX USHRT_MAX
#define FT_INT_MAX    INT_MAX
#define FT_INT_MIN    INT_MIN
#define FT_UINT_MAX   UINT_MAX
#define FT_ULONG_MAX  ULONG_MAX


  /**********************************************************************/
  /*                                                                    */
  /*                 character and string processing                    */
  /*                                                                    */
  /**********************************************************************/


#include <string.h>

#define ft_memchr   memchr
#define ft_memcmp   memcmp
#define ft_memcpy   memcpy
#define ft_memmove  memmove
#define ft_memset   memset
#define ft_strcat   strcat
#define ft_strcmp   strcmp
#define ft_strcpy   strcpy
#define ft_strlen   strlen
#define ft_strncmp  strncmp
#define ft_strncpy  strncpy
#define ft_strrchr  strrchr
#define ft_strstr   strstr


  /**********************************************************************/
  /*                                                                    */
  /*                           file handling                            */
  /*                                                                    */
  /**********************************************************************/


#include <stdio.h>

#define FT_FILE     FILE
#define ft_fclose   file_fclose //fclose
#define ft_fopen    file_fopen //fopen
#define ft_fread    file_fread //fread
#define ft_fseek    file_fseek //fseek
#define ft_ftell    file_ftell //ftell
#define ft_sprintf  sprintf


  /**********************************************************************/
  /*                                                                    */
  /*                             sorting                                */
  /*                                                                    */
  /**********************************************************************/


#include <stdlib.h>

#define ft_qsort  qsort


  /**********************************************************************/
  /*                                                                    */
  /*                        memory allocation                           */
  /*                                                                    */
  /**********************************************************************/
extern void* ttfmalloc(size_t bytes);
extern void ttffree(void* mem);
extern void* ttfrealloc(void* oldmem, size_t bytes);
extern void* ttfcalloc(size_t n_elements, size_t elem_size);

///#define MALLOC(size) msAPI_Memory_Allocate(size, BUF_ID_GLYPH_DISP_INFO)        ///MLE_Malloc(size)
#define MALLOC(size) ttfmalloc(size)                                                                        ///MLE_Malloc(size)
///#define REALLOC(ptr, size) msAPI_Memory_ReAllocate(ptr, size, BUF_ID_GLYPH_DISP_INFO)   ///MLE_Realloc(ptr, size)
#define REALLOC(ptr, size) ttfrealloc(ptr, size)                                                         ///MLE_Realloc(ptr, size)
///#define FREE(a) msAPI_Memory_Free(a, BUF_ID_GLYPH_DISP_INFO)    ///MLE_Free(a)
#define FREE(a) ttffree(a)                                                                    ///MLE_Free(a)

///#define CALLOC(num,size) msAPI_Memory_CAllocate(num, size, BUF_ID_GLYPH_DISP_INFO)        ///MLE_Calloc(num,size)
#define CALLOC(num,size) ttfcalloc(num, size)        ///MLE_Calloc(num,size)

#define ft_scalloc(x)       //ttfcalloc                              // not used now
///#define ft_sfree(x)         msAPI_Memory_Free(x, BUF_ID_GLYPH_DISP_INFO)    //MsHMEMFree(x,0)
#define ft_sfree(x)     ttffree(x)    //MsHMEMFree(x,0)
///#define ft_smalloc(x)       msAPI_Memory_Allocate(x, BUF_ID_GLYPH_DISP_INFO)    //MsHMEMMalloc(ftHmemCacheHandle,x,0)
#define ft_smalloc(x)   ttfmalloc(x)    //MsHMEMMalloc(ftHmemCacheHandle,x,0)
///#define ft_srealloc(x,y)    msAPI_Memory_ReAllocate(x, y, BUF_ID_GLYPH_DISP_INFO)   //MsHMEMRealloc(ftHmemCacheHandle,x,y,0)
#define ft_srealloc(x,y)    ttfrealloc(x, y)   //MsHMEMRealloc(ftHmemCacheHandle,x,y,0)
//#define ft_squery(x)        {ghStatus_t status={0};MsHMEMQueryHeapStatus(ftHmemCacheHandle,&status);*x=status.TotalFreeSize;}
///extern unsigned long dlmemory_query(void);
///#define ft_squery(x)        {*x = dlmemory_query();}    
extern unsigned long        ttfmemory_query(void);
#define ft_squery(x)        {*x = ttfmemory_query();}


  /**********************************************************************/
  /*                                                                    */
  /*                          miscellaneous                             */
  /*                                                                    */
  /**********************************************************************/


#define ft_atol   atol
#define ft_labs   labs


  /**********************************************************************/
  /*                                                                    */
  /*                         execution control                          */
  /*                                                                    */
  /**********************************************************************/


#include <setjmp.h>

#define ft_jmp_buf     jmp_buf  /* note: this cannot be a typedef since */
                                /*       jmp_buf is defined as a macro  */
                                /*       on certain platforms           */

#define ft_longjmp     longjmp
#define ft_setjmp( b ) setjmp( *(ft_jmp_buf*) &(b) ) /* same thing here */


  /* the following is only used for debugging purposes, i.e., if */
  /* FT_DEBUG_LEVEL_ERROR or FT_DEBUG_LEVEL_TRACE are defined    */

#include <stdarg.h>


#endif /* __FTSTDLIB_H__ */


/* END */
