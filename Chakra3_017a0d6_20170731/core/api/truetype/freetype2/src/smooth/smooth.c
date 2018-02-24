/***************************************************************************/
/*                                                                         */
/*  smooth.c                                                               */
/*                                                                         */
/*    FreeType anti-aliasing rasterer module component (body only).        */
/*                                                                         */
/*  Copyright 1996-2001 by                                                 */
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
#include "msAPI_MLE_font_vector.h"

#if ( !MONO_FONT )

#define FT_MAKE_OPTION_SINGLE_OBJECT

#include <ft2build.h>
#include "ftspic.c"
#include "ftgrays.c"
#include "ftsmooth.c"

#endif
/* END */
