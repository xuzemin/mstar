/***************************************************************************************/
/* FILE: Si2176_L0_TV_Chassis.h                                                        */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/***************************************************************************************/
#ifndef SI2176_L0_TV_CHASSIS_H
#define SI2176_L0_TV_CHASSIS_H

/* movd code to remove compile error by yooheeyong 20110523 */
typedef struct L0_Context {
    unsigned char   address;
     int             indexSize;
} L0_Context;

int      system_wait(int time_ms);
int      system_time(void);

void	L0_Init                  (L0_Context *pContext);
void	SendRSTb (void); 
int		L0_ReadCommandBytes      (L0_Context* i2c, int iNbBytes, unsigned char *pucDataBuffer) ;
int		L0_WriteCommandBytes     (L0_Context* i2c, int iNbBytes, unsigned char *pucDataBuffer) ;
#endif
