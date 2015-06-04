#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "global.h"

#ifdef __COMMUNICATION
#define  COMMU_EXT 
#else 
#define COMMU_EXT extern 
#endif 

COMMU_EXT ENUM_USB_CON USB_STATUS;


void DSP_INIT(void);
void SendByte(uint8_t data); 
unsigned char  DSP_SEND(uint8_t cnt, const uint8_t *DSP_DATA);
unsigned char  DSP_SEND_USB(uint8_t cnt, uint8_t *DSP_DATA);
unsigned char  Scen_Send(uint8_t Scen, uint8_t State);
unsigned char  Select_Send(uint8_t Select_data);
unsigned char  SHOW_SCREEN(uint8_t comm,  const uint8_t *DSP_DATA);
unsigned char  SHOW_SCREENA(uint8_t comm, uint8_t cnt, const uint8_t *DSP_DATA) ;
unsigned char  SHOW_SCREEN_LONG(uint8_t comm,/* uint8_t cnt,*/ const uint8_t *DSP_DATA1,const uint8_t *DSP_DATA2);
unsigned char  Dsp_Send_Data(uint8_t data1,uint8_t data2,uint8_t data3,uint8_t data4,uint8_t data5);
void UART_INT_HANDLE(uint32_t u32IntStatus);
void SendString(void);
unsigned char  DSP_SENDA(uint8_t cnt, volatile uint8_t *DSP_DATA);
unsigned char  DSP_SENDB(uint8_t CMD,uint8_t Foward, const uint8_t *DSP_DATA);
int32_t DrvFMC_Read(uint32_t u32addr, uint32_t * u32data);
int32_t DrvFMC_Erase(uint32_t u32addr);
int32_t DrvFMC_Write(uint32_t u32addr, uint32_t u32data);
int32_t DrvFMC_WriteConfig(uint32_t u32data0, uint32_t u32data1);
void DrvFMC_DisableISP(void);
void DrvFMC_EnableISP(void);
uint32_t DrvFMC_ReadDataFlashBaseAddr(void);

unsigned char  SHOW_SCREENW(uint8_t comm,/* uint8_t cnt,*/ const uint8_t *DSP_DATA); 
unsigned char  DSP_SENDBW(uint8_t CMD,uint8_t Foward, const uint8_t *DSP_DATA); 
unsigned char  SHOW_SCREEN_T_W(uint8_t comm, uint8_t time, const uint8_t *DSP_DATA);

unsigned char  Select_Send_LONG(uint8_t Select_data) ;
#endif

