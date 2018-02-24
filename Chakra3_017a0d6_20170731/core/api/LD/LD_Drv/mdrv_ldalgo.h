#ifndef _MDRV_LDALGO_H_
#define _MDRV_LDALGO_H_

#include "Board.h"


#if ( LD_ENABLE )

//====================================================================================

typedef enum
{
    HAL_LD_EDGE_TB_TYPE = 0,
    HAL_LD_EDGE_LR_TYPE = 1,
    HAL_LD_DIRECT_TYPE  = 2,
    HAL_LD_LOCAL_TYPE   = 3
} EnuLD_LED_TYPE;

typedef enum
{
    LD_COEF_LINEAR = 0,
    LD_COEF_PERCEPTUAL = 1
} EnuLD_COEF_ENCODING;

typedef enum
{
    LD_TF_MSTAR = 0
} EnuLD_TEMPORAL_FILTER_STYLE;

typedef enum
{
    LD_SF_MSTAR = 0,
    LD_SF_LINEAR
} EnuLD_SPATIAL_FILTER_STYLE;

typedef U8* Typ_Tbl_LD_Gamma;
typedef U8* Typ_Tbl_LD_Remap;

typedef struct
{
    Typ_Tbl_LD_Gamma* p_LdAlgo_Tbl_LD_Gamma;
    Typ_Tbl_LD_Remap* p_LdAlgo_Tbl_LD_Remap;

    U16* pu16OutLedBuf;
    U32 u32OutLedBufSize;

} StuLdAlgoInit;

//====================================================================================

void MDrv_LDAlgo_Init(StuLdAlgoInit* pstLdAlgoInit);

void MDrv_LDAlgo_Main(void);

//====================================================================================

#endif // LD_ENABLE

#endif // _MDRV_LDALGO_H_

