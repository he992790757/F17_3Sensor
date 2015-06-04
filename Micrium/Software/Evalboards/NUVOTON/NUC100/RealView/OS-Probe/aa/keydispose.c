
/***************************************************************************************
****************************************************************************************
* FILE		: keydispose.c
* Description	:  	A 老化程序
 						1,正常老化
 						2,拍照老化				
					B 正常程序
					C 校正程序 
*			  
* Copyright (c) 2013 by XXX. All Rights Reserved.
* History:
* Version		Name       		Date			Description
   0.1		XXX	2013/08/20	Initial Version
****************************************************************************************
****************************************************************************************/
#define __KEYDISPOSE

#include "Keydispose.h"
#include "ucos_ii.h"
#include "stdint.h"
#include "global.h"
#include "KeyScan.h"
#include "performance.h"
#include "Led.h"
#include "communication.h" 
#include "V6MDebug.h"
#include "stdlib.h"
//#inlcude <date.h>

//#include"DS1307.h"
//#include "time.h"
#include "config.h"
volatile uint8_t KS=0 ,KS_button = 0 ; 

uint32_t SysVersion[3];
//={0x56312E31,0x362E3030,0x33000000};
//uint32_t SysVersion[3]={0x56312E31,0x352E3030,0x35000000};

#ifdef AD_16_C608
const uint8_t  SysVersion1[12] ="V1.16.013TS"; 
const uint8_t  HrdVersion1[12] ="V1.16.001";
const uint8_t  MachineType1[12]="AD-16";
const uint8_t  CdKey1[12]	   ="FFFFFFFF" ;
const uint8_t  MachineNum1[12] ="FFFFFFFF" ;
const uint8_t  ProductDate1[12]=__DATE__  ;



#elif defined  AD_16_STD
const uint8_t  SysVersion1[12] 	="V1.15.010"; 	//System.Sys.Data.info.SoftwareVer[0]		此1处+说明+程序文件名称和宏定义需要修改
const uint8_t  HrdVersion1[12]	="V1.15.001";
const uint8_t  MachineType1[12]	="AD-16";
const uint8_t  CdKey1[12]		="FFFFFFFF" ;
const uint8_t  MachineNum1[12]  ="FFFFFFFF" ;
const uint8_t  ProductDate1[12] =__DATE__;

#elif defined AD_16_C608_1000PICS

const uint8_t  SysVersion1[12] ="V1.17.005"; 
const uint8_t  HrdVersion1[12] ="V1.17.001";
const uint8_t  MachineType1[12]="AD-16";
const uint8_t  CdKey1[12]	   ="FFFFFFFF" ;
const uint8_t  MachineNum1[12] ="FFFFFFFF" ;
const uint8_t  ProductDate1[12]=__DATE__  ;

#endif


ENUM_LED_STATU LedTemp ; 

void boardtest(void);

void  SysVersionChange()
{
	SysVersion[0] = ((SysVersion1[0]<<24)|(SysVersion1[1]<<16)|(SysVersion1[2]<<8)|(SysVersion1[3])); 
	SysVersion[1] = ((SysVersion1[4]<<24)|(SysVersion1[5]<<16)|(SysVersion1[6]<<8)|(SysVersion1[7])); 
	SysVersion[2] = (SysVersion1[8]<<24); 

 	System.Sys.Data.info.HardwareVer[0]	 =((HrdVersion1[0]<<24)|(HrdVersion1[1]<<16)|(HrdVersion1[2]<<8)|(HrdVersion1[3])); 
 	System.Sys.Data.info.HardwareVer[1]	 =((HrdVersion1[4]<<24)|(HrdVersion1[5]<<16)|(HrdVersion1[6]<<8)|(HrdVersion1[7])); 
	System.Sys.Data.info.HardwareVer[2]	 =(HrdVersion1[8]<<24); 

 	System.Sys.Data.info.MachineType[0]	 =((MachineType1[0]<<24)|(MachineType1[1]<<16)|(MachineType1[2]<<8)|(MachineType1[3])); 
 	System.Sys.Data.info.MachineType[1]	 =((MachineType1[4]<<24)|(MachineType1[5]<<16)|(MachineType1[6]<<8)|(MachineType1[7])); 
	System.Sys.Data.info.MachineType[2]	 =((MachineType1[8]<<24)|(MachineType1[9]<<16)|(MachineType1[10]<<8)|(MachineType1[11])); 


 	System.Sys.Data.info.CdKey[0]	 =((CdKey1[0]<<24)|(CdKey1[1]<<16)|(CdKey1[2]<<8)|(CdKey1[3])); 
 	System.Sys.Data.info.CdKey[1]	 =((CdKey1[4]<<24)|(CdKey1[5]<<16)|(CdKey1[6]<<8)|(CdKey1[7])); 
	System.Sys.Data.info.CdKey[2]	 =((CdKey1[8]<<24)|(CdKey1[9]<<16)|(CdKey1[10]<<8)|(CdKey1[11])); 

  	System.Sys.Data.info.MachineNum[0]	 =((MachineNum1[0]<<24)|(MachineNum1[1]<<16)|(MachineNum1[2]<<8)|(MachineNum1[3])); 
 	System.Sys.Data.info.MachineNum[1]	 =((MachineNum1[4]<<24)|(MachineNum1[5]<<16)|(MachineNum1[6]<<8)|(MachineNum1[7])); 
	System.Sys.Data.info.MachineNum[2]	 =((MachineNum1[8]<<24)|(MachineNum1[9]<<16)|(MachineNum1[10]<<8)|(MachineNum1[11])); 

 	System.Sys.Data.info.ProductDate[0]	 =((ProductDate1[0]<<24)|(ProductDate1[1]<<16)|(ProductDate1[2]<<8)|(ProductDate1[3])); 
 	System.Sys.Data.info.ProductDate[1]	 =((ProductDate1[4]<<24)|(ProductDate1[5]<<16)|(ProductDate1[6]<<8)|(ProductDate1[7])); 
	System.Sys.Data.info.ProductDate[2]	 =((ProductDate1[8]<<24)|(ProductDate1[9]<<16)|(ProductDate1[10]<<8)|(ProductDate1[11]));
	//生产日期

//	printf("%d",__DATE__) ;

}
/*=================================================================================
* Function	: UsbInfoDispose
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
=================================================================================*/
void UsbInfoDispose()
{
	if(ptr != NULL)
	{	
		System.Key.NoKeyTime = 0 ;

		if(System.Dsp.Mode == SLEEP_MODE)		// 在USB通信过程中不休眠
		{	
			CheckMode(); 
		}
		ptr(); 
	 	MCU_Status.Struct_Status=0x01;	
		ptr = NULL ;
	}	
	return ; 
}

void KeyInfoDispose()
{
	
	
		//按键检测处理
	System.Key.Value = KeyScan() ;
	System.Key.Keylong = &Keylong ; 
	if(!System.Key.Value)
	{
		// 处理休眠操作 
		if(System.Key.NoKeyTime == 180)
		{
			if(System.Dsp.Mode == CHECK_MODE||VIEW_MODE)
			{
				System.Dsp.Mode = SLEEP_MODE ; 
				Light_Init() ; 
			//	SHOW_SCREEN(0xE8,  " "); 
			}
		}
		else if ((System.Key.NoKeyTime == 300)&&(System.Dsp.Mode == SLEEP_MODE))
		{
		 	System.Dsp.Mode = SLEEP_MODE ;
		  //	SHOW_SCREEN(0xE8,  "Power Saving Mode"); 
			SHOW_SCREENW(0xE8, WcharToChar(L"节电模式") );
			OSTimeDly(200);			   //必须有
		}
	}
	else
	{
	//	GR_DBG_PRINTF("keylong is  %d OK it is  %d\n\n",*System.Key.Keylong,Keylong);
		// 处理唤醒操作
		System.Key.NoKeyTime = 0 ;

		if(System.Dsp.Mode == SLEEP_MODE)
		{	
			CheckMode(); 
			OSTimeDly(200) ; 
		}
		//处理按键操作
		switch(System.Key.Value)
		{
			case 1 :// 顶白光 
				{
					if(System.Led.Statu == C608_PWR_ON)
					{
						CheckMode();
						OSTimeDly(100) ;
					}
					else
					{		
						switch(System.Dsp.Mode)
						{
							case VIEW_MODE:  CheckMode(); break ; 
							default :break ; 
						}
						Photo_SignAndCount();
					}

				}break ; 
			case 2 :// check: 850 940 770 闪烁   长按:进入PCCAM
				{
				}break ; 

			case 3 ://check: 紫外-激光 长按:进入校正
				{					
					if(*System.Key.Keylong)// 进入校正功能
					{
					    	if(System.Dsp.Mode == CHECK_MODE)
							{
								PriorExposure();
							}
					}
					else
					{
						if(System.Led.Statu == C608_PWR_ON)
						{
							CheckMode();
							OSTimeDly(100) ;
						}
						else
						{	
							switch(System.Dsp.Mode)
							{
								case VIEW_MODE:  CheckMode(); break ; 
								default :break ;
							}
						
							if((System.Dsp.Mode ==PCCAM_MODE)||(System.Dsp.Mode ==CHECK_MODE))
							{
							   Photo_SignAndChk();
							}	
						} 
					//	PhotoMvRight() ; 
					}
				}break ; 

			case 4 ://check : sensor1 sensor2 sensor3 ,长按:608    
				{  

				}break ; 
			case 5 ://check: 左白光 右白光 左红外， 右红外 view:翻页 放大
				{

					
					//	PhotoDelAll();
					if(System.Led.Statu == C608_PWR_ON)
					{
						CheckMode();
						OSTimeDly(100) ;
					}
					else
					{						
						switch(System.Dsp.Mode)
						{
							
							case PCCAM_MODE :
							case CHECK_MODE :
							{
							   	ViewMode() ;
	
							}break; 
							case VIEW_MODE :
							{
								if(*System.Key.Keylong) 
								{
									CheckMode();
								}
								else
								{
									ViewMode_F1() ;	
								}
							}break; 
							default :break ;
						}
					}					
				}break ; 
			case 6 ://check: 底白光，底红外  view :右边翻页
				{
					if(System.Led.Statu == C608_PWR_ON)
					{
						CheckMode();
						OSTimeDly(100) ;
					}
					else
					{	
						switch(System.Dsp.Mode)
						{
							case PCCAM_MODE :
							case CHECK_MODE :
							{
							}break; 
							case VIEW_MODE :
							{						
								ViewMode_F2() ;
	
							}break; 
							default :break ;
						}
					}										
				}break ; 
			case 7 ://view--check ; 
				{
					if(System.Led.Statu == C608_PWR_ON)
					{
						CheckMode();
						OSTimeDly(100) ;
					}
					else
					{	
						switch(System.Dsp.Mode)
						{
							case PCCAM_MODE :
							case CHECK_MODE :
							{
							  	 C608_On()	;	
							}break; 
							case VIEW_MODE :
							{
									ViewMode_F3() ;	
							}break; 
							default :break ;
						}
					}														
				}break ; 
			case 8 ://check:短按单拍，长按8连拍 ，view 长按删除，短按确认
				{
					if(System.Led.Statu == C608_PWR_ON)
					{
						CheckMode();
						OSTimeDly(100) ;
					}
					else
					{	
						if(*System.Key.Keylong)// 进入校正功能
						{

						}
						else
						{
							switch(System.Dsp.Mode)
							{
								case PCCAM_MODE :
								case CHECK_MODE :
								{
								  // CheckMode();
								   if( System.Local_SignOutCount_Flag  == 0 )
								   {
								   	   System.Local_SignOutCount_Flag = 1 ; 	   
								   }
								   
								   Local_SignOutCount = 0 ;  	
								   ShowLeftBtmNum(); 
		
								}break; 
								case VIEW_MODE :
								{
									ViewMode_F4() ;	
								}break; 
								default :break ;
							} 	
						}
					}


				}break ; 
			case 9 ://check: 短按连拍，长按修改密码  // view:自动回放
				{
					if(System.Led.Statu == C608_PWR_ON)
					{
						CheckMode();
						OSTimeDly(100) ;
					}
					else
					{						

				 	    ViewMode() ;
						PhotoDelAll();
					 	CheckMode();   
					}				
				}break ; 
			default : break ; 
		}
	}
}
uint8_t BoxOpenCheck()
{
	KS = (uint8_t) DrvGPIO_GetBit(E_GPE, 5); 
	if(KS != KS_button)
	{
		KS_button = KS ; 
	    if( KS_button == 0 ) //闭合
		   	{ 
				 switch(LedTemp)
				 {
					case 	TOP_WHITE_ON  : Top_W_On();    		break ;  
					case 	TOP_IR850_ON  : Top_IR850_On( );	break ; 
					case 	TOP_IR940_ON  : Top_IR940_On( );	break ; 

					case 	LEFT_W_ON     : Left_W_On( );   	break ; 
					case 	RIGHT_W_ON 	  : Right_W_On( );	break ; 
					case 	LEFT_IR850_ON : Left_IR850_On();	break ; 
					case 	RIGHT_IR850_ON:	Right_IR850_On();	break ; 
                                                                      
					case 	BOT_W_ON   	  : Bot_W_On();			break ; 
					case 	BOT_IR_ON  	  : Bot_IR_On(); 		break ; 
					case 	RIGHT_UV_ON   : Right_UV_On(); 		break ; 
					case 	DB_UV_ON      : Double_UV_On(); 	break ; 
					case 	RIGHT_IR770_ON: Right_IR770_On();	break ;  
					case 	RIGHT_LASER_ON:	Right_Laser_On(); 	break ; 
					case 	C608_PWR_ON   :	C608_On(); 			break ;
					case 	DB_WT_UV_ON	  :	Double_WT_UV_On(); 	break ; 
					case    DB_UV_EXPOSURE1_ON : Double_UV_Exposure1_On();break ;
					case 	DB_UV_EXPOSURE2_ON : Double_UV_Exposure2_On();break ;
					
				 	default :	break ; 
				 }
		   	}
		   else
		   	{
				 LedTemp = System.Led.Statu ; 
			 	Light_Init() ; 
		    }				
	}
	if( KS ) return 0x01 ;
	else	return 0x00 ; 
}
void USbInCheck()
{
	System.Usb.NewUsbStatu = USB_STATUS ; 
	if(System.Usb.OldUsbStatu != System.Usb.NewUsbStatu)
	{
		System.Usb.UsbStatuLabel = 1 ; 
		if(System.Usb.NewUsbStatu == USB_IN)
		{
			//插入USB操作
			// SHOW_SCREEN(0xE3,"USB READY\n");
		}
		else if(System.Usb.NewUsbStatu == USB_OUT)
		{
			//拔出USB操作
			// SHOW_SCREEN(0xE3,"USB NOT READY\n");
			if((System.Dsp.Mode == PCCAM_MODE)||(System.Dsp.Mode == TF_MODE))
			{
				CheckMode(); 
			}
		}
		System.Usb.OldUsbStatu = System.Usb.NewUsbStatu ; 
		OSTimeDly(10); 
	}	
}
void KeyDispose()
{
	//翻盖处理跟检测
	if(BoxOpenCheck()) return ; 

	//USB状态检测
	//USbInCheck() ; 
	// USB信息处理
	UsbInfoDispose();
	// 按键信息处理
    KeyInfoDispose();
	//定时器锁定信息
#ifdef DS1307_ON
	if(System.Sys.PassWrd.InputErrCount >= INPUT_ERR_TIME_MAX)
	{
		
		uint32_t m ;  

		GR_DBG_PRINTF("System.Sys.PassWrd.InputErrCount: %d \n\n ",System.Sys.PassWrd.InputErrCount);
 		GR_DBG_PRINTF("System.Sys.PassWrd.LockTime: %d \n\n ",System.Sys.PassWrd.LockTime); 
		DS1307_RD(&date[0]); 
		m = sTime(NowTime);
	    GR_DBG_PRINTF("sTime(NowTime): %d \n\n",m);

		m = m -  System.Sys.PassWrd.LockTime; 
 
		GR_DBG_PRINTF("locked time is gone: %d \n\n",m);
		if ( m >= SYS_LOCK_TIME_SETTING )	   //锁定时间2分钟
		{
			System.Sys.PassWrd.InputErrCount = 0 ; 
			System.Sys.SaveInfoFlag = 0x01 ; 
		}
	}
#else
	if(System.Sys.PassWrd.InputErrCount >= INPUT_ERR_TIME_MAX)
	{
			System.Sys.PassWrd.InputErrCount = 0 ; 
			System.Sys.SaveInfoFlag = 0x01 ;		
	}
#endif 		
	// 系统保存信息
	if(System.Sys.SaveInfoFlag  == 0x01)
	{
		SystemWriteBCKData();
	}
	// 系统软硬件错误
	SYS_Error();
}

void TESTA()	//正常老化
{
	uint32_t i = 120 ; 
	uint8_t  m = 0 ; 
	OSTimeDly(500) ; 
TESTAG:
	i = 120 ; 
	while(i--)
	{
		Top_W_On();
		OSTimeDly(200);     	
		Select_Send(0x21);  
		OSTimeDly(400); 
//		Top_IR850_On( ); 
//		OSTimeDly(400); 
		Top_IR940_On( ); 
		OSTimeDly(200);     	
		Select_Send(0x21); 
		OSTimeDly(400); 

		Left_W_On( );  
		OSTimeDly(200);     	
		Select_Send(0x21); 
		OSTimeDly(400);   

		Right_IR850_On( ); 
		OSTimeDly(200);     	
		Select_Send(0x21); 
		OSTimeDly(400); 

		Left_IR850_On(); 
		OSTimeDly(200);     	
		Select_Send(0x21); 
		OSTimeDly(400); 

		Right_IR850_On(); 
		OSTimeDly(200);     	
		Select_Send(0x21); 
		OSTimeDly(400);   
		                                            
		Bot_W_On();	
		OSTimeDly(200);     	
		Select_Send(0x21); 
		OSTimeDly(400); 
			 
		Bot_IR_On(); 
		OSTimeDly(200);     	
		Select_Send(0x21); 
		OSTimeDly(400); 	 

//		Right_UV_On(); 
//		OSTimeDly(400); 	 
		Double_UV_On();  
		OSTimeDly(200);     	
		Select_Send(0x21); 
		OSTimeDly(400); 
//		Right_IR770_On();
//		OSTimeDly(400); 	 
//		Right_Laser_On();  
//		OSTimeDly(400); 
	} 
   	 SHOW_SCREEN(0xE8, "Press K1 To Run Again\n");       

	 Light_Init();
	 while(1)
	 {
	  	 m = 0 ; 
	 	 m = KeyScan() ; 	 
		 if(m) 
		 {	
		 	GR_DBG_PRINTF("\nm  Value is %d\n",m);
		 	Select_Send(0xE9);  
		 	 if(m == 1)
			 {
			 	 goto  TESTAG ;
			 }
			 else
			 {
			 	 break ; 
			 }
		 }	
		 OSTimeDly(10); 
	 }
}

void TestHardWareInit()
{
	/***** 系统信息  ******/
//	uint32_t m ; 	 

	OSTimeDly(500) ;
	// 主板软件版本
	SHOW_SCREEN_LONG(0xE8,"1-MthrBrd Sft Ver Is:",&SysVersion1[0]);
	OSTimeDly(300) ;
	// DSP软件版本
	SHOW_SCREEN_LONG(0xE8,"2-DSP Sft Ver Is:","NON");
	OSTimeDly(300) ;	

	//按键好坏测试
//	   SHOW_SCREEN_LONG(0xE8,"Please enter ","K1" ); while(K1 != 0 ); 
//	   SHOW_SCREEN_LONG(0xE8,"Please enter ","K2" ); while(K2 != 0 ); 
//	   SHOW_SCREEN_LONG(0xE8,"Please enter ","K3" ); while(K3 != 0 ); 
//	   SHOW_SCREEN_LONG(0xE8,"Please enter ","K4" ); while(K4 != 0 ); 
//	   SHOW_SCREEN_LONG(0xE8,"Please enter ","K5" ); while(K5 != 0 ); 
//	   SHOW_SCREEN_LONG(0xE8,"Please enter ","K6" ); while(K6 != 0 ); 
//	   SHOW_SCREEN_LONG(0xE8,"Please enter ","K7" ); while(K7 != 0 ); 
//	   SHOW_SCREEN_LONG(0xE8,"Please enter ","K8" ); while(K8 != 0 ); 
//	   SHOW_SCREEN_LONG(0xE8,"Please enter ","K9" ); while(K9 != 0 ); 

	// 灯源好坏
	System.Error = NON  ; 
	System.Dsp.Mode = CHECK_MODE;
		Top_W_On();			ADC_Checking(ADC_CK_VLT_T_W,ADC_RSD_T_W-100 );		
								if(System.Error != NON){System.Error = NON ; SHOW_SCREEN(0xE8,"3-T-W is Err\nPress K9 to next" );      }
								else { SHOW_SCREEN_LONG(0xE8,"3-T-W","  is OK\nPress K9 to next" ); }		while(K9 != 0 ); 	 
		Top_IR940_On( ); 	ADC_Checking(ADC_CK_VLT_T_IR940,ADC_RSD_T_IR940-200);	
								if(System.Error != NON){System.Error = NON ; SHOW_SCREEN(0xE8,"4-T-IR940 is Err\nPress K9 to next" );   }
								else { SHOW_SCREEN_LONG(0xE8,"4-T-IR940"," is OK\nPress K9 to next" ); }	while(K9 != 0 ); 
//		Left_W_On( );  		ADC_Checking(ADC_CK_VLT_L_W,ADC_RSD_L_W-100);
//							if(System.Error != NON){System.Error = NON ; SHOW_SCREEN(0xE8,"5-L-W  is Err\nPress K9 to next" );   }  
//								else { SHOW_SCREEN_LONG(0xE8,"5-L-W"," is OK\nPress K9 to next" ); }	while(K9 != 0 ); 
//		Right_W_On( );  	ADC_Checking(ADC_CK_VLT_R_W,ADC_RSD_R_W-50);
//							if(System.Error != NON){System.Error = NON ; SHOW_SCREEN(0xE8,"6-R-W  is Err\nPress K9 to next" );   }  
//								else { SHOW_SCREEN_LONG(0xE8,"6-R-W "," is OK\nPress K9 to next" ); }	while(K9 != 0 ); 
//		Left_IR850_On();    ADC_Checking(ADC_CK_VLT_L_IR,ADC_RSD_L_IR-100);
//							if(System.Error != NON){System.Error = NON ; SHOW_SCREEN(0xE8,"7-L-IR is Err\nPress K9 to next" );  } 
//								else { SHOW_SCREEN_LONG(0xE8,"7-L-IR"," is OK\nPress K9 to next" ); }	while(K9 != 0 ); 
//		Right_IR850_On(); 	ADC_Checking(ADC_CK_VLT_R_IR,ADC_RSD_R_IR-100);
//							if(System.Error != NON){System.Error = NON ; SHOW_SCREEN(0xE8,"8-R-IR is Err\nPress K9 to next" );  }                                               
//								else { SHOW_SCREEN_LONG(0xE8,"8-R-IR"," is OK\nPress K9 to next" ); }	while(K9 != 0 ); 
//		Bot_W_On();		 	ADC_Checking(ADC_CK_VLT_B_W,ADC_RSD_B_W-150);
//							if(System.Error != NON){System.Error = NON ; SHOW_SCREEN(0xE8,"9-B-W is Err\nPress K9 to next" );  }  
//								else { SHOW_SCREEN_LONG(0xE8,"9-B-W"," is OK\nPress K9 to next" ); }	while(K9 != 0 ); 
		Bot_IR_On(); 		ADC_Checking(ADC_CK_VLT_B_IR,ADC_RSD_B_IR-200);
							if(System.Error != NON){System.Error = NON ; SHOW_SCREEN(0xE8,"10-B-IR is Err\nPress K9 to next" ); } 	 	 
								 else { SHOW_SCREEN_LONG(0xE8,"10-B-IR"," is OK\nPress K9 to next" ); }	while(K9 != 0 ); 
		Double_UV_On();  	ADC_Checking(ADC_CK_VLT_B_IR,ADC_RSD_B_IR-150);
							if(System.Error != NON){System.Error = NON ; SHOW_SCREEN(0xE8,"11-D-UV is Err\nPress K9 to next" ); } 		
								else { SHOW_SCREEN_LONG(0xE8,"11-D-UV ","is OK\nPress K9 to next" ); }	while(K9 != 0 ); 
	// 时钟好坏 
		SHOW_SCREEN(0xe8,"wait...");
//		DS1307_RD(&date[0]);   
//		m = sTime(NowTime) ; 
		OSTimeDly(400); 
//	    DS1307_RD(&date[0]);  
//	    if(sTime(NowTime)-m < 3) SHOW_SCREEN(0xe8,"12-Systime  is Err\nPress K9 to next");
//			else  SHOW_SCREEN(0xe8,"12-Systime is OK\nPress K9 to next");		 

		OSTimeDly(10); 

		while(K9 != 0 ); 

        SHOW_SCREEN(0xe8,"END\npress K9 to exit");	

		while(K9 != 0 ); 
	// 外接608好坏

	// SD  PCCAM  图像质量好坏。
		if((K8 == 0)&&(K7 == 0))	  //对于已经运行过第一次程序，但是时钟芯片因为电不足
		{
			SHOW_SCREEN(0xe8,"Init Environment");
	
			Vir_Init() ;
			//初始化所有变量内容
	 		System.Sys.SaveInfoFlag = 1 ; 
			OSTimeDly(300); 
		}
     	Select_Send(0xE9); 	 
}
void TESTB()
{
	// 老化测试 --各个灯条循环亮。 
	TestHardWareInit(); 
}

void TESTC()
{ 

//		 boardtest();
//for( ;;  )
//{
///*----------------------------------------------------*/			 
//	  		 
//	    Double_UV_On(); 
//		OSTimeDly(400); 
//
//		Light_Init();
// 	    OSTimeDly(400); 
//	    
///*----------------------------------------------------*/
//
//}	

	// 老化测试 --紫灯的老化测试
 	unsigned int i =0 ; 
	unsigned char m ;
	unsigned char  LightOn = 0, LightOff = 0 ; 

	uint8_t data[10]	= {0xF9,8,'O','N',0x33,0x33,'O','F', 0x33,0x33, } ;

	SHOW_SCREEN(0xE8 , "Enter the Value:");

	while(1)
	{
		m  = 0 ;
		OSTimeDly(10) ; 
		m = KeyScan(); 
		if(m == 6)	  // 亮的时间
		{
			uint8_t ss[1] ; 
			LightOn += 1 ; 
			if(LightOn ==9 ){LightOn = 0 ; }
			ss[0] = LightOn+0x30;
			SHOW_SCREEN_LONG(0xE8,"Light On S:",ss);   data[4]=0x30+LightOn/10; data[5]=0x30+LightOn%10;
		//	while(K6 == 0); OSTimeDly(30);break ; 
		}
		if(m == 7)	  // 亮的时间
		{
			uint8_t ss[1] ;
			LightOff += 1 ; 
			if(LightOff ==9 ){LightOff = 0 ; }
			ss[0] = LightOff+0x30;
			SHOW_SCREEN_LONG(0xE8,"Light Off S:",ss);   data[8]=0x30+LightOff/10; data[9]=0x30+LightOff%10;
		//	while(K7 == 0); OSTimeDly(30);break ; 
		}
		if(m == 8)
		{
			Select_Send(0xE9);
			OSTimeDly(100); 
			Scen_Send(0xFA,0x01);

			//DSP_SEND(8, &TOP_W_d[0]);
			SHOW_SCREENA(0xF9, 10, &data[2]); 
			break ; 
		}
	}
	System.Key.Value = 0 ; 
	System.Led.Statu = TOP_WHITE_ON ; 	
	System.Dsp.Mode = CHECK_MODE; 

	CheckMode(); 

	for(i = 0 ;i <= 2000; i++ )
	{
/*----------------------------------------------------*/			 
		  		 
		    Double_UV_On(); 
			OSTimeDly(100); 

			if(LightOn>2) Select_Send(0x21);
			OSTimeDly(LightOn*100);

			if(LightOff == 0)Light_Init();
	 	    OSTimeDly(LightOff*100); 
		    
/*----------------------------------------------------*/

	}	
}

void TESTD()	   //连拍老化测试
{
	uint16_t i =0 ;
	uint8_t	 m = 0 ;
AA:	for(i = 0 ; i <2000; i++)
	{	
		PhotographFour();
		OSTimeDly(200); 
	} 
	Light_Init(); 	

   	SHOW_SCREEN(0xE8, "Press K4 To Run Again\n");
	while(1)
	{	
		 m = KeyScan() ; 
		 if(m) 
		 {
		 	 Select_Send(0xE9);  
		 	 if(m == 4)
			 {
			 	 goto  AA ;
			 }
			 else
			 {
			 	 break ; 
			 }
		 }	
	}
////////////////////////////////////////////////////////




///////////////////////////////////////////////////////

}

void KeyInfoDispose_Debug()
{
	
	
		//按键检测处理
	System.Key.Value = KeyScan() ;
	System.Key.Keylong = &Keylong ; 
	if(!System.Key.Value)
	{
		// 处理休眠操作
	}
	else
	{
	//	GR_DBG_PRINTF("keylong is  %d OK it is  %d\n\n",*System.Key.Keylong,Keylong);
		// 处理唤醒操作
		System.Key.NoKeyTime = 0 ;

		if(System.Dsp.Mode == SLEEP_MODE)
		{	
			CheckMode(); 
		}
		//处理按键操作
		switch(System.Key.Value)
		{
			case 1 :// 顶白光 
				{		
					Top_W_On();	
					PhotoMvLeft() ;
				}break ; 
			case 2 :// check: 850 940 770 闪烁   长按:进入PCCAM
				{
				#ifdef ONE_SENSOR
					Top_IR940_On_test();
				    PhotoMvUp() ; 
				#else
					if(*System.Key.Keylong)
					{
						switch(System.Dsp.Mode )
						{
							case PCCAM_MODE : CheckMode();	break;
							default:		  PccamMode();	break; 
						}
					}
					else
					{
						if(System.Dsp.Mode == CHECK_MODE||PCCAM_MODE)
						{
							switch(System.Led.Statu)
							{
								case TOP_IR850_ON : Top_IR940_On();break ; 
								case TOP_IR940_ON : Right_IR770_On();break ; 
								default :Top_IR850_On(); break ; 
							}
						}
						 
					}
				#endif 
				}break ; 

			case 3 ://check: 紫外-激光 长按:进入校正
				{					
					if(*System.Key.Keylong)// 进入校正功能
					{
						if(System.Dsp.Mode == CHECK_MODE)
						{
							PriorExposure();
						}
					}
					else
					{
						if((System.Dsp.Mode ==PCCAM_MODE)||(System.Dsp.Mode ==CHECK_MODE))
						{
							 Double_UV_On(); 				
						}
						PhotoMvRight() ;
					}
				}break ; 

			case 4 ://check : sensor1 sensor2 sensor3 ,长按:608    
				{
					switch(System.Dsp.Mode)
					{ 
						#ifdef ONE_SENSOR
						case PCCAM_MODE :
						{
							if(*System.Key.Keylong) 
							{
								CheckMode();
							}		
						}  break ;
						#endif 

						case VIEW_MODE :
						case CHECK_MODE :
						{
							if(*System.Key.Keylong) 
							{
								PccamMode();
							}
							else
							{
//								switch(System.Led.Statu)
//								{
//									case C608_PWR_ON: CheckMode();break; 
//									default:C608_On(); break; 	
//								}
								PhotoZoomUp();	
							}

	
						} break ; 
						default :break ; 
					}
					
				}break ; 
			case 5 ://check: 左白光 右白光 左红外， 右红外 view:翻页 放大
				{
					switch(System.Dsp.Mode)
					{
						case PCCAM_MODE :
						case CHECK_MODE :
						{
							switch(System.Led.Statu)
							{
								case LEFT_W_ON 	:	Right_W_On();		break ; 
								case RIGHT_W_ON	:	Left_IR850_On();	break ;
								case LEFT_IR850_ON:	Right_IR850_On();	break ;
								default :Left_W_On();
							}
						}break; 
						case VIEW_MODE :
						{	
							switch(System.Dsp.ViewMode.Zoom)
							{
								case X0 : 	PhotoPrevious(); break; 
								default :	PhotoMvLeft() ; 
							}
						}break; 
						default :break ;
					}					
				}break ; 
			case 6 ://check: 底白光，底红外  view :右边翻页
				{
					switch(System.Dsp.Mode)
					{
						case PCCAM_MODE :
						case CHECK_MODE :
						{
							switch(System.Led.Statu)
							{
								case BOT_W_ON :	Bot_IR_On(); break ; 
								default :Bot_W_On();
							}
						}break; 
						case VIEW_MODE :
						{
							switch(System.Dsp.ViewMode.Zoom)
							{
								//case X0 :	PhotoNext(); break ; 
								default :	PhotoMvDown() ; break ; 
							}
						}break; 
						default :break ;
					}										
				}break ; 
			case 7 ://view--check ; 
				{
					switch(System.Dsp.Mode)
					{
						case CHECK_MODE :
						{
						  VerifyPassword(0x07,&CheckMode,&ViewMode); 						
						} break; 
						case VIEW_MODE :
						{
							CheckMode();
						} break; 			
						default :break ;
					}							
										
				}break ; 
			case 8 ://check:短按单拍，长按8连拍 ，view 长按删除，短按确认
				{
					switch(System.Dsp.Mode)
					{
						case CHECK_MODE :
						{
						#ifdef ONE_SENSOR
							PhotographOne(); 
						#else
						
							if(*System.Key.Keylong) 
							{
								//PhotographOne(); 
							}
							else
							{	
								PhotographEight(); 
							}
						#endif
						}break; 
						case VIEW_MODE :
						{
							if(*System.Key.Keylong) 
							{
								PhotoDelAll(); 
							}
							else
							{
								
							}							
						}break; 
						default :break ;
					}  	
				}break ; 
			case 9 ://check: 短按连拍，长按修改密码  // view:自动回放
				{
					switch(System.Dsp.Mode)
					{
						case CHECK_MODE :
						{
							if(*System.Key.Keylong) 
							{
							 	VerifyPassword(0x09,&CheckMode,&ChangePassWord); 	
								CheckMode(); 
							}
							else
							{	
								PhotographFour(); 
							}
						}break; 
						case VIEW_MODE :
						{	
							PhotoAutoView(); // 自动回放
						}break;
						default :break ;
					}				
				}break ; 
			default : break ; 
		}
	}
}
void KeyDispose_debug()
{

	UsbInfoDispose();
	// 按键信息处理

    KeyInfoDispose_Debug() ;
	//定时器锁定信息


	if(System.Sys.PassWrd.InputErrCount >= INPUT_ERR_TIME_MAX)
	{
			System.Sys.PassWrd.InputErrCount = 0 ; 
			System.Sys.SaveInfoFlag = 0x01 ;		
	} 
		
}
void TESTE()
{
	for(;;)
	{
		KeyDispose_debug() ; 
		OSTimeDly(5); 	
	}
}

void boardtest()
{
//	while(K1 == 0)OSTimeDly(10) ; while(K1 == 1)OSTimeDly(10) ; 	//TF
    CheckMode() ;
	while(K1 == 0)OSTimeDly(10) ; while(K1 == 1)OSTimeDly(10) ; 	//rst 	
	OSTimeDly(100) ; 

	TfMode() ; 
	
	OSTimeDly(100) ;															 
	while(K1 == 0){OSTimeDly(100); } while(K1 == 1){UsbInfoDispose();OSTimeDly(10) ; }	//rst

	CheckMode() ; 
	OSTimeDly(200) ;
    DspRst() ; 

    while(1){ 
                if(K9 == 0 ){Light_Init(); TOP_W = 0 ; 
                            TOP_IR850= 0 ;
							TOP_IR940 = 0 ;
                            LEFT_W = 0 ; 
							RIGHT_W = 0 ; 
							LEFT_IR850 = 0 ;
							RIGHT_IR850 = 0 ;
							BOT_W = 0 ;
							BOT_IR = 0   ;
							RIGHT_UV = 0 ;
                            LEFT_UV = 0 ;
				            } 
				
                if(K2 == 0 ){Light_Init(); TOP_IR850= 0 ;} 
                if(K3 == 0 ){Light_Init(); TOP_IR940 = 0 ; }
                if(K4 == 0 ){Light_Init(); LEFT_W = 0 ; RIGHT_W = 0 ; }	  
                if(K5 == 0 ){Light_Init(); TOP_IR940 = 0 ;TOP_IR850= 0 ; ;} OSTimeDly(1); 
                if(K6 == 0 ){Light_Init(); LEFT_IR850 = 0 ; RIGHT_IR850 = 0 ; } OSTimeDly(1); 
                if(K7 == 0 ){Light_Init(); BOT_W = 0 ;BOT_IR = 0   ;} OSTimeDly(1);
                if(K8 == 0 ){Light_Init(); RIGHT_UV = 0 ;LEFT_UV = 0 ; } OSTimeDly(1);
                if(K1 == 0 ){Light_Init();break ;} OSTimeDly(1); 	
				OSTimeDly(10); 
			}  	
	CheckMode() ; 
	OSTimeDly(300); 
    while(K1 == 0)OSTimeDly(10) ; while(K1 == 1)OSTimeDly(10) ;
    PhotographOne() ;
	OSTimeDly(300) ;
	while(K1 == 0)OSTimeDly(10) ; while(K1 == 1)OSTimeDly(10) ;
	ViewMode(); 
	OSTimeDly(100) ;
	while(K1 == 0)OSTimeDly(10) ; while(K1 == 1)OSTimeDly(10) ;
	//PhotoDelOne() ;
	Select_Send_LONG(0x24);
	OSTimeDly(100) ;
	while(K1 == 0)OSTimeDly(10) ; while(K1 == 1)OSTimeDly(10) ;
	CheckMode() ; 
	OSTimeDly(100); 
	PccamMode() ; 
	OSTimeDly(300) ;
	while(K1 == 0)OSTimeDly(10) ; while(K1 == 1){UsbInfoDispose();OSTimeDly(10) ; }
	CheckMode() ; 
}


