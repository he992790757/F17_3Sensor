#define __COMMUNICATION
#include <stdio.h> 
#include <stdint.h>
#include "Driver\DrvUART.h" 
#include "Driver\DrvGPIO.h" 
#include "Driver\DrvSYS.h" 
#include "NUC1xx.h" 
#include "communication.h" 
#include <ucos_ii.h>
#include "config.h"
#include "DrvUSB.h"			
#include "V6MDebug.h"
//const uint8_t LOGO[]={0xF9,0x03,0x47,0x52};										
//const uint8_t SAVE[]={0x3F};								
//const uint8_t TOP_W_data[]={0x16,0x05,0x57};				
//			
//const uint8_t Modify_AGC5[]={0xFB,0X05,0X22,0X22};					
//const uint8_t Modify_AGC6[]={0xFB,0X06,0X22,0X22};			
//
//const uint8_t Modify_AGC7[]={0xFB,0X07,0X10,0X10};				


//const uint8_t Modify_TG3[]={0xFC,0x03,0x36,0x3F};				
//const uint8_t Modify_TG4[]={0xFC,0x04,0x64,0x64};			
//const uint8_t Modify_TG5[]={0xFC,0X05,0x18,0x18};				
//const uint8_t Modify_TG6[]={0xFC,0X06,0x22,0x22};				
//
//const uint8_t Modify_TG7[]={0xFC,0X07,0x09,0x09};				


#define CONFIG0         0x00300000
#define CONFIG1         0x00300004

#define NewComm						  //新串口通讯协议

uint32_t u32Data[5];    

#define DSP_UART_TIME_OUT  450
unsigned int Countflag = 0 ; 

volatile uint8_t buffer[64]; 
//uint8_t UART_Flag;     
//volatile uint8_t Continue_Flag;
volatile uint8_t USB_OLD_STATUS;
//extern volatile Status MCU_Status;

///////////////////////////////////////////////	  新增加的东西
volatile uint8_t Status_Change;//extern volatile uint8_t Status_Change;			 //系统状态发生改变标志位
volatile uint8_t Serial_Change;	//extern volatile uint8_t Serial_Change;			 //串口状态发生改变标志位
volatile uint8_t SysInfo;


///////////////////////////////////////////////

//void SendByte(uint8_t data) 
//{ 
//
//	while(UART0->FSR.TX_FULL == 1); 
//	UART0->DATA=data; 
//
//} 
//


//void SendString(void) 
//{ 
//	SendByte(buffer[0]); 
//} 


void UART_INT_HANDLE(uint32_t u32IntStatus) 
{ 
	uint8_t i=0;
	if((u32IntStatus&DRVUART_RDAINT)||(u32IntStatus&DRVUART_TOUTINT))
	{ 

		if(UART0->ISR.RDA_IF==1) 
		{ 
			UART0->ISR.RDA_IF=0;
										 
				for(i=0;i<62;i++) 
				{ 
					if(UART0->FSR.RX_EMPTY ==0)		   		//当FIFO缓冲不为空
					{
						buffer[i]=UART0->DATA;
					}
					else break;
				} 
		}
		else
		if(UART0->ISR.TOUT_IF==1)
		{
			UART0->ISR.TOUT_IF=0;
			for(i=0;i<62;i++) 
			{ 
				if(UART0->FSR.RX_EMPTY ==0)		      		//当FIFO缓冲不为空
				{
					buffer[i]=UART0->DATA;
				}
				else break;
			} 
		}

#ifdef	AD_16 
	if(buffer[0]==0x23)	
	{	
//		unsigned char i =0 ; 

		System.Uart.CmdFlag = buffer[1]; 

		if(System.Uart.CmdFlag == 0xBC) 		   	//DSP主动发送
			{
				
			}
		else if(System.Uart.CmdFlag == 0xBD )		   	//
			{

			}
		else if(System.Uart.CmdFlag == 0x77)
		    {
			   System.SignOutCount = (buffer[0x0D]<<8)|buffer[0x0E];
			   System.Signtotal    = (buffer[0x0F]<<8)|buffer[0x10];	
		    }
		else 												// 正常情况 发送 返回
			{											   	//DSP其他的指令
			//	System.Uart.Lightflag 	= buffer[2] ; 	
				System.Uart.UsbFlag		= buffer[3] ; 
				System.Uart.Sensor		= buffer[4] ; 
				System.Uart.Display		= buffer[5] ; 
			 //	System.Uart.PlayZom		= buffer[6] ; 
				System.Uart.PhotoFlag	= buffer[7] ;   // 0 ，闲  1，连拍 告诉网络， 2 存卡瓶颈 ，3 忙
				System.Uart.SdFlag		= buffer[8] ;   // 01-有卡，02，卡拔除，03卡满,04卡故障
				System.Uart.Reserved1	= buffer[9] ;   
				System.Uart.Reserved2	= buffer[10] ;  				
			}	/*  */					
			
//		for(i = 0 ; i< 11;i++ )
//		{
//			GR_DBG_PRINTF(" 0x%X ", buffer[i+1]); 
//			buffer[i] = 0x00 ; 
//		}
//		GR_DBG_PRINTF("\n\n\n "); 
	}

#elif defined AD_13

	if(buffer[0]==0x23)
	{
		if(buffer[3]==0x03)
		{
			USB_STATUS= USB_OUT;
		}
		else if(buffer[3]==0x04)
		{
			USB_STATUS= USB_IN;
		}

		MCU_Status.Sys_Status	=buffer[3];		//存储系统状态
		MCU_Status.Sen_Status	=buffer[4];		//存储sensor状态
		MCU_Status.Scale_Status	=buffer[5];		//存储显示比例状态,这个需要自己设置，DSP默认不判断
		MCU_Status.Menu_Status	=buffer[6];		//存储菜单状态
		MCU_Status.SD_Status	=buffer[7];		//存储SD卡状态
		Serial_Change=TRUE;		
	
	}
#endif 

	} 
			 
}  

//void DSP_INIT(void)
//{
//	 Scen_Send(0x60,0x00);				   //拍照水印
//	 OSTimeDly(20);
//
//	 Scen_Send(0xC1,0x60);				   //duibidu
//	 OSTimeDly(50);
//	
//	 OSTimeDly(20);
//	 Scen_Send(0x01,0x00);
//	 OSTimeDly(20);
//	 DSP_SEND(3, &TOP_W_data[0]); 
//	 OSTimeDly(50);
//}

unsigned char  SHOW_SCREEN_T_W(uint8_t comm, uint8_t time, const uint8_t *DSP_DATA)
{
	uint8_t i=0,cnt=0;
	for(;;cnt++)
	{
		if(*(DSP_DATA+cnt) == NULL)
		{
			if(*(DSP_DATA+cnt+1 ) == NULL) break; 
		}
	}
   	while(UART0->FSR.TX_FULL == 1);		   
	UART0->DATA = 0xAA;	
		
	while(UART0->FSR.TX_FULL == 1);					
	UART0->DATA = 0x23;

	while(UART0->FSR.TX_FULL == 1);					
	UART0->DATA = comm;

	while(UART0->FSR.TX_FULL == 1);					
	UART0->DATA = time;

	while(UART0->FSR.TX_FULL == 1);					
	UART0->DATA = cnt;

	for(i=0;i<cnt;i++)
	{
		while(UART0->FSR.TX_FULL == 1);							   
		UART0->DATA = *(DSP_DATA+i);	
	}
	
	while(UART0->FSR.TX_FULL == 1);		   
	UART0->DATA = 0xAA;		
// 	OSTimeDly(20) ;
	Countflag = 0 ; 
	while(System.Uart.CmdFlag != comm)
		{
			OSTimeDly(1),
			Countflag++; 
			if(Countflag > DSP_UART_TIME_OUT) 
			//	return 1 ;  
			{	Countflag = 0 ; 
				System.Error = SYS_CON_TIME_OUT ; 
				GR_DBG_PRINTF("\nthe EEROR inrrupt Flag: 0x%x  \n\n ",comm );
				return 1 ; 
			}
			
		} 
	
	return 0 ; 
	
}


unsigned char  SHOW_SCREENW(uint8_t comm,/* uint8_t cnt,*/ const uint8_t *DSP_DATA)
{
	uint8_t i=0,cnt=0;
	for(;;cnt++)
	{
		if(*(DSP_DATA+cnt) == NULL)
		{
			if(*(DSP_DATA+cnt+1 ) == NULL) break; 
		}
	}
   	while(UART0->FSR.TX_FULL == 1);		   
	UART0->DATA = 0xAA;	
		
	while(UART0->FSR.TX_FULL == 1);					
	UART0->DATA = 0x23;

	while(UART0->FSR.TX_FULL == 1);					
	UART0->DATA = comm;

	while(UART0->FSR.TX_FULL == 1);					
	UART0->DATA = cnt;

	for(i=0;i<cnt;i++)
	{
		while(UART0->FSR.TX_FULL == 1);							   
		UART0->DATA = *(DSP_DATA+i);	
	}
	
	while(UART0->FSR.TX_FULL == 1);		   
	UART0->DATA = 0xAA;		
// 	OSTimeDly(20) ;
	Countflag = 0 ; 
	while(System.Uart.CmdFlag != comm)
		{
			OSTimeDly(1),
			Countflag++; 
			if(Countflag > DSP_UART_TIME_OUT) 
			//	return 1 ;  
			{	Countflag = 0 ; 
				System.Error = SYS_CON_TIME_OUT ; 
				GR_DBG_PRINTF("\nthe EEROR inrrupt Flag: 0x%x  \n\n ",comm );
				return 1 ; 
			}
			
		} 
	
	return 0 ; 
	
}

unsigned char  SHOW_SCREEN(uint8_t comm,/* uint8_t cnt,*/ const uint8_t *DSP_DATA)
{
	uint8_t i=0,cnt=0;
	for(;;cnt++)
	{
		if(*(DSP_DATA+cnt) == NULL)	 break; 
	}
   	while(UART0->FSR.TX_FULL == 1);		   
	UART0->DATA = 0xAA;	
		
	while(UART0->FSR.TX_FULL == 1);					
	UART0->DATA = 0x23;

	while(UART0->FSR.TX_FULL == 1);					
	UART0->DATA = comm;

	while(UART0->FSR.TX_FULL == 1);					
	UART0->DATA = cnt;

	for(i=0;i<cnt;i++)
	{
		while(UART0->FSR.TX_FULL == 1);							   
		UART0->DATA = *(DSP_DATA+i);	
	}
	
	while(UART0->FSR.TX_FULL == 1);		   
	UART0->DATA = 0xAA;		
// 	OSTimeDly(20) ;
	Countflag = 0 ; 
	while(System.Uart.CmdFlag != comm)
		{
			OSTimeDly(1),
			Countflag++; 
			if(Countflag > DSP_UART_TIME_OUT) 
			//	return 1 ;  
			{	Countflag = 0 ; 
				System.Error = SYS_CON_TIME_OUT ; 
				GR_DBG_PRINTF("\nthe EEROR inrrupt Flag: 0x%x  \n\n ",comm );
				return 1 ; 
			}
			
		} 
	
	return 0 ; 
	
}

unsigned char  SHOW_SCREEN_LONG(uint8_t comm,/* uint8_t cnt,*/ const uint8_t *DSP_DATA1,const uint8_t *DSP_DATA2)
{
	uint8_t i=0,cnt=0,cnt1=0,cnt2=0;
	for(;;cnt1++)
	{
		if(*(DSP_DATA1+cnt1) == NULL) break; 
	}

	for(;;cnt2++)
	{
		if(*(DSP_DATA2+cnt2) == NULL) break; 
	}
	cnt = cnt1 +cnt2 ; 

   	while(UART0->FSR.TX_FULL == 1);		   
	UART0->DATA = 0xAA;	
		
	while(UART0->FSR.TX_FULL == 1);					
	UART0->DATA = 0x23;

	while(UART0->FSR.TX_FULL == 1);					
	UART0->DATA = comm;


	while(UART0->FSR.TX_FULL == 1);					
	UART0->DATA = cnt;

	for(i=0;i<cnt1;i++)
	{
		while(UART0->FSR.TX_FULL == 1);							   
		UART0->DATA = *(DSP_DATA1+i);	
	}
	for(i=0;i<cnt2;i++)
	{
		while(UART0->FSR.TX_FULL == 1);							   
		UART0->DATA = *(DSP_DATA2+i);	
	}	
		
	while(UART0->FSR.TX_FULL == 1);		   
	UART0->DATA = 0xAA;		
	Countflag = 0 ; 
	while(System.Uart.CmdFlag != comm)
		{
			OSTimeDly(1),
			Countflag++; 
			if(Countflag > DSP_UART_TIME_OUT) 
			{  Countflag = 0 ; 
				System.Error = SYS_CON_TIME_OUT ; 
				GR_DBG_PRINTF("\nthe EEROR inrrupt Flag: 0x%x  \n\n ",comm );
				return 1 ; 
			}
			
		} 
	
	return 0 ; 
	
 //	OSTimeDly(50) ;
}
unsigned char  SHOW_SCREENA(uint8_t comm, uint8_t cnt, const uint8_t *DSP_DATA)
{
	uint8_t i=0;
    while(UART0->FSR.TX_FULL == 1);		   
 	UART0->DATA = 0xAA;	
		
	while(UART0->FSR.TX_FULL == 1);					
	UART0->DATA = 0x23;

	while(UART0->FSR.TX_FULL == 1);					
	UART0->DATA = comm;

	while(UART0->FSR.TX_FULL == 1);					
	UART0->DATA = cnt;

	for(i=0;i<cnt;i++)
	{
		while(UART0->FSR.TX_FULL == 1);							   
		UART0->DATA = *(DSP_DATA+i);	
	}
	
	while(UART0->FSR.TX_FULL == 1);		   
	UART0->DATA = 0xAA;	
	//OSTimeDly(5) ;	
	Countflag = 0 ; 
	while(System.Uart.CmdFlag != comm)
		{
			OSTimeDly(1),
			Countflag++; 
			if(Countflag > DSP_UART_TIME_OUT) 
			//	return 1 ;  
			{	Countflag = 0 ; 
				System.Error = SYS_CON_TIME_OUT ; 
				GR_DBG_PRINTF("\nthe EEROR inrrupt Flag: 0x%x  \n\n ",comm );
				return 1 ; 
			}
			
		} 
	
	return 0 ; 	
}

unsigned char  DSP_SEND(uint8_t cnt, const uint8_t *DSP_DATA)
{
	uint8_t i;
   	while(UART0->FSR.TX_FULL == 1);		   
 	UART0->DATA = 0xAA;	
		
	while(UART0->FSR.TX_FULL == 1);					
	UART0->DATA = 0x23;

	for(i=0;i<cnt;i++)
	{
		while(UART0->FSR.TX_FULL == 1);							   
		UART0->DATA = *(DSP_DATA+i);	
	}
		
	while(UART0->FSR.TX_FULL == 1);		   
	UART0->DATA = 0xAA;	
	//OSTimeDly(5) ;
	Countflag = 0 ; 	
	while(System.Uart.CmdFlag != *(DSP_DATA+0))
		{
			OSTimeDly(1),
			Countflag++; 
			if(Countflag > DSP_UART_TIME_OUT) 
			//	return 1 ;  
			{	Countflag = 0 ; 
				System.Error = SYS_CON_TIME_OUT ; 
				GR_DBG_PRINTF("\nthe EEROR inrrupt Flag: 0x%x  \n\n ",*(DSP_DATA+0) );
				return 1 ; 
			}
			
		} 
	
	return 0 ; 
	
}
unsigned char  DSP_SENDA(uint8_t cnt, volatile uint8_t *DSP_DATA)
{
	uint8_t i;

   	while(UART0->FSR.TX_FULL == 1);		   
 	UART0->DATA = 0xAA;	
		
	while(UART0->FSR.TX_FULL == 1);					
	UART0->DATA = 0x23;
	for(i=0;i<cnt;i++)
	{
		while(UART0->FSR.TX_FULL == 1);							   
		UART0->DATA = *(DSP_DATA+i);	
	}

	while(UART0->FSR.TX_FULL == 1);		   
	UART0->DATA = 0xAA;	
 	//OSTimeDly(2) ;	
 	Countflag = 0 ; 
 	while(System.Uart.CmdFlag != *(DSP_DATA+0))
		{
			OSTimeDly(1),
			Countflag++; 
			if(Countflag > DSP_UART_TIME_OUT) 
			//	return 1 ;  
			{	Countflag = 0 ; 
				System.Error = SYS_CON_TIME_OUT ; 
				GR_DBG_PRINTF("\nthe EEROR inrrupt Flag: 0x%x  \n\n ",*(DSP_DATA+0) );
				return 1 ; 
			}
			
		} 
	return 0 ; 	

}
unsigned char  DSP_SENDBW(uint8_t CMD,uint8_t Foward, const uint8_t *DSP_DATA)
{
	uint8_t i 	,cnt=0;

	for(;;cnt++)
	{
		if(*(DSP_DATA+cnt) == NULL) break; 
	}

   	while(UART0->FSR.TX_FULL == 1);		   
	UART0->DATA = 0xAA;	
			
	while(UART0->FSR.TX_FULL == 1);					
	UART0->DATA = 0x23;

	if(CMD != NULL)
		{
			while(UART0->FSR.TX_FULL == 1);					
			UART0->DATA = CMD;
		}
	if(Foward != NULL)
		{
			while(UART0->FSR.TX_FULL == 1);					
			UART0->DATA = Foward;
		}
	
	while(UART0->FSR.TX_FULL == 1);					
	UART0->DATA = cnt;
	for(i=0;*(DSP_DATA+i)!= NULL;i++)
	{
		while(UART0->FSR.TX_FULL == 1);							   
		UART0->DATA = *(DSP_DATA+i);	
	}
	while(UART0->FSR.TX_FULL == 1);		   
	UART0->DATA = 0xAA;		
	//OSTimeDly(10);
	Countflag = 0 ; 
	while(System.Uart.CmdFlag != CMD)
		{
			OSTimeDly(1),
			Countflag++; 
			if(Countflag > DSP_UART_TIME_OUT) 
			//	return 1 ;  
			{	Countflag = 0 ; 
				System.Error = SYS_CON_TIME_OUT ; 
				GR_DBG_PRINTF("\nthe EEROR inrrupt Flag: 0x%x \n\n ",CMD );
				return 1 ; 
			}
			
		} 
	
	return 0 ; 	
}

unsigned char  DSP_SENDB(uint8_t CMD,uint8_t Foward, const uint8_t *DSP_DATA)
{
	uint8_t i 	,cnt=0;

	for(;;cnt++)
	{
		if(*(DSP_DATA+cnt) == NULL) break; 
	}

   	while(UART0->FSR.TX_FULL == 1);		   
	UART0->DATA = 0xAA;	
			
	while(UART0->FSR.TX_FULL == 1);					
	UART0->DATA = 0x23;

	if(CMD != NULL)
		{
			while(UART0->FSR.TX_FULL == 1);					
			UART0->DATA = CMD;
		}
	if(Foward != NULL)
		{
			while(UART0->FSR.TX_FULL == 1);					
			UART0->DATA = Foward;
		}
	
	while(UART0->FSR.TX_FULL == 1);					
	UART0->DATA = cnt;

	for(i=0;*(DSP_DATA+i)!= NULL;i++)
	{
		while(UART0->FSR.TX_FULL == 1);							   
		UART0->DATA = *(DSP_DATA+i);	
	}
	while(UART0->FSR.TX_FULL == 1);		   
	UART0->DATA = 0xAA;		
	//OSTimeDly(10);
	Countflag = 0 ; 
	while(System.Uart.CmdFlag != CMD)
		{
			OSTimeDly(1),
			Countflag++; 
			if(Countflag > DSP_UART_TIME_OUT) 
			//	return 1 ;  
			{	Countflag = 0 ; 
				System.Error = SYS_CON_TIME_OUT ; 
				GR_DBG_PRINTF("\nthe EEROR inrrupt Flag: 0x%x \n\n ",CMD );
				return 1 ; 
			}
			
		} 
	
	return 0 ; 	
}

unsigned char  DSP_SEND_USB(uint8_t cnt, uint8_t *DSP_DATA)
{
	uint8_t i;
   	while(UART0->FSR.TX_FULL == 1);		   
 	UART0->DATA = 0xAA;	
		
	while(UART0->FSR.TX_FULL == 1);					
	UART0->DATA = 0x23;

	for(i=0;i<cnt;i++)
	{
		while(UART0->FSR.TX_FULL == 1);							   
		UART0->DATA = *(DSP_DATA+i);	
	}
	
	while(UART0->FSR.TX_FULL == 1);		   
	UART0->DATA = 0xAA;	
	//OSTimeDly(1) ;	
//	Countflag = 0 ; 
//	while(System.Uart.CmdFlag != *(DSP_DATA+0))
//		{
//			OSTimeDly(1),
//			Countflag++; 
//			if(Countflag > DSP_UART_TIME_OUT) 
//			//	return 1 ;  
//			{	Countflag = 0 ; 
//				System.Error = SYS_CON_TIME_OUT ; 
//				GR_DBG_PRINTF("\nthe EEROR inrrupt Flag: 0x%x \n\n ",*(DSP_DATA+0) );
//				return 1 ; 
//			}
//			
//		} 
	return 0 ; 	
	
}

// void SHOW_SCREEN(uint8_t comm, uint8_t cnt, const uint8_t *DSP_DATA)
// {
// 	uint8_t i;

// //   	while(UART0->FSR.TX_FULL == 1);		   
// //	UART0->DATA = 0xAA;	
// 		
// 	while(UART0->FSR.TX_FULL == 1);					
// 	UART0->DATA = 0x23;

// 	while(UART0->FSR.TX_FULL == 1);					
// 	UART0->DATA = comm;

// 	while(UART0->FSR.TX_FULL == 1);					
// 	UART0->DATA = cnt;

// 	for(i=0;i<cnt;i++)
// 	{
// 		while(UART0->FSR.TX_FULL == 1);							   
// 		UART0->DATA = *(DSP_DATA+i);	
// 	}
// 	
// 	while(UART0->FSR.TX_FULL == 1);		   
// 	UART0->DATA = 0xAA;		
// }

unsigned char  Scen_Send(uint8_t Scen, uint8_t State)
{
	while(UART0->FSR.TX_FULL == 1);		   
	UART0->DATA = 0xAA;
		
	while(UART0->FSR.TX_FULL == 1);
	UART0->DATA = 0x23;

	while(UART0->FSR.TX_FULL == 1);				   
	UART0->DATA = Scen;
	
	while(UART0->FSR.TX_FULL == 1);							   
	UART0->DATA = State;	
		
	while(UART0->FSR.TX_FULL == 1);							   
	UART0->DATA = 0xAA;	
	//OSTimeDly(10);
	Countflag = 0 ; 
	while(System.Uart.CmdFlag != Scen)
		{
			OSTimeDly(1),
			Countflag++; 
			if(Countflag > DSP_UART_TIME_OUT) 
			//	return 1 ;  
			{	Countflag = 0 ; 
				System.Error = SYS_CON_TIME_OUT ; 
				GR_DBG_PRINTF("\nthe EEROR inrrupt Flag: 0x%x \n\n",Scen );
				return 1 ; 
			}
			
		} 
	return 0 ; 	
}

unsigned char  Dsp_Send_Data(uint8_t data1,uint8_t data2,uint8_t data3,uint8_t data4,uint8_t data5)
{
		
	System.Uart.CmdFlag = 0x00 ;
		
	while(UART0->FSR.TX_FULL == 1);		   
	UART0->DATA = 0xAA;	
		
	while(UART0->FSR.TX_FULL == 1);
	UART0->DATA = 0x23;

	if(data1 != D_NON)
	{
		while(UART0->FSR.TX_FULL == 1);	   
		UART0->DATA = data1;
	}
	if(data2 != D_NON)
	{
		while(UART0->FSR.TX_FULL == 1);	   
		UART0->DATA = data2;
	}
	if(data3 != D_NON)
	{
		while(UART0->FSR.TX_FULL == 1);	   
		UART0->DATA = data3;
	}
	if(data4 != D_NON)
	{
		while(UART0->FSR.TX_FULL == 1);	   
		UART0->DATA = data4;
	}
	if(data5 != D_NON)
	{
		while(UART0->FSR.TX_FULL == 1);	   
		UART0->DATA = data5;
	}

	while(UART0->FSR.TX_FULL == 1);		   
	UART0->DATA = 0xAA;	
	//OSTimeDly(5) ;

	Countflag = 0 ; 
	while(System.Uart.CmdFlag != data1)
		{
			OSTimeDly(1),
			Countflag++; 
			if(Countflag > DSP_UART_TIME_OUT) 
			//	return 1 ;  
			{	Countflag = 0 ; 
				System.Error = SYS_CON_TIME_OUT ; 
				GR_DBG_PRINTF("\nthe EEROR inrrupt Flag: 0x%x \n\n",data1 );
				return 1 ; 
			}
		} 
	return 0 ; 
}

unsigned char  Select_Send_LONG(uint8_t Select_data)
{		
	System.Uart.CmdFlag = 0x00 ;
	
	while(UART0->FSR.TX_FULL == 1);		   
	UART0->DATA = 0xAA;	
		
	while(UART0->FSR.TX_FULL == 1);
	UART0->DATA = 0x23;

	while(UART0->FSR.TX_FULL == 1);	   
	UART0->DATA = Select_data;

	while(UART0->FSR.TX_FULL == 1);		   
	UART0->DATA = 0xAA;	
	//OSTimeDly(5) ;

	Countflag = 0 ; 
	while(System.Uart.CmdFlag != Select_data)
		{
			OSTimeDly(1),
			Countflag++; 
			if(Countflag >4000) 
			//	return 1 ;  
			{	Countflag = 0 ; 
				System.Error = SYS_CON_TIME_OUT ; 
				GR_DBG_PRINTF("\nthe EEROR inrrupt Flag: 0x%x \n\n",Select_data );
				return 1 ; 
			}
		} 
	return 0 ; 
}

unsigned char  Select_Send(uint8_t Select_data)
{		
	System.Uart.CmdFlag = 0x00 ;	
	while(UART0->FSR.TX_FULL == 1);		   
	UART0->DATA = 0xAA;	
		
	while(UART0->FSR.TX_FULL == 1);
	UART0->DATA = 0x23;

	while(UART0->FSR.TX_FULL == 1);	   
	UART0->DATA = Select_data;

	while(UART0->FSR.TX_FULL == 1);		   
	UART0->DATA = 0xAA;	
	//OSTimeDly(5) ;

	Countflag = 0 ; 
	while(System.Uart.CmdFlag != Select_data)
		{
			OSTimeDly(1),
			Countflag++; 
			if(Countflag > DSP_UART_TIME_OUT) 
			//	return 1 ;  
			{	Countflag = 0 ; 
				System.Error = SYS_CON_TIME_OUT ; 
				GR_DBG_PRINTF("\nthe EEROR inrrupt Flag: 0x%x \n\n",Select_data );
				return 1 ; 
			}
		} 
	return 0 ; 
}


int32_t DrvFMC_Read(uint32_t u32addr, uint32_t * u32data)
{ 
    FMC->ISPCMD.FCTRL = 0;
    FMC->ISPCMD.FCEN = 0;
    FMC->ISPCMD.FOEN = 0;
    FMC->ISPADR = u32addr;
//    FMC->ISPDAT = 0;
    __set_PRIMASK(1);
    FMC->ISPTRG.ISPGO = 1;    
    __ISB();
    while (FMC->ISPTRG.ISPGO);
    __set_PRIMASK(0);
    
    if (FMC->ISPCON.ISPFF == 1)
    {
        FMC->ISPCON.ISPFF = 1;
//        return E_DRVFMC_ERR_ISP_FAIL;
		return 0;
    }
    
    *u32data = FMC->ISPDAT;
    return 0;
}

void DrvFMC_EnableISP(void)
{
    if (SYSCLK->PWRCON.OSC22M_EN == 0)
    {
        SYSCLK->PWRCON.OSC22M_EN = 1;
        
        /* Wait 22M stable */
        OSTimeDly(1);
    }

    SYSCLK->AHBCLK.ISP_EN = 1;
    FMC->ISPCON.ISPEN = 1;
}

void DrvFMC_DisableISP(void)
{
    FMC->ISPCON.ISPEN = 0;
}
int32_t DrvFMC_Erase(uint32_t u32addr)
{
    FMC->ISPCMD.FCTRL = 2;
    FMC->ISPCMD.FCEN = 0;
    FMC->ISPCMD.FOEN = 1;
    FMC->ISPADR = u32addr;
    __set_PRIMASK(1);
    FMC->ISPTRG.ISPGO = 1;  
    __ISB();
    while (FMC->ISPTRG.ISPGO);  
    __set_PRIMASK(0);
    
    if (FMC->ISPCON.ISPFF == 1)
    {
        FMC->ISPCON.ISPFF = 1;
//        return E_DRVFMC_ERR_ISP_FAIL;
		return 0;
    }
    
    return 0;
}

int32_t DrvFMC_Write(uint32_t u32addr, uint32_t u32data)
{
    FMC->ISPCMD.FCTRL = 1;
    FMC->ISPCMD.FCEN = 0;
    FMC->ISPCMD.FOEN = 1;
    FMC->ISPADR = u32addr;
    FMC->ISPDAT = u32data;
    __set_PRIMASK(1);
    FMC->ISPTRG.ISPGO = 1;
    __ISB();
    while (FMC->ISPTRG.ISPGO);
    __set_PRIMASK(0);
    
    if (FMC->ISPCON.ISPFF == 1)
    {
        FMC->ISPCON.ISPFF = 1;
//        return E_DRVFMC_ERR_ISP_FAIL;
		return 0;
    }

    
    return 0;
}

int32_t DrvFMC_WriteConfig(uint32_t u32data0, uint32_t u32data1)
{       
    if ( DrvFMC_Erase(CONFIG0) != E_SUCCESS )
//        return E_DRVFMC_ERR_ISP_FAIL;
		return 0;
    
    if ( DrvFMC_Write(CONFIG0, u32data0) != E_SUCCESS )
//        return E_DRVFMC_ERR_ISP_FAIL;	
		return 0;
    return DrvFMC_Write(CONFIG1, u32data1);
}
uint32_t DrvFMC_ReadDataFlashBaseAddr(void)
{	
	return FMC->DFBADR;
}
