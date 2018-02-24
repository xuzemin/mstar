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
//***************************************************************************
//!file     si_cbusDefs.c
//!brief    CBUS API Definitions
//
// No part of this work may be reproduced, modified, distributed,
// transmitted, transcribed, or translated into any language or computer
// format, in any form or by any means without written permission of
// Silicon Image, Inc., 1060 East Arques Avenue, Sunnyvale, California 94085
//
// Copyright 2007-2009, Silicon Image, Inc.  All rights reserved.
//***************************************************************************/

#ifndef __SI_CBUS_DEFS_H__
#define	__SI_CBUS_DEFS_H__

// Version that this chip supports
#define	MHL_VER_MAJOR		(0x01 << 4)	// bits 4..7
#define	MHL_VER_MINOR		0x00		// bits 0..3
#define		MHL_VERSION						(MHL_VER_MAJOR | MHL_VER_MINOR)

#define	CBUS_VER_MAJOR		(0x01 << 4)	// bits 4..7
#define	CBUS_VER_MINOR		0x00		// bits 0..3
#define		MHL_CBUS_VERSION				(CBUS_VER_MAJOR | CBUS_VER_MINOR)

#define	MHL_DEV_CAT_SINK					0x01
#define	MHL_DEV_CAT_SOURCE					0x02
#define	MHL_DEV_CAT_DONGLE					0x03

#define		MHL_POWER_SUPPLY_CAPACITY		16		// 160 mA current
#define		MHL_POWER_SUPPLY_PROVIDED		16		// 160mA 0r 0 for Wolverine.
#define		MHL_VIDEO_LINK_MODE_SUPORT		SUPP_RGB444|SUPP_YCBCR444|SUPP_YCBCR422|SUPP_ISLANDS|SUPP_VGA		
#define		MHL_AUDIO_LINK_MODE_SUPORT		AUD_2CH
#define		MHL_VIDEO_TYPE_SUPPORT			0

#define		MHL_BANDWIDTH_LIMIT				0x0F		// 75 MHz

#define		MHL_DEVCAP_SIZE					16
#define		MHL_INTERRUPT_SIZE				3
#define		MHL_STATUS_SIZE					3
#define     MHL_INT_STATUS_SIZE				((MHL_INTERRUPT_SIZE<<4)|MHL_STATUS_SIZE)
#define		MHL_SCRATCHPAD_SIZE				16
#define		MHL_MAX_BUFFER_SIZE				MHL_SCRATCHPAD_SIZE	// manually define highest number

#define 	MHL_RCP_SUPPORT					(0x01 << 0)
#define 	MHL_RAP_SUPPORT					(0x01 << 1)
#define 	MHL_SP_SUPPORT					(0x01 << 2)
#define			MHL_FEATURE_FLAG			(MHL_RCP_SUPPORT|MHL_RAP_SUPPORT|MHL_SP_SUPPORT)

#define     MHL_DEVICE_ID_H					0x92
#define     MHL_DEVICE_ID_L					0x31

#define 	MHL_REG_CHANGE_INT_OFFSET		0x20

#define		MHL_DEVICE_STATUS_CONNECTED_RDY_REG_OFFSET		0x30
#define		DCAP_RDY											0x01
#define		DSCR_RDY											0x02

#define		MHL_DEVICE_STATUS_LINK_MODE_REG_OFFSET			0x31
#define		PATH_EN												0x08

#define		MHL_DEV_CAP_DEV_STATE_REG_OFFSET				0x00

#define		MHL_DEV_CAP_MHL_VERSION_REG_OFFSET				0x01

#define		MHL_DEV_CAP_DEV_CAT_REG_OFFSET					0x02
#define		SOURCE_DEV											0x00
#define		SINGLE_INPUT_SINK									0x01
#define		MULTIPLE_INPUT_SINK									0x02
#define		UNPOWERED_DONGLE									0x03
#define		SELF_POWERED_DONGLE									0x04
#define		HDCP_REPEATER										0x05
#define		NON_DISPLAY_SINK									0x06
#define		POWER_NEUTRAL_SINK									0x07
#define		OTHER_DEV_CAT										0x80

#define		MHL_DEV_CAP_ADOPTER_IDH_REG_OFFSET				0x03

#define		MHL_DEV_CAP_ADOPTER_IDL_REG_OFFSET				0x04

#define		MHL_DEV_CAP_VID_LINK_MODE_REG_OFFSET			0x05
#define		SUPP_RGB444											(0x01 << 0)
#define		SUPP_YCBCR444										(0x01 << 1)
#define		SUPP_YCBCR422										(0x01 << 2)
#define		SUPP_PPIXEL											(0x01 << 3)
#define		SUPP_ISLANDS										(0x01 << 4)
#define     SUPP_VGA											(0x01 << 5)

#define		MHL_DEV_CAP_AUD_LINK_MODE_REG_OFFSET			0x06
#define		AUD_2CH												(0x01 << 0)
#define		AUD_8CH												(0x01 << 1)

#define		MHL_DEV_CAP_VIDEO_TYPE_REG_OFFSET				0x07
#define		VT_GRAPHICS											(0x01 << 0)
#define		VT_PHOTO											(0x01 << 1)
#define		VT_CINEMA											(0x01 << 2)
#define		VT_GAME												(0x01 << 3)
#define		SUPP_VT												(0x01 << 7)


#define		MHL_DEV_CAP_LOG_DEV_MAP_REG_OFFSET				0x08
#define		LD_DISPLAY											(0x01 << 0)
#define		LD_VIDEO											(0x01 << 1)
#define		LD_AUDIO											(0x01 << 2)
#define		LD_MEDIA											(0x01 << 3)
#define		LD_TUNER											(0x01 << 4)
#define		LD_RECORD											(0x01 << 5)
#define		LD_SPEAKER											(0x01 << 6)
#define		LD_GUI												(0x01 << 7)

#define		MHL_DEV_CAP_BANDWIDTH_REG_OFFSET				0x09

#define		MHL_DEV_CAP_FEATURE_FLAG_REG_OFFSET				0x0A
#define		RCP_SUPPORT											(0x01 << 0)
#define		RAP_SUPPORT											(0x01 << 1)



//------------------------------------------------------------------------------
//
// MHL Specs defined registers in device capability set
//
//
typedef struct {
	unsigned char	mhl_devcap_version;					// 0x00
	unsigned char	mhl_devcap_cbus_version;			// 0x01
	unsigned char	mhl_devcap_device_category;			// 0x02
	unsigned char	mhl_devcap_power_supply_capacity;	// 0x03
   	unsigned char	mhl_devcap_power_supply_provided;	// 0x04
   	unsigned char	mhl_devcap_video_link_mode_support;	// 0x05
   	unsigned char	mhl_devcap_audio_link_mode_support;	// 0x06
   	unsigned char	mhl_devcap_hdcp_status;				// 0x07
   	unsigned char	mhl_devcap_logical_device_map;		// 0x08
   	unsigned char	mhl_devcap_link_bandwidth_limit;	// 0x09
   	unsigned char	mhl_devcap_reserved_1;				// 0x0a
   	unsigned char	mhl_devcap_reserved_2;				// 0x0b
   	unsigned char	mhl_devcap_reserved_3;				// 0x0c
   	unsigned char	mhl_devcap_scratchpad_size;			// 0x0d
   	unsigned char	mhl_devcap_interrupt_size;			// 0x0e
   	unsigned char	mhl_devcap_devcap_size;				// 0x0f

} mhl_devcap_t;
//------------------------------------------------------------------------------
//
// MHL Specs defined registers for interrupts
//
//
typedef struct {

	unsigned char	mhl_intr_0;		// 0x00
	unsigned char	mhl_intr_1;		// 0x01
	unsigned char	mhl_intr_2;		// 0x02
	unsigned char	mhl_intr_3;		// 0x03

} mhl_interrupt_t;
//------------------------------------------------------------------------------
//
// MHL Specs defined registers for status
//
//
typedef struct {

	unsigned char	mhl_status_0;	// 0x00
	unsigned char	mhl_status_1;	// 0x01
	unsigned char	mhl_status_2;	// 0x02
	unsigned char	mhl_status_3;	// 0x03

} mhl_status_t;
//------------------------------------------------------------------------------
//
// MHL Specs defined registers for local scratchpad registers
//
//
typedef struct {

	unsigned char	mhl_scratchpad[16];

} mhl_scratchpad_t;
//------------------------------------------------------------------------------

//------- END OF DEFINES -------------
#endif	// __SI_CBUS_DEFS_H__
