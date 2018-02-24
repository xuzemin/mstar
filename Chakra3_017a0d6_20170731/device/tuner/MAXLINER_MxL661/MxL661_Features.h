/*******************************************************************************
 *
 * FILE NAME          : MxL661_Features.h
 * 
 * AUTHOR             : Dong Liu
 *  
 * DATE CREATED       : 08/17/2012
 *
 * DESCRIPTION        : This file contains MxL661 device feature definition. 
 *                      User can enable or disable certain macro-definition to 
 *                      add or delete corresponding feature (funtion) 
 *
 *******************************************************************************
 *                Copyright (c) 2012, MaxLinear, Inc.
 ******************************************************************************/

#ifndef __MXL661_TUNER_FEATURES_H__
#define __MXL661_TUNER_FEATURES_H__

/******************************************************************************
   Features List 
******************************************************************************/
// MXL661_ENABLE_MANUAL_AFC is used to protect Tuner AFC program bit while do  
//   application mode over write default. 
// Enable this macro-definition means Tuner AFC feature will be turned on   
//   or turned off by calling MXL661_TUNER_AFC_CFG API.
// Disable this macro-definition means in analog TV mode, tuner AFC function 
//   is always turned on. 
#define MXL661_ENABLE_MANUAL_AFC  	            1    

// MXL661_ENABLE_TELETEXT_SPUR is used enable or disable the feature of "reduce spurs 
//   that caused by teletext broadcast"
// For the application that does not has teletext broadcast, this feature can 
//   be disabled. 
//#define MXL661_ENABLE_TELETEXT_SPUR_FEATURE    1 

// MXL661_CUSTOMER_SPECIFIC_SETTING_1 is used for one customer special setting while 
//   implement application mode setting and channel tune 
//#define MXL661_CUSTOMER_SPECIFIC_SETTING_1   1

// MXL661_CUSTOMER_SPECIFIC_SETTING_2 is used for one customer special setting while 
//   implement channel tune operation
//#define MXL661_CUSTOMER_SPECIFIC_SETTING_2   1

// MXL661_CUSTOMER_SPECIFIC_SETTING_3 is used on one customer platform, it is used to   
//   enable or disable NTSC N+1 block performance improvement.  
#define MXL661_CUSTOMER_SPECIFIC_SETTING_3    1 

// MXL661_ENABLE_BALUNLESS_SPUR_FEATURE is used to enable the spur table with balunless or balun.
// The spur table with balunless will be used when it(MXL661_ENABLE_BALUNLESS_SPUR_FEATURE ) is set 1.
// The spur table with balun will be used when it(MXL661_ENABLE_BALUNLESS_SPUR_FEATURE ) is disabled.
//#define MXL661_ENABLE_BALUNLESS_SPUR_FEATURE    1 

#endif /* __MXL661_TUNER_FEATURES_H__ */




