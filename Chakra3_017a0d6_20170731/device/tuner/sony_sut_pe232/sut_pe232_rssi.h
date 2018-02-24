/******************************************************************************
 *   $ Copyright $ Sony Corporation
 *-----------------------------------------------------------------------------
 *   File Name   : $File: sut_pe232_rssi.h $
 *   Modified    : $Date: 2013/07/15 $ By $Author: $
 *   Revision    : $Revision: 0.40 $
 *   Description : SUT-PE232 Tuner Control Sample Code
 *-----------------------------------------------------------------------------
 * This program may contain information about unfinished products and is subject
 * to change without notice.
 * Sony cannot assume responsibility for any problems arising out of the
 * use of the program
 *****************************************************************************/
/******************************************************************************
 *   includes:
 *    - system includes
 *    - application includes
 *****************************************************************************/

#ifndef _SUT_PE232_RSSI_H_
#define _SUT_PE232_RSSI_H_ 

typedef struct sony_ascot3_rx23x_ModuleParam {
    UINT32 freq;
    INT16  param;
} sony_ascot3_rx23x_ModuleParam;

const INT16 demod_iftgt[28] = {
       0, /* SONY_ASCOT3_TV_SYSTEM_UNKNOWN */
       0, /* SONY_ASCOT3_ATV_MN_EIAJ   */
       0, /* SONY_ASCOT3_ATV_MN_SAP    */
       0, /* SONY_ASCOT3_ATV_MN_A2     */
       0, /* SONY_ASCOT3_ATV_BG        */
       0, /* SONY_ASCOT3_ATV_I         */
       0, /* SONY_ASCOT3_ATV_DK        */
       0, /* SONY_ASCOT3_ATV_L         */
       0, /* SONY_ASCOT3_ATV_L_DASH    */

       0, /* SONY_ASCOT3_DTV_8VSB      */
       0, /* SONY_ASCOT3_DTV_QAM       */
    -450, /* SONY_ASCOT3_DTV_ISDBT_6   */
    -450, /* SONY_ASCOT3_DTV_ISDBT_7   */
    -450, /* SONY_ASCOT3_DTV_ISDBT_8   */
    -400, /* SONY_ASCOT3_DTV_DVBT_5    */
    -400, /* SONY_ASCOT3_DTV_DVBT_6    */
    -400, /* SONY_ASCOT3_DTV_DVBT_7    */
    -400, /* SONY_ASCOT3_DTV_DVBT_8    */
    -400, /* SONY_ASCOT3_DTV_DVBT2_1_7 */
    -400, /* SONY_ASCOT3_DTV_DVBT2_5   */
    -400, /* SONY_ASCOT3_DTV_DVBT2_6   */
    -400, /* SONY_ASCOT3_DTV_DVBT2_7   */
    -400, /* SONY_ASCOT3_DTV_DVBT2_8   */
    -550, /* SONY_ASCOT3_DTV_DVBC_6    */
    -550, /* SONY_ASCOT3_DTV_DVBC_8    */
    -400, /* SONY_ASCOT3_DTV_DVBC2_6   */
    -400, /* SONY_ASCOT3_DTV_DVBC2_8   */
    -900  /* SONY_ASCOT3_DTV_DTMB      */
};

const sony_ascot3_rx23x_ModuleParam PE232_LNAON_RSSI_TABLE[] = {
    { 800000,  -279 },
    { 630000,  -365 },
    { 530000,  -471 },
    { 464000,  -488 },
    { 350000,  -747 },
    { 320000,  -646 },
    { 196000,  -722 },
    { 130000,  -504 },
    {  65000,  -645 },
    {  55000,  -651 },
    {      0,  -495 }
};

const sony_ascot3_rx23x_ModuleParam PE232_LNAOFF_RSSI_TABLE[] = {
    { 800000,  819 },
    { 630000,  699 },
    { 530000,  750 },
    { 464000,  845 },
    { 350000,  643 },
    { 320000,  721 },
    { 196000,  591 },
    { 130000,  798 },
    {  65000,  684 },
    {  55000,  681 },
    {      0,  812 }
};

const sony_ascot3_rx23x_ModuleParam DEFAULT[] = {
    {      0,    0 }
};


#endif