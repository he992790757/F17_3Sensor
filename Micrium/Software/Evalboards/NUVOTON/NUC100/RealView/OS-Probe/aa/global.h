
/***************************************************************************************
****************************************************************************************
* FILE		: global.h
* Description	: 
*			  
* Copyright (c) 2013 by XXX. All Rights Reserved.
* 
* History:
* Version		Name       		Date			Description
   0.1		XXX	2013/08/20	Initial Version
   
****************************************************************************************
****************************************************************************************/

#ifndef _APP_H_
#define _APP_H_

#ifdef  __APP
#define APP_EXT 
#else 
#define APP_EXT extern 
#endif 

#include<stdint.h>



//#endif
///////////////////////////////////////MachineConfig/////////////////////////////////////////////


//#define AD_16 

//#define GR_DBG_PRINT


#ifdef GR_DBG_PRINT
#define	GR_DBG_PRINTF printf 
#else
#define GR_DBG_PRINTF(...)
#endif 



#ifdef AD_13
	#define ONE_SENSOR 				// THREE_SENSOR 默认3SENSOR 
	#define ADC_CHECKING		 	// 是否有电流检测
	#define DS1307_ON 				//开启时钟

	#define MACHINE_TYPE	"AD-13" 
	#define PRODUCT_DATE	_DATE_


#elif defined AD_16_STD

	#define AD_16
	#define ONE_SENSOR // THREE_SENSOR 默认3SENSOR 

	#define ADC_CHECKING		 	// 是否有电流检测

	//#define DS1307_ON 			// 不开启时钟

	#define MACHINE_TYPE	"AD-16" 
	#define PRODUCT_DATE	_DATE_
//	#define INLAND_MACHINE			// 国内的机器

#elif defined AD_16_C608

	#define AD_16
	#define ONE_SENSOR // THREE_SENSOR 默认3SENSOR 
    #define STD_C608
	#define ADC_CHECKING		 	// 是否有电流检测
	 
	//#define DS1307_ON 			// 不开启时钟
	#define MACHINE_TYPE	"AD-16" 
	#define PRODUCT_DATE	_DATE_

#elif defined AD_16_C608_1000PICS

	#define AD_16
	#define ONE_SENSOR // THREE_SENSOR 默认3SENSOR 
    #define STD_C608
	#define ADC_CHECKING		 	// 是否有电流检测
	#define AD_16_1000PICS 
	//#define DS1307_ON 			// 不开启时钟
	#define MACHINE_TYPE	"AD-16" 
	#define PRODUCT_DATE	_DATE_

#endif  











//定义场景 

#define G_SENCE_DB_UV	  	   	0x01 	 
#define G_SENCE_WT 	   			0x02	
#define G_SENCE_L_W 	       	0x03 
#define G_SENCE_R_W 	       	0x04 
#define G_SENCE_B_W 	       	0x05 
	 
#define G_SENCE_T_IR940 	   	0x06		 
#define G_SENCE_T_IR850	       	0x07		 		 
#define G_SENCE_L_IR 	  		0x08		 		 
#define G_SENCE_B_IR 	   		0x09	
#define G_SENCE_R_IR	  	   	0x10 	 	  

#define G_SENCE_DB_UV2	  	   	0x01 	 
//#define THREE_SENSOR 

//#ifdef	ADC_CHECKING				标准值

#define ADC_STAND_VOLTAGE	2048 		 //2048		   0.245
#define ADC_RSD 			500			 //100

#define ADC_CK_VLT_T_W 		1045		 //950
#define ADC_RSD_T_W 		300			 //90

#define ADC_CK_VLT_T_IR850  500	  		 //
#define ADC_RSD_T_IR850 	400	  		 //

#define ADC_CK_VLT_T_IR940 	1780		 //1750
#define ADC_RSD_T_IR940 	400			 //140

#define ADC_CK_VLT_L_W		650			 //650	   160mA
#define ADC_RSD_L_W 		600			 //140

#define ADC_CK_VLT_R_W  	410			 //430
#define ADC_RSD_R_W  		400

#define ADC_CK_VLT_L_IR 	950			 //920		 --OK
#define ADC_RSD_L_IR 		900

#define ADC_CK_VLT_R_IR 	620			 //620
#define ADC_RSD_R_IR 		600

#define ADC_CK_VLT_B_W  	785
#define ADC_RSD_B_W			700

#define ADC_CK_VLT_B_IR  	960
#define ADC_RSD_B_IR		480

#define ADC_CK_VLT_R_UV		500
#define ADC_RSD_R_UV		400

#define ADC_CK_VLT_DB_UV	820		//11.5V---	600  	  //700
									//11.6V-- 	630	
									//12.0V--	749	
									//12.3V-- 	820	 
									//12.4V--	839	 
									//12.6V-- 	900 
#define ADC_RSD_DB_UV 		300

#define ADC_CK_VLT_R_770	500
#define ADC_RSD_R_770 		400

#define ADC_CK_VLT_R_LA		500
#define ADC_RSD_R_LA 		400
//#endif

#define TOP_R_LABEL 	0x01 
#define LEFT_LABEL 		0x02 
#define RIGHT_LABEL 	0x03 
#define BTM_LABEL		0x04 
#define TOP_LABEL 		0x05



#define D_NON 0xF0 			//没有数据输入的时候

///////////////////////////////////////1 LED /////////////////////////////////////////////
typedef enum
{
	ALL_LED_OFF 	= 0, 	   // 顶白光

	TOP_WHITE_ON 	= 3  ,
	LEFT_W_ON    	= 4  , 
	TOP_IR850_ON 	= 5  ,
	TOP_IR940_ON 	= 6  ,
	DB_UV_ON     	= 7  , 
	LEFT_IR850_ON 	= 8  ,  
	BOT_W_ON       	= 9  ,
	BOT_IR_ON     	= 10 ,
		 	  
	RIGHT_W_ON 	,   
	RIGHT_IR850_ON	, 
	RIGHT_UV_ON    	, 
	DB_WT_UV_ON		,
	DB_UV_EXPOSURE1_ON ,
	DB_UV_EXPOSURE2_ON ,
	RIGHT_IR770_ON , 
	RIGHT_LASER_ON	, 
	C608_PWR_ON 	, 
} ENUM_LED_STATU;



typedef struct 
{
	ENUM_LED_STATU Statu; 
	
}LED_STATU ; 
///////////////////////////////////////2  DSP /////////////////////////////////////////////

typedef enum       // dsp的模式
{
	VIEW_MODE , 
	CHECK_MODE  ,  // 检查模式
	TF_MODE ,
	PCCAM_MODE , 
	SLEEP_MODE,
} ENUM_DSP_MODE ;


typedef enum      // 放大倍数
{
	X0,X1,X2,X3,X4 
} ENUM_DSP_ZOOM ;

typedef enum       //sensor 选择
{
	NONSENSOR,SENSOR1, SENSOR2,SENSOR3,C608 ,
} ENUM_DSP_SENSOR;

typedef enum       //sensor 选择
{
	IN,
	OUT ,
} ENUM_DSP_SD;

typedef struct 
{		
	ENUM_DSP_ZOOM   Zoom ;
	uint8_t	 CycleView ; 
	uint8_t  CycleViewPause ; 
} STRUCT_VIEW; 

typedef struct 
{		
	ENUM_DSP_ZOOM   Zoom ; 			
} STRUCT_CHECK ; 

typedef struct 
{		
	uint8_t t ; 
} STRUCT_TF ; 

typedef struct 
{		
  uint8_t ConnectIn ; 	
} STRUCT_PCCAM ;

typedef struct 
{	uint8_t     FB1 ; 		  //ISO					//2
	uint8_t     FB2 ; 		  //ISO					//2
	uint8_t     FC1 ;  		  //曝光时间			//2
	uint8_t     FC2 ;  		  //曝光时间			//2
	uint8_t	    WB1 ; 		  //白平衡				//2
	uint8_t	    WB2 ; 		  //白平衡				//2
	uint8_t 	 Sharpness  ; //锐度				//1
	uint8_t 	 Contrast	; //对比度				//1
	uint8_t		 Brightness ; //亮度				//1
	uint8_t		 Saturation ; //饱和度				//1
	uint8_t 	 Num	;     //对应场景			//1	
	uint8_t 	 Mode	;     //色彩模式 			//1		色彩模式 01 彩色手动 03黑白手动
} STRUCT_PHOTO ; 

typedef struct 
{
	ENUM_DSP_MODE 		Mode ; 
	STRUCT_VIEW  		ViewMode; 
	STRUCT_CHECK 		CheckMode ;  
	STRUCT_TF			TF_Mode; 
	STRUCT_PCCAM   		PccamMode; 
	ENUM_DSP_SENSOR     Sensor; 
	ENUM_DSP_SD			SD ; 
	union  photo
	{
		STRUCT_PHOTO   Scene[10]; 
        uint8_t Flag ;   // 记录当前是哪个场景
		uint32_t photo[30];
	} photo	 ; 

}DSP_STATU ; 		 



///////////////////////////////////////key /////////////////////////////////////////////
typedef struct 
{		
  uint8_t* Keylong ;
  uint8_t 	Value ;
  uint16_t NoKeyTime; 
} KEY_STATU ;

///////////////////////////////////////SYS /////////////////////////////////////////////
#define PASSWORD_LENGTH 4
#define INPUT_ERR_TIME_MAX 3 
#define SYS_LOCK_TIME_SETTING  120    // S设定
//#define INFO_DATA_LENGTH 25
#define PAGE_SIZE 512

typedef struct 
{
//	uint32_t Info[INFO_DATA_LENGTH]; // 
	struct 
	{		
	  //uint8_t  InputLength ; 	//正在输入的密码长度
	  //uint8_t  InputCode[PASSWORD_LENGTH] ; 
	  uint8_t  Code[PASSWORD_LENGTH] ;
	  uint8_t  InputErrCount ; //密码连续输入错误次数
	  uint32_t LockTime ; 
	} PassWrd; 

	uint8_t SaveInfoFlag ;   		//保存信息的标志
	uint8_t NonFirstTimeUseFlag ; 	//不是第一次使用机器

	union 
	{
		struct 
		{
			uint32_t SoftwareVer[3];			//软件版本			
			uint32_t SysInfo[3] ; 			//系统信息
			uint32_t MachineType[3] ; 		//机器型号
			uint32_t MachineNum[3];			//编号
			uint32_t CdKey[3];				//序列号
			uint32_t HardwareVer[3];			//硬件版本
			uint32_t ProductDate[3];			//生产日期	  
		}info;
		
		uint32_t SysData[21]; 
	}Data ; 	
	
//	uint32_t *Num ; 
}SYS_STATU ; 


///////////////////////////////////////USB /////////////////////////////////////////////
typedef enum       //USBconnecting
{
	USB_IN,
	USB_OUT ,
} ENUM_USB_CON;

typedef struct 
{
	ENUM_USB_CON  OldUsbStatu  ;  //0 老的statu  1现在的statu USB插入跟拔出
	ENUM_USB_CON  NewUsbStatu  ; 
	volatile uint8_t  UsbStatuLabel  ; 

}USB_STATU ;
///////////////////////////////////////Time /////////////////////////////////////////////
typedef struct 
{
	uint8_t Click; 
	uint8_t Sec ; // 秒
	uint8_t Min ; 
//	uint8_t Hour; 
//	uint8_t Day ; 
//	uint8_t month ; 
//	uint8_t year; 
//	uint8_t week ; 

}TIME ;

///////////////////////////////////////SYS /////////////////////////////////////////////
typedef enum
{
	NON,
	LED_HRD_ERR , 
	W_T_LED_ERR, 
	IR_T_LED_ERR,
	UV_LED_ERR,
	IR_B_LED_ERR,
	SYS_HRD_ERR ,
	ADC_COUNT_OUT, 
	SYS_CON_TIME_OUT,

	
}SYS_ERROR; 

/////////////////////////////////////////////////////////////////////////////////////////////////


typedef struct 
{
	uint8_t CmdFlag; 	 	// 1指令标志01、……31，此标志位，1
								//MCU每次会打开灯会更新，
								//可通过MCU指令设置此状态	  BB  a

	uint8_t Lightflag;		// 2灯源标志		XX
	uint8_t UsbFlag;		// 3usb标志		YY
	uint8_t Sensor;			// 4SENSOR状态	01-SENSOR1，02-SENSOR2……	
	uint8_t Display;		// 5显示比例		01-16:9，02-4:3				
	uint8_t PlayZom;		// 6预览放大		F代表回放模式，1-不放大，
													//2-2X,3-3X,4-4X,5-5X,
													//6-6X,7-7X				
	uint8_t PhotoFlag; 		// 7连拍标志		1代表非连拍模式，2代表连拍模式，3机器等待状态，（可以通过MCU>DSP指令码发码来设置此状态位）				
	uint8_t SdFlag;			// 8SD卡状态		01-有卡，02，卡拔除，03卡满,04卡故障				
	uint8_t Reserved1;		// 9预留	（可以通过MCU>DSP指令码发码来设置此状态位）				
	uint8_t Reserved2;		// 10预留	（可以通过MCU>DSP指令码发码来设置此状态位）				
	
	
}UART_STATU ;





////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct 
{ 
 	KEY_STATU Key ; 
	LED_STATU Led;
	DSP_STATU Dsp; 
 	USB_STATU Usb; 
	SYS_STATU Sys; 
	TIME	  Time ; 
	SYS_ERROR  Error;
	UART_STATU Uart; 
	uint8_t   Process_TakePht; 
	uint8_t   SleepEnable;
	uint16_t   PhotoNum ;
	uint16_t   SignOutCount ;  // 照片分组数 
	uint16_t   Signtotal ;     // 照片总数 
	uint8_t	   Local_SignOutCount_Flag;  
	uint8_t  XyZoom[3]	;
}SYSTEM ; 

APP_EXT SYSTEM System; 


#endif /*_APP_H_*/







