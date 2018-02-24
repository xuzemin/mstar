////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (!¡±MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef MW_USBCMAC_H
#define MW_USBCMAC_H

#ifdef MW_USBCMAC_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

#define AES_ENCRYPT     1
#define AES_DECRYPT     0

/**
 * \brief          AES context structure
 */
typedef struct
{
    int nr;                     /*!<  number of rounds  */
    unsigned long *rk;          /*!<  AES round keys    */
    unsigned long buf[68];      /*!<  unaligned data    */
}
aes_context;

INTERFACE unsigned char Check_CMAC(unsigned int u32miu0addr, unsigned int u32FileLength);

#undef INTERFACE

#endif

