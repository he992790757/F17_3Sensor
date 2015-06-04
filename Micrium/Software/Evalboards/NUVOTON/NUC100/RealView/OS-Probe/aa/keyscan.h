#ifndef KEYSCAN_H
#define KEYSCAN_H

#include <stdint.h>

#ifdef __KEYSCAN 
#define KEYSCAN_EXT 
#else
#define KEYSCAN_EXT extern 
#endif 

KEYSCAN_EXT uint8_t 	Keylong  ; 

uint8_t KeyScan(void);


//void Key_time_clr(void);
//void Judge_press(void);
//void Key_time_clr_all(void);		

//extern volatile uint8_t lens_flag;
//extern volatile uint8_t cut_flagA;
//extern volatile uint8_t cut_flagB;


//extern uint8_t 	UV_flag;
//extern uint8_t 	Keylong;		//长按键标志
//extern uint8_t 	cut_flage;
//extern uint8_t 	long_key_zood_flage;
//extern volatile uint8_t 	AV_flag;

///*************其它变量**************/
//extern uint8_t 	IR_850_940;		// IR850，940切换标志
//extern uint8_t 	standby;  		//待机标志位
//extern uint8_t 	ViewMode;			//预览模式和回放模式标志位
//extern uint8_t	B_Sensor;			//摄像机切换,小视窗或大视窗
//extern uint8_t 	Dzoom;			//切换到数码变焦标志位hby1029 add
//extern uint8_t 	PictureMode;		//切换黑白和彩色图象 =0为彩色 hby1109 add
//extern uint8_t 	Stand_by_timer;	//待机定时器

///**************按键次数寄存*************/

//extern uint8_t 	K1_time;
//extern uint8_t 	K2_time;
//extern uint8_t 	K3_time;
//extern uint8_t 	K4_time;
//extern uint8_t 	K5_time;
//extern uint8_t 	K6_time;
//extern uint8_t 	K7_time;
//extern uint8_t  K8_time;
//extern uint8_t 	K9_time;
//extern uint8_t 	K10_time;
//extern uint8_t 	K11_time;
//extern uint8_t 	K12_time;
//extern uint8_t 	K13_time;
//extern uint8_t 	K14_time;

//extern uint8_t		key_z;

//extern uint32_t 	press_time;
//extern uint32_t 	LED_STATE;

//int32_t DrvFMC_Read(uint32_t u32addr, uint32_t * u32data);
//int32_t DrvFMC_Erase(uint32_t u32addr);
//int32_t DrvFMC_Write(uint32_t u32addr, uint32_t u32data);
//int32_t DrvFMC_WriteConfig(uint32_t u32data0, uint32_t u32data1);
//void DrvFMC_DisableISP(void);
//void DrvFMC_EnableISP(void);

#endif


