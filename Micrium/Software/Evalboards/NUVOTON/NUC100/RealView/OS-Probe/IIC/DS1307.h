#ifndef __DS1307_H_
#define __DS1307_H_

#include"Sim_IIC.h"
#include"stdint.h"
#ifdef	__EXT_DS1307
#define EXT_DS 
#else 
#define EXT_DS 	extern
#endif

EXT_DS volatile uint8_t date[7]; 
EXT_DS volatile uint8_t date_dsp[7];


#define DS1307_ADDR  0xD0
void DS1307_Init(void); 
uint8_t  DS1307_WR(volatile uint8_t* DATA);
uint8_t DS1307_RD(volatile uint8_t* DATA);
//void  DS1307_DatChg(void); 
#endif

