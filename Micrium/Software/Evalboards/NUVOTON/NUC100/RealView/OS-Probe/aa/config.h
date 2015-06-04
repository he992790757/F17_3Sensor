
#ifndef CONFIG_H
#define CONFIG_H

#include "DrvGPIO.h"	 
#include "global.h"	

///**************键盘定义*************/ 

#define		K5	GPA_10
#define		K6	GPC_1	//	GPA_9
#define		K2	GPC_0	//GPA_8
#define		K7	GPB_4//用于独立按键第六个
#define		K3	GPB_5//用于独立按键第七个
#define		K8	GPB_6// 用于独立按键第一个 
#define		K4	GPB_7// 用于独立按键第二个
#define		K9  GPB_12//
#define		K1  GPA_11//
 

/************各种LED控制IO**********/
#define    	TOP_W       	GPA_2   //顶850红外
#define    	TOP_IR850      	GPA_13//GPA_1   //顶940红外
#define    	TOP_IR940      	GPA_12//GPA_0   //顶白光


#define     BOT_W       	GPA_3   //前紫灯	
#define    	BOT_IR     		GPA_6   //底红我
#define 	RIGHT_UV    	GPE_3  	// GPB_2
#define    	LEFT_UV       	GPA_5   //底白光  
#define    	RIGHT_IR770     GPE_15//GPC_11  //侧白光
#define 	RIGHT_LASER		GPB_9	//激光
#define 	C3_PWR 			GPA_15  //C608




#ifdef AD_16_1000PICS

#define    	LEFT_W      	GPA_7    //侧白光
#define 	RIGHT_W 		GPA_4

#define    	LEFT_IR850     	GPC_7  //侧红外
#define     RIGHT_IR850	    GPC_3     //后紫灯	 --

#define     AV_2660_SW		GPC_11  

#else

#define    	LEFT_W      	GPC_7   //侧白光
#define 	RIGHT_W 		GPC_3
#define    	LEFT_IR850     	GPA_7   //侧红外
#define     RIGHT_IR850	    GPA_8   //GPA_4   //后紫灯	 --

#define     AV_2660_SW		GPA_4  

#endif 

//#define 	JG 			GPA_15
//#define    	TEST_LED    GPB_9  
/***************4639*****************/
#define    	A1      	GPC_8 
#define    	A0      	GPC_9  
#define    	EN       	GPC_10 
/***************IRCUT*****************/
//#define 	CUT_A1 		GPC_0
//#define 	CUT_A2 		GPC_1
//#define 	CUT_B1 		GPC_2


#define		DSP_INIT_PIN  GPB_3


#endif





