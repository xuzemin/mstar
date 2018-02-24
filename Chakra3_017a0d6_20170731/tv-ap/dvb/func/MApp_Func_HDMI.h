
#ifndef _MAPP_FUNC_HDMI_H_
#define _MAPP_FUNC_HDMI_H_

#include "Board.h"

#include "apiXC_Sys.h"

#if ENABLE_EDID_SWITCH
void MApp_Func_HDMI_Set_EdidSel(E_USER_HDMI_EDID_SEL eUserEdid);
#endif

#if(ENABLE_CEC)
BOOLEAN MApp_CEC_Set_Enable(BOOLEAN bCecEnable);
#endif


#endif // _MAPP_FUNC_HDMI_H_

