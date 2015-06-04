
/***************************************************************************************	
****************************************************************************************	
*                         AD_NUC SERIALS BOARD SUPPORT                                  	
*                                                                                       	
*                    (c) Copyright  2014 by jeson.(j_He).                          	
*                             All Rights Reserved.                                      	
* 																						 	
*                 (With any question and problem,connect author)                	        
*                                                                                       	
* FILE			: dspperf.c																
* VERSION		: V0.2																		
* BY			: jeson.(j_He) 																
* FOR			: AD_NUC Serial 															
* DATE			: 2014/06/21													
* MODE			: Thumb2																	
* Description   : QQ :136353309															
* TOOLCHAIN 	: RealView Microcontroller Development Kit (MDK4.12)						
* 				  Nuvoton Tools																
*																							
*******************************************************************************************
******************************************************************************************/
#define __ DSPPERF
#include "stdio.h"
#include "stdint.h"
#include "ucos_ii.h"
#include "Led.h"
#include "dspperf.h"
#include "global.h"
#include "performance.h"
#include "communication.h"


#define MAX_COLOURFUL_NUM  5   //定义最大彩色照片场景编号
/*==================================================================
* Function	    : PhotoArgvToDsp
* Description	: 发送拍照参数 。 
* Input Para	: 
* Output Para	: 
* Return Value  : 
==================================================================*/
void PhotoArgvToDsp(uint8_t SceNum)
{

	        Dsp_Send_Data(0xFF,SceNum,(uint8_t)((System.Dsp.photo.Scene[SceNum].WB1)),(uint8_t)((System.Dsp.photo.Scene[SceNum].WB2)),D_NON); //白平衡
            OSTimeDly(10); 

			Scen_Send(0xD7,System.Dsp.photo.Scene[SceNum].Sharpness) ; 		    //锐度
            OSTimeDly(10); 
            Scen_Send(0xDA,System.Dsp.photo.Scene[SceNum].Contrast) ; 		    //对比度
            OSTimeDly(10); 
            Scen_Send(0xD9,System.Dsp.photo.Scene[SceNum].Brightness) ; 		//亮度
            OSTimeDly(10); 
			Scen_Send(0xD8,System.Dsp.photo.Scene[SceNum].Saturation) ;			//饱和度
			OSTimeDly(10); 

  	        Dsp_Send_Data(0xFB,SceNum,(uint8_t)((System.Dsp.photo.Scene[SceNum].FB1)),(uint8_t)((System.Dsp.photo.Scene[SceNum].FB2)),D_NON); //曝光度
            OSTimeDly(10); 
 	        Dsp_Send_Data(0xFC,SceNum,(uint8_t)((System.Dsp.photo.Scene[SceNum].FC1)),(uint8_t)((System.Dsp.photo.Scene[SceNum].FC2)),D_NON); //曝光时间
            OSTimeDly(10); 
            if(SceNum <=5)  Scen_Send(SceNum,0x01 ) ; 
            else  Scen_Send(SceNum,0x03 ) ; 	
            OSTimeDly(10); 
			GR_DBG_PRINTF("\n\nScene is %x %x %x %x %x %x %x %x %x %x %x\n\n ",
									SceNum,
									System.Dsp.photo.Scene[SceNum].FB1,
									System.Dsp.photo.Scene[SceNum].FB2,
									System.Dsp.photo.Scene[SceNum].FC1,
									System.Dsp.photo.Scene[SceNum].FC2,
									System.Dsp.photo.Scene[SceNum].Sharpness,
									System.Dsp.photo.Scene[SceNum].Contrast,
									System.Dsp.photo.Scene[SceNum].Brightness,
									System.Dsp.photo.Scene[SceNum].Saturation,
									System.Dsp.photo.Scene[SceNum].WB1,
									System.Dsp.photo.Scene[SceNum].WB2
									);
			Select_Send(0x96);			 
			OSTimeDly(100);
			Scen_Send(0xE6, SceNum); 														
			OSTimeDly(400);		
}

void ArguPriorExposure()
{
    
	switch(System.Dsp.photo.Flag)
	{
        case G_SENCE_DB_UV      :   Double_UV_On()  ; break ; 
        case G_SENCE_WT         :   Top_W_On()      ; break ; 	
        case G_SENCE_L_W 	    :   Left_W_On()     ; break ; 
        case G_SENCE_R_W 	    :   Right_IR850_On(); break ; 
        case G_SENCE_B_W 	    :   Bot_W_On()      ; break ;  
        	 
        case G_SENCE_T_IR940 	:  	Top_IR940_On()  ; break ; 
        case G_SENCE_T_IR850	:  	Top_IR850_On()  ; break ; 
        case G_SENCE_L_IR 	  	:	Left_IR850_On() ; break ; 
        case G_SENCE_B_IR 	   	:   Bot_IR_On()     ; break ; 
        case G_SENCE_R_IR	  	: 	Right_IR850_On(); break ; 
        default :return  ; 
	}
    OSTimeDly(100); 
 //	GR_DBG_PRINTF("\n\nArguPriorExposure IN \n\n");	
    if(System.Dsp.photo.Flag != 0 )
    {     
        PhotoArgvToDsp(System.Dsp.photo.Flag);  // 矫正		
		System.Dsp.photo.Flag = 0 ; 
 //       GR_DBG_PRINTF("\nPhotoArgvToDsp IN \n\n");	
    }

    ModifyInfo() ; 

	CheckMode();   
}


void PhotoArgvToDspAdjust(uint8_t SceNum)
{

	        Dsp_Send_Data(0xFF,SceNum,(uint8_t)((System.Dsp.photo.Scene[SceNum].WB1)),(uint8_t)((System.Dsp.photo.Scene[SceNum].WB2)),D_NON); //白平衡
            OSTimeDly(10); 

			Scen_Send(0xD7,System.Dsp.photo.Scene[SceNum].Sharpness) ; 		    //锐度
            OSTimeDly(10); 
            Scen_Send(0xDA,System.Dsp.photo.Scene[SceNum].Contrast) ; 		    //对比度
            OSTimeDly(10); 
            Scen_Send(0xD9,System.Dsp.photo.Scene[SceNum].Brightness) ; 		//亮度
            OSTimeDly(10); 
			Scen_Send(0xD8,System.Dsp.photo.Scene[SceNum].Saturation) ;			//饱和度
			OSTimeDly(10); 

  	        Dsp_Send_Data(0xFB,SceNum,(uint8_t)((System.Dsp.photo.Scene[SceNum].FB1)),(uint8_t)((System.Dsp.photo.Scene[SceNum].FB2)),D_NON); //曝光度
            OSTimeDly(10); 
 	        Dsp_Send_Data(0xFC,SceNum,(uint8_t)((System.Dsp.photo.Scene[SceNum].FC1)),(uint8_t)((System.Dsp.photo.Scene[SceNum].FC2)),D_NON); //曝光时间
            OSTimeDly(10);
			Scen_Send(SceNum,(uint8_t)(System.Dsp.photo.Scene[SceNum].Mode));
			OSTimeDly(10);  	

//			Select_Send(0x96);			 
//			OSTimeDly(100);
//			Scen_Send(0xE6, SceNum); 														
//			OSTimeDly(400);		
}

void ArguPriorExposureAdjust()
{
    
//	switch(System.Dsp.photo.Flag)
//	{
//        case G_SENCE_DB_UV      :   Double_UV_On()  ; break ; 
//        case G_SENCE_WT         :   Top_W_On()      ; break ; 	
//        case G_SENCE_L_W 	    :   Left_W_On()     ; break ; 
//        case G_SENCE_R_W 	    :   Right_IR850_On(); break ; 
//        case G_SENCE_B_W 	    :   Bot_W_On()      ; break ;  
//        	 
//        case G_SENCE_T_IR940 	:  	Top_IR940_On()  ; break ; 
//        case G_SENCE_T_IR850	:  	Top_IR850_On()  ; break ; 
//        case G_SENCE_L_IR 	  	:	Left_IR850_On() ; break ; 
//        case G_SENCE_B_IR 	   	:   Bot_IR_On()     ; break ; 
//        case G_SENCE_R_IR	  	: 	Right_IR850_On(); break ; 
//        default :return  ; 
//	}
//    OSTimeDly(100); 
 //	GR_DBG_PRINTF("\n\nArguPriorExposure IN \n\n");	
    if(System.Dsp.photo.Flag != 0 )
    {     
        PhotoArgvToDspAdjust(System.Dsp.photo.Flag);  // 矫正		
		System.Dsp.photo.Flag = 0 ; 
 //       GR_DBG_PRINTF("\nPhotoArgvToDsp IN \n\n");	
    }

 //   ModifyInfo() ; 

//	CheckMode();   
}
