/******************************************************************************
 *   $ Copyright $ Sony Corporation
 *-----------------------------------------------------------------------------
 *   File Name   : $File: sut_pex44_rssi.h $
 *   Modified    : $Date: 2014/04/21 $ By $Author: $
 *   Revision    : $Revision: 1.0.0.0 $
 *   Description : SUT-PE241/541 Tuner Control Sample Code
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


#ifndef _SUT_PEX41_RSSI_H_
#define _SUT_PEX41_RSSI_H_ 

typedef struct sony_helene_ModuleParam {
    UINT32 freq;
    INT16  param;
} sony_helene_ModuleParam;

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

const sony_helene_ModuleParam PE241_RSSI_TABLE[] = {
    { 692000,  357 },
    { 532000,  354 },
    { 464000,  474 },
    { 350000,  274 },
    { 335000,  260 },
    { 320000,  311 },
    { 261000,  230 },
    { 215000,  278 },
    { 184000,  413 },
    { 172000,  541 },
    { 150000,  569 },
    { 122000,  515 },
    {  86000,  396 },
    {  65000,  399 },
    {  52000,  552 },
    {      0,  775 } 
};

const sony_helene_ModuleParam PE541_LNAON_RSSI_TABLE_1ST[] = {
    { 692000,  803 },
    { 532000,  866 },
    { 464000, 1021 },
    { 350000,  786 },
    { 335000,  754 },
    { 320000,  794 },
    { 261000,  690 },
    { 215000,  718 },
    { 184000,  832 },
    { 172000,  945 },
    { 150000, 1037 },
    { 122000,  914 },
    {  86000,  737 },
    {  65000,  653 },
    {  52000,  843 },
    {      0, 1132 }
};

const sony_helene_ModuleParam PE541_LNAOFF_RSSI_TABLE_1ST[] = {
    { 692000, 1019 },
    { 532000,  990 },
    { 464000, 1125 },
    { 350000,  956 },
    { 335000,  935 },
    { 320000,  982 },
    { 261000,  900 },
    { 215000,  928 },
    { 184000, 1036 },
    { 172000, 1144 },
    { 150000, 1240 },
    { 122000, 1181 },
    {  86000, 1096 },
    {  65000, 1122 },
    {  52000, 1286 },
    {  0    , 1482 }

};

const sony_helene_ModuleParam PE541_LNAON_RSSI_TABLE_2ND[] = {
    { 692000,  484 },
    { 532000,  560 },
    { 464000,  708 },
    { 350000,  457 },
    { 335000,  428 },
    { 320000,  494 },
    { 261000,  371 },
    { 215000,  418 },
    { 184000,  551 },
    { 172000,  681 },
    { 150000,  786 },
    { 122000,  709 },
    {  86000,  602 },
    {  65000,  620 },
    {  52000,  804 },
    {      0, 1017 }
};

const sony_helene_ModuleParam PE541_LNAOFF_RSSI_TABLE_2ND[] = {
    { 692000,  672 },
    { 532000,  690 },
    { 464000,  877 },
    { 350000,  708 },
    { 335000,  687 },
    { 320000,  758 },
    { 261000,  648 },
    { 215000,  680 },
    { 184000,  797 },
    { 172000,  910 },
    { 150000, 1009 },
    { 122000,  947 },
    {  86000,  862 },
    {  65000,  890 },
    {  52000, 1061 },
    {      0, 1265 }

};

const sony_helene_ModuleParam DEFAULT[] = {
    {      0,    0 }
};


#endif
