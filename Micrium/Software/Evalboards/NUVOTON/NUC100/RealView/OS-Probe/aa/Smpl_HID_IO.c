/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2009 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include "Driver\DrvGPIO.h"
#include "Driver\DrvSYS.h"
#include "Driver\DrvUART.h"
#include "Driver\DrvUSB.h"
#include "HID_API.h"
#include "communication.h" 
#include "config.h"
#include "keydispose.h"
#include "HIDSysIO.h"
#include "V6MDebug.h"
#include "led.h"

const uint8_t TOP_WT[]={0x16,0x01,0x57};

#define DATA_FLASH_BASE          ((     uint32_t)0x0001F000)
#define GR_ID          			0x12345678UL



extern void	Bot_W_On(void);
extern void LensCut(uint8_t N_P);
extern int32_t HID_MainProcess(void);
extern uint8_t UART_Flag;
volatile uint8_t AV_flag;
extern uint8_t UV_MODE;
extern uint8_t 	K2_time;
extern uint8_t 	K1_time;
extern uint8_t  IR_MODE;
extern uint8_t  WT_MODE;
extern uint8_t PART_VIEW;

void Delay(uint32_t delayCnt)
{
    while (delayCnt--)
    {
        __NOP();
        __NOP();
    }
}

void InitIO()
{
	DrvGPIO_Open(E_GPA, 0, E_IO_OUTPUT);
	DrvGPIO_Open(E_GPA, 1, E_IO_OUTPUT);
	DrvGPIO_Open(E_GPA, 2, E_IO_OUTPUT);
	DrvGPIO_Open(E_GPA, 3, E_IO_OUTPUT);
	DrvGPIO_Open(E_GPA, 4, E_IO_OUTPUT);
	DrvGPIO_Open(E_GPA, 5, E_IO_OUTPUT);
	DrvGPIO_Open(E_GPA, 6, E_IO_OUTPUT);
	DrvGPIO_Open(E_GPA, 7, E_IO_OUTPUT);
	DrvGPIO_Open(E_GPC, 7, E_IO_OUTPUT);

	DrvGPIO_SetPortBits (E_GPA, 0xFFFF);
	DrvGPIO_SetPortBits (E_GPB, 0xFFFF);
	DrvGPIO_SetPortBits (E_GPC, 0xFFFF);
	DrvGPIO_SetPortBits (E_GPD, 0xFFFF);
	DrvGPIO_SetPortBits (E_GPE, 0xFFFF);
}

void InitValue()
{
	lens_flag=1;
	cut_flagA=1;
	cut_flagB=1;
	AV_flag=0;
	IR_MODE=0;
	UV_MODE=0;
	PART_VIEW=0;
	WT_MODE=0;
}

/*************摄像头开机初始化****************/
void init_sensor(void)
{

}

void InitStart()
{
	uint8_t i;

	init_sensor();

//	K2_LED=0;			//开机白光灯亮
	for(i=0;i<10;i++)
	{	DrvSYS_Delay(120000);
		K2_LED=!K2_LED; //开机LED闪，模拟进入自检
	}
//	K2_LED=0;
	TOP_W_on();
	WT_MODE=1;
//	DrvSYS_Delay(300000);
//	DrvSYS_Delay(300000);
//	DrvSYS_Delay(300000);
//	DrvSYS_Delay(300000);
//	DrvSYS_Delay(300000);
//	DrvSYS_Delay(300000);
//	DrvSYS_Delay(300000);
//	DrvSYS_Delay(300000);
//	DrvSYS_Delay(300000);
//	DrvSYS_Delay(300000);
//	DrvSYS_Delay(300000);
//	DrvSYS_Delay(300000);
//	DrvSYS_Delay(300000);
//	DrvSYS_Delay(300000);
//	DrvSYS_Delay(300000);
//	DrvSYS_Delay(300000);
	DrvSYS_Delay(300000);
	DrvSYS_Delay(300000);


	DrvSYS_Delay(300000);
	DrvSYS_Delay(300000);
	DrvSYS_Delay(300000);
	DrvSYS_Delay(300000);
	DrvSYS_Delay(300000);
	DrvSYS_Delay(300000);
	DrvSYS_Delay(300000);
	DrvSYS_Delay(300000);
	DrvSYS_Delay(300000);
	DrvSYS_Delay(300000);
	DrvSYS_Delay(300000);
	DrvSYS_Delay(300000);
	DrvSYS_Delay(300000);
	DrvSYS_Delay(300000);
	DrvSYS_Delay(300000);
	DrvSYS_Delay(300000);
	DrvSYS_Delay(300000);
	DSP_SEND(3, &TOP_WT[0]);
	DrvSYS_Delay(100000); 
	Scen_Send(G_SENCE_WT,0x00);
	DrvSYS_Delay(300000);
	Select_Send(0x70);						//16:9
	DrvSYS_Delay(300000);
	DrvSYS_Delay(300000);
	DrvSYS_Delay(300000);
	DrvSYS_Delay(300000);
	DrvSYS_Delay(300000);
	K2_time=1;
	K1_time=1;
	lens_flag=0;
	LensCut(0);
	lens_flag=1;

}


/*---------------------------------------------------------------------------------------------------------*/
/*  Main Function									                                           			   */
/*---------------------------------------------------------------------------------------------------------*/
//
//int32_t main(void)
//{
////	uint8_t bInChar[12] ={0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0x20,0x05,0x00,0x3A,0xD0}; 
//	int32_t i32Ret = E_SUCCESS;
//	E_DRVUSB_STATE eUsbState;
//	
////
////    STR_UART_T sParam;
////
////    /* Set UART Pin */
////    DrvGPIO_InitFunction(E_FUNC_UART0);
////
////    /* UART Setting */
////    sParam.u32BaudRate 		= 115200;
////    sParam.u8cDataBits 		= DRVUART_DATABITS_8;
////    sParam.u8cStopBits 		= DRVUART_STOPBITS_1;
////    sParam.u8cParity 		= DRVUART_PARITY_NONE;
////    sParam.u8cRxTriggerLevel = DRVUART_FIFO_1BYTES;			//FIFO缓存长度设置
//////	sParam.u8TimeOut		 =4;					 		//FIFO超时溢出--Q
////    /* Select UART Clock Source From 12Mhz*/
////    DrvSYS_SelectIPClockSource(E_SYS_UART_CLKSRC, 0);
////
////    /* Set UART Configuration */
////    DrvUART_Open(UART_PORT0, &sParam);
////		
////	DrvUART_EnableInt(UART_PORT0,DRVUART_RDAINT,UART_INT_HANDLE); 
////
////    UNLOCKREG();
////
////    SYSCLK->PWRCON.XTL12M_EN = 1;
////
////    /* Enable PLL */
////    DrvSYS_SetPLLMode(0);
////    Delay(1000);
////
////    /* Switch to PLL clock */
////    DrvSYS_SelectHCLKSource(2);
////    Delay(100);
////
////    /* Update system core clock */
////    SystemCoreClockUpdate();
////
////    printf("NUC100 USB HID IO\n");
////	DrvUART_Write(UART_PORT0,bInChar,12); 
////
////	InitIO();
////	InitStart();
//
//    STR_UART_T sParam;
//
//	
////	DrvSYS_ClearResetSource (1 << 1);    /* Clear Bit 3 (Low Voltage Reset) */ 
//
//    /* Set UART Pin */
////   DrvGPIO_InitFunction(E_FUNC_UART0);
// 	DrvGPIO_InitFunction(E_FUNC_UART0_RX_TX);
//	
//    /* UART Setting */
//    sParam.u32BaudRate 		= 115200;
//    sParam.u8cDataBits 		= DRVUART_DATABITS_8;
//    sParam.u8cStopBits 		= DRVUART_STOPBITS_1;
//    sParam.u8cParity 		= DRVUART_PARITY_NONE;
//    sParam.u8cRxTriggerLevel = DRVUART_FIFO_1BYTES;
//
//    /* Select UART Clock Source From 12Mhz*/
//    DrvSYS_SelectIPClockSource(E_SYS_UART_CLKSRC, 0);
//
//    /* Set UART Configuration */
//    DrvUART_Open(UART_PORT0, &sParam);
//
//    UNLOCKREG();
//
//    SYSCLK->PWRCON.XTL12M_EN = 1;
//
//    /* Enable PLL */
//    DrvSYS_SetPLLMode(0);
//    Delay(1000);
//
//    /* Switch to PLL clock */
//    DrvSYS_SelectHCLKSource(2);
//    Delay(100);
//
//    /* Update system core clock */
//    SystemCoreClockUpdate();
//
//	DrvUART_EnableInt(UART_PORT0,DRVUART_RDAINT,UART_INT_HANDLE);		//使能串口中断
//	/***********************FMC配置**************************/
//	DrvFMC_EnableISP();
//
//	DrvFMC_WriteConfig (0xFFFFFFFE, 0x1E000);
//
//	DrvFMC_Erase (0x1F000); 
//	DrvFMC_Write (0x1F000, 0x12345678); 
//	DrvFMC_DisableISP();
//
//
////	LOCKREG();
//    printf("NUC100 USB HID IO\n");
//
//
////	Light_Init();
//
//
//	InitValue();
//	InitIO();
//	C3_PWR=0;
//	
//
//	
//	InitStart();
//
////	C3_PWR=0;
//
//	DSP_INIT();
////	Scen_Send(0x3B,0x01);					//把串口返送的码显示到屏幕上
////	DrvGPIO_Open(E_GPB, 2, E_IO_QUASI);
////	DrvGPIO_Open(E_GPB, 3, E_IO_QUASI);
//
//	
//
////	TEST_LED=0;
////	CUT_B1=0;
////	CUT_B2=0;
////	CUT_A1=0;
////	CUT_A2=0;
//    while (1)
//    {
//
//	    i32Ret = DrvUSB_Open(0);
//	    if (i32Ret != E_SUCCESS)
//	        return i32Ret;
//	
//	    while (1)
//	    {
//	        /* Disable USB-related interrupts. */
//	        _DRVUSB_ENABLE_MISC_INT(0);
//	
//	        /* Enable float-detection interrupt. */
//	        _DRVUSB_ENABLE_FLDET_INT();
//	
//	        // Wait for USB connected.
//	        while (1)
//	        {
//	            // Order here is significant.
//	            // Give a chance to handle remaining events before exiting this loop.
//	            eUsbState = DrvUSB_GetUsbState();
//	
//	            //DrvUSB_DispatchEvent();
//	
//	            if (eUsbState >= eDRVUSB_ATTACHED &&
//	                    eUsbState != eDRVUSB_SUSPENDED)
//	            {
//	                break;
//	            }
//				KeyDispose();
//	        }
//	
//	        /* Start HID and install the callback functions to handle in/out report */
//	        HID_Init((void *)HID_GetInReport, (void *)HID_SetOutReport);
//	
//	        // Enable USB-related interrupts.
//	        _DRVUSB_ENABLE_MISC_INT(INTEN_WAKEUP | INTEN_WAKEUPEN | INTEN_FLDET | INTEN_USB | INTEN_BUS);
//	
//	        // Poll and handle USB events.
//	        while (1)
//	        {
//	            eUsbState = DrvUSB_GetUsbState();
//	
//	            DrvUSB_DispatchEvent();
//	
//	            if (eUsbState == eDRVUSB_DETACHED)
//	            {
//	                break;
//	            }
//				KeyDispose();
//	        }
//	
//	        // Disable USB-related interrupts.
//	        _DRVUSB_ENABLE_MISC_INT(0);
//	    }		      
//    }
//}




