
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
	#define ONE_SENSOR 				// THREE_SENSOR Ĭ��3SENSOR 
	#define ADC_CHECKING		 	// �Ƿ��е������
	#define DS1307_ON 				//����ʱ��

	#define MACHINE_TYPE	"AD-13" 
	#define PRODUCT_DATE	_DATE_


#elif defined AD_16_STD

	#define AD_16
	#define ONE_SENSOR // THREE_SENSOR Ĭ��3SENSOR 

	#define ADC_CHECKING		 	// �Ƿ��е������

	//#define DS1307_ON 			// ������ʱ��

	#define MACHINE_TYPE	"AD-16" 
	#define PRODUCT_DATE	_DATE_
//	#define INLAND_MACHINE			// ���ڵĻ���

#elif defined AD_16_C608

	#define AD_16
	#define ONE_SENSOR // THREE_SENSOR Ĭ��3SENSOR 
    #define STD_C608
	#define ADC_CHECKING		 	// �Ƿ��е������
	 
	//#define DS1307_ON 			// ������ʱ��
	#define MACHINE_TYPE	"AD-16" 
	#define PRODUCT_DATE	_DATE_

#elif defined AD_16_C608_1000PICS

	#define AD_16
	#define ONE_SENSOR // THREE_SENSOR Ĭ��3SENSOR 
    #define STD_C608
	#define ADC_CHECKING		 	// �Ƿ��е������
	#define AD_16_1000PICS 
	//#define DS1307_ON 			// ������ʱ��
	#define MACHINE_TYPE	"AD-16" 
	#define PRODUCT_DATE	_DATE_

#endif  











//���峡�� 

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

//#ifdef	ADC_CHECKING				��׼ֵ

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



#define D_NON 0xF0 			//û�����������ʱ��

///////////////////////////////////////1 LED /////////////////////////////////////////////
typedef enum
{
	ALL_LED_OFF 	= 0, 	   // ���׹�

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

typedef enum       // dsp��ģʽ
{
	VIEW_MODE , 
	CHECK_MODE  ,  // ���ģʽ
	TF_MODE ,
	PCCAM_MODE , 
	SLEEP_MODE,
} ENUM_DSP_MODE ;


typedef enum      // �Ŵ���
{
	X0,X1,X2,X3,X4 
} ENUM_DSP_ZOOM ;

typedef enum       //sensor ѡ��
{
	NONSENSOR,SENSOR1, SENSOR2,SENSOR3,C608 ,
} ENUM_DSP_SENSOR;

typedef enum       //sensor ѡ��
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
	uint8_t     FC1 ;  		  //�ع�ʱ��			//2
	uint8_t     FC2 ;  		  //�ع�ʱ��			//2
	uint8_t	    WB1 ; 		  //��ƽ��				//2
	uint8_t	    WB2 ; 		  //��ƽ��				//2
	uint8_t 	 Sharpness  ; //���				//1
	uint8_t 	 Contrast	; //�Աȶ�				//1
	uint8_t		 Brightness ; //����				//1
	uint8_t		 Saturation ; //���Ͷ�				//1
	uint8_t 	 Num	;     //��Ӧ����			//1	
	uint8_t 	 Mode	;     //ɫ��ģʽ 			//1		ɫ��ģʽ 01 ��ɫ�ֶ� 03�ڰ��ֶ�
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
        uint8_t Flag ;   // ��¼��ǰ���ĸ�����
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
#define SYS_LOCK_TIME_SETTING  120    // S�趨
//#define INFO_DATA_LENGTH 25
#define PAGE_SIZE 512

typedef struct 
{
//	uint32_t Info[INFO_DATA_LENGTH]; // 
	struct 
	{		
	  //uint8_t  InputLength ; 	//������������볤��
	  //uint8_t  InputCode[PASSWORD_LENGTH] ; 
	  uint8_t  Code[PASSWORD_LENGTH] ;
	  uint8_t  InputErrCount ; //������������������
	  uint32_t LockTime ; 
	} PassWrd; 

	uint8_t SaveInfoFlag ;   		//������Ϣ�ı�־
	uint8_t NonFirstTimeUseFlag ; 	//���ǵ�һ��ʹ�û���

	union 
	{
		struct 
		{
			uint32_t SoftwareVer[3];			//����汾			
			uint32_t SysInfo[3] ; 			//ϵͳ��Ϣ
			uint32_t MachineType[3] ; 		//�����ͺ�
			uint32_t MachineNum[3];			//���
			uint32_t CdKey[3];				//���к�
			uint32_t HardwareVer[3];			//Ӳ���汾
			uint32_t ProductDate[3];			//��������	  
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
	ENUM_USB_CON  OldUsbStatu  ;  //0 �ϵ�statu  1���ڵ�statu USB������γ�
	ENUM_USB_CON  NewUsbStatu  ; 
	volatile uint8_t  UsbStatuLabel  ; 

}USB_STATU ;
///////////////////////////////////////Time /////////////////////////////////////////////
typedef struct 
{
	uint8_t Click; 
	uint8_t Sec ; // ��
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
	uint8_t CmdFlag; 	 	// 1ָ���־01������31���˱�־λ��1
								//MCUÿ�λ�򿪵ƻ���£�
								//��ͨ��MCUָ�����ô�״̬	  BB  a

	uint8_t Lightflag;		// 2��Դ��־		XX
	uint8_t UsbFlag;		// 3usb��־		YY
	uint8_t Sensor;			// 4SENSOR״̬	01-SENSOR1��02-SENSOR2����	
	uint8_t Display;		// 5��ʾ����		01-16:9��02-4:3				
	uint8_t PlayZom;		// 6Ԥ���Ŵ�		F����ط�ģʽ��1-���Ŵ�
													//2-2X,3-3X,4-4X,5-5X,
													//6-6X,7-7X				
	uint8_t PhotoFlag; 		// 7���ı�־		1���������ģʽ��2��������ģʽ��3�����ȴ�״̬��������ͨ��MCU>DSPָ���뷢�������ô�״̬λ��				
	uint8_t SdFlag;			// 8SD��״̬		01-�п���02�����γ���03����,04������				
	uint8_t Reserved1;		// 9Ԥ��	������ͨ��MCU>DSPָ���뷢�������ô�״̬λ��				
	uint8_t Reserved2;		// 10Ԥ��	������ͨ��MCU>DSPָ���뷢�������ô�״̬λ��				
	
	
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
	uint16_t   SignOutCount ;  // ��Ƭ������ 
	uint16_t   Signtotal ;     // ��Ƭ���� 
	uint8_t	   Local_SignOutCount_Flag;  
	uint8_t  XyZoom[3]	;
}SYSTEM ; 

APP_EXT SYSTEM System; 


#endif /*_APP_H_*/







