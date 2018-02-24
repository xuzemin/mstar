/***************************************************************************/
/*                                                                         */
/*  ttpost.h                                                               */
/*                                                                         */
/*    Postcript name table processing for TrueType and OpenType fonts      */
/*    (specification).                                                     */
/*                                                                         */
/*  Copyright 1996-2001, 2002 by                                           */
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

#ifndef __TTPOST_H__
#define __TTPOST_H__


#include <ft2build.h>
#include FT_CONFIG_CONFIG_H
#include FT_INTERNAL_TRUETYPE_TYPES_H


FT_BEGIN_HEADER


  FT_LOCAL( FT_Error )
  tt_face_get_ps_name( TT_Face      face,
                       FT_UInt      idx,
                       FT_String**  PSname );

  FT_LOCAL( void )
  tt_face_free_ps_names( TT_Face  face );


FT_END_HEADER

#endif /* __TTPOST_H__ */


/* END */
