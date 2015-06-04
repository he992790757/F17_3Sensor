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
//extern volatile uint32_t	SysData[18];					   //ϵͳ��Ϣ�洢
const uint8_t g_HID_au8DeviceReportDescriptor[] =
{

    0x05, 0x01, 	// USAGE_PAGE (Generic Desktop)
    0x09, 0x00, 	// USAGE (0)

    0xa1, 0x01, 	// COLLECTION (Application)
    0x15, 0x00, 	//     LOGICAL_MINIMUM (0)		// �߼���Сֵ
    0x25, 0xff, 	//     LOGICAL_MAXIMUM (255)	// �߼����ֵ
    0x19, 0x01, 	//     USAGE_MINIMUM (1)		// ��;��Сֵ
    0x29, 0x08, 	//     USAGE_MAXIMUM (8)		// ��;���ֵ
    0x95, HID_MAX_PACKET_SIZE_EP0, //     REPORT_COUNT (8)

    0x75, 0x08, 	//     REPORT_SIZE (8)			// ������ַ����
    0x81, 0x02, 	//     INPUT (Data,Var,Abs)		// ֵ

    0x19, 0x01, 	//     USAGE_MINIMUM (1)
    0x29, 0x08, 	//     USAGE_MAXIMUM (8)

    0x91, 0x02, 	//   OUTPUT (Data,Var,Abs)

    0xc0        	// END_COLLECTION

/*
 //ÿ�п�ʼ�ĵ�һ�ֽ�Ϊ����Ŀ��ǰ׺��ǰ׺�ĸ�ʽΪ��
 //D7~D4��bTag��D3~D2��bType��D1~D0��bSize�����·ֱ��ÿ����Ŀע�͡�
 
 //����һ��ȫ�֣�bTypeΪ1����Ŀ������;ҳѡ��Ϊ��ͨ����Generic Desktop Page��
 //�����1�ֽ����ݣ�bSizeΪ1����������ֽ����Ͳ�ע���ˣ��Լ�����bSize���жϡ�
 0x05, 0x01, // USAGE_PAGE (Generic Desktop)
 
 //����һ���ֲ���bTypeΪ2����Ŀ����;ѡ��Ϊ0x00������ͨ����ҳ�У�
 //����;��δ����ģ����ʹ�ø���;�������ϣ���ôϵͳ���������
 //������׼ϵͳ�豸���Ӷ��ͳ���һ���û��Զ����HID�豸��
 0x09, 0x00, // USAGE (0)
 
 //����һ������Ŀ��bTypeΪ0����Ŀ�������ϣ������������0x01��ʾ
 //�ü�����һ��Ӧ�ü��ϡ�����������ǰ������;ҳ����;����Ϊ
 //�û��Զ��塣
 0xa1, 0x01, // COLLECTION (Application)

 //����һ��ȫ����Ŀ��˵���߼�ֵ��СֵΪ0��
 0x15, 0x00, //     LOGICAL_MINIMUM (0)
 
 //����һ��ȫ����Ŀ��˵���߼�ֵ���Ϊ255��
 0x25, 0xff, //     LOGICAL_MAXIMUM (255)
 
 //����һ���ֲ���Ŀ��˵����;����СֵΪ1��
 0x19, 0x01, //     USAGE_MINIMUM (1)
 
 //����һ���ֲ���Ŀ��˵����;�����ֵ8��
 0x29, 0x08, //     USAGE_MAXIMUM (8) 
 
 //����һ��ȫ����Ŀ��˵�������������Ϊ�˸���
 0x95, 0x40, //     REPORT_COUNT (8)
 
 //����һ��ȫ����Ŀ��˵��ÿ��������ĳ���Ϊ8bit����1�ֽڡ�
 0x75, 0x08, //     REPORT_SIZE (8)
 
 //����һ������Ŀ��˵����8������Ϊ8bit����������Ϊ���롣
 0x81, 0x02, //     INPUT (Data,Var,Abs)
 
 //����һ���ֲ���Ŀ��˵����;����СֵΪ1��
 0x19, 0x01, //     USAGE_MINIMUM (1)
 
 //����һ���ֲ���Ŀ��˵����;�����ֵ8��
 0x29, 0x08, //     USAGE_MAXIMUM (8) 
 
 //����һ������Ŀ������������ݣ�8�ֽڣ�ע��ǰ���ȫ����Ŀ����
 0x91, 0x02, //   OUTPUT (Data,Var,Abs)
 
 //�����������Ŀ�����ر�ǰ��ļ��ϡ�bSizeΪ0�����Ժ���û���ݡ�
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
	
	//MCU_Status.Struct_Status=1;		//ָ��ִ��״̬��00���ճɹ���01ִ�гɹ���02ʧ�ܣ�03����
	//MCU_Status.Sys_Status=4;		//ϵͳ״̬��01 U�� 02 PC-CAM 03������ʾ״̬������USB��04 ������ʾ״̬��δ��USB
	//MCU_Status.Sen_Status=1;		//sensor״̬��01 ȫ�� 02 �ֲ� 03 ϸ�ھֲ� 04 C608 
	//MCU_Status.Scale_Status=1;		//��ʾ����״̬��01 16:9  02 4:3 
	//MCU_Status.Menu_Status=1;		//�˵�״̬��01 Ԥ��ģʽ 02 �ط� 03����
	//MCU_Status.SD_Status=2;
 
		pu8Buffer[0]=0x47;						//G
		pu8Buffer[1]=0x52;						//R
		pu8Buffer[2]=0x09;//0x09;						//ָ�����ݳ��ȣ�����ָ��ͷ��ָ��β
		pu8Buffer[3]=0x23;						//ָ��ͷ
		pu8Buffer[4]=MCU_Status.Struct_Name;	// ָ������
		pu8Buffer[5]=MCU_Status.Struct_Status;
		pu8Buffer[6]=System.Uart.UsbFlag	;		//MCU_Status.Sys_Status;
		pu8Buffer[7]=System.Uart.Sensor;			//MCU_Status.Sen_Status;
		pu8Buffer[8]=System.Uart.Display;			//MCU_Status.Scale_Status;
		pu8Buffer[9]=System.Uart.PlayZom;			// System.Uart.PhotoFlag;			//MCU_Status.Menu_Status;
		pu8Buffer[10]= System.Process_TakePht ;  //System.Uart.SdFlag; 			//MCU_Status.SD_Status;
		pu8Buffer[11]=System.Led.Statu ;			//MCU_Status.LED_Status;	

	// �˴����ػ�����Ϣ


		pu8Buffer[12]=0xAA;
		pu8Buffer[13] = 0x24 ; 
		switch(pu8Buffer[4])
		{
			case V6M_CMD_C_Sys_Inf : // ϵͳ��Ϣ
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
			case V6M_CMD_C_Mac_Ver: // �����ͺ�
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
			case V6M_CMD_C_Pro_Num: //��Ʒ���к�
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
			case V6M_CMD_C_Mac_Num: //�������
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
			case V6M_CMD_C_Sof_Ver: //����汾
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
			case V6M_CMD_C_Pro_Dat:  //��������
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
			case V6M_CMD_C_Hrd_Ver: //Ӳ���汾
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
			case V6M_CMD_C_Sign_NUM: //��Ƭ����
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
