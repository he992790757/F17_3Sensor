#define   __LED
#include "Led.h"
#include "config.h"
#include "global.h"
#include "communication.h"
#include <ucos_ii.h>
#include <stdio.h>
#include "performance.h"


const uint8_t UV_Snr1_ExposureEV_FB[] ={0xFB,G_SENCE_DB_UV,0x60,0x60}	;	
const uint8_t UV_Snr1_ExposureEV_FC[] ={0xFC,G_SENCE_DB_UV,0x30,0x30}	;

const uint8_t UV_Snr2_ExposureEV_FB[] ={0xFB,G_SENCE_DB_UV2,0x90,0x90}	;	
const uint8_t UV_Snr2_ExposureEV_FC[] ={0xFC,G_SENCE_DB_UV2,0x50,0x50}	;
const uint8_t test[] = {0x7e,0xa2} ; 


void  Light_Init()
{
	TOP_W       	= 	1 ; 
	TOP_IR850   	= 	1 ; 
	TOP_IR940   	= 	1 ; 
	LEFT_W       	= 	1 ; 
	RIGHT_W 	 	= 	1 ; 
	LEFT_IR850   	=	1 ; 
	RIGHT_IR850	 	= 	1 ;                        
	BOT_W       	= 	1 ;                      
	BOT_IR     	 	= 	1 ;                            
	RIGHT_UV    	= 	1 ;                       
	LEFT_UV        	= 	1 ;                         
	RIGHT_IR770  	= 	1 ;                          
	RIGHT_LASER	 	= 	1 ;                        
	C3_PWR 		 	= 	0 ;                            
	AV_2660_SW		=   1  ; 
	System.Led.Statu = ALL_LED_OFF ; 
}

void Top_W_On(void)
{

	if((System.Dsp.Mode == CHECK_MODE)||(System.Dsp.Mode == PCCAM_MODE))
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 	
		DSP_SENDBW(0x16,TOP_LABEL, WcharToChar(L"白光")); 	
		Light_Init();
	   	TOP_W = 0;

		Scen_Send(G_SENCE_WT,0x00);

		Scen_Send(0xD7,System.Dsp.photo.Scene[G_SENCE_WT].Sharpness) ; 		    //锐度
        OSTimeDly(1); 		
		Scen_Send(0xD8,System.Dsp.photo.Scene[G_SENCE_WT].Saturation) ;			//饱和度
		OSTimeDly(1); 
        Scen_Send(0xD9,System.Dsp.photo.Scene[G_SENCE_WT].Brightness) ; 		//亮度
        OSTimeDly(1); 

		Scen_Send(0xE5, G_SENCE_WT); 
		OSTimeDly(5); 		
		System.Led.Statu = TOP_WHITE_ON ; 	
		ADC_Checking(ADC_CK_VLT_T_W,ADC_RSD_T_W );
	}
}

void Top_IR850_On(void)
{
	if(System.Dsp.Mode == CHECK_MODE||System.Dsp.Mode == PCCAM_MODE)
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 
		DSP_SENDBW(0x16,TOP_LABEL, WcharToChar(L"红外") ); 			//	200ms
		Light_Init();
		TOP_IR850=0;
		Scen_Send(G_SENCE_T_IR850,0x02);					    //	200ms
		System.Led.Statu = TOP_IR850_ON ; 
	//	ADC_Checking(ADC_CK_VLT_T_IR850,ADC_RSD_T_IR850);
	}
}
void Top_IR940_On_test(void)
{


	if((System.Dsp.Mode == CHECK_MODE)||System.Dsp.Mode ==  PCCAM_MODE)
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 

		DSP_SENDBW(0x16,TOP_LABEL,WcharToChar(L"红外") ); //	"940" 		

		Light_Init();
		TOP_IR940=0;
		Scen_Send(G_SENCE_T_IR940,0x02);	
		System.Led.Statu= TOP_IR940_ON ; 
		ADC_Checking(ADC_CK_VLT_T_IR940,ADC_RSD_T_IR940);
		OSTimeDly(50);
		Dsp_Send_Data(0xFF,G_SENCE_T_IR940,0x50,0xD1,D_NON);
	}
}


void Top_IR940_On(void)
{


	if((System.Dsp.Mode == CHECK_MODE)||System.Dsp.Mode ==  PCCAM_MODE)
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 

		DSP_SENDBW(0x16,TOP_LABEL,WcharToChar(L"红外") ); //	"940" 		

		Light_Init();
		TOP_IR940=0;
		Scen_Send(G_SENCE_T_IR940,0x02);	
		System.Led.Statu= TOP_IR940_ON ; 
		ADC_Checking(ADC_CK_VLT_T_IR940,ADC_RSD_T_IR940);

	}
}

void Left_W_On(void)
{
	if((System.Dsp.Mode == CHECK_MODE)||System.Dsp.Mode == PCCAM_MODE)
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 
 		DSP_SENDB(0x16,LEFT_LABEL, "W" ); 

		Light_Init();
//		LEFT_W = 0;
		RIGHT_W = 0 ;
		RIGHT_IR850 = 0;

		Scen_Send(G_SENCE_L_W,0x00);
		System.Led.Statu = LEFT_W_ON ; 
	//	ADC_Checking(ADC_CK_VLT_L_W,ADC_RSD_L_W);
	}
}

void Right_W_On(void)
{
	if((System.Dsp.Mode == CHECK_MODE)||(System.Dsp.Mode == PCCAM_MODE))
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 

		DSP_SENDB(0x16,RIGHT_LABEL, "W" );
		Light_Init();
		RIGHT_W=0;
		Scen_Send(G_SENCE_L_W,0x00);
		System.Led.Statu = RIGHT_W_ON ; 

	//	ADC_Checking(ADC_CK_VLT_R_W,ADC_RSD_R_W);
	}
}

void Left_IR850_On(void)
{
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 

		DSP_SENDB(0x16,LEFT_LABEL, "IR" );
		Light_Init();
		LEFT_IR850 = 0;
		Scen_Send(G_SENCE_L_IR,0x02);

		System.Led.Statu = LEFT_IR850_ON ;  
	//	ADC_Checking(ADC_CK_VLT_L_IR,ADC_RSD_L_IR);
	}
}

void Right_IR850_On(void)
{
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 

		DSP_SENDB(0x16,RIGHT_LABEL, "IR" ); 

		Light_Init();
		RIGHT_IR850 = 0;
		
		Scen_Send(G_SENCE_L_IR,0x02);
		System.Led.Statu = RIGHT_IR850_ON ;  
	//	ADC_Checking(ADC_CK_VLT_R_IR,ADC_RSD_R_IR);
	}
}

void Bot_W_On(void)
{
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 
		DSP_SENDB(0x16,BTM_LABEL, "W" ); 

		Light_Init();
		BOT_W=0;	
		
		Scen_Send(G_SENCE_B_W,0x00);	
		System.Led.Statu = BOT_W_ON ; 
	//	ADC_Checking(ADC_CK_VLT_B_W,ADC_RSD_B_W);
	}
}

void Bot_IR_On(void)
{
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 

		DSP_SENDB(0x16,BTM_LABEL, "IR" ); 
		Light_Init();
		BOT_IR=0;	
		
		Scen_Send(G_SENCE_B_IR,0x02); 
		System.Led.Statu = BOT_IR_ON ; 
		ADC_Checking(ADC_CK_VLT_B_IR,ADC_RSD_B_IR);
	}
}
void Right_UV_On(void)
{
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 
		DSP_SENDB(0x16,RIGHT_LABEL, "UV365" ); 

		Light_Init();
		RIGHT_UV=0;
		
		Scen_Send(G_SENCE_DB_UV,0x00);
		System.Led.Statu = RIGHT_UV_ON ; 
	// 	ADC_Checking(ADC_CK_VLT_R_UV,ADC_RSD_R_UV);
	}
}

void Double_WT_UV_On(void)
{
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 

		DSP_SENDB(0x16,0x08, "UV365" ); 
		Scen_Send(G_SENCE_DB_UV,0x00);	

		Light_Init();
	   	TOP_W = 0;
		OSTimeDly(100);

		Light_Init();
		LEFT_UV=0;
	//	OSTimeDly(100);
		RIGHT_UV=0;
			
		System.Led.Statu = DB_WT_UV_ON ; 
		ADC_Checking(ADC_CK_VLT_DB_UV,ADC_RSD_DB_UV);
	}
}

void Double_UV_On(void)
{
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 

		DSP_SENDB(0x16,0x08, "UV365" ); 
		
		Light_Init();
		LEFT_UV=0;
	//	OSTimeDly(100);
		RIGHT_UV=0;
		Scen_Send(G_SENCE_DB_UV,0x00);	

		System.Led.Statu = DB_UV_ON ; 
		ADC_Checking(ADC_CK_VLT_DB_UV,ADC_RSD_DB_UV);
	}
}


void Double_UV_Exposure1_On(void)
{
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 

		DSP_SENDB(0x16,0x08, "UV365" ); 

	
		DSP_SEND(4, &UV_Snr1_ExposureEV_FB[0]);
	//	OSTimeDly(10); 
		DSP_SEND(4, &UV_Snr1_ExposureEV_FC[0]);
	//	OSTimeDly(10); 
		Scen_Send(G_SENCE_DB_UV,0x01 ) ; 

		Light_Init();
		LEFT_UV=0;
	//	OSTimeDly(100);
		RIGHT_UV=0;

		System.Led.Statu = DB_UV_EXPOSURE1_ON; 
		ADC_Checking(ADC_CK_VLT_DB_UV,ADC_RSD_DB_UV);
	}
}

void Double_UV_Exposure2_On(void)
{
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 

		DSP_SENDB(0x16,0x08, "UV365" ); 

	
		DSP_SEND(4, &UV_Snr2_ExposureEV_FB[0]);
	//	OSTimeDly(10); 
		DSP_SEND(4, &UV_Snr2_ExposureEV_FC[0]);
	//	OSTimeDly(10); 
		Scen_Send(G_SENCE_DB_UV2,0x01 ) ; 

		Light_Init();
		LEFT_UV=0;
	//	OSTimeDly(100);
		RIGHT_UV=0;			

		System.Led.Statu = DB_UV_EXPOSURE2_ON ; 
		ADC_Checking(ADC_CK_VLT_DB_UV,ADC_RSD_DB_UV);
	}
}


void Right_IR770_On(void)
{
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 

		DSP_SENDB(0x16,TOP_LABEL, "IR" ); 
		Light_Init();
		RIGHT_IR770 = 0;
		
		Scen_Send(G_SENCE_B_IR,0x02);	
		System.Led.Statu = RIGHT_IR770_ON; 
	//	ADC_Checking(ADC_CK_VLT_R_770,ADC_RSD_R_770);
	}
}

void Right_Laser_On(void)
{
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 
		DSP_SENDB(0x16,TOP_LABEL, "LSR" ); 

		Light_Init();
		RIGHT_LASER = 0;
		
		Scen_Send(G_SENCE_B_IR,0x00);	
		System.Led.Statu = RIGHT_LASER_ON; 
	//	ADC_Checking(ADC_CK_VLT_R_LA,ADC_RSD_R_LA);
	}
}

void C608_On(void)
{
#ifdef STD_C608
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
	{
		Light_Init();
		A1=0;  
		A0=1; 
		EN=1;
	  	C3_PWR = 1;												                                                                                    
		OSTimeDly(10);

		AV_2660_SW = 0 ; 	
		DSP_SENDB(0x16,0x08, " C608");	 			
		OSTimeDly(10);	
		
		Select_Send(0x39);			      
		OSTimeDly(50);
		  
		Scen_Send(0xC1,0xC8);
		
		System.Led.Statu = C608_PWR_ON; 
		System.Dsp.Sensor = C608 ;
//	System.Dsp.Scale_Status = X0;    //存储方式
	}
#endif 
}

void CheckLight()
{
	
	Light_Init();TOP_IR940=0;if(!ADC_Checking(ADC_CK_VLT_T_IR940,ADC_RSD_T_IR940)) System.Error =IR_T_LED_ERR  ;	 
	Light_Init();BOT_IR=0;	 if(!ADC_Checking(ADC_CK_VLT_B_IR,ADC_RSD_B_IR)) System.Error =IR_B_LED_ERR  ;
	Light_Init();LEFT_UV=0;	 RIGHT_UV=0;	if(! ADC_Checking(ADC_CK_VLT_DB_UV,ADC_RSD_DB_UV)) System.Error =UV_LED_ERR  ;
	Light_Init();TOP_W = 0;	 if(!ADC_Checking(ADC_CK_VLT_T_W,ADC_RSD_T_W ))System.Error =W_T_LED_ERR  ;
//	Light_Init();
}


