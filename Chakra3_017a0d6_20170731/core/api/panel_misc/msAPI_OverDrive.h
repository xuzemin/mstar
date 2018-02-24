#ifndef _MSAPI_OVER_DRIVE_H_
#define _MSAPI_OVER_DRIVE_H_


#include "Board.h"

#include "Panel.h"


#if( ENABLE_OVERDRIVE&&ENABLE_OD_BIN )

BOOL msAPI_OD_BIN_Init(void);


#define OD_BIN_TBL_2D       0
#define OD_BIN_TBL_3D       1

#define OD_BIN_TBL_CH_R     0
#define OD_BIN_TBL_CH_G     1
#define OD_BIN_TBL_CH_B     2

#define OD_BIN_TBL_TYPE_33x33    0
#define OD_BIN_TBL_TYPE_17X17    1

BOOL msAPI_OD_BIN_Get_TableData(BOOL bIs3D, U8 u8TblIdx, U8 u8RGBChannel, U8 u8TblType, U8* pu8TblDataBuf, U16 u16BufSize);

#endif

/***************************************************************************************/
#endif // #ifndef _MDRV_MFC_TCON_H_

