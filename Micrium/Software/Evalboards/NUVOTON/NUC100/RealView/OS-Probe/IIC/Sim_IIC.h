#ifndef __IIC_SIM_H__
#define __IIC_SIM_H__

	#include "stdint.h"
	#include "DrvGPIO.h"
	#define SCL GPA_9	//GPC_1
	#define SDA GPA_8	//GPC_0
	#define NOP(Perm)  IIcDelay(Perm) 
		
void IIC_SimStart(void);	
void IIC_SimStop(void);
uint8_t IIC_SimSend(uint8_t Perm);
uint8_t IIC_SimRead(void);
void Ack_I2c(uint8_t a); 

	
#endif 	

