/***************************************************************************************/
/* FILE: si2158_L0_TV_Chassis.h                                                        */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/***************************************************************************************/
#ifndef SILABS_L0_SI2158_API_H
#define SILABS_L0_SI2158_API_H

#include "Si2158_Commands.h" 
#include "Si2158_Properties.h" 
#include "Si2158_typedefs.h"
#include "../LGIT_Tuner_bsp.h"

#if defined (__cplusplus)
extern "C" {
#endif

extern void LGIT_dbg(const char *fmt, ...);
//#define SiTRACE LGIT_dbg
#define SiTraceConfiguration LGIT_dbg

void	Si2158_L0_Init                  (Si2158_L0_Context *pContext);
void	Si2158_L0_SetAddress            (Si2158_L0_Context *pContext, unsigned int add, int addSize);
void	system_wait_ms_si2158              (int time_ms);

int		Si2158_L0_ReadCommandBytes      (Si2158_L0_Context* i2c, int iNbBytes, unsigned char *pucDataBuffer) ;
int		Si2158_L0_WriteCommandBytes     (Si2158_L0_Context* i2c, int iNbBytes, unsigned char *pucDataBuffer) ;
int     system_time_si2158        (void);

#if defined (__cplusplus)
};
#endif

#endif
