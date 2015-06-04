#define __PERFORMANCE 

#include "performance.h"
#include "global.h"
#include "ucos_ii.h"
#include "stdint.h"
#include "Led.h"
#include "communication.h"
#include "KeyScan.h"
//#include "DS1307.h"
//#include "time.h"
#include "DrvADC.h"
#include "stdio.h"
#include "config.h"
#include "Keydispose.h"
#include "dspperf.h"
const uint8_t TW_Snr1EV_FB[] ={0xFB,G_SENCE_WT,0x08,0x08}	;	   //ÆØ¹âÊ±¼ä
const uint8_t TW_Snr1EV_FC[] ={0xFC,G_SENCE_WT,0x16,0x16}	;

const uint8_t UV_Snr1EV_FB[] ={0xFB,G_SENCE_DB_UV,0x30,0x30}	;	
const uint8_t UV_Snr1EV_FC[] ={0xFC,G_SENCE_DB_UV,0x32,0x32}	;

const uint8_t L_IR_Snr1EV_FB[] ={0xFB,G_SENCE_L_IR,0x09,0x09}	;	   //ÆØ¹âÊ±¼ä
const uint8_t L_IR_Snr1EV_FC[] ={0xFC,G_SENCE_L_IR,0x30,0x30}	;

const uint8_t UV_Snr2EV_FB[] ={0xFB,0x04,0x20,0x20}	;	
const uint8_t UV_Snr2EV_FC[] ={0xFC,0x04,0x70,0x70}	; 
const uint8_t UV_Snr3EV_FB[] ={0xFB,0x05,0x25,0x25}	;		
const uint8_t UV_Snr3EV_FC[] ={0xFC,0x05,0x20,0x20}	;

const uint8_t IR940_Snr1EV_FB[] ={0xFB,G_SENCE_T_IR940,0x0F,0x0F}	;	
const uint8_t IR940_Snr1EV_FC[] ={0xFC,G_SENCE_T_IR940,0x18,0x18}	;

//const uint8_t Zoom0X[]={0x2C,0x10,0x80,0x80};
const uint8_t Zoom1X[]={0x2C,0x10,0x80,0x80};
const uint8_t Zoom2X[]={0x2C,0x20,0x80,0x80};
const uint8_t Zoom3X[]={0x2C,0x30,0x80,0x80};

volatile uint8_t DeepCompression  ;

uint8_t* WcharToChar(wchar_t *p)
{
	 uint8_t i = 0 ; 

	 for(;i<=30;i++)
	 {
	 	char_array[i] = 0 ; 
	 }
	 char_array[0]	= 0xFF ; 
	 char_array[1]	= 0xFE ; 
	 for(i=0;;i++)
	 {
	 	 if(*(p+i) != NULL)
		 {
		    char_array[2*i+2] = *(p+i)>>8 ; 
			char_array[2*i+3] = *(p+i) ; 	 	
		 } 
		 else
		 {
		 	break ; 
		 }	  
	 }	
	 return &char_array[0]; 	
}



void SHOW_SCREEN_WC_NUM(uint8_t comm,wchar_t *p,uint16_t NUM,wchar_t *s,uint16_t NUM1)
{
    uint8_t i=0,t = 0 ; ; 


	 for(;i<=34;i++)
	 {
	 	char_array[i] = 0 ; 
	 }
	 char_array[0]	= 0xFF ; 
	 char_array[1]	= 0xFE ; 

	 for(i=0;;i++)
	 {
	 	 if(*(p+i) != NULL)
		 {
		    char_array[2*i+2] = *(p+i)>>8 ; 
			char_array[2*i+3] = *(p+i) ; 	 	
		 } 
		 else
		 {
		 	break ; 
		 }	  
	 }

	 char_array[2*i+2] = 0x00 ;   
	 char_array[2*i+3] = NUM/1000 +0x30 ;   

	 char_array[2*i+4] = 0x00 ; 
	 char_array[2*i+5] = NUM%1000/100 +0x30 ;

	 char_array[2*i+6] = 0x00 ;
	 char_array[2*i+7] = NUM%100/10 +0x30 ; 
	 
	 char_array[2*i+8] = 0x00 ;
	 char_array[2*i+9] = NUM%100%10 +0x30 ; 
	 	   
	     
	 t = 2*i+10 ; 
	 for(i=0;;i++)
	 {
	 	 if(*(s+i) != NULL)
		 {
		    char_array[t+2*i] = *(s+i)>>8 ; 
			char_array[t+2*i+1] = *(s+i) ; 	 	
		 } 
		 else
		 {
		 	break ; 
		 }	  
	 }

	 if(System.Local_SignOutCount_Flag  == 0 )
	 {
	 
	 }
	 else
	 {
	   	 char_array[t+2*i-8] = 0x00 ;
		 char_array[t+2*i-7] = NUM1/1000 +0x30 ;   

		 char_array[t+2*i-6] = 0x00 ; 
		 char_array[t+2*i-5] = NUM1%1000/100 +0x30 ;

		 char_array[t+2*i-4] = 0x00 ;
		 char_array[t+2*i-3] = NUM1%100/10 +0x30 ;    

		 char_array[t+2*i-2] = 0x00 ;
		 char_array[t+2*i-1] = NUM1%100%10 +0x30 ;    
	 }	 	 	 	 	
	 SHOW_SCREENW(comm, &char_array[0] );


}

void XyZoomFuc()
{
	if((System.Dsp.Mode == CHECK_MODE)||
	   (System.Dsp.Mode == PCCAM_MODE))
	{
		if(System.XyZoom[0] == 0xAA) System.XyZoom[0] = 0xAB ; 
		if(System.XyZoom[0] == 0xF0) System.XyZoom[0] = 0xF1 ;

		if(System.XyZoom[1] == 0xAA) System.XyZoom[1] = 0xAB ; 
		if(System.XyZoom[1] == 0xF0) System.XyZoom[1] = 0xF1 ; 

		if(System.XyZoom[2] == 0xAA) System.XyZoom[2] = 0xAB ; 
		if(System.XyZoom[2] == 0xF0) System.XyZoom[2] = 0xF1 ; 
   		Dsp_Send_Data(0x2C,System.XyZoom[0],System.XyZoom[1],System.XyZoom[2],D_NON); 
	}	
}


void ShowChkPhotOne()
{
	SHOW_SCREENW(0xE8, WcharToChar(L"Çë½øÒ»²½¼ì²é") ); 
}
void ShowChkPhotAgain()
{
	SHOW_SCREENW(0xE8, WcharToChar(L"¿É,Çë½øÒ»²½¼ì²é") ); 	
}
void ExtBlackScreen()
{
     Select_Send(0xE9);
}
void Photo_SignAndCount()
{
	if(System.Dsp.Mode == CHECK_MODE)
	{
		if(System.SignOutCount>=1500)
		{
			SHOW_SCREEN_T_W(0xE3,0x05,WcharToChar(L"ÕÕÆ¬ÊýÁ¿µ½ÉÏÏÞ,Çë´¦Àí"));
			return ;
		}

		if(System.Uart.SdFlag	==0x03)
		{
			 SHOW_SCREEN_T_W(0xE3,0x05,WcharToChar(L"¿¨Âú,Çë´¦Àí"));
			 return ; 
		}

		System.Process_TakePht  = 0 ; 

		if(System.Dsp.Sensor !=SENSOR1)
		{	
				CheckMode();
				OSTimeDly(200);   
		}
	 	if(System.Dsp.CheckMode.Zoom != X0)
		{
			Check_View_Zoom(X0);
		}


	 	SHOW_SCREENW(0xE8, WcharToChar(L"Ç©·¢Êý¾Ý²É¼¯,ÇëÉÔºò") );	
		
		if(	System.Local_SignOutCount_Flag  == 1)  
		{
			Local_SignOutCount++ ; 	 
		} 
		PhotographFour();  

		System.Process_TakePht  = 1 ; 


	//	OSTimeDly(100); 
		if(System.PhotoNum != 4)
		{
	 		System.PhotoNum = 4 ;  //4ÕÅÕÕÆ¬
			System.Sys.SaveInfoFlag  = 0x01  ;
		}
	}
}
void Photo_SignAndChk()
{
	if(System.Dsp.Mode == CHECK_MODE)
	{
		if(System.SignOutCount>=1500)
		{
			SHOW_SCREEN_T_W(0xE3,0x05,WcharToChar(L"ÕÕÆ¬ÊýÁ¿µ½ÉÏÏÞ,Çë´¦Àí"));
			return ;
		}

		if(System.Uart.SdFlag	==0x03)
		{
			 SHOW_SCREEN_T_W(0xE3,0x05,WcharToChar(L"¿¨Âú,Çë´¦Àí"));
			 return ; 
		}
		System.Process_TakePht  = 0 ; 

		if(System.Dsp.Sensor !=SENSOR1)
		{	
			CheckMode(); 
			OSTimeDly(200);  
		}
	 	if(System.Dsp.CheckMode.Zoom != X0)
		{
			Check_View_Zoom(X0);
		}
		SHOW_SCREENW(0xE8, WcharToChar(L"Êý¾Ý²É¼¯ÖÐ,ÇëÉÔºò...") );	
	//	PhotographFour_Sign();  	
//	    System.SignOutCount++ ; 


	 	PhotographFour();  	
	//	Select_Send(0xE9); 
	//	ShowLeftBtmNum(); 
		
		System.Process_TakePht  = 1 ; 
		if(System.PhotoNum != 4)
		{
	 		System.PhotoNum = 4 ; 
			System.Sys.SaveInfoFlag  = 0x01  ;
		}
	}
}

void  ShowLeftBtmNum()
{ 
//	Select_Send_LONG(0x77) ;
	
	SHOW_SCREEN_WC_NUM(0xE2, L"×Ü:",System.SignOutCount,L"  ±¾´Î:----",Local_SignOutCount);	
}
/*==================================================================
* Function	: PhotoMvUp
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void PhotoMvUp()
{
	if((System.Dsp.Mode == VIEW_MODE)&&(System.Dsp.ViewMode.Zoom != X0 ))
	{
		Select_Send(0x17);
		OSTimeDly(10);	
	}
}


/*==================================================================
* Function		: PhotoMvDown
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value	: 
==================================================================*/
void PhotoMvDown()
{
	if((System.Dsp.Mode == VIEW_MODE)&&(System.Dsp.ViewMode.Zoom != X0 ))
	{
		Select_Send(0x18);
		OSTimeDly(10);	
	}
}


/*==================================================================
* Function		: PhotoMvLeft
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void PhotoMvLeft()
{
	if((System.Dsp.Mode == VIEW_MODE))
	{
		if(System.Dsp.ViewMode.Zoom != X0)
		{
			Select_Send(0x19);
			OSTimeDly(10);	
		}
		else
		{
			PhotoPrevious();
		}
	}
}

/*==================================================================
* Function		: PhotoMvRight
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void PhotoMvRight()
{
	if((System.Dsp.Mode == VIEW_MODE))
	{
		if(System.Dsp.ViewMode.Zoom != X0)
		{
			Select_Send(0x1A);
			OSTimeDly(10);		
		}
		else
		{
			PhotoNext();
		}


	}
}

/*==================================================================
* Function	: PhotoNext
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void PhotoNext()
{
	if((System.Dsp.Mode == VIEW_MODE)&&(System.Dsp.ViewMode.Zoom == X0 ))
	{
		Select_Send(0x2b);
		OSTimeDly(20);	
	}
}

/*==================================================================
* Function	: PhotoPrevious
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void PhotoPrevious()
{
	if((System.Dsp.Mode == VIEW_MODE)&&(System.Dsp.ViewMode.Zoom == X0 ))
	{
		Select_Send(0x2a);
		OSTimeDly(20);
	}
	
}

void Check_View_Zoom(ENUM_DSP_ZOOM NUM)	   // ÕÕÆ¬·Å´ó
{
	if((System.Dsp.Mode == CHECK_MODE)||(System.Dsp.Mode == PCCAM_MODE))
	{
		switch(NUM)
		{
			case X0 :	Select_Send(0x30);  
						System.Dsp.CheckMode.Zoom = X0 ;
						OSTimeDly(10);break ;  //DSP_SENDB(0xe2,NULL," "); 
			
			case X1 : //	Scen_Send(0x2C,0x30);  	
						Dsp_Send_Data(0x2C,0x30,0,0,D_NON); 	
						System.Dsp.CheckMode.Zoom = X1 ;		 	
						OSTimeDly(10); break ;//DSP_SENDB(0xe2,NULL,"X3"); 		
						 
			case X2 : //	Scen_Send(0x2C,0x50);  	
					    Dsp_Send_Data(0x2C,0x50,0,0,D_NON); 
						System.Dsp.CheckMode.Zoom = X2 ;		 	
						OSTimeDly(10);break ; //DSP_SENDB(0xe2,NULL,"X5"); 	
						
 			case X3 :  // Scen_Send(0x2C,0x70);  
						Dsp_Send_Data(0x2C,0x70,0,0,D_NON); 			
 		 				System.Dsp.CheckMode.Zoom = X3 ;		 	
 			 			OSTimeDly(10);break ; //DSP_SENDB(0xe2,NULL,"X7"); 		

			default : 	break ; 
		}
	}
	else if(System.Dsp.Mode == VIEW_MODE)
	{
		switch(NUM)
		{
			case X0 :	Select_Send(0x3A); 
						System.Dsp.ViewMode.Zoom = X0 ;
						OSTimeDly(10); break ; //DSP_SENDB(0xe2,NULL,"  "); 		
						
			case X1 : 	Scen_Send(0x33,0x30);  		
						System.Dsp.ViewMode.Zoom = X1 ;		 	
						OSTimeDly(10); break ;//DSP_SENDB(0xe2,NULL,"X3"); 		
						 
			case X2 : 	Scen_Send(0x33,0x50);  		
						System.Dsp.ViewMode.Zoom = X2 ;		 	
						OSTimeDly(10); break ;//DSP_SENDB(0xe2,NULL,"X5"); 		
						
 			case X3 :   Scen_Send(0x33,0x70);  			
 			 			System.Dsp.ViewMode.Zoom = X3 ;		 	
 			 			OSTimeDly(10); break ;//DSP_SENDB(0xe2,NULL,"X7"); 		

			default : 	break ; 
		}
		
	} 
	ShowZoom(); 
}


void PhotoZoomUp(void)	   // ÕÕÆ¬·Å´ó
{


	if((System.Dsp.Mode == CHECK_MODE)||(System.Dsp.Mode == PCCAM_MODE))
	{
		switch(System.Dsp.CheckMode.Zoom)
		{
			case X0 : 	System.Dsp.CheckMode.Zoom = X1 ; break ;		 	
								
						 
			case X1 : 	System.Dsp.CheckMode.Zoom = X2 ; break ;			
						
//			case X2 :   System.Dsp.CheckMode.Zoom = X3 ; break ; 				

			default :  	System.Dsp.CheckMode.Zoom = X0 ; break ; 
		}
		Check_View_Zoom(System.Dsp.CheckMode.Zoom );
	}
	else if(System.Dsp.Mode == VIEW_MODE)
	{
		switch(System.Dsp.ViewMode.Zoom)
		{
			case X0 : 	System.Dsp.ViewMode.Zoom = X1 ;	break ; 		
						 
			case X1 : 	System.Dsp.ViewMode.Zoom = X2 ;	break ; 			
						
//			case X2 :   System.Dsp.ViewMode.Zoom = X3 ; break ; 			

			default : 	System.Dsp.ViewMode.Zoom = X0 ;	break ;
		}
		Check_View_Zoom(System.Dsp.ViewMode.Zoom);
	}
}
void PhotoZoomDown(void)   // ÕÕÆ¬ËõÐ¡
{
//	if(System.Dsp.Mode == VIEW_MODE)
//	{
//		switch(System.Dsp.ViewMode.Zoom)
//		{
//			case X3 :   Scen_Send(0x33,0x30);  		
//						System.Dsp.ViewMode.Zoom = X2 ;		 	
//						OSTimeDly(20); DSP_SENDB(0xe2,NULL,"X3"); 		break ;
//
//			case X2 :   Scen_Send(0x33,0x20);  		
//						System.Dsp.ViewMode.Zoom = X1 ;		 	
//						OSTimeDly(20); DSP_SENDB(0xe2,NULL,"X2"); 		break ;
//
//			case X1 :   Select_Send(0x3A);  		
//						System.Dsp.ViewMode.Zoom = X0 ;		 	
//						OSTimeDly(20); DSP_SENDB(0xe2,NULL,"X1"); 		break ;
//						 
//			default : 	Select_Send(0x3A);   		
//			 			System.Dsp.ViewMode.Zoom = X0 ;		 	
//			 			OSTimeDly(20); DSP_SENDB(0xe2,NULL,"X1"); 		break ;
//		}
//	}
}

void ShowZoom(void)
{	if(System.Dsp.Mode == CHECK_MODE)
	{
		switch(System.Dsp.CheckMode.Zoom)
		{
		 	case X0 :	OSTimeDly(10);DSP_SENDB(0xe2,NULL,"  "); System.Uart.PlayZom = 0x01 ;  break ;
			case X1 :	OSTimeDly(10);DSP_SENDB(0xe2,NULL,"X3"); System.Uart.PlayZom = 0x02 ; break ;
			case X2 :	OSTimeDly(10);DSP_SENDB(0xe2,NULL,"X5"); System.Uart.PlayZom = 0x02 ;  break ;	
			default :break ;
		}
	}
	if(System.Dsp.Mode == VIEW_MODE)
	{
		switch(System.Dsp.ViewMode.Zoom)
		{
		 	case X0 :	OSTimeDly(10);DSP_SENDB(0xe2,NULL,"  "); System.Uart.PlayZom = 0x03 ;   break ;
			case X1 :	OSTimeDly(10);DSP_SENDB(0xe2,NULL,"X3"); System.Uart.PlayZom = 0x04 ;   break ;
			case X2 :	OSTimeDly(10);DSP_SENDB(0xe2,NULL,"X5"); System.Uart.PlayZom = 0x04 ;   break ;	
			default :break ;
		}		
	}
}


void PhotoAutoView(void)
{
	if(System.Dsp.ViewMode.CycleView == 0)
	{
	    System.Dsp.ViewMode.CycleView = 1 ; 
	}
	else
	{
		if(System.Dsp.ViewMode.CycleViewPause == 1)
		{
			System.Dsp.ViewMode.CycleViewPause	=0 ; 
		}
		else
		{
			System.Dsp.ViewMode.CycleViewPause	=1 ; 
		}
	}
}

void Zhuanfa(void)
{
		
}

void TimeSet(void)
{
		
}

void UV365_70ExpSet(void)
{
	if(System.Dsp.Mode == CHECK_MODE)
	{
		Sensor1(); 
		Double_UV_On(); 
		
		Select_Send(0x96); 				 
		OSTimeDly(5);

		DSP_SEND(4, &ADJ_ExpSetFB[0]);
	    OSTimeDly(10); 
		DSP_SEND(4, &ADJ_ExpSetFC[0]);
		OSTimeDly(10); 
		Scen_Send(G_SENCE_DB_UV,0x01 ) ; 
		OSTimeDly(300);				
		Scen_Send(0xE6,G_SENCE_DB_UV); 														
		OSTimeDly(400);	
		
		Select_Send(0x96); 				 
		OSTimeDly(5);
		Scen_Send(G_SENCE_DB_UV,0x00);
		OSTimeDly(10);	
		Scen_Send(0xe5, G_SENCE_DB_UV);							
		OSTimeDly(100);	
		Scen_Send(0xE7, G_SENCE_DB_UV); 	
		OSTimeDly(300);
		SHOW_SCREEN(0xE3,"OK\n");
	}
}
void UV365_71ExpSet(void)
{
	if(System.Dsp.Mode == CHECK_MODE)
	{
//		Sensor2(); 	
//	    Double_UV_On();
//
//		DSP_SEND(4, &ADJ_ExpSetFB[0]);
//	    OSTimeDly(10); 
//		DSP_SEND(4, &ADJ_ExpSetFC[0]);
//		OSTimeDly(10); 
//		Scen_Send(G_SENCE_DB_UV,0x01 ) ; 
//		OSTimeDly(300);	
//		
//		Select_Send(0x96); 			
//		OSTimeDly(5);	
//		Scen_Send(0xE6, PH_SENCE_TOP_UV_71); 														
//		OSTimeDly(400);		
//
//		Select_Send(0x96); 			
//		OSTimeDly(5);
//		Scen_Send(G_SENCE_DB_UV,0x00);		
//		OSTimeDly(10);	
//		Scen_Send(0xe5,PH_SENCE_TOP_UV_71);							
//		OSTimeDly(100);	
//		Scen_Send(0xE7,PH_SENCE_TOP_UV_71); 	
//		OSTimeDly(300);
//		
//		//DSP_SENDB(0xe2,NULL,"X3"); 	
//	    SHOW_SCREEN(0xE3,"OK\n");	
	}
}

void Format_SDcard(void)
{
	OSTimeDly(5);
	Dsp_Send_Data(0x2D,D_NON,D_NON,D_NON,D_NON);
//	OSTimeDly(200);
//	Dsp_Send_Data(0x28,D_NON,D_NON,D_NON,D_NON);
//	OSTimeDly(200);
//	Dsp_Send_Data(0x2F,D_NON,D_NON,D_NON,D_NON);	
}

void UV365_72ExpSet(void)
{
	if(System.Dsp.Mode == CHECK_MODE)
	{
		Sensor3(); 	
	    Double_UV_On();
	
		DSP_SEND(4, &ADJ_ExpSetFB[0]);
	    OSTimeDly(10); 
		DSP_SEND(4, &ADJ_ExpSetFC[0]);
		OSTimeDly(10); 
		Scen_Send(G_SENCE_DB_UV,0x01 ) ; 
		OSTimeDly(300);	
		
		Select_Send(0x96); 			
		OSTimeDly(5);
		
		Scen_Send(0xE6, G_SENCE_DB_UV); 														
		OSTimeDly(400);		

		Select_Send(0x96); 			
		OSTimeDly(5);
		Scen_Send(G_SENCE_DB_UV,0x00);		
		OSTimeDly(10);	
		Scen_Send(0xe5,G_SENCE_DB_UV);							
		OSTimeDly(100);	
		Scen_Send(0xE7,G_SENCE_DB_UV); 	
		OSTimeDly(300);
		
		//DSP_SENDB(0xe2,NULL,"X3"); 	
	    SHOW_SCREEN(0xE3,"OK\n");		
	}
}
void IR770_72ExpSet(void)
{
//	Sensor3(); 
//	Right_IR770_On(); 
//	OSTimeDly(100);
//	DSP_SEND(4, &ADJ_ExpSetFB[0]);
//    OSTimeDly(10); 
//	DSP_SEND(4, &ADJ_ExpSetFC[0]);
//	OSTimeDly(10); 
//	Scen_Send(0x01,0x03 ) ; 
//	OSTimeDly(300);	
//	
//	Select_Send(0x96); 			
//	OSTimeDly(5);		
//	Scen_Send(0xE6, PH_SENCE_TOP_IR770_72); 														
//	OSTimeDly(400);	
//	
//	Select_Send(0x96); 			
//	OSTimeDly(5);
//	Scen_Send(0x01,0x02);		
//	OSTimeDly(10);	
//	Scen_Send(0xe5,PH_SENCE_TOP_IR770_72);							
//	OSTimeDly(100);	
//	Scen_Send(0xE7,PH_SENCE_TOP_IR770_72); 	
//	OSTimeDly(300);	
//	
//	SHOW_SCREEN(0xE3,"OK\n");
}
void QueryInfo(void)
{

	SystemReadBCKData();  //¶ÁÈ¡ÐÅÏ¢	

}

void ModifyInfo(void)
{
	SystemWriteBCKData() ; // ´æ´¢ÐÅÏ¢	   
	GR_DBG_PRINTF("\n\nSystemWriteBCKData \n\n");
}

void MacSleep(void)
{
	if(System.Dsp.Mode == CHECK_MODE||VIEW_MODE)
	{
		System.Dsp.Mode = SLEEP_MODE ; 
		Light_Init() ; 
		Select_Send(0x31);
	//	SHOW_SCREEN(0xE8,  " "); 
	}					  
}
void MacWakeup(void)
{
	System.Key.NoKeyTime = 0 ;	
	if(System.Dsp.Mode == SLEEP_MODE)
	{	
		Select_Send(0x32);
		CheckMode(); 
		OSTimeDly(200) ; 
	}	  		
}
void Slp_enable(void)
{

	System.SleepEnable = 1 ; 

}

void Slp_disable(void)
{

	System.SleepEnable = 0 ; 
	if(System.Dsp.Mode == SLEEP_MODE)
	{	
		CheckMode(); 
		OSTimeDly(200) ; 
	}
}
/*==================================================================
* Function	: Sensor1
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void Sensor1()
{
	if(System.Dsp.Sensor != SENSOR1)
	{
		Select_Send(0x70);
		OSTimeDly(50); 
		Scen_Send(0xC1,0x60);
		OSTimeDly(5); 
		System.Dsp.Sensor = SENSOR1 ; 
	//	OSTimeDly(50); 
		System.Dsp.CheckMode.Zoom = X0 ;
		System.Dsp.ViewMode.Zoom  = X0 ; 
	 }
}

/*==================================================================
* Function	: Sensor2
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void Sensor2()
{
	Select_Send(0x71);
	OSTimeDly(100); 
	Scen_Send(0xC1,0x60);
	OSTimeDly(5); 
	System.Dsp.Sensor = SENSOR2 ; 
	OSTimeDly(150); 
}

/*==================================================================
* Function	: Sensor3
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void Sensor3()
{
	Select_Send(0x72);
	OSTimeDly(200); 
	Scen_Send(0xC1,0x60);
	OSTimeDly(5); 
	System.Dsp.Sensor = SENSOR3 ; 
	OSTimeDly(150); 
}



/*==================================================================
* Function	: CheckMode
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void CheckMode()
{

	if((System.Dsp.Mode == PCCAM_MODE)||(System.Dsp.Mode == TF_MODE))
	{
		Select_Send(0xCE); 
		#ifdef AD_13
		OSTimeDly(150);
		#elif defined AD_16 
		OSTimeDly(10);
		#endif 	 

	}
	else if(System.Dsp.Mode == VIEW_MODE)
	{
	 	Select_Send(0x26); 
		#ifdef AD_13
		OSTimeDly(50);
		#elif defined AD_16 
		OSTimeDly(5);
		#endif 	

	}  
	else if(System.Dsp.Mode == SLEEP_MODE )
	{
		Select_Send(0xE9);
		OSTimeDly(50);  
	}
	if(System.Dsp.Sensor != SENSOR1)
	{	
 		Sensor1();
	} 
	System.Dsp.Mode = CHECK_MODE ; 
	Top_W_On();   

	Check_View_Zoom(X0) ;
	ShowLeftBtmNum(); 
}


/*==================================================================
* Function	: ViewMode
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void ViewMode()
{
	if(System.Dsp.Mode == CHECK_MODE)
	{
		Light_Init(); 

		Select_Send(0x25);		
		OSTimeDly(50);	
		#ifdef AD_13				   
		System.Dsp.Sensor = NONSENSOR ;
		#elif defined AD_16

		#endif 

		MvtempDec1 = 0 ; 
		MvtempDec = 0 ;

		System.Dsp.Mode = VIEW_MODE ; 
		System.Dsp.ViewMode.Zoom = X0 ;
		System.Uart.PlayZom = 0x03 ; 
//		GR_DBG_PRINTF("IS In ViewMode\n\n");
	}
}

void ViewMode_F1()	//Í¼Ïñ
{
	if(System.Dsp.Mode == VIEW_MODE)
	{

 		if(System.Dsp.ViewMode.Zoom != X0 )
		{
			Select_Send(0x3A);		
			OSTimeDly(50);	
			System.Dsp.Mode = VIEW_MODE ; 
			System.Dsp.ViewMode.Zoom = X0 ;

		}
		else
		{
			if(MvtempDec==1)
			{
				PhotoMvRight() ;
				if(++MvtempDec1>=System.PhotoNum-1) {MvtempDec1 = 0 ; MvtempDec = 0 ;} 
				   
			//	  OSTimeDly(100);
			}
			else
			{
				PhotoMvLeft() ;	
				if(++MvtempDec1>=System.PhotoNum-1) {MvtempDec1 = 0 ; MvtempDec = 1 ;} 
					
			//		OSTimeDly(100); 
			}		
		}
   }
}

void ViewMode_F2()	// ºÅÂë
{

	if(System.Dsp.Mode == VIEW_MODE)
	{
		if(System.Dsp.ViewMode.Zoom != X2 )
		{
			Dsp_Send_Data(0x33,0x60,0x01,0x42,0x43); 	//23 33 30 01 39 3D AA	//	Dsp_Send_Data(0x33,0x60,0x01,0x42,0x4B); 	//23 33 30 01 39 3D AA			
			OSTimeDly(50);
			System.Dsp.ViewMode.Zoom = X2 ;
		}
		else
		{
			if(MvtempDec==1)
			{
				if(++MvtempDec1>=System.PhotoNum-1) {MvtempDec1 = 0 ; MvtempDec = 0 ;} 
			//	  PhotoMvRight() ; 
			Dsp_Send_Data(0x2B,0x60,0x01,0x42,0x43);//	Dsp_Send_Data(0x2B,0x60,0x01,0x42,0x4B);
		//	OSTimeDly(100);
			}
			else
			{
				if(++MvtempDec1>=System.PhotoNum-1) {MvtempDec1 = 0 ; MvtempDec = 1 ;} 
			//	PhotoMvLeft() ;	 	232A3001393DAA
				Dsp_Send_Data(0x2A,0x60,0x01,0x42,0x43);//   	Dsp_Send_Data(0x2A,0x60,0x01,0x42,0x4B);	   Ôö´óÏò×óÒÆÏÂÒÆ
			//	OSTimeDly(100);
			}						
		}
	}

}
void ViewMode_F3()	// ´óÐ´½ð¶î
{ 
	if(System.Dsp.Mode == VIEW_MODE)
	{
		if(System.Dsp.ViewMode.Zoom != X3 )
		{
			Dsp_Send_Data(0x33,0x60,0x00,0x22,0x08); 		//23 33 30 01 39 3D AA			
			OSTimeDly(50);
			System.Dsp.ViewMode.Zoom = X3 ;

		}
		else
		{
			if(MvtempDec == 1)
			{
				if(++MvtempDec1 >= System.PhotoNum-1) 
				{
					MvtempDec1 = 0 ; MvtempDec = 0 ;
				} 
				Dsp_Send_Data(0x2B,0x60,0x00,0x22,0x08); 		//  Dsp_Send_Data(0x2B,0x40,0x00,0x1F,0x08); 
			//	OSTimeDly(100);
			}
			else
			{
				if(++MvtempDec1 >=System.PhotoNum-1) 
				{
					MvtempDec1 = 0 ; MvtempDec = 1 ;
				} 
			   	Dsp_Send_Data(0x2A,0x60,0x00,0x22,0x08); 
			//	OSTimeDly(100);
			}						
		}
	}
 	
}
void ViewMode_F4()	//Êý×Ö Ð¡Ð´½ð¶î
{
	if(System.Dsp.Mode == VIEW_MODE)
	{
		if(System.Dsp.ViewMode.Zoom != X4 )
		{
			Dsp_Send_Data(0x33,0x60,0x01,0x30,0x8);
			OSTimeDly(50);
			System.Dsp.ViewMode.Zoom = X4 ;
		}
		else
		{
			if(MvtempDec ==1)
			{
				if(++MvtempDec1 >=System.PhotoNum-1) {MvtempDec1 = 0 ; MvtempDec = 0 ;} 
			//	  PhotoMvRight() ; 
				Dsp_Send_Data(0x2B,0x60,0x01,0x30,0x8);
			//	OSTimeDly(100);
			}
			else
			{
				if(++MvtempDec1 >=System.PhotoNum-1) {MvtempDec1 = 0 ; MvtempDec = 1 ;} 
			//	PhotoMvLeft() ;	 	232A3001393DAA
			   	Dsp_Send_Data(0x2A,0x60,0x01,0x30,0x08);
			//	OSTimeDly(100);
			}						
		}
	}

	
//	if(System.Dsp.Mode == CHECK_MODE)
//	{
//		Light_Init(); 
//
////		Select_Send(0x25);		
//		
//
//
//		MvtempDec1 = 0 ; 
//		MvtempDec = 0 ;
//
//		System.Dsp.Mode = VIEW_MODE ; 
//		System.Dsp.ViewMode.Zoom = X0 ;
//		System.Uart.PlayZom = 0x03 ; 
////		GR_DBG_PRINTF("IS In ViewMode\n\n");
//	}
}

/*==================================================================
* Function	: PccamMode
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void PccamMode()
{
	if(System.Dsp.Mode == TF_MODE)
	{
		CheckMode(); 
	}
	if(System.Dsp.Mode == CHECK_MODE)
	{
		Select_Send(0xCD); 
		OSTimeDly(200) ;
		System.Dsp.Mode = PCCAM_MODE ; 
	}
}

/*==================================================================
* Function	: TfMode
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void TfMode()
{
	if(System.Dsp.Mode == PCCAM_MODE)
	{
		CheckMode(); 
	}
	
	if((System.Dsp.Mode == CHECK_MODE)||(System.Dsp.Mode == VIEW_MODE))
	{
		System.Dsp.Mode = TF_MODE ; 
		
		Select_Send(0xCC);				//UÅÌ
		Light_Init() ; 
		OSTimeDly(10);	
	}

//	System.Local_SignOutCount_Flag  = 0; 
//	Local_SignOutCount =0 ; 	 
}


/*==================================================================
* Function	: PhotographOne
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
#ifdef AD_13
void PhotographOne()
{
	if(System.Dsp.Mode == CHECK_MODE)
	{
		Select_Send(0x96); 				//µ¥¶ÀÅÄÕÕ·Ö×é¡£ºÍÁ¬ÅÄÇø·Ö¿ªÀ´£¡
		OSTimeDly(5);
		Select_Send(0x21); 					
		OSTimeDly(120);	
	}
}
#elif defined AD_16
void PhotographOne()
{
	if(System.Dsp.Mode == CHECK_MODE)
	{
		
		Select_Send(0x96); 				//µ¥¶ÀÅÄÕÕ·Ö×é¡£ºÍÁ¬ÅÄÇø·Ö¿ªÀ´£¡
		OSTimeDly(5);
	//	Select_Send(0x21); 					
		Dsp_Send_Data(0x21,0x00,0x01,0x01,D_NON);

//		switch(System.Led.Statu)
//		{
//			case DB_UV_EXPOSURE1_ON :Double_UV_Exposure1_On();
//			case DB_UV_EXPOSURE2_ON :Double_UV_Exposure2_On();
//		}
	 	OSTimeDly(20);	

		ShowZoom();
	}
}
#endif 
void PhotoNumAdjust()
{
ShowLeftBtmNum(); 	
}

void PhotographFour_Sign()
{
	
	if(System.Dsp.Mode == CHECK_MODE)
	{

	  //	 SHOW_SCREEN(0xE8, WcharToChar(L"Ç©·¢²É¼¯ÇëÉÔºó") );	//	   "Wait..."
/*----------------------------------------------------*/
		if(System.Dsp.Sensor !=SENSOR1)
		{
			Sensor1();
		}
	 	if(System.Dsp.CheckMode.Zoom != X0)
		{
			Check_View_Zoom(X0);
		}
////----------------------------------------------------*/
		Light_Init();
	   	TOP_W = 0;
		Scen_Send(G_SENCE_WT,0x00);
		System.Led.Statu = TOP_WHITE_ON ; 	
		
		Select_Send(0x74);			//´´½¨ÐÂ·Ö×é

		Scen_Send(0xD7,System.Dsp.photo.Scene[G_SENCE_WT].Sharpness) ; 		    //Èñ¶È
        OSTimeDly(10); 
        Scen_Send(0xDA,System.Dsp.photo.Scene[G_SENCE_WT].Contrast) ; 		    //¶Ô±È¶È
        OSTimeDly(10); 
        Scen_Send(0xD9,System.Dsp.photo.Scene[G_SENCE_WT].Brightness) ; 		//ÁÁ¶È
        OSTimeDly(10); 
		Scen_Send(0xD8,System.Dsp.photo.Scene[G_SENCE_WT].Saturation) ;			//±¥ºÍ¶È
		OSTimeDly(10); 
		Scen_Send(0xE5, G_SENCE_WT); 
		OSTimeDly(10); 

	 	Scen_Send(0xE7, G_SENCE_WT); 	

/*----------------------------------------------------*/	//		
	//	Top_IR940_On(); 
		Light_Init();
		TOP_IR940=0;
		Scen_Send(G_SENCE_T_IR940,0x02);
		System.Led.Statu= TOP_IR940_ON ; 
		Scen_Send(0xD7,System.Dsp.photo.Scene[G_SENCE_T_IR940].Sharpness) ; 		    //Èñ¶È
        OSTimeDly(10); 
        Scen_Send(0xDA,System.Dsp.photo.Scene[G_SENCE_T_IR940].Contrast) ; 		    //¶Ô±È¶È
        OSTimeDly(10); 
        Scen_Send(0xD9,System.Dsp.photo.Scene[G_SENCE_T_IR940].Brightness) ; 		//ÁÁ¶È
        OSTimeDly(10); 
		Scen_Send(0xD8,System.Dsp.photo.Scene[G_SENCE_T_IR940].Saturation) ;			//±¥ºÍ¶È
		OSTimeDly(10); 
		Scen_Send(0xE5, G_SENCE_T_IR940); 
		OSTimeDly(10); 
	//	Dsp_Send_Data(0x21,0x00,0x01,0x01,D_NON);
	    Scen_Send(0xE7, G_SENCE_T_IR940); 	
	//	OSTimeDly(50); 
/*----------------------------------------------------*/	 //µ×ºìÍâ									 							
	//	Bot_IR_On(); 
		Light_Init();
		BOT_IR=0;		
		Scen_Send(G_SENCE_B_IR,0x02); 
		System.Led.Statu = BOT_IR_ON ; 

		Scen_Send(0xD7,System.Dsp.photo.Scene[G_SENCE_B_IR].Sharpness) ; 		    //Èñ¶È
        OSTimeDly(10); 
        Scen_Send(0xDA,System.Dsp.photo.Scene[G_SENCE_B_IR].Contrast) ; 		    //¶Ô±È¶È
        OSTimeDly(10); 
        Scen_Send(0xD9,System.Dsp.photo.Scene[G_SENCE_B_IR].Brightness) ; 		//ÁÁ¶È
        OSTimeDly(10); 
		Scen_Send(0xD8,System.Dsp.photo.Scene[G_SENCE_B_IR].Saturation) ;			//±¥ºÍ¶È
		OSTimeDly(10); 
		Scen_Send(0xE5, G_SENCE_B_IR); 
		OSTimeDly(10);

		//OSTimeDly(10); 		
		Dsp_Send_Data(0x21,0x00,0x01,0x01,D_NON);												
	// 	OSTimeDly(50);
/////*----------------------------------------------------*/	 //×ó²àbaidenbg
												 							
		Light_Init();
		LEFT_W = 0;	
		RIGHT_W = 0;	
		Scen_Send(G_SENCE_L_W,0x00);
		OSTimeDly(10);
		System.Led.Statu= LEFT_W_ON ; 

		Scen_Send(0xD7,System.Dsp.photo.Scene[G_SENCE_L_W].Sharpness) ; 		    //Èñ¶È
        OSTimeDly(10); 
        Scen_Send(0xDA,System.Dsp.photo.Scene[G_SENCE_L_W].Contrast) ; 		    //¶Ô±È¶È
        OSTimeDly(10); 
        Scen_Send(0xD9,System.Dsp.photo.Scene[G_SENCE_L_W].Brightness) ; 		//ÁÁ¶È
        OSTimeDly(10); 
		Scen_Send(0xD8,System.Dsp.photo.Scene[G_SENCE_L_W].Saturation) ;			//±¥ºÍ¶È
		OSTimeDly(10); 
		Scen_Send(0xE5, G_SENCE_L_W); 
		OSTimeDly(10); 
	//	Dsp_Send_Data(0x21,0x00,0x01,0x01,D_NON);
	    Scen_Send(0xE7, G_SENCE_L_W); 
			

///*----------------------------------------------------*/ 	//×Ï¹â
	 //	Double_UV_On(); 
	  	Light_Init();
		LEFT_UV=0;
	//	OSTimeDly(100);
		RIGHT_UV=0;
		Scen_Send(G_SENCE_DB_UV,0x00);	
		OSTimeDly(10);
		System.Led.Statu = DB_UV_ON ; 

 		Scen_Send(0xD7,System.Dsp.photo.Scene[G_SENCE_DB_UV].Sharpness) ; 		    //Èñ¶È
        OSTimeDly(10); 
        Scen_Send(0xDA,System.Dsp.photo.Scene[G_SENCE_DB_UV].Contrast) ; 		    //¶Ô±È¶È
        OSTimeDly(10); 
        Scen_Send(0xD9,System.Dsp.photo.Scene[G_SENCE_DB_UV].Brightness) ; 		//ÁÁ¶È
        OSTimeDly(10); 
		Scen_Send(0xD8,System.Dsp.photo.Scene[G_SENCE_DB_UV].Saturation) ;			//±¥ºÍ¶È
		OSTimeDly(10); 
		Scen_Send(0xE5, G_SENCE_DB_UV); 
		OSTimeDly(10);
		Scen_Send(0x50,0x25) ; 
		Scen_Send(0xE7, G_SENCE_DB_UV); 	
		Scen_Send(0x50,0x01 ) ;	
		Select_Send(0xE9);   
/*----------------------------------------------------*/	
		CheckMode();  
	}	
}

void PhotographFour()
{
	
	if(System.Dsp.Mode == CHECK_MODE)
	{
	  //	 SHOW_SCREEN(0xE8, WcharToChar(L"Ç©·¢²É¼¯ÇëÉÔºó") );	//	   "Wait..."
/*----------------------------------------------------*/
		if(System.Dsp.Sensor !=SENSOR1)
		{	
			Top_W_On();
			Sensor1();
		}
	 	if(System.Dsp.CheckMode.Zoom != X0)
		{
			Check_View_Zoom(X0);
		}

	 	System.SignOutCount++ ; 
		Light_Init();
	   	TOP_W = 0;
//		Scen_Send(G_SENCE_WT,0x00);
		System.Led.Statu = TOP_WHITE_ON ; 	
				
		Select_Send(0x74);			//´´½¨ÐÂ·Ö×é	
		Scen_Send(0xE5, G_SENCE_WT); 
        OSTimeDly(5); 

//	 	Scen_Send(0xE7, G_SENCE_WT); 	
		Dsp_Send_Data(0xE7, G_SENCE_WT,DeepCompression, D_NON,D_NON); 
	 //	Dsp_Send_Data(0x21,0x00,0x01,0x01,D_NON);
	 //	OSTimeDly(200);
/*----------------------------------------------------*/	// 
//	Top_IR940_On();

		Light_Init();
		TOP_IR940=0;
		Scen_Send(G_SENCE_T_IR940,0x02);
		System.Led.Statu= TOP_IR940_ON ; 

		Scen_Send(0xD7,System.Dsp.photo.Scene[G_SENCE_T_IR940].Sharpness) ; 		    //Èñ¶È
        OSTimeDly(1);
		Scen_Send(0xD8,System.Dsp.photo.Scene[G_SENCE_T_IR940].Saturation) ;			//±¥ºÍ¶È
		OSTimeDly(1); 		 
        Scen_Send(0xD9,System.Dsp.photo.Scene[G_SENCE_T_IR940].Brightness) ; 		//ÁÁ¶È
        OSTimeDly(1); 
 //       Scen_Send(0xDA,System.Dsp.photo.Scene[G_SENCE_T_IR940].Contrast) ; 		    //¶Ô±È¶È
 //       OSTimeDly(5); 
		Scen_Send(0xE5, G_SENCE_T_IR940); 
		OSTimeDly(5); 
	//	Dsp_Send_Data(0x21,0x00,0x01,0x01,D_NON);
	//    Scen_Send(0xE7, G_SENCE_T_IR940); 	
		Dsp_Send_Data(0xE7, G_SENCE_T_IR940,DeepCompression, D_NON,D_NON); 
	//	OSTimeDly(50); 

/*----------------------------------------------------*/	 //µ×ºìÍâ									 							
	//	Bot_IR_On(); 
		Light_Init();
		BOT_IR=0;		
		Scen_Send(G_SENCE_B_IR,0x02); 

//		System.Led.Statu = BOT_IR_ON ; 
//
//		Scen_Send(0xD7,System.Dsp.photo.Scene[G_SENCE_B_IR].Sharpness) ; 		    //Èñ¶È
//        OSTimeDly(5); 
// //       Scen_Send(0xDA,System.Dsp.photo.Scene[G_SENCE_B_IR].Contrast) ; 		    //¶Ô±È¶È
// //       OSTimeDly(5); 
//        Scen_Send(0xD9,System.Dsp.photo.Scene[G_SENCE_B_IR].Brightness) ; 		//ÁÁ¶È
//        OSTimeDly(5); 
//		Scen_Send(0xD8,System.Dsp.photo.Scene[G_SENCE_B_IR].Saturation) ;			//±¥ºÍ¶È
//		OSTimeDly(5); 
//		Scen_Send(0xE5, G_SENCE_B_IR); 
//		OSTimeDly(5);
//	    Scen_Send(0xE7, G_SENCE_B_IR); 

		OSTimeDly(10); 		
		Dsp_Send_Data(0x21,0x00,0x01,DeepCompression,D_NON);												
	// 	OSTimeDly(50);
/*----------------------------------------------------*/ 	//×Ï¹â
	 //	Double_UV_On(); 
	//	Scen_Send(0xe5,PH_SENCE_TOP_UV_70);	
	  	Light_Init();
		LEFT_UV=0;
	//	OSTimeDly(100);
		RIGHT_UV=0;
		Scen_Send(G_SENCE_DB_UV,0x00);	
		OSTimeDly(1);
		System.Led.Statu = DB_UV_ON ; 

 		Scen_Send(0xD7,System.Dsp.photo.Scene[G_SENCE_DB_UV].Sharpness) ; 		    //Èñ¶È
        OSTimeDly(1); 
  //      Scen_Send(0xDA,System.Dsp.photo.Scene[G_SENCE_DB_UV].Contrast) ; 		    //¶Ô±È¶È
  //      OSTimeDly(5); 
        Scen_Send(0xD9,System.Dsp.photo.Scene[G_SENCE_DB_UV].Brightness) ; 		//ÁÁ¶È
        OSTimeDly(1); 
		Scen_Send(0xD8,System.Dsp.photo.Scene[G_SENCE_DB_UV].Saturation) ;			//±¥ºÍ¶È
		OSTimeDly(1); 
		Scen_Send(0xE5, G_SENCE_DB_UV); 
		OSTimeDly(1);

		Scen_Send(0x50,0x25) ; 
//		Dsp_Send_Data(0xFF,G_SENCE_DB_UV,0xA0,0x70,D_NON);					
//		Scen_Send(0xD8,0xF1) ; 								
//		OSTimeDly(10);	

	//	Scen_Send(0xE7, G_SENCE_DB_UV); 	
		Dsp_Send_Data(0xE7, G_SENCE_DB_UV,DeepCompression, D_NON,D_NON); 
	 //	Dsp_Send_Data(0x21,0x00,0x01,0x01,D_NON);
	//	OSTimeDly(40);
		Scen_Send(0x50,0x01 ) ;	
//		Scen_Send(0xD8,0x80) ; 			 
//		Dsp_Send_Data(0xFF,0x01,0x80,0x80,0x80);	
		Select_Send(0xE9);   
/*----------------------------------------------------*/	       
		CheckMode();  
	}
}

// void PhotographFour()
//{
//	
//	if(System.Dsp.Mode == CHECK_MODE)
//	{
//	  //	 SHOW_SCREEN(0xE8, WcharToChar(L"Ç©·¢²É¼¯ÇëÉÔºó") );	//	   "Wait..."
///*----------------------------------------------------*/
//		if(System.Dsp.Sensor !=SENSOR1)
//		{	
//			Top_W_On();
//			Sensor1();
//		}
//	 	if(System.Dsp.CheckMode.Zoom != X0)
//		{
//			Check_View_Zoom(X0);
//		}
//
//
//	 	System.SignOutCount++ ; 
//		Light_Init();
//	   	TOP_W = 0;
//		Scen_Send(G_SENCE_WT,0x00);
//		System.Led.Statu = TOP_WHITE_ON ; 	
//
//			
//		Select_Send(0x74);			//´´½¨ÐÂ·Ö×é
//	//	Scen_Send(0xE5, PH_SENCE_TOP_WT_70); 	
//	 //	OSTimeDly(10);				
//
//		Scen_Send(0xD7,System.Dsp.photo.Scene[G_SENCE_WT].Sharpness) ; 		    //Èñ¶È
//        OSTimeDly(5); 		
//		Scen_Send(0xD8,System.Dsp.photo.Scene[G_SENCE_WT].Saturation) ;			//±¥ºÍ¶È
//		OSTimeDly(5); 
//        Scen_Send(0xD9,System.Dsp.photo.Scene[G_SENCE_WT].Brightness) ; 		//ÁÁ¶È
//        OSTimeDly(5); 
//        Scen_Send(0xDA,System.Dsp.photo.Scene[G_SENCE_WT].Contrast) ; 		    //¶Ô±È¶È
//        OSTimeDly(5); 
//
//		Scen_Send(0xE5, G_SENCE_WT); 
//		OSTimeDly(10); 
//
//	 	Scen_Send(0xE7, G_SENCE_WT); 	
//	 //	Dsp_Send_Data(0x21,0x00,0x01,0x01,D_NON);
//	 //	OSTimeDly(200);
///*----------------------------------------------------*/	//		
//	//	Top_IR940_On(); 
//		Light_Init();
//		TOP_IR940=0;
//		Scen_Send(G_SENCE_T_IR940,0x02);
//		System.Led.Statu= TOP_IR940_ON ; 
//
//		Scen_Send(0xD7,System.Dsp.photo.Scene[G_SENCE_T_IR940].Sharpness) ; 		    //Èñ¶È
//        OSTimeDly(10);
//		Scen_Send(0xD8,System.Dsp.photo.Scene[G_SENCE_T_IR940].Saturation) ;			//±¥ºÍ¶È
//		OSTimeDly(10); 		 
//        Scen_Send(0xD9,System.Dsp.photo.Scene[G_SENCE_T_IR940].Brightness) ; 		//ÁÁ¶È
//        OSTimeDly(10); 
//        Scen_Send(0xDA,System.Dsp.photo.Scene[G_SENCE_T_IR940].Contrast) ; 		    //¶Ô±È¶È
//        OSTimeDly(10); 
//		Scen_Send(0xE5, G_SENCE_T_IR940); 
//		OSTimeDly(10); 
//	//	Dsp_Send_Data(0x21,0x00,0x01,0x01,D_NON);
//	    Scen_Send(0xE7, G_SENCE_T_IR940); 	
//	//	OSTimeDly(50); 
//
///*----------------------------------------------------*/	 //µ×ºìÍâ									 							
//	//	Bot_IR_On(); 
//		Light_Init();
//		BOT_IR=0;		
//		Scen_Send(G_SENCE_B_IR,0x02); 
//		System.Led.Statu = BOT_IR_ON ; 
//
//		Scen_Send(0xD7,System.Dsp.photo.Scene[G_SENCE_B_IR].Sharpness) ; 		    //Èñ¶È
//        OSTimeDly(10); 
//        Scen_Send(0xDA,System.Dsp.photo.Scene[G_SENCE_B_IR].Contrast) ; 		    //¶Ô±È¶È
//        OSTimeDly(10); 
//        Scen_Send(0xD9,System.Dsp.photo.Scene[G_SENCE_B_IR].Brightness) ; 		//ÁÁ¶È
//        OSTimeDly(10); 
//		Scen_Send(0xD8,System.Dsp.photo.Scene[G_SENCE_B_IR].Saturation) ;			//±¥ºÍ¶È
//		OSTimeDly(10); 
//		Scen_Send(0xE5, G_SENCE_B_IR); 
//		OSTimeDly(10);
//
//		//OSTimeDly(10); 		
//		Dsp_Send_Data(0x21,0x00,0x01,0x01,D_NON);												
//	// 	OSTimeDly(50);
///*----------------------------------------------------*/ 	//×Ï¹â
//
//
//
//
//	 //	Double_UV_On(); 
//	//	Scen_Send(0xe5,PH_SENCE_TOP_UV_70);	
//	  	Light_Init();
//		LEFT_UV=0;
//	//	OSTimeDly(100);
//		RIGHT_UV=0;
//		Scen_Send(G_SENCE_DB_UV,0x00);	
//		OSTimeDly(10);
//		System.Led.Statu = DB_UV_ON ; 
//
// 		Scen_Send(0xD7,System.Dsp.photo.Scene[G_SENCE_DB_UV].Sharpness) ; 		    //Èñ¶È
//        OSTimeDly(10); 
//        Scen_Send(0xDA,System.Dsp.photo.Scene[G_SENCE_DB_UV].Contrast) ; 		    //¶Ô±È¶È
//        OSTimeDly(10); 
//        Scen_Send(0xD9,System.Dsp.photo.Scene[G_SENCE_DB_UV].Brightness) ; 		//ÁÁ¶È
//        OSTimeDly(10); 
//		Scen_Send(0xD8,System.Dsp.photo.Scene[G_SENCE_DB_UV].Saturation) ;			//±¥ºÍ¶È
//		OSTimeDly(10); 
//		Scen_Send(0xE5, G_SENCE_DB_UV); 
//		OSTimeDly(10);
//
//
//		Scen_Send(0x50,0x25) ; 
//
////		Dsp_Send_Data(0xFF,G_SENCE_DB_UV,0xA0,0x70,D_NON);					
////		Scen_Send(0xD8,0xF1) ; 								
////		OSTimeDly(10);	
//		Scen_Send(0xE7, G_SENCE_DB_UV); 	
//	 //	Dsp_Send_Data(0x21,0x00,0x01,0x01,D_NON);
//	//	OSTimeDly(40);
//
//		Scen_Send(0x50,0x01 ) ;	
////		Scen_Send(0xD8,0x80) ; 			 
////		Dsp_Send_Data(0xFF,0x01,0x80,0x80,0x80);	
//		Select_Send(0xE9);   
///*----------------------------------------------------*/	 
//        
//		CheckMode();  
//
//		
//	  //  Select_Send(0xE9); // ½áÊøµÈ´ýÏÔÊ¾	
////		OSTimeDly(50) ; 
//	}
//}
//
//

/*==================================================================
* Function	: PhotographEight
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void PhotographEight()
{
	if(System.Dsp.Mode == CHECK_MODE)
	{
			SHOW_SCREEN(0xE8,"Wait..." );
			OSTimeDly(10);
			if(System.Dsp.Sensor != SENSOR2)
			{
				Sensor2(); 
			}	
	/*----------------------------------------------------*/  //²à°×				
			Right_IR850_On();   							
			Select_Send(0x21);	
			OSTimeDly(200);

	/*----------------------------------------------------*///×Ï¹â				 
//			Double_UV_On();	 
//			Scen_Send(0xe5,PH_SENCE_TOP_UV_71);
//			OSTimeDly(100);	
//			Scen_Send(0xE7, PH_SENCE_TOP_UV_71); 	
//			OSTimeDly(300);
	/*----------------------------------------------------*///²àºìÍâ
			Right_IR850_On(); 
			OSTimeDly(100);
		    Select_Send(0x21); 
			OSTimeDly(200); 	

	/*----------------------------------------------------*///µ×ºìÍâ															 
			Bot_IR_On();	
			OSTimeDly(160); 		
			Select_Send(0x21); 													
		 	OSTimeDly(200);			

	/*----------------------------------------------------*///sensor3		
//			Sensor3();						
//	/*----------------------------------------------------*///¶¥°×¹â									
//			Top_W_On(); 
//			OSTimeDly(100);
//			Select_Send(0x21); 								//ÅÄÕÕ
//			OSTimeDly(250);
//	/*----------------------------------------------------*///²à°×¹â
//			Right_W_On(); 
//			OSTimeDly(200);
//		    Select_Send(0x21); 
//			OSTimeDly(200); 	
//	/*----------------------------------------------------*///×Ï¹â
//			Double_UV_On(); 
//			OSTimeDly(10);	
//			Scen_Send(0xe5,PH_SENCE_TOP_UV_72);
//			
//			OSTimeDly(100);	
//			Scen_Send(0xE7, PH_SENCE_TOP_UV_72); 	
//			OSTimeDly(300);
//	/*----------------------------------------------------*/ //IR					
//										 
//			Right_IR770_On(); 
//			OSTimeDly(200);
//			Select_Send(0x21); 													
//		 	OSTimeDly(200);			
//			
//	/*----------------------------------------------------*/
			CheckMode(); 
			
	 	//	Select_Send(0xE9); // ½áÊøµÈ´ýÏÔÊ¾ 
	}			
}

/*==================================================================
* Function	: PhotoDelOne
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void PhotoDelOne()
{
	if(System.Dsp.Mode == VIEW_MODE)
	{
		Select_Send(0x3C);
		Local_SignOutCount  = 0  ; 
		System.Local_SignOutCount_Flag  =0	;
		OSTimeDly(200);	
	}
}

/*==================================================================
* Function	: PhotoDelAll
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void PhotoDelAll(void) //(uint8_t KeyValue) 
{
	uint16_t  i = 0  ;
	uint8_t key = 0  ; 
	uint8_t KeyValue = 0x09 ; 
	if(System.Dsp.Mode == VIEW_MODE)
	{
		SHOW_SCREEN_T_W(0xE3,0x05,WcharToChar(L"É¾³ýËùÓÐÕÕÆ¬?"));	//SHOW_SCREENW(0xE8, WcharToChar(L"Ç©·¢Êý¾Ý²É¼¯,ÇëÉÔºò...") );	
	//	SHOW_SCREENW(0xE8, WcharToChar(L"É¾³ýËùÓÐÕÕÆ¬?") );
	 
	 	while(KeyScan());
		while(i++ < 45)
		{		
			key =  KeyScan(); 
		
			if(key)
			{
				if(KeyValue == key)
				{
					SHOW_SCREEN_T_W(0xE3,0x05,WcharToChar(L"É¾³ýÖÐ,ÇëÉÔºò..."));		
				 // 	SHOW_SCREENW(0xE8, WcharToChar(L"É¾³ýÖÐ...") );

					if(System.PhotoNum != 0)
					{
				 		System.PhotoNum = 0 ;  //4ÕÅÕÕÆ¬
						System.Sys.SaveInfoFlag  = 0x01  ;
					}
																	
					Local_SignOutCount  = 0  ; 
					System.Local_SignOutCount_Flag  =0	;
					Select_Send_LONG(0x24);
				//	Format_SDcard(); 					
					OSTimeDly(300);	

					System.SignOutCount = 0 ;
			//		Select_Send(0xE9);												
				//	while(KeyValue != KeyScan());		  //µÈ´ýÔÙ°´Ò»´Î
					break ;
				}
				else 
				{
					break ; 
				}				
			}
			OSTimeDly(10) ; 
		}
		Select_Send(0xE9);		
	}
	
}



/*==================================================================
* Function	: PriorExposure
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void PriorExposure()
{



	if(System.Dsp.Mode == CHECK_MODE)
	{	
			uint8_t i = 0 ; 	
			CheckMode(); 


			//Êý¾Ý³õÊ¼»¯
			for(i=0;i<30;i++)
			{
				System.Dsp.photo.photo[i] = 0x00000000  ; 
			}
			//Ä¬ÈÏ°×¹â²ÎÊý
			
			System.Dsp.photo.Scene[G_SENCE_WT].FB1   = 0x08;
			System.Dsp.photo.Scene[G_SENCE_WT].FB2   = 0x08	; 
			System.Dsp.photo.Scene[G_SENCE_WT].FC1   = 0x16	;
			System.Dsp.photo.Scene[G_SENCE_WT].FC2   = 0x16	; 
			System.Dsp.photo.Scene[G_SENCE_WT].WB1   = 0xA6 ;
			System.Dsp.photo.Scene[G_SENCE_WT].WB2   = 0x7E ; 				
            System.Dsp.photo.Scene[G_SENCE_WT].Sharpness = 0x80 ; 
			//System.Dsp.photo.Scene[G_SENCE_WT].Contrast	 = 0x00 ; 	
			System.Dsp.photo.Scene[G_SENCE_WT].Saturation = 0x6a;
			System.Dsp.photo.Scene[G_SENCE_WT].Brightness = 0x80 ;  

			
            
			
			//940²ÎÊý
			System.Dsp.photo.Scene[G_SENCE_T_IR940].FB1   = 0x10;
			System.Dsp.photo.Scene[G_SENCE_T_IR940].FB2   = 0x10	; 
			System.Dsp.photo.Scene[G_SENCE_T_IR940].FC1   = 0x30	;
			System.Dsp.photo.Scene[G_SENCE_T_IR940].FC2   = 0x30	; 
			System.Dsp.photo.Scene[G_SENCE_T_IR940].WB1   = 0x48 ;
			System.Dsp.photo.Scene[G_SENCE_T_IR940].WB2   = 0xC0 ; 				
            System.Dsp.photo.Scene[G_SENCE_T_IR940].Sharpness = 0x90; 

			
			//×ó°×¹â²ÎÊý
			System.Dsp.photo.Scene[G_SENCE_L_W].FB1   = 0x09;
			System.Dsp.photo.Scene[G_SENCE_L_W].FB2   = 0x09	; 
			System.Dsp.photo.Scene[G_SENCE_L_W].FC1   = 0x30	;
			System.Dsp.photo.Scene[G_SENCE_L_W].FC2   = 0x30	; 		
			//×óºìÍâ²ÎÊý
			System.Dsp.photo.Scene[G_SENCE_L_IR].FB1   = 0x09;
			System.Dsp.photo.Scene[G_SENCE_L_IR].FB2   = 0x09	; 
			System.Dsp.photo.Scene[G_SENCE_L_IR].FC1   = 0x30	;
			System.Dsp.photo.Scene[G_SENCE_L_IR].FC2   = 0x30	; 		
			//Í¸ºìÍâ²Îý

			//uV²ÎÊý
			System.Dsp.photo.Scene[G_SENCE_DB_UV].FB1   = 0x30;
			System.Dsp.photo.Scene[G_SENCE_DB_UV].FB2   = 0x30	; 
			System.Dsp.photo.Scene[G_SENCE_DB_UV].FC1   = 0x32	;
			System.Dsp.photo.Scene[G_SENCE_DB_UV].FC2   = 0x32	; 
			System.Dsp.photo.Scene[G_SENCE_DB_UV].WB1   = 0xA0 ;
			System.Dsp.photo.Scene[G_SENCE_DB_UV].WB2   = 0x70 ; 				
            System.Dsp.photo.Scene[G_SENCE_DB_UV].Sharpness = 0xB1; 
			//System.Dsp.photo.Scene[G_SENCE_DB_UV].Contrast	 = 0x00 ; 	
			System.Dsp.photo.Scene[G_SENCE_DB_UV].Saturation = 0xA0;
			System.Dsp.photo.Scene[G_SENCE_DB_UV].Brightness = 0x70 ; 
			//
			Select_Send(0x96);			//´´½¨ÐÂ·Ö×é
			OSTimeDly(300);
/////////////////////////////////////////////////////////////°×¹â

			System.Dsp.photo.Flag = 	G_SENCE_WT ; 
			ArguPriorExposure()   ;
/////////////////////////////////////////////////////////////×ó°×¹â
 			System.Dsp.photo.Flag = 	G_SENCE_L_W	  ;
			ArguPriorExposure()   ;

/////////////////////////////////////////////////////////////×óºìÍâ
 			System.Dsp.photo.Flag = 	G_SENCE_L_IR	  ;
			ArguPriorExposure()   ;
/////////////////////////////////////////////////////////////940
			System.Dsp.photo.Flag = 	G_SENCE_T_IR940	  ;
			ArguPriorExposure()   ;
///////////////////////////////////////////////////////////////Í¸850
			System.Dsp.photo.Flag = 	G_SENCE_B_IR	  ;
			ArguPriorExposure()   ;
/////////////////////////////////////////////////////////////UV
			System.Dsp.photo.Flag = 	G_SENCE_DB_UV	  ;
			ArguPriorExposure()   ;
			OSTimeDly(200); 

//			//ÖØ·¢ £¬µÚÒ»´Î¿ÉÄÜÆØ¹â
//			DSP_SEND(4, &TW_Snr1EV_FB[0]);
//      		OSTimeDly(10); 
//			DSP_SEND(4, &TW_Snr1EV_FC[0]);
//			OSTimeDly(10); 
//			Scen_Send(0xD8,0x80) ;
//			OSTimeDly(10); 
//			Dsp_Send_Data(0xFF,G_SENCE_WT,0xAF,0x78,D_NON);
////			Scen_Send(0xD8,0x00) ;
////			Dsp_Send_Data(0xFF,G_SENCE_WT,0x00,0x00,D_NON);	
//				
//				
//			OSTimeDly(20); 

//			Scen_Send(G_SENCE_WT,0x01 ) ; 
//			OSTimeDly(300);	
//		//	OSTimeDly(300);
//			Scen_Send(0xE6, G_SENCE_WT); 
//			OSTimeDly(300);
//			Scen_Send(0xD8,0x00) ;
///////////////////////////////////////////////////////
////			Scen_Send(0xE6, PH_SENCE_R_IR850); 
////			OSTimeDly(300);
//			Left_IR850_On();
//			DSP_SEND(4, &L_IR_Snr1EV_FB[0]);
//      		OSTimeDly(10); 
//			DSP_SEND(4, &L_IR_Snr1EV_FC[0]);
//			OSTimeDly(10); 
//			Scen_Send(G_SENCE_L_IR,0x01 ) ; 
//			OSTimeDly(300);	
//		//	OSTimeDly(300);
//			Scen_Send(0xE6, G_SENCE_L_IR); 
//			OSTimeDly(300);
/////////////////////////////////////////////////////////////////
//			Top_IR940_On();
//			OSTimeDly(100); 
//
//			Dsp_Send_Data(0xFF,G_SENCE_T_IR940,0x50,0xD1,D_NON);
//
//////			DSP_SEND(4, &IR940_Snr1EV_FB[0]);
//////      		OSTimeDly(10); 
//////			DSP_SEND(4, &IR940_Snr1EV_FC[0]);
//////			OSTimeDly(100); 
//////			Scen_Send(G_SENCE_T_IR940,0x03 ) ; 
//			OSTimeDly(300);	
//		//	OSTimeDly(300);
//			Scen_Send(0xE6, G_SENCE_T_IR940); 
//			OSTimeDly(300);

/*----------------------------------------------------*/ //×Ï¹â
//		 	Double_UV_On();
//			OSTimeDly(300);		
//			Select_Send(0x96);			 
//			OSTimeDly(10);
//			Scen_Send(0xE6, G_SENCE_DB_UV); 														
//			OSTimeDly(600);		
//		 	Double_UV_On();
// 
//			Scen_Send(0x50,0x25 ) ; 
//			OSTimeDly(10); 
//			Scen_Send(0xD8,0xF1) ; 	
//		    Dsp_Send_Data(0xFF,G_SENCE_DB_UV,0xA0,0x70,D_NON);
//			//OSTimeDly(10); 
//
//			DSP_SEND(4, &UV_Snr1EV_FB[0]);
//      		OSTimeDly(10); 
//			DSP_SEND(4, &UV_Snr1EV_FC[0]);
//			OSTimeDly(10); 
//			Scen_Send(G_SENCE_DB_UV,0x01 ) ; 
//			OSTimeDly(300);		
//			
//			Select_Send(0x96);			 
//			OSTimeDly(10);
//			Scen_Send(0xE6, G_SENCE_DB_UV); 														
//			OSTimeDly(600);	
//
//			Scen_Send(0x50,0x01) ;
//			Scen_Send(0xD8,0x80) ; 	 	
////			Dsp_Send_Data(0xFF,0x01,0x80,0x80,0x80);
//			OSTimeDly(10); 

			CheckMode(); 

	}

}



void Vir_Init()
{
	System.Key.Value = 0 ; 
	
	System.Led.Statu = TOP_WHITE_ON ; 
	
	System.Dsp.Mode = CHECK_MODE; 

	
	System.Dsp.CheckMode.Zoom = X0 ; 
	System.Dsp.ViewMode.Zoom  = X0 ; 
	System.Dsp.TF_Mode.t = 0 ; 
	System.Dsp.PccamMode.ConnectIn = 0 ; 
	System.Dsp.Sensor =SENSOR1 ; 
	System.Dsp.SD = OUT ; 
	System.Usb.NewUsbStatu 	= USB_OUT; 
	System.Usb.OldUsbStatu 	= USB_OUT;  
	System.Usb.UsbStatuLabel= 0 ;
	
	System.Sys.PassWrd.Code[0] = 1 ; 
	System.Sys.PassWrd.Code[1] = 2 ; 
	System.Sys.PassWrd.Code[2] = 3 ;
	System.Sys.PassWrd.Code[3] = 4 ; 
//
	System.Sys.PassWrd.InputErrCount = 0 ; 
	System.Sys.PassWrd.LockTime	= 0 ; 
//	System.Sys.SaveInfoFlag = 1 ; 
	System.Sys.NonFirstTimeUseFlag = 0x01 ; 

	SysVersionChange() ; 
	System.Sys.Data.info.SoftwareVer[0]	 =SysVersion[0];	//V1.02.016
 	System.Sys.Data.info.SoftwareVer[1]	 =SysVersion[1];
	System.Sys.Data.info.SoftwareVer[2]	 =SysVersion[2];  

// 	System.Sys.Data.info.HardwareVer[0]	 =0x56312E31;	//V1.14.001
// 	System.Sys.Data.info.HardwareVer[1]	 =0x352E3030;
//	System.Sys.Data.info.HardwareVer[2]	 =0x31000000; 
//
// 	System.Sys.Data.info.MachineType[0]	 =0x41442D31; 
// 	System.Sys.Data.info.MachineType[1]	 =0x36000000;
//	System.Sys.Data.info.MachineType[2]	 =0x30000000;  
//
//  	System.Sys.Data.info.CdKey[0]	 =0x30313233; 	 //ÐòÁÐºÅ 
// 	System.Sys.Data.info.CdKey[1]	 =0x34353637;
//	System.Sys.Data.info.CdKey[2]	 =0x38000000;  
//
//  	System.Sys.Data.info.MachineNum[0]	 =0x30313233; 	 //±àºÅ
// 	System.Sys.Data.info.MachineNum[1]	 =0x34353637;
//	System.Sys.Data.info.MachineNum[2]	 =0x38000000;  
//
//   	System.Sys.Data.info.ProductDate[0]	 =0x32303134; 	 //Éú²úÈÕÆÚ
// 	System.Sys.Data.info.ProductDate[1]	 =0x30373330;
//	System.Sys.Data.info.ProductDate[2]	 =0x33000000;  

	System.Error = NON ; 

//	ADJ_ExpSetFB[0]=0xFB ; 
//	ADJ_ExpSetFB[1]=0x01 ; 
//	ADJ_ExpSetFB[2]=0x20 ; 
//	ADJ_ExpSetFB[3]=0x20 ; 
//
//	ADJ_ExpSetFC[0]=0xFC ; 
//	ADJ_ExpSetFC[1]=0x01 ; 
//	ADJ_ExpSetFC[2]=0x18 ; 
//	ADJ_ExpSetFC[3]=0x18 ; 		

//	date[6] = 0x13;  
//	date[5] = 0x01; 
//	date[4] = 0x01;
//	date[3] = 0x01;
//	date[2] = 0x01; 
//	date[1] = 0x01;
//	date[0] = 0x01;
//    DS1307_WR(&date[0]); 
}

void Vir_Init_Update()
{
	System.Key.Value = 0 ; 
	
	System.Led.Statu = TOP_WHITE_ON ; 
	
	System.Dsp.Mode = CHECK_MODE; 

	
	System.Dsp.CheckMode.Zoom = X0 ; 
	System.Dsp.ViewMode.Zoom  = X0 ; 
	System.Dsp.TF_Mode.t = 0 ; 
	System.Dsp.PccamMode.ConnectIn = 0 ; 
	System.Dsp.Sensor =SENSOR1 ; 
	System.Dsp.SD = OUT ; 
	System.Usb.NewUsbStatu 	= USB_OUT; 
	System.Usb.OldUsbStatu 	= USB_OUT;  
	System.Usb.UsbStatuLabel= 0 ;
	 //Éý¼¶¹Ì¼þ²»»Ö¸´ÃÜÂë
	System.Sys.PassWrd.LockTime	= 0 ; 
	System.Sys.SaveInfoFlag = 0 ; 
	System.Sys.NonFirstTimeUseFlag = 0x01 ; 

	System.Sys.Data.info.SoftwareVer[0]	 =SysVersion[0];	 
 	System.Sys.Data.info.SoftwareVer[1]	 =SysVersion[1];
	System.Sys.Data.info.SoftwareVer[2]	 =SysVersion[2];  
	DeepCompression = 0x06 ;
	System.Error = NON ; 
}
/*==================================================================
* Function	: PasswdFuc
* Description	: °´¼üÊäÈëÃÜÂë²Ù×÷
* Input Para	: 	keyReturnValue : ÊäÈë·µ»ØµÄ°´¼ü¼üÖµ 
					void (*Fuc)(void) °´¼ü·µ»ØµÄ³¡¾°  
					void (*PasswdFinish)() ÃÜÂëÊäÈë³É¹¦ºóµÄ³¡¾°
* Output Para	: 
* Return Value: 
==================================================================*/
void VerifyPassword(uint8_t keyReturnValue,void (*Fuc)(),void (*PasswdFinish)() )
{   
	uint16_t nonBtnDwnTime = 0 ; 
	uint8_t i = 0 ; 
	uint8_t InputPasswdLength=0 ; 
	uint32_t temp = 0 ;
	uint8_t PassWord[PASSWORD_LENGTH]; 

	
	//ÅÐ±ð´íÎóÊäÈë´ÎÊý
	if(System.Sys.PassWrd.InputErrCount  >= INPUT_ERR_TIME_MAX)
	{
		SHOW_SCREEN(0xE3,"Password Locked");
		OSTimeDly(300) ;
		return ; 
	}
	//³õÊ¼»¯

	Light_Init(); 

//	DS1307_RD(&date[0]); 
//	temp = sTime(NowTime) ;
// 	System.Sys.PassWrd.InputLength = 0 ; 
// 	System.Sys.PassWrd.InputErrCount = 0 ;  //Á¬ÐøÊäÈë¼¸´ÎÃÜÂëÍË»ØºóÈÔÓÐÐ§

	for(i=0;i<PASSWORD_LENGTH;i++)
	{
		PassWord[i] = 0 ;
	} //System.Sys.PassWrd.InputCode[i] = 0x00 ;
	
	SHOW_SCREENA(0xE8,(16),"Enter Password:\nXXXXXXXX");

	while(KeyScan()); 
	while(nonBtnDwnTime++ <= 65535)
	{	//°´¼üÉ¨Ãè
		System.Key.Value = KeyScan();  
		System.Key.Keylong = &Keylong ;
		//¼üÖµ´¦Àí
		if(System.Key.Value)
		{    
			
			nonBtnDwnTime = 0 ; 
 			if(System.Key.Value == keyReturnValue)
			{
				if(*System.Key.Keylong)
				{ 
				
				}
				else
				{
				  GR_DBG_PRINTF("exit the viewMode\n\n"); break ; 
				}
				
			} 
			else
			{
				PassWord[InputPasswdLength++] = System.Key.Value;
				SHOW_SCREENA(0xE8,(16+InputPasswdLength),"Enter Password:\nXXXXXXXX"); 
			}
		}	
		//¼üÖµÅÐ¶Ï
		if(InputPasswdLength == PASSWORD_LENGTH)
		{
			InputPasswdLength = 0 ;  //³õÊ¼»¯³¤¶È£¬·ÀÖ¹¶þ´ÎÅÐ¶ÏÃÜÂë ¡£ 
			for(i=0 ; i<PASSWORD_LENGTH;i++)
			{
				if(PassWord[i] == System.Sys.PassWrd.Code[i])
				{
					if(i == (PASSWORD_LENGTH - 1))
					{
						System.Sys.PassWrd.InputErrCount = 0 ; 
						Select_Send(0xE9);
						(*PasswdFinish)();
						//OSTimeDly(200); 
						GR_DBG_PRINTF("Machine is in viewMode\n\n") ; 
						return ; 
					}
				}
				else
				{
					SHOW_SCREEN(0xE8,  "Password Error"); 
					OSTimeDly(50);
					GR_DBG_PRINTF("AAASystem.Sys.PassWrd.InputErrCount is :%d",System.Sys.PassWrd.InputErrCount);	
					if(++System.Sys.PassWrd.InputErrCount >= INPUT_ERR_TIME_MAX)
					{
						
//						DS1307_RD(&date[0]); 
//					 	System.Sys.PassWrd.LockTime = sTime(NowTime) ;
						temp = System.Sys.PassWrd.LockTime - temp ; 

						if(temp <= 2 ) 	//·ÀÖ¹ÔÚDS1307Ã»µçµÄÊ±ºò²»ÄÜ¶Á³öÐÅÏ¢
						{	
							System.Sys.PassWrd.InputErrCount = 0 ;  
						}
 						System.Sys.SaveInfoFlag = 1 ; 			//´æ´¢ÃÜÂëËø¶¨ÐÅÏ¢ ¡£ 			
						Select_Send(0xE9);	
						(*Fuc)() ; 
						return ;   
					} 
					SHOW_SCREENA(0xE8,(16),"Enter Password:\nXXXXXXXX");
					break; 
			 	}
			}
		
		}
		OSTimeDly(5) ;
	}
	Select_Send(0xE9);	
	(*Fuc)() ; 
	return ;  
}
/*==================================================================
* Function	: ChangePassWord
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void ChangePassWord()//(uint8_t keyReturnValue)
{
	uint16_t nonBtnDwnTime = 0 ; 
	uint8_t i = 0 ; 
	uint8_t PassWord1[PASSWORD_LENGTH], PassWord2[PASSWORD_LENGTH];
	uint8_t InputPasswdLength=0 ; 
	
//	System.Sys.PassWrd.InputLength = 0 ; 
//	System.Sys.PassWrd.InputErrCount = 0 ; 
	for(i=0;i<PASSWORD_LENGTH;i++)   
	{
		PassWord1[i]= 0 ; 
		PassWord2[i]= 0 ; 
	}
	SHOW_SCREENA(0xE8,20,"Enter New Password:\nXXXX"); 
	while(nonBtnDwnTime<62225)
	{
		System.Key.Value = KeyScan();
		System.Key.Keylong = &Keylong ; 
		if(System.Key.Value) 
		{	
			nonBtnDwnTime = 0 ; 
			
			if(System.Key.Value == 7)
			{
				continue ; 
			}	
			if(System.Key.Value== 9)//keyReturnValue )
			{
				if(System.Key.Keylong)
				{ 
					Select_Send(0xE9); return ; 		  
				}
			}
			else
			{
				PassWord1[InputPasswdLength++] = System.Key.Value;
				SHOW_SCREENA(0xE8,(20+InputPasswdLength),"Enter New Password:\nXXXXXXXX"); 
			}
			if(InputPasswdLength == PASSWORD_LENGTH)
			{
				break ; 
			}
		}
	}
	OSTimeDly(10); 
	if(InputPasswdLength == PASSWORD_LENGTH)
	{
		nonBtnDwnTime = 0 ; 
		InputPasswdLength = 0 ; 
		SHOW_SCREENA(0xE8,13,"Enter Again:\nXXXXXXXX");	
		while(nonBtnDwnTime<62225)	
		{
			System.Key.Value = KeyScan();
			System.Key.Keylong = &Keylong ; 
			if(System.Key.Value) 
			{	
				nonBtnDwnTime = 0 ; 
				
				if(System.Key.Value == 7)
				{
					continue ; 
				}	
				if(System.Key.Value== 9)//keyReturnValue )
				{
					if(System.Key.Keylong)
					{ 
						Select_Send(0xE9); return ; 		  
					}
				}
				else
				{
					PassWord2[InputPasswdLength++] = System.Key.Value;
					SHOW_SCREENA(0xE8,(13+InputPasswdLength),"Enter Again:\nXXXXXXXX");	
				}
				if(InputPasswdLength == PASSWORD_LENGTH)
				{
					InputPasswdLength  = 0 ; 
					for(i=0;i<PASSWORD_LENGTH;i++)
					{
						if(PassWord1[i] == PassWord2[i])
						{
							if(i == PASSWORD_LENGTH - 1)
							{
								for(i = 0 ;i< PASSWORD_LENGTH ;i++)     // ³É¹¦ ---±£´æÃÜÂë
								{
									System.Sys.PassWrd.Code[i] = PassWord1[i];
								}
 								System.Sys.SaveInfoFlag = 1 ; 			//±£´æ

								SHOW_SCREEN(0xE8,"Succeed"); 
								OSTimeDly(100); 
								Select_Send(0xE9); return ; 
							}
						}
						else
						{
							SHOW_SCREEN(0xE8,"Failed"); 
							OSTimeDly(100); 
							Select_Send(0xE9); return ; 
						}
					}
				}
			}
			OSTimeDly(10); 
		}
	}
	Select_Send(0xE9); return ;  
}

/*=================================================================================
* Function	: SystemReadBCKData
* Description	: ¶ÁÈ¡ÏµÍ³±£´æÐÅÏ¢ÄÚÈÝ
* Input Para	: 
* Output Para	: 
* Return Value: 
=================================================================================*/
void SystemReadBCKData()
{
	
	uint32_t DataAddrPasswd,Temp;
	uint8_t  i= 0  ; 
	UNLOCKREG();
	DrvFMC_EnableISP();
 	DataAddrPasswd = DrvFMC_ReadDataFlashBaseAddr()+PAGE_SIZE*0;
	
	for(i=0;i<21;i++)
	{
 		DrvFMC_Read ((DataAddrPasswd+i*4),  &Temp)	; 
		System.Sys.Data.SysData[i] = Temp ; 
	}

	for(i=0;i<PASSWORD_LENGTH;i++) 
 	{
 		DrvFMC_Read ((DataAddrPasswd +21*4+i*4), &Temp);
		System.Sys.PassWrd.Code[i] = Temp ;
	}	
	
	{ DrvFMC_Read ((DataAddrPasswd+30*4), &Temp); System.Sys.PassWrd.InputErrCount=(uint8_t)Temp  ;}
	{ DrvFMC_Read ((DataAddrPasswd+31*4), &Temp); System.Sys.PassWrd.LockTime = Temp	;}
	{ DrvFMC_Read ((DataAddrPasswd+32*4), &Temp); System.Sys.NonFirstTimeUseFlag	=(uint8_t)Temp;}	

	for(i=0;i<30;i++) 
 	{
 		DrvFMC_Read ((DataAddrPasswd +33*4+i*4), &Temp);
		System.Dsp.photo.photo[i] = Temp ;
	}
	{ DrvFMC_Read ((DataAddrPasswd+63*4), &Temp); System.PhotoNum 	=(uint8_t)Temp;}	
	{ DrvFMC_Read ((DataAddrPasswd+64*4), &Temp); DeepCompression 	=(uint8_t)Temp;}
			
	DrvFMC_DisableISP();
	LOCKREG();		
}


/*=================================================================================
* Function	: SysteWriteBCKData
* Description	: 
* Input Para	: 
* Output Para	: __________OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
* Return Value: 
=================================================================================*/
void SystemWriteBCKData() 
{
	uint32_t DataAddrPasswd,Temp;
	uint8_t  i= 0  ; 

	UNLOCKREG();
	DrvFMC_EnableISP();	
	DataAddrPasswd = DrvFMC_ReadDataFlashBaseAddr()+PAGE_SIZE*0;
	DrvFMC_Erase (DataAddrPasswd ); 
	
	 for(i=0;i<21;i++)						  //ÏµÍ³ÐÅÏ¢
	 {
	 	Temp = System.Sys.Data.SysData[i]; 
		DrvFMC_Write ((DataAddrPasswd+i*4), Temp);
	 }




	for(i=0;i<PASSWORD_LENGTH;i++) 			  //  ÃÜÂë
		{
			Temp = System.Sys.PassWrd.Code[i] ;
			DrvFMC_Write ((DataAddrPasswd+21*4+i*4), Temp);
		}

 //	DataAddrPasswd = DrvFMC_ReadDataFlashBaseAddr()+PAGE_SIZE*1;
//	DrvFMC_Erase (DataAddrPasswd ); 
	{Temp = (uint32_t)System.Sys.PassWrd.InputErrCount  ;DrvFMC_Write ((DataAddrPasswd+30*4), Temp);}
	{Temp =  System.Sys.PassWrd.LockTime	    		;DrvFMC_Write ((DataAddrPasswd+31*4), Temp);}
	{Temp = (uint32_t)System.Sys.NonFirstTimeUseFlag    ;DrvFMC_Write ((DataAddrPasswd+32*4), Temp);}		

	 for(i=0;i<30;i++)						 // ÕÕÆ¬ÐÅÏ¢
	 {
	 	Temp = System.Dsp.photo.photo[i] ; 
		DrvFMC_Write ((DataAddrPasswd+33*4+i*4), Temp);
	 }

	{Temp = (uint32_t)System.PhotoNum    ;DrvFMC_Write ((DataAddrPasswd+63*4), Temp);}	 
	{Temp = (uint32_t)DeepCompression    ;DrvFMC_Write ((DataAddrPasswd+64*4), Temp);}
			
	DrvFMC_DisableISP();
	LOCKREG();		
	

 	System.Sys.SaveInfoFlag = 0x00 ; 
}

void ConfigBCK() 
{	
	SystemReadBCKData(); 
 	if(  System.Sys.NonFirstTimeUseFlag != 0x01)   //µÚÒ»´Î³õÊ¼»¯
	//	||(System.Sys.Data.info.SoftwareVer[0]	!=SysVersion[0])
	//	||(System.Sys.Data.info.SoftwareVer[1]	!=SysVersion[1])
	//    ||(System.Sys.Data.info.SoftwareVer[2]	!=SysVersion[2]) )
	{
		OSTimeDly(300); 
		//SHOW_SCREEN(0xe3," Init Environment");
	   SHOW_SCREEN_T_W(0xE3,0x02,"Init Environment");
		//SHOW_SCREEN_T_W(0xE3,0x02,"Init Environment");
		//V1.02.016
 	
 


		Vir_Init() ;
		//³õÊ¼»¯ËùÓÐ±äÁ¿ÄÚÈÝ
 		System.Sys.SaveInfoFlag = 1 ; 
		OSTimeDly(300); 
	//	PriorExposure() ; 
	//	Select_Send(0xE9);
	}

 	if(   (System.Sys.Data.info.SoftwareVer[0]	!=SysVersion[0])   //³ÌÐòÉý¼¶
    	||(System.Sys.Data.info.SoftwareVer[1]	!=SysVersion[1])
        ||(System.Sys.Data.info.SoftwareVer[2]	!=SysVersion[2]) )
	{
		OSTimeDly(300); 
		SHOW_SCREEN_T_W(0xE3,0x02,"Update Firmware");
	//	SHOW_SCREENW(0xE3, WcharToChar(L"¹Ì¼þÉý¼¶") ); 
		Vir_Init_Update();
 		System.Sys.SaveInfoFlag = 1 ; 
		OSTimeDly(300); 
	}
}
void CycleViewFuc()
{
//	K4_LED	= ~K4_LED ; 
		
	 if(System.Dsp.ViewMode.CycleView== 1)			 // In the CycleViewMode 
	 {
		if(System.Dsp.Mode != VIEW_MODE)
		{
			System.Dsp.ViewMode.CycleView = 0 ;	 return ; 
		}	
			 
	 	if(System.Dsp.ViewMode.CycleViewPause == 0)		 //Pause 
	 	{
	      	if((System.Dsp.Mode == VIEW_MODE)&&(System.Dsp.ViewMode.Zoom == X0))
			{
				Select_Send(0x2b);OSTimeDly(50);   
			}	
		}
	 }
 	 OSTimeDly(50); 
}
void AdcIntCallback(uint32_t u32UserData)
{
	gu8AdcIntFlag =1;		
}


/*==================================================================
* Function	: ADC_Dispose
* Description	: OneSingleMode
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
uint32_t  ADC_Dispose(uint8_t Channel)
{	
	uint32_t i32ConversionData  ;  
	UNLOCKREG(x);
 	 
	DrvADC_Open(ADC_SINGLE_END, ADC_SINGLE_OP, 0, EXTERNAL_12MHZ, 3);	
//	GR_DBG_PRINTF("\n\nConversion rate: %d samples/second\n", DrvADC_GetConversionRate());
	DrvADC_SetADCOperationMode(ADC_SINGLE_OP);		 			/* Set the ADC operation mode as single mode */

	DrvADC_SetADCInputMode(ADC_SINGLE_END);	 		     		/* Set the ADC input mode */
	
	DrvADC_SetADCChannel((1<<Channel), ADC_SINGLE_END);			/* Set the ADC channel */												 	 		
    gu8AdcIntFlag = 0;	   	
    DrvADC_EnableADCInt(AdcIntCallback, 0);						  
    DrvADC_StartConvert();									    /* Start A/D conversion */
 
		
    while(gu8AdcIntFlag==0)/* Ó¦¸ÃÉè¶¨²Ù×÷²½Öè*/;     DrvADC_DisableADCInt(); 			/* Wait ADC interrupt */ 
	i32ConversionData = DrvADC_GetConversionData(Channel);
    OSTimeDly(1) ;														 

 	DrvADC_Close();
	LOCKREG(x);
	return 	 i32ConversionData ; 
}


/*==================================================================
* Function	: MedianFilter
* Description	: 
* Input Para	: 1²ÎÓëÔËËãµÄÊý×é 
                  2Êý×é³¤¶È
* Output Para	: Æ½¾ùÖµ
* Return Value: 
==================================================================*/
uint32_t MedianFilter(uint32_t *Array, uint8_t Num )
{
	uint8_t i = 0 ,j = 0 ;
	uint32_t Sum =0;
	
	for( i=0 ; i<Num;i++ )
	{
		for( j=i;j<Num;j++ )
		{
			 
			uint32_t  m = *(Array+i)<*(Array+j)? *(Array+i):*(Array+j) ; 
			*(Array+j)= *(Array+i)>*(Array+j)? *(Array+i):*(Array+j) ;
			*(Array+i)= m ; 
		}
		//GR_DBG_PRINTF("Array[%d] is : %d\n\n", i ,*(Array+i));
	}
  	for(i=1 ;i<Num-1;i++)
  	{
		Sum += *(Array+i); 
	}
	return Sum/(Num-2) ; 	
}
/*==================================================================
* Function	: ADC_Checking
* Description	: ÉèÖÃµÚÒ»µÚ¶þÍ¨µÀ
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
uint8_t ADC_Checking(uint32_t CHANNEL_VOLT ,uint32_t ERR_RANGE )
{
#ifdef ADC_CHECKING
#define ADC_VALUE_COUNT_MAX 10 //6  //must >=3 
	uint8_t count= 0,ValueCount = 0 ; 
	uint32_t ch1 = 0; 
	uint32_t ch2 = 0; 
  	uint32_t ADC_Value[ADC_VALUE_COUNT_MAX]; 	
//	GR_DBG_PRINTF("\nInput ADC......\n\n"); 
	for(;;)
	{		
		ch1 = ADC_Dispose(0x00) ; // GR_DBG_PRINTF("\nCH1 Is %X(%d)\n",ch1,ch1); 
		ch2 = ADC_Dispose(0x01) ; // GR_DBG_PRINTF("\nCH2 Is %X(%d)\n\n",ch2,ch2);

		if( ((ADC_STAND_VOLTAGE - ADC_RSD) <ch1) && (ch1<(ADC_STAND_VOLTAGE+ADC_RSD)))
		{ 
			OSTimeDly(1); 

			ADC_Value[ValueCount++] = ch2 ; //+= ch2 ; 
		 	//	GR_DBG_PRINTF("ADC_Value[%d] is: %d \n\n ",ValueCount-1, ADC_Value[ValueCount-1]);	
			if(ValueCount >=ADC_VALUE_COUNT_MAX)
			{
				ch2 = MedianFilter(ADC_Value, ADC_VALUE_COUNT_MAX );
			 	GR_DBG_PRINTF("ADC_ch2 is: %d \n\n\n ",ch2);	
				//ch2 =	ADC_Value /6  ;  GR_DBG_PRINTF("\nCH2 average Is %X(%d)\n\n",ch2,ch2);
				
				if(((CHANNEL_VOLT - ERR_RANGE) < ch2) && (ch2 < (CHANNEL_VOLT + ERR_RANGE)))
				{
			//		GR_DBG_PRINTF("\n LED Is OK!!!\n\n");
					return TRUE ;  
				}
				else						   // ¶ÁÈ¡ÊýÖµ²»Æ¥Åä
				{
					System.Error = LED_HRD_ERR; 
			//		GR_DBG_PRINTF("\n LED have some error!!!\n\n\n");
					return FALSE ;	
				}
			}
			else
			{
				continue ; 
			}
		}
		else
		{
			System.Error = SYS_HRD_ERR; 
		//	GR_DBG_PRINTF("\n stdand voltage is Err,Discard the Value!!!\n\n\n");
		}
		if(count++ >= 100) 						// ÒòÎªµçÑ¹²»ÎÈ¶ÁÈ¡´íÎóÊý´óÓÚ30´Î
		{
			System.Error = ADC_COUNT_OUT; 
		//	GR_DBG_PRINTF("\nADC Perform  Failed!!\n\n");
			return FALSE ;
		}  
	}
#endif
//	return TRUE ;
}


 void SYS_Error()
 {
 	if(System.Error != NON)
 	{
		switch(System.Error)
		{
			case W_T_LED_ERR : 	SHOW_SCREEN(0xE8, "ERR H131051"); break ; 
		 	case IR_T_LED_ERR : SHOW_SCREEN(0xE8, "ERR H131052"); break ;  
			case UV_LED_ERR :	SHOW_SCREEN(0xE8,"ERR H131053"); break ;  
			case IR_B_LED_ERR:	SHOW_SCREEN(0xE8,"ERR H131054"); break ; 

			case LED_HRD_ERR : SHOW_SCREEN(0xE8, "ERR H13105"); break ; 
		 	case SYS_HRD_ERR : SHOW_SCREEN(0xE8, "ERR H13106"); break ;  
			case ADC_COUNT_OUT :SHOW_SCREEN(0xE8,"ERR H13107"); break ;  
//	 		case SYS_CON_TIME_OUT :SHOW_SCREEN(0xE8,"ERR H13108"); break ; 
			default	:break ; 
		}
		
		System.Error  = NON ; 
	 // 	Light_Init();
	//	while(1);
	}	
 }

void DspRst()
{
//	OSTimeDly(10);
//	DSP_INIT_PIN = 0 ; 
//	OSTimeDly(10);
//	DSP_INIT_PIN = 1 ; 
//	OSTimeDly(10);

//	DSP_INIT_PIN = 0 ; 
//	OSTimeDly(10);
//	DSP_INIT_PIN = 1 ; 
//	OSTimeDly(10);

	DSP_INIT_PIN = 0 ; 
	OSTimeDly(50);
	DSP_INIT_PIN = 1 ; 
 	OSTimeDly(200);
}
/////////////////////////////////////////////

//void ApCombine(const uint8_t* DataA,const uint8_t* DataB, uint8_t* DataC)
//{
//	uint8_t  i=0, j=0; 
//	for(i=0;(*(DataA + i)!= NULL)&&(i<255) ;i++)
//	{
//	   *(DataC+i) = DataA[i]; 
//	}
//	for(j=0;(*(DataA + j)!= NULL)&&(i<255) ;i++,j++)
//	{
//	   *(DataC+i) = DataB[j];
//	}	
//}



