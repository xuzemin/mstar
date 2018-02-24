
#ifndef __COMPRESSION_H__
#define __COMPRESSION_H__
#include "MsTypes.h"

MS_U32 Encode(MS_U8 *pInStream, MS_U8 *pOutStream, MS_U32 u32DataLen);
MS_U32 Decode(MS_U8 *pInStream, MS_U8 *pOutStream, MS_U32 u32DataLen);

#endif /* __COMPRESSION_H__ */

