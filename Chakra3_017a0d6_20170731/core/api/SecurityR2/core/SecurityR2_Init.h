#ifndef __SECURE_R2_INIT__
#define __SECURE_R2_INIT__

#include "MsTypes.h"
#include "datatype.h"

typedef enum E_SecR2_Satus
{
	E_SECR2_SUCCESS = 0,
	E_SECR2_UNKNOW_ERROR = 1,
	E_SECR2_DRAMSIZE_ERROR = 2,
	E_SECR2_SecureR2_BaseAddr_ERROR = 3,
	E_SECR2_SecureR2_Size_ERROR = 4,
} E_SecR2_Satus;

E_SecR2_Satus SecurityR2_Init(U16 u16DramSize, U32 u32SecureR2_Base_Addr, U32 u32SecureR2_Size, U32 u32SecureRange_Base_Addr, U32 u32SecureRange_Size, U16 u16DebugMode);

#endif
