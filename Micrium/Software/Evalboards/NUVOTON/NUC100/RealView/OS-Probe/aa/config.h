
#ifndef CONFIG_H
#define CONFIG_H

#include "DrvGPIO.h"	 
#include "global.h"	

///**************���̶���*************/ 

#define		K5	GPA_10
#define		K6	GPC_1	//	GPA_9
#define		K2	GPC_0	//GPA_8
#define		K7	GPB_4//���ڶ�������������
#define		K3	GPB_5//���ڶ����������߸�
#define		K8	GPB_6// ���ڶ���������һ�� 
#define		K4	GPB_7// ���ڶ��������ڶ���
#define		K9  GPB_12//
#define		K1  GPA_11//
 

/************����LED����IO**********/
#define    	TOP_W       	GPA_2   //��850����
#define    	TOP_IR850      	GPA_13//GPA_1   //��940����
#define    	TOP_IR940      	GPA_12//GPA_0   //���׹�


#define     BOT_W       	GPA_3   //ǰ�ϵ�	
#define    	BOT_IR     		GPA_6   //�׺���
#define 	RIGHT_UV    	GPE_3  	// GPB_2
#define    	LEFT_UV       	GPA_5   //�װ׹�  
#define    	RIGHT_IR770     GPE_15//GPC_11  //��׹�
#define 	RIGHT_LASER		GPB_9	//����
#define 	C3_PWR 			GPA_15  //C608




#ifdef AD_16_1000PICS

#define    	LEFT_W      	GPA_7    //��׹�
#define 	RIGHT_W 		GPA_4

#define    	LEFT_IR850     	GPC_7  //�����
#define     RIGHT_IR850	    GPC_3     //���ϵ�	 --

#define     AV_2660_SW		GPC_11  

#else

#define    	LEFT_W      	GPC_7   //��׹�
#define 	RIGHT_W 		GPC_3
#define    	LEFT_IR850     	GPA_7   //�����
#define     RIGHT_IR850	    GPA_8   //GPA_4   //���ϵ�	 --

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





