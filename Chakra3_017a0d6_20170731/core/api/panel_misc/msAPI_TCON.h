#ifndef _MSAPI_TCON_H_
#define _MSAPI_TCON_H_


#include "Board.h"

#include "Panel.h"


#if( ENABLE_TCON_2014 )

BOOL msAPI_TCON_Init(void);


typedef enum
{
    TCON_TBL_2D,
    TCON_TBL_3D,
} EnuTConTbl2D3D;

BOOL msAPI_TCON_LoadTable(EnuTConTbl2D3D eTConTbl2D3D);

#endif

/***************************************************************************************/
#endif // #ifndef _MDRV_MFC_TCON_H_

