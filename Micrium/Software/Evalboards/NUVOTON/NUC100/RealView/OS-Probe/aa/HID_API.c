/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2009 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "DrvUSB.h"
#include "HIDSysIO.h"
#include "HID_API.h"
#include "V6MDebug.h"
#include "config.h"
#include "global.h"
#include "performance.h"

#define HID_FUNCTION    0

/* Define the vendor id and product id */
#define USB_VID			0x0416+0x104 // 0x051A
#define USB_PID			0x501B+0x100 // 0x511B

//#define USB_VID			0x0416
//#define USB_PID			0x501B

#define HID_DEFAULT_INT_IN_INTERVAL	255
#define HID_IS_SELF_POWERED         0
#define HID_IS_REMOTE_WAKEUP        0
#define HID_MAX_POWER               50  		/* The unit is in 2mA. ex: 50 * 2mA = 100mA */

//#define HID_REPORT_SIZE             64		/* 14 */
#define HID_REPORT_SIZE		    HID_MAX_PACKET_SIZE_EP0       /* The unit is in bytes */
#define LEN_CONFIG_AND_SUBORDINATE (LEN_CONFIG+LEN_INTERFACE+LEN_HID+LEN_ENDPOINT*2)

// extern volatile Status MCU_Status;
//extern volatile uint8_t Status_Change;
extern S_HID_DEVICE g_HID_sDevice;
//extern volatile uint8_t SysInfo;
//extern volatile uint32_t	SysData[18];					   //系统信息存储
const uint8_t g_HID_au8DeviceReportDescriptor[] =
{

    0x05, 0x01, 	// USAGE_PAGE (Generic Desktop)
    0x09, 0x00, 	// USAGE (0)

    0xa1, 0x01, 	// COLLECTION (Application)
    0x15, 0x00, 	//     LOGICAL_MINIMUM (0)		// 逻辑最小值
    0x25, 0xff, 	//     LOGICAL_MAXIMUM (255)	// 逻辑最大值
    0x19, 0x01, 	//     USAGE_MINIMUM (1)		// 用途最小值
    0x29, 0x08, 	//     USAGE_MAXIMUM (8)		// 用途最大值
    0x95, HID_MAX_PACKET_SIZE_EP0, //     REPORT_COUNT (8)

    0x75, 0x08, 	//     REPORT_SIZE (8)			// 报告的字符宽度
    0x81, 0x02, 	//     INPUT (Data,Var,Abs)		// 值

    0x19, 0x01, 	//     USAGE_MINIMUM (1)
    0x29, 0x08, 	//     USAGE_MAXIMUM (8)

    0x91, 0x02, 	//   OUTPUT (Data,Var,Abs)

    0xc0        	// END_COLLECTION

/*
 //每行开始的第一字节为该条目的前缀，前缀的格式为：
 //D7~D4：bTag。D3~D2：bType；D1~D0：bSize。以下分别对每个条目注释。
 
 //这是一个全局（bType为1）条目，将用途页选择为普通桌面Generic Desktop Page。
 //后面跟1字节数据（bSize为1），后面的字节数就不注释了，自己根据bSize来判断。
 0x05, 0x01, // USAGE_PAGE (Generic Desktop)
 
 //这是一个局部（bType为2）条目，用途选择为0x00。在普通桌面页中，
 //该用途是未定义的，如果使用该用途来开集合，那么系统将不会把它
 //当作标准系统设备，从而就成了一个用户自定义的HID设备。
 0x09, 0x00, // USAGE (0)
 
 //这是一个主条目（bType为0）条目，开集合，后面跟的数据0x01表示
 //该集合是一个应用集合。它的性质在前面由用途页和用途定义为
 //用户自定义。
 0xa1, 0x01, // COLLECTION (Application)

 //这是一个全局条目，说明逻辑值最小值为0。
 0x15, 0x00, //     LOGICAL_MINIMUM (0)
 
 //这是一个全局条目，说明逻辑值最大为255。
 0x25, 0xff, //     LOGICAL_MAXIMUM (255)
 
 //这是一个局部条目，说明用途的最小值为1。
 0x19, 0x01, //     USAGE_MINIMUM (1)
 
 //这是一个局部条目，说明用途的最大值8。
 0x29, 0x08, //     USAGE_MAXIMUM (8) 
 
 //这是一个全局条目，说明数据域的数量为八个。
 0x95, 0x40, //     REPORT_COUNT (8)
 
 //这是一个全局条目，说明每个数据域的长度为8bit，即1字节。
 0x75, 0x08, //     REPORT_SIZE (8)
 
 //这是一个主条目，说明有8个长度为8bit的数据域做为输入。
 0x81, 0x02, //     INPUT (Data,Var,Abs)
 
 //这是一个局部条目，说明用途的最小值为1。
 0x19, 0x01, //     USAGE_MINIMUM (1)
 
 //这是一个局部条目，说明用途的最大值8。
 0x29, 0x08, //     USAGE_MAXIMUM (8) 
 
 //这是一个主条目。定义输出数据（8字节，注意前面的全局条目）。
 0x91, 0x02, //   OUTPUT (Data,Var,Abs)
 
 //下面这个主条目用来关闭前面的集合。bSize为0，所以后面没数据。
 0xc0        // END_COLLECTION
*/ 
};

#define HID_DEVICE_REPORT_DESCRIPTOR_SIZE \
    sizeof (g_HID_au8DeviceReportDescriptor) / sizeof(g_HID_au8DeviceReportDescriptor[0])
const uint32_t g_HID_u32DeviceReportDescriptorSize = HID_DEVICE_REPORT_DESCRIPTOR_SIZE;


#define HID_REPORT_DESCRIPTOR_SIZE HID_DEVICE_REPORT_DESCRIPTOR_SIZE

static uint8_t g_au8DeviceReport[HID_REPORT_SIZE];
static const uint32_t g_u32DeviceReportSize = sizeof(g_au8DeviceReport) / sizeof(g_au8DeviceReport[0]);

const uint8_t gau8DeviceDescriptor[] =
{
    LEN_DEVICE,		// bLength
    DESC_DEVICE,	// bDescriptorType
    0x10, 0x01,		// bcdUSB
    0x00,			// bDeviceClass
    0x00,			// bDeviceSubClass
    0x00,			// bDeviceProtocol
    HID_MAX_PACKET_SIZE_EP0,	// bMaxPacketSize0
    // idVendor
    USB_VID & 0x00FF,
    (USB_VID & 0xFF00) >> 8,
    // idProduct
    USB_PID & 0x00FF,
    (USB_PID & 0xFF00) >> 8,
    0x00, 0x00,		// bcdDevice
    0x01,			// iManufacture
    0x02,			// iProduct
    0x03,			// iSerialNumber
    0x01			// bNumConfigurations
};

const uint8_t gau8ConfigDescriptor[] =
{
    LEN_CONFIG,		// bLength
    DESC_CONFIG,	// bDescriptorType
    // wTotalLength
    LEN_CONFIG_AND_SUBORDINATE & 0x00FF,
    (LEN_CONFIG_AND_SUBORDINATE & 0xFF00) >> 8,
    0x01,			// bNumInterfaces
    0x01,			// bConfigurationValue
    0x00,			// iConfiguration
    0x80 | (HID_IS_SELF_POWERED << 6) | (HID_IS_REMOTE_WAKEUP << 5),// bmAttributes
    HID_MAX_POWER,			// MaxPower

    // I/F descr: HID
    LEN_INTERFACE,	// bLength
    DESC_INTERFACE,	// bDescriptorType
    0x00,			// bInterfaceNumber
    0x00,			// bAlternateSetting
    0x02,			// bNumEndpoints
    0x03,			// bInterfaceClass
    0x00,			// bInterfaceSubClass
    0x00,			// bInterfaceProtocol
    0x00,			// iInterface

    // HID Descriptor
    LEN_HID,		// Size of this descriptor in UINT8s.
    DESC_HID,		// HID descriptor type.
    0x10, 0x01, 	// HID Class Spec. release number.
    0x00,			// H/W target country.
    0x01,			// Number of HID class descriptors to follow.
    DESC_HID_RPT,	// Dscriptor type.
    // Total length of report descriptor.
    HID_REPORT_DESCRIPTOR_SIZE & 0x00FF,
    (HID_REPORT_DESCRIPTOR_SIZE & 0xFF00) >> 8,

    // EP Descriptor: interrupt in.
    LEN_ENDPOINT,	// bLength
    DESC_ENDPOINT,	// bDescriptorType
    HID_IN_EP_NUM | EP_INPUT,   // bEndpointAddress
    EP_INT, // bmAttributes
    // wMaxPacketSize
    HID_MAX_PACKET_SIZE_EP1 & 0x00FF,
    (HID_MAX_PACKET_SIZE_EP1 & 0xFF00) >> 8,
    HID_DEFAULT_INT_IN_INTERVAL,		// bInterval

    // EP Descriptor: interrupt out.
    LEN_ENDPOINT,	// bLength
    DESC_ENDPOINT,	// bDescriptorType
    HID_OUT_EP_NUM | EP_OUTPUT,   // bEndpointAddress
    EP_INT, // bmAttributes
    // wMaxPacketSize
    HID_MAX_PACKET_SIZE_EP2 & 0x00FF,
    (HID_MAX_PACKET_SIZE_EP2 & 0xFF00) >> 8,
    HID_DEFAULT_INT_IN_INTERVAL		// bInterval

};

const uint8_t gau8StringLang[4] =
{
    4,				// bLength
    DESC_STRING,	// bDescriptorType
    0x09, 0x04
};

const uint8_t gau8VendorStringDescriptor[] =
{
    16,
    DESC_STRING,
    'S', 0,
    'Z', 0,
    'G', 0,
    'R', 0,
    '-', 0,
    'A', 0,
    'D', 0
};

const uint8_t gau8ProductStringDescriptor[] =
{
    22,
    DESC_STRING,
    'G', 0,
    'R', 0,
    ' ', 0,
    'U', 0,
    'S', 0,
    'B', 0,
    ' ', 0,
    'H', 0,
    'I', 0,
    'D', 0
};

const uint8_t gau8StringSerial[26] =
{
    26,				// bLength
    DESC_STRING,	// bDescriptorType
    'B', 0,
    '0', 0,
    '2', 0,
    '0', 0,
    '1', 0,
    '3', 0,
    '0', 0,
    '9', 0,
    '2', 0,
    '1', 0,
    '1', 0,
    '0', 0
};

void HID_Init(void *pfGetInReport, void *pfSetOutReport)
{
    /* Open HID to initial the descriptors and control handlers */
    HID_Open(HID_REPORT_SIZE, pfGetInReport, pfSetOutReport);

    /* Set the HID report descriptor */
    HID_SetReportDescriptor(g_HID_au8DeviceReportDescriptor, g_HID_u32DeviceReportDescriptorSize);

    /* Set the HID report buffer */
    HID_SetReportBuf(g_au8DeviceReport, g_u32DeviceReportSize);
}


/* Data for input & output */
static uint8_t g_u8CmdIndex = 0;
void USB_SendBackData(uint8_t bError, const uint8_t *pu8Buffer, uint32_t u32Size)
{
    uint8_t *pu8EpBuf;

    pu8EpBuf = (uint8_t *) & g_au8DeviceReport;
    if (u32Size > sizeof(g_au8DeviceReport))
        u32Size = sizeof(g_au8DeviceReport);

    pu8EpBuf[0] = (g_u8CmdIndex & (uint8_t)0x7F) | (bError ? (uint8_t)0x80 : (uint8_t)0x00);
    pu8EpBuf[1] = (uint8_t)u32Size;
    memcpy(&pu8EpBuf[2], pu8Buffer, u32Size);
}

/* This callback will be executed whenever the interrupt IN transaction is received from HOST to get
   report. */

void HID_GetInReport(uint8_t *buf)
{
 	uint8_t  pu8Buffer[32]; //i, 
	
	//MCU_Status.Struct_Status=1;		//指令执行状态，00接收成功，01执行成功，02失败，03其他
	//MCU_Status.Sys_Status=4;		//系统状态，01 U盘 02 PC-CAM 03机器显示状态（接了USB）04 机器显示状态，未接USB
	//MCU_Status.Sen_Status=1;		//sensor状态，01 全幅 02 局部 03 细节局部 04 C608 
	//MCU_Status.Scale_Status=1;		//显示比例状态，01 16:9  02 4:3 
	//MCU_Status.Menu_Status=1;		//菜单状态，01 预览模式 02 回放 03其他
	//MCU_Status.SD_Status=2;
 
		pu8Buffer[0]=0x47;						//G
		pu8Buffer[1]=0x52;						//R
		pu8Buffer[2]=0x09;//0x09;						//指令数据长度，包括指令头和指令尾
		pu8Buffer[3]=0x23;						//指令头
		pu8Buffer[4]=MCU_Status.Struct_Name;	// 指令名称
		pu8Buffer[5]=MCU_Status.Struct_Status;
		pu8Buffer[6]=System.Uart.UsbFlag	;		//MCU_Status.Sys_Status;
		pu8Buffer[7]=System.Uart.Sensor;			//MCU_Status.Sen_Status;
		pu8Buffer[8]=System.Uart.Display;			//MCU_Status.Scale_Status;
		pu8Buffer[9]=System.Uart.PlayZom;			// System.Uart.PhotoFlag;			//MCU_Status.Menu_Status;
		pu8Buffer[10]= System.Process_TakePht ;  //System.Uart.SdFlag; 			//MCU_Status.SD_Status;
		pu8Buffer[11]=System.Led.Statu ;			//MCU_Status.LED_Status;	

	// 此处返回机器信息


		pu8Buffer[12]=0xAA;
		pu8Buffer[13] = 0x24 ; 
		switch(pu8Buffer[4])
		{
			case V6M_CMD_C_Sys_Inf : // 系统信息
			{	
				pu8Buffer[14] = V6M_CMD_C_Sys_Inf ; 
				pu8Buffer[15]=(uint8_t)(System.Sys.Data.info.SysInfo[0]>>24); //(SysData[0]>>24);
				pu8Buffer[16]=(uint8_t)(System.Sys.Data.info.SysInfo[0]>>16);
				pu8Buffer[17]=(uint8_t)(System.Sys.Data.info.SysInfo[0]>>8);
				pu8Buffer[18]=(uint8_t)(System.Sys.Data.info.SysInfo[0]);
				pu8Buffer[19]=(uint8_t)(System.Sys.Data.info.SysInfo[1]>>24);
				pu8Buffer[20]=(uint8_t)(System.Sys.Data.info.SysInfo[1]>>16);
				pu8Buffer[21]=(uint8_t)(System.Sys.Data.info.SysInfo[1]>>8);
				pu8Buffer[22]=(uint8_t)(System.Sys.Data.info.SysInfo[1]);
				pu8Buffer[23]=(uint8_t)(System.Sys.Data.info.SysInfo[2]>>24);
				pu8Buffer[24]=(uint8_t)(System.Sys.Data.info.SysInfo[2]>>16);
				pu8Buffer[25]=(uint8_t)(System.Sys.Data.info.SysInfo[2]>>8);
				pu8Buffer[26]=(uint8_t)(System.Sys.Data.info.SysInfo[2]);
			}	break ; 
			case V6M_CMD_C_Mac_Ver: // 机器型号
			{	
				pu8Buffer[14] =V6M_CMD_C_Mac_Ver; 
				pu8Buffer[15]=(uint8_t)(System.Sys.Data.info.MachineType[0]>>24);
				pu8Buffer[16]=(uint8_t)(System.Sys.Data.info.MachineType[0]>>16);
				pu8Buffer[17]=(uint8_t)(System.Sys.Data.info.MachineType[0]>>8);
				pu8Buffer[18]=(uint8_t)(System.Sys.Data.info.MachineType[0]);
				pu8Buffer[19]=(uint8_t)(System.Sys.Data.info.MachineType[1]>>24);
				pu8Buffer[20]=(uint8_t)(System.Sys.Data.info.MachineType[1]>>16);
				pu8Buffer[21]=(uint8_t)(System.Sys.Data.info.MachineType[1]>>8);
				pu8Buffer[22]=(uint8_t)(System.Sys.Data.info.MachineType[1]);
				pu8Buffer[23]=(uint8_t)(System.Sys.Data.info.MachineType[2]>>24);
				pu8Buffer[24]=(uint8_t)(System.Sys.Data.info.MachineType[2]>>16);
				pu8Buffer[25]=(uint8_t)(System.Sys.Data.info.MachineType[2]>>8);
				pu8Buffer[26]=(uint8_t)(System.Sys.Data.info.MachineType[2]);
			}	break ; 	
			case V6M_CMD_C_Pro_Num: //产品序列号
			{	
				pu8Buffer[14] =V6M_CMD_C_Pro_Num; 
				pu8Buffer[15]=(uint8_t)(System.Sys.Data.info.CdKey[0]>>24);
				pu8Buffer[16]=(uint8_t)(System.Sys.Data.info.CdKey[0]>>16);
				pu8Buffer[17]=(uint8_t)(System.Sys.Data.info.CdKey[0]>>8);
				pu8Buffer[18]=(uint8_t)(System.Sys.Data.info.CdKey[0]);
				pu8Buffer[19]=(uint8_t)(System.Sys.Data.info.CdKey[1]>>24);
				pu8Buffer[20]=(uint8_t)(System.Sys.Data.info.CdKey[1]>>16);
				pu8Buffer[21]=(uint8_t)(System.Sys.Data.info.CdKey[1]>>8);
				pu8Buffer[22]=(uint8_t)(System.Sys.Data.info.CdKey[1]);
				pu8Buffer[23]=(uint8_t)(System.Sys.Data.info.CdKey[2]>>24);
				pu8Buffer[24]=(uint8_t)(System.Sys.Data.info.CdKey[2]>>16);
				pu8Buffer[25]=(uint8_t)(System.Sys.Data.info.CdKey[2]>>8);
				pu8Buffer[26]=(uint8_t)(System.Sys.Data.info.CdKey[2]);
			}	break ; 
			case V6M_CMD_C_Mac_Num: //机器编号
			{	
				pu8Buffer[14] =V6M_CMD_C_Mac_Num ; 
				pu8Buffer[15]=(uint8_t)(System.Sys.Data.info.MachineNum[0]>>24);
				pu8Buffer[16]=(uint8_t)(System.Sys.Data.info.MachineNum[0]>>16);
				pu8Buffer[17]=(uint8_t)(System.Sys.Data.info.MachineNum[0]>>8);
				pu8Buffer[18]=(uint8_t)(System.Sys.Data.info.MachineNum[0]);
				pu8Buffer[19]=(uint8_t)(System.Sys.Data.info.MachineNum[1]>>24);
				pu8Buffer[20]=(uint8_t)(System.Sys.Data.info.MachineNum[1]>>16);
				pu8Buffer[21]=(uint8_t)(System.Sys.Data.info.MachineNum[1]>>8);
				pu8Buffer[22]=(uint8_t)(System.Sys.Data.info.MachineNum[1]);
				pu8Buffer[23]=(uint8_t)(System.Sys.Data.info.MachineNum[2]>>24);
				pu8Buffer[24]=(uint8_t)(System.Sys.Data.info.MachineNum[2]>>16);
				pu8Buffer[25]=(uint8_t)(System.Sys.Data.info.MachineNum[2]>>8);
				pu8Buffer[26]=(uint8_t)(System.Sys.Data.info.MachineNum[2]);
			}	break ; 
			case V6M_CMD_C_Sof_Ver: //软件版本
			{	
				pu8Buffer[14] =V6M_CMD_C_Sof_Ver; 
				pu8Buffer[15]=(uint8_t)(System.Sys.Data.info.SoftwareVer[0]>>24);
				pu8Buffer[16]=(uint8_t)(System.Sys.Data.info.SoftwareVer[0]>>16);
				pu8Buffer[17]=(uint8_t)(System.Sys.Data.info.SoftwareVer[0]>>8);
				pu8Buffer[18]=(uint8_t)(System.Sys.Data.info.SoftwareVer[0]);
				pu8Buffer[19]=(uint8_t)(System.Sys.Data.info.SoftwareVer[1]>>24);
				pu8Buffer[20]=(uint8_t)(System.Sys.Data.info.SoftwareVer[1]>>16);
				pu8Buffer[21]=(uint8_t)(System.Sys.Data.info.SoftwareVer[1]>>8);
				pu8Buffer[22]=(uint8_t)(System.Sys.Data.info.SoftwareVer[1]);
				pu8Buffer[23]=(uint8_t)(System.Sys.Data.info.SoftwareVer[2]>>24);
				pu8Buffer[24]=(uint8_t)(System.Sys.Data.info.SoftwareVer[2]>>16);
				pu8Buffer[25]=(uint8_t)(System.Sys.Data.info.SoftwareVer[2]>>8);
				pu8Buffer[26]=(uint8_t)(System.Sys.Data.info.SoftwareVer[2]);
			}	break ; 
			case V6M_CMD_C_Pro_Dat:  //生产日期
			{	
				pu8Buffer[14] =V6M_CMD_C_Pro_Dat ; 
				pu8Buffer[15]=(uint8_t)(System.Sys.Data.info.ProductDate[0]>>24);
				pu8Buffer[16]=(uint8_t)(System.Sys.Data.info.ProductDate[0]>>16);
				pu8Buffer[17]=(uint8_t)(System.Sys.Data.info.ProductDate[0]>>8);
				pu8Buffer[18]=(uint8_t)(System.Sys.Data.info.ProductDate[0]);
				pu8Buffer[19]=(uint8_t)(System.Sys.Data.info.ProductDate[1]>>24);
				pu8Buffer[20]=(uint8_t)(System.Sys.Data.info.ProductDate[1]>>16);
				pu8Buffer[21]=(uint8_t)(System.Sys.Data.info.ProductDate[1]>>8);
				pu8Buffer[22]=(uint8_t)(System.Sys.Data.info.ProductDate[1]);
				pu8Buffer[23]=(uint8_t)(System.Sys.Data.info.ProductDate[2]>>24);
				pu8Buffer[24]=(uint8_t)(System.Sys.Data.info.ProductDate[2]>>16);
				pu8Buffer[25]=(uint8_t)(System.Sys.Data.info.ProductDate[2]>>8);
				pu8Buffer[26]=(uint8_t)(System.Sys.Data.info.ProductDate[2]);
			}	break ; 
			case V6M_CMD_C_Hrd_Ver: //硬件版本
			{	
				pu8Buffer[14] =V6M_CMD_C_Hrd_Ver; 
				pu8Buffer[15]=(uint8_t)(System.Sys.Data.info.HardwareVer[0]>>24);
				pu8Buffer[16]=(uint8_t)(System.Sys.Data.info.HardwareVer[0]>>16);
				pu8Buffer[17]=(uint8_t)(System.Sys.Data.info.HardwareVer[0]>>8);
				pu8Buffer[18]=(uint8_t)(System.Sys.Data.info.HardwareVer[0]);
				pu8Buffer[19]=(uint8_t)(System.Sys.Data.info.HardwareVer[1]>>24);
				pu8Buffer[20]=(uint8_t)(System.Sys.Data.info.HardwareVer[1]>>16);
				pu8Buffer[21]=(uint8_t)(System.Sys.Data.info.HardwareVer[1]>>8);
				pu8Buffer[22]=(uint8_t)(System.Sys.Data.info.HardwareVer[1]);
				pu8Buffer[23]=(uint8_t)(System.Sys.Data.info.HardwareVer[2]>>24);
				pu8Buffer[24]=(uint8_t)(System.Sys.Data.info.HardwareVer[2]>>16);
				pu8Buffer[25]=(uint8_t)(System.Sys.Data.info.HardwareVer[2]>>8);
				pu8Buffer[26]=(uint8_t)(System.Sys.Data.info.HardwareVer[2]);
			}	break ; 
			case V6M_CMD_C_Sign_NUM: //照片参数
			{	
				pu8Buffer[14] =V6M_CMD_C_Sign_NUM; 
				pu8Buffer[15]=(uint8_t)System.SignOutCount>>8 ;
				pu8Buffer[16]=(uint8_t)System.SignOutCount ;
				pu8Buffer[17]=(uint8_t)System.Signtotal >>8 ;
				pu8Buffer[18]=(uint8_t)System.Signtotal ;
				pu8Buffer[19] = (uint8_t)Local_SignOutCount>>8 ; //(uint8_t)System.Signtotal >>8 ; 
				pu8Buffer[20] = (uint8_t)Local_SignOutCount ;
				pu8Buffer[21]=0;
				pu8Buffer[22]=0;
				pu8Buffer[23]=0;
				pu8Buffer[24]=0;
				pu8Buffer[25]=0;
				pu8Buffer[26]=0;
			}	break ; 																								
			default:
			{
				pu8Buffer[14]=0x00 ; 
				pu8Buffer[15]=0x00 ;
				pu8Buffer[16]=0x00 ;
				pu8Buffer[17]=0x00 ;
				pu8Buffer[18]=0x00 ;
				pu8Buffer[19]=0x00 ;
				pu8Buffer[20]=0x00 ;
				pu8Buffer[21]=0x00 ;
				pu8Buffer[22]=0x00 ;
				pu8Buffer[23]=0x00 ;
				pu8Buffer[24]=0x00 ;
				pu8Buffer[25]=0x00 ;
				pu8Buffer[26]=0x00 ;				
			}	break;					
		}
//		pu8Buffer[27] = (uint8_t)System.SignOutCount>>8 ; 
//		pu8Buffer[28] = (uint8_t)System.SignOutCount  ; 
//		pu8Buffer[29] = (uint8_t)Local_SignOutCount>>8 ; //(uint8_t)System.Signtotal >>8 ; 
//		pu8Buffer[30] = (uint8_t)Local_SignOutCount ;
		pu8Buffer[27] = 0xBB ; 
	 	USB_SendBackData(0, pu8Buffer, 28);	   	
}

/* This callback will be executed whenever the interrupt OUT transaction is received from HOST to set
   report. */
void HID_SetOutReport(uint8_t *pu8EpBuf)
{
    uint32_t u32Size = (uint32_t)pu8EpBuf[1];
//	uint8_t	 i;
    //Set new index
    g_u8CmdIndex = pu8EpBuf[0];

//	printf("SetOutReport\n");
//	for(i=0;i<u32Size;i++)
//	{
//		 SendByte(pu8EpBuf[i]);
//	}

     V6M_ProcessCommand((uint8_t *)&pu8EpBuf[2], u32Size);
}

//int32_t HID_MainProcess(void)
//{
//    int32_t i32Ret = E_SUCCESS;
//    E_DRVUSB_STATE eUsbState;
//
//    i32Ret = DrvUSB_Open(0);
//    if (i32Ret != E_SUCCESS)
//        return i32Ret;
//
//    while (1)
//    {
//        /* Disable USB-related interrupts. */
//        _DRVUSB_ENABLE_MISC_INT(0);
//
//        /* Enable float-detection interrupt. */
//        _DRVUSB_ENABLE_FLDET_INT();
//
//        // Wait for USB connected.
//        while (1)
//        {
//            // Order here is significant.
//            // Give a chance to handle remaining events before exiting this loop.
//            eUsbState = DrvUSB_GetUsbState();
//
//            //DrvUSB_DispatchEvent();
//
//            if (eUsbState >= eDRVUSB_ATTACHED &&
//                    eUsbState != eDRVUSB_SUSPENDED)
//            {
//                break;
//            }
//        }
//
//        /* Start HID and install the callback functions to handle in/out report */
//        HID_Init((void *)HID_GetInReport, (void *)HID_SetOutReport);
//
//        // Enable USB-related interrupts.
//        _DRVUSB_ENABLE_MISC_INT(INTEN_WAKEUP | INTEN_WAKEUPEN | INTEN_FLDET | INTEN_USB | INTEN_BUS);
//
//        // Poll and handle USB events.
//        while (1)
//        {
//            eUsbState = DrvUSB_GetUsbState();
//
//            DrvUSB_DispatchEvent();
//
//            if (eUsbState == eDRVUSB_DETACHED)
//            {
//                break;
//            }
//        }
//
//        // Disable USB-related interrupts.
//        _DRVUSB_ENABLE_MISC_INT(0);
//    }
//}
