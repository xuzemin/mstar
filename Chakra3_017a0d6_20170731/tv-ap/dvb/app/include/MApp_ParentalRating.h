#ifndef _MAPP_PARENTAL_RATING_H_
#define _MAPP_PARENTAL_RATING_H_


#include "Board.h"


#define ENABLE_CHG_CH_DEFAULT_LOCK  0


void MApp_Set_MonitorParental(BOOLEAN bEnable);
BOOLEAN MApp_Get_MonitorParental(void);

#if(ENABLE_DTV)
BOOLEAN MApp_Get_ParentalBlock_state(void);
void MApp_Set_ParentalBlock_state(BOOLEAN bEnable);
void MApp_ParentalRating_PasswordInputMessageHandle(BOOL ActOnOff);
void MApp_ParentalRating_BlockStatus_Monitor(void);

void MApp_ParentalRating_DisableChannel(void);
void MApp_ParentalRating_EnableChannel(void);
#endif

#endif

