/***************************************************************************/
/*                                                                         */
/*  sferrors.h                                                             */
/*                                                                         */
/*    SFNT error codes (specification only).                               */
/*                                                                         */
/*  Copyright 2001, 2004, 2012, 2013 by                                    */
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
  /* This file is used to define the SFNT error enumeration constants.     */
  /*                                                                       */
  /*************************************************************************/

#ifndef __SFERRORS_H__
#define __SFERRORS_H__

#include FT_MODULE_ERRORS_H

#undef __FTERRORS_H__

#include FT_ERRORS_H

#undef  FT_ERR_PREFIX
#define FT_ERR_PREFIX  FT_Err_  //SFNT_Err_
#define FT_ERR_BASE    FT_Mod_Err_SFNT

#endif /* __SFERRORS_H__ */

/* END */
