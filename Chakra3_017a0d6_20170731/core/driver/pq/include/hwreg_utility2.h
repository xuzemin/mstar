//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all 
// or part of MStar Software is expressly prohibited, unless prior written 
// permission has been granted by MStar. 
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.  
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software. 
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s 
//    confidential information in strictest confidence and not disclose to any
//    third party.  
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.  
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or 
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.  
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _HWREG_UTILITY_H_
#define _HWREG_UTILITY_H_

#include "hwreg_pq.h"

extern MS_U8   MApi_XC_ReadByte(MS_U32 u32Reg);
extern MS_U16 MApi_XC_Read2Byte(MS_U32 u32Reg);
extern MS_U32 MApi_XC_Read4Byte(MS_U32 u32Reg);
extern MS_U8   MApi_XC_ReadRegbit(MS_U32 u32Reg, MS_U8 u8Mask);
extern void   MApi_XC_WriteRegBit(MS_U32 u32Reg, MS_BOOL bEnable, MS_U8 u8Mask);
extern void    MApi_XC_WriteByte(MS_U32 u32Reg, MS_U8 u8Val);
extern void    MApi_XC_Write2Byte(MS_U32 u32Reg, MS_U16 u16Val);
extern void    MApi_XC_Write3Byte(MS_U32 u32Reg, MS_U32 u32Val);
extern void    MApi_XC_Write4Byte(MS_U32 u32Reg, MS_U32 u32Val);
extern void    MApi_XC_WriteByteMask(MS_U32 u32Reg, MS_U8 u8Val, MS_U8 u8Msk);
extern void    MApi_XC_Write2ByteMask(MS_U32 u32Reg, MS_U16 u16val, MS_U16 u16Mask);
//=============================================================
// Just for Scaler
extern void    MApi_XC_W2BYTE(MS_U32 u32Reg, MS_U16 u16Val);
extern MS_U16  MApi_XC_R2BYTE(MS_U32 u32Reg);
extern void    MApi_XC_W4BYTE(MS_U32 u32Reg, MS_U32 u32Val);
extern MS_U32  MApi_XC_R4BYTE(MS_U32 u32Reg);
extern MS_U16  MApi_XC_R2BYTEMSK(MS_U32 u32Reg, MS_U16 u16mask);
extern void    MApi_XC_W2BYTEMSK(MS_U32 u32Reg, MS_U16 u16Val, MS_U16 u16mask);

//=============================================================
//General ( Make sure u32Reg is not ODD
extern void    MApi_XC_GW2BYTE(MS_U32 u32Reg, MS_U16 u16Val);
extern MS_U16    MApi_XC_GR2BYTE(MS_U32 u32Reg);
extern void    MApi_XC_GW4BYTE(MS_U32 u32Reg, MS_U32 u32Val);
extern MS_U32  MApi_XC_GR4BYTE(MS_U32 u32Reg);
extern MS_U16  MApi_XC_GR2BYTEMSK(MS_U32 u32Reg, MS_U16 u16mask);
extern void MApi_XC_GW2BYTEMSK(MS_U32 u32Reg, MS_U16 u16Val, MS_U16 u16mask);


#if 0
//!! Do not include this header in driver or api level

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
extern MS_U32 PQ_RIU_BASE;      // This should be inited before XC library starting.

#define _BITMASK(loc_msb, loc_lsb) ((1U << (loc_msb)) - (1U << (loc_lsb)) + (1U << (loc_msb)))
#define BITMASK(x) _BITMASK(1?x, 0?x)
#define HBMASK    0xFF00
#define LBMASK    0x00FF

#define RIU_MACRO_START     do {
#define RIU_MACRO_END       } while (0)

// Address bus of RIU is 16 bits.
#define RIU_READ_BYTE(addr)         ( READ_BYTE( PQ_RIU_BASE + (addr) ) )
#define RIU_READ_2BYTE(addr)        ( READ_WORD( PQ_RIU_BASE + (addr) ) )
#define RIU_WRITE_BYTE(addr, val)   { WRITE_BYTE( PQ_RIU_BASE + (addr), val) }
#define RIU_WRITE_2BYTE(addr, val)  { WRITE_WORD( PQ_RIU_BASE + (addr), val) }


//=============================================================
// Standard Form

#define MDrv_ReadByte( u32Reg )   RIU_READ_BYTE(((u32Reg) << 1) - ((u32Reg) & 1))

#define MDrv_Read2Byte( u32Reg )    (RIU_READ_2BYTE((u32Reg)<<1))

#define MDrv_Read4Byte( u32Reg )   ( (MS_U32)RIU_READ_2BYTE((u32Reg)<<1) | ((MS_U32)RIU_READ_2BYTE(((u32Reg)+2)<<1)<<16 )  )

#define MDrv_ReadRegBit( u32Reg, u8Mask )   (RIU_READ_BYTE(((u32Reg)<<1) - ((u32Reg) & 1)) & (u8Mask))

#define MDrv_WriteRegBit( u32Reg, bEnable, u8Mask )                                     \
    RIU_MACRO_START                                                                     \
    RIU_WRITE_BYTE( (((u32Reg) <<1) - ((u32Reg) & 1)) , (bEnable) ? (RIU_READ_BYTE(  (((u32Reg) <<1) - ((u32Reg) & 1))  ) |  (u8Mask)) :                           \
                                (RIU_READ_BYTE( (((u32Reg) <<1) - ((u32Reg) & 1)) ) & ~(u8Mask)));                            \
    RIU_MACRO_END

#define MDrv_WriteByte( u32Reg, u8Val )                                                 \
    RIU_MACRO_START                                                                     \
    RIU_WRITE_BYTE(((u32Reg) << 1) - ((u32Reg) & 1), u8Val);   \
    RIU_MACRO_END

#define MDrv_Write2Byte( u32Reg, u16Val )                                               \
    RIU_MACRO_START                                                                     \
    if ( ((u32Reg) & 0x01) )                                                        \
    {                                                                               \
        RIU_WRITE_BYTE(((u32Reg) << 1) - 1, (MS_U8)((u16Val)));                                  \
        RIU_WRITE_BYTE(((u32Reg) + 1) << 1, (MS_U8)((u16Val) >> 8));                             \
    }                                                                               \
    else                                                                            \
    {                                                                               \
        RIU_WRITE_2BYTE( ((u32Reg)<<1) ,  u16Val);                                                       \
    }                                                                               \
    RIU_MACRO_END

#define MDrv_Write3Byte( u32Reg, u32Val )   \
    RIU_MACRO_START                         \
    if ((u32Reg) & 0x01)                                                                \
    {                                                                                               \
        RIU_WRITE_BYTE((u32Reg << 1) - 1, u32Val);                                    \
        RIU_WRITE_2BYTE( (u32Reg + 1)<<1 , ((u32Val) >> 8));                                      \
    }                                                                                           \
    else                                                                                        \
    {                                                                                               \
        RIU_WRITE_2BYTE( (u32Reg) << 1,  u32Val);                                                         \
        RIU_WRITE_BYTE( (u32Reg + 2) << 1 ,  ((u32Val) >> 16));                             \
    }                           \
    RIU_MACRO_END

#define MDrv_Write4Byte( u32Reg, u32Val )                                               \
    RIU_MACRO_START                                                                     \
    if ((u32Reg) & 0x01)                                                      \
    {                                                                                               \
        RIU_WRITE_BYTE( ((u32Reg) << 1) - 1 ,  u32Val);                                         \
        RIU_WRITE_2BYTE( ((u32Reg) + 1)<<1 , ( (u32Val) >> 8));                                      \
        RIU_WRITE_BYTE( (((u32Reg) + 3) << 1) ,  ((u32Val) >> 24));                           \
    }                                                                                               \
    else                                                                                                \
    {                                                                                                   \
        RIU_WRITE_2BYTE( (u32Reg) <<1 ,  u32Val);                                                             \
        RIU_WRITE_2BYTE(  ((u32Reg) + 2)<<1 ,  ((u32Val) >> 16));                                             \
    }                                                                     \
    RIU_MACRO_END

#define MDrv_WriteByteMask( u32Reg, u8Val, u8Msk )                                      \
    RIU_MACRO_START                                                                     \
    RIU_WRITE_BYTE( (((u32Reg) <<1) - ((u32Reg) & 1)), (RIU_READ_BYTE((((u32Reg) <<1) - ((u32Reg) & 1))) & ~(u8Msk)) | ((u8Val) & (u8Msk)));                   \
    RIU_MACRO_END




//=============================================================
// Just for Scaler
#define SC_W2BYTE( u32Reg, u16Val)\
            ( { RIU_WRITE_2BYTE(REG_SCALER_BASE << 1, ((u32Reg) >> 8) & 0x00FF ) ; \
                RIU_WRITE_2BYTE( (REG_SCALER_BASE +((u32Reg) & 0xFF) ) << 1 , u16Val  ) ; } )

#define SC_R2BYTE( u32Reg ) \
            ( { RIU_WRITE_2BYTE(REG_SCALER_BASE << 1, ( (u32Reg) >> 8) & 0x00FF ) ; \
                RIU_READ_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFF) )<<1 ) ; } )

#define SC_W4BYTE( u32Reg, u32Val)\
            ( { RIU_WRITE_2BYTE(REG_SCALER_BASE<<1, ((u32Reg) >> 8) & 0x00FF ) ; \
                RIU_WRITE_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFF) ) <<1, (MS_U16)((u32Val) & 0x0000FFFF) ) ; \
                RIU_WRITE_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFF) + 2 ) << 1, (MS_U16)(((u32Val) >> 16) & 0x0000FFFF) ); } )

#define SC_R4BYTE( u32Reg )\
            ( { RIU_WRITE_2BYTE(REG_SCALER_BASE << 1, ((u32Reg) >> 8) & 0x00FF ) ; \
                RIU_READ_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFF) ) << 1 ) | (MS_U32)(RIU_READ_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFF) + 2 ) << 1 )) << 16; } )

#define SC_R2BYTEMSK( u32Reg, u16mask)\
            ( { RIU_WRITE_2BYTE(REG_SCALER_BASE << 1, ((u32Reg) >> 8) & 0x00FF ) ; \
                RIU_READ_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFF) ) << 1) & (u16mask) ; } )

#define SC_W2BYTEMSK( u32Reg, u16Val, u16Mask)\
            ( { RIU_WRITE_2BYTE(REG_SCALER_BASE << 1, ((u32Reg) >> 8) & 0x00FF ) ; \
                RIU_WRITE_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFF) ) << 1, (RIU_READ_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFF) ) << 1) & ~(u16Mask) ) | ((u16Val) & (u16Mask)) ) ; })

//=============================================================
// Just for MOD
#define MOD_W2BYTE( u32Reg, u16Val)\
            ( { RIU_WRITE_2BYTE(REG_MOD_BASE << 1, ((u32Reg) >> 8) & 0x00FF ); \
                RIU_WRITE_2BYTE( (REG_MOD_BASE + ((u32Reg) & 0xFF) ) << 1, u16Val ); } )

#define MOD_R2BYTE( u32Reg ) \
            ( { RIU_WRITE_2BYTE(REG_MOD_BASE << 1, ((u32Reg) >> 8) & 0x00FF ); \
                RIU_READ_2BYTE( (REG_MOD_BASE + ((u32Reg) & 0xFF) ) << 1) ; } )

#define MOD_R2BYTEMSK( u32Reg, u16mask)\
            ( { RIU_WRITE_2BYTE(REG_MOD_BASE << 1, ((u32Reg) >> 8) & 0x00FF ); \
                RIU_READ_2BYTE( (REG_MOD_BASE + ((u32Reg) & 0xFF) ) << 1) & (u16mask); })

#define MOD_W2BYTEMSK( u32Reg, u16Val, u16Mask)\
            ( { RIU_WRITE_2BYTE(REG_MOD_BASE << 1, ((u32Reg) >> 8) & 0x00FF ); \
                RIU_WRITE_2BYTE( (REG_MOD_BASE + ((u32Reg) & 0xFF) )<<1 , (RIU_READ_2BYTE( (REG_MOD_BASE + ((u32Reg) & 0xFF) ) << 1 ) & ~(u16Mask)) | ((u16Val) & (u16Mask)) ); } )


//=============================================================
//General ( Make sure u32Reg is not ODD
#define W2BYTE( u32Reg, u16Val) RIU_WRITE_2BYTE( (u32Reg) << 1 , u16Val )


#define R2BYTE( u32Reg ) RIU_READ_2BYTE( (u32Reg) << 1)

#define W4BYTE( u32Reg, u32Val)\
            ( { RIU_WRITE_2BYTE( (u32Reg) << 1, ((u32Val) & 0x0000FFFF) ); \
                RIU_WRITE_2BYTE( ( (u32Reg) + 2) << 1 , (((u32Val) >> 16) & 0x0000FFFF)) ; } )

#define R4BYTE( u32Reg )\
            ( { RIU_READ_2BYTE( (u32Reg) << 1) | (MS_U32)(RIU_READ_2BYTE( ( (u32Reg) + 2 ) << 1) ) ; } )

#define R2BYTEMSK( u32Reg, u16mask)\
            ( { RIU_READ_2BYTE( (u32Reg)<< 1) & (u16mask) ; } )

#define W2BYTEMSK( u32Reg, u16Val, u16Mask)\
            ( { RIU_WRITE_2BYTE( (u32Reg)<< 1 , (RIU_READ_2BYTE((u32Reg) << 1) & ~(u16Mask)) | ((u16Val) & (u16Mask)) ) ; } )

#endif
#endif

