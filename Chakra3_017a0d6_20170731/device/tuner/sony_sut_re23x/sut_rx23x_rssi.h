/******************************************************************************
 *   $ Copyright $ Sony Corporation
 *-----------------------------------------------------------------------------
 *   File Name   : $File: sut_rx23x_rssi.h $
 *   Modified    : $Date: 2013/10/18 $ By $Author: $
 *   Revision    : $Revision: 0.60 $
 *   Description : SUT-Rx23x Tuner Control Sample Code
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

#ifndef _SUT_RX23X_RSSI_H_
#define _SUT_RX23X_RSSI_H_ 

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

const sony_ascot3_rx23x_ModuleParam RE231_RSSI_TABLE[] = {
    { 692000,  301 },
    { 532000,  315 },
    { 464000,  458 },
    { 350000,  236 },
    { 335000,  216 },
    { 320000,  305 },
    { 261000,  224 },
    { 215000,  212 },
    { 184000,  326 },
    { 172000,  457 },
    { 150000,  524 },
    { 122000,  443 },
    {  86000,  334 },
    {  65000,  364 },
    {  52000,  358 },
    {      0,  534 }
};

const sony_ascot3_rx23x_ModuleParam RA231_RSSI_TABLE[] = {
    { 692000,  293 },
    { 532000,  295 },
    { 464000,  471 },
    { 350000,  217 },
    { 335000,  201 },
    { 320000,  284 },
    { 261000,  219 },
    { 215000,  199 },
    { 184000,  314 },
    { 172000,  441 },
    { 150000,  481 },
    { 122000,  419 },
    {  86000,  322 },
    {  65000,  344 },
    {  52000,  326 },
    {      0,  502 }
};

const sony_ascot3_rx23x_ModuleParam RB231_TERR_RSSI_TABLE[] = {
    { 692000,  316 },
    { 532000,  334 },
    { 464000,  601 },
    { 350000,  358 },
    { 335000,  340 },
    { 320000,  427 },
    { 261000,  339 },
    { 215000,  315 },
    { 184000,  414 },
    { 172000,  540 },
    { 150000,  620 },
    { 122000,  543 },
    {  86000,  440 },
    {  65000,  456 },
    {  52000,  435 },
    {      0,  448 }
};

const sony_ascot3_rx23x_ModuleParam RB231_CABLE_RSSI_TABLE[] = {
    { 692000,  326 },
    { 532000,  342 },
    { 464000,  605 },
    { 350000,  369 },
    { 335000,  351 },
    { 320000,  442 },
    { 261000,  348 },
    { 215000,  327 },
    { 184000,  425 },
    { 172000,  551 },
    { 150000,  626 },
    { 122000,  545 },
    {  86000,  441 },
    {  65000,  448 },
    {  52000,  411 },
    {      0,  405 }
};

const sony_ascot3_rx23x_ModuleParam DEFAULT[] = {
    {      0,    0 }
};


#endif