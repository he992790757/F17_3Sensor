
/***************************************************************************************
****************************************************************************************
* FILE		: performance.h
* Description	: 
*			  
* Copyright (c) 2013 by XXX. All Rights Reserved.
* 
* History:
* Version		Name       		Date			Description
   0.1		XXX	2013/08/21	Initial Version
   
****************************************************************************************
****************************************************************************************/


#ifndef __PERFORMANCE_H__
#define __PERFORMANCE_H__
#include "stdint.h"
#include "global.h"
#include <wchar.h>
#include <wctype.h>
#ifdef  __PERFORMANCE 
#define PERFOR_EXT 
#else 
#define PERFOR_EXT  extern 
#endif 

PERFOR_EXT  uint8_t ADJ_ExpSetFB[4]; 	 
PERFOR_EXT  uint8_t ADJ_ExpSetFC[4];
PERFOR_EXT  uint8_t	gu8AdcIntFlag ;
PERFOR_EXT  uint8_t	char_array[34] ;
PERFOR_EXT  uint16_t  Local_SignOutCount ;

PERFOR_EXT 	uint8_t	MvtempDec1  ; 	 //翻页次数记录
PERFOR_EXT 	uint8_t	MvtempDec  ;	 //向右翻页完毕
//PERFOR_EXT 	uint8_t	PhotoNum  ;		 //照片的张数    //4 5 
//PERFOR_EXT 	uint8_t	MvtempDec1_F2  ; 
//PERFOR_EXT 	uint8_t	MvtempDec_F2  ;
//
//PERFOR_EXT 	uint8_t	MvtempDec1_F3  ; 
//PERFOR_EXT 	uint8_t	MvtempDec_F3  ;
//
//PERFOR_EXT 	uint8_t	MvtempDec1_F4  ; 
//PERFOR_EXT 	uint8_t	MvtempDec_F4  ;

//#define PH_SENCE_TOP_WT_70		0x09 
//#define PH_SENCE_TOP_UV_70		0x02 
//#define PH_SENCE_TOP_IR940_70	0x03 
//
//#define PH_SENCE_L_IR850		0x04 
//
////#define PH_SENCE_TOP_UV_71		0x04 
//#define PH_SENCE_TOP_WT_72		0x05 
//#define PH_SENCE_TOP_UV_72		0x06 
//#define PH_SENCE_TOP_IR770_72	0x07 

//#define PH_SENCE_TOP_WT_70		0x08 
//#define PH_SENCE_TOP_WT_70		0x09 
//#define PH_SENCE_TOP_WT_70		0x0A 
//#define PH_SENCE_TOP_WT_70	0x0B
//#define PH_SENCE_TOP_WT_70	0x0C 
//#define PH_SENCE_TOP_WT_70	0x0D 
//#define PH_SENCE_TOP_WT_70	0x0E 
//#define PH_SENCE_TOP_WT_70	0x0F 
//#define PH_SENCE_TOP_WT_70	0x11
//#define PH_SENCE_TOP_WT_70	0x12 
//#define PH_SENCE_TOP_WT_70	0x13 
//#define PH_SENCE_TOP_WT_70	0x14 
//#define PH_SENCE_TOP_WT_70	0x15 
//#define PH_SENCE_TOP_WT_70	0x16 
//#define PH_SENCE_TOP_WT_70	0x17 
//#define PH_SENCE_TOP_WT_70	0x18 
//#define PH_SENCE_TOP_WT_70	0x19 
//#define PH_SENCE_TOP_WT_70	0x1A 
//#define PH_SENCE_TOP_WT_70	0x1B 
//#define PH_SENCE_TOP_WT_70	0x1C 
//#define PH_SENCE_TOP_WT_70	0x1D 
//#define PH_SENCE_TOP_WT_70	0x1E 
//#define PH_SENCE_TOP_WT_70	0x1F 




void VerifyPassword(uint8_t keyReturnValue,void (*Fuc)(),void (*PasswdFinish)() );
void ChangePassWord(void);
void PhotoDelAll(void) ;
void PhotoDelOne(void);
void PhotographEight(void);
void PhotographFour(void);
void PhotographOne(void);
void PhotoMvDown(void);
void PhotoMvLeft(void);
void PhotoMvRight(void);
void PhotoMvUp(void);
void PhotoNext(void);
void PhotoPrevious(void);
void PriorExposure(void);
void Sensor1(void);
void Sensor2(void);
void Sensor3(void);
void TfMode(void);
void ViewMode(void);
void ViewMode_F1(void);
void ViewMode_F2(void);
void ViewMode_F3(void);
void ViewMode_F4(void);


void CheckMode(void);
void PccamMode(void);
void Vir_Init(void);
void Vir_Init_Update(void);
void SystemReadBCKData(void);
void SystemWriteBCKData(void); 
void ConfigBCK(void) ; 
void PhotoZoomUp(void) ;
void PhotoZoomDown(void) ;
void PhotoAutoView(void);
void Zhuanfa(void);
void TimeSet(void) ;
void UV365_70ExpSet(void);
void UV365_71ExpSet(void);
void UV365_72ExpSet(void);
void QueryInfo(void);
void ModifyInfo(void) ;
void MacSleep(void);
void MacWakeup(void) ;
void Slp_enable(void) ;
void Slp_disable(void) ;
void CycleViewFuc(void);
void Format_SDcard(void);
//uint32_t  ADC_Dispose(uint8_t Channel);
uint8_t ADC_Checking(uint32_t CHANNEL_VOLT,uint32_t ERR_RANGE ); 
void SYS_Error(void) ; 
void DspRst(void) ;
void ShowZoom(void);
void Check_View_Zoom(ENUM_DSP_ZOOM NUM);
//void ApCombine(const uint8_t* DataA,const uint8_t* DataB, uint8_t* DataC); 

uint8_t* WcharToChar(wchar_t *p);
void SHOW_SCREEN_WC_NUM(uint8_t comm,wchar_t *p,uint16_t NUM,wchar_t *s,uint16_t NUM1);
void ExtBlackScreen(void); 
void ShowChkPhotOne(void);
void ShowChkPhotAgain(void); 
void Photo_SignAndCount(void) ;
void Photo_SignAndChk(void)	;
void PhotographFour_Sign(void) ;
void  ShowLeftBtmNum(void) ;
void PhotoNumAdjust(void);
void XyZoomFuc(void) ;

extern volatile uint8_t DeepCompression ; 

#endif /*_PERFORMANCE_H_*/





