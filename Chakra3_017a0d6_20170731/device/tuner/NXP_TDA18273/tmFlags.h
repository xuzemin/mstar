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
 /*                                        */
 /*                                                                     */
 /* -- DO NOT EDIT --  file built by                                    */
 /*                                        */
 /*-------------------------------------------------------------------------    */
 /* (C) Copyright 2000 Koninklijke Philips Electronics N.V., All Rights Reserved*/
 /*                                                                              */
 /* This source code and any compilation or derivative thereof is the sole       */
 /* property of Philips Corporation and is provided pursuant to a Software       */
 /* License Agreement.  This code is the proprietary information of              */
 /* Philips Corporation and is confidential in nature.  Its use and              */
 /* dissemination by any party other than Philips Corporation is strictly        */
 /* limited by the confidential information provisions of the Agreement          */
 /* referenced above.                                                            */
 /*-------------------------------------------------------------------------     */
 /*                                        */

 /*                                        */
 /* DOCUMENT REF: DVP Build Process Specification                               */
 /*                                                                             */
 /* NOTES:        This file defines the TMFL_xxx build flags.                   */
 /*                                                                             */
 #if         !defined(_TMFLAGS_H_SEEN_)
 #define _TMFLAGS_H_SEEN_
 /* configuration                                                            */
 /*      */
 /* FILENAME:     tmFlags.h                   */
 /*                                           */
 /* DESCRIPTION:  Generated by  */
 #define TMFL_BUILD_VERSION            00.00.00
 #define TMFL_CPU                      0x00020011
 #define TMFL_ENDIAN                   1
 #define TMFL_OS                       0x03020500
 #define TMFL_CPU_IS_X86               1
 #define TMFL_CPU_IS_MIPS              0
 #define TMFL_CPU_IS_HP                0
 #define TMFL_CPU_IS_TM                0
 #define TMFL_CPU_IS_ARM               0
 #define TMFL_CPU_IS_REAL              0
 #define TMFL_OS_IS_BTM                0
 #define TMFL_OS_IS_CE                 0
 #define TMFL_OS_IS_NT                 1
 #define TMFL_OS_IS_PSOS               0
 #define TMFL_OS_IS_NULLOS             0
 #define TMFL_OS_IS_ECOS               0
 #define TMFL_OS_IS_VXWORKS            0
 #define TMFL_OS_IS_MTOS               0
 #define TMFL_OS_IS_CEXEC              0

 // For fix build code error
 #define TMFL_OS_IS_HPUNIX            0

 /* DO NOT CHANGE THIS FILE INDEPENDENTLY !!!                                   */
 /* IT MUST BE SYNCHONISED WITH THE TMFLAGS TEMPLATE FILE ON THE                */
 /* MOREUSE WEB SITE http://pww.rtg.sc.philips.com/cmd/html/global_files.html   */
 /* CONTACT MOREUSE BEFORE ADDING NEW VALUES                                    */
 /* constants                                    */
 #define TMFL_CPU_TYPE_MASK            0xffff0000
 #define TMFL_CPU_TYPE_X86             0x00010000
 #define TMFL_CPU_TYPE_MIPS            0x00020000
 #define TMFL_CPU_TYPE_TM              0x00030000
 #define TMFL_CPU_TYPE_HP              0x00040000
 #define TMFL_CPU_TYPE_ARM             0x00050000
 #define TMFL_CPU_TYPE_REAL            0x00060000
 #define TMFL_CPU_MODEL_MASK           0x0000ffff
 #define TMFL_CPU_MODEL_I486           0x00000001
 #define TMFL_CPU_MODEL_R3940          0x00000002
 #define TMFL_CPU_MODEL_R4300          0x00000003
 #define TMFL_CPU_MODEL_TM1100         0x00000004
 #define TMFL_CPU_MODEL_TM1300         0x00000005
 #define TMFL_CPU_MODEL_TM32           0x00000006
 #define TMFL_CPU_MODEL_HP             0x00000007
 #define TMFL_CPU_MODEL_R4640          0x00000008
 #define TMFL_CPU_MODEL_ARM7           0x00000009
 #define TMFL_CPU_MODEL_ARM920T        0x0000000a
 #define TMFL_CPU_MODEL_ARM940T        0x0000000b
 #define TMFL_CPU_MODEL_ARM10          0x0000000c
 #define TMFL_CPU_MODEL_STRONGARM      0x0000000d
 #define TMFL_CPU_MODEL_RD24120        0x0000000e
 #define TMFL_CPU_MODEL_ARM926EJS      0x0000000f
 #define TMFL_CPU_MODEL_ARM946         0x00000010
 #define TMFL_CPU_MODEL_R1910          0x00000011
 #define TMFL_CPU_MODEL_R4450          0x00000012
 #define TMFL_CPU_MODEL_TM3260         0x00000013
 #define TMFL_ENDIAN_BIG               1
 #define TMFL_ENDIAN_LITTLE            0
 #define TMFL_OS_MASK                  0xff000000
 #define TMFL_OS_VERSION_MASK          0x00ffffff
 #define TMFL_OS_BTM                   0x00000000
 #define TMFL_OS_CE                    0x01000000
 #define TMFL_OS_CE212                 0x01020102
 #define TMFL_OS_CE300                 0x01030000
 #define TMFL_OS_NT                    0x02000000
 #define TMFL_OS_NT4                   0x02040000
 #define TMFL_OS_PSOS                  0x03000000
 #define TMFL_OS_PSOS250               0x03020500
 #define TMFL_OS_PSOS200               0x03020000
 #define TMFL_OS_NULLOS                0x04000000
 #define TMFL_OS_ECOS                  0x05000000
 #define TMFL_OS_VXWORKS               0x06000000
 #define TMFL_OS_MTOS                  0x07000000
 #define TMFL_OS_CEXEC                 0x08000000
 #define TMFL_SCOPE_SP                 0
 #define TMFL_SCOPE_MP                 1
 #define TMFL_REL_ASSERT               0x00000002
 #define TMFL_REL_DEBUG                0x00000001
 #define TMFL_REL_RETAIL               0x00000000
 #define TMFL_CPU_I486                 0x00010001
 #define TMFL_CPU_R3940                0x00020002
 #define TMFL_CPU_R4300                0x00020003
 #define TMFL_CPU_TM1100               0x00030004
 #define TMFL_CPU_TM1300               0x00030005
 #define TMFL_CPU_TM32                 0x00030006
 #define TMFL_CPU_HP                   0x00040007
 #define TMFL_CPU_R4640             0x00020008
 #define TMFL_CPU_ARM7              0x00050009
 #define TMFL_CPU_ARM920T           0x0005000a
 #define TMFL_CPU_ARM940T           0x0005000b
 #define TMFL_CPU_ARM10                   0x0005000c
 #define TMFL_CPU_STRONGARM            0x0005000d
 #define TMFL_CPU_RD24120              0x0006000e
 #define TMFL_CPU_ARM926EJS            0x0005000f
 #define TMFL_CPU_ARM946               0x00050010
 #define TMFL_CPU_R1910             0x00020011
 #define TMFL_CPU_R4450             0x00020012
 #define TMFL_CPU_TM3260             0x00030013
 #define TMFL_MODE_KERNEL              1
 #define TMFL_MODE_USER                0

 #endif   /* !defined(_TMFLAGS_H_SEEN_)                                         */
