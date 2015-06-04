#ifndef __TIME_H__
#define __TIME_H__
#include<stdint.h>		

#ifdef 	__EXT_TIME__
#define EXT_TIME 
#else 
#define EXT_TIME extern 
#endif 



typedef struct tm
{
	uint16_t year ; 
	uint8_t month ; 
	uint8_t day ; 
	uint8_t week ; 
	uint8_t hour ; 
	uint8_t min ; 
	uint8_t sec ; 
}tm; 

EXT_TIME tm NowTime ; 
uint32_t sTime(tm time); 

#endif 
