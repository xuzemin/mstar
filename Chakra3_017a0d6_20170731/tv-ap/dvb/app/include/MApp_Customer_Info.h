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


/* INPUT_SW_PROJECT
Chakra      -   01
POLLUX      -   02
ARCHIMEDES  -   03
Chakra2     !V   04
OBAMA       !V   05
*/

/* INPUT_PRODUCT_TYPE
TV-01
STB-02
*/

/* INPUT_TV_SYSTEM
ATSC-01
DVBT-02
DVBC-03
DVBS-04
DMBT-05
ATV Only-06
*/

//**************************************************************************
//********************** Customer Info Input Area **************************
//**************************************************************************
//Customer ID (Example:0009 = 0x0009) (Example: 20= 0x0014)
#define INPUT_CUSTOMER_ID_LOW_BYTE  0x76//0x53//0x66 //gchen @ 20171219
#define INPUT_CUSTOMER_ID_HIGH_BYTE 0x00//0x03//0x66

//Model ID (Example:0001 = 0x0001)
#define INPUT_MODEL_ID_LOW_BYTE     0x40//0x94//0x01 //gchen @ 20171219
#define INPUT_MODEL_ID_HIGH_BYTE    0x04//0x88//0x00

//Chip ID (Example:000B = 0x000B)
#define INPUT_CHIP_ID_LOW_BYTE      0xB3//0x66 //gchen @ 20171219
#define INPUT_CHIP_ID_HIGH_BYTE     0x00//0x66

#define INPUT_SW_PROJECT            0x04
#define INPUT_SW_GENERATION         0x01
#define INPUT_PRODUCT_TYPE          0x01
#define INPUT_TV_SYSTEM             0x02

//Label (Example:00000456 = 0x0001C8)
#define INPUT_LABEL_LOW_BYTE        0x08
#define INPUT_LABEL_MIDDLE_BYTE     0x00
#define INPUT_LABEL_HIGH_BYTE       0x00

//CL(Change-List) (Example:00101234 = 0x18B72)
#define INPUT_CL_LOW_BYTE           0x10
#define INPUT_CL_MIDDLE_BYTE        0x4C
#define INPUT_CL_HIGH_BYTE          0x02

#define DRM_MODEL_ID  0x3130


//  SW Quality
//  01-BOOTLEG
//  02-Demo
//  03-Pre-Alpha
//  04-Alpha
//  05-Beta
//  06-RC
//  07-RTM
//  Quality flag can be modified by release engineer only

#define INPUT_RELEASE_QUALITY       0x01

//CPU TYPE
//01-MIPS
//02-AEON
#if (defined(MIPS_CHAKRA) || defined(ARM_CHAKRA))
#define  INPUT_CPU_TYPE 0x01
#else
#define  INPUT_CPU_TYPE 0x02
#endif

//Customer IP
//gchen @ 20171219 //hash key
//00000000 08002840 20000104 38F80000
//00000000 00000840 20000144 7BF89800
//0xb7,0x29,0x30,0xbc,0x80,0x10,0x60,0xf1,0xc4,0x17,0x61,0xd2,0x4e,0x74,0x8d,0xb5
//0x02,0x68,0x74,0xcc,0x72,0xf3,0x9c,0x3a,0x87,0x98,0x3f,0x95,0x10,0x56,0xf2,0x2a
unsigned char code IP_Cntrol_Mapping_1[8] = "00000000"; //Customer IP Control-1
unsigned char code IP_Cntrol_Mapping_2[8] = "00000840"; //Customer IP Control-2
unsigned char code IP_Cntrol_Mapping_3[8] = "20000144"; //Customer IP Control-3
unsigned char code IP_Cntrol_Mapping_4[8] = "7BF89800"; //Customer IP Control-4
unsigned char code Customer_hash[] = {0x02,0x68,0x74,0xcc,0x72,0xf3,0x9c,0x3a,0x87,0x98,0x3f,0x95,0x10,0x56,0xf2,0x2a};

/*
unsigned char code IP_Cntrol_Mapping_1[8] = "00000000"; //Customer IP Control-1
unsigned char code IP_Cntrol_Mapping_2[8] = "00000000"; //Customer IP Control-2
unsigned char code IP_Cntrol_Mapping_3[8] = "00000000"; //Customer IP Control-3
unsigned char code IP_Cntrol_Mapping_4[8] = "08F80000"; //Customer IP Control-4

unsigned char code Customer_hash[] = {0x1a,0x30,0x4f,0x0a,0x3a,0x42,0xd9,0x4b,0x08,0xd5,0x74,0xa2,0xfd,0xf1,0x69,0x3f};
*/
U16 u16DRMModelID=DRM_MODEL_ID;
//**************************************************************************
//**************************************************************************
//**************************************************************************





unsigned char code CID_Buf[32] =  {
//Fix Value: Do not Modify
        'M', 'S', 'I', 'F',         // (Do not modify)Mstar Information:MSIF
        '0', '1',                   // (Do not modifyCustomer Info Class: 01

//Customer Info area
        INPUT_CUSTOMER_ID_LOW_BYTE,
        INPUT_CUSTOMER_ID_HIGH_BYTE,

        INPUT_MODEL_ID_LOW_BYTE,
        INPUT_MODEL_ID_HIGH_BYTE,

        INPUT_CHIP_ID_LOW_BYTE,
        INPUT_CHIP_ID_HIGH_BYTE,

        INPUT_SW_PROJECT,
        INPUT_SW_GENERATION,
        INPUT_PRODUCT_TYPE,
        INPUT_TV_SYSTEM,

        INPUT_LABEL_LOW_BYTE,
        INPUT_LABEL_MIDDLE_BYTE,
        INPUT_LABEL_HIGH_BYTE,

        INPUT_CL_LOW_BYTE,
        INPUT_CL_MIDDLE_BYTE,
        INPUT_CL_HIGH_BYTE,

        INPUT_RELEASE_QUALITY,

        INPUT_CPU_TYPE,
//Reserve
        '0', '0', '0', '0', '0', '0', '0', '0'   // Reserve
        };



