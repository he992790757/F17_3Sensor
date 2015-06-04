
/***************************************************************************************
****************************************************************************************
* FILE		: led.h
* Description	: 
*			  
* Copyright (c) 2013 by XXX. All Rights Reserved.
* 
* History:
* Version		Name       		Date			Description
   0.1		XXX	2013/08/20	Initial Version
   
****************************************************************************************
****************************************************************************************/


#ifndef __LED_H__
#define __LED_H__

#ifdef  __LED
#define LED_EXT 
#else 
#define LED_EXT extern 
#endif 

#include"stdint.h"


void Bot_IR_On(void);
void Bot_W_On(void);
void C608_On(void);
void Double_UV_On(void);
void Left_IR850_On(void);
void Left_W_On(void);
void  Light_Init(void);
void Right_IR770_On(void);
void Right_IR850_On(void);
void Right_Laser_On(void);
void Right_UV_On(void);
void Right_W_On(void);
void Top_IR850_On(void);
void Top_IR940_On(void);
void Top_IR940_On_test(void);
void Top_W_On(void);
void CheckLight(void);
void Double_WT_UV_On(void) ; 
void Double_UV_Exposure1_On(void);
void Double_UV_Exposure2_On(void);
#endif

