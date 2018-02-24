/*
  Copyright (C) 2010 NXP B.V., All Rights Reserved.
  This source code and any compilation or derivative thereof is the proprietary
  information of NXP B.V. and is confidential in nature. Under no circumstances
  is this software to be  exposed to or placed under an Open Source License of
  any type without the expressed written permission of NXP B.V.
 *
 * \file          tmbslTDA182I4_Instance.h
 *
 * \date          %modify_time%
 *
 * \author        David LEGENDRE
 *                Michael VANNIER
 *
 * \brief         Describe briefly the purpose of this file.
 *
 * REFERENCE DOCUMENTS :
 *                TDA182I4_Driver_User_Guide.pdf
 *
 * TVFE SW Arch V4 Template: Author Christophe CAZETTES
 *
 * \section info Change Information
 *
*/

#ifndef _TMBSL_TDA182I4_INSTANCE_H
#define _TMBSL_TDA182I4_INSTANCE_H

#ifdef __cplusplus
extern "C"
{
#endif


tmErrorCode_t
iTDA182I4_AllocInstance(tmUnitSelect_t tUnit, ppTDA182I4Object_t ppDrvObject);

tmErrorCode_t
iTDA182I4_DeAllocInstance(pTDA182I4Object_t pDrvObject);

tmErrorCode_t
iTDA182I4_GetInstance(tmUnitSelect_t tUnit, ppTDA182I4Object_t ppDrvObject);

tmErrorCode_t
iTDA182I4_ResetInstance(pTDA182I4Object_t pDrvObject);


#ifdef __cplusplus
}
#endif

#endif /* _TMBSL_TDA182I4_INSTANCE_H */

