#ifndef _MAPP_EDID_TABLE_H_
#define _MAPP_EDID_TABLE_H_

#include "Board.h"

#if (ENABLE_DDC_RAM)

#ifndef ENABLE_EDID_HDMI_1p4
    #define ENABLE_EDID_HDMI_1p4 (ENABLE_HDMI_4K_2K||ENABLE_3D_PROCESS)
#endif

#define ENABLE_EDID_SUPPORT_DDP_SAD (ENABLE_DOLBY_BULLETIN24&&ENABLE_DYNAMIC_EDID)

//-------------------------------------------------------------------

typedef enum
{
    E_EDID_TBL_VGA,

    E_EDID_TBL_HDMI_1p3_1p4,

#if(ENABLE_HDMI_4K_2K||ENABLE_EDID_SWITCH) // 4k X 2k
    E_EDID_TBL_HDMI_2p0,
#endif

    E_EDID_TBL_UNKNOWN,

} EnuEdidTblSel;

BOOL MApp_Edid_Get_Table(EnuEdidTblSel eEdidTblSel, U8 u8PhyAddr, U8* pu8EdidTbl, U8* pu8PhyAddrPos);

#define MApp_Edid_Get_VGATable(edidBuf)  (MApp_Edid_Get_Table(E_EDID_TBL_VGA, 0, edidBuf, NULL))

#if (ENABLE_EDID_SUPPORT_DDP_SAD)
void MApp_Edid_Set_EnableAudioDDP(BOOL bEnAudioDDP, U8* pu8SAD );
#endif

#endif // ENABLE_DDC_RAM

#endif // _MAPP_EDID_TABLE_H_

